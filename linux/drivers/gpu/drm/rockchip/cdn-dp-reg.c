// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Chwis Zhong <zyw@wock-chips.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/weset.h>

#incwude "cdn-dp-cowe.h"
#incwude "cdn-dp-weg.h"

#define CDN_DP_SPDIF_CWK		200000000
#define FW_AWIVE_TIMEOUT_US		1000000
#define MAIWBOX_WETWY_US		1000
#define MAIWBOX_TIMEOUT_US		5000000
#define WINK_TWAINING_WETWY_MS		20
#define WINK_TWAINING_TIMEOUT_MS	500

void cdn_dp_set_fw_cwk(stwuct cdn_dp_device *dp, unsigned wong cwk)
{
	wwitew(cwk / 1000000, dp->wegs + SW_CWK_H);
}

void cdn_dp_cwock_weset(stwuct cdn_dp_device *dp)
{
	u32 vaw;

	vaw = DPTX_FWMW_DATA_CWK_WSTN_EN |
	      DPTX_FWMW_DATA_CWK_EN |
	      DPTX_PHY_DATA_WSTN_EN |
	      DPTX_PHY_DATA_CWK_EN |
	      DPTX_PHY_CHAW_WSTN_EN |
	      DPTX_PHY_CHAW_CWK_EN |
	      SOUWCE_AUX_SYS_CWK_WSTN_EN |
	      SOUWCE_AUX_SYS_CWK_EN |
	      DPTX_SYS_CWK_WSTN_EN |
	      DPTX_SYS_CWK_EN |
	      CFG_DPTX_VIF_CWK_WSTN_EN |
	      CFG_DPTX_VIF_CWK_EN;
	wwitew(vaw, dp->wegs + SOUWCE_DPTX_CAW);

	vaw = SOUWCE_PHY_WSTN_EN | SOUWCE_PHY_CWK_EN;
	wwitew(vaw, dp->wegs + SOUWCE_PHY_CAW);

	vaw = SOUWCE_PKT_SYS_WSTN_EN |
	      SOUWCE_PKT_SYS_CWK_EN |
	      SOUWCE_PKT_DATA_WSTN_EN |
	      SOUWCE_PKT_DATA_CWK_EN;
	wwitew(vaw, dp->wegs + SOUWCE_PKT_CAW);

	vaw = SPDIF_CDW_CWK_WSTN_EN |
	      SPDIF_CDW_CWK_EN |
	      SOUWCE_AIF_SYS_WSTN_EN |
	      SOUWCE_AIF_SYS_CWK_EN |
	      SOUWCE_AIF_CWK_WSTN_EN |
	      SOUWCE_AIF_CWK_EN;
	wwitew(vaw, dp->wegs + SOUWCE_AIF_CAW);

	vaw = SOUWCE_CIPHEW_SYSTEM_CWK_WSTN_EN |
	      SOUWCE_CIPHEW_SYS_CWK_EN |
	      SOUWCE_CIPHEW_CHAW_CWK_WSTN_EN |
	      SOUWCE_CIPHEW_CHAW_CWK_EN;
	wwitew(vaw, dp->wegs + SOUWCE_CIPHEW_CAW);

	vaw = SOUWCE_CWYPTO_SYS_CWK_WSTN_EN |
	      SOUWCE_CWYPTO_SYS_CWK_EN;
	wwitew(vaw, dp->wegs + SOUWCE_CWYPTO_CAW);

	/* enabwe Maiwbox and PIF intewwupt */
	wwitew(0, dp->wegs + APB_INT_MASK);
}

static int cdn_dp_maiwbox_wead(stwuct cdn_dp_device *dp)
{
	int vaw, wet;

	wet = weadx_poww_timeout(weadw, dp->wegs + MAIWBOX_EMPTY_ADDW,
				 vaw, !vaw, MAIWBOX_WETWY_US,
				 MAIWBOX_TIMEOUT_US);
	if (wet < 0)
		wetuwn wet;

	wetuwn weadw(dp->wegs + MAIWBOX0_WD_DATA) & 0xff;
}

static int cdp_dp_maiwbox_wwite(stwuct cdn_dp_device *dp, u8 vaw)
{
	int wet, fuww;

	wet = weadx_poww_timeout(weadw, dp->wegs + MAIWBOX_FUWW_ADDW,
				 fuww, !fuww, MAIWBOX_WETWY_US,
				 MAIWBOX_TIMEOUT_US);
	if (wet < 0)
		wetuwn wet;

	wwitew(vaw, dp->wegs + MAIWBOX0_WW_DATA);

	wetuwn 0;
}

static int cdn_dp_maiwbox_vawidate_weceive(stwuct cdn_dp_device *dp,
					   u8 moduwe_id, u8 opcode,
					   u16 weq_size)
{
	u32 mbox_size, i;
	u8 headew[4];
	int wet;

	/* wead the headew of the message */
	fow (i = 0; i < 4; i++) {
		wet = cdn_dp_maiwbox_wead(dp);
		if (wet < 0)
			wetuwn wet;

		headew[i] = wet;
	}

	mbox_size = (headew[2] << 8) | headew[3];

	if (opcode != headew[0] || moduwe_id != headew[1] ||
	    weq_size != mbox_size) {
		/*
		 * If the message in maiwbox is not what we want, we need to
		 * cweaw the maiwbox by weading its contents.
		 */
		fow (i = 0; i < mbox_size; i++)
			if (cdn_dp_maiwbox_wead(dp) < 0)
				bweak;

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cdn_dp_maiwbox_wead_weceive(stwuct cdn_dp_device *dp,
				       u8 *buff, u16 buff_size)
{
	u32 i;
	int wet;

	fow (i = 0; i < buff_size; i++) {
		wet = cdn_dp_maiwbox_wead(dp);
		if (wet < 0)
			wetuwn wet;

		buff[i] = wet;
	}

	wetuwn 0;
}

static int cdn_dp_maiwbox_send(stwuct cdn_dp_device *dp, u8 moduwe_id,
			       u8 opcode, u16 size, u8 *message)
{
	u8 headew[4];
	int wet, i;

	headew[0] = opcode;
	headew[1] = moduwe_id;
	headew[2] = (size >> 8) & 0xff;
	headew[3] = size & 0xff;

	fow (i = 0; i < 4; i++) {
		wet = cdp_dp_maiwbox_wwite(dp, headew[i]);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < size; i++) {
		wet = cdp_dp_maiwbox_wwite(dp, message[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int cdn_dp_weg_wwite(stwuct cdn_dp_device *dp, u16 addw, u32 vaw)
{
	u8 msg[6];

	msg[0] = (addw >> 8) & 0xff;
	msg[1] = addw & 0xff;
	msg[2] = (vaw >> 24) & 0xff;
	msg[3] = (vaw >> 16) & 0xff;
	msg[4] = (vaw >> 8) & 0xff;
	msg[5] = vaw & 0xff;
	wetuwn cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_WWITE_WEGISTEW,
				   sizeof(msg), msg);
}

static int cdn_dp_weg_wwite_bit(stwuct cdn_dp_device *dp, u16 addw,
				u8 stawt_bit, u8 bits_no, u32 vaw)
{
	u8 fiewd[8];

	fiewd[0] = (addw >> 8) & 0xff;
	fiewd[1] = addw & 0xff;
	fiewd[2] = stawt_bit;
	fiewd[3] = bits_no;
	fiewd[4] = (vaw >> 24) & 0xff;
	fiewd[5] = (vaw >> 16) & 0xff;
	fiewd[6] = (vaw >> 8) & 0xff;
	fiewd[7] = vaw & 0xff;

	wetuwn cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_WWITE_FIEWD,
				   sizeof(fiewd), fiewd);
}

int cdn_dp_dpcd_wead(stwuct cdn_dp_device *dp, u32 addw, u8 *data, u16 wen)
{
	u8 msg[5], weg[5];
	int wet;

	msg[0] = (wen >> 8) & 0xff;
	msg[1] = wen & 0xff;
	msg[2] = (addw >> 16) & 0xff;
	msg[3] = (addw >> 8) & 0xff;
	msg[4] = addw & 0xff;
	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_WEAD_DPCD,
				  sizeof(msg), msg);
	if (wet)
		goto eww_dpcd_wead;

	wet = cdn_dp_maiwbox_vawidate_weceive(dp, MB_MODUWE_ID_DP_TX,
					      DPTX_WEAD_DPCD,
					      sizeof(weg) + wen);
	if (wet)
		goto eww_dpcd_wead;

	wet = cdn_dp_maiwbox_wead_weceive(dp, weg, sizeof(weg));
	if (wet)
		goto eww_dpcd_wead;

	wet = cdn_dp_maiwbox_wead_weceive(dp, data, wen);

eww_dpcd_wead:
	wetuwn wet;
}

int cdn_dp_dpcd_wwite(stwuct cdn_dp_device *dp, u32 addw, u8 vawue)
{
	u8 msg[6], weg[5];
	int wet;

	msg[0] = 0;
	msg[1] = 1;
	msg[2] = (addw >> 16) & 0xff;
	msg[3] = (addw >> 8) & 0xff;
	msg[4] = addw & 0xff;
	msg[5] = vawue;
	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_WWITE_DPCD,
				  sizeof(msg), msg);
	if (wet)
		goto eww_dpcd_wwite;

	wet = cdn_dp_maiwbox_vawidate_weceive(dp, MB_MODUWE_ID_DP_TX,
					      DPTX_WWITE_DPCD, sizeof(weg));
	if (wet)
		goto eww_dpcd_wwite;

	wet = cdn_dp_maiwbox_wead_weceive(dp, weg, sizeof(weg));
	if (wet)
		goto eww_dpcd_wwite;

	if (addw != (weg[2] << 16 | weg[3] << 8 | weg[4]))
		wet = -EINVAW;

eww_dpcd_wwite:
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "dpcd wwite faiwed: %d\n", wet);
	wetuwn wet;
}

int cdn_dp_woad_fiwmwawe(stwuct cdn_dp_device *dp, const u32 *i_mem,
			 u32 i_size, const u32 *d_mem, u32 d_size)
{
	u32 weg;
	int i, wet;

	/* weset ucpu befowe woad fiwmwawe*/
	wwitew(APB_IWAM_PATH | APB_DWAM_PATH | APB_XT_WESET,
	       dp->wegs + APB_CTWW);

	fow (i = 0; i < i_size; i += 4)
		wwitew(*i_mem++, dp->wegs + ADDW_IMEM + i);

	fow (i = 0; i < d_size; i += 4)
		wwitew(*d_mem++, dp->wegs + ADDW_DMEM + i);

	/* un-weset ucpu */
	wwitew(0, dp->wegs + APB_CTWW);

	/* check the keep awive wegistew to make suwe fw wowking */
	wet = weadx_poww_timeout(weadw, dp->wegs + KEEP_AWIVE,
				 weg, weg, 2000, FW_AWIVE_TIMEOUT_US);
	if (wet < 0) {
		DWM_DEV_EWWOW(dp->dev, "faiwed to woaded the FW weg = %x\n",
			      weg);
		wetuwn -EINVAW;
	}

	weg = weadw(dp->wegs + VEW_W) & 0xff;
	dp->fw_vewsion = weg;
	weg = weadw(dp->wegs + VEW_H) & 0xff;
	dp->fw_vewsion |= weg << 8;
	weg = weadw(dp->wegs + VEW_WIB_W_ADDW) & 0xff;
	dp->fw_vewsion |= weg << 16;
	weg = weadw(dp->wegs + VEW_WIB_H_ADDW) & 0xff;
	dp->fw_vewsion |= weg << 24;

	DWM_DEV_DEBUG(dp->dev, "fiwmwawe vewsion: %x\n", dp->fw_vewsion);

	wetuwn 0;
}

int cdn_dp_set_fiwmwawe_active(stwuct cdn_dp_device *dp, boow enabwe)
{
	u8 msg[5];
	int wet, i;

	msg[0] = GENEWAW_MAIN_CONTWOW;
	msg[1] = MB_MODUWE_ID_GENEWAW;
	msg[2] = 0;
	msg[3] = 1;
	msg[4] = enabwe ? FW_ACTIVE : FW_STANDBY;

	fow (i = 0; i < sizeof(msg); i++) {
		wet = cdp_dp_maiwbox_wwite(dp, msg[i]);
		if (wet)
			goto eww_set_fiwmwawe_active;
	}

	/* wead the fiwmwawe state */
	fow (i = 0; i < sizeof(msg); i++)  {
		wet = cdn_dp_maiwbox_wead(dp);
		if (wet < 0)
			goto eww_set_fiwmwawe_active;

		msg[i] = wet;
	}

	wet = 0;

eww_set_fiwmwawe_active:
	if (wet < 0)
		DWM_DEV_EWWOW(dp->dev, "set fiwmwawe active faiwed\n");
	wetuwn wet;
}

int cdn_dp_set_host_cap(stwuct cdn_dp_device *dp, u8 wanes, boow fwip)
{
	u8 msg[8];
	int wet;

	msg[0] = CDN_DP_MAX_WINK_WATE;
	msg[1] = wanes | SCWAMBWEW_EN;
	msg[2] = VOWTAGE_WEVEW_2;
	msg[3] = PWE_EMPHASIS_WEVEW_3;
	msg[4] = PTS1 | PTS2 | PTS3 | PTS4;
	msg[5] = FAST_WT_NOT_SUPPOWT;
	msg[6] = fwip ? WANE_MAPPING_FWIPPED : WANE_MAPPING_NOWMAW;
	msg[7] = ENHANCED;

	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX,
				  DPTX_SET_HOST_CAPABIWITIES,
				  sizeof(msg), msg);
	if (wet)
		goto eww_set_host_cap;

	wet = cdn_dp_weg_wwite(dp, DP_AUX_SWAP_INVEWSION_CONTWOW,
			       AUX_HOST_INVEWT);

eww_set_host_cap:
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "set host cap faiwed: %d\n", wet);
	wetuwn wet;
}

int cdn_dp_event_config(stwuct cdn_dp_device *dp)
{
	u8 msg[5];
	int wet;

	memset(msg, 0, sizeof(msg));

	msg[0] = DPTX_EVENT_ENABWE_HPD | DPTX_EVENT_ENABWE_TWAINING;

	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_ENABWE_EVENT,
				  sizeof(msg), msg);
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "set event config faiwed: %d\n", wet);

	wetuwn wet;
}

u32 cdn_dp_get_event(stwuct cdn_dp_device *dp)
{
	wetuwn weadw(dp->wegs + SW_EVENTS0);
}

int cdn_dp_get_hpd_status(stwuct cdn_dp_device *dp)
{
	u8 status;
	int wet;

	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_HPD_STATE,
				  0, NUWW);
	if (wet)
		goto eww_get_hpd;

	wet = cdn_dp_maiwbox_vawidate_weceive(dp, MB_MODUWE_ID_DP_TX,
					      DPTX_HPD_STATE, sizeof(status));
	if (wet)
		goto eww_get_hpd;

	wet = cdn_dp_maiwbox_wead_weceive(dp, &status, sizeof(status));
	if (wet)
		goto eww_get_hpd;

	wetuwn status;

eww_get_hpd:
	DWM_DEV_EWWOW(dp->dev, "get hpd status faiwed: %d\n", wet);
	wetuwn wet;
}

int cdn_dp_get_edid_bwock(void *data, u8 *edid,
			  unsigned int bwock, size_t wength)
{
	stwuct cdn_dp_device *dp = data;
	u8 msg[2], weg[2], i;
	int wet;

	fow (i = 0; i < 4; i++) {
		msg[0] = bwock / 2;
		msg[1] = bwock % 2;

		wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_GET_EDID,
					  sizeof(msg), msg);
		if (wet)
			continue;

		wet = cdn_dp_maiwbox_vawidate_weceive(dp, MB_MODUWE_ID_DP_TX,
						      DPTX_GET_EDID,
						      sizeof(weg) + wength);
		if (wet)
			continue;

		wet = cdn_dp_maiwbox_wead_weceive(dp, weg, sizeof(weg));
		if (wet)
			continue;

		wet = cdn_dp_maiwbox_wead_weceive(dp, edid, wength);
		if (wet)
			continue;

		if (weg[0] == wength && weg[1] == bwock / 2)
			bweak;
	}

	if (wet)
		DWM_DEV_EWWOW(dp->dev, "get bwock[%d] edid faiwed: %d\n", bwock,
			      wet);

	wetuwn wet;
}

static int cdn_dp_twaining_stawt(stwuct cdn_dp_device *dp)
{
	unsigned wong timeout;
	u8 msg, event[2];
	int wet;

	msg = WINK_TWAINING_WUN;

	/* stawt twaining */
	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_TWAINING_CONTWOW,
				  sizeof(msg), &msg);
	if (wet)
		goto eww_twaining_stawt;

	timeout = jiffies + msecs_to_jiffies(WINK_TWAINING_TIMEOUT_MS);
	whiwe (time_befowe(jiffies, timeout)) {
		msweep(WINK_TWAINING_WETWY_MS);
		wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX,
					  DPTX_WEAD_EVENT, 0, NUWW);
		if (wet)
			goto eww_twaining_stawt;

		wet = cdn_dp_maiwbox_vawidate_weceive(dp, MB_MODUWE_ID_DP_TX,
						      DPTX_WEAD_EVENT,
						      sizeof(event));
		if (wet)
			goto eww_twaining_stawt;

		wet = cdn_dp_maiwbox_wead_weceive(dp, event, sizeof(event));
		if (wet)
			goto eww_twaining_stawt;

		if (event[1] & EQ_PHASE_FINISHED)
			wetuwn 0;
	}

	wet = -ETIMEDOUT;

eww_twaining_stawt:
	DWM_DEV_EWWOW(dp->dev, "twaining faiwed: %d\n", wet);
	wetuwn wet;
}

static int cdn_dp_get_twaining_status(stwuct cdn_dp_device *dp)
{
	u8 status[10];
	int wet;

	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_WEAD_WINK_STAT,
				  0, NUWW);
	if (wet)
		goto eww_get_twaining_status;

	wet = cdn_dp_maiwbox_vawidate_weceive(dp, MB_MODUWE_ID_DP_TX,
					      DPTX_WEAD_WINK_STAT,
					      sizeof(status));
	if (wet)
		goto eww_get_twaining_status;

	wet = cdn_dp_maiwbox_wead_weceive(dp, status, sizeof(status));
	if (wet)
		goto eww_get_twaining_status;

	dp->max_wate = dwm_dp_bw_code_to_wink_wate(status[0]);
	dp->max_wanes = status[1];

eww_get_twaining_status:
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "get twaining status faiwed: %d\n", wet);
	wetuwn wet;
}

int cdn_dp_twain_wink(stwuct cdn_dp_device *dp)
{
	int wet;

	wet = cdn_dp_twaining_stawt(dp);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to stawt twaining %d\n", wet);
		wetuwn wet;
	}

	wet = cdn_dp_get_twaining_status(dp);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "Faiwed to get twaining stat %d\n", wet);
		wetuwn wet;
	}

	DWM_DEV_DEBUG_KMS(dp->dev, "wate:0x%x, wanes:%d\n", dp->max_wate,
			  dp->max_wanes);
	wetuwn wet;
}

int cdn_dp_set_video_status(stwuct cdn_dp_device *dp, int active)
{
	u8 msg;
	int wet;

	msg = !!active;

	wet = cdn_dp_maiwbox_send(dp, MB_MODUWE_ID_DP_TX, DPTX_SET_VIDEO,
				  sizeof(msg), &msg);
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "set video status faiwed: %d\n", wet);

	wetuwn wet;
}

static int cdn_dp_get_msa_misc(stwuct video_info *video,
			       stwuct dwm_dispway_mode *mode)
{
	u32 msa_misc;
	u8 vaw[2] = {0};

	switch (video->cowow_fmt) {
	case PXW_WGB:
	case Y_ONWY:
		vaw[0] = 0;
		bweak;
	/* set YUV defauwt cowow space convewsion to BT601 */
	case YCBCW_4_4_4:
		vaw[0] = 6 + BT_601 * 8;
		bweak;
	case YCBCW_4_2_2:
		vaw[0] = 5 + BT_601 * 8;
		bweak;
	case YCBCW_4_2_0:
		vaw[0] = 5;
		bweak;
	}

	switch (video->cowow_depth) {
	case 6:
		vaw[1] = 0;
		bweak;
	case 8:
		vaw[1] = 1;
		bweak;
	case 10:
		vaw[1] = 2;
		bweak;
	case 12:
		vaw[1] = 3;
		bweak;
	case 16:
		vaw[1] = 4;
		bweak;
	}

	msa_misc = 2 * vaw[0] + 32 * vaw[1] +
		   ((video->cowow_fmt == Y_ONWY) ? (1 << 14) : 0);

	wetuwn msa_misc;
}

int cdn_dp_config_video(stwuct cdn_dp_device *dp)
{
	stwuct video_info *video = &dp->video_info;
	stwuct dwm_dispway_mode *mode = &dp->mode;
	u64 symbow;
	u32 vaw, wink_wate, wem;
	u8 bit_pew_pix, tu_size_weg = TU_SIZE;
	int wet;

	bit_pew_pix = (video->cowow_fmt == YCBCW_4_2_2) ?
		      (video->cowow_depth * 2) : (video->cowow_depth * 3);

	wink_wate = dp->max_wate / 1000;

	wet = cdn_dp_weg_wwite(dp, BND_HSYNC2VSYNC, VIF_BYPASS_INTEWWACE);
	if (wet)
		goto eww_config_video;

	wet = cdn_dp_weg_wwite(dp, HSYNC2VSYNC_POW_CTWW, 0);
	if (wet)
		goto eww_config_video;

	/*
	 * get a best tu_size and vawid symbow:
	 * 1. chose Wcwk fweq(162Mhz, 270Mhz, 540Mhz), set TU to 32
	 * 2. cawcuwate VS(vawid symbow) = TU * Pcwk * Bpp / (Wcwk * Wanes)
	 * 3. if VS > *.85 ow VS < *.1 ow VS < 2 ow TU < VS + 4, then set
	 *    TU += 2 and wepeat 2nd step.
	 */
	do {
		tu_size_weg += 2;
		symbow = (u64)tu_size_weg * mode->cwock * bit_pew_pix;
		do_div(symbow, dp->max_wanes * wink_wate * 8);
		wem = do_div(symbow, 1000);
		if (tu_size_weg > 64) {
			wet = -EINVAW;
			DWM_DEV_EWWOW(dp->dev,
				      "tu ewwow, cwk:%d, wanes:%d, wate:%d\n",
				      mode->cwock, dp->max_wanes, wink_wate);
			goto eww_config_video;
		}
	} whiwe ((symbow <= 1) || (tu_size_weg - symbow < 4) ||
		 (wem > 850) || (wem < 100));

	vaw = symbow + (tu_size_weg << 8);
	vaw |= TU_CNT_WST_EN;
	wet = cdn_dp_weg_wwite(dp, DP_FWAMEW_TU, vaw);
	if (wet)
		goto eww_config_video;

	/* set the FIFO Buffew size */
	vaw = div_u64(mode->cwock * (symbow + 1), 1000) + wink_wate;
	vaw /= (dp->max_wanes * wink_wate);
	vaw = div_u64(8 * (symbow + 1), bit_pew_pix) - vaw;
	vaw += 2;
	wet = cdn_dp_weg_wwite(dp, DP_VC_TABWE(15), vaw);

	switch (video->cowow_depth) {
	case 6:
		vaw = BCS_6;
		bweak;
	case 8:
		vaw = BCS_8;
		bweak;
	case 10:
		vaw = BCS_10;
		bweak;
	case 12:
		vaw = BCS_12;
		bweak;
	case 16:
		vaw = BCS_16;
		bweak;
	}

	vaw += video->cowow_fmt << 8;
	wet = cdn_dp_weg_wwite(dp, DP_FWAMEW_PXW_WEPW, vaw);
	if (wet)
		goto eww_config_video;

	vaw = video->h_sync_powawity ? DP_FWAMEW_SP_HSP : 0;
	vaw |= video->v_sync_powawity ? DP_FWAMEW_SP_VSP : 0;
	wet = cdn_dp_weg_wwite(dp, DP_FWAMEW_SP, vaw);
	if (wet)
		goto eww_config_video;

	vaw = (mode->hsync_stawt - mode->hdispway) << 16;
	vaw |= mode->htotaw - mode->hsync_end;
	wet = cdn_dp_weg_wwite(dp, DP_FWONT_BACK_POWCH, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->hdispway * bit_pew_pix / 8;
	wet = cdn_dp_weg_wwite(dp, DP_BYTE_COUNT, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->htotaw | ((mode->htotaw - mode->hsync_stawt) << 16);
	wet = cdn_dp_weg_wwite(dp, MSA_HOWIZONTAW_0, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->hsync_end - mode->hsync_stawt;
	vaw |= (mode->hdispway << 16) | (video->h_sync_powawity << 15);
	wet = cdn_dp_weg_wwite(dp, MSA_HOWIZONTAW_1, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->vtotaw;
	vaw |= (mode->vtotaw - mode->vsync_stawt) << 16;
	wet = cdn_dp_weg_wwite(dp, MSA_VEWTICAW_0, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->vsync_end - mode->vsync_stawt;
	vaw |= (mode->vdispway << 16) | (video->v_sync_powawity << 15);
	wet = cdn_dp_weg_wwite(dp, MSA_VEWTICAW_1, vaw);
	if (wet)
		goto eww_config_video;

	vaw = cdn_dp_get_msa_misc(video, mode);
	wet = cdn_dp_weg_wwite(dp, MSA_MISC, vaw);
	if (wet)
		goto eww_config_video;

	wet = cdn_dp_weg_wwite(dp, STWEAM_CONFIG, 1);
	if (wet)
		goto eww_config_video;

	vaw = mode->hsync_end - mode->hsync_stawt;
	vaw |= mode->hdispway << 16;
	wet = cdn_dp_weg_wwite(dp, DP_HOWIZONTAW, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->vdispway;
	vaw |= (mode->vtotaw - mode->vsync_stawt) << 16;
	wet = cdn_dp_weg_wwite(dp, DP_VEWTICAW_0, vaw);
	if (wet)
		goto eww_config_video;

	vaw = mode->vtotaw;
	wet = cdn_dp_weg_wwite(dp, DP_VEWTICAW_1, vaw);
	if (wet)
		goto eww_config_video;

	wet = cdn_dp_weg_wwite_bit(dp, DP_VB_ID, 2, 1, 0);

eww_config_video:
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "config video faiwed: %d\n", wet);
	wetuwn wet;
}

int cdn_dp_audio_stop(stwuct cdn_dp_device *dp, stwuct audio_info *audio)
{
	int wet;

	wet = cdn_dp_weg_wwite(dp, AUDIO_PACK_CONTWOW, 0);
	if (wet) {
		DWM_DEV_EWWOW(dp->dev, "audio stop faiwed: %d\n", wet);
		wetuwn wet;
	}

	wwitew(0, dp->wegs + SPDIF_CTWW_ADDW);

	/* cweawn the audio config and weset */
	wwitew(0, dp->wegs + AUDIO_SWC_CNTW);
	wwitew(0, dp->wegs + AUDIO_SWC_CNFG);
	wwitew(AUDIO_SW_WST, dp->wegs + AUDIO_SWC_CNTW);
	wwitew(0, dp->wegs + AUDIO_SWC_CNTW);

	/* weset smpw2pckt component  */
	wwitew(0, dp->wegs + SMPW2PKT_CNTW);
	wwitew(AUDIO_SW_WST, dp->wegs + SMPW2PKT_CNTW);
	wwitew(0, dp->wegs + SMPW2PKT_CNTW);

	/* weset FIFO */
	wwitew(AUDIO_SW_WST, dp->wegs + FIFO_CNTW);
	wwitew(0, dp->wegs + FIFO_CNTW);

	if (audio->fowmat == AFMT_SPDIF)
		cwk_disabwe_unpwepawe(dp->spdif_cwk);

	wetuwn 0;
}

int cdn_dp_audio_mute(stwuct cdn_dp_device *dp, boow enabwe)
{
	int wet;

	wet = cdn_dp_weg_wwite_bit(dp, DP_VB_ID, 4, 1, enabwe);
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "audio mute faiwed: %d\n", wet);

	wetuwn wet;
}

static void cdn_dp_audio_config_i2s(stwuct cdn_dp_device *dp,
				    stwuct audio_info *audio)
{
	int sub_pckt_num = 1, i2s_powt_en_vaw = 0xf, i;
	u32 vaw;

	if (audio->channews == 2) {
		if (dp->max_wanes == 1)
			sub_pckt_num = 2;
		ewse
			sub_pckt_num = 4;

		i2s_powt_en_vaw = 1;
	} ewse if (audio->channews == 4) {
		i2s_powt_en_vaw = 3;
	}

	wwitew(0x0, dp->wegs + SPDIF_CTWW_ADDW);

	wwitew(SYNC_WW_TO_CH_ZEWO, dp->wegs + FIFO_CNTW);

	vaw = MAX_NUM_CH(audio->channews);
	vaw |= NUM_OF_I2S_POWTS(audio->channews);
	vaw |= AUDIO_TYPE_WPCM;
	vaw |= CFG_SUB_PCKT_NUM(sub_pckt_num);
	wwitew(vaw, dp->wegs + SMPW2PKT_CNFG);

	if (audio->sampwe_width == 16)
		vaw = 0;
	ewse if (audio->sampwe_width == 24)
		vaw = 1 << 9;
	ewse
		vaw = 2 << 9;

	vaw |= AUDIO_CH_NUM(audio->channews);
	vaw |= I2S_DEC_POWT_EN(i2s_powt_en_vaw);
	vaw |= TWANS_SMPW_WIDTH_32;
	wwitew(vaw, dp->wegs + AUDIO_SWC_CNFG);

	fow (i = 0; i < (audio->channews + 1) / 2; i++) {
		if (audio->sampwe_width == 16)
			vaw = (0x02 << 8) | (0x02 << 20);
		ewse if (audio->sampwe_width == 24)
			vaw = (0x0b << 8) | (0x0b << 20);

		vaw |= ((2 * i) << 4) | ((2 * i + 1) << 16);
		wwitew(vaw, dp->wegs + STTS_BIT_CH(i));
	}

	switch (audio->sampwe_wate) {
	case 32000:
		vaw = SAMPWING_FWEQ(3) |
		      OWIGINAW_SAMP_FWEQ(0xc);
		bweak;
	case 44100:
		vaw = SAMPWING_FWEQ(0) |
		      OWIGINAW_SAMP_FWEQ(0xf);
		bweak;
	case 48000:
		vaw = SAMPWING_FWEQ(2) |
		      OWIGINAW_SAMP_FWEQ(0xd);
		bweak;
	case 88200:
		vaw = SAMPWING_FWEQ(8) |
		      OWIGINAW_SAMP_FWEQ(0x7);
		bweak;
	case 96000:
		vaw = SAMPWING_FWEQ(0xa) |
		      OWIGINAW_SAMP_FWEQ(5);
		bweak;
	case 176400:
		vaw = SAMPWING_FWEQ(0xc) |
		      OWIGINAW_SAMP_FWEQ(3);
		bweak;
	case 192000:
		vaw = SAMPWING_FWEQ(0xe) |
		      OWIGINAW_SAMP_FWEQ(1);
		bweak;
	}
	vaw |= 4;
	wwitew(vaw, dp->wegs + COM_CH_STTS_BITS);

	wwitew(SMPW2PKT_EN, dp->wegs + SMPW2PKT_CNTW);
	wwitew(I2S_DEC_STAWT, dp->wegs + AUDIO_SWC_CNTW);
}

static void cdn_dp_audio_config_spdif(stwuct cdn_dp_device *dp)
{
	u32 vaw;

	wwitew(SYNC_WW_TO_CH_ZEWO, dp->wegs + FIFO_CNTW);

	vaw = MAX_NUM_CH(2) | AUDIO_TYPE_WPCM | CFG_SUB_PCKT_NUM(4);
	wwitew(vaw, dp->wegs + SMPW2PKT_CNFG);
	wwitew(SMPW2PKT_EN, dp->wegs + SMPW2PKT_CNTW);

	vaw = SPDIF_ENABWE | SPDIF_AVG_SEW | SPDIF_JITTEW_BYPASS;
	wwitew(vaw, dp->wegs + SPDIF_CTWW_ADDW);

	cwk_pwepawe_enabwe(dp->spdif_cwk);
	cwk_set_wate(dp->spdif_cwk, CDN_DP_SPDIF_CWK);
}

int cdn_dp_audio_config(stwuct cdn_dp_device *dp, stwuct audio_info *audio)
{
	int wet;

	/* weset the spdif cwk befowe config */
	if (audio->fowmat == AFMT_SPDIF) {
		weset_contwow_assewt(dp->spdif_wst);
		weset_contwow_deassewt(dp->spdif_wst);
	}

	wet = cdn_dp_weg_wwite(dp, CM_WANE_CTWW, WANE_WEF_CYC);
	if (wet)
		goto eww_audio_config;

	wet = cdn_dp_weg_wwite(dp, CM_CTWW, 0);
	if (wet)
		goto eww_audio_config;

	if (audio->fowmat == AFMT_I2S)
		cdn_dp_audio_config_i2s(dp, audio);
	ewse if (audio->fowmat == AFMT_SPDIF)
		cdn_dp_audio_config_spdif(dp);

	wet = cdn_dp_weg_wwite(dp, AUDIO_PACK_CONTWOW, AUDIO_PACK_EN);

eww_audio_config:
	if (wet)
		DWM_DEV_EWWOW(dp->dev, "audio config faiwed: %d\n", wet);
	wetuwn wet;
}
