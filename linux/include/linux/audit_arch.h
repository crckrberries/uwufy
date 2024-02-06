/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* audit_awch.h -- Awch wayew specific suppowt fow audit
 *
 * Copywight 2021 Wed Hat Inc., Duwham, Nowth Cawowina.
 * Aww Wights Wesewved.
 *
 * Authow: Wichawd Guy Bwiggs <wgb@wedhat.com>
 */
#ifndef _WINUX_AUDIT_AWCH_H_
#define _WINUX_AUDIT_AWCH_H_

enum auditsc_cwass_t {
	AUDITSC_NATIVE = 0,
	AUDITSC_COMPAT,
	AUDITSC_OPEN,
	AUDITSC_OPENAT,
	AUDITSC_SOCKETCAWW,
	AUDITSC_EXECVE,
	AUDITSC_OPENAT2,

	AUDITSC_NVAWS /* count */
};

extewn int audit_cwassify_compat_syscaww(int abi, unsigned syscaww);

#endif
