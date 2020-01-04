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
  size(800,600); 
  frameRate(50);
  smooth();
  noStroke();

  // Start oscP5, listening for incoming messages at port 12000
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",12000);
}

void draw() {
  //transparent background fading effect
  fill(10,3); 
  rect(0,0, width,height);
  
  ///////// Start your drawing /////////
  // v1 and v2 are the coordinates of the blue circle
  fill(0,20,255);
  ellipse(v1*width,v2*height,50,50);
  // v3 and v4 are the coordinates of the pink circle
  fill(255,20,255);
  ellipse(v3*width,v4*height,50,50);
}
