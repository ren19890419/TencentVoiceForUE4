# TencentVoiceForUnreal
# 虚幻引擎腾讯语音插件

## 概述
虚幻引擎腾讯与语音插件，只是整合了腾讯云语音SDK（该插件目前只整合了Win64和Win32版本），并提供了相关蓝图节点以方便使用。如果需要在打包后使用，需要将打包后的\<your project name\>/Plugins/TencentVoiceForUE4/ThirdParty/\<OSVersion\>/lib/GCloudVoice.dll复制到\<your project name\>/Binaries/\<OSVersion\>下，才能正常使用。

## 使用步骤
1.设置业务信息
![image](https://github.com/ThePupilOfTheOcean/TencentVoiceForUE4/blob/master/Images/SetAppInfo.png)
2.初始化语音引擎
调用方式：GetVoiceClient-\>InitVoiceEngine\(\)
3.设置回调类
![image](https://github.com/ThePupilOfTheOcean/TencentVoiceForUE4/blob/master/Images/SetNotify.png)
4.设置引擎模式\(目前只做了实时语音模式\)
调用方式：GetVoiceClient-\>SetMode\(\)
* 5.设置是否允许加入多个语音房间\(根据自己需要选择启用\)
调用方式：GetVoiceClient-\>EnableMultiRoom\(\)
6.加入语音房间
![image](https://github.com/ThePupilOfTheOcean/TencentVoiceForUE4/blob/master/Images/JoinRoom.png)
7.回调
![image](https://github.com/ThePupilOfTheOcean/TencentVoiceForUE4/blob/master/Images/OnJoinRoomCompleted.png)
![image](https://github.com/ThePupilOfTheOcean/TencentVoiceForUE4/blob/master/Images/OnQuitRoomCompleted.png)

这样就应该可以了。感谢您的使用！
