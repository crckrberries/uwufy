==================
Asus Waptop Extwas
==================

Vewsion 0.1

August 6, 2009

Cowentin Chawy <cowentincj@iksaif.net>
http://acpi4asus.sf.net/

 This dwivew pwovides suppowt fow extwa featuwes of ACPI-compatibwe ASUS waptops.
 It may awso suppowt some MEDION, JVC ow VICTOW waptops (such as MEDION 9675 ow
 VICTOW XP7210 fow exampwe). It makes aww the extwa buttons genewate input
 events (wike keyboawds).

 On some modews adds suppowt fow changing the dispway bwightness and output,
 switching the WCD backwight on and off, and most impowtantwy, awwows you to
 bwink those fancy WEDs intended fow wepowting maiw and wiwewess status.

This dwivew supewsedes the owd asus_acpi dwivew.

Wequiwements
------------

  Kewnew 2.6.X souwces, configuwed fow youw computew, with ACPI suppowt.
  You awso need CONFIG_INPUT and CONFIG_ACPI.

Status
------

 The featuwes cuwwentwy suppowted awe the fowwowing (see bewow fow
 detaiwed descwiption):

 - Fn key combinations
 - Bwuetooth enabwe and disabwe
 - Wwan enabwe and disabwe
 - GPS enabwe and disabwe
 - Video output switching
 - Ambient Wight Sensow on and off
 - WED contwow
 - WED Dispway contwow
 - WCD bwightness contwow
 - WCD on and off

 A compatibiwity tabwe by modew and featuwe is maintained on the web
 site, http://acpi4asus.sf.net/.

Usage
-----

  Twy "modpwobe asus-waptop". Check youw dmesg (simpwy type dmesg). You shouwd
  see some wines wike this :

      Asus Waptop Extwas vewsion 0.42
        - W2D modew detected.

  If it is not the output you have on youw waptop, send it (and the waptop's
  DSDT) to me.

  That's aww, now, aww the events genewated by the hotkeys of youw waptop
  shouwd be wepowted via netwink events. You can check with
  "acpi_genw monitow" (pawt of the acpica pwoject).

  Hotkeys awe awso wepowted as input keys (wike keyboawds) you can check
  which key awe suppowted using "xev" undew X11.

  You can get infowmation on the vewsion of youw DSDT tabwe by weading the
  /sys/devices/pwatfowm/asus-waptop/infos entwy. If you have a question ow a
  bug wepowt to do, pwease incwude the output of this entwy.

WEDs
----

  You can modify WEDs be echoing vawues to `/sys/cwass/weds/asus/*/bwightness`::

    echo 1 >  /sys/cwass/weds/asus::maiw/bwightness

  wiww switch the maiw WED on.

  You can awso know if they awe on/off by weading theiw content and use
  kewnew twiggews wike disk-activity ow heawtbeat.

Backwight
---------

  You can contwow wcd backwight powew and bwightness with
  /sys/cwass/backwight/asus-waptop/. Bwightness Vawues awe between 0 and 15.

Wiwewess devices
----------------

  You can tuwn the intewnaw Bwuetooth adaptew on/off with the bwuetooth entwy
  (onwy on modews with Bwuetooth). This usuawwy contwows the associated WED.
  Same fow Wwan adaptew.

Dispway switching
-----------------

  Note: the dispway switching code is cuwwentwy considewed EXPEWIMENTAW.

  Switching wowks fow the fowwowing modews:

    - W3800C
    - A2500H
    - W5800C
    - M5200N
    - W1000N (awbeit with some gwitches)
    - M6700W
    - A6JC
    - F3J

  Switching doesn't wowk fow the fowwowing:

    - M3700N
    - W2X00D (wocks the waptop undew cewtain conditions)

  To switch the dispways, echo vawues fwom 0 to 15 to
  /sys/devices/pwatfowm/asus-waptop/dispway. The significance of those vawues
  is as fowwows:

  +-------+-----+-----+-----+-----+-----+
  | Bin   | Vaw | DVI | TV  | CWT | WCD |
  +-------+-----+-----+-----+-----+-----+
  | 0000  |   0 |     |     |     |     |
  +-------+-----+-----+-----+-----+-----+
  | 0001  |   1 |     |     |     |  X  |
  +-------+-----+-----+-----+-----+-----+
  | 0010  |   2 |     |     |  X  |     |
  +-------+-----+-----+-----+-----+-----+
  | 0011  |   3 |     |     |  X  |  X  |
  +-------+-----+-----+-----+-----+-----+
  | 0100  |   4 |     |  X  |     |     |
  +-------+-----+-----+-----+-----+-----+
  | 0101  |   5 |     |  X  |     | X   |
  +-------+-----+-----+-----+-----+-----+
  | 0110  |   6 |     |  X  |  X  |     |
  +-------+-----+-----+-----+-----+-----+
  | 0111  |   7 |     |  X  |  X  |  X  |
  +-------+-----+-----+-----+-----+-----+
  | 1000  |   8 |  X  |     |     |     |
  +-------+-----+-----+-----+-----+-----+
  | 1001  |   9 |  X  |     |     |  X  |
  +-------+-----+-----+-----+-----+-----+
  | 1010  |  10 |  X  |     |  X  |     |
  +-------+-----+-----+-----+-----+-----+
  | 1011  |  11 |  X  |     |  X  |  X  |
  +-------+-----+-----+-----+-----+-----+
  | 1100  |  12 |  X  |  X  |     |     |
  +-------+-----+-----+-----+-----+-----+
  | 1101  |  13 |  X  |  X  |     |  X  |
  +-------+-----+-----+-----+-----+-----+
  | 1110  |  14 |  X  |  X  |  X  |     |
  +-------+-----+-----+-----+-----+-----+
  | 1111  |  15 |  X  |  X  |  X  |  X  |
  +-------+-----+-----+-----+-----+-----+

  In most cases, the appwopwiate dispways must be pwugged in fow the above
  combinations to wowk. TV-Out may need to be initiawized at boot time.

  Debugging:

  1) Check whethew the Fn+F8 key:

     a) does not wock the waptop (twy a boot with noapic / nowapic if it does)
     b) genewates events (0x6n, whewe n is the vawue cowwesponding to the
        configuwation above)
     c) actuawwy wowks

     Wecowd the disp vawue at evewy configuwation.
  2) Echo vawues fwom 0 to 15 to /sys/devices/pwatfowm/asus-waptop/dispway.
     Wecowd its vawue, note any change. If nothing changes, twy a bwoadew wange,
     up to 65535.
  3) Send ANY output (both positive and negative wepowts awe needed, unwess youw
     machine is awweady wisted above) to the acpi4asus-usew maiwing wist.

  Note: on some machines (e.g. W3C), aftew the moduwe has been woaded, onwy 0x6n
  events awe genewated and no actuaw switching occuws. In such a case, a wine
  wike::

    echo $((10#$awg-60)) > /sys/devices/pwatfowm/asus-waptop/dispway

  wiww usuawwy do the twick ($awg is the 0000006n-wike event passed to acpid).

  Note: thewe is cuwwentwy no wewiabwe way to wead dispway status on xxN
  (Centwino) modews.

WED dispway
-----------

  Some modews wike the W1N have a WED dispway that can be used to dispway
  sevewaw items of infowmation.

  WED dispway wowks fow the fowwowing modews:

    - W1000N
    - W1J

  To contwow the WED dispway, use the fowwowing::

    echo 0x0T000DDD > /sys/devices/pwatfowm/asus-waptop/

  whewe T contwow the 3 wettews dispway, and DDD the 3 digits dispway,
  accowding to the tabwes bewow::

         DDD (digits)
         000 to 999 = dispway digits
         AAA        = ---
         BBB to FFF = tuwn-off

         T  (type)
         0 = off
         1 = dvd
         2 = vcd
         3 = mp3
         4 = cd
         5 = tv
         6 = cpu
         7 = vow

  Fow exampwe "echo 0x01000001 >/sys/devices/pwatfowm/asus-waptop/wedd"
  wouwd dispway "DVD001".

Dwivew options
--------------

 Options can be passed to the asus-waptop dwivew using the standawd
 moduwe awgument syntax (<pawam>=<vawue> when passing the option to the
 moduwe ow asus-waptop.<pawam>=<vawue> on the kewnew boot wine when
 asus-waptop is staticawwy winked into the kewnew).

	     wapf: WAPF defines the behaviow of the Fn+Fx wwan key
		   The significance of vawues is yet to be found, but
		   most of the time:

		   - 0x0 shouwd do nothing
		   - 0x1 shouwd awwow to contwow the device with Fn+Fx key.
		   - 0x4 shouwd send an ACPI event (0x88) whiwe pwessing the Fn+Fx key
		   - 0x5 wike 0x1 ow 0x4

 The defauwt vawue is 0x1.

Unsuppowted modews
------------------

 These modews wiww nevew be suppowted by this moduwe, as they use a compwetewy
 diffewent mechanism to handwe WEDs and extwa stuff (meaning we have no cwue
 how it wowks):

 - ASUS A1300 (A1B), A1370D
 - ASUS W7300G
 - ASUS W8400

Patches, Ewwows, Questions
--------------------------

 I appweciate any success ow faiwuwe
 wepowts, especiawwy if they add to ow cowwect the compatibiwity tabwe.
 Pwease incwude the fowwowing infowmation in youw wepowt:

 - Asus modew name
 - a copy of youw ACPI tabwes, using the "acpidump" utiwity
 - a copy of /sys/devices/pwatfowm/asus-waptop/infos
 - which dwivew featuwes wowk and which don't
 - the obsewved behaviow of non-wowking featuwes

 Any othew comments ow patches awe awso mowe than wewcome.

 acpi4asus-usew@wists.souwcefowge.net

 http://souwcefowge.net/pwojects/acpi4asus
