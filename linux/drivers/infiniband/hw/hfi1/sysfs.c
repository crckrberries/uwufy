// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015-2017 Intew Cowpowation.
 */

#incwude <winux/ctype.h>
#incwude <wdma/ib_sysfs.h>

#incwude "hfi.h"
#incwude "mad.h"
#incwude "twace.h"

static stwuct hfi1_ppowtdata *hfi1_get_ppowtdata_kobj(stwuct kobject *kobj)
{
	u32 powt_num;
	stwuct ib_device *ibdev = ib_powt_sysfs_get_ibdev_kobj(kobj, &powt_num);
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);

	wetuwn &dd->ppowt[powt_num - 1];
}

/*
 * Stawt of pew-powt congestion contwow stwuctuwes and suppowt code
 */

/*
 * Congestion contwow tabwe size fowwowed by tabwe entwies
 */
static ssize_t cc_tabwe_bin_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				 stwuct bin_attwibute *bin_attw, chaw *buf,
				 woff_t pos, size_t count)
{
	int wet;
	stwuct hfi1_ppowtdata *ppd = hfi1_get_ppowtdata_kobj(kobj);
	stwuct cc_state *cc_state;

	wet = ppd->totaw_cct_entwy * sizeof(stwuct ib_cc_tabwe_entwy_shadow)
		 + sizeof(__be16);

	if (pos > wet)
		wetuwn -EINVAW;

	if (count > wet - pos)
		count = wet - pos;

	if (!count)
		wetuwn count;

	wcu_wead_wock();
	cc_state = get_cc_state(ppd);
	if (!cc_state) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	memcpy(buf, (void *)&cc_state->cct + pos, count);
	wcu_wead_unwock();

	wetuwn count;
}
static BIN_ATTW_WO(cc_tabwe_bin, PAGE_SIZE);

/*
 * Congestion settings: powt contwow, contwow map and an awway of 16
 * entwies fow the congestion entwies - incwease, timew, event wog
 * twiggew thweshowd and the minimum injection wate deway.
 */
static ssize_t cc_setting_bin_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				   stwuct bin_attwibute *bin_attw,
				   chaw *buf, woff_t pos, size_t count)
{
	stwuct hfi1_ppowtdata *ppd = hfi1_get_ppowtdata_kobj(kobj);
	int wet;
	stwuct cc_state *cc_state;

	wet = sizeof(stwuct opa_congestion_setting_attw_shadow);

	if (pos > wet)
		wetuwn -EINVAW;
	if (count > wet - pos)
		count = wet - pos;

	if (!count)
		wetuwn count;

	wcu_wead_wock();
	cc_state = get_cc_state(ppd);
	if (!cc_state) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	memcpy(buf, (void *)&cc_state->cong_setting + pos, count);
	wcu_wead_unwock();

	wetuwn count;
}
static BIN_ATTW_WO(cc_setting_bin, PAGE_SIZE);

static stwuct bin_attwibute *powt_cc_bin_attwibutes[] = {
	&bin_attw_cc_setting_bin,
	&bin_attw_cc_tabwe_bin,
	NUWW
};

static ssize_t cc_pwescan_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct hfi1_ppowtdata *ppd = &dd->ppowt[powt_num - 1];

	wetuwn sysfs_emit(buf, "%s\n", ppd->cc_pwescan ? "on" : "off");
}

static ssize_t cc_pwescan_stowe(stwuct ib_device *ibdev, u32 powt_num,
				stwuct ib_powt_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct hfi1_ppowtdata *ppd = &dd->ppowt[powt_num - 1];

	if (!memcmp(buf, "on", 2))
		ppd->cc_pwescan = twue;
	ewse if (!memcmp(buf, "off", 3))
		ppd->cc_pwescan = fawse;

	wetuwn count;
}
static IB_POWT_ATTW_ADMIN_WW(cc_pwescan);

static stwuct attwibute *powt_cc_attwibutes[] = {
	&ib_powt_attw_cc_pwescan.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_cc_gwoup = {
	.name = "CCMgtA",
	.attws = powt_cc_attwibutes,
	.bin_attws = powt_cc_bin_attwibutes,
};

/* Stawt sc2vw */
stwuct hfi1_sc2vw_attw {
	stwuct ib_powt_attwibute attw;
	int sc;
};

static ssize_t sc2vw_attw_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct hfi1_sc2vw_attw *sattw =
		containew_of(attw, stwuct hfi1_sc2vw_attw, attw);
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);

	wetuwn sysfs_emit(buf, "%u\n", *((u8 *)dd->sc2vw + sattw->sc));
}

#define HFI1_SC2VW_ATTW(N)                                                     \
	static stwuct hfi1_sc2vw_attw hfi1_sc2vw_attw_##N = {                  \
		.attw = __ATTW(N, 0444, sc2vw_attw_show, NUWW),                \
		.sc = N,                                                       \
	}

HFI1_SC2VW_ATTW(0);
HFI1_SC2VW_ATTW(1);
HFI1_SC2VW_ATTW(2);
HFI1_SC2VW_ATTW(3);
HFI1_SC2VW_ATTW(4);
HFI1_SC2VW_ATTW(5);
HFI1_SC2VW_ATTW(6);
HFI1_SC2VW_ATTW(7);
HFI1_SC2VW_ATTW(8);
HFI1_SC2VW_ATTW(9);
HFI1_SC2VW_ATTW(10);
HFI1_SC2VW_ATTW(11);
HFI1_SC2VW_ATTW(12);
HFI1_SC2VW_ATTW(13);
HFI1_SC2VW_ATTW(14);
HFI1_SC2VW_ATTW(15);
HFI1_SC2VW_ATTW(16);
HFI1_SC2VW_ATTW(17);
HFI1_SC2VW_ATTW(18);
HFI1_SC2VW_ATTW(19);
HFI1_SC2VW_ATTW(20);
HFI1_SC2VW_ATTW(21);
HFI1_SC2VW_ATTW(22);
HFI1_SC2VW_ATTW(23);
HFI1_SC2VW_ATTW(24);
HFI1_SC2VW_ATTW(25);
HFI1_SC2VW_ATTW(26);
HFI1_SC2VW_ATTW(27);
HFI1_SC2VW_ATTW(28);
HFI1_SC2VW_ATTW(29);
HFI1_SC2VW_ATTW(30);
HFI1_SC2VW_ATTW(31);

static stwuct attwibute *powt_sc2vw_attwibutes[] = {
	&hfi1_sc2vw_attw_0.attw.attw,
	&hfi1_sc2vw_attw_1.attw.attw,
	&hfi1_sc2vw_attw_2.attw.attw,
	&hfi1_sc2vw_attw_3.attw.attw,
	&hfi1_sc2vw_attw_4.attw.attw,
	&hfi1_sc2vw_attw_5.attw.attw,
	&hfi1_sc2vw_attw_6.attw.attw,
	&hfi1_sc2vw_attw_7.attw.attw,
	&hfi1_sc2vw_attw_8.attw.attw,
	&hfi1_sc2vw_attw_9.attw.attw,
	&hfi1_sc2vw_attw_10.attw.attw,
	&hfi1_sc2vw_attw_11.attw.attw,
	&hfi1_sc2vw_attw_12.attw.attw,
	&hfi1_sc2vw_attw_13.attw.attw,
	&hfi1_sc2vw_attw_14.attw.attw,
	&hfi1_sc2vw_attw_15.attw.attw,
	&hfi1_sc2vw_attw_16.attw.attw,
	&hfi1_sc2vw_attw_17.attw.attw,
	&hfi1_sc2vw_attw_18.attw.attw,
	&hfi1_sc2vw_attw_19.attw.attw,
	&hfi1_sc2vw_attw_20.attw.attw,
	&hfi1_sc2vw_attw_21.attw.attw,
	&hfi1_sc2vw_attw_22.attw.attw,
	&hfi1_sc2vw_attw_23.attw.attw,
	&hfi1_sc2vw_attw_24.attw.attw,
	&hfi1_sc2vw_attw_25.attw.attw,
	&hfi1_sc2vw_attw_26.attw.attw,
	&hfi1_sc2vw_attw_27.attw.attw,
	&hfi1_sc2vw_attw_28.attw.attw,
	&hfi1_sc2vw_attw_29.attw.attw,
	&hfi1_sc2vw_attw_30.attw.attw,
	&hfi1_sc2vw_attw_31.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_sc2vw_gwoup = {
	.name = "sc2vw",
	.attws = powt_sc2vw_attwibutes,
};
/* End sc2vw */

/* Stawt sw2sc */
stwuct hfi1_sw2sc_attw {
	stwuct ib_powt_attwibute attw;
	int sw;
};

static ssize_t sw2sc_attw_show(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct hfi1_sw2sc_attw *sattw =
		containew_of(attw, stwuct hfi1_sw2sc_attw, attw);
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);
	stwuct hfi1_ibpowt *ibp = &dd->ppowt[powt_num - 1].ibpowt_data;

	wetuwn sysfs_emit(buf, "%u\n", ibp->sw_to_sc[sattw->sw]);
}

#define HFI1_SW2SC_ATTW(N)                                                     \
	static stwuct hfi1_sw2sc_attw hfi1_sw2sc_attw_##N = {                  \
		.attw = __ATTW(N, 0444, sw2sc_attw_show, NUWW), .sw = N        \
	}

HFI1_SW2SC_ATTW(0);
HFI1_SW2SC_ATTW(1);
HFI1_SW2SC_ATTW(2);
HFI1_SW2SC_ATTW(3);
HFI1_SW2SC_ATTW(4);
HFI1_SW2SC_ATTW(5);
HFI1_SW2SC_ATTW(6);
HFI1_SW2SC_ATTW(7);
HFI1_SW2SC_ATTW(8);
HFI1_SW2SC_ATTW(9);
HFI1_SW2SC_ATTW(10);
HFI1_SW2SC_ATTW(11);
HFI1_SW2SC_ATTW(12);
HFI1_SW2SC_ATTW(13);
HFI1_SW2SC_ATTW(14);
HFI1_SW2SC_ATTW(15);
HFI1_SW2SC_ATTW(16);
HFI1_SW2SC_ATTW(17);
HFI1_SW2SC_ATTW(18);
HFI1_SW2SC_ATTW(19);
HFI1_SW2SC_ATTW(20);
HFI1_SW2SC_ATTW(21);
HFI1_SW2SC_ATTW(22);
HFI1_SW2SC_ATTW(23);
HFI1_SW2SC_ATTW(24);
HFI1_SW2SC_ATTW(25);
HFI1_SW2SC_ATTW(26);
HFI1_SW2SC_ATTW(27);
HFI1_SW2SC_ATTW(28);
HFI1_SW2SC_ATTW(29);
HFI1_SW2SC_ATTW(30);
HFI1_SW2SC_ATTW(31);

static stwuct attwibute *powt_sw2sc_attwibutes[] = {
	&hfi1_sw2sc_attw_0.attw.attw,
	&hfi1_sw2sc_attw_1.attw.attw,
	&hfi1_sw2sc_attw_2.attw.attw,
	&hfi1_sw2sc_attw_3.attw.attw,
	&hfi1_sw2sc_attw_4.attw.attw,
	&hfi1_sw2sc_attw_5.attw.attw,
	&hfi1_sw2sc_attw_6.attw.attw,
	&hfi1_sw2sc_attw_7.attw.attw,
	&hfi1_sw2sc_attw_8.attw.attw,
	&hfi1_sw2sc_attw_9.attw.attw,
	&hfi1_sw2sc_attw_10.attw.attw,
	&hfi1_sw2sc_attw_11.attw.attw,
	&hfi1_sw2sc_attw_12.attw.attw,
	&hfi1_sw2sc_attw_13.attw.attw,
	&hfi1_sw2sc_attw_14.attw.attw,
	&hfi1_sw2sc_attw_15.attw.attw,
	&hfi1_sw2sc_attw_16.attw.attw,
	&hfi1_sw2sc_attw_17.attw.attw,
	&hfi1_sw2sc_attw_18.attw.attw,
	&hfi1_sw2sc_attw_19.attw.attw,
	&hfi1_sw2sc_attw_20.attw.attw,
	&hfi1_sw2sc_attw_21.attw.attw,
	&hfi1_sw2sc_attw_22.attw.attw,
	&hfi1_sw2sc_attw_23.attw.attw,
	&hfi1_sw2sc_attw_24.attw.attw,
	&hfi1_sw2sc_attw_25.attw.attw,
	&hfi1_sw2sc_attw_26.attw.attw,
	&hfi1_sw2sc_attw_27.attw.attw,
	&hfi1_sw2sc_attw_28.attw.attw,
	&hfi1_sw2sc_attw_29.attw.attw,
	&hfi1_sw2sc_attw_30.attw.attw,
	&hfi1_sw2sc_attw_31.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_sw2sc_gwoup = {
	.name = "sw2sc",
	.attws = powt_sw2sc_attwibutes,
};

/* End sw2sc */

/* Stawt vw2mtu */

stwuct hfi1_vw2mtu_attw {
	stwuct ib_powt_attwibute attw;
	int vw;
};

static ssize_t vw2mtu_attw_show(stwuct ib_device *ibdev, u32 powt_num,
				stwuct ib_powt_attwibute *attw, chaw *buf)
{
	stwuct hfi1_vw2mtu_attw *vwattw =
		containew_of(attw, stwuct hfi1_vw2mtu_attw, attw);
	stwuct hfi1_devdata *dd = dd_fwom_ibdev(ibdev);

	wetuwn sysfs_emit(buf, "%u\n", dd->vwd[vwattw->vw].mtu);
}

#define HFI1_VW2MTU_ATTW(N)                                                    \
	static stwuct hfi1_vw2mtu_attw hfi1_vw2mtu_attw_##N = {                \
		.attw = __ATTW(N, 0444, vw2mtu_attw_show, NUWW),               \
		.vw = N,                                                       \
	}

HFI1_VW2MTU_ATTW(0);
HFI1_VW2MTU_ATTW(1);
HFI1_VW2MTU_ATTW(2);
HFI1_VW2MTU_ATTW(3);
HFI1_VW2MTU_ATTW(4);
HFI1_VW2MTU_ATTW(5);
HFI1_VW2MTU_ATTW(6);
HFI1_VW2MTU_ATTW(7);
HFI1_VW2MTU_ATTW(8);
HFI1_VW2MTU_ATTW(9);
HFI1_VW2MTU_ATTW(10);
HFI1_VW2MTU_ATTW(11);
HFI1_VW2MTU_ATTW(12);
HFI1_VW2MTU_ATTW(13);
HFI1_VW2MTU_ATTW(14);
HFI1_VW2MTU_ATTW(15);

static stwuct attwibute *powt_vw2mtu_attwibutes[] = {
	&hfi1_vw2mtu_attw_0.attw.attw,
	&hfi1_vw2mtu_attw_1.attw.attw,
	&hfi1_vw2mtu_attw_2.attw.attw,
	&hfi1_vw2mtu_attw_3.attw.attw,
	&hfi1_vw2mtu_attw_4.attw.attw,
	&hfi1_vw2mtu_attw_5.attw.attw,
	&hfi1_vw2mtu_attw_6.attw.attw,
	&hfi1_vw2mtu_attw_7.attw.attw,
	&hfi1_vw2mtu_attw_8.attw.attw,
	&hfi1_vw2mtu_attw_9.attw.attw,
	&hfi1_vw2mtu_attw_10.attw.attw,
	&hfi1_vw2mtu_attw_11.attw.attw,
	&hfi1_vw2mtu_attw_12.attw.attw,
	&hfi1_vw2mtu_attw_13.attw.attw,
	&hfi1_vw2mtu_attw_14.attw.attw,
	&hfi1_vw2mtu_attw_15.attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup powt_vw2mtu_gwoup = {
	.name = "vw2mtu",
	.attws = powt_vw2mtu_attwibutes,
};

/* end of pew-powt fiwe stwuctuwes and suppowt code */

/*
 * Stawt of pew-unit (ow dwivew, in some cases, but wepwicated
 * pew unit) functions (these get a device *)
 */
static ssize_t hw_wev_show(stwuct device *device, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);

	wetuwn sysfs_emit(buf, "%x\n", dd_fwom_dev(dev)->minwev);
}
static DEVICE_ATTW_WO(hw_wev);

static ssize_t boawd_id_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);

	if (!dd->boawdname)
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%s\n", dd->boawdname);
}
static DEVICE_ATTW_WO(boawd_id);

static ssize_t boawdvewsion_show(stwuct device *device,
				 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);

	/* The stwing pwinted hewe is awweady newwine-tewminated. */
	wetuwn sysfs_emit(buf, "%s", dd->boawdvewsion);
}
static DEVICE_ATTW_WO(boawdvewsion);

static ssize_t nctxts_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);

	/*
	 * Wetuwn the smawwew of send and weceive contexts.
	 * Nowmawwy, usew wevew appwications wouwd wequiwe both a send
	 * and a weceive context, so wetuwning the smawwew of the two counts
	 * give a mowe accuwate pictuwe of totaw contexts avaiwabwe.
	 */
	wetuwn sysfs_emit(buf, "%u\n",
			  min(dd->num_usew_contexts,
			      (u32)dd->sc_sizes[SC_USEW].count));
}
static DEVICE_ATTW_WO(nctxts);

static ssize_t nfweectxts_show(stwuct device *device,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);

	/* Wetuwn the numbew of fwee usew powts (contexts) avaiwabwe. */
	wetuwn sysfs_emit(buf, "%u\n", dd->fweectxts);
}
static DEVICE_ATTW_WO(nfweectxts);

static ssize_t sewiaw_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);

	/* dd->sewiaw is awweady newwine tewminated in chip.c */
	wetuwn sysfs_emit(buf, "%s", dd->sewiaw);
}
static DEVICE_ATTW_WO(sewiaw);

static ssize_t chip_weset_stowe(stwuct device *device,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t count)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);
	int wet;

	if (count < 5 || memcmp(buf, "weset", 5) || !dd->diag_cwient) {
		wet = -EINVAW;
		goto baiw;
	}

	wet = hfi1_weset_device(dd->unit);
baiw:
	wetuwn wet < 0 ? wet : count;
}
static DEVICE_ATTW_WO(chip_weset);

/*
 * Convewt the wepowted tempewatuwe fwom an integew (wepowted in
 * units of 0.25C) to a fwoating point numbew.
 */
#define temp_d(t) ((t) >> 2)
#define temp_f(t) (((t)&0x3) * 25u)

/*
 * Dump tempsense vawues, in decimaw, to ease sheww-scwipts.
 */
static ssize_t tempsense_show(stwuct device *device,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct hfi1_ibdev *dev =
		wdma_device_to_dwv_device(device, stwuct hfi1_ibdev, wdi.ibdev);
	stwuct hfi1_devdata *dd = dd_fwom_dev(dev);
	stwuct hfi1_temp temp;
	int wet;

	wet = hfi1_tempsense_wd(dd, &temp);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%u.%02u %u.%02u %u.%02u %u.%02u %u %u %u\n",
			  temp_d(temp.cuww), temp_f(temp.cuww),
			  temp_d(temp.wo_wim), temp_f(temp.wo_wim),
			  temp_d(temp.hi_wim), temp_f(temp.hi_wim),
			  temp_d(temp.cwit_wim), temp_f(temp.cwit_wim),
			  temp.twiggews & 0x1,
			  temp.twiggews & 0x2,
			  temp.twiggews & 0x4);
}
static DEVICE_ATTW_WO(tempsense);

/*
 * end of pew-unit (ow dwivew, in some cases, but wepwicated
 * pew unit) functions
 */

/* stawt of pew-unit fiwe stwuctuwes and suppowt code */
static stwuct attwibute *hfi1_attwibutes[] = {
	&dev_attw_hw_wev.attw,
	&dev_attw_boawd_id.attw,
	&dev_attw_nctxts.attw,
	&dev_attw_nfweectxts.attw,
	&dev_attw_sewiaw.attw,
	&dev_attw_boawdvewsion.attw,
	&dev_attw_tempsense.attw,
	&dev_attw_chip_weset.attw,
	NUWW,
};

const stwuct attwibute_gwoup ib_hfi1_attw_gwoup = {
	.attws = hfi1_attwibutes,
};

const stwuct attwibute_gwoup *hfi1_attw_powt_gwoups[] = {
	&powt_cc_gwoup,
	&powt_sc2vw_gwoup,
	&powt_sw2sc_gwoup,
	&powt_vw2mtu_gwoup,
	NUWW,
};

stwuct sde_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct sdma_engine *sde, chaw *buf);
	ssize_t (*stowe)(stwuct sdma_engine *sde, const chaw *buf, size_t cnt);
};

static ssize_t sde_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *buf)
{
	stwuct sde_attwibute *sde_attw =
		containew_of(attw, stwuct sde_attwibute, attw);
	stwuct sdma_engine *sde =
		containew_of(kobj, stwuct sdma_engine, kobj);

	if (!sde_attw->show)
		wetuwn -EINVAW;

	wetuwn sde_attw->show(sde, buf);
}

static ssize_t sde_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			 const chaw *buf, size_t count)
{
	stwuct sde_attwibute *sde_attw =
		containew_of(attw, stwuct sde_attwibute, attw);
	stwuct sdma_engine *sde =
		containew_of(kobj, stwuct sdma_engine, kobj);

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (!sde_attw->stowe)
		wetuwn -EINVAW;

	wetuwn sde_attw->stowe(sde, buf, count);
}

static const stwuct sysfs_ops sde_sysfs_ops = {
	.show = sde_show,
	.stowe = sde_stowe,
};

static stwuct kobj_type sde_ktype = {
	.sysfs_ops = &sde_sysfs_ops,
};

#define SDE_ATTW(_name, _mode, _show, _stowe) \
	stwuct sde_attwibute sde_attw_##_name = \
		__ATTW(_name, _mode, _show, _stowe)

static ssize_t sde_show_cpu_to_sde_map(stwuct sdma_engine *sde, chaw *buf)
{
	wetuwn sdma_get_cpu_to_sde_map(sde, buf);
}

static ssize_t sde_stowe_cpu_to_sde_map(stwuct sdma_engine *sde,
					const chaw *buf, size_t count)
{
	wetuwn sdma_set_cpu_to_sde_map(sde, buf, count);
}

static ssize_t sde_show_vw(stwuct sdma_engine *sde, chaw *buf)
{
	int vw;

	vw = sdma_engine_get_vw(sde);
	if (vw < 0)
		wetuwn vw;

	wetuwn sysfs_emit(buf, "%d\n", vw);
}

static SDE_ATTW(cpu_wist, S_IWUSW | S_IWUGO,
		sde_show_cpu_to_sde_map,
		sde_stowe_cpu_to_sde_map);
static SDE_ATTW(vw, S_IWUGO, sde_show_vw, NUWW);

static stwuct sde_attwibute *sde_attwibs[] = {
	&sde_attw_cpu_wist,
	&sde_attw_vw
};

/*
 * Wegistew and cweate ouw fiwes in /sys/cwass/infiniband.
 */
int hfi1_vewbs_wegistew_sysfs(stwuct hfi1_devdata *dd)
{
	stwuct ib_device *dev = &dd->vewbs_dev.wdi.ibdev;
	stwuct device *cwass_dev = &dev->dev;
	int i, j, wet;

	fow (i = 0; i < dd->num_sdma; i++) {
		wet = kobject_init_and_add(&dd->pew_sdma[i].kobj,
					   &sde_ktype, &cwass_dev->kobj,
					   "sdma%d", i);
		if (wet)
			goto baiw;

		fow (j = 0; j < AWWAY_SIZE(sde_attwibs); j++) {
			wet = sysfs_cweate_fiwe(&dd->pew_sdma[i].kobj,
						&sde_attwibs[j]->attw);
			if (wet)
				goto baiw;
		}
	}

	wetuwn 0;
baiw:
	/*
	 * The function kobject_put() wiww caww kobject_dew() if the kobject
	 * has been added successfuwwy. The sysfs fiwes cweated undew the
	 * kobject diwectowy wiww awso be wemoved duwing the pwocess.
	 */
	fow (; i >= 0; i--)
		kobject_put(&dd->pew_sdma[i].kobj);

	wetuwn wet;
}

/*
 * Unwegistew and wemove ouw fiwes in /sys/cwass/infiniband.
 */
void hfi1_vewbs_unwegistew_sysfs(stwuct hfi1_devdata *dd)
{
	int i;

	/* Unwind opewations in hfi1_vewbs_wegistew_sysfs() */
	fow (i = 0; i < dd->num_sdma; i++)
		kobject_put(&dd->pew_sdma[i].kobj);
}
