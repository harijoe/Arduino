
 void setup()  { 

}  
void loop()  {
 
 
  for(int b = 0 ; b <= 255; b=b+5) 
  { 
      for(int g = 0 ; g <= 255; g=g+5) 
    { 
      for(int r= 0 ; r <= 255; r=r+5) 
       { 
        analogWrite(6, b);         
        analogWrite(9, g);         
        analogWrite(10, r);    
        delay(10);
 
      } 
    }
  }
 
}
