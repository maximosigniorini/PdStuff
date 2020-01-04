
// Processing send RSS data to Pure Data in OSC
// Data : Xml elements titles from a rss feed
// This example send a OscMessage beginnig with "title" to route it in Pure Data
// Because of this problem : OSC string and Pd symbols : http://www.mail-archive.com/pd-list@iem.at/msg50847.html
// 

// ------ CONFIG ------
int rss_max = 5;  // Number of rss to send
boolean DEBUG = true;
String url = "http://rss.feedsportal.com/c/268/f/3632/index.rss"; // Choose a RSS feed   

/* 
RSS ADRESSES :
-------------
http://www.lemonde.fr/rss/ > ex : http://www.lemonde.fr/rss/une.xml
http://www.investir.fr/rss/ > ex : http://www.investir.fr/RSS/cac40.xml
http://www.reuters.com/tools/rss/ > ex : http://feeds.reuters.com/reuters/topNews
http://www.lachainemeteo.com/meteo-rss/toute-l-actualite-meteo.xml
http://rss.feedsportal.com/c/268/f/3632/index.rss
*/

// ------ LIBRARIES -------
import oscP5.*; 
import netP5.*; 
  
// ------ VARIABLES -------
OscP5 oscP5;
OscMessage myMessage;
NetAddress myRemoteLocation;
String date, title;
XML rss;
XML [] xmldate, xmltitle;  
XML xml = loadXML("fancy.xml");

// ------ SETUP -------
void setup() {
  frameRate(0.2); // toutes les 5 secondes
  
  // OSC
  oscP5 = new OscP5(this,"127.0.0.1",9997);
  
  // XML
 // rss = new XML (this, url);   
  rss = loadXML (url);   
  xmldate = rss.getChildren("channel/item/pubDate");  // get date
  xmltitle = rss.getChildren("channel/item/title");   // get title
}

// ------ DRAW -------
void draw() {
  background(0);  
  sendXml();
  if (DEBUG) printXml();
}

// ------ SEND OSC -------
void sendXml(){
  for (int i = 0; i < rss_max ; i++) { // xmldate.length 
  date = "date "+ xmldate[i].getContent();  
  title =  "title " + i + " " + xmltitle[i].getContent();
  myMessage = new OscMessage("/rss"); 
  //myMessage.add(date);
  myMessage.add(title);
  oscP5.send(myMessage);
  }
}

void printXml(){
  println ("******************************************");
  for (int i = 0; i < rss_max ; i++) { // xmldate.length 
    println ("DATE :" + xmldate[i].getContent());  
    println ("TITLE :" + xmltitle[i].getContent());
  }
}
