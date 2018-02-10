// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCloudVoice.h"
#include "TypeExtension.h"
#include "Runtime/Engine/Public/Tickable.h"
#include "VoiceClient.generated.h"

class UNotifyBase;

/**
 * 
 */
UCLASS()
class TENCENTVOICEFORUNREAL_API UVoiceClient : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UVoiceClient(const FObjectInitializer& ObjectInitializer);
	~UVoiceClient();

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

public:
	/**
	 * Add a room name to JoinedRoomName
	 *
	 * @param RoomName The room name need to add
	 */
	void AddJoinedRoomName(const FString& RoomName);

	/**
	 * Remove a room name from JoinedRoomName
	 *
	 * @Param RoomName The room name need to remove
	 */
	void RemoveJoinedRoomName(const FString& RoomName);

	/**
	 * Get or New a voice client instance(if not exist), singleton object.
	 *
	 * @return UVoiceClient pointer
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		static UVoiceClient* GetVoiceClient();

	/**
	 * Get this voice client status
	 *
	 * @return This voice client whether in voice room
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		bool GetRoomStatus() const;

	/**
	 * Set VoiceEngine AppInfo.
	 *
	 * @param appID your game ID from gcloud.qq.com
	 * @param appKey your game key from gcloud.qq.com
	 * @param openID player's openID from QQ or Wechat. or a unit role ID.
	 * @return if m_voiceengine is nullptr return -1, if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 SetAppInfo(const FString& appID, const FString& appKey, const FString& OpenID);

	 /**
	 * Init the voice engine.
	 *
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 InitVoiceEngine();

	/**
	* Set the notify to engine.
	*
	* @param NotifyInstance the notify
	* @return if NotifyInstance is nullptr return -1, if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 SetNotify(UNotifyBase* NotifyInstance);

	 /**
	 * Set the mode for engine.
	 *
	 * @param mode: mode to set
	 *              RealTime:    realtime mode for TeamRoom or NationalRoom
	 *              Messages:    voice message mode
	 *              Translation: speach to text mode
	 *				RSTT:		 real-time speach to text mode
	 *				HIGHQUALITY: high quality realtime voice, will cost more network traffic
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 SetMode(EVoiceMode VoiceMode);

	/**
	* enable a client join in multi rooms.
	*
	* this may cause higher bitrate
	*
	* @param bEnable ture for open and false for close
	* @return if success return 0, failed return other errno @see GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 EnableMultiRoom(bool bEnable);

	/**
	* Join in team room.
	*
	* @param RoomName the room to join, should be less than 127byte, composed by alpha.
	* @param msTimeout time for join, it is micro second. value range[5000, 60000]
	* @return if already joined this room return -1, if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 JoinTeamRoom(const FString& RoomName, int32 msTimeout);

	/**
	* Join in a national room.
	*
	* @param RoomName the room to join, should be less than 127byte, composed by alpha.
	* @param role a GCloudVoiceMemberRole value illustrate wheather can send voice data.
	* @param msTimeout time for join, it is micro second. value range[5000, 60000]
	* @return if already joined this room return -1, if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 JoinNationalRoom(const FString& RoomName, EVoiceMemberRole MemberRole, int32 msTimeout);

	/**
	* Quit the voice room(Do not distinguish team room or National room).
	*
	* @param RoomName the room to join, should be less than 127byte, composed by alpha.
	* @param msTimeout time for quit, it is micro second.value range[5000, 60000]
	* @return if had not joined the room return -1, if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 QuitRoom(const FString& RoomName, int32 msTimeout);

	 /**
	 * Set the server address, just used for foreign game,such as Korea, Europe...
	 *
	 * @param ServerAddr URL of server
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 SetServerInfo(const FString& ServerAddr);

	 /**
	 * The Application's Pause.
	 *
	 * When your app pause such as goto backend you should invoke this
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 OnPause();

	/**
	* The Application's Resume.
	*
	* When your app reuse such as come back from  backend you should invoke this
	* @return if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 OnResume();

	 /**
	 * Test wheather microphone is available
	 *
	 * @return if success return 0, means have detect micphone device,failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		int32 TestMic();

	/**
	* Get micphone's volume
	*
	* @return micphone's volume , if return value>0, means you have said something capture by micphone
	*/
	UFUNCTION(BlueprintPure, Category = "Voice Plug-in")
		int32 GetMicLevel();

	/**
	* Open player's micro phone  and begin to send player's voice data.
	*
	* @return if success return 0, failed return other errno @see GCloudVoiceErrno
	* @see : GCloudVoiceErrno
	*/
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 OpenMic();

	 /**
	 * Close players's micro phone and stop to send player's voice data.
	 *
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 CloseMic();

	 /**
	 * Open player's speaker and begin recvie voice data from the net .
	 *
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 OpenSpeaker();

	 /**
	 * Close player's speaker and stop to recive voice data from the net.
	 *
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 CloseSpeaker();

	/**
	 * Set voice client Mic volume
	 *
	 * @param vol Windows value range[0,1000].
	 * @return if success return0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 SetMicVolume(int vol);

	 /**
	 * set sepaker's volume
	 *
	 * @param vol setspeakervolume, Android & IOS, value range is 0-800, 100 means original voice volume, 50 means only 1/2 original voice volume, 200 means double original voice volume, Windows value range is 0x0-0xFFFF(65535), suggested value bigger than 0xff00, then you can hear you speaker sound
	 * @return if success return 0, failed return other errno @see GCloudVoiceErrno
	 * @see : GCloudVoiceErrno
	 */
	UFUNCTION(BlueprintCallable, Category = "Voice Plug-in")
		int32 SetSpeakerVolume(int vol);

private:
	// The UVoiceClient instance handle (singleton object)
	static UVoiceClient* VoiceClient;
	// The TencentVoiceEngine handle
	class gcloud_voice::IGCloudVoiceEngine* m_voiceengine;
	// Markup this VoiceClient whether joined voice room and tickable (default value is false)
	bool bRoomStatus;
	// This array storage the voice client has joined room name
	TArray<FString> JoinedRoomName;
};
