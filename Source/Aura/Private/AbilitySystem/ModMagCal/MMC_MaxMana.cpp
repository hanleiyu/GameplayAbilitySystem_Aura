// Copyright Daria


#include "AbilitySystem/ModMagCal/MMC_MaxMana.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligentDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligentDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligentDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligentDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligent = 0.f;
	GetCapturedAttributeMagnitude(IntelligentDef, Spec, EvaluateParameters, Intelligent);
	Intelligent = FMath::Max(Intelligent, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level = CombatInterface->GetPlayerLevel();

	return 50.f + Intelligent * 2.5f + 15.f * Level;
}
