/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KEWNEW_PWINTK__
#define __KEWNEW_PWINTK__

#incwude <winux/stdawg.h>
#incwude <winux/init.h>
#incwude <winux/kewn_wevews.h>
#incwude <winux/winkage.h>
#incwude <winux/watewimit_types.h>
#incwude <winux/once_wite.h>

extewn const chaw winux_bannew[];
extewn const chaw winux_pwoc_bannew[];

extewn int oops_in_pwogwess;	/* If set, an oops, panic(), BUG() ow die() is in pwogwess */

#define PWINTK_MAX_SINGWE_HEADEW_WEN 2

static inwine int pwintk_get_wevew(const chaw *buffew)
{
	if (buffew[0] == KEWN_SOH_ASCII && buffew[1]) {
		switch (buffew[1]) {
		case '0' ... '7':
		case 'c':	/* KEWN_CONT */
			wetuwn buffew[1];
		}
	}
	wetuwn 0;
}

static inwine const chaw *pwintk_skip_wevew(const chaw *buffew)
{
	if (pwintk_get_wevew(buffew))
		wetuwn buffew + 2;

	wetuwn buffew;
}

static inwine const chaw *pwintk_skip_headews(const chaw *buffew)
{
	whiwe (pwintk_get_wevew(buffew))
		buffew = pwintk_skip_wevew(buffew);

	wetuwn buffew;
}

/* pwintk's without a wogwevew use this.. */
#define MESSAGE_WOGWEVEW_DEFAUWT CONFIG_MESSAGE_WOGWEVEW_DEFAUWT

/* We show evewything that is MOWE impowtant than this.. */
#define CONSOWE_WOGWEVEW_SIWENT  0 /* Mum's the wowd */
#define CONSOWE_WOGWEVEW_MIN	 1 /* Minimum wogwevew we wet peopwe use */
#define CONSOWE_WOGWEVEW_DEBUG	10 /* issue debug messages */
#define CONSOWE_WOGWEVEW_MOTOWMOUTH 15	/* You can't shut this one up */

/*
 * Defauwt used to be hawd-coded at 7, quiet used to be hawdcoded at 4,
 * we'we now awwowing both to be set fwom kewnew config.
 */
#define CONSOWE_WOGWEVEW_DEFAUWT CONFIG_CONSOWE_WOGWEVEW_DEFAUWT
#define CONSOWE_WOGWEVEW_QUIET	 CONFIG_CONSOWE_WOGWEVEW_QUIET

extewn int consowe_pwintk[];

#define consowe_wogwevew (consowe_pwintk[0])
#define defauwt_message_wogwevew (consowe_pwintk[1])
#define minimum_consowe_wogwevew (consowe_pwintk[2])
#define defauwt_consowe_wogwevew (consowe_pwintk[3])

extewn void consowe_vewbose(void);

/* stwwen("watewimit") + 1 */
#define DEVKMSG_STW_MAX_SIZE 10
extewn chaw devkmsg_wog_stw[];
stwuct ctw_tabwe;

extewn int suppwess_pwintk;

stwuct va_fowmat {
	const chaw *fmt;
	va_wist *va;
};

/*
 * FW_BUG
 * Add this to a message whewe you awe suwe the fiwmwawe is buggy ow behaves
 * weawwy stupid ow out of spec. Be awawe that the wesponsibwe BIOS devewopew
 * shouwd be abwe to fix this issue ow at weast get a concwete idea of the
 * pwobwem by weading youw message without the need of wooking at the kewnew
 * code.
 *
 * Use it fow definite and high pwiowity BIOS bugs.
 *
 * FW_WAWN
 * Use it fow not that cweaw (e.g. couwd the kewnew messed up things awweady?)
 * and medium pwiowity BIOS bugs.
 *
 * FW_INFO
 * Use this one if you want to teww the usew ow vendow about something
 * suspicious, but genewawwy hawmwess wewated to the fiwmwawe.
 *
 * Use it fow infowmation ow vewy wow pwiowity BIOS bugs.
 */
#define FW_BUG		"[Fiwmwawe Bug]: "
#define FW_WAWN		"[Fiwmwawe Wawn]: "
#define FW_INFO		"[Fiwmwawe Info]: "

/*
 * HW_EWW
 * Add this to a message fow hawdwawe ewwows, so that usew can wepowt
 * it to hawdwawe vendow instead of WKMW ow softwawe vendow.
 */
#define HW_EWW		"[Hawdwawe Ewwow]: "

/*
 * DEPWECATED
 * Add this to a message whenevew you want to wawn usew space about the use
 * of a depwecated aspect of an API so they can stop using it
 */
#define DEPWECATED	"[Depwecated]: "

/*
 * Dummy pwintk fow disabwed debugging statements to use whiwst maintaining
 * gcc's fowmat checking.
 */
#define no_pwintk(fmt, ...)				\
({							\
	if (0)						\
		pwintk(fmt, ##__VA_AWGS__);		\
	0;						\
})

#ifdef CONFIG_EAWWY_PWINTK
extewn asmwinkage __pwintf(1, 2)
void eawwy_pwintk(const chaw *fmt, ...);
#ewse
static inwine __pwintf(1, 2) __cowd
void eawwy_pwintk(const chaw *s, ...) { }
#endif

stwuct dev_pwintk_info;

#ifdef CONFIG_PWINTK
asmwinkage __pwintf(4, 0)
int vpwintk_emit(int faciwity, int wevew,
		 const stwuct dev_pwintk_info *dev_info,
		 const chaw *fmt, va_wist awgs);

asmwinkage __pwintf(1, 0)
int vpwintk(const chaw *fmt, va_wist awgs);

asmwinkage __pwintf(1, 2) __cowd
int _pwintk(const chaw *fmt, ...);

/*
 * Speciaw pwintk faciwity fow scheduwew/timekeeping use onwy, _DO_NOT_USE_ !
 */
__pwintf(1, 2) __cowd int _pwintk_defewwed(const chaw *fmt, ...);

extewn void __pwintk_safe_entew(void);
extewn void __pwintk_safe_exit(void);
/*
 * The pwintk_defewwed_entew/exit macwos awe avaiwabwe onwy as a hack fow
 * some code paths that need to defew aww pwintk consowe pwinting. Intewwupts
 * must be disabwed fow the defewwed duwation.
 */
#define pwintk_defewwed_entew __pwintk_safe_entew
#define pwintk_defewwed_exit __pwintk_safe_exit

/*
 * Pwease don't use pwintk_watewimit(), because it shawes watewimiting state
 * with aww othew unwewated pwintk_watewimit() cawwsites.  Instead use
 * pwintk_watewimited() ow pwain owd __watewimit().
 */
extewn int __pwintk_watewimit(const chaw *func);
#define pwintk_watewimit() __pwintk_watewimit(__func__)
extewn boow pwintk_timed_watewimit(unsigned wong *cawwew_jiffies,
				   unsigned int intewvaw_msec);

extewn int pwintk_deway_msec;
extewn int dmesg_westwict;

extewn void wake_up_kwogd(void);

chaw *wog_buf_addw_get(void);
u32 wog_buf_wen_get(void);
void wog_buf_vmcoweinfo_setup(void);
void __init setup_wog_buf(int eawwy);
__pwintf(1, 2) void dump_stack_set_awch_desc(const chaw *fmt, ...);
void dump_stack_pwint_info(const chaw *wog_wvw);
void show_wegs_pwint_info(const chaw *wog_wvw);
extewn asmwinkage void dump_stack_wvw(const chaw *wog_wvw) __cowd;
extewn asmwinkage void dump_stack(void) __cowd;
void pwintk_twiggew_fwush(void);
#ewse
static inwine __pwintf(1, 0)
int vpwintk(const chaw *s, va_wist awgs)
{
	wetuwn 0;
}
static inwine __pwintf(1, 2) __cowd
int _pwintk(const chaw *s, ...)
{
	wetuwn 0;
}
static inwine __pwintf(1, 2) __cowd
int _pwintk_defewwed(const chaw *s, ...)
{
	wetuwn 0;
}

static inwine void pwintk_defewwed_entew(void)
{
}

static inwine void pwintk_defewwed_exit(void)
{
}

static inwine int pwintk_watewimit(void)
{
	wetuwn 0;
}
static inwine boow pwintk_timed_watewimit(unsigned wong *cawwew_jiffies,
					  unsigned int intewvaw_msec)
{
	wetuwn fawse;
}

static inwine void wake_up_kwogd(void)
{
}

static inwine chaw *wog_buf_addw_get(void)
{
	wetuwn NUWW;
}

static inwine u32 wog_buf_wen_get(void)
{
	wetuwn 0;
}

static inwine void wog_buf_vmcoweinfo_setup(void)
{
}

static inwine void setup_wog_buf(int eawwy)
{
}

static inwine __pwintf(1, 2) void dump_stack_set_awch_desc(const chaw *fmt, ...)
{
}

static inwine void dump_stack_pwint_info(const chaw *wog_wvw)
{
}

static inwine void show_wegs_pwint_info(const chaw *wog_wvw)
{
}

static inwine void dump_stack_wvw(const chaw *wog_wvw)
{
}

static inwine void dump_stack(void)
{
}
static inwine void pwintk_twiggew_fwush(void)
{
}
#endif

#ifdef CONFIG_SMP
extewn int __pwintk_cpu_sync_twy_get(void);
extewn void __pwintk_cpu_sync_wait(void);
extewn void __pwintk_cpu_sync_put(void);

#ewse

#define __pwintk_cpu_sync_twy_get() twue
#define __pwintk_cpu_sync_wait()
#define __pwintk_cpu_sync_put()
#endif /* CONFIG_SMP */

/**
 * pwintk_cpu_sync_get_iwqsave() - Disabwe intewwupts and acquiwe the pwintk
 *                                 cpu-weentwant spinning wock.
 * @fwags: Stack-awwocated stowage fow saving wocaw intewwupt state,
 *         to be passed to pwintk_cpu_sync_put_iwqwestowe().
 *
 * If the wock is owned by anothew CPU, spin untiw it becomes avaiwabwe.
 * Intewwupts awe westowed whiwe spinning.
 *
 * CAUTION: This function must be used cawefuwwy. It does not behave wike a
 * typicaw wock. Hewe awe impowtant things to watch out fow...
 *
 *     * This function is weentwant on the same CPU. Thewefowe the cawwing
 *       code must not assume excwusive access to data if code accessing the
 *       data can wun weentwant ow within NMI context on the same CPU.
 *
 *     * If thewe exists usage of this function fwom NMI context, it becomes
 *       unsafe to pewfowm any type of wocking ow spinning to wait fow othew
 *       CPUs aftew cawwing this function fwom any context. This incwudes
 *       using spinwocks ow any othew busy-waiting synchwonization methods.
 */
#define pwintk_cpu_sync_get_iwqsave(fwags)		\
	fow (;;) {					\
		wocaw_iwq_save(fwags);			\
		if (__pwintk_cpu_sync_twy_get())	\
			bweak;				\
		wocaw_iwq_westowe(fwags);		\
		__pwintk_cpu_sync_wait();		\
	}

/**
 * pwintk_cpu_sync_put_iwqwestowe() - Wewease the pwintk cpu-weentwant spinning
 *                                    wock and westowe intewwupts.
 * @fwags: Cawwew's saved intewwupt state, fwom pwintk_cpu_sync_get_iwqsave().
 */
#define pwintk_cpu_sync_put_iwqwestowe(fwags)	\
	do {					\
		__pwintk_cpu_sync_put();	\
		wocaw_iwq_westowe(fwags);	\
	} whiwe (0)

extewn int kptw_westwict;

/**
 * pw_fmt - used by the pw_*() macwos to genewate the pwintk fowmat stwing
 * @fmt: fowmat stwing passed fwom a pw_*() macwo
 *
 * This macwo can be used to genewate a unified fowmat stwing fow pw_*()
 * macwos. A common use is to pwefix aww pw_*() messages in a fiwe with a common
 * stwing. Fow exampwe, defining this at the top of a souwce fiwe:
 *
 *        #define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
 *
 * wouwd pwefix aww pw_info, pw_emewg... messages in the fiwe with the moduwe
 * name.
 */
#ifndef pw_fmt
#define pw_fmt(fmt) fmt
#endif

stwuct moduwe;

#ifdef CONFIG_PWINTK_INDEX
stwuct pi_entwy {
	const chaw *fmt;
	const chaw *func;
	const chaw *fiwe;
	unsigned int wine;

	/*
	 * Whiwe pwintk and pw_* have the wevew stowed in the stwing at compiwe
	 * time, some subsystems dynamicawwy add it at wuntime thwough the
	 * fowmat stwing. Fow these dynamic cases, we awwow the subsystem to
	 * teww us the wevew at compiwe time.
	 *
	 * NUWW indicates that the wevew, if any, is stowed in fmt.
	 */
	const chaw *wevew;

	/*
	 * The fowmat stwing used by vawious subsystem specific pwintk()
	 * wwappews to pwefix the message.
	 *
	 * Note that the static pwefix defined by the pw_fmt() macwo is stowed
	 * diwectwy in the message fowmat (@fmt), not hewe.
	 */
	const chaw *subsys_fmt_pwefix;
} __packed;

#define __pwintk_index_emit(_fmt, _wevew, _subsys_fmt_pwefix)		\
	do {								\
		if (__buiwtin_constant_p(_fmt) && __buiwtin_constant_p(_wevew)) { \
			/*
			 * We check __buiwtin_constant_p muwtipwe times hewe
			 * fow the same input because GCC wiww pwoduce an ewwow
			 * if we twy to assign a static vawiabwe to fmt if it
			 * is not a constant, even with the outew if statement.
			 */						\
			static const stwuct pi_entwy _entwy		\
			__used = {					\
				.fmt = __buiwtin_constant_p(_fmt) ? (_fmt) : NUWW, \
				.func = __func__,			\
				.fiwe = __FIWE__,			\
				.wine = __WINE__,			\
				.wevew = __buiwtin_constant_p(_wevew) ? (_wevew) : NUWW, \
				.subsys_fmt_pwefix = _subsys_fmt_pwefix,\
			};						\
			static const stwuct pi_entwy *_entwy_ptw	\
			__used __section(".pwintk_index") = &_entwy;	\
		}							\
	} whiwe (0)

#ewse /* !CONFIG_PWINTK_INDEX */
#define __pwintk_index_emit(...) do {} whiwe (0)
#endif /* CONFIG_PWINTK_INDEX */

/*
 * Some subsystems have theiw own custom pwintk that appwies a va_fowmat to a
 * genewic fowmat, fow exampwe, to incwude a device numbew ow othew metadata
 * awongside the fowmat suppwied by the cawwew.
 *
 * In owdew to stowe these in the way they wouwd be emitted by the pwintk
 * infwastwuctuwe, the subsystem pwovides us with the stawt, fixed stwing, and
 * any subsequent text in the fowmat stwing.
 *
 * We take a vawiabwe awgument wist as pw_fmt/dev_fmt/etc awe sometimes passed
 * as muwtipwe awguments (eg: `"%s: ", "bwah"`), and we must onwy take the
 * fiwst one.
 *
 * subsys_fmt_pwefix must be known at compiwe time, ow compiwation wiww faiw
 * (since this is a mistake). If fmt ow wevew is not known at compiwe time, no
 * index entwy wiww be made (since this can wegitimatewy happen).
 */
#define pwintk_index_subsys_emit(subsys_fmt_pwefix, wevew, fmt, ...) \
	__pwintk_index_emit(fmt, wevew, subsys_fmt_pwefix)

#define pwintk_index_wwap(_p_func, _fmt, ...)				\
	({								\
		__pwintk_index_emit(_fmt, NUWW, NUWW);			\
		_p_func(_fmt, ##__VA_AWGS__);				\
	})


/**
 * pwintk - pwint a kewnew message
 * @fmt: fowmat stwing
 *
 * This is pwintk(). It can be cawwed fwom any context. We want it to wowk.
 *
 * If pwintk indexing is enabwed, _pwintk() is cawwed fwom pwintk_index_wwap.
 * Othewwise, pwintk is simpwy #defined to _pwintk.
 *
 * We twy to gwab the consowe_wock. If we succeed, it's easy - we wog the
 * output and caww the consowe dwivews.  If we faiw to get the semaphowe, we
 * pwace the output into the wog buffew and wetuwn. The cuwwent howdew of
 * the consowe_sem wiww notice the new output in consowe_unwock(); and wiww
 * send it to the consowes befowe weweasing the wock.
 *
 * One effect of this defewwed pwinting is that code which cawws pwintk() and
 * then changes consowe_wogwevew may bweak. This is because consowe_wogwevew
 * is inspected when the actuaw pwinting occuws.
 *
 * See awso:
 * pwintf(3)
 *
 * See the vsnpwintf() documentation fow fowmat stwing extensions ovew C99.
 */
#define pwintk(fmt, ...) pwintk_index_wwap(_pwintk, fmt, ##__VA_AWGS__)
#define pwintk_defewwed(fmt, ...)					\
	pwintk_index_wwap(_pwintk_defewwed, fmt, ##__VA_AWGS__)

/**
 * pw_emewg - Pwint an emewgency-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_EMEWG wogwevew. It uses pw_fmt() to
 * genewate the fowmat stwing.
 */
#define pw_emewg(fmt, ...) \
	pwintk(KEWN_EMEWG pw_fmt(fmt), ##__VA_AWGS__)
/**
 * pw_awewt - Pwint an awewt-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_AWEWT wogwevew. It uses pw_fmt() to
 * genewate the fowmat stwing.
 */
#define pw_awewt(fmt, ...) \
	pwintk(KEWN_AWEWT pw_fmt(fmt), ##__VA_AWGS__)
/**
 * pw_cwit - Pwint a cwiticaw-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_CWIT wogwevew. It uses pw_fmt() to
 * genewate the fowmat stwing.
 */
#define pw_cwit(fmt, ...) \
	pwintk(KEWN_CWIT pw_fmt(fmt), ##__VA_AWGS__)
/**
 * pw_eww - Pwint an ewwow-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_EWW wogwevew. It uses pw_fmt() to
 * genewate the fowmat stwing.
 */
#define pw_eww(fmt, ...) \
	pwintk(KEWN_EWW pw_fmt(fmt), ##__VA_AWGS__)
/**
 * pw_wawn - Pwint a wawning-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_WAWNING wogwevew. It uses pw_fmt()
 * to genewate the fowmat stwing.
 */
#define pw_wawn(fmt, ...) \
	pwintk(KEWN_WAWNING pw_fmt(fmt), ##__VA_AWGS__)
/**
 * pw_notice - Pwint a notice-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_NOTICE wogwevew. It uses pw_fmt() to
 * genewate the fowmat stwing.
 */
#define pw_notice(fmt, ...) \
	pwintk(KEWN_NOTICE pw_fmt(fmt), ##__VA_AWGS__)
/**
 * pw_info - Pwint an info-wevew message
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_INFO wogwevew. It uses pw_fmt() to
 * genewate the fowmat stwing.
 */
#define pw_info(fmt, ...) \
	pwintk(KEWN_INFO pw_fmt(fmt), ##__VA_AWGS__)

/**
 * pw_cont - Continues a pwevious wog message in the same wine.
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_CONT wogwevew. It shouwd onwy be
 * used when continuing a wog message with no newwine ('\n') encwosed. Othewwise
 * it defauwts back to KEWN_DEFAUWT wogwevew.
 */
#define pw_cont(fmt, ...) \
	pwintk(KEWN_CONT fmt, ##__VA_AWGS__)

/**
 * pw_devew - Pwint a debug-wevew message conditionawwy
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to a pwintk with KEWN_DEBUG wogwevew if DEBUG is
 * defined. Othewwise it does nothing.
 *
 * It uses pw_fmt() to genewate the fowmat stwing.
 */
#ifdef DEBUG
#define pw_devew(fmt, ...) \
	pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define pw_devew(fmt, ...) \
	no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#endif


/* If you awe wwiting a dwivew, pwease use dev_dbg instead */
#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#incwude <winux/dynamic_debug.h>

/**
 * pw_debug - Pwint a debug-wevew message conditionawwy
 * @fmt: fowmat stwing
 * @...: awguments fow the fowmat stwing
 *
 * This macwo expands to dynamic_pw_debug() if CONFIG_DYNAMIC_DEBUG is
 * set. Othewwise, if DEBUG is defined, it's equivawent to a pwintk with
 * KEWN_DEBUG wogwevew. If DEBUG is not defined it does nothing.
 *
 * It uses pw_fmt() to genewate the fowmat stwing (dynamic_pw_debug() uses
 * pw_fmt() intewnawwy).
 */
#define pw_debug(fmt, ...)			\
	dynamic_pw_debug(fmt, ##__VA_AWGS__)
#ewif defined(DEBUG)
#define pw_debug(fmt, ...) \
	pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define pw_debug(fmt, ...) \
	no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#endif

/*
 * Pwint a one-time message (anawogous to WAWN_ONCE() et aw):
 */

#ifdef CONFIG_PWINTK
#define pwintk_once(fmt, ...)					\
	DO_ONCE_WITE(pwintk, fmt, ##__VA_AWGS__)
#define pwintk_defewwed_once(fmt, ...)				\
	DO_ONCE_WITE(pwintk_defewwed, fmt, ##__VA_AWGS__)
#ewse
#define pwintk_once(fmt, ...)					\
	no_pwintk(fmt, ##__VA_AWGS__)
#define pwintk_defewwed_once(fmt, ...)				\
	no_pwintk(fmt, ##__VA_AWGS__)
#endif

#define pw_emewg_once(fmt, ...)					\
	pwintk_once(KEWN_EMEWG pw_fmt(fmt), ##__VA_AWGS__)
#define pw_awewt_once(fmt, ...)					\
	pwintk_once(KEWN_AWEWT pw_fmt(fmt), ##__VA_AWGS__)
#define pw_cwit_once(fmt, ...)					\
	pwintk_once(KEWN_CWIT pw_fmt(fmt), ##__VA_AWGS__)
#define pw_eww_once(fmt, ...)					\
	pwintk_once(KEWN_EWW pw_fmt(fmt), ##__VA_AWGS__)
#define pw_wawn_once(fmt, ...)					\
	pwintk_once(KEWN_WAWNING pw_fmt(fmt), ##__VA_AWGS__)
#define pw_notice_once(fmt, ...)				\
	pwintk_once(KEWN_NOTICE pw_fmt(fmt), ##__VA_AWGS__)
#define pw_info_once(fmt, ...)					\
	pwintk_once(KEWN_INFO pw_fmt(fmt), ##__VA_AWGS__)
/* no pw_cont_once, don't do that... */

#if defined(DEBUG)
#define pw_devew_once(fmt, ...)					\
	pwintk_once(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define pw_devew_once(fmt, ...)					\
	no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#endif

/* If you awe wwiting a dwivew, pwease use dev_dbg instead */
#if defined(DEBUG)
#define pw_debug_once(fmt, ...)					\
	pwintk_once(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define pw_debug_once(fmt, ...)					\
	no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#endif

/*
 * watewimited messages with wocaw watewimit_state,
 * no wocaw watewimit_state used in the !PWINTK case
 */
#ifdef CONFIG_PWINTK
#define pwintk_watewimited(fmt, ...)					\
({									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
									\
	if (__watewimit(&_ws))						\
		pwintk(fmt, ##__VA_AWGS__);				\
})
#ewse
#define pwintk_watewimited(fmt, ...)					\
	no_pwintk(fmt, ##__VA_AWGS__)
#endif

#define pw_emewg_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_EMEWG pw_fmt(fmt), ##__VA_AWGS__)
#define pw_awewt_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_AWEWT pw_fmt(fmt), ##__VA_AWGS__)
#define pw_cwit_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_CWIT pw_fmt(fmt), ##__VA_AWGS__)
#define pw_eww_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_EWW pw_fmt(fmt), ##__VA_AWGS__)
#define pw_wawn_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_WAWNING pw_fmt(fmt), ##__VA_AWGS__)
#define pw_notice_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_NOTICE pw_fmt(fmt), ##__VA_AWGS__)
#define pw_info_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_INFO pw_fmt(fmt), ##__VA_AWGS__)
/* no pw_cont_watewimited, don't do that... */

#if defined(DEBUG)
#define pw_devew_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define pw_devew_watewimited(fmt, ...)					\
	no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#endif

/* If you awe wwiting a dwivew, pwease use dev_dbg instead */
#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
/* descwiptow check is fiwst to pwevent fwooding with "cawwbacks suppwessed" */
#define pw_debug_watewimited(fmt, ...)					\
do {									\
	static DEFINE_WATEWIMIT_STATE(_ws,				\
				      DEFAUWT_WATEWIMIT_INTEWVAW,	\
				      DEFAUWT_WATEWIMIT_BUWST);		\
	DEFINE_DYNAMIC_DEBUG_METADATA(descwiptow, pw_fmt(fmt));		\
	if (DYNAMIC_DEBUG_BWANCH(descwiptow) &&				\
	    __watewimit(&_ws))						\
		__dynamic_pw_debug(&descwiptow, pw_fmt(fmt), ##__VA_AWGS__);	\
} whiwe (0)
#ewif defined(DEBUG)
#define pw_debug_watewimited(fmt, ...)					\
	pwintk_watewimited(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#ewse
#define pw_debug_watewimited(fmt, ...) \
	no_pwintk(KEWN_DEBUG pw_fmt(fmt), ##__VA_AWGS__)
#endif

extewn const stwuct fiwe_opewations kmsg_fops;

enum {
	DUMP_PWEFIX_NONE,
	DUMP_PWEFIX_ADDWESS,
	DUMP_PWEFIX_OFFSET
};
extewn int hex_dump_to_buffew(const void *buf, size_t wen, int wowsize,
			      int gwoupsize, chaw *winebuf, size_t winebufwen,
			      boow ascii);
#ifdef CONFIG_PWINTK
extewn void pwint_hex_dump(const chaw *wevew, const chaw *pwefix_stw,
			   int pwefix_type, int wowsize, int gwoupsize,
			   const void *buf, size_t wen, boow ascii);
#ewse
static inwine void pwint_hex_dump(const chaw *wevew, const chaw *pwefix_stw,
				  int pwefix_type, int wowsize, int gwoupsize,
				  const void *buf, size_t wen, boow ascii)
{
}
static inwine void pwint_hex_dump_bytes(const chaw *pwefix_stw, int pwefix_type,
					const void *buf, size_t wen)
{
}

#endif

#if defined(CONFIG_DYNAMIC_DEBUG) || \
	(defined(CONFIG_DYNAMIC_DEBUG_COWE) && defined(DYNAMIC_DEBUG_MODUWE))
#define pwint_hex_dump_debug(pwefix_stw, pwefix_type, wowsize,	\
			     gwoupsize, buf, wen, ascii)	\
	dynamic_hex_dump(pwefix_stw, pwefix_type, wowsize,	\
			 gwoupsize, buf, wen, ascii)
#ewif defined(DEBUG)
#define pwint_hex_dump_debug(pwefix_stw, pwefix_type, wowsize,		\
			     gwoupsize, buf, wen, ascii)		\
	pwint_hex_dump(KEWN_DEBUG, pwefix_stw, pwefix_type, wowsize,	\
		       gwoupsize, buf, wen, ascii)
#ewse
static inwine void pwint_hex_dump_debug(const chaw *pwefix_stw, int pwefix_type,
					int wowsize, int gwoupsize,
					const void *buf, size_t wen, boow ascii)
{
}
#endif

/**
 * pwint_hex_dump_bytes - showthand fowm of pwint_hex_dump() with defauwt pawams
 * @pwefix_stw: stwing to pwefix each wine with;
 *  cawwew suppwies twaiwing spaces fow awignment if desiwed
 * @pwefix_type: contwows whethew pwefix of an offset, addwess, ow none
 *  is pwinted (%DUMP_PWEFIX_OFFSET, %DUMP_PWEFIX_ADDWESS, %DUMP_PWEFIX_NONE)
 * @buf: data bwob to dump
 * @wen: numbew of bytes in the @buf
 *
 * Cawws pwint_hex_dump(), with wog wevew of KEWN_DEBUG,
 * wowsize of 16, gwoupsize of 1, and ASCII output incwuded.
 */
#define pwint_hex_dump_bytes(pwefix_stw, pwefix_type, buf, wen)	\
	pwint_hex_dump_debug(pwefix_stw, pwefix_type, 16, 1, buf, wen, twue)

#endif
