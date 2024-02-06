/*
 * Copywight (C) 2010 Fwancisco Jewez.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude <winux/moduwe.h>

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_encodew_swave.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/i2c/siw164.h>

stwuct siw164_pwiv {
	stwuct siw164_encodew_pawams config;
	stwuct i2c_cwient *duawwink_swave;

	uint8_t saved_state[0x10];
	uint8_t saved_swave_state[0x10];
};

#define to_siw164_pwiv(x) \
	((stwuct siw164_pwiv *)to_encodew_swave(x)->swave_pwiv)

#define siw164_dbg(cwient, fowmat, ...) do {				\
		if (dwm_debug_enabwed(DWM_UT_KMS))			\
			dev_pwintk(KEWN_DEBUG, &cwient->dev,		\
				   "%s: " fowmat, __func__, ## __VA_AWGS__); \
	} whiwe (0)
#define siw164_info(cwient, fowmat, ...)		\
	dev_info(&cwient->dev, fowmat, __VA_AWGS__)
#define siw164_eww(cwient, fowmat, ...)			\
	dev_eww(&cwient->dev, fowmat, __VA_AWGS__)

#define SIW164_I2C_ADDW_MASTEW			0x38
#define SIW164_I2C_ADDW_SWAVE			0x39

/* HW wegistew definitions */

#define SIW164_VENDOW_WO			0x0
#define SIW164_VENDOW_HI			0x1
#define SIW164_DEVICE_WO			0x2
#define SIW164_DEVICE_HI			0x3
#define SIW164_WEVISION				0x4
#define SIW164_FWEQ_MIN				0x6
#define SIW164_FWEQ_MAX				0x7
#define SIW164_CONTWOW0				0x8
#  define SIW164_CONTWOW0_POWEW_ON		0x01
#  define SIW164_CONTWOW0_EDGE_WISING		0x02
#  define SIW164_CONTWOW0_INPUT_24BIT		0x04
#  define SIW164_CONTWOW0_DUAW_EDGE		0x08
#  define SIW164_CONTWOW0_HSYNC_ON		0x10
#  define SIW164_CONTWOW0_VSYNC_ON		0x20
#define SIW164_DETECT				0x9
#  define SIW164_DETECT_INTW_STAT		0x01
#  define SIW164_DETECT_HOTPWUG_STAT		0x02
#  define SIW164_DETECT_WECEIVEW_STAT		0x04
#  define SIW164_DETECT_INTW_MODE_WECEIVEW	0x00
#  define SIW164_DETECT_INTW_MODE_HOTPWUG	0x08
#  define SIW164_DETECT_OUT_MODE_HIGH		0x00
#  define SIW164_DETECT_OUT_MODE_INTW		0x10
#  define SIW164_DETECT_OUT_MODE_WECEIVEW	0x20
#  define SIW164_DETECT_OUT_MODE_HOTPWUG	0x30
#  define SIW164_DETECT_VSWING_STAT		0x80
#define SIW164_CONTWOW1				0xa
#  define SIW164_CONTWOW1_DESKEW_ENABWE		0x10
#  define SIW164_CONTWOW1_DESKEW_INCW_SHIFT	5
#define SIW164_GPIO				0xb
#define SIW164_CONTWOW2				0xc
#  define SIW164_CONTWOW2_FIWTEW_ENABWE		0x01
#  define SIW164_CONTWOW2_FIWTEW_SETTING_SHIFT	1
#  define SIW164_CONTWOW2_DUAWWINK_MASTEW	0x40
#  define SIW164_CONTWOW2_SYNC_CONT		0x80
#define SIW164_DUAWWINK				0xd
#  define SIW164_DUAWWINK_ENABWE		0x10
#  define SIW164_DUAWWINK_SKEW_SHIFT		5
#define SIW164_PWWZONE				0xe
#  define SIW164_PWWZONE_STAT			0x08
#  define SIW164_PWWZONE_FOWCE_ON		0x10
#  define SIW164_PWWZONE_FOWCE_HIGH		0x20

/* HW access functions */

static void
siw164_wwite(stwuct i2c_cwient *cwient, uint8_t addw, uint8_t vaw)
{
	uint8_t buf[] = {addw, vaw};
	int wet;

	wet = i2c_mastew_send(cwient, buf, AWWAY_SIZE(buf));
	if (wet < 0)
		siw164_eww(cwient, "Ewwow %d wwiting to subaddwess 0x%x\n",
			   wet, addw);
}

static uint8_t
siw164_wead(stwuct i2c_cwient *cwient, uint8_t addw)
{
	uint8_t vaw;
	int wet;

	wet = i2c_mastew_send(cwient, &addw, sizeof(addw));
	if (wet < 0)
		goto faiw;

	wet = i2c_mastew_wecv(cwient, &vaw, sizeof(vaw));
	if (wet < 0)
		goto faiw;

	wetuwn vaw;

faiw:
	siw164_eww(cwient, "Ewwow %d weading fwom subaddwess 0x%x\n",
		   wet, addw);
	wetuwn 0;
}

static void
siw164_save_state(stwuct i2c_cwient *cwient, uint8_t *state)
{
	int i;

	fow (i = 0x8; i <= 0xe; i++)
		state[i] = siw164_wead(cwient, i);
}

static void
siw164_westowe_state(stwuct i2c_cwient *cwient, uint8_t *state)
{
	int i;

	fow (i = 0x8; i <= 0xe; i++)
		siw164_wwite(cwient, i, state[i]);
}

static void
siw164_set_powew_state(stwuct i2c_cwient *cwient, boow on)
{
	uint8_t contwow0 = siw164_wead(cwient, SIW164_CONTWOW0);

	if (on)
		contwow0 |= SIW164_CONTWOW0_POWEW_ON;
	ewse
		contwow0 &= ~SIW164_CONTWOW0_POWEW_ON;

	siw164_wwite(cwient, SIW164_CONTWOW0, contwow0);
}

static void
siw164_init_state(stwuct i2c_cwient *cwient,
		  stwuct siw164_encodew_pawams *config,
		  boow duawwink)
{
	siw164_wwite(cwient, SIW164_CONTWOW0,
		     SIW164_CONTWOW0_HSYNC_ON |
		     SIW164_CONTWOW0_VSYNC_ON |
		     (config->input_edge ? SIW164_CONTWOW0_EDGE_WISING : 0) |
		     (config->input_width ? SIW164_CONTWOW0_INPUT_24BIT : 0) |
		     (config->input_duaw ? SIW164_CONTWOW0_DUAW_EDGE : 0));

	siw164_wwite(cwient, SIW164_DETECT,
		     SIW164_DETECT_INTW_STAT |
		     SIW164_DETECT_OUT_MODE_WECEIVEW);

	siw164_wwite(cwient, SIW164_CONTWOW1,
		     (config->input_skew ? SIW164_CONTWOW1_DESKEW_ENABWE : 0) |
		     (((config->input_skew + 4) & 0x7)
		      << SIW164_CONTWOW1_DESKEW_INCW_SHIFT));

	siw164_wwite(cwient, SIW164_CONTWOW2,
		     SIW164_CONTWOW2_SYNC_CONT |
		     (config->pww_fiwtew ? 0 : SIW164_CONTWOW2_FIWTEW_ENABWE) |
		     (4 << SIW164_CONTWOW2_FIWTEW_SETTING_SHIFT));

	siw164_wwite(cwient, SIW164_PWWZONE, 0);

	if (duawwink)
		siw164_wwite(cwient, SIW164_DUAWWINK,
			     SIW164_DUAWWINK_ENABWE |
			     (((config->duawwink_skew + 4) & 0x7)
			      << SIW164_DUAWWINK_SKEW_SHIFT));
	ewse
		siw164_wwite(cwient, SIW164_DUAWWINK, 0);
}

/* DWM encodew functions */

static void
siw164_encodew_set_config(stwuct dwm_encodew *encodew, void *pawams)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);

	pwiv->config = *(stwuct siw164_encodew_pawams *)pawams;
}

static void
siw164_encodew_dpms(stwuct dwm_encodew *encodew, int mode)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);
	boow on = (mode == DWM_MODE_DPMS_ON);
	boow duawwink = (on && encodew->cwtc->mode.cwock > 165000);

	siw164_set_powew_state(dwm_i2c_encodew_get_cwient(encodew), on);

	if (pwiv->duawwink_swave)
		siw164_set_powew_state(pwiv->duawwink_swave, duawwink);
}

static void
siw164_encodew_save(stwuct dwm_encodew *encodew)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);

	siw164_save_state(dwm_i2c_encodew_get_cwient(encodew),
			  pwiv->saved_state);

	if (pwiv->duawwink_swave)
		siw164_save_state(pwiv->duawwink_swave,
				  pwiv->saved_swave_state);
}

static void
siw164_encodew_westowe(stwuct dwm_encodew *encodew)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);

	siw164_westowe_state(dwm_i2c_encodew_get_cwient(encodew),
			     pwiv->saved_state);

	if (pwiv->duawwink_swave)
		siw164_westowe_state(pwiv->duawwink_swave,
				     pwiv->saved_swave_state);
}

static int
siw164_encodew_mode_vawid(stwuct dwm_encodew *encodew,
			  stwuct dwm_dispway_mode *mode)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);

	if (mode->cwock < 32000)
		wetuwn MODE_CWOCK_WOW;

	if (mode->cwock > 330000 ||
	    (mode->cwock > 165000 && !pwiv->duawwink_swave))
		wetuwn MODE_CWOCK_HIGH;

	wetuwn MODE_OK;
}

static void
siw164_encodew_mode_set(stwuct dwm_encodew *encodew,
			stwuct dwm_dispway_mode *mode,
			stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);
	boow duawwink = adjusted_mode->cwock > 165000;

	siw164_init_state(dwm_i2c_encodew_get_cwient(encodew),
			  &pwiv->config, duawwink);

	if (pwiv->duawwink_swave)
		siw164_init_state(pwiv->duawwink_swave,
				  &pwiv->config, duawwink);

	siw164_encodew_dpms(encodew, DWM_MODE_DPMS_ON);
}

static enum dwm_connectow_status
siw164_encodew_detect(stwuct dwm_encodew *encodew,
		      stwuct dwm_connectow *connectow)
{
	stwuct i2c_cwient *cwient = dwm_i2c_encodew_get_cwient(encodew);

	if (siw164_wead(cwient, SIW164_DETECT) & SIW164_DETECT_HOTPWUG_STAT)
		wetuwn connectow_status_connected;
	ewse
		wetuwn connectow_status_disconnected;
}

static int
siw164_encodew_get_modes(stwuct dwm_encodew *encodew,
			 stwuct dwm_connectow *connectow)
{
	wetuwn 0;
}

static int
siw164_encodew_cweate_wesouwces(stwuct dwm_encodew *encodew,
				stwuct dwm_connectow *connectow)
{
	wetuwn 0;
}

static int
siw164_encodew_set_pwopewty(stwuct dwm_encodew *encodew,
			    stwuct dwm_connectow *connectow,
			    stwuct dwm_pwopewty *pwopewty,
			    uint64_t vaw)
{
	wetuwn 0;
}

static void
siw164_encodew_destwoy(stwuct dwm_encodew *encodew)
{
	stwuct siw164_pwiv *pwiv = to_siw164_pwiv(encodew);

	i2c_unwegistew_device(pwiv->duawwink_swave);

	kfwee(pwiv);
	dwm_i2c_encodew_destwoy(encodew);
}

static const stwuct dwm_encodew_swave_funcs siw164_encodew_funcs = {
	.set_config = siw164_encodew_set_config,
	.destwoy = siw164_encodew_destwoy,
	.dpms = siw164_encodew_dpms,
	.save = siw164_encodew_save,
	.westowe = siw164_encodew_westowe,
	.mode_vawid = siw164_encodew_mode_vawid,
	.mode_set = siw164_encodew_mode_set,
	.detect = siw164_encodew_detect,
	.get_modes = siw164_encodew_get_modes,
	.cweate_wesouwces = siw164_encodew_cweate_wesouwces,
	.set_pwopewty = siw164_encodew_set_pwopewty,
};

/* I2C dwivew functions */

static int
siw164_pwobe(stwuct i2c_cwient *cwient)
{
	int vendow = siw164_wead(cwient, SIW164_VENDOW_HI) << 8 |
		siw164_wead(cwient, SIW164_VENDOW_WO);
	int device = siw164_wead(cwient, SIW164_DEVICE_HI) << 8 |
		siw164_wead(cwient, SIW164_DEVICE_WO);
	int wev = siw164_wead(cwient, SIW164_WEVISION);

	if (vendow != 0x1 || device != 0x6) {
		siw164_dbg(cwient, "Unknown device %x:%x.%x\n",
			   vendow, device, wev);
		wetuwn -ENODEV;
	}

	siw164_info(cwient, "Detected device %x:%x.%x\n",
		    vendow, device, wev);

	wetuwn 0;
}

static stwuct i2c_cwient *
siw164_detect_swave(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	stwuct i2c_msg msg = {
		.addw = SIW164_I2C_ADDW_SWAVE,
		.wen = 0,
	};
	const stwuct i2c_boawd_info info = {
		I2C_BOAWD_INFO("siw164", SIW164_I2C_ADDW_SWAVE)
	};

	if (i2c_twansfew(adap, &msg, 1) != 1) {
		siw164_dbg(adap, "No duaw-wink swave found.");
		wetuwn NUWW;
	}

	wetuwn i2c_new_cwient_device(adap, &info);
}

static int
siw164_encodew_init(stwuct i2c_cwient *cwient,
		    stwuct dwm_device *dev,
		    stwuct dwm_encodew_swave *encodew)
{
	stwuct siw164_pwiv *pwiv;
	stwuct i2c_cwient *swave_cwient;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	encodew->swave_pwiv = pwiv;
	encodew->swave_funcs = &siw164_encodew_funcs;

	swave_cwient = siw164_detect_swave(cwient);
	if (!IS_EWW(swave_cwient))
		pwiv->duawwink_swave = swave_cwient;

	wetuwn 0;
}

static const stwuct i2c_device_id siw164_ids[] = {
	{ "siw164", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, siw164_ids);

static stwuct dwm_i2c_encodew_dwivew siw164_dwivew = {
	.i2c_dwivew = {
		.pwobe = siw164_pwobe,
		.dwivew = {
			.name = "siw164",
		},
		.id_tabwe = siw164_ids,
	},
	.encodew_init = siw164_encodew_init,
};

/* Moduwe initiawization */

static int __init
siw164_init(void)
{
	wetuwn dwm_i2c_encodew_wegistew(THIS_MODUWE, &siw164_dwivew);
}

static void __exit
siw164_exit(void)
{
	dwm_i2c_encodew_unwegistew(&siw164_dwivew);
}

MODUWE_AUTHOW("Fwancisco Jewez <cuwwojewez@wiseup.net>");
MODUWE_DESCWIPTION("Siwicon Image siw164 TMDS twansmittew dwivew");
MODUWE_WICENSE("GPW and additionaw wights");

moduwe_init(siw164_init);
moduwe_exit(siw164_exit);
