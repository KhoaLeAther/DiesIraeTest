// Fill out your copyright notice in the Description page of Project Settings.


#include "AIWorldInfoData.h"

void UAIWorldInfoData::UpdateRemainingTime(float DeltaTime)
{
	RemainTime += DeltaTime;
	if (RemainTime >= UpdateInterval)
	{
		if (BlackboardComp.IsValid())
		{
			UpdateWorldInfo();
		}
		RemainTime = 0.0f;//Reset time counter
	}
}
