// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class KDT_UE_JSONSTUDY_API CSVLoader
{
public:
	CSVLoader();
	~CSVLoader();

	template<typename T>
	static TArray<T> CSVToData(FString filename)
	{
		// csv ���� ��� �����
		FString path = FPaths::ProjectDir() + TEXT("CSV/") + filename;
		UE_LOG(LogTemp, Warning, TEXT("file path : %s"), *path);

		// ��� ���� ���� ����
		TArray<T> infos;

		// ���� ���� ���� ������ �Լ��� ������
		if (FPaths::FileExists(path) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("file not exist : %s"), *path);
			return infos;
		}

		// csv ���� �о� ����
		FString fileContent;
		if (FFileHelper::LoadFileToString(fileContent, *path))
		{
			UE_LOG(LogTemp, Warning, TEXT("file content : %s"), *fileContent);
			// ���� ���� ������
			TArray<FString> rows;
			fileContent.ParseIntoArrayLines(rows);

			// ���� �̸� ������
			TArray<FString> variableNames;
			rows[0].ParseIntoArray(variableNames, TEXT(","));
			for (int32 i = 0; i < variableNames.Num(); i++)
				variableNames[i].RemoveSpacesInline();

			// ������ ������

			for (int32 i = 1; i < rows.Num(); i++)
			{
				// ���� , �������� ������
				TArray<FString> values;
				rows[i].ParseIntoArray(values, TEXT(","));
				if (values.Num() != variableNames.Num())
				{
					UE_LOG(LogTemp, Error, TEXT("value contain , %d"), i);
					continue;
				}

				// ���� ���� �ڷ����� �°� ��������
				T info;
				
				// T �� �ڷ����� � ������ �Ǿ��ִ��� 
				UScriptStruct* p = T::StaticStruct();

				for (int32 j = 0; j < variableNames.Num(); j++)
				{
					// variableNames[j] �̸����� �Ǿ��ִ� ������ ����
					FProperty* property = p->FindPropertyByName(*variableNames[j]);

					if (property == nullptr)
					{
						UE_LOG(LogTemp, Error, TEXT("proprety is null : %s"), *variableNames[j]);
						continue;
					}

					if (property->IsA<FStrProperty>())
					{
						FString* valuePtr = property->ContainerPtrToValuePtr<FString>(&info);
						*valuePtr = values[j];
					}
					else if (property->IsA<FIntProperty>())
					{
						int32* valuePtr = property->ContainerPtrToValuePtr<int32>(&info);
						*valuePtr = FCString::Atoi(*values[j]);
					}
					else if (property->IsA<FBoolProperty>())
					{
						bool* valuePtr = property->ContainerPtrToValuePtr<bool>(&info);
						*valuePtr = values[j].ToBool();
					}
					else if (property->IsA<FFloatProperty>())
					{
						float* valuePtr = property->ContainerPtrToValuePtr<float>(&info);
						*valuePtr = FCString::Atof(*values[j]);
					}
				}

				// ���� �ϳ� �߰�
				infos.Add(info);
			}
		}
		// ��� ���� ��ȯ
		return infos;
	}

	static TArray<struct FStudentInfo> CSVToData(FString filename);
};
