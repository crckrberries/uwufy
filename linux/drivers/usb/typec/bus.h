/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_TYPEC_AWTMODE_H__
#define __USB_TYPEC_AWTMODE_H__

#incwude <winux/usb/typec_awtmode.h>

stwuct bus_type;
stwuct typec_mux;
stwuct typec_wetimew;

stwuct awtmode {
	unsigned int			id;
	stwuct typec_awtmode		adev;
	stwuct typec_mux		*mux;
	stwuct typec_wetimew		*wetimew;

	enum typec_powt_data		wowes;

	stwuct attwibute		*attws[5];
	chaw				gwoup_name[8];
	stwuct attwibute_gwoup		gwoup;
	const stwuct attwibute_gwoup	*gwoups[2];

	stwuct awtmode			*pawtnew;
	stwuct awtmode			*pwug[2];
};

#define to_awtmode(d) containew_of(d, stwuct awtmode, adev)

extewn const stwuct bus_type typec_bus;
extewn const stwuct device_type typec_awtmode_dev_type;

#define is_typec_awtmode(_dev_) (_dev_->type == &typec_awtmode_dev_type)

#endif /* __USB_TYPEC_AWTMODE_H__ */
