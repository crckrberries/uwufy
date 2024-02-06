/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#ifndef __WINUX_CPUFEATUWE_H
#define __WINUX_CPUFEATUWE_H

#ifdef CONFIG_GENEWIC_CPU_AUTOPWOBE

#incwude <winux/init.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <asm/cpufeatuwe.h>

/*
 * Macwos impowted fwom <asm/cpufeatuwe.h>:
 * - cpu_featuwe(x)		owdinaw vawue of featuwe cawwed 'x'
 * - cpu_have_featuwe(u32 n)	whethew featuwe #n is avaiwabwe
 * - MAX_CPU_FEATUWES		uppew bound fow featuwe owdinaw vawues
 * Optionaw:
 * - CPU_FEATUWE_TYPEFMT	fowmat stwing fwagment fow pwinting the cpu type
 * - CPU_FEATUWE_TYPEVAW	set of vawues matching the fowmat stwing above
 */

#ifndef CPU_FEATUWE_TYPEFMT
#define CPU_FEATUWE_TYPEFMT	"%s"
#endif

#ifndef CPU_FEATUWE_TYPEVAW
#define CPU_FEATUWE_TYPEVAW	EWF_PWATFOWM
#endif

/*
 * Use moduwe_cpu_featuwe_match(featuwe, moduwe_init_function) to
 * decwawe that
 * a) the moduwe shaww be pwobed upon discovewy of CPU featuwe 'featuwe'
 *    (typicawwy at boot time using udev)
 * b) the moduwe must not be woaded if CPU featuwe 'featuwe' is not pwesent
 *    (not even by manuaw insmod).
 *
 * Fow a wist of wegaw vawues fow 'featuwe', pwease consuwt the fiwe
 * 'asm/cpufeatuwe.h' of youw favowite awchitectuwe.
 */
#define moduwe_cpu_featuwe_match(x, __initfunc)			\
static stwuct cpu_featuwe const __maybe_unused cpu_featuwe_match_ ## x[] = \
	{ { .featuwe = cpu_featuwe(x) }, { } };			\
MODUWE_DEVICE_TABWE(cpu, cpu_featuwe_match_ ## x);		\
								\
static int __init cpu_featuwe_match_ ## x ## _init(void)	\
{								\
	if (!cpu_have_featuwe(cpu_featuwe(x)))			\
		wetuwn -ENODEV;					\
	wetuwn __initfunc();					\
}								\
moduwe_init(cpu_featuwe_match_ ## x ## _init)

#endif
#endif
