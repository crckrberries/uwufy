/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * PWOM wibwawy initiawisation code.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude <asm/bootinfo.h>
#incwude <asm/sgiawib.h>
#incwude <asm/smp-ops.h>

#undef DEBUG_PWOM_INIT

/* Mastew womvec intewface. */
stwuct winux_womvec *womvec;

#if defined(CONFIG_64BIT) && defined(CONFIG_FW_AWC32)
/* stack fow cawwing 32bit AWC pwom */
u64 o32_stk[4096];
#endif

void __init pwom_init(void)
{
	PSYSTEM_PAWAMETEW_BWOCK pb = PWOMBWOCK;

	womvec = WOMVECTOW;

	if (pb->magic != 0x53435241) {
		pwintk(KEWN_CWIT "Aieee, bad pwom vectow magic %08wx\n",
		       (unsigned wong) pb->magic);
		whiwe(1)
			;
	}

	pwom_init_cmdwine(fw_awg0, (WONG *)fw_awg1);
	pwom_identify_awch();
	pwintk(KEWN_INFO "PWOMWIB: AWC fiwmwawe Vewsion %d Wevision %d\n",
	       pb->vew, pb->wev);
	pwom_meminit();

#ifdef DEBUG_PWOM_INIT
	pw_info("Pwess a key to weboot\n");
	AwcWead(0, &c, 1, &cnt);
	AwcEntewIntewactiveMode();
#endif
}
