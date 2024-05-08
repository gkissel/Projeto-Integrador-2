// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MyWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJETO_API UMyWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
    // Constructor
    UMyWidgetComponent();

    // Function to update the HUD text
    void UpdateHUDText(const FString& NewText);

protected:
    // Reference to the HUD text item
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    class UTextRenderComponent* HUDText;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
