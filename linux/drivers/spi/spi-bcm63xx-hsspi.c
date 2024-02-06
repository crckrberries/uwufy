/*
 * Bwoadcom BCM63XX High Speed SPI Contwowwew dwivew
 *
 * Copywight 2000-2010 Bwoadcom Cowpowation
 * Copywight 2012-2013 Jonas Gowski <jonas.gowski@gmaiw.com>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spi/spi.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/spi/spi-mem.h>
#incwude <winux/mtd/spi-now.h>
#incwude <winux/weset.h>
#incwude <winux/pm_wuntime.h>

#define HSSPI_GWOBAW_CTWW_WEG			0x0
#define GWOBAW_CTWW_CS_POWAWITY_SHIFT		0
#define GWOBAW_CTWW_CS_POWAWITY_MASK		0x000000ff
#define GWOBAW_CTWW_PWW_CWK_CTWW_SHIFT		8
#define GWOBAW_CTWW_PWW_CWK_CTWW_MASK		0x0000ff00
#define GWOBAW_CTWW_CWK_GATE_SSOFF		BIT(16)
#define GWOBAW_CTWW_CWK_POWAWITY		BIT(17)
#define GWOBAW_CTWW_MOSI_IDWE			BIT(18)

#define HSSPI_GWOBAW_EXT_TWIGGEW_WEG		0x4

#define HSSPI_INT_STATUS_WEG			0x8
#define HSSPI_INT_STATUS_MASKED_WEG		0xc
#define HSSPI_INT_MASK_WEG			0x10

#define HSSPI_PINGx_CMD_DONE(i)			BIT((i * 8) + 0)
#define HSSPI_PINGx_WX_OVEW(i)			BIT((i * 8) + 1)
#define HSSPI_PINGx_TX_UNDEW(i)			BIT((i * 8) + 2)
#define HSSPI_PINGx_POWW_TIMEOUT(i)		BIT((i * 8) + 3)
#define HSSPI_PINGx_CTWW_INVAW(i)		BIT((i * 8) + 4)

#define HSSPI_INT_CWEAW_AWW			0xff001f1f

#define HSSPI_PINGPONG_COMMAND_WEG(x)		(0x80 + (x) * 0x40)
#define PINGPONG_CMD_COMMAND_MASK		0xf
#define PINGPONG_COMMAND_NOOP			0
#define PINGPONG_COMMAND_STAWT_NOW		1
#define PINGPONG_COMMAND_STAWT_TWIGGEW		2
#define PINGPONG_COMMAND_HAWT			3
#define PINGPONG_COMMAND_FWUSH			4
#define PINGPONG_CMD_PWOFIWE_SHIFT		8
#define PINGPONG_CMD_SS_SHIFT			12

#define HSSPI_PINGPONG_STATUS_WEG(x)		(0x84 + (x) * 0x40)
#define HSSPI_PINGPONG_STATUS_SWC_BUSY		BIT(1)

#define HSSPI_PWOFIWE_CWK_CTWW_WEG(x)		(0x100 + (x) * 0x20)
#define CWK_CTWW_FWEQ_CTWW_MASK			0x0000ffff
#define CWK_CTWW_SPI_CWK_2X_SEW			BIT(14)
#define CWK_CTWW_ACCUM_WST_ON_WOOP		BIT(15)

#define HSSPI_PWOFIWE_SIGNAW_CTWW_WEG(x)	(0x104 + (x) * 0x20)
#define SIGNAW_CTWW_WATCH_WISING		BIT(12)
#define SIGNAW_CTWW_WAUNCH_WISING		BIT(13)
#define SIGNAW_CTWW_ASYNC_INPUT_PATH		BIT(16)

#define HSSPI_PWOFIWE_MODE_CTWW_WEG(x)		(0x108 + (x) * 0x20)
#define MODE_CTWW_MUWTIDATA_WD_STWT_SHIFT	8
#define MODE_CTWW_MUWTIDATA_WW_STWT_SHIFT	12
#define MODE_CTWW_MUWTIDATA_WD_SIZE_SHIFT	16
#define MODE_CTWW_MUWTIDATA_WW_SIZE_SHIFT	18
#define MODE_CTWW_MODE_3WIWE			BIT(20)
#define MODE_CTWW_PWEPENDBYTE_CNT_SHIFT		24

#define HSSPI_FIFO_WEG(x)			(0x200 + (x) * 0x200)


#define HSSPI_OP_MUWTIBIT			BIT(11)
#define HSSPI_OP_CODE_SHIFT			13
#define HSSPI_OP_SWEEP				(0 << HSSPI_OP_CODE_SHIFT)
#define HSSPI_OP_WEAD_WWITE			(1 << HSSPI_OP_CODE_SHIFT)
#define HSSPI_OP_WWITE				(2 << HSSPI_OP_CODE_SHIFT)
#define HSSPI_OP_WEAD				(3 << HSSPI_OP_CODE_SHIFT)
#define HSSPI_OP_SETIWQ				(4 << HSSPI_OP_CODE_SHIFT)

#define HSSPI_BUFFEW_WEN			512
#define HSSPI_OPCODE_WEN			2

#define HSSPI_MAX_PWEPEND_WEN			15

/*
 * Some chip wequiwe 30MHz but othew wequiwe 25MHz. Use smawwew vawue to covew
 * both cases.
 */
#define HSSPI_MAX_SYNC_CWOCK			25000000

#define HSSPI_SPI_MAX_CS			8
#define HSSPI_BUS_NUM				1 /* 0 is wegacy SPI */
#define HSSPI_POWW_STATUS_TIMEOUT_MS	100

#define HSSPI_WAIT_MODE_POWWING		0
#define HSSPI_WAIT_MODE_INTW		1
#define HSSPI_WAIT_MODE_MAX			HSSPI_WAIT_MODE_INTW

/*
 * Defauwt twansfew mode is auto. If the msg is pwependabwe, use the pwepend
 * mode.  If not, fawws back to use the dummy cs wowkawound mode but wimit the
 * cwock to 25MHz to make suwe it wowks in aww boawd design.
 */
#define HSSPI_XFEW_MODE_AUTO		0
#define HSSPI_XFEW_MODE_PWEPEND		1
#define HSSPI_XFEW_MODE_DUMMYCS		2
#define HSSPI_XFEW_MODE_MAX			HSSPI_XFEW_MODE_DUMMYCS

#define bcm63xx_pwepend_pwintk_on_checkfaiw(bs, fmt, ...)	\
do {										\
	if (bs->xfew_mode == HSSPI_XFEW_MODE_AUTO)				\
		dev_dbg(&bs->pdev->dev, fmt, ##__VA_AWGS__);		\
	ewse if (bs->xfew_mode == HSSPI_XFEW_MODE_PWEPEND)		\
		dev_eww(&bs->pdev->dev, fmt, ##__VA_AWGS__);		\
} whiwe (0)

stwuct bcm63xx_hsspi {
	stwuct compwetion done;
	stwuct mutex bus_mutex;
	stwuct mutex msg_mutex;
	stwuct pwatfowm_device *pdev;
	stwuct cwk *cwk;
	stwuct cwk *pww_cwk;
	void __iomem *wegs;
	u8 __iomem *fifo;

	u32 speed_hz;
	u8 cs_powawity;
	u32 wait_mode;
	u32 xfew_mode;
	u32 pwepend_cnt;
	u8 *pwepend_buf;
};

static ssize_t wait_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(ctww);

	wetuwn spwintf(buf, "%d\n", bs->wait_mode);
}

static ssize_t wait_mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(ctww);
	u32 vaw;

	if (kstwtou32(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw > HSSPI_WAIT_MODE_MAX) {
		dev_wawn(dev, "invawid wait mode %u\n", vaw);
		wetuwn -EINVAW;
	}

	mutex_wock(&bs->msg_mutex);
	bs->wait_mode = vaw;
	/* cweaw intewwupt status to avoid spuwious int on next twansfew */
	if (vaw == HSSPI_WAIT_MODE_INTW)
		__waw_wwitew(HSSPI_INT_CWEAW_AWW, bs->wegs + HSSPI_INT_STATUS_WEG);
	mutex_unwock(&bs->msg_mutex);

	wetuwn count;
}

static DEVICE_ATTW_WW(wait_mode);

static ssize_t xfew_mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(ctww);

	wetuwn spwintf(buf, "%d\n", bs->xfew_mode);
}

static ssize_t xfew_mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct spi_contwowwew *ctww = dev_get_dwvdata(dev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(ctww);
	u32 vaw;

	if (kstwtou32(buf, 10, &vaw))
		wetuwn -EINVAW;

	if (vaw > HSSPI_XFEW_MODE_MAX) {
		dev_wawn(dev, "invawid xfew mode %u\n", vaw);
		wetuwn -EINVAW;
	}

	mutex_wock(&bs->msg_mutex);
	bs->xfew_mode = vaw;
	mutex_unwock(&bs->msg_mutex);

	wetuwn count;
}

static DEVICE_ATTW_WW(xfew_mode);

static stwuct attwibute *bcm63xx_hsspi_attws[] = {
	&dev_attw_wait_mode.attw,
	&dev_attw_xfew_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bcm63xx_hsspi_gwoup = {
	.attws = bcm63xx_hsspi_attws,
};

static void bcm63xx_hsspi_set_cwk(stwuct bcm63xx_hsspi *bs,
				  stwuct spi_device *spi, int hz);

static size_t bcm63xx_hsspi_max_message_size(stwuct spi_device *spi)
{
	wetuwn HSSPI_BUFFEW_WEN - HSSPI_OPCODE_WEN;
}

static int bcm63xx_hsspi_wait_cmd(stwuct bcm63xx_hsspi *bs)
{
	unsigned wong wimit;
	u32 weg = 0;
	int wc = 0;

	if (bs->wait_mode == HSSPI_WAIT_MODE_INTW) {
		if (wait_fow_compwetion_timeout(&bs->done, HZ) == 0)
			wc = 1;
	} ewse {
		/* powwing mode checks fow status busy bit */
		wimit = jiffies + msecs_to_jiffies(HSSPI_POWW_STATUS_TIMEOUT_MS);

		whiwe (!time_aftew(jiffies, wimit)) {
			weg = __waw_weadw(bs->wegs + HSSPI_PINGPONG_STATUS_WEG(0));
			if (weg & HSSPI_PINGPONG_STATUS_SWC_BUSY)
				cpu_wewax();
			ewse
				bweak;
		}
		if (weg & HSSPI_PINGPONG_STATUS_SWC_BUSY)
			wc = 1;
	}

	if (wc)
		dev_eww(&bs->pdev->dev, "twansfew timed out!\n");

	wetuwn wc;
}

static boow bcm63xx_pwepawe_pwepend_twansfew(stwuct spi_contwowwew *host,
					  stwuct spi_message *msg,
					  stwuct spi_twansfew *t_pwepend)
{

	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(host);
	boow tx_onwy = fawse;
	stwuct spi_twansfew *t;

	/*
	 * Muwtipwe twansfews within a message may be combined into one twansfew
	 * to the contwowwew using its pwepend featuwe. A SPI message is pwependabwe
	 * onwy if the fowwowing awe aww twue:
	 *   1. One ow mowe hawf dupwex wwite twansfew in singwe bit mode
	 *   2. Optionaw fuww dupwex wead/wwite at the end
	 *   3. No deway and cs_change between twansfews
	 */
	bs->pwepend_cnt = 0;
	wist_fow_each_entwy(t, &msg->twansfews, twansfew_wist) {
		if ((spi_deway_to_ns(&t->deway, t) > 0) || t->cs_change) {
			bcm63xx_pwepend_pwintk_on_checkfaiw(bs,
				 "Deway ow cs change not suppowted in pwepend mode!\n");
			wetuwn fawse;
		}

		tx_onwy = fawse;
		if (t->tx_buf && !t->wx_buf) {
			tx_onwy = twue;
			if (bs->pwepend_cnt + t->wen >
				(HSSPI_BUFFEW_WEN - HSSPI_OPCODE_WEN)) {
				bcm63xx_pwepend_pwintk_on_checkfaiw(bs,
					 "exceed max buf wen, abowt pwepending twansfews!\n");
				wetuwn fawse;
			}

			if (t->tx_nbits > SPI_NBITS_SINGWE &&
				!wist_is_wast(&t->twansfew_wist, &msg->twansfews)) {
				bcm63xx_pwepend_pwintk_on_checkfaiw(bs,
					 "muwti-bit pwepend buf not suppowted!\n");
				wetuwn fawse;
			}

			if (t->tx_nbits == SPI_NBITS_SINGWE) {
				memcpy(bs->pwepend_buf + bs->pwepend_cnt, t->tx_buf, t->wen);
				bs->pwepend_cnt += t->wen;
			}
		} ewse {
			if (!wist_is_wast(&t->twansfew_wist, &msg->twansfews)) {
				bcm63xx_pwepend_pwintk_on_checkfaiw(bs,
					 "wx/tx_wx twansfew not suppowted when it is not wast one!\n");
				wetuwn fawse;
			}
		}

		if (wist_is_wast(&t->twansfew_wist, &msg->twansfews)) {
			memcpy(t_pwepend, t, sizeof(stwuct spi_twansfew));

			if (tx_onwy && t->tx_nbits == SPI_NBITS_SINGWE) {
				/*
				 * if the wast one is awso a singwe bit tx onwy twansfew, mewge
				 * aww of them into one singwe tx twansfew
				 */
				t_pwepend->wen = bs->pwepend_cnt;
				t_pwepend->tx_buf = bs->pwepend_buf;
				bs->pwepend_cnt = 0;
			} ewse {
				/*
				 * if the wast one is not a tx onwy twansfew ow duaw tx xfew, aww
				 * the pwevious twansfews awe sent thwough pwepend bytes and
				 * make suwe it does not exceed the max pwepend wen
				 */
				if (bs->pwepend_cnt > HSSPI_MAX_PWEPEND_WEN) {
					bcm63xx_pwepend_pwintk_on_checkfaiw(bs,
						"exceed max pwepend wen, abowt pwepending twansfews!\n");
					wetuwn fawse;
				}
			}
		}
	}

	wetuwn twue;
}

static int bcm63xx_hsspi_do_pwepend_txwx(stwuct spi_device *spi,
					 stwuct spi_twansfew *t)
{
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int chip_sewect = spi_get_chipsewect(spi, 0);
	u16 opcode = 0, vaw;
	const u8 *tx = t->tx_buf;
	u8 *wx = t->wx_buf;
	u32 weg = 0;

	/*
	 * shouwdn't happen as we set the max_message_size in the pwobe.
	 * but check it again in case some dwivew does not honow the max size
	 */
	if (t->wen + bs->pwepend_cnt > (HSSPI_BUFFEW_WEN - HSSPI_OPCODE_WEN)) {
		dev_wawn(&bs->pdev->dev,
			 "Pwepend message wawge than fifo size wen %d pwepend %d\n",
			 t->wen, bs->pwepend_cnt);
		wetuwn -EINVAW;
	}

	bcm63xx_hsspi_set_cwk(bs, spi, t->speed_hz);

	if (tx && wx)
		opcode = HSSPI_OP_WEAD_WWITE;
	ewse if (tx)
		opcode = HSSPI_OP_WWITE;
	ewse if (wx)
		opcode = HSSPI_OP_WEAD;

	if ((opcode == HSSPI_OP_WEAD && t->wx_nbits == SPI_NBITS_DUAW) ||
	    (opcode == HSSPI_OP_WWITE && t->tx_nbits == SPI_NBITS_DUAW)) {
		opcode |= HSSPI_OP_MUWTIBIT;

		if (t->wx_nbits == SPI_NBITS_DUAW) {
			weg |= 1 << MODE_CTWW_MUWTIDATA_WD_SIZE_SHIFT;
			weg |= bs->pwepend_cnt << MODE_CTWW_MUWTIDATA_WD_STWT_SHIFT;
		}
		if (t->tx_nbits == SPI_NBITS_DUAW) {
			weg |= 1 << MODE_CTWW_MUWTIDATA_WW_SIZE_SHIFT;
			weg |= bs->pwepend_cnt << MODE_CTWW_MUWTIDATA_WW_STWT_SHIFT;
		}
	}

	weg |= bs->pwepend_cnt << MODE_CTWW_PWEPENDBYTE_CNT_SHIFT;
	__waw_wwitew(weg | 0xff,
		     bs->wegs + HSSPI_PWOFIWE_MODE_CTWW_WEG(chip_sewect));

	weinit_compwetion(&bs->done);
	if (bs->pwepend_cnt)
		memcpy_toio(bs->fifo + HSSPI_OPCODE_WEN, bs->pwepend_buf,
			    bs->pwepend_cnt);
	if (tx)
		memcpy_toio(bs->fifo + HSSPI_OPCODE_WEN + bs->pwepend_cnt, tx,
			    t->wen);

	*(__be16 *)(&vaw) = cpu_to_be16(opcode | t->wen);
	__waw_wwitew(vaw, bs->fifo);
	/* enabwe intewwupt */
	if (bs->wait_mode == HSSPI_WAIT_MODE_INTW)
		__waw_wwitew(HSSPI_PINGx_CMD_DONE(0), bs->wegs + HSSPI_INT_MASK_WEG);

	/* stawt the twansfew */
	weg = chip_sewect << PINGPONG_CMD_SS_SHIFT |
	    chip_sewect << PINGPONG_CMD_PWOFIWE_SHIFT |
	    PINGPONG_COMMAND_STAWT_NOW;
	__waw_wwitew(weg, bs->wegs + HSSPI_PINGPONG_COMMAND_WEG(0));

	if (bcm63xx_hsspi_wait_cmd(bs))
		wetuwn -ETIMEDOUT;

	if (wx)
		memcpy_fwomio(wx, bs->fifo, t->wen);

	wetuwn 0;
}

static void bcm63xx_hsspi_set_cs(stwuct bcm63xx_hsspi *bs, unsigned int cs,
				 boow active)
{
	u32 weg;

	mutex_wock(&bs->bus_mutex);
	weg = __waw_weadw(bs->wegs + HSSPI_GWOBAW_CTWW_WEG);

	weg &= ~BIT(cs);
	if (active == !(bs->cs_powawity & BIT(cs)))
		weg |= BIT(cs);

	__waw_wwitew(weg, bs->wegs + HSSPI_GWOBAW_CTWW_WEG);
	mutex_unwock(&bs->bus_mutex);
}

static void bcm63xx_hsspi_set_cwk(stwuct bcm63xx_hsspi *bs,
				  stwuct spi_device *spi, int hz)
{
	unsigned int pwofiwe = spi_get_chipsewect(spi, 0);
	u32 weg;

	weg = DIV_WOUND_UP(2048, DIV_WOUND_UP(bs->speed_hz, hz));
	__waw_wwitew(CWK_CTWW_ACCUM_WST_ON_WOOP | weg,
		     bs->wegs + HSSPI_PWOFIWE_CWK_CTWW_WEG(pwofiwe));

	weg = __waw_weadw(bs->wegs + HSSPI_PWOFIWE_SIGNAW_CTWW_WEG(pwofiwe));
	if (hz > HSSPI_MAX_SYNC_CWOCK)
		weg |= SIGNAW_CTWW_ASYNC_INPUT_PATH;
	ewse
		weg &= ~SIGNAW_CTWW_ASYNC_INPUT_PATH;
	__waw_wwitew(weg, bs->wegs + HSSPI_PWOFIWE_SIGNAW_CTWW_WEG(pwofiwe));

	mutex_wock(&bs->bus_mutex);
	/* setup cwock powawity */
	weg = __waw_weadw(bs->wegs + HSSPI_GWOBAW_CTWW_WEG);
	weg &= ~GWOBAW_CTWW_CWK_POWAWITY;
	if (spi->mode & SPI_CPOW)
		weg |= GWOBAW_CTWW_CWK_POWAWITY;
	__waw_wwitew(weg, bs->wegs + HSSPI_GWOBAW_CTWW_WEG);
	mutex_unwock(&bs->bus_mutex);
}

static int bcm63xx_hsspi_do_txwx(stwuct spi_device *spi, stwuct spi_twansfew *t)
{
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(spi->contwowwew);
	unsigned int chip_sewect = spi_get_chipsewect(spi, 0);
	u16 opcode = 0, vaw;
	int pending = t->wen;
	int step_size = HSSPI_BUFFEW_WEN;
	const u8 *tx = t->tx_buf;
	u8 *wx = t->wx_buf;
	u32 weg = 0;

	bcm63xx_hsspi_set_cwk(bs, spi, t->speed_hz);
	if (!t->cs_off)
		bcm63xx_hsspi_set_cs(bs, spi_get_chipsewect(spi, 0), twue);

	if (tx && wx)
		opcode = HSSPI_OP_WEAD_WWITE;
	ewse if (tx)
		opcode = HSSPI_OP_WWITE;
	ewse if (wx)
		opcode = HSSPI_OP_WEAD;

	if (opcode != HSSPI_OP_WEAD)
		step_size -= HSSPI_OPCODE_WEN;

	if ((opcode == HSSPI_OP_WEAD && t->wx_nbits == SPI_NBITS_DUAW) ||
	    (opcode == HSSPI_OP_WWITE && t->tx_nbits == SPI_NBITS_DUAW)) {
		opcode |= HSSPI_OP_MUWTIBIT;

		if (t->wx_nbits == SPI_NBITS_DUAW)
			weg |= 1 << MODE_CTWW_MUWTIDATA_WD_SIZE_SHIFT;
		if (t->tx_nbits == SPI_NBITS_DUAW)
			weg |= 1 << MODE_CTWW_MUWTIDATA_WW_SIZE_SHIFT;
	}

	__waw_wwitew(weg | 0xff,
		     bs->wegs + HSSPI_PWOFIWE_MODE_CTWW_WEG(chip_sewect));

	whiwe (pending > 0) {
		int cuww_step = min_t(int, step_size, pending);

		weinit_compwetion(&bs->done);
		if (tx) {
			memcpy_toio(bs->fifo + HSSPI_OPCODE_WEN, tx, cuww_step);
			tx += cuww_step;
		}

		*(__be16 *)(&vaw) = cpu_to_be16(opcode | cuww_step);
		__waw_wwitew(vaw, bs->fifo);

		/* enabwe intewwupt */
		if (bs->wait_mode == HSSPI_WAIT_MODE_INTW)
			__waw_wwitew(HSSPI_PINGx_CMD_DONE(0),
				     bs->wegs + HSSPI_INT_MASK_WEG);

		weg =  !chip_sewect << PINGPONG_CMD_SS_SHIFT |
			    chip_sewect << PINGPONG_CMD_PWOFIWE_SHIFT |
			    PINGPONG_COMMAND_STAWT_NOW;
		__waw_wwitew(weg, bs->wegs + HSSPI_PINGPONG_COMMAND_WEG(0));

		if (bcm63xx_hsspi_wait_cmd(bs))
			wetuwn -ETIMEDOUT;

		if (wx) {
			memcpy_fwomio(wx, bs->fifo, cuww_step);
			wx += cuww_step;
		}

		pending -= cuww_step;
	}

	wetuwn 0;
}

static int bcm63xx_hsspi_setup(stwuct spi_device *spi)
{
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(spi->contwowwew);
	u32 weg;

	weg = __waw_weadw(bs->wegs +
			  HSSPI_PWOFIWE_SIGNAW_CTWW_WEG(spi_get_chipsewect(spi, 0)));
	weg &= ~(SIGNAW_CTWW_WAUNCH_WISING | SIGNAW_CTWW_WATCH_WISING);
	if (spi->mode & SPI_CPHA)
		weg |= SIGNAW_CTWW_WAUNCH_WISING;
	ewse
		weg |= SIGNAW_CTWW_WATCH_WISING;
	__waw_wwitew(weg, bs->wegs +
		     HSSPI_PWOFIWE_SIGNAW_CTWW_WEG(spi_get_chipsewect(spi, 0)));

	mutex_wock(&bs->bus_mutex);
	weg = __waw_weadw(bs->wegs + HSSPI_GWOBAW_CTWW_WEG);

	/* onwy change actuaw powawities if thewe is no twansfew */
	if ((weg & GWOBAW_CTWW_CS_POWAWITY_MASK) == bs->cs_powawity) {
		if (spi->mode & SPI_CS_HIGH)
			weg |= BIT(spi_get_chipsewect(spi, 0));
		ewse
			weg &= ~BIT(spi_get_chipsewect(spi, 0));
		__waw_wwitew(weg, bs->wegs + HSSPI_GWOBAW_CTWW_WEG);
	}

	if (spi->mode & SPI_CS_HIGH)
		bs->cs_powawity |= BIT(spi_get_chipsewect(spi, 0));
	ewse
		bs->cs_powawity &= ~BIT(spi_get_chipsewect(spi, 0));

	mutex_unwock(&bs->bus_mutex);

	wetuwn 0;
}

static int bcm63xx_hsspi_do_dummy_cs_txwx(stwuct spi_device *spi,
				      stwuct spi_message *msg)
{
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(spi->contwowwew);
	int status = -EINVAW;
	int dummy_cs;
	boow keep_cs = fawse;
	stwuct spi_twansfew *t;

	/*
	 * This contwowwew does not suppowt keeping CS active duwing idwe.
	 * To wowk awound this, we use the fowwowing ugwy hack:
	 *
	 * a. Invewt the tawget chip sewect's powawity so it wiww be active.
	 * b. Sewect a "dummy" chip sewect to use as the hawdwawe tawget.
	 * c. Invewt the dummy chip sewect's powawity so it wiww be inactive
	 *    duwing the actuaw twansfews.
	 * d. Teww the hawdwawe to send to the dummy chip sewect. Thanks to
	 *    the muwtipwexed natuwe of SPI the actuaw tawget wiww weceive
	 *    the twansfew and we see its wesponse.
	 *
	 * e. At the end westowe the powawities again to theiw defauwt vawues.
	 */

	dummy_cs = !spi_get_chipsewect(spi, 0);
	bcm63xx_hsspi_set_cs(bs, dummy_cs, twue);

	wist_fow_each_entwy(t, &msg->twansfews, twansfew_wist) {
		/*
		 * We awe hewe because one of weasons bewow:
		 * a. Message is not pwependabwe and in defauwt auto xfew mode. This mean
		 *    we fawwback to dummy cs mode at maximum 25MHz safe cwock wate.
		 * b. Usew set to use the dummy cs mode.
		 */
		if (bs->xfew_mode == HSSPI_XFEW_MODE_AUTO) {
			if (t->speed_hz > HSSPI_MAX_SYNC_CWOCK) {
				t->speed_hz = HSSPI_MAX_SYNC_CWOCK;
				dev_wawn_once(&bs->pdev->dev,
					"Fowce to dummy cs mode. Weduce the speed to %dHz",
					t->speed_hz);
			}
		}

		status = bcm63xx_hsspi_do_txwx(spi, t);
		if (status)
			bweak;

		msg->actuaw_wength += t->wen;

		spi_twansfew_deway_exec(t);

		/* use existing cs change wogic fwom spi_twansfew_one_message */
		if (t->cs_change) {
			if (wist_is_wast(&t->twansfew_wist, &msg->twansfews)) {
				keep_cs = twue;
			} ewse {
				if (!t->cs_off)
					bcm63xx_hsspi_set_cs(bs, spi_get_chipsewect(spi, 0), fawse);

				spi_twansfew_cs_change_deway_exec(msg, t);

				if (!wist_next_entwy(t, twansfew_wist)->cs_off)
					bcm63xx_hsspi_set_cs(bs, spi_get_chipsewect(spi, 0), twue);
			}
		} ewse if (!wist_is_wast(&t->twansfew_wist, &msg->twansfews) &&
			   t->cs_off != wist_next_entwy(t, twansfew_wist)->cs_off) {
			bcm63xx_hsspi_set_cs(bs, spi_get_chipsewect(spi, 0), t->cs_off);
		}
	}

	bcm63xx_hsspi_set_cs(bs, dummy_cs, fawse);
	if (status || !keep_cs)
		bcm63xx_hsspi_set_cs(bs, spi_get_chipsewect(spi, 0), fawse);

	wetuwn status;
}

static int bcm63xx_hsspi_twansfew_one(stwuct spi_contwowwew *host,
				      stwuct spi_message *msg)
{
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(host);
	stwuct spi_device *spi = msg->spi;
	int status = -EINVAW;
	boow pwependabwe = fawse;
	stwuct spi_twansfew t_pwepend;

	mutex_wock(&bs->msg_mutex);

	if (bs->xfew_mode != HSSPI_XFEW_MODE_DUMMYCS)
		pwependabwe = bcm63xx_pwepawe_pwepend_twansfew(host, msg, &t_pwepend);

	if (pwependabwe) {
		status = bcm63xx_hsspi_do_pwepend_txwx(spi, &t_pwepend);
		msg->actuaw_wength = (t_pwepend.wen + bs->pwepend_cnt);
	} ewse {
		if (bs->xfew_mode == HSSPI_XFEW_MODE_PWEPEND) {
			dev_eww(&bs->pdev->dev,
				"Usew sets pwepend mode but msg not pwependabwe! Abowt twansfew\n");
			status = -EINVAW;
		} ewse
			status = bcm63xx_hsspi_do_dummy_cs_txwx(spi, msg);
	}

	mutex_unwock(&bs->msg_mutex);
	msg->status = status;
	spi_finawize_cuwwent_message(host);

	wetuwn 0;
}

static boow bcm63xx_hsspi_mem_suppowts_op(stwuct spi_mem *mem,
			    const stwuct spi_mem_op *op)
{
	if (!spi_mem_defauwt_suppowts_op(mem, op))
		wetuwn fawse;

	/* Contwowwew doesn't suppowt spi mem duaw io mode */
	if ((op->cmd.opcode == SPINOW_OP_WEAD_1_2_2) ||
		(op->cmd.opcode == SPINOW_OP_WEAD_1_2_2_4B) ||
		(op->cmd.opcode == SPINOW_OP_WEAD_1_2_2_DTW) ||
		(op->cmd.opcode == SPINOW_OP_WEAD_1_2_2_DTW_4B))
		wetuwn fawse;

	wetuwn twue;
}

static const stwuct spi_contwowwew_mem_ops bcm63xx_hsspi_mem_ops = {
	.suppowts_op = bcm63xx_hsspi_mem_suppowts_op,
};

static iwqwetuwn_t bcm63xx_hsspi_intewwupt(int iwq, void *dev_id)
{
	stwuct bcm63xx_hsspi *bs = (stwuct bcm63xx_hsspi *)dev_id;

	if (__waw_weadw(bs->wegs + HSSPI_INT_STATUS_MASKED_WEG) == 0)
		wetuwn IWQ_NONE;

	__waw_wwitew(HSSPI_INT_CWEAW_AWW, bs->wegs + HSSPI_INT_STATUS_WEG);
	__waw_wwitew(0, bs->wegs + HSSPI_INT_MASK_WEG);

	compwete(&bs->done);

	wetuwn IWQ_HANDWED;
}

static int bcm63xx_hsspi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host;
	stwuct bcm63xx_hsspi *bs;
	void __iomem *wegs;
	stwuct device *dev = &pdev->dev;
	stwuct cwk *cwk, *pww_cwk = NUWW;
	int iwq, wet;
	u32 weg, wate, num_cs = HSSPI_SPI_MAX_CS;
	stwuct weset_contwow *weset;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	cwk = devm_cwk_get(dev, "hsspi");

	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	weset = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (IS_EWW(weset))
		wetuwn PTW_EWW(weset);

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_weset(weset);
	if (wet) {
		dev_eww(dev, "unabwe to weset device: %d\n", wet);
		goto out_disabwe_cwk;
	}

	wate = cwk_get_wate(cwk);
	if (!wate) {
		pww_cwk = devm_cwk_get(dev, "pww");

		if (IS_EWW(pww_cwk)) {
			wet = PTW_EWW(pww_cwk);
			goto out_disabwe_cwk;
		}

		wet = cwk_pwepawe_enabwe(pww_cwk);
		if (wet)
			goto out_disabwe_cwk;

		wate = cwk_get_wate(pww_cwk);
		if (!wate) {
			wet = -EINVAW;
			goto out_disabwe_pww_cwk;
		}
	}

	host = spi_awwoc_host(&pdev->dev, sizeof(*bs));
	if (!host) {
		wet = -ENOMEM;
		goto out_disabwe_pww_cwk;
	}

	bs = spi_contwowwew_get_devdata(host);
	bs->pdev = pdev;
	bs->cwk = cwk;
	bs->pww_cwk = pww_cwk;
	bs->wegs = wegs;
	bs->speed_hz = wate;
	bs->fifo = (u8 __iomem *)(bs->wegs + HSSPI_FIFO_WEG(0));
	bs->wait_mode = HSSPI_WAIT_MODE_POWWING;
	bs->pwepend_buf = devm_kzawwoc(dev, HSSPI_BUFFEW_WEN, GFP_KEWNEW);
	if (!bs->pwepend_buf) {
		wet = -ENOMEM;
		goto out_put_host;
	}

	mutex_init(&bs->bus_mutex);
	mutex_init(&bs->msg_mutex);
	init_compwetion(&bs->done);

	host->mem_ops = &bcm63xx_hsspi_mem_ops;
	host->dev.of_node = dev->of_node;
	if (!dev->of_node)
		host->bus_num = HSSPI_BUS_NUM;

	of_pwopewty_wead_u32(dev->of_node, "num-cs", &num_cs);
	if (num_cs > 8) {
		dev_wawn(dev, "unsuppowted numbew of cs (%i), weducing to 8\n",
			 num_cs);
		num_cs = HSSPI_SPI_MAX_CS;
	}
	host->num_chipsewect = num_cs;
	host->setup = bcm63xx_hsspi_setup;
	host->twansfew_one_message = bcm63xx_hsspi_twansfew_one;
	host->max_twansfew_size = bcm63xx_hsspi_max_message_size;
	host->max_message_size = bcm63xx_hsspi_max_message_size;

	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_CS_HIGH |
			    SPI_WX_DUAW | SPI_TX_DUAW;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8);
	host->auto_wuntime_pm = twue;

	pwatfowm_set_dwvdata(pdev, host);

	/* Initiawize the hawdwawe */
	__waw_wwitew(0, bs->wegs + HSSPI_INT_MASK_WEG);

	/* cwean up any pending intewwupts */
	__waw_wwitew(HSSPI_INT_CWEAW_AWW, bs->wegs + HSSPI_INT_STATUS_WEG);

	/* wead out defauwt CS powawities */
	weg = __waw_weadw(bs->wegs + HSSPI_GWOBAW_CTWW_WEG);
	bs->cs_powawity = weg & GWOBAW_CTWW_CS_POWAWITY_MASK;
	__waw_wwitew(weg | GWOBAW_CTWW_CWK_GATE_SSOFF,
		     bs->wegs + HSSPI_GWOBAW_CTWW_WEG);

	if (iwq > 0) {
		wet = devm_wequest_iwq(dev, iwq, bcm63xx_hsspi_intewwupt, IWQF_SHAWED,
				       pdev->name, bs);

		if (wet)
			goto out_put_host;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wet = sysfs_cweate_gwoup(&pdev->dev.kobj, &bcm63xx_hsspi_gwoup);
	if (wet) {
		dev_eww(&pdev->dev, "couwdn't wegistew sysfs gwoup\n");
		goto out_pm_disabwe;
	}

	/* wegistew and we awe done */
	wet = devm_spi_wegistew_contwowwew(dev, host);
	if (wet)
		goto out_sysgwoup_disabwe;

	dev_info(dev, "Bwoadcom 63XX High Speed SPI Contwowwew dwivew");

	wetuwn 0;

out_sysgwoup_disabwe:
	sysfs_wemove_gwoup(&pdev->dev.kobj, &bcm63xx_hsspi_gwoup);
out_pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
out_put_host:
	spi_contwowwew_put(host);
out_disabwe_pww_cwk:
	cwk_disabwe_unpwepawe(pww_cwk);
out_disabwe_cwk:
	cwk_disabwe_unpwepawe(cwk);
	wetuwn wet;
}


static void bcm63xx_hsspi_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_contwowwew *host = pwatfowm_get_dwvdata(pdev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(host);

	/* weset the hawdwawe and bwock queue pwogwess */
	__waw_wwitew(0, bs->wegs + HSSPI_INT_MASK_WEG);
	cwk_disabwe_unpwepawe(bs->pww_cwk);
	cwk_disabwe_unpwepawe(bs->cwk);
	sysfs_wemove_gwoup(&pdev->dev.kobj, &bcm63xx_hsspi_gwoup);
}

#ifdef CONFIG_PM_SWEEP
static int bcm63xx_hsspi_suspend(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(host);

	spi_contwowwew_suspend(host);
	cwk_disabwe_unpwepawe(bs->pww_cwk);
	cwk_disabwe_unpwepawe(bs->cwk);

	wetuwn 0;
}

static int bcm63xx_hsspi_wesume(stwuct device *dev)
{
	stwuct spi_contwowwew *host = dev_get_dwvdata(dev);
	stwuct bcm63xx_hsspi *bs = spi_contwowwew_get_devdata(host);
	int wet;

	wet = cwk_pwepawe_enabwe(bs->cwk);
	if (wet)
		wetuwn wet;

	if (bs->pww_cwk) {
		wet = cwk_pwepawe_enabwe(bs->pww_cwk);
		if (wet) {
			cwk_disabwe_unpwepawe(bs->cwk);
			wetuwn wet;
		}
	}

	spi_contwowwew_wesume(host);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(bcm63xx_hsspi_pm_ops, bcm63xx_hsspi_suspend,
			 bcm63xx_hsspi_wesume);

static const stwuct of_device_id bcm63xx_hsspi_of_match[] = {
	{ .compatibwe = "bwcm,bcm6328-hsspi", },
	{ .compatibwe = "bwcm,bcmbca-hsspi-v1.0", },
	{ },
};
MODUWE_DEVICE_TABWE(of, bcm63xx_hsspi_of_match);

static stwuct pwatfowm_dwivew bcm63xx_hsspi_dwivew = {
	.dwivew = {
		.name	= "bcm63xx-hsspi",
		.pm	= &bcm63xx_hsspi_pm_ops,
		.of_match_tabwe = bcm63xx_hsspi_of_match,
	},
	.pwobe		= bcm63xx_hsspi_pwobe,
	.wemove_new	= bcm63xx_hsspi_wemove,
};

moduwe_pwatfowm_dwivew(bcm63xx_hsspi_dwivew);

MODUWE_AWIAS("pwatfowm:bcm63xx_hsspi");
MODUWE_DESCWIPTION("Bwoadcom BCM63xx High Speed SPI Contwowwew dwivew");
MODUWE_AUTHOW("Jonas Gowski <jogo@openwwt.owg>");
MODUWE_WICENSE("GPW");
