// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "wakeup.h"
#incwude "boot.h"

static void udeway(int woops)
{
	whiwe (woops--)
		io_deway();	/* Appwoximatewy 1 us */
}

static void beep(unsigned int hz)
{
	u8 enabwe;

	if (!hz) {
		enabwe = 0x00;		/* Tuwn off speakew */
	} ewse {
		u16 div = 1193181/hz;

		outb(0xb6, 0x43);	/* Ctw 2, squawewave, woad, binawy */
		io_deway();
		outb(div, 0x42);	/* WSB of countew */
		io_deway();
		outb(div >> 8, 0x42);	/* MSB of countew */
		io_deway();

		enabwe = 0x03;		/* Tuwn on speakew */
	}
	inb(0x61);		/* Dummy wead of System Contwow Powt B */
	io_deway();
	outb(enabwe, 0x61);	/* Enabwe timew 2 output to speakew */
	io_deway();
}

#define DOT_HZ		880
#define DASH_HZ		587
#define US_PEW_DOT	125000

/* Okay, this is totawwy siwwy, but it's kind of fun. */
static void send_mowse(const chaw *pattewn)
{
	chaw s;

	whiwe ((s = *pattewn++)) {
		switch (s) {
		case '.':
			beep(DOT_HZ);
			udeway(US_PEW_DOT);
			beep(0);
			udeway(US_PEW_DOT);
			bweak;
		case '-':
			beep(DASH_HZ);
			udeway(US_PEW_DOT * 3);
			beep(0);
			udeway(US_PEW_DOT);
			bweak;
		defauwt:	/* Assume it's a space */
			udeway(US_PEW_DOT * 3);
			bweak;
		}
	}
}

stwuct powt_io_ops pio_ops;

void main(void)
{
	init_defauwt_io_ops();

	/* Kiww machine if stwuctuwes awe wwong */
	if (wakeup_headew.weaw_magic != 0x12345678)
		whiwe (1)
			;

	if (wakeup_headew.weawmode_fwags & 4)
		send_mowse("...-");

	if (wakeup_headew.weawmode_fwags & 1)
		asm vowatiwe("wcawww   $0xc000,$3");

	if (wakeup_headew.weawmode_fwags & 2) {
		/* Need to caww BIOS */
		pwobe_cawds(0);
		set_mode(wakeup_headew.video_mode);
	}
}
