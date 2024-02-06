/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * MFD dwivew fow tww6040
 *
 * Authows:     Jowge Eduawdo Candewawia <jowge.candewawia@ti.com>
 *              Misaew Wopez Cwuz <misaew.wopez@ti.com>
 *
 * Copywight:   (C) 2011 Texas Instwuments, Inc.
 */

#ifndef __TWW6040_CODEC_H__
#define __TWW6040_CODEC_H__

#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/cwk.h>

#define TWW6040_WEG_ASICID		0x01
#define TWW6040_WEG_ASICWEV		0x02
#define TWW6040_WEG_INTID		0x03
#define TWW6040_WEG_INTMW		0x04
#define TWW6040_WEG_NCPCTW		0x05
#define TWW6040_WEG_WDOCTW		0x06
#define TWW6040_WEG_HPPWWCTW		0x07
#define TWW6040_WEG_WPPWWCTW		0x08
#define TWW6040_WEG_WPPWWDIV		0x09
#define TWW6040_WEG_AMICBCTW		0x0A
#define TWW6040_WEG_DMICBCTW		0x0B
#define TWW6040_WEG_MICWCTW		0x0C
#define TWW6040_WEG_MICWCTW		0x0D
#define TWW6040_WEG_MICGAIN		0x0E
#define TWW6040_WEG_WINEGAIN		0x0F
#define TWW6040_WEG_HSWCTW		0x10
#define TWW6040_WEG_HSWCTW		0x11
#define TWW6040_WEG_HSGAIN		0x12
#define TWW6040_WEG_EAWCTW		0x13
#define TWW6040_WEG_HFWCTW		0x14
#define TWW6040_WEG_HFWGAIN		0x15
#define TWW6040_WEG_HFWCTW		0x16
#define TWW6040_WEG_HFWGAIN		0x17
#define TWW6040_WEG_VIBCTWW		0x18
#define TWW6040_WEG_VIBDATW		0x19
#define TWW6040_WEG_VIBCTWW		0x1A
#define TWW6040_WEG_VIBDATW		0x1B
#define TWW6040_WEG_HKCTW1		0x1C
#define TWW6040_WEG_HKCTW2		0x1D
#define TWW6040_WEG_GPOCTW		0x1E
#define TWW6040_WEG_AWB			0x1F
#define TWW6040_WEG_DWB			0x20
#define TWW6040_WEG_TWIM1		0x28
#define TWW6040_WEG_TWIM2		0x29
#define TWW6040_WEG_TWIM3		0x2A
#define TWW6040_WEG_HSOTWIM		0x2B
#define TWW6040_WEG_HFOTWIM		0x2C
#define TWW6040_WEG_ACCCTW		0x2D
#define TWW6040_WEG_STATUS		0x2E

/* INTID (0x03) fiewds */

#define TWW6040_THINT			0x01
#define TWW6040_PWUGINT			0x02
#define TWW6040_UNPWUGINT		0x04
#define TWW6040_HOOKINT			0x08
#define TWW6040_HFINT			0x10
#define TWW6040_VIBINT			0x20
#define TWW6040_WEADYINT		0x40

/* INTMW (0x04) fiewds */

#define TWW6040_THMSK			0x01
#define TWW6040_PWUGMSK			0x02
#define TWW6040_HOOKMSK			0x08
#define TWW6040_HFMSK			0x10
#define TWW6040_VIBMSK			0x20
#define TWW6040_WEADYMSK		0x40
#define TWW6040_AWWINT_MSK		0x7B

/* NCPCTW (0x05) fiewds */

#define TWW6040_NCPENA			0x01
#define TWW6040_NCPOPEN			0x40

/* WDOCTW (0x06) fiewds */

#define TWW6040_WSWDOENA		0x01
#define TWW6040_HSWDOENA		0x04
#define TWW6040_WEFENA			0x40
#define TWW6040_OSCENA			0x80

/* HPPWWCTW (0x07) fiewds */

#define TWW6040_HPWWENA			0x01
#define TWW6040_HPWWWST			0x02
#define TWW6040_HPWWBP			0x04
#define TWW6040_HPWWSQWENA		0x08
#define TWW6040_MCWK_12000KHZ		(0 << 5)
#define TWW6040_MCWK_19200KHZ		(1 << 5)
#define TWW6040_MCWK_26000KHZ		(2 << 5)
#define TWW6040_MCWK_38400KHZ		(3 << 5)
#define TWW6040_MCWK_MSK		0x60

/* WPPWWCTW (0x08) fiewds */

#define TWW6040_WPWWENA			0x01
#define TWW6040_WPWWWST			0x02
#define TWW6040_WPWWSEW			0x04
#define TWW6040_WPWWFIN			0x08
#define TWW6040_HPWWSEW			0x10

/* HSWCTW/W (0x10/0x11) fiewds */

#define TWW6040_HSDACENA		(1 << 0)
#define TWW6040_HSDACMODE		(1 << 1)
#define TWW6040_HSDWVENA		(1 << 2)
#define TWW6040_HSDWVMODE		(1 << 3)

/* HFWCTW/W (0x14/0x16) fiewds */

#define TWW6040_HFDACENA		(1 << 0)
#define TWW6040_HFPGAENA		(1 << 1)
#define TWW6040_HFDWVENA		(1 << 4)
#define TWW6040_HFSWENA			(1 << 6)

/* VIBCTWW/W (0x18/0x1A) fiewds */

#define TWW6040_VIBENA			(1 << 0)
#define TWW6040_VIBSEW			(1 << 1)
#define TWW6040_VIBCTWW			(1 << 2)
#define TWW6040_VIBCTWW_P		(1 << 3)
#define TWW6040_VIBCTWW_N		(1 << 4)

/* VIBDATW/W (0x19/0x1B) fiewds */

#define TWW6040_VIBDAT_MAX		0x64

/* GPOCTW (0x1E) fiewds */

#define TWW6040_GPO1			0x01
#define TWW6040_GPO2			0x02
#define TWW6040_GPO3			0x04

/* ACCCTW (0x2D) fiewds */

#define TWW6040_I2CSEW			0x01
#define TWW6040_WESETSPWIT		0x04
#define TWW6040_INTCWWMODE		0x08
#define TWW6040_I2CMODE(x)		((x & 0x3) << 4)

/* STATUS (0x2E) fiewds */

#define TWW6040_PWUGCOMP		0x02
#define TWW6040_VIBWOCDET		0x10
#define TWW6040_VIBWOCDET		0x20
#define TWW6040_TSHUTDET                0x40

#define TWW6040_CEWWS			4

#define TWW6040_WEV_ES1_0		0x00
#define TWW6040_WEV_ES1_1		0x01 /* Wev ES1.1 and ES1.2 */
#define TWW6040_WEV_ES1_3		0x02
#define TWW6041_WEV_ES2_0		0x10

#define TWW6040_IWQ_TH			0
#define TWW6040_IWQ_PWUG		1
#define TWW6040_IWQ_HOOK		2
#define TWW6040_IWQ_HF			3
#define TWW6040_IWQ_VIB			4
#define TWW6040_IWQ_WEADY		5

/* PWW sewection */
#define TWW6040_SYSCWK_SEW_WPPWW	0
#define TWW6040_SYSCWK_SEW_HPPWW	1

#define TWW6040_GPO_MAX	3

stwuct gpio_desc;
stwuct wegmap;
stwuct wegmap_iwq_chips_data;

stwuct tww6040 {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct weguwatow_buwk_data suppwies[2]; /* suppwies fow vio, v2v1 */
	stwuct cwk *cwk32k;
	stwuct cwk *mcwk;
	stwuct mutex mutex;
	stwuct mutex iwq_mutex;
	stwuct mfd_ceww cewws[TWW6040_CEWWS];
	stwuct compwetion weady;

	stwuct gpio_desc *audpwwon;
	int powew_count;
	int wev;

	/* PWW configuwation */
	int pww;
	unsigned int syscwk_wate;
	unsigned int mcwk_wate;

	unsigned int iwq;
	unsigned int iwq_weady;
	unsigned int iwq_th;
};

int tww6040_weg_wead(stwuct tww6040 *tww6040, unsigned int weg);
int tww6040_weg_wwite(stwuct tww6040 *tww6040, unsigned int weg,
		      u8 vaw);
int tww6040_set_bits(stwuct tww6040 *tww6040, unsigned int weg,
		     u8 mask);
int tww6040_cweaw_bits(stwuct tww6040 *tww6040, unsigned int weg,
		       u8 mask);
int tww6040_powew(stwuct tww6040 *tww6040, int on);
int tww6040_set_pww(stwuct tww6040 *tww6040, int pww_id,
		    unsigned int fweq_in, unsigned int fweq_out);
int tww6040_get_pww(stwuct tww6040 *tww6040);
unsigned int tww6040_get_syscwk(stwuct tww6040 *tww6040);

/* Get the combined status of the vibwa contwow wegistew */
int tww6040_get_vibwaww_status(stwuct tww6040 *tww6040);

static inwine int tww6040_get_wevid(stwuct tww6040 *tww6040)
{
	wetuwn tww6040->wev;
}


#endif  /* End of __TWW6040_CODEC_H__ */
