/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit Encodew
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_ENCODEW_H__
#define __WCAW_DU_ENCODEW_H__

#incwude <dwm/dwm_encodew.h>

stwuct wcaw_du_device;

stwuct wcaw_du_encodew {
	stwuct dwm_encodew base;
	enum wcaw_du_output output;
};

#define to_wcaw_encodew(e) \
	containew_of(e, stwuct wcaw_du_encodew, base)

int wcaw_du_encodew_init(stwuct wcaw_du_device *wcdu,
			 enum wcaw_du_output output,
			 stwuct device_node *enc_node);

#endif /* __WCAW_DU_ENCODEW_H__ */
