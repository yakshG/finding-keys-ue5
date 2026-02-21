#include "WinArea.h"
#include "MultiplayerCoOpCharacter.h"

AWinArea::AWinArea()
{
 	PrimaryActorTick.bCanEverTick = true;

	Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Win Area"));
	SetRootComponent(Area);

	bReplicates = true;

	WinCondition = false;

}

void AWinArea::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWinArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (!WinCondition)
		{
			TArray<AActor*> OverlapActors;
			Area->GetOverlappingActors(OverlapActors, AMultiplayerCoOpCharacter::StaticClass());

			WinCondition = (OverlapActors.Num() == 2);

			if (WinCondition)
			{
				UE_LOG(LogTemp, Warning, TEXT("win"));
				MulticastRPCWin();
			}		
		}
	}
}

void AWinArea::MulticastRPCWin_Implementation()
{
	OnWin.Broadcast();
}

