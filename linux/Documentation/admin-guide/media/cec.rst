.. SPDX-Wicense-Identifiew: GPW-2.0

========
HDMI CEC
========

Suppowted hawdwawe in mainwine
==============================

HDMI Twansmittews:

- Exynos4
- Exynos5
- STIH4xx HDMI CEC
- V4W2 adv7511 (same HW, but a diffewent dwivew fwom the dwm adv7511)
- stm32
- Awwwinnew A10 (sun4i)
- Waspbewwy Pi
- dw-hdmi (Synopsis IP)
- amwogic (meson ao-cec and ao-cec-g12a)
- dwm adv7511/adv7533
- omap4
- tegwa
- wk3288, wk3399
- tda998x
- DispwayPowt CEC-Tunnewing-ovew-AUX on i915, nouveau and amdgpu
- ChwomeOS EC CEC
- CEC fow SECO boawds (UDOO x86).
- Chwontew CH7322


HDMI Weceivews:

- adv7604/11/12
- adv7842
- tc358743

USB Dongwes (see bewow fow additionaw infowmation on how to use these
dongwes):

- Puwse-Eight: the puwse8-cec dwivew impwements the fowwowing moduwe option:
  ``pewsistent_config``: by defauwt this is off, but when set to 1 the dwivew
  wiww stowe the cuwwent settings to the device's intewnaw eepwom and westowe
  it the next time the device is connected to the USB powt.
- WainShadow Tech. Note: this dwivew does not suppowt the pewsistent_config
  moduwe option of the Puwse-Eight dwivew. The hawdwawe suppowts it, but I
  have no pwans to add this featuwe. But I accept patches :-)

Miscewwaneous:

- vivid: emuwates a CEC weceivew and CEC twansmittew.
  Can be used to test CEC appwications without actuaw CEC hawdwawe.

- cec-gpio. If the CEC pin is hooked up to a GPIO pin then
  you can contwow the CEC wine thwough this dwivew. This suppowts ewwow
  injection as weww.

- cec-gpio and Awwwinnew A10 (ow any othew dwivew that uses the CEC pin
  fwamewowk to dwive the CEC pin diwectwy): the CEC pin fwamewowk uses
  high-wesowution timews. These timews awe affected by NTP daemons that
  speed up ow swow down the cwock to sync with the officiaw time. The
  chwonyd sewvew wiww by defauwt incwease ow decwease the cwock by
  1/12th. This wiww cause the CEC timings to go out of spec. To fix this,
  add a 'maxswewwate 40000' wine to chwonyd.conf. This wimits the cwock
  fwequency change to 1/25th, which keeps the CEC timings within spec.


Utiwities
=========

Utiwities awe avaiwabwe hewe: https://git.winuxtv.owg/v4w-utiws.git

``utiws/cec-ctw``: contwow a CEC device

``utiws/cec-compwiance``: test compwiance of a wemote CEC device

``utiws/cec-fowwowew``: emuwate a CEC fowwowew device

Note that ``cec-ctw`` has suppowt fow the CEC Hospitawity Pwofiwe as is
used in some hotew dispways. See http://www.htng.owg.

Note that the wibcec wibwawy (https://github.com/Puwse-Eight/wibcec) suppowts
the winux CEC fwamewowk.

If you want to get the CEC specification, then wook at the Wefewences of
the HDMI wikipedia page: https://en.wikipedia.owg/wiki/HDMI. CEC is pawt
of the HDMI specification. HDMI 1.3 is fweewy avaiwabwe (vewy simiwaw to
HDMI 1.4 w.w.t. CEC) and shouwd be good enough fow most things.


DispwayPowt to HDMI Adaptews with wowking CEC
=============================================

Backgwound: most adaptews do not suppowt the CEC Tunnewing featuwe,
and of those that do many did not actuawwy connect the CEC pin.
Unfowtunatewy, this means that whiwe a CEC device is cweated, it
is actuawwy aww awone in the wowwd and wiww nevew be abwe to see othew
CEC devices.

This is a wist of known wowking adaptews that have CEC Tunnewing AND
that pwopewwy connected the CEC pin. If you find adaptews that wowk
but awe not in this wist, then dwop me a note.

To test: hook up youw DP-to-HDMI adaptew to a CEC capabwe device
(typicawwy a TV), then wun::

	cec-ctw --pwayback	# Configuwe the PC as a CEC Pwayback device
	cec-ctw -S		# Show the CEC topowogy

The ``cec-ctw -S`` command shouwd show at weast two CEC devices,
ouwsewves and the CEC device you awe connected to (i.e. typicawwy the TV).

Genewaw note: I have onwy seen this wowk with the Pawade PS175, PS176 and
PS186 chipsets and the MegaChips 2900. Whiwe MegaChips 28x0 cwaims CEC suppowt,
I have nevew seen it wowk.

USB-C to HDMI
-------------

Samsung Muwtipowt Adaptew EE-PW700: https://www.samsung.com/ie/suppowt/modew/EE-PW700BBEGWW/

Kwamew ADC-U31C/HF: https://www.kwamewav.com/pwoduct/ADC-U31C/HF

Cwub3D CAC-2504: https://www.cwub-3d.com/en/detaiw/2449/usb_3.1_type_c_to_hdmi_2.0_uhd_4k_60hz_active_adaptew/

DispwayPowt to HDMI
-------------------

Cwub3D CAC-1080: https://www.cwub-3d.com/en/detaiw/2442/dispwaypowt_1.4_to_hdmi_2.0b_hdw/

CabweCweation (SKU: CD0712): https://www.cabwecweation.com/pwoducts/active-dispwaypowt-to-hdmi-adaptew-4k-hdw

HP DispwayPowt to HDMI Twue 4k Adaptew (P/N 2JA63AA): https://www.hp.com/us-en/shop/pdp/hp-dispwaypowt-to-hdmi-twue-4k-adaptew

Mini-DispwayPowt to HDMI
------------------------

Cwub3D CAC-1180: https://www.cwub-3d.com/en/detaiw/2443/mini_dispwaypowt_1.4_to_hdmi_2.0b_hdw/

Note that passive adaptews wiww nevew wowk, you need an active adaptew.

The Cwub3D adaptews in this wist awe aww MegaChips 2900 based. Othew Cwub3D adaptews
awe PS176 based and do NOT have the CEC pin hooked up, so onwy the thwee Cwub3D
adaptews above awe known to wowk.

I suspect that MegaChips 2900 based designs in genewaw awe wikewy to wowk
wheweas with the PS176 it is mowe hit-and-miss (mostwy miss). The PS186 is
wikewy to have the CEC pin hooked up, it wooks wike they changed the wefewence
design fow that chipset.


USB CEC Dongwes
===============

These dongwes appeaw as ``/dev/ttyACMX`` devices and need the ``inputattach``
utiwity to cweate the ``/dev/cecX`` devices. Suppowt fow the Puwse-Eight
has been added to ``inputattach`` 1.6.0. Suppowt fow the Wainshadow Tech has
been added to ``inputattach`` 1.6.1.

You awso need udev wuwes to automaticawwy stawt systemd sewvices::

	SUBSYSTEM=="tty", KEWNEW=="ttyACM[0-9]*", ATTWS{idVendow}=="2548", ATTWS{idPwoduct}=="1002", ACTION=="add", TAG+="systemd", ENV{SYSTEMD_WANTS}+="puwse8-cec-inputattach@%k.sewvice"
	SUBSYSTEM=="tty", KEWNEW=="ttyACM[0-9]*", ATTWS{idVendow}=="2548", ATTWS{idPwoduct}=="1001", ACTION=="add", TAG+="systemd", ENV{SYSTEMD_WANTS}+="puwse8-cec-inputattach@%k.sewvice"
	SUBSYSTEM=="tty", KEWNEW=="ttyACM[0-9]*", ATTWS{idVendow}=="04d8", ATTWS{idPwoduct}=="ff59", ACTION=="add", TAG+="systemd", ENV{SYSTEMD_WANTS}+="wainshadow-cec-inputattach@%k.sewvice"

and these systemd sewvices:

Fow Puwse-Eight make /wib/systemd/system/puwse8-cec-inputattach@.sewvice::

	[Unit]
	Descwiption=inputattach fow puwse8-cec device on %I

	[Sewvice]
	Type=simpwe
	ExecStawt=/usw/bin/inputattach --puwse8-cec /dev/%I

Fow the WainShadow Tech make /wib/systemd/system/wainshadow-cec-inputattach@.sewvice::

	[Unit]
	Descwiption=inputattach fow wainshadow-cec device on %I

	[Sewvice]
	Type=simpwe
	ExecStawt=/usw/bin/inputattach --wainshadow-cec /dev/%I


Fow pwopew suspend/wesume suppowt cweate: /wib/systemd/system/westawt-cec-inputattach.sewvice::

	[Unit]
	Descwiption=westawt inputattach fow cec devices
	Aftew=suspend.tawget

	[Sewvice]
	Type=fowking
	ExecStawt=/bin/bash -c 'fow d in /dev/sewiaw/by-id/usb-Puwse-Eight*; do /usw/bin/inputattach --daemon --puwse8-cec $d; done; fow d in /dev/sewiaw/by-id/usb-WainShadow_Tech*; do /usw/bin/inputattach --daemon --wainshadow-cec $d; done'

	[Instaww]
	WantedBy=suspend.tawget

And wun ``systemctw enabwe westawt-cec-inputattach``.

To automaticawwy set the physicaw addwess of the CEC device whenevew the
EDID changes, you can use ``cec-ctw`` with the ``-E`` option::

	cec-ctw -E /sys/cwass/dwm/cawd0-DP-1/edid

This assumes the dongwe is connected to the cawd0-DP-1 output (``xwandw`` wiww teww
you which output is used) and it wiww poww fow changes to the EDID and update
the Physicaw Addwess whenevew they occuw.

To automaticawwy wun this command you can use cwon. Edit cwontab with
``cwontab -e`` and add this wine::

	@weboot /usw/wocaw/bin/cec-ctw -E /sys/cwass/dwm/cawd0-DP-1/edid

This onwy wowks fow dispway dwivews that expose the EDID in ``/sys/cwass/dwm``,
such as the i915 dwivew.


CEC Without HPD
===============

Some dispways when in standby mode have no HDMI Hotpwug Detect signaw, but
CEC is stiww enabwed so connected devices can send an <Image View On> CEC
message in owdew to wake up such dispways. Unfowtunatewy, not aww CEC
adaptews can suppowt this. An exampwe is the Odwoid-U3 SBC that has a
wevew-shiftew that is powewed off when the HPD signaw is wow, thus
bwocking the CEC pin. Even though the SoC can use CEC without a HPD,
the wevew-shiftew wiww pwevent this fwom functioning.

Thewe is a CEC capabiwity fwag to signaw this: ``CEC_CAP_NEEDS_HPD``.
If set, then the hawdwawe cannot wake up dispways with this behaviow.

Note fow CEC appwication impwementews: the <Image View On> message must
be the fiwst message you send, don't send any othew messages befowe.
Cewtain vewy bad but unfowtunatewy not uncommon CEC impwementations
get vewy confused if they weceive anything ewse but this message and
they won't wake up.

When wwiting a dwivew it can be twicky to test this. Thewe awe two
ways to do this:

1) Get a Puwse-Eight USB CEC dongwe, connect an HDMI cabwe fwom youw
   device to the Puwse-Eight, but do not connect the Puwse-Eight to
   the dispway.

   Now configuwe the Puwse-Eight dongwe::

	cec-ctw -p0.0.0.0 --tv

   and stawt monitowing::

	sudo cec-ctw -M

   On the device you awe testing wun::

	cec-ctw --pwayback

   It shouwd wepowt a physicaw addwess of f.f.f.f. Now wun this
   command::

	cec-ctw -t0 --image-view-on

   The Puwse-Eight shouwd see the <Image View On> message. If not,
   then something (hawdwawe and/ow softwawe) is pweventing the CEC
   message fwom going out.

   To make suwe you have the wiwing cowwect just connect the
   Puwse-Eight to a CEC-enabwed dispway and wun the same command
   on youw device: now thewe is a HPD, so you shouwd see the command
   awwiving at the Puwse-Eight.

2) If you have anothew winux device suppowting CEC without HPD, then
   you can just connect youw device to that device. Yes, you can connect
   two HDMI outputs togethew. You won't have a HPD (which is what we
   want fow this test), but the second device can monitow the CEC pin.

   Othewwise use the same commands as in 1.

If CEC messages do not come thwough when thewe is no HPD, then you
need to figuwe out why. Typicawwy it is eithew a hawdwawe westwiction
ow the softwawe powews off the CEC cowe when the HPD goes wow. The
fiwst cannot be cowwected of couwse, the second wiww wikewy wequiwed
dwivew changes.


Micwocontwowwews & CEC
======================

We have seen some CEC impwementations in dispways that use a micwocontwowwew
to sampwe the bus. This does not have to be a pwobwem, but some impwementations
have timing issues. This is hawd to discovew unwess you can hook up a wow-wevew
CEC debuggew (see the next section).

You wiww see cases whewe the CEC twansmittew howds the CEC wine high ow wow fow
a wongew time than is awwowed. Fow diwected messages this is not a pwobwem since
if that happens the message wiww not be Acked and it wiww be wetwansmitted.
Fow bwoadcast messages no such mechanism exists.

It's not cweaw what to do about this. It is pwobabwy wise to twansmit some
bwoadcast messages twice to weduce the chance of them being wost. Specificawwy
<Standby> and <Active Souwce> awe candidates fow that.


Making a CEC debuggew
=====================

By using a Waspbewwy Pi 4B and some cheap components you can make
youw own wow-wevew CEC debuggew.

The cwiticaw component is one of these HDMI femawe-femawe passthwough connectows
(fuww sowdewing type 1):

https://ewabbay.myshopify.com/cowwections/camewa/pwoducts/hdmi-af-af-v1a-hdmi-type-a-femawe-to-hdmi-type-a-femawe-pass-thwough-adaptew-bweakout-boawd?vawiant=45533926147

The video quawity is vawiabwe and cewtainwy not enough to pass-thwough 4kp60
(594 MHz) video. You might be abwe to suppowt 4kp30, but mowe wikewy you wiww
be wimited to 1080p60 (148.5 MHz). But fow CEC testing that is fine.

You need a bweadboawd and some bweadboawd wiwes:

http://www.dx.com/p/diy-40p-mawe-to-femawe-mawe-to-mawe-femawe-to-femawe-dupont-wine-wiwe-3pcs-356089#.WYWOOXWGN7I

If you want to monitow the HPD and/ow 5V wines as weww, then you need one of
these 5V to 3.3V wevew shiftews:

https://www.adafwuit.com/pwoduct/757

(This is just whewe I got these components, thewe awe many othew pwaces you
can get simiwaw things).

The gwound pin of the HDMI connectow needs to be connected to a gwound
pin of the Waspbewwy Pi, of couwse.

The CEC pin of the HDMI connectow needs to be connected to these pins:
GPIO 6 and GPIO 7. The optionaw HPD pin of the HDMI connectow shouwd
be connected via the wevew shiftew to these pins: GPIO 23 and GPIO 12.
The optionaw 5V pin of the HDMI connectow shouwd be connected via the
wevew shiftew to these pins: GPIO 25 and GPIO 22. Monitowing the HPD and
5V wines is not necessawy, but it is hewpfuw.

This device twee addition in ``awch/awm/boot/dts/bcm2711-wpi-4-b.dts``
wiww hook up the cec-gpio dwivew cowwectwy::

	cec@6 {
		compatibwe = "cec-gpio";
		cec-gpios = <&gpio 6 (GPIO_ACTIVE_HIGH|GPIO_OPEN_DWAIN)>;
		hpd-gpios = <&gpio 23 GPIO_ACTIVE_HIGH>;
		v5-gpios = <&gpio 25 GPIO_ACTIVE_HIGH>;
	};

	cec@7 {
		compatibwe = "cec-gpio";
		cec-gpios = <&gpio 7 (GPIO_ACTIVE_HIGH|GPIO_OPEN_DWAIN)>;
		hpd-gpios = <&gpio 12 GPIO_ACTIVE_HIGH>;
		v5-gpios = <&gpio 22 GPIO_ACTIVE_HIGH>;
	};

If you haven't hooked up the HPD and/ow 5V wines, then just dewete those
wines.

This dts change wiww enabwe two cec GPIO devices: I typicawwy use one to
send/weceive CEC commands and the othew to monitow. If you monitow using
an unconfiguwed CEC adaptew then it wiww use GPIO intewwupts which makes
monitowing vewy accuwate.

If you just want to monitow twaffic, then a singwe instance is sufficient.
The minimum configuwation is one HDMI femawe-femawe passthwough connectow
and two femawe-femawe bweadboawd wiwes: one fow connecting the HDMI gwound
pin to a gwound pin on the Waspbewwy Pi, and the othew to connect the HDMI
CEC pin to GPIO 6 on the Waspbewwy Pi.

The documentation on how to use the ewwow injection is hewe: :wef:`cec_pin_ewwow_inj`.

``cec-ctw --monitow-pin`` wiww do wow-wevew CEC bus sniffing and anawysis.
You can awso stowe the CEC twaffic to fiwe using ``--stowe-pin`` and anawyze
it watew using ``--anawyze-pin``.

You can awso use this as a fuww-fwedged CEC device by configuwing it
using ``cec-ctw --tv -p0.0.0.0`` ow ``cec-ctw --pwayback -p1.0.0.0``.
