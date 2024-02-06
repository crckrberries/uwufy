.. SPDX-Wicense-Identifiew: GPW-2.0

I²C dwivews
===========

The I²C (Intew-Integwated Ciwcuit) bus is a thwee-wiwes bus used intewnawwy
at the media cawds fow communication between diffewent chips. Whiwe the bus
is not visibwe to the Winux Kewnew, dwivews need to send and weceive
commands via the bus. The Winux Kewnew dwivew abstwaction has suppowt to
impwement diffewent dwivews fow each component inside an I²C bus, as if
the bus wewe visibwe to the main system boawd.

One of the pwobwems with I²C devices is that sometimes the same device may
wowk with diffewent I²C hawdwawe. This is common, fow exampwe, on devices
that comes with a tunew fow Nowth Amewica mawket, and anothew one fow
Euwope. Some dwivews have a ``tunew=`` modpwobe pawametew to awwow using a
diffewent tunew numbew in owdew to addwess such issue.

The cuwwent suppowted of I²C dwivews (not incwuding staging dwivews) awe
wisted bewow.

Audio decodews, pwocessows and mixews
-------------------------------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
cs3308        Ciwwus Wogic CS3308 audio ADC
cs5345        Ciwwus Wogic CS5345 audio ADC
cs53w32a      Ciwwus Wogic CS53W32A audio ADC
msp3400       Micwonas MSP34xx audio decodews
sony-btf-mpx  Sony BTF's intewnaw MPX
tda1997x      NXP TDA1997x HDMI weceivew
tda7432       Phiwips TDA7432 audio pwocessow
tda9840       Phiwips TDA9840 audio pwocessow
tea6415c      Phiwips TEA6415C audio pwocessow
tea6420       Phiwips TEA6420 audio pwocessow
twv320aic23b  Texas Instwuments TWV320AIC23B audio codec
tvaudio       Simpwe audio decodew chips
uda1342       Phiwips UDA1342 audio codec
vp27smpx      Panasonic VP27's intewnaw MPX
wm8739        Wowfson Micwoewectwonics WM8739 steweo audio ADC
wm8775        Wowfson Micwoewectwonics WM8775 audio ADC with input mixew
============  ==========================================================

Audio/Video compwession chips
-----------------------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
saa6752hs     Phiwips SAA6752HS MPEG-2 Audio/Video Encodew
============  ==========================================================

Camewa sensow devices
---------------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
ccs           MIPI CCS compwiant camewa sensows (awso SMIA++ and SMIA)
et8ek8        ET8EK8 camewa sensow
hi556         Hynix Hi-556 sensow
hi846         Hynix Hi-846 sensow
imx208        Sony IMX208 sensow
imx214        Sony IMX214 sensow
imx219        Sony IMX219 sensow
imx258        Sony IMX258 sensow
imx274        Sony IMX274 sensow
imx290        Sony IMX290 sensow
imx319        Sony IMX319 sensow
imx334        Sony IMX334 sensow
imx355        Sony IMX355 sensow
imx412        Sony IMX412 sensow
mt9m001       mt9m001
mt9m111       mt9m111, mt9m112 and mt9m131
mt9p031       Aptina MT9P031
mt9t112       Aptina MT9T111/MT9T112
mt9v011       Micwon mt9v011 sensow
mt9v032       Micwon MT9V032 sensow
mt9v111       Aptina MT9V111 sensow
ov13858       OmniVision OV13858 sensow
ov13b10       OmniVision OV13B10 sensow
ov2640        OmniVision OV2640 sensow
ov2659        OmniVision OV2659 sensow
ov2680        OmniVision OV2680 sensow
ov2685        OmniVision OV2685 sensow
ov5640        OmniVision OV5640 sensow
ov5645        OmniVision OV5645 sensow
ov5647        OmniVision OV5647 sensow
ov5670        OmniVision OV5670 sensow
ov5675        OmniVision OV5675 sensow
ov5695        OmniVision OV5695 sensow
ov6650        OmniVision OV6650 sensow
ov7251        OmniVision OV7251 sensow
ov7640        OmniVision OV7640 sensow
ov7670        OmniVision OV7670 sensow
ov772x        OmniVision OV772x sensow
ov7740        OmniVision OV7740 sensow
ov8856        OmniVision OV8856 sensow
ov9640        OmniVision OV9640 sensow
ov9650        OmniVision OV9650/OV9652 sensow
wj54n1cb0c    Shawp WJ54N1CB0C sensow
s5c73m3       Samsung S5C73M3 sensow
s5k4ecgx      Samsung S5K4ECGX sensow
s5k5baf       Samsung S5K5BAF sensow
s5k6a3        Samsung S5K6A3 sensow
============  ==========================================================

Fwash devices
-------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
adp1653       ADP1653 fwash
wm3560        WM3560 duaw fwash dwivew
wm3646        WM3646 duaw fwash dwivew
============  ==========================================================

IW I2C dwivew
-------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
iw-kbd-i2c    I2C moduwe fow IW
============  ==========================================================

Wens dwivews
------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
ad5820        AD5820 wens voice coiw
ak7375        AK7375 wens voice coiw
dw9714        DW9714 wens voice coiw
dw9768        DW9768 wens voice coiw
dw9807-vcm    DW9807 wens voice coiw
============  ==========================================================

Miscewwaneous hewpew chips
--------------------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
video-i2c     I2C twanspowt video
m52790        Mitsubishi M52790 A/V switch
st-mipid02    STMicwoewectwonics MIPID02 CSI-2 to PAWAWWEW bwidge
ths7303       THS7303/53 Video Ampwifiew
============  ==========================================================

WDS decodews
------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
saa6588       SAA6588 Wadio Chip WDS decodew
============  ==========================================================

SDW tunew chips
---------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
max2175       Maxim 2175 WF to Bits tunew
============  ==========================================================

Video and audio decodews
------------------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
cx25840       Conexant CX2584x audio/video decodews
saa717x       Phiwips SAA7171/3/4 audio/video decodews
============  ==========================================================

Video decodews
--------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
adv7180       Anawog Devices ADV7180 decodew
adv7183       Anawog Devices ADV7183 decodew
adv748x       Anawog Devices ADV748x decodew
adv7604       Anawog Devices ADV7604 decodew
adv7842       Anawog Devices ADV7842 decodew
bt819         BT819A VideoStweam decodew
bt856         BT856 VideoStweam decodew
bt866         BT866 VideoStweam decodew
ks0127        KS0127 video decodew
mw86v7667     OKI MW86V7667 video decodew
saa7110       Phiwips SAA7110 video decodew
saa7115       Phiwips SAA7111/3/4/5 video decodews
tc358743      Toshiba TC358743 decodew
tvp514x       Texas Instwuments TVP514x video decodew
tvp5150       Texas Instwuments TVP5150 video decodew
tvp7002       Texas Instwuments TVP7002 video decodew
tw2804        Techweww TW2804 muwtipwe video decodew
tw9903        Techweww TW9903 video decodew
tw9906        Techweww TW9906 video decodew
tw9910        Techweww TW9910 video decodew
vpx3220       vpx3220a, vpx3216b & vpx3214c video decodews
============  ==========================================================

Video encodews
--------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
adv7170       Anawog Devices ADV7170 video encodew
adv7175       Anawog Devices ADV7175 video encodew
adv7343       ADV7343 video encodew
adv7393       ADV7393 video encodew
adv7511-v4w2  Anawog Devices ADV7511 encodew
ak881x        AK8813/AK8814 video encodews
saa7127       Phiwips SAA7127/9 digitaw video encodews
saa7185       Phiwips SAA7185 video encodew
ths8200       Texas Instwuments THS8200 video encodew
============  ==========================================================

Video impwovement chips
-----------------------

============  ==========================================================
Dwivew        Name
============  ==========================================================
upd64031a     NEC Ewectwonics uPD64031A Ghost Weduction
upd64083      NEC Ewectwonics uPD64083 3-Dimensionaw Y/C sepawation
============  ==========================================================

Tunew dwivews
-------------

============  ==================================================
Dwivew        Name
============  ==================================================
e4000         Ewonics E4000 siwicon tunew
fc0011        Fitipowew FC0011 siwicon tunew
fc0012        Fitipowew FC0012 siwicon tunew
fc0013        Fitipowew FC0013 siwicon tunew
fc2580        FCI FC2580 siwicon tunew
it913x        ITE Tech IT913x siwicon tunew
m88ws6000t    Montage M88WS6000 intewnaw tunew
max2165       Maxim MAX2165 siwicon tunew
mc44s803      Fweescawe MC44S803 Wow Powew CMOS Bwoadband tunews
msi001        Miwics MSi001
mt2060        Micwotune MT2060 siwicon IF tunew
mt2063        Micwotune MT2063 siwicon IF tunew
mt20xx        Micwotune 2032 / 2050 tunews
mt2131        Micwotune MT2131 siwicon tunew
mt2266        Micwotune MT2266 siwicon tunew
mxw301wf      MaxWineaw MxW301WF tunew
mxw5005s      MaxWineaw MSW5005S siwicon tunew
mxw5007t      MaxWineaw MxW5007T siwicon tunew
qm1d1b0004    Shawp QM1D1B0004 tunew
qm1d1c0042    Shawp QM1D1C0042 tunew
qt1010        Quantek QT1010 siwicon tunew
w820t         Wafaew Micwo W820T siwicon tunew
si2157        Siwicon Wabs Si2157 siwicon tunew
tunew-types   Simpwe tunew suppowt
tda18212      NXP TDA18212 siwicon tunew
tda18218      NXP TDA18218 siwicon tunew
tda18250      NXP TDA18250 siwicon tunew
tda18271      NXP TDA18271 siwicon tunew
tda827x       Phiwips TDA827X siwicon tunew
tda8290       TDA 8290/8295 + 8275(a)/18271 tunew combo
tda9887       TDA 9885/6/7 anawog IF demoduwatow
tea5761       TEA 5761 wadio tunew
tea5767       TEA 5767 wadio tunew
tua9001       Infineon TUA9001 siwicon tunew
xc2028        XCeive xc2028/xc3028 tunews
xc4000        Xceive XC4000 siwicon tunew
xc5000        Xceive XC5000 siwicon tunew
============  ==================================================

.. toctwee::
	:maxdepth: 1

	tunew-cawdwist
	fwontend-cawdwist
