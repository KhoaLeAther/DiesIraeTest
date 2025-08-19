// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
//#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayEffectTypes.h"
#include "DamageDataInfo.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EDamageDirection : uint8
{
	EDD_Unknown,
	EDD_Forward,
	EDD_Backward,
	EDD_Left,
	EDD_Right,
	EDD_Up,
	EDD_Down
};

UENUM(BlueprintType)
enum EHitReactType : uint8
{
	EHRT_None,
	EHRT_Light,//normal stagger upper body anim
	EHRT_Heavy,//full body (default slot anim)
	EHRT_Airborne,//airborne (flymode, push upward)
	EHRT_Knockdown,//launch character
	EHRT_Custom //Retribution or special contextual anim
};

USTRUCT(BlueprintType)
struct FBDDamageInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	float DamageAmount = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	FGameplayTagContainer DamageTags;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	TEnumAsByte<EHitReactType> HitReact = EHitReactType::EHRT_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage Info")
	TEnumAsByte<EDamageDirection> DamageDirection = EDamageDirection::EDD_Unknown;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		DamageTags.NetSerialize(Ar, Map, bOutSuccess);
		return true;
	}
};

/*
USTRUCT(BlueprintType)
struct BASEGAMEPLAYABILITYSYSTEM_API FGameplayAbilityTargetData_HitReactData : public FGameplayAbilityTargetData
{
	GENERATED_BODY()
public:

	FGameplayAbilityTargetData_HitReactData()
	{
	}

	UPROPERTY()
	FBDDamageInfo DamageInfo;

	// This is required for all child structs of FGameplayAbilityTargetData
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayAbilityTargetData_HitReactData::StaticStruct();
	}

	// This is required for all child structs of FGameplayAbilityTargetData
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		DamageInfo.NetSerialize(Ar, Map, bOutSuccess);
		bOutSuccess = true;
		return true;
	}
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_HitReactData> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_HitReactData>
{
	enum
	{
		WithNetSerializer = true // This is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};*/

USTRUCT(BlueprintType)
struct BASEGAMEPLAYABILITYSYSTEM_API FGameplayEffectContext_HitReactData : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	FGameplayEffectContext_HitReactData()
	{
	}

	//UPROPERTY()
	TSharedPtr<FBDDamageInfo> DamageInfo;

	virtual void AddDamageInfo(const FBDDamageInfo& InDamageInfo);

	virtual FBDDamageInfo* GetDamageInfo() const
	{
		return DamageInfo.Get();
	}

	// This is required for all child structs of FGameplayEffectContext
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext_HitReactData::StaticStruct();
	}

	virtual FGameplayEffectContext_HitReactData* Duplicate() const override
	{
		FGameplayEffectContext_HitReactData* NewContext = new FGameplayEffectContext_HitReactData();
		*NewContext = *this;
		NewContext->AddActors(Actors);
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	// This is required for all child structs of FGameplayAbilityTargetData
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
	{
		bOutSuccess = true;
		return true;
	}
};

template<>
struct TStructOpsTypeTraits< FGameplayEffectContext_HitReactData > : public TStructOpsTypeTraitsBase2< FGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};