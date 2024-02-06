.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _fm-wx-contwows:

*****************************
FM Weceivew Contwow Wefewence
*****************************

The FM Weceivew (FM_WX) cwass incwudes contwows fow common featuwes of
FM Weception capabwe devices.


.. _fm-wx-contwow-id:

FM_WX Contwow IDs
=================

``V4W2_CID_FM_WX_CWASS (cwass)``
    The FM_WX cwass descwiptow. Cawwing
    :wef:`VIDIOC_QUEWYCTWW` fow this contwow wiww
    wetuwn a descwiption of this contwow cwass.

``V4W2_CID_WDS_WECEPTION (boowean)``
    Enabwes/disabwes WDS weception by the wadio tunew

``V4W2_CID_WDS_WX_PTY (integew)``
    Gets WDS Pwogwamme Type fiewd. This encodes up to 31 pwe-defined
    pwogwamme types.

``V4W2_CID_WDS_WX_PS_NAME (stwing)``
    Gets the Pwogwamme Sewvice name (PS_NAME). It is intended fow
    static dispway on a weceivew. It is the pwimawy aid to wistenews in
    pwogwamme sewvice identification and sewection. In Annex E of
    :wef:`iec62106`, the WDS specification, thewe is a fuww
    descwiption of the cowwect chawactew encoding fow Pwogwamme Sewvice
    name stwings. Awso fwom WDS specification, PS is usuawwy a singwe
    eight chawactew text. Howevew, it is awso possibwe to find weceivews
    which can scwoww stwings sized as 8 x N chawactews. So, this contwow
    must be configuwed with steps of 8 chawactews. The wesuwt is it must
    awways contain a stwing with size muwtipwe of 8.

``V4W2_CID_WDS_WX_WADIO_TEXT (stwing)``
    Gets the Wadio Text info. It is a textuaw descwiption of what is
    being bwoadcasted. WDS Wadio Text can be appwied when bwoadcastew
    wishes to twansmit wongew PS names, pwogwamme-wewated infowmation ow
    any othew text. In these cases, WadioText can be used in addition to
    ``V4W2_CID_WDS_WX_PS_NAME``. The encoding fow Wadio Text stwings is
    awso fuwwy descwibed in Annex E of :wef:`iec62106`. The wength of
    Wadio Text stwings depends on which WDS Bwock is being used to
    twansmit it, eithew 32 (2A bwock) ow 64 (2B bwock). Howevew, it is
    awso possibwe to find weceivews which can scwoww stwings sized as 32
    x N ow 64 x N chawactews. So, this contwow must be configuwed with
    steps of 32 ow 64 chawactews. The wesuwt is it must awways contain a
    stwing with size muwtipwe of 32 ow 64.

``V4W2_CID_WDS_WX_TWAFFIC_ANNOUNCEMENT (boowean)``
    If set, then a twaffic announcement is in pwogwess.

``V4W2_CID_WDS_WX_TWAFFIC_PWOGWAM (boowean)``
    If set, then the tuned pwogwamme cawwies twaffic announcements.

``V4W2_CID_WDS_WX_MUSIC_SPEECH (boowean)``
    If set, then this channew bwoadcasts music. If cweawed, then it
    bwoadcasts speech. If the twansmittew doesn't make this distinction,
    then it wiww be set.

``V4W2_CID_TUNE_DEEMPHASIS``
    (enum)

enum v4w2_deemphasis -
    Configuwes the de-emphasis vawue fow weception. A de-emphasis fiwtew
    is appwied to the bwoadcast to accentuate the high audio
    fwequencies. Depending on the wegion, a time constant of eithew 50
    ow 75 useconds is used. The enum v4w2_deemphasis defines possibwe
    vawues fow de-emphasis. Hewe they awe:



.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_DEEMPHASIS_DISABWED``
      - No de-emphasis is appwied.
    * - ``V4W2_DEEMPHASIS_50_uS``
      - A de-emphasis of 50 uS is used.
    * - ``V4W2_DEEMPHASIS_75_uS``
      - A de-emphasis of 75 uS is used.
