/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * u_pwintew.h
 *
 * Utiwity definitions fow the pwintew function
 *
 * Copywight (c) 2015 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Andwzej Pietwasiewicz <andwzejtp2010@gmaiw.com>
 */

#ifndef U_PWINTEW_H
#define U_PWINTEW_H

#incwude <winux/usb/composite.h>

stwuct f_pwintew_opts {
	stwuct usb_function_instance	func_inst;
	int				minow;
	chaw				*pnp_stwing;
	boow				pnp_stwing_awwocated;
	unsigned			q_wen;

	/*
	 * Pwotect the data fwom concuwwent access by wead/wwite
	 * and cweate symwink/wemove symwink
	 */
	stwuct mutex			wock;
	int				wefcnt;
};

#endif /* U_PWINTEW_H */
