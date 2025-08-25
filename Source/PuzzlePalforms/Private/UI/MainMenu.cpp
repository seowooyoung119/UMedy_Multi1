#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(HostButton != nullptr && OpenJoinMenuButton != nullptr)) return false;
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	OpenJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
	CancelJoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::CancelJoinMenu);
	JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	
	return true;
}

void UMainMenu::SetMainMenuInterface(IMainMenuInterface* InMainMenuInterface)
{
	this->MainMenuInterface = InMainMenuInterface;
}

void UMainMenu::Setup()
{
	this->SetIsFocusable(true);
	this->AddToViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::Teardown()
{
	this->SetIsFocusable(false);
	this->RemoveFromParent();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMainMenu::HostServer()
{
	if (MainMenuInterface != nullptr)
	{
		MainMenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MainMenuInterface != nullptr)
	{
		MainMenuInterface->Join(IPAddressField->GetText().ToString());
	}
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MainMenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MainMenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::CancelJoinMenu()
{
	if (!ensure(MainMenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;

	MainMenuSwitcher->SetActiveWidget(MainMenu);
}
