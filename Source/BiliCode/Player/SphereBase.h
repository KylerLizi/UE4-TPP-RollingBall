// Fill out your copyright notice in the Description page of Project Settings.
/*实例化组件，输入按键绑定*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SphereBase.generated.h"//必须放在include最后

UCLASS()
class BILICODE_API ASphereBase : public APawn//APawn 继承 Actor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASphereBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RootComp")
		class USceneComponent * RootComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "SphereMeshComp")
		class UStaticMeshComponent * SphereMeshComp;//class声明

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "CameraArmComp")
		class USpringArmComponent * CameraArmComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraComp")
		class UCameraComponent * CameraComp;

	FVector AngularVector;
	FVector LinearVector;
	FVector CameraInput;
	FVector SphereBeginLocation;
	float ZoomValue;
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool IsInput;//控制是否能输入按键
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SphereSpeed")
		float SphereSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SpeedMin")
		float SpeedMin;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SpeedMax")
		float SpeedMax;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)//蓝图中可调用
		void MoveForward(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float AxisValue);
	UFUNCTION(BlueprintCallable)
		void MoveQuick();
	UFUNCTION(BlueprintCallable)
		void MoveNormal();

		void PitchCamera(float AxisValue);
		void YawCamera(float AxisValue);

		void StartJump();
		void StopJump();

		void ZoomIn();
		void ZoomStop();
		void ZoomOut();
};
