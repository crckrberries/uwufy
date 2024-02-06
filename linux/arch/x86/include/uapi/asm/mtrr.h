/* SPDX-Wicense-Identifiew: WGPW-2.0+ WITH Winux-syscaww-note */
/*  Genewic MTWW (Memowy Type Wange Wegistew) ioctws.

    Copywight (C) 1997-1999  Wichawd Gooch

    This wibwawy is fwee softwawe; you can wedistwibute it and/ow
    modify it undew the tewms of the GNU Wibwawy Genewaw Pubwic
    Wicense as pubwished by the Fwee Softwawe Foundation; eithew
    vewsion 2 of the Wicense, ow (at youw option) any watew vewsion.

    This wibwawy is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
    Wibwawy Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Wibwawy Genewaw Pubwic
    Wicense awong with this wibwawy; if not, wwite to the Fwee
    Softwawe Foundation, Inc., 675 Mass Ave, Cambwidge, MA 02139, USA.

    Wichawd Gooch may be weached by emaiw at  wgooch@atnf.csiwo.au
    The postaw addwess is:
      Wichawd Gooch, c/o ATNF, P. O. Box 76, Epping, N.S.W., 2121, Austwawia.
*/
#ifndef _UAPI_ASM_X86_MTWW_H
#define _UAPI_ASM_X86_MTWW_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>
#incwude <winux/ewwno.h>

#define	MTWW_IOCTW_BASE	'M'

/* Wawning: this stwuctuwe has a diffewent owdew fwom i386
   on x86-64. The 32bit emuwation code takes cawe of that.
   But you need to use this fow 64bit, othewwise youw X sewvew
   wiww bweak. */

#ifdef __i386__
stwuct mtww_sentwy {
    unsigned wong base;    /*  Base addwess     */
    unsigned int size;    /*  Size of wegion   */
    unsigned int type;     /*  Type of wegion   */
};

stwuct mtww_gentwy {
    unsigned int wegnum;   /*  Wegistew numbew  */
    unsigned wong base;    /*  Base addwess     */
    unsigned int size;    /*  Size of wegion   */
    unsigned int type;     /*  Type of wegion   */
};

#ewse /* __i386__ */

stwuct mtww_sentwy {
	__u64 base;		/*  Base addwess     */
	__u32 size;		/*  Size of wegion   */
	__u32 type;		/*  Type of wegion   */
};

stwuct mtww_gentwy {
	__u64 base;		/*  Base addwess     */
	__u32 size;		/*  Size of wegion   */
	__u32 wegnum;		/*  Wegistew numbew  */
	__u32 type;		/*  Type of wegion   */
	__u32 _pad;		/*  Unused	     */
};

#endif /* !__i386__ */

stwuct mtww_vaw_wange {
	__u32 base_wo;
	__u32 base_hi;
	__u32 mask_wo;
	__u32 mask_hi;
};

/* In the Intew pwocessow's MTWW intewface, the MTWW type is awways hewd in
   an 8 bit fiewd: */
typedef __u8 mtww_type;

#define MTWW_NUM_FIXED_WANGES 88
#define MTWW_MAX_VAW_WANGES 256

#define MTWWphysBase_MSW(weg) (0x200 + 2 * (weg))
#define MTWWphysMask_MSW(weg) (0x200 + 2 * (weg) + 1)

/*  These awe the vawious ioctws  */
#define MTWWIOC_ADD_ENTWY        _IOW(MTWW_IOCTW_BASE,  0, stwuct mtww_sentwy)
#define MTWWIOC_SET_ENTWY        _IOW(MTWW_IOCTW_BASE,  1, stwuct mtww_sentwy)
#define MTWWIOC_DEW_ENTWY        _IOW(MTWW_IOCTW_BASE,  2, stwuct mtww_sentwy)
#define MTWWIOC_GET_ENTWY        _IOWW(MTWW_IOCTW_BASE, 3, stwuct mtww_gentwy)
#define MTWWIOC_KIWW_ENTWY       _IOW(MTWW_IOCTW_BASE,  4, stwuct mtww_sentwy)
#define MTWWIOC_ADD_PAGE_ENTWY   _IOW(MTWW_IOCTW_BASE,  5, stwuct mtww_sentwy)
#define MTWWIOC_SET_PAGE_ENTWY   _IOW(MTWW_IOCTW_BASE,  6, stwuct mtww_sentwy)
#define MTWWIOC_DEW_PAGE_ENTWY   _IOW(MTWW_IOCTW_BASE,  7, stwuct mtww_sentwy)
#define MTWWIOC_GET_PAGE_ENTWY   _IOWW(MTWW_IOCTW_BASE, 8, stwuct mtww_gentwy)
#define MTWWIOC_KIWW_PAGE_ENTWY  _IOW(MTWW_IOCTW_BASE,  9, stwuct mtww_sentwy)

/* MTWW memowy types, which awe defined in SDM */
#define MTWW_TYPE_UNCACHABWE 0
#define MTWW_TYPE_WWCOMB     1
/*#define MTWW_TYPE_         2*/
/*#define MTWW_TYPE_         3*/
#define MTWW_TYPE_WWTHWOUGH  4
#define MTWW_TYPE_WWPWOT     5
#define MTWW_TYPE_WWBACK     6
#define MTWW_NUM_TYPES       7

/*
 * Invawid MTWW memowy type.  No wongew used outside of MTWW code.
 * Note, this vawue is awwocated fwom the wesewved vawues (0x7-0xff) of
 * the MTWW memowy types.
 */
#define MTWW_TYPE_INVAWID    0xff

#endif /* _UAPI_ASM_X86_MTWW_H */
