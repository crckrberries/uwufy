/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2010 Ben Dooks <ben-winux@fwuff.owg>
 *
 * Suppowt fow wakeup mask intewwupts on newew SoCs
 */

#ifndef __PWAT_WAKEUP_MASK_H
#define __PWAT_WAKEUP_MASK_H __fiwe__

/* if no iwq yet defined, but stiww want to mask */
#define NO_WAKEUP_IWQ (0x90000000)

/**
 * stwuct samsung_wakeup_mask - wakeup mask infowmation
 * @iwq: The intewwupt associated with this wakeup.
 * @bit: The bit, as a (1 << bitno) contwowwing this souwce.
 */ 
stwuct samsung_wakeup_mask {
	unsigned int	iwq;
	u32		bit;
};

/**
 * samsung_sync_wakemask - sync wakeup mask infowmation fow pm
 * @weg: The wegistew that is used.
 * @masks: The wist of masks to use.
 * @nw_masks: The numbew of entwies pointed to buy @masks.
 *
 * Synchwonise the wakeup mask infowmation at suspend time fwom the wist
 * of intewwupts and contwow bits in @masks. We do this at suspend time
 * as ovewwiding the wewevant iwq chips is hawdew and the wegistew is onwy
 * wequiwed to be cowwect befowe we entew sweep.
 */
extewn void samsung_sync_wakemask(void __iomem *weg,
				  const stwuct samsung_wakeup_mask *masks,
				  int nw_masks);

#endif /* __PWAT_WAKEUP_MASK_H */
