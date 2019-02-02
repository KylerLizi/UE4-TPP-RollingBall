// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxHit/DieSphere.h"
#include "Engine.h"//GetWorld
#include "GameMode/BiliCodeGameModeBase.h"

void ADieSphere::OnHitSphere(AActor * sphere)
{
	//GetWorld()->GetAuthGameMode();
	ABiliCodeGameModeBase * GameModeBase = Cast<ABiliCodeGameModeBase>(GetWorld()->GetAuthGameMode());
	GameModeBase->SetPlayerLocation();//调用GameMode 位置set函数
}
