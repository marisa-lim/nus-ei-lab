//               Soft & Hybrid Robotics User Interface
//               Edited by Marisa Lim

import controlP5.*;
import processing.serial.*;

ControlP5 cp5; //create ControlP5 object

// The serial port:
Serial port;
float rightval = 0;
float leftval = 0;
float thumbval = 0;

// set fonts
PFont title;
PFont button;  
  
float url1, url2, url3;

// set window dimensions
int windowwidth = 1433;
int windowheight = 950;
PImage right, left, thumb;

void setup(){ //same as arduino program
  
  size(1433, 950);    //window size, (width, height)
  
 // printArray(Serial.list());   //prints all available serial ports (uncomment when connected to Arduino)
  
  //port = new Serial(this, "COM9", 115200);  // uncomment when connected to Arduino, change COM number
  
  
  cp5 = new ControlP5(this);
  title = createFont("sansserif",70);  // custom fonts for buttons and title
  button = createFont("sansserif",20);
  right = loadImage("right.jpg"); // load images of actuator
  left = loadImage("left.jpg");
  thumb = loadImage("thumb.jpg");
  
  // create adjustable knob for right finger
  Knob t1=cp5.addKnob("rightval") 
          .setRange(0, 150) // 0 to 150 degrees
          .setPosition(315, 600) // set position (pixels)
          .setRadius(50) // knob radius
          .setNumberOfTickMarks(5)
          .setTickMarkLength(4)
          .setColorForeground(color(255,0,0))
          .setColorBackground(color(0,0,0))
          .setDragDirection(Knob.HORIZONTAL); // drag horizontally to vary
  // create label for knob
  Label label = t1.getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE);
  label.setFont(button);
  label.toUpperCase(false);
  label.setColor(color(0));
  label.setText("(0-150 degrees)")
       .setSize(15); // font size
  
  // create adjustable knob for left finger
  Knob t2 = cp5.addKnob("leftval") 
          .setRange(0, 150) // 0 to 150 degrees
          .setPosition(660, 600) // set position (pixels)
          .setRadius(50) // knob radius
          .setNumberOfTickMarks(5)
          .setTickMarkLength(4)
          .setColorForeground(color(255,0,0))
          .setColorBackground(color(0,0,0))
          .setDragDirection(Knob.HORIZONTAL); // drag horizontally to vary
  // create label for knob
  Label label2 = t2.getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE);
  label2.setFont(button);
  label2.toUpperCase(false);
  label2.setColor(color(0));
  label2.setText("(0-150 degrees)")
        .setSize(15); // font size
  
  // create adjustable slider for centre finger
  Slider t3 = cp5.addSlider("thumbval", 0, 20, 0, 970, 630, 200, 50) // slider range, position
                  .setNumberOfTickMarks(5)
                  .setColorForeground(color(255,0,0))
                  .setColorBackground(color(0,0,0))
                  .setColorTickMark(color(255, 69, 0))
                  .snapToTickMarks(false);
  // create label for slider
  Label label3 = t3.getCaptionLabel().align(ControlP5.CENTER, ControlP5.BOTTOM_OUTSIDE);
  label3.setFont(button);
  label3.toUpperCase(false);
  label3.setColor(color(0));
  label3.setText("(0-20 mm)")
        .setSize(15); // font size
  
  // create Configure button
  cp5.addButton("Configure")
     .setPosition(350, 770)
     .setSize(170,50)
     //.updateSize()
     .setColorBackground(color(0,0,0));
     
  // create Reset button
  cp5.addButton("Reset")
     .setPosition(900, 770)
     .setSize(150,50)
     //.updateSize()
     .setColorBackground(color(0,0,0));
  cp5.getController("Configure").setFont(button); 
  cp5.getController("Reset").setFont(button);
  
  // create Claw button
  //cp5.addButton("Claw")
  //   .setPosition(900, 770)
  //   .setSize(150,50)
  //   //.updateSize()
  //   .setColorBackground(color(0,0,0));
  //cp5.getController("Configure").setFont(button); 
  //cp5.getController("Reset").setFont(button);
  
  // create Pinch button
  
  
  // create Scoop button
} 
 

void draw(){  //same as loop in arduino

  background(204, 204, 255); // background color of window (r, g, b) or (0 to 255)
  
  //lets give title to our window
  fill(0, 0, 0);               //text color (r, g, b)
  textFont(title, 70);
  textAlign(CENTER);
  text("Soft & Hybrid Robotics",1433/2, 150);  // ("text", x coordinate, y coordinate)
  
  image(right, 230, 270, 270, 230);
  image(left, 580, 270, 270, 230);
  image(thumb, 930, 270, 270, 230);

  fill(0, 0, 0);               //text color (r, g, b)
  textFont(title, 25);
  textAlign(CENTER);
  text("Left Finger Rotation",720, 550);  // ("text", x coordinate, y coordinate)
  
  fill(0, 0, 0);               //text color (r, g, b)
  textFont(title, 25);
  text("Right Finger Rotation",363, 550);  // ("text", x coordinate, y coordinate)
  
  fill(0, 0, 0);               //text color (r, g, b)
  textFont(title, 25);
  text("Thumb Linear Displacement", 1070, 550);  // ("text", x coordinate, y coordinate)  
  
  fill(0,0,0); //knob 1
  textFont(title, 15);
  text("0", 318,700);
  
  fill(0,0,0); //knob 1
  textFont(title, 15);
  text("30", 295,646);
  
  fill(0,0,0); //knob 1
  textFont(title, 15);
  text("60", 330,595);
 
  fill(0,0,0); //knob 1
  textFont(title, 15);
  text("90", 400,595);
  
  fill(0,0,0); //knob 1
  textFont(title, 15);
  text("120", 436,646);
  
  fill(0,0,0); //knob 1
  textFont(title, 15);
  text("150", 426,700);
  
  fill(0,0,0); //knob 2
  textFont(title, 15);
  text("0", 663,700);
  
  fill(0,0,0); //knob 2
  textFont(title, 15);
  text("30", 640,646);
  
  fill(0,0,0); //knob 2
  textFont(title, 15);
  text("60", 675,595);
 
  fill(0,0,0); //knob 2
  textFont(title, 15);
  text("90", 745,595);
  
  fill(0,0,0); //knob 2
  textFont(title, 15);
  text("120", 781,646);
  
  fill(0,0,0); //knob 2
  textFont(title, 15);
  text("150", 771,700);
  
  fill(0,0,0); //slider
  textFont(title, 15);
  text("0", 970,615);
 
  fill(0,0,0); //slider
  textFont(title, 15);
  text("5", 1020,615);
  
  fill(0,0,0); //slider
  textFont(title, 15);
  text("10", 1070,615);
  
  fill(0,0,0); //slider
  textFont(title, 15);
  text("15", 1120,615);
  
  fill(0,0,0); //slider
  textFont(title, 15);
  text("20", 1170,615);
}
  
void Configure() {
  print("Configuration:");
  url1 = cp5.get(Knob.class,"rightval").getValue();
  url2 = cp5.get(Knob.class,"leftval").getValue();
  url3 = cp5.get(Slider.class,"thumbval").getValue();
  String number = "set " + url1 + " " + url2 + " " + url3;
//  port.write(number); // uncomment when connected to Arduino
  println(number);
  print(" rightval = " + url1 + " degrees,");
  print(" leftval = " + url2 + " degrees,");
  print(" thumbval = " + url3 + " mm");
  println();
}

void Reset() {
//  port.write("reset"); // uncomment when connected to Arduino
  cp5.get(Knob.class,"rightval").setValue(0);
  cp5.get(Knob.class, "leftval").setValue(0);
  cp5.get(Slider.class, "thumbval").setValue(0);
  print("Reset:");
  print(" rightval = " + 0 + " degree,");
  print(" leftval = " + 0 + " degree,");
  print(" thumbval = " + 0 + " cm");
  println();
}

void Claw() {
// port.write("claw"); // uncomment when connected to Arduino
  print("Claw:");
  print(" rightval = 45 degree,");
  print(" left val = 45 degree,");
  print(" thumbval = 0 degree");
  println();
}
