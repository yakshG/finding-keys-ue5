#include "PressurePlate.h"

APressurePlate::APressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	Activated = false;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root Component");
	SetRootComponent(RootComp);

	Trigger = CreateDefaultSubobject<UStaticMeshComponent>("Trigger Mesh");
	Trigger->SetupAttachment(RootComp);
	Trigger->SetIsReplicated(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);

	Transporter = CreateDefaultSubobject<UTransporterComponent>(TEXT("Transporter"));
	Transporter->MoveTime = 0.25f;
	Transporter->OwnerIsPlate = true;

}

void APressurePlate::BeginPlay()
{ 
	Super::BeginPlay();

	Trigger->SetVisibility(false);
	Trigger->SetCollisionProfileName(FName("OverlapAll"));

	FVector Point1 = GetActorLocation();
	FVector Point2 = Point1 + FVector(0.f, 0.f, -10.f);

	Transporter->SetPoints(Point1, Point2);
	
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority())
		return;

	TArray<AActor*> OverlappingActors;
	AActor* TriggerActor = 0;

	Trigger->GetOverlappingActors(OverlappingActors);

	for (int AIndex = 0; AIndex < OverlappingActors.Num(); AIndex++)
	{
		AActor* A = OverlappingActors[AIndex];

		if (A->ActorHasTag("TriggerActor"))
		{
			TriggerActor = A;
			break;
		}
	}
	if (TriggerActor)
	{
		if (!Activated)
		{
			Activated = true;
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Activated."));
			OnActivated.Broadcast();
		}
	}
	else
	{
		if (Activated)
		{
			Activated = false;
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Cyan, TEXT("Deactivated."));
			OnDeactivated.Broadcast();
		}
	}


}

