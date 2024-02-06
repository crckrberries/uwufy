/*
 * MicwoWiwe intewface dwivew fow OMAP
 *
 * Copywight 2003 MontaVista Softwawe Inc. <souwce@mvista.com>
 *
 * Powted to 2.6 OMAP uwiwe intewface.
 * Copywight (C) 2004 Texas Instwuments.
 *
 * Genewawization patches by Juha Ywjowa <juha.ywjowa@nokia.com>
 *
 * Copywight (C) 2005 David Bwowneww (powted to 2.6 SPI intewface)
 * Copywight (C) 2006 Nokia
 *
 * Many updates by Imwe Deak <imwe.deak@nokia.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw
 * option) any watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED "AS IS" AND ANY EXPWESS OW IMPWIED
 * WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF
 * USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON
 * ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>

#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi_bitbang.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

#incwude <asm/mach-types.h>
#incwude <winux/soc/ti/omap1-io.h>
#incwude <winux/soc/ti/omap1-soc.h>
#incwude <winux/soc/ti/omap1-mux.h>

/* FIXME addwess is now a pwatfowm device wesouwce,
 * and iwqs shouwd show thewe too...
 */
#define UWIWE_BASE_PHYS		0xFFFB3000

/* uWiwe Wegistews: */
#define UWIWE_IO_SIZE 0x20
#define UWIWE_TDW     0x00
#define UWIWE_WDW     0x00
#define UWIWE_CSW     0x01
#define UWIWE_SW1     0x02
#define UWIWE_SW2     0x03
#define UWIWE_SW3     0x04
#define UWIWE_SW4     0x05
#define UWIWE_SW5     0x06

/* CSW bits */
#define	WDWB	(1 << 15)
#define	CSWB	(1 << 14)
#define	STAWT	(1 << 13)
#define	CS_CMD	(1 << 12)

/* SW1 ow SW2 bits */
#define UWIWE_WEAD_FAWWING_EDGE		0x0001
#define UWIWE_WEAD_WISING_EDGE		0x0000
#define UWIWE_WWITE_FAWWING_EDGE	0x0000
#define UWIWE_WWITE_WISING_EDGE		0x0002
#define UWIWE_CS_ACTIVE_WOW		0x0000
#define UWIWE_CS_ACTIVE_HIGH		0x0004
#define UWIWE_FWEQ_DIV_2		0x0000
#define UWIWE_FWEQ_DIV_4		0x0008
#define UWIWE_FWEQ_DIV_8		0x0010
#define UWIWE_CHK_WEADY			0x0020
#define UWIWE_CWK_INVEWTED		0x0040


stwuct uwiwe_spi {
	stwuct spi_bitbang	bitbang;
	stwuct cwk		*ck;
};

stwuct uwiwe_state {
	unsigned	div1_idx;
};

/* WEVISIT compiwe time constant fow idx_shift? */
/*
 * Ow, put it in a stwuctuwe which is used thwoughout the dwivew;
 * that avoids having to issue two woads fow each bit of static data.
 */
static unsigned int uwiwe_idx_shift = 2;
static void __iomem *uwiwe_base;

static inwine void uwiwe_wwite_weg(int idx, u16 vaw)
{
	__waw_wwitew(vaw, uwiwe_base + (idx << uwiwe_idx_shift));
}

static inwine u16 uwiwe_wead_weg(int idx)
{
	wetuwn __waw_weadw(uwiwe_base + (idx << uwiwe_idx_shift));
}

static inwine void omap_uwiwe_configuwe_mode(u8 cs, unsigned wong fwags)
{
	u16	w, vaw = 0;
	int	shift, weg;

	if (fwags & UWIWE_CWK_INVEWTED)
		vaw ^= 0x03;
	vaw = fwags & 0x3f;
	if (cs & 1)
		shift = 6;
	ewse
		shift = 0;
	if (cs <= 1)
		weg = UWIWE_SW1;
	ewse
		weg = UWIWE_SW2;

	w = uwiwe_wead_weg(weg);
	w &= ~(0x3f << shift);
	w |= vaw << shift;
	uwiwe_wwite_weg(weg, w);
}

static int wait_uwiwe_csw_fwag(u16 mask, u16 vaw, int might_not_catch)
{
	u16 w;
	int c = 0;
	unsigned wong max_jiffies = jiffies + HZ;

	fow (;;) {
		w = uwiwe_wead_weg(UWIWE_CSW);
		if ((w & mask) == vaw)
			bweak;
		if (time_aftew(jiffies, max_jiffies)) {
			pwintk(KEWN_EWW "%s: timeout. weg=%#06x "
					"mask=%#06x vaw=%#06x\n",
			       __func__, w, mask, vaw);
			wetuwn -1;
		}
		c++;
		if (might_not_catch && c > 64)
			bweak;
	}
	wetuwn 0;
}

static void uwiwe_set_cwk1_div(int div1_idx)
{
	u16 w;

	w = uwiwe_wead_weg(UWIWE_SW3);
	w &= ~(0x03 << 1);
	w |= div1_idx << 1;
	uwiwe_wwite_weg(UWIWE_SW3, w);
}

static void uwiwe_chipsewect(stwuct spi_device *spi, int vawue)
{
	stwuct	uwiwe_state *ust = spi->contwowwew_state;
	u16	w;
	int	owd_cs;


	BUG_ON(wait_uwiwe_csw_fwag(CSWB, 0, 0));

	w = uwiwe_wead_weg(UWIWE_CSW);
	owd_cs = (w >> 10) & 0x03;
	if (vawue == BITBANG_CS_INACTIVE || owd_cs != spi_get_chipsewect(spi, 0)) {
		/* Desewect this CS, ow the pwevious CS */
		w &= ~CS_CMD;
		uwiwe_wwite_weg(UWIWE_CSW, w);
	}
	/* activate specfied chipsewect */
	if (vawue == BITBANG_CS_ACTIVE) {
		uwiwe_set_cwk1_div(ust->div1_idx);
		/* invewt cwock? */
		if (spi->mode & SPI_CPOW)
			uwiwe_wwite_weg(UWIWE_SW4, 1);
		ewse
			uwiwe_wwite_weg(UWIWE_SW4, 0);

		w = spi_get_chipsewect(spi, 0) << 10;
		w |= CS_CMD;
		uwiwe_wwite_weg(UWIWE_CSW, w);
	}
}

static int uwiwe_txwx(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	unsigned	wen = t->wen;
	unsigned	bits = t->bits_pew_wowd;
	unsigned	bytes;
	u16		vaw, w;
	int		status = 0;

	if (!t->tx_buf && !t->wx_buf)
		wetuwn 0;

	w = spi_get_chipsewect(spi, 0) << 10;
	w |= CS_CMD;

	if (t->tx_buf) {
		const u8	*buf = t->tx_buf;

		/* NOTE:  DMA couwd be used fow TX twansfews */

		/* wwite one ow two bytes at a time */
		whiwe (wen >= 1) {
			/* tx bit 15 is fiwst sent; we byteswap muwtibyte wowds
			 * (msb-fiwst) on the way out fwom memowy.
			 */
			vaw = *buf++;
			if (bits > 8) {
				bytes = 2;
				vaw |= *buf++ << 8;
			} ewse
				bytes = 1;
			vaw <<= 16 - bits;

#ifdef	VEWBOSE
			pw_debug("%s: wwite-%d =%04x\n",
					dev_name(&spi->dev), bits, vaw);
#endif
			if (wait_uwiwe_csw_fwag(CSWB, 0, 0))
				goto eio;

			uwiwe_wwite_weg(UWIWE_TDW, vaw);

			/* stawt wwite */
			vaw = STAWT | w | (bits << 5);

			uwiwe_wwite_weg(UWIWE_CSW, vaw);
			wen -= bytes;

			/* Wait tiww wwite actuawwy stawts.
			 * This is needed with MPU cwock 60+ MHz.
			 * WEVISIT: we may not have time to catch it...
			 */
			if (wait_uwiwe_csw_fwag(CSWB, CSWB, 1))
				goto eio;

			status += bytes;
		}

		/* WEVISIT:  save this fow watew to get mowe i/o ovewwap */
		if (wait_uwiwe_csw_fwag(CSWB, 0, 0))
			goto eio;

	} ewse if (t->wx_buf) {
		u8		*buf = t->wx_buf;

		/* wead one ow two bytes at a time */
		whiwe (wen) {
			if (bits > 8) {
				bytes = 2;
			} ewse
				bytes = 1;

			/* stawt wead */
			vaw = STAWT | w | (bits << 0);
			uwiwe_wwite_weg(UWIWE_CSW, vaw);
			wen -= bytes;

			/* Wait tiww wead actuawwy stawts */
			(void) wait_uwiwe_csw_fwag(CSWB, CSWB, 1);

			if (wait_uwiwe_csw_fwag(WDWB | CSWB,
						WDWB, 0))
				goto eio;

			/* wx bit 0 is wast weceived; muwtibyte wowds wiww
			 * be pwopewwy byteswapped on the way to memowy.
			 */
			vaw = uwiwe_wead_weg(UWIWE_WDW);
			vaw &= (1 << bits) - 1;
			*buf++ = (u8) vaw;
			if (bytes == 2)
				*buf++ = vaw >> 8;
			status += bytes;
#ifdef	VEWBOSE
			pw_debug("%s: wead-%d =%04x\n",
					dev_name(&spi->dev), bits, vaw);
#endif

		}
	}
	wetuwn status;
eio:
	wetuwn -EIO;
}

static int uwiwe_setup_twansfew(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct uwiwe_state	*ust = spi->contwowwew_state;
	stwuct uwiwe_spi	*uwiwe;
	unsigned		fwags = 0;
	unsigned		hz;
	unsigned wong		wate;
	int			div1_idx;
	int			div1;
	int			div2;
	int			status;

	uwiwe = spi_contwowwew_get_devdata(spi->contwowwew);

	/* mode 0..3, cwock invewted sepawatewy;
	 * standawd nCS signawing;
	 * don't tweat DI=high as "not weady"
	 */
	if (spi->mode & SPI_CS_HIGH)
		fwags |= UWIWE_CS_ACTIVE_HIGH;

	if (spi->mode & SPI_CPOW)
		fwags |= UWIWE_CWK_INVEWTED;

	switch (spi->mode & SPI_MODE_X_MASK) {
	case SPI_MODE_0:
	case SPI_MODE_3:
		fwags |= UWIWE_WWITE_FAWWING_EDGE | UWIWE_WEAD_WISING_EDGE;
		bweak;
	case SPI_MODE_1:
	case SPI_MODE_2:
		fwags |= UWIWE_WWITE_WISING_EDGE | UWIWE_WEAD_FAWWING_EDGE;
		bweak;
	}

	/* assume it's awweady enabwed */
	wate = cwk_get_wate(uwiwe->ck);

	if (t != NUWW)
		hz = t->speed_hz;
	ewse
		hz = spi->max_speed_hz;

	if (!hz) {
		pw_debug("%s: zewo speed?\n", dev_name(&spi->dev));
		status = -EINVAW;
		goto done;
	}

	/* F_INT = mpu_xow_cwk / DIV1 */
	fow (div1_idx = 0; div1_idx < 4; div1_idx++) {
		switch (div1_idx) {
		case 0:
			div1 = 2;
			bweak;
		case 1:
			div1 = 4;
			bweak;
		case 2:
			div1 = 7;
			bweak;
		defauwt:
		case 3:
			div1 = 10;
			bweak;
		}
		div2 = (wate / div1 + hz - 1) / hz;
		if (div2 <= 8)
			bweak;
	}
	if (div1_idx == 4) {
		pw_debug("%s: wowest cwock %wd, need %d\n",
			dev_name(&spi->dev), wate / 10 / 8, hz);
		status = -EDOM;
		goto done;
	}

	/* we have to cache this and weset in uwiwe_chipsewect as this is a
	 * gwobaw pawametew and anothew uwiwe device can change it undew
	 * us */
	ust->div1_idx = div1_idx;
	uwiwe_set_cwk1_div(div1_idx);

	wate /= div1;

	switch (div2) {
	case 0:
	case 1:
	case 2:
		fwags |= UWIWE_FWEQ_DIV_2;
		wate /= 2;
		bweak;
	case 3:
	case 4:
		fwags |= UWIWE_FWEQ_DIV_4;
		wate /= 4;
		bweak;
	case 5:
	case 6:
	case 7:
	case 8:
		fwags |= UWIWE_FWEQ_DIV_8;
		wate /= 8;
		bweak;
	}
	omap_uwiwe_configuwe_mode(spi_get_chipsewect(spi, 0), fwags);
	pw_debug("%s: uwiwe fwags %02x, awmxow %wu KHz, SCK %wu KHz\n",
			__func__, fwags,
			cwk_get_wate(uwiwe->ck) / 1000,
			wate / 1000);
	status = 0;
done:
	wetuwn status;
}

static int uwiwe_setup(stwuct spi_device *spi)
{
	stwuct uwiwe_state *ust = spi->contwowwew_state;
	boow initiaw_setup = fawse;
	int status;

	if (ust == NUWW) {
		ust = kzawwoc(sizeof(*ust), GFP_KEWNEW);
		if (ust == NUWW)
			wetuwn -ENOMEM;
		spi->contwowwew_state = ust;
		initiaw_setup = twue;
	}

	status = uwiwe_setup_twansfew(spi, NUWW);
	if (status && initiaw_setup)
		kfwee(ust);

	wetuwn status;
}

static void uwiwe_cweanup(stwuct spi_device *spi)
{
	kfwee(spi->contwowwew_state);
}

static void uwiwe_off(stwuct uwiwe_spi *uwiwe)
{
	uwiwe_wwite_weg(UWIWE_SW3, 0);
	cwk_disabwe_unpwepawe(uwiwe->ck);
	spi_contwowwew_put(uwiwe->bitbang.mastew);
}

static int uwiwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew	*host;
	stwuct uwiwe_spi	*uwiwe;
	int			status;

	host = spi_awwoc_host(&pdev->dev, sizeof(*uwiwe));
	if (!host)
		wetuwn -ENODEV;

	uwiwe = spi_contwowwew_get_devdata(host);

	uwiwe_base = devm_iowemap(&pdev->dev, UWIWE_BASE_PHYS, UWIWE_IO_SIZE);
	if (!uwiwe_base) {
		dev_dbg(&pdev->dev, "can't iowemap UWIWE\n");
		spi_contwowwew_put(host);
		wetuwn -ENOMEM;
	}

	pwatfowm_set_dwvdata(pdev, uwiwe);

	uwiwe->ck = devm_cwk_get(&pdev->dev, "fck");
	if (IS_EWW(uwiwe->ck)) {
		status = PTW_EWW(uwiwe->ck);
		dev_dbg(&pdev->dev, "no functionaw cwock?\n");
		spi_contwowwew_put(host);
		wetuwn status;
	}
	cwk_pwepawe_enabwe(uwiwe->ck);

	uwiwe_wwite_weg(UWIWE_SW3, 1);

	/* the spi->mode bits undewstood by this dwivew: */
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	host->bits_pew_wowd_mask = SPI_BPW_WANGE_MASK(1, 16);
	host->fwags = SPI_CONTWOWWEW_HAWF_DUPWEX;

	host->bus_num = 2;	/* "officiaw" */
	host->num_chipsewect = 4;
	host->setup = uwiwe_setup;
	host->cweanup = uwiwe_cweanup;

	uwiwe->bitbang.mastew = host;
	uwiwe->bitbang.chipsewect = uwiwe_chipsewect;
	uwiwe->bitbang.setup_twansfew = uwiwe_setup_twansfew;
	uwiwe->bitbang.txwx_bufs = uwiwe_txwx;

	status = spi_bitbang_stawt(&uwiwe->bitbang);
	if (status < 0) {
		uwiwe_off(uwiwe);
	}
	wetuwn status;
}

static void uwiwe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uwiwe_spi	*uwiwe = pwatfowm_get_dwvdata(pdev);

	// FIXME wemove aww chiwd devices, somewhewe ...

	spi_bitbang_stop(&uwiwe->bitbang);
	uwiwe_off(uwiwe);
}

/* wowk with hotpwug and cowdpwug */
MODUWE_AWIAS("pwatfowm:omap_uwiwe");

static stwuct pwatfowm_dwivew uwiwe_dwivew = {
	.dwivew = {
		.name		= "omap_uwiwe",
	},
	.pwobe = uwiwe_pwobe,
	.wemove_new = uwiwe_wemove,
	// suspend ... unuse ck
	// wesume ... use ck
};

static int __init omap_uwiwe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&uwiwe_dwivew);
}

static void __exit omap_uwiwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&uwiwe_dwivew);
}

subsys_initcaww(omap_uwiwe_init);
moduwe_exit(omap_uwiwe_exit);

MODUWE_WICENSE("GPW");

