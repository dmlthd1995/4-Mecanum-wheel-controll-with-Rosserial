//Arduino mega source code
#include <ros.h>                      // ROS 헤더
#include <geometry_msgs/Twist.h>      // geometry_msgs 헤더
#define WHEEL_RADIUS 0.08             // 휠 반경 [ m ]
#define WHEEL_SEPARATION_WIDTH 0.46   // 휠 베이스간 전폭 [ m ]
#define WHEEL_SEPARATION_LENGTH 0.40  // 휠 베이스간 전장 [ m ]
String txString = "";                 // txString 설정 및 초기화
int Tar_linear_x = 0;                 // linear x값 설정 및 초기화
int Tar_linear_y = 0;                 // linear y값 설정 및 초기화
int Tar_angular_z = 0;                // angular_z값 설정 및 초기화
double Tar_wheel_front_left, Tar_wheel_front_right, Tar_wheel_rear_left, Tar_wheel_rear_right; //구동 모터별 변수 설정
void messageCb(const geometry_msgs::Twist& twist); //geometry_msgs/Twist 설정
ros::NodeHandle nh;                   //ROS 핸들
ros::Subscriber <geometry_msgs::Twist> sub("cmd_vel", &messageCb); //Subscriber 설정

void messageCb(const geometry_msgs::Twist& twist) //geometry_msgs 처리 함수
{
  const float Tar_linear_x = twist.linear.x;      //geometry_msgs로 받은 twist.linear.x을 Tar_linear_x로 변환 및 저장
  const float Tar_linear_y = twist.linear.y;      //geometry_msgs로 받은 twist.linear.y를 Tar_linear_y로 변환 및 저장
  const float Tar_angular_z = twist.angular.z;    //geometry_msgs로 받은 twist.angular.z를 Tar_angular_z로 변환 및 저장

  // 출력값 [ rad/s ]
  Tar_wheel_front_left = (1/WHEEL_RADIUS) * (Tar_linear_x - Tar_linear_y - (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z);  //Tar_wheel_front_left값 계산 수식
  Tar_wheel_front_right = (1/WHEEL_RADIUS) * (Tar_linear_x + Tar_linear_y + (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z); //Tar_wheel_front_right값 계산 수식
  Tar_wheel_rear_left = (1/WHEEL_RADIUS) * (Tar_linear_x + Tar_linear_y - (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z);   //Tar_wheel_rear_left값 계산 수식
  Tar_wheel_rear_right = (1/WHEEL_RADIUS) * (Tar_linear_x - Tar_linear_y + (WHEEL_SEPARATION_WIDTH + WHEEL_SEPARATION_LENGTH)*Tar_angular_z);  //Tar_wheel_rear_right값 계산 수식
  Speed_send();     //Serial통신으로 각 모터별 속도값 전달
}

void Speed_send() //Serial통신으로 각 모터별 속도값을 전달하는 함수
{
  txString += '#';                  //String 시작문자 '#'
  txString += Tar_wheel_front_left; //Tar_wheel_front_left값 붙이기
  txString += ',';                  //구분자 ',' 삽입
  txString += Tar_wheel_front_right;//Tar_wheel_front_right값 붙이기

  txString += ',';                  //구분자 ',' 삽입
  txString += Tar_wheel_rear_right; //Tar_wheel_rear_right값 붙이기
  txString += ',';                  //구분자 ',' 삽입
  txString += Tar_wheel_rear_left;  //Tar_wheel_rear_left값 붙이기
  txString += '@';                  //종료문자 '@'
  Serial1.print(txString);          //String을 Serial1으로 전송
  txString = "";                    //String 초기화
}

void setup()
{
  Serial1.begin(57600); //Serial1 통신속도 57600
  nh.initNode();        //노드 실행
  nh.subscribe(sub);    //서브스크립 실행
}

void loop()
{
  nh.spinOnce();        //nh.spinOnce 실행
}
