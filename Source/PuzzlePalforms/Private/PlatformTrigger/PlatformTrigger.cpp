#include "PlatformTrigger/PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "MovingPlatform/PPMovingPlatform.h"

APlatformTrigger::APlatformTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	
	TriggerBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBoxComponent"));
	check(TriggerBoxComponent);
	SetRootComponent(TriggerBoxComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	check(StaticMeshComponent);
	StaticMeshComponent->SetupAttachment(TriggerBoxComponent);

	TriggerBoxComponent->SetCollisionObjectType(ECC_WorldDynamic);
	TriggerBoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	TriggerBoxComponent->IgnoreActorWhenMoving(this, true);
}

void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true); 		// 이 액터의 레플리케이트 허용
	SetReplicateMovement(true); // 이 액터의 움직임 레플리케이트 허용
	
	if(HasAuthority())
	{
		TriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerEnter);
		TriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::OnTriggerExit);
	}
}

void APlatformTrigger::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(HasAuthority())
	{
		for (int i = 0; i < MovingPlatforms.Num(); ++i)
		{
			MovingPlatforms[i] = nullptr;
		}
		MovingPlatforms.Empty();
	}
	
	Super::EndPlay(EndPlayReason);
}

void APlatformTrigger::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (false == HasAuthority() || nullptr == OtherActor || this == OtherActor) return;
	
	if (true == HasAuthority() && OtherActor->IsA<ACharacter>())
	{
		for (int i = 0; i < MovingPlatforms.Num(); ++i)
		{
			MovingPlatforms[i]->AddActiveTrigger();
		}
	}
	
}

void APlatformTrigger::OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (false == HasAuthority() || nullptr == OtherActor || this == OtherActor) return;
	
	if (true == HasAuthority() && OtherActor->IsA<ACharacter>())
	{
		for (int i = 0; i < MovingPlatforms.Num(); ++i)
		{
			MovingPlatforms[i]->RemoveActiveTrigger();
		}
	}
}

