#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "KeyHolder.generated.h"

UCLASS()
class MULTIPLAYERCOOP_API AKeyHolder : public AActor
{
	GENERATED_BODY()
	
public:
	AKeyHolder();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* KeyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KeyRotateSpeed;

	UFUNCTION()
	void ActivateKeyMesh();

};
