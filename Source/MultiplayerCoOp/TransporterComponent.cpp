#include "TransporterComponent.h"
#include "PressurePlate.h"
#include "CollectibleKey.h"

UTransporterComponent::UTransporterComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);

	StartPoint = FVector::Zero();
	EndPoint = FVector::Zero();
	ArePointsSet = false;

	MoveTime = 2.0f;
	ActivatedTriggerCount = 0;

}


void UTransporterComponent::BeginPlay()
{
	Super::BeginPlay();

	if (OwnerIsPlate)
	{
		PlateActors.Add(GetOwner());
	}

	for (AActor* A : PlateActors)
	{
		APressurePlate* PlateActor = Cast<APressurePlate>(A);
		if (PlateActor)
		{
			PlateActor->OnActivated.AddDynamic(this, &UTransporterComponent::OnTriggerActivated);
			PlateActor->OnDeactivated.AddDynamic(this, &UTransporterComponent::OnTriggerDeactivated);
			continue;
		}

		ACollectibleKey* Key = Cast<ACollectibleKey>(A);
		if (Key)
		{
			Key->OnCollected.AddDynamic(this, &UTransporterComponent::OnTriggerActivated);
		}
	}


}

void UTransporterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (PlateActors.Num() > 0)
	{
		AllPlatesTriggered = (ActivatedTriggerCount >= PlateActors.Num());
		//if (AllPlatesTriggered)
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("all activated")));
	}

	AActor* Owner = GetOwner();
	if (Owner && Owner->HasAuthority() && ArePointsSet)
	{
		FVector CurrentLocation = Owner->GetActorLocation();
		float Speed = FVector::Distance(StartPoint, EndPoint) / MoveTime;

		FVector TargetLocation = AllPlatesTriggered ? EndPoint : StartPoint;

		if (!CurrentLocation.Equals(TargetLocation))
		{
			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
			Owner->SetActorLocation(NewLocation);
		}
		
	}
}

void UTransporterComponent::SetPoints(FVector Point1, FVector Point2)
{
	if (ArePointsSet)
		return;

	if (Point1.Equals(Point2))
		return;

	ArePointsSet = true;
	StartPoint = Point1;
	EndPoint = Point2;
}

void UTransporterComponent::OnTriggerActivated()
{
	ActivatedTriggerCount++;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("activated: %d"), ActivatedTriggerCount));
}

void UTransporterComponent::OnTriggerDeactivated()
{
	ActivatedTriggerCount--;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("activated: %d"), ActivatedTriggerCount));
}

