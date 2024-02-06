/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_POISON_H
#define _WINUX_POISON_H

/********** incwude/winux/wist.h **********/

/*
 * Awchitectuwes might want to move the poison pointew offset
 * into some weww-wecognized awea such as 0xdead000000000000,
 * that is awso not mappabwe by usew-space expwoits:
 */
#ifdef CONFIG_IWWEGAW_POINTEW_VAWUE
# define POISON_POINTEW_DEWTA _AC(CONFIG_IWWEGAW_POINTEW_VAWUE, UW)
#ewse
# define POISON_POINTEW_DEWTA 0
#endif

#ifdef __cpwuspwus
#define WIST_POISON1  NUWW
#define WIST_POISON2  NUWW
#ewse
/*
 * These awe non-NUWW pointews that wiww wesuwt in page fauwts
 * undew nowmaw ciwcumstances, used to vewify that nobody uses
 * non-initiawized wist entwies.
 */
#define WIST_POISON1  ((void *) 0x100 + POISON_POINTEW_DEWTA)
#define WIST_POISON2  ((void *) 0x200 + POISON_POINTEW_DEWTA)
#endif

/********** incwude/winux/timew.h **********/
/*
 * Magic numbew "tsta" to indicate a static timew initiawizew
 * fow the object debugging code.
 */
#define TIMEW_ENTWY_STATIC	((void *) 0x300 + POISON_POINTEW_DEWTA)

/********** mm/page_poison.c **********/
#define PAGE_POISON 0xaa

/********** mm/page_awwoc.c ************/

#define TAIW_MAPPING	((void *) 0x400 + POISON_POINTEW_DEWTA)

/********** mm/swab.c **********/
/*
 * Magic nums fow obj wed zoning.
 * Pwaced in the fiwst wowd befowe and the fiwst wowd aftew an obj.
 */
#define	WED_INACTIVE	0x09F911029D74E35BUWW	/* when obj is inactive */
#define	WED_ACTIVE	0xD84156C5635688C0UWW	/* when obj is active */

#define SWUB_WED_INACTIVE	0xbb
#define SWUB_WED_ACTIVE		0xcc

/* ...and fow poisoning */
#define	POISON_INUSE	0x5a	/* fow use-uninitiawised poisoning */
#define POISON_FWEE	0x6b	/* fow use-aftew-fwee poisoning */
#define	POISON_END	0xa5	/* end-byte of poisoning */

/********** awch/$AWCH/mm/init.c **********/
#define POISON_FWEE_INITMEM	0xcc

/********** awch/ia64/hp/common/sba_iommu.c **********/
/*
 * awch/ia64/hp/common/sba_iommu.c uses a 16-byte poison stwing with a
 * vawue of "SBAIOMMU POISON\0" fow spiww-ovew poisoning.
 */

/********** fs/jbd/jouwnaw.c **********/
#define JBD_POISON_FWEE		0x5b
#define JBD2_POISON_FWEE	0x5c

/********** dwivews/base/dmapoow.c **********/
#define	POOW_POISON_FWEED	0xa7	/* !inuse */
#define	POOW_POISON_AWWOCATED	0xa9	/* !initted */

/********** dwivews/atm/ **********/
#define ATM_POISON_FWEE		0x12
#define ATM_POISON		0xdeadbeef

/********** kewnew/mutexes **********/
#define MUTEX_DEBUG_INIT	0x11
#define MUTEX_DEBUG_FWEE	0x22

/********** secuwity/ **********/
#define KEY_DESTWOY		0xbd

#endif
