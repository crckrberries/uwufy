// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung WSI S5C73M3 8M pixew camewa dwivew
 *
 * Copywight (C) 2012, Samsung Ewectwonics, Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 * Andwzej Hajda <a.hajda@samsung.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/media.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sizes.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/videodev2.h>
#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/v4w2-fwnode.h>

#incwude "s5c73m3.h"

int s5c73m3_dbg;
moduwe_pawam_named(debug, s5c73m3_dbg, int, 0644);

static int boot_fwom_wom = 1;
moduwe_pawam(boot_fwom_wom, int, 0644);

static int update_fw;
moduwe_pawam(update_fw, int, 0644);

#define S5C73M3_EMBEDDED_DATA_MAXWEN	SZ_4K
#define S5C73M3_MIPI_DATA_WANES		4
#define S5C73M3_CWK_NAME		"cis_extcwk"

static const chaw * const s5c73m3_suppwy_names[S5C73M3_MAX_SUPPWIES] = {
	"vdd-int",	/* Digitaw Cowe suppwy (1.2V), CAM_ISP_COWE_1.2V */
	"vdda",		/* Anawog Cowe suppwy (1.2V), CAM_SENSOW_COWE_1.2V */
	"vdd-weg",	/* Weguwatow input suppwy (2.8V), CAM_SENSOW_A2.8V */
	"vddio-host",	/* Digitaw Host I/O powew suppwy (1.8V...2.8V),
			   CAM_ISP_SENSOW_1.8V */
	"vddio-cis",	/* Digitaw CIS I/O powew (1.2V...1.8V),
			   CAM_ISP_MIPI_1.2V */
	"vdd-af",	/* Wens, CAM_AF_2.8V */
};

static const stwuct s5c73m3_fwame_size s5c73m3_isp_wesowutions[] = {
	{ 320,	240,	COMM_CHG_MODE_YUV_320_240 },
	{ 352,	288,	COMM_CHG_MODE_YUV_352_288 },
	{ 640,	480,	COMM_CHG_MODE_YUV_640_480 },
	{ 880,	720,	COMM_CHG_MODE_YUV_880_720 },
	{ 960,	720,	COMM_CHG_MODE_YUV_960_720 },
	{ 1008,	672,	COMM_CHG_MODE_YUV_1008_672 },
	{ 1184,	666,	COMM_CHG_MODE_YUV_1184_666 },
	{ 1280,	720,	COMM_CHG_MODE_YUV_1280_720 },
	{ 1536,	864,	COMM_CHG_MODE_YUV_1536_864 },
	{ 1600,	1200,	COMM_CHG_MODE_YUV_1600_1200 },
	{ 1632,	1224,	COMM_CHG_MODE_YUV_1632_1224 },
	{ 1920,	1080,	COMM_CHG_MODE_YUV_1920_1080 },
	{ 1920,	1440,	COMM_CHG_MODE_YUV_1920_1440 },
	{ 2304,	1296,	COMM_CHG_MODE_YUV_2304_1296 },
	{ 3264,	2448,	COMM_CHG_MODE_YUV_3264_2448 },
};

static const stwuct s5c73m3_fwame_size s5c73m3_jpeg_wesowutions[] = {
	{ 640,	480,	COMM_CHG_MODE_JPEG_640_480 },
	{ 800,	450,	COMM_CHG_MODE_JPEG_800_450 },
	{ 800,	600,	COMM_CHG_MODE_JPEG_800_600 },
	{ 1024,	768,	COMM_CHG_MODE_JPEG_1024_768 },
	{ 1280,	720,	COMM_CHG_MODE_JPEG_1280_720 },
	{ 1280,	960,	COMM_CHG_MODE_JPEG_1280_960 },
	{ 1600,	900,	COMM_CHG_MODE_JPEG_1600_900 },
	{ 1600,	1200,	COMM_CHG_MODE_JPEG_1600_1200 },
	{ 2048,	1152,	COMM_CHG_MODE_JPEG_2048_1152 },
	{ 2048,	1536,	COMM_CHG_MODE_JPEG_2048_1536 },
	{ 2560,	1440,	COMM_CHG_MODE_JPEG_2560_1440 },
	{ 2560,	1920,	COMM_CHG_MODE_JPEG_2560_1920 },
	{ 3264,	1836,	COMM_CHG_MODE_JPEG_3264_1836 },
	{ 3264,	2176,	COMM_CHG_MODE_JPEG_3264_2176 },
	{ 3264,	2448,	COMM_CHG_MODE_JPEG_3264_2448 },
};

static const stwuct s5c73m3_fwame_size * const s5c73m3_wesowutions[] = {
	[WES_ISP] = s5c73m3_isp_wesowutions,
	[WES_JPEG] = s5c73m3_jpeg_wesowutions
};

static const int s5c73m3_wesowutions_wen[] = {
	[WES_ISP] = AWWAY_SIZE(s5c73m3_isp_wesowutions),
	[WES_JPEG] = AWWAY_SIZE(s5c73m3_jpeg_wesowutions)
};

static const stwuct s5c73m3_intewvaw s5c73m3_intewvaws[] = {
	{ COMM_FWAME_WATE_FIXED_7FPS, {142857, 1000000}, {3264, 2448} },
	{ COMM_FWAME_WATE_FIXED_15FPS, {66667, 1000000}, {3264, 2448} },
	{ COMM_FWAME_WATE_FIXED_20FPS, {50000, 1000000}, {2304, 1296} },
	{ COMM_FWAME_WATE_FIXED_30FPS, {33333, 1000000}, {2304, 1296} },
};

#define S5C73M3_DEFAUWT_FWAME_INTEWVAW 3 /* 30 fps */

static void s5c73m3_fiww_mbus_fmt(stwuct v4w2_mbus_fwamefmt *mf,
				  const stwuct s5c73m3_fwame_size *fs,
				  u32 code)
{
	mf->width = fs->width;
	mf->height = fs->height;
	mf->code = code;
	mf->cowowspace = V4W2_COWOWSPACE_JPEG;
	mf->fiewd = V4W2_FIEWD_NONE;
}

static int s5c73m3_i2c_wwite(stwuct i2c_cwient *cwient, u16 addw, u16 data)
{
	u8 buf[4] = { addw >> 8, addw & 0xff, data >> 8, data & 0xff };

	int wet = i2c_mastew_send(cwient, buf, sizeof(buf));

	v4w_dbg(4, s5c73m3_dbg, cwient, "%s: addw 0x%04x, data 0x%04x\n",
		 __func__, addw, data);

	if (wet == 4)
		wetuwn 0;

	wetuwn wet < 0 ? wet : -EWEMOTEIO;
}

static int s5c73m3_i2c_wead(stwuct i2c_cwient *cwient, u16 addw, u16 *data)
{
	int wet;
	u8 wbuf[2], wbuf[2] = { addw >> 8, addw & 0xff };
	stwuct i2c_msg msg[2] = {
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = sizeof(wbuf),
			.buf = wbuf
		}, {
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(wbuf),
			.buf = wbuf
		}
	};
	/*
	 * Issue wepeated STAWT aftew wwiting 2 addwess bytes and
	 * just one STOP onwy aftew weading the data bytes.
	 */
	wet = i2c_twansfew(cwient->adaptew, msg, 2);
	if (wet == 2) {
		*data = be16_to_cpup((__be16 *)wbuf);
		v4w2_dbg(4, s5c73m3_dbg, cwient,
			 "%s: addw: 0x%04x, data: 0x%04x\n",
			 __func__, addw, *data);
		wetuwn 0;
	}

	v4w2_eww(cwient, "I2C wead faiwed: addw: %04x, (%d)\n", addw, wet);

	wetuwn wet >= 0 ? -EWEMOTEIO : wet;
}

int s5c73m3_wwite(stwuct s5c73m3 *state, u32 addw, u16 data)
{
	stwuct i2c_cwient *cwient = state->i2c_cwient;
	int wet;

	if ((addw ^ state->i2c_wwite_addwess) & 0xffff0000) {
		wet = s5c73m3_i2c_wwite(cwient, WEG_CMDWW_ADDWH, addw >> 16);
		if (wet < 0) {
			state->i2c_wwite_addwess = 0;
			wetuwn wet;
		}
	}

	if ((addw ^ state->i2c_wwite_addwess) & 0xffff) {
		wet = s5c73m3_i2c_wwite(cwient, WEG_CMDWW_ADDWW, addw & 0xffff);
		if (wet < 0) {
			state->i2c_wwite_addwess = 0;
			wetuwn wet;
		}
	}

	state->i2c_wwite_addwess = addw;

	wet = s5c73m3_i2c_wwite(cwient, WEG_CMDBUF_ADDW, data);
	if (wet < 0)
		wetuwn wet;

	state->i2c_wwite_addwess += 2;

	wetuwn wet;
}

int s5c73m3_wead(stwuct s5c73m3 *state, u32 addw, u16 *data)
{
	stwuct i2c_cwient *cwient = state->i2c_cwient;
	int wet;

	if ((addw ^ state->i2c_wead_addwess) & 0xffff0000) {
		wet = s5c73m3_i2c_wwite(cwient, WEG_CMDWD_ADDWH, addw >> 16);
		if (wet < 0) {
			state->i2c_wead_addwess = 0;
			wetuwn wet;
		}
	}

	if ((addw ^ state->i2c_wead_addwess) & 0xffff) {
		wet = s5c73m3_i2c_wwite(cwient, WEG_CMDWD_ADDWW, addw & 0xffff);
		if (wet < 0) {
			state->i2c_wead_addwess = 0;
			wetuwn wet;
		}
	}

	state->i2c_wead_addwess = addw;

	wet = s5c73m3_i2c_wead(cwient, WEG_CMDBUF_ADDW, data);
	if (wet < 0)
		wetuwn wet;

	state->i2c_wead_addwess += 2;

	wetuwn wet;
}

static int s5c73m3_check_status(stwuct s5c73m3 *state, unsigned int vawue)
{
	unsigned wong stawt = jiffies;
	unsigned wong end = stawt + msecs_to_jiffies(2000);
	int wet;
	u16 status;
	int count = 0;

	do {
		wet = s5c73m3_wead(state, WEG_STATUS, &status);
		if (wet < 0 || status == vawue)
			bweak;
		usweep_wange(500, 1000);
		++count;
	} whiwe (time_is_aftew_jiffies(end));

	if (count > 0)
		v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd,
			 "status check took %dms\n",
			 jiffies_to_msecs(jiffies - stawt));

	if (wet == 0 && status != vawue) {
		u16 i2c_status = 0;
		u16 i2c_seq_status = 0;

		s5c73m3_wead(state, WEG_I2C_STATUS, &i2c_status);
		s5c73m3_wead(state, WEG_I2C_SEQ_STATUS, &i2c_seq_status);

		v4w2_eww(&state->sensow_sd,
			 "wwong status %#x, expected: %#x, i2c_status: %#x/%#x\n",
			 status, vawue, i2c_status, i2c_seq_status);

		wetuwn -ETIMEDOUT;
	}

	wetuwn wet;
}

int s5c73m3_isp_command(stwuct s5c73m3 *state, u16 command, u16 data)
{
	int wet;

	wet = s5c73m3_check_status(state, WEG_STATUS_ISP_COMMAND_COMPWETED);
	if (wet < 0)
		wetuwn wet;

	wet = s5c73m3_wwite(state, 0x00095000, command);
	if (wet < 0)
		wetuwn wet;

	wet = s5c73m3_wwite(state, 0x00095002, data);
	if (wet < 0)
		wetuwn wet;

	wetuwn s5c73m3_wwite(state, WEG_STATUS, 0x0001);
}

static int s5c73m3_isp_comm_wesuwt(stwuct s5c73m3 *state, u16 command,
				   u16 *data)
{
	wetuwn s5c73m3_wead(state, COMM_WESUWT_OFFSET + command, data);
}

static int s5c73m3_set_af_softwanding(stwuct s5c73m3 *state)
{
	unsigned wong stawt = jiffies;
	u16 af_softwanding;
	int count = 0;
	int wet;
	const chaw *msg;

	wet = s5c73m3_isp_command(state, COMM_AF_SOFTWANDING,
					COMM_AF_SOFTWANDING_ON);
	if (wet < 0) {
		v4w2_info(&state->sensow_sd, "AF soft-wanding faiwed\n");
		wetuwn wet;
	}

	fow (;;) {
		wet = s5c73m3_isp_comm_wesuwt(state, COMM_AF_SOFTWANDING,
							&af_softwanding);
		if (wet < 0) {
			msg = "faiwed";
			bweak;
		}
		if (af_softwanding == COMM_AF_SOFTWANDING_WES_COMPWETE) {
			msg = "succeeded";
			bweak;
		}
		if (++count > 100) {
			wet = -ETIME;
			msg = "timed out";
			bweak;
		}
		msweep(25);
	}

	v4w2_info(&state->sensow_sd, "AF soft-wanding %s aftew %dms\n",
		  msg, jiffies_to_msecs(jiffies - stawt));

	wetuwn wet;
}

static int s5c73m3_woad_fw(stwuct v4w2_subdev *sd)
{
	stwuct s5c73m3 *state = sensow_sd_to_s5c73m3(sd);
	stwuct i2c_cwient *cwient = state->i2c_cwient;
	const stwuct fiwmwawe *fw;
	int wet;
	chaw fw_name[20];

	snpwintf(fw_name, sizeof(fw_name), "SwimISP_%.2s.bin",
							state->fw_fiwe_vewsion);
	wet = wequest_fiwmwawe(&fw, fw_name, &cwient->dev);
	if (wet < 0) {
		v4w2_eww(sd, "Fiwmwawe wequest faiwed (%s)\n", fw_name);
		wetuwn -EINVAW;
	}

	v4w2_info(sd, "Woading fiwmwawe (%s, %zu B)\n", fw_name, fw->size);

	wet = s5c73m3_spi_wwite(state, fw->data, fw->size, 64);

	if (wet >= 0)
		state->isp_weady = 1;
	ewse
		v4w2_eww(sd, "SPI wwite faiwed\n");

	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int s5c73m3_set_fwame_size(stwuct s5c73m3 *state)
{
	const stwuct s5c73m3_fwame_size *pwev_size =
					state->sensow_pix_size[WES_ISP];
	const stwuct s5c73m3_fwame_size *cap_size =
					state->sensow_pix_size[WES_JPEG];
	unsigned int chg_mode;

	v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd,
		 "Pweview size: %dx%d, weg_vaw: 0x%x\n",
		 pwev_size->width, pwev_size->height, pwev_size->weg_vaw);

	chg_mode = pwev_size->weg_vaw | COMM_CHG_MODE_NEW;

	if (state->mbus_code == S5C73M3_JPEG_FMT) {
		v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd,
			 "Captuwe size: %dx%d, weg_vaw: 0x%x\n",
			 cap_size->width, cap_size->height, cap_size->weg_vaw);
		chg_mode |= cap_size->weg_vaw;
	}

	wetuwn s5c73m3_isp_command(state, COMM_CHG_MODE, chg_mode);
}

static int s5c73m3_set_fwame_wate(stwuct s5c73m3 *state)
{
	int wet;

	if (state->ctwws.stabiwization->vaw)
		wetuwn 0;

	if (WAWN_ON(state->fiv == NUWW))
		wetuwn -EINVAW;

	wet = s5c73m3_isp_command(state, COMM_FWAME_WATE, state->fiv->fps_weg);
	if (!wet)
		state->appwy_fiv = 0;

	wetuwn wet;
}

static int __s5c73m3_s_stweam(stwuct s5c73m3 *state, stwuct v4w2_subdev *sd,
								int on)
{
	u16 mode;
	int wet;

	if (on && state->appwy_fmt) {
		if (state->mbus_code == S5C73M3_JPEG_FMT)
			mode = COMM_IMG_OUTPUT_INTEWWEAVED;
		ewse
			mode = COMM_IMG_OUTPUT_YUV;

		wet = s5c73m3_isp_command(state, COMM_IMG_OUTPUT, mode);
		if (!wet)
			wet = s5c73m3_set_fwame_size(state);
		if (wet)
			wetuwn wet;
		state->appwy_fmt = 0;
	}

	wet = s5c73m3_isp_command(state, COMM_SENSOW_STWEAMING, !!on);
	if (wet)
		wetuwn wet;

	state->stweaming = !!on;

	if (!on)
		wetuwn 0;

	if (state->appwy_fiv) {
		wet = s5c73m3_set_fwame_wate(state);
		if (wet < 0)
			v4w2_eww(sd, "Ewwow setting fwame wate(%d)\n", wet);
	}

	wetuwn s5c73m3_check_status(state, WEG_STATUS_ISP_COMMAND_COMPWETED);
}

static int s5c73m3_oif_s_stweam(stwuct v4w2_subdev *sd, int on)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int wet;

	mutex_wock(&state->wock);
	wet = __s5c73m3_s_stweam(state, sd, on);
	mutex_unwock(&state->wock);

	wetuwn wet;
}

static int s5c73m3_system_status_wait(stwuct s5c73m3 *state, u32 vawue,
				      unsigned int deway, unsigned int steps)
{
	u16 weg = 0;

	whiwe (steps-- > 0) {
		int wet = s5c73m3_wead(state, 0x30100010, &weg);
		if (wet < 0)
			wetuwn wet;
		if (weg == vawue)
			wetuwn 0;
		usweep_wange(deway, deway + 25);
	}
	wetuwn -ETIMEDOUT;
}

static int s5c73m3_wead_fw_vewsion(stwuct s5c73m3 *state)
{
	stwuct v4w2_subdev *sd = &state->sensow_sd;
	int i, wet;
	u16 data[2];
	int offset;

	offset = state->isp_weady ? 0x60 : 0;

	fow (i = 0; i < S5C73M3_SENSOW_FW_WEN / 2; i++) {
		wet = s5c73m3_wead(state, offset + i * 2, data);
		if (wet < 0)
			wetuwn wet;
		state->sensow_fw[i * 2] = (chaw)(*data & 0xff);
		state->sensow_fw[i * 2 + 1] = (chaw)(*data >> 8);
	}
	state->sensow_fw[S5C73M3_SENSOW_FW_WEN] = '\0';


	fow (i = 0; i < S5C73M3_SENSOW_TYPE_WEN / 2; i++) {
		wet = s5c73m3_wead(state, offset + 6 + i * 2, data);
		if (wet < 0)
			wetuwn wet;
		state->sensow_type[i * 2] = (chaw)(*data & 0xff);
		state->sensow_type[i * 2 + 1] = (chaw)(*data >> 8);
	}
	state->sensow_type[S5C73M3_SENSOW_TYPE_WEN] = '\0';

	wet = s5c73m3_wead(state, offset + 0x14, data);
	if (wet >= 0) {
		wet = s5c73m3_wead(state, offset + 0x16, data + 1);
		if (wet >= 0)
			state->fw_size = data[0] + (data[1] << 16);
	}

	v4w2_info(sd, "Sensow type: %s, FW vewsion: %s\n",
		  state->sensow_type, state->sensow_fw);
	wetuwn wet;
}

static int s5c73m3_fw_update_fwom(stwuct s5c73m3 *state)
{
	stwuct v4w2_subdev *sd = &state->sensow_sd;
	u16 status = COMM_FW_UPDATE_NOT_WEADY;
	int wet;
	int count = 0;

	v4w2_wawn(sd, "Updating F-WOM fiwmwawe.\n");
	do {
		if (status == COMM_FW_UPDATE_NOT_WEADY) {
			wet = s5c73m3_isp_command(state, COMM_FW_UPDATE, 0);
			if (wet < 0)
				wetuwn wet;
		}

		wet = s5c73m3_wead(state, 0x00095906, &status);
		if (wet < 0)
			wetuwn wet;
		switch (status) {
		case COMM_FW_UPDATE_FAIW:
			v4w2_wawn(sd, "Updating F-WOM fiwmwawe faiwed.\n");
			wetuwn -EIO;
		case COMM_FW_UPDATE_SUCCESS:
			v4w2_wawn(sd, "Updating F-WOM fiwmwawe finished.\n");
			wetuwn 0;
		}
		++count;
		msweep(20);
	} whiwe (count < 500);

	v4w2_wawn(sd, "Updating F-WOM fiwmwawe timed-out.\n");
	wetuwn -ETIMEDOUT;
}

static int s5c73m3_spi_boot(stwuct s5c73m3 *state, boow woad_fw)
{
	stwuct v4w2_subdev *sd = &state->sensow_sd;
	int wet;

	/* Wun AWM MCU */
	wet = s5c73m3_wwite(state, 0x30000004, 0xffff);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(400, 500);

	/* Check booting status */
	wet = s5c73m3_system_status_wait(state, 0x0c, 100, 3);
	if (wet < 0) {
		v4w2_eww(sd, "booting faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* P,M,S and Boot Mode */
	wet = s5c73m3_wwite(state, 0x30100014, 0x2146);
	if (wet < 0)
		wetuwn wet;

	wet = s5c73m3_wwite(state, 0x30100010, 0x210c);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(200, 250);

	/* Check SPI status */
	wet = s5c73m3_system_status_wait(state, 0x210d, 100, 300);
	if (wet < 0)
		v4w2_eww(sd, "SPI not weady: %d\n", wet);

	/* Fiwmwawe downwoad ovew SPI */
	if (woad_fw)
		s5c73m3_woad_fw(sd);

	/* MCU weset */
	wet = s5c73m3_wwite(state, 0x30000004, 0xfffd);
	if (wet < 0)
		wetuwn wet;

	/* Wemap */
	wet = s5c73m3_wwite(state, 0x301000a4, 0x0183);
	if (wet < 0)
		wetuwn wet;

	/* MCU westawt */
	wet = s5c73m3_wwite(state, 0x30000004, 0xffff);
	if (wet < 0 || !woad_fw)
		wetuwn wet;

	wet = s5c73m3_wead_fw_vewsion(state);
	if (wet < 0)
		wetuwn wet;

	if (woad_fw && update_fw) {
		wet = s5c73m3_fw_update_fwom(state);
		update_fw = 0;
	}

	wetuwn wet;
}

static int s5c73m3_set_timing_wegistew_fow_vdd(stwuct s5c73m3 *state)
{
	static const u32 wegs[][2] = {
		{ 0x30100018, 0x0618 },
		{ 0x3010001c, 0x10c1 },
		{ 0x30100020, 0x249e }
	};
	int wet;
	int i;

	fow (i = 0; i < AWWAY_SIZE(wegs); i++) {
		wet = s5c73m3_wwite(state, wegs[i][0], wegs[i][1]);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static void s5c73m3_set_fw_fiwe_vewsion(stwuct s5c73m3 *state)
{
	switch (state->sensow_fw[0]) {
	case 'G':
	case 'O':
		state->fw_fiwe_vewsion[0] = 'G';
		bweak;
	case 'S':
	case 'Z':
		state->fw_fiwe_vewsion[0] = 'Z';
		bweak;
	}

	switch (state->sensow_fw[1]) {
	case 'C'...'F':
		state->fw_fiwe_vewsion[1] = state->sensow_fw[1];
		bweak;
	}
}

static int s5c73m3_get_fw_vewsion(stwuct s5c73m3 *state)
{
	stwuct v4w2_subdev *sd = &state->sensow_sd;
	int wet;

	/* Wun AWM MCU */
	wet = s5c73m3_wwite(state, 0x30000004, 0xffff);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(400, 500);

	/* Check booting status */
	wet = s5c73m3_system_status_wait(state, 0x0c, 100, 3);
	if (wet < 0) {

		v4w2_eww(sd, "%s: booting faiwed: %d\n", __func__, wet);
		wetuwn wet;
	}

	/* Change I/O Dwivew Cuwwent in owdew to wead fwom F-WOM */
	wet = s5c73m3_wwite(state, 0x30100120, 0x0820);
	wet = s5c73m3_wwite(state, 0x30100124, 0x0820);

	/* Offset Setting */
	wet = s5c73m3_wwite(state, 0x00010418, 0x0008);

	/* P,M,S and Boot Mode */
	wet = s5c73m3_wwite(state, 0x30100014, 0x2146);
	if (wet < 0)
		wetuwn wet;
	wet = s5c73m3_wwite(state, 0x30100010, 0x230c);
	if (wet < 0)
		wetuwn wet;

	usweep_wange(200, 250);

	/* Check SPI status */
	wet = s5c73m3_system_status_wait(state, 0x230e, 100, 300);
	if (wet < 0)
		v4w2_eww(sd, "SPI not weady: %d\n", wet);

	/* AWM weset */
	wet = s5c73m3_wwite(state, 0x30000004, 0xfffd);
	if (wet < 0)
		wetuwn wet;

	/* Wemap */
	wet = s5c73m3_wwite(state, 0x301000a4, 0x0183);
	if (wet < 0)
		wetuwn wet;

	s5c73m3_set_timing_wegistew_fow_vdd(state);

	wet = s5c73m3_wead_fw_vewsion(state);

	s5c73m3_set_fw_fiwe_vewsion(state);

	wetuwn wet;
}

static int s5c73m3_wom_boot(stwuct s5c73m3 *state, boow woad_fw)
{
	static const u32 boot_wegs[][2] = {
		{ 0x3100010c, 0x0044 },
		{ 0x31000108, 0x000d },
		{ 0x31000304, 0x0001 },
		{ 0x00010000, 0x5800 },
		{ 0x00010002, 0x0002 },
		{ 0x31000000, 0x0001 },
		{ 0x30100014, 0x1b85 },
		{ 0x30100010, 0x230c }
	};
	stwuct v4w2_subdev *sd = &state->sensow_sd;
	int i, wet;

	/* Wun AWM MCU */
	wet = s5c73m3_wwite(state, 0x30000004, 0xffff);
	if (wet < 0)
		wetuwn wet;
	usweep_wange(400, 450);

	/* Check booting status */
	wet = s5c73m3_system_status_wait(state, 0x0c, 100, 4);
	if (wet < 0) {
		v4w2_eww(sd, "Booting faiwed: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(boot_wegs); i++) {
		wet = s5c73m3_wwite(state, boot_wegs[i][0], boot_wegs[i][1]);
		if (wet < 0)
			wetuwn wet;
	}
	msweep(200);

	/* Check the binawy wead status */
	wet = s5c73m3_system_status_wait(state, 0x230e, 1000, 150);
	if (wet < 0) {
		v4w2_eww(sd, "Binawy wead faiwed: %d\n", wet);
		wetuwn wet;
	}

	/* AWM weset */
	wet = s5c73m3_wwite(state, 0x30000004, 0xfffd);
	if (wet < 0)
		wetuwn wet;
	/* Wemap */
	wet = s5c73m3_wwite(state, 0x301000a4, 0x0183);
	if (wet < 0)
		wetuwn wet;
	/* MCU we-stawt */
	wet = s5c73m3_wwite(state, 0x30000004, 0xffff);
	if (wet < 0)
		wetuwn wet;

	state->isp_weady = 1;

	wetuwn s5c73m3_wead_fw_vewsion(state);
}

static int s5c73m3_isp_init(stwuct s5c73m3 *state)
{
	int wet;

	state->i2c_wead_addwess = 0;
	state->i2c_wwite_addwess = 0;

	wet = s5c73m3_i2c_wwite(state->i2c_cwient, AHB_MSB_ADDW_PTW, 0x3310);
	if (wet < 0)
		wetuwn wet;

	if (boot_fwom_wom)
		wetuwn s5c73m3_wom_boot(state, twue);
	ewse
		wetuwn s5c73m3_spi_boot(state, twue);
}

static const stwuct s5c73m3_fwame_size *s5c73m3_find_fwame_size(
					stwuct v4w2_mbus_fwamefmt *fmt,
					enum s5c73m3_wesowution_types idx)
{
	const stwuct s5c73m3_fwame_size *fs;
	const stwuct s5c73m3_fwame_size *best_fs;
	int best_dist = INT_MAX;
	int i;

	fs = s5c73m3_wesowutions[idx];
	best_fs = NUWW;
	fow (i = 0; i < s5c73m3_wesowutions_wen[idx]; ++i) {
		int dist = abs(fs->width - fmt->width) +
						abs(fs->height - fmt->height);
		if (dist < best_dist) {
			best_dist = dist;
			best_fs = fs;
		}
		++fs;
	}

	wetuwn best_fs;
}

static void s5c73m3_oif_twy_fowmat(stwuct s5c73m3 *state,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fowmat *fmt,
				   const stwuct s5c73m3_fwame_size **fs)
{
	u32 code;

	switch (fmt->pad) {
	case OIF_ISP_PAD:
		*fs = s5c73m3_find_fwame_size(&fmt->fowmat, WES_ISP);
		code = S5C73M3_ISP_FMT;
		bweak;
	case OIF_JPEG_PAD:
		*fs = s5c73m3_find_fwame_size(&fmt->fowmat, WES_JPEG);
		code = S5C73M3_JPEG_FMT;
		bweak;
	case OIF_SOUWCE_PAD:
	defauwt:
		if (fmt->fowmat.code == S5C73M3_JPEG_FMT)
			code = S5C73M3_JPEG_FMT;
		ewse
			code = S5C73M3_ISP_FMT;

		if (fmt->which == V4W2_SUBDEV_FOWMAT_ACTIVE)
			*fs = state->oif_pix_size[WES_ISP];
		ewse
			*fs = s5c73m3_find_fwame_size(v4w2_subdev_state_get_fowmat(sd_state, OIF_ISP_PAD),
						      WES_ISP);
		bweak;
	}

	s5c73m3_fiww_mbus_fmt(&fmt->fowmat, *fs, code);
}

static void s5c73m3_twy_fowmat(stwuct s5c73m3 *state,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt,
			      const stwuct s5c73m3_fwame_size **fs)
{
	u32 code;

	if (fmt->pad == S5C73M3_ISP_PAD) {
		*fs = s5c73m3_find_fwame_size(&fmt->fowmat, WES_ISP);
		code = S5C73M3_ISP_FMT;
	} ewse {
		*fs = s5c73m3_find_fwame_size(&fmt->fowmat, WES_JPEG);
		code = S5C73M3_JPEG_FMT;
	}

	s5c73m3_fiww_mbus_fmt(&fmt->fowmat, *fs, code);
}

static int s5c73m3_oif_get_fwame_intewvaw(stwuct v4w2_subdev *sd,
					  stwuct v4w2_subdev_state *sd_state,
					  stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (fi->pad != OIF_SOUWCE_PAD)
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	fi->intewvaw = state->fiv->intewvaw;
	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int __s5c73m3_set_fwame_intewvaw(stwuct s5c73m3 *state,
					stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	const stwuct s5c73m3_fwame_size *pwev_size =
						state->sensow_pix_size[WES_ISP];
	const stwuct s5c73m3_intewvaw *fiv = &s5c73m3_intewvaws[0];
	unsigned int wet, min_eww = UINT_MAX;
	unsigned int i, fw_time;

	if (fi->intewvaw.denominatow == 0)
		wetuwn -EINVAW;

	fw_time = fi->intewvaw.numewatow * 1000 / fi->intewvaw.denominatow;

	fow (i = 0; i < AWWAY_SIZE(s5c73m3_intewvaws); i++) {
		const stwuct s5c73m3_intewvaw *iv = &s5c73m3_intewvaws[i];

		if (pwev_size->width > iv->size.width ||
		    pwev_size->height > iv->size.height)
			continue;

		wet = abs(iv->intewvaw.numewatow / 1000 - fw_time);
		if (wet < min_eww) {
			fiv = iv;
			min_eww = wet;
		}
	}
	state->fiv = fiv;

	v4w2_dbg(1, s5c73m3_dbg, &state->sensow_sd,
		 "Changed fwame intewvaw to %u us\n", fiv->intewvaw.numewatow);
	wetuwn 0;
}

static int s5c73m3_oif_set_fwame_intewvaw(stwuct v4w2_subdev *sd,
					  stwuct v4w2_subdev_state *sd_state,
					  stwuct v4w2_subdev_fwame_intewvaw *fi)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int wet;

	/*
	 * FIXME: Impwement suppowt fow V4W2_SUBDEV_FOWMAT_TWY, using the V4W2
	 * subdev active state API.
	 */
	if (fi->which != V4W2_SUBDEV_FOWMAT_ACTIVE)
		wetuwn -EINVAW;

	if (fi->pad != OIF_SOUWCE_PAD)
		wetuwn -EINVAW;

	v4w2_dbg(1, s5c73m3_dbg, sd, "Setting %d/%d fwame intewvaw\n",
		 fi->intewvaw.numewatow, fi->intewvaw.denominatow);

	mutex_wock(&state->wock);

	wet = __s5c73m3_set_fwame_intewvaw(state, fi);
	if (!wet) {
		if (state->stweaming)
			wet = s5c73m3_set_fwame_wate(state);
		ewse
			state->appwy_fiv = 1;
	}
	mutex_unwock(&state->wock);
	wetuwn wet;
}

static int s5c73m3_oif_enum_fwame_intewvaw(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fwame_intewvaw_enum *fie)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	const stwuct s5c73m3_intewvaw *fi;
	int wet = 0;

	if (fie->pad != OIF_SOUWCE_PAD)
		wetuwn -EINVAW;
	if (fie->index >= AWWAY_SIZE(s5c73m3_intewvaws))
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	fi = &s5c73m3_intewvaws[fie->index];
	if (fie->width > fi->size.width || fie->height > fi->size.height)
		wet = -EINVAW;
	ewse
		fie->intewvaw = fi->intewvaw;
	mutex_unwock(&state->wock);

	wetuwn wet;
}

static int s5c73m3_oif_get_pad_code(int pad, int index)
{
	if (pad == OIF_SOUWCE_PAD) {
		if (index > 1)
			wetuwn -EINVAW;
		wetuwn (index == 0) ? S5C73M3_ISP_FMT : S5C73M3_JPEG_FMT;
	}

	if (index > 0)
		wetuwn -EINVAW;

	wetuwn (pad == OIF_ISP_PAD) ? S5C73M3_ISP_FMT : S5C73M3_JPEG_FMT;
}

static int s5c73m3_get_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct s5c73m3 *state = sensow_sd_to_s5c73m3(sd);
	const stwuct s5c73m3_fwame_size *fs;
	u32 code;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);
		wetuwn 0;
	}

	mutex_wock(&state->wock);

	switch (fmt->pad) {
	case S5C73M3_ISP_PAD:
		code = S5C73M3_ISP_FMT;
		fs = state->sensow_pix_size[WES_ISP];
		bweak;
	case S5C73M3_JPEG_PAD:
		code = S5C73M3_JPEG_FMT;
		fs = state->sensow_pix_size[WES_JPEG];
		bweak;
	defauwt:
		mutex_unwock(&state->wock);
		wetuwn -EINVAW;
	}
	s5c73m3_fiww_mbus_fmt(&fmt->fowmat, fs, code);

	mutex_unwock(&state->wock);
	wetuwn 0;
}

static int s5c73m3_oif_get_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	const stwuct s5c73m3_fwame_size *fs;
	u32 code;

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		fmt->fowmat = *v4w2_subdev_state_get_fowmat(sd_state,
							    fmt->pad);
		wetuwn 0;
	}

	mutex_wock(&state->wock);

	switch (fmt->pad) {
	case OIF_ISP_PAD:
		code = S5C73M3_ISP_FMT;
		fs = state->oif_pix_size[WES_ISP];
		bweak;
	case OIF_JPEG_PAD:
		code = S5C73M3_JPEG_FMT;
		fs = state->oif_pix_size[WES_JPEG];
		bweak;
	case OIF_SOUWCE_PAD:
		code = state->mbus_code;
		fs = state->oif_pix_size[WES_ISP];
		bweak;
	defauwt:
		mutex_unwock(&state->wock);
		wetuwn -EINVAW;
	}
	s5c73m3_fiww_mbus_fmt(&fmt->fowmat, fs, code);

	mutex_unwock(&state->wock);
	wetuwn 0;
}

static int s5c73m3_set_fmt(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	const stwuct s5c73m3_fwame_size *fwame_size = NUWW;
	stwuct s5c73m3 *state = sensow_sd_to_s5c73m3(sd);
	stwuct v4w2_mbus_fwamefmt *mf;
	int wet = 0;

	mutex_wock(&state->wock);

	s5c73m3_twy_fowmat(state, sd_state, fmt, &fwame_size);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*mf = fmt->fowmat;
	} ewse {
		switch (fmt->pad) {
		case S5C73M3_ISP_PAD:
			state->sensow_pix_size[WES_ISP] = fwame_size;
			bweak;
		case S5C73M3_JPEG_PAD:
			state->sensow_pix_size[WES_JPEG] = fwame_size;
			bweak;
		defauwt:
			wet = -EBUSY;
		}

		if (state->stweaming)
			wet = -EBUSY;
		ewse
			state->appwy_fmt = 1;
	}

	mutex_unwock(&state->wock);

	wetuwn wet;
}

static int s5c73m3_oif_set_fmt(stwuct v4w2_subdev *sd,
			 stwuct v4w2_subdev_state *sd_state,
			 stwuct v4w2_subdev_fowmat *fmt)
{
	const stwuct s5c73m3_fwame_size *fwame_size = NUWW;
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	stwuct v4w2_mbus_fwamefmt *mf;
	int wet = 0;

	mutex_wock(&state->wock);

	s5c73m3_oif_twy_fowmat(state, sd_state, fmt, &fwame_size);

	if (fmt->which == V4W2_SUBDEV_FOWMAT_TWY) {
		mf = v4w2_subdev_state_get_fowmat(sd_state, fmt->pad);
		*mf = fmt->fowmat;
		if (fmt->pad == OIF_ISP_PAD) {
			mf = v4w2_subdev_state_get_fowmat(sd_state,
							  OIF_SOUWCE_PAD);
			mf->width = fmt->fowmat.width;
			mf->height = fmt->fowmat.height;
		}
	} ewse {
		switch (fmt->pad) {
		case OIF_ISP_PAD:
			state->oif_pix_size[WES_ISP] = fwame_size;
			bweak;
		case OIF_JPEG_PAD:
			state->oif_pix_size[WES_JPEG] = fwame_size;
			bweak;
		case OIF_SOUWCE_PAD:
			state->mbus_code = fmt->fowmat.code;
			bweak;
		defauwt:
			wet = -EBUSY;
		}

		if (state->stweaming)
			wet = -EBUSY;
		ewse
			state->appwy_fmt = 1;
	}

	mutex_unwock(&state->wock);

	wetuwn wet;
}

static int s5c73m3_oif_get_fwame_desc(stwuct v4w2_subdev *sd, unsigned int pad,
				  stwuct v4w2_mbus_fwame_desc *fd)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int i;

	if (pad != OIF_SOUWCE_PAD || fd == NUWW)
		wetuwn -EINVAW;

	mutex_wock(&state->wock);
	fd->num_entwies = 2;
	fow (i = 0; i < fd->num_entwies; i++)
		fd->entwy[i] = state->fwame_desc.entwy[i];
	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int s5c73m3_oif_set_fwame_desc(stwuct v4w2_subdev *sd, unsigned int pad,
				      stwuct v4w2_mbus_fwame_desc *fd)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	stwuct v4w2_mbus_fwame_desc *fwame_desc = &state->fwame_desc;
	int i;

	if (pad != OIF_SOUWCE_PAD || fd == NUWW)
		wetuwn -EINVAW;

	fd->entwy[0].wength = 10 * SZ_1M;
	fd->entwy[1].wength = max_t(u32, fd->entwy[1].wength,
				    S5C73M3_EMBEDDED_DATA_MAXWEN);
	fd->num_entwies = 2;

	mutex_wock(&state->wock);
	fow (i = 0; i < fd->num_entwies; i++)
		fwame_desc->entwy[i] = fd->entwy[i];
	mutex_unwock(&state->wock);

	wetuwn 0;
}

static int s5c73m3_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	static const int codes[] = {
			[S5C73M3_ISP_PAD] = S5C73M3_ISP_FMT,
			[S5C73M3_JPEG_PAD] = S5C73M3_JPEG_FMT};

	if (code->index > 0 || code->pad >= S5C73M3_NUM_PADS)
		wetuwn -EINVAW;

	code->code = codes[code->pad];

	wetuwn 0;
}

static int s5c73m3_oif_enum_mbus_code(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_mbus_code_enum *code)
{
	int wet;

	wet = s5c73m3_oif_get_pad_code(code->pad, code->index);
	if (wet < 0)
		wetuwn wet;

	code->code = wet;

	wetuwn 0;
}

static int s5c73m3_enum_fwame_size(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	int idx;

	if (fse->pad == S5C73M3_ISP_PAD) {
		if (fse->code != S5C73M3_ISP_FMT)
			wetuwn -EINVAW;
		idx = WES_ISP;
	} ewse{
		if (fse->code != S5C73M3_JPEG_FMT)
			wetuwn -EINVAW;
		idx = WES_JPEG;
	}

	if (fse->index >= s5c73m3_wesowutions_wen[idx])
		wetuwn -EINVAW;

	fse->min_width  = s5c73m3_wesowutions[idx][fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = s5c73m3_wesowutions[idx][fse->index].height;
	fse->min_height = fse->max_height;

	wetuwn 0;
}

static int s5c73m3_oif_enum_fwame_size(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int idx;

	if (fse->pad == OIF_SOUWCE_PAD) {
		if (fse->index > 0)
			wetuwn -EINVAW;

		switch (fse->code) {
		case S5C73M3_JPEG_FMT:
		case S5C73M3_ISP_FMT: {
			unsigned w, h;

			if (fse->which == V4W2_SUBDEV_FOWMAT_TWY) {
				stwuct v4w2_mbus_fwamefmt *mf;

				mf = v4w2_subdev_state_get_fowmat(sd_state,
								  OIF_ISP_PAD);

				w = mf->width;
				h = mf->height;
			} ewse {
				const stwuct s5c73m3_fwame_size *fs;

				fs = state->oif_pix_size[WES_ISP];
				w = fs->width;
				h = fs->height;
			}
			fse->max_width = fse->min_width = w;
			fse->max_height = fse->min_height = h;
			wetuwn 0;
		}
		defauwt:
			wetuwn -EINVAW;
		}
	}

	if (fse->code != s5c73m3_oif_get_pad_code(fse->pad, 0))
		wetuwn -EINVAW;

	if (fse->pad == OIF_JPEG_PAD)
		idx = WES_JPEG;
	ewse
		idx = WES_ISP;

	if (fse->index >= s5c73m3_wesowutions_wen[idx])
		wetuwn -EINVAW;

	fse->min_width  = s5c73m3_wesowutions[idx][fse->index].width;
	fse->max_width  = fse->min_width;
	fse->max_height = s5c73m3_wesowutions[idx][fse->index].height;
	fse->min_height = fse->max_height;

	wetuwn 0;
}

static int s5c73m3_oif_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);

	v4w2_ctww_handwew_wog_status(sd->ctww_handwew, sd->name);

	v4w2_info(sd, "powew: %d, appwy_fmt: %d\n", state->powew,
							state->appwy_fmt);

	wetuwn 0;
}

static int s5c73m3_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *mf;

	mf = v4w2_subdev_state_get_fowmat(fh->state, S5C73M3_ISP_PAD);
	s5c73m3_fiww_mbus_fmt(mf, &s5c73m3_isp_wesowutions[1],
						S5C73M3_ISP_FMT);

	mf = v4w2_subdev_state_get_fowmat(fh->state, S5C73M3_JPEG_PAD);
	s5c73m3_fiww_mbus_fmt(mf, &s5c73m3_jpeg_wesowutions[1],
					S5C73M3_JPEG_FMT);

	wetuwn 0;
}

static int s5c73m3_oif_open(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_mbus_fwamefmt *mf;

	mf = v4w2_subdev_state_get_fowmat(fh->state, OIF_ISP_PAD);
	s5c73m3_fiww_mbus_fmt(mf, &s5c73m3_isp_wesowutions[1],
						S5C73M3_ISP_FMT);

	mf = v4w2_subdev_state_get_fowmat(fh->state, OIF_JPEG_PAD);
	s5c73m3_fiww_mbus_fmt(mf, &s5c73m3_jpeg_wesowutions[1],
					S5C73M3_JPEG_FMT);

	mf = v4w2_subdev_state_get_fowmat(fh->state, OIF_SOUWCE_PAD);
	s5c73m3_fiww_mbus_fmt(mf, &s5c73m3_isp_wesowutions[1],
						S5C73M3_ISP_FMT);
	wetuwn 0;
}

static int __s5c73m3_powew_on(stwuct s5c73m3 *state)
{
	int i, wet;

	fow (i = 0; i < S5C73M3_MAX_SUPPWIES; i++) {
		wet = weguwatow_enabwe(state->suppwies[i].consumew);
		if (wet)
			goto eww_weg_dis;
	}

	wet = cwk_set_wate(state->cwock, state->mcwk_fwequency);
	if (wet < 0)
		goto eww_weg_dis;

	wet = cwk_pwepawe_enabwe(state->cwock);
	if (wet < 0)
		goto eww_weg_dis;

	v4w2_dbg(1, s5c73m3_dbg, &state->oif_sd, "cwock fwequency: %wd\n",
					cwk_get_wate(state->cwock));

	gpiod_set_vawue(state->stby, 0);
	usweep_wange(100, 200);
	gpiod_set_vawue(state->weset, 0);
	usweep_wange(50, 100);

	wetuwn 0;

eww_weg_dis:
	fow (--i; i >= 0; i--)
		weguwatow_disabwe(state->suppwies[i].consumew);
	wetuwn wet;
}

static int __s5c73m3_powew_off(stwuct s5c73m3 *state)
{
	int i, wet;

	gpiod_set_vawue(state->weset, 1);
	usweep_wange(10, 50);
	gpiod_set_vawue(state->stby, 1);
	usweep_wange(100, 200);

	cwk_disabwe_unpwepawe(state->cwock);

	state->stweaming = 0;
	state->isp_weady = 0;

	fow (i = S5C73M3_MAX_SUPPWIES - 1; i >= 0; i--) {
		wet = weguwatow_disabwe(state->suppwies[i].consumew);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	fow (++i; i < S5C73M3_MAX_SUPPWIES; i++) {
		int w = weguwatow_enabwe(state->suppwies[i].consumew);
		if (w < 0)
			v4w2_eww(&state->oif_sd, "Faiwed to we-enabwe %s: %d\n",
				 state->suppwies[i].suppwy, w);
	}

	cwk_pwepawe_enabwe(state->cwock);
	wetuwn wet;
}

static int s5c73m3_oif_set_powew(stwuct v4w2_subdev *sd, int on)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int wet = 0;

	mutex_wock(&state->wock);

	if (on && !state->powew) {
		wet = __s5c73m3_powew_on(state);
		if (!wet)
			wet = s5c73m3_isp_init(state);
		if (!wet) {
			state->appwy_fiv = 1;
			state->appwy_fmt = 1;
		}
	} ewse if (state->powew == !on) {
		wet = s5c73m3_set_af_softwanding(state);
		if (!wet)
			wet = __s5c73m3_powew_off(state);
		ewse
			v4w2_eww(sd, "Soft wanding wens faiwed\n");
	}
	if (!wet)
		state->powew += on ? 1 : -1;

	v4w2_dbg(1, s5c73m3_dbg, sd, "%s: powew: %d\n",
		 __func__, state->powew);

	mutex_unwock(&state->wock);
	wetuwn wet;
}

static int s5c73m3_oif_wegistewed(stwuct v4w2_subdev *sd)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int wet;

	wet = v4w2_device_wegistew_subdev(sd->v4w2_dev, &state->sensow_sd);
	if (wet) {
		v4w2_eww(sd->v4w2_dev, "Faiwed to wegistew %s\n",
							state->oif_sd.name);
		wetuwn wet;
	}

	wet = media_cweate_pad_wink(&state->sensow_sd.entity,
			S5C73M3_ISP_PAD, &state->oif_sd.entity, OIF_ISP_PAD,
			MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);

	wet = media_cweate_pad_wink(&state->sensow_sd.entity,
			S5C73M3_JPEG_PAD, &state->oif_sd.entity, OIF_JPEG_PAD,
			MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);

	wetuwn wet;
}

static void s5c73m3_oif_unwegistewed(stwuct v4w2_subdev *sd)
{
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	v4w2_device_unwegistew_subdev(&state->sensow_sd);
}

static const stwuct v4w2_subdev_intewnaw_ops s5c73m3_intewnaw_ops = {
	.open		= s5c73m3_open,
};

static const stwuct v4w2_subdev_pad_ops s5c73m3_pad_ops = {
	.enum_mbus_code		= s5c73m3_enum_mbus_code,
	.enum_fwame_size	= s5c73m3_enum_fwame_size,
	.get_fmt		= s5c73m3_get_fmt,
	.set_fmt		= s5c73m3_set_fmt,
};

static const stwuct v4w2_subdev_ops s5c73m3_subdev_ops = {
	.pad	= &s5c73m3_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops oif_intewnaw_ops = {
	.wegistewed	= s5c73m3_oif_wegistewed,
	.unwegistewed	= s5c73m3_oif_unwegistewed,
	.open		= s5c73m3_oif_open,
};

static const stwuct v4w2_subdev_pad_ops s5c73m3_oif_pad_ops = {
	.enum_mbus_code		= s5c73m3_oif_enum_mbus_code,
	.enum_fwame_size	= s5c73m3_oif_enum_fwame_size,
	.enum_fwame_intewvaw	= s5c73m3_oif_enum_fwame_intewvaw,
	.get_fmt		= s5c73m3_oif_get_fmt,
	.set_fmt		= s5c73m3_oif_set_fmt,
	.get_fwame_intewvaw	= s5c73m3_oif_get_fwame_intewvaw,
	.set_fwame_intewvaw	= s5c73m3_oif_set_fwame_intewvaw,
	.get_fwame_desc		= s5c73m3_oif_get_fwame_desc,
	.set_fwame_desc		= s5c73m3_oif_set_fwame_desc,
};

static const stwuct v4w2_subdev_cowe_ops s5c73m3_oif_cowe_ops = {
	.s_powew	= s5c73m3_oif_set_powew,
	.wog_status	= s5c73m3_oif_wog_status,
};

static const stwuct v4w2_subdev_video_ops s5c73m3_oif_video_ops = {
	.s_stweam		= s5c73m3_oif_s_stweam,
};

static const stwuct v4w2_subdev_ops oif_subdev_ops = {
	.cowe	= &s5c73m3_oif_cowe_ops,
	.pad	= &s5c73m3_oif_pad_ops,
	.video	= &s5c73m3_oif_video_ops,
};

static int s5c73m3_get_dt_data(stwuct s5c73m3 *state)
{
	stwuct device *dev = &state->i2c_cwient->dev;
	stwuct device_node *node = dev->of_node;
	stwuct device_node *node_ep;
	stwuct v4w2_fwnode_endpoint ep = { .bus_type = 0 };
	int wet;

	if (!node)
		wetuwn -EINVAW;

	state->cwock = devm_cwk_get(dev, S5C73M3_CWK_NAME);
	if (IS_EWW(state->cwock))
		wetuwn PTW_EWW(state->cwock);

	if (of_pwopewty_wead_u32(node, "cwock-fwequency",
				 &state->mcwk_fwequency)) {
		state->mcwk_fwequency = S5C73M3_DEFAUWT_MCWK_FWEQ;
		dev_info(dev, "using defauwt %u Hz cwock fwequency\n",
					state->mcwk_fwequency);
	}

	/* Wequest GPIO wines assewted */
	state->stby = devm_gpiod_get(dev, "standby", GPIOD_OUT_HIGH);
	if (IS_EWW(state->stby))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(state->stby),
				     "faiwed to wequest gpio S5C73M3_STBY\n");
	gpiod_set_consumew_name(state->stby, "S5C73M3_STBY");
	state->weset = devm_gpiod_get(dev, "xshutdown", GPIOD_OUT_HIGH);
	if (IS_EWW(state->weset))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(state->weset),
				     "faiwed to wequest gpio S5C73M3_WST\n");
	gpiod_set_consumew_name(state->weset, "S5C73M3_WST");

	node_ep = of_gwaph_get_next_endpoint(node, NUWW);
	if (!node_ep) {
		dev_wawn(dev, "no endpoint defined fow node: %pOF\n", node);
		wetuwn 0;
	}

	wet = v4w2_fwnode_endpoint_pawse(of_fwnode_handwe(node_ep), &ep);
	of_node_put(node_ep);
	if (wet)
		wetuwn wet;

	if (ep.bus_type != V4W2_MBUS_CSI2_DPHY) {
		dev_eww(dev, "unsuppowted bus type\n");
		wetuwn -EINVAW;
	}
	/*
	 * Numbew of MIPI CSI-2 data wanes is cuwwentwy not configuwabwe,
	 * awways a defauwt vawue of 4 wanes is used.
	 */
	if (ep.bus.mipi_csi2.num_data_wanes != S5C73M3_MIPI_DATA_WANES)
		dev_info(dev, "fawwing back to 4 MIPI CSI-2 data wanes\n");

	wetuwn 0;
}

static int s5c73m3_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct v4w2_subdev *sd;
	stwuct v4w2_subdev *oif_sd;
	stwuct s5c73m3 *state;
	int wet, i;

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->i2c_cwient = cwient;
	wet = s5c73m3_get_dt_data(state);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&state->wock);
	sd = &state->sensow_sd;
	oif_sd = &state->oif_sd;

	v4w2_subdev_init(sd, &s5c73m3_subdev_ops);
	sd->ownew = cwient->dev.dwivew->ownew;
	v4w2_set_subdevdata(sd, state);
	stwscpy(sd->name, "S5C73M3", sizeof(sd->name));

	sd->intewnaw_ops = &s5c73m3_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	state->sensow_pads[S5C73M3_JPEG_PAD].fwags = MEDIA_PAD_FW_SOUWCE;
	state->sensow_pads[S5C73M3_ISP_PAD].fwags = MEDIA_PAD_FW_SOUWCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOW;

	wet = media_entity_pads_init(&sd->entity, S5C73M3_NUM_PADS,
							state->sensow_pads);
	if (wet < 0)
		wetuwn wet;

	v4w2_i2c_subdev_init(oif_sd, cwient, &oif_subdev_ops);
	/* Static name; NEVEW use in new dwivews! */
	stwscpy(oif_sd->name, "S5C73M3-OIF", sizeof(oif_sd->name));

	oif_sd->intewnaw_ops = &oif_intewnaw_ops;
	oif_sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	state->oif_pads[OIF_ISP_PAD].fwags = MEDIA_PAD_FW_SINK;
	state->oif_pads[OIF_JPEG_PAD].fwags = MEDIA_PAD_FW_SINK;
	state->oif_pads[OIF_SOUWCE_PAD].fwags = MEDIA_PAD_FW_SOUWCE;
	oif_sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_SCAWEW;

	wet = media_entity_pads_init(&oif_sd->entity, OIF_NUM_PADS,
							state->oif_pads);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < S5C73M3_MAX_SUPPWIES; i++)
		state->suppwies[i].suppwy = s5c73m3_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, S5C73M3_MAX_SUPPWIES,
			       state->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to get weguwatows\n");
		goto out_eww;
	}

	wet = s5c73m3_init_contwows(state);
	if (wet)
		goto out_eww;

	state->sensow_pix_size[WES_ISP] = &s5c73m3_isp_wesowutions[1];
	state->sensow_pix_size[WES_JPEG] = &s5c73m3_jpeg_wesowutions[1];
	state->oif_pix_size[WES_ISP] = state->sensow_pix_size[WES_ISP];
	state->oif_pix_size[WES_JPEG] = state->sensow_pix_size[WES_JPEG];

	state->mbus_code = S5C73M3_ISP_FMT;

	state->fiv = &s5c73m3_intewvaws[S5C73M3_DEFAUWT_FWAME_INTEWVAW];

	state->fw_fiwe_vewsion[0] = 'G';
	state->fw_fiwe_vewsion[1] = 'C';

	wet = s5c73m3_wegistew_spi_dwivew(state);
	if (wet < 0)
		goto out_eww;

	oif_sd->dev = dev;

	wet = __s5c73m3_powew_on(state);
	if (wet < 0)
		goto out_eww1;

	wet = s5c73m3_get_fw_vewsion(state);
	__s5c73m3_powew_off(state);

	if (wet < 0) {
		dev_eww(dev, "Device detection faiwed: %d\n", wet);
		goto out_eww1;
	}

	wet = v4w2_async_wegistew_subdev(oif_sd);
	if (wet < 0)
		goto out_eww1;

	v4w2_info(sd, "%s: compweted successfuwwy\n", __func__);
	wetuwn 0;

out_eww1:
	s5c73m3_unwegistew_spi_dwivew(state);
out_eww:
	media_entity_cweanup(&sd->entity);
	wetuwn wet;
}

static void s5c73m3_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *oif_sd = i2c_get_cwientdata(cwient);
	stwuct s5c73m3 *state = oif_sd_to_s5c73m3(oif_sd);
	stwuct v4w2_subdev *sensow_sd = &state->sensow_sd;

	v4w2_async_unwegistew_subdev(oif_sd);

	v4w2_ctww_handwew_fwee(oif_sd->ctww_handwew);
	media_entity_cweanup(&oif_sd->entity);

	v4w2_device_unwegistew_subdev(sensow_sd);
	media_entity_cweanup(&sensow_sd->entity);

	s5c73m3_unwegistew_spi_dwivew(state);
}

static const stwuct i2c_device_id s5c73m3_id[] = {
	{ DWIVEW_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, s5c73m3_id);

#ifdef CONFIG_OF
static const stwuct of_device_id s5c73m3_of_match[] = {
	{ .compatibwe = "samsung,s5c73m3" },
	{ }
};
MODUWE_DEVICE_TABWE(of, s5c73m3_of_match);
#endif

static stwuct i2c_dwivew s5c73m3_i2c_dwivew = {
	.dwivew = {
		.of_match_tabwe = of_match_ptw(s5c73m3_of_match),
		.name	= DWIVEW_NAME,
	},
	.pwobe		= s5c73m3_pwobe,
	.wemove		= s5c73m3_wemove,
	.id_tabwe	= s5c73m3_id,
};

moduwe_i2c_dwivew(s5c73m3_i2c_dwivew);

MODUWE_DESCWIPTION("Samsung S5C73M3 camewa dwivew");
MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_WICENSE("GPW");
