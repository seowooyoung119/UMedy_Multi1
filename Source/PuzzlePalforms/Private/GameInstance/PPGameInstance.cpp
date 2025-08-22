#include "GameInstance/PPGameInstance.h"

UPPGameInstance::UPPGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("PPGameInstance Constructor"));
}

void UPPGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("PPGameInstance Init"));
}

void UPPGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	
	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPPGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	
	Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Red, FString::Printf(TEXT("Joining : %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	
	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
	
}