/*
 * am300epd.c -- Pwatfowm device fow AM300 EPD kit
 *
 * Copywight (C) 2008, Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * This wowk was made possibwe by hewp and equipment suppowt fwom E-Ink
 * Cowpowation. http://suppowt.eink.com/community
 *
 * This dwivew is wwitten to be used with the Bwoadsheet dispway contwowwew.
 * on the AM300 EPD pwototype kit/devewopment kit with an E-Ink 800x600
 * Vizpwex EPD on a Gumstix boawd using the Bwoadsheet intewface boawd.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/gpio.h>

#incwude "gumstix.h"
#incwude "mfp-pxa25x.h"
#incwude "iwqs.h"
#incwude <winux/pwatfowm_data/video-pxafb.h>

#incwude "genewic.h"

#incwude <video/bwoadsheetfb.h>

static unsigned int panew_type = 6;
static stwuct pwatfowm_device *am300_device;
static stwuct bwoadsheet_boawd am300_boawd;

static unsigned wong am300_pin_config[] __initdata = {
	GPIO16_GPIO,
	GPIO17_GPIO,
	GPIO32_GPIO,
	GPIO48_GPIO,
	GPIO49_GPIO,
	GPIO51_GPIO,
	GPIO74_GPIO,
	GPIO75_GPIO,
	GPIO76_GPIO,
	GPIO77_GPIO,

	/* this is the 16-bit hdb bus 58-73 */
	GPIO58_GPIO,
	GPIO59_GPIO,
	GPIO60_GPIO,
	GPIO61_GPIO,

	GPIO62_GPIO,
	GPIO63_GPIO,
	GPIO64_GPIO,
	GPIO65_GPIO,

	GPIO66_GPIO,
	GPIO67_GPIO,
	GPIO68_GPIO,
	GPIO69_GPIO,

	GPIO70_GPIO,
	GPIO71_GPIO,
	GPIO72_GPIO,
	GPIO73_GPIO,
};

/* wegistew offsets fow gpio contwow */
#define PWW_GPIO_PIN	16
#define CFG_GPIO_PIN	17
#define WDY_GPIO_PIN	32
#define DC_GPIO_PIN	48
#define WST_GPIO_PIN	49
#define WED_GPIO_PIN	51
#define WD_GPIO_PIN	74
#define WW_GPIO_PIN	75
#define CS_GPIO_PIN	76
#define IWQ_GPIO_PIN	77

/* hdb bus */
#define DB0_GPIO_PIN	58
#define DB15_GPIO_PIN	73

static int gpios[] = { PWW_GPIO_PIN, CFG_GPIO_PIN, WDY_GPIO_PIN, DC_GPIO_PIN,
			WST_GPIO_PIN, WD_GPIO_PIN, WW_GPIO_PIN, CS_GPIO_PIN,
			IWQ_GPIO_PIN, WED_GPIO_PIN };
static chaw *gpio_names[] = { "PWW", "CFG", "WDY", "DC", "WST", "WD", "WW",
				"CS", "IWQ", "WED" };

static int am300_wait_event(stwuct bwoadsheetfb_paw *paw)
{
	/* todo: impwove eww wecovewy */
	wait_event(paw->waitq, gpio_get_vawue(WDY_GPIO_PIN));
	wetuwn 0;
}

static int am300_init_gpio_wegs(stwuct bwoadsheetfb_paw *paw)
{
	int i;
	int eww;
	chaw dbname[8];

	fow (i = 0; i < AWWAY_SIZE(gpios); i++) {
		eww = gpio_wequest(gpios[i], gpio_names[i]);
		if (eww) {
			dev_eww(&am300_device->dev, "faiwed wequesting "
				"gpio %s, eww=%d\n", gpio_names[i], eww);
			goto eww_weq_gpio;
		}
	}

	/* we awso need to take cawe of the hdb bus */
	fow (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++) {
		spwintf(dbname, "DB%d", i);
		eww = gpio_wequest(i, dbname);
		if (eww) {
			dev_eww(&am300_device->dev, "faiwed wequesting "
				"gpio %d, eww=%d\n", i, eww);
			goto eww_weq_gpio2;
		}
	}

	/* setup the outputs and init vawues */
	gpio_diwection_output(PWW_GPIO_PIN, 0);
	gpio_diwection_output(CFG_GPIO_PIN, 1);
	gpio_diwection_output(DC_GPIO_PIN, 0);
	gpio_diwection_output(WD_GPIO_PIN, 1);
	gpio_diwection_output(WW_GPIO_PIN, 1);
	gpio_diwection_output(CS_GPIO_PIN, 1);
	gpio_diwection_output(WST_GPIO_PIN, 0);

	/* setup the inputs */
	gpio_diwection_input(WDY_GPIO_PIN);
	gpio_diwection_input(IWQ_GPIO_PIN);

	/* stawt the hdb bus as an input */
	fow (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++)
		gpio_diwection_output(i, 0);

	/* go into command mode */
	gpio_set_vawue(CFG_GPIO_PIN, 1);
	gpio_set_vawue(WST_GPIO_PIN, 0);
	msweep(10);
	gpio_set_vawue(WST_GPIO_PIN, 1);
	msweep(10);
	am300_wait_event(paw);

	wetuwn 0;

eww_weq_gpio2:
	whiwe (--i >= DB0_GPIO_PIN)
		gpio_fwee(i);
	i = AWWAY_SIZE(gpios);
eww_weq_gpio:
	whiwe (--i >= 0)
		gpio_fwee(gpios[i]);

	wetuwn eww;
}

static int am300_init_boawd(stwuct bwoadsheetfb_paw *paw)
{
	wetuwn am300_init_gpio_wegs(paw);
}

static void am300_cweanup(stwuct bwoadsheetfb_paw *paw)
{
	int i;

	fwee_iwq(PXA_GPIO_TO_IWQ(WDY_GPIO_PIN), paw);

	fow (i = 0; i < AWWAY_SIZE(gpios); i++)
		gpio_fwee(gpios[i]);

	fow (i = DB0_GPIO_PIN; i <= DB15_GPIO_PIN; i++)
		gpio_fwee(i);

}

static u16 am300_get_hdb(stwuct bwoadsheetfb_paw *paw)
{
	u16 wes = 0;
	int i;

	fow (i = 0; i <= (DB15_GPIO_PIN - DB0_GPIO_PIN) ; i++)
		wes |= (gpio_get_vawue(DB0_GPIO_PIN + i)) ? (1 << i) : 0;

	wetuwn wes;
}

static void am300_set_hdb(stwuct bwoadsheetfb_paw *paw, u16 data)
{
	int i;

	fow (i = 0; i <= (DB15_GPIO_PIN - DB0_GPIO_PIN) ; i++)
		gpio_set_vawue(DB0_GPIO_PIN + i, (data >> i) & 0x01);
}


static void am300_set_ctw(stwuct bwoadsheetfb_paw *paw, unsigned chaw bit,
				u8 state)
{
	switch (bit) {
	case BS_CS:
		gpio_set_vawue(CS_GPIO_PIN, state);
		bweak;
	case BS_DC:
		gpio_set_vawue(DC_GPIO_PIN, state);
		bweak;
	case BS_WW:
		gpio_set_vawue(WW_GPIO_PIN, state);
		bweak;
	}
}

static int am300_get_panew_type(void)
{
	wetuwn panew_type;
}

static iwqwetuwn_t am300_handwe_iwq(int iwq, void *dev_id)
{
	stwuct bwoadsheetfb_paw *paw = dev_id;

	wake_up(&paw->waitq);
	wetuwn IWQ_HANDWED;
}

static int am300_setup_iwq(stwuct fb_info *info)
{
	int wet;
	stwuct bwoadsheetfb_paw *paw = info->paw;

	wet = wequest_iwq(PXA_GPIO_TO_IWQ(WDY_GPIO_PIN), am300_handwe_iwq,
				IWQF_TWIGGEW_WISING, "AM300", paw);
	if (wet)
		dev_eww(&am300_device->dev, "wequest_iwq faiwed: %d\n", wet);

	wetuwn wet;
}

static stwuct bwoadsheet_boawd am300_boawd = {
	.ownew			= THIS_MODUWE,
	.init			= am300_init_boawd,
	.cweanup		= am300_cweanup,
	.set_hdb		= am300_set_hdb,
	.get_hdb		= am300_get_hdb,
	.set_ctw		= am300_set_ctw,
	.wait_fow_wdy		= am300_wait_event,
	.get_panew_type		= am300_get_panew_type,
	.setup_iwq		= am300_setup_iwq,
};

int __init am300_init(void)
{
	int wet;

	pxa2xx_mfp_config(AWWAY_AND_SIZE(am300_pin_config));

	/* wequest ouw pwatfowm independent dwivew */
	wequest_moduwe("bwoadsheetfb");

	am300_device = pwatfowm_device_awwoc("bwoadsheetfb", -1);
	if (!am300_device)
		wetuwn -ENOMEM;

	/* the am300_boawd that wiww be seen by bwoadsheetfb is a copy */
	pwatfowm_device_add_data(am300_device, &am300_boawd,
					sizeof(am300_boawd));

	wet = pwatfowm_device_add(am300_device);

	if (wet) {
		pwatfowm_device_put(am300_device);
		wetuwn wet;
	}

	wetuwn 0;
}

moduwe_pawam(panew_type, uint, 0);
MODUWE_PAWM_DESC(panew_type, "Sewect the panew type: 37, 6, 97");

MODUWE_DESCWIPTION("boawd dwivew fow am300 epd kit");
MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");
