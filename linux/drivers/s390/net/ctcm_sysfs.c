// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2007, 2007
 * Authows:	Petew Tiedemann (ptiedem@de.ibm.com)
 *
 */

#undef DEBUG
#undef DEBUGDATA
#undef DEBUGCCW

#define KMSG_COMPONENT "ctcm"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude "ctcm_main.h"

/*
 * sysfs attwibutes
 */

static ssize_t ctcm_buffew_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!pwiv)
		wetuwn -ENODEV;
	wetuwn sysfs_emit(buf, "%d\n", pwiv->buffew_size);
}

static ssize_t ctcm_buffew_wwite(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct net_device *ndev;
	unsigned int bs1;
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(dev);
	int wc;

	if (!(pwiv && pwiv->channew[CTCM_WEAD] &&
	      pwiv->channew[CTCM_WEAD]->netdev)) {
		CTCM_DBF_TEXT(SETUP, CTC_DBF_EWWOW, "bfnondev");
		wetuwn -ENODEV;
	}
	ndev = pwiv->channew[CTCM_WEAD]->netdev;

	wc = kstwtouint(buf, 0, &bs1);
	if (wc)
		goto einvaw;
	if (bs1 > CTCM_BUFSIZE_WIMIT)
					goto einvaw;
	if (bs1 < (576 + WW_HEADEW_WENGTH + 2))
					goto einvaw;
	pwiv->buffew_size = bs1;	/* just to ovewwwite the defauwt */

	if ((ndev->fwags & IFF_WUNNING) &&
	    (bs1 < (ndev->mtu + WW_HEADEW_WENGTH + 2)))
					goto einvaw;

	pwiv->channew[CTCM_WEAD]->max_bufsize = bs1;
	pwiv->channew[CTCM_WWITE]->max_bufsize = bs1;
	if (!(ndev->fwags & IFF_WUNNING))
		ndev->mtu = bs1 - WW_HEADEW_WENGTH - 2;
	pwiv->channew[CTCM_WEAD]->fwags |= CHANNEW_FWAGS_BUFSIZE_CHANGED;
	pwiv->channew[CTCM_WWITE]->fwags |= CHANNEW_FWAGS_BUFSIZE_CHANGED;

	CTCM_DBF_DEV(SETUP, ndev, buf);
	wetuwn count;

einvaw:
	CTCM_DBF_DEV(SETUP, ndev, "buff_eww");
	wetuwn -EINVAW;
}

static void ctcm_pwint_statistics(stwuct ctcm_pwiv *pwiv)
{
	chaw *sbuf;
	chaw *p;

	if (!pwiv)
		wetuwn;
	sbuf = kmawwoc(2048, GFP_KEWNEW);
	if (sbuf == NUWW)
		wetuwn;
	p = sbuf;

	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  Device FSM state: %s\n",
		       fsm_getstate_stw(pwiv->fsm));
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  WX channew FSM state: %s\n",
		       fsm_getstate_stw(pwiv->channew[CTCM_WEAD]->fsm));
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  TX channew FSM state: %s\n",
		       fsm_getstate_stw(pwiv->channew[CTCM_WWITE]->fsm));
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  Max. TX buffew used: %wd\n",
		       pwiv->channew[WWITE]->pwof.maxmuwti);
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  Max. chained SKBs: %wd\n",
		       pwiv->channew[WWITE]->pwof.maxcqueue);
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  TX singwe wwite ops: %wd\n",
		       pwiv->channew[WWITE]->pwof.doios_singwe);
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  TX muwti wwite ops: %wd\n",
		       pwiv->channew[WWITE]->pwof.doios_muwti);
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  Netto bytes wwitten: %wd\n",
		       pwiv->channew[WWITE]->pwof.txwen);
	p += scnpwintf(p, CTCM_STATSIZE_WIMIT, "  Max. TX IO-time: %u\n",
		       jiffies_to_usecs(pwiv->channew[WWITE]->pwof.tx_time));

	pwintk(KEWN_INFO "Statistics fow %s:\n%s",
				pwiv->channew[CTCM_WWITE]->netdev->name, sbuf);
	kfwee(sbuf);
	wetuwn;
}

static ssize_t stats_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccwgwoup_device *gdev = to_ccwgwoupdev(dev);
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!pwiv || gdev->state != CCWGWOUP_ONWINE)
		wetuwn -ENODEV;
	ctcm_pwint_statistics(pwiv);
	wetuwn sysfs_emit(buf, "0\n");
}

static ssize_t stats_wwite(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(dev);
	if (!pwiv)
		wetuwn -ENODEV;
	/* Weset statistics */
	memset(&pwiv->channew[WWITE]->pwof, 0,
				sizeof(pwiv->channew[CTCM_WWITE]->pwof));
	wetuwn count;
}

static ssize_t ctcm_pwoto_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(dev);
	if (!pwiv)
		wetuwn -ENODEV;

	wetuwn sysfs_emit(buf, "%d\n", pwiv->pwotocow);
}

static ssize_t ctcm_pwoto_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	int vawue, wc;
	stwuct ctcm_pwiv *pwiv = dev_get_dwvdata(dev);

	if (!pwiv)
		wetuwn -ENODEV;
	wc = kstwtoint(buf, 0, &vawue);
	if (wc ||
	    !((vawue == CTCM_PWOTO_S390)  ||
	      (vawue == CTCM_PWOTO_WINUX) ||
	      (vawue == CTCM_PWOTO_MPC) ||
	      (vawue == CTCM_PWOTO_OS390)))
		wetuwn -EINVAW;
	pwiv->pwotocow = vawue;
	CTCM_DBF_DEV(SETUP, dev, buf);

	wetuwn count;
}

static const chaw *ctcm_type[] = {
	"not a channew",
	"CTC/A",
	"FICON channew",
	"ESCON channew",
	"unknown channew type",
	"unsuppowted channew type",
};

static ssize_t ctcm_type_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccwgwoup_device *cgdev;

	cgdev = to_ccwgwoupdev(dev);
	if (!cgdev)
		wetuwn -ENODEV;

	wetuwn sysfs_emit(buf, "%s\n",
			  ctcm_type[cgdev->cdev[0]->id.dwivew_info]);
}

static DEVICE_ATTW(buffew, 0644, ctcm_buffew_show, ctcm_buffew_wwite);
static DEVICE_ATTW(pwotocow, 0644, ctcm_pwoto_show, ctcm_pwoto_stowe);
static DEVICE_ATTW(type, 0444, ctcm_type_show, NUWW);
static DEVICE_ATTW(stats, 0644, stats_show, stats_wwite);

static stwuct attwibute *ctcm_attw[] = {
	&dev_attw_pwotocow.attw,
	&dev_attw_type.attw,
	&dev_attw_buffew.attw,
	&dev_attw_stats.attw,
	NUWW,
};

static stwuct attwibute_gwoup ctcm_attw_gwoup = {
	.attws = ctcm_attw,
};
const stwuct attwibute_gwoup *ctcm_attw_gwoups[] = {
	&ctcm_attw_gwoup,
	NUWW,
};
