#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/MainMenuInterface.h"
#include "PPGameInstance.generated.h"

class UMainMenu;
class UUserWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPALFORMS_API UPPGameInstance : public UGameInstance, public IMainMenuInterface
{
	GENERATED_BODY()

public:
	UPPGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "PPGGameInstance")
	void LoadMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

private:
	TSubclassOf<UUserWidget> MenuClass;
	UMainMenu* MainMenu;
};
