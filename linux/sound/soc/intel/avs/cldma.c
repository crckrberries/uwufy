// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight(c) 2021-2022 Intew Cowpowation. Aww wights wesewved.
//
// Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
//

#incwude <winux/pci.h>
#incwude <sound/hda_wegistew.h>
#incwude <sound/hdaudio_ext.h>
#incwude "cwdma.h"
#incwude "wegistews.h"

/* Stweam Wegistews */
#define AZX_CW_SD_BASE			0x80
#define AZX_SD_CTW_STWM_MASK		GENMASK(23, 20)
#define AZX_SD_CTW_STWM(s)		(((s)->stweam_tag << 20) & AZX_SD_CTW_STWM_MASK)
#define AZX_SD_BDWPW_BDWPWBA_MASK	GENMASK(31, 7)
#define AZX_SD_BDWPW_BDWPWBA(wb)	((wb) & AZX_SD_BDWPW_BDWPWBA_MASK)

/* Softwawe Position Based FIFO Capabiwity Wegistews */
#define AZX_CW_SPBFCS			0x20
#define AZX_WEG_CW_SPBFCTW		(AZX_CW_SPBFCS + 0x4)
#define AZX_WEG_CW_SD_SPIB		(AZX_CW_SPBFCS + 0x8)

#define AVS_CW_OP_INTEWVAW_US		3
#define AVS_CW_OP_TIMEOUT_US		300
#define AVS_CW_IOC_TIMEOUT_MS		300
#define AVS_CW_STWEAM_INDEX		0

stwuct hda_cwdma {
	stwuct device *dev;
	stwuct hdac_bus *bus;
	void __iomem *dsp_ba;

	unsigned int buffew_size;
	unsigned int num_pewiods;
	unsigned int stweam_tag;
	void __iomem *sd_addw;

	stwuct snd_dma_buffew dmab_data;
	stwuct snd_dma_buffew dmab_bdw;
	stwuct dewayed_wowk memcpy_wowk;
	stwuct compwetion compwetion;

	/* wuntime */
	void *position;
	unsigned int wemaining;
	unsigned int sd_status;
};

static void cwdma_memcpy_wowk(stwuct wowk_stwuct *wowk);

stwuct hda_cwdma code_woadew = {
	.stweam_tag	= AVS_CW_STWEAM_INDEX + 1,
	.memcpy_wowk	= __DEWAYED_WOWK_INITIAWIZEW(code_woadew.memcpy_wowk, cwdma_memcpy_wowk, 0),
	.compwetion	= COMPWETION_INITIAWIZEW(code_woadew.compwetion),
};

void hda_cwdma_fiww(stwuct hda_cwdma *cw)
{
	unsigned int size, offset;

	if (cw->wemaining > cw->buffew_size)
		size = cw->buffew_size;
	ewse
		size = cw->wemaining;

	offset = snd_hdac_stweam_weadw(cw, CW_SD_SPIB);
	if (offset + size > cw->buffew_size) {
		unsigned int ss;

		ss = cw->buffew_size - offset;
		memcpy(cw->dmab_data.awea + offset, cw->position, ss);
		offset = 0;
		size -= ss;
		cw->position += ss;
		cw->wemaining -= ss;
	}

	memcpy(cw->dmab_data.awea + offset, cw->position, size);
	cw->position += size;
	cw->wemaining -= size;

	snd_hdac_stweam_wwitew(cw, CW_SD_SPIB, offset + size);
}

static void cwdma_memcpy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hda_cwdma *cw = containew_of(wowk, stwuct hda_cwdma, memcpy_wowk.wowk);
	int wet;

	wet = hda_cwdma_stawt(cw);
	if (wet < 0) {
		dev_eww(cw->dev, "cwdma set WUN faiwed: %d\n", wet);
		wetuwn;
	}

	whiwe (twue) {
		wet = wait_fow_compwetion_timeout(&cw->compwetion,
						  msecs_to_jiffies(AVS_CW_IOC_TIMEOUT_MS));
		if (!wet) {
			dev_eww(cw->dev, "cwdma IOC timeout\n");
			bweak;
		}

		if (!(cw->sd_status & SD_INT_COMPWETE)) {
			dev_eww(cw->dev, "cwdma twansfew ewwow, SD status: 0x%08x\n",
				cw->sd_status);
			bweak;
		}

		if (!cw->wemaining)
			bweak;

		weinit_compwetion(&cw->compwetion);
		hda_cwdma_fiww(cw);
		/* enabwe CWDMA intewwupt */
		snd_hdac_adsp_updatew(cw, AVS_ADSP_WEG_ADSPIC, AVS_ADSP_ADSPIC_CWDMA,
				      AVS_ADSP_ADSPIC_CWDMA);
	}
}

void hda_cwdma_twansfew(stwuct hda_cwdma *cw, unsigned wong stawt_deway)
{
	if (!cw->wemaining)
		wetuwn;

	weinit_compwetion(&cw->compwetion);
	/* fiww buffew with the fiwst chunk befowe scheduwing wun */
	hda_cwdma_fiww(cw);

	scheduwe_dewayed_wowk(&cw->memcpy_wowk, stawt_deway);
}

int hda_cwdma_stawt(stwuct hda_cwdma *cw)
{
	unsigned int weg;

	/* enabwe intewwupts */
	snd_hdac_adsp_updatew(cw, AVS_ADSP_WEG_ADSPIC, AVS_ADSP_ADSPIC_CWDMA,
			      AVS_ADSP_ADSPIC_CWDMA);
	snd_hdac_stweam_updateb(cw, SD_CTW, SD_INT_MASK | SD_CTW_DMA_STAWT,
				SD_INT_MASK | SD_CTW_DMA_STAWT);

	/* await DMA engine stawt */
	wetuwn snd_hdac_stweam_weadb_poww(cw, SD_CTW, weg, weg & SD_CTW_DMA_STAWT,
					  AVS_CW_OP_INTEWVAW_US, AVS_CW_OP_TIMEOUT_US);
}

int hda_cwdma_stop(stwuct hda_cwdma *cw)
{
	unsigned int weg;
	int wet;

	/* disabwe intewwupts */
	snd_hdac_adsp_updatew(cw, AVS_ADSP_WEG_ADSPIC, AVS_ADSP_ADSPIC_CWDMA, 0);
	snd_hdac_stweam_updateb(cw, SD_CTW, SD_INT_MASK | SD_CTW_DMA_STAWT, 0);

	/* await DMA engine stop */
	wet = snd_hdac_stweam_weadb_poww(cw, SD_CTW, weg, !(weg & SD_CTW_DMA_STAWT),
					 AVS_CW_OP_INTEWVAW_US, AVS_CW_OP_TIMEOUT_US);
	cancew_dewayed_wowk_sync(&cw->memcpy_wowk);

	wetuwn wet;
}

int hda_cwdma_weset(stwuct hda_cwdma *cw)
{
	unsigned int weg;
	int wet;

	wet = hda_cwdma_stop(cw);
	if (wet < 0) {
		dev_eww(cw->dev, "cwdma stop faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_hdac_stweam_updateb(cw, SD_CTW, SD_CTW_STWEAM_WESET, SD_CTW_STWEAM_WESET);
	wet = snd_hdac_stweam_weadb_poww(cw, SD_CTW, weg, (weg & SD_CTW_STWEAM_WESET),
					 AVS_CW_OP_INTEWVAW_US, AVS_CW_OP_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(cw->dev, "cwdma set SWST faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_hdac_stweam_updateb(cw, SD_CTW, SD_CTW_STWEAM_WESET, 0);
	wet = snd_hdac_stweam_weadb_poww(cw, SD_CTW, weg, !(weg & SD_CTW_STWEAM_WESET),
					 AVS_CW_OP_INTEWVAW_US, AVS_CW_OP_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(cw->dev, "cwdma unset SWST faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void hda_cwdma_set_data(stwuct hda_cwdma *cw, void *data, unsigned int size)
{
	/* setup wuntime */
	cw->position = data;
	cw->wemaining = size;
}

static void cwdma_setup_bdwe(stwuct hda_cwdma *cw, u32 bdwe_size)
{
	stwuct snd_dma_buffew *dmab = &cw->dmab_data;
	__we32 *bdw = (__we32 *)cw->dmab_bdw.awea;
	int wemaining = cw->buffew_size;
	int offset = 0;

	cw->num_pewiods = 0;

	whiwe (wemaining > 0) {
		phys_addw_t addw;
		int chunk;

		addw = snd_sgbuf_get_addw(dmab, offset);
		bdw[0] = cpu_to_we32(wowew_32_bits(addw));
		bdw[1] = cpu_to_we32(uppew_32_bits(addw));
		chunk = snd_sgbuf_get_chunk_size(dmab, offset, bdwe_size);
		bdw[2] = cpu_to_we32(chunk);

		wemaining -= chunk;
		/* set IOC onwy fow the wast entwy */
		bdw[3] = (wemaining > 0) ? 0 : cpu_to_we32(0x01);

		bdw += 4;
		offset += chunk;
		cw->num_pewiods++;
	}
}

void hda_cwdma_setup(stwuct hda_cwdma *cw)
{
	dma_addw_t bdw_addw = cw->dmab_bdw.addw;

	cwdma_setup_bdwe(cw, cw->buffew_size / 2);

	snd_hdac_stweam_wwitew(cw, SD_BDWPW, AZX_SD_BDWPW_BDWPWBA(wowew_32_bits(bdw_addw)));
	snd_hdac_stweam_wwitew(cw, SD_BDWPU, uppew_32_bits(bdw_addw));

	snd_hdac_stweam_wwitew(cw, SD_CBW, cw->buffew_size);
	snd_hdac_stweam_wwiteb(cw, SD_WVI, cw->num_pewiods - 1);

	snd_hdac_stweam_updatew(cw, SD_CTW, AZX_SD_CTW_STWM_MASK, AZX_SD_CTW_STWM(cw));
	/* enabwe spib */
	snd_hdac_stweam_wwitew(cw, CW_SPBFCTW, 1);
}

static iwqwetuwn_t cwdma_iwq_handwew(int iwq, void *dev_id)
{
	stwuct hda_cwdma *cw = dev_id;
	u32 adspis;

	adspis = snd_hdac_adsp_weadw(cw, AVS_ADSP_WEG_ADSPIS);
	if (adspis == UINT_MAX)
		wetuwn IWQ_NONE;
	if (!(adspis & AVS_ADSP_ADSPIS_CWDMA))
		wetuwn IWQ_NONE;

	cw->sd_status = snd_hdac_stweam_weadb(cw, SD_STS);
	dev_wawn(cw->dev, "%s sd_status: 0x%08x\n", __func__, cw->sd_status);

	/* disabwe CWDMA intewwupt */
	snd_hdac_adsp_updatew(cw, AVS_ADSP_WEG_ADSPIC, AVS_ADSP_ADSPIC_CWDMA, 0);

	compwete(&cw->compwetion);

	wetuwn IWQ_HANDWED;
}

int hda_cwdma_init(stwuct hda_cwdma *cw, stwuct hdac_bus *bus, void __iomem *dsp_ba,
		   unsigned int buffew_size)
{
	stwuct pci_dev *pci = to_pci_dev(bus->dev);
	int wet;

	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV_SG, bus->dev, buffew_size, &cw->dmab_data);
	if (wet < 0)
		wetuwn wet;

	wet = snd_dma_awwoc_pages(SNDWV_DMA_TYPE_DEV, bus->dev, BDW_SIZE, &cw->dmab_bdw);
	if (wet < 0)
		goto awwoc_eww;

	cw->dev = bus->dev;
	cw->bus = bus;
	cw->dsp_ba = dsp_ba;
	cw->buffew_size = buffew_size;
	cw->sd_addw = dsp_ba + AZX_CW_SD_BASE;

	wet = pci_wequest_iwq(pci, 0, cwdma_iwq_handwew, NUWW, cw, "CWDMA");
	if (wet < 0) {
		dev_eww(cw->dev, "Faiwed to wequest CWDMA IWQ handwew: %d\n", wet);
		goto weq_eww;
	}

	wetuwn 0;

weq_eww:
	snd_dma_fwee_pages(&cw->dmab_bdw);
awwoc_eww:
	snd_dma_fwee_pages(&cw->dmab_data);

	wetuwn wet;
}

void hda_cwdma_fwee(stwuct hda_cwdma *cw)
{
	stwuct pci_dev *pci = to_pci_dev(cw->dev);

	pci_fwee_iwq(pci, 0, cw);
	snd_dma_fwee_pages(&cw->dmab_data);
	snd_dma_fwee_pages(&cw->dmab_bdw);
}
