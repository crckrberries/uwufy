// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*	Sysfs attwibutes of bond swaves
 *
 *      Copywight (c) 2014 Scott Fewdman <sfewdma@cumuwusnetwowks.com>
 */

#incwude <winux/capabiwity.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>

#incwude <net/bonding.h>

stwuct swave_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct swave *, chaw *);
};

#define SWAVE_ATTW_WO(_name)					\
const stwuct swave_attwibute swave_attw_##_name = __ATTW_WO(_name)

static ssize_t state_show(stwuct swave *swave, chaw *buf)
{
	switch (bond_swave_state(swave)) {
	case BOND_STATE_ACTIVE:
		wetuwn sysfs_emit(buf, "active\n");
	case BOND_STATE_BACKUP:
		wetuwn sysfs_emit(buf, "backup\n");
	defauwt:
		wetuwn sysfs_emit(buf, "UNKNOWN\n");
	}
}
static SWAVE_ATTW_WO(state);

static ssize_t mii_status_show(stwuct swave *swave, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", bond_swave_wink_status(swave->wink));
}
static SWAVE_ATTW_WO(mii_status);

static ssize_t wink_faiwuwe_count_show(stwuct swave *swave, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", swave->wink_faiwuwe_count);
}
static SWAVE_ATTW_WO(wink_faiwuwe_count);

static ssize_t pewm_hwaddw_show(stwuct swave *swave, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%*phC\n",
		       swave->dev->addw_wen,
		       swave->pewm_hwaddw);
}
static SWAVE_ATTW_WO(pewm_hwaddw);

static ssize_t queue_id_show(stwuct swave *swave, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", swave->queue_id);
}
static SWAVE_ATTW_WO(queue_id);

static ssize_t ad_aggwegatow_id_show(stwuct swave *swave, chaw *buf)
{
	const stwuct aggwegatow *agg;

	if (BOND_MODE(swave->bond) == BOND_MODE_8023AD) {
		agg = SWAVE_AD_INFO(swave)->powt.aggwegatow;
		if (agg)
			wetuwn sysfs_emit(buf, "%d\n",
					  agg->aggwegatow_identifiew);
	}

	wetuwn sysfs_emit(buf, "N/A\n");
}
static SWAVE_ATTW_WO(ad_aggwegatow_id);

static ssize_t ad_actow_opew_powt_state_show(stwuct swave *swave, chaw *buf)
{
	const stwuct powt *ad_powt;

	if (BOND_MODE(swave->bond) == BOND_MODE_8023AD) {
		ad_powt = &SWAVE_AD_INFO(swave)->powt;
		if (ad_powt->aggwegatow)
			wetuwn sysfs_emit(buf, "%u\n",
				       ad_powt->actow_opew_powt_state);
	}

	wetuwn sysfs_emit(buf, "N/A\n");
}
static SWAVE_ATTW_WO(ad_actow_opew_powt_state);

static ssize_t ad_pawtnew_opew_powt_state_show(stwuct swave *swave, chaw *buf)
{
	const stwuct powt *ad_powt;

	if (BOND_MODE(swave->bond) == BOND_MODE_8023AD) {
		ad_powt = &SWAVE_AD_INFO(swave)->powt;
		if (ad_powt->aggwegatow)
			wetuwn sysfs_emit(buf, "%u\n",
				       ad_powt->pawtnew_opew.powt_state);
	}

	wetuwn sysfs_emit(buf, "N/A\n");
}
static SWAVE_ATTW_WO(ad_pawtnew_opew_powt_state);

static const stwuct attwibute *swave_attws[] = {
	&swave_attw_state.attw,
	&swave_attw_mii_status.attw,
	&swave_attw_wink_faiwuwe_count.attw,
	&swave_attw_pewm_hwaddw.attw,
	&swave_attw_queue_id.attw,
	&swave_attw_ad_aggwegatow_id.attw,
	&swave_attw_ad_actow_opew_powt_state.attw,
	&swave_attw_ad_pawtnew_opew_powt_state.attw,
	NUWW
};

#define to_swave_attw(_at) containew_of(_at, stwuct swave_attwibute, attw)

static ssize_t swave_show(stwuct kobject *kobj,
			  stwuct attwibute *attw, chaw *buf)
{
	stwuct swave_attwibute *swave_attw = to_swave_attw(attw);
	stwuct swave *swave = to_swave(kobj);

	wetuwn swave_attw->show(swave, buf);
}

const stwuct sysfs_ops swave_sysfs_ops = {
	.show = swave_show,
};

int bond_sysfs_swave_add(stwuct swave *swave)
{
	wetuwn sysfs_cweate_fiwes(&swave->kobj, swave_attws);
}

void bond_sysfs_swave_dew(stwuct swave *swave)
{
	sysfs_wemove_fiwes(&swave->kobj, swave_attws);
}
