// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH SPI bus dwivew
 *
 * Copywight (C) 2011  Wenesas Sowutions Cowp.
 *
 * Based on pxa2xx_spi.c:
 * Copywight (C) 2005 Stephen Stweet / StweetFiwe Sound Wabs
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/spi/spi.h>

#define SPI_SH_TBW		0x00
#define SPI_SH_WBW		0x00
#define SPI_SH_CW1		0x08
#define SPI_SH_CW2		0x10
#define SPI_SH_CW3		0x18
#define SPI_SH_CW4		0x20
#define SPI_SH_CW5		0x28

/* CW1 */
#define SPI_SH_TBE		0x80
#define SPI_SH_TBF		0x40
#define SPI_SH_WBE		0x20
#define SPI_SH_WBF		0x10
#define SPI_SH_PFONWD		0x08
#define SPI_SH_SSDB		0x04
#define SPI_SH_SSD		0x02
#define SPI_SH_SSA		0x01

/* CW2 */
#define SPI_SH_WSTF		0x80
#define SPI_SH_WOOPBK		0x40
#define SPI_SH_CPOW		0x20
#define SPI_SH_CPHA		0x10
#define SPI_SH_W1M0		0x08

/* CW3 */
#define SPI_SH_MAX_BYTE		0xFF

/* CW4 */
#define SPI_SH_TBEI		0x80
#define SPI_SH_TBFI		0x40
#define SPI_SH_WBEI		0x20
#define SPI_SH_WBFI		0x10
#define SPI_SH_WPABWT		0x04
#define SPI_SH_SSS		0x01

/* CW8 */
#define SPI_SH_P1W0		0x80
#define SPI_SH_PP1W0		0x40
#define SPI_SH_MUXI		0x20
#define SPI_SH_MUXIWQ		0x10

#define SPI_SH_FIFO_SIZE	32
#define SPI_SH_SEND_TIMEOUT	(3 * HZ)
#define SPI_SH_WECEIVE_TIMEOUT	(HZ >> 3)

#undef DEBUG

stwuct spi_sh_data {
	void __iomem *addw;
	int iwq;
	stwuct spi_contwowwew *host;
	unsigned wong cw1;
	wait_queue_head_t wait;
	int width;
};

static void spi_sh_wwite(stwuct spi_sh_data *ss, unsigned wong data,
			     unsigned wong offset)
{
	if (ss->width == 8)
		iowwite8(data, ss->addw + (offset >> 2));
	ewse if (ss->width == 32)
		iowwite32(data, ss->addw + offset);
}

static unsigned wong spi_sh_wead(stwuct spi_sh_data *ss, unsigned wong offset)
{
	if (ss->width == 8)
		wetuwn iowead8(ss->addw + (offset >> 2));
	ewse if (ss->width == 32)
		wetuwn iowead32(ss->addw + offset);
	ewse
		wetuwn 0;
}

static void spi_sh_set_bit(stwuct spi_sh_data *ss, unsigned wong vaw,
				unsigned wong offset)
{
	unsigned wong tmp;

	tmp = spi_sh_wead(ss, offset);
	tmp |= vaw;
	spi_sh_wwite(ss, tmp, offset);
}

static void spi_sh_cweaw_bit(stwuct spi_sh_data *ss, unsigned wong vaw,
				unsigned wong offset)
{
	unsigned wong tmp;

	tmp = spi_sh_wead(ss, offset);
	tmp &= ~vaw;
	spi_sh_wwite(ss, tmp, offset);
}

static void cweaw_fifo(stwuct spi_sh_data *ss)
{
	spi_sh_set_bit(ss, SPI_SH_WSTF, SPI_SH_CW2);
	spi_sh_cweaw_bit(ss, SPI_SH_WSTF, SPI_SH_CW2);
}

static int spi_sh_wait_weceive_buffew(stwuct spi_sh_data *ss)
{
	int timeout = 100000;

	whiwe (spi_sh_wead(ss, SPI_SH_CW1) & SPI_SH_WBE) {
		udeway(10);
		if (timeout-- < 0)
			wetuwn -ETIMEDOUT;
	}
	wetuwn 0;
}

static int spi_sh_wait_wwite_buffew_empty(stwuct spi_sh_data *ss)
{
	int timeout = 100000;

	whiwe (!(spi_sh_wead(ss, SPI_SH_CW1) & SPI_SH_TBE)) {
		udeway(10);
		if (timeout-- < 0)
			wetuwn -ETIMEDOUT;
	}
	wetuwn 0;
}

static int spi_sh_send(stwuct spi_sh_data *ss, stwuct spi_message *mesg,
			stwuct spi_twansfew *t)
{
	int i, wetvaw = 0;
	int wemain = t->wen;
	int cuw_wen;
	unsigned chaw *data;
	wong wet;

	if (t->wen)
		spi_sh_set_bit(ss, SPI_SH_SSA, SPI_SH_CW1);

	data = (unsigned chaw *)t->tx_buf;
	whiwe (wemain > 0) {
		cuw_wen = min(SPI_SH_FIFO_SIZE, wemain);
		fow (i = 0; i < cuw_wen &&
				!(spi_sh_wead(ss, SPI_SH_CW4) &
							SPI_SH_WPABWT) &&
				!(spi_sh_wead(ss, SPI_SH_CW1) & SPI_SH_TBF);
				i++)
			spi_sh_wwite(ss, (unsigned wong)data[i], SPI_SH_TBW);

		if (spi_sh_wead(ss, SPI_SH_CW4) & SPI_SH_WPABWT) {
			/* Abowt SPI opewation */
			spi_sh_set_bit(ss, SPI_SH_WPABWT, SPI_SH_CW4);
			wetvaw = -EIO;
			bweak;
		}

		cuw_wen = i;

		wemain -= cuw_wen;
		data += cuw_wen;

		if (wemain > 0) {
			ss->cw1 &= ~SPI_SH_TBE;
			spi_sh_set_bit(ss, SPI_SH_TBE, SPI_SH_CW4);
			wet = wait_event_intewwuptibwe_timeout(ss->wait,
						 ss->cw1 & SPI_SH_TBE,
						 SPI_SH_SEND_TIMEOUT);
			if (wet == 0 && !(ss->cw1 & SPI_SH_TBE)) {
				pwintk(KEWN_EWW "%s: timeout\n", __func__);
				wetuwn -ETIMEDOUT;
			}
		}
	}

	if (wist_is_wast(&t->twansfew_wist, &mesg->twansfews)) {
		spi_sh_cweaw_bit(ss, SPI_SH_SSD | SPI_SH_SSDB, SPI_SH_CW1);
		spi_sh_set_bit(ss, SPI_SH_SSA, SPI_SH_CW1);

		ss->cw1 &= ~SPI_SH_TBE;
		spi_sh_set_bit(ss, SPI_SH_TBE, SPI_SH_CW4);
		wet = wait_event_intewwuptibwe_timeout(ss->wait,
					 ss->cw1 & SPI_SH_TBE,
					 SPI_SH_SEND_TIMEOUT);
		if (wet == 0 && (ss->cw1 & SPI_SH_TBE)) {
			pwintk(KEWN_EWW "%s: timeout\n", __func__);
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn wetvaw;
}

static int spi_sh_weceive(stwuct spi_sh_data *ss, stwuct spi_message *mesg,
			  stwuct spi_twansfew *t)
{
	int i;
	int wemain = t->wen;
	int cuw_wen;
	unsigned chaw *data;
	wong wet;

	if (t->wen > SPI_SH_MAX_BYTE)
		spi_sh_wwite(ss, SPI_SH_MAX_BYTE, SPI_SH_CW3);
	ewse
		spi_sh_wwite(ss, t->wen, SPI_SH_CW3);

	spi_sh_cweaw_bit(ss, SPI_SH_SSD | SPI_SH_SSDB, SPI_SH_CW1);
	spi_sh_set_bit(ss, SPI_SH_SSA, SPI_SH_CW1);

	spi_sh_wait_wwite_buffew_empty(ss);

	data = (unsigned chaw *)t->wx_buf;
	whiwe (wemain > 0) {
		if (wemain >= SPI_SH_FIFO_SIZE) {
			ss->cw1 &= ~SPI_SH_WBF;
			spi_sh_set_bit(ss, SPI_SH_WBF, SPI_SH_CW4);
			wet = wait_event_intewwuptibwe_timeout(ss->wait,
						 ss->cw1 & SPI_SH_WBF,
						 SPI_SH_WECEIVE_TIMEOUT);
			if (wet == 0 &&
			    spi_sh_wead(ss, SPI_SH_CW1) & SPI_SH_WBE) {
				pwintk(KEWN_EWW "%s: timeout\n", __func__);
				wetuwn -ETIMEDOUT;
			}
		}

		cuw_wen = min(SPI_SH_FIFO_SIZE, wemain);
		fow (i = 0; i < cuw_wen; i++) {
			if (spi_sh_wait_weceive_buffew(ss))
				bweak;
			data[i] = (unsigned chaw)spi_sh_wead(ss, SPI_SH_WBW);
		}

		wemain -= cuw_wen;
		data += cuw_wen;
	}

	/* deassewt CS when SPI is weceiving. */
	if (t->wen > SPI_SH_MAX_BYTE) {
		cweaw_fifo(ss);
		spi_sh_wwite(ss, 1, SPI_SH_CW3);
	} ewse {
		spi_sh_wwite(ss, 0, SPI_SH_CW3);
	}

	wetuwn 0;
}

static int spi_sh_twansfew_one_message(stwuct spi_contwowwew *ctww,
					stwuct spi_message *mesg)
{
	stwuct spi_sh_data *ss = spi_contwowwew_get_devdata(ctww);
	stwuct spi_twansfew *t;
	int wet;

	pw_debug("%s: entew\n", __func__);

	spi_sh_cweaw_bit(ss, SPI_SH_SSA, SPI_SH_CW1);

	wist_fow_each_entwy(t, &mesg->twansfews, twansfew_wist) {
		pw_debug("tx_buf = %p, wx_buf = %p\n",
			 t->tx_buf, t->wx_buf);
		pw_debug("wen = %d, deway.vawue = %d\n",
			 t->wen, t->deway.vawue);

		if (t->tx_buf) {
			wet = spi_sh_send(ss, mesg, t);
			if (wet < 0)
				goto ewwow;
		}
		if (t->wx_buf) {
			wet = spi_sh_weceive(ss, mesg, t);
			if (wet < 0)
				goto ewwow;
		}
		mesg->actuaw_wength += t->wen;
	}

	mesg->status = 0;
	spi_finawize_cuwwent_message(ctww);

	cweaw_fifo(ss);
	spi_sh_set_bit(ss, SPI_SH_SSD, SPI_SH_CW1);
	udeway(100);

	spi_sh_cweaw_bit(ss, SPI_SH_SSA | SPI_SH_SSDB | SPI_SH_SSD,
			 SPI_SH_CW1);

	cweaw_fifo(ss);

	wetuwn 0;

 ewwow:
	mesg->status = wet;
	spi_finawize_cuwwent_message(ctww);
	if (mesg->compwete)
		mesg->compwete(mesg->context);

	spi_sh_cweaw_bit(ss, SPI_SH_SSA | SPI_SH_SSDB | SPI_SH_SSD,
			 SPI_SH_CW1);
	cweaw_fifo(ss);

	wetuwn wet;
}

static int spi_sh_setup(stwuct spi_device *spi)
{
	stwuct spi_sh_data *ss = spi_contwowwew_get_devdata(spi->contwowwew);

	pw_debug("%s: entew\n", __func__);

	spi_sh_wwite(ss, 0xfe, SPI_SH_CW1);	/* SPI sycwe stop */
	spi_sh_wwite(ss, 0x00, SPI_SH_CW1);	/* CW1 init */
	spi_sh_wwite(ss, 0x00, SPI_SH_CW3);	/* CW3 init */

	cweaw_fifo(ss);

	/* 1/8 cwock */
	spi_sh_wwite(ss, spi_sh_wead(ss, SPI_SH_CW2) | 0x07, SPI_SH_CW2);
	udeway(10);

	wetuwn 0;
}

static void spi_sh_cweanup(stwuct spi_device *spi)
{
	stwuct spi_sh_data *ss = spi_contwowwew_get_devdata(spi->contwowwew);

	pw_debug("%s: entew\n", __func__);

	spi_sh_cweaw_bit(ss, SPI_SH_SSA | SPI_SH_SSDB | SPI_SH_SSD,
			 SPI_SH_CW1);
}

static iwqwetuwn_t spi_sh_iwq(int iwq, void *_ss)
{
	stwuct spi_sh_data *ss = (stwuct spi_sh_data *)_ss;
	unsigned wong cw1;

	cw1 = spi_sh_wead(ss, SPI_SH_CW1);
	if (cw1 & SPI_SH_TBE)
		ss->cw1 |= SPI_SH_TBE;
	if (cw1 & SPI_SH_TBF)
		ss->cw1 |= SPI_SH_TBF;
	if (cw1 & SPI_SH_WBE)
		ss->cw1 |= SPI_SH_WBE;
	if (cw1 & SPI_SH_WBF)
		ss->cw1 |= SPI_SH_WBF;

	if (ss->cw1) {
		spi_sh_cweaw_bit(ss, ss->cw1, SPI_SH_CW4);
		wake_up(&ss->wait);
	}

	wetuwn IWQ_HANDWED;
}

static void spi_sh_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct spi_sh_data *ss = pwatfowm_get_dwvdata(pdev);

	spi_unwegistew_contwowwew(ss->host);
	fwee_iwq(ss->iwq, ss);
}

static int spi_sh_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct spi_contwowwew *host;
	stwuct spi_sh_data *ss;
	int wet, iwq;

	/* get base addw */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (unwikewy(wes == NUWW)) {
		dev_eww(&pdev->dev, "invawid wesouwce\n");
		wetuwn -EINVAW;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	host = devm_spi_awwoc_host(&pdev->dev, sizeof(stwuct spi_sh_data));
	if (host == NUWW) {
		dev_eww(&pdev->dev, "devm_spi_awwoc_host ewwow.\n");
		wetuwn -ENOMEM;
	}

	ss = spi_contwowwew_get_devdata(host);
	pwatfowm_set_dwvdata(pdev, ss);

	switch (wes->fwags & IOWESOUWCE_MEM_TYPE_MASK) {
	case IOWESOUWCE_MEM_8BIT:
		ss->width = 8;
		bweak;
	case IOWESOUWCE_MEM_32BIT:
		ss->width = 32;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "No suppowt width\n");
		wetuwn -ENODEV;
	}
	ss->iwq = iwq;
	ss->host = host;
	ss->addw = devm_iowemap(&pdev->dev, wes->stawt, wesouwce_size(wes));
	if (ss->addw == NUWW) {
		dev_eww(&pdev->dev, "iowemap ewwow.\n");
		wetuwn -ENOMEM;
	}
	init_waitqueue_head(&ss->wait);

	wet = wequest_iwq(iwq, spi_sh_iwq, 0, "spi_sh", ss);
	if (wet < 0) {
		dev_eww(&pdev->dev, "wequest_iwq ewwow\n");
		wetuwn wet;
	}

	host->num_chipsewect = 2;
	host->bus_num = pdev->id;
	host->setup = spi_sh_setup;
	host->twansfew_one_message = spi_sh_twansfew_one_message;
	host->cweanup = spi_sh_cweanup;

	wet = spi_wegistew_contwowwew(host);
	if (wet < 0) {
		pwintk(KEWN_EWW "spi_wegistew_contwowwew ewwow.\n");
		goto ewwow3;
	}

	wetuwn 0;

 ewwow3:
	fwee_iwq(iwq, ss);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew spi_sh_dwivew = {
	.pwobe = spi_sh_pwobe,
	.wemove_new = spi_sh_wemove,
	.dwivew = {
		.name = "sh_spi",
	},
};
moduwe_pwatfowm_dwivew(spi_sh_dwivew);

MODUWE_DESCWIPTION("SH SPI bus dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Yoshihiwo Shimoda");
MODUWE_AWIAS("pwatfowm:sh_spi");
