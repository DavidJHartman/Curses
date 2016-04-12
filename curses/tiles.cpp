#include <iostream>
#include "tiles.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace noise;
tiles::tiles()
{
    height=5000;
    width=5000;
    fillMap();
    makeTileMap();


}

void tiles::fillMap()
{
    tileMap.resize(2);
    for(int a=0; a<2; a++)
    {
        tileMap[a].resize(height);
        for(int b=0; b<height; b++)
    {
        tileMap[a][b].resize(width);
        for(int c=0; c<tileMap[a][b][c].size())
        {
            tileMap[a][b][c]=NULL:
        }
    }
    }
    //fills tileMap with blanks
}



void tiles::makeTileMap()
{
srand(time(NULL));
    module::Perlin preLandTerrain1;
    preLandTerrain1.SetFrequency(1);
    preLandTerrain1.SetSeed(rand());
    module::ScaleBias landTerrain1;
    landTerrain1.SetSourceModule(0,preLandTerrain1);
    landTerrain1.SetBias(-0.1);

    module::Perlin preLandTerrain2;
    preLandTerrain2.SetFrequency(2);
    preLandTerrain2.SetSeed(rand());

    module::ScaleBias landTerrain2;
    landTerrain2.SetSourceModule(0,preLandTerrain2);
    landTerrain2.SetScale(1.2);
    landTerrain2.SetBias(-0.2);

    module::RidgedMulti preOceanTerrain;
    preOceanTerrain.SetFrequency(32);

    module::ScaleBias oceanTerrain;
    oceanTerrain.SetSourceModule(0,preOceanTerrain);
    oceanTerrain.SetScale(1.2);
    oceanTerrain.SetBias(-0.2);
    //preTerrainType.SetFrequency();

    module::Select finalTerrain_;
    finalTerrain_.SetSourceModule(0,oceanTerrain);
    finalTerrain_.SetSourceModule(1,landTerrain1);
    finalTerrain_.SetControlModule(landTerrain2);
    finalTerrain_.SetBounds(-100.0,-.7);


    finalTerrain.SetSourceModule(0,finalTerrain_);
    finalTerrain.SetSourceModule(1,landTerrain2);
    finalTerrain.SetControlModule(landTerrain2);
    finalTerrain.SetBounds(-0.7,100);
    finalTerrain.SetEdgeFalloff(0.5);
    //generate ma

/*utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
  heightMapBuilder.SetSourceModule(finalTerrain);
  heightMapBuilder.SetDestNoiseMap(heightMap);
  heightMapBuilder.SetDestSize (100, 100);
  heightMapBuilder.SetBounds (0,1 , 0, 1);
*/
    double temp_height;
    for(double a=0; a<height; a++)
    {
        for(double b=0; b<width; b++)
        {
            for(int c=0; c<2; c++)
            {
              if(c==0)
              {
            tileMap[c][a][b]=NULL;

            }
            else if(c==1)
            {
                tileMap[c][a][b]=new tile();
            }
        }
            //tileMap[a][b]->elevation=finalTerrain.GetValue(tileMap[a][b]->position.x,tileMap[a][b]->position.x,.3);

           //std::cout << finalTerrain.GetValue(tileMap[a][b]->position.x,tileMap[a][b]->position.y) << std::endl;
        }
    }

 /*  heightMapBuilder.Build ();
    utils::RendererImage renderer;
  utils::Image image;
  renderer.SetSourceNoiseMap (heightMap);
  renderer.SetDestImage (image);
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
  renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
  renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
  renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
  renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
  renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
  renderer.AddGradientPoint ( 1.200, utils::Color (255,255,255,255));
  renderer.EnableLight();
  renderer.SetLightContrast(3.0);
  renderer.SetLightBrightness(2.0);
  renderer.Render ();
   utils::WriterBMP writer;
  writer.SetSourceImage (image);
  writer.SetDestFilename ("tutorial.bmp");
  writer.WriteDestFile ();
  std::cout << "Here\n";
    //sets elevations*/
}

tiles::~tiles()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap[a].size(); b++)
        {
            for(int c=0; c<2; c++)
            {
                delete tileMap[c][a][b];
            }

        }
    }
}

std::string tiles::findTileType(double elevation)
{
     if(elevation<-.2)
    {
       return "water";
    }
    else if(elevation<.2)
    {
        return "sand";
    }
    else if(elevation<.4)
    {
        return "grass";
    }
    else if(elevation<.6)
    {
        return "dirt";
    }
    else if(elevation<.8)
    {
        return "stone";
    }
    else
    {
        return "white";//snow
    }
}

   /* module::Turbulence turbulence;
    turbulence.SetSourceModule(0,turbulence);
    turbulence.SetFrequency(4.0);
    turbulence.SetPower(0.125);
*/




   // myModule.SetSeed(rand()%time(NULL));

   // module::Perlin terrainType;
   //e.SetSourceModule(0, myModule);
   // inverter.SetSourceModule(myModule);

// double perlin_map_width=2;
// double perlin_map_height=2;

