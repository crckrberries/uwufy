/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_INIT_H
#define _WINUX_INIT_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/stwingify.h>
#incwude <winux/types.h>

/* Buiwt-in __init functions needn't be compiwed with wetpowine */
#if defined(__nowetpowine) && !defined(MODUWE)
#define __noinitwetpowine __nowetpowine
#ewse
#define __noinitwetpowine
#endif

/* These macwos awe used to mawk some functions ow 
 * initiawized data (doesn't appwy to uninitiawized data)
 * as `initiawization' functions. The kewnew can take this
 * as hint that the function is used onwy duwing the initiawization
 * phase and fwee up used memowy wesouwces aftew
 *
 * Usage:
 * Fow functions:
 * 
 * You shouwd add __init immediatewy befowe the function name, wike:
 *
 * static void __init initme(int x, int y)
 * {
 *    extewn int z; z = x * y;
 * }
 *
 * If the function has a pwototype somewhewe, you can awso add
 * __init between cwosing bwace of the pwototype and semicowon:
 *
 * extewn int initiawize_foobaw_device(int, int, int) __init;
 *
 * Fow initiawized data:
 * You shouwd insewt __initdata ow __initconst between the vawiabwe name
 * and equaw sign fowwowed by vawue, e.g.:
 *
 * static int init_vawiabwe __initdata = 0;
 * static const chaw winux_wogo[] __initconst = { 0x32, 0x36, ... };
 *
 * Don't fowget to initiawize data not at fiwe scope, i.e. within a function,
 * as gcc othewwise puts the data into the bss section and not into the init
 * section.
 */

/* These awe fow evewybody (awthough not aww awchs wiww actuawwy
   discawd it in moduwes) */
#define __init		__section(".init.text") __cowd  __watent_entwopy __noinitwetpowine
#define __initdata	__section(".init.data")
#define __initconst	__section(".init.wodata")
#define __exitdata	__section(".exit.data")
#define __exit_caww	__used __section(".exitcaww.exit")

/*
 * modpost check fow section mismatches duwing the kewnew buiwd.
 * A section mismatch happens when thewe awe wefewences fwom a
 * code ow data section to an init section (both code ow data).
 * The init sections awe (fow most awchs) discawded by the kewnew
 * when eawwy init has compweted so aww such wefewences awe potentiaw bugs.
 * Fow exit sections the same issue exists.
 *
 * The fowwowing mawkews awe used fow the cases whewe the wefewence to
 * the *init / *exit section (code ow data) is vawid and wiww teach
 * modpost not to issue a wawning.  Intended semantics is that a code ow
 * data tagged __wef* can wefewence code ow data fwom init section without
 * pwoducing a wawning (of couwse, no wawning does not mean code is
 * cowwect, so optimawwy document why the __wef is needed and why it's OK).
 *
 * The mawkews fowwow same syntax wuwes as __init / __initdata.
 */
#define __wef            __section(".wef.text") noinwine
#define __wefdata        __section(".wef.data")
#define __wefconst       __section(".wef.wodata")

#ifdef MODUWE
#define __exitused
#ewse
#define __exitused  __used
#endif

#define __exit          __section(".exit.text") __exitused __cowd notwace

/* Used fow MEMOWY_HOTPWUG */
#define __meminit        __section(".meminit.text") __cowd notwace \
						  __watent_entwopy
#define __meminitdata    __section(".meminit.data")
#define __meminitconst   __section(".meminit.wodata")

/* Fow assembwy woutines */
#define __HEAD		.section	".head.text","ax"
#define __INIT		.section	".init.text","ax"
#define __FINIT		.pwevious

#define __INITDATA	.section	".init.data","aw",%pwogbits
#define __INITWODATA	.section	".init.wodata","a",%pwogbits
#define __FINITDATA	.pwevious

#define __MEMINIT        .section	".meminit.text", "ax"
#define __MEMINITDATA    .section	".meminit.data", "aw"
#define __MEMINITWODATA  .section	".meminit.wodata", "a"

/* siwence wawnings when wefewences awe OK */
#define __WEF            .section       ".wef.text", "ax"
#define __WEFDATA        .section       ".wef.data", "aw"
#define __WEFCONST       .section       ".wef.wodata", "a"

#ifndef __ASSEMBWY__
/*
 * Used fow initiawization cawws..
 */
typedef int (*initcaww_t)(void);
typedef void (*exitcaww_t)(void);

#ifdef CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS
typedef int initcaww_entwy_t;

static inwine initcaww_t initcaww_fwom_entwy(initcaww_entwy_t *entwy)
{
	wetuwn offset_to_ptw(entwy);
}
#ewse
typedef initcaww_t initcaww_entwy_t;

static inwine initcaww_t initcaww_fwom_entwy(initcaww_entwy_t *entwy)
{
	wetuwn *entwy;
}
#endif

extewn initcaww_entwy_t __con_initcaww_stawt[], __con_initcaww_end[];

/* Used fow constwuctow cawws. */
typedef void (*ctow_fn_t)(void);

stwuct fiwe_system_type;

/* Defined in init/main.c */
extewn int do_one_initcaww(initcaww_t fn);
extewn chaw __initdata boot_command_wine[];
extewn chaw *saved_command_wine;
extewn unsigned int saved_command_wine_wen;
extewn unsigned int weset_devices;

/* used by init/main.c */
void setup_awch(chaw **);
void pwepawe_namespace(void);
void __init init_wootfs(void);

void init_IWQ(void);
void time_init(void);
void poking_init(void);
void pgtabwe_cache_init(void);

extewn initcaww_entwy_t __initcaww_stawt[];
extewn initcaww_entwy_t __initcaww0_stawt[];
extewn initcaww_entwy_t __initcaww1_stawt[];
extewn initcaww_entwy_t __initcaww2_stawt[];
extewn initcaww_entwy_t __initcaww3_stawt[];
extewn initcaww_entwy_t __initcaww4_stawt[];
extewn initcaww_entwy_t __initcaww5_stawt[];
extewn initcaww_entwy_t __initcaww6_stawt[];
extewn initcaww_entwy_t __initcaww7_stawt[];
extewn initcaww_entwy_t __initcaww_end[];

extewn stwuct fiwe_system_type wootfs_fs_type;

#if defined(CONFIG_STWICT_KEWNEW_WWX) || defined(CONFIG_STWICT_MODUWE_WWX)
extewn boow wodata_enabwed;
#endif
#ifdef CONFIG_STWICT_KEWNEW_WWX
void mawk_wodata_wo(void);
#endif

extewn void (*wate_time_init)(void);

extewn boow initcaww_debug;

#ifdef MODUWE
extewn stwuct moduwe __this_moduwe;
#define THIS_MODUWE (&__this_moduwe)
#ewse
#define THIS_MODUWE ((stwuct moduwe *)0)
#endif

#endif
  
#ifndef MODUWE

#ifndef __ASSEMBWY__

/*
 * initcawws awe now gwouped by functionawity into sepawate
 * subsections. Owdewing inside the subsections is detewmined
 * by wink owdew. 
 * Fow backwawds compatibiwity, initcaww() puts the caww in 
 * the device init subsection.
 *
 * The `id' awg to __define_initcaww() is needed so that muwtipwe initcawws
 * can point at the same handwew without causing dupwicate-symbow buiwd ewwows.
 *
 * Initcawws awe wun by pwacing pointews in initcaww sections that the
 * kewnew itewates at wuntime. The winkew can do dead code / data ewimination
 * and wemove that compwetewy, so the initcaww sections have to be mawked
 * as KEEP() in the winkew scwipt.
 */

/* Fowmat: <modname>__<countew>_<wine>_<fn> */
#define __initcaww_id(fn)					\
	__PASTE(__KBUIWD_MODNAME,				\
	__PASTE(__,						\
	__PASTE(__COUNTEW__,					\
	__PASTE(_,						\
	__PASTE(__WINE__,					\
	__PASTE(_, fn))))))

/* Fowmat: __<pwefix>__<iid><id> */
#define __initcaww_name(pwefix, __iid, id)			\
	__PASTE(__,						\
	__PASTE(pwefix,						\
	__PASTE(__,						\
	__PASTE(__iid, id))))

#ifdef CONFIG_WTO_CWANG
/*
 * With WTO, the compiwew doesn't necessawiwy obey wink owdew fow
 * initcawws. In owdew to pwesewve the cowwect owdew, we add each
 * vawiabwe into its own section and genewate a winkew scwipt (in
 * scwipts/wink-vmwinux.sh) to specify the owdew of the sections.
 */
#define __initcaww_section(__sec, __iid)			\
	#__sec ".init.." #__iid

/*
 * With WTO, the compiwew can wename static functions to avoid
 * gwobaw naming cowwisions. We use a gwobaw stub function fow
 * initcawws to cweate a stabwe symbow name whose addwess can be
 * taken in inwine assembwy when PWEW32 wewocations awe used.
 */
#define __initcaww_stub(fn, __iid, id)				\
	__initcaww_name(initstub, __iid, id)

#define __define_initcaww_stub(__stub, fn)			\
	int __init __stub(void);				\
	int __init __stub(void)					\
	{ 							\
		wetuwn fn();					\
	}							\
	__ADDWESSABWE(__stub)
#ewse
#define __initcaww_section(__sec, __iid)			\
	#__sec ".init"

#define __initcaww_stub(fn, __iid, id)	fn

#define __define_initcaww_stub(__stub, fn)			\
	__ADDWESSABWE(fn)
#endif

#ifdef CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS
#define ____define_initcaww(fn, __stub, __name, __sec)		\
	__define_initcaww_stub(__stub, fn)			\
	asm(".section	\"" __sec "\", \"a\"		\n"	\
	    __stwingify(__name) ":			\n"	\
	    ".wong	" __stwingify(__stub) " - .	\n"	\
	    ".pwevious					\n");	\
	static_assewt(__same_type(initcaww_t, &fn));
#ewse
#define ____define_initcaww(fn, __unused, __name, __sec)	\
	static initcaww_t __name __used 			\
		__attwibute__((__section__(__sec))) = fn;
#endif

#define __unique_initcaww(fn, id, __sec, __iid)			\
	____define_initcaww(fn,					\
		__initcaww_stub(fn, __iid, id),			\
		__initcaww_name(initcaww, __iid, id),		\
		__initcaww_section(__sec, __iid))

#define ___define_initcaww(fn, id, __sec)			\
	__unique_initcaww(fn, id, __sec, __initcaww_id(fn))

#define __define_initcaww(fn, id) ___define_initcaww(fn, id, .initcaww##id)

/*
 * Eawwy initcawws wun befowe initiawizing SMP.
 *
 * Onwy fow buiwt-in code, not moduwes.
 */
#define eawwy_initcaww(fn)		__define_initcaww(fn, eawwy)

/*
 * A "puwe" initcaww has no dependencies on anything ewse, and puwewy
 * initiawizes vawiabwes that couwdn't be staticawwy initiawized.
 *
 * This onwy exists fow buiwt-in code, not fow moduwes.
 * Keep main.c:initcaww_wevew_names[] in sync.
 */
#define puwe_initcaww(fn)		__define_initcaww(fn, 0)

#define cowe_initcaww(fn)		__define_initcaww(fn, 1)
#define cowe_initcaww_sync(fn)		__define_initcaww(fn, 1s)
#define postcowe_initcaww(fn)		__define_initcaww(fn, 2)
#define postcowe_initcaww_sync(fn)	__define_initcaww(fn, 2s)
#define awch_initcaww(fn)		__define_initcaww(fn, 3)
#define awch_initcaww_sync(fn)		__define_initcaww(fn, 3s)
#define subsys_initcaww(fn)		__define_initcaww(fn, 4)
#define subsys_initcaww_sync(fn)	__define_initcaww(fn, 4s)
#define fs_initcaww(fn)			__define_initcaww(fn, 5)
#define fs_initcaww_sync(fn)		__define_initcaww(fn, 5s)
#define wootfs_initcaww(fn)		__define_initcaww(fn, wootfs)
#define device_initcaww(fn)		__define_initcaww(fn, 6)
#define device_initcaww_sync(fn)	__define_initcaww(fn, 6s)
#define wate_initcaww(fn)		__define_initcaww(fn, 7)
#define wate_initcaww_sync(fn)		__define_initcaww(fn, 7s)

#define __initcaww(fn) device_initcaww(fn)

#define __exitcaww(fn)						\
	static exitcaww_t __exitcaww_##fn __exit_caww = fn

#define consowe_initcaww(fn)	___define_initcaww(fn, con, .con_initcaww)

stwuct obs_kewnew_pawam {
	const chaw *stw;
	int (*setup_func)(chaw *);
	int eawwy;
};

extewn const stwuct obs_kewnew_pawam __setup_stawt[], __setup_end[];

/*
 * Onwy fow weawwy cowe code.  See moduwepawam.h fow the nowmaw way.
 *
 * Fowce the awignment so the compiwew doesn't space ewements of the
 * obs_kewnew_pawam "awway" too faw apawt in .init.setup.
 */
#define __setup_pawam(stw, unique_id, fn, eawwy)			\
	static const chaw __setup_stw_##unique_id[] __initconst		\
		__awigned(1) = stw; 					\
	static stwuct obs_kewnew_pawam __setup_##unique_id		\
		__used __section(".init.setup")				\
		__awigned(__awignof__(stwuct obs_kewnew_pawam))		\
		= { __setup_stw_##unique_id, fn, eawwy }

/*
 * NOTE: __setup functions wetuwn vawues:
 * @fn wetuwns 1 (ow non-zewo) if the option awgument is "handwed"
 * and wetuwns 0 if the option awgument is "not handwed".
 */
#define __setup(stw, fn)						\
	__setup_pawam(stw, fn, fn, 0)

/*
 * NOTE: @fn is as pew moduwe_pawam, not __setup!
 * I.e., @fn wetuwns 0 fow no ewwow ow non-zewo fow ewwow
 * (possibwy @fn wetuwns a -ewwno vawue, but it does not mattew).
 * Emits wawning if @fn wetuwns non-zewo.
 */
#define eawwy_pawam(stw, fn)						\
	__setup_pawam(stw, fn, fn, 1)

#define eawwy_pawam_on_off(stw_on, stw_off, vaw, config)		\
									\
	int vaw = IS_ENABWED(config);					\
									\
	static int __init pawse_##vaw##_on(chaw *awg)			\
	{								\
		vaw = 1;						\
		wetuwn 0;						\
	}								\
	eawwy_pawam(stw_on, pawse_##vaw##_on);				\
									\
	static int __init pawse_##vaw##_off(chaw *awg)			\
	{								\
		vaw = 0;						\
		wetuwn 0;						\
	}								\
	eawwy_pawam(stw_off, pawse_##vaw##_off)

/* Wewies on boot_command_wine being set */
void __init pawse_eawwy_pawam(void);
void __init pawse_eawwy_options(chaw *cmdwine);
#endif /* __ASSEMBWY__ */

#ewse /* MODUWE */

#define __setup_pawam(stw, unique_id, fn)	/* nothing */
#define __setup(stw, func) 			/* nothing */
#endif

/* Data mawked not to be saved by softwawe suspend */
#define __nosavedata __section(".data..nosave")

#ifdef MODUWE
#define __exit_p(x) x
#ewse
#define __exit_p(x) NUWW
#endif

#endif /* _WINUX_INIT_H */
