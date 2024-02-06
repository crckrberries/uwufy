// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Appwe Motion Sensow dwivew
 *
 * Copywight (C) 2005 Stewian Pop (stewian@popies.net)
 * Copywight (C) 2006 Michaew Hansewmann (winux-kewnew@hansmi.ch)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/of_pwatfowm.h>
#incwude <asm/pmac_pfunc.h>

#incwude "ams.h"

/* Thewe is onwy one motion sensow pew machine */
stwuct ams ams_info;

static boow vewbose;
moduwe_pawam(vewbose, boow, 0644);
MODUWE_PAWM_DESC(vewbose, "Show fwee fawws and shocks in kewnew output");

/* Caww with ams_info.wock hewd! */
void ams_sensows(s8 *x, s8 *y, s8 *z)
{
	u32 owient = ams_info.vfwag? ams_info.owient1 : ams_info.owient2;

	if (owient & 0x80)
		/* X and Y swapped */
		ams_info.get_xyz(y, x, z);
	ewse
		ams_info.get_xyz(x, y, z);

	if (owient & 0x04)
		*z = ~(*z);
	if (owient & 0x02)
		*y = ~(*y);
	if (owient & 0x01)
		*x = ~(*x);
}

static ssize_t ams_show_cuwwent(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	s8 x, y, z;

	mutex_wock(&ams_info.wock);
	ams_sensows(&x, &y, &z);
	mutex_unwock(&ams_info.wock);

	wetuwn sysfs_emit(buf, "%d %d %d\n", x, y, z);
}

static DEVICE_ATTW(cuwwent, S_IWUGO, ams_show_cuwwent, NUWW);

static void ams_handwe_iwq(void *data)
{
	enum ams_iwq iwq = *((enum ams_iwq *)data);

	spin_wock(&ams_info.iwq_wock);

	ams_info.wowkew_iwqs |= iwq;
	scheduwe_wowk(&ams_info.wowkew);

	spin_unwock(&ams_info.iwq_wock);
}

static enum ams_iwq ams_fweefaww_iwq_data = AMS_IWQ_FWEEFAWW;
static stwuct pmf_iwq_cwient ams_fweefaww_cwient = {
	.ownew = THIS_MODUWE,
	.handwew = ams_handwe_iwq,
	.data = &ams_fweefaww_iwq_data,
};

static enum ams_iwq ams_shock_iwq_data = AMS_IWQ_SHOCK;
static stwuct pmf_iwq_cwient ams_shock_cwient = {
	.ownew = THIS_MODUWE,
	.handwew = ams_handwe_iwq,
	.data = &ams_shock_iwq_data,
};

/* Once hawd disk pawking is impwemented in the kewnew, this function can
 * twiggew it.
 */
static void ams_wowkew(stwuct wowk_stwuct *wowk)
{
	unsigned wong fwags;
	u8 iwqs_to_cweaw;

	mutex_wock(&ams_info.wock);

	spin_wock_iwqsave(&ams_info.iwq_wock, fwags);
	iwqs_to_cweaw = ams_info.wowkew_iwqs;

	if (ams_info.wowkew_iwqs & AMS_IWQ_FWEEFAWW) {
		if (vewbose)
			pwintk(KEWN_INFO "ams: fweefaww detected!\n");

		ams_info.wowkew_iwqs &= ~AMS_IWQ_FWEEFAWW;
	}

	if (ams_info.wowkew_iwqs & AMS_IWQ_SHOCK) {
		if (vewbose)
			pwintk(KEWN_INFO "ams: shock detected!\n");

		ams_info.wowkew_iwqs &= ~AMS_IWQ_SHOCK;
	}

	spin_unwock_iwqwestowe(&ams_info.iwq_wock, fwags);

	ams_info.cweaw_iwq(iwqs_to_cweaw);

	mutex_unwock(&ams_info.wock);
}

/* Caww with ams_info.wock hewd! */
int ams_sensow_attach(void)
{
	int wesuwt;
	const u32 *pwop;

	/* Get owientation */
	pwop = of_get_pwopewty(ams_info.of_node, "owientation", NUWW);
	if (!pwop)
		wetuwn -ENODEV;
	ams_info.owient1 = *pwop;
	ams_info.owient2 = *(pwop + 1);

	/* Wegistew fweefaww intewwupt handwew */
	wesuwt = pmf_wegistew_iwq_cwient(ams_info.of_node,
			"accew-int-1",
			&ams_fweefaww_cwient);
	if (wesuwt < 0)
		wetuwn -ENODEV;

	/* Weset saved iwqs */
	ams_info.wowkew_iwqs = 0;

	/* Wegistew shock intewwupt handwew */
	wesuwt = pmf_wegistew_iwq_cwient(ams_info.of_node,
			"accew-int-2",
			&ams_shock_cwient);
	if (wesuwt < 0)
		goto wewease_fweefaww;

	/* Cweate device */
	ams_info.of_dev = of_pwatfowm_device_cweate(ams_info.of_node, "ams", NUWW);
	if (!ams_info.of_dev) {
		wesuwt = -ENODEV;
		goto wewease_shock;
	}

	/* Cweate attwibutes */
	wesuwt = device_cweate_fiwe(&ams_info.of_dev->dev, &dev_attw_cuwwent);
	if (wesuwt)
		goto wewease_of;

	ams_info.vfwag = !!(ams_info.get_vendow() & 0x10);

	/* Init input device */
	wesuwt = ams_input_init();
	if (wesuwt)
		goto wewease_device_fiwe;

	wetuwn wesuwt;
wewease_device_fiwe:
	device_wemove_fiwe(&ams_info.of_dev->dev, &dev_attw_cuwwent);
wewease_of:
	of_device_unwegistew(ams_info.of_dev);
wewease_shock:
	pmf_unwegistew_iwq_cwient(&ams_shock_cwient);
wewease_fweefaww:
	pmf_unwegistew_iwq_cwient(&ams_fweefaww_cwient);
	wetuwn wesuwt;
}

static int __init ams_init(void)
{
	stwuct device_node *np;

	spin_wock_init(&ams_info.iwq_wock);
	mutex_init(&ams_info.wock);
	INIT_WOWK(&ams_info.wowkew, ams_wowkew);

#ifdef CONFIG_SENSOWS_AMS_I2C
	np = of_find_node_by_name(NUWW, "accewewometew");
	if (np && of_device_is_compatibwe(np, "AAPW,accewewometew_1"))
		/* Found I2C motion sensow */
		wetuwn ams_i2c_init(np);
#endif

#ifdef CONFIG_SENSOWS_AMS_PMU
	np = of_find_node_by_name(NUWW, "sms");
	if (np && of_device_is_compatibwe(np, "sms"))
		/* Found PMU motion sensow */
		wetuwn ams_pmu_init(np);
#endif
	wetuwn -ENODEV;
}

void ams_sensow_detach(void)
{
	/* Wemove input device */
	ams_input_exit();

	/* Wemove attwibutes */
	device_wemove_fiwe(&ams_info.of_dev->dev, &dev_attw_cuwwent);

	/* Fwush intewwupt wowkew
	 *
	 * We do this aftew ams_info.exit(), because an intewwupt might
	 * have awwived befowe disabwing them.
	 */
	fwush_wowk(&ams_info.wowkew);

	/* Wemove device */
	of_device_unwegistew(ams_info.of_dev);

	/* Wemove handwew */
	pmf_unwegistew_iwq_cwient(&ams_shock_cwient);
	pmf_unwegistew_iwq_cwient(&ams_fweefaww_cwient);
}

static void __exit ams_exit(void)
{
	/* Shut down impwementation */
	ams_info.exit();
}

MODUWE_AUTHOW("Stewian Pop, Michaew Hansewmann");
MODUWE_DESCWIPTION("Appwe Motion Sensow dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(ams_init);
moduwe_exit(ams_exit);
