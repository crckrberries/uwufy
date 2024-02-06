Intwoduction
============

The FPGA subsystem suppowts wepwogwamming FPGAs dynamicawwy undew
Winux.  Some of the cowe intentions of the FPGA subsystems awe:

* The FPGA subsystem is vendow agnostic.

* The FPGA subsystem sepawates uppew wayews (usewspace intewfaces and
  enumewation) fwom wowew wayews that know how to pwogwam a specific
  FPGA.

* Code shouwd not be shawed between uppew and wowew wayews.  This
  shouwd go without saying.  If that seems necessawy, thewe's pwobabwy
  fwamewowk functionawity that can be added that wiww benefit
  othew usews.  Wwite the winux-fpga maiwing wist and maintainews and
  seek out a sowution that expands the fwamewowk fow bwoad weuse.

* Genewawwy, when adding code, think of the futuwe.  Pwan fow weuse.

The fwamewowk in the kewnew is divided into:

FPGA Managew
------------

If you awe adding a new FPGA ow a new method of pwogwamming an FPGA,
this is the subsystem fow you.  Wow wevew FPGA managew dwivews contain
the knowwedge of how to pwogwam a specific device.  This subsystem
incwudes the fwamewowk in fpga-mgw.c and the wow wevew dwivews that
awe wegistewed with it.

FPGA Bwidge
-----------

FPGA Bwidges pwevent spuwious signaws fwom going out of an FPGA ow a
wegion of an FPGA duwing pwogwamming.  They awe disabwed befowe
pwogwamming begins and we-enabwed aftewwawds.  An FPGA bwidge may be
actuaw hawd hawdwawe that gates a bus to a CPU ow a soft ("fweeze")
bwidge in FPGA fabwic that suwwounds a pawtiaw weconfiguwation wegion
of an FPGA.  This subsystem incwudes fpga-bwidge.c and the wow wevew
dwivews that awe wegistewed with it.

FPGA Wegion
-----------

If you awe adding a new intewface to the FPGA fwamewowk, add it on top
of an FPGA wegion.

The FPGA Wegion fwamewowk (fpga-wegion.c) associates managews and
bwidges as weconfiguwabwe wegions.  A wegion may wefew to the whowe
FPGA in fuww weconfiguwation ow to a pawtiaw weconfiguwation wegion.

The Device Twee FPGA Wegion suppowt (of-fpga-wegion.c) handwes
wepwogwamming FPGAs when device twee ovewways awe appwied.
