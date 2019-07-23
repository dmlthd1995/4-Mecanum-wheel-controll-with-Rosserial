//Makeblock orion board source code
#include "MeOrion.h" //MeOrin 헤더

MeEncoderNew motor1(0x09, SLOT1); //motor1 모터드라이브 주소 설정
MeEncoderNew motor2(0x09, SLOT2); //motor2 모터드라이브 주소 설정
MeEncoderNew motor3(0x0a, SLOT1); //motor3 모터드라이브 주소 설정
MeEncoderNew motor4(0x0a, SLOT2); //motor4 모터드라이브 주소 설정

float motor1speed = 0;                  //motor1speed 변수 설정 및 초기화
float motor2speed = 0;                  //motor2speed 변수 설정 및 초기화
float motor3speed = 0;                  //motor3speed 변수 설정 및 초기화
float motor4speed = 0;                  //motor4speed 변수 설정 및 초기화
bool bRxStart;                          //String 검출을 위한 bool
String rxString = "";                   //String 초기화
signed char Martix[4] = {1, -1, -1, 1}; //장착된 모터의 방향을 맞춰주기위한 배열

void motorprocess()                     //모터 구동 프로세스
{
  motor1speed = motor1speed * Martix[0];//motor1speed*1
  motor2speed = motor2speed * Martix[1];//motor2speed*-1
  motor3speed = motor3speed * Martix[2];//motor3speed*-1
  motor4speed = motor4speed * Martix[3];//motor4speed*1
  motor1.runSpeed(motor1speed, 0);      //motor1 구동
  motor2.runSpeed(motor2speed, 0);      //motor2 구동
  motor3.runSpeed(motor3speed, 0);      //motor3 구동
  motor4.runSpeed(motor4speed, 0);      //motor4 구동
  if (motor1speed == 0 && motor2speed == 0 && motor3speed == 0 && motor4speed == 0) //모든 모터 속도값이 0이면 정지
  {
    motor1.runSpeed(0, 1);
    motor2.runSpeed(0, 1);
    motor3.runSpeed(0, 1);
    motor4.runSpeed(0, 1);
  }
}

void setup()
{
  motor1.begin();     //motor1 시작
  motor2.begin();     //motor2 시작
  motor3.begin();     //motor3 시작
  motor4.begin();     //motor4 시작
  delay(10);          //10ms 딜레이
  motor1.setMode(1);  //0:I2C_MODE;1:PWM_MODE;2:PWM_I2C_PWM;
  motor2.setMode(2);  //0:I2C_MODE;1:PWM_MODE;2:PWM_I2C_PWM;
  motor3.setMode(1);  //0:I2C_MODE;1:PWM_MODE;2:PWM_I2C_PWM;
  motor4.setMode(2);  //0:I2C_MODE;1:PWM_MODE;2:PWM_I2C_PWM;
  motor1.runSpeed(0); //motor1 초기화
  motor2.runSpeed(0); //motor2 초기화
  motor3.runSpeed(0); //motor3 초기화
  motor4.runSpeed(0); //motor4 초기화
  Serial.begin(57600);//Serial 통신속도 57600 설정
}

void loop()
{
  if (Serial.available() > 0) //수신된 Serial값이 있으면
  {
    char c = Serial.read();   //Serial값을 c변수에 저장
    if (bRxStart == false)
    {
      //시작문자 검출
      if (c == '#') bRxStart = true;
    }
    else
    {
      if (c == '@')
      {
        //종료문자 검출시 String 초기화
        dataParsing(rxString);
        delay(10);
        bRxStart = false;
        rxString = "";
      }
      else
      {
      //추출값 저장
      rxString += c;
      }
    }
    motorprocess(); //모터 구동 프로세스
  }
}

void dataParsing(String str) //각속도 값 추출 함수
{
  int index1 = str.indexOf(',');                //첫번째 ',' index1주소 설정
  int index2 = str.indexOf(',', index1 + 1);    //두번째 ',' index2주소 설정
  int index3 = str.indexOf(',', index2 + 1);    //세번째 ',' index3주소 설정
  int index4 = str.indexOf('@', index3 + 1);    //종료문자 '@' index4주소 설정
  String motor1_val = str.substring(0, index1); //0부터 index1까지 motor1_val에 저장
  String motor2_val = str.substring(index1 + 1, index2); //index1+1부터 index2까지 motor2_val에 저장
  String motor3_val = str.substring(index2 + 1, index3); //index2+1부터 index3까지 motor3_val에 저장
  String motor4_val = str.substring(index3 + 1, index4); //index3+1부터 index4까지 motor4_val에 저장
  motor1speed = motor1_val.toFloat();           //motor1_val값 정수형으로 변환
  motor2speed = motor2_val.toFloat();           //motor2_val값 정수형으로 변환
  motor3speed = motor3_val.toFloat();           //motor3_val값 정수형으로 변환
  motor4speed = motor4_val.toFloat();           //motor4_val값 정수형으로 변환
}
