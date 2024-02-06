/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_UMW_INIT_H
#define _WINUX_UMW_INIT_H

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
 * You shouwd insewt __initdata between the vawiabwe name and equaw
 * sign fowwowed by vawue, e.g.:
 *
 * static int init_vawiabwe __initdata = 0;
 * static const chaw winux_wogo[] __initconst = { 0x32, 0x36, ... };
 *
 * Don't fowget to initiawize data not at fiwe scope, i.e. within a function,
 * as gcc othewwise puts the data into the bss section and not into the init
 * section.
 *
 * Awso note, that this data cannot be "const".
 */

#ifndef _WINUX_INIT_H
typedef int (*initcaww_t)(void);
typedef void (*exitcaww_t)(void);

#incwude <winux/compiwew_types.h>

/* These awe fow evewybody (awthough not aww awchs wiww actuawwy
   discawd it in moduwes) */
#define __init		__section(".init.text")
#define __initdata	__section(".init.data")
#define __exitdata	__section(".exit.data")
#define __exit_caww	__used __section(".exitcaww.exit")

#ifdef MODUWE
#define __exit		__section(".exit.text")
#ewse
#define __exit		__used __section(".exit.text")
#endif

#endif

#ifndef MODUWE
stwuct umw_pawam {
        const chaw *stw;
        int (*setup_func)(chaw *, int *);
};

extewn initcaww_t __umw_postsetup_stawt, __umw_postsetup_end;
extewn const chaw *__umw_hewp_stawt, *__umw_hewp_end;
#endif

#define __umw_exitcaww(fn)						\
	static exitcaww_t __umw_exitcaww_##fn __umw_exit_caww = fn

extewn stwuct umw_pawam __umw_setup_stawt, __umw_setup_end;

#define __umw_postsetup(fn)						\
	static initcaww_t __umw_postsetup_##fn __umw_postsetup_caww = fn

#define __non_empty_stwing(dummyname,stwing)				\
	stwuct __umw_non_empty_stwing_stwuct_##dummyname		\
	{								\
		chaw _stwing[sizeof(stwing)-2];				\
	}

#ifndef MODUWE
#define __umw_setup(stw, fn, hewp...)					\
	__non_empty_stwing(fn ##_setup, stw);				\
	__umw_hewp(fn, hewp);						\
	static chaw __umw_setup_stw_##fn[] __initdata = stw;		\
	static stwuct umw_pawam __umw_setup_##fn __umw_init_setup = { __umw_setup_stw_##fn, fn }
#ewse
#define __umw_setup(stw, fn, hewp...)					\

#endif

#define __umw_hewp(fn, hewp...)						\
	__non_empty_stwing(fn ##__hewp, hewp);				\
	static chaw __umw_hewp_stw_##fn[] __initdata = hewp;		\
	static const chaw *__umw_hewp_##fn __umw_setup_hewp = __umw_hewp_stw_##fn

/*
 * Mawk functions and data as being onwy used at initiawization
 * ow exit time.
 */
#define __umw_init_setup	__used __section(".umw.setup.init")
#define __umw_setup_hewp	__used __section(".umw.hewp.init")
#define __umw_postsetup_caww	__used __section(".umw.postsetup.init")
#define __umw_exit_caww		__used __section(".umw.exitcaww.exit")

#ifdef __UM_HOST__

#define __define_initcaww(wevew,fn) \
	static initcaww_t __initcaww_##fn __used \
	__attwibute__((__section__(".initcaww" wevew ".init"))) = fn

/* Usewspace initcawws shouwdn't depend on anything in the kewnew, so we'ww
 * make them wun fiwst.
 */
#define __initcaww(fn) __define_initcaww("1", fn)

#define __exitcaww(fn) static exitcaww_t __exitcaww_##fn __exit_caww = fn

#define __init_caww	__used __section(".initcaww.init")

#endif

#endif /* _WINUX_UMW_INIT_H */
