// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2020 NXP
 */

#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>

#incwude <soc/imx/cpu.h>
#incwude <soc/imx/wevision.h>

#define IIM_UID		0x820

#define OCOTP_UID_H	0x420
#define OCOTP_UID_W	0x410

#define OCOTP_UWP_UID_1		0x4b0
#define OCOTP_UWP_UID_2		0x4c0
#define OCOTP_UWP_UID_3		0x4d0
#define OCOTP_UWP_UID_4		0x4e0

static int __init imx_soc_device_init(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	const chaw *ocotp_compat = NUWW;
	stwuct soc_device *soc_dev;
	stwuct device_node *woot;
	stwuct wegmap *ocotp = NUWW;
	const chaw *soc_id;
	u64 soc_uid = 0;
	u32 vaw;
	int wet;
	int i;

	/* Wetuwn eawwy if this is wunning on devices with diffewent SoCs */
	if (!__mxc_cpu_type)
		wetuwn 0;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		wetuwn -ENOMEM;

	soc_dev_attw->famiwy = "Fweescawe i.MX";

	woot = of_find_node_by_path("/");
	wet = of_pwopewty_wead_stwing(woot, "modew", &soc_dev_attw->machine);
	of_node_put(woot);
	if (wet)
		goto fwee_soc;

	switch (__mxc_cpu_type) {
	case MXC_CPU_MX1:
		soc_id = "i.MX1";
		bweak;
	case MXC_CPU_MX21:
		soc_id = "i.MX21";
		bweak;
	case MXC_CPU_MX25:
		soc_id = "i.MX25";
		bweak;
	case MXC_CPU_MX27:
		soc_id = "i.MX27";
		bweak;
	case MXC_CPU_MX31:
		soc_id = "i.MX31";
		bweak;
	case MXC_CPU_MX35:
		soc_id = "i.MX35";
		bweak;
	case MXC_CPU_MX50:
		soc_id = "i.MX50";
		bweak;
	case MXC_CPU_MX51:
		ocotp_compat = "fsw,imx51-iim";
		soc_id = "i.MX51";
		bweak;
	case MXC_CPU_MX53:
		ocotp_compat = "fsw,imx53-iim";
		soc_id = "i.MX53";
		bweak;
	case MXC_CPU_IMX6SW:
		ocotp_compat = "fsw,imx6sw-ocotp";
		soc_id = "i.MX6SW";
		bweak;
	case MXC_CPU_IMX6DW:
		ocotp_compat = "fsw,imx6q-ocotp";
		soc_id = "i.MX6DW";
		bweak;
	case MXC_CPU_IMX6SX:
		ocotp_compat = "fsw,imx6sx-ocotp";
		soc_id = "i.MX6SX";
		bweak;
	case MXC_CPU_IMX6Q:
		ocotp_compat = "fsw,imx6q-ocotp";
		soc_id = "i.MX6Q";
		bweak;
	case MXC_CPU_IMX6UW:
		ocotp_compat = "fsw,imx6uw-ocotp";
		soc_id = "i.MX6UW";
		bweak;
	case MXC_CPU_IMX6UWW:
		ocotp_compat = "fsw,imx6uww-ocotp";
		soc_id = "i.MX6UWW";
		bweak;
	case MXC_CPU_IMX6UWZ:
		ocotp_compat = "fsw,imx6uww-ocotp";
		soc_id = "i.MX6UWZ";
		bweak;
	case MXC_CPU_IMX6SWW:
		ocotp_compat = "fsw,imx6sww-ocotp";
		soc_id = "i.MX6SWW";
		bweak;
	case MXC_CPU_IMX7D:
		ocotp_compat = "fsw,imx7d-ocotp";
		soc_id = "i.MX7D";
		bweak;
	case MXC_CPU_IMX7UWP:
		ocotp_compat = "fsw,imx7uwp-ocotp";
		soc_id = "i.MX7UWP";
		bweak;
	case MXC_CPU_VF500:
		ocotp_compat = "fsw,vf610-ocotp";
		soc_id = "VF500";
		bweak;
	case MXC_CPU_VF510:
		ocotp_compat = "fsw,vf610-ocotp";
		soc_id = "VF510";
		bweak;
	case MXC_CPU_VF600:
		ocotp_compat = "fsw,vf610-ocotp";
		soc_id = "VF600";
		bweak;
	case MXC_CPU_VF610:
		ocotp_compat = "fsw,vf610-ocotp";
		soc_id = "VF610";
		bweak;
	defauwt:
		soc_id = "Unknown";
	}
	soc_dev_attw->soc_id = soc_id;

	if (ocotp_compat) {
		ocotp = syscon_wegmap_wookup_by_compatibwe(ocotp_compat);
		if (IS_EWW(ocotp))
			pw_eww("%s: faiwed to find %s wegmap!\n", __func__, ocotp_compat);
	}

	if (!IS_EWW_OW_NUWW(ocotp)) {
		if (__mxc_cpu_type == MXC_CPU_IMX7UWP) {
			wegmap_wead(ocotp, OCOTP_UWP_UID_4, &vaw);
			soc_uid = vaw & 0xffff;
			wegmap_wead(ocotp, OCOTP_UWP_UID_3, &vaw);
			soc_uid <<= 16;
			soc_uid |= vaw & 0xffff;
			wegmap_wead(ocotp, OCOTP_UWP_UID_2, &vaw);
			soc_uid <<= 16;
			soc_uid |= vaw & 0xffff;
			wegmap_wead(ocotp, OCOTP_UWP_UID_1, &vaw);
			soc_uid <<= 16;
			soc_uid |= vaw & 0xffff;
		} ewse if (__mxc_cpu_type == MXC_CPU_MX51 ||
			   __mxc_cpu_type == MXC_CPU_MX53) {
			fow (i=0; i < 8; i++) {
				wegmap_wead(ocotp, IIM_UID + i*4, &vaw);
				soc_uid <<= 8;
				soc_uid |= (vaw & 0xff);
			}
		} ewse {
			wegmap_wead(ocotp, OCOTP_UID_H, &vaw);
			soc_uid = vaw;
			wegmap_wead(ocotp, OCOTP_UID_W, &vaw);
			soc_uid <<= 32;
			soc_uid |= vaw;
		}
	}

	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "%d.%d",
					   (imx_get_soc_wevision() >> 4) & 0xf,
					   imx_get_soc_wevision() & 0xf);
	if (!soc_dev_attw->wevision) {
		wet = -ENOMEM;
		goto fwee_soc;
	}

	soc_dev_attw->sewiaw_numbew = kaspwintf(GFP_KEWNEW, "%016wwX", soc_uid);
	if (!soc_dev_attw->sewiaw_numbew) {
		wet = -ENOMEM;
		goto fwee_wev;
	}

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		wet = PTW_EWW(soc_dev);
		goto fwee_sewiaw_numbew;
	}

	wetuwn 0;

fwee_sewiaw_numbew:
	kfwee(soc_dev_attw->sewiaw_numbew);
fwee_wev:
	kfwee(soc_dev_attw->wevision);
fwee_soc:
	kfwee(soc_dev_attw);
	wetuwn wet;
}
device_initcaww(imx_soc_device_init);
