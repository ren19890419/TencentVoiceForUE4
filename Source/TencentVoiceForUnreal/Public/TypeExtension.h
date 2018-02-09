// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EVoiceMemberRole : uint8
{
	/* member who can open microphone and say */
	Anchor = 1,
	/* member who can only hear anchor's voice */
	Audience,
};

UENUM(BlueprintType)
enum class EVoiceMode : uint8
{
	/* realtime mode for TeamRoom or NationalRoom */
	RealTime = 0,
	/* voice message mode */
	Messages,
	/* speach to text mode */
	Translation,
	/* real-time speach to text mode */
	RSTT,
	/* high quality realtime voice, will cost more network traffic */
	HIGHQUALITY = 4,
};

UENUM(BlueprintType)
enum class EGCloudVoiceCompleteCode : uint8
{
	GV_ON_JOINROOM_SUCC = 1,	//join room succ
	GV_ON_JOINROOM_TIMEOUT,  //join room timeout
	GV_ON_JOINROOM_SVR_ERR,  //communication with svr occur some err, such as err data recv from svr
	GV_ON_JOINROOM_UNKNOWN, //reserved, our internal unknow err

	GV_ON_NET_ERR,  //net err,may be can't connect to network

	GV_ON_QUITROOM_SUCC, //quitroom succ, if you have join room succ first, quit room will alway return succ

	GV_ON_MESSAGE_KEY_APPLIED_SUCC,  //apply message authkey succ
	GV_ON_MESSAGE_KEY_APPLIED_TIMEOUT,		//apply message authkey timeout
	GV_ON_MESSAGE_KEY_APPLIED_SVR_ERR,  //communication with svr occur some err, such as err data recv from svr
	GV_ON_MESSAGE_KEY_APPLIED_UNKNOWN,  //reserved,  our internal unknow err

	GV_ON_UPLOAD_RECORD_DONE,  //upload record file succ
	GV_ON_UPLOAD_RECORD_ERROR,  //upload record file occur error
	GV_ON_DOWNLOAD_RECORD_DONE,	//download record file succ
	GV_ON_DOWNLOAD_RECORD_ERROR,	//download record file occur error

	GV_ON_STT_SUCC, // speech to text successful
	GV_ON_STT_TIMEOUT, // speech to text with timeout
	GV_ON_STT_APIERR, // server's error

	GV_ON_RSTT_SUCC, // speech to text successful
	GV_ON_RSTT_TIMEOUT, // speech to text with timeout
	GV_ON_RSTT_APIERR, // server's error

	GV_ON_PLAYFILE_DONE,  //the record file played end

	GV_ON_ROOM_OFFLINE, // Dropped from the room
	GV_ON_UNKNOWN,
	GV_ON_ROLE_SUCC,    // Change Role Success
	GV_ON_ROLE_TIMEOUT, // Change Role with tiemout
	GV_ON_ROLE_MAX_AHCHOR, // To much Anchor
	GV_ON_ROLE_NO_CHANGE, // The same role
	GV_ON_ROLE_SVR_ERROR, // server's error

	GV_ON_RSTT_RETRY, // need retry stt
};