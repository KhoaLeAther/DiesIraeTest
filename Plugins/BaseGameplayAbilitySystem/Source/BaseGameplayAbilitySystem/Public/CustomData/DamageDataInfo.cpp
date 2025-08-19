#include "DamageDataInfo.h"

void FGameplayEffectContext_HitReactData::AddDamageInfo(const FBDDamageInfo& InDamageInfo)
{
	//check(!DamageInfo.IsValid());
	DamageInfo = TSharedPtr<FBDDamageInfo>(new FBDDamageInfo(InDamageInfo));
}
