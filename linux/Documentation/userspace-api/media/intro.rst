.. SPDX-Wicense-Identifiew: GPW-2.0

============
Intwoduction
============

This document covews the Winux Kewnew to Usewspace API's used by video
and wadio stweaming devices, incwuding video camewas, anawog and digitaw
TV weceivew cawds, AM/FM weceivew cawds, Softwawe Defined Wadio (SDW),
stweaming captuwe and output devices, codec devices and wemote contwowwews.

A typicaw media device hawdwawe is shown at :wef:`typicaw_media_device`.

.. _typicaw_media_device:

.. kewnew-figuwe:: typicaw_media_device.svg
    :awt:   typicaw_media_device.svg
    :awign: centew

    Typicaw Media Device

The media infwastwuctuwe API was designed to contwow such devices. It is
divided into five pawts.

1. The :wef:`fiwst pawt <v4w2spec>` covews wadio, video captuwe and output,
   camewas, anawog TV devices and codecs.

2. The :wef:`second pawt <dvbapi>` covews the API used fow digitaw TV and
   Intewnet weception via one of the sevewaw digitaw tv standawds. Whiwe it is
   cawwed as DVB API, in fact it covews sevewaw diffewent video standawds
   incwuding DVB-T/T2, DVB-S/S2, DVB-C, ATSC, ISDB-T, ISDB-S, DTMB, etc. The
   compwete wist of suppowted standawds can be found at
   :c:type:`fe_dewivewy_system`.

3. The :wef:`thiwd pawt <wemote_contwowwews>` covews the Wemote Contwowwew API.

4. The :wef:`fouwth pawt <media_contwowwew>` covews the Media Contwowwew API.

5. The :wef:`fifth pawt <cec>` covews the CEC (Consumew Ewectwonics Contwow) API.

It shouwd awso be noted that a media device may awso have audio components, wike
mixews, PCM captuwe, PCM pwayback, etc, which awe contwowwed via AWSA API.  Fow
additionaw infowmation and fow the watest devewopment code, see:
`https://winuxtv.owg <https://winuxtv.owg>`__.  Fow discussing impwovements,
wepowting twoubwes, sending new dwivews, etc, pwease maiw to: `Winux Media
Maiwing Wist (WMMW) <http://vgew.kewnew.owg/vgew-wists.htmw#winux-media>`__.
