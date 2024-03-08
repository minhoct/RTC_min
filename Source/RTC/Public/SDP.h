// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SocketIOClientComponent.h"
#include "SDP.generated.h"


// �̵�� ������ ���� ����ü
struct MediaDescription {
	FString type; // ��: "audio", "video"
	int32 port;
	FString protocol; // ��: "RTP/AVP"
	TArray<int32> format; // Ÿ�Ե�
};

// �̵�� �Ӽ��� ���� ����ü
struct AttributeDescription {
	FString a;
};

// SDP ��ü�� ��Ÿ���� ����ü
struct SessionDescription {
	int32 v; // �������� ����, ���� 0
	FString o; // originator
	FString s; // sessionName
	FString c; // connectionInfo
	FString t; // timing
	TArray<MediaDescription> m; // mediaDescriptions �̵�� �����
	TArray<AttributeDescription> a; // attribute �̵�� �Ӽ���
	//����:https://brunch.co.kr/@linecard/141
};

// ICE Candidate�� ��Ÿ���� ����ü
struct IceCandidate
{

	FString Candidate;
	FString SdpMid;
	int32 SdpMLineIndex;
	FString Foundation;
	int32 Component;
	FString Protocol;
	uint32 Priority;
	FString Address;
	int32 Port;
	FString Type;
};



UCLASS()
class RTC_API ASDP: public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASDP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTC")
	USocketIOClientComponent* siocc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RTC")
	FSIOConnectParams SIOConnectParams;

	FString RoomName;
	TSharedPtr<FJsonObject> SelfInfo;

public:
	UFUNCTION(BlueprintCallable)
	void JoinRoom(FString roomName);

	void Offer(SessionDescription offer, FString roomName);
	void Answer(SessionDescription answer, FString roomName);
	void Candidate(IceCandidate candidate, FString roomName);
	USIOJsonValue* ConvertSessionDescriptionToSIOJsonValue(const SessionDescription& SessionDesc);
	USIOJsonValue* IceCandidateToSIOJsonValue(const IceCandidate& Candidate);
	void Offer(const SessionDescription& Offer, const FString& roomName);
	void ReceiveAnswer(const SessionDescription& Answer);

public:
	void OnConnectionFail();


};
