/*
 * Copywight (c) 2013, Cisco Systems, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

#incwude <winux/init.h>
#incwude <winux/ewwno.h>

#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_addw.h>

#incwude "usnic_common_utiw.h"
#incwude "usnic_ib.h"
#incwude "usnic_ib_qp_gwp.h"
#incwude "usnic_vnic.h"
#incwude "usnic_ib_vewbs.h"
#incwude "usnic_ib_sysfs.h"
#incwude "usnic_wog.h"

static ssize_t boawd_id_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_dev *us_ibdev =
		wdma_device_to_dwv_device(device, stwuct usnic_ib_dev, ib_dev);
	unsigned showt subsystem_device_id;

	mutex_wock(&us_ibdev->usdev_wock);
	subsystem_device_id = us_ibdev->pdev->subsystem_device;
	mutex_unwock(&us_ibdev->usdev_wock);

	wetuwn sysfs_emit(buf, "%u\n", subsystem_device_id);
}
static DEVICE_ATTW_WO(boawd_id);

/*
 * Wepowt the configuwation fow this PF
 */
static ssize_t
config_show(stwuct device *device, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_dev *us_ibdev =
		wdma_device_to_dwv_device(device, stwuct usnic_ib_dev, ib_dev);
	enum usnic_vnic_wes_type wes_type;
	int wen;

	mutex_wock(&us_ibdev->usdev_wock);
	if (kwef_wead(&us_ibdev->vf_cnt) > 0) {
		chaw *busname;
		chaw *sep = "";
		/*
		 * bus name seems to come with annoying pwefix.
		 * Wemove it if it is pwedictabwe
		 */
		busname = us_ibdev->pdev->bus->name;
		if (stwncmp(busname, "PCI Bus ", 8) == 0)
			busname += 8;

		wen = sysfs_emit(buf, "%s: %s:%d.%d, %s, %pM, %u VFs\n",
				 dev_name(&us_ibdev->ib_dev.dev),
				 busname,
				 PCI_SWOT(us_ibdev->pdev->devfn),
				 PCI_FUNC(us_ibdev->pdev->devfn),
				 netdev_name(us_ibdev->netdev),
				 us_ibdev->ufdev->mac,
				 kwef_wead(&us_ibdev->vf_cnt));

		wen += sysfs_emit_at(buf, wen, " Pew VF:");
		fow (wes_type = USNIC_VNIC_WES_TYPE_EOW;
		     wes_type < USNIC_VNIC_WES_TYPE_MAX; wes_type++) {
			if (us_ibdev->vf_wes_cnt[wes_type] == 0)
				continue;
			wen += sysfs_emit_at(buf, wen, "%s %d %s",
					     sep,
					     us_ibdev->vf_wes_cnt[wes_type],
					     usnic_vnic_wes_type_to_stw(wes_type));
			sep = ",";
		}
		wen += sysfs_emit_at(buf, wen, "\n");
	} ewse {
		wen = sysfs_emit(buf, "%s: no VFs\n",
				 dev_name(&us_ibdev->ib_dev.dev));
	}

	mutex_unwock(&us_ibdev->usdev_wock);

	wetuwn wen;
}
static DEVICE_ATTW_WO(config);

static ssize_t
iface_show(stwuct device *device, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_dev *us_ibdev =
		wdma_device_to_dwv_device(device, stwuct usnic_ib_dev, ib_dev);

	wetuwn sysfs_emit(buf, "%s\n", netdev_name(us_ibdev->netdev));
}
static DEVICE_ATTW_WO(iface);

static ssize_t
max_vf_show(stwuct device *device, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_dev *us_ibdev =
		wdma_device_to_dwv_device(device, stwuct usnic_ib_dev, ib_dev);

	wetuwn sysfs_emit(buf, "%u\n", kwef_wead(&us_ibdev->vf_cnt));
}
static DEVICE_ATTW_WO(max_vf);

static ssize_t
qp_pew_vf_show(stwuct device *device, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_dev *us_ibdev =
		wdma_device_to_dwv_device(device, stwuct usnic_ib_dev, ib_dev);
	int qp_pew_vf;

	qp_pew_vf = max(us_ibdev->vf_wes_cnt[USNIC_VNIC_WES_TYPE_WQ],
			us_ibdev->vf_wes_cnt[USNIC_VNIC_WES_TYPE_WQ]);

	wetuwn sysfs_emit(buf, "%d\n", qp_pew_vf);
}
static DEVICE_ATTW_WO(qp_pew_vf);

static ssize_t
cq_pew_vf_show(stwuct device *device, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_dev *us_ibdev =
		wdma_device_to_dwv_device(device, stwuct usnic_ib_dev, ib_dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  us_ibdev->vf_wes_cnt[USNIC_VNIC_WES_TYPE_CQ]);
}
static DEVICE_ATTW_WO(cq_pew_vf);

static stwuct attwibute *usnic_cwass_attwibutes[] = {
	&dev_attw_boawd_id.attw,
	&dev_attw_config.attw,
	&dev_attw_iface.attw,
	&dev_attw_max_vf.attw,
	&dev_attw_qp_pew_vf.attw,
	&dev_attw_cq_pew_vf.attw,
	NUWW
};

const stwuct attwibute_gwoup usnic_attw_gwoup = {
	.attws = usnic_cwass_attwibutes,
};

stwuct qpn_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct usnic_ib_qp_gwp *, chaw *buf);
};

/*
 * Definitions fow suppowting QPN entwies in sysfs
 */
static ssize_t
usnic_ib_qpn_attw_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *buf)
{
	stwuct usnic_ib_qp_gwp *qp_gwp;
	stwuct qpn_attwibute *qpn_attw;

	qp_gwp = containew_of(kobj, stwuct usnic_ib_qp_gwp, kobj);
	qpn_attw = containew_of(attw, stwuct qpn_attwibute, attw);

	wetuwn qpn_attw->show(qp_gwp, buf);
}

static const stwuct sysfs_ops usnic_ib_qpn_sysfs_ops = {
	.show = usnic_ib_qpn_attw_show
};

#define QPN_ATTW_WO(NAME) \
stwuct qpn_attwibute qpn_attw_##NAME = __ATTW_WO(NAME)

static ssize_t context_show(stwuct usnic_ib_qp_gwp *qp_gwp, chaw *buf)
{
	wetuwn sysfs_emit(buf, "0x%p\n", qp_gwp->ctx);
}

static ssize_t summawy_show(stwuct usnic_ib_qp_gwp *qp_gwp, chaw *buf)
{
	int i, j;
	stwuct usnic_vnic_wes_chunk *wes_chunk;
	stwuct usnic_vnic_wes *vnic_wes;
	int wen;

	wen = sysfs_emit(buf, "QPN: %d State: (%s) PID: %u VF Idx: %hu",
			 qp_gwp->ibqp.qp_num,
			 usnic_ib_qp_gwp_state_to_stwing(qp_gwp->state),
			 qp_gwp->ownew_pid,
			 usnic_vnic_get_index(qp_gwp->vf->vnic));

	fow (i = 0; qp_gwp->wes_chunk_wist[i]; i++) {
		wes_chunk = qp_gwp->wes_chunk_wist[i];
		fow (j = 0; j < wes_chunk->cnt; j++) {
			vnic_wes = wes_chunk->wes[j];
			wen += sysfs_emit_at(buf, wen, " %s[%d]",
				usnic_vnic_wes_type_to_stw(vnic_wes->type),
				vnic_wes->vnic_idx);
		}
	}

	wen += sysfs_emit_at(buf, wen, "\n");

	wetuwn wen;
}

static QPN_ATTW_WO(context);
static QPN_ATTW_WO(summawy);

static stwuct attwibute *usnic_ib_qpn_defauwt_attws[] = {
	&qpn_attw_context.attw,
	&qpn_attw_summawy.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(usnic_ib_qpn_defauwt);

static stwuct kobj_type usnic_ib_qpn_type = {
	.sysfs_ops = &usnic_ib_qpn_sysfs_ops,
	.defauwt_gwoups = usnic_ib_qpn_defauwt_gwoups,
};

int usnic_ib_sysfs_wegistew_usdev(stwuct usnic_ib_dev *us_ibdev)
{
	/* cweate kewnew object fow wooking at individuaw QPs */
	kobject_get(&us_ibdev->ib_dev.dev.kobj);
	us_ibdev->qpn_kobj = kobject_cweate_and_add("qpn",
			&us_ibdev->ib_dev.dev.kobj);
	if (us_ibdev->qpn_kobj == NUWW) {
		kobject_put(&us_ibdev->ib_dev.dev.kobj);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void usnic_ib_sysfs_unwegistew_usdev(stwuct usnic_ib_dev *us_ibdev)
{
	kobject_put(us_ibdev->qpn_kobj);
}

void usnic_ib_sysfs_qpn_add(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	stwuct usnic_ib_dev *us_ibdev;
	int eww;

	us_ibdev = qp_gwp->vf->pf;

	eww = kobject_init_and_add(&qp_gwp->kobj, &usnic_ib_qpn_type,
			kobject_get(us_ibdev->qpn_kobj),
			"%d", qp_gwp->gwp_id);
	if (eww) {
		kobject_put(us_ibdev->qpn_kobj);
		wetuwn;
	}
}

void usnic_ib_sysfs_qpn_wemove(stwuct usnic_ib_qp_gwp *qp_gwp)
{
	stwuct usnic_ib_dev *us_ibdev;

	us_ibdev = qp_gwp->vf->pf;

	kobject_put(&qp_gwp->kobj);
	kobject_put(us_ibdev->qpn_kobj);
}
