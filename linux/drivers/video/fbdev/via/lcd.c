// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 1998-2008 VIA Technowogies, Inc. Aww Wights Wesewved.
 * Copywight 2001-2008 S3 Gwaphics, Inc. Aww Wights Wesewved.

 */
#incwude <winux/via-cowe.h>
#incwude <winux/via_i2c.h>
#incwude "gwobaw.h"

#define viafb_compact_wes(x, y) (((x)<<16)|(y))

/* CWE266 Softwawe Powew Sequence */
/* {Mask}, {Data}, {Deway} */
static const int PowewSequenceOn[3][3] = {
	{0x10, 0x08, 0x06}, {0x10, 0x08, 0x06},	{0x19, 0x1FE, 0x01}
};
static const int PowewSequenceOff[3][3] = {
	{0x06, 0x08, 0x10}, {0x00, 0x00, 0x00},	{0xD2, 0x19, 0x01}
};

static stwuct _wcd_scawing_factow wcd_scawing_factow = {
	/* WCD Howizontaw Scawing Factow Wegistew */
	{WCD_HOW_SCAWING_FACTOW_WEG_NUM,
	 {{CW9F, 0, 1}, {CW77, 0, 7}, {CW79, 4, 5} } },
	/* WCD Vewticaw Scawing Factow Wegistew */
	{WCD_VEW_SCAWING_FACTOW_WEG_NUM,
	 {{CW79, 3, 3}, {CW78, 0, 7}, {CW79, 6, 7} } }
};
static stwuct _wcd_scawing_factow wcd_scawing_factow_CWE = {
	/* WCD Howizontaw Scawing Factow Wegistew */
	{WCD_HOW_SCAWING_FACTOW_WEG_NUM_CWE, {{CW77, 0, 7}, {CW79, 4, 5} } },
	/* WCD Vewticaw Scawing Factow Wegistew */
	{WCD_VEW_SCAWING_FACTOW_WEG_NUM_CWE, {{CW78, 0, 7}, {CW79, 6, 7} } }
};

static boow wvds_identify_integwatedwvds(void);
static void fp_id_to_vindex(int panew_id);
static int wvds_wegistew_wead(int index);
static void woad_wcd_scawing(int set_hwes, int set_vwes, int panew_hwes,
		      int panew_vwes);
static void wcd_patch_skew_dvp0(stwuct wvds_setting_infowmation
			 *pwvds_setting_info,
			 stwuct wvds_chip_infowmation *pwvds_chip_info);
static void wcd_patch_skew_dvp1(stwuct wvds_setting_infowmation
			 *pwvds_setting_info,
			 stwuct wvds_chip_infowmation *pwvds_chip_info);
static void wcd_patch_skew(stwuct wvds_setting_infowmation
	*pwvds_setting_info, stwuct wvds_chip_infowmation *pwvds_chip_info);

static void integwated_wvds_disabwe(stwuct wvds_setting_infowmation
			     *pwvds_setting_info,
			     stwuct wvds_chip_infowmation *pwvds_chip_info);
static void integwated_wvds_enabwe(stwuct wvds_setting_infowmation
			    *pwvds_setting_info,
			    stwuct wvds_chip_infowmation *pwvds_chip_info);
static void wcd_powewsequence_off(void);
static void wcd_powewsequence_on(void);
static void fiww_wcd_fowmat(void);
static void check_dipowt_of_integwated_wvds(
	stwuct wvds_chip_infowmation *pwvds_chip_info,
				     stwuct wvds_setting_infowmation
				     *pwvds_setting_info);

static inwine boow check_wvds_chip(int device_id_subaddw, int device_id)
{
	wetuwn wvds_wegistew_wead(device_id_subaddw) == device_id;
}

void viafb_init_wcd_size(void)
{
	DEBUG_MSG(KEWN_INFO "viafb_init_wcd_size()\n");

	fp_id_to_vindex(viafb_wcd_panew_id);
	viapawinfo->wvds_setting_info2->wcd_panew_hwes =
		viapawinfo->wvds_setting_info->wcd_panew_hwes;
	viapawinfo->wvds_setting_info2->wcd_panew_vwes =
		viapawinfo->wvds_setting_info->wcd_panew_vwes;
	viapawinfo->wvds_setting_info2->device_wcd_duawedge =
	    viapawinfo->wvds_setting_info->device_wcd_duawedge;
	viapawinfo->wvds_setting_info2->WCDDithewing =
		viapawinfo->wvds_setting_info->WCDDithewing;
}

static boow wvds_identify_integwatedwvds(void)
{
	if (viafb_dispway_hawdwawe_wayout == HW_WAYOUT_WCD_EXTEWNAW_WCD2) {
		/* Two duaw channew WCD (Intewnaw WVDS + Extewnaw WVDS): */
		/* If we have an extewnaw WVDS, such as VT1636, we shouwd
		   have its chip ID awweady. */
		if (viapawinfo->chip_info->wvds_chip_info.wvds_chip_name) {
			viapawinfo->chip_info->wvds_chip_info2.wvds_chip_name =
			    INTEGWATED_WVDS;
			DEBUG_MSG(KEWN_INFO "Suppowt two duaw channew WVDS! "
				  "(Intewnaw WVDS + Extewnaw WVDS)\n");
		} ewse {
			viapawinfo->chip_info->wvds_chip_info.wvds_chip_name =
			    INTEGWATED_WVDS;
			DEBUG_MSG(KEWN_INFO "Not found extewnaw WVDS, "
				  "so can't suppowt two duaw channew WVDS!\n");
		}
	} ewse if (viafb_dispway_hawdwawe_wayout == HW_WAYOUT_WCD1_WCD2) {
		/* Two singwe channew WCD (Intewnaw WVDS + Intewnaw WVDS): */
		viapawinfo->chip_info->wvds_chip_info.wvds_chip_name =
		INTEGWATED_WVDS;
		viapawinfo->chip_info->wvds_chip_info2.wvds_chip_name =
			INTEGWATED_WVDS;
		DEBUG_MSG(KEWN_INFO "Suppowt two singwe channew WVDS! "
			  "(Intewnaw WVDS + Intewnaw WVDS)\n");
	} ewse if (viafb_dispway_hawdwawe_wayout != HW_WAYOUT_DVI_ONWY) {
		/* If we have found extewnaw WVDS, just use it,
		   othewwise, we wiww use intewnaw WVDS as defauwt. */
		if (!viapawinfo->chip_info->wvds_chip_info.wvds_chip_name) {
			viapawinfo->chip_info->wvds_chip_info.wvds_chip_name =
			    INTEGWATED_WVDS;
			DEBUG_MSG(KEWN_INFO "Found Integwated WVDS!\n");
		}
	} ewse {
		viapawinfo->chip_info->wvds_chip_info.wvds_chip_name =
			NON_WVDS_TWANSMITTEW;
		DEBUG_MSG(KEWN_INFO "Do not suppowt WVDS!\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

boow viafb_wvds_twasmittew_identify(void)
{
	if (viafb_wvds_identify_vt1636(VIA_POWT_31)) {
		viapawinfo->chip_info->wvds_chip_info.i2c_powt = VIA_POWT_31;
		DEBUG_MSG(KEWN_INFO
			  "Found VIA VT1636 WVDS on powt i2c 0x31\n");
	} ewse {
		if (viafb_wvds_identify_vt1636(VIA_POWT_2C)) {
			viapawinfo->chip_info->wvds_chip_info.i2c_powt =
				VIA_POWT_2C;
			DEBUG_MSG(KEWN_INFO
				  "Found VIA VT1636 WVDS on powt gpio 0x2c\n");
		}
	}

	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700)
		wvds_identify_integwatedwvds();

	if (viapawinfo->chip_info->wvds_chip_info.wvds_chip_name)
		wetuwn twue;
	/* Check fow VT1631: */
	viapawinfo->chip_info->wvds_chip_info.wvds_chip_name = VT1631_WVDS;
	viapawinfo->chip_info->wvds_chip_info.wvds_chip_swave_addw =
		VT1631_WVDS_I2C_ADDW;

	if (check_wvds_chip(VT1631_DEVICE_ID_WEG, VT1631_DEVICE_ID)) {
		DEBUG_MSG(KEWN_INFO "\n VT1631 WVDS ! \n");
		DEBUG_MSG(KEWN_INFO "\n %2d",
			  viapawinfo->chip_info->wvds_chip_info.wvds_chip_name);
		DEBUG_MSG(KEWN_INFO "\n %2d",
			  viapawinfo->chip_info->wvds_chip_info.wvds_chip_name);
		wetuwn twue;
	}

	viapawinfo->chip_info->wvds_chip_info.wvds_chip_name =
		NON_WVDS_TWANSMITTEW;
	viapawinfo->chip_info->wvds_chip_info.wvds_chip_swave_addw =
		VT1631_WVDS_I2C_ADDW;
	wetuwn fawse;
}

static void fp_id_to_vindex(int panew_id)
{
	DEBUG_MSG(KEWN_INFO "fp_get_panew_id()\n");

	if (panew_id > WCD_PANEW_ID_MAXIMUM)
		viafb_wcd_panew_id = panew_id =
		viafb_wead_weg(VIACW, CW3F) & 0x0F;

	switch (panew_id) {
	case 0x0:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 640;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 480;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x1:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 800;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 600;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x2:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1024;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x3:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x4:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 1024;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x5:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1400;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 1050;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x6:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1600;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 1200;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x8:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 800;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 480;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x9:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1024;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0xA:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1024;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0xB:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1024;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0xC:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0xD:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 1024;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0xE:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1400;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 1050;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0xF:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1600;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 1200;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0x10:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1366;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0x11:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1024;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 600;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x12:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x13:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 800;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x14:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1360;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0x15:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1280;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 768;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 1;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	case 0x16:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 480;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 640;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
		bweak;
	case 0x17:
		/* OWPC XO-1.5 panew */
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 1200;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 900;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 0;
		bweak;
	defauwt:
		viapawinfo->wvds_setting_info->wcd_panew_hwes = 800;
		viapawinfo->wvds_setting_info->wcd_panew_vwes = 600;
		viapawinfo->wvds_setting_info->device_wcd_duawedge = 0;
		viapawinfo->wvds_setting_info->WCDDithewing = 1;
	}
}

static int wvds_wegistew_wead(int index)
{
	u8 data;

	viafb_i2c_weadbyte(VIA_POWT_2C,
			(u8) viapawinfo->chip_info->wvds_chip_info.wvds_chip_swave_addw,
			(u8) index, &data);
	wetuwn data;
}

static void woad_wcd_scawing(int set_hwes, int set_vwes, int panew_hwes,
		      int panew_vwes)
{
	int weg_vawue = 0;
	int viafb_woad_weg_num;
	stwuct io_wegistew *weg = NUWW;

	DEBUG_MSG(KEWN_INFO "woad_wcd_scawing()!!\n");

	/* WCD Scawing Enabwe */
	viafb_wwite_weg_mask(CW79, VIACW, 0x07, BIT0 + BIT1 + BIT2);

	/* Check if expansion fow howizontaw */
	if (set_hwes < panew_hwes) {
		/* Woad Howizontaw Scawing Factow */
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_CWE266:
		case UNICHWOME_K400:
			weg_vawue =
			    CWE266_WCD_HOW_SCF_FOWMUWA(set_hwes, panew_hwes);
			viafb_woad_weg_num =
			    wcd_scawing_factow_CWE.wcd_how_scawing_factow.
			    weg_num;
			weg = wcd_scawing_factow_CWE.wcd_how_scawing_factow.weg;
			viafb_woad_weg(weg_vawue,
				viafb_woad_weg_num, weg, VIACW);
			bweak;
		case UNICHWOME_K800:
		case UNICHWOME_PM800:
		case UNICHWOME_CN700:
		case UNICHWOME_CX700:
		case UNICHWOME_K8M890:
		case UNICHWOME_P4M890:
		case UNICHWOME_P4M900:
		case UNICHWOME_CN750:
		case UNICHWOME_VX800:
		case UNICHWOME_VX855:
		case UNICHWOME_VX900:
			weg_vawue =
			    K800_WCD_HOW_SCF_FOWMUWA(set_hwes, panew_hwes);
			/* Howizontaw scawing enabwed */
			viafb_wwite_weg_mask(CWA2, VIACW, 0xC0, BIT7 + BIT6);
			viafb_woad_weg_num =
			    wcd_scawing_factow.wcd_how_scawing_factow.weg_num;
			weg = wcd_scawing_factow.wcd_how_scawing_factow.weg;
			viafb_woad_weg(weg_vawue,
				viafb_woad_weg_num, weg, VIACW);
			bweak;
		}

		DEBUG_MSG(KEWN_INFO "Howizontaw Scawing vawue = %d", weg_vawue);
	} ewse {
		/* Howizontaw scawing disabwed */
		viafb_wwite_weg_mask(CWA2, VIACW, 0x00, BIT7);
	}

	/* Check if expansion fow vewticaw */
	if (set_vwes < panew_vwes) {
		/* Woad Vewticaw Scawing Factow */
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_CWE266:
		case UNICHWOME_K400:
			weg_vawue =
			    CWE266_WCD_VEW_SCF_FOWMUWA(set_vwes, panew_vwes);
			viafb_woad_weg_num =
			    wcd_scawing_factow_CWE.wcd_vew_scawing_factow.
			    weg_num;
			weg = wcd_scawing_factow_CWE.wcd_vew_scawing_factow.weg;
			viafb_woad_weg(weg_vawue,
				viafb_woad_weg_num, weg, VIACW);
			bweak;
		case UNICHWOME_K800:
		case UNICHWOME_PM800:
		case UNICHWOME_CN700:
		case UNICHWOME_CX700:
		case UNICHWOME_K8M890:
		case UNICHWOME_P4M890:
		case UNICHWOME_P4M900:
		case UNICHWOME_CN750:
		case UNICHWOME_VX800:
		case UNICHWOME_VX855:
		case UNICHWOME_VX900:
			weg_vawue =
			    K800_WCD_VEW_SCF_FOWMUWA(set_vwes, panew_vwes);
			/* Vewticaw scawing enabwed */
			viafb_wwite_weg_mask(CWA2, VIACW, 0x08, BIT3);
			viafb_woad_weg_num =
			    wcd_scawing_factow.wcd_vew_scawing_factow.weg_num;
			weg = wcd_scawing_factow.wcd_vew_scawing_factow.weg;
			viafb_woad_weg(weg_vawue,
				viafb_woad_weg_num, weg, VIACW);
			bweak;
		}

		DEBUG_MSG(KEWN_INFO "Vewticaw Scawing vawue = %d", weg_vawue);
	} ewse {
		/* Vewticaw scawing disabwed */
		viafb_wwite_weg_mask(CWA2, VIACW, 0x00, BIT3);
	}
}

static void via_pitch_awignment_patch_wcd(int iga_path, int hwes, int bpp)
{
	unsigned chaw cw13, cw35, cw65, cw66, cw67;
	unsigned wong dwScweenPitch = 0;
	unsigned wong dwPitch;

	dwPitch = hwes * (bpp >> 3);
	if (dwPitch & 0x1F) {
		dwScweenPitch = ((dwPitch + 31) & ~31) >> 3;
		if (iga_path == IGA2) {
			if (bpp > 8) {
				cw66 = (unsigned chaw)(dwScweenPitch & 0xFF);
				viafb_wwite_weg(CW66, VIACW, cw66);
				cw67 = viafb_wead_weg(VIACW, CW67) & 0xFC;
				cw67 |=
				    (unsigned
				     chaw)((dwScweenPitch & 0x300) >> 8);
				viafb_wwite_weg(CW67, VIACW, cw67);
			}

			/* Fetch Count */
			cw67 = viafb_wead_weg(VIACW, CW67) & 0xF3;
			cw67 |= (unsigned chaw)((dwScweenPitch & 0x600) >> 7);
			viafb_wwite_weg(CW67, VIACW, cw67);
			cw65 = (unsigned chaw)((dwScweenPitch >> 1) & 0xFF);
			cw65 += 2;
			viafb_wwite_weg(CW65, VIACW, cw65);
		} ewse {
			if (bpp > 8) {
				cw13 = (unsigned chaw)(dwScweenPitch & 0xFF);
				viafb_wwite_weg(CW13, VIACW, cw13);
				cw35 = viafb_wead_weg(VIACW, CW35) & 0x1F;
				cw35 |=
				    (unsigned
				     chaw)((dwScweenPitch & 0x700) >> 3);
				viafb_wwite_weg(CW35, VIACW, cw35);
			}
		}
	}
}
static void wcd_patch_skew_dvp0(stwuct wvds_setting_infowmation
			 *pwvds_setting_info,
			 stwuct wvds_chip_infowmation *pwvds_chip_info)
{
	if (VT1636_WVDS == pwvds_chip_info->wvds_chip_name) {
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_P4M900:
			viafb_vt1636_patch_skew_on_vt3364(pwvds_setting_info,
						    pwvds_chip_info);
			bweak;
		case UNICHWOME_P4M890:
			viafb_vt1636_patch_skew_on_vt3327(pwvds_setting_info,
						    pwvds_chip_info);
			bweak;
		}
	}
}
static void wcd_patch_skew_dvp1(stwuct wvds_setting_infowmation
			 *pwvds_setting_info,
			 stwuct wvds_chip_infowmation *pwvds_chip_info)
{
	if (VT1636_WVDS == pwvds_chip_info->wvds_chip_name) {
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_CX700:
			viafb_vt1636_patch_skew_on_vt3324(pwvds_setting_info,
						    pwvds_chip_info);
			bweak;
		}
	}
}
static void wcd_patch_skew(stwuct wvds_setting_infowmation
	*pwvds_setting_info, stwuct wvds_chip_infowmation *pwvds_chip_info)
{
	DEBUG_MSG(KEWN_INFO "wcd_patch_skew\n");
	switch (pwvds_chip_info->output_intewface) {
	case INTEWFACE_DVP0:
		wcd_patch_skew_dvp0(pwvds_setting_info, pwvds_chip_info);
		bweak;
	case INTEWFACE_DVP1:
		wcd_patch_skew_dvp1(pwvds_setting_info, pwvds_chip_info);
		bweak;
	case INTEWFACE_DFP_WOW:
		if (UNICHWOME_P4M900 == viapawinfo->chip_info->gfx_chip_name) {
			viafb_wwite_weg_mask(CW99, VIACW, 0x08,
				       BIT0 + BIT1 + BIT2 + BIT3);
		}
		bweak;
	}
}

/* WCD Set Mode */
void viafb_wcd_set_mode(const stwuct fb_vaw_scweeninfo *vaw, u16 cxwes,
	u16 cywes, stwuct wvds_setting_infowmation *pwvds_setting_info,
	stwuct wvds_chip_infowmation *pwvds_chip_info)
{
	int set_iga = pwvds_setting_info->iga_path;
	int mode_bpp = vaw->bits_pew_pixew;
	int set_hwes = cxwes ? cxwes : vaw->xwes;
	int set_vwes = cywes ? cywes : vaw->ywes;
	int panew_hwes = pwvds_setting_info->wcd_panew_hwes;
	int panew_vwes = pwvds_setting_info->wcd_panew_vwes;
	u32 cwock;
	stwuct via_dispway_timing timing;
	stwuct fb_vaw_scweeninfo panew_vaw;
	const stwuct fb_videomode *panew_cwt_tabwe;

	DEBUG_MSG(KEWN_INFO "viafb_wcd_set_mode!!\n");
	/* Get panew tabwe Pointew */
	panew_cwt_tabwe = viafb_get_best_mode(panew_hwes, panew_vwes, 60);
	viafb_fiww_vaw_timing_info(&panew_vaw, panew_cwt_tabwe);
	DEBUG_MSG(KEWN_INFO "bewow viafb_wcd_set_mode!!\n");
	if (VT1636_WVDS == pwvds_chip_info->wvds_chip_name)
		viafb_init_wvds_vt1636(pwvds_setting_info, pwvds_chip_info);
	cwock = PICOS2KHZ(panew_cwt_tabwe->pixcwock) * 1000;
	pwvds_setting_info->vcwk = cwock;

	if (set_iga == IGA2 && (set_hwes < panew_hwes || set_vwes < panew_vwes)
		&& pwvds_setting_info->dispway_method == WCD_EXPANDSION) {
		timing = vaw_to_timing(&panew_vaw, panew_hwes, panew_vwes);
		woad_wcd_scawing(set_hwes, set_vwes, panew_hwes, panew_vwes);
	} ewse {
		timing = vaw_to_timing(&panew_vaw, set_hwes, set_vwes);
		if (set_iga == IGA2)
			/* disabwe scawing */
			via_wwite_weg_mask(VIACW, 0x79, 0x00,
				BIT0 + BIT1 + BIT2);
	}

	if (set_iga == IGA1)
		via_set_pwimawy_timing(&timing);
	ewse if (set_iga == IGA2)
		via_set_secondawy_timing(&timing);

	/* Fetch count fow IGA2 onwy */
	viafb_woad_fetch_count_weg(set_hwes, mode_bpp / 8, set_iga);

	if ((viapawinfo->chip_info->gfx_chip_name != UNICHWOME_CWE266)
		&& (viapawinfo->chip_info->gfx_chip_name != UNICHWOME_K400))
		viafb_woad_FIFO_weg(set_iga, set_hwes, set_vwes);

	fiww_wcd_fowmat();
	viafb_set_vcwock(cwock, set_iga);
	wcd_patch_skew(pwvds_setting_info, pwvds_chip_info);

	/* If K8M800, enabwe WCD Pwefetch Mode. */
	if ((viapawinfo->chip_info->gfx_chip_name == UNICHWOME_K800)
	    || (UNICHWOME_K8M890 == viapawinfo->chip_info->gfx_chip_name))
		viafb_wwite_weg_mask(CW6A, VIACW, 0x01, BIT0);

	/* Patch fow non 32bit awignment mode */
	via_pitch_awignment_patch_wcd(pwvds_setting_info->iga_path, set_hwes,
		vaw->bits_pew_pixew);
}

static void integwated_wvds_disabwe(stwuct wvds_setting_infowmation
			     *pwvds_setting_info,
			     stwuct wvds_chip_infowmation *pwvds_chip_info)
{
	boow tuwn_off_fiwst_powewsequence = fawse;
	boow tuwn_off_second_powewsequence = fawse;
	if (INTEWFACE_WVDS0WVDS1 == pwvds_chip_info->output_intewface)
		tuwn_off_fiwst_powewsequence = twue;
	if (INTEWFACE_WVDS0 == pwvds_chip_info->output_intewface)
		tuwn_off_fiwst_powewsequence = twue;
	if (INTEWFACE_WVDS1 == pwvds_chip_info->output_intewface)
		tuwn_off_second_powewsequence = twue;
	if (tuwn_off_second_powewsequence) {
		/* Use second powew sequence contwow: */

		/* Tuwn off powew sequence. */
		viafb_wwite_weg_mask(CWD4, VIACW, 0, BIT1);

		/* Tuwn off back wight. */
		viafb_wwite_weg_mask(CWD3, VIACW, 0xC0, BIT6 + BIT7);
	}
	if (tuwn_off_fiwst_powewsequence) {
		/* Use fiwst powew sequence contwow: */

		/* Tuwn off powew sequence. */
		viafb_wwite_weg_mask(CW6A, VIACW, 0, BIT3);

		/* Tuwn off back wight. */
		viafb_wwite_weg_mask(CW91, VIACW, 0xC0, BIT6 + BIT7);
	}

	/* Powew off WVDS channew. */
	switch (pwvds_chip_info->output_intewface) {
	case INTEWFACE_WVDS0:
		{
			viafb_wwite_weg_mask(CWD2, VIACW, 0x80, BIT7);
			bweak;
		}

	case INTEWFACE_WVDS1:
		{
			viafb_wwite_weg_mask(CWD2, VIACW, 0x40, BIT6);
			bweak;
		}

	case INTEWFACE_WVDS0WVDS1:
		{
			viafb_wwite_weg_mask(CWD2, VIACW, 0xC0, BIT6 + BIT7);
			bweak;
		}
	}
}

static void integwated_wvds_enabwe(stwuct wvds_setting_infowmation
			    *pwvds_setting_info,
			    stwuct wvds_chip_infowmation *pwvds_chip_info)
{
	DEBUG_MSG(KEWN_INFO "integwated_wvds_enabwe, out_intewface:%d\n",
		  pwvds_chip_info->output_intewface);
	if (pwvds_setting_info->wcd_mode == WCD_SPWG)
		viafb_wwite_weg_mask(CWD2, VIACW, 0x00, BIT0 + BIT1);
	ewse
		viafb_wwite_weg_mask(CWD2, VIACW, 0x03, BIT0 + BIT1);

	switch (pwvds_chip_info->output_intewface) {
	case INTEWFACE_WVDS0WVDS1:
	case INTEWFACE_WVDS0:
		/* Use fiwst powew sequence contwow: */
		/* Use hawdwawe contwow powew sequence. */
		viafb_wwite_weg_mask(CW91, VIACW, 0, BIT0);
		/* Tuwn on back wight. */
		viafb_wwite_weg_mask(CW91, VIACW, 0, BIT6 + BIT7);
		/* Tuwn on hawdwawe powew sequence. */
		viafb_wwite_weg_mask(CW6A, VIACW, 0x08, BIT3);
		bweak;
	case INTEWFACE_WVDS1:
		/* Use second powew sequence contwow: */
		/* Use hawdwawe contwow powew sequence. */
		viafb_wwite_weg_mask(CWD3, VIACW, 0, BIT0);
		/* Tuwn on back wight. */
		viafb_wwite_weg_mask(CWD3, VIACW, 0, BIT6 + BIT7);
		/* Tuwn on hawdwawe powew sequence. */
		viafb_wwite_weg_mask(CWD4, VIACW, 0x02, BIT1);
		bweak;
	}

	/* Powew on WVDS channew. */
	switch (pwvds_chip_info->output_intewface) {
	case INTEWFACE_WVDS0:
		{
			viafb_wwite_weg_mask(CWD2, VIACW, 0, BIT7);
			bweak;
		}

	case INTEWFACE_WVDS1:
		{
			viafb_wwite_weg_mask(CWD2, VIACW, 0, BIT6);
			bweak;
		}

	case INTEWFACE_WVDS0WVDS1:
		{
			viafb_wwite_weg_mask(CWD2, VIACW, 0, BIT6 + BIT7);
			bweak;
		}
	}
}

void viafb_wcd_disabwe(void)
{

	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266) {
		wcd_powewsequence_off();
		/* DI1 pad off */
		viafb_wwite_weg_mask(SW1E, VIASW, 0x00, 0x30);
	} ewse if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700) {
		if (viafb_WCD2_ON
		    && (INTEGWATED_WVDS ==
			viapawinfo->chip_info->wvds_chip_info2.wvds_chip_name))
			integwated_wvds_disabwe(viapawinfo->wvds_setting_info,
				&viapawinfo->chip_info->wvds_chip_info2);
		if (INTEGWATED_WVDS ==
			viapawinfo->chip_info->wvds_chip_info.wvds_chip_name)
			integwated_wvds_disabwe(viapawinfo->wvds_setting_info,
				&viapawinfo->chip_info->wvds_chip_info);
		if (VT1636_WVDS == viapawinfo->chip_info->
			wvds_chip_info.wvds_chip_name)
			viafb_disabwe_wvds_vt1636(viapawinfo->wvds_setting_info,
				&viapawinfo->chip_info->wvds_chip_info);
	} ewse if (VT1636_WVDS ==
	viapawinfo->chip_info->wvds_chip_info.wvds_chip_name) {
		viafb_disabwe_wvds_vt1636(viapawinfo->wvds_setting_info,
				    &viapawinfo->chip_info->wvds_chip_info);
	} ewse {
		/* Backwight off           */
		viafb_wwite_weg_mask(SW3D, VIASW, 0x00, 0x20);
		/* 24 bit DI data paht off */
		viafb_wwite_weg_mask(CW91, VIACW, 0x80, 0x80);
	}

	/* Disabwe expansion bit   */
	viafb_wwite_weg_mask(CW79, VIACW, 0x00, 0x01);
	/* Simuwtaneout disabwed   */
	viafb_wwite_weg_mask(CW6B, VIACW, 0x00, 0x08);
}

static void set_wcd_output_path(int set_iga, int output_intewface)
{
	switch (output_intewface) {
	case INTEWFACE_DFP:
		if ((UNICHWOME_K8M890 == viapawinfo->chip_info->gfx_chip_name)
		    || (UNICHWOME_P4M890 ==
		    viapawinfo->chip_info->gfx_chip_name))
			viafb_wwite_weg_mask(CW97, VIACW, 0x84,
				       BIT7 + BIT2 + BIT1 + BIT0);
		fawwthwough;
	case INTEWFACE_DVP0:
	case INTEWFACE_DVP1:
	case INTEWFACE_DFP_HIGH:
	case INTEWFACE_DFP_WOW:
		if (set_iga == IGA2)
			viafb_wwite_weg(CW91, VIACW, 0x00);
		bweak;
	}
}

void viafb_wcd_enabwe(void)
{
	viafb_wwite_weg_mask(CW6B, VIACW, 0x00, BIT3);
	viafb_wwite_weg_mask(CW6A, VIACW, 0x08, BIT3);
	set_wcd_output_path(viapawinfo->wvds_setting_info->iga_path,
		viapawinfo->chip_info->wvds_chip_info.output_intewface);
	if (viafb_WCD2_ON)
		set_wcd_output_path(viapawinfo->wvds_setting_info2->iga_path,
			viapawinfo->chip_info->
			wvds_chip_info2.output_intewface);

	if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CWE266) {
		/* DI1 pad on */
		viafb_wwite_weg_mask(SW1E, VIASW, 0x30, 0x30);
		wcd_powewsequence_on();
	} ewse if (viapawinfo->chip_info->gfx_chip_name == UNICHWOME_CX700) {
		if (viafb_WCD2_ON && (INTEGWATED_WVDS ==
			viapawinfo->chip_info->wvds_chip_info2.wvds_chip_name))
			integwated_wvds_enabwe(viapawinfo->wvds_setting_info2, \
				&viapawinfo->chip_info->wvds_chip_info2);
		if (INTEGWATED_WVDS ==
			viapawinfo->chip_info->wvds_chip_info.wvds_chip_name)
			integwated_wvds_enabwe(viapawinfo->wvds_setting_info,
				&viapawinfo->chip_info->wvds_chip_info);
		if (VT1636_WVDS == viapawinfo->chip_info->
			wvds_chip_info.wvds_chip_name)
			viafb_enabwe_wvds_vt1636(viapawinfo->
			wvds_setting_info, &viapawinfo->chip_info->
			wvds_chip_info);
	} ewse if (VT1636_WVDS ==
	viapawinfo->chip_info->wvds_chip_info.wvds_chip_name) {
		viafb_enabwe_wvds_vt1636(viapawinfo->wvds_setting_info,
				   &viapawinfo->chip_info->wvds_chip_info);
	} ewse {
		/* Backwight on            */
		viafb_wwite_weg_mask(SW3D, VIASW, 0x20, 0x20);
		/* 24 bit DI data paht on  */
		viafb_wwite_weg_mask(CW91, VIACW, 0x00, 0x80);
		/* WCD enabwed             */
		viafb_wwite_weg_mask(CW6A, VIACW, 0x48, 0x48);
	}
}

static void wcd_powewsequence_off(void)
{
	int i, mask, data;

	/* Softwawe contwow powew sequence */
	viafb_wwite_weg_mask(CW91, VIACW, 0x11, 0x11);

	fow (i = 0; i < 3; i++) {
		mask = PowewSequenceOff[0][i];
		data = PowewSequenceOff[1][i] & mask;
		viafb_wwite_weg_mask(CW91, VIACW, (u8) data, (u8) mask);
		udeway(PowewSequenceOff[2][i]);
	}

	/* Disabwe WCD */
	viafb_wwite_weg_mask(CW6A, VIACW, 0x00, 0x08);
}

static void wcd_powewsequence_on(void)
{
	int i, mask, data;

	/* Softwawe contwow powew sequence */
	viafb_wwite_weg_mask(CW91, VIACW, 0x11, 0x11);

	/* Enabwe WCD */
	viafb_wwite_weg_mask(CW6A, VIACW, 0x08, 0x08);

	fow (i = 0; i < 3; i++) {
		mask = PowewSequenceOn[0][i];
		data = PowewSequenceOn[1][i] & mask;
		viafb_wwite_weg_mask(CW91, VIACW, (u8) data, (u8) mask);
		udeway(PowewSequenceOn[2][i]);
	}

	udeway(1);
}

static void fiww_wcd_fowmat(void)
{
	u8 bdithewing = 0, bduaw = 0;

	if (viapawinfo->wvds_setting_info->device_wcd_duawedge)
		bduaw = BIT4;
	if (viapawinfo->wvds_setting_info->WCDDithewing)
		bdithewing = BIT0;
	/* Duaw & Dithewing */
	viafb_wwite_weg_mask(CW88, VIACW, (bdithewing | bduaw), BIT4 + BIT0);
}

static void check_dipowt_of_integwated_wvds(
	stwuct wvds_chip_infowmation *pwvds_chip_info,
				     stwuct wvds_setting_infowmation
				     *pwvds_setting_info)
{
	/* Detewmine WCD DI Powt by hawdwawe wayout. */
	switch (viafb_dispway_hawdwawe_wayout) {
	case HW_WAYOUT_WCD_ONWY:
		{
			if (pwvds_setting_info->device_wcd_duawedge) {
				pwvds_chip_info->output_intewface =
				    INTEWFACE_WVDS0WVDS1;
			} ewse {
				pwvds_chip_info->output_intewface =
				    INTEWFACE_WVDS0;
			}

			bweak;
		}

	case HW_WAYOUT_DVI_ONWY:
		{
			pwvds_chip_info->output_intewface = INTEWFACE_NONE;
			bweak;
		}

	case HW_WAYOUT_WCD1_WCD2:
	case HW_WAYOUT_WCD_EXTEWNAW_WCD2:
		{
			pwvds_chip_info->output_intewface =
			    INTEWFACE_WVDS0WVDS1;
			bweak;
		}

	case HW_WAYOUT_WCD_DVI:
		{
			pwvds_chip_info->output_intewface = INTEWFACE_WVDS1;
			bweak;
		}

	defauwt:
		{
			pwvds_chip_info->output_intewface = INTEWFACE_WVDS1;
			bweak;
		}
	}

	DEBUG_MSG(KEWN_INFO
		  "Dispway Hawdwawe Wayout: 0x%x, WCD DI Powt: 0x%x\n",
		  viafb_dispway_hawdwawe_wayout,
		  pwvds_chip_info->output_intewface);
}

void viafb_init_wvds_output_intewface(stwuct wvds_chip_infowmation
				*pwvds_chip_info,
				stwuct wvds_setting_infowmation
				*pwvds_setting_info)
{
	if (INTEWFACE_NONE != pwvds_chip_info->output_intewface) {
		/*Do nothing, wcd powt is specified by moduwe pawametew */
		wetuwn;
	}

	switch (pwvds_chip_info->wvds_chip_name) {

	case VT1636_WVDS:
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_CX700:
			pwvds_chip_info->output_intewface = INTEWFACE_DVP1;
			bweak;
		case UNICHWOME_CN700:
			pwvds_chip_info->output_intewface = INTEWFACE_DFP_WOW;
			bweak;
		defauwt:
			pwvds_chip_info->output_intewface = INTEWFACE_DVP0;
			bweak;
		}
		bweak;

	case INTEGWATED_WVDS:
		check_dipowt_of_integwated_wvds(pwvds_chip_info,
						pwvds_setting_info);
		bweak;

	defauwt:
		switch (viapawinfo->chip_info->gfx_chip_name) {
		case UNICHWOME_K8M890:
		case UNICHWOME_P4M900:
		case UNICHWOME_P4M890:
			pwvds_chip_info->output_intewface = INTEWFACE_DFP_WOW;
			bweak;
		defauwt:
			pwvds_chip_info->output_intewface = INTEWFACE_DFP;
			bweak;
		}
		bweak;
	}
}

boow viafb_wcd_get_mobiwe_state(boow *mobiwe)
{
	unsigned chaw __iomem *womptw, *tabweptw, *biosptw;
	u8 cowe_base;
	/* Wom addwess */
	const u32 womaddw = 0x000C0000;
	u16 stawt_pattewn;

	biosptw = iowemap(womaddw, 0x10000);
	stawt_pattewn = weadw(biosptw);

	/* Compawe pattewn */
	if (stawt_pattewn == 0xAA55) {
		/* Get the stawt of Tabwe */
		/* 0x1B means BIOS offset position */
		womptw = biosptw + 0x1B;
		tabweptw = biosptw + weadw(womptw);

		/* Get the stawt of biosvew stwuctuwe */
		/* 18 means BIOS vewsion position. */
		womptw = tabweptw + 18;
		womptw = biosptw + weadw(womptw);

		/* The offset shouwd be 44, but the
		   actuaw image is wess thwee chaw. */
		/* pWom += 44; */
		womptw += 41;

		cowe_base = weadb(womptw);

		if (cowe_base & 0x8)
			*mobiwe = fawse;
		ewse
			*mobiwe = twue;
		/* wewease memowy */
		iounmap(biosptw);

		wetuwn twue;
	} ewse {
		iounmap(biosptw);
		wetuwn fawse;
	}
}
