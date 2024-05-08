#include "DiamondSquareHUD.h"
#include "Components/TextRenderComponent.h"

ADiamondSquareHUD::ADiamondSquareHUD()
{
    // Create a text render component
    HUDText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HUDText"));
    HUDText->SetHorizontalAlignment(EHTA_Center);
    HUDText->SetVerticalAlignment(EVRTA_TextCenter);
    HUDText->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    HUDText->SetText(FText::FromString(TEXT("HUD Text")));
    HUDText->SetupAttachment(RootComponent);
}

void ADiamondSquareHUD::BeginPlay()
{
    Super::BeginPlay();
}

void ADiamondSquareHUD::UpdateHUDText(const FString& NewText)
{
    HUDText->SetText(FText::FromString(NewText));
}
