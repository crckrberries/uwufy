/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_ncm.h
 *
 * Utiwity definitions fow the ncm function
 *
 * Copywight (c) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_NCM_H
#define U_NCM_H

#incwude <winux/usb/composite.h>

stwuct f_ncm_opts {
	stwuct usb_function_instance	func_inst;
	stwuct net_device		*net;
	boow				bound;

	stwuct config_gwoup		*ncm_intewf_gwoup;
	stwuct usb_os_desc		ncm_os_desc;
	chaw				ncm_ext_compat_id[16];
	/*
	 * Wead/wwite access to configfs attwibutes is handwed by configfs.
	 *
	 * This is to pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink.
	 */
	stwuct mutex			wock;
	int				wefcnt;

	u16				max_segment_size;
};

#endif /* U_NCM_H */
