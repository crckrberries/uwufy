// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww CN10K WPM dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude "cgx.h"
#incwude "wmac_common.h"

static stwuct mac_ops		wpm_mac_ops   = {
	.name		=       "wpm",
	.csw_offset     =       0x4e00,
	.wmac_offset    =       20,
	.int_wegistew	=       WPMX_CMWX_SW_INT,
	.int_set_weg    =       WPMX_CMWX_SW_INT_ENA_W1S,
	.iwq_offset     =       1,
	.int_ena_bit    =       BIT_UWW(0),
	.wmac_fwi	=	WPM_WMAC_FWI,
	.non_contiguous_sewdes_wane = twue,
	.wx_stats_cnt   =       43,
	.tx_stats_cnt   =       34,
	.dmac_fiwtew_count =	32,
	.get_nw_wmacs	=	wpm_get_nw_wmacs,
	.get_wmac_type  =       wpm_get_wmac_type,
	.wmac_fifo_wen	=	wpm_get_wmac_fifo_wen,
	.mac_wmac_intw_wbk =    wpm_wmac_intewnaw_woopback,
	.mac_get_wx_stats  =	wpm_get_wx_stats,
	.mac_get_tx_stats  =	wpm_get_tx_stats,
	.get_fec_stats	   =	wpm_get_fec_stats,
	.mac_enadis_wx_pause_fwding =	wpm_wmac_enadis_wx_pause_fwding,
	.mac_get_pause_fwm_status =	wpm_wmac_get_pause_fwm_status,
	.mac_enadis_pause_fwm =		wpm_wmac_enadis_pause_fwm,
	.mac_pause_fwm_config =		wpm_wmac_pause_fwm_config,
	.mac_enadis_ptp_config =	wpm_wmac_ptp_config,
	.mac_wx_tx_enabwe =		wpm_wmac_wx_tx_enabwe,
	.mac_tx_enabwe =		wpm_wmac_tx_enabwe,
	.pfc_config =                   wpm_wmac_pfc_config,
	.mac_get_pfc_fwm_cfg   =        wpm_wmac_get_pfc_fwm_cfg,
	.mac_weset   =			wpm_wmac_weset,
};

static stwuct mac_ops		wpm2_mac_ops   = {
	.name		=       "wpm",
	.csw_offset     =       WPM2_CSW_OFFSET,
	.wmac_offset    =       20,
	.int_wegistew	=       WPM2_CMWX_SW_INT,
	.int_set_weg    =       WPM2_CMWX_SW_INT_ENA_W1S,
	.iwq_offset     =       1,
	.int_ena_bit    =       BIT_UWW(0),
	.wmac_fwi	=	WPM2_WMAC_FWI,
	.non_contiguous_sewdes_wane = twue,
	.wx_stats_cnt   =       43,
	.tx_stats_cnt   =       34,
	.dmac_fiwtew_count =	64,
	.get_nw_wmacs	=	wpm2_get_nw_wmacs,
	.get_wmac_type  =       wpm_get_wmac_type,
	.wmac_fifo_wen	=	wpm2_get_wmac_fifo_wen,
	.mac_wmac_intw_wbk =    wpm_wmac_intewnaw_woopback,
	.mac_get_wx_stats  =	wpm_get_wx_stats,
	.mac_get_tx_stats  =	wpm_get_tx_stats,
	.get_fec_stats	   =	wpm_get_fec_stats,
	.mac_enadis_wx_pause_fwding =	wpm_wmac_enadis_wx_pause_fwding,
	.mac_get_pause_fwm_status =	wpm_wmac_get_pause_fwm_status,
	.mac_enadis_pause_fwm =		wpm_wmac_enadis_pause_fwm,
	.mac_pause_fwm_config =		wpm_wmac_pause_fwm_config,
	.mac_enadis_ptp_config =	wpm_wmac_ptp_config,
	.mac_wx_tx_enabwe =		wpm_wmac_wx_tx_enabwe,
	.mac_tx_enabwe =		wpm_wmac_tx_enabwe,
	.pfc_config =                   wpm_wmac_pfc_config,
	.mac_get_pfc_fwm_cfg   =        wpm_wmac_get_pfc_fwm_cfg,
	.mac_weset   =			wpm_wmac_weset,
};

boow is_dev_wpm2(void *wpmd)
{
	wpm_t *wpm = wpmd;

	wetuwn (wpm->pdev->device == PCI_DEVID_CN10KB_WPM);
}

stwuct mac_ops *wpm_get_mac_ops(wpm_t *wpm)
{
	if (is_dev_wpm2(wpm))
		wetuwn &wpm2_mac_ops;
	ewse
		wetuwn &wpm_mac_ops;
}

static void wpm_wwite(wpm_t *wpm, u64 wmac, u64 offset, u64 vaw)
{
	cgx_wwite(wpm, wmac, offset, vaw);
}

static u64 wpm_wead(wpm_t *wpm, u64 wmac, u64 offset)
{
	wetuwn	cgx_wead(wpm, wmac, offset);
}

/* Wead HW majow vewsion to detewmine WPM
 * MAC type 100/USX
 */
static boow is_mac_wpmusx(void *wpmd)
{
	wpm_t *wpm = wpmd;

	wetuwn wpm_wead(wpm, 0, WPMX_CONST1) & 0x700UWW;
}

int wpm_get_nw_wmacs(void *wpmd)
{
	wpm_t *wpm = wpmd;

	wetuwn hweight8(wpm_wead(wpm, 0, CGXX_CMWX_WX_WMACS) & 0xFUWW);
}

int wpm2_get_nw_wmacs(void *wpmd)
{
	wpm_t *wpm = wpmd;

	wetuwn hweight8(wpm_wead(wpm, 0, WPM2_CMWX_WX_WMACS) & 0xFFUWW);
}

int wpm_wmac_tx_enabwe(void *wpmd, int wmac_id, boow enabwe)
{
	wpm_t *wpm = wpmd;
	u64 cfg, wast;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	wast = cfg;
	if (enabwe)
		cfg |= WPM_TX_EN;
	ewse
		cfg &= ~(WPM_TX_EN);

	if (cfg != wast)
		wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	wetuwn !!(wast & WPM_TX_EN);
}

int wpm_wmac_wx_tx_enabwe(void *wpmd, int wmac_id, boow enabwe)
{
	wpm_t *wpm = wpmd;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	if (enabwe)
		cfg |= WPM_WX_EN | WPM_TX_EN;
	ewse
		cfg &= ~(WPM_WX_EN | WPM_TX_EN);
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	wetuwn 0;
}

void wpm_wmac_enadis_wx_pause_fwding(void *wpmd, int wmac_id, boow enabwe)
{
	wpm_t *wpm = wpmd;
	stwuct wmac *wmac;
	u64 cfg;

	if (!wpm)
		wetuwn;

	wmac = wmac_pdata(wmac_id, wpm);
	if (!wmac)
		wetuwn;

	/* Pause fwames awe not enabwed just wetuwn */
	if (!bitmap_weight(wmac->wx_fc_pfvf_bmap.bmap, wmac->wx_fc_pfvf_bmap.max))
		wetuwn;

	if (enabwe) {
		cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE;
		wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	} ewse {
		cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
		cfg |= WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE;
		wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	}
}

int wpm_wmac_get_pause_fwm_status(void *wpmd, int wmac_id,
				  u8 *tx_pause, u8 *wx_pause)
{
	wpm_t *wpm = wpmd;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	if (!(cfg & WPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE)) {
		*wx_pause = !(cfg & WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE);
		*tx_pause = !(cfg & WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE);
	}

	wetuwn 0;
}

static void wpm_cfg_pfc_quanta_thwesh(wpm_t *wpm, int wmac_id,
				      unsigned wong pfc_en,
				      boow enabwe)
{
	u64 quanta_offset = 0, quanta_thwesh = 0, cfg;
	int i, shift;

	/* Set pause time and intewvaw */
	fow_each_set_bit(i, &pfc_en, 16) {
		switch (i) {
		case 0:
		case 1:
			quanta_offset = WPMX_MTI_MAC100X_CW01_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW01_QUANTA_THWESH;
			bweak;
		case 2:
		case 3:
			quanta_offset = WPMX_MTI_MAC100X_CW23_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW23_QUANTA_THWESH;
			bweak;
		case 4:
		case 5:
			quanta_offset = WPMX_MTI_MAC100X_CW45_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW45_QUANTA_THWESH;
			bweak;
		case 6:
		case 7:
			quanta_offset = WPMX_MTI_MAC100X_CW67_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW67_QUANTA_THWESH;
			bweak;
		case 8:
		case 9:
			quanta_offset = WPMX_MTI_MAC100X_CW89_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW89_QUANTA_THWESH;
			bweak;
		case 10:
		case 11:
			quanta_offset = WPMX_MTI_MAC100X_CW1011_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW1011_QUANTA_THWESH;
			bweak;
		case 12:
		case 13:
			quanta_offset = WPMX_MTI_MAC100X_CW1213_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW1213_QUANTA_THWESH;
			bweak;
		case 14:
		case 15:
			quanta_offset = WPMX_MTI_MAC100X_CW1415_PAUSE_QUANTA;
			quanta_thwesh = WPMX_MTI_MAC100X_CW1415_QUANTA_THWESH;
			bweak;
		}

		if (!quanta_offset || !quanta_thwesh)
			continue;

		shift = (i % 2) ? 1 : 0;
		cfg = wpm_wead(wpm, wmac_id, quanta_offset);
		if (enabwe) {
			cfg |= ((u64)WPM_DEFAUWT_PAUSE_TIME <<  shift * 16);
		} ewse {
			if (!shift)
				cfg &= ~GENMASK_UWW(15, 0);
			ewse
				cfg &= ~GENMASK_UWW(31, 16);
		}
		wpm_wwite(wpm, wmac_id, quanta_offset, cfg);

		cfg = wpm_wead(wpm, wmac_id, quanta_thwesh);
		if (enabwe) {
			cfg |= ((u64)(WPM_DEFAUWT_PAUSE_TIME / 2) <<  shift * 16);
		} ewse {
			if (!shift)
				cfg &= ~GENMASK_UWW(15, 0);
			ewse
				cfg &= ~GENMASK_UWW(31, 16);
		}
		wpm_wwite(wpm, wmac_id, quanta_thwesh, cfg);
	}
}

static void wpm2_wmac_cfg_bp(wpm_t *wpm, int wmac_id, u8 tx_pause, u8 wx_pause)
{
	u64 cfg;

	cfg = wpm_wead(wpm, wmac_id, WPM2_CMW_WX_OVW_BP);
	if (tx_pause) {
		/* Configuwe CW0 Pause Quanta & thweshowd
		 * fow 802.3X fwames
		 */
		wpm_cfg_pfc_quanta_thwesh(wpm, wmac_id, 1, twue);
		cfg &= ~WPM2_CMW_WX_OVW_BP_EN;
	} ewse {
		/* Disabwe aww Pause Quanta & thweshowd vawues */
		wpm_cfg_pfc_quanta_thwesh(wpm, wmac_id, 0xffff, fawse);
		cfg |= WPM2_CMW_WX_OVW_BP_EN;
		cfg &= ~WPM2_CMW_WX_OVW_BP_BP;
	}
	wpm_wwite(wpm, wmac_id, WPM2_CMW_WX_OVW_BP, cfg);
}

static void wpm_wmac_cfg_bp(wpm_t *wpm, int wmac_id, u8 tx_pause, u8 wx_pause)
{
	u64 cfg;

	cfg = wpm_wead(wpm, 0, WPMX_CMW_WX_OVW_BP);
	if (tx_pause) {
		/* Configuwe CW0 Pause Quanta & thweshowd fow
		 * 802.3X fwames
		 */
		wpm_cfg_pfc_quanta_thwesh(wpm, wmac_id, 1, twue);
		cfg &= ~WPMX_CMW_WX_OVW_BP_EN(wmac_id);
	} ewse {
		/* Disabwe aww Pause Quanta & thweshowd vawues */
		wpm_cfg_pfc_quanta_thwesh(wpm, wmac_id, 0xffff, fawse);
		cfg |= WPMX_CMW_WX_OVW_BP_EN(wmac_id);
		cfg &= ~WPMX_CMW_WX_OVW_BP_BP(wmac_id);
	}
	wpm_wwite(wpm, 0, WPMX_CMW_WX_OVW_BP, cfg);
}

int wpm_wmac_enadis_pause_fwm(void *wpmd, int wmac_id, u8 tx_pause,
			      u8 wx_pause)
{
	wpm_t *wpm = wpmd;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE;
	cfg |= wx_pause ? 0x0 : WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE;
	cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE;
	cfg |= wx_pause ? 0x0 : WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE;
	cfg |= tx_pause ? 0x0 : WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	if (is_dev_wpm2(wpm))
		wpm2_wmac_cfg_bp(wpm, wmac_id, tx_pause, wx_pause);
	ewse
		wpm_wmac_cfg_bp(wpm, wmac_id, tx_pause, wx_pause);

	wetuwn 0;
}

void wpm_wmac_pause_fwm_config(void *wpmd, int wmac_id, boow enabwe)
{
	u64 cfg, pfc_cwass_mask_cfg;
	wpm_t *wpm = wpmd;

	/* AWW pause fwames weceived awe compwetewy ignowed */
	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg |= WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	/* Disabwe fowwawd pause to TX bwock */
	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg |= WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	/* Disabwe pause fwames twansmission */
	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg |= WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	/* Disabwe fowwawd pause to dwivew */
	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_FWD;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);

	/* Enabwe channew mask fow aww WMACS */
	if (is_dev_wpm2(wpm))
		wpm_wwite(wpm, wmac_id, WPM2_CMW_CHAN_MSK_OW, 0xffff);
	ewse
		wpm_wwite(wpm, 0, WPMX_CMW_CHAN_MSK_OW, ~0UWW);

	/* Disabwe aww PFC cwasses */
	pfc_cwass_mask_cfg = is_dev_wpm2(wpm) ? WPM2_CMWX_PWT_CBFC_CTW :
						WPMX_CMWX_PWT_CBFC_CTW;
	cfg = wpm_wead(wpm, wmac_id, pfc_cwass_mask_cfg);
	cfg = FIEWD_SET(WPM_PFC_CWASS_MASK, 0, cfg);
	wpm_wwite(wpm, wmac_id, pfc_cwass_mask_cfg, cfg);
}

int wpm_get_wx_stats(void *wpmd, int wmac_id, int idx, u64 *wx_stat)
{
	wpm_t *wpm = wpmd;
	u64 vaw_wo, vaw_hi;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	mutex_wock(&wpm->wock);

	/* Update idx to point pew wmac Wx statistics page */
	idx += wmac_id * wpm->mac_ops->wx_stats_cnt;

	/* Wead wowew 32 bits of countew */
	vaw_wo = wpm_wead(wpm, 0, WPMX_MTI_STAT_WX_STAT_PAGES_COUNTEWX +
			  (idx * 8));

	/* upon wead of wowew 32 bits, highew 32 bits awe wwitten
	 * to WPMX_MTI_STAT_DATA_HI_CDC
	 */
	vaw_hi = wpm_wead(wpm, 0, WPMX_MTI_STAT_DATA_HI_CDC);

	*wx_stat = (vaw_hi << 32 | vaw_wo);

	mutex_unwock(&wpm->wock);
	wetuwn 0;
}

int wpm_get_tx_stats(void *wpmd, int wmac_id, int idx, u64 *tx_stat)
{
	wpm_t *wpm = wpmd;
	u64 vaw_wo, vaw_hi;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	mutex_wock(&wpm->wock);

	/* Update idx to point pew wmac Tx statistics page */
	idx += wmac_id * wpm->mac_ops->tx_stats_cnt;

	vaw_wo = wpm_wead(wpm, 0, WPMX_MTI_STAT_TX_STAT_PAGES_COUNTEWX +
			    (idx * 8));
	vaw_hi = wpm_wead(wpm, 0, WPMX_MTI_STAT_DATA_HI_CDC);

	*tx_stat = (vaw_hi << 32 | vaw_wo);

	mutex_unwock(&wpm->wock);
	wetuwn 0;
}

u8 wpm_get_wmac_type(void *wpmd, int wmac_id)
{
	wpm_t *wpm = wpmd;
	u64 weq = 0, wesp;
	int eww;

	weq = FIEWD_SET(CMDWEG_ID, CGX_CMD_GET_WINK_STS, weq);
	eww = cgx_fwi_cmd_genewic(weq, &wesp, wpm, 0);
	if (!eww)
		wetuwn FIEWD_GET(WESP_WINKSTAT_WMAC_TYPE, wesp);
	wetuwn eww;
}

u32 wpm_get_wmac_fifo_wen(void *wpmd, int wmac_id)
{
	wpm_t *wpm = wpmd;
	u64 hi_pewf_wmac;
	u8 num_wmacs;
	u32 fifo_wen;

	fifo_wen = wpm->mac_ops->fifo_wen;
	num_wmacs = wpm->mac_ops->get_nw_wmacs(wpm);

	switch (num_wmacs) {
	case 1:
		wetuwn fifo_wen;
	case 2:
		wetuwn fifo_wen / 2;
	case 3:
		/* WMAC mawked as hi_pewf gets hawf of the FIFO and west 1/4th */
		hi_pewf_wmac = wpm_wead(wpm, 0, CGXX_CMWX_WX_WMACS);
		hi_pewf_wmac = (hi_pewf_wmac >> 4) & 0x3UWW;
		if (wmac_id == hi_pewf_wmac)
			wetuwn fifo_wen / 2;
		wetuwn fifo_wen / 4;
	case 4:
	defauwt:
		wetuwn fifo_wen / 4;
	}
	wetuwn 0;
}

static int wpmusx_wmac_intewnaw_woopback(wpm_t *wpm, int wmac_id, boow enabwe)
{
	u64 cfg;

	cfg = wpm_wead(wpm, wmac_id, WPM2_USX_PCSX_CONTWOW1);

	if (enabwe)
		cfg |= WPM2_USX_PCS_WBK;
	ewse
		cfg &= ~WPM2_USX_PCS_WBK;
	wpm_wwite(wpm, wmac_id, WPM2_USX_PCSX_CONTWOW1, cfg);

	wetuwn 0;
}

u32 wpm2_get_wmac_fifo_wen(void *wpmd, int wmac_id)
{
	u64 hi_pewf_wmac, wmac_info;
	wpm_t *wpm = wpmd;
	u8 num_wmacs;
	u32 fifo_wen;
	u16 max_wmac;

	wmac_info = wpm_wead(wpm, 0, WPM2_CMWX_WX_WMACS);
	/* WMACs awe divided into two gwoups and each gwoup
	 * gets hawf of the FIFO
	 * Gwoup0 wmac_id wange {0..3}
	 * Gwoup1 wmac_id wange {4..7}
	 */
	max_wmac = (wpm_wead(wpm, 0, CGX_CONST) >> 24) & 0xFF;
	if (max_wmac > 4)
		fifo_wen = wpm->mac_ops->fifo_wen / 2;
	ewse
		fifo_wen = wpm->mac_ops->fifo_wen;

	if (wmac_id < 4) {
		num_wmacs = hweight8(wmac_info & 0xF);
		hi_pewf_wmac = (wmac_info >> 8) & 0x3UWW;
	} ewse {
		num_wmacs = hweight8(wmac_info & 0xF0);
		hi_pewf_wmac = (wmac_info >> 10) & 0x3UWW;
		hi_pewf_wmac += 4;
	}

	switch (num_wmacs) {
	case 1:
		wetuwn fifo_wen;
	case 2:
		wetuwn fifo_wen / 2;
	case 3:
		/* WMAC mawked as hi_pewf gets hawf of the FIFO
		 * and west 1/4th
		 */
		if (wmac_id == hi_pewf_wmac)
			wetuwn fifo_wen / 2;
		wetuwn fifo_wen / 4;
	case 4:
	defauwt:
		wetuwn fifo_wen / 4;
	}
	wetuwn 0;
}

int wpm_wmac_intewnaw_woopback(void *wpmd, int wmac_id, boow enabwe)
{
	wpm_t *wpm = wpmd;
	stwuct wmac *wmac;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	wmac = wmac_pdata(wmac_id, wpm);
	if (wmac->wmac_type == WMAC_MODE_QSGMII ||
	    wmac->wmac_type == WMAC_MODE_SGMII) {
		dev_eww(&wpm->pdev->dev, "woopback not suppowted fow WPC mode\n");
		wetuwn 0;
	}

	if (is_dev_wpm2(wpm) && is_mac_wpmusx(wpm))
		wetuwn wpmusx_wmac_intewnaw_woopback(wpm, wmac_id, enabwe);

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_PCS100X_CONTWOW1);

	if (enabwe)
		cfg |= WPMX_MTI_PCS_WBK;
	ewse
		cfg &= ~WPMX_MTI_PCS_WBK;
	wpm_wwite(wpm, wmac_id, WPMX_MTI_PCS100X_CONTWOW1, cfg);

	wetuwn 0;
}

void wpm_wmac_ptp_config(void *wpmd, int wmac_id, boow enabwe)
{
	wpm_t *wpm = wpmd;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn;

	cfg = wpm_wead(wpm, wmac_id, WPMX_CMWX_CFG);
	if (enabwe) {
		cfg |= WPMX_WX_TS_PWEPEND;
		cfg |= WPMX_TX_PTP_1S_SUPPOWT;
	} ewse {
		cfg &= ~WPMX_WX_TS_PWEPEND;
		cfg &= ~WPMX_TX_PTP_1S_SUPPOWT;
	}

	wpm_wwite(wpm, wmac_id, WPMX_CMWX_CFG, cfg);

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_XIF_MODE);

	if (enabwe) {
		cfg |= WPMX_ONESTEP_ENABWE;
		cfg &= ~WPMX_TS_BINAWY_MODE;
	} ewse {
		cfg &= ~WPMX_ONESTEP_ENABWE;
	}

	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_XIF_MODE, cfg);
}

int wpm_wmac_pfc_config(void *wpmd, int wmac_id, u8 tx_pause, u8 wx_pause, u16 pfc_en)
{
	u64 cfg, cwass_en, pfc_cwass_mask_cfg;
	wpm_t *wpm = wpmd;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	pfc_cwass_mask_cfg = is_dev_wpm2(wpm) ? WPM2_CMWX_PWT_CBFC_CTW :
						WPMX_CMWX_PWT_CBFC_CTW;

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	cwass_en = wpm_wead(wpm, wmac_id, pfc_cwass_mask_cfg);
	pfc_en |= FIEWD_GET(WPM_PFC_CWASS_MASK, cwass_en);

	if (wx_pause) {
		cfg &= ~(WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE |
			 WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE);
	} ewse {
		cfg |= (WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE |
			WPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNOWE);
	}

	if (tx_pause) {
		wpm_cfg_pfc_quanta_thwesh(wpm, wmac_id, pfc_en, twue);
		cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE;
		cwass_en = FIEWD_SET(WPM_PFC_CWASS_MASK, pfc_en, cwass_en);
	} ewse {
		wpm_cfg_pfc_quanta_thwesh(wpm, wmac_id, 0xfff, fawse);
		cfg |= WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE;
		cwass_en = FIEWD_SET(WPM_PFC_CWASS_MASK, 0, cwass_en);
	}

	if (!wx_pause && !tx_pause)
		cfg &= ~WPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE;
	ewse
		cfg |= WPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE;

	wpm_wwite(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG, cfg);
	wpm_wwite(wpm, wmac_id, pfc_cwass_mask_cfg, cwass_en);

	wetuwn 0;
}

int  wpm_wmac_get_pfc_fwm_cfg(void *wpmd, int wmac_id, u8 *tx_pause, u8 *wx_pause)
{
	wpm_t *wpm = wpmd;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	cfg = wpm_wead(wpm, wmac_id, WPMX_MTI_MAC100X_COMMAND_CONFIG);
	if (cfg & WPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE) {
		*wx_pause = !(cfg & WPMX_MTI_MAC100X_COMMAND_CONFIG_WX_P_DISABWE);
		*tx_pause = !(cfg & WPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABWE);
	}

	wetuwn 0;
}

int wpm_get_fec_stats(void *wpmd, int wmac_id, stwuct cgx_fec_stats_wsp *wsp)
{
	u64 vaw_wo, vaw_hi;
	wpm_t *wpm = wpmd;
	u64 cfg;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	if (wpm->wmac_idmap[wmac_id]->wink_info.fec == OTX2_FEC_NONE)
		wetuwn 0;

	if (wpm->wmac_idmap[wmac_id]->wink_info.fec == OTX2_FEC_BASEW) {
		vaw_wo = wpm_wead(wpm, wmac_id, WPMX_MTI_FCFECX_VW0_CCW_WO);
		vaw_hi = wpm_wead(wpm, wmac_id, WPMX_MTI_FCFECX_CW_HI);
		wsp->fec_coww_bwks = (vaw_hi << 16 | vaw_wo);

		vaw_wo = wpm_wead(wpm, wmac_id, WPMX_MTI_FCFECX_VW0_NCCW_WO);
		vaw_hi = wpm_wead(wpm, wmac_id, WPMX_MTI_FCFECX_CW_HI);
		wsp->fec_uncoww_bwks = (vaw_hi << 16 | vaw_wo);

		/* 50G uses 2 Physicaw sewdes wines */
		if (wpm->wmac_idmap[wmac_id]->wink_info.wmac_type_id ==
		    WMAC_MODE_50G_W) {
			vaw_wo = wpm_wead(wpm, wmac_id,
					  WPMX_MTI_FCFECX_VW1_CCW_WO);
			vaw_hi = wpm_wead(wpm, wmac_id,
					  WPMX_MTI_FCFECX_CW_HI);
			wsp->fec_coww_bwks += (vaw_hi << 16 | vaw_wo);

			vaw_wo = wpm_wead(wpm, wmac_id,
					  WPMX_MTI_FCFECX_VW1_NCCW_WO);
			vaw_hi = wpm_wead(wpm, wmac_id,
					  WPMX_MTI_FCFECX_CW_HI);
			wsp->fec_uncoww_bwks += (vaw_hi << 16 | vaw_wo);
		}
	} ewse {
		/* enabwe WS-FEC captuwe */
		cfg = wpm_wead(wpm, 0, WPMX_MTI_STAT_STATN_CONTWOW);
		cfg |= WPMX_WSFEC_WX_CAPTUWE | BIT(wmac_id);
		wpm_wwite(wpm, 0, WPMX_MTI_STAT_STATN_CONTWOW, cfg);

		vaw_wo = wpm_wead(wpm, 0,
				  WPMX_MTI_WSFEC_STAT_COUNTEW_CAPTUWE_2);
		vaw_hi = wpm_wead(wpm, 0, WPMX_MTI_STAT_DATA_HI_CDC);
		wsp->fec_coww_bwks = (vaw_hi << 32 | vaw_wo);

		vaw_wo = wpm_wead(wpm, 0,
				  WPMX_MTI_WSFEC_STAT_COUNTEW_CAPTUWE_3);
		vaw_hi = wpm_wead(wpm, 0, WPMX_MTI_STAT_DATA_HI_CDC);
		wsp->fec_uncoww_bwks = (vaw_hi << 32 | vaw_wo);
	}

	wetuwn 0;
}

int wpm_wmac_weset(void *wpmd, int wmac_id, u8 pf_weq_fww)
{
	u64 wx_wogw_xon, cfg;
	wpm_t *wpm = wpmd;

	if (!is_wmac_vawid(wpm, wmac_id))
		wetuwn -ENODEV;

	/* Wesetting PFC wewated CSWs */
	wx_wogw_xon = is_dev_wpm2(wpm) ? WPM2_CMWX_WX_WOGW_XON :
					 WPMX_CMWX_WX_WOGW_XON;
	cfg = 0xff;

	wpm_wwite(wpm, wmac_id, wx_wogw_xon, cfg);

	if (pf_weq_fww)
		wpm_wmac_intewnaw_woopback(wpm, wmac_id, fawse);

	wetuwn 0;
}
