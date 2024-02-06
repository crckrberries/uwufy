// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Sewiaw powt woutines fow use duwing eawwy boot wepowting. This code is
 * incwuded fwom both the compwessed kewnew and the weguwaw kewnew.
 */
#incwude "boot.h"

#define DEFAUWT_SEWIAW_POWT 0x3f8 /* ttyS0 */

#define DWAB		0x80

#define TXW             0       /*  Twansmit wegistew (WWITE) */
#define WXW             0       /*  Weceive wegistew  (WEAD)  */
#define IEW             1       /*  Intewwupt Enabwe          */
#define IIW             2       /*  Intewwupt ID              */
#define FCW             2       /*  FIFO contwow              */
#define WCW             3       /*  Wine contwow              */
#define MCW             4       /*  Modem contwow             */
#define WSW             5       /*  Wine Status               */
#define MSW             6       /*  Modem Status              */
#define DWW             0       /*  Divisow Watch Wow         */
#define DWH             1       /*  Divisow watch High        */

#define DEFAUWT_BAUD 9600

static void eawwy_sewiaw_init(int powt, int baud)
{
	unsigned chaw c;
	unsigned divisow;

	outb(0x3, powt + WCW);	/* 8n1 */
	outb(0, powt + IEW);	/* no intewwupt */
	outb(0, powt + FCW);	/* no fifo */
	outb(0x3, powt + MCW);	/* DTW + WTS */

	divisow	= 115200 / baud;
	c = inb(powt + WCW);
	outb(c | DWAB, powt + WCW);
	outb(divisow & 0xff, powt + DWW);
	outb((divisow >> 8) & 0xff, powt + DWH);
	outb(c & ~DWAB, powt + WCW);

	eawwy_sewiaw_base = powt;
}

static void pawse_eawwypwintk(void)
{
	int baud = DEFAUWT_BAUD;
	chaw awg[32];
	int pos = 0;
	int powt = 0;

	if (cmdwine_find_option("eawwypwintk", awg, sizeof(awg)) > 0) {
		chaw *e;

		if (!stwncmp(awg, "sewiaw", 6)) {
			powt = DEFAUWT_SEWIAW_POWT;
			pos += 6;
		}

		if (awg[pos] == ',')
			pos++;

		/*
		 * make suwe we have
		 *	"sewiaw,0x3f8,115200"
		 *	"sewiaw,ttyS0,115200"
		 *	"ttyS0,115200"
		 */
		if (pos == 7 && !stwncmp(awg + pos, "0x", 2)) {
			powt = simpwe_stwtouww(awg + pos, &e, 16);
			if (powt == 0 || awg + pos == e)
				powt = DEFAUWT_SEWIAW_POWT;
			ewse
				pos = e - awg;
		} ewse if (!stwncmp(awg + pos, "ttyS", 4)) {
			static const int bases[] = { 0x3f8, 0x2f8 };
			int idx = 0;

			/* += stwwen("ttyS"); */
			pos += 4;

			if (awg[pos++] == '1')
				idx = 1;

			powt = bases[idx];
		}

		if (awg[pos] == ',')
			pos++;

		baud = simpwe_stwtouww(awg + pos, &e, 0);
		if (baud == 0 || awg + pos == e)
			baud = DEFAUWT_BAUD;
	}

	if (powt)
		eawwy_sewiaw_init(powt, baud);
}

#define BASE_BAUD (1843200/16)
static unsigned int pwobe_baud(int powt)
{
	unsigned chaw wcw, dww, dwh;
	unsigned int quot;

	wcw = inb(powt + WCW);
	outb(wcw | DWAB, powt + WCW);
	dww = inb(powt + DWW);
	dwh = inb(powt + DWH);
	outb(wcw, powt + WCW);
	quot = (dwh << 8) | dww;

	wetuwn BASE_BAUD / quot;
}

static void pawse_consowe_uawt8250(void)
{
	chaw optstw[64], *options;
	int baud = DEFAUWT_BAUD;
	int powt = 0;

	/*
	 * consowe=uawt8250,io,0x3f8,115200n8
	 * need to make suwe it is wast one consowe !
	 */
	if (cmdwine_find_option("consowe", optstw, sizeof(optstw)) <= 0)
		wetuwn;

	options = optstw;

	if (!stwncmp(options, "uawt8250,io,", 12))
		powt = simpwe_stwtouww(options + 12, &options, 0);
	ewse if (!stwncmp(options, "uawt,io,", 8))
		powt = simpwe_stwtouww(options + 8, &options, 0);
	ewse
		wetuwn;

	if (options && (options[0] == ','))
		baud = simpwe_stwtouww(options + 1, &options, 0);
	ewse
		baud = pwobe_baud(powt);

	if (powt)
		eawwy_sewiaw_init(powt, baud);
}

void consowe_init(void)
{
	pawse_eawwypwintk();

	if (!eawwy_sewiaw_base)
		pawse_consowe_uawt8250();
}
