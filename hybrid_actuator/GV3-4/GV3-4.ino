boolean io0Stat,io0StatPrev, io1Stat, io1StatPrev;
int MotorSpeed = 6; // in rounds per second

void setup()  //----------------------------------------------------------------------------------------------------------------------
{
  Serial.begin(115200);

  pinMode(9, OUTPUT);     // grasp right
  pinMode(10, OUTPUT);    // grasp center
  pinMode(8, OUTPUT);     // grasp left
  pinMode(3, OUTPUT);     // hold right
  pinMode(5, OUTPUT);     // hold center
  pinMode(6, OUTPUT);     // hold left
  pinMode(13, OUTPUT);    // tmcCLK
  pinMode(4, OUTPUT);     // tmcCS1
  pinMode(7, OUTPUT);     // tmcCS2
  pinMode(11, OUTPUT);    // tmcSDI
  pinMode(2, OUTPUT);     // tmcEN1
  pinMode(A0, OUTPUT);    // tmcEN2
  pinMode(12, INPUT_PULLUP);  // tmcSDO

  digitalWrite(4, HIGH);  // tmcCS1
  digitalWrite(7, HIGH);  // tmcCS2
  digitalWrite(2, HIGH);  // tmcEN1
  digitalWrite(A0, HIGH); // tmcEN2

  // Motor 1 - Left
  wtt(1, 0x80 + 0x00, 0x00, 0x00, 0x03, 0x50);    // GCONF
  wtt(1, 0x80 + 0x24, 0x00, 0x00, 0x75, 0x30);    // A1
  wtt(1, 0x80 + 0x25, 0x00, 0x00, 0x00, 0x00);    // V1
  wtt(1, 0x80 + 0x28, 0x00, 0x00, 0x75, 0x30);    // DMAX
  wtt(1, 0x80 + 0x2A, 0x00, 0x00, 0x75, 0x30);    // D1
  wtt(1, 0x80 + 0x2B, 0x00, 0x00, 0x00, 0x0A);    // VSTOP
  wtt(1, 0x80 + 0x34, 0x00, 0x00, 0x00, 0x00);    // SW_MODE
  wtt(1, 0x80 + 0x6C, 0x00, 0x31, 0x80, 0x11);    // CHOPCONF
  wtt(1, 0x80 + 0x6D, 0x00, 0x00, 0x00, 0x00);    // COOLCONF

  // Motor 2 - Right
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

  // Motor 3 - Center
  wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x00, 0x50);
  wtt(3, 0x80 + 0x24, 0x00, 0x00, 0x75, 0x30);
  wtt(3, 0x80 + 0x25, 0x00, 0x00, 0x00, 0x00);
  wtt(3, 0x80 + 0x28, 0x00, 0x00, 0x75, 0x30);
  wtt(3, 0x80 + 0x2A, 0x00, 0x00, 0x75, 0x30);
  wtt(3, 0x80 + 0x2B, 0x00, 0x00, 0x00, 0x0A);
  wtt(3, 0x80 + 0x34, 0x00, 0x00, 0x00, 0x00);
  wtt(3, 0x80 + 0x6C, 0x00, 0x31, 0x80, 0x11);
  wtt(3, 0x80 + 0x6D, 0x00, 0x00, 0x00, 0x00);

  // Motor 4 - Tilt
  wtt(4, 0x80 + 0x24 + 0x20, 0x00, 0x00, 0x75, 0x30);
  wtt(4, 0x80 + 0x25 + 0x20, 0x00, 0x7A, 0x00, 0x00);
  wtt(4, 0x80 + 0x28 + 0x20, 0x00, 0x00, 0x75, 0x30);
  wtt(4, 0x80 + 0x2A + 0x20, 0x00, 0x00, 0x75, 0x30);
  wtt(4, 0x80 + 0x2B + 0x20, 0x00, 0x00, 0x00, 0x0A);
  wtt(4, 0x80 + 0x2C + 0x20, 0x00, 0x00, 0x00, 0x00);
  wtt(4, 0x80 + 0x30 + 0x20, 0x00, 0x00, 0x00, 0x05);
  wtt(4, 0x80 + 0x34 + 0x20, 0x00, 0x00, 0x00, 0x00);
  wtt(4, 0x80 + 0x6C + 0x10, 0x00, 0x31, 0x80, 0x11);
  wtt(4, 0x80 + 0x6D + 0x10, 0x00, 0x00, 0x00, 0x00);

  digitalWrite(2, LOW);  // tmcEN1
  digitalWrite(A0, LOW); // tmcEN2

  // mlh();
  // mrh();
  // mch();
  // mth();
}

void loop()  //---------------------------------------------------------------------------------------------------------------------------------------------------------
{
  String ipw;
  while (Serial.available())
  {
    char c = Serial.read();
    ipw += c;

    if (ipw == "gl1") gl1();     // grasp left ON
    if (ipw == "gl0") gl0();     // grasp left OFF
    if (ipw == "gc1") gc1();     // grasp center ON
    if (ipw == "gc0") gc0();     // grasp center OFF
    if (ipw == "gr1") gr1();     // grasp right ON
    if (ipw == "gr0") gr0();     // grasp right OFF
    if (ipw == "ga1") ga1();     // grasp all ON
    if (ipw == "ga0") ga0();     // grasp all OFF

    if (ipw == "hl1") hl1();      // hold left ON
    if (ipw == "hl0") hl0();     // hold left OFF
    if (ipw == "hc1") hc1();     // hold center ON
    if (ipw == "hc0") hc0();     // hold center OFF
    if (ipw == "hr1") hr1();     // hold right ON
    if (ipw == "hr0") hr0();     // hold right OFF
    if (ipw == "ha1") ha1();     // hold all ON
    if (ipw == "ha0") ha0();     // hold all OFF

    if (ipw == "mlh") mlh();     // motor 1 home        [ Motor 1 ]
    if (ipw == "mlp") mlp(1, 1); // motor 1 move at speed (rps) to position (deg)
    if (ipw == "mlf") mlf(1);    // motor 1 forward
    if (ipw == "mlr") mlr(1);    // motor 1 reverse
    if (ipw == "mls") mls();     // motor l stop

    if (ipw == "mrh") mrh();     // motor r home        [ Motor 2 ]
    if (ipw == "mrp") mrp(1, 1); // motor r move at speed (rps) to position (deg)
    if (ipw == "mrf") mrf(1);    // motor r forward
    if (ipw == "mrr") mrr(1);    // motor r reverse
    if (ipw == "mrs") mrs();     // motor r stop

    if (ipw == "mch") mch();     // motor c home        [ Motor 3 ]
    if (ipw == "mcp") mcp(1, 1); // motor c move at speed (mm/s) to position (mm)
    if (ipw == "mcf") mcf(1);    // motor c forward
    if (ipw == "mcr") mcr(1);    // motor c reverse
    if (ipw == "mcs") mcs();     // motor c stop

    if (ipw == "mth") mth();     // motor t home        [ Motor 4 ]
    if (ipw == "mtp") mtp(1, 1); // motor t move at speed (deg/s) to position (deg)
    if (ipw == "mtf") mtf(1);    // motor t forward
    if (ipw == "mtr") mtr(1);    // motor t reverse
    if (ipw == "mts") mts();     // motor t stop
    
    if(ipw == "claw") claw();    // mlp and mrp 45 degrees
    if(ipw == "pinch") pinch();  // mlp and mrp 90 degrees
    if(ipw == "scoop") scoop();  // scoop position

    if (ipw == "io0") io0();     // I/O 0 status
    if (ipw == "io1") io1();     // I/O 1 status

    if (ipw == "rpg") rpg();     // run program

    if (ipw == "mc1") mc1();     // motor controller ON
    if (ipw == "mc0") mc0();     // motor controller OFF
  }
  ipw = "";
  delay(1);
  io0StatPrev =io0Stat;
  io1StatPrev =io1Stat;
  io0Stat = digitalRead(A1);
  io1Stat = digitalRead(A2);
  if(io0Stat && !io0StatPrev)                  // If IO # 0 turns ON, grip all actuators
  {
    Serial.println("IO 0 ON");
    gr1();
    gl1();
    gc1();
  }
  if(!io0Stat && io0StatPrev)                  // If IO # 0 turns OFF, ungrip all actuators
  {
    Serial.println("IO 0 OFF");
    gr0();
    gl0();
    gc0();
  }
  if(io1Stat && !io1StatPrev)                  // If IO # 1 turns ON, hold all actuators
  {
    Serial.println("IO 1 ON");
    hr1();
    hl1();
    hc1();
  }
  if(!io1Stat && io1StatPrev)                  // If IO # 1 turns OFF, unhold all actuators
  {
    Serial.println("IO 1 OFF");
    mrp(10, 0);
    hr0();
    hl0();
    hc0();
  }
}


void gl1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("gl1");
  digitalWrite(8, HIGH);
}


void gl0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("gl0");
  digitalWrite(8, LOW);
}


void gc1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("gc1");
  digitalWrite(10, HIGH);
}


void gc0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("gc0");
  digitalWrite(10, LOW);
}


void gr1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("gr1");
  digitalWrite(9, HIGH);
}


void gr0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("gr0");
  digitalWrite(9, LOW);
}


void ga1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("ga1");
  digitalWrite(8, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(9, HIGH);
}


void ga0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("ga0");
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
}


void hl1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("hl1");
  digitalWrite(6, HIGH);
}


void hl0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("hl0");
  digitalWrite(6, LOW);
}


void hc1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("hc1");
  digitalWrite(5, HIGH);
}


void hc0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("hc0");
  digitalWrite(5, LOW);
}


void hr1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("hr1");
  digitalWrite(3, HIGH);
}


void hr0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("hr0");
  digitalWrite(3, LOW);
}


void ha1() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("ha1");
  digitalWrite(6, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(3, HIGH);
}


void ha0() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("ha0");
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);
}

void scoop() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  mc1();
  
  long mvs = MotorSpeed;   // note that center motor speed is in terms of mm/s
  long mvp_L = 156; // number of degrees from home
  long mvp_R = 156; // number of degrees from home
  long mvp_C = 0; // mm away from home
  
  Serial.println("Pinch Position");
  mmt(1, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp_L * 51200 * 20 / 360);  // Left Motor
  mmt(2, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp_R * 51200 * 20 / 360);  // Right Motor
  mmt(3, 1.4 * 51200 * mvs, 50000, 31, 0, 0, mvp_C * 51200 / 2);  // Center Motor
  while(rft(1, 34, 0, 0, 0, 0) != 0 || rft(2, 66, 0, 0, 0, 0) != 0 || rft(3, 34, 0, 0, 0, 0) != 0) {};  

  mc0();
}

void claw() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  mc1();
  
  long mvs = MotorSpeed;   // note that center motor speed is in terms of mm/s
  long mvp_L = 45; // number of degrees from home
  long mvp_R = 45; // number of degrees from home
  long mvp_C = 10; // mm away from home
  
  Serial.println("Pinch Position");
  mmt(1, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp_L * 51200 * 20 / 360);  // Left Motor
  mmt(2, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp_R * 51200 * 20 / 360);  // Right Motor
  mmt(3, 1.4 * 51200 * mvs, 50000, 31, 0, 0, mvp_C * 51200 / 2);  // Center Motor
  while(rft(1, 34, 0, 0, 0, 0) != 0 || rft(2, 66, 0, 0, 0, 0) != 0 || rft(3, 34, 0, 0, 0, 0) != 0) {};  

  mc0();
}

void pinch() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  mc1();
  
  long mvs = MotorSpeed;   // note that center motor speed is in terms of mm/s
  long mvp_L = 0; // number of degrees from home
  long mvp_R = 0; // number of degrees from home
  long mvp_C = 10; // mm away from home
  
  Serial.println("Pinch Position");
  mmt(1, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp_L * 51200 * 20 / 360);  // Left Motor
  mmt(2, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp_R * 51200 * 20 / 360);  // Right Motor
  mmt(3, 1.4 * 51200 * mvs, 50000, 31, 0, 0, mvp_C * 51200 / 2);  // Center Motor
  while(rft(1, 34, 0, 0, 0, 0) != 0 || rft(2, 66, 0, 0, 0, 0) != 0 || rft(3, 34, 0, 0, 0, 0) != 0) {};  

  mc0();
}

void mlh() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlh ");
  mmt(1, 1.4 * 51200 * 3, 30000, 31, 0, 1, 0);
  delay(100);
  mmt(1, 1.4 * 51200 * 3, 30000, 31, 0, 2, 0);
  while (rft(1, 0x22, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(1, 0, 50000, 31, 0, 2, 0);
  wtt(1, 0x21 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);
  Serial.println(rft(1, 0x21, 0x00, 0x00, 0x00, 0x00));
}


void mlp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlp ");
  if (mvs == 1)
  {
    mvs = gnb();
    mvp = gnb();
  }

  mmt(1, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp * 51200 * 20 / 360);
  while (rft(1, 34, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mlf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlf ");
  if (mvs == 1) mvs = gnb();
  mmt(1, 1.4 * 51200 * mvs, 30000, 10, 1, 1, 0);
  Serial.println(mvs);
  delay(200);
  mls();
}


void mlr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mlr ");
  if (mvs == 1) mvs = gnb();
  mmt(1, 1.4 * 51200 * mvs, 30000, 10, 1, 2, 0);
  Serial.println(mvs);
  delay(200);
  mls();
}


void mls() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mls");
  mmt(1, 0, 50000, 10, 1, 1, 0);
  while (rft(1, 34, 0, 0, 0, 0) != 0) {};
}


void mrh() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrh ");
  mmt(2, 1.4 * 51200 * 3, 30000, 31, 0, 1, 0);
  delay(100);
  mmt(2, 1.4 * 51200 * 3, 30000, 31, 0, 2, 0);
  while (rft(2, 0x42, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(2, 0, 50000, 31, 1, 2, 0);
  wtt(2, 0x41 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);
  Serial.println(rft(2, 0x41, 0x00, 0x00, 0x00, 0x00));
}


void mrp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrp ");
  if (mvs == 1)
  {
    mvs = gnb();
    mvp = gnb();
  }

  mmt(2, 1.4 * 51200 * mvs, 30000, 31, 0, 0, mvp * 51200 * 20 / 360);
  while (rft(2, 66, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");

  Serial.println(mvp);
}


void mrf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrf ");
  if (mvs == 1) mvs = gnb();
  mmt(2, 1.4 * 51200 * mvs, 50000, 10, 1, 1, 0);
  Serial.println(mvs);
  delay(200);
  mrs();
}


void mrr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mrr ");
  if (mvs == 1) mvs = gnb();
  mmt(2, 1.4 * 51200 * mvs, 50000, 10, 1, 2, 0);
  Serial.println(mvs);
  delay(200);
  mrs();
}


void mrs() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mrs");
  mmt(2, 0, 50000, 10, 1, 1, 0);
  while (rft(2, 34, 0, 0, 0, 0) != 0) {};
}


void mch() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mch ");
  mmt(3, 1.4 * 51200 * 5, 50000, 31, 0, 1, 0);
  delay(100);
  mmt(3, 1.4 * 51200 * 5, 50000, 31, 0, 2, 0);
  while (rft(3, 0x22, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(3, 0, 50000, 31, 0, 2, 0);
  wtt(3, 0x21 + 0x80, 0x00, 0x00, 0x00, 0x00);
  delay(100);

  //wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x03, 0x10);
  //delay(100);
  //mcp(3, 2);
  //mmt(3, 0, 50000, 15, 1, 2, 0);
  //delay(100);
  //wtt(3, 0x80 + 0x00, 0x00, 0x00, 0x03, 0x10);
  //delay(100);
  //wtt(3, 0x21 + 0x80, 0x00, 0x00, 0x00, 0x00);
  //delay(100);

  Serial.println(rft(3, 0x21, 0x00, 0x00, 0x00, 0x00));
}


void mcp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mcp ");
  if (mvs == 1)
  {
    mvs = gnb();
    mvp = gnb();
  }
  mmt(3, 1.4 * 51200 * mvs, 50000, 31, 0, 0, mvp * 51200 / 2);
  while (rft(3, 34, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mcf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mcf ");
  if (mvs == 1) mvs = gnb();
  mmt(3, 1.4 * 51200 * mvs, 50000, 10, 2, 1, 0);
  Serial.println(mvs);
  delay(1000);
  mcs();
}


void mcr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mcr ");
  if (mvs == 1) mvs = gnb();
  mmt(3, 1.4 * 51200 * mvs, 50000, 10, 2, 2, 0);
  Serial.println(mvs);
  delay(1000);
  mcs();
}


void mcs() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mcs");
  mmt(3, 0, 50000, 10, 1, 1, 0);
  while (rft(3, 34, 0, 0, 0, 0) != 0) {};
}


void mth() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mth ");
  mmt(4, 51200 * 10, 60000, 31, 28, 2, 0);
  delay(10);
  while (rft(4, 0x22 + 0x20, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(4, 0, 60000, 31, 28, 1, 0);
  delay(10);
  wtt(4, 0x21 + 0x80 + 0x20, 0x00, 0x00, 0x00, 0x00);
  delay(10);
  mmt(4, 51200 * 20, 50000, 20, 10, 0, 54.0 / 360 * 51200 * 100);  // 54.0 degrees home offset
  while (rft(4, 0x22 + 0x20, 0x00, 0x00, 0x00, 0x00) != 0) {};
  mmt(4, 0, 60000, 31, 28, 1, 0);
  delay(10);
  wtt(4, 0x21 + 0x80 + 0x20, 0x00, 0x00, 0x00, 0x00);
  delay(10);
  Serial.println(rft(4, 0x21 + 0x20, 0x00, 0x00, 0x00, 0x00));
}


void mtp(long mvs, long mvp) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mtp ");
  if (mvs == 1)
  {
    mvs = gnb();
    mvp = gnb();
  }
  mmt(4, 51200 * 2 * mvs, 60000, 31, 28, 0, mvp * 14222);
  while (rft(4, 66, 0, 0, 0, 0) != 0) {};
  Serial.print(mvs);
  Serial.print(" ");
  Serial.println(mvp);
}


void mtf(long mvs) //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mtf ");
  if (mvs == 1) mvs = gnb();
  mmt(4, 51200 * 2 * mvs, 60000, 10, 10, 1, 0);
  Serial.println(mvs);
  //delay(1000);
  //mcs();
}


void mtr(long mvs) //-----------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("mtr ");
  if (mvs == 1) mvs = gnb();
  mmt(4, 51200 * 2 * mvs, 60000, 10, 10, 2, 0);
  Serial.println(mvs);
  //delay(1000);
  //mcs();
}


void mts() //-------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mts");
  mmt(4, 0, 50000, 10, 10, 1, 0);
  while (rft(4, 66, 0, 0, 0, 0) != 0) {};
}


void io0() //--------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("io0 = ");
  Serial.println(digitalRead(A1));
}


void io1() //--------------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.print("io1 = ");
  Serial.println(digitalRead(A2));
}


void rpg()  //-----------------------------------------------------------------------------------------------------------------------------------------------
{
  for(int j= 0; j<60; j++)
  {
    mrp(10, 135);
    mlp(10, 135);
    mrp(10, 0);
    mlp(10, 0); 
  }
}


void mc1()  //-----------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mc1");
  digitalWrite(2, LOW);
  digitalWrite(A0, LOW);
}


void mc0()  //-----------------------------------------------------------------------------------------------------------------------------------------------
{
  Serial.println("mc0");
  digitalWrite(2, HIGH);
  digitalWrite(A0, HIGH);
}



void wtt(int mnb, byte add, byte by1, byte by2, byte by3, byte by4)  //----------------------------------------------------------------------------------
{
  if (mnb == 1 || mnb == 2) digitalWrite(4, LOW);
  if (mnb == 3 || mnb == 4) digitalWrite(7, LOW);
  shiftOut(11, 13, MSBFIRST, (char) add);
  shiftOut(11, 13, MSBFIRST, (char) by1);
  shiftOut(11, 13, MSBFIRST, (char) by2);
  shiftOut(11, 13, MSBFIRST, (char) by3);
  shiftOut(11, 13, MSBFIRST, (char) by4);
  if (mnb == 1 || mnb == 2) digitalWrite(4, HIGH);
  if (mnb == 3 || mnb == 4) digitalWrite(7, HIGH);
}

long rft(int mnb, byte addr, byte by1, byte by2, byte by3, byte by4)  //---------------------------------------------------------------------------------
{
  byte sta, b1r, b2r, b3r, b4r;
  long dta;
  if (mnb == 1 || mnb == 2) digitalWrite(4, LOW);
  if (mnb == 3 || mnb == 4) digitalWrite(7, LOW);

  shiftOut(11, 13, MSBFIRST, (char) addr);
  shiftOut(11, 13, MSBFIRST, (char) by1);
  shiftOut(11, 13, MSBFIRST, (char) by2);
  shiftOut(11, 13, MSBFIRST, (char) by3);
  shiftOut(11, 13, MSBFIRST, (char) by4);

  if (mnb == 1 || mnb == 2) digitalWrite(4, HIGH);
  if (mnb == 3 || mnb == 4) digitalWrite(7, HIGH);

  if (mnb == 1 || mnb == 2) digitalWrite(4, LOW);
  if (mnb == 3 || mnb == 4) digitalWrite(7, LOW);

  sta = shiftIn(12, 13, MSBFIRST);
  b1r = shiftIn(12, 13, MSBFIRST);
  b2r = shiftIn(12, 13, MSBFIRST);
  b3r = shiftIn(12, 13, MSBFIRST);
  b4r = shiftIn(12, 13, MSBFIRST);

  if (mnb == 1 || mnb == 2) digitalWrite(4, HIGH);
  if (mnb == 3 || mnb == 4) digitalWrite(7, HIGH);

  dta = b1r;
  dta = dta << 8 | b2r;
  dta = dta << 8 | b3r;
  dta = dta << 8 | b4r;
  return dta;
}

void mmt(int smn, long vmx, long amx, int irn, int ihd, int ram, long xtg)  //----------------------------------------------------------------------------------
{
  int mtu;
  if (smn == 1 || smn == 3) mtu = 0;
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
