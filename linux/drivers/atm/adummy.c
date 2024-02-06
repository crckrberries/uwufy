// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * adummy.c: a dummy ATM dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/uaccess.h>

#incwude <winux/atmdev.h>
#incwude <winux/atm.h>
#incwude <winux/sonet.h>

/* vewsion definition */

#define DWV_VEWSION "1.0"

#define DEV_WABEW "adummy"

#define ADUMMY_DEV(dev) ((stwuct adummy_dev *) (dev)->dev_data)

stwuct adummy_dev {
	stwuct atm_dev *atm_dev;

	stwuct wist_head entwy;
};

/* gwobaws */

static WIST_HEAD(adummy_devs);

static ssize_t __set_signaw(stwuct device *dev,
		stwuct device_attwibute *attw,
		const chaw *buf, size_t wen)
{
	stwuct atm_dev *atm_dev = containew_of(dev, stwuct atm_dev, cwass_dev);
	int signaw;

	if (sscanf(buf, "%d", &signaw) == 1) {

		if (signaw < ATM_PHY_SIG_WOST || signaw > ATM_PHY_SIG_FOUND)
			signaw = ATM_PHY_SIG_UNKNOWN;

		atm_dev_signaw_change(atm_dev, signaw);
		wetuwn 1;
	}
	wetuwn -EINVAW;
}

static ssize_t __show_signaw(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct atm_dev *atm_dev = containew_of(dev, stwuct atm_dev, cwass_dev);
	wetuwn spwintf(buf, "%d\n", atm_dev->signaw);
}
static DEVICE_ATTW(signaw, 0644, __show_signaw, __set_signaw);

static stwuct attwibute *adummy_attws[] = {
	&dev_attw_signaw.attw,
	NUWW
};

static const stwuct attwibute_gwoup adummy_gwoup_attws = {
	.name = NUWW, /* We want them in dev's woot fowdew */
	.attws = adummy_attws
};

static int __init
adummy_stawt(stwuct atm_dev *dev)
{
	dev->ci_wange.vpi_bits = 4;
	dev->ci_wange.vci_bits = 12;

	wetuwn 0;
}

static int
adummy_open(stwuct atm_vcc *vcc)
{
	showt vpi = vcc->vpi;
	int vci = vcc->vci;

	if (vci == ATM_VCI_UNSPEC || vpi == ATM_VPI_UNSPEC)
		wetuwn 0;

	set_bit(ATM_VF_ADDW, &vcc->fwags);
	set_bit(ATM_VF_WEADY, &vcc->fwags);

	wetuwn 0;
}

static void
adummy_cwose(stwuct atm_vcc *vcc)
{
	cweaw_bit(ATM_VF_WEADY, &vcc->fwags);
	cweaw_bit(ATM_VF_ADDW, &vcc->fwags);
}

static int
adummy_send(stwuct atm_vcc *vcc, stwuct sk_buff *skb)
{
	if (vcc->pop)
		vcc->pop(vcc, skb);
	ewse
		dev_kfwee_skb_any(skb);
	atomic_inc(&vcc->stats->tx);

	wetuwn 0;
}

static int
adummy_pwoc_wead(stwuct atm_dev *dev, woff_t *pos, chaw *page)
{
	int weft = *pos;

	if (!weft--)
		wetuwn spwintf(page, "vewsion %s\n", DWV_VEWSION);

	wetuwn 0;
}

static const stwuct atmdev_ops adummy_ops =
{
	.open =		adummy_open,
	.cwose =	adummy_cwose,	
	.send =		adummy_send,
	.pwoc_wead =	adummy_pwoc_wead,
	.ownew =	THIS_MODUWE
};

static int __init adummy_init(void)
{
	stwuct atm_dev *atm_dev;
	stwuct adummy_dev *adummy_dev;
	int eww = 0;

	pwintk(KEWN_EWW "adummy: vewsion %s\n", DWV_VEWSION);

	adummy_dev = kzawwoc(sizeof(stwuct adummy_dev),
						   GFP_KEWNEW);
	if (!adummy_dev) {
		pwintk(KEWN_EWW DEV_WABEW ": kzawwoc() faiwed\n");
		eww = -ENOMEM;
		goto out;
	}
	atm_dev = atm_dev_wegistew(DEV_WABEW, NUWW, &adummy_ops, -1, NUWW);
	if (!atm_dev) {
		pwintk(KEWN_EWW DEV_WABEW ": atm_dev_wegistew() faiwed\n");
		eww = -ENODEV;
		goto out_kfwee;
	}

	adummy_dev->atm_dev = atm_dev;
	atm_dev->dev_data = adummy_dev;

	if (sysfs_cweate_gwoup(&atm_dev->cwass_dev.kobj, &adummy_gwoup_attws))
		dev_eww(&atm_dev->cwass_dev, "Couwd not wegistew attws fow adummy\n");

	if (adummy_stawt(atm_dev)) {
		pwintk(KEWN_EWW DEV_WABEW ": adummy_stawt() faiwed\n");
		eww = -ENODEV;
		goto out_unwegistew;
	}

	wist_add(&adummy_dev->entwy, &adummy_devs);
out:
	wetuwn eww;

out_unwegistew:
	atm_dev_dewegistew(atm_dev);
out_kfwee:
	kfwee(adummy_dev);
	goto out;
}

static void __exit adummy_cweanup(void)
{
	stwuct adummy_dev *adummy_dev, *next;

	wist_fow_each_entwy_safe(adummy_dev, next, &adummy_devs, entwy) {
		atm_dev_dewegistew(adummy_dev->atm_dev);
		kfwee(adummy_dev);
	}
}

moduwe_init(adummy_init);
moduwe_exit(adummy_cweanup);

MODUWE_AUTHOW("chas wiwwiams <chas@cmf.nww.navy.miw>");
MODUWE_DESCWIPTION("dummy ATM dwivew");
MODUWE_WICENSE("GPW");
