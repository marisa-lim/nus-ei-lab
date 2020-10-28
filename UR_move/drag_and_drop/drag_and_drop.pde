//import controlP5.*;
//import processing.serial.*;

//ControlP5 cp5; //create ControlP5 object

int food1_x = 230;
int food1_y = 270;
int food2_x= 580;
int food2_y = 270;
int food3_x = 930;
int food3_y = 270;

DraggingPic[] dragImages = new DraggingPic[3];
 
void setup() {
  size(1433, 850);
  background(255);   
  noStroke(); 
 
  dragImages[0] = new  DraggingPic(food1_x, food1_y, "broccoli-icon.png"); // change file names here! 
  dragImages[1] = new  DraggingPic(food2_x, food2_y, "sausage-icon.png");
  dragImages[2] = new  DraggingPic(food3_x, food3_y, "bread-icon.png");
}
 
void draw() { 
  background(255, 255, 191);   
  for (DraggingPic currentDraggingPic : dragImages) {
    currentDraggingPic.display();
    currentDraggingPic.mouseDragged();
  }//for
}
 
// ------------------------------------------
 
void mousePressed() {
  for (DraggingPic currentDraggingPic : dragImages) {
    currentDraggingPic.draggingpicMousePressed();
  }//for
}
 
void mouseReleased() {
  for (DraggingPic currentDraggingPic : dragImages) {
    currentDraggingPic.draggingpicMouseReleased();
  }//for
}
 
// ==================================================
 
class DraggingPic {
 
  int x;
  int y;
  PImage sample;
 
  // controls whether we are dragging (holding the mouse)
  boolean hold; 
 
  // constructor
  DraggingPic(int posx, int posy, 
    String imageNameAsString) { 
    x=posx;
    y=posy;
    sample = loadImage(imageNameAsString);
    sample.resize(100, 0);
  }// constructor
 
  void display() {
    image(sample, x, y);
  }
 
  void draggingpicMousePressed() {
    if (mouseX>x&&
      mouseY>y&&
      mouseX<x+sample.width && 
      mouseY<y+sample.height) {
      hold=true;
    }
  }
 
  void draggingpicMouseReleased() {
    hold=false;
  }
 
  void mouseDragged() {
    if (hold) {
      x=mouseX; 
      y=mouseY;
    }
  }//method
  //
}//class 
// 
