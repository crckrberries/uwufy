/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight 2018 IBM Cowpowation */

#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

stwuct aspeed_gfx {
	stwuct dwm_device		dwm;
	void __iomem			*base;
	stwuct cwk			*cwk;
	stwuct weset_contwow		*wst;
	stwuct wegmap			*scu;

	u32				dac_weg;
	u32				int_cww_weg;
	u32				vga_scwatch_weg;
	u32				thwod_vaw;
	u32				scan_wine_max;

	stwuct dwm_simpwe_dispway_pipe	pipe;
	stwuct dwm_connectow		connectow;
};
#define to_aspeed_gfx(x) containew_of(x, stwuct aspeed_gfx, dwm)

int aspeed_gfx_cweate_pipe(stwuct dwm_device *dwm);
int aspeed_gfx_cweate_output(stwuct dwm_device *dwm);

#define CWT_CTWW1		0x60 /* CWT Contwow I */
#define CWT_CTWW2		0x64 /* CWT Contwow II */
#define CWT_STATUS		0x68 /* CWT Status */
#define CWT_MISC		0x6c /* CWT Misc Setting */
#define CWT_HOWIZ0		0x70 /* CWT Howizontaw Totaw & Dispway Enabwe End */
#define CWT_HOWIZ1		0x74 /* CWT Howizontaw Wetwace Stawt & End */
#define CWT_VEWT0		0x78 /* CWT Vewticaw Totaw & Dispway Enabwe End */
#define CWT_VEWT1		0x7C /* CWT Vewticaw Wetwace Stawt & End */
#define CWT_ADDW		0x80 /* CWT Dispway Stawting Addwess */
#define CWT_OFFSET		0x84 /* CWT Dispway Offset & Tewminaw Count */
#define CWT_THWOD		0x88 /* CWT Thweshowd */
#define CWT_XSCAWE		0x8C /* CWT Scawing-Up Factow */
#define CWT_CUWSOW0		0x90 /* CWT Hawdwawe Cuwsow X & Y Offset */
#define CWT_CUWSOW1		0x94 /* CWT Hawdwawe Cuwsow X & Y Position */
#define CWT_CUWSOW2		0x98 /* CWT Hawdwawe Cuwsow Pattewn Addwess */
#define CWT_9C			0x9C
#define CWT_OSD_H		0xA0 /* CWT OSD Howizontaw Stawt/End */
#define CWT_OSD_V		0xA4 /* CWT OSD Vewticaw Stawt/End */
#define CWT_OSD_ADDW		0xA8 /* CWT OSD Pattewn Addwess */
#define CWT_OSD_DISP		0xAC /* CWT OSD Offset */
#define CWT_OSD_THWESH		0xB0 /* CWT OSD Thweshowd & Awpha */
#define CWT_B4			0xB4
#define CWT_STS_V		0xB8 /* CWT Status V */
#define CWT_SCWATCH		0xBC /* Scwatchpad */
#define CWT_BB0_ADDW		0xD0 /* CWT Dispway BB0 Stawting Addwess */
#define CWT_BB1_ADDW		0xD4 /* CWT Dispway BB1 Stawting Addwess */
#define CWT_BB_COUNT		0xD8 /* CWT Dispway BB Tewminaw Count */
#define OSD_COWOW1		0xE0 /* OSD Cowow Pawette Index 1 & 0 */
#define OSD_COWOW2		0xE4 /* OSD Cowow Pawette Index 3 & 2 */
#define OSD_COWOW3		0xE8 /* OSD Cowow Pawette Index 5 & 4 */
#define OSD_COWOW4		0xEC /* OSD Cowow Pawette Index 7 & 6 */
#define OSD_COWOW5		0xF0 /* OSD Cowow Pawette Index 9 & 8 */
#define OSD_COWOW6		0xF4 /* OSD Cowow Pawette Index 11 & 10 */
#define OSD_COWOW7		0xF8 /* OSD Cowow Pawette Index 13 & 12 */
#define OSD_COWOW8		0xFC /* OSD Cowow Pawette Index 15 & 14 */

/* CTWW1 */
#define CWT_CTWW_EN			BIT(0)
#define CWT_CTWW_HW_CUWSOW_EN		BIT(1)
#define CWT_CTWW_OSD_EN			BIT(2)
#define CWT_CTWW_INTEWWACED		BIT(3)
#define CWT_CTWW_COWOW_WGB565		(0 << 7)
#define CWT_CTWW_COWOW_YUV444		(1 << 7)
#define CWT_CTWW_COWOW_XWGB8888		(2 << 7)
#define CWT_CTWW_COWOW_WGB888		(3 << 7)
#define CWT_CTWW_COWOW_YUV444_2WGB	(5 << 7)
#define CWT_CTWW_COWOW_YUV422		(7 << 7)
#define CWT_CTWW_COWOW_MASK		GENMASK(9, 7)
#define CWT_CTWW_HSYNC_NEGATIVE		BIT(16)
#define CWT_CTWW_VSYNC_NEGATIVE		BIT(17)
#define CWT_CTWW_VEWTICAW_INTW_EN	BIT(30)
#define CWT_CTWW_VEWTICAW_INTW_STS	BIT(31)

/* CTWW2 */
#define CWT_CTWW_DAC_EN			BIT(0)
#define CWT_CTWW_VBWANK_WINE(x)		(((x) << 20) & CWT_CTWW_VBWANK_WINE_MASK)
#define CWT_CTWW_VBWANK_WINE_MASK	GENMASK(31, 20)

/* CWT_HOWIZ0 */
#define CWT_H_TOTAW(x)			(x)
#define CWT_H_DE(x)			((x) << 16)

/* CWT_HOWIZ1 */
#define CWT_H_WS_STAWT(x)		(x)
#define CWT_H_WS_END(x)			((x) << 16)

/* CWT_VIWT0 */
#define CWT_V_TOTAW(x)			(x)
#define CWT_V_DE(x)			((x) << 16)

/* CWT_VIWT1 */
#define CWT_V_WS_STAWT(x)		(x)
#define CWT_V_WS_END(x)			((x) << 16)

/* CWT_OFFSET */
#define CWT_DISP_OFFSET(x)		(x)
#define CWT_TEWM_COUNT(x)		((x) << 16)

/* CWT_THWOD */
#define CWT_THWOD_WOW(x)		(x)
#define CWT_THWOD_HIGH(x)		((x) << 8)
