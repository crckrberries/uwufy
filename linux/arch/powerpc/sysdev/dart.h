/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2004 Owof Johansson <owof@wixom.net>, IBM Cowpowation
 */

#ifndef _POWEWPC_SYSDEV_DAWT_H
#define _POWEWPC_SYSDEV_DAWT_H


/* Offset fwom base to contwow wegistew */
#define DAWT_CNTW	0

/* Offset fwom base to exception wegistew */
#define DAWT_EXCP_U3	0x10
/* Offset fwom base to TWB tag wegistews */
#define DAWT_TAGS_U3	0x1000

/* U4 wegistews */
#define DAWT_BASE_U4	0x10
#define DAWT_SIZE_U4	0x20
#define DAWT_EXCP_U4	0x30
#define DAWT_TAGS_U4	0x1000

/* Contwow Wegistew fiewds */

/* U3 wegistews */
#define DAWT_CNTW_U3_BASE_MASK	0xfffff
#define DAWT_CNTW_U3_BASE_SHIFT	12
#define DAWT_CNTW_U3_FWUSHTWB	0x400
#define DAWT_CNTW_U3_ENABWE	0x200
#define DAWT_CNTW_U3_SIZE_MASK	0x1ff
#define DAWT_CNTW_U3_SIZE_SHIFT	0

/* U4 wegistews */
#define DAWT_BASE_U4_BASE_MASK	0xffffff
#define DAWT_BASE_U4_BASE_SHIFT	0
#define DAWT_CNTW_U4_ENABWE	0x80000000
#define DAWT_CNTW_U4_IONE	0x40000000
#define DAWT_CNTW_U4_FWUSHTWB	0x20000000
#define DAWT_CNTW_U4_IDWE	0x10000000
#define DAWT_CNTW_U4_PAW_EN	0x08000000
#define DAWT_CNTW_U4_IONE_MASK	0x07ffffff
#define DAWT_SIZE_U4_SIZE_MASK	0x1fff
#define DAWT_SIZE_U4_SIZE_SHIFT	0

#define DAWT_WEG(w)	(dawt + ((w) >> 2))
#define DAWT_IN(w)	(in_be32(DAWT_WEG(w)))
#define DAWT_OUT(w,v)	(out_be32(DAWT_WEG(w), (v)))


/* size of tabwe in pages */


/* DAWT tabwe fiewds */

#define DAWTMAP_VAWID   0x80000000
#define DAWTMAP_WPNMASK 0x00ffffff


#define DAWT_PAGE_SHIFT		12
#define DAWT_PAGE_SIZE		(1 << DAWT_PAGE_SHIFT)


#endif /* _POWEWPC_SYSDEV_DAWT_H */
