#include "globals.h"
#include "spritemap.h"

Spritemap::Spritemap():Image(){

  animation_map_ = std::map< std::string, Animation* >();
  current_animation_ = NULL;
  
  columns_ = 0;
  rows_ = 0;
  complete_ = false;
  frame_ = 0;
  frame_count_ = 0;
  index_ = 0;
  rate_ = 1;
  
}

Spritemap::~Spritemap() {
  
}

Spritemap::Spritemap(const char * filename, int frame_width, int frame_height):Image(filename){
  frame_width_ = frame_width;
  frame_height_ = frame_height;
  
  //callback
  
  //Map of all animations from a string to a list
  animation_map_ = std::map< std::string, Animation* >();
  current_animation_ = NULL;
  
  columns_ = floor(image_surface_->w/frame_width_);
  rows_ = floor(image_surface_->h/frame_height_);
  
  frame_count_ = columns_ * rows_;
  complete_ = false;
  frame_ = 0;
  frame_count_ = 0;
  index_ = 0;
  rate_ = 1;
  
}

void Spritemap::Update() {
  //Image::Update(dt);
  float dt = 0.02;
  if (current_animation_ != NULL && !complete_) {
    timer_ += current_animation_->frame_rate * dt * rate_;
    if (timer_ >= 1.0f) {
      while (timer_ >= 1.0f) {
        --timer_;
        ++index_;
        

        if (index_ == current_animation_->frame_count) {
          if (current_animation_->loop) {
            index_ = 0;
            //if (callback != null) callback();
          } else {
            index_ = current_animation_->frame_count - 1;
            complete_ = true;
            //if (callback != null) callback();
            break;
          }
        }
      }
      if (current_animation_ != NULL) {
        frame_ = current_animation_->frames[index_];
      }
    }
  }
}

void Spritemap::Add(std::string name, int frames[], int frame_count, float frame_rate, bool loop) {
  animation_map_[name] =  new Animation(name, frames, frame_count, frame_rate, loop);
}

void Spritemap::Play(std::string name, bool reset, int frame) {
  
  if (!reset && current_animation_ && current_animation_->name == name) {
    return; 
  }
  current_animation_ = animation_map_[name];
  if (current_animation_ == NULL) {
    frame_ = index_ = 0;
    complete_ = true;
    return;
  }
  index_ = 0;
  timer_ = 0;
  frame_ = current_animation_->frames[frame % current_animation_->frame_count];
  complete_ = false;
}

void Spritemap::SetFrame(int column, int row) {
  current_animation_ = NULL;
  int frame = (row % rows_) * columns_ + (column % columns_);
  if (frame_ == frame) return;
  frame_ = frame;
  timer_ = 0;
}

void Spritemap::DrawTexture(Point p) {
  double x = p.x - origin_x_ + offset_x_;
  double y = p.y - origin_y_ + offset_y_;
  
  double w = frame_width_ * scale_x_ * scale_;
  double h = frame_height_ * scale_y_ * scale_;
  
  //(frame_ % columns_);
  //int(frame_ / columns_);
  
  double x_texture_offset = (double)(frame_width_)/(double)(image_surface_->w);
  double y_texture_offset = (double)(frame_height_)/(double)(image_surface_->h);
  
  int current_col = (frame_ % columns_);
  int current_row = int(frame_ / columns_);
  
  //std::cerr << current_col << " " << current_row << std::endl;
  
  glBegin( GL_QUADS );
  //Draw flipped   //row * frame_width_/image_surface_->w
  if (!flipped_) {
    //Bottom-left vertex (corner)
    glTexCoord2d( current_col * x_texture_offset, current_row * y_texture_offset); glVertex3d( x, y, 0.0f );
    //Bottom-right vertex (corner)
    glTexCoord2d( (current_col + 1) * x_texture_offset, current_row * y_texture_offset); glVertex3d( x+w, y, 0.f );
    //Top-right vertex (corner)
    glTexCoord2d( (current_col + 1) * x_texture_offset, (current_row + 1) * y_texture_offset); glVertex3d( x+w, y+h, 0.f );
    //Top-left vertex (corner)
    glTexCoord2d( current_col * x_texture_offset, (current_row + 1) * y_texture_offset); glVertex3d( x, y+h, 0.f );
    
  } else {
    //Top-left vertex (corner)
    glTexCoord2f( (current_col + 1) * x_texture_offset, current_row * y_texture_offset ); glVertex3f( x, y, 0.0f );
    //Bottom-left vertex (corner)
    glTexCoord2f( current_col * x_texture_offset, current_row * y_texture_offset ); glVertex3f( x+w, y, 0.f );
    //Bottom-right vertex (corner)
    glTexCoord2f( current_col * x_texture_offset, (current_row + 1) * y_texture_offset ); glVertex3f( x+w, y+h, 0.f );
    //Top-right vertex (corner)
    glTexCoord2f( (current_col + 1) * x_texture_offset, (current_row + 1) * y_texture_offset ); glVertex3f( x, y+h, 0.f );     
  }
  glEnd();
}