// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxHit/HitBoxBase.h"
#include "SetLocation.generated.h"

/**
 * 
 */
UCLASS()
class BILICODE_API ASetLocation : public AHitBoxBase
{
	GENERATED_BODY()
public:
	ASetLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent * SetMeshComp;// 声明复活点模型对象

public:
	virtual void OnHitSphere(AActor * sphere) override;
	
	
};
