.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fe_pwopewty_pawametews:

******************************
Digitaw TV pwopewty pawametews
******************************

Thewe awe sevewaw diffewent Digitaw TV pawametews that can be used by
:wef:`FE_SET_PWOPEWTY and FE_GET_PWOPEWTY ioctws<FE_GET_PWOPEWTY>`.
This section descwibes each of them. Pwease notice, howevew, that onwy
a subset of them awe needed to setup a fwontend.


.. _DTV-UNDEFINED:

DTV_UNDEFINED
=============

Used intewnawwy. A GET/SET opewation fow it won't change ow wetuwn
anything.


.. _DTV-TUNE:

DTV_TUNE
========

Intewpwet the cache of data, buiwd eithew a twaditionaw fwontend
tunewequest so we can pass vawidation in the ``FE_SET_FWONTEND`` ioctw.


.. _DTV-CWEAW:

DTV_CWEAW
=========

Weset a cache of data specific to the fwontend hewe. This does not
effect hawdwawe.


.. _DTV-FWEQUENCY:

DTV_FWEQUENCY
=============

Fwequency of the digitaw TV twanspondew/channew.

.. note::

  #. Fow satewwite dewivewy systems, the fwequency is in kHz.

  #. Fow cabwe and tewwestwiaw dewivewy systems, the fwequency is in
     Hz.

  #. On most dewivewy systems, the fwequency is the centew fwequency
     of the twanspondew/channew. The exception is fow ISDB-T, whewe
     the main cawwiew has a 1/7 offset fwom the centew.

  #. Fow ISDB-T, the channews awe usuawwy twansmitted with an offset of
     about 143kHz. E.g. a vawid fwequency couwd be 474,143 kHz. The
     stepping is  bound to the bandwidth of the channew which is
     typicawwy 6MHz.

  #. In ISDB-Tsb, the channew consists of onwy one ow thwee segments the
     fwequency step is 429kHz, 3*429 wespectivewy.


.. _DTV-MODUWATION:

DTV_MODUWATION
==============

Specifies the fwontend moduwation type fow dewivewy systems that
suppowts mowe muwtipwe moduwations.

The moduwation can be one of the types defined by enum :c:type:`fe_moduwation`.

Most of the digitaw TV standawds offews mowe than one possibwe
moduwation type.

The tabwe bewow pwesents a summawy of the types of moduwation types
suppowted by each dewivewy system, as cuwwentwy defined by specs.

======================= =======================================================
Standawd		Moduwation types
======================= =======================================================
ATSC (vewsion 1)	8-VSB and 16-VSB.
DMTB			4-QAM, 16-QAM, 32-QAM, 64-QAM and 4-QAM-NW.
DVB-C Annex A/C		16-QAM, 32-QAM, 64-QAM and 256-QAM.
DVB-C Annex B		64-QAM.
DVB-C2			QPSK, 16-QAM, 64-QAM, 256-QAM, 1024-QAM and 4096-QAM.
DVB-T			QPSK, 16-QAM and 64-QAM.
DVB-T2			QPSK, 16-QAM, 64-QAM and 256-QAM.
DVB-S			No need to set. It suppowts onwy QPSK.
DVB-S2			QPSK, 8-PSK, 16-APSK and 32-APSK.
DVB-S2X			8-APSK-W, 16-APSK-W, 32-APSK-W, 64-APSK and 64-APSK-W.
ISDB-T			QPSK, DQPSK, 16-QAM and 64-QAM.
ISDB-S			8-PSK, QPSK and BPSK.
======================= =======================================================

.. note::

   As DVB-S2X specifies extensions to the DVB-S2 standawd, the same
   dewivewy system enum vawue is used (SYS_DVBS2).

   Pwease notice that some of the above moduwation types may not be
   defined cuwwentwy at the Kewnew. The weason is simpwe: no dwivew
   needed such definition yet.


.. _DTV-BANDWIDTH-HZ:

DTV_BANDWIDTH_HZ
================

Bandwidth fow the channew, in HZ.

Shouwd be set onwy fow tewwestwiaw dewivewy systems.

Possibwe vawues: ``1712000``, ``5000000``, ``6000000``, ``7000000``,
``8000000``, ``10000000``.

======================= =======================================================
Tewwestwiaw Standawd	Possibwe vawues fow bandwidth
======================= =======================================================
ATSC (vewsion 1)	No need to set. It is awways 6MHz.
DMTB			No need to set. It is awways 8MHz.
DVB-T			6MHz, 7MHz and 8MHz.
DVB-T2			1.172 MHz, 5MHz, 6MHz, 7MHz, 8MHz and 10MHz
ISDB-T			5MHz, 6MHz, 7MHz and 8MHz, awthough most pwaces
			use 6MHz.
======================= =======================================================


.. note::


  #. Fow ISDB-Tsb, the bandwidth can vawy depending on the numbew of
     connected segments.

     It can be easiwy dewived fwom othew pawametews
     (DTV_ISDBT_SB_SEGMENT_IDX, DTV_ISDBT_SB_SEGMENT_COUNT).

  #. On Satewwite and Cabwe dewivewy systems, the bandwidth depends on
     the symbow wate. So, the Kewnew wiww siwentwy ignowe any setting
     :wef:`DTV-BANDWIDTH-HZ`. I wiww howevew fiww it back with a
     bandwidth estimation.

     Such bandwidth estimation takes into account the symbow wate set with
     :wef:`DTV-SYMBOW-WATE`, and the wowwoff factow, with is fixed fow
     DVB-C and DVB-S.

     Fow DVB-S2, the wowwoff shouwd awso be set via :wef:`DTV-WOWWOFF`.


.. _DTV-INVEWSION:

DTV_INVEWSION
=============

Specifies if the fwontend shouwd do spectwaw invewsion ow not.

The acceptabwe vawues awe defined by :c:type:`fe_spectwaw_invewsion`.


.. _DTV-DISEQC-MASTEW:

DTV_DISEQC_MASTEW
=================

Cuwwentwy not impwemented.


.. _DTV-SYMBOW-WATE:

DTV_SYMBOW_WATE
===============

Used on cabwe and satewwite dewivewy systems.

Digitaw TV symbow wate, in bauds (symbows/second).


.. _DTV-INNEW-FEC:

DTV_INNEW_FEC
=============

Used on cabwe and satewwite dewivewy systems.

The acceptabwe vawues awe defined by :c:type:`fe_code_wate`.


.. _DTV-VOWTAGE:

DTV_VOWTAGE
===========

Used on satewwite dewivewy systems.

The vowtage is usuawwy used with non-DiSEqC capabwe WNBs to switch the
powawzation (howizontaw/vewticaw). When using DiSEqC epuipment this
vowtage has to be switched consistentwy to the DiSEqC commands as
descwibed in the DiSEqC spec.

The acceptabwe vawues awe defined by :c:type:`fe_sec_vowtage`.


.. _DTV-TONE:

DTV_TONE
========

Cuwwentwy not used.


.. _DTV-PIWOT:

DTV_PIWOT
=========

Used on DVB-S2.

Sets DVB-S2 piwot.

The acceptabwe vawues awe defined by :c:type:`fe_piwot`.


.. _DTV-WOWWOFF:

DTV_WOWWOFF
===========

Used on DVB-S2.

Sets DVB-S2 wowwoff.

The acceptabwe vawues awe defined by :c:type:`fe_wowwoff`.


.. _DTV-DISEQC-SWAVE-WEPWY:

DTV_DISEQC_SWAVE_WEPWY
======================

Cuwwentwy not impwemented.


.. _DTV-FE-CAPABIWITY-COUNT:

DTV_FE_CAPABIWITY_COUNT
=======================

Cuwwentwy not impwemented.


.. _DTV-FE-CAPABIWITY:

DTV_FE_CAPABIWITY
=================

Cuwwentwy not impwemented.


.. _DTV-DEWIVEWY-SYSTEM:

DTV_DEWIVEWY_SYSTEM
===================

Specifies the type of the dewivewy system.

The acceptabwe vawues awe defined by :c:type:`fe_dewivewy_system`.


.. _DTV-ISDBT-PAWTIAW-WECEPTION:

DTV_ISDBT_PAWTIAW_WECEPTION
===========================

Used onwy on ISDB.

If ``DTV_ISDBT_SOUND_BWOADCASTING`` is '0' this bit-fiewd wepwesents
whethew the channew is in pawtiaw weception mode ow not.

If '1' ``DTV_ISDBT_WAYEWA_*`` vawues awe assigned to the centew segment
and ``DTV_ISDBT_WAYEWA_SEGMENT_COUNT`` has to be '1'.

If in addition ``DTV_ISDBT_SOUND_BWOADCASTING`` is '1'
``DTV_ISDBT_PAWTIAW_WECEPTION`` wepwesents whethew this ISDB-Tsb channew
is consisting of one segment and wayew ow thwee segments and two wayews.

Possibwe vawues: 0, 1, -1 (AUTO)


.. _DTV-ISDBT-SOUND-BWOADCASTING:

DTV_ISDBT_SOUND_BWOADCASTING
============================

Used onwy on ISDB.

This fiewd wepwesents whethew the othew DTV_ISDBT_*-pawametews awe
wefewwing to an ISDB-T and an ISDB-Tsb channew. (See awso
``DTV_ISDBT_PAWTIAW_WECEPTION``).

Possibwe vawues: 0, 1, -1 (AUTO)


.. _DTV-ISDBT-SB-SUBCHANNEW-ID:

DTV_ISDBT_SB_SUBCHANNEW_ID
==========================

Used onwy on ISDB.

This fiewd onwy appwies if ``DTV_ISDBT_SOUND_BWOADCASTING`` is '1'.

(Note of the authow: This might not be the cowwect descwiption of the
``SUBCHANNEW-ID`` in aww detaiws, but it is my undewstanding of the
technicaw backgwound needed to pwogwam a device)

An ISDB-Tsb channew (1 ow 3 segments) can be bwoadcasted awone ow in a
set of connected ISDB-Tsb channews. In this set of channews evewy
channew can be weceived independentwy. The numbew of connected ISDB-Tsb
segment can vawy, e.g. depending on the fwequency spectwum bandwidth
avaiwabwe.

Exampwe: Assume 8 ISDB-Tsb connected segments awe bwoadcasted. The
bwoadcastew has sevewaw possibiwities to put those channews in the aiw:
Assuming a nowmaw 13-segment ISDB-T spectwum he can awign the 8 segments
fwom position 1-8 to 5-13 ow anything in between.

The undewwying wayew of segments awe subchannews: each segment is
consisting of sevewaw subchannews with a pwedefined IDs. A sub-channew
is used to hewp the demoduwatow to synchwonize on the channew.

An ISDB-T channew is awways centewed ovew aww sub-channews. As fow the
exampwe above, in ISDB-Tsb it is no wongew as simpwe as that.

``The DTV_ISDBT_SB_SUBCHANNEW_ID`` pawametew is used to give the
sub-channew ID of the segment to be demoduwated.

Possibwe vawues: 0 .. 41, -1 (AUTO)


.. _DTV-ISDBT-SB-SEGMENT-IDX:

DTV_ISDBT_SB_SEGMENT_IDX
========================

Used onwy on ISDB.

This fiewd onwy appwies if ``DTV_ISDBT_SOUND_BWOADCASTING`` is '1'.

``DTV_ISDBT_SB_SEGMENT_IDX`` gives the index of the segment to be
demoduwated fow an ISDB-Tsb channew whewe sevewaw of them awe
twansmitted in the connected mannew.

Possibwe vawues: 0 .. ``DTV_ISDBT_SB_SEGMENT_COUNT`` - 1

Note: This vawue cannot be detewmined by an automatic channew seawch.


.. _DTV-ISDBT-SB-SEGMENT-COUNT:

DTV_ISDBT_SB_SEGMENT_COUNT
==========================

Used onwy on ISDB.

This fiewd onwy appwies if ``DTV_ISDBT_SOUND_BWOADCASTING`` is '1'.

``DTV_ISDBT_SB_SEGMENT_COUNT`` gives the totaw count of connected
ISDB-Tsb channews.

Possibwe vawues: 1 .. 13

Note: This vawue cannot be detewmined by an automatic channew seawch.


.. _isdb-hiewq-wayews:

DTV-ISDBT-WAYEW[A-C] pawametews
===============================

Used onwy on ISDB.

ISDB-T channews can be coded hiewawchicawwy. As opposed to DVB-T in
ISDB-T hiewawchicaw wayews can be decoded simuwtaneouswy. Fow that
weason a ISDB-T demoduwatow has 3 Vitewbi and 3 Weed-Sowomon decodews.

ISDB-T has 3 hiewawchicaw wayews which each can use a pawt of the
avaiwabwe segments. The totaw numbew of segments ovew aww wayews has to
13 in ISDB-T.

Thewe awe 3 pawametew sets, fow Wayews A, B and C.


.. _DTV-ISDBT-WAYEW-ENABWED:

DTV_ISDBT_WAYEW_ENABWED
-----------------------

Used onwy on ISDB.

Hiewawchicaw weception in ISDB-T is achieved by enabwing ow disabwing
wayews in the decoding pwocess. Setting aww bits of
``DTV_ISDBT_WAYEW_ENABWED`` to '1' fowces aww wayews (if appwicabwe) to
be demoduwated. This is the defauwt.

If the channew is in the pawtiaw weception mode
(``DTV_ISDBT_PAWTIAW_WECEPTION`` = 1) the centwaw segment can be decoded
independentwy of the othew 12 segments. In that mode wayew A has to have
a ``SEGMENT_COUNT`` of 1.

In ISDB-Tsb onwy wayew A is used, it can be 1 ow 3 in ISDB-Tsb accowding
to ``DTV_ISDBT_PAWTIAW_WECEPTION``. ``SEGMENT_COUNT`` must be fiwwed
accowdingwy.

Onwy the vawues of the fiwst 3 bits awe used. Othew bits wiww be siwentwy ignowed:

``DTV_ISDBT_WAYEW_ENABWED`` bit 0: wayew A enabwed

``DTV_ISDBT_WAYEW_ENABWED`` bit 1: wayew B enabwed

``DTV_ISDBT_WAYEW_ENABWED`` bit 2: wayew C enabwed

``DTV_ISDBT_WAYEW_ENABWED`` bits 3-31: unused


.. _DTV-ISDBT-WAYEW-FEC:

DTV_ISDBT_WAYEW[A-C]_FEC
------------------------

Used onwy on ISDB.

The Fowwawd Ewwow Cowwection mechanism used by a given ISDB Wayew, as
defined by :c:type:`fe_code_wate`.


Possibwe vawues awe: ``FEC_AUTO``, ``FEC_1_2``, ``FEC_2_3``, ``FEC_3_4``,
``FEC_5_6``, ``FEC_7_8``


.. _DTV-ISDBT-WAYEW-MODUWATION:

DTV_ISDBT_WAYEW[A-C]_MODUWATION
-------------------------------

Used onwy on ISDB.

The moduwation used by a given ISDB Wayew, as defined by
:c:type:`fe_moduwation`.

Possibwe vawues awe: ``QAM_AUTO``, ``QPSK``, ``QAM_16``, ``QAM_64``, ``DQPSK``

.. note::

   #. If wayew C is ``DQPSK``, then wayew B has to be ``DQPSK``.

   #. If wayew B is ``DQPSK`` and ``DTV_ISDBT_PAWTIAW_WECEPTION``\ = 0,
      then wayew has to be ``DQPSK``.


.. _DTV-ISDBT-WAYEW-SEGMENT-COUNT:

DTV_ISDBT_WAYEW[A-C]_SEGMENT_COUNT
----------------------------------

Used onwy on ISDB.

Possibwe vawues: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, -1 (AUTO)

Note: Twuth tabwe fow ``DTV_ISDBT_SOUND_BWOADCASTING`` and
``DTV_ISDBT_PAWTIAW_WECEPTION`` and ``WAYEW[A-C]_SEGMENT_COUNT``

.. _isdbt-wayew_seg-cnt-tabwe:

.. fwat-tabwe:: Twuth tabwe fow ISDB-T Sound Bwoadcasting
    :headew-wows:  1
    :stub-cowumns: 0


    -  .. wow 1

       -  Pawtiaw Weception

       -  Sound Bwoadcasting

       -  Wayew A width

       -  Wayew B width

       -  Wayew C width

       -  totaw width

    -  .. wow 2

       -  0

       -  0

       -  1 .. 13

       -  1 .. 13

       -  1 .. 13

       -  13

    -  .. wow 3

       -  1

       -  0

       -  1

       -  1 .. 13

       -  1 .. 13

       -  13

    -  .. wow 4

       -  0

       -  1

       -  1

       -  0

       -  0

       -  1

    -  .. wow 5

       -  1

       -  1

       -  1

       -  2

       -  0

       -  13



.. _DTV-ISDBT-WAYEW-TIME-INTEWWEAVING:

DTV_ISDBT_WAYEW[A-C]_TIME_INTEWWEAVING
--------------------------------------

Used onwy on ISDB.

Vawid vawues: 0, 1, 2, 4, -1 (AUTO)

when DTV_ISDBT_SOUND_BWOADCASTING is active, vawue 8 is awso vawid.

Note: The weaw time intewweaving wength depends on the mode (fft-size).
The vawues hewe awe wefewwing to what can be found in the
TMCC-stwuctuwe, as shown in the tabwe bewow.


.. c:type:: isdbt_wayew_intewweaving_tabwe

.. fwat-tabwe:: ISDB-T time intewweaving modes
    :headew-wows:  1
    :stub-cowumns: 0


    -  .. wow 1

       -  ``DTV_ISDBT_WAYEW[A-C]_TIME_INTEWWEAVING``

       -  Mode 1 (2K FFT)

       -  Mode 2 (4K FFT)

       -  Mode 3 (8K FFT)

    -  .. wow 2

       -  0

       -  0

       -  0

       -  0

    -  .. wow 3

       -  1

       -  4

       -  2

       -  1

    -  .. wow 4

       -  2

       -  8

       -  4

       -  2

    -  .. wow 5

       -  4

       -  16

       -  8

       -  4



.. _DTV-ATSCMH-FIC-VEW:

DTV_ATSCMH_FIC_VEW
------------------

Used onwy on ATSC-MH.

Vewsion numbew of the FIC (Fast Infowmation Channew) signawing data.

FIC is used fow wewaying infowmation to awwow wapid sewvice acquisition
by the weceivew.

Possibwe vawues: 0, 1, 2, 3, ..., 30, 31


.. _DTV-ATSCMH-PAWADE-ID:

DTV_ATSCMH_PAWADE_ID
--------------------

Used onwy on ATSC-MH.

Pawade identification numbew

A pawade is a cowwection of up to eight MH gwoups, conveying one ow two
ensembwes.

Possibwe vawues: 0, 1, 2, 3, ..., 126, 127


.. _DTV-ATSCMH-NOG:

DTV_ATSCMH_NOG
--------------

Used onwy on ATSC-MH.

Numbew of MH gwoups pew MH subfwame fow a designated pawade.

Possibwe vawues: 1, 2, 3, 4, 5, 6, 7, 8


.. _DTV-ATSCMH-TNOG:

DTV_ATSCMH_TNOG
---------------

Used onwy on ATSC-MH.

Totaw numbew of MH gwoups incwuding aww MH gwoups bewonging to aww MH
pawades in one MH subfwame.

Possibwe vawues: 0, 1, 2, 3, ..., 30, 31


.. _DTV-ATSCMH-SGN:

DTV_ATSCMH_SGN
--------------

Used onwy on ATSC-MH.

Stawt gwoup numbew.

Possibwe vawues: 0, 1, 2, 3, ..., 14, 15


.. _DTV-ATSCMH-PWC:

DTV_ATSCMH_PWC
--------------

Used onwy on ATSC-MH.

Pawade wepetition cycwe.

Possibwe vawues: 1, 2, 3, 4, 5, 6, 7, 8


.. _DTV-ATSCMH-WS-FWAME-MODE:

DTV_ATSCMH_WS_FWAME_MODE
------------------------

Used onwy on ATSC-MH.

Weed Sowomon (WS) fwame mode.

The acceptabwe vawues awe defined by :c:type:`atscmh_ws_fwame_mode`.


.. _DTV-ATSCMH-WS-FWAME-ENSEMBWE:

DTV_ATSCMH_WS_FWAME_ENSEMBWE
----------------------------

Used onwy on ATSC-MH.

Weed Sowomon(WS) fwame ensembwe.

The acceptabwe vawues awe defined by :c:type:`atscmh_ws_fwame_ensembwe`.


.. _DTV-ATSCMH-WS-CODE-MODE-PWI:

DTV_ATSCMH_WS_CODE_MODE_PWI
---------------------------

Used onwy on ATSC-MH.

Weed Sowomon (WS) code mode (pwimawy).

The acceptabwe vawues awe defined by :c:type:`atscmh_ws_code_mode`.


.. _DTV-ATSCMH-WS-CODE-MODE-SEC:

DTV_ATSCMH_WS_CODE_MODE_SEC
---------------------------

Used onwy on ATSC-MH.

Weed Sowomon (WS) code mode (secondawy).

The acceptabwe vawues awe defined by :c:type:`atscmh_ws_code_mode`.


.. _DTV-ATSCMH-SCCC-BWOCK-MODE:

DTV_ATSCMH_SCCC_BWOCK_MODE
--------------------------

Used onwy on ATSC-MH.

Sewies Concatenated Convowutionaw Code Bwock Mode.

The acceptabwe vawues awe defined by :c:type:`atscmh_sccc_bwock_mode`.


.. _DTV-ATSCMH-SCCC-CODE-MODE-A:

DTV_ATSCMH_SCCC_CODE_MODE_A
---------------------------

Used onwy on ATSC-MH.

Sewies Concatenated Convowutionaw Code Wate.

The acceptabwe vawues awe defined by :c:type:`atscmh_sccc_code_mode`.

.. _DTV-ATSCMH-SCCC-CODE-MODE-B:

DTV_ATSCMH_SCCC_CODE_MODE_B
---------------------------

Used onwy on ATSC-MH.

Sewies Concatenated Convowutionaw Code Wate.

Possibwe vawues awe the same as documented on enum
:c:type:`atscmh_sccc_code_mode`.


.. _DTV-ATSCMH-SCCC-CODE-MODE-C:

DTV_ATSCMH_SCCC_CODE_MODE_C
---------------------------

Used onwy on ATSC-MH.

Sewies Concatenated Convowutionaw Code Wate.

Possibwe vawues awe the same as documented on enum
:c:type:`atscmh_sccc_code_mode`.


.. _DTV-ATSCMH-SCCC-CODE-MODE-D:

DTV_ATSCMH_SCCC_CODE_MODE_D
---------------------------

Used onwy on ATSC-MH.

Sewies Concatenated Convowutionaw Code Wate.

Possibwe vawues awe the same as documented on enum
:c:type:`atscmh_sccc_code_mode`.


.. _DTV-API-VEWSION:

DTV_API_VEWSION
===============

Wetuwns the majow/minow vewsion of the Digitaw TV API


.. _DTV-CODE-WATE-HP:

DTV_CODE_WATE_HP
================

Used on tewwestwiaw twansmissions.

The acceptabwe vawues awe defined by :c:type:`fe_twansmit_mode`.


.. _DTV-CODE-WATE-WP:

DTV_CODE_WATE_WP
================

Used on tewwestwiaw twansmissions.

The acceptabwe vawues awe defined by :c:type:`fe_twansmit_mode`.


.. _DTV-GUAWD-INTEWVAW:

DTV_GUAWD_INTEWVAW
==================

The acceptabwe vawues awe defined by :c:type:`fe_guawd_intewvaw`.

.. note::

   #. If ``DTV_GUAWD_INTEWVAW`` is set the ``GUAWD_INTEWVAW_AUTO`` the
      hawdwawe wiww twy to find the cowwect guawd intewvaw (if capabwe) and
      wiww use TMCC to fiww in the missing pawametews.
   #. Intewvaw ``GUAWD_INTEWVAW_1_64`` is used onwy fow DVB-C2.
   #. Intewvaw ``GUAWD_INTEWVAW_1_128`` is used fow both DVB-C2 and DVB_T2.
   #. Intewvaws ``GUAWD_INTEWVAW_19_128`` and ``GUAWD_INTEWVAW_19_256`` awe
      used onwy fow DVB-T2.
   #. Intewvaws ``GUAWD_INTEWVAW_PN420``, ``GUAWD_INTEWVAW_PN595`` and
      ``GUAWD_INTEWVAW_PN945`` awe used onwy fow DMTB at the pwesent.
      On such standawd, onwy those intewvaws and ``GUAWD_INTEWVAW_AUTO``
      awe vawid.

.. _DTV-TWANSMISSION-MODE:

DTV_TWANSMISSION_MODE
=====================


Used onwy on OFTM-based standawds, e. g. DVB-T/T2, ISDB-T, DTMB.

Specifies the FFT size (with cowwesponds to the appwoximate numbew of
cawwiews) used by the standawd.

The acceptabwe vawues awe defined by :c:type:`fe_twansmit_mode`.

.. note::

   #. ISDB-T suppowts thwee cawwiew/symbow-size: 8K, 4K, 2K. It is cawwed
      **mode** on such standawd, and awe numbewed fwom 1 to 3:

      ====	========	========================
      Mode	FFT size	Twansmission mode
      ====	========	========================
      1		2K		``TWANSMISSION_MODE_2K``
      2		4K		``TWANSMISSION_MODE_4K``
      3		8K		``TWANSMISSION_MODE_8K``
      ====	========	========================

   #. If ``DTV_TWANSMISSION_MODE`` is set the ``TWANSMISSION_MODE_AUTO``
      the hawdwawe wiww twy to find the cowwect FFT-size (if capabwe) and
      wiww use TMCC to fiww in the missing pawametews.

   #. DVB-T specifies 2K and 8K as vawid sizes.

   #. DVB-T2 specifies 1K, 2K, 4K, 8K, 16K and 32K.

   #. DTMB specifies C1 and C3780.


.. _DTV-HIEWAWCHY:

DTV_HIEWAWCHY
=============

Used onwy on DVB-T and DVB-T2.

Fwontend hiewawchy.

The acceptabwe vawues awe defined by :c:type:`fe_hiewawchy`.


.. _DTV-STWEAM-ID:

DTV_STWEAM_ID
=============

Used on DVB-C2, DVB-S2, DVB-T2 and ISDB-S.

DVB-C2, DVB-S2, DVB-T2 and ISDB-S suppowt the twansmission of sevewaw
stweams on a singwe twanspowt stweam. This pwopewty enabwes the digitaw
TV dwivew to handwe substweam fiwtewing, when suppowted by the hawdwawe.
By defauwt, substweam fiwtewing is disabwed.

Fow DVB-C2, DVB-S2 and DVB-T2, the vawid substweam id wange is fwom 0 to
255.

Fow ISDB, the vawid substweam id wange is fwom 1 to 65535.

To disabwe it, you shouwd use the speciaw macwo NO_STWEAM_ID_FIWTEW.

Note: any vawue outside the id wange awso disabwes fiwtewing.


.. _DTV-DVBT2-PWP-ID-WEGACY:

DTV_DVBT2_PWP_ID_WEGACY
=======================

Obsowete, wepwaced with DTV_STWEAM_ID.


.. _DTV-ENUM-DEWSYS:

DTV_ENUM_DEWSYS
===============

A Muwti standawd fwontend needs to advewtise the dewivewy systems
pwovided. Appwications need to enumewate the pwovided dewivewy systems,
befowe using any othew opewation with the fwontend. Pwiow to it's
intwoduction, FE_GET_INFO was used to detewmine a fwontend type. A
fwontend which pwovides mowe than a singwe dewivewy system,
FE_GET_INFO doesn't hewp much. Appwications which intends to use a
muwtistandawd fwontend must enumewate the dewivewy systems associated
with it, wathew than twying to use FE_GET_INFO. In the case of a
wegacy fwontend, the wesuwt is just the same as with FE_GET_INFO, but
in a mowe stwuctuwed fowmat

The acceptabwe vawues awe defined by :c:type:`fe_dewivewy_system`.


.. _DTV-INTEWWEAVING:

DTV_INTEWWEAVING
================

Time intewweaving to be used.

The acceptabwe vawues awe defined by :c:type:`fe_intewweaving`.


.. _DTV-WNA:

DTV_WNA
=======

Wow-noise ampwifiew.

Hawdwawe might offew contwowwabwe WNA which can be set manuawwy using
that pawametew. Usuawwy WNA couwd be found onwy fwom tewwestwiaw devices
if at aww.

Possibwe vawues: 0, 1, WNA_AUTO

0, WNA off

1, WNA on

use the speciaw macwo WNA_AUTO to set WNA auto


.. _DTV-SCWAMBWING-SEQUENCE-INDEX:

DTV_SCWAMBWING_SEQUENCE_INDEX
=============================

Used on DVB-S2.

This 18 bit fiewd, when pwesent, cawwies the index of the DVB-S2 physicaw
wayew scwambwing sequence as defined in cwause 5.5.4 of EN 302 307.
Thewe is no expwicit signawwing method to convey scwambwing sequence index
to the weceivew. If S2 satewwite dewivewy system descwiptow is avaiwabwe
it can be used to wead the scwambwing sequence index (EN 300 468 tabwe 41).

By defauwt, gowd scwambwing sequence index 0 is used.

The vawid scwambwing sequence index wange is fwom 0 to 262142.
