// Get OSC Events
// 4 variables by default : /v1, /v2, /v3 and /v4

void oscEvent(OscMessage theOscMessage) {  
// OSC 1:
if(theOscMessage.checkAddrPattern("/v1")==true) 
  {
  if(theOscMessage.checkTypetag("f")) 
    {
    v1 = theOscMessage.get(0).floatValue(); 
    return;
    } 
  } 
  
// OSC 2: 
if(theOscMessage.checkAddrPattern("/v2")==true) 
  {
  if(theOscMessage.checkTypetag("f")) 
    {
    v2 = theOscMessage.get(0).floatValue(); 
    return;
    } 
  } 
  
// OSC 3:  
if(theOscMessage.checkAddrPattern("/v3")==true) 
  {
  if(theOscMessage.checkTypetag("f")) 
    {
    v3 = theOscMessage.get(0).floatValue(); 
    return;
    } 
  }
// OSC 4:  
if(theOscMessage.checkAddrPattern("/v4")==true) 
  {
  if(theOscMessage.checkTypetag("f")) 
    {
    v4 = theOscMessage.get(0).floatValue(); 
    return;
    } 
  }  
  
}
