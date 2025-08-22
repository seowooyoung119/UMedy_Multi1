#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PPGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPALFORMS_API UPPGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPPGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);
};
