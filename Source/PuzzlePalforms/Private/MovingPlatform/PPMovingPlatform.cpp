#include "PuzzlePalforms/Public/MovingPlatform/PPMovingPlatform.h"

APPMovingPlatform::APPMovingPlatform()
	: GlobalStartLocation(0.f, 0.f, 0.f)
	, GlobalCurrentLocation(0.f, 0.f, 0.f)
	, GlobalTargetLocation(0.f, 0.f, 0.f)
	, PlatformSpeed(10.f)
	, ActiveTrigger(0)
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void APPMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true); 		// 이 액터의 레플리케이트 허용
	SetReplicateMovement(true); // 이 액터의 움직임 레플리케이트 허용
	
	if(HasAuthority())
	{
		GlobalCurrentLocation = GlobalStartLocation = GetActorLocation(); // 초기화 위해 존재
		GlobalTargetLocation = GetTransform().TransformPosition(GlobalTargetLocation);
	}
}

void APPMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(HasAuthority() && ActiveTrigger > 0)
	{
		// 서버일 경우 움직임
		
		GlobalCurrentLocation = GetActorLocation(); // 현재 위치 추적

		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size(); // 시작 지점으로부터 목표까지 거리 (목표 거리)
		float JourneyTravelled = (GlobalCurrentLocation - GlobalStartLocation).Size(); // 시작 지점으으로부터 현재까지 거리 (이동 거리)

		if (JourneyTravelled >= JourneyLength) // 이동 거리가 목표 거리보다 클 경우 
		{
			// 시작 지점과 목표 지점을 서로 뒤바꾼다.
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;

			// 중요 : 시작 지점과 목표 지점을 계속 바꾼다.
			// 이를 통해 From 시작 to지점목표 지점, From목표 지점 to 시작 점 이라는 거리는 항상 같음.
			// 하지만 시작 지점과 목표 지점은 바뀌었기 때문에
			// float JourneyTravelled = (GlobalCurrentLocation - GlobalStartLocation).Size(); 에서 이동 거리는 매번 바뀜.
			// 왜냐하면 swap 되면 도달한 목표 지점(GlobalTargetLocation)이 시작 지점(GlobalStartLocation)이 되기 때문.
		}
		
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Moving(DeltaTime, PlatformSpeed, GlobalCurrentLocation, Direction);
		SetActorLocation(GlobalCurrentLocation);
			
	}
	else if(!HasAuthority())
	{
		// 클라이언트일 경우 움직이지 않음
	}
}

void APPMovingPlatform::AddActiveTrigger()
{
	++ActiveTrigger;
	UE_LOG(LogTemp, Warning, TEXT("Active Trigger : %d"), ActiveTrigger);
}

void APPMovingPlatform::RemoveActiveTrigger()
{
	--ActiveTrigger;
	UE_LOG(LogTemp, Warning, TEXT("Active Trigger : %d"), ActiveTrigger);
}
