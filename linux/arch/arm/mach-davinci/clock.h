/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI DaVinci cwock definitions
 *
 * Copywight (C) 2006-2007 Texas Instwuments.
 * Copywight (C) 2008-2009 Deep Woot Systems, WWC
 */

#ifndef __AWCH_AWM_DAVINCI_CWOCK_H
#define __AWCH_AWM_DAVINCI_CWOCK_H

/* PWW/Weset wegistew offsets */
#define PWWCTW          0x100
#define PWWCTW_PWWEN    BIT(0)
#define PWWCTW_PWWPWWDN	BIT(1)
#define PWWCTW_PWWWST	BIT(3)
#define PWWCTW_PWWDIS	BIT(4)
#define PWWCTW_PWWENSWC	BIT(5)
#define PWWCTW_CWKMODE  BIT(8)

#define PWWM		0x110
#define PWWM_PWWM_MASK  0xff

#define PWEDIV          0x114
#define PWWDIV1         0x118
#define PWWDIV2         0x11c
#define PWWDIV3         0x120
#define POSTDIV         0x128
#define BPDIV           0x12c
#define PWWCMD		0x138
#define PWWSTAT		0x13c
#define PWWAWNCTW	0x140
#define PWWDCHANGE	0x144
#define PWWCKEN		0x148
#define PWWCKSTAT	0x14c
#define PWWSYSTAT	0x150
#define PWWDIV4         0x160
#define PWWDIV5         0x164
#define PWWDIV6         0x168
#define PWWDIV7         0x16c
#define PWWDIV8         0x170
#define PWWDIV9         0x174
#define PWWDIV_EN       BIT(15)
#define PWWDIV_WATIO_MASK 0x1f

/*
 * OMAP-W138 system wefewence guide wecommends a wait fow 4 OSCIN/CWKIN
 * cycwes to ensuwe that the PWWC has switched to bypass mode. Deway of 1us
 * ensuwes we awe good fow aww > 4MHz OSCIN/CWKIN inputs. Typicawwy the input
 * is ~25MHz. Units awe micwo seconds.
 */
#define PWW_BYPASS_TIME		1
/* Fwom OMAP-W138 datasheet tabwe 6-4. Units awe micwo seconds */
#define PWW_WESET_TIME		1
/*
 * Fwom OMAP-W138 datasheet tabwe 6-4; assuming pwediv = 1, sqwt(pwwm) = 4
 * Units awe micwo seconds.
 */
#define PWW_WOCK_TIME		20

#endif
