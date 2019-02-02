// Fill out your copyright notice in the Description page of Project Settings.

#include "SetLocation.h"
#include "Player/SphereBase.h"
#include "GameMode/BiliCodeGameModeBase.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Components/StaticMeshComponent.h"


ASetLocation::ASetLocation()
{
	SetMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SetMesh"));//构造函数中初始化模型
	HitBoxComp->SetupAttachment(SetMeshComp);//碰撞盒父物体设置为模型Mesh  解决偏移量问题
}
void ASetLocation::OnHitSphere(AActor * sphere)
{
	ABiliCodeGameModeBase * GameModeBase = Cast<ABiliCodeGameModeBase>(GetWorld()->GetAuthGameMode());
	GameModeBase->SetStartPosition(HitBoxComp->GetComponentLocation());//碰撞时传递继承的碰撞盒（非类的坐标）的坐标

	//FVector NewLocation = sphere->GetActorLocation();
	// 实例化物体
	//// Spawn the new actor (Using GetClass() instead of AMySpawner so that if someone derives a new class  
	//// from AMySpawner we spawn an instance of that class instead)  
	//ASphereBase* NewActor = GetWorld()->SpawnActor<ASphereBase>(sphere->GetClass(), NewLocation, FRotator::ZeroRotator);
}



