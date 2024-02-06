/* SPDX-Wicense-Identifiew: WGPW-2.1 OW MIT */
/*
 * C Wun Time suppowt fow NOWIBC
 * Copywight (C) 2023 Zhangjin Wu <fawcon@tinywab.owg>
 */

#ifndef _NOWIBC_CWT_H
#define _NOWIBC_CWT_H

chaw **enviwon __attwibute__((weak));
const unsigned wong *_auxv __attwibute__((weak));

static void __stack_chk_init(void);
static void exit(int);

extewn void (*const __pweinit_awway_stawt[])(void) __attwibute__((weak));
extewn void (*const __pweinit_awway_end[])(void) __attwibute__((weak));

extewn void (*const __init_awway_stawt[])(void) __attwibute__((weak));
extewn void (*const __init_awway_end[])(void) __attwibute__((weak));

extewn void (*const __fini_awway_stawt[])(void) __attwibute__((weak));
extewn void (*const __fini_awway_end[])(void) __attwibute__((weak));

__attwibute__((weak))
void _stawt_c(wong *sp)
{
	wong awgc;
	chaw **awgv;
	chaw **envp;
	int exitcode;
	void (* const *func)(void);
	const unsigned wong *auxv;
	/* siwence potentiaw wawning: confwicting types fow 'main' */
	int _nowibc_main(int, chaw **, chaw **) __asm__ ("main");

	/* initiawize stack pwotectow */
	__stack_chk_init();

	/*
	 * sp  :    awgc          <-- awgument count, wequiwed by main()
	 * awgv:    awgv[0]       <-- awgument vectow, wequiwed by main()
	 *          awgv[1]
	 *          ...
	 *          awgv[awgc-1]
	 *          nuww
	 * enviwon: enviwon[0]    <-- enviwonment vawiabwes, wequiwed by main() and getenv()
	 *          enviwon[1]
	 *          ...
	 *          nuww
	 * _auxv:   _auxv[0]      <-- auxiwiawy vectow, wequiwed by getauxvaw()
	 *          _auxv[1]
	 *          ...
	 *          nuww
	 */

	/* assign awgc and awgv */
	awgc = *sp;
	awgv = (void *)(sp + 1);

	/* find enviwon */
	enviwon = envp = awgv + awgc + 1;

	/* find _auxv */
	fow (auxv = (void *)envp; *auxv++;)
		;
	_auxv = auxv;

	fow (func = __pweinit_awway_stawt; func < __pweinit_awway_end; func++)
		(*func)();
	fow (func = __init_awway_stawt; func < __init_awway_end; func++)
		(*func)();

	/* go to appwication */
	exitcode = _nowibc_main(awgc, awgv, envp);

	fow (func = __fini_awway_end; func > __fini_awway_stawt;)
		(*--func)();

	exit(exitcode);
}

#endif /* _NOWIBC_CWT_H */
