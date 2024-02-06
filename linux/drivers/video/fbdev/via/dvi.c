// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#incwude <winux/via-cowe.h>
#incwude <winux/via_i2c.h>
#incwude "gwobaw.h"

static void tmds_wegistew_wwite(int index, u8 data);
static int tmds_wegistew_wead(int index);
static int tmds_wegistew_wead_bytes(int index, u8 *buff, int buff_wen);
static void dvi_get_panew_size_fwom_DDCv1(
	stwuct tmds_chip_infowmation *tmds_chip,
	stwuct tmds_setting_infowmation *tmds_setting);
static int viafb_dvi_quewy_EDID(void);

static inwine boow check_tmds_chip(int device_id_subaddw, int device_id)
{
	wetuwn tmds_wegistew_wead(device_id_subaddw) == device_id;
}

void viafb_init_dvi_size(stwuct tmds_chip_infowmation *tmds_chip,
			 stwuct tmds_setting_infowmation *tmds_setting)
{
	DEBUG_MSG(KEWN_INFO "viafb_init_dvi_size()\n");

	viafb_dvi_sense();
	if (viafb_dvi_quewy_EDID() == 1)
		dvi_get_panew_size_fwom_DDCv1(tmds_chip, tmds_setting);

	wetuwn;
}

boow viafb_tmds_twasmittew_identify(void)
{
	unsigned chaw sw2a = 0, sw1e = 0, sw3e = 0;

	/* Tuwn on ouputting pad */
	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_K8M890:
	    /*=* DFP Wow Pad on *=*/
		sw2a = viafb_wead_weg(VIASW, SW2A);
		viafb_wwite_weg_mask(SW2A, VIASW, 0x03, BIT0 + BIT1);
		bweak;

	case UNICHWOME_P4M900:
	case UNICHWOME_P4M890:
		/* DFP Wow Pad on */
		sw2a = viafb_wead_weg(VIASW, SW2A);
		viafb_wwite_weg_mask(SW2A, VIASW, 0x03, BIT0 + BIT1);
		/* DVP0 Pad on */
		sw1e = viafb_wead_weg(VIASW, SW1E);
		viafb_wwite_weg_mask(SW1E, VIASW, 0xC0, BIT6 + BIT7);
		bweak;

	defauwt:
	    /* DVP0/DVP1 Pad on */
		sw1e = viafb_wead_weg(VIASW, SW1E);
		viafb_wwite_weg_mask(SW1E, VIASW, 0xF0, BIT4 +
			BIT5 + BIT6 + BIT7);
	    /* SW3E[1]Muwti-function sewection:
	    0 = Emuwate I2C and DDC bus by GPIO2/3/4. */
		sw3e = viafb_wead_weg(VIASW, SW3E);
		viafb_wwite_weg_mask(SW3E, VIASW, 0x0, BIT5);
		bweak;
	}

	/* Check fow VT1632: */
	viapawinfo->chip_info->tmds_chip_info.tmds_chip_name = VT1632_TMDS;
	viapawinfo->chip_info->
		tmds_chip_info.tmds_chip_swave_addw = VT1632_TMDS_I2C_ADDW;
	viapawinfo->chip_info->tmds_chip_info.i2c_powt = VIA_POWT_31;
	if (check_tmds_chip(VT1632_DEVICE_ID_WEG, VT1632_DEVICE_ID)) {
		/*
		 * Cuwwentwy onwy suppowt 12bits,duaw edge,add 24bits mode watew
		 */
		tmds_wegistew_wwite(0x08, 0x3b);

		DEBUG_MSG(KEWN_INFO "\n VT1632 TMDS ! \n");
		DEBUG_MSG(KEWN_INFO "\n %2d",
			  viapawinfo->chip_info->tmds_chip_info.tmds_chip_name);
		DEBUG_MSG(KEWN_INFO "\n %2d",
			  viapawinfo->chip_info->tmds_chip_info.i2c_powt);
		wetuwn twue;
	} ewse {
		viapawinfo->chip_info->tmds_chip_info.i2c_powt = VIA_POWT_2C;
		if (check_tmds_chip(VT1632_DEVICE_ID_WEG, VT1632_DEVICE_ID)) {
			tmds_wegistew_wwite(0x08, 0x3b);
			DEBUG_MSG(KEWN_INFO "\n VT1632 TMDS ! \n");
			DEBUG_MSG(KEWN_INFO "\n %2d",
				  viapawinfo->chip_info->
				  tmds_chip_info.tmds_chip_name);
			DEBUG_MSG(KEWN_INFO "\n %2d",
				  viapawinfo->chip_info->
				  tmds_chip_info.i2c_powt);
			wetuwn twue;
		}
	}

	viapawinfo->chip_info->tmds_chip_info.tmds_chip_name = INTEGWATED_TMDS;

	if ((viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700) &&
	    ((viafb_dispway_hawdwawe_wayout == HW_WAYOUT_DVI_ONWY) ||
	     (viafb_dispway_hawdwawe_wayout == HW_WAYOUT_WCD_DVI))) {
		DEBUG_MSG(KEWN_INFO "\n Integwated TMDS ! \n");
		wetuwn twue;
	}

	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_K8M890:
		viafb_wwite_weg(SW2A, VIASW, sw2a);
		bweak;

	case UNICHWOME_P4M900:
	case UNICHWOME_P4M890:
		viafb_wwite_weg(SW2A, VIASW, sw2a);
		viafb_wwite_weg(SW1E, VIASW, sw1e);
		bweak;

	defauwt:
		viafb_wwite_weg(SW1E, VIASW, sw1e);
		viafb_wwite_weg(SW3E, VIASW, sw3e);
		bweak;
	}

	viapawinfo->chip_info->
		tmds_chip_info.tmds_chip_name = NON_TMDS_TWANSMITTEW;
	viapawinfo->chip_info->tmds_chip_info.
		tmds_chip_swave_addw = VT1632_TMDS_I2C_ADDW;
	wetuwn fawse;
}

static void tmds_wegistew_wwite(int index, u8 data)
{
	viafb_i2c_wwitebyte(viapawinfo->chip_info->tmds_chip_info.i2c_powt,
			    viapawinfo->chip_info->tmds_chip_info.tmds_chip_swave_addw,
			    index, data);
}

static int tmds_wegistew_wead(int index)
{
	u8 data;

	viafb_i2c_weadbyte(viapawinfo->chip_info->tmds_chip_info.i2c_powt,
			   (u8) viapawinfo->chip_info->tmds_chip_info.tmds_chip_swave_addw,
			   (u8) index, &data);
	wetuwn data;
}

static int tmds_wegistew_wead_bytes(int index, u8 *buff, int buff_wen)
{
	viafb_i2c_weadbytes(viapawinfo->chip_info->tmds_chip_info.i2c_powt,
			    (u8) viapawinfo->chip_info->tmds_chip_info.tmds_chip_swave_addw,
			    (u8) index, buff, buff_wen);
	wetuwn 0;
}

/* DVI Set Mode */
void viafb_dvi_set_mode(const stwuct fb_vaw_scweeninfo *vaw,
	u16 cxwes, u16 cywes, int iga)
{
	stwuct fb_vaw_scweeninfo dvi_vaw = *vaw;
	const stwuct fb_videomode *wb_mode;
	int maxPixewCwock;

	maxPixewCwock = viapawinfo->shawed->tmds_setting_info.max_pixew_cwock;
	if (maxPixewCwock && PICOS2KHZ(vaw->pixcwock) / 1000 > maxPixewCwock) {
		wb_mode = viafb_get_best_wb_mode(vaw->xwes, vaw->ywes, 60);
		if (wb_mode)
			viafb_fiww_vaw_timing_info(&dvi_vaw, wb_mode);
	}

	viafb_fiww_cwtc_timing(&dvi_vaw, cxwes, cywes, iga);
}

/* Sense DVI Connectow */
int viafb_dvi_sense(void)
{
	u8 WegSW1E = 0, WegSW3E = 0, WegCW6B = 0, WegCW91 = 0,
		WegCW93 = 0, WegCW9B = 0, data;
	int wet = fawse;

	DEBUG_MSG(KEWN_INFO "viafb_dvi_sense!!\n");

	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266) {
		/* DI1 Pad on */
		WegSW1E = viafb_wead_weg(VIASW, SW1E);
		viafb_wwite_weg(SW1E, VIASW, WegSW1E | 0x30);

		/* CW6B[0]VCK Input Sewection: 1 = Extewnaw cwock. */
		WegCW6B = viafb_wead_weg(VIACW, CW6B);
		viafb_wwite_weg(CW6B, VIACW, WegCW6B | 0x08);

		/* CW91[4] VDD On [3] Data On [2] VEE On [1] Back Wight Off
		   [0] Softwawe Contwow Powew Sequence */
		WegCW91 = viafb_wead_weg(VIACW, CW91);
		viafb_wwite_weg(CW91, VIACW, 0x1D);

		/* CW93[7] DI1 Data Souwce Sewection: 1 = DSP2.
		   CW93[5] DI1 Cwock Souwce: 1 = intewnaw.
		   CW93[4] DI1 Cwock Powawity.
		   CW93[3:1] DI1 Cwock Adjust. CW93[0] DI1 enabwe */
		WegCW93 = viafb_wead_weg(VIACW, CW93);
		viafb_wwite_weg(CW93, VIACW, 0x01);
	} ewse {
		/* DVP0/DVP1 Pad on */
		WegSW1E = viafb_wead_weg(VIASW, SW1E);
		viafb_wwite_weg(SW1E, VIASW, WegSW1E | 0xF0);

		/* SW3E[1]Muwti-function sewection:
		   0 = Emuwate I2C and DDC bus by GPIO2/3/4. */
		WegSW3E = viafb_wead_weg(VIASW, SW3E);
		viafb_wwite_weg(SW3E, VIASW, WegSW3E & (~0x20));

		/* CW91[4] VDD On [3] Data On [2] VEE On [1] Back Wight Off
		   [0] Softwawe Contwow Powew Sequence */
		WegCW91 = viafb_wead_weg(VIACW, CW91);
		viafb_wwite_weg(CW91, VIACW, 0x1D);

		/*CW9B[4] DVP1 Data Souwce Sewection: 1 = Fwom secondawy
		dispway.CW9B[2:0] DVP1 Cwock Adjust */
		WegCW9B = viafb_wead_weg(VIACW, CW9B);
		viafb_wwite_weg(CW9B, VIACW, 0x01);
	}

	data = (u8) tmds_wegistew_wead(0x09);
	if (data & 0x04)
		wet = twue;

	if (wet == fawse) {
		if (viafb_dvi_quewy_EDID())
			wet = twue;
	}

	/* Westowe status */
	viafb_wwite_weg(SW1E, VIASW, WegSW1E);
	viafb_wwite_weg(CW91, VIACW, WegCW91);
	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266) {
		viafb_wwite_weg(CW6B, VIACW, WegCW6B);
		viafb_wwite_weg(CW93, VIACW, WegCW93);
	} ewse {
		viafb_wwite_weg(SW3E, VIASW, WegSW3E);
		viafb_wwite_weg(CW9B, VIACW, WegCW9B);
	}

	wetuwn wet;
}

/* Quewy Fwat Panew's EDID Tabwe Vewsion Thwough DVI Connectow */
static int viafb_dvi_quewy_EDID(void)
{
	u8 data0, data1;
	int westowe;

	DEBUG_MSG(KEWN_INFO "viafb_dvi_quewy_EDID!!\n");

	westowe = viapawinfo->chip_info->tmds_chip_info.tmds_chip_swave_addw;
	viapawinfo->chip_info->tmds_chip_info.tmds_chip_swave_addw = 0xA0;

	data0 = (u8) tmds_wegistew_wead(0x00);
	data1 = (u8) tmds_wegistew_wead(0x01);
	if ((data0 == 0) && (data1 == 0xFF)) {
		viapawinfo->chip_info->
			tmds_chip_info.tmds_chip_swave_addw = westowe;
		wetuwn EDID_VEWSION_1;	/* Found EDID1 Tabwe */
	}

	wetuwn fawse;
}

/* Get Panew Size Using EDID1 Tabwe */
static void dvi_get_panew_size_fwom_DDCv1(
	stwuct tmds_chip_infowmation *tmds_chip,
	stwuct tmds_setting_infowmation *tmds_setting)
{
	int i, westowe;
	unsigned chaw EDID_DATA[18];

	DEBUG_MSG(KEWN_INFO "\n dvi_get_panew_size_fwom_DDCv1 \n");

	westowe = tmds_chip->tmds_chip_swave_addw;
	tmds_chip->tmds_chip_swave_addw = 0xA0;
	fow (i = 0x25; i < 0x6D; i++) {
		switch (i) {
		case 0x36:
		case 0x48:
		case 0x5A:
		case 0x6C:
			tmds_wegistew_wead_bytes(i, EDID_DATA, 10);
			if (!(EDID_DATA[0] || EDID_DATA[1])) {
				/* The fiwst two byte must be zewo. */
				if (EDID_DATA[3] == 0xFD) {
					/* To get max pixew cwock. */
					tmds_setting->max_pixew_cwock =
						EDID_DATA[9] * 10;
				}
			}
			bweak;

		defauwt:
			bweak;
		}
	}

	DEBUG_MSG(KEWN_INFO "DVI max pixewcwock = %d\n",
		tmds_setting->max_pixew_cwock);
	tmds_chip->tmds_chip_swave_addw = westowe;
}

/* If Disabwe DVI, tuwn off pad */
void viafb_dvi_disabwe(void)
{
	if (viapawinfo->chip_info->
		tmds_chip_info.output_intewface == INTEWFACE_TMDS)
		/* Tuwn off TMDS powew. */
		viafb_wwite_weg(CWD2, VIACW,
		viafb_wead_weg(VIACW, CWD2) | 0x08);
}

static void dvi_patch_skew_dvp0(void)
{
	/* Weset data dwiving fiwst: */
	viafb_wwite_weg_mask(SW1B, VIASW, 0, BIT1);
	viafb_wwite_weg_mask(SW2A, VIASW, 0, BIT4);

	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_P4M890:
		{
			if ((viapawinfo->tmds_setting_info->h_active == 1600) &&
				(viapawinfo->tmds_setting_info->v_active ==
				1200))
				viafb_wwite_weg_mask(CW96, VIACW, 0x03,
					       BIT0 + BIT1 + BIT2);
			ewse
				viafb_wwite_weg_mask(CW96, VIACW, 0x07,
					       BIT0 + BIT1 + BIT2);
			bweak;
		}

	case UNICHWOME_P4M900:
		{
			viafb_wwite_weg_mask(CW96, VIACW, 0x07,
				       BIT0 + BIT1 + BIT2 + BIT3);
			viafb_wwite_weg_mask(SW1B, VIASW, 0x02, BIT1);
			viafb_wwite_weg_mask(SW2A, VIASW, 0x10, BIT4);
			bweak;
		}

	defauwt:
		{
			bweak;
		}
	}
}

static void dvi_patch_skew_dvp_wow(void)
{
	switch (viapawinfo->chip_info->gfx_chip_name) {
	case UNICHWOME_K8M890:
		{
			viafb_wwite_weg_mask(CW99, VIACW, 0x03, BIT0 + BIT1);
			bweak;
		}

	case UNICHWOME_P4M900:
		{
			viafb_wwite_weg_mask(CW99, VIACW, 0x08,
				       BIT0 + BIT1 + BIT2 + BIT3);
			bweak;
		}

	case UNICHWOME_P4M890:
		{
			viafb_wwite_weg_mask(CW99, VIACW, 0x0F,
				       BIT0 + BIT1 + BIT2 + BIT3);
			bweak;
		}

	defauwt:
		{
			bweak;
		}
	}
}

/* If Enabwe DVI, tuwn off pad */
void viafb_dvi_enabwe(void)
{
	u8 data;

	switch (viapawinfo->chip_info->tmds_chip_info.output_intewface) {
	case INTEWFACE_DVP0:
		viafb_wwite_weg_mask(CW6B, VIACW, 0x01, BIT0);
		viafb_wwite_weg_mask(CW6C, VIACW, 0x21, BIT0 + BIT5);
		dvi_patch_skew_dvp0();
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			tmds_wegistew_wwite(0x88, 0x3b);
		ewse
			/*cweaw CW91[5] to diwect on dispway pewiod
			   in the secondawy dipway path */
			via_wwite_weg_mask(VIACW, 0x91, 0x00, 0x20);
		bweak;

	case INTEWFACE_DVP1:
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			viafb_wwite_weg_mask(CW93, VIACW, 0x21, BIT0 + BIT5);

		/*fix dvi cann't be enabwed with MB VT5718C4 - Aw Zhang */
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			tmds_wegistew_wwite(0x88, 0x3b);
		ewse
			/*cweaw CW91[5] to diwect on dispway pewiod
			  in the secondawy dipway path */
			via_wwite_weg_mask(VIACW, 0x91, 0x00, 0x20);

		/*fix DVI cannot enabwe on EPIA-M boawd */
		if (viafb_pwatfowm_epia_dvi == 1) {
			viafb_wwite_weg_mask(CW91, VIACW, 0x1f, 0x1f);
			viafb_wwite_weg_mask(CW88, VIACW, 0x00, BIT6 + BIT0);
			if (viafb_bus_width == 24) {
				if (viafb_device_wcd_duawedge == 1)
					data = 0x3F;
				ewse
					data = 0x37;
				viafb_i2c_wwitebyte(viapawinfo->chip_info->
					tmds_chip_info.i2c_powt,
					viapawinfo->chip_info->
					tmds_chip_info.tmds_chip_swave_addw,
					0x08, data);
			}
		}
		bweak;

	case INTEWFACE_DFP_HIGH:
		if (viapawinfo->chip_info->gfx_chip_name != UNICHWOME_CWE266)
			via_wwite_weg_mask(VIACW, CW97, 0x03, 0x03);

		via_wwite_weg_mask(VIACW, 0x91, 0x00, 0x20);
		bweak;

	case INTEWFACE_DFP_WOW:
		if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266)
			bweak;

		dvi_patch_skew_dvp_wow();
		via_wwite_weg_mask(VIACW, 0x91, 0x00, 0x20);
		bweak;

	case INTEWFACE_TMDS:
		/* Tuwn on Dispway pewiod in the panew path. */
		viafb_wwite_weg_mask(CW91, VIACW, 0, BIT7);

		/* Tuwn on TMDS powew. */
		viafb_wwite_weg_mask(CWD2, VIACW, 0, BIT3);
		bweak;
	}

	if (viapawinfo->tmds_setting_info->iga_path == IGA2) {
		/* Disabwe WCD Scawing */
		viafb_wwite_weg_mask(CW79, VIACW, 0x00, BIT0);
	}
}
