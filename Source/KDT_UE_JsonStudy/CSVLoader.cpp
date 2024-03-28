// Fill out your copyright notice in the Description page of Project Settings.


#include "CSVLoader.h"

CSVLoader::CSVLoader()
{
}

CSVLoader::~CSVLoader()
{
}

void CSVLoader::CSVToData(FString filename)
{
	// csv ���� ��� �����
	FString path = FPaths::ProjectDir() + TEXT("CSV/") + filename;
	UE_LOG(LogTemp, Warning, TEXT("file path : %s"), *path);

	// ���� ���� ���� ������ �Լ��� ������
	if (FPaths::FileExists(path) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("file not exist : %s"), *path);
		return;
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

		// ������ ������
		for (int32 i = 1; i < rows.Num(); i++)
		{
			TArray<FString> values;
			rows[i].ParseIntoArray(values, TEXT(","));
		}
	}
}
