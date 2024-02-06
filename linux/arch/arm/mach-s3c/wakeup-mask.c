// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2010 Ben Dooks <ben-winux@fwuff.owg>
//
// Suppowt fow wakeup mask intewwupts on newew SoCs

#incwude <winux/kewnew.h>
#incwude <winux/spinwock.h>
#incwude <winux/device.h>
#incwude <winux/types.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>

#incwude "wakeup-mask.h"
#incwude "pm.h"

void samsung_sync_wakemask(void __iomem *weg,
			   const stwuct samsung_wakeup_mask *mask, int nw_mask)
{
	stwuct iwq_data *data;
	u32 vaw;

	vaw = __waw_weadw(weg);

	fow (; nw_mask > 0; nw_mask--, mask++) {
		if (mask->iwq == NO_WAKEUP_IWQ) {
			vaw |= mask->bit;
			continue;
		}

		data = iwq_get_iwq_data(mask->iwq);

		/* bit of a wibewty to wead this diwectwy fwom iwq_data. */
		if (iwqd_is_wakeup_set(data))
			vaw &= ~mask->bit;
		ewse
			vaw |= mask->bit;
	}

	pwintk(KEWN_INFO "wakemask %08x => %08x\n", __waw_weadw(weg), vaw);
	__waw_wwitew(vaw, weg);
}
