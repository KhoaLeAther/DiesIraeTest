// Fill out your copyright notice in the Description page of Project Settings.


#include "DiesIrae/Characters/DiesIraeCharacter_Player.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ADiesIraeCharacter_Player::ADiesIraeCharacter_Player(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
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
}


//////////////////////////////////////////////////////////////////////////
// Input

void ADiesIraeCharacter_Player::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if (CharacterAbilityComponent)
	{
		LevelChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetLevelAttribute()).AddUObject(this, &ADiesIraeCharacter_Player::LevelChanged);
		ExpChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetExpAttribute()).AddUObject(this, &ADiesIraeCharacter_Player::ExpChanged);
		MaxExpChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetMaxExpAttribute()).AddUObject(this, &ADiesIraeCharacter_Player::MaxExpChanged);
	}

	SetLevel(1); // Initialize character level to 1 or load save here

	DiesIraeHUD = CreateWidget<UDiesIraeHUD>(GetWorld(), DiesIraeHUDClass);
	if (DiesIraeHUD.IsValid())
	{
		DiesIraeHUD->AddToViewport();
		DiesIraeHUD->InitializeHUD();
	}
}

void ADiesIraeCharacter_Player::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADiesIraeCharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADiesIraeCharacter_Player::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADiesIraeCharacter_Player::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADiesIraeCharacter_Player::SetLevel(int Level)
{
	if (CharacterAttributeSet)
	{
		CharacterAttributeSet->SetLevel(Level);
	}
}

void ADiesIraeCharacter_Player::SetExp(float Exp)
{
}

int ADiesIraeCharacter_Player::GetCharacterLevel() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetLevel();
	}

	return 0.0f;
}

float ADiesIraeCharacter_Player::GetExp() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetExp();
	}

	return 0.0f;
}

float ADiesIraeCharacter_Player::GetMaxExp() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetMaxExp();
	}

	return 0.0f;
}

void ADiesIraeCharacter_Player::HealthChanged(const FOnAttributeChangeData& Data)
{
	if (DiesIraeHUD.IsValid())
	{
		DiesIraeHUD->UpdatePlayerHealth(Data.NewValue / GetMaxHealth());
	}
}

void ADiesIraeCharacter_Player::LevelChanged(const FOnAttributeChangeData& Data)
{
	InitializeAttributes(GetCharacterLevel());
}

void ADiesIraeCharacter_Player::ExpChanged(const FOnAttributeChangeData& Data)
{
}

void ADiesIraeCharacter_Player::MaxExpChanged(const FOnAttributeChangeData& Data)
{
}

void ADiesIraeCharacter_Player::Move(const FInputActionValue& Value)
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

void ADiesIraeCharacter_Player::Look(const FInputActionValue& Value)
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
