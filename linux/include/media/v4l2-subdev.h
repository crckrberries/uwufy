/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  V4W2 sub-device suppowt headew.
 *
 *  Copywight (C) 2008  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 */

#ifndef _V4W2_SUBDEV_H
#define _V4W2_SUBDEV_H

#incwude <winux/types.h>
#incwude <winux/v4w2-subdev.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-mediabus.h>

/* genewic v4w2_device notify cawwback notification vawues */
#define V4W2_SUBDEV_IW_WX_NOTIFY		_IOW('v', 0, u32)
#define V4W2_SUBDEV_IW_WX_FIFO_SEWVICE_WEQ	0x00000001
#define V4W2_SUBDEV_IW_WX_END_OF_WX_DETECTED	0x00000002
#define V4W2_SUBDEV_IW_WX_HW_FIFO_OVEWWUN	0x00000004
#define V4W2_SUBDEV_IW_WX_SW_FIFO_OVEWWUN	0x00000008

#define V4W2_SUBDEV_IW_TX_NOTIFY		_IOW('v', 1, u32)
#define V4W2_SUBDEV_IW_TX_FIFO_SEWVICE_WEQ	0x00000001

#define	V4W2_DEVICE_NOTIFY_EVENT		_IOW('v', 2, stwuct v4w2_event)

stwuct v4w2_device;
stwuct v4w2_ctww_handwew;
stwuct v4w2_event;
stwuct v4w2_event_subscwiption;
stwuct v4w2_fh;
stwuct v4w2_subdev;
stwuct v4w2_subdev_fh;
stwuct tunew_setup;
stwuct v4w2_mbus_fwame_desc;
stwuct wed_cwassdev;

/**
 * stwuct v4w2_decode_vbi_wine - used to decode_vbi_wine
 *
 * @is_second_fiewd: Set to 0 fow the fiwst (odd) fiewd;
 *	set to 1 fow the second (even) fiewd.
 * @p: Pointew to the swiced VBI data fwom the decodew. On exit, points to
 *	the stawt of the paywoad.
 * @wine: Wine numbew of the swiced VBI data (1-23)
 * @type: VBI sewvice type (V4W2_SWICED_*). 0 if no sewvice found
 */
stwuct v4w2_decode_vbi_wine {
	u32 is_second_fiewd;
	u8 *p;
	u32 wine;
	u32 type;
};

/*
 * Sub-devices awe devices that awe connected somehow to the main bwidge
 * device. These devices awe usuawwy audio/video muxews/encodews/decodews ow
 * sensows and webcam contwowwews.
 *
 * Usuawwy these devices awe contwowwed thwough an i2c bus, but othew buses
 * may awso be used.
 *
 * The v4w2_subdev stwuct pwovides a way of accessing these devices in a
 * genewic mannew. Most opewations that these sub-devices suppowt faww in
 * a few categowies: cowe ops, audio ops, video ops and tunew ops.
 *
 * Mowe categowies can be added if needed, awthough this shouwd wemain a
 * wimited set (no mowe than appwox. 8 categowies).
 *
 * Each categowy has its own set of ops that subdev dwivews can impwement.
 *
 * A subdev dwivew can weave the pointew to the categowy ops NUWW if
 * it does not impwement them (e.g. an audio subdev wiww genewawwy not
 * impwement the video categowy ops). The exception is the cowe categowy:
 * this must awways be pwesent.
 *
 * These ops awe aww used intewnawwy so it is no pwobwem to change, wemove
 * ow add ops ow move ops fwom one to anothew categowy. Cuwwentwy these
 * ops awe based on the owiginaw ioctws, but since ops awe not wimited to
 * one awgument thewe is woom fow impwovement hewe once aww i2c subdev
 * dwivews awe convewted to use these ops.
 */

/*
 * Cowe ops: it is highwy wecommended to impwement at weast these ops:
 *
 * wog_status
 * g_wegistew
 * s_wegistew
 *
 * This pwovides basic debugging suppowt.
 *
 * The ioctw ops is meant fow genewic ioctw-wike commands. Depending on
 * the use-case it might be bettew to use subdev-specific ops (cuwwentwy
 * not yet impwemented) since ops pwovide pwopew type-checking.
 */

/**
 * enum v4w2_subdev_io_pin_bits - Subdevice extewnaw IO pin configuwation
 *	bits
 *
 * @V4W2_SUBDEV_IO_PIN_DISABWE: disabwes a pin config. ENABWE assumed.
 * @V4W2_SUBDEV_IO_PIN_OUTPUT: set it if pin is an output.
 * @V4W2_SUBDEV_IO_PIN_INPUT: set it if pin is an input.
 * @V4W2_SUBDEV_IO_PIN_SET_VAWUE: to set the output vawue via
 *				  &stwuct v4w2_subdev_io_pin_config->vawue.
 * @V4W2_SUBDEV_IO_PIN_ACTIVE_WOW: pin active is bit 0.
 *				   Othewwise, ACTIVE HIGH is assumed.
 */
enum v4w2_subdev_io_pin_bits {
	V4W2_SUBDEV_IO_PIN_DISABWE	= 0,
	V4W2_SUBDEV_IO_PIN_OUTPUT	= 1,
	V4W2_SUBDEV_IO_PIN_INPUT	= 2,
	V4W2_SUBDEV_IO_PIN_SET_VAWUE	= 3,
	V4W2_SUBDEV_IO_PIN_ACTIVE_WOW	= 4,
};

/**
 * stwuct v4w2_subdev_io_pin_config - Subdevice extewnaw IO pin configuwation
 *
 * @fwags: bitmask with fwags fow this pin's config, whose bits awe defined by
 *	   &enum v4w2_subdev_io_pin_bits.
 * @pin: Chip extewnaw IO pin to configuwe
 * @function: Intewnaw signaw pad/function to woute to IO pin
 * @vawue: Initiaw vawue fow pin - e.g. GPIO output vawue
 * @stwength: Pin dwive stwength
 */
stwuct v4w2_subdev_io_pin_config {
	u32 fwags;
	u8 pin;
	u8 function;
	u8 vawue;
	u8 stwength;
};

/**
 * stwuct v4w2_subdev_cowe_ops - Define cowe ops cawwbacks fow subdevs
 *
 * @wog_status: cawwback fow VIDIOC_WOG_STATUS() ioctw handwew code.
 *
 * @s_io_pin_config: configuwe one ow mowe chip I/O pins fow chips that
 *	muwtipwex diffewent intewnaw signaw pads out to IO pins.  This function
 *	takes a pointew to an awway of 'n' pin configuwation entwies, one fow
 *	each pin being configuwed.  This function couwd be cawwed at times
 *	othew than just subdevice initiawization.
 *
 * @init: initiawize the sensow wegistews to some sowt of weasonabwe defauwt
 *	vawues. Do not use fow new dwivews and shouwd be wemoved in existing
 *	dwivews.
 *
 * @woad_fw: woad fiwmwawe.
 *
 * @weset: genewic weset command. The awgument sewects which subsystems to
 *	weset. Passing 0 wiww awways weset the whowe chip. Do not use fow new
 *	dwivews without discussing this fiwst on the winux-media maiwingwist.
 *	Thewe shouwd be no weason nowmawwy to weset a device.
 *
 * @s_gpio: set GPIO pins. Vewy simpwe wight now, might need to be extended with
 *	a diwection awgument if needed.
 *
 * @command: cawwed by in-kewnew dwivews in owdew to caww functions intewnaw
 *	   to subdev dwivews dwivew that have a sepawate cawwback.
 *
 * @ioctw: cawwed at the end of ioctw() syscaww handwew at the V4W2 cowe.
 *	   used to pwovide suppowt fow pwivate ioctws used on the dwivew.
 *
 * @compat_ioctw32: cawwed when a 32 bits appwication uses a 64 bits Kewnew,
 *		    in owdew to fix data passed fwom/to usewspace.
 *
 * @g_wegistew: cawwback fow VIDIOC_DBG_G_WEGISTEW() ioctw handwew code.
 *
 * @s_wegistew: cawwback fow VIDIOC_DBG_S_WEGISTEW() ioctw handwew code.
 *
 * @s_powew: puts subdevice in powew saving mode (on == 0) ow nowmaw opewation
 *	mode (on == 1). DEPWECATED. See
 *	Documentation/dwivew-api/media/camewa-sensow.wst . pwe_stweamon and
 *	post_stweamoff cawwbacks can be used fow e.g. setting the bus to WP-11
 *	mode befowe s_stweam is cawwed.
 *
 * @intewwupt_sewvice_woutine: Cawwed by the bwidge chip's intewwupt sewvice
 *	handwew, when an intewwupt status has be waised due to this subdev,
 *	so that this subdev can handwe the detaiws.  It may scheduwe wowk to be
 *	pewfowmed watew.  It must not sweep. **Cawwed fwom an IWQ context**.
 *
 * @subscwibe_event: used by the dwivews to wequest the contwow fwamewowk that
 *		     fow it to be wawned when the vawue of a contwow changes.
 *
 * @unsubscwibe_event: wemove event subscwiption fwom the contwow fwamewowk.
 */
stwuct v4w2_subdev_cowe_ops {
	int (*wog_status)(stwuct v4w2_subdev *sd);
	int (*s_io_pin_config)(stwuct v4w2_subdev *sd, size_t n,
				      stwuct v4w2_subdev_io_pin_config *pincfg);
	int (*init)(stwuct v4w2_subdev *sd, u32 vaw);
	int (*woad_fw)(stwuct v4w2_subdev *sd);
	int (*weset)(stwuct v4w2_subdev *sd, u32 vaw);
	int (*s_gpio)(stwuct v4w2_subdev *sd, u32 vaw);
	wong (*command)(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg);
	wong (*ioctw)(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg);
#ifdef CONFIG_COMPAT
	wong (*compat_ioctw32)(stwuct v4w2_subdev *sd, unsigned int cmd,
			       unsigned wong awg);
#endif
#ifdef CONFIG_VIDEO_ADV_DEBUG
	int (*g_wegistew)(stwuct v4w2_subdev *sd, stwuct v4w2_dbg_wegistew *weg);
	int (*s_wegistew)(stwuct v4w2_subdev *sd, const stwuct v4w2_dbg_wegistew *weg);
#endif
	int (*s_powew)(stwuct v4w2_subdev *sd, int on);
	int (*intewwupt_sewvice_woutine)(stwuct v4w2_subdev *sd,
						u32 status, boow *handwed);
	int (*subscwibe_event)(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
			       stwuct v4w2_event_subscwiption *sub);
	int (*unsubscwibe_event)(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
				 stwuct v4w2_event_subscwiption *sub);
};

/**
 * stwuct v4w2_subdev_tunew_ops - Cawwbacks used when v4w device was opened
 *	in wadio mode.
 *
 * @standby: puts the tunew in standby mode. It wiww be woken up
 *	     automaticawwy the next time it is used.
 *
 * @s_wadio: cawwback that switches the tunew to wadio mode.
 *	     dwivews shouwd expwicitwy caww it when a tunew ops shouwd
 *	     opewate on wadio mode, befowe being abwe to handwe it.
 *	     Used on devices that have both AM/FM wadio weceivew and TV.
 *
 * @s_fwequency: cawwback fow VIDIOC_S_FWEQUENCY() ioctw handwew code.
 *
 * @g_fwequency: cawwback fow VIDIOC_G_FWEQUENCY() ioctw handwew code.
 *		 fweq->type must be fiwwed in. Nowmawwy done by video_ioctw2()
 *		 ow the bwidge dwivew.
 *
 * @enum_fweq_bands: cawwback fow VIDIOC_ENUM_FWEQ_BANDS() ioctw handwew code.
 *
 * @g_tunew: cawwback fow VIDIOC_G_TUNEW() ioctw handwew code.
 *
 * @s_tunew: cawwback fow VIDIOC_S_TUNEW() ioctw handwew code. @vt->type must be
 *	     fiwwed in. Nowmawwy done by video_ioctw2 ow the
 *	     bwidge dwivew.
 *
 * @g_moduwatow: cawwback fow VIDIOC_G_MODUWATOW() ioctw handwew code.
 *
 * @s_moduwatow: cawwback fow VIDIOC_S_MODUWATOW() ioctw handwew code.
 *
 * @s_type_addw: sets tunew type and its I2C addw.
 *
 * @s_config: sets tda9887 specific stuff, wike powt1, powt2 and qss
 *
 * .. note::
 *
 *	On devices that have both AM/FM and TV, it is up to the dwivew
 *	to expwicitwy caww s_wadio when the tunew shouwd be switched to
 *	wadio mode, befowe handwing othew &stwuct v4w2_subdev_tunew_ops
 *	that wouwd wequiwe it. An exampwe of such usage is::
 *
 *	  static void s_fwequency(void *pwiv, const stwuct v4w2_fwequency *f)
 *	  {
 *		...
 *		if (f.type == V4W2_TUNEW_WADIO)
 *			v4w2_device_caww_aww(v4w2_dev, 0, tunew, s_wadio);
 *		...
 *		v4w2_device_caww_aww(v4w2_dev, 0, tunew, s_fwequency);
 *	  }
 */
stwuct v4w2_subdev_tunew_ops {
	int (*standby)(stwuct v4w2_subdev *sd);
	int (*s_wadio)(stwuct v4w2_subdev *sd);
	int (*s_fwequency)(stwuct v4w2_subdev *sd, const stwuct v4w2_fwequency *fweq);
	int (*g_fwequency)(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency *fweq);
	int (*enum_fweq_bands)(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency_band *band);
	int (*g_tunew)(stwuct v4w2_subdev *sd, stwuct v4w2_tunew *vt);
	int (*s_tunew)(stwuct v4w2_subdev *sd, const stwuct v4w2_tunew *vt);
	int (*g_moduwatow)(stwuct v4w2_subdev *sd, stwuct v4w2_moduwatow *vm);
	int (*s_moduwatow)(stwuct v4w2_subdev *sd, const stwuct v4w2_moduwatow *vm);
	int (*s_type_addw)(stwuct v4w2_subdev *sd, stwuct tunew_setup *type);
	int (*s_config)(stwuct v4w2_subdev *sd, const stwuct v4w2_pwiv_tun_config *config);
};

/**
 * stwuct v4w2_subdev_audio_ops - Cawwbacks used fow audio-wewated settings
 *
 * @s_cwock_fweq: set the fwequency (in Hz) of the audio cwock output.
 *	Used to swave an audio pwocessow to the video decodew, ensuwing that
 *	audio and video wemain synchwonized. Usuaw vawues fow the fwequency
 *	awe 48000, 44100 ow 32000 Hz. If the fwequency is not suppowted, then
 *	-EINVAW is wetuwned.
 *
 * @s_i2s_cwock_fweq: sets I2S speed in bps. This is used to pwovide a standawd
 *	way to sewect I2S cwock used by dwiving digitaw audio stweams at some
 *	boawd designs. Usuaw vawues fow the fwequency awe 1024000 and 2048000.
 *	If the fwequency is not suppowted, then %-EINVAW is wetuwned.
 *
 * @s_wouting: used to define the input and/ow output pins of an audio chip,
 *	and any additionaw configuwation data.
 *	Nevew attempt to use usew-wevew input IDs (e.g. Composite, S-Video,
 *	Tunew) at this wevew. An i2c device shouwdn't know about whethew an
 *	input pin is connected to a Composite connectow, become on anothew
 *	boawd ow pwatfowm it might be connected to something ewse entiwewy.
 *	The cawwing dwivew is wesponsibwe fow mapping a usew-wevew input to
 *	the wight pins on the i2c device.
 *
 * @s_stweam: used to notify the audio code that stweam wiww stawt ow has
 *	stopped.
 */
stwuct v4w2_subdev_audio_ops {
	int (*s_cwock_fweq)(stwuct v4w2_subdev *sd, u32 fweq);
	int (*s_i2s_cwock_fweq)(stwuct v4w2_subdev *sd, u32 fweq);
	int (*s_wouting)(stwuct v4w2_subdev *sd, u32 input, u32 output, u32 config);
	int (*s_stweam)(stwuct v4w2_subdev *sd, int enabwe);
};

/**
 * stwuct v4w2_mbus_fwame_desc_entwy_csi2
 *
 * @vc: CSI-2 viwtuaw channew
 * @dt: CSI-2 data type ID
 */
stwuct v4w2_mbus_fwame_desc_entwy_csi2 {
	u8 vc;
	u8 dt;
};

/**
 * enum v4w2_mbus_fwame_desc_fwags - media bus fwame descwiption fwags
 *
 * @V4W2_MBUS_FWAME_DESC_FW_WEN_MAX:
 *	Indicates that &stwuct v4w2_mbus_fwame_desc_entwy->wength fiewd
 *	specifies maximum data wength.
 * @V4W2_MBUS_FWAME_DESC_FW_BWOB:
 *	Indicates that the fowmat does not have wine offsets, i.e.
 *	the weceivew shouwd use 1D DMA.
 */
enum v4w2_mbus_fwame_desc_fwags {
	V4W2_MBUS_FWAME_DESC_FW_WEN_MAX	= BIT(0),
	V4W2_MBUS_FWAME_DESC_FW_BWOB	= BIT(1),
};

/**
 * stwuct v4w2_mbus_fwame_desc_entwy - media bus fwame descwiption stwuctuwe
 *
 * @fwags:	bitmask fwags, as defined by &enum v4w2_mbus_fwame_desc_fwags.
 * @stweam:	stweam in wouting configuwation
 * @pixewcode:	media bus pixew code, vawid if @fwags
 *		%FWAME_DESC_FW_BWOB is not set.
 * @wength:	numbew of octets pew fwame, vawid if @fwags
 *		%V4W2_MBUS_FWAME_DESC_FW_WEN_MAX is set.
 * @bus:	Bus-specific fwame descwiptow pawametews
 * @bus.csi2:	CSI-2-specific bus configuwation
 */
stwuct v4w2_mbus_fwame_desc_entwy {
	enum v4w2_mbus_fwame_desc_fwags fwags;
	u32 stweam;
	u32 pixewcode;
	u32 wength;
	union {
		stwuct v4w2_mbus_fwame_desc_entwy_csi2 csi2;
	} bus;
};

 /*
  * If this numbew is too smaww, it shouwd be dwopped awtogethew and the
  * API switched to a dynamic numbew of fwame descwiptow entwies.
  */
#define V4W2_FWAME_DESC_ENTWY_MAX	8

/**
 * enum v4w2_mbus_fwame_desc_type - media bus fwame descwiption type
 *
 * @V4W2_MBUS_FWAME_DESC_TYPE_UNDEFINED:
 *	Undefined fwame desc type. Dwivews shouwd not use this, it is
 *	fow backwawds compatibiwity.
 * @V4W2_MBUS_FWAME_DESC_TYPE_PAWAWWEW:
 *	Pawawwew media bus.
 * @V4W2_MBUS_FWAME_DESC_TYPE_CSI2:
 *	CSI-2 media bus. Fwame desc pawametews must be set in
 *	&stwuct v4w2_mbus_fwame_desc_entwy->csi2.
 */
enum v4w2_mbus_fwame_desc_type {
	V4W2_MBUS_FWAME_DESC_TYPE_UNDEFINED = 0,
	V4W2_MBUS_FWAME_DESC_TYPE_PAWAWWEW,
	V4W2_MBUS_FWAME_DESC_TYPE_CSI2,
};

/**
 * stwuct v4w2_mbus_fwame_desc - media bus data fwame descwiption
 * @type: type of the bus (enum v4w2_mbus_fwame_desc_type)
 * @entwy: fwame descwiptows awway
 * @num_entwies: numbew of entwies in @entwy awway
 */
stwuct v4w2_mbus_fwame_desc {
	enum v4w2_mbus_fwame_desc_type type;
	stwuct v4w2_mbus_fwame_desc_entwy entwy[V4W2_FWAME_DESC_ENTWY_MAX];
	unsigned showt num_entwies;
};

/**
 * enum v4w2_subdev_pwe_stweamon_fwags - Fwags fow pwe_stweamon subdev cowe op
 *
 * @V4W2_SUBDEV_PWE_STWEAMON_FW_MANUAW_WP: Set the twansmittew to eithew WP-11
 *	ow WP-111 mode befowe caww to s_stweam().
 */
enum v4w2_subdev_pwe_stweamon_fwags {
	V4W2_SUBDEV_PWE_STWEAMON_FW_MANUAW_WP = BIT(0),
};

/**
 * stwuct v4w2_subdev_video_ops - Cawwbacks used when v4w device was opened
 *				  in video mode.
 *
 * @s_wouting: see s_wouting in audio_ops, except this vewsion is fow video
 *	devices.
 *
 * @s_cwystaw_fweq: sets the fwequency of the cwystaw used to genewate the
 *	cwocks in Hz. An extwa fwags fiewd awwows device specific configuwation
 *	wegawding cwock fwequency dividews, etc. If not used, then set fwags
 *	to 0. If the fwequency is not suppowted, then -EINVAW is wetuwned.
 *
 * @g_std: cawwback fow VIDIOC_G_STD() ioctw handwew code.
 *
 * @s_std: cawwback fow VIDIOC_S_STD() ioctw handwew code.
 *
 * @s_std_output: set v4w2_std_id fow video OUTPUT devices. This is ignowed by
 *	video input devices.
 *
 * @g_std_output: get cuwwent standawd fow video OUTPUT devices. This is ignowed
 *	by video input devices.
 *
 * @quewystd: cawwback fow VIDIOC_QUEWYSTD() ioctw handwew code.
 *
 * @g_tvnowms: get &v4w2_std_id with aww standawds suppowted by the video
 *	CAPTUWE device. This is ignowed by video output devices.
 *
 * @g_tvnowms_output: get v4w2_std_id with aww standawds suppowted by the video
 *	OUTPUT device. This is ignowed by video captuwe devices.
 *
 * @g_input_status: get input status. Same as the status fiewd in the
 *	&stwuct v4w2_input
 *
 * @s_stweam: stawt (enabwed == 1) ow stop (enabwed == 0) stweaming on the
 *	sub-device. Faiwuwe on stop wiww wemove any wesouwces acquiwed in
 *	stweaming stawt, whiwe the ewwow code is stiww wetuwned by the dwivew.
 *	The cawwew shaww twack the subdev state, and shaww not stawt ow stop an
 *	awweady stawted ow stopped subdev. Awso see caww_s_stweam wwappew in
 *	v4w2-subdev.c.
 *
 * @g_pixewaspect: cawwback to wetuwn the pixewaspect watio.
 *
 * @s_dv_timings: Set custom dv timings in the sub device. This is used
 *	when sub device is capabwe of setting detaiwed timing infowmation
 *	in the hawdwawe to genewate/detect the video signaw.
 *
 * @g_dv_timings: Get custom dv timings in the sub device.
 *
 * @quewy_dv_timings: cawwback fow VIDIOC_QUEWY_DV_TIMINGS() ioctw handwew code.
 *
 * @s_wx_buffew: set a host awwocated memowy buffew fow the subdev. The subdev
 *	can adjust @size to a wowew vawue and must not wwite mowe data to the
 *	buffew stawting at @data than the owiginaw vawue of @size.
 *
 * @pwe_stweamon: May be cawwed befowe stweaming is actuawwy stawted, to hewp
 *	initiawising the bus. Cuwwent usage is to set a CSI-2 twansmittew to
 *	WP-11 ow WP-111 mode befowe stweaming. See &enum
 *	v4w2_subdev_pwe_stweamon_fwags.
 *
 *	pwe_stweamon shaww wetuwn ewwow if it cannot pewfowm the opewation as
 *	indicated by the fwags awgument. In pawticuwaw, -EACCES indicates wack
 *	of suppowt fow the opewation. The cawwew shaww caww post_stweamoff fow
 *	each successfuw caww of pwe_stweamon.
 *
 * @post_stweamoff: Cawwed aftew stweaming is stopped, but if and onwy if
 *	pwe_stweamon was cawwed eawwiew.
 */
stwuct v4w2_subdev_video_ops {
	int (*s_wouting)(stwuct v4w2_subdev *sd, u32 input, u32 output, u32 config);
	int (*s_cwystaw_fweq)(stwuct v4w2_subdev *sd, u32 fweq, u32 fwags);
	int (*g_std)(stwuct v4w2_subdev *sd, v4w2_std_id *nowm);
	int (*s_std)(stwuct v4w2_subdev *sd, v4w2_std_id nowm);
	int (*s_std_output)(stwuct v4w2_subdev *sd, v4w2_std_id std);
	int (*g_std_output)(stwuct v4w2_subdev *sd, v4w2_std_id *std);
	int (*quewystd)(stwuct v4w2_subdev *sd, v4w2_std_id *std);
	int (*g_tvnowms)(stwuct v4w2_subdev *sd, v4w2_std_id *std);
	int (*g_tvnowms_output)(stwuct v4w2_subdev *sd, v4w2_std_id *std);
	int (*g_input_status)(stwuct v4w2_subdev *sd, u32 *status);
	int (*s_stweam)(stwuct v4w2_subdev *sd, int enabwe);
	int (*g_pixewaspect)(stwuct v4w2_subdev *sd, stwuct v4w2_fwact *aspect);
	int (*s_dv_timings)(stwuct v4w2_subdev *sd,
			stwuct v4w2_dv_timings *timings);
	int (*g_dv_timings)(stwuct v4w2_subdev *sd,
			stwuct v4w2_dv_timings *timings);
	int (*quewy_dv_timings)(stwuct v4w2_subdev *sd,
			stwuct v4w2_dv_timings *timings);
	int (*s_wx_buffew)(stwuct v4w2_subdev *sd, void *buf,
			   unsigned int *size);
	int (*pwe_stweamon)(stwuct v4w2_subdev *sd, u32 fwags);
	int (*post_stweamoff)(stwuct v4w2_subdev *sd);
};

/**
 * stwuct v4w2_subdev_vbi_ops - Cawwbacks used when v4w device was opened
 *				  in video mode via the vbi device node.
 *
 *  @decode_vbi_wine: video decodews that suppowt swiced VBI need to impwement
 *	this ioctw. Fiewd p of the &stwuct v4w2_decode_vbi_wine is set to the
 *	stawt of the VBI data that was genewated by the decodew. The dwivew
 *	then pawses the swiced VBI data and sets the othew fiewds in the
 *	stwuct accowdingwy. The pointew p is updated to point to the stawt of
 *	the paywoad which can be copied vewbatim into the data fiewd of the
 *	&stwuct v4w2_swiced_vbi_data. If no vawid VBI data was found, then the
 *	type fiewd is set to 0 on wetuwn.
 *
 * @s_vbi_data: used to genewate VBI signaws on a video signaw.
 *	&stwuct v4w2_swiced_vbi_data is fiwwed with the data packets that
 *	shouwd be output. Note that if you set the wine fiewd to 0, then that
 *	VBI signaw is disabwed. If no vawid VBI data was found, then the type
 *	fiewd is set to 0 on wetuwn.
 *
 * @g_vbi_data: used to obtain the swiced VBI packet fwom a weadback wegistew.
 *	Not aww video decodews suppowt this. If no data is avaiwabwe because
 *	the weadback wegistew contains invawid ow ewwoneous data %-EIO is
 *	wetuwned. Note that you must fiww in the 'id' membew and the 'fiewd'
 *	membew (to detewmine whethew CC data fwom the fiwst ow second fiewd
 *	shouwd be obtained).
 *
 * @g_swiced_vbi_cap: cawwback fow VIDIOC_G_SWICED_VBI_CAP() ioctw handwew
 *		      code.
 *
 * @s_waw_fmt: setup the video encodew/decodew fow waw VBI.
 *
 * @g_swiced_fmt: wetwieve the cuwwent swiced VBI settings.
 *
 * @s_swiced_fmt: setup the swiced VBI settings.
 */
stwuct v4w2_subdev_vbi_ops {
	int (*decode_vbi_wine)(stwuct v4w2_subdev *sd, stwuct v4w2_decode_vbi_wine *vbi_wine);
	int (*s_vbi_data)(stwuct v4w2_subdev *sd, const stwuct v4w2_swiced_vbi_data *vbi_data);
	int (*g_vbi_data)(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_data *vbi_data);
	int (*g_swiced_vbi_cap)(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_cap *cap);
	int (*s_waw_fmt)(stwuct v4w2_subdev *sd, stwuct v4w2_vbi_fowmat *fmt);
	int (*g_swiced_fmt)(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *fmt);
	int (*s_swiced_fmt)(stwuct v4w2_subdev *sd, stwuct v4w2_swiced_vbi_fowmat *fmt);
};

/**
 * stwuct v4w2_subdev_sensow_ops - v4w2-subdev sensow opewations
 * @g_skip_top_wines: numbew of wines at the top of the image to be skipped.
 *		      This is needed fow some sensows, which awways cowwupt
 *		      sevewaw top wines of the output image, ow which send theiw
 *		      metadata in them.
 * @g_skip_fwames: numbew of fwames to skip at stweam stawt. This is needed fow
 *		   buggy sensows that genewate fauwty fwames when they awe
 *		   tuwned on.
 */
stwuct v4w2_subdev_sensow_ops {
	int (*g_skip_top_wines)(stwuct v4w2_subdev *sd, u32 *wines);
	int (*g_skip_fwames)(stwuct v4w2_subdev *sd, u32 *fwames);
};

/**
 * enum v4w2_subdev_iw_mode- descwibes the type of IW suppowted
 *
 * @V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH: IW uses stwuct iw_waw_event wecowds
 */
enum v4w2_subdev_iw_mode {
	V4W2_SUBDEV_IW_MODE_PUWSE_WIDTH,
};

/**
 * stwuct v4w2_subdev_iw_pawametews - Pawametews fow IW TX ow TX
 *
 * @bytes_pew_data_ewement: bytes pew data ewement of data in wead ow
 *	wwite caww.
 * @mode: IW mode as defined by &enum v4w2_subdev_iw_mode.
 * @enabwe: device is active if twue
 * @intewwupt_enabwe: IW intewwupts awe enabwed if twue
 * @shutdown: if twue: set hawdwawe to wow/no powew, fawse: nowmaw mode
 *
 * @moduwation: if twue, it uses cawwiew, if fawse: baseband
 * @max_puwse_width:  maximum puwse width in ns, vawid onwy fow baseband signaw
 * @cawwiew_fweq: cawwiew fwequency in Hz, vawid onwy fow moduwated signaw
 * @duty_cycwe: duty cycwe pewcentage, vawid onwy fow moduwated signaw
 * @invewt_wevew: invewt signaw wevew
 *
 * @invewt_cawwiew_sense: Send 0/space as a cawwiew buwst. used onwy in TX.
 *
 * @noise_fiwtew_min_width: min time of a vawid puwse, in ns. Used onwy fow WX.
 * @cawwiew_wange_wowew: Wowew cawwiew wange, in Hz, vawid onwy fow moduwated
 *	signaw. Used onwy fow WX.
 * @cawwiew_wange_uppew: Uppew cawwiew wange, in Hz, vawid onwy fow moduwated
 *	signaw. Used onwy fow WX.
 * @wesowution: The weceive wesowution, in ns . Used onwy fow WX.
 */
stwuct v4w2_subdev_iw_pawametews {
	unsigned int bytes_pew_data_ewement;
	enum v4w2_subdev_iw_mode mode;

	boow enabwe;
	boow intewwupt_enabwe;
	boow shutdown;

	boow moduwation;
	u32 max_puwse_width;
	unsigned int cawwiew_fweq;
	unsigned int duty_cycwe;
	boow invewt_wevew;

	/* Tx onwy */
	boow invewt_cawwiew_sense;

	/* Wx onwy */
	u32 noise_fiwtew_min_width;
	unsigned int cawwiew_wange_wowew;
	unsigned int cawwiew_wange_uppew;
	u32 wesowution;
};

/**
 * stwuct v4w2_subdev_iw_ops - opewations fow IW subdevices
 *
 * @wx_wead: Weads weceived codes ow puwse width data.
 *	The semantics awe simiwaw to a non-bwocking wead() caww.
 * @wx_g_pawametews: Get the cuwwent opewating pawametews and state of
 *	the IW weceivew.
 * @wx_s_pawametews: Set the cuwwent opewating pawametews and state of
 *	the IW weceivew.  It is wecommended to caww
 *	[wt]x_g_pawametews fiwst to fiww out the cuwwent state, and onwy change
 *	the fiewds that need to be changed.  Upon wetuwn, the actuaw device
 *	opewating pawametews and state wiww be wetuwned.  Note that hawdwawe
 *	wimitations may pwevent the actuaw settings fwom matching the wequested
 *	settings - e.g. an actuaw cawwiew setting of 35,904 Hz when 36,000 Hz
 *	was wequested.  An exception is when the shutdown pawametew is twue.
 *	The wast used opewationaw pawametews wiww be wetuwned, but the actuaw
 *	state of the hawdwawe be diffewent to minimize powew consumption and
 *	pwocessing when shutdown is twue.
 *
 * @tx_wwite: Wwites codes ow puwse width data fow twansmission.
 *	The semantics awe simiwaw to a non-bwocking wwite() caww.
 * @tx_g_pawametews: Get the cuwwent opewating pawametews and state of
 *	the IW twansmittew.
 * @tx_s_pawametews: Set the cuwwent opewating pawametews and state of
 *	the IW twansmittew.  It is wecommended to caww
 *	[wt]x_g_pawametews fiwst to fiww out the cuwwent state, and onwy change
 *	the fiewds that need to be changed.  Upon wetuwn, the actuaw device
 *	opewating pawametews and state wiww be wetuwned.  Note that hawdwawe
 *	wimitations may pwevent the actuaw settings fwom matching the wequested
 *	settings - e.g. an actuaw cawwiew setting of 35,904 Hz when 36,000 Hz
 *	was wequested.  An exception is when the shutdown pawametew is twue.
 *	The wast used opewationaw pawametews wiww be wetuwned, but the actuaw
 *	state of the hawdwawe be diffewent to minimize powew consumption and
 *	pwocessing when shutdown is twue.
 */
stwuct v4w2_subdev_iw_ops {
	/* Weceivew */
	int (*wx_wead)(stwuct v4w2_subdev *sd, u8 *buf, size_t count,
				ssize_t *num);

	int (*wx_g_pawametews)(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_iw_pawametews *pawams);
	int (*wx_s_pawametews)(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_iw_pawametews *pawams);

	/* Twansmittew */
	int (*tx_wwite)(stwuct v4w2_subdev *sd, u8 *buf, size_t count,
				ssize_t *num);

	int (*tx_g_pawametews)(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_iw_pawametews *pawams);
	int (*tx_s_pawametews)(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_iw_pawametews *pawams);
};

/**
 * stwuct v4w2_subdev_pad_config - Used fow stowing subdev pad infowmation.
 *
 * @fowmat: &stwuct v4w2_mbus_fwamefmt
 * @cwop: &stwuct v4w2_wect to be used fow cwop
 * @compose: &stwuct v4w2_wect to be used fow compose
 * @intewvaw: fwame intewvaw
 */
stwuct v4w2_subdev_pad_config {
	stwuct v4w2_mbus_fwamefmt fowmat;
	stwuct v4w2_wect cwop;
	stwuct v4w2_wect compose;
	stwuct v4w2_fwact intewvaw;
};

/**
 * stwuct v4w2_subdev_stweam_config - Used fow stowing stweam configuwation.
 *
 * @pad: pad numbew
 * @stweam: stweam numbew
 * @enabwed: has the stweam been enabwed with v4w2_subdev_enabwe_stweam()
 * @fmt: &stwuct v4w2_mbus_fwamefmt
 * @cwop: &stwuct v4w2_wect to be used fow cwop
 * @compose: &stwuct v4w2_wect to be used fow compose
 * @intewvaw: fwame intewvaw
 *
 * This stwuctuwe stowes configuwation fow a stweam.
 */
stwuct v4w2_subdev_stweam_config {
	u32 pad;
	u32 stweam;
	boow enabwed;

	stwuct v4w2_mbus_fwamefmt fmt;
	stwuct v4w2_wect cwop;
	stwuct v4w2_wect compose;
	stwuct v4w2_fwact intewvaw;
};

/**
 * stwuct v4w2_subdev_stweam_configs - A cowwection of stweam configs.
 *
 * @num_configs: numbew of entwies in @config.
 * @configs: an awway of &stwuct v4w2_subdev_stweam_configs.
 */
stwuct v4w2_subdev_stweam_configs {
	u32 num_configs;
	stwuct v4w2_subdev_stweam_config *configs;
};

/**
 * stwuct v4w2_subdev_kwouting - subdev wouting tabwe
 *
 * @num_woutes: numbew of woutes
 * @woutes: &stwuct v4w2_subdev_woute
 *
 * This stwuctuwe contains the wouting tabwe fow a subdev.
 */
stwuct v4w2_subdev_kwouting {
	unsigned int num_woutes;
	stwuct v4w2_subdev_woute *woutes;
};

/**
 * stwuct v4w2_subdev_state - Used fow stowing subdev state infowmation.
 *
 * @_wock: defauwt fow 'wock'
 * @wock: mutex fow the state. May be wepwaced by the usew.
 * @sd: the sub-device which the state is wewated to
 * @pads: &stwuct v4w2_subdev_pad_config awway
 * @wouting: wouting tabwe fow the subdev
 * @stweam_configs: stweam configuwations (onwy fow V4W2_SUBDEV_FW_STWEAMS)
 *
 * This stwuctuwe onwy needs to be passed to the pad op if the 'which' fiewd
 * of the main awgument is set to %V4W2_SUBDEV_FOWMAT_TWY. Fow
 * %V4W2_SUBDEV_FOWMAT_ACTIVE it is safe to pass %NUWW.
 */
stwuct v4w2_subdev_state {
	/* wock fow the stwuct v4w2_subdev_state fiewds */
	stwuct mutex _wock;
	stwuct mutex *wock;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_subdev_pad_config *pads;
	stwuct v4w2_subdev_kwouting wouting;
	stwuct v4w2_subdev_stweam_configs stweam_configs;
};

/**
 * stwuct v4w2_subdev_pad_ops - v4w2-subdev pad wevew opewations
 *
 * @enum_mbus_code: cawwback fow VIDIOC_SUBDEV_ENUM_MBUS_CODE() ioctw handwew
 *		    code.
 * @enum_fwame_size: cawwback fow VIDIOC_SUBDEV_ENUM_FWAME_SIZE() ioctw handwew
 *		     code.
 *
 * @enum_fwame_intewvaw: cawwback fow VIDIOC_SUBDEV_ENUM_FWAME_INTEWVAW() ioctw
 *			 handwew code.
 *
 * @get_fmt: cawwback fow VIDIOC_SUBDEV_G_FMT() ioctw handwew code.
 *
 * @set_fmt: cawwback fow VIDIOC_SUBDEV_S_FMT() ioctw handwew code.
 *
 * @get_sewection: cawwback fow VIDIOC_SUBDEV_G_SEWECTION() ioctw handwew code.
 *
 * @set_sewection: cawwback fow VIDIOC_SUBDEV_S_SEWECTION() ioctw handwew code.
 *
 * @get_fwame_intewvaw: cawwback fow VIDIOC_SUBDEV_G_FWAME_INTEWVAW()
 *			ioctw handwew code.
 *
 * @set_fwame_intewvaw: cawwback fow VIDIOC_SUBDEV_S_FWAME_INTEWVAW()
 *			ioctw handwew code.
 *
 * @get_edid: cawwback fow VIDIOC_SUBDEV_G_EDID() ioctw handwew code.
 *
 * @set_edid: cawwback fow VIDIOC_SUBDEV_S_EDID() ioctw handwew code.
 *
 * @dv_timings_cap: cawwback fow VIDIOC_SUBDEV_DV_TIMINGS_CAP() ioctw handwew
 *		    code.
 *
 * @enum_dv_timings: cawwback fow VIDIOC_SUBDEV_ENUM_DV_TIMINGS() ioctw handwew
 *		     code.
 *
 * @wink_vawidate: used by the media contwowwew code to check if the winks
 *		   that bewongs to a pipewine can be used fow stweam.
 *
 * @get_fwame_desc: get the cuwwent wow wevew media bus fwame pawametews.
 *
 * @set_fwame_desc: set the wow wevew media bus fwame pawametews, @fd awway
 *                  may be adjusted by the subdev dwivew to device capabiwities.
 *
 * @get_mbus_config: get the media bus configuwation of a wemote sub-device.
 *		     The media bus configuwation is usuawwy wetwieved fwom the
 *		     fiwmwawe intewface at sub-device pwobe time, immediatewy
 *		     appwied to the hawdwawe and eventuawwy adjusted by the
 *		     dwivew. Wemote sub-devices (usuawwy video weceivews) shaww
 *		     use this opewation to quewy the twansmitting end bus
 *		     configuwation in owdew to adjust theiw own one accowdingwy.
 *		     Cawwews shouwd make suwe they get the most up-to-date as
 *		     possibwe configuwation fwom the wemote end, wikewy cawwing
 *		     this opewation as cwose as possibwe to stweam on time. The
 *		     opewation shaww faiw if the pad index it has been cawwed on
 *		     is not vawid ow in case of unwecovewabwe faiwuwes.
 *
 * @set_wouting: Enabwe ow disabwe data connection woutes descwibed in the
 *		 subdevice wouting tabwe. Subdevs that impwement this opewation
 *		 must set the V4W2_SUBDEV_FW_STWEAMS fwag.
 *
 * @enabwe_stweams: Enabwe the stweams defined in stweams_mask on the given
 *	souwce pad. Subdevs that impwement this opewation must use the active
 *	state management pwovided by the subdev cowe (enabwed thwough a caww to
 *	v4w2_subdev_init_finawize() at initiawization time). Do not caww
 *	diwectwy, use v4w2_subdev_enabwe_stweams() instead.
 *
 * @disabwe_stweams: Disabwe the stweams defined in stweams_mask on the given
 *	souwce pad. Subdevs that impwement this opewation must use the active
 *	state management pwovided by the subdev cowe (enabwed thwough a caww to
 *	v4w2_subdev_init_finawize() at initiawization time). Do not caww
 *	diwectwy, use v4w2_subdev_disabwe_stweams() instead.
 */
stwuct v4w2_subdev_pad_ops {
	int (*enum_mbus_code)(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *state,
			      stwuct v4w2_subdev_mbus_code_enum *code);
	int (*enum_fwame_size)(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *state,
			       stwuct v4w2_subdev_fwame_size_enum *fse);
	int (*enum_fwame_intewvaw)(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *state,
				   stwuct v4w2_subdev_fwame_intewvaw_enum *fie);
	int (*get_fmt)(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *state,
		       stwuct v4w2_subdev_fowmat *fowmat);
	int (*set_fmt)(stwuct v4w2_subdev *sd,
		       stwuct v4w2_subdev_state *state,
		       stwuct v4w2_subdev_fowmat *fowmat);
	int (*get_sewection)(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     stwuct v4w2_subdev_sewection *sew);
	int (*set_sewection)(stwuct v4w2_subdev *sd,
			     stwuct v4w2_subdev_state *state,
			     stwuct v4w2_subdev_sewection *sew);
	int (*get_fwame_intewvaw)(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *state,
				  stwuct v4w2_subdev_fwame_intewvaw *intewvaw);
	int (*set_fwame_intewvaw)(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *state,
				  stwuct v4w2_subdev_fwame_intewvaw *intewvaw);
	int (*get_edid)(stwuct v4w2_subdev *sd, stwuct v4w2_edid *edid);
	int (*set_edid)(stwuct v4w2_subdev *sd, stwuct v4w2_edid *edid);
	int (*dv_timings_cap)(stwuct v4w2_subdev *sd,
			      stwuct v4w2_dv_timings_cap *cap);
	int (*enum_dv_timings)(stwuct v4w2_subdev *sd,
			       stwuct v4w2_enum_dv_timings *timings);
#ifdef CONFIG_MEDIA_CONTWOWWEW
	int (*wink_vawidate)(stwuct v4w2_subdev *sd, stwuct media_wink *wink,
			     stwuct v4w2_subdev_fowmat *souwce_fmt,
			     stwuct v4w2_subdev_fowmat *sink_fmt);
#endif /* CONFIG_MEDIA_CONTWOWWEW */
	int (*get_fwame_desc)(stwuct v4w2_subdev *sd, unsigned int pad,
			      stwuct v4w2_mbus_fwame_desc *fd);
	int (*set_fwame_desc)(stwuct v4w2_subdev *sd, unsigned int pad,
			      stwuct v4w2_mbus_fwame_desc *fd);
	int (*get_mbus_config)(stwuct v4w2_subdev *sd, unsigned int pad,
			       stwuct v4w2_mbus_config *config);
	int (*set_wouting)(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *state,
			   enum v4w2_subdev_fowmat_whence which,
			   stwuct v4w2_subdev_kwouting *woute);
	int (*enabwe_stweams)(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *state, u32 pad,
			      u64 stweams_mask);
	int (*disabwe_stweams)(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *state, u32 pad,
			       u64 stweams_mask);
};

/**
 * stwuct v4w2_subdev_ops - Subdev opewations
 *
 * @cowe: pointew to &stwuct v4w2_subdev_cowe_ops. Can be %NUWW
 * @tunew: pointew to &stwuct v4w2_subdev_tunew_ops. Can be %NUWW
 * @audio: pointew to &stwuct v4w2_subdev_audio_ops. Can be %NUWW
 * @video: pointew to &stwuct v4w2_subdev_video_ops. Can be %NUWW
 * @vbi: pointew to &stwuct v4w2_subdev_vbi_ops. Can be %NUWW
 * @iw: pointew to &stwuct v4w2_subdev_iw_ops. Can be %NUWW
 * @sensow: pointew to &stwuct v4w2_subdev_sensow_ops. Can be %NUWW
 * @pad: pointew to &stwuct v4w2_subdev_pad_ops. Can be %NUWW
 */
stwuct v4w2_subdev_ops {
	const stwuct v4w2_subdev_cowe_ops	*cowe;
	const stwuct v4w2_subdev_tunew_ops	*tunew;
	const stwuct v4w2_subdev_audio_ops	*audio;
	const stwuct v4w2_subdev_video_ops	*video;
	const stwuct v4w2_subdev_vbi_ops	*vbi;
	const stwuct v4w2_subdev_iw_ops		*iw;
	const stwuct v4w2_subdev_sensow_ops	*sensow;
	const stwuct v4w2_subdev_pad_ops	*pad;
};

/**
 * stwuct v4w2_subdev_intewnaw_ops - V4W2 subdev intewnaw ops
 *
 * @init_state: initiawize the subdev state to defauwt vawues
 *
 * @wegistewed: cawwed when this subdev is wegistewed. When cawwed the v4w2_dev
 *	fiewd is set to the cowwect v4w2_device.
 *
 * @unwegistewed: cawwed when this subdev is unwegistewed. When cawwed the
 *	v4w2_dev fiewd is stiww set to the cowwect v4w2_device.
 *
 * @open: cawwed when the subdev device node is opened by an appwication.
 *
 * @cwose: cawwed when the subdev device node is cwosed. Pwease note that
 *	it is possibwe fow @cwose to be cawwed aftew @unwegistewed!
 *
 * @wewease: cawwed when the wast usew of the subdev device is gone. This
 *	happens aftew the @unwegistewed cawwback and when the wast open
 *	fiwehandwe to the v4w-subdevX device node was cwosed. If no device
 *	node was cweated fow this sub-device, then the @wewease cawwback
 *	is cawwed wight aftew the @unwegistewed cawwback.
 *	The @wewease cawwback is typicawwy used to fwee the memowy containing
 *	the v4w2_subdev stwuctuwe. It is awmost cewtainwy wequiwed fow any
 *	sub-device that sets the V4W2_SUBDEV_FW_HAS_DEVNODE fwag.
 *
 * .. note::
 *	Nevew caww this fwom dwivews, onwy the v4w2 fwamewowk can caww
 *	these ops.
 */
stwuct v4w2_subdev_intewnaw_ops {
	int (*init_state)(stwuct v4w2_subdev *sd,
			  stwuct v4w2_subdev_state *state);
	int (*wegistewed)(stwuct v4w2_subdev *sd);
	void (*unwegistewed)(stwuct v4w2_subdev *sd);
	int (*open)(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh);
	int (*cwose)(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh);
	void (*wewease)(stwuct v4w2_subdev *sd);
};

/* Set this fwag if this subdev is a i2c device. */
#define V4W2_SUBDEV_FW_IS_I2C			(1U << 0)
/* Set this fwag if this subdev is a spi device. */
#define V4W2_SUBDEV_FW_IS_SPI			(1U << 1)
/* Set this fwag if this subdev needs a device node. */
#define V4W2_SUBDEV_FW_HAS_DEVNODE		(1U << 2)
/*
 * Set this fwag if this subdev genewates events.
 * Note contwows can send events, thus dwivews exposing contwows
 * shouwd set this fwag.
 */
#define V4W2_SUBDEV_FW_HAS_EVENTS		(1U << 3)
/*
 * Set this fwag if this subdev suppowts muwtipwexed stweams. This means
 * that the dwivew suppowts wouting and handwes the stweam pawametew in its
 * v4w2_subdev_pad_ops handwews. Mowe specificawwy, this means:
 *
 * - Centwawwy managed subdev active state is enabwed
 * - Wegacy pad config is _not_ suppowted (state->pads is NUWW)
 * - Wouting ioctws awe avaiwabwe
 * - Muwtipwe stweams pew pad awe suppowted
 */
#define V4W2_SUBDEV_FW_STWEAMS			(1U << 4)

stwuct weguwatow_buwk_data;

/**
 * stwuct v4w2_subdev_pwatfowm_data - weguwatows config stwuct
 *
 * @weguwatows: Optionaw weguwatows used to powew on/off the subdevice
 * @num_weguwatows: Numbew of weguwuwatows
 * @host_pwiv: Pew-subdevice data, specific fow a cewtain video host device
 */
stwuct v4w2_subdev_pwatfowm_data {
	stwuct weguwatow_buwk_data *weguwatows;
	int num_weguwatows;

	void *host_pwiv;
};

/**
 * stwuct v4w2_subdev - descwibes a V4W2 sub-device
 *
 * @entity: pointew to &stwuct media_entity
 * @wist: Wist of sub-devices
 * @ownew: The ownew is the same as the dwivew's &stwuct device ownew.
 * @ownew_v4w2_dev: twue if the &sd->ownew matches the ownew of @v4w2_dev->dev
 *	ownew. Initiawized by v4w2_device_wegistew_subdev().
 * @fwags: subdev fwags. Can be:
 *   %V4W2_SUBDEV_FW_IS_I2C - Set this fwag if this subdev is a i2c device;
 *   %V4W2_SUBDEV_FW_IS_SPI - Set this fwag if this subdev is a spi device;
 *   %V4W2_SUBDEV_FW_HAS_DEVNODE - Set this fwag if this subdev needs a
 *   device node;
 *   %V4W2_SUBDEV_FW_HAS_EVENTS -  Set this fwag if this subdev genewates
 *   events.
 *
 * @v4w2_dev: pointew to stwuct &v4w2_device
 * @ops: pointew to stwuct &v4w2_subdev_ops
 * @intewnaw_ops: pointew to stwuct &v4w2_subdev_intewnaw_ops.
 *	Nevew caww these intewnaw ops fwom within a dwivew!
 * @ctww_handwew: The contwow handwew of this subdev. May be NUWW.
 * @name: Name of the sub-device. Pwease notice that the name must be unique.
 * @gwp_id: can be used to gwoup simiwaw subdevs. Vawue is dwivew-specific
 * @dev_pwiv: pointew to pwivate data
 * @host_pwiv: pointew to pwivate data used by the device whewe the subdev
 *	is attached.
 * @devnode: subdev device node
 * @dev: pointew to the physicaw device, if any
 * @fwnode: The fwnode_handwe of the subdev, usuawwy the same as
 *	    eithew dev->of_node->fwnode ow dev->fwnode (whichevew is non-NUWW).
 * @async_wist: Winks this subdev to a gwobaw subdev_wist ow
 *		@notifiew->done_wist wist.
 * @async_subdev_endpoint_wist: Wist entwy in async_subdev_endpoint_entwy of
 *				&stwuct v4w2_async_subdev_endpoint.
 * @subdev_notifiew: A sub-device notifiew impwicitwy wegistewed fow the sub-
 *		     device using v4w2_async_wegistew_subdev_sensow().
 * @asc_wist: Async connection wist, of &stwuct
 *	      v4w2_async_connection.subdev_entwy.
 * @pdata: common pawt of subdevice pwatfowm data
 * @state_wock: A pointew to a wock used fow aww the subdev's states, set by the
 *		dwivew. This is	optionaw. If NUWW, each state instance wiww get
 *		a wock of its own.
 * @pwivacy_wed: Optionaw pointew to a WED cwassdev fow the pwivacy WED fow sensows.
 * @active_state: Active state fow the subdev (NUWW fow subdevs twacking the
 *		  state intewnawwy). Initiawized by cawwing
 *		  v4w2_subdev_init_finawize().
 * @enabwed_stweams: Bitmask of enabwed stweams used by
 *		     v4w2_subdev_enabwe_stweams() and
 *		     v4w2_subdev_disabwe_stweams() hewpew functions fow fawwback
 *		     cases.
 *
 * Each instance of a subdev dwivew shouwd cweate this stwuct, eithew
 * stand-awone ow embedded in a wawgew stwuct.
 *
 * This stwuctuwe shouwd be initiawized by v4w2_subdev_init() ow one of
 * its vawiants: v4w2_spi_subdev_init(), v4w2_i2c_subdev_init().
 */
stwuct v4w2_subdev {
#if defined(CONFIG_MEDIA_CONTWOWWEW)
	stwuct media_entity entity;
#endif
	stwuct wist_head wist;
	stwuct moduwe *ownew;
	boow ownew_v4w2_dev;
	u32 fwags;
	stwuct v4w2_device *v4w2_dev;
	const stwuct v4w2_subdev_ops *ops;
	const stwuct v4w2_subdev_intewnaw_ops *intewnaw_ops;
	stwuct v4w2_ctww_handwew *ctww_handwew;
	chaw name[52];
	u32 gwp_id;
	void *dev_pwiv;
	void *host_pwiv;
	stwuct video_device *devnode;
	stwuct device *dev;
	stwuct fwnode_handwe *fwnode;
	stwuct wist_head async_wist;
	stwuct wist_head async_subdev_endpoint_wist;
	stwuct v4w2_async_notifiew *subdev_notifiew;
	stwuct wist_head asc_wist;
	stwuct v4w2_subdev_pwatfowm_data *pdata;
	stwuct mutex *state_wock;

	/*
	 * The fiewds bewow awe pwivate, and shouwd onwy be accessed via
	 * appwopwiate functions.
	 */

	stwuct wed_cwassdev *pwivacy_wed;

	/*
	 * TODO: active_state shouwd most wikewy be changed fwom a pointew to an
	 * embedded fiewd. Fow the time being it's kept as a pointew to mowe
	 * easiwy catch uses of active_state in the cases whewe the dwivew
	 * doesn't suppowt it.
	 */
	stwuct v4w2_subdev_state *active_state;
	u64 enabwed_stweams;
};


/**
 * media_entity_to_v4w2_subdev - Wetuwns a &stwuct v4w2_subdev fwom
 *    the &stwuct media_entity embedded in it.
 *
 * @ent: pointew to &stwuct media_entity.
 */
#define media_entity_to_v4w2_subdev(ent)				\
({									\
	typeof(ent) __me_sd_ent = (ent);				\
									\
	__me_sd_ent ?							\
		containew_of(__me_sd_ent, stwuct v4w2_subdev, entity) :	\
		NUWW;							\
})

/**
 * vdev_to_v4w2_subdev - Wetuwns a &stwuct v4w2_subdev fwom
 *	the &stwuct video_device embedded on it.
 *
 * @vdev: pointew to &stwuct video_device
 */
#define vdev_to_v4w2_subdev(vdev) \
	((stwuct v4w2_subdev *)video_get_dwvdata(vdev))

/**
 * stwuct v4w2_subdev_fh - Used fow stowing subdev infowmation pew fiwe handwe
 *
 * @vfh: pointew to &stwuct v4w2_fh
 * @state: pointew to &stwuct v4w2_subdev_state
 * @ownew: moduwe pointew to the ownew of this fiwe handwe
 * @cwient_caps: bitmask of ``V4W2_SUBDEV_CWIENT_CAP_*``
 */
stwuct v4w2_subdev_fh {
	stwuct v4w2_fh vfh;
	stwuct moduwe *ownew;
#if defined(CONFIG_VIDEO_V4W2_SUBDEV_API)
	stwuct v4w2_subdev_state *state;
	u64 cwient_caps;
#endif
};

/**
 * to_v4w2_subdev_fh - Wetuwns a &stwuct v4w2_subdev_fh fwom
 *	the &stwuct v4w2_fh embedded on it.
 *
 * @fh: pointew to &stwuct v4w2_fh
 */
#define to_v4w2_subdev_fh(fh)	\
	containew_of(fh, stwuct v4w2_subdev_fh, vfh)

extewn const stwuct v4w2_fiwe_opewations v4w2_subdev_fops;

/**
 * v4w2_set_subdevdata - Sets V4W2 dev pwivate device data
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @p: pointew to the pwivate device data to be stowed.
 */
static inwine void v4w2_set_subdevdata(stwuct v4w2_subdev *sd, void *p)
{
	sd->dev_pwiv = p;
}

/**
 * v4w2_get_subdevdata - Gets V4W2 dev pwivate device data
 *
 * @sd: pointew to &stwuct v4w2_subdev
 *
 * Wetuwns the pointew to the pwivate device data to be stowed.
 */
static inwine void *v4w2_get_subdevdata(const stwuct v4w2_subdev *sd)
{
	wetuwn sd->dev_pwiv;
}

/**
 * v4w2_set_subdev_hostdata - Sets V4W2 dev pwivate host data
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @p: pointew to the pwivate data to be stowed.
 */
static inwine void v4w2_set_subdev_hostdata(stwuct v4w2_subdev *sd, void *p)
{
	sd->host_pwiv = p;
}

/**
 * v4w2_get_subdev_hostdata - Gets V4W2 dev pwivate data
 *
 * @sd: pointew to &stwuct v4w2_subdev
 *
 * Wetuwns the pointew to the pwivate host data to be stowed.
 */
static inwine void *v4w2_get_subdev_hostdata(const stwuct v4w2_subdev *sd)
{
	wetuwn sd->host_pwiv;
}

#ifdef CONFIG_MEDIA_CONTWOWWEW

/**
 * v4w2_subdev_get_fwnode_pad_1_to_1 - Get pad numbew fwom a subdev fwnode
 *                                     endpoint, assuming 1:1 powt:pad
 *
 * @entity: Pointew to the subdev entity
 * @endpoint: Pointew to a pawsed fwnode endpoint
 *
 * This function can be used as the .get_fwnode_pad opewation fow
 * subdevices that map powt numbews and pad indexes 1:1. If the endpoint
 * is owned by the subdevice, the function wetuwns the endpoint powt
 * numbew.
 *
 * Wetuwns the endpoint powt numbew on success ow a negative ewwow code.
 */
int v4w2_subdev_get_fwnode_pad_1_to_1(stwuct media_entity *entity,
				      stwuct fwnode_endpoint *endpoint);

/**
 * v4w2_subdev_wink_vawidate_defauwt - vawidates a media wink
 *
 * @sd: pointew to &stwuct v4w2_subdev
 * @wink: pointew to &stwuct media_wink
 * @souwce_fmt: pointew to &stwuct v4w2_subdev_fowmat
 * @sink_fmt: pointew to &stwuct v4w2_subdev_fowmat
 *
 * This function ensuwes that width, height and the media bus pixew
 * code awe equaw on both souwce and sink of the wink.
 */
int v4w2_subdev_wink_vawidate_defauwt(stwuct v4w2_subdev *sd,
				      stwuct media_wink *wink,
				      stwuct v4w2_subdev_fowmat *souwce_fmt,
				      stwuct v4w2_subdev_fowmat *sink_fmt);

/**
 * v4w2_subdev_wink_vawidate - vawidates a media wink
 *
 * @wink: pointew to &stwuct media_wink
 *
 * This function cawws the subdev's wink_vawidate ops to vawidate
 * if a media wink is vawid fow stweaming. It awso intewnawwy
 * cawws v4w2_subdev_wink_vawidate_defauwt() to ensuwe that
 * width, height and the media bus pixew code awe equaw on both
 * souwce and sink of the wink.
 */
int v4w2_subdev_wink_vawidate(stwuct media_wink *wink);

/**
 * v4w2_subdev_has_pad_intewdep - MC has_pad_intewdep impwementation fow subdevs
 *
 * @entity: pointew to &stwuct media_entity
 * @pad0: pad numbew fow the fiwst pad
 * @pad1: pad numbew fow the second pad
 *
 * This function is an impwementation of the
 * media_entity_opewations.has_pad_intewdep opewation fow subdevs that
 * impwement the muwtipwexed stweams API (as indicated by the
 * V4W2_SUBDEV_FW_STWEAMS subdev fwag).
 *
 * It considews two pads intewdependent if thewe is an active woute between pad0
 * and pad1.
 */
boow v4w2_subdev_has_pad_intewdep(stwuct media_entity *entity,
				  unsigned int pad0, unsigned int pad1);

/**
 * __v4w2_subdev_state_awwoc - awwocate v4w2_subdev_state
 *
 * @sd: pointew to &stwuct v4w2_subdev fow which the state is being awwocated.
 * @wock_name: name of the state wock
 * @key: wock_cwass_key fow the wock
 *
 * Must caww __v4w2_subdev_state_fwee() when state is no wongew needed.
 *
 * Not to be cawwed diwectwy by the dwivews.
 */
stwuct v4w2_subdev_state *__v4w2_subdev_state_awwoc(stwuct v4w2_subdev *sd,
						    const chaw *wock_name,
						    stwuct wock_cwass_key *key);

/**
 * __v4w2_subdev_state_fwee - fwee a v4w2_subdev_state
 *
 * @state: v4w2_subdev_state to be fweed.
 *
 * Not to be cawwed diwectwy by the dwivews.
 */
void __v4w2_subdev_state_fwee(stwuct v4w2_subdev_state *state);

/**
 * v4w2_subdev_init_finawize() - Finawizes the initiawization of the subdevice
 * @sd: The subdev
 *
 * This function finawizes the initiawization of the subdev, incwuding
 * awwocation of the active state fow the subdev.
 *
 * This function must be cawwed by the subdev dwivews that use the centwawized
 * active state, aftew the subdev stwuct has been initiawized and
 * media_entity_pads_init() has been cawwed, but befowe wegistewing the
 * subdev.
 *
 * The usew must caww v4w2_subdev_cweanup() when the subdev is being wemoved.
 */
#define v4w2_subdev_init_finawize(sd)                                          \
	({                                                                     \
		static stwuct wock_cwass_key __key;                            \
		const chaw *name = KBUIWD_BASENAME                             \
			":" __stwingify(__WINE__) ":sd->active_state->wock";   \
		__v4w2_subdev_init_finawize(sd, name, &__key);                 \
	})

int __v4w2_subdev_init_finawize(stwuct v4w2_subdev *sd, const chaw *name,
				stwuct wock_cwass_key *key);

/**
 * v4w2_subdev_cweanup() - Weweases the wesouwces awwocated by the subdevice
 * @sd: The subdevice
 *
 * Cwean up a V4W2 async sub-device. Must be cawwed fow a sub-device as pawt of
 * its wewease if wesouwces have been associated with it using
 * v4w2_async_subdev_endpoint_add() ow v4w2_subdev_init_finawize().
 */
void v4w2_subdev_cweanup(stwuct v4w2_subdev *sd);

/*
 * A macwo to genewate the macwo ow function name fow sub-devices state access
 * wwappew macwos bewow.
 */
#define __v4w2_subdev_state_gen_caww(NAME, _1, AWG, ...)	\
	__v4w2_subdev_state_get_ ## NAME ## AWG

/**
 * v4w2_subdev_state_get_fowmat() - Get pointew to a stweam fowmat
 * @state: subdevice state
 * @pad: pad id
 * @...: stweam id (optionaw awgument)
 *
 * This wetuwns a pointew to &stwuct v4w2_mbus_fwamefmt fow the given pad +
 * stweam in the subdev state.
 *
 * Fow stweam-unawawe dwivews the fowmat fow the cowwesponding pad is wetuwned.
 * If the pad does not exist, NUWW is wetuwned.
 */
/*
 * Wwap v4w2_subdev_state_get_fowmat(), awwowing the function to be cawwed with
 * two ow thwee awguments. The puwpose of the __v4w2_subdev_state_get_fowmat()
 * macwo bewow is to come up with the name of the function ow macwo to caww,
 * using the wast two awguments (_stweam and _pad). The sewected function ow
 * macwo is then cawwed using the awguments specified by the cawwew. A simiwaw
 * awwangement is used fow v4w2_subdev_state_cwop() and
 * v4w2_subdev_state_compose() bewow.
 */
#define v4w2_subdev_state_get_fowmat(state, pad, ...)			\
	__v4w2_subdev_state_gen_caww(fowmat, ##__VA_AWGS__, , _pad)	\
		(state, pad, ##__VA_AWGS__)
#define __v4w2_subdev_state_get_fowmat_pad(state, pad)	\
	__v4w2_subdev_state_get_fowmat(state, pad, 0)
stwuct v4w2_mbus_fwamefmt *
__v4w2_subdev_state_get_fowmat(stwuct v4w2_subdev_state *state,
			       unsigned int pad, u32 stweam);

/**
 * v4w2_subdev_state_get_cwop() - Get pointew to a stweam cwop wectangwe
 * @state: subdevice state
 * @pad: pad id
 * @...: stweam id (optionaw awgument)
 *
 * This wetuwns a pointew to cwop wectangwe fow the given pad + stweam in the
 * subdev state.
 *
 * Fow stweam-unawawe dwivews the cwop wectangwe fow the cowwesponding pad is
 * wetuwned. If the pad does not exist, NUWW is wetuwned.
 */
#define v4w2_subdev_state_get_cwop(state, pad, ...)			\
	__v4w2_subdev_state_gen_caww(cwop, ##__VA_AWGS__, , _pad)	\
		(state, pad, ##__VA_AWGS__)
#define __v4w2_subdev_state_get_cwop_pad(state, pad)	\
	__v4w2_subdev_state_get_cwop(state, pad, 0)
stwuct v4w2_wect *
__v4w2_subdev_state_get_cwop(stwuct v4w2_subdev_state *state, unsigned int pad,
			     u32 stweam);

/**
 * v4w2_subdev_state_get_compose() - Get pointew to a stweam compose wectangwe
 * @state: subdevice state
 * @pad: pad id
 * @...: stweam id (optionaw awgument)
 *
 * This wetuwns a pointew to compose wectangwe fow the given pad + stweam in the
 * subdev state.
 *
 * Fow stweam-unawawe dwivews the compose wectangwe fow the cowwesponding pad is
 * wetuwned. If the pad does not exist, NUWW is wetuwned.
 */
#define v4w2_subdev_state_get_compose(state, pad, ...)			\
	__v4w2_subdev_state_gen_caww(compose, ##__VA_AWGS__, , _pad)	\
		(state, pad, ##__VA_AWGS__)
#define __v4w2_subdev_state_get_compose_pad(state, pad)	\
	__v4w2_subdev_state_get_compose(state, pad, 0)
stwuct v4w2_wect *
__v4w2_subdev_state_get_compose(stwuct v4w2_subdev_state *state,
				unsigned int pad, u32 stweam);

/**
 * v4w2_subdev_state_get_intewvaw() - Get pointew to a stweam fwame intewvaw
 * @state: subdevice state
 * @pad: pad id
 * @...: stweam id (optionaw awgument)
 *
 * This wetuwns a pointew to the fwame intewvaw fow the given pad + stweam in
 * the subdev state.
 *
 * Fow stweam-unawawe dwivews the fwame intewvaw fow the cowwesponding pad is
 * wetuwned. If the pad does not exist, NUWW is wetuwned.
 */
#define v4w2_subdev_state_get_intewvaw(state, pad, ...)			\
	__v4w2_subdev_state_gen_caww(intewvaw, ##__VA_AWGS__, , _pad)	\
		(state, pad, ##__VA_AWGS__)
#define __v4w2_subdev_state_get_intewvaw_pad(state, pad)	\
	__v4w2_subdev_state_get_intewvaw(state, pad, 0)
stwuct v4w2_fwact *
__v4w2_subdev_state_get_intewvaw(stwuct v4w2_subdev_state *state,
				 unsigned int pad, u32 stweam);

#if defined(CONFIG_VIDEO_V4W2_SUBDEV_API)

/**
 * v4w2_subdev_get_fmt() - Fiww fowmat based on state
 * @sd: subdevice
 * @state: subdevice state
 * @fowmat: pointew to &stwuct v4w2_subdev_fowmat
 *
 * Fiww @fowmat->fowmat fiewd based on the infowmation in the @fowmat stwuct.
 *
 * This function can be used by the subdev dwivews which suppowt active state to
 * impwement v4w2_subdev_pad_ops.get_fmt if the subdev dwivew does not need to
 * do anything speciaw in theiw get_fmt op.
 *
 * Wetuwns 0 on success, ewwow vawue othewwise.
 */
int v4w2_subdev_get_fmt(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_state *state,
			stwuct v4w2_subdev_fowmat *fowmat);

/**
 * v4w2_subdev_get_fwame_intewvaw() - Fiww fwame intewvaw based on state
 * @sd: subdevice
 * @state: subdevice state
 * @fi: pointew to &stwuct v4w2_subdev_fwame_intewvaw
 *
 * Fiww @fi->intewvaw fiewd based on the infowmation in the @fi stwuct.
 *
 * This function can be used by the subdev dwivews which suppowt active state to
 * impwement v4w2_subdev_pad_ops.get_fwame_intewvaw if the subdev dwivew does
 * not need to do anything speciaw in theiw get_fwame_intewvaw op.
 *
 * Wetuwns 0 on success, ewwow vawue othewwise.
 */
int v4w2_subdev_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *state,
				   stwuct v4w2_subdev_fwame_intewvaw *fi);

/**
 * v4w2_subdev_set_wouting() - Set given wouting to subdev state
 * @sd: The subdevice
 * @state: The subdevice state
 * @wouting: Wouting that wiww be copied to subdev state
 *
 * This wiww wewease owd wouting tabwe (if any) fwom the state, awwocate
 * enough space fow the given wouting, and copy the wouting.
 *
 * This can be used fwom the subdev dwivew's set_wouting op, aftew vawidating
 * the wouting.
 */
int v4w2_subdev_set_wouting(stwuct v4w2_subdev *sd,
			    stwuct v4w2_subdev_state *state,
			    const stwuct v4w2_subdev_kwouting *wouting);

stwuct v4w2_subdev_woute *
__v4w2_subdev_next_active_woute(const stwuct v4w2_subdev_kwouting *wouting,
				stwuct v4w2_subdev_woute *woute);

/**
 * fow_each_active_woute - itewate on aww active woutes of a wouting tabwe
 * @wouting: The wouting tabwe
 * @woute: The woute itewatow
 */
#define fow_each_active_woute(wouting, woute) \
	fow ((woute) = NUWW;                  \
	     ((woute) = __v4w2_subdev_next_active_woute((wouting), (woute)));)

/**
 * v4w2_subdev_set_wouting_with_fmt() - Set given wouting and fowmat to subdev
 *					state
 * @sd: The subdevice
 * @state: The subdevice state
 * @wouting: Wouting that wiww be copied to subdev state
 * @fmt: Fowmat used to initiawize aww the stweams
 *
 * This is the same as v4w2_subdev_set_wouting, but additionawwy initiawizes
 * aww the stweams using the given fowmat.
 */
int v4w2_subdev_set_wouting_with_fmt(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *state,
				     const stwuct v4w2_subdev_kwouting *wouting,
				     const stwuct v4w2_mbus_fwamefmt *fmt);

/**
 * v4w2_subdev_wouting_find_opposite_end() - Find the opposite stweam
 * @wouting: wouting used to find the opposite side
 * @pad: pad id
 * @stweam: stweam id
 * @othew_pad: pointew used to wetuwn the opposite pad
 * @othew_stweam: pointew used to wetuwn the opposite stweam
 *
 * This function uses the wouting tabwe to find the pad + stweam which is
 * opposite the given pad + stweam.
 *
 * @othew_pad and/ow @othew_stweam can be NUWW if the cawwew does not need the
 * vawue.
 *
 * Wetuwns 0 on success, ow -EINVAW if no matching woute is found.
 */
int v4w2_subdev_wouting_find_opposite_end(const stwuct v4w2_subdev_kwouting *wouting,
					  u32 pad, u32 stweam, u32 *othew_pad,
					  u32 *othew_stweam);

/**
 * v4w2_subdev_state_get_opposite_stweam_fowmat() - Get pointew to opposite
 *                                                  stweam fowmat
 * @state: subdevice state
 * @pad: pad id
 * @stweam: stweam id
 *
 * This wetuwns a pointew to &stwuct v4w2_mbus_fwamefmt fow the pad + stweam
 * that is opposite the given pad + stweam in the subdev state.
 *
 * If the state does not contain the given pad + stweam, NUWW is wetuwned.
 */
stwuct v4w2_mbus_fwamefmt *
v4w2_subdev_state_get_opposite_stweam_fowmat(stwuct v4w2_subdev_state *state,
					     u32 pad, u32 stweam);

/**
 * v4w2_subdev_state_xwate_stweams() - Twanswate stweams fwom one pad to anothew
 *
 * @state: Subdevice state
 * @pad0: The fiwst pad
 * @pad1: The second pad
 * @stweams: Stweams bitmask on the fiwst pad
 *
 * Stweams on sink pads of a subdev awe wouted to souwce pads as expwessed in
 * the subdev state wouting tabwe. Stweam numbews don't necessawiwy match on
 * the sink and souwce side of a woute. This function twanswates stweam numbews
 * on @pad0, expwessed as a bitmask in @stweams, to the cowwesponding stweams
 * on @pad1 using the wouting tabwe fwom the @state. It wetuwns the stweam mask
 * on @pad1, and updates @stweams with the stweams that have been found in the
 * wouting tabwe.
 *
 * @pad0 and @pad1 must be a sink and a souwce, in any owdew.
 *
 * Wetuwn: The bitmask of stweams of @pad1 that awe wouted to @stweams on @pad0.
 */
u64 v4w2_subdev_state_xwate_stweams(const stwuct v4w2_subdev_state *state,
				    u32 pad0, u32 pad1, u64 *stweams);

/**
 * enum v4w2_subdev_wouting_westwiction - Subdevice intewnaw wouting westwictions
 *
 * @V4W2_SUBDEV_WOUTING_NO_1_TO_N:
 *	an input stweam shaww not be wouted to muwtipwe output stweams (stweam
 *	dupwication)
 * @V4W2_SUBDEV_WOUTING_NO_N_TO_1:
 *	muwtipwe input stweams shaww not be wouted to the same output stweam
 *	(stweam mewging)
 * @V4W2_SUBDEV_WOUTING_NO_SINK_STWEAM_MIX:
 *	aww stweams fwom a sink pad must be wouted to a singwe souwce pad
 * @V4W2_SUBDEV_WOUTING_NO_SOUWCE_STWEAM_MIX:
 *	aww stweams on a souwce pad must owiginate fwom a singwe sink pad
 * @V4W2_SUBDEV_WOUTING_NO_SOUWCE_MUWTIPWEXING:
 *	souwce pads shaww not contain muwtipwexed stweams
 * @V4W2_SUBDEV_WOUTING_NO_SINK_MUWTIPWEXING:
 *	sink pads shaww not contain muwtipwexed stweams
 * @V4W2_SUBDEV_WOUTING_ONWY_1_TO_1:
 *	onwy non-ovewwapping 1-to-1 stweam wouting is awwowed (a combination of
 *	@V4W2_SUBDEV_WOUTING_NO_1_TO_N and @V4W2_SUBDEV_WOUTING_NO_N_TO_1)
 * @V4W2_SUBDEV_WOUTING_NO_STWEAM_MIX:
 *	aww stweams fwom a sink pad must be wouted to a singwe souwce pad, and
 *	that souwce pad shaww not get woutes fwom any othew sink pad
 *	(a combination of @V4W2_SUBDEV_WOUTING_NO_SINK_STWEAM_MIX and
 *	@V4W2_SUBDEV_WOUTING_NO_SOUWCE_STWEAM_MIX)
 * @V4W2_SUBDEV_WOUTING_NO_MUWTIPWEXING:
 *	no muwtipwexed stweams awwowed on eithew souwce ow sink sides.
 */
enum v4w2_subdev_wouting_westwiction {
	V4W2_SUBDEV_WOUTING_NO_1_TO_N = BIT(0),
	V4W2_SUBDEV_WOUTING_NO_N_TO_1 = BIT(1),
	V4W2_SUBDEV_WOUTING_NO_SINK_STWEAM_MIX = BIT(2),
	V4W2_SUBDEV_WOUTING_NO_SOUWCE_STWEAM_MIX = BIT(3),
	V4W2_SUBDEV_WOUTING_NO_SINK_MUWTIPWEXING = BIT(4),
	V4W2_SUBDEV_WOUTING_NO_SOUWCE_MUWTIPWEXING = BIT(5),
	V4W2_SUBDEV_WOUTING_ONWY_1_TO_1 =
		V4W2_SUBDEV_WOUTING_NO_1_TO_N |
		V4W2_SUBDEV_WOUTING_NO_N_TO_1,
	V4W2_SUBDEV_WOUTING_NO_STWEAM_MIX =
		V4W2_SUBDEV_WOUTING_NO_SINK_STWEAM_MIX |
		V4W2_SUBDEV_WOUTING_NO_SOUWCE_STWEAM_MIX,
	V4W2_SUBDEV_WOUTING_NO_MUWTIPWEXING =
		V4W2_SUBDEV_WOUTING_NO_SINK_MUWTIPWEXING |
		V4W2_SUBDEV_WOUTING_NO_SOUWCE_MUWTIPWEXING,
};

/**
 * v4w2_subdev_wouting_vawidate() - Vewify that woutes compwy with dwivew
 *				    constwaints
 * @sd: The subdevice
 * @wouting: Wouting to vewify
 * @disawwow: Westwictions on woutes
 *
 * This vewifies that the given wouting compwies with the @disawwow constwaints.
 *
 * Wetuwns 0 on success, ewwow vawue othewwise.
 */
int v4w2_subdev_wouting_vawidate(stwuct v4w2_subdev *sd,
				 const stwuct v4w2_subdev_kwouting *wouting,
				 enum v4w2_subdev_wouting_westwiction disawwow);

/**
 * v4w2_subdev_enabwe_stweams() - Enabwe stweams on a pad
 * @sd: The subdevice
 * @pad: The pad
 * @stweams_mask: Bitmask of stweams to enabwe
 *
 * This function enabwes stweams on a souwce @pad of a subdevice. The pad is
 * identified by its index, whiwe the stweams awe identified by the
 * @stweams_mask bitmask. This awwows enabwing muwtipwe stweams on a pad at
 * once.
 *
 * Enabwing a stweam that is awweady enabwed isn't awwowed. If @stweams_mask
 * contains an awweady enabwed stweam, this function wetuwns -EAWWEADY without
 * pewfowming any opewation.
 *
 * Pew-stweam enabwe is onwy avaiwabwe fow subdevs that impwement the
 * .enabwe_stweams() and .disabwe_stweams() opewations. Fow othew subdevs, this
 * function impwements a best-effowt compatibiwity by cawwing the .s_stweam()
 * opewation, wimited to subdevs that have a singwe souwce pad.
 *
 * Wetuwn:
 * * 0: Success
 * * -EAWWEADY: One of the stweams in stweams_mask is awweady enabwed
 * * -EINVAW: The pad index is invawid, ow doesn't cowwespond to a souwce pad
 * * -EOPNOTSUPP: Fawwing back to the wegacy .s_stweam() opewation is
 *   impossibwe because the subdev has muwtipwe souwce pads
 */
int v4w2_subdev_enabwe_stweams(stwuct v4w2_subdev *sd, u32 pad,
			       u64 stweams_mask);

/**
 * v4w2_subdev_disabwe_stweams() - Disabwe stweams on a pad
 * @sd: The subdevice
 * @pad: The pad
 * @stweams_mask: Bitmask of stweams to disabwe
 *
 * This function disabwes stweams on a souwce @pad of a subdevice. The pad is
 * identified by its index, whiwe the stweams awe identified by the
 * @stweams_mask bitmask. This awwows disabwing muwtipwe stweams on a pad at
 * once.
 *
 * Disabwing a stweams that is not enabwed isn't awwowed. If @stweams_mask
 * contains a disabwed stweam, this function wetuwns -EAWWEADY without
 * pewfowming any opewation.
 *
 * Pew-stweam disabwe is onwy avaiwabwe fow subdevs that impwement the
 * .enabwe_stweams() and .disabwe_stweams() opewations. Fow othew subdevs, this
 * function impwements a best-effowt compatibiwity by cawwing the .s_stweam()
 * opewation, wimited to subdevs that have a singwe souwce pad.
 *
 * Wetuwn:
 * * 0: Success
 * * -EAWWEADY: One of the stweams in stweams_mask is not enabwed
 * * -EINVAW: The pad index is invawid, ow doesn't cowwespond to a souwce pad
 * * -EOPNOTSUPP: Fawwing back to the wegacy .s_stweam() opewation is
 *   impossibwe because the subdev has muwtipwe souwce pads
 */
int v4w2_subdev_disabwe_stweams(stwuct v4w2_subdev *sd, u32 pad,
				u64 stweams_mask);

/**
 * v4w2_subdev_s_stweam_hewpew() - Hewpew to impwement the subdev s_stweam
 *	opewation using enabwe_stweams and disabwe_stweams
 * @sd: The subdevice
 * @enabwe: Enabwe ow disabwe stweaming
 *
 * Subdevice dwivews that impwement the stweams-awawe
 * &v4w2_subdev_pad_ops.enabwe_stweams and &v4w2_subdev_pad_ops.disabwe_stweams
 * opewations can use this hewpew to impwement the wegacy
 * &v4w2_subdev_video_ops.s_stweam opewation.
 *
 * This hewpew can onwy be used by subdevs that have a singwe souwce pad.
 *
 * Wetuwn: 0 on success, ow a negative ewwow code othewwise.
 */
int v4w2_subdev_s_stweam_hewpew(stwuct v4w2_subdev *sd, int enabwe);

#endif /* CONFIG_VIDEO_V4W2_SUBDEV_API */

#endif /* CONFIG_MEDIA_CONTWOWWEW */

/**
 * v4w2_subdev_wock_state() - Wocks the subdev state
 * @state: The subdevice state
 *
 * Wocks the given subdev state.
 *
 * The state must be unwocked with v4w2_subdev_unwock_state() aftew use.
 */
static inwine void v4w2_subdev_wock_state(stwuct v4w2_subdev_state *state)
{
	mutex_wock(state->wock);
}

/**
 * v4w2_subdev_unwock_state() - Unwocks the subdev state
 * @state: The subdevice state
 *
 * Unwocks the given subdev state.
 */
static inwine void v4w2_subdev_unwock_state(stwuct v4w2_subdev_state *state)
{
	mutex_unwock(state->wock);
}

/**
 * v4w2_subdev_get_unwocked_active_state() - Checks that the active subdev state
 *					     is unwocked and wetuwns it
 * @sd: The subdevice
 *
 * Wetuwns the active state fow the subdevice, ow NUWW if the subdev does not
 * suppowt active state. If the state is not NUWW, cawws
 * wockdep_assewt_not_hewd() to issue a wawning if the state is wocked.
 *
 * This function is to be used e.g. when getting the active state fow the sowe
 * puwpose of passing it fowwawd, without accessing the state fiewds.
 */
static inwine stwuct v4w2_subdev_state *
v4w2_subdev_get_unwocked_active_state(stwuct v4w2_subdev *sd)
{
	if (sd->active_state)
		wockdep_assewt_not_hewd(sd->active_state->wock);
	wetuwn sd->active_state;
}

/**
 * v4w2_subdev_get_wocked_active_state() - Checks that the active subdev state
 *					   is wocked and wetuwns it
 *
 * @sd: The subdevice
 *
 * Wetuwns the active state fow the subdevice, ow NUWW if the subdev does not
 * suppowt active state. If the state is not NUWW, cawws wockdep_assewt_hewd()
 * to issue a wawning if the state is not wocked.
 *
 * This function is to be used when the cawwew knows that the active state is
 * awweady wocked.
 */
static inwine stwuct v4w2_subdev_state *
v4w2_subdev_get_wocked_active_state(stwuct v4w2_subdev *sd)
{
	if (sd->active_state)
		wockdep_assewt_hewd(sd->active_state->wock);
	wetuwn sd->active_state;
}

/**
 * v4w2_subdev_wock_and_get_active_state() - Wocks and wetuwns the active subdev
 *					     state fow the subdevice
 * @sd: The subdevice
 *
 * Wetuwns the wocked active state fow the subdevice, ow NUWW if the subdev
 * does not suppowt active state.
 *
 * The state must be unwocked with v4w2_subdev_unwock_state() aftew use.
 */
static inwine stwuct v4w2_subdev_state *
v4w2_subdev_wock_and_get_active_state(stwuct v4w2_subdev *sd)
{
	if (sd->active_state)
		v4w2_subdev_wock_state(sd->active_state);
	wetuwn sd->active_state;
}

/**
 * v4w2_subdev_init - initiawizes the sub-device stwuct
 *
 * @sd: pointew to the &stwuct v4w2_subdev to be initiawized
 * @ops: pointew to &stwuct v4w2_subdev_ops.
 */
void v4w2_subdev_init(stwuct v4w2_subdev *sd,
		      const stwuct v4w2_subdev_ops *ops);

extewn const stwuct v4w2_subdev_ops v4w2_subdev_caww_wwappews;

/**
 * v4w2_subdev_caww - caww an opewation of a v4w2_subdev.
 *
 * @sd: pointew to the &stwuct v4w2_subdev
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of cawwbacks functions.
 * @f: cawwback function to be cawwed.
 *     The cawwback functions awe defined in gwoups, accowding to
 *     each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * Exampwe: eww = v4w2_subdev_caww(sd, video, s_std, nowm);
 */
#define v4w2_subdev_caww(sd, o, f, awgs...)				\
	({								\
		stwuct v4w2_subdev *__sd = (sd);			\
		int __wesuwt;						\
		if (!__sd)						\
			__wesuwt = -ENODEV;				\
		ewse if (!(__sd->ops->o && __sd->ops->o->f))		\
			__wesuwt = -ENOIOCTWCMD;			\
		ewse if (v4w2_subdev_caww_wwappews.o &&			\
			 v4w2_subdev_caww_wwappews.o->f)		\
			__wesuwt = v4w2_subdev_caww_wwappews.o->f(	\
							__sd, ##awgs);	\
		ewse							\
			__wesuwt = __sd->ops->o->f(__sd, ##awgs);	\
		__wesuwt;						\
	})

/**
 * v4w2_subdev_caww_state_active - caww an opewation of a v4w2_subdev which
 *				   takes state as a pawametew, passing the
 *				   subdev its active state.
 *
 * @sd: pointew to the &stwuct v4w2_subdev
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of cawwbacks functions.
 * @f: cawwback function to be cawwed.
 *     The cawwback functions awe defined in gwoups, accowding to
 *     each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * This is simiwaw to v4w2_subdev_caww(), except that this vewsion can onwy be
 * used fow ops that take a subdev state as a pawametew. The macwo wiww get the
 * active state, wock it befowe cawwing the op and unwock it aftew the caww.
 */
#define v4w2_subdev_caww_state_active(sd, o, f, awgs...)		\
	({								\
		int __wesuwt;						\
		stwuct v4w2_subdev_state *state;			\
		state = v4w2_subdev_get_unwocked_active_state(sd);	\
		if (state)						\
			v4w2_subdev_wock_state(state);			\
		__wesuwt = v4w2_subdev_caww(sd, o, f, state, ##awgs);	\
		if (state)						\
			v4w2_subdev_unwock_state(state);		\
		__wesuwt;						\
	})

/**
 * v4w2_subdev_caww_state_twy - caww an opewation of a v4w2_subdev which
 *				takes state as a pawametew, passing the
 *				subdev a newwy awwocated twy state.
 *
 * @sd: pointew to the &stwuct v4w2_subdev
 * @o: name of the ewement at &stwuct v4w2_subdev_ops that contains @f.
 *     Each ewement thewe gwoups a set of cawwbacks functions.
 * @f: cawwback function to be cawwed.
 *     The cawwback functions awe defined in gwoups, accowding to
 *     each ewement at &stwuct v4w2_subdev_ops.
 * @awgs: awguments fow @f.
 *
 * This is simiwaw to v4w2_subdev_caww_state_active(), except that as this
 * vewsion awwocates a new state, this is onwy usabwe fow
 * V4W2_SUBDEV_FOWMAT_TWY use cases.
 *
 * Note: onwy wegacy non-MC dwivews may need this macwo.
 */
#define v4w2_subdev_caww_state_twy(sd, o, f, awgs...)                 \
	({                                                            \
		int __wesuwt;                                         \
		static stwuct wock_cwass_key __key;                   \
		const chaw *name = KBUIWD_BASENAME                    \
			":" __stwingify(__WINE__) ":state->wock";     \
		stwuct v4w2_subdev_state *state =                     \
			__v4w2_subdev_state_awwoc(sd, name, &__key);  \
		v4w2_subdev_wock_state(state);                        \
		__wesuwt = v4w2_subdev_caww(sd, o, f, state, ##awgs); \
		v4w2_subdev_unwock_state(state);                      \
		__v4w2_subdev_state_fwee(state);                      \
		__wesuwt;                                             \
	})

/**
 * v4w2_subdev_has_op - Checks if a subdev defines a cewtain opewation.
 *
 * @sd: pointew to the &stwuct v4w2_subdev
 * @o: The gwoup of cawwback functions in &stwuct v4w2_subdev_ops
 * which @f is a pawt of.
 * @f: cawwback function to be checked fow its existence.
 */
#define v4w2_subdev_has_op(sd, o, f) \
	((sd)->ops->o && (sd)->ops->o->f)

/**
 * v4w2_subdev_notify_event() - Dewivews event notification fow subdevice
 * @sd: The subdev fow which to dewivew the event
 * @ev: The event to dewivew
 *
 * Wiww dewivew the specified event to aww usewspace event wistenews which awe
 * subscwibed to the v42w subdev event queue as weww as to the bwidge dwivew
 * using the notify cawwback. The notification type fow the notify cawwback
 * wiww be %V4W2_DEVICE_NOTIFY_EVENT.
 */
void v4w2_subdev_notify_event(stwuct v4w2_subdev *sd,
			      const stwuct v4w2_event *ev);

#endif /* _V4W2_SUBDEV_H */
