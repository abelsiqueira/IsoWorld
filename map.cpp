#include "map.h"
#include <iostream>
using namespace std;

const char terrainLand  = '.';
const char terrainWater = 'w';
const float vTileSize = 48;
const float tileScale = 128.0/96.0;
const float hTileSize = tileScale*vTileSize;

Map::Map () {
  width  = 10;
  height = 8;
  cx = 5;
  cy = 4;
  windowWidth = 1280;
  windowHeight = 720;
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

  land  = al_create_bitmap(2*hTileSize, 2*vTileSize);
  water = al_create_bitmap(2*hTileSize, 2*vTileSize);

  ALLEGRO_BITMAP *land_sheet = al_load_bitmap("land.bmp");
  al_convert_mask_to_alpha(land_sheet, al_map_rgb(128, 128, 128));
  ALLEGRO_BITMAP *water_sheet = al_load_bitmap("water.bmp");
  al_convert_mask_to_alpha(water_sheet, al_map_rgb(128, 128, 128));

  al_set_target_bitmap(land);
  al_draw_bitmap_region(land_sheet, 2*4*hTileSize, 2*4*vTileSize, 2*hTileSize, 
      2*vTileSize, 0, 0, 0);
  al_draw_line(0, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
  al_draw_line(2*hTileSize, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
  al_draw_line(0, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
  al_draw_line(2*hTileSize, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
  al_set_target_bitmap(water);
  al_draw_bitmap(water_sheet, 0, 0, 0);
  al_draw_line(0, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
  al_draw_line(2*hTileSize, vTileSize, hTileSize, 0, al_map_rgb(0,0,0), 1);
  al_draw_line(0, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
  al_draw_line(2*hTileSize, vTileSize, hTileSize, 2*vTileSize, al_map_rgb(0,0,0), 1);
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
      float y = windowHeight/2 + (i-j-cx+cy-1)*vTileSize;
      switch (map[i][j]) {
        case '.':
          al_draw_bitmap(land, x, y, 0);
          break;
        case 'w':
          al_draw_bitmap(water, x, y, 0);
          break;
      }
    }
  }
}
