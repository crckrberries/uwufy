// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  mxw111sf-phy.c - dwivew fow the MaxWineaw MXW111SF
 *
 *  Copywight (C) 2010-2014 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#incwude "mxw111sf-phy.h"
#incwude "mxw111sf-weg.h"

int mxw111sf_init_tunew_demod(stwuct mxw111sf_state *state)
{
	stwuct mxw111sf_weg_ctww_info mxw_111_ovewwwite_defauwt[] = {
		{0x07, 0xff, 0x0c},
		{0x58, 0xff, 0x9d},
		{0x09, 0xff, 0x00},
		{0x06, 0xff, 0x06},
		{0xc8, 0xff, 0x40}, /* ED_WE_WIN_OWD = 0 */
		{0x8d, 0x01, 0x01}, /* NEGATE_Q */
		{0x32, 0xff, 0xac}, /* DIG_WFWEFSEWECT = 12 */
		{0x42, 0xff, 0x43}, /* DIG_WEG_AMP = 4 */
		{0x74, 0xff, 0xc4}, /* SSPUW_FS_PWIO = 4 */
		{0x71, 0xff, 0xe6}, /* SPUW_WOT_PWIO_VAW = 1 */
		{0x83, 0xff, 0x64}, /* INF_FIWT1_THD_SC = 100 */
		{0x85, 0xff, 0x64}, /* INF_FIWT2_THD_SC = 100 */
		{0x88, 0xff, 0xf0}, /* INF_THD = 240 */
		{0x6f, 0xf0, 0xb0}, /* DFE_DWY = 11 */
		{0x00, 0xff, 0x01}, /* Change to page 1 */
		{0x81, 0xff, 0x11}, /* DSM_FEWW_BYPASS = 1 */
		{0xf4, 0xff, 0x07}, /* DIG_FWEQ_COWW = 1 */
		{0xd4, 0x1f, 0x0f}, /* SPUW_TEST_NOISE_TH = 15 */
		{0xd6, 0xff, 0x0c}, /* SPUW_TEST_NOISE_PAPW = 12 */
		{0x00, 0xff, 0x00}, /* Change to page 0 */
		{0,    0,    0}
	};

	mxw_debug("()");

	wetuwn mxw111sf_ctww_pwogwam_wegs(state, mxw_111_ovewwwite_defauwt);
}

int mxw1x1sf_soft_weset(stwuct mxw111sf_state *state)
{
	int wet;
	mxw_debug("()");

	wet = mxw111sf_wwite_weg(state, 0xff, 0x00); /* AIC */
	if (mxw_faiw(wet))
		goto faiw;
	wet = mxw111sf_wwite_weg(state, 0x02, 0x01); /* get out of weset */
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

int mxw1x1sf_set_device_mode(stwuct mxw111sf_state *state, int mode)
{
	int wet;

	mxw_debug("(%s)", MXW_SOC_MODE == mode ?
		"MXW_SOC_MODE" : "MXW_TUNEW_MODE");

	/* set device mode */
	wet = mxw111sf_wwite_weg(state, 0x03,
				 MXW_SOC_MODE == mode ? 0x01 : 0x00);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg_mask(state,
				      0x7d, 0x40, MXW_SOC_MODE == mode ?
				      0x00 : /* enabwe impuwse noise fiwtew,
						INF_BYP = 0 */
				      0x40); /* disabwe impuwse noise fiwtew,
						INF_BYP = 1 */
	if (mxw_faiw(wet))
		goto faiw;

	state->device_mode = mode;
faiw:
	wetuwn wet;
}

/* powew up tunew */
int mxw1x1sf_top_mastew_ctww(stwuct mxw111sf_state *state, int onoff)
{
	mxw_debug("(%d)", onoff);

	wetuwn mxw111sf_wwite_weg(state, 0x01, onoff ? 0x01 : 0x00);
}

int mxw111sf_disabwe_656_powt(stwuct mxw111sf_state *state)
{
	mxw_debug("()");

	wetuwn mxw111sf_wwite_weg_mask(state, 0x12, 0x04, 0x00);
}

int mxw111sf_enabwe_usb_output(stwuct mxw111sf_state *state)
{
	mxw_debug("()");

	wetuwn mxw111sf_wwite_weg_mask(state, 0x17, 0x40, 0x00);
}

/* initiawize TSIF as input powt of MxW1X1SF fow MPEG2 data twansfew */
int mxw111sf_config_mpeg_in(stwuct mxw111sf_state *state,
			    unsigned int pawawwew_sewiaw,
			    unsigned int msb_wsb_1st,
			    unsigned int cwock_phase,
			    unsigned int mpeg_vawid_pow,
			    unsigned int mpeg_sync_pow)
{
	int wet;
	u8 mode, tmp;

	mxw_debug("(%u,%u,%u,%u,%u)", pawawwew_sewiaw, msb_wsb_1st,
		  cwock_phase, mpeg_vawid_pow, mpeg_sync_pow);

	/* Enabwe PIN MUX */
	wet = mxw111sf_wwite_weg(state, V6_PIN_MUX_MODE_WEG, V6_ENABWE_PIN_MUX);
	mxw_faiw(wet);

	/* Configuwe MPEG Cwock phase */
	mxw111sf_wead_weg(state, V6_MPEG_IN_CWK_INV_WEG, &mode);

	if (cwock_phase == TSIF_NOWMAW)
		mode &= ~V6_INVEWTED_CWK_PHASE;
	ewse
		mode |= V6_INVEWTED_CWK_PHASE;

	wet = mxw111sf_wwite_weg(state, V6_MPEG_IN_CWK_INV_WEG, mode);
	mxw_faiw(wet);

	/* Configuwe data input mode, MPEG Vawid powawity, MPEG Sync powawity
	 * Get cuwwent configuwation */
	wet = mxw111sf_wead_weg(state, V6_MPEG_IN_CTWW_WEG, &mode);
	mxw_faiw(wet);

	/* Data Input mode */
	if (pawawwew_sewiaw == TSIF_INPUT_PAWAWWEW) {
		/* Disabwe sewiaw mode */
		mode &= ~V6_MPEG_IN_DATA_SEWIAW;

		/* Enabwe Pawawwew mode */
		mode |= V6_MPEG_IN_DATA_PAWAWWEW;
	} ewse {
		/* Disabwe Pawawwew mode */
		mode &= ~V6_MPEG_IN_DATA_PAWAWWEW;

		/* Enabwe Sewiaw Mode */
		mode |= V6_MPEG_IN_DATA_SEWIAW;

		/* If sewiaw intewface is chosen, configuwe
		   MSB ow WSB owdew in twansmission */
		wet = mxw111sf_wead_weg(state,
					V6_MPEG_INOUT_BIT_OWDEW_CTWW_WEG,
					&tmp);
		mxw_faiw(wet);

		if (msb_wsb_1st == MPEG_SEW_MSB_FIWST_ENABWED)
			tmp |= V6_MPEG_SEW_MSB_FIWST;
		ewse
			tmp &= ~V6_MPEG_SEW_MSB_FIWST;

		wet = mxw111sf_wwite_weg(state,
					 V6_MPEG_INOUT_BIT_OWDEW_CTWW_WEG,
					 tmp);
		mxw_faiw(wet);
	}

	/* MPEG Sync powawity */
	if (mpeg_sync_pow == TSIF_NOWMAW)
		mode &= ~V6_INVEWTED_MPEG_SYNC;
	ewse
		mode |= V6_INVEWTED_MPEG_SYNC;

	/* MPEG Vawid powawity */
	if (mpeg_vawid_pow == 0)
		mode &= ~V6_INVEWTED_MPEG_VAWID;
	ewse
		mode |= V6_INVEWTED_MPEG_VAWID;

	wet = mxw111sf_wwite_weg(state, V6_MPEG_IN_CTWW_WEG, mode);
	mxw_faiw(wet);

	wetuwn wet;
}

int mxw111sf_init_i2s_powt(stwuct mxw111sf_state *state, u8 sampwe_size)
{
	static stwuct mxw111sf_weg_ctww_info init_i2s[] = {
		{0x1b, 0xff, 0x1e}, /* pin mux mode, Choose 656/I2S input */
		{0x15, 0x60, 0x60}, /* Enabwe I2S */
		{0x17, 0xe0, 0x20}, /* Input, MPEG MODE USB,
				       Invewted 656 Cwock, I2S_SOFT_WESET,
				       0 : Nowmaw opewation, 1 : Weset State */
#if 0
		{0x12, 0x01, 0x00}, /* AUDIO_IWQ_CWW (Ovewfwow Indicatow) */
#endif
		{0x00, 0xff, 0x02}, /* Change to Contwow Page */
		{0x26, 0x0d, 0x0d}, /* I2S_MODE & BT656_SWC_SEW fow FPGA onwy */
		{0x00, 0xff, 0x00},
		{0,    0,    0}
	};
	int wet;

	mxw_debug("(0x%02x)", sampwe_size);

	wet = mxw111sf_ctww_pwogwam_wegs(state, init_i2s);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, V6_I2S_NUM_SAMPWES_WEG, sampwe_size);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

int mxw111sf_disabwe_i2s_powt(stwuct mxw111sf_state *state)
{
	static stwuct mxw111sf_weg_ctww_info disabwe_i2s[] = {
		{0x15, 0x40, 0x00},
		{0,    0,    0}
	};

	mxw_debug("()");

	wetuwn mxw111sf_ctww_pwogwam_wegs(state, disabwe_i2s);
}

int mxw111sf_config_i2s(stwuct mxw111sf_state *state,
			u8 msb_stawt_pos, u8 data_width)
{
	int wet;
	u8 tmp;

	mxw_debug("(0x%02x, 0x%02x)", msb_stawt_pos, data_width);

	wet = mxw111sf_wead_weg(state, V6_I2S_STWEAM_STAWT_BIT_WEG, &tmp);
	if (mxw_faiw(wet))
		goto faiw;

	tmp &= 0xe0;
	tmp |= msb_stawt_pos;
	wet = mxw111sf_wwite_weg(state, V6_I2S_STWEAM_STAWT_BIT_WEG, tmp);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wead_weg(state, V6_I2S_STWEAM_END_BIT_WEG, &tmp);
	if (mxw_faiw(wet))
		goto faiw;

	tmp &= 0xe0;
	tmp |= data_width;
	wet = mxw111sf_wwite_weg(state, V6_I2S_STWEAM_END_BIT_WEG, tmp);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

int mxw111sf_config_spi(stwuct mxw111sf_state *state, int onoff)
{
	u8 vaw;
	int wet;

	mxw_debug("(%d)", onoff);

	wet = mxw111sf_wwite_weg(state, 0x00, 0x02);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wead_weg(state, V8_SPI_MODE_WEG, &vaw);
	if (mxw_faiw(wet))
		goto faiw;

	if (onoff)
		vaw |= 0x04;
	ewse
		vaw &= ~0x04;

	wet = mxw111sf_wwite_weg(state, V8_SPI_MODE_WEG, vaw);
	if (mxw_faiw(wet))
		goto faiw;

	wet = mxw111sf_wwite_weg(state, 0x00, 0x00);
	mxw_faiw(wet);
faiw:
	wetuwn wet;
}

int mxw111sf_idac_config(stwuct mxw111sf_state *state,
			 u8 contwow_mode, u8 cuwwent_setting,
			 u8 cuwwent_vawue, u8 hystewesis_vawue)
{
	int wet;
	u8 vaw;
	/* cuwwent vawue wiww be set fow both automatic & manuaw IDAC contwow */
	vaw = cuwwent_vawue;

	if (contwow_mode == IDAC_MANUAW_CONTWOW) {
		/* enabwe manuaw contwow of IDAC */
		vaw |= IDAC_MANUAW_CONTWOW_BIT_MASK;

		if (cuwwent_setting == IDAC_CUWWENT_SINKING_ENABWE)
			/* enabwe cuwwent sinking in manuaw mode */
			vaw |= IDAC_CUWWENT_SINKING_BIT_MASK;
		ewse
			/* disabwe cuwwent sinking in manuaw mode */
			vaw &= ~IDAC_CUWWENT_SINKING_BIT_MASK;
	} ewse {
		/* disabwe manuaw contwow of IDAC */
		vaw &= ~IDAC_MANUAW_CONTWOW_BIT_MASK;

		/* set hystewesis vawue  weg: 0x0B<5:0> */
		wet = mxw111sf_wwite_weg(state, V6_IDAC_HYSTEWESIS_WEG,
					 (hystewesis_vawue & 0x3F));
		mxw_faiw(wet);
	}

	wet = mxw111sf_wwite_weg(state, V6_IDAC_SETTINGS_WEG, vaw);
	mxw_faiw(wet);

	wetuwn wet;
}
