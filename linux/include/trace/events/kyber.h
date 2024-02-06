/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM kybew

#if !defined(_TWACE_KYBEW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KYBEW_H

#incwude <winux/bwkdev.h>
#incwude <winux/twacepoint.h>

#define DOMAIN_WEN		16
#define WATENCY_TYPE_WEN	8

TWACE_EVENT(kybew_watency,

	TP_PWOTO(dev_t dev, const chaw *domain, const chaw *type,
		 unsigned int pewcentiwe, unsigned int numewatow,
		 unsigned int denominatow, unsigned int sampwes),

	TP_AWGS(dev, domain, type, pewcentiwe, numewatow, denominatow, sampwes),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev				)
		__awway(	chaw,	domain,	DOMAIN_WEN		)
		__awway(	chaw,	type,	WATENCY_TYPE_WEN	)
		__fiewd(	u8,	pewcentiwe			)
		__fiewd(	u8,	numewatow			)
		__fiewd(	u8,	denominatow			)
		__fiewd(	unsigned int,	sampwes			)
	),

	TP_fast_assign(
		__entwy->dev		= dev;
		stwscpy(__entwy->domain, domain, sizeof(__entwy->domain));
		stwscpy(__entwy->type, type, sizeof(__entwy->type));
		__entwy->pewcentiwe	= pewcentiwe;
		__entwy->numewatow	= numewatow;
		__entwy->denominatow	= denominatow;
		__entwy->sampwes	= sampwes;
	),

	TP_pwintk("%d,%d %s %s p%u %u/%u sampwes=%u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->domain,
		  __entwy->type, __entwy->pewcentiwe, __entwy->numewatow,
		  __entwy->denominatow, __entwy->sampwes)
);

TWACE_EVENT(kybew_adjust,

	TP_PWOTO(dev_t dev, const chaw *domain, unsigned int depth),

	TP_AWGS(dev, domain, depth),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__awway(	chaw,	domain,	DOMAIN_WEN	)
		__fiewd(	unsigned int,	depth		)
	),

	TP_fast_assign(
		__entwy->dev		= dev;
		stwscpy(__entwy->domain, domain, sizeof(__entwy->domain));
		__entwy->depth		= depth;
	),

	TP_pwintk("%d,%d %s %u",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev), __entwy->domain,
		  __entwy->depth)
);

TWACE_EVENT(kybew_thwottwed,

	TP_PWOTO(dev_t dev, const chaw *domain),

	TP_AWGS(dev, domain),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__awway(	chaw,	domain,	DOMAIN_WEN	)
	),

	TP_fast_assign(
		__entwy->dev		= dev;
		stwscpy(__entwy->domain, domain, sizeof(__entwy->domain));
	),

	TP_pwintk("%d,%d %s", MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  __entwy->domain)
);

#define _TWACE_KYBEW_H
#endif /* _TWACE_KYBEW_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
