// Fill out your copyright notice in the Description page of Project Settings.

#include "NotifyBase.h"

UNotifyBase* UNotifyBase::NotifyInstance = nullptr;

UNotifyBase::UNotifyBase(const FObjectInitializer& ObjectInitializer) : UObject(ObjectInitializer)
{
	VoiceClient = UVoiceClient::GetVoiceClient();
}

UNotifyBase::~UNotifyBase()
{

}

void UNotifyBase::OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID)
{
	if (gcloud_voice::GV_ON_JOINROOM_SUCC == code)
	{
		VoiceClient->AddJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}
	// If the first voice room joins failed, and then turn off voice client tick.
	else
	{
		VoiceClient->RemoveJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}

	OnJoinRoomCompleted.Broadcast(static_cast<EGCloudVoiceCompleteCode>(code), FString(ANSI_TO_TCHAR(roomName)), memberID);
}

void UNotifyBase::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{
}

void UNotifyBase::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{
	if (gcloud_voice::GV_ON_QUITROOM_SUCC == code)
	{
		VoiceClient->RemoveJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}

	OnQuitRoomCompleted.Broadcast(static_cast<EGCloudVoiceCompleteCode>(code), FString(ANSI_TO_TCHAR(roomName)));
}

void UNotifyBase::OnMemberVoice(const char *roomName, unsigned int member, int status)
{
	OnMemberVoiceCompleted.Broadcast(FString(ANSI_TO_TCHAR(roomName)), member, status);
}

void UNotifyBase::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
}

void UNotifyBase::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
}

void UNotifyBase::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{
}

void UNotifyBase::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{
}

void UNotifyBase::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{
}

void UNotifyBase::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{
}

void UNotifyBase::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{
}

void UNotifyBase::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{
}

UNotifyBase * UNotifyBase::GetNotifyInstance()
{
	if (nullptr == NotifyInstance)
	{
		NotifyInstance = NewObject<UNotifyBase>();
		NotifyInstance->AddToRoot();
	}
	return NotifyInstance;
}

//UNotifyBase * UNotifyBase::NewNotifyInstance(TSubclassOf<UNotifyBase> NotifyClass)
//{
//	if (nullptr == NotifyInstance)
//	{
//		NotifyInstance = NewObject<UNotifyBase>(NotifyClass->GetClass());
//		NotifyInstance->AddToRoot();
//	}
//	return NotifyInstance;
//}