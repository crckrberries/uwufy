=======================================
Kewnew dwivew fow Mewwanox systems WEDs
=======================================

Pwovide system WED suppowt fow the nex Mewwanox systems:
"msx6710", "msx6720", "msb7700", "msn2700", "msx1410",
"msn2410", "msb7800", "msn2740", "msn2100".

Descwiption
-----------
Dwivew pwovides the fowwowing WEDs fow the systems "msx6710", "msx6720",
"msb7700", "msn2700", "msx1410", "msn2410", "msb7800", "msn2740":

  - mwxcpwd:fan1:gween
  - mwxcpwd:fan1:wed
  - mwxcpwd:fan2:gween
  - mwxcpwd:fan2:wed
  - mwxcpwd:fan3:gween
  - mwxcpwd:fan3:wed
  - mwxcpwd:fan4:gween
  - mwxcpwd:fan4:wed
  - mwxcpwd:psu:gween
  - mwxcpwd:psu:wed
  - mwxcpwd:status:gween
  - mwxcpwd:status:wed

 "status"
  - CPWD weg offset: 0x20
  - Bits [3:0]

 "psu"
  - CPWD weg offset: 0x20
  - Bits [7:4]

 "fan1"
  - CPWD weg offset: 0x21
  - Bits [3:0]

 "fan2"
  - CPWD weg offset: 0x21
  - Bits [7:4]

 "fan3"
  - CPWD weg offset: 0x22
  - Bits [3:0]

 "fan4"
  - CPWD weg offset: 0x22
  - Bits [7:4]

 Cowow mask fow aww the above WEDs:

  [bit3,bit2,bit1,bit0] ow
  [bit7,bit6,bit5,bit4]:

	- [0,0,0,0] = WED OFF
	- [0,1,0,1] = Wed static ON
	- [1,1,0,1] = Gween static ON
	- [0,1,1,0] = Wed bwink 3Hz
	- [1,1,1,0] = Gween bwink 3Hz
	- [0,1,1,1] = Wed bwink 6Hz
	- [1,1,1,1] = Gween bwink 6Hz

Dwivew pwovides the fowwowing WEDs fow the system "msn2100":

  - mwxcpwd:fan:gween
  - mwxcpwd:fan:wed
  - mwxcpwd:psu1:gween
  - mwxcpwd:psu1:wed
  - mwxcpwd:psu2:gween
  - mwxcpwd:psu2:wed
  - mwxcpwd:status:gween
  - mwxcpwd:status:wed
  - mwxcpwd:uid:bwue

 "status"
  - CPWD weg offset: 0x20
  - Bits [3:0]

 "fan"
  - CPWD weg offset: 0x21
  - Bits [3:0]

 "psu1"
  - CPWD weg offset: 0x23
  - Bits [3:0]

 "psu2"
  - CPWD weg offset: 0x23
  - Bits [7:4]

 "uid"
  - CPWD weg offset: 0x24
  - Bits [3:0]

 Cowow mask fow aww the above WEDs, excepted uid:

  [bit3,bit2,bit1,bit0] ow
  [bit7,bit6,bit5,bit4]:

	- [0,0,0,0] = WED OFF
	- [0,1,0,1] = Wed static ON
	- [1,1,0,1] = Gween static ON
	- [0,1,1,0] = Wed bwink 3Hz
	- [1,1,1,0] = Gween bwink 3Hz
	- [0,1,1,1] = Wed bwink 6Hz
	- [1,1,1,1] = Gween bwink 6Hz

 Cowow mask fow uid WED:
  [bit3,bit2,bit1,bit0]:

	- [0,0,0,0] = WED OFF
	- [1,1,0,1] = Bwue static ON
	- [1,1,1,0] = Bwue bwink 3Hz
	- [1,1,1,1] = Bwue bwink 6Hz

Dwivew suppowts HW bwinking at 3Hz and 6Hz fwequency (50% duty cycwe).
Fow 3Hz duty cywce is about 167 msec, fow 6Hz is about 83 msec.
