// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiesIrae/DiesIraeCharacter.h"
#include "DiesIrae/UI/DiesIraeHUD.h"
#include "DiesIraeCharacter_Player.generated.h"

/**
 * 
 */
UCLASS()
class DIESIRAE_API ADiesIraeCharacter_Player : public ADiesIraeCharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	/** Standard constructor, called after all reflected properties have been initialized */
	ADiesIraeCharacter_Player(const class FObjectInitializer& ObjectInitializer);

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	virtual void SetLevel(int Level);
	virtual void SetExp(float Exp);

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	int GetCharacterLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetExp() const;
	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetMaxExp() const;

	FDelegateHandle LevelChangedDelegateHandle;
	FDelegateHandle ExpChangedDelegateHandle;
	FDelegateHandle MaxExpChangedDelegateHandle;

	virtual void HealthChanged(const FOnAttributeChangeData& Data) override;
	virtual void LevelChanged(const FOnAttributeChangeData& Data);
	virtual void ExpChanged(const FOnAttributeChangeData& Data);
	virtual void MaxExpChanged(const FOnAttributeChangeData& Data);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "DiesIrae|HUD")
	TSubclassOf<UDiesIraeHUD> DiesIraeHUDClass;

	TWeakObjectPtr<UDiesIraeHUD> DiesIraeHUD;
};
