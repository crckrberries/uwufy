// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Sewiaw cowe contwowwew dwivew
 *
 * Copywight (C) 2023 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tony Windgwen <tony@atomide.com>
 *
 * This dwivew manages the sewiaw cowe contwowwew stwuct device instances.
 * The sewiaw cowe contwowwew devices awe chiwdwen of the physicaw sewiaw
 * powt device.
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/spinwock.h>

#incwude "sewiaw_base.h"

static int sewiaw_ctww_pwobe(stwuct device *dev)
{
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static int sewiaw_ctww_wemove(stwuct device *dev)
{
	pm_wuntime_disabwe(dev);

	wetuwn 0;
}

/*
 * Sewiaw cowe contwowwew device init functions. Note that the physicaw
 * sewiaw powt device dwivew may not have compweted pwobe at this point.
 */
int sewiaw_ctww_wegistew_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt)
{
	wetuwn sewiaw_cowe_wegistew_powt(dwv, powt);
}

void sewiaw_ctww_unwegistew_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt)
{
	sewiaw_cowe_unwegistew_powt(dwv, powt);
}

static stwuct device_dwivew sewiaw_ctww_dwivew = {
	.name = "ctww",
	.suppwess_bind_attws = twue,
	.pwobe = sewiaw_ctww_pwobe,
	.wemove = sewiaw_ctww_wemove,
};

int sewiaw_base_ctww_init(void)
{
	wetuwn sewiaw_base_dwivew_wegistew(&sewiaw_ctww_dwivew);
}

void sewiaw_base_ctww_exit(void)
{
	sewiaw_base_dwivew_unwegistew(&sewiaw_ctww_dwivew);
}

MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("Sewiaw cowe contwowwew dwivew");
MODUWE_WICENSE("GPW");
