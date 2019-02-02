// Fill out your copyright notice in the Description page of Project Settings.

#include "BiliCodeGameModeBase.h"
#include "Engine.h"
#include "Player/SphereBase.h"

ABiliCodeGameModeBase::ABiliCodeGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;//开启Tick,默认不调用

	DeathSum = 0;
	IsEnd = false;
}

void ABiliCodeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->GetFirstPlayerController()->GetPawn();//找到第一个玩家控制器
	ASphereBase * Pawn = Cast<ASphereBase>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Pawn)//获取到再赋值，比较安全
	{
		PlayerPawn = Pawn;
		StartPosition = PlayerPawn->GetActorLocation();//初始化复活点
		//CameraStartPos = PlayerPawn->CameraArmComp->RelativeLocation; 不用这样
	}
}

void ABiliCodeGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, StartPosition.ToString());//窗口显示调试信息
}


void ABiliCodeGameModeBase::SetPlayerLocation()
{
	//PlayerPawn->SetActorLocation(StartPosition);//重置小球（根节点）位置
	PlayerPawn->SphereMeshComp->SetRelativeLocation(StartPosition);//重置小球位置
	//FVector NewLocation = PlayerPawn->SphereMeshComp->GetRelativeTransform().GetLocation() - StartPosition;不用这样
	//PlayerPawn->CameraArmComp->SetRelativeLocation(CameraStartPos);不用这样
	PlayerPawn->SphereMeshComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));//速度归零
	PlayerPawn->SphereMeshComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));
	DeathSum++;
}

void ABiliCodeGameModeBase::SetStartPosition(FVector Location)
{
	if (Location != FVector(0, 0, 0))
	{
		StartPosition = Location;
		//CameraStartPos = PlayerPawn->CameraArmComp->RelativeLocation;不用这样
	}
}

void ABiliCodeGameModeBase::SetPlayerInput(bool isInput)//修改玩家能否输入
{
	PlayerPawn->IsInput = isInput;
	if (!isInput)//切断玩家输入则游戏结束
	{
		IsEnd = true;
	}
	PlayerPawn->SphereMeshComp->SetPhysicsLinearVelocity(FVector(0, 0, 0));//速度归零
	PlayerPawn->SphereMeshComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));
}

