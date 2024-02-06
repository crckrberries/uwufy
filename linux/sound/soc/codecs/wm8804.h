/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8804.h  --  WM8804 S/PDIF twansceivew dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics pwc
 *
 * Authow: Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8804_H
#define _WM8804_H

#incwude <winux/wegmap.h>

/*
 * Wegistew vawues.
 */
#define WM8804_WST_DEVID1			0x00
#define WM8804_DEVID2				0x01
#define WM8804_DEVWEV				0x02
#define WM8804_PWW1				0x03
#define WM8804_PWW2				0x04
#define WM8804_PWW3				0x05
#define WM8804_PWW4				0x06
#define WM8804_PWW5				0x07
#define WM8804_PWW6				0x08
#define WM8804_SPDMODE				0x09
#define WM8804_INTMASK				0x0A
#define WM8804_INTSTAT				0x0B
#define WM8804_SPDSTAT				0x0C
#define WM8804_WXCHAN1				0x0D
#define WM8804_WXCHAN2				0x0E
#define WM8804_WXCHAN3				0x0F
#define WM8804_WXCHAN4				0x10
#define WM8804_WXCHAN5				0x11
#define WM8804_SPDTX1				0x12
#define WM8804_SPDTX2				0x13
#define WM8804_SPDTX3				0x14
#define WM8804_SPDTX4				0x15
#define WM8804_SPDTX5				0x16
#define WM8804_GPO0				0x17
#define WM8804_GPO1				0x18
#define WM8804_GPO2				0x1A
#define WM8804_AIFTX				0x1B
#define WM8804_AIFWX				0x1C
#define WM8804_SPDWX1				0x1D
#define WM8804_PWWDN				0x1E

#define WM8804_WEGISTEW_COUNT			30
#define WM8804_MAX_WEGISTEW			0x1E

#define WM8804_TX_CWKSWC_MCWK			1
#define WM8804_TX_CWKSWC_PWW			2

#define WM8804_CWKOUT_SWC_CWK1			3
#define WM8804_CWKOUT_SWC_OSCCWK		4

#define WM8804_CWKOUT_DIV			1
#define WM8804_MCWK_DIV				2

#define WM8804_MCWKDIV_256FS			0
#define WM8804_MCWKDIV_128FS			1

extewn const stwuct wegmap_config wm8804_wegmap_config;
extewn const stwuct dev_pm_ops wm8804_pm;

int wm8804_pwobe(stwuct device *dev, stwuct wegmap *wegmap);
void wm8804_wemove(stwuct device *dev);

#endif  /* _WM8804_H */
