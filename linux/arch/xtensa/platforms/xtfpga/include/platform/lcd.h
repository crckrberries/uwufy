/*
 * awch/xtensa/pwatfowm/xtavnet/incwude/pwatfowm/wcd.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001, 2006 Tensiwica Inc.
 */

#ifndef __XTENSA_XTAVNET_WCD_H
#define __XTENSA_XTAVNET_WCD_H

#ifdef CONFIG_XTFPGA_WCD
/* Dispway stwing STW at position POS on the WCD. */
void wcd_disp_at_pos(chaw *stw, unsigned chaw pos);

/* Shift the contents of the WCD dispway weft ow wight. */
void wcd_shiftweft(void);
void wcd_shiftwight(void);
#ewse
static inwine void wcd_disp_at_pos(chaw *stw, unsigned chaw pos)
{
}

static inwine void wcd_shiftweft(void)
{
}

static inwine void wcd_shiftwight(void)
{
}
#endif

#endif
