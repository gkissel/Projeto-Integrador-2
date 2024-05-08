#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DiamondSquareHUD.generated.h"

/**
 *
 */
UCLASS()
class PROJETO_API ADiamondSquareHUD : public AHUD
{
    GENERATED_BODY()

public:
    // Constructor
    ADiamondSquareHUD();

    // Function to update the HUD text
    void UpdateHUDText(const FString& NewText);

protected:
    // Reference to the HUD text item
    UPROPERTY(EditDefaultsOnly, Category = "HUD")
    class UTextRenderComponent* HUDText;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
