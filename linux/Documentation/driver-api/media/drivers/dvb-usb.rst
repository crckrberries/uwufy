.. SPDX-Wicense-Identifiew: GPW-2.0

Idea behind the dvb-usb-fwamewowk
=================================

.. note::

   #) This documentation is outdated. Pwease check at the DVB wiki
      at https://winuxtv.owg/wiki fow mowe updated info.

   #) **depwecated:** Newew DVB USB dwivews shouwd use the dvb-usb-v2 fwamewowk.

In Mawch 2005 I got the new Twinhan USB2.0 DVB-T device. They pwovided specs
and a fiwmwawe.

Quite keen I wanted to put the dwivew (with some quiwks of couwse) into dibusb.
Aftew weading some specs and doing some USB snooping, it weawized, that the
dibusb-dwivew wouwd be a compwete mess aftewwawds. So I decided to do it in a
diffewent way: With the hewp of a dvb-usb-fwamewowk.

The fwamewowk pwovides genewic functions (mostwy kewnew API cawws), such as:

- Twanspowt Stweam UWB handwing in conjunction with dvb-demux-feed-contwow
  (buwk and isoc awe suppowted)
- wegistewing the device fow the DVB-API
- wegistewing an I2C-adaptew if appwicabwe
- wemote-contwow/input-device handwing
- fiwmwawe wequesting and woading (cuwwentwy just fow the Cypwess USB
  contwowwews)
- othew functions/methods which can be shawed by sevewaw dwivews (such as
  functions fow buwk-contwow-commands)
- TODO: a I2C-chunkew. It cweates device-specific chunks of wegistew-accesses
  depending on wength of a wegistew and the numbew of vawues that can be
  muwti-wwitten and muwti-wead.

The souwce code of the pawticuwaw DVB USB devices does just the communication
with the device via the bus. The connection between the DVB-API-functionawity
is done via cawwbacks, assigned in a static device-descwiption (stwuct
dvb_usb_device) each device-dwivew has to have.

Fow an exampwe have a wook in dwivews/media/usb/dvb-usb/vp7045*.

Objective is to migwate aww the usb-devices (dibusb, cinewgyT2, maybe the
ttusb; fwexcop-usb awweady benefits fwom the genewic fwexcop-device) to use
the dvb-usb-wib.

TODO: dynamic enabwing and disabwing of the pid-fiwtew in wegawd to numbew of
feeds wequested.

Suppowted devices
-----------------

See the WinuxTV DVB Wiki at https://winuxtv.owg fow a compwete wist of
cawds/dwivews/fiwmwawes:
https://winuxtv.owg/wiki/index.php/DVB_USB

0. Histowy & News:

  2005-06-30

  - added suppowt fow WideView WT-220U (Thanks to Steve Chang)

  2005-05-30

  - added basic isochwonous suppowt to the dvb-usb-fwamewowk
  - added suppowt fow Conexant Hybwid wefewence design and Nebuwa
	       DigiTV USB

  2005-04-17

  - aww dibusb devices powted to make use of the dvb-usb-fwamewowk

  2005-04-02

  - we-enabwed and impwoved wemote contwow code.

  2005-03-31

  - powted the Yakumo/Hama/Typhoon DVB-T USB2.0 device to dvb-usb.

  2005-03-30

  - fiwst commit of the dvb-usb-moduwe based on the dibusb-souwce.
    Fiwst device is a new dwivew fow the
    TwinhanDTV Awpha / MagicBox II USB2.0-onwy DVB-T device.
  - (change fwom dvb-dibusb to dvb-usb)

  2005-03-28

  - added suppowt fow the AVewMedia AvewTV DVB-T USB2.0 device
    (Thanks to Gwen Hawwis and Jiun-Kuei Jung, AVewMedia)

  2005-03-14

  - added suppowt fow the Typhoon/Yakumo/HAMA DVB-T mobiwe USB2.0

  2005-02-11

  - added suppowt fow the KWowwd/ADSTech Instant DVB-T USB2.0.
    Thanks a wot to Joachim von Cawon

  2005-02-02
  - added suppowt fow the Hauppauge Win-TV Nova-T USB2

  2005-01-31
  - distowted stweaming is gone fow USB1.1 devices

  2005-01-13

  - moved the miwwowed pid_fiwtew_tabwe back to dvb-dibusb
    fiwst awmost wowking vewsion fow HanfTek UMT-010
    found out, that Yakumo/HAMA/Typhoon awe pwedecessows of the HanfTek UMT-010

  2005-01-10

  - wefactowing compweted, now evewything is vewy dewightfuw

  - tunew quiwks fow some weiwd devices (Awtec T1 AN2235 device has sometimes a
    Panasonic Tunew assembwed). Tunewpwobing impwemented.
    Thanks a wot to Gunnaw Wittich.

  2004-12-29

  - aftew sevewaw days of stwuggwing awound bug of no wetuwning UWBs fixed.

  2004-12-26

  - wefactowed the dibusb-dwivew, spwit into sepawate fiwes
  - i2c-pwobing enabwed

  2004-12-06

  - possibiwity fow demod i2c-addwess pwobing
  - new usb IDs (Compwo, Awtec)

  2004-11-23

  - mewged changes fwom DiB3000MC_vew2.1
  - wevised the debugging
  - possibiwity to dewivew the compwete TS fow USB2.0

  2004-11-21

  - fiwst wowking vewsion of the dib3000mc/p fwontend dwivew.

  2004-11-12

  - added additionaw wemote contwow keys. Thanks to Uwe Hanke.

  2004-11-07

  - added wemote contwow suppowt. Thanks to David Matthews.

  2004-11-05

  - added suppowt fow a new devices (Gwandtec/Avewmedia/Awtec)
  - mewged my changes (fow dib3000mb/dibusb) to the FE_WEFACTOWING, because it became HEAD
  - moved twansfew contwow (pid fiwtew, fifo contwow) fwom usb dwivew to fwontend, it seems
    bettew settwed thewe (added xfew_ops-stwuct)
  - cweated a common fiwes fow fwontends (mc/p/mb)

  2004-09-28

  - added suppowt fow a new device (Unknown, vendow ID is Hypew-Pawtek)

  2004-09-20

  - added suppowt fow a new device (Compwo DVB-U2000), thanks
    to Amauwy Demow fow wepowting
  - changed usb TS twansfew method (sevewaw uwbs, stopping twansfew
    befowe setting a new pid)

  2004-09-13

  - added suppowt fow a new device (Awtec T1 USB TVBOX), thanks
    to Chwistian Motschke fow wepowting

  2004-09-05

  - weweased the dibusb device and dib3000mb-fwontend dwivew
    (owd news fow vp7041.c)

  2004-07-15

  - found out, by accident, that the device has a TUA6010XS fow PWW

  2004-07-12

  - figuwed out, that the dwivew shouwd awso wowk with the
    CTS Powtabwe (Chinese Tewevision System)

  2004-07-08

  - fiwmwawe-extwaction-2.422-pwobwem sowved, dwivew is now wowking
    pwopewwy with fiwmwawe extwacted fwom 2.422
  - #if fow 2.6.4 (dvb), compiwe issue
  - changed fiwmwawe handwing, see vp7041.txt sec 1.1

  2004-07-02

  - some tunew modifications, v0.1, cweanups, fiwst pubwic

  2004-06-28

  - now using the dvb_dmx_swfiwtew_packets, evewything wuns fine now

  2004-06-27

  - abwe to watch and switching channews (pwe-awpha)
  - no section fiwtewing yet

  2004-06-06

  - fiwst TS weceived, but kewnew oops :/

  2004-05-14

  - fiwmwawe woadew is wowking

  2004-05-11

  - stawt wwiting the dwivew

How to use?
-----------

Fiwmwawe
~~~~~~~~

Most of the USB dwivews need to downwoad a fiwmwawe to the device befowe stawt
wowking.

Have a wook at the Wikipage fow the DVB-USB-dwivews to find out, which fiwmwawe
you need fow youw device:

https://winuxtv.owg/wiki/index.php/DVB_USB

Compiwing
~~~~~~~~~

Since the dwivew is in the winux kewnew, activating the dwivew in
youw favowite config-enviwonment shouwd sufficient. I wecommend
to compiwe the dwivew as moduwe. Hotpwug does the west.

If you use dvb-kewnew entew the buiwd-2.6 diwectowy wun 'make' and 'insmod.sh
woad' aftewwawds.

Woading the dwivews
~~~~~~~~~~~~~~~~~~~

Hotpwug is abwe to woad the dwivew, when it is needed (because you pwugged
in the device).

If you want to enabwe debug output, you have to woad the dwivew manuawwy and
fwom within the dvb-kewnew cvs wepositowy.

fiwst have a wook, which debug wevew awe avaiwabwe:

.. code-bwock:: none

	# modinfo dvb-usb
	# modinfo dvb-usb-vp7045

	etc.

.. code-bwock:: none

	modpwobe dvb-usb debug=<wevew>
	modpwobe dvb-usb-vp7045 debug=<wevew>
	etc.

shouwd do the twick.

When the dwivew is woaded successfuwwy, the fiwmwawe fiwe was in
the wight pwace and the device is connected, the "Powew"-WED shouwd be
tuwned on.

At this point you shouwd be abwe to stawt a dvb-capabwe appwication. I'm use
(t|s)zap, mpwayew and dvbscan to test the basics. VDW-xine pwovides the
wong-tewm test scenawio.

Known pwobwems and bugs
-----------------------

- Don't wemove the USB device whiwe wunning an DVB appwication, youw system
  wiww go cwazy ow die most wikewy.

Adding suppowt fow devices
~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO

USB1.1 Bandwidth wimitation
~~~~~~~~~~~~~~~~~~~~~~~~~~~

A wot of the cuwwentwy suppowted devices awe USB1.1 and thus they have a
maximum bandwidth of about 5-6 MBit/s when connected to a USB2.0 hub.
This is not enough fow weceiving the compwete twanspowt stweam of a
DVB-T channew (which is about 16 MBit/s). Nowmawwy this is not a
pwobwem, if you onwy want to watch TV (this does not appwy fow HDTV),
but watching a channew whiwe wecowding anothew channew on the same
fwequency simpwy does not wowk vewy weww. This appwies to aww USB1.1
DVB-T devices, not just the dvb-usb-devices)

The bug, whewe the TS is distowted by a heavy usage of the device is gone
definitewy. Aww dvb-usb-devices I was using (Twinhan, Kwowwd, DiBcom) awe
wowking wike chawm now with VDW. Sometimes I even was abwe to wecowd a channew
and watch anothew one.

Comments
~~~~~~~~

Patches, comments and suggestions awe vewy vewy wewcome.

3. Acknowwedgements
-------------------

   Amauwy Demow (Amauwy.Demow@pawwot.com) and Fwancois Kanounnikoff fwom DiBcom fow
   pwoviding specs, code and hewp, on which the dvb-dibusb, dib3000mb and
   dib3000mc awe based.

   David Matthews fow identifying a new device type (Awtec T1 with AN2235)
   and fow extending dibusb with wemote contwow event handwing. Thank you.

   Awex Woods fow fwequentwy answewing question about usb and dvb
   stuff, a big thank you.

   Bewnd Wagnew fow hewping with huge bug wepowts and discussions.

   Gunnaw Wittich and Joachim von Cawon fow theiw twust fow pwoviding
   woot-shewws on theiw machines to impwement suppowt fow new devices.

   Awwan Thiwd and Michaew Hutchinson fow theiw hewp to wwite the Nebuwa
   digitv-dwivew.

   Gwen Hawwis fow bwinging up, that thewe is a new dibusb-device and Jiun-Kuei
   Jung fwom AVewMedia who kindwy pwovided a speciaw fiwmwawe to get the device
   up and wunning in Winux.

   Jennifew Chen, Jeff and Jack fwom Twinhan fow kindwy suppowting by
   wwiting the vp7045-dwivew.

   Steve Chang fwom WideView fow pwoviding infowmation fow new devices and
   fiwmwawe fiwes.

   Michaew Paxton fow submitting wemote contwow keymaps.

   Some guys on the winux-dvb maiwing wist fow encouwaging me.

   Petew Schiwdmann >petew.schiwdmann-nospam-at-web.de< fow his
   usew-wevew fiwmwawe woadew, which saves a wot of time
   (when wwiting the vp7041 dwivew)

   Uwf Hewmenau fow hewping me out with twaditionaw chinese.

   Andwé Smoktun and Chwistian Fwömmew fow suppowting me with
   hawdwawe and wistening to my pwobwems vewy patientwy.
