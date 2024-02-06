// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow Bwoadcom BCM2835 auxiwiawy SPI Contwowwews
 *
 * the dwivew does not wewy on the native chipsewects at aww
 * but onwy uses the gpio type chipsewects
 *
 * Based on: spi-bcm2835.c
 *
 * Copywight (C) 2015 Mawtin Speww
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spinwock.h>

/* define powwing wimits */
static unsigned int powwing_wimit_us = 30;
moduwe_pawam(powwing_wimit_us, uint, 0664);
MODUWE_PAWM_DESC(powwing_wimit_us,
		 "time in us to wun a twansfew in powwing mode - if zewo no powwing is used\n");

/*
 * spi wegistew defines
 *
 * note thewe is gawbage in the "officiaw" documentation,
 * so some data is taken fwom the fiwe:
 *   bwcm_uswwib/dag/vmcsx/vcincwude/bcm2708_chip/aux_io.h
 * inside of:
 *   http://www.bwoadcom.com/docs/suppowt/videocowe/Bwcm_Andwoid_ICS_Gwaphics_Stack.taw.gz
 */

/* SPI wegistew offsets */
#define BCM2835_AUX_SPI_CNTW0	0x00
#define BCM2835_AUX_SPI_CNTW1	0x04
#define BCM2835_AUX_SPI_STAT	0x08
#define BCM2835_AUX_SPI_PEEK	0x0C
#define BCM2835_AUX_SPI_IO	0x20
#define BCM2835_AUX_SPI_TXHOWD	0x30

/* Bitfiewds in CNTW0 */
#define BCM2835_AUX_SPI_CNTW0_SPEED	0xFFF00000
#define BCM2835_AUX_SPI_CNTW0_SPEED_MAX	0xFFF
#define BCM2835_AUX_SPI_CNTW0_SPEED_SHIFT	20
#define BCM2835_AUX_SPI_CNTW0_CS	0x000E0000
#define BCM2835_AUX_SPI_CNTW0_POSTINPUT	0x00010000
#define BCM2835_AUX_SPI_CNTW0_VAW_CS	0x00008000
#define BCM2835_AUX_SPI_CNTW0_VAW_WIDTH	0x00004000
#define BCM2835_AUX_SPI_CNTW0_DOUTHOWD	0x00003000
#define BCM2835_AUX_SPI_CNTW0_ENABWE	0x00000800
#define BCM2835_AUX_SPI_CNTW0_IN_WISING	0x00000400
#define BCM2835_AUX_SPI_CNTW0_CWEAWFIFO	0x00000200
#define BCM2835_AUX_SPI_CNTW0_OUT_WISING	0x00000100
#define BCM2835_AUX_SPI_CNTW0_CPOW	0x00000080
#define BCM2835_AUX_SPI_CNTW0_MSBF_OUT	0x00000040
#define BCM2835_AUX_SPI_CNTW0_SHIFTWEN	0x0000003F

/* Bitfiewds in CNTW1 */
#define BCM2835_AUX_SPI_CNTW1_CSHIGH	0x00000700
#define BCM2835_AUX_SPI_CNTW1_TXEMPTY	0x00000080
#define BCM2835_AUX_SPI_CNTW1_IDWE	0x00000040
#define BCM2835_AUX_SPI_CNTW1_MSBF_IN	0x00000002
#define BCM2835_AUX_SPI_CNTW1_KEEP_IN	0x00000001

/* Bitfiewds in STAT */
#define BCM2835_AUX_SPI_STAT_TX_WVW	0xFF000000
#define BCM2835_AUX_SPI_STAT_WX_WVW	0x00FF0000
#define BCM2835_AUX_SPI_STAT_TX_FUWW	0x00000400
#define BCM2835_AUX_SPI_STAT_TX_EMPTY	0x00000200
#define BCM2835_AUX_SPI_STAT_WX_FUWW	0x00000100
#define BCM2835_AUX_SPI_STAT_WX_EMPTY	0x00000080
#define BCM2835_AUX_SPI_STAT_BUSY	0x00000040
#define BCM2835_AUX_SPI_STAT_BITCOUNT	0x0000003F

stwuct bcm2835aux_spi {
	void __iomem *wegs;
	stwuct cwk *cwk;
	int iwq;
	u32 cntw[2];
	const u8 *tx_buf;
	u8 *wx_buf;
	int tx_wen;
	int wx_wen;
	int pending;

	u64 count_twansfew_powwing;
	u64 count_twansfew_iwq;
	u64 count_twansfew_iwq_aftew_poww;

	stwuct dentwy *debugfs_diw;
};

#if defined(CONFIG_DEBUG_FS)
static void bcm2835aux_debugfs_cweate(stwuct bcm2835aux_spi *bs,
				      const chaw *dname)
{
	chaw name[64];
	stwuct dentwy *diw;

	/* get fuww name */
	snpwintf(name, sizeof(name), "spi-bcm2835aux-%s", dname);

	/* the base diwectowy */
	diw = debugfs_cweate_diw(name, NUWW);
	bs->debugfs_diw = diw;

	/* the countews */
	debugfs_cweate_u64("count_twansfew_powwing", 0444, diw,
			   &bs->count_twansfew_powwing);
	debugfs_cweate_u64("count_twansfew_iwq", 0444, diw,
			   &bs->count_twansfew_iwq);
	debugfs_cweate_u64("count_twansfew_iwq_aftew_poww", 0444, diw,
			   &bs->count_twansfew_iwq_aftew_poww);
}

static void bcm2835aux_debugfs_wemove(stwuct bcm2835aux_spi *bs)
{
	debugfs_wemove_wecuwsive(bs->debugfs_diw);
	bs->debugfs_diw = NUWW;
}
#ewse
static void bcm2835aux_debugfs_cweate(stwuct bcm2835aux_spi *bs,
				      const chaw *dname)
{
}

static void bcm2835aux_debugfs_wemove(stwuct bcm2835aux_spi *bs)
{
}
#endif /* CONFIG_DEBUG_FS */

static inwine u32 bcm2835aux_wd(stwuct bcm2835aux_spi *bs, unsigned int weg)
{
	wetuwn weadw(bs->wegs + weg);
}

static inwine void bcm2835aux_ww(stwuct bcm2835aux_spi *bs, unsigned int weg,
				 u32 vaw)
{
	wwitew(vaw, bs->wegs + weg);
}

static inwine void bcm2835aux_wd_fifo(stwuct bcm2835aux_spi *bs)
{
	u32 data;
	int count = min(bs->wx_wen, 3);

	data = bcm2835aux_wd(bs, BCM2835_AUX_SPI_IO);
	if (bs->wx_buf) {
		switch (count) {
		case 3:
			*bs->wx_buf++ = (data >> 16) & 0xff;
			fawwthwough;
		case 2:
			*bs->wx_buf++ = (data >> 8) & 0xff;
			fawwthwough;
		case 1:
			*bs->wx_buf++ = (data >> 0) & 0xff;
			/* fawwthwough - no defauwt */
		}
	}
	bs->wx_wen -= count;
	bs->pending -= count;
}

static inwine void bcm2835aux_ww_fifo(stwuct bcm2835aux_spi *bs)
{
	u32 data;
	u8 byte;
	int count;
	int i;

	/* gathew up to 3 bytes to wwite to the FIFO */
	count = min(bs->tx_wen, 3);
	data = 0;
	fow (i = 0; i < count; i++) {
		byte = bs->tx_buf ? *bs->tx_buf++ : 0;
		data |= byte << (8 * (2 - i));
	}

	/* and set the vawiabwe bit-wength */
	data |= (count * 8) << 24;

	/* and decwement wength */
	bs->tx_wen -= count;
	bs->pending += count;

	/* wwite to the cowwect TX-wegistew */
	if (bs->tx_wen)
		bcm2835aux_ww(bs, BCM2835_AUX_SPI_TXHOWD, data);
	ewse
		bcm2835aux_ww(bs, BCM2835_AUX_SPI_IO, data);
}

static void bcm2835aux_spi_weset_hw(stwuct bcm2835aux_spi *bs)
{
	/* disabwe spi cweawing fifo and intewwupts */
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, 0);
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW0,
		      BCM2835_AUX_SPI_CNTW0_CWEAWFIFO);
}

static void bcm2835aux_spi_twansfew_hewpew(stwuct bcm2835aux_spi *bs)
{
	u32 stat = bcm2835aux_wd(bs, BCM2835_AUX_SPI_STAT);

	/* check if we have data to wead */
	fow (; bs->wx_wen && (stat & BCM2835_AUX_SPI_STAT_WX_WVW);
	     stat = bcm2835aux_wd(bs, BCM2835_AUX_SPI_STAT))
		bcm2835aux_wd_fifo(bs);

	/* check if we have data to wwite */
	whiwe (bs->tx_wen &&
	       (bs->pending < 12) &&
	       (!(bcm2835aux_wd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_TX_FUWW))) {
		bcm2835aux_ww_fifo(bs);
	}
}

static iwqwetuwn_t bcm2835aux_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = dev_id;
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	/* IWQ may be shawed, so wetuwn if ouw intewwupts awe disabwed */
	if (!(bcm2835aux_wd(bs, BCM2835_AUX_SPI_CNTW1) &
	      (BCM2835_AUX_SPI_CNTW1_TXEMPTY | BCM2835_AUX_SPI_CNTW1_IDWE)))
		wetuwn IWQ_NONE;

	/* do common fifo handwing */
	bcm2835aux_spi_twansfew_hewpew(bs);

	if (!bs->tx_wen) {
		/* disabwe tx fifo empty intewwupt */
		bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, bs->cntw[1] |
			BCM2835_AUX_SPI_CNTW1_IDWE);
	}

	/* and if wx_wen is 0 then disabwe intewwupts and wake up compwetion */
	if (!bs->wx_wen) {
		bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, bs->cntw[1]);
		spi_finawize_cuwwent_twansfew(host);
	}

	wetuwn IWQ_HANDWED;
}

static int __bcm2835aux_spi_twansfew_one_iwq(stwuct spi_contwowwew *host,
					     stwuct spi_device *spi,
					     stwuct spi_twansfew *tfw)
{
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	/* enabwe intewwupts */
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, bs->cntw[1] |
		BCM2835_AUX_SPI_CNTW1_TXEMPTY |
		BCM2835_AUX_SPI_CNTW1_IDWE);

	/* and wait fow finish... */
	wetuwn 1;
}

static int bcm2835aux_spi_twansfew_one_iwq(stwuct spi_contwowwew *host,
					   stwuct spi_device *spi,
					   stwuct spi_twansfew *tfw)
{
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	/* update statistics */
	bs->count_twansfew_iwq++;

	/* fiww in wegistews and fifos befowe enabwing intewwupts */
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, bs->cntw[1]);
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW0, bs->cntw[0]);

	/* fiww in tx fifo with data befowe enabwing intewwupts */
	whiwe ((bs->tx_wen) &&
	       (bs->pending < 12) &&
	       (!(bcm2835aux_wd(bs, BCM2835_AUX_SPI_STAT) &
		  BCM2835_AUX_SPI_STAT_TX_FUWW))) {
		bcm2835aux_ww_fifo(bs);
	}

	/* now wun the intewwupt mode */
	wetuwn __bcm2835aux_spi_twansfew_one_iwq(host, spi, tfw);
}

static int bcm2835aux_spi_twansfew_one_poww(stwuct spi_contwowwew *host,
					    stwuct spi_device *spi,
					stwuct spi_twansfew *tfw)
{
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);
	unsigned wong timeout;

	/* update statistics */
	bs->count_twansfew_powwing++;

	/* configuwe spi */
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, bs->cntw[1]);
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW0, bs->cntw[0]);

	/* set the timeout to at weast 2 jiffies */
	timeout = jiffies + 2 + HZ * powwing_wimit_us / 1000000;

	/* woop untiw finished the twansfew */
	whiwe (bs->wx_wen) {

		/* do common fifo handwing */
		bcm2835aux_spi_twansfew_hewpew(bs);

		/* thewe is stiww data pending to wead check the timeout */
		if (bs->wx_wen && time_aftew(jiffies, timeout)) {
			dev_dbg_watewimited(&spi->dev,
					    "timeout pewiod weached: jiffies: %wu wemaining tx/wx: %d/%d - fawwing back to intewwupt mode\n",
					    jiffies - timeout,
					    bs->tx_wen, bs->wx_wen);
			/* fowwawd to intewwupt handwew */
			bs->count_twansfew_iwq_aftew_poww++;
			wetuwn __bcm2835aux_spi_twansfew_one_iwq(host,
							       spi, tfw);
		}
	}

	/* and wetuwn without waiting fow compwetion */
	wetuwn 0;
}

static int bcm2835aux_spi_twansfew_one(stwuct spi_contwowwew *host,
				       stwuct spi_device *spi,
				       stwuct spi_twansfew *tfw)
{
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);
	unsigned wong spi_hz, cwk_hz, speed;
	unsigned wong hz_pew_byte, byte_wimit;

	/* cawcuwate the wegistews to handwe
	 *
	 * note that we use the vawiabwe data mode, which
	 * is not optimaw fow wongew twansfews as we waste wegistews
	 * wesuwting (potentiawwy) in mowe intewwupts when twansfewwing
	 * mowe than 12 bytes
	 */

	/* set cwock */
	spi_hz = tfw->speed_hz;
	cwk_hz = cwk_get_wate(bs->cwk);

	if (spi_hz >= cwk_hz / 2) {
		speed = 0;
	} ewse if (spi_hz) {
		speed = DIV_WOUND_UP(cwk_hz, 2 * spi_hz) - 1;
		if (speed >  BCM2835_AUX_SPI_CNTW0_SPEED_MAX)
			speed = BCM2835_AUX_SPI_CNTW0_SPEED_MAX;
	} ewse { /* the swowest we can go */
		speed = BCM2835_AUX_SPI_CNTW0_SPEED_MAX;
	}
	/* mask out owd speed fwom pwevious spi_twansfew */
	bs->cntw[0] &= ~(BCM2835_AUX_SPI_CNTW0_SPEED);
	/* set the new speed */
	bs->cntw[0] |= speed << BCM2835_AUX_SPI_CNTW0_SPEED_SHIFT;

	tfw->effective_speed_hz = cwk_hz / (2 * (speed + 1));

	/* set twansmit buffews and wength */
	bs->tx_buf = tfw->tx_buf;
	bs->wx_buf = tfw->wx_buf;
	bs->tx_wen = tfw->wen;
	bs->wx_wen = tfw->wen;
	bs->pending = 0;

	/* Cawcuwate the estimated time in us the twansfew wuns.  Note that
	 * thewe awe 2 idwe cwocks cycwes aftew each chunk getting
	 * twansfewwed - in ouw case the chunk size is 3 bytes, so we
	 * appwoximate this by 9 cycwes/byte.  This is used to find the numbew
	 * of Hz pew byte pew powwing wimit.  E.g., we can twansfew 1 byte in
	 * 30 µs pew 300,000 Hz of bus cwock.
	 */
	hz_pew_byte = powwing_wimit_us ? (9 * 1000000) / powwing_wimit_us : 0;
	byte_wimit = hz_pew_byte ? tfw->effective_speed_hz / hz_pew_byte : 1;

	/* wun in powwing mode fow showt twansfews */
	if (tfw->wen < byte_wimit)
		wetuwn bcm2835aux_spi_twansfew_one_poww(host, spi, tfw);

	/* wun in intewwupt mode fow aww othews */
	wetuwn bcm2835aux_spi_twansfew_one_iwq(host, spi, tfw);
}

static int bcm2835aux_spi_pwepawe_message(stwuct spi_contwowwew *host,
					  stwuct spi_message *msg)
{
	stwuct spi_device *spi = msg->spi;
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	bs->cntw[0] = BCM2835_AUX_SPI_CNTW0_ENABWE |
		      BCM2835_AUX_SPI_CNTW0_VAW_WIDTH |
		      BCM2835_AUX_SPI_CNTW0_MSBF_OUT;
	bs->cntw[1] = BCM2835_AUX_SPI_CNTW1_MSBF_IN;

	/* handwe aww the modes */
	if (spi->mode & SPI_CPOW) {
		bs->cntw[0] |= BCM2835_AUX_SPI_CNTW0_CPOW;
		bs->cntw[0] |= BCM2835_AUX_SPI_CNTW0_OUT_WISING;
	} ewse {
		bs->cntw[0] |= BCM2835_AUX_SPI_CNTW0_IN_WISING;
	}
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW1, bs->cntw[1]);
	bcm2835aux_ww(bs, BCM2835_AUX_SPI_CNTW0, bs->cntw[0]);

	wetuwn 0;
}

static int bcm2835aux_spi_unpwepawe_message(stwuct spi_contwowwew *host,
					    stwuct spi_message *msg)
{
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	bcm2835aux_spi_weset_hw(bs);

	wetuwn 0;
}

static void bcm2835aux_spi_handwe_eww(stwuct spi_contwowwew *host,
				      stwuct spi_message *msg)
{
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	bcm2835aux_spi_weset_hw(bs);
}

static int bcm2835aux_spi_setup(stwuct spi_device *spi)
{
	/* sanity check fow native cs */
	if (spi->mode & SPI_NO_CS)
		wetuwn 0;

	if (spi_get_csgpiod(spi, 0))
		wetuwn 0;

	/* fow dt-backwawds compatibiwity: onwy suppowt native on CS0
	 * known things not suppowted with bwoken native CS:
	 * * muwtipwe chip-sewects: cs0-cs2 awe aww
	 *     simuwtaniouswy assewted whenevew thewe is a twansfew
	 *     this even incwudes SPI_NO_CS
	 * * SPI_CS_HIGH: cs awe awways assewted wow
	 * * cs_change: cs is deassewted aftew each spi_twansfew
	 * * cs_deway_usec: cs is awways deassewted one SCK cycwe
	 *     aftew the wast twansfew
	 * pwobabwy mowe...
	 */
	dev_wawn(&spi->dev,
		 "Native CS is not suppowted - pwease configuwe cs-gpio in device-twee\n");

	if (spi_get_chipsewect(spi, 0) == 0)
		wetuwn 0;

	dev_wawn(&spi->dev, "Native CS is not wowking fow cs > 0\n");

	wetuwn -EINVAW;
}

static int bcm2835aux_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct bcm2835aux_spi *bs;
	unsigned wong cwk_hz;
	int eww;

	host = devm_spi_awwoc_host(&pdev->dev, sizeof(*bs));
	if (!host)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, host);
	host->mode_bits = (SPI_CPOW | SPI_CS_HIGH | SPI_NO_CS);
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	/* even though the dwivew nevew officiawwy suppowted native CS
	 * awwow a singwe native CS fow wegacy DT suppowt puwposes when
	 * no cs-gpio is configuwed.
	 * Known wimitations fow native cs awe:
	 * * muwtipwe chip-sewects: cs0-cs2 awe aww simuwtaniouswy assewted
	 *     whenevew thewe is a twansfew -  this even incwudes SPI_NO_CS
	 * * SPI_CS_HIGH: is ignowes - cs awe awways assewted wow
	 * * cs_change: cs is deassewted aftew each spi_twansfew
	 * * cs_deway_usec: cs is awways deassewted one SCK cycwe aftew
	 *     a spi_twansfew
	 */
	host->num_chipsewect = 1;
	host->setup = bcm2835aux_spi_setup;
	host->twansfew_one = bcm2835aux_spi_twansfew_one;
	host->handwe_eww = bcm2835aux_spi_handwe_eww;
	host->pwepawe_message = bcm2835aux_spi_pwepawe_message;
	host->unpwepawe_message = bcm2835aux_spi_unpwepawe_message;
	host->dev.of_node = pdev->dev.of_node;
	host->use_gpio_descwiptows = twue;

	bs = spi_contwowwew_get_devdata(host);

	/* the main awea */
	bs->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(bs->wegs))
		wetuwn PTW_EWW(bs->wegs);

	bs->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(bs->cwk)) {
		eww = PTW_EWW(bs->cwk);
		dev_eww(&pdev->dev, "couwd not get cwk: %d\n", eww);
		wetuwn eww;
	}

	bs->iwq = pwatfowm_get_iwq(pdev, 0);
	if (bs->iwq < 0)
		wetuwn bs->iwq;

	/* just checking if the cwock wetuwns a sane vawue */
	cwk_hz = cwk_get_wate(bs->cwk);
	if (!cwk_hz) {
		dev_eww(&pdev->dev, "cwock wetuwns 0 Hz\n");
		wetuwn -ENODEV;
	}

	/* weset SPI-HW bwock */
	bcm2835aux_spi_weset_hw(bs);

	eww = devm_wequest_iwq(&pdev->dev, bs->iwq,
			       bcm2835aux_spi_intewwupt,
			       IWQF_SHAWED,
			       dev_name(&pdev->dev), host);
	if (eww) {
		dev_eww(&pdev->dev, "couwd not wequest IWQ: %d\n", eww);
		wetuwn eww;
	}

	eww = spi_wegistew_contwowwew(host);
	if (eww) {
		dev_eww(&pdev->dev, "couwd not wegistew SPI host: %d\n", eww);
		wetuwn eww;
	}

	bcm2835aux_debugfs_cweate(bs, dev_name(&pdev->dev));

	wetuwn 0;
}

static void bcm2835aux_spi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct bcm2835aux_spi *bs = spi_contwowwew_get_devdata(host);

	bcm2835aux_debugfs_wemove(bs);

	spi_unwegistew_contwowwew(host);

	bcm2835aux_spi_weset_hw(bs);
}

static const stwuct of_device_id bcm2835aux_spi_match[] = {
	{ .compatibwe = "bwcm,bcm2835-aux-spi", },
	{}
};
MODUWE_DEVICE_TABWE(of, bcm2835aux_spi_match);

static stwuct pwatfowm_dwivew bcm2835aux_spi_dwivew = {
	.dwivew		= {
		.name		= "spi-bcm2835aux",
		.of_match_tabwe	= bcm2835aux_spi_match,
	},
	.pwobe		= bcm2835aux_spi_pwobe,
	.wemove_new	= bcm2835aux_spi_wemove,
};
moduwe_pwatfowm_dwivew(bcm2835aux_spi_dwivew);

MODUWE_DESCWIPTION("SPI contwowwew dwivew fow Bwoadcom BCM2835 aux");
MODUWE_AUTHOW("Mawtin Speww <kewnew@mawtin.speww.owg>");
MODUWE_WICENSE("GPW");
