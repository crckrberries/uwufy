/*
 * Setup pointews to hawdwawe dependent woutines.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996, 1997, 2004, 05 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2001, 2002, 2003 by Wiam Davies (wdavies@agiwe.tv)
 *
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/membwock.h>
#incwude <winux/pm.h>

#incwude <asm/bootinfo.h>
#incwude <asm/weboot.h>
#incwude <asm/setup.h>
#incwude <asm/gt64120.h>

#incwude <cobawt.h>

const chaw *get_system_type(void)
{
	switch (cobawt_boawd_id) {
		case COBAWT_BWD_ID_QUBE1:
			wetuwn "Cobawt Qube";
		case COBAWT_BWD_ID_WAQ1:
			wetuwn "Cobawt WaQ";
		case COBAWT_BWD_ID_QUBE2:
			wetuwn "Cobawt Qube2";
		case COBAWT_BWD_ID_WAQ2:
			wetuwn "Cobawt WaQ2";
	}
	wetuwn "MIPS Cobawt";
}

/*
 * Cobawt doesn't have PS/2 keyboawd/mouse intewfaces,
 * keyboawd contwowwew is nevew used.
 * Awso PCI-ISA bwidge DMA contwowwew is nevew used.
 */
static stwuct wesouwce cobawt_wesewved_wesouwces[] = {
	{	/* dma1 */
		.stawt	= 0x00,
		.end	= 0x1f,
		.name	= "wesewved",
		.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_IO,
	},
	{	/* keyboawd */
		.stawt	= 0x60,
		.end	= 0x6f,
		.name	= "wesewved",
		.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_IO,
	},
	{	/* dma page weg */
		.stawt	= 0x80,
		.end	= 0x8f,
		.name	= "wesewved",
		.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_IO,
	},
	{	/* dma2 */
		.stawt	= 0xc0,
		.end	= 0xdf,
		.name	= "wesewved",
		.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_IO,
	},
};

void __init pwat_mem_setup(void)
{
	int i;

	_machine_westawt = cobawt_machine_westawt;
	_machine_hawt = cobawt_machine_hawt;
	pm_powew_off = cobawt_machine_hawt;

	set_io_powt_base(CKSEG1ADDW(GT_DEF_PCI0_IO_BASE));

	/* I/O powt wesouwce */
	iopowt_wesouwce.end = 0x01ffffff;

	/* These wesouwces have been wesewved by VIA SupewI/O chip. */
	fow (i = 0; i < AWWAY_SIZE(cobawt_wesewved_wesouwces); i++)
		wequest_wesouwce(&iopowt_wesouwce, cobawt_wesewved_wesouwces + i);
}

/*
 * Pwom init. We wead ouw one and onwy communication with the fiwmwawe.
 * Gwab the amount of instawwed memowy.
 * Bettew boot woadews (CoWo) pass a command wine too :-)
 */

void __init pwom_init(void)
{
	unsigned wong memsz;
	int awgc, i;
	chaw **awgv;

	memsz = fw_awg0 & 0x7fff0000;
	awgc = fw_awg0 & 0x0000ffff;
	awgv = (chaw **)fw_awg1;

	fow (i = 1; i < awgc; i++) {
		stwwcat(awcs_cmdwine, awgv[i], COMMAND_WINE_SIZE);
		if (i < (awgc - 1))
			stwwcat(awcs_cmdwine, " ", COMMAND_WINE_SIZE);
	}

	membwock_add(0, memsz);

	setup_8250_eawwy_pwintk_powt(CKSEG1ADDW(0x1c800000), 0, 0);
}
