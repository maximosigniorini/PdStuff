// Processing receive OSC data from Pd 
// with the [osc-out] object
// download La Malinette @ reso-nance.org/malinette
//////////////////////////////////////////////////////////////////
// Import
import oscP5.*;
import netP5.*;

// Variables
OscP5 oscP5;
NetAddress myRemoteLocation;

// By default we use 4 variables (see oscEvents if you want more)
float v1, v2, v3, v4; 

void setup() {
  size(600,400);
  frameRate(30);
  smooth();
  
  // start oscP5, listening for incoming messages at port 12000
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",12000);
}

void draw() {
  //transparent background for fadin effect
  fill(0,30); 
  rect(0,0,width,height); 
  
  ///////// Start your drawing /////////
  // we use the three OSC value from pd to translate a rectangle and scale it
  fill(0);
  
  stroke(255,0,0);
  line(0,0,v1*width+20,v2*height);
  line(0,height,v1*width+20,v2*height);
  line(v1*width+20,v2*height,0, height);
  line(v1*width+20,v2*height,width, height);
   
  stroke(255);
  translate(v1*width+20,v2*height);
  scale(v3);
  ellipse(0,0,100,100);
}
