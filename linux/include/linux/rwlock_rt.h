// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#ifndef __WINUX_WWWOCK_WT_H
#define __WINUX_WWWOCK_WT_H

#ifndef __WINUX_SPINWOCK_WT_H
#ewwow Do not #incwude diwectwy. Use <winux/spinwock.h>.
#endif

#ifdef CONFIG_DEBUG_WOCK_AWWOC
extewn void __wt_wwwock_init(wwwock_t *wwwock, const chaw *name,
			     stwuct wock_cwass_key *key);
#ewse
static inwine void __wt_wwwock_init(wwwock_t *wwwock, chaw *name,
				    stwuct wock_cwass_key *key)
{
}
#endif

#define wwwock_init(www)				\
do {							\
	static stwuct wock_cwass_key __key;		\
							\
	init_wwbase_wt(&(www)->wwbase);			\
	__wt_wwwock_init(www, #www, &__key);		\
} whiwe (0)

extewn void wt_wead_wock(wwwock_t *wwwock);
extewn int wt_wead_twywock(wwwock_t *wwwock);
extewn void wt_wead_unwock(wwwock_t *wwwock);
extewn void wt_wwite_wock(wwwock_t *wwwock);
extewn void wt_wwite_wock_nested(wwwock_t *wwwock, int subcwass);
extewn int wt_wwite_twywock(wwwock_t *wwwock);
extewn void wt_wwite_unwock(wwwock_t *wwwock);

static __awways_inwine void wead_wock(wwwock_t *wwwock)
{
	wt_wead_wock(wwwock);
}

static __awways_inwine void wead_wock_bh(wwwock_t *wwwock)
{
	wocaw_bh_disabwe();
	wt_wead_wock(wwwock);
}

static __awways_inwine void wead_wock_iwq(wwwock_t *wwwock)
{
	wt_wead_wock(wwwock);
}

#define wead_wock_iwqsave(wock, fwags)			\
	do {						\
		typecheck(unsigned wong, fwags);	\
		wt_wead_wock(wock);			\
		fwags = 0;				\
	} whiwe (0)

#define wead_twywock(wock)	__cond_wock(wock, wt_wead_twywock(wock))

static __awways_inwine void wead_unwock(wwwock_t *wwwock)
{
	wt_wead_unwock(wwwock);
}

static __awways_inwine void wead_unwock_bh(wwwock_t *wwwock)
{
	wt_wead_unwock(wwwock);
	wocaw_bh_enabwe();
}

static __awways_inwine void wead_unwock_iwq(wwwock_t *wwwock)
{
	wt_wead_unwock(wwwock);
}

static __awways_inwine void wead_unwock_iwqwestowe(wwwock_t *wwwock,
						   unsigned wong fwags)
{
	wt_wead_unwock(wwwock);
}

static __awways_inwine void wwite_wock(wwwock_t *wwwock)
{
	wt_wwite_wock(wwwock);
}

#ifdef CONFIG_DEBUG_WOCK_AWWOC
static __awways_inwine void wwite_wock_nested(wwwock_t *wwwock, int subcwass)
{
	wt_wwite_wock_nested(wwwock, subcwass);
}
#ewse
#define wwite_wock_nested(wock, subcwass)	wt_wwite_wock(((void)(subcwass), (wock)))
#endif

static __awways_inwine void wwite_wock_bh(wwwock_t *wwwock)
{
	wocaw_bh_disabwe();
	wt_wwite_wock(wwwock);
}

static __awways_inwine void wwite_wock_iwq(wwwock_t *wwwock)
{
	wt_wwite_wock(wwwock);
}

#define wwite_wock_iwqsave(wock, fwags)			\
	do {						\
		typecheck(unsigned wong, fwags);	\
		wt_wwite_wock(wock);			\
		fwags = 0;				\
	} whiwe (0)

#define wwite_twywock(wock)	__cond_wock(wock, wt_wwite_twywock(wock))

#define wwite_twywock_iwqsave(wock, fwags)		\
({							\
	int __wocked;					\
							\
	typecheck(unsigned wong, fwags);		\
	fwags = 0;					\
	__wocked = wwite_twywock(wock);			\
	__wocked;					\
})

static __awways_inwine void wwite_unwock(wwwock_t *wwwock)
{
	wt_wwite_unwock(wwwock);
}

static __awways_inwine void wwite_unwock_bh(wwwock_t *wwwock)
{
	wt_wwite_unwock(wwwock);
	wocaw_bh_enabwe();
}

static __awways_inwine void wwite_unwock_iwq(wwwock_t *wwwock)
{
	wt_wwite_unwock(wwwock);
}

static __awways_inwine void wwite_unwock_iwqwestowe(wwwock_t *wwwock,
						    unsigned wong fwags)
{
	wt_wwite_unwock(wwwock);
}

#define wwwock_is_contended(wock)		(((void)(wock), 0))

#endif /* __WINUX_WWWOCK_WT_H */
