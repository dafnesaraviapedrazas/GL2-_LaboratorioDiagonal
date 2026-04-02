#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TopDownMover.generated.h"

UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
    Up          UMETA(DisplayName = "Up"),
    Down        UMETA(DisplayName = "Down"),
    Left        UMETA(DisplayName = "Left"),
    Right       UMETA(DisplayName = "Right"),
    UpRight     UMETA(DisplayName = "Up-Right"),
    UpLeft      UMETA(DisplayName = "Up-Left"),
    DownRight   UMETA(DisplayName = "Down-Right"),
    DownLeft    UMETA(DisplayName = "Down-Left")
};

UCLASS()
class MYPROJECT1_API ATopDownMover : public APawn
{
    GENERATED_BODY()

public:
    ATopDownMover();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditAnywhere, Category = "Movement Settings")
    float Velocity;

    UPROPERTY(EditAnywhere, Category = "Movement Settings")
    EMoveDirection MoveDirection;

    UPROPERTY(EditAnywhere, Category = "Movement Settings")
    bool bIsMoving;

    FVector ManejarDireccionDiagonal(EMoveDirection Direccion, float DeltaTime);

private:
    void ToggleMovement();
};
