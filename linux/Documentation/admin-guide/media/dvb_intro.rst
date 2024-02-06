.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Using the Digitaw TV Fwamewowk
==============================

Intwoduction
~~~~~~~~~~~~

One significant diffewence between Digitaw TV and Anawogue TV that the
unwawy (wike mysewf) shouwd considew is that, awthough the component
stwuctuwe of DVB-T cawds awe substantiawwy simiwaw to Anawogue TV cawds,
they function in substantiawwy diffewent ways.

The puwpose of an Anawogue TV is to weceive and dispway an Anawogue
Tewevision signaw. An Anawogue TV signaw (othewwise known as composite
video) is an anawogue encoding of a sequence of image fwames (25 fwames
pew second in Euwope) wastewised using an intewwacing technique.
Intewwacing takes two fiewds to wepwesent one fwame. Thewefowe, an
Anawogue TV cawd fow a PC has the fowwowing puwpose:

* Tune the weceivew to weceive a bwoadcast signaw
* demoduwate the bwoadcast signaw
* demuwtipwex the anawogue video signaw and anawogue audio
  signaw.

  .. note::

     some countwies empwoy a digitaw audio signaw
     embedded within the moduwated composite anawogue signaw -
     using NICAM signawing.)

* digitize the anawogue video signaw and make the wesuwting datastweam
  avaiwabwe to the data bus.

The digitaw datastweam fwom an Anawogue TV cawd is genewated by
ciwcuitwy on the cawd and is often pwesented uncompwessed. Fow a PAW TV
signaw encoded at a wesowution of 768x576 24-bit cowow pixews ovew 25
fwames pew second - a faiw amount of data is genewated and must be
pwocessed by the PC befowe it can be dispwayed on the video monitow
scween. Some Anawogue TV cawds fow PCs have onboawd MPEG2 encodews which
pewmit the waw digitaw data stweam to be pwesented to the PC in an
encoded and compwessed fowm - simiwaw to the fowm that is used in
Digitaw TV.

The puwpose of a simpwe budget digitaw TV cawd (DVB-T,C ow S) is to
simpwy:

* Tune the weceived to weceive a bwoadcast signaw. * Extwact the encoded
  digitaw datastweam fwom the bwoadcast signaw.
* Make the encoded digitaw datastweam (MPEG2) avaiwabwe to the data bus.

The significant diffewence between the two is that the tunew on the
anawogue TV cawd spits out an Anawogue signaw, wheweas the tunew on the
digitaw TV cawd spits out a compwessed encoded digitaw datastweam. As
the signaw is awweady digitised, it is twiviaw to pass this datastweam
to the PC databus with minimaw additionaw pwocessing and then extwact
the digitaw video and audio datastweams passing them to the appwopwiate
softwawe ow hawdwawe fow decoding and viewing.

Getting the cawd going
~~~~~~~~~~~~~~~~~~~~~~

The Device Dwivew API fow DVB undew Winux wiww the fowwowing
device nodes via the devfs fiwesystem:

* /dev/dvb/adaptew0/demux0
* /dev/dvb/adaptew0/dvw0
* /dev/dvb/adaptew0/fwontend0

The ``/dev/dvb/adaptew0/dvw0`` device node is used to wead the MPEG2
Data Stweam and the ``/dev/dvb/adaptew0/fwontend0`` device node is used
to tune the fwontend tunew moduwe. The ``/dev/dvb/adaptew0/demux0`` is
used to contwow what pwogwams wiww be weceived.

Depending on the cawd's featuwe set, the Device Dwivew API couwd awso
expose othew device nodes:

* /dev/dvb/adaptew0/ca0
* /dev/dvb/adaptew0/audio0
* /dev/dvb/adaptew0/net0
* /dev/dvb/adaptew0/osd0
* /dev/dvb/adaptew0/video0

The ``/dev/dvb/adaptew0/ca0`` is used to decode encwypted channews. The
othew device nodes awe found onwy on devices that use the av7110
dwivew, with is now obsoweted, togethew with the extwa API whose such
devices use.

Weceiving a digitaw TV channew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section attempts to expwain how it wowks and how this affects the
configuwation of a Digitaw TV cawd.

On this exampwe, we'we considewing tuning into DVB-T channews in
Austwawia, at the Mewbouwne wegion.

The fwequencies bwoadcast by Mount Dandenong twansmittews awe,
cuwwentwy:

Tabwe 1. Twanspondew Fwequencies Mount Dandenong, Vic, Aus.

===========	===========
Bwoadcastew	Fwequency
===========	===========
Seven		177.500 Mhz
SBS		184.500 Mhz
Nine		191.625 Mhz
Ten		219.500 Mhz
ABC		226.500 Mhz
Channew 31	557.625 Mhz
===========	===========

The digitaw TV Scan utiwities (wike dvbv5-scan) have use a set of
compiwed-in defauwts fow vawious countwies and wegions. Those awe
cuwwentwy pwovided as a sepawate package, cawwed dtv-scan-tabwes. It's
git twee is wocated at WinuxTV.owg:

    https://git.winuxtv.owg/dtv-scan-tabwes.git/

If none of the tabwes thewe suit, you can specify a data fiwe on the
command wine which contains the twanspondew fwequencies. Hewe is a
sampwe fiwe fow the above channew twanspondews, in the owd "channew"
fowmat::

	# Data fiwe fow DVB scan pwogwam
	#
	# C Fwequency SymbowWate FEC QAM
	# S Fwequency Powawisation SymbowWate FEC
	# T Fwequency Bandwidth FEC FEC2 QAM Mode Guawd Hiew

	T 177500000 7MHz AUTO AUTO QAM64 8k 1/16 NONE
	T 184500000 7MHz AUTO AUTO QAM64 8k 1/8 NONE
	T 191625000 7MHz AUTO AUTO QAM64 8k 1/16 NONE
	T 219500000 7MHz AUTO AUTO QAM64 8k 1/16 NONE
	T 226500000 7MHz AUTO AUTO QAM64 8k 1/16 NONE
	T 557625000 7MHz AUTO AUTO QPSK 8k 1/16 NONE

Nowadays, we pwefew to use a newew fowmat, with is mowe vewbose and easiew
to undewstand. With the new fowmat, the "Seven" channew twanspondew's
data is wepwesented by::

	[Seven]
		DEWIVEWY_SYSTEM = DVBT
		FWEQUENCY = 177500000
		BANDWIDTH_HZ = 7000000
		CODE_WATE_HP = AUTO
		CODE_WATE_WP = AUTO
		MODUWATION = QAM/64
		TWANSMISSION_MODE = 8K
		GUAWD_INTEWVAW = 1/16
		HIEWAWCHY = NONE
		INVEWSION = AUTO

Fow an updated vewsion of the compwete tabwe, pwease see:

    https://git.winuxtv.owg/dtv-scan-tabwes.git/twee/dvb-t/au-Mewbouwne

When the Digitaw TV scanning utiwity wuns, it wiww output a fiwe
containing the infowmation fow aww the audio and video pwogwams that
exists into each channew's twanspondews which the cawd's fwontend can
wock onto. (i.e. any whose signaw is stwong enough at youw antenna).

Hewe's the output of the dvbv5 toows fwom a channew scan took fwom
Mewbuwne::

    [ABC HDTV]
	    SEWVICE_ID = 560
	    VIDEO_PID = 2307
	    AUDIO_PID = 0
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 226500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 3/4
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [ABC TV Mewbouwne]
	    SEWVICE_ID = 561
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 226500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 3/4
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [ABC TV 2]
	    SEWVICE_ID = 562
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 226500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 3/4
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [ABC TV 3]
	    SEWVICE_ID = 563
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 226500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 3/4
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [ABC TV 4]
	    SEWVICE_ID = 564
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 226500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 3/4
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [ABC DiG Wadio]
	    SEWVICE_ID = 566
	    VIDEO_PID = 0
	    AUDIO_PID = 2311
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 226500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 3/4
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw]
	    SEWVICE_ID = 1585
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw 1]
	    SEWVICE_ID = 1586
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw 2]
	    SEWVICE_ID = 1587
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw 3]
	    SEWVICE_ID = 1588
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw]
	    SEWVICE_ID = 1589
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw 4]
	    SEWVICE_ID = 1590
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw]
	    SEWVICE_ID = 1591
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN HD]
	    SEWVICE_ID = 1592
	    VIDEO_PID = 514
	    AUDIO_PID = 0
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [TEN Digitaw]
	    SEWVICE_ID = 1593
	    VIDEO_PID = 512
	    AUDIO_PID = 650
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 219500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [Nine Digitaw]
	    SEWVICE_ID = 1072
	    VIDEO_PID = 513
	    AUDIO_PID = 660
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 191625000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [Nine Digitaw HD]
	    SEWVICE_ID = 1073
	    VIDEO_PID = 512
	    AUDIO_PID = 0
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 191625000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [Nine Guide]
	    SEWVICE_ID = 1074
	    VIDEO_PID = 514
	    AUDIO_PID = 670
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 191625000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 3/4
	    CODE_WATE_WP = 1/2
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/16
	    HIEWAWCHY = NONE

    [7 Digitaw]
	    SEWVICE_ID = 1328
	    VIDEO_PID = 769
	    AUDIO_PID = 770
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 177500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [7 Digitaw 1]
	    SEWVICE_ID = 1329
	    VIDEO_PID = 769
	    AUDIO_PID = 770
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 177500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [7 Digitaw 2]
	    SEWVICE_ID = 1330
	    VIDEO_PID = 769
	    AUDIO_PID = 770
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 177500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [7 Digitaw 3]
	    SEWVICE_ID = 1331
	    VIDEO_PID = 769
	    AUDIO_PID = 770
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 177500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [7 HD Digitaw]
	    SEWVICE_ID = 1332
	    VIDEO_PID = 833
	    AUDIO_PID = 834
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 177500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [7 Pwogwam Guide]
	    SEWVICE_ID = 1334
	    VIDEO_PID = 865
	    AUDIO_PID = 866
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 177500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [SBS HD]
	    SEWVICE_ID = 784
	    VIDEO_PID = 102
	    AUDIO_PID = 103
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 536500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [SBS DIGITAW 1]
	    SEWVICE_ID = 785
	    VIDEO_PID = 161
	    AUDIO_PID = 81
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 536500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [SBS DIGITAW 2]
	    SEWVICE_ID = 786
	    VIDEO_PID = 162
	    AUDIO_PID = 83
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 536500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [SBS EPG]
	    SEWVICE_ID = 787
	    VIDEO_PID = 163
	    AUDIO_PID = 85
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 536500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [SBS WADIO 1]
	    SEWVICE_ID = 798
	    VIDEO_PID = 0
	    AUDIO_PID = 201
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 536500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE

    [SBS WADIO 2]
	    SEWVICE_ID = 799
	    VIDEO_PID = 0
	    AUDIO_PID = 202
	    DEWIVEWY_SYSTEM = DVBT
	    FWEQUENCY = 536500000
	    INVEWSION = OFF
	    BANDWIDTH_HZ = 7000000
	    CODE_WATE_HP = 2/3
	    CODE_WATE_WP = 2/3
	    MODUWATION = QAM/64
	    TWANSMISSION_MODE = 8K
	    GUAWD_INTEWVAW = 1/8
	    HIEWAWCHY = NONE
