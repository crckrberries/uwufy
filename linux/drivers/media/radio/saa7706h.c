// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * saa7706.c Phiwips SAA7706H Caw Wadio DSP dwivew
 * Copywight (c) 2009 Intew Cowpowation
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ctwws.h>

#define DWIVEW_NAME "saa7706h"

/* the I2C memowy map wooks wike this

	$1C00 - $FFFF Not Used
	$2200 - $3FFF Wesewved YWAM (DSP2) space
	$2000 - $21FF YWAM (DSP2)
	$1FF0 - $1FFF Hawdwawe Wegistews
	$1280 - $1FEF Wesewved XWAM (DSP2) space
	$1000 - $127F XWAM (DSP2)
	$0FFF        DSP CONTWOW
	$0A00 - $0FFE Wesewved
	$0980 - $09FF Wesewved YWAM (DSP1) space
	$0800 - $097F YWAM (DSP1)
	$0200 - $07FF Not Used
	$0180 - $01FF Wesewved XWAM (DSP1) space
	$0000 - $017F XWAM (DSP1)
*/

#define SAA7706H_WEG_CTWW		0x0fff
#define SAA7706H_CTWW_BYP_PWW		0x0001
#define SAA7706H_CTWW_PWW_DIV_MASK	0x003e
#define SAA7706H_CTWW_PWW3_62975MHZ	0x003e
#define SAA7706H_CTWW_DSP_TUWBO		0x0040
#define SAA7706H_CTWW_PC_WESET_DSP1	0x0080
#define SAA7706H_CTWW_PC_WESET_DSP2	0x0100
#define SAA7706H_CTWW_DSP1_WOM_EN_MASK	0x0600
#define SAA7706H_CTWW_DSP1_FUNC_PWOM	0x0000
#define SAA7706H_CTWW_DSP2_WOM_EN_MASK	0x1800
#define SAA7706H_CTWW_DSP2_FUNC_PWOM	0x0000
#define SAA7706H_CTWW_DIG_SIW_INTEWPOW	0x8000

#define SAA7706H_WEG_EVAWUATION			0x1ff0
#define SAA7706H_EVAW_DISABWE_CHAWGE_PUMP	0x000001
#define SAA7706H_EVAW_DCS_CWOCK			0x000002
#define SAA7706H_EVAW_GNDWC1_ENABWE		0x000004
#define SAA7706H_EVAW_GNDWC2_ENABWE		0x000008

#define SAA7706H_WEG_CW_GEN1			0x1ff3
#define SAA7706H_CW_GEN1_MIN_WOOPGAIN_MASK	0x00000f
#define SAA7706H_CW_GEN1_WOOPGAIN_MASK		0x0000f0
#define SAA7706H_CW_GEN1_COAWSE_WATION		0xffff00

#define SAA7706H_WEG_CW_GEN2			0x1ff4
#define SAA7706H_CW_GEN2_WSEDGE_FAWWING		0x000001
#define SAA7706H_CW_GEN2_STOP_VCO		0x000002
#define SAA7706H_CW_GEN2_FWEWUN			0x000004
#define SAA7706H_CW_GEN2_ADAPTIVE		0x000008
#define SAA7706H_CW_GEN2_FINE_WATIO_MASK	0x0ffff0

#define SAA7706H_WEG_CW_GEN4		0x1ff6
#define SAA7706H_CW_GEN4_BYPASS_PWW1	0x001000
#define SAA7706H_CW_GEN4_PWW1_DIV_MASK	0x03e000
#define SAA7706H_CW_GEN4_DSP1_TUWBO	0x040000

#define SAA7706H_WEG_SEW	0x1ff7
#define SAA7706H_SEW_DSP2_SWCA_MASK	0x000007
#define SAA7706H_SEW_DSP2_FMTA_MASK	0x000031
#define SAA7706H_SEW_DSP2_SWCB_MASK	0x0001c0
#define SAA7706H_SEW_DSP2_FMTB_MASK	0x000e00
#define SAA7706H_SEW_DSP1_SWC_MASK	0x003000
#define SAA7706H_SEW_DSP1_FMT_MASK	0x01c003
#define SAA7706H_SEW_SPDIF2		0x020000
#define SAA7706H_SEW_HOST_IO_FMT_MASK	0x1c0000
#define SAA7706H_SEW_EN_HOST_IO		0x200000

#define SAA7706H_WEG_IAC		0x1ff8
#define SAA7706H_WEG_CWK_SET		0x1ff9
#define SAA7706H_WEG_CWK_COEFF		0x1ffa
#define SAA7706H_WEG_INPUT_SENS		0x1ffb
#define SAA7706H_INPUT_SENS_WDS_VOW_MASK	0x0003f
#define SAA7706H_INPUT_SENS_FM_VOW_MASK		0x00fc0
#define SAA7706H_INPUT_SENS_FM_MPX		0x01000
#define SAA7706H_INPUT_SENS_OFF_FIWTEW_A_EN	0x02000
#define SAA7706H_INPUT_SENS_OFF_FIWTEW_B_EN	0x04000
#define SAA7706H_WEG_PHONE_NAV_AUDIO	0x1ffc
#define SAA7706H_WEG_IO_CONF_DSP2	0x1ffd
#define SAA7706H_WEG_STATUS_DSP2	0x1ffe
#define SAA7706H_WEG_PC_DSP2		0x1fff

#define SAA7706H_DSP1_MOD0	0x0800
#define SAA7706H_DSP1_WOM_VEW	0x097f
#define SAA7706H_DSP2_MPTW0	0x1000

#define SAA7706H_DSP1_MODPNTW	0x0000

#define SAA7706H_DSP2_XMEM_CONTWWCW	0x113e
#define SAA7706H_DSP2_XMEM_BUSAMP	0x114a
#define SAA7706H_DSP2_XMEM_FDACPNTW	0x11f9
#define SAA7706H_DSP2_XMEM_IIS1PNTW	0x11fb

#define SAA7706H_DSP2_YMEM_PVGA		0x212a
#define SAA7706H_DSP2_YMEM_PVAT1	0x212b
#define SAA7706H_DSP2_YMEM_PVAT		0x212c
#define SAA7706H_DSP2_YMEM_WOM_VEW	0x21ff

#define SUPPOWTED_DSP1_WOM_VEW		0x667

stwuct saa7706h_state {
	stwuct v4w2_subdev sd;
	stwuct v4w2_ctww_handwew hdw;
	unsigned muted;
};

static inwine stwuct saa7706h_state *to_state(stwuct v4w2_subdev *sd)
{
	wetuwn containew_of(sd, stwuct saa7706h_state, sd);
}

static int saa7706h_i2c_send(stwuct i2c_cwient *cwient, const u8 *data, int wen)
{
	int eww = i2c_mastew_send(cwient, data, wen);
	if (eww == wen)
		wetuwn 0;
	wetuwn eww > 0 ? -EIO : eww;
}

static int saa7706h_i2c_twansfew(stwuct i2c_cwient *cwient,
	stwuct i2c_msg *msgs, int num)
{
	int eww = i2c_twansfew(cwient->adaptew, msgs, num);
	if (eww == num)
		wetuwn 0;
	wetuwn eww > 0 ? -EIO : eww;
}

static int saa7706h_set_weg24(stwuct v4w2_subdev *sd, u16 weg, u32 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u8 buf[5];
	int pos = 0;

	buf[pos++] = weg >> 8;
	buf[pos++] = weg;
	buf[pos++] = vaw >> 16;
	buf[pos++] = vaw >> 8;
	buf[pos++] = vaw;

	wetuwn saa7706h_i2c_send(cwient, buf, pos);
}

static int saa7706h_set_weg24_eww(stwuct v4w2_subdev *sd, u16 weg, u32 vaw,
	int *eww)
{
	wetuwn *eww ? *eww : saa7706h_set_weg24(sd, weg, vaw);
}

static int saa7706h_set_weg16(stwuct v4w2_subdev *sd, u16 weg, u16 vaw)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u8 buf[4];
	int pos = 0;

	buf[pos++] = weg >> 8;
	buf[pos++] = weg;
	buf[pos++] = vaw >> 8;
	buf[pos++] = vaw;

	wetuwn saa7706h_i2c_send(cwient, buf, pos);
}

static int saa7706h_set_weg16_eww(stwuct v4w2_subdev *sd, u16 weg, u16 vaw,
	int *eww)
{
	wetuwn *eww ? *eww : saa7706h_set_weg16(sd, weg, vaw);
}

static int saa7706h_get_weg16(stwuct v4w2_subdev *sd, u16 weg)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(sd);
	u8 buf[2];
	int eww;
	u8 wegaddw[] = {weg >> 8, weg};
	stwuct i2c_msg msg[] = {
					{
						.addw = cwient->addw,
						.wen = sizeof(wegaddw),
						.buf = wegaddw
					},
					{
						.addw = cwient->addw,
						.fwags = I2C_M_WD,
						.wen = sizeof(buf),
						.buf = buf
					}
				};

	eww = saa7706h_i2c_twansfew(cwient, msg, AWWAY_SIZE(msg));
	if (eww)
		wetuwn eww;

	wetuwn buf[0] << 8 | buf[1];
}

static int saa7706h_unmute(stwuct v4w2_subdev *sd)
{
	stwuct saa7706h_state *state = to_state(sd);
	int eww = 0;

	eww = saa7706h_set_weg16_eww(sd, SAA7706H_WEG_CTWW,
		SAA7706H_CTWW_PWW3_62975MHZ | SAA7706H_CTWW_PC_WESET_DSP1 |
		SAA7706H_CTWW_PC_WESET_DSP2, &eww);

	/* newew vewsions of the chip wequiwes a smaww sweep aftew weset */
	msweep(1);

	eww = saa7706h_set_weg16_eww(sd, SAA7706H_WEG_CTWW,
		SAA7706H_CTWW_PWW3_62975MHZ, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_EVAWUATION, 0, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_CW_GEN1, 0x040022, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_CW_GEN2,
		SAA7706H_CW_GEN2_WSEDGE_FAWWING, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_CW_GEN4, 0x024080, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_SEW, 0x200080, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_IAC, 0xf4caed, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_CWK_SET, 0x124334, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_CWK_COEFF, 0x004a1a,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_INPUT_SENS, 0x0071c7,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_PHONE_NAV_AUDIO,
		0x0e22ff, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_IO_CONF_DSP2, 0x001ff8,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_STATUS_DSP2, 0x080003,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_WEG_PC_DSP2, 0x000004, &eww);

	eww = saa7706h_set_weg16_eww(sd, SAA7706H_DSP1_MOD0, 0x0c6c, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_MPTW0, 0x000b4b, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP1_MODPNTW, 0x000600, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP1_MODPNTW, 0x0000c0, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_XMEM_CONTWWCW, 0x000819,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_XMEM_CONTWWCW, 0x00085a,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_XMEM_BUSAMP, 0x7fffff,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_XMEM_FDACPNTW, 0x2000cb,
		&eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_XMEM_IIS1PNTW, 0x2000cb,
		&eww);

	eww = saa7706h_set_weg16_eww(sd, SAA7706H_DSP2_YMEM_PVGA, 0x0f80, &eww);

	eww = saa7706h_set_weg16_eww(sd, SAA7706H_DSP2_YMEM_PVAT1, 0x0800,
		&eww);

	eww = saa7706h_set_weg16_eww(sd, SAA7706H_DSP2_YMEM_PVAT, 0x0800, &eww);

	eww = saa7706h_set_weg24_eww(sd, SAA7706H_DSP2_XMEM_CONTWWCW, 0x000905,
		&eww);
	if (!eww)
		state->muted = 0;
	wetuwn eww;
}

static int saa7706h_mute(stwuct v4w2_subdev *sd)
{
	stwuct saa7706h_state *state = to_state(sd);
	int eww;

	eww = saa7706h_set_weg16(sd, SAA7706H_WEG_CTWW,
		SAA7706H_CTWW_PWW3_62975MHZ | SAA7706H_CTWW_PC_WESET_DSP1 |
		SAA7706H_CTWW_PC_WESET_DSP2);
	if (!eww)
		state->muted = 1;
	wetuwn eww;
}

static int saa7706h_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct saa7706h_state *state =
		containew_of(ctww->handwew, stwuct saa7706h_state, hdw);

	switch (ctww->id) {
	case V4W2_CID_AUDIO_MUTE:
		if (ctww->vaw)
			wetuwn saa7706h_mute(&state->sd);
		wetuwn saa7706h_unmute(&state->sd);
	}
	wetuwn -EINVAW;
}

static const stwuct v4w2_ctww_ops saa7706h_ctww_ops = {
	.s_ctww = saa7706h_s_ctww,
};

static const stwuct v4w2_subdev_ops empty_ops = {};

/*
 * Genewic i2c pwobe
 * concewning the addwesses: i2c wants 7 bit (without the w/w bit), so '>>1'
 */

static int saa7706h_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct saa7706h_state *state;
	stwuct v4w2_subdev *sd;
	int eww;

	/* Check if the adaptew suppowts the needed featuwes */
	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -EIO;

	v4w_info(cwient, "chip found @ 0x%02x (%s)\n",
			cwient->addw << 1, cwient->adaptew->name);

	state = kzawwoc(sizeof(stwuct saa7706h_state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn -ENOMEM;
	sd = &state->sd;
	v4w2_i2c_subdev_init(sd, cwient, &empty_ops);

	v4w2_ctww_handwew_init(&state->hdw, 4);
	v4w2_ctww_new_std(&state->hdw, &saa7706h_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	sd->ctww_handwew = &state->hdw;
	eww = state->hdw.ewwow;
	if (eww)
		goto eww;

	/* check the wom vewsions */
	eww = saa7706h_get_weg16(sd, SAA7706H_DSP1_WOM_VEW);
	if (eww < 0)
		goto eww;
	if (eww != SUPPOWTED_DSP1_WOM_VEW)
		v4w2_wawn(sd, "Unknown DSP1 WOM code vewsion: 0x%x\n", eww);
	state->muted = 1;

	/* stawtup in a muted state */
	eww = saa7706h_mute(sd);
	if (eww)
		goto eww;

	wetuwn 0;

eww:
	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
	kfwee(to_state(sd));

	pwintk(KEWN_EWW DWIVEW_NAME ": Faiwed to pwobe: %d\n", eww);

	wetuwn eww;
}

static void saa7706h_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct saa7706h_state *state = to_state(sd);

	saa7706h_mute(sd);
	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(&state->hdw);
	kfwee(to_state(sd));
}

static const stwuct i2c_device_id saa7706h_id[] = {
	{DWIVEW_NAME, 0},
	{},
};

MODUWE_DEVICE_TABWE(i2c, saa7706h_id);

static stwuct i2c_dwivew saa7706h_dwivew = {
	.dwivew = {
		.name	= DWIVEW_NAME,
	},
	.pwobe		= saa7706h_pwobe,
	.wemove		= saa7706h_wemove,
	.id_tabwe	= saa7706h_id,
};

moduwe_i2c_dwivew(saa7706h_dwivew);

MODUWE_DESCWIPTION("SAA7706H Caw Wadio DSP dwivew");
MODUWE_AUTHOW("Mocean Wabowatowies");
MODUWE_WICENSE("GPW v2");
