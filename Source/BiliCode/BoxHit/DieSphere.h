// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitBoxBase.h"
#include "DieSphere.generated.h"


/**
 * 
 */
UCLASS()
class BILICODE_API ADieSphere : public AHitBoxBase
{
	GENERATED_BODY()

public:
	virtual void OnHitSphere(AActor * sphere) override;//重写函数比较安全，这里可以不写
	
};
