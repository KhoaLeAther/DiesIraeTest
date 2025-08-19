// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "InputTriggers.h"
#include "Components/BoxComponent.h"
#include "BaseWorldInteraction.generated.h"

UCLASS()
class WORLDINTERACTIONRUNTIME_API ABaseWorldInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWorldInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Interaction")
	bool IsTriggered() const { return bTriggered; }
	UFUNCTION(BlueprintPure, Category = "Interaction")
	AActor* GetInteractingActor() const { return InteractingActor; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Input")
	TObjectPtr<UInputAction> InteractionInputAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction|Input")
	ETriggerEvent InteractionInputTrigger = ETriggerEvent::Triggered;

	UFUNCTION(BlueprintImplementableEvent, Category = "Interaction")
	void K2_OnInteractionTriggered(AActor* InteractActor);

	UFUNCTION()
	void EnterInteractionRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OutOfInteractionRange(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnInputActionReceived(const FInputActionInstance& InputActionInstance);

	void TriggerInteraction(AActor* InteractActor);

private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> TriggerBox;

	AActor* InteractingActor = nullptr;
	bool bTriggered = false;
};
