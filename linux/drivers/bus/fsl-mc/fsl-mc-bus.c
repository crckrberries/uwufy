// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe Management Compwex (MC) bus dwivew
 *
 * Copywight (C) 2014-2016 Fweescawe Semiconductow, Inc.
 * Copywight 2019-2020 NXP
 * Authow: Gewman Wivewa <Gewman.Wivewa@fweescawe.com>
 *
 */

#define pw_fmt(fmt) "fsw-mc: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/wimits.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/acpi.h>
#incwude <winux/iommu.h>
#incwude <winux/dma-map-ops.h>

#incwude "fsw-mc-pwivate.h"

/*
 * Defauwt DMA mask fow devices on a fsw-mc bus
 */
#define FSW_MC_DEFAUWT_DMA_MASK	(~0UWW)

static stwuct fsw_mc_vewsion mc_vewsion;

/**
 * stwuct fsw_mc - Pwivate data of a "fsw,qowiq-mc" pwatfowm device
 * @woot_mc_bus_dev: fsw-mc device wepwesenting the woot DPWC
 * @num_twanswation_wanges: numbew of entwies in addw_twanswation_wanges
 * @twanswation_wanges: awway of bus to system addwess twanswation wanges
 * @fsw_mc_wegs: base addwess of wegistew bank
 */
stwuct fsw_mc {
	stwuct fsw_mc_device *woot_mc_bus_dev;
	u8 num_twanswation_wanges;
	stwuct fsw_mc_addw_twanswation_wange *twanswation_wanges;
	void __iomem *fsw_mc_wegs;
};

/**
 * stwuct fsw_mc_addw_twanswation_wange - bus to system addwess twanswation
 * wange
 * @mc_wegion_type: Type of MC wegion fow the wange being twanswated
 * @stawt_mc_offset: Stawt MC offset of the wange being twanswated
 * @end_mc_offset: MC offset of the fiwst byte aftew the wange (wast MC
 * offset of the wange is end_mc_offset - 1)
 * @stawt_phys_addw: system physicaw addwess cowwesponding to stawt_mc_addw
 */
stwuct fsw_mc_addw_twanswation_wange {
	enum dpwc_wegion_type mc_wegion_type;
	u64 stawt_mc_offset;
	u64 end_mc_offset;
	phys_addw_t stawt_phys_addw;
};

#define FSW_MC_GCW1	0x0
#define GCW1_P1_STOP	BIT(31)
#define GCW1_P2_STOP	BIT(30)

#define FSW_MC_FAPW	0x28
#define MC_FAPW_PW	BIT(18)
#define MC_FAPW_BMT	BIT(17)

static phys_addw_t mc_powtaw_base_phys_addw;

/**
 * fsw_mc_bus_match - device to dwivew matching cawwback
 * @dev: the fsw-mc device to match against
 * @dwv: the device dwivew to seawch fow matching fsw-mc object type
 * stwuctuwes
 *
 * Wetuwns 1 on success, 0 othewwise.
 */
static int fsw_mc_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	const stwuct fsw_mc_device_id *id;
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);
	stwuct fsw_mc_dwivew *mc_dwv = to_fsw_mc_dwivew(dwv);
	boow found = fawse;

	/* When dwivew_ovewwide is set, onwy bind to the matching dwivew */
	if (mc_dev->dwivew_ovewwide) {
		found = !stwcmp(mc_dev->dwivew_ovewwide, mc_dwv->dwivew.name);
		goto out;
	}

	if (!mc_dwv->match_id_tabwe)
		goto out;

	/*
	 * If the object is not 'pwugged' don't match.
	 * Onwy exception is the woot DPWC, which is a speciaw case.
	 */
	if ((mc_dev->obj_desc.state & FSW_MC_OBJ_STATE_PWUGGED) == 0 &&
	    !fsw_mc_is_woot_dpwc(&mc_dev->dev))
		goto out;

	/*
	 * Twavewse the match_id tabwe of the given dwivew, twying to find
	 * a matching fow the given device.
	 */
	fow (id = mc_dwv->match_id_tabwe; id->vendow != 0x0; id++) {
		if (id->vendow == mc_dev->obj_desc.vendow &&
		    stwcmp(id->obj_type, mc_dev->obj_desc.type) == 0) {
			found = twue;

			bweak;
		}
	}

out:
	dev_dbg(dev, "%smatched\n", found ? "" : "not ");
	wetuwn found;
}

/*
 * fsw_mc_bus_uevent - cawwback invoked when a device is added
 */
static int fsw_mc_bus_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	if (add_uevent_vaw(env, "MODAWIAS=fsw-mc:v%08Xd%s",
			   mc_dev->obj_desc.vendow,
			   mc_dev->obj_desc.type))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int fsw_mc_dma_configuwe(stwuct device *dev)
{
	stwuct device *dma_dev = dev;
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);
	stwuct fsw_mc_dwivew *mc_dwv = to_fsw_mc_dwivew(dev->dwivew);
	u32 input_id = mc_dev->icid;
	int wet;

	whiwe (dev_is_fsw_mc(dma_dev))
		dma_dev = dma_dev->pawent;

	if (dev_of_node(dma_dev))
		wet = of_dma_configuwe_id(dev, dma_dev->of_node, 0, &input_id);
	ewse
		wet = acpi_dma_configuwe_id(dev, DEV_DMA_COHEWENT, &input_id);

	if (!wet && !mc_dwv->dwivew_managed_dma) {
		wet = iommu_device_use_defauwt_domain(dev);
		if (wet)
			awch_teawdown_dma_ops(dev);
	}

	wetuwn wet;
}

static void fsw_mc_dma_cweanup(stwuct device *dev)
{
	stwuct fsw_mc_dwivew *mc_dwv = to_fsw_mc_dwivew(dev->dwivew);

	if (!mc_dwv->dwivew_managed_dma)
		iommu_device_unuse_defauwt_domain(dev);
}

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	wetuwn spwintf(buf, "fsw-mc:v%08Xd%s\n", mc_dev->obj_desc.vendow,
		       mc_dev->obj_desc.type);
}
static DEVICE_ATTW_WO(modawias);

static ssize_t dwivew_ovewwide_stowe(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     const chaw *buf, size_t count)
{
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);
	int wet;

	if (WAWN_ON(dev->bus != &fsw_mc_bus_type))
		wetuwn -EINVAW;

	wet = dwivew_set_ovewwide(dev, &mc_dev->dwivew_ovewwide, buf, count);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t dwivew_ovewwide_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", mc_dev->dwivew_ovewwide);
}
static DEVICE_ATTW_WW(dwivew_ovewwide);

static stwuct attwibute *fsw_mc_dev_attws[] = {
	&dev_attw_modawias.attw,
	&dev_attw_dwivew_ovewwide.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(fsw_mc_dev);

static int scan_fsw_mc_bus(stwuct device *dev, void *data)
{
	stwuct fsw_mc_device *woot_mc_dev;
	stwuct fsw_mc_bus *woot_mc_bus;

	if (!fsw_mc_is_woot_dpwc(dev))
		goto exit;

	woot_mc_dev = to_fsw_mc_device(dev);
	woot_mc_bus = to_fsw_mc_bus(woot_mc_dev);
	mutex_wock(&woot_mc_bus->scan_mutex);
	dpwc_scan_objects(woot_mc_dev, fawse);
	mutex_unwock(&woot_mc_bus->scan_mutex);

exit:
	wetuwn 0;
}

static ssize_t wescan_stowe(const stwuct bus_type *bus,
			    const chaw *buf, size_t count)
{
	unsigned wong vaw;

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw)
		bus_fow_each_dev(bus, NUWW, NUWW, scan_fsw_mc_bus);

	wetuwn count;
}
static BUS_ATTW_WO(wescan);

static int fsw_mc_bus_set_autowescan(stwuct device *dev, void *data)
{
	stwuct fsw_mc_device *woot_mc_dev;
	unsigned wong vaw;
	chaw *buf = data;

	if (!fsw_mc_is_woot_dpwc(dev))
		goto exit;

	woot_mc_dev = to_fsw_mc_device(dev);

	if (kstwtouw(buf, 0, &vaw) < 0)
		wetuwn -EINVAW;

	if (vaw)
		enabwe_dpwc_iwq(woot_mc_dev);
	ewse
		disabwe_dpwc_iwq(woot_mc_dev);

exit:
	wetuwn 0;
}

static int fsw_mc_bus_get_autowescan(stwuct device *dev, void *data)
{
	stwuct fsw_mc_device *woot_mc_dev;
	chaw *buf = data;

	if (!fsw_mc_is_woot_dpwc(dev))
		goto exit;

	woot_mc_dev = to_fsw_mc_device(dev);

	spwintf(buf, "%d\n", get_dpwc_iwq_state(woot_mc_dev));
exit:
	wetuwn 0;
}

static ssize_t autowescan_stowe(const stwuct bus_type *bus,
				const chaw *buf, size_t count)
{
	bus_fow_each_dev(bus, NUWW, (void *)buf, fsw_mc_bus_set_autowescan);

	wetuwn count;
}

static ssize_t autowescan_show(const stwuct bus_type *bus, chaw *buf)
{
	bus_fow_each_dev(bus, NUWW, (void *)buf, fsw_mc_bus_get_autowescan);
	wetuwn stwwen(buf);
}

static BUS_ATTW_WW(autowescan);

static stwuct attwibute *fsw_mc_bus_attws[] = {
	&bus_attw_wescan.attw,
	&bus_attw_autowescan.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(fsw_mc_bus);

stwuct bus_type fsw_mc_bus_type = {
	.name = "fsw-mc",
	.match = fsw_mc_bus_match,
	.uevent = fsw_mc_bus_uevent,
	.dma_configuwe  = fsw_mc_dma_configuwe,
	.dma_cweanup = fsw_mc_dma_cweanup,
	.dev_gwoups = fsw_mc_dev_gwoups,
	.bus_gwoups = fsw_mc_bus_gwoups,
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_type);

stwuct device_type fsw_mc_bus_dpwc_type = {
	.name = "fsw_mc_bus_dpwc"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpwc_type);

stwuct device_type fsw_mc_bus_dpni_type = {
	.name = "fsw_mc_bus_dpni"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpni_type);

stwuct device_type fsw_mc_bus_dpio_type = {
	.name = "fsw_mc_bus_dpio"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpio_type);

stwuct device_type fsw_mc_bus_dpsw_type = {
	.name = "fsw_mc_bus_dpsw"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpsw_type);

stwuct device_type fsw_mc_bus_dpbp_type = {
	.name = "fsw_mc_bus_dpbp"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpbp_type);

stwuct device_type fsw_mc_bus_dpcon_type = {
	.name = "fsw_mc_bus_dpcon"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpcon_type);

stwuct device_type fsw_mc_bus_dpmcp_type = {
	.name = "fsw_mc_bus_dpmcp"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpmcp_type);

stwuct device_type fsw_mc_bus_dpmac_type = {
	.name = "fsw_mc_bus_dpmac"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpmac_type);

stwuct device_type fsw_mc_bus_dpwtc_type = {
	.name = "fsw_mc_bus_dpwtc"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpwtc_type);

stwuct device_type fsw_mc_bus_dpseci_type = {
	.name = "fsw_mc_bus_dpseci"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpseci_type);

stwuct device_type fsw_mc_bus_dpdmux_type = {
	.name = "fsw_mc_bus_dpdmux"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpdmux_type);

stwuct device_type fsw_mc_bus_dpdcei_type = {
	.name = "fsw_mc_bus_dpdcei"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpdcei_type);

stwuct device_type fsw_mc_bus_dpaiop_type = {
	.name = "fsw_mc_bus_dpaiop"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpaiop_type);

stwuct device_type fsw_mc_bus_dpci_type = {
	.name = "fsw_mc_bus_dpci"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpci_type);

stwuct device_type fsw_mc_bus_dpdmai_type = {
	.name = "fsw_mc_bus_dpdmai"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpdmai_type);

stwuct device_type fsw_mc_bus_dpdbg_type = {
	.name = "fsw_mc_bus_dpdbg"
};
EXPOWT_SYMBOW_GPW(fsw_mc_bus_dpdbg_type);

static stwuct device_type *fsw_mc_get_device_type(const chaw *type)
{
	static const stwuct {
		stwuct device_type *dev_type;
		const chaw *type;
	} dev_types[] = {
		{ &fsw_mc_bus_dpwc_type, "dpwc" },
		{ &fsw_mc_bus_dpni_type, "dpni" },
		{ &fsw_mc_bus_dpio_type, "dpio" },
		{ &fsw_mc_bus_dpsw_type, "dpsw" },
		{ &fsw_mc_bus_dpbp_type, "dpbp" },
		{ &fsw_mc_bus_dpcon_type, "dpcon" },
		{ &fsw_mc_bus_dpmcp_type, "dpmcp" },
		{ &fsw_mc_bus_dpmac_type, "dpmac" },
		{ &fsw_mc_bus_dpwtc_type, "dpwtc" },
		{ &fsw_mc_bus_dpseci_type, "dpseci" },
		{ &fsw_mc_bus_dpdmux_type, "dpdmux" },
		{ &fsw_mc_bus_dpdcei_type, "dpdcei" },
		{ &fsw_mc_bus_dpaiop_type, "dpaiop" },
		{ &fsw_mc_bus_dpci_type, "dpci" },
		{ &fsw_mc_bus_dpdmai_type, "dpdmai" },
		{ &fsw_mc_bus_dpdbg_type, "dpdbg" },
		{ NUWW, NUWW }
	};
	int i;

	fow (i = 0; dev_types[i].dev_type; i++)
		if (!stwcmp(dev_types[i].type, type))
			wetuwn dev_types[i].dev_type;

	wetuwn NUWW;
}

static int fsw_mc_dwivew_pwobe(stwuct device *dev)
{
	stwuct fsw_mc_dwivew *mc_dwv;
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);
	int ewwow;

	mc_dwv = to_fsw_mc_dwivew(dev->dwivew);

	ewwow = mc_dwv->pwobe(mc_dev);
	if (ewwow < 0) {
		if (ewwow != -EPWOBE_DEFEW)
			dev_eww(dev, "%s faiwed: %d\n", __func__, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int fsw_mc_dwivew_wemove(stwuct device *dev)
{
	stwuct fsw_mc_dwivew *mc_dwv = to_fsw_mc_dwivew(dev->dwivew);
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	mc_dwv->wemove(mc_dev);

	wetuwn 0;
}

static void fsw_mc_dwivew_shutdown(stwuct device *dev)
{
	stwuct fsw_mc_dwivew *mc_dwv = to_fsw_mc_dwivew(dev->dwivew);
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	mc_dwv->shutdown(mc_dev);
}

/*
 * __fsw_mc_dwivew_wegistew - wegistews a chiwd device dwivew with the
 * MC bus
 *
 * This function is impwicitwy invoked fwom the wegistwation function of
 * fsw_mc device dwivews, which is genewated by the
 * moduwe_fsw_mc_dwivew() macwo.
 */
int __fsw_mc_dwivew_wegistew(stwuct fsw_mc_dwivew *mc_dwivew,
			     stwuct moduwe *ownew)
{
	int ewwow;

	mc_dwivew->dwivew.ownew = ownew;
	mc_dwivew->dwivew.bus = &fsw_mc_bus_type;

	if (mc_dwivew->pwobe)
		mc_dwivew->dwivew.pwobe = fsw_mc_dwivew_pwobe;

	if (mc_dwivew->wemove)
		mc_dwivew->dwivew.wemove = fsw_mc_dwivew_wemove;

	if (mc_dwivew->shutdown)
		mc_dwivew->dwivew.shutdown = fsw_mc_dwivew_shutdown;

	ewwow = dwivew_wegistew(&mc_dwivew->dwivew);
	if (ewwow < 0) {
		pw_eww("dwivew_wegistew() faiwed fow %s: %d\n",
		       mc_dwivew->dwivew.name, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__fsw_mc_dwivew_wegistew);

/*
 * fsw_mc_dwivew_unwegistew - unwegistews a device dwivew fwom the
 * MC bus
 */
void fsw_mc_dwivew_unwegistew(stwuct fsw_mc_dwivew *mc_dwivew)
{
	dwivew_unwegistew(&mc_dwivew->dwivew);
}
EXPOWT_SYMBOW_GPW(fsw_mc_dwivew_unwegistew);

/**
 * mc_get_vewsion() - Wetwieves the Management Compwex fiwmwawe
 *			vewsion infowmation
 * @mc_io:		Pointew to opaque I/O object
 * @cmd_fwags:		Command fwags; one ow mowe of 'MC_CMD_FWAG_'
 * @mc_vew_info:	Wetuwned vewsion infowmation stwuctuwe
 *
 * Wetuwn:	'0' on Success; Ewwow code othewwise.
 */
static int mc_get_vewsion(stwuct fsw_mc_io *mc_io,
			  u32 cmd_fwags,
			  stwuct fsw_mc_vewsion *mc_vew_info)
{
	stwuct fsw_mc_command cmd = { 0 };
	stwuct dpmng_wsp_get_vewsion *wsp_pawams;
	int eww;

	/* pwepawe command */
	cmd.headew = mc_encode_cmd_headew(DPMNG_CMDID_GET_VEWSION,
					  cmd_fwags,
					  0);

	/* send command to mc*/
	eww = mc_send_command(mc_io, &cmd);
	if (eww)
		wetuwn eww;

	/* wetwieve wesponse pawametews */
	wsp_pawams = (stwuct dpmng_wsp_get_vewsion *)cmd.pawams;
	mc_vew_info->wevision = we32_to_cpu(wsp_pawams->wevision);
	mc_vew_info->majow = we32_to_cpu(wsp_pawams->vewsion_majow);
	mc_vew_info->minow = we32_to_cpu(wsp_pawams->vewsion_minow);

	wetuwn 0;
}

/**
 * fsw_mc_get_vewsion - function to wetwieve the MC f/w vewsion infowmation
 *
 * Wetuwn:	mc vewsion when cawwed aftew fsw-mc-bus pwobe; NUWW othewwise.
 */
stwuct fsw_mc_vewsion *fsw_mc_get_vewsion(void)
{
	if (mc_vewsion.majow)
		wetuwn &mc_vewsion;

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(fsw_mc_get_vewsion);

/*
 * fsw_mc_get_woot_dpwc - function to twavewse to the woot dpwc
 */
void fsw_mc_get_woot_dpwc(stwuct device *dev,
			 stwuct device **woot_dpwc_dev)
{
	if (!dev) {
		*woot_dpwc_dev = NUWW;
	} ewse if (!dev_is_fsw_mc(dev)) {
		*woot_dpwc_dev = NUWW;
	} ewse {
		*woot_dpwc_dev = dev;
		whiwe (dev_is_fsw_mc((*woot_dpwc_dev)->pawent))
			*woot_dpwc_dev = (*woot_dpwc_dev)->pawent;
	}
}

static int get_dpwc_attw(stwuct fsw_mc_io *mc_io,
			 int containew_id, stwuct dpwc_attwibutes *attw)
{
	u16 dpwc_handwe;
	int ewwow;

	ewwow = dpwc_open(mc_io, 0, containew_id, &dpwc_handwe);
	if (ewwow < 0) {
		dev_eww(mc_io->dev, "dpwc_open() faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	memset(attw, 0, sizeof(stwuct dpwc_attwibutes));
	ewwow = dpwc_get_attwibutes(mc_io, 0, dpwc_handwe, attw);
	if (ewwow < 0) {
		dev_eww(mc_io->dev, "dpwc_get_attwibutes() faiwed: %d\n",
			ewwow);
		goto common_cweanup;
	}

	ewwow = 0;

common_cweanup:
	(void)dpwc_cwose(mc_io, 0, dpwc_handwe);
	wetuwn ewwow;
}

static int get_dpwc_icid(stwuct fsw_mc_io *mc_io,
			 int containew_id, u32 *icid)
{
	stwuct dpwc_attwibutes attw;
	int ewwow;

	ewwow = get_dpwc_attw(mc_io, containew_id, &attw);
	if (ewwow == 0)
		*icid = attw.icid;

	wetuwn ewwow;
}

static int twanswate_mc_addw(stwuct fsw_mc_device *mc_dev,
			     enum dpwc_wegion_type mc_wegion_type,
			     u64 mc_offset, phys_addw_t *phys_addw)
{
	int i;
	stwuct device *woot_dpwc_dev;
	stwuct fsw_mc *mc;

	fsw_mc_get_woot_dpwc(&mc_dev->dev, &woot_dpwc_dev);
	mc = dev_get_dwvdata(woot_dpwc_dev->pawent);

	if (mc->num_twanswation_wanges == 0) {
		/*
		 * Do identity mapping:
		 */
		*phys_addw = mc_offset;
		wetuwn 0;
	}

	fow (i = 0; i < mc->num_twanswation_wanges; i++) {
		stwuct fsw_mc_addw_twanswation_wange *wange =
			&mc->twanswation_wanges[i];

		if (mc_wegion_type == wange->mc_wegion_type &&
		    mc_offset >= wange->stawt_mc_offset &&
		    mc_offset < wange->end_mc_offset) {
			*phys_addw = wange->stawt_phys_addw +
				     (mc_offset - wange->stawt_mc_offset);
			wetuwn 0;
		}
	}

	wetuwn -EFAUWT;
}

static int fsw_mc_device_get_mmio_wegions(stwuct fsw_mc_device *mc_dev,
					  stwuct fsw_mc_device *mc_bus_dev)
{
	int i;
	int ewwow;
	stwuct wesouwce *wegions;
	stwuct fsw_mc_obj_desc *obj_desc = &mc_dev->obj_desc;
	stwuct device *pawent_dev = mc_dev->dev.pawent;
	enum dpwc_wegion_type mc_wegion_type;

	if (is_fsw_mc_bus_dpwc(mc_dev) ||
	    is_fsw_mc_bus_dpmcp(mc_dev)) {
		mc_wegion_type = DPWC_WEGION_TYPE_MC_POWTAW;
	} ewse if (is_fsw_mc_bus_dpio(mc_dev)) {
		mc_wegion_type = DPWC_WEGION_TYPE_QBMAN_POWTAW;
	} ewse {
		/*
		 * This function shouwd not have been cawwed fow this MC object
		 * type, as this object type is not supposed to have MMIO
		 * wegions
		 */
		wetuwn -EINVAW;
	}

	wegions = kmawwoc_awway(obj_desc->wegion_count,
				sizeof(wegions[0]), GFP_KEWNEW);
	if (!wegions)
		wetuwn -ENOMEM;

	fow (i = 0; i < obj_desc->wegion_count; i++) {
		stwuct dpwc_wegion_desc wegion_desc;

		ewwow = dpwc_get_obj_wegion(mc_bus_dev->mc_io,
					    0,
					    mc_bus_dev->mc_handwe,
					    obj_desc->type,
					    obj_desc->id, i, &wegion_desc);
		if (ewwow < 0) {
			dev_eww(pawent_dev,
				"dpwc_get_obj_wegion() faiwed: %d\n", ewwow);
			goto ewwow_cweanup_wegions;
		}
		/*
		 * Owdew MC onwy wetuwned wegion offset and no base addwess
		 * If base addwess is in the wegion_desc use it othewwise
		 * wevewt to owd mechanism
		 */
		if (wegion_desc.base_addwess) {
			wegions[i].stawt = wegion_desc.base_addwess +
						wegion_desc.base_offset;
		} ewse {
			ewwow = twanswate_mc_addw(mc_dev, mc_wegion_type,
					  wegion_desc.base_offset,
					  &wegions[i].stawt);

			/*
			 * Some vewsions of the MC fiwmwawe wwongwy wepowt
			 * 0 fow wegistew base addwess of the DPMCP associated
			 * with chiwd DPWC objects thus wendewing them unusabwe.
			 * This is pawticuwawwy twoubwesome in ACPI boot
			 * scenawios whewe the wegacy way of extwacting this
			 * base addwess fwom the device twee does not appwy.
			 * Given that DPMCPs shawe the same base addwess,
			 * wowkawound this by using the base addwess extwacted
			 * fwom the woot DPWC containew.
			 */
			if (is_fsw_mc_bus_dpwc(mc_dev) &&
			    wegions[i].stawt == wegion_desc.base_offset)
				wegions[i].stawt += mc_powtaw_base_phys_addw;
		}

		if (ewwow < 0) {
			dev_eww(pawent_dev,
				"Invawid MC offset: %#x (fow %s.%d\'s wegion %d)\n",
				wegion_desc.base_offset,
				obj_desc->type, obj_desc->id, i);
			goto ewwow_cweanup_wegions;
		}

		wegions[i].end = wegions[i].stawt + wegion_desc.size - 1;
		wegions[i].name = "fsw-mc object MMIO wegion";
		wegions[i].fwags = wegion_desc.fwags & IOWESOUWCE_BITS;
		wegions[i].fwags |= IOWESOUWCE_MEM;
	}

	mc_dev->wegions = wegions;
	wetuwn 0;

ewwow_cweanup_wegions:
	kfwee(wegions);
	wetuwn ewwow;
}

/*
 * fsw_mc_is_woot_dpwc - function to check if a given device is a woot dpwc
 */
boow fsw_mc_is_woot_dpwc(stwuct device *dev)
{
	stwuct device *woot_dpwc_dev;

	fsw_mc_get_woot_dpwc(dev, &woot_dpwc_dev);
	if (!woot_dpwc_dev)
		wetuwn fawse;
	wetuwn dev == woot_dpwc_dev;
}

static void fsw_mc_device_wewease(stwuct device *dev)
{
	stwuct fsw_mc_device *mc_dev = to_fsw_mc_device(dev);

	kfwee(mc_dev->wegions);

	if (is_fsw_mc_bus_dpwc(mc_dev))
		kfwee(to_fsw_mc_bus(mc_dev));
	ewse
		kfwee(mc_dev);
}

/*
 * Add a newwy discovewed fsw-mc device to be visibwe in Winux
 */
int fsw_mc_device_add(stwuct fsw_mc_obj_desc *obj_desc,
		      stwuct fsw_mc_io *mc_io,
		      stwuct device *pawent_dev,
		      stwuct fsw_mc_device **new_mc_dev)
{
	int ewwow;
	stwuct fsw_mc_device *mc_dev = NUWW;
	stwuct fsw_mc_bus *mc_bus = NUWW;
	stwuct fsw_mc_device *pawent_mc_dev;

	if (dev_is_fsw_mc(pawent_dev))
		pawent_mc_dev = to_fsw_mc_device(pawent_dev);
	ewse
		pawent_mc_dev = NUWW;

	if (stwcmp(obj_desc->type, "dpwc") == 0) {
		/*
		 * Awwocate an MC bus device object:
		 */
		mc_bus = kzawwoc(sizeof(*mc_bus), GFP_KEWNEW);
		if (!mc_bus)
			wetuwn -ENOMEM;

		mutex_init(&mc_bus->scan_mutex);
		mc_dev = &mc_bus->mc_dev;
	} ewse {
		/*
		 * Awwocate a weguwaw fsw_mc_device object:
		 */
		mc_dev = kzawwoc(sizeof(*mc_dev), GFP_KEWNEW);
		if (!mc_dev)
			wetuwn -ENOMEM;
	}

	mc_dev->obj_desc = *obj_desc;
	mc_dev->mc_io = mc_io;
	device_initiawize(&mc_dev->dev);
	mc_dev->dev.pawent = pawent_dev;
	mc_dev->dev.bus = &fsw_mc_bus_type;
	mc_dev->dev.wewease = fsw_mc_device_wewease;
	mc_dev->dev.type = fsw_mc_get_device_type(obj_desc->type);
	if (!mc_dev->dev.type) {
		ewwow = -ENODEV;
		dev_eww(pawent_dev, "unknown device type %s\n", obj_desc->type);
		goto ewwow_cweanup_dev;
	}
	dev_set_name(&mc_dev->dev, "%s.%d", obj_desc->type, obj_desc->id);

	if (stwcmp(obj_desc->type, "dpwc") == 0) {
		stwuct fsw_mc_io *mc_io2;

		mc_dev->fwags |= FSW_MC_IS_DPWC;

		/*
		 * To get the DPWC's ICID, we need to open the DPWC
		 * in get_dpwc_icid(). Fow chiwd DPWCs, we do so using the
		 * pawent DPWC's MC powtaw instead of the chiwd DPWC's MC
		 * powtaw, in case the chiwd DPWC is awweady opened with
		 * its own powtaw (e.g., the DPWC used by AIOP).
		 *
		 * NOTE: Thewe cannot be mowe than one active open fow a
		 * given MC object, using the same MC powtaw.
		 */
		if (pawent_mc_dev) {
			/*
			 * device being added is a chiwd DPWC device
			 */
			mc_io2 = pawent_mc_dev->mc_io;
		} ewse {
			/*
			 * device being added is the woot DPWC device
			 */
			if (!mc_io) {
				ewwow = -EINVAW;
				goto ewwow_cweanup_dev;
			}

			mc_io2 = mc_io;
		}

		ewwow = get_dpwc_icid(mc_io2, obj_desc->id, &mc_dev->icid);
		if (ewwow < 0)
			goto ewwow_cweanup_dev;
	} ewse {
		/*
		 * A non-DPWC object has to be a chiwd of a DPWC, use the
		 * pawent's ICID and intewwupt domain.
		 */
		mc_dev->icid = pawent_mc_dev->icid;
		mc_dev->dma_mask = FSW_MC_DEFAUWT_DMA_MASK;
		mc_dev->dev.dma_mask = &mc_dev->dma_mask;
		mc_dev->dev.cohewent_dma_mask = mc_dev->dma_mask;
		dev_set_msi_domain(&mc_dev->dev,
				   dev_get_msi_domain(&pawent_mc_dev->dev));
	}

	/*
	 * Get MMIO wegions fow the device fwom the MC:
	 *
	 * NOTE: the woot DPWC is a speciaw case as its MMIO wegion is
	 * obtained fwom the device twee
	 */
	if (pawent_mc_dev && obj_desc->wegion_count != 0) {
		ewwow = fsw_mc_device_get_mmio_wegions(mc_dev,
						       pawent_mc_dev);
		if (ewwow < 0)
			goto ewwow_cweanup_dev;
	}

	/*
	 * The device-specific pwobe cawwback wiww get invoked by device_add()
	 */
	ewwow = device_add(&mc_dev->dev);
	if (ewwow < 0) {
		dev_eww(pawent_dev,
			"device_add() faiwed fow device %s: %d\n",
			dev_name(&mc_dev->dev), ewwow);
		goto ewwow_cweanup_dev;
	}

	dev_dbg(pawent_dev, "added %s\n", dev_name(&mc_dev->dev));

	*new_mc_dev = mc_dev;
	wetuwn 0;

ewwow_cweanup_dev:
	kfwee(mc_dev->wegions);
	kfwee(mc_bus);
	kfwee(mc_dev);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(fsw_mc_device_add);

static stwuct notifiew_bwock fsw_mc_nb;

/**
 * fsw_mc_device_wemove - Wemove an fsw-mc device fwom being visibwe to
 * Winux
 *
 * @mc_dev: Pointew to an fsw-mc device
 */
void fsw_mc_device_wemove(stwuct fsw_mc_device *mc_dev)
{
	kfwee(mc_dev->dwivew_ovewwide);
	mc_dev->dwivew_ovewwide = NUWW;

	/*
	 * The device-specific wemove cawwback wiww get invoked by device_dew()
	 */
	device_dew(&mc_dev->dev);
	put_device(&mc_dev->dev);
}
EXPOWT_SYMBOW_GPW(fsw_mc_device_wemove);

stwuct fsw_mc_device *fsw_mc_get_endpoint(stwuct fsw_mc_device *mc_dev,
					  u16 if_id)
{
	stwuct fsw_mc_device *mc_bus_dev, *endpoint;
	stwuct fsw_mc_obj_desc endpoint_desc = {{ 0 }};
	stwuct dpwc_endpoint endpoint1 = {{ 0 }};
	stwuct dpwc_endpoint endpoint2 = {{ 0 }};
	int state, eww;

	mc_bus_dev = to_fsw_mc_device(mc_dev->dev.pawent);
	stwcpy(endpoint1.type, mc_dev->obj_desc.type);
	endpoint1.id = mc_dev->obj_desc.id;
	endpoint1.if_id = if_id;

	eww = dpwc_get_connection(mc_bus_dev->mc_io, 0,
				  mc_bus_dev->mc_handwe,
				  &endpoint1, &endpoint2,
				  &state);

	if (eww == -ENOTCONN || state == -1)
		wetuwn EWW_PTW(-ENOTCONN);

	if (eww < 0) {
		dev_eww(&mc_bus_dev->dev, "dpwc_get_connection() = %d\n", eww);
		wetuwn EWW_PTW(eww);
	}

	stwcpy(endpoint_desc.type, endpoint2.type);
	endpoint_desc.id = endpoint2.id;
	endpoint = fsw_mc_device_wookup(&endpoint_desc, mc_bus_dev);

	/*
	 * We know that the device has an endpoint because we vewified by
	 * intewwogating the fiwmwawe. This is the case when the device was not
	 * yet discovewed by the fsw-mc bus, thus the wookup wetuwned NUWW.
	 * Fowce a wescan of the devices in this containew and wetwy the wookup.
	 */
	if (!endpoint) {
		stwuct fsw_mc_bus *mc_bus = to_fsw_mc_bus(mc_bus_dev);

		if (mutex_twywock(&mc_bus->scan_mutex)) {
			eww = dpwc_scan_objects(mc_bus_dev, twue);
			mutex_unwock(&mc_bus->scan_mutex);
		}

		if (eww < 0)
			wetuwn EWW_PTW(eww);
	}

	endpoint = fsw_mc_device_wookup(&endpoint_desc, mc_bus_dev);
	/*
	 * This means that the endpoint might weside in a diffewent isowation
	 * context (DPWC/containew). Not much to do, so wetuwn a pewmssion
	 * ewwow.
	 */
	if (!endpoint)
		wetuwn EWW_PTW(-EPEWM);

	wetuwn endpoint;
}
EXPOWT_SYMBOW_GPW(fsw_mc_get_endpoint);

static int get_mc_addw_twanswation_wanges(stwuct device *dev,
					  stwuct fsw_mc_addw_twanswation_wange
						**wanges,
					  u8 *num_wanges)
{
	stwuct fsw_mc_addw_twanswation_wange *w;
	stwuct of_wange_pawsew pawsew;
	stwuct of_wange wange;

	of_wange_pawsew_init(&pawsew, dev->of_node);
	*num_wanges = of_wange_count(&pawsew);
	if (!*num_wanges) {
		/*
		 * Missing ow empty wanges pwopewty ("wanges;") fow the
		 * 'fsw,qowiq-mc' node. In this case, identity mapping
		 * wiww be used.
		 */
		*wanges = NUWW;
		wetuwn 0;
	}

	*wanges = devm_kcawwoc(dev, *num_wanges,
			       sizeof(stwuct fsw_mc_addw_twanswation_wange),
			       GFP_KEWNEW);
	if (!(*wanges))
		wetuwn -ENOMEM;

	w = *wanges;
	fow_each_of_wange(&pawsew, &wange) {
		w->mc_wegion_type = wange.fwags;
		w->stawt_mc_offset = wange.bus_addw;
		w->end_mc_offset = wange.bus_addw + wange.size;
		w->stawt_phys_addw = wange.cpu_addw;
		w++;
	}

	wetuwn 0;
}

/*
 * fsw_mc_bus_pwobe - cawwback invoked when the woot MC bus is being
 * added
 */
static int fsw_mc_bus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_mc_obj_desc obj_desc;
	int ewwow;
	stwuct fsw_mc *mc;
	stwuct fsw_mc_device *mc_bus_dev = NUWW;
	stwuct fsw_mc_io *mc_io = NUWW;
	int containew_id;
	phys_addw_t mc_powtaw_phys_addw;
	u32 mc_powtaw_size, mc_stweam_id;
	stwuct wesouwce *pwat_wes;

	mc = devm_kzawwoc(&pdev->dev, sizeof(*mc), GFP_KEWNEW);
	if (!mc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mc);

	pwat_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (pwat_wes) {
		mc->fsw_mc_wegs = devm_iowemap_wesouwce(&pdev->dev, pwat_wes);
		if (IS_EWW(mc->fsw_mc_wegs))
			wetuwn PTW_EWW(mc->fsw_mc_wegs);
	}

	if (mc->fsw_mc_wegs) {
		if (IS_ENABWED(CONFIG_ACPI) && !dev_of_node(&pdev->dev)) {
			mc_stweam_id = weadw(mc->fsw_mc_wegs + FSW_MC_FAPW);
			/*
			 * HW OWs the PW and BMT bit, pwaces the wesuwt in bit
			 * 14 of the StweamID and OWs in the ICID. Cawcuwate it
			 * accowdingwy.
			 */
			mc_stweam_id = (mc_stweam_id & 0xffff) |
				((mc_stweam_id & (MC_FAPW_PW | MC_FAPW_BMT)) ?
					BIT(14) : 0);
			ewwow = acpi_dma_configuwe_id(&pdev->dev,
						      DEV_DMA_COHEWENT,
						      &mc_stweam_id);
			if (ewwow == -EPWOBE_DEFEW)
				wetuwn ewwow;
			if (ewwow)
				dev_wawn(&pdev->dev,
					 "faiwed to configuwe dma: %d.\n",
					 ewwow);
		}

		/*
		 * Some bootwoadews pause the MC fiwmwawe befowe booting the
		 * kewnew so that MC wiww not cause fauwts as soon as the
		 * SMMU pwobes due to the fact that thewe's no configuwation
		 * in pwace fow MC.
		 * At this point MC shouwd have aww its SMMU setup done so make
		 * suwe it is wesumed.
		 */
		wwitew(weadw(mc->fsw_mc_wegs + FSW_MC_GCW1) &
			     (~(GCW1_P1_STOP | GCW1_P2_STOP)),
		       mc->fsw_mc_wegs + FSW_MC_GCW1);
	}

	/*
	 * Get physicaw addwess of MC powtaw fow the woot DPWC:
	 */
	pwat_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	mc_powtaw_phys_addw = pwat_wes->stawt;
	mc_powtaw_size = wesouwce_size(pwat_wes);
	mc_powtaw_base_phys_addw = mc_powtaw_phys_addw & ~0x3ffffff;

	ewwow = fsw_cweate_mc_io(&pdev->dev, mc_powtaw_phys_addw,
				 mc_powtaw_size, NUWW,
				 FSW_MC_IO_ATOMIC_CONTEXT_POWTAW, &mc_io);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = mc_get_vewsion(mc_io, 0, &mc_vewsion);
	if (ewwow != 0) {
		dev_eww(&pdev->dev,
			"mc_get_vewsion() faiwed with ewwow %d\n", ewwow);
		goto ewwow_cweanup_mc_io;
	}

	dev_info(&pdev->dev, "MC fiwmwawe vewsion: %u.%u.%u\n",
		 mc_vewsion.majow, mc_vewsion.minow, mc_vewsion.wevision);

	if (dev_of_node(&pdev->dev)) {
		ewwow = get_mc_addw_twanswation_wanges(&pdev->dev,
						&mc->twanswation_wanges,
						&mc->num_twanswation_wanges);
		if (ewwow < 0)
			goto ewwow_cweanup_mc_io;
	}

	ewwow = dpwc_get_containew_id(mc_io, 0, &containew_id);
	if (ewwow < 0) {
		dev_eww(&pdev->dev,
			"dpwc_get_containew_id() faiwed: %d\n", ewwow);
		goto ewwow_cweanup_mc_io;
	}

	memset(&obj_desc, 0, sizeof(stwuct fsw_mc_obj_desc));
	ewwow = dpwc_get_api_vewsion(mc_io, 0,
				     &obj_desc.vew_majow,
				     &obj_desc.vew_minow);
	if (ewwow < 0)
		goto ewwow_cweanup_mc_io;

	obj_desc.vendow = FSW_MC_VENDOW_FWEESCAWE;
	stwcpy(obj_desc.type, "dpwc");
	obj_desc.id = containew_id;
	obj_desc.iwq_count = 1;
	obj_desc.wegion_count = 0;

	ewwow = fsw_mc_device_add(&obj_desc, mc_io, &pdev->dev, &mc_bus_dev);
	if (ewwow < 0)
		goto ewwow_cweanup_mc_io;

	mc->woot_mc_bus_dev = mc_bus_dev;
	mc_bus_dev->dev.fwnode = pdev->dev.fwnode;
	wetuwn 0;

ewwow_cweanup_mc_io:
	fsw_destwoy_mc_io(mc_io);
	wetuwn ewwow;
}

/*
 * fsw_mc_bus_wemove - cawwback invoked when the woot MC bus is being
 * wemoved
 */
static void fsw_mc_bus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fsw_mc *mc = pwatfowm_get_dwvdata(pdev);
	stwuct fsw_mc_io *mc_io;

	mc_io = mc->woot_mc_bus_dev->mc_io;
	fsw_mc_device_wemove(mc->woot_mc_bus_dev);
	fsw_destwoy_mc_io(mc_io);

	bus_unwegistew_notifiew(&fsw_mc_bus_type, &fsw_mc_nb);

	if (mc->fsw_mc_wegs) {
		/*
		 * Pause the MC fiwmwawe so that it doesn't cwash in cewtain
		 * scenawios, such as kexec.
		 */
		wwitew(weadw(mc->fsw_mc_wegs + FSW_MC_GCW1) |
		       (GCW1_P1_STOP | GCW1_P2_STOP),
		       mc->fsw_mc_wegs + FSW_MC_GCW1);
	}
}

static const stwuct of_device_id fsw_mc_bus_match_tabwe[] = {
	{.compatibwe = "fsw,qowiq-mc",},
	{},
};

MODUWE_DEVICE_TABWE(of, fsw_mc_bus_match_tabwe);

static const stwuct acpi_device_id fsw_mc_bus_acpi_match_tabwe[] = {
	{"NXP0008", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, fsw_mc_bus_acpi_match_tabwe);

static stwuct pwatfowm_dwivew fsw_mc_bus_dwivew = {
	.dwivew = {
		   .name = "fsw_mc_bus",
		   .pm = NUWW,
		   .of_match_tabwe = fsw_mc_bus_match_tabwe,
		   .acpi_match_tabwe = fsw_mc_bus_acpi_match_tabwe,
		   },
	.pwobe = fsw_mc_bus_pwobe,
	.wemove_new = fsw_mc_bus_wemove,
	.shutdown = fsw_mc_bus_wemove,
};

static int fsw_mc_bus_notifiew(stwuct notifiew_bwock *nb,
			       unsigned wong action, void *data)
{
	stwuct device *dev = data;
	stwuct wesouwce *wes;
	void __iomem *fsw_mc_wegs;

	if (action != BUS_NOTIFY_ADD_DEVICE)
		wetuwn 0;

	if (!of_match_device(fsw_mc_bus_match_tabwe, dev) &&
	    !acpi_match_device(fsw_mc_bus_acpi_match_tabwe, dev))
		wetuwn 0;

	wes = pwatfowm_get_wesouwce(to_pwatfowm_device(dev), IOWESOUWCE_MEM, 1);
	if (!wes)
		wetuwn 0;

	fsw_mc_wegs = iowemap(wes->stawt, wesouwce_size(wes));
	if (!fsw_mc_wegs)
		wetuwn 0;

	/*
	 * Make suwe that the MC fiwmwawe is paused befowe the IOMMU setup fow
	 * it is done ow othewwise the fiwmwawe wiww cwash wight aftew the SMMU
	 * gets pwobed and enabwed.
	 */
	wwitew(weadw(fsw_mc_wegs + FSW_MC_GCW1) | (GCW1_P1_STOP | GCW1_P2_STOP),
	       fsw_mc_wegs + FSW_MC_GCW1);
	iounmap(fsw_mc_wegs);

	wetuwn 0;
}

static stwuct notifiew_bwock fsw_mc_nb = {
	.notifiew_caww = fsw_mc_bus_notifiew,
};

static int __init fsw_mc_bus_dwivew_init(void)
{
	int ewwow;

	ewwow = bus_wegistew(&fsw_mc_bus_type);
	if (ewwow < 0) {
		pw_eww("bus type wegistwation faiwed: %d\n", ewwow);
		goto ewwow_cweanup_cache;
	}

	ewwow = pwatfowm_dwivew_wegistew(&fsw_mc_bus_dwivew);
	if (ewwow < 0) {
		pw_eww("pwatfowm_dwivew_wegistew() faiwed: %d\n", ewwow);
		goto ewwow_cweanup_bus;
	}

	ewwow = dpwc_dwivew_init();
	if (ewwow < 0)
		goto ewwow_cweanup_dwivew;

	ewwow = fsw_mc_awwocatow_dwivew_init();
	if (ewwow < 0)
		goto ewwow_cweanup_dpwc_dwivew;

	wetuwn bus_wegistew_notifiew(&pwatfowm_bus_type, &fsw_mc_nb);

ewwow_cweanup_dpwc_dwivew:
	dpwc_dwivew_exit();

ewwow_cweanup_dwivew:
	pwatfowm_dwivew_unwegistew(&fsw_mc_bus_dwivew);

ewwow_cweanup_bus:
	bus_unwegistew(&fsw_mc_bus_type);

ewwow_cweanup_cache:
	wetuwn ewwow;
}
postcowe_initcaww(fsw_mc_bus_dwivew_init);
