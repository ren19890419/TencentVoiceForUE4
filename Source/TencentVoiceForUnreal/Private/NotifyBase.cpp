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
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnJoinRoom return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_JOINROOM_SUCC == code)
	{
		VoiceClient->AddJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
		VoiceClient->TestMic();
		OnJoinRoomCompleted.Broadcast(static_cast<EGCloudVoiceCompleteCode>(code), FString(ANSI_TO_TCHAR(roomName)), static_cast<int32>(memberID));
	}
	// If the first voice room joins failed, and then turn off voice client tick.
	else
	{
		VoiceClient->RemoveJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}
}

void UNotifyBase::OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnStatusUpdate return code %d!"), *(this->GetName()), static_cast<int32>(status));
}

void UNotifyBase::OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnQuitRoom return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_QUITROOM_SUCC == code)
	{
		OnQuitRoomCompleted.Broadcast(static_cast<EGCloudVoiceCompleteCode>(code), FString(ANSI_TO_TCHAR(roomName)));
		VoiceClient->RemoveJoinedRoomName(FString(ANSI_TO_TCHAR(roomName)));
	}
}

void UNotifyBase::OnMemberVoice(const char *roomName, unsigned int member, int status)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnMemberVoice report member:%d with status:%d in room:%s"), *(this->GetName()), static_cast<int32>(member), static_cast<int32>(status), *FString(ANSI_TO_TCHAR(roomName)));
	OnMemberVoiceCompleted.Broadcast(FString(ANSI_TO_TCHAR(roomName)), static_cast<int32>(member), static_cast<int32>(status));
}

void UNotifyBase::OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnUploadFile return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_UPLOAD_RECORD_DONE == code)
	{
	}
}

void UNotifyBase::OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnDownloadFile return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_DOWNLOAD_RECORD_DONE == code)
	{
	}
}

void UNotifyBase::OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnPlayRecordedFile return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_PLAYFILE_DONE == code)
	{
	}
}

void UNotifyBase::OnApplyMessageKey(GCloudVoiceCompleteCode code)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnApplyMessageKey return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_MESSAGE_KEY_APPLIED_SUCC == code)
	{
	}
}

void UNotifyBase::OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnSpeechToText return code %d!"), *(this->GetName()), static_cast<int32>(code));
}

void UNotifyBase::OnRecording(const unsigned char* pAudioData, unsigned int nDataLength)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnRecording"), *(this->GetName()));
}

void UNotifyBase::OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnStreamSpeechToText return code %d!"), *(this->GetName()), static_cast<int32>(code));
}

void UNotifyBase::OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("%s OnRoleChanged return code %d!"), *(this->GetName()), static_cast<int32>(code));

	if (gcloud_voice::GV_ON_ROLE_SUCC == code)
	{
	}
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