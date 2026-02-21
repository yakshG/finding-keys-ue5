#include "KeyHolder.h"

AKeyHolder::AKeyHolder()
{
 	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));

	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	KeyMesh->SetupAttachment(RootComp);
	KeyMesh->SetIsReplicated(true);
	KeyMesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	KeyRotateSpeed = 100.0f;
}

void AKeyHolder::BeginPlay()
{
	Super::BeginPlay();

	KeyMesh->SetVisibility(false);
	
}

void AKeyHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		if (KeyMesh)
		{
			KeyMesh->AddRelativeRotation(FRotator(0.f, KeyRotateSpeed * DeltaTime, 0.f));
		}
		}
}

void AKeyHolder::ActivateKeyMesh()
{
	KeyMesh->SetVisibility(true);
}

