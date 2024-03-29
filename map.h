#ifndef map_h
#define map_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

class Map {
  public:
    Map (const char * = 0);
    ~Map ();

    void Draw () const;
  private:
    size_t width, height;
    int cx, cy;
    float windowWidth, windowHeight;
    char **map;
    ALLEGRO_BITMAP *land, *water;
    ALLEGRO_BITMAP *border[8];
};

#endif
