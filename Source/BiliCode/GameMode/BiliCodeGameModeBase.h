// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BiliCodeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BILICODE_API ABiliCodeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		ABiliCodeGameModeBase();//添加GameMode构造函数

public:
	virtual void BeginPlay() override;//添加overr安全一些

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayPawn")
		class ASphereBase * PlayerPawn;//定义小球玩家指针
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StartPosition;
	//FVector CameraStartPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DeathSum")
		int32 DeathSum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsEnd;//检测游戏是否已结束
public:
	UFUNCTION(BlueprintCallable)
		void SetPlayerLocation();//死亡触发事件

	UFUNCTION(BlueprintCallable)
		void SetStartPosition(FVector Location);//复活点更新函数

	UFUNCTION(BlueprintCallable)
		void SetPlayerInput(bool isInput);

};
