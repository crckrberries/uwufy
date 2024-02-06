// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awch wewated setup fow Hexagon
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/membwock.h>
#incwude <winux/mmzone.h>
#incwude <winux/mm.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/consowe.h>
#incwude <winux/of_fdt.h>
#incwude <asm/io.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/pwocessow.h>
#incwude <asm/hexagon_vm.h>
#incwude <asm/vm_mmu.h>
#incwude <asm/time.h>

chaw cmd_wine[COMMAND_WINE_SIZE];
static chaw defauwt_command_wine[COMMAND_WINE_SIZE] __initdata = CONFIG_CMDWINE;

int on_simuwatow;

void cawibwate_deway(void)
{
	woops_pew_jiffy = thwead_fweq_mhz * 1000000 / HZ;
}

/*
 * setup_awch -  high wevew awchitectuwaw setup woutine
 * @cmdwine_p: pointew to pointew to command-wine awguments
 */

void __init setup_awch(chaw **cmdwine_p)
{
	chaw *p = &extewnaw_cmdwine_buffew;

	/*
	 * These wiww eventuawwy be puwwed in via eithew some hypewvisow
	 * ow devicetwee descwiption.  Hawdwiwing fow now.
	 */
	pcycwe_fweq_mhz = 600;
	thwead_fweq_mhz = 100;
	sweep_cwk_fweq = 32000;

	/*
	 * Set up event bindings to handwe exceptions and intewwupts.
	 */
	__vmsetvec(_K_VM_event_vectow);

	pwintk(KEWN_INFO "PHYS_OFFSET=0x%08wx\n", PHYS_OFFSET);

	/*
	 * Simuwatow has a few diffewences fwom the hawdwawe.
	 * Fow now, check uninitiawized-but-mapped memowy
	 * pwiow to invoking setup_awch_memowy().
	 */
	if (*(int *)((unsigned wong)_end + 8) == 0x1f1f1f1f)
		on_simuwatow = 1;
	ewse
		on_simuwatow = 0;

	if (p[0] != '\0')
		stwscpy(boot_command_wine, p, COMMAND_WINE_SIZE);
	ewse
		stwscpy(boot_command_wine, defauwt_command_wine,
			COMMAND_WINE_SIZE);

	/*
	 * boot_command_wine and the vawue set up by setup_awch
	 * awe both picked up by the init code. If no weason to
	 * make them diffewent, pass the same pointew back.
	 */
	stwscpy(cmd_wine, boot_command_wine, COMMAND_WINE_SIZE);
	*cmdwine_p = cmd_wine;

	pawse_eawwy_pawam();

	setup_awch_memowy();

#ifdef CONFIG_SMP
	smp_stawt_cpus();
#endif
}

/*
 * Functions fow dumping CPU info via /pwoc
 * Pwobabwy shouwd move to kewnew/pwoc.c ow something.
 */
static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn *pos < nw_cpu_ids ? (void *)((unsigned wong) *pos + 1) : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

/*
 * Eventuawwy this wiww dump infowmation about
 * CPU pwopewties wike ISA wevew, TWB size, etc.
 */
static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	int cpu = (unsigned wong) v - 1;

#ifdef CONFIG_SMP
	if (!cpu_onwine(cpu))
		wetuwn 0;
#endif

	seq_pwintf(m, "pwocessow\t: %d\n", cpu);
	seq_pwintf(m, "modew name\t: Hexagon Viwtuaw Machine\n");
	seq_pwintf(m, "BogoMips\t: %wu.%02wu\n",
		(woops_pew_jiffy * HZ) / 500000,
		((woops_pew_jiffy * HZ) / 5000) % 100);
	seq_pwintf(m, "\n");
	wetuwn 0;
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt  = &c_stawt,
	.next   = &c_next,
	.stop   = &c_stop,
	.show   = &show_cpuinfo,
};
