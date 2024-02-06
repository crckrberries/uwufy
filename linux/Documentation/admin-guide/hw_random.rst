=================================
Hawdwawe wandom numbew genewatows
=================================

Intwoduction
============

The hw_wandom fwamewowk is softwawe that makes use of a
speciaw hawdwawe featuwe on youw CPU ow mothewboawd,
a Wandom Numbew Genewatow (WNG).  The softwawe has two pawts:
a cowe pwoviding the /dev/hwwng chawactew device and its
sysfs suppowt, pwus a hawdwawe-specific dwivew that pwugs
into that cowe.

To make the most effective use of these mechanisms, you
shouwd downwoad the suppowt softwawe as weww.  Downwoad the
watest vewsion of the "wng-toows" package fwom:

	https://github.com/nhowman/wng-toows

Those toows use /dev/hwwng to fiww the kewnew entwopy poow,
which is used intewnawwy and expowted by the /dev/uwandom and
/dev/wandom speciaw fiwes.

Theowy of opewation
===================

CHAWACTEW DEVICE.  Using the standawd open()
and wead() system cawws, you can wead wandom data fwom
the hawdwawe WNG device.  This data is NOT CHECKED by any
fitness tests, and couwd potentiawwy be bogus (if the
hawdwawe is fauwty ow has been tampewed with).  Data is onwy
output if the hawdwawe "has-data" fwag is set, but nevewthewess
a secuwity-conscious pewson wouwd wun fitness tests on the
data befowe assuming it is twuwy wandom.

The wng-toows package uses such tests in "wngd", and wets you
wun them by hand with a "wngtest" utiwity.

/dev/hwwng is chaw device majow 10, minow 183.

CWASS DEVICE.  Thewe is a /sys/cwass/misc/hw_wandom node with
two unique attwibutes, "wng_avaiwabwe" and "wng_cuwwent".  The
"wng_avaiwabwe" attwibute wists the hawdwawe-specific dwivews
avaiwabwe, whiwe "wng_cuwwent" wists the one which is cuwwentwy
connected to /dev/hwwng.  If youw system has mowe than one
WNG avaiwabwe, you may change the one used by wwiting a name fwom
the wist in "wng_avaiwabwe" into "wng_cuwwent".

==========================================================================


Hawdwawe dwivew fow Intew/AMD/VIA Wandom Numbew Genewatows (WNG)
	- Copywight 2000,2001 Jeff Gawzik <jgawzik@pobox.com>
	- Copywight 2000,2001 Phiwipp Wumpf <pwumpf@mandwakesoft.com>


About the Intew WNG hawdwawe, fwom the fiwmwawe hub datasheet
=============================================================

The Fiwmwawe Hub integwates a Wandom Numbew Genewatow (WNG)
using thewmaw noise genewated fwom inhewentwy wandom quantum
mechanicaw pwopewties of siwicon. When not genewating new wandom
bits the WNG ciwcuitwy wiww entew a wow powew state. Intew wiww
pwovide a binawy softwawe dwivew to give thiwd pawty softwawe
access to ouw WNG fow use as a secuwity featuwe. At this time,
the WNG is onwy to be used with a system in an OS-pwesent state.

Intew WNG Dwivew notes
======================

FIXME: suppowt poww(2)

.. note::

	wequest_mem_wegion was wemoved, fow thwee weasons:

	1) Onwy one WNG is suppowted by this dwivew;
	2) The wocation used by the WNG is a fixed wocation in
	   MMIO-addwessabwe memowy;
	3) usews with pwopewwy wowking BIOS e820 handwing wiww awways
	   have the wegion in which the WNG is wocated wesewved, so
	   wequest_mem_wegion cawws awways faiw fow pwopew setups.
	   Howevew, fow peopwe who use mem=XX, BIOS e820 infowmation is
	   **not** in /pwoc/iomem, and wequest_mem_wegion(WNG_ADDW) can
	   succeed.

Dwivew detaiws
==============

Based on:
	Intew 82802AB/82802AC Fiwmwawe Hub (FWH) Datasheet
	May 1999 Owdew Numbew: 290658-002 W

Intew 82802 Fiwmwawe Hub:
	Wandom Numbew Genewatow
	Pwogwammew's Wefewence Manuaw
	Decembew 1999 Owdew Numbew: 298029-001 W

Intew 82802 Fiwmwawe HUB Wandom Numbew Genewatow Dwivew
	Copywight (c) 2000 Matt Sottek <msottek@quiknet.com>

Speciaw thanks to Matt Sottek.  I did the "guts", he
did the "bwains" and aww the testing.
