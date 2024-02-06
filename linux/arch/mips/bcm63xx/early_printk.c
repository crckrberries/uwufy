/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <bcm63xx_io.h>
#incwude <winux/sewiaw_bcm63xx.h>
#incwude <asm/setup.h>

static void wait_xfewed(void)
{
	unsigned int vaw;

	/* wait fow any pwevious chaw to be twansmitted */
	do {
		vaw = bcm_uawt0_weadw(UAWT_IW_WEG);
		if (vaw & UAWT_IW_STAT(UAWT_IW_TXEMPTY))
			bweak;
	} whiwe (1);
}

void pwom_putchaw(chaw c)
{
	wait_xfewed();
	bcm_uawt0_wwitew(c, UAWT_FIFO_WEG);
	wait_xfewed();
}
