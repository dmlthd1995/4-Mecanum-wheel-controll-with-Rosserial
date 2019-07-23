# ■ Ros_serial_arduino_for-mecanum_wheel
Arduino mega, orion board based 4 macanum wheel controll with Rosserial

## ●4-메카넘휠의 구동 원리
![image](https://user-images.githubusercontent.com/47591345/61585646-ef9f8400-ab9b-11e9-9f16-69dfa768ac67.png)
***
## ●Makeblock Orion board source code
![image](https://user-images.githubusercontent.com/47591345/61575495-88d08b00-ab07-11e9-9902-d7ff17361987.png)
![image](https://user-images.githubusercontent.com/47591345/61575497-8b32e500-ab07-11e9-9502-5f3c8ed22fd6.png)
***
## ●Arduino mega source code
![image](https://user-images.githubusercontent.com/47591345/61575498-8e2dd580-ab07-11e9-8643-ceaf6b044970.png)
![image](https://user-images.githubusercontent.com/47591345/61696209-ebc45b00-ad6f-11e9-8814-ff437c86a412.png)


***
## ●실행모습
![image](https://user-images.githubusercontent.com/47591345/61575514-bc131a00-ab07-11e9-8c3e-f01eedcd168f.png)
***
## ●rostopic list 확인 방법
$ rostopic list
***
## ●rostopic list
/cmd_vel
***
## ●명령어
$ roscore
$ rosrun rosserial_python serial_node.py /dev/ttyACM0  (연결 안될 시 물리포트넘버를 확인해 주세요.)
$ rostopic pub -1 /cmd_vel geometry_msgs/Twist '[x, y, 0]' '[0, 0, z]' (x, y, z에 임의값 입력하시면 됩니다.)
***
## ●Example
### ○대각선
$ rostopic pub -1 /cmd_vel geometry/Twist '[1.5, 1.5, 0]' '[0, 0, 0]'
$ rostopic pub -1 /cmd_vel geometry/Twist '[-1.5, -1.5, 0]' '[0, 0, 0]’

### ○전진, 후진, 좌측, 우측, 회전
rostopic pub -1 /cmd_vel geometry/Twist '[1.5, 0, 0]' '[0, 0, 0]'
rostopic pub -1 /cmd_vel geometry/Twist '[-1.5, 0, 0]' '[0, 0, 0]'
rostopic pub -1 /cmd_vel geometry/Twist '[0, 1.5, 0]' '[0, 0, 0]'
rostopic pub -1 /cmd_vel geometry/Twist '[0, -1.5, 0]' '[0, 0, 0]'
rostopic pub -1 /cmd_vel geometry/Twist '[0, 0, 0]' '[0, 0, 3]'

### ○원
rostopic pub -1 /cmd_vel geometry/Twist '[1.5, 0, 0]' '[0, 0, 2]’

### 중심점 바라보면서 원그리기
rostopic pub -1 /cmd_vel geometry/Twist '[0, 1.5, 0]' '[0, 0, 2]'
***
## ●4-마카넘휠 모바일 플랫폼 외형
![image](https://user-images.githubusercontent.com/47591345/61575598-760a8600-ab08-11e9-99c9-1270fb560e30.png)
![image](https://user-images.githubusercontent.com/47591345/61575599-799e0d00-ab08-11e9-9c98-96c0aa66683d.png)
![image](https://user-images.githubusercontent.com/47591345/61575602-7dca2a80-ab08-11e9-8b31-99a4ee45b154.png)
