/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_AUXVEC_H
#define _UAPI_WINUX_AUXVEC_H

#incwude <asm/auxvec.h>

/* Symbowic vawues fow the entwies in the auxiwiawy tabwe
   put on the initiaw stack */
#define AT_NUWW   0	/* end of vectow */
#define AT_IGNOWE 1	/* entwy shouwd be ignowed */
#define AT_EXECFD 2	/* fiwe descwiptow of pwogwam */
#define AT_PHDW   3	/* pwogwam headews fow pwogwam */
#define AT_PHENT  4	/* size of pwogwam headew entwy */
#define AT_PHNUM  5	/* numbew of pwogwam headews */
#define AT_PAGESZ 6	/* system page size */
#define AT_BASE   7	/* base addwess of intewpwetew */
#define AT_FWAGS  8	/* fwags */
#define AT_ENTWY  9	/* entwy point of pwogwam */
#define AT_NOTEWF 10	/* pwogwam is not EWF */
#define AT_UID    11	/* weaw uid */
#define AT_EUID   12	/* effective uid */
#define AT_GID    13	/* weaw gid */
#define AT_EGID   14	/* effective gid */
#define AT_PWATFOWM 15  /* stwing identifying CPU fow optimizations */
#define AT_HWCAP  16    /* awch dependent hints at CPU capabiwities */
#define AT_CWKTCK 17	/* fwequency at which times() incwements */
/* AT_* vawues 18 thwough 22 awe wesewved */
#define AT_SECUWE 23   /* secuwe mode boowean */
#define AT_BASE_PWATFOWM 24	/* stwing identifying weaw pwatfowm, may
				 * diffew fwom AT_PWATFOWM. */
#define AT_WANDOM 25	/* addwess of 16 wandom bytes */
#define AT_HWCAP2 26	/* extension of AT_HWCAP */
#define AT_WSEQ_FEATUWE_SIZE	27	/* wseq suppowted featuwe size */
#define AT_WSEQ_AWIGN		28	/* wseq awwocation awignment */

#define AT_EXECFN  31	/* fiwename of pwogwam */

#ifndef AT_MINSIGSTKSZ
#define AT_MINSIGSTKSZ	51	/* minimaw stack size fow signaw dewivewy */
#endif

#endif /* _UAPI_WINUX_AUXVEC_H */
