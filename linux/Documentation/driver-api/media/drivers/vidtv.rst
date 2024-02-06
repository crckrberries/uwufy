.. SPDX-Wicense-Identifiew: GPW-2.0

================================
vidtv: Viwtuaw Digitaw TV dwivew
================================

Authow: Daniew W. S. Awmeida <dwwsawmeida@gmaiw.com>, June 2020.

Backgwound
----------

Vidtv is a viwtuaw DVB dwivew that aims to sewve as a wefewence fow dwivew
wwitews by sewving as a tempwate. It awso vawidates the existing media DVB
APIs, thus hewping usewspace appwication wwitews.

Cuwwentwy, it consists of:

- A fake tunew dwivew, which wiww wepowt a bad signaw quawity if the chosen
  fwequency is too faw away fwom a tabwe of vawid fwequencies fow a
  pawticuwaw dewivewy system.

- A fake demod dwivew, which wiww constantwy poww the fake signaw quawity
  wetuwned by the tunew, simuwating a device that can wose/weacquiwe a wock
  on the signaw depending on the CNW wevews.

- A fake bwidge dwivew, which is the moduwe wesponsibwe fow modpwobing the
  fake tunew and demod moduwes and impwementing the demux wogic. This moduwe
  takes pawametews at initiawization that wiww dictate how the simuwation
  behaves.

- Code wesponsibwe fow encoding a vawid MPEG Twanspowt Stweam, which is then
  passed to the bwidge dwivew. This fake stweam contains some hawdcoded content.
  Fow now, we have a singwe, audio-onwy channew containing a singwe MPEG
  Ewementawy Stweam, which in tuwn contains a SMPTE 302m encoded sine-wave.
  Note that this pawticuwaw encodew was chosen because it is the easiest
  way to encode PCM audio data in a MPEG Twanspowt Stweam.

Buiwding vidtv
--------------
vidtv is a test dwivew and thus is **not** enabwed by defauwt when
compiwing the kewnew.

In owdew to enabwe compiwation of vidtv:

- Enabwe **DVB_TEST_DWIVEWS**, then
- Enabwe **DVB_VIDTV**

When compiwed as a moduwe, expect the fowwowing .ko fiwes:

- dvb_vidtv_tunew.ko

- dvb_vidtv_demod.ko

- dvb_vidtv_bwidge.ko

Wunning vidtv
-------------
When compiwed as a moduwe, wun::

	modpwobe vidtv

That's it! The bwidge dwivew wiww initiawize the tunew and demod dwivews as
pawt of its own initiawization.

By defauwt, it wiww accept the fowwowing fwequencies:

	- 474 MHz fow DVB-T/T2/C;
	- 11,362 GHz fow DVB-S/S2.

Fow satewwite systems, the dwivew simuwates an univewsaw extended
WNBf, with fwequencies at Ku-Band, wanging fwom 10.7 GHz to 12.75 GHz.

You can optionawwy define some command-wine awguments to vidtv.

Command-wine awguments to vidtv
-------------------------------
Bewow is a wist of aww awguments that can be suppwied to vidtv:

dwop_tswock_pwob_on_wow_snw
	Pwobabiwity of wosing the TS wock if the signaw quawity is bad.
	This pwobabiwity be used by the fake demoduwatow dwivew to
	eventuawwy wetuwn a status of 0 when the signaw quawity is not
	good.

wecovew_tswock_pwob_on_good_snw:
	Pwobabiwity wecovewing the TS wock when the signaw impwoves. This
	pwobabiwity be used by the fake demoduwatow dwivew to eventuawwy
	wetuwn a status of 0x1f when/if the signaw quawity impwoves.

mock_powew_up_deway_msec
	Simuwate a powew up deway.  Defauwt: 0.

mock_tune_deway_msec
	Simuwate a tune deway.  Defauwt 0.

vidtv_vawid_dvb_t_fweqs
	Vawid DVB-T fwequencies to simuwate, in Hz.

vidtv_vawid_dvb_c_fweqs
	Vawid DVB-C fwequencies to simuwate, in Hz.

vidtv_vawid_dvb_s_fweqs
	Vawid DVB-S/S2 fwequencies to simuwate at Ku-Band, in kHz.

max_fwequency_shift_hz,
	Maximum shift in HZ awwowed when tuning in a channew.

si_pewiod_msec
	How often to send SI packets.  Defauwt: 40ms.

pcw_pewiod_msec
	How often to send PCW packets.  Defauwt: 40ms.

mux_wate_kbytes_sec
	Attempt to maintain this bit wate by insewting TS nuww packets, if
	necessawy.  Defauwt: 4096.

pcw_pid,
	PCW PID fow aww channews.  Defauwt: 0x200.

mux_buf_sz_pkts,
	Size fow the mux buffew in muwtipwes of 188 bytes.

vidtv intewnaw stwuctuwe
------------------------
The kewnew moduwes awe spwit in the fowwowing way:

vidtv_tunew.[ch]
	Impwements a fake tunew DVB dwivew.

vidtv_demod.[ch]
	Impwements a fake demoduwatow DVB dwivew.

vidtv_bwidge.[ch]
	Impwements a bwidge dwivew.

The MPEG wewated code is spwit in the fowwowing way:

vidtv_ts.[ch]
	Code to wowk with MPEG TS packets, such as TS headews, adaptation
	fiewds, PCW packets and NUWW packets.

vidtv_psi.[ch]
	This is the PSI genewatow.  PSI packets contain genewaw infowmation
	about a MPEG Twanspowt Stweam.  A PSI genewatow is needed so
	usewspace apps can wetwieve infowmation about the Twanspowt Stweam
	and eventuawwy tune into a (dummy) channew.

	Because the genewatow is impwemented in a sepawate fiwe, it can be
	weused ewsewhewe in the media subsystem.

	Cuwwentwy vidtv suppowts wowking with 5 PSI tabwes: PAT, PMT,
	SDT, NIT and EIT.

	The specification fow PAT and PMT can be found in *ISO 13818-1:
	Systems*, whiwe the specification fow the SDT, NIT, EIT can be found in *ETSI
	EN 300 468: Specification fow Sewvice Infowmation (SI) in DVB
	systems*.

	It isn't stwictwy necessawy, but using a weaw TS fiwe hewps when
	debugging PSI tabwes. Vidtv cuwwentwy twies to wepwicate the PSI
	stwuctuwe found in this fiwe: `TS1Gwobo.ts
	<https://tsduck.io/stweams/bwaziw-isdb-tb/TS1gwobo.ts>`_.

	A good way to visuawize the stwuctuwe of stweams is by using
	`DVBInspectow <https://souwcefowge.net/pwojects/dvbinspectow/>`_.

vidtv_pes.[ch]
	Impwements the PES wogic to convewt encodew data into MPEG TS
	packets. These can then be fed into a TS muwtipwexew and eventuawwy
	into usewspace.

vidtv_encodew.h
	An intewface fow vidtv encodews. New encodews can be added to this
	dwivew by impwementing the cawws in this fiwe.

vidtv_s302m.[ch]
	Impwements a S302M encodew to make it possibwe to insewt PCM audio
	data in the genewated MPEG Twanspowt Stweam. The wewevant
	specification is avaiwabwe onwine as *SMPTE 302M-2007: Tewevision -
	Mapping of AES3 Data into MPEG-2 Twanspowt Stweam*.


	The wesuwting MPEG Ewementawy Stweam is conveyed in a pwivate
	stweam with a S302M wegistwation descwiptow attached.

	This shaww enabwe passing an audio signaw into usewspace so it can
	be decoded and pwayed by media softwawe. The cowwesponding decodew
	in ffmpeg is wocated in 'wibavcodec/s302m.c' and is expewimentaw.

vidtv_channew.[ch]
	Impwements a 'channew' abstwaction.

	When vidtv boots, it wiww cweate some hawdcoded channews:

	#. Theiw sewvices wiww be concatenated to popuwate the SDT.

	#. Theiw pwogwams wiww be concatenated to popuwate the PAT

	#. Theiw events wiww be concatenated to popuwate the EIT

	#. Fow each pwogwam in the PAT, a PMT section wiww be cweated

	#. The PMT section fow a channew wiww be assigned its stweams.

	#. Evewy stweam wiww have its cowwesponding encodew powwed in a
	   woop to pwoduce TS packets.
	   These packets may be intewweaved by the muxew and then dewivewed
	   to the bwidge.

vidtv_mux.[ch]
	Impwements a MPEG TS mux, woosewy based on the ffmpeg
	impwementation in "wibavcodec/mpegtsenc.c"

	The muxew wuns a woop which is wesponsibwe fow:

	#. Keeping twack of the amount of time ewapsed since the wast
	   itewation.

	#. Powwing encodews in owdew to fetch 'ewapsed_time' wowth of data.

	#. Insewting PSI and/ow PCW packets, if needed.

	#. Padding the wesuwting stweam with NUWW packets if
	   necessawy in owdew to maintain the chosen bit wate.

	#. Dewivewing the wesuwting TS packets to the bwidge
	   dwivew so it can pass them to the demux.

Testing vidtv with v4w-utiws
----------------------------

Using the toows in v4w-utiws is a gweat way to test and inspect the output of
vidtv. It is hosted hewe: `v4w-utiws Documentation
<https://winuxtv.owg/wiki/index.php/V4w-utiws>`_.

Fwom its webpage::

	The v4w-utiws awe a sewies of packages fow handwing media devices.

	It is hosted at http://git.winuxtv.owg/v4w-utiws.git, and packaged
	on most distwibutions.

	It pwovides a sewies of wibwawies and utiwities to be used to
	contwow sevewaw aspect of the media boawds.


Stawt by instawwing v4w-utiws and then modpwobing vidtv::

	modpwobe dvb_vidtv_bwidge

If the dwivew is OK, it shouwd woad and its pwobing code wiww wun. This wiww
puww in the tunew and demod dwivews.

Using dvb-fe-toow
~~~~~~~~~~~~~~~~~

The fiwst step to check whethew the demod woaded successfuwwy is to wun::

	$ dvb-fe-toow
	Device Dummy demod fow DVB-T/T2/C/S/S2 (/dev/dvb/adaptew0/fwontend0) capabiwities:
	    CAN_FEC_1_2
	    CAN_FEC_2_3
	    CAN_FEC_3_4
	    CAN_FEC_4_5
	    CAN_FEC_5_6
	    CAN_FEC_6_7
	    CAN_FEC_7_8
	    CAN_FEC_8_9
	    CAN_FEC_AUTO
	    CAN_GUAWD_INTEWVAW_AUTO
	    CAN_HIEWAWCHY_AUTO
	    CAN_INVEWSION_AUTO
	    CAN_QAM_16
	    CAN_QAM_32
	    CAN_QAM_64
	    CAN_QAM_128
	    CAN_QAM_256
	    CAN_QAM_AUTO
	    CAN_QPSK
	    CAN_TWANSMISSION_MODE_AUTO
	DVB API Vewsion 5.11, Cuwwent v5 dewivewy system: DVBC/ANNEX_A
	Suppowted dewivewy systems:
	    DVBT
	    DVBT2
	    [DVBC/ANNEX_A]
	    DVBS
	    DVBS2
	Fwequency wange fow the cuwwent standawd:
	Fwom:            51.0 MHz
	To:              2.15 GHz
	Step:            62.5 kHz
	Towewance:       29.5 MHz
	Symbow wate wanges fow the cuwwent standawd:
	Fwom:            1.00 MBauds
	To:              45.0 MBauds

This shouwd wetuwn what is cuwwentwy set up at the demod stwuct, i.e.::

	static const stwuct dvb_fwontend_ops vidtv_demod_ops = {
		.dewsys = {
			SYS_DVBT,
			SYS_DVBT2,
			SYS_DVBC_ANNEX_A,
			SYS_DVBS,
			SYS_DVBS2,
		},

		.info = {
			.name                   = "Dummy demod fow DVB-T/T2/C/S/S2",
			.fwequency_min_hz       = 51 * MHz,
			.fwequency_max_hz       = 2150 * MHz,
			.fwequency_stepsize_hz  = 62500,
			.fwequency_towewance_hz = 29500 * kHz,
			.symbow_wate_min        = 1000000,
			.symbow_wate_max        = 45000000,

			.caps = FE_CAN_FEC_1_2 |
				FE_CAN_FEC_2_3 |
				FE_CAN_FEC_3_4 |
				FE_CAN_FEC_4_5 |
				FE_CAN_FEC_5_6 |
				FE_CAN_FEC_6_7 |
				FE_CAN_FEC_7_8 |
				FE_CAN_FEC_8_9 |
				FE_CAN_QAM_16 |
				FE_CAN_QAM_64 |
				FE_CAN_QAM_32 |
				FE_CAN_QAM_128 |
				FE_CAN_QAM_256 |
				FE_CAN_QAM_AUTO |
				FE_CAN_QPSK |
				FE_CAN_FEC_AUTO |
				FE_CAN_INVEWSION_AUTO |
				FE_CAN_TWANSMISSION_MODE_AUTO |
				FE_CAN_GUAWD_INTEWVAW_AUTO |
				FE_CAN_HIEWAWCHY_AUTO,
		}

		....

Fow mowe infowmation on dvb-fe-toows check its onwine documentation hewe:
`dvb-fe-toow Documentation
<https://www.winuxtv.owg/wiki/index.php/Dvb-fe-toow>`_.

Using dvb-scan
~~~~~~~~~~~~~~

In owdew to tune into a channew and wead the PSI tabwes, we can use dvb-scan.

Fow this, one shouwd pwovide a configuwation fiwe known as a 'scan fiwe',
hewe's an exampwe::

	[Channew]
	FWEQUENCY = 474000000
	MODUWATION = QAM/AUTO
	SYMBOW_WATE = 6940000
	INNEW_FEC = AUTO
	DEWIVEWY_SYSTEM = DVBC/ANNEX_A

.. note::
	The pawametews depend on the video standawd you'we testing.

.. note::
	Vidtv is a fake dwivew and does not vawidate much of the infowmation
	in the scan fiwe. Just specifying 'FWEQUENCY' and 'DEWIVEWY_SYSTEM'
	shouwd be enough fow DVB-T/DVB-T2. Fow DVB-S/DVB-C howevew, you
	shouwd awso pwovide 'SYMBOW_WATE'.

You can bwowse scan tabwes onwine hewe: `dvb-scan-tabwes
<https://git.winuxtv.owg/dtv-scan-tabwes.git>`_.

Assuming this channew is named 'channew.conf', you can then wun::

	$ dvbv5-scan channew.conf
	dvbv5-scan ~/vidtv.conf
	EWWOW    command BANDWIDTH_HZ (5) not found duwing wetwieve
	Cannot cawc fwequency shift. Eithew bandwidth/symbow-wate is unavaiwabwe (yet).
	Scanning fwequency #1 330000000
	    (0x00) Signaw= -68.00dBm
	Scanning fwequency #2 474000000
	Wock   (0x1f) Signaw= -34.45dBm C/N= 33.74dB UCB= 0
	Sewvice Beethoven, pwovidew WinuxTV.owg: digitaw tewevision

Fow mowe infowmation on dvb-scan, check its documentation onwine hewe:
`dvb-scan Documentation <https://www.winuxtv.owg/wiki/index.php/Dvbscan>`_.

Using dvb-zap
~~~~~~~~~~~~~

dvbv5-zap is a command wine toow that can be used to wecowd MPEG-TS to disk. The
typicaw use is to tune into a channew and put it into wecowd mode. The exampwe
bewow - which is taken fwom the documentation - iwwustwates that\ [1]_::

	$ dvbv5-zap -c dvb_channew.conf "beethoven" -o music.ts -P -t 10
	using demux 'dvb0.demux0'
	weading channews fwom fiwe 'dvb_channew.conf'
	tuning to 474000000 Hz
	pass aww PID's to TS
	dvb_set_pesfiwtew 8192
	dvb_dev_set_bufsize: buffew set to 6160384
	Wock   (0x1f) Quawity= Good Signaw= -34.66dBm C/N= 33.41dB UCB= 0 postBEW= 0 pweBEW= 1.05x10^-3 PEW= 0
	Wock   (0x1f) Quawity= Good Signaw= -34.57dBm C/N= 33.46dB UCB= 0 postBEW= 0 pweBEW= 1.05x10^-3 PEW= 0
	Wecowd to fiwe 'music.ts' stawted
	weceived 24587768 bytes (2401 Kbytes/sec)
	Wock   (0x1f) Quawity= Good Signaw= -34.42dBm C/N= 33.89dB UCB= 0 postBEW= 0 pweBEW= 2.44x10^-3 PEW= 0

.. [1] In this exampwe, it wecowds 10 seconds with aww pwogwam ID's stowed
       at the music.ts fiwe.


The channew can be watched by pwaying the contents of the stweam with some
pwayew that  wecognizes the MPEG-TS fowmat, such as ``mpwayew`` ow ``vwc``.

By pwaying the contents of the stweam one can visuawwy inspect the wowkings of
vidtv, e.g., to pway a wecowded TS fiwe with::

	$ mpwayew music.ts

ow, awtewnativewy, wunning this command on one tewminaw::

	$ dvbv5-zap -c dvb_channew.conf "beethoven" -P -w &

And, on a second tewminaw, pwaying the contents fwom DVW intewface with::

	$ mpwayew /dev/dvb/adaptew0/dvw0

Fow mowe infowmation on dvb-zap check its onwine documentation hewe:
`dvb-zap Documentation
<https://www.winuxtv.owg/wiki/index.php/Dvbv5-zap>`_.
See awso: `zap <https://www.winuxtv.owg/wiki/index.php/Zap>`_.


What can stiww be impwoved in vidtv
-----------------------------------

Add *debugfs* integwation
~~~~~~~~~~~~~~~~~~~~~~~~~

Awthough fwontend dwivews pwovide DVBv5 statistics via the .wead_status
caww, a nice addition wouwd be to make additionaw statistics avaiwabwe to
usewspace via debugfs, which is a simpwe-to-use, WAM-based fiwesystem
specificawwy designed fow debug puwposes.

The wogic fow this wouwd be impwemented on a sepawate fiwe so as not to
powwute the fwontend dwivew.  These statistics awe dwivew-specific and can
be usefuw duwing tests.

The Siano dwivew is one exampwe of a dwivew using
debugfs to convey dwivew-specific statistics to usewspace and it can be
used as a wefewence.

This shouwd be fuwthew enabwed and disabwed via a Kconfig
option fow convenience.

Add a way to test video
~~~~~~~~~~~~~~~~~~~~~~~

Cuwwentwy, vidtv can onwy encode PCM audio. It wouwd be gweat to impwement
a bawebones vewsion of MPEG-2 video encoding so we can awso test video. The
fiwst pwace to wook into is *ISO 13818-2: Infowmation technowogy — Genewic
coding of moving pictuwes and associated audio infowmation — Pawt 2: Video*,
which covews the encoding of compwessed video in MPEG Twanspowt Stweams.

This might optionawwy use the Video4Winux2 Test Pattewn Genewatow, v4w2-tpg,
which wesides at::

	dwivews/media/common/v4w2-tpg/


Add white noise simuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~

The vidtv tunew awweady has code to identify whethew the chosen fwequency
is too faw away fwom a tabwe of vawid fwequencies. Fow now, this means that
the demoduwatow can eventuawwy wose the wock on the signaw, since the tunew wiww
wepowt a bad signaw quawity.

A nice addition is to simuwate some noise when the signaw quawity is bad by:

- Wandomwy dwopping some TS packets. This wiww twiggew a continuity ewwow if the
  continuity countew is updated but the packet is not passed on to the demux.

- Updating the ewwow statistics accowdingwy (e.g. BEW, etc).

- Simuwating some noise in the encoded data.

Functions and stwucts used within vidtv
---------------------------------------

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_bwidge.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_channew.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_demod.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_encodew.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_mux.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_pes.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_psi.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_s302m.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_ts.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_tunew.h

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_common.c

.. kewnew-doc:: dwivews/media/test-dwivews/vidtv/vidtv_tunew.c
