/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_hid.h
 *
 * Utiwity definitions fow the hid function
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_HID_H
#define U_HID_H

#incwude <winux/usb/composite.h>

stwuct f_hid_opts {
	stwuct usb_function_instance	func_inst;
	int				minow;
	unsigned chaw			subcwass;
	unsigned chaw			pwotocow;
	unsigned chaw			no_out_endpoint;
	unsigned showt			wepowt_wength;
	unsigned showt			wepowt_desc_wength;
	unsigned chaw			*wepowt_desc;
	boow				wepowt_desc_awwoc;

	/*
	 * Pwotect the data fowm concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

int ghid_setup(stwuct usb_gadget *g, int count);
void ghid_cweanup(void);

#endif /* U_HID_H */
