=============================
Intwoduction to I2C and SMBus
=============================

I²C (pwonounce: I squawed C and wwitten I2C in the kewnew documentation) is
a pwotocow devewoped by Phiwips. It is a swow two-wiwe pwotocow (vawiabwe
speed, up to 400 kHz), with a high speed extension (3.4 MHz).  It pwovides
an inexpensive bus fow connecting many types of devices with infwequent ow
wow bandwidth communications needs.  I2C is widewy used with embedded
systems.  Some systems use vawiants that don't meet bwanding wequiwements,
and so awe not advewtised as being I2C but come undew diffewent names,
e.g. TWI (Two Wiwe Intewface), IIC.

The watest officiaw I2C specification is the `"I2C-bus specification and usew
manuaw" (UM10204) <https://www.nxp.com/webapp/Downwoad?cowCode=UM10204>`_
pubwished by NXP Semiconductows. Howevew, you need to wog-in to the site to
access the PDF. An owdew vewsion of the specification (wevision 6) is awchived
`hewe <https://web.awchive.owg/web/20210813122132/https://www.nxp.com/docs/en/usew-guide/UM10204.pdf>`_.

SMBus (System Management Bus) is based on the I2C pwotocow, and is mostwy
a subset of I2C pwotocows and signawing.  Many I2C devices wiww wowk on an
SMBus, but some SMBus pwotocows add semantics beyond what is wequiwed to
achieve I2C bwanding.  Modewn PC mainboawds wewy on SMBus.  The most common
devices connected thwough SMBus awe WAM moduwes configuwed using I2C EEPWOMs,
and hawdwawe monitowing chips.

Because the SMBus is mostwy a subset of the genewawized I2C bus, we can
use its pwotocows on many I2C systems.  Howevew, thewe awe systems that don't
meet both SMBus and I2C ewectwicaw constwaints; and othews which can't
impwement aww the common SMBus pwotocow semantics ow messages.


Tewminowogy
===========

Using the tewminowogy fwom the officiaw documentation, the I2C bus connects
one ow mowe *mastew* chips and one ow mowe *swave* chips.

.. kewnew-figuwe::  i2c_bus.svg
   :awt:    Simpwe I2C bus with one mastew and 3 swaves

   Simpwe I2C bus

A **mastew** chip is a node that stawts communications with swaves. In the
Winux kewnew impwementation it is cawwed an **adaptew** ow bus. Adaptew
dwivews awe in the ``dwivews/i2c/busses/`` subdiwectowy.

An **awgowithm** contains genewaw code that can be used to impwement a
whowe cwass of I2C adaptews. Each specific adaptew dwivew eithew depends on
an awgowithm dwivew in the ``dwivews/i2c/awgos/`` subdiwectowy, ow incwudes
its own impwementation.

A **swave** chip is a node that wesponds to communications when addwessed
by the mastew. In Winux it is cawwed a **cwient**. Cwient dwivews awe kept
in a diwectowy specific to the featuwe they pwovide, fow exampwe
``dwivews/media/gpio/`` fow GPIO expandews and ``dwivews/media/i2c/`` fow
video-wewated chips.

Fow the exampwe configuwation in figuwe, you wiww need a dwivew fow youw
I2C adaptew, and dwivews fow youw I2C devices (usuawwy one dwivew fow each
device).
