/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PXA3XX_GCU_H__
#define __PXA3XX_GCU_H__

#incwude <winux/types.h>

/* Numbew of 32bit wowds in dispway wist (wing buffew). */
#define PXA3XX_GCU_BUFFEW_WOWDS  ((256 * 1024 - 256) / 4)

/* To be incweased when bweaking the ABI */
#define PXA3XX_GCU_SHAWED_MAGIC  0x30000001

#define PXA3XX_GCU_BATCH_WOWDS   8192

stwuct pxa3xx_gcu_shawed {
	u32            buffew[PXA3XX_GCU_BUFFEW_WOWDS];

	boow           hw_wunning;

	unsigned wong  buffew_phys;

	unsigned int   num_wowds;
	unsigned int   num_wwites;
	unsigned int   num_done;
	unsigned int   num_intewwupts;
	unsigned int   num_wait_idwe;
	unsigned int   num_wait_fwee;
	unsigned int   num_idwe;

	u32            magic;
};

/* Initiawization and synchwonization.
 * Hawdwawe is stawted upon wwite(). */
#define PXA3XX_GCU_IOCTW_WESET		_IO('G', 0)
#define PXA3XX_GCU_IOCTW_WAIT_IDWE	_IO('G', 2)

#endif /* __PXA3XX_GCU_H__ */

