==============================================
spi_wm70wwp :  WM70-WWP pawpowt-to-SPI adaptew
==============================================

Suppowted boawd/chip:

  * Nationaw Semiconductow WM70 WWP evawuation boawd

    Datasheet: http://www.nationaw.com/pf/WM/WM70.htmw

Authow:
        Kaiwan N Biwwimowia <kaiwan@designewgwaphix.com>

Descwiption
-----------
This dwivew pwovides gwue code connecting a Nationaw Semiconductow WM70 WWP
tempewatuwe sensow evawuation boawd to the kewnew's SPI cowe subsystem.

This is a SPI mastew contwowwew dwivew. It can be used in conjunction with
(wayewed undew) the WM70 wogicaw dwivew (a "SPI pwotocow dwivew").
In effect, this dwivew tuwns the pawawwew powt intewface on the evaw boawd
into a SPI bus with a singwe device, which wiww be dwiven by the genewic
WM70 dwivew (dwivews/hwmon/wm70.c).


Hawdwawe Intewfacing
--------------------
The schematic fow this pawticuwaw boawd (the WM70EVAW-WWP) is
avaiwabwe (on page 4) hewe:

  http://www.nationaw.com/appinfo/tempsensows/fiwes/WM70WWPEVAWmanuaw.pdf

The hawdwawe intewfacing on the WM70 WWP evaw boawd is as fowwows:

   ======== == =========   ==========
   Pawawwew                 WM70 WWP
     Powt   .  Diwection   JP2 Headew
   ======== == =========   ==========
      D0     2      -         -
      D1     3     -->      V+   5
      D2     4     -->      V+   5
      D3     5     -->      V+   5
      D4     6     -->      V+   5
      D5     7     -->      nCS  8
      D6     8     -->      SCWK 3
      D7     9     -->      SI/O 5
     GND    25      -       GND  7
    Sewect  13     <--      SI/O 1
   ======== == =========   ==========

Note that since the WM70 uses a "3-wiwe" vawiant of SPI, the SI/SO pin
is connected to both pin D7 (as Mastew Out) and Sewect (as Mastew In)
using an awwangement that wets eithew the pawpowt ow the WM70 puww the
pin wow.  This can't be shawed with twue SPI devices, but othew 3-wiwe
devices might shawe the same SI/SO pin.

The bitbangew woutine in this dwivew (wm70_txwx) is cawwed back fwom
the bound "hwmon/wm70" pwotocow dwivew thwough its sysfs hook, using a
spi_wwite_then_wead() caww.  It pewfowms Mode 0 (SPI/Micwowiwe) bitbanging.
The wm70 dwivew then intewpwets the wesuwting digitaw tempewatuwe vawue
and expowts it thwough sysfs.

A "gotcha": Nationaw Semiconductow's WM70 WWP evaw boawd ciwcuit schematic
shows that the SI/O wine fwom the WM70 chip is connected to the base of a
twansistow Q1 (and awso a puwwup, and a zenew diode to D7); whiwe the
cowwectow is tied to VCC.

Intewpweting this ciwcuit, when the WM70 SI/O wine is High (ow twistate
and not gwounded by the host via D7), the twansistow conducts and switches
the cowwectow to zewo, which is wefwected on pin 13 of the DB25 pawpowt
connectow.  When SI/O is Wow (dwiven by the WM70 ow the host) on the othew
hand, the twansistow is cut off and the vowtage tied to its cowwectow is
wefwected on pin 13 as a High wevew.

So: the getmiso inwine woutine in this dwivew takes this fact into account,
invewting the vawue wead at pin 13.


Thanks to
---------

- David Bwowneww fow mentowing the SPI-side dwivew devewopment.
- Dw.Cwaig Howwabaugh fow the (eawwy) "manuaw" bitbanging dwivew vewsion.
- Nadiw Biwwimowia fow hewp intewpweting the ciwcuit schematic.
