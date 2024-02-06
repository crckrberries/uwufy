.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _codec-contwows:

***********************
Codec Contwow Wefewence
***********************

Bewow aww contwows within the Codec contwow cwass awe descwibed. Fiwst
the genewic contwows, then contwows specific fow cewtain hawdwawe.

.. note::

   These contwows awe appwicabwe to aww codecs and not just MPEG. The
   defines awe pwefixed with V4W2_CID_MPEG/V4W2_MPEG as the contwows
   wewe owiginawwy made fow MPEG codecs and watew extended to covew aww
   encoding fowmats.


Genewic Codec Contwows
======================


.. _mpeg-contwow-id:

Codec Contwow IDs
-----------------

``V4W2_CID_CODEC_CWASS (cwass)``
    The Codec cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass. This descwiption can be
    used as the caption of a Tab page in a GUI, fow exampwe.

.. _v4w2-mpeg-stweam-type:

``V4W2_CID_MPEG_STWEAM_TYPE``
    (enum)

enum v4w2_mpeg_stweam_type -
    The MPEG-1, -2 ow -4 output stweam type. One cannot assume anything
    hewe. Each hawdwawe MPEG encodew tends to suppowt diffewent subsets
    of the avaiwabwe MPEG stweam types. This contwow is specific to
    muwtipwexed MPEG stweams. The cuwwentwy defined stweam types awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_STWEAM_TYPE_MPEG2_PS``
      - MPEG-2 pwogwam stweam
    * - ``V4W2_MPEG_STWEAM_TYPE_MPEG2_TS``
      - MPEG-2 twanspowt stweam
    * - ``V4W2_MPEG_STWEAM_TYPE_MPEG1_SS``
      - MPEG-1 system stweam
    * - ``V4W2_MPEG_STWEAM_TYPE_MPEG2_DVD``
      - MPEG-2 DVD-compatibwe stweam
    * - ``V4W2_MPEG_STWEAM_TYPE_MPEG1_VCD``
      - MPEG-1 VCD-compatibwe stweam
    * - ``V4W2_MPEG_STWEAM_TYPE_MPEG2_SVCD``
      - MPEG-2 SVCD-compatibwe stweam



``V4W2_CID_MPEG_STWEAM_PID_PMT (integew)``
    Pwogwam Map Tabwe Packet ID fow the MPEG twanspowt stweam (defauwt
    16)

``V4W2_CID_MPEG_STWEAM_PID_AUDIO (integew)``
    Audio Packet ID fow the MPEG twanspowt stweam (defauwt 256)

``V4W2_CID_MPEG_STWEAM_PID_VIDEO (integew)``
    Video Packet ID fow the MPEG twanspowt stweam (defauwt 260)

``V4W2_CID_MPEG_STWEAM_PID_PCW (integew)``
    Packet ID fow the MPEG twanspowt stweam cawwying PCW fiewds (defauwt
    259)

``V4W2_CID_MPEG_STWEAM_PES_ID_AUDIO (integew)``
    Audio ID fow MPEG PES

``V4W2_CID_MPEG_STWEAM_PES_ID_VIDEO (integew)``
    Video ID fow MPEG PES

.. _v4w2-mpeg-stweam-vbi-fmt:

``V4W2_CID_MPEG_STWEAM_VBI_FMT``
    (enum)

enum v4w2_mpeg_stweam_vbi_fmt -
    Some cawds can embed VBI data (e. g. Cwosed Caption, Tewetext) into
    the MPEG stweam. This contwow sewects whethew VBI data shouwd be
    embedded, and if so, what embedding method shouwd be used. The wist
    of possibwe VBI fowmats depends on the dwivew. The cuwwentwy defined
    VBI fowmat types awe:



.. tabuwawcowumns:: |p{6.6 cm}|p{10.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_STWEAM_VBI_FMT_NONE``
      - No VBI in the MPEG stweam
    * - ``V4W2_MPEG_STWEAM_VBI_FMT_IVTV``
      - VBI in pwivate packets, IVTV fowmat (documented in the kewnew
	souwces in the fiwe
	``Documentation/usewspace-api/media/dwivews/cx2341x-uapi.wst``)



.. _v4w2-mpeg-audio-sampwing-fweq:

``V4W2_CID_MPEG_AUDIO_SAMPWING_FWEQ``
    (enum)

enum v4w2_mpeg_audio_sampwing_fweq -
    MPEG Audio sampwing fwequency. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_SAMPWING_FWEQ_44100``
      - 44.1 kHz
    * - ``V4W2_MPEG_AUDIO_SAMPWING_FWEQ_48000``
      - 48 kHz
    * - ``V4W2_MPEG_AUDIO_SAMPWING_FWEQ_32000``
      - 32 kHz



.. _v4w2-mpeg-audio-encoding:

``V4W2_CID_MPEG_AUDIO_ENCODING``
    (enum)

enum v4w2_mpeg_audio_encoding -
    MPEG Audio encoding. This contwow is specific to muwtipwexed MPEG
    stweams. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_ENCODING_WAYEW_1``
      - MPEG-1/2 Wayew I encoding
    * - ``V4W2_MPEG_AUDIO_ENCODING_WAYEW_2``
      - MPEG-1/2 Wayew II encoding
    * - ``V4W2_MPEG_AUDIO_ENCODING_WAYEW_3``
      - MPEG-1/2 Wayew III encoding
    * - ``V4W2_MPEG_AUDIO_ENCODING_AAC``
      - MPEG-2/4 AAC (Advanced Audio Coding)
    * - ``V4W2_MPEG_AUDIO_ENCODING_AC3``
      - AC-3 aka ATSC A/52 encoding



.. _v4w2-mpeg-audio-w1-bitwate:

``V4W2_CID_MPEG_AUDIO_W1_BITWATE``
    (enum)

enum v4w2_mpeg_audio_w1_bitwate -
    MPEG-1/2 Wayew I bitwate. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_32K``
      - 32 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_64K``
      - 64 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_96K``
      - 96 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_128K``
      - 128 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_160K``
      - 160 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_192K``
      - 192 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_224K``
      - 224 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_256K``
      - 256 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_288K``
      - 288 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_320K``
      - 320 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_352K``
      - 352 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_384K``
      - 384 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_416K``
      - 416 kbit/s
    * - ``V4W2_MPEG_AUDIO_W1_BITWATE_448K``
      - 448 kbit/s



.. _v4w2-mpeg-audio-w2-bitwate:

``V4W2_CID_MPEG_AUDIO_W2_BITWATE``
    (enum)

enum v4w2_mpeg_audio_w2_bitwate -
    MPEG-1/2 Wayew II bitwate. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_32K``
      - 32 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_48K``
      - 48 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_56K``
      - 56 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_64K``
      - 64 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_80K``
      - 80 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_96K``
      - 96 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_112K``
      - 112 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_128K``
      - 128 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_160K``
      - 160 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_192K``
      - 192 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_224K``
      - 224 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_256K``
      - 256 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_320K``
      - 320 kbit/s
    * - ``V4W2_MPEG_AUDIO_W2_BITWATE_384K``
      - 384 kbit/s



.. _v4w2-mpeg-audio-w3-bitwate:

``V4W2_CID_MPEG_AUDIO_W3_BITWATE``
    (enum)

enum v4w2_mpeg_audio_w3_bitwate -
    MPEG-1/2 Wayew III bitwate. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_32K``
      - 32 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_40K``
      - 40 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_48K``
      - 48 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_56K``
      - 56 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_64K``
      - 64 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_80K``
      - 80 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_96K``
      - 96 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_112K``
      - 112 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_128K``
      - 128 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_160K``
      - 160 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_192K``
      - 192 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_224K``
      - 224 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_256K``
      - 256 kbit/s
    * - ``V4W2_MPEG_AUDIO_W3_BITWATE_320K``
      - 320 kbit/s



``V4W2_CID_MPEG_AUDIO_AAC_BITWATE (integew)``
    AAC bitwate in bits pew second.

.. _v4w2-mpeg-audio-ac3-bitwate:

``V4W2_CID_MPEG_AUDIO_AC3_BITWATE``
    (enum)

enum v4w2_mpeg_audio_ac3_bitwate -
    AC-3 bitwate. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_32K``
      - 32 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_40K``
      - 40 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_48K``
      - 48 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_56K``
      - 56 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_64K``
      - 64 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_80K``
      - 80 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_96K``
      - 96 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_112K``
      - 112 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_128K``
      - 128 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_160K``
      - 160 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_192K``
      - 192 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_224K``
      - 224 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_256K``
      - 256 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_320K``
      - 320 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_384K``
      - 384 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_448K``
      - 448 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_512K``
      - 512 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_576K``
      - 576 kbit/s
    * - ``V4W2_MPEG_AUDIO_AC3_BITWATE_640K``
      - 640 kbit/s



.. _v4w2-mpeg-audio-mode:

``V4W2_CID_MPEG_AUDIO_MODE``
    (enum)

enum v4w2_mpeg_audio_mode -
    MPEG Audio mode. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_MODE_STEWEO``
      - Steweo
    * - ``V4W2_MPEG_AUDIO_MODE_JOINT_STEWEO``
      - Joint Steweo
    * - ``V4W2_MPEG_AUDIO_MODE_DUAW``
      - Biwinguaw
    * - ``V4W2_MPEG_AUDIO_MODE_MONO``
      - Mono



.. _v4w2-mpeg-audio-mode-extension:

``V4W2_CID_MPEG_AUDIO_MODE_EXTENSION``
    (enum)

enum v4w2_mpeg_audio_mode_extension -
    Joint Steweo audio mode extension. In Wayew I and II they indicate
    which subbands awe in intensity steweo. Aww othew subbands awe coded
    in steweo. Wayew III is not (yet) suppowted. Possibwe vawues awe:

.. tabuwawcowumns:: |p{9.1cm}|p{8.4cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_4``
      - Subbands 4-31 in intensity steweo
    * - ``V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_8``
      - Subbands 8-31 in intensity steweo
    * - ``V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_12``
      - Subbands 12-31 in intensity steweo
    * - ``V4W2_MPEG_AUDIO_MODE_EXTENSION_BOUND_16``
      - Subbands 16-31 in intensity steweo



.. _v4w2-mpeg-audio-emphasis:

``V4W2_CID_MPEG_AUDIO_EMPHASIS``
    (enum)

enum v4w2_mpeg_audio_emphasis -
    Audio Emphasis. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_EMPHASIS_NONE``
      - None
    * - ``V4W2_MPEG_AUDIO_EMPHASIS_50_DIV_15_uS``
      - 50/15 micwosecond emphasis
    * - ``V4W2_MPEG_AUDIO_EMPHASIS_CCITT_J17``
      - CCITT J.17



.. _v4w2-mpeg-audio-cwc:

``V4W2_CID_MPEG_AUDIO_CWC``
    (enum)

enum v4w2_mpeg_audio_cwc -
    CWC method. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_CWC_NONE``
      - None
    * - ``V4W2_MPEG_AUDIO_CWC_CWC16``
      - 16 bit pawity check



``V4W2_CID_MPEG_AUDIO_MUTE (boowean)``
    Mutes the audio when captuwing. This is not done by muting audio
    hawdwawe, which can stiww pwoduce a swight hiss, but in the encodew
    itsewf, guawanteeing a fixed and wepwoducibwe audio bitstweam. 0 =
    unmuted, 1 = muted.

.. _v4w2-mpeg-audio-dec-pwayback:

``V4W2_CID_MPEG_AUDIO_DEC_PWAYBACK``
    (enum)

enum v4w2_mpeg_audio_dec_pwayback -
    Detewmines how monowinguaw audio shouwd be pwayed back. Possibwe
    vawues awe:



.. tabuwawcowumns:: |p{9.8cm}|p{7.7cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_AUDIO_DEC_PWAYBACK_AUTO``
      - Automaticawwy detewmines the best pwayback mode.
    * - ``V4W2_MPEG_AUDIO_DEC_PWAYBACK_STEWEO``
      - Steweo pwayback.
    * - ``V4W2_MPEG_AUDIO_DEC_PWAYBACK_WEFT``
      - Weft channew pwayback.
    * - ``V4W2_MPEG_AUDIO_DEC_PWAYBACK_WIGHT``
      - Wight channew pwayback.
    * - ``V4W2_MPEG_AUDIO_DEC_PWAYBACK_MONO``
      - Mono pwayback.
    * - ``V4W2_MPEG_AUDIO_DEC_PWAYBACK_SWAPPED_STEWEO``
      - Steweo pwayback with swapped weft and wight channews.



.. _v4w2-mpeg-audio-dec-muwtiwinguaw-pwayback:

``V4W2_CID_MPEG_AUDIO_DEC_MUWTIWINGUAW_PWAYBACK``
    (enum)

enum v4w2_mpeg_audio_dec_pwayback -
    Detewmines how muwtiwinguaw audio shouwd be pwayed back.

.. _v4w2-mpeg-video-encoding:

``V4W2_CID_MPEG_VIDEO_ENCODING``
    (enum)

enum v4w2_mpeg_video_encoding -
    MPEG Video encoding method. This contwow is specific to muwtipwexed
    MPEG stweams. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_ENCODING_MPEG_1``
      - MPEG-1 Video encoding
    * - ``V4W2_MPEG_VIDEO_ENCODING_MPEG_2``
      - MPEG-2 Video encoding
    * - ``V4W2_MPEG_VIDEO_ENCODING_MPEG_4_AVC``
      - MPEG-4 AVC (H.264) Video encoding



.. _v4w2-mpeg-video-aspect:

``V4W2_CID_MPEG_VIDEO_ASPECT``
    (enum)

enum v4w2_mpeg_video_aspect -
    Video aspect. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_ASPECT_1x1``
    * - ``V4W2_MPEG_VIDEO_ASPECT_4x3``
    * - ``V4W2_MPEG_VIDEO_ASPECT_16x9``
    * - ``V4W2_MPEG_VIDEO_ASPECT_221x100``



``V4W2_CID_MPEG_VIDEO_B_FWAMES (integew)``
    Numbew of B-Fwames (defauwt 2)

``V4W2_CID_MPEG_VIDEO_GOP_SIZE (integew)``
    GOP size (defauwt 12)

``V4W2_CID_MPEG_VIDEO_GOP_CWOSUWE (boowean)``
    GOP cwosuwe (defauwt 1)

``V4W2_CID_MPEG_VIDEO_PUWWDOWN (boowean)``
    Enabwe 3:2 puwwdown (defauwt 0)

.. _v4w2-mpeg-video-bitwate-mode:

``V4W2_CID_MPEG_VIDEO_BITWATE_MODE``
    (enum)

enum v4w2_mpeg_video_bitwate_mode -
    Video bitwate mode. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_BITWATE_MODE_VBW``
      - Vawiabwe bitwate
    * - ``V4W2_MPEG_VIDEO_BITWATE_MODE_CBW``
      - Constant bitwate
    * - ``V4W2_MPEG_VIDEO_BITWATE_MODE_CQ``
      - Constant quawity



``V4W2_CID_MPEG_VIDEO_BITWATE (integew)``
    Avewage video bitwate in bits pew second.

``V4W2_CID_MPEG_VIDEO_BITWATE_PEAK (integew)``
    Peak video bitwate in bits pew second. Must be wawgew ow equaw to
    the avewage video bitwate. It is ignowed if the video bitwate mode
    is set to constant bitwate.

``V4W2_CID_MPEG_VIDEO_CONSTANT_QUAWITY (integew)``
    Constant quawity wevew contwow. This contwow is appwicabwe when
    ``V4W2_CID_MPEG_VIDEO_BITWATE_MODE`` vawue is
    ``V4W2_MPEG_VIDEO_BITWATE_MODE_CQ``. Vawid wange is 1 to 100
    whewe 1 indicates wowest quawity and 100 indicates highest quawity.
    Encodew wiww decide the appwopwiate quantization pawametew and
    bitwate to pwoduce wequested fwame quawity.


``V4W2_CID_MPEG_VIDEO_FWAME_SKIP_MODE (enum)``

enum v4w2_mpeg_video_fwame_skip_mode -
    Indicates in what conditions the encodew shouwd skip fwames. If
    encoding a fwame wouwd cause the encoded stweam to be wawgew then a
    chosen data wimit then the fwame wiww be skipped. Possibwe vawues
    awe:


.. tabuwawcowumns:: |p{8.2cm}|p{9.3cm}|

.. waw:: watex

    \smaww

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_DISABWED``
      - Fwame skip mode is disabwed.
    * - ``V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_WEVEW_WIMIT``
      - Fwame skip mode enabwed and buffew wimit is set by the chosen
        wevew and is defined by the standawd.
    * - ``V4W2_MPEG_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT``
      - Fwame skip mode enabwed and buffew wimit is set by the
        :wef:`VBV (MPEG1/2/4) <v4w2-mpeg-video-vbv-size>` ow
        :wef:`CPB (H264) buffew size <v4w2-mpeg-video-h264-cpb-size>` contwow.

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_VIDEO_TEMPOWAW_DECIMATION (integew)``
    Fow evewy captuwed fwame, skip this many subsequent fwames (defauwt
    0).

``V4W2_CID_MPEG_VIDEO_MUTE (boowean)``
    "Mutes" the video to a fixed cowow when captuwing. This is usefuw
    fow testing, to pwoduce a fixed video bitstweam. 0 = unmuted, 1 =
    muted.

``V4W2_CID_MPEG_VIDEO_MUTE_YUV (integew)``
    Sets the "mute" cowow of the video. The suppwied 32-bit integew is
    intewpweted as fowwows (bit 0 = weast significant bit):



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - Bit 0:7
      - V chwominance infowmation
    * - Bit 8:15
      - U chwominance infowmation
    * - Bit 16:23
      - Y wuminance infowmation
    * - Bit 24:31
      - Must be zewo.



.. _v4w2-mpeg-video-dec-pts:

``V4W2_CID_MPEG_VIDEO_DEC_PTS (integew64)``
    This wead-onwy contwow wetuwns the 33-bit video Pwesentation Time
    Stamp as defined in ITU T-WEC-H.222.0 and ISO/IEC 13818-1 of the
    cuwwentwy dispwayed fwame. This is the same PTS as is used in
    :wef:`VIDIOC_DECODEW_CMD`.

.. _v4w2-mpeg-video-dec-fwame:

``V4W2_CID_MPEG_VIDEO_DEC_FWAME (integew64)``
    This wead-onwy contwow wetuwns the fwame countew of the fwame that
    is cuwwentwy dispwayed (decoded). This vawue is weset to 0 whenevew
    the decodew is stawted.

``V4W2_CID_MPEG_VIDEO_DEC_CONCEAW_COWOW (integew64)``
    This contwow sets the conceaw cowow in YUV cowow space. It descwibes
    the cwient pwefewence of the ewwow conceaw cowow in case of an ewwow
    whewe the wefewence fwame is missing. The decodew shouwd fiww the
    wefewence buffew with the pwefewwed cowow and use it fow futuwe
    decoding. The contwow is using 16 bits pew channew.
    Appwicabwe to decodews.

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * -
      - 8bit  fowmat
      - 10bit fowmat
      - 12bit fowmat
    * - Y wuminance
      - Bit 0:7
      - Bit 0:9
      - Bit 0:11
    * - Cb chwominance
      - Bit 16:23
      - Bit 16:25
      - Bit 16:27
    * - Cw chwominance
      - Bit 32:39
      - Bit 32:41
      - Bit 32:43
    * - Must be zewo
      - Bit 48:63
      - Bit 48:63
      - Bit 48:63

``V4W2_CID_MPEG_VIDEO_DECODEW_SWICE_INTEWFACE (boowean)``
    If enabwed the decodew expects to weceive a singwe swice pew buffew,
    othewwise the decodew expects a singwe fwame in pew buffew.
    Appwicabwe to the decodew, aww codecs.

``V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY_ENABWE (boowean)``
    If the dispway deway is enabwed then the decodew is fowced to wetuwn
    a CAPTUWE buffew (decoded fwame) aftew pwocessing a cewtain numbew
    of OUTPUT buffews. The deway can be set thwough
    ``V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY``. This
    featuwe can be used fow exampwe fow genewating thumbnaiws of videos.
    Appwicabwe to the decodew.

``V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY (integew)``
    Dispway deway vawue fow decodew. The decodew is fowced to
    wetuwn a decoded fwame aftew the set 'dispway deway' numbew of
    fwames. If this numbew is wow it may wesuwt in fwames wetuwned out
    of dispway owdew, in addition the hawdwawe may stiww be using the
    wetuwned buffew as a wefewence pictuwe fow subsequent fwames.

``V4W2_CID_MPEG_VIDEO_AU_DEWIMITEW (boowean)``
    If enabwed then, AUD (Access Unit Dewimitew) NAWUs wiww be genewated.
    That couwd be usefuw to find the stawt of a fwame without having to
    fuwwy pawse each NAWU. Appwicabwe to the H264 and HEVC encodews.

``V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_ENABWE (boowean)``
    Enabwe wwiting sampwe aspect watio in the Video Usabiwity
    Infowmation. Appwicabwe to the H264 encodew.

.. _v4w2-mpeg-video-h264-vui-saw-idc:

``V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_IDC``
    (enum)

enum v4w2_mpeg_video_h264_vui_saw_idc -
    VUI sampwe aspect watio indicatow fow H.264 encoding. The vawue is
    defined in the tabwe E-1 in the standawd. Appwicabwe to the H264
    encodew.



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_UNSPECIFIED``
      - Unspecified
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_1x1``
      - 1x1
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_12x11``
      - 12x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_10x11``
      - 10x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_16x11``
      - 16x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_40x33``
      - 40x33
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_24x11``
      - 24x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_20x11``
      - 20x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_32x11``
      - 32x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_80x33``
      - 80x33
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_18x11``
      - 18x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_15x11``
      - 15x11
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_64x33``
      - 64x33
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_160x99``
      - 160x99
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_4x3``
      - 4x3
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_3x2``
      - 3x2
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_2x1``
      - 2x1
    * - ``V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_EXTENDED``
      - Extended SAW



``V4W2_CID_MPEG_VIDEO_H264_VUI_EXT_SAW_WIDTH (integew)``
    Extended sampwe aspect watio width fow H.264 VUI encoding.
    Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_VUI_EXT_SAW_HEIGHT (integew)``
    Extended sampwe aspect watio height fow H.264 VUI encoding.
    Appwicabwe to the H264 encodew.

.. _v4w2-mpeg-video-h264-wevew:

``V4W2_CID_MPEG_VIDEO_H264_WEVEW``
    (enum)

enum v4w2_mpeg_video_h264_wevew -
    The wevew infowmation fow the H264 video ewementawy stweam.
    Appwicabwe to the H264 encodew. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_1_0``
      - Wevew 1.0
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_1B``
      - Wevew 1B
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_1_1``
      - Wevew 1.1
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_1_2``
      - Wevew 1.2
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_1_3``
      - Wevew 1.3
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_2_0``
      - Wevew 2.0
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_2_1``
      - Wevew 2.1
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_2_2``
      - Wevew 2.2
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_3_0``
      - Wevew 3.0
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_3_1``
      - Wevew 3.1
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_3_2``
      - Wevew 3.2
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_4_0``
      - Wevew 4.0
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_4_1``
      - Wevew 4.1
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_4_2``
      - Wevew 4.2
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_5_0``
      - Wevew 5.0
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_5_1``
      - Wevew 5.1
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_5_2``
      - Wevew 5.2
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_6_0``
      - Wevew 6.0
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_6_1``
      - Wevew 6.1
    * - ``V4W2_MPEG_VIDEO_H264_WEVEW_6_2``
      - Wevew 6.2



.. _v4w2-mpeg-video-mpeg2-wevew:

``V4W2_CID_MPEG_VIDEO_MPEG2_WEVEW``
    (enum)

enum v4w2_mpeg_video_mpeg2_wevew -
    The wevew infowmation fow the MPEG2 ewementawy stweam. Appwicabwe to
    MPEG2 codecs. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_MPEG2_WEVEW_WOW``
      - Wow Wevew (WW)
    * - ``V4W2_MPEG_VIDEO_MPEG2_WEVEW_MAIN``
      - Main Wevew (MW)
    * - ``V4W2_MPEG_VIDEO_MPEG2_WEVEW_HIGH_1440``
      - High-1440 Wevew (H-14)
    * - ``V4W2_MPEG_VIDEO_MPEG2_WEVEW_HIGH``
      - High Wevew (HW)



.. _v4w2-mpeg-video-mpeg4-wevew:

``V4W2_CID_MPEG_VIDEO_MPEG4_WEVEW``
    (enum)

enum v4w2_mpeg_video_mpeg4_wevew -
    The wevew infowmation fow the MPEG4 ewementawy stweam. Appwicabwe to
    the MPEG4 encodew. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_0``
      - Wevew 0
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_0B``
      - Wevew 0b
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_1``
      - Wevew 1
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_2``
      - Wevew 2
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_3``
      - Wevew 3
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_3B``
      - Wevew 3b
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_4``
      - Wevew 4
    * - ``V4W2_MPEG_VIDEO_MPEG4_WEVEW_5``
      - Wevew 5



.. _v4w2-mpeg-video-h264-pwofiwe:

``V4W2_CID_MPEG_VIDEO_H264_PWOFIWE``
    (enum)

enum v4w2_mpeg_video_h264_pwofiwe -
    The pwofiwe infowmation fow H264. Appwicabwe to the H264 encodew.
    Possibwe vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{10.2cm}|p{7.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE``
      - Basewine pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_BASEWINE``
      - Constwained Basewine pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN``
      - Main pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED``
      - Extended pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH``
      - High pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_10``
      - High 10 pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_422``
      - High 422 pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_444_PWEDICTIVE``
      - High 444 Pwedictive pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_10_INTWA``
      - High 10 Intwa pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_422_INTWA``
      - High 422 Intwa pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_444_INTWA``
      - High 444 Intwa pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_CAVWC_444_INTWA``
      - CAVWC 444 Intwa pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_SCAWABWE_BASEWINE``
      - Scawabwe Basewine pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_SCAWABWE_HIGH``
      - Scawabwe High pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_SCAWABWE_HIGH_INTWA``
      - Scawabwe High Intwa pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_STEWEO_HIGH``
      - Steweo High pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_MUWTIVIEW_HIGH``
      - Muwtiview High pwofiwe
    * - ``V4W2_MPEG_VIDEO_H264_PWOFIWE_CONSTWAINED_HIGH``
      - Constwained High pwofiwe

.. waw:: watex

    \nowmawsize

.. _v4w2-mpeg-video-mpeg2-pwofiwe:

``V4W2_CID_MPEG_VIDEO_MPEG2_PWOFIWE``
    (enum)

enum v4w2_mpeg_video_mpeg2_pwofiwe -
    The pwofiwe infowmation fow MPEG2. Appwicabwe to MPEG2 codecs.
    Possibwe vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{10.2cm}|p{7.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SIMPWE``
      - Simpwe pwofiwe (SP)
    * - ``V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_MAIN``
      - Main pwofiwe (MP)
    * - ``V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SNW_SCAWABWE``
      - SNW Scawabwe pwofiwe (SNW)
    * - ``V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_SPATIAWWY_SCAWABWE``
      - Spatiawwy Scawabwe pwofiwe (Spt)
    * - ``V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_HIGH``
      - High pwofiwe (HP)
    * - ``V4W2_MPEG_VIDEO_MPEG2_PWOFIWE_MUWTIVIEW``
      - Muwti-view pwofiwe (MVP)


.. waw:: watex

    \nowmawsize

.. _v4w2-mpeg-video-mpeg4-pwofiwe:

``V4W2_CID_MPEG_VIDEO_MPEG4_PWOFIWE``
    (enum)

enum v4w2_mpeg_video_mpeg4_pwofiwe -
    The pwofiwe infowmation fow MPEG4. Appwicabwe to the MPEG4 encodew.
    Possibwe vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{11.8cm}|p{5.7cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE``
      - Simpwe pwofiwe
    * - ``V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_SIMPWE``
      - Advanced Simpwe pwofiwe
    * - ``V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_COWE``
      - Cowe pwofiwe
    * - ``V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_SIMPWE_SCAWABWE``
      - Simpwe Scawabwe pwofiwe
    * - ``V4W2_MPEG_VIDEO_MPEG4_PWOFIWE_ADVANCED_CODING_EFFICIENCY``
      - Advanced Coding Efficiency pwofiwe

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_VIDEO_MAX_WEF_PIC (integew)``
    The maximum numbew of wefewence pictuwes used fow encoding.
    Appwicabwe to the encodew.

.. _v4w2-mpeg-video-muwti-swice-mode:

``V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MODE``
    (enum)

enum v4w2_mpeg_video_muwti_swice_mode -
    Detewmines how the encodew shouwd handwe division of fwame into
    swices. Appwicabwe to the encodew. Possibwe vawues awe:



.. tabuwawcowumns:: |p{9.6cm}|p{7.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_SINGWE``
      - Singwe swice pew fwame.
    * - ``V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_MB``
      - Muwtipwe swices with set maximum numbew of macwobwocks pew swice.
    * - ``V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_BYTES``
      - Muwtipwe swice with set maximum size in bytes pew swice.



``V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MAX_MB (integew)``
    The maximum numbew of macwobwocks in a swice. Used when
    ``V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MODE`` is set to
    ``V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_MB``. Appwicabwe to the
    encodew.

``V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MAX_BYTES (integew)``
    The maximum size of a swice in bytes. Used when
    ``V4W2_CID_MPEG_VIDEO_MUWTI_SWICE_MODE`` is set to
    ``V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_BYTES``. Appwicabwe to the
    encodew.

.. _v4w2-mpeg-video-h264-woop-fiwtew-mode:

``V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE``
    (enum)

enum v4w2_mpeg_video_h264_woop_fiwtew_mode -
    Woop fiwtew mode fow H264 encodew. Possibwe vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{13.5cm}|p{4.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_ENABWED``
      - Woop fiwtew is enabwed.
    * - ``V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_DISABWED``
      - Woop fiwtew is disabwed.
    * - ``V4W2_MPEG_VIDEO_H264_WOOP_FIWTEW_MODE_DISABWED_AT_SWICE_BOUNDAWY``
      - Woop fiwtew is disabwed at the swice boundawy.

.. waw:: watex

    \nowmawsize


``V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_AWPHA (integew)``
    Woop fiwtew awpha coefficient, defined in the H264 standawd.
    This vawue cowwesponds to the swice_awpha_c0_offset_div2 swice headew
    fiewd, and shouwd be in the wange of -6 to +6, incwusive. The actuaw awpha
    offset FiwtewOffsetA is twice this vawue.
    Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_WOOP_FIWTEW_BETA (integew)``
    Woop fiwtew beta coefficient, defined in the H264 standawd.
    This cowwesponds to the swice_beta_offset_div2 swice headew fiewd, and
    shouwd be in the wange of -6 to +6, incwusive. The actuaw beta offset
    FiwtewOffsetB is twice this vawue.
    Appwicabwe to the H264 encodew.

.. _v4w2-mpeg-video-h264-entwopy-mode:

``V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE``
    (enum)

enum v4w2_mpeg_video_h264_entwopy_mode -
    Entwopy coding mode fow H264 - CABAC/CAVAWC. Appwicabwe to the H264
    encodew. Possibwe vawues awe:


.. tabuwawcowumns:: |p{9.0cm}|p{8.5cm}|


.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CAVWC``
      - Use CAVWC entwopy coding.
    * - ``V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CABAC``
      - Use CABAC entwopy coding.



``V4W2_CID_MPEG_VIDEO_H264_8X8_TWANSFOWM (boowean)``
    Enabwe 8X8 twansfowm fow H264. Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_CONSTWAINED_INTWA_PWEDICTION (boowean)``
    Enabwe constwained intwa pwediction fow H264. Appwicabwe to the H264
    encodew.

``V4W2_CID_MPEG_VIDEO_H264_CHWOMA_QP_INDEX_OFFSET (integew)``
    Specify the offset that shouwd be added to the wuma quantization
    pawametew to detewmine the chwoma quantization pawametew. Appwicabwe
    to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_CYCWIC_INTWA_WEFWESH_MB (integew)``
    Cycwic intwa macwobwock wefwesh. This is the numbew of continuous
    macwobwocks wefweshed evewy fwame. Each fwame a successive set of
    macwobwocks is wefweshed untiw the cycwe compwetes and stawts fwom
    the top of the fwame. Setting this contwow to zewo means that
    macwobwocks wiww not be wefweshed.  Note that this contwow wiww not
    take effect when ``V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD`` contwow
    is set to non zewo vawue.
    Appwicabwe to H264, H263 and MPEG4 encodew.

``V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE (enum)``

enum v4w2_mpeg_video_intwa_wefwesh_pewiod_type -
    Sets the type of intwa wefwesh. The pewiod to wefwesh
    the whowe fwame is specified by V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD.
    Note that if this contwow is not pwesent, then it is undefined what
    wefwesh type is used and it is up to the dwivew to decide.
    Appwicabwe to H264 and HEVC encodews. Possibwe vawues awe:

.. tabuwawcowumns:: |p{9.6cm}|p{7.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE_WANDOM``
      - The whowe fwame is compwetewy wefweshed wandomwy
        aftew the specified pewiod.
    * - ``V4W2_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD_TYPE_CYCWIC``
      - The whowe fwame MBs awe compwetewy wefweshed in cycwic owdew
        aftew the specified pewiod.

``V4W2_CID_MPEG_VIDEO_INTWA_WEFWESH_PEWIOD (integew)``
    Intwa macwobwock wefwesh pewiod. This sets the pewiod to wefwesh
    the whowe fwame. In othew wowds, this defines the numbew of fwames
    fow which the whowe fwame wiww be intwa-wefweshed.  An exampwe:
    setting pewiod to 1 means that the whowe fwame wiww be wefweshed,
    setting pewiod to 2 means that the hawf of macwobwocks wiww be
    intwa-wefweshed on fwameX and the othew hawf of macwobwocks
    wiww be wefweshed in fwameX + 1 and so on. Setting the pewiod to
    zewo means no pewiod is specified.
    Note that if the cwient sets this contwow to non zewo vawue the
    ``V4W2_CID_MPEG_VIDEO_CYCWIC_INTWA_WEFWESH_MB`` contwow shaww be
    ignowed. Appwicabwe to H264 and HEVC encodews.

``V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE (boowean)``
    Fwame wevew wate contwow enabwe. If this contwow is disabwed then
    the quantization pawametew fow each fwame type is constant and set
    with appwopwiate contwows (e.g.
    ``V4W2_CID_MPEG_VIDEO_H263_I_FWAME_QP``). If fwame wate contwow is
    enabwed then quantization pawametew is adjusted to meet the chosen
    bitwate. Minimum and maximum vawue fow the quantization pawametew
    can be set with appwopwiate contwows (e.g.
    ``V4W2_CID_MPEG_VIDEO_H263_MIN_QP``). Appwicabwe to encodews.

``V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE (boowean)``
    Macwobwock wevew wate contwow enabwe. Appwicabwe to the MPEG4 and
    H264 encodews.

``V4W2_CID_MPEG_VIDEO_MPEG4_QPEW (boowean)``
    Quawtew pixew motion estimation fow MPEG4. Appwicabwe to the MPEG4
    encodew.

``V4W2_CID_MPEG_VIDEO_H263_I_FWAME_QP (integew)``
    Quantization pawametew fow an I fwame fow H263. Vawid wange: fwom 1
    to 31.

``V4W2_CID_MPEG_VIDEO_H263_MIN_QP (integew)``
    Minimum quantization pawametew fow H263. Vawid wange: fwom 1 to 31.

``V4W2_CID_MPEG_VIDEO_H263_MAX_QP (integew)``
    Maximum quantization pawametew fow H263. Vawid wange: fwom 1 to 31.

``V4W2_CID_MPEG_VIDEO_H263_P_FWAME_QP (integew)``
    Quantization pawametew fow an P fwame fow H263. Vawid wange: fwom 1
    to 31.

``V4W2_CID_MPEG_VIDEO_H263_B_FWAME_QP (integew)``
    Quantization pawametew fow an B fwame fow H263. Vawid wange: fwom 1
    to 31.

``V4W2_CID_MPEG_VIDEO_H264_I_FWAME_QP (integew)``
    Quantization pawametew fow an I fwame fow H264. Vawid wange: fwom 0
    to 51.

``V4W2_CID_MPEG_VIDEO_H264_MIN_QP (integew)``
    Minimum quantization pawametew fow H264. Vawid wange: fwom 0 to 51.

``V4W2_CID_MPEG_VIDEO_H264_MAX_QP (integew)``
    Maximum quantization pawametew fow H264. Vawid wange: fwom 0 to 51.

``V4W2_CID_MPEG_VIDEO_H264_P_FWAME_QP (integew)``
    Quantization pawametew fow an P fwame fow H264. Vawid wange: fwom 0
    to 51.

``V4W2_CID_MPEG_VIDEO_H264_B_FWAME_QP (integew)``
    Quantization pawametew fow an B fwame fow H264. Vawid wange: fwom 0
    to 51.

``V4W2_CID_MPEG_VIDEO_H264_I_FWAME_MIN_QP (integew)``
    Minimum quantization pawametew fow the H264 I fwame to wimit I fwame
    quawity to a wange. Vawid wange: fwom 0 to 51. If
    V4W2_CID_MPEG_VIDEO_H264_MIN_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_H264_I_FWAME_MAX_QP (integew)``
    Maximum quantization pawametew fow the H264 I fwame to wimit I fwame
    quawity to a wange. Vawid wange: fwom 0 to 51. If
    V4W2_CID_MPEG_VIDEO_H264_MAX_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_H264_P_FWAME_MIN_QP (integew)``
    Minimum quantization pawametew fow the H264 P fwame to wimit P fwame
    quawity to a wange. Vawid wange: fwom 0 to 51. If
    V4W2_CID_MPEG_VIDEO_H264_MIN_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_H264_P_FWAME_MAX_QP (integew)``
    Maximum quantization pawametew fow the H264 P fwame to wimit P fwame
    quawity to a wange. Vawid wange: fwom 0 to 51. If
    V4W2_CID_MPEG_VIDEO_H264_MAX_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_H264_B_FWAME_MIN_QP (integew)``
    Minimum quantization pawametew fow the H264 B fwame to wimit B fwame
    quawity to a wange. Vawid wange: fwom 0 to 51. If
    V4W2_CID_MPEG_VIDEO_H264_MIN_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_H264_B_FWAME_MAX_QP (integew)``
    Maximum quantization pawametew fow the H264 B fwame to wimit B fwame
    quawity to a wange. Vawid wange: fwom 0 to 51. If
    V4W2_CID_MPEG_VIDEO_H264_MAX_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_MPEG4_I_FWAME_QP (integew)``
    Quantization pawametew fow an I fwame fow MPEG4. Vawid wange: fwom 1
    to 31.

``V4W2_CID_MPEG_VIDEO_MPEG4_MIN_QP (integew)``
    Minimum quantization pawametew fow MPEG4. Vawid wange: fwom 1 to 31.

``V4W2_CID_MPEG_VIDEO_MPEG4_MAX_QP (integew)``
    Maximum quantization pawametew fow MPEG4. Vawid wange: fwom 1 to 31.

``V4W2_CID_MPEG_VIDEO_MPEG4_P_FWAME_QP (integew)``
    Quantization pawametew fow an P fwame fow MPEG4. Vawid wange: fwom 1
    to 31.

``V4W2_CID_MPEG_VIDEO_MPEG4_B_FWAME_QP (integew)``
    Quantization pawametew fow an B fwame fow MPEG4. Vawid wange: fwom 1
    to 31.

.. _v4w2-mpeg-video-vbv-size:

``V4W2_CID_MPEG_VIDEO_VBV_SIZE (integew)``
    The Video Buffew Vewifiew size in kiwobytes, it is used as a
    wimitation of fwame skip. The VBV is defined in the standawd as a
    mean to vewify that the pwoduced stweam wiww be successfuwwy
    decoded. The standawd descwibes it as "Pawt of a hypotheticaw
    decodew that is conceptuawwy connected to the output of the encodew.
    Its puwpose is to pwovide a constwaint on the vawiabiwity of the
    data wate that an encodew ow editing pwocess may pwoduce.".
    Appwicabwe to the MPEG1, MPEG2, MPEG4 encodews.

.. _v4w2-mpeg-video-vbv-deway:

``V4W2_CID_MPEG_VIDEO_VBV_DEWAY (integew)``
    Sets the initiaw deway in miwwiseconds fow VBV buffew contwow.

.. _v4w2-mpeg-video-how-seawch-wange:

``V4W2_CID_MPEG_VIDEO_MV_H_SEAWCH_WANGE (integew)``
    Howizontaw seawch wange defines maximum howizontaw seawch awea in
    pixews to seawch and match fow the pwesent Macwobwock (MB) in the
    wefewence pictuwe. This V4W2 contwow macwo is used to set howizontaw
    seawch wange fow motion estimation moduwe in video encodew.

.. _v4w2-mpeg-video-vewt-seawch-wange:

``V4W2_CID_MPEG_VIDEO_MV_V_SEAWCH_WANGE (integew)``
    Vewticaw seawch wange defines maximum vewticaw seawch awea in pixews
    to seawch and match fow the pwesent Macwobwock (MB) in the wefewence
    pictuwe. This V4W2 contwow macwo is used to set vewticaw seawch
    wange fow motion estimation moduwe in video encodew.

.. _v4w2-mpeg-video-fowce-key-fwame:

``V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME (button)``
    Fowce a key fwame fow the next queued buffew. Appwicabwe to
    encodews. This is a genewaw, codec-agnostic keyfwame contwow.

.. _v4w2-mpeg-video-h264-cpb-size:

``V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE (integew)``
    The Coded Pictuwe Buffew size in kiwobytes, it is used as a
    wimitation of fwame skip. The CPB is defined in the H264 standawd as
    a mean to vewify that the pwoduced stweam wiww be successfuwwy
    decoded. Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD (integew)``
    Pewiod between I-fwames in the open GOP fow H264. In case of an open
    GOP this is the pewiod between two I-fwames. The pewiod between IDW
    (Instantaneous Decoding Wefwesh) fwames is taken fwom the GOP_SIZE
    contwow. An IDW fwame, which stands fow Instantaneous Decoding
    Wefwesh is an I-fwame aftew which no pwiow fwames awe wefewenced.
    This means that a stweam can be westawted fwom an IDW fwame without
    the need to stowe ow decode any pwevious fwames. Appwicabwe to the
    H264 encodew.

.. _v4w2-mpeg-video-headew-mode:

``V4W2_CID_MPEG_VIDEO_HEADEW_MODE``
    (enum)

enum v4w2_mpeg_video_headew_mode -
    Detewmines whethew the headew is wetuwned as the fiwst buffew ow is
    it wetuwned togethew with the fiwst fwame. Appwicabwe to encodews.
    Possibwe vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{10.3cm}|p{7.2cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_HEADEW_MODE_SEPAWATE``
      - The stweam headew is wetuwned sepawatewy in the fiwst buffew.
    * - ``V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME``
      - The stweam headew is wetuwned togethew with the fiwst encoded
	fwame.

.. waw:: watex

    \nowmawsize


``V4W2_CID_MPEG_VIDEO_WEPEAT_SEQ_HEADEW (boowean)``
    Wepeat the video sequence headews. Wepeating these headews makes
    wandom access to the video stweam easiew. Appwicabwe to the MPEG1, 2
    and 4 encodew.

``V4W2_CID_MPEG_VIDEO_DECODEW_MPEG4_DEBWOCK_FIWTEW (boowean)``
    Enabwed the debwocking post pwocessing fiwtew fow MPEG4 decodew.
    Appwicabwe to the MPEG4 decodew.

``V4W2_CID_MPEG_VIDEO_MPEG4_VOP_TIME_WES (integew)``
    vop_time_incwement_wesowution vawue fow MPEG4. Appwicabwe to the
    MPEG4 encodew.

``V4W2_CID_MPEG_VIDEO_MPEG4_VOP_TIME_INC (integew)``
    vop_time_incwement vawue fow MPEG4. Appwicabwe to the MPEG4
    encodew.

``V4W2_CID_MPEG_VIDEO_H264_SEI_FWAME_PACKING (boowean)``
    Enabwe genewation of fwame packing suppwementaw enhancement
    infowmation in the encoded bitstweam. The fwame packing SEI message
    contains the awwangement of W and W pwanes fow 3D viewing.
    Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_SEI_FP_CUWWENT_FWAME_0 (boowean)``
    Sets cuwwent fwame as fwame0 in fwame packing SEI. Appwicabwe to the
    H264 encodew.

.. _v4w2-mpeg-video-h264-sei-fp-awwangement-type:

``V4W2_CID_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE``
    (enum)

enum v4w2_mpeg_video_h264_sei_fp_awwangement_type -
    Fwame packing awwangement type fow H264 SEI. Appwicabwe to the H264
    encodew. Possibwe vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{12cm}|p{5.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_CHEKEWBOAWD``
      - Pixews awe awtewnativewy fwom W and W.
    * - ``V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_COWUMN``
      - W and W awe intewwaced by cowumn.
    * - ``V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_WOW``
      - W and W awe intewwaced by wow.
    * - ``V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_SIDE_BY_SIDE``
      - W is on the weft, W on the wight.
    * - ``V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_TOP_BOTTOM``
      - W is on top, W on bottom.
    * - ``V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_TEMPOWAW``
      - One view pew fwame.

.. waw:: watex

    \nowmawsize



``V4W2_CID_MPEG_VIDEO_H264_FMO (boowean)``
    Enabwes fwexibwe macwobwock owdewing in the encoded bitstweam. It is
    a technique used fow westwuctuwing the owdewing of macwobwocks in
    pictuwes. Appwicabwe to the H264 encodew.

.. _v4w2-mpeg-video-h264-fmo-map-type:

``V4W2_CID_MPEG_VIDEO_H264_FMO_MAP_TYPE``
   (enum)

enum v4w2_mpeg_video_h264_fmo_map_type -
    When using FMO, the map type divides the image in diffewent scan
    pattewns of macwobwocks. Appwicabwe to the H264 encodew. Possibwe
    vawues awe:

.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{12.5cm}|p{5.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_INTEWWEAVED_SWICES``
      - Swices awe intewweaved one aftew othew with macwobwocks in wun
	wength owdew.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_SCATTEWED_SWICES``
      - Scattews the macwobwocks based on a mathematicaw function known to
	both encodew and decodew.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_FOWEGWOUND_WITH_WEFT_OVEW``
      - Macwobwocks awwanged in wectanguwaw aweas ow wegions of intewest.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_BOX_OUT``
      - Swice gwoups gwow in a cycwic way fwom centwe to outwawds.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WASTEW_SCAN``
      - Swice gwoups gwow in wastew scan pattewn fwom weft to wight.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WIPE_SCAN``
      - Swice gwoups gwow in wipe scan pattewn fwom top to bottom.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_EXPWICIT``
      - Usew defined map type.

.. waw:: watex

    \nowmawsize



``V4W2_CID_MPEG_VIDEO_H264_FMO_SWICE_GWOUP (integew)``
    Numbew of swice gwoups in FMO. Appwicabwe to the H264 encodew.

.. _v4w2-mpeg-video-h264-fmo-change-diwection:

``V4W2_CID_MPEG_VIDEO_H264_FMO_CHANGE_DIWECTION``
    (enum)

enum v4w2_mpeg_video_h264_fmo_change_diw -
    Specifies a diwection of the swice gwoup change fow wastew and wipe
    maps. Appwicabwe to the H264 encodew. Possibwe vawues awe:

.. tabuwawcowumns:: |p{9.6cm}|p{7.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_FMO_CHANGE_DIW_WIGHT``
      - Wastew scan ow wipe wight.
    * - ``V4W2_MPEG_VIDEO_H264_FMO_CHANGE_DIW_WEFT``
      - Wevewse wastew scan ow wipe weft.



``V4W2_CID_MPEG_VIDEO_H264_FMO_CHANGE_WATE (integew)``
    Specifies the size of the fiwst swice gwoup fow wastew and wipe map.
    Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_FMO_WUN_WENGTH (integew)``
    Specifies the numbew of consecutive macwobwocks fow the intewweaved
    map. Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_ASO (boowean)``
    Enabwes awbitwawy swice owdewing in encoded bitstweam. Appwicabwe to
    the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_ASO_SWICE_OWDEW (integew)``
    Specifies the swice owdew in ASO. Appwicabwe to the H264 encodew.
    The suppwied 32-bit integew is intewpweted as fowwows (bit 0 = weast
    significant bit):



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - Bit 0:15
      - Swice ID
    * - Bit 16:32
      - Swice position ow owdew



``V4W2_CID_MPEG_VIDEO_H264_HIEWAWCHICAW_CODING (boowean)``
    Enabwes H264 hiewawchicaw coding. Appwicabwe to the H264 encodew.

.. _v4w2-mpeg-video-h264-hiewawchicaw-coding-type:

``V4W2_CID_MPEG_VIDEO_H264_HIEWAWCHICAW_CODING_TYPE``
    (enum)

enum v4w2_mpeg_video_h264_hiewawchicaw_coding_type -
    Specifies the hiewawchicaw coding type. Appwicabwe to the H264
    encodew. Possibwe vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_H264_HIEWAWCHICAW_CODING_B``
      - Hiewawchicaw B coding.
    * - ``V4W2_MPEG_VIDEO_H264_HIEWAWCHICAW_CODING_P``
      - Hiewawchicaw P coding.



``V4W2_CID_MPEG_VIDEO_H264_HIEWAWCHICAW_CODING_WAYEW (integew)``
    Specifies the numbew of hiewawchicaw coding wayews. Appwicabwe to
    the H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEWAWCHICAW_CODING_WAYEW_QP (integew)``
    Specifies a usew defined QP fow each wayew. Appwicabwe to the H264
    encodew. The suppwied 32-bit integew is intewpweted as fowwows (bit
    0 = weast significant bit):



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - Bit 0:15
      - QP vawue
    * - Bit 16:32
      - Wayew numbew

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W0_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 0 fow H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W1_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 1 fow H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W2_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 2 fow H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W3_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 3 fow H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W4_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 4 fow H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W5_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 5 fow H264 encodew.

``V4W2_CID_MPEG_VIDEO_H264_HIEW_CODING_W6_BW (integew)``
    Indicates bit wate (bps) fow hiewawchicaw coding wayew 6 fow H264 encodew.

``V4W2_CID_FWHT_I_FWAME_QP (integew)``
    Quantization pawametew fow an I fwame fow FWHT. Vawid wange: fwom 1
    to 31.

``V4W2_CID_FWHT_P_FWAME_QP (integew)``
    Quantization pawametew fow a P fwame fow FWHT. Vawid wange: fwom 1
    to 31.

.. waw:: watex

    \nowmawsize


MFC 5.1 MPEG Contwows
=====================

The fowwowing MPEG cwass contwows deaw with MPEG decoding and encoding
settings that awe specific to the Muwti Fowmat Codec 5.1 device pwesent
in the S5P famiwy of SoCs by Samsung.


.. _mfc51-contwow-id:

MFC 5.1 Contwow IDs
-------------------

``V4W2_CID_MPEG_MFC51_VIDEO_DECODEW_H264_DISPWAY_DEWAY_ENABWE (boowean)``
    If the dispway deway is enabwed then the decodew is fowced to wetuwn
    a CAPTUWE buffew (decoded fwame) aftew pwocessing a cewtain numbew
    of OUTPUT buffews. The deway can be set thwough
    ``V4W2_CID_MPEG_MFC51_VIDEO_DECODEW_H264_DISPWAY_DEWAY``. This
    featuwe can be used fow exampwe fow genewating thumbnaiws of videos.
    Appwicabwe to the H264 decodew.

    .. note::

       This contwow is depwecated. Use the standawd
       ``V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY_ENABWE`` contwow instead.

``V4W2_CID_MPEG_MFC51_VIDEO_DECODEW_H264_DISPWAY_DEWAY (integew)``
    Dispway deway vawue fow H264 decodew. The decodew is fowced to
    wetuwn a decoded fwame aftew the set 'dispway deway' numbew of
    fwames. If this numbew is wow it may wesuwt in fwames wetuwned out
    of dispway owdew, in addition the hawdwawe may stiww be using the
    wetuwned buffew as a wefewence pictuwe fow subsequent fwames.

    .. note::

       This contwow is depwecated. Use the standawd
       ``V4W2_CID_MPEG_VIDEO_DEC_DISPWAY_DEWAY`` contwow instead.

``V4W2_CID_MPEG_MFC51_VIDEO_H264_NUM_WEF_PIC_FOW_P (integew)``
    The numbew of wefewence pictuwes used fow encoding a P pictuwe.
    Appwicabwe to the H264 encodew.

``V4W2_CID_MPEG_MFC51_VIDEO_PADDING (boowean)``
    Padding enabwe in the encodew - use a cowow instead of wepeating
    bowdew pixews. Appwicabwe to encodews.

``V4W2_CID_MPEG_MFC51_VIDEO_PADDING_YUV (integew)``
    Padding cowow in the encodew. Appwicabwe to encodews. The suppwied
    32-bit integew is intewpweted as fowwows (bit 0 = weast significant
    bit):



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - Bit 0:7
      - V chwominance infowmation
    * - Bit 8:15
      - U chwominance infowmation
    * - Bit 16:23
      - Y wuminance infowmation
    * - Bit 24:31
      - Must be zewo.



``V4W2_CID_MPEG_MFC51_VIDEO_WC_WEACTION_COEFF (integew)``
    Weaction coefficient fow MFC wate contwow. Appwicabwe to encodews.

    .. note::

       #. Vawid onwy when the fwame wevew WC is enabwed.

       #. Fow tight CBW, this fiewd must be smaww (ex. 2 ~ 10). Fow
	  VBW, this fiewd must be wawge (ex. 100 ~ 1000).

       #. It is not wecommended to use the gweatew numbew than
	  FWAME_WATE * (10^9 / BIT_WATE).

``V4W2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_WC_DAWK (boowean)``
    Adaptive wate contwow fow dawk wegion. Vawid onwy when H.264 and
    macwobwock wevew WC is enabwed
    (``V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE``). Appwicabwe to the H264
    encodew.

``V4W2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_WC_SMOOTH (boowean)``
    Adaptive wate contwow fow smooth wegion. Vawid onwy when H.264 and
    macwobwock wevew WC is enabwed
    (``V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE``). Appwicabwe to the H264
    encodew.

``V4W2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_WC_STATIC (boowean)``
    Adaptive wate contwow fow static wegion. Vawid onwy when H.264 and
    macwobwock wevew WC is enabwed
    (``V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE``). Appwicabwe to the H264
    encodew.

``V4W2_CID_MPEG_MFC51_VIDEO_H264_ADAPTIVE_WC_ACTIVITY (boowean)``
    Adaptive wate contwow fow activity wegion. Vawid onwy when H.264 and
    macwobwock wevew WC is enabwed
    (``V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE``). Appwicabwe to the H264
    encodew.

.. _v4w2-mpeg-mfc51-video-fwame-skip-mode:

``V4W2_CID_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE``
    (enum)

    .. note::

       This contwow is depwecated. Use the standawd
       ``V4W2_CID_MPEG_VIDEO_FWAME_SKIP_MODE`` contwow instead.

enum v4w2_mpeg_mfc51_video_fwame_skip_mode -
    Indicates in what conditions the encodew shouwd skip fwames. If
    encoding a fwame wouwd cause the encoded stweam to be wawgew then a
    chosen data wimit then the fwame wiww be skipped. Possibwe vawues
    awe:


.. tabuwawcowumns:: |p{9.4cm}|p{8.1cm}|

.. waw:: watex

    \smaww

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_DISABWED``
      - Fwame skip mode is disabwed.
    * - ``V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_WEVEW_WIMIT``
      - Fwame skip mode enabwed and buffew wimit is set by the chosen
	wevew and is defined by the standawd.
    * - ``V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT``
      - Fwame skip mode enabwed and buffew wimit is set by the VBV
	(MPEG1/2/4) ow CPB (H264) buffew size contwow.

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_MFC51_VIDEO_WC_FIXED_TAWGET_BIT (integew)``
    Enabwe wate-contwow with fixed tawget bit. If this setting is
    enabwed, then the wate contwow wogic of the encodew wiww cawcuwate
    the avewage bitwate fow a GOP and keep it bewow ow equaw the set
    bitwate tawget. Othewwise the wate contwow wogic cawcuwates the
    ovewaww avewage bitwate fow the stweam and keeps it bewow ow equaw
    to the set bitwate. In the fiwst case the avewage bitwate fow the
    whowe stweam wiww be smawwew then the set bitwate. This is caused
    because the avewage is cawcuwated fow smawwew numbew of fwames, on
    the othew hand enabwing this setting wiww ensuwe that the stweam
    wiww meet tight bandwidth constwaints. Appwicabwe to encodews.

.. _v4w2-mpeg-mfc51-video-fowce-fwame-type:

``V4W2_CID_MPEG_MFC51_VIDEO_FOWCE_FWAME_TYPE``
    (enum)

enum v4w2_mpeg_mfc51_video_fowce_fwame_type -
    Fowce a fwame type fow the next queued buffew. Appwicabwe to
    encodews. Possibwe vawues awe:

.. tabuwawcowumns:: |p{9.9cm}|p{7.6cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_MFC51_FOWCE_FWAME_TYPE_DISABWED``
      - Fowcing a specific fwame type disabwed.
    * - ``V4W2_MPEG_MFC51_FOWCE_FWAME_TYPE_I_FWAME``
      - Fowce an I-fwame.
    * - ``V4W2_MPEG_MFC51_FOWCE_FWAME_TYPE_NOT_CODED``
      - Fowce a non-coded fwame.


CX2341x MPEG Contwows
=====================

The fowwowing MPEG cwass contwows deaw with MPEG encoding settings that
awe specific to the Conexant CX23415 and CX23416 MPEG encoding chips.


.. _cx2341x-contwow-id:

CX2341x Contwow IDs
-------------------

.. _v4w2-mpeg-cx2341x-video-spatiaw-fiwtew-mode:

``V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE``
    (enum)

enum v4w2_mpeg_cx2341x_video_spatiaw_fiwtew_mode -
    Sets the Spatiaw Fiwtew mode (defauwt ``MANUAW``). Possibwe vawues
    awe:


.. tabuwawcowumns:: |p{11.5cm}|p{6.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_MANUAW``
      - Choose the fiwtew manuawwy
    * - ``V4W2_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW_MODE_AUTO``
      - Choose the fiwtew automaticawwy



``V4W2_CID_MPEG_CX2341X_VIDEO_SPATIAW_FIWTEW (integew (0-15))``
    The setting fow the Spatiaw Fiwtew. 0 = off, 15 = maximum. (Defauwt
    is 0.)

.. _wuma-spatiaw-fiwtew-type:

``V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE``
    (enum)

enum v4w2_mpeg_cx2341x_video_wuma_spatiaw_fiwtew_type -
    Sewect the awgowithm to use fow the Wuma Spatiaw Fiwtew (defauwt
    ``1D_HOW``). Possibwe vawues:

.. tabuwawcowumns:: |p{13.1cm}|p{4.4cm}|

.. waw:: watex

    \footnotesize

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_OFF``
      - No fiwtew
    * - ``V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_1D_HOW``
      - One-dimensionaw howizontaw
    * - ``V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_1D_VEWT``
      - One-dimensionaw vewticaw
    * - ``V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_2D_HV_SEPAWABWE``
      - Two-dimensionaw sepawabwe
    * - ``V4W2_MPEG_CX2341X_VIDEO_WUMA_SPATIAW_FIWTEW_TYPE_2D_SYM_NON_SEPAWABWE``
      - Two-dimensionaw symmetwicaw non-sepawabwe

.. waw:: watex

    \nowmawsize

.. _chwoma-spatiaw-fiwtew-type:

``V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE``
    (enum)

enum v4w2_mpeg_cx2341x_video_chwoma_spatiaw_fiwtew_type -
    Sewect the awgowithm fow the Chwoma Spatiaw Fiwtew (defauwt
    ``1D_HOW``). Possibwe vawues awe:

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{11.0cm}|p{6.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_OFF``
      - No fiwtew
    * - ``V4W2_MPEG_CX2341X_VIDEO_CHWOMA_SPATIAW_FIWTEW_TYPE_1D_HOW``
      - One-dimensionaw howizontaw

.. waw:: watex

    \nowmawsize

.. _v4w2-mpeg-cx2341x-video-tempowaw-fiwtew-mode:

``V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE``
    (enum)

enum v4w2_mpeg_cx2341x_video_tempowaw_fiwtew_mode -
    Sets the Tempowaw Fiwtew mode (defauwt ``MANUAW``). Possibwe vawues
    awe:

.. waw:: watex

    \footnotesize

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_MANUAW``
      - Choose the fiwtew manuawwy
    * - ``V4W2_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW_MODE_AUTO``
      - Choose the fiwtew automaticawwy

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_CX2341X_VIDEO_TEMPOWAW_FIWTEW (integew (0-31))``
    The setting fow the Tempowaw Fiwtew. 0 = off, 31 = maximum. (Defauwt
    is 8 fow fuww-scawe captuwing and 0 fow scawed captuwing.)

.. _v4w2-mpeg-cx2341x-video-median-fiwtew-type:

``V4W2_CID_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE``
    (enum)

enum v4w2_mpeg_cx2341x_video_median_fiwtew_type -
    Median Fiwtew Type (defauwt ``OFF``). Possibwe vawues awe:


.. waw:: watex

    \smaww

.. tabuwawcowumns:: |p{11.0cm}|p{6.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_OFF``
      - No fiwtew
    * - ``V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_HOW``
      - Howizontaw fiwtew
    * - ``V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_VEWT``
      - Vewticaw fiwtew
    * - ``V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_HOW_VEWT``
      - Howizontaw and vewticaw fiwtew
    * - ``V4W2_MPEG_CX2341X_VIDEO_MEDIAN_FIWTEW_TYPE_DIAG``
      - Diagonaw fiwtew

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_BOTTOM (integew (0-255))``
    Thweshowd above which the wuminance median fiwtew is enabwed
    (defauwt 0)

``V4W2_CID_MPEG_CX2341X_VIDEO_WUMA_MEDIAN_FIWTEW_TOP (integew (0-255))``
    Thweshowd bewow which the wuminance median fiwtew is enabwed
    (defauwt 255)

``V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_BOTTOM (integew (0-255))``
    Thweshowd above which the chwoma median fiwtew is enabwed (defauwt
    0)

``V4W2_CID_MPEG_CX2341X_VIDEO_CHWOMA_MEDIAN_FIWTEW_TOP (integew (0-255))``
    Thweshowd bewow which the chwoma median fiwtew is enabwed (defauwt
    255)

``V4W2_CID_MPEG_CX2341X_STWEAM_INSEWT_NAV_PACKETS (boowean)``
    The CX2341X MPEG encodew can insewt one empty MPEG-2 PES packet into
    the stweam between evewy fouw video fwames. The packet size is 2048
    bytes, incwuding the packet_stawt_code_pwefix and stweam_id
    fiewds. The stweam_id is 0xBF (pwivate stweam 2). The paywoad
    consists of 0x00 bytes, to be fiwwed in by the appwication. 0 = do
    not insewt, 1 = insewt packets.


VPX Contwow Wefewence
=====================

The VPX contwows incwude contwows fow encoding pawametews of VPx video
codec.


.. _vpx-contwow-id:

VPX Contwow IDs
---------------

.. _v4w2-vpx-num-pawtitions:

``V4W2_CID_MPEG_VIDEO_VPX_NUM_PAWTITIONS``
    (enum)

enum v4w2_vp8_num_pawtitions -
    The numbew of token pawtitions to use in VP8 encodew. Possibwe
    vawues awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_CID_MPEG_VIDEO_VPX_1_PAWTITION``
      - 1 coefficient pawtition
    * - ``V4W2_CID_MPEG_VIDEO_VPX_2_PAWTITIONS``
      - 2 coefficient pawtitions
    * - ``V4W2_CID_MPEG_VIDEO_VPX_4_PAWTITIONS``
      - 4 coefficient pawtitions
    * - ``V4W2_CID_MPEG_VIDEO_VPX_8_PAWTITIONS``
      - 8 coefficient pawtitions



``V4W2_CID_MPEG_VIDEO_VPX_IMD_DISABWE_4X4 (boowean)``
    Setting this pwevents intwa 4x4 mode in the intwa mode decision.

.. _v4w2-vpx-num-wef-fwames:

``V4W2_CID_MPEG_VIDEO_VPX_NUM_WEF_FWAMES``
    (enum)

enum v4w2_vp8_num_wef_fwames -
    The numbew of wefewence pictuwes fow encoding P fwames. Possibwe
    vawues awe:

.. tabuwawcowumns:: |p{7.5cm}|p{7.5cm}|

.. waw:: watex

    \smaww

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_CID_MPEG_VIDEO_VPX_1_WEF_FWAME``
      - Wast encoded fwame wiww be seawched
    * - ``V4W2_CID_MPEG_VIDEO_VPX_2_WEF_FWAME``
      - Two fwames wiww be seawched among the wast encoded fwame, the
	gowden fwame and the awtewnate wefewence (awtwef) fwame. The
	encodew impwementation wiww decide which two awe chosen.
    * - ``V4W2_CID_MPEG_VIDEO_VPX_3_WEF_FWAME``
      - The wast encoded fwame, the gowden fwame and the awtwef fwame wiww
	be seawched.

.. waw:: watex

    \nowmawsize



``V4W2_CID_MPEG_VIDEO_VPX_FIWTEW_WEVEW (integew)``
    Indicates the woop fiwtew wevew. The adjustment of the woop fiwtew
    wevew is done via a dewta vawue against a basewine woop fiwtew
    vawue.

``V4W2_CID_MPEG_VIDEO_VPX_FIWTEW_SHAWPNESS (integew)``
    This pawametew affects the woop fiwtew. Anything above zewo weakens
    the debwocking effect on the woop fiwtew.

``V4W2_CID_MPEG_VIDEO_VPX_GOWDEN_FWAME_WEF_PEWIOD (integew)``
    Sets the wefwesh pewiod fow the gowden fwame. The pewiod is defined
    in numbew of fwames. Fow a vawue of 'n', evewy nth fwame stawting
    fwom the fiwst key fwame wiww be taken as a gowden fwame. Fow eg.
    fow encoding sequence of 0, 1, 2, 3, 4, 5, 6, 7 whewe the gowden
    fwame wefwesh pewiod is set as 4, the fwames 0, 4, 8 etc wiww be
    taken as the gowden fwames as fwame 0 is awways a key fwame.

.. _v4w2-vpx-gowden-fwame-sew:

``V4W2_CID_MPEG_VIDEO_VPX_GOWDEN_FWAME_SEW``
    (enum)

enum v4w2_vp8_gowden_fwame_sew -
    Sewects the gowden fwame fow encoding. Possibwe vawues awe:

.. waw:: watex

    \scwiptsize

.. tabuwawcowumns:: |p{8.6cm}|p{8.9cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_CID_MPEG_VIDEO_VPX_GOWDEN_FWAME_USE_PWEV``
      - Use the (n-2)th fwame as a gowden fwame, cuwwent fwame index being
	'n'.
    * - ``V4W2_CID_MPEG_VIDEO_VPX_GOWDEN_FWAME_USE_WEF_PEWIOD``
      - Use the pwevious specific fwame indicated by
	``V4W2_CID_MPEG_VIDEO_VPX_GOWDEN_FWAME_WEF_PEWIOD`` as a
	gowden fwame.

.. waw:: watex

    \nowmawsize


``V4W2_CID_MPEG_VIDEO_VPX_MIN_QP (integew)``
    Minimum quantization pawametew fow VP8.

``V4W2_CID_MPEG_VIDEO_VPX_MAX_QP (integew)``
    Maximum quantization pawametew fow VP8.

``V4W2_CID_MPEG_VIDEO_VPX_I_FWAME_QP (integew)``
    Quantization pawametew fow an I fwame fow VP8.

``V4W2_CID_MPEG_VIDEO_VPX_P_FWAME_QP (integew)``
    Quantization pawametew fow a P fwame fow VP8.

.. _v4w2-mpeg-video-vp8-pwofiwe:

``V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE``
    (enum)

enum v4w2_mpeg_video_vp8_pwofiwe -
    This contwow awwows sewecting the pwofiwe fow VP8 encodew.
    This is awso used to enumewate suppowted pwofiwes by VP8 encodew ow decodew.
    Possibwe vawues awe:

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_VP8_PWOFIWE_0``
      - Pwofiwe 0
    * - ``V4W2_MPEG_VIDEO_VP8_PWOFIWE_1``
      - Pwofiwe 1
    * - ``V4W2_MPEG_VIDEO_VP8_PWOFIWE_2``
      - Pwofiwe 2
    * - ``V4W2_MPEG_VIDEO_VP8_PWOFIWE_3``
      - Pwofiwe 3

.. _v4w2-mpeg-video-vp9-pwofiwe:

``V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE``
    (enum)

enum v4w2_mpeg_video_vp9_pwofiwe -
    This contwow awwows sewecting the pwofiwe fow VP9 encodew.
    This is awso used to enumewate suppowted pwofiwes by VP9 encodew ow decodew.
    Possibwe vawues awe:

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_VP9_PWOFIWE_0``
      - Pwofiwe 0
    * - ``V4W2_MPEG_VIDEO_VP9_PWOFIWE_1``
      - Pwofiwe 1
    * - ``V4W2_MPEG_VIDEO_VP9_PWOFIWE_2``
      - Pwofiwe 2
    * - ``V4W2_MPEG_VIDEO_VP9_PWOFIWE_3``
      - Pwofiwe 3

.. _v4w2-mpeg-video-vp9-wevew:

``V4W2_CID_MPEG_VIDEO_VP9_WEVEW (enum)``

enum v4w2_mpeg_video_vp9_wevew -
    This contwow awwows sewecting the wevew fow VP9 encodew.
    This is awso used to enumewate suppowted wevews by VP9 encodew ow decodew.
    Mowe infowmation can be found at
    `webmpwoject <https://www.webmpwoject.owg/vp9/wevews/>`__. Possibwe vawues awe:

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_1_0``
      - Wevew 1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_1_1``
      - Wevew 1.1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_2_0``
      - Wevew 2
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_2_1``
      - Wevew 2.1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_3_0``
      - Wevew 3
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_3_1``
      - Wevew 3.1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_4_0``
      - Wevew 4
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_4_1``
      - Wevew 4.1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_5_0``
      - Wevew 5
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_5_1``
      - Wevew 5.1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_5_2``
      - Wevew 5.2
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_6_0``
      - Wevew 6
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_6_1``
      - Wevew 6.1
    * - ``V4W2_MPEG_VIDEO_VP9_WEVEW_6_2``
      - Wevew 6.2


High Efficiency Video Coding (HEVC/H.265) Contwow Wefewence
===========================================================

The HEVC/H.265 contwows incwude contwows fow encoding pawametews of HEVC/H.265
video codec.


.. _hevc-contwow-id:

HEVC/H.265 Contwow IDs
----------------------

``V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP (integew)``
    Minimum quantization pawametew fow HEVC.
    Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.

``V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP (integew)``
    Maximum quantization pawametew fow HEVC.
    Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.

``V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_QP (integew)``
    Quantization pawametew fow an I fwame fow HEVC.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_QP (integew)``
    Quantization pawametew fow a P fwame fow HEVC.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_QP (integew)``
    Quantization pawametew fow a B fwame fow HEVC.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_MIN_QP (integew)``
    Minimum quantization pawametew fow the HEVC I fwame to wimit I fwame
    quawity to a wange. Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.
    If V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_HEVC_I_FWAME_MAX_QP (integew)``
    Maximum quantization pawametew fow the HEVC I fwame to wimit I fwame
    quawity to a wange. Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.
    If V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_MIN_QP (integew)``
    Minimum quantization pawametew fow the HEVC P fwame to wimit P fwame
    quawity to a wange. Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.
    If V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_HEVC_P_FWAME_MAX_QP (integew)``
    Maximum quantization pawametew fow the HEVC P fwame to wimit P fwame
    quawity to a wange. Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.
    If V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_MIN_QP (integew)``
    Minimum quantization pawametew fow the HEVC B fwame to wimit B fwame
    quawity to a wange. Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.
    If V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_HEVC_B_FWAME_MAX_QP (integew)``
    Maximum quantization pawametew fow the HEVC B fwame to wimit B fwame
    quawity to a wange. Vawid wange: fwom 0 to 51 fow 8 bit and fwom 0 to 63 fow 10 bit.
    If V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP is awso set, the quantization pawametew
    shouwd be chosen to meet both wequiwements.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_QP (boowean)``
    HIEWAWCHICAW_QP awwows the host to specify the quantization pawametew
    vawues fow each tempowaw wayew thwough HIEWAWCHICAW_QP_WAYEW. This is
    vawid onwy if HIEWAWCHICAW_CODING_WAYEW is gweatew than 1. Setting the
    contwow vawue to 1 enabwes setting of the QP vawues fow the wayews.

.. _v4w2-hevc-hiew-coding-type:

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_TYPE``
    (enum)

enum v4w2_mpeg_video_hevc_hiew_coding_type -
    Sewects the hiewawchicaw coding type fow encoding. Possibwe vawues awe:

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{8.2cm}|p{9.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_HEVC_HIEWAWCHICAW_CODING_B``
      - Use the B fwame fow hiewawchicaw coding.
    * - ``V4W2_MPEG_VIDEO_HEVC_HIEWAWCHICAW_CODING_P``
      - Use the P fwame fow hiewawchicaw coding.

.. waw:: watex

    \nowmawsize


``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_WAYEW (integew)``
    Sewects the hiewawchicaw coding wayew. In nowmaw encoding
    (non-hiewawchiaw coding), it shouwd be zewo. Possibwe vawues awe [0, 6].
    0 indicates HIEWAWCHICAW CODING WAYEW 0, 1 indicates HIEWAWCHICAW CODING
    WAYEW 1 and so on.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W0_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 0.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W1_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 1.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W2_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 2.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W3_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 3.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W4_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 4.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W5_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 5.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W6_QP (integew)``
    Indicates quantization pawametew fow hiewawchicaw coding wayew 6.
    Vawid wange: [V4W2_CID_MPEG_VIDEO_HEVC_MIN_QP,
    V4W2_CID_MPEG_VIDEO_HEVC_MAX_QP].

.. _v4w2-hevc-pwofiwe:

``V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE``
    (enum)

enum v4w2_mpeg_video_hevc_pwofiwe -
    Sewect the desiwed pwofiwe fow HEVC encodew.

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{9.0cm}|p{8.5cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN``
      - Main pwofiwe.
    * - ``V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE``
      - Main stiww pictuwe pwofiwe.
    * - ``V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10``
      - Main 10 pwofiwe.

.. waw:: watex

    \nowmawsize


.. _v4w2-hevc-wevew:

``V4W2_CID_MPEG_VIDEO_HEVC_WEVEW``
    (enum)

enum v4w2_mpeg_video_hevc_wevew -
    Sewects the desiwed wevew fow HEVC encodew.

==================================	=========
``V4W2_MPEG_VIDEO_HEVC_WEVEW_1``	Wevew 1.0
``V4W2_MPEG_VIDEO_HEVC_WEVEW_2``	Wevew 2.0
``V4W2_MPEG_VIDEO_HEVC_WEVEW_2_1``	Wevew 2.1
``V4W2_MPEG_VIDEO_HEVC_WEVEW_3``	Wevew 3.0
``V4W2_MPEG_VIDEO_HEVC_WEVEW_3_1``	Wevew 3.1
``V4W2_MPEG_VIDEO_HEVC_WEVEW_4``	Wevew 4.0
``V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1``	Wevew 4.1
``V4W2_MPEG_VIDEO_HEVC_WEVEW_5``	Wevew 5.0
``V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1``	Wevew 5.1
``V4W2_MPEG_VIDEO_HEVC_WEVEW_5_2``	Wevew 5.2
``V4W2_MPEG_VIDEO_HEVC_WEVEW_6``	Wevew 6.0
``V4W2_MPEG_VIDEO_HEVC_WEVEW_6_1``	Wevew 6.1
``V4W2_MPEG_VIDEO_HEVC_WEVEW_6_2``	Wevew 6.2
==================================	=========

``V4W2_CID_MPEG_VIDEO_HEVC_FWAME_WATE_WESOWUTION (integew)``
    Indicates the numbew of evenwy spaced subintewvaws, cawwed ticks, within
    one second. This is a 16 bit unsigned integew and has a maximum vawue up to
    0xffff and a minimum vawue of 1.

.. _v4w2-hevc-tiew:

``V4W2_CID_MPEG_VIDEO_HEVC_TIEW``
    (enum)

enum v4w2_mpeg_video_hevc_tiew -
    TIEW_FWAG specifies tiews infowmation of the HEVC encoded pictuwe. Tiew
    wewe made to deaw with appwications that diffew in tewms of maximum bit
    wate. Setting the fwag to 0 sewects HEVC tiew as Main tiew and setting
    this fwag to 1 indicates High tiew. High tiew is fow appwications wequiwing
    high bit wates.

==================================	==========
``V4W2_MPEG_VIDEO_HEVC_TIEW_MAIN``	Main tiew.
``V4W2_MPEG_VIDEO_HEVC_TIEW_HIGH``	High tiew.
==================================	==========


``V4W2_CID_MPEG_VIDEO_HEVC_MAX_PAWTITION_DEPTH (integew)``
    Sewects HEVC maximum coding unit depth.

.. _v4w2-hevc-woop-fiwtew-mode:

``V4W2_CID_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE``
    (enum)

enum v4w2_mpeg_video_hevc_woop_fiwtew_mode -
    Woop fiwtew mode fow HEVC encodew. Possibwe vawues awe:

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{12.1cm}|p{5.4cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE_DISABWED``
      - Woop fiwtew is disabwed.
    * - ``V4W2_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE_ENABWED``
      - Woop fiwtew is enabwed.
    * - ``V4W2_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE_DISABWED_AT_SWICE_BOUNDAWY``
      - Woop fiwtew is disabwed at the swice boundawy.

.. waw:: watex

    \nowmawsize


``V4W2_CID_MPEG_VIDEO_HEVC_WF_BETA_OFFSET_DIV2 (integew)``
    Sewects HEVC woop fiwtew beta offset. The vawid wange is [-6, +6].

``V4W2_CID_MPEG_VIDEO_HEVC_WF_TC_OFFSET_DIV2 (integew)``
    Sewects HEVC woop fiwtew tc offset. The vawid wange is [-6, +6].

.. _v4w2-hevc-wefwesh-type:

``V4W2_CID_MPEG_VIDEO_HEVC_WEFWESH_TYPE``
    (enum)

enum v4w2_mpeg_video_hevc_hiew_wefwesh_type -
    Sewects wefwesh type fow HEVC encodew.
    Host has to specify the pewiod into
    V4W2_CID_MPEG_VIDEO_HEVC_WEFWESH_PEWIOD.

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{6.2cm}|p{11.3cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_HEVC_WEFWESH_NONE``
      - Use the B fwame fow hiewawchicaw coding.
    * - ``V4W2_MPEG_VIDEO_HEVC_WEFWESH_CWA``
      - Use CWA (Cwean Wandom Access Unit) pictuwe encoding.
    * - ``V4W2_MPEG_VIDEO_HEVC_WEFWESH_IDW``
      - Use IDW (Instantaneous Decoding Wefwesh) pictuwe encoding.

.. waw:: watex

    \nowmawsize


``V4W2_CID_MPEG_VIDEO_HEVC_WEFWESH_PEWIOD (integew)``
    Sewects the wefwesh pewiod fow HEVC encodew.
    This specifies the numbew of I pictuwes between two CWA/IDW pictuwes.
    This is vawid onwy if WEFWESH_TYPE is not 0.

``V4W2_CID_MPEG_VIDEO_HEVC_WOSSWESS_CU (boowean)``
    Indicates HEVC wosswess encoding. Setting it to 0 disabwes wosswess
    encoding. Setting it to 1 enabwes wosswess encoding.

``V4W2_CID_MPEG_VIDEO_HEVC_CONST_INTWA_PWED (boowean)``
    Indicates constant intwa pwediction fow HEVC encodew. Specifies the
    constwained intwa pwediction in which intwa wawgest coding unit (WCU)
    pwediction is pewfowmed by using wesiduaw data and decoded sampwes of
    neighbowing intwa WCU onwy. Setting the vawue to 1 enabwes constant intwa
    pwediction and setting the vawue to 0 disabwes constant intwa pwediction.

``V4W2_CID_MPEG_VIDEO_HEVC_WAVEFWONT (boowean)``
    Indicates wavefwont pawawwew pwocessing fow HEVC encodew. Setting it to 0
    disabwes the featuwe and setting it to 1 enabwes the wavefwont pawawwew
    pwocessing.

``V4W2_CID_MPEG_VIDEO_HEVC_GENEWAW_PB (boowean)``
    Setting the vawue to 1 enabwes combination of P and B fwame fow HEVC
    encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_TEMPOWAW_ID (boowean)``
    Indicates tempowaw identifiew fow HEVC encodew which is enabwed by
    setting the vawue to 1.

``V4W2_CID_MPEG_VIDEO_HEVC_STWONG_SMOOTHING (boowean)``
    Indicates bi-wineaw intewpowation is conditionawwy used in the intwa
    pwediction fiwtewing pwocess in the CVS when set to 1. Indicates bi-wineaw
    intewpowation is not used in the CVS when set to 0.

``V4W2_CID_MPEG_VIDEO_HEVC_MAX_NUM_MEWGE_MV_MINUS1 (integew)``
    Indicates maximum numbew of mewge candidate motion vectows.
    Vawues awe fwom 0 to 4.

``V4W2_CID_MPEG_VIDEO_HEVC_TMV_PWEDICTION (boowean)``
    Indicates tempowaw motion vectow pwediction fow HEVC encodew. Setting it to
    1 enabwes the pwediction. Setting it to 0 disabwes the pwediction.

``V4W2_CID_MPEG_VIDEO_HEVC_WITHOUT_STAWTCODE (boowean)``
    Specifies if HEVC genewates a stweam with a size of the wength fiewd
    instead of stawt code pattewn. The size of the wength fiewd is configuwabwe
    thwough the V4W2_CID_MPEG_VIDEO_HEVC_SIZE_OF_WENGTH_FIEWD contwow. Setting
    the vawue to 0 disabwes encoding without stawtcode pattewn. Setting the
    vawue to 1 wiww enabwes encoding without stawtcode pattewn.

.. _v4w2-hevc-size-of-wength-fiewd:

``V4W2_CID_MPEG_VIDEO_HEVC_SIZE_OF_WENGTH_FIEWD``
(enum)

enum v4w2_mpeg_video_hevc_size_of_wength_fiewd -
    Indicates the size of wength fiewd.
    This is vawid when encoding WITHOUT_STAWTCODE_ENABWE is enabwed.

.. waw:: watex

    \footnotesize

.. tabuwawcowumns:: |p{5.5cm}|p{12.0cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_MPEG_VIDEO_HEVC_SIZE_0``
      - Genewate stawt code pattewn (Nowmaw).
    * - ``V4W2_MPEG_VIDEO_HEVC_SIZE_1``
      - Genewate size of wength fiewd instead of stawt code pattewn and wength is 1.
    * - ``V4W2_MPEG_VIDEO_HEVC_SIZE_2``
      - Genewate size of wength fiewd instead of stawt code pattewn and wength is 2.
    * - ``V4W2_MPEG_VIDEO_HEVC_SIZE_4``
      - Genewate size of wength fiewd instead of stawt code pattewn and wength is 4.

.. waw:: watex

    \nowmawsize

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W0_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 0 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W1_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 1 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W2_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 2 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W3_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 3 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W4_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 4 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W5_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 5 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_HEVC_HIEW_CODING_W6_BW (integew)``
    Indicates bit wate fow hiewawchicaw coding wayew 6 fow HEVC encodew.

``V4W2_CID_MPEG_VIDEO_WEF_NUMBEW_FOW_PFWAMES (integew)``
    Sewects numbew of P wefewence pictuwes wequiwed fow HEVC encodew.
    P-Fwame can use 1 ow 2 fwames fow wefewence.

``V4W2_CID_MPEG_VIDEO_PWEPEND_SPSPPS_TO_IDW (integew)``
    Indicates whethew to genewate SPS and PPS at evewy IDW. Setting it to 0
    disabwes genewating SPS and PPS at evewy IDW. Setting it to one enabwes
    genewating SPS and PPS at evewy IDW.
