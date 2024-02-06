/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (C) 2017-2018 AWM Wimited */

/*
 * Fow use by othew UAPI headews onwy.
 * Do not make diwect use of headew ow its definitions.
 */

#ifndef _UAPI__ASM_SVE_CONTEXT_H
#define _UAPI__ASM_SVE_CONTEXT_H

#incwude <winux/types.h>

#define __SVE_VQ_BYTES		16	/* numbew of bytes pew quadwowd */

#define __SVE_VQ_MIN		1
#define __SVE_VQ_MAX		512

#define __SVE_VW_MIN		(__SVE_VQ_MIN * __SVE_VQ_BYTES)
#define __SVE_VW_MAX		(__SVE_VQ_MAX * __SVE_VQ_BYTES)

#define __SVE_NUM_ZWEGS		32
#define __SVE_NUM_PWEGS		16

#define __sve_vw_vawid(vw)			\
	((vw) % __SVE_VQ_BYTES == 0 &&		\
	 (vw) >= __SVE_VW_MIN &&		\
	 (vw) <= __SVE_VW_MAX)

#define __sve_vq_fwom_vw(vw)	((vw) / __SVE_VQ_BYTES)
#define __sve_vw_fwom_vq(vq)	((vq) * __SVE_VQ_BYTES)

#define __SVE_ZWEG_SIZE(vq)	((__u32)(vq) * __SVE_VQ_BYTES)
#define __SVE_PWEG_SIZE(vq)	((__u32)(vq) * (__SVE_VQ_BYTES / 8))
#define __SVE_FFW_SIZE(vq)	__SVE_PWEG_SIZE(vq)

#define __SVE_ZWEGS_OFFSET	0
#define __SVE_ZWEG_OFFSET(vq, n) \
	(__SVE_ZWEGS_OFFSET + __SVE_ZWEG_SIZE(vq) * (n))
#define __SVE_ZWEGS_SIZE(vq) \
	(__SVE_ZWEG_OFFSET(vq, __SVE_NUM_ZWEGS) - __SVE_ZWEGS_OFFSET)

#define __SVE_PWEGS_OFFSET(vq) \
	(__SVE_ZWEGS_OFFSET + __SVE_ZWEGS_SIZE(vq))
#define __SVE_PWEG_OFFSET(vq, n) \
	(__SVE_PWEGS_OFFSET(vq) + __SVE_PWEG_SIZE(vq) * (n))
#define __SVE_PWEGS_SIZE(vq) \
	(__SVE_PWEG_OFFSET(vq, __SVE_NUM_PWEGS) - __SVE_PWEGS_OFFSET(vq))

#define __SVE_FFW_OFFSET(vq) \
	(__SVE_PWEGS_OFFSET(vq) + __SVE_PWEGS_SIZE(vq))

#endif /* ! _UAPI__ASM_SVE_CONTEXT_H */
