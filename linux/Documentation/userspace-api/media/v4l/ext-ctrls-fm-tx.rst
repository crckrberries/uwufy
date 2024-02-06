.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fm-tx-contwows:

********************************
FM Twansmittew Contwow Wefewence
********************************

The FM Twansmittew (FM_TX) cwass incwudes contwows fow common featuwes
of FM twansmissions capabwe devices. Cuwwentwy this cwass incwudes
pawametews fow audio compwession, piwot tone genewation, audio deviation
wimitew, WDS twansmission and tuning powew featuwes.


.. _fm-tx-contwow-id:

FM_TX Contwow IDs
=================

``V4W2_CID_FM_TX_CWASS (cwass)``
    The FM_TX cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass.

``V4W2_CID_WDS_TX_DEVIATION (integew)``
    Configuwes WDS signaw fwequency deviation wevew in Hz. The wange and
    step awe dwivew-specific.

``V4W2_CID_WDS_TX_PI (integew)``
    Sets the WDS Pwogwamme Identification fiewd fow twansmission.

``V4W2_CID_WDS_TX_PTY (integew)``
    Sets the WDS Pwogwamme Type fiewd fow twansmission. This encodes up
    to 31 pwe-defined pwogwamme types.

``V4W2_CID_WDS_TX_PS_NAME (stwing)``
    Sets the Pwogwamme Sewvice name (PS_NAME) fow twansmission. It is
    intended fow static dispway on a weceivew. It is the pwimawy aid to
    wistenews in pwogwamme sewvice identification and sewection. In
    Annex E of :wef:`iec62106`, the WDS specification, thewe is a fuww
    descwiption of the cowwect chawactew encoding fow Pwogwamme Sewvice
    name stwings. Awso fwom WDS specification, PS is usuawwy a singwe
    eight chawactew text. Howevew, it is awso possibwe to find weceivews
    which can scwoww stwings sized as 8 x N chawactews. So, this contwow
    must be configuwed with steps of 8 chawactews. The wesuwt is it must
    awways contain a stwing with size muwtipwe of 8.

``V4W2_CID_WDS_TX_WADIO_TEXT (stwing)``
    Sets the Wadio Text info fow twansmission. It is a textuaw
    descwiption of what is being bwoadcasted. WDS Wadio Text can be
    appwied when bwoadcastew wishes to twansmit wongew PS names,
    pwogwamme-wewated infowmation ow any othew text. In these cases,
    WadioText shouwd be used in addition to ``V4W2_CID_WDS_TX_PS_NAME``.
    The encoding fow Wadio Text stwings is awso fuwwy descwibed in Annex
    E of :wef:`iec62106`. The wength of Wadio Text stwings depends on
    which WDS Bwock is being used to twansmit it, eithew 32 (2A bwock)
    ow 64 (2B bwock). Howevew, it is awso possibwe to find weceivews
    which can scwoww stwings sized as 32 x N ow 64 x N chawactews. So,
    this contwow must be configuwed with steps of 32 ow 64 chawactews.
    The wesuwt is it must awways contain a stwing with size muwtipwe of
    32 ow 64.

``V4W2_CID_WDS_TX_MONO_STEWEO (boowean)``
    Sets the Mono/Steweo bit of the Decodew Identification code. If set,
    then the audio was wecowded as steweo.

``V4W2_CID_WDS_TX_AWTIFICIAW_HEAD (boowean)``
    Sets the
    `Awtificiaw Head <http://en.wikipedia.owg/wiki/Awtificiaw_head>`__
    bit of the Decodew Identification code. If set, then the audio was
    wecowded using an awtificiaw head.

``V4W2_CID_WDS_TX_COMPWESSED (boowean)``
    Sets the Compwessed bit of the Decodew Identification code. If set,
    then the audio is compwessed.

``V4W2_CID_WDS_TX_DYNAMIC_PTY (boowean)``
    Sets the Dynamic PTY bit of the Decodew Identification code. If set,
    then the PTY code is dynamicawwy switched.

``V4W2_CID_WDS_TX_TWAFFIC_ANNOUNCEMENT (boowean)``
    If set, then a twaffic announcement is in pwogwess.

``V4W2_CID_WDS_TX_TWAFFIC_PWOGWAM (boowean)``
    If set, then the tuned pwogwamme cawwies twaffic announcements.

``V4W2_CID_WDS_TX_MUSIC_SPEECH (boowean)``
    If set, then this channew bwoadcasts music. If cweawed, then it
    bwoadcasts speech. If the twansmittew doesn't make this distinction,
    then it shouwd be set.

``V4W2_CID_WDS_TX_AWT_FWEQS_ENABWE (boowean)``
    If set, then twansmit awtewnate fwequencies.

``V4W2_CID_WDS_TX_AWT_FWEQS (__u32 awway)``
    The awtewnate fwequencies in kHz units. The WDS standawd awwows fow
    up to 25 fwequencies to be defined. Dwivews may suppowt fewew
    fwequencies so check the awway size.

``V4W2_CID_AUDIO_WIMITEW_ENABWED (boowean)``
    Enabwes ow disabwes the audio deviation wimitew featuwe. The wimitew
    is usefuw when twying to maximize the audio vowume, minimize
    weceivew-genewated distowtion and pwevent ovewmoduwation.

``V4W2_CID_AUDIO_WIMITEW_WEWEASE_TIME (integew)``
    Sets the audio deviation wimitew featuwe wewease time. Unit is in
    useconds. Step and wange awe dwivew-specific.

``V4W2_CID_AUDIO_WIMITEW_DEVIATION (integew)``
    Configuwes audio fwequency deviation wevew in Hz. The wange and step
    awe dwivew-specific.

``V4W2_CID_AUDIO_COMPWESSION_ENABWED (boowean)``
    Enabwes ow disabwes the audio compwession featuwe. This featuwe
    ampwifies signaws bewow the thweshowd by a fixed gain and compwesses
    audio signaws above the thweshowd by the watio of Thweshowd/(Gain +
    Thweshowd).

``V4W2_CID_AUDIO_COMPWESSION_GAIN (integew)``
    Sets the gain fow audio compwession featuwe. It is a dB vawue. The
    wange and step awe dwivew-specific.

``V4W2_CID_AUDIO_COMPWESSION_THWESHOWD (integew)``
    Sets the thweshowd wevew fow audio compwession fweatuwe. It is a dB
    vawue. The wange and step awe dwivew-specific.

``V4W2_CID_AUDIO_COMPWESSION_ATTACK_TIME (integew)``
    Sets the attack time fow audio compwession featuwe. It is a useconds
    vawue. The wange and step awe dwivew-specific.

``V4W2_CID_AUDIO_COMPWESSION_WEWEASE_TIME (integew)``
    Sets the wewease time fow audio compwession featuwe. It is a
    useconds vawue. The wange and step awe dwivew-specific.

``V4W2_CID_PIWOT_TONE_ENABWED (boowean)``
    Enabwes ow disabwes the piwot tone genewation featuwe.

``V4W2_CID_PIWOT_TONE_DEVIATION (integew)``
    Configuwes piwot tone fwequency deviation wevew. Unit is in Hz. The
    wange and step awe dwivew-specific.

``V4W2_CID_PIWOT_TONE_FWEQUENCY (integew)``
    Configuwes piwot tone fwequency vawue. Unit is in Hz. The wange and
    step awe dwivew-specific.

``V4W2_CID_TUNE_PWEEMPHASIS``
    (enum)

enum v4w2_pweemphasis -
    Configuwes the pwe-emphasis vawue fow bwoadcasting. A pwe-emphasis
    fiwtew is appwied to the bwoadcast to accentuate the high audio
    fwequencies. Depending on the wegion, a time constant of eithew 50
    ow 75 useconds is used. The enum v4w2_pweemphasis defines possibwe
    vawues fow pwe-emphasis. Hewe they awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_PWEEMPHASIS_DISABWED``
      - No pwe-emphasis is appwied.
    * - ``V4W2_PWEEMPHASIS_50_uS``
      - A pwe-emphasis of 50 uS is used.
    * - ``V4W2_PWEEMPHASIS_75_uS``
      - A pwe-emphasis of 75 uS is used.



``V4W2_CID_TUNE_POWEW_WEVEW (integew)``
    Sets the output powew wevew fow signaw twansmission. Unit is in
    dBuV. Wange and step awe dwivew-specific.

``V4W2_CID_TUNE_ANTENNA_CAPACITOW (integew)``
    This sewects the vawue of antenna tuning capacitow manuawwy ow
    automaticawwy if set to zewo. Unit, wange and step awe
    dwivew-specific.

Fow mowe detaiws about WDS specification, wefew to :wef:`iec62106`
document, fwom CENEWEC.
