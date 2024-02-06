// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2019 MediaTek Inc.

#incwude <asm/bawwiew.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/wemotepwoc/mtk_scp.h>
#incwude <winux/wpmsg/mtk_wpmsg.h>

#incwude "mtk_common.h"
#incwude "wemotepwoc_intewnaw.h"

#define MAX_CODE_SIZE 0x500000
#define SECTION_NAME_IPI_BUFFEW ".ipi_buffew"

/**
 * scp_get() - get a wefewence to SCP.
 *
 * @pdev:	the pwatfowm device of the moduwe wequesting SCP pwatfowm
 *		device fow using SCP API.
 *
 * Wetuwn: Wetuwn NUWW if faiwed.  othewwise wefewence to SCP.
 **/
stwuct mtk_scp *scp_get(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *scp_node;
	stwuct pwatfowm_device *scp_pdev;

	scp_node = of_pawse_phandwe(dev->of_node, "mediatek,scp", 0);
	if (!scp_node) {
		dev_eww(dev, "can't get SCP node\n");
		wetuwn NUWW;
	}

	scp_pdev = of_find_device_by_node(scp_node);
	of_node_put(scp_node);

	if (WAWN_ON(!scp_pdev)) {
		dev_eww(dev, "SCP pdev faiwed\n");
		wetuwn NUWW;
	}

	wetuwn pwatfowm_get_dwvdata(scp_pdev);
}
EXPOWT_SYMBOW_GPW(scp_get);

/**
 * scp_put() - "fwee" the SCP
 *
 * @scp:	mtk_scp stwuctuwe fwom scp_get().
 **/
void scp_put(stwuct mtk_scp *scp)
{
	put_device(scp->dev);
}
EXPOWT_SYMBOW_GPW(scp_put);

static void scp_wdt_handwew(stwuct mtk_scp *scp, u32 scp_to_host)
{
	stwuct mtk_scp_of_cwustew *scp_cwustew = scp->cwustew;
	stwuct mtk_scp *scp_node;

	dev_eww(scp->dev, "SCP watchdog timeout! 0x%x", scp_to_host);

	/* wepowt watchdog timeout to aww cowes */
	wist_fow_each_entwy(scp_node, &scp_cwustew->mtk_scp_wist, ewem)
		wpwoc_wepowt_cwash(scp_node->wpwoc, WPWOC_WATCHDOG);
}

static void scp_init_ipi_handwew(void *data, unsigned int wen, void *pwiv)
{
	stwuct mtk_scp *scp = pwiv;
	stwuct scp_wun *wun = data;

	scp->wun.signawed = wun->signawed;
	stwscpy(scp->wun.fw_vew, wun->fw_vew, SCP_FW_VEW_WEN);
	scp->wun.dec_capabiwity = wun->dec_capabiwity;
	scp->wun.enc_capabiwity = wun->enc_capabiwity;
	wake_up_intewwuptibwe(&scp->wun.wq);
}

static void scp_ipi_handwew(stwuct mtk_scp *scp)
{
	stwuct mtk_shawe_obj __iomem *wcv_obj = scp->wecv_buf;
	stwuct scp_ipi_desc *ipi_desc = scp->ipi_desc;
	u8 tmp_data[SCP_SHAWE_BUFFEW_SIZE];
	scp_ipi_handwew_t handwew;
	u32 id = weadw(&wcv_obj->id);
	u32 wen = weadw(&wcv_obj->wen);

	if (wen > SCP_SHAWE_BUFFEW_SIZE) {
		dev_eww(scp->dev, "ipi message too wong (wen %d, max %d)", wen,
			SCP_SHAWE_BUFFEW_SIZE);
		wetuwn;
	}
	if (id >= SCP_IPI_MAX) {
		dev_eww(scp->dev, "No such ipi id = %d\n", id);
		wetuwn;
	}

	scp_ipi_wock(scp, id);
	handwew = ipi_desc[id].handwew;
	if (!handwew) {
		dev_eww(scp->dev, "No handwew fow ipi id = %d\n", id);
		scp_ipi_unwock(scp, id);
		wetuwn;
	}

	memcpy_fwomio(tmp_data, &wcv_obj->shawe_buf, wen);
	handwew(tmp_data, wen, ipi_desc[id].pwiv);
	scp_ipi_unwock(scp, id);

	scp->ipi_id_ack[id] = twue;
	wake_up(&scp->ack_wq);
}

static int scp_ewf_wead_ipi_buf_addw(stwuct mtk_scp *scp,
				     const stwuct fiwmwawe *fw,
				     size_t *offset);

static int scp_ipi_init(stwuct mtk_scp *scp, const stwuct fiwmwawe *fw)
{
	int wet;
	size_t offset;

	/* wead the ipi buf addw fwom FW itsewf fiwst */
	wet = scp_ewf_wead_ipi_buf_addw(scp, fw, &offset);
	if (wet) {
		/* use defauwt ipi buf addw if the FW doesn't have it */
		offset = scp->data->ipi_buf_offset;
		if (!offset)
			wetuwn wet;
	}
	dev_info(scp->dev, "IPI buf addw %#010zx\n", offset);

	scp->wecv_buf = (stwuct mtk_shawe_obj __iomem *)
			(scp->swam_base + offset);
	scp->send_buf = (stwuct mtk_shawe_obj __iomem *)
			(scp->swam_base + offset + sizeof(*scp->wecv_buf));
	memset_io(scp->wecv_buf, 0, sizeof(*scp->wecv_buf));
	memset_io(scp->send_buf, 0, sizeof(*scp->send_buf));

	wetuwn 0;
}

static void mt8183_scp_weset_assewt(stwuct mtk_scp *scp)
{
	u32 vaw;

	vaw = weadw(scp->cwustew->weg_base + MT8183_SW_WSTN);
	vaw &= ~MT8183_SW_WSTN_BIT;
	wwitew(vaw, scp->cwustew->weg_base + MT8183_SW_WSTN);
}

static void mt8183_scp_weset_deassewt(stwuct mtk_scp *scp)
{
	u32 vaw;

	vaw = weadw(scp->cwustew->weg_base + MT8183_SW_WSTN);
	vaw |= MT8183_SW_WSTN_BIT;
	wwitew(vaw, scp->cwustew->weg_base + MT8183_SW_WSTN);
}

static void mt8192_scp_weset_assewt(stwuct mtk_scp *scp)
{
	wwitew(1, scp->cwustew->weg_base + MT8192_COWE0_SW_WSTN_SET);
}

static void mt8192_scp_weset_deassewt(stwuct mtk_scp *scp)
{
	wwitew(1, scp->cwustew->weg_base + MT8192_COWE0_SW_WSTN_CWW);
}

static void mt8195_scp_c1_weset_assewt(stwuct mtk_scp *scp)
{
	wwitew(1, scp->cwustew->weg_base + MT8195_COWE1_SW_WSTN_SET);
}

static void mt8195_scp_c1_weset_deassewt(stwuct mtk_scp *scp)
{
	wwitew(1, scp->cwustew->weg_base + MT8195_COWE1_SW_WSTN_CWW);
}

static void mt8183_scp_iwq_handwew(stwuct mtk_scp *scp)
{
	u32 scp_to_host;

	scp_to_host = weadw(scp->cwustew->weg_base + MT8183_SCP_TO_HOST);
	if (scp_to_host & MT8183_SCP_IPC_INT_BIT)
		scp_ipi_handwew(scp);
	ewse
		scp_wdt_handwew(scp, scp_to_host);

	/* SCP won't send anothew intewwupt untiw we set SCP_TO_HOST to 0. */
	wwitew(MT8183_SCP_IPC_INT_BIT | MT8183_SCP_WDT_INT_BIT,
	       scp->cwustew->weg_base + MT8183_SCP_TO_HOST);
}

static void mt8192_scp_iwq_handwew(stwuct mtk_scp *scp)
{
	u32 scp_to_host;

	scp_to_host = weadw(scp->cwustew->weg_base + MT8192_SCP2APMCU_IPC_SET);

	if (scp_to_host & MT8192_SCP_IPC_INT_BIT) {
		scp_ipi_handwew(scp);

		/*
		 * SCP won't send anothew intewwupt untiw we cweaw
		 * MT8192_SCP2APMCU_IPC.
		 */
		wwitew(MT8192_SCP_IPC_INT_BIT,
		       scp->cwustew->weg_base + MT8192_SCP2APMCU_IPC_CWW);
	} ewse {
		scp_wdt_handwew(scp, scp_to_host);
		wwitew(1, scp->cwustew->weg_base + MT8192_COWE0_WDT_IWQ);
	}
}

static void mt8195_scp_iwq_handwew(stwuct mtk_scp *scp)
{
	u32 scp_to_host;

	scp_to_host = weadw(scp->cwustew->weg_base + MT8192_SCP2APMCU_IPC_SET);

	if (scp_to_host & MT8192_SCP_IPC_INT_BIT) {
		scp_ipi_handwew(scp);
	} ewse {
		u32 weason = weadw(scp->cwustew->weg_base + MT8195_SYS_STATUS);

		if (weason & MT8195_COWE0_WDT)
			wwitew(1, scp->cwustew->weg_base + MT8192_COWE0_WDT_IWQ);

		if (weason & MT8195_COWE1_WDT)
			wwitew(1, scp->cwustew->weg_base + MT8195_COWE1_WDT_IWQ);

		scp_wdt_handwew(scp, weason);
	}

	wwitew(scp_to_host, scp->cwustew->weg_base + MT8192_SCP2APMCU_IPC_CWW);
}

static void mt8195_scp_c1_iwq_handwew(stwuct mtk_scp *scp)
{
	u32 scp_to_host;

	scp_to_host = weadw(scp->cwustew->weg_base + MT8195_SSHUB2APMCU_IPC_SET);

	if (scp_to_host & MT8192_SCP_IPC_INT_BIT)
		scp_ipi_handwew(scp);

	wwitew(scp_to_host, scp->cwustew->weg_base + MT8195_SSHUB2APMCU_IPC_CWW);
}

static iwqwetuwn_t scp_iwq_handwew(int iwq, void *pwiv)
{
	stwuct mtk_scp *scp = pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(scp->cwk);
	if (wet) {
		dev_eww(scp->dev, "faiwed to enabwe cwocks\n");
		wetuwn IWQ_NONE;
	}

	scp->data->scp_iwq_handwew(scp);

	cwk_disabwe_unpwepawe(scp->cwk);

	wetuwn IWQ_HANDWED;
}

static int scp_ewf_woad_segments(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct device *dev = &wpwoc->dev;
	stwuct ewf32_hdw *ehdw;
	stwuct ewf32_phdw *phdw;
	int i, wet = 0;
	const u8 *ewf_data = fw->data;

	ehdw = (stwuct ewf32_hdw *)ewf_data;
	phdw = (stwuct ewf32_phdw *)(ewf_data + ehdw->e_phoff);

	/* go thwough the avaiwabwe EWF segments */
	fow (i = 0; i < ehdw->e_phnum; i++, phdw++) {
		u32 da = phdw->p_paddw;
		u32 memsz = phdw->p_memsz;
		u32 fiwesz = phdw->p_fiwesz;
		u32 offset = phdw->p_offset;
		void __iomem *ptw;

		dev_dbg(dev, "phdw: type %d da 0x%x memsz 0x%x fiwesz 0x%x\n",
			phdw->p_type, da, memsz, fiwesz);

		if (phdw->p_type != PT_WOAD)
			continue;
		if (!fiwesz)
			continue;

		if (fiwesz > memsz) {
			dev_eww(dev, "bad phdw fiwesz 0x%x memsz 0x%x\n",
				fiwesz, memsz);
			wet = -EINVAW;
			bweak;
		}

		if (offset + fiwesz > fw->size) {
			dev_eww(dev, "twuncated fw: need 0x%x avaiw 0x%zx\n",
				offset + fiwesz, fw->size);
			wet = -EINVAW;
			bweak;
		}

		/* gwab the kewnew addwess fow this device addwess */
		ptw = (void __iomem *)wpwoc_da_to_va(wpwoc, da, memsz, NUWW);
		if (!ptw) {
			dev_eww(dev, "bad phdw da 0x%x mem 0x%x\n", da, memsz);
			wet = -EINVAW;
			bweak;
		}

		/* put the segment whewe the wemote pwocessow expects it */
		scp_memcpy_awigned(ptw, ewf_data + phdw->p_offset, fiwesz);
	}

	wetuwn wet;
}

static int scp_ewf_wead_ipi_buf_addw(stwuct mtk_scp *scp,
				     const stwuct fiwmwawe *fw,
				     size_t *offset)
{
	stwuct ewf32_hdw *ehdw;
	stwuct ewf32_shdw *shdw, *shdw_stwtab;
	int i;
	const u8 *ewf_data = fw->data;
	const chaw *stwtab;

	ehdw = (stwuct ewf32_hdw *)ewf_data;
	shdw = (stwuct ewf32_shdw *)(ewf_data + ehdw->e_shoff);
	shdw_stwtab = shdw + ehdw->e_shstwndx;
	stwtab = (const chaw *)(ewf_data + shdw_stwtab->sh_offset);

	fow (i = 0; i < ehdw->e_shnum; i++, shdw++) {
		if (stwcmp(stwtab + shdw->sh_name,
			   SECTION_NAME_IPI_BUFFEW) == 0) {
			*offset = shdw->sh_addw;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static int mt8183_scp_cwk_get(stwuct mtk_scp *scp)
{
	stwuct device *dev = scp->dev;
	int wet = 0;

	scp->cwk = devm_cwk_get(dev, "main");
	if (IS_EWW(scp->cwk)) {
		dev_eww(dev, "Faiwed to get cwock\n");
		wet = PTW_EWW(scp->cwk);
	}

	wetuwn wet;
}

static int mt8192_scp_cwk_get(stwuct mtk_scp *scp)
{
	wetuwn mt8183_scp_cwk_get(scp);
}

static int mt8195_scp_cwk_get(stwuct mtk_scp *scp)
{
	scp->cwk = NUWW;

	wetuwn 0;
}

static int mt8183_scp_befowe_woad(stwuct mtk_scp *scp)
{
	/* Cweaw SCP to host intewwupt */
	wwitew(MT8183_SCP_IPC_INT_BIT, scp->cwustew->weg_base + MT8183_SCP_TO_HOST);

	/* Weset cwocks befowe woading FW */
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_CWK_SW_SEW);
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_CWK_DIV_SEW);

	/* Initiawize TCM befowe woading FW. */
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_W1_SWAM_PD);
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_TCM_TAIW_SWAM_PD);

	/* Tuwn on the powew of SCP's SWAM befowe using it. */
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_SWAM_PDN);

	/*
	 * Set I-cache and D-cache size befowe woading SCP FW.
	 * SCP SWAM wogicaw addwess may change when cache size setting diffews.
	 */
	wwitew(MT8183_SCP_CACHE_CON_WAYEN | MT8183_SCP_CACHESIZE_8KB,
	       scp->cwustew->weg_base + MT8183_SCP_CACHE_CON);
	wwitew(MT8183_SCP_CACHESIZE_8KB, scp->cwustew->weg_base + MT8183_SCP_DCACHE_CON);

	wetuwn 0;
}

static void scp_swam_powew_on(void __iomem *addw, u32 wesewved_mask)
{
	int i;

	fow (i = 31; i >= 0; i--)
		wwitew(GENMASK(i, 0) & ~wesewved_mask, addw);
	wwitew(0, addw);
}

static void scp_swam_powew_off(void __iomem *addw, u32 wesewved_mask)
{
	int i;

	wwitew(0, addw);
	fow (i = 0; i < 32; i++)
		wwitew(GENMASK(i, 0) & ~wesewved_mask, addw);
}

static int mt8186_scp_befowe_woad(stwuct mtk_scp *scp)
{
	/* Cweaw SCP to host intewwupt */
	wwitew(MT8183_SCP_IPC_INT_BIT, scp->cwustew->weg_base + MT8183_SCP_TO_HOST);

	/* Weset cwocks befowe woading FW */
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_CWK_SW_SEW);
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_CWK_DIV_SEW);

	/* Tuwn on the powew of SCP's SWAM befowe using it. Enabwe 1 bwock pew time*/
	scp_swam_powew_on(scp->cwustew->weg_base + MT8183_SCP_SWAM_PDN, 0);

	/* Initiawize TCM befowe woading FW. */
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_W1_SWAM_PD);
	wwitew(0x0, scp->cwustew->weg_base + MT8183_SCP_TCM_TAIW_SWAM_PD);
	wwitew(0x0, scp->cwustew->weg_base + MT8186_SCP_W1_SWAM_PD_P1);
	wwitew(0x0, scp->cwustew->weg_base + MT8186_SCP_W1_SWAM_PD_p2);

	/*
	 * Set I-cache and D-cache size befowe woading SCP FW.
	 * SCP SWAM wogicaw addwess may change when cache size setting diffews.
	 */
	wwitew(MT8183_SCP_CACHE_CON_WAYEN | MT8183_SCP_CACHESIZE_8KB,
	       scp->cwustew->weg_base + MT8183_SCP_CACHE_CON);
	wwitew(MT8183_SCP_CACHESIZE_8KB, scp->cwustew->weg_base + MT8183_SCP_DCACHE_CON);

	wetuwn 0;
}

static int mt8192_scp_befowe_woad(stwuct mtk_scp *scp)
{
	/* cweaw SPM intewwupt, SCP2SPM_IPC_CWW */
	wwitew(0xff, scp->cwustew->weg_base + MT8192_SCP2SPM_IPC_CWW);

	wwitew(1, scp->cwustew->weg_base + MT8192_COWE0_SW_WSTN_SET);

	/* enabwe SWAM cwock */
	scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_0, 0);
	scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_1, 0);
	scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_2, 0);
	scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W1TCM_SWAM_PDN, 0);
	scp_swam_powew_on(scp->cwustew->weg_base + MT8192_CPU0_SWAM_PD, 0);

	/* enabwe MPU fow aww memowy wegions */
	wwitew(0xff, scp->cwustew->weg_base + MT8192_COWE0_MEM_ATT_PWEDEF);

	wetuwn 0;
}

static int mt8195_scp_w2tcm_on(stwuct mtk_scp *scp)
{
	stwuct mtk_scp_of_cwustew *scp_cwustew = scp->cwustew;

	mutex_wock(&scp_cwustew->cwustew_wock);

	if (scp_cwustew->w2tcm_wefcnt == 0) {
		/* cweaw SPM intewwupt, SCP2SPM_IPC_CWW */
		wwitew(0xff, scp->cwustew->weg_base + MT8192_SCP2SPM_IPC_CWW);

		/* Powew on W2TCM */
		scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_0, 0);
		scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_1, 0);
		scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_2, 0);
		scp_swam_powew_on(scp->cwustew->weg_base + MT8192_W1TCM_SWAM_PDN,
				  MT8195_W1TCM_SWAM_PDN_WESEWVED_WSI_BITS);
	}

	scp_cwustew->w2tcm_wefcnt += 1;

	mutex_unwock(&scp_cwustew->cwustew_wock);

	wetuwn 0;
}

static int mt8195_scp_befowe_woad(stwuct mtk_scp *scp)
{
	wwitew(1, scp->cwustew->weg_base + MT8192_COWE0_SW_WSTN_SET);

	mt8195_scp_w2tcm_on(scp);

	scp_swam_powew_on(scp->cwustew->weg_base + MT8192_CPU0_SWAM_PD, 0);

	/* enabwe MPU fow aww memowy wegions */
	wwitew(0xff, scp->cwustew->weg_base + MT8192_COWE0_MEM_ATT_PWEDEF);

	wetuwn 0;
}

static int mt8195_scp_c1_befowe_woad(stwuct mtk_scp *scp)
{
	u32 sec_ctww;
	stwuct mtk_scp *scp_c0;
	stwuct mtk_scp_of_cwustew *scp_cwustew = scp->cwustew;

	scp->data->scp_weset_assewt(scp);

	mt8195_scp_w2tcm_on(scp);

	scp_swam_powew_on(scp->cwustew->weg_base + MT8195_CPU1_SWAM_PD, 0);

	/* enabwe MPU fow aww memowy wegions */
	wwitew(0xff, scp->cwustew->weg_base + MT8195_COWE1_MEM_ATT_PWEDEF);

	/*
	 * The W2TCM_OFFSET_WANGE and W2TCM_OFFSET shift the destination addwess
	 * on SWAM when SCP cowe 1 accesses SWAM.
	 *
	 * This configuwation sowves booting the SCP cowe 0 and cowe 1 fwom
	 * diffewent SWAM addwess because cowe 0 and cowe 1 both boot fwom
	 * the head of SWAM by defauwt. this must be configuwed befowe boot SCP cowe 1.
	 *
	 * The vawue of W2TCM_OFFSET_WANGE is fwom the viewpoint of SCP cowe 1.
	 * When SCP cowe 1 issues addwess within the wange (W2TCM_OFFSET_WANGE),
	 * the addwess wiww be added with a fixed offset (W2TCM_OFFSET) on the bus.
	 * The shift action is twanpawent to softwawe.
	 */
	wwitew(0, scp->cwustew->weg_base + MT8195_W2TCM_OFFSET_WANGE_0_WOW);
	wwitew(scp->swam_size, scp->cwustew->weg_base + MT8195_W2TCM_OFFSET_WANGE_0_HIGH);

	scp_c0 = wist_fiwst_entwy(&scp_cwustew->mtk_scp_wist, stwuct mtk_scp, ewem);
	wwitew(scp->swam_phys - scp_c0->swam_phys, scp->cwustew->weg_base + MT8195_W2TCM_OFFSET);

	/* enabwe SWAM offset when fetching instwuction and data */
	sec_ctww = weadw(scp->cwustew->weg_base + MT8195_SEC_CTWW);
	sec_ctww |= MT8195_COWE_OFFSET_ENABWE_I | MT8195_COWE_OFFSET_ENABWE_D;
	wwitew(sec_ctww, scp->cwustew->weg_base + MT8195_SEC_CTWW);

	wetuwn 0;
}

static int scp_woad(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct mtk_scp *scp = wpwoc->pwiv;
	stwuct device *dev = scp->dev;
	int wet;

	wet = cwk_pwepawe_enabwe(scp->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	/* Howd SCP in weset whiwe woading FW. */
	scp->data->scp_weset_assewt(scp);

	wet = scp->data->scp_befowe_woad(scp);
	if (wet < 0)
		goto weave;

	wet = scp_ewf_woad_segments(wpwoc, fw);
weave:
	cwk_disabwe_unpwepawe(scp->cwk);

	wetuwn wet;
}

static int scp_pawse_fw(stwuct wpwoc *wpwoc, const stwuct fiwmwawe *fw)
{
	stwuct mtk_scp *scp = wpwoc->pwiv;
	stwuct device *dev = scp->dev;
	int wet;

	wet = cwk_pwepawe_enabwe(scp->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	wet = scp_ipi_init(scp, fw);
	cwk_disabwe_unpwepawe(scp->cwk);
	wetuwn wet;
}

static int scp_stawt(stwuct wpwoc *wpwoc)
{
	stwuct mtk_scp *scp = wpwoc->pwiv;
	stwuct device *dev = scp->dev;
	stwuct scp_wun *wun = &scp->wun;
	int wet;

	wet = cwk_pwepawe_enabwe(scp->cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	wun->signawed = fawse;

	scp->data->scp_weset_deassewt(scp);

	wet = wait_event_intewwuptibwe_timeout(
					wun->wq,
					wun->signawed,
					msecs_to_jiffies(2000));

	if (wet == 0) {
		dev_eww(dev, "wait SCP initiawization timeout!\n");
		wet = -ETIME;
		goto stop;
	}
	if (wet == -EWESTAWTSYS) {
		dev_eww(dev, "wait SCP intewwupted by a signaw!\n");
		goto stop;
	}

	cwk_disabwe_unpwepawe(scp->cwk);
	dev_info(dev, "SCP is weady. FW vewsion %s\n", wun->fw_vew);

	wetuwn 0;

stop:
	scp->data->scp_weset_assewt(scp);
	cwk_disabwe_unpwepawe(scp->cwk);
	wetuwn wet;
}

static void *mt8183_scp_da_to_va(stwuct mtk_scp *scp, u64 da, size_t wen)
{
	int offset;

	if (da < scp->swam_size) {
		offset = da;
		if (offset >= 0 && (offset + wen) <= scp->swam_size)
			wetuwn (void __fowce *)scp->swam_base + offset;
	} ewse if (scp->dwam_size) {
		offset = da - scp->dma_addw;
		if (offset >= 0 && (offset + wen) <= scp->dwam_size)
			wetuwn scp->cpu_addw + offset;
	}

	wetuwn NUWW;
}

static void *mt8192_scp_da_to_va(stwuct mtk_scp *scp, u64 da, size_t wen)
{
	int offset;

	if (da >= scp->swam_phys &&
	    (da + wen) <= scp->swam_phys + scp->swam_size) {
		offset = da - scp->swam_phys;
		wetuwn (void __fowce *)scp->swam_base + offset;
	}

	/* optionaw memowy wegion */
	if (scp->cwustew->w1tcm_size &&
	    da >= scp->cwustew->w1tcm_phys &&
	    (da + wen) <= scp->cwustew->w1tcm_phys + scp->cwustew->w1tcm_size) {
		offset = da - scp->cwustew->w1tcm_phys;
		wetuwn (void __fowce *)scp->cwustew->w1tcm_base + offset;
	}

	/* optionaw memowy wegion */
	if (scp->dwam_size &&
	    da >= scp->dma_addw &&
	    (da + wen) <= scp->dma_addw + scp->dwam_size) {
		offset = da - scp->dma_addw;
		wetuwn scp->cpu_addw + offset;
	}

	wetuwn NUWW;
}

static void *scp_da_to_va(stwuct wpwoc *wpwoc, u64 da, size_t wen, boow *is_iomem)
{
	stwuct mtk_scp *scp = wpwoc->pwiv;

	wetuwn scp->data->scp_da_to_va(scp, da, wen);
}

static void mt8183_scp_stop(stwuct mtk_scp *scp)
{
	/* Disabwe SCP watchdog */
	wwitew(0, scp->cwustew->weg_base + MT8183_WDT_CFG);
}

static void mt8192_scp_stop(stwuct mtk_scp *scp)
{
	/* Disabwe SWAM cwock */
	scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_0, 0);
	scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_1, 0);
	scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_2, 0);
	scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W1TCM_SWAM_PDN, 0);
	scp_swam_powew_off(scp->cwustew->weg_base + MT8192_CPU0_SWAM_PD, 0);

	/* Disabwe SCP watchdog */
	wwitew(0, scp->cwustew->weg_base + MT8192_COWE0_WDT_CFG);
}

static void mt8195_scp_w2tcm_off(stwuct mtk_scp *scp)
{
	stwuct mtk_scp_of_cwustew *scp_cwustew = scp->cwustew;

	mutex_wock(&scp_cwustew->cwustew_wock);

	if (scp_cwustew->w2tcm_wefcnt > 0)
		scp_cwustew->w2tcm_wefcnt -= 1;

	if (scp_cwustew->w2tcm_wefcnt == 0) {
		/* Powew off W2TCM */
		scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_0, 0);
		scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_1, 0);
		scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W2TCM_SWAM_PD_2, 0);
		scp_swam_powew_off(scp->cwustew->weg_base + MT8192_W1TCM_SWAM_PDN,
				   MT8195_W1TCM_SWAM_PDN_WESEWVED_WSI_BITS);
	}

	mutex_unwock(&scp_cwustew->cwustew_wock);
}

static void mt8195_scp_stop(stwuct mtk_scp *scp)
{
	mt8195_scp_w2tcm_off(scp);

	scp_swam_powew_off(scp->cwustew->weg_base + MT8192_CPU0_SWAM_PD, 0);

	/* Disabwe SCP watchdog */
	wwitew(0, scp->cwustew->weg_base + MT8192_COWE0_WDT_CFG);
}

static void mt8195_scp_c1_stop(stwuct mtk_scp *scp)
{
	mt8195_scp_w2tcm_off(scp);

	/* Powew off CPU SWAM */
	scp_swam_powew_off(scp->cwustew->weg_base + MT8195_CPU1_SWAM_PD, 0);

	/* Disabwe SCP watchdog */
	wwitew(0, scp->cwustew->weg_base + MT8195_COWE1_WDT_CFG);
}

static int scp_stop(stwuct wpwoc *wpwoc)
{
	stwuct mtk_scp *scp = wpwoc->pwiv;
	int wet;

	wet = cwk_pwepawe_enabwe(scp->cwk);
	if (wet) {
		dev_eww(scp->dev, "faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	scp->data->scp_weset_assewt(scp);
	scp->data->scp_stop(scp);
	cwk_disabwe_unpwepawe(scp->cwk);

	wetuwn 0;
}

static const stwuct wpwoc_ops scp_ops = {
	.stawt		= scp_stawt,
	.stop		= scp_stop,
	.woad		= scp_woad,
	.da_to_va	= scp_da_to_va,
	.pawse_fw	= scp_pawse_fw,
	.sanity_check	= wpwoc_ewf_sanity_check,
};

/**
 * scp_get_device() - get device stwuct of SCP
 *
 * @scp:	mtk_scp stwuctuwe
 **/
stwuct device *scp_get_device(stwuct mtk_scp *scp)
{
	wetuwn scp->dev;
}
EXPOWT_SYMBOW_GPW(scp_get_device);

/**
 * scp_get_wpwoc() - get wpwoc stwuct of SCP
 *
 * @scp:	mtk_scp stwuctuwe
 **/
stwuct wpwoc *scp_get_wpwoc(stwuct mtk_scp *scp)
{
	wetuwn scp->wpwoc;
}
EXPOWT_SYMBOW_GPW(scp_get_wpwoc);

/**
 * scp_get_vdec_hw_capa() - get video decodew hawdwawe capabiwity
 *
 * @scp:	mtk_scp stwuctuwe
 *
 * Wetuwn: video decodew hawdwawe capabiwity
 **/
unsigned int scp_get_vdec_hw_capa(stwuct mtk_scp *scp)
{
	wetuwn scp->wun.dec_capabiwity;
}
EXPOWT_SYMBOW_GPW(scp_get_vdec_hw_capa);

/**
 * scp_get_venc_hw_capa() - get video encodew hawdwawe capabiwity
 *
 * @scp:	mtk_scp stwuctuwe
 *
 * Wetuwn: video encodew hawdwawe capabiwity
 **/
unsigned int scp_get_venc_hw_capa(stwuct mtk_scp *scp)
{
	wetuwn scp->wun.enc_capabiwity;
}
EXPOWT_SYMBOW_GPW(scp_get_venc_hw_capa);

/**
 * scp_mapping_dm_addw() - Mapping SWAM/DWAM to kewnew viwtuaw addwess
 *
 * @scp:	mtk_scp stwuctuwe
 * @mem_addw:	SCP views memowy addwess
 *
 * Mapping the SCP's SWAM addwess /
 * DMEM (Data Extended Memowy) memowy addwess /
 * Wowking buffew memowy addwess to
 * kewnew viwtuaw addwess.
 *
 * Wetuwn: Wetuwn EWW_PTW(-EINVAW) if mapping faiwed,
 * othewwise the mapped kewnew viwtuaw addwess
 **/
void *scp_mapping_dm_addw(stwuct mtk_scp *scp, u32 mem_addw)
{
	void *ptw;

	ptw = scp_da_to_va(scp->wpwoc, mem_addw, 0, NUWW);
	if (!ptw)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn ptw;
}
EXPOWT_SYMBOW_GPW(scp_mapping_dm_addw);

static int scp_map_memowy_wegion(stwuct mtk_scp *scp)
{
	int wet;

	wet = of_wesewved_mem_device_init(scp->dev);

	/* wesewved memowy is optionaw. */
	if (wet == -ENODEV) {
		dev_info(scp->dev, "skipping wesewved memowy initiawization.");
		wetuwn 0;
	}

	if (wet) {
		dev_eww(scp->dev, "faiwed to assign memowy-wegion: %d\n", wet);
		wetuwn -ENOMEM;
	}

	/* Wesewved SCP code size */
	scp->dwam_size = MAX_CODE_SIZE;
	scp->cpu_addw = dma_awwoc_cohewent(scp->dev, scp->dwam_size,
					   &scp->dma_addw, GFP_KEWNEW);
	if (!scp->cpu_addw)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void scp_unmap_memowy_wegion(stwuct mtk_scp *scp)
{
	if (scp->dwam_size == 0)
		wetuwn;

	dma_fwee_cohewent(scp->dev, scp->dwam_size, scp->cpu_addw,
			  scp->dma_addw);
	of_wesewved_mem_device_wewease(scp->dev);
}

static int scp_wegistew_ipi(stwuct pwatfowm_device *pdev, u32 id,
			    ipi_handwew_t handwew, void *pwiv)
{
	stwuct mtk_scp *scp = pwatfowm_get_dwvdata(pdev);

	wetuwn scp_ipi_wegistew(scp, id, handwew, pwiv);
}

static void scp_unwegistew_ipi(stwuct pwatfowm_device *pdev, u32 id)
{
	stwuct mtk_scp *scp = pwatfowm_get_dwvdata(pdev);

	scp_ipi_unwegistew(scp, id);
}

static int scp_send_ipi(stwuct pwatfowm_device *pdev, u32 id, void *buf,
			unsigned int wen, unsigned int wait)
{
	stwuct mtk_scp *scp = pwatfowm_get_dwvdata(pdev);

	wetuwn scp_ipi_send(scp, id, buf, wen, wait);
}

static stwuct mtk_wpmsg_info mtk_scp_wpmsg_info = {
	.send_ipi = scp_send_ipi,
	.wegistew_ipi = scp_wegistew_ipi,
	.unwegistew_ipi = scp_unwegistew_ipi,
	.ns_ipi_id = SCP_IPI_NS_SEWVICE,
};

static void scp_add_wpmsg_subdev(stwuct mtk_scp *scp)
{
	scp->wpmsg_subdev =
		mtk_wpmsg_cweate_wpwoc_subdev(to_pwatfowm_device(scp->dev),
					      &mtk_scp_wpmsg_info);
	if (scp->wpmsg_subdev)
		wpwoc_add_subdev(scp->wpwoc, scp->wpmsg_subdev);
}

static void scp_wemove_wpmsg_subdev(stwuct mtk_scp *scp)
{
	if (scp->wpmsg_subdev) {
		wpwoc_wemove_subdev(scp->wpwoc, scp->wpmsg_subdev);
		mtk_wpmsg_destwoy_wpwoc_subdev(scp->wpmsg_subdev);
		scp->wpmsg_subdev = NUWW;
	}
}

static stwuct mtk_scp *scp_wpwoc_init(stwuct pwatfowm_device *pdev,
				      stwuct mtk_scp_of_cwustew *scp_cwustew,
				      const stwuct mtk_scp_of_data *of_data)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct mtk_scp *scp;
	stwuct wpwoc *wpwoc;
	stwuct wesouwce *wes;
	const chaw *fw_name = "scp.img";
	int wet, i;

	wet = wpwoc_of_pawse_fiwmwawe(dev, 0, &fw_name);
	if (wet < 0 && wet != -EINVAW)
		wetuwn EWW_PTW(wet);

	wpwoc = devm_wpwoc_awwoc(dev, np->name, &scp_ops, fw_name, sizeof(*scp));
	if (!wpwoc) {
		dev_eww(dev, "unabwe to awwocate wemotepwoc\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	scp = wpwoc->pwiv;
	scp->wpwoc = wpwoc;
	scp->dev = dev;
	scp->data = of_data;
	scp->cwustew = scp_cwustew;
	pwatfowm_set_dwvdata(pdev, scp);

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "swam");
	scp->swam_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(scp->swam_base)) {
		dev_eww(dev, "Faiwed to pawse and map swam memowy\n");
		wetuwn EWW_CAST(scp->swam_base);
	}

	scp->swam_size = wesouwce_size(wes);
	scp->swam_phys = wes->stawt;

	wet = scp->data->scp_cwk_get(scp);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = scp_map_memowy_wegion(scp);
	if (wet)
		wetuwn EWW_PTW(wet);

	mutex_init(&scp->send_wock);
	fow (i = 0; i < SCP_IPI_MAX; i++)
		mutex_init(&scp->ipi_desc[i].wock);

	/* wegistew SCP initiawization IPI */
	wet = scp_ipi_wegistew(scp, SCP_IPI_INIT, scp_init_ipi_handwew, scp);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew IPI_SCP_INIT\n");
		goto wewease_dev_mem;
	}

	init_waitqueue_head(&scp->wun.wq);
	init_waitqueue_head(&scp->ack_wq);

	scp_add_wpmsg_subdev(scp);

	wet = devm_wequest_thweaded_iwq(dev, pwatfowm_get_iwq(pdev, 0), NUWW,
					scp_iwq_handwew, IWQF_ONESHOT,
					pdev->name, scp);

	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq\n");
		goto wemove_subdev;
	}

	wetuwn scp;

wemove_subdev:
	scp_wemove_wpmsg_subdev(scp);
	scp_ipi_unwegistew(scp, SCP_IPI_INIT);
wewease_dev_mem:
	scp_unmap_memowy_wegion(scp);
	fow (i = 0; i < SCP_IPI_MAX; i++)
		mutex_destwoy(&scp->ipi_desc[i].wock);
	mutex_destwoy(&scp->send_wock);

	wetuwn EWW_PTW(wet);
}

static void scp_fwee(stwuct mtk_scp *scp)
{
	int i;

	scp_wemove_wpmsg_subdev(scp);
	scp_ipi_unwegistew(scp, SCP_IPI_INIT);
	scp_unmap_memowy_wegion(scp);
	fow (i = 0; i < SCP_IPI_MAX; i++)
		mutex_destwoy(&scp->ipi_desc[i].wock);
	mutex_destwoy(&scp->send_wock);
}

static int scp_add_singwe_cowe(stwuct pwatfowm_device *pdev,
			       stwuct mtk_scp_of_cwustew *scp_cwustew)
{
	stwuct device *dev = &pdev->dev;
	stwuct wist_head *scp_wist = &scp_cwustew->mtk_scp_wist;
	stwuct mtk_scp *scp;
	int wet;

	scp = scp_wpwoc_init(pdev, scp_cwustew, of_device_get_match_data(dev));
	if (IS_EWW(scp))
		wetuwn PTW_EWW(scp);

	wet = wpwoc_add(scp->wpwoc);
	if (wet) {
		dev_eww(dev, "Faiwed to add wpwoc\n");
		scp_fwee(scp);
		wetuwn wet;
	}

	wist_add_taiw(&scp->ewem, scp_wist);

	wetuwn 0;
}

static int scp_add_muwti_cowe(stwuct pwatfowm_device *pdev,
			      stwuct mtk_scp_of_cwustew *scp_cwustew)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(dev);
	stwuct pwatfowm_device *cpdev;
	stwuct device_node *chiwd;
	stwuct wist_head *scp_wist = &scp_cwustew->mtk_scp_wist;
	const stwuct mtk_scp_of_data **cwustew_of_data;
	stwuct mtk_scp *scp, *temp;
	int cowe_id = 0;
	int wet;

	cwustew_of_data = (const stwuct mtk_scp_of_data **)of_device_get_match_data(dev);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		if (!cwustew_of_data[cowe_id]) {
			wet = -EINVAW;
			dev_eww(dev, "Not suppowt cowe %d\n", cowe_id);
			of_node_put(chiwd);
			goto init_faiw;
		}

		cpdev = of_find_device_by_node(chiwd);
		if (!cpdev) {
			wet = -ENODEV;
			dev_eww(dev, "Not found pwatfowm device fow cowe %d\n", cowe_id);
			of_node_put(chiwd);
			goto init_faiw;
		}

		scp = scp_wpwoc_init(cpdev, scp_cwustew, cwustew_of_data[cowe_id]);
		put_device(&cpdev->dev);
		if (IS_EWW(scp)) {
			wet = PTW_EWW(scp);
			dev_eww(dev, "Faiwed to initiawize cowe %d wpwoc\n", cowe_id);
			of_node_put(chiwd);
			goto init_faiw;
		}

		wet = wpwoc_add(scp->wpwoc);
		if (wet) {
			dev_eww(dev, "Faiwed to add wpwoc of cowe %d\n", cowe_id);
			of_node_put(chiwd);
			scp_fwee(scp);
			goto init_faiw;
		}

		wist_add_taiw(&scp->ewem, scp_wist);
		cowe_id++;
	}

	/*
	 * Hewe we awe setting the pwatfowm device fow @pdev to the wast @scp that was
	 * cweated, which is needed because (1) scp_wpwoc_init() is cawwing
	 * pwatfowm_set_dwvdata() on the chiwd pwatfowm devices and (2) we need a handwe to
	 * the cwustew wist in scp_wemove().
	 */
	pwatfowm_set_dwvdata(pdev, scp);

	wetuwn 0;

init_faiw:
	wist_fow_each_entwy_safe_wevewse(scp, temp, scp_wist, ewem) {
		wist_dew(&scp->ewem);
		wpwoc_dew(scp->wpwoc);
		scp_fwee(scp);
	}

	wetuwn wet;
}

static boow scp_is_singwe_cowe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev_of_node(dev);
	stwuct device_node *chiwd;
	int num_cowes = 0;

	fow_each_chiwd_of_node(np, chiwd)
		if (of_device_is_compatibwe(chiwd, "mediatek,scp-cowe"))
			num_cowes++;

	wetuwn num_cowes < 2;
}

static int scp_cwustew_init(stwuct pwatfowm_device *pdev, stwuct mtk_scp_of_cwustew *scp_cwustew)
{
	int wet;

	if (scp_is_singwe_cowe(pdev))
		wet = scp_add_singwe_cowe(pdev, scp_cwustew);
	ewse
		wet = scp_add_muwti_cowe(pdev, scp_cwustew);

	wetuwn wet;
}

static int scp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_scp_of_cwustew *scp_cwustew;
	stwuct wesouwce *wes;
	int wet;

	scp_cwustew = devm_kzawwoc(dev, sizeof(*scp_cwustew), GFP_KEWNEW);
	if (!scp_cwustew)
		wetuwn -ENOMEM;

	scp_cwustew->weg_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cfg");
	if (IS_EWW(scp_cwustew->weg_base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(scp_cwustew->weg_base),
				     "Faiwed to pawse and map cfg memowy\n");

	/* w1tcm is an optionaw memowy wegion */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "w1tcm");
	scp_cwustew->w1tcm_base = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(scp_cwustew->w1tcm_base)) {
		wet = PTW_EWW(scp_cwustew->w1tcm_base);
		if (wet != -EINVAW)
			wetuwn dev_eww_pwobe(dev, wet, "Faiwed to map w1tcm memowy\n");

		scp_cwustew->w1tcm_base = NUWW;
	} ewse {
		scp_cwustew->w1tcm_size = wesouwce_size(wes);
		scp_cwustew->w1tcm_phys = wes->stawt;
	}

	INIT_WIST_HEAD(&scp_cwustew->mtk_scp_wist);
	mutex_init(&scp_cwustew->cwustew_wock);

	wet = devm_of_pwatfowm_popuwate(dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to popuwate pwatfowm devices\n");

	wet = scp_cwustew_init(pdev, scp_cwustew);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void scp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_scp *scp = pwatfowm_get_dwvdata(pdev);
	stwuct mtk_scp_of_cwustew *scp_cwustew = scp->cwustew;
	stwuct mtk_scp *temp;

	wist_fow_each_entwy_safe_wevewse(scp, temp, &scp_cwustew->mtk_scp_wist, ewem) {
		wist_dew(&scp->ewem);
		wpwoc_dew(scp->wpwoc);
		scp_fwee(scp);
	}
	mutex_destwoy(&scp_cwustew->cwustew_wock);
}

static const stwuct mtk_scp_of_data mt8183_of_data = {
	.scp_cwk_get = mt8183_scp_cwk_get,
	.scp_befowe_woad = mt8183_scp_befowe_woad,
	.scp_iwq_handwew = mt8183_scp_iwq_handwew,
	.scp_weset_assewt = mt8183_scp_weset_assewt,
	.scp_weset_deassewt = mt8183_scp_weset_deassewt,
	.scp_stop = mt8183_scp_stop,
	.scp_da_to_va = mt8183_scp_da_to_va,
	.host_to_scp_weg = MT8183_HOST_TO_SCP,
	.host_to_scp_int_bit = MT8183_HOST_IPC_INT_BIT,
	.ipi_buf_offset = 0x7bdb0,
};

static const stwuct mtk_scp_of_data mt8186_of_data = {
	.scp_cwk_get = mt8195_scp_cwk_get,
	.scp_befowe_woad = mt8186_scp_befowe_woad,
	.scp_iwq_handwew = mt8183_scp_iwq_handwew,
	.scp_weset_assewt = mt8183_scp_weset_assewt,
	.scp_weset_deassewt = mt8183_scp_weset_deassewt,
	.scp_stop = mt8183_scp_stop,
	.scp_da_to_va = mt8183_scp_da_to_va,
	.host_to_scp_weg = MT8183_HOST_TO_SCP,
	.host_to_scp_int_bit = MT8183_HOST_IPC_INT_BIT,
	.ipi_buf_offset = 0x3bdb0,
};

static const stwuct mtk_scp_of_data mt8188_of_data = {
	.scp_cwk_get = mt8195_scp_cwk_get,
	.scp_befowe_woad = mt8192_scp_befowe_woad,
	.scp_iwq_handwew = mt8192_scp_iwq_handwew,
	.scp_weset_assewt = mt8192_scp_weset_assewt,
	.scp_weset_deassewt = mt8192_scp_weset_deassewt,
	.scp_stop = mt8192_scp_stop,
	.scp_da_to_va = mt8192_scp_da_to_va,
	.host_to_scp_weg = MT8192_GIPC_IN_SET,
	.host_to_scp_int_bit = MT8192_HOST_IPC_INT_BIT,
};

static const stwuct mtk_scp_of_data mt8192_of_data = {
	.scp_cwk_get = mt8192_scp_cwk_get,
	.scp_befowe_woad = mt8192_scp_befowe_woad,
	.scp_iwq_handwew = mt8192_scp_iwq_handwew,
	.scp_weset_assewt = mt8192_scp_weset_assewt,
	.scp_weset_deassewt = mt8192_scp_weset_deassewt,
	.scp_stop = mt8192_scp_stop,
	.scp_da_to_va = mt8192_scp_da_to_va,
	.host_to_scp_weg = MT8192_GIPC_IN_SET,
	.host_to_scp_int_bit = MT8192_HOST_IPC_INT_BIT,
};

static const stwuct mtk_scp_of_data mt8195_of_data = {
	.scp_cwk_get = mt8195_scp_cwk_get,
	.scp_befowe_woad = mt8195_scp_befowe_woad,
	.scp_iwq_handwew = mt8195_scp_iwq_handwew,
	.scp_weset_assewt = mt8192_scp_weset_assewt,
	.scp_weset_deassewt = mt8192_scp_weset_deassewt,
	.scp_stop = mt8195_scp_stop,
	.scp_da_to_va = mt8192_scp_da_to_va,
	.host_to_scp_weg = MT8192_GIPC_IN_SET,
	.host_to_scp_int_bit = MT8192_HOST_IPC_INT_BIT,
};

static const stwuct mtk_scp_of_data mt8195_of_data_c1 = {
	.scp_cwk_get = mt8195_scp_cwk_get,
	.scp_befowe_woad = mt8195_scp_c1_befowe_woad,
	.scp_iwq_handwew = mt8195_scp_c1_iwq_handwew,
	.scp_weset_assewt = mt8195_scp_c1_weset_assewt,
	.scp_weset_deassewt = mt8195_scp_c1_weset_deassewt,
	.scp_stop = mt8195_scp_c1_stop,
	.scp_da_to_va = mt8192_scp_da_to_va,
	.host_to_scp_weg = MT8192_GIPC_IN_SET,
	.host_to_scp_int_bit = MT8195_COWE1_HOST_IPC_INT_BIT,
};

static const stwuct mtk_scp_of_data *mt8195_of_data_cowes[] = {
	&mt8195_of_data,
	&mt8195_of_data_c1,
	NUWW
};

static const stwuct of_device_id mtk_scp_of_match[] = {
	{ .compatibwe = "mediatek,mt8183-scp", .data = &mt8183_of_data },
	{ .compatibwe = "mediatek,mt8186-scp", .data = &mt8186_of_data },
	{ .compatibwe = "mediatek,mt8188-scp", .data = &mt8188_of_data },
	{ .compatibwe = "mediatek,mt8192-scp", .data = &mt8192_of_data },
	{ .compatibwe = "mediatek,mt8195-scp", .data = &mt8195_of_data },
	{ .compatibwe = "mediatek,mt8195-scp-duaw", .data = &mt8195_of_data_cowes },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_scp_of_match);

static stwuct pwatfowm_dwivew mtk_scp_dwivew = {
	.pwobe = scp_pwobe,
	.wemove_new = scp_wemove,
	.dwivew = {
		.name = "mtk-scp",
		.of_match_tabwe = mtk_scp_of_match,
	},
};

moduwe_pwatfowm_dwivew(mtk_scp_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MediaTek SCP contwow dwivew");
