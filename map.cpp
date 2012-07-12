#include "map.h"
#include <iostream>
#include <fstream>
using namespace std;

const char terrainLand  = '.';
const char terrainWater = 'w';
const float vTileSize = 48;
const float tileScale = 128.0/96.0;
const float hTileSize = tileScale*vTileSize;

Map::Map (const char * inFile) {
  windowWidth = 1280;
  windowHeight = 720;
  if (inFile == 0) {
    width  = 10;
    height = 8;
    cx = 5;
    cy = 4;
    map = new char*[width];
    for (size_t i = 0; i < width; i++)
      map[i] = new char[height];

    for (size_t i = 0; i < width; i++) {
      for (size_t j = 0; j < height; j++) {
        if ( (i < 2) || (i >= width - 2) || 
             (j < 2) || (j >= height - 2) )
          map[i][j] = terrainWater;
        else
          map[i][j] = terrainLand;
      }
    }
  } else {
    std::ifstream file(inFile);
    file >> height >> width;

    map = new char*[width];
    for (size_t i = 0; i < width; i++)
      map[i] = new char[height];

    for (size_t j = 0; j < height; j++) {
      for (size_t i = 0; i < width; i++) {
        file >> map[i][j];
      }
    }
    cx = 1+width/2;
    cy = 1+height/2;
  }

  land  = al_create_bitmap(2*hTileSize, 2*vTileSize);
  water = al_create_bitmap(2*hTileSize, 2*vTileSize);
  for (size_t i = 0; i < 8; i++) {
    border[i] = al_create_bitmap(2*hTileSize, 2*vTileSize);
  }

  ALLEGRO_BITMAP *land_sheet = al_load_bitmap("land.bmp");
  al_convert_mask_to_alpha(land_sheet, al_map_rgb(128, 128, 128));
  al_convert_mask_to_alpha(land_sheet, al_map_rgb(191, 123, 199));
  ALLEGRO_BITMAP *water_sheet = al_load_bitmap("water.bmp");
  al_convert_mask_to_alpha(water_sheet, al_map_rgb(128, 128, 128));

  al_set_target_bitmap(land);
  al_draw_bitmap_region(land_sheet, 2*4*hTileSize, 2*4*vTileSize, 2*hTileSize, 
      2*vTileSize, 0, 0, 0);
//  al_draw_line(0, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
//  al_draw_line(2*hTileSize, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
//  al_draw_line(0, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
//  al_draw_line(2*hTileSize, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
  al_set_target_bitmap(water);
  al_draw_bitmap(water_sheet, 0, 0, 0);
//  al_draw_line(0, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
//  al_draw_line(2*hTileSize, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
//  al_draw_line(0, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
//  al_draw_line(2*hTileSize, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
  al_set_target_bitmap(border[0]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*2*hTileSize, 2*7*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[2]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*3*hTileSize, 2*7*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[4]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*1*hTileSize, 2*7*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[6]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*0*hTileSize, 2*7*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[1]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*1*hTileSize, 2*8*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[3]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*0*hTileSize, 2*8*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[5]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*2*hTileSize, 2*8*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(border[7]);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_bitmap_region(land_sheet, 2*3*hTileSize, 2*8*vTileSize, 2*hTileSize,
      2*vTileSize, 0, 0, 0);
  al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
}

Map::~Map () {
  al_destroy_bitmap(land);
  al_destroy_bitmap(water);
  for (size_t i = 0; i < width; i++)
    delete []map[i];
  delete []map;
}

void Map::Draw () const {
  for (int i = 0; i < (int)width; i++) {
    for (int j = 0; j < (int)height; j++) {
      float x = windowWidth/2 + (i+j-cx-cy+1)*hTileSize;
      float y = windowHeight/2 + (j-i-cy+cx-1)*vTileSize;
      switch (map[i][j]) {
        case '.':
          al_draw_bitmap(land, x, y, 0);
          break;
        case 'w':
          al_draw_bitmap(water, x, y, 0);
          break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
          al_draw_bitmap(border[map[i][j] - '0'], x, y, 0);
          break;
        default:
          break;
      }
    }
  }
}
