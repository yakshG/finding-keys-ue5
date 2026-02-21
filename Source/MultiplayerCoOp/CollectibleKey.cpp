#include "CollectibleKey.h"
#include "Net/UnrealNetwork.h"
#include "MultiplayerCoOpCharacter.h"

ACollectibleKey::ACollectibleKey()
{
 	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	RotateSpeed = 100.0f;

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(RootComp);

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));
	Capsule->SetupAttachment(RootComp);
	Capsule->SetIsReplicated(true);
	Capsule->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Capsule->SetCapsuleHalfHeight(150.0f);
	Capsule->SetCapsuleRadius(100.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComp);
	Mesh->SetIsReplicated(true);
	Mesh->SetCollisionProfileName(FName("OverlapAllDynamic"));

	CollectAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Collect Audio"));
	CollectAudio->SetupAttachment(RootComp);
	CollectAudio->SetAutoActivate(false);

}

void ACollectibleKey::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACollectibleKey, IsCollected);

}

void ACollectibleKey::OnRep_IsCollected()
{
	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("onrep_collected - server."));

		if (IsCollected)
		{
			OnCollected.Broadcast();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("onrep_collected - client."));
	}

	Mesh->SetVisibility(!IsCollected);
	CollectAudio->Play();

	if (IsCollected && KeyHolderRef)
	{
		KeyHolderRef->ActivateKeyMesh();
	}
}

void ACollectibleKey::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectibleKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{

		Mesh->AddRelativeRotation(FRotator(0.f, RotateSpeed * DeltaTime, 0.f));

		TArray<AActor*> OverlapActors;
		Capsule->GetOverlappingActors(OverlapActors, AMultiplayerCoOpCharacter::StaticClass());

		if (!OverlapActors.IsEmpty())
		{

			if (!IsCollected)
			{
				IsCollected = true;
				OnRep_IsCollected();
				return;
			}
		}
	}

}

