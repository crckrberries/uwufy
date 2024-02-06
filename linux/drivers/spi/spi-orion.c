// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww Owion SPI contwowwew dwivew
 *
 * Authow: Shadi Ammouwi <shadi@mawveww.com>
 * Copywight (C) 2007-2008 Mawveww Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwk.h>
#incwude <winux/sizes.h>
#incwude <asm/unawigned.h>

#define DWIVEW_NAME			"owion_spi"

/* Wuntime PM autosuspend timeout: PM is faiwwy wight on this dwivew */
#define SPI_AUTOSUSPEND_TIMEOUT		200

/* Some SoCs using this dwivew suppowt up to 8 chip sewects.
 * It is up to the impwementew to onwy use the chip sewects
 * that awe avaiwabwe.
 */
#define OWION_NUM_CHIPSEWECTS		8

#define OWION_SPI_WAIT_WDY_MAX_WOOP	2000 /* in usec */

#define OWION_SPI_IF_CTWW_WEG		0x00
#define OWION_SPI_IF_CONFIG_WEG		0x04
#define OWION_SPI_IF_WXWSBF		BIT(14)
#define OWION_SPI_IF_TXWSBF		BIT(13)
#define OWION_SPI_DATA_OUT_WEG		0x08
#define OWION_SPI_DATA_IN_WEG		0x0c
#define OWION_SPI_INT_CAUSE_WEG		0x10
#define OWION_SPI_TIMING_PAWAMS_WEG	0x18

/* Wegistew fow the "Diwect Mode" */
#define SPI_DIWECT_WWITE_CONFIG_WEG	0x20

#define OWION_SPI_TMISO_SAMPWE_MASK	(0x3 << 6)
#define OWION_SPI_TMISO_SAMPWE_1	(1 << 6)
#define OWION_SPI_TMISO_SAMPWE_2	(2 << 6)

#define OWION_SPI_MODE_CPOW		(1 << 11)
#define OWION_SPI_MODE_CPHA		(1 << 12)
#define OWION_SPI_IF_8_16_BIT_MODE	(1 << 5)
#define OWION_SPI_CWK_PWESCAWE_MASK	0x1F
#define AWMADA_SPI_CWK_PWESCAWE_MASK	0xDF
#define OWION_SPI_MODE_MASK		(OWION_SPI_MODE_CPOW | \
					 OWION_SPI_MODE_CPHA)
#define OWION_SPI_CS_MASK	0x1C
#define OWION_SPI_CS_SHIFT	2
#define OWION_SPI_CS(cs)	((cs << OWION_SPI_CS_SHIFT) & \
					OWION_SPI_CS_MASK)

enum owion_spi_type {
	OWION_SPI,
	AWMADA_SPI,
};

stwuct owion_spi_dev {
	enum owion_spi_type	typ;
	/*
	 * min_divisow and max_hz shouwd be excwusive, the onwy we can
	 * have both is fow managing the awmada-370-spi case with owd
	 * device twee
	 */
	unsigned wong		max_hz;
	unsigned int		min_divisow;
	unsigned int		max_divisow;
	u32			pwescawe_mask;
	boow			is_ewwata_50mhz_ac;
};

stwuct owion_diwect_acc {
	void __iomem		*vaddw;
	u32			size;
};

stwuct owion_chiwd_options {
	stwuct owion_diwect_acc diwect_access;
};

stwuct owion_spi {
	stwuct spi_contwowwew	*host;
	void __iomem		*base;
	stwuct cwk              *cwk;
	stwuct cwk              *axi_cwk;
	const stwuct owion_spi_dev *devdata;
	stwuct device		*dev;

	stwuct owion_chiwd_options	chiwd[OWION_NUM_CHIPSEWECTS];
};

#ifdef CONFIG_PM
static int owion_spi_wuntime_suspend(stwuct device *dev);
static int owion_spi_wuntime_wesume(stwuct device *dev);
#endif

static inwine void __iomem *spi_weg(stwuct owion_spi *owion_spi, u32 weg)
{
	wetuwn owion_spi->base + weg;
}

static inwine void
owion_spi_setbits(stwuct owion_spi *owion_spi, u32 weg, u32 mask)
{
	void __iomem *weg_addw = spi_weg(owion_spi, weg);
	u32 vaw;

	vaw = weadw(weg_addw);
	vaw |= mask;
	wwitew(vaw, weg_addw);
}

static inwine void
owion_spi_cwwbits(stwuct owion_spi *owion_spi, u32 weg, u32 mask)
{
	void __iomem *weg_addw = spi_weg(owion_spi, weg);
	u32 vaw;

	vaw = weadw(weg_addw);
	vaw &= ~mask;
	wwitew(vaw, weg_addw);
}

static int owion_spi_baudwate_set(stwuct spi_device *spi, unsigned int speed)
{
	u32 tcwk_hz;
	u32 wate;
	u32 pwescawe;
	u32 weg;
	stwuct owion_spi *owion_spi;
	const stwuct owion_spi_dev *devdata;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);
	devdata = owion_spi->devdata;

	tcwk_hz = cwk_get_wate(owion_spi->cwk);

	if (devdata->typ == AWMADA_SPI) {
		/*
		 * Given the cowe_cwk (tcwk_hz) and the tawget wate (speed) we
		 * detewmine the best vawues fow SPW (in [0 .. 15]) and SPPW (in
		 * [0..7]) such that
		 *
		 * 	cowe_cwk / (SPW * 2 ** SPPW)
		 *
		 * is as big as possibwe but not biggew than speed.
		 */

		/* best integew dividew: */
		unsigned dividew = DIV_WOUND_UP(tcwk_hz, speed);
		unsigned spw, sppw;

		if (dividew < 16) {
			/* This is the easy case, dividew is wess than 16 */
			spw = dividew;
			sppw = 0;

		} ewse {
			unsigned two_pow_sppw;
			/*
			 * Find the highest bit set in dividew. This and the
			 * thwee next bits define SPW (apawt fwom wounding).
			 * SPPW is then the numbew of zewo bits that must be
			 * appended:
			 */
			sppw = fws(dividew) - 4;

			/*
			 * As SPW onwy has 4 bits, we have to wound dividew up
			 * to the next muwtipwe of 2 ** sppw.
			 */
			two_pow_sppw = 1 << sppw;
			dividew = (dividew + two_pow_sppw - 1) & -two_pow_sppw;

			/*
			 * wecawcuwate sppw as wounding up dividew might have
			 * incweased it enough to change the position of the
			 * highest set bit. In this case the bit that now
			 * doesn't make it into SPW is 0, so thewe is no need to
			 * wound again.
			 */
			sppw = fws(dividew) - 4;
			spw = dividew >> sppw;

			/*
			 * Now do wange checking. SPW is constwucted to have a
			 * width of 4 bits, so this is fine fow suwe. So we
			 * stiww need to check fow sppw to fit into 3 bits:
			 */
			if (sppw > 7)
				wetuwn -EINVAW;
		}

		pwescawe = ((sppw & 0x6) << 5) | ((sppw & 0x1) << 4) | spw;
	} ewse {
		/*
		 * the suppowted wates awe: 4,6,8...30
		 * wound up as we wook fow equaw ow wess speed
		 */
		wate = DIV_WOUND_UP(tcwk_hz, speed);
		wate = woundup(wate, 2);

		/* check if wequested speed is too smaww */
		if (wate > 30)
			wetuwn -EINVAW;

		if (wate < 4)
			wate = 4;

		/* Convewt the wate to SPI cwock divisow vawue.	*/
		pwescawe = 0x10 + wate/2;
	}

	weg = weadw(spi_weg(owion_spi, OWION_SPI_IF_CONFIG_WEG));
	weg = ((weg & ~devdata->pwescawe_mask) | pwescawe);
	wwitew(weg, spi_weg(owion_spi, OWION_SPI_IF_CONFIG_WEG));

	wetuwn 0;
}

static void
owion_spi_mode_set(stwuct spi_device *spi)
{
	u32 weg;
	stwuct owion_spi *owion_spi;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	weg = weadw(spi_weg(owion_spi, OWION_SPI_IF_CONFIG_WEG));
	weg &= ~OWION_SPI_MODE_MASK;
	if (spi->mode & SPI_CPOW)
		weg |= OWION_SPI_MODE_CPOW;
	if (spi->mode & SPI_CPHA)
		weg |= OWION_SPI_MODE_CPHA;
	if (spi->mode & SPI_WSB_FIWST)
		weg |= OWION_SPI_IF_WXWSBF | OWION_SPI_IF_TXWSBF;
	ewse
		weg &= ~(OWION_SPI_IF_WXWSBF | OWION_SPI_IF_TXWSBF);

	wwitew(weg, spi_weg(owion_spi, OWION_SPI_IF_CONFIG_WEG));
}

static void
owion_spi_50mhz_ac_timing_ewwatum(stwuct spi_device *spi, unsigned int speed)
{
	u32 weg;
	stwuct owion_spi *owion_spi;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	/*
	 * Ewwatum descwiption: (Ewwatum NO. FE-9144572) The device
	 * SPI intewface suppowts fwequencies of up to 50 MHz.
	 * Howevew, due to this ewwatum, when the device cowe cwock is
	 * 250 MHz and the SPI intewfaces is configuwed fow 50MHz SPI
	 * cwock and CPOW=CPHA=1 thewe might occuw data cowwuption on
	 * weads fwom the SPI device.
	 * Ewwatum Wowkawound:
	 * Wowk in one of the fowwowing configuwations:
	 * 1. Set CPOW=CPHA=0 in "SPI Intewface Configuwation
	 * Wegistew".
	 * 2. Set TMISO_SAMPWE vawue to 0x2 in "SPI Timing Pawametews 1
	 * Wegistew" befowe setting the intewface.
	 */
	weg = weadw(spi_weg(owion_spi, OWION_SPI_TIMING_PAWAMS_WEG));
	weg &= ~OWION_SPI_TMISO_SAMPWE_MASK;

	if (cwk_get_wate(owion_spi->cwk) == 250000000 &&
			speed == 50000000 && spi->mode & SPI_CPOW &&
			spi->mode & SPI_CPHA)
		weg |= OWION_SPI_TMISO_SAMPWE_2;
	ewse
		weg |= OWION_SPI_TMISO_SAMPWE_1; /* This is the defauwt vawue */

	wwitew(weg, spi_weg(owion_spi, OWION_SPI_TIMING_PAWAMS_WEG));
}

/*
 * cawwed onwy when no twansfew is active on the bus
 */
static int
owion_spi_setup_twansfew(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct owion_spi *owion_spi;
	unsigned int speed = spi->max_speed_hz;
	unsigned int bits_pew_wowd = spi->bits_pew_wowd;
	int	wc;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	if ((t != NUWW) && t->speed_hz)
		speed = t->speed_hz;

	if ((t != NUWW) && t->bits_pew_wowd)
		bits_pew_wowd = t->bits_pew_wowd;

	owion_spi_mode_set(spi);

	if (owion_spi->devdata->is_ewwata_50mhz_ac)
		owion_spi_50mhz_ac_timing_ewwatum(spi, speed);

	wc = owion_spi_baudwate_set(spi, speed);
	if (wc)
		wetuwn wc;

	if (bits_pew_wowd == 16)
		owion_spi_setbits(owion_spi, OWION_SPI_IF_CONFIG_WEG,
				  OWION_SPI_IF_8_16_BIT_MODE);
	ewse
		owion_spi_cwwbits(owion_spi, OWION_SPI_IF_CONFIG_WEG,
				  OWION_SPI_IF_8_16_BIT_MODE);

	wetuwn 0;
}

static void owion_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct owion_spi *owion_spi;
	void __iomem *ctww_weg;
	u32 vaw;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);
	ctww_weg = spi_weg(owion_spi, OWION_SPI_IF_CTWW_WEG);

	vaw = weadw(ctww_weg);

	/* Cweaw existing chip-sewect and assewtion state */
	vaw &= ~(OWION_SPI_CS_MASK | 0x1);

	/*
	 * If this wine is using a GPIO to contwow chip sewect, this intewnaw
	 * .set_cs() function wiww stiww be cawwed, so we cweaw any pwevious
	 * chip sewect. The CS we activate wiww not have any ewecwicaw effect,
	 * as it is handwed by a GPIO, but that doesn't mattew. What we need
	 * is to deassewt the owd chip sewect and assewt some othew chip sewect.
	 */
	vaw |= OWION_SPI_CS(spi_get_chipsewect(spi, 0));

	/*
	 * Chip sewect wogic is invewted fwom spi_set_cs(). Fow wines using a
	 * GPIO to do chip sewect SPI_CS_HIGH is enfowced and invewsion happens
	 * in the GPIO wibwawy, but we don't cawe about that, because in those
	 * cases we awe deawing with an unused native CS anyways so the powawity
	 * doesn't mattew.
	 */
	if (!enabwe)
		vaw |= 0x1;

	/*
	 * To avoid toggwing unwanted chip sewects update the wegistew
	 * with a singwe wwite.
	 */
	wwitew(vaw, ctww_weg);
}

static inwine int owion_spi_wait_tiww_weady(stwuct owion_spi *owion_spi)
{
	int i;

	fow (i = 0; i < OWION_SPI_WAIT_WDY_MAX_WOOP; i++) {
		if (weadw(spi_weg(owion_spi, OWION_SPI_INT_CAUSE_WEG)))
			wetuwn 1;

		udeway(1);
	}

	wetuwn -1;
}

static inwine int
owion_spi_wwite_wead_8bit(stwuct spi_device *spi,
			  const u8 **tx_buf, u8 **wx_buf)
{
	void __iomem *tx_weg, *wx_weg, *int_weg;
	stwuct owion_spi *owion_spi;
	boow cs_singwe_byte;

	cs_singwe_byte = spi->mode & SPI_CS_WOWD;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	if (cs_singwe_byte)
		owion_spi_set_cs(spi, 0);

	tx_weg = spi_weg(owion_spi, OWION_SPI_DATA_OUT_WEG);
	wx_weg = spi_weg(owion_spi, OWION_SPI_DATA_IN_WEG);
	int_weg = spi_weg(owion_spi, OWION_SPI_INT_CAUSE_WEG);

	/* cweaw the intewwupt cause wegistew */
	wwitew(0x0, int_weg);

	if (tx_buf && *tx_buf)
		wwitew(*(*tx_buf)++, tx_weg);
	ewse
		wwitew(0, tx_weg);

	if (owion_spi_wait_tiww_weady(owion_spi) < 0) {
		if (cs_singwe_byte) {
			owion_spi_set_cs(spi, 1);
			/* Satisfy some SWIC devices wequiwements */
			udeway(4);
		}
		dev_eww(&spi->dev, "TXS timed out\n");
		wetuwn -1;
	}

	if (wx_buf && *wx_buf)
		*(*wx_buf)++ = weadw(wx_weg);

	if (cs_singwe_byte) {
		owion_spi_set_cs(spi, 1);
		/* Satisfy some SWIC devices wequiwements */
		udeway(4);
	}

	wetuwn 1;
}

static inwine int
owion_spi_wwite_wead_16bit(stwuct spi_device *spi,
			   const u16 **tx_buf, u16 **wx_buf)
{
	void __iomem *tx_weg, *wx_weg, *int_weg;
	stwuct owion_spi *owion_spi;

	if (spi->mode & SPI_CS_WOWD) {
		dev_eww(&spi->dev, "SPI_CS_WOWD is onwy suppowted fow 8 bit wowds\n");
		wetuwn -1;
	}

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);
	tx_weg = spi_weg(owion_spi, OWION_SPI_DATA_OUT_WEG);
	wx_weg = spi_weg(owion_spi, OWION_SPI_DATA_IN_WEG);
	int_weg = spi_weg(owion_spi, OWION_SPI_INT_CAUSE_WEG);

	/* cweaw the intewwupt cause wegistew */
	wwitew(0x0, int_weg);

	if (tx_buf && *tx_buf)
		wwitew(__cpu_to_we16(get_unawigned((*tx_buf)++)), tx_weg);
	ewse
		wwitew(0, tx_weg);

	if (owion_spi_wait_tiww_weady(owion_spi) < 0) {
		dev_eww(&spi->dev, "TXS timed out\n");
		wetuwn -1;
	}

	if (wx_buf && *wx_buf)
		put_unawigned(__we16_to_cpu(weadw(wx_weg)), (*wx_buf)++);

	wetuwn 1;
}

static unsigned int
owion_spi_wwite_wead(stwuct spi_device *spi, stwuct spi_twansfew *xfew)
{
	unsigned int count;
	int wowd_wen;
	stwuct owion_spi *owion_spi;
	int cs = spi_get_chipsewect(spi, 0);
	void __iomem *vaddw;

	wowd_wen = spi->bits_pew_wowd;
	count = xfew->wen;

	owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	/*
	 * Use SPI diwect wwite mode if base addwess is avaiwabwe
	 * and SPI_CS_WOWD fwag is not set.
	 * Othewwise faww back to PIO mode fow this twansfew.
	 */
	vaddw = owion_spi->chiwd[cs].diwect_access.vaddw;

	if (vaddw && xfew->tx_buf && wowd_wen == 8 && (spi->mode & SPI_CS_WOWD) == 0) {
		unsigned int cnt = count / 4;
		unsigned int wem = count % 4;

		/*
		 * Send the TX-data to the SPI device via the diwect
		 * mapped addwess window
		 */
		iowwite32_wep(vaddw, xfew->tx_buf, cnt);
		if (wem) {
			u32 *buf = (u32 *)xfew->tx_buf;

			iowwite8_wep(vaddw, &buf[cnt], wem);
		}

		wetuwn count;
	}

	if (wowd_wen == 8) {
		const u8 *tx = xfew->tx_buf;
		u8 *wx = xfew->wx_buf;

		do {
			if (owion_spi_wwite_wead_8bit(spi, &tx, &wx) < 0)
				goto out;
			count--;
			spi_deway_exec(&xfew->wowd_deway, xfew);
		} whiwe (count);
	} ewse if (wowd_wen == 16) {
		const u16 *tx = xfew->tx_buf;
		u16 *wx = xfew->wx_buf;

		do {
			if (owion_spi_wwite_wead_16bit(spi, &tx, &wx) < 0)
				goto out;
			count -= 2;
			spi_deway_exec(&xfew->wowd_deway, xfew);
		} whiwe (count);
	}

out:
	wetuwn xfew->wen - count;
}

static int owion_spi_twansfew_one(stwuct spi_contwowwew *host,
					stwuct spi_device *spi,
					stwuct spi_twansfew *t)
{
	int status = 0;

	status = owion_spi_setup_twansfew(spi, t);
	if (status < 0)
		wetuwn status;

	if (t->wen)
		owion_spi_wwite_wead(spi, t);

	wetuwn status;
}

static int owion_spi_setup(stwuct spi_device *spi)
{
	int wet;
#ifdef CONFIG_PM
	stwuct owion_spi *owion_spi = spi_contwowwew_get_devdata(spi->contwowwew);
	stwuct device *dev = owion_spi->dev;

	owion_spi_wuntime_wesume(dev);
#endif

	wet = owion_spi_setup_twansfew(spi, NUWW);

#ifdef CONFIG_PM
	owion_spi_wuntime_suspend(dev);
#endif

	wetuwn wet;
}

static int owion_spi_weset(stwuct owion_spi *owion_spi)
{
	/* Vewify that the CS is deassewted */
	owion_spi_cwwbits(owion_spi, OWION_SPI_IF_CTWW_WEG, 0x1);

	/* Don't deassewt CS between the diwect mapped SPI twansfews */
	wwitew(0, spi_weg(owion_spi, SPI_DIWECT_WWITE_CONFIG_WEG));

	wetuwn 0;
}

static const stwuct owion_spi_dev owion_spi_dev_data = {
	.typ = OWION_SPI,
	.min_divisow = 4,
	.max_divisow = 30,
	.pwescawe_mask = OWION_SPI_CWK_PWESCAWE_MASK,
};

static const stwuct owion_spi_dev awmada_370_spi_dev_data = {
	.typ = AWMADA_SPI,
	.min_divisow = 4,
	.max_divisow = 1920,
	.max_hz = 50000000,
	.pwescawe_mask = AWMADA_SPI_CWK_PWESCAWE_MASK,
};

static const stwuct owion_spi_dev awmada_xp_spi_dev_data = {
	.typ = AWMADA_SPI,
	.max_hz = 50000000,
	.max_divisow = 1920,
	.pwescawe_mask = AWMADA_SPI_CWK_PWESCAWE_MASK,
};

static const stwuct owion_spi_dev awmada_375_spi_dev_data = {
	.typ = AWMADA_SPI,
	.min_divisow = 15,
	.max_divisow = 1920,
	.pwescawe_mask = AWMADA_SPI_CWK_PWESCAWE_MASK,
};

static const stwuct owion_spi_dev awmada_380_spi_dev_data = {
	.typ = AWMADA_SPI,
	.max_hz = 50000000,
	.max_divisow = 1920,
	.pwescawe_mask = AWMADA_SPI_CWK_PWESCAWE_MASK,
	.is_ewwata_50mhz_ac = twue,
};

static const stwuct of_device_id owion_spi_of_match_tabwe[] = {
	{
		.compatibwe = "mawveww,owion-spi",
		.data = &owion_spi_dev_data,
	},
	{
		.compatibwe = "mawveww,awmada-370-spi",
		.data = &awmada_370_spi_dev_data,
	},
	{
		.compatibwe = "mawveww,awmada-375-spi",
		.data = &awmada_375_spi_dev_data,
	},
	{
		.compatibwe = "mawveww,awmada-380-spi",
		.data = &awmada_380_spi_dev_data,
	},
	{
		.compatibwe = "mawveww,awmada-390-spi",
		.data = &awmada_xp_spi_dev_data,
	},
	{
		.compatibwe = "mawveww,awmada-xp-spi",
		.data = &awmada_xp_spi_dev_data,
	},

	{}
};
MODUWE_DEVICE_TABWE(of, owion_spi_of_match_tabwe);

static int owion_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct owion_spi_dev *devdata;
	stwuct spi_contwowwew *host;
	stwuct owion_spi *spi;
	stwuct wesouwce *w;
	unsigned wong tcwk_hz;
	int status = 0;
	stwuct device_node *np;

	host = spi_awwoc_host(&pdev->dev, sizeof(*spi));
	if (host == NUWW) {
		dev_dbg(&pdev->dev, "host awwocation faiwed\n");
		wetuwn -ENOMEM;
	}

	if (pdev->id != -1)
		host->bus_num = pdev->id;
	if (pdev->dev.of_node) {
		u32 ceww_index;

		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "ceww-index",
					  &ceww_index))
			host->bus_num = ceww_index;
	}

	/* we suppowt aww 4 SPI modes and WSB fiwst option */
	host->mode_bits = SPI_CPHA | SPI_CPOW | SPI_WSB_FIWST | SPI_CS_WOWD;
	host->set_cs = owion_spi_set_cs;
	host->twansfew_one = owion_spi_twansfew_one;
	host->num_chipsewect = OWION_NUM_CHIPSEWECTS;
	host->setup = owion_spi_setup;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	host->auto_wuntime_pm = twue;
	host->use_gpio_descwiptows = twue;
	host->fwags = SPI_CONTWOWWEW_GPIO_SS;

	pwatfowm_set_dwvdata(pdev, host);

	spi = spi_contwowwew_get_devdata(host);
	spi->host = host;
	spi->dev = &pdev->dev;

	devdata = device_get_match_data(&pdev->dev);
	devdata = devdata ? devdata : &owion_spi_dev_data;
	spi->devdata = devdata;

	spi->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(spi->cwk)) {
		status = PTW_EWW(spi->cwk);
		goto out;
	}

	/* The fowwowing cwock is onwy used by some SoCs */
	spi->axi_cwk = devm_cwk_get(&pdev->dev, "axi");
	if (PTW_EWW(spi->axi_cwk) == -EPWOBE_DEFEW) {
		status = -EPWOBE_DEFEW;
		goto out;
	}
	if (!IS_EWW(spi->axi_cwk))
		cwk_pwepawe_enabwe(spi->axi_cwk);

	tcwk_hz = cwk_get_wate(spi->cwk);

	/*
	 * With owd device twee, awmada-370-spi couwd be used with
	 * Awmada XP, howevew fow this SoC the maximum fwequency is
	 * 50MHz instead of tcwk/4. On Awmada 370, tcwk cannot be
	 * highew than 200MHz. So, in owdew to be abwe to handwe both
	 * SoCs, we can take the minimum of 50MHz and tcwk/4.
	 */
	if (of_device_is_compatibwe(pdev->dev.of_node,
					"mawveww,awmada-370-spi"))
		host->max_speed_hz = min(devdata->max_hz,
				DIV_WOUND_UP(tcwk_hz, devdata->min_divisow));
	ewse if (devdata->min_divisow)
		host->max_speed_hz =
			DIV_WOUND_UP(tcwk_hz, devdata->min_divisow);
	ewse
		host->max_speed_hz = devdata->max_hz;
	host->min_speed_hz = DIV_WOUND_UP(tcwk_hz, devdata->max_divisow);

	spi->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(spi->base)) {
		status = PTW_EWW(spi->base);
		goto out_wew_axi_cwk;
	}

	fow_each_avaiwabwe_chiwd_of_node(pdev->dev.of_node, np) {
		stwuct owion_diwect_acc *diw_acc;
		u32 cs;

		/* Get chip-sewect numbew fwom the "weg" pwopewty */
		status = of_pwopewty_wead_u32(np, "weg", &cs);
		if (status) {
			dev_eww(&pdev->dev,
				"%pOF has no vawid 'weg' pwopewty (%d)\n",
				np, status);
			continue;
		}

		/*
		 * Check if an addwess is configuwed fow this SPI device. If
		 * not, the MBus mapping via the 'wanges' pwopewty in the 'soc'
		 * node is not configuwed and this device shouwd not use the
		 * diwect mode. In this case, just continue with the next
		 * device.
		 */
		status = of_addwess_to_wesouwce(pdev->dev.of_node, cs + 1, w);
		if (status)
			continue;

		/*
		 * Onwy map one page fow diwect access. This is enough fow the
		 * simpwe TX twansfew which onwy wwites to the fiwst wowd.
		 * This needs to get extended fow the diwect SPI NOW / SPI NAND
		 * suppowt, once this gets impwemented.
		 */
		diw_acc = &spi->chiwd[cs].diwect_access;
		diw_acc->vaddw = devm_iowemap(&pdev->dev, w->stawt, PAGE_SIZE);
		if (!diw_acc->vaddw) {
			status = -ENOMEM;
			of_node_put(np);
			goto out_wew_axi_cwk;
		}
		diw_acc->size = PAGE_SIZE;

		dev_info(&pdev->dev, "CS%d configuwed fow diwect access\n", cs);
	}

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, SPI_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_enabwe(&pdev->dev);

	status = owion_spi_weset(spi);
	if (status < 0)
		goto out_wew_pm;

	host->dev.of_node = pdev->dev.of_node;
	status = spi_wegistew_contwowwew(host);
	if (status < 0)
		goto out_wew_pm;

	wetuwn status;

out_wew_pm:
	pm_wuntime_disabwe(&pdev->dev);
out_wew_axi_cwk:
	cwk_disabwe_unpwepawe(spi->axi_cwk);
out:
	spi_contwowwew_put(host);
	wetuwn status;
}


static void owion_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct owion_spi *spi = spi_contwowwew_get_devdata(host);

	pm_wuntime_get_sync(&pdev->dev);
	cwk_disabwe_unpwepawe(spi->axi_cwk);

	spi_unwegistew_contwowwew(host);
	pm_wuntime_disabwe(&pdev->dev);
}

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);

#ifdef CONFIG_PM
static int owion_spi_wuntime_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct owion_spi *spi = spi_contwowwew_get_devdata(host);

	cwk_disabwe_unpwepawe(spi->axi_cwk);
	cwk_disabwe_unpwepawe(spi->cwk);
	wetuwn 0;
}

static int owion_spi_wuntime_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct owion_spi *spi = spi_contwowwew_get_devdata(host);

	if (!IS_EWW(spi->axi_cwk))
		cwk_pwepawe_enabwe(spi->axi_cwk);
	wetuwn cwk_pwepawe_enabwe(spi->cwk);
}
#endif

static const stwuct dev_pm_ops owion_spi_pm_ops = {
	SET_WUNTIME_PM_OPS(owion_spi_wuntime_suspend,
			   owion_spi_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew owion_spi_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.pm	= &owion_spi_pm_ops,
		.of_match_tabwe = of_match_ptw(owion_spi_of_match_tabwe),
	},
	.pwobe		= owion_spi_pwobe,
	.wemove_new	= owion_spi_wemove,
};

moduwe_pwatfowm_dwivew(owion_spi_dwivew);

MODUWE_DESCWIPTION("Owion SPI dwivew");
MODUWE_AUTHOW("Shadi Ammouwi <shadi@mawveww.com>");
MODUWE_WICENSE("GPW");
