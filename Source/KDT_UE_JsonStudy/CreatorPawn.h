// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CreatorPawn.generated.h"

UCLASS()
class KDT_UE_JSONSTUDY_API ACreatorPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreatorPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// ������ ����� Actor ��Ƴ� ����
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> cubeFactory;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> sphereFactory;
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> coneFactory;

	// ������ ��� ��� ���� ����
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> shapeFactory;

	// ������ ������ ��Ƴ��� ����
	UPROPERTY(VisibleAnywhere)
	TArray<class AShapeActor*> allShapes;

public:
	// ����� ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void CreateCube();
	UFUNCTION(BlueprintCallable)
	void CreateSphere();
	UFUNCTION(BlueprintCallable)
	void CreateCone();

	UFUNCTION(BlueprintCallable)
	void CreateShape(int32 shapeIdx);
	void CreateShape(int32 shapeIdx, FVector pos, FRotator rot, FVector scale);

	FVector GetRandLocation();
	FRotator GetRandRotation();

	// ���� �Լ�
	UFUNCTION(BlueprintCallable)
	void SaveData();

	// �ҷ����� �Լ�
	UFUNCTION(BlueprintCallable)
	void LoadData();


	// Cube : 0, Sphere : 1, Cone : 2
	// 1 ��Ű ������ Cube ����
	// 2 ��Ű ������ Sphere ����
	// 3 ��Ű ������ Cone ����

	// ������ ���͸� ������ ��ġ(-10000 ~ 10000), ������ ũ�� (0.5 ~ 4), ������ ȸ��

	
};
