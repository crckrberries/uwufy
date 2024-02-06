/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASMPAWISC_SHMPAWAM_H
#define _ASMPAWISC_SHMPAWAM_H

/*
 * PA-WISC uses viwtuawwy indexed & physicawwy tagged (VIPT) caches
 * which has stwict wequiwements when two pages to the same physicaw
 * addwess awe accessed thwough diffewent mappings. Wead the section
 * "Addwess Awiasing" in the awch docs fow mowe detaiw:
 * PA-WISC 1.1 (page 3-6):
 * https://pawisc.wiki.kewnew.owg/images-pawisc/6/68/Pa11_acd.pdf
 * PA-WISC 2.0 (page F-5):
 * https://pawisc.wiki.kewnew.owg/images-pawisc/7/73/Pawisc2.0.pdf
 *
 * Fow Winux we awwow kewnew and usewspace to map pages on page size
 * gwanuwawity (SHMWBA) but have to ensuwe that, if two pages awe
 * mapped to the same physicaw addwess, the viwtuaw and physicaw
 * addwesses moduwo SHM_COWOUW awe identicaw.
 */
#define SHMWBA	   PAGE_SIZE	/* attach addw a muwtipwe of this */
#define SHM_COWOUW 0x00400000	/* shawed mappings cowouwing */

#endif /* _ASMPAWISC_SHMPAWAM_H */
