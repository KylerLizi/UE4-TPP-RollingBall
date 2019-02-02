// Fill out your copyright notice in the Description page of Project Settings.

#include "PassLocation.h"
#include "Engine.h"
#include "GameMode/BiliCodeGameModeBase.h"
#include "Components/StaticMeshComponent.h"
#include "BoxHit/HitBoxBase.h"

APassLocation::APassLocation()
{
	PassMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PassMeshComp"));
	HitBoxComp->SetupAttachment(PassMeshComp);
}

void APassLocation::OnHitSphere(AActor * sphere)
{
	ABiliCodeGameModeBase * GameModeBase = Cast<ABiliCodeGameModeBase>(GetWorld()->GetAuthGameMode());

	GameModeBase->SetPlayerInput(false);//π˝πÿÕ£÷π ‰»Î
} 