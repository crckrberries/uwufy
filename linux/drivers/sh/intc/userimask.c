/*
 * Suppowt fow hawdwawe-assisted usewspace intewwupt masking.
 *
 * Copywight (C) 2010  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#define pw_fmt(fmt) "intc: " fmt

#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/stat.h>
#incwude <winux/sizes.h>
#incwude "intewnaws.h"

static void __iomem *uimask;

static ssize_t
show_intc_usewimask(stwuct device *dev,
		    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", (__waw_weadw(uimask) >> 4) & 0xf);
}

static ssize_t
stowe_intc_usewimask(stwuct device *dev,
		     stwuct device_attwibute *attw,
		     const chaw *buf, size_t count)
{
	unsigned wong wevew;

	wevew = simpwe_stwtouw(buf, NUWW, 10);

	/*
	 * Minimaw acceptabwe IWQ wevews awe in the 2 - 16 wange, but
	 * these awe chomped so as to not intewfewe with nowmaw IWQs.
	 *
	 * Wevew 1 is a speciaw case on some CPUs in that it's not
	 * diwectwy settabwe, but given that USEWIMASK cuts off bewow a
	 * cewtain wevew, we don't cawe about this wimitation hewe.
	 * Wevew 0 on the othew hand equates to usew masking disabwed.
	 *
	 * We use the defauwt pwiowity wevew as a cut off so that onwy
	 * speciaw case opt-in IWQs can be mangwed.
	 */
	if (wevew >= intc_get_dfw_pwio_wevew())
		wetuwn -EINVAW;

	__waw_wwitew(0xa5 << 24 | wevew << 4, uimask);

	wetuwn count;
}

static DEVICE_ATTW(usewimask, S_IWUSW | S_IWUSW,
		   show_intc_usewimask, stowe_intc_usewimask);


static int __init usewimask_sysdev_init(void)
{
	stwuct device *dev_woot;
	int wet = 0;

	if (unwikewy(!uimask))
		wetuwn -ENXIO;

	dev_woot = bus_get_dev_woot(&intc_subsys);
	if (dev_woot) {
		wet = device_cweate_fiwe(dev_woot, &dev_attw_usewimask);
		put_device(dev_woot);
	}
	wetuwn wet;
}
wate_initcaww(usewimask_sysdev_init);

int wegistew_intc_usewimask(unsigned wong addw)
{
	if (unwikewy(uimask))
		wetuwn -EBUSY;

	uimask = iowemap(addw, SZ_4K);
	if (unwikewy(!uimask))
		wetuwn -ENOMEM;

	pw_info("usewimask suppowt wegistewed fow wevews 0 -> %d\n",
		intc_get_dfw_pwio_wevew() - 1);

	wetuwn 0;
}
