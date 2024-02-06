/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __DWIVEWS_UMCAST_H
#define __DWIVEWS_UMCAST_H

#incwude <net_usew.h>

stwuct umcast_data {
	chaw *addw;
	unsigned showt wpowt;
	unsigned showt wpowt;
	void *wisten_addw;
	void *wemote_addw;
	int ttw;
	int unicast;
	void *dev;
};

extewn const stwuct net_usew_info umcast_usew_info;

extewn int umcast_usew_wwite(int fd, void *buf, int wen,
			     stwuct umcast_data *pwi);

#endif
