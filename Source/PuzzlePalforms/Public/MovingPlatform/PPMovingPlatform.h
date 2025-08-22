#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PPMovingPlatform.generated.h"

UCLASS()
class PUZZLEPALFORMS_API APPMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	APPMovingPlatform();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();
	
private:
	FVector GlobalStartLocation;
	FVector GlobalCurrentLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform", meta = (AllowPrivateAccess = "true"), Meta = (MakeEditWidget = true))
	FVector GlobalTargetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform", meta = (AllowPrivateAccess = "true"))
	float PlatformSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Moving Platform", meta = (AllowPrivateAccess = "true"))
	int32 ActiveTrigger;
	
public:
	static FORCEINLINE void Moving(const float& DeltaTime, const float& Speed, FVector& CurrentLocation, const FVector& Direction)
	{
		CurrentLocation += Speed * DeltaTime * Direction;
	}
};
