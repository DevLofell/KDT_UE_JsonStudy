// Fill out your copyright notice in the Description page of Project Settings.


#include "CSVLoader.h"
#include "CSVPawn.h"

CSVLoader::CSVLoader()
{
}

CSVLoader::~CSVLoader()
{
}

TArray<FStudentInfo> CSVLoader::CSVToData(FString filename)
{
	// csv ���� ��� �����
	FString path = FPaths::ProjectDir() + TEXT("CSV/") + filename;
	UE_LOG(LogTemp, Warning, TEXT("file path : %s"), *path);

	// ��� �л����� ���� ����
	TArray<FStudentInfo> studentInfos;

	// ���� ���� ���� ������ �Լ��� ������
	if (FPaths::FileExists(path) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("file not exist : %s"), *path);
		return studentInfos;
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
			// ���� , �������� ������
			TArray<FString> values;
			rows[i].ParseIntoArray(values, TEXT(","));

			// ���� ���� �ڷ����� �°� ��������
			FStudentInfo info;
			for (int32 j = 0; j < variableNames.Num(); j++)
			{
				if (variableNames[j] == TEXT("Name"))
				{
					info.name = values[j];
				}
				else if (variableNames[j] == TEXT("Age"))
				{
					info.age = FCString::Atoi(*values[j]);
				}
				else if (variableNames[j] == TEXT("Gender"))
				{
					info.gender = values[j].ToBool();
				}
				else if (variableNames[j] == TEXT("StudentId"))
				{
					info.studentId = values[j];
				}
			}

			// �л� ���� �ϳ� �߰�
			studentInfos.Add(info);
		}
	}
	// ����л� ���� ��ȯ
	return studentInfos;
}
