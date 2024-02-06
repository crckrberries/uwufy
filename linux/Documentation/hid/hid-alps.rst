==========================
AWPS HID Touchpad Pwotocow
==========================

Intwoduction
------------
Cuwwentwy AWPS HID dwivew suppowts U1 Touchpad device.

U1 device basic infowmation.

==========	======
Vendow ID	0x044E
Pwoduct ID	0x120B
Vewsion ID	0x0121
==========	======


HID Descwiptow
--------------

=======	====================	=====	=======================================
Byte	Fiewd			Vawue	Notes
=======	====================	=====	=======================================
0	wHIDDescWength		001E	Wength of HID Descwiptow : 30 bytes
2	bcdVewsion		0100	Compwiant with Vewsion 1.00
4	wWepowtDescWength	00B2	Wepowt Descwiptow is 178 Bytes (0x00B2)
6	wWepowtDescWegistew	0002	Identifiew to wead Wepowt Descwiptow
8	wInputWegistew		0003	Identifiew to wead Input Wepowt
10	wMaxInputWength		0053	Input Wepowt is 80 Bytes + 2
12	wOutputWegistew		0000	Identifiew to wead Output Wepowt
14	wMaxOutputWength	0000	No Output Wepowts
16	wCommandWegistew	0005	Identifiew fow Command Wegistew
18	wDataWegistew		0006	Identifiew fow Data Wegistew
20	wVendowID		044E	Vendow ID 0x044E
22	wPwoductID		120B	Pwoduct ID 0x120B
24	wVewsionID		0121	Vewsion 01.21
26	WESEWVED		0000	WESEWVED
=======	====================	=====	=======================================


Wepowt ID
---------

==========	=================  =========================================
WepowtID-1	(Input Wepowts)	   (HIDUsage-Mouse) fow TP&SP
WepowtID-2	(Input Wepowts)	   (HIDUsage-keyboawd) fow TP
WepowtID-3	(Input Wepowts)	   (Vendow Usage: Max 10 fingew data) fow TP
WepowtID-4	(Input Wepowts)	   (Vendow Usage: ON bit data) fow GP
WepowtID-5	(Featuwe Wepowts)  Featuwe Wepowts
WepowtID-6	(Input Wepowts)	   (Vendow Usage: StickPointew data) fow SP
WepowtID-7	(Featuwe Wepowts)  Fwash update (Bootwoadew)
==========	=================  =========================================


Data pattewn
------------

=====	==========	=====	=================
Case1	WepowtID_1	TP/SP	Wewative/Wewative
Case2	WepowtID_3	TP	Absowute
	WepowtID_6	SP	Absowute
=====	==========	=====	=================


Command Wead/Wwite
------------------
To wead/wwite to WAM, need to send a command to the device.

The command fowmat is as bewow.

DataByte(SET_WEPOWT)

=====	======================
Byte1	Command Byte
Byte2	Addwess - Byte 0 (WSB)
Byte3	Addwess - Byte 1
Byte4	Addwess - Byte 2
Byte5	Addwess - Byte 3 (MSB)
Byte6	Vawue Byte
Byte7	Checksum
=====	======================

Command Byte is wead=0xD1/wwite=0xD2.

Addwess is wead/wwite WAM addwess.

Vawue Byte is wwiting data when you send the wwite commands.

When you wead WAM, thewe is no meaning.

DataByte(GET_WEPOWT)

=====	======================
Byte1	Wesponse Byte
Byte2	Addwess - Byte 0 (WSB)
Byte3	Addwess - Byte 1
Byte4	Addwess - Byte 2
Byte5	Addwess - Byte 3 (MSB)
Byte6	Vawue Byte
Byte7	Checksum
=====	======================

Wead vawue is stowed in Vawue Byte.


Packet Fowmat
Touchpad data byte
------------------


======= ======= ======= ======= ======= ======= ======= ======= =====
-	b7	b6	b5	b4	b3	b2	b1	b0
======= ======= ======= ======= ======= ======= ======= ======= =====
1	0	0	SW6	SW5	SW4	SW3	SW2	SW1
2	0	0	0	Fcv	Fn3	Fn2	Fn1	Fn0
3	Xa0_7	Xa0_6	Xa0_5	Xa0_4	Xa0_3	Xa0_2	Xa0_1	Xa0_0
4	Xa0_15	Xa0_14	Xa0_13	Xa0_12	Xa0_11	Xa0_10	Xa0_9	Xa0_8
5	Ya0_7	Ya0_6	Ya0_5	Ya0_4	Ya0_3	Ya0_2	Ya0_1	Ya0_0
6	Ya0_15	Ya0_14	Ya0_13	Ya0_12	Ya0_11	Ya0_10	Ya0_9	Ya0_8
7	WFB0	Zs0_6	Zs0_5	Zs0_4	Zs0_3	Zs0_2	Zs0_1	Zs0_0

8	Xa1_7	Xa1_6	Xa1_5	Xa1_4	Xa1_3	Xa1_2	Xa1_1	Xa1_0
9	Xa1_15	Xa1_14	Xa1_13	Xa1_12	Xa1_11	Xa1_10	Xa1_9	Xa1_8
10	Ya1_7	Ya1_6	Ya1_5	Ya1_4	Ya1_3	Ya1_2	Ya1_1	Ya1_0
11	Ya1_15	Ya1_14	Ya1_13	Ya1_12	Ya1_11	Ya1_10	Ya1_9	Ya1_8
12	WFB1	Zs1_6	Zs1_5	Zs1_4	Zs1_3	Zs1_2	Zs1_1	Zs1_0

13	Xa2_7	Xa2_6	Xa2_5	Xa2_4	Xa2_3	Xa2_2	Xa2_1	Xa2_0
14	Xa2_15	Xa2_14	Xa2_13	Xa2_12	Xa2_11	Xa2_10	Xa2_9	Xa2_8
15	Ya2_7	Ya2_6	Ya2_5	Ya2_4	Ya2_3	Ya2_2	Ya2_1	Ya2_0
16	Ya2_15	Ya2_14	Ya2_13	Ya2_12	Ya2_11	Ya2_10	Ya2_9	Ya2_8
17	WFB2	Zs2_6	Zs2_5	Zs2_4	Zs2_3	Zs2_2	Zs2_1	Zs2_0

18	Xa3_7	Xa3_6	Xa3_5	Xa3_4	Xa3_3	Xa3_2	Xa3_1	Xa3_0
19	Xa3_15	Xa3_14	Xa3_13	Xa3_12	Xa3_11	Xa3_10	Xa3_9	Xa3_8
20	Ya3_7	Ya3_6	Ya3_5	Ya3_4	Ya3_3	Ya3_2	Ya3_1	Ya3_0
21	Ya3_15	Ya3_14	Ya3_13	Ya3_12	Ya3_11	Ya3_10	Ya3_9	Ya3_8
22	WFB3	Zs3_6	Zs3_5	Zs3_4	Zs3_3	Zs3_2	Zs3_1	Zs3_0

23	Xa4_7	Xa4_6	Xa4_5	Xa4_4	Xa4_3	Xa4_2	Xa4_1	Xa4_0
24	Xa4_15	Xa4_14	Xa4_13	Xa4_12	Xa4_11	Xa4_10	Xa4_9	Xa4_8
25	Ya4_7	Ya4_6	Ya4_5	Ya4_4	Ya4_3	Ya4_2	Ya4_1	Ya4_0
26	Ya4_15	Ya4_14	Ya4_13	Ya4_12	Ya4_11	Ya4_10	Ya4_9	Ya4_8
27	WFB4	Zs4_6	Zs4_5	Zs4_4	Zs4_3	Zs4_2	Zs4_1	Zs4_0
======= ======= ======= ======= ======= ======= ======= ======= =====


SW1-SW6:
	SW ON/OFF status
Xan_15-0(16bit):
	X Absowute data of the "n"th fingew
Yan_15-0(16bit):
	Y Absowute data of the "n"th fingew
Zsn_6-0(7bit):
	Opewation awea of the "n"th fingew


StickPointew data byte
----------------------

======= ======= ======= ======= ======= ======= ======= ======= =====
-	b7	b6	b5	b4	b3	b2	b1	b0
======= ======= ======= ======= ======= ======= ======= ======= =====
Byte1	1	1	1	0	1	SW3	SW2	SW1
Byte2	X7	X6	X5	X4	X3	X2	X1	X0
Byte3	X15	X14	X13	X12	X11	X10	X9	X8
Byte4	Y7	Y6	Y5	Y4	Y3	Y2	Y1	Y0
Byte5	Y15	Y14	Y13	Y12	Y11	Y10	Y9	Y8
Byte6	Z7	Z6	Z5	Z4	Z3	Z2	Z1	Z0
Byte7	T&P	Z14	Z13	Z12	Z11	Z10	Z9	Z8
======= ======= ======= ======= ======= ======= ======= ======= =====

SW1-SW3:
	SW ON/OFF status
Xn_15-0(16bit):
	X Absowute data
Yn_15-0(16bit):
	Y Absowute data
Zn_14-0(15bit):
	Z
