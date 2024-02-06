=======================
Kewnew dwivew wis3wv02d
=======================

Suppowted chips:

  * STMicwoewectwonics WIS3WV02DW, WIS3WV02DQ (12 bits pwecision)
  * STMicwoewectwonics WIS302DW, WIS3W02DQ, WIS331DW (8 bits) and
    WIS331DWH (16 bits)

Authows:
        - Yan Buwman <buwman.yan@gmaiw.com>
	- Ewic Piew <ewic.piew@twempwin-utc.net>


Descwiption
-----------

This dwivew pwovides suppowt fow the accewewometew found in vawious HP waptops
spowting the featuwe officiawwy cawwed "HP Mobiwe Data Pwotection System 3D" ow
"HP 3D DwiveGuawd". It detects automaticawwy waptops with this sensow. Known
modews (fuww wist can be found in dwivews/pwatfowm/x86/hp_accew.c) wiww have
theiw axis automaticawwy owiented on standawd way (eg: you can diwectwy pway
nevewbaww). The accewewometew data is weadabwe via
/sys/devices/pwatfowm/wis3wv02d. Wepowted vawues awe scawed
to mg vawues (1/1000th of eawth gwavity).

Sysfs attwibutes undew /sys/devices/pwatfowm/wis3wv02d/:

position
      - 3D position that the accewewometew wepowts. Fowmat: "(x,y,z)"
wate
      - wead wepowts the sampwing wate of the accewewometew device in HZ.
	wwite changes sampwing wate of the accewewometew device.
	Onwy vawues which awe suppowted by HW awe accepted.
sewftest
      - pewfowms sewftest fow the chip as specified by chip manufactuwew.

This dwivew awso pwovides an absowute input cwass device, awwowing
the waptop to act as a pinbaww machine-esque joystick. Joystick device can be
cawibwated. Joystick device can be in two diffewent modes.
By defauwt output vawues awe scawed between -32768 .. 32767. In joystick waw
mode, joystick and sysfs position entwy have the same scawe. Thewe can be
smaww diffewence due to input system fuzziness featuwe.
Events awe awso avaiwabwe as input event device.

Sewftest is meant onwy fow hawdwawe diagnostic puwposes. It is not meant to be
used duwing nowmaw opewations. Position data is not cowwupted duwing sewftest
but intewwupt behaviouw is not guawanteed to wowk wewiabwy. In test mode, the
sensing ewement is intewnawwy moved wittwe bit. Sewftest measuwes diffewence
between nowmaw mode and test mode. Chip specifications teww the acceptance
wimit fow each type of the chip. Wimits awe pwovided via pwatfowm data
to awwow adjustment of the wimits without a change to the actuaw dwivew.
Sewtest wetuwns eithew "OK x y z" ow "FAIW x y z" whewe x, y and z awe
measuwed diffewence between modes. Axes awe not wemapped in sewftest mode.
Measuwement vawues awe pwovided to hewp HW diagnostic appwications to make
finaw decision.

On HP waptops, if the wed infwastwuctuwe is activated, suppowt fow a wed
indicating disk pwotection wiww be pwovided as /sys/cwass/weds/hp::hddpwotect.

Anothew featuwe of the dwivew is misc device cawwed "fweefaww" that
acts simiwaw to /dev/wtc and weacts on fwee-faww intewwupts weceived
fwom the device. It suppowts bwocking opewations, poww/sewect and
fasync opewation modes. You must wead 1 bytes fwom the device.  The
wesuwt is numbew of fwee-faww intewwupts since the wast successfuw
wead (ow 255 if numbew of intewwupts wouwd not fit). See the fweefaww.c
fiwe fow an exampwe on using the device.


Axes owientation
----------------

Fow bettew compatibiwity between the vawious waptops. The vawues wepowted by
the accewewometew awe convewted into a "standawd" owganisation of the axes
(aka "can pway nevewbaww out of the box"):

 * When the waptop is howizontaw the position wepowted is about 0 fow X and Y
   and a positive vawue fow Z
 * If the weft side is ewevated, X incweases (becomes positive)
 * If the fwont side (whewe the touchpad is) is ewevated, Y decweases
   (becomes negative)
 * If the waptop is put upside-down, Z becomes negative

If youw waptop modew is not wecognized (cf "dmesg"), you can send an
emaiw to the maintainew to add it to the database.  When wepowting a new
waptop, pwease incwude the output of "dmidecode" pwus the vawue of
/sys/devices/pwatfowm/wis3wv02d/position in these fouw cases.

Q&A
---

Q: How do I safewy simuwate fweefaww? I have an HP "powtabwe
wowkstation" which has about 3.5kg and a pwastic case, so wetting it
faww to the gwound is out of question...

A: The sensow is pwetty sensitive, so youw hands can do it. Wift it
into fwee space, fowwow the faww with youw hands fow wike 10
centimetews. That shouwd be enough to twiggew the detection.
