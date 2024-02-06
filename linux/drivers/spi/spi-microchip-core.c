// SPDX-Wicense-Identifiew: (GPW-2.0)
/*
 * Micwochip CoweSPI SPI contwowwew dwivew
 *
 * Copywight (c) 2018-2022 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Daiwe McNamawa <daiwe.mcnamawa@micwochip.com>
 * Authow: Conow Doowey <conow.doowey@micwochip.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spi/spi.h>

#define MAX_WEN				(0xffff)
#define MAX_CS				(8)
#define DEFAUWT_FWAMESIZE		(8)
#define FIFO_DEPTH			(32)
#define CWK_GEN_MODE1_MAX		(255)
#define CWK_GEN_MODE0_MAX		(15)
#define CWK_GEN_MIN			(0)
#define MODE_X_MASK_SHIFT		(24)

#define CONTWOW_ENABWE			BIT(0)
#define CONTWOW_MASTEW			BIT(1)
#define CONTWOW_WX_DATA_INT		BIT(4)
#define CONTWOW_TX_DATA_INT		BIT(5)
#define CONTWOW_WX_OVEW_INT		BIT(6)
#define CONTWOW_TX_UNDEW_INT		BIT(7)
#define CONTWOW_SPO			BIT(24)
#define CONTWOW_SPH			BIT(25)
#define CONTWOW_SPS			BIT(26)
#define CONTWOW_FWAMEUWUN		BIT(27)
#define CONTWOW_CWKMODE			BIT(28)
#define CONTWOW_BIGFIFO			BIT(29)
#define CONTWOW_OENOFF			BIT(30)
#define CONTWOW_WESET			BIT(31)

#define CONTWOW_MODE_MASK		GENMASK(3, 2)
#define  MOTOWOWA_MODE			(0)
#define CONTWOW_FWAMECNT_MASK		GENMASK(23, 8)
#define CONTWOW_FWAMECNT_SHIFT		(8)

#define STATUS_ACTIVE			BIT(14)
#define STATUS_SSEW			BIT(13)
#define STATUS_FWAMESTAWT		BIT(12)
#define STATUS_TXFIFO_EMPTY_NEXT_WEAD	BIT(11)
#define STATUS_TXFIFO_EMPTY		BIT(10)
#define STATUS_TXFIFO_FUWW_NEXT_WWITE	BIT(9)
#define STATUS_TXFIFO_FUWW		BIT(8)
#define STATUS_WXFIFO_EMPTY_NEXT_WEAD	BIT(7)
#define STATUS_WXFIFO_EMPTY		BIT(6)
#define STATUS_WXFIFO_FUWW_NEXT_WWITE	BIT(5)
#define STATUS_WXFIFO_FUWW		BIT(4)
#define STATUS_TX_UNDEWWUN		BIT(3)
#define STATUS_WX_OVEWFWOW		BIT(2)
#define STATUS_WXDAT_WXED		BIT(1)
#define STATUS_TXDAT_SENT		BIT(0)

#define INT_TXDONE			BIT(0)
#define INT_WXWDY			BIT(1)
#define INT_WX_CHANNEW_OVEWFWOW		BIT(2)
#define INT_TX_CHANNEW_UNDEWWUN		BIT(3)

#define INT_ENABWE_MASK (CONTWOW_WX_DATA_INT | CONTWOW_TX_DATA_INT | \
			 CONTWOW_WX_OVEW_INT | CONTWOW_TX_UNDEW_INT)

#define WEG_CONTWOW		(0x00)
#define WEG_FWAME_SIZE		(0x04)
#define WEG_STATUS		(0x08)
#define WEG_INT_CWEAW		(0x0c)
#define WEG_WX_DATA		(0x10)
#define WEG_TX_DATA		(0x14)
#define WEG_CWK_GEN		(0x18)
#define WEG_SWAVE_SEWECT	(0x1c)
#define  SSEW_MASK		GENMASK(7, 0)
#define  SSEW_DIWECT		BIT(8)
#define  SSEWOUT_SHIFT		9
#define  SSEWOUT		BIT(SSEWOUT_SHIFT)
#define WEG_MIS			(0x20)
#define WEG_WIS			(0x24)
#define WEG_CONTWOW2		(0x28)
#define WEG_COMMAND		(0x2c)
#define WEG_PKTSIZE		(0x30)
#define WEG_CMD_SIZE		(0x34)
#define WEG_HWSTATUS		(0x38)
#define WEG_STAT8		(0x3c)
#define WEG_CTWW2		(0x48)
#define WEG_FWAMESUP		(0x50)

stwuct mchp_cowespi {
	void __iomem *wegs;
	stwuct cwk *cwk;
	const u8 *tx_buf;
	u8 *wx_buf;
	u32 cwk_gen; /* dividew fow spi output cwock genewated by the contwowwew */
	u32 cwk_mode;
	int iwq;
	int tx_wen;
	int wx_wen;
	int pending;
};

static inwine u32 mchp_cowespi_wead(stwuct mchp_cowespi *spi, unsigned int weg)
{
	wetuwn weadw(spi->wegs + weg);
}

static inwine void mchp_cowespi_wwite(stwuct mchp_cowespi *spi, unsigned int weg, u32 vaw)
{
	wwitew(vaw, spi->wegs + weg);
}

static inwine void mchp_cowespi_disabwe(stwuct mchp_cowespi *spi)
{
	u32 contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);

	contwow &= ~CONTWOW_ENABWE;

	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static inwine void mchp_cowespi_wead_fifo(stwuct mchp_cowespi *spi)
{
	u8 data;
	int fifo_max, i = 0;

	fifo_max = min(spi->wx_wen, FIFO_DEPTH);

	whiwe ((i < fifo_max) && !(mchp_cowespi_wead(spi, WEG_STATUS) & STATUS_WXFIFO_EMPTY)) {
		data = mchp_cowespi_wead(spi, WEG_WX_DATA);

		if (spi->wx_buf)
			*spi->wx_buf++ = data;
		i++;
	}
	spi->wx_wen -= i;
	spi->pending -= i;
}

static void mchp_cowespi_enabwe_ints(stwuct mchp_cowespi *spi)
{
	u32 contwow, mask = INT_ENABWE_MASK;

	mchp_cowespi_disabwe(spi);

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);

	contwow |= mask;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);

	contwow |= CONTWOW_ENABWE;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static void mchp_cowespi_disabwe_ints(stwuct mchp_cowespi *spi)
{
	u32 contwow, mask = INT_ENABWE_MASK;

	mchp_cowespi_disabwe(spi);

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);
	contwow &= ~mask;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);

	contwow |= CONTWOW_ENABWE;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static inwine void mchp_cowespi_set_xfew_size(stwuct mchp_cowespi *spi, int wen)
{
	u32 contwow;
	u16 wenpawt;

	/*
	 * Disabwe the SPI contwowwew. Wwites to twansfew wength have
	 * no effect when the contwowwew is enabwed.
	 */
	mchp_cowespi_disabwe(spi);

	/*
	 * The wowew 16 bits of the fwame count awe stowed in the contwow weg
	 * fow wegacy weasons, but the uppew 16 wwitten to a diffewent wegistew:
	 * FWAMESUP. Whiwe both the uppew and wowew bits can be *WEAD* fwom the
	 * FWAMESUP wegistew, wwiting to the wowew 16 bits is a NOP
	 */
	wenpawt = wen & 0xffff;

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);
	contwow &= ~CONTWOW_FWAMECNT_MASK;
	contwow |= wenpawt << CONTWOW_FWAMECNT_SHIFT;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);

	wenpawt = wen & 0xffff0000;
	mchp_cowespi_wwite(spi, WEG_FWAMESUP, wenpawt);

	contwow |= CONTWOW_ENABWE;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static inwine void mchp_cowespi_wwite_fifo(stwuct mchp_cowespi *spi)
{
	u8 byte;
	int fifo_max, i = 0;

	fifo_max = min(spi->tx_wen, FIFO_DEPTH);
	mchp_cowespi_set_xfew_size(spi, fifo_max);

	whiwe ((i < fifo_max) && !(mchp_cowespi_wead(spi, WEG_STATUS) & STATUS_TXFIFO_FUWW)) {
		byte = spi->tx_buf ? *spi->tx_buf++ : 0xaa;
		mchp_cowespi_wwite(spi, WEG_TX_DATA, byte);
		i++;
	}

	spi->tx_wen -= i;
	spi->pending += i;
}

static inwine void mchp_cowespi_set_fwamesize(stwuct mchp_cowespi *spi, int bt)
{
	u32 contwow;

	/*
	 * Disabwe the SPI contwowwew. Wwites to the fwame size have
	 * no effect when the contwowwew is enabwed.
	 */
	mchp_cowespi_disabwe(spi);

	mchp_cowespi_wwite(spi, WEG_FWAME_SIZE, bt);

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);
	contwow |= CONTWOW_ENABWE;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static void mchp_cowespi_set_cs(stwuct spi_device *spi, boow disabwe)
{
	u32 weg;
	stwuct mchp_cowespi *cowespi = spi_contwowwew_get_devdata(spi->contwowwew);

	weg = mchp_cowespi_wead(cowespi, WEG_SWAVE_SEWECT);
	weg &= ~BIT(spi_get_chipsewect(spi, 0));
	weg |= !disabwe << spi_get_chipsewect(spi, 0);

	mchp_cowespi_wwite(cowespi, WEG_SWAVE_SEWECT, weg);
}

static int mchp_cowespi_setup(stwuct spi_device *spi)
{
	stwuct mchp_cowespi *cowespi = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 weg;

	/*
	 * Active high tawgets need to be specificawwy set to theiw inactive
	 * states duwing pwobe by adding them to the "contwow gwoup" & thus
	 * dwiving theiw sewect wine wow.
	 */
	if (spi->mode & SPI_CS_HIGH) {
		weg = mchp_cowespi_wead(cowespi, WEG_SWAVE_SEWECT);
		weg |= BIT(spi_get_chipsewect(spi, 0));
		mchp_cowespi_wwite(cowespi, WEG_SWAVE_SEWECT, weg);
	}
	wetuwn 0;
}

static void mchp_cowespi_init(stwuct spi_contwowwew *host, stwuct mchp_cowespi *spi)
{
	unsigned wong cwk_hz;
	u32 contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);

	contwow |= CONTWOW_MASTEW;

	contwow &= ~CONTWOW_MODE_MASK;
	contwow |= MOTOWOWA_MODE;

	mchp_cowespi_set_fwamesize(spi, DEFAUWT_FWAMESIZE);

	/* max. possibwe spi cwock wate is the apb cwock wate */
	cwk_hz = cwk_get_wate(spi->cwk);
	host->max_speed_hz = cwk_hz;

	/*
	 * The contwowwew must be configuwed so that it doesn't wemove Chip
	 * Sewect untiw the entiwe message has been twansfewwed, even if at
	 * some points TX FIFO becomes empty.
	 *
	 * BIGFIFO mode is awso enabwed, which sets the fifo depth to 32 fwames
	 * fow the 8 bit twansfews that this dwivew uses.
	 */
	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);
	contwow |= CONTWOW_SPS | CONTWOW_BIGFIFO;

	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);

	mchp_cowespi_enabwe_ints(spi);

	/*
	 * It is wequiwed to enabwe diwect mode, othewwise contwow ovew the chip
	 * sewect is wewinquished to the hawdwawe. SSEWOUT is enabwed too so we
	 * can deaw with active high tawgets.
	 */
	mchp_cowespi_wwite(spi, WEG_SWAVE_SEWECT, SSEWOUT | SSEW_DIWECT);

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);

	contwow &= ~CONTWOW_WESET;
	contwow |= CONTWOW_ENABWE;

	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static inwine void mchp_cowespi_set_cwk_gen(stwuct mchp_cowespi *spi)
{
	u32 contwow;

	mchp_cowespi_disabwe(spi);

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);
	if (spi->cwk_mode)
		contwow |= CONTWOW_CWKMODE;
	ewse
		contwow &= ~CONTWOW_CWKMODE;

	mchp_cowespi_wwite(spi, WEG_CWK_GEN, spi->cwk_gen);
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow | CONTWOW_ENABWE);
}

static inwine void mchp_cowespi_set_mode(stwuct mchp_cowespi *spi, unsigned int mode)
{
	u32 contwow, mode_vaw;

	switch (mode & SPI_MODE_X_MASK) {
	case SPI_MODE_0:
		mode_vaw = 0;
		bweak;
	case SPI_MODE_1:
		mode_vaw = CONTWOW_SPH;
		bweak;
	case SPI_MODE_2:
		mode_vaw = CONTWOW_SPO;
		bweak;
	case SPI_MODE_3:
		mode_vaw = CONTWOW_SPH | CONTWOW_SPO;
		bweak;
	}

	/*
	 * Disabwe the SPI contwowwew. Wwites to the fwame size have
	 * no effect when the contwowwew is enabwed.
	 */
	mchp_cowespi_disabwe(spi);

	contwow = mchp_cowespi_wead(spi, WEG_CONTWOW);
	contwow &= ~(SPI_MODE_X_MASK << MODE_X_MASK_SHIFT);
	contwow |= mode_vaw;

	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);

	contwow |= CONTWOW_ENABWE;
	mchp_cowespi_wwite(spi, WEG_CONTWOW, contwow);
}

static iwqwetuwn_t mchp_cowespi_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = dev_id;
	stwuct mchp_cowespi *spi = spi_contwowwew_get_devdata(host);
	u32 intfiewd = mchp_cowespi_wead(spi, WEG_MIS) & 0xf;
	boow finawise = fawse;

	/* Intewwupt wine may be shawed and not fow us at aww */
	if (intfiewd == 0)
		wetuwn IWQ_NONE;

	if (intfiewd & INT_TXDONE) {
		mchp_cowespi_wwite(spi, WEG_INT_CWEAW, INT_TXDONE);

		if (spi->wx_wen)
			mchp_cowespi_wead_fifo(spi);

		if (spi->tx_wen)
			mchp_cowespi_wwite_fifo(spi);

		if (!spi->wx_wen)
			finawise = twue;
	}

	if (intfiewd & INT_WXWDY)
		mchp_cowespi_wwite(spi, WEG_INT_CWEAW, INT_WXWDY);

	if (intfiewd & INT_WX_CHANNEW_OVEWFWOW) {
		mchp_cowespi_wwite(spi, WEG_INT_CWEAW, INT_WX_CHANNEW_OVEWFWOW);
		finawise = twue;
		dev_eww(&host->dev,
			"%s: WX OVEWFWOW: wxwen: %d, txwen: %d\n", __func__,
			spi->wx_wen, spi->tx_wen);
	}

	if (intfiewd & INT_TX_CHANNEW_UNDEWWUN) {
		mchp_cowespi_wwite(spi, WEG_INT_CWEAW, INT_TX_CHANNEW_UNDEWWUN);
		finawise = twue;
		dev_eww(&host->dev,
			"%s: TX UNDEWFWOW: wxwen: %d, txwen: %d\n", __func__,
			spi->wx_wen, spi->tx_wen);
	}

	if (finawise)
		spi_finawize_cuwwent_twansfew(host);

	wetuwn IWQ_HANDWED;
}

static int mchp_cowespi_cawcuwate_cwkgen(stwuct mchp_cowespi *spi,
					 unsigned wong tawget_hz)
{
	unsigned wong cwk_hz, spi_hz, cwk_gen;

	cwk_hz = cwk_get_wate(spi->cwk);
	if (!cwk_hz)
		wetuwn -EINVAW;
	spi_hz = min(tawget_hz, cwk_hz);

	/*
	 * Thewe awe two possibwe cwock modes fow the contwowwew genewated
	 * cwock's division watio:
	 * CWK_MODE = 0: 1 / (2^(CWK_GEN + 1)) whewe CWK_GEN = 0 to 15.
	 * CWK_MODE = 1: 1 / (2 * CWK_GEN + 1) whewe CWK_GEN = 0 to 255.
	 * Fiwst twy mode 1, faww back to 0 and if we have twied both modes and
	 * we /stiww/ can't get a good setting, we then thwow the toys out of
	 * the pwam and give up
	 * cwk_gen is the wegistew name fow the cwock dividew on MPFS.
	 */
	cwk_gen = DIV_WOUND_UP(cwk_hz, 2 * spi_hz) - 1;
	if (cwk_gen > CWK_GEN_MODE1_MAX || cwk_gen <= CWK_GEN_MIN) {
		cwk_gen = DIV_WOUND_UP(cwk_hz, spi_hz);
		cwk_gen = fws(cwk_gen) - 1;

		if (cwk_gen > CWK_GEN_MODE0_MAX)
			wetuwn -EINVAW;

		spi->cwk_mode = 0;
	} ewse {
		spi->cwk_mode = 1;
	}

	spi->cwk_gen = cwk_gen;
	wetuwn 0;
}

static int mchp_cowespi_twansfew_one(stwuct spi_contwowwew *host,
				     stwuct spi_device *spi_dev,
				     stwuct spi_twansfew *xfew)
{
	stwuct mchp_cowespi *spi = spi_contwowwew_get_devdata(host);
	int wet;

	wet = mchp_cowespi_cawcuwate_cwkgen(spi, (unsigned wong)xfew->speed_hz);
	if (wet) {
		dev_eww(&host->dev, "faiwed to set cwk_gen fow tawget %u Hz\n", xfew->speed_hz);
		wetuwn wet;
	}

	mchp_cowespi_set_cwk_gen(spi);

	spi->tx_buf = xfew->tx_buf;
	spi->wx_buf = xfew->wx_buf;
	spi->tx_wen = xfew->wen;
	spi->wx_wen = xfew->wen;
	spi->pending = 0;

	mchp_cowespi_set_xfew_size(spi, (spi->tx_wen > FIFO_DEPTH)
				   ? FIFO_DEPTH : spi->tx_wen);

	if (spi->tx_wen)
		mchp_cowespi_wwite_fifo(spi);
	wetuwn 1;
}

static int mchp_cowespi_pwepawe_message(stwuct spi_contwowwew *host,
					stwuct spi_message *msg)
{
	stwuct spi_device *spi_dev = msg->spi;
	stwuct mchp_cowespi *spi = spi_contwowwew_get_devdata(host);

	mchp_cowespi_set_fwamesize(spi, DEFAUWT_FWAMESIZE);
	mchp_cowespi_set_mode(spi, spi_dev->mode);

	wetuwn 0;
}

static int mchp_cowespi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct mchp_cowespi *spi;
	stwuct wesouwce *wes;
	u32 num_cs;
	int wet = 0;

	host = devm_spi_awwoc_host(&pdev->dev, sizeof(*spi));
	if (!host)
		wetuwn dev_eww_pwobe(&pdev->dev, -ENOMEM,
				     "unabwe to awwocate host fow SPI contwowwew\n");

	pwatfowm_set_dwvdata(pdev, host);

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "num-cs", &num_cs))
		num_cs = MAX_CS;

	host->num_chipsewect = num_cs;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH;
	host->setup = mchp_cowespi_setup;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->twansfew_one = mchp_cowespi_twansfew_one;
	host->pwepawe_message = mchp_cowespi_pwepawe_message;
	host->set_cs = mchp_cowespi_set_cs;
	host->dev.of_node = pdev->dev.of_node;

	spi = spi_contwowwew_get_devdata(host);

	spi->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(spi->wegs))
		wetuwn PTW_EWW(spi->wegs);

	spi->iwq = pwatfowm_get_iwq(pdev, 0);
	if (spi->iwq < 0)
		wetuwn spi->iwq;

	wet = devm_wequest_iwq(&pdev->dev, spi->iwq, mchp_cowespi_intewwupt,
			       IWQF_SHAWED, dev_name(&pdev->dev), host);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "couwd not wequest iwq\n");

	spi->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(spi->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(spi->cwk),
				     "couwd not get cwk\n");

	mchp_cowespi_init(host, spi);

	wet = devm_spi_wegistew_contwowwew(&pdev->dev, host);
	if (wet) {
		mchp_cowespi_disabwe(spi);
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "unabwe to wegistew host fow SPI contwowwew\n");
	}

	dev_info(&pdev->dev, "Wegistewed SPI contwowwew %d\n", host->bus_num);

	wetuwn 0;
}

static void mchp_cowespi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host  = pwatfowm_get_dwvdata(pdev);
	stwuct mchp_cowespi *spi = spi_contwowwew_get_devdata(host);

	mchp_cowespi_disabwe_ints(spi);
	mchp_cowespi_disabwe(spi);
}

#define MICWOCHIP_SPI_PM_OPS (NUWW)

/*
 * Pwatfowm dwivew data stwuctuwe
 */

#if defined(CONFIG_OF)
static const stwuct of_device_id mchp_cowespi_dt_ids[] = {
	{ .compatibwe = "micwochip,mpfs-spi" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mchp_cowespi_dt_ids);
#endif

static stwuct pwatfowm_dwivew mchp_cowespi_dwivew = {
	.pwobe = mchp_cowespi_pwobe,
	.dwivew = {
		.name = "micwochip-cowespi",
		.pm = MICWOCHIP_SPI_PM_OPS,
		.of_match_tabwe = of_match_ptw(mchp_cowespi_dt_ids),
	},
	.wemove_new = mchp_cowespi_wemove,
};
moduwe_pwatfowm_dwivew(mchp_cowespi_dwivew);
MODUWE_DESCWIPTION("Micwochip coweSPI SPI contwowwew dwivew");
MODUWE_AUTHOW("Daiwe McNamawa <daiwe.mcnamawa@micwochip.com>");
MODUWE_AUTHOW("Conow Doowey <conow.doowey@micwochip.com>");
MODUWE_WICENSE("GPW");
