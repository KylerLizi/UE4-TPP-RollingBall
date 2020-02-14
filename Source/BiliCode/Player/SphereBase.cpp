// Fill out your copyright notice in the Description page of Project Settings.

#include "SphereBase.h"
#include "Components/StaticMeshComponent.h"//Mesh头文件
#include "GameFramework/SpringArmComponent.h"//摄像机手臂头文件
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InputComponent.h"//输入按键绑定头文件
#include "Engine.h"

// Sets default values
ASphereBase::ASphereBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsInput = true;
	SphereSpeed = 300.0f;
	SpeedMin = SphereSpeed;
	SpeedMax = 500.0f;
	ZoomValue = 0.5f;

	//创建组件
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SphereMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereBaseComp"));
	CameraArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArmComp"));
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	//组件关系
	SphereMeshComp->SetupAttachment(RootComp);
	CameraArmComp->SetupAttachment(RootComp);
	CameraComp->SetupAttachment(CameraArmComp);

	//设置参数
	//CameraArmComp->TargetArmLength = 1000.0f;
	CameraArmComp->bEnableCameraLag = false;
	//CameraArmComp->CameraLagSpeed = 6.0f;
	
	//设置物理效果为真
	SphereMeshComp->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ASphereBase::BeginPlay()
{
	Super::BeginPlay();
	//SphereBeginLocation = SphereMeshComp->GetComponentLocation();//获得初始小球位置
}

// Called every frame
void ASphereBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red,SphereMeshComp->CurrentTag->t);//窗口显示调试信息

	if (!AngularVector.IsZero())
	{
		FVector NewVector = FVector(0, 0, 0);
		
		NewVector += AngularVector.X  * CameraArmComp->GetForwardVector() * SphereSpeed;
		NewVector += AngularVector.Y  * CameraArmComp->GetRightVector() * SphereSpeed;
		
		SphereMeshComp->SetPhysicsAngularVelocity(NewVector);//小球向一个向量方向旋转移动
	}
	

	{//相机臂左右旋转（相机臂与小球是兄弟关系
		FRotator LRRotation = CameraArmComp->GetComponentRotation();
		//LRCameraRotation.Yaw = FMath::Clamp(LRCameraRotation.Yaw + CameraInput.X, -80.0f, 80.0f);//控制旋转范围
		// *** Root Actor的旋转 会改变 -80 —— 80的角度
		LRRotation.Yaw += CameraInput.X;
		CameraArmComp->SetWorldRotation(LRRotation);
	}

	{//相机臂跟随小球
		
		FVector NewLocation = SphereMeshComp->GetComponentLocation();// -SphereBeginLocation;//获取小球的位置变化量
		CameraArmComp->SetWorldLocation(NewLocation);
		//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Purple, NewLocation.ToString());

		/*DrawDebugLine(
			GetWorld(),
			SphereBeginLocation,
			SphereMeshComp->GetComponentLocation(),
			FColor::Red,
			false, -1, 0,
			3.
		);
		DrawDebugPoint(
			GetWorld(),
			CameraArmComp->GetComponentLocation(),
			20,  					//size
			FColor::Green,  //pink
			true,  				//persistent (never goes away)
			0.03 					//point leaves a trail on moving object
		);*/
	}

	 //相机臂上下旋转
	{
		FRotator UDRotation = CameraArmComp->GetComponentRotation();
		UDRotation.Pitch = FMath::Clamp(UDRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);//控制旋转范围
		CameraArmComp->SetWorldRotation(UDRotation);
	}//

	{//相机缩放
		ZoomValue = FMath::Clamp<float>(ZoomValue, 0.0f, 1.0f);
		//基于ZoomFActor来混合相机的视域和弹簧臂的长度
		CameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomValue);
		CameraArmComp->TargetArmLength = FMath::Lerp<float>(1500.0f, 500.0f, ZoomValue);//
	}

	{//跳跃
		if (LinearVector != FVector(0, 0, 0))
		{
			SphereMeshComp->AddForce(LinearVector);
		}
	}
}

// Called to bind functionality to input
void ASphereBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)//pawn不同于actor的地方,用于绑定按键
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASphereBase::MoveForward);//绑定 前后移动映射 的函数
	PlayerInputComponent->BindAxis("MoveRight", this, &ASphereBase::MoveRight);//绑定左右
	PlayerInputComponent->BindAction("MoveQuick", IE_Pressed, this, &ASphereBase::MoveQuick);//不同Axis在于区别在于包含按下/抬起调用
	PlayerInputComponent->BindAction("MoveQuick", IE_Released, this, &ASphereBase::MoveNormal);
	PlayerInputComponent->BindAxis("CameraYaw", this, &ASphereBase::YawCamera);
	PlayerInputComponent->BindAxis("CameraPitch", this, &ASphereBase::PitchCamera);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASphereBase::StartJump);//绑定跳跃
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ASphereBase::StopJump);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ASphereBase::ZoomIn);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &ASphereBase::ZoomStop);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ASphereBase::ZoomOut);
	PlayerInputComponent->BindAction("ZoomIn", IE_Released, this, &ASphereBase::ZoomStop);
}

//前后左右
void ASphereBase::MoveForward(float AxisValue)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::SanitizeFloat(val));//窗口显示调用信息
	if (IsInput)
	{
#ifdef WORLD_DIRECTION
		AngularVector.Y = SphereSpeed * AxisValue;//①
#else
		AngularVector.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f); //②③
#endif
	}
}

void ASphereBase::MoveRight(float AxisValue)
{
	if (IsInput)
	{
		AngularVector.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
	}
}

void ASphereBase::MoveQuick()//按下Shift或空格增加移速
{
	SphereSpeed = SpeedMax;
}

void ASphereBase::MoveNormal()
{
	SphereSpeed = SpeedMin;
}
//相机旋转
void ASphereBase::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void ASphereBase::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}
//跳跃
void ASphereBase::StartJump()
{
	LinearVector.Z = 1000.0f;
	//bPressedJump = true;  Character类下
}

void ASphereBase::StopJump()
{
	LinearVector.Z = 0.f;
}

void ASphereBase::ZoomIn()
{
	ZoomValue += 0.1f;
}

void ASphereBase::ZoomStop()
{
}

void ASphereBase::ZoomOut()
{
	ZoomValue -= 0.1f;
}
