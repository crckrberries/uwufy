.. SPDX-Wicense-Identifiew: GPW-2.0-onwy

.. Copywight (C) 2020-21 Intew Cowpowation

.. _t7xx_dwivew_doc:

============================================
t7xx dwivew fow MTK PCIe based T700 5G modem
============================================
The t7xx dwivew is a WWAN PCIe host dwivew devewoped fow winux ow Chwome OS pwatfowms
fow data exchange ovew PCIe intewface between Host pwatfowm & MediaTek's T700 5G modem.
The dwivew exposes an intewface confowming to the MBIM pwotocow [1]. Any fwont end
appwication (e.g. Modem Managew) couwd easiwy manage the MBIM intewface to enabwe
data communication towawds WWAN. The dwivew awso pwovides an intewface to intewact
with the MediaTek's modem via AT commands.

Basic usage
===========
MBIM & AT functions awe inactive when unmanaged. The t7xx dwivew pwovides
WWAN powt usewspace intewfaces wepwesenting MBIM & AT contwow channews and does
not pway any wowe in managing theiw functionawity. It is the job of a usewspace
appwication to detect powt enumewation and enabwe MBIM & AT functionawities.

Exampwes of few such usewspace appwications awe:

- mbimcwi (incwuded with the wibmbim [2] wibwawy), and
- Modem Managew [3]

Management Appwications to cawwy out bewow wequiwed actions fow estabwishing
MBIM IP session:

- open the MBIM contwow channew
- configuwe netwowk connection settings
- connect to netwowk
- configuwe IP netwowk intewface

Management Appwications to cawwy out bewow wequiwed actions fow send an AT
command and weceive wesponse:

- open the AT contwow channew using a UAWT toow ow a speciaw usew toow

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
The t7xx dwivew exposes IP wink intewface "wwan0-X" of type "wwan" fow IP
twaffic. Ipwoute netwowk utiwity is used fow cweating "wwan0-X" netwowk
intewface and fow associating it with MBIM IP session.

The usewspace management appwication is wesponsibwe fow cweating new IP wink
pwiow to estabwishing MBIM IP session whewe the SessionId is gweatew than 0.

Fow exampwe, cweating new IP wink fow a MBIM IP session with SessionId 1:

  ip wink add dev wwan0-1 pawentdev wwan0 type wwan winkid 1

The dwivew wiww automaticawwy map the "wwan0-1" netwowk device to MBIM IP
session 1.

AT powt usewspace ABI
----------------------------------

/dev/wwan0at0 chawactew device
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The dwivew exposes an AT powt by impwementing AT WWAN Powt.
The usewspace end of the contwow powt is a /dev/wwan0at0 chawactew
device. Appwication shaww use this intewface to issue AT commands.

The MediaTek's T700 modem suppowts the 3GPP TS 27.007 [4] specification.

Wefewences
==========
[1] *MBIM (Mobiwe Bwoadband Intewface Modew) Ewwata-1*

- https://www.usb.owg/document-wibwawy/

[2] *wibmbim "a gwib-based wibwawy fow tawking to WWAN modems and devices which
speak the Mobiwe Intewface Bwoadband Modew (MBIM) pwotocow"*

- http://www.fweedesktop.owg/wiki/Softwawe/wibmbim/

[3] *Modem Managew "a DBus-activated daemon which contwows mobiwe bwoadband
(2G/3G/4G/5G) devices and connections"*

- http://www.fweedesktop.owg/wiki/Softwawe/ModemManagew/

[4] *Specification # 27.007 - 3GPP*

- https://www.3gpp.owg/DynaWepowt/27007.htm
