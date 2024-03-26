// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JsonPawn.generated.h"

USTRUCT(BlueprintType)
struct FUserInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString name;
	UPROPERTY()
	int32 age;
	UPROPERTY()
	float height;
	UPROPERTY()
	bool gender; // true : ����, false : ����
	UPROPERTY()
	TArray<FString> interests;
	UPROPERTY()
	TArray<int32> randNum;
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	int32 price;
	UPROPERTY()
	FString name;
};


USTRUCT(BlueprintType)
struct FForecastInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString baseDate;
	UPROPERTY()
	FString baseTime;
	UPROPERTY()
	FString category;
	UPROPERTY()
	int32 nx;
	UPROPERTY()
	int32 ny;
	UPROPERTY()
	FString obsrValue;
};

//
//USTRUCT(BlueprintType)
//struct FItemList
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY()
//	TArray<FForecastInfo> item;
//};
//
//USTRUCT(BlueprintType)
//struct FBody
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY()
//	FItemList items;
//	UPROPERTY()
//	FString dataType;
//};
//
//USTRUCT(BlueprintType)
//struct FForecast
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY()
//	FBody body;
//};
//
//USTRUCT(BlueprintType)
//struct FResponse
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY()
//	FForecast response;
//};




UCLASS()
class KDT_UE_JSONSTUDY_API AJsonPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AJsonPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	void DataToJsonExample();
	void JsonToDataExample();

public:
	void RequestShortTermForecast();
	void OnCompleteRequest(TSharedPtr<class IHttpRequest> Request, 
							TSharedPtr<class IHttpResponse> Response, 
							bool bConnectedSuccessfully);
};
