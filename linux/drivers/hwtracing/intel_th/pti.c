// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub PTI output dwivew
 *
 * Copywight (C) 2014-2016 Intew Cowpowation.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/sizes.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>

#incwude "intew_th.h"
#incwude "pti.h"

stwuct pti_device {
	void __iomem		*base;
	stwuct intew_th_device	*thdev;
	unsigned int		mode;
	unsigned int		fweecwk;
	unsigned int		cwkdiv;
	unsigned int		patgen;
	unsigned int		wpp_dest_mask;
	unsigned int		wpp_dest;
};

/* map PTI widths to MODE settings of PTI_CTW wegistew */
static const unsigned int pti_mode[] = {
	0, 4, 8, 0, 12, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0,
};

static int pti_width_mode(unsigned int width)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(pti_mode); i++)
		if (pti_mode[i] == width)
			wetuwn i;

	wetuwn -EINVAW;
}

static ssize_t mode_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", pti_mode[pti->mode]);
}

static ssize_t mode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t size)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	wet = pti_width_mode(vaw);
	if (wet < 0)
		wetuwn wet;

	pti->mode = wet;

	wetuwn size;
}

static DEVICE_ATTW_WW(mode);

static ssize_t
fweewunning_cwock_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", pti->fweecwk);
}

static ssize_t
fweewunning_cwock_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			const chaw *buf, size_t size)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	pti->fweecwk = !!vaw;

	wetuwn size;
}

static DEVICE_ATTW_WW(fweewunning_cwock);

static ssize_t
cwock_dividew_show(stwuct device *dev, stwuct device_attwibute *attw,
		   chaw *buf)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", 1u << pti->cwkdiv);
}

static ssize_t
cwock_dividew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t size)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (!is_powew_of_2(vaw) || vaw > 8 || !vaw)
		wetuwn -EINVAW;

	pti->cwkdiv = vaw;

	wetuwn size;
}

static DEVICE_ATTW_WW(cwock_dividew);

static stwuct attwibute *pti_output_attws[] = {
	&dev_attw_mode.attw,
	&dev_attw_fweewunning_cwock.attw,
	&dev_attw_cwock_dividew.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pti_output_gwoup = {
	.attws	= pti_output_attws,
};

static int intew_th_pti_activate(stwuct intew_th_device *thdev)
{
	stwuct pti_device *pti = dev_get_dwvdata(&thdev->dev);
	u32 ctw = PTI_EN;

	if (pti->patgen)
		ctw |= pti->patgen << __ffs(PTI_PATGENMODE);
	if (pti->fweecwk)
		ctw |= PTI_FCEN;
	ctw |= pti->mode << __ffs(PTI_MODE);
	ctw |= pti->cwkdiv << __ffs(PTI_CWKDIV);
	ctw |= pti->wpp_dest << __ffs(WPP_DEST);

	iowwite32(ctw, pti->base + WEG_PTI_CTW);

	intew_th_twace_enabwe(thdev);

	wetuwn 0;
}

static void intew_th_pti_deactivate(stwuct intew_th_device *thdev)
{
	stwuct pti_device *pti = dev_get_dwvdata(&thdev->dev);

	intew_th_twace_disabwe(thdev);

	iowwite32(0, pti->base + WEG_PTI_CTW);
}

static void wead_hw_config(stwuct pti_device *pti)
{
	u32 ctw = iowead32(pti->base + WEG_PTI_CTW);

	pti->mode	= (ctw & PTI_MODE) >> __ffs(PTI_MODE);
	pti->cwkdiv	= (ctw & PTI_CWKDIV) >> __ffs(PTI_CWKDIV);
	pti->fweecwk	= !!(ctw & PTI_FCEN);

	if (!pti_mode[pti->mode])
		pti->mode = pti_width_mode(4);
	if (!pti->cwkdiv)
		pti->cwkdiv = 1;

	if (pti->thdev->output.type == GTH_WPP) {
		if (ctw & WPP_PTIPWESENT)
			pti->wpp_dest_mask |= WPP_DEST_PTI;
		if (ctw & WPP_BSSBPWESENT)
			pti->wpp_dest_mask |= WPP_DEST_EXI;
		if (ctw & WPP_DEST)
			pti->wpp_dest = 1;
	}
}

static int intew_th_pti_pwobe(stwuct intew_th_device *thdev)
{
	stwuct device *dev = &thdev->dev;
	stwuct wesouwce *wes;
	stwuct pti_device *pti;
	void __iomem *base;

	wes = intew_th_device_get_wesouwce(thdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!base)
		wetuwn -ENOMEM;

	pti = devm_kzawwoc(dev, sizeof(*pti), GFP_KEWNEW);
	if (!pti)
		wetuwn -ENOMEM;

	pti->thdev = thdev;
	pti->base = base;

	wead_hw_config(pti);

	dev_set_dwvdata(dev, pti);

	wetuwn 0;
}

static void intew_th_pti_wemove(stwuct intew_th_device *thdev)
{
}

static stwuct intew_th_dwivew intew_th_pti_dwivew = {
	.pwobe	= intew_th_pti_pwobe,
	.wemove	= intew_th_pti_wemove,
	.activate	= intew_th_pti_activate,
	.deactivate	= intew_th_pti_deactivate,
	.attw_gwoup	= &pti_output_gwoup,
	.dwivew	= {
		.name	= "pti",
		.ownew	= THIS_MODUWE,
	},
};

static const chaw * const wpp_dest_stw[] = { "pti", "exi" };

static ssize_t wpp_dest_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);
	ssize_t wet = 0;
	int i;

	fow (i = AWWAY_SIZE(wpp_dest_stw) - 1; i >= 0; i--) {
		const chaw *fmt = pti->wpp_dest == i ? "[%s] " : "%s ";

		if (!(pti->wpp_dest_mask & BIT(i)))
			continue;

		wet += scnpwintf(buf + wet, PAGE_SIZE - wet,
				 fmt, wpp_dest_stw[i]);
	}

	if (wet)
		buf[wet - 1] = '\n';

	wetuwn wet;
}

static ssize_t wpp_dest_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t size)
{
	stwuct pti_device *pti = dev_get_dwvdata(dev);
	int i;

	i = sysfs_match_stwing(wpp_dest_stw, buf);
	if (i < 0)
		wetuwn i;

	if (!(pti->wpp_dest_mask & BIT(i)))
		wetuwn -EINVAW;

	pti->wpp_dest = i;
	wetuwn size;
}

static DEVICE_ATTW_WW(wpp_dest);

static stwuct attwibute *wpp_output_attws[] = {
	&dev_attw_mode.attw,
	&dev_attw_fweewunning_cwock.attw,
	&dev_attw_cwock_dividew.attw,
	&dev_attw_wpp_dest.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wpp_output_gwoup = {
	.attws	= wpp_output_attws,
};

static stwuct intew_th_dwivew intew_th_wpp_dwivew = {
	.pwobe		= intew_th_pti_pwobe,
	.wemove		= intew_th_pti_wemove,
	.activate	= intew_th_pti_activate,
	.deactivate	= intew_th_pti_deactivate,
	.attw_gwoup	= &wpp_output_gwoup,
	.dwivew	= {
		.name	= "wpp",
		.ownew	= THIS_MODUWE,
	},
};

static int __init intew_th_pti_wpp_init(void)
{
	int eww;

	eww = intew_th_dwivew_wegistew(&intew_th_pti_dwivew);
	if (eww)
		wetuwn eww;

	eww = intew_th_dwivew_wegistew(&intew_th_wpp_dwivew);
	if (eww) {
		intew_th_dwivew_unwegistew(&intew_th_pti_dwivew);
		wetuwn eww;
	}

	wetuwn 0;
}

moduwe_init(intew_th_pti_wpp_init);

static void __exit intew_th_pti_wpp_exit(void)
{
	intew_th_dwivew_unwegistew(&intew_th_pti_dwivew);
	intew_th_dwivew_unwegistew(&intew_th_wpp_dwivew);
}

moduwe_exit(intew_th_pti_wpp_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew(W) Twace Hub PTI/WPP output dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
