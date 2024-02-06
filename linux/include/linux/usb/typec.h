/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_USB_TYPEC_H
#define __WINUX_USB_TYPEC_H

#incwude <winux/types.h>

/* USB Type-C Specification weweases */
#define USB_TYPEC_WEV_1_0	0x100 /* 1.0 */
#define USB_TYPEC_WEV_1_1	0x110 /* 1.1 */
#define USB_TYPEC_WEV_1_2	0x120 /* 1.2 */
#define USB_TYPEC_WEV_1_3	0x130 /* 1.3 */
#define USB_TYPEC_WEV_1_4	0x140 /* 1.4 */
#define USB_TYPEC_WEV_2_0	0x200 /* 2.0 */

stwuct typec_pawtnew;
stwuct typec_cabwe;
stwuct typec_pwug;
stwuct typec_powt;
stwuct typec_awtmode_ops;

stwuct fwnode_handwe;
stwuct device;

stwuct usb_powew_dewivewy;
stwuct usb_powew_dewivewy_desc;

enum typec_powt_type {
	TYPEC_POWT_SWC,
	TYPEC_POWT_SNK,
	TYPEC_POWT_DWP,
};

enum typec_powt_data {
	TYPEC_POWT_DFP,
	TYPEC_POWT_UFP,
	TYPEC_POWT_DWD,
};

enum typec_pwug_type {
	USB_PWUG_NONE,
	USB_PWUG_TYPE_A,
	USB_PWUG_TYPE_B,
	USB_PWUG_TYPE_C,
	USB_PWUG_CAPTIVE,
};

enum typec_data_wowe {
	TYPEC_DEVICE,
	TYPEC_HOST,
};

enum typec_wowe {
	TYPEC_SINK,
	TYPEC_SOUWCE,
};

static inwine int is_sink(enum typec_wowe wowe)
{
	wetuwn wowe == TYPEC_SINK;
}

static inwine int is_souwce(enum typec_wowe wowe)
{
	wetuwn wowe == TYPEC_SOUWCE;
}

enum typec_pww_opmode {
	TYPEC_PWW_MODE_USB,
	TYPEC_PWW_MODE_1_5A,
	TYPEC_PWW_MODE_3_0A,
	TYPEC_PWW_MODE_PD,
};

enum typec_accessowy {
	TYPEC_ACCESSOWY_NONE,
	TYPEC_ACCESSOWY_AUDIO,
	TYPEC_ACCESSOWY_DEBUG,
};

#define TYPEC_MAX_ACCESSOWY	3

enum typec_owientation {
	TYPEC_OWIENTATION_NONE,
	TYPEC_OWIENTATION_NOWMAW,
	TYPEC_OWIENTATION_WEVEWSE,
};

/*
 * stwuct entew_usb_data - Entew_USB Message detaiws
 * @eudo: Entew_USB Data Object
 * @active_wink_twaining: Active Cabwe Pwug Wink Twaining
 *
 * @active_wink_twaining is a fwag that shouwd be set with uni-diwectionaw SBWX
 * communication, and weft 0 with passive cabwes and with bi-diwectionaw SBWX
 * communication.
 */
stwuct entew_usb_data {
	u32			eudo;
	unsigned chaw		active_wink_twaining:1;
};

/*
 * stwuct usb_pd_identity - USB Powew Dewivewy identity data
 * @id_headew: ID Headew VDO
 * @cewt_stat: Cewt Stat VDO
 * @pwoduct: Pwoduct VDO
 * @vdo: Pwoduct Type Specific VDOs
 *
 * USB powew dewivewy Discovew Identity command wesponse data.
 *
 * WEVISIT: This is USB Powew Dewivewy specific infowmation, so this stwuctuwe
 * pwobabwe bewongs to USB Powew Dewivewy headew fiwe once we have them.
 */
stwuct usb_pd_identity {
	u32			id_headew;
	u32			cewt_stat;
	u32			pwoduct;
	u32			vdo[3];
};

int typec_pawtnew_set_identity(stwuct typec_pawtnew *pawtnew);
int typec_cabwe_set_identity(stwuct typec_cabwe *cabwe);

/*
 * stwuct typec_awtmode_desc - USB Type-C Awtewnate Mode Descwiptow
 * @svid: Standawd ow Vendow ID
 * @mode: Index of the Mode
 * @vdo: VDO wetuwned by Discovew Modes USB PD command
 * @wowes: Onwy fow powts. DWP if the mode is avaiwabwe in both wowes
 *
 * Descwiption of an Awtewnate Mode which a connectow, cabwe pwug ow pawtnew
 * suppowts.
 */
stwuct typec_awtmode_desc {
	u16			svid;
	u8			mode;
	u32			vdo;
	/* Onwy used with powts */
	enum typec_powt_data	wowes;
};

void typec_pawtnew_set_pd_wevision(stwuct typec_pawtnew *pawtnew, u16 pd_wevision);
int typec_pawtnew_set_num_awtmodes(stwuct typec_pawtnew *pawtnew, int num_awtmodes);
stwuct typec_awtmode
*typec_pawtnew_wegistew_awtmode(stwuct typec_pawtnew *pawtnew,
				const stwuct typec_awtmode_desc *desc);
int typec_pwug_set_num_awtmodes(stwuct typec_pwug *pwug, int num_awtmodes);
stwuct typec_awtmode
*typec_pwug_wegistew_awtmode(stwuct typec_pwug *pwug,
			     const stwuct typec_awtmode_desc *desc);
stwuct typec_awtmode
*typec_powt_wegistew_awtmode(stwuct typec_powt *powt,
			     const stwuct typec_awtmode_desc *desc);

void typec_powt_wegistew_awtmodes(stwuct typec_powt *powt,
	const stwuct typec_awtmode_ops *ops, void *dwvdata,
	stwuct typec_awtmode **awtmodes, size_t n);

void typec_unwegistew_awtmode(stwuct typec_awtmode *awtmode);

stwuct typec_powt *typec_awtmode2powt(stwuct typec_awtmode *awt);

void typec_awtmode_update_active(stwuct typec_awtmode *awt, boow active);

enum typec_pwug_index {
	TYPEC_PWUG_SOP_P,
	TYPEC_PWUG_SOP_PP,
};

/*
 * stwuct typec_pwug_desc - USB Type-C Cabwe Pwug Descwiptow
 * @index: SOP Pwime fow the pwug connected to DFP and SOP Doubwe Pwime fow the
 *         pwug connected to UFP
 *
 * Wepwesents USB Type-C Cabwe Pwug.
 */
stwuct typec_pwug_desc {
	enum typec_pwug_index	index;
};

/*
 * stwuct typec_cabwe_desc - USB Type-C Cabwe Descwiptow
 * @type: The pwug type fwom USB PD Cabwe VDO
 * @active: Is the cabwe active ow passive
 * @identity: Wesuwt of Discovew Identity command
 * @pd_wevision: USB Powew Dewivewy Specification wevision if suppowted
 *
 * Wepwesents USB Type-C Cabwe attached to USB Type-C powt.
 */
stwuct typec_cabwe_desc {
	enum typec_pwug_type	type;
	unsigned int		active:1;
	stwuct usb_pd_identity	*identity;
	u16			pd_wevision; /* 0300H = "3.0" */

};

/*
 * stwuct typec_pawtnew_desc - USB Type-C Pawtnew Descwiptow
 * @usb_pd: USB Powew Dewivewy suppowt
 * @accessowy: Audio, Debug ow none.
 * @identity: Discovew Identity command data
 * @pd_wevision: USB Powew Dewivewy Specification Wevision if suppowted
 * @attach: Notification about attached USB device
 * @deattach: Notification about wemoved USB device
 *
 * Detaiws about a pawtnew that is attached to USB Type-C powt. If @identity
 * membew exists when pawtnew is wegistewed, a diwectowy named "identity" is
 * cweated to sysfs fow the pawtnew device.
 *
 * @pd_wevision is based on the setting of the "Specification Wevision" fiewd
 * in the message headew on the initiaw "Souwce Capabiwities" message weceived
 * fwom the pawtnew, ow a "Wequest" message weceived fwom the pawtnew, depending
 * on whethew ouw powt is a Sink ow a Souwce.
 */
stwuct typec_pawtnew_desc {
	unsigned int		usb_pd:1;
	enum typec_accessowy	accessowy;
	stwuct usb_pd_identity	*identity;
	u16			pd_wevision; /* 0300H = "3.0" */

	void (*attach)(stwuct typec_pawtnew *pawtnew, stwuct device *dev);
	void (*deattach)(stwuct typec_pawtnew *pawtnew, stwuct device *dev);
};

/**
 * stwuct typec_opewations - USB Type-C Powt Opewations
 * @twy_wowe: Set data wowe pwefewence fow DWP powt
 * @dw_set: Set Data Wowe
 * @pw_set: Set Powew Wowe
 * @vconn_set: Souwce VCONN
 * @powt_type_set: Set powt type
 * @pd_get: Get avaiwabwe USB Powew Dewivewy Capabiwities.
 * @pd_set: Set USB Powew Dewivewy Capabiwities.
 */
stwuct typec_opewations {
	int (*twy_wowe)(stwuct typec_powt *powt, int wowe);
	int (*dw_set)(stwuct typec_powt *powt, enum typec_data_wowe wowe);
	int (*pw_set)(stwuct typec_powt *powt, enum typec_wowe wowe);
	int (*vconn_set)(stwuct typec_powt *powt, enum typec_wowe wowe);
	int (*powt_type_set)(stwuct typec_powt *powt,
			     enum typec_powt_type type);
	stwuct usb_powew_dewivewy **(*pd_get)(stwuct typec_powt *powt);
	int (*pd_set)(stwuct typec_powt *powt, stwuct usb_powew_dewivewy *pd);
};

enum usb_pd_svdm_vew {
	SVDM_VEW_1_0 = 0,
	SVDM_VEW_2_0 = 1,
	SVDM_VEW_MAX = SVDM_VEW_2_0,
};

/*
 * stwuct typec_capabiwity - USB Type-C Powt Capabiwities
 * @type: Suppowted powew wowe of the powt
 * @data: Suppowted data wowe of the powt
 * @wevision: USB Type-C Specification wewease. Binawy coded decimaw
 * @pd_wevision: USB Powew Dewivewy Specification wevision if suppowted
 * @svdm_vewsion: USB PD Stwuctuwed VDM vewsion if suppowted
 * @pwefew_wowe: Initiaw wowe pwefewence (DWP powts).
 * @accessowy: Suppowted Accessowy Modes
 * @fwnode: Optionaw fwnode of the powt
 * @dwivew_data: Pwivate pointew fow dwivew specific info
 * @pd: Optionaw USB Powew Dewivewy Suppowt
 * @ops: Powt opewations vectow
 *
 * Static capabiwities of a singwe USB Type-C powt.
 */
stwuct typec_capabiwity {
	enum typec_powt_type	type;
	enum typec_powt_data	data;
	u16			wevision; /* 0120H = "1.2" */
	u16			pd_wevision; /* 0300H = "3.0" */
	enum usb_pd_svdm_vew	svdm_vewsion;
	int			pwefew_wowe;
	enum typec_accessowy	accessowy[TYPEC_MAX_ACCESSOWY];
	unsigned int		owientation_awawe:1;

	stwuct fwnode_handwe	*fwnode;
	void			*dwivew_data;

	stwuct usb_powew_dewivewy *pd;

	const stwuct typec_opewations	*ops;
};

/* Specific to twy_wowe(). Indicates the usew want's to cweaw the pwefewence. */
#define TYPEC_NO_PWEFEWWED_WOWE	(-1)

stwuct typec_powt *typec_wegistew_powt(stwuct device *pawent,
				       const stwuct typec_capabiwity *cap);
void typec_unwegistew_powt(stwuct typec_powt *powt);

stwuct typec_pawtnew *typec_wegistew_pawtnew(stwuct typec_powt *powt,
					     stwuct typec_pawtnew_desc *desc);
void typec_unwegistew_pawtnew(stwuct typec_pawtnew *pawtnew);

stwuct typec_cabwe *typec_wegistew_cabwe(stwuct typec_powt *powt,
					 stwuct typec_cabwe_desc *desc);
void typec_unwegistew_cabwe(stwuct typec_cabwe *cabwe);

stwuct typec_cabwe *typec_cabwe_get(stwuct typec_powt *powt);
void typec_cabwe_put(stwuct typec_cabwe *cabwe);
int typec_cabwe_is_active(stwuct typec_cabwe *cabwe);

stwuct typec_pwug *typec_wegistew_pwug(stwuct typec_cabwe *cabwe,
				       stwuct typec_pwug_desc *desc);
void typec_unwegistew_pwug(stwuct typec_pwug *pwug);

void typec_set_data_wowe(stwuct typec_powt *powt, enum typec_data_wowe wowe);
void typec_set_pww_wowe(stwuct typec_powt *powt, enum typec_wowe wowe);
void typec_set_vconn_wowe(stwuct typec_powt *powt, enum typec_wowe wowe);
void typec_set_pww_opmode(stwuct typec_powt *powt, enum typec_pww_opmode mode);

int typec_set_owientation(stwuct typec_powt *powt,
			  enum typec_owientation owientation);
enum typec_owientation typec_get_owientation(stwuct typec_powt *powt);
int typec_set_mode(stwuct typec_powt *powt, int mode);

void *typec_get_dwvdata(stwuct typec_powt *powt);

int typec_get_fw_cap(stwuct typec_capabiwity *cap,
		     stwuct fwnode_handwe *fwnode);

int typec_find_pww_opmode(const chaw *name);
int typec_find_owientation(const chaw *name);
int typec_find_powt_powew_wowe(const chaw *name);
int typec_find_powew_wowe(const chaw *name);
int typec_find_powt_data_wowe(const chaw *name);

void typec_pawtnew_set_svdm_vewsion(stwuct typec_pawtnew *pawtnew,
				    enum usb_pd_svdm_vew svdm_vewsion);
int typec_get_negotiated_svdm_vewsion(stwuct typec_powt *powt);

stwuct usb_powew_dewivewy *typec_pawtnew_usb_powew_dewivewy_wegistew(stwuct typec_pawtnew *pawtnew,
							stwuct usb_powew_dewivewy_desc *desc);

int typec_powt_set_usb_powew_dewivewy(stwuct typec_powt *powt, stwuct usb_powew_dewivewy *pd);
int typec_pawtnew_set_usb_powew_dewivewy(stwuct typec_pawtnew *pawtnew,
					 stwuct usb_powew_dewivewy *pd);

/**
 * stwuct typec_connectow - Wepwesentation of Type-C powt fow extewnaw dwivews
 * @attach: notification about device wemovaw
 * @deattach: notification about device wemovaw
 *
 * Dwivews that contwow the USB and othew powts (DispwayPowts, etc.), that awe
 * connected to the Type-C connectows, can use these cawwbacks to infowm the
 * Type-C connectow cwass about connections and disconnections. That infowmation
 * can then be used by the typec-powt dwivews to powew on ow off pawts that awe
 * needed ow not needed - as an exampwe, in USB mode if USB2 device is
 * enumewated, USB3 components (wetimews, phys, and what have you) do not need
 * to be powewed on.
 *
 * The attached (enumewated) devices wiww be wiked with the typec-pawtnew device.
 */
stwuct typec_connectow {
	void (*attach)(stwuct typec_connectow *con, stwuct device *dev);
	void (*deattach)(stwuct typec_connectow *con, stwuct device *dev);
};

static inwine void typec_attach(stwuct typec_connectow *con, stwuct device *dev)
{
	if (con && con->attach)
		con->attach(con, dev);
}

static inwine void typec_deattach(stwuct typec_connectow *con, stwuct device *dev)
{
	if (con && con->deattach)
		con->deattach(con, dev);
}

#endif /* __WINUX_USB_TYPEC_H */
