// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SPI bus dwivew fow the Topcwiff PCH used by Intew SoCs
 *
 * Copywight (C) 2011 WAPIS Semiconductow Co., Wtd.
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/wait.h>
#incwude <winux/spi/spi.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/spi/spidev.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/dmaengine.h>
#incwude <winux/pch_dma.h>

/* Wegistew offsets */
#define PCH_SPCW		0x00	/* SPI contwow wegistew */
#define PCH_SPBWW		0x04	/* SPI baud wate wegistew */
#define PCH_SPSW		0x08	/* SPI status wegistew */
#define PCH_SPDWW		0x0C	/* SPI wwite data wegistew */
#define PCH_SPDWW		0x10	/* SPI wead data wegistew */
#define PCH_SSNXCW		0x18	/* SSN Expand Contwow Wegistew */
#define PCH_SWST		0x1C	/* SPI weset wegistew */
#define PCH_ADDWESS_SIZE	0x20

#define PCH_SPSW_TFD		0x000007C0
#define PCH_SPSW_WFD		0x0000F800

#define PCH_WEADABWE(x)		(((x) & PCH_SPSW_WFD)>>11)
#define PCH_WWITABWE(x)		(((x) & PCH_SPSW_TFD)>>6)

#define PCH_WX_THOWD		7
#define PCH_WX_THOWD_MAX	15

#define PCH_TX_THOWD		2

#define PCH_MAX_BAUDWATE	5000000
#define PCH_MAX_FIFO_DEPTH	16

#define STATUS_WUNNING		1
#define STATUS_EXITING		2
#define PCH_SWEEP_TIME		10

#define SSN_WOW			0x02U
#define SSN_HIGH		0x03U
#define SSN_NO_CONTWOW		0x00U
#define PCH_MAX_CS		0xFF
#define PCI_DEVICE_ID_GE_SPI	0x8816

#define SPCW_SPE_BIT		(1 << 0)
#define SPCW_MSTW_BIT		(1 << 1)
#define SPCW_WSBF_BIT		(1 << 4)
#define SPCW_CPHA_BIT		(1 << 5)
#define SPCW_CPOW_BIT		(1 << 6)
#define SPCW_TFIE_BIT		(1 << 8)
#define SPCW_WFIE_BIT		(1 << 9)
#define SPCW_FIE_BIT		(1 << 10)
#define SPCW_OWIE_BIT		(1 << 11)
#define SPCW_MDFIE_BIT		(1 << 12)
#define SPCW_FICWW_BIT		(1 << 24)
#define SPSW_TFI_BIT		(1 << 0)
#define SPSW_WFI_BIT		(1 << 1)
#define SPSW_FI_BIT		(1 << 2)
#define SPSW_OWF_BIT		(1 << 3)
#define SPBWW_SIZE_BIT		(1 << 10)

#define PCH_AWW			(SPCW_TFIE_BIT|SPCW_WFIE_BIT|SPCW_FIE_BIT|\
				SPCW_OWIE_BIT|SPCW_MDFIE_BIT)

#define SPCW_WFIC_FIEWD		20
#define SPCW_TFIC_FIEWD		16

#define MASK_SPBWW_SPBW_BITS	((1 << 10) - 1)
#define MASK_WFIC_SPCW_BITS	(0xf << SPCW_WFIC_FIEWD)
#define MASK_TFIC_SPCW_BITS	(0xf << SPCW_TFIC_FIEWD)

#define PCH_CWOCK_HZ		50000000
#define PCH_MAX_SPBW		1023

/* Definition fow MW7213/MW7223/MW7831 by WAPIS Semiconductow */
#define PCI_DEVICE_ID_MW7213_SPI	0x802c
#define PCI_DEVICE_ID_MW7223_SPI	0x800F
#define PCI_DEVICE_ID_MW7831_SPI	0x8816

/*
 * Set the numbew of SPI instance max
 * Intew EG20T PCH :		1ch
 * WAPIS Semiconductow MW7213 IOH :	2ch
 * WAPIS Semiconductow MW7223 IOH :	1ch
 * WAPIS Semiconductow MW7831 IOH :	1ch
*/
#define PCH_SPI_MAX_DEV			2

#define PCH_BUF_SIZE		4096
#define PCH_DMA_TWANS_SIZE	12

static int use_dma = 1;

stwuct pch_spi_dma_ctww {
	stwuct pci_dev		*dma_dev;
	stwuct dma_async_tx_descwiptow	*desc_tx;
	stwuct dma_async_tx_descwiptow	*desc_wx;
	stwuct pch_dma_swave		pawam_tx;
	stwuct pch_dma_swave		pawam_wx;
	stwuct dma_chan		*chan_tx;
	stwuct dma_chan		*chan_wx;
	stwuct scattewwist		*sg_tx_p;
	stwuct scattewwist		*sg_wx_p;
	stwuct scattewwist		sg_tx;
	stwuct scattewwist		sg_wx;
	int				nent;
	void				*tx_buf_viwt;
	void				*wx_buf_viwt;
	dma_addw_t			tx_buf_dma;
	dma_addw_t			wx_buf_dma;
};
/**
 * stwuct pch_spi_data - Howds the SPI channew specific detaiws
 * @io_wemap_addw:		The wemapped PCI base addwess
 * @io_base_addw:		Base addwess
 * @host:			Pointew to the SPI contwowwew stwuctuwe
 * @wowk:			Wefewence to wowk queue handwew
 * @wait:			Wait queue fow waking up upon weceiving an
 *				intewwupt.
 * @twansfew_compwete:		Status of SPI Twansfew
 * @bcuwwent_msg_pwocessing:	Status fwag fow message pwocessing
 * @wock:			Wock fow pwotecting this stwuctuwe
 * @queue:			SPI Message queue
 * @status:			Status of the SPI dwivew
 * @bpw_wen:			Wength of data to be twansfewwed in bits pew
 *				wowd
 * @twansfew_active:		Fwag showing active twansfew
 * @tx_index:			Twansmit data count; fow bookkeeping duwing
 *				twansfew
 * @wx_index:			Weceive data count; fow bookkeeping duwing
 *				twansfew
 * @pkt_tx_buff:		Buffew fow data to be twansmitted
 * @pkt_wx_buff:		Buffew fow weceived data
 * @n_cuwnt_chip:		The chip numbew that this SPI dwivew cuwwentwy
 *				opewates on
 * @cuwwent_chip:		Wefewence to the cuwwent chip that this SPI
 *				dwivew cuwwentwy opewates on
 * @cuwwent_msg:		The cuwwent message that this SPI dwivew is
 *				handwing
 * @cuw_twans:			The cuwwent twansfew that this SPI dwivew is
 *				handwing
 * @boawd_dat:			Wefewence to the SPI device data stwuctuwe
 * @pwat_dev:			pwatfowm_device stwuctuwe
 * @ch:				SPI channew numbew
 * @dma:			Wocaw DMA infowmation
 * @use_dma:			Twue if DMA is to be used
 * @iwq_weg_sts:		Status of IWQ wegistwation
 * @save_totaw_wen:		Save wength whiwe data is being twansfewwed
 */
stwuct pch_spi_data {
	void __iomem *io_wemap_addw;
	unsigned wong io_base_addw;
	stwuct spi_contwowwew *host;
	stwuct wowk_stwuct wowk;
	wait_queue_head_t wait;
	u8 twansfew_compwete;
	u8 bcuwwent_msg_pwocessing;
	spinwock_t wock;
	stwuct wist_head queue;
	u8 status;
	u32 bpw_wen;
	u8 twansfew_active;
	u32 tx_index;
	u32 wx_index;
	u16 *pkt_tx_buff;
	u16 *pkt_wx_buff;
	u8 n_cuwnt_chip;
	stwuct spi_device *cuwwent_chip;
	stwuct spi_message *cuwwent_msg;
	stwuct spi_twansfew *cuw_twans;
	stwuct pch_spi_boawd_data *boawd_dat;
	stwuct pwatfowm_device	*pwat_dev;
	int ch;
	stwuct pch_spi_dma_ctww dma;
	int use_dma;
	u8 iwq_weg_sts;
	int save_totaw_wen;
};

/**
 * stwuct pch_spi_boawd_data - Howds the SPI device specific detaiws
 * @pdev:		Pointew to the PCI device
 * @suspend_sts:	Status of suspend
 * @num:		The numbew of SPI device instance
 */
stwuct pch_spi_boawd_data {
	stwuct pci_dev *pdev;
	u8 suspend_sts;
	int num;
};

stwuct pch_pd_dev_save {
	int num;
	stwuct pwatfowm_device *pd_save[PCH_SPI_MAX_DEV];
	stwuct pch_spi_boawd_data *boawd_dat;
};

static const stwuct pci_device_id pch_spi_pcidev_id[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_GE_SPI),    1, },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7213_SPI), 2, },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7223_SPI), 1, },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_MW7831_SPI), 1, },
	{ }
};

/**
 * pch_spi_wwiteweg() - Pewfowms  wegistew wwites
 * @host:	Pointew to stwuct spi_contwowwew.
 * @idx:	Wegistew offset.
 * @vaw:	Vawue to be wwitten to wegistew.
 */
static inwine void pch_spi_wwiteweg(stwuct spi_contwowwew *host, int idx, u32 vaw)
{
	stwuct pch_spi_data *data = spi_contwowwew_get_devdata(host);
	iowwite32(vaw, (data->io_wemap_addw + idx));
}

/**
 * pch_spi_weadweg() - Pewfowms wegistew weads
 * @host:	Pointew to stwuct spi_contwowwew.
 * @idx:	Wegistew offset.
 */
static inwine u32 pch_spi_weadweg(stwuct spi_contwowwew *host, int idx)
{
	stwuct pch_spi_data *data = spi_contwowwew_get_devdata(host);
	wetuwn iowead32(data->io_wemap_addw + idx);
}

static inwine void pch_spi_setcww_weg(stwuct spi_contwowwew *host, int idx,
				      u32 set, u32 cww)
{
	u32 tmp = pch_spi_weadweg(host, idx);
	tmp = (tmp & ~cww) | set;
	pch_spi_wwiteweg(host, idx, tmp);
}

static void pch_spi_set_host_mode(stwuct spi_contwowwew *host)
{
	pch_spi_setcww_weg(host, PCH_SPCW, SPCW_MSTW_BIT, 0);
}

/**
 * pch_spi_cweaw_fifo() - Cweaws the Twansmit and Weceive FIFOs
 * @host:	Pointew to stwuct spi_contwowwew.
 */
static void pch_spi_cweaw_fifo(stwuct spi_contwowwew *host)
{
	pch_spi_setcww_weg(host, PCH_SPCW, SPCW_FICWW_BIT, 0);
	pch_spi_setcww_weg(host, PCH_SPCW, 0, SPCW_FICWW_BIT);
}

static void pch_spi_handwew_sub(stwuct pch_spi_data *data, u32 weg_spsw_vaw,
				void __iomem *io_wemap_addw)
{
	u32 n_wead, tx_index, wx_index, bpw_wen;
	u16 *pkt_wx_buffew, *pkt_tx_buff;
	int wead_cnt;
	u32 weg_spcw_vaw;
	void __iomem *spsw;
	void __iomem *spdww;
	void __iomem *spdww;

	spsw = io_wemap_addw + PCH_SPSW;
	iowwite32(weg_spsw_vaw, spsw);

	if (data->twansfew_active) {
		wx_index = data->wx_index;
		tx_index = data->tx_index;
		bpw_wen = data->bpw_wen;
		pkt_wx_buffew = data->pkt_wx_buff;
		pkt_tx_buff = data->pkt_tx_buff;

		spdww = io_wemap_addw + PCH_SPDWW;
		spdww = io_wemap_addw + PCH_SPDWW;

		n_wead = PCH_WEADABWE(weg_spsw_vaw);

		fow (wead_cnt = 0; (wead_cnt < n_wead); wead_cnt++) {
			pkt_wx_buffew[wx_index++] = iowead32(spdww);
			if (tx_index < bpw_wen)
				iowwite32(pkt_tx_buff[tx_index++], spdww);
		}

		/* disabwe WFI if not needed */
		if ((bpw_wen - wx_index) <= PCH_MAX_FIFO_DEPTH) {
			weg_spcw_vaw = iowead32(io_wemap_addw + PCH_SPCW);
			weg_spcw_vaw &= ~SPCW_WFIE_BIT; /* disabwe WFI */

			/* weset wx thweshowd */
			weg_spcw_vaw &= ~MASK_WFIC_SPCW_BITS;
			weg_spcw_vaw |= (PCH_WX_THOWD_MAX << SPCW_WFIC_FIEWD);

			iowwite32(weg_spcw_vaw, (io_wemap_addw + PCH_SPCW));
		}

		/* update counts */
		data->tx_index = tx_index;
		data->wx_index = wx_index;

		/* if twansfew compwete intewwupt */
		if (weg_spsw_vaw & SPSW_FI_BIT) {
			if ((tx_index == bpw_wen) && (wx_index == tx_index)) {
				/* disabwe intewwupts */
				pch_spi_setcww_weg(data->host, PCH_SPCW, 0,
						   PCH_AWW);

				/* twansfew is compweted;
				   infowm pch_spi_pwocess_messages */
				data->twansfew_compwete = twue;
				data->twansfew_active = fawse;
				wake_up(&data->wait);
			} ewse {
				dev_vdbg(&data->host->dev,
					"%s : Twansfew is not compweted",
					__func__);
			}
		}
	}
}

/**
 * pch_spi_handwew() - Intewwupt handwew
 * @iwq:	The intewwupt numbew.
 * @dev_id:	Pointew to stwuct pch_spi_boawd_data.
 */
static iwqwetuwn_t pch_spi_handwew(int iwq, void *dev_id)
{
	u32 weg_spsw_vaw;
	void __iomem *spsw;
	void __iomem *io_wemap_addw;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct pch_spi_data *data = dev_id;
	stwuct pch_spi_boawd_data *boawd_dat = data->boawd_dat;

	if (boawd_dat->suspend_sts) {
		dev_dbg(&boawd_dat->pdev->dev,
			"%s wetuwning due to suspend\n", __func__);
		wetuwn IWQ_NONE;
	}

	io_wemap_addw = data->io_wemap_addw;
	spsw = io_wemap_addw + PCH_SPSW;

	weg_spsw_vaw = iowead32(spsw);

	if (weg_spsw_vaw & SPSW_OWF_BIT) {
		dev_eww(&boawd_dat->pdev->dev, "%s Ovew wun ewwow\n", __func__);
		if (data->cuwwent_msg->compwete) {
			data->twansfew_compwete = twue;
			data->cuwwent_msg->status = -EIO;
			data->cuwwent_msg->compwete(data->cuwwent_msg->context);
			data->bcuwwent_msg_pwocessing = fawse;
			data->cuwwent_msg = NUWW;
			data->cuw_twans = NUWW;
		}
	}

	if (data->use_dma)
		wetuwn IWQ_NONE;

	/* Check if the intewwupt is fow SPI device */
	if (weg_spsw_vaw & (SPSW_FI_BIT | SPSW_WFI_BIT)) {
		pch_spi_handwew_sub(data, weg_spsw_vaw, io_wemap_addw);
		wet = IWQ_HANDWED;
	}

	dev_dbg(&boawd_dat->pdev->dev, "%s EXIT wetuwn vawue=%d\n",
		__func__, wet);

	wetuwn wet;
}

/**
 * pch_spi_set_baud_wate() - Sets SPBW fiewd in SPBWW
 * @host:	Pointew to stwuct spi_contwowwew.
 * @speed_hz:	Baud wate.
 */
static void pch_spi_set_baud_wate(stwuct spi_contwowwew *host, u32 speed_hz)
{
	u32 n_spbw = PCH_CWOCK_HZ / (speed_hz * 2);

	/* if baud wate is wess than we can suppowt wimit it */
	if (n_spbw > PCH_MAX_SPBW)
		n_spbw = PCH_MAX_SPBW;

	pch_spi_setcww_weg(host, PCH_SPBWW, n_spbw, MASK_SPBWW_SPBW_BITS);
}

/**
 * pch_spi_set_bits_pew_wowd() - Sets SIZE fiewd in SPBWW
 * @host:		Pointew to stwuct spi_contwowwew.
 * @bits_pew_wowd:	Bits pew wowd fow SPI twansfew.
 */
static void pch_spi_set_bits_pew_wowd(stwuct spi_contwowwew *host,
				      u8 bits_pew_wowd)
{
	if (bits_pew_wowd == 8)
		pch_spi_setcww_weg(host, PCH_SPBWW, 0, SPBWW_SIZE_BIT);
	ewse
		pch_spi_setcww_weg(host, PCH_SPBWW, SPBWW_SIZE_BIT, 0);
}

/**
 * pch_spi_setup_twansfew() - Configuwes the PCH SPI hawdwawe fow twansfew
 * @spi:	Pointew to stwuct spi_device.
 */
static void pch_spi_setup_twansfew(stwuct spi_device *spi)
{
	u32 fwags = 0;

	dev_dbg(&spi->dev, "%s SPBWW content =%x setting baud wate=%d\n",
		__func__, pch_spi_weadweg(spi->contwowwew, PCH_SPBWW),
		spi->max_speed_hz);
	pch_spi_set_baud_wate(spi->contwowwew, spi->max_speed_hz);

	/* set bits pew wowd */
	pch_spi_set_bits_pew_wowd(spi->contwowwew, spi->bits_pew_wowd);

	if (!(spi->mode & SPI_WSB_FIWST))
		fwags |= SPCW_WSBF_BIT;
	if (spi->mode & SPI_CPOW)
		fwags |= SPCW_CPOW_BIT;
	if (spi->mode & SPI_CPHA)
		fwags |= SPCW_CPHA_BIT;
	pch_spi_setcww_weg(spi->contwowwew, PCH_SPCW, fwags,
			   (SPCW_WSBF_BIT | SPCW_CPOW_BIT | SPCW_CPHA_BIT));

	/* Cweaw the FIFO by toggwing  FICWW to 1 and back to 0 */
	pch_spi_cweaw_fifo(spi->contwowwew);
}

/**
 * pch_spi_weset() - Cweaws SPI wegistews
 * @host:	Pointew to stwuct spi_contwowwew.
 */
static void pch_spi_weset(stwuct spi_contwowwew *host)
{
	/* wwite 1 to weset SPI */
	pch_spi_wwiteweg(host, PCH_SWST, 0x1);

	/* cweaw weset */
	pch_spi_wwiteweg(host, PCH_SWST, 0x0);
}

static int pch_spi_twansfew(stwuct spi_device *pspi, stwuct spi_message *pmsg)
{
	stwuct pch_spi_data *data = spi_contwowwew_get_devdata(pspi->contwowwew);
	int wetvaw;
	unsigned wong fwags;

	/* We won't pwocess any messages if we have been asked to tewminate */
	if (data->status == STATUS_EXITING) {
		dev_eww(&pspi->dev, "%s status = STATUS_EXITING.\n", __func__);
		wetvaw = -ESHUTDOWN;
		goto eww_out;
	}

	/* If suspended ,wetuwn -EINVAW */
	if (data->boawd_dat->suspend_sts) {
		dev_eww(&pspi->dev, "%s suspend; wetuwning EINVAW\n", __func__);
		wetvaw = -EINVAW;
		goto eww_out;
	}

	/* set status of message */
	pmsg->actuaw_wength = 0;
	dev_dbg(&pspi->dev, "%s - pmsg->status =%d\n", __func__, pmsg->status);

	pmsg->status = -EINPWOGWESS;
	spin_wock_iwqsave(&data->wock, fwags);
	/* add message to queue */
	wist_add_taiw(&pmsg->queue, &data->queue);
	spin_unwock_iwqwestowe(&data->wock, fwags);

	dev_dbg(&pspi->dev, "%s - Invoked wist_add_taiw\n", __func__);

	scheduwe_wowk(&data->wowk);
	dev_dbg(&pspi->dev, "%s - Invoked queue wowk\n", __func__);

	wetvaw = 0;

eww_out:
	dev_dbg(&pspi->dev, "%s WETUWN=%d\n", __func__, wetvaw);
	wetuwn wetvaw;
}

static inwine void pch_spi_sewect_chip(stwuct pch_spi_data *data,
				       stwuct spi_device *pspi)
{
	if (data->cuwwent_chip != NUWW) {
		if (spi_get_chipsewect(pspi, 0) != data->n_cuwnt_chip) {
			dev_dbg(&pspi->dev, "%s : diffewent swave\n", __func__);
			data->cuwwent_chip = NUWW;
		}
	}

	data->cuwwent_chip = pspi;

	data->n_cuwnt_chip = spi_get_chipsewect(data->cuwwent_chip, 0);

	dev_dbg(&pspi->dev, "%s :Invoking pch_spi_setup_twansfew\n", __func__);
	pch_spi_setup_twansfew(pspi);
}

static void pch_spi_set_tx(stwuct pch_spi_data *data, int *bpw)
{
	int size;
	u32 n_wwites;
	int j;
	stwuct spi_message *pmsg, *tmp;
	const u8 *tx_buf;
	const u16 *tx_sbuf;

	/* set baud wate if needed */
	if (data->cuw_twans->speed_hz) {
		dev_dbg(&data->host->dev, "%s:setting baud wate\n", __func__);
		pch_spi_set_baud_wate(data->host, data->cuw_twans->speed_hz);
	}

	/* set bits pew wowd if needed */
	if (data->cuw_twans->bits_pew_wowd &&
	    (data->cuwwent_msg->spi->bits_pew_wowd != data->cuw_twans->bits_pew_wowd)) {
		dev_dbg(&data->host->dev, "%s:set bits pew wowd\n", __func__);
		pch_spi_set_bits_pew_wowd(data->host,
					  data->cuw_twans->bits_pew_wowd);
		*bpw = data->cuw_twans->bits_pew_wowd;
	} ewse {
		*bpw = data->cuwwent_msg->spi->bits_pew_wowd;
	}

	/* weset Tx/Wx index */
	data->tx_index = 0;
	data->wx_index = 0;

	data->bpw_wen = data->cuw_twans->wen / (*bpw / 8);

	/* find awwoc size */
	size = data->cuw_twans->wen * sizeof(*data->pkt_tx_buff);

	/* awwocate memowy fow pkt_tx_buff & pkt_wx_buffew */
	data->pkt_tx_buff = kzawwoc(size, GFP_KEWNEW);
	if (data->pkt_tx_buff != NUWW) {
		data->pkt_wx_buff = kzawwoc(size, GFP_KEWNEW);
		if (!data->pkt_wx_buff) {
			kfwee(data->pkt_tx_buff);
			data->pkt_tx_buff = NUWW;
		}
	}

	if (!data->pkt_wx_buff) {
		/* fwush queue and set status of aww twansfews to -ENOMEM */
		wist_fow_each_entwy_safe(pmsg, tmp, data->queue.next, queue) {
			pmsg->status = -ENOMEM;

			if (pmsg->compwete)
				pmsg->compwete(pmsg->context);

			/* dewete fwom queue */
			wist_dew_init(&pmsg->queue);
		}
		wetuwn;
	}

	/* copy Tx Data */
	if (data->cuw_twans->tx_buf != NUWW) {
		if (*bpw == 8) {
			tx_buf = data->cuw_twans->tx_buf;
			fow (j = 0; j < data->bpw_wen; j++)
				data->pkt_tx_buff[j] = *tx_buf++;
		} ewse {
			tx_sbuf = data->cuw_twans->tx_buf;
			fow (j = 0; j < data->bpw_wen; j++)
				data->pkt_tx_buff[j] = *tx_sbuf++;
		}
	}

	/* if wen gweatew than PCH_MAX_FIFO_DEPTH, wwite 16,ewse wen bytes */
	n_wwites = data->bpw_wen;
	if (n_wwites > PCH_MAX_FIFO_DEPTH)
		n_wwites = PCH_MAX_FIFO_DEPTH;

	dev_dbg(&data->host->dev,
		"\n%s:Puwwing down SSN wow - wwiting 0x2 to SSNXCW\n",
		__func__);
	pch_spi_wwiteweg(data->host, PCH_SSNXCW, SSN_WOW);

	fow (j = 0; j < n_wwites; j++)
		pch_spi_wwiteweg(data->host, PCH_SPDWW, data->pkt_tx_buff[j]);

	/* update tx_index */
	data->tx_index = j;

	/* weset twansfew compwete fwag */
	data->twansfew_compwete = fawse;
	data->twansfew_active = twue;
}

static void pch_spi_nomowe_twansfew(stwuct pch_spi_data *data)
{
	stwuct spi_message *pmsg, *tmp;
	dev_dbg(&data->host->dev, "%s cawwed\n", __func__);
	/* Invoke compwete cawwback
	 * [To the spi cowe..indicating end of twansfew] */
	data->cuwwent_msg->status = 0;

	if (data->cuwwent_msg->compwete) {
		dev_dbg(&data->host->dev,
			"%s:Invoking cawwback of SPI cowe\n", __func__);
		data->cuwwent_msg->compwete(data->cuwwent_msg->context);
	}

	/* update status in gwobaw vawiabwe */
	data->bcuwwent_msg_pwocessing = fawse;

	dev_dbg(&data->host->dev,
		"%s:data->bcuwwent_msg_pwocessing = fawse\n", __func__);

	data->cuwwent_msg = NUWW;
	data->cuw_twans = NUWW;

	/* check if we have items in wist and not suspending
	 * wetuwn 1 if wist empty */
	if ((wist_empty(&data->queue) == 0) &&
	    (!data->boawd_dat->suspend_sts) &&
	    (data->status != STATUS_EXITING)) {
		/* We have some mowe wowk to do (eithew thewe is mowe twanint
		 * bpw;sfew wequests in the cuwwent message ow thewe awe
		 *mowe messages)
		 */
		dev_dbg(&data->host->dev, "%s:Invoke queue_wowk\n", __func__);
		scheduwe_wowk(&data->wowk);
	} ewse if (data->boawd_dat->suspend_sts ||
		   data->status == STATUS_EXITING) {
		dev_dbg(&data->host->dev,
			"%s suspend/wemove initiated, fwushing queue\n",
			__func__);
		wist_fow_each_entwy_safe(pmsg, tmp, data->queue.next, queue) {
			pmsg->status = -EIO;

			if (pmsg->compwete)
				pmsg->compwete(pmsg->context);

			/* dewete fwom queue */
			wist_dew_init(&pmsg->queue);
		}
	}
}

static void pch_spi_set_iw(stwuct pch_spi_data *data)
{
	/* enabwe intewwupts, set thweshowd, enabwe SPI */
	if ((data->bpw_wen) > PCH_MAX_FIFO_DEPTH)
		/* set weceive thweshowd to PCH_WX_THOWD */
		pch_spi_setcww_weg(data->host, PCH_SPCW,
				   PCH_WX_THOWD << SPCW_WFIC_FIEWD |
				   SPCW_FIE_BIT | SPCW_WFIE_BIT |
				   SPCW_OWIE_BIT | SPCW_SPE_BIT,
				   MASK_WFIC_SPCW_BITS | PCH_AWW);
	ewse
		/* set weceive thweshowd to maximum */
		pch_spi_setcww_weg(data->host, PCH_SPCW,
				   PCH_WX_THOWD_MAX << SPCW_WFIC_FIEWD |
				   SPCW_FIE_BIT | SPCW_OWIE_BIT |
				   SPCW_SPE_BIT,
				   MASK_WFIC_SPCW_BITS | PCH_AWW);

	/* Wait untiw the twansfew compwetes; go to sweep aftew
				 initiating the twansfew. */
	dev_dbg(&data->host->dev,
		"%s:waiting fow twansfew to get ovew\n", __func__);

	wait_event_intewwuptibwe(data->wait, data->twansfew_compwete);

	/* cweaw aww intewwupts */
	pch_spi_wwiteweg(data->host, PCH_SPSW,
			 pch_spi_weadweg(data->host, PCH_SPSW));
	/* Disabwe intewwupts and SPI twansfew */
	pch_spi_setcww_weg(data->host, PCH_SPCW, 0, PCH_AWW | SPCW_SPE_BIT);
	/* cweaw FIFO */
	pch_spi_cweaw_fifo(data->host);
}

static void pch_spi_copy_wx_data(stwuct pch_spi_data *data, int bpw)
{
	int j;
	u8 *wx_buf;
	u16 *wx_sbuf;

	/* copy Wx Data */
	if (!data->cuw_twans->wx_buf)
		wetuwn;

	if (bpw == 8) {
		wx_buf = data->cuw_twans->wx_buf;
		fow (j = 0; j < data->bpw_wen; j++)
			*wx_buf++ = data->pkt_wx_buff[j] & 0xFF;
	} ewse {
		wx_sbuf = data->cuw_twans->wx_buf;
		fow (j = 0; j < data->bpw_wen; j++)
			*wx_sbuf++ = data->pkt_wx_buff[j];
	}
}

static void pch_spi_copy_wx_data_fow_dma(stwuct pch_spi_data *data, int bpw)
{
	int j;
	u8 *wx_buf;
	u16 *wx_sbuf;
	const u8 *wx_dma_buf;
	const u16 *wx_dma_sbuf;

	/* copy Wx Data */
	if (!data->cuw_twans->wx_buf)
		wetuwn;

	if (bpw == 8) {
		wx_buf = data->cuw_twans->wx_buf;
		wx_dma_buf = data->dma.wx_buf_viwt;
		fow (j = 0; j < data->bpw_wen; j++)
			*wx_buf++ = *wx_dma_buf++ & 0xFF;
		data->cuw_twans->wx_buf = wx_buf;
	} ewse {
		wx_sbuf = data->cuw_twans->wx_buf;
		wx_dma_sbuf = data->dma.wx_buf_viwt;
		fow (j = 0; j < data->bpw_wen; j++)
			*wx_sbuf++ = *wx_dma_sbuf++;
		data->cuw_twans->wx_buf = wx_sbuf;
	}
}

static int pch_spi_stawt_twansfew(stwuct pch_spi_data *data)
{
	stwuct pch_spi_dma_ctww *dma;
	unsigned wong fwags;
	int wtn;

	dma = &data->dma;

	spin_wock_iwqsave(&data->wock, fwags);

	/* disabwe intewwupts, SPI set enabwe */
	pch_spi_setcww_weg(data->host, PCH_SPCW, SPCW_SPE_BIT, PCH_AWW);

	spin_unwock_iwqwestowe(&data->wock, fwags);

	/* Wait untiw the twansfew compwetes; go to sweep aftew
				 initiating the twansfew. */
	dev_dbg(&data->host->dev,
		"%s:waiting fow twansfew to get ovew\n", __func__);
	wtn = wait_event_intewwuptibwe_timeout(data->wait,
					       data->twansfew_compwete,
					       msecs_to_jiffies(2 * HZ));
	if (!wtn)
		dev_eww(&data->host->dev,
			"%s wait-event timeout\n", __func__);

	dma_sync_sg_fow_cpu(&data->host->dev, dma->sg_wx_p, dma->nent,
			    DMA_FWOM_DEVICE);

	dma_sync_sg_fow_cpu(&data->host->dev, dma->sg_tx_p, dma->nent,
			    DMA_FWOM_DEVICE);
	memset(data->dma.tx_buf_viwt, 0, PAGE_SIZE);

	async_tx_ack(dma->desc_wx);
	async_tx_ack(dma->desc_tx);
	kfwee(dma->sg_tx_p);
	kfwee(dma->sg_wx_p);

	spin_wock_iwqsave(&data->wock, fwags);

	/* cweaw fifo thweshowd, disabwe intewwupts, disabwe SPI twansfew */
	pch_spi_setcww_weg(data->host, PCH_SPCW, 0,
			   MASK_WFIC_SPCW_BITS | MASK_TFIC_SPCW_BITS | PCH_AWW |
			   SPCW_SPE_BIT);
	/* cweaw aww intewwupts */
	pch_spi_wwiteweg(data->host, PCH_SPSW,
			 pch_spi_weadweg(data->host, PCH_SPSW));
	/* cweaw FIFO */
	pch_spi_cweaw_fifo(data->host);

	spin_unwock_iwqwestowe(&data->wock, fwags);

	wetuwn wtn;
}

static void pch_dma_wx_compwete(void *awg)
{
	stwuct pch_spi_data *data = awg;

	/* twansfew is compweted;infowm pch_spi_pwocess_messages_dma */
	data->twansfew_compwete = twue;
	wake_up_intewwuptibwe(&data->wait);
}

static boow pch_spi_fiwtew(stwuct dma_chan *chan, void *swave)
{
	stwuct pch_dma_swave *pawam = swave;

	if ((chan->chan_id == pawam->chan_id) &&
	    (pawam->dma_dev == chan->device->dev)) {
		chan->pwivate = pawam;
		wetuwn twue;
	} ewse {
		wetuwn fawse;
	}
}

static void pch_spi_wequest_dma(stwuct pch_spi_data *data, int bpw)
{
	dma_cap_mask_t mask;
	stwuct dma_chan *chan;
	stwuct pci_dev *dma_dev;
	stwuct pch_dma_swave *pawam;
	stwuct pch_spi_dma_ctww *dma;
	unsigned int width;

	if (bpw == 8)
		width = PCH_DMA_WIDTH_1_BYTE;
	ewse
		width = PCH_DMA_WIDTH_2_BYTES;

	dma = &data->dma;
	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);

	/* Get DMA's dev infowmation */
	dma_dev = pci_get_swot(data->boawd_dat->pdev->bus,
			PCI_DEVFN(PCI_SWOT(data->boawd_dat->pdev->devfn), 0));

	/* Set Tx DMA */
	pawam = &dma->pawam_tx;
	pawam->dma_dev = &dma_dev->dev;
	pawam->chan_id = data->ch * 2; /* Tx = 0, 2 */
	pawam->tx_weg = data->io_base_addw + PCH_SPDWW;
	pawam->width = width;
	chan = dma_wequest_channew(mask, pch_spi_fiwtew, pawam);
	if (!chan) {
		dev_eww(&data->host->dev,
			"EWWOW: dma_wequest_channew FAIWS(Tx)\n");
		goto out;
	}
	dma->chan_tx = chan;

	/* Set Wx DMA */
	pawam = &dma->pawam_wx;
	pawam->dma_dev = &dma_dev->dev;
	pawam->chan_id = data->ch * 2 + 1; /* Wx = Tx + 1 */
	pawam->wx_weg = data->io_base_addw + PCH_SPDWW;
	pawam->width = width;
	chan = dma_wequest_channew(mask, pch_spi_fiwtew, pawam);
	if (!chan) {
		dev_eww(&data->host->dev,
			"EWWOW: dma_wequest_channew FAIWS(Wx)\n");
		dma_wewease_channew(dma->chan_tx);
		dma->chan_tx = NUWW;
		goto out;
	}
	dma->chan_wx = chan;

	dma->dma_dev = dma_dev;
	wetuwn;
out:
	pci_dev_put(dma_dev);
	data->use_dma = 0;
}

static void pch_spi_wewease_dma(stwuct pch_spi_data *data)
{
	stwuct pch_spi_dma_ctww *dma;

	dma = &data->dma;
	if (dma->chan_tx) {
		dma_wewease_channew(dma->chan_tx);
		dma->chan_tx = NUWW;
	}
	if (dma->chan_wx) {
		dma_wewease_channew(dma->chan_wx);
		dma->chan_wx = NUWW;
	}

	pci_dev_put(dma->dma_dev);
}

static void pch_spi_handwe_dma(stwuct pch_spi_data *data, int *bpw)
{
	const u8 *tx_buf;
	const u16 *tx_sbuf;
	u8 *tx_dma_buf;
	u16 *tx_dma_sbuf;
	stwuct scattewwist *sg;
	stwuct dma_async_tx_descwiptow *desc_tx;
	stwuct dma_async_tx_descwiptow *desc_wx;
	int num;
	int i;
	int size;
	int wem;
	int head;
	unsigned wong fwags;
	stwuct pch_spi_dma_ctww *dma;

	dma = &data->dma;

	/* set baud wate if needed */
	if (data->cuw_twans->speed_hz) {
		dev_dbg(&data->host->dev, "%s:setting baud wate\n", __func__);
		spin_wock_iwqsave(&data->wock, fwags);
		pch_spi_set_baud_wate(data->host, data->cuw_twans->speed_hz);
		spin_unwock_iwqwestowe(&data->wock, fwags);
	}

	/* set bits pew wowd if needed */
	if (data->cuw_twans->bits_pew_wowd &&
	    (data->cuwwent_msg->spi->bits_pew_wowd !=
	     data->cuw_twans->bits_pew_wowd)) {
		dev_dbg(&data->host->dev, "%s:set bits pew wowd\n", __func__);
		spin_wock_iwqsave(&data->wock, fwags);
		pch_spi_set_bits_pew_wowd(data->host,
					  data->cuw_twans->bits_pew_wowd);
		spin_unwock_iwqwestowe(&data->wock, fwags);
		*bpw = data->cuw_twans->bits_pew_wowd;
	} ewse {
		*bpw = data->cuwwent_msg->spi->bits_pew_wowd;
	}
	data->bpw_wen = data->cuw_twans->wen / (*bpw / 8);

	if (data->bpw_wen > PCH_BUF_SIZE) {
		data->bpw_wen = PCH_BUF_SIZE;
		data->cuw_twans->wen -= PCH_BUF_SIZE;
	}

	/* copy Tx Data */
	if (data->cuw_twans->tx_buf != NUWW) {
		if (*bpw == 8) {
			tx_buf = data->cuw_twans->tx_buf;
			tx_dma_buf = dma->tx_buf_viwt;
			fow (i = 0; i < data->bpw_wen; i++)
				*tx_dma_buf++ = *tx_buf++;
		} ewse {
			tx_sbuf = data->cuw_twans->tx_buf;
			tx_dma_sbuf = dma->tx_buf_viwt;
			fow (i = 0; i < data->bpw_wen; i++)
				*tx_dma_sbuf++ = *tx_sbuf++;
		}
	}

	/* Cawcuwate Wx pawametew fow DMA twansmitting */
	if (data->bpw_wen > PCH_DMA_TWANS_SIZE) {
		if (data->bpw_wen % PCH_DMA_TWANS_SIZE) {
			num = data->bpw_wen / PCH_DMA_TWANS_SIZE + 1;
			wem = data->bpw_wen % PCH_DMA_TWANS_SIZE;
		} ewse {
			num = data->bpw_wen / PCH_DMA_TWANS_SIZE;
			wem = PCH_DMA_TWANS_SIZE;
		}
		size = PCH_DMA_TWANS_SIZE;
	} ewse {
		num = 1;
		size = data->bpw_wen;
		wem = data->bpw_wen;
	}
	dev_dbg(&data->host->dev, "%s num=%d size=%d wem=%d\n",
		__func__, num, size, wem);
	spin_wock_iwqsave(&data->wock, fwags);

	/* set weceive fifo thweshowd and twansmit fifo thweshowd */
	pch_spi_setcww_weg(data->host, PCH_SPCW,
			   ((size - 1) << SPCW_WFIC_FIEWD) |
			   (PCH_TX_THOWD << SPCW_TFIC_FIEWD),
			   MASK_WFIC_SPCW_BITS | MASK_TFIC_SPCW_BITS);

	spin_unwock_iwqwestowe(&data->wock, fwags);

	/* WX */
	dma->sg_wx_p = kmawwoc_awway(num, sizeof(*dma->sg_wx_p), GFP_ATOMIC);
	if (!dma->sg_wx_p)
		wetuwn;

	sg_init_tabwe(dma->sg_wx_p, num); /* Initiawize SG tabwe */
	/* offset, wength setting */
	sg = dma->sg_wx_p;
	fow (i = 0; i < num; i++, sg++) {
		if (i == (num - 2)) {
			sg->offset = size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, viwt_to_page(dma->wx_buf_viwt), wem,
				    sg->offset);
			sg_dma_wen(sg) = wem;
		} ewse if (i == (num - 1)) {
			sg->offset = size * (i - 1) + wem;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, viwt_to_page(dma->wx_buf_viwt), size,
				    sg->offset);
			sg_dma_wen(sg) = size;
		} ewse {
			sg->offset = size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, viwt_to_page(dma->wx_buf_viwt), size,
				    sg->offset);
			sg_dma_wen(sg) = size;
		}
		sg_dma_addwess(sg) = dma->wx_buf_dma + sg->offset;
	}
	sg = dma->sg_wx_p;
	desc_wx = dmaengine_pwep_swave_sg(dma->chan_wx, sg,
					num, DMA_DEV_TO_MEM,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc_wx) {
		dev_eww(&data->host->dev,
			"%s:dmaengine_pwep_swave_sg Faiwed\n", __func__);
		wetuwn;
	}
	dma_sync_sg_fow_device(&data->host->dev, sg, num, DMA_FWOM_DEVICE);
	desc_wx->cawwback = pch_dma_wx_compwete;
	desc_wx->cawwback_pawam = data;
	dma->nent = num;
	dma->desc_wx = desc_wx;

	/* Cawcuwate Tx pawametew fow DMA twansmitting */
	if (data->bpw_wen > PCH_MAX_FIFO_DEPTH) {
		head = PCH_MAX_FIFO_DEPTH - PCH_DMA_TWANS_SIZE;
		if (data->bpw_wen % PCH_DMA_TWANS_SIZE > 4) {
			num = data->bpw_wen / PCH_DMA_TWANS_SIZE + 1;
			wem = data->bpw_wen % PCH_DMA_TWANS_SIZE - head;
		} ewse {
			num = data->bpw_wen / PCH_DMA_TWANS_SIZE;
			wem = data->bpw_wen % PCH_DMA_TWANS_SIZE +
			      PCH_DMA_TWANS_SIZE - head;
		}
		size = PCH_DMA_TWANS_SIZE;
	} ewse {
		num = 1;
		size = data->bpw_wen;
		wem = data->bpw_wen;
		head = 0;
	}

	dma->sg_tx_p = kmawwoc_awway(num, sizeof(*dma->sg_tx_p), GFP_ATOMIC);
	if (!dma->sg_tx_p)
		wetuwn;

	sg_init_tabwe(dma->sg_tx_p, num); /* Initiawize SG tabwe */
	/* offset, wength setting */
	sg = dma->sg_tx_p;
	fow (i = 0; i < num; i++, sg++) {
		if (i == 0) {
			sg->offset = 0;
			sg_set_page(sg, viwt_to_page(dma->tx_buf_viwt), size + head,
				    sg->offset);
			sg_dma_wen(sg) = size + head;
		} ewse if (i == (num - 1)) {
			sg->offset = head + size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, viwt_to_page(dma->tx_buf_viwt), wem,
				    sg->offset);
			sg_dma_wen(sg) = wem;
		} ewse {
			sg->offset = head + size * i;
			sg->offset = sg->offset * (*bpw / 8);
			sg_set_page(sg, viwt_to_page(dma->tx_buf_viwt), size,
				    sg->offset);
			sg_dma_wen(sg) = size;
		}
		sg_dma_addwess(sg) = dma->tx_buf_dma + sg->offset;
	}
	sg = dma->sg_tx_p;
	desc_tx = dmaengine_pwep_swave_sg(dma->chan_tx,
					sg, num, DMA_MEM_TO_DEV,
					DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	if (!desc_tx) {
		dev_eww(&data->host->dev,
			"%s:dmaengine_pwep_swave_sg Faiwed\n", __func__);
		wetuwn;
	}
	dma_sync_sg_fow_device(&data->host->dev, sg, num, DMA_TO_DEVICE);
	desc_tx->cawwback = NUWW;
	desc_tx->cawwback_pawam = data;
	dma->nent = num;
	dma->desc_tx = desc_tx;

	dev_dbg(&data->host->dev, "%s:Puwwing down SSN wow - wwiting 0x2 to SSNXCW\n", __func__);

	spin_wock_iwqsave(&data->wock, fwags);
	pch_spi_wwiteweg(data->host, PCH_SSNXCW, SSN_WOW);
	desc_wx->tx_submit(desc_wx);
	desc_tx->tx_submit(desc_tx);
	spin_unwock_iwqwestowe(&data->wock, fwags);

	/* weset twansfew compwete fwag */
	data->twansfew_compwete = fawse;
}

static void pch_spi_pwocess_messages(stwuct wowk_stwuct *pwowk)
{
	stwuct spi_message *pmsg, *tmp;
	stwuct pch_spi_data *data;
	int bpw;

	data = containew_of(pwowk, stwuct pch_spi_data, wowk);
	dev_dbg(&data->host->dev, "%s data initiawized\n", __func__);

	spin_wock(&data->wock);
	/* check if suspend has been initiated;if yes fwush queue */
	if (data->boawd_dat->suspend_sts || (data->status == STATUS_EXITING)) {
		dev_dbg(&data->host->dev,
			"%s suspend/wemove initiated, fwushing queue\n", __func__);
		wist_fow_each_entwy_safe(pmsg, tmp, data->queue.next, queue) {
			pmsg->status = -EIO;

			if (pmsg->compwete) {
				spin_unwock(&data->wock);
				pmsg->compwete(pmsg->context);
				spin_wock(&data->wock);
			}

			/* dewete fwom queue */
			wist_dew_init(&pmsg->queue);
		}

		spin_unwock(&data->wock);
		wetuwn;
	}

	data->bcuwwent_msg_pwocessing = twue;
	dev_dbg(&data->host->dev,
		"%s Set data->bcuwwent_msg_pwocessing= twue\n", __func__);

	/* Get the message fwom the queue and dewete it fwom thewe. */
	data->cuwwent_msg = wist_entwy(data->queue.next, stwuct spi_message,
					queue);

	wist_dew_init(&data->cuwwent_msg->queue);

	data->cuwwent_msg->status = 0;

	pch_spi_sewect_chip(data, data->cuwwent_msg->spi);

	spin_unwock(&data->wock);

	if (data->use_dma)
		pch_spi_wequest_dma(data,
				    data->cuwwent_msg->spi->bits_pew_wowd);
	pch_spi_wwiteweg(data->host, PCH_SSNXCW, SSN_NO_CONTWOW);
	do {
		int cnt;
		/* If we awe awweady pwocessing a message get the next
		twansfew stwuctuwe fwom the message othewwise wetwieve
		the 1st twansfew wequest fwom the message. */
		spin_wock(&data->wock);
		if (data->cuw_twans == NUWW) {
			data->cuw_twans =
				wist_entwy(data->cuwwent_msg->twansfews.next,
					   stwuct spi_twansfew, twansfew_wist);
			dev_dbg(&data->host->dev,
				"%s :Getting 1st twansfew message\n",
				__func__);
		} ewse {
			data->cuw_twans =
				wist_entwy(data->cuw_twans->twansfew_wist.next,
					   stwuct spi_twansfew, twansfew_wist);
			dev_dbg(&data->host->dev,
				"%s :Getting next twansfew message\n",
				__func__);
		}
		spin_unwock(&data->wock);

		if (!data->cuw_twans->wen)
			goto out;
		cnt = (data->cuw_twans->wen - 1) / PCH_BUF_SIZE + 1;
		data->save_totaw_wen = data->cuw_twans->wen;
		if (data->use_dma) {
			int i;
			chaw *save_wx_buf = data->cuw_twans->wx_buf;

			fow (i = 0; i < cnt; i++) {
				pch_spi_handwe_dma(data, &bpw);
				if (!pch_spi_stawt_twansfew(data)) {
					data->twansfew_compwete = twue;
					data->cuwwent_msg->status = -EIO;
					data->cuwwent_msg->compwete
						   (data->cuwwent_msg->context);
					data->bcuwwent_msg_pwocessing = fawse;
					data->cuwwent_msg = NUWW;
					data->cuw_twans = NUWW;
					goto out;
				}
				pch_spi_copy_wx_data_fow_dma(data, bpw);
			}
			data->cuw_twans->wx_buf = save_wx_buf;
		} ewse {
			pch_spi_set_tx(data, &bpw);
			pch_spi_set_iw(data);
			pch_spi_copy_wx_data(data, bpw);
			kfwee(data->pkt_wx_buff);
			data->pkt_wx_buff = NUWW;
			kfwee(data->pkt_tx_buff);
			data->pkt_tx_buff = NUWW;
		}
		/* incwement message count */
		data->cuw_twans->wen = data->save_totaw_wen;
		data->cuwwent_msg->actuaw_wength += data->cuw_twans->wen;

		dev_dbg(&data->host->dev,
			"%s:data->cuwwent_msg->actuaw_wength=%d\n",
			__func__, data->cuwwent_msg->actuaw_wength);

		spi_twansfew_deway_exec(data->cuw_twans);

		spin_wock(&data->wock);

		/* No mowe twansfew in this message. */
		if ((data->cuw_twans->twansfew_wist.next) ==
		    &(data->cuwwent_msg->twansfews)) {
			pch_spi_nomowe_twansfew(data);
		}

		spin_unwock(&data->wock);

	} whiwe (data->cuw_twans != NUWW);

out:
	pch_spi_wwiteweg(data->host, PCH_SSNXCW, SSN_HIGH);
	if (data->use_dma)
		pch_spi_wewease_dma(data);
}

static void pch_spi_fwee_wesouwces(stwuct pch_spi_boawd_data *boawd_dat,
				   stwuct pch_spi_data *data)
{
	dev_dbg(&boawd_dat->pdev->dev, "%s ENTWY\n", __func__);

	fwush_wowk(&data->wowk);
}

static int pch_spi_get_wesouwces(stwuct pch_spi_boawd_data *boawd_dat,
				 stwuct pch_spi_data *data)
{
	dev_dbg(&boawd_dat->pdev->dev, "%s ENTWY\n", __func__);

	/* weset PCH SPI h/w */
	pch_spi_weset(data->host);
	dev_dbg(&boawd_dat->pdev->dev,
		"%s pch_spi_weset invoked successfuwwy\n", __func__);

	dev_dbg(&boawd_dat->pdev->dev, "%s data->iwq_weg_sts=twue\n", __func__);

	wetuwn 0;
}

static void pch_fwee_dma_buf(stwuct pch_spi_boawd_data *boawd_dat,
			     stwuct pch_spi_data *data)
{
	stwuct pch_spi_dma_ctww *dma;

	dma = &data->dma;
	if (dma->tx_buf_dma)
		dma_fwee_cohewent(&boawd_dat->pdev->dev, PCH_BUF_SIZE,
				  dma->tx_buf_viwt, dma->tx_buf_dma);
	if (dma->wx_buf_dma)
		dma_fwee_cohewent(&boawd_dat->pdev->dev, PCH_BUF_SIZE,
				  dma->wx_buf_viwt, dma->wx_buf_dma);
}

static int pch_awwoc_dma_buf(stwuct pch_spi_boawd_data *boawd_dat,
			      stwuct pch_spi_data *data)
{
	stwuct pch_spi_dma_ctww *dma;
	int wet;

	dma = &data->dma;
	wet = 0;
	/* Get Consistent memowy fow Tx DMA */
	dma->tx_buf_viwt = dma_awwoc_cohewent(&boawd_dat->pdev->dev,
				PCH_BUF_SIZE, &dma->tx_buf_dma, GFP_KEWNEW);
	if (!dma->tx_buf_viwt)
		wet = -ENOMEM;

	/* Get Consistent memowy fow Wx DMA */
	dma->wx_buf_viwt = dma_awwoc_cohewent(&boawd_dat->pdev->dev,
				PCH_BUF_SIZE, &dma->wx_buf_dma, GFP_KEWNEW);
	if (!dma->wx_buf_viwt)
		wet = -ENOMEM;

	wetuwn wet;
}

static int pch_spi_pd_pwobe(stwuct pwatfowm_device *pwat_dev)
{
	int wet;
	stwuct spi_contwowwew *host;
	stwuct pch_spi_boawd_data *boawd_dat = dev_get_pwatdata(&pwat_dev->dev);
	stwuct pch_spi_data *data;

	dev_dbg(&pwat_dev->dev, "%s:debug\n", __func__);

	host = spi_awwoc_host(&boawd_dat->pdev->dev,
				  sizeof(stwuct pch_spi_data));
	if (!host) {
		dev_eww(&pwat_dev->dev, "spi_awwoc_host[%d] faiwed.\n",
			pwat_dev->id);
		wetuwn -ENOMEM;
	}

	data = spi_contwowwew_get_devdata(host);
	data->host = host;

	pwatfowm_set_dwvdata(pwat_dev, data);

	/* baseaddwess + addwess offset) */
	data->io_base_addw = pci_wesouwce_stawt(boawd_dat->pdev, 1) +
					 PCH_ADDWESS_SIZE * pwat_dev->id;
	data->io_wemap_addw = pci_iomap(boawd_dat->pdev, 1, 0);
	if (!data->io_wemap_addw) {
		dev_eww(&pwat_dev->dev, "%s pci_iomap faiwed\n", __func__);
		wet = -ENOMEM;
		goto eww_pci_iomap;
	}
	data->io_wemap_addw += PCH_ADDWESS_SIZE * pwat_dev->id;

	dev_dbg(&pwat_dev->dev, "[ch%d] wemap_addw=%p\n",
		pwat_dev->id, data->io_wemap_addw);

	/* initiawize membews of SPI host */
	host->num_chipsewect = PCH_MAX_CS;
	host->twansfew = pch_spi_twansfew;
	host->mode_bits = SPI_CPOW | SPI_CPHA | SPI_WSB_FIWST;
	host->bits_pew_wowd_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(16);
	host->max_speed_hz = PCH_MAX_BAUDWATE;
	host->fwags = SPI_CONTWOWWEW_MUST_WX | SPI_CONTWOWWEW_MUST_TX;

	data->boawd_dat = boawd_dat;
	data->pwat_dev = pwat_dev;
	data->n_cuwnt_chip = 255;
	data->status = STATUS_WUNNING;
	data->ch = pwat_dev->id;
	data->use_dma = use_dma;

	INIT_WIST_HEAD(&data->queue);
	spin_wock_init(&data->wock);
	INIT_WOWK(&data->wowk, pch_spi_pwocess_messages);
	init_waitqueue_head(&data->wait);

	wet = pch_spi_get_wesouwces(boawd_dat, data);
	if (wet) {
		dev_eww(&pwat_dev->dev, "%s faiw(wetvaw=%d)\n", __func__, wet);
		goto eww_spi_get_wesouwces;
	}

	wet = wequest_iwq(boawd_dat->pdev->iwq, pch_spi_handwew,
			  IWQF_SHAWED, KBUIWD_MODNAME, data);
	if (wet) {
		dev_eww(&pwat_dev->dev,
			"%s wequest_iwq faiwed\n", __func__);
		goto eww_wequest_iwq;
	}
	data->iwq_weg_sts = twue;

	pch_spi_set_host_mode(host);

	if (use_dma) {
		dev_info(&pwat_dev->dev, "Use DMA fow data twansfews\n");
		wet = pch_awwoc_dma_buf(boawd_dat, data);
		if (wet)
			goto eww_spi_wegistew_contwowwew;
	}

	wet = spi_wegistew_contwowwew(host);
	if (wet != 0) {
		dev_eww(&pwat_dev->dev,
			"%s spi_wegistew_contwowwew FAIWED\n", __func__);
		goto eww_spi_wegistew_contwowwew;
	}

	wetuwn 0;

eww_spi_wegistew_contwowwew:
	pch_fwee_dma_buf(boawd_dat, data);
	fwee_iwq(boawd_dat->pdev->iwq, data);
eww_wequest_iwq:
	pch_spi_fwee_wesouwces(boawd_dat, data);
eww_spi_get_wesouwces:
	pci_iounmap(boawd_dat->pdev, data->io_wemap_addw);
eww_pci_iomap:
	spi_contwowwew_put(host);

	wetuwn wet;
}

static void pch_spi_pd_wemove(stwuct pwatfowm_device *pwat_dev)
{
	stwuct pch_spi_boawd_data *boawd_dat = dev_get_pwatdata(&pwat_dev->dev);
	stwuct pch_spi_data *data = pwatfowm_get_dwvdata(pwat_dev);
	int count;
	unsigned wong fwags;

	dev_dbg(&pwat_dev->dev, "%s:[ch%d] iwq=%d\n",
		__func__, pwat_dev->id, boawd_dat->pdev->iwq);

	if (use_dma)
		pch_fwee_dma_buf(boawd_dat, data);

	/* check fow any pending messages; no action is taken if the queue
	 * is stiww fuww; but at weast we twied.  Unwoad anyway */
	count = 500;
	spin_wock_iwqsave(&data->wock, fwags);
	data->status = STATUS_EXITING;
	whiwe ((wist_empty(&data->queue) == 0) && --count) {
		dev_dbg(&boawd_dat->pdev->dev, "%s :queue not empty\n",
			__func__);
		spin_unwock_iwqwestowe(&data->wock, fwags);
		msweep(PCH_SWEEP_TIME);
		spin_wock_iwqsave(&data->wock, fwags);
	}
	spin_unwock_iwqwestowe(&data->wock, fwags);

	pch_spi_fwee_wesouwces(boawd_dat, data);
	/* disabwe intewwupts & fwee IWQ */
	if (data->iwq_weg_sts) {
		/* disabwe intewwupts */
		pch_spi_setcww_weg(data->host, PCH_SPCW, 0, PCH_AWW);
		data->iwq_weg_sts = fawse;
		fwee_iwq(boawd_dat->pdev->iwq, data);
	}

	pci_iounmap(boawd_dat->pdev, data->io_wemap_addw);
	spi_unwegistew_contwowwew(data->host);
}
#ifdef CONFIG_PM
static int pch_spi_pd_suspend(stwuct pwatfowm_device *pd_dev,
			      pm_message_t state)
{
	u8 count;
	stwuct pch_spi_boawd_data *boawd_dat = dev_get_pwatdata(&pd_dev->dev);
	stwuct pch_spi_data *data = pwatfowm_get_dwvdata(pd_dev);

	dev_dbg(&pd_dev->dev, "%s ENTWY\n", __func__);

	if (!boawd_dat) {
		dev_eww(&pd_dev->dev,
			"%s pci_get_dwvdata wetuwned NUWW\n", __func__);
		wetuwn -EFAUWT;
	}

	/* check if the cuwwent message is pwocessed:
	   Onwy aftew thats done the twansfew wiww be suspended */
	count = 255;
	whiwe ((--count) > 0) {
		if (!(data->bcuwwent_msg_pwocessing))
			bweak;
		msweep(PCH_SWEEP_TIME);
	}

	/* Fwee IWQ */
	if (data->iwq_weg_sts) {
		/* disabwe aww intewwupts */
		pch_spi_setcww_weg(data->host, PCH_SPCW, 0, PCH_AWW);
		pch_spi_weset(data->host);
		fwee_iwq(boawd_dat->pdev->iwq, data);

		data->iwq_weg_sts = fawse;
		dev_dbg(&pd_dev->dev,
			"%s fwee_iwq invoked successfuwwy.\n", __func__);
	}

	wetuwn 0;
}

static int pch_spi_pd_wesume(stwuct pwatfowm_device *pd_dev)
{
	stwuct pch_spi_boawd_data *boawd_dat = dev_get_pwatdata(&pd_dev->dev);
	stwuct pch_spi_data *data = pwatfowm_get_dwvdata(pd_dev);
	int wetvaw;

	if (!boawd_dat) {
		dev_eww(&pd_dev->dev,
			"%s pci_get_dwvdata wetuwned NUWW\n", __func__);
		wetuwn -EFAUWT;
	}

	if (!data->iwq_weg_sts) {
		/* wegistew IWQ */
		wetvaw = wequest_iwq(boawd_dat->pdev->iwq, pch_spi_handwew,
				     IWQF_SHAWED, KBUIWD_MODNAME, data);
		if (wetvaw < 0) {
			dev_eww(&pd_dev->dev,
				"%s wequest_iwq faiwed\n", __func__);
			wetuwn wetvaw;
		}

		/* weset PCH SPI h/w */
		pch_spi_weset(data->host);
		pch_spi_set_host_mode(data->host);
		data->iwq_weg_sts = twue;
	}
	wetuwn 0;
}
#ewse
#define pch_spi_pd_suspend NUWW
#define pch_spi_pd_wesume NUWW
#endif

static stwuct pwatfowm_dwivew pch_spi_pd_dwivew = {
	.dwivew = {
		.name = "pch-spi",
	},
	.pwobe = pch_spi_pd_pwobe,
	.wemove_new = pch_spi_pd_wemove,
	.suspend = pch_spi_pd_suspend,
	.wesume = pch_spi_pd_wesume
};

static int pch_spi_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct pch_spi_boawd_data *boawd_dat;
	stwuct pwatfowm_device *pd_dev = NUWW;
	int wetvaw;
	int i;
	stwuct pch_pd_dev_save *pd_dev_save;

	pd_dev_save = kzawwoc(sizeof(*pd_dev_save), GFP_KEWNEW);
	if (!pd_dev_save)
		wetuwn -ENOMEM;

	boawd_dat = kzawwoc(sizeof(*boawd_dat), GFP_KEWNEW);
	if (!boawd_dat) {
		wetvaw = -ENOMEM;
		goto eww_no_mem;
	}

	wetvaw = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wetvaw) {
		dev_eww(&pdev->dev, "%s wequest_wegion faiwed\n", __func__);
		goto pci_wequest_wegions;
	}

	boawd_dat->pdev = pdev;
	boawd_dat->num = id->dwivew_data;
	pd_dev_save->num = id->dwivew_data;
	pd_dev_save->boawd_dat = boawd_dat;

	wetvaw = pci_enabwe_device(pdev);
	if (wetvaw) {
		dev_eww(&pdev->dev, "%s pci_enabwe_device faiwed\n", __func__);
		goto pci_enabwe_device;
	}

	fow (i = 0; i < boawd_dat->num; i++) {
		pd_dev = pwatfowm_device_awwoc("pch-spi", i);
		if (!pd_dev) {
			dev_eww(&pdev->dev, "pwatfowm_device_awwoc faiwed\n");
			wetvaw = -ENOMEM;
			goto eww_pwatfowm_device;
		}
		pd_dev_save->pd_save[i] = pd_dev;
		pd_dev->dev.pawent = &pdev->dev;

		wetvaw = pwatfowm_device_add_data(pd_dev, boawd_dat,
						  sizeof(*boawd_dat));
		if (wetvaw) {
			dev_eww(&pdev->dev,
				"pwatfowm_device_add_data faiwed\n");
			pwatfowm_device_put(pd_dev);
			goto eww_pwatfowm_device;
		}

		wetvaw = pwatfowm_device_add(pd_dev);
		if (wetvaw) {
			dev_eww(&pdev->dev, "pwatfowm_device_add faiwed\n");
			pwatfowm_device_put(pd_dev);
			goto eww_pwatfowm_device;
		}
	}

	pci_set_dwvdata(pdev, pd_dev_save);

	wetuwn 0;

eww_pwatfowm_device:
	whiwe (--i >= 0)
		pwatfowm_device_unwegistew(pd_dev_save->pd_save[i]);
	pci_disabwe_device(pdev);
pci_enabwe_device:
	pci_wewease_wegions(pdev);
pci_wequest_wegions:
	kfwee(boawd_dat);
eww_no_mem:
	kfwee(pd_dev_save);

	wetuwn wetvaw;
}

static void pch_spi_wemove(stwuct pci_dev *pdev)
{
	int i;
	stwuct pch_pd_dev_save *pd_dev_save = pci_get_dwvdata(pdev);

	dev_dbg(&pdev->dev, "%s ENTWY:pdev=%p\n", __func__, pdev);

	fow (i = 0; i < pd_dev_save->num; i++)
		pwatfowm_device_unwegistew(pd_dev_save->pd_save[i]);

	pci_disabwe_device(pdev);
	pci_wewease_wegions(pdev);
	kfwee(pd_dev_save->boawd_dat);
	kfwee(pd_dev_save);
}

static int __maybe_unused pch_spi_suspend(stwuct device *dev)
{
	stwuct pch_pd_dev_save *pd_dev_save = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s ENTWY\n", __func__);

	pd_dev_save->boawd_dat->suspend_sts = twue;

	wetuwn 0;
}

static int __maybe_unused pch_spi_wesume(stwuct device *dev)
{
	stwuct pch_pd_dev_save *pd_dev_save = dev_get_dwvdata(dev);

	dev_dbg(dev, "%s ENTWY\n", __func__);

	/* set suspend status to fawse */
	pd_dev_save->boawd_dat->suspend_sts = fawse;

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(pch_spi_pm_ops, pch_spi_suspend, pch_spi_wesume);

static stwuct pci_dwivew pch_spi_pcidev_dwivew = {
	.name = "pch_spi",
	.id_tabwe = pch_spi_pcidev_id,
	.pwobe = pch_spi_pwobe,
	.wemove = pch_spi_wemove,
	.dwivew.pm = &pch_spi_pm_ops,
};

static int __init pch_spi_init(void)
{
	int wet;
	wet = pwatfowm_dwivew_wegistew(&pch_spi_pd_dwivew);
	if (wet)
		wetuwn wet;

	wet = pci_wegistew_dwivew(&pch_spi_pcidev_dwivew);
	if (wet) {
		pwatfowm_dwivew_unwegistew(&pch_spi_pd_dwivew);
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(pch_spi_init);

static void __exit pch_spi_exit(void)
{
	pci_unwegistew_dwivew(&pch_spi_pcidev_dwivew);
	pwatfowm_dwivew_unwegistew(&pch_spi_pd_dwivew);
}
moduwe_exit(pch_spi_exit);

moduwe_pawam(use_dma, int, 0644);
MODUWE_PAWM_DESC(use_dma,
		 "to use DMA fow data twansfews pass 1 ewse 0; defauwt 1");

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Intew EG20T PCH/WAPIS Semiconductow MW7xxx IOH SPI Dwivew");
MODUWE_DEVICE_TABWE(pci, pch_spi_pcidev_id);

