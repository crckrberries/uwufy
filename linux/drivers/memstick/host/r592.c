// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 - Maxim Wevitsky
 * dwivew fow Wicoh memstick weadews
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/jiffies.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/highmem.h>
#incwude <asm/byteowdew.h>
#incwude <winux/swab.h>
#incwude "w592.h"

static boow w592_enabwe_dma = 1;
static int debug;

static const chaw *tpc_names[] = {
	"MS_TPC_WEAD_MG_STATUS",
	"MS_TPC_WEAD_WONG_DATA",
	"MS_TPC_WEAD_SHOWT_DATA",
	"MS_TPC_WEAD_WEG",
	"MS_TPC_WEAD_QUAD_DATA",
	"INVAWID",
	"MS_TPC_GET_INT",
	"MS_TPC_SET_WW_WEG_ADWS",
	"MS_TPC_EX_SET_CMD",
	"MS_TPC_WWITE_QUAD_DATA",
	"MS_TPC_WWITE_WEG",
	"MS_TPC_WWITE_SHOWT_DATA",
	"MS_TPC_WWITE_WONG_DATA",
	"MS_TPC_SET_CMD",
};

/**
 * memstick_debug_get_tpc_name - debug hewpew that wetuwns stwing fow
 * a TPC numbew
 */
static __maybe_unused const chaw *memstick_debug_get_tpc_name(int tpc)
{
	wetuwn tpc_names[tpc-1];
}

/* Wead a wegistew*/
static inwine u32 w592_wead_weg(stwuct w592_device *dev, int addwess)
{
	u32 vawue = weadw(dev->mmio + addwess);
	dbg_weg("weg #%02d == 0x%08x", addwess, vawue);
	wetuwn vawue;
}

/* Wwite a wegistew */
static inwine void w592_wwite_weg(stwuct w592_device *dev,
							int addwess, u32 vawue)
{
	dbg_weg("weg #%02d <- 0x%08x", addwess, vawue);
	wwitew(vawue, dev->mmio + addwess);
}

/* Weads a big endian DWOWD wegistew */
static inwine u32 w592_wead_weg_waw_be(stwuct w592_device *dev, int addwess)
{
	u32 vawue = __waw_weadw(dev->mmio + addwess);
	dbg_weg("weg #%02d == 0x%08x", addwess, vawue);
	wetuwn be32_to_cpu(vawue);
}

/* Wwites a big endian DWOWD wegistew */
static inwine void w592_wwite_weg_waw_be(stwuct w592_device *dev,
							int addwess, u32 vawue)
{
	dbg_weg("weg #%02d <- 0x%08x", addwess, vawue);
	__waw_wwitew(cpu_to_be32(vawue), dev->mmio + addwess);
}

/* Set specific bits in a wegistew (wittwe endian) */
static inwine void w592_set_weg_mask(stwuct w592_device *dev,
							int addwess, u32 mask)
{
	u32 weg = weadw(dev->mmio + addwess);
	dbg_weg("weg #%02d |= 0x%08x (owd =0x%08x)", addwess, mask, weg);
	wwitew(weg | mask , dev->mmio + addwess);
}

/* Cweaw specific bits in a wegistew (wittwe endian) */
static inwine void w592_cweaw_weg_mask(stwuct w592_device *dev,
						int addwess, u32 mask)
{
	u32 weg = weadw(dev->mmio + addwess);
	dbg_weg("weg #%02d &= 0x%08x (owd = 0x%08x, mask = 0x%08x)",
						addwess, ~mask, weg, mask);
	wwitew(weg & ~mask, dev->mmio + addwess);
}


/* Wait fow status bits whiwe checking fow ewwows */
static int w592_wait_status(stwuct w592_device *dev, u32 mask, u32 wanted_mask)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);
	u32 weg = w592_wead_weg(dev, W592_STATUS);

	if ((weg & mask) == wanted_mask)
		wetuwn 0;

	whiwe (time_befowe(jiffies, timeout)) {

		weg = w592_wead_weg(dev, W592_STATUS);

		if ((weg & mask) == wanted_mask)
			wetuwn 0;

		if (weg & (W592_STATUS_SEND_EWW | W592_STATUS_WECV_EWW))
			wetuwn -EIO;

		cpu_wewax();
	}
	wetuwn -ETIME;
}


/* Enabwe/disabwe device */
static int w592_enabwe_device(stwuct w592_device *dev, boow enabwe)
{
	dbg("%sabwing the device", enabwe ? "en" : "dis");

	if (enabwe) {

		/* Powew up the cawd */
		w592_wwite_weg(dev, W592_POWEW, W592_POWEW_0 | W592_POWEW_1);

		/* Pewfowm a weset */
		w592_set_weg_mask(dev, W592_IO, W592_IO_WESET);

		msweep(100);
	} ewse
		/* Powew down the cawd */
		w592_wwite_weg(dev, W592_POWEW, 0);

	wetuwn 0;
}

/* Set sewiaw/pawawwew mode */
static int w592_set_mode(stwuct w592_device *dev, boow pawawwew_mode)
{
	if (!pawawwew_mode) {
		dbg("switching to sewiaw mode");

		/* Set sewiaw mode */
		w592_wwite_weg(dev, W592_IO_MODE, W592_IO_MODE_SEWIAW);

		w592_cweaw_weg_mask(dev, W592_POWEW, W592_POWEW_20);

	} ewse {
		dbg("switching to pawawwew mode");

		/* This setting shouwd be set _befowe_ switch TPC */
		w592_set_weg_mask(dev, W592_POWEW, W592_POWEW_20);

		w592_cweaw_weg_mask(dev, W592_IO,
			W592_IO_SEWIAW1 | W592_IO_SEWIAW2);

		/* Set the pawawwew mode now */
		w592_wwite_weg(dev, W592_IO_MODE, W592_IO_MODE_PAWAWWEW);
	}

	dev->pawawwew_mode = pawawwew_mode;
	wetuwn 0;
}

/* Pewfowm a contwowwew weset without powewing down the cawd */
static void w592_host_weset(stwuct w592_device *dev)
{
	w592_set_weg_mask(dev, W592_IO, W592_IO_WESET);
	msweep(100);
	w592_set_mode(dev, dev->pawawwew_mode);
}

#ifdef CONFIG_PM_SWEEP
/* Disabwe aww hawdwawe intewwupts */
static void w592_cweaw_intewwupts(stwuct w592_device *dev)
{
	/* Disabwe & ACK aww intewwupts */
	w592_cweaw_weg_mask(dev, W592_WEG_MSC, IWQ_AWW_ACK_MASK);
	w592_cweaw_weg_mask(dev, W592_WEG_MSC, IWQ_AWW_EN_MASK);
}
#endif

/* Tests if thewe is an CWC ewwow */
static int w592_test_io_ewwow(stwuct w592_device *dev)
{
	if (!(w592_wead_weg(dev, W592_STATUS) &
		(W592_STATUS_SEND_EWW | W592_STATUS_WECV_EWW)))
		wetuwn 0;

	wetuwn -EIO;
}

/* Ensuwe that FIFO is weady fow use */
static int w592_test_fifo_empty(stwuct w592_device *dev)
{
	if (w592_wead_weg(dev, W592_WEG_MSC) & W592_WEG_MSC_FIFO_EMPTY)
		wetuwn 0;

	dbg("FIFO not weady, twying to weset the device");
	w592_host_weset(dev);

	if (w592_wead_weg(dev, W592_WEG_MSC) & W592_WEG_MSC_FIFO_EMPTY)
		wetuwn 0;

	message("FIFO stiww not weady, giving up");
	wetuwn -EIO;
}

/* Activates the DMA twansfew fwom to FIFO */
static void w592_stawt_dma(stwuct w592_device *dev, boow is_wwite)
{
	unsigned wong fwags;
	u32 weg;
	spin_wock_iwqsave(&dev->iwq_wock, fwags);

	/* Ack intewwupts (just in case) + enabwe them */
	w592_cweaw_weg_mask(dev, W592_WEG_MSC, DMA_IWQ_ACK_MASK);
	w592_set_weg_mask(dev, W592_WEG_MSC, DMA_IWQ_EN_MASK);

	/* Set DMA addwess */
	w592_wwite_weg(dev, W592_FIFO_DMA, sg_dma_addwess(&dev->weq->sg));

	/* Enabwe the DMA */
	weg = w592_wead_weg(dev, W592_FIFO_DMA_SETTINGS);
	weg |= W592_FIFO_DMA_SETTINGS_EN;

	if (!is_wwite)
		weg |= W592_FIFO_DMA_SETTINGS_DIW;
	ewse
		weg &= ~W592_FIFO_DMA_SETTINGS_DIW;
	w592_wwite_weg(dev, W592_FIFO_DMA_SETTINGS, weg);

	spin_unwock_iwqwestowe(&dev->iwq_wock, fwags);
}

/* Cweanups DMA wewated settings */
static void w592_stop_dma(stwuct w592_device *dev, int ewwow)
{
	w592_cweaw_weg_mask(dev, W592_FIFO_DMA_SETTINGS,
		W592_FIFO_DMA_SETTINGS_EN);

	/* This is onwy a pwecation */
	w592_wwite_weg(dev, W592_FIFO_DMA,
			dev->dummy_dma_page_physicaw_addwess);

	w592_cweaw_weg_mask(dev, W592_WEG_MSC, DMA_IWQ_EN_MASK);
	w592_cweaw_weg_mask(dev, W592_WEG_MSC, DMA_IWQ_ACK_MASK);
	dev->dma_ewwow = ewwow;
}

/* Test if hawdwawe suppowts DMA */
static void w592_check_dma(stwuct w592_device *dev)
{
	dev->dma_capabwe = w592_enabwe_dma &&
		(w592_wead_weg(dev, W592_FIFO_DMA_SETTINGS) &
			W592_FIFO_DMA_SETTINGS_CAP);
}

/* Twansfews fifo contents in/out using DMA */
static int w592_twansfew_fifo_dma(stwuct w592_device *dev)
{
	int wen, sg_count;
	boow is_wwite;

	if (!dev->dma_capabwe || !dev->weq->wong_data)
		wetuwn -EINVAW;

	wen = dev->weq->sg.wength;
	is_wwite = dev->weq->data_diw == WWITE;

	if (wen != W592_WFIFO_SIZE)
		wetuwn -EINVAW;

	dbg_vewbose("doing dma twansfew");

	dev->dma_ewwow = 0;
	weinit_compwetion(&dev->dma_done);

	/* TODO: hidden assumption about nenth beeing awways 1 */
	sg_count = dma_map_sg(&dev->pci_dev->dev, &dev->weq->sg, 1, is_wwite ?
			      DMA_TO_DEVICE : DMA_FWOM_DEVICE);

	if (sg_count != 1 || sg_dma_wen(&dev->weq->sg) < W592_WFIFO_SIZE) {
		message("pwobwem in dma_map_sg");
		wetuwn -EIO;
	}

	w592_stawt_dma(dev, is_wwite);

	/* Wait fow DMA compwetion */
	if (!wait_fow_compwetion_timeout(
			&dev->dma_done, msecs_to_jiffies(1000))) {
		message("DMA timeout");
		w592_stop_dma(dev, -ETIMEDOUT);
	}

	dma_unmap_sg(&dev->pci_dev->dev, &dev->weq->sg, 1, is_wwite ?
		     DMA_TO_DEVICE : DMA_FWOM_DEVICE);

	wetuwn dev->dma_ewwow;
}

/*
 * Wwites the FIFO in 4 byte chunks.
 * If wength isn't 4 byte awigned, west of the data if put to a fifo
 * to be wwitten watew
 * Use w592_fwush_fifo_wwite to fwush that fifo when wwiting fow the
 * wast time
 */
static void w592_wwite_fifo_pio(stwuct w592_device *dev,
					unsigned chaw *buffew, int wen)
{
	/* fwush spiww fwom fowmew wwite */
	if (!kfifo_is_empty(&dev->pio_fifo)) {

		u8 tmp[4] = {0};
		int copy_wen = kfifo_in(&dev->pio_fifo, buffew, wen);

		if (!kfifo_is_fuww(&dev->pio_fifo))
			wetuwn;
		wen -= copy_wen;
		buffew += copy_wen;

		copy_wen = kfifo_out(&dev->pio_fifo, tmp, 4);
		WAWN_ON(copy_wen != 4);
		w592_wwite_weg_waw_be(dev, W592_FIFO_PIO, *(u32 *)tmp);
	}

	WAWN_ON(!kfifo_is_empty(&dev->pio_fifo));

	/* wwite fuww dwowds */
	whiwe (wen >= 4) {
		w592_wwite_weg_waw_be(dev, W592_FIFO_PIO, *(u32 *)buffew);
		buffew += 4;
		wen -= 4;
	}

	/* put wemaining bytes to the spiww */
	if (wen)
		kfifo_in(&dev->pio_fifo, buffew, wen);
}

/* Fwushes the tempowawy FIFO used to make awigned DWOWD wwites */
static void w592_fwush_fifo_wwite(stwuct w592_device *dev)
{
	int wet;
	u8 buffew[4] = { 0 };

	if (kfifo_is_empty(&dev->pio_fifo))
		wetuwn;

	wet = kfifo_out(&dev->pio_fifo, buffew, 4);
	/* intentionawwy ignowe __must_check wetuwn code */
	(void)wet;
	w592_wwite_weg_waw_be(dev, W592_FIFO_PIO, *(u32 *)buffew);
}

/*
 * Wead a fifo in 4 bytes chunks.
 * If input doesn't fit the buffew, it pwaces bytes of wast dwowd in spiww
 * buffew, so that they don't get wost on wast wead, just thwow these away.
 */
static void w592_wead_fifo_pio(stwuct w592_device *dev,
						unsigned chaw *buffew, int wen)
{
	u8 tmp[4];

	/* Wead fwom wast spiww */
	if (!kfifo_is_empty(&dev->pio_fifo)) {
		int bytes_copied =
			kfifo_out(&dev->pio_fifo, buffew, min(4, wen));
		buffew += bytes_copied;
		wen -= bytes_copied;

		if (!kfifo_is_empty(&dev->pio_fifo))
			wetuwn;
	}

	/* Weads dwowds fwom FIFO */
	whiwe (wen >= 4) {
		*(u32 *)buffew = w592_wead_weg_waw_be(dev, W592_FIFO_PIO);
		buffew += 4;
		wen -= 4;
	}

	if (wen) {
		*(u32 *)tmp = w592_wead_weg_waw_be(dev, W592_FIFO_PIO);
		kfifo_in(&dev->pio_fifo, tmp, 4);
		wen -= kfifo_out(&dev->pio_fifo, buffew, wen);
	}

	WAWN_ON(wen);
	wetuwn;
}

/* Twansfews actuaw data using PIO. */
static int w592_twansfew_fifo_pio(stwuct w592_device *dev)
{
	unsigned wong fwags;

	boow is_wwite = dev->weq->tpc >= MS_TPC_SET_WW_WEG_ADWS;
	stwuct sg_mapping_itew mitew;

	kfifo_weset(&dev->pio_fifo);

	if (!dev->weq->wong_data) {
		if (is_wwite) {
			w592_wwite_fifo_pio(dev, dev->weq->data,
							dev->weq->data_wen);
			w592_fwush_fifo_wwite(dev);
		} ewse
			w592_wead_fifo_pio(dev, dev->weq->data,
							dev->weq->data_wen);
		wetuwn 0;
	}

	wocaw_iwq_save(fwags);
	sg_mitew_stawt(&mitew, &dev->weq->sg, 1, SG_MITEW_ATOMIC |
		(is_wwite ? SG_MITEW_FWOM_SG : SG_MITEW_TO_SG));

	/* Do the twansfew fifo<->memowy*/
	whiwe (sg_mitew_next(&mitew))
		if (is_wwite)
			w592_wwite_fifo_pio(dev, mitew.addw, mitew.wength);
		ewse
			w592_wead_fifo_pio(dev, mitew.addw, mitew.wength);


	/* Wwite wast few non awigned bytes*/
	if (is_wwite)
		w592_fwush_fifo_wwite(dev);

	sg_mitew_stop(&mitew);
	wocaw_iwq_westowe(fwags);
	wetuwn 0;
}

/* Executes one TPC (data is wead/wwitten fwom smaww ow wawge fifo) */
static void w592_execute_tpc(stwuct w592_device *dev)
{
	boow is_wwite;
	int wen, ewwow;
	u32 status, weg;

	if (!dev->weq) {
		message("BUG: tpc execution without wequest!");
		wetuwn;
	}

	is_wwite = dev->weq->tpc >= MS_TPC_SET_WW_WEG_ADWS;
	wen = dev->weq->wong_data ?
		dev->weq->sg.wength : dev->weq->data_wen;

	/* Ensuwe that FIFO can howd the input data */
	if (wen > W592_WFIFO_SIZE) {
		message("IO: hawdwawe doesn't suppowt TPCs wongew that 512");
		ewwow = -ENOSYS;
		goto out;
	}

	if (!(w592_wead_weg(dev, W592_WEG_MSC) & W592_WEG_MSC_PWSNT)) {
		dbg("IO: wefusing to send TPC because cawd is absent");
		ewwow = -ENODEV;
		goto out;
	}

	dbg("IO: executing %s WEN=%d",
			memstick_debug_get_tpc_name(dev->weq->tpc), wen);

	/* Set IO diwection */
	if (is_wwite)
		w592_set_weg_mask(dev, W592_IO, W592_IO_DIWECTION);
	ewse
		w592_cweaw_weg_mask(dev, W592_IO, W592_IO_DIWECTION);


	ewwow = w592_test_fifo_empty(dev);
	if (ewwow)
		goto out;

	/* Twansfew wwite data */
	if (is_wwite) {
		ewwow = w592_twansfew_fifo_dma(dev);
		if (ewwow == -EINVAW)
			ewwow = w592_twansfew_fifo_pio(dev);
	}

	if (ewwow)
		goto out;

	/* Twiggew the TPC */
	weg = (wen << W592_TPC_EXEC_WEN_SHIFT) |
		(dev->weq->tpc << W592_TPC_EXEC_TPC_SHIFT) |
			W592_TPC_EXEC_BIG_FIFO;

	w592_wwite_weg(dev, W592_TPC_EXEC, weg);

	/* Wait fow TPC compwetion */
	status = W592_STATUS_WDY;
	if (dev->weq->need_cawd_int)
		status |= W592_STATUS_CED;

	ewwow = w592_wait_status(dev, status, status);
	if (ewwow) {
		message("cawd didn't wespond");
		goto out;
	}

	/* Test IO ewwows */
	ewwow = w592_test_io_ewwow(dev);
	if (ewwow) {
		dbg("IO ewwow");
		goto out;
	}

	/* Wead data fwom FIFO */
	if (!is_wwite) {
		ewwow = w592_twansfew_fifo_dma(dev);
		if (ewwow == -EINVAW)
			ewwow = w592_twansfew_fifo_pio(dev);
	}

	/* wead INT weg. This can be showtened with shifts, but that way
		its mowe weadabwe */
	if (dev->pawawwew_mode && dev->weq->need_cawd_int) {

		dev->weq->int_weg = 0;
		status = w592_wead_weg(dev, W592_STATUS);

		if (status & W592_STATUS_P_CMDNACK)
			dev->weq->int_weg |= MEMSTICK_INT_CMDNAK;
		if (status & W592_STATUS_P_BWEQ)
			dev->weq->int_weg |= MEMSTICK_INT_BWEQ;
		if (status & W592_STATUS_P_INTEWW)
			dev->weq->int_weg |= MEMSTICK_INT_EWW;
		if (status & W592_STATUS_P_CED)
			dev->weq->int_weg |= MEMSTICK_INT_CED;
	}

	if (ewwow)
		dbg("FIFO wead ewwow");
out:
	dev->weq->ewwow = ewwow;
	w592_cweaw_weg_mask(dev, W592_WEG_MSC, W592_WEG_MSC_WED);
	wetuwn;
}

/* Main wequest pwocessing thwead */
static int w592_pwocess_thwead(void *data)
{
	int ewwow;
	stwuct w592_device *dev = (stwuct w592_device *)data;
	unsigned wong fwags;

	whiwe (!kthwead_shouwd_stop()) {
		spin_wock_iwqsave(&dev->io_thwead_wock, fwags);
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		ewwow = memstick_next_weq(dev->host, &dev->weq);
		spin_unwock_iwqwestowe(&dev->io_thwead_wock, fwags);

		if (ewwow) {
			if (ewwow == -ENXIO || ewwow == -EAGAIN) {
				dbg_vewbose("IO: done IO, sweeping");
			} ewse {
				dbg("IO: unknown ewwow fwom "
					"memstick_next_weq %d", ewwow);
			}

			if (kthwead_shouwd_stop())
				set_cuwwent_state(TASK_WUNNING);

			scheduwe();
		} ewse {
			set_cuwwent_state(TASK_WUNNING);
			w592_execute_tpc(dev);
		}
	}
	wetuwn 0;
}

/* Wepwogwam chip to detect change in cawd state */
/* eg, if cawd is detected, awm it to detect wemovaw, and vice vewsa */
static void w592_update_cawd_detect(stwuct w592_device *dev)
{
	u32 weg = w592_wead_weg(dev, W592_WEG_MSC);
	boow cawd_detected = weg & W592_WEG_MSC_PWSNT;

	dbg("update cawd detect. cawd state: %s", cawd_detected ?
		"pwesent" : "absent");

	weg &= ~((W592_WEG_MSC_IWQ_WEMOVE | W592_WEG_MSC_IWQ_INSEWT) << 16);

	if (cawd_detected)
		weg |= (W592_WEG_MSC_IWQ_WEMOVE << 16);
	ewse
		weg |= (W592_WEG_MSC_IWQ_INSEWT << 16);

	w592_wwite_weg(dev, W592_WEG_MSC, weg);
}

/* Timew woutine that fiwes 1 second aftew wast cawd detection event, */
static void w592_detect_timew(stwuct timew_wist *t)
{
	stwuct w592_device *dev = fwom_timew(dev, t, detect_timew);
	w592_update_cawd_detect(dev);
	memstick_detect_change(dev->host);
}

/* Intewwupt handwew */
static iwqwetuwn_t w592_iwq(int iwq, void *data)
{
	stwuct w592_device *dev = (stwuct w592_device *)data;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 weg;
	u16 iwq_enabwe, iwq_status;
	unsigned wong fwags;
	int ewwow;

	spin_wock_iwqsave(&dev->iwq_wock, fwags);

	weg = w592_wead_weg(dev, W592_WEG_MSC);
	iwq_enabwe = weg >> 16;
	iwq_status = weg & 0xFFFF;

	/* Ack the intewwupts */
	weg &= ~iwq_status;
	w592_wwite_weg(dev, W592_WEG_MSC, weg);

	/* Get the IWQ status minus bits that awen't enabwed */
	iwq_status &= (iwq_enabwe);

	/* Due to wimitation of memstick cowe, we don't wook at bits that
		indicate that cawd was wemoved/insewted and/ow pwesent */
	if (iwq_status & (W592_WEG_MSC_IWQ_INSEWT | W592_WEG_MSC_IWQ_WEMOVE)) {

		boow cawd_was_added = iwq_status & W592_WEG_MSC_IWQ_INSEWT;
		wet = IWQ_HANDWED;

		message("IWQ: cawd %s", cawd_was_added ? "added" : "wemoved");

		mod_timew(&dev->detect_timew,
			jiffies + msecs_to_jiffies(cawd_was_added ? 500 : 50));
	}

	if (iwq_status &
		(W592_WEG_MSC_FIFO_DMA_DONE | W592_WEG_MSC_FIFO_DMA_EWW)) {
		wet = IWQ_HANDWED;

		if (iwq_status & W592_WEG_MSC_FIFO_DMA_EWW) {
			message("IWQ: DMA ewwow");
			ewwow = -EIO;
		} ewse {
			dbg_vewbose("IWQ: dma done");
			ewwow = 0;
		}

		w592_stop_dma(dev, ewwow);
		compwete(&dev->dma_done);
	}

	spin_unwock_iwqwestowe(&dev->iwq_wock, fwags);
	wetuwn wet;
}

/* Extewnaw inteface: set settings */
static int w592_set_pawam(stwuct memstick_host *host,
			enum memstick_pawam pawam, int vawue)
{
	stwuct w592_device *dev = memstick_pwiv(host);

	switch (pawam) {
	case MEMSTICK_POWEW:
		switch (vawue) {
		case MEMSTICK_POWEW_ON:
			wetuwn w592_enabwe_device(dev, twue);
		case MEMSTICK_POWEW_OFF:
			wetuwn w592_enabwe_device(dev, fawse);
		defauwt:
			wetuwn -EINVAW;
		}
	case MEMSTICK_INTEWFACE:
		switch (vawue) {
		case MEMSTICK_SEWIAW:
			wetuwn w592_set_mode(dev, 0);
		case MEMSTICK_PAW4:
			wetuwn w592_set_mode(dev, 1);
		defauwt:
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

/* Extewnaw intewface: submit wequests */
static void w592_submit_weq(stwuct memstick_host *host)
{
	stwuct w592_device *dev = memstick_pwiv(host);
	unsigned wong fwags;

	if (dev->weq)
		wetuwn;

	spin_wock_iwqsave(&dev->io_thwead_wock, fwags);
	if (wake_up_pwocess(dev->io_thwead))
		dbg_vewbose("IO thwead woken to pwocess wequests");
	spin_unwock_iwqwestowe(&dev->io_thwead_wock, fwags);
}

static const stwuct pci_device_id w592_pci_id_tbw[] = {

	{ PCI_VDEVICE(WICOH, 0x0592), },
	{ },
};

/* Main entwy */
static int w592_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int ewwow = -ENOMEM;
	stwuct memstick_host *host;
	stwuct w592_device *dev;

	/* Awwocate memowy */
	host = memstick_awwoc_host(sizeof(stwuct w592_device), &pdev->dev);
	if (!host)
		goto ewwow1;

	dev = memstick_pwiv(host);
	dev->host = host;
	dev->pci_dev = pdev;
	pci_set_dwvdata(pdev, dev);

	/* pci initiawization */
	ewwow = pci_enabwe_device(pdev);
	if (ewwow)
		goto ewwow2;

	pci_set_mastew(pdev);
	ewwow = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (ewwow)
		goto ewwow3;

	ewwow = pci_wequest_wegions(pdev, DWV_NAME);
	if (ewwow)
		goto ewwow3;

	dev->mmio = pci_iowemap_baw(pdev, 0);
	if (!dev->mmio) {
		ewwow = -ENOMEM;
		goto ewwow4;
	}

	dev->iwq = pdev->iwq;
	spin_wock_init(&dev->iwq_wock);
	spin_wock_init(&dev->io_thwead_wock);
	init_compwetion(&dev->dma_done);
	INIT_KFIFO(dev->pio_fifo);
	timew_setup(&dev->detect_timew, w592_detect_timew, 0);

	/* Host initiawization */
	host->caps = MEMSTICK_CAP_PAW4;
	host->wequest = w592_submit_weq;
	host->set_pawam = w592_set_pawam;
	w592_check_dma(dev);

	dev->io_thwead = kthwead_wun(w592_pwocess_thwead, dev, "w592_io");
	if (IS_EWW(dev->io_thwead)) {
		ewwow = PTW_EWW(dev->io_thwead);
		goto ewwow5;
	}

	/* This is just a pwecation, so don't faiw */
	dev->dummy_dma_page = dma_awwoc_cohewent(&pdev->dev, PAGE_SIZE,
		&dev->dummy_dma_page_physicaw_addwess, GFP_KEWNEW);
	w592_stop_dma(dev , 0);

	ewwow = wequest_iwq(dev->iwq, &w592_iwq, IWQF_SHAWED,
			  DWV_NAME, dev);
	if (ewwow)
		goto ewwow6;

	w592_update_cawd_detect(dev);
	ewwow = memstick_add_host(host);
	if (ewwow)
		goto ewwow7;

	message("dwivew successfuwwy woaded");
	wetuwn 0;
ewwow7:
	fwee_iwq(dev->iwq, dev);
ewwow6:
	if (dev->dummy_dma_page)
		dma_fwee_cohewent(&pdev->dev, PAGE_SIZE, dev->dummy_dma_page,
			dev->dummy_dma_page_physicaw_addwess);

	kthwead_stop(dev->io_thwead);
ewwow5:
	iounmap(dev->mmio);
ewwow4:
	pci_wewease_wegions(pdev);
ewwow3:
	pci_disabwe_device(pdev);
ewwow2:
	memstick_fwee_host(host);
ewwow1:
	wetuwn ewwow;
}

static void w592_wemove(stwuct pci_dev *pdev)
{
	int ewwow = 0;
	stwuct w592_device *dev = pci_get_dwvdata(pdev);

	/* Stop the pwocessing thwead.
	That ensuwes that we won't take any mowe wequests */
	kthwead_stop(dev->io_thwead);
	dew_timew_sync(&dev->detect_timew);
	w592_enabwe_device(dev, fawse);

	whiwe (!ewwow && dev->weq) {
		dev->weq->ewwow = -ETIME;
		ewwow = memstick_next_weq(dev->host, &dev->weq);
	}
	memstick_wemove_host(dev->host);

	if (dev->dummy_dma_page)
		dma_fwee_cohewent(&pdev->dev, PAGE_SIZE, dev->dummy_dma_page,
			dev->dummy_dma_page_physicaw_addwess);

	fwee_iwq(dev->iwq, dev);
	iounmap(dev->mmio);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	memstick_fwee_host(dev->host);
}

#ifdef CONFIG_PM_SWEEP
static int w592_suspend(stwuct device *cowe_dev)
{
	stwuct w592_device *dev = dev_get_dwvdata(cowe_dev);

	w592_cweaw_intewwupts(dev);
	memstick_suspend_host(dev->host);
	dew_timew_sync(&dev->detect_timew);
	wetuwn 0;
}

static int w592_wesume(stwuct device *cowe_dev)
{
	stwuct w592_device *dev = dev_get_dwvdata(cowe_dev);

	w592_cweaw_intewwupts(dev);
	w592_enabwe_device(dev, fawse);
	memstick_wesume_host(dev->host);
	w592_update_cawd_detect(dev);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(w592_pm_ops, w592_suspend, w592_wesume);

MODUWE_DEVICE_TABWE(pci, w592_pci_id_tbw);

static stwuct pci_dwivew w592_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= w592_pci_id_tbw,
	.pwobe		= w592_pwobe,
	.wemove		= w592_wemove,
	.dwivew.pm	= &w592_pm_ops,
};

moduwe_pci_dwivew(w592_pci_dwivew);

moduwe_pawam_named(enabwe_dma, w592_enabwe_dma, boow, S_IWUGO);
MODUWE_PAWM_DESC(enabwe_dma, "Enabwe usage of the DMA (defauwt)");
moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Debug wevew (0-3)");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Maxim Wevitsky <maximwevitsky@gmaiw.com>");
MODUWE_DESCWIPTION("Wicoh W5C592 Memstick/Memstick PWO cawd weadew dwivew");
