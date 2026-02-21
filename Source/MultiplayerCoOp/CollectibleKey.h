#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "KeyHolder.h"
#include "CollectibleKey.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCollectibleKeyOnCollected);

UCLASS()
class MULTIPLAYERCOOP_API ACollectibleKey : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectibleKey();
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRep_IsCollected();


protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(ReplicatedUsing = OnRep_IsCollected, BlueprintReadWrite, VisibleAnywhere)
	bool IsCollected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RotateSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAudioComponent* CollectAudio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AKeyHolder* KeyHolderRef;

	FCollectibleKeyOnCollected OnCollected;

};
