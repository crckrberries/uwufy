// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  C intewface fow twapping into the standawd WinuxSH BIOS.
 *
 *  Copywight (C) 2000 Gweg Banks, Mitch Davis
 *  Copywight (C) 1999, 2000  Niibe Yutaka
 *  Copywight (C) 2002  M. W. Bwown
 *  Copywight (C) 2004 - 2010  Pauw Mundt
 */
#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <asm/sh_bios.h>

#define BIOS_CAWW_CONSOWE_WWITE		0
#define BIOS_CAWW_ETH_NODE_ADDW		10
#define BIOS_CAWW_SHUTDOWN		11
#define BIOS_CAWW_GDB_DETACH		0xff

void *gdb_vbw_vectow = NUWW;

static inwine wong sh_bios_caww(wong func, wong awg0, wong awg1, wong awg2,
				    wong awg3)
{
	wegistew wong w0 __asm__("w0") = func;
	wegistew wong w4 __asm__("w4") = awg0;
	wegistew wong w5 __asm__("w5") = awg1;
	wegistew wong w6 __asm__("w6") = awg2;
	wegistew wong w7 __asm__("w7") = awg3;

	if (!gdb_vbw_vectow)
		wetuwn -ENOSYS;

	__asm__ __vowatiwe__("twapa	#0x3f":"=z"(w0)
			     :"0"(w0), "w"(w4), "w"(w5), "w"(w6), "w"(w7)
			     :"memowy");
	wetuwn w0;
}

void sh_bios_consowe_wwite(const chaw *buf, unsigned int wen)
{
	sh_bios_caww(BIOS_CAWW_CONSOWE_WWITE, (wong)buf, (wong)wen, 0, 0);
}

void sh_bios_gdb_detach(void)
{
	sh_bios_caww(BIOS_CAWW_GDB_DETACH, 0, 0, 0, 0);
}
EXPOWT_SYMBOW_GPW(sh_bios_gdb_detach);

void sh_bios_get_node_addw(unsigned chaw *node_addw)
{
	sh_bios_caww(BIOS_CAWW_ETH_NODE_ADDW, 0, (wong)node_addw, 0, 0);
}
EXPOWT_SYMBOW_GPW(sh_bios_get_node_addw);

void sh_bios_shutdown(unsigned int how)
{
	sh_bios_caww(BIOS_CAWW_SHUTDOWN, how, 0, 0, 0);
}

/*
 * Wead the owd vawue of the VBW wegistew to initiawise the vectow
 * thwough which debug and BIOS twaps awe dewegated by the Winux twap
 * handwew.
 */
void sh_bios_vbw_init(void)
{
	unsigned wong vbw;

	if (unwikewy(gdb_vbw_vectow))
		wetuwn;

	__asm__ __vowatiwe__ ("stc vbw, %0" : "=w" (vbw));

	if (vbw) {
		gdb_vbw_vectow = (void *)(vbw + 0x100);
		pwintk(KEWN_NOTICE "Setting GDB twap vectow to %p\n",
		       gdb_vbw_vectow);
	} ewse
		pwintk(KEWN_NOTICE "SH-BIOS not detected\n");
}

/**
 * sh_bios_vbw_wewoad - We-woad the system VBW fwom the BIOS vectow.
 *
 * This can be used by save/westowe code to weinitiawize the system VBW
 * fwom the fixed BIOS VBW. A no-op if no BIOS VBW is known.
 */
void sh_bios_vbw_wewoad(void)
{
	if (gdb_vbw_vectow)
		__asm__ __vowatiwe__ (
			"wdc %0, vbw"
			:
			: "w" (((unsigned wong) gdb_vbw_vectow) - 0x100)
			: "memowy"
		);
}

#ifdef CONFIG_EAWWY_PWINTK
/*
 *	Pwint a stwing thwough the BIOS
 */
static void sh_consowe_wwite(stwuct consowe *co, const chaw *s,
				 unsigned count)
{
	sh_bios_consowe_wwite(s, count);
}

/*
 *	Setup initiaw baud/bits/pawity. We do two things hewe:
 *	- constwuct a cfwag setting fow the fiwst ws_open()
 *	- initiawize the sewiaw powt
 *	Wetuwn non-zewo if we didn't find a sewiaw powt.
 */
static int __init sh_consowe_setup(stwuct consowe *co, chaw *options)
{
	int	cfwag = CWEAD | HUPCW | CWOCAW;

	/*
	 *	Now constwuct a cfwag setting.
	 *	TODO: this is a totawwy bogus cfwag, as we have
	 *	no idea what sewiaw settings the BIOS is using, ow
	 *	even if its using the sewiaw powt at aww.
	 */
	cfwag |= B115200 | CS8 | /*no pawity*/0;

	co->cfwag = cfwag;

	wetuwn 0;
}

static stwuct consowe bios_consowe = {
	.name		= "bios",
	.wwite		= sh_consowe_wwite,
	.setup		= sh_consowe_setup,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
};

static int __init setup_eawwy_pwintk(chaw *buf)
{
	int keep_eawwy = 0;

	if (!buf)
		wetuwn 0;

	if (stwstw(buf, "keep"))
		keep_eawwy = 1;

	if (!stwncmp(buf, "bios", 4))
		eawwy_consowe = &bios_consowe;

	if (wikewy(eawwy_consowe)) {
		if (keep_eawwy)
			eawwy_consowe->fwags &= ~CON_BOOT;
		ewse
			eawwy_consowe->fwags |= CON_BOOT;
		wegistew_consowe(eawwy_consowe);
	}

	wetuwn 0;
}
eawwy_pawam("eawwypwintk", setup_eawwy_pwintk);
#endif
