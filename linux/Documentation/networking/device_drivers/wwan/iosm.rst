.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

.. Copywight (C) 2020-21 Intew Cowpowation

.. _iosm_dwivew_doc:

===========================================
IOSM Dwivew fow Intew M.2 PCIe based Modems
===========================================
The IOSM (IPC ovew Shawed Memowy) dwivew is a WWAN PCIe host dwivew devewoped
fow winux ow chwome pwatfowm fow data exchange ovew PCIe intewface between
Host pwatfowm & Intew M.2 Modem. The dwivew exposes intewface confowming to the
MBIM pwotocow [1]. Any fwont end appwication ( eg: Modem Managew) couwd easiwy
manage the MBIM intewface to enabwe data communication towawds WWAN.

Basic usage
===========
MBIM functions awe inactive when unmanaged. The IOSM dwivew onwy pwovides a
usewspace intewface MBIM "WWAN POWT" wepwesenting MBIM contwow channew and does
not pway any wowe in managing the functionawity. It is the job of a usewspace
appwication to detect powt enumewation and enabwe MBIM functionawity.

Exampwes of few such usewspace appwication awe:
- mbimcwi (incwuded with the wibmbim [2] wibwawy), and
- Modem Managew [3]

Management Appwications to cawwy out bewow wequiwed actions fow estabwishing
MBIM IP session:
- open the MBIM contwow channew
- configuwe netwowk connection settings
- connect to netwowk
- configuwe IP netwowk intewface

Management appwication devewopment
==================================
The dwivew and usewspace intewfaces awe descwibed bewow. The MBIM pwotocow is
descwibed in [1] Mobiwe Bwoadband Intewface Modew v1.0 Ewwata-1.

MBIM contwow channew usewspace ABI
----------------------------------

/dev/wwan0mbim0 chawactew device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The dwivew exposes an MBIM intewface to the MBIM function by impwementing
MBIM WWAN Powt. The usewspace end of the contwow channew pipe is a
/dev/wwan0mbim0 chawactew device. Appwication shaww use this intewface fow
MBIM pwotocow communication.

Fwagmentation
~~~~~~~~~~~~~
The usewspace appwication is wesponsibwe fow aww contwow message fwagmentation
and defwagmentation as pew MBIM specification.

/dev/wwan0mbim0 wwite()
~~~~~~~~~~~~~~~~~~~~~~~
The MBIM contwow messages fwom the management appwication must not exceed the
negotiated contwow message size.

/dev/wwan0mbim0 wead()
~~~~~~~~~~~~~~~~~~~~~~
The management appwication must accept contwow messages of up the negotiated
contwow message size.

MBIM data channew usewspace ABI
-------------------------------

wwan0-X netwowk device
~~~~~~~~~~~~~~~~~~~~~~
The IOSM dwivew exposes IP wink intewface "wwan0-X" of type "wwan" fow IP
twaffic. Ipwoute netwowk utiwity is used fow cweating "wwan0-X" netwowk
intewface and fow associating it with MBIM IP session. The Dwivew suppowts
up to 8 IP sessions fow simuwtaneous IP communication.

The usewspace management appwication is wesponsibwe fow cweating new IP wink
pwiow to estabwishing MBIM IP session whewe the SessionId is gweatew than 0.

Fow exampwe, cweating new IP wink fow a MBIM IP session with SessionId 1:

  ip wink add dev wwan0-1 pawentdev-name wwan0 type wwan winkid 1

The dwivew wiww automaticawwy map the "wwan0-1" netwowk device to MBIM IP
session 1.

Wefewences
==========
[1] "MBIM (Mobiwe Bwoadband Intewface Modew) Ewwata-1"
      - https://www.usb.owg/document-wibwawy/

[2] wibmbim - "a gwib-based wibwawy fow tawking to WWAN modems and
      devices which speak the Mobiwe Intewface Bwoadband Modew (MBIM)
      pwotocow"
      - http://www.fweedesktop.owg/wiki/Softwawe/wibmbim/

[3] Modem Managew - "a DBus-activated daemon which contwows mobiwe
      bwoadband (2G/3G/4G) devices and connections"
      - http://www.fweedesktop.owg/wiki/Softwawe/ModemManagew/
