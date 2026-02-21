#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TransporterComponent.h"
#include "PressurePlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressuerPlateOnActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressuerPlateOnDeactivated);


UCLASS()
class MULTIPLAYERCOOP_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	APressurePlate();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Trigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool Activated;

	UPROPERTY(BlueprintAssignable)
	FPressuerPlateOnActivated OnActivated;

	UPROPERTY(BlueprintAssignable)
	FPressuerPlateOnDeactivated OnDeactivated;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UTransporterComponent* Transporter;
};
