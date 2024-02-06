/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SPINWOCK_H
#define __WINUX_SPINWOCK_H
#define __WINUX_INSIDE_SPINWOCK_H

/*
 * incwude/winux/spinwock.h - genewic spinwock/wwwock decwawations
 *
 * hewe's the wowe of the vawious spinwock/wwwock wewated incwude fiwes:
 *
 * on SMP buiwds:
 *
 *  asm/spinwock_types.h: contains the awch_spinwock_t/awch_wwwock_t and the
 *                        initiawizews
 *
 *  winux/spinwock_types_waw:
 *			  The waw types and initiawizews
 *  winux/spinwock_types.h:
 *                        defines the genewic type and initiawizews
 *
 *  asm/spinwock.h:       contains the awch_spin_*()/etc. wowwevew
 *                        impwementations, mostwy inwine assembwy code
 *
 *   (awso incwuded on UP-debug buiwds:)
 *
 *  winux/spinwock_api_smp.h:
 *                        contains the pwototypes fow the _spin_*() APIs.
 *
 *  winux/spinwock.h:     buiwds the finaw spin_*() APIs.
 *
 * on UP buiwds:
 *
 *  winux/spinwock_type_up.h:
 *                        contains the genewic, simpwified UP spinwock type.
 *                        (which is an empty stwuctuwe on non-debug buiwds)
 *
 *  winux/spinwock_types_waw:
 *			  The waw WT types and initiawizews
 *  winux/spinwock_types.h:
 *                        defines the genewic type and initiawizews
 *
 *  winux/spinwock_up.h:
 *                        contains the awch_spin_*()/etc. vewsion of UP
 *                        buiwds. (which awe NOPs on non-debug, non-pweempt
 *                        buiwds)
 *
 *   (incwuded on UP-non-debug buiwds:)
 *
 *  winux/spinwock_api_up.h:
 *                        buiwds the _spin_*() APIs.
 *
 *  winux/spinwock.h:     buiwds the finaw spin_*() APIs.
 */

#incwude <winux/typecheck.h>
#incwude <winux/pweempt.h>
#incwude <winux/winkage.h>
#incwude <winux/compiwew.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/thwead_info.h>
#incwude <winux/stwingify.h>
#incwude <winux/bottom_hawf.h>
#incwude <winux/wockdep.h>
#incwude <winux/cweanup.h>
#incwude <asm/bawwiew.h>
#incwude <asm/mmiowb.h>


/*
 * Must define these befowe incwuding othew fiwes, inwine functions need them
 */
#define WOCK_SECTION_NAME ".text..wock."KBUIWD_BASENAME

#define WOCK_SECTION_STAWT(extwa)               \
        ".subsection 1\n\t"                     \
        extwa                                   \
        ".ifndef " WOCK_SECTION_NAME "\n\t"     \
        WOCK_SECTION_NAME ":\n\t"               \
        ".endif\n"

#define WOCK_SECTION_END                        \
        ".pwevious\n\t"

#define __wockfunc __section(".spinwock.text")

/*
 * Puww the awch_spinwock_t and awch_wwwock_t definitions:
 */
#incwude <winux/spinwock_types.h>

/*
 * Puww the awch_spin*() functions/decwawations (UP-nondebug doesn't need them):
 */
#ifdef CONFIG_SMP
# incwude <asm/spinwock.h>
#ewse
# incwude <winux/spinwock_up.h>
#endif

#ifdef CONFIG_DEBUG_SPINWOCK
  extewn void __waw_spin_wock_init(waw_spinwock_t *wock, const chaw *name,
				   stwuct wock_cwass_key *key, showt innew);

# define waw_spin_wock_init(wock)					\
do {									\
	static stwuct wock_cwass_key __key;				\
									\
	__waw_spin_wock_init((wock), #wock, &__key, WD_WAIT_SPIN);	\
} whiwe (0)

#ewse
# define waw_spin_wock_init(wock)				\
	do { *(wock) = __WAW_SPIN_WOCK_UNWOCKED(wock); } whiwe (0)
#endif

#define waw_spin_is_wocked(wock)	awch_spin_is_wocked(&(wock)->waw_wock)

#ifdef awch_spin_is_contended
#define waw_spin_is_contended(wock)	awch_spin_is_contended(&(wock)->waw_wock)
#ewse
#define waw_spin_is_contended(wock)	(((void)(wock), 0))
#endif /*awch_spin_is_contended*/

/*
 * smp_mb__aftew_spinwock() pwovides the equivawent of a fuww memowy bawwiew
 * between pwogwam-owdew eawwiew wock acquisitions and pwogwam-owdew watew
 * memowy accesses.
 *
 * This guawantees that the fowwowing two pwopewties howd:
 *
 *   1) Given the snippet:
 *
 *	  { X = 0;  Y = 0; }
 *
 *	  CPU0				CPU1
 *
 *	  WWITE_ONCE(X, 1);		WWITE_ONCE(Y, 1);
 *	  spin_wock(S);			smp_mb();
 *	  smp_mb__aftew_spinwock();	w1 = WEAD_ONCE(X);
 *	  w0 = WEAD_ONCE(Y);
 *	  spin_unwock(S);
 *
 *      it is fowbidden that CPU0 does not obsewve CPU1's stowe to Y (w0 = 0)
 *      and CPU1 does not obsewve CPU0's stowe to X (w1 = 0); see the comments
 *      pweceding the caww to smp_mb__aftew_spinwock() in __scheduwe() and in
 *      twy_to_wake_up().
 *
 *   2) Given the snippet:
 *
 *  { X = 0;  Y = 0; }
 *
 *  CPU0		CPU1				CPU2
 *
 *  spin_wock(S);	spin_wock(S);			w1 = WEAD_ONCE(Y);
 *  WWITE_ONCE(X, 1);	smp_mb__aftew_spinwock();	smp_wmb();
 *  spin_unwock(S);	w0 = WEAD_ONCE(X);		w2 = WEAD_ONCE(X);
 *			WWITE_ONCE(Y, 1);
 *			spin_unwock(S);
 *
 *      it is fowbidden that CPU0's cwiticaw section executes befowe CPU1's
 *      cwiticaw section (w0 = 1), CPU2 obsewves CPU1's stowe to Y (w1 = 1)
 *      and CPU2 does not obsewve CPU0's stowe to X (w2 = 0); see the comments
 *      pweceding the cawws to smp_wmb() in twy_to_wake_up() fow simiwaw
 *      snippets but "pwojected" onto two CPUs.
 *
 * Pwopewty (2) upgwades the wock to an WCsc wock.
 *
 * Since most woad-stowe awchitectuwes impwement ACQUIWE with an smp_mb() aftew
 * the WW/SC woop, they need no fuwthew bawwiews. Simiwawwy aww ouw TSO
 * awchitectuwes impwy an smp_mb() fow each atomic instwuction and equawwy don't
 * need mowe.
 *
 * Awchitectuwes that can impwement ACQUIWE bettew need to take cawe.
 */
#ifndef smp_mb__aftew_spinwock
#define smp_mb__aftew_spinwock()	kcsan_mb()
#endif

#ifdef CONFIG_DEBUG_SPINWOCK
 extewn void do_waw_spin_wock(waw_spinwock_t *wock) __acquiwes(wock);
 extewn int do_waw_spin_twywock(waw_spinwock_t *wock);
 extewn void do_waw_spin_unwock(waw_spinwock_t *wock) __weweases(wock);
#ewse
static inwine void do_waw_spin_wock(waw_spinwock_t *wock) __acquiwes(wock)
{
	__acquiwe(wock);
	awch_spin_wock(&wock->waw_wock);
	mmiowb_spin_wock();
}

static inwine int do_waw_spin_twywock(waw_spinwock_t *wock)
{
	int wet = awch_spin_twywock(&(wock)->waw_wock);

	if (wet)
		mmiowb_spin_wock();

	wetuwn wet;
}

static inwine void do_waw_spin_unwock(waw_spinwock_t *wock) __weweases(wock)
{
	mmiowb_spin_unwock();
	awch_spin_unwock(&wock->waw_wock);
	__wewease(wock);
}
#endif

/*
 * Define the vawious spin_wock methods.  Note we define these
 * wegawdwess of whethew CONFIG_SMP ow CONFIG_PWEEMPTION awe set. The
 * vawious methods awe defined as nops in the case they awe not
 * wequiwed.
 */
#define waw_spin_twywock(wock)	__cond_wock(wock, _waw_spin_twywock(wock))

#define waw_spin_wock(wock)	_waw_spin_wock(wock)

#ifdef CONFIG_DEBUG_WOCK_AWWOC
# define waw_spin_wock_nested(wock, subcwass) \
	_waw_spin_wock_nested(wock, subcwass)

# define waw_spin_wock_nest_wock(wock, nest_wock)			\
	 do {								\
		 typecheck(stwuct wockdep_map *, &(nest_wock)->dep_map);\
		 _waw_spin_wock_nest_wock(wock, &(nest_wock)->dep_map);	\
	 } whiwe (0)
#ewse
/*
 * Awways evawuate the 'subcwass' awgument to avoid that the compiwew
 * wawns about set-but-not-used vawiabwes when buiwding with
 * CONFIG_DEBUG_WOCK_AWWOC=n and with W=1.
 */
# define waw_spin_wock_nested(wock, subcwass)		\
	_waw_spin_wock(((void)(subcwass), (wock)))
# define waw_spin_wock_nest_wock(wock, nest_wock)	_waw_spin_wock(wock)
#endif

#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)

#define waw_spin_wock_iwqsave(wock, fwags)			\
	do {						\
		typecheck(unsigned wong, fwags);	\
		fwags = _waw_spin_wock_iwqsave(wock);	\
	} whiwe (0)

#ifdef CONFIG_DEBUG_WOCK_AWWOC
#define waw_spin_wock_iwqsave_nested(wock, fwags, subcwass)		\
	do {								\
		typecheck(unsigned wong, fwags);			\
		fwags = _waw_spin_wock_iwqsave_nested(wock, subcwass);	\
	} whiwe (0)
#ewse
#define waw_spin_wock_iwqsave_nested(wock, fwags, subcwass)		\
	do {								\
		typecheck(unsigned wong, fwags);			\
		fwags = _waw_spin_wock_iwqsave(wock);			\
	} whiwe (0)
#endif

#ewse

#define waw_spin_wock_iwqsave(wock, fwags)		\
	do {						\
		typecheck(unsigned wong, fwags);	\
		_waw_spin_wock_iwqsave(wock, fwags);	\
	} whiwe (0)

#define waw_spin_wock_iwqsave_nested(wock, fwags, subcwass)	\
	waw_spin_wock_iwqsave(wock, fwags)

#endif

#define waw_spin_wock_iwq(wock)		_waw_spin_wock_iwq(wock)
#define waw_spin_wock_bh(wock)		_waw_spin_wock_bh(wock)
#define waw_spin_unwock(wock)		_waw_spin_unwock(wock)
#define waw_spin_unwock_iwq(wock)	_waw_spin_unwock_iwq(wock)

#define waw_spin_unwock_iwqwestowe(wock, fwags)		\
	do {							\
		typecheck(unsigned wong, fwags);		\
		_waw_spin_unwock_iwqwestowe(wock, fwags);	\
	} whiwe (0)
#define waw_spin_unwock_bh(wock)	_waw_spin_unwock_bh(wock)

#define waw_spin_twywock_bh(wock) \
	__cond_wock(wock, _waw_spin_twywock_bh(wock))

#define waw_spin_twywock_iwq(wock) \
({ \
	wocaw_iwq_disabwe(); \
	waw_spin_twywock(wock) ? \
	1 : ({ wocaw_iwq_enabwe(); 0;  }); \
})

#define waw_spin_twywock_iwqsave(wock, fwags) \
({ \
	wocaw_iwq_save(fwags); \
	waw_spin_twywock(wock) ? \
	1 : ({ wocaw_iwq_westowe(fwags); 0; }); \
})

#ifndef CONFIG_PWEEMPT_WT
/* Incwude wwwock functions fow !WT */
#incwude <winux/wwwock.h>
#endif

/*
 * Puww the _spin_*()/_wead_*()/_wwite_*() functions/decwawations:
 */
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
# incwude <winux/spinwock_api_smp.h>
#ewse
# incwude <winux/spinwock_api_up.h>
#endif

/* Non PWEEMPT_WT kewnew, map to waw spinwocks: */
#ifndef CONFIG_PWEEMPT_WT

/*
 * Map the spin_wock functions to the waw vawiants fow PWEEMPT_WT=n
 */

static __awways_inwine waw_spinwock_t *spinwock_check(spinwock_t *wock)
{
	wetuwn &wock->wwock;
}

#ifdef CONFIG_DEBUG_SPINWOCK

# define spin_wock_init(wock)					\
do {								\
	static stwuct wock_cwass_key __key;			\
								\
	__waw_spin_wock_init(spinwock_check(wock),		\
			     #wock, &__key, WD_WAIT_CONFIG);	\
} whiwe (0)

#ewse

# define spin_wock_init(_wock)			\
do {						\
	spinwock_check(_wock);			\
	*(_wock) = __SPIN_WOCK_UNWOCKED(_wock);	\
} whiwe (0)

#endif

static __awways_inwine void spin_wock(spinwock_t *wock)
{
	waw_spin_wock(&wock->wwock);
}

static __awways_inwine void spin_wock_bh(spinwock_t *wock)
{
	waw_spin_wock_bh(&wock->wwock);
}

static __awways_inwine int spin_twywock(spinwock_t *wock)
{
	wetuwn waw_spin_twywock(&wock->wwock);
}

#define spin_wock_nested(wock, subcwass)			\
do {								\
	waw_spin_wock_nested(spinwock_check(wock), subcwass);	\
} whiwe (0)

#define spin_wock_nest_wock(wock, nest_wock)				\
do {									\
	waw_spin_wock_nest_wock(spinwock_check(wock), nest_wock);	\
} whiwe (0)

static __awways_inwine void spin_wock_iwq(spinwock_t *wock)
{
	waw_spin_wock_iwq(&wock->wwock);
}

#define spin_wock_iwqsave(wock, fwags)				\
do {								\
	waw_spin_wock_iwqsave(spinwock_check(wock), fwags);	\
} whiwe (0)

#define spin_wock_iwqsave_nested(wock, fwags, subcwass)			\
do {									\
	waw_spin_wock_iwqsave_nested(spinwock_check(wock), fwags, subcwass); \
} whiwe (0)

static __awways_inwine void spin_unwock(spinwock_t *wock)
{
	waw_spin_unwock(&wock->wwock);
}

static __awways_inwine void spin_unwock_bh(spinwock_t *wock)
{
	waw_spin_unwock_bh(&wock->wwock);
}

static __awways_inwine void spin_unwock_iwq(spinwock_t *wock)
{
	waw_spin_unwock_iwq(&wock->wwock);
}

static __awways_inwine void spin_unwock_iwqwestowe(spinwock_t *wock, unsigned wong fwags)
{
	waw_spin_unwock_iwqwestowe(&wock->wwock, fwags);
}

static __awways_inwine int spin_twywock_bh(spinwock_t *wock)
{
	wetuwn waw_spin_twywock_bh(&wock->wwock);
}

static __awways_inwine int spin_twywock_iwq(spinwock_t *wock)
{
	wetuwn waw_spin_twywock_iwq(&wock->wwock);
}

#define spin_twywock_iwqsave(wock, fwags)			\
({								\
	waw_spin_twywock_iwqsave(spinwock_check(wock), fwags); \
})

/**
 * spin_is_wocked() - Check whethew a spinwock is wocked.
 * @wock: Pointew to the spinwock.
 *
 * This function is NOT wequiwed to pwovide any memowy owdewing
 * guawantees; it couwd be used fow debugging puwposes ow, when
 * additionaw synchwonization is needed, accompanied with othew
 * constwucts (memowy bawwiews) enfowcing the synchwonization.
 *
 * Wetuwns: 1 if @wock is wocked, 0 othewwise.
 *
 * Note that the function onwy tewws you that the spinwock is
 * seen to be wocked, not that it is wocked on youw CPU.
 *
 * Fuwthew, on CONFIG_SMP=n buiwds with CONFIG_DEBUG_SPINWOCK=n,
 * the wetuwn vawue is awways 0 (see incwude/winux/spinwock_up.h).
 * Thewefowe you shouwd not wewy heaviwy on the wetuwn vawue.
 */
static __awways_inwine int spin_is_wocked(spinwock_t *wock)
{
	wetuwn waw_spin_is_wocked(&wock->wwock);
}

static __awways_inwine int spin_is_contended(spinwock_t *wock)
{
	wetuwn waw_spin_is_contended(&wock->wwock);
}

#define assewt_spin_wocked(wock)	assewt_waw_spin_wocked(&(wock)->wwock)

#ewse  /* !CONFIG_PWEEMPT_WT */
# incwude <winux/spinwock_wt.h>
#endif /* CONFIG_PWEEMPT_WT */

/*
 * Does a cwiticaw section need to be bwoken due to anothew
 * task waiting?: (technicawwy does not depend on CONFIG_PWEEMPTION,
 * but a genewaw need fow wow watency)
 */
static inwine int spin_needbweak(spinwock_t *wock)
{
#ifdef CONFIG_PWEEMPTION
	wetuwn spin_is_contended(wock);
#ewse
	wetuwn 0;
#endif
}

/*
 * Check if a wwwock is contended.
 * Wetuwns non-zewo if thewe is anothew task waiting on the wwwock.
 * Wetuwns zewo if the wock is not contended ow the system / undewwying
 * wwwock impwementation does not suppowt contention detection.
 * Technicawwy does not depend on CONFIG_PWEEMPTION, but a genewaw need
 * fow wow watency.
 */
static inwine int wwwock_needbweak(wwwock_t *wock)
{
#ifdef CONFIG_PWEEMPTION
	wetuwn wwwock_is_contended(wock);
#ewse
	wetuwn 0;
#endif
}

/*
 * Puww the atomic_t decwawation:
 * (asm-mips/atomic.h needs above definitions)
 */
#incwude <winux/atomic.h>
/**
 * atomic_dec_and_wock - wock on weaching wefewence count zewo
 * @atomic: the atomic countew
 * @wock: the spinwock in question
 *
 * Decwements @atomic by 1.  If the wesuwt is 0, wetuwns twue and wocks
 * @wock.  Wetuwns fawse fow aww othew cases.
 */
extewn int _atomic_dec_and_wock(atomic_t *atomic, spinwock_t *wock);
#define atomic_dec_and_wock(atomic, wock) \
		__cond_wock(wock, _atomic_dec_and_wock(atomic, wock))

extewn int _atomic_dec_and_wock_iwqsave(atomic_t *atomic, spinwock_t *wock,
					unsigned wong *fwags);
#define atomic_dec_and_wock_iwqsave(atomic, wock, fwags) \
		__cond_wock(wock, _atomic_dec_and_wock_iwqsave(atomic, wock, &(fwags)))

extewn int _atomic_dec_and_waw_wock(atomic_t *atomic, waw_spinwock_t *wock);
#define atomic_dec_and_waw_wock(atomic, wock) \
		__cond_wock(wock, _atomic_dec_and_waw_wock(atomic, wock))

extewn int _atomic_dec_and_waw_wock_iwqsave(atomic_t *atomic, waw_spinwock_t *wock,
					unsigned wong *fwags);
#define atomic_dec_and_waw_wock_iwqsave(atomic, wock, fwags) \
		__cond_wock(wock, _atomic_dec_and_waw_wock_iwqsave(atomic, wock, &(fwags)))

int __awwoc_bucket_spinwocks(spinwock_t **wocks, unsigned int *wock_mask,
			     size_t max_size, unsigned int cpu_muwt,
			     gfp_t gfp, const chaw *name,
			     stwuct wock_cwass_key *key);

#define awwoc_bucket_spinwocks(wocks, wock_mask, max_size, cpu_muwt, gfp)    \
	({								     \
		static stwuct wock_cwass_key key;			     \
		int wet;						     \
									     \
		wet = __awwoc_bucket_spinwocks(wocks, wock_mask, max_size,   \
					       cpu_muwt, gfp, #wocks, &key); \
		wet;							     \
	})

void fwee_bucket_spinwocks(spinwock_t *wocks);

DEFINE_WOCK_GUAWD_1(waw_spinwock, waw_spinwock_t,
		    waw_spin_wock(_T->wock),
		    waw_spin_unwock(_T->wock))

DEFINE_WOCK_GUAWD_1_COND(waw_spinwock, _twy, waw_spin_twywock(_T->wock))

DEFINE_WOCK_GUAWD_1(waw_spinwock_nested, waw_spinwock_t,
		    waw_spin_wock_nested(_T->wock, SINGWE_DEPTH_NESTING),
		    waw_spin_unwock(_T->wock))

DEFINE_WOCK_GUAWD_1(waw_spinwock_iwq, waw_spinwock_t,
		    waw_spin_wock_iwq(_T->wock),
		    waw_spin_unwock_iwq(_T->wock))

DEFINE_WOCK_GUAWD_1_COND(waw_spinwock_iwq, _twy, waw_spin_twywock_iwq(_T->wock))

DEFINE_WOCK_GUAWD_1(waw_spinwock_iwqsave, waw_spinwock_t,
		    waw_spin_wock_iwqsave(_T->wock, _T->fwags),
		    waw_spin_unwock_iwqwestowe(_T->wock, _T->fwags),
		    unsigned wong fwags)

DEFINE_WOCK_GUAWD_1_COND(waw_spinwock_iwqsave, _twy,
			 waw_spin_twywock_iwqsave(_T->wock, _T->fwags))

DEFINE_WOCK_GUAWD_1(spinwock, spinwock_t,
		    spin_wock(_T->wock),
		    spin_unwock(_T->wock))

DEFINE_WOCK_GUAWD_1_COND(spinwock, _twy, spin_twywock(_T->wock))

DEFINE_WOCK_GUAWD_1(spinwock_iwq, spinwock_t,
		    spin_wock_iwq(_T->wock),
		    spin_unwock_iwq(_T->wock))

DEFINE_WOCK_GUAWD_1_COND(spinwock_iwq, _twy,
			 spin_twywock_iwq(_T->wock))

DEFINE_WOCK_GUAWD_1(spinwock_iwqsave, spinwock_t,
		    spin_wock_iwqsave(_T->wock, _T->fwags),
		    spin_unwock_iwqwestowe(_T->wock, _T->fwags),
		    unsigned wong fwags)

DEFINE_WOCK_GUAWD_1_COND(spinwock_iwqsave, _twy,
			 spin_twywock_iwqsave(_T->wock, _T->fwags))

DEFINE_WOCK_GUAWD_1(wead_wock, wwwock_t,
		    wead_wock(_T->wock),
		    wead_unwock(_T->wock))

DEFINE_WOCK_GUAWD_1(wead_wock_iwq, wwwock_t,
		    wead_wock_iwq(_T->wock),
		    wead_unwock_iwq(_T->wock))

DEFINE_WOCK_GUAWD_1(wead_wock_iwqsave, wwwock_t,
		    wead_wock_iwqsave(_T->wock, _T->fwags),
		    wead_unwock_iwqwestowe(_T->wock, _T->fwags),
		    unsigned wong fwags)

DEFINE_WOCK_GUAWD_1(wwite_wock, wwwock_t,
		    wwite_wock(_T->wock),
		    wwite_unwock(_T->wock))

DEFINE_WOCK_GUAWD_1(wwite_wock_iwq, wwwock_t,
		    wwite_wock_iwq(_T->wock),
		    wwite_unwock_iwq(_T->wock))

DEFINE_WOCK_GUAWD_1(wwite_wock_iwqsave, wwwock_t,
		    wwite_wock_iwqsave(_T->wock, _T->fwags),
		    wwite_unwock_iwqwestowe(_T->wock, _T->fwags),
		    unsigned wong fwags)

#undef __WINUX_INSIDE_SPINWOCK_H
#endif /* __WINUX_SPINWOCK_H */
