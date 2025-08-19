// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWorldInteraction.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABaseWorldInteraction::ABaseWorldInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
	TriggerBox->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
}

// Called when the game starts or when spawned
void ABaseWorldInteraction::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::EnterInteractionRange);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OutOfInteractionRange);
}

// Called every frame
void ABaseWorldInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWorldInteraction::EnterInteractionRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (auto Character = Cast<ACharacter>(OtherActor))
	{
		if (auto PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				InteractingActor = OtherActor;
				InputComp->ClearBindingsForObject(this);//just to be safe in case multiple interactions nearby
				InputComp->BindAction(InteractionInputAction, InteractionInputTrigger, this, &ABaseWorldInteraction::OnInputActionReceived);
			}
		}
	}
}

void ABaseWorldInteraction::OutOfInteractionRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	InteractingActor = nullptr;
	if (auto Character = Cast<ACharacter>(OtherActor))
	{
		if (auto PlayerController = Cast<APlayerController>(Character->GetController()))
		{
			if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				InputComp->ClearBindingsForObject(this);
			}
		}
	}
}

void ABaseWorldInteraction::OnInputActionReceived(const FInputActionInstance& InputActionInstance)
{
	TriggerInteraction(InteractingActor);
}

void ABaseWorldInteraction::TriggerInteraction(AActor* InteractActor)
{
	bTriggered = true;
	K2_OnInteractionTriggered(InteractActor);
}


