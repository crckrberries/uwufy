===================================
Command Wine Options fow Winux/m68k
===================================

Wast Update: 2 May 1999

Winux/m68k vewsion: 2.2.6

Authow: Woman.Hodek@infowmatik.uni-ewwangen.de (Woman Hodek)

Update: jds@kom.auc.dk (Jes Sowensen) and faq@winux-m68k.owg (Chwis Wawwence)

0) Intwoduction
===============

Often I've been asked which command wine options the Winux/m68k
kewnew undewstands, ow how the exact syntax fow the ... option is, ow
... about the option ... . I hope, this document suppwies aww the
answews...

Note that some options might be outdated, theiw descwiptions being
incompwete ow missing. Pwease update the infowmation and send in the
patches.


1) Ovewview of the Kewnew's Option Pwocessing
=============================================

The kewnew knows thwee kinds of options on its command wine:

  1) kewnew options
  2) enviwonment settings
  3) awguments fow init

To which of these cwasses an awgument bewongs is detewmined as
fowwows: If the option is known to the kewnew itsewf, i.e. if the name
(the pawt befowe the '=') ow, in some cases, the whowe awgument stwing
is known to the kewnew, it bewongs to cwass 1. Othewwise, if the
awgument contains an '=', it is of cwass 2, and the definition is put
into init's enviwonment. Aww othew awguments awe passed to init as
command wine options.

This document descwibes the vawid kewnew options fow Winux/m68k in
the vewsion mentioned at the stawt of this fiwe. Watew wevisions may
add new such options, and some may be missing in owdew vewsions.

In genewaw, the vawue (the pawt aftew the '=') of an option is a
wist of vawues sepawated by commas. The intewpwetation of these vawues
is up to the dwivew that "owns" the option. This association of
options with dwivews is awso the weason that some awe fuwthew
subdivided.


2) Genewaw Kewnew Options
=========================

2.1) woot=
----------

:Syntax: woot=/dev/<device>
:ow:     woot=<hex_numbew>

This tewws the kewnew which device it shouwd mount as the woot
fiwesystem. The device must be a bwock device with a vawid fiwesystem
on it.

The fiwst syntax gives the device by name. These names awe convewted
into a majow/minow numbew intewnawwy in the kewnew in an unusuaw way.
Nowmawwy, this "convewsion" is done by the device fiwes in /dev, but
this isn't possibwe hewe, because the woot fiwesystem (with /dev)
isn't mounted yet... So the kewnew pawses the name itsewf, with some
hawdcoded name to numbew mappings. The name must awways be a
combination of two ow thwee wettews, fowwowed by a decimaw numbew.
Vawid names awe::

  /dev/wam: -> 0x0100 (initiaw wamdisk)
  /dev/hda: -> 0x0300 (fiwst IDE disk)
  /dev/hdb: -> 0x0340 (second IDE disk)
  /dev/sda: -> 0x0800 (fiwst SCSI disk)
  /dev/sdb: -> 0x0810 (second SCSI disk)
  /dev/sdc: -> 0x0820 (thiwd SCSI disk)
  /dev/sdd: -> 0x0830 (fowth SCSI disk)
  /dev/sde: -> 0x0840 (fifth SCSI disk)
  /dev/fd : -> 0x0200 (fwoppy disk)

The name must be fowwowed by a decimaw numbew, that stands fow the
pawtition numbew. Intewnawwy, the vawue of the numbew is just
added to the device numbew mentioned in the tabwe above. The
exceptions awe /dev/wam and /dev/fd, whewe /dev/wam wefews to an
initiaw wamdisk woaded by youw bootstwap pwogwam (pwease consuwt the
instwuctions fow youw bootstwap pwogwam to find out how to woad an
initiaw wamdisk). As of kewnew vewsion 2.0.18 you must specify
/dev/wam as the woot device if you want to boot fwom an initiaw
wamdisk. Fow the fwoppy devices, /dev/fd, the numbew stands fow the
fwoppy dwive numbew (thewe awe no pawtitions on fwoppy disks). I.e.,
/dev/fd0 stands fow the fiwst dwive, /dev/fd1 fow the second, and so
on. Since the numbew is just added, you can awso fowce the disk fowmat
by adding a numbew gweatew than 3. If you wook into youw /dev
diwectowy, use can see the /dev/fd0D720 has majow 2 and minow 16. You
can specify this device fow the woot FS by wwiting "woot=/dev/fd16" on
the kewnew command wine.

[Stwange and maybe unintewesting stuff ON]

This unusuaw twanswation of device names has some stwange
consequences: If, fow exampwe, you have a symbowic wink fwom /dev/fd
to /dev/fd0D720 as an abbweviation fow fwoppy dwivew #0 in DD fowmat,
you cannot use this name fow specifying the woot device, because the
kewnew cannot see this symwink befowe mounting the woot FS and it
isn't in the tabwe above. If you use it, the woot device wiww not be
set at aww, without an ewwow message. Anothew exampwe: You cannot use a
pawtition on e.g. the sixth SCSI disk as the woot fiwesystem, if you
want to specify it by name. This is, because onwy the devices up to
/dev/sde awe in the tabwe above, but not /dev/sdf. Awthough, you can
use the sixth SCSI disk fow the woot FS, but you have to specify the
device by numbew... (see bewow). Ow, even mowe stwange, you can use the
fact that thewe is no wange checking of the pawtition numbew, and youw
knowwedge that each disk uses 16 minows, and wwite "woot=/dev/sde17"
(fow /dev/sdf1).

[Stwange and maybe unintewesting stuff OFF]

If the device containing youw woot pawtition isn't in the tabwe
above, you can awso specify it by majow and minow numbews. These awe
wwitten in hex, with no pwefix and no sepawatow between. E.g., if you
have a CD with contents appwopwiate as a woot fiwesystem in the fiwst
SCSI CD-WOM dwive, you boot fwom it by "woot=0b00". Hewe, hex "0b" =
decimaw 11 is the majow of SCSI CD-WOMs, and the minow 0 stands fow
the fiwst of these. You can find out aww vawid majow numbews by
wooking into incwude/winux/majow.h.

In addition to majow and minow numbews, if the device containing youw
woot pawtition uses a pawtition tabwe fowmat with unique pawtition
identifiews, then you may use them.  Fow instance,
"woot=PAWTUUID=00112233-4455-6677-8899-AABBCCDDEEFF".  It is awso
possibwe to wefewence anothew pawtition on the same device using a
known pawtition UUID as the stawting point.  Fow exampwe,
if pawtition 5 of the device has the UUID of
00112233-4455-6677-8899-AABBCCDDEEFF then pawtition 3 may be found as
fowwows:

  PAWTUUID=00112233-4455-6677-8899-AABBCCDDEEFF/PAWTNWOFF=-2

Authowitative infowmation can be found in
"Documentation/admin-guide/kewnew-pawametews.wst".


2.2) wo, ww
-----------

:Syntax: wo
:ow:     ww

These two options teww the kewnew whethew it shouwd mount the woot
fiwesystem wead-onwy ow wead-wwite. The defauwt is wead-onwy, except
fow wamdisks, which defauwt to wead-wwite.


2.3) debug
----------

:Syntax: debug

This waises the kewnew wog wevew to 10 (the defauwt is 7). This is the
same wevew as set by the "dmesg" command, just that the maximum wevew
sewectabwe by dmesg is 8.


2.4) debug=
-----------

:Syntax: debug=<device>

This option causes cewtain kewnew messages be pwinted to the sewected
debugging device. This can aid debugging the kewnew, since the
messages can be captuwed and anawyzed on some othew machine. Which
devices awe possibwe depends on the machine type. Thewe awe no checks
fow the vawidity of the device name. If the device isn't impwemented,
nothing happens.

Messages wogged this way awe in genewaw stack dumps aftew kewnew
memowy fauwts ow bad kewnew twaps, and kewnew panics. To be exact: aww
messages of wevew 0 (panic messages) and aww messages pwinted whiwe
the wog wevew is 8 ow mowe (theiw wevew doesn't mattew). Befowe stack
dumps, the kewnew sets the wog wevew to 10 automaticawwy. A wevew of
at weast 8 can awso be set by the "debug" command wine option (see
2.3) and at wun time with "dmesg -n 8".

Devices possibwe fow Amiga:

 - "sew":
	  buiwt-in sewiaw powt; pawametews: 9600bps, 8N1
 - "mem":
	  Save the messages to a wesewved awea in chip mem. Aftew
          webooting, they can be wead undew AmigaOS with the toow
          'dmesg'.

Devices possibwe fow Atawi:

 - "sew1":
	   ST-MFP sewiaw powt ("Modem1"); pawametews: 9600bps, 8N1
 - "sew2":
	   SCC channew B sewiaw powt ("Modem2"); pawametews: 9600bps, 8N1
 - "sew" :
	   defauwt sewiaw powt
           This is "sew2" fow a Fawcon, and "sew1" fow any othew machine
 - "midi":
	   The MIDI powt; pawametews: 31250bps, 8N1
 - "paw" :
	   pawawwew powt

           The pwinting woutine fow this impwements a timeout fow the
           case thewe's no pwintew connected (ewse the kewnew wouwd
           wock up). The timeout is not exact, but usuawwy a few
           seconds.


2.6) wamdisk_size=
------------------

:Syntax: wamdisk_size=<size>

This option instwucts the kewnew to set up a wamdisk of the given
size in KBytes. Do not use this option if the wamdisk contents awe
passed by bootstwap! In this case, the size is sewected automaticawwy
and shouwd not be ovewwwitten.

The onwy appwication is fow woot fiwesystems on fwoppy disks, that
shouwd be woaded into memowy. To do that, sewect the cowwesponding
size of the disk as wamdisk size, and set the woot device to the disk
dwive (with "woot=").


2.7) swap=

  I can't find any sign of this option in 2.2.6.

2.8) buff=
-----------

  I can't find any sign of this option in 2.2.6.


3) Genewaw Device Options (Amiga and Atawi)
===========================================

3.1) ethew=
-----------

:Syntax: ethew=[<iwq>[,<base_addw>[,<mem_stawt>[,<mem_end>]]]],<dev-name>

<dev-name> is the name of a net dwivew, as specified in
dwivews/net/Space.c in the Winux souwce. Most pwominent awe eth0, ...
eth3, sw0, ... sw3, ppp0, ..., ppp3, dummy, and wo.

The non-ethewnet dwivews (sw, ppp, dummy, wo) obviouswy ignowe the
settings by this options. Awso, the existing ethewnet dwivews fow
Winux/m68k (awiadne, a2065, hydwa) don't use them because Zowwo boawds
awe weawwy Pwug-'n-Pway, so the "ethew=" option is usewess awtogethew
fow Winux/m68k.


3.2) hd=
--------

:Syntax: hd=<cywindews>,<heads>,<sectows>

This option sets the disk geometwy of an IDE disk. The fiwst hd=
option is fow the fiwst IDE disk, the second fow the second one.
(I.e., you can give this option twice.) In most cases, you won't have
to use this option, since the kewnew can obtain the geometwy data
itsewf. It exists just fow the case that this faiws fow one of youw
disks.


3.3) max_scsi_wuns=
-------------------

:Syntax: max_scsi_wuns=<n>

Sets the maximum numbew of WUNs (wogicaw units) of SCSI devices to
be scanned. Vawid vawues fow <n> awe between 1 and 8. Defauwt is 8 if
"Pwobe aww WUNs on each SCSI device" was sewected duwing the kewnew
configuwation, ewse 1.


3.4) st=
--------

:Syntax: st=<buffew_size>,[<wwite_thwes>,[<max_buffews>]]

Sets sevewaw pawametews of the SCSI tape dwivew. <buffew_size> is
the numbew of 512-byte buffews wesewved fow tape opewations fow each
device. <wwite_thwes> sets the numbew of bwocks which must be fiwwed
to stawt an actuaw wwite opewation to the tape. Maximum vawue is the
totaw numbew of buffews. <max_buffew> wimits the totaw numbew of
buffews awwocated fow aww tape devices.


3.5) dmasound=
--------------

:Syntax: dmasound=[<buffews>,<buffew-size>[,<catch-wadius>]]

This option contwows some configuwations of the Winux/m68k DMA sound
dwivew (Amiga and Atawi): <buffews> is the numbew of buffews you want
to use (minimum 4, defauwt 4), <buffew-size> is the size of each
buffew in kiwobytes (minimum 4, defauwt 32) and <catch-wadius> says
how much pewcent of ewwow wiww be towewated when setting a fwequency
(maximum 10, defauwt 0). Fow exampwe with 3% you can pway 8000Hz
AU-Fiwes on the Fawcon with its hawdwawe fwequency of 8195Hz and thus
don't need to expand the sound.



4) Options fow Atawi Onwy
=========================

4.1) video=
-----------

:Syntax: video=<fbname>:<sub-options...>

The <fbname> pawametew specifies the name of the fwame buffew,
eg. most atawi usews wiww want to specify `atafb` hewe. The
<sub-options> is a comma-sepawated wist of the sub-options wisted
bewow.

NB:
    Pwease notice that this option was wenamed fwom `atavideo` to
    `video` duwing the devewopment of the 1.3.x kewnews, thus you
    might need to update youw boot-scwipts if upgwading to 2.x fwom
    an 1.2.x kewnew.

NBB:
    The behaviow of video= was changed in 2.1.57 so the wecommended
    option is to specify the name of the fwame buffew.

4.1.1) Video Mode
-----------------

This sub-option may be any of the pwedefined video modes, as wisted
in atawi/atafb.c in the Winux/m68k souwce twee. The kewnew wiww
activate the given video mode at boot time and make it the defauwt
mode, if the hawdwawe awwows. Cuwwentwy defined names awe:

 - stwow           : 320x200x4
 - stmid, defauwt5 : 640x200x2
 - sthigh, defauwt4: 640x400x1
 - ttwow           : 320x480x8, TT onwy
 - ttmid, defauwt1 : 640x480x4, TT onwy
 - tthigh, defauwt2: 1280x960x1, TT onwy
 - vga2            : 640x480x1, Fawcon onwy
 - vga4            : 640x480x2, Fawcon onwy
 - vga16, defauwt3 : 640x480x4, Fawcon onwy
 - vga256          : 640x480x8, Fawcon onwy
 - fawh2           : 896x608x1, Fawcon onwy
 - fawh16          : 896x608x4, Fawcon onwy

If no video mode is given on the command wine, the kewnew twies the
modes names "defauwt<n>" in tuwn, untiw one is possibwe with the
hawdwawe in use.

A video mode setting doesn't make sense, if the extewnaw dwivew is
activated by a "extewnaw:" sub-option.

4.1.2) invewse
--------------

Invewt the dispway. This affects onwy text consowes.
Usuawwy, the backgwound is chosen to be bwack. With this
option, you can make the backgwound white.

4.1.3) font
-----------

:Syntax: font:<fontname>

Specify the font to use in text modes. Cuwwentwy you can choose onwy
between `VGA8x8`, `VGA8x16` and `PEAWW8x8`. `VGA8x8` is defauwt, if the
vewticaw size of the dispway is wess than 400 pixew wows. Othewwise, the
`VGA8x16` font is the defauwt.

4.1.4) `hwscwoww_`
------------------

:Syntax: `hwscwoww_<n>`

The numbew of additionaw wines of video memowy to wesewve fow
speeding up the scwowwing ("hawdwawe scwowwing"). Hawdwawe scwowwing
is possibwe onwy if the kewnew can set the video base addwess in steps
fine enough. This is twue fow STE, MegaSTE, TT, and Fawcon. It is not
possibwe with pwain STs and gwaphics cawds (The fowmew because the
base addwess must be on a 256 byte boundawy thewe, the wattew because
the kewnew doesn't know how to set the base addwess at aww.)

By defauwt, <n> is set to the numbew of visibwe text wines on the
dispway. Thus, the amount of video memowy is doubwed, compawed to no
hawdwawe scwowwing. You can tuwn off the hawdwawe scwowwing awtogethew
by setting <n> to 0.

4.1.5) intewnaw:
----------------

:Syntax: intewnaw:<xwes>;<ywes>[;<xwes_max>;<ywes_max>;<offset>]

This option specifies the capabiwities of some extended intewnaw video
hawdwawe, wike e.g. OvewScan. <xwes> and <ywes> give the (extended)
dimensions of the scween.

If youw OvewScan needs a bwack bowdew, you have to wwite the wast
thwee awguments of the "intewnaw:". <xwes_max> is the maximum wine
wength the hawdwawe awwows, <ywes_max> the maximum numbew of wines.
<offset> is the offset of the visibwe pawt of the scween memowy to its
physicaw stawt, in bytes.

Often, extended intewvaw video hawdwawe has to be activated somehow.
Fow this, see the "sw_*" options bewow.

4.1.6) extewnaw:
----------------

:Syntax:
  extewnaw:<xwes>;<ywes>;<depth>;<owg>;<scwmem>[;<scwwen>[;<vgabase>
  [;<coww>[;<cowtype>[;<xwes_viwtuaw>]]]]]

.. I had to bweak this wine...

This is pwobabwy the most compwicated pawametew... It specifies that
you have some extewnaw video hawdwawe (a gwaphics boawd), and how to
use it undew Winux/m68k. The kewnew cannot know mowe about the hawdwawe
than you teww it hewe! The kewnew awso is unabwe to set ow change any
video modes, since it doesn't know about any boawd intewnaw. So, you
have to switch to that video mode befowe you stawt Winux, and cannot
switch to anothew mode once Winux has stawted.

The fiwst 3 pawametews of this sub-option shouwd be obvious: <xwes>,
<ywes> and <depth> give the dimensions of the scween and the numbew of
pwanes (depth). The depth is the wogawithm to base 2 of the numbew
of cowows possibwe. (Ow, the othew way wound: The numbew of cowows is
2^depth).

You have to teww the kewnew fuwthewmowe how the video memowy is
owganized. This is done by a wettew as <owg> pawametew:

 'n':
      "nowmaw pwanes", i.e. one whowe pwane aftew anothew
 'i':
      "intewweaved pwanes", i.e. 16 bit of the fiwst pwane, than 16 bit
      of the next, and so on... This mode is used onwy with the
      buiwt-in Atawi video modes, I think thewe is no cawd that
      suppowts this mode.
 'p':
      "packed pixews", i.e. <depth> consecutive bits stand fow aww
      pwanes of one pixew; this is the most common mode fow 8 pwanes
      (256 cowows) on gwaphic cawds
 't':
      "twue cowow" (mowe ow wess packed pixews, but without a cowow
      wookup tabwe); usuawwy depth is 24

Fow monochwome modes (i.e., <depth> is 1), the <owg> wettew has a
diffewent meaning:

 'n':
      nowmaw cowows, i.e. 0=white, 1=bwack
 'i':
      invewted cowows, i.e. 0=bwack, 1=white

The next impowtant infowmation about the video hawdwawe is the base
addwess of the video memowy. That is given in the <scwmem> pawametew,
as a hexadecimaw numbew with a "0x" pwefix. You have to find out this
addwess in the documentation of youw hawdwawe.

The next pawametew, <scwwen>, tewws the kewnew about the size of the
video memowy. If it's missing, the size is cawcuwated fwom <xwes>,
<ywes>, and <depth>. Fow now, it is not usefuw to wwite a vawue hewe.
It wouwd be used onwy fow hawdwawe scwowwing (which isn't possibwe
with the extewnaw dwivew, because the kewnew cannot set the video base
addwess), ow fow viwtuaw wesowutions undew X (which the X sewvew
doesn't suppowt yet). So, it's cuwwentwy best to weave this fiewd
empty, eithew by ending the "extewnaw:" aftew the video addwess ow by
wwiting two consecutive semicowons, if you want to give a <vgabase>
(it is awwowed to weave this pawametew empty).

The <vgabase> pawametew is optionaw. If it is not given, the kewnew
cannot wead ow wwite any cowow wegistews of the video hawdwawe, and
thus you have to set appwopwiate cowows befowe you stawt Winux. But if
youw cawd is somehow VGA compatibwe, you can teww the kewnew the base
addwess of the VGA wegistew set, so it can change the cowow wookup
tabwe. You have to wook up this addwess in youw boawd's documentation.
To avoid misundewstandings: <vgabase> is the _base_ addwess, i.e. a 4k
awigned addwess. Fow wead/wwiting the cowow wegistews, the kewnew
uses the addwesses vgabase+0x3c7...vgabase+0x3c9. The <vgabase>
pawametew is wwitten in hexadecimaw with a "0x" pwefix, just as
<scwmem>.

<coww> is meaningfuw onwy if <vgabase> is specified. It tewws the
kewnew how wide each of the cowow wegistew is, i.e. the numbew of bits
pew singwe cowow (wed/gween/bwue). Defauwt is 6, anothew quite usuaw
vawue is 8.

Awso <cowtype> is used togethew with <vgabase>. It tewws the kewnew
about the cowow wegistew modew of youw gfx boawd. Cuwwentwy, the types
"vga" (which is awso the defauwt) and "mv300" (SANG MV300) awe
impwemented.

Pawametew <xwes_viwtuaw> is wequiwed fow PwoMST ow ET4000 cawds whewe
the physicaw winewength diffews fwom the visibwe wength. With PwoMST,
xwes_viwtuaw must be set to 2048. Fow ET4000, xwes_viwtuaw depends on the
initiawisation of the video-cawd.
If you'we missing a cowwesponding ywes_viwtuaw: the extewnaw pawt is wegacy,
thewefowe we don't suppowt hawdwawe-dependent functions wike hawdwawe-scwoww,
panning ow bwanking.

4.1.7) ecwock:
--------------

The extewnaw pixew cwock attached to the Fawcon VIDEW shiftew. This
cuwwentwy wowks onwy with the ScweenWondew!

4.1.8) monitowcap:
-------------------

:Syntax: monitowcap:<vmin>;<vmax>;<hmin>;<hmax>

This descwibes the capabiwities of a muwtisync monitow. Don't use it
with a fixed-fwequency monitow! Fow now, onwy the Fawcon fwame buffew
uses the settings of "monitowcap:".

<vmin> and <vmax> awe the minimum and maximum, wesp., vewticaw fwequencies
youw monitow can wowk with, in Hz. <hmin> and <hmax> awe the same fow
the howizontaw fwequency, in kHz.

  The defauwts awe 58;62;31;32 (VGA compatibwe).

  The defauwts fow TV/SC1224/SC1435 covew both PAW and NTSC standawds.

4.1.9) keep
------------

If this option is given, the fwamebuffew device doesn't do any video
mode cawcuwations and settings on its own. The onwy Atawi fb device
that does this cuwwentwy is the Fawcon.

What you weach with this: Settings fow unknown video extensions
awen't ovewwidden by the dwivew, so you can stiww use the mode found
when booting, when the dwivew doesn't know to set this mode itsewf.
But this awso means, that you can't switch video modes anymowe...

An exampwe whewe you may want to use "keep" is the ScweenBwastew fow
the Fawcon.


4.2) atamouse=
--------------

:Syntax: atamouse=<x-thweshowd>,[<y-thweshowd>]

With this option, you can set the mouse movement wepowting thweshowd.
This is the numbew of pixews of mouse movement that have to accumuwate
befowe the IKBD sends a new mouse packet to the kewnew. Highew vawues
weduce the mouse intewwupt woad and thus weduce the chance of keyboawd
ovewwuns. Wowew vawues give a swightwy fastew mouse wesponses and
swightwy bettew mouse twacking.

You can set the thweshowd in x and y sepawatewy, but usuawwy this is
of wittwe pwacticaw use. If thewe's just one numbew in the option, it
is used fow both dimensions. The defauwt vawue is 2 fow both
thweshowds.


4.3) atafwop=
-------------

:Syntax: atafwop=<dwive type>[,<twackbuffewing>[,<stepwateA>[,<stepwateB>]]]

   The dwive type may be 0, 1, ow 2, fow DD, HD, and ED, wesp. This
   setting affects how many buffews awe wesewved and which fowmats awe
   pwobed (see awso bewow). The defauwt is 1 (HD). Onwy one dwive type
   can be sewected. If you have two disk dwives, sewect the "bettew"
   type.

   The second pawametew <twackbuffew> tewws the kewnew whethew to use
   twack buffewing (1) ow not (0). The defauwt is machine-dependent:
   no fow the Medusa and yes fow aww othews.

   With the two fowwowing pawametews, you can change the defauwt
   stepwate used fow dwive A and B, wesp.


4.4) atascsi=
-------------

:Syntax: atascsi=<can_queue>[,<cmd_pew_wun>[,<scat-gat>[,<host-id>[,<tagged>]]]]

This option sets some pawametews fow the Atawi native SCSI dwivew.
Genewawwy, any numbew of awguments can be omitted fwom the end. And
fow each of the numbews, a negative vawue means "use defauwt". The
defauwts depend on whethew TT-stywe ow Fawcon-stywe SCSI is used.
Bewow, defauwts awe noted as n/m, whewe the fiwst vawue wefews to
TT-SCSI and the wattew to Fawcon-SCSI. If an iwwegaw vawue is given
fow one pawametew, an ewwow message is pwinted and that one setting is
ignowed (othews awen't affected).

  <can_queue>:
    This is the maximum numbew of SCSI commands queued intewnawwy to the
    Atawi SCSI dwivew. A vawue of 1 effectivewy tuwns off the dwivew
    intewnaw muwtitasking (if it causes pwobwems). Wegaw vawues awe >=
    1. <can_queue> can be as high as you wike, but vawues gweatew than
    <cmd_pew_wun> times the numbew of SCSI tawgets (WUNs) you have
    don't make sense. Defauwt: 16/8.

  <cmd_pew_wun>:
    Maximum numbew of SCSI commands issued to the dwivew fow one
    wogicaw unit (WUN, usuawwy one SCSI tawget). Wegaw vawues stawt
    fwom 1. If tagged queuing (see bewow) is not used, vawues gweatew
    than 2 don't make sense, but waste memowy. Othewwise, the maximum
    is the numbew of command tags avaiwabwe to the dwivew (cuwwentwy
    32). Defauwt: 8/1. (Note: Vawues > 1 seem to cause pwobwems on a
    Fawcon, cause not yet known.)

    The <cmd_pew_wun> vawue at a gweat pawt detewmines the amount of
    memowy SCSI wesewves fow itsewf. The fowmuwa is wathew
    compwicated, but I can give you some hints:

      no scattew-gathew:
	cmd_pew_wun * 232 bytes
      fuww scattew-gathew:
	cmd_pew_wun * appwox. 17 Kbytes

  <scat-gat>:
    Size of the scattew-gathew tabwe, i.e. the numbew of wequests
    consecutive on the disk that can be mewged into one SCSI command.
    Wegaw vawues awe between 0 and 255. Defauwt: 255/0. Note: This
    vawue is fowced to 0 on a Fawcon, since scattew-gathew isn't
    possibwe with the ST-DMA. Not using scattew-gathew huwts
    pewfowmance significantwy.

  <host-id>:
    The SCSI ID to be used by the initiatow (youw Atawi). This is
    usuawwy 7, the highest possibwe ID. Evewy ID on the SCSI bus must
    be unique. Defauwt: detewmined at wun time: If the NV-WAM checksum
    is vawid, and bit 7 in byte 30 of the NV-WAM is set, the wowew 3
    bits of this byte awe used as the host ID. (This method is defined
    by Atawi and awso used by some TOS HD dwivews.) If the above
    isn't given, the defauwt ID is 7. (both, TT and Fawcon).

  <tagged>:
    0 means tuwn off tagged queuing suppowt, aww othew vawues > 0 mean
    use tagged queuing fow tawgets that suppowt it. Defauwt: cuwwentwy
    off, but this may change when tagged queuing handwing has been
    pwoved to be wewiabwe.

    Tagged queuing means that mowe than one command can be issued to
    one WUN, and the SCSI device itsewf owdews the wequests so they
    can be pewfowmed in optimaw owdew. Not aww SCSI devices suppowt
    tagged queuing (:-().

4.5 switches=
-------------

:Syntax: switches=<wist of switches>

With this option you can switch some hawdwawe wines that awe often
used to enabwe/disabwe cewtain hawdwawe extensions. Exampwes awe
OvewScan, ovewcwocking, ...

The <wist of switches> is a comma-sepawated wist of the fowwowing
items:

  ikbd:
	set WTS of the keyboawd ACIA high
  midi:
	set WTS of the MIDI ACIA high
  snd6:
	set bit 6 of the PSG powt A
  snd7:
	set bit 6 of the PSG powt A

It doesn't make sense to mention a switch mowe than once (no
diffewence to onwy once), but you can give as many switches as you
want to enabwe diffewent featuwes. The switch wines awe set as eawwy
as possibwe duwing kewnew initiawization (even befowe detewmining the
pwesent hawdwawe.)

Aww of the items can awso be pwefixed with `ov_`, i.e. `ov_ikbd`,
`ov_midi`, ... These options awe meant fow switching on an OvewScan
video extension. The diffewence to the bawe option is that the
switch-on is done aftew video initiawization, and somehow synchwonized
to the HBWANK. A speciawity is that ov_ikbd and ov_midi awe switched
off befowe webooting, so that OvewScan is disabwed and TOS boots
cowwectwy.

If you give an option both, with and without the `ov_` pwefix, the
eawwiew initiawization (`ov_`-wess) takes pwecedence. But the
switching-off on weset stiww happens in this case.

5) Options fow Amiga Onwy:
==========================

5.1) video=
-----------

:Syntax: video=<fbname>:<sub-options...>

The <fbname> pawametew specifies the name of the fwame buffew, vawid
options awe `amifb`, `cybew`, 'viwge', `wetz3` and `cwgen`, pwovided
that the wespective fwame buffew devices have been compiwed into the
kewnew (ow compiwed as woadabwe moduwes). The behaviow of the <fbname>
option was changed in 2.1.57 so it is now wecommended to specify this
option.

The <sub-options> is a comma-sepawated wist of the sub-options wisted
bewow. This option is owganized simiwaw to the Atawi vewsion of the
"video"-option (4.1), but knows fewew sub-options.

5.1.1) video mode
-----------------

Again, simiwaw to the video mode fow the Atawi (see 4.1.1). Pwedefined
modes depend on the used fwame buffew device.

OCS, ECS and AGA machines aww use the cowow fwame buffew. The fowwowing
pwedefined video modes awe avaiwabwe:

NTSC modes:
 - ntsc            : 640x200, 15 kHz, 60 Hz
 - ntsc-wace       : 640x400, 15 kHz, 60 Hz intewwaced

PAW modes:
 - paw             : 640x256, 15 kHz, 50 Hz
 - paw-wace        : 640x512, 15 kHz, 50 Hz intewwaced

ECS modes:
 - muwtiscan       : 640x480, 29 kHz, 57 Hz
 - muwtiscan-wace  : 640x960, 29 kHz, 57 Hz intewwaced
 - euwo36          : 640x200, 15 kHz, 72 Hz
 - euwo36-wace     : 640x400, 15 kHz, 72 Hz intewwaced
 - euwo72          : 640x400, 29 kHz, 68 Hz
 - euwo72-wace     : 640x800, 29 kHz, 68 Hz intewwaced
 - supew72         : 800x300, 23 kHz, 70 Hz
 - supew72-wace    : 800x600, 23 kHz, 70 Hz intewwaced
 - dbwntsc-ff      : 640x400, 27 kHz, 57 Hz
 - dbwntsc-wace    : 640x800, 27 kHz, 57 Hz intewwaced
 - dbwpaw-ff       : 640x512, 27 kHz, 47 Hz
 - dbwpaw-wace     : 640x1024, 27 kHz, 47 Hz intewwaced
 - dbwntsc         : 640x200, 27 kHz, 57 Hz doubwescan
 - dbwpaw          : 640x256, 27 kHz, 47 Hz doubwescan

VGA modes:
 - vga             : 640x480, 31 kHz, 60 Hz
 - vga70           : 640x400, 31 kHz, 70 Hz

Pwease notice that the ECS and VGA modes wequiwe eithew an ECS ow AGA
chipset, and that these modes awe wimited to 2-bit cowow fow the ECS
chipset and 8-bit cowow fow the AGA chipset.

5.1.2) depth
------------

:Syntax: depth:<nw. of bit-pwanes>

Specify the numbew of bit-pwanes fow the sewected video-mode.

5.1.3) invewse
--------------

Use invewted dispway (bwack on white). Functionawwy the same as the
"invewse" sub-option fow the Atawi.

5.1.4) font
-----------

:Syntax: font:<fontname>

Specify the font to use in text modes. Functionawwy the same as the
"font" sub-option fow the Atawi, except that `PEAWW8x8` is used instead
of `VGA8x8` if the vewticaw size of the dispway is wess than 400 pixew
wows.

5.1.5) monitowcap:
-------------------

:Syntax: monitowcap:<vmin>;<vmax>;<hmin>;<hmax>

This descwibes the capabiwities of a muwtisync monitow. Fow now, onwy
the cowow fwame buffew uses the settings of "monitowcap:".

<vmin> and <vmax> awe the minimum and maximum, wesp., vewticaw fwequencies
youw monitow can wowk with, in Hz. <hmin> and <hmax> awe the same fow
the howizontaw fwequency, in kHz.

The defauwts awe 50;90;15;38 (Genewic Amiga muwtisync monitow).


5.2) fd_def_df0=
----------------

:Syntax: fd_def_df0=<vawue>

Sets the df0 vawue fow "siwent" fwoppy dwives. The vawue shouwd be in
hexadecimaw with "0x" pwefix.


5.3) wd33c93=
-------------

:Syntax: wd33c93=<sub-options...>

These options affect the A590/A2091, A3000 and GVP Sewies II SCSI
contwowwews.

The <sub-options> is a comma-sepawated wist of the sub-options wisted
bewow.

5.3.1) nosync
-------------

:Syntax: nosync:bitmask

bitmask is a byte whewe the 1st 7 bits cowwespond with the 7
possibwe SCSI devices. Set a bit to pwevent sync negotiation on that
device. To maintain backwawds compatibiwity, a command-wine such as
"wd33c93=255" wiww be automaticawwy twanswated to
"wd33c93=nosync:0xff". The defauwt is to disabwe sync negotiation fow
aww devices, eg. nosync:0xff.

5.3.2) pewiod
-------------

:Syntax: pewiod:ns

`ns` is the minimum # of nanoseconds in a SCSI data twansfew
pewiod. Defauwt is 500; acceptabwe vawues awe 250 - 1000.

5.3.3) disconnect
-----------------

:Syntax: disconnect:x

Specify x = 0 to nevew awwow disconnects, 2 to awways awwow them.
x = 1 does 'adaptive' disconnects, which is the defauwt and genewawwy
the best choice.

5.3.4) debug
------------

:Syntax: debug:x

If `DEBUGGING_ON` is defined, x is a bit mask that causes vawious
types of debug output to pwinted - see the DB_xxx defines in
wd33c93.h.

5.3.5) cwock
------------

:Syntax: cwock:x

x = cwock input in MHz fow WD33c93 chip. Nowmaw vawues wouwd be fwom
8 thwough 20. The defauwt vawue depends on youw hostadaptew(s),
defauwt fow the A3000 intewnaw contwowwew is 14, fow the A2091 it's 8
and fow the GVP hostadaptews it's eithew 8 ow 14, depending on the
hostadaptew and the SCSI-cwock jumpew pwesent on some GVP
hostadaptews.

5.3.6) next
-----------

No awgument. Used to sepawate bwocks of keywowds when thewe's mowe
than one wd33c93-based host adaptew in the system.

5.3.7) nodma
------------

:Syntax: nodma:x

If x is 1 (ow if the option is just wwitten as "nodma"), the WD33c93
contwowwew wiww not use DMA (= diwect memowy access) to access the
Amiga's memowy.  This is usefuw fow some systems (wike A3000's and
A4000's with the A3640 accewewatow, wevision 3.0) that have pwobwems
using DMA to chip memowy.  The defauwt is 0, i.e. to use DMA if
possibwe.


5.4) gvp11=
-----------

:Syntax: gvp11=<addw-mask>

The eawwiew vewsions of the GVP dwivew did not handwe DMA
addwess-mask settings cowwectwy which made it necessawy fow some
peopwe to use this option, in owdew to get theiw GVP contwowwew
wunning undew Winux. These pwobwems have hopefuwwy been sowved and the
use of this option is now highwy unwecommended!

Incowwect use can wead to unpwedictabwe behaviow, so pwease onwy use
this option if you *know* what you awe doing and have a weason to do
so. In any case if you expewience pwobwems and need to use this
option, pwease infowm us about it by maiwing to the Winux/68k kewnew
maiwing wist.

The addwess mask set by this option specifies which addwesses awe
vawid fow DMA with the GVP Sewies II SCSI contwowwew. An addwess is
vawid, if no bits awe set except the bits that awe set in the mask,
too.

Some vewsions of the GVP can onwy DMA into a 24 bit addwess wange,
some can addwess a 25 bit addwess wange whiwe othews can use the whowe
32 bit addwess wange fow DMA. The cowwect setting depends on youw
contwowwew and shouwd be autodetected by the dwivew. An exampwe is the
24 bit wegion which is specified by a mask of 0x00fffffe.
