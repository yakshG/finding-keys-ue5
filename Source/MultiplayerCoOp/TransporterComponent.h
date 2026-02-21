#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TransporterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERCOOP_API UTransporterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTransporterComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	FVector StartPoint;
	FVector EndPoint;

	bool ArePointsSet;
	
	UPROPERTY(EditAnywhere)
	float MoveTime;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> PlateActors;

	UPROPERTY(VisibleAnywhere)
	int ActivatedTriggerCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool AllPlatesTriggered;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool OwnerIsPlate;

	UFUNCTION(BlueprintCallable)
	void SetPoints(FVector Point1, FVector Point2);

	UFUNCTION()
	void OnTriggerActivated();

	UFUNCTION()
	void OnTriggerDeactivated();

};
