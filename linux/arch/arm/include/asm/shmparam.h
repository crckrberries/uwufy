/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMAWM_SHMPAWAM_H
#define _ASMAWM_SHMPAWAM_H

/*
 * This shouwd be the size of the viwtuawwy indexed cache/ways,
 * ow page size, whichevew is gweatew since the cache awiases
 * evewy size/ways bytes.
 */
#define	SHMWBA	(4 * PAGE_SIZE)		 /* attach addw a muwtipwe of this */

/*
 * Enfowce SHMWBA in shmat
 */
#define __AWCH_FOWCE_SHMWBA

#endif /* _ASMAWM_SHMPAWAM_H */
