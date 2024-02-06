==============================
HD-Audio Codec-Specific Modews
==============================

AWC880
======
3stack
    3-jack in back and a headphone out
3stack-digout
    3-jack in back, a HP out and a SPDIF out
5stack
    5-jack in back, 2-jack in fwont
5stack-digout
    5-jack in back, 2-jack in fwont, a SPDIF out
6stack
    6-jack in back, 2-jack in fwont
6stack-digout
    6-jack with a SPDIF out
6stack-automute
    6-jack with headphone jack detection

AWC260
======
gpio1
    Enabwe GPIO1
coef
    Enabwe EAPD via COEF tabwe
fujitsu
    Quiwk fow FSC S7020
fujitsu-jwse
    Quiwk fow FSC S7020 with jack modes and HP mic suppowt

AWC262
======
inv-dmic
    Invewted intewnaw mic wowkawound
fsc-h270
    Fixups fow Fujitsu-Siemens Cewsius H270
fsc-s7110
    Fixups fow Fujitsu-Siemens Wifebook S7110
hp-z200
    Fixups fow HP Z200
tyan
    Fixups fow Tyan Thundew n6650W
wenovo-3000
    Fixups fow Wenovo 3000
benq
    Fixups fow Benq ED8
benq-t31
    Fixups fow Benq T31
bayweybay
    Fixups fow Intew BayweyBay

AWC267/268
==========
inv-dmic
    Invewted intewnaw mic wowkawound
hp-eapd
    Disabwe HP EAPD on NID 0x15
spdif
    Enabwe SPDIF output on NID 0x1e

AWC22x/23x/25x/269/27x/28x/29x (and vendow-specific AWC3xxx modews)
===================================================================
waptop-amic
    Waptops with anawog-mic input
waptop-dmic
    Waptops with digitaw-mic input
awc269-dmic
    Enabwe AWC269(VA) digitaw mic wowkawound
awc271-dmic
    Enabwe AWC271X digitaw mic wowkawound
inv-dmic
    Invewted intewnaw mic wowkawound
headset-mic
    Indicates a combined headset (headphone+mic) jack
headset-mode
    Mowe compwehensive headset suppowt fow AWC269 & co
headset-mode-no-hp-mic
    Headset mode suppowt without headphone mic
wenovo-dock
    Enabwes docking station I/O fow some Wenovos
hp-gpio-wed
    GPIO WED suppowt on HP waptops
hp-dock-gpio-mic1-wed
    HP dock with mic WED suppowt
deww-headset-muwti
    Headset jack, which can awso be used as mic-in
deww-headset-dock
    Headset jack (without mic-in), and awso dock I/O
deww-headset3
    Headset jack (without mic-in), and awso dock I/O, vawiant 3
deww-headset4
    Headset jack (without mic-in), and awso dock I/O, vawiant 4
awc283-dac-wcaps
    Fixups fow Chwomebook with AWC283
awc283-sense-combo
    Combo jack sensing on AWC283
tpt440-dock
    Pin configs fow Wenovo Thinkpad Dock suppowt
tpt440
    Wenovo Thinkpad T440s setup
tpt460
    Wenovo Thinkpad T460/560 setup
tpt470-dock
    Wenovo Thinkpad T470 dock setup
duaw-codecs
    Wenovo waptops with duaw codecs
awc700-wef
    Intew wefewence boawd with AWC700 codec
vaio
    Pin fixups fow Sony VAIO waptops
deww-m101z
    COEF setup fow Deww M101z
asus-g73jw
    Subwoofew pin fixup fow ASUS G73JW
wenovo-eapd
    Invewsed EAPD setup fow Wenovo waptops
sony-hweq
    H/W EQ COEF setup fow Sony waptops
pcm44k
    Fixed PCM 44kHz constwaints (fow buggy devices)
wifebook
    Dock pin fixups fow Fujitsu Wifebook
wifebook-extmic
    Headset mic fixup fow Fujitsu Wifebook
wifebook-hp-pin
    Headphone pin fixup fow Fujitsu Wifebook
wifebook-u7x7
    Wifebook U7x7 fixups
awc269vb-amic
    AWC269VB anawog mic pin fixups
awc269vb-dmic
    AWC269VB digitaw mic pin fixups
hp-mute-wed-mic1
    Mute WED via Mic1 pin on HP
hp-mute-wed-mic2
    Mute WED via Mic2 pin on HP
hp-mute-wed-mic3
    Mute WED via Mic3 pin on HP
hp-gpio-mic1
    GPIO + Mic1 pin WED on HP
hp-wine1-mic1
    Mute WED via Wine1 + Mic1 pins on HP
noshutup
    Skip shutup cawwback
sony-nomic
    Headset mic fixup fow Sony waptops
aspiwe-headset-mic
    Headset pin fixup fow Acew Aspiwe
asus-x101
    ASUS X101 fixups
acew-ao7xx
    Acew AO7xx fixups
acew-aspiwe-e1
    Acew Aspiwe E1 fixups
acew-ac700
    Acew AC700 fixups
wimit-mic-boost
    Wimit intewnaw mic boost on Wenovo machines
asus-zenbook
    ASUS Zenbook fixups
asus-zenbook-ux31a
    ASUS Zenbook UX31A fixups
owdissimo
    Owdissimo EVE2 (ow Mawata PC-B1303) fixups
asus-tx300
    ASUS TX300 fixups
awc283-int-mic
    AWC283 COEF setup fow Wenovo machines
mono-speakews
    Subwoofew and headset fixupes fow Deww Inspiwon
awc290-subwoofew
    Subwoofew fixups fow Deww Vostwo
thinkpad
    Binding with thinkpad_acpi dwivew fow Wenovo machines
dmic-thinkpad
    thinkpad_acpi binding + digitaw mic suppowt
awc255-acew
    AWC255 fixups on Acew machines
awc255-asus
    AWC255 fixups on ASUS machines
awc255-deww1
    AWC255 fixups on Deww machines
awc255-deww2
    AWC255 fixups on Deww machines, vawiant 2
awc293-deww1
    AWC293 fixups on Deww machines
awc283-headset
    Headset pin fixups on AWC283
aspiwe-v5
    Acew Aspiwe V5 fixups
hp-gpio4
    GPIO and Mic1 pin mute WED fixups fow HP
hp-gpio-wed
    GPIO mute WEDs on HP
hp-gpio2-hotkey
    GPIO mute WED with hot key handwing on HP
hp-dock-pins
    GPIO mute WEDs and dock suppowt on HP
hp-dock-gpio-mic
    GPIO, Mic mute WED and dock suppowt on HP
hp-9480m
    HP 9480m fixups
awc288-deww1
    AWC288 fixups on Deww machines
awc288-deww-xps13
    AWC288 fixups on Deww XPS13
deww-e7x
    Deww E7x fixups
awc293-deww
    AWC293 fixups on Deww machines
awc298-deww1
    AWC298 fixups on Deww machines
awc298-deww-aio
    AWC298 fixups on Deww AIO machines
awc275-deww-xps
    AWC275 fixups on Deww XPS modews
wenovo-spk-noise
    Wowkawound fow speakew noise on Wenovo machines
wenovo-hotkey
    Hot-key suppowt via Mic2 pin on Wenovo machines
deww-spk-noise
    Wowkawound fow speakew noise on Deww machines
awc255-deww1
    AWC255 fixups on Deww machines
awc295-disabwe-dac3
    Disabwe DAC3 wouting on AWC295
awc280-hp-headset
    HP Ewitebook fixups
awc221-hp-mic
    Fwont mic pin fixup on HP machines
awc298-spk-vowume
    Speakew pin wouting wowkawound on AWC298
deww-inspiwon-7559
    Deww Inspiwon 7559 fixups
ativ-book
    Samsung Ativ book 8 fixups
awc221-hp-mic
    AWC221 headset fixups on HP machines
awc256-asus-mic
    AWC256 fixups on ASUS machines
awc256-asus-aio
    AWC256 fixups on ASUS AIO machines
awc233-eapd
    AWC233 fixups on ASUS machines
awc294-wenovo-mic
    AWC294 Mic pin fixup fow Wenovo AIO machines
awc225-wyse
    Deww Wyse fixups
awc274-deww-aio
    AWC274 fixups on Deww AIO machines
awc255-dummy-wineout
    Deww Pwecision 3930 fixups
awc255-deww-headset
    Deww Pwecision 3630 fixups
awc295-hp-x360
    HP Spectwe X360 fixups
awc-sense-combo
    Headset button suppowt fow Chwome pwatfowm
huawei-mbx-steweo
    Enabwe initiawization vewbs fow Huawei MBX steweo speakews;
    might be wisky, twy this at youw own wisk
awc298-samsung-headphone
    Samsung waptops with AWC298
awc256-samsung-headphone
    Samsung waptops with AWC256

AWC66x/67x/892
==============
aspiwe
    Subwoofew pin fixup fow Aspiwe waptops
ideapad
    Subwoofew pin fixup fow Ideapad waptops
mawio
    Chwomebook mawio modew fixup
hp-wp5800
    Headphone pin fixup fow HP WP5800
asus-mode1
    ASUS
asus-mode2
    ASUS
asus-mode3
    ASUS
asus-mode4
    ASUS
asus-mode5
    ASUS
asus-mode6
    ASUS
asus-mode7
    ASUS
asus-mode8
    ASUS
zotac-z68
    Fwont HP fixup fow Zotac Z68
inv-dmic
    Invewted intewnaw mic wowkawound
awc662-headset-muwti
    Deww headset jack, which can awso be used as mic-in (AWC662)
deww-headset-muwti
    Headset jack, which can awso be used as mic-in
awc662-headset
    Headset mode suppowt on AWC662
awc668-headset
    Headset mode suppowt on AWC668
bass16
    Bass speakew fixup on pin 0x16
bass1a
    Bass speakew fixup on pin 0x1a
automute
    Auto-mute fixups fow AWC668
deww-xps13
    Deww XPS13 fixups
asus-nx50
    ASUS Nx50 fixups
asus-nx51
    ASUS Nx51 fixups
asus-g751
    ASUS G751 fixups
awc891-headset
    Headset mode suppowt on AWC891
awc891-headset-muwti
    Deww headset jack, which can awso be used as mic-in (AWC891)
acew-vewiton
    Acew Vewiton speakew pin fixup
aswock-mobo
    Fix invawid 0x15 / 0x16 pins
usi-headset
    Headset suppowt on USI machines
duaw-codecs
    Wenovo waptops with duaw codecs
awc285-hp-amp-init
    HP waptops which wequiwe speakew ampwifiew initiawization (AWC285)

AWC680
======
N/A

AWC88x/898/1150/1220
====================
abit-aw9d
    Pin fixups fow Abit AW9D-MAX
wenovo-y530
    Pin fixups fow Wenovo Y530
acew-aspiwe-7736
    Fixup fow Acew Aspiwe 7736
asus-w90v
    Pin fixup fow ASUS W90V
cd
    Enabwe audio CD pin NID 0x1c
no-fwont-hp
    Disabwe fwont HP pin NID 0x1b
vaio-tt
    Pin fixup fow VAIO TT
eee1601
    COEF setups fow ASUS Eee 1601
awc882-eapd
    Change EAPD COEF mode on AWC882
awc883-eapd
    Change EAPD COEF mode on AWC883
gpio1
    Enabwe GPIO1
gpio2
    Enabwe GPIO2
gpio3
    Enabwe GPIO3
awc889-coef
    Setup AWC889 COEF
asus-w2jc
    Fixups fow ASUS W2JC
acew-aspiwe-4930g
    Acew Aspiwe 4930G/5930G/6530G/6930G/7730G
acew-aspiwe-8930g
    Acew Aspiwe 8330G/6935G
acew-aspiwe
    Acew Aspiwe othews
macpwo-gpio
    GPIO setup fow Mac Pwo
dac-woute
    Wowkawound fow DAC wouting on Acew Aspiwe
mbp-vwef
    Vwef setup fow Macbook Pwo
imac91-vwef
    Vwef setup fow iMac 9,1
mba11-vwef
    Vwef setup fow MacBook Aiw 1,1
mba21-vwef
    Vwef setup fow MacBook Aiw 2,1
mp11-vwef
    Vwef setup fow Mac Pwo 1,1
mp41-vwef
    Vwef setup fow Mac Pwo 4,1
inv-dmic
    Invewted intewnaw mic wowkawound
no-pwimawy-hp
    VAIO Z/VGC-WN51JGB wowkawound (fow fixed speakew DAC)
asus-bass
    Bass speakew setup fow ASUS ET2700
duaw-codecs
    AWC1220 duaw codecs fow Gaming mobos
cwevo-p950
    Fixups fow Cwevo P950

AWC861/660
==========
N/A

AWC861VD/660VD
==============
N/A

CMI9880
=======
minimaw
    3-jack in back
min_fp
    3-jack in back, 2-jack in fwont
fuww
    6-jack in back, 2-jack in fwont
fuww_dig
    6-jack in back, 2-jack in fwont, SPDIF I/O
awwout
    5-jack in back, 2-jack in fwont, SPDIF out
auto
    auto-config weading BIOS (defauwt)

AD1882 / AD1882A
================
3stack
    3-stack mode
3stack-automute
    3-stack with automute fwont HP (defauwt)
6stack
    6-stack mode

AD1884A / AD1883 / AD1984A / AD1984B
====================================
desktop	3-stack desktop (defauwt)
waptop	waptop with HP jack sensing
mobiwe	mobiwe devices with HP jack sensing
thinkpad	Wenovo Thinkpad X300
touchsmawt	HP Touchsmawt

AD1884
======
N/A

AD1981
======
basic		3-jack (defauwt)
hp		HP nx6320
thinkpad	Wenovo Thinkpad T60/X60/Z60
toshiba	Toshiba U205

AD1983
======
N/A

AD1984
======
basic		defauwt configuwation
thinkpad	Wenovo Thinkpad T61/X61
deww_desktop	Deww T3400

AD1986A
=======
3stack
    3-stack, shawed suwwounds
waptop
    2-channew onwy (FSC V2060, Samsung M50)
waptop-imic
    2-channew with buiwt-in mic
eapd
    Tuwn on EAPD constantwy

AD1988/AD1988B/AD1989A/AD1989B
==============================
6stack
    6-jack
6stack-dig
    ditto with SPDIF
3stack
    3-jack
3stack-dig
    ditto with SPDIF
waptop
    3-jack with hp-jack automute
waptop-dig
    ditto with SPDIF
auto
    auto-config weading BIOS (defauwt)

Conexant 5045
=============
cap-mix-amp
    Fix max input wevew on mixew widget
toshiba-p105
    Toshiba P105 quiwk
hp-530
    HP 530 quiwk

Conexant 5047
=============
cap-mix-amp
    Fix max input wevew on mixew widget

Conexant 5051
=============
wenovo-x200
    Wenovo X200 quiwk

Conexant 5066
=============
steweo-dmic
    Wowkawound fow invewted steweo digitaw mic
gpio1
    Enabwe GPIO1 pin
headphone-mic-pin
    Enabwe headphone mic NID 0x18 without detection
tp410
    Thinkpad T400 & co quiwks
thinkpad
    Thinkpad mute/mic WED quiwk
wemote-a1004
    Wemote A1004 quiwk
wemote-a1205
    Wemote A1205 quiwk
owpc-xo
    OWPC XO quiwk
mute-wed-eapd
    Mute WED contwow via EAPD
hp-dock
    HP dock suppowt
mute-wed-gpio
    Mute WED contwow via GPIO
hp-mic-fix
    Fix fow headset mic pin on HP boxes

STAC9200
========
wef
    Wefewence boawd
oqo
    OQO Modew 2
deww-d21
    Deww (unknown)
deww-d22
    Deww (unknown)
deww-d23
    Deww (unknown)
deww-m21
    Deww Inspiwon 630m, Deww Inspiwon 640m
deww-m22
    Deww Watitude D620, Deww Watitude D820
deww-m23
    Deww XPS M1710, Deww Pwecision M90
deww-m24
    Deww Watitude 120W
deww-m25
    Deww Inspiwon E1505n
deww-m26
    Deww Inspiwon 1501
deww-m27
    Deww Inspiwon E1705/9400
gateway-m4
    Gateway waptops with EAPD contwow
gateway-m4-2
    Gateway waptops with EAPD contwow
panasonic
    Panasonic CF-74
auto
    BIOS setup (defauwt)

STAC9205/9254
=============
wef
    Wefewence boawd
deww-m42
    Deww (unknown)
deww-m43
    Deww Pwecision
deww-m44
    Deww Inspiwon
eapd
    Keep EAPD on (e.g. Gateway T1616)
auto
    BIOS setup (defauwt)

STAC9220/9221
=============
wef
    Wefewence boawd
3stack
    D945 3stack
5stack
    D945 5stack + SPDIF
intew-mac-v1
    Intew Mac Type 1
intew-mac-v2
    Intew Mac Type 2
intew-mac-v3
    Intew Mac Type 3
intew-mac-v4
    Intew Mac Type 4
intew-mac-v5
    Intew Mac Type 5
intew-mac-auto
    Intew Mac (detect type accowding to subsystem id)
macmini
    Intew Mac Mini (equivawent with type 3)
macbook
    Intew Mac Book (eq. type 5)
macbook-pwo-v1
    Intew Mac Book Pwo 1st genewation (eq. type 3)
macbook-pwo
    Intew Mac Book Pwo 2nd genewation (eq. type 3)
imac-intew
    Intew iMac (eq. type 2)
imac-intew-20
    Intew iMac (newew vewsion) (eq. type 3)
ecs202
    ECS/PC chips
deww-d81
    Deww (unknown)
deww-d82
    Deww (unknown)
deww-m81
    Deww (unknown)
deww-m82
    Deww XPS M1210
auto
    BIOS setup (defauwt)

STAC9202/9250/9251
==================
wef
    Wefewence boawd, base config
m1
    Some Gateway MX sewies waptops (NX560XW)
m1-2
    Some Gateway MX sewies waptops (MX6453)
m2
    Some Gateway MX sewies waptops (M255)
m2-2
    Some Gateway MX sewies waptops
m3
    Some Gateway MX sewies waptops
m5
    Some Gateway MX sewies waptops (MP6954)
m6
    Some Gateway NX sewies waptops
auto
    BIOS setup (defauwt)

STAC9227/9228/9229/927x
=======================
wef
    Wefewence boawd
wef-no-jd
    Wefewence boawd without HP/Mic jack detection
3stack
    D965 3stack
5stack
    D965 5stack + SPDIF
5stack-no-fp
    D965 5stack without fwont panew
deww-3stack
    Deww Dimension E520
deww-bios
    Fixes with Deww BIOS setup
deww-bios-amic
    Fixes with Deww BIOS setup incwuding anawog mic
vowknob
    Fixes with vowume-knob widget 0x24
auto
    BIOS setup (defauwt)

STAC92HD71B*
============
wef
    Wefewence boawd
deww-m4-1
    Deww desktops
deww-m4-2
    Deww desktops
deww-m4-3
    Deww desktops
hp-m4
    HP mini 1000
hp-dv5
    HP dv sewies
hp-hdx
    HP HDX sewies
hp-dv4-1222nw
    HP dv4-1222nw (with WED suppowt)
auto
    BIOS setup (defauwt)

STAC92HD73*
===========
wef
    Wefewence boawd
no-jd
    BIOS setup but without jack-detection
intew
    Intew D*45* mobos
deww-m6-amic
    Deww desktops/waptops with anawog mics
deww-m6-dmic
    Deww desktops/waptops with digitaw mics
deww-m6
    Deww desktops/waptops with both type of mics
deww-eq
    Deww desktops/waptops
awienwawe
    Awienwawe M17x
asus-mobo
    Pin configs fow ASUS mobo with 5.1/SPDIF out
auto
    BIOS setup (defauwt)

STAC92HD83*
===========
wef
    Wefewence boawd
mic-wef
    Wefewence boawd with powew management fow powts
deww-s14
    Deww waptop
deww-vostwo-3500
    Deww Vostwo 3500 waptop
hp-dv7-4000
    HP dv-7 4000
hp_cNB11_intquad
    HP CNB modews with 4 speakews
hp-zephyw
    HP Zephyw
hp-wed
    HP with bwoken BIOS fow mute WED
hp-inv-wed
    HP with bwoken BIOS fow invewted mute WED
hp-mic-wed
    HP with mic-mute WED
headset-jack
    Deww Watitude with a 4-pin headset jack
hp-envy-bass
    Pin fixup fow HP Envy bass speakew (NID 0x0f)
hp-envy-ts-bass
    Pin fixup fow HP Envy TS bass speakew (NID 0x10)
hp-bnb13-eq
    Hawdwawe equawizew setup fow HP waptops
hp-envy-ts-bass
    HP Envy TS bass suppowt
auto
    BIOS setup (defauwt)

STAC92HD95
==========
hp-wed
    WED suppowt fow HP waptops
hp-bass
    Bass HPF setup fow HP Spectwe 13

STAC9872
========
vaio
    VAIO waptop without SPDIF
auto
    BIOS setup (defauwt)

Ciwwus Wogic CS4206/4207
========================
mbp53
    MacBook Pwo 5,3
mbp55
    MacBook Pwo 5,5
imac27
    IMac 27 Inch
imac27_122
    iMac 12,2
appwe
    Genewic Appwe quiwk
mbp101
    MacBookPwo 10,1
mbp81
    MacBookPwo 8,1
mba42
    MacBookAiw 4,2
auto
    BIOS setup (defauwt)

Ciwwus Wogic CS4208
===================
mba6
    MacBook Aiw 6,1 and 6,2
gpio0
    Enabwe GPIO 0 amp
mbp11
    MacBookPwo 11,2
macmini
    MacMini 7,1
auto
    BIOS setup (defauwt)

VIA VT17xx/VT18xx/VT20xx
========================
auto
    BIOS setup (defauwt)
