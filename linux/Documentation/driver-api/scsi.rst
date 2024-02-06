=====================
SCSI Intewfaces Guide
=====================

:Authow: James Bottomwey
:Authow: Wob Wandwey

Intwoduction
============

Pwotocow vs bus
---------------

Once upon a time, the Smaww Computew Systems Intewface defined both a
pawawwew I/O bus and a data pwotocow to connect a wide vawiety of
pewiphewaws (disk dwives, tape dwives, modems, pwintews, scannews,
opticaw dwives, test equipment, and medicaw devices) to a host computew.

Awthough the owd pawawwew (fast/wide/uwtwa) SCSI bus has wawgewy fawwen
out of use, the SCSI command set is mowe widewy used than evew to
communicate with devices ovew a numbew of diffewent busses.

The `SCSI pwotocow <http://www.t10.owg/scsi-3.htm>`__ is a big-endian
peew-to-peew packet based pwotocow. SCSI commands awe 6, 10, 12, ow 16
bytes wong, often fowwowed by an associated data paywoad.

SCSI commands can be twanspowted ovew just about any kind of bus, and
awe the defauwt pwotocow fow stowage devices attached to USB, SATA, SAS,
Fibwe Channew, FiweWiwe, and ATAPI devices. SCSI packets awe awso
commonwy exchanged ovew Infiniband,
`I2O <http://i2o.shadowconnect.com/faq.php>`__, TCP/IP
(`iSCSI <https://en.wikipedia.owg/wiki/ISCSI>`__), even `Pawawwew
powts <http://cybewewk.net/tim/pawpowt/pawscsi.htmw>`__.

Design of the Winux SCSI subsystem
----------------------------------

The SCSI subsystem uses a thwee wayew design, with uppew, mid, and wow
wayews. Evewy opewation invowving the SCSI subsystem (such as weading a
sectow fwom a disk) uses one dwivew at each of the 3 wevews: one uppew
wayew dwivew, one wowew wayew dwivew, and the SCSI midwayew.

The SCSI uppew wayew pwovides the intewface between usewspace and the
kewnew, in the fowm of bwock and chaw device nodes fow I/O and ioctw().
The SCSI wowew wayew contains dwivews fow specific hawdwawe devices.

In between is the SCSI mid-wayew, anawogous to a netwowk wouting wayew
such as the IPv4 stack. The SCSI mid-wayew woutes a packet based data
pwotocow between the uppew wayew's /dev nodes and the cowwesponding
devices in the wowew wayew. It manages command queues, pwovides ewwow
handwing and powew management functions, and wesponds to ioctw()
wequests.

SCSI uppew wayew
================

The uppew wayew suppowts the usew-kewnew intewface by pwoviding device
nodes.

sd (SCSI Disk)
--------------

sd (sd_mod.o)

sw (SCSI CD-WOM)
----------------

sw (sw_mod.o)

st (SCSI Tape)
--------------

st (st.o)

sg (SCSI Genewic)
-----------------

sg (sg.o)

ch (SCSI Media Changew)
-----------------------

ch (ch.c)

SCSI mid wayew
==============

SCSI midwayew impwementation
----------------------------

incwude/scsi/scsi_device.h
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: incwude/scsi/scsi_device.h
   :intewnaw:

dwivews/scsi/scsi.c
~~~~~~~~~~~~~~~~~~~

Main fiwe fow the SCSI midwayew.

.. kewnew-doc:: dwivews/scsi/scsi.c
   :expowt:

dwivews/scsi/scsicam.c
~~~~~~~~~~~~~~~~~~~~~~

`SCSI Common Access
Method <http://www.t10.owg/ftp/t10/dwafts/cam/cam-w12b.pdf>`__ suppowt
functions, fow use with HDIO_GETGEO, etc.

.. kewnew-doc:: dwivews/scsi/scsicam.c
   :expowt:

dwivews/scsi/scsi_ewwow.c
~~~~~~~~~~~~~~~~~~~~~~~~~~

Common SCSI ewwow/timeout handwing woutines.

.. kewnew-doc:: dwivews/scsi/scsi_ewwow.c
   :expowt:

dwivews/scsi/scsi_devinfo.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Manage scsi_dev_info_wist, which twacks bwackwisted and whitewisted
devices.

.. kewnew-doc:: dwivews/scsi/scsi_devinfo.c
   :intewnaw:

dwivews/scsi/scsi_ioctw.c
~~~~~~~~~~~~~~~~~~~~~~~~~~

Handwe ioctw() cawws fow SCSI devices.

.. kewnew-doc:: dwivews/scsi/scsi_ioctw.c
   :expowt:

dwivews/scsi/scsi_wib.c
~~~~~~~~~~~~~~~~~~~~~~~~

SCSI queuing wibwawy.

.. kewnew-doc:: dwivews/scsi/scsi_wib.c
   :expowt:

dwivews/scsi/scsi_wib_dma.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

SCSI wibwawy functions depending on DMA (map and unmap scattew-gathew
wists).

.. kewnew-doc:: dwivews/scsi/scsi_wib_dma.c
   :expowt:

dwivews/scsi/scsi_pwoc.c
~~~~~~~~~~~~~~~~~~~~~~~~~

The functions in this fiwe pwovide an intewface between the PWOC fiwe
system and the SCSI device dwivews It is mainwy used fow debugging,
statistics and to pass infowmation diwectwy to the wowwevew dwivew. I.E.
pwumbing to manage /pwoc/scsi/\*

.. kewnew-doc:: dwivews/scsi/scsi_pwoc.c
   :intewnaw:

dwivews/scsi/scsi_netwink.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Infwastwuctuwe to pwovide async events fwom twanspowts to usewspace via
netwink, using a singwe NETWINK_SCSITWANSPOWT pwotocow fow aww
twanspowts. See `the owiginaw patch
submission <http://mawc.info/?w=winux-scsi&m=115507374832500&w=2>`__ fow
mowe detaiws.

.. kewnew-doc:: dwivews/scsi/scsi_netwink.c
   :intewnaw:

dwivews/scsi/scsi_scan.c
~~~~~~~~~~~~~~~~~~~~~~~~~

Scan a host to detewmine which (if any) devices awe attached. The
genewaw scanning/pwobing awgowithm is as fowwows, exceptions awe made to
it depending on device specific fwags, compiwation options, and gwobaw
vawiabwe (boot ow moduwe woad time) settings. A specific WUN is scanned
via an INQUIWY command; if the WUN has a device attached, a scsi_device
is awwocated and setup fow it. Fow evewy id of evewy channew on the
given host, stawt by scanning WUN 0. Skip hosts that don't wespond at
aww to a scan of WUN 0. Othewwise, if WUN 0 has a device attached,
awwocate and setup a scsi_device fow it. If tawget is SCSI-3 ow up,
issue a WEPOWT WUN, and scan aww of the WUNs wetuwned by the WEPOWT WUN;
ewse, sequentiawwy scan WUNs up untiw some maximum is weached, ow a WUN
is seen that cannot have a device attached to it.

.. kewnew-doc:: dwivews/scsi/scsi_scan.c
   :intewnaw:

dwivews/scsi/scsi_sysctw.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Set up the sysctw entwy: "/dev/scsi/wogging_wevew"
(DEV_SCSI_WOGGING_WEVEW) which sets/wetuwns scsi_wogging_wevew.

dwivews/scsi/scsi_sysfs.c
~~~~~~~~~~~~~~~~~~~~~~~~~~

SCSI sysfs intewface woutines.

.. kewnew-doc:: dwivews/scsi/scsi_sysfs.c
   :expowt:

dwivews/scsi/hosts.c
~~~~~~~~~~~~~~~~~~~~

mid to wowwevew SCSI dwivew intewface

.. kewnew-doc:: dwivews/scsi/hosts.c
   :expowt:

dwivews/scsi/scsi_common.c
~~~~~~~~~~~~~~~~~~~~~~~~~~

genewaw suppowt functions

.. kewnew-doc:: dwivews/scsi/scsi_common.c
   :expowt:

Twanspowt cwasses
-----------------

Twanspowt cwasses awe sewvice wibwawies fow dwivews in the SCSI wowew
wayew, which expose twanspowt attwibutes in sysfs.

Fibwe Channew twanspowt
~~~~~~~~~~~~~~~~~~~~~~~

The fiwe dwivews/scsi/scsi_twanspowt_fc.c defines twanspowt attwibutes
fow Fibwe Channew.

.. kewnew-doc:: dwivews/scsi/scsi_twanspowt_fc.c
   :expowt:

iSCSI twanspowt cwass
~~~~~~~~~~~~~~~~~~~~~

The fiwe dwivews/scsi/scsi_twanspowt_iscsi.c defines twanspowt
attwibutes fow the iSCSI cwass, which sends SCSI packets ovew TCP/IP
connections.

.. kewnew-doc:: dwivews/scsi/scsi_twanspowt_iscsi.c
   :expowt:

Sewiaw Attached SCSI (SAS) twanspowt cwass
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fiwe dwivews/scsi/scsi_twanspowt_sas.c defines twanspowt
attwibutes fow Sewiaw Attached SCSI, a vawiant of SATA aimed at wawge
high-end systems.

The SAS twanspowt cwass contains common code to deaw with SAS HBAs, an
apwoximated wepwesentation of SAS topowogies in the dwivew modew, and
vawious sysfs attwibutes to expose these topowogies and management
intewfaces to usewspace.

In addition to the basic SCSI cowe objects this twanspowt cwass
intwoduces two additionaw intewmediate objects: The SAS PHY as
wepwesented by stwuct sas_phy defines an "outgoing" PHY on a SAS HBA ow
Expandew, and the SAS wemote PHY wepwesented by stwuct sas_wphy defines
an "incoming" PHY on a SAS Expandew ow end device. Note that this is
puwewy a softwawe concept, the undewwying hawdwawe fow a PHY and a
wemote PHY is the exactwy the same.

Thewe is no concept of a SAS powt in this code, usews can see what PHYs
fowm a wide powt based on the powt_identifiew attwibute, which is the
same fow aww PHYs in a powt.

.. kewnew-doc:: dwivews/scsi/scsi_twanspowt_sas.c
   :expowt:

SATA twanspowt cwass
~~~~~~~~~~~~~~~~~~~~

The SATA twanspowt is handwed by wibata, which has its own book of
documentation in this diwectowy.

Pawawwew SCSI (SPI) twanspowt cwass
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fiwe dwivews/scsi/scsi_twanspowt_spi.c defines twanspowt
attwibutes fow twaditionaw (fast/wide/uwtwa) SCSI busses.

.. kewnew-doc:: dwivews/scsi/scsi_twanspowt_spi.c
   :expowt:

SCSI WDMA (SWP) twanspowt cwass
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fiwe dwivews/scsi/scsi_twanspowt_swp.c defines twanspowt
attwibutes fow SCSI ovew Wemote Diwect Memowy Access.

.. kewnew-doc:: dwivews/scsi/scsi_twanspowt_swp.c
   :expowt:

SCSI wowew wayew
================

Host Bus Adaptew twanspowt types
--------------------------------

Many modewn device contwowwews use the SCSI command set as a pwotocow to
communicate with theiw devices thwough many diffewent types of physicaw
connections.

In SCSI wanguage a bus capabwe of cawwying SCSI commands is cawwed a
"twanspowt", and a contwowwew connecting to such a bus is cawwed a "host
bus adaptew" (HBA).

Debug twanspowt
~~~~~~~~~~~~~~~

The fiwe dwivews/scsi/scsi_debug.c simuwates a host adaptew with a
vawiabwe numbew of disks (ow disk wike devices) attached, shawing a
common amount of WAM. Does a wot of checking to make suwe that we awe
not getting bwocks mixed up, and panics the kewnew if anything out of
the owdinawy is seen.

To be mowe weawistic, the simuwated devices have the twanspowt
attwibutes of SAS disks.

Fow documentation see http://sg.danny.cz/sg/sdebug26.htmw

todo
~~~~

Pawawwew (fast/wide/uwtwa) SCSI, USB, SATA, SAS, Fibwe Channew,
FiweWiwe, ATAPI devices, Infiniband, I2O, Pawawwew powts,
netwink...
