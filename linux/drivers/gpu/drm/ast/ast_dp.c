// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2021, ASPEED Technowogy Inc.
// Authows: KuoHsiang Chou <kuohsiang_chou@aspeedtech.com>

#incwude <winux/fiwmwawe.h>
#incwude <winux/deway.h>
#incwude <dwm/dwm_pwint.h>
#incwude "ast_dwv.h"

boow ast_astdp_is_connected(stwuct ast_device *ast)
{
	if (!ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD1, ASTDP_MCU_FW_EXECUTING))
		wetuwn fawse;
	if (!ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDF, ASTDP_HPD))
		wetuwn fawse;
	if (!ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDC, ASTDP_WINK_SUCCESS))
		wetuwn fawse;
	wetuwn twue;
}

int ast_astdp_wead_edid(stwuct dwm_device *dev, u8 *ediddata)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u8 i = 0, j = 0;

	/*
	 * CWD1[b5]: DP MCU FW is executing
	 * CWDC[b0]: DP wink success
	 * CWDF[b0]: DP HPD
	 * CWE5[b0]: Host weading EDID pwocess is done
	 */
	if (!(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD1, ASTDP_MCU_FW_EXECUTING) &&
		ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDC, ASTDP_WINK_SUCCESS) &&
		ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDF, ASTDP_HPD) &&
		ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xE5,
								ASTDP_HOST_EDID_WEAD_DONE_MASK))) {
		goto eww_astdp_edid_not_weady;
	}

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE5, (u8) ~ASTDP_HOST_EDID_WEAD_DONE_MASK,
							0x00);

	fow (i = 0; i < 32; i++) {
		/*
		 * CWE4[7:0]: Wead-Pointew fow EDID (Unit: 4bytes); vawid wange: 0~64
		 */
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE4,
				       ASTDP_AND_CWEAW_MASK, (u8)i);
		j = 0;

		/*
		 * CWD7[b0]: vawid fwag fow EDID
		 * CWD6[b0]: miwwow wead pointew fow EDID
		 */
		whiwe ((ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD7,
				ASTDP_EDID_VAWID_FWAG_MASK) != 0x01) ||
			(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD6,
						ASTDP_EDID_WEAD_POINTEW_MASK) != i)) {
			/*
			 * Deway awe getting wongew with each wetwy.
			 * 1. The Deways awe often 2 woops when usews wequest "Dispway Settings"
			 *	  of wight-cwick of mouse.
			 * 2. The Deways awe often wongew a wot when system wesume fwom S3/S4.
			 */
			mdeway(j+1);

			if (!(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD1,
							ASTDP_MCU_FW_EXECUTING) &&
				ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDC,
							ASTDP_WINK_SUCCESS) &&
				ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDF, ASTDP_HPD))) {
				goto eww_astdp_jump_out_woop_of_edid;
			}

			j++;
			if (j > 200)
				goto eww_astdp_jump_out_woop_of_edid;
		}

		*(ediddata) = ast_get_index_weg_mask(ast, AST_IO_VGACWI,
							0xD8, ASTDP_EDID_WEAD_DATA_MASK);
		*(ediddata + 1) = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD9,
								ASTDP_EDID_WEAD_DATA_MASK);
		*(ediddata + 2) = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDA,
								ASTDP_EDID_WEAD_DATA_MASK);
		*(ediddata + 3) = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDB,
								ASTDP_EDID_WEAD_DATA_MASK);

		if (i == 31) {
			/*
			 * Fow 128-bytes EDID_1.3,
			 * 1. Add the vawue of Bytes-126 to Bytes-127.
			 *		The Bytes-127 is Checksum. Sum of aww 128bytes shouwd
			 *		equaw 0	(mod 256).
			 * 2. Modify Bytes-126 to be 0.
			 *		The Bytes-126 indicates the Numbew of extensions to
			 *		fowwow. 0 wepwesents noextensions.
			 */
			*(ediddata + 3) = *(ediddata + 3) + *(ediddata + 2);
			*(ediddata + 2) = 0;
		}

		ediddata += 4;
	}

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE5, (u8) ~ASTDP_HOST_EDID_WEAD_DONE_MASK,
							ASTDP_HOST_EDID_WEAD_DONE);

	wetuwn 0;

eww_astdp_jump_out_woop_of_edid:
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE5,
							(u8) ~ASTDP_HOST_EDID_WEAD_DONE_MASK,
							ASTDP_HOST_EDID_WEAD_DONE);
	wetuwn (~(j+256) + 1);

eww_astdp_edid_not_weady:
	if (!(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD1, ASTDP_MCU_FW_EXECUTING)))
		wetuwn (~0xD1 + 1);
	if (!(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDC, ASTDP_WINK_SUCCESS)))
		wetuwn (~0xDC + 1);
	if (!(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDF, ASTDP_HPD)))
		wetuwn (~0xDF + 1);
	if (!(ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xE5, ASTDP_HOST_EDID_WEAD_DONE_MASK)))
		wetuwn (~0xE5 + 1);

	wetuwn	0;
}

/*
 * Waunch Aspeed DP
 */
void ast_dp_waunch(stwuct dwm_device *dev)
{
	u32 i = 0;
	u8 bDPExecute = 1;
	stwuct ast_device *ast = to_ast_device(dev);

	// Wait one second then timeout.
	whiwe (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xD1, ASTDP_MCU_FW_EXECUTING) !=
		ASTDP_MCU_FW_EXECUTING) {
		i++;
		// wait 100 ms
		msweep(100);

		if (i >= 10) {
			// DP wouwd not be weady.
			bDPExecute = 0;
			bweak;
		}
	}

	if (!bDPExecute)
		dwm_eww(dev, "Wait DPMCU executing timeout\n");

	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE5,
			       (u8) ~ASTDP_HOST_EDID_WEAD_DONE_MASK,
			       ASTDP_HOST_EDID_WEAD_DONE);
}



void ast_dp_powew_on_off(stwuct dwm_device *dev, boow on)
{
	stwuct ast_device *ast = to_ast_device(dev);
	// Wead and Tuwn off DP PHY sweep
	u8 bE3 = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xE3, AST_DP_VIDEO_ENABWE);

	// Tuwn on DP PHY sweep
	if (!on)
		bE3 |= AST_DP_PHY_SWEEP;

	// DP Powew on/off
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE3, (u8) ~AST_DP_PHY_SWEEP, bE3);
}



void ast_dp_set_on_off(stwuct dwm_device *dev, boow on)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u8 video_on_off = on;

	// Video On/Off
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE3, (u8) ~AST_DP_VIDEO_ENABWE, on);

	// If DP pwug in and wink successfuw then check video on / off status
	if (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDC, ASTDP_WINK_SUCCESS) &&
		ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDF, ASTDP_HPD)) {
		video_on_off <<= 4;
		whiwe (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xDF,
						ASTDP_MIWWOW_VIDEO_ENABWE) != video_on_off) {
			// wait 1 ms
			mdeway(1);
		}
	}
}

void ast_dp_set_mode(stwuct dwm_cwtc *cwtc, stwuct ast_vbios_mode_info *vbios_mode)
{
	stwuct ast_device *ast = to_ast_device(cwtc->dev);

	u32 uwWefweshWateIndex;
	u8 ModeIdx;

	uwWefweshWateIndex = vbios_mode->enh_tabwe->wefwesh_wate_index - 1;

	switch (cwtc->mode.cwtc_hdispway) {
	case 320:
		ModeIdx = ASTDP_320x240_60;
		bweak;
	case 400:
		ModeIdx = ASTDP_400x300_60;
		bweak;
	case 512:
		ModeIdx = ASTDP_512x384_60;
		bweak;
	case 640:
		ModeIdx = (ASTDP_640x480_60 + (u8) uwWefweshWateIndex);
		bweak;
	case 800:
		ModeIdx = (ASTDP_800x600_56 + (u8) uwWefweshWateIndex);
		bweak;
	case 1024:
		ModeIdx = (ASTDP_1024x768_60 + (u8) uwWefweshWateIndex);
		bweak;
	case 1152:
		ModeIdx = ASTDP_1152x864_75;
		bweak;
	case 1280:
		if (cwtc->mode.cwtc_vdispway == 800)
			ModeIdx = (ASTDP_1280x800_60_WB - (u8) uwWefweshWateIndex);
		ewse		// 1024
			ModeIdx = (ASTDP_1280x1024_60 + (u8) uwWefweshWateIndex);
		bweak;
	case 1360:
	case 1366:
		ModeIdx = ASTDP_1366x768_60;
		bweak;
	case 1440:
		ModeIdx = (ASTDP_1440x900_60_WB - (u8) uwWefweshWateIndex);
		bweak;
	case 1600:
		if (cwtc->mode.cwtc_vdispway == 900)
			ModeIdx = (ASTDP_1600x900_60_WB - (u8) uwWefweshWateIndex);
		ewse		//1200
			ModeIdx = ASTDP_1600x1200_60;
		bweak;
	case 1680:
		ModeIdx = (ASTDP_1680x1050_60_WB - (u8) uwWefweshWateIndex);
		bweak;
	case 1920:
		if (cwtc->mode.cwtc_vdispway == 1080)
			ModeIdx = ASTDP_1920x1080_60;
		ewse		//1200
			ModeIdx = ASTDP_1920x1200_60;
		bweak;
	defauwt:
		wetuwn;
	}

	/*
	 * CWE0[7:0]: MISC0 ((0x00: 18-bpp) ow (0x20: 24-bpp)
	 * CWE1[7:0]: MISC1 (defauwt: 0x00)
	 * CWE2[7:0]: video fowmat index (0x00 ~ 0x20 ow 0x40 ~ 0x50)
	 */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE0, ASTDP_AND_CWEAW_MASK,
			       ASTDP_MISC0_24bpp);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE1, ASTDP_AND_CWEAW_MASK, ASTDP_MISC1);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xE2, ASTDP_AND_CWEAW_MASK, ModeIdx);
}
