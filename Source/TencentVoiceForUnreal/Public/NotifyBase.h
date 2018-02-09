// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "CoreUObject.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "VoiceClient.h"
#include "TypeExtension.h"
#include "TencentVoiceForUnreal.h"
#include "NotifyBase.generated.h"

using namespace gcloud_voice;

/**
 * 
 */
UCLASS(BlueprintType)
class TENCENTVOICEFORUNREAL_API UNotifyBase : public UObject, public IGCloudVoiceNotify
{
	GENERATED_BODY()

public:
	UNotifyBase(const FObjectInitializer& ObjectInitializer);
	virtual ~UNotifyBase();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnJoinRoom, EGCloudVoiceCompleteCode, code, FString, roomName, int32, memberID);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuitRoom, EGCloudVoiceCompleteCode, code, FString, roomName);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnMemberVoice, FString, roomName, int32, member, int32, status);

public:
	virtual void OnJoinRoom(GCloudVoiceCompleteCode code, const char *roomName, int memberID) override;
	virtual void OnStatusUpdate(GCloudVoiceCompleteCode status, const char *roomName, int memberID) override;
	virtual void OnQuitRoom(GCloudVoiceCompleteCode code, const char *roomName) override;
	virtual void OnMemberVoice(const char *roomName, unsigned int member, int status) override;
	virtual void OnUploadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID) override;
	virtual void OnDownloadFile(GCloudVoiceCompleteCode code, const char *filePath, const char *fileID) override;
	virtual void OnPlayRecordedFile(GCloudVoiceCompleteCode code, const char *filePath) override;
	virtual void OnApplyMessageKey(GCloudVoiceCompleteCode code) override;
	virtual void OnSpeechToText(GCloudVoiceCompleteCode code, const char *fileID, const char *result) override;
	virtual void OnRecording(const unsigned char* pAudioData, unsigned int nDataLength) override;
	virtual void OnStreamSpeechToText(GCloudVoiceCompleteCode code, int error, const char *result, const char *voicePath) override;
	virtual void OnRoleChanged(GCloudVoiceCompleteCode code, const char *roomName, int memberID, int role) override;

public:
	/**
	 * Get the notify instance (singleton object)
	 *
	 * @return UNotifyBase pointer
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		static UNotifyBase* GetNotifyInstance();

	//UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
	//	// New a notify instance (singleton object)
	//	static UNotifyBase* NewNotifyInstance(TSubclassOf<UNotifyBase> NotifyClass);

private:
	// The UNotifyBase instance handle (singleton object)
	static UNotifyBase* NotifyInstance;
	// The VoiceClient instance handle
	class UVoiceClient* VoiceClient;

	UPROPERTY(BlueprintAssignable, Category = "Voice Plug-in")
		FOnJoinRoom OnJoinRoomCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Voice Plug-in")
		FOnQuitRoom OnQuitRoomCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Voice Plug-in")
		FOnMemberVoice OnMemberVoiceCompleted;
};
