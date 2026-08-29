#include "MovableActor.h"

AMovableActor::AMovableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	Point1 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow 1"));
	Point1->SetupAttachment(RootComp);
	Point1->SetRelativeLocation(FVector(0.f, 0.f, 0.f));

	Point2 = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow 2"));
	Point2->SetupAttachment(RootComp);
	Point2->SetRelativeLocation(FVector(0.f, 0.f, 300.0f));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);

	Transporter = CreateDefaultSubobject<UTransporterComponent>(TEXT("Transporter"));

}

void AMovableActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (Transporter)
	{
		FVector StartPoint = Point1->GetComponentLocation();
		FVector EndPoint = Point2->GetComponentLocation();

		Transporter->SetPoints(StartPoint, EndPoint);
	}
}

void AMovableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

