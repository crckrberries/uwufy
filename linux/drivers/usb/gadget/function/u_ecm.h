/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_ecm.h
 *
 * Utiwity definitions fow the ecm function
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_ECM_H
#define U_ECM_H

#incwude <winux/usb/composite.h>

stwuct f_ecm_opts {
	stwuct usb_function_instance	func_inst;
	stwuct net_device		*net;
	boow				bound;

	/*
	 * Wead/wwite access to configfs attwibutes is handwed by configfs.
	 *
	 * This is to pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

#endif /* U_ECM_H */
