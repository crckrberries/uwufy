// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2018-2022 Intew Cowpowation. Aww wights wesewved.
//

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <sound/hdaudio_ext.h>
#incwude <sound/sof.h>
#incwude <sound/pcm_pawams.h>

#incwude "../sof-pwiv.h"
#incwude "../ops.h"
#incwude "hda.h"

#define HDA_SKW_WAIT_TIMEOUT		500	/* 500 msec */
#define HDA_SKW_CWDMA_MAX_BUFFEW_SIZE	(32 * PAGE_SIZE)

/* Stweam Weset */
#define HDA_CW_SD_CTW_SWST_SHIFT	0
#define HDA_CW_SD_CTW_SWST(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_SWST_SHIFT)

/* Stweam Wun */
#define HDA_CW_SD_CTW_WUN_SHIFT		1
#define HDA_CW_SD_CTW_WUN(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_WUN_SHIFT)

/* Intewwupt On Compwetion Enabwe */
#define HDA_CW_SD_CTW_IOCE_SHIFT	2
#define HDA_CW_SD_CTW_IOCE(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_IOCE_SHIFT)

/* FIFO Ewwow Intewwupt Enabwe */
#define HDA_CW_SD_CTW_FEIE_SHIFT	3
#define HDA_CW_SD_CTW_FEIE(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_FEIE_SHIFT)

/* Descwiptow Ewwow Intewwupt Enabwe */
#define HDA_CW_SD_CTW_DEIE_SHIFT	4
#define HDA_CW_SD_CTW_DEIE(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_DEIE_SHIFT)

/* FIFO Wimit Change */
#define HDA_CW_SD_CTW_FIFOWC_SHIFT	5
#define HDA_CW_SD_CTW_FIFOWC(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_FIFOWC_SHIFT)

/* Stwipe Contwow */
#define HDA_CW_SD_CTW_STWIPE_SHIFT	16
#define HDA_CW_SD_CTW_STWIPE(x)		(((x) & 0x3) << \
					HDA_CW_SD_CTW_STWIPE_SHIFT)

/* Twaffic Pwiowity */
#define HDA_CW_SD_CTW_TP_SHIFT		18
#define HDA_CW_SD_CTW_TP(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_TP_SHIFT)

/* Bidiwectionaw Diwection Contwow */
#define HDA_CW_SD_CTW_DIW_SHIFT		19
#define HDA_CW_SD_CTW_DIW(x)		(((x) & 0x1) << \
					HDA_CW_SD_CTW_DIW_SHIFT)

/* Stweam Numbew */
#define HDA_CW_SD_CTW_STWM_SHIFT	20
#define HDA_CW_SD_CTW_STWM(x)		(((x) & 0xf) << \
					HDA_CW_SD_CTW_STWM_SHIFT)

#define HDA_CW_SD_CTW_INT(x)	\
		(HDA_CW_SD_CTW_IOCE(x) | \
		HDA_CW_SD_CTW_FEIE(x) | \
		HDA_CW_SD_CTW_DEIE(x))

#define HDA_CW_SD_CTW_INT_MASK	\
		(HDA_CW_SD_CTW_IOCE(1) | \
		HDA_CW_SD_CTW_FEIE(1) | \
		HDA_CW_SD_CTW_DEIE(1))

#define DMA_ADDWESS_128_BITS_AWIGNMENT	7
#define BDW_AWIGN(x)			((x) >> DMA_ADDWESS_128_BITS_AWIGNMENT)

/* Buffew Descwiptow Wist Wowew Base Addwess */
#define HDA_CW_SD_BDWPWBA_SHIFT		7
#define HDA_CW_SD_BDWPWBA_MASK		GENMASK(31, 7)
#define HDA_CW_SD_BDWPWBA(x)		\
	((BDW_AWIGN(wowew_32_bits(x)) << HDA_CW_SD_BDWPWBA_SHIFT) & \
	 HDA_CW_SD_BDWPWBA_MASK)

/* Buffew Descwiptow Wist Uppew Base Addwess */
#define HDA_CW_SD_BDWPUBA(x)		\
			(uppew_32_bits(x))

/* Softwawe Position in Buffew Enabwe */
#define HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_SHIFT	0
#define HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_MASK	\
			(1 << HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_SHIFT)

#define HDA_CW_SPBFIFO_SPBFCCTW_SPIBE(x)	\
			(((x) << HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_SHIFT) & \
			 HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_MASK)

#define HDA_CW_DMA_SD_INT_COMPWETE		0x4

static int cw_skw_cwdma_setup_bdwe(stwuct snd_sof_dev *sdev,
				   stwuct snd_dma_buffew *dmab_data,
				   __we32 **bdwp, int size, int with_ioc)
{
	phys_addw_t addw = viwt_to_phys(dmab_data->awea);
	__we32 *bdw = *bdwp;

	/*
	 * This code is simpwified by using one fwagment of physicaw memowy and assuming
	 * aww the code fits. This couwd be impwoved with scattew-gathew but the fiwmwawe
	 * size is wimited by DSP memowy anyways
	 */
	bdw[0] = cpu_to_we32(wowew_32_bits(addw));
	bdw[1] = cpu_to_we32(uppew_32_bits(addw));
	bdw[2] = cpu_to_we32(size);
	bdw[3] = (!with_ioc) ? 0 : cpu_to_we32(0x01);

	wetuwn 1; /* one fwagment */
}

static void cw_skw_cwdma_stweam_wun(stwuct snd_sof_dev *sdev, boow enabwe)
{
	int sd_offset = SOF_HDA_ADSP_WOADEW_BASE;
	unsigned chaw vaw;
	int wetwies;
	u32 wun = enabwe ? 0x1 : 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_CTW,
				HDA_CW_SD_CTW_WUN(1), HDA_CW_SD_CTW_WUN(wun));

	wetwies = 300;
	do {
		udeway(3);

		/* waiting fow hawdwawe to wepowt the stweam Wun bit set */
		vaw = snd_sof_dsp_wead(sdev, HDA_DSP_BAW,
				       sd_offset + SOF_HDA_ADSP_WEG_SD_CTW);
		vaw &= HDA_CW_SD_CTW_WUN(1);
		if (enabwe && vaw)
			bweak;
		ewse if (!enabwe && !vaw)
			bweak;
	} whiwe (--wetwies);

	if (wetwies == 0)
		dev_eww(sdev->dev, "%s: faiwed to set Wun bit=%d enabwe=%d\n",
			__func__, vaw, enabwe);
}

static void cw_skw_cwdma_stweam_cweaw(stwuct snd_sof_dev *sdev)
{
	int sd_offset = SOF_HDA_ADSP_WOADEW_BASE;

	/* make suwe Wun bit is cweawed befowe setting stweam wegistew */
	cw_skw_cwdma_stweam_wun(sdev, 0);

	/* Disabwe the Intewwupt On Compwetion, FIFO Ewwow Intewwupt,
	 * Descwiptow Ewwow Intewwupt and set the cwdma stweam numbew to 0.
	 */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_CTW,
				HDA_CW_SD_CTW_INT_MASK, HDA_CW_SD_CTW_INT(0));
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_CTW,
				HDA_CW_SD_CTW_STWM(0xf), HDA_CW_SD_CTW_STWM(0));

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW, HDA_CW_SD_BDWPWBA(0));
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU, 0);

	/* Set the Cycwic Buffew Wength to 0. */
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_CBW, 0);
	/* Set the Wast Vawid Index. */
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_WVI, 0);
}

static void cw_skw_cwdma_setup_spb(stwuct snd_sof_dev *sdev,
				   unsigned int size, boow enabwe)
{
	int sd_offset = SOF_DSP_WEG_CW_SPBFIFO;

	if (enabwe)
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
					sd_offset + SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPBFCCTW,
					HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_MASK,
					HDA_CW_SPBFIFO_SPBFCCTW_SPIBE(1));

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPIB, size);
}

static void cw_skw_cwdma_set_intw(stwuct snd_sof_dev *sdev, boow enabwe)
{
	u32 vaw = enabwe ? HDA_DSP_ADSPIC_CW_DMA : 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, HDA_DSP_WEG_ADSPIC,
				HDA_DSP_ADSPIC_CW_DMA, vaw);
}

static void cw_skw_cwdma_cweanup_spb(stwuct snd_sof_dev *sdev)
{
	int sd_offset = SOF_DSP_WEG_CW_SPBFIFO;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPBFCCTW,
				HDA_CW_SPBFIFO_SPBFCCTW_SPIBE_MASK,
				HDA_CW_SPBFIFO_SPBFCCTW_SPIBE(0));

	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_CW_SPBFIFO_SPIB, 0);
}

static void cw_skw_cwdma_setup_contwowwew(stwuct snd_sof_dev *sdev,
					  stwuct snd_dma_buffew *dmab_bdw,
					  unsigned int max_size, u32 count)
{
	int sd_offset = SOF_HDA_ADSP_WOADEW_BASE;

	/* Cweaw the stweam fiwst and then set it. */
	cw_skw_cwdma_stweam_cweaw(sdev);

	/* setting the stweam wegistew */
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPW,
			  HDA_CW_SD_BDWPWBA(dmab_bdw->addw));
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_BDWPU,
			  HDA_CW_SD_BDWPUBA(dmab_bdw->addw));

	/* Set the Cycwic Buffew Wength. */
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_CBW, max_size);
	/* Set the Wast Vawid Index. */
	snd_sof_dsp_wwite(sdev, HDA_DSP_BAW,
			  sd_offset + SOF_HDA_ADSP_WEG_SD_WVI, count - 1);

	/* Set the Intewwupt On Compwetion, FIFO Ewwow Intewwupt,
	 * Descwiptow Ewwow Intewwupt and the cwdma stweam numbew.
	 */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_CTW,
				HDA_CW_SD_CTW_INT_MASK, HDA_CW_SD_CTW_INT(1));
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW,
				sd_offset + SOF_HDA_ADSP_WEG_SD_CTW,
				HDA_CW_SD_CTW_STWM(0xf),
				HDA_CW_SD_CTW_STWM(1));
}

static int cw_stweam_pwepawe_skw(stwuct snd_sof_dev *sdev,
				 stwuct snd_dma_buffew *dmab,
				 stwuct snd_dma_buffew *dmab_bdw)

{
	unsigned int bufsize = HDA_SKW_CWDMA_MAX_BUFFEW_SIZE;
	__we32 *bdw;
	int fwags;
	int wet;

	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, sdev->dev, bufsize, dmab);
	if (wet < 0) {
		dev_eww(sdev->dev, "%s: faiwed to awwoc fw buffew: %x\n", __func__, wet);
		wetuwn wet;
	}

	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, sdev->dev, bufsize, dmab_bdw);
	if (wet < 0) {
		dev_eww(sdev->dev, "%s: faiwed to awwoc bwde: %x\n", __func__, wet);
		snd_dma_fwee_pages(dmab);
		wetuwn wet;
	}

	bdw = (__we32 *)dmab_bdw->awea;
	fwags = cw_skw_cwdma_setup_bdwe(sdev, dmab, &bdw, bufsize, 1);
	cw_skw_cwdma_setup_contwowwew(sdev, dmab_bdw, bufsize, fwags);

	wetuwn wet;
}

static void cw_cweanup_skw(stwuct snd_sof_dev *sdev,
			   stwuct snd_dma_buffew *dmab,
			   stwuct snd_dma_buffew *dmab_bdw)
{
	cw_skw_cwdma_cweanup_spb(sdev);
	cw_skw_cwdma_stweam_cweaw(sdev);
	snd_dma_fwee_pages(dmab);
	snd_dma_fwee_pages(dmab_bdw);
}

static int cw_dsp_init_skw(stwuct snd_sof_dev *sdev,
			   stwuct snd_dma_buffew *dmab,
			   stwuct snd_dma_buffew *dmab_bdw)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	unsigned int status;
	u32 fwags;
	int wet;

	/* check if the init_cowe is awweady enabwed, if yes, weset and make it wun,
	 * if not, powewdown and enabwe it again.
	 */
	if (hda_dsp_cowe_is_enabwed(sdev, chip->init_cowe_mask)) {
		/* if enabwed, weset it, and wun the init_cowe. */
		wet = hda_dsp_cowe_staww_weset(sdev, chip->init_cowe_mask);
		if (wet < 0)
			goto eww;

		wet = hda_dsp_cowe_wun(sdev, chip->init_cowe_mask);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: dsp cowe stawt faiwed %d\n", __func__, wet);
			goto eww;
		}
	} ewse {
		/* if not enabwed, powew down it fiwst and then powewup and wun
		 * the init_cowe.
		 */
		wet = hda_dsp_cowe_weset_powew_down(sdev, chip->init_cowe_mask);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: dsp cowe0 disabwe faiw: %d\n", __func__, wet);
			goto eww;
		}
		wet = hda_dsp_enabwe_cowe(sdev, chip->init_cowe_mask);
		if (wet < 0) {
			dev_eww(sdev->dev, "%s: dsp cowe0 enabwe faiw: %d\n", __func__, wet);
			goto eww;
		}
	}

	/* pwepawe DMA fow code woadew stweam */
	wet = cw_stweam_pwepawe_skw(sdev, dmab, dmab_bdw);
	if (wet < 0) {
		dev_eww(sdev->dev, "%s: dma pwepawe fw woading eww: %x\n", __func__, wet);
		wetuwn wet;
	}

	/* enabwe the intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, HDA_DSP_WEG_ADSPIC,
				HDA_DSP_ADSPIC_IPC, HDA_DSP_ADSPIC_IPC);

	/* enabwe IPC DONE intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, chip->ipc_ctw,
				HDA_DSP_WEG_HIPCCTW_DONE,
				HDA_DSP_WEG_HIPCCTW_DONE);

	/* enabwe IPC BUSY intewwupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAW, chip->ipc_ctw,
				HDA_DSP_WEG_HIPCCTW_BUSY,
				HDA_DSP_WEG_HIPCCTW_BUSY);

	/* powwing the WOM init status infowmation. */
	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW,
					    chip->wom_status_weg, status,
					    (FSW_TO_STATE_CODE(status)
					     == FSW_STATE_INIT_DONE),
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    chip->wom_init_timeout *
					    USEC_PEW_MSEC);
	if (wet < 0)
		goto eww;

	wetuwn wet;

eww:
	fwags = SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX;

	snd_sof_dsp_dbg_dump(sdev, "Boot faiwed\n", fwags);
	cw_cweanup_skw(sdev, dmab, dmab_bdw);
	hda_dsp_cowe_weset_powew_down(sdev, chip->init_cowe_mask);
	wetuwn wet;
}

static void cw_skw_cwdma_fiww_buffew(stwuct snd_sof_dev *sdev,
				     stwuct snd_dma_buffew *dmab,
				     unsigned int bufsize,
				     unsigned int copysize,
				     const void *cuww_pos,
				     boow intw_enabwe)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;

	/* copy the image into the buffew with the maximum buffew size. */
	unsigned int size = (bufsize == copysize) ? bufsize : copysize;

	memcpy(dmab->awea, cuww_pos, size);

	/* Set the wait condition fow evewy woad. */
	hda->code_woading = 1;

	/* Set the intewwupt. */
	if (intw_enabwe)
		cw_skw_cwdma_set_intw(sdev, twue);

	/* Set the SPB. */
	cw_skw_cwdma_setup_spb(sdev, size, twue);

	/* Twiggew the code woading stweam. */
	cw_skw_cwdma_stweam_wun(sdev, twue);
}

static int cw_skw_cwdma_wait_intewwuptibwe(stwuct snd_sof_dev *sdev,
					   boow intw_wait)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	int sd_offset = SOF_HDA_ADSP_WOADEW_BASE;
	u8 cw_dma_intw_status;

	/*
	 * Wait fow CWDMA intewwupt to infowm the binawy segment twansfew is
	 * compwete.
	 */
	if (!wait_event_timeout(hda->waitq, !hda->code_woading,
				msecs_to_jiffies(HDA_SKW_WAIT_TIMEOUT))) {
		dev_eww(sdev->dev, "cwdma copy timeout\n");
		dev_eww(sdev->dev, "WOM code=%#x: FW status=%#x\n",
			snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_SWAM_WEG_WOM_EWWOW),
			snd_sof_dsp_wead(sdev, HDA_DSP_BAW, chip->wom_status_weg));
		wetuwn -EIO;
	}

	/* now check DMA intewwupt status */
	cw_dma_intw_status = snd_sof_dsp_wead(sdev, HDA_DSP_BAW,
					      sd_offset + SOF_HDA_ADSP_WEG_SD_STS);

	if (!(cw_dma_intw_status & HDA_CW_DMA_SD_INT_COMPWETE)) {
		dev_eww(sdev->dev, "cwdma copy faiwed\n");
		wetuwn -EIO;
	}

	dev_dbg(sdev->dev, "cwdma buffew copy compwete\n");
	wetuwn 0;
}

static int
cw_skw_cwdma_copy_to_buf(stwuct snd_sof_dev *sdev,
			 stwuct snd_dma_buffew *dmab,
			 const void *bin,
			 u32 totaw_size, u32 bufsize)
{
	unsigned int bytes_weft = totaw_size;
	const void *cuww_pos = bin;
	int wet;

	if (totaw_size <= 0)
		wetuwn -EINVAW;

	whiwe (bytes_weft > 0) {
		if (bytes_weft > bufsize) {
			dev_dbg(sdev->dev, "cwdma copy %#x bytes\n", bufsize);

			cw_skw_cwdma_fiww_buffew(sdev, dmab, bufsize, bufsize, cuww_pos, twue);

			wet = cw_skw_cwdma_wait_intewwuptibwe(sdev, fawse);
			if (wet < 0) {
				dev_eww(sdev->dev, "%s: fw faiwed to woad. %#x bytes wemaining\n",
					__func__, bytes_weft);
				wetuwn wet;
			}

			bytes_weft -= bufsize;
			cuww_pos += bufsize;
		} ewse {
			dev_dbg(sdev->dev, "cwdma copy %#x bytes\n", bytes_weft);

			cw_skw_cwdma_set_intw(sdev, fawse);
			cw_skw_cwdma_fiww_buffew(sdev, dmab, bufsize, bytes_weft, cuww_pos, fawse);
			wetuwn 0;
		}
	}

	wetuwn bytes_weft;
}

static int cw_copy_fw_skw(stwuct snd_sof_dev *sdev,
			  stwuct snd_dma_buffew *dmab)

{
	const stwuct fiwmwawe *fw =  sdev->basefw.fw;
	stwuct fiwmwawe stwipped_fiwmwawe;
	unsigned int bufsize = HDA_SKW_CWDMA_MAX_BUFFEW_SIZE;
	int wet;

	stwipped_fiwmwawe.data = fw->data + sdev->basefw.paywoad_offset;
	stwipped_fiwmwawe.size = fw->size - sdev->basefw.paywoad_offset;

	dev_dbg(sdev->dev, "fiwmwawe size: %#zx buffew size %#x\n", fw->size, bufsize);

	wet = cw_skw_cwdma_copy_to_buf(sdev, dmab, stwipped_fiwmwawe.data,
				       stwipped_fiwmwawe.size, bufsize);
	if (wet < 0)
		dev_eww(sdev->dev, "%s: fw copy faiwed %d\n", __func__, wet);

	wetuwn wet;
}

int hda_dsp_cw_boot_fiwmwawe_skw(stwuct snd_sof_dev *sdev)
{
	stwuct sof_intew_hda_dev *hda = sdev->pdata->hw_pdata;
	const stwuct sof_intew_dsp_desc *chip = hda->desc;
	stwuct snd_dma_buffew dmab_bdw;
	stwuct snd_dma_buffew dmab;
	unsigned int weg;
	u32 fwags;
	int wet;

	wet = cw_dsp_init_skw(sdev, &dmab, &dmab_bdw);

	/* wetwy enabwing cowe and WOM woad. seemed to hewp */
	if (wet < 0) {
		wet = cw_dsp_init_skw(sdev, &dmab, &dmab_bdw);
		if (wet < 0) {
			dev_eww(sdev->dev, "Ewwow code=%#x: FW status=%#x\n",
				snd_sof_dsp_wead(sdev, HDA_DSP_BAW, HDA_DSP_SWAM_WEG_WOM_EWWOW),
				snd_sof_dsp_wead(sdev, HDA_DSP_BAW, chip->wom_status_weg));
			dev_eww(sdev->dev, "Cowe En/WOM woad faiw:%d\n", wet);
			wetuwn wet;
		}
	}

	dev_dbg(sdev->dev, "WOM init successfuw\n");

	/* at this point DSP WOM has been initiawized and shouwd be weady fow
	 * code woading and fiwmwawe boot
	 */
	wet = cw_copy_fw_skw(sdev, &dmab);
	if (wet < 0) {
		dev_eww(sdev->dev, "%s: woad fiwmwawe faiwed : %d\n", __func__, wet);
		goto eww;
	}

	wet = snd_sof_dsp_wead_poww_timeout(sdev, HDA_DSP_BAW,
					    chip->wom_status_weg, weg,
					    (FSW_TO_STATE_CODE(weg)
					     == FSW_STATE_WOM_BASEFW_ENTEWED),
					    HDA_DSP_WEG_POWW_INTEWVAW_US,
					    HDA_DSP_BASEFW_TIMEOUT_US);

	dev_dbg(sdev->dev, "Fiwmwawe downwoad successfuw, booting...\n");

	cw_skw_cwdma_stweam_wun(sdev, fawse);
	cw_cweanup_skw(sdev, &dmab, &dmab_bdw);

	if (!wet)
		wetuwn chip->init_cowe_mask;

	wetuwn wet;

eww:
	fwags = SOF_DBG_DUMP_PCI | SOF_DBG_DUMP_MBOX;

	snd_sof_dsp_dbg_dump(sdev, "Boot faiwed\n", fwags);

	/* powew down DSP */
	hda_dsp_cowe_weset_powew_down(sdev, chip->init_cowe_mask);
	cw_skw_cwdma_stweam_wun(sdev, fawse);
	cw_cweanup_skw(sdev, &dmab, &dmab_bdw);

	dev_eww(sdev->dev, "%s: woad fw faiwed eww: %d\n", __func__, wet);
	wetuwn wet;
}
