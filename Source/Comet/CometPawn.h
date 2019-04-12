// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CometPawn.generated.h"

UCLASS(Config=Game)
class ACometPawn : public APawn
{
	GENERATED_BODY()

public:
	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlaneMesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	class ACometPlayerController* PlayerController;
public:
	ACometPawn();

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// End AActor overrides

protected:

	virtual void BeginPlay() override;

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	// End APawn overrides

	/** Bound to the thrust axis */
	void ThrustInput(float Val);
	
	/** Bound to the vertical axis */
	void MoveUpInput(float Val);

	/** Bound to the horizontal axis */
	void MoveRightInput(float Val);

	/** Bound to the dash axis */
	void DashInput(float Val);

private:

	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration = 800;

	/** How quickly pawn can steer */
	UPROPERTY(Category=Plane, EditAnywhere)
	float YawSpeed = 90;

	UPROPERTY(Category=Plane, EditAnywhere)
	float PitchSpeed = 90;

	UPROPERTY(Category = Plane, EditAnywhere)
	float MaxPitchAngle = 85;

	/** Max forward speed */
	UPROPERTY(Category = Pitch, EditAnywhere)
	float MaxSpeed = 5000;

	/** Min forward speed */
	UPROPERTY(Category=Yaw, EditAnywhere)
	float MinSpeed = 50;

	/** How quickly forward dash speed is */
	UPROPERTY(Category = Plane, EditAnywhere)
		float DashSpeed = 200;

	/** How sensitive the comet moves sideways */
	UPROPERTY(Category = Plane, EditAnywhere)
		float PitchDashSpeed = 110;
	UPROPERTY(Category = Plane, EditAnywhere)
		float YawDashSpeed = 110;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	/*Current Dash Speed*/
	float CurrentDashSpeed;

	/*Saving original yaw and pitch speeds for the dash input*/
	float OriginalPitch;
	float OriginalYaw;
	
	/*just to test some stuff*/
	bool bIsDashing;

	/* setting the dash time and editing in blueprint*/
	UFUNCTION(BlueprintCallable)
		bool getIsDash();

public:
	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return PlaneMesh; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
