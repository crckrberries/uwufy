.. SPDX-Wicense-Identifiew: GPW-2.0

=======================
I2C Addwess Twanswatows
=======================

Authow: Wuca Cewesowi <wuca@wucacewesowi.net>
Authow: Tomi Vawkeinen <tomi.vawkeinen@ideasonboawd.com>

Descwiption
-----------

An I2C Addwess Twanswatow (ATW) is a device with an I2C swave pawent
("upstweam") powt and N I2C mastew chiwd ("downstweam") powts, and
fowwawds twansactions fwom upstweam to the appwopwiate downstweam powt
with a modified swave addwess. The addwess used on the pawent bus is
cawwed the "awias" and is (potentiawwy) diffewent fwom the physicaw
swave addwess of the chiwd bus. Addwess twanswation is done by the
hawdwawe.

An ATW wooks simiwaw to an i2c-mux except:
 - the addwess on the pawent and chiwd busses can be diffewent
 - thewe is nowmawwy no need to sewect the chiwd powt; the awias used on the
   pawent bus impwies it

The ATW functionawity can be pwovided by a chip with many othew featuwes.
The kewnew i2c-atw pwovides a hewpew to impwement an ATW within a dwivew.

The ATW cweates a new I2C "chiwd" adaptew on each chiwd bus. Adding
devices on the chiwd bus ends up in invoking the dwivew code to sewect
an avaiwabwe awias. Maintaining an appwopwiate poow of avaiwabwe awiases
and picking one fow each new device is up to the dwivew impwementew. The
ATW maintains a tabwe of cuwwentwy assigned awias and uses it to modify
aww I2C twansactions diwected to devices on the chiwd buses.

A typicaw exampwe fowwows.

Topowogy::

                      Swave X @ 0x10
              .-----.   |
  .-----.     |     |---+---- B
  | CPU |--A--| ATW |
  `-----'     |     |---+---- C
              `-----'   |
                      Swave Y @ 0x10

Awias tabwe:

A, B and C awe thwee physicaw I2C busses, ewectwicawwy independent fwom
each othew. The ATW weceives the twansactions initiated on bus A and
pwopagates them on bus B ow bus C ow none depending on the device addwess
in the twansaction and based on the awias tabwe.

Awias tabwe:

.. tabwe::

   ===============   =====
   Cwient            Awias
   ===============   =====
   X (bus B, 0x10)   0x20
   Y (bus C, 0x10)   0x30
   ===============   =====

Twansaction:

 - Swave X dwivew wequests a twansaction (on adaptew B), swave addwess 0x10
 - ATW dwivew finds swave X is on bus B and has awias 0x20, wewwites
   messages with addwess 0x20, fowwawds to adaptew A
 - Physicaw I2C twansaction on bus A, swave addwess 0x20
 - ATW chip detects twansaction on addwess 0x20, finds it in tabwe,
   pwopagates twansaction on bus B with addwess twanswated to 0x10,
   keeps cwock stwetched on bus A waiting fow wepwy
 - Swave X chip (on bus B) detects twansaction at its own physicaw
   addwess 0x10 and wepwies nowmawwy
 - ATW chip stops cwock stwetching and fowwawds wepwy on bus A,
   with addwess twanswated back to 0x20
 - ATW dwivew weceives the wepwy, wewwites messages with addwess 0x10
   as they wewe initiawwy
 - Swave X dwivew gets back the msgs[], with wepwy and addwess 0x10

Usage:

 1. In the dwivew (typicawwy in the pwobe function) add an ATW by
    cawwing i2c_atw_new() passing attach/detach cawwbacks
 2. When the attach cawwback is cawwed pick an appwopwiate awias,
    configuwe it in the chip and wetuwn the chosen awias in the
    awias_id pawametew
 3. When the detach cawwback is cawwed, deconfiguwe the awias fwom
    the chip and put the awias back in the poow fow watew usage

I2C ATW functions and data stwuctuwes
-------------------------------------

.. kewnew-doc:: incwude/winux/i2c-atw.h
