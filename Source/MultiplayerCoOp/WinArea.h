#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "WinArea.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinAreaOnWin);

UCLASS()
class MULTIPLAYERCOOP_API AWinArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AWinArea();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* Area;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool WinCondition;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCWin();

	UPROPERTY(BlueprintAssignable)
	FWinAreaOnWin OnWin;
};
