// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxHit/HitBoxBase.h"
#include "Components/BoxComponent.h"
#include "Player/SphereBase.h"//判断碰撞是否是小球

// Sets default values
AHitBoxBase::AHitBoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBoxComp"));//初始化组件
	HitBoxComp-> OnComponentBeginOverlap.AddDynamic(this, &AHitBoxBase::BeginHit);//类似蓝图BeginOverLap
}

// Called when the game starts or when spawned
void AHitBoxBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitBoxBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//BeginOverLap蓝图中有很多参数，绑定函数需添加
//UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult
void AHitBoxBase::BeginHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//判断碰撞是否为小球
	//类型转化Cast<转换类型>(转换对象)
	if (Cast<ASphereBase>(OtherActor))
	{ 
		OnHitSphere(Cast<ASphereBase>(OtherActor));
	}
}

void AHitBoxBase::OnHitSphere(AActor * sphere)
{
}

