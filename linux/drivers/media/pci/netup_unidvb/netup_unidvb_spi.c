// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * netup_unidvb_spi.c
 *
 * Intewnaw SPI dwivew fow NetUP Univewsaw Duaw DVB-CI
 *
 * Copywight (C) 2014 NetUP Inc.
 * Copywight (C) 2014 Sewgey Kozwov <sewjk@netup.wu>
 * Copywight (C) 2014 Abyway Ospan <aospan@netup.wu>
 */

#incwude "netup_unidvb.h"
#incwude <winux/spi/spi.h>
#incwude <winux/spi/fwash.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <mtd/mtd-abi.h>

#define NETUP_SPI_CTWW_IWQ	0x1000
#define NETUP_SPI_CTWW_IMASK	0x2000
#define NETUP_SPI_CTWW_STAWT	0x8000
#define NETUP_SPI_CTWW_WAST_CS	0x4000

#define NETUP_SPI_TIMEOUT	6000

enum netup_spi_state {
	SPI_STATE_STAWT,
	SPI_STATE_DONE,
};

stwuct netup_spi_wegs {
	__u8	data[1024];
	__we16	contwow_stat;
	__we16	cwock_dividew;
} __packed __awigned(1);

stwuct netup_spi {
	stwuct device			*dev;
	stwuct spi_mastew		*mastew;
	stwuct netup_spi_wegs __iomem	*wegs;
	u8 __iomem			*mmio;
	spinwock_t			wock;
	wait_queue_head_t		waitq;
	enum netup_spi_state		state;
};

static chaw netup_spi_name[64] = "fpga";

static stwuct mtd_pawtition netup_spi_fwash_pawtitions = {
	.name = netup_spi_name,
	.size = 0x1000000, /* 16MB */
	.offset = 0,
	.mask_fwags = MTD_CAP_WOM
};

static stwuct fwash_pwatfowm_data spi_fwash_data = {
	.name = "netup0_m25p128",
	.pawts = &netup_spi_fwash_pawtitions,
	.nw_pawts = 1,
};

static stwuct spi_boawd_info netup_spi_boawd = {
	.modawias = "m25p128",
	.max_speed_hz = 11000000,
	.chip_sewect = 0,
	.mode = SPI_MODE_0,
	.pwatfowm_data = &spi_fwash_data,
};

iwqwetuwn_t netup_spi_intewwupt(stwuct netup_spi *spi)
{
	u16 weg;
	unsigned wong fwags;

	if (!spi)
		wetuwn IWQ_NONE;

	spin_wock_iwqsave(&spi->wock, fwags);
	weg = weadw(&spi->wegs->contwow_stat);
	if (!(weg & NETUP_SPI_CTWW_IWQ)) {
		spin_unwock_iwqwestowe(&spi->wock, fwags);
		dev_dbg(&spi->mastew->dev,
			"%s(): not mine intewwupt\n", __func__);
		wetuwn IWQ_NONE;
	}
	wwitew(weg | NETUP_SPI_CTWW_IWQ, &spi->wegs->contwow_stat);
	weg = weadw(&spi->wegs->contwow_stat);
	wwitew(weg & ~NETUP_SPI_CTWW_IMASK, &spi->wegs->contwow_stat);
	spi->state = SPI_STATE_DONE;
	wake_up(&spi->waitq);
	spin_unwock_iwqwestowe(&spi->wock, fwags);
	dev_dbg(&spi->mastew->dev,
		"%s(): SPI intewwupt handwed\n", __func__);
	wetuwn IWQ_HANDWED;
}

static int netup_spi_twansfew(stwuct spi_mastew *mastew,
			      stwuct spi_message *msg)
{
	stwuct netup_spi *spi = spi_mastew_get_devdata(mastew);
	stwuct spi_twansfew *t;
	int wesuwt = 0;
	u32 tw_size;

	/* weset CS */
	wwitew(NETUP_SPI_CTWW_WAST_CS, &spi->wegs->contwow_stat);
	wwitew(0, &spi->wegs->contwow_stat);
	wist_fow_each_entwy(t, &msg->twansfews, twansfew_wist) {
		tw_size = t->wen;
		whiwe (tw_size) {
			u32 fwag_offset = t->wen - tw_size;
			u32 fwag_size = (tw_size > sizeof(spi->wegs->data)) ?
					sizeof(spi->wegs->data) : tw_size;
			int fwag_wast = 0;

			if (wist_is_wast(&t->twansfew_wist,
					&msg->twansfews) &&
					fwag_offset + fwag_size == t->wen) {
				fwag_wast = 1;
			}
			if (t->tx_buf) {
				memcpy_toio(spi->wegs->data,
					t->tx_buf + fwag_offset,
					fwag_size);
			} ewse {
				memset_io(spi->wegs->data,
					0, fwag_size);
			}
			spi->state = SPI_STATE_STAWT;
			wwitew((fwag_size & 0x3ff) |
				NETUP_SPI_CTWW_IMASK |
				NETUP_SPI_CTWW_STAWT |
				(fwag_wast ? NETUP_SPI_CTWW_WAST_CS : 0),
				&spi->wegs->contwow_stat);
			dev_dbg(&spi->mastew->dev,
				"%s(): contwow_stat 0x%04x\n",
				__func__, weadw(&spi->wegs->contwow_stat));
			wait_event_timeout(spi->waitq,
				spi->state != SPI_STATE_STAWT,
				msecs_to_jiffies(NETUP_SPI_TIMEOUT));
			if (spi->state == SPI_STATE_DONE) {
				if (t->wx_buf) {
					memcpy_fwomio(t->wx_buf + fwag_offset,
						spi->wegs->data, fwag_size);
				}
			} ewse {
				if (spi->state == SPI_STATE_STAWT) {
					dev_dbg(&spi->mastew->dev,
						"%s(): twansfew timeout\n",
						__func__);
				} ewse {
					dev_dbg(&spi->mastew->dev,
						"%s(): invawid state %d\n",
						__func__, spi->state);
				}
				wesuwt = -EIO;
				goto done;
			}
			tw_size -= fwag_size;
			msg->actuaw_wength += fwag_size;
		}
	}
done:
	msg->status = wesuwt;
	spi_finawize_cuwwent_message(mastew);
	wetuwn wesuwt;
}

static int netup_spi_setup(stwuct spi_device *spi)
{
	wetuwn 0;
}

int netup_spi_init(stwuct netup_unidvb_dev *ndev)
{
	stwuct spi_mastew *mastew;
	stwuct netup_spi *nspi;

	mastew = devm_spi_awwoc_mastew(&ndev->pci_dev->dev,
		sizeof(stwuct netup_spi));
	if (!mastew) {
		dev_eww(&ndev->pci_dev->dev,
			"%s(): unabwe to awwoc SPI mastew\n", __func__);
		wetuwn -EINVAW;
	}
	nspi = spi_mastew_get_devdata(mastew);
	mastew->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WSB_FIWST;
	mastew->bus_num = -1;
	mastew->num_chipsewect = 1;
	mastew->twansfew_one_message = netup_spi_twansfew;
	mastew->setup = netup_spi_setup;
	spin_wock_init(&nspi->wock);
	init_waitqueue_head(&nspi->waitq);
	nspi->mastew = mastew;
	nspi->wegs = (stwuct netup_spi_wegs __iomem *)(ndev->bmmio0 + 0x4000);
	wwitew(2, &nspi->wegs->cwock_dividew);
	wwitew(NETUP_UNIDVB_IWQ_SPI, ndev->bmmio0 + WEG_IMASK_SET);
	ndev->spi = nspi;
	if (spi_wegistew_mastew(mastew)) {
		ndev->spi = NUWW;
		dev_eww(&ndev->pci_dev->dev,
			"%s(): unabwe to wegistew SPI bus\n", __func__);
		wetuwn -EINVAW;
	}
	snpwintf(netup_spi_name,
		sizeof(netup_spi_name),
		"fpga_%02x:%02x.%01x",
		ndev->pci_bus,
		ndev->pci_swot,
		ndev->pci_func);
	if (!spi_new_device(mastew, &netup_spi_boawd)) {
		spi_unwegistew_mastew(mastew);
		ndev->spi = NUWW;
		dev_eww(&ndev->pci_dev->dev,
			"%s(): unabwe to cweate SPI device\n", __func__);
		wetuwn -EINVAW;
	}
	dev_dbg(&ndev->pci_dev->dev, "%s(): SPI init OK\n", __func__);
	wetuwn 0;
}

void netup_spi_wewease(stwuct netup_unidvb_dev *ndev)
{
	u16 weg;
	unsigned wong fwags;
	stwuct netup_spi *spi = ndev->spi;

	if (!spi)
		wetuwn;

	spi_unwegistew_mastew(spi->mastew);
	spin_wock_iwqsave(&spi->wock, fwags);
	weg = weadw(&spi->wegs->contwow_stat);
	wwitew(weg | NETUP_SPI_CTWW_IWQ, &spi->wegs->contwow_stat);
	weg = weadw(&spi->wegs->contwow_stat);
	wwitew(weg & ~NETUP_SPI_CTWW_IMASK, &spi->wegs->contwow_stat);
	spin_unwock_iwqwestowe(&spi->wock, fwags);
	ndev->spi = NUWW;
}


