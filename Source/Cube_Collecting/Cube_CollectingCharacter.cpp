// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cube_CollectingCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Cube.h"
#include "CubeSpawner.h"
#include "MySphere.h"
#include "Actor_Spawner.h"
#include "GameHUD.h"
#include "Blueprint/UserWidget.h"
#include "MenuPlayerController.h"
#include "Engine/Engine.h"
//////////////////////////////////////////////////////////////////////////
// ACube_CollectingCharacter

ACube_CollectingCharacter::ACube_CollectingCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	GameHUD = nullptr;
	GameHUDClass = nullptr;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACube_CollectingCharacter::OnOverlapBegin);

	MaxHealth = 25.0f;
	Health = MaxHealth;

	HealthDelta = 5.0f;
	HealthDecayDelta = -0.7f;

	PrimaryActorTick.bCanEverTick = true;
}

void ACube_CollectingCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	//only create widget if the character is locally controlled(only when an actually user and screen is present)
	if (IsLocallyControlled() && GameHUDClass)
	{
		//set the owner of the widget to the player controller
		AMenuPlayerController* MPC = GetController<AMenuPlayerController>();
		check(MPC);
		GameHUD = CreateWidget<UGameHUD>(MPC, GameHUDClass);
		GameHUD->AddToPlayerScreen();
		GameHUD->SetHealth(Health, MaxHealth);
	}
}

void ACube_CollectingCharacter::SpawnActors()
{
	//Find the Actor Spawner in the world, and invoke it's Spawn Actor function
	//get the a cube spawner class
	AActor* ActorSpawnerTofind = UGameplayStatics::GetActorOfClass(GetWorld(), ACubeSpawner::StaticClass());

	//convert it to type acubespawner? which is a more usable format
	ACubeSpawner* ActorSpawnerReference = Cast<ACubeSpawner>(ActorSpawnerTofind);
	if (ActorSpawnerReference)
	{
		ActorSpawnerReference->SpawnCube();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpawnActors called!"));
	}
	
}

void ACube_CollectingCharacter::DestroyActors()
{
	//Get every Actor to Spawn in the world and invoke Destroy Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMySphere::StaticClass(), FoundActors);
	for (AActor* ActorFound : FoundActors)
	{
		ActorFound->Destroy();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("DestroyActors called!"));
	}
}

void ACube_CollectingCharacter::SpawnCube()
{
	UWorld* world = GetWorld();
	AActor* ActorSpawnerTofind = UGameplayStatics::GetActorOfClass(world, AActor_Spawner::StaticClass());
	AActor_Spawner* ActorSpawnerReference = Cast<AActor_Spawner>(ActorSpawnerTofind);
	if (ActorSpawnerReference)
	{
		ActorSpawnerReference->Spawn();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SpawnCube called!"));
		}
	}
	else {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("Error"));
		}
	}
}

void ACube_CollectingCharacter::DestroyCubes()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACube::StaticClass(), FoundActors);
	for (AActor* ActorFound : FoundActors)
	{
		ActorFound->Destroy();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, TEXT("DestoryCubes called!"));
		}
	}
}

void ACube_CollectingCharacter::EndPlay(const EEndPlayReason::Type EndPlay)
{
	if (GameHUD)
	{
		//remove the widget from the player's viewport
		GameHUD->RemoveFromParent();
		//let garbage collection delete the instance of the widget
		GameHUD = nullptr;
	}

	Super::EndPlay(EndPlay);
}

void ACube_CollectingCharacter::Tick(float DeltaTime)
{
	ACube_CollectingCharacter::LeakHealth();
}

void ACube_CollectingCharacter::LeakHealth()
{
	float TimeSinceStart = GetWorld()->GetTimeSeconds();
	if (TimeSinceStart > 60 && TimeSinceStart < 120)
	{
		HealthDecayDelta = -0.8f;
	}
	if (TimeSinceStart > 120 && TimeSinceStart < 180)
	{
		HealthDecayDelta = -1.0f;
	}
	if (TimeSinceStart > 180 && TimeSinceStart < 240)
	{
		HealthDecayDelta = -1.25;
	}
	if (TimeSinceStart > 240 && TimeSinceStart < 300)
	{
		HealthDecayDelta = -1.5;
	}
	if (TimeSinceStart > 300 && TimeSinceStart < 360)
	{
		HealthDecayDelta = -2.0f;
	}
	Health = FMath::Clamp(Health + (HealthDecayDelta * GetWorld()->GetDeltaSeconds()), 0.0f, MaxHealth);
	GameHUD->SetHealth(Health, MaxHealth);
	if (Health == 0.0f)
	{
		
	}
}

void ACube_CollectingCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACube::StaticClass()))
	{
		float HealthPercent = GameHUD->CheckHealth();
		if (HealthPercent == -1.0f)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("An error has occured"));
			}
		}
		if (!(HealthPercent == 1.0f))
		{
			Health = FMath::Clamp(Health + HealthDelta, 0.0f, MaxHealth);
			GameHUD->SetHealth(Health, MaxHealth);
		}

	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACube_CollectingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACube_CollectingCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACube_CollectingCharacter::Look);

		PlayerInputComponent->BindAction("Spawn_Actors", IE_Pressed, this, &ACube_CollectingCharacter::SpawnActors);
		PlayerInputComponent->BindAction("Destroy_Actors", IE_Pressed, this, &ACube_CollectingCharacter::DestroyActors);
		PlayerInputComponent->BindAction("Spawn_Cube", IE_Pressed, this, &ACube_CollectingCharacter::SpawnCube);
		PlayerInputComponent->BindAction("Destroy_Cubes", IE_Pressed, this, &ACube_CollectingCharacter::DestroyCubes);

	}

}


void ACube_CollectingCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACube_CollectingCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}




