// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatorPawn.h"
#include "ShapeActor.h"

// Sets default values
ACreatorPawn::ACreatorPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACreatorPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACreatorPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACreatorPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACreatorPawn::CreateCube()
{
	GetWorld()->SpawnActor<AActor>(cubeFactory);
}

void ACreatorPawn::CreateSphere()
{
	GetWorld()->SpawnActor<AActor>(sphereFactory);
}

void ACreatorPawn::CreateCone()
{
	GetWorld()->SpawnActor<AActor>(coneFactory);
}

void ACreatorPawn::CreateShape(int32 shapeIdx)
{
	FVector randLocation = GetRandLocation();
	FRotator randRotation = GetRandRotation();
	
	float randScale = FMath::RandRange(0.5f, 2.0f);

	AActor* shape = GetWorld()->SpawnActor<AActor>(shapeFactory[shapeIdx]);
	shape->SetActorLocation(randLocation);
	shape->SetActorRotation(randRotation);
	shape->SetActorScale3D(FVector(randScale));

	// ������� Shape �� AShapeActor �� ����ȯ�ϰ� allShapes �� �߰�
	AShapeActor* shapeActor = Cast<AShapeActor>(shape);
	// shapeActor->type = shapeIdx; << �̹� Blueprint ���� ���� �س���
	allShapes.Add(shapeActor);
}

FVector ACreatorPawn::GetRandLocation()
{
	//���� ��ġ ������
	float randX = FMath::RandRange(-500.0f, 500.0f);
	float randY = FMath::RandRange(-500.0f, 500.0f);
	float randZ = FMath::RandRange(-500.0f, 500.0f);

	return FVector(randX, randY, randZ);
}

FRotator ACreatorPawn::GetRandRotation()
{
	float randPicth = FMath::RandRange(0.0f, 360.0f);
	float randYaw = FMath::RandRange(0.0f, 360.0f);
	float randRoll = FMath::RandRange(0.0f, 360.0f);

	return FRotator(randPicth, randYaw, randRoll);
}

void ACreatorPawn::SaveData()
{
	// allShapes �� �ִ� AShapeActor �� ��ġ,ȸ��,ũ��,Type �� ������ Json ���� ����

	// Data -> JsonObject -> JsonString
	/*{
		"PosX" : 10.0f,
		"PosY" : 10.0f,
		"PosZ" : 10.0f,
		"Pitch" : 10.0f,
		"Yaw" : 10.0f,
		"Roll" : 10.0f,
		"Type" : 1
	}*/

	// JsonObject ������
	TSharedPtr<FJsonObject> jsonObejct = MakeShared<FJsonObject>();
	// JsonObject �� allShapes �� 0��° Actor ������(��ġ, ȸ��, ũ��, type) �� ����
	jsonObejct->SetNumberField(TEXT("PosX"), allShapes[0]->GetActorLocation().X);
	jsonObejct->SetNumberField(TEXT("PosY"), allShapes[0]->GetActorLocation().Y);
	jsonObejct->SetNumberField(TEXT("PosZ"), allShapes[0]->GetActorLocation().Z);
	jsonObejct->SetNumberField(TEXT("Picth"), allShapes[0]->GetActorRotation().Pitch);
	jsonObejct->SetNumberField(TEXT("Yaw"), allShapes[0]->GetActorRotation().Yaw);
	jsonObejct->SetNumberField(TEXT("Roll"), allShapes[0]->GetActorRotation().Roll);
	jsonObejct->SetNumberField(TEXT("Type"), allShapes[0]->type);

	// JsonObject �� String ���� ��ȯ
	FString jsonString;
	TSharedRef<TJsonWriter<>> jsonWriter = TJsonWriterFactory<>::Create(&jsonString);
	FJsonSerializer::Serialize(jsonObejct.ToSharedRef(), jsonWriter);

	UE_LOG(LogTemp, Warning, TEXT("shape : %s"), *jsonString);	

}



