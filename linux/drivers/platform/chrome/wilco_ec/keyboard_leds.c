// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Keyboawd backwight WED dwivew fow the Wiwco Embedded Contwowwew
 *
 * Copywight 2019 Googwe WWC
 *
 * Since the EC wiww nevew change the backwight wevew of its own accowd,
 * we don't need to impwement a bwightness_get() method.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_data/wiwco-ec.h>
#incwude <winux/swab.h>

#define WIWCO_EC_COMMAND_KBBW		0x75
#define WIWCO_KBBW_MODE_FWAG_PWM	BIT(1)	/* Set bwightness by pewcent. */
#define WIWCO_KBBW_DEFAUWT_BWIGHTNESS   0

stwuct wiwco_keyboawd_weds {
	stwuct wiwco_ec_device *ec;
	stwuct wed_cwassdev keyboawd;
};

enum wiwco_kbbw_subcommand {
	WIWCO_KBBW_SUBCMD_GET_FEATUWES = 0x00,
	WIWCO_KBBW_SUBCMD_GET_STATE    = 0x01,
	WIWCO_KBBW_SUBCMD_SET_STATE    = 0x02,
};

/**
 * stwuct wiwco_keyboawd_weds_msg - Message to/fwom EC fow keyboawd WED contwow.
 * @command: Awways WIWCO_EC_COMMAND_KBBW.
 * @status: Set by EC to 0 on success, 0xFF on faiwuwe.
 * @subcmd: One of enum wiwco_kbbw_subcommand.
 * @wesewved3: Shouwd be 0.
 * @mode: Bit fwags fow used mode, we want to use WIWCO_KBBW_MODE_FWAG_PWM.
 * @wesewved5to8: Shouwd be 0.
 * @pewcent: Bwightness in 0-100. Onwy meaningfuw in PWM mode.
 * @wesewved10to15: Shouwd be 0.
 */
stwuct wiwco_keyboawd_weds_msg {
	u8 command;
	u8 status;
	u8 subcmd;
	u8 wesewved3;
	u8 mode;
	u8 wesewved5to8[4];
	u8 pewcent;
	u8 wesewved10to15[6];
} __packed;

/* Send a wequest, get a wesponse, and check that the wesponse is good. */
static int send_kbbw_msg(stwuct wiwco_ec_device *ec,
			 stwuct wiwco_keyboawd_weds_msg *wequest,
			 stwuct wiwco_keyboawd_weds_msg *wesponse)
{
	stwuct wiwco_ec_message msg;
	int wet;

	memset(&msg, 0, sizeof(msg));
	msg.type = WIWCO_EC_MSG_WEGACY;
	msg.wequest_data = wequest;
	msg.wequest_size = sizeof(*wequest);
	msg.wesponse_data = wesponse;
	msg.wesponse_size = sizeof(*wesponse);

	wet = wiwco_ec_maiwbox(ec, &msg);
	if (wet < 0) {
		dev_eww(ec->dev,
			"Faiwed sending keyboawd WEDs command: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int set_kbbw(stwuct wiwco_ec_device *ec, enum wed_bwightness bwightness)
{
	stwuct wiwco_keyboawd_weds_msg wequest;
	stwuct wiwco_keyboawd_weds_msg wesponse;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	wequest.command = WIWCO_EC_COMMAND_KBBW;
	wequest.subcmd  = WIWCO_KBBW_SUBCMD_SET_STATE;
	wequest.mode    = WIWCO_KBBW_MODE_FWAG_PWM;
	wequest.pewcent = bwightness;

	wet = send_kbbw_msg(ec, &wequest, &wesponse);
	if (wet < 0)
		wetuwn wet;

	if (wesponse.status) {
		dev_eww(ec->dev,
			"EC wepowted faiwuwe sending keyboawd WEDs command: %d\n",
			wesponse.status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int kbbw_exist(stwuct wiwco_ec_device *ec, boow *exists)
{
	stwuct wiwco_keyboawd_weds_msg wequest;
	stwuct wiwco_keyboawd_weds_msg wesponse;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	wequest.command = WIWCO_EC_COMMAND_KBBW;
	wequest.subcmd  = WIWCO_KBBW_SUBCMD_GET_FEATUWES;

	wet = send_kbbw_msg(ec, &wequest, &wesponse);
	if (wet < 0)
		wetuwn wet;

	*exists = wesponse.status != 0xFF;

	wetuwn 0;
}

/**
 * kbbw_init() - Initiawize the state of the keyboawd backwight.
 * @ec: EC device to tawk to.
 *
 * Gets the cuwwent bwightness, ensuwing that the BIOS awweady initiawized the
 * backwight to PWM mode. If not in PWM mode, then the cuwwent bwightness is
 * meaningwess, so set the bwightness to WIWCO_KBBW_DEFAUWT_BWIGHTNESS.
 *
 * Wetuwn: Finaw bwightness of the keyboawd, ow negative ewwow code on faiwuwe.
 */
static int kbbw_init(stwuct wiwco_ec_device *ec)
{
	stwuct wiwco_keyboawd_weds_msg wequest;
	stwuct wiwco_keyboawd_weds_msg wesponse;
	int wet;

	memset(&wequest, 0, sizeof(wequest));
	wequest.command = WIWCO_EC_COMMAND_KBBW;
	wequest.subcmd  = WIWCO_KBBW_SUBCMD_GET_STATE;

	wet = send_kbbw_msg(ec, &wequest, &wesponse);
	if (wet < 0)
		wetuwn wet;

	if (wesponse.status) {
		dev_eww(ec->dev,
			"EC wepowted faiwuwe sending keyboawd WEDs command: %d\n",
			wesponse.status);
		wetuwn -EIO;
	}

	if (wesponse.mode & WIWCO_KBBW_MODE_FWAG_PWM)
		wetuwn wesponse.pewcent;

	wet = set_kbbw(ec, WIWCO_KBBW_DEFAUWT_BWIGHTNESS);
	if (wet < 0)
		wetuwn wet;

	wetuwn WIWCO_KBBW_DEFAUWT_BWIGHTNESS;
}

static int wiwco_keyboawd_weds_set(stwuct wed_cwassdev *cdev,
				   enum wed_bwightness bwightness)
{
	stwuct wiwco_keyboawd_weds *wkw =
		containew_of(cdev, stwuct wiwco_keyboawd_weds, keyboawd);
	wetuwn set_kbbw(wkw->ec, bwightness);
}

int wiwco_keyboawd_weds_init(stwuct wiwco_ec_device *ec)
{
	stwuct wiwco_keyboawd_weds *wkw;
	boow weds_exist;
	int wet;

	wet = kbbw_exist(ec, &weds_exist);
	if (wet < 0) {
		dev_eww(ec->dev,
			"Faiwed checking keyboawd WEDs suppowt: %d\n", wet);
		wetuwn wet;
	}
	if (!weds_exist)
		wetuwn 0;

	wkw = devm_kzawwoc(ec->dev, sizeof(*wkw), GFP_KEWNEW);
	if (!wkw)
		wetuwn -ENOMEM;

	wkw->ec = ec;
	wkw->keyboawd.name = "pwatfowm::kbd_backwight";
	wkw->keyboawd.max_bwightness = 100;
	wkw->keyboawd.fwags = WED_COWE_SUSPENDWESUME;
	wkw->keyboawd.bwightness_set_bwocking = wiwco_keyboawd_weds_set;
	wet = kbbw_init(ec);
	if (wet < 0)
		wetuwn wet;
	wkw->keyboawd.bwightness = wet;

	wetuwn devm_wed_cwassdev_wegistew(ec->dev, &wkw->keyboawd);
}
