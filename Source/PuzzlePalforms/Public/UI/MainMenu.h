#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuInterface.h"
#include "MainMenu.generated.h"

class UEditableTextBox;
class UWidgetSwitcher;
class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPALFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMainMenuInterface(IMainMenuInterface* InMainMenuInterface);

	void Setup();

	void Teardown();
	
private:
	UPROPERTY(meta = (BindWidget))
	UButton* HostButton;

	UPROPERTY(meta = (BindWidget))
	UButton* OpenJoinMenuButton;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinServerButton;
	
	UPROPERTY(meta = (BindWidget))
	UButton* CancelJoinMenuButton;
	
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* IPAddressField;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainMenuSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* JoinMenu;
	
	UPROPERTY(meta = (BindWidget))
	UWidget* MainMenu;
	
	UFUNCTION()
	void HostServer();
	
	UFUNCTION()
	void JoinServer();

	UFUNCTION()
	void OpenJoinMenu();
	
	UFUNCTION()
	void CancelJoinMenu();
	
	IMainMenuInterface* MainMenuInterface;
	
protected:
	virtual bool Initialize() override;
};
