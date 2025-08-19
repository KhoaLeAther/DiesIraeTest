// Copyright Epic Games, Inc. All Rights Reserved.

#include "DiesIraeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseGameplayAbilityTags.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADiesIraeCharacter

ADiesIraeCharacter::ADiesIraeCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	CharacterAbilityComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

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
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
}

void ADiesIraeCharacter::BeginPlay()
{
	Super::BeginPlay();


	if (CharacterAbilityComponent)
	{
		HealthChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetHealthAttribute()).AddUObject(this, &ADiesIraeCharacter::HealthChanged);
		MaxHealthChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ADiesIraeCharacter::MaxHealthChanged);
		DamageChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetDamageAttribute()).AddUObject(this, &ADiesIraeCharacter::DamageChanged);
		InDamageChangedDelegateHandle = CharacterAbilityComponent->GetGameplayAttributeValueChangeDelegate(CharacterAttributeSet->GetInDamageAttribute()).AddUObject(this, &ADiesIraeCharacter::InDamageChanged);
	}
}

void ADiesIraeCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	if (CharacterAbilityComponent)
	{
		CharacterAttributeSet = NewObject<UBaseCharacterAttributeSet>(this, TEXT("AttributeSet"));
	}
}

void ADiesIraeCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADiesIraeCharacter::InitializeAttributes(int CharLevel)
{
	if (!CharacterAbilityComponent || !DefaultAttributes)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = CharacterAbilityComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle EffectHandle = CharacterAbilityComponent->MakeOutgoingSpec(DefaultAttributes, CharLevel, EffectContext);

	if (EffectHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = CharacterAbilityComponent->ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), CharacterAbilityComponent);
	}
	SetHealth(GetMaxHealth());
}

float ADiesIraeCharacter::GetHealth() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetHealth();
	}
	return 0.0f;
}

float ADiesIraeCharacter::GetMaxHealth() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetMaxHealth();
	}
	return 0.0f;
}

float ADiesIraeCharacter::GetDamage() const
{
	if (CharacterAttributeSet)
	{
		return CharacterAttributeSet->GetDamage();
	}
	return 0.0f;
}

void ADiesIraeCharacter::SetHealth(float Health)
{
	if (CharacterAttributeSet)
	{
		CharacterAttributeSet->SetHealth(Health);
	}
}

void ADiesIraeCharacter::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;
	UE_LOG(LogTemp, Warning, TEXT("Health Changed, remaining hp %f"), Health);

	if (!IsAlive() && !CharacterAbilityComponent->HasMatchingGameplayTag(CharacterState::Dead))//prevent playing dead animation or effect many times
	{
		Die();
	}
}

void ADiesIraeCharacter::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ADiesIraeCharacter::DamageChanged(const FOnAttributeChangeData& Data)
{
}

void ADiesIraeCharacter::InDamageChanged(const FOnAttributeChangeData& Data)
{
}

UAbilitySystemComponent* ADiesIraeCharacter::GetAbilitySystemComponent() const
{
	return CharacterAbilityComponent;
}

bool ADiesIraeCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ADiesIraeCharacter::Die_Implementation()
{
	if (CharacterAbilityComponent)
	{
		CharacterAbilityComponent->AddLooseGameplayTag(CharacterState::Dead);
	}
	// Optionally, you can also play a death animation or sound here
	UE_LOG(LogTemplateCharacter, Warning, TEXT("Character %s has died."), *GetName());

	// Disable character input

	// Optionally, you can destroy the character or set it to a ragdoll state
	// Destroy();
}
