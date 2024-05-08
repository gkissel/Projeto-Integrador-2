#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "PerlinTerreno.generated.h"

UCLASS()
class PROJETO_API APerlinTerreno : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APerlinTerreno();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(EditAnywhere, Category = "DiamondSquare")
	UMaterialInterface* Material;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UProceduralMeshComponent* ProceduralMesh;

	// Properties
	
	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	int32 XSize;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	int32 YSize;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	int32 ZMin;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	int32 ZMax;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	float Scale;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	float UVScale;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	float Roughness;

	UPROPERTY(EditAnywhere, Category = "Terrain Settings")
	float PerlinNoiseScale;


	// Arrays to hold generated data
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<struct FProcMeshTangent> Tangents;

	// Functions
	void CreateVertices();
	void GenerateTerrain();
	void DiamondSquareAlgorithm(TArray<TArray<float>>& grid, int x1, int y1, int x2, int y2);
	void CreateTriangles();
	void CalculateNormals();
};
