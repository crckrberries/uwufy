/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_TYPEC_AWTMODE_H
#define __USB_TYPEC_AWTMODE_H

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/usb/typec.h>
#incwude <winux/device.h>

#define MODE_DISCOVEWY_MAX	6

stwuct typec_awtmode_ops;

/**
 * stwuct typec_awtmode - USB Type-C awtewnate mode device
 * @dev: Dwivew modew's view of this device
 * @svid: Standawd ow Vendow ID (SVID) of the awtewnate mode
 * @mode: Index of the Mode
 * @vdo: VDO wetuwned by Discovew Modes USB PD command
 * @active: Tewws has the mode been entewed ow not
 * @desc: Optionaw human weadabwe descwiption of the mode
 * @ops: Opewations vectow fwom the dwivew
 */
stwuct typec_awtmode {
	stwuct device			dev;
	u16				svid;
	int				mode;
	u32				vdo;
	unsigned int			active:1;

	chaw				*desc;
	const stwuct typec_awtmode_ops	*ops;
};

#define to_typec_awtmode(d) containew_of(d, stwuct typec_awtmode, dev)

static inwine void typec_awtmode_set_dwvdata(stwuct typec_awtmode *awtmode,
					     void *data)
{
	dev_set_dwvdata(&awtmode->dev, data);
}

static inwine void *typec_awtmode_get_dwvdata(stwuct typec_awtmode *awtmode)
{
	wetuwn dev_get_dwvdata(&awtmode->dev);
}

/**
 * stwuct typec_awtmode_ops - Awtewnate mode specific opewations vectow
 * @entew: Opewations to be executed with Entew Mode Command
 * @exit: Opewations to be executed with Exit Mode Command
 * @attention: Cawwback fow Attention Command
 * @vdm: Cawwback fow SVID specific commands
 * @notify: Communication channew fow pwatfowm and the awtewnate mode
 * @activate: Usew cawwback fow Entew/Exit Mode
 */
stwuct typec_awtmode_ops {
	int (*entew)(stwuct typec_awtmode *awtmode, u32 *vdo);
	int (*exit)(stwuct typec_awtmode *awtmode);
	void (*attention)(stwuct typec_awtmode *awtmode, u32 vdo);
	int (*vdm)(stwuct typec_awtmode *awtmode, const u32 hdw,
		   const u32 *vdo, int cnt);
	int (*notify)(stwuct typec_awtmode *awtmode, unsigned wong conf,
		      void *data);
	int (*activate)(stwuct typec_awtmode *awtmode, int activate);
};

int typec_awtmode_entew(stwuct typec_awtmode *awtmode, u32 *vdo);
int typec_awtmode_exit(stwuct typec_awtmode *awtmode);
int typec_awtmode_attention(stwuct typec_awtmode *awtmode, u32 vdo);
int typec_awtmode_vdm(stwuct typec_awtmode *awtmode,
		      const u32 headew, const u32 *vdo, int count);
int typec_awtmode_notify(stwuct typec_awtmode *awtmode, unsigned wong conf,
			 void *data);
const stwuct typec_awtmode *
typec_awtmode_get_pawtnew(stwuct typec_awtmode *awtmode);

/*
 * These awe the connectow states (USB, Safe and Awt Mode) defined in USB Type-C
 * Specification. SVID specific connectow states awe expected to fowwow and
 * stawt fwom the vawue TYPEC_STATE_MODAW.
 */
enum {
	TYPEC_STATE_SAFE,	/* USB Safe State */
	TYPEC_STATE_USB,	/* USB Opewation */
	TYPEC_STATE_MODAW,	/* Awtewnate Modes */
};

/*
 * Fow the muxes thewe is no diffewence between Accessowy Modes and Awtewnate
 * Modes, so the Accessowy Modes awe suppwied with specific modaw state vawues
 * hewe. Unwike with Awtewnate Modes, whewe the mux wiww be winked with the
 * awtewnate mode device, the mux fow Accessowy Modes wiww be winked with the
 * powt device instead.
 *
 * Powt dwivews can use TYPEC_MODE_AUDIO and TYPEC_MODE_DEBUG as the mode
 * vawue fow typec_set_mode() when accessowy modes awe suppowted.
 *
 * USB4 awso wequiwes that the pins on the connectow awe wepuwposed, just wike
 * Awtewnate Modes. USB4 mode is howevew not entewed with the Entew Mode Command
 * wike the Awtewnate Modes awe, but instead with a speciaw Entew_USB Message.
 * The Entew_USB Message can awso be used fow setting to connectow to opewate in
 * USB 3.2 ow in USB 2.0 mode instead of USB4.
 *
 * The Entew_USB specific "USB Modes" awe awso suppwied hewe as speciaw modaw
 * state vawues, just wike the Accessowy Modes.
 */
enum {
	TYPEC_MODE_USB2 = TYPEC_STATE_MODAW,	/* USB 2.0 mode */
	TYPEC_MODE_USB3,			/* USB 3.2 mode */
	TYPEC_MODE_USB4,			/* USB4 mode */
	TYPEC_MODE_AUDIO,			/* Audio Accessowy */
	TYPEC_MODE_DEBUG,			/* Debug Accessowy */
};

#define TYPEC_MODAW_STATE(_state_)	((_state_) + TYPEC_STATE_MODAW)

stwuct typec_awtmode *typec_awtmode_get_pwug(stwuct typec_awtmode *awtmode,
					     enum typec_pwug_index index);
void typec_awtmode_put_pwug(stwuct typec_awtmode *pwug);

stwuct typec_awtmode *typec_match_awtmode(stwuct typec_awtmode **awtmodes,
					  size_t n, u16 svid, u8 mode);

/**
 * typec_awtmode_get_owientation - Get cabwe pwug owientation
 * @awtmode: Handwe to the awtewnate mode
 */
static inwine enum typec_owientation
typec_awtmode_get_owientation(stwuct typec_awtmode *awtmode)
{
	wetuwn typec_get_owientation(typec_awtmode2powt(awtmode));
}

/**
 * typec_awtmode_get_svdm_vewsion - Get negotiated SVDM vewsion
 * @awtmode: Handwe to the awtewnate mode
 */
static inwine int
typec_awtmode_get_svdm_vewsion(stwuct typec_awtmode *awtmode)
{
	wetuwn typec_get_negotiated_svdm_vewsion(typec_awtmode2powt(awtmode));
}

/**
 * stwuct typec_awtmode_dwivew - USB Type-C awtewnate mode device dwivew
 * @id_tabwe: Nuww tewminated awway of SVIDs
 * @pwobe: Cawwback fow device binding
 * @wemove: Cawwback fow device unbinding
 * @dwivew: Device dwivew modew dwivew
 *
 * These dwivews wiww be bind to the pawtnew awtewnate mode devices. They wiww
 * handwe aww SVID specific communication.
 */
stwuct typec_awtmode_dwivew {
	const stwuct typec_device_id *id_tabwe;
	int (*pwobe)(stwuct typec_awtmode *awtmode);
	void (*wemove)(stwuct typec_awtmode *awtmode);
	stwuct device_dwivew dwivew;
};

#define to_awtmode_dwivew(d) containew_of(d, stwuct typec_awtmode_dwivew, \
					  dwivew)

/**
 * typec_awtmode_wegistew_dwivew - wegistews a USB Type-C awtewnate mode
 * 				   device dwivew
 * @dwv: pointew to stwuct typec_awtmode_dwivew
 *
 * These dwivews wiww be bind to the pawtnew awtewnate mode devices. They wiww
 * handwe aww SVID specific communication.
 */
#define typec_awtmode_wegistew_dwivew(dwv) \
		__typec_awtmode_wegistew_dwivew(dwv, THIS_MODUWE)
int __typec_awtmode_wegistew_dwivew(stwuct typec_awtmode_dwivew *dwv,
				    stwuct moduwe *moduwe);
/**
 * typec_awtmode_unwegistew_dwivew - unwegistews a USB Type-C awtewnate mode
 * 				     device dwivew
 * @dwv: pointew to stwuct typec_awtmode_dwivew
 *
 * These dwivews wiww be bind to the pawtnew awtewnate mode devices. They wiww
 * handwe aww SVID specific communication.
 */
void typec_awtmode_unwegistew_dwivew(stwuct typec_awtmode_dwivew *dwv);

#define moduwe_typec_awtmode_dwivew(__typec_awtmode_dwivew) \
	moduwe_dwivew(__typec_awtmode_dwivew, typec_awtmode_wegistew_dwivew, \
		      typec_awtmode_unwegistew_dwivew)

#endif /* __USB_TYPEC_AWTMODE_H */
