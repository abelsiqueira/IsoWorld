/* Copyright 2012 - Abel Soares Siqueira
 * 
 * This file is part of IsoWorld.
 * 
 * IsoWorld is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * IsoWorld is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with IsoWorld.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "map.h"

const unsigned int constFps = 1;

int main () {
  ALLEGRO_DISPLAY *display;
  ALLEGRO_EVENT_QUEUE *eventQueue;
  ALLEGRO_TIMER *timer;

  bool done = false;

  al_init();
  display = al_create_display(1280, 720);
  al_set_window_title(display, "IsoWorld");
  eventQueue = al_create_event_queue();
  timer = al_create_timer(1.0/constFps);

  al_init_primitives_addon();
  al_install_keyboard();
  al_init_image_addon();

  al_register_event_source(eventQueue, al_get_display_event_source(display));
  al_register_event_source(eventQueue, al_get_timer_event_source(timer));
  al_register_event_source(eventQueue, al_get_keyboard_event_source());

  bool redraw = false;
  enum Keys { key_up, key_down, key_left, key_right };

  Map map;

  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_start_timer(timer);
  while (!done) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(eventQueue, &ev);

    if (ev.type == ALLEGRO_EVENT_TIMER) {
      redraw = true;
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      switch (ev.keyboard.keycode) {
        case ALLEGRO_KEY_Q:
        case ALLEGRO_KEY_ESCAPE:
          done = true;
          break;
        default: 
          break;
      }
    } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
    }

    if (redraw && al_is_event_queue_empty(eventQueue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb_f(0.0, 0.0, 0.0));

      map.Draw();
      al_draw_line(0, 720/2, 1280, 720/2, al_map_rgb(255,0,0),1);
      al_draw_line(1280/2, 0, 1280/2, 720, al_map_rgb(255,0,0),1);

      al_flip_display();
    }
  }

  al_destroy_timer(timer);
  al_destroy_event_queue(eventQueue);
  al_destroy_display(display);
}
