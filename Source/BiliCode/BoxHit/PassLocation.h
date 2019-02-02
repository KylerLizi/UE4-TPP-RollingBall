// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxHit/HitBoxBase.h"
#include "PassLocation.generated.h"

/**
 * 
 */
UCLASS()
class BILICODE_API APassLocation : public AHitBoxBase
{
	GENERATED_BODY()
public:
	APassLocation();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent * PassMeshComp;

public:
	virtual void OnHitSphere(AActor * sphere) override;
	
	
};
