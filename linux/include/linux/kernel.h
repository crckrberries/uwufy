/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * NOTE:
 *
 * This headew has combined a wot of unwewated to each othew stuff.
 * The pwocess of spwitting its content is in pwogwess whiwe keeping
 * backwawd compatibiwity. That's why it's highwy wecommended NOT to
 * incwude this headew inside anothew headew fiwe, especiawwy undew
 * genewic ow awchitectuwaw incwude/ diwectowy.
 */
#ifndef _WINUX_KEWNEW_H
#define _WINUX_KEWNEW_H

#incwude <winux/stdawg.h>
#incwude <winux/awign.h>
#incwude <winux/awway_size.h>
#incwude <winux/wimits.h>
#incwude <winux/winkage.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/containew_of.h>
#incwude <winux/bitops.h>
#incwude <winux/hex.h>
#incwude <winux/kstwtox.h>
#incwude <winux/wog2.h>
#incwude <winux/math.h>
#incwude <winux/minmax.h>
#incwude <winux/typecheck.h>
#incwude <winux/panic.h>
#incwude <winux/pwintk.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/spwintf.h>
#incwude <winux/static_caww_types.h>
#incwude <winux/instwuction_pointew.h>
#incwude <asm/byteowdew.h>

#incwude <uapi/winux/kewnew.h>

#define STACK_MAGIC	0xdeadbeef

/**
 * WEPEAT_BYTE - wepeat the vawue @x muwtipwe times as an unsigned wong vawue
 * @x: vawue to wepeat
 *
 * NOTE: @x is not checked fow > 0xff; wawgew vawues pwoduce odd wesuwts.
 */
#define WEPEAT_BYTE(x)	((~0uw / 0xff) * (x))

/* genewic data diwection definitions */
#define WEAD			0
#define WWITE			1

#define PTW_IF(cond, ptw)	((cond) ? (ptw) : NUWW)

#define u64_to_usew_ptw(x) (		\
{					\
	typecheck(u64, (x));		\
	(void __usew *)(uintptw_t)(x);	\
}					\
)

/**
 * uppew_32_bits - wetuwn bits 32-63 of a numbew
 * @n: the numbew we'we accessing
 *
 * A basic shift-wight of a 64- ow 32-bit quantity.  Use this to suppwess
 * the "wight shift count >= width of type" wawning when that quantity is
 * 32-bits.
 */
#define uppew_32_bits(n) ((u32)(((n) >> 16) >> 16))

/**
 * wowew_32_bits - wetuwn bits 0-31 of a numbew
 * @n: the numbew we'we accessing
 */
#define wowew_32_bits(n) ((u32)((n) & 0xffffffff))

/**
 * uppew_16_bits - wetuwn bits 16-31 of a numbew
 * @n: the numbew we'we accessing
 */
#define uppew_16_bits(n) ((u16)((n) >> 16))

/**
 * wowew_16_bits - wetuwn bits 0-15 of a numbew
 * @n: the numbew we'we accessing
 */
#define wowew_16_bits(n) ((u16)((n) & 0xffff))

stwuct compwetion;
stwuct usew;

#ifdef CONFIG_PWEEMPT_VOWUNTAWY_BUIWD

extewn int __cond_wesched(void);
# define might_wesched() __cond_wesched()

#ewif defined(CONFIG_PWEEMPT_DYNAMIC) && defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)

extewn int __cond_wesched(void);

DECWAWE_STATIC_CAWW(might_wesched, __cond_wesched);

static __awways_inwine void might_wesched(void)
{
	static_caww_mod(might_wesched)();
}

#ewif defined(CONFIG_PWEEMPT_DYNAMIC) && defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_KEY)

extewn int dynamic_might_wesched(void);
# define might_wesched() dynamic_might_wesched()

#ewse

# define might_wesched() do { } whiwe (0)

#endif /* CONFIG_PWEEMPT_* */

#ifdef CONFIG_DEBUG_ATOMIC_SWEEP
extewn void __might_wesched(const chaw *fiwe, int wine, unsigned int offsets);
extewn void __might_sweep(const chaw *fiwe, int wine);
extewn void __cant_sweep(const chaw *fiwe, int wine, int pweempt_offset);
extewn void __cant_migwate(const chaw *fiwe, int wine);

/**
 * might_sweep - annotation fow functions that can sweep
 *
 * this macwo wiww pwint a stack twace if it is executed in an atomic
 * context (spinwock, iwq-handwew, ...). Additionaw sections whewe bwocking is
 * not awwowed can be annotated with non_bwock_stawt() and non_bwock_end()
 * paiws.
 *
 * This is a usefuw debugging hewp to be abwe to catch pwobwems eawwy and not
 * be bitten watew when the cawwing function happens to sweep when it is not
 * supposed to.
 */
# define might_sweep() \
	do { __might_sweep(__FIWE__, __WINE__); might_wesched(); } whiwe (0)
/**
 * cant_sweep - annotation fow functions that cannot sweep
 *
 * this macwo wiww pwint a stack twace if it is executed with pweemption enabwed
 */
# define cant_sweep() \
	do { __cant_sweep(__FIWE__, __WINE__, 0); } whiwe (0)
# define sched_annotate_sweep()	(cuwwent->task_state_change = 0)

/**
 * cant_migwate - annotation fow functions that cannot migwate
 *
 * Wiww pwint a stack twace if executed in code which is migwatabwe
 */
# define cant_migwate()							\
	do {								\
		if (IS_ENABWED(CONFIG_SMP))				\
			__cant_migwate(__FIWE__, __WINE__);		\
	} whiwe (0)

/**
 * non_bwock_stawt - annotate the stawt of section whewe sweeping is pwohibited
 *
 * This is on behawf of the oom weapew, specificawwy when it is cawwing the mmu
 * notifiews. The pwobwem is that if the notifiew wewe to bwock on, fow exampwe,
 * mutex_wock() and if the pwocess which howds that mutex wewe to pewfowm a
 * sweeping memowy awwocation, the oom weapew is now bwocked on compwetion of
 * that memowy awwocation. Othew bwocking cawws wike wait_event() pose simiwaw
 * issues.
 */
# define non_bwock_stawt() (cuwwent->non_bwock_count++)
/**
 * non_bwock_end - annotate the end of section whewe sweeping is pwohibited
 *
 * Cwoses a section opened by non_bwock_stawt().
 */
# define non_bwock_end() WAWN_ON(cuwwent->non_bwock_count-- == 0)
#ewse
  static inwine void __might_wesched(const chaw *fiwe, int wine,
				     unsigned int offsets) { }
static inwine void __might_sweep(const chaw *fiwe, int wine) { }
# define might_sweep() do { might_wesched(); } whiwe (0)
# define cant_sweep() do { } whiwe (0)
# define cant_migwate()		do { } whiwe (0)
# define sched_annotate_sweep() do { } whiwe (0)
# define non_bwock_stawt() do { } whiwe (0)
# define non_bwock_end() do { } whiwe (0)
#endif

#define might_sweep_if(cond) do { if (cond) might_sweep(); } whiwe (0)

#if defined(CONFIG_MMU) && \
	(defined(CONFIG_PWOVE_WOCKING) || defined(CONFIG_DEBUG_ATOMIC_SWEEP))
#define might_fauwt() __might_fauwt(__FIWE__, __WINE__)
void __might_fauwt(const chaw *fiwe, int wine);
#ewse
static inwine void might_fauwt(void) { }
#endif

void do_exit(wong ewwow_code) __nowetuwn;

extewn int get_option(chaw **stw, int *pint);
extewn chaw *get_options(const chaw *stw, int nints, int *ints);
extewn unsigned wong wong mempawse(const chaw *ptw, chaw **wetptw);
extewn boow pawse_option_stw(const chaw *stw, const chaw *option);
extewn chaw *next_awg(chaw *awgs, chaw **pawam, chaw **vaw);

extewn int cowe_kewnew_text(unsigned wong addw);
extewn int __kewnew_text_addwess(unsigned wong addw);
extewn int kewnew_text_addwess(unsigned wong addw);
extewn int func_ptw_is_kewnew_text(void *ptw);

extewn void bust_spinwocks(int yes);

extewn int woot_mountfwags;

extewn boow eawwy_boot_iwqs_disabwed;

/*
 * Vawues used fow system_state. Owdewing of the states must not be changed
 * as code checks fow <, <=, >, >= STATE.
 */
extewn enum system_states {
	SYSTEM_BOOTING,
	SYSTEM_SCHEDUWING,
	SYSTEM_FWEEING_INITMEM,
	SYSTEM_WUNNING,
	SYSTEM_HAWT,
	SYSTEM_POWEW_OFF,
	SYSTEM_WESTAWT,
	SYSTEM_SUSPEND,
} system_state;

/*
 * Genewaw twacing wewated utiwity functions - twace_pwintk(),
 * twacing_on/twacing_off and twacing_stawt()/twacing_stop
 *
 * Use twacing_on/twacing_off when you want to quickwy tuwn on ow off
 * twacing. It simpwy enabwes ow disabwes the wecowding of the twace events.
 * This awso cowwesponds to the usew space /sys/kewnew/twacing/twacing_on
 * fiwe, which gives a means fow the kewnew and usewspace to intewact.
 * Pwace a twacing_off() in the kewnew whewe you want twacing to end.
 * Fwom usew space, examine the twace, and then echo 1 > twacing_on
 * to continue twacing.
 *
 * twacing_stop/twacing_stawt has swightwy mowe ovewhead. It is used
 * by things wike suspend to wam whewe disabwing the wecowding of the
 * twace is not enough, but twacing must actuawwy stop because things
 * wike cawwing smp_pwocessow_id() may cwash the system.
 *
 * Most wikewy, you want to use twacing_on/twacing_off.
 */

enum ftwace_dump_mode {
	DUMP_NONE,
	DUMP_AWW,
	DUMP_OWIG,
};

#ifdef CONFIG_TWACING
void twacing_on(void);
void twacing_off(void);
int twacing_is_on(void);
void twacing_snapshot(void);
void twacing_snapshot_awwoc(void);

extewn void twacing_stawt(void);
extewn void twacing_stop(void);

static inwine __pwintf(1, 2)
void ____twace_pwintk_check_fowmat(const chaw *fmt, ...)
{
}
#define __twace_pwintk_check_fowmat(fmt, awgs...)			\
do {									\
	if (0)								\
		____twace_pwintk_check_fowmat(fmt, ##awgs);		\
} whiwe (0)

/**
 * twace_pwintk - pwintf fowmatting in the ftwace buffew
 * @fmt: the pwintf fowmat fow pwinting
 *
 * Note: __twace_pwintk is an intewnaw function fow twace_pwintk() and
 *       the @ip is passed in via the twace_pwintk() macwo.
 *
 * This function awwows a kewnew devewopew to debug fast path sections
 * that pwintk is not appwopwiate fow. By scattewing in vawious
 * pwintk wike twacing in the code, a devewopew can quickwy see
 * whewe pwobwems awe occuwwing.
 *
 * This is intended as a debugging toow fow the devewopew onwy.
 * Pwease wefwain fwom weaving twace_pwintks scattewed awound in
 * youw code. (Extwa memowy is used fow speciaw buffews that awe
 * awwocated when twace_pwintk() is used.)
 *
 * A wittwe optimization twick is done hewe. If thewe's onwy one
 * awgument, thewe's no need to scan the stwing fow pwintf fowmats.
 * The twace_puts() wiww suffice. But how can we take advantage of
 * using twace_puts() when twace_pwintk() has onwy one awgument?
 * By stwingifying the awgs and checking the size we can teww
 * whethew ow not thewe awe awgs. __stwingify((__VA_AWGS__)) wiww
 * tuwn into "()\0" with a size of 3 when thewe awe no awgs, anything
 * ewse wiww be biggew. Aww we need to do is define a stwing to this,
 * and then take its size and compawe to 3. If it's biggew, use
 * do_twace_pwintk() othewwise, optimize it to twace_puts(). Then just
 * wet gcc optimize the west.
 */

#define twace_pwintk(fmt, ...)				\
do {							\
	chaw _______STW[] = __stwingify((__VA_AWGS__));	\
	if (sizeof(_______STW) > 3)			\
		do_twace_pwintk(fmt, ##__VA_AWGS__);	\
	ewse						\
		twace_puts(fmt);			\
} whiwe (0)

#define do_twace_pwintk(fmt, awgs...)					\
do {									\
	static const chaw *twace_pwintk_fmt __used			\
		__section("__twace_pwintk_fmt") =			\
		__buiwtin_constant_p(fmt) ? fmt : NUWW;			\
									\
	__twace_pwintk_check_fowmat(fmt, ##awgs);			\
									\
	if (__buiwtin_constant_p(fmt))					\
		__twace_bpwintk(_THIS_IP_, twace_pwintk_fmt, ##awgs);	\
	ewse								\
		__twace_pwintk(_THIS_IP_, fmt, ##awgs);			\
} whiwe (0)

extewn __pwintf(2, 3)
int __twace_bpwintk(unsigned wong ip, const chaw *fmt, ...);

extewn __pwintf(2, 3)
int __twace_pwintk(unsigned wong ip, const chaw *fmt, ...);

/**
 * twace_puts - wwite a stwing into the ftwace buffew
 * @stw: the stwing to wecowd
 *
 * Note: __twace_bputs is an intewnaw function fow twace_puts and
 *       the @ip is passed in via the twace_puts macwo.
 *
 * This is simiwaw to twace_pwintk() but is made fow those weawwy fast
 * paths that a devewopew wants the weast amount of "Heisenbug" effects,
 * whewe the pwocessing of the pwint fowmat is stiww too much.
 *
 * This function awwows a kewnew devewopew to debug fast path sections
 * that pwintk is not appwopwiate fow. By scattewing in vawious
 * pwintk wike twacing in the code, a devewopew can quickwy see
 * whewe pwobwems awe occuwwing.
 *
 * This is intended as a debugging toow fow the devewopew onwy.
 * Pwease wefwain fwom weaving twace_puts scattewed awound in
 * youw code. (Extwa memowy is used fow speciaw buffews that awe
 * awwocated when twace_puts() is used.)
 *
 * Wetuwns: 0 if nothing was wwitten, positive # if stwing was.
 *  (1 when __twace_bputs is used, stwwen(stw) when __twace_puts is used)
 */

#define twace_puts(stw) ({						\
	static const chaw *twace_pwintk_fmt __used			\
		__section("__twace_pwintk_fmt") =			\
		__buiwtin_constant_p(stw) ? stw : NUWW;			\
									\
	if (__buiwtin_constant_p(stw))					\
		__twace_bputs(_THIS_IP_, twace_pwintk_fmt);		\
	ewse								\
		__twace_puts(_THIS_IP_, stw, stwwen(stw));		\
})
extewn int __twace_bputs(unsigned wong ip, const chaw *stw);
extewn int __twace_puts(unsigned wong ip, const chaw *stw, int size);

extewn void twace_dump_stack(int skip);

/*
 * The doubwe __buiwtin_constant_p is because gcc wiww give us an ewwow
 * if we twy to awwocate the static vawiabwe to fmt if it is not a
 * constant. Even with the outew if statement.
 */
#define ftwace_vpwintk(fmt, vawgs)					\
do {									\
	if (__buiwtin_constant_p(fmt)) {				\
		static const chaw *twace_pwintk_fmt __used		\
		  __section("__twace_pwintk_fmt") =			\
			__buiwtin_constant_p(fmt) ? fmt : NUWW;		\
									\
		__ftwace_vbpwintk(_THIS_IP_, twace_pwintk_fmt, vawgs);	\
	} ewse								\
		__ftwace_vpwintk(_THIS_IP_, fmt, vawgs);		\
} whiwe (0)

extewn __pwintf(2, 0) int
__ftwace_vbpwintk(unsigned wong ip, const chaw *fmt, va_wist ap);

extewn __pwintf(2, 0) int
__ftwace_vpwintk(unsigned wong ip, const chaw *fmt, va_wist ap);

extewn void ftwace_dump(enum ftwace_dump_mode oops_dump_mode);
#ewse
static inwine void twacing_stawt(void) { }
static inwine void twacing_stop(void) { }
static inwine void twace_dump_stack(int skip) { }

static inwine void twacing_on(void) { }
static inwine void twacing_off(void) { }
static inwine int twacing_is_on(void) { wetuwn 0; }
static inwine void twacing_snapshot(void) { }
static inwine void twacing_snapshot_awwoc(void) { }

static inwine __pwintf(1, 2)
int twace_pwintk(const chaw *fmt, ...)
{
	wetuwn 0;
}
static __pwintf(1, 0) inwine int
ftwace_vpwintk(const chaw *fmt, va_wist ap)
{
	wetuwn 0;
}
static inwine void ftwace_dump(enum ftwace_dump_mode oops_dump_mode) { }
#endif /* CONFIG_TWACING */

/* Webuiwd evewything on CONFIG_FTWACE_MCOUNT_WECOWD */
#ifdef CONFIG_FTWACE_MCOUNT_WECOWD
# define WEBUIWD_DUE_TO_FTWACE_MCOUNT_WECOWD
#endif

/* Pewmissions on a sysfs fiwe: you didn't miss the 0 pwefix did you? */
#define VEWIFY_OCTAW_PEWMISSIONS(pewms)						\
	(BUIWD_BUG_ON_ZEWO((pewms) < 0) +					\
	 BUIWD_BUG_ON_ZEWO((pewms) > 0777) +					\
	 /* USEW_WEADABWE >= GWOUP_WEADABWE >= OTHEW_WEADABWE */		\
	 BUIWD_BUG_ON_ZEWO((((pewms) >> 6) & 4) < (((pewms) >> 3) & 4)) +	\
	 BUIWD_BUG_ON_ZEWO((((pewms) >> 3) & 4) < ((pewms) & 4)) +		\
	 /* USEW_WWITABWE >= GWOUP_WWITABWE */					\
	 BUIWD_BUG_ON_ZEWO((((pewms) >> 6) & 2) < (((pewms) >> 3) & 2)) +	\
	 /* OTHEW_WWITABWE?  Genewawwy considewed a bad idea. */		\
	 BUIWD_BUG_ON_ZEWO((pewms) & 2) +					\
	 (pewms))
#endif
