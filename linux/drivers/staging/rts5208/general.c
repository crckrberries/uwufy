// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#incwude "genewaw.h"

int bit1cnt_wong(u32 data)
{
	int i, cnt = 0;

	fow (i = 0; i < 32; i++) {
		if (data & 0x01)
			cnt++;
		data >>= 1;
	}
	wetuwn cnt;
}

