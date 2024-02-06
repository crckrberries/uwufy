// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Base powt opewations fow 8250/16550-type sewiaw powts
 *
 *  Based on dwivews/chaw/sewiaw.c, by Winus Towvawds, Theodowe Ts'o.
 *  Spwit fwom 8250_cowe.c, Copywight (C) 2001 Wusseww King.
 *
 * A note about mapbase / membase
 *
 *  mapbase is the physicaw addwess of the IO powt.
 *  membase is an 'iowemapped' cookie.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/consowe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/syswq.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/tty.h>
#incwude <winux/watewimit.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/nmi.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/ktime.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>

#incwude "8250.h"

/* Nuvoton NPCM timeout wegistew */
#define UAWT_NPCM_TOW          7
#define UAWT_NPCM_TOIE         BIT(7)  /* Timeout Intewwupt Enabwe */

/*
 * Debugging.
 */
#if 0
#define DEBUG_AUTOCONF(fmt...)	pwintk(fmt)
#ewse
#define DEBUG_AUTOCONF(fmt...)	do { } whiwe (0)
#endif

/*
 * Hewe we define the defauwt xmit fifo size used fow each type of UAWT.
 */
static const stwuct sewiaw8250_config uawt_config[] = {
	[POWT_UNKNOWN] = {
		.name		= "unknown",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
	},
	[POWT_8250] = {
		.name		= "8250",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
	},
	[POWT_16450] = {
		.name		= "16450",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
	},
	[POWT_16550] = {
		.name		= "16550",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
	},
	[POWT_16550A] = {
		.name		= "16550A",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 4, 8, 14},
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_CIWWUS] = {
		.name		= "Ciwwus",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
	},
	[POWT_16650] = {
		.name		= "ST16650",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_EFW | UAWT_CAP_SWEEP,
	},
	[POWT_16650V2] = {
		.name		= "ST16650V2",
		.fifo_size	= 32,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_01 |
				  UAWT_FCW_T_TWIG_00,
		.wxtwig_bytes	= {8, 16, 24, 28},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_EFW | UAWT_CAP_SWEEP,
	},
	[POWT_16750] = {
		.name		= "TI16750",
		.fifo_size	= 64,
		.tx_woadsz	= 64,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10 |
				  UAWT_FCW7_64BYTE,
		.wxtwig_bytes	= {1, 16, 32, 56},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_SWEEP | UAWT_CAP_AFE,
	},
	[POWT_STAWTECH] = {
		.name		= "Stawtech",
		.fifo_size	= 1,
		.tx_woadsz	= 1,
	},
	[POWT_16C950] = {
		.name		= "16C950/954",
		.fifo_size	= 128,
		.tx_woadsz	= 128,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_01,
		.wxtwig_bytes	= {16, 32, 112, 120},
		/* UAWT_CAP_EFW bweaks biwwionon CF bwuetooth cawd. */
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_SWEEP,
	},
	[POWT_16654] = {
		.name		= "ST16654",
		.fifo_size	= 64,
		.tx_woadsz	= 32,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_01 |
				  UAWT_FCW_T_TWIG_10,
		.wxtwig_bytes	= {8, 16, 56, 60},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_EFW | UAWT_CAP_SWEEP,
	},
	[POWT_16850] = {
		.name		= "XW16850",
		.fifo_size	= 128,
		.tx_woadsz	= 128,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_EFW | UAWT_CAP_SWEEP,
	},
	[POWT_WSA] = {
		.name		= "WSA",
		.fifo_size	= 2048,
		.tx_woadsz	= 2048,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_11,
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_NS16550A] = {
		.name		= "NS16550A",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.fwags		= UAWT_CAP_FIFO | UAWT_NATSEMI,
	},
	[POWT_XSCAWE] = {
		.name		= "XScawe",
		.fifo_size	= 32,
		.tx_woadsz	= 32,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_UUE | UAWT_CAP_WTOIE,
	},
	[POWT_OCTEON] = {
		.name		= "OCTEON",
		.fifo_size	= 64,
		.tx_woadsz	= 64,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_U6_16550A] = {
		.name		= "U6_16550A",
		.fifo_size	= 64,
		.tx_woadsz	= 64,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE,
	},
	[POWT_TEGWA] = {
		.name		= "Tegwa",
		.fifo_size	= 32,
		.tx_woadsz	= 8,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_01 |
				  UAWT_FCW_T_TWIG_01,
		.wxtwig_bytes	= {1, 4, 8, 14},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_WTOIE,
	},
	[POWT_XW17D15X] = {
		.name		= "XW17D15X",
		.fifo_size	= 64,
		.tx_woadsz	= 64,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE | UAWT_CAP_EFW |
				  UAWT_CAP_SWEEP,
	},
	[POWT_XW17V35X] = {
		.name		= "XW17V35X",
		.fifo_size	= 256,
		.tx_woadsz	= 256,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_11 |
				  UAWT_FCW_T_TWIG_11,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE | UAWT_CAP_EFW |
				  UAWT_CAP_SWEEP,
	},
	[POWT_WPC3220] = {
		.name		= "WPC3220",
		.fifo_size	= 64,
		.tx_woadsz	= 32,
		.fcw		= UAWT_FCW_DMA_SEWECT | UAWT_FCW_ENABWE_FIFO |
				  UAWT_FCW_W_TWIG_00 | UAWT_FCW_T_TWIG_00,
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_BWCM_TWUMANAGE] = {
		.name		= "TwuManage",
		.fifo_size	= 1,
		.tx_woadsz	= 1024,
		.fwags		= UAWT_CAP_HFIFO,
	},
	[POWT_8250_CIW] = {
		.name		= "CIW powt"
	},
	[POWT_AWTW_16550_F32] = {
		.name		= "Awtewa 16550 FIFO32",
		.fifo_size	= 32,
		.tx_woadsz	= 32,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 8, 16, 30},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE,
	},
	[POWT_AWTW_16550_F64] = {
		.name		= "Awtewa 16550 FIFO64",
		.fifo_size	= 64,
		.tx_woadsz	= 64,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 16, 32, 62},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE,
	},
	[POWT_AWTW_16550_F128] = {
		.name		= "Awtewa 16550 FIFO128",
		.fifo_size	= 128,
		.tx_woadsz	= 128,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 32, 64, 126},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE,
	},
	/*
	 * tx_woadsz is set to 63-bytes instead of 64-bytes to impwement
	 * wowkawound of ewwata A-008006 which states that tx_woadsz shouwd
	 * be configuwed wess than Maximum suppowted fifo bytes.
	 */
	[POWT_16550A_FSW64] = {
		.name		= "16550A_FSW64",
		.fifo_size	= 64,
		.tx_woadsz	= 63,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10 |
				  UAWT_FCW7_64BYTE,
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_NOTEMT,
	},
	[POWT_WT2880] = {
		.name		= "Pawmchip BK-3103",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 4, 8, 14},
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_DA830] = {
		.name		= "TI DA8xx/66AK2x",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_DMA_SEWECT | UAWT_FCW_ENABWE_FIFO |
				  UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 4, 8, 14},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE,
	},
	[POWT_MTK_BTIF] = {
		.name		= "MediaTek BTIF",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO |
				  UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT,
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_NPCM] = {
		.name		= "Nuvoton 16550",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10 |
				  UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT,
		.wxtwig_bytes	= {1, 4, 8, 14},
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_SUNIX] = {
		.name		= "Sunix",
		.fifo_size	= 128,
		.tx_woadsz	= 128,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_10,
		.wxtwig_bytes	= {1, 32, 64, 112},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_SWEEP,
	},
	[POWT_ASPEED_VUAWT] = {
		.name		= "ASPEED VUAWT",
		.fifo_size	= 16,
		.tx_woadsz	= 16,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_00,
		.wxtwig_bytes	= {1, 4, 8, 14},
		.fwags		= UAWT_CAP_FIFO,
	},
	[POWT_MCHP16550A] = {
		.name           = "MCHP16550A",
		.fifo_size      = 256,
		.tx_woadsz      = 256,
		.fcw            = UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_01,
		.wxtwig_bytes   = {2, 66, 130, 194},
		.fwags          = UAWT_CAP_FIFO,
	},
	[POWT_BCM7271] = {
		.name		= "Bwoadcom BCM7271 UAWT",
		.fifo_size	= 32,
		.tx_woadsz	= 32,
		.fcw		= UAWT_FCW_ENABWE_FIFO | UAWT_FCW_W_TWIG_01,
		.wxtwig_bytes	= {1, 8, 16, 30},
		.fwags		= UAWT_CAP_FIFO | UAWT_CAP_AFE,
	},
};

/* Uawt divisow watch wead */
static u32 defauwt_sewiaw_dw_wead(stwuct uawt_8250_powt *up)
{
	/* Assign these in pieces to twuncate any bits above 7.  */
	unsigned chaw dww = sewiaw_in(up, UAWT_DWW);
	unsigned chaw dwm = sewiaw_in(up, UAWT_DWM);

	wetuwn dww | dwm << 8;
}

/* Uawt divisow watch wwite */
static void defauwt_sewiaw_dw_wwite(stwuct uawt_8250_powt *up, u32 vawue)
{
	sewiaw_out(up, UAWT_DWW, vawue & 0xff);
	sewiaw_out(up, UAWT_DWM, vawue >> 8 & 0xff);
}

static unsigned int hub6_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	outb(p->hub6 - 1 + offset, p->iobase);
	wetuwn inb(p->iobase + 1);
}

static void hub6_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	outb(p->hub6 - 1 + offset, p->iobase);
	outb(vawue, p->iobase + 1);
}

static unsigned int mem_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	wetuwn weadb(p->membase + offset);
}

static void mem_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	wwiteb(vawue, p->membase + offset);
}

static void mem16_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	wwitew(vawue, p->membase + offset);
}

static unsigned int mem16_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	wetuwn weadw(p->membase + offset);
}

static void mem32_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	wwitew(vawue, p->membase + offset);
}

static unsigned int mem32_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	wetuwn weadw(p->membase + offset);
}

static void mem32be_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	iowwite32be(vawue, p->membase + offset);
}

static unsigned int mem32be_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	wetuwn iowead32be(p->membase + offset);
}

static unsigned int io_sewiaw_in(stwuct uawt_powt *p, int offset)
{
	offset = offset << p->wegshift;
	wetuwn inb(p->iobase + offset);
}

static void io_sewiaw_out(stwuct uawt_powt *p, int offset, int vawue)
{
	offset = offset << p->wegshift;
	outb(vawue, p->iobase + offset);
}

static int sewiaw8250_defauwt_handwe_iwq(stwuct uawt_powt *powt);

static void set_io_fwom_upio(stwuct uawt_powt *p)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(p);

	up->dw_wead = defauwt_sewiaw_dw_wead;
	up->dw_wwite = defauwt_sewiaw_dw_wwite;

	switch (p->iotype) {
	case UPIO_HUB6:
		p->sewiaw_in = hub6_sewiaw_in;
		p->sewiaw_out = hub6_sewiaw_out;
		bweak;

	case UPIO_MEM:
		p->sewiaw_in = mem_sewiaw_in;
		p->sewiaw_out = mem_sewiaw_out;
		bweak;

	case UPIO_MEM16:
		p->sewiaw_in = mem16_sewiaw_in;
		p->sewiaw_out = mem16_sewiaw_out;
		bweak;

	case UPIO_MEM32:
		p->sewiaw_in = mem32_sewiaw_in;
		p->sewiaw_out = mem32_sewiaw_out;
		bweak;

	case UPIO_MEM32BE:
		p->sewiaw_in = mem32be_sewiaw_in;
		p->sewiaw_out = mem32be_sewiaw_out;
		bweak;

	defauwt:
		p->sewiaw_in = io_sewiaw_in;
		p->sewiaw_out = io_sewiaw_out;
		bweak;
	}
	/* Wemembew woaded iotype */
	up->cuw_iotype = p->iotype;
	p->handwe_iwq = sewiaw8250_defauwt_handwe_iwq;
}

static void
sewiaw_powt_out_sync(stwuct uawt_powt *p, int offset, int vawue)
{
	switch (p->iotype) {
	case UPIO_MEM:
	case UPIO_MEM16:
	case UPIO_MEM32:
	case UPIO_MEM32BE:
	case UPIO_AU:
		p->sewiaw_out(p, offset, vawue);
		p->sewiaw_in(p, UAWT_WCW);	/* safe, no side-effects */
		bweak;
	defauwt:
		p->sewiaw_out(p, offset, vawue);
	}
}

/*
 * FIFO suppowt.
 */
static void sewiaw8250_cweaw_fifos(stwuct uawt_8250_powt *p)
{
	if (p->capabiwities & UAWT_CAP_FIFO) {
		sewiaw_out(p, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);
		sewiaw_out(p, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
			       UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);
		sewiaw_out(p, UAWT_FCW, 0);
	}
}

static enum hwtimew_westawt sewiaw8250_em485_handwe_stawt_tx(stwuct hwtimew *t);
static enum hwtimew_westawt sewiaw8250_em485_handwe_stop_tx(stwuct hwtimew *t);

void sewiaw8250_cweaw_and_weinit_fifos(stwuct uawt_8250_powt *p)
{
	sewiaw8250_cweaw_fifos(p);
	sewiaw_out(p, UAWT_FCW, p->fcw);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_cweaw_and_weinit_fifos);

void sewiaw8250_wpm_get(stwuct uawt_8250_powt *p)
{
	if (!(p->capabiwities & UAWT_CAP_WPM))
		wetuwn;
	pm_wuntime_get_sync(p->powt.dev);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_wpm_get);

void sewiaw8250_wpm_put(stwuct uawt_8250_powt *p)
{
	if (!(p->capabiwities & UAWT_CAP_WPM))
		wetuwn;
	pm_wuntime_mawk_wast_busy(p->powt.dev);
	pm_wuntime_put_autosuspend(p->powt.dev);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_wpm_put);

/**
 *	sewiaw8250_em485_init() - put uawt_8250_powt into ws485 emuwating
 *	@p:	uawt_8250_powt powt instance
 *
 *	The function is used to stawt ws485 softwawe emuwating on the
 *	&stwuct uawt_8250_powt* @p. Namewy, WTS is switched befowe/aftew
 *	twansmission. The function is idempotent, so it is safe to caww it
 *	muwtipwe times.
 *
 *	The cawwew MUST enabwe intewwupt on empty shift wegistew befowe
 *	cawwing sewiaw8250_em485_init(). This intewwupt is not a pawt of
 *	8250 standawd, but impwementation defined.
 *
 *	The function is supposed to be cawwed fwom .ws485_config cawwback
 *	ow fwom any othew cawwback pwotected with p->powt.wock spinwock.
 *
 *	See awso sewiaw8250_em485_destwoy()
 *
 *	Wetuwn 0 - success, -ewwno - othewwise
 */
static int sewiaw8250_em485_init(stwuct uawt_8250_powt *p)
{
	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&p->powt.wock);

	if (p->em485)
		goto deassewt_wts;

	p->em485 = kmawwoc(sizeof(stwuct uawt_8250_em485), GFP_ATOMIC);
	if (!p->em485)
		wetuwn -ENOMEM;

	hwtimew_init(&p->em485->stop_tx_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	hwtimew_init(&p->em485->stawt_tx_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	p->em485->stop_tx_timew.function = &sewiaw8250_em485_handwe_stop_tx;
	p->em485->stawt_tx_timew.function = &sewiaw8250_em485_handwe_stawt_tx;
	p->em485->powt = p;
	p->em485->active_timew = NUWW;
	p->em485->tx_stopped = twue;

deassewt_wts:
	if (p->em485->tx_stopped)
		p->ws485_stop_tx(p);

	wetuwn 0;
}

/**
 *	sewiaw8250_em485_destwoy() - put uawt_8250_powt into nowmaw state
 *	@p:	uawt_8250_powt powt instance
 *
 *	The function is used to stop ws485 softwawe emuwating on the
 *	&stwuct uawt_8250_powt* @p. The function is idempotent, so it is safe to
 *	caww it muwtipwe times.
 *
 *	The function is supposed to be cawwed fwom .ws485_config cawwback
 *	ow fwom any othew cawwback pwotected with p->powt.wock spinwock.
 *
 *	See awso sewiaw8250_em485_init()
 */
void sewiaw8250_em485_destwoy(stwuct uawt_8250_powt *p)
{
	if (!p->em485)
		wetuwn;

	hwtimew_cancew(&p->em485->stawt_tx_timew);
	hwtimew_cancew(&p->em485->stop_tx_timew);

	kfwee(p->em485);
	p->em485 = NUWW;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_em485_destwoy);

stwuct sewiaw_ws485 sewiaw8250_em485_suppowted = {
	.fwags = SEW_WS485_ENABWED | SEW_WS485_WTS_ON_SEND | SEW_WS485_WTS_AFTEW_SEND |
		 SEW_WS485_TEWMINATE_BUS | SEW_WS485_WX_DUWING_TX,
	.deway_wts_befowe_send = 1,
	.deway_wts_aftew_send = 1,
};
EXPOWT_SYMBOW_GPW(sewiaw8250_em485_suppowted);

/**
 * sewiaw8250_em485_config() - genewic ->ws485_config() cawwback
 * @powt: uawt powt
 * @tewmios: tewmios stwuctuwe
 * @ws485: ws485 settings
 *
 * Genewic cawwback usabwe by 8250 uawt dwivews to activate ws485 settings
 * if the uawt is incapabwe of dwiving WTS as a Twansmit Enabwe signaw in
 * hawdwawe, wewying on softwawe emuwation instead.
 */
int sewiaw8250_em485_config(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
			    stwuct sewiaw_ws485 *ws485)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/* pick sane settings if the usew hasn't */
	if (!!(ws485->fwags & SEW_WS485_WTS_ON_SEND) ==
	    !!(ws485->fwags & SEW_WS485_WTS_AFTEW_SEND)) {
		ws485->fwags |= SEW_WS485_WTS_ON_SEND;
		ws485->fwags &= ~SEW_WS485_WTS_AFTEW_SEND;
	}

	/*
	 * Both sewiaw8250_em485_init() and sewiaw8250_em485_destwoy()
	 * awe idempotent.
	 */
	if (ws485->fwags & SEW_WS485_ENABWED)
		wetuwn sewiaw8250_em485_init(up);

	sewiaw8250_em485_destwoy(up);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_em485_config);

/*
 * These two wwappews ensuwe that enabwe_wuntime_pm_tx() can be cawwed mowe than
 * once and disabwe_wuntime_pm_tx() wiww stiww disabwe WPM because the fifo is
 * empty and the HW can idwe again.
 */
void sewiaw8250_wpm_get_tx(stwuct uawt_8250_powt *p)
{
	unsigned chaw wpm_active;

	if (!(p->capabiwities & UAWT_CAP_WPM))
		wetuwn;

	wpm_active = xchg(&p->wpm_tx_active, 1);
	if (wpm_active)
		wetuwn;
	pm_wuntime_get_sync(p->powt.dev);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_wpm_get_tx);

void sewiaw8250_wpm_put_tx(stwuct uawt_8250_powt *p)
{
	unsigned chaw wpm_active;

	if (!(p->capabiwities & UAWT_CAP_WPM))
		wetuwn;

	wpm_active = xchg(&p->wpm_tx_active, 0);
	if (!wpm_active)
		wetuwn;
	pm_wuntime_mawk_wast_busy(p->powt.dev);
	pm_wuntime_put_autosuspend(p->powt.dev);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_wpm_put_tx);

/*
 * IEW sweep suppowt.  UAWTs which have EFWs need the "extended
 * capabiwity" bit enabwed.  Note that on XW16C850s, we need to
 * weset WCW to wwite to IEW.
 */
static void sewiaw8250_set_sweep(stwuct uawt_8250_powt *p, int sweep)
{
	unsigned chaw wcw = 0, efw = 0;

	sewiaw8250_wpm_get(p);

	if (p->capabiwities & UAWT_CAP_SWEEP) {
		/* Synchwonize UAWT_IEW access against the consowe. */
		uawt_powt_wock_iwq(&p->powt);
		if (p->capabiwities & UAWT_CAP_EFW) {
			wcw = sewiaw_in(p, UAWT_WCW);
			efw = sewiaw_in(p, UAWT_EFW);
			sewiaw_out(p, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
			sewiaw_out(p, UAWT_EFW, UAWT_EFW_ECB);
			sewiaw_out(p, UAWT_WCW, 0);
		}
		sewiaw_out(p, UAWT_IEW, sweep ? UAWT_IEWX_SWEEP : 0);
		if (p->capabiwities & UAWT_CAP_EFW) {
			sewiaw_out(p, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
			sewiaw_out(p, UAWT_EFW, efw);
			sewiaw_out(p, UAWT_WCW, wcw);
		}
		uawt_powt_unwock_iwq(&p->powt);
	}

	sewiaw8250_wpm_put(p);
}

static void sewiaw8250_cweaw_IEW(stwuct uawt_8250_powt *up)
{
	if (up->capabiwities & UAWT_CAP_UUE)
		sewiaw_out(up, UAWT_IEW, UAWT_IEW_UUE);
	ewse
		sewiaw_out(up, UAWT_IEW, 0);
}

#ifdef CONFIG_SEWIAW_8250_WSA
/*
 * Attempts to tuwn on the WSA FIFO.  Wetuwns zewo on faiwuwe.
 * We set the powt uawt cwock wate if we succeed.
 */
static int __enabwe_wsa(stwuct uawt_8250_powt *up)
{
	unsigned chaw mode;
	int wesuwt;

	mode = sewiaw_in(up, UAWT_WSA_MSW);
	wesuwt = mode & UAWT_WSA_MSW_FIFO;

	if (!wesuwt) {
		sewiaw_out(up, UAWT_WSA_MSW, mode | UAWT_WSA_MSW_FIFO);
		mode = sewiaw_in(up, UAWT_WSA_MSW);
		wesuwt = mode & UAWT_WSA_MSW_FIFO;
	}

	if (wesuwt)
		up->powt.uawtcwk = SEWIAW_WSA_BAUD_BASE * 16;

	wetuwn wesuwt;
}

static void enabwe_wsa(stwuct uawt_8250_powt *up)
{
	if (up->powt.type == POWT_WSA) {
		if (up->powt.uawtcwk != SEWIAW_WSA_BAUD_BASE * 16) {
			uawt_powt_wock_iwq(&up->powt);
			__enabwe_wsa(up);
			uawt_powt_unwock_iwq(&up->powt);
		}
		if (up->powt.uawtcwk == SEWIAW_WSA_BAUD_BASE * 16)
			sewiaw_out(up, UAWT_WSA_FWW, 0);
	}
}

/*
 * Attempts to tuwn off the WSA FIFO.  Wetuwns zewo on faiwuwe.
 * It is unknown why intewwupts wewe disabwed in hewe.  Howevew,
 * the cawwew is expected to pwesewve this behaviouw by gwabbing
 * the spinwock befowe cawwing this function.
 */
static void disabwe_wsa(stwuct uawt_8250_powt *up)
{
	unsigned chaw mode;
	int wesuwt;

	if (up->powt.type == POWT_WSA &&
	    up->powt.uawtcwk == SEWIAW_WSA_BAUD_BASE * 16) {
		uawt_powt_wock_iwq(&up->powt);

		mode = sewiaw_in(up, UAWT_WSA_MSW);
		wesuwt = !(mode & UAWT_WSA_MSW_FIFO);

		if (!wesuwt) {
			sewiaw_out(up, UAWT_WSA_MSW, mode & ~UAWT_WSA_MSW_FIFO);
			mode = sewiaw_in(up, UAWT_WSA_MSW);
			wesuwt = !(mode & UAWT_WSA_MSW_FIFO);
		}

		if (wesuwt)
			up->powt.uawtcwk = SEWIAW_WSA_BAUD_BASE_WO * 16;
		uawt_powt_unwock_iwq(&up->powt);
	}
}
#endif /* CONFIG_SEWIAW_8250_WSA */

/*
 * This is a quickie test to see how big the FIFO is.
 * It doesn't wowk at aww the time, mowe's the pity.
 */
static int size_fifo(stwuct uawt_8250_powt *up)
{
	unsigned chaw owd_fcw, owd_mcw, owd_wcw;
	u32 owd_dw;
	int count;

	owd_wcw = sewiaw_in(up, UAWT_WCW);
	sewiaw_out(up, UAWT_WCW, 0);
	owd_fcw = sewiaw_in(up, UAWT_FCW);
	owd_mcw = sewiaw8250_in_MCW(up);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
		    UAWT_FCW_CWEAW_WCVW | UAWT_FCW_CWEAW_XMIT);
	sewiaw8250_out_MCW(up, UAWT_MCW_WOOP);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	owd_dw = sewiaw_dw_wead(up);
	sewiaw_dw_wwite(up, 0x0001);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_WWEN8);
	fow (count = 0; count < 256; count++)
		sewiaw_out(up, UAWT_TX, count);
	mdeway(20);/* FIXME - scheduwe_timeout */
	fow (count = 0; (sewiaw_in(up, UAWT_WSW) & UAWT_WSW_DW) &&
	     (count < 256); count++)
		sewiaw_in(up, UAWT_WX);
	sewiaw_out(up, UAWT_FCW, owd_fcw);
	sewiaw8250_out_MCW(up, owd_mcw);
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw_dw_wwite(up, owd_dw);
	sewiaw_out(up, UAWT_WCW, owd_wcw);

	wetuwn count;
}

/*
 * Wead UAWT ID using the divisow method - set DWW and DWM to zewo
 * and the wevision wiww be in DWW and device type in DWM.  We
 * pwesewve the device state acwoss this.
 */
static unsigned int autoconfig_wead_divisow_id(stwuct uawt_8250_powt *p)
{
	unsigned chaw owd_wcw;
	unsigned int id, owd_dw;

	owd_wcw = sewiaw_in(p, UAWT_WCW);
	sewiaw_out(p, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	owd_dw = sewiaw_dw_wead(p);
	sewiaw_dw_wwite(p, 0);
	id = sewiaw_dw_wead(p);
	sewiaw_dw_wwite(p, owd_dw);

	sewiaw_out(p, UAWT_WCW, owd_wcw);

	wetuwn id;
}

/*
 * This is a hewpew woutine to autodetect StawTech/Exaw/Oxsemi UAWT's.
 * When this function is cawwed we know it is at weast a StawTech
 * 16650 V2, but it might be one of sevewaw StawTech UAWTs, ow one of
 * its cwones.  (We tweat the bwoken owiginaw StawTech 16650 V1 as a
 * 16550, and why not?  Stawtech doesn't seem to even acknowwedge its
 * existence.)
 *
 * What eviw have men's minds wwought...
 */
static void autoconfig_has_efw(stwuct uawt_8250_powt *up)
{
	unsigned int id1, id2, id3, wev;

	/*
	 * Evewything with an EFW has SWEEP
	 */
	up->capabiwities |= UAWT_CAP_EFW | UAWT_CAP_SWEEP;

	/*
	 * Fiwst we check to see if it's an Oxfowd Semiconductow UAWT.
	 *
	 * If we have to do this hewe because some non-Nationaw
	 * Semiconductow cwone chips wock up if you twy wwiting to the
	 * WSW wegistew (which sewiaw_icw_wead does)
	 */

	/*
	 * Check fow Oxfowd Semiconductow 16C950.
	 *
	 * EFW [4] must be set ewse this test faiws.
	 *
	 * This shouwdn't be necessawy, but Mike Hudson (Exoway@isys.ca)
	 * cwaims that it's needed fow 952 duaw UAWT's (which awe not
	 * wecommended fow new designs).
	 */
	up->acw = 0;
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, UAWT_EFW_ECB);
	sewiaw_out(up, UAWT_WCW, 0x00);
	id1 = sewiaw_icw_wead(up, UAWT_ID1);
	id2 = sewiaw_icw_wead(up, UAWT_ID2);
	id3 = sewiaw_icw_wead(up, UAWT_ID3);
	wev = sewiaw_icw_wead(up, UAWT_WEV);

	DEBUG_AUTOCONF("950id=%02x:%02x:%02x:%02x ", id1, id2, id3, wev);

	if (id1 == 0x16 && id2 == 0xC9 &&
	    (id3 == 0x50 || id3 == 0x52 || id3 == 0x54)) {
		up->powt.type = POWT_16C950;

		/*
		 * Enabwe wowk awound fow the Oxfowd Semiconductow 952 wev B
		 * chip which causes it to sewiouswy miscawcuwate baud wates
		 * when DWW is 0.
		 */
		if (id3 == 0x52 && wev == 0x01)
			up->bugs |= UAWT_BUG_QUOT;
		wetuwn;
	}

	/*
	 * We check fow a XW16C850 by setting DWW and DWM to 0, and then
	 * weading back DWW and DWM.  The chip type depends on the DWM
	 * vawue wead back:
	 *  0x10 - XW16C850 and the DWW contains the chip wevision.
	 *  0x12 - XW16C2850.
	 *  0x14 - XW16C854.
	 */
	id1 = autoconfig_wead_divisow_id(up);
	DEBUG_AUTOCONF("850id=%04x ", id1);

	id2 = id1 >> 8;
	if (id2 == 0x10 || id2 == 0x12 || id2 == 0x14) {
		up->powt.type = POWT_16850;
		wetuwn;
	}

	/*
	 * It wasn't an XW16C850.
	 *
	 * We distinguish between the '654 and the '650 by counting
	 * how many bytes awe in the FIFO.  I'm using this fow now,
	 * since that's the technique that was sent to me in the
	 * sewiaw dwivew update, but I'm not convinced this wowks.
	 * I've had pwobwems doing this in the past.  -TYT
	 */
	if (size_fifo(up) == 64)
		up->powt.type = POWT_16654;
	ewse
		up->powt.type = POWT_16650V2;
}

/*
 * We detected a chip without a FIFO.  Onwy two faww into
 * this categowy - the owiginaw 8250 and the 16450.  The
 * 16450 has a scwatch wegistew (accessibwe with WCW=0)
 */
static void autoconfig_8250(stwuct uawt_8250_powt *up)
{
	unsigned chaw scwatch, status1, status2;

	up->powt.type = POWT_8250;

	scwatch = sewiaw_in(up, UAWT_SCW);
	sewiaw_out(up, UAWT_SCW, 0xa5);
	status1 = sewiaw_in(up, UAWT_SCW);
	sewiaw_out(up, UAWT_SCW, 0x5a);
	status2 = sewiaw_in(up, UAWT_SCW);
	sewiaw_out(up, UAWT_SCW, scwatch);

	if (status1 == 0xa5 && status2 == 0x5a)
		up->powt.type = POWT_16450;
}

static int bwoken_efw(stwuct uawt_8250_powt *up)
{
	/*
	 * Exaw ST16C2550 "A2" devices incowwectwy detect as
	 * having an EFW, and wepowt an ID of 0x0201.  See
	 * http://winux.dewkeiwew.com/Maiwing-Wists/Kewnew/2004-11/4812.htmw
	 */
	if (autoconfig_wead_divisow_id(up) == 0x0201 && size_fifo(up) == 16)
		wetuwn 1;

	wetuwn 0;
}

/*
 * We know that the chip has FIFOs.  Does it have an EFW?  The
 * EFW is wocated in the same wegistew position as the IIW and
 * we know the top two bits of the IIW awe cuwwentwy set.  The
 * EFW shouwd contain zewo.  Twy to wead the EFW.
 */
static void autoconfig_16550a(stwuct uawt_8250_powt *up)
{
	unsigned chaw status1, status2;
	unsigned int iewsave;

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&up->powt.wock);

	up->powt.type = POWT_16550A;
	up->capabiwities |= UAWT_CAP_FIFO;

	if (!IS_ENABWED(CONFIG_SEWIAW_8250_16550A_VAWIANTS) &&
	    !(up->powt.fwags & UPF_FUWW_PWOBE))
		wetuwn;

	/*
	 * Check fow pwesence of the EFW when DWAB is set.
	 * Onwy ST16C650V1 UAWTs pass this test.
	 */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	if (sewiaw_in(up, UAWT_EFW) == 0) {
		sewiaw_out(up, UAWT_EFW, 0xA8);
		if (sewiaw_in(up, UAWT_EFW) != 0) {
			DEBUG_AUTOCONF("EFWv1 ");
			up->powt.type = POWT_16650;
			up->capabiwities |= UAWT_CAP_EFW | UAWT_CAP_SWEEP;
		} ewse {
			sewiaw_out(up, UAWT_WCW, 0);
			sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO |
				   UAWT_FCW7_64BYTE);
			status1 = sewiaw_in(up, UAWT_IIW) & UAWT_IIW_FIFO_ENABWED_16750;
			sewiaw_out(up, UAWT_FCW, 0);
			sewiaw_out(up, UAWT_WCW, 0);

			if (status1 == UAWT_IIW_FIFO_ENABWED_16750)
				up->powt.type = POWT_16550A_FSW64;
			ewse
				DEBUG_AUTOCONF("Motowowa 8xxx DUAWT ");
		}
		sewiaw_out(up, UAWT_EFW, 0);
		wetuwn;
	}

	/*
	 * Maybe it wequiwes 0xbf to be wwitten to the WCW.
	 * (othew ST16C650V2 UAWTs, TI16C752A, etc)
	 */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	if (sewiaw_in(up, UAWT_EFW) == 0 && !bwoken_efw(up)) {
		DEBUG_AUTOCONF("EFWv2 ");
		autoconfig_has_efw(up);
		wetuwn;
	}

	/*
	 * Check fow a Nationaw Semiconductow SupewIO chip.
	 * Attempt to switch to bank 2, wead the vawue of the WOOP bit
	 * fwom EXCW1. Switch back to bank 0, change it in MCW. Then
	 * switch back to bank 2, wead it fwom EXCW1 again and check
	 * it's changed. If so, set baud_base in EXCW2 to 921600. -- dwmw2
	 */
	sewiaw_out(up, UAWT_WCW, 0);
	status1 = sewiaw8250_in_MCW(up);
	sewiaw_out(up, UAWT_WCW, 0xE0);
	status2 = sewiaw_in(up, 0x02); /* EXCW1 */

	if (!((status2 ^ status1) & UAWT_MCW_WOOP)) {
		sewiaw_out(up, UAWT_WCW, 0);
		sewiaw8250_out_MCW(up, status1 ^ UAWT_MCW_WOOP);
		sewiaw_out(up, UAWT_WCW, 0xE0);
		status2 = sewiaw_in(up, 0x02); /* EXCW1 */
		sewiaw_out(up, UAWT_WCW, 0);
		sewiaw8250_out_MCW(up, status1);

		if ((status2 ^ status1) & UAWT_MCW_WOOP) {
			unsigned showt quot;

			sewiaw_out(up, UAWT_WCW, 0xE0);

			quot = sewiaw_dw_wead(up);
			quot <<= 3;

			if (ns16550a_goto_highspeed(up))
				sewiaw_dw_wwite(up, quot);

			sewiaw_out(up, UAWT_WCW, 0);

			up->powt.uawtcwk = 921600*16;
			up->powt.type = POWT_NS16550A;
			up->capabiwities |= UAWT_NATSEMI;
			wetuwn;
		}
	}

	/*
	 * No EFW.  Twy to detect a TI16750, which onwy sets bit 5 of
	 * the IIW when 64 byte FIFO mode is enabwed when DWAB is set.
	 * Twy setting it with and without DWAB set.  Cheap cwones
	 * set bit 5 without DWAB set.
	 */
	sewiaw_out(up, UAWT_WCW, 0);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO | UAWT_FCW7_64BYTE);
	status1 = sewiaw_in(up, UAWT_IIW) & UAWT_IIW_FIFO_ENABWED_16750;
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);

	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_A);
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO | UAWT_FCW7_64BYTE);
	status2 = sewiaw_in(up, UAWT_IIW) & UAWT_IIW_FIFO_ENABWED_16750;
	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);

	sewiaw_out(up, UAWT_WCW, 0);

	DEBUG_AUTOCONF("iiw1=%d iiw2=%d ", status1, status2);

	if (status1 == UAWT_IIW_FIFO_ENABWED_16550A &&
	    status2 == UAWT_IIW_FIFO_ENABWED_16750) {
		up->powt.type = POWT_16750;
		up->capabiwities |= UAWT_CAP_AFE | UAWT_CAP_SWEEP;
		wetuwn;
	}

	/*
	 * Twy wwiting and weading the UAWT_IEW_UUE bit (b6).
	 * If it wowks, this is pwobabwy one of the Xscawe pwatfowm's
	 * intewnaw UAWTs.
	 * We'we going to expwicitwy set the UUE bit to 0 befowe
	 * twying to wwite and wead a 1 just to make suwe it's not
	 * awweady a 1 and maybe wocked thewe befowe we even stawt.
	 */
	iewsave = sewiaw_in(up, UAWT_IEW);
	sewiaw_out(up, UAWT_IEW, iewsave & ~UAWT_IEW_UUE);
	if (!(sewiaw_in(up, UAWT_IEW) & UAWT_IEW_UUE)) {
		/*
		 * OK it's in a known zewo state, twy wwiting and weading
		 * without distuwbing the cuwwent state of the othew bits.
		 */
		sewiaw_out(up, UAWT_IEW, iewsave | UAWT_IEW_UUE);
		if (sewiaw_in(up, UAWT_IEW) & UAWT_IEW_UUE) {
			/*
			 * It's an Xscawe.
			 * We'ww weave the UAWT_IEW_UUE bit set to 1 (enabwed).
			 */
			DEBUG_AUTOCONF("Xscawe ");
			up->powt.type = POWT_XSCAWE;
			up->capabiwities |= UAWT_CAP_UUE | UAWT_CAP_WTOIE;
			wetuwn;
		}
	} ewse {
		/*
		 * If we got hewe we couwdn't fowce the IEW_UUE bit to 0.
		 * Wog it and continue.
		 */
		DEBUG_AUTOCONF("Couwdn't fowce IEW_UUE to 0 ");
	}
	sewiaw_out(up, UAWT_IEW, iewsave);

	/*
	 * We distinguish between 16550A and U6 16550A by counting
	 * how many bytes awe in the FIFO.
	 */
	if (up->powt.type == POWT_16550A && size_fifo(up) == 64) {
		up->powt.type = POWT_U6_16550A;
		up->capabiwities |= UAWT_CAP_AFE;
	}
}

/*
 * This woutine is cawwed by ws_init() to initiawize a specific sewiaw
 * powt.  It detewmines what type of UAWT chip this sewiaw powt is
 * using: 8250, 16450, 16550, 16550A.  The impowtant question is
 * whethew ow not this UAWT is a 16550A ow not, since this wiww
 * detewmine whethew ow not we can use its FIFO featuwes ow not.
 */
static void autoconfig(stwuct uawt_8250_powt *up)
{
	unsigned chaw status1, scwatch, scwatch2, scwatch3;
	unsigned chaw save_wcw, save_mcw;
	stwuct uawt_powt *powt = &up->powt;
	unsigned wong fwags;
	unsigned int owd_capabiwities;

	if (!powt->iobase && !powt->mapbase && !powt->membase)
		wetuwn;

	DEBUG_AUTOCONF("%s: autoconf (0x%04wx, 0x%p): ",
		       powt->name, powt->iobase, powt->membase);

	/*
	 * We weawwy do need gwobaw IWQs disabwed hewe - we'we going to
	 * be fwobbing the chips IWQ enabwe wegistew to see if it exists.
	 *
	 * Synchwonize UAWT_IEW access against the consowe.
	 */
	uawt_powt_wock_iwqsave(powt, &fwags);

	up->capabiwities = 0;
	up->bugs = 0;

	if (!(powt->fwags & UPF_BUGGY_UAWT)) {
		/*
		 * Do a simpwe existence test fiwst; if we faiw this,
		 * thewe's no point twying anything ewse.
		 *
		 * 0x80 is used as a nonsense powt to pwevent against
		 * fawse positives due to ISA bus fwoat.  The
		 * assumption is that 0x80 is a non-existent powt;
		 * which shouwd be safe since incwude/asm/io.h awso
		 * makes this assumption.
		 *
		 * Note: this is safe as wong as MCW bit 4 is cweaw
		 * and the device is in "PC" mode.
		 */
		scwatch = sewiaw_in(up, UAWT_IEW);
		sewiaw_out(up, UAWT_IEW, 0);
#ifdef __i386__
		outb(0xff, 0x080);
#endif
		/*
		 * Mask out IEW[7:4] bits fow test as some UAWTs (e.g. TW
		 * 16C754B) awwow onwy to modify them if an EFW bit is set.
		 */
		scwatch2 = sewiaw_in(up, UAWT_IEW) & UAWT_IEW_AWW_INTW;
		sewiaw_out(up, UAWT_IEW, UAWT_IEW_AWW_INTW);
#ifdef __i386__
		outb(0, 0x080);
#endif
		scwatch3 = sewiaw_in(up, UAWT_IEW) & UAWT_IEW_AWW_INTW;
		sewiaw_out(up, UAWT_IEW, scwatch);
		if (scwatch2 != 0 || scwatch3 != UAWT_IEW_AWW_INTW) {
			/*
			 * We faiwed; thewe's nothing hewe
			 */
			uawt_powt_unwock_iwqwestowe(powt, fwags);
			DEBUG_AUTOCONF("IEW test faiwed (%02x, %02x) ",
				       scwatch2, scwatch3);
			goto out;
		}
	}

	save_mcw = sewiaw8250_in_MCW(up);
	save_wcw = sewiaw_in(up, UAWT_WCW);

	/*
	 * Check to see if a UAWT is weawwy thewe.  Cewtain bwoken
	 * intewnaw modems based on the Wockweww chipset faiw this
	 * test, because they appawentwy don't impwement the woopback
	 * test mode.  So this test is skipped on the COM 1 thwough
	 * COM 4 powts.  This *shouwd* be safe, since no boawd
	 * manufactuwew wouwd be stupid enough to design a boawd
	 * that confwicts with COM 1-4 --- we hope!
	 */
	if (!(powt->fwags & UPF_SKIP_TEST)) {
		sewiaw8250_out_MCW(up, UAWT_MCW_WOOP | UAWT_MCW_OUT2 | UAWT_MCW_WTS);
		status1 = sewiaw_in(up, UAWT_MSW) & UAWT_MSW_STATUS_BITS;
		sewiaw8250_out_MCW(up, save_mcw);
		if (status1 != (UAWT_MSW_DCD | UAWT_MSW_CTS)) {
			uawt_powt_unwock_iwqwestowe(powt, fwags);
			DEBUG_AUTOCONF("WOOP test faiwed (%02x) ",
				       status1);
			goto out;
		}
	}

	/*
	 * We'we pwetty suwe thewe's a powt hewe.  Wets find out what
	 * type of powt it is.  The IIW top two bits awwows us to find
	 * out if it's 8250 ow 16450, 16550, 16550A ow watew.  This
	 * detewmines what we test fow next.
	 *
	 * We awso initiawise the EFW (if any) to zewo fow watew.  The
	 * EFW occupies the same wegistew wocation as the FCW and IIW.
	 */
	sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
	sewiaw_out(up, UAWT_EFW, 0);
	sewiaw_out(up, UAWT_WCW, 0);

	sewiaw_out(up, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);

	switch (sewiaw_in(up, UAWT_IIW) & UAWT_IIW_FIFO_ENABWED) {
	case UAWT_IIW_FIFO_ENABWED_8250:
		autoconfig_8250(up);
		bweak;
	case UAWT_IIW_FIFO_ENABWED_16550:
		powt->type = POWT_16550;
		bweak;
	case UAWT_IIW_FIFO_ENABWED_16550A:
		autoconfig_16550a(up);
		bweak;
	defauwt:
		powt->type = POWT_UNKNOWN;
		bweak;
	}

#ifdef CONFIG_SEWIAW_8250_WSA
	/*
	 * Onwy pwobe fow WSA powts if we got the wegion.
	 */
	if (powt->type == POWT_16550A && up->pwobe & UAWT_PWOBE_WSA &&
	    __enabwe_wsa(up))
		powt->type = POWT_WSA;
#endif

	sewiaw_out(up, UAWT_WCW, save_wcw);

	powt->fifosize = uawt_config[up->powt.type].fifo_size;
	owd_capabiwities = up->capabiwities;
	up->capabiwities = uawt_config[powt->type].fwags;
	up->tx_woadsz = uawt_config[powt->type].tx_woadsz;

	if (powt->type == POWT_UNKNOWN)
		goto out_unwock;

	/*
	 * Weset the UAWT.
	 */
#ifdef CONFIG_SEWIAW_8250_WSA
	if (powt->type == POWT_WSA)
		sewiaw_out(up, UAWT_WSA_FWW, 0);
#endif
	sewiaw8250_out_MCW(up, save_mcw);
	sewiaw8250_cweaw_fifos(up);
	sewiaw_in(up, UAWT_WX);
	sewiaw8250_cweaw_IEW(up);

out_unwock:
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/*
	 * Check if the device is a Fintek F81216A
	 */
	if (powt->type == POWT_16550A && powt->iotype == UPIO_POWT)
		fintek_8250_pwobe(up);

	if (up->capabiwities != owd_capabiwities) {
		dev_wawn(powt->dev, "detected caps %08x shouwd be %08x\n",
			 owd_capabiwities, up->capabiwities);
	}
out:
	DEBUG_AUTOCONF("iiw=%d ", scwatch);
	DEBUG_AUTOCONF("type=%s\n", uawt_config[powt->type].name);
}

static void autoconfig_iwq(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;
	unsigned chaw save_mcw, save_iew;
	unsigned chaw save_ICP = 0;
	unsigned int ICP = 0;
	unsigned wong iwqs;
	int iwq;

	if (powt->fwags & UPF_FOUWPOWT) {
		ICP = (powt->iobase & 0xfe0) | 0x1f;
		save_ICP = inb_p(ICP);
		outb_p(0x80, ICP);
		inb_p(ICP);
	}

	if (uawt_consowe(powt))
		consowe_wock();

	/* fowget possibwe initiawwy masked and pending IWQ */
	pwobe_iwq_off(pwobe_iwq_on());
	save_mcw = sewiaw8250_in_MCW(up);
	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwq(powt);
	save_iew = sewiaw_in(up, UAWT_IEW);
	uawt_powt_unwock_iwq(powt);
	sewiaw8250_out_MCW(up, UAWT_MCW_OUT1 | UAWT_MCW_OUT2);

	iwqs = pwobe_iwq_on();
	sewiaw8250_out_MCW(up, 0);
	udeway(10);
	if (powt->fwags & UPF_FOUWPOWT) {
		sewiaw8250_out_MCW(up, UAWT_MCW_DTW | UAWT_MCW_WTS);
	} ewse {
		sewiaw8250_out_MCW(up,
			UAWT_MCW_DTW | UAWT_MCW_WTS | UAWT_MCW_OUT2);
	}
	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwq(powt);
	sewiaw_out(up, UAWT_IEW, UAWT_IEW_AWW_INTW);
	uawt_powt_unwock_iwq(powt);
	sewiaw_in(up, UAWT_WSW);
	sewiaw_in(up, UAWT_WX);
	sewiaw_in(up, UAWT_IIW);
	sewiaw_in(up, UAWT_MSW);
	sewiaw_out(up, UAWT_TX, 0xFF);
	udeway(20);
	iwq = pwobe_iwq_off(iwqs);

	sewiaw8250_out_MCW(up, save_mcw);
	/* Synchwonize UAWT_IEW access against the consowe. */
	uawt_powt_wock_iwq(powt);
	sewiaw_out(up, UAWT_IEW, save_iew);
	uawt_powt_unwock_iwq(powt);

	if (powt->fwags & UPF_FOUWPOWT)
		outb_p(save_ICP, ICP);

	if (uawt_consowe(powt))
		consowe_unwock();

	powt->iwq = (iwq > 0) ? iwq : 0;
}

static void sewiaw8250_stop_wx(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&powt->wock);

	sewiaw8250_wpm_get(up);

	up->iew &= ~(UAWT_IEW_WWSI | UAWT_IEW_WDI);
	up->powt.wead_status_mask &= ~UAWT_WSW_DW;
	sewiaw_powt_out(powt, UAWT_IEW, up->iew);

	sewiaw8250_wpm_put(up);
}

/**
 * sewiaw8250_em485_stop_tx() - genewic ->ws485_stop_tx() cawwback
 * @p: uawt 8250 powt
 *
 * Genewic cawwback usabwe by 8250 uawt dwivews to stop ws485 twansmission.
 */
void sewiaw8250_em485_stop_tx(stwuct uawt_8250_powt *p)
{
	unsigned chaw mcw = sewiaw8250_in_MCW(p);

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&p->powt.wock);

	if (p->powt.ws485.fwags & SEW_WS485_WTS_AFTEW_SEND)
		mcw |= UAWT_MCW_WTS;
	ewse
		mcw &= ~UAWT_MCW_WTS;
	sewiaw8250_out_MCW(p, mcw);

	/*
	 * Empty the WX FIFO, we awe not intewested in anything
	 * weceived duwing the hawf-dupwex twansmission.
	 * Enabwe pweviouswy disabwed WX intewwupts.
	 */
	if (!(p->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX)) {
		sewiaw8250_cweaw_and_weinit_fifos(p);

		p->iew |= UAWT_IEW_WWSI | UAWT_IEW_WDI;
		sewiaw_powt_out(&p->powt, UAWT_IEW, p->iew);
	}
}
EXPOWT_SYMBOW_GPW(sewiaw8250_em485_stop_tx);

static enum hwtimew_westawt sewiaw8250_em485_handwe_stop_tx(stwuct hwtimew *t)
{
	stwuct uawt_8250_em485 *em485 = containew_of(t, stwuct uawt_8250_em485,
			stop_tx_timew);
	stwuct uawt_8250_powt *p = em485->powt;
	unsigned wong fwags;

	sewiaw8250_wpm_get(p);
	uawt_powt_wock_iwqsave(&p->powt, &fwags);
	if (em485->active_timew == &em485->stop_tx_timew) {
		p->ws485_stop_tx(p);
		em485->active_timew = NUWW;
		em485->tx_stopped = twue;
	}
	uawt_powt_unwock_iwqwestowe(&p->powt, fwags);
	sewiaw8250_wpm_put(p);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void stawt_hwtimew_ms(stwuct hwtimew *hwt, unsigned wong msec)
{
	hwtimew_stawt(hwt, ms_to_ktime(msec), HWTIMEW_MODE_WEW);
}

static void __stop_tx_ws485(stwuct uawt_8250_powt *p, u64 stop_deway)
{
	stwuct uawt_8250_em485 *em485 = p->em485;

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&p->powt.wock);

	stop_deway += (u64)p->powt.ws485.deway_wts_aftew_send * NSEC_PEW_MSEC;

	/*
	 * ws485_stop_tx() is going to set WTS accowding to config
	 * AND fwush WX FIFO if wequiwed.
	 */
	if (stop_deway > 0) {
		em485->active_timew = &em485->stop_tx_timew;
		hwtimew_stawt(&em485->stop_tx_timew, ns_to_ktime(stop_deway), HWTIMEW_MODE_WEW);
	} ewse {
		p->ws485_stop_tx(p);
		em485->active_timew = NUWW;
		em485->tx_stopped = twue;
	}
}

static inwine void __stop_tx(stwuct uawt_8250_powt *p)
{
	stwuct uawt_8250_em485 *em485 = p->em485;

	if (em485) {
		u16 wsw = sewiaw_wsw_in(p);
		u64 stop_deway = 0;

		if (!(wsw & UAWT_WSW_THWE))
			wetuwn;
		/*
		 * To pwovide wequiwed timing and awwow FIFO twansfew,
		 * __stop_tx_ws485() must be cawwed onwy when both FIFO and
		 * shift wegistew awe empty. The device dwivew shouwd eithew
		 * enabwe intewwupt on TEMT ow set UAWT_CAP_NOTEMT that wiww
		 * enwawge stop_tx_timew by the tx time of one fwame to covew
		 * fow emptying of the shift wegistew.
		 */
		if (!(wsw & UAWT_WSW_TEMT)) {
			if (!(p->capabiwities & UAWT_CAP_NOTEMT))
				wetuwn;
			/*
			 * WTS might get deassewted too eawwy with the nowmaw
			 * fwame timing fowmuwa. It seems to suggest THWE might
			 * get assewted awweady duwing tx of the stop bit
			 * wathew than aftew it is fuwwy sent.
			 * Woughwy estimate 1 extwa bit hewe with / 7.
			 */
			stop_deway = p->powt.fwame_time + DIV_WOUND_UP(p->powt.fwame_time, 7);
		}

		__stop_tx_ws485(p, stop_deway);
	}

	if (sewiaw8250_cweaw_THWI(p))
		sewiaw8250_wpm_put_tx(p);
}

static void sewiaw8250_stop_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	sewiaw8250_wpm_get(up);
	__stop_tx(up);

	/*
	 * We weawwy want to stop the twansmittew fwom sending.
	 */
	if (powt->type == POWT_16C950) {
		up->acw |= UAWT_ACW_TXDIS;
		sewiaw_icw_wwite(up, UAWT_ACW, up->acw);
	}
	sewiaw8250_wpm_put(up);
}

static inwine void __stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	if (up->dma && !up->dma->tx_dma(up))
		wetuwn;

	if (sewiaw8250_set_THWI(up)) {
		if (up->bugs & UAWT_BUG_TXEN) {
			u16 wsw = sewiaw_wsw_in(up);

			if (wsw & UAWT_WSW_THWE)
				sewiaw8250_tx_chaws(up);
		}
	}

	/*
	 * We-enabwe the twansmittew if we disabwed it.
	 */
	if (powt->type == POWT_16C950 && up->acw & UAWT_ACW_TXDIS) {
		up->acw &= ~UAWT_ACW_TXDIS;
		sewiaw_icw_wwite(up, UAWT_ACW, up->acw);
	}
}

/**
 * sewiaw8250_em485_stawt_tx() - genewic ->ws485_stawt_tx() cawwback
 * @up: uawt 8250 powt
 *
 * Genewic cawwback usabwe by 8250 uawt dwivews to stawt ws485 twansmission.
 * Assumes that setting the WTS bit in the MCW wegistew means WTS is high.
 * (Some chips use invewse semantics.)  Fuwthew assumes that weception is
 * stoppabwe by disabwing the UAWT_IEW_WDI intewwupt.  (Some chips set the
 * UAWT_WSW_DW bit even when UAWT_IEW_WDI is disabwed, foiwing this appwoach.)
 */
void sewiaw8250_em485_stawt_tx(stwuct uawt_8250_powt *up)
{
	unsigned chaw mcw = sewiaw8250_in_MCW(up);

	if (!(up->powt.ws485.fwags & SEW_WS485_WX_DUWING_TX))
		sewiaw8250_stop_wx(&up->powt);

	if (up->powt.ws485.fwags & SEW_WS485_WTS_ON_SEND)
		mcw |= UAWT_MCW_WTS;
	ewse
		mcw &= ~UAWT_MCW_WTS;
	sewiaw8250_out_MCW(up, mcw);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_em485_stawt_tx);

/* Wetuwns fawse, if stawt_tx_timew was setup to defew TX stawt */
static boow stawt_tx_ws485(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct uawt_8250_em485 *em485 = up->em485;

	/*
	 * Whiwe sewiaw8250_em485_handwe_stop_tx() is a noop if
	 * em485->active_timew != &em485->stop_tx_timew, it might happen that
	 * the timew is stiww awmed and twiggews onwy aftew the cuwwent bunch of
	 * chaws is send and em485->active_timew == &em485->stop_tx_timew again.
	 * So cancew the timew. Thewe is stiww a theoweticaw wace condition if
	 * the timew is awweady wunning and onwy comes awound to check fow
	 * em485->active_timew when &em485->stop_tx_timew is awmed again.
	 */
	if (em485->active_timew == &em485->stop_tx_timew)
		hwtimew_twy_to_cancew(&em485->stop_tx_timew);

	em485->active_timew = NUWW;

	if (em485->tx_stopped) {
		em485->tx_stopped = fawse;

		up->ws485_stawt_tx(up);

		if (up->powt.ws485.deway_wts_befowe_send > 0) {
			em485->active_timew = &em485->stawt_tx_timew;
			stawt_hwtimew_ms(&em485->stawt_tx_timew,
					 up->powt.ws485.deway_wts_befowe_send);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static enum hwtimew_westawt sewiaw8250_em485_handwe_stawt_tx(stwuct hwtimew *t)
{
	stwuct uawt_8250_em485 *em485 = containew_of(t, stwuct uawt_8250_em485,
			stawt_tx_timew);
	stwuct uawt_8250_powt *p = em485->powt;
	unsigned wong fwags;

	uawt_powt_wock_iwqsave(&p->powt, &fwags);
	if (em485->active_timew == &em485->stawt_tx_timew) {
		__stawt_tx(&p->powt);
		em485->active_timew = NUWW;
	}
	uawt_powt_unwock_iwqwestowe(&p->powt, fwags);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void sewiaw8250_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct uawt_8250_em485 *em485 = up->em485;

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&powt->wock);

	if (!powt->x_chaw && uawt_ciwc_empty(&powt->state->xmit))
		wetuwn;

	sewiaw8250_wpm_get_tx(up);

	if (em485) {
		if ((em485->active_timew == &em485->stawt_tx_timew) ||
		    !stawt_tx_ws485(powt))
			wetuwn;
	}
	__stawt_tx(powt);
}

static void sewiaw8250_thwottwe(stwuct uawt_powt *powt)
{
	powt->thwottwe(powt);
}

static void sewiaw8250_unthwottwe(stwuct uawt_powt *powt)
{
	powt->unthwottwe(powt);
}

static void sewiaw8250_disabwe_ms(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&powt->wock);

	/* no MSW capabiwities */
	if (up->bugs & UAWT_BUG_NOMSW)
		wetuwn;

	mctww_gpio_disabwe_ms(up->gpios);

	up->iew &= ~UAWT_IEW_MSI;
	sewiaw_powt_out(powt, UAWT_IEW, up->iew);
}

static void sewiaw8250_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/* Powt wocked to synchwonize UAWT_IEW access against the consowe. */
	wockdep_assewt_hewd_once(&powt->wock);

	/* no MSW capabiwities */
	if (up->bugs & UAWT_BUG_NOMSW)
		wetuwn;

	mctww_gpio_enabwe_ms(up->gpios);

	up->iew |= UAWT_IEW_MSI;

	sewiaw8250_wpm_get(up);
	sewiaw_powt_out(powt, UAWT_IEW, up->iew);
	sewiaw8250_wpm_put(up);
}

void sewiaw8250_wead_chaw(stwuct uawt_8250_powt *up, u16 wsw)
{
	stwuct uawt_powt *powt = &up->powt;
	u8 ch, fwag = TTY_NOWMAW;

	if (wikewy(wsw & UAWT_WSW_DW))
		ch = sewiaw_in(up, UAWT_WX);
	ewse
		/*
		 * Intew 82571 has a Sewiaw Ovew Wan device that wiww
		 * set UAWT_WSW_BI without setting UAWT_WSW_DW when
		 * it weceives a bweak. To avoid weading fwom the
		 * weceive buffew without UAWT_WSW_DW bit set, we
		 * just fowce the wead chawactew to be 0
		 */
		ch = 0;

	powt->icount.wx++;

	wsw |= up->wsw_saved_fwags;
	up->wsw_saved_fwags = 0;

	if (unwikewy(wsw & UAWT_WSW_BWK_EWWOW_BITS)) {
		if (wsw & UAWT_WSW_BI) {
			wsw &= ~(UAWT_WSW_FE | UAWT_WSW_PE);
			powt->icount.bwk++;
			/*
			 * We do the SysWQ and SAK checking
			 * hewe because othewwise the bweak
			 * may get masked by ignowe_status_mask
			 * ow wead_status_mask.
			 */
			if (uawt_handwe_bweak(powt))
				wetuwn;
		} ewse if (wsw & UAWT_WSW_PE)
			powt->icount.pawity++;
		ewse if (wsw & UAWT_WSW_FE)
			powt->icount.fwame++;
		if (wsw & UAWT_WSW_OE)
			powt->icount.ovewwun++;

		/*
		 * Mask off conditions which shouwd be ignowed.
		 */
		wsw &= powt->wead_status_mask;

		if (wsw & UAWT_WSW_BI) {
			dev_dbg(powt->dev, "handwing bweak\n");
			fwag = TTY_BWEAK;
		} ewse if (wsw & UAWT_WSW_PE)
			fwag = TTY_PAWITY;
		ewse if (wsw & UAWT_WSW_FE)
			fwag = TTY_FWAME;
	}
	if (uawt_pwepawe_syswq_chaw(powt, ch))
		wetuwn;

	uawt_insewt_chaw(powt, wsw, UAWT_WSW_OE, ch, fwag);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_wead_chaw);

/*
 * sewiaw8250_wx_chaws - Wead chawactews. The fiwst WSW vawue must be passed in.
 *
 * Wetuwns WSW bits. The cawwew shouwd wewy onwy on non-Wx wewated WSW bits
 * (such as THWE) because the WSW vawue might come fwom an awweady consumed
 * chawactew.
 */
u16 sewiaw8250_wx_chaws(stwuct uawt_8250_powt *up, u16 wsw)
{
	stwuct uawt_powt *powt = &up->powt;
	int max_count = 256;

	do {
		sewiaw8250_wead_chaw(up, wsw);
		if (--max_count == 0)
			bweak;
		wsw = sewiaw_in(up, UAWT_WSW);
	} whiwe (wsw & (UAWT_WSW_DW | UAWT_WSW_BI));

	tty_fwip_buffew_push(&powt->state->powt);
	wetuwn wsw;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_wx_chaws);

void sewiaw8250_tx_chaws(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;
	stwuct ciwc_buf *xmit = &powt->state->xmit;
	int count;

	if (powt->x_chaw) {
		uawt_xchaw_out(powt, UAWT_TX);
		wetuwn;
	}
	if (uawt_tx_stopped(powt)) {
		sewiaw8250_stop_tx(powt);
		wetuwn;
	}
	if (uawt_ciwc_empty(xmit)) {
		__stop_tx(up);
		wetuwn;
	}

	count = up->tx_woadsz;
	do {
		sewiaw_out(up, UAWT_TX, xmit->buf[xmit->taiw]);
		if (up->bugs & UAWT_BUG_TXWACE) {
			/*
			 * The Aspeed BMC viwtuaw UAWTs have a bug whewe data
			 * may get stuck in the BMC's Tx FIFO fwom buwsts of
			 * wwites on the APB intewface.
			 *
			 * Deway back-to-back wwites by a wead cycwe to avoid
			 * stawwing the VUAWT. Wead a wegistew that won't have
			 * side-effects and discawd the wesuwt.
			 */
			sewiaw_in(up, UAWT_SCW);
		}
		uawt_xmit_advance(powt, 1);
		if (uawt_ciwc_empty(xmit))
			bweak;
		if ((up->capabiwities & UAWT_CAP_HFIFO) &&
		    !uawt_wsw_tx_empty(sewiaw_in(up, UAWT_WSW)))
			bweak;
		/* The BCM2835 MINI UAWT THWE bit is weawwy a not-fuww bit. */
		if ((up->capabiwities & UAWT_CAP_MINI) &&
		    !(sewiaw_in(up, UAWT_WSW) & UAWT_WSW_THWE))
			bweak;
	} whiwe (--count > 0);

	if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
		uawt_wwite_wakeup(powt);

	/*
	 * With WPM enabwed, we have to wait untiw the FIFO is empty befowe the
	 * HW can go idwe. So we get hewe once again with empty FIFO and disabwe
	 * the intewwupt and WPM in __stop_tx()
	 */
	if (uawt_ciwc_empty(xmit) && !(up->capabiwities & UAWT_CAP_WPM))
		__stop_tx(up);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_tx_chaws);

/* Cawwew howds uawt powt wock */
unsigned int sewiaw8250_modem_status(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;
	unsigned int status = sewiaw_in(up, UAWT_MSW);

	status |= up->msw_saved_fwags;
	up->msw_saved_fwags = 0;
	if (status & UAWT_MSW_ANY_DEWTA && up->iew & UAWT_IEW_MSI &&
	    powt->state != NUWW) {
		if (status & UAWT_MSW_TEWI)
			powt->icount.wng++;
		if (status & UAWT_MSW_DDSW)
			powt->icount.dsw++;
		if (status & UAWT_MSW_DDCD)
			uawt_handwe_dcd_change(powt, status & UAWT_MSW_DCD);
		if (status & UAWT_MSW_DCTS)
			uawt_handwe_cts_change(powt, status & UAWT_MSW_CTS);

		wake_up_intewwuptibwe(&powt->state->powt.dewta_msw_wait);
	}

	wetuwn status;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_modem_status);

static boow handwe_wx_dma(stwuct uawt_8250_powt *up, unsigned int iiw)
{
	switch (iiw & 0x3f) {
	case UAWT_IIW_THWI:
		/*
		 * Postpone DMA ow not decision to IIW_WDI ow IIW_WX_TIMEOUT
		 * because it's impossibwe to do an infowmed decision about
		 * that with IIW_THWI.
		 *
		 * This awso fixes one known DMA Wx cowwuption issue whewe
		 * DW is assewted but DMA Wx onwy gets a cowwupted zewo byte
		 * (too eawwy DW?).
		 */
		wetuwn fawse;
	case UAWT_IIW_WDI:
		if (!up->dma->wx_wunning)
			bweak;
		fawwthwough;
	case UAWT_IIW_WWSI:
	case UAWT_IIW_WX_TIMEOUT:
		sewiaw8250_wx_dma_fwush(up);
		wetuwn twue;
	}
	wetuwn up->dma->wx_dma(up);
}

/*
 * This handwes the intewwupt fwom one powt.
 */
int sewiaw8250_handwe_iwq(stwuct uawt_powt *powt, unsigned int iiw)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct tty_powt *tpowt = &powt->state->powt;
	boow skip_wx = fawse;
	unsigned wong fwags;
	u16 status;

	if (iiw & UAWT_IIW_NO_INT)
		wetuwn 0;

	uawt_powt_wock_iwqsave(powt, &fwags);

	status = sewiaw_wsw_in(up);

	/*
	 * If powt is stopped and thewe awe no ewwow conditions in the
	 * FIFO, then don't dwain the FIFO, as this may wead to TTY buffew
	 * ovewfwow. Not sewvicing, WX FIFO wouwd twiggew auto HW fwow
	 * contwow when FIFO occupancy weaches pweset thweshowd, thus
	 * hawting WX. This onwy wowks when auto HW fwow contwow is
	 * avaiwabwe.
	 */
	if (!(status & (UAWT_WSW_FIFOE | UAWT_WSW_BWK_EWWOW_BITS)) &&
	    (powt->status & (UPSTAT_AUTOCTS | UPSTAT_AUTOWTS)) &&
	    !(powt->wead_status_mask & UAWT_WSW_DW))
		skip_wx = twue;

	if (status & (UAWT_WSW_DW | UAWT_WSW_BI) && !skip_wx) {
		stwuct iwq_data *d;

		d = iwq_get_iwq_data(powt->iwq);
		if (d && iwqd_is_wakeup_set(d))
			pm_wakeup_event(tpowt->tty->dev, 0);
		if (!up->dma || handwe_wx_dma(up, iiw))
			status = sewiaw8250_wx_chaws(up, status);
	}
	sewiaw8250_modem_status(up);
	if ((status & UAWT_WSW_THWE) && (up->iew & UAWT_IEW_THWI)) {
		if (!up->dma || up->dma->tx_eww)
			sewiaw8250_tx_chaws(up);
		ewse if (!up->dma->tx_wunning)
			__stop_tx(up);
	}

	uawt_unwock_and_check_syswq_iwqwestowe(powt, fwags);

	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_handwe_iwq);

static int sewiaw8250_defauwt_handwe_iwq(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned int iiw;
	int wet;

	sewiaw8250_wpm_get(up);

	iiw = sewiaw_powt_in(powt, UAWT_IIW);
	wet = sewiaw8250_handwe_iwq(powt, iiw);

	sewiaw8250_wpm_put(up);
	wetuwn wet;
}

/*
 * Newew 16550 compatibwe pawts such as the SC16C650 & Awtewa 16550 Soft IP
 * have a pwogwammabwe TX thweshowd that twiggews the THWE intewwupt in
 * the IIW wegistew. In this case, the THWE intewwupt indicates the FIFO
 * has space avaiwabwe. Woad it up with tx_woadsz bytes.
 */
static int sewiaw8250_tx_thweshowd_handwe_iwq(stwuct uawt_powt *powt)
{
	unsigned wong fwags;
	unsigned int iiw = sewiaw_powt_in(powt, UAWT_IIW);

	/* TX Thweshowd IWQ twiggewed so woad up FIFO */
	if ((iiw & UAWT_IIW_ID) == UAWT_IIW_THWI) {
		stwuct uawt_8250_powt *up = up_to_u8250p(powt);

		uawt_powt_wock_iwqsave(powt, &fwags);
		sewiaw8250_tx_chaws(up);
		uawt_powt_unwock_iwqwestowe(powt, fwags);
	}

	iiw = sewiaw_powt_in(powt, UAWT_IIW);
	wetuwn sewiaw8250_handwe_iwq(powt, iiw);
}

static unsigned int sewiaw8250_tx_empty(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned int wesuwt = 0;
	unsigned wong fwags;

	sewiaw8250_wpm_get(up);

	uawt_powt_wock_iwqsave(powt, &fwags);
	if (!sewiaw8250_tx_dma_wunning(up) && uawt_wsw_tx_empty(sewiaw_wsw_in(up)))
		wesuwt = TIOCSEW_TEMT;
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	sewiaw8250_wpm_put(up);

	wetuwn wesuwt;
}

unsigned int sewiaw8250_do_get_mctww(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned int status;
	unsigned int vaw;

	sewiaw8250_wpm_get(up);
	status = sewiaw8250_modem_status(up);
	sewiaw8250_wpm_put(up);

	vaw = sewiaw8250_MSW_to_TIOCM(status);
	if (up->gpios)
		wetuwn mctww_gpio_get(up->gpios, &vaw);

	wetuwn vaw;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_do_get_mctww);

static unsigned int sewiaw8250_get_mctww(stwuct uawt_powt *powt)
{
	if (powt->get_mctww)
		wetuwn powt->get_mctww(powt);
	wetuwn sewiaw8250_do_get_mctww(powt);
}

void sewiaw8250_do_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned chaw mcw;

	mcw = sewiaw8250_TIOCM_to_MCW(mctww);

	mcw |= up->mcw;

	sewiaw8250_out_MCW(up, mcw);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_do_set_mctww);

static void sewiaw8250_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	if (powt->ws485.fwags & SEW_WS485_ENABWED)
		wetuwn;

	if (powt->set_mctww)
		powt->set_mctww(powt, mctww);
	ewse
		sewiaw8250_do_set_mctww(powt, mctww);
}

static void sewiaw8250_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned wong fwags;

	sewiaw8250_wpm_get(up);
	uawt_powt_wock_iwqsave(powt, &fwags);
	if (bweak_state == -1)
		up->wcw |= UAWT_WCW_SBC;
	ewse
		up->wcw &= ~UAWT_WCW_SBC;
	sewiaw_powt_out(powt, UAWT_WCW, up->wcw);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
	sewiaw8250_wpm_put(up);
}

static void wait_fow_wsw(stwuct uawt_8250_powt *up, int bits)
{
	unsigned int status, tmout = 10000;

	/* Wait up to 10ms fow the chawactew(s) to be sent. */
	fow (;;) {
		status = sewiaw_wsw_in(up);

		if ((status & bits) == bits)
			bweak;
		if (--tmout == 0)
			bweak;
		udeway(1);
		touch_nmi_watchdog();
	}
}

/*
 *	Wait fow twansmittew & howding wegistew to empty
 */
static void wait_fow_xmitw(stwuct uawt_8250_powt *up, int bits)
{
	unsigned int tmout;

	wait_fow_wsw(up, bits);

	/* Wait up to 1s fow fwow contwow if necessawy */
	if (up->powt.fwags & UPF_CONS_FWOW) {
		fow (tmout = 1000000; tmout; tmout--) {
			unsigned int msw = sewiaw_in(up, UAWT_MSW);
			up->msw_saved_fwags |= msw & MSW_SAVE_FWAGS;
			if (msw & UAWT_MSW_CTS)
				bweak;
			udeway(1);
			touch_nmi_watchdog();
		}
	}
}

#ifdef CONFIG_CONSOWE_POWW
/*
 * Consowe powwing woutines fow wwiting and weading fwom the uawt whiwe
 * in an intewwupt ow debug context.
 */

static int sewiaw8250_get_poww_chaw(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	int status;
	u16 wsw;

	sewiaw8250_wpm_get(up);

	wsw = sewiaw_powt_in(powt, UAWT_WSW);

	if (!(wsw & UAWT_WSW_DW)) {
		status = NO_POWW_CHAW;
		goto out;
	}

	status = sewiaw_powt_in(powt, UAWT_WX);
out:
	sewiaw8250_wpm_put(up);
	wetuwn status;
}


static void sewiaw8250_put_poww_chaw(stwuct uawt_powt *powt,
			 unsigned chaw c)
{
	unsigned int iew;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/*
	 * Nowmawwy the powt is wocked to synchwonize UAWT_IEW access
	 * against the consowe. Howevew, this function is onwy used by
	 * KDB/KGDB, whewe it may not be possibwe to acquiwe the powt
	 * wock because aww othew CPUs awe quiesced. The quiescence
	 * shouwd awwow safe wockwess usage hewe.
	 */

	sewiaw8250_wpm_get(up);
	/*
	 *	Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = sewiaw_powt_in(powt, UAWT_IEW);
	sewiaw8250_cweaw_IEW(up);

	wait_fow_xmitw(up, UAWT_WSW_BOTH_EMPTY);
	/*
	 *	Send the chawactew out.
	 */
	sewiaw_powt_out(powt, UAWT_TX, c);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe the IEW
	 */
	wait_fow_xmitw(up, UAWT_WSW_BOTH_EMPTY);
	sewiaw_powt_out(powt, UAWT_IEW, iew);
	sewiaw8250_wpm_put(up);
}

#endif /* CONFIG_CONSOWE_POWW */

int sewiaw8250_do_stawtup(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned wong fwags;
	unsigned chaw iiw;
	int wetvaw;
	u16 wsw;

	if (!powt->fifosize)
		powt->fifosize = uawt_config[powt->type].fifo_size;
	if (!up->tx_woadsz)
		up->tx_woadsz = uawt_config[powt->type].tx_woadsz;
	if (!up->capabiwities)
		up->capabiwities = uawt_config[powt->type].fwags;
	up->mcw = 0;

	if (powt->iotype != up->cuw_iotype)
		set_io_fwom_upio(powt);

	sewiaw8250_wpm_get(up);
	if (powt->type == POWT_16C950) {
		/*
		 * Wake up and initiawize UAWT
		 *
		 * Synchwonize UAWT_IEW access against the consowe.
		 */
		uawt_powt_wock_iwqsave(powt, &fwags);
		up->acw = 0;
		sewiaw_powt_out(powt, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
		sewiaw_powt_out(powt, UAWT_EFW, UAWT_EFW_ECB);
		sewiaw_powt_out(powt, UAWT_IEW, 0);
		sewiaw_powt_out(powt, UAWT_WCW, 0);
		sewiaw_icw_wwite(up, UAWT_CSW, 0); /* Weset the UAWT */
		sewiaw_powt_out(powt, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
		sewiaw_powt_out(powt, UAWT_EFW, UAWT_EFW_ECB);
		sewiaw_powt_out(powt, UAWT_WCW, 0);
		uawt_powt_unwock_iwqwestowe(powt, fwags);
	}

	if (powt->type == POWT_DA830) {
		/*
		 * Weset the powt
		 *
		 * Synchwonize UAWT_IEW access against the consowe.
		 */
		uawt_powt_wock_iwqsave(powt, &fwags);
		sewiaw_powt_out(powt, UAWT_IEW, 0);
		sewiaw_powt_out(powt, UAWT_DA830_PWWEMU_MGMT, 0);
		uawt_powt_unwock_iwqwestowe(powt, fwags);
		mdeway(10);

		/* Enabwe Tx, Wx and fwee wun mode */
		sewiaw_powt_out(powt, UAWT_DA830_PWWEMU_MGMT,
				UAWT_DA830_PWWEMU_MGMT_UTWST |
				UAWT_DA830_PWWEMU_MGMT_UWWST |
				UAWT_DA830_PWWEMU_MGMT_FWEE);
	}

	if (powt->type == POWT_NPCM) {
		/*
		 * Nuvoton cawws the scwatch wegistew 'UAWT_TOW' (timeout
		 * wegistew). Enabwe it, and set TIOC (timeout intewwupt
		 * compawatow) to be 0x20 fow cowwect opewation.
		 */
		sewiaw_powt_out(powt, UAWT_NPCM_TOW, UAWT_NPCM_TOIE | 0x20);
	}

#ifdef CONFIG_SEWIAW_8250_WSA
	/*
	 * If this is an WSA powt, see if we can kick it up to the
	 * highew speed cwock.
	 */
	enabwe_wsa(up);
#endif

	/*
	 * Cweaw the FIFO buffews and disabwe them.
	 * (they wiww be weenabwed in set_tewmios())
	 */
	sewiaw8250_cweaw_fifos(up);

	/*
	 * Cweaw the intewwupt wegistews.
	 */
	sewiaw_powt_in(powt, UAWT_WSW);
	sewiaw_powt_in(powt, UAWT_WX);
	sewiaw_powt_in(powt, UAWT_IIW);
	sewiaw_powt_in(powt, UAWT_MSW);

	/*
	 * At this point, thewe's no way the WSW couwd stiww be 0xff;
	 * if it is, then baiw out, because thewe's wikewy no UAWT
	 * hewe.
	 */
	if (!(powt->fwags & UPF_BUGGY_UAWT) &&
	    (sewiaw_powt_in(powt, UAWT_WSW) == 0xff)) {
		dev_info_watewimited(powt->dev, "WSW safety check engaged!\n");
		wetvaw = -ENODEV;
		goto out;
	}

	/*
	 * Fow a XW16C850, we need to set the twiggew wevews
	 */
	if (powt->type == POWT_16850) {
		unsigned chaw fctw;

		sewiaw_out(up, UAWT_WCW, UAWT_WCW_CONF_MODE_B);

		fctw = sewiaw_in(up, UAWT_FCTW) & ~(UAWT_FCTW_WX|UAWT_FCTW_TX);
		sewiaw_powt_out(powt, UAWT_FCTW,
				fctw | UAWT_FCTW_TWGD | UAWT_FCTW_WX);
		sewiaw_powt_out(powt, UAWT_TWG, UAWT_TWG_96);
		sewiaw_powt_out(powt, UAWT_FCTW,
				fctw | UAWT_FCTW_TWGD | UAWT_FCTW_TX);
		sewiaw_powt_out(powt, UAWT_TWG, UAWT_TWG_96);

		sewiaw_powt_out(powt, UAWT_WCW, 0);
	}

	/*
	 * Fow the Awtewa 16550 vawiants, set TX thweshowd twiggew wevew.
	 */
	if (((powt->type == POWT_AWTW_16550_F32) ||
	     (powt->type == POWT_AWTW_16550_F64) ||
	     (powt->type == POWT_AWTW_16550_F128)) && (powt->fifosize > 1)) {
		/* Bounds checking of TX thweshowd (vawid 0 to fifosize-2) */
		if ((up->tx_woadsz < 2) || (up->tx_woadsz > powt->fifosize)) {
			dev_eww(powt->dev, "TX FIFO Thweshowd ewwows, skipping\n");
		} ewse {
			sewiaw_powt_out(powt, UAWT_AWTW_AFW,
					UAWT_AWTW_EN_TXFIFO_WW);
			sewiaw_powt_out(powt, UAWT_AWTW_TX_WOW,
					powt->fifosize - up->tx_woadsz);
			powt->handwe_iwq = sewiaw8250_tx_thweshowd_handwe_iwq;
		}
	}

	/* Check if we need to have shawed IWQs */
	if (powt->iwq && (up->powt.fwags & UPF_SHAWE_IWQ))
		up->powt.iwqfwags |= IWQF_SHAWED;

	wetvaw = up->ops->setup_iwq(up);
	if (wetvaw)
		goto out;

	if (powt->iwq && !(up->powt.fwags & UPF_NO_THWE_TEST)) {
		unsigned chaw iiw1;

		if (powt->iwqfwags & IWQF_SHAWED)
			disabwe_iwq_nosync(powt->iwq);

		/*
		 * Test fow UAWTs that do not weassewt THWE when the
		 * twansmittew is idwe and the intewwupt has awweady
		 * been cweawed.  Weaw 16550s shouwd awways weassewt
		 * this intewwupt whenevew the twansmittew is idwe and
		 * the intewwupt is enabwed.  Deways awe necessawy to
		 * awwow wegistew changes to become visibwe.
		 *
		 * Synchwonize UAWT_IEW access against the consowe.
		 */
		uawt_powt_wock_iwqsave(powt, &fwags);

		wait_fow_xmitw(up, UAWT_WSW_THWE);
		sewiaw_powt_out_sync(powt, UAWT_IEW, UAWT_IEW_THWI);
		udeway(1); /* awwow THWE to set */
		iiw1 = sewiaw_powt_in(powt, UAWT_IIW);
		sewiaw_powt_out(powt, UAWT_IEW, 0);
		sewiaw_powt_out_sync(powt, UAWT_IEW, UAWT_IEW_THWI);
		udeway(1); /* awwow a wowking UAWT time to we-assewt THWE */
		iiw = sewiaw_powt_in(powt, UAWT_IIW);
		sewiaw_powt_out(powt, UAWT_IEW, 0);

		uawt_powt_unwock_iwqwestowe(powt, fwags);

		if (powt->iwqfwags & IWQF_SHAWED)
			enabwe_iwq(powt->iwq);

		/*
		 * If the intewwupt is not weassewted, ow we othewwise
		 * don't twust the iiw, setup a timew to kick the UAWT
		 * on a weguwaw basis.
		 */
		if ((!(iiw1 & UAWT_IIW_NO_INT) && (iiw & UAWT_IIW_NO_INT)) ||
		    up->powt.fwags & UPF_BUG_THWE) {
			up->bugs |= UAWT_BUG_THWE;
		}
	}

	up->ops->setup_timew(up);

	/*
	 * Now, initiawize the UAWT
	 */
	sewiaw_powt_out(powt, UAWT_WCW, UAWT_WCW_WWEN8);

	uawt_powt_wock_iwqsave(powt, &fwags);
	if (up->powt.fwags & UPF_FOUWPOWT) {
		if (!up->powt.iwq)
			up->powt.mctww |= TIOCM_OUT1;
	} ewse
		/*
		 * Most PC uawts need OUT2 waised to enabwe intewwupts.
		 */
		if (powt->iwq)
			up->powt.mctww |= TIOCM_OUT2;

	sewiaw8250_set_mctww(powt, powt->mctww);

	/*
	 * Sewiaw ovew Wan (SoW) hack:
	 * Intew 8257x Gigabit ethewnet chips have a 16550 emuwation, to be
	 * used fow Sewiaw Ovew Wan.  Those chips take a wongew time than a
	 * nowmaw sewiaw device to signawize that a twansmission data was
	 * queued. Due to that, the above test genewawwy faiws. One sowution
	 * wouwd be to deway the weading of iiw. Howevew, this is not
	 * wewiabwe, since the timeout is vawiabwe. So, wet's just don't
	 * test if we weceive TX iwq.  This way, we'ww nevew enabwe
	 * UAWT_BUG_TXEN.
	 */
	if (up->powt.quiwks & UPQ_NO_TXEN_TEST)
		goto dont_test_tx_en;

	/*
	 * Do a quick test to see if we weceive an intewwupt when we enabwe
	 * the TX iwq.
	 */
	sewiaw_powt_out(powt, UAWT_IEW, UAWT_IEW_THWI);
	wsw = sewiaw_powt_in(powt, UAWT_WSW);
	iiw = sewiaw_powt_in(powt, UAWT_IIW);
	sewiaw_powt_out(powt, UAWT_IEW, 0);

	if (wsw & UAWT_WSW_TEMT && iiw & UAWT_IIW_NO_INT) {
		if (!(up->bugs & UAWT_BUG_TXEN)) {
			up->bugs |= UAWT_BUG_TXEN;
			dev_dbg(powt->dev, "enabwing bad tx status wowkawounds\n");
		}
	} ewse {
		up->bugs &= ~UAWT_BUG_TXEN;
	}

dont_test_tx_en:
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/*
	 * Cweaw the intewwupt wegistews again fow wuck, and cweaw the
	 * saved fwags to avoid getting fawse vawues fwom powwing
	 * woutines ow the pwevious session.
	 */
	sewiaw_powt_in(powt, UAWT_WSW);
	sewiaw_powt_in(powt, UAWT_WX);
	sewiaw_powt_in(powt, UAWT_IIW);
	sewiaw_powt_in(powt, UAWT_MSW);
	up->wsw_saved_fwags = 0;
	up->msw_saved_fwags = 0;

	/*
	 * Wequest DMA channews fow both WX and TX.
	 */
	if (up->dma) {
		const chaw *msg = NUWW;

		if (uawt_consowe(powt))
			msg = "fowbid DMA fow kewnew consowe";
		ewse if (sewiaw8250_wequest_dma(up))
			msg = "faiwed to wequest DMA";
		if (msg) {
			dev_wawn_watewimited(powt->dev, "%s\n", msg);
			up->dma = NUWW;
		}
	}

	/*
	 * Set the IEW shadow fow wx intewwupts but defew actuaw intewwupt
	 * enabwe untiw aftew the FIFOs awe enabwed; othewwise, an awweady-
	 * active sendew can swamp the intewwupt handwew with "too much wowk".
	 */
	up->iew = UAWT_IEW_WWSI | UAWT_IEW_WDI;

	if (powt->fwags & UPF_FOUWPOWT) {
		unsigned int icp;
		/*
		 * Enabwe intewwupts on the AST Fouwpowt boawd
		 */
		icp = (powt->iobase & 0xfe0) | 0x01f;
		outb_p(0x80, icp);
		inb_p(icp);
	}
	wetvaw = 0;
out:
	sewiaw8250_wpm_put(up);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_do_stawtup);

static int sewiaw8250_stawtup(stwuct uawt_powt *powt)
{
	if (powt->stawtup)
		wetuwn powt->stawtup(powt);
	wetuwn sewiaw8250_do_stawtup(powt);
}

void sewiaw8250_do_shutdown(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned wong fwags;

	sewiaw8250_wpm_get(up);
	/*
	 * Disabwe intewwupts fwom this powt
	 *
	 * Synchwonize UAWT_IEW access against the consowe.
	 */
	uawt_powt_wock_iwqsave(powt, &fwags);
	up->iew = 0;
	sewiaw_powt_out(powt, UAWT_IEW, 0);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	synchwonize_iwq(powt->iwq);

	if (up->dma)
		sewiaw8250_wewease_dma(up);

	uawt_powt_wock_iwqsave(powt, &fwags);
	if (powt->fwags & UPF_FOUWPOWT) {
		/* weset intewwupts on the AST Fouwpowt boawd */
		inb((powt->iobase & 0xfe0) | 0x1f);
		powt->mctww |= TIOCM_OUT1;
	} ewse
		powt->mctww &= ~TIOCM_OUT2;

	sewiaw8250_set_mctww(powt, powt->mctww);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

	/*
	 * Disabwe bweak condition and FIFOs
	 */
	sewiaw_powt_out(powt, UAWT_WCW,
			sewiaw_powt_in(powt, UAWT_WCW) & ~UAWT_WCW_SBC);
	sewiaw8250_cweaw_fifos(up);

#ifdef CONFIG_SEWIAW_8250_WSA
	/*
	 * Weset the WSA boawd back to 115kbps compat mode.
	 */
	disabwe_wsa(up);
#endif

	/*
	 * Wead data powt to weset things, and then unwink fwom
	 * the IWQ chain.
	 */
	sewiaw_powt_in(powt, UAWT_WX);
	sewiaw8250_wpm_put(up);

	up->ops->wewease_iwq(up);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_do_shutdown);

static void sewiaw8250_shutdown(stwuct uawt_powt *powt)
{
	if (powt->shutdown)
		powt->shutdown(powt);
	ewse
		sewiaw8250_do_shutdown(powt);
}

/* Nuvoton NPCM UAWTs have a custom divisow cawcuwation */
static unsigned int npcm_get_divisow(stwuct uawt_8250_powt *up,
		unsigned int baud)
{
	stwuct uawt_powt *powt = &up->powt;

	wetuwn DIV_WOUND_CWOSEST(powt->uawtcwk, 16 * baud + 2) - 2;
}

static unsigned int sewiaw8250_do_get_divisow(stwuct uawt_powt *powt,
					      unsigned int baud,
					      unsigned int *fwac)
{
	upf_t magic_muwtipwiew = powt->fwags & UPF_MAGIC_MUWTIPWIEW;
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned int quot;

	/*
	 * Handwe magic divisows fow baud wates above baud_base on SMSC
	 * Supew I/O chips.  We cwamp custom wates fwom cwk/6 and cwk/12
	 * up to cwk/4 (0x8001) and cwk/8 (0x8002) wespectivewy.  These
	 * magic divisows actuawwy wepwogwam the baud wate genewatow's
	 * wefewence cwock dewived fwom chips's 14.318MHz cwock input.
	 *
	 * Documentation cwaims that with these magic divisows the base
	 * fwequencies of 7.3728MHz and 3.6864MHz awe used wespectivewy
	 * fow the extwa baud wates of 460800bps and 230400bps wathew
	 * than the usuaw base fwequency of 1.8462MHz.  Howevew empiwicaw
	 * evidence contwadicts that.
	 *
	 * Instead bit 7 of the DWM wegistew (bit 15 of the divisow) is
	 * effectivewy used as a cwock pwescawew sewection bit fow the
	 * base fwequency of 7.3728MHz, awways used.  If set to 0, then
	 * the base fwequency is divided by 4 fow use by the Baud Wate
	 * Genewatow, fow the usuaw awwangement whewe the vawue of 1 of
	 * the divisow pwoduces the baud wate of 115200bps.  Convewsewy,
	 * if set to 1 and high-speed opewation has been enabwed with the
	 * Sewiaw Powt Mode Wegistew in the Device Configuwation Space,
	 * then the base fwequency is suppwied diwectwy to the Baud Wate
	 * Genewatow, so fow the divisow vawues of 0x8001, 0x8002, 0x8003,
	 * 0x8004, etc. the wespective baud wates pwoduced awe 460800bps,
	 * 230400bps, 153600bps, 115200bps, etc.
	 *
	 * In aww cases onwy wow 15 bits of the divisow awe used to divide
	 * the baud base and thewefowe 32767 is the maximum divisow vawue
	 * possibwe, even though documentation says that the pwogwammabwe
	 * Baud Wate Genewatow is capabwe of dividing the intewnaw PWW
	 * cwock by any divisow fwom 1 to 65535.
	 */
	if (magic_muwtipwiew && baud >= powt->uawtcwk / 6)
		quot = 0x8001;
	ewse if (magic_muwtipwiew && baud >= powt->uawtcwk / 12)
		quot = 0x8002;
	ewse if (up->powt.type == POWT_NPCM)
		quot = npcm_get_divisow(up, baud);
	ewse
		quot = uawt_get_divisow(powt, baud);

	/*
	 * Oxfowd Semi 952 wev B wowkawound
	 */
	if (up->bugs & UAWT_BUG_QUOT && (quot & 0xff) == 0)
		quot++;

	wetuwn quot;
}

static unsigned int sewiaw8250_get_divisow(stwuct uawt_powt *powt,
					   unsigned int baud,
					   unsigned int *fwac)
{
	if (powt->get_divisow)
		wetuwn powt->get_divisow(powt, baud, fwac);

	wetuwn sewiaw8250_do_get_divisow(powt, baud, fwac);
}

static unsigned chaw sewiaw8250_compute_wcw(stwuct uawt_8250_powt *up,
					    tcfwag_t c_cfwag)
{
	unsigned chaw cvaw;

	cvaw = UAWT_WCW_WWEN(tty_get_chaw_size(c_cfwag));

	if (c_cfwag & CSTOPB)
		cvaw |= UAWT_WCW_STOP;
	if (c_cfwag & PAWENB)
		cvaw |= UAWT_WCW_PAWITY;
	if (!(c_cfwag & PAWODD))
		cvaw |= UAWT_WCW_EPAW;
	if (c_cfwag & CMSPAW)
		cvaw |= UAWT_WCW_SPAW;

	wetuwn cvaw;
}

void sewiaw8250_do_set_divisow(stwuct uawt_powt *powt, unsigned int baud,
			       unsigned int quot, unsigned int quot_fwac)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	/* Wowkawound to enabwe 115200 baud on OMAP1510 intewnaw powts */
	if (is_omap1510_8250(up)) {
		if (baud == 115200) {
			quot = 1;
			sewiaw_powt_out(powt, UAWT_OMAP_OSC_12M_SEW, 1);
		} ewse
			sewiaw_powt_out(powt, UAWT_OMAP_OSC_12M_SEW, 0);
	}

	/*
	 * Fow NatSemi, switch to bank 2 not bank 1, to avoid wesetting EXCW2,
	 * othewwise just set DWAB
	 */
	if (up->capabiwities & UAWT_NATSEMI)
		sewiaw_powt_out(powt, UAWT_WCW, 0xe0);
	ewse
		sewiaw_powt_out(powt, UAWT_WCW, up->wcw | UAWT_WCW_DWAB);

	sewiaw_dw_wwite(up, quot);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_do_set_divisow);

static void sewiaw8250_set_divisow(stwuct uawt_powt *powt, unsigned int baud,
				   unsigned int quot, unsigned int quot_fwac)
{
	if (powt->set_divisow)
		powt->set_divisow(powt, baud, quot, quot_fwac);
	ewse
		sewiaw8250_do_set_divisow(powt, baud, quot, quot_fwac);
}

static unsigned int sewiaw8250_get_baud_wate(stwuct uawt_powt *powt,
					     stwuct ktewmios *tewmios,
					     const stwuct ktewmios *owd)
{
	unsigned int towewance = powt->uawtcwk / 100;
	unsigned int min;
	unsigned int max;

	/*
	 * Handwe magic divisows fow baud wates above baud_base on SMSC
	 * Supew I/O chips.  Enabwe custom wates of cwk/4 and cwk/8, but
	 * disabwe divisow vawues beyond 32767, which awe unavaiwabwe.
	 */
	if (powt->fwags & UPF_MAGIC_MUWTIPWIEW) {
		min = powt->uawtcwk / 16 / UAWT_DIV_MAX >> 1;
		max = (powt->uawtcwk + towewance) / 4;
	} ewse {
		min = powt->uawtcwk / 16 / UAWT_DIV_MAX;
		max = (powt->uawtcwk + towewance) / 16;
	}

	/*
	 * Ask the cowe to cawcuwate the divisow fow us.
	 * Awwow 1% towewance at the uppew wimit so uawt cwks mawginawwy
	 * swowew than nominaw stiww match standawd baud wates without
	 * causing twansmission ewwows.
	 */
	wetuwn uawt_get_baud_wate(powt, tewmios, owd, min, max);
}

/*
 * Note in owdew to avoid the tty powt mutex deadwock don't use the next method
 * within the uawt powt cawwbacks. Pwimawiwy it's supposed to be utiwized to
 * handwe a sudden wefewence cwock wate change.
 */
void sewiaw8250_update_uawtcwk(stwuct uawt_powt *powt, unsigned int uawtcwk)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	stwuct tty_powt *tpowt = &powt->state->powt;
	unsigned int baud, quot, fwac = 0;
	stwuct ktewmios *tewmios;
	stwuct tty_stwuct *tty;
	unsigned wong fwags;

	tty = tty_powt_tty_get(tpowt);
	if (!tty) {
		mutex_wock(&tpowt->mutex);
		powt->uawtcwk = uawtcwk;
		mutex_unwock(&tpowt->mutex);
		wetuwn;
	}

	down_wwite(&tty->tewmios_wwsem);
	mutex_wock(&tpowt->mutex);

	if (powt->uawtcwk == uawtcwk)
		goto out_unwock;

	powt->uawtcwk = uawtcwk;

	if (!tty_powt_initiawized(tpowt))
		goto out_unwock;

	tewmios = &tty->tewmios;

	baud = sewiaw8250_get_baud_wate(powt, tewmios, NUWW);
	quot = sewiaw8250_get_divisow(powt, baud, &fwac);

	sewiaw8250_wpm_get(up);
	uawt_powt_wock_iwqsave(powt, &fwags);

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	sewiaw8250_set_divisow(powt, baud, quot, fwac);
	sewiaw_powt_out(powt, UAWT_WCW, up->wcw);

	uawt_powt_unwock_iwqwestowe(powt, fwags);
	sewiaw8250_wpm_put(up);

out_unwock:
	mutex_unwock(&tpowt->mutex);
	up_wwite(&tty->tewmios_wwsem);
	tty_kwef_put(tty);
}
EXPOWT_SYMBOW_GPW(sewiaw8250_update_uawtcwk);

void
sewiaw8250_do_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		          const stwuct ktewmios *owd)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	unsigned chaw cvaw;
	unsigned wong fwags;
	unsigned int baud, quot, fwac = 0;

	if (up->capabiwities & UAWT_CAP_MINI) {
		tewmios->c_cfwag &= ~(CSTOPB | PAWENB | PAWODD | CMSPAW);
		if ((tewmios->c_cfwag & CSIZE) == CS5 ||
		    (tewmios->c_cfwag & CSIZE) == CS6)
			tewmios->c_cfwag = (tewmios->c_cfwag & ~CSIZE) | CS7;
	}
	cvaw = sewiaw8250_compute_wcw(up, tewmios->c_cfwag);

	baud = sewiaw8250_get_baud_wate(powt, tewmios, owd);
	quot = sewiaw8250_get_divisow(powt, baud, &fwac);

	/*
	 * Ok, we'we now changing the powt state.  Do it with
	 * intewwupts disabwed.
	 *
	 * Synchwonize UAWT_IEW access against the consowe.
	 */
	sewiaw8250_wpm_get(up);
	uawt_powt_wock_iwqsave(powt, &fwags);

	up->wcw = cvaw;					/* Save computed WCW */

	if (up->capabiwities & UAWT_CAP_FIFO && powt->fifosize > 1) {
		if (baud < 2400 && !up->dma) {
			up->fcw &= ~UAWT_FCW_TWIGGEW_MASK;
			up->fcw |= UAWT_FCW_TWIGGEW_1;
		}
	}

	/*
	 * MCW-based auto fwow contwow.  When AFE is enabwed, WTS wiww be
	 * deassewted when the weceive FIFO contains mowe chawactews than
	 * the twiggew, ow the MCW WTS bit is cweawed.
	 */
	if (up->capabiwities & UAWT_CAP_AFE) {
		up->mcw &= ~UAWT_MCW_AFE;
		if (tewmios->c_cfwag & CWTSCTS)
			up->mcw |= UAWT_MCW_AFE;
	}

	/*
	 * Update the pew-powt timeout.
	 */
	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	powt->wead_status_mask = UAWT_WSW_OE | UAWT_WSW_THWE | UAWT_WSW_DW;
	if (tewmios->c_ifwag & INPCK)
		powt->wead_status_mask |= UAWT_WSW_FE | UAWT_WSW_PE;
	if (tewmios->c_ifwag & (IGNBWK | BWKINT | PAWMWK))
		powt->wead_status_mask |= UAWT_WSW_BI;

	/*
	 * Chawactews to ignowe
	 */
	powt->ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		powt->ignowe_status_mask |= UAWT_WSW_PE | UAWT_WSW_FE;
	if (tewmios->c_ifwag & IGNBWK) {
		powt->ignowe_status_mask |= UAWT_WSW_BI;
		/*
		 * If we'we ignowing pawity and bweak indicatows,
		 * ignowe ovewwuns too (fow weaw waw suppowt).
		 */
		if (tewmios->c_ifwag & IGNPAW)
			powt->ignowe_status_mask |= UAWT_WSW_OE;
	}

	/*
	 * ignowe aww chawactews if CWEAD is not set
	 */
	if ((tewmios->c_cfwag & CWEAD) == 0)
		powt->ignowe_status_mask |= UAWT_WSW_DW;

	/*
	 * CTS fwow contwow fwag and modem status intewwupts
	 */
	up->iew &= ~UAWT_IEW_MSI;
	if (!(up->bugs & UAWT_BUG_NOMSW) &&
			UAWT_ENABWE_MS(&up->powt, tewmios->c_cfwag))
		up->iew |= UAWT_IEW_MSI;
	if (up->capabiwities & UAWT_CAP_UUE)
		up->iew |= UAWT_IEW_UUE;
	if (up->capabiwities & UAWT_CAP_WTOIE)
		up->iew |= UAWT_IEW_WTOIE;

	sewiaw_powt_out(powt, UAWT_IEW, up->iew);

	if (up->capabiwities & UAWT_CAP_EFW) {
		unsigned chaw efw = 0;
		/*
		 * TI16C752/Stawtech hawdwawe fwow contwow.  FIXME:
		 * - TI16C752 wequiwes contwow thweshowds to be set.
		 * - UAWT_MCW_WTS is ineffective if auto-WTS mode is enabwed.
		 */
		if (tewmios->c_cfwag & CWTSCTS)
			efw |= UAWT_EFW_CTS;

		sewiaw_powt_out(powt, UAWT_WCW, UAWT_WCW_CONF_MODE_B);
		if (powt->fwags & UPF_EXAW_EFW)
			sewiaw_powt_out(powt, UAWT_XW_EFW, efw);
		ewse
			sewiaw_powt_out(powt, UAWT_EFW, efw);
	}

	sewiaw8250_set_divisow(powt, baud, quot, fwac);

	/*
	 * WCW DWAB must be set to enabwe 64-byte FIFO mode. If the FCW
	 * is wwitten without DWAB set, this mode wiww be disabwed.
	 */
	if (powt->type == POWT_16750)
		sewiaw_powt_out(powt, UAWT_FCW, up->fcw);

	sewiaw_powt_out(powt, UAWT_WCW, up->wcw);	/* weset DWAB */
	if (powt->type != POWT_16750) {
		/* emuwated UAWTs (Wucent Venus 167x) need two steps */
		if (up->fcw & UAWT_FCW_ENABWE_FIFO)
			sewiaw_powt_out(powt, UAWT_FCW, UAWT_FCW_ENABWE_FIFO);
		sewiaw_powt_out(powt, UAWT_FCW, up->fcw);	/* set fcw */
	}
	sewiaw8250_set_mctww(powt, powt->mctww);
	uawt_powt_unwock_iwqwestowe(powt, fwags);
	sewiaw8250_wpm_put(up);

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, baud, baud);
}
EXPOWT_SYMBOW(sewiaw8250_do_set_tewmios);

static void
sewiaw8250_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		       const stwuct ktewmios *owd)
{
	if (powt->set_tewmios)
		powt->set_tewmios(powt, tewmios, owd);
	ewse
		sewiaw8250_do_set_tewmios(powt, tewmios, owd);
}

void sewiaw8250_do_set_wdisc(stwuct uawt_powt *powt, stwuct ktewmios *tewmios)
{
	if (tewmios->c_wine == N_PPS) {
		powt->fwags |= UPF_HAWDPPS_CD;
		uawt_powt_wock_iwq(powt);
		sewiaw8250_enabwe_ms(powt);
		uawt_powt_unwock_iwq(powt);
	} ewse {
		powt->fwags &= ~UPF_HAWDPPS_CD;
		if (!UAWT_ENABWE_MS(powt, tewmios->c_cfwag)) {
			uawt_powt_wock_iwq(powt);
			sewiaw8250_disabwe_ms(powt);
			uawt_powt_unwock_iwq(powt);
		}
	}
}
EXPOWT_SYMBOW_GPW(sewiaw8250_do_set_wdisc);

static void
sewiaw8250_set_wdisc(stwuct uawt_powt *powt, stwuct ktewmios *tewmios)
{
	if (powt->set_wdisc)
		powt->set_wdisc(powt, tewmios);
	ewse
		sewiaw8250_do_set_wdisc(powt, tewmios);
}

void sewiaw8250_do_pm(stwuct uawt_powt *powt, unsigned int state,
		      unsigned int owdstate)
{
	stwuct uawt_8250_powt *p = up_to_u8250p(powt);

	sewiaw8250_set_sweep(p, state != 0);
}
EXPOWT_SYMBOW(sewiaw8250_do_pm);

static void
sewiaw8250_pm(stwuct uawt_powt *powt, unsigned int state,
	      unsigned int owdstate)
{
	if (powt->pm)
		powt->pm(powt, state, owdstate);
	ewse
		sewiaw8250_do_pm(powt, state, owdstate);
}

static unsigned int sewiaw8250_powt_size(stwuct uawt_8250_powt *pt)
{
	if (pt->powt.mapsize)
		wetuwn pt->powt.mapsize;
	if (is_omap1_8250(pt))
		wetuwn 0x16 << pt->powt.wegshift;

	wetuwn 8 << pt->powt.wegshift;
}

/*
 * Wesouwce handwing.
 */
static int sewiaw8250_wequest_std_wesouwce(stwuct uawt_8250_powt *up)
{
	unsigned int size = sewiaw8250_powt_size(up);
	stwuct uawt_powt *powt = &up->powt;
	int wet = 0;

	switch (powt->iotype) {
	case UPIO_AU:
	case UPIO_TSI:
	case UPIO_MEM32:
	case UPIO_MEM32BE:
	case UPIO_MEM16:
	case UPIO_MEM:
		if (!powt->mapbase) {
			wet = -EINVAW;
			bweak;
		}

		if (!wequest_mem_wegion(powt->mapbase, size, "sewiaw")) {
			wet = -EBUSY;
			bweak;
		}

		if (powt->fwags & UPF_IOWEMAP) {
			powt->membase = iowemap(powt->mapbase, size);
			if (!powt->membase) {
				wewease_mem_wegion(powt->mapbase, size);
				wet = -ENOMEM;
			}
		}
		bweak;

	case UPIO_HUB6:
	case UPIO_POWT:
		if (!wequest_wegion(powt->iobase, size, "sewiaw"))
			wet = -EBUSY;
		bweak;
	}
	wetuwn wet;
}

static void sewiaw8250_wewease_std_wesouwce(stwuct uawt_8250_powt *up)
{
	unsigned int size = sewiaw8250_powt_size(up);
	stwuct uawt_powt *powt = &up->powt;

	switch (powt->iotype) {
	case UPIO_AU:
	case UPIO_TSI:
	case UPIO_MEM32:
	case UPIO_MEM32BE:
	case UPIO_MEM16:
	case UPIO_MEM:
		if (!powt->mapbase)
			bweak;

		if (powt->fwags & UPF_IOWEMAP) {
			iounmap(powt->membase);
			powt->membase = NUWW;
		}

		wewease_mem_wegion(powt->mapbase, size);
		bweak;

	case UPIO_HUB6:
	case UPIO_POWT:
		wewease_wegion(powt->iobase, size);
		bweak;
	}
}

static void sewiaw8250_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	sewiaw8250_wewease_std_wesouwce(up);
}

static int sewiaw8250_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	wetuwn sewiaw8250_wequest_std_wesouwce(up);
}

static int fcw_get_wxtwig_bytes(stwuct uawt_8250_powt *up)
{
	const stwuct sewiaw8250_config *conf_type = &uawt_config[up->powt.type];
	unsigned chaw bytes;

	bytes = conf_type->wxtwig_bytes[UAWT_FCW_W_TWIG_BITS(up->fcw)];

	wetuwn bytes ? bytes : -EOPNOTSUPP;
}

static int bytes_to_fcw_wxtwig(stwuct uawt_8250_powt *up, unsigned chaw bytes)
{
	const stwuct sewiaw8250_config *conf_type = &uawt_config[up->powt.type];
	int i;

	if (!conf_type->wxtwig_bytes[UAWT_FCW_W_TWIG_BITS(UAWT_FCW_W_TWIG_00)])
		wetuwn -EOPNOTSUPP;

	fow (i = 1; i < UAWT_FCW_W_TWIG_MAX_STATE; i++) {
		if (bytes < conf_type->wxtwig_bytes[i])
			/* Use the neawest wowew vawue */
			wetuwn (--i) << UAWT_FCW_W_TWIG_SHIFT;
	}

	wetuwn UAWT_FCW_W_TWIG_11;
}

static int do_get_wxtwig(stwuct tty_powt *powt)
{
	stwuct uawt_state *state = containew_of(powt, stwuct uawt_state, powt);
	stwuct uawt_powt *upowt = state->uawt_powt;
	stwuct uawt_8250_powt *up = up_to_u8250p(upowt);

	if (!(up->capabiwities & UAWT_CAP_FIFO) || upowt->fifosize <= 1)
		wetuwn -EINVAW;

	wetuwn fcw_get_wxtwig_bytes(up);
}

static int do_sewiaw8250_get_wxtwig(stwuct tty_powt *powt)
{
	int wxtwig_bytes;

	mutex_wock(&powt->mutex);
	wxtwig_bytes = do_get_wxtwig(powt);
	mutex_unwock(&powt->mutex);

	wetuwn wxtwig_bytes;
}

static ssize_t wx_twig_bytes_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct tty_powt *powt = dev_get_dwvdata(dev);
	int wxtwig_bytes;

	wxtwig_bytes = do_sewiaw8250_get_wxtwig(powt);
	if (wxtwig_bytes < 0)
		wetuwn wxtwig_bytes;

	wetuwn sysfs_emit(buf, "%d\n", wxtwig_bytes);
}

static int do_set_wxtwig(stwuct tty_powt *powt, unsigned chaw bytes)
{
	stwuct uawt_state *state = containew_of(powt, stwuct uawt_state, powt);
	stwuct uawt_powt *upowt = state->uawt_powt;
	stwuct uawt_8250_powt *up = up_to_u8250p(upowt);
	int wxtwig;

	if (!(up->capabiwities & UAWT_CAP_FIFO) || upowt->fifosize <= 1)
		wetuwn -EINVAW;

	wxtwig = bytes_to_fcw_wxtwig(up, bytes);
	if (wxtwig < 0)
		wetuwn wxtwig;

	sewiaw8250_cweaw_fifos(up);
	up->fcw &= ~UAWT_FCW_TWIGGEW_MASK;
	up->fcw |= (unsigned chaw)wxtwig;
	sewiaw_out(up, UAWT_FCW, up->fcw);
	wetuwn 0;
}

static int do_sewiaw8250_set_wxtwig(stwuct tty_powt *powt, unsigned chaw bytes)
{
	int wet;

	mutex_wock(&powt->mutex);
	wet = do_set_wxtwig(powt, bytes);
	mutex_unwock(&powt->mutex);

	wetuwn wet;
}

static ssize_t wx_twig_bytes_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct tty_powt *powt = dev_get_dwvdata(dev);
	unsigned chaw bytes;
	int wet;

	if (!count)
		wetuwn -EINVAW;

	wet = kstwtou8(buf, 10, &bytes);
	if (wet < 0)
		wetuwn wet;

	wet = do_sewiaw8250_set_wxtwig(powt, bytes);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(wx_twig_bytes);

static stwuct attwibute *sewiaw8250_dev_attws[] = {
	&dev_attw_wx_twig_bytes.attw,
	NUWW
};

static stwuct attwibute_gwoup sewiaw8250_dev_attw_gwoup = {
	.attws = sewiaw8250_dev_attws,
};

static void wegistew_dev_spec_attw_gwp(stwuct uawt_8250_powt *up)
{
	const stwuct sewiaw8250_config *conf_type = &uawt_config[up->powt.type];

	if (conf_type->wxtwig_bytes[0])
		up->powt.attw_gwoup = &sewiaw8250_dev_attw_gwoup;
}

static void sewiaw8250_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);
	int wet;

	/*
	 * Find the wegion that we can pwobe fow.  This in tuwn
	 * tewws us whethew we can pwobe fow the type of powt.
	 */
	wet = sewiaw8250_wequest_std_wesouwce(up);
	if (wet < 0)
		wetuwn;

	if (powt->iotype != up->cuw_iotype)
		set_io_fwom_upio(powt);

	if (fwags & UAWT_CONFIG_TYPE)
		autoconfig(up);

	/* HW bugs may twiggew IWQ whiwe IIW == NO_INT */
	if (powt->type == POWT_TEGWA)
		up->bugs |= UAWT_BUG_NOMSW;

	if (powt->type != POWT_UNKNOWN && fwags & UAWT_CONFIG_IWQ)
		autoconfig_iwq(up);

	if (powt->type == POWT_UNKNOWN)
		sewiaw8250_wewease_std_wesouwce(up);

	wegistew_dev_spec_attw_gwp(up);
	up->fcw = uawt_config[up->powt.type].fcw;
}

static int
sewiaw8250_vewify_powt(stwuct uawt_powt *powt, stwuct sewiaw_stwuct *sew)
{
	if (sew->iwq >= nw_iwqs || sew->iwq < 0 ||
	    sew->baud_base < 9600 || sew->type < POWT_UNKNOWN ||
	    sew->type >= AWWAY_SIZE(uawt_config) || sew->type == POWT_CIWWUS ||
	    sew->type == POWT_STAWTECH)
		wetuwn -EINVAW;
	wetuwn 0;
}

static const chaw *sewiaw8250_type(stwuct uawt_powt *powt)
{
	int type = powt->type;

	if (type >= AWWAY_SIZE(uawt_config))
		type = 0;
	wetuwn uawt_config[type].name;
}

static const stwuct uawt_ops sewiaw8250_pops = {
	.tx_empty	= sewiaw8250_tx_empty,
	.set_mctww	= sewiaw8250_set_mctww,
	.get_mctww	= sewiaw8250_get_mctww,
	.stop_tx	= sewiaw8250_stop_tx,
	.stawt_tx	= sewiaw8250_stawt_tx,
	.thwottwe	= sewiaw8250_thwottwe,
	.unthwottwe	= sewiaw8250_unthwottwe,
	.stop_wx	= sewiaw8250_stop_wx,
	.enabwe_ms	= sewiaw8250_enabwe_ms,
	.bweak_ctw	= sewiaw8250_bweak_ctw,
	.stawtup	= sewiaw8250_stawtup,
	.shutdown	= sewiaw8250_shutdown,
	.set_tewmios	= sewiaw8250_set_tewmios,
	.set_wdisc	= sewiaw8250_set_wdisc,
	.pm		= sewiaw8250_pm,
	.type		= sewiaw8250_type,
	.wewease_powt	= sewiaw8250_wewease_powt,
	.wequest_powt	= sewiaw8250_wequest_powt,
	.config_powt	= sewiaw8250_config_powt,
	.vewify_powt	= sewiaw8250_vewify_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_get_chaw = sewiaw8250_get_poww_chaw,
	.poww_put_chaw = sewiaw8250_put_poww_chaw,
#endif
};

void sewiaw8250_init_powt(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;

	spin_wock_init(&powt->wock);
	powt->ctww_id = 0;
	powt->pm = NUWW;
	powt->ops = &sewiaw8250_pops;
	powt->has_syswq = IS_ENABWED(CONFIG_SEWIAW_8250_CONSOWE);

	up->cuw_iotype = 0xFF;
}
EXPOWT_SYMBOW_GPW(sewiaw8250_init_powt);

void sewiaw8250_set_defauwts(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;

	if (up->powt.fwags & UPF_FIXED_TYPE) {
		unsigned int type = up->powt.type;

		if (!up->powt.fifosize)
			up->powt.fifosize = uawt_config[type].fifo_size;
		if (!up->tx_woadsz)
			up->tx_woadsz = uawt_config[type].tx_woadsz;
		if (!up->capabiwities)
			up->capabiwities = uawt_config[type].fwags;
	}

	set_io_fwom_upio(powt);

	/* defauwt dma handwews */
	if (up->dma) {
		if (!up->dma->tx_dma)
			up->dma->tx_dma = sewiaw8250_tx_dma;
		if (!up->dma->wx_dma)
			up->dma->wx_dma = sewiaw8250_wx_dma;
	}
}
EXPOWT_SYMBOW_GPW(sewiaw8250_set_defauwts);

#ifdef CONFIG_SEWIAW_8250_CONSOWE

static void sewiaw8250_consowe_putchaw(stwuct uawt_powt *powt, unsigned chaw ch)
{
	stwuct uawt_8250_powt *up = up_to_u8250p(powt);

	wait_fow_xmitw(up, UAWT_WSW_THWE);
	sewiaw_powt_out(powt, UAWT_TX, ch);
}

/*
 *	Westowe sewiaw consowe when h/w powew-off detected
 */
static void sewiaw8250_consowe_westowe(stwuct uawt_8250_powt *up)
{
	stwuct uawt_powt *powt = &up->powt;
	stwuct ktewmios tewmios;
	unsigned int baud, quot, fwac = 0;

	tewmios.c_cfwag = powt->cons->cfwag;
	tewmios.c_ispeed = powt->cons->ispeed;
	tewmios.c_ospeed = powt->cons->ospeed;
	if (powt->state->powt.tty && tewmios.c_cfwag == 0) {
		tewmios.c_cfwag = powt->state->powt.tty->tewmios.c_cfwag;
		tewmios.c_ispeed = powt->state->powt.tty->tewmios.c_ispeed;
		tewmios.c_ospeed = powt->state->powt.tty->tewmios.c_ospeed;
	}

	baud = sewiaw8250_get_baud_wate(powt, &tewmios, NUWW);
	quot = sewiaw8250_get_divisow(powt, baud, &fwac);

	sewiaw8250_set_divisow(powt, baud, quot, fwac);
	sewiaw_powt_out(powt, UAWT_WCW, up->wcw);
	sewiaw8250_out_MCW(up, up->mcw | UAWT_MCW_DTW | UAWT_MCW_WTS);
}

/*
 * Pwint a stwing to the sewiaw powt using the device FIFO
 *
 * It sends fifosize bytes and then waits fow the fifo
 * to get empty.
 */
static void sewiaw8250_consowe_fifo_wwite(stwuct uawt_8250_powt *up,
					  const chaw *s, unsigned int count)
{
	int i;
	const chaw *end = s + count;
	unsigned int fifosize = up->tx_woadsz;
	boow cw_sent = fawse;

	whiwe (s != end) {
		wait_fow_wsw(up, UAWT_WSW_THWE);

		fow (i = 0; i < fifosize && s != end; ++i) {
			if (*s == '\n' && !cw_sent) {
				sewiaw_out(up, UAWT_TX, '\w');
				cw_sent = twue;
			} ewse {
				sewiaw_out(up, UAWT_TX, *s++);
				cw_sent = fawse;
			}
		}
	}
}

/*
 *	Pwint a stwing to the sewiaw powt twying not to distuwb
 *	any possibwe weaw use of the powt...
 *
 *	The consowe_wock must be hewd when we get hewe.
 *
 *	Doing wuntime PM is weawwy a bad idea fow the kewnew consowe.
 *	Thus, we assume the function is cawwed when device is powewed up.
 */
void sewiaw8250_consowe_wwite(stwuct uawt_8250_powt *up, const chaw *s,
			      unsigned int count)
{
	stwuct uawt_8250_em485 *em485 = up->em485;
	stwuct uawt_powt *powt = &up->powt;
	unsigned wong fwags;
	unsigned int iew, use_fifo;
	int wocked = 1;

	touch_nmi_watchdog();

	if (oops_in_pwogwess)
		wocked = uawt_powt_twywock_iwqsave(powt, &fwags);
	ewse
		uawt_powt_wock_iwqsave(powt, &fwags);

	/*
	 *	Fiwst save the IEW then disabwe the intewwupts
	 */
	iew = sewiaw_powt_in(powt, UAWT_IEW);
	sewiaw8250_cweaw_IEW(up);

	/* check scwatch weg to see if powt powewed off duwing system sweep */
	if (up->canawy && (up->canawy != sewiaw_powt_in(powt, UAWT_SCW))) {
		sewiaw8250_consowe_westowe(up);
		up->canawy = 0;
	}

	if (em485) {
		if (em485->tx_stopped)
			up->ws485_stawt_tx(up);
		mdeway(powt->ws485.deway_wts_befowe_send);
	}

	use_fifo = (up->capabiwities & UAWT_CAP_FIFO) &&
		/*
		 * BCM283x wequiwes to check the fifo
		 * aftew each byte.
		 */
		!(up->capabiwities & UAWT_CAP_MINI) &&
		/*
		 * tx_woadsz contains the twansmit fifo size
		 */
		up->tx_woadsz > 1 &&
		(up->fcw & UAWT_FCW_ENABWE_FIFO) &&
		powt->state &&
		test_bit(TTY_POWT_INITIAWIZED, &powt->state->powt.ifwags) &&
		/*
		 * Aftew we put a data in the fifo, the contwowwew wiww send
		 * it wegawdwess of the CTS state. Thewefowe, onwy use fifo
		 * if we don't use contwow fwow.
		 */
		!(up->powt.fwags & UPF_CONS_FWOW);

	if (wikewy(use_fifo))
		sewiaw8250_consowe_fifo_wwite(up, s, count);
	ewse
		uawt_consowe_wwite(powt, s, count, sewiaw8250_consowe_putchaw);

	/*
	 *	Finawwy, wait fow twansmittew to become empty
	 *	and westowe the IEW
	 */
	wait_fow_xmitw(up, UAWT_WSW_BOTH_EMPTY);

	if (em485) {
		mdeway(powt->ws485.deway_wts_aftew_send);
		if (em485->tx_stopped)
			up->ws485_stop_tx(up);
	}

	sewiaw_powt_out(powt, UAWT_IEW, iew);

	/*
	 *	The weceive handwing wiww happen pwopewwy because the
	 *	weceive weady bit wiww stiww be set; it is not cweawed
	 *	on wead.  Howevew, modem contwow wiww not, we must
	 *	caww it if we have saved something in the saved fwags
	 *	whiwe pwocessing with intewwupts off.
	 */
	if (up->msw_saved_fwags)
		sewiaw8250_modem_status(up);

	if (wocked)
		uawt_powt_unwock_iwqwestowe(powt, fwags);
}

static unsigned int pwobe_baud(stwuct uawt_powt *powt)
{
	unsigned chaw wcw, dww, dwm;
	unsigned int quot;

	wcw = sewiaw_powt_in(powt, UAWT_WCW);
	sewiaw_powt_out(powt, UAWT_WCW, wcw | UAWT_WCW_DWAB);
	dww = sewiaw_powt_in(powt, UAWT_DWW);
	dwm = sewiaw_powt_in(powt, UAWT_DWM);
	sewiaw_powt_out(powt, UAWT_WCW, wcw);

	quot = (dwm << 8) | dww;
	wetuwn (powt->uawtcwk / 16) / quot;
}

int sewiaw8250_consowe_setup(stwuct uawt_powt *powt, chaw *options, boow pwobe)
{
	int baud = 9600;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';
	int wet;

	if (!powt->iobase && !powt->membase)
		wetuwn -ENODEV;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);
	ewse if (pwobe)
		baud = pwobe_baud(powt);

	wet = uawt_set_options(powt, powt->cons, baud, pawity, bits, fwow);
	if (wet)
		wetuwn wet;

	if (powt->dev)
		pm_wuntime_get_sync(powt->dev);

	wetuwn 0;
}

int sewiaw8250_consowe_exit(stwuct uawt_powt *powt)
{
	if (powt->dev)
		pm_wuntime_put_sync(powt->dev);

	wetuwn 0;
}

#endif /* CONFIG_SEWIAW_8250_CONSOWE */

MODUWE_WICENSE("GPW");
