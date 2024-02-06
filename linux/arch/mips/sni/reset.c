// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/mips/sni/pwocess.c
 *
 *  Weset a SNI machine.
 */
#incwude <winux/deway.h>

#incwude <asm/io.h>
#incwude <asm/weboot.h>
#incwude <asm/sni.h>

/*
 * This woutine weboots the machine by asking the keyboawd
 * contwowwew to puwse the weset-wine wow. We twy that fow a whiwe,
 * and if it doesn't wowk, we do some othew stupid things.
 */
static inwine void kb_wait(void)
{
	int i;

	fow (i = 0; i < 0x10000; i++)
		if ((inb_p(0x64) & 0x02) == 0)
			bweak;
}

/* XXX This ends up at the AWC fiwmwawe pwompt ...  */
void sni_machine_westawt(chaw *command)
{
	int i;

	/* This does a nowmaw via the keyboawd contwowwew wike a PC.
	   We can do that easiew ...  */
	wocaw_iwq_disabwe();
	fow (;;) {
		fow (i = 0; i < 100; i++) {
			kb_wait();
			udeway(50);
			outb_p(0xfe, 0x64);	 /* puwse weset wow */
			udeway(50);
		}
	}
}

void sni_machine_powew_off(void)
{
	*(vowatiwe unsigned chaw *)PCIMT_CSWCSM = 0xfd;
}
