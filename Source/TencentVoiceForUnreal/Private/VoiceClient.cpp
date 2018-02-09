// Fill out your copyright notice in the Description page of Project Settings.

#include "VoiceClient.h"

UVoiceClient* UVoiceClient::VoiceClient = nullptr;

UVoiceClient::UVoiceClient(const FObjectInitializer& ObjectInitializer) : UObject(ObjectInitializer)
{
	bRoomStatus = false;
	JoinedRoomName.Empty();
	m_voiceengine = gcloud_voice::GetVoiceEngine();
}

UVoiceClient::~UVoiceClient()
{

}

void UVoiceClient::Tick(float DeltaTime)
{
	m_voiceengine->Poll();
}

FORCEINLINE bool UVoiceClient::IsTickable() const
{
	//return bRoomStatus;
	return true;
}

FORCEINLINE TStatId UVoiceClient::GetStatId() const
{
	return TStatId();
}

UVoiceClient * UVoiceClient::GetVoiceClient()
{
	if (nullptr == VoiceClient)
	{
		VoiceClient = NewObject<UVoiceClient>();
		VoiceClient->AddToRoot();
	}
	return VoiceClient;
}

bool UVoiceClient::GetRoomStatus() const
{
	return bRoomStatus;
}

void UVoiceClient::AddJoinedRoomName(const FString & RoomName)
{
	if (JoinedRoomName.Num() == 0)
	{
		OpenMic();
		OpenSpeaker();

		SetMicVolume(1000);
		SetSpeakerVolume(0xffff);
	}

	if (!JoinedRoomName.Contains(RoomName))
	{
		JoinedRoomName.Emplace(RoomName);

		UE_LOG(TencentVoicePlugin, Display, TEXT("Joined room name added %s!"), *RoomName);
	}
}

void UVoiceClient::RemoveJoinedRoomName(const FString & RoomName)
{
	if (JoinedRoomName.Contains(RoomName))
	{
		JoinedRoomName.Remove(RoomName);

		UE_LOG(TencentVoicePlugin, Display, TEXT("Joined room name removed %s!"), *RoomName);
	}

	if (JoinedRoomName.Num() == 0)
	{
		CloseMic();
		CloseSpeaker();

		bRoomStatus = false;
	}
}

bool UVoiceClient::SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID)
{
	GCloudVoiceErrno ErrorCode;

	if (nullptr != m_voiceengine)
	{
		ErrorCode = m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*OpenID));

		if (GCloudVoiceErrno::GCLOUD_VOICE_SUCC == ErrorCode)
		{
			OutputLog.Broadcast(FString(TEXT("SetAppInfo:")) + FString::FromInt(static_cast<int32>(ErrorCode)));
			return true;
		}
		else
		{
			OutputLog.Broadcast(FString(TEXT("SetAppInfo:")) + FString::FromInt(static_cast<int32>(ErrorCode)));
			return false;
		}
	}
	OutputLog.Broadcast(FString(TEXT("SetAppInfo:m_voiceengine is nullptr!")));
	return false;
}

void UVoiceClient::InitVoiceEngine()
{
	OutputLog.Broadcast(FString(TEXT("InitEngine:")) + FString::FromInt(static_cast<int32>(m_voiceengine->Init())));
}

void UVoiceClient::SetMode(EVoiceMode VoiceMode)
{
	OutputLog.Broadcast(FString(TEXT("SetMode:")) + FString::FromInt(static_cast<int32>(m_voiceengine->SetMode(static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMode>(VoiceMode)))));
}

void UVoiceClient::SetServerInfo(const FString & ServerAddr)
{
	OutputLog.Broadcast(FString(TEXT("SetServerInfo:")) + FString::FromInt(static_cast<int32>(m_voiceengine->SetServerInfo(TCHAR_TO_ANSI(*ServerAddr)))));
}

void UVoiceClient::OnPause()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OnPause return code %d!"), static_cast<int32>(m_voiceengine->Pause()));
}

void UVoiceClient::OnResume()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OnResume return code %d!"), static_cast<int32>(m_voiceengine->Resume()));
}

bool UVoiceClient::SetNotify(UNotifyBase* NotifyInstance)
{
	//UE_LOG(TencentVoicePlugin, Display, TEXT("SetNotify return code %d!"), static_cast<int32>(m_voiceengine->SetNotify(NotifyInstance)));

	GCloudVoiceErrno ErrorCode;

	if (nullptr != NotifyInstance)
	{
		ErrorCode = m_voiceengine->SetNotify(NotifyInstance);
		if (gcloud_voice::GCLOUD_VOICE_SUCC == ErrorCode)
		{
			OutputLog.Broadcast(FString(TEXT("SetNotify:")) + FString::FromInt(static_cast<int32>(ErrorCode)));
			return true;
		}
		else
		{
			OutputLog.Broadcast(FString(TEXT("SetNotify:")) + FString::FromInt(static_cast<int32>(ErrorCode)));
			return false;
		}
	}
	OutputLog.Broadcast(FString(TEXT("SetNotify:NotifyInstance is nullptr!")));
	return false;
}

void UVoiceClient::JoinTeamRoom(const FString & RoomName, int32 msTimeout)
{
	if (JoinedRoomName.Num() == 0)
	{
		bRoomStatus = true;
	}

	if (!JoinedRoomName.Contains(RoomName))
	{
		OutputLog.Broadcast(FString(TEXT("JoinTeamRoom:")) + FString::FromInt(static_cast<int32>(m_voiceengine->JoinTeamRoom(TCHAR_TO_ANSI(*RoomName), msTimeout))));
	}
}

void UVoiceClient::JoinNationalRoom(const FString & RoomName, EVoiceMemberRole MemberRole, int32 msTimeout)
{
	if (JoinedRoomName.Num() == 0)
	{
		bRoomStatus = true;
	}

	if (!JoinedRoomName.Contains(RoomName))
	{
		OutputLog.Broadcast(FString(TEXT("JoinNationalRoom:")) + FString::FromInt(static_cast<int32>(m_voiceengine->JoinNationalRoom(TCHAR_TO_ANSI(*RoomName), static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMemberRole>(MemberRole), msTimeout))));
	}
}

bool UVoiceClient::TestMic()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("MicLevel return code %d!"), m_voiceengine->GetMicLevel(true));
	UE_LOG(TencentVoicePlugin, Display, TEXT("TestMic return code %d!"), static_cast<int32>(m_voiceengine->TestMic()));

	if (gcloud_voice::GCLOUD_VOICE_SUCC == m_voiceengine->TestMic())
	{
		return true;
	}
	return false;
}

void UVoiceClient::OpenMic()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OpenMic return code %d!"), static_cast<int32>(m_voiceengine->OpenMic()));
}

void UVoiceClient::CloseMic()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("CloseMic return code %d!"), static_cast<int32>(m_voiceengine->CloseMic()));
}

void UVoiceClient::OpenSpeaker()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("OpenSpeaker return code %d!"), static_cast<int32>(m_voiceengine->OpenSpeaker()));
}

void UVoiceClient::CloseSpeaker()
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("CloseSpeaker return code %d!"), static_cast<int32>(m_voiceengine->CloseSpeaker()));
}

bool UVoiceClient::EnableMultiRoom(bool bEnable)
{
	gcloud_voice::GCloudVoiceErrno ErrorCode = m_voiceengine->EnableMultiRoom(bEnable);

	if (gcloud_voice::GCLOUD_VOICE_SUCC == ErrorCode)
	{
		OutputLog.Broadcast(FString(TEXT("EnableMultiRoom:")) + FString::FromInt(ErrorCode));
		return true;
	}
	OutputLog.Broadcast(FString(TEXT("EnableMultiRoom:")) + FString::FromInt(ErrorCode));
	return false;
}

void UVoiceClient::SetMicVolume(int vol)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("SetMicVolume %d, return code %d!"), vol, static_cast<int32>(m_voiceengine->SetMicVolume(vol)));
}

void UVoiceClient::SetSpeakerVolume(int vol)
{
	UE_LOG(TencentVoicePlugin, Display, TEXT("SetSpeakerVolume %d, return code %d!"), vol, static_cast<int32>(m_voiceengine->SetSpeakerVolume(vol)));
}

void UVoiceClient::QuitRoom(const FString & RoomName, int32 msTimeout)
{
	if (JoinedRoomName.Contains(RoomName))
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("UVoiceClient::QuitRoom return code %d!"), static_cast<int32>(m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*RoomName), msTimeout)));
	}
}

void UVoiceClient::QuitAllRoom(int32 msTimeout)
{
	for (auto& Iterator : JoinedRoomName)
	{
		UE_LOG(TencentVoicePlugin, Display, TEXT("UVoiceClient::QuitAllRoom return code %d!"), static_cast<int32>(m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*Iterator), msTimeout)));
	}
}
