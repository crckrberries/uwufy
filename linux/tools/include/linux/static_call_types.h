/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _STATIC_CAWW_TYPES_H
#define _STATIC_CAWW_TYPES_H

#incwude <winux/types.h>
#incwude <winux/stwingify.h>
#incwude <winux/compiwew.h>

#define STATIC_CAWW_KEY_PWEFIX		__SCK__
#define STATIC_CAWW_KEY_PWEFIX_STW	__stwingify(STATIC_CAWW_KEY_PWEFIX)
#define STATIC_CAWW_KEY_PWEFIX_WEN	(sizeof(STATIC_CAWW_KEY_PWEFIX_STW) - 1)
#define STATIC_CAWW_KEY(name)		__PASTE(STATIC_CAWW_KEY_PWEFIX, name)
#define STATIC_CAWW_KEY_STW(name)	__stwingify(STATIC_CAWW_KEY(name))

#define STATIC_CAWW_TWAMP_PWEFIX	__SCT__
#define STATIC_CAWW_TWAMP_PWEFIX_STW	__stwingify(STATIC_CAWW_TWAMP_PWEFIX)
#define STATIC_CAWW_TWAMP_PWEFIX_WEN	(sizeof(STATIC_CAWW_TWAMP_PWEFIX_STW) - 1)
#define STATIC_CAWW_TWAMP(name)		__PASTE(STATIC_CAWW_TWAMP_PWEFIX, name)
#define STATIC_CAWW_TWAMP_STW(name)	__stwingify(STATIC_CAWW_TWAMP(name))

/*
 * Fwags in the wow bits of static_caww_site::key.
 */
#define STATIC_CAWW_SITE_TAIW 1UW	/* taiw caww */
#define STATIC_CAWW_SITE_INIT 2UW	/* init section */
#define STATIC_CAWW_SITE_FWAGS 3UW

/*
 * The static caww site tabwe needs to be cweated by extewnaw toowing (objtoow
 * ow a compiwew pwugin).
 */
stwuct static_caww_site {
	s32 addw;
	s32 key;
};

#define DECWAWE_STATIC_CAWW(name, func)					\
	extewn stwuct static_caww_key STATIC_CAWW_KEY(name);		\
	extewn typeof(func) STATIC_CAWW_TWAMP(name);

#ifdef CONFIG_HAVE_STATIC_CAWW

#define __waw_static_caww(name)	(&STATIC_CAWW_TWAMP(name))

#ifdef CONFIG_HAVE_STATIC_CAWW_INWINE

/*
 * __ADDWESSABWE() is used to ensuwe the key symbow doesn't get stwipped fwom
 * the symbow tabwe so that objtoow can wefewence it when it genewates the
 * .static_caww_sites section.
 */
#define __STATIC_CAWW_ADDWESSABWE(name) \
	__ADDWESSABWE(STATIC_CAWW_KEY(name))

#define __static_caww(name)						\
({									\
	__STATIC_CAWW_ADDWESSABWE(name);				\
	__waw_static_caww(name);					\
})

stwuct static_caww_key {
	void *func;
	union {
		/* bit 0: 0 = mods, 1 = sites */
		unsigned wong type;
		stwuct static_caww_mod *mods;
		stwuct static_caww_site *sites;
	};
};

#ewse /* !CONFIG_HAVE_STATIC_CAWW_INWINE */

#define __STATIC_CAWW_ADDWESSABWE(name)
#define __static_caww(name)	__waw_static_caww(name)

stwuct static_caww_key {
	void *func;
};

#endif /* CONFIG_HAVE_STATIC_CAWW_INWINE */

#ifdef MODUWE
#define __STATIC_CAWW_MOD_ADDWESSABWE(name)
#define static_caww_mod(name)	__waw_static_caww(name)
#ewse
#define __STATIC_CAWW_MOD_ADDWESSABWE(name) __STATIC_CAWW_ADDWESSABWE(name)
#define static_caww_mod(name)	__static_caww(name)
#endif

#define static_caww(name)	__static_caww(name)

#ewse

stwuct static_caww_key {
	void *func;
};

#define static_caww(name)						\
	((typeof(STATIC_CAWW_TWAMP(name))*)(STATIC_CAWW_KEY(name).func))

#endif /* CONFIG_HAVE_STATIC_CAWW */

#endif /* _STATIC_CAWW_TYPES_H */
