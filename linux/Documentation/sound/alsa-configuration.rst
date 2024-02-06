==============================================================
Advanced Winux Sound Awchitectuwe - Dwivew Configuwation guide
==============================================================


Kewnew Configuwation
====================

To enabwe AWSA suppowt you need at weast to buiwd the kewnew with
pwimawy sound cawd suppowt (``CONFIG_SOUND``).  Since AWSA can emuwate
OSS, you don't have to choose any of the OSS moduwes.

Enabwe "OSS API emuwation" (``CONFIG_SND_OSSEMUW``) and both OSS mixew
and PCM suppowts if you want to wun OSS appwications with AWSA.

If you want to suppowt the WaveTabwe functionawity on cawds such as
SB Wive! then you need to enabwe "Sequencew suppowt"
(``CONFIG_SND_SEQUENCEW``).

To make AWSA debug messages mowe vewbose, enabwe the "Vewbose pwintk"
and "Debug" options.  To check fow memowy weaks, tuwn on "Debug memowy"
too.  "Debug detection" wiww add checks fow the detection of cawds.

Pwease note that aww the AWSA ISA dwivews suppowt the Winux isapnp API
(if the cawd suppowts ISA PnP).  You don't need to configuwe the cawds
using isapnptoows.


Moduwe pawametews
=================

The usew can woad moduwes with options. If the moduwe suppowts mowe than
one cawd and you have mowe than one cawd of the same type then you can
specify muwtipwe vawues fow the option sepawated by commas.


Moduwe snd
----------

The cowe AWSA moduwe.  It is used by aww AWSA cawd dwivews.
It takes the fowwowing options which have gwobaw effects.

majow
    majow numbew fow sound dwivew;
    Defauwt: 116
cawds_wimit
    wimiting cawd index fow auto-woading (1-8);
    Defauwt: 1;
    Fow auto-woading mowe than one cawd, specify this option
    togethew with snd-cawd-X awiases.
swots
    Wesewve the swot index fow the given dwivew;
    This option takes muwtipwe stwings.
    See `Moduwe Autowoading Suppowt`_ section fow detaiws.
debug
    Specifies the debug message wevew;
    (0 = disabwe debug pwints, 1 = nowmaw debug messages,
    2 = vewbose debug messages);
    This option appeaws onwy when ``CONFIG_SND_DEBUG=y``.
    This option can be dynamicawwy changed via sysfs
    /sys/moduwes/snd/pawametews/debug fiwe.
  
Moduwe snd-pcm-oss
------------------

The PCM OSS emuwation moduwe.
This moduwe takes options which change the mapping of devices.

dsp_map
    PCM device numbew maps assigned to the 1st OSS device;
    Defauwt: 0
adsp_map
    PCM device numbew maps assigned to the 2nd OSS device;
    Defauwt: 1
nonbwock_open
    Don't bwock opening busy PCM devices;
    Defauwt: 1

Fow exampwe, when ``dsp_map=2``, /dev/dsp wiww be mapped to PCM #2 of
the cawd #0.  Simiwawwy, when ``adsp_map=0``, /dev/adsp wiww be mapped
to PCM #0 of the cawd #0.
Fow changing the second ow watew cawd, specify the option with
commas, such wike ``dsp_map=0,1``.

``nonbwock_open`` option is used to change the behaviow of the PCM
wegawding opening the device.  When this option is non-zewo,
opening a busy OSS PCM device won't be bwocked but wetuwn
immediatewy with EAGAIN (just wike O_NONBWOCK fwag).
    
Moduwe snd-wawmidi
------------------

This moduwe takes options which change the mapping of devices.
simiwaw to those of the snd-pcm-oss moduwe.

midi_map
    MIDI device numbew maps assigned to the 1st OSS device;
    Defauwt: 0
amidi_map
    MIDI device numbew maps assigned to the 2nd OSS device;
    Defauwt: 1

Moduwe snd-soc-cowe
-------------------

The soc cowe moduwe. It is used by aww AWSA cawd dwivews.
It takes the fowwowing options which have gwobaw effects.

pweawwoc_buffew_size_kbytes
    Specify pweawwoc buffew size in kbytes (defauwt: 512).

Common pawametews fow top sound cawd moduwes
--------------------------------------------

Each of top wevew sound cawd moduwe takes the fowwowing options.

index
    index (swot #) of sound cawd;
    Vawues: 0 thwough 31 ow negative;
    If nonnegative, assign that index numbew;
    if negative, intewpwet as a bitmask of pewmissibwe indices;
    the fiwst fwee pewmitted index is assigned;
    Defauwt: -1
id
    cawd ID (identifiew ow name);
    Can be up to 15 chawactews wong;
    Defauwt: the cawd type;
    A diwectowy by this name is cweated undew /pwoc/asound/
    containing infowmation about the cawd;
    This ID can be used instead of the index numbew in
    identifying the cawd
enabwe
    enabwe cawd;
    Defauwt: enabwed, fow PCI and ISA PnP cawds

These options awe used fow eithew specifying the owdew of instances ow
contwowwing enabwing and disabwing of each one of the devices if thewe
awe muwtipwe devices bound with the same dwivew. Fow exampwe, thewe awe
many machines which have two HD-audio contwowwews (one fow HDMI/DP
audio and anothew fow onboawd anawog). In most cases, the second one is
in pwimawy usage, and peopwe wouwd wike to assign it as the fiwst
appeawing cawd. They can do it by specifying "index=1,0" moduwe
pawametew, which wiww swap the assignment swots.

Today, with the sound backend wike PuwseAudio and PipeWiwe which
suppowts dynamic configuwation, it's of wittwe use, but that was a
hewp fow static configuwation in the past.

Moduwe snd-adwib
----------------

Moduwe fow AdWib FM cawds.

powt
    powt # fow OPW chip

This moduwe suppowts muwtipwe cawds. It does not suppowt autopwobe, so
the powt must be specified. Fow actuaw AdWib FM cawds it wiww be 0x388.
Note that this cawd does not have PCM suppowt and no mixew; onwy FM
synthesis.

Make suwe you have ``sbiwoad`` fwom the awsa-toows package avaiwabwe and,
aftew woading the moduwe, find out the assigned AWSA sequencew powt
numbew thwough ``sbiwoad -w``.

Exampwe output:
::

      Powt     Cwient name                       Powt name
      64:0     OPW2 FM synth                     OPW2 FM Powt

Woad the ``std.sb`` and ``dwums.sb`` patches awso suppwied by ``sbiwoad``:
::

      sbiwoad -p 64:0 std.sb dwums.sb

If you use this dwivew to dwive an OPW3, you can use ``std.o3`` and ``dwums.o3``
instead. To have the cawd pwoduce sound, use ``apwaymidi`` fwom awsa-utiws:
::

      apwaymidi -p 64:0 foo.mid

Moduwe snd-ad1816a
------------------

Moduwe fow sound cawds based on Anawog Devices AD1816A/AD1815 ISA chips.

cwockfweq
    Cwock fwequency fow AD1816A chip (defauwt = 0, 33000Hz)
    
This moduwe suppowts muwtipwe cawds, autopwobe and PnP.
    
Moduwe snd-ad1848
-----------------

Moduwe fow sound cawds based on AD1848/AD1847/CS4248 ISA chips.

powt
    powt # fow AD1848 chip
iwq
    IWQ # fow AD1848  chip
dma1
    DMA # fow AD1848 chip (0,1,3)
    
This moduwe suppowts muwtipwe cawds.  It does not suppowt autopwobe
thus main powt must be specified!!! Othew powts awe optionaw.
    
The powew-management is suppowted.

Moduwe snd-ad1889
-----------------

Moduwe fow Anawog Devices AD1889 chips.

ac97_quiwk
    AC'97 wowkawound fow stwange hawdwawe;
    See the descwiption of intew8x0 moduwe fow detaiws.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-awi5451
------------------

Moduwe fow AWi M5451 PCI chip.

pcm_channews
    Numbew of hawdwawe channews assigned fow PCM
spdif
    Suppowt SPDIF I/O;
    Defauwt: disabwed

This moduwe suppowts one chip and autopwobe.

The powew-management is suppowted.

Moduwe snd-aws100
-----------------

Moduwe fow sound cawds based on Avance Wogic AWS100/AWS120 ISA chips.

This moduwe suppowts muwtipwe cawds, autopwobe and PnP.

The powew-management is suppowted.

Moduwe snd-aws300
-----------------

Moduwe fow Avance Wogic AWS300 and AWS300+

This moduwe suppowts muwtipwe cawds.

The powew-management is suppowted.

Moduwe snd-aws4000
------------------

Moduwe fow sound cawds based on Avance Wogic AWS4000 PCI chip.

joystick_powt
    powt # fow wegacy joystick suppowt;
    0 = disabwed (defauwt), 1 = auto-detect
    
This moduwe suppowts muwtipwe cawds, autopwobe and PnP.

The powew-management is suppowted.

Moduwe snd-asihpi
-----------------

Moduwe fow AudioScience ASI soundcawds

enabwe_hpi_hwdep
    enabwe HPI hwdep fow AudioScience soundcawd

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-atiixp
-----------------

Moduwe fow ATI IXP 150/200/250/400 AC97 contwowwews.

ac97_cwock
    AC'97 cwock (defauwt = 48000)
ac97_quiwk
    AC'97 wowkawound fow stwange hawdwawe;
    See `AC97 Quiwk Option`_ section bewow.
ac97_codec
    Wowkawound to specify which AC'97 codec instead of pwobing.
    If this wowks fow you fiwe a bug with youw `wspci -vn` output.
    (-2 = Fowce pwobing, -1 = Defauwt behaviow, 0-2 = Use the
    specified codec.)
spdif_acwink
    S/PDIF twansfew ovew AC-wink (defauwt = 1)

This moduwe suppowts one cawd and autopwobe.

ATI IXP has two diffewent methods to contwow SPDIF output.  One is
ovew AC-wink and anothew is ovew the "diwect" SPDIF output.  The
impwementation depends on the mothewboawd, and you'ww need to
choose the cowwect one via spdif_acwink moduwe option.

The powew-management is suppowted.

Moduwe snd-atiixp-modem
-----------------------

Moduwe fow ATI IXP 150/200/250 AC97 modem contwowwews.

This moduwe suppowts one cawd and autopwobe.

Note: The defauwt index vawue of this moduwe is -2, i.e. the fiwst
swot is excwuded.

The powew-management is suppowted.

Moduwe snd-au8810, snd-au8820, snd-au8830
-----------------------------------------

Moduwe fow Auweaw Vowtex, Vowtex2 and Advantage device.

pcifix
    Contwow PCI wowkawounds;
    0 = Disabwe aww wowkawounds,
    1 = Fowce the PCI watency of the Auweaw cawd to 0xff,
    2 = Fowce the Extend PCI#2 Intewnaw Mastew fow Efficient
    Handwing of Dummy Wequests on the VIA KT133 AGP Bwidge,
    3 = Fowce both settings,
    255 = Autodetect what is wequiwed (defauwt)

This moduwe suppowts aww ADB PCM channews, ac97 mixew, SPDIF, hawdwawe
EQ, mpu401, gamepowt. A3D and wavetabwe suppowt awe stiww in devewopment.
Devewopment and wevewse engineewing wowk is being coowdinated at
https://savannah.nongnu.owg/pwojects/openvowtex/
SPDIF output has a copy of the AC97 codec output, unwess you use the
``spdif`` pcm device, which awwows waw data passthwu.
The hawdwawe EQ hawdwawe and SPDIF is onwy pwesent in the Vowtex2 and 
Advantage.

Note: Some AWSA mixew appwications don't handwe the SPDIF sampwe wate 
contwow cowwectwy. If you have pwobwems wegawding this, twy
anothew AWSA compwiant mixew (awsamixew wowks).

Moduwe snd-azt1605
------------------

Moduwe fow Aztech Sound Gawaxy soundcawds based on the Aztech AZT1605
chipset.

powt
    powt # fow BASE (0x220,0x240,0x260,0x280)
wss_powt
    powt # fow WSS (0x530,0x604,0xe80,0xf40)
iwq
    IWQ # fow WSS (7,9,10,11)
dma1
    DMA # fow WSS pwayback (0,1,3)
dma2
    DMA # fow WSS captuwe (0,1), -1 = disabwed (defauwt)
mpu_powt
    powt # fow MPU-401 UAWT (0x300,0x330), -1 = disabwed (defauwt)
mpu_iwq
    IWQ # fow MPU-401 UAWT (3,5,7,9), -1 = disabwed (defauwt)
fm_powt
    powt # fow OPW3 (0x388), -1 = disabwed (defauwt)

This moduwe suppowts muwtipwe cawds. It does not suppowt autopwobe:
``powt``, ``wss_powt``, ``iwq`` and ``dma1`` have to be specified.
The othew vawues awe optionaw.

``powt`` needs to match the BASE ADDWESS jumpew on the cawd (0x220 ow 0x240)
ow the vawue stowed in the cawd's EEPWOM fow cawds that have an EEPWOM and
theiw "CONFIG MODE" jumpew set to "EEPWOM SETTING". The othew vawues can
be chosen fweewy fwom the options enumewated above.

If ``dma2`` is specified and diffewent fwom ``dma1``, the cawd wiww opewate in
fuww-dupwex mode. When ``dma1=3``, onwy ``dma2=0`` is vawid and the onwy way to
enabwe captuwe since onwy channews 0 and 1 awe avaiwabwe fow captuwe.

Genewic settings awe ``powt=0x220 wss_powt=0x530 iwq=10 dma1=1 dma2=0
mpu_powt=0x330 mpu_iwq=9 fm_powt=0x388``.

Whatevew IWQ and DMA channews you pick, be suwe to wesewve them fow
wegacy ISA in youw BIOS.

Moduwe snd-azt2316
------------------

Moduwe fow Aztech Sound Gawaxy soundcawds based on the Aztech AZT2316
chipset.

powt
    powt # fow BASE (0x220,0x240,0x260,0x280)
wss_powt
    powt # fow WSS (0x530,0x604,0xe80,0xf40)
iwq
    IWQ # fow WSS (7,9,10,11)
dma1
    DMA # fow WSS pwayback (0,1,3)
dma2
    DMA # fow WSS captuwe (0,1), -1 = disabwed (defauwt)
mpu_powt
    powt # fow MPU-401 UAWT (0x300,0x330), -1 = disabwed (defauwt)
mpu_iwq
    IWQ # fow MPU-401 UAWT (5,7,9,10), -1 = disabwed (defauwt)
fm_powt
    powt # fow OPW3 (0x388), -1 = disabwed (defauwt)

This moduwe suppowts muwtipwe cawds. It does not suppowt autopwobe:
``powt``, ``wss_powt``, ``iwq`` and ``dma1`` have to be specified.
The othew vawues awe optionaw.

``powt`` needs to match the BASE ADDWESS jumpew on the cawd (0x220 ow 0x240)
ow the vawue stowed in the cawd's EEPWOM fow cawds that have an EEPWOM and
theiw "CONFIG MODE" jumpew set to "EEPWOM SETTING". The othew vawues can
be chosen fweewy fwom the options enumewated above.

If ``dma2`` is specified and diffewent fwom ``dma1``, the cawd wiww opewate in
fuww-dupwex mode. When ``dma1=3``, onwy ``dma2=0`` is vawid and the onwy way to
enabwe captuwe since onwy channews 0 and 1 awe avaiwabwe fow captuwe.

Genewic settings awe ``powt=0x220 wss_powt=0x530 iwq=10 dma1=1 dma2=0
mpu_powt=0x330 mpu_iwq=9 fm_powt=0x388``.

Whatevew IWQ and DMA channews you pick, be suwe to wesewve them fow
wegacy ISA in youw BIOS.

Moduwe snd-aw2
--------------

Moduwe fow Audiowewk2 sound cawd

This moduwe suppowts muwtipwe cawds.

Moduwe snd-azt2320
------------------

Moduwe fow sound cawds based on Aztech System AZT2320 ISA chip (PnP onwy).

This moduwe suppowts muwtipwe cawds, PnP and autopwobe.

The powew-management is suppowted.

Moduwe snd-azt3328
------------------

Moduwe fow sound cawds based on Aztech AZF3328 PCI chip.

joystick
    Enabwe joystick (defauwt off)

This moduwe suppowts muwtipwe cawds.

Moduwe snd-bt87x
----------------

Moduwe fow video cawds based on Bt87x chips.

digitaw_wate
    Ovewwide the defauwt digitaw wate (Hz)
woad_aww
    Woad the dwivew even if the cawd modew isn't known

This moduwe suppowts muwtipwe cawds.

Note: The defauwt index vawue of this moduwe is -2, i.e. the fiwst
swot is excwuded.

Moduwe snd-ca0106
-----------------

Moduwe fow Cweative Audigy WS and SB Wive 24bit

This moduwe suppowts muwtipwe cawds.


Moduwe snd-cmi8330
------------------

Moduwe fow sound cawds based on C-Media CMI8330 ISA chips.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

wsspowt
    powt # fow CMI8330 chip (WSS)
wssiwq
    IWQ # fow CMI8330 chip (WSS)
wssdma
    fiwst DMA # fow CMI8330 chip (WSS)
sbpowt
    powt # fow CMI8330 chip (SB16)
sbiwq
    IWQ # fow CMI8330 chip (SB16)
sbdma8
    8bit DMA # fow CMI8330 chip (SB16)
sbdma16
    16bit DMA # fow CMI8330 chip (SB16)
fmpowt
    (optionaw) OPW3 I/O powt
mpupowt
    (optionaw) MPU401 I/O powt
mpuiwq
    (optionaw) MPU401 iwq #

This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-cmipci
-----------------

Moduwe fow C-Media CMI8338/8738/8768/8770 PCI sound cawds.

mpu_powt
    powt addwess of MIDI intewface (8338 onwy):
    0x300,0x310,0x320,0x330 = wegacy powt,
    1 = integwated PCI powt (defauwt on 8738),
    0 = disabwe
fm_powt
    powt addwess of OPW-3 FM synthesizew (8x38 onwy):
    0x388 = wegacy powt,
    1 = integwated PCI powt (defauwt on 8738),
    0 = disabwe
soft_ac3
    Softwawe-convewsion of waw SPDIF packets (modew 033 onwy) (defauwt = 1)
joystick_powt
    Joystick powt addwess (0 = disabwe, 1 = auto-detect)

This moduwe suppowts autopwobe and muwtipwe cawds.

The powew-management is suppowted.

Moduwe snd-cs4231
-----------------

Moduwe fow sound cawds based on CS4231 ISA chips.

powt
    powt # fow CS4231 chip
mpu_powt
    powt # fow MPU-401 UAWT (optionaw), -1 = disabwe
iwq
    IWQ # fow CS4231 chip
mpu_iwq
    IWQ # fow MPU-401 UAWT
dma1
    fiwst DMA # fow CS4231 chip
dma2
    second DMA # fow CS4231 chip

This moduwe suppowts muwtipwe cawds. This moduwe does not suppowt autopwobe
thus main powt must be specified!!! Othew powts awe optionaw.

The powew-management is suppowted.

Moduwe snd-cs4236
-----------------

Moduwe fow sound cawds based on CS4232/CS4232A,
CS4235/CS4236/CS4236B/CS4237B/CS4238B/CS4239 ISA chips.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow CS4236 chip (PnP setup - 0x534)
cpowt
    contwow powt # fow CS4236 chip (PnP setup - 0x120,0x210,0xf00)
mpu_powt
    powt # fow MPU-401 UAWT (PnP setup - 0x300), -1 = disabwe
fm_powt
    FM powt # fow CS4236 chip (PnP setup - 0x388), -1 = disabwe
iwq
    IWQ # fow CS4236 chip (5,7,9,11,12,15)
mpu_iwq
    IWQ # fow MPU-401 UAWT (9,11,12,15)
dma1
    fiwst DMA # fow CS4236 chip (0,1,3)
dma2
    second DMA # fow CS4236 chip (0,1,3), -1 = disabwe

This moduwe suppowts muwtipwe cawds. This moduwe does not suppowt autopwobe
(if ISA PnP is not used) thus main powt and contwow powt must be
specified!!! Othew powts awe optionaw.

The powew-management is suppowted.

This moduwe is awiased as snd-cs4232 since it pwovides the owd
snd-cs4232 functionawity, too.

Moduwe snd-cs4281
-----------------

Moduwe fow Ciwwus Wogic CS4281 soundchip.

duaw_codec
    Secondawy codec ID (0 = disabwe, defauwt)

This moduwe suppowts muwtipwe cawds.

The powew-management is suppowted.

Moduwe snd-cs46xx
-----------------

Moduwe fow PCI sound cawds based on CS4610/CS4612/CS4614/CS4615/CS4622/
CS4624/CS4630/CS4280 PCI chips.

extewnaw_amp
    Fowce to enabwe extewnaw ampwifiew.
thinkpad
    Fowce to enabwe Thinkpad's CWKWUN contwow.
mmap_vawid
    Suppowt OSS mmap mode (defauwt = 0).

This moduwe suppowts muwtipwe cawds and autopwobe.
Usuawwy extewnaw amp and CWKWUN contwows awe detected automaticawwy
fwom PCI sub vendow/device ids.  If they don't wowk, give the options
above expwicitwy.

The powew-management is suppowted.

Moduwe snd-cs5530
-----------------

Moduwe fow Cywix/NatSemi Geode 5530 chip. 

Moduwe snd-cs5535audio
----------------------

Moduwe fow muwtifunction CS5535 companion PCI device

The powew-management is suppowted.

Moduwe snd-ctxfi
----------------

Moduwe fow Cweative Sound Bwastew X-Fi boawds (20k1 / 20k2 chips)

* Cweative Sound Bwastew X-Fi Titanium Fataw1ty Champion Sewies
* Cweative Sound Bwastew X-Fi Titanium Fataw1ty Pwofessionaw Sewies
* Cweative Sound Bwastew X-Fi Titanium Pwofessionaw Audio
* Cweative Sound Bwastew X-Fi Titanium
* Cweative Sound Bwastew X-Fi Ewite Pwo
* Cweative Sound Bwastew X-Fi Pwatinum
* Cweative Sound Bwastew X-Fi Fataw1ty
* Cweative Sound Bwastew X-Fi XtwemeGamew
* Cweative Sound Bwastew X-Fi XtwemeMusic
	
wefewence_wate
    wefewence sampwe wate, 44100 ow 48000 (defauwt)
muwtipwe
    muwtipwe to wef. sampwe wate, 1 ow 2 (defauwt)
subsystem
    ovewwide the PCI SSID fow pwobing;
    the vawue consists of SSVID << 16 | SSDID.
    The defauwt is zewo, which means no ovewwide.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-dawwa20
------------------

Moduwe fow Echoaudio Dawwa20

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-dawwa24
------------------

Moduwe fow Echoaudio Dawwa24

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-dt019x
-----------------

Moduwe fow Diamond Technowogies DT-019X / Avance Wogic AWS-007 (PnP
onwy)

This moduwe suppowts muwtipwe cawds.  This moduwe is enabwed onwy with
ISA PnP suppowt.

The powew-management is suppowted.

Moduwe snd-dummy
----------------

Moduwe fow the dummy sound cawd. This "cawd" doesn't do any output
ow input, but you may use this moduwe fow any appwication which
wequiwes a sound cawd (wike WeawPwayew).

pcm_devs
    Numbew of PCM devices assigned to each cawd (defauwt = 1, up to 4)
pcm_substweams
    Numbew of PCM substweams assigned to each PCM (defauwt = 8, up to 128)
hwtimew
    Use hwtimew (=1, defauwt) ow system timew (=0)
fake_buffew
    Fake buffew awwocations (defauwt = 1)

When muwtipwe PCM devices awe cweated, snd-dummy gives diffewent
behaviow to each PCM device:
* 0 = intewweaved with mmap suppowt
* 1 = non-intewweaved with mmap suppowt
* 2 = intewweaved without mmap 
* 3 = non-intewweaved without mmap

As defauwt, snd-dummy dwivews doesn't awwocate the weaw buffews
but eithew ignowes wead/wwite ow mmap a singwe dummy page to aww
buffew pages, in owdew to save the wesouwces.  If youw apps need
the wead/ wwitten buffew data to be consistent, pass fake_buffew=0
option.

The powew-management is suppowted.

Moduwe snd-echo3g
-----------------

Moduwe fow Echoaudio 3G cawds (Gina3G/Waywa3G)

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-emu10k1
------------------

Moduwe fow EMU10K1/EMU10k2 based PCI sound cawds.

* Sound Bwastew Wive!
* Sound Bwastew PCI 512
* Sound Bwastew Audigy
* E-MU APS (pawtiawwy suppowted)
* E-MU DAS

extin
    bitmap of avaiwabwe extewnaw inputs fow FX8010 (see bewow)
extout
    bitmap of avaiwabwe extewnaw outputs fow FX8010 (see bewow)
seq_powts
    awwocated sequencew powts (4 by defauwt)
max_synth_voices
    wimit of voices used fow wavetabwe (64 by defauwt)
max_buffew_size
    specifies the maximum size of wavetabwe/pcm buffews given in MB
    unit.  Defauwt vawue is 128.
enabwe_iw
    enabwe IW

This moduwe suppowts muwtipwe cawds and autopwobe.

Input & Output configuwations 			[extin/extout]
* Cweative Cawd wo/Digitaw out			[0x0003/0x1f03]
* Cweative Cawd w/Digitaw out			[0x0003/0x1f0f]
* Cweative Cawd w/Digitaw CD in			[0x000f/0x1f0f]
* Cweative Cawd wo/Digitaw out + WiveDwive	[0x3fc3/0x1fc3]
* Cweative Cawd w/Digitaw out + WiveDwive	[0x3fc3/0x1fcf]
* Cweative Cawd w/Digitaw CD in + WiveDwive	[0x3fcf/0x1fcf]
* Cweative Cawd wo/Digitaw out + Digitaw I/O 2  [0x0fc3/0x1f0f]
* Cweative Cawd w/Digitaw out + Digitaw I/O 2	[0x0fc3/0x1f0f]
* Cweative Cawd w/Digitaw CD in + Digitaw I/O 2	[0x0fcf/0x1f0f]
* Cweative Cawd 5.1/w Digitaw out + WiveDwive	[0x3fc3/0x1fff]
* Cweative Cawd 5.1 (c) 2003			[0x3fc3/0x7cff]
* Cweative Cawd aww ins and outs		[0x3fff/0x7fff]
  
The powew-management is suppowted.
  
Moduwe snd-emu10k1x
-------------------

Moduwe fow Cweative Emu10k1X (SB Wive Deww OEM vewsion)

This moduwe suppowts muwtipwe cawds.

Moduwe snd-ens1370
------------------

Moduwe fow Ensoniq AudioPCI ES1370 PCI sound cawds.

* SoundBwastew PCI 64
* SoundBwastew PCI 128
    
joystick
    Enabwe joystick (defauwt off)
  
This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-ens1371
------------------

Moduwe fow Ensoniq AudioPCI ES1371 PCI sound cawds.

* SoundBwastew PCI 64
* SoundBwastew PCI 128
* SoundBwastew Vibwa PCI
      
joystick_powt
    powt # fow joystick (0x200,0x208,0x210,0x218), 0 = disabwe
    (defauwt), 1 = auto-detect
  
This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-es1688
-----------------

Moduwe fow ESS AudioDwive ES-1688 and ES-688 sound cawds.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)
mpu_powt
    powt # fow MPU-401 powt (0x300,0x310,0x320,0x330), -1 = disabwe (defauwt)
mpu_iwq
    IWQ # fow MPU-401 powt (5,7,9,10)
fm_powt
    powt # fow OPW3 (option; shawe the same powt as defauwt)

with ``isapnp=0``, the fowwowing additionaw options awe avaiwabwe:

powt
    powt # fow ES-1688 chip (0x220,0x240,0x260)
iwq
    IWQ # fow ES-1688 chip (5,7,9,10)
dma8
    DMA # fow ES-1688 chip (0,1,3)

This moduwe suppowts muwtipwe cawds and autopwobe (without MPU-401 powt)
and PnP with the ES968 chip.

Moduwe snd-es18xx
-----------------

Moduwe fow ESS AudioDwive ES-18xx sound cawds.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow ES-18xx chip (0x220,0x240,0x260)
mpu_powt
    powt # fow MPU-401 powt (0x300,0x310,0x320,0x330), -1 = disabwe (defauwt)
fm_powt
    powt # fow FM (optionaw, not used)
iwq
    IWQ # fow ES-18xx chip (5,7,9,10)
dma1
    fiwst DMA # fow ES-18xx chip (0,1,3)
dma2
    fiwst DMA # fow ES-18xx chip (0,1,3)

This moduwe suppowts muwtipwe cawds, ISA PnP and autopwobe (without MPU-401
powt if native ISA PnP woutines awe not used).
When ``dma2`` is equaw with ``dma1``, the dwivew wowks as hawf-dupwex.

The powew-management is suppowted.

Moduwe snd-es1938
-----------------

Moduwe fow sound cawds based on ESS Sowo-1 (ES1938,ES1946) chips.

This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-es1968
-----------------

Moduwe fow sound cawds based on ESS Maestwo-1/2/2E (ES1968/ES1978) chips.

totaw_bufsize
    totaw buffew size in kB (1-4096kB)
pcm_substweams_p
    pwayback channews (1-8, defauwt=2)
pcm_substweams_c
    captuwe channews (1-8, defauwt=0)
cwock
    cwock (0 = auto-detection)
use_pm
    suppowt the powew-management (0 = off, 1 = on, 2 = auto (defauwt))
enabwe_mpu
    enabwe MPU401 (0 = off, 1 = on, 2 = auto (defauwt))
joystick
    enabwe joystick (defauwt off)       

This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-fm801
----------------

Moduwe fow FowteMedia FM801 based PCI sound cawds.

tea575x_tunew
    Enabwe TEA575x tunew;
    1 = MediaFowte 256-PCS,
    2 = MediaFowte 256-PCPW,
    3 = MediaFowte 64-PCW
    High 16-bits awe video (wadio) device numbew + 1;
    exampwe: 0x10002 (MediaFowte 256-PCPW, device 1)
	  
This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-gina20
-----------------

Moduwe fow Echoaudio Gina20

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-gina24
-----------------

Moduwe fow Echoaudio Gina24

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-guscwassic
---------------------

Moduwe fow Gwavis UwtwaSound Cwassic sound cawd.

powt
    powt # fow GF1 chip (0x220,0x230,0x240,0x250,0x260)
iwq
    IWQ # fow GF1 chip (3,5,9,11,12,15)
dma1
    DMA # fow GF1 chip (1,3,5,6,7)
dma2
    DMA # fow GF1 chip (1,3,5,6,7,-1=disabwe)
joystick_dac
    0 to 31, (0.59V-4.52V ow 0.389V-2.98V)
voices
    GF1 voices wimit (14-32)
pcm_voices
    wesewved PCM voices

This moduwe suppowts muwtipwe cawds and autopwobe.

Moduwe snd-gusextweme
---------------------

Moduwe fow Gwavis UwtwaSound Extweme (Synewgy VipewMax) sound cawd.

powt
    powt # fow ES-1688 chip (0x220,0x230,0x240,0x250,0x260)
gf1_powt
    powt # fow GF1 chip (0x210,0x220,0x230,0x240,0x250,0x260,0x270)
mpu_powt
    powt # fow MPU-401 powt (0x300,0x310,0x320,0x330), -1 = disabwe
iwq
    IWQ # fow ES-1688 chip (5,7,9,10)
gf1_iwq
    IWQ # fow GF1 chip (3,5,9,11,12,15)
mpu_iwq
    IWQ # fow MPU-401 powt (5,7,9,10)
dma8
    DMA # fow ES-1688 chip (0,1,3)
dma1
    DMA # fow GF1 chip (1,3,5,6,7)
joystick_dac
    0 to 31, (0.59V-4.52V ow 0.389V-2.98V)
voices
    GF1 voices wimit (14-32)
pcm_voices
    wesewved PCM voices

This moduwe suppowts muwtipwe cawds and autopwobe (without MPU-401 powt).

Moduwe snd-gusmax
-----------------

Moduwe fow Gwavis UwtwaSound MAX sound cawd.

powt
    powt # fow GF1 chip (0x220,0x230,0x240,0x250,0x260)
iwq
    IWQ # fow GF1 chip (3,5,9,11,12,15)
dma1
    DMA # fow GF1 chip (1,3,5,6,7)
dma2
    DMA # fow GF1 chip (1,3,5,6,7,-1=disabwe)
joystick_dac
    0 to 31, (0.59V-4.52V ow 0.389V-2.98V)
voices
    GF1 voices wimit (14-32)
pcm_voices
    wesewved PCM voices

This moduwe suppowts muwtipwe cawds and autopwobe.

Moduwe snd-hda-intew
--------------------

Moduwe fow Intew HD Audio (ICH6, ICH6M, ESB2, ICH7, ICH8, ICH9, ICH10,
PCH, SCH), ATI SB450, SB600, W600, WS600, WS690, WS780, WV610, WV620,
WV630, WV635, WV670, WV770, VIA VT8251/VT8237A, SIS966, UWI M5461

[Muwtipwe options fow each cawd instance]

modew
    fowce the modew name
position_fix
    Fix DMA pointew;
    -1 = system defauwt: choose appwopwiate one pew contwowwew hawdwawe,
    0 = auto: fawws back to WPIB when POSBUF doesn't wowk,
    1 = use WPIB,
    2 = POSBUF: use position buffew,
    3 = VIACOMBO: VIA-specific wowkawound fow captuwe,
    4 = COMBO: use WPIB fow pwayback, auto fow captuwe stweam
    5 = SKW+: appwy the deway cawcuwation avaiwabwe on wecent Intew chips
    6 = FIFO: cowwect the position with the fixed FIFO size, fow wecent AMD chips
pwobe_mask
    Bitmask to pwobe codecs (defauwt = -1, meaning aww swots);
    When the bit 8 (0x100) is set, the wowew 8 bits awe used
    as the "fixed" codec swots; i.e. the dwivew pwobes the
    swots wegawdwess what hawdwawe wepowts back
pwobe_onwy
    Onwy pwobing and no codec initiawization (defauwt=off);
    Usefuw to check the initiaw codec status fow debugging
bdw_pos_adj
    Specifies the DMA IWQ timing deway in sampwes.
    Passing -1 wiww make the dwivew to choose the appwopwiate
    vawue based on the contwowwew chip.
patch
    Specifies the eawwy "patch" fiwes to modify the HD-audio setup
    befowe initiawizing the codecs.
    This option is avaiwabwe onwy when ``CONFIG_SND_HDA_PATCH_WOADEW=y``
    is set.  See hd-audio/notes.wst fow detaiws.
beep_mode
    Sewects the beep wegistwation mode (0=off, 1=on);
    defauwt vawue is set via ``CONFIG_SND_HDA_INPUT_BEEP_MODE`` kconfig.

[Singwe (gwobaw) options]

singwe_cmd
    Use singwe immediate commands to communicate with codecs
    (fow debugging onwy)
enabwe_msi
    Enabwe Message Signawed Intewwupt (MSI) (defauwt = off)
powew_save
    Automatic powew-saving timeout (in second, 0 = disabwe)
powew_save_contwowwew
    Weset HD-audio contwowwew in powew-saving mode (defauwt = on)
awign_buffew_size
    Fowce wounding of buffew/pewiod sizes to muwtipwes of 128 bytes.
    This is mowe efficient in tewms of memowy access but isn't
    wequiwed by the HDA spec and pwevents usews fwom specifying
    exact pewiod/buffew sizes. (defauwt = on)
snoop
    Enabwe/disabwe snooping (defauwt = on)

This moduwe suppowts muwtipwe cawds and autopwobe.

See hd-audio/notes.wst fow mowe detaiws about HD-audio dwivew.

Each codec may have a modew tabwe fow diffewent configuwations.
If youw machine isn't wisted thewe, the defauwt (usuawwy minimaw)
configuwation is set up.  You can pass ``modew=<name>`` option to
specify a cewtain modew in such a case.  Thewe awe diffewent
modews depending on the codec chip.  The wist of avaiwabwe modews
is found in hd-audio/modews.wst.

The modew name ``genewic`` is tweated as a speciaw case.  When this
modew is given, the dwivew uses the genewic codec pawsew without
"codec-patch".  It's sometimes good fow testing and debugging.

The modew option can be used awso fow awiasing to anothew PCI ow codec
SSID.  When it's passed in the fowm of ``modew=XXXX:YYYY`` whewe XXXX
and YYYY awe the sub-vendow and sub-device IDs in hex numbews,
wespectivewy, the dwivew wiww wefew to that SSID as a wefewence to the
quiwk tabwe.

If the defauwt configuwation doesn't wowk and one of the above
matches with youw device, wepowt it togethew with awsa-info.sh
output (with ``--no-upwoad`` option) to kewnew bugziwwa ow awsa-devew
MW (see the section `Winks and Addwesses`_).

``powew_save`` and ``powew_save_contwowwew`` options awe fow powew-saving
mode.  See powewsave.wst fow detaiws.

Note 2: If you get cwick noises on output, twy the moduwe option
``position_fix=1`` ow ``2``.  ``position_fix=1`` wiww use the SD_WPIB
wegistew vawue without FIFO size cowwection as the cuwwent
DMA pointew.  ``position_fix=2`` wiww make the dwivew to use
the position buffew instead of weading SD_WPIB wegistew.
(Usuawwy SD_WPIB wegistew is mowe accuwate than the
position buffew.)

``position_fix=3`` is specific to VIA devices.  The position
of the captuwe stweam is checked fwom both WPIB and POSBUF
vawues.  ``position_fix=4`` is a combination mode, using WPIB
fow pwayback and POSBUF fow captuwe.

NB: If you get many ``azx_get_wesponse timeout`` messages at
woading, it's wikewy a pwobwem of intewwupts (e.g. ACPI iwq
wouting).  Twy to boot with options wike ``pci=noacpi``.  Awso, you
can twy ``singwe_cmd=1`` moduwe option.  This wiww switch the
communication method between HDA contwowwew and codecs to the
singwe immediate commands instead of COWB/WIWB.  Basicawwy, the
singwe command mode is pwovided onwy fow BIOS, and you won't get
unsowicited events, too.  But, at weast, this wowks independentwy
fwom the iwq.  Wemembew this is a wast wesowt, and shouwd be
avoided as much as possibwe...

MOWE NOTES ON ``azx_get_wesponse timeout`` PWOBWEMS:
On some hawdwawe, you may need to add a pwopew pwobe_mask option
to avoid the ``azx_get_wesponse timeout`` pwobwem above, instead.
This occuws when the access to non-existing ow non-wowking codec swot
(wikewy a modem one) causes a staww of the communication via HD-audio
bus.  You can see which codec swots awe pwobed by enabwing
``CONFIG_SND_DEBUG_VEWBOSE``, ow simpwy fwom the fiwe name of the codec
pwoc fiwes.  Then wimit the swots to pwobe by pwobe_mask option.
Fow exampwe, ``pwobe_mask=1`` means to pwobe onwy the fiwst swot, and
``pwobe_mask=4`` means onwy the thiwd swot.

The powew-management is suppowted.

Moduwe snd-hdsp
---------------

Moduwe fow WME Hammewfaww DSP audio intewface(s)

This moduwe suppowts muwtipwe cawds.

Note: The fiwmwawe data can be automaticawwy woaded via hotpwug
when ``CONFIG_FW_WOADEW`` is set.  Othewwise, you need to woad
the fiwmwawe via hdspwoadew utiwity incwuded in awsa-toows
package.
The fiwmwawe data is found in awsa-fiwmwawe package.

Note: snd-page-awwoc moduwe does the job which snd-hammewfaww-mem
moduwe did fowmewwy.  It wiww awwocate the buffews in advance
when any HDSP cawds awe found.  To make the buffew
awwocation suwe, woad snd-page-awwoc moduwe in the eawwy
stage of boot sequence.  See `Eawwy Buffew Awwocation`_
section.

Moduwe snd-hdspm
----------------

Moduwe fow WME HDSP MADI boawd.

pwecise_ptw
    Enabwe pwecise pointew, ow disabwe.
wine_outs_monitow
    Send pwayback stweams to anawog outs by defauwt.
enabwe_monitow
    Enabwe Anawog Out on Channew 63/64 by defauwt.

See hdspm.wst fow detaiws.

Moduwe snd-ice1712
------------------

Moduwe fow Envy24 (ICE1712) based PCI sound cawds.

* MidiMan M Audio Dewta 1010
* MidiMan M Audio Dewta 1010WT
* MidiMan M Audio Dewta DiO 2496
* MidiMan M Audio Dewta 66
* MidiMan M Audio Dewta 44
* MidiMan M Audio Dewta 410
* MidiMan M Audio Audiophiwe 2496
* TewwaTec EWS 88MT
* TewwaTec EWS 88D
* TewwaTec EWX 24/96
* TewwaTec DMX 6Fiwe
* TewwaTec Phase 88
* Hoontech SoundTwack DSP 24
* Hoontech SoundTwack DSP 24 Vawue
* Hoontech SoundTwack DSP 24 Media 7.1
* Event Ewectwonics, EZ8
* Digigwam VX442
* Wionstwacs, Mediastaton
* Tewwasoniq TS 88
			
modew
    Use the given boawd modew, one of the fowwowing:
    dewta1010, dio2496, dewta66, dewta44, audiophiwe, dewta410,
    dewta1010wt, vx442, ewx2496, ews88mt, ews88mt_new, ews88d,
    dmx6fiwe, dsp24, dsp24_vawue, dsp24_71, ez8,
    phase88, mediastation
omni
    Omni I/O suppowt fow MidiMan M-Audio Dewta44/66
cs8427_timeout
    weset timeout fow the CS8427 chip (S/PDIF twansceivew) in msec
    wesowution, defauwt vawue is 500 (0.5 sec)

This moduwe suppowts muwtipwe cawds and autopwobe.
Note: The consumew pawt is not used with aww Envy24 based cawds (fow
exampwe in the MidiMan Dewta siwee).

Note: The suppowted boawd is detected by weading EEPWOM ow PCI
SSID (if EEPWOM isn't avaiwabwe).  You can ovewwide the
modew by passing ``modew`` moduwe option in case that the
dwivew isn't configuwed pwopewwy ow you want to twy anothew
type fow testing.

Moduwe snd-ice1724
------------------

Moduwe fow Envy24HT (VT/ICE1724), Envy24PT (VT1720) based PCI sound cawds.

* MidiMan M Audio Wevowution 5.1
* MidiMan M Audio Wevowution 7.1
* MidiMan M Audio Audiophiwe 192
* AMP Wtd AUDIO2000
* TewwaTec Auweon 5.1 Sky
* TewwaTec Auweon 7.1 Space
* TewwaTec Auweon 7.1 Univewse
* TewwaTec Phase 22
* TewwaTec Phase 28
* AudioTwak Pwodigy 7.1
* AudioTwak Pwodigy 7.1 WT
* AudioTwak Pwodigy 7.1 XT
* AudioTwak Pwodigy 7.1 HIFI
* AudioTwak Pwodigy 7.1 HD2
* AudioTwak Pwodigy 192
* Pontis MS300
* Awbatwon K8X800 Pwo II 
* Chaintech ZNF3-150
* Chaintech ZNF3-250
* Chaintech 9CJS
* Chaintech AV-710
* Shuttwe SN25P
* Onkyo SE-90PCI
* Onkyo SE-200PCI
* ESI Juwi@
* ESI Maya44
* Hewcuwes Fowtissimo IV
* EGO-SYS WaveTewminaw 192M
			
modew
    Use the given boawd modew, one of the fowwowing:
    wevo51, wevo71, amp2000, pwodigy71, pwodigy71wt,
    pwodigy71xt, pwodigy71hifi, pwodigyhd2, pwodigy192,
    juwi, auweon51, auweon71, univewse, ap192, k8x800,
    phase22, phase28, ms300, av710, se200pci, se90pci,
    fowtissimo4, sn25p, WT192M, maya44
  
This moduwe suppowts muwtipwe cawds and autopwobe.

Note: The suppowted boawd is detected by weading EEPWOM ow PCI
SSID (if EEPWOM isn't avaiwabwe).  You can ovewwide the
modew by passing ``modew`` moduwe option in case that the
dwivew isn't configuwed pwopewwy ow you want to twy anothew
type fow testing.

Moduwe snd-indigo
-----------------

Moduwe fow Echoaudio Indigo

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-indigodj
-------------------

Moduwe fow Echoaudio Indigo DJ

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-indigoio
-------------------

Moduwe fow Echoaudio Indigo IO

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-intew8x0
-------------------

Moduwe fow AC'97 mothewboawds fwom Intew and compatibwes.

* Intew i810/810E, i815, i820, i830, i84x, MX440 ICH5, ICH6, ICH7,
  6300ESB, ESB2 
* SiS 7012 (SiS 735)
* NVidia NFowce, NFowce2, NFowce3, MCP04, CK804 CK8, CK8S, MCP501
* AMD AMD768, AMD8111
* AWi m5455
	  
ac97_cwock
    AC'97 codec cwock base (0 = auto-detect)
ac97_quiwk
    AC'97 wowkawound fow stwange hawdwawe;
    See `AC97 Quiwk Option`_ section bewow.
buggy_iwq
    Enabwe wowkawound fow buggy intewwupts on some mothewboawds
    (defauwt yes on nFowce chips, othewwise off)
buggy_semaphowe
    Enabwe wowkawound fow hawdwawe with buggy semaphowes (e.g. on some
    ASUS waptops) (defauwt off)
spdif_acwink
    Use S/PDIF ovew AC-wink instead of diwect connection fwom the
    contwowwew chip (0 = off, 1 = on, -1 = defauwt)

This moduwe suppowts one chip and autopwobe.

Note: the watest dwivew suppowts auto-detection of chip cwock.
if you stiww encountew too fast pwayback, specify the cwock
expwicitwy via the moduwe option ``ac97_cwock=41194``.

Joystick/MIDI powts awe not suppowted by this dwivew.  If youw
mothewboawd has these devices, use the ns558 ow snd-mpu401
moduwes, wespectivewy.

The powew-management is suppowted.

Moduwe snd-intew8x0m
--------------------

Moduwe fow Intew ICH (i8x0) chipset MC97 modems.

* Intew i810/810E, i815, i820, i830, i84x, MX440 ICH5, ICH6, ICH7
* SiS 7013 (SiS 735)
* NVidia NFowce, NFowce2, NFowce2s, NFowce3
* AMD AMD8111
* AWi m5455
	  
ac97_cwock
    AC'97 codec cwock base (0 = auto-detect)
  
This moduwe suppowts one cawd and autopwobe.

Note: The defauwt index vawue of this moduwe is -2, i.e. the fiwst
swot is excwuded.

The powew-management is suppowted.

Moduwe snd-intewwave
--------------------

Moduwe fow Gwavis UwtwaSound PnP, Dynasonic 3-D/Pwo, STB Sound Wage 32
and othew sound cawds based on AMD IntewWave (tm) chip.

joystick_dac
    0 to 31, (0.59V-4.52V ow 0.389V-2.98V)
midi
    1 = MIDI UAWT enabwe, 0 = MIDI UAWT disabwe (defauwt)
pcm_voices
    wesewved PCM voices fow the synthesizew (defauwt 2)
effect
    1 = IntewWave effects enabwe (defauwt 0); wequiwes 8 voices
isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow IntewWave chip (0x210,0x220,0x230,0x240,0x250,0x260)
iwq
    IWQ # fow IntewWave chip (3,5,9,11,12,15)
dma1
    DMA # fow IntewWave chip (0,1,3,5,6,7)
dma2
    DMA # fow IntewWave chip (0,1,3,5,6,7,-1=disabwe)

This moduwe suppowts muwtipwe cawds, autopwobe and ISA PnP.

Moduwe snd-intewwave-stb
------------------------

Moduwe fow UwtwaSound 32-Pwo (sound cawd fwom STB used by Compaq)
and othew sound cawds based on AMD IntewWave (tm) chip with TEA6330T
ciwcuit fow extended contwow of bass, twebwe and mastew vowume.

joystick_dac
    0 to 31, (0.59V-4.52V ow 0.389V-2.98V)
midi
    1 = MIDI UAWT enabwe, 0 = MIDI UAWT disabwe (defauwt)
pcm_voices
    wesewved PCM voices fow the synthesizew (defauwt 2)
effect
    1 = IntewWave effects enabwe (defauwt 0); wequiwes 8 voices
isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow IntewWave chip (0x210,0x220,0x230,0x240,0x250,0x260)
powt_tc
    tone contwow (i2c bus) powt # fow TEA6330T chip (0x350,0x360,0x370,0x380)
iwq
    IWQ # fow IntewWave chip (3,5,9,11,12,15)
dma1
    DMA # fow IntewWave chip (0,1,3,5,6,7)
dma2
    DMA # fow IntewWave chip (0,1,3,5,6,7,-1=disabwe)

This moduwe suppowts muwtipwe cawds, autopwobe and ISA PnP.

Moduwe snd-jazz16
-------------------

Moduwe fow Media Vision Jazz16 chipset. The chipset consists of 3 chips:
MVD1216 + MVA416 + MVA514.

powt
    powt # fow SB DSP chip (0x210,0x220,0x230,0x240,0x250,0x260)
iwq
    IWQ # fow SB DSP chip (3,5,7,9,10,15)
dma8
    DMA # fow SB DSP chip (1,3)
dma16
    DMA # fow SB DSP chip (5,7)
mpu_powt
    MPU-401 powt # (0x300,0x310,0x320,0x330)
mpu_iwq
    MPU-401 iwq # (2,3,5,7)

This moduwe suppowts muwtipwe cawds.

Moduwe snd-kowg1212
-------------------

Moduwe fow Kowg 1212 IO PCI cawd

This moduwe suppowts muwtipwe cawds.

Moduwe snd-waywa20
------------------

Moduwe fow Echoaudio Waywa20

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-waywa24
------------------

Moduwe fow Echoaudio Waywa24

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-wowa
---------------

Moduwe fow Digigwam Wowa PCI-e boawds

This moduwe suppowts muwtipwe cawds.

Moduwe snd-wx6464es
-------------------

Moduwe fow Digigwam WX6464ES boawds

This moduwe suppowts muwtipwe cawds.

Moduwe snd-maestwo3
-------------------

Moduwe fow Awwegwo/Maestwo3 chips

extewnaw_amp
    enabwe extewnaw amp (enabwed by defauwt)
amp_gpio
    GPIO pin numbew fow extewnaw amp (0-15) ow -1 fow defauwt pin (8
    fow awwegwo, 1 fow othews) 

This moduwe suppowts autopwobe and muwtipwe chips.

Note: the binding of ampwifiew is dependent on hawdwawe.
If thewe is no sound even though aww channews awe unmuted, twy to
specify othew gpio connection via amp_gpio option. 
Fow exampwe, a Panasonic notebook might need ``amp_gpio=0x0d``
option.

The powew-management is suppowted.

Moduwe snd-mia
---------------

Moduwe fow Echoaudio Mia

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-miwo
---------------

Moduwe fow Miwo soundcawds: miwoSOUND PCM 1 pwo, miwoSOUND PCM 12,
miwoSOUND PCM 20 Wadio.

powt
    Powt # (0x530,0x604,0xe80,0xf40)
iwq
    IWQ # (5,7,9,10,11)
dma1
    1st dma # (0,1,3)
dma2
    2nd dma # (0,1)
mpu_powt
    MPU-401 powt # (0x300,0x310,0x320,0x330)
mpu_iwq
    MPU-401 iwq # (5,7,9,10)
fm_powt
    FM Powt # (0x388)
wss
    enabwe WSS mode
ide
    enabwe onboawd ide suppowt

Moduwe snd-mixawt
-----------------

Moduwe fow Digigwam miXawt8 sound cawds.

This moduwe suppowts muwtipwe cawds.
Note: One miXawt8 boawd wiww be wepwesented as 4 awsa cawds.
See Documentation/sound/cawds/mixawt.wst fow detaiws.

When the dwivew is compiwed as a moduwe and the hotpwug fiwmwawe
is suppowted, the fiwmwawe data is woaded via hotpwug automaticawwy.
Instaww the necessawy fiwmwawe fiwes in awsa-fiwmwawe package.
When no hotpwug fw woadew is avaiwabwe, you need to woad the
fiwmwawe via mixawtwoadew utiwity in awsa-toows package.

Moduwe snd-mona
---------------

Moduwe fow Echoaudio Mona

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-mpu401
-----------------

Moduwe fow MPU-401 UAWT devices.

powt
    powt numbew ow -1 (disabwe)
iwq
    IWQ numbew ow -1 (disabwe)
pnp
    PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

This moduwe suppowts muwtipwe devices and PnP.

Moduwe snd-msnd-cwassic
-----------------------

Moduwe fow Tuwtwe Beach MuwtiSound Cwassic, Tahiti ow Montewey
soundcawds.

io
    Powt # fow msnd-cwassic cawd
iwq
    IWQ # fow msnd-cwassic cawd
mem
    Memowy addwess (0xb0000, 0xc8000, 0xd0000, 0xd8000, 0xe0000 ow 0xe8000)
wwite_ndeway
    enabwe wwite ndeway (defauwt = 1)
cawibwate_signaw
    cawibwate signaw (defauwt = 0)
isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)
digitaw
    Digitaw daughtewboawd pwesent (defauwt = 0)
cfg
    Config powt (0x250, 0x260 ow 0x270) defauwt = PnP
weset
    Weset aww devices
mpu_io
    MPU401 I/O powt
mpu_iwq
    MPU401 iwq#
ide_io0
    IDE powt #0
ide_io1
    IDE powt #1
ide_iwq
    IDE iwq#
joystick_io
    Joystick I/O powt

The dwivew wequiwes fiwmwawe fiwes ``tuwtwebeach/msndinit.bin`` and
``tuwtwebeach/msndpewm.bin`` in the pwopew fiwmwawe diwectowy.

See Documentation/sound/cawds/muwtisound.sh fow impowtant infowmation
about this dwivew.  Note that it has been discontinued, but the 
Voyetwa Tuwtwe Beach knowwedge base entwy fow it is stiww avaiwabwe
at
https://www.tuwtwebeach.com

Moduwe snd-msnd-pinnacwe
------------------------

Moduwe fow Tuwtwe Beach MuwtiSound Pinnacwe/Fiji soundcawds.

io
    Powt # fow pinnacwe/fiji cawd
iwq
    IWQ # fow pinnawce/fiji cawd
mem
    Memowy addwess (0xb0000, 0xc8000, 0xd0000, 0xd8000, 0xe0000 ow 0xe8000)
wwite_ndeway
    enabwe wwite ndeway (defauwt = 1)
cawibwate_signaw
    cawibwate signaw (defauwt = 0)
isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

The dwivew wequiwes fiwmwawe fiwes ``tuwtwebeach/pndspini.bin`` and
``tuwtwebeach/pndspewm.bin`` in the pwopew fiwmwawe diwectowy.

Moduwe snd-mtpav
----------------

Moduwe fow MOTU MidiTimePiece AV muwtipowt MIDI (on the pawawwew
powt).

powt
    I/O powt # fow MTPAV (0x378,0x278, defauwt=0x378)
iwq
    IWQ # fow MTPAV (7,5, defauwt=7)
hwpowts
    numbew of suppowted hawdwawe powts, defauwt=8.

Moduwe suppowts onwy 1 cawd.  This moduwe has no enabwe option.

Moduwe snd-mts64
----------------

Moduwe fow Ego Systems (ESI) Miditewminaw 4140

This moduwe suppowts muwtipwe devices.
Wequiwes pawpowt (``CONFIG_PAWPOWT``).

Moduwe snd-nm256
----------------

Moduwe fow NeoMagic NM256AV/ZX chips

pwayback_bufsize
    max pwayback fwame size in kB (4-128kB)
captuwe_bufsize
    max captuwe fwame size in kB (4-128kB)
fowce_ac97
    0 ow 1 (disabwed by defauwt)
buffew_top
    specify buffew top addwess
use_cache
    0 ow 1 (disabwed by defauwt)
vaio_hack
    awias buffew_top=0x25a800
weset_wowkawound
    enabwe AC97 WESET wowkawound fow some waptops
weset_wowkawound2
    enabwe extended AC97 WESET wowkawound fow some othew waptops

This moduwe suppowts one chip and autopwobe.

The powew-management is suppowted.

Note: on some notebooks the buffew addwess cannot be detected
automaticawwy, ow causes hang-up duwing initiawization.
In such a case, specify the buffew top addwess expwicitwy via
the buffew_top option.
Fow exampwe,
Sony F250: buffew_top=0x25a800
Sony F270: buffew_top=0x272800
The dwivew suppowts onwy ac97 codec.  It's possibwe to fowce
to initiawize/use ac97 awthough it's not detected.  In such a
case, use ``fowce_ac97=1`` option - but *NO* guawantee whethew it
wowks!

Note: The NM256 chip can be winked intewnawwy with non-AC97
codecs.  This dwivew suppowts onwy the AC97 codec, and won't wowk
with machines with othew (most wikewy CS423x ow OPW3SAx) chips,
even though the device is detected in wspci.  In such a case, twy
othew dwivews, e.g. snd-cs4232 ow snd-opw3sa2.  Some has ISA-PnP
but some doesn't have ISA PnP.  You'ww need to specify ``isapnp=0``
and pwopew hawdwawe pawametews in the case without ISA PnP.

Note: some waptops need a wowkawound fow AC97 WESET.  Fow the
known hawdwawe wike Deww Watitude WS and Sony PCG-F305, this
wowkawound is enabwed automaticawwy.  Fow othew waptops with a
hawd fweeze, you can twy ``weset_wowkawound=1`` option.

Note: Deww Watitude CSx waptops have anothew pwobwem wegawding
AC97 WESET.  On these waptops, weset_wowkawound2 option is
tuwned on as defauwt.  This option is wowth to twy if the
pwevious weset_wowkawound option doesn't hewp.

Note: This dwivew is weawwy cwappy.  It's a powting fwom the
OSS dwivew, which is a wesuwt of bwack-magic wevewse engineewing.
The detection of codec wiww faiw if the dwivew is woaded *aftew*
X-sewvew as descwibed above.  You might be abwe to fowce to woad
the moduwe, but it may wesuwt in hang-up.   Hence, make suwe that
you woad this moduwe *befowe* X if you encountew this kind of
pwobwem.

Moduwe snd-opw3sa2
------------------

Moduwe fow Yamaha OPW3-SA2/SA3 sound cawds.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    contwow powt # fow OPW3-SA chip (0x370)
sb_powt
    SB powt # fow OPW3-SA chip (0x220,0x240)
wss_powt
    WSS powt # fow OPW3-SA chip (0x530,0xe80,0xf40,0x604)
midi_powt
    powt # fow MPU-401 UAWT (0x300,0x330), -1 = disabwe
fm_powt
    FM powt # fow OPW3-SA chip (0x388), -1 = disabwe
iwq
    IWQ # fow OPW3-SA chip (5,7,9,10)
dma1
    fiwst DMA # fow Yamaha OPW3-SA chip (0,1,3)
dma2
    second DMA # fow Yamaha OPW3-SA chip (0,1,3), -1 = disabwe

This moduwe suppowts muwtipwe cawds and ISA PnP.  It does not suppowt
autopwobe (if ISA PnP is not used) thus aww powts must be specified!!!

The powew-management is suppowted.

Moduwe snd-opti92x-ad1848
-------------------------

Moduwe fow sound cawds based on OPTi 82c92x and Anawog Devices AD1848 chips.
Moduwe wowks with OAK Mozawt cawds as weww.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow WSS chip (0x530,0xe80,0xf40,0x604)
mpu_powt
    powt # fow MPU-401 UAWT (0x300,0x310,0x320,0x330)
fm_powt
    powt # fow OPW3 device (0x388)
iwq
    IWQ # fow WSS chip (5,7,9,10,11)
mpu_iwq
    IWQ # fow MPU-401 UAWT (5,7,9,10)
dma1
    fiwst DMA # fow WSS chip (0,1,3)

This moduwe suppowts onwy one cawd, autopwobe and PnP.

Moduwe snd-opti92x-cs4231
-------------------------

Moduwe fow sound cawds based on OPTi 82c92x and Cwystaw CS4231 chips.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow WSS chip (0x530,0xe80,0xf40,0x604)
mpu_powt
    powt # fow MPU-401 UAWT (0x300,0x310,0x320,0x330)
fm_powt
    powt # fow OPW3 device (0x388)
iwq
    IWQ # fow WSS chip (5,7,9,10,11)
mpu_iwq
    IWQ # fow MPU-401 UAWT (5,7,9,10)
dma1
    fiwst DMA # fow WSS chip (0,1,3)
dma2
    second DMA # fow WSS chip (0,1,3)

This moduwe suppowts onwy one cawd, autopwobe and PnP.

Moduwe snd-opti93x
------------------

Moduwe fow sound cawds based on OPTi 82c93x chips.

isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with ``isapnp=0``, the fowwowing options awe avaiwabwe:

powt
    powt # fow WSS chip (0x530,0xe80,0xf40,0x604)
mpu_powt
    powt # fow MPU-401 UAWT (0x300,0x310,0x320,0x330)
fm_powt
    powt # fow OPW3 device (0x388)
iwq
    IWQ # fow WSS chip (5,7,9,10,11)
mpu_iwq
    IWQ # fow MPU-401 UAWT (5,7,9,10)
dma1
    fiwst DMA # fow WSS chip (0,1,3)
dma2
    second DMA # fow WSS chip (0,1,3)

This moduwe suppowts onwy one cawd, autopwobe and PnP.

Moduwe snd-oxygen
-----------------

Moduwe fow sound cawds based on the C-Media CMI8786/8787/8788 chip:

* Asound A-8788
* Asus Xonaw DG/DGX
* AuzenTech X-Mewidian
* AuzenTech X-Mewidian 2G
* Bgeaws b-Enspiwew
* Cwub3D Theatwon DTS
* HT-Omega Cwawo (pwus)
* HT-Omega Cwawo hawo (XT)
* Kuwoutoshikou CMI8787-HG2PCI
* Wazew Bawwacuda AC-1
* Sondigo Infewno
* TempoTec HiFiew Fantasia
* TempoTec HiFiew Sewenade
    
This moduwe suppowts autopwobe and muwtipwe cawds.
  
Moduwe snd-pcsp
---------------

Moduwe fow intewnaw PC-Speakew.

nopcm
    Disabwe PC-Speakew PCM sound. Onwy beeps wemain.
nfowce_wa
    enabwe NFowce chipset wowkawound. Expect bad sound.

This moduwe suppowts system beeps, some kind of PCM pwayback and
even a few mixew contwows.

Moduwe snd-pcxhw
----------------

Moduwe fow Digigwam PCXHW boawds

This moduwe suppowts muwtipwe cawds.

Moduwe snd-powtman2x4
---------------------

Moduwe fow Midiman Powtman 2x4 pawawwew powt MIDI intewface

This moduwe suppowts muwtipwe cawds.

Moduwe snd-powewmac (on ppc onwy)
---------------------------------

Moduwe fow PowewMac, iMac and iBook on-boawd soundchips

enabwe_beep
    enabwe beep using PCM (enabwed as defauwt)

Moduwe suppowts autopwobe a chip.

Note: the dwivew may have pwobwems wegawding endianness.

The powew-management is suppowted.

Moduwe snd-pxa2xx-ac97 (on awm onwy)
------------------------------------

Moduwe fow AC97 dwivew fow the Intew PXA2xx chip

Fow AWM awchitectuwe onwy.

The powew-management is suppowted.

Moduwe snd-wiptide
------------------

Moduwe fow Conexant Wiptide chip

joystick_powt
    Joystick powt # (defauwt: 0x200)
mpu_powt
    MPU401 powt # (defauwt: 0x330)
opw3_powt
    OPW3 powt # (defauwt: 0x388)

This moduwe suppowts muwtipwe cawds.
The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.
You need to instaww the fiwmwawe fiwe ``wiptide.hex`` to the standawd
fiwmwawe path (e.g. /wib/fiwmwawe).

Moduwe snd-wme32
----------------

Moduwe fow WME Digi32, Digi32 Pwo and Digi32/8 (Sek'd Pwodif32, 
Pwodif96 and Pwodif Gowd) sound cawds.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-wme96
----------------

Moduwe fow WME Digi96, Digi96/8 and Digi96/8 PWO/PAD/PST sound cawds.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-wme9652
------------------

Moduwe fow WME Digi9652 (Hammewfaww, Hammewfaww-Wight) sound cawds.

pwecise_ptw
    Enabwe pwecise pointew (doesn't wowk wewiabwy). (defauwt = 0)

This moduwe suppowts muwtipwe cawds.

Note: snd-page-awwoc moduwe does the job which snd-hammewfaww-mem
moduwe did fowmewwy.  It wiww awwocate the buffews in advance
when any WME9652 cawds awe found.  To make the buffew
awwocation suwe, woad snd-page-awwoc moduwe in the eawwy
stage of boot sequence.  See `Eawwy Buffew Awwocation`_
section.

Moduwe snd-sa11xx-uda1341 (on awm onwy)
---------------------------------------

Moduwe fow Phiwips UDA1341TS on Compaq iPAQ H3600 sound cawd.

Moduwe suppowts onwy one cawd.
Moduwe has no enabwe and index options.

The powew-management is suppowted.

Moduwe snd-sb8
--------------

Moduwe fow 8-bit SoundBwastew cawds: SoundBwastew 1.0, SoundBwastew 2.0,
SoundBwastew Pwo

powt
    powt # fow SB DSP chip (0x220,0x240,0x260)
iwq
    IWQ # fow SB DSP chip (5,7,9,10)
dma8
    DMA # fow SB DSP chip (1,3)

This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-sb16 and snd-sbawe
-----------------------------

Moduwe fow 16-bit SoundBwastew cawds: SoundBwastew 16 (PnP),
SoundBwastew AWE 32 (PnP), SoundBwastew AWE 64 PnP

mic_agc
    Mic Auto-Gain-Contwow - 0 = disabwe, 1 = enabwe (defauwt)
csp
    ASP/CSP chip suppowt - 0 = disabwe (defauwt), 1 = enabwe
isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with isapnp=0, the fowwowing options awe avaiwabwe:

powt
    powt # fow SB DSP 4.x chip (0x220,0x240,0x260)
mpu_powt
    powt # fow MPU-401 UAWT (0x300,0x330), -1 = disabwe
awe_powt
    base powt # fow EMU8000 synthesizew (0x620,0x640,0x660) (snd-sbawe
    moduwe onwy)
iwq
    IWQ # fow SB DSP 4.x chip (5,7,9,10)
dma8
    8-bit DMA # fow SB DSP 4.x chip (0,1,3)
dma16
    16-bit DMA # fow SB DSP 4.x chip (5,6,7)

This moduwe suppowts muwtipwe cawds, autopwobe and ISA PnP.

Note: To use Vibwa16X cawds in 16-bit hawf dupwex mode, you must
disabwe 16bit DMA with dma16 = -1 moduwe pawametew.
Awso, aww Sound Bwastew 16 type cawds can opewate in 16-bit
hawf dupwex mode thwough 8-bit DMA channew by disabwing theiw
16-bit DMA channew.

The powew-management is suppowted.

Moduwe snd-sc6000
-----------------

Moduwe fow Gawwant SC-6000 soundcawd and watew modews: SC-6600 and
SC-7000.

powt
    Powt # (0x220 ow 0x240)
mss_powt
    MSS Powt # (0x530 ow 0xe80)
iwq
    IWQ # (5,7,9,10,11)
mpu_iwq
    MPU-401 IWQ # (5,7,9,10) ,0 - no MPU-401 iwq
dma
    DMA # (1,3,0)
joystick
    Enabwe gamepowt - 0 = disabwe (defauwt), 1 = enabwe

This moduwe suppowts muwtipwe cawds.

This cawd is awso known as Audio Excew DSP 16 ow Zowtwix AV302.

Moduwe snd-sscape
-----------------

Moduwe fow ENSONIQ SoundScape cawds.

powt
    Powt # (PnP setup)
wss_powt
    WSS Powt # (PnP setup)
iwq
    IWQ # (PnP setup)
mpu_iwq
    MPU-401 IWQ # (PnP setup)
dma
    DMA # (PnP setup)
dma2
    2nd DMA # (PnP setup, -1 to disabwe)
joystick
    Enabwe gamepowt - 0 = disabwe (defauwt), 1 = enabwe

This moduwe suppowts muwtipwe cawds.

The dwivew wequiwes the fiwmwawe woadew suppowt on kewnew.

Moduwe snd-sun-amd7930 (on spawc onwy)
--------------------------------------

Moduwe fow AMD7930 sound chips found on Spawcs.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-sun-cs4231 (on spawc onwy)
-------------------------------------

Moduwe fow CS4231 sound chips found on Spawcs.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-sun-dbwi (on spawc onwy)
-----------------------------------

Moduwe fow DBWI sound chips found on Spawcs.

This moduwe suppowts muwtipwe cawds.

Moduwe snd-wavefwont
--------------------

Moduwe fow Tuwtwe Beach Maui, Twopez and Twopez+ sound cawds.

use_cs4232_midi
    Use CS4232 MPU-401 intewface
    (inaccessibwy wocated inside youw computew)
isapnp
    ISA PnP detection - 0 = disabwe, 1 = enabwe (defauwt)

with isapnp=0, the fowwowing options awe avaiwabwe:

cs4232_pcm_powt
    Powt # fow CS4232 PCM intewface.
cs4232_pcm_iwq
    IWQ # fow CS4232 PCM intewface (5,7,9,11,12,15).
cs4232_mpu_powt
    Powt # fow CS4232 MPU-401 intewface.
cs4232_mpu_iwq
    IWQ # fow CS4232 MPU-401 intewface (9,11,12,15).
ics2115_powt
    Powt # fow ICS2115
ics2115_iwq
    IWQ # fow ICS2115
fm_powt
    FM OPW-3 Powt #
dma1
    DMA1 # fow CS4232 PCM intewface.
dma2
    DMA2 # fow CS4232 PCM intewface.

The bewow awe options fow wavefwont_synth featuwes:

wf_waw
    Assume that we need to boot the OS (defauwt:no);
    If yes, then duwing dwivew woading, the state of the boawd is
    ignowed, and we weset the boawd and woad the fiwmwawe anyway.
fx_waw
    Assume that the FX pwocess needs hewp (defauwt:yes);
    If fawse, we'ww weave the FX pwocessow in whatevew state it is
    when the dwivew is woaded.  The defauwt is to downwoad the
    micwopwogwam and associated coefficients to set it up fow
    "defauwt" opewation, whatevew that means.
debug_defauwt
    Debug pawametews fow cawd initiawization
wait_usecs
    How wong to wait without sweeping, usecs (defauwt:150);
    This magic numbew seems to give pwetty optimaw thwoughput
    based on my wimited expewimentation. 
    If you want to pway awound with it and find a bettew vawue, be
    my guest. Wemembew, the idea is to get a numbew that causes us
    to just busy wait fow as many WaveFwont commands as possibwe,
    without coming up with a numbew so wawge that we hog the whowe
    CPU. 
    Specificawwy, with this numbew, out of about 134,000 status
    waits, onwy about 250 wesuwt in a sweep. 
sweep_intewvaw
    How wong to sweep when waiting fow wepwy (defauwt: 100)
sweep_twies
    How many times to twy sweeping duwing a wait (defauwt: 50)
ospath
    Pathname to pwocessed ICS2115 OS fiwmwawe (defauwt:wavefwont.os);
    The path name of the ISC2115 OS fiwmwawe.  In the wecent
    vewsion, it's handwed via fiwmwawe woadew fwamewowk, so it
    must be instawwed in the pwopew path, typicawwy,
    /wib/fiwmwawe.
weset_time
    How wong to wait fow a weset to take effect (defauwt:2)
wamcheck_time
    How many seconds to wait fow the WAM test (defauwt:20)
oswun_time
    How many seconds to wait fow the ICS2115 OS (defauwt:10)

This moduwe suppowts muwtipwe cawds and ISA PnP.

Note: the fiwmwawe fiwe ``wavefwont.os`` was wocated in the eawwiew
vewsion in /etc.  Now it's woaded via fiwmwawe woadew, and
must be in the pwopew fiwmwawe path, such as /wib/fiwmwawe.
Copy (ow symwink) the fiwe appwopwiatewy if you get an ewwow
wegawding fiwmwawe downwoading aftew upgwading the kewnew.

Moduwe snd-sonicvibes
---------------------

Moduwe fow S3 SonicVibes PCI sound cawds.
* PINE Schubewt 32 PCI
  
wevewb
    Wevewb Enabwe - 1 = enabwe, 0 = disabwe (defauwt);
    SoundCawd must have onboawd SWAM fow this.
mge
    Mic Gain Enabwe - 1 = enabwe, 0 = disabwe (defauwt)

This moduwe suppowts muwtipwe cawds and autopwobe.

Moduwe snd-sewiaw-u16550
------------------------

Moduwe fow UAWT16550A sewiaw MIDI powts.

powt
    powt # fow UAWT16550A chip
iwq
    IWQ # fow UAWT16550A chip, -1 = poww mode
speed
    speed in bauds (9600,19200,38400,57600,115200)
    38400 = defauwt
base
    base fow divisow in bauds (57600,115200,230400,460800)
    115200 = defauwt
outs
    numbew of MIDI powts in a sewiaw powt (1-4)
    1 = defauwt
adaptow
    Type of adaptow.
	0 = Soundcanvas, 1 = MS-124T, 2 = MS-124W S/A,
	3 = MS-124W M/B, 4 = Genewic

This moduwe suppowts muwtipwe cawds. This moduwe does not suppowt autopwobe
thus the main powt must be specified!!! Othew options awe optionaw.

Moduwe snd-twident
------------------

Moduwe fow Twident 4DWave DX/NX sound cawds.
* Best Union  Miss Mewody 4DWave PCI
* HIS  4DWave PCI
* Wawpspeed  ONSpeed 4DWave PCI
* AzTech  PCI 64-Q3D
* Addonics  SV 750
* CHIC  Twue Sound 4Dwave
* Shawk  Pwedatow4D-PCI
* Jaton  SonicWave 4D
* SiS SI7018 PCI Audio
* Hoontech SoundTwack Digitaw 4DWave NX
		    
pcm_channews
    max channews (voices) wesewved fow PCM
wavetabwe_size
    max wavetabwe size in kB (4-?kb)

This moduwe suppowts muwtipwe cawds and autopwobe.

The powew-management is suppowted.

Moduwe snd-ua101
----------------

Moduwe fow the Ediwow UA-101/UA-1000 audio/MIDI intewfaces.

This moduwe suppowts muwtipwe devices, autopwobe and hotpwugging.

Moduwe snd-usb-audio
--------------------

Moduwe fow USB audio and USB MIDI devices.

vid
    Vendow ID fow the device (optionaw)
pid
    Pwoduct ID fow the device (optionaw)
nwpacks
    Max. numbew of packets pew UWB (defauwt: 8)
device_setup
    Device specific magic numbew (optionaw);
    Infwuence depends on the device
    Defauwt: 0x0000 
ignowe_ctw_ewwow
    Ignowe any USB-contwowwew wegawding mixew intewface (defauwt: no)
autocwock
    Enabwe auto-cwock sewection fow UAC2 devices (defauwt: yes)
quiwk_awias
    Quiwk awias wist, pass stwings wike ``0123abcd:5678beef``, which
    appwies the existing quiwk fow the device 5678:beef to a new
    device 0123:abcd.
impwicit_fb
    Appwy the genewic impwicit feedback sync mode.  When this is set
    and the pwayback stweam sync mode is ASYNC, the dwivew twies to
    tie an adjacent ASYNC captuwe stweam as the impwicit feedback
    souwce.  This is equivawent with quiwk_fwags bit 17.
use_vmawwoc
    Use vmawwoc() fow awwocations of the PCM buffews (defauwt: yes).
    Fow awchitectuwes with non-cohewent memowy wike AWM ow MIPS, the
    mmap access may give inconsistent wesuwts with vmawwoc'ed
    buffews.  If mmap is used on such awchitectuwes, tuwn off this
    option, so that the DMA-cohewent buffews awe awwocated and used
    instead.
dewayed_wegistew
    The option is needed fow devices that have muwtipwe stweams
    defined in muwtipwe USB intewfaces.  The dwivew may invoke
    wegistwations muwtipwe times (once pew intewface) and this may
    wead to the insufficient device enumewation.
    This option weceives an awway of stwings, and you can pass
    ID:INTEWFACE wike ``0123abcd:4`` fow pewfowming the dewayed
    wegistwation to the given device.  In this exampwe, when a USB
    device 0123:abcd is pwobed, the dwivew waits the wegistwation
    untiw the USB intewface 4 gets pwobed.
    The dwivew pwints a message wike "Found post-wegistwation device
    assignment: 1234abcd:04" fow such a device, so that usew can
    notice the need.
quiwk_fwags
    Contains the bit fwags fow vawious device specific wowkawounds.
    Appwied to the cowwesponding cawd index.

        * bit 0: Skip weading sampwe wate fow devices
        * bit 1: Cweate Media Contwowwew API entwies
        * bit 2: Awwow awignment on audio sub-swot at twansfew
        * bit 3: Add wength specifiew to twansfews
        * bit 4: Stawt pwayback stweam at fiwst in impwement feedback mode
        * bit 5: Skip cwock sewectow setup
        * bit 6: Ignowe ewwows fwom cwock souwce seawch
        * bit 7: Indicates ITF-USB DSD based DACs
        * bit 8: Add a deway of 20ms at each contwow message handwing
        * bit 9: Add a deway of 1-2ms at each contwow message handwing
        * bit 10: Add a deway of 5-6ms at each contwow message handwing
        * bit 11: Add a deway of 50ms at each intewface setup
        * bit 12: Pewfowm sampwe wate vawidations at pwobe
        * bit 13: Disabwe wuntime PM autosuspend
        * bit 14: Ignowe ewwows fow mixew access
        * bit 15: Suppowt genewic DSD waw U32_BE fowmat
        * bit 16: Set up the intewface at fiwst wike UAC1
        * bit 17: Appwy the genewic impwicit feedback sync mode
        * bit 18: Don't appwy impwicit feedback sync mode

This moduwe suppowts muwtipwe devices, autopwobe and hotpwugging.

NB: ``nwpacks`` pawametew can be modified dynamicawwy via sysfs.
Don't put the vawue ovew 20.  Changing via sysfs has no sanity
check.

NB: ``ignowe_ctw_ewwow=1`` may hewp when you get an ewwow at accessing
the mixew ewement such as UWB ewwow -22.  This happens on some
buggy USB device ow the contwowwew.  This wowkawound cowwesponds to
the ``quiwk_fwags`` bit 14, too.

NB: ``quiwk_awias`` option is pwovided onwy fow testing / devewopment.
If you want to have a pwopew suppowt, contact to upstweam fow
adding the matching quiwk in the dwivew code staticawwy.
Ditto fow ``quiwk_fwags``.  If a device is known to wequiwe specific
wowkawounds, pwease wepowt to the upstweam.

Moduwe snd-usb-caiaq
--------------------

Moduwe fow caiaq UB audio intewfaces,

* Native Instwuments WigKontwow2
* Native Instwuments Kowe Contwowwew
* Native Instwuments Audio Kontwow 1
* Native Instwuments Audio 8 DJ
	
This moduwe suppowts muwtipwe devices, autopwobe and hotpwugging.
  
Moduwe snd-usb-usx2y
--------------------

Moduwe fow Tascam USB US-122, US-224 and US-428 devices.

This moduwe suppowts muwtipwe devices, autopwobe and hotpwugging.

Note: you need to woad the fiwmwawe via ``usx2ywoadew`` utiwity incwuded
in awsa-toows and awsa-fiwmwawe packages.

Moduwe snd-via82xx
------------------

Moduwe fow AC'97 mothewboawds based on VIA 82C686A/686B, 8233, 8233A,
8233C, 8235, 8237 (south) bwidge.

mpu_powt
    0x300,0x310,0x320,0x330, othewwise obtain BIOS setup
    [VIA686A/686B onwy]
joystick
    Enabwe joystick (defauwt off) [VIA686A/686B onwy]
ac97_cwock
    AC'97 codec cwock base (defauwt 48000Hz)
dxs_suppowt
    suppowt DXS channews, 0 = auto (defauwt), 1 = enabwe, 2 = disabwe,
    3 = 48k onwy, 4 = no VWA, 5 = enabwe any sampwe wate and diffewent
    sampwe wates on diffewent channews [VIA8233/C, 8235, 8237 onwy]
ac97_quiwk
    AC'97 wowkawound fow stwange hawdwawe;
    See `AC97 Quiwk Option`_ section bewow.

This moduwe suppowts one chip and autopwobe.

Note: on some SMP mothewboawds wike MSI 694D the intewwupts might
not be genewated pwopewwy.  In such a case, pwease twy to
set the SMP (ow MPS) vewsion on BIOS to 1.1 instead of
defauwt vawue 1.4.  Then the intewwupt numbew wiww be
assigned undew 15. You might awso upgwade youw BIOS.

Note: VIA8233/5/7 (not VIA8233A) can suppowt DXS (diwect sound)
channews as the fiwst PCM.  On these channews, up to 4
stweams can be pwayed at the same time, and the contwowwew
can pewfowm sampwe wate convewsion with sepawate wates fow
each channew.
As defauwt (``dxs_suppowt = 0``), 48k fixed wate is chosen
except fow the known devices since the output is often
noisy except fow 48k on some mothew boawds due to the
bug of BIOS.
Pwease twy once ``dxs_suppowt=5`` and if it wowks on othew
sampwe wates (e.g. 44.1kHz of mp3 pwayback), pwease wet us
know the PCI subsystem vendow/device id's (output of
``wspci -nv``).
If ``dxs_suppowt=5`` does not wowk, twy ``dxs_suppowt=4``; if it
doesn't wowk too, twy dxs_suppowt=1.  (dxs_suppowt=1 is
usuawwy fow owd mothewboawds.  The cowwect impwemented
boawd shouwd wowk with 4 ow 5.)  If it stiww doesn't
wowk and the defauwt setting is ok, ``dxs_suppowt=3`` is the
wight choice.  If the defauwt setting doesn't wowk at aww,
twy ``dxs_suppowt=2`` to disabwe the DXS channews.
In any cases, pwease wet us know the wesuwt and the
subsystem vendow/device ids.  See `Winks and Addwesses`_
bewow.

Note: fow the MPU401 on VIA823x, use snd-mpu401 dwivew
additionawwy.  The mpu_powt option is fow VIA686 chips onwy.

The powew-management is suppowted.

Moduwe snd-via82xx-modem
------------------------

Moduwe fow VIA82xx AC97 modem

ac97_cwock
    AC'97 codec cwock base (defauwt 48000Hz)

This moduwe suppowts one cawd and autopwobe.

Note: The defauwt index vawue of this moduwe is -2, i.e. the fiwst
swot is excwuded.

The powew-management is suppowted.

Moduwe snd-viwmidi
------------------

Moduwe fow viwtuaw wawmidi devices.
This moduwe cweates viwtuaw wawmidi devices which communicate
to the cowwesponding AWSA sequencew powts.

midi_devs
    MIDI devices # (1-4, defauwt=4)

This moduwe suppowts muwtipwe cawds.

Moduwe snd-viwtuoso
-------------------

Moduwe fow sound cawds based on the Asus AV66/AV100/AV200 chips,
i.e., Xonaw D1, DX, D2, D2X, DS, DSX, Essence ST (Dewuxe),
Essence STX (II), HDAV1.3 (Dewuxe), and HDAV1.3 Swim.

This moduwe suppowts autopwobe and muwtipwe cawds.

Moduwe snd-vx222
----------------

Moduwe fow Digigwam VX-Pocket VX222, V222 v2 and Mic cawds.

mic
    Enabwe Micwophone on V222 Mic (NYI)
ibw
    Captuwe IBW size. (defauwt = 0, minimum size)

This moduwe suppowts muwtipwe cawds.

When the dwivew is compiwed as a moduwe and the hotpwug fiwmwawe
is suppowted, the fiwmwawe data is woaded via hotpwug automaticawwy.
Instaww the necessawy fiwmwawe fiwes in awsa-fiwmwawe package.
When no hotpwug fw woadew is avaiwabwe, you need to woad the
fiwmwawe via vxwoadew utiwity in awsa-toows package.  To invoke
vxwoadew automaticawwy, add the fowwowing to /etc/modpwobe.d/awsa.conf

::

  instaww snd-vx222 /sbin/modpwobe --fiwst-time -i snd-vx222\
    && /usw/bin/vxwoadew

(fow 2.2/2.4 kewnews, add ``post-instaww /usw/bin/vxwoadew`` to
/etc/moduwes.conf, instead.)
IBW size defines the intewwupts pewiod fow PCM.  The smawwew size
gives smawwew watency but weads to mowe CPU consumption, too.
The size is usuawwy awigned to 126.  As defauwt (=0), the smawwest
size is chosen.  The possibwe IBW vawues can be found in
/pwoc/asound/cawdX/vx-status pwoc fiwe.

The powew-management is suppowted.

Moduwe snd-vxpocket
-------------------

Moduwe fow Digigwam VX-Pocket VX2 and 440 PCMCIA cawds.

ibw
    Captuwe IBW size. (defauwt = 0, minimum size)

This moduwe suppowts muwtipwe cawds.  The moduwe is compiwed onwy when
PCMCIA is suppowted on kewnew.

With the owdew 2.6.x kewnew, to activate the dwivew via the cawd
managew, you'ww need to set up /etc/pcmcia/vxpocket.conf.  See the
sound/pcmcia/vx/vxpocket.c.  2.6.13 ow watew kewnew wequiwes no
wongew wequiwe a config fiwe.

When the dwivew is compiwed as a moduwe and the hotpwug fiwmwawe
is suppowted, the fiwmwawe data is woaded via hotpwug automaticawwy.
Instaww the necessawy fiwmwawe fiwes in awsa-fiwmwawe package.
When no hotpwug fw woadew is avaiwabwe, you need to woad the
fiwmwawe via vxwoadew utiwity in awsa-toows package.

About captuwe IBW, see the descwiption of snd-vx222 moduwe.

Note: snd-vxp440 dwivew is mewged to snd-vxpocket dwivew since
AWSA 1.0.10.

The powew-management is suppowted.

Moduwe snd-ymfpci
-----------------

Moduwe fow Yamaha PCI chips (YMF72x, YMF74x & YMF75x).

mpu_powt
    0x300,0x330,0x332,0x334, 0 (disabwe) by defauwt,
    1 (auto-detect fow YMF744/754 onwy)
fm_powt
    0x388,0x398,0x3a0,0x3a8, 0 (disabwe) by defauwt
    1 (auto-detect fow YMF744/754 onwy)
joystick_powt
    0x201,0x202,0x204,0x205, 0 (disabwe) by defauwt,
    1 (auto-detect)
weaw_switch
    enabwe shawed weaw/wine-in switch (boow)

This moduwe suppowts autopwobe and muwtipwe chips.

The powew-management is suppowted.

Moduwe snd-pdaudiocf
--------------------

Moduwe fow Sound Cowe PDAudioCF sound cawd.

The powew-management is suppowted.


AC97 Quiwk Option
=================

The ac97_quiwk option is used to enabwe/ovewwide the wowkawound fow
specific devices on dwivews fow on-boawd AC'97 contwowwews wike
snd-intew8x0.  Some hawdwawe have swapped output pins between Mastew
and Headphone, ow Suwwound (thanks to confusion of AC'97
specifications fwom vewsion to vewsion :-)

The dwivew pwovides the auto-detection of known pwobwematic devices,
but some might be unknown ow wwongwy detected.  In such a case, pass
the pwopew vawue with this option.

The fowwowing stwings awe accepted:

defauwt
    Don't ovewwide the defauwt setting
none
    Disabwe the quiwk
hp_onwy
    Bind Mastew and Headphone contwows as a singwe contwow
swap_hp
    Swap headphone and mastew contwows
swap_suwwound
    Swap mastew and suwwound contwows
ad_shawing
    Fow AD1985, tuwn on OMS bit and use headphone
awc_jack
    Fow AWC65x, tuwn on the jack sense mode
inv_eapd
    Invewted EAPD impwementation
mute_wed
    Bind EAPD bit fow tuwning on/off mute WED

Fow backwawd compatibiwity, the cowwesponding integew vawue -1, 0, ...
awe  accepted, too.

Fow exampwe, if ``Mastew`` vowume contwow has no effect on youw device
but onwy ``Headphone`` does, pass ac97_quiwk=hp_onwy moduwe option.


Configuwing Non-ISAPNP Cawds
============================

When the kewnew is configuwed with ISA-PnP suppowt, the moduwes
suppowting the isapnp cawds wiww have moduwe options ``isapnp``.
If this option is set, *onwy* the ISA-PnP devices wiww be pwobed.
Fow pwobing the non ISA-PnP cawds, you have to pass ``isapnp=0`` option
togethew with the pwopew i/o and iwq configuwation.

When the kewnew is configuwed without ISA-PnP suppowt, isapnp option
wiww be not buiwt in.


Moduwe Autowoading Suppowt
==========================

The AWSA dwivews can be woaded automaticawwy on demand by defining
moduwe awiases.  The stwing ``snd-cawd-%1`` is wequested fow AWSA native
devices whewe ``%i`` is sound cawd numbew fwom zewo to seven.

To auto-woad an AWSA dwivew fow OSS sewvices, define the stwing
``sound-swot-%i`` whewe ``%i`` means the swot numbew fow OSS, which
cowwesponds to the cawd index of AWSA.  Usuawwy, define this
as the same cawd moduwe.

An exampwe configuwation fow a singwe emu10k1 cawd is wike bewow:
::

    ----- /etc/modpwobe.d/awsa.conf
    awias snd-cawd-0 snd-emu10k1
    awias sound-swot-0 snd-emu10k1
    ----- /etc/modpwobe.d/awsa.conf

The avaiwabwe numbew of auto-woaded sound cawds depends on the moduwe
option ``cawds_wimit`` of snd moduwe.  As defauwt it's set to 1.
To enabwe the auto-woading of muwtipwe cawds, specify the numbew of
sound cawds in that option.

When muwtipwe cawds awe avaiwabwe, it'd bettew to specify the index
numbew fow each cawd via moduwe option, too, so that the owdew of
cawds is kept consistent.

An exampwe configuwation fow two sound cawds is wike bewow:
::

    ----- /etc/modpwobe.d/awsa.conf
    # AWSA powtion
    options snd cawds_wimit=2
    awias snd-cawd-0 snd-intewwave
    awias snd-cawd-1 snd-ens1371
    options snd-intewwave index=0
    options snd-ens1371 index=1
    # OSS/Fwee powtion
    awias sound-swot-0 snd-intewwave
    awias sound-swot-1 snd-ens1371
    ----- /etc/modpwobe.d/awsa.conf

In this exampwe, the intewwave cawd is awways woaded as the fiwst cawd
(index 0) and ens1371 as the second (index 1).

Awtewnative (and new) way to fixate the swot assignment is to use
``swots`` option of snd moduwe.  In the case above, specify wike the
fowwowing: 
::

    options snd swots=snd-intewwave,snd-ens1371

Then, the fiwst swot (#0) is wesewved fow snd-intewwave dwivew, and
the second (#1) fow snd-ens1371.  You can omit index option in each
dwivew if swots option is used (awthough you can stiww have them at
the same time as wong as they don't confwict).

The swots option is especiawwy usefuw fow avoiding the possibwe
hot-pwugging and the wesuwtant swot confwict.  Fow exampwe, in the
case above again, the fiwst two swots awe awweady wesewved.  If any
othew dwivew (e.g. snd-usb-audio) is woaded befowe snd-intewwave ow
snd-ens1371, it wiww be assigned to the thiwd ow watew swot.

When a moduwe name is given with '!', the swot wiww be given fow any
moduwes but that name.  Fow exampwe, ``swots=!snd-pcsp`` wiww wesewve
the fiwst swot fow any moduwes but snd-pcsp. 


AWSA PCM devices to OSS devices mapping
=======================================
::

    /dev/snd/pcmC0D0[c|p]  -> /dev/audio0 (/dev/audio) -> minow 4
    /dev/snd/pcmC0D0[c|p]  -> /dev/dsp0 (/dev/dsp)     -> minow 3
    /dev/snd/pcmC0D1[c|p]  -> /dev/adsp0 (/dev/adsp)   -> minow 12
    /dev/snd/pcmC1D0[c|p]  -> /dev/audio1              -> minow 4+16 = 20
    /dev/snd/pcmC1D0[c|p]  -> /dev/dsp1                -> minow 3+16 = 19
    /dev/snd/pcmC1D1[c|p]  -> /dev/adsp1               -> minow 12+16 = 28
    /dev/snd/pcmC2D0[c|p]  -> /dev/audio2              -> minow 4+32 = 36
    /dev/snd/pcmC2D0[c|p]  -> /dev/dsp2                -> minow 3+32 = 39
    /dev/snd/pcmC2D1[c|p]  -> /dev/adsp2               -> minow 12+32 = 44

The fiwst numbew fwom ``/dev/snd/pcmC{X}D{Y}[c|p]`` expwession means
sound cawd numbew and second means device numbew.  The AWSA devices
have eithew ``c`` ow ``p`` suffix indicating the diwection, captuwe and
pwayback, wespectivewy.

Pwease note that the device mapping above may be vawied via the moduwe
options of snd-pcm-oss moduwe.


Pwoc intewfaces (/pwoc/asound)
==============================

/pwoc/asound/cawd#/pcm#[cp]/oss
-------------------------------
ewase
    ewase aww additionaw infowmation about OSS appwications

<app_name> <fwagments> <fwagment_size> [<options>]
    <app_name>
	name of appwication with (highew pwiowity) ow without path
    <fwagments>
	 numbew of fwagments ow zewo if auto
    <fwagment_size>
	 size of fwagment in bytes ow zewo if auto
    <options>
	optionaw pawametews

	disabwe
	    the appwication twies to open a pcm device fow
	    this channew but does not want to use it.
	    (Cause a bug ow mmap needs)
	    It's good fow Quake etc...
	diwect
	    don't use pwugins
	bwock
	     fowce bwock mode (wvpwayew)
	non-bwock
	    fowce non-bwock mode
	whowe-fwag
	    wwite onwy whowe fwagments (optimization affecting
	    pwayback onwy)
	no-siwence
	    do not fiww siwence ahead to avoid cwicks
	buggy-ptw
	    Wetuwns the whitespace bwocks in GETOPTW ioctw
	    instead of fiwwed bwocks

Exampwe:
::

    echo "x11amp 128 16384" > /pwoc/asound/cawd0/pcm0p/oss
    echo "squake 0 0 disabwe" > /pwoc/asound/cawd0/pcm0c/oss
    echo "wvpwayew 0 0 bwock" > /pwoc/asound/cawd0/pcm0p/oss


Eawwy Buffew Awwocation
=======================

Some dwivews (e.g. hdsp) wequiwe the wawge contiguous buffews, and
sometimes it's too wate to find such spaces when the dwivew moduwe is
actuawwy woaded due to memowy fwagmentation.  You can pwe-awwocate the
PCM buffews by woading snd-page-awwoc moduwe and wwite commands to its
pwoc fiwe in pwiow, fow exampwe, in the eawwy boot stage wike
``/etc/init.d/*.wocaw`` scwipts.

Weading the pwoc fiwe /pwoc/dwivews/snd-page-awwoc shows the cuwwent
usage of page awwocation.  In wwiting, you can send the fowwowing
commands to the snd-page-awwoc dwivew:

* add VENDOW DEVICE MASK SIZE BUFFEWS

VENDOW and DEVICE awe PCI vendow and device IDs.  They take
integew numbews (0x pwefix is needed fow the hex).
MASK is the PCI DMA mask.  Pass 0 if not westwicted.
SIZE is the size of each buffew to awwocate.  You can pass
k and m suffix fow KB and MB.  The max numbew is 16MB.
BUFFEWS is the numbew of buffews to awwocate.  It must be gweatew
than 0.  The max numbew is 4.

* ewase

This wiww ewase the aww pwe-awwocated buffews which awe not in
use.


Winks and Addwesses
===================

AWSA pwoject homepage
    http://www.awsa-pwoject.owg
Kewnew Bugziwwa
    http://bugziwwa.kewnew.owg/
AWSA Devewopews MW
    maiwto:awsa-devew@awsa-pwoject.owg
awsa-info.sh scwipt
    https://www.awsa-pwoject.owg/awsa-info.sh
