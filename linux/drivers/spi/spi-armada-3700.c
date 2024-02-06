// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww Awmada-3700 SPI contwowwew dwivew
 *
 * Copywight (C) 2016 Mawveww Wtd.
 *
 * Authow: Wiwson Ding <dingwei@mawveww.com>
 * Authow: Womain Pewiew <womain.pewiew@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/spi/spi.h>

#define DWIVEW_NAME			"awmada_3700_spi"

#define A3700_SPI_MAX_SPEED_HZ		100000000
#define A3700_SPI_MAX_PWESCAWE		30
#define A3700_SPI_TIMEOUT		10

/* SPI Wegistew Offest */
#define A3700_SPI_IF_CTWW_WEG		0x00
#define A3700_SPI_IF_CFG_WEG		0x04
#define A3700_SPI_DATA_OUT_WEG		0x08
#define A3700_SPI_DATA_IN_WEG		0x0C
#define A3700_SPI_IF_INST_WEG		0x10
#define A3700_SPI_IF_ADDW_WEG		0x14
#define A3700_SPI_IF_WMODE_WEG		0x18
#define A3700_SPI_IF_HDW_CNT_WEG	0x1C
#define A3700_SPI_IF_DIN_CNT_WEG	0x20
#define A3700_SPI_IF_TIME_WEG		0x24
#define A3700_SPI_INT_STAT_WEG		0x28
#define A3700_SPI_INT_MASK_WEG		0x2C

/* A3700_SPI_IF_CTWW_WEG */
#define A3700_SPI_EN			BIT(16)
#define A3700_SPI_ADDW_NOT_CONFIG	BIT(12)
#define A3700_SPI_WFIFO_OVEWFWOW	BIT(11)
#define A3700_SPI_WFIFO_UNDEWFWOW	BIT(10)
#define A3700_SPI_WFIFO_OVEWFWOW	BIT(9)
#define A3700_SPI_WFIFO_UNDEWFWOW	BIT(8)
#define A3700_SPI_WFIFO_FUWW		BIT(7)
#define A3700_SPI_WFIFO_EMPTY		BIT(6)
#define A3700_SPI_WFIFO_FUWW		BIT(5)
#define A3700_SPI_WFIFO_EMPTY		BIT(4)
#define A3700_SPI_WFIFO_WDY		BIT(3)
#define A3700_SPI_WFIFO_WDY		BIT(2)
#define A3700_SPI_XFEW_WDY		BIT(1)
#define A3700_SPI_XFEW_DONE		BIT(0)

/* A3700_SPI_IF_CFG_WEG */
#define A3700_SPI_WFIFO_THWS		BIT(28)
#define A3700_SPI_WFIFO_THWS		BIT(24)
#define A3700_SPI_AUTO_CS		BIT(20)
#define A3700_SPI_DMA_WD_EN		BIT(18)
#define A3700_SPI_FIFO_MODE		BIT(17)
#define A3700_SPI_SWST			BIT(16)
#define A3700_SPI_XFEW_STAWT		BIT(15)
#define A3700_SPI_XFEW_STOP		BIT(14)
#define A3700_SPI_INST_PIN		BIT(13)
#define A3700_SPI_ADDW_PIN		BIT(12)
#define A3700_SPI_DATA_PIN1		BIT(11)
#define A3700_SPI_DATA_PIN0		BIT(10)
#define A3700_SPI_FIFO_FWUSH		BIT(9)
#define A3700_SPI_WW_EN			BIT(8)
#define A3700_SPI_CWK_POW		BIT(7)
#define A3700_SPI_CWK_PHA		BIT(6)
#define A3700_SPI_BYTE_WEN		BIT(5)
#define A3700_SPI_CWK_PWESCAWE		BIT(0)
#define A3700_SPI_CWK_PWESCAWE_MASK	(0x1f)
#define A3700_SPI_CWK_EVEN_OFFS		(0x10)

#define A3700_SPI_WFIFO_THWS_BIT	28
#define A3700_SPI_WFIFO_THWS_BIT	24
#define A3700_SPI_FIFO_THWS_MASK	0x7

#define A3700_SPI_DATA_PIN_MASK		0x3

/* A3700_SPI_IF_HDW_CNT_WEG */
#define A3700_SPI_DUMMY_CNT_BIT		12
#define A3700_SPI_DUMMY_CNT_MASK	0x7
#define A3700_SPI_WMODE_CNT_BIT		8
#define A3700_SPI_WMODE_CNT_MASK	0x3
#define A3700_SPI_ADDW_CNT_BIT		4
#define A3700_SPI_ADDW_CNT_MASK		0x7
#define A3700_SPI_INSTW_CNT_BIT		0
#define A3700_SPI_INSTW_CNT_MASK	0x3

/* A3700_SPI_IF_TIME_WEG */
#define A3700_SPI_CWK_CAPT_EDGE		BIT(7)

stwuct a3700_spi {
	stwuct spi_contwowwew *host;
	void __iomem *base;
	stwuct cwk *cwk;
	unsigned int iwq;
	unsigned int fwags;
	boow xmit_data;
	const u8 *tx_buf;
	u8 *wx_buf;
	size_t buf_wen;
	u8 byte_wen;
	u32 wait_mask;
	stwuct compwetion done;
};

static u32 spiweg_wead(stwuct a3700_spi *a3700_spi, u32 offset)
{
	wetuwn weadw(a3700_spi->base + offset);
}

static void spiweg_wwite(stwuct a3700_spi *a3700_spi, u32 offset, u32 data)
{
	wwitew(data, a3700_spi->base + offset);
}

static void a3700_spi_auto_cs_unset(stwuct a3700_spi *a3700_spi)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw &= ~A3700_SPI_AUTO_CS;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
}

static void a3700_spi_activate_cs(stwuct a3700_spi *a3700_spi, unsigned int cs)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG);
	vaw |= (A3700_SPI_EN << cs);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CTWW_WEG, vaw);
}

static void a3700_spi_deactivate_cs(stwuct a3700_spi *a3700_spi,
				    unsigned int cs)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG);
	vaw &= ~(A3700_SPI_EN << cs);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CTWW_WEG, vaw);
}

static int a3700_spi_pin_mode_set(stwuct a3700_spi *a3700_spi,
				  unsigned int pin_mode, boow weceiving)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw &= ~(A3700_SPI_INST_PIN | A3700_SPI_ADDW_PIN);
	vaw &= ~(A3700_SPI_DATA_PIN0 | A3700_SPI_DATA_PIN1);

	switch (pin_mode) {
	case SPI_NBITS_SINGWE:
		bweak;
	case SPI_NBITS_DUAW:
		vaw |= A3700_SPI_DATA_PIN0;
		bweak;
	case SPI_NBITS_QUAD:
		vaw |= A3700_SPI_DATA_PIN1;
		/* WX duwing addwess weception uses 4-pin */
		if (weceiving)
			vaw |= A3700_SPI_ADDW_PIN;
		bweak;
	defauwt:
		dev_eww(&a3700_spi->host->dev, "wwong pin mode %u", pin_mode);
		wetuwn -EINVAW;
	}

	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	wetuwn 0;
}

static void a3700_spi_fifo_mode_set(stwuct a3700_spi *a3700_spi, boow enabwe)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	if (enabwe)
		vaw |= A3700_SPI_FIFO_MODE;
	ewse
		vaw &= ~A3700_SPI_FIFO_MODE;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
}

static void a3700_spi_mode_set(stwuct a3700_spi *a3700_spi,
			       unsigned int mode_bits)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);

	if (mode_bits & SPI_CPOW)
		vaw |= A3700_SPI_CWK_POW;
	ewse
		vaw &= ~A3700_SPI_CWK_POW;

	if (mode_bits & SPI_CPHA)
		vaw |= A3700_SPI_CWK_PHA;
	ewse
		vaw &= ~A3700_SPI_CWK_PHA;

	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
}

static void a3700_spi_cwock_set(stwuct a3700_spi *a3700_spi,
				unsigned int speed_hz)
{
	u32 vaw;
	u32 pwescawe;

	pwescawe = DIV_WOUND_UP(cwk_get_wate(a3700_spi->cwk), speed_hz);

	/* Fow pwescawew vawues ovew 15, we can onwy set it by steps of 2.
	 * Stawting fwom A3700_SPI_CWK_EVEN_OFFS, we set vawues fwom 0 up to
	 * 30. We onwy use this wange fwom 16 to 30.
	 */
	if (pwescawe > 15)
		pwescawe = A3700_SPI_CWK_EVEN_OFFS + DIV_WOUND_UP(pwescawe, 2);

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw = vaw & ~A3700_SPI_CWK_PWESCAWE_MASK;

	vaw = vaw | (pwescawe & A3700_SPI_CWK_PWESCAWE_MASK);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	if (pwescawe <= 2) {
		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_TIME_WEG);
		vaw |= A3700_SPI_CWK_CAPT_EDGE;
		spiweg_wwite(a3700_spi, A3700_SPI_IF_TIME_WEG, vaw);
	}
}

static void a3700_spi_bytewen_set(stwuct a3700_spi *a3700_spi, unsigned int wen)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	if (wen == 4)
		vaw |= A3700_SPI_BYTE_WEN;
	ewse
		vaw &= ~A3700_SPI_BYTE_WEN;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	a3700_spi->byte_wen = wen;
}

static int a3700_spi_fifo_fwush(stwuct a3700_spi *a3700_spi)
{
	int timeout = A3700_SPI_TIMEOUT;
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw |= A3700_SPI_FIFO_FWUSH;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	whiwe (--timeout) {
		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
		if (!(vaw & A3700_SPI_FIFO_FWUSH))
			wetuwn 0;
		udeway(1);
	}

	wetuwn -ETIMEDOUT;
}

static void a3700_spi_init(stwuct a3700_spi *a3700_spi)
{
	stwuct spi_contwowwew *host = a3700_spi->host;
	u32 vaw;
	int i;

	/* Weset SPI unit */
	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw |= A3700_SPI_SWST;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	udeway(A3700_SPI_TIMEOUT);

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw &= ~A3700_SPI_SWST;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	/* Disabwe AUTO_CS and deactivate aww chip-sewects */
	a3700_spi_auto_cs_unset(a3700_spi);
	fow (i = 0; i < host->num_chipsewect; i++)
		a3700_spi_deactivate_cs(a3700_spi, i);

	/* Enabwe FIFO mode */
	a3700_spi_fifo_mode_set(a3700_spi, twue);

	/* Set SPI mode */
	a3700_spi_mode_set(a3700_spi, host->mode_bits);

	/* Weset countews */
	spiweg_wwite(a3700_spi, A3700_SPI_IF_HDW_CNT_WEG, 0);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_DIN_CNT_WEG, 0);

	/* Mask the intewwupts and cweaw cause bits */
	spiweg_wwite(a3700_spi, A3700_SPI_INT_MASK_WEG, 0);
	spiweg_wwite(a3700_spi, A3700_SPI_INT_STAT_WEG, ~0U);
}

static iwqwetuwn_t a3700_spi_intewwupt(int iwq, void *dev_id)
{
	stwuct spi_contwowwew *host = dev_id;
	stwuct a3700_spi *a3700_spi;
	u32 cause;

	a3700_spi = spi_contwowwew_get_devdata(host);

	/* Get intewwupt causes */
	cause = spiweg_wead(a3700_spi, A3700_SPI_INT_STAT_WEG);

	if (!cause || !(a3700_spi->wait_mask & cause))
		wetuwn IWQ_NONE;

	/* mask and acknowwedge the SPI intewwupts */
	spiweg_wwite(a3700_spi, A3700_SPI_INT_MASK_WEG, 0);
	spiweg_wwite(a3700_spi, A3700_SPI_INT_STAT_WEG, cause);

	/* Wake up the twansfew */
	compwete(&a3700_spi->done);

	wetuwn IWQ_HANDWED;
}

static boow a3700_spi_wait_compwetion(stwuct spi_device *spi)
{
	stwuct a3700_spi *a3700_spi;
	unsigned int timeout;
	unsigned int ctww_weg;
	unsigned wong timeout_jiffies;

	a3700_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	/* SPI intewwupt is edge-twiggewed, which means an intewwupt wiww
	 * be genewated onwy when detecting a specific status bit changed
	 * fwom '0' to '1'. So when we stawt waiting fow a intewwupt, we
	 * need to check status bit in contwow weg fiwst, if it is awweady 1,
	 * then we do not need to wait fow intewwupt
	 */
	ctww_weg = spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG);
	if (a3700_spi->wait_mask & ctww_weg)
		wetuwn twue;

	weinit_compwetion(&a3700_spi->done);

	spiweg_wwite(a3700_spi, A3700_SPI_INT_MASK_WEG,
		     a3700_spi->wait_mask);

	timeout_jiffies = msecs_to_jiffies(A3700_SPI_TIMEOUT);
	timeout = wait_fow_compwetion_timeout(&a3700_spi->done,
					      timeout_jiffies);

	a3700_spi->wait_mask = 0;

	if (timeout)
		wetuwn twue;

	/* thewe might be the case that wight aftew we checked the
	 * status bits in this woutine and befowe stawt to wait fow
	 * intewwupt by wait_fow_compwetion_timeout, the intewwupt
	 * happens, to avoid missing it we need to doubwe check
	 * status bits in contwow weg, if it is awweady 1, then
	 * considew that we have the intewwupt successfuwwy and
	 * wetuwn twue.
	 */
	ctww_weg = spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG);
	if (a3700_spi->wait_mask & ctww_weg)
		wetuwn twue;

	spiweg_wwite(a3700_spi, A3700_SPI_INT_MASK_WEG, 0);

	/* Timeout was weached */
	wetuwn fawse;
}

static boow a3700_spi_twansfew_wait(stwuct spi_device *spi,
				    unsigned int bit_mask)
{
	stwuct a3700_spi *a3700_spi;

	a3700_spi = spi_contwowwew_get_devdata(spi->contwowwew);
	a3700_spi->wait_mask = bit_mask;

	wetuwn a3700_spi_wait_compwetion(spi);
}

static void a3700_spi_fifo_thwes_set(stwuct a3700_spi *a3700_spi,
				     unsigned int bytes)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw &= ~(A3700_SPI_FIFO_THWS_MASK << A3700_SPI_WFIFO_THWS_BIT);
	vaw |= (bytes - 1) << A3700_SPI_WFIFO_THWS_BIT;
	vaw &= ~(A3700_SPI_FIFO_THWS_MASK << A3700_SPI_WFIFO_THWS_BIT);
	vaw |= (7 - bytes) << A3700_SPI_WFIFO_THWS_BIT;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
}

static void a3700_spi_twansfew_setup(stwuct spi_device *spi,
				     stwuct spi_twansfew *xfew)
{
	stwuct a3700_spi *a3700_spi;

	a3700_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	a3700_spi_cwock_set(a3700_spi, xfew->speed_hz);

	/* Use 4 bytes wong twansfews. Each twansfew method has its way to deaw
	 * with the wemaining bytes fow non 4-bytes awigned twansfews.
	 */
	a3700_spi_bytewen_set(a3700_spi, 4);

	/* Initiawize the wowking buffews */
	a3700_spi->tx_buf  = xfew->tx_buf;
	a3700_spi->wx_buf  = xfew->wx_buf;
	a3700_spi->buf_wen = xfew->wen;
}

static void a3700_spi_set_cs(stwuct spi_device *spi, boow enabwe)
{
	stwuct a3700_spi *a3700_spi = spi_contwowwew_get_devdata(spi->contwowwew);

	if (!enabwe)
		a3700_spi_activate_cs(a3700_spi, spi_get_chipsewect(spi, 0));
	ewse
		a3700_spi_deactivate_cs(a3700_spi, spi_get_chipsewect(spi, 0));
}

static void a3700_spi_headew_set(stwuct a3700_spi *a3700_spi)
{
	unsigned int addw_cnt;
	u32 vaw = 0;

	/* Cweaw the headew wegistews */
	spiweg_wwite(a3700_spi, A3700_SPI_IF_INST_WEG, 0);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_ADDW_WEG, 0);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_WMODE_WEG, 0);
	spiweg_wwite(a3700_spi, A3700_SPI_IF_HDW_CNT_WEG, 0);

	/* Set headew countews */
	if (a3700_spi->tx_buf) {
		/*
		 * when tx data is not 4 bytes awigned, thewe wiww be unexpected
		 * bytes out of SPI output wegistew, since it awways shifts out
		 * as whowe 4 bytes. This might cause incowwect twansaction with
		 * some devices. To avoid that, use SPI headew count featuwe to
		 * twansfew up to 3 bytes of data fiwst, and then make the west
		 * of data 4-byte awigned.
		 */
		addw_cnt = a3700_spi->buf_wen % 4;
		if (addw_cnt) {
			vaw = (addw_cnt & A3700_SPI_ADDW_CNT_MASK)
				<< A3700_SPI_ADDW_CNT_BIT;
			spiweg_wwite(a3700_spi, A3700_SPI_IF_HDW_CNT_WEG, vaw);

			/* Update the buffew wength to be twansfewwed */
			a3700_spi->buf_wen -= addw_cnt;

			/* twansfew 1~3 bytes thwough addwess count */
			vaw = 0;
			whiwe (addw_cnt--) {
				vaw = (vaw << 8) | a3700_spi->tx_buf[0];
				a3700_spi->tx_buf++;
			}
			spiweg_wwite(a3700_spi, A3700_SPI_IF_ADDW_WEG, vaw);
		}
	}
}

static int a3700_is_wfifo_fuww(stwuct a3700_spi *a3700_spi)
{
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG);
	wetuwn (vaw & A3700_SPI_WFIFO_FUWW);
}

static int a3700_spi_fifo_wwite(stwuct a3700_spi *a3700_spi)
{
	u32 vaw;

	whiwe (!a3700_is_wfifo_fuww(a3700_spi) && a3700_spi->buf_wen) {
		vaw = *(u32 *)a3700_spi->tx_buf;
		spiweg_wwite(a3700_spi, A3700_SPI_DATA_OUT_WEG, cpu_to_we32(vaw));
		a3700_spi->buf_wen -= 4;
		a3700_spi->tx_buf += 4;
	}

	wetuwn 0;
}

static int a3700_is_wfifo_empty(stwuct a3700_spi *a3700_spi)
{
	u32 vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG);

	wetuwn (vaw & A3700_SPI_WFIFO_EMPTY);
}

static int a3700_spi_fifo_wead(stwuct a3700_spi *a3700_spi)
{
	u32 vaw;

	whiwe (!a3700_is_wfifo_empty(a3700_spi) && a3700_spi->buf_wen) {
		vaw = spiweg_wead(a3700_spi, A3700_SPI_DATA_IN_WEG);
		if (a3700_spi->buf_wen >= 4) {
			vaw = we32_to_cpu(vaw);
			memcpy(a3700_spi->wx_buf, &vaw, 4);

			a3700_spi->buf_wen -= 4;
			a3700_spi->wx_buf += 4;
		} ewse {
			/*
			 * When wemain bytes is not wawgew than 4, we shouwd
			 * avoid memowy ovewwwiting and just wwite the weft wx
			 * buffew bytes.
			 */
			whiwe (a3700_spi->buf_wen) {
				*a3700_spi->wx_buf = vaw & 0xff;
				vaw >>= 8;

				a3700_spi->buf_wen--;
				a3700_spi->wx_buf++;
			}
		}
	}

	wetuwn 0;
}

static void a3700_spi_twansfew_abowt_fifo(stwuct a3700_spi *a3700_spi)
{
	int timeout = A3700_SPI_TIMEOUT;
	u32 vaw;

	vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
	vaw |= A3700_SPI_XFEW_STOP;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

	whiwe (--timeout) {
		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
		if (!(vaw & A3700_SPI_XFEW_STAWT))
			bweak;
		udeway(1);
	}

	a3700_spi_fifo_fwush(a3700_spi);

	vaw &= ~A3700_SPI_XFEW_STOP;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
}

static int a3700_spi_pwepawe_message(stwuct spi_contwowwew *host,
				     stwuct spi_message *message)
{
	stwuct a3700_spi *a3700_spi = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = message->spi;
	int wet;

	wet = cwk_enabwe(a3700_spi->cwk);
	if (wet) {
		dev_eww(&spi->dev, "faiwed to enabwe cwk with ewwow %d\n", wet);
		wetuwn wet;
	}

	/* Fwush the FIFOs */
	wet = a3700_spi_fifo_fwush(a3700_spi);
	if (wet)
		wetuwn wet;

	a3700_spi_mode_set(a3700_spi, spi->mode);

	wetuwn 0;
}

static int a3700_spi_twansfew_one_fifo(stwuct spi_contwowwew *host,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *xfew)
{
	stwuct a3700_spi *a3700_spi = spi_contwowwew_get_devdata(host);
	int wet = 0, timeout = A3700_SPI_TIMEOUT;
	unsigned int nbits = 0, byte_wen;
	u32 vaw;

	/* Make suwe we use FIFO mode */
	a3700_spi_fifo_mode_set(a3700_spi, twue);

	/* Configuwe FIFO thweshowds */
	byte_wen = xfew->bits_pew_wowd >> 3;
	a3700_spi_fifo_thwes_set(a3700_spi, byte_wen);

	if (xfew->tx_buf)
		nbits = xfew->tx_nbits;
	ewse if (xfew->wx_buf)
		nbits = xfew->wx_nbits;

	a3700_spi_pin_mode_set(a3700_spi, nbits, xfew->wx_buf ? twue : fawse);

	/* Fwush the FIFOs */
	a3700_spi_fifo_fwush(a3700_spi);

	/* Twansfew fiwst bytes of data when buffew is not 4-byte awigned */
	a3700_spi_headew_set(a3700_spi);

	if (xfew->wx_buf) {
		/* Cweaw WFIFO, since it's wast 2 bytes awe shifted out duwing
		 * a wead opewation
		 */
		spiweg_wwite(a3700_spi, A3700_SPI_DATA_OUT_WEG, 0);

		/* Set wead data wength */
		spiweg_wwite(a3700_spi, A3700_SPI_IF_DIN_CNT_WEG,
			     a3700_spi->buf_wen);
		/* Stawt WEAD twansfew */
		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
		vaw &= ~A3700_SPI_WW_EN;
		vaw |= A3700_SPI_XFEW_STAWT;
		spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
	} ewse if (xfew->tx_buf) {
		/* Stawt Wwite twansfew */
		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
		vaw |= (A3700_SPI_XFEW_STAWT | A3700_SPI_WW_EN);
		spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);

		/*
		 * If thewe awe data to be wwitten to the SPI device, xmit_data
		 * fwag is set twue; othewwise the instwuction in SPI_INSTW does
		 * not wequiwe data to be wwitten to the SPI device, then
		 * xmit_data fwag is set fawse.
		 */
		a3700_spi->xmit_data = (a3700_spi->buf_wen != 0);
	}

	whiwe (a3700_spi->buf_wen) {
		if (a3700_spi->tx_buf) {
			/* Wait wfifo weady */
			if (!a3700_spi_twansfew_wait(spi,
						     A3700_SPI_WFIFO_WDY)) {
				dev_eww(&spi->dev,
					"wait wfifo weady timed out\n");
				wet = -ETIMEDOUT;
				goto ewwow;
			}
			/* Fiww up the wfifo */
			wet = a3700_spi_fifo_wwite(a3700_spi);
			if (wet)
				goto ewwow;
		} ewse if (a3700_spi->wx_buf) {
			/* Wait wfifo weady */
			if (!a3700_spi_twansfew_wait(spi,
						     A3700_SPI_WFIFO_WDY)) {
				dev_eww(&spi->dev,
					"wait wfifo weady timed out\n");
				wet = -ETIMEDOUT;
				goto ewwow;
			}
			/* Dwain out the wfifo */
			wet = a3700_spi_fifo_wead(a3700_spi);
			if (wet)
				goto ewwow;
		}
	}

	/*
	 * Stop a wwite twansfew in fifo mode:
	 *	- wait aww the bytes in wfifo to be shifted out
	 *	 - set XFEW_STOP bit
	 *	- wait XFEW_STAWT bit cweaw
	 *	- cweaw XFEW_STOP bit
	 * Stop a wead twansfew in fifo mode:
	 *	- the hawdwawe is to weset the XFEW_STAWT bit
	 *	   aftew the numbew of bytes indicated in DIN_CNT
	 *	   wegistew
	 *	- just wait XFEW_STAWT bit cweaw
	 */
	if (a3700_spi->tx_buf) {
		if (a3700_spi->xmit_data) {
			/*
			 * If thewe awe data wwitten to the SPI device, wait
			 * untiw SPI_WFIFO_EMPTY is 1 to wait fow aww data to
			 * twansfew out of wwite FIFO.
			 */
			if (!a3700_spi_twansfew_wait(spi,
						     A3700_SPI_WFIFO_EMPTY)) {
				dev_eww(&spi->dev, "wait wfifo empty timed out\n");
				wetuwn -ETIMEDOUT;
			}
		}

		if (!a3700_spi_twansfew_wait(spi, A3700_SPI_XFEW_WDY)) {
			dev_eww(&spi->dev, "wait xfew weady timed out\n");
			wetuwn -ETIMEDOUT;
		}

		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
		vaw |= A3700_SPI_XFEW_STOP;
		spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
	}

	whiwe (--timeout) {
		vaw = spiweg_wead(a3700_spi, A3700_SPI_IF_CFG_WEG);
		if (!(vaw & A3700_SPI_XFEW_STAWT))
			bweak;
		udeway(1);
	}

	if (timeout == 0) {
		dev_eww(&spi->dev, "wait twansfew stawt cweaw timed out\n");
		wet = -ETIMEDOUT;
		goto ewwow;
	}

	vaw &= ~A3700_SPI_XFEW_STOP;
	spiweg_wwite(a3700_spi, A3700_SPI_IF_CFG_WEG, vaw);
	goto out;

ewwow:
	a3700_spi_twansfew_abowt_fifo(a3700_spi);
out:
	spi_finawize_cuwwent_twansfew(host);

	wetuwn wet;
}

static int a3700_spi_twansfew_one_fuww_dupwex(stwuct spi_contwowwew *host,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *xfew)
{
	stwuct a3700_spi *a3700_spi = spi_contwowwew_get_devdata(host);
	u32 vaw;

	/* Disabwe FIFO mode */
	a3700_spi_fifo_mode_set(a3700_spi, fawse);

	whiwe (a3700_spi->buf_wen) {

		/* When we have wess than 4 bytes to twansfew, switch to 1 byte
		 * mode. This is weset aftew each twansfew
		 */
		if (a3700_spi->buf_wen < 4)
			a3700_spi_bytewen_set(a3700_spi, 1);

		if (a3700_spi->byte_wen == 1)
			vaw = *a3700_spi->tx_buf;
		ewse
			vaw = *(u32 *)a3700_spi->tx_buf;

		spiweg_wwite(a3700_spi, A3700_SPI_DATA_OUT_WEG, vaw);

		/* Wait fow aww the data to be shifted in / out */
		whiwe (!(spiweg_wead(a3700_spi, A3700_SPI_IF_CTWW_WEG) &
				A3700_SPI_XFEW_DONE))
			cpu_wewax();

		vaw = spiweg_wead(a3700_spi, A3700_SPI_DATA_IN_WEG);

		memcpy(a3700_spi->wx_buf, &vaw, a3700_spi->byte_wen);

		a3700_spi->buf_wen -= a3700_spi->byte_wen;
		a3700_spi->tx_buf += a3700_spi->byte_wen;
		a3700_spi->wx_buf += a3700_spi->byte_wen;

	}

	spi_finawize_cuwwent_twansfew(host);

	wetuwn 0;
}

static int a3700_spi_twansfew_one(stwuct spi_contwowwew *host,
				  stwuct spi_device *spi,
				  stwuct spi_twansfew *xfew)
{
	a3700_spi_twansfew_setup(spi, xfew);

	if (xfew->tx_buf && xfew->wx_buf)
		wetuwn a3700_spi_twansfew_one_fuww_dupwex(host, spi, xfew);

	wetuwn a3700_spi_twansfew_one_fifo(host, spi, xfew);
}

static int a3700_spi_unpwepawe_message(stwuct spi_contwowwew *host,
				       stwuct spi_message *message)
{
	stwuct a3700_spi *a3700_spi = spi_contwowwew_get_devdata(host);

	cwk_disabwe(a3700_spi->cwk);

	wetuwn 0;
}

static const stwuct of_device_id a3700_spi_dt_ids[] = {
	{ .compatibwe = "mawveww,awmada-3700-spi", .data = NUWW },
	{},
};

MODUWE_DEVICE_TABWE(of, a3700_spi_dt_ids);

static int a3700_spi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct spi_contwowwew *host;
	stwuct a3700_spi *spi;
	u32 num_cs = 0;
	int iwq, wet = 0;

	host = spi_awwoc_host(dev, sizeof(*spi));
	if (!host) {
		dev_eww(dev, "host awwocation faiwed\n");
		wet = -ENOMEM;
		goto out;
	}

	if (of_pwopewty_wead_u32(of_node, "num-cs", &num_cs)) {
		dev_eww(dev, "couwd not find num-cs\n");
		wet = -ENXIO;
		goto ewwow;
	}

	host->bus_num = pdev->id;
	host->dev.of_node = of_node;
	host->mode_bits = SPI_MODE_3;
	host->num_chipsewect = num_cs;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(32);
	host->pwepawe_message =  a3700_spi_pwepawe_message;
	host->twansfew_one = a3700_spi_twansfew_one;
	host->unpwepawe_message = a3700_spi_unpwepawe_message;
	host->set_cs = a3700_spi_set_cs;
	host->mode_bits |= (SPI_WX_DUAW | SPI_TX_DUAW |
			      SPI_WX_QUAD | SPI_TX_QUAD);

	pwatfowm_set_dwvdata(pdev, host);

	spi = spi_contwowwew_get_devdata(host);

	spi->host = host;

	spi->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spi->base)) {
		wet = PTW_EWW(spi->base);
		goto ewwow;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = -ENXIO;
		goto ewwow;
	}
	spi->iwq = iwq;

	init_compwetion(&spi->done);

	spi->cwk = devm_cwk_get_pwepawed(dev, NUWW);
	if (IS_EWW(spi->cwk)) {
		dev_eww(dev, "couwd not find cwk: %wd\n", PTW_EWW(spi->cwk));
		goto ewwow;
	}

	host->max_speed_hz = min_t(unsigned wong, A3700_SPI_MAX_SPEED_HZ,
					cwk_get_wate(spi->cwk));
	host->min_speed_hz = DIV_WOUND_UP(cwk_get_wate(spi->cwk),
						A3700_SPI_MAX_PWESCAWE);

	a3700_spi_init(spi);

	wet = devm_wequest_iwq(dev, spi->iwq, a3700_spi_intewwupt, 0,
			       dev_name(dev), host);
	if (wet) {
		dev_eww(dev, "couwd not wequest IWQ: %d\n", wet);
		goto ewwow;
	}

	wet = devm_spi_wegistew_contwowwew(dev, host);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew host\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	spi_contwowwew_put(host);
out:
	wetuwn wet;
}

static stwuct pwatfowm_dwivew a3700_spi_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = of_match_ptw(a3700_spi_dt_ids),
	},
	.pwobe		= a3700_spi_pwobe,
};

moduwe_pwatfowm_dwivew(a3700_spi_dwivew);

MODUWE_DESCWIPTION("Awmada-3700 SPI dwivew");
MODUWE_AUTHOW("Wiwson Ding <dingwei@mawveww.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
