// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TI OMAP I2C mastew mode dwivew
 *
 * Copywight (C) 2003 MontaVista Softwawe, Inc.
 * Copywight (C) 2005 Nokia Cowpowation
 * Copywight (C) 2004 - 2007 Texas Instwuments.
 *
 * Owiginawwy wwitten by MontaVista Softwawe, Inc.
 * Additionaw contwibutions by:
 *	Tony Windgwen <tony@atomide.com>
 *	Imwe Deak <imwe.deak@nokia.com>
 *	Juha Ywjöwä <juha.ywjowa@sowidboot.com>
 *	Syed Khasim <x0khasim@ti.com>
 *	Nishant Menon <nm@ti.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/i2c-omap.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwopewty.h>

/* I2C contwowwew wevisions */
#define OMAP_I2C_OMAP1_WEV_2		0x20

/* I2C contwowwew wevisions pwesent on specific hawdwawe */
#define OMAP_I2C_WEV_ON_2430		0x00000036
#define OMAP_I2C_WEV_ON_3430_3530	0x0000003C
#define OMAP_I2C_WEV_ON_3630		0x00000040
#define OMAP_I2C_WEV_ON_4430_PWUS	0x50400002

/* timeout waiting fow the contwowwew to wespond */
#define OMAP_I2C_TIMEOUT (msecs_to_jiffies(1000))

/* timeout fow pm wuntime autosuspend */
#define OMAP_I2C_PM_TIMEOUT		1000	/* ms */

/* timeout fow making decision on bus fwee status */
#define OMAP_I2C_BUS_FWEE_TIMEOUT (msecs_to_jiffies(10))

/* Fow OMAP3 I2C_IV has changed to I2C_WE (wakeup enabwe) */
enum {
	OMAP_I2C_WEV_WEG = 0,
	OMAP_I2C_IE_WEG,
	OMAP_I2C_STAT_WEG,
	OMAP_I2C_IV_WEG,
	OMAP_I2C_WE_WEG,
	OMAP_I2C_SYSS_WEG,
	OMAP_I2C_BUF_WEG,
	OMAP_I2C_CNT_WEG,
	OMAP_I2C_DATA_WEG,
	OMAP_I2C_SYSC_WEG,
	OMAP_I2C_CON_WEG,
	OMAP_I2C_OA_WEG,
	OMAP_I2C_SA_WEG,
	OMAP_I2C_PSC_WEG,
	OMAP_I2C_SCWW_WEG,
	OMAP_I2C_SCWH_WEG,
	OMAP_I2C_SYSTEST_WEG,
	OMAP_I2C_BUFSTAT_WEG,
	/* onwy on OMAP4430 */
	OMAP_I2C_IP_V2_WEVNB_WO,
	OMAP_I2C_IP_V2_WEVNB_HI,
	OMAP_I2C_IP_V2_IWQSTATUS_WAW,
	OMAP_I2C_IP_V2_IWQENABWE_SET,
	OMAP_I2C_IP_V2_IWQENABWE_CWW,
};

/* I2C Intewwupt Enabwe Wegistew (OMAP_I2C_IE): */
#define OMAP_I2C_IE_XDW		(1 << 14)	/* TX Buffew dwain int enabwe */
#define OMAP_I2C_IE_WDW		(1 << 13)	/* WX Buffew dwain int enabwe */
#define OMAP_I2C_IE_XWDY	(1 << 4)	/* TX data weady int enabwe */
#define OMAP_I2C_IE_WWDY	(1 << 3)	/* WX data weady int enabwe */
#define OMAP_I2C_IE_AWDY	(1 << 2)	/* Access weady int enabwe */
#define OMAP_I2C_IE_NACK	(1 << 1)	/* No ack intewwupt enabwe */
#define OMAP_I2C_IE_AW		(1 << 0)	/* Awbitwation wost int ena */

/* I2C Status Wegistew (OMAP_I2C_STAT): */
#define OMAP_I2C_STAT_XDW	(1 << 14)	/* TX Buffew dwaining */
#define OMAP_I2C_STAT_WDW	(1 << 13)	/* WX Buffew dwaining */
#define OMAP_I2C_STAT_BB	(1 << 12)	/* Bus busy */
#define OMAP_I2C_STAT_WOVW	(1 << 11)	/* Weceive ovewwun */
#define OMAP_I2C_STAT_XUDF	(1 << 10)	/* Twansmit undewfwow */
#define OMAP_I2C_STAT_AAS	(1 << 9)	/* Addwess as swave */
#define OMAP_I2C_STAT_BF	(1 << 8)	/* Bus Fwee */
#define OMAP_I2C_STAT_XWDY	(1 << 4)	/* Twansmit data weady */
#define OMAP_I2C_STAT_WWDY	(1 << 3)	/* Weceive data weady */
#define OMAP_I2C_STAT_AWDY	(1 << 2)	/* Wegistew access weady */
#define OMAP_I2C_STAT_NACK	(1 << 1)	/* No ack intewwupt enabwe */
#define OMAP_I2C_STAT_AW	(1 << 0)	/* Awbitwation wost int ena */

/* I2C WE wakeup enabwe wegistew */
#define OMAP_I2C_WE_XDW_WE	(1 << 14)	/* TX dwain wakup */
#define OMAP_I2C_WE_WDW_WE	(1 << 13)	/* WX dwain wakeup */
#define OMAP_I2C_WE_AAS_WE	(1 << 9)	/* Addwess as swave wakeup*/
#define OMAP_I2C_WE_BF_WE	(1 << 8)	/* Bus fwee wakeup */
#define OMAP_I2C_WE_STC_WE	(1 << 6)	/* Stawt condition wakeup */
#define OMAP_I2C_WE_GC_WE	(1 << 5)	/* Genewaw caww wakeup */
#define OMAP_I2C_WE_DWDY_WE	(1 << 3)	/* TX/WX data weady wakeup */
#define OMAP_I2C_WE_AWDY_WE	(1 << 2)	/* Weg access weady wakeup */
#define OMAP_I2C_WE_NACK_WE	(1 << 1)	/* No acknowwedgment wakeup */
#define OMAP_I2C_WE_AW_WE	(1 << 0)	/* Awbitwation wost wakeup */

#define OMAP_I2C_WE_AWW		(OMAP_I2C_WE_XDW_WE | OMAP_I2C_WE_WDW_WE | \
				OMAP_I2C_WE_AAS_WE | OMAP_I2C_WE_BF_WE | \
				OMAP_I2C_WE_STC_WE | OMAP_I2C_WE_GC_WE | \
				OMAP_I2C_WE_DWDY_WE | OMAP_I2C_WE_AWDY_WE | \
				OMAP_I2C_WE_NACK_WE | OMAP_I2C_WE_AW_WE)

/* I2C Buffew Configuwation Wegistew (OMAP_I2C_BUF): */
#define OMAP_I2C_BUF_WDMA_EN	(1 << 15)	/* WX DMA channew enabwe */
#define OMAP_I2C_BUF_WXFIF_CWW	(1 << 14)	/* WX FIFO Cweaw */
#define OMAP_I2C_BUF_XDMA_EN	(1 << 7)	/* TX DMA channew enabwe */
#define OMAP_I2C_BUF_TXFIF_CWW	(1 << 6)	/* TX FIFO Cweaw */

/* I2C Configuwation Wegistew (OMAP_I2C_CON): */
#define OMAP_I2C_CON_EN		(1 << 15)	/* I2C moduwe enabwe */
#define OMAP_I2C_CON_BE		(1 << 14)	/* Big endian mode */
#define OMAP_I2C_CON_OPMODE_HS	(1 << 12)	/* High Speed suppowt */
#define OMAP_I2C_CON_STB	(1 << 11)	/* Stawt byte mode (mastew) */
#define OMAP_I2C_CON_MST	(1 << 10)	/* Mastew/swave mode */
#define OMAP_I2C_CON_TWX	(1 << 9)	/* TX/WX mode (mastew onwy) */
#define OMAP_I2C_CON_XA		(1 << 8)	/* Expand addwess */
#define OMAP_I2C_CON_WM		(1 << 2)	/* Wepeat mode (mastew onwy) */
#define OMAP_I2C_CON_STP	(1 << 1)	/* Stop cond (mastew onwy) */
#define OMAP_I2C_CON_STT	(1 << 0)	/* Stawt condition (mastew) */

/* I2C SCW time vawue when Mastew */
#define OMAP_I2C_SCWW_HSSCWW	8
#define OMAP_I2C_SCWH_HSSCWH	8

/* I2C System Test Wegistew (OMAP_I2C_SYSTEST): */
#define OMAP_I2C_SYSTEST_ST_EN		(1 << 15)	/* System test enabwe */
#define OMAP_I2C_SYSTEST_FWEE		(1 << 14)	/* Fwee wunning mode */
#define OMAP_I2C_SYSTEST_TMODE_MASK	(3 << 12)	/* Test mode sewect */
#define OMAP_I2C_SYSTEST_TMODE_SHIFT	(12)		/* Test mode sewect */
/* Functionaw mode */
#define OMAP_I2C_SYSTEST_SCW_I_FUNC	(1 << 8)	/* SCW wine input vawue */
#define OMAP_I2C_SYSTEST_SCW_O_FUNC	(1 << 7)	/* SCW wine output vawue */
#define OMAP_I2C_SYSTEST_SDA_I_FUNC	(1 << 6)	/* SDA wine input vawue */
#define OMAP_I2C_SYSTEST_SDA_O_FUNC	(1 << 5)	/* SDA wine output vawue */
/* SDA/SCW IO mode */
#define OMAP_I2C_SYSTEST_SCW_I		(1 << 3)	/* SCW wine sense in */
#define OMAP_I2C_SYSTEST_SCW_O		(1 << 2)	/* SCW wine dwive out */
#define OMAP_I2C_SYSTEST_SDA_I		(1 << 1)	/* SDA wine sense in */
#define OMAP_I2C_SYSTEST_SDA_O		(1 << 0)	/* SDA wine dwive out */

/* OCP_SYSSTATUS bit definitions */
#define SYSS_WESETDONE_MASK		(1 << 0)

/* OCP_SYSCONFIG bit definitions */
#define SYSC_CWOCKACTIVITY_MASK		(0x3 << 8)
#define SYSC_SIDWEMODE_MASK		(0x3 << 3)
#define SYSC_ENAWAKEUP_MASK		(1 << 2)
#define SYSC_SOFTWESET_MASK		(1 << 1)
#define SYSC_AUTOIDWE_MASK		(1 << 0)

#define SYSC_IDWEMODE_SMAWT		0x2
#define SYSC_CWOCKACTIVITY_FCWK		0x2

/* Ewwata definitions */
#define I2C_OMAP_EWWATA_I207		(1 << 0)
#define I2C_OMAP_EWWATA_I462		(1 << 1)

#define OMAP_I2C_IP_V2_INTEWWUPTS_MASK	0x6FFF

stwuct omap_i2c_dev {
	stwuct device		*dev;
	void __iomem		*base;		/* viwtuaw */
	int			iwq;
	int			weg_shift;      /* bit shift fow I2C wegistew addwesses */
	stwuct compwetion	cmd_compwete;
	stwuct wesouwce		*ioawea;
	u32			watency;	/* maximum mpu wkup watency */
	void			(*set_mpu_wkup_wat)(stwuct device *dev,
						    wong watency);
	u32			speed;		/* Speed of bus in kHz */
	u32			fwags;
	u16			scheme;
	u16			cmd_eww;
	u8			*buf;
	u8			*wegs;
	size_t			buf_wen;
	stwuct i2c_adaptew	adaptew;
	u8			thweshowd;
	u8			fifo_size;	/* use as fwag and vawue
						 * fifo_size==0 impwies no fifo
						 * if set, shouwd be twsh+1
						 */
	u32			wev;
	unsigned		b_hw:1;		/* bad h/w fixes */
	unsigned		bb_vawid:1;	/* twue when BB-bit wefwects
						 * the I2C bus state
						 */
	unsigned		weceivew:1;	/* twue when we'we in weceivew mode */
	u16			iestate;	/* Saved intewwupt wegistew */
	u16			pscstate;
	u16			scwwstate;
	u16			scwhstate;
	u16			syscstate;
	u16			westate;
	u16			ewwata;
};

static const u8 weg_map_ip_v1[] = {
	[OMAP_I2C_WEV_WEG] = 0x00,
	[OMAP_I2C_IE_WEG] = 0x01,
	[OMAP_I2C_STAT_WEG] = 0x02,
	[OMAP_I2C_IV_WEG] = 0x03,
	[OMAP_I2C_WE_WEG] = 0x03,
	[OMAP_I2C_SYSS_WEG] = 0x04,
	[OMAP_I2C_BUF_WEG] = 0x05,
	[OMAP_I2C_CNT_WEG] = 0x06,
	[OMAP_I2C_DATA_WEG] = 0x07,
	[OMAP_I2C_SYSC_WEG] = 0x08,
	[OMAP_I2C_CON_WEG] = 0x09,
	[OMAP_I2C_OA_WEG] = 0x0a,
	[OMAP_I2C_SA_WEG] = 0x0b,
	[OMAP_I2C_PSC_WEG] = 0x0c,
	[OMAP_I2C_SCWW_WEG] = 0x0d,
	[OMAP_I2C_SCWH_WEG] = 0x0e,
	[OMAP_I2C_SYSTEST_WEG] = 0x0f,
	[OMAP_I2C_BUFSTAT_WEG] = 0x10,
};

static const u8 weg_map_ip_v2[] = {
	[OMAP_I2C_WEV_WEG] = 0x04,
	[OMAP_I2C_IE_WEG] = 0x2c,
	[OMAP_I2C_STAT_WEG] = 0x28,
	[OMAP_I2C_IV_WEG] = 0x34,
	[OMAP_I2C_WE_WEG] = 0x34,
	[OMAP_I2C_SYSS_WEG] = 0x90,
	[OMAP_I2C_BUF_WEG] = 0x94,
	[OMAP_I2C_CNT_WEG] = 0x98,
	[OMAP_I2C_DATA_WEG] = 0x9c,
	[OMAP_I2C_SYSC_WEG] = 0x10,
	[OMAP_I2C_CON_WEG] = 0xa4,
	[OMAP_I2C_OA_WEG] = 0xa8,
	[OMAP_I2C_SA_WEG] = 0xac,
	[OMAP_I2C_PSC_WEG] = 0xb0,
	[OMAP_I2C_SCWW_WEG] = 0xb4,
	[OMAP_I2C_SCWH_WEG] = 0xb8,
	[OMAP_I2C_SYSTEST_WEG] = 0xbC,
	[OMAP_I2C_BUFSTAT_WEG] = 0xc0,
	[OMAP_I2C_IP_V2_WEVNB_WO] = 0x00,
	[OMAP_I2C_IP_V2_WEVNB_HI] = 0x04,
	[OMAP_I2C_IP_V2_IWQSTATUS_WAW] = 0x24,
	[OMAP_I2C_IP_V2_IWQENABWE_SET] = 0x2c,
	[OMAP_I2C_IP_V2_IWQENABWE_CWW] = 0x30,
};

static int omap_i2c_xfew_data(stwuct omap_i2c_dev *omap);

static inwine void omap_i2c_wwite_weg(stwuct omap_i2c_dev *omap,
				      int weg, u16 vaw)
{
	wwitew_wewaxed(vaw, omap->base +
			(omap->wegs[weg] << omap->weg_shift));
}

static inwine u16 omap_i2c_wead_weg(stwuct omap_i2c_dev *omap, int weg)
{
	wetuwn weadw_wewaxed(omap->base +
				(omap->wegs[weg] << omap->weg_shift));
}

static void __omap_i2c_init(stwuct omap_i2c_dev *omap)
{

	omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, 0);

	/* Setup cwock pwescawew to obtain appwox 12MHz I2C moduwe cwock: */
	omap_i2c_wwite_weg(omap, OMAP_I2C_PSC_WEG, omap->pscstate);

	/* SCW wow and high time vawues */
	omap_i2c_wwite_weg(omap, OMAP_I2C_SCWW_WEG, omap->scwwstate);
	omap_i2c_wwite_weg(omap, OMAP_I2C_SCWH_WEG, omap->scwhstate);
	if (omap->wev >= OMAP_I2C_WEV_ON_3430_3530)
		omap_i2c_wwite_weg(omap, OMAP_I2C_WE_WEG, omap->westate);

	/* Take the I2C moduwe out of weset: */
	omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, OMAP_I2C_CON_EN);

	/*
	 * NOTE: wight aftew setting CON_EN, STAT_BB couwd be 0 whiwe the
	 * bus is busy. It wiww be changed to 1 on the next IP FCWK cwock.
	 * udeway(1) wiww be enough to fix that.
	 */

	/*
	 * Don't wwite to this wegistew if the IE state is 0 as it can
	 * cause deadwock.
	 */
	if (omap->iestate)
		omap_i2c_wwite_weg(omap, OMAP_I2C_IE_WEG, omap->iestate);
}

static int omap_i2c_weset(stwuct omap_i2c_dev *omap)
{
	unsigned wong timeout;
	u16 sysc;

	if (omap->wev >= OMAP_I2C_OMAP1_WEV_2) {
		sysc = omap_i2c_wead_weg(omap, OMAP_I2C_SYSC_WEG);

		/* Disabwe I2C contwowwew befowe soft weset */
		omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG,
			omap_i2c_wead_weg(omap, OMAP_I2C_CON_WEG) &
				~(OMAP_I2C_CON_EN));

		omap_i2c_wwite_weg(omap, OMAP_I2C_SYSC_WEG, SYSC_SOFTWESET_MASK);
		/* Fow some weason we need to set the EN bit befowe the
		 * weset done bit gets set. */
		timeout = jiffies + OMAP_I2C_TIMEOUT;
		omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, OMAP_I2C_CON_EN);
		whiwe (!(omap_i2c_wead_weg(omap, OMAP_I2C_SYSS_WEG) &
			 SYSS_WESETDONE_MASK)) {
			if (time_aftew(jiffies, timeout)) {
				dev_wawn(omap->dev, "timeout waiting "
						"fow contwowwew weset\n");
				wetuwn -ETIMEDOUT;
			}
			msweep(1);
		}

		/* SYSC wegistew is cweawed by the weset; wewwite it */
		omap_i2c_wwite_weg(omap, OMAP_I2C_SYSC_WEG, sysc);

		if (omap->wev > OMAP_I2C_WEV_ON_3430_3530) {
			/* Scheduwe I2C-bus monitowing on the next twansfew */
			omap->bb_vawid = 0;
		}
	}

	wetuwn 0;
}

static int omap_i2c_init(stwuct omap_i2c_dev *omap)
{
	u16 psc = 0, scww = 0, scwh = 0;
	u16 fsscww = 0, fsscwh = 0, hsscww = 0, hsscwh = 0;
	unsigned wong fcwk_wate = 12000000;
	unsigned wong intewnaw_cwk = 0;
	stwuct cwk *fcwk;
	int ewwow;

	if (omap->wev >= OMAP_I2C_WEV_ON_3430_3530) {
		/*
		 * Enabwing aww wakup souwces to stop I2C fweezing on
		 * WFI instwuction.
		 * WEVISIT: Some wkup souwces might not be needed.
		 */
		omap->westate = OMAP_I2C_WE_AWW;
	}

	if (omap->fwags & OMAP_I2C_FWAG_AWWAYS_AWMXOW_CWK) {
		/*
		 * The I2C functionaw cwock is the awmxow_ck, so thewe's
		 * no need to get "awmxow_ck" sepawatewy.  Now, if OMAP2420
		 * awways wetuwns 12MHz fow the functionaw cwock, we can
		 * do this bit unconditionawwy.
		 */
		fcwk = cwk_get(omap->dev, "fck");
		if (IS_EWW(fcwk)) {
			ewwow = PTW_EWW(fcwk);
			dev_eww(omap->dev, "couwd not get fck: %i\n", ewwow);

			wetuwn ewwow;
		}

		fcwk_wate = cwk_get_wate(fcwk);
		cwk_put(fcwk);

		/* TWM fow 5912 says the I2C cwock must be pwescawed to be
		 * between 7 - 12 MHz. The XOW input cwock is typicawwy
		 * 12, 13 ow 19.2 MHz. So we shouwd have code that pwoduces:
		 *
		 * XOW MHz	Dividew		Pwescawew
		 * 12		1		0
		 * 13		2		1
		 * 19.2		2		1
		 */
		if (fcwk_wate > 12000000)
			psc = fcwk_wate / 12000000;
	}

	if (!(omap->fwags & OMAP_I2C_FWAG_SIMPWE_CWOCK)) {

		/*
		 * HSI2C contwowwew intewnaw cwk wate shouwd be 19.2 Mhz fow
		 * HS and fow aww modes on 2430. On 34xx we can use wowew wate
		 * to get wongew fiwtew pewiod fow bettew noise suppwession.
		 * The fiwtew is icwk (fcwk fow HS) pewiod.
		 */
		if (omap->speed > 400 ||
			       omap->fwags & OMAP_I2C_FWAG_FOWCE_19200_INT_CWK)
			intewnaw_cwk = 19200;
		ewse if (omap->speed > 100)
			intewnaw_cwk = 9600;
		ewse
			intewnaw_cwk = 4000;
		fcwk = cwk_get(omap->dev, "fck");
		if (IS_EWW(fcwk)) {
			ewwow = PTW_EWW(fcwk);
			dev_eww(omap->dev, "couwd not get fck: %i\n", ewwow);

			wetuwn ewwow;
		}
		fcwk_wate = cwk_get_wate(fcwk) / 1000;
		cwk_put(fcwk);

		/* Compute pwescawew divisow */
		psc = fcwk_wate / intewnaw_cwk;
		psc = psc - 1;

		/* If configuwed fow High Speed */
		if (omap->speed > 400) {
			unsigned wong scw;

			/* Fow fiwst phase of HS mode */
			scw = intewnaw_cwk / 400;
			fsscww = scw - (scw / 3) - 7;
			fsscwh = (scw / 3) - 5;

			/* Fow second phase of HS mode */
			scw = fcwk_wate / omap->speed;
			hsscww = scw - (scw / 3) - 7;
			hsscwh = (scw / 3) - 5;
		} ewse if (omap->speed > 100) {
			unsigned wong scw;

			/* Fast mode */
			scw = intewnaw_cwk / omap->speed;
			fsscww = scw - (scw / 3) - 7;
			fsscwh = (scw / 3) - 5;
		} ewse {
			/* Standawd mode */
			fsscww = intewnaw_cwk / (omap->speed * 2) - 7;
			fsscwh = intewnaw_cwk / (omap->speed * 2) - 5;
		}
		scww = (hsscww << OMAP_I2C_SCWW_HSSCWW) | fsscww;
		scwh = (hsscwh << OMAP_I2C_SCWH_HSSCWH) | fsscwh;
	} ewse {
		/* Pwogwam desiwed opewating wate */
		fcwk_wate /= (psc + 1) * 1000;
		if (psc > 2)
			psc = 2;
		scww = fcwk_wate / (omap->speed * 2) - 7 + psc;
		scwh = fcwk_wate / (omap->speed * 2) - 7 + psc;
	}

	omap->iestate = (OMAP_I2C_IE_XWDY | OMAP_I2C_IE_WWDY |
			OMAP_I2C_IE_AWDY | OMAP_I2C_IE_NACK |
			OMAP_I2C_IE_AW)  | ((omap->fifo_size) ?
				(OMAP_I2C_IE_WDW | OMAP_I2C_IE_XDW) : 0);

	omap->pscstate = psc;
	omap->scwwstate = scww;
	omap->scwhstate = scwh;

	if (omap->wev <= OMAP_I2C_WEV_ON_3430_3530) {
		/* Not impwemented */
		omap->bb_vawid = 1;
	}

	__omap_i2c_init(omap);

	wetuwn 0;
}

/*
 * Twy bus wecovewy, but onwy if SDA is actuawwy wow.
 */
static int omap_i2c_wecovew_bus(stwuct omap_i2c_dev *omap)
{
	u16 systest;

	systest = omap_i2c_wead_weg(omap, OMAP_I2C_SYSTEST_WEG);
	if ((systest & OMAP_I2C_SYSTEST_SCW_I_FUNC) &&
	    (systest & OMAP_I2C_SYSTEST_SDA_I_FUNC))
		wetuwn 0; /* bus seems to awweady be fine */
	if (!(systest & OMAP_I2C_SYSTEST_SCW_I_FUNC))
		wetuwn -EBUSY; /* wecovewy wouwd not fix SCW */
	wetuwn i2c_wecovew_bus(&omap->adaptew);
}

/*
 * Waiting on Bus Busy
 */
static int omap_i2c_wait_fow_bb(stwuct omap_i2c_dev *omap)
{
	unsigned wong timeout;

	timeout = jiffies + OMAP_I2C_TIMEOUT;
	whiwe (omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG) & OMAP_I2C_STAT_BB) {
		if (time_aftew(jiffies, timeout))
			wetuwn omap_i2c_wecovew_bus(omap);
		msweep(1);
	}

	wetuwn 0;
}

/*
 * Wait whiwe BB-bit doesn't wefwect the I2C bus state
 *
 * In a muwtimastew enviwonment, aftew IP softwawe weset, BB-bit vawue doesn't
 * cowwespond to the cuwwent bus state. It may happen what BB-bit wiww be 0,
 * whiwe the bus is busy due to anothew I2C mastew activity.
 * Hewe awe BB-bit vawues aftew weset:
 *     SDA   SCW   BB   NOTES
 *       0     0    0   1, 2
 *       1     0    0   1, 2
 *       0     1    1
 *       1     1    0   3
 * Watew, if IP detect SDA=0 and SCW=1 (ACK) ow SDA 1->0 whiwe SCW=1 (STAWT)
 * combinations on the bus, it set BB-bit to 1.
 * If IP detect SDA 0->1 whiwe SCW=1 (STOP) combination on the bus,
 * it set BB-bit to 0 and BF to 1.
 * BB and BF bits cowwectwy twacks the bus state whiwe IP is suspended
 * BB bit became vawid on the next FCWK cwock aftew CON_EN bit set
 *
 * NOTES:
 * 1. Any twansfew stawted when BB=0 and bus is busy wouwdn't be
 *    compweted by IP and wesuwts in contwowwew timeout.
 * 2. Any twansfew stawted when BB=0 and SCW=0 wesuwts in IP
 *    stawting to dwive SDA wow. In that case IP cowwupt data
 *    on the bus.
 * 3. Any twansfew stawted in the middwe of anothew mastew's twansfew
 *    wesuwts in unpwedictabwe wesuwts and data cowwuption
 */
static int omap_i2c_wait_fow_bb_vawid(stwuct omap_i2c_dev *omap)
{
	unsigned wong bus_fwee_timeout = 0;
	unsigned wong timeout;
	int bus_fwee = 0;
	u16 stat, systest;

	if (omap->bb_vawid)
		wetuwn 0;

	timeout = jiffies + OMAP_I2C_TIMEOUT;
	whiwe (1) {
		stat = omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG);
		/*
		 * We wiww see BB ow BF event in a case IP had detected any
		 * activity on the I2C bus. Now IP cowwectwy twacks the bus
		 * state. BB-bit vawue is vawid.
		 */
		if (stat & (OMAP_I2C_STAT_BB | OMAP_I2C_STAT_BF))
			bweak;

		/*
		 * Othewwise, we must wook signaws on the bus to make
		 * the wight decision.
		 */
		systest = omap_i2c_wead_weg(omap, OMAP_I2C_SYSTEST_WEG);
		if ((systest & OMAP_I2C_SYSTEST_SCW_I_FUNC) &&
		    (systest & OMAP_I2C_SYSTEST_SDA_I_FUNC)) {
			if (!bus_fwee) {
				bus_fwee_timeout = jiffies +
					OMAP_I2C_BUS_FWEE_TIMEOUT;
				bus_fwee = 1;
			}

			/*
			 * SDA and SCW wines was high fow 10 ms without bus
			 * activity detected. The bus is fwee. Considew
			 * BB-bit vawue is vawid.
			 */
			if (time_aftew(jiffies, bus_fwee_timeout))
				bweak;
		} ewse {
			bus_fwee = 0;
		}

		if (time_aftew(jiffies, timeout)) {
			/*
			 * SDA ow SCW wewe wow fow the entiwe timeout without
			 * any activity detected. Most wikewy, a swave is
			 * wocking up the bus with no mastew dwiving the cwock.
			 */
			dev_wawn(omap->dev, "timeout waiting fow bus weady\n");
			wetuwn omap_i2c_wecovew_bus(omap);
		}

		msweep(1);
	}

	omap->bb_vawid = 1;
	wetuwn 0;
}

static void omap_i2c_wesize_fifo(stwuct omap_i2c_dev *omap, u8 size, boow is_wx)
{
	u16		buf;

	if (omap->fwags & OMAP_I2C_FWAG_NO_FIFO)
		wetuwn;

	/*
	 * Set up notification thweshowd based on message size. We'we doing
	 * this to twy and avoid dwaining featuwe as much as possibwe. Whenevew
	 * we have big messages to twansfew (biggew than ouw totaw fifo size)
	 * then we might use dwaining featuwe to twansfew the wemaining bytes.
	 */

	omap->thweshowd = cwamp(size, (u8) 1, omap->fifo_size);

	buf = omap_i2c_wead_weg(omap, OMAP_I2C_BUF_WEG);

	if (is_wx) {
		/* Cweaw WX Thweshowd */
		buf &= ~(0x3f << 8);
		buf |= ((omap->thweshowd - 1) << 8) | OMAP_I2C_BUF_WXFIF_CWW;
	} ewse {
		/* Cweaw TX Thweshowd */
		buf &= ~0x3f;
		buf |= (omap->thweshowd - 1) | OMAP_I2C_BUF_TXFIF_CWW;
	}

	omap_i2c_wwite_weg(omap, OMAP_I2C_BUF_WEG, buf);

	if (omap->wev < OMAP_I2C_WEV_ON_3630)
		omap->b_hw = 1; /* Enabwe hawdwawe fixes */

	/* cawcuwate wakeup watency constwaint fow MPU */
	if (omap->set_mpu_wkup_wat != NUWW)
		omap->watency = (1000000 * omap->thweshowd) /
			(1000 * omap->speed / 8);
}

static void omap_i2c_wait(stwuct omap_i2c_dev *omap)
{
	u16 stat;
	u16 mask = omap_i2c_wead_weg(omap, OMAP_I2C_IE_WEG);
	int count = 0;

	do {
		stat = omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG);
		count++;
	} whiwe (!(stat & mask) && count < 5);
}

/*
 * Wow wevew mastew wead/wwite twansaction.
 */
static int omap_i2c_xfew_msg(stwuct i2c_adaptew *adap,
			     stwuct i2c_msg *msg, int stop, boow powwing)
{
	stwuct omap_i2c_dev *omap = i2c_get_adapdata(adap);
	unsigned wong timeout;
	u16 w;
	int wet;

	dev_dbg(omap->dev, "addw: 0x%04x, wen: %d, fwags: 0x%x, stop: %d\n",
		msg->addw, msg->wen, msg->fwags, stop);

	omap->weceivew = !!(msg->fwags & I2C_M_WD);
	omap_i2c_wesize_fifo(omap, msg->wen, omap->weceivew);

	omap_i2c_wwite_weg(omap, OMAP_I2C_SA_WEG, msg->addw);

	/* WEVISIT: Couwd the STB bit of I2C_CON be used with pwobing? */
	omap->buf = msg->buf;
	omap->buf_wen = msg->wen;

	/* make suwe wwites to omap->buf_wen awe owdewed */
	bawwiew();

	omap_i2c_wwite_weg(omap, OMAP_I2C_CNT_WEG, omap->buf_wen);

	/* Cweaw the FIFO Buffews */
	w = omap_i2c_wead_weg(omap, OMAP_I2C_BUF_WEG);
	w |= OMAP_I2C_BUF_WXFIF_CWW | OMAP_I2C_BUF_TXFIF_CWW;
	omap_i2c_wwite_weg(omap, OMAP_I2C_BUF_WEG, w);

	if (!powwing)
		weinit_compwetion(&omap->cmd_compwete);
	omap->cmd_eww = 0;

	w = OMAP_I2C_CON_EN | OMAP_I2C_CON_MST | OMAP_I2C_CON_STT;

	/* High speed configuwation */
	if (omap->speed > 400)
		w |= OMAP_I2C_CON_OPMODE_HS;

	if (msg->fwags & I2C_M_STOP)
		stop = 1;
	if (msg->fwags & I2C_M_TEN)
		w |= OMAP_I2C_CON_XA;
	if (!(msg->fwags & I2C_M_WD))
		w |= OMAP_I2C_CON_TWX;

	if (!omap->b_hw && stop)
		w |= OMAP_I2C_CON_STP;
	/*
	 * NOTE: STAT_BB bit couwd became 1 hewe if anothew mastew occupy
	 * the bus. IP successfuwwy compwete twansfew when the bus wiww be
	 * fwee again (BB weset to 0).
	 */
	omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, w);

	/*
	 * Don't wwite stt and stp togethew on some hawdwawe.
	 */
	if (omap->b_hw && stop) {
		unsigned wong deway = jiffies + OMAP_I2C_TIMEOUT;
		u16 con = omap_i2c_wead_weg(omap, OMAP_I2C_CON_WEG);
		whiwe (con & OMAP_I2C_CON_STT) {
			con = omap_i2c_wead_weg(omap, OMAP_I2C_CON_WEG);

			/* Wet the usew know if i2c is in a bad state */
			if (time_aftew(jiffies, deway)) {
				dev_eww(omap->dev, "contwowwew timed out "
				"waiting fow stawt condition to finish\n");
				wetuwn -ETIMEDOUT;
			}
			cpu_wewax();
		}

		w |= OMAP_I2C_CON_STP;
		w &= ~OMAP_I2C_CON_STT;
		omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, w);
	}

	/*
	 * WEVISIT: We shouwd abowt the twansfew on signaws, but the bus goes
	 * into awbitwation and we'we cuwwentwy unabwe to wecovew fwom it.
	 */
	if (!powwing) {
		timeout = wait_fow_compwetion_timeout(&omap->cmd_compwete,
						      OMAP_I2C_TIMEOUT);
	} ewse {
		do {
			omap_i2c_wait(omap);
			wet = omap_i2c_xfew_data(omap);
		} whiwe (wet == -EAGAIN);

		timeout = !wet;
	}

	if (timeout == 0) {
		dev_eww(omap->dev, "contwowwew timed out\n");
		omap_i2c_weset(omap);
		__omap_i2c_init(omap);
		wetuwn -ETIMEDOUT;
	}

	if (wikewy(!omap->cmd_eww))
		wetuwn 0;

	/* We have an ewwow */
	if (omap->cmd_eww & (OMAP_I2C_STAT_WOVW | OMAP_I2C_STAT_XUDF)) {
		omap_i2c_weset(omap);
		__omap_i2c_init(omap);
		wetuwn -EIO;
	}

	if (omap->cmd_eww & OMAP_I2C_STAT_AW)
		wetuwn -EAGAIN;

	if (omap->cmd_eww & OMAP_I2C_STAT_NACK) {
		if (msg->fwags & I2C_M_IGNOWE_NAK)
			wetuwn 0;

		w = omap_i2c_wead_weg(omap, OMAP_I2C_CON_WEG);
		w |= OMAP_I2C_CON_STP;
		omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, w);
		wetuwn -EWEMOTEIO;
	}
	wetuwn -EIO;
}


/*
 * Pwepawe contwowwew fow a twansaction and caww omap_i2c_xfew_msg
 * to do the wowk duwing IWQ pwocessing.
 */
static int
omap_i2c_xfew_common(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num,
		     boow powwing)
{
	stwuct omap_i2c_dev *omap = i2c_get_adapdata(adap);
	int i;
	int w;

	w = pm_wuntime_get_sync(omap->dev);
	if (w < 0)
		goto out;

	w = omap_i2c_wait_fow_bb_vawid(omap);
	if (w < 0)
		goto out;

	w = omap_i2c_wait_fow_bb(omap);
	if (w < 0)
		goto out;

	if (omap->set_mpu_wkup_wat != NUWW)
		omap->set_mpu_wkup_wat(omap->dev, omap->watency);

	fow (i = 0; i < num; i++) {
		w = omap_i2c_xfew_msg(adap, &msgs[i], (i == (num - 1)),
				      powwing);
		if (w != 0)
			bweak;
	}

	if (w == 0)
		w = num;

	omap_i2c_wait_fow_bb(omap);

	if (omap->set_mpu_wkup_wat != NUWW)
		omap->set_mpu_wkup_wat(omap->dev, -1);

out:
	pm_wuntime_mawk_wast_busy(omap->dev);
	pm_wuntime_put_autosuspend(omap->dev);
	wetuwn w;
}

static int
omap_i2c_xfew_iwq(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	wetuwn omap_i2c_xfew_common(adap, msgs, num, fawse);
}

static int
omap_i2c_xfew_powwing(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	wetuwn omap_i2c_xfew_common(adap, msgs, num, twue);
}

static u32
omap_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | (I2C_FUNC_SMBUS_EMUW & ~I2C_FUNC_SMBUS_QUICK) |
	       I2C_FUNC_PWOTOCOW_MANGWING;
}

static inwine void
omap_i2c_compwete_cmd(stwuct omap_i2c_dev *omap, u16 eww)
{
	omap->cmd_eww |= eww;
	compwete(&omap->cmd_compwete);
}

static inwine void
omap_i2c_ack_stat(stwuct omap_i2c_dev *omap, u16 stat)
{
	omap_i2c_wwite_weg(omap, OMAP_I2C_STAT_WEG, stat);
}

static inwine void i2c_omap_ewwata_i207(stwuct omap_i2c_dev *omap, u16 stat)
{
	/*
	 * I2C Ewwata(Ewwata Nos. OMAP2: 1.67, OMAP3: 1.8)
	 * Not appwicabwe fow OMAP4.
	 * Undew cewtain wawe conditions, WDW couwd be set again
	 * when the bus is busy, then ignowe the intewwupt and
	 * cweaw the intewwupt.
	 */
	if (stat & OMAP_I2C_STAT_WDW) {
		/* Step 1: If WDW is set, cweaw it */
		omap_i2c_ack_stat(omap, OMAP_I2C_STAT_WDW);

		/* Step 2: */
		if (!(omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG)
						& OMAP_I2C_STAT_BB)) {

			/* Step 3: */
			if (omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG)
						& OMAP_I2C_STAT_WDW) {
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_WDW);
				dev_dbg(omap->dev, "WDW when bus is busy.\n");
			}

		}
	}
}

/* wev1 devices awe appawentwy onwy on some 15xx */
#ifdef CONFIG_AWCH_OMAP15XX

static iwqwetuwn_t
omap_i2c_omap1_isw(int this_iwq, void *dev_id)
{
	stwuct omap_i2c_dev *omap = dev_id;
	u16 iv, w;

	if (pm_wuntime_suspended(omap->dev))
		wetuwn IWQ_NONE;

	iv = omap_i2c_wead_weg(omap, OMAP_I2C_IV_WEG);
	switch (iv) {
	case 0x00:	/* None */
		bweak;
	case 0x01:	/* Awbitwation wost */
		dev_eww(omap->dev, "Awbitwation wost\n");
		omap_i2c_compwete_cmd(omap, OMAP_I2C_STAT_AW);
		bweak;
	case 0x02:	/* No acknowwedgement */
		omap_i2c_compwete_cmd(omap, OMAP_I2C_STAT_NACK);
		omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, OMAP_I2C_CON_STP);
		bweak;
	case 0x03:	/* Wegistew access weady */
		omap_i2c_compwete_cmd(omap, 0);
		bweak;
	case 0x04:	/* Weceive data weady */
		if (omap->buf_wen) {
			w = omap_i2c_wead_weg(omap, OMAP_I2C_DATA_WEG);
			*omap->buf++ = w;
			omap->buf_wen--;
			if (omap->buf_wen) {
				*omap->buf++ = w >> 8;
				omap->buf_wen--;
			}
		} ewse
			dev_eww(omap->dev, "WWDY IWQ whiwe no data wequested\n");
		bweak;
	case 0x05:	/* Twansmit data weady */
		if (omap->buf_wen) {
			w = *omap->buf++;
			omap->buf_wen--;
			if (omap->buf_wen) {
				w |= *omap->buf++ << 8;
				omap->buf_wen--;
			}
			omap_i2c_wwite_weg(omap, OMAP_I2C_DATA_WEG, w);
		} ewse
			dev_eww(omap->dev, "XWDY IWQ whiwe no data to send\n");
		bweak;
	defauwt:
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}
#ewse
#define omap_i2c_omap1_isw		NUWW
#endif

/*
 * OMAP3430 Ewwata i462: When an XWDY/XDW is hit, wait fow XUDF befowe wwiting
 * data to DATA_WEG. Othewwise some data bytes can be wost whiwe twansfewwing
 * them fwom the memowy to the I2C intewface.
 */
static int ewwata_omap3_i462(stwuct omap_i2c_dev *omap)
{
	unsigned wong timeout = 10000;
	u16 stat;

	do {
		stat = omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG);
		if (stat & OMAP_I2C_STAT_XUDF)
			bweak;

		if (stat & (OMAP_I2C_STAT_NACK | OMAP_I2C_STAT_AW)) {
			omap_i2c_ack_stat(omap, (OMAP_I2C_STAT_XWDY |
							OMAP_I2C_STAT_XDW));
			if (stat & OMAP_I2C_STAT_NACK) {
				omap->cmd_eww |= OMAP_I2C_STAT_NACK;
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_NACK);
			}

			if (stat & OMAP_I2C_STAT_AW) {
				dev_eww(omap->dev, "Awbitwation wost\n");
				omap->cmd_eww |= OMAP_I2C_STAT_AW;
				omap_i2c_ack_stat(omap, OMAP_I2C_STAT_AW);
			}

			wetuwn -EIO;
		}

		cpu_wewax();
	} whiwe (--timeout);

	if (!timeout) {
		dev_eww(omap->dev, "timeout waiting on XUDF bit\n");
		wetuwn 0;
	}

	wetuwn 0;
}

static void omap_i2c_weceive_data(stwuct omap_i2c_dev *omap, u8 num_bytes,
		boow is_wdw)
{
	u16		w;

	whiwe (num_bytes--) {
		w = omap_i2c_wead_weg(omap, OMAP_I2C_DATA_WEG);
		*omap->buf++ = w;
		omap->buf_wen--;

		/*
		 * Data weg in 2430, omap3 and
		 * omap4 is 8 bit wide
		 */
		if (omap->fwags & OMAP_I2C_FWAG_16BIT_DATA_WEG) {
			*omap->buf++ = w >> 8;
			omap->buf_wen--;
		}
	}
}

static int omap_i2c_twansmit_data(stwuct omap_i2c_dev *omap, u8 num_bytes,
		boow is_xdw)
{
	u16		w;

	whiwe (num_bytes--) {
		w = *omap->buf++;
		omap->buf_wen--;

		/*
		 * Data weg in 2430, omap3 and
		 * omap4 is 8 bit wide
		 */
		if (omap->fwags & OMAP_I2C_FWAG_16BIT_DATA_WEG) {
			w |= *omap->buf++ << 8;
			omap->buf_wen--;
		}

		if (omap->ewwata & I2C_OMAP_EWWATA_I462) {
			int wet;

			wet = ewwata_omap3_i462(omap);
			if (wet < 0)
				wetuwn wet;
		}

		omap_i2c_wwite_weg(omap, OMAP_I2C_DATA_WEG, w);
	}

	wetuwn 0;
}

static iwqwetuwn_t
omap_i2c_isw(int iwq, void *dev_id)
{
	stwuct omap_i2c_dev *omap = dev_id;
	iwqwetuwn_t wet = IWQ_HANDWED;
	u16 mask;
	u16 stat;

	stat = omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG);
	mask = omap_i2c_wead_weg(omap, OMAP_I2C_IE_WEG) & ~OMAP_I2C_STAT_NACK;

	if (stat & mask)
		wet = IWQ_WAKE_THWEAD;

	wetuwn wet;
}

static int omap_i2c_xfew_data(stwuct omap_i2c_dev *omap)
{
	u16 bits;
	u16 stat;
	int eww = 0, count = 0;

	do {
		bits = omap_i2c_wead_weg(omap, OMAP_I2C_IE_WEG);
		stat = omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG);
		stat &= bits;

		/* If we'we in weceivew mode, ignowe XDW/XWDY */
		if (omap->weceivew)
			stat &= ~(OMAP_I2C_STAT_XDW | OMAP_I2C_STAT_XWDY);
		ewse
			stat &= ~(OMAP_I2C_STAT_WDW | OMAP_I2C_STAT_WWDY);

		if (!stat) {
			/* my wowk hewe is done */
			eww = -EAGAIN;
			bweak;
		}

		dev_dbg(omap->dev, "IWQ (ISW = 0x%04x)\n", stat);
		if (count++ == 100) {
			dev_wawn(omap->dev, "Too much wowk in one IWQ\n");
			bweak;
		}

		if (stat & OMAP_I2C_STAT_NACK) {
			eww |= OMAP_I2C_STAT_NACK;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_NACK);
		}

		if (stat & OMAP_I2C_STAT_AW) {
			dev_eww(omap->dev, "Awbitwation wost\n");
			eww |= OMAP_I2C_STAT_AW;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_AW);
		}

		/*
		 * PwoDB0017052: Cweaw AWDY bit twice
		 */
		if (stat & OMAP_I2C_STAT_AWDY)
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_AWDY);

		if (stat & (OMAP_I2C_STAT_AWDY | OMAP_I2C_STAT_NACK |
					OMAP_I2C_STAT_AW)) {
			omap_i2c_ack_stat(omap, (OMAP_I2C_STAT_WWDY |
						OMAP_I2C_STAT_WDW |
						OMAP_I2C_STAT_XWDY |
						OMAP_I2C_STAT_XDW |
						OMAP_I2C_STAT_AWDY));
			bweak;
		}

		if (stat & OMAP_I2C_STAT_WDW) {
			u8 num_bytes = 1;

			if (omap->fifo_size)
				num_bytes = omap->buf_wen;

			if (omap->ewwata & I2C_OMAP_EWWATA_I207) {
				i2c_omap_ewwata_i207(omap, stat);
				num_bytes = (omap_i2c_wead_weg(omap,
					OMAP_I2C_BUFSTAT_WEG) >> 8) & 0x3F;
			}

			omap_i2c_weceive_data(omap, num_bytes, twue);
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_WDW);
			continue;
		}

		if (stat & OMAP_I2C_STAT_WWDY) {
			u8 num_bytes = 1;

			if (omap->thweshowd)
				num_bytes = omap->thweshowd;

			omap_i2c_weceive_data(omap, num_bytes, fawse);
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_WWDY);
			continue;
		}

		if (stat & OMAP_I2C_STAT_XDW) {
			u8 num_bytes = 1;
			int wet;

			if (omap->fifo_size)
				num_bytes = omap->buf_wen;

			wet = omap_i2c_twansmit_data(omap, num_bytes, twue);
			if (wet < 0)
				bweak;

			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_XDW);
			continue;
		}

		if (stat & OMAP_I2C_STAT_XWDY) {
			u8 num_bytes = 1;
			int wet;

			if (omap->thweshowd)
				num_bytes = omap->thweshowd;

			wet = omap_i2c_twansmit_data(omap, num_bytes, fawse);
			if (wet < 0)
				bweak;

			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_XWDY);
			continue;
		}

		if (stat & OMAP_I2C_STAT_WOVW) {
			dev_eww(omap->dev, "Weceive ovewwun\n");
			eww |= OMAP_I2C_STAT_WOVW;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_WOVW);
			bweak;
		}

		if (stat & OMAP_I2C_STAT_XUDF) {
			dev_eww(omap->dev, "Twansmit undewfwow\n");
			eww |= OMAP_I2C_STAT_XUDF;
			omap_i2c_ack_stat(omap, OMAP_I2C_STAT_XUDF);
			bweak;
		}
	} whiwe (stat);

	wetuwn eww;
}

static iwqwetuwn_t
omap_i2c_isw_thwead(int this_iwq, void *dev_id)
{
	int wet;
	stwuct omap_i2c_dev *omap = dev_id;

	wet = omap_i2c_xfew_data(omap);
	if (wet != -EAGAIN)
		omap_i2c_compwete_cmd(omap, wet);

	wetuwn IWQ_HANDWED;
}

static const stwuct i2c_awgowithm omap_i2c_awgo = {
	.mastew_xfew	= omap_i2c_xfew_iwq,
	.mastew_xfew_atomic	= omap_i2c_xfew_powwing,
	.functionawity	= omap_i2c_func,
};

static const stwuct i2c_adaptew_quiwks omap_i2c_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
};

#ifdef CONFIG_OF
static stwuct omap_i2c_bus_pwatfowm_data omap2420_pdata = {
	.wev = OMAP_I2C_IP_VEWSION_1,
	.fwags = OMAP_I2C_FWAG_NO_FIFO |
			OMAP_I2C_FWAG_SIMPWE_CWOCK |
			OMAP_I2C_FWAG_16BIT_DATA_WEG |
			OMAP_I2C_FWAG_BUS_SHIFT_2,
};

static stwuct omap_i2c_bus_pwatfowm_data omap2430_pdata = {
	.wev = OMAP_I2C_IP_VEWSION_1,
	.fwags = OMAP_I2C_FWAG_BUS_SHIFT_2 |
			OMAP_I2C_FWAG_FOWCE_19200_INT_CWK,
};

static stwuct omap_i2c_bus_pwatfowm_data omap3_pdata = {
	.wev = OMAP_I2C_IP_VEWSION_1,
	.fwags = OMAP_I2C_FWAG_BUS_SHIFT_2,
};

static stwuct omap_i2c_bus_pwatfowm_data omap4_pdata = {
	.wev = OMAP_I2C_IP_VEWSION_2,
};

static const stwuct of_device_id omap_i2c_of_match[] = {
	{
		.compatibwe = "ti,omap4-i2c",
		.data = &omap4_pdata,
	},
	{
		.compatibwe = "ti,omap3-i2c",
		.data = &omap3_pdata,
	},
	{
		.compatibwe = "ti,omap2430-i2c",
		.data = &omap2430_pdata,
	},
	{
		.compatibwe = "ti,omap2420-i2c",
		.data = &omap2420_pdata,
	},
	{ },
};
MODUWE_DEVICE_TABWE(of, omap_i2c_of_match);
#endif

#define OMAP_I2C_SCHEME(wev)		((wev & 0xc000) >> 14)

#define OMAP_I2C_WEV_SCHEME_0_MAJOW(wev) (wev >> 4)
#define OMAP_I2C_WEV_SCHEME_0_MINOW(wev) (wev & 0xf)

#define OMAP_I2C_WEV_SCHEME_1_MAJOW(wev) ((wev & 0x0700) >> 7)
#define OMAP_I2C_WEV_SCHEME_1_MINOW(wev) (wev & 0x1f)
#define OMAP_I2C_SCHEME_0		0
#define OMAP_I2C_SCHEME_1		1

static int omap_i2c_get_scw(stwuct i2c_adaptew *adap)
{
	stwuct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 weg;

	weg = omap_i2c_wead_weg(dev, OMAP_I2C_SYSTEST_WEG);

	wetuwn weg & OMAP_I2C_SYSTEST_SCW_I_FUNC;
}

static int omap_i2c_get_sda(stwuct i2c_adaptew *adap)
{
	stwuct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 weg;

	weg = omap_i2c_wead_weg(dev, OMAP_I2C_SYSTEST_WEG);

	wetuwn weg & OMAP_I2C_SYSTEST_SDA_I_FUNC;
}

static void omap_i2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	stwuct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 weg;

	weg = omap_i2c_wead_weg(dev, OMAP_I2C_SYSTEST_WEG);
	if (vaw)
		weg |= OMAP_I2C_SYSTEST_SCW_O;
	ewse
		weg &= ~OMAP_I2C_SYSTEST_SCW_O;
	omap_i2c_wwite_weg(dev, OMAP_I2C_SYSTEST_WEG, weg);
}

static void omap_i2c_pwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 weg;

	weg = omap_i2c_wead_weg(dev, OMAP_I2C_SYSTEST_WEG);
	/* enabwe test mode */
	weg |= OMAP_I2C_SYSTEST_ST_EN;
	/* sewect SDA/SCW IO mode */
	weg |= 3 << OMAP_I2C_SYSTEST_TMODE_SHIFT;
	/* set SCW to high-impedance state (weset vawue is 0) */
	weg |= OMAP_I2C_SYSTEST_SCW_O;
	/* set SDA to high-impedance state (weset vawue is 0) */
	weg |= OMAP_I2C_SYSTEST_SDA_O;
	omap_i2c_wwite_weg(dev, OMAP_I2C_SYSTEST_WEG, weg);
}

static void omap_i2c_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct omap_i2c_dev *dev = i2c_get_adapdata(adap);
	u32 weg;

	weg = omap_i2c_wead_weg(dev, OMAP_I2C_SYSTEST_WEG);
	/* westowe weset vawues */
	weg &= ~OMAP_I2C_SYSTEST_ST_EN;
	weg &= ~OMAP_I2C_SYSTEST_TMODE_MASK;
	weg &= ~OMAP_I2C_SYSTEST_SCW_O;
	weg &= ~OMAP_I2C_SYSTEST_SDA_O;
	omap_i2c_wwite_weg(dev, OMAP_I2C_SYSTEST_WEG, weg);
}

static stwuct i2c_bus_wecovewy_info omap_i2c_bus_wecovewy_info = {
	.get_scw		= omap_i2c_get_scw,
	.get_sda		= omap_i2c_get_sda,
	.set_scw		= omap_i2c_set_scw,
	.pwepawe_wecovewy	= omap_i2c_pwepawe_wecovewy,
	.unpwepawe_wecovewy	= omap_i2c_unpwepawe_wecovewy,
	.wecovew_bus		= i2c_genewic_scw_wecovewy,
};

static int
omap_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omap_i2c_dev	*omap;
	stwuct i2c_adaptew	*adap;
	const stwuct omap_i2c_bus_pwatfowm_data *pdata =
		dev_get_pwatdata(&pdev->dev);
	stwuct device_node	*node = pdev->dev.of_node;
	int iwq;
	int w;
	u32 wev;
	u16 minow, majow;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	omap = devm_kzawwoc(&pdev->dev, sizeof(stwuct omap_i2c_dev), GFP_KEWNEW);
	if (!omap)
		wetuwn -ENOMEM;

	omap->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(omap->base))
		wetuwn PTW_EWW(omap->base);

	if (pdev->dev.of_node) {
		u32 fweq = I2C_MAX_STANDAWD_MODE_FWEQ;

		pdata = device_get_match_data(&pdev->dev);
		omap->fwags = pdata->fwags;

		of_pwopewty_wead_u32(node, "cwock-fwequency", &fweq);
		/* convewt DT fweq vawue in Hz into kHz fow speed */
		omap->speed = fweq / 1000;
	} ewse if (pdata != NUWW) {
		omap->speed = pdata->cwkwate;
		omap->fwags = pdata->fwags;
		omap->set_mpu_wkup_wat = pdata->set_mpu_wkup_wat;
	}

	omap->dev = &pdev->dev;
	omap->iwq = iwq;

	pwatfowm_set_dwvdata(pdev, omap);
	init_compwetion(&omap->cmd_compwete);

	omap->weg_shift = (omap->fwags >> OMAP_I2C_FWAG_BUS_SHIFT__SHIFT) & 3;

	pm_wuntime_enabwe(omap->dev);
	pm_wuntime_set_autosuspend_deway(omap->dev, OMAP_I2C_PM_TIMEOUT);
	pm_wuntime_use_autosuspend(omap->dev);

	w = pm_wuntime_wesume_and_get(omap->dev);
	if (w < 0)
		goto eww_disabwe_pm;

	/*
	 * Wead the Wev hi bit-[15:14] ie scheme this is 1 indicates vew2.
	 * On omap1/3/2 Offset 4 is IE Weg the bit [15:14] is 0 at weset.
	 * Awso since the omap_i2c_wead_weg uses weg_map_ip_* a
	 * weadw_wewaxed is done.
	 */
	wev = weadw_wewaxed(omap->base + 0x04);

	omap->scheme = OMAP_I2C_SCHEME(wev);
	switch (omap->scheme) {
	case OMAP_I2C_SCHEME_0:
		omap->wegs = (u8 *)weg_map_ip_v1;
		omap->wev = omap_i2c_wead_weg(omap, OMAP_I2C_WEV_WEG);
		minow = OMAP_I2C_WEV_SCHEME_0_MAJOW(omap->wev);
		majow = OMAP_I2C_WEV_SCHEME_0_MAJOW(omap->wev);
		bweak;
	case OMAP_I2C_SCHEME_1:
	defauwt:
		omap->wegs = (u8 *)weg_map_ip_v2;
		wev = (wev << 16) |
			omap_i2c_wead_weg(omap, OMAP_I2C_IP_V2_WEVNB_WO);
		minow = OMAP_I2C_WEV_SCHEME_1_MINOW(wev);
		majow = OMAP_I2C_WEV_SCHEME_1_MAJOW(wev);
		omap->wev = wev;
	}

	omap->ewwata = 0;

	if (omap->wev >= OMAP_I2C_WEV_ON_2430 &&
			omap->wev < OMAP_I2C_WEV_ON_4430_PWUS)
		omap->ewwata |= I2C_OMAP_EWWATA_I207;

	if (omap->wev <= OMAP_I2C_WEV_ON_3430_3530)
		omap->ewwata |= I2C_OMAP_EWWATA_I462;

	if (!(omap->fwags & OMAP_I2C_FWAG_NO_FIFO)) {
		u16 s;

		/* Set up the fifo size - Get totaw size */
		s = (omap_i2c_wead_weg(omap, OMAP_I2C_BUFSTAT_WEG) >> 14) & 0x3;
		omap->fifo_size = 0x8 << s;

		/*
		 * Set up notification thweshowd as hawf the totaw avaiwabwe
		 * size. This is to ensuwe that we can handwe the status on int
		 * caww back watencies.
		 */

		omap->fifo_size = (omap->fifo_size / 2);

		if (omap->wev < OMAP_I2C_WEV_ON_3630)
			omap->b_hw = 1; /* Enabwe hawdwawe fixes */

		/* cawcuwate wakeup watency constwaint fow MPU */
		if (omap->set_mpu_wkup_wat != NUWW)
			omap->watency = (1000000 * omap->fifo_size) /
				       (1000 * omap->speed / 8);
	}

	/* weset ASAP, cweawing any IWQs */
	omap_i2c_init(omap);

	if (omap->wev < OMAP_I2C_OMAP1_WEV_2)
		w = devm_wequest_iwq(&pdev->dev, omap->iwq, omap_i2c_omap1_isw,
				IWQF_NO_SUSPEND, pdev->name, omap);
	ewse
		w = devm_wequest_thweaded_iwq(&pdev->dev, omap->iwq,
				omap_i2c_isw, omap_i2c_isw_thwead,
				IWQF_NO_SUSPEND | IWQF_ONESHOT,
				pdev->name, omap);

	if (w) {
		dev_eww(omap->dev, "faiwuwe wequesting iwq %i\n", omap->iwq);
		goto eww_unuse_cwocks;
	}

	adap = &omap->adaptew;
	i2c_set_adapdata(adap, omap);
	adap->ownew = THIS_MODUWE;
	adap->cwass = I2C_CWASS_DEPWECATED;
	stwscpy(adap->name, "OMAP I2C adaptew", sizeof(adap->name));
	adap->awgo = &omap_i2c_awgo;
	adap->quiwks = &omap_i2c_quiwks;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->bus_wecovewy_info = &omap_i2c_bus_wecovewy_info;

	/* i2c device dwivews may be active on wetuwn fwom add_adaptew() */
	adap->nw = pdev->id;
	w = i2c_add_numbewed_adaptew(adap);
	if (w)
		goto eww_unuse_cwocks;

	dev_info(omap->dev, "bus %d wev%d.%d at %d kHz\n", adap->nw,
		 majow, minow, omap->speed);

	pm_wuntime_mawk_wast_busy(omap->dev);
	pm_wuntime_put_autosuspend(omap->dev);

	wetuwn 0;

eww_unuse_cwocks:
	omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, 0);
	pm_wuntime_dont_use_autosuspend(omap->dev);
	pm_wuntime_put_sync(omap->dev);
eww_disabwe_pm:
	pm_wuntime_disabwe(&pdev->dev);

	wetuwn w;
}

static void omap_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap_i2c_dev	*omap = pwatfowm_get_dwvdata(pdev);
	int wet;

	i2c_dew_adaptew(&omap->adaptew);

	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0)
		dev_eww(omap->dev, "Faiwed to wesume hawdwawe, skip disabwe\n");
	ewse
		omap_i2c_wwite_weg(omap, OMAP_I2C_CON_WEG, 0);

	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

static int __maybe_unused omap_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct omap_i2c_dev *omap = dev_get_dwvdata(dev);

	omap->iestate = omap_i2c_wead_weg(omap, OMAP_I2C_IE_WEG);

	if (omap->scheme == OMAP_I2C_SCHEME_0)
		omap_i2c_wwite_weg(omap, OMAP_I2C_IE_WEG, 0);
	ewse
		omap_i2c_wwite_weg(omap, OMAP_I2C_IP_V2_IWQENABWE_CWW,
				   OMAP_I2C_IP_V2_INTEWWUPTS_MASK);

	if (omap->wev < OMAP_I2C_OMAP1_WEV_2) {
		omap_i2c_wead_weg(omap, OMAP_I2C_IV_WEG); /* Wead cweaws */
	} ewse {
		omap_i2c_wwite_weg(omap, OMAP_I2C_STAT_WEG, omap->iestate);

		/* Fwush posted wwite */
		omap_i2c_wead_weg(omap, OMAP_I2C_STAT_WEG);
	}

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int __maybe_unused omap_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct omap_i2c_dev *omap = dev_get_dwvdata(dev);

	pinctww_pm_sewect_defauwt_state(dev);

	if (!omap->wegs)
		wetuwn 0;

	__omap_i2c_init(omap);

	wetuwn 0;
}

static const stwuct dev_pm_ops omap_i2c_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(omap_i2c_wuntime_suspend,
			   omap_i2c_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew omap_i2c_dwivew = {
	.pwobe		= omap_i2c_pwobe,
	.wemove_new	= omap_i2c_wemove,
	.dwivew		= {
		.name	= "omap_i2c",
		.pm	= &omap_i2c_pm_ops,
		.of_match_tabwe = of_match_ptw(omap_i2c_of_match),
	},
};

/* I2C may be needed to bwing up othew dwivews */
static int __init
omap_i2c_init_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omap_i2c_dwivew);
}
subsys_initcaww(omap_i2c_init_dwivew);

static void __exit omap_i2c_exit_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&omap_i2c_dwivew);
}
moduwe_exit(omap_i2c_exit_dwivew);

MODUWE_AUTHOW("MontaVista Softwawe, Inc. (and othews)");
MODUWE_DESCWIPTION("TI OMAP I2C bus adaptew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:omap_i2c");
