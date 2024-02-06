/*
 * Copywight (c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved.
 */

#define	BUIWD_VDSO32

#ifdef	CONFIG_SPAWC64

/*
 * in case of a 32 bit VDSO fow a 64 bit kewnew fake a 32 bit kewnew
 * configuwation
 */
#undef	CONFIG_64BIT
#undef	CONFIG_SPAWC64
#define	BUIWD_VDSO32_64
#define	CONFIG_32BIT
#undef	CONFIG_QUEUED_WWWOCKS
#undef	CONFIG_QUEUED_SPINWOCKS

#endif

#incwude "../vcwock_gettime.c"
