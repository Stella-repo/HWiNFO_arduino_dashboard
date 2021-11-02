# HWiNFO_arduino_dashboard
HWiNFO의 Shared Memory Support 기능을 사용하여 각종 정보를 받아오고 파이썬 코드를 통해 아두이노와 시리얼 통신을 하여 OLED디스플레이에 표시합니다   

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
  * FAN rpm값
  
## 프리뷰

## 

## 설정방법

## 사용한 외부 라이브러리
* [u8glib](https://github.com/olikraus/u8glib)
* [I2CMux](https://github.com/alvaroferran/I2C-multiplexer)

## 참고한 블로그    
https://clemencyking.tistory.com/20
