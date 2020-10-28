// editor: Marisa Lim
// NUS Gripper V2 04
// works in tandem with Processing GUI

void setup()  //----------------------------------------------------------------------------------------------------------------------
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, INPUT_PULLUP);
     
  digitalWrite(6, HIGH); 
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);  
  digitalWrite(10, LOW); 

  Serial.begin(115200);  

  // Motor 1
  wtt(1, 0x80 + 0x00, 0x00, 0x00, 0x02, 0x50);                 
  wtt(1, 0x80 + 0x24, 0x00, 0x00, 0x75, 0x30);                 
  wtt(1, 0x80 + 0x25, 0x00, 0x00, 0x00, 0x00);                  
  wtt(1, 0x80 + 0x28, 0x00, 0x00, 0x75, 0x30);                 
  wtt(1, 0x80 + 0x2A, 0x00, 0x00, 0x75, 0x30);                
  wtt(1, 0x80 + 0x2B, 0x00, 0x00, 0x00, 0x0A);                  
  wtt(1, 0x80 + 0x34, 0x00, 0x00, 0x00, 0x00);                 
  wtt(1, 0x80 + 0x6C, 0x00, 0x31, 0x80, 0x11);                 
  wtt(1, 0x80 + 0x6D, 0x00, 0x00, 0x00, 0x00);                 

  // Motor 2 
  wtt(2, 0x80 + 0x24 + 0x20, 0x00, 0x00, 0x75, 0x30);         
  wtt(2, 0x80 + 0x25 + 0x20, 0x00, 0x7A, 0x00, 0x00);          
  wtt(2, 0x80 + 0x28 + 0x20, 0x00, 0x00, 0x75, 0x30);         
  wtt(2, 0x80 + 0x2A + 0x20, 0x00, 0x00, 0x75, 0x30);        
  wtt(2, 0x80 + 0x2B + 0x20, 0x00, 0x00, 0x00, 0x0A);         
  wtt(2, 0x80 + 0x2C + 0x20, 0x00, 0x00, 0x00, 0x00);         
  wtt(2, 0x80 + 0x30 + 0x20, 0x00, 0x00, 0x00, 0x05);          
  wtt(2, 0x80 + 0x34 + 0x20, 0x00, 0x00, 0x00, 0x00);          
  wtt(2, 0x80 + 0x6C + 0x10, 0x00, 0x31, 0x80, 0x11);          
  wtt(2, 0x80 + 0x6D + 0x10, 0x00, 0x00, 0x00, 0x00);  

  // Motor 3
  //wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x00, 0x00);
  //wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x00, 0x00);                     
  wtt(3, 0x80 + 0x24, 0x00, 0x00, 0x75, 0x30);                
  wtt(3, 0x80 + 0x25, 0x00, 0x00, 0x00, 0x00);            
  wtt(3, 0x80 + 0x28, 0x00, 0x00, 0x75, 0x30);                 
  wtt(3, 0x80 + 0x2A, 0x00, 0x00, 0x75, 0x30);                 
  wtt(3, 0x80 + 0x2B, 0x00, 0x00, 0x00, 0x0A);                 
  wtt(3, 0x80 + 0x34, 0x00, 0x00, 0x00, 0x04);                
  wtt(3, 0x80 + 0x6C, 0x00, 0x31, 0x80, 0x11);              
  wtt(3, 0x80 + 0x6D, 0x00, 0x00, 0x00, 0x00);  

  // Motor 4
  wtt(4, 0x80 + 0x24 + 0x20, 0x00, 0x00, 0x75, 0x30);         
  wtt(4, 0x80 + 0x25 + 0x20, 0x00, 0x7A, 0x00, 0x00);          
  wtt(4, 0x80 + 0x28 + 0x20, 0x00, 0x00, 0x75, 0x30);         
  wtt(4, 0x80 + 0x2A + 0x20, 0x00, 0x00, 0x75, 0x30);        
  wtt(4, 0x80 + 0x2B + 0x20, 0x00, 0x00, 0x00, 0x0A);         
  wtt(4, 0x80 + 0x2C + 0x20, 0x00, 0x00, 0x00, 0x00);         
  wtt(4, 0x80 + 0x30 + 0x20, 0x00, 0x00, 0x00, 0x05);          
  wtt(4, 0x80 + 0x34 + 0x20, 0x00, 0x00, 0x00, 0x04);          
  wtt(4, 0x80 + 0x6C + 0x10, 0x00, 0x31, 0x80, 0x11);          
  wtt(4, 0x80 + 0x6D + 0x10, 0x00, 0x00, 0x00, 0x00);  


  /*
  mmt(3, 1.4 * 51200 * 5, 50000, 10, 1, 1, 0);
  delay(1000);
  mmt(3, 0, 50000, 10, 1, 2, 0);
  while(rft(3, 0x22, 0x00, 0x00, 0x00, 0x00) != 0) {};
  */

  mch();
  mlh();
  mrh();
  //mth();
}


void loop()  //---------------------------------------------------------------------------------------------------------------------------------------------------------
{ 
  String ipw;
  while(Serial.available()) 
  {
    char c = Serial.read();
    ipw += c; 

    if(ipw == "sl1") sl1();      // solenoid valve left ON
    if(ipw == "sl0") sl0();      // solenoid valve left OFF
    if(ipw == "sc1") sc1();      // solenoid valve center ON
    if(ipw == "sc0") sc0();      // solenoid valve center OFF
    if(ipw == "sr1") sr1();      // solenoid valve right ON
    if(ipw == "sr0") sr0();      // solenoid valve right OFF
    if(ipw == "sa1") sa1();      // solenoid valve all ON
    if(ipw == "sa0") sa0();      // solenoid valve all OFF

    if (ipw == "set") set(1, 1, 1); // set from GUI Processing
    if (ipw == "reset") reset();  // to original position (reset function) from GUI Processing
    if(ipw == "tilt") tilt();     // motor t rotating to 100 degress at interval of 10 degrees (for testing)
    if(ipw == "claw") claw();     // mlp and mrp 45 degrees
    if(ipw == "pinch") pinch();   // mlp and mrp 90 degrees
    if(ipw == "scoop") scoop();   // scoop position; mlp and mrp beside mcp
    
    if(ipw == "mlh") mlh();      // motor 1 home        [ Motor 1 ]
    if(ipw == "mlp") mlp(1, 1);  // motor 1 move at speed (rps) to position (deg)
    if(ipw == "mlf") mlf(1);     // motor 1 forward
    if(ipw == "mlr") mlr(1);     // motor 1 reverse
    if(ipw == "mls") mls();      // motor l stop
    
    if(ipw == "mrh") mrh();      // motor r home        [ Motor 2 ]
    if(ipw == "mrp") mrp(1, 1);  // motor r move at speed (rps) to position (deg)
    if(ipw == "mrf") mrf(1);     // motor r forward
    if(ipw == "mrr") mrr(1);     // motor r reverse
    if(ipw == "mrs") mrs();      // motor r stop

    if(ipw == "mch") mch();      // motor c home        [ Motor 3 ]
    if(ipw == "mcp") mcp(1, 1);  // motor c move at speed (mm/s) to position (mm)
    if(ipw == "mcf") mcf(1);     // motor c forward
    if(ipw == "mcr") mcr(1);     // motor c reverse
    if(ipw == "mcs") mcs();      // motor c stop

    if(ipw == "mth") mth();      // motor t home
    if(ipw == "mtp") mtp(1, 1);  // motor t move at speed (deg/s) to position (deg)
    if(ipw == "mtf") mtf(1);     // motor t forward
    if(ipw == "mtr") mtr(1);     // motor t reverse
    if(ipw == "mts") mts();      // motor t stop
    
    if(ipw == "rpg") rpg();      // run program

    if(ipw == "mc1") mc1();      // motor controller ON
    if(ipw == "mc0") mc0();      // motor controller OFF
  }
  ipw = "";
  delay(1);
}

// Valve functions

void sl1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sl1");
  digitalWrite(4, HIGH);
}


void sl0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sl0");
  digitalWrite(4, LOW);
}


void sc1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sc1");
  digitalWrite(3, HIGH);
}


void sc0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sc0");
  digitalWrite(3, LOW);
}



void sr1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sr1");
  digitalWrite(2, HIGH);
}


void sr0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sr0");
  digitalWrite(2, LOW);
}



void sa1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sa1");
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}


void sa0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("sa0");
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

// Position functions

void tilt() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("tilt ");

  long mvs = 5;
  long mvp = 10;
  
  while(mvp < 100) // check if reach 100 degrees
  {
    mmt(4, 51200 * 2 * mvs, 60000, 30, 30, 0, mvp * 14222);
    while(rft(4, 66, 0, 0, 0, 0) != 0) {}; 
    mvp += 10;
    Serial.println(mvp);
    delay(5);
  } 

  delay(50);
  
  mmt(4, 51200 * 2 * mvs, 60000, 30, 30, 0, 0 * 14222);
  while(rft(4, 66, 0, 0, 0, 0) != 0) {}; 

}

void scoop() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("scoop");
  mlp(5, 175);
  mrp(5, 175);
}

void claw() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("claw");
  mlp(5, 45);
  mrp(5, 45);
}

void pinch() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("pinch");
  mlp(5, 0);
  mrp(5, 0);
}

void set(long r, long l, long t) // -------------------------------------------------------------------------------------------------------------------------------------------------
{
  //mc1();
  
  long mvs = MotorSpeed;   // note that center motor speed is in terms of mm/s
  Serial.print("set ");
  if(r == 1) 
  {
    r = gnb();
    l = gnb();
    t = gnb();
  }
  
  mmt(1, 1.4 * 51200 * mvs, 60000, 31, 1, 0, l * 51200 * 20 / 360);  // Left Motor
  mmt(2, 1.4 * 51200 * mvs, 60000, 31, 1, 0, r * 51200 * 20 / 360);  // Right Motor
  mmt(3, 1.4 * 51200 * mvs, 60000, 30, 1, 0, t * 51200 / 2);  // Center Motor
  while(rft(1, 34, 0, 0, 0, 0) != 0 || rft(2, 66, 0, 0, 0, 0) != 0 || rft(3, 34, 0, 0, 0, 0) != 0) {};  
  Serial.print(r);
  Serial.print(" ");
  Serial.print(l); 
  Serial.print(" ");
  Serial.println(t); 
  
  //mc0();
}

void reset() // -------------------------------------------------------------------------------------------------------------------------------------------------
{
  //mc1();
  
  Serial.println("Reset all Motors to Home");
  mch(); 
  delay(1);
  mlh();
  mrh();

  //mc0();
}


void mlh() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlh ");
  mmt(1, 1.4 * 51200 * 3, 50000, 31, 1, 1, 0);
  delay(100);
  mmt(1, 1.4 * 51200 * 3, 50000, 31, 1, 2, 0);
  while(rft(1, 0x22, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(1, 0, 50000, 31, 1, 2, 0);
  wtt(1, 0x21 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);
  Serial.println(rft(1, 0x21, 0x00, 0x00, 0x00, 0x00));
}


void mlp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlp ");
  if(mvs == 1) 
  {
    mvs = gnb();
    mvp = gnb();
  }
  
  mmt(1, 1.4 * 51200 * mvs, 60000, 31, 1, 0, mvp * 51200 * 20 / 360);
  while(rft(1, 34, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mlf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlf ");
  if(mvs == 1) mvs = gnb();
  mmt(1, 1.4 * 51200 * mvs, 50000, 30, 1, 1, 0);
  Serial.println(mvs);
  delay(200);
  mls();
}


void mlr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlr ");
  if(mvs == 1) mvs = gnb();
  mmt(1, 1.4 * 51200 * mvs, 50000, 30, 1, 2, 0);
  Serial.println(mvs);
  delay(200);
  mls();
}


void mls() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mls");
  mmt(1, 0, 50000, 30, 1, 1, 0);
  while(rft(1, 34, 0, 0, 0, 0) != 0) {};
}


void mrh() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrh ");
  mmt(2, 1.4 * 51200 * 3, 50000, 31, 1, 1, 0);
  delay(100);
  mmt(2, 1.4 * 51200 * 3, 50000, 31, 1, 2, 0);
  while(rft(2, 0x42, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(2, 0, 50000, 31, 1, 2, 0);
  wtt(2, 0x41 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);
  Serial.println(rft(2, 0x41, 0x00, 0x00, 0x00, 0x00));
}


void mrp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrp ");
  if(mvs == 1) 
  {
    mvs = gnb();
    mvp = gnb();
  }
  
  mmt(2, 1.4 * 51200 * mvs, 60000, 31, 1, 0, mvp * 51200 * 20 / 360);
  while(rft(2, 66, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mrf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrf ");
  if(mvs == 1) mvs = gnb();
  mmt(2, 1.4 * 51200 * mvs, 50000, 30, 1, 1, 0);
  Serial.println(mvs);
  delay(200);
  mrs();
}


void mrr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrr ");
  if(mvs == 1) mvs = gnb();
  mmt(2, 1.4 * 51200 * mvs, 50000, 30, 1, 2, 0);
  Serial.println(mvs);
  delay(200);
  mrs();
}


void mrs() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mrs");
  mmt(2, 0, 50000, 30, 1, 1, 0);
  while(rft(2, 34, 0, 0, 0, 0) != 0) {};
}


void mch() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mch ");
  wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x03, 0x10);
  delay(100);
  mmt(3, 1.4 * 51200 * 5, 50000, 30, 1, 1, 0);
  delay(500);
  mmt(3, 1.4 * 51200 * 5, 50000, 30, 1, 2, 0);
  while(rft(3, 0x22, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(3, 0, 50000, 30, 1, 2, 0);
  wtt(3, 0x21 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);

  wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x02, 0x10);
  delay(100);
  mcp(3, 2); //2 mm short of moving back due to manufacturer issue
  mmt(3, 0, 50000, 30, 1, 2, 0);
  delay(100);
  wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x03, 0x10);
  delay(100);
  wtt(3, 0x21 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);

  Serial.println(rft(3, 0x21, 0x00, 0x00, 0x00, 0x00));
}


void mcp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mcp ");
  if(mvs == 1) 
  {
    mvs = gnb();
    mvp = gnb();
  }
  mmt(3, 1.4 * 51200 * mvs, 60000, 30, 1, 0, mvp * 51200 / 2);
  while(rft(3, 34, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mcf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mcf ");
  if(mvs == 1) mvs = gnb();
  mmt(3, 1.4 * 51200 * mvs, 50000, 15, 2, 1, 0);
  Serial.println(mvs);
  delay(1000);
  mcs();
}


void mcr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mcr ");
  if(mvs == 1) mvs = gnb();
  mmt(3, 1.4 * 51200 * mvs, 50000, 15, 2, 2, 0);
  Serial.println(mvs);
  delay(1000);
  mcs();
}


void mcs() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mcs");
  mmt(3, 0, 50000, 30, 1, 1, 0);
  while(rft(3, 34, 0, 0, 0, 0) != 0) {};
}


void mth() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mth ");
  wtt(4, 0x80 + 0x34 + 0x20, 0x00, 0x00, 0x00, 0x00);   
  delay(10);
  mmt(4, 51200 * 10, 60000, 30, 30, 2, 0);
  delay(10);
  while(rft(4, 0x22 + 0x20, 0x00, 0x00, 0x00, 0x00) != 0) {};
  wtt(4, 0x21 + 0x80 + 0x20, 0x00, 0x00, 0x00, 0x00);
  delay(10);
  mmt(4, 51200 * 20, 50000, 30, 30, 0, 55.0 / 360 * 51200 * 100);  // 55.0 degrees home offset
  while(rft(4, 0x22 + 0x20, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(4, 0, 60000, 30, 30, 1, 0);
  delay(10);
  wtt(4, 0x21 + 0x80 + 0x20, 0x00, 0x00, 0x00, 0x00);
  Serial.println(rft(4, 0x21 + 0x20, 0x00, 0x00, 0x00, 0x00));
  /*
  //while(!digitalRead(7)){};
  wtt(4, 0x21 + 0x80 + 0x20, 0x00, 0x00, 0x00, 0x00);
  delay(5);
  mmt(4, 51200 * 20, 50000, 30, 0, 0, 45.0 / 360 * 51200 * 100);
  
  while(rft(4, 0x22 + 0x20, 0x00, 0x00, 0x00, 0x00) != 0) {};
  Serial.println(rft(4, 0x21 + 0x20, 0x00, 0x00, 0x00, 0x00));
  */
}


void mtp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mtp ");
  if(mvs == 1) 
  {
    mvs = gnb();
    mvp = gnb();
  }
  mmt(4, 51200 * 2 * mvs, 60000, 30, 30, 0, mvp * 14222);
  while(rft(4, 66, 0, 0, 0, 0) != 0) {}; 
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mtf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mtf ");
  if(mvs == 1) mvs = gnb();
  mmt(4, 51200 * 2 * mvs, 60000, 30, 30, 1, 0);
  Serial.println(mvs);
  //delay(1000);
  //mcs();
}


void mtr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mtr ");
  if(mvs == 1) mvs = gnb();
  mmt(4, 51200 * 2 * mvs, 60000, 30, 30, 2, 0);
  Serial.println(mvs);
  //delay(1000);
  //mcs();
}


void mts() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mts");
  mmt(4, 0, 50000, 30, 30, 1, 0);
  while(rft(4, 66, 0, 0, 0, 0) != 0) {};  
}


void rpg()  //-----------------------------------------------------------------------------------------------------------------------------------------------
{
  mc1();
  Serial.println("rpg");
  mlh();
  mrh();
  mch();
  delay(300);
  for(int a = 0; a < 5; a++)
  {
    mmt(1, 1.4 * 51200 * 5, 60000, 30, 1, 0, 90 * 51200 * 20 / 360);
    mmt(2, 1.4 * 51200 * 5, 60000, 30, 1, 0, 90 * 51200 * 20 / 360);
    mmt(3, 1.4 * 51200 * 10, 60000, 30, 1, 0, 20 * 51200 / 2);
    delay(1200);
    mmt(1, 1.4 * 51200 * 5, 60000, 30, 1, 0, 0);
    mmt(2, 1.4 * 51200 * 5, 60000, 30, 1, 0, 0); 
    mmt(3, 1.4 * 51200 * 10, 60000, 30, 1, 0, 0); 
    delay(1200);  
  }
  mc0();
}


void mc1()  //-----------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mc1");
  digitalWrite(9, LOW);  
  digitalWrite(10, LOW); 
}


void mc0()  //-----------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mc1");
  digitalWrite(9, HIGH);  
  digitalWrite(10, HIGH); 
}
  


void wtt(int mnb, byte add, byte by1, byte by2, byte by3, byte by4)  //----------------------------------------------------------------------------------
{
  if(mnb == 1 || mnb == 2) digitalWrite(6, LOW);
  if(mnb == 3 || mnb == 4) digitalWrite(8, LOW);
  shiftOut(12, 13, MSBFIRST, (char) add);  
  shiftOut(12, 13, MSBFIRST, (char) by1);  
  shiftOut(12, 13, MSBFIRST, (char) by2); 
  shiftOut(12, 13, MSBFIRST, (char) by3); 
  shiftOut(12, 13, MSBFIRST, (char) by4); 
  if(mnb == 1 || mnb == 2) digitalWrite(6, HIGH);
  if(mnb == 3 || mnb == 4) digitalWrite(8, HIGH);
}

long rft(int mnb, byte addr, byte by1, byte by2, byte by3, byte by4)  //---------------------------------------------------------------------------------
{
  byte sta, b1r, b2r, b3r, b4r;
  long dta;
  if(mnb == 1 || mnb == 2) digitalWrite(6, LOW);
  if(mnb == 3 || mnb == 4) digitalWrite(8, LOW);
  
  shiftOut(12, 13, MSBFIRST, (char) addr);  
  shiftOut(12, 13, MSBFIRST, (char) by1);  
  shiftOut(12, 13, MSBFIRST, (char) by2); 
  shiftOut(12, 13, MSBFIRST, (char) by3); 
  shiftOut(12, 13, MSBFIRST, (char) by4); 

  if(mnb == 1 || mnb == 2) digitalWrite(6, HIGH);
  if(mnb == 3 || mnb == 4) digitalWrite(8, HIGH);
  
  if(mnb == 1 || mnb == 2) digitalWrite(6, LOW);
  if(mnb == 3 || mnb == 4) digitalWrite(8, LOW);

  sta = shiftIn(11, 13, MSBFIRST);
  b1r = shiftIn(11, 13, MSBFIRST);
  b2r = shiftIn(11, 13, MSBFIRST);
  b3r = shiftIn(11, 13, MSBFIRST);
  b4r = shiftIn(11, 13, MSBFIRST); 
  
  if(mnb == 1 || mnb == 2) digitalWrite(6, HIGH);
  if(mnb == 3 || mnb == 4) digitalWrite(8, HIGH);

  dta = b1r;
  dta = dta << 8 | b2r;
  dta = dta << 8 | b3r;
  dta = dta << 8 | b4r;
  return dta;
}

void mmt(int smn, long vmx, long amx, int irn, int ihd, int ram, long xtg)  //----------------------------------------------------------------------------------
{
  int mtu;
  if(smn == 1 || smn == 3) mtu = 0;
  else mtu = 1;
  byte vmx3, vmx2, vmx1, vmx0;
  vmx3 = vmx >> 24;
  vmx2 = vmx >> 16;
  vmx1 = vmx >> 8;
  vmx0 = vmx; 
  byte amx3, amx2, amx1, amx0;
  amx3 = amx >> 24;
  amx2 = amx >> 16;
  amx1 = amx >> 8;
  amx0 = amx; 
  byte xtg3, xtg2, xtg1, xtg0;
  xtg3 = xtg >> 24;
  xtg2 = xtg >> 16;
  xtg1 = xtg >> 8;
  xtg0 = xtg; 
  wtt(smn, 0xA8 + 0x20 * mtu, amx3, amx2, amx1, amx0);     
  wtt(smn, 0xA7 + 0x20 * mtu, vmx3, vmx2, vmx1, vmx0);     
  wtt(smn, 0xA6 + 0x20 * mtu, amx3, amx2, amx1, amx0);    
  wtt(smn, 0xB0 + 0x20 * mtu, 0x00, 0x00, irn, ihd);      
  wtt(smn, 0xB4 + 0x20 * mtu, 0x00, 0x00, 0x00, 0x05);         
  wtt(smn, 0xA0 + 0x20 * mtu, 0x00, 0x00, 0x00, ram);     
  wtt(smn, 0xAD + 0x20 * mtu, xtg3, xtg2, xtg1, xtg0);   
}

long gnb() //-------------------------------------------------------------------------------------------------------------------------------------------
{
  while (Serial.available() == 0);
  float val = Serial.parseFloat(); 
  return (long) val;
}
