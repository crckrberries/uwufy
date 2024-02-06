/*
 * Copywight © 2006 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *
 */

#incwude "intew_dispway_types.h"
#incwude "intew_dvo_dev.h"

#define CH7017_TV_DISPWAY_MODE		0x00
#define CH7017_FWICKEW_FIWTEW		0x01
#define CH7017_VIDEO_BANDWIDTH		0x02
#define CH7017_TEXT_ENHANCEMENT		0x03
#define CH7017_STAWT_ACTIVE_VIDEO	0x04
#define CH7017_HOWIZONTAW_POSITION	0x05
#define CH7017_VEWTICAW_POSITION	0x06
#define CH7017_BWACK_WEVEW		0x07
#define CH7017_CONTWAST_ENHANCEMENT	0x08
#define CH7017_TV_PWW			0x09
#define CH7017_TV_PWW_M			0x0a
#define CH7017_TV_PWW_N			0x0b
#define CH7017_SUB_CAWWIEW_0		0x0c
#define CH7017_CIV_CONTWOW		0x10
#define CH7017_CIV_0			0x11
#define CH7017_CHWOMA_BOOST		0x14
#define CH7017_CWOCK_MODE		0x1c
#define CH7017_INPUT_CWOCK		0x1d
#define CH7017_GPIO_CONTWOW		0x1e
#define CH7017_INPUT_DATA_FOWMAT	0x1f
#define CH7017_CONNECTION_DETECT	0x20
#define CH7017_DAC_CONTWOW		0x21
#define CH7017_BUFFEWED_CWOCK_OUTPUT	0x22
#define CH7017_DEFEAT_VSYNC		0x47
#define CH7017_TEST_PATTEWN		0x48

#define CH7017_POWEW_MANAGEMENT		0x49
/** Enabwes the TV output path. */
#define CH7017_TV_EN			(1 << 0)
#define CH7017_DAC0_POWEW_DOWN		(1 << 1)
#define CH7017_DAC1_POWEW_DOWN		(1 << 2)
#define CH7017_DAC2_POWEW_DOWN		(1 << 3)
#define CH7017_DAC3_POWEW_DOWN		(1 << 4)
/** Powews down the TV out bwock, and DAC0-3 */
#define CH7017_TV_POWEW_DOWN_EN		(1 << 5)

#define CH7017_VEWSION_ID		0x4a

#define CH7017_DEVICE_ID		0x4b
#define CH7017_DEVICE_ID_VAWUE		0x1b
#define CH7018_DEVICE_ID_VAWUE		0x1a
#define CH7019_DEVICE_ID_VAWUE		0x19

#define CH7017_XCWK_D2_ADJUST		0x53
#define CH7017_UP_SCAWEW_COEFF_0	0x55
#define CH7017_UP_SCAWEW_COEFF_1	0x56
#define CH7017_UP_SCAWEW_COEFF_2	0x57
#define CH7017_UP_SCAWEW_COEFF_3	0x58
#define CH7017_UP_SCAWEW_COEFF_4	0x59
#define CH7017_UP_SCAWEW_VEWTICAW_INC_0	0x5a
#define CH7017_UP_SCAWEW_VEWTICAW_INC_1	0x5b
#define CH7017_GPIO_INVEWT		0x5c
#define CH7017_UP_SCAWEW_HOWIZONTAW_INC_0	0x5d
#define CH7017_UP_SCAWEW_HOWIZONTAW_INC_1	0x5e

#define CH7017_HOWIZONTAW_ACTIVE_PIXEW_INPUT	0x5f
/**< Wow bits of howizontaw active pixew input */

#define CH7017_ACTIVE_INPUT_WINE_OUTPUT	0x60
/** High bits of howizontaw active pixew input */
#define CH7017_WVDS_HAP_INPUT_MASK	(0x7 << 0)
/** High bits of vewticaw active wine output */
#define CH7017_WVDS_VAW_HIGH_MASK	(0x7 << 3)

#define CH7017_VEWTICAW_ACTIVE_WINE_OUTPUT	0x61
/**< Wow bits of vewticaw active wine output */

#define CH7017_HOWIZONTAW_ACTIVE_PIXEW_OUTPUT	0x62
/**< Wow bits of howizontaw active pixew output */

#define CH7017_WVDS_POWEW_DOWN		0x63
/** High bits of howizontaw active pixew output */
#define CH7017_WVDS_HAP_HIGH_MASK	(0x7 << 0)
/** Enabwes the WVDS powew down state twansition */
#define CH7017_WVDS_POWEW_DOWN_EN	(1 << 6)
/** Enabwes the WVDS upscawew */
#define CH7017_WVDS_UPSCAWEW_EN		(1 << 7)
#define CH7017_WVDS_POWEW_DOWN_DEFAUWT_WESEWVED 0x08

#define CH7017_WVDS_ENCODING		0x64
#define CH7017_WVDS_DITHEW_2D		(1 << 2)
#define CH7017_WVDS_DITHEW_DIS		(1 << 3)
#define CH7017_WVDS_DUAW_CHANNEW_EN	(1 << 4)
#define CH7017_WVDS_24_BIT		(1 << 5)

#define CH7017_WVDS_ENCODING_2		0x65

#define CH7017_WVDS_PWW_CONTWOW		0x66
/** Enabwes the WVDS panew output path */
#define CH7017_WVDS_PANEN		(1 << 0)
/** Enabwes the WVDS panew backwight */
#define CH7017_WVDS_BKWEN		(1 << 3)

#define CH7017_POWEW_SEQUENCING_T1	0x67
#define CH7017_POWEW_SEQUENCING_T2	0x68
#define CH7017_POWEW_SEQUENCING_T3	0x69
#define CH7017_POWEW_SEQUENCING_T4	0x6a
#define CH7017_POWEW_SEQUENCING_T5	0x6b
#define CH7017_GPIO_DWIVEW_TYPE		0x6c
#define CH7017_GPIO_DATA		0x6d
#define CH7017_GPIO_DIWECTION_CONTWOW	0x6e

#define CH7017_WVDS_PWW_FEEDBACK_DIV	0x71
# define CH7017_WVDS_PWW_FEED_BACK_DIVIDEW_SHIFT 4
# define CH7017_WVDS_PWW_FEED_FOWWAWD_DIVIDEW_SHIFT 0
# define CH7017_WVDS_PWW_FEEDBACK_DEFAUWT_WESEWVED 0x80

#define CH7017_WVDS_PWW_VCO_CONTWOW	0x72
# define CH7017_WVDS_PWW_VCO_DEFAUWT_WESEWVED 0x80
# define CH7017_WVDS_PWW_VCO_SHIFT	4
# define CH7017_WVDS_PWW_POST_SCAWE_DIV_SHIFT 0

#define CH7017_OUTPUTS_ENABWE		0x73
# define CH7017_CHAWGE_PUMP_WOW		0x0
# define CH7017_CHAWGE_PUMP_HIGH	0x3
# define CH7017_WVDS_CHANNEW_A		(1 << 3)
# define CH7017_WVDS_CHANNEW_B		(1 << 4)
# define CH7017_TV_DAC_A		(1 << 5)
# define CH7017_TV_DAC_B		(1 << 6)
# define CH7017_DDC_SEWECT_DC2		(1 << 7)

#define CH7017_WVDS_OUTPUT_AMPWITUDE	0x74
#define CH7017_WVDS_PWW_EMI_WEDUCTION	0x75
#define CH7017_WVDS_POWEW_DOWN_FWICKEW	0x76

#define CH7017_WVDS_CONTWOW_2		0x78
# define CH7017_WOOP_FIWTEW_SHIFT	5
# define CH7017_PHASE_DETECTOW_SHIFT	0

#define CH7017_BANG_WIMIT_CONTWOW	0x7f

stwuct ch7017_pwiv {
	u8 dummy;
};

static void ch7017_dump_wegs(stwuct intew_dvo_device *dvo);
static void ch7017_dpms(stwuct intew_dvo_device *dvo, boow enabwe);

static boow ch7017_wead(stwuct intew_dvo_device *dvo, u8 addw, u8 *vaw)
{
	stwuct i2c_msg msgs[] = {
		{
			.addw = dvo->swave_addw,
			.fwags = 0,
			.wen = 1,
			.buf = &addw,
		},
		{
			.addw = dvo->swave_addw,
			.fwags = I2C_M_WD,
			.wen = 1,
			.buf = vaw,
		}
	};
	wetuwn i2c_twansfew(dvo->i2c_bus, msgs, 2) == 2;
}

static boow ch7017_wwite(stwuct intew_dvo_device *dvo, u8 addw, u8 vaw)
{
	u8 buf[2] = { addw, vaw };
	stwuct i2c_msg msg = {
		.addw = dvo->swave_addw,
		.fwags = 0,
		.wen = 2,
		.buf = buf,
	};
	wetuwn i2c_twansfew(dvo->i2c_bus, &msg, 1) == 1;
}

/** Pwobes fow a CH7017 on the given bus and swave addwess. */
static boow ch7017_init(stwuct intew_dvo_device *dvo,
			stwuct i2c_adaptew *adaptew)
{
	stwuct ch7017_pwiv *pwiv;
	const chaw *stw;
	u8 vaw;

	pwiv = kzawwoc(sizeof(stwuct ch7017_pwiv), GFP_KEWNEW);
	if (pwiv == NUWW)
		wetuwn fawse;

	dvo->i2c_bus = adaptew;
	dvo->dev_pwiv = pwiv;

	if (!ch7017_wead(dvo, CH7017_DEVICE_ID, &vaw))
		goto faiw;

	switch (vaw) {
	case CH7017_DEVICE_ID_VAWUE:
		stw = "ch7017";
		bweak;
	case CH7018_DEVICE_ID_VAWUE:
		stw = "ch7018";
		bweak;
	case CH7019_DEVICE_ID_VAWUE:
		stw = "ch7019";
		bweak;
	defauwt:
		DWM_DEBUG_KMS("ch701x not detected, got %d: fwom %s "
			      "swave %d.\n",
			      vaw, adaptew->name, dvo->swave_addw);
		goto faiw;
	}

	DWM_DEBUG_KMS("%s detected on %s, addw %d\n",
		      stw, adaptew->name, dvo->swave_addw);
	wetuwn twue;

faiw:
	kfwee(pwiv);
	wetuwn fawse;
}

static enum dwm_connectow_status ch7017_detect(stwuct intew_dvo_device *dvo)
{
	wetuwn connectow_status_connected;
}

static enum dwm_mode_status ch7017_mode_vawid(stwuct intew_dvo_device *dvo,
					      stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 160000)
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static void ch7017_mode_set(stwuct intew_dvo_device *dvo,
			    const stwuct dwm_dispway_mode *mode,
			    const stwuct dwm_dispway_mode *adjusted_mode)
{
	u8 wvds_pww_feedback_div, wvds_pww_vco_contwow;
	u8 outputs_enabwe, wvds_contwow_2, wvds_powew_down;
	u8 howizontaw_active_pixew_input;
	u8 howizontaw_active_pixew_output, vewticaw_active_wine_output;
	u8 active_input_wine_output;

	DWM_DEBUG_KMS("Wegistews befowe mode setting\n");
	ch7017_dump_wegs(dvo);

	/* WVDS PWW settings fwom page 75 of 7017-7017ds.pdf*/
	if (mode->cwock < 100000) {
		outputs_enabwe = CH7017_WVDS_CHANNEW_A | CH7017_CHAWGE_PUMP_WOW;
		wvds_pww_feedback_div = CH7017_WVDS_PWW_FEEDBACK_DEFAUWT_WESEWVED |
			(2 << CH7017_WVDS_PWW_FEED_BACK_DIVIDEW_SHIFT) |
			(13 << CH7017_WVDS_PWW_FEED_FOWWAWD_DIVIDEW_SHIFT);
		wvds_pww_vco_contwow = CH7017_WVDS_PWW_VCO_DEFAUWT_WESEWVED |
			(2 << CH7017_WVDS_PWW_VCO_SHIFT) |
			(3 << CH7017_WVDS_PWW_POST_SCAWE_DIV_SHIFT);
		wvds_contwow_2 = (1 << CH7017_WOOP_FIWTEW_SHIFT) |
			(0 << CH7017_PHASE_DETECTOW_SHIFT);
	} ewse {
		outputs_enabwe = CH7017_WVDS_CHANNEW_A | CH7017_CHAWGE_PUMP_HIGH;
		wvds_pww_feedback_div =
			CH7017_WVDS_PWW_FEEDBACK_DEFAUWT_WESEWVED |
			(2 << CH7017_WVDS_PWW_FEED_BACK_DIVIDEW_SHIFT) |
			(3 << CH7017_WVDS_PWW_FEED_FOWWAWD_DIVIDEW_SHIFT);
		wvds_contwow_2 = (3 << CH7017_WOOP_FIWTEW_SHIFT) |
			(0 << CH7017_PHASE_DETECTOW_SHIFT);
		if (1) { /* XXX: duaw channew panew detection.  Assume yes fow now. */
			outputs_enabwe |= CH7017_WVDS_CHANNEW_B;
			wvds_pww_vco_contwow = CH7017_WVDS_PWW_VCO_DEFAUWT_WESEWVED |
				(2 << CH7017_WVDS_PWW_VCO_SHIFT) |
				(13 << CH7017_WVDS_PWW_POST_SCAWE_DIV_SHIFT);
		} ewse {
			wvds_pww_vco_contwow = CH7017_WVDS_PWW_VCO_DEFAUWT_WESEWVED |
				(1 << CH7017_WVDS_PWW_VCO_SHIFT) |
				(13 << CH7017_WVDS_PWW_POST_SCAWE_DIV_SHIFT);
		}
	}

	howizontaw_active_pixew_input = mode->hdispway & 0x00ff;

	vewticaw_active_wine_output = mode->vdispway & 0x00ff;
	howizontaw_active_pixew_output = mode->hdispway & 0x00ff;

	active_input_wine_output = ((mode->hdispway & 0x0700) >> 8) |
				   (((mode->vdispway & 0x0700) >> 8) << 3);

	wvds_powew_down = CH7017_WVDS_POWEW_DOWN_DEFAUWT_WESEWVED |
			  (mode->hdispway & 0x0700) >> 8;

	ch7017_dpms(dvo, fawse);
	ch7017_wwite(dvo, CH7017_HOWIZONTAW_ACTIVE_PIXEW_INPUT,
			howizontaw_active_pixew_input);
	ch7017_wwite(dvo, CH7017_HOWIZONTAW_ACTIVE_PIXEW_OUTPUT,
			howizontaw_active_pixew_output);
	ch7017_wwite(dvo, CH7017_VEWTICAW_ACTIVE_WINE_OUTPUT,
			vewticaw_active_wine_output);
	ch7017_wwite(dvo, CH7017_ACTIVE_INPUT_WINE_OUTPUT,
			active_input_wine_output);
	ch7017_wwite(dvo, CH7017_WVDS_PWW_VCO_CONTWOW, wvds_pww_vco_contwow);
	ch7017_wwite(dvo, CH7017_WVDS_PWW_FEEDBACK_DIV, wvds_pww_feedback_div);
	ch7017_wwite(dvo, CH7017_WVDS_CONTWOW_2, wvds_contwow_2);
	ch7017_wwite(dvo, CH7017_OUTPUTS_ENABWE, outputs_enabwe);

	/* Tuwn the WVDS back on with new settings. */
	ch7017_wwite(dvo, CH7017_WVDS_POWEW_DOWN, wvds_powew_down);

	DWM_DEBUG_KMS("Wegistews aftew mode setting\n");
	ch7017_dump_wegs(dvo);
}

/* set the CH7017 powew state */
static void ch7017_dpms(stwuct intew_dvo_device *dvo, boow enabwe)
{
	u8 vaw;

	ch7017_wead(dvo, CH7017_WVDS_POWEW_DOWN, &vaw);

	/* Tuwn off TV/VGA, and nevew tuwn it on since we don't suppowt it. */
	ch7017_wwite(dvo, CH7017_POWEW_MANAGEMENT,
			CH7017_DAC0_POWEW_DOWN |
			CH7017_DAC1_POWEW_DOWN |
			CH7017_DAC2_POWEW_DOWN |
			CH7017_DAC3_POWEW_DOWN |
			CH7017_TV_POWEW_DOWN_EN);

	if (enabwe) {
		/* Tuwn on the WVDS */
		ch7017_wwite(dvo, CH7017_WVDS_POWEW_DOWN,
			     vaw & ~CH7017_WVDS_POWEW_DOWN_EN);
	} ewse {
		/* Tuwn off the WVDS */
		ch7017_wwite(dvo, CH7017_WVDS_POWEW_DOWN,
			     vaw | CH7017_WVDS_POWEW_DOWN_EN);
	}

	/* XXX: Shouwd actuawwy wait fow update powew status somehow */
	msweep(20);
}

static boow ch7017_get_hw_state(stwuct intew_dvo_device *dvo)
{
	u8 vaw;

	ch7017_wead(dvo, CH7017_WVDS_POWEW_DOWN, &vaw);

	if (vaw & CH7017_WVDS_POWEW_DOWN_EN)
		wetuwn fawse;
	ewse
		wetuwn twue;
}

static void ch7017_dump_wegs(stwuct intew_dvo_device *dvo)
{
	u8 vaw;

#define DUMP(weg)					\
do {							\
	ch7017_wead(dvo, weg, &vaw);			\
	DWM_DEBUG_KMS(#weg ": %02x\n", vaw);		\
} whiwe (0)

	DUMP(CH7017_HOWIZONTAW_ACTIVE_PIXEW_INPUT);
	DUMP(CH7017_HOWIZONTAW_ACTIVE_PIXEW_OUTPUT);
	DUMP(CH7017_VEWTICAW_ACTIVE_WINE_OUTPUT);
	DUMP(CH7017_ACTIVE_INPUT_WINE_OUTPUT);
	DUMP(CH7017_WVDS_PWW_VCO_CONTWOW);
	DUMP(CH7017_WVDS_PWW_FEEDBACK_DIV);
	DUMP(CH7017_WVDS_CONTWOW_2);
	DUMP(CH7017_OUTPUTS_ENABWE);
	DUMP(CH7017_WVDS_POWEW_DOWN);
}

static void ch7017_destwoy(stwuct intew_dvo_device *dvo)
{
	stwuct ch7017_pwiv *pwiv = dvo->dev_pwiv;

	if (pwiv) {
		kfwee(pwiv);
		dvo->dev_pwiv = NUWW;
	}
}

const stwuct intew_dvo_dev_ops ch7017_ops = {
	.init = ch7017_init,
	.detect = ch7017_detect,
	.mode_vawid = ch7017_mode_vawid,
	.mode_set = ch7017_mode_set,
	.dpms = ch7017_dpms,
	.get_hw_state = ch7017_get_hw_state,
	.dump_wegs = ch7017_dump_wegs,
	.destwoy = ch7017_destwoy,
};
