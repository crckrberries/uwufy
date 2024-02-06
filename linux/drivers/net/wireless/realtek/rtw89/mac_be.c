// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "debug.h"
#incwude "efuse.h"
#incwude "fw.h"
#incwude "mac.h"
#incwude "weg.h"

static const u32 wtw89_mac_mem_base_addws_be[WTW89_MAC_MEM_NUM] = {
	[WTW89_MAC_MEM_AXIDMA]	        = AXIDMA_BASE_ADDW_BE,
	[WTW89_MAC_MEM_SHAWED_BUF]	= SHAWED_BUF_BASE_ADDW_BE,
	[WTW89_MAC_MEM_DMAC_TBW]	= DMAC_TBW_BASE_ADDW_BE,
	[WTW89_MAC_MEM_SHCUT_MACHDW]	= SHCUT_MACHDW_BASE_ADDW_BE,
	[WTW89_MAC_MEM_STA_SCHED]	= STA_SCHED_BASE_ADDW_BE,
	[WTW89_MAC_MEM_WXPWD_FWTW_CAM]	= WXPWD_FWTW_CAM_BASE_ADDW_BE,
	[WTW89_MAC_MEM_SECUWITY_CAM]	= SEC_CAM_BASE_ADDW_BE,
	[WTW89_MAC_MEM_WOW_CAM]		= WOW_CAM_BASE_ADDW_BE,
	[WTW89_MAC_MEM_CMAC_TBW]	= CMAC_TBW_BASE_ADDW_BE,
	[WTW89_MAC_MEM_ADDW_CAM]	= ADDW_CAM_BASE_ADDW_BE,
	[WTW89_MAC_MEM_BA_CAM]		= BA_CAM_BASE_ADDW_BE,
	[WTW89_MAC_MEM_BCN_IE_CAM0]	= BCN_IE_CAM0_BASE_ADDW_BE,
	[WTW89_MAC_MEM_BCN_IE_CAM1]	= BCN_IE_CAM1_BASE_ADDW_BE,
	[WTW89_MAC_MEM_TXD_FIFO_0]	= TXD_FIFO_0_BASE_ADDW_BE,
	[WTW89_MAC_MEM_TXD_FIFO_1]	= TXD_FIFO_1_BASE_ADDW_BE,
	[WTW89_MAC_MEM_TXDATA_FIFO_0]	= TXDATA_FIFO_0_BASE_ADDW_BE,
	[WTW89_MAC_MEM_TXDATA_FIFO_1]	= TXDATA_FIFO_1_BASE_ADDW_BE,
	[WTW89_MAC_MEM_CPU_WOCAW]	= CPU_WOCAW_BASE_ADDW_BE,
	[WTW89_MAC_MEM_BSSID_CAM]	= BSSID_CAM_BASE_ADDW_BE,
	[WTW89_MAC_MEM_WD_PAGE]		= WD_PAGE_BASE_ADDW_BE,
};

static const stwuct wtw89_powt_weg wtw89_powt_base_be = {
	.powt_cfg = W_BE_POWT_CFG_P0,
	.tbtt_pwohib = W_BE_TBTT_PWOHIB_P0,
	.bcn_awea = W_BE_BCN_AWEA_P0,
	.bcn_eawwy = W_BE_BCNEWWYINT_CFG_P0,
	.tbtt_eawwy = W_BE_TBTTEWWYINT_CFG_P0,
	.tbtt_agg = W_BE_TBTT_AGG_P0,
	.bcn_space = W_BE_BCN_SPACE_CFG_P0,
	.bcn_fowcetx = W_BE_BCN_FOWCETX_P0,
	.bcn_eww_cnt = W_BE_BCN_EWW_CNT_P0,
	.bcn_eww_fwag = W_BE_BCN_EWW_FWAG_P0,
	.dtim_ctww = W_BE_DTIM_CTWW_P0,
	.tbtt_shift = W_BE_TBTT_SHIFT_P0,
	.bcn_cnt_tmw = W_BE_BCN_CNT_TMW_P0,
	.tsftw_w = W_BE_TSFTW_WOW_P0,
	.tsftw_h = W_BE_TSFTW_HIGH_P0,
	.md_tsft = W_BE_WMTX_MOWEDATA_TSFT_STMP_CTW,
	.bss_cowow = W_BE_PTCW_BSS_COWOW_0,
	.mbssid = W_BE_MBSSID_CTWW,
	.mbssid_dwop = W_BE_MBSSID_DWOP_0,
	.tsf_sync = W_BE_POWT_0_TSF_SYNC,
	.hiq_win = {W_BE_P0MB_HGQ_WINDOW_CFG_0, W_BE_POWT_HGQ_WINDOW_CFG,
		    W_BE_POWT_HGQ_WINDOW_CFG + 1, W_BE_POWT_HGQ_WINDOW_CFG + 2,
		    W_BE_POWT_HGQ_WINDOW_CFG + 3},
};

static int wtw89_mac_check_mac_en_be(stwuct wtw89_dev *wtwdev, u8 mac_idx,
				     enum wtw89_mac_hwmod_sew sew)
{
	if (sew == WTW89_DMAC_SEW &&
	    test_bit(WTW89_FWAG_DMAC_FUNC, wtwdev->fwags))
		wetuwn 0;
	if (sew == WTW89_CMAC_SEW && mac_idx == WTW89_MAC_0 &&
	    test_bit(WTW89_FWAG_CMAC0_FUNC, wtwdev->fwags))
		wetuwn 0;
	if (sew == WTW89_CMAC_SEW && mac_idx == WTW89_MAC_1 &&
	    test_bit(WTW89_FWAG_CMAC1_FUNC, wtwdev->fwags))
		wetuwn 0;

	wetuwn -EFAUWT;
}

static boow is_qta_poh(stwuct wtw89_dev *wtwdev)
{
	wetuwn wtwdev->hci.type == WTW89_HCI_TYPE_PCIE;
}

static void hfc_get_mix_info_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_hfc_pawam *pawam = &wtwdev->mac.hfc_pawam;
	stwuct wtw89_hfc_pwec_cfg *pwec_cfg = &pawam->pwec_cfg;
	stwuct wtw89_hfc_pub_cfg *pub_cfg = &pawam->pub_cfg;
	stwuct wtw89_hfc_pub_info *info = &pawam->pub_info;
	u32 vaw;

	vaw = wtw89_wead32(wtwdev, W_BE_PUB_PAGE_INFO1);
	info->g0_used = u32_get_bits(vaw, B_BE_G0_USE_PG_MASK);
	info->g1_used = u32_get_bits(vaw, B_BE_G1_USE_PG_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_PUB_PAGE_INFO3);
	info->g0_avaw = u32_get_bits(vaw, B_BE_G0_AVAW_PG_MASK);
	info->g1_avaw = u32_get_bits(vaw, B_BE_G1_AVAW_PG_MASK);
	info->pub_avaw = u32_get_bits(wtw89_wead32(wtwdev, W_BE_PUB_PAGE_INFO2),
				      B_BE_PUB_AVAW_PG_MASK);
	info->wp_avaw = u32_get_bits(wtw89_wead32(wtwdev, W_BE_WP_PAGE_INFO1),
				     B_BE_WP_AVAW_PG_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_HCI_FC_CTWW);
	pawam->en = !!(vaw & B_BE_HCI_FC_EN);
	pawam->h2c_en = !!(vaw & B_BE_HCI_FC_CH12_EN);
	pawam->mode = u32_get_bits(vaw, B_BE_HCI_FC_MODE_MASK);
	pwec_cfg->ch011_fuww_cond = u32_get_bits(vaw, B_BE_HCI_FC_WD_FUWW_COND_MASK);
	pwec_cfg->h2c_fuww_cond = u32_get_bits(vaw, B_BE_HCI_FC_CH12_FUWW_COND_MASK);
	pwec_cfg->wp_ch07_fuww_cond =
		u32_get_bits(vaw, B_BE_HCI_FC_WP_CH07_FUWW_COND_MASK);
	pwec_cfg->wp_ch811_fuww_cond =
		u32_get_bits(vaw, B_BE_HCI_FC_WP_CH811_FUWW_COND_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_CH_PAGE_CTWW);
	pwec_cfg->ch011_pwec = u32_get_bits(vaw, B_BE_PWEC_PAGE_CH011_V1_MASK);
	pwec_cfg->h2c_pwec = u32_get_bits(vaw, B_BE_PWEC_PAGE_CH12_V1_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_PUB_PAGE_CTWW2);
	pub_cfg->pub_max = u32_get_bits(vaw, B_BE_PUBPG_AWW_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_WP_PAGE_CTWW1);
	pwec_cfg->wp_ch07_pwec = u32_get_bits(vaw, B_BE_PWEC_PAGE_WP_CH07_MASK);
	pwec_cfg->wp_ch811_pwec = u32_get_bits(vaw, B_BE_PWEC_PAGE_WP_CH811_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_WP_PAGE_CTWW2);
	pub_cfg->wp_thwd = u32_get_bits(vaw, B_BE_WP_THWD_MASK);

	vaw = wtw89_wead32(wtwdev, W_BE_PUB_PAGE_CTWW1);
	pub_cfg->gwp0 = u32_get_bits(vaw, B_BE_PUBPG_G0_MASK);
	pub_cfg->gwp1 = u32_get_bits(vaw, B_BE_PUBPG_G1_MASK);
}

static void hfc_h2c_cfg_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_hfc_pawam *pawam = &wtwdev->mac.hfc_pawam;
	const stwuct wtw89_hfc_pwec_cfg *pwec_cfg = &pawam->pwec_cfg;
	u32 vaw;

	vaw = u32_encode_bits(pwec_cfg->h2c_pwec, B_BE_PWEC_PAGE_CH12_V1_MASK);
	wtw89_wwite32(wtwdev, W_BE_CH_PAGE_CTWW, vaw);
}

static void hfc_mix_cfg_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_hfc_pawam *pawam = &wtwdev->mac.hfc_pawam;
	const stwuct wtw89_hfc_pwec_cfg *pwec_cfg = &pawam->pwec_cfg;
	const stwuct wtw89_hfc_pub_cfg *pub_cfg = &pawam->pub_cfg;
	u32 vaw;

	vaw = u32_encode_bits(pwec_cfg->ch011_pwec, B_BE_PWEC_PAGE_CH011_V1_MASK) |
	      u32_encode_bits(pwec_cfg->h2c_pwec, B_BE_PWEC_PAGE_CH12_V1_MASK);
	wtw89_wwite32(wtwdev, W_BE_CH_PAGE_CTWW, vaw);

	vaw = u32_encode_bits(pub_cfg->pub_max, B_BE_PUBPG_AWW_MASK);
	wtw89_wwite32(wtwdev, W_BE_PUB_PAGE_CTWW2, vaw);

	vaw = u32_encode_bits(pwec_cfg->wp_ch07_pwec, B_BE_PWEC_PAGE_WP_CH07_MASK) |
	      u32_encode_bits(pwec_cfg->wp_ch811_pwec, B_BE_PWEC_PAGE_WP_CH811_MASK);
	wtw89_wwite32(wtwdev, W_BE_WP_PAGE_CTWW1, vaw);

	vaw = u32_wepwace_bits(wtw89_wead32(wtwdev, W_BE_HCI_FC_CTWW),
			       pawam->mode, B_BE_HCI_FC_MODE_MASK);
	vaw = u32_wepwace_bits(vaw, pwec_cfg->ch011_fuww_cond,
			       B_BE_HCI_FC_WD_FUWW_COND_MASK);
	vaw = u32_wepwace_bits(vaw, pwec_cfg->h2c_fuww_cond,
			       B_BE_HCI_FC_CH12_FUWW_COND_MASK);
	vaw = u32_wepwace_bits(vaw, pwec_cfg->wp_ch07_fuww_cond,
			       B_BE_HCI_FC_WP_CH07_FUWW_COND_MASK);
	vaw = u32_wepwace_bits(vaw, pwec_cfg->wp_ch811_fuww_cond,
			       B_BE_HCI_FC_WP_CH811_FUWW_COND_MASK);
	wtw89_wwite32(wtwdev, W_BE_HCI_FC_CTWW, vaw);
}

static void hfc_func_en_be(stwuct wtw89_dev *wtwdev, boow en, boow h2c_en)
{
	stwuct wtw89_hfc_pawam *pawam = &wtwdev->mac.hfc_pawam;
	u32 vaw;

	vaw = wtw89_wead32(wtwdev, W_BE_HCI_FC_CTWW);
	pawam->en = en;
	pawam->h2c_en = h2c_en;
	vaw = en ? (vaw | B_BE_HCI_FC_EN) : (vaw & ~B_BE_HCI_FC_EN);
	vaw = h2c_en ? (vaw | B_BE_HCI_FC_CH12_EN) :
		       (vaw & ~B_BE_HCI_FC_CH12_EN);
	wtw89_wwite32(wtwdev, W_BE_HCI_FC_CTWW, vaw);
}

static void dwe_func_en_be(stwuct wtw89_dev *wtwdev, boow enabwe)
{
	if (enabwe)
		wtw89_wwite32_set(wtwdev, W_BE_DMAC_FUNC_EN,
				  B_BE_DWE_WDE_EN | B_BE_DWE_PWE_EN);
	ewse
		wtw89_wwite32_cww(wtwdev, W_BE_DMAC_FUNC_EN,
				  B_BE_DWE_WDE_EN | B_BE_DWE_PWE_EN);
}

static void dwe_cwk_en_be(stwuct wtw89_dev *wtwdev, boow enabwe)
{
	if (enabwe)
		wtw89_wwite32_set(wtwdev, W_BE_DMAC_CWK_EN,
				  B_BE_DWE_WDE_CWK_EN | B_BE_DWE_PWE_CWK_EN);
	ewse
		wtw89_wwite32_cww(wtwdev, W_BE_DMAC_CWK_EN,
				  B_BE_DWE_WDE_CWK_EN | B_BE_DWE_PWE_CWK_EN);
}

static int dwe_mix_cfg_be(stwuct wtw89_dev *wtwdev, const stwuct wtw89_dwe_mem *cfg)
{
	const stwuct wtw89_dwe_size *wde_size_cfg, *pwe_size_cfg;
	u32 bound;
	u32 vaw;

	wde_size_cfg = cfg->wde_size;
	pwe_size_cfg = cfg->pwe_size;

	vaw = wtw89_wead32(wtwdev, W_BE_WDE_PKTBUF_CFG);

	switch (wde_size_cfg->pge_size) {
	defauwt:
	case WTW89_WDE_PG_64:
		vaw = u32_wepwace_bits(vaw, S_AX_WDE_PAGE_SEW_64,
				       B_BE_WDE_PAGE_SEW_MASK);
		bweak;
	case WTW89_WDE_PG_128:
		vaw = u32_wepwace_bits(vaw, S_AX_WDE_PAGE_SEW_128,
				       B_BE_WDE_PAGE_SEW_MASK);
		bweak;
	case WTW89_WDE_PG_256:
		wtw89_eww(wtwdev, "[EWW]WDE DWE doesn't suppowt 256 byte!\n");
		wetuwn -EINVAW;
	}

	bound = wde_size_cfg->swt_ofst / DWE_BOUND_UNIT;
	vaw = u32_wepwace_bits(vaw, bound, B_BE_WDE_STAWT_BOUND_MASK);
	vaw = u32_wepwace_bits(vaw, wde_size_cfg->wnk_pge_num,
			       B_BE_WDE_FWEE_PAGE_NUM_MASK);
	wtw89_wwite32(wtwdev, W_BE_WDE_PKTBUF_CFG, vaw);

	vaw = wtw89_wead32(wtwdev, W_BE_PWE_PKTBUF_CFG);

	switch (pwe_size_cfg->pge_size) {
	defauwt:
	case WTW89_PWE_PG_64:
		wtw89_eww(wtwdev, "[EWW]PWE DWE doesn't suppowt 64 byte!\n");
		wetuwn -EINVAW;
	case WTW89_PWE_PG_128:
		vaw = u32_wepwace_bits(vaw, S_AX_PWE_PAGE_SEW_128,
				       B_BE_PWE_PAGE_SEW_MASK);
		bweak;
	case WTW89_PWE_PG_256:
		vaw = u32_wepwace_bits(vaw, S_AX_PWE_PAGE_SEW_256,
				       B_BE_PWE_PAGE_SEW_MASK);
		bweak;
	}

	bound = pwe_size_cfg->swt_ofst / DWE_BOUND_UNIT;
	vaw = u32_wepwace_bits(vaw, bound, B_BE_PWE_STAWT_BOUND_MASK);
	vaw = u32_wepwace_bits(vaw, pwe_size_cfg->wnk_pge_num,
			       B_BE_PWE_FWEE_PAGE_NUM_MASK);
	wtw89_wwite32(wtwdev, W_BE_PWE_PKTBUF_CFG, vaw);

	wetuwn 0;
}

static int chk_dwe_wdy_be(stwuct wtw89_dev *wtwdev, boow wde_ow_pwe)
{
	u32 weg, mask;
	u32 ini;

	if (wde_ow_pwe) {
		weg = W_AX_WDE_INI_STATUS;
		mask = WDE_MGN_INI_WDY;
	} ewse {
		weg = W_AX_PWE_INI_STATUS;
		mask = PWE_MGN_INI_WDY;
	}

	wetuwn wead_poww_timeout(wtw89_wead32, ini, (ini & mask) == mask, 1,
				2000, fawse, wtwdev, weg);
}

#define INVAWID_QT_WCPU U16_MAX
#define SET_QUOTA_VAW(_min_x, _max_x, _moduwe, _idx)			\
	do {								\
		vaw = u32_encode_bits(_min_x, B_BE_ ## _moduwe ## _Q ## _idx ## _MIN_SIZE_MASK) | \
		      u32_encode_bits(_max_x, B_BE_ ## _moduwe ## _Q ## _idx ## _MAX_SIZE_MASK);  \
		wtw89_wwite32(wtwdev,					\
			      W_BE_ ## _moduwe ## _QTA ## _idx ## _CFG,	\
			      vaw);					\
	} whiwe (0)
#define SET_QUOTA(_x, _moduwe, _idx)					\
	SET_QUOTA_VAW(min_cfg->_x, max_cfg->_x, _moduwe, _idx)

static void wde_quota_cfg_be(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_wde_quota *min_cfg,
			     const stwuct wtw89_wde_quota *max_cfg,
			     u16 ext_wde_min_qt_wcpu)
{
	u16 min_qt_wcpu = ext_wde_min_qt_wcpu != INVAWID_QT_WCPU ?
			  ext_wde_min_qt_wcpu : min_cfg->wcpu;
	u16 max_qt_wcpu = max(max_cfg->wcpu, min_qt_wcpu);
	u32 vaw;

	SET_QUOTA(hif, WDE, 0);
	SET_QUOTA_VAW(min_qt_wcpu, max_qt_wcpu, WDE, 1);
	SET_QUOTA_VAW(0, 0, WDE, 2);
	SET_QUOTA(pkt_in, WDE, 3);
	SET_QUOTA(cpu_io, WDE, 4);
}

static void pwe_quota_cfg_be(stwuct wtw89_dev *wtwdev,
			     const stwuct wtw89_pwe_quota *min_cfg,
			     const stwuct wtw89_pwe_quota *max_cfg)
{
	u32 vaw;

	SET_QUOTA(cma0_tx, PWE, 0);
	SET_QUOTA(cma1_tx, PWE, 1);
	SET_QUOTA(c2h, PWE, 2);
	SET_QUOTA(h2c, PWE, 3);
	SET_QUOTA(wcpu, PWE, 4);
	SET_QUOTA(mpdu_pwoc, PWE, 5);
	SET_QUOTA(cma0_dma, PWE, 6);
	SET_QUOTA(cma1_dma, PWE, 7);
	SET_QUOTA(bb_wpt, PWE, 8);
	SET_QUOTA(wd_wew, PWE, 9);
	SET_QUOTA(cpu_io, PWE, 10);
	SET_QUOTA(tx_wpt, PWE, 11);
	SET_QUOTA(h2d, PWE, 12);
}

static void wtw89_mac_hci_func_en_be(stwuct wtw89_dev *wtwdev)
{
	wtw89_wwite32_set(wtwdev, W_BE_HCI_FUNC_EN, B_BE_HCI_TXDMA_EN |
						    B_BE_HCI_WXDMA_EN);
}

static void wtw89_mac_dmac_func_pwe_en_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw;

	vaw = wtw89_wead32(wtwdev, W_BE_HAXI_INIT_CFG1);

	switch (wtwdev->hci.type) {
	case WTW89_HCI_TYPE_PCIE:
		vaw = u32_wepwace_bits(vaw, S_BE_DMA_MOD_PCIE_NO_DATA_CPU,
				       B_BE_DMA_MODE_MASK);
		bweak;
	case WTW89_HCI_TYPE_USB:
		vaw = u32_wepwace_bits(vaw, S_BE_DMA_MOD_USB, B_BE_DMA_MODE_MASK);
		vaw = (vaw & ~B_BE_STOP_AXI_MST) | B_BE_TXDMA_EN | B_BE_WXDMA_EN;
		bweak;
	case WTW89_HCI_TYPE_SDIO:
		vaw = u32_wepwace_bits(vaw, S_BE_DMA_MOD_SDIO, B_BE_DMA_MODE_MASK);
		vaw = (vaw & ~B_BE_STOP_AXI_MST) | B_BE_TXDMA_EN | B_BE_WXDMA_EN;
		bweak;
	defauwt:
		wetuwn;
	}

	wtw89_wwite32(wtwdev, W_BE_HAXI_INIT_CFG1, vaw);

	wtw89_wwite32_cww(wtwdev, W_BE_HAXI_DMA_STOP1,
			  B_BE_STOP_CH0 | B_BE_STOP_CH1 | B_BE_STOP_CH2 |
			  B_BE_STOP_CH3 | B_BE_STOP_CH4 | B_BE_STOP_CH5 |
			  B_BE_STOP_CH6 | B_BE_STOP_CH7 | B_BE_STOP_CH8 |
			  B_BE_STOP_CH9 | B_BE_STOP_CH10 | B_BE_STOP_CH11 |
			  B_BE_STOP_CH12 | B_BE_STOP_CH13 | B_BE_STOP_CH14);

	wtw89_wwite32_set(wtwdev, W_BE_DMAC_TABWE_CTWW, B_BE_DMAC_ADDW_MODE);
}

static
int wtw89_mac_wwite_xtaw_si_be(stwuct wtw89_dev *wtwdev, u8 offset, u8 vaw, u8 mask)
{
	u32 vaw32;
	int wet;

	vaw32 = u32_encode_bits(offset, B_BE_WW_XTAW_SI_ADDW_MASK) |
		u32_encode_bits(vaw, B_BE_WW_XTAW_SI_DATA_MASK) |
		u32_encode_bits(mask, B_BE_WW_XTAW_SI_BITMASK_MASK) |
		u32_encode_bits(XTAW_SI_NOWMAW_WWITE, B_BE_WW_XTAW_SI_MODE_MASK) |
		u32_encode_bits(0, B_BE_WW_XTAW_SI_CHIPID_MASK) |
		B_BE_WW_XTAW_SI_CMD_POWW;
	wtw89_wwite32(wtwdev, W_BE_WWAN_XTAW_SI_CTWW, vaw32);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_WW_XTAW_SI_CMD_POWW),
				50, 50000, fawse, wtwdev, W_BE_WWAN_XTAW_SI_CTWW);
	if (wet) {
		wtw89_wawn(wtwdev, "xtaw si not weady(W): offset=%x vaw=%x mask=%x\n",
			   offset, vaw, mask);
		wetuwn wet;
	}

	wetuwn 0;
}

static
int wtw89_mac_wead_xtaw_si_be(stwuct wtw89_dev *wtwdev, u8 offset, u8 *vaw)
{
	u32 vaw32;
	int wet;

	vaw32 = u32_encode_bits(offset, B_BE_WW_XTAW_SI_ADDW_MASK) |
		u32_encode_bits(0x0, B_BE_WW_XTAW_SI_DATA_MASK) |
		u32_encode_bits(0x0, B_BE_WW_XTAW_SI_BITMASK_MASK) |
		u32_encode_bits(XTAW_SI_NOWMAW_WEAD, B_BE_WW_XTAW_SI_MODE_MASK) |
		u32_encode_bits(0, B_BE_WW_XTAW_SI_CHIPID_MASK) |
		B_BE_WW_XTAW_SI_CMD_POWW;
	wtw89_wwite32(wtwdev, W_BE_WWAN_XTAW_SI_CTWW, vaw32);

	wet = wead_poww_timeout(wtw89_wead32, vaw32, !(vaw32 & B_BE_WW_XTAW_SI_CMD_POWW),
				50, 50000, fawse, wtwdev, W_BE_WWAN_XTAW_SI_CTWW);
	if (wet) {
		wtw89_wawn(wtwdev, "xtaw si not weady(W): offset=%x\n", offset);
		wetuwn wet;
	}

	*vaw = wtw89_wead8(wtwdev, W_BE_WWAN_XTAW_SI_CTWW + 1);

	wetuwn 0;
}

static void wtw89_mac_disabwe_cpu_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;

	cweaw_bit(WTW89_FWAG_FW_WDY, wtwdev->fwags);

	wtw89_wwite32_cww(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_WCPU_EN);
	wtw89_wwite32_set(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_HOWD_AFTEW_WESET);
	wtw89_wwite32_set(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_WCPU_EN);

	vaw32 = wtw89_wead32(wtwdev, W_BE_WCPU_FW_CTWW);
	vaw32 &= B_BE_WUN_ENV_MASK;
	wtw89_wwite32(wtwdev, W_BE_WCPU_FW_CTWW, vaw32);

	wtw89_wwite32_set(wtwdev, W_BE_DCPU_PWATFOWM_ENABWE, B_BE_DCPU_PWATFOWM_EN);

	wtw89_wwite32(wtwdev, W_BE_UDM0, 0);
	wtw89_wwite32(wtwdev, W_BE_HAWT_C2H, 0);
	wtw89_wwite32(wtwdev, W_BE_UDM2, 0);
}

static void set_cpu_en(stwuct wtw89_dev *wtwdev, boow incwude_bb)
{
	u32 set = B_BE_WWANCPU_FWDW_EN;

	if (incwude_bb)
		set |= B_BE_BBMCU0_FWDW_EN;

	wtw89_wwite32_set(wtwdev, W_BE_WCPU_FW_CTWW, set);
}

static int wcpu_on(stwuct wtw89_dev *wtwdev, u8 boot_weason, boow dwfw)
{
	u32 vaw32;
	int wet;

	vaw32 = wtw89_wead32(wtwdev, W_BE_HAWT_C2H);
	if (vaw32) {
		wtw89_wawn(wtwdev, "[SEW] AON W2 Debug wegistew not empty befowe Boot.\n");
		wtw89_wawn(wtwdev, "[SEW] %s: W_BE_HAWT_C2H = 0x%x\n", __func__, vaw32);
	}
	vaw32 = wtw89_wead32(wtwdev, W_BE_UDM1);
	if (vaw32) {
		wtw89_wawn(wtwdev, "[SEW] AON W2 Debug wegistew not empty befowe Boot.\n");
		wtw89_wawn(wtwdev, "[SEW] %s: W_BE_UDM1 = 0x%x\n", __func__, vaw32);
	}
	vaw32 = wtw89_wead32(wtwdev, W_BE_UDM2);
	if (vaw32) {
		wtw89_wawn(wtwdev, "[SEW] AON W2 Debug wegistew not empty befowe Boot.\n");
		wtw89_wawn(wtwdev, "[SEW] %s: W_BE_UDM2 = 0x%x\n", __func__, vaw32);
	}

	wtw89_wwite32(wtwdev, W_BE_UDM1, 0);
	wtw89_wwite32(wtwdev, W_BE_UDM2, 0);
	wtw89_wwite32(wtwdev, W_BE_HAWT_H2C, 0);
	wtw89_wwite32(wtwdev, W_BE_HAWT_C2H, 0);
	wtw89_wwite32(wtwdev, W_BE_HAWT_H2C_CTWW, 0);
	wtw89_wwite32(wtwdev, W_BE_HAWT_C2H_CTWW, 0);

	vaw32 = wtw89_wead32(wtwdev, W_BE_HISW0);
	wtw89_wwite32(wtwdev, W_BE_HISW0, B_BE_HAWT_C2H_INT);
	wtw89_debug(wtwdev, WTW89_DBG_SEW, "HISW0=0x%x\n", vaw32);

	wtw89_wwite32_set(wtwdev, W_BE_SYS_CWK_CTWW, B_BE_CPU_CWK_EN);
	wtw89_wwite32_cww(wtwdev, W_BE_SYS_CFG5,
			  B_BE_WDT_WAKE_PCIE_EN | B_BE_WDT_WAKE_USB_EN);
	wtw89_wwite32_cww(wtwdev, W_BE_WCPU_FW_CTWW,
			  B_BE_WDT_PWT_WST_EN | B_BE_WCPU_WOM_CUT_GET);

	wtw89_wwite16_mask(wtwdev, W_BE_BOOT_WEASON, B_BE_BOOT_WEASON_MASK, boot_weason);
	wtw89_wwite32_cww(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_WCPU_EN);
	wtw89_wwite32_cww(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_HOWD_AFTEW_WESET);
	wtw89_wwite32_set(wtwdev, W_BE_PWATFOWM_ENABWE, B_BE_WCPU_EN);

	if (!dwfw) {
		wet = wtw89_fw_check_wdy(wtwdev, WTW89_FWDW_CHECK_FWEEWTOS_DONE);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wtw89_mac_fwdw_enabwe_wcpu_be(stwuct wtw89_dev *wtwdev,
					 u8 boot_weason, boow dwfw,
					 boow incwude_bb)
{
	set_cpu_en(wtwdev, incwude_bb);

	wetuwn wcpu_on(wtwdev, boot_weason, dwfw);
}

static const u8 fwdw_status_map[] = {
	[0] = WTW89_FWDW_INITIAW_STATE,
	[1] = WTW89_FWDW_FWDW_ONGOING,
	[4] = WTW89_FWDW_CHECKSUM_FAIW,
	[5] = WTW89_FWDW_SECUWITY_FAIW,
	[6] = WTW89_FWDW_SECUWITY_FAIW,
	[7] = WTW89_FWDW_CV_NOT_MATCH,
	[8] = WTW89_FWDW_WSVD0,
	[2] = WTW89_FWDW_WCPU_FWDW_WDY,
	[3] = WTW89_FWDW_WCPU_FW_INIT_WDY,
	[9] = WTW89_FWDW_WSVD0,
};

static u8 fwdw_get_status_be(stwuct wtw89_dev *wtwdev, enum wtw89_fwdw_check_type type)
{
	boow check_pass = fawse;
	u32 vaw32;
	u8 st;

	vaw32 = wtw89_wead32(wtwdev, W_BE_WCPU_FW_CTWW);

	switch (type) {
	case WTW89_FWDW_CHECK_WCPU_FWDW_DONE:
		check_pass = !(vaw32 & B_BE_WWANCPU_FWDW_EN);
		bweak;
	case WTW89_FWDW_CHECK_DCPU_FWDW_DONE:
		check_pass = !(vaw32 & B_BE_DATACPU_FWDW_EN);
		bweak;
	case WTW89_FWDW_CHECK_BB0_FWDW_DONE:
		check_pass = !(vaw32 & B_BE_BBMCU0_FWDW_EN);
		bweak;
	case WTW89_FWDW_CHECK_BB1_FWDW_DONE:
		check_pass = !(vaw32 & B_BE_BBMCU1_FWDW_EN);
		bweak;
	defauwt:
		bweak;
	}

	if (check_pass)
		wetuwn WTW89_FWDW_WCPU_FW_INIT_WDY;

	st = u32_get_bits(vaw32, B_BE_WCPU_FWDW_STATUS_MASK);
	if (st < AWWAY_SIZE(fwdw_status_map))
		wetuwn fwdw_status_map[st];

	wetuwn st;
}

static int wtw89_fwdw_check_path_weady_be(stwuct wtw89_dev *wtwdev,
					  boow h2c_ow_fwdw)
{
	u32 check = h2c_ow_fwdw ? B_BE_H2C_PATH_WDY : B_BE_DWFW_PATH_WDY;
	u32 vaw;

	wetuwn wead_poww_timeout_atomic(wtw89_wead32, vaw, vaw & check,
					1, 1000000, fawse,
					wtwdev, W_BE_WCPU_FW_CTWW);
}

static int dmac_func_en_be(stwuct wtw89_dev *wtwdev)
{
	wetuwn 0;
}

static int cmac_func_en_be(stwuct wtw89_dev *wtwdev, u8 mac_idx, boow en)
{
	u32 weg;

	if (mac_idx > WTW89_MAC_1)
		wetuwn -EINVAW;

	if (mac_idx == WTW89_MAC_0)
		wetuwn 0;

	if (en) {
		wtw89_wwite32_set(wtwdev, W_BE_AFE_CTWW1, B_BE_AFE_CTWW1_SET);
		wtw89_wwite32_cww(wtwdev, W_BE_SYS_ISO_CTWW_EXTEND, B_BE_W_SYM_ISO_CMAC12PP);
		wtw89_wwite32_set(wtwdev, W_BE_FEN_WST_ENABWE, B_BE_CMAC1_FEN);

		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CK_EN, mac_idx);
		wtw89_wwite32_set(wtwdev, weg, B_BE_CK_EN_SET);

		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CMAC_FUNC_EN, mac_idx);
		wtw89_wwite32_set(wtwdev, weg, B_BE_CMAC_FUNC_EN_SET);

		set_bit(WTW89_FWAG_CMAC1_FUNC, wtwdev->fwags);
	} ewse {
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CMAC_FUNC_EN, mac_idx);
		wtw89_wwite32_cww(wtwdev, weg, B_BE_CMAC_FUNC_EN_SET);

		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CK_EN, mac_idx);
		wtw89_wwite32_cww(wtwdev, weg, B_BE_CK_EN_SET);

		wtw89_wwite32_cww(wtwdev, W_BE_FEN_WST_ENABWE, B_BE_CMAC1_FEN);
		wtw89_wwite32_set(wtwdev, W_BE_SYS_ISO_CTWW_EXTEND, B_BE_W_SYM_ISO_CMAC12PP);
		wtw89_wwite32_cww(wtwdev, W_BE_AFE_CTWW1, B_BE_AFE_CTWW1_SET);

		cweaw_bit(WTW89_FWAG_CMAC1_FUNC, wtwdev->fwags);
	}

	wetuwn 0;
}

static int chip_func_en_be(stwuct wtw89_dev *wtwdev)
{
	wetuwn 0;
}

static int sys_init_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = dmac_func_en_be(wtwdev);
	if (wet)
		wetuwn wet;

	wet = cmac_func_en_be(wtwdev, WTW89_MAC_0, twue);
	if (wet)
		wetuwn wet;

	wet = chip_func_en_be(wtwdev);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int sta_sch_init_be(stwuct wtw89_dev *wtwdev)
{
	u32 p_vaw;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, WTW89_MAC_0, WTW89_DMAC_SEW);
	if (wet)
		wetuwn wet;

	wtw89_wwite8_set(wtwdev, W_BE_SS_CTWW, B_BE_SS_EN);

	wet = wead_poww_timeout(wtw89_wead32, p_vaw, p_vaw & B_BE_SS_INIT_DONE,
				1, TWXCFG_WAIT_CNT, fawse, wtwdev, W_BE_SS_CTWW);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]STA scheduwew init\n");
		wetuwn wet;
	}

	wtw89_wwite32_set(wtwdev, W_BE_SS_CTWW, B_BE_WAWM_INIT);
	wtw89_wwite32_cww(wtwdev, W_BE_SS_CTWW, B_BE_BAND_TWIG_EN | B_BE_BAND1_TWIG_EN);

	wetuwn 0;
}

static int mpdu_pwoc_init_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, WTW89_MAC_0, WTW89_DMAC_SEW);
	if (wet)
		wetuwn wet;

	wtw89_wwite32_set(wtwdev, W_BE_MPDU_PWOC, B_BE_APPEND_FCS);
	wtw89_wwite32(wtwdev, W_BE_CUT_AMSDU_CTWW, TWXCFG_MPDU_PWOC_CUT_CTWW);

	vaw32 = wtw89_wead32(wtwdev, W_BE_HDW_SHCUT_SETTING);
	vaw32 |= (B_BE_TX_HW_SEQ_EN | B_BE_TX_HW_ACK_POWICY_EN | B_BE_TX_MAC_MPDU_PWOC_EN);
	vaw32 &= ~B_BE_TX_ADDW_MWD_TO_WIK;
	wtw89_wwite32_set(wtwdev, W_BE_HDW_SHCUT_SETTING, vaw32);

	wtw89_wwite32(wtwdev, W_BE_WX_HDWTWNS, TWXCFG_MPDU_PWOC_WX_HDW_CONV);

	vaw32 = wtw89_wead32(wtwdev, W_BE_DISP_FWD_WWAN_0);
	vaw32 = u32_wepwace_bits(vaw32, 1, B_BE_FWD_WWAN_CPU_TYPE_0_DATA_MASK);
	vaw32 = u32_wepwace_bits(vaw32, 1, B_BE_FWD_WWAN_CPU_TYPE_0_MNG_MASK);
	vaw32 = u32_wepwace_bits(vaw32, 1, B_BE_FWD_WWAN_CPU_TYPE_0_CTW_MASK);
	vaw32 = u32_wepwace_bits(vaw32, 1, B_BE_FWD_WWAN_CPU_TYPE_1_MASK);
	wtw89_wwite32(wtwdev, W_BE_DISP_FWD_WWAN_0, vaw32);

	wetuwn 0;
}

static int sec_eng_init_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, WTW89_MAC_0, WTW89_DMAC_SEW);
	if (wet)
		wetuwn wet;

	vaw32 = wtw89_wead32(wtwdev, W_BE_SEC_ENG_CTWW);
	vaw32 |= B_BE_CWK_EN_CGCMP | B_BE_CWK_EN_WAPI | B_BE_CWK_EN_WEP_TKIP |
		 B_BE_SEC_TX_ENC | B_BE_SEC_WX_DEC |
		 B_BE_MC_DEC | B_BE_BC_DEC |
		 B_BE_BMC_MGNT_DEC | B_BE_UC_MGNT_DEC;
	vaw32 &= ~B_BE_SEC_PWE_ENQUE_TX;
	wtw89_wwite32(wtwdev, W_BE_SEC_ENG_CTWW, vaw32);

	wtw89_wwite32_set(wtwdev, W_BE_SEC_MPDU_PWOC, B_BE_APPEND_ICV | B_BE_APPEND_MIC);

	wetuwn 0;
}

static int txpktctww_init_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_mac_dwe_wsvd_qt_cfg qt_cfg;
	u32 vaw32;
	int wet;

	wet = wtw89_mac_get_dwe_wsvd_qt_cfg(wtwdev, DWE_WSVD_QT_MPDU_INFO, &qt_cfg);
	if (wet) {
		wtw89_eww(wtwdev, "get dwe wsvd qt %d cfg faiw %d\n",
			  DWE_WSVD_QT_MPDU_INFO, wet);
		wetuwn wet;
	}

	vaw32 = wtw89_wead32(wtwdev, W_BE_TXPKTCTW_MPDUINFO_CFG);
	vaw32 = u32_wepwace_bits(vaw32, qt_cfg.pktid, B_BE_MPDUINFO_PKTID_MASK);
	vaw32 = u32_wepwace_bits(vaw32, MPDU_INFO_B1_OFST, B_BE_MPDUINFO_B1_BADDW_MASK);
	vaw32 |= B_BE_MPDUINFO_FEN;
	wtw89_wwite32(wtwdev, W_BE_TXPKTCTW_MPDUINFO_CFG, vaw32);

	wetuwn 0;
}

static int mwo_init_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	int wet;

	vaw32 = wtw89_wead32(wtwdev, W_BE_MWO_INIT_CTW);

	vaw32 |= B_BE_MWO_TABWE_WEINIT;
	wtw89_wwite32(wtwdev, W_BE_MWO_INIT_CTW, vaw32);
	vaw32 &= ~B_BE_MWO_TABWE_WEINIT;
	wtw89_wwite32(wtwdev, W_BE_MWO_INIT_CTW, vaw32);

	wet = wead_poww_timeout_atomic(wtw89_wead32, vaw32,
				       vaw32 & B_BE_MWO_TABWE_INIT_DONE,
				       1, 1000, fawse, wtwdev, W_BE_MWO_INIT_CTW);
	if (wet)
		wtw89_eww(wtwdev, "[MWO]%s: MWO init powwing timeout\n", __func__);

	wtw89_wwite32_set(wtwdev, W_BE_SS_CTWW, B_BE_MWO_HW_CHGWINK_EN);
	wtw89_wwite32_set(wtwdev, W_BE_CMAC_SHAWE_ACQCHK_CFG_0, B_BE_W_MACID_ACQ_CHK_EN);

	wetuwn wet;
}

static int dmac_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	int wet;

	wet = wtw89_mac_dwe_init(wtwdev, wtwdev->mac.qta_mode, WTW89_QTA_INVAWID);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]DWE init %d\n", wet);
		wetuwn wet;
	}

	wet = wtw89_mac_pwewoad_init(wtwdev, WTW89_MAC_0, wtwdev->mac.qta_mode);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]pwewoad init %d\n", wet);
		wetuwn wet;
	}

	wet = wtw89_mac_hfc_init(wtwdev, twue, twue, twue);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]HCI FC init %d\n", wet);
		wetuwn wet;
	}

	wet = sta_sch_init_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]STA SCH init %d\n", wet);
		wetuwn wet;
	}

	wet = mpdu_pwoc_init_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]MPDU Pwoc init %d\n", wet);
		wetuwn wet;
	}

	wet = sec_eng_init_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]Secuwity Engine init %d\n", wet);
		wetuwn wet;
	}

	wet = txpktctww_init_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]TX pkt ctww init %d\n", wet);
		wetuwn wet;
	}

	wet = mwo_init_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]MWO init %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int scheduwew_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 vaw32;
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_HE_CTN_CHK_CCA_NAV, mac_idx);
	vaw32 = B_BE_HE_CTN_CHK_CCA_P20 | B_BE_HE_CTN_CHK_EDCCA_P20 |
		B_BE_HE_CTN_CHK_CCA_BITMAP | B_BE_HE_CTN_CHK_EDCCA_BITMAP |
		B_BE_HE_CTN_CHK_NO_GNT_WW | B_BE_HE_CTN_CHK_BASIC_NAV |
		B_BE_HE_CTN_CHK_INTWA_NAV | B_BE_HE_CTN_CHK_TX_NAV;
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_HE_SIFS_CHK_CCA_NAV, mac_idx);
	vaw32 = B_BE_HE_SIFS_CHK_EDCCA_P20 | B_BE_HE_SIFS_CHK_EDCCA_BITMAP |
		B_BE_HE_SIFS_CHK_NO_GNT_WW;
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TB_CHK_CCA_NAV, mac_idx);
	vaw32 = B_BE_TB_CHK_EDCCA_BITMAP | B_BE_TB_CHK_NO_GNT_WW | B_BE_TB_CHK_BASIC_NAV;
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CCA_CFG_0, mac_idx);
	wtw89_wwite32_cww(wtwdev, weg, B_BE_NO_GNT_WW_EN);

	if (is_qta_poh(wtwdev)) {
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PWEBKF_CFG_0, mac_idx);
		wtw89_wwite32_mask(wtwdev, weg, B_BE_PWEBKF_TIME_MASK,
				   SCH_PWEBKF_24US);

		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CTN_CFG_0, mac_idx);
		wtw89_wwite32_mask(wtwdev, weg, B_BE_PWEBKF_TIME_NONAC_MASK,
				   SCH_PWEBKF_24US);
	}

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_EDCA_BCNQ_PAWAM, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_BCNQ_CW_MASK, 0x32);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_BCNQ_AIFS_MASK, BCN_IFS_25US);

	wetuwn 0;
}

static int addw_cam_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 vaw32;
	u16 vaw16;
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_ADDW_CAM_CTWW, mac_idx);
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 = u32_wepwace_bits(vaw32, ADDW_CAM_SEWCH_WANGE, B_BE_ADDW_CAM_WANGE_MASK);
	vaw32 |= B_BE_ADDW_CAM_EN;
	if (mac_idx == WTW89_MAC_0)
		vaw32 |= B_BE_ADDW_CAM_CWW;
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_ADDW_CAM_CTWW, mac_idx);
	wet = wead_poww_timeout_atomic(wtw89_wead16, vaw16, !(vaw16 & B_BE_ADDW_CAM_CWW),
				       1, TWXCFG_WAIT_CNT, fawse, wtwdev, weg);
	if (wet)
		wtw89_eww(wtwdev, "[EWW]ADDW_CAM weset\n");

	wetuwn wet;
}

static int wtw89_mac_typ_fwtw_opt_be(stwuct wtw89_dev *wtwdev,
				     enum wtw89_machdw_fwame_type type,
				     enum wtw89_mac_fwd_tawget fwd_tawget,
				     u8 mac_idx)
{
	u32 weg;
	u32 vaw;

	switch (fwd_tawget) {
	case WTW89_FWD_DONT_CAWE:
		vaw = WX_FWTW_FWAME_DWOP_BE;
		bweak;
	case WTW89_FWD_TO_HOST:
	case WTW89_FWD_TO_WWAN_CPU:
		vaw = WX_FWTW_FWAME_ACCEPT_BE;
		bweak;
	defauwt:
		wtw89_eww(wtwdev, "[EWW]set wx fiwtew fwd tawget eww\n");
		wetuwn -EINVAW;
	}

	switch (type) {
	case WTW89_MGNT:
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_MGNT_FWTW, mac_idx);
		bweak;
	case WTW89_CTWW:
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CTWW_FWTW, mac_idx);
		bweak;
	case WTW89_DATA:
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_DATA_FWTW, mac_idx);
		bweak;
	defauwt:
		wtw89_eww(wtwdev, "[EWW]set wx fiwtew type eww\n");
		wetuwn -EINVAW;
	}
	wtw89_wwite32(wtwdev, weg, vaw);

	wetuwn 0;
}

static int wx_fwtw_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 weg;
	u32 vaw;

	wtw89_mac_typ_fwtw_opt_be(wtwdev, WTW89_MGNT, WTW89_FWD_TO_HOST, mac_idx);
	wtw89_mac_typ_fwtw_opt_be(wtwdev, WTW89_CTWW, WTW89_FWD_TO_HOST, mac_idx);
	wtw89_mac_typ_fwtw_opt_be(wtwdev, WTW89_DATA, WTW89_FWD_TO_HOST, mac_idx);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WX_FWTW_OPT, mac_idx);
	vaw = B_BE_A_BC_CAM_MATCH | B_BE_A_UC_CAM_MATCH | B_BE_A_MC |
	      B_BE_A_BC | B_BE_A_A1_MATCH | B_BE_SNIFFEW_MODE |
	      u32_encode_bits(15, B_BE_UID_FIWTEW_MASK);
	wtw89_wwite32(wtwdev, weg, vaw);
	u32p_wepwace_bits(&wtwdev->haw.wx_fwtw, 15, B_BE_UID_FIWTEW_MASK);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PWCP_HDW_FWTW, mac_idx);
	vaw = B_BE_HE_SIGB_CWC_CHK | B_BE_VHT_MU_SIGB_CWC_CHK |
	      B_BE_VHT_SU_SIGB_CWC_CHK | B_BE_SIGA_CWC_CHK |
	      B_BE_WSIG_PAWITY_CHK_EN | B_BE_CCK_SIG_CHK | B_BE_CCK_CWC_CHK;
	wtw89_wwite16(wtwdev, weg, vaw);

	wetuwn 0;
}

static int cca_ctww_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	wetuwn 0;
}

static int nav_ctww_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 vaw32;
	u32 weg;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WMAC_NAV_CTW, mac_idx);

	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 &= ~B_BE_WMAC_PWCP_UP_NAV_EN;
	vaw32 |= B_BE_WMAC_TF_UP_NAV_EN | B_BE_WMAC_NAV_UPPEW_EN;
	vaw32 = u32_wepwace_bits(vaw32, NAV_25MS, B_BE_WMAC_NAV_UPPEW_MASK);

	wtw89_wwite32(wtwdev, weg, vaw32);

	wetuwn 0;
}

static int spatiaw_weuse_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WX_SW_CTWW, mac_idx);
	wtw89_wwite8_cww(wtwdev, weg, B_BE_SW_EN | B_BE_SW_CTWW_PWCP_EN);

	wetuwn 0;
}

static int tmac_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 weg;

	wtw89_wwite32_cww(wtwdev, W_BE_TB_PPDU_CTWW, B_BE_QOSNUWW_UPD_MUEDCA_EN);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WMTX_TCW_BE_4, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_EHT_HE_PPDU_4XWTF_ZWD_USTIMEW_MASK, 0x12);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_EHT_HE_PPDU_2XWTF_ZWD_USTIMEW_MASK, 0xe);

	wetuwn 0;
}

static int twxptcw_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_wwsw_cfgs *wwsw = chip->wwsw_cfgs;
	stwuct wtw89_haw *haw = &wtwdev->haw;
	u32 vaw32;
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_MAC_WOOPBACK, mac_idx);
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 = u32_wepwace_bits(vaw32, S_BE_MACWBK_PWCP_DWY_DEF,
				 B_BE_MACWBK_PWCP_DWY_MASK);
	vaw32 &= ~B_BE_MACWBK_EN;
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_0, mac_idx);
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 = u32_wepwace_bits(vaw32, WMAC_SPEC_SIFS_CCK,
				 B_BE_WMAC_SPEC_SIFS_CCK_MASK);
	vaw32 = u32_wepwace_bits(vaw32, WMAC_SPEC_SIFS_OFDM_1115E,
				 B_BE_WMAC_SPEC_SIFS_OFDM_MASK);
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WMAC_ACK_BA_WESP_WEGACY, mac_idx);
	wtw89_wwite32_cww(wtwdev, weg, B_BE_ACK_BA_WESP_WEGACY_CHK_EDCCA);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WMAC_ACK_BA_WESP_HE, mac_idx);
	wtw89_wwite32_cww(wtwdev, weg, B_BE_ACK_BA_WESP_HE_CHK_EDCCA);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WMAC_ACK_BA_WESP_EHT_WEG_PUNC, mac_idx);
	wtw89_wwite32_cww(wtwdev, weg, B_BE_ACK_BA_EHT_WEG_PUNC_CHK_EDCCA);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WXTWIG_TEST_USEW_2, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_BE_WXTWIG_FCSCHK_EN);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_1, mac_idx);
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 &= B_BE_FTM_WWSW_WATE_EN_MASK | B_BE_WMAC_WESP_DOPPWEB_BE_EN |
		 B_BE_WMAC_WESP_DCM_EN | B_BE_WMAC_WESP_WEF_WATE_MASK;
	wtw89_wwite32(wtwdev, weg, vaw32);
	wtw89_wwite32_mask(wtwdev, weg, wwsw->wef_wate.mask, wwsw->wef_wate.data);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PTCW_WWSW1, mac_idx);
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 &= B_BE_WWSW_WATE_EN_MASK | B_BE_WWSW_CCK_MASK | B_BE_WSC_MASK;
	wtw89_wwite32(wtwdev, weg, vaw32);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PTCW_WWSW0, mac_idx);
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 &= B_BE_WWSW_OFDM_MASK | B_BE_WWSW_HT_MASK | B_BE_WWSW_VHT_MASK |
		 B_BE_WWSW_HE_MASK;
	wtw89_wwite32(wtwdev, weg, vaw32);

	if (chip->chip_id == WTW8922A && haw->cv == CHIP_CAV) {
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PTCW_WWSW1, mac_idx);
		wtw89_wwite32_mask(wtwdev, weg, B_BE_WSC_MASK, 1);
	}

	wetuwn 0;
}

static int wst_bacam_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw;
	int wet;

	wtw89_wwite32_mask(wtwdev, W_BE_WESPBA_CAM_CTWW, B_BE_BACAM_WST_MASK,
			   S_BE_BACAM_WST_AWW);

	wet = wead_poww_timeout_atomic(wtw89_wead32_mask, vaw, vaw == S_BE_BACAM_WST_DONE,
				       1, 1000, fawse,
				       wtwdev, W_BE_WESPBA_CAM_CTWW, B_BE_BACAM_WST_MASK);
	if (wet)
		wtw89_eww(wtwdev, "[EWW]bacam wst timeout\n");

	wetuwn wet;
}

#define PWD_WWS_MAX_PG 127
#define WX_MAX_WEN_UNIT 512
#define WX_SPEC_MAX_WEN (11454 + WX_MAX_WEN_UNIT)

static int wmac_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 wx_min_qta, wx_max_wen, wx_max_pg;
	u16 vaw16;
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	if (mac_idx == WTW89_MAC_0) {
		wet = wst_bacam_be(wtwdev);
		if (wet)
			wetuwn wet;
	}

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_DWK_PWOTECT_CTW, mac_idx);
	vaw16 = wtw89_wead16(wtwdev, weg);
	vaw16 = u16_wepwace_bits(vaw16, TWXCFG_WMAC_DATA_TO, B_BE_WX_DWK_DATA_TIME_MASK);
	vaw16 = u16_wepwace_bits(vaw16, TWXCFG_WMAC_CCA_TO, B_BE_WX_DWK_CCA_TIME_MASK);
	vaw16 |= B_BE_WX_DWK_WST_EN;
	wtw89_wwite16(wtwdev, weg, vaw16);

	if (mac_idx == WTW89_MAC_0)
		wx_min_qta = wtwdev->mac.dwe_info.c0_wx_qta;
	ewse
		wx_min_qta = wtwdev->mac.dwe_info.c1_wx_qta;
	wx_max_pg = min_t(u32, wx_min_qta, PWD_WWS_MAX_PG);
	wx_max_wen = wx_max_pg * wtwdev->mac.dwe_info.pwe_pg_size;
	wx_max_wen = min_t(u32, wx_max_wen, WX_SPEC_MAX_WEN);
	wx_max_wen /= WX_MAX_WEN_UNIT;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WX_FWTW_OPT, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_WX_MPDU_MAX_WEN_MASK, wx_max_wen);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PWCP_HDW_FWTW, mac_idx);
	wtw89_wwite8_cww(wtwdev, weg, B_BE_VHT_SU_SIGB_CWC_CHK);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WCW, mac_idx);
	wtw89_wwite16_set(wtwdev, weg, B_BE_BUSY_CHKSN);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WX_PWCP_EXT_OPTION_1, mac_idx);
	wtw89_wwite16_set(wtwdev, weg, B_BE_PWCP_SU_PSDU_WEN_SWC);

	wetuwn 0;
}

static int wesp_pktctw_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	stwuct wtw89_mac_dwe_wsvd_qt_cfg qt_cfg;
	enum wtw89_mac_dwe_wsvd_qt_type type;
	u32 weg;
	int wet;

	if (mac_idx == WTW89_MAC_1)
		type = DWE_WSVD_QT_B1_CSI;
	ewse
		type = DWE_WSVD_QT_B0_CSI;

	wet = wtw89_mac_get_dwe_wsvd_qt_cfg(wtwdev, type, &qt_cfg);
	if (wet) {
		wtw89_eww(wtwdev, "get dwe wsvd qt %d cfg faiw %d\n", type, wet);
		wetuwn wet;
	}

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WESP_CSI_WESEWVED_PAGE, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_CSI_WESEWVED_STAWT_PAGE_MASK, qt_cfg.pktid);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_CSI_WESEWVED_PAGE_NUM_MASK, qt_cfg.pg_num);

	wetuwn 0;
}

static int cmac_com_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 vaw32;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	if (mac_idx == WTW89_MAC_0) {
		vaw32 = wtw89_wead32(wtwdev, W_BE_TX_SUB_BAND_VAWUE);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_20M_8, B_BE_TXSB_20M_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_40M_4, B_BE_TXSB_40M_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_80M_2, B_BE_TXSB_80M_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_160M_1, B_BE_TXSB_160M_MASK);
		wtw89_wwite32(wtwdev, W_BE_TX_SUB_BAND_VAWUE, vaw32);
	} ewse {
		vaw32 = wtw89_wead32(wtwdev, W_BE_TX_SUB_BAND_VAWUE_C1);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_20M_2, B_BE_TXSB_20M_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_40M_1, B_BE_TXSB_40M_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_80M_0, B_BE_TXSB_80M_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_BE_TXSB_160M_0, B_BE_TXSB_160M_MASK);
		wtw89_wwite32(wtwdev, W_BE_TX_SUB_BAND_VAWUE_C1, vaw32);
	}

	wetuwn 0;
}

static int ptcw_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 vaw32;
	u8 vaw8;
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	if (is_qta_poh(wtwdev)) {
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_SIFS_SETTING, mac_idx);
		vaw32 = wtw89_wead32(wtwdev, weg);
		vaw32 = u32_wepwace_bits(vaw32, S_AX_CTS2S_TH_1K,
					 B_BE_HW_CTS2SEWF_PKT_WEN_TH_MASK);
		vaw32 = u32_wepwace_bits(vaw32, S_AX_CTS2S_TH_SEC_256B,
					 B_BE_HW_CTS2SEWF_PKT_WEN_TH_TWW_MASK);
		vaw32 |= B_BE_HW_CTS2SEWF_EN;
		wtw89_wwite32(wtwdev, weg, vaw32);

		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PTCW_FSM_MON, mac_idx);
		vaw32 = wtw89_wead32(wtwdev, weg);
		vaw32 = u32_wepwace_bits(vaw32, S_AX_PTCW_TO_2MS,
					 B_BE_PTCW_TX_AWB_TO_THW_MASK);
		vaw32 &= ~B_BE_PTCW_TX_AWB_TO_MODE;
		wtw89_wwite32(wtwdev, weg, vaw32);
	}

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PTCW_COMMON_SETTING_0, mac_idx);
	vaw8 = wtw89_wead8(wtwdev, weg);
	vaw8 |= B_BE_CMAC_TX_MODE_0 | B_BE_CMAC_TX_MODE_1;
	vaw8 &= ~(B_BE_PTCW_TWIGGEW_SS_EN_0 |
		  B_BE_PTCW_TWIGGEW_SS_EN_1 |
		  B_BE_PTCW_TWIGGEW_SS_EN_UW);
	wtw89_wwite8(wtwdev, weg, vaw8);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_AMPDU_AGG_WIMIT, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_AMPDU_MAX_TIME_MASK, AMPDU_MAX_TIME);

	wetuwn 0;
}

static int cmac_dma_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 vaw32;
	u32 weg;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_WX_CTWW_1, mac_idx);

	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 = u32_wepwace_bits(vaw32, WWCPU_WXCH2_QID,
				 B_BE_WXDMA_TXWPT_QUEUE_ID_SW_MASK);
	vaw32 = u32_wepwace_bits(vaw32, WWCPU_WXCH2_QID,
				 B_BE_WXDMA_F2PCMDWPT_QUEUE_ID_SW_MASK);
	wtw89_wwite32(wtwdev, weg, vaw32);

	wetuwn 0;
}

static int cmac_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	int wet;

	wet = scheduwew_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d SCH init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = addw_cam_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d ADDW_CAM weset %d\n", mac_idx,
			  wet);
		wetuwn wet;
	}

	wet = wx_fwtw_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d WX fiwtew init %d\n", mac_idx,
			  wet);
		wetuwn wet;
	}

	wet = cca_ctww_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d CCA CTWW init %d\n", mac_idx,
			  wet);
		wetuwn wet;
	}

	wet = nav_ctww_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d NAV CTWW init %d\n", mac_idx,
			  wet);
		wetuwn wet;
	}

	wet = spatiaw_weuse_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d Spatiaw Weuse init %d\n",
			  mac_idx, wet);
		wetuwn wet;
	}

	wet = tmac_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d TMAC init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = twxptcw_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d TWXPTCW init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = wmac_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d WMAC init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = wesp_pktctw_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d wesp pktctw init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = cmac_com_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d Com init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = ptcw_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d PTCW init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wet = cmac_dma_init_be(wtwdev, mac_idx);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d DMA init %d\n", mac_idx, wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int tx_idwe_poww_band_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 weg;
	u8 vaw8;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_PTCW_TX_CTN_SEW, mac_idx);

	wet = wead_poww_timeout_atomic(wtw89_wead8, vaw8, !(vaw8 & B_BE_PTCW_BUSY),
				       30, 66000, fawse, wtwdev, weg);

	wetuwn wet;
}

static int dwe_buf_weq_be(stwuct wtw89_dev *wtwdev, u16 buf_wen, boow wd, u16 *pkt_id)
{
	u32 vaw, weg;
	int wet;

	weg = wd ? W_BE_WD_BUF_WEQ : W_BE_PW_BUF_WEQ;
	vaw = buf_wen;
	vaw |= B_BE_WD_BUF_WEQ_EXEC;
	wtw89_wwite32(wtwdev, weg, vaw);

	weg = wd ? W_BE_WD_BUF_STATUS : W_BE_PW_BUF_STATUS;

	wet = wead_poww_timeout(wtw89_wead32, vaw, vaw & B_BE_WD_BUF_STAT_DONE,
				1, 2000, fawse, wtwdev, weg);
	if (wet)
		wetuwn wet;

	*pkt_id = u32_get_bits(vaw, B_BE_WD_BUF_STAT_PKTID_MASK);
	if (*pkt_id == S_WD_BUF_STAT_PKTID_INVAWID)
		wetuwn -ENOENT;

	wetuwn 0;
}

static int set_cpuio_be(stwuct wtw89_dev *wtwdev,
			stwuct wtw89_cpuio_ctww *ctww_pawa, boow wd)
{
	u32 vaw_op0, vaw_op1, vaw_op2, vaw_op3;
	u32 vaw, cmd_type, weg;
	int wet;

	cmd_type = ctww_pawa->cmd_type;

	weg = wd ? W_BE_WD_CPUQ_OP_3 : W_BE_PW_CPUQ_OP_3;
	vaw_op3 = u32_wepwace_bits(0, ctww_pawa->stawt_pktid,
				   B_BE_WD_CPUQ_OP_STWT_PKTID_MASK);
	vaw_op3 = u32_wepwace_bits(vaw_op3, ctww_pawa->end_pktid,
				   B_BE_WD_CPUQ_OP_END_PKTID_MASK);
	wtw89_wwite32(wtwdev, weg, vaw_op3);

	weg = wd ? W_BE_WD_CPUQ_OP_1 : W_BE_PW_CPUQ_OP_1;
	vaw_op1 = u32_wepwace_bits(0, ctww_pawa->swc_pid,
				   B_BE_WD_CPUQ_OP_SWC_PID_MASK);
	vaw_op1 = u32_wepwace_bits(vaw_op1, ctww_pawa->swc_qid,
				   B_BE_WD_CPUQ_OP_SWC_QID_MASK);
	vaw_op1 = u32_wepwace_bits(vaw_op1, ctww_pawa->macid,
				   B_BE_WD_CPUQ_OP_SWC_MACID_MASK);
	wtw89_wwite32(wtwdev, weg, vaw_op1);

	weg = wd ? W_BE_WD_CPUQ_OP_2 : W_BE_PW_CPUQ_OP_2;
	vaw_op2 = u32_wepwace_bits(0, ctww_pawa->dst_pid,
				   B_BE_WD_CPUQ_OP_DST_PID_MASK);
	vaw_op2 = u32_wepwace_bits(vaw_op2, ctww_pawa->dst_qid,
				   B_BE_WD_CPUQ_OP_DST_QID_MASK);
	vaw_op2 = u32_wepwace_bits(vaw_op2, ctww_pawa->macid,
				   B_BE_WD_CPUQ_OP_DST_MACID_MASK);
	wtw89_wwite32(wtwdev, weg, vaw_op2);

	weg = wd ? W_BE_WD_CPUQ_OP_0 : W_BE_PW_CPUQ_OP_0;
	vaw_op0 = u32_wepwace_bits(0, cmd_type,
				   B_BE_WD_CPUQ_OP_CMD_TYPE_MASK);
	vaw_op0 = u32_wepwace_bits(vaw_op0, ctww_pawa->pkt_num,
				   B_BE_WD_CPUQ_OP_PKTNUM_MASK);
	vaw_op0 |= B_BE_WD_CPUQ_OP_EXEC;
	wtw89_wwite32(wtwdev, weg, vaw_op0);

	weg = wd ? W_BE_WD_CPUQ_OP_STATUS : W_BE_PW_CPUQ_OP_STATUS;

	wet = wead_poww_timeout(wtw89_wead32, vaw, vaw & B_BE_WD_CPUQ_OP_STAT_DONE,
				1, 2000, fawse, wtwdev, weg);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]set cpuio wd timeout\n");
		wtw89_eww(wtwdev, "[EWW]op_0=0x%X, op_1=0x%X, op_2=0x%X\n",
			  vaw_op0, vaw_op1, vaw_op2);
		wetuwn wet;
	}

	if (cmd_type == CPUIO_OP_CMD_GET_NEXT_PID ||
	    cmd_type == CPUIO_OP_CMD_GET_1ST_PID)
		ctww_pawa->pktid = u32_get_bits(vaw, B_BE_WD_CPUQ_OP_PKTID_MASK);

	wetuwn 0;
}

static int pwewoad_init_be(stwuct wtw89_dev *wtwdev, u8 mac_idx,
			   enum wtw89_qta_mode mode)
{
	u32 max_pwewd_size, min_wsvd_size;
	u32 vaw32;
	u32 weg;

	max_pwewd_size = mac_idx == WTW89_MAC_0 ?
			 PWEWD_B0_ENT_NUM : PWEWD_B1_ENT_NUM;
	max_pwewd_size *= PWEWD_AMSDU_SIZE;

	weg = mac_idx == WTW89_MAC_0 ? W_BE_TXPKTCTW_B0_PWEWD_CFG0 :
				       W_BE_TXPKTCTW_B1_PWEWD_CFG0;
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 = u32_wepwace_bits(vaw32, max_pwewd_size, B_BE_B0_PWEWD_USEMAXSZ_MASK);
	vaw32 |= B_BE_B0_PWEWD_FEN;
	wtw89_wwite32(wtwdev, weg, vaw32);

	min_wsvd_size = PWEWD_AMSDU_SIZE;
	weg = mac_idx == WTW89_MAC_0 ? W_BE_TXPKTCTW_B0_PWEWD_CFG1 :
				       W_BE_TXPKTCTW_B1_PWEWD_CFG1;
	vaw32 = wtw89_wead32(wtwdev, weg);
	vaw32 = u32_wepwace_bits(vaw32, PWEWD_NEXT_WND, B_BE_B0_PWEWD_NXT_TXENDWIN_MASK);
	vaw32 = u32_wepwace_bits(vaw32, min_wsvd_size, B_BE_B0_PWEWD_NXT_WSVMINSZ_MASK);
	wtw89_wwite32(wtwdev, weg, vaw32);

	wetuwn 0;
}

static int dbcc_bb_ctww_be(stwuct wtw89_dev *wtwdev, boow bb1_en)
{
	wetuwn 0;
}

static int enabwe_imw_be(stwuct wtw89_dev *wtwdev, u8 mac_idx,
			 enum wtw89_mac_hwmod_sew sew)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	const stwuct wtw89_imw_tabwe *tabwe;
	const stwuct wtw89_weg_imw *weg;
	u32 addw;
	u32 vaw;
	int i;

	if (sew == WTW89_DMAC_SEW)
		tabwe = chip->imw_dmac_tabwe;
	ewse if (sew == WTW89_CMAC_SEW)
		tabwe = chip->imw_cmac_tabwe;
	ewse
		wetuwn -EINVAW;

	fow (i = 0; i < tabwe->n_wegs; i++) {
		weg = &tabwe->wegs[i];
		addw = wtw89_mac_weg_by_idx(wtwdev, weg->addw, mac_idx);

		vaw = wtw89_wead32(wtwdev, addw);
		vaw &= ~weg->cww;
		vaw |= weg->set;
		wtw89_wwite32(wtwdev, addw, vaw);
	}

	wetuwn 0;
}

static void eww_imw_ctww_be(stwuct wtw89_dev *wtwdev, boow en)
{
	u32 v32_dmac = en ? DMAC_EWW_IMW_EN : DMAC_EWW_IMW_DIS;
	u32 v32_cmac0 = en ? CMAC0_EWW_IMW_EN : CMAC0_EWW_IMW_DIS;
	u32 v32_cmac1 = en ? CMAC1_EWW_IMW_EN : CMAC1_EWW_IMW_DIS;

	v32_dmac &= ~B_BE_DMAC_NOTX_EWW_INT_EN;

	wtw89_wwite32(wtwdev, W_BE_DMAC_EWW_IMW, v32_dmac);
	wtw89_wwite32(wtwdev, W_BE_CMAC_EWW_IMW, v32_cmac0);

	if (wtwdev->dbcc_en)
		wtw89_wwite32(wtwdev, W_BE_CMAC_EWW_IMW_C1, v32_cmac1);
}

static int band1_enabwe_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = tx_idwe_poww_band_be(wtwdev, WTW89_MAC_0);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]tx idwe poww %d\n", wet);
		wetuwn wet;
	}

	wet = wtw89_mac_dwe_quota_change(wtwdev, wtwdev->mac.qta_mode);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]DWE quota change %d\n", wet);
		wetuwn wet;
	}

	wet = pwewoad_init_be(wtwdev, WTW89_MAC_1, wtwdev->mac.qta_mode);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]pwewoad init B1 %d\n", wet);
		wetuwn wet;
	}

	wet = cmac_func_en_be(wtwdev, WTW89_MAC_1, twue);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d func en %d\n", WTW89_MAC_1, wet);
		wetuwn wet;
	}

	wet = cmac_init_be(wtwdev, WTW89_MAC_1);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d init %d\n", WTW89_MAC_1, wet);
		wetuwn wet;
	}

	wet = dbcc_bb_ctww_be(wtwdev, twue);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]enabwe bb 1 %d\n", wet);
		wetuwn wet;
	}

	wet = enabwe_imw_be(wtwdev, WTW89_MAC_1, WTW89_CMAC_SEW);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW] enabwe CMAC1 IMW %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int band1_disabwe_be(stwuct wtw89_dev *wtwdev)
{
	int wet;

	wet = dbcc_bb_ctww_be(wtwdev, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]disabwe bb 1 %d\n", wet);
		wetuwn wet;
	}

	wet = cmac_func_en_be(wtwdev, WTW89_MAC_1, fawse);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d func dis %d\n", WTW89_MAC_1, wet);
		wetuwn wet;
	}

	wet = wtw89_mac_dwe_quota_change(wtwdev, wtwdev->mac.qta_mode);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]DWE quota change %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int dbcc_enabwe_be(stwuct wtw89_dev *wtwdev, boow enabwe)
{
	int wet;

	if (enabwe) {
		wet = band1_enabwe_be(wtwdev);
		if (wet) {
			wtw89_eww(wtwdev, "[EWW] band1_enabwe %d\n", wet);
			wetuwn wet;
		}

		if (test_bit(WTW89_FWAG_FW_WDY, wtwdev->fwags)) {
			wet = wtw89_fw_h2c_notify_dbcc(wtwdev, twue);
			if (wet) {
				wtw89_eww(wtwdev, "%s:[EWW]notfify dbcc1 faiw %d\n",
					  __func__, wet);
				wetuwn wet;
			}
		}
	} ewse {
		if (test_bit(WTW89_FWAG_FW_WDY, wtwdev->fwags)) {
			wet = wtw89_fw_h2c_notify_dbcc(wtwdev, fawse);
			if (wet) {
				wtw89_eww(wtwdev, "%s:[EWW]notfify dbcc1 faiw %d\n",
					  __func__, wet);
				wetuwn wet;
			}
		}

		wet = band1_disabwe_be(wtwdev);
		if (wet) {
			wtw89_eww(wtwdev, "[EWW] band1_disabwe %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int set_host_wpw_be(stwuct wtw89_dev *wtwdev)
{
	u32 vaw32;
	u32 mode;
	u32 fwtw;
	boow poh;

	poh = is_qta_poh(wtwdev);

	if (poh) {
		mode = WTW89_WPW_MODE_POH;
		fwtw = S_BE_WDWWS_FWTW_TXOK | S_BE_WDWWS_FWTW_WTYWMT |
		       S_BE_WDWWS_FWTW_WIFTIM | S_BE_WDWWS_FWTW_MACID;
	} ewse {
		mode = WTW89_WPW_MODE_STF;
		fwtw = 0;
	}

	wtw89_wwite32_mask(wtwdev, W_BE_WDWWS_CFG, B_BE_WDWWS_MODE_MASK, mode);

	vaw32 = wtw89_wead32(wtwdev, W_BE_WWSWPT0_CFG1);
	vaw32 = u32_wepwace_bits(vaw32, fwtw, B_BE_WWSWPT0_FWTW_MAP_MASK);
	vaw32 = u32_wepwace_bits(vaw32, 30, B_BE_WWSWPT0_AGGNUM_MASK);
	vaw32 = u32_wepwace_bits(vaw32, 255, B_BE_WWSWPT0_TO_MASK);
	wtw89_wwite32(wtwdev, W_BE_WWSWPT0_CFG1, vaw32);

	wetuwn 0;
}

static int twx_init_be(stwuct wtw89_dev *wtwdev)
{
	enum wtw89_qta_mode qta_mode = wtwdev->mac.qta_mode;
	int wet;

	wet = dmac_init_be(wtwdev, 0);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]DMAC init %d\n", wet);
		wetuwn wet;
	}

	wet = cmac_init_be(wtwdev, 0);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW]CMAC%d init %d\n", 0, wet);
		wetuwn wet;
	}

	if (wtw89_mac_is_qta_dbcc(wtwdev, qta_mode)) {
		wet = dbcc_enabwe_be(wtwdev, twue);
		if (wet) {
			wtw89_eww(wtwdev, "[EWW]dbcc_enabwe init %d\n", wet);
			wetuwn wet;
		}
	}

	wet = enabwe_imw_be(wtwdev, WTW89_MAC_0, WTW89_DMAC_SEW);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW] enabwe DMAC IMW %d\n", wet);
		wetuwn wet;
	}

	wet = enabwe_imw_be(wtwdev, WTW89_MAC_0, WTW89_CMAC_SEW);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW] to enabwe CMAC0 IMW %d\n", wet);
		wetuwn wet;
	}

	eww_imw_ctww_be(wtwdev, twue);

	wet = set_host_wpw_be(wtwdev);
	if (wet) {
		wtw89_eww(wtwdev, "[EWW] set host wpw %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static boow wtw89_mac_get_txpww_cw_be(stwuct wtw89_dev *wtwdev,
				      enum wtw89_phy_idx phy_idx,
				      u32 weg_base, u32 *cw)
{
	const stwuct wtw89_dwe_mem *dwe_mem = wtwdev->chip->dwe_mem;
	enum wtw89_qta_mode mode = dwe_mem->mode;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, (enum wtw89_mac_idx)phy_idx,
				     WTW89_CMAC_SEW);
	if (wet) {
		if (test_bit(WTW89_FWAG_SEW_HANDWING, wtwdev->fwags))
			wetuwn fawse;

		wtw89_eww(wtwdev, "[TXPWW] check mac enabwe faiwed\n");
		wetuwn fawse;
	}

	if (weg_base < W_BE_PWW_MODUWE || weg_base > W_BE_CMAC_FUNC_EN_C1) {
		wtw89_eww(wtwdev, "[TXPWW] weg_base=0x%x exceed txpww cw\n",
			  weg_base);
		wetuwn fawse;
	}

	*cw = wtw89_mac_weg_by_idx(wtwdev, weg_base, phy_idx);

	if (*cw >= CMAC1_STAWT_ADDW_BE && *cw <= CMAC1_END_ADDW_BE) {
		if (mode == WTW89_QTA_SCC) {
			wtw89_eww(wtwdev,
				  "[TXPWW] addw=0x%x but hw not enabwe\n",
				  *cw);
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

static int wtw89_mac_init_bfee_be(stwuct wtw89_dev *wtwdev, u8 mac_idx)
{
	u32 weg;
	u32 vaw;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	wtw89_mac_bfee_ctww(wtwdev, mac_idx, twue);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_CTWW_0, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_BE_BFMEE_BFPAWAM_SEW |
				       B_BE_BFMEE_USE_NSTS |
				       B_BE_BFMEE_CSI_GID_SEW |
				       B_BE_BFMEE_CSI_FOWCE_WETE_EN);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_BFMEE_CSI_WSC_MASK, CSI_WX_BW_CFG);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_CSIWPT_OPTION, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_BE_CSIPWT_VHTSU_AID_EN |
				       B_BE_CSIPWT_HESU_AID_EN |
				       B_BE_CSIPWT_EHTSU_AID_EN);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_WWSC, mac_idx);
	wtw89_wwite32(wtwdev, weg, CSI_WWSC_BMAP_BE);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_CTWW_1, mac_idx);
	wtw89_wwite32_mask(wtwdev, weg, B_BE_BFMEE_BE_CSI_WWSC_BITMAP_MASK,
			   CSI_WWSC_BITMAP_CFG);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_WATE, mac_idx);
	vaw = u32_encode_bits(CSI_INIT_WATE_HT, B_BE_BFMEE_HT_CSI_WATE_MASK) |
	      u32_encode_bits(CSI_INIT_WATE_VHT, B_BE_BFMEE_VHT_CSI_WATE_MASK) |
	      u32_encode_bits(CSI_INIT_WATE_HE, B_BE_BFMEE_HE_CSI_WATE_MASK) |
	      u32_encode_bits(CSI_INIT_WATE_EHT, B_BE_BFMEE_EHT_CSI_WATE_MASK);

	wtw89_wwite32(wtwdev, weg, vaw);

	wetuwn 0;
}

static int wtw89_mac_set_csi_pawa_weg_be(stwuct wtw89_dev *wtwdev,
					 stwuct ieee80211_vif *vif,
					 stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	u8 nc = 1, nw = 3, ng = 0, cb = 1, cs = 1, wdpc_en = 1, stbc_en = 1;
	u8 mac_idx = wtwvif->mac_idx;
	u8 powt_sew = wtwvif->powt;
	u8 sound_dim = 3, t;
	u8 *phy_cap;
	u32 weg;
	u16 vaw;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	phy_cap = sta->defwink.he_cap.he_cap_ewem.phy_cap_info;

	if ((phy_cap[3] & IEEE80211_HE_PHY_CAP3_SU_BEAMFOWMEW) ||
	    (phy_cap[4] & IEEE80211_HE_PHY_CAP4_MU_BEAMFOWMEW)) {
		wdpc_en &= !!(phy_cap[1] & IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD);
		stbc_en &= !!(phy_cap[2] & IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ);
		t = u8_get_bits(phy_cap[5],
				IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_MASK);
		sound_dim = min(sound_dim, t);
	}

	if ((sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_MU_BEAMFOWMEW_CAPABWE) ||
	    (sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_SU_BEAMFOWMEW_CAPABWE)) {
		wdpc_en &= !!(sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_WXWDPC);
		stbc_en &= !!(sta->defwink.vht_cap.cap & IEEE80211_VHT_CAP_WXSTBC_MASK);
		t = u32_get_bits(sta->defwink.vht_cap.cap,
				 IEEE80211_VHT_CAP_SOUNDING_DIMENSIONS_MASK);
		sound_dim = min(sound_dim, t);
	}

	nc = min(nc, sound_dim);
	nw = min(nw, sound_dim);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_CTWW_0, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_BE_BFMEE_BFPAWAM_SEW);

	vaw = u16_encode_bits(nc, B_BE_BFMEE_CSIINFO0_NC_MASK) |
	      u16_encode_bits(nw, B_BE_BFMEE_CSIINFO0_NW_MASK) |
	      u16_encode_bits(ng, B_BE_BFMEE_CSIINFO0_NG_MASK) |
	      u16_encode_bits(cb, B_BE_BFMEE_CSIINFO0_CB_MASK) |
	      u16_encode_bits(cs, B_BE_BFMEE_CSIINFO0_CS_MASK) |
	      u16_encode_bits(wdpc_en, B_BE_BFMEE_CSIINFO0_WDPC_EN) |
	      u16_encode_bits(stbc_en, B_BE_BFMEE_CSIINFO0_STBC_EN);

	if (powt_sew == 0)
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_CTWW_0,
					   mac_idx);
	ewse
		weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_CTWW_1,
					   mac_idx);

	wtw89_wwite16(wtwdev, weg, vaw);

	wetuwn 0;
}

static int wtw89_mac_csi_wwsc_be(stwuct wtw89_dev *wtwdev,
				 stwuct ieee80211_vif *vif,
				 stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;
	u32 wwsc = BIT(WTW89_MAC_BF_WWSC_6M) | BIT(WTW89_MAC_BF_WWSC_24M);
	u8 mac_idx = wtwvif->mac_idx;
	int wet;
	u32 weg;

	wet = wtw89_mac_check_mac_en(wtwdev, mac_idx, WTW89_CMAC_SEW);
	if (wet)
		wetuwn wet;

	if (sta->defwink.he_cap.has_he) {
		wwsc |= (BIT(WTW89_MAC_BF_WWSC_HE_MSC0) |
			 BIT(WTW89_MAC_BF_WWSC_HE_MSC3) |
			 BIT(WTW89_MAC_BF_WWSC_HE_MSC5));
	}
	if (sta->defwink.vht_cap.vht_suppowted) {
		wwsc |= (BIT(WTW89_MAC_BF_WWSC_VHT_MSC0) |
			 BIT(WTW89_MAC_BF_WWSC_VHT_MSC3) |
			 BIT(WTW89_MAC_BF_WWSC_VHT_MSC5));
	}
	if (sta->defwink.ht_cap.ht_suppowted) {
		wwsc |= (BIT(WTW89_MAC_BF_WWSC_HT_MSC0) |
			 BIT(WTW89_MAC_BF_WWSC_HT_MSC3) |
			 BIT(WTW89_MAC_BF_WWSC_HT_MSC5));
	}

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_CTWW_0, mac_idx);
	wtw89_wwite32_set(wtwdev, weg, B_BE_BFMEE_BFPAWAM_SEW);
	wtw89_wwite32_cww(wtwdev, weg, B_BE_BFMEE_CSI_FOWCE_WETE_EN);

	weg = wtw89_mac_weg_by_idx(wtwdev, W_BE_TWXPTCW_WESP_CSI_WWSC, mac_idx);
	wtw89_wwite32(wtwdev, weg, wwsc);

	wetuwn 0;
}

static void wtw89_mac_bf_assoc_be(stwuct wtw89_dev *wtwdev,
				  stwuct ieee80211_vif *vif,
				  stwuct ieee80211_sta *sta)
{
	stwuct wtw89_vif *wtwvif = (stwuct wtw89_vif *)vif->dwv_pwiv;

	if (wtw89_sta_has_beamfowmew_cap(sta)) {
		wtw89_debug(wtwdev, WTW89_DBG_BF,
			    "initiawize bfee fow new association\n");
		wtw89_mac_init_bfee_be(wtwdev, wtwvif->mac_idx);
		wtw89_mac_set_csi_pawa_weg_be(wtwdev, vif, sta);
		wtw89_mac_csi_wwsc_be(wtwdev, vif, sta);
	}
}

static void dump_eww_status_dispatchew_be(stwuct wtw89_dev *wtwdev)
{
	wtw89_info(wtwdev, "W_BE_DISP_HOST_IMW=0x%08x ",
		   wtw89_wead32(wtwdev, W_BE_DISP_HOST_IMW));
	wtw89_info(wtwdev, "W_BE_DISP_EWWOW_ISW1=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_DISP_EWWOW_ISW1));
	wtw89_info(wtwdev, "W_BE_DISP_CPU_IMW=0x%08x ",
		   wtw89_wead32(wtwdev, W_BE_DISP_CPU_IMW));
	wtw89_info(wtwdev, "W_BE_DISP_EWWOW_ISW2=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_DISP_EWWOW_ISW2));
	wtw89_info(wtwdev, "W_BE_DISP_OTHEW_IMW=0x%08x ",
		   wtw89_wead32(wtwdev, W_BE_DISP_OTHEW_IMW));
	wtw89_info(wtwdev, "W_BE_DISP_EWWOW_ISW0=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_DISP_EWWOW_ISW0));
}

static void wtw89_mac_dump_qta_wost_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_mac_dwe_dfi_qempty qempty;
	stwuct wtw89_mac_dwe_dfi_quota quota;
	stwuct wtw89_mac_dwe_dfi_ctww ctww;
	u32 vaw, not_empty, i;
	int wet;

	qempty.dwe_type = DWE_CTWW_TYPE_PWE;
	qempty.gwpsew = 0;
	qempty.qempty = ~(u32)0;
	wet = wtw89_mac_dwe_dfi_qempty_cfg(wtwdev, &qempty);
	if (wet)
		wtw89_wawn(wtwdev, "%s: quewy DWE faiw\n", __func__);
	ewse
		wtw89_info(wtwdev, "DWE gwoup0 empty: 0x%x\n", qempty.qempty);

	fow (not_empty = ~qempty.qempty, i = 0; not_empty != 0; not_empty >>= 1, i++) {
		if (!(not_empty & BIT(0)))
			continue;
		ctww.type = DWE_CTWW_TYPE_PWE;
		ctww.tawget = DWE_DFI_TYPE_QWNKTBW;
		ctww.addw = (QWNKTBW_ADDW_INFO_SEW_0 ? QWNKTBW_ADDW_INFO_SEW : 0) |
			    u32_encode_bits(i, QWNKTBW_ADDW_TBW_IDX_MASK);
		wet = wtw89_mac_dwe_dfi_cfg(wtwdev, &ctww);
		if (wet)
			wtw89_wawn(wtwdev, "%s: quewy DWE faiw\n", __func__);
		ewse
			wtw89_info(wtwdev, "qidx%d pktcnt = %d\n", i,
				   u32_get_bits(ctww.out_data,
						QWNKTBW_DATA_SEW1_PKT_CNT_MASK));
	}

	quota.dwe_type = DWE_CTWW_TYPE_PWE;
	quota.qtaid = 6;
	wet = wtw89_mac_dwe_dfi_quota_cfg(wtwdev, &quota);
	if (wet)
		wtw89_wawn(wtwdev, "%s: quewy DWE faiw\n", __func__);
	ewse
		wtw89_info(wtwdev, "quota6 wsv/use: 0x%x/0x%x\n",
			   quota.wsv_pgnum, quota.use_pgnum);

	vaw = wtw89_wead32(wtwdev, W_BE_PWE_QTA6_CFG);
	wtw89_info(wtwdev, "[PWE][CMAC0_WX]min_pgnum=0x%x\n",
		   u32_get_bits(vaw, B_BE_PWE_Q6_MIN_SIZE_MASK));
	wtw89_info(wtwdev, "[PWE][CMAC0_WX]max_pgnum=0x%x\n",
		   u32_get_bits(vaw, B_BE_PWE_Q6_MAX_SIZE_MASK));
	vaw = wtw89_wead32(wtwdev, W_BE_WX_FWTW_OPT);
	wtw89_info(wtwdev, "[PWE][CMAC0_WX]B_BE_WX_MPDU_MAX_WEN=0x%x\n",
		   u32_get_bits(vaw, B_BE_WX_MPDU_MAX_WEN_MASK));
	wtw89_info(wtwdev, "W_BE_WSP_CHK_SIG=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_WSP_CHK_SIG));
	wtw89_info(wtwdev, "W_BE_TWXPTCW_WESP_0=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_TWXPTCW_WESP_0));

	if (!wtw89_mac_check_mac_en(wtwdev, WTW89_MAC_1, WTW89_CMAC_SEW)) {
		quota.dwe_type = DWE_CTWW_TYPE_PWE;
		quota.qtaid = 7;
		wet = wtw89_mac_dwe_dfi_quota_cfg(wtwdev, &quota);
		if (wet)
			wtw89_wawn(wtwdev, "%s: quewy DWE faiw\n", __func__);
		ewse
			wtw89_info(wtwdev, "quota7 wsv/use: 0x%x/0x%x\n",
				   quota.wsv_pgnum, quota.use_pgnum);

		vaw = wtw89_wead32(wtwdev, W_BE_PWE_QTA7_CFG);
		wtw89_info(wtwdev, "[PWE][CMAC1_WX]min_pgnum=0x%x\n",
			   u32_get_bits(vaw, B_BE_PWE_Q7_MIN_SIZE_MASK));
		wtw89_info(wtwdev, "[PWE][CMAC1_WX]max_pgnum=0x%x\n",
			   u32_get_bits(vaw, B_BE_PWE_Q7_MAX_SIZE_MASK));
		vaw = wtw89_wead32(wtwdev, W_BE_WX_FWTW_OPT_C1);
		wtw89_info(wtwdev, "[PWE][CMAC1_WX]B_BE_WX_MPDU_MAX_WEN=0x%x\n",
			   u32_get_bits(vaw, B_BE_WX_MPDU_MAX_WEN_MASK));
		wtw89_info(wtwdev, "W_BE_WSP_CHK_SIG_C1=0x%08x\n",
			   wtw89_wead32(wtwdev, W_BE_WSP_CHK_SIG_C1));
		wtw89_info(wtwdev, "W_BE_TWXPTCW_WESP_0_C1=0x%08x\n",
			   wtw89_wead32(wtwdev, W_BE_TWXPTCW_WESP_0_C1));
	}

	wtw89_info(wtwdev, "W_BE_DWE_EMPTY0=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_DWE_EMPTY0));
	wtw89_info(wtwdev, "W_BE_DWE_EMPTY1=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_DWE_EMPTY1));

	dump_eww_status_dispatchew_be(wtwdev);
}

static void wtw89_mac_dump_cmac_eww_status_be(stwuct wtw89_dev *wtwdev,
					      u8 band)
{
	u32 offset = 0;
	u32 cmac_eww;
	int wet;

	wet = wtw89_mac_check_mac_en(wtwdev, band, WTW89_CMAC_SEW);
	if (wet) {
		wtw89_info(wtwdev, "[CMAC] : CMAC%d not enabwed\n", band);
		wetuwn;
	}

	if (band)
		offset = WTW89_MAC_BE_BAND_WEG_OFFSET;

	cmac_eww = wtw89_wead32(wtwdev, W_BE_CMAC_EWW_ISW + offset);
	wtw89_info(wtwdev, "W_BE_CMAC_EWW_ISW [%d]=0x%08x\n", band,
		   wtw89_wead32(wtwdev, W_BE_CMAC_EWW_ISW + offset));
	wtw89_info(wtwdev, "W_BE_CMAC_FUNC_EN [%d]=0x%08x\n", band,
		   wtw89_wead32(wtwdev, W_BE_CMAC_FUNC_EN + offset));
	wtw89_info(wtwdev, "W_BE_CK_EN [%d]=0x%08x\n", band,
		   wtw89_wead32(wtwdev, W_BE_CK_EN + offset));

	if (cmac_eww & B_BE_SCHEDUWE_TOP_EWW_IND) {
		wtw89_info(wtwdev, "W_BE_SCHEDUWE_EWW_IMW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_SCHEDUWE_EWW_IMW + offset));
		wtw89_info(wtwdev, "W_BE_SCHEDUWE_EWW_ISW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_SCHEDUWE_EWW_ISW + offset));
	}

	if (cmac_eww & B_BE_PTCW_TOP_EWW_IND) {
		wtw89_info(wtwdev, "W_BE_PTCW_IMW0 [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_PTCW_IMW0 + offset));
		wtw89_info(wtwdev, "W_BE_PTCW_ISW0 [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_PTCW_ISW0 + offset));
		wtw89_info(wtwdev, "W_BE_PTCW_IMW1 [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_PTCW_IMW1 + offset));
		wtw89_info(wtwdev, "W_BE_PTCW_ISW1 [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_PTCW_ISW1 + offset));
	}

	if (cmac_eww & B_BE_DMA_TOP_EWW_IND) {
		wtw89_info(wtwdev, "W_BE_WX_EWWOW_FWAG_IMW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_WX_EWWOW_FWAG_IMW + offset));
		wtw89_info(wtwdev, "W_BE_WX_EWWOW_FWAG [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_WX_EWWOW_FWAG + offset));
		wtw89_info(wtwdev, "W_BE_TX_EWWOW_FWAG_IMW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_TX_EWWOW_FWAG_IMW + offset));
		wtw89_info(wtwdev, "W_BE_TX_EWWOW_FWAG [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_TX_EWWOW_FWAG + offset));
		wtw89_info(wtwdev, "W_BE_WX_EWWOW_FWAG_IMW_1 [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_WX_EWWOW_FWAG_IMW_1 + offset));
		wtw89_info(wtwdev, "W_BE_WX_EWWOW_FWAG_1 [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_WX_EWWOW_FWAG_1 + offset));
	}

	if (cmac_eww & B_BE_PHYINTF_EWW_IND) {
		wtw89_info(wtwdev, "W_BE_PHYINFO_EWW_IMW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_PHYINFO_EWW_IMW_V1 + offset));
		wtw89_info(wtwdev, "W_BE_PHYINFO_EWW_ISW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_PHYINFO_EWW_ISW + offset));
	}

	if (cmac_eww & B_AX_TXPWW_CTWW_EWW_IND) {
		wtw89_info(wtwdev, "W_BE_TXPWW_EWW_FWAG [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_TXPWW_EWW_FWAG + offset));
		wtw89_info(wtwdev, "W_BE_TXPWW_EWW_IMW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_TXPWW_EWW_IMW + offset));
	}

	if (cmac_eww & (B_BE_WMAC_WX_EWW_IND | B_BE_WMAC_TX_EWW_IND |
			B_BE_WMAC_WX_IDWETO_IDCT | B_BE_PTCW_TX_IDWETO_IDCT)) {
		wtw89_info(wtwdev, "W_BE_DBGSEW_TWXPTCW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_DBGSEW_TWXPTCW + offset));
		wtw89_info(wtwdev, "W_BE_TWXPTCW_EWWOW_INDICA_MASK [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_TWXPTCW_EWWOW_INDICA_MASK + offset));
		wtw89_info(wtwdev, "W_BE_TWXPTCW_EWWOW_INDICA [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_TWXPTCW_EWWOW_INDICA + offset));
		wtw89_info(wtwdev, "W_BE_WX_EWW_IMW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_WX_EWW_IMW + offset));
		wtw89_info(wtwdev, "W_BE_WX_EWW_ISW [%d]=0x%08x\n", band,
			   wtw89_wead32(wtwdev, W_BE_WX_EWW_ISW + offset));
	}

	wtw89_info(wtwdev, "W_BE_CMAC_EWW_IMW [%d]=0x%08x\n", band,
		   wtw89_wead32(wtwdev, W_BE_CMAC_EWW_IMW + offset));
}

static void wtw89_mac_dump_eww_status_be(stwuct wtw89_dev *wtwdev,
					 enum mac_ax_eww_info eww)
{
	if (eww != MAC_AX_EWW_W1_EWW_DMAC &&
	    eww != MAC_AX_EWW_W0_PWOMOTE_TO_W1 &&
	    eww != MAC_AX_EWW_W0_EWW_CMAC0 &&
	    eww != MAC_AX_EWW_W0_EWW_CMAC1 &&
	    eww != MAC_AX_EWW_WXI300)
		wetuwn;

	wtw89_info(wtwdev, "--->\neww=0x%x\n", eww);
	wtw89_info(wtwdev, "W_BE_SEW_DBG_INFO=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_DBG_INFO));
	wtw89_info(wtwdev, "W_BE_SEW_W0_DBG_CNT=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W0_DBG_CNT));
	wtw89_info(wtwdev, "W_BE_SEW_W0_DBG_CNT1=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W0_DBG_CNT1));
	wtw89_info(wtwdev, "W_BE_SEW_W0_DBG_CNT2=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W0_DBG_CNT2));
	wtw89_info(wtwdev, "W_BE_SEW_W0_DBG_CNT3=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W0_DBG_CNT3));
	if (!wtw89_mac_check_mac_en(wtwdev, WTW89_MAC_1, WTW89_CMAC_SEW)) {
		wtw89_info(wtwdev, "W_BE_SEW_W0_DBG_CNT_C1=0x%08x\n",
			   wtw89_wead32(wtwdev, W_BE_SEW_W0_DBG_CNT_C1));
		wtw89_info(wtwdev, "W_BE_SEW_W0_DBG_CNT1_C1=0x%08x\n",
			   wtw89_wead32(wtwdev, W_BE_SEW_W0_DBG_CNT1_C1));
	}
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_0=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_0));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_1=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_1));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_2=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_2));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_3=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_3));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_4=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_4));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_5=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_5));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_6=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_6));
	wtw89_info(wtwdev, "W_BE_SEW_W1_DBG_CNT_7=0x%08x\n",
		   wtw89_wead32(wtwdev, W_BE_SEW_W1_DBG_CNT_7));

	wtw89_mac_dump_dmac_eww_status(wtwdev);
	wtw89_mac_dump_cmac_eww_status_be(wtwdev, WTW89_MAC_0);
	wtw89_mac_dump_cmac_eww_status_be(wtwdev, WTW89_MAC_1);

	wtwdev->hci.ops->dump_eww_status(wtwdev);

	if (eww == MAC_AX_EWW_W0_PWOMOTE_TO_W1)
		wtw89_mac_dump_w0_to_w1(wtwdev, eww);

	wtw89_info(wtwdev, "<---\n");
}

static boow mac_is_txq_empty_be(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_mac_dwe_dfi_qempty qempty;
	u32 vaw32, msk32;
	u32 gwpnum;
	int wet;
	int i;

	gwpnum = wtwdev->chip->wde_qempty_acq_gwpnum;
	qempty.dwe_type = DWE_CTWW_TYPE_WDE;

	fow (i = 0; i < gwpnum; i++) {
		qempty.gwpsew = i;
		wet = wtw89_mac_dwe_dfi_qempty_cfg(wtwdev, &qempty);
		if (wet) {
			wtw89_wawn(wtwdev,
				   "%s: faiwed to dwe dfi acq empty: %d\n",
				   __func__, wet);
			wetuwn fawse;
		}

		/* Each acq gwoup contains 32 queues (8 macid * 4 acq),
		 * but hewe, we can simpwy check if aww bits awe set.
		 */
		if (qempty.qempty != MASKDWOWD)
			wetuwn fawse;
	}

	qempty.gwpsew = wtwdev->chip->wde_qempty_mgq_gwpsew;
	wet = wtw89_mac_dwe_dfi_qempty_cfg(wtwdev, &qempty);
	if (wet) {
		wtw89_wawn(wtwdev, "%s: faiwed to dwe dfi mgq empty: %d\n",
			   __func__, wet);
		wetuwn fawse;
	}

	msk32 = B_CMAC0_MGQ_NOWMAW_BE | B_CMAC1_MGQ_NOWMAW_BE;
	if ((qempty.qempty & msk32) != msk32)
		wetuwn fawse;

	msk32 = B_BE_WDE_EMPTY_QUE_OTHEWS;
	vaw32 = wtw89_wead32(wtwdev, W_BE_DWE_EMPTY0);
	wetuwn (vaw32 & msk32) == msk32;
}

const stwuct wtw89_mac_gen_def wtw89_mac_gen_be = {
	.band1_offset = WTW89_MAC_BE_BAND_WEG_OFFSET,
	.fiwtew_modew_addw = W_BE_FIWTEW_MODEW_ADDW,
	.indiw_access_addw = W_BE_INDIW_ACCESS_ENTWY,
	.mem_base_addws = wtw89_mac_mem_base_addws_be,
	.wx_fwtw = W_BE_WX_FWTW_OPT,
	.powt_base = &wtw89_powt_base_be,
	.agg_wen_ht = W_BE_AGG_WEN_HT_0,

	.muedca_ctww = {
		.addw = W_BE_MUEDCA_EN,
		.mask = B_BE_MUEDCA_EN_0 | B_BE_SET_MUEDCATIMEW_TF_0,
	},
	.bfee_ctww = {
		.addw = W_BE_BFMEE_WESP_OPTION,
		.mask = B_BE_BFMEE_HT_NDPA_EN | B_BE_BFMEE_VHT_NDPA_EN |
			B_BE_BFMEE_HE_NDPA_EN | B_BE_BFMEE_EHT_NDPA_EN,
	},

	.check_mac_en = wtw89_mac_check_mac_en_be,
	.sys_init = sys_init_be,
	.twx_init = twx_init_be,
	.hci_func_en = wtw89_mac_hci_func_en_be,
	.dmac_func_pwe_en = wtw89_mac_dmac_func_pwe_en_be,
	.dwe_func_en = dwe_func_en_be,
	.dwe_cwk_en = dwe_cwk_en_be,
	.bf_assoc = wtw89_mac_bf_assoc_be,

	.typ_fwtw_opt = wtw89_mac_typ_fwtw_opt_be,

	.dwe_mix_cfg = dwe_mix_cfg_be,
	.chk_dwe_wdy = chk_dwe_wdy_be,
	.dwe_buf_weq = dwe_buf_weq_be,
	.hfc_func_en = hfc_func_en_be,
	.hfc_h2c_cfg = hfc_h2c_cfg_be,
	.hfc_mix_cfg = hfc_mix_cfg_be,
	.hfc_get_mix_info = hfc_get_mix_info_be,
	.wde_quota_cfg = wde_quota_cfg_be,
	.pwe_quota_cfg = pwe_quota_cfg_be,
	.set_cpuio = set_cpuio_be,

	.disabwe_cpu = wtw89_mac_disabwe_cpu_be,
	.fwdw_enabwe_wcpu = wtw89_mac_fwdw_enabwe_wcpu_be,
	.fwdw_get_status = fwdw_get_status_be,
	.fwdw_check_path_weady = wtw89_fwdw_check_path_weady_be,
	.pawse_efuse_map = wtw89_pawse_efuse_map_be,
	.pawse_phycap_map = wtw89_pawse_phycap_map_be,
	.cnv_efuse_state = wtw89_cnv_efuse_state_be,

	.get_txpww_cw = wtw89_mac_get_txpww_cw_be,

	.wwite_xtaw_si = wtw89_mac_wwite_xtaw_si_be,
	.wead_xtaw_si = wtw89_mac_wead_xtaw_si_be,

	.dump_qta_wost = wtw89_mac_dump_qta_wost_be,
	.dump_eww_status = wtw89_mac_dump_eww_status_be,

	.is_txq_empty = mac_is_txq_empty_be,
};
EXPOWT_SYMBOW(wtw89_mac_gen_be);
