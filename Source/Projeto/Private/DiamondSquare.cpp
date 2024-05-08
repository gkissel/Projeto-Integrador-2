#include "DiamondSquare.h"
#include "Math/UnrealMathUtility.h"
#include "KismetProceduralMeshLibrary.h"
#include "DiamondSquareHUD.h"

#include "Blueprint/UserWidget.h" 

ADiamondSquare::ADiamondSquare()
    : XSize(0),
    YSize(0),
    ZMin(0),
    ZMax(0),
    Scale(0),
    UVScale(0),
    Roughness(0),
    Material(nullptr),
    ProceduralMesh(nullptr),
    PerlinNoiseScale(0),
    TrianglesNumber(2),
    TerrainSettingsWidget(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;

    ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");
    RootComponent = ProceduralMesh;
}

void ADiamondSquare::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    Regenerate();
}

void ADiamondSquare::Regenerate()
{
    Vertices.Reset();
    Triangles.Reset();
    UV0.Reset();
    Normals.Reset();

    GenerateTerrain();

    CreateTriangles();
    UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UV0, Normals, Tangents);

    ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UV0, TArray<FColor>(), Tangents, true);
    ProceduralMesh->SetMaterial(0, Material);
}

void ADiamondSquare::BeginPlay()
{
    Super::BeginPlay();

    if (TerrainSettingsWidgetClass)
    {
        TerrainSettingsWidget = CreateWidget<UUserWidget>(GetWorld(), TerrainSettingsWidgetClass);
        if (TerrainSettingsWidget)
        {
            TerrainSettingsWidget->AddToViewport();
            // You might want to bind events here to handle parameter changes from the widget
            // For example:
            // TerrainSettingsWidget->BindWidgetEvent(TEXT("OnXSizeChanged"), FOnClicked::CreateUObject(this, &ADiamondSquare::OnXSizeChanged));
        }
    }
    
}

void ADiamondSquare::CreateVertices()
{
    for (int X = 0; X <= XSize; X++)
    {
        for (int Y = 0; Y <= YSize; Y++)
        {
            Vertices.Add(FVector(X * Scale, Y * Scale, 0));
            UV0.Add(FVector2D(X * UVScale, Y * UVScale));
        }
    }
}

void ADiamondSquare::GenerateTerrain()
{
    TArray<TArray<float>> heightMap;
    heightMap.Init(TArray<float>(), XSize + 1);
    for (int i = 0; i <= XSize; ++i)
    {
        heightMap[i].Init(0, YSize + 1);
    }

    DiamondSquareAlgorithm(heightMap, 0, 0, XSize, YSize);

    for (int X = 0; X <= XSize; X++)
    {
        for (int Y = 0; Y <= YSize; Y++)
        {
            float noise = FMath::PerlinNoise2D(FVector2D(X, Y) * PerlinNoiseScale) * ZMax;
            Vertices.Add(FVector(X * Scale, Y * Scale, heightMap[X][Y] + noise));
            UV0.Add(FVector2D(X * UVScale, Y * UVScale));
        }
    }
}

void ADiamondSquare::DiamondSquareAlgorithm(TArray<TArray<float>>& grid, int x1, int y1, int x2, int y2)
{
    if (x2 - x1 <= 1 || y2 - y1 <= 1)
    {
        return;
    }

    int mx = (x1 + x2) / 2;
    int my = (y1 + y2) / 2;

    float avg = (grid[x1][y1] + grid[x2][y1] + grid[x1][y2] + grid[x2][y2]) / 4.0f;
    float offset = FMath::FRandRange(-Roughness * 0.5f, Roughness * 0.5f); // Adjust roughness range

    grid[mx][my] = avg + offset;

    avg = (grid[x1][y1] + grid[x2][y1] + grid[x1][y2] + grid[x2][y2]) / 4.0f;
    offset = FMath::FRandRange(-Roughness * 0.5f, Roughness * 0.5f); // Adjust roughness range

    grid[x1][my] = (grid[x1][y1] + grid[mx][my] + grid[x1][y2]) / 3.0f + offset;
    grid[mx][y1] = (grid[x1][y1] + grid[mx][my] + grid[x2][y1]) / 3.0f + offset;
    grid[x2][my] = (grid[x2][y1] + grid[mx][my] + grid[x2][y2]) / 3.0f + offset;
    grid[mx][y2] = (grid[x1][y2] + grid[mx][my] + grid[x2][y2]) / 3.0f + offset;

    DiamondSquareAlgorithm(grid, x1, y1, mx, my);
    DiamondSquareAlgorithm(grid, mx, y1, x2, my);
    DiamondSquareAlgorithm(grid, x1, my, mx, y2);
    DiamondSquareAlgorithm(grid, mx, my, x2, y2);
}

void ADiamondSquare::CreateTriangles()
{
    int32 Vertex = 0;

    for (int X = 0; X < XSize; X++)
    {
        for (int Y = 0; Y < YSize; Y++)
        {
            Triangles.Add(Vertex);
            Triangles.Add(Vertex + 1);
            Triangles.Add(Vertex + YSize + 1);

            Triangles.Add(Vertex + 1);
            Triangles.Add(Vertex + YSize + 2);
            Triangles.Add(Vertex + YSize + 1);

            Vertex++;
        }
        Vertex++;
    }
}

void ADiamondSquare::CalculateNormals()
{
    Normals.Empty();

    for (int X = 0; X <= XSize; X++)
    {
        for (int Y = 0; Y <= YSize; Y++)
        {
            if (X < XSize && Y < YSize)
            {
                FVector p00 = Vertices[X * (YSize + 1) + Y];
                FVector p01 = Vertices[X * (YSize + 1) + Y + 1];
                FVector p10 = Vertices[(X + 1) * (YSize + 1) + Y];
                FVector p11 = Vertices[(X + 1) * (YSize + 1) + Y + 1];

                FVector e1 = p01 - p00;
                FVector e2 = p10 - p00;
                FVector e3 = p11 - p00;

                FVector normal = FVector::CrossProduct(e2, e1).GetSafeNormal();

                Normals.Add(normal);
            }
        }
    }
}

void ADiamondSquare::UpdateXSize(int NewXSize)
{
    XSize = NewXSize;
    Regenerate();
}

void ADiamondSquare::UpdateYSize(int NewYSize)
{
    YSize = NewYSize;
    Regenerate();
}

void ADiamondSquare::UpdateZMin(int NewZMin)
{
    ZMin = NewZMin;
    Regenerate();
}

void ADiamondSquare::UpdateZMax(int NewZMax)
{
    ZMax = NewZMax;
    Regenerate();
}

void ADiamondSquare::UpdateScale(float NewScale)
{
    Scale = NewScale;
    Regenerate();
}

void ADiamondSquare::UpdateUVScale(float NewUVScale)
{
    UVScale = NewUVScale;
    Regenerate();
}

void ADiamondSquare::UpdateRoughness(float NewRoughness)
{
    Roughness = NewRoughness;
    Regenerate();
}

void ADiamondSquare::UpdatePerlinNoiseScale(float NewPerlinNoiseScale)
{
    PerlinNoiseScale = NewPerlinNoiseScale;
    Regenerate();
}

void ADiamondSquare::UpdateTrianglesNumber(int NewTrianglesNumber)
{
    TrianglesNumber = NewTrianglesNumber;
    Regenerate();
}

void ADiamondSquare::UpdateMaterial(UMaterialInterface* NewMaterial)
{
    Material = NewMaterial;
    Regenerate();
}
