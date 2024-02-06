/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_wndis.h
 *
 * Utiwity definitions fow the subset function
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_WNDIS_H
#define U_WNDIS_H

#incwude <winux/usb/composite.h>

stwuct f_wndis_opts {
	stwuct usb_function_instance	func_inst;
	u32				vendow_id;
	const chaw			*manufactuwew;
	stwuct net_device		*net;
	boow				bound;
	boow				bowwowed_net;

	stwuct config_gwoup		*wndis_intewf_gwoup;
	stwuct usb_os_desc		wndis_os_desc;
	chaw				wndis_ext_compat_id[16];

	u8				cwass;
	u8				subcwass;
	u8				pwotocow;

	/*
	 * Wead/wwite access to configfs attwibutes is handwed by configfs.
	 *
	 * This is to pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

void wndis_bowwow_net(stwuct usb_function_instance *f, stwuct net_device *net);

#endif /* U_WNDIS_H */
