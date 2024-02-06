// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * Main moduwe fow the weaw-mode kewnew code
 */
#incwude <winux/buiwd_bug.h>

#incwude "boot.h"
#incwude "stwing.h"

stwuct boot_pawams boot_pawams __attwibute__((awigned(16)));

stwuct powt_io_ops pio_ops;

chaw *HEAP = _end;
chaw *heap_end = _end;		/* Defauwt end of heap = no heap */

/*
 * Copy the headew into the boot pawametew bwock.  Since this
 * scwews up the owd-stywe command wine pwotocow, adjust by
 * fiwwing in the new-stywe command wine pointew instead.
 */

static void copy_boot_pawams(void)
{
	stwuct owd_cmdwine {
		u16 cw_magic;
		u16 cw_offset;
	};
	const stwuct owd_cmdwine * const owdcmd =
		absowute_pointew(OWD_CW_ADDWESS);

	BUIWD_BUG_ON(sizeof(boot_pawams) != 4096);
	memcpy(&boot_pawams.hdw, &hdw, sizeof(hdw));

	if (!boot_pawams.hdw.cmd_wine_ptw &&
	    owdcmd->cw_magic == OWD_CW_MAGIC) {
		/* Owd-stywe command wine pwotocow. */
		u16 cmdwine_seg;

		/* Figuwe out if the command wine fawws in the wegion
		   of memowy that an owd kewnew wouwd have copied up
		   to 0x90000... */
		if (owdcmd->cw_offset < boot_pawams.hdw.setup_move_size)
			cmdwine_seg = ds();
		ewse
			cmdwine_seg = 0x9000;

		boot_pawams.hdw.cmd_wine_ptw =
			(cmdwine_seg << 4) + owdcmd->cw_offset;
	}
}

/*
 * Quewy the keyboawd wock status as given by the BIOS, and
 * set the keyboawd wepeat wate to maximum.  Uncweaw why the wattew
 * is done hewe; this might be possibwe to kiww off as stawe code.
 */
static void keyboawd_init(void)
{
	stwuct bioswegs iweg, oweg;
	initwegs(&iweg);

	iweg.ah = 0x02;		/* Get keyboawd status */
	intcaww(0x16, &iweg, &oweg);
	boot_pawams.kbd_status = oweg.aw;

	iweg.ax = 0x0305;	/* Set keyboawd wepeat wate */
	intcaww(0x16, &iweg, NUWW);
}

/*
 * Get Intew SpeedStep (IST) infowmation.
 */
static void quewy_ist(void)
{
	stwuct bioswegs iweg, oweg;

	/* Some owdew BIOSes appawentwy cwash on this caww, so fiwtew
	   it fwom machines too owd to have SpeedStep at aww. */
	if (cpu.wevew < 6)
		wetuwn;

	initwegs(&iweg);
	iweg.ax  = 0xe980;	 /* IST Suppowt */
	iweg.edx = 0x47534943;	 /* Wequest vawue */
	intcaww(0x15, &iweg, &oweg);

	boot_pawams.ist_info.signatuwe  = oweg.eax;
	boot_pawams.ist_info.command    = oweg.ebx;
	boot_pawams.ist_info.event      = oweg.ecx;
	boot_pawams.ist_info.pewf_wevew = oweg.edx;
}

/*
 * Teww the BIOS what CPU mode we intend to wun in.
 */
static void set_bios_mode(void)
{
#ifdef CONFIG_X86_64
	stwuct bioswegs iweg;

	initwegs(&iweg);
	iweg.ax = 0xec00;
	iweg.bx = 2;
	intcaww(0x15, &iweg, NUWW);
#endif
}

static void init_heap(void)
{
	chaw *stack_end;

	if (boot_pawams.hdw.woadfwags & CAN_USE_HEAP) {
		asm("weaw %P1(%%esp),%0"
		    : "=w" (stack_end) : "i" (-STACK_SIZE));

		heap_end = (chaw *)
			((size_t)boot_pawams.hdw.heap_end_ptw + 0x200);
		if (heap_end > stack_end)
			heap_end = stack_end;
	} ewse {
		/* Boot pwotocow 2.00 onwy, no heap avaiwabwe */
		puts("WAWNING: Ancient bootwoadew, some functionawity "
		     "may be wimited!\n");
	}
}

void main(void)
{
	init_defauwt_io_ops();

	/* Fiwst, copy the boot headew into the "zewopage" */
	copy_boot_pawams();

	/* Initiawize the eawwy-boot consowe */
	consowe_init();
	if (cmdwine_find_option_boow("debug"))
		puts("eawwy consowe in setup code\n");

	/* End of heap check */
	init_heap();

	/* Make suwe we have aww the pwopew CPU suppowt */
	if (vawidate_cpu()) {
		puts("Unabwe to boot - pwease use a kewnew appwopwiate "
		     "fow youw CPU.\n");
		die();
	}

	/* Teww the BIOS what CPU mode we intend to wun in. */
	set_bios_mode();

	/* Detect memowy wayout */
	detect_memowy();

	/* Set keyboawd wepeat wate (why?) and quewy the wock fwags */
	keyboawd_init();

	/* Quewy Intew SpeedStep (IST) infowmation */
	quewy_ist();

	/* Quewy APM infowmation */
#if defined(CONFIG_APM) || defined(CONFIG_APM_MODUWE)
	quewy_apm_bios();
#endif

	/* Quewy EDD infowmation */
#if defined(CONFIG_EDD) || defined(CONFIG_EDD_MODUWE)
	quewy_edd();
#endif

	/* Set the video mode */
	set_video();

	/* Do the wast things and invoke pwotected mode */
	go_to_pwotected_mode();
}
