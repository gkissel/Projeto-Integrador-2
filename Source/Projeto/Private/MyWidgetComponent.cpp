#include "MyWidgetComponent.h"
#include "Components/TextRenderComponent.h"

UMyWidgetComponent::UMyWidgetComponent()
{
    // Set up the widget component
    SetWidgetSpace(EWidgetSpace::Screen);
    SetDrawSize(FVector2D(100, 50)); // Set the initial size of the widget
}

void UMyWidgetComponent::BeginPlay()
{
    Super::BeginPlay();

    // Create the HUD text render component
    HUDText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HUDText"));
    if (HUDText)
    {
        HUDText->SetupAttachment(this);
        HUDText->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
        HUDText->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
        HUDText->SetText(FText::FromString("Default HUD Text")); // Set default text
    }
}

void UMyWidgetComponent::UpdateHUDText(const FString& NewText)
{
    // Update the HUD text
    if (HUDText)
    {
        HUDText->SetText(FText::FromString(NewText));
    }
}
