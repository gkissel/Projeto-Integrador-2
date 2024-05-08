#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "DiamondSquare.generated.h"

UCLASS()
class PROJETO_API ADiamondSquare : public AActor
{
    GENERATED_BODY()

public:
    ADiamondSquare();

    UPROPERTY(EditAnywhere, Category = "Terrain Settings")
    class UUserWidget* TerrainSettingsWidget;

    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<class UUserWidget> TerrainSettingsWidgetClass;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    int XSize;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    int YSize;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    int ZMin;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    int ZMax;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    float Scale;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    float UVScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DiamondSquare")
    float Roughness;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    float PerlinNoiseScale;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    int TrianglesNumber;

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateXSize(int NewXSize);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateYSize(int NewYSize);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateZMin(int NewZMin);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateZMax(int NewZMax);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateScale(float NewScale);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateUVScale(float NewUVScale);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateRoughness(float NewRoughness);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdatePerlinNoiseScale(float NewPerlinNoiseScale);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateTrianglesNumber(int NewTrianglesNumber);

    UFUNCTION(BlueprintCallable, Category = "DiamondSquare")
    void UpdateMaterial(UMaterialInterface* NewMaterial);

protected:
    virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& Transform) override;

    UPROPERTY(EditAnywhere, Category = "DiamondSquare")
    UMaterialInterface* Material;
    void Regenerate();

private:
    UProceduralMeshComponent* ProceduralMesh;
    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector2D> UV0;
    TArray<FVector> Normals;
    TArray<struct FProcMeshTangent> Tangents;

    void CreateVertices();
    void GenerateTerrain();
    void CreateTriangles();
    void DiamondSquareAlgorithm(TArray<TArray<float>>& grid, int x1, int y1, int x2, int y2);
    void CalculateNormals();

};
