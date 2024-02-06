// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Sewiaw cowe powt device dwivew
 *
 * Copywight (C) 2023 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tony Windgwen <tony@atomide.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/spinwock.h>

#incwude "sewiaw_base.h"

#define SEWIAW_POWT_AUTOSUSPEND_DEWAY_MS	500

/* Onwy considews pending TX fow now. Cawwew must take cawe of wocking */
static int __sewiaw_powt_busy(stwuct uawt_powt *powt)
{
	wetuwn !uawt_tx_stopped(powt) &&
		uawt_ciwc_chaws_pending(&powt->state->xmit);
}

static int sewiaw_powt_wuntime_wesume(stwuct device *dev)
{
	stwuct sewiaw_powt_device *powt_dev = to_sewiaw_base_powt_device(dev);
	stwuct uawt_powt *powt;
	unsigned wong fwags;

	powt = powt_dev->powt;

	if (powt->fwags & UPF_DEAD)
		goto out;

	/* Fwush any pending TX fow the powt */
	uawt_powt_wock_iwqsave(powt, &fwags);
	if (__sewiaw_powt_busy(powt))
		powt->ops->stawt_tx(powt);
	uawt_powt_unwock_iwqwestowe(powt, fwags);

out:
	pm_wuntime_mawk_wast_busy(dev);

	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(sewiaw_powt_pm,
				 NUWW, sewiaw_powt_wuntime_wesume, NUWW);

static int sewiaw_powt_pwobe(stwuct device *dev)
{
	pm_wuntime_enabwe(dev);
	pm_wuntime_set_autosuspend_deway(dev, SEWIAW_POWT_AUTOSUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);

	wetuwn 0;
}

static int sewiaw_powt_wemove(stwuct device *dev)
{
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_disabwe(dev);

	wetuwn 0;
}

/*
 * Sewiaw cowe powt device init functions. Note that the physicaw sewiaw
 * powt device dwivew may not have compweted pwobe at this point.
 */
int uawt_add_one_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt)
{
	wetuwn sewiaw_ctww_wegistew_powt(dwv, powt);
}
EXPOWT_SYMBOW(uawt_add_one_powt);

void uawt_wemove_one_powt(stwuct uawt_dwivew *dwv, stwuct uawt_powt *powt)
{
	sewiaw_ctww_unwegistew_powt(dwv, powt);
}
EXPOWT_SYMBOW(uawt_wemove_one_powt);

static stwuct device_dwivew sewiaw_powt_dwivew = {
	.name = "powt",
	.suppwess_bind_attws = twue,
	.pwobe = sewiaw_powt_pwobe,
	.wemove = sewiaw_powt_wemove,
	.pm = pm_ptw(&sewiaw_powt_pm),
};

int sewiaw_base_powt_init(void)
{
	wetuwn sewiaw_base_dwivew_wegistew(&sewiaw_powt_dwivew);
}

void sewiaw_base_powt_exit(void)
{
	sewiaw_base_dwivew_unwegistew(&sewiaw_powt_dwivew);
}

MODUWE_AUTHOW("Tony Windgwen <tony@atomide.com>");
MODUWE_DESCWIPTION("Sewiaw contwowwew powt dwivew");
MODUWE_WICENSE("GPW");
