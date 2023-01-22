#include <Arduino.h>
#include <Arduboy2.h>
#include <Sprites.h>

#include "draw.h"
#include "images.h"

Arduboy2 arduboy;


#define RINGS 10



class Ringa {
  public:
    float x_offset;
    float y_offset;
    float rotation;
    uint8_t r;
    uint8_t type;
    Ringa() {
      this->x_offset = (random(100)-50)/10.0f;
      this->y_offset = (random(100)-50)/10.0f;
      this->rotation = random(256);
      this->r = 64;
      this->type = random(4);
    };
    void draw(float dist, float lastx, float lasty, float rot) {
      float r = 32; // TODO
      float srot = sin((rot*2*M_PI)/255);
      float crot = cos((rot*2*M_PI)/255);
      float x = lastx + (crot*this->x_offset + srot*this->y_offset);
      float y = lasty + (srot*this->x_offset + crot*this->y_offset);

      switch(this->type) {
        case 0: // open
          arduboy.drawCircle(x, y, r);
          break;
        case 1: // 1/3
          drawArc(x,y,this->r, WHITE, 32+rot, 96+rot);

          // arduboy.drawLine(x-r*rot_cos + 1,y, x+r*rot_cos-1, y);
          break;
        case 2: // 1/3 and 1/3
          drawArc(x,y,this->r, WHITE, 160+rot, 224+rot);
          drawArc(x,y,this->r, WHITE, 32+rot, 96+rot);
          break;
        case 3: // half
          drawArc(x,y,this->r, WHITE, 0+rot, 128+rot);
          break;
        case 4: // cross
          drawArc(x,y,this->r, WHITE, 0+rot, 128+rot);
          break;
      };
    };


};


struct Ring{
  float x_offset;
  float y_offset;
  uint8_t type;
} ;


float position = 0;
Ring rings[RINGS];

void gen_ring(uint8_t num) {
  rings[num].x_offset = max(-30,min(30, rings[num].x_offset +(random(100)-50)/10.0f));
  rings[num].y_offset = max(-30,min(30, rings[num].y_offset +(random(100)-50)/10.0f));
  rings[num].type = random(3);
  // rings[num].x_offset = 10;
  // rings[num].y_offset = 10;
}

void setup() {
  
  
  // arduboy.begin();
  arduboy.boot();



  arduboy.clear();
  arduboy.setFrameRate(75);

  for(uint8_t i; i<RINGS; i++) {
    gen_ring(i);
  }

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

float adj_dist(float x, float center, float dist) {
  return (x-center) * (dist*dist)/30 + center;
}

float speed=0;

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
  if(speed <0) {
    speed = 0;
  }

  position += speed;
  if (position > RINGS) {
    position -= RINGS;
  }

  float dist = (int)position - position + 1;
  float x = 64;
  float y = 0;
  // arduboy.setCursor(0,0);
  // arduboy.println(dist,2);
  for(uint8_t i=1; i<7; i++) {
    uint8_t offset = ((int)position + i) % RINGS;
    if(i > 1) {
      // x = adj_dist(x+rings[offset].x_offset, 64, dist);
      // y = adj_dist(y+rings[offset].y_offset, 10*dist, dist);
      x = adj_dist(x+rings[offset].x_offset, 64, dist);
      y = adj_dist(y+rings[offset].y_offset, 32-40/(dist+1), dist);
    } else {
      // x = adj_dist(x+rings[offset].x_offset * (dist), 64, dist);
      // y = adj_dist(y+rings[offset].y_offset * (dist), 10*dist, dist);
      x = adj_dist(x+rings[offset].x_offset * (dist), 64, dist);
      y = adj_dist(y+rings[offset].y_offset * (dist), 32-40/(dist+1), dist);

    }
    if(dist > 0.5f) {
      // if (arduboy.frameCount % i <1) {
        float w = 64.0f/(dist*dist);
        arduboy.drawCircle(x,y,w);
        if (rings[offset].type==1) {
          arduboy.drawLine(x-w+1,y, x+w-1, y);
        }
        if (rings[offset].type==2) {
          arduboy.drawLine(x,y-w+1,x,y+w-1);
        }

      // }
    }
    dist++;
  }


  Sprites::drawExternalMask(56,45,ship, shipMask, 0,0);
  // Sprites::drawOverwrite(55,45,ship,0);

  // Sprites::drawExternalMask(55,45,ship_bits, ship_bits, 0, 1);
  // arduboy.drawLine(64,45,72,60);
  // arduboy.drawLine(64,45,55,60);


  // arduboy.drawCircle(64,32,32.0f/(count^2));
  // arduboy.drawCircle(64,32,);
  // arduboy.drawCircle(64,32,);
  // arduboy.drawCircle(64,32,);
  
  // count++;

  arduboy.display(CLEAR_BUFFER);
}