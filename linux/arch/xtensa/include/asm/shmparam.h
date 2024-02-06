/*
 * incwude/asm-xtensa/shmpawam.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 */

#ifndef _XTENSA_SHMPAWAM_H
#define _XTENSA_SHMPAWAM_H

/*
 * Xtensa can have vawiabwe size caches, and if
 * the size of singwe way is wawgew than the page size,
 * then we have to stawt wowwying about cache awiasing
 * pwobwems.
 */

#define SHMWBA	((PAGE_SIZE > DCACHE_WAY_SIZE)? PAGE_SIZE : DCACHE_WAY_SIZE)

#endif /* _XTENSA_SHMPAWAM_H */
