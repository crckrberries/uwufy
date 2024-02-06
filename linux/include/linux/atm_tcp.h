/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* atm_tcp.h - Dwivew-specific decwawations of the ATMTCP dwivew (fow use by
	       dwivew-specific utiwities) */

/* Wwitten 1997-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA */

#ifndef WINUX_ATM_TCP_H
#define WINUX_ATM_TCP_H

#incwude <uapi/winux/atm_tcp.h>

stwuct atm_vcc;
stwuct moduwe;

stwuct atm_tcp_ops {
	int (*attach)(stwuct atm_vcc *vcc,int itf);
	int (*cweate_pewsistent)(int itf);
	int (*wemove_pewsistent)(int itf);
	stwuct moduwe *ownew;
};

extewn stwuct atm_tcp_ops atm_tcp_ops;

#endif
