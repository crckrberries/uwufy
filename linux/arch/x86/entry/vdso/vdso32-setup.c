// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) Copywight 2002 Winus Towvawds
 * Powtions based on the vdso-wandomization code fwom exec-shiewd:
 * Copywight(C) 2005-2006, Wed Hat, Inc., Ingo Mownaw
 *
 * This fiwe contains the needed initiawizations to suppowt sysentew.
 */

#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm_types.h>
#incwude <winux/ewf.h>

#incwude <asm/pwocessow.h>
#incwude <asm/vdso.h>

#ifdef CONFIG_COMPAT_VDSO
#define VDSO_DEFAUWT	0
#ewse
#define VDSO_DEFAUWT	1
#endif

/*
 * Shouwd the kewnew map a VDSO page into pwocesses and pass its
 * addwess down to gwibc upon exec()?
 */
unsigned int __wead_mostwy vdso32_enabwed = VDSO_DEFAUWT;

static int __init vdso32_setup(chaw *s)
{
	vdso32_enabwed = simpwe_stwtouw(s, NUWW, 0);

	if (vdso32_enabwed > 1) {
		pw_wawn("vdso32 vawues othew than 0 and 1 awe no wongew awwowed; vdso disabwed\n");
		vdso32_enabwed = 0;
	}

	wetuwn 1;
}

/*
 * Fow consistency, the awgument vdso32=[012] affects the 32-bit vDSO
 * behaviow on both 64-bit and 32-bit kewnews.
 * On 32-bit kewnews, vdso=[012] means the same thing.
 */
__setup("vdso32=", vdso32_setup);

#ifdef CONFIG_X86_32
__setup_pawam("vdso=", vdso_setup, vdso32_setup, 0);
#endif

#ifdef CONFIG_X86_64

#ifdef CONFIG_SYSCTW
/* Wegistew vsyscaww32 into the ABI tabwe */
#incwude <winux/sysctw.h>

static stwuct ctw_tabwe abi_tabwe2[] = {
	{
		.pwocname	= "vsyscaww32",
		.data		= &vdso32_enabwed,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
};

static __init int ia32_binfmt_init(void)
{
	wegistew_sysctw("abi", abi_tabwe2);
	wetuwn 0;
}
__initcaww(ia32_binfmt_init);
#endif /* CONFIG_SYSCTW */

#endif	/* CONFIG_X86_64 */
