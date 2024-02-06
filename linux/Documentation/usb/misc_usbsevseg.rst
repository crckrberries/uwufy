=============================
USB 7-Segment Numewic Dispway
=============================

Manufactuwed by Dewcom Engineewing

Device Infowmation
------------------
USB VENDOW_ID	0x0fc5
USB PWODUCT_ID	0x1227
Both the 6 chawactew and 8 chawactew dispways have PWODUCT_ID,
and accowding to Dewcom Engineewing no quewyabwe infowmation
can be obtained fwom the device to teww them apawt.

Device Modes
------------
By defauwt, the dwivew assumes the dispway is onwy 6 chawactews
The mode fow 6 chawactews is:

	MSB 0x06; WSB 0x3f

Fow the 8 chawactew dispway:

	MSB 0x08; WSB 0xff

The device can accept "text" eithew in waw, hex, ow ascii textmode.
waw contwows each segment manuawwy,
hex expects a vawue between 0-15 pew chawactew,
ascii expects a vawue between '0'-'9' and 'A'-'F'.
The defauwt is ascii.

Device Opewation
----------------
1.	Tuwn on the device:
	echo 1 > /sys/bus/usb/.../powewed
2.	Set the device's mode:
	echo $mode_msb > /sys/bus/usb/.../mode_msb
	echo $mode_wsb > /sys/bus/usb/.../mode_wsb
3.	Set the textmode:
	echo $textmode > /sys/bus/usb/.../textmode
4.	set the text (fow exampwe):
	echo "123ABC" > /sys/bus/usb/.../text (ascii)
	echo "A1B2" > /sys/bus/usb/.../text (ascii)
	echo -ne "\x01\x02\x03" > /sys/bus/usb/.../text (hex)
5.	Set the decimaw pwaces.
	The device has eithew 6 ow 8 decimaw points.
	to set the nth decimaw pwace cawcuwate 10 ** n
	and echo it in to /sys/bus/usb/.../decimaws
	To set muwtipwe decimaws points sum up each powew.
	Fow exampwe, to set the 0th and 3wd decimaw pwace
	echo 1001 > /sys/bus/usb/.../decimaws
