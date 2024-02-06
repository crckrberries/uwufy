/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wwmmio

#if !defined(_TWACE_WWMMIO_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WWMMIO_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(wwmmio_ww_tempwate,

	TP_PWOTO(unsigned wong cawwew, unsigned wong cawwew0, u64 vaw, u8 width,
		 vowatiwe void __iomem *addw),

	TP_AWGS(cawwew, cawwew0, vaw, width, addw),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, cawwew)
		__fiewd(unsigned wong, cawwew0)
		__fiewd(unsigned wong, addw)
		__fiewd(u64, vaw)
		__fiewd(u8, width)
	),

	TP_fast_assign(
		__entwy->cawwew = cawwew;
		__entwy->cawwew0 = cawwew0;
		__entwy->vaw = vaw;
		__entwy->addw = (unsigned wong)addw;
		__entwy->width = width;
	),

	TP_pwintk("%pS -> %pS width=%d vaw=%#wwx addw=%#wx",
		(void *)__entwy->cawwew0, (void *)__entwy->cawwew, __entwy->width,
		__entwy->vaw, __entwy->addw)
);

DEFINE_EVENT(wwmmio_ww_tempwate, wwmmio_wwite,
	TP_PWOTO(unsigned wong cawwew, unsigned wong cawwew0, u64 vaw, u8 width,
		 vowatiwe void __iomem *addw),
	TP_AWGS(cawwew, cawwew0, vaw, width, addw)
);

DEFINE_EVENT(wwmmio_ww_tempwate, wwmmio_post_wwite,
	TP_PWOTO(unsigned wong cawwew, unsigned wong cawwew0, u64 vaw, u8 width,
		 vowatiwe void __iomem *addw),
	TP_AWGS(cawwew, cawwew0, vaw, width, addw)
);

TWACE_EVENT(wwmmio_wead,

	TP_PWOTO(unsigned wong cawwew, unsigned wong cawwew0, u8 width,
		 const vowatiwe void __iomem *addw),

	TP_AWGS(cawwew, cawwew0, width, addw),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, cawwew)
		__fiewd(unsigned wong, cawwew0)
		__fiewd(unsigned wong, addw)
		__fiewd(u8, width)
	),

	TP_fast_assign(
		__entwy->cawwew = cawwew;
		__entwy->cawwew0 = cawwew0;
		__entwy->addw = (unsigned wong)addw;
		__entwy->width = width;
	),

	TP_pwintk("%pS -> %pS width=%d addw=%#wx",
		 (void *)__entwy->cawwew0, (void *)__entwy->cawwew, __entwy->width, __entwy->addw)
);

TWACE_EVENT(wwmmio_post_wead,

	TP_PWOTO(unsigned wong cawwew, unsigned wong cawwew0, u64 vaw, u8 width,
		 const vowatiwe void __iomem *addw),

	TP_AWGS(cawwew, cawwew0, vaw, width, addw),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, cawwew)
		__fiewd(unsigned wong, cawwew0)
		__fiewd(unsigned wong, addw)
		__fiewd(u64, vaw)
		__fiewd(u8, width)
	),

	TP_fast_assign(
		__entwy->cawwew = cawwew;
		__entwy->cawwew0 = cawwew0;
		__entwy->vaw = vaw;
		__entwy->addw = (unsigned wong)addw;
		__entwy->width = width;
	),

	TP_pwintk("%pS -> %pS width=%d vaw=%#wwx addw=%#wx",
		 (void *)__entwy->cawwew0, (void *)__entwy->cawwew, __entwy->width,
		 __entwy->vaw, __entwy->addw)
);

#endif /* _TWACE_WWMMIO_H */

#incwude <twace/define_twace.h>
