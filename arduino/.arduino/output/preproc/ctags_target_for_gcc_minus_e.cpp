# 1 "C:\\Users\\ellan\\Documents\\iesl1001\\arduino\\zumoBatteriV2\\zumoBatteriV2.ino"
# 2 "C:\\Users\\ellan\\Documents\\iesl1001\\arduino\\zumoBatteriV2\\zumoBatteriV2.ino" 2


Zumo32U4Encoders encoder;
Zumo32U4Motors motors;
Zumo32U4OLED display;

float q, i, totDiss;
bool A = 1;
unsigned long currentMillis, sMillis, t;
const int speedCheck = 250;
const int O = 12;
int screenCount = 1;

float distance()
{
    float L = encoder.getCountsLeft();
    float R = encoder.getCountsRight();
    if (A == 1)
    {
        i = sqrt(L * L + R * R);
        A = 0;
        t = millis();
    }
    if ((millis() - t) >= speedCheck)
    {
        q = sqrt(L * L + R * R);
        A = 1;
    }
    float dis = ((((i - q) / (910)) * O)>0?(((i - q) / (910)) * O):-(((i - q) / (910)) * O));
    return dis;
}

float toDistance(float y)
{
    totDiss = (totDiss + y)/100; //totDiss + (y/100)
    return totDiss;
}


float speed(float x)
{
    float hastighet = x * ( 1000/speedCheck);
    return hastighet;
}
void screen1(){
    display.clear();
    display.gotoXY(0,0);
    display.print((reinterpret_cast<const __FlashStringHelper *>(
# 49 "C:\\Users\\ellan\\Documents\\iesl1001\\arduino\\zumoBatteriV2\\zumoBatteriV2.ino" 3
                 (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 49 "C:\\Users\\ellan\\Documents\\iesl1001\\arduino\\zumoBatteriV2\\zumoBatteriV2.ino"
                 "Speed:"
# 49 "C:\\Users\\ellan\\Documents\\iesl1001\\arduino\\zumoBatteriV2\\zumoBatteriV2.ino" 3
                 ); &__c[0];}))
# 49 "C:\\Users\\ellan\\Documents\\iesl1001\\arduino\\zumoBatteriV2\\zumoBatteriV2.ino"
                 )));
    display.print(speed(distance()));
}

void screen2(){
    display.clear();
    display.gotoXY(0,32);
    display.print("Distance:");
    display.print("  ");
    display.print(toDistance(distance()));
}

void Oled() {
    const int screenTime = 5000;
    if ((millis()-sMillis)>= screenTime){
        screenCount++;
    }
    if (screenCount == 1){
        screen1();
    }
    else if (screenCount == 2){
        screen2();
    }
    else {
        screenCount = 0;
    }
}

void setup()
{
    Serial.begin(9600);
    display.clear();
}

void loop()
{
    Oled();
    motors.setSpeeds(200, 200);
    // distance();
    if ((millis() - currentMillis) >= speedCheck)
    {
        float d = distance();
        //Serial.println(d);
        currentMillis = millis();
        Serial.println(speed(distance()));
        Serial.print("totaldiss");
        Serial.println(toDistance(d));
    }
}
