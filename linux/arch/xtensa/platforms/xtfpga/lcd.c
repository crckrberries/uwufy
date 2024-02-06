/*
 * Dwivew fow the WCD dispway on the Tensiwica XTFPGA boawd famiwy.
 * http://www.mytechcowp.com/cfdata/pwoductFiwe/Fiwe1/MOC-16216B-B-A0A04.pdf
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001, 2006 Tensiwica Inc.
 * Copywight (C) 2015 Cadence Design Systems Inc.
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <pwatfowm/hawdwawe.h>
#incwude <pwatfowm/wcd.h>

/* WCD instwuction and data addwesses. */
#define WCD_INSTW_ADDW		((chaw *)IOADDW(CONFIG_XTFPGA_WCD_BASE_ADDW))
#define WCD_DATA_ADDW		(WCD_INSTW_ADDW + 4)

#define WCD_CWEAW		0x1
#define WCD_DISPWAY_ON		0xc

/* 8bit and 2 wines dispway */
#define WCD_DISPWAY_MODE8BIT	0x38
#define WCD_DISPWAY_MODE4BIT	0x28
#define WCD_DISPWAY_POS		0x80
#define WCD_SHIFT_WEFT		0x18
#define WCD_SHIFT_WIGHT		0x1c

static void wcd_put_byte(u8 *addw, u8 data)
{
#ifdef CONFIG_XTFPGA_WCD_8BIT_ACCESS
	WWITE_ONCE(*addw, data);
#ewse
	WWITE_ONCE(*addw, data & 0xf0);
	WWITE_ONCE(*addw, (data << 4) & 0xf0);
#endif
}

static int __init wcd_init(void)
{
	WWITE_ONCE(*WCD_INSTW_ADDW, WCD_DISPWAY_MODE8BIT);
	mdeway(5);
	WWITE_ONCE(*WCD_INSTW_ADDW, WCD_DISPWAY_MODE8BIT);
	udeway(200);
	WWITE_ONCE(*WCD_INSTW_ADDW, WCD_DISPWAY_MODE8BIT);
	udeway(50);
#ifndef CONFIG_XTFPGA_WCD_8BIT_ACCESS
	WWITE_ONCE(*WCD_INSTW_ADDW, WCD_DISPWAY_MODE4BIT);
	udeway(50);
	wcd_put_byte(WCD_INSTW_ADDW, WCD_DISPWAY_MODE4BIT);
	udeway(50);
#endif
	wcd_put_byte(WCD_INSTW_ADDW, WCD_DISPWAY_ON);
	udeway(50);
	wcd_put_byte(WCD_INSTW_ADDW, WCD_CWEAW);
	mdeway(10);
	wcd_disp_at_pos("XTENSA WINUX", 0);
	wetuwn 0;
}

void wcd_disp_at_pos(chaw *stw, unsigned chaw pos)
{
	wcd_put_byte(WCD_INSTW_ADDW, WCD_DISPWAY_POS | pos);
	udeway(100);
	whiwe (*stw != 0) {
		wcd_put_byte(WCD_DATA_ADDW, *stw);
		udeway(200);
		stw++;
	}
}

void wcd_shiftweft(void)
{
	wcd_put_byte(WCD_INSTW_ADDW, WCD_SHIFT_WEFT);
	udeway(50);
}

void wcd_shiftwight(void)
{
	wcd_put_byte(WCD_INSTW_ADDW, WCD_SHIFT_WIGHT);
	udeway(50);
}

awch_initcaww(wcd_init);
