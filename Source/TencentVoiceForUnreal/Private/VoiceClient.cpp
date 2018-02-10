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
		JoinedRoomName.Add(RoomName);
	}
}

void UVoiceClient::RemoveJoinedRoomName(const FString & RoomName)
{
	if (JoinedRoomName.Contains(RoomName))
	{
		JoinedRoomName.Remove(RoomName);
	}

	if (JoinedRoomName.Num() == 0)
	{
		CloseMic();
		CloseSpeaker();

		JoinedRoomName.Empty();

		bRoomStatus = false;
	}
}

int32 UVoiceClient::SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID)
{
	int32 ErrorCode;

	if (nullptr != m_voiceengine)
	{
		ErrorCode = static_cast<int32>(m_voiceengine->SetAppInfo(TCHAR_TO_ANSI(*appID), TCHAR_TO_ANSI(*appKey), TCHAR_TO_ANSI(*OpenID)));
		return ErrorCode;
	}

	ErrorCode = -1;
	return ErrorCode;
}

int32 UVoiceClient::InitVoiceEngine()
{
	return static_cast<int32>(m_voiceengine->Init());
}

int32 UVoiceClient::SetNotify(UNotifyBase* NotifyInstance)
{
	int32 ErrorCode;

	if (nullptr != NotifyInstance)
	{
		ErrorCode = static_cast<int32>(m_voiceengine->SetNotify(NotifyInstance));
		return ErrorCode;
	}
	ErrorCode = -1;
	return ErrorCode;
}

int32 UVoiceClient::SetMode(EVoiceMode VoiceMode)
{
	return static_cast<int32>(m_voiceengine->SetMode(static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMode>(VoiceMode)));
}

int32 UVoiceClient::EnableMultiRoom(bool bEnable)
{
	return static_cast<int32>(m_voiceengine->EnableMultiRoom(bEnable));
}

int32 UVoiceClient::JoinTeamRoom(const FString & RoomName, int32 msTimeout)
{
	if (JoinedRoomName.Num() == 0)
	{
		bRoomStatus = true;
	}

	if (!JoinedRoomName.Contains(RoomName))
	{
		return static_cast<int32>(m_voiceengine->JoinTeamRoom(TCHAR_TO_ANSI(*RoomName), msTimeout));
	}
	return -1;
}

int32 UVoiceClient::JoinNationalRoom(const FString & RoomName, EVoiceMemberRole MemberRole, int32 msTimeout)
{
	if (JoinedRoomName.Num() == 0)
	{
		bRoomStatus = true;
	}

	if (!JoinedRoomName.Contains(RoomName))
	{
		return static_cast<int32>(m_voiceengine->JoinNationalRoom(TCHAR_TO_ANSI(*RoomName), static_cast<gcloud_voice::IGCloudVoiceEngine::GCloudVoiceMemberRole>(MemberRole), msTimeout));
	}
	return -1;
}

int32 UVoiceClient::QuitRoom(const FString & RoomName, int32 msTimeout)
{
	if (JoinedRoomName.Contains(RoomName))
	{
		return static_cast<int32>(m_voiceengine->QuitRoom(TCHAR_TO_ANSI(*RoomName), msTimeout));
	}
	return -1;
}

int32 UVoiceClient::SetServerInfo(const FString & ServerAddr)
{
	return static_cast<int32>(m_voiceengine->SetServerInfo(TCHAR_TO_ANSI(*ServerAddr)));
}

int32 UVoiceClient::OnPause()
{
	return static_cast<int32>(m_voiceengine->Pause());
}

int32 UVoiceClient::OnResume()
{
	return static_cast<int32>(m_voiceengine->Resume());
}

int32 UVoiceClient::TestMic()
{
	return static_cast<int32>(m_voiceengine->TestMic());
}

int32 UVoiceClient::GetMicLevel()
{
	return static_cast<int32>(m_voiceengine->GetMicLevel(true));
}

int32 UVoiceClient::OpenMic()
{
	return static_cast<int32>(m_voiceengine->OpenMic());
}

int32 UVoiceClient::CloseMic()
{
	return static_cast<int32>(m_voiceengine->CloseMic());
}

int32 UVoiceClient::OpenSpeaker()
{
	return static_cast<int32>(m_voiceengine->OpenSpeaker());
}

int32 UVoiceClient::CloseSpeaker()
{
	return static_cast<int32>(m_voiceengine->CloseSpeaker());
}

int32 UVoiceClient::SetMicVolume(int vol)
{
	return static_cast<int32>(m_voiceengine->SetMicVolume(vol));
}

int32 UVoiceClient::SetSpeakerVolume(int vol)
{
	return static_cast<int32>(m_voiceengine->SetSpeakerVolume(vol));
}
