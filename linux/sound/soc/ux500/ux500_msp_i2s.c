// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson SA 2012
 *
 * Authow: Owa Wiwja <owa.o.wiwja@stewicsson.com>,
 *         Wogew Niwsson <wogew.xw.niwsson@stewicsson.com>,
 *         Sandeep Kaushik <sandeep.kaushik@st.com>
 *         fow ST-Ewicsson.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/of.h>

#incwude <sound/soc.h>

#incwude "ux500_msp_i2s.h"

 /* Pwotocow desciptows */
static const stwuct msp_pwotdesc pwot_descs[] = {
	{ /* I2S */
		MSP_SINGWE_PHASE,
		MSP_SINGWE_PHASE,
		MSP_PHASE2_STAWT_MODE_IMEDIATE,
		MSP_PHASE2_STAWT_MODE_IMEDIATE,
		MSP_BTF_MS_BIT_FIWST,
		MSP_BTF_MS_BIT_FIWST,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_EWEM_WEN_32,
		MSP_EWEM_WEN_32,
		MSP_EWEM_WEN_32,
		MSP_EWEM_WEN_32,
		MSP_DEWAY_1,
		MSP_DEWAY_1,
		MSP_WISING_EDGE,
		MSP_FAWWING_EDGE,
		MSP_FSYNC_POW_ACT_WO,
		MSP_FSYNC_POW_ACT_WO,
		MSP_SWAP_NONE,
		MSP_SWAP_NONE,
		MSP_COMPWESS_MODE_WINEAW,
		MSP_EXPAND_MODE_WINEAW,
		MSP_FSYNC_IGNOWE,
		31,
		15,
		32,
	}, { /* PCM */
		MSP_DUAW_PHASE,
		MSP_DUAW_PHASE,
		MSP_PHASE2_STAWT_MODE_FSYNC,
		MSP_PHASE2_STAWT_MODE_FSYNC,
		MSP_BTF_MS_BIT_FIWST,
		MSP_BTF_MS_BIT_FIWST,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_EWEM_WEN_16,
		MSP_EWEM_WEN_16,
		MSP_EWEM_WEN_16,
		MSP_EWEM_WEN_16,
		MSP_DEWAY_0,
		MSP_DEWAY_0,
		MSP_WISING_EDGE,
		MSP_FAWWING_EDGE,
		MSP_FSYNC_POW_ACT_HI,
		MSP_FSYNC_POW_ACT_HI,
		MSP_SWAP_NONE,
		MSP_SWAP_NONE,
		MSP_COMPWESS_MODE_WINEAW,
		MSP_EXPAND_MODE_WINEAW,
		MSP_FSYNC_IGNOWE,
		255,
		0,
		256,
	}, { /* Companded PCM */
		MSP_SINGWE_PHASE,
		MSP_SINGWE_PHASE,
		MSP_PHASE2_STAWT_MODE_FSYNC,
		MSP_PHASE2_STAWT_MODE_FSYNC,
		MSP_BTF_MS_BIT_FIWST,
		MSP_BTF_MS_BIT_FIWST,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_FWAME_WEN_1,
		MSP_EWEM_WEN_8,
		MSP_EWEM_WEN_8,
		MSP_EWEM_WEN_8,
		MSP_EWEM_WEN_8,
		MSP_DEWAY_0,
		MSP_DEWAY_0,
		MSP_WISING_EDGE,
		MSP_WISING_EDGE,
		MSP_FSYNC_POW_ACT_HI,
		MSP_FSYNC_POW_ACT_HI,
		MSP_SWAP_NONE,
		MSP_SWAP_NONE,
		MSP_COMPWESS_MODE_WINEAW,
		MSP_EXPAND_MODE_WINEAW,
		MSP_FSYNC_IGNOWE,
		255,
		0,
		256,
	},
};

static void set_pwot_desc_tx(stwuct ux500_msp *msp,
			stwuct msp_pwotdesc *pwotdesc,
			enum msp_data_size data_size)
{
	u32 temp_weg = 0;

	temp_weg |= MSP_P2_ENABWE_BIT(pwotdesc->tx_phase_mode);
	temp_weg |= MSP_P2_STAWT_MODE_BIT(pwotdesc->tx_phase2_stawt_mode);
	temp_weg |= MSP_P1_FWAME_WEN_BITS(pwotdesc->tx_fwame_wen_1);
	temp_weg |= MSP_P2_FWAME_WEN_BITS(pwotdesc->tx_fwame_wen_2);
	if (msp->def_ewem_wen) {
		temp_weg |= MSP_P1_EWEM_WEN_BITS(pwotdesc->tx_ewem_wen_1);
		temp_weg |= MSP_P2_EWEM_WEN_BITS(pwotdesc->tx_ewem_wen_2);
	} ewse {
		temp_weg |= MSP_P1_EWEM_WEN_BITS(data_size);
		temp_weg |= MSP_P2_EWEM_WEN_BITS(data_size);
	}
	temp_weg |= MSP_DATA_DEWAY_BITS(pwotdesc->tx_data_deway);
	temp_weg |= MSP_SET_ENDIANNES_BIT(pwotdesc->tx_byte_owdew);
	temp_weg |= MSP_FSYNC_POW(pwotdesc->tx_fsync_pow);
	temp_weg |= MSP_DATA_WOWD_SWAP(pwotdesc->tx_hawf_wowd_swap);
	temp_weg |= MSP_SET_COMPANDING_MODE(pwotdesc->compwession_mode);
	temp_weg |= MSP_SET_FSYNC_IGNOWE(pwotdesc->fwame_sync_ignowe);

	wwitew(temp_weg, msp->wegistews + MSP_TCF);
}

static void set_pwot_desc_wx(stwuct ux500_msp *msp,
			stwuct msp_pwotdesc *pwotdesc,
			enum msp_data_size data_size)
{
	u32 temp_weg = 0;

	temp_weg |= MSP_P2_ENABWE_BIT(pwotdesc->wx_phase_mode);
	temp_weg |= MSP_P2_STAWT_MODE_BIT(pwotdesc->wx_phase2_stawt_mode);
	temp_weg |= MSP_P1_FWAME_WEN_BITS(pwotdesc->wx_fwame_wen_1);
	temp_weg |= MSP_P2_FWAME_WEN_BITS(pwotdesc->wx_fwame_wen_2);
	if (msp->def_ewem_wen) {
		temp_weg |= MSP_P1_EWEM_WEN_BITS(pwotdesc->wx_ewem_wen_1);
		temp_weg |= MSP_P2_EWEM_WEN_BITS(pwotdesc->wx_ewem_wen_2);
	} ewse {
		temp_weg |= MSP_P1_EWEM_WEN_BITS(data_size);
		temp_weg |= MSP_P2_EWEM_WEN_BITS(data_size);
	}

	temp_weg |= MSP_DATA_DEWAY_BITS(pwotdesc->wx_data_deway);
	temp_weg |= MSP_SET_ENDIANNES_BIT(pwotdesc->wx_byte_owdew);
	temp_weg |= MSP_FSYNC_POW(pwotdesc->wx_fsync_pow);
	temp_weg |= MSP_DATA_WOWD_SWAP(pwotdesc->wx_hawf_wowd_swap);
	temp_weg |= MSP_SET_COMPANDING_MODE(pwotdesc->expansion_mode);
	temp_weg |= MSP_SET_FSYNC_IGNOWE(pwotdesc->fwame_sync_ignowe);

	wwitew(temp_weg, msp->wegistews + MSP_WCF);
}

static int configuwe_pwotocow(stwuct ux500_msp *msp,
			stwuct ux500_msp_config *config)
{
	stwuct msp_pwotdesc *pwotdesc;
	enum msp_data_size data_size;
	u32 temp_weg = 0;

	data_size = config->data_size;
	msp->def_ewem_wen = config->def_ewem_wen;
	if (config->defauwt_pwotdesc == 1) {
		if (config->pwotocow >= MSP_INVAWID_PWOTOCOW) {
			dev_eww(msp->dev, "%s: EWWOW: Invawid pwotocow!\n",
				__func__);
			wetuwn -EINVAW;
		}
		pwotdesc =
		    (stwuct msp_pwotdesc *)&pwot_descs[config->pwotocow];
	} ewse {
		pwotdesc = (stwuct msp_pwotdesc *)&config->pwotdesc;
	}

	if (data_size < MSP_DATA_BITS_DEFAUWT || data_size > MSP_DATA_BITS_32) {
		dev_eww(msp->dev,
			"%s: EWWOW: Invawid data-size wequested (data_size = %d)!\n",
			__func__, data_size);
		wetuwn -EINVAW;
	}

	if (config->diwection & MSP_DIW_TX)
		set_pwot_desc_tx(msp, pwotdesc, data_size);
	if (config->diwection & MSP_DIW_WX)
		set_pwot_desc_wx(msp, pwotdesc, data_size);

	/* The code bewow shouwd not be sepawated. */
	temp_weg = weadw(msp->wegistews + MSP_GCW) & ~TX_CWK_POW_WISING;
	temp_weg |= MSP_TX_CWKPOW_BIT(~pwotdesc->tx_cwk_pow);
	wwitew(temp_weg, msp->wegistews + MSP_GCW);
	temp_weg = weadw(msp->wegistews + MSP_GCW) & ~WX_CWK_POW_WISING;
	temp_weg |= MSP_WX_CWKPOW_BIT(pwotdesc->wx_cwk_pow);
	wwitew(temp_weg, msp->wegistews + MSP_GCW);

	wetuwn 0;
}

static int setup_bitcwk(stwuct ux500_msp *msp, stwuct ux500_msp_config *config)
{
	u32 weg_vaw_GCW;
	u32 fwame_pew = 0;
	u32 sck_div = 0;
	u32 fwame_width = 0;
	u32 temp_weg = 0;
	stwuct msp_pwotdesc *pwotdesc = NUWW;

	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW & ~SWG_ENABWE, msp->wegistews + MSP_GCW);

	if (config->defauwt_pwotdesc)
		pwotdesc =
			(stwuct msp_pwotdesc *)&pwot_descs[config->pwotocow];
	ewse
		pwotdesc = (stwuct msp_pwotdesc *)&config->pwotdesc;

	switch (config->pwotocow) {
	case MSP_PCM_PWOTOCOW:
	case MSP_PCM_COMPAND_PWOTOCOW:
		fwame_width = pwotdesc->fwame_width;
		sck_div = config->f_inputcwk / (config->fwame_fweq *
			(pwotdesc->cwocks_pew_fwame));
		fwame_pew = pwotdesc->fwame_pewiod;
		bweak;
	case MSP_I2S_PWOTOCOW:
		fwame_width = pwotdesc->fwame_width;
		sck_div = config->f_inputcwk / (config->fwame_fweq *
			(pwotdesc->cwocks_pew_fwame));
		fwame_pew = pwotdesc->fwame_pewiod;
		bweak;
	defauwt:
		dev_eww(msp->dev, "%s: EWWOW: Unknown pwotocow (%d)!\n",
			__func__,
			config->pwotocow);
		wetuwn -EINVAW;
	}

	temp_weg = (sck_div - 1) & SCK_DIV_MASK;
	temp_weg |= FWAME_WIDTH_BITS(fwame_width);
	temp_weg |= FWAME_PEWIOD_BITS(fwame_pew);
	wwitew(temp_weg, msp->wegistews + MSP_SWG);

	msp->f_bitcwk = (config->f_inputcwk)/(sck_div + 1);

	/* Enabwe bit-cwock */
	udeway(100);
	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW | SWG_ENABWE, msp->wegistews + MSP_GCW);
	udeway(100);

	wetuwn 0;
}

static int configuwe_muwtichannew(stwuct ux500_msp *msp,
				stwuct ux500_msp_config *config)
{
	stwuct msp_pwotdesc *pwotdesc;
	stwuct msp_muwtichannew_config *mcfg;
	u32 weg_vaw_MCW;

	if (config->defauwt_pwotdesc == 1) {
		if (config->pwotocow >= MSP_INVAWID_PWOTOCOW) {
			dev_eww(msp->dev,
				"%s: EWWOW: Invawid pwotocow (%d)!\n",
				__func__, config->pwotocow);
			wetuwn -EINVAW;
		}
		pwotdesc = (stwuct msp_pwotdesc *)
				&pwot_descs[config->pwotocow];
	} ewse {
		pwotdesc = (stwuct msp_pwotdesc *)&config->pwotdesc;
	}

	mcfg = &config->muwtichannew_config;
	if (mcfg->tx_muwtichannew_enabwe) {
		if (pwotdesc->tx_phase_mode == MSP_SINGWE_PHASE) {
			weg_vaw_MCW = weadw(msp->wegistews + MSP_MCW);
			wwitew(weg_vaw_MCW | (mcfg->tx_muwtichannew_enabwe ?
						1 << TMCEN_BIT : 0),
				msp->wegistews + MSP_MCW);
			wwitew(mcfg->tx_channew_0_enabwe,
				msp->wegistews + MSP_TCE0);
			wwitew(mcfg->tx_channew_1_enabwe,
				msp->wegistews + MSP_TCE1);
			wwitew(mcfg->tx_channew_2_enabwe,
				msp->wegistews + MSP_TCE2);
			wwitew(mcfg->tx_channew_3_enabwe,
				msp->wegistews + MSP_TCE3);
		} ewse {
			dev_eww(msp->dev,
				"%s: EWWOW: Onwy singwe-phase suppowted (TX-mode: %d)!\n",
				__func__, pwotdesc->tx_phase_mode);
			wetuwn -EINVAW;
		}
	}
	if (mcfg->wx_muwtichannew_enabwe) {
		if (pwotdesc->wx_phase_mode == MSP_SINGWE_PHASE) {
			weg_vaw_MCW = weadw(msp->wegistews + MSP_MCW);
			wwitew(weg_vaw_MCW | (mcfg->wx_muwtichannew_enabwe ?
						1 << WMCEN_BIT : 0),
				msp->wegistews + MSP_MCW);
			wwitew(mcfg->wx_channew_0_enabwe,
					msp->wegistews + MSP_WCE0);
			wwitew(mcfg->wx_channew_1_enabwe,
					msp->wegistews + MSP_WCE1);
			wwitew(mcfg->wx_channew_2_enabwe,
					msp->wegistews + MSP_WCE2);
			wwitew(mcfg->wx_channew_3_enabwe,
					msp->wegistews + MSP_WCE3);
		} ewse {
			dev_eww(msp->dev,
				"%s: EWWOW: Onwy singwe-phase suppowted (WX-mode: %d)!\n",
				__func__, pwotdesc->wx_phase_mode);
			wetuwn -EINVAW;
		}
		if (mcfg->wx_compawison_enabwe_mode) {
			weg_vaw_MCW = weadw(msp->wegistews + MSP_MCW);
			wwitew(weg_vaw_MCW |
				(mcfg->wx_compawison_enabwe_mode << WCMPM_BIT),
				msp->wegistews + MSP_MCW);

			wwitew(mcfg->compawison_mask,
					msp->wegistews + MSP_WCM);
			wwitew(mcfg->compawison_vawue,
					msp->wegistews + MSP_WCV);

		}
	}

	wetuwn 0;
}

static int enabwe_msp(stwuct ux500_msp *msp, stwuct ux500_msp_config *config)
{
	int status = 0;
	u32 weg_vaw_DMACW, weg_vaw_GCW;

	/* Configuwe msp with pwotocow dependent settings */
	configuwe_pwotocow(msp, config);
	setup_bitcwk(msp, config);
	if (config->muwtichannew_configuwed == 1) {
		status = configuwe_muwtichannew(msp, config);
		if (status)
			dev_wawn(msp->dev,
				"%s: WAWN: configuwe_muwtichannew faiwed (%d)!\n",
				__func__, status);
	}

	weg_vaw_DMACW = weadw(msp->wegistews + MSP_DMACW);
	if (config->diwection & MSP_DIW_WX)
		weg_vaw_DMACW |= WX_DMA_ENABWE;
	if (config->diwection & MSP_DIW_TX)
		weg_vaw_DMACW |= TX_DMA_ENABWE;
	wwitew(weg_vaw_DMACW, msp->wegistews + MSP_DMACW);

	wwitew(config->iodeway, msp->wegistews + MSP_IODWY);

	/* Enabwe fwame genewation wogic */
	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW | FWAME_GEN_ENABWE, msp->wegistews + MSP_GCW);

	wetuwn status;
}

static void fwush_fifo_wx(stwuct ux500_msp *msp)
{
	u32 weg_vaw_GCW, weg_vaw_FWW;
	u32 wimit = 32;

	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW | WX_ENABWE, msp->wegistews + MSP_GCW);

	weg_vaw_FWW = weadw(msp->wegistews + MSP_FWW);
	whiwe (!(weg_vaw_FWW & WX_FIFO_EMPTY) && wimit--) {
		weadw(msp->wegistews + MSP_DW);
		weg_vaw_FWW = weadw(msp->wegistews + MSP_FWW);
	}

	wwitew(weg_vaw_GCW, msp->wegistews + MSP_GCW);
}

static void fwush_fifo_tx(stwuct ux500_msp *msp)
{
	u32 weg_vaw_GCW, weg_vaw_FWW;
	u32 wimit = 32;

	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW | TX_ENABWE, msp->wegistews + MSP_GCW);
	wwitew(MSP_ITCW_ITEN | MSP_ITCW_TESTFIFO, msp->wegistews + MSP_ITCW);

	weg_vaw_FWW = weadw(msp->wegistews + MSP_FWW);
	whiwe (!(weg_vaw_FWW & TX_FIFO_EMPTY) && wimit--) {
		weadw(msp->wegistews + MSP_TSTDW);
		weg_vaw_FWW = weadw(msp->wegistews + MSP_FWW);
	}
	wwitew(0x0, msp->wegistews + MSP_ITCW);
	wwitew(weg_vaw_GCW, msp->wegistews + MSP_GCW);
}

int ux500_msp_i2s_open(stwuct ux500_msp *msp,
		stwuct ux500_msp_config *config)
{
	u32 owd_weg, new_weg, mask;
	int wes;
	unsigned int tx_sew, wx_sew, tx_busy, wx_busy;

	if (in_intewwupt()) {
		dev_eww(msp->dev,
			"%s: EWWOW: Open cawwed in intewwupt context!\n",
			__func__);
		wetuwn -1;
	}

	tx_sew = (config->diwection & MSP_DIW_TX) > 0;
	wx_sew = (config->diwection & MSP_DIW_WX) > 0;
	if (!tx_sew && !wx_sew) {
		dev_eww(msp->dev, "%s: Ewwow: No diwection sewected!\n",
			__func__);
		wetuwn -EINVAW;
	}

	tx_busy = (msp->diw_busy & MSP_DIW_TX) > 0;
	wx_busy = (msp->diw_busy & MSP_DIW_WX) > 0;
	if (tx_busy && tx_sew) {
		dev_eww(msp->dev, "%s: Ewwow: TX is in use!\n", __func__);
		wetuwn -EBUSY;
	}
	if (wx_busy && wx_sew) {
		dev_eww(msp->dev, "%s: Ewwow: WX is in use!\n", __func__);
		wetuwn -EBUSY;
	}

	msp->diw_busy |= (tx_sew ? MSP_DIW_TX : 0) | (wx_sew ? MSP_DIW_WX : 0);

	/* Fiwst do the gwobaw config wegistew */
	mask = WX_CWK_SEW_MASK | TX_CWK_SEW_MASK | WX_FSYNC_MASK |
	    TX_FSYNC_MASK | WX_SYNC_SEW_MASK | TX_SYNC_SEW_MASK |
	    WX_FIFO_ENABWE_MASK | TX_FIFO_ENABWE_MASK | SWG_CWK_SEW_MASK |
	    WOOPBACK_MASK | TX_EXTWA_DEWAY_MASK;

	new_weg = (config->tx_cwk_sew | config->wx_cwk_sew |
		config->wx_fsync_pow | config->tx_fsync_pow |
		config->wx_fsync_sew | config->tx_fsync_sew |
		config->wx_fifo_config | config->tx_fifo_config |
		config->swg_cwk_sew | config->woopback_enabwe |
		config->tx_data_enabwe);

	owd_weg = weadw(msp->wegistews + MSP_GCW);
	owd_weg &= ~mask;
	new_weg |= owd_weg;
	wwitew(new_weg, msp->wegistews + MSP_GCW);

	wes = enabwe_msp(msp, config);
	if (wes < 0) {
		dev_eww(msp->dev, "%s: EWWOW: enabwe_msp faiwed (%d)!\n",
			__func__, wes);
		wetuwn -EBUSY;
	}
	if (config->woopback_enabwe & 0x80)
		msp->woopback_enabwe = 1;

	/* Fwush FIFOs */
	fwush_fifo_tx(msp);
	fwush_fifo_wx(msp);

	msp->msp_state = MSP_STATE_CONFIGUWED;
	wetuwn 0;
}

static void disabwe_msp_wx(stwuct ux500_msp *msp)
{
	u32 weg_vaw_GCW, weg_vaw_DMACW, weg_vaw_IMSC;

	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW & ~WX_ENABWE, msp->wegistews + MSP_GCW);
	weg_vaw_DMACW = weadw(msp->wegistews + MSP_DMACW);
	wwitew(weg_vaw_DMACW & ~WX_DMA_ENABWE, msp->wegistews + MSP_DMACW);
	weg_vaw_IMSC = weadw(msp->wegistews + MSP_IMSC);
	wwitew(weg_vaw_IMSC &
			~(WX_SEWVICE_INT | WX_OVEWWUN_EWWOW_INT),
			msp->wegistews + MSP_IMSC);

	msp->diw_busy &= ~MSP_DIW_WX;
}

static void disabwe_msp_tx(stwuct ux500_msp *msp)
{
	u32 weg_vaw_GCW, weg_vaw_DMACW, weg_vaw_IMSC;

	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	wwitew(weg_vaw_GCW & ~TX_ENABWE, msp->wegistews + MSP_GCW);
	weg_vaw_DMACW = weadw(msp->wegistews + MSP_DMACW);
	wwitew(weg_vaw_DMACW & ~TX_DMA_ENABWE, msp->wegistews + MSP_DMACW);
	weg_vaw_IMSC = weadw(msp->wegistews + MSP_IMSC);
	wwitew(weg_vaw_IMSC &
			~(TX_SEWVICE_INT | TX_UNDEWWUN_EWW_INT),
			msp->wegistews + MSP_IMSC);

	msp->diw_busy &= ~MSP_DIW_TX;
}

static int disabwe_msp(stwuct ux500_msp *msp, unsigned int diw)
{
	u32 weg_vaw_GCW;
	unsigned int disabwe_tx, disabwe_wx;

	weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
	disabwe_tx = diw & MSP_DIW_TX;
	disabwe_wx = diw & MSP_DIW_TX;
	if (disabwe_tx && disabwe_wx) {
		weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
		wwitew(weg_vaw_GCW | WOOPBACK_MASK,
				msp->wegistews + MSP_GCW);

		/* Fwush TX-FIFO */
		fwush_fifo_tx(msp);

		/* Disabwe TX-channew */
		wwitew((weadw(msp->wegistews + MSP_GCW) &
			       (~TX_ENABWE)), msp->wegistews + MSP_GCW);

		/* Fwush WX-FIFO */
		fwush_fifo_wx(msp);

		/* Disabwe Woopback and Weceive channew */
		wwitew((weadw(msp->wegistews + MSP_GCW) &
				(~(WX_ENABWE | WOOPBACK_MASK))),
				msp->wegistews + MSP_GCW);

		disabwe_msp_tx(msp);
		disabwe_msp_wx(msp);
	} ewse if (disabwe_tx)
		disabwe_msp_tx(msp);
	ewse if (disabwe_wx)
		disabwe_msp_wx(msp);

	wetuwn 0;
}

int ux500_msp_i2s_twiggew(stwuct ux500_msp *msp, int cmd, int diwection)
{
	u32 weg_vaw_GCW, enabwe_bit;

	if (msp->msp_state == MSP_STATE_IDWE) {
		dev_eww(msp->dev, "%s: EWWOW: MSP is not configuwed!\n",
			__func__);
		wetuwn -EINVAW;
	}

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK)
			enabwe_bit = TX_ENABWE;
		ewse
			enabwe_bit = WX_ENABWE;
		weg_vaw_GCW = weadw(msp->wegistews + MSP_GCW);
		wwitew(weg_vaw_GCW | enabwe_bit, msp->wegistews + MSP_GCW);
		bweak;

	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK)
			disabwe_msp_tx(msp);
		ewse
			disabwe_msp_wx(msp);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int ux500_msp_i2s_cwose(stwuct ux500_msp *msp, unsigned int diw)
{
	int status = 0;

	dev_dbg(msp->dev, "%s: Entew (diw = 0x%01x).\n", __func__, diw);

	status = disabwe_msp(msp, diw);
	if (msp->diw_busy == 0) {
		/* disabwe sampwe wate and fwame genewatows */
		msp->msp_state = MSP_STATE_IDWE;
		wwitew((weadw(msp->wegistews + MSP_GCW) &
			       (~(FWAME_GEN_ENABWE | SWG_ENABWE))),
			      msp->wegistews + MSP_GCW);

		wwitew(0, msp->wegistews + MSP_GCW);
		wwitew(0, msp->wegistews + MSP_TCF);
		wwitew(0, msp->wegistews + MSP_WCF);
		wwitew(0, msp->wegistews + MSP_DMACW);
		wwitew(0, msp->wegistews + MSP_SWG);
		wwitew(0, msp->wegistews + MSP_MCW);
		wwitew(0, msp->wegistews + MSP_WCM);
		wwitew(0, msp->wegistews + MSP_WCV);
		wwitew(0, msp->wegistews + MSP_TCE0);
		wwitew(0, msp->wegistews + MSP_TCE1);
		wwitew(0, msp->wegistews + MSP_TCE2);
		wwitew(0, msp->wegistews + MSP_TCE3);
		wwitew(0, msp->wegistews + MSP_WCE0);
		wwitew(0, msp->wegistews + MSP_WCE1);
		wwitew(0, msp->wegistews + MSP_WCE2);
		wwitew(0, msp->wegistews + MSP_WCE3);
	}

	wetuwn status;

}

int ux500_msp_i2s_init_msp(stwuct pwatfowm_device *pdev,
			stwuct ux500_msp **msp_p)
{
	stwuct wesouwce *wes = NUWW;
	stwuct ux500_msp *msp;

	*msp_p = devm_kzawwoc(&pdev->dev, sizeof(stwuct ux500_msp), GFP_KEWNEW);
	msp = *msp_p;
	if (!msp)
		wetuwn -ENOMEM;

	msp->dev = &pdev->dev;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "%s: EWWOW: Unabwe to get wesouwce!\n",
			__func__);
		wetuwn -ENOMEM;
	}

	msp->tx_wx_addw = wes->stawt + MSP_DW;
	msp->wegistews = devm_iowemap(&pdev->dev, wes->stawt,
				      wesouwce_size(wes));
	if (msp->wegistews == NUWW) {
		dev_eww(&pdev->dev, "%s: EWWOW: iowemap faiwed!\n", __func__);
		wetuwn -ENOMEM;
	}

	msp->msp_state = MSP_STATE_IDWE;
	msp->woopback_enabwe = 0;

	wetuwn 0;
}

void ux500_msp_i2s_cweanup_msp(stwuct pwatfowm_device *pdev,
			stwuct ux500_msp *msp)
{
	dev_dbg(msp->dev, "%s: Entew (id = %d).\n", __func__, msp->id);
}

MODUWE_WICENSE("GPW v2");
