// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpAmmo.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
APickUpAmmo::APickUpAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Colisor = CreateDefaultSubobject<UBoxComponent>(FName("Colisor"));
	Colisor->InitBoxExtent(FVector(16.f, 32.f, 16.f));
	Colisor->SetCollisionProfileName("Trigger");
	RootComponent = Colisor;

	ObjetoDoPickup = CreateDefaultSubobject<UStaticMeshComponent>(FName("ObjetoDoPickup"));
	ObjetoDoPickup->SetRelativeLocation(FVector(0.f, 0.f, -16.f));
	ObjetoDoPickup->SetupAttachment(RootComponent);

	SomDoPickup = CreateDefaultSubobject<UAudioComponent>(FName("SomDoPickup"));
	SomDoPickup->bAutoActivate = false;
	SomDoPickup->SetupAttachment(RootComponent);

	Colisor->OnComponentBeginOverlap.AddDynamic(this, &APickUpAmmo::ColidiuComPickUp);
}

// Called when the game starts or when spawned
void APickUpAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUpAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//DrawDebugBox(GetWorld(), GetActorLocation(), FVector(16.f, 32.f, 16.f), FColor::Red, true, -1, 0, 0.15f);
}

void APickUpAmmo::ColidiuComPickUp(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("OverlappedComponent = %s "), *OverlappedComp->GetName());
		//OverlappedComp � o componente deste ator (APickUpAmmo) que sofreu overlap
		//Neste caso OverlappedComponent = Colisor
		UE_LOG(LogTemp, Warning, TEXT("OtherActor = %s "), *OtherActor->GetName());
		//OtherActor � o ator que se sobrepoe a este ator(APickUpAmmo)
		UE_LOG(LogTemp, Error, TEXT("OtherComp = %s "), *OtherComp->GetName());
		//OtherComp � o componente do outro ator e que fez overlap com este ator
		UE_LOG(LogTemp, Warning, TEXT("OtherBodyIndex = %d "), OtherBodyIndex);
		//OtherBodyIndex = O �ndice do componente que est� sendo sobreposto
		
		//Ativa o som, pois ele foi desativado
		SomDoPickup->Activate(true);
		//Indica que o som nao ir� parar caso o proprietario deste componente seja destruido
		SomDoPickup->bStopWhenOwnerDestroyed = false;
		SomDoPickup->Play(0.0f);
		Destroy();
	}
}

