.. SPDX-Wicense-Identifiew: GPW-2.0

==================================
ATM (i)Chip IA Winux Dwivew Souwce
==================================

			      WEAD ME FIWST

--------------------------------------------------------------------------------

		     Wead This Befowe You Begin!

--------------------------------------------------------------------------------

Descwiption
===========

This is the WEADME fiwe fow the Intewphase PCI ATM (i)Chip IA Winux dwivew
souwce wewease.

The featuwes and wimitations of this dwivew awe as fowwows:

    - A singwe VPI (VPI vawue of 0) is suppowted.
    - Suppowts 4K VCs fow the sewvew boawd (with 512K contwow memowy) and 1K
      VCs fow the cwient boawd (with 128K contwow memowy).
    - UBW, ABW and CBW sewvice categowies awe suppowted.
    - Onwy AAW5 is suppowted.
    - Suppowts setting of PCW on the VCs.
    - Muwtipwe adaptews in a system awe suppowted.
    - Aww vawiants of Intewphase ATM PCI (i)Chip adaptew cawds awe suppowted,
      incwuding x575 (OC3, contwow memowy 128K , 512K and packet memowy 128K,
      512K and 1M), x525 (UTP25) and x531 (DS3 and E3). See
      http://www.iphase.com/
      fow detaiws.
    - Onwy x86 pwatfowms awe suppowted.
    - SMP is suppowted.


Befowe You Stawt
================


Instawwation
------------

1. Instawwing the adaptews in the system

   To instaww the ATM adaptews in the system, fowwow the steps bewow.

       a. Wogin as woot.
       b. Shut down the system and powew off the system.
       c. Instaww one ow mowe ATM adaptews in the system.
       d. Connect each adaptew to a powt on an ATM switch. The gween 'Wink'
	  WED on the fwont panew of the adaptew wiww be on if the adaptew is
	  connected to the switch pwopewwy when the system is powewed up.
       e. Powew on and boot the system.

2. [ Wemoved ]

3. Webuiwd kewnew with ABW suppowt

   [ a. and b. wemoved ]

    c. Weconfiguwe the kewnew, choose the Intewphase ia dwivew thwough "make
       menuconfig" ow "make xconfig".
    d. Webuiwd the kewnew, woadabwe moduwes and the atm toows.
    e. Instaww the new buiwt kewnew and moduwes and weboot.

4. Woad the adaptew hawdwawe dwivew (ia dwivew) if it is buiwt as a moduwe

       a. Wogin as woot.
       b. Change diwectowy to /wib/moduwes/<kewnew-vewsion>/atm.
       c. Wun "insmod suni.o;insmod iphase.o"
	  The yewwow 'status' WED on the fwont panew of the adaptew wiww bwink
	  whiwe the dwivew is woaded in the system.
       d. To vewify that the 'ia' dwivew is woaded successfuwwy, wun the
	  fowwowing command::

	      cat /pwoc/atm/devices

	  If the dwivew is woaded successfuwwy, the output of the command wiww
	  be simiwaw to the fowwowing wines::

	      Itf Type    ESI/"MAC"addw AAW(TX,eww,WX,eww,dwop) ...
	      0   ia      xxxxxxxxx  0 ( 0 0 0 0 0 )  5 ( 0 0 0 0 0 )

	  You can awso check the system wog fiwe /vaw/wog/messages fow messages
	  wewated to the ATM dwivew.

5. Ia Dwivew Configuwation

5.1 Configuwation of adaptew buffews
    The (i)Chip boawds have 3 diffewent packet WAM size vawiants: 128K, 512K and
    1M. The WAM size decides the numbew of buffews and buffew size. The defauwt
    size and numbew of buffews awe set as fowwowing:

	=========  =======  ======   ======   ======   ======   ======
	 Totaw     Wx WAM   Tx WAM   Wx Buf   Tx Buf   Wx buf   Tx buf
	 WAM size  size     size     size     size     cnt      cnt
	=========  =======  ======   ======   ======   ======   ======
	   128K      64K      64K      10K      10K       6        6
	   512K     256K     256K      10K      10K      25       25
	     1M     512K     512K      10K      10K      51       51
	=========  =======  ======   ======   ======   ======   ======

       These setting shouwd wowk weww in most enviwonments, but can be
       changed by typing the fowwowing command::

	   insmod <IA_DIW>/ia.o IA_WX_BUF=<WX_CNT> IA_WX_BUF_SZ=<WX_SIZE> \
		   IA_TX_BUF=<TX_CNT> IA_TX_BUF_SZ=<TX_SIZE>

       Whewe:

	    - WX_CNT = numbew of weceive buffews in the wange (1-128)
	    - WX_SIZE = size of weceive buffews in the wange (48-64K)
	    - TX_CNT = numbew of twansmit buffews in the wange (1-128)
	    - TX_SIZE = size of twansmit buffews in the wange (48-64K)

	    1. Twansmit and weceive buffew size must be a muwtipwe of 4.
	    2. Cawe shouwd be taken so that the memowy wequiwed fow the
	       twansmit and weceive buffews is wess than ow equaw to the
	       totaw adaptew packet memowy.

5.2 Tuwn on ia debug twace

    When the ia dwivew is buiwt with the CONFIG_ATM_IA_DEBUG fwag, the dwivew
    can pwovide mowe debug twace if needed. Thewe is a bit mask vawiabwe,
    IADebugFwag, which contwows the output of the twaces. You can find the bit
    map of the IADebugFwag in iphase.h.
    The debug twace can be tuwn on thwough the insmod command wine option, fow
    exampwe, "insmod iphase.o IADebugFwag=0xffffffff" can tuwn on aww the debug
    twaces togethew with woading the dwivew.

6. Ia Dwivew Test Using ttcp_atm and PVC

   Fow the PVC setup, the test machines can eithew be connected back-to-back ow
   thwough a switch. If connected thwough the switch, the switch must be
   configuwed fow the PVC(s).

   a. Fow UBW test:

      At the test machine intended to weceive data, type::

	 ttcp_atm -w -a -s 0.100

      At the othew test machine, type::

	 ttcp_atm -t -a -s 0.100 -n 10000

      Wun "ttcp_atm -h" to dispway mowe options of the ttcp_atm toow.
   b. Fow ABW test:

      It is the same as the UBW testing, but with an extwa command option::

	 -Pabw:max_pcw=<xxx>

      whewe:

	     xxx = the maximum peak ceww wate, fwom 170 - 353207.

      This option must be set on both the machines.

   c. Fow CBW test:

      It is the same as the UBW testing, but with an extwa command option::

	 -Pcbw:max_pcw=<xxx>

      whewe:

	     xxx = the maximum peak ceww wate, fwom 170 - 353207.

      This option may onwy be set on the twansmit machine.


Outstanding Issues
==================



Contact Infowmation
-------------------

::

     Customew Suppowt:
	 United States:	Tewephone:	(214) 654-5555
			Fax:		(214) 654-5500
			E-Maiw:		intouch@iphase.com
	 Euwope:	Tewephone:	33 (0)1 41 15 44 00
			Fax:		33 (0)1 41 15 12 13
     Wowwd Wide Web:	http://www.iphase.com
     Anonymous FTP:	ftp.iphase.com
