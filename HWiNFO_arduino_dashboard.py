import os
import psutil
import math
import serial
import threading
from datetime import datetime
import time

ser = serial.Serial(port='COM3', baudrate=9600) #아두이노와 연결된 포트에 맞게 수정하기

def hwinfo():
	#################### 디스크 남은량 ####################
	cdr_abl = str(math.floor(psutil.disk_usage('c:')[2]/2.**30))
	ddr_abl = str(math.floor(psutil.disk_usage('d:')[2]/2.**30))
	#################### 디스크 남은량 ####################
	
	#################### HWiNFO 레지스트리값 ####################
	reg = os.popen('reg query HKEY_CURRENT_USER\SOFTWARE\HWiNFO64\VSB').readlines() #레지스트리로 센서값 불러오기
	mem_usg = str(reg[3][24:reg[3].rfind('GB')-1]) #불러온 레지스트리값의 3번째 줄에서 24번째 글자부터 GB글자 전까지 문자열 잘라내기
	mem_lod = str(math.ceil(float(reg[6][24:reg[6].rfind('%')-1]))) #문자열 편집후 실수로 소수점 둘쨰자리에서 변환하고 올림하기

	cpu_usg = str(math.ceil(float(reg[9][24:reg[9].rfind('%')-1])))
	cpu_tmp = str(reg[12][24:reg[12].rfind('°C')-1])

	cpu_fan = str(reg[18][24:reg[18].rfind('RPM')-1])
	fnt_fan = str(reg[21][24:reg[21].rfind('RPM')-1])

	t_sen = str(math.ceil(float(reg[24][24:reg[24].rfind('°C')-3])))

	ddr_act = str(math.ceil(float(reg[27][24:reg[27].rfind('%')-1])))
	ddr_red = float(reg[30][24:reg[30].rfind('KB/s')-1])
	ddr_wrt = float(reg[33][25:reg[33].rfind('KB/s')-1])
	cdr_act = str(math.ceil(float(reg[36][25:reg[36].rfind('%')-1])))
	cdr_red = float(reg[39][25:reg[39].rfind('KB/s')-1])
	cdr_wrt = float(reg[42][25:reg[42].rfind('KB/s')-1])

	gpu_tmp = str(reg[45][25:reg[45].rfind('°C')-1])
	gpu_fan = str(reg[48][25:reg[48].rfind('RPM')-1])
	gpu_cor = float(reg[51][25:reg[51].rfind('%')-1])
	gpu_vid = float(reg[54][25:reg[54].rfind('%')-1])
	gpu_d3d = float(reg[57][25:reg[57].rfind('%')-1])
	gpu_dec = float(reg[60][25:reg[60].rfind('%')-1])
	gpu_enc = float(reg[63][25:reg[63].rfind('%')-1])

	int_dlr = float(reg[66][25:reg[66].rfind('Kbps')-1])
	int_upr = float(reg[69][25:reg[69].rfind('Kbps')-1])
	#################### HWiNFO 레지스트리값 ####################
	
	#################### GPU 최고 사용량 판단 및 값 반올림 ####################
	gpu_usg = []
	gpu_usg.extend([gpu_cor, gpu_vid, gpu_d3d, gpu_dec, gpu_enc])
	max_gpu_usg = math.ceil((max(gpu_usg)))
		#윈도우에서는 GPU의 Core, Video Engine, D3D, Video Decode, Video Encode 로드율 중에서 제일 큰 값을 출쳑함
	gpu_enc = math.ceil(gpu_enc)
	#################### GPU 최고 사용량 판단 및 값 반올림 ####################
	
	#################### 디스크, 인터넷 사용량 및 단위 ####################
	##D드라이브
	if ddr_red < 999: #999넘는 숫자는 올림하면 1000이 되기때문에 999보다 작은수를 지정함
		ddr_red_unit = 'K'
		if ddr_red < 100:
			ddr_red = str(ddr_red) #100보다 작으면 소수점 첫째자리까지 표시
		else:
			ddr_red = str(math.ceil(ddr_red)) #100이상이면 소수점 표시 안함
	else:
		ddr_red = ddr_red/1000
		ddr_red_unit = 'M'
		if ddr_red < 100:
			ddr_red = str(round(ddr_red, 1))
		else:
			ddr_red = str(math.ceil(ddr_red))
	
	if ddr_wrt < 999:
		ddr_wrt_unit = 'K'
		if ddr_wrt < 100:
			ddr_wrt = str(ddr_wrt)
		else:
			ddr_wrt = str(math.ceil(ddr_wrt))		
	else:
		ddr_wrt = ddr_wrt/1000
		ddr_wrt_unit = 'M'
		if ddr_wrt < 100:
			ddr_wrt = str(round(ddr_wrt, 1))
		else:
			ddr_wrt = str(math.ceil(ddr_wrt))
	
	##C드라이브
	if cdr_red < 999:
		cdr_red_unit = 'K'
		if cdr_red < 100:
			cdr_red = str(cdr_red)
		else:
			cdr_red = str(math.ceil(cdr_red))		
	else:
		cdr_red = cdr_red/1000
		cdr_red_unit = 'M'
		if cdr_red < 100:
			cdr_red = str(round(cdr_red, 1))
		else:
			cdr_red = str(math.ceil(cdr_red))

	if cdr_wrt < 999:
		cdr_wrt_unit = 'K'
		if cdr_wrt < 100:
			cdr_wrt = str(cdr_wrt)
		else:
			cdr_wrt = str(math.ceil(cdr_wrt))		
	else:
		cdr_wrt = cdr_wrt/1000
		cdr_wrt_unit = 'M'
		if cdr_wrt < 100:
			cdr_wrt = str(round(cdr_wrt, 1))
		else:
			cdr_wrt = str(math.ceil(cdr_wrt))
			
	##인터넷
	if int_upr < 999:
		int_upr_unit = 'K'
		if int_upr < 100:
			int_upr = str(int_upr)
		else:
			int_upr = str(math.ceil(int_upr))		
	else:
		int_upr = int_upr/1000
		int_upr_unit = 'M'
		if int_upr < 100:
			int_upr = str(round(int_upr, 1))
		else:
			int_upr = str(math.ceil(int_upr))

	if int_dlr < 999:
		int_dlr_unit = 'K'
		if int_dlr < 100:
			int_dlr = str(int_dlr)
		else:
			int_dlr = str(math.ceil(int_dlr))		
	else:
		int_dlr = int_dlr/1000
		int_dlr_unit = 'M'
		if int_dlr < 100:
			int_dlr = str(round(int_dlr, 1))
		else:
			int_dlr = str(math.ceil(int_dlr))
	#################### 디스크, 인터넷 사용량 및 단위 ####################
	
	send_data = str(mem_usg) + '/' + str(mem_lod) + '/' + str(cpu_usg) + '/' + str(cpu_tmp) + '/' + str(cpu_fan) + '/' + str(fnt_fan) + '/' + str(t_sen) + '/' + str(ddr_act) + '/' + str(ddr_red) + '/' + str(ddr_wrt) + '/' + str(ddr_red_unit) + '/' + str(ddr_wrt_unit) + '/' + str(cdr_act) + '/' + str(cdr_red) + '/' + str(cdr_wrt) + '/' + str(cdr_red_unit) + '/' + str(cdr_wrt_unit) +'/' + str(gpu_tmp) + '/' + str(gpu_fan) + '/' + str(max_gpu_usg) +'/' + str(gpu_enc) + '/' + str(int_upr) + '/' + str(int_dlr) + '/' + str(int_upr_unit)+ '/' +  str(int_dlr_unit) + '/' + str(cdr_abl) + '/' + str(ddr_abl) + '/' + '>'
	print(datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f'))
	print(send_data.encode())
	
	ser.write(send_data.encode()) #아두이노로 전송


while True:
	threading.Thread(target=hwinfo).start() #쓰레딩 안하고 그냥 1초쉬면 코드 실행시간까지 겹쳐서 재대로 1초마다 실행이 안됨
	time.sleep(1)
