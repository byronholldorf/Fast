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
#define NEAR_CLIP_PLANE 1.2f

#define FRAME_RATE 40

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


float position = 0;
float speed=0;
float rot=0;
float boost=50;
uint16_t crash_sequence = 0;
int8_t x_shake;

uint8_t lap = 1;
long last_lap_time = 0;
long lap_start_millis = 0;
long race_start_millis = 0;


float adj_dist(float x, float center, float dist) {
  return (x-center) * (dist*dist)/80 + center;
}

/**
 * @brief get x,y units for rotating 0-255
 * 
 */
Pointf get_rot(uint8_t rotate, uint8_t r) {
  if (r < 3) {
    uint8_t rot =  -rotate - 16;
    // if (rot < 0)
    //   return Pointf(1,0);
    if (rot < 32)
      return Pointf(.707f, .707f);
    if (rot < 64)
      return Pointf(0, 1);
    if (rot < 96) 
      return Pointf(-.707f, .707f);
    if (rot < 128)
      return Pointf(-1, 0);
    if (rot < 160)
      return Pointf(-.707f, -.707f);
    if (rot < 192)
      return Pointf(-1, 0);
    if (rot < 224)
      return Pointf(.707f, -.707f);
    return Pointf(1,0);
  } else {
    float adjr = -rotate*M_PI*2/256;
    return Pointf(cos(adjr), sin(adjr));
  }
}

Pointf get_circ_pt(Pointf center, float r, Pointf rotate) {
  return Pointf(center.x+r*rotate.x, center.y+r*rotate.y);
}


float y_adj_center(float dist_to_cam) {
  return max(-128, -80/(dist_to_cam));
}

float size_adj(float dist_to_cam) {
  return min(128,2*64/(dist_to_cam));
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
  float x = 64+x_shake;
  uint8_t dither = uint8_t(dist_to_cam);

  uint8_t angle = (uint8_t)(rot + rings[offset].rotation);
  switch(rings[offset].type) {
    case 0: // Start
      drawArc(x,y,r, WHITE, 0, 0);
      drawArc(x,y,r+2, WHITE, 0, 0, dither);
      drawArc(x,y,r+4, WHITE, 0, 0, dither);
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
        Pointf rot1 = get_rot(angle, r);
        Pointf rot2 = get_rot(96+angle, r);
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
        Pointf p1 = get_circ_pt(Pointf(x,y), r, get_rot(w+angle, r));
        Pointf p2 = get_circ_pt(Pointf(x,y), r, get_rot(128-w+angle, r));
        arduboy.drawLine(p1.x,p1.y,p2.x,p2.y, WHITE);

        p1 = get_circ_pt(Pointf(x,y), r, get_rot(128+w+angle, r));
        p2 = get_circ_pt(Pointf(x,y), r, get_rot(-w+angle, r));
        arduboy.drawLine(p1.x,p1.y,p2.x,p2.y, WHITE);
      }
      break;
    case 4: // boost
      {
        drawArc(x,y,r, WHITE, 0,0, dither);
        uint8_t w = 10;
        Pointf rot1 = get_rot(w+angle, r);
        Pointf rot2 = get_rot(angle, r);
        Pointf rot3 = get_rot(-w+angle, r);
        uint16_t total_ms=1000;
        uint16_t st = total_ms/7;
        if (blink(MS_TO_FRAMES(3*st), MS_TO_FRAMES(total_ms), MS_TO_FRAMES(0*st))) {
          draw_arrow(x, dist_to_cam, rot1, rot2, rot3);
        }
        if (dist_to_cam < 12) {
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
      }
      
      break;
  };
}

void crash() {
  crash_sequence = max(min(40*(speed*20),FRAME_RATE*3/2), 10);
  speed = 0;
}

void check_collision(uint8_t offset) {
  uint8_t angle = (uint8_t)(-64-rot - rings[offset].rotation);
  uint8_t ship_size=5;
  switch(rings[offset].type) {
    case 0: // lap
      last_lap_time = lap_start_millis - millis();
      lap_start_millis = millis();
      lap++;
      
      break;
    case 1: // open
      break;
    case 2: // 1/3 (0,96)
      // if (angle > 96-ship_size && angle < 192+ship_size) {
      if (angle < 96+ship_size || angle > 256-ship_size) {
  
  // arduboy.display();
  // delay(1000);

        crash();
      }
      break;
    case 3: // middle (+-7)
      if (angle < ship_size+7 || angle > 256-ship_size-7) {
        crash();
      }
      if (angle < 128+ship_size+7 && angle > 128-ship_size-7) {
        crash();
      }
      break;
    case 4: // powerup (+-10)
      // if (angle < 192+ship_size+10 && angle > 192-ship_size-10) {
      if (angle < ship_size+10 || angle > 256-ship_size-10) {
        boost = min(200, boost+20);
      }
      break;
  }
}


// void draw_ring(float dist_to_cam, uint8_t offset) {
//   float y = 32+y_adj_center(dist_to_cam);
//   float size = size_adj(dist_to_cam);
//   draw_ring(64,y,size,offset,uint8_t(dist_to_cam/2), dist_to_cam);
// }

void draw_generic_ring(float dist_to_cam) {
  drawArc(64+x_shake,32+y_adj_center(dist_to_cam),size_adj(dist_to_cam), WHITE, 0, 0, uint8_t(dist_to_cam*3/5));
}

void draw_level() {
  uint8_t drawn_rings=32;
  uint8_t ring_mult = 8;
  float draw_pos = position-0.1;
  
  uint16_t current_position = (uint16_t)(draw_pos*ring_mult);
  float distance_to_cam = ((int)(draw_pos*ring_mult+1) - draw_pos*ring_mult);

  for(uint8_t ring=0; ring<drawn_rings; ring++) {
    if(distance_to_cam > NEAR_CLIP_PLANE) {
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
  randomSeed(1);
  for(uint8_t i=1; i<num_rings; i++) {
    gen_ring(i);
  }
  rings[0].type = 0;
  // rings[1].type = 3;
  // rings[1].rotation = 0;

  // rings[2].type = 3;
  // rings[2].rotation = 64;
}



float engine_force = 0;
float mass = 500;
float drag = 100;
float friction = .1;
float braking_friction = 0;

float turn_speed = 0;
float turn_friction = .15;
float turn_static_friction = .005;

void draw_debug() {
  tinyfont.setCursor(90,1);
  tinyfont.println(position, 2);
  tinyfont.setCursor(90,6);
  tinyfont.println(speed*100, 2);
  tinyfont.setCursor(90,12);
  tinyfont.println(boost);

  tinyfont.setCursor(2,30);
  static int cpu = 0;
  if (arduboy.everyXFrames(20)) {
    cpu = arduboy.cpuLoad();
  } else {
    cpu = max(cpu, arduboy.cpuLoad());
  }
  
  tinyfont.print(cpu);
  tinyfont.print('%');
}


void physics() {

  if (crash_sequence) {
    crash_sequence--;
    // if(arduboy.everyXFrames(2)) {
      x_shake = (random(25)) * crash_sequence / 100;
      if (crash_sequence % 2) {
        x_shake = -x_shake;
      }
    // }
    if (!crash_sequence) {
      x_shake =0;
      position += .2;
    }
    return;
  } 

  if(arduboy.buttonsState() & (UP_BUTTON | B_BUTTON)) {
    // speed += 0.0001f;

    engine_force++;
    if (engine_force > 6)
      engine_force = 6;
    if (boost && arduboy.pressed(B_BUTTON)) {
      engine_force *= 3;
      boost--;
    }
  } else {
    engine_force = 0;
  }

  if(arduboy.pressed(DOWN_BUTTON)) {
    // speed -= 0.001f;
    braking_friction += 1;
    if (braking_friction > 20) {
      braking_friction=20;
    }
  } else {
    braking_friction -= 5;
    if (braking_friction < 0) {
      braking_friction=0;
    }
  }

  if(arduboy.pressed(RIGHT_BUTTON)) {
    // rot -=.5;
    turn_speed -= 1 + speed * 30;
  }
  if(arduboy.pressed(LEFT_BUTTON)) {
    // rot +=.5;
    turn_speed += 1 + speed * 30;
  }

  rot += turn_speed*.1;
  if (rot < 0) {
    rot += 256;
  }
  if (rot >= 256) {
    rot -= 256;
  }
  if (turn_speed > 0) {
    // turn_speed = max(0, turn_speed - turn_friction*turn_speed - turn_static_friction);
    turn_speed = turn_speed - turn_friction*turn_speed;
  } else {
    // turn_speed = min(0, turn_speed - turn_friction*turn_speed + turn_static_friction);
    turn_speed = turn_speed - turn_friction*turn_speed;
  }

  float force = engine_force - (drag*speed) - friction - braking_friction;
  float accel = force/mass;
  speed += accel / FRAME_RATE;


  if(speed <0) {
    speed = 0;
  }

  float last_position = position;
  position += speed;
  if (position > num_rings) {
    position -= num_rings;
  }

  if((uint8_t)last_position != (uint8_t)position) {
    check_collision((uint8_t)position);
  }


}

void draw_guages(uint8_t value1, uint8_t value2) {
  uint8_t x=16, y=62, xmax=126, num=10, h1=2, h2=10;
  uint8_t w=(xmax-x-64)/num;
  for (uint8_t i=0; i<num; i++) {
    uint8_t h = h1+i*(h2-h1)/num;
    arduboy.fillRect(64-x-i*(w+1), y-h, w-1, h, (value1>i)?WHITE:BLACK);
    arduboy.fillRect(64+x+i*w, y-h, w-1, h, (value2>i)?WHITE:BLACK);
    
  }

  
  // arduboy.drawLine(left, bot, tra_x, bot);
  // arduboy.drawLine(left, bot, left, top2);
  // arduboy.drawLine(left, top2, tra_x, top2);
  // drawArc(tra_x, top2 - small_r, small_r, WHITE, 192, 224);
  // drawArc(tra_x, bot - large_r, large_r, WHITE, 192, 224);
  // arduboy.drawLine(tra_x+small_r, top2, tra_x, top2);
  // uint8_t lengthspeed
}

void draw_lap() {
  tinyfont.setCursor(2,2);
  tinyfont.print("Lap: ");
  tinyfont.print(lap);
}

void draw_ship() {
  Sprites::drawExternalMask(56-(turn_speed*.3)+x_shake,45,ship, shipMask, 0,0);
}

void loop() {
  if (!arduboy.nextFrame()) {
    return;
  }

  physics();
  // draw_debug();
  draw_level();
  draw_ship();
  draw_lap();
  draw_guages(boost/20, min(speed*100,10));
  
  arduboy.display(CLEAR_BUFFER);
}