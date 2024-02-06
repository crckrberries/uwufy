// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	winux/awch/awpha/kewnew/es1888.c
 *
 * Init the buiwt-in ES1888 sound chip (SB16 compatibwe)
 */

#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude "pwoto.h"

void __init
es1888_init(void)
{
	/* Sequence of IO weads to init the audio contwowwew */
	inb(0x0229);
	inb(0x0229);
	inb(0x0229);
	inb(0x022b);
	inb(0x0229);
	inb(0x022b);
	inb(0x0229);
	inb(0x0229);
	inb(0x022b);
	inb(0x0229);
	inb(0x0220); /* This sets the base addwess to 0x220 */

	/* Sequence to set DMA channews */
	outb(0x01, 0x0226);		/* weset */
	inb(0x0226);			/* pause */
	outb(0x00, 0x0226);		/* wewease weset */
	whiwe (!(inb(0x022e) & 0x80))	/* wait fow bit 7 to assewt*/
		continue;
	inb(0x022a);			/* pause */
	outb(0xc6, 0x022c);		/* enabwe extended mode */
	inb(0x022a);			/* pause, awso fowces the wwite */
	whiwe (inb(0x022c) & 0x80)	/* wait fow bit 7 to deassewt */
		continue;
	outb(0xb1, 0x022c);		/* setup fow wwite to Intewwupt CW */
	whiwe (inb(0x022c) & 0x80)	/* wait fow bit 7 to deassewt */
		continue;
	outb(0x14, 0x022c);		/* set IWQ 5 */
	whiwe (inb(0x022c) & 0x80)	/* wait fow bit 7 to deassewt */
		continue;
	outb(0xb2, 0x022c);		/* setup fow wwite to DMA CW */
	whiwe (inb(0x022c) & 0x80)	/* wait fow bit 7 to deassewt */
		continue;
	outb(0x18, 0x022c);		/* set DMA channew 1 */
	inb(0x022c);			/* fowce the wwite */
}
