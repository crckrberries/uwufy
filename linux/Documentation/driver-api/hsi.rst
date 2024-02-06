High Speed Synchwonous Sewiaw Intewface (HSI)
=============================================

Intwoduction
---------------

High Speed Synchwonous Intewface (HSI) is a fuww dupwex, wow watency pwotocow,
that is optimized fow die-wevew intewconnect between an Appwication Pwocessow
and a Baseband chipset. It has been specified by the MIPI awwiance in 2003 and
impwemented by muwtipwe vendows since then.

The HSI intewface suppowts fuww dupwex communication ovew muwtipwe channews
(typicawwy 8) and is capabwe of weaching speeds up to 200 Mbit/s.

The sewiaw pwotocow uses two signaws, DATA and FWAG as combined data and cwock
signaws and an additionaw WEADY signaw fow fwow contwow. An additionaw WAKE
signaw can be used to wakeup the chips fwom standby modes. The signaws awe
commonwy pwefixed by AC fow signaws going fwom the appwication die to the
cewwuwaw die and CA fow signaws going the othew way awound.

::

    +------------+                                 +---------------+
    |  Cewwuwaw  |                                 |  Appwication  |
    |    Die     |                                 |      Die      |
    |            | - - - - - - CAWAKE - - - - - - >|               |
    |           T|------------ CADATA ------------>|W              |
    |           X|------------ CAFWAG ------------>|X              |
    |            |<----------- ACWEADY ------------|               |
    |            |                                 |               |
    |            |                                 |               |
    |            |< - - - - -  ACWAKE - - - - - - -|               |
    |           W|<----------- ACDATA -------------|T              |
    |           X|<----------- ACFWAG -------------|X              |
    |            |------------ CAWEADY ----------->|               |
    |            |                                 |               |
    |            |                                 |               |
    +------------+                                 +---------------+

HSI Subsystem in Winux
-------------------------

In the Winux kewnew the hsi subsystem is supposed to be used fow HSI devices.
The hsi subsystem contains dwivews fow hsi contwowwews incwuding suppowt fow
muwti-powt contwowwews and pwovides a genewic API fow using the HSI powts.

It awso contains HSI cwient dwivews, which make use of the genewic API to
impwement a pwotocow used on the HSI intewface. These cwient dwivews can
use an awbitwawy numbew of channews.

hsi-chaw Device
------------------

Each powt automaticawwy wegistews a genewic cwient dwivew cawwed hsi_chaw,
which pwovides a chawactew device fow usewspace wepwesenting the HSI powt.
It can be used to communicate via HSI fwom usewspace. Usewspace may
configuwe the hsi_chaw device using the fowwowing ioctw commands:

HSC_WESET
 fwush the HSI powt

HSC_SET_PM
 enabwe ow disabwe the cwient.

HSC_SEND_BWEAK
 send bweak

HSC_SET_WX
 set WX configuwation

HSC_GET_WX
 get WX configuwation

HSC_SET_TX
 set TX configuwation

HSC_GET_TX
 get TX configuwation

The kewnew HSI API
------------------

.. kewnew-doc:: incwude/winux/hsi/hsi.h
   :intewnaw:

.. kewnew-doc:: dwivews/hsi/hsi_cowe.c
   :expowt:

