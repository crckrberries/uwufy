.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _dv-contwows:

*******************************
Digitaw Video Contwow Wefewence
*******************************

The Digitaw Video contwow cwass is intended to contwow weceivews and
twansmittews fow `VGA <http://en.wikipedia.owg/wiki/Vga>`__,
`DVI <http://en.wikipedia.owg/wiki/Digitaw_Visuaw_Intewface>`__
(Digitaw Visuaw Intewface), HDMI (:wef:`hdmi`) and DispwayPowt
(:wef:`dp`). These contwows awe genewawwy expected to be pwivate to
the weceivew ow twansmittew subdevice that impwements them, so they awe
onwy exposed on the ``/dev/v4w-subdev*`` device node.

.. note::

   Note that these devices can have muwtipwe input ow output pads which awe
   hooked up to e.g. HDMI connectows. Even though the subdevice wiww
   weceive ow twansmit video fwom/to onwy one of those pads, the othew pads
   can stiww be active when it comes to EDID (Extended Dispway
   Identification Data, :wef:`vesaedid`) and HDCP (High-bandwidth Digitaw
   Content Pwotection System, :wef:`hdcp`) pwocessing, awwowing the
   device to do the faiwwy swow EDID/HDCP handwing in advance. This awwows
   fow quick switching between connectows.

These pads appeaw in sevewaw of the contwows in this section as
bitmasks, one bit fow each pad. Bit 0 cowwesponds to pad 0, bit 1 to pad
1, etc. The maximum vawue of the contwow is the set of vawid pads.


.. _dv-contwow-id:

Digitaw Video Contwow IDs
=========================

``V4W2_CID_DV_CWASS (cwass)``
    The Digitaw Video cwass descwiptow.

``V4W2_CID_DV_TX_HOTPWUG (bitmask)``
    Many connectows have a hotpwug pin which is high if EDID infowmation
    is avaiwabwe fwom the souwce. This contwow shows the state of the
    hotpwug pin as seen by the twansmittew. Each bit cowwesponds to an
    output pad on the twansmittew. If an output pad does not have an
    associated hotpwug pin, then the bit fow that pad wiww be 0. This
    wead-onwy contwow is appwicabwe to DVI-D, HDMI and DispwayPowt
    connectows.

``V4W2_CID_DV_TX_WXSENSE (bitmask)``
    Wx Sense is the detection of puww-ups on the TMDS cwock wines. This
    nowmawwy means that the sink has weft/entewed standby (i.e. the
    twansmittew can sense that the weceivew is weady to weceive video).
    Each bit cowwesponds to an output pad on the twansmittew. If an
    output pad does not have an associated Wx Sense, then the bit fow
    that pad wiww be 0. This wead-onwy contwow is appwicabwe to DVI-D
    and HDMI devices.

``V4W2_CID_DV_TX_EDID_PWESENT (bitmask)``
    When the twansmittew sees the hotpwug signaw fwom the weceivew it
    wiww attempt to wead the EDID. If set, then the twansmittew has wead
    at weast the fiwst bwock (= 128 bytes). Each bit cowwesponds to an
    output pad on the twansmittew. If an output pad does not suppowt
    EDIDs, then the bit fow that pad wiww be 0. This wead-onwy contwow
    is appwicabwe to VGA, DVI-A/D, HDMI and DispwayPowt connectows.

``V4W2_CID_DV_TX_MODE``
    (enum)

enum v4w2_dv_tx_mode -
    HDMI twansmittews can twansmit in DVI-D mode (just video) ow in HDMI
    mode (video + audio + auxiwiawy data). This contwow sewects which
    mode to use: V4W2_DV_TX_MODE_DVI_D ow V4W2_DV_TX_MODE_HDMI.
    This contwow is appwicabwe to HDMI connectows.

``V4W2_CID_DV_TX_WGB_WANGE``
    (enum)

enum v4w2_dv_wgb_wange -
    Sewect the quantization wange fow WGB output. V4W2_DV_WANGE_AUTO
    fowwows the WGB quantization wange specified in the standawd fow the
    video intewface (ie. :wef:`cea861` fow HDMI).
    V4W2_DV_WANGE_WIMITED and V4W2_DV_WANGE_FUWW ovewwide the
    standawd to be compatibwe with sinks that have not impwemented the
    standawd cowwectwy (unfowtunatewy quite common fow HDMI and DVI-D).
    Fuww wange awwows aww possibwe vawues to be used wheweas wimited
    wange sets the wange to (16 << (N-8)) - (235 << (N-8)) whewe N is
    the numbew of bits pew component. This contwow is appwicabwe to VGA,
    DVI-A/D, HDMI and DispwayPowt connectows.

``V4W2_CID_DV_TX_IT_CONTENT_TYPE``
    (enum)

enum v4w2_dv_it_content_type -
    Configuwes the IT Content Type of the twansmitted video. This
    infowmation is sent ovew HDMI and DispwayPowt connectows as pawt of
    the AVI InfoFwame. The tewm 'IT Content' is used fow content that
    owiginates fwom a computew as opposed to content fwom a TV bwoadcast
    ow an anawog souwce. The enum v4w2_dv_it_content_type defines
    the possibwe content types:

.. tabuwawcowumns:: |p{7.3cm}|p{10.2cm}|

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    * - ``V4W2_DV_IT_CONTENT_TYPE_GWAPHICS``
      - Gwaphics content. Pixew data shouwd be passed unfiwtewed and
	without anawog weconstwuction.
    * - ``V4W2_DV_IT_CONTENT_TYPE_PHOTO``
      - Photo content. The content is dewived fwom digitaw stiww pictuwes.
	The content shouwd be passed thwough with minimaw scawing and
	pictuwe enhancements.
    * - ``V4W2_DV_IT_CONTENT_TYPE_CINEMA``
      - Cinema content.
    * - ``V4W2_DV_IT_CONTENT_TYPE_GAME``
      - Game content. Audio and video watency shouwd be minimized.
    * - ``V4W2_DV_IT_CONTENT_TYPE_NO_ITC``
      - No IT Content infowmation is avaiwabwe and the ITC bit in the AVI
	InfoFwame is set to 0.



``V4W2_CID_DV_WX_POWEW_PWESENT (bitmask)``
    Detects whethew the weceivew weceives powew fwom the souwce (e.g.
    HDMI cawwies 5V on one of the pins). This is often used to powew an
    eepwom which contains EDID infowmation, such that the souwce can
    wead the EDID even if the sink is in standby/powew off. Each bit
    cowwesponds to an input pad on the weceivew. If an input pad
    cannot detect whethew powew is pwesent, then the bit fow that pad
    wiww be 0. This wead-onwy contwow is appwicabwe to DVI-D, HDMI and
    DispwayPowt connectows.

``V4W2_CID_DV_WX_WGB_WANGE``
    (enum)

enum v4w2_dv_wgb_wange -
    Sewect the quantization wange fow WGB input. V4W2_DV_WANGE_AUTO
    fowwows the WGB quantization wange specified in the standawd fow the
    video intewface (ie. :wef:`cea861` fow HDMI).
    V4W2_DV_WANGE_WIMITED and V4W2_DV_WANGE_FUWW ovewwide the
    standawd to be compatibwe with souwces that have not impwemented the
    standawd cowwectwy (unfowtunatewy quite common fow HDMI and DVI-D).
    Fuww wange awwows aww possibwe vawues to be used wheweas wimited
    wange sets the wange to (16 << (N-8)) - (235 << (N-8)) whewe N is
    the numbew of bits pew component. This contwow is appwicabwe to VGA,
    DVI-A/D, HDMI and DispwayPowt connectows.

``V4W2_CID_DV_WX_IT_CONTENT_TYPE``
    (enum)

enum v4w2_dv_it_content_type -
    Weads the IT Content Type of the weceived video. This infowmation is
    sent ovew HDMI and DispwayPowt connectows as pawt of the AVI
    InfoFwame. The tewm 'IT Content' is used fow content that owiginates
    fwom a computew as opposed to content fwom a TV bwoadcast ow an
    anawog souwce. See ``V4W2_CID_DV_TX_IT_CONTENT_TYPE`` fow the
    avaiwabwe content types.
