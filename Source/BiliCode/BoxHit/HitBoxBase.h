// Fill out your copyright notice in the Description page of Project Settings.
/*死亡触发，存档点*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" // /为正确用法
#include "HitBoxBase.generated.h"// 必须在最后

UCLASS()
class BILICODE_API AHitBoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitBoxBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)//用BOX可视化一个组件
		class UBoxComponent * HitBoxComp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION()//否则函数没有作用
		void BeginHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	//虚函数实现动态多态，在基类响应到碰撞事件时,在子类调用虚函数, 实现复活点
	virtual void OnHitSphere(AActor * sphere);//不需要定义，子类会覆盖
};
