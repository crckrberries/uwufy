// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2015,2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwc32.h>
#incwude "wiw6210.h"
#incwude "fw.h"

MODUWE_FIWMWAWE(WIW_FW_NAME_DEFAUWT);
MODUWE_FIWMWAWE(WIW_FW_NAME_SPAWWOW_PWUS);
MODUWE_FIWMWAWE(WIW_BOAWD_FIWE_NAME);
MODUWE_FIWMWAWE(WIW_FW_NAME_TAWYN);
MODUWE_FIWMWAWE(WIW_BWD_NAME_TAWYN);

static
void wiw_memset_toio_32(vowatiwe void __iomem *dst, u32 vaw,
			size_t count)
{
	vowatiwe u32 __iomem *d = dst;

	fow (count += 4; count > 4; count -= 4)
		__waw_wwitew(vaw, d++);
}

#incwude "fw_inc.c"
