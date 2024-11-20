#define STEP_PIN 2
#define DIR_PIN 3
#define ENABLE_PIN 4

#define STEP_PIN1 5
#define DIR_PIN1 6
#define ENABLE_PIN1 7

#define STEP_PIN_MAN 8
#define DIR_PIN_MAN 9
#define ENABLE_PIN_MAN 10

#define OUT_1_VERT 40//up /orange 3
#define OUT_2_VERT 41//back/ red 1

#define OUT_1_GOR 24
#define OUT_2_GOR 25

#define time_motor 2
#define time_motor_man 1
#define time_vert 6150
#define time_gor 8000

#define reset_button 47
#define sensor 12
#define sensor1 13
#define sensor_man 37

int size = time_vert+4300;
int kvadro = time_vert + 3250;
bool repeat_flag = false;
int dist = round(2250/0.706858);
int dist1 = round(2250/0.706858);
int dist_man = 5450;
int dist_man_second = 2020;
int to_st = 350;

void setup() {
  pinMode(sensor, INPUT_PULLUP);
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor_man, INPUT_PULLUP);
  pinMode(reset_button, INPUT_PULLUP);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  pinMode(STEP_PIN1, OUTPUT);
  pinMode(DIR_PIN1, OUTPUT);
  pinMode(ENABLE_PIN1, OUTPUT);

  pinMode(STEP_PIN_MAN, OUTPUT);
  pinMode(DIR_PIN_MAN, OUTPUT);
  pinMode(ENABLE_PIN_MAN, OUTPUT);

  pinMode(OUT_1_GOR, OUTPUT);
  pinMode(OUT_2_GOR, OUTPUT);

  pinMode(OUT_1_VERT, OUTPUT);
  pinMode(OUT_2_VERT, OUTPUT);


  digitalWrite(OUT_1_GOR, 0);
  digitalWrite(OUT_2_GOR, 0);

  digitalWrite(OUT_1_VERT, 0);
  digitalWrite(OUT_2_VERT, 0);

  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(ENABLE_PIN1, LOW);
  digitalWrite(ENABLE_PIN_MAN, LOW);
  Serial.begin(9600);
}

void chick(){
  delay(200);
  digitalWrite(OUT_1_VERT, 0);
  digitalWrite(OUT_2_VERT, 1);
  delay(500);
  digitalWrite(OUT_1_VERT, 1);
  digitalWrite(OUT_2_VERT, 0);
  delay(500);
  digitalWrite(OUT_1_VERT, 0);
  digitalWrite(OUT_2_VERT, 0);
}

void input_man(int f = 0, int this_time_gor = time_gor){
  
  Serial.println("вставляем");
  digitalWrite(OUT_1_GOR, 1);
  digitalWrite(OUT_2_GOR, 0);
  delay(this_time_gor);
  digitalWrite(OUT_1_GOR, 0);
  digitalWrite(OUT_2_GOR, 0);
  
  if (f == 1){
    digitalWrite(OUT_1_VERT, 1);
    digitalWrite(OUT_2_VERT, 0);
    delay(time_vert);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
  else if (f == 2){
    digitalWrite(OUT_1_VERT, 1);
    digitalWrite(OUT_2_VERT, 0);
    delay(size);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
  else if (f == 3){
    digitalWrite(OUT_1_VERT, 1);
    digitalWrite(OUT_2_VERT, 0);
    delay(kvadro+1500);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
  else if (f == -1){
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 1);
    delay(time_vert);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
  else if (f == -2){
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 1);
    delay(size);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
}

void output_man(int f = 0, int this_time_gor = time_gor){
  Serial.println("закручиваем");
  digitalWrite(OUT_1_GOR, 0);
  digitalWrite(OUT_2_GOR, 1);
  delay(this_time_gor);
  digitalWrite(OUT_1_GOR, 0);
  digitalWrite(OUT_2_GOR, 0);
  if (f == 1){
    digitalWrite(OUT_1_VERT, 1);
    digitalWrite(OUT_2_VERT, 0);
    delay(time_vert);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
  else if (f == 2){
    digitalWrite(OUT_1_VERT, 1);
    digitalWrite(OUT_2_VERT, 0);
    delay(size);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);
  }
  else if (f == -1){
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 1);
    delay(time_vert);
    digitalWrite(OUT_1_VERT, 0);
    digitalWrite(OUT_2_VERT, 0);    
  }
}

void unwinding(){
  Serial.println("раскручиваем полностью");
  digitalWrite(OUT_1_GOR, 0);
  digitalWrite(OUT_2_GOR, 1);
 
  delay(4000);
  digitalWrite(OUT_1_VERT, 0);
  digitalWrite(OUT_2_VERT, 1);
  
  delay(kvadro+10); 
  digitalWrite(OUT_1_GOR, 1);
  digitalWrite(OUT_2_GOR, 0);
  delay(2000);
  digitalWrite(OUT_1_GOR, 0);
  digitalWrite(OUT_2_GOR, 0);
  digitalWrite(OUT_1_VERT, 1);
  digitalWrite(OUT_2_VERT, 0);
  delay(kvadro);
  digitalWrite(OUT_1_VERT, 0);
  digitalWrite(OUT_2_VERT, 0);


}

void move_to_box(){
  // ----Мотор на манипуляторе------
    // Задаем направление вращения

  while (digitalRead(sensor_man)) {
      digitalWrite(DIR_PIN_MAN, LOW); 
      // digitalWrite(ENABLE_PIN_MAN, LOW); 
      digitalWrite(STEP_PIN_MAN, HIGH);
      delay(time_motor_man);
      digitalWrite(STEP_PIN_MAN, LOW);
      delay(time_motor_man);
    }

}

void loop() {
 
  if (!digitalRead(reset_button)){
    repeat_flag = true;
  }

  if (repeat_flag) {
    digitalWrite(ENABLE_PIN_MAN, LOW);
    // -----------Зажим------------
    digitalWrite(DIR_PIN, LOW);   
    digitalWrite(ENABLE_PIN, LOW);         
    for (int i = 0; i < dist; i++) {  
      digitalWrite(STEP_PIN, HIGH);
      delay(time_motor);
      digitalWrite(STEP_PIN, LOW);
      delay(time_motor);
    }
    digitalWrite(ENABLE_PIN, HIGH);  // Выключаем мотор
    // ---------2 зажим----------
    digitalWrite(DIR_PIN1, LOW);   
    digitalWrite(ENABLE_PIN1, LOW);         
    for (int i = 0; i < dist1; i++) {  
      digitalWrite(STEP_PIN1, HIGH);
      delay(time_motor);
      digitalWrite(STEP_PIN1, LOW);
      delay(time_motor);
    }
    digitalWrite(ENABLE_PIN1, HIGH);  // Выключаем мотор

    // ---------МАНИПУЛЯТОР-----------

    // раскручиваем
   unwinding();

    // ----Мотор на манипуляторе------
    for (int i = 0; i <= 10; ++i){
      move_to_box();
    }

    // ---------вставляем--------
   input_man(1);

    // ---------вынимаем--------
    output_man();
    
    //---------уезжаем---------
    digitalWrite(DIR_PIN_MAN, HIGH);            //Задаем направление вращения
    for (int i = 0; i < dist_man; i++) {  // dist_man - 1 расстояние до магазина
      digitalWrite(STEP_PIN_MAN, HIGH);
      delay(time_motor_man);
      digitalWrite(STEP_PIN_MAN, LOW);
      delay(time_motor_man);
    }
    // digitalWrite(ENABLE_PIN_MAN, HIGH);  //Выключаем мотор

    // ---------вставляем--------
    input_man(-2, to_st);

    // ---------подождем--------
    delay(500);

    // ---------вынимаем--------
    output_man(0);
    
    //-ещё чуть-чуть отъезжаем--
    // digitalWrite(ENABLE_PIN_MAN, HIGH); 
    digitalWrite(DIR_PIN_MAN, HIGH);            //Задаем направление вращения
    for (int i = 0; i < dist_man_second; i++) {   // dist_man_second - 2 расстояние до магазина
      digitalWrite(STEP_PIN_MAN, HIGH); 
      delay(time_motor_man);
      digitalWrite(STEP_PIN_MAN, LOW);
      delay(time_motor_man);
    }
    // digitalWrite(ENABLE_PIN_MAN, HIGH);  //Выключаем мотор

    // ---------вставляем--------
    input_man(3, to_st+2450);

    // ---------подождем--------
    delay(500);

    // ---------вынимаем--------
    // output_man(2, to_st);


    // ----Мотор на манипуляторе------
    digitalWrite(DIR_PIN_MAN, LOW);            //Задаем направление вращения
    for (int i = 0; i < dist_man_second+dist_man; i++) {  
      digitalWrite(STEP_PIN_MAN, HIGH);
      delay(time_motor_man);
      digitalWrite(STEP_PIN_MAN, LOW);
      delay(time_motor_man);
    }

    // ---------вставляем--------
    input_man(0, time_gor-to_st);

    // ---------вынимаем--------
    output_man(-1);

    //---------уезжаем---------
    
    digitalWrite(ENABLE_PIN_MAN, HIGH);  //Выключаем мотор
    repeat_flag = false;

  }
  while (digitalRead(sensor1)) {
     digitalWrite(ENABLE_PIN, LOW);
     digitalWrite(DIR_PIN, HIGH);
     digitalWrite(STEP_PIN, HIGH);
     delay(time_motor);
     digitalWrite(STEP_PIN, LOW);
     delay(time_motor);
   }  
   digitalWrite(ENABLE_PIN, HIGH);
  
  while (digitalRead(sensor)) {
    digitalWrite(ENABLE_PIN1, LOW);
    digitalWrite(DIR_PIN1, HIGH);
    digitalWrite(STEP_PIN1, HIGH);
    delay(time_motor);
    digitalWrite(STEP_PIN1, LOW);
    delay(time_motor);
  } 
  digitalWrite(ENABLE_PIN1, HIGH);
}
