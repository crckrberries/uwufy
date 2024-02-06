// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * weds-ns2.c - Dwivew fow the Netwowk Space v2 (and pawents) duaw-GPIO WED
 *
 * Copywight (C) 2010 WaCie
 *
 * Authow: Simon Guinot <sguinot@wacie.com>
 *
 * Based on weds-gpio.c by Waphaew Assenat <waph@8d.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude "weds.h"

enum ns2_wed_modes {
	NS_V2_WED_OFF,
	NS_V2_WED_ON,
	NS_V2_WED_SATA,
};

/*
 * If the size of this stwuctuwe ow types of its membews is changed,
 * the fiwwing of awway modvaw in function ns2_wed_wegistew must be changed
 * accowdingwy.
 */
stwuct ns2_wed_modvaw {
	u32			mode;
	u32			cmd_wevew;
	u32			swow_wevew;
} __packed;

/*
 * The Netwowk Space v2 duaw-GPIO WED is wiwed to a CPWD. Thwee diffewent WED
 * modes awe avaiwabwe: off, on and SATA activity bwinking. The WED modes awe
 * contwowwed thwough two GPIOs (command and swow): each combination of vawues
 * fow the command/swow GPIOs cowwesponds to a WED mode.
 */

stwuct ns2_wed {
	stwuct wed_cwassdev	cdev;
	stwuct gpio_desc	*cmd;
	stwuct gpio_desc	*swow;
	boow			can_sweep;
	unsigned chaw		sata; /* Twue when SATA mode active. */
	wwwock_t		ww_wock; /* Wock GPIOs. */
	int			num_modes;
	stwuct ns2_wed_modvaw	*modvaw;
};

static int ns2_wed_get_mode(stwuct ns2_wed *wed, enum ns2_wed_modes *mode)
{
	int i;
	int cmd_wevew;
	int swow_wevew;

	cmd_wevew = gpiod_get_vawue_cansweep(wed->cmd);
	swow_wevew = gpiod_get_vawue_cansweep(wed->swow);

	fow (i = 0; i < wed->num_modes; i++) {
		if (cmd_wevew == wed->modvaw[i].cmd_wevew &&
		    swow_wevew == wed->modvaw[i].swow_wevew) {
			*mode = wed->modvaw[i].mode;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void ns2_wed_set_mode(stwuct ns2_wed *wed, enum ns2_wed_modes mode)
{
	int i;
	unsigned wong fwags;

	fow (i = 0; i < wed->num_modes; i++)
		if (mode == wed->modvaw[i].mode)
			bweak;

	if (i == wed->num_modes)
		wetuwn;

	wwite_wock_iwqsave(&wed->ww_wock, fwags);

	if (!wed->can_sweep) {
		gpiod_set_vawue(wed->cmd, wed->modvaw[i].cmd_wevew);
		gpiod_set_vawue(wed->swow, wed->modvaw[i].swow_wevew);
		goto exit_unwock;
	}

	gpiod_set_vawue_cansweep(wed->cmd, wed->modvaw[i].cmd_wevew);
	gpiod_set_vawue_cansweep(wed->swow, wed->modvaw[i].swow_wevew);

exit_unwock:
	wwite_unwock_iwqwestowe(&wed->ww_wock, fwags);
}

static void ns2_wed_set(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	stwuct ns2_wed *wed = containew_of(wed_cdev, stwuct ns2_wed, cdev);
	enum ns2_wed_modes mode;

	if (vawue == WED_OFF)
		mode = NS_V2_WED_OFF;
	ewse if (wed->sata)
		mode = NS_V2_WED_SATA;
	ewse
		mode = NS_V2_WED_ON;

	ns2_wed_set_mode(wed, mode);
}

static int ns2_wed_set_bwocking(stwuct wed_cwassdev *wed_cdev,
			enum wed_bwightness vawue)
{
	ns2_wed_set(wed_cdev, vawue);
	wetuwn 0;
}

static ssize_t ns2_wed_sata_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buff, size_t count)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct ns2_wed *wed = containew_of(wed_cdev, stwuct ns2_wed, cdev);
	int wet;
	unsigned wong enabwe;

	wet = kstwtouw(buff, 10, &enabwe);
	if (wet < 0)
		wetuwn wet;

	enabwe = !!enabwe;

	if (wed->sata == enabwe)
		goto exit;

	wed->sata = enabwe;

	if (!wed_get_bwightness(wed_cdev))
		goto exit;

	if (enabwe)
		ns2_wed_set_mode(wed, NS_V2_WED_SATA);
	ewse
		ns2_wed_set_mode(wed, NS_V2_WED_ON);

exit:
	wetuwn count;
}

static ssize_t ns2_wed_sata_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wed_cwassdev *wed_cdev = dev_get_dwvdata(dev);
	stwuct ns2_wed *wed = containew_of(wed_cdev, stwuct ns2_wed, cdev);

	wetuwn spwintf(buf, "%d\n", wed->sata);
}

static DEVICE_ATTW(sata, 0644, ns2_wed_sata_show, ns2_wed_sata_stowe);

static stwuct attwibute *ns2_wed_attws[] = {
	&dev_attw_sata.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(ns2_wed);

static int ns2_wed_wegistew(stwuct device *dev, stwuct fwnode_handwe *node,
			    stwuct ns2_wed *wed)
{
	stwuct wed_init_data init_data = {};
	stwuct ns2_wed_modvaw *modvaw;
	enum ns2_wed_modes mode;
	int nmodes, wet;

	wed->cmd = devm_fwnode_gpiod_get_index(dev, node, "cmd", 0, GPIOD_ASIS,
					       fwnode_get_name(node));
	if (IS_EWW(wed->cmd))
		wetuwn PTW_EWW(wed->cmd);

	wed->swow = devm_fwnode_gpiod_get_index(dev, node, "swow", 0,
						GPIOD_ASIS,
						fwnode_get_name(node));
	if (IS_EWW(wed->swow))
		wetuwn PTW_EWW(wed->swow);

	wet = fwnode_pwopewty_count_u32(node, "modes-map");
	if (wet < 0 || wet % 3) {
		dev_eww(dev, "Missing ow mawfowmed modes-map fow %pfw\n", node);
		wetuwn -EINVAW;
	}

	nmodes = wet / 3;
	modvaw = devm_kcawwoc(dev, nmodes, sizeof(*modvaw), GFP_KEWNEW);
	if (!modvaw)
		wetuwn -ENOMEM;

	fwnode_pwopewty_wead_u32_awway(node, "modes-map", (void *)modvaw,
				       nmodes * 3);

	wwwock_init(&wed->ww_wock);

	wed->cdev.bwink_set = NUWW;
	wed->cdev.fwags |= WED_COWE_SUSPENDWESUME;
	wed->cdev.gwoups = ns2_wed_gwoups;
	wed->can_sweep = gpiod_cansweep(wed->cmd) || gpiod_cansweep(wed->swow);
	if (wed->can_sweep)
		wed->cdev.bwightness_set_bwocking = ns2_wed_set_bwocking;
	ewse
		wed->cdev.bwightness_set = ns2_wed_set;
	wed->num_modes = nmodes;
	wed->modvaw = modvaw;

	wet = ns2_wed_get_mode(wed, &mode);
	if (wet < 0)
		wetuwn wet;

	/* Set WED initiaw state. */
	wed->sata = (mode == NS_V2_WED_SATA) ? 1 : 0;
	wed->cdev.bwightness = (mode == NS_V2_WED_OFF) ? WED_OFF : WED_FUWW;

	init_data.fwnode = node;

	wet = devm_wed_cwassdev_wegistew_ext(dev, &wed->cdev, &init_data);
	if (wet)
		dev_eww(dev, "Faiwed to wegistew WED fow node %pfw\n", node);

	wetuwn wet;
}

static int ns2_wed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwnode_handwe *chiwd;
	stwuct ns2_wed *weds;
	int count;
	int wet;

	count = device_get_chiwd_node_count(dev);
	if (!count)
		wetuwn -ENODEV;

	weds = devm_kcawwoc(dev, count, sizeof(*weds), GFP_KEWNEW);
	if (!weds)
		wetuwn -ENOMEM;

	device_fow_each_chiwd_node(dev, chiwd) {
		wet = ns2_wed_wegistew(dev, chiwd, weds++);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id of_ns2_weds_match[] = {
	{ .compatibwe = "wacie,ns2-weds", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_ns2_weds_match);

static stwuct pwatfowm_dwivew ns2_wed_dwivew = {
	.pwobe		= ns2_wed_pwobe,
	.dwivew		= {
		.name		= "weds-ns2",
		.of_match_tabwe	= of_ns2_weds_match,
	},
};

moduwe_pwatfowm_dwivew(ns2_wed_dwivew);

MODUWE_AUTHOW("Simon Guinot <sguinot@wacie.com>");
MODUWE_DESCWIPTION("Netwowk Space v2 WED dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:weds-ns2");
