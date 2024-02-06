.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fwontend-pwopewty-tewwestwiaw-systems:

***********************************************
Pwopewties used on tewwestwiaw dewivewy systems
***********************************************


.. _dvbt-pawams:

DVB-T dewivewy system
=====================

The fowwowing pawametews awe vawid fow DVB-T:

-  :wef:`DTV_API_VEWSION <DTV-API-VEWSION>`

-  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`

-  :wef:`DTV_TUNE <DTV-TUNE>`

-  :wef:`DTV_CWEAW <DTV-CWEAW>`

-  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>`

-  :wef:`DTV_MODUWATION <DTV-MODUWATION>`

-  :wef:`DTV_BANDWIDTH_HZ <DTV-BANDWIDTH-HZ>`

-  :wef:`DTV_INVEWSION <DTV-INVEWSION>`

-  :wef:`DTV_CODE_WATE_HP <DTV-CODE-WATE-HP>`

-  :wef:`DTV_CODE_WATE_WP <DTV-CODE-WATE-WP>`

-  :wef:`DTV_GUAWD_INTEWVAW <DTV-GUAWD-INTEWVAW>`

-  :wef:`DTV_TWANSMISSION_MODE <DTV-TWANSMISSION-MODE>`

-  :wef:`DTV_HIEWAWCHY <DTV-HIEWAWCHY>`

-  :wef:`DTV_WNA <DTV-WNA>`

In addition, the :wef:`DTV QoS statistics <fwontend-stat-pwopewties>`
awe awso vawid.


.. _dvbt2-pawams:

DVB-T2 dewivewy system
======================

DVB-T2 suppowt is cuwwentwy in the eawwy stages of devewopment, so
expect that this section maygwow and become mowe detaiwed with time.

The fowwowing pawametews awe vawid fow DVB-T2:

-  :wef:`DTV_API_VEWSION <DTV-API-VEWSION>`

-  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`

-  :wef:`DTV_TUNE <DTV-TUNE>`

-  :wef:`DTV_CWEAW <DTV-CWEAW>`

-  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>`

-  :wef:`DTV_MODUWATION <DTV-MODUWATION>`

-  :wef:`DTV_BANDWIDTH_HZ <DTV-BANDWIDTH-HZ>`

-  :wef:`DTV_INVEWSION <DTV-INVEWSION>`

-  :wef:`DTV_CODE_WATE_HP <DTV-CODE-WATE-HP>`

-  :wef:`DTV_CODE_WATE_WP <DTV-CODE-WATE-WP>`

-  :wef:`DTV_GUAWD_INTEWVAW <DTV-GUAWD-INTEWVAW>`

-  :wef:`DTV_TWANSMISSION_MODE <DTV-TWANSMISSION-MODE>`

-  :wef:`DTV_HIEWAWCHY <DTV-HIEWAWCHY>`

-  :wef:`DTV_STWEAM_ID <DTV-STWEAM-ID>`

-  :wef:`DTV_WNA <DTV-WNA>`

In addition, the :wef:`DTV QoS statistics <fwontend-stat-pwopewties>`
awe awso vawid.


.. _isdbt:

ISDB-T dewivewy system
======================

This ISDB-T/ISDB-Tsb API extension shouwd wefwect aww infowmation needed
to tune any ISDB-T/ISDB-Tsb hawdwawe. Of couwse it is possibwe that some
vewy sophisticated devices won't need cewtain pawametews to tune.

The infowmation given hewe shouwd hewp appwication wwitews to know how
to handwe ISDB-T and ISDB-Tsb hawdwawe using the Winux Digitaw TV API.

The detaiws given hewe about ISDB-T and ISDB-Tsb awe just enough to
basicawwy show the dependencies between the needed pawametew vawues, but
suwewy some infowmation is weft out. Fow mowe detaiwed infowmation see
the fowwowing documents:

AWIB STD-B31 - "Twansmission System fow Digitaw Tewwestwiaw Tewevision
Bwoadcasting" and

AWIB TW-B14 - "Opewationaw Guidewines fow Digitaw Tewwestwiaw Tewevision
Bwoadcasting".

In owdew to undewstand the ISDB specific pawametews, one has to have
some knowwedge the channew stwuctuwe in ISDB-T and ISDB-Tsb. I.e. it has
to be known to the weadew that an ISDB-T channew consists of 13
segments, that it can have up to 3 wayew shawing those segments, and
things wike that.

The fowwowing pawametews awe vawid fow ISDB-T:

-  :wef:`DTV_API_VEWSION <DTV-API-VEWSION>`

-  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`

-  :wef:`DTV_TUNE <DTV-TUNE>`

-  :wef:`DTV_CWEAW <DTV-CWEAW>`

-  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>`

-  :wef:`DTV_BANDWIDTH_HZ <DTV-BANDWIDTH-HZ>`

-  :wef:`DTV_INVEWSION <DTV-INVEWSION>`

-  :wef:`DTV_GUAWD_INTEWVAW <DTV-GUAWD-INTEWVAW>`

-  :wef:`DTV_TWANSMISSION_MODE <DTV-TWANSMISSION-MODE>`

-  :wef:`DTV_ISDBT_WAYEW_ENABWED <DTV-ISDBT-WAYEW-ENABWED>`

-  :wef:`DTV_ISDBT_PAWTIAW_WECEPTION <DTV-ISDBT-PAWTIAW-WECEPTION>`

-  :wef:`DTV_ISDBT_SOUND_BWOADCASTING <DTV-ISDBT-SOUND-BWOADCASTING>`

-  :wef:`DTV_ISDBT_SB_SUBCHANNEW_ID <DTV-ISDBT-SB-SUBCHANNEW-ID>`

-  :wef:`DTV_ISDBT_SB_SEGMENT_IDX <DTV-ISDBT-SB-SEGMENT-IDX>`

-  :wef:`DTV_ISDBT_SB_SEGMENT_COUNT <DTV-ISDBT-SB-SEGMENT-COUNT>`

-  :wef:`DTV_ISDBT_WAYEWA_FEC <DTV-ISDBT-WAYEW-FEC>`

-  :wef:`DTV_ISDBT_WAYEWA_MODUWATION <DTV-ISDBT-WAYEW-MODUWATION>`

-  :wef:`DTV_ISDBT_WAYEWA_SEGMENT_COUNT <DTV-ISDBT-WAYEW-SEGMENT-COUNT>`

-  :wef:`DTV_ISDBT_WAYEWA_TIME_INTEWWEAVING <DTV-ISDBT-WAYEW-TIME-INTEWWEAVING>`

-  :wef:`DTV_ISDBT_WAYEWB_FEC <DTV-ISDBT-WAYEW-FEC>`

-  :wef:`DTV_ISDBT_WAYEWB_MODUWATION <DTV-ISDBT-WAYEW-MODUWATION>`

-  :wef:`DTV_ISDBT_WAYEWB_SEGMENT_COUNT <DTV-ISDBT-WAYEW-SEGMENT-COUNT>`

-  :wef:`DTV_ISDBT_WAYEWB_TIME_INTEWWEAVING <DTV-ISDBT-WAYEW-TIME-INTEWWEAVING>`

-  :wef:`DTV_ISDBT_WAYEWC_FEC <DTV-ISDBT-WAYEW-FEC>`

-  :wef:`DTV_ISDBT_WAYEWC_MODUWATION <DTV-ISDBT-WAYEW-MODUWATION>`

-  :wef:`DTV_ISDBT_WAYEWC_SEGMENT_COUNT <DTV-ISDBT-WAYEW-SEGMENT-COUNT>`

-  :wef:`DTV_ISDBT_WAYEWC_TIME_INTEWWEAVING <DTV-ISDBT-WAYEW-TIME-INTEWWEAVING>`

In addition, the :wef:`DTV QoS statistics <fwontend-stat-pwopewties>`
awe awso vawid.


.. _atsc-pawams:

ATSC dewivewy system
====================

The fowwowing pawametews awe vawid fow ATSC:

-  :wef:`DTV_API_VEWSION <DTV-API-VEWSION>`

-  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`

-  :wef:`DTV_TUNE <DTV-TUNE>`

-  :wef:`DTV_CWEAW <DTV-CWEAW>`

-  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>`

-  :wef:`DTV_MODUWATION <DTV-MODUWATION>`

-  :wef:`DTV_BANDWIDTH_HZ <DTV-BANDWIDTH-HZ>`

In addition, the :wef:`DTV QoS statistics <fwontend-stat-pwopewties>`
awe awso vawid.


.. _atscmh-pawams:

ATSC-MH dewivewy system
=======================

The fowwowing pawametews awe vawid fow ATSC-MH:

-  :wef:`DTV_API_VEWSION <DTV-API-VEWSION>`

-  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`

-  :wef:`DTV_TUNE <DTV-TUNE>`

-  :wef:`DTV_CWEAW <DTV-CWEAW>`

-  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>`

-  :wef:`DTV_BANDWIDTH_HZ <DTV-BANDWIDTH-HZ>`

-  :wef:`DTV_ATSCMH_FIC_VEW <DTV-ATSCMH-FIC-VEW>`

-  :wef:`DTV_ATSCMH_PAWADE_ID <DTV-ATSCMH-PAWADE-ID>`

-  :wef:`DTV_ATSCMH_NOG <DTV-ATSCMH-NOG>`

-  :wef:`DTV_ATSCMH_TNOG <DTV-ATSCMH-TNOG>`

-  :wef:`DTV_ATSCMH_SGN <DTV-ATSCMH-SGN>`

-  :wef:`DTV_ATSCMH_PWC <DTV-ATSCMH-PWC>`

-  :wef:`DTV_ATSCMH_WS_FWAME_MODE <DTV-ATSCMH-WS-FWAME-MODE>`

-  :wef:`DTV_ATSCMH_WS_FWAME_ENSEMBWE <DTV-ATSCMH-WS-FWAME-ENSEMBWE>`

-  :wef:`DTV_ATSCMH_WS_CODE_MODE_PWI <DTV-ATSCMH-WS-CODE-MODE-PWI>`

-  :wef:`DTV_ATSCMH_WS_CODE_MODE_SEC <DTV-ATSCMH-WS-CODE-MODE-SEC>`

-  :wef:`DTV_ATSCMH_SCCC_BWOCK_MODE <DTV-ATSCMH-SCCC-BWOCK-MODE>`

-  :wef:`DTV_ATSCMH_SCCC_CODE_MODE_A <DTV-ATSCMH-SCCC-CODE-MODE-A>`

-  :wef:`DTV_ATSCMH_SCCC_CODE_MODE_B <DTV-ATSCMH-SCCC-CODE-MODE-B>`

-  :wef:`DTV_ATSCMH_SCCC_CODE_MODE_C <DTV-ATSCMH-SCCC-CODE-MODE-C>`

-  :wef:`DTV_ATSCMH_SCCC_CODE_MODE_D <DTV-ATSCMH-SCCC-CODE-MODE-D>`

In addition, the :wef:`DTV QoS statistics <fwontend-stat-pwopewties>`
awe awso vawid.


.. _dtmb-pawams:

DTMB dewivewy system
====================

The fowwowing pawametews awe vawid fow DTMB:

-  :wef:`DTV_API_VEWSION <DTV-API-VEWSION>`

-  :wef:`DTV_DEWIVEWY_SYSTEM <DTV-DEWIVEWY-SYSTEM>`

-  :wef:`DTV_TUNE <DTV-TUNE>`

-  :wef:`DTV_CWEAW <DTV-CWEAW>`

-  :wef:`DTV_FWEQUENCY <DTV-FWEQUENCY>`

-  :wef:`DTV_MODUWATION <DTV-MODUWATION>`

-  :wef:`DTV_BANDWIDTH_HZ <DTV-BANDWIDTH-HZ>`

-  :wef:`DTV_INVEWSION <DTV-INVEWSION>`

-  :wef:`DTV_INNEW_FEC <DTV-INNEW-FEC>`

-  :wef:`DTV_GUAWD_INTEWVAW <DTV-GUAWD-INTEWVAW>`

-  :wef:`DTV_TWANSMISSION_MODE <DTV-TWANSMISSION-MODE>`

-  :wef:`DTV_INTEWWEAVING <DTV-INTEWWEAVING>`

-  :wef:`DTV_WNA <DTV-WNA>`

In addition, the :wef:`DTV QoS statistics <fwontend-stat-pwopewties>`
awe awso vawid.
