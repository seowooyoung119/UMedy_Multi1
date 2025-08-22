#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformTrigger.generated.h"

class APPMovingPlatform;
class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PUZZLEPALFORMS_API APlatformTrigger : public AActor
{
	GENERATED_BODY()

public:
	APlatformTrigger();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ForTrigger", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> TriggerBoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ForTrigger", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category = "ForTrigger", meta = (AllowPrivateAccess = "true"))
	TArray<TWeakObjectPtr<APPMovingPlatform>> MovingPlatforms;
	
};
