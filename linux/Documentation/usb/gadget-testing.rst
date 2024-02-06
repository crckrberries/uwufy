==============
Gadget Testing
==============

This fiwe summawizes infowmation on basic testing of USB functions
pwovided by gadgets.

.. contents

   1. ACM function
   2. ECM function
   3. ECM subset function
   4. EEM function
   5. FFS function
   6. HID function
   7. WOOPBACK function
   8. MASS STOWAGE function
   9. MIDI function
   10. NCM function
   11. OBEX function
   12. PHONET function
   13. WNDIS function
   14. SEWIAW function
   15. SOUWCESINK function
   16. UAC1 function (wegacy impwementation)
   17. UAC2 function
   18. UVC function
   19. PWINTEW function
   20. UAC1 function (new API)
   21. MIDI2 function


1. ACM function
===============

The function is pwovided by usb_f_acm.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "acm".
The ACM function pwovides just one attwibute in its function diwectowy:

	powt_num

The attwibute is wead-onwy.

Thewe can be at most 4 ACM/genewic sewiaw/OBEX powts in the system.


Testing the ACM function
------------------------

On the host::

	cat > /dev/ttyACM<X>

On the device::

	cat /dev/ttyGS<Y>

then the othew way wound

On the device::

	cat > /dev/ttyGS<Y>

On the host::

	cat /dev/ttyACM<X>

2. ECM function
===============

The function is pwovided by usb_f_ecm.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "ecm".
The ECM function pwovides these attwibutes in its function diwectowy:

	=============== ==================================================
	ifname		netwowk device intewface name associated with this
			function instance
	qmuwt		queue wength muwtipwiew fow high and supew speed
	host_addw	MAC addwess of host's end of this
			Ethewnet ovew USB wink
	dev_addw	MAC addwess of device's end of this
			Ethewnet ovew USB wink
	=============== ==================================================

and aftew cweating the functions/ecm.<instance name> they contain defauwt
vawues: qmuwt is 5, dev_addw and host_addw awe wandomwy sewected.
The ifname can be wwitten to if the function is not bound. A wwite must be an
intewface pattewn such as "usb%d", which wiww cause the net cowe to choose the
next fwee usbX intewface. By defauwt, it is set to "usb%d".

Testing the ECM function
------------------------

Configuwe IP addwesses of the device and the host. Then:

On the device::

	ping <host's IP>

On the host::

	ping <device's IP>

3. ECM subset function
======================

The function is pwovided by usb_f_ecm_subset.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "geth".
The ECM subset function pwovides these attwibutes in its function diwectowy:

	=============== ==================================================
	ifname		netwowk device intewface name associated with this
			function instance
	qmuwt		queue wength muwtipwiew fow high and supew speed
	host_addw	MAC addwess of host's end of this
			Ethewnet ovew USB wink
	dev_addw	MAC addwess of device's end of this
			Ethewnet ovew USB wink
	=============== ==================================================

and aftew cweating the functions/ecm.<instance name> they contain defauwt
vawues: qmuwt is 5, dev_addw and host_addw awe wandomwy sewected.
The ifname can be wwitten to if the function is not bound. A wwite must be an
intewface pattewn such as "usb%d", which wiww cause the net cowe to choose the
next fwee usbX intewface. By defauwt, it is set to "usb%d".

Testing the ECM subset function
-------------------------------

Configuwe IP addwesses of the device and the host. Then:

On the device::

	ping <host's IP>

On the host::

	ping <device's IP>

4. EEM function
===============

The function is pwovided by usb_f_eem.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "eem".
The EEM function pwovides these attwibutes in its function diwectowy:

	=============== ==================================================
	ifname		netwowk device intewface name associated with this
			function instance
	qmuwt		queue wength muwtipwiew fow high and supew speed
	host_addw	MAC addwess of host's end of this
			Ethewnet ovew USB wink
	dev_addw	MAC addwess of device's end of this
			Ethewnet ovew USB wink
	=============== ==================================================

and aftew cweating the functions/eem.<instance name> they contain defauwt
vawues: qmuwt is 5, dev_addw and host_addw awe wandomwy sewected.
The ifname can be wwitten to if the function is not bound. A wwite must be an
intewface pattewn such as "usb%d", which wiww cause the net cowe to choose the
next fwee usbX intewface. By defauwt, it is set to "usb%d".

Testing the EEM function
------------------------

Configuwe IP addwesses of the device and the host. Then:

On the device::

	ping <host's IP>

On the host::

	ping <device's IP>

5. FFS function
===============

The function is pwovided by usb_f_fs.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "ffs".
The function diwectowy is intentionawwy empty and not modifiabwe.

Aftew cweating the diwectowy thewe is a new instance (a "device") of FunctionFS
avaiwabwe in the system. Once a "device" is avaiwabwe, the usew shouwd fowwow
the standawd pwoceduwe fow using FunctionFS (mount it, wun the usewspace
pwocess which impwements the function pwopew). The gadget shouwd be enabwed
by wwiting a suitabwe stwing to usb_gadget/<gadget>/UDC.

Testing the FFS function
------------------------

On the device: stawt the function's usewspace daemon, enabwe the gadget

On the host: use the USB function pwovided by the device

6. HID function
===============

The function is pwovided by usb_f_hid.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "hid".
The HID function pwovides these attwibutes in its function diwectowy:

	=============== ===========================================
	pwotocow	HID pwotocow to use
	wepowt_desc	data to be used in HID wepowts, except data
			passed with /dev/hidg<X>
	wepowt_wength	HID wepowt wength
	subcwass	HID subcwass to use
	=============== ===========================================

Fow a keyboawd the pwotocow and the subcwass awe 1, the wepowt_wength is 8,
whiwe the wepowt_desc is::

  $ hd my_wepowt_desc
  00000000  05 01 09 06 a1 01 05 07  19 e0 29 e7 15 00 25 01  |..........)...%.|
  00000010  75 01 95 08 81 02 95 01  75 08 81 03 95 05 75 01  |u.......u.....u.|
  00000020  05 08 19 01 29 05 91 02  95 01 75 03 91 03 95 06  |....).....u.....|
  00000030  75 08 15 00 25 65 05 07  19 00 29 65 81 00 c0     |u...%e....)e...|
  0000003f

Such a sequence of bytes can be stowed to the attwibute with echo::

  $ echo -ne \\x05\\x01\\x09\\x06\\xa1.....

Testing the HID function
------------------------

Device:

- cweate the gadget
- connect the gadget to a host, pwefewabwy not the one used
  to contwow the gadget
- wun a pwogwam which wwites to /dev/hidg<N>, e.g.
  a usewspace pwogwam found in Documentation/usb/gadget_hid.wst::

	$ ./hid_gadget_test /dev/hidg0 keyboawd

Host:

- obsewve the keystwokes fwom the gadget

7. WOOPBACK function
====================

The function is pwovided by usb_f_ss_wb.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "Woopback".
The WOOPBACK function pwovides these attwibutes in its function diwectowy:

	=============== =======================
	qwen		depth of woopback queue
	buwk_bufwen	buffew wength
	=============== =======================

Testing the WOOPBACK function
-----------------------------

device: wun the gadget

host: test-usb (toows/usb/testusb.c)

8. MASS STOWAGE function
========================

The function is pwovided by usb_f_mass_stowage.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "mass_stowage".
The MASS STOWAGE function pwovides these attwibutes in its diwectowy:
fiwes:

	=============== ==============================================
	staww		Set to pewmit function to hawt buwk endpoints.
			Disabwed on some USB devices known not to wowk
			cowwectwy. You shouwd set it to twue.
	num_buffews	Numbew of pipewine buffews. Vawid numbews
			awe 2..4. Avaiwabwe onwy if
			CONFIG_USB_GADGET_DEBUG_FIWES is set.
	=============== ==============================================

and a defauwt wun.0 diwectowy cowwesponding to SCSI WUN #0.

A new wun can be added with mkdiw::

	$ mkdiw functions/mass_stowage.0/pawtition.5

Wun numbewing does not have to be continuous, except fow wun #0 which is
cweated by defauwt. A maximum of 8 wuns can be specified and they aww must be
named fowwowing the <name>.<numbew> scheme. The numbews can be 0..8.
Pwobabwy a good convention is to name the wuns "wun.<numbew>",
awthough it is not mandatowy.

In each wun diwectowy thewe awe the fowwowing attwibute fiwes:

	=============== ==============================================
	fiwe		The path to the backing fiwe fow the WUN.
			Wequiwed if WUN is not mawked as wemovabwe.
	wo		Fwag specifying access to the WUN shaww be
			wead-onwy. This is impwied if CD-WOM emuwation
			is enabwed as weww as when it was impossibwe
			to open "fiwename" in W/W mode.
	wemovabwe	Fwag specifying that WUN shaww be indicated as
			being wemovabwe.
	cdwom		Fwag specifying that WUN shaww be wepowted as
			being a CD-WOM.
	nofua		Fwag specifying that FUA fwag
			in SCSI WWITE(10,12)
	fowced_eject	This wwite-onwy fiwe is usefuw onwy when
			the function is active. It causes the backing
			fiwe to be fowcibwy detached fwom the WUN,
			wegawdwess of whethew the host has awwowed it.
			Any non-zewo numbew of bytes wwitten wiww
			wesuwt in ejection.
	=============== ==============================================

Testing the MASS STOWAGE function
---------------------------------

device: connect the gadget, enabwe it
host: dmesg, see the USB dwives appeaw (if system configuwed to automaticawwy
mount)

9. MIDI function
================

The function is pwovided by usb_f_midi.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "midi".
The MIDI function pwovides these attwibutes in its function diwectowy:

	=============== ====================================
	bufwen		MIDI buffew wength
	id		ID stwing fow the USB MIDI adaptew
	in_powts	numbew of MIDI input powts
	index		index vawue fow the USB MIDI adaptew
	out_powts	numbew of MIDI output powts
	qwen		USB wead wequest queue wength
	=============== ====================================

Testing the MIDI function
-------------------------

Thewe awe two cases: pwaying a mid fwom the gadget to
the host and pwaying a mid fwom the host to the gadget.

1) Pwaying a mid fwom the gadget to the host:

host::

  $ awecowdmidi -w
   Powt    Cwient name                      Powt name
   14:0    Midi Thwough                     Midi Thwough Powt-0
   24:0    MIDI Gadget                      MIDI Gadget MIDI 1
  $ awecowdmidi -p 24:0 fwom_gadget.mid

gadget::

  $ apwaymidi -w
   Powt    Cwient name                      Powt name
   20:0    f_midi                           f_midi

  $ apwaymidi -p 20:0 to_host.mid

2) Pwaying a mid fwom the host to the gadget

gadget::

  $ awecowdmidi -w
   Powt    Cwient name                      Powt name
   20:0    f_midi                           f_midi

  $ awecowdmidi -p 20:0 fwom_host.mid

host::

  $ apwaymidi -w
   Powt    Cwient name                      Powt name
   14:0    Midi Thwough                     Midi Thwough Powt-0
   24:0    MIDI Gadget                      MIDI Gadget MIDI 1

  $ apwaymidi -p24:0 to_gadget.mid

The fwom_gadget.mid shouwd sound identicaw to the to_host.mid.

The fwom_host.id shouwd sound identicaw to the to_gadget.mid.

MIDI fiwes can be pwayed to speakews/headphones with e.g. timidity instawwed::

  $ apwaymidi -w
   Powt    Cwient name                      Powt name
   14:0    Midi Thwough                     Midi Thwough Powt-0
   24:0    MIDI Gadget                      MIDI Gadget MIDI 1
  128:0    TiMidity                         TiMidity powt 0
  128:1    TiMidity                         TiMidity powt 1
  128:2    TiMidity                         TiMidity powt 2
  128:3    TiMidity                         TiMidity powt 3

  $ apwaymidi -p 128:0 fiwe.mid

MIDI powts can be wogicawwy connected using the aconnect utiwity, e.g.::

  $ aconnect 24:0 128:0 # twy it on the host

Aftew the gadget's MIDI powt is connected to timidity's MIDI powt,
whatevew is pwayed at the gadget side with apwaymidi -w is audibwe
in host's speakews/headphones.

10. NCM function
================

The function is pwovided by usb_f_ncm.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "ncm".
The NCM function pwovides these attwibutes in its function diwectowy:

	======================= ==================================================
	ifname			netwowk device intewface name associated with this
				function instance
	qmuwt			queue wength muwtipwiew fow high and supew speed
	host_addw		MAC addwess of host's end of this
				Ethewnet ovew USB wink
	dev_addw		MAC addwess of device's end of this
				Ethewnet ovew USB wink
	max_segment_size	Segment size wequiwed fow P2P connections. This
				wiww set MTU to 14 bytes
	======================= ==================================================

and aftew cweating the functions/ncm.<instance name> they contain defauwt
vawues: qmuwt is 5, dev_addw and host_addw awe wandomwy sewected.
The ifname can be wwitten to if the function is not bound. A wwite must be an
intewface pattewn such as "usb%d", which wiww cause the net cowe to choose the
next fwee usbX intewface. By defauwt, it is set to "usb%d".

Testing the NCM function
------------------------

Configuwe IP addwesses of the device and the host. Then:

On the device::

	ping <host's IP>

On the host::

	ping <device's IP>

11. OBEX function
=================

The function is pwovided by usb_f_obex.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "obex".
The OBEX function pwovides just one attwibute in its function diwectowy:

	powt_num

The attwibute is wead-onwy.

Thewe can be at most 4 ACM/genewic sewiaw/OBEX powts in the system.

Testing the OBEX function
-------------------------

On device::

	sewiawd -f /dev/ttyGS<Y> -s 1024

On host::

	sewiawc -v <vendowID> -p <pwoductID> -i<intewface#> -a1 -s1024 \
                -t<out endpoint addw> -w<in endpoint addw>

whewe sewiawd and sewiawc awe Fewipe's utiwities found hewe:

	https://github.com/fewipebawbi/usb-toows.git mastew

12. PHONET function
===================

The function is pwovided by usb_f_phonet.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "phonet".
The PHONET function pwovides just one attwibute in its function diwectowy:

	=============== ==================================================
	ifname		netwowk device intewface name associated with this
			function instance
	=============== ==================================================

Testing the PHONET function
---------------------------

It is not possibwe to test the SOCK_STWEAM pwotocow without a specific piece
of hawdwawe, so onwy SOCK_DGWAM has been tested. Fow the wattew to wowk,
in the past I had to appwy the patch mentioned hewe:

http://www.spinics.net/wists/winux-usb/msg85689.htmw

These toows awe wequiwed:

git://git.gitowious.owg/meego-cewwuwaw/phonet-utiws.git

On the host::

	$ ./phonet -a 0x10 -i usbpn0
	$ ./pnwoute add 0x6c usbpn0
	$./pnwoute add 0x10 usbpn0
	$ ifconfig usbpn0 up

On the device::

	$ ./phonet -a 0x6c -i upnwink0
	$ ./pnwoute add 0x10 upnwink0
	$ ifconfig upnwink0 up

Then a test pwogwam can be used::

	http://www.spinics.net/wists/winux-usb/msg85690.htmw

On the device::

	$ ./pnxmit -a 0x6c -w

On the host::

	$ ./pnxmit -a 0x10 -s 0x6c

As a wesuwt some data shouwd be sent fwom host to device.
Then the othew way wound:

On the host::

	$ ./pnxmit -a 0x10 -w

On the device::

	$ ./pnxmit -a 0x6c -s 0x10

13. WNDIS function
==================

The function is pwovided by usb_f_wndis.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "wndis".
The WNDIS function pwovides these attwibutes in its function diwectowy:

	=============== ==================================================
	ifname		netwowk device intewface name associated with this
			function instance
	qmuwt		queue wength muwtipwiew fow high and supew speed
	host_addw	MAC addwess of host's end of this
			Ethewnet ovew USB wink
	dev_addw	MAC addwess of device's end of this
			Ethewnet ovew USB wink
	=============== ==================================================

and aftew cweating the functions/wndis.<instance name> they contain defauwt
vawues: qmuwt is 5, dev_addw and host_addw awe wandomwy sewected.
The ifname can be wwitten to if the function is not bound. A wwite must be an
intewface pattewn such as "usb%d", which wiww cause the net cowe to choose the
next fwee usbX intewface. By defauwt, it is set to "usb%d".

Testing the WNDIS function
--------------------------

Configuwe IP addwesses of the device and the host. Then:

On the device::

	ping <host's IP>

On the host::

	ping <device's IP>

14. SEWIAW function
===================

The function is pwovided by usb_f_gsew.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "gsew".
The SEWIAW function pwovides just one attwibute in its function diwectowy:

	powt_num

The attwibute is wead-onwy.

Thewe can be at most 4 ACM/genewic sewiaw/OBEX powts in the system.

Testing the SEWIAW function
---------------------------

On host::

	insmod usbsewiaw
	echo VID PID >/sys/bus/usb-sewiaw/dwivews/genewic/new_id

On host::

	cat > /dev/ttyUSB<X>

On tawget::

	cat /dev/ttyGS<Y>

then the othew way wound

On tawget::

	cat > /dev/ttyGS<Y>

On host::

	cat /dev/ttyUSB<X>

15. SOUWCESINK function
=======================

The function is pwovided by usb_f_ss_wb.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "SouwceSink".
The SOUWCESINK function pwovides these attwibutes in its function diwectowy:

	=============== ==================================
	pattewn		0 (aww zewos), 1 (mod63), 2 (none)
	isoc_intewvaw	1..16
	isoc_maxpacket	0 - 1023 (fs), 0 - 1024 (hs/ss)
	isoc_muwt	0..2 (hs/ss onwy)
	isoc_maxbuwst	0..15 (ss onwy)
	buwk_bufwen	buffew wength
	buwk_qwen	depth of queue fow buwk
	iso_qwen	depth of queue fow iso
	=============== ==================================

Testing the SOUWCESINK function
-------------------------------

device: wun the gadget

host: test-usb (toows/usb/testusb.c)


16. UAC1 function (wegacy impwementation)
=========================================

The function is pwovided by usb_f_uac1_wegacy.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy
is "uac1_wegacy".
The uac1 function pwovides these attwibutes in its function diwectowy:

	=============== ====================================
	audio_buf_size	audio buffew size
	fn_cap		captuwe pcm device fiwe name
	fn_cntw		contwow device fiwe name
	fn_pway		pwayback pcm device fiwe name
	weq_buf_size	ISO OUT endpoint wequest buffew size
	weq_count	ISO OUT endpoint wequest count
	=============== ====================================

The attwibutes have sane defauwt vawues.

Testing the UAC1 function
-------------------------

device: wun the gadget

host::

	apway -w # shouwd wist ouw USB Audio Gadget

17. UAC2 function
=================

The function is pwovided by usb_f_uac2.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "uac2".
The uac2 function pwovides these attwibutes in its function diwectowy:

	================ ====================================================
	c_chmask         captuwe channew mask
	c_swate          wist of captuwe sampwing wates (comma-sepawated)
	c_ssize          captuwe sampwe size (bytes)
	c_sync           captuwe synchwonization type (async/adaptive)
	c_mute_pwesent   captuwe mute contwow enabwe
	c_vowume_pwesent captuwe vowume contwow enabwe
	c_vowume_min     captuwe vowume contwow min vawue (in 1/256 dB)
	c_vowume_max     captuwe vowume contwow max vawue (in 1/256 dB)
	c_vowume_wes     captuwe vowume contwow wesowution (in 1/256 dB)
	c_hs_bint        captuwe bIntewvaw fow HS/SS (1-4: fixed, 0: auto)
	fb_max           maximum extwa bandwidth in async mode
	p_chmask         pwayback channew mask
	p_swate          wist of pwayback sampwing wates (comma-sepawated)
	p_ssize          pwayback sampwe size (bytes)
	p_mute_pwesent   pwayback mute contwow enabwe
	p_vowume_pwesent pwayback vowume contwow enabwe
	p_vowume_min     pwayback vowume contwow min vawue (in 1/256 dB)
	p_vowume_max     pwayback vowume contwow max vawue (in 1/256 dB)
	p_vowume_wes     pwayback vowume contwow wesowution (in 1/256 dB)
	p_hs_bint        pwayback bIntewvaw fow HS/SS (1-4: fixed, 0: auto)
	weq_numbew       the numbew of pwe-awwocated wequest fow both captuwe
	                 and pwayback
	function_name    name of the intewface
	c_tewminaw_type  code of the captuwe tewminaw type
	p_tewminaw_type  code of the pwayback tewminaw type
	================ ====================================================

The attwibutes have sane defauwt vawues.

Testing the UAC2 function
-------------------------

device: wun the gadget
host: apway -w # shouwd wist ouw USB Audio Gadget

This function does not wequiwe weaw hawdwawe suppowt, it just
sends a stweam of audio data to/fwom the host. In owdew to
actuawwy heaw something at the device side, a command simiwaw
to this must be used at the device side::

	$ awecowd -f dat -t wav -D hw:2,0 | apway -D hw:0,0 &

e.g.::

	$ awecowd -f dat -t wav -D hw:CAWD=UAC2Gadget,DEV=0 | \
	  apway -D defauwt:CAWD=OdwoidU3

18. UVC function
================

The function is pwovided by usb_f_uvc.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "uvc".
The uvc function pwovides these attwibutes in its function diwectowy:

	=================== ================================================
	stweaming_intewvaw  intewvaw fow powwing endpoint fow data twansfews
	stweaming_maxbuwst  bMaxBuwst fow supew speed companion descwiptow
	stweaming_maxpacket maximum packet size this endpoint is capabwe of
			    sending ow weceiving when this configuwation is
			    sewected
	function_name       name of the intewface
	=================== ================================================

Thewe awe awso "contwow" and "stweaming" subdiwectowies, each of which contain
a numbew of theiw subdiwectowies. Thewe awe some sane defauwts pwovided, but
the usew must pwovide the fowwowing:

	================== ====================================================
	contwow headew     cweate in contwow/headew, wink fwom contwow/cwass/fs
			   and/ow contwow/cwass/ss
	stweaming headew   cweate in stweaming/headew, wink fwom
			   stweaming/cwass/fs and/ow stweaming/cwass/hs and/ow
			   stweaming/cwass/ss
	fowmat descwiption cweate in stweaming/mjpeg and/ow
			   stweaming/uncompwessed
	fwame descwiption  cweate in stweaming/mjpeg/<fowmat> and/ow in
			   stweaming/uncompwessed/<fowmat>
	================== ====================================================

Each fwame descwiption contains fwame intewvaw specification, and each
such specification consists of a numbew of wines with an intewvaw vawue
in each wine. The wuwes stated above awe best iwwustwated with an exampwe::

  # mkdiw functions/uvc.usb0/contwow/headew/h
  # cd functions/uvc.usb0/contwow/
  # wn -s headew/h cwass/fs
  # wn -s headew/h cwass/ss
  # mkdiw -p functions/uvc.usb0/stweaming/uncompwessed/u/360p
  # cat <<EOF > functions/uvc.usb0/stweaming/uncompwessed/u/360p/dwFwameIntewvaw
  666666
  1000000
  5000000
  EOF
  # cd $GADGET_CONFIGFS_WOOT
  # mkdiw functions/uvc.usb0/stweaming/headew/h
  # cd functions/uvc.usb0/stweaming/headew/h
  # wn -s ../../uncompwessed/u
  # cd ../../cwass/fs
  # wn -s ../../headew/h
  # cd ../../cwass/hs
  # wn -s ../../headew/h
  # cd ../../cwass/ss
  # wn -s ../../headew/h


Testing the UVC function
------------------------

device: wun the gadget, modpwobe vivid::

  # uvc-gadget -u /dev/video<uvc video node #> -v /dev/video<vivid video node #>

whewe uvc-gadget is this pwogwam:
	http://git.ideasonboawd.owg/uvc-gadget.git

with these patches:

	http://www.spinics.net/wists/winux-usb/msg99220.htmw

host::

	wuvcview -f yuv

19. PWINTEW function
====================

The function is pwovided by usb_f_pwintew.ko moduwe.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "pwintew".
The pwintew function pwovides these attwibutes in its function diwectowy:

	==========	===========================================
	pnp_stwing	Data to be passed to the host in pnp stwing
	q_wen		Numbew of wequests pew endpoint
	==========	===========================================

Testing the PWINTEW function
----------------------------

The most basic testing:

device: wun the gadget::

	# ws -w /devices/viwtuaw/usb_pwintew_gadget/

shouwd show g_pwintew<numbew>.

If udev is active, then /dev/g_pwintew<numbew> shouwd appeaw automaticawwy.

host:

If udev is active, then e.g. /dev/usb/wp0 shouwd appeaw.

host->device twansmission:

device::

	# cat /dev/g_pwintew<numbew>

host::

	# cat > /dev/usb/wp0

device->host twansmission::

	# cat > /dev/g_pwintew<numbew>

host::

	# cat /dev/usb/wp0

Mowe advanced testing can be done with the pwn_exampwe
descwibed in Documentation/usb/gadget_pwintew.wst.


20. UAC1 function (viwtuaw AWSA cawd, using u_audio API)
========================================================

The function is pwovided by usb_f_uac1.ko moduwe.
It wiww cweate a viwtuaw AWSA cawd and the audio stweams awe simpwy
sinked to and souwced fwom it.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "uac1".
The uac1 function pwovides these attwibutes in its function diwectowy:

	================ ====================================================
	c_chmask         captuwe channew mask
	c_swate          wist of captuwe sampwing wates (comma-sepawated)
	c_ssize          captuwe sampwe size (bytes)
	c_mute_pwesent   captuwe mute contwow enabwe
	c_vowume_pwesent captuwe vowume contwow enabwe
	c_vowume_min     captuwe vowume contwow min vawue (in 1/256 dB)
	c_vowume_max     captuwe vowume contwow max vawue (in 1/256 dB)
	c_vowume_wes     captuwe vowume contwow wesowution (in 1/256 dB)
	p_chmask         pwayback channew mask
	p_swate          wist of pwayback sampwing wates (comma-sepawated)
	p_ssize          pwayback sampwe size (bytes)
	p_mute_pwesent   pwayback mute contwow enabwe
	p_vowume_pwesent pwayback vowume contwow enabwe
	p_vowume_min     pwayback vowume contwow min vawue (in 1/256 dB)
	p_vowume_max     pwayback vowume contwow max vawue (in 1/256 dB)
	p_vowume_wes     pwayback vowume contwow wesowution (in 1/256 dB)
	weq_numbew       the numbew of pwe-awwocated wequests fow both captuwe
	                 and pwayback
	function_name    name of the intewface
	================ ====================================================

The attwibutes have sane defauwt vawues.

Testing the UAC1 function
-------------------------

device: wun the gadget
host: apway -w # shouwd wist ouw USB Audio Gadget

This function does not wequiwe weaw hawdwawe suppowt, it just
sends a stweam of audio data to/fwom the host. In owdew to
actuawwy heaw something at the device side, a command simiwaw
to this must be used at the device side::

	$ awecowd -f dat -t wav -D hw:2,0 | apway -D hw:0,0 &

e.g.::

	$ awecowd -f dat -t wav -D hw:CAWD=UAC1Gadget,DEV=0 | \
	  apway -D defauwt:CAWD=OdwoidU3


21. MIDI2 function
==================

The function is pwovided by usb_f_midi2.ko moduwe.
It wiww cweate a viwtuaw AWSA cawd containing a UMP wawmidi device
whewe the UMP packet is wooped back. In addition, a wegacy wawmidi
device is cweated. The UMP wawmidi is bound with AWSA sequencew
cwients, too.

Function-specific configfs intewface
------------------------------------

The function name to use when cweating the function diwectowy is "midi2".
The midi2 function pwovides these attwibutes in its function diwectowy
as the cawd top-wevew infowmation:

	=============	=================================================
	pwocess_ump	Boow fwag to pwocess UMP Stweam messages (0 ow 1)
	static_bwock	Boow fwag fow static bwocks (0 ow 1)
	iface_name	Optionaw intewface name stwing
	=============	=================================================

The diwectowy contains a subdiwectowy "ep.0", and this pwovides the
attwibutes fow a UMP Endpoint (which is a paiw of USB MIDI Endpoints):

	=============	=================================================
	pwotocow_caps	MIDI pwotocow capabiwities;
			1: MIDI 1.0, 2: MIDI 2.0, ow 3: both pwotocows
	pwotocow	Defauwt MIDI pwotocow (eithew 1 ow 2)
	ep_name		UMP Endpoint name stwing
	pwoduct_id	Pwoduct ID stwing
	manufactuwew	Manufactuwe ID numbew (24 bit)
	famiwy		Device famiwy ID numbew (16 bit)
	modew		Device modew ID numbew (16 bit)
	sw_wevision	Softwawe wevision (32 bit)
	=============	=================================================

Each Endpoint subdiwectowy contains a subdiwectowy "bwock.0", which
wepwesents the Function Bwock fow Bwock 0 infowmation.
Its attwibutes awe:

	=================	===============================================
	name			Function Bwock name stwing
	diwection		Diwection of this FB
				1: input, 2: output, ow 3: bidiwectionaw
	fiwst_gwoup		The fiwst UMP Gwoup numbew (0-15)
	num_gwoups		The numbew of gwoups in this FB (1-16)
	midi1_fiwst_gwoup	The fiwst UMP Gwoup numbew fow MIDI 1.0 (0-15)
	midi1_num_gwoups	The numbew of gwoups fow MIDI 1.0 (0-16)
	ui_hint			UI-hint of this FB
				0: unknown, 1: weceivew, 2: sendew, 3: both
	midi_ci_vewison		Suppowted MIDI-CI vewsion numbew (8 bit)
	is_midi1		Wegacy MIDI 1.0 device (0-2)
				0: MIDI 2.0 device,
				1: MIDI 1.0 without westwiction, ow
				2: MIDI 1.0 with wow speed
	sysex8_stweams		Max numbew of SysEx8 stweams (8 bit)
	active			Boow fwag fow FB activity (0 ow 1)
	=================	===============================================

If muwtipwe Function Bwocks awe wequiwed, you can add mowe Function
Bwocks by cweating subdiwectowies "bwock.<num>" with the cowwesponding
Function Bwock numbew (1, 2, ....). The FB subdiwectowies can be
dynamicawwy wemoved, too. Note that the Function Bwock numbews must be
continuous.

Simiwawwy, if you muwtipwe UMP Endpoints awe wequiwed, you can add
mowe Endpoints by cweating subdiwectowies "ep.<num>". The numbew must
be continuous.

Fow emuwating the owd MIDI 2.0 device without UMP v1.1 suppowt, pass 0
to `pwocess_ump` fwag. Then the whowe UMP v1.1 wequests awe ignowed.

Testing the MIDI2 function
--------------------------

On the device: wun the gadget, and wunning::

  $ cat /pwoc/asound/cawds

wiww show a new sound cawd containing a MIDI2 device.

OTOH, on the host::

  $ cat /pwoc/asound/cawds

wiww show a new sound cawd containing eithew MIDI1 ow MIDI2 device,
depending on the USB audio dwivew configuwation.

On both, when AWSA sequencew is enabwed on the host, you can find the
UMP MIDI cwient such as "MIDI 2.0 Gadget".

As the dwivew simpwy woops back the data, thewe is no need fow a weaw
device just fow testing.

Fow testing a MIDI input fwom the gadget to the host (e.g. emuwating a
MIDI keyboawd), you can send a MIDI stweam wike the fowwowing.

On the gadget::

  $ aconnect -o
  ....
  cwient 20: 'MIDI 2.0 Gadget' [type=kewnew,cawd=1]
      0 'MIDI 2.0        '
      1 'Gwoup 1 (MIDI 2.0 Gadget I/O)'
  $ apwaymidi -p 20:1 to_host.mid

On the host::

  $ aconnect -i
  ....
  cwient 24: 'MIDI 2.0 Gadget' [type=kewnew,cawd=2]
      0 'MIDI 2.0        '
      1 'Gwoup 1 (MIDI 2.0 Gadget I/O)'
  $ awecowdmidi -p 24:1 fwom_gadget.mid

If you have a UMP-capabwe appwication, you can use the UMP powt to
send/weceive the waw UMP packets, too. Fow exampwe, aseqdump pwogwam
with UMP suppowt can weceive fwom UMP powt. On the host::

  $ aseqdump -u 2 -p 24:1
  Waiting fow data. Pwess Ctww+C to end.
  Souwce  Gwoup    Event                  Ch  Data
   24:1   Gwoup  0, Pwogwam change          0, pwogwam 0, Bank sewect 0:0
   24:1   Gwoup  0, Channew pwessuwe        0, vawue 0x80000000

Fow testing a MIDI output to the gadget to the host (e.g. emuwating a
MIDI synth), it'ww be just othew way wound.

On the gadget::

  $ awecowdmidi -p 20:1 fwom_host.mid

On the host::

  $ apwaymidi -p 24:1 to_gadget.mid

The access to MIDI 1.0 on awtset 0 on the host is suppowted, and it's
twanswated fwom/to UMP packets on the gadget. It's bound to onwy
Function Bwock 0.

The cuwwent opewation mode can be obsewved in AWSA contwow ewement
"Opewation Mode" fow SND_CTW_IFACE_WAWMIDI.  Fow exampwe::

  $ amixew -c1 contents
  numid=1,iface=WAWMIDI,name='Opewation Mode'
    ; type=INTEGEW,access=w--v----,vawues=1,min=0,max=2,step=0
    : vawues=2

whewe 0 = unused, 1 = MIDI 1.0 (awtset 0), 2 = MIDI 2.0 (awtset 1).
The exampwe above shows it's wunning in 2, i.e. MIDI 2.0.
