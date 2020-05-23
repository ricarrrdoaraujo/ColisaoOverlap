// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerEsferico.h"
#include "Engine/Engine.h"

void ATriggerEsferico::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerEsferico::ColisaoDetectada);
	//Função OnActorBeginOverlap é Delegate
	//Assim ela permite que outras funcoes possam ser anexadas a elas
	//Logo quando o evento de overlap ocorrer a função OnActorBeginOverlap vai ser disparada
	//e todas as outras funções que tiverem sido anexadas a elas via delegate tbm serão chamadas
	//Assim estamos indicando que a função ColisaoDetectada seja chamada quando a função
	//OnActorBeginOverlap for chamada
	//Isso é realizado passando o endereço da função passando com &
	//this indica que queremos que este objeto Trigger seja considerado ao anexar função
	//Logo é neste (this) objeto que caso o evento overlap ocorra ele vai chamar a função
	//OnActorBeginOverlap que consequentemente vai chamar a função ColisaoDetectada

	OnActorEndOverlap.AddDynamic(this, &ATriggerEsferico::DeixouDeColidir);
	//Anexando uma funcao a funcao OnActorEndOverlap para que ela seja acionada quando
	//esta funcao ocorrer
}

void ATriggerEsferico::ColisaoDetectada(AActor * me, AActor* other)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Entrou no trigger em overlap: %s"),
		*GetActorLocation().ToString()));
	//other->Destroy();
	//Quando o player ou algum elemento tocar o trigger, ele será destruido e uma mensagem aparece na tela
}

void ATriggerEsferico::DeixouDeColidir(AActor* me, AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Deixou de sobrepor o trigger em: %s"),
		*GetActorLocation().ToString()));

}
