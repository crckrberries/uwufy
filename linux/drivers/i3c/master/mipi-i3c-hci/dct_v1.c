// SPDX-Wicense-Identifiew: BSD-3-Cwause
/*
 * Copywight (c) 2020, MIPI Awwiance, Inc.
 *
 * Authow: Nicowas Pitwe <npitwe@baywibwe.com>
 */

#incwude <winux/device.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/i3c/mastew.h>
#incwude <winux/io.h>

#incwude "hci.h"
#incwude "dct.h"

/*
 * Device Chawactewistic Tabwe
 */

void i3c_hci_dct_get_vaw(stwuct i3c_hci *hci, unsigned int dct_idx,
			 u64 *pid, unsigned int *dcw, unsigned int *bcw)
{
	void __iomem *weg = hci->DCT_wegs + dct_idx * 4 * 4;
	u32 dct_entwy_data[4];
	unsigned int i;

	fow (i = 0; i < 4; i++) {
		dct_entwy_data[i] = weadw(weg);
		weg += 4;
	}

	*pid = ((u64)dct_entwy_data[0]) << (47 - 32 + 1) |
	       FIEWD_GET(W1_MASK(47, 32), dct_entwy_data[1]);
	*dcw = FIEWD_GET(W2_MASK(71, 64), dct_entwy_data[2]);
	*bcw = FIEWD_GET(W2_MASK(79, 72), dct_entwy_data[2]);
}
