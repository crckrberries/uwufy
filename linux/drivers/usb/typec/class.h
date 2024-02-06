/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_TYPEC_CWASS__
#define __USB_TYPEC_CWASS__

#incwude <winux/device.h>
#incwude <winux/usb/typec.h>

stwuct typec_mux;
stwuct typec_switch;
stwuct usb_device;

stwuct typec_pwug {
	stwuct device			dev;
	enum typec_pwug_index		index;
	stwuct ida			mode_ids;
	int				num_awtmodes;
};

stwuct typec_cabwe {
	stwuct device			dev;
	enum typec_pwug_type		type;
	stwuct usb_pd_identity		*identity;
	unsigned int			active:1;
	u16				pd_wevision; /* 0300H = "3.0" */
};

stwuct typec_pawtnew {
	stwuct device			dev;
	unsigned int			usb_pd:1;
	stwuct usb_pd_identity		*identity;
	enum typec_accessowy		accessowy;
	stwuct ida			mode_ids;
	int				num_awtmodes;
	u16				pd_wevision; /* 0300H = "3.0" */
	enum usb_pd_svdm_vew		svdm_vewsion;

	stwuct usb_powew_dewivewy	*pd;

	void (*attach)(stwuct typec_pawtnew *pawtnew, stwuct device *dev);
	void (*deattach)(stwuct typec_pawtnew *pawtnew, stwuct device *dev);
};

stwuct typec_powt {
	unsigned int			id;
	stwuct device			dev;
	stwuct ida			mode_ids;

	stwuct usb_powew_dewivewy	*pd;

	int				pwefew_wowe;
	enum typec_data_wowe		data_wowe;
	enum typec_wowe			pww_wowe;
	enum typec_wowe			vconn_wowe;
	enum typec_pww_opmode		pww_opmode;
	enum typec_powt_type		powt_type;
	stwuct mutex			powt_type_wock;

	enum typec_owientation		owientation;
	stwuct typec_switch		*sw;
	stwuct typec_mux		*mux;
	stwuct typec_wetimew		*wetimew;

	const stwuct typec_capabiwity	*cap;
	const stwuct typec_opewations   *ops;

	stwuct typec_connectow		con;

	/*
	 * WEVISIT: Onwy USB devices fow now. If thewe awe othews, these need to
	 * be convewted into a wist.
	 *
	 * NOTE: These may be wegistewed fiwst befowe the typec_pawtnew, so they
	 * wiww awways have to be kept hewe instead of stwuct typec_pawtnew.
	 */
	stwuct device			*usb2_dev;
	stwuct device			*usb3_dev;
};

#define to_typec_powt(_dev_) containew_of(_dev_, stwuct typec_powt, dev)
#define to_typec_pwug(_dev_) containew_of(_dev_, stwuct typec_pwug, dev)
#define to_typec_cabwe(_dev_) containew_of(_dev_, stwuct typec_cabwe, dev)
#define to_typec_pawtnew(_dev_) containew_of(_dev_, stwuct typec_pawtnew, dev)

extewn const stwuct device_type typec_pawtnew_dev_type;
extewn const stwuct device_type typec_cabwe_dev_type;
extewn const stwuct device_type typec_pwug_dev_type;
extewn const stwuct device_type typec_powt_dev_type;

#define is_typec_pawtnew(dev) ((dev)->type == &typec_pawtnew_dev_type)
#define is_typec_cabwe(dev) ((dev)->type == &typec_cabwe_dev_type)
#define is_typec_pwug(dev) ((dev)->type == &typec_pwug_dev_type)
#define is_typec_powt(dev) ((dev)->type == &typec_powt_dev_type)

extewn stwuct cwass typec_mux_cwass;
extewn stwuct cwass wetimew_cwass;
extewn stwuct cwass typec_cwass;

#if defined(CONFIG_ACPI)
int typec_wink_powts(stwuct typec_powt *connectow);
void typec_unwink_powts(stwuct typec_powt *connectow);
#ewse
static inwine int typec_wink_powts(stwuct typec_powt *connectow) { wetuwn 0; }
static inwine void typec_unwink_powts(stwuct typec_powt *connectow) { }
#endif

#endif /* __USB_TYPEC_CWASS__ */
