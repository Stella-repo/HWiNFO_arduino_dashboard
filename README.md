# HWiNFO_arduino_dashboard
HWiNFO의 Shared Memory Support 기능을 사용하여 각종 정보를 받아오고 파이썬 코드를 통해 아두이노와 시리얼 통신을 하여 OLED디스플레이에 표시합니다   
푸시버튼을 이용하여 oled화면을 끄고 켤수도 있습니다

## 표시하는 정보  
* CPU   
  * CPU 로드율
  * CPU 패키지 온도
  * 수냉쿨러 수온
  * CPU 로드율 그래프
  
* GPU
  * GPU 로드율
  * NVENC 로드율
  * GPU 온도
  * GPU 로드율 그래프
  
* RAM, DISK
  * RAM 로드율
  * RAM 사용량
  * DISK 남은용량

* DISK
  * DISK 로드율
  * DISK 읽기, 쓰기 속도 (단위 : KB/s, MB/s)

* NET, FAN
  * 인터넷 보내기, 받기 속도 (단위 : Kbps, Mbps)
  * FAN RPM값
  
## 프리뷰
![preview](https://github.com/Stella-repo/HWiNFO_arduino_dashboard/blob/main/img/preview.gif?raw=true)

## 결선도   


## HWiNFO 설정방법  
최신버전 HWiNFO에서는 Shared Memory Support 기능에 제한시간이 생겼습니다  
v6.42 이하 버전을 사용하시만 제한없이 사용가능합니다  


![setting1](https://github.com/Stella-repo/HWiNFO_arduino_dashboard/blob/main/img/setting1.png?raw=true)
![setting2](https://github.com/Stella-repo/HWiNFO_arduino_dashboard/blob/main/img/setting2.png?raw=true)
![setting3](https://github.com/Stella-repo/HWiNFO_arduino_dashboard/blob/main/img/setting3.png?raw=true)

Physical Memory Used - Multiply → 0.00097(= /1024) (MB → GB)  
Drive Total Activity - Read Rate, Write Rate → 1024 (MB/s → KB/s)  
Network Current DL, UP rate - Multiply → 8 (KB/s → Kbps)  

## 사용한 외부 라이브러리
* [u8glib](https://github.com/olikraus/u8glib)
* [I2CMux](https://github.com/alvaroferran/I2C-multiplexer)

## 참고한 블로그    
https://clemencyking.tistory.com/20
