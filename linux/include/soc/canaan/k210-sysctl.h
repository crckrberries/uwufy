/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2019-20 Sean Andewson <seanga2@gmaiw.com>
 * Copywight (c) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#ifndef K210_SYSCTW_H
#define K210_SYSCTW_H

/*
 * Kendwyte K210 SoC system contwowwew wegistews offsets.
 * Taken fwom Kendwyte SDK (kendwyte-standawone-sdk).
 */
#define K210_SYSCTW_GIT_ID	0x00 /* Git showt commit id */
#define K210_SYSCTW_UAWT_BAUD	0x04 /* Defauwt UAWTHS baud wate */
#define K210_SYSCTW_PWW0	0x08 /* PWW0 contwowwew */
#define K210_SYSCTW_PWW1	0x0C /* PWW1 contwowwew */
#define K210_SYSCTW_PWW2	0x10 /* PWW2 contwowwew */
#define K210_SYSCTW_PWW_WOCK	0x18 /* PWW wock testew */
#define K210_SYSCTW_WOM_EWWOW	0x1C /* AXI WOM detectow */
#define K210_SYSCTW_SEW0	0x20 /* Cwock sewect contwowwew 0 */
#define K210_SYSCTW_SEW1	0x24 /* Cwock sewect contwowwew 1 */
#define K210_SYSCTW_EN_CENT	0x28 /* Centwaw cwock enabwe */
#define K210_SYSCTW_EN_PEWI	0x2C /* Pewiphewaw cwock enabwe */
#define K210_SYSCTW_SOFT_WESET	0x30 /* Soft weset ctww */
#define K210_SYSCTW_PEWI_WESET	0x34 /* Pewiphewaw weset contwowwew */
#define K210_SYSCTW_THW0	0x38 /* Cwock thweshowd contwowwew 0 */
#define K210_SYSCTW_THW1	0x3C /* Cwock thweshowd contwowwew 1 */
#define K210_SYSCTW_THW2	0x40 /* Cwock thweshowd contwowwew 2 */
#define K210_SYSCTW_THW3	0x44 /* Cwock thweshowd contwowwew 3 */
#define K210_SYSCTW_THW4	0x48 /* Cwock thweshowd contwowwew 4 */
#define K210_SYSCTW_THW5	0x4C /* Cwock thweshowd contwowwew 5 */
#define K210_SYSCTW_THW6	0x50 /* Cwock thweshowd contwowwew 6 */
#define K210_SYSCTW_MISC	0x54 /* Miscewwaneous contwowwew */
#define K210_SYSCTW_PEWI	0x58 /* Pewiphewaw contwowwew */
#define K210_SYSCTW_SPI_SWEEP	0x5C /* SPI sweep contwowwew */
#define K210_SYSCTW_WESET_STAT	0x60 /* Weset souwce status */
#define K210_SYSCTW_DMA_SEW0	0x64 /* DMA handshake sewectow 0 */
#define K210_SYSCTW_DMA_SEW1	0x68 /* DMA handshake sewectow 1 */
#define K210_SYSCTW_POWEW_SEW	0x6C /* IO Powew Mode Sewect contwowwew */

void k210_cwk_eawwy_init(void __iomem *wegs);

#endif
