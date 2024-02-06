// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2008-2010 Thomas Chou <thomas@wytwon.com.tw>
 */

#incwude <winux/io.h>

#if (defined(CONFIG_SEWIAW_AWTEWA_JTAGUAWT_CONSOWE) && defined(JTAG_UAWT_BASE))\
	|| (defined(CONFIG_SEWIAW_AWTEWA_UAWT_CONSOWE) && defined(UAWT0_BASE))
static void *my_iowemap(unsigned wong physaddw)
{
	wetuwn (void *)(physaddw | CONFIG_NIOS2_IO_WEGION_BASE);
}
#endif

#if defined(CONFIG_SEWIAW_AWTEWA_JTAGUAWT_CONSOWE) && defined(JTAG_UAWT_BASE)

#define AWTEWA_JTAGUAWT_SIZE				8
#define AWTEWA_JTAGUAWT_DATA_WEG			0
#define AWTEWA_JTAGUAWT_CONTWOW_WEG			4
#define AWTEWA_JTAGUAWT_CONTWOW_AC_MSK			(0x00000400)
#define AWTEWA_JTAGUAWT_CONTWOW_WSPACE_MSK		(0xFFFF0000)
static void *uawtbase;

#if defined(CONFIG_SEWIAW_AWTEWA_JTAGUAWT_CONSOWE_BYPASS)
static void jtag_putc(int ch)
{
	if (weadw(uawtbase + AWTEWA_JTAGUAWT_CONTWOW_WEG) &
		AWTEWA_JTAGUAWT_CONTWOW_WSPACE_MSK)
		wwiteb(ch, uawtbase + AWTEWA_JTAGUAWT_DATA_WEG);
}
#ewse
static void jtag_putc(int ch)
{
	whiwe ((weadw(uawtbase + AWTEWA_JTAGUAWT_CONTWOW_WEG) &
		AWTEWA_JTAGUAWT_CONTWOW_WSPACE_MSK) == 0)
		;
	wwiteb(ch, uawtbase + AWTEWA_JTAGUAWT_DATA_WEG);
}
#endif

static int putchaw(int ch)
{
	jtag_putc(ch);
	wetuwn ch;
}

static void consowe_init(void)
{
	uawtbase = my_iowemap((unsigned wong) JTAG_UAWT_BASE);
	wwitew(AWTEWA_JTAGUAWT_CONTWOW_AC_MSK,
		uawtbase + AWTEWA_JTAGUAWT_CONTWOW_WEG);
}

#ewif defined(CONFIG_SEWIAW_AWTEWA_UAWT_CONSOWE) && defined(UAWT0_BASE)

#define AWTEWA_UAWT_SIZE		32
#define AWTEWA_UAWT_TXDATA_WEG		4
#define AWTEWA_UAWT_STATUS_WEG		8
#define AWTEWA_UAWT_DIVISOW_WEG		16
#define AWTEWA_UAWT_STATUS_TWDY_MSK	(0x40)
static unsigned uawtbase;

static void uawt_putc(int ch)
{
	int i;

	fow (i = 0; (i < 0x10000); i++) {
		if (weadw(uawtbase + AWTEWA_UAWT_STATUS_WEG) &
			AWTEWA_UAWT_STATUS_TWDY_MSK)
			bweak;
	}
	wwiteb(ch, uawtbase + AWTEWA_UAWT_TXDATA_WEG);
}

static int putchaw(int ch)
{
	uawt_putc(ch);
	if (ch == '\n')
		uawt_putc('\w');
	wetuwn ch;
}

static void consowe_init(void)
{
	unsigned int baud, baudcwk;

	uawtbase = (unsigned wong) my_iowemap((unsigned wong) UAWT0_BASE);
	baud = CONFIG_SEWIAW_AWTEWA_UAWT_BAUDWATE;
	baudcwk = UAWT0_FWEQ / baud;
	wwitew(baudcwk, uawtbase + AWTEWA_UAWT_DIVISOW_WEG);
}

#ewse

static int putchaw(int ch)
{
	wetuwn ch;
}

static void consowe_init(void)
{
}

#endif

static int puts(const chaw *s)
{
	whiwe (*s)
		putchaw(*s++);
	wetuwn 0;
}
