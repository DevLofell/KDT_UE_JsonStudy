// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JsonUtility.generated.h"

/**
 * 
 */
UCLASS()
class KDT_UE_JSONSTUDY_API UJsonUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	/*
	UPROPERTY()
	int32 price = 1000;
	UPROPERTY()
	FString name = "����";
	*/

public:
	template<typename T>
	static FString DataToJson(void* data)
	{
		// T �� �ڷ����� � ������ �Ǿ��ִ��� 
		UScriptStruct* p = T::StaticStruct();

		// data �� JsonObject �� ���� ����
		TSharedPtr<FJsonObject> jsonObject = MakeShared<FJsonObject>();

		// FProperty : ������ ���� ����
		for (FProperty* property = p->PropertyLink; property != nullptr; property = property->PropertyLinkNext)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Varible Name : %s"), *property->GetName());

			// ���� �̸�
			FString propertyName = property->GetName();

			// ������ ���� ����
			if (property->IsA<FStrProperty>())
			{
				// data �� propertyName ���� �Ǿ��ִ� ������ �ּҰ�
				FString* valuePtr = property->ContainerPtrToValuePtr<FString>(data);

				// propertyName ���� �Ǿ��ִ� ������ ���� �����ͼ� JsonObject �� ����
				jsonObject->SetStringField(propertyName, *valuePtr);

				//UE_LOG(LogTemp, Warning, TEXT("%s : %s"), *propertyName, **valuePtr);
			}
			else if (property->IsA<FIntProperty>())
			{
				int32* valuePtr = property->ContainerPtrToValuePtr<int32>(data);
				jsonObject->SetNumberField(propertyName, *valuePtr);
				//UE_LOG(LogTemp, Warning, TEXT("%s : %d"), *propertyName, *valuePtr);
			}
			else if (property->IsA<FFloatProperty>())
			{
				float* valuePtr = property->ContainerPtrToValuePtr<float>(data);
				jsonObject->SetNumberField(propertyName, *valuePtr);
				//UE_LOG(LogTemp, Warning, TEXT("%s : %f"), *propertyName, *valuePtr);
			}
			else if (property->IsA<FBoolProperty>())
			{
				bool* valuePtr = property->ContainerPtrToValuePtr<bool>(data);
				jsonObject->SetBoolField(propertyName, *valuePtr);
				//UE_LOG(LogTemp, Warning, TEXT("%s : %d"), *propertyName, *valuePtr);
			}
			else if (property->IsA<FArrayProperty>())
			{
				auto value = ArrayToJsonArray(property, data);
				jsonObject->SetArrayField(propertyName, value);
			}
			else if(property->IsA<FStructProperty>())
			{
				UE_LOG(LogTemp, Warning, TEXT("%s : etc..."), *propertyName);
			}
		}

		// JsonObject �� String���� ��ȯ�ؼ� ��ȯ
		return JsonToString(jsonObject);
	}

	static TArray<TSharedPtr<FJsonValue>> ArrayToJsonArray(FProperty* property, void* data)
	{
		TArray<TSharedPtr<FJsonValue>> jsonArray;

		FArrayProperty* arrayProperty = CastField<FArrayProperty>(property);
		// Array �� � Ÿ���� ��� �ִ��� ����
		FProperty* innerProperty = arrayProperty->Inner;
		// data �� Array ���� �ּҰ��� ��������
		void* arrayValuePtr = arrayProperty->ContainerPtrToValuePtr<void>(data);
		// array �� ���� �����ϱ� ���� Helper
		FScriptArrayHelper arrayHelper(arrayProperty, arrayValuePtr);

		// ���࿡ innerProperty �� String �̶��
		if (innerProperty->IsA<FStrProperty>())
		{
			SetArrayValue<FString, FJsonValueString>(arrayHelper, jsonArray);
		}
		else if (innerProperty->IsA<FIntProperty>())
		{
			SetArrayValue<int32, FJsonValueNumber>(arrayHelper, jsonArray);
		}

		return jsonArray;
	}

	template<typename T, typename U>
	static void SetArrayValue(FScriptArrayHelper& arrayHelper, TArray<TSharedPtr<FJsonValue>>& jsonArray)
	{
		for (int32 i = 0; i < arrayHelper.Num(); i++)
		{
			T value = *(T*)arrayHelper.GetRawPtr(i);
			jsonArray.Add(MakeShared<U>(value));
		}
	}

	static FString JsonToString(TSharedPtr<FJsonObject> jsonObject)
	{
		FString jsonString = "";
		auto jsonWriter = TJsonWriterFactory<>::Create(&jsonString);
		FJsonSerializer::Serialize(jsonObject.ToSharedRef(), jsonWriter);
		return jsonString;
	}
};
