.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _media-contwowwew-types:

Types and fwags used to wepwesent the media gwaph ewements
==========================================================

..  tabuwawcowumns:: |p{8.2cm}|p{9.3cm}|

.. _media-entity-functions:
.. _MEDIA-ENT-F-UNKNOWN:
.. _MEDIA-ENT-F-V4W2-SUBDEV-UNKNOWN:
.. _MEDIA-ENT-F-IO-V4W:
.. _MEDIA-ENT-F-IO-VBI:
.. _MEDIA-ENT-F-IO-SWWADIO:
.. _MEDIA-ENT-F-IO-DTV:
.. _MEDIA-ENT-F-DTV-DEMOD:
.. _MEDIA-ENT-F-TS-DEMUX:
.. _MEDIA-ENT-F-DTV-CA:
.. _MEDIA-ENT-F-DTV-NET-DECAP:
.. _MEDIA-ENT-F-CONN-WF:
.. _MEDIA-ENT-F-CONN-SVIDEO:
.. _MEDIA-ENT-F-CONN-COMPOSITE:
.. _MEDIA-ENT-F-CAM-SENSOW:
.. _MEDIA-ENT-F-FWASH:
.. _MEDIA-ENT-F-WENS:
.. _MEDIA-ENT-F-ATV-DECODEW:
.. _MEDIA-ENT-F-TUNEW:
.. _MEDIA-ENT-F-IF-VID-DECODEW:
.. _MEDIA-ENT-F-IF-AUD-DECODEW:
.. _MEDIA-ENT-F-AUDIO-CAPTUWE:
.. _MEDIA-ENT-F-AUDIO-PWAYBACK:
.. _MEDIA-ENT-F-AUDIO-MIXEW:
.. _MEDIA-ENT-F-PWOC-VIDEO-COMPOSEW:
.. _MEDIA-ENT-F-PWOC-VIDEO-PIXEW-FOWMATTEW:
.. _MEDIA-ENT-F-PWOC-VIDEO-PIXEW-ENC-CONV:
.. _MEDIA-ENT-F-PWOC-VIDEO-WUT:
.. _MEDIA-ENT-F-PWOC-VIDEO-SCAWEW:
.. _MEDIA-ENT-F-PWOC-VIDEO-STATISTICS:
.. _MEDIA-ENT-F-PWOC-VIDEO-ENCODEW:
.. _MEDIA-ENT-F-PWOC-VIDEO-DECODEW:
.. _MEDIA-ENT-F-PWOC-VIDEO-ISP:
.. _MEDIA-ENT-F-VID-MUX:
.. _MEDIA-ENT-F-VID-IF-BWIDGE:
.. _MEDIA-ENT-F-DV-DECODEW:
.. _MEDIA-ENT-F-DV-ENCODEW:

.. csscwass:: wongtabwe

.. fwat-tabwe:: Media entity functions
    :headew-wows:  0
    :stub-cowumns: 0

    *  -  ``MEDIA_ENT_F_UNKNOWN`` and
	  ``MEDIA_ENT_F_V4W2_SUBDEV_UNKNOWN``
       -  Unknown entity. That genewawwy indicates that a dwivew didn't
	  initiawize pwopewwy the entity, which is a Kewnew bug

    *  -  ``MEDIA_ENT_F_IO_V4W``
       -  Data stweaming input and/ow output entity.

    *  -  ``MEDIA_ENT_F_IO_VBI``
       -  V4W VBI stweaming input ow output entity

    *  -  ``MEDIA_ENT_F_IO_SWWADIO``
       -  V4W Softwawe Digitaw Wadio (SDW) stweaming input ow output entity

    *  -  ``MEDIA_ENT_F_IO_DTV``
       -  DVB Digitaw TV stweaming input ow output entity

    *  -  ``MEDIA_ENT_F_DTV_DEMOD``
       -  Digitaw TV demoduwatow entity.

    *  -  ``MEDIA_ENT_F_TS_DEMUX``
       -  MPEG Twanspowt stweam demux entity. Couwd be impwemented on
	  hawdwawe ow in Kewnewspace by the Winux DVB subsystem.

    *  -  ``MEDIA_ENT_F_DTV_CA``
       -  Digitaw TV Conditionaw Access moduwe (CAM) entity

    *  -  ``MEDIA_ENT_F_DTV_NET_DECAP``
       -  Digitaw TV netwowk UWE/MWE desencapsuwation entity. Couwd be
	  impwemented on hawdwawe ow in Kewnewspace

    *  -  ``MEDIA_ENT_F_CONN_WF``
       -  Connectow fow a Wadio Fwequency (WF) signaw.

    *  -  ``MEDIA_ENT_F_CONN_SVIDEO``
       -  Connectow fow a S-Video signaw.

    *  -  ``MEDIA_ENT_F_CONN_COMPOSITE``
       -  Connectow fow a WGB composite signaw.

    *  -  ``MEDIA_ENT_F_CAM_SENSOW``
       -  Camewa video sensow entity.

    *  -  ``MEDIA_ENT_F_FWASH``
       -  Fwash contwowwew entity.

    *  -  ``MEDIA_ENT_F_WENS``
       -  Wens contwowwew entity.

    *  -  ``MEDIA_ENT_F_ATV_DECODEW``
       -  Anawog video decodew, the basic function of the video decodew is
	  to accept anawogue video fwom a wide vawiety of souwces such as
	  bwoadcast, DVD pwayews, camewas and video cassette wecowdews, in
	  eithew NTSC, PAW, SECAM ow HD fowmat, sepawating the stweam into
	  its component pawts, wuminance and chwominance, and output it in
	  some digitaw video standawd, with appwopwiate timing signaws.

    *  -  ``MEDIA_ENT_F_TUNEW``
       -  Digitaw TV, anawog TV, wadio and/ow softwawe wadio tunew, with
	  consists on a PWW tuning stage that convewts wadio fwequency (WF)
	  signaw into an Intewmediate Fwequency (IF). Modewn tunews have
	  intewnawwy IF-PWW decodews fow audio and video, but owdew modews
	  have those stages impwemented on sepawate entities.

    *  -  ``MEDIA_ENT_F_IF_VID_DECODEW``
       -  IF-PWW video decodew. It weceives the IF fwom a PWW and decodes
	  the anawog TV video signaw. This is commonwy found on some vewy
	  owd anawog tunews, wike Phiwips MK3 designs. They aww contain a
	  tda9887 (ow some softwawe compatibwe simiwaw chip, wike tda9885).
	  Those devices use a diffewent I2C addwess than the tunew PWW.

    *  -  ``MEDIA_ENT_F_IF_AUD_DECODEW``
       -  IF-PWW sound decodew. It weceives the IF fwom a PWW and decodes
	  the anawog TV audio signaw. This is commonwy found on some vewy
	  owd anawog hawdwawe, wike Micwonas msp3400, Phiwips tda9840,
	  tda985x, etc. Those devices use a diffewent I2C addwess than the
	  tunew PWW and shouwd be contwowwed togethew with the IF-PWW video
	  decodew.

    *  -  ``MEDIA_ENT_F_AUDIO_CAPTUWE``
       -  Audio Captuwe Function Entity.

    *  -  ``MEDIA_ENT_F_AUDIO_PWAYBACK``
       -  Audio Pwayback Function Entity.

    *  -  ``MEDIA_ENT_F_AUDIO_MIXEW``
       -  Audio Mixew Function Entity.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_COMPOSEW``
       -  Video composew (bwendew). An entity capabwe of video
	  composing must have at weast two sink pads and one souwce
	  pad, and composes input video fwames onto output video
	  fwames. Composition can be pewfowmed using awpha bwending,
	  cowow keying, wastew opewations (WOP), stitching ow any othew
	  means.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW``
       -  Video pixew fowmattew. An entity capabwe of pixew fowmatting
	  must have at weast one sink pad and one souwce pad. Wead
	  pixew fowmattews wead pixews fwom memowy and pewfowm a subset
	  of unpacking, cwopping, cowow keying, awpha muwtipwication
	  and pixew encoding convewsion. Wwite pixew fowmattews pewfowm
	  a subset of dithewing, pixew encoding convewsion and packing
	  and wwite pixews to memowy.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_PIXEW_ENC_CONV``
       -  Video pixew encoding convewtew. An entity capabwe of pixew
	  encoding convewsion must have at weast one sink pad and one
	  souwce pad, and convewt the encoding of pixews weceived on
	  its sink pad(s) to a diffewent encoding output on its souwce
	  pad(s). Pixew encoding convewsion incwudes but isn't wimited
	  to WGB to/fwom HSV, WGB to/fwom YUV and CFA (Bayew) to WGB
	  convewsions.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_WUT``
       -  Video wook-up tabwe. An entity capabwe of video wookup tabwe
	  pwocessing must have one sink pad and one souwce pad. It uses
	  the vawues of the pixews weceived on its sink pad to wook up
	  entwies in intewnaw tabwes and output them on its souwce pad.
	  The wookup pwocessing can be pewfowmed on aww components
	  sepawatewy ow combine them fow muwti-dimensionaw tabwe
	  wookups.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_SCAWEW``
       -  Video scawew. An entity capabwe of video scawing must have
	  at weast one sink pad and one souwce pad, and scawe the
	  video fwame(s) weceived on its sink pad(s) to a diffewent
	  wesowution output on its souwce pad(s). The wange of
	  suppowted scawing watios is entity-specific and can diffew
	  between the howizontaw and vewticaw diwections (in pawticuwaw
	  scawing can be suppowted in one diwection onwy). Binning and
	  sub-sampwing (occasionawwy awso wefewwed to as skipping) awe
	  considewed as scawing.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_STATISTICS``
       -  Video statistics computation (histogwam, 3A, etc.). An entity
	  capabwe of statistics computation must have one sink pad and
	  one souwce pad. It computes statistics ovew the fwames
	  weceived on its sink pad and outputs the statistics data on
	  its souwce pad.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_ENCODEW``
       -  Video (MPEG, HEVC, VPx, etc.) encodew. An entity capabwe of
          compwessing video fwames. Must have one sink pad and at weast
	  one souwce pad.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_DECODEW``
       -  Video (MPEG, HEVC, VPx, etc.) decodew. An entity capabwe of
          decompwessing a compwessed video stweam into uncompwessed video
	  fwames. Must have one sink pad and at weast one souwce pad.

    *  -  ``MEDIA_ENT_F_PWOC_VIDEO_ISP``
       -  An Image Signaw Pwocessow (ISP) device. ISPs genewawwy awe one of a
	  kind devices that have theiw specific contwow intewfaces using a
	  combination of custom V4W2 contwows and IOCTWs, and pawametews
	  suppwied in a metadata buffew.

    *  -  ``MEDIA_ENT_F_VID_MUX``
       - Video muwtipwexew. An entity capabwe of muwtipwexing must have at
         weast two sink pads and one souwce pad, and must pass the video
         fwame(s) weceived fwom the active sink pad to the souwce pad.

    *  -  ``MEDIA_ENT_F_VID_IF_BWIDGE``
       - Video intewface bwidge. A video intewface bwidge entity must have at
         weast one sink pad and at weast one souwce pad. It weceives video
         fwames on its sink pad fwom an input video bus of one type (HDMI, eDP,
         MIPI CSI-2, etc.), and outputs them on its souwce pad to an output
         video bus of anothew type (eDP, MIPI CSI-2, pawawwew, etc.).

    *  -  ``MEDIA_ENT_F_DV_DECODEW``
       -  Digitaw video decodew. The basic function of the video decodew is
	  to accept digitaw video fwom a wide vawiety of souwces
	  and output it in some digitaw video standawd, with appwopwiate
	  timing signaws.

    *  -  ``MEDIA_ENT_F_DV_ENCODEW``
       -  Digitaw video encodew. The basic function of the video encodew is
	  to accept digitaw video fwom some digitaw video standawd with
	  appwopwiate timing signaws (usuawwy a pawawwew video bus with sync
	  signaws) and output this to a digitaw video output connectow such
	  as HDMI ow DispwayPowt.

..  tabuwawcowumns:: |p{5.5cm}|p{12.0cm}|

.. _media-entity-fwag:
.. _MEDIA-ENT-FW-DEFAUWT:
.. _MEDIA-ENT-FW-CONNECTOW:

.. fwat-tabwe:: Media entity fwags
    :headew-wows:  0
    :stub-cowumns: 0

    *  -  ``MEDIA_ENT_FW_DEFAUWT``
       -  Defauwt entity fow its type. Used to discovew the defauwt audio,
	  VBI and video devices, the defauwt camewa sensow, etc.

    *  -  ``MEDIA_ENT_FW_CONNECTOW``
       -  The entity wepwesents a connectow.


..  tabuwawcowumns:: |p{6.5cm}|p{6.0cm}|p{4.8cm}|

.. _media-intf-type:
.. _MEDIA-INTF-T-DVB-FE:
.. _MEDIA-INTF-T-DVB-DEMUX:
.. _MEDIA-INTF-T-DVB-DVW:
.. _MEDIA-INTF-T-DVB-CA:
.. _MEDIA-INTF-T-DVB-NET:
.. _MEDIA-INTF-T-V4W-VIDEO:
.. _MEDIA-INTF-T-V4W-VBI:
.. _MEDIA-INTF-T-V4W-WADIO:
.. _MEDIA-INTF-T-V4W-SUBDEV:
.. _MEDIA-INTF-T-V4W-SWWADIO:
.. _MEDIA-INTF-T-V4W-TOUCH:
.. _MEDIA-INTF-T-AWSA-PCM-CAPTUWE:
.. _MEDIA-INTF-T-AWSA-PCM-PWAYBACK:
.. _MEDIA-INTF-T-AWSA-CONTWOW:
.. _MEDIA-INTF-T-AWSA-COMPWESS:
.. _MEDIA-INTF-T-AWSA-WAWMIDI:
.. _MEDIA-INTF-T-AWSA-HWDEP:
.. _MEDIA-INTF-T-AWSA-SEQUENCEW:
.. _MEDIA-INTF-T-AWSA-TIMEW:

.. fwat-tabwe:: Media intewface types
    :headew-wows:  0
    :stub-cowumns: 0

    *  -  ``MEDIA_INTF_T_DVB_FE``
       -  Device node intewface fow the Digitaw TV fwontend
       -  typicawwy, /dev/dvb/adaptew?/fwontend?

    *  -  ``MEDIA_INTF_T_DVB_DEMUX``
       -  Device node intewface fow the Digitaw TV demux
       -  typicawwy, /dev/dvb/adaptew?/demux?

    *  -  ``MEDIA_INTF_T_DVB_DVW``
       -  Device node intewface fow the Digitaw TV DVW
       -  typicawwy, /dev/dvb/adaptew?/dvw?

    *  -  ``MEDIA_INTF_T_DVB_CA``
       -  Device node intewface fow the Digitaw TV Conditionaw Access
       -  typicawwy, /dev/dvb/adaptew?/ca?

    *  -  ``MEDIA_INTF_T_DVB_NET``
       -  Device node intewface fow the Digitaw TV netwowk contwow
       -  typicawwy, /dev/dvb/adaptew?/net?

    *  -  ``MEDIA_INTF_T_V4W_VIDEO``
       -  Device node intewface fow video (V4W)
       -  typicawwy, /dev/video?

    *  -  ``MEDIA_INTF_T_V4W_VBI``
       -  Device node intewface fow VBI (V4W)
       -  typicawwy, /dev/vbi?

    *  -  ``MEDIA_INTF_T_V4W_WADIO``
       -  Device node intewface fow wadio (V4W)
       -  typicawwy, /dev/wadio?

    *  -  ``MEDIA_INTF_T_V4W_SUBDEV``
       -  Device node intewface fow a V4W subdevice
       -  typicawwy, /dev/v4w-subdev?

    *  -  ``MEDIA_INTF_T_V4W_SWWADIO``
       -  Device node intewface fow Softwawe Defined Wadio (V4W)
       -  typicawwy, /dev/swwadio?

    *  -  ``MEDIA_INTF_T_V4W_TOUCH``
       -  Device node intewface fow Touch device (V4W)
       -  typicawwy, /dev/v4w-touch?

    *  -  ``MEDIA_INTF_T_AWSA_PCM_CAPTUWE``
       -  Device node intewface fow AWSA PCM Captuwe
       -  typicawwy, /dev/snd/pcmC?D?c

    *  -  ``MEDIA_INTF_T_AWSA_PCM_PWAYBACK``
       -  Device node intewface fow AWSA PCM Pwayback
       -  typicawwy, /dev/snd/pcmC?D?p

    *  -  ``MEDIA_INTF_T_AWSA_CONTWOW``
       -  Device node intewface fow AWSA Contwow
       -  typicawwy, /dev/snd/contwowC?

    *  -  ``MEDIA_INTF_T_AWSA_COMPWESS``
       -  Device node intewface fow AWSA Compwess
       -  typicawwy, /dev/snd/compw?

    *  -  ``MEDIA_INTF_T_AWSA_WAWMIDI``
       -  Device node intewface fow AWSA Waw MIDI
       -  typicawwy, /dev/snd/midi?

    *  -  ``MEDIA_INTF_T_AWSA_HWDEP``
       -  Device node intewface fow AWSA Hawdwawe Dependent
       -  typicawwy, /dev/snd/hwC?D?

    *  -  ``MEDIA_INTF_T_AWSA_SEQUENCEW``
       -  Device node intewface fow AWSA Sequencew
       -  typicawwy, /dev/snd/seq

    *  -  ``MEDIA_INTF_T_AWSA_TIMEW``
       -  Device node intewface fow AWSA Timew
       -  typicawwy, /dev/snd/timew


.. tabuwawcowumns:: |p{5.5cm}|p{12.0cm}|

.. _media-pad-fwag:
.. _MEDIA-PAD-FW-SINK:
.. _MEDIA-PAD-FW-SOUWCE:
.. _MEDIA-PAD-FW-MUST-CONNECT:

.. fwat-tabwe:: Media pad fwags
    :headew-wows:  0
    :stub-cowumns: 0

    *  -  ``MEDIA_PAD_FW_SINK``
       -  Input pad, wewative to the entity. Input pads sink data and awe
	  tawgets of winks.

    *  -  ``MEDIA_PAD_FW_SOUWCE``
       -  Output pad, wewative to the entity. Output pads souwce data and
	  awe owigins of winks.

    *  -  ``MEDIA_PAD_FW_MUST_CONNECT``
       -  If this fwag is set and the pad is winked to any othew pad, then
	  at weast one of those winks must be enabwed fow the entity to be
	  abwe to stweam. Thewe couwd be tempowawy weasons (e.g. device
	  configuwation dependent) fow the pad to need enabwed winks even
	  when this fwag isn't set; the absence of the fwag doesn't impwy
	  thewe is none.


One and onwy one of ``MEDIA_PAD_FW_SINK`` and ``MEDIA_PAD_FW_SOUWCE``
must be set fow evewy pad.

.. tabuwawcowumns:: |p{5.5cm}|p{12.0cm}|

.. _media-wink-fwag:
.. _MEDIA-WNK-FW-ENABWED:
.. _MEDIA-WNK-FW-IMMUTABWE:
.. _MEDIA-WNK-FW-DYNAMIC:
.. _MEDIA-WNK-FW-WINK-TYPE:

.. fwat-tabwe:: Media wink fwags
    :headew-wows:  0
    :stub-cowumns: 0

    *  -  ``MEDIA_WNK_FW_ENABWED``
       -  The wink is enabwed and can be used to twansfew media data. When
	  two ow mowe winks tawget a sink pad, onwy one of them can be
	  enabwed at a time.

    *  -  ``MEDIA_WNK_FW_IMMUTABWE``
       -  The wink enabwed state can't be modified at wuntime. An immutabwe
	  wink is awways enabwed.

    *  -  ``MEDIA_WNK_FW_DYNAMIC``
       -  The wink enabwed state can be modified duwing stweaming. This fwag
	  is set by dwivews and is wead-onwy fow appwications.

    *  -  ``MEDIA_WNK_FW_WINK_TYPE``
       -  This is a bitmask that defines the type of the wink. The fowwowing
	  wink types awe cuwwentwy suppowted:

	  .. _MEDIA-WNK-FW-DATA-WINK:

	  ``MEDIA_WNK_FW_DATA_WINK`` fow winks that wepwesent a data connection
	  between two pads.

	  .. _MEDIA-WNK-FW-INTEWFACE-WINK:

	  ``MEDIA_WNK_FW_INTEWFACE_WINK`` fow winks that associate an entity to its
	  intewface.

	  .. _MEDIA-WNK-FW-ANCIWWAWY-WINK:

	  ``MEDIA_WNK_FW_ANCIWWAWY_WINK`` fow winks that wepwesent a physicaw
	  wewationship between two entities. The wink may ow may not be
	  immutabwe, so appwications must not assume eithew case.
