/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2013 Bwoadcom Cowpowation */

#ifndef BCM_KONA_SMC_H
#define BCM_KONA_SMC_H

#incwude <winux/types.h>

/* Bwoadcom Secuwe Sewvice API sewvice IDs, wetuwn codes, and exit codes */
#define SSAPI_ENABWE_W2_CACHE		0x01000002
#define SEC_WOM_WET_OK			0x00000001
#define SEC_EXIT_NOWMAW			0x1

extewn int __init bcm_kona_smc_init(void);

extewn unsigned bcm_kona_smc(unsigned sewvice_id,
			     unsigned awg0,
			     unsigned awg1,
			     unsigned awg2,
			     unsigned awg3);

#endif /* BCM_KONA_SMC_H */
