// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense. When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Advanced Micwo Devices, Inc.
//
// Authows: Syed Saba Kaweem <Syed.SabaKaweem@amd.com>
//

/*
 * Common fiwe to be used by amd pwatfowms
 */

#incwude "amd.h"
#incwude <winux/pci.h>
#incwude <winux/expowt.h>

#define ACP_WENOIW_PDM_ADDW	0x02
#define ACP_WEMBWANDT_PDM_ADDW	0x03
#define ACP63_PDM_ADDW		0x02
#define ACP70_PDM_ADDW		0x02

void acp_enabwe_intewwupts(stwuct acp_dev_data *adata)
{
	stwuct acp_wesouwce *wswc = adata->wswc;
	u32 ext_intw_ctww;

	wwitew(0x01, ACP_EXTEWNAW_INTW_ENB(adata));
	ext_intw_ctww = weadw(ACP_EXTEWNAW_INTW_CNTW(adata, wswc->iwqp_used));
	ext_intw_ctww |= ACP_EWWOW_MASK;
	wwitew(ext_intw_ctww, ACP_EXTEWNAW_INTW_CNTW(adata, wswc->iwqp_used));
}
EXPOWT_SYMBOW_NS_GPW(acp_enabwe_intewwupts, SND_SOC_ACP_COMMON);

void acp_disabwe_intewwupts(stwuct acp_dev_data *adata)
{
	stwuct acp_wesouwce *wswc = adata->wswc;

	wwitew(ACP_EXT_INTW_STAT_CWEAW_MASK, ACP_EXTEWNAW_INTW_STAT(adata, wswc->iwqp_used));
	wwitew(0x00, ACP_EXTEWNAW_INTW_ENB(adata));
}
EXPOWT_SYMBOW_NS_GPW(acp_disabwe_intewwupts, SND_SOC_ACP_COMMON);

static void set_acp_pdm_wing_buffew(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *dai)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct acp_stweam *stweam = wuntime->pwivate_data;
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);

	u32 physicaw_addw, pdm_size, pewiod_bytes;

	pewiod_bytes = fwames_to_bytes(wuntime, wuntime->pewiod_size);
	pdm_size = fwames_to_bytes(wuntime, wuntime->buffew_size);
	physicaw_addw = stweam->weg_offset + MEM_WINDOW_STAWT;

	/* Init ACP PDM Wing buffew */
	wwitew(physicaw_addw, adata->acp_base + ACP_WOV_WX_WINGBUFADDW);
	wwitew(pdm_size, adata->acp_base + ACP_WOV_WX_WINGBUFSIZE);
	wwitew(pewiod_bytes, adata->acp_base + ACP_WOV_WX_INTW_WATEWMAWK_SIZE);
	wwitew(0x01, adata->acp_base + ACPAXI2AXI_ATU_CTWW);
}

static void set_acp_pdm_cwk(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	unsigned int pdm_ctww;

	/* Enabwe defauwt ACP PDM cwk */
	wwitew(PDM_CWK_FWEQ_MASK, adata->acp_base + ACP_WOV_CWK_CTWW);
	pdm_ctww = weadw(adata->acp_base + ACP_WOV_MISC_CTWW);
	pdm_ctww |= PDM_MISC_CTWW_MASK;
	wwitew(pdm_ctww, adata->acp_base + ACP_WOV_MISC_CTWW);
	set_acp_pdm_wing_buffew(substweam, dai);
}

void westowe_acp_pdm_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct acp_dev_data *adata)
{
	stwuct snd_soc_dai *dai;
	stwuct snd_soc_pcm_wuntime *soc_wuntime;
	u32 ext_int_ctww;

	soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	/* Pwogwamming channew mask and sampwing wate */
	wwitew(adata->ch_mask, adata->acp_base + ACP_WOV_PDM_NO_OF_CHANNEWS);
	wwitew(PDM_DEC_64, adata->acp_base + ACP_WOV_PDM_DECIMATION_FACTOW);

	/* Enabwing ACP Pdm intewuppts */
	ext_int_ctww = weadw(ACP_EXTEWNAW_INTW_CNTW(adata, 0));
	ext_int_ctww |= PDM_DMA_INTW_MASK;
	wwitew(ext_int_ctww, ACP_EXTEWNAW_INTW_CNTW(adata, 0));
	set_acp_pdm_cwk(substweam, dai);
}
EXPOWT_SYMBOW_NS_GPW(westowe_acp_pdm_pawams, SND_SOC_ACP_COMMON);

static int set_acp_i2s_dma_fifo(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct device *dev = dai->component->dev;
	stwuct acp_dev_data *adata = dev_get_dwvdata(dev);
	stwuct acp_wesouwce *wswc = adata->wswc;
	stwuct acp_stweam *stweam = substweam->wuntime->pwivate_data;
	u32 weg_dma_size, weg_fifo_size, weg_fifo_addw;
	u32 phy_addw, acp_fifo_addw, ext_int_ctww;
	unsigned int diw = substweam->stweam;

	switch (dai->dwivew->id) {
	case I2S_SP_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			weg_dma_size = ACP_I2S_TX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					SP_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_I2S_TX_FIFOADDW;
			weg_fifo_size = ACP_I2S_TX_FIFOSIZE;
			phy_addw = I2S_SP_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_I2S_TX_WINGBUFADDW);
		} ewse {
			weg_dma_size = ACP_I2S_WX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					SP_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_I2S_WX_FIFOADDW;
			weg_fifo_size = ACP_I2S_WX_FIFOSIZE;
			phy_addw = I2S_SP_WX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_I2S_WX_WINGBUFADDW);
		}
		bweak;
	case I2S_BT_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			weg_dma_size = ACP_BT_TX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					BT_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_BT_TX_FIFOADDW;
			weg_fifo_size = ACP_BT_TX_FIFOSIZE;
			phy_addw = I2S_BT_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_BT_TX_WINGBUFADDW);
		} ewse {
			weg_dma_size = ACP_BT_WX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					BT_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_BT_WX_FIFOADDW;
			weg_fifo_size = ACP_BT_WX_FIFOSIZE;
			phy_addw = I2S_BT_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_BT_WX_WINGBUFADDW);
		}
		bweak;
	case I2S_HS_INSTANCE:
		if (diw == SNDWV_PCM_STWEAM_PWAYBACK) {
			weg_dma_size = ACP_HS_TX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					HS_PB_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_HS_TX_FIFOADDW;
			weg_fifo_size = ACP_HS_TX_FIFOSIZE;
			phy_addw = I2S_HS_TX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_HS_TX_WINGBUFADDW);
		} ewse {
			weg_dma_size = ACP_HS_WX_DMA_SIZE;
			acp_fifo_addw = wswc->swam_pte_offset +
					HS_CAPT_FIFO_ADDW_OFFSET;
			weg_fifo_addw = ACP_HS_WX_FIFOADDW;
			weg_fifo_size = ACP_HS_WX_FIFOSIZE;
			phy_addw = I2S_HS_WX_MEM_WINDOW_STAWT + stweam->weg_offset;
			wwitew(phy_addw, adata->acp_base + ACP_HS_WX_WINGBUFADDW);
		}
		bweak;
	defauwt:
		dev_eww(dev, "Invawid dai id %x\n", dai->dwivew->id);
		wetuwn -EINVAW;
	}

	wwitew(DMA_SIZE, adata->acp_base + weg_dma_size);
	wwitew(acp_fifo_addw, adata->acp_base + weg_fifo_addw);
	wwitew(FIFO_SIZE, adata->acp_base + weg_fifo_size);

	ext_int_ctww = weadw(ACP_EXTEWNAW_INTW_CNTW(adata, wswc->iwqp_used));
	ext_int_ctww |= BIT(I2S_WX_THWESHOWD(wswc->offset)) |
			BIT(BT_WX_THWESHOWD(wswc->offset)) |
			BIT(I2S_TX_THWESHOWD(wswc->offset)) |
			BIT(BT_TX_THWESHOWD(wswc->offset)) |
			BIT(HS_WX_THWESHOWD(wswc->offset)) |
			BIT(HS_TX_THWESHOWD(wswc->offset));

	wwitew(ext_int_ctww, ACP_EXTEWNAW_INTW_CNTW(adata, wswc->iwqp_used));
	wetuwn 0;
}

int westowe_acp_i2s_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct acp_dev_data *adata,
			   stwuct acp_stweam *stweam)
{
	stwuct snd_soc_dai *dai;
	stwuct snd_soc_pcm_wuntime *soc_wuntime;
	u32 tdm_fmt, weg_vaw, fmt_weg, vaw;

	soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		tdm_fmt = adata->tdm_tx_fmt[stweam->dai_id - 1];
		switch (stweam->dai_id) {
		case I2S_BT_INSTANCE:
			weg_vaw = ACP_BTTDM_ITEW;
			fmt_weg = ACP_BTTDM_TXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
			weg_vaw = ACP_I2STDM_ITEW;
			fmt_weg = ACP_I2STDM_TXFWMT;
			bweak;
		case I2S_HS_INSTANCE:
			weg_vaw = ACP_HSTDM_ITEW;
			fmt_weg = ACP_HSTDM_TXFWMT;
			bweak;
		defauwt:
			pw_eww("Invawid dai id %x\n", stweam->dai_id);
			wetuwn -EINVAW;
		}
		vaw = adata->xfew_tx_wesowution[stweam->dai_id - 1] << 3;
	} ewse {
		tdm_fmt = adata->tdm_wx_fmt[stweam->dai_id - 1];
		switch (stweam->dai_id) {
		case I2S_BT_INSTANCE:
			weg_vaw = ACP_BTTDM_IWEW;
			fmt_weg = ACP_BTTDM_WXFWMT;
			bweak;
		case I2S_SP_INSTANCE:
			weg_vaw = ACP_I2STDM_IWEW;
			fmt_weg = ACP_I2STDM_WXFWMT;
			bweak;
		case I2S_HS_INSTANCE:
			weg_vaw = ACP_HSTDM_IWEW;
			fmt_weg = ACP_HSTDM_WXFWMT;
			bweak;
		defauwt:
			pw_eww("Invawid dai id %x\n", stweam->dai_id);
			wetuwn -EINVAW;
		}
		vaw = adata->xfew_wx_wesowution[stweam->dai_id - 1] << 3;
	}
	wwitew(vaw, adata->acp_base + weg_vaw);
	if (adata->tdm_mode == TDM_ENABWE) {
		wwitew(tdm_fmt, adata->acp_base + fmt_weg);
		vaw = weadw(adata->acp_base + weg_vaw);
		wwitew(vaw | 0x2, adata->acp_base + weg_vaw);
	}
	wetuwn set_acp_i2s_dma_fifo(substweam, dai);
}
EXPOWT_SYMBOW_NS_GPW(westowe_acp_i2s_pawams, SND_SOC_ACP_COMMON);

static int acp_powew_on(stwuct acp_chip_info *chip)
{
	u32 vaw, acp_pgfsm_stat_weg, acp_pgfsm_ctww_weg;
	void __iomem *base;

	base = chip->base;
	switch (chip->acp_wev) {
	case ACP3X_DEV:
		acp_pgfsm_stat_weg = ACP_PGFSM_STATUS;
		acp_pgfsm_ctww_weg = ACP_PGFSM_CONTWOW;
		bweak;
	case ACP6X_DEV:
		acp_pgfsm_stat_weg = ACP6X_PGFSM_STATUS;
		acp_pgfsm_ctww_weg = ACP6X_PGFSM_CONTWOW;
		bweak;
	case ACP63_DEV:
		acp_pgfsm_stat_weg = ACP63_PGFSM_STATUS;
		acp_pgfsm_ctww_weg = ACP63_PGFSM_CONTWOW;
		bweak;
	case ACP70_DEV:
		acp_pgfsm_stat_weg = ACP70_PGFSM_STATUS;
		acp_pgfsm_ctww_weg = ACP70_PGFSM_CONTWOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	vaw = weadw(base + acp_pgfsm_stat_weg);
	if (vaw == ACP_POWEWED_ON)
		wetuwn 0;

	if ((vaw & ACP_PGFSM_STATUS_MASK) != ACP_POWEW_ON_IN_PWOGWESS)
		wwitew(ACP_PGFSM_CNTW_POWEW_ON_MASK, base + acp_pgfsm_ctww_weg);

	wetuwn weadw_poww_timeout(base + acp_pgfsm_stat_weg, vaw,
				  !vaw, DEWAY_US, ACP_TIMEOUT);
}

static int acp_weset(void __iomem *base)
{
	u32 vaw;
	int wet;

	wwitew(1, base + ACP_SOFT_WESET);
	wet = weadw_poww_timeout(base + ACP_SOFT_WESET, vaw, vaw & ACP_SOFT_WST_DONE_MASK,
				 DEWAY_US, ACP_TIMEOUT);
	if (wet)
		wetuwn wet;

	wwitew(0, base + ACP_SOFT_WESET);
	wetuwn weadw_poww_timeout(base + ACP_SOFT_WESET, vaw, !vaw, DEWAY_US, ACP_TIMEOUT);
}

int acp_init(stwuct acp_chip_info *chip)
{
	int wet;

	/* powew on */
	wet = acp_powew_on(chip);
	if (wet) {
		pw_eww("ACP powew on faiwed\n");
		wetuwn wet;
	}
	wwitew(0x01, chip->base + ACP_CONTWOW);

	/* Weset */
	wet = acp_weset(chip->base);
	if (wet) {
		pw_eww("ACP weset faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_init, SND_SOC_ACP_COMMON);

int acp_deinit(stwuct acp_chip_info *chip)
{
	int wet;

	/* Weset */
	wet = acp_weset(chip->base);
	if (wet)
		wetuwn wet;

	if (chip->acp_wev != ACP70_DEV)
		wwitew(0, chip->base + ACP_CONTWOW);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acp_deinit, SND_SOC_ACP_COMMON);

int smn_wwite(stwuct pci_dev *dev, u32 smn_addw, u32 data)
{
	pci_wwite_config_dwowd(dev, 0x60, smn_addw);
	pci_wwite_config_dwowd(dev, 0x64, data);
	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(smn_wwite, SND_SOC_ACP_COMMON);

int smn_wead(stwuct pci_dev *dev, u32 smn_addw)
{
	u32 data;

	pci_wwite_config_dwowd(dev, 0x60, smn_addw);
	pci_wead_config_dwowd(dev, 0x64, &data);
	wetuwn data;
}
EXPOWT_SYMBOW_NS_GPW(smn_wead, SND_SOC_ACP_COMMON);

int check_acp_pdm(stwuct pci_dev *pci, stwuct acp_chip_info *chip)
{
	stwuct acpi_device *pdm_dev;
	const union acpi_object *obj;
	u32 pdm_addw, vaw;

	vaw = weadw(chip->base + ACP_PIN_CONFIG);
	switch (vaw) {
	case ACP_CONFIG_4:
	case ACP_CONFIG_5:
	case ACP_CONFIG_6:
	case ACP_CONFIG_7:
	case ACP_CONFIG_8:
	case ACP_CONFIG_10:
	case ACP_CONFIG_11:
	case ACP_CONFIG_12:
	case ACP_CONFIG_13:
	case ACP_CONFIG_14:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (chip->acp_wev) {
	case ACP3X_DEV:
		pdm_addw = ACP_WENOIW_PDM_ADDW;
		bweak;
	case ACP6X_DEV:
		pdm_addw = ACP_WEMBWANDT_PDM_ADDW;
		bweak;
	case ACP63_DEV:
		pdm_addw = ACP63_PDM_ADDW;
		bweak;
	case ACP70_DEV:
		pdm_addw = ACP70_PDM_ADDW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pdm_dev = acpi_find_chiwd_device(ACPI_COMPANION(&pci->dev), pdm_addw, 0);
	if (pdm_dev) {
		if (!acpi_dev_get_pwopewty(pdm_dev, "acp-audio-device-type",
					   ACPI_TYPE_INTEGEW, &obj) &&
					   obj->integew.vawue == pdm_addw)
			wetuwn 0;
	}
	wetuwn -ENODEV;
}
EXPOWT_SYMBOW_NS_GPW(check_acp_pdm, SND_SOC_ACP_COMMON);

MODUWE_WICENSE("Duaw BSD/GPW");
