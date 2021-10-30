#first git test  
import os
import psutil
import math
import serial
import threading
from datetime import datetime
import time
import threading

ser = serial.Serial(port='COM3', baudrate=9600)

def hwinfo():
	
	#################### 디스크 남은량 ####################
	cdr_abl = str(math.floor(psutil.disk_usage('c:')[2]/2.**30))
	ddr_abl = str(math.floor(psutil.disk_usage('d:')[2]/2.**30))
	#################### 디스크 남은량 ####################
	
	#################### HWiufo 레지스트리값 ####################
	reg = os.popen('reg query HKEY_CURRENT_USER\SOFTWARE\HWiNFO64\VSB').readlines()
	mem_abl = str(reg[3][24:reg[3].rfind('GB')-1])
	mem_lod = str(math.ceil(float(reg[6][24:reg[6].rfind('%')-1])))

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
	#################### HWiufo 레지스트리값 ####################
	
	
	#################### GPU 최고 사용량 계산 ####################
	gpu_usg = []
	gpu_usg.extend([gpu_cor, gpu_vid, gpu_d3d, gpu_dec, gpu_enc])
	max_gpu_usg = math.ceil((max(gpu_usg)))
	gpu_enc = math.ceil(gpu_enc)
	#################### GPU 최고 사용량 계산 ####################
	
	#################### 디스크, 인터넷 사용량 단위 ####################
	##D드라이브
	if ddr_red < 999:
		ddr_red_unit = 'K'
		if ddr_red < 100:
			ddr_red = str(ddr_red)
		else:
			ddr_red = str(math.ceil(ddr_red))		
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
			
	##C인터넷
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
	#################### 디스크, 인터넷 사용량 단위 ####################
	
	send_data = str(mem_abl) + '/' + str(mem_lod) + '/' + str(cpu_usg) + '/' + str(cpu_tmp) + '/' + str(cpu_fan) + '/' + str(fnt_fan) + '/' + str(t_sen) + '/' + str(ddr_act) + '/' + str(ddr_red) + '/' + str(ddr_wrt) + '/' + str(ddr_red_unit) + '/' + str(ddr_wrt_unit) + '/' + str(cdr_act) + '/' + str(cdr_red) + '/' + str(cdr_wrt) + '/' + str(cdr_red_unit) + '/' + str(cdr_wrt_unit) +'/' + str(gpu_tmp) + '/' + str(gpu_fan) + '/' + str(max_gpu_usg) +'/' + str(gpu_enc) + '/' + str(int_upr) + '/' + str(int_dlr) + '/' + str(int_upr_unit)+ '/' +  str(int_dlr_unit) + '/' + str(cdr_abl) + '/' + str(ddr_abl) + '/' + '>'
	print(datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f'))
	print(send_data.encode())
	
	ser.write(send_data.encode())

while True:
	threading.Thread(target=hwinfo).start()
	time.sleep(1)
