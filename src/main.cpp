#include <Arduino.h>
#include <Arduboy2.h>
#include <Tinyfont.h>
#include <Sprites.h>

#include "draw.h"
#include "images.h"

Arduboy2 arduboy;
Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

#define MAX_RINGS 50
#define RING_RADIUS 100

#define FRAME_RATE 45

#define MS_TO_FRAMES(ms) ((ms)/(1000/FRAME_RATE))
#define FRAMES_TO_MS(frame) ((frame)(1000/FRAME_RATE))


struct Ring {
  float x_offset;
  float y_offset;
  uint8_t rotation;
  uint8_t type;
} ;

uint8_t num_rings=30;
Ring rings[MAX_RINGS];

float position = 0;
float speed=0;
float rot=0;

float adj_dist(float x, float center, float dist) {
  return (x-center) * (dist*dist)/80 + center;
}

struct Pointf
{
  float x;
  float y;
  Pointf() = default;
  constexpr Pointf(float x, float y)
    : x(x), y(y)
  {
  }
};

/**
 * @brief get x,y units for rotating 0-255
 * 
 */
Pointf get_rot(float rotate) {
  float adjr = -rotate*M_PI*2/256;
  return Pointf(cos(adjr), sin(adjr));
}

Pointf get_circ_pt(Pointf center, float r, Pointf rotate) {
  return Pointf(center.x+r*rotate.x, center.y+r*rotate.y);
}


float y_adj_center(float dist_to_cam) {
  return -80/(dist_to_cam);
}

float size_adj(float dist_to_cam) {
  return 2*64/(dist_to_cam);
}

bool blink(uint16_t on_frames, uint16_t total_frames, uint16_t offset_frames=0) {
  return ((arduboy.frameCount - offset_frames) % total_frames) < on_frames;
}

void draw_arrow(float x, float d2cam1, Pointf rot1, Pointf rot2, Pointf rot3) {
  float pt_dist = 1.0f;
  Pointf xy = Pointf(x, 32+y_adj_center(d2cam1));
  Pointf xy2 = Pointf(x, 32+y_adj_center(d2cam1+pt_dist));
  float r1 = size_adj(d2cam1);
  float r2 = size_adj(d2cam1 + pt_dist);

  Pointf p1 = get_circ_pt(xy, r1, rot1);
  Pointf p2 = get_circ_pt(xy2, r2, rot2);
  Pointf p3 = get_circ_pt(xy, r1, rot3);
  arduboy.drawLine(p1.x,p1.y,p2.x,p2.y, WHITE);
  arduboy.drawLine(p3.x,p3.y,p2.x,p2.y, WHITE);
}

void draw_ring(float dist_to_cam, uint8_t offset) {
  float y = 32+y_adj_center(dist_to_cam);
  float r = size_adj(dist_to_cam);
  float x = 64;
  uint8_t dither = uint8_t(dist_to_cam/2);

  uint8_t angle = (uint8_t)(rot + rings[offset].rotation);
  switch(rings[offset].type) {
    case 0: // Start
      drawArc(x,y,r, WHITE, 0, 0);
      drawArc(x,y,r+2, WHITE, 0, 0);
      // drawArc(x,y,r, WHITE, 160+angle, 224+angle);
      // drawArc(x,y,r, WHITE, 32+angle, 96+angle);
      break;
    case 1: // open
      // if (dither<5) {
        // arduboy.drawCircle(x, y, r, color);
        drawArc(x, y, r, WHITE, 0, 0, dither);
      // }
      break;
    case 2: // 1/3
      {
        // if (dither < 5) {
          drawArc(x,y,r, WHITE, 96+angle, angle, dither);
        // }
        Pointf rot1 = get_rot(angle);
        Pointf rot2 = get_rot(96+angle);
        Pointf start = get_circ_pt(Pointf(x,y), r, rot1);
        Pointf stop = get_circ_pt(Pointf(x,y), r, rot2);
        // Pointf start2 = get_circ_pt(Pointf(x,y), r-2, rot1);
        // Pointf stop2 = get_circ_pt(Pointf(x,y), r-2, rot2);
        arduboy.drawLine(start.x, start.y, stop.x, stop.y, WHITE);
        drawArc(x,y,r, WHITE, angle, 96+angle);
        // arduboy.drawLine(start2.x, start2.y, start.x, start.y, WHITE);
        // arduboy.drawLine(start2.x, start2.y, stop2.x, stop2.y, WHITE);
        // arduboy.drawLine(stop.x, stop.y, stop2.x, stop2.y, WHITE);
      }
      break;
    case 3: // middle
      {
        uint8_t w=7;
        drawArc(x,y,r, WHITE, w+angle, 128-w+angle, dither);
        drawArc(x,y,r, WHITE, 128-w+angle, 128+w+angle);
        drawArc(x,y,r, WHITE, 128+w+angle, -w+angle, dither);
        drawArc(x,y,r, WHITE, -w+angle, w+angle);
        Pointf p1 = get_circ_pt(Pointf(x,y), r, get_rot(w+angle));
        Pointf p2 = get_circ_pt(Pointf(x,y), r, get_rot(128-w+angle));
        arduboy.drawLine(p1.x,p1.y,p2.x,p2.y, WHITE);

        p1 = get_circ_pt(Pointf(x,y), r, get_rot(128+w+angle));
        p2 = get_circ_pt(Pointf(x,y), r, get_rot(-w+angle));
        arduboy.drawLine(p1.x,p1.y,p2.x,p2.y, WHITE);
      }
      break;
    case 4: // boost
      {
        drawArc(x,y,r, WHITE, 0,0, dither);
        uint8_t w = 10;
        Pointf rot1 = get_rot(w+angle);
        Pointf rot2 = get_rot(angle);
        Pointf rot3 = get_rot(-w+angle);
        uint16_t total_ms=1000;
        uint16_t st = total_ms/7;
        if (blink(MS_TO_FRAMES(3*st), MS_TO_FRAMES(total_ms), MS_TO_FRAMES(0*st))) {
          draw_arrow(x, dist_to_cam, rot1, rot2, rot3);
        }
        if (blink(MS_TO_FRAMES(3*st), MS_TO_FRAMES(total_ms), MS_TO_FRAMES(1*st))) {
          draw_arrow(x, dist_to_cam+1, rot1, rot2, rot3);
        }
        if (blink(MS_TO_FRAMES(3*st), MS_TO_FRAMES(total_ms), MS_TO_FRAMES(2*st))) {
          draw_arrow(x, dist_to_cam+2, rot1, rot2, rot3);
        }
        if (blink(MS_TO_FRAMES(3*st), MS_TO_FRAMES(total_ms), MS_TO_FRAMES(3*st))) {
          draw_arrow(x, dist_to_cam+3, rot1, rot2, rot3);
        }
      }
      
      break;
  };
}


// void draw_ring(float dist_to_cam, uint8_t offset) {
//   float y = 32+y_adj_center(dist_to_cam);
//   float size = size_adj(dist_to_cam);
//   draw_ring(64,y,size,offset,uint8_t(dist_to_cam/2), dist_to_cam);
// }

void draw_generic_ring(float dist_to_cam) {
  drawArc(64,32+y_adj_center(dist_to_cam),size_adj(dist_to_cam), WHITE, 0, 0, uint8_t(dist_to_cam));
}

void draw_level(float position) {
  uint8_t drawn_rings=40;
  uint8_t ring_mult = 12;
  tinyfont.setCursor(1,1);
  tinyfont.println(position,2);
  tinyfont.setCursor(1,6);
  static int cpu = 0;
  if (arduboy.everyXFrames(10)) {
    cpu = arduboy.cpuLoad();
  }
  tinyfont.print(cpu);
  tinyfont.print('%');
  uint16_t current_position = (uint16_t)(position*ring_mult);
  float distance_to_cam = ((int)(position*ring_mult+1) - position*ring_mult);

  for(uint8_t ring=0; ring<drawn_rings; ring++) {
    if(distance_to_cam > .5) {
      if(current_position % ring_mult == 0) { // +1 ???
        draw_ring(distance_to_cam, current_position/ring_mult);
      } else {
        draw_generic_ring(distance_to_cam);
      }
    }

    distance_to_cam += 1;
    current_position += 1;
    if (current_position > num_rings*ring_mult) {
      current_position -= num_rings*ring_mult;
    }
  }
}




void gen_ring(uint8_t num) {
  // rings[num].x_offset = (random(100)-50)/10.0f;
  // rings[num].y_offset = (random(100)-50)/10.0f;
  rings[num].type = random(4)+1;
  rings[num].rotation = random(256);
}

void setup() {
  
  
  // arduboy.begin();
  arduboy.boot();



  arduboy.clear();
  arduboy.setFrameRate(FRAME_RATE);

  for(uint8_t i; i<num_rings; i++) {
    gen_ring(i);
  }
  rings[0].type = 0;
  rings[1].type = 4;
}

void arc_test() {



  // drawArc(64,32, 30, 1, 1, 255);
  // drawArc(64,32, 28, 1, 33, 255);
  // drawArc(64,32, 26, 1, 65, 255);
  // drawArc(64,32, 24, 1, 97, 255);
  // drawArc(64,32, 22, 1, 129, 255);
  // drawArc(64,32, 20, 1, 161, 255);
  // drawArc(64,32, 18, 1, 193, 255);
  // drawArc(64,32, 16, 1, 225, 255);


  // drawArc(64,32, 30, 1, 1, 0);
  // drawArc(64,32, 28, 1, 33, 0);
  // drawArc(64,32, 26, 1, 65, 32);
  // drawArc(64,32, 24, 1, 97, 64);
  // drawArc(64,32, 22, 1, 129, 96);
  // drawArc(64,32, 20, 1, 161, 128);
  // drawArc(64,32, 18, 1, 193, 160);
  // drawArc(64,32, 16, 1, 225, 192);

  static float pos1 = 0;
  static float pos2 = 0;

  drawArc(64,32,16,1,(uint8_t)pos1, (uint8_t)pos2);
  // drawArc(64,32,16,1,0, (uint8_t)pos2);

  arduboy.setCursor(0,0);
  arduboy.println(pos1,2);
  arduboy.println(pos2,2);

  if(arduboy.pressed(DOWN_BUTTON)) {
    pos1 +=.5;
  }
  if(arduboy.pressed(UP_BUTTON)) {
    pos1 -=.5;
  }
  if(arduboy.pressed(RIGHT_BUTTON)) {
    pos2 +=.5;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    pos2 -=.5;
  }
  // pos1 += .5;
  // pos2 += .1;

  if(pos1 > 255) {
    pos1 -= 255;
  }
  if(pos1 < 0) {
    pos1 += 255;
  }
  if(pos2 > 255) {
    pos2 -= 255;
  }
  if(pos2 < 0) {
    pos2 += 255;
  }

  arduboy.display(CLEAR_BUFFER);
  return;
}


void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  // arc_test();
  // return;



  if(arduboy.pressed(UP_BUTTON)) {
    speed += 0.0001f;
  }
  if(arduboy.pressed(DOWN_BUTTON)) {
    speed -= 0.001f;
  }

  if(arduboy.pressed(RIGHT_BUTTON)) {
    rot -=.5;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    rot +=.5;
  }


  if(speed <0) {
    speed = 0;
  }

  position += speed;
  if (position > num_rings) {
    position -= num_rings;
  }

  draw_level(position);

  Sprites::drawExternalMask(56,45,ship, shipMask, 0,0);

  arduboy.display(CLEAR_BUFFER);
}