// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEsferico.h"
#include "Engine/Engine.h"

void ATriggerEsferico::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerEsferico::ColisaoDetectada);
	//Fun��o OnActorBeginOverlap � Delegate
	//Assim ela permite que outras funcoes possam ser anexadas a elas
	//Logo quando o evento de overlap ocorrer a fun��o OnActorBeginOverlap vai ser disparada
	//e todas as outras fun��es que tiverem sido anexadas a elas via delegate tbm ser�o chamadas
	//Assim estamos indicando que a fun��o ColisaoDetectada seja chamada quando a fun��o
	//OnActorBeginOverlap for chamada
	//Isso � realizado passando o endere�o da fun��o passando com &
	//this indica que queremos que este objeto Trigger seja considerado ao anexar fun��o
	//Logo � neste (this) objeto que caso o evento overlap ocorra ele vai chamar a fun��o
	//OnActorBeginOverlap que consequentemente vai chamar a fun��o ColisaoDetectada

	OnActorEndOverlap.AddDynamic(this, &ATriggerEsferico::DeixouDeColidir);
	//Anexando uma funcao a funcao OnActorEndOverlap para que ela seja acionada quando
	//esta funcao ocorrer
}

void ATriggerEsferico::ColisaoDetectada(AActor * me, AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Entrou no trigger em overlap: %s"),
		*GetActorLocation().ToString()));
	//other->Destroy();
	//Quando o player ou algum elemento tocar o trigger, ele ser� destruido e uma mensagem aparece na tela
}

void ATriggerEsferico::DeixouDeColidir(AActor* me, AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Deixou de sobrepor o trigger em: %s"),
		*GetActorLocation().ToString()));

}
