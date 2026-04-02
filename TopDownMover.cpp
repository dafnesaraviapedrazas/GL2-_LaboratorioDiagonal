#include "TopDownMover.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ATopDownMover::ATopDownMover()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoReceiveInput = EAutoReceiveInput::Player0;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
    }

    Velocity = 400.0f;
    MoveDirection = EMoveDirection::Right;
    bIsMoving = false;
}

void ATopDownMover::BeginPlay()
{
    Super::BeginPlay();
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC) EnableInput(PC);
}

void ATopDownMover::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsMoving)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector MovementStep = ManejarDireccionDiagonal(MoveDirection, DeltaTime);
        CurrentLocation += MovementStep;
        SetActorLocation(CurrentLocation);
    }
}

FVector ATopDownMover::ManejarDireccionDiagonal(EMoveDirection Direccion, float DeltaTime)
{
    FVector MovementStep = FVector::ZeroVector;

    switch (Direccion)
    {
        case EMoveDirection::Up:         MovementStep.X = 1.0f;  break;
        case EMoveDirection::Down:       MovementStep.X = -1.0f; break;
        case EMoveDirection::Right:      MovementStep.Y = 1.0f;  break;
        case EMoveDirection::Left:       MovementStep.Y = -1.0f; break;
        case EMoveDirection::UpRight:    MovementStep = FVector(0.707f, 0.707f, 0.0f);   break;
        case EMoveDirection::UpLeft:     MovementStep = FVector(0.707f, -0.707f, 0.0f);  break;
        case EMoveDirection::DownRight:  MovementStep = FVector(-0.707f, 0.707f, 0.0f);  break;
        case EMoveDirection::DownLeft:   MovementStep = FVector(-0.707f, -0.707f, 0.0f); break;
    }

    return MovementStep * Velocity * DeltaTime;
}

void ATopDownMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("ToggleMove", IE_Pressed, this, &ATopDownMover::ToggleMovement).bConsumeInput = false;
}

void ATopDownMover::ToggleMovement()
{
    bIsMoving = !bIsMoving;
}
