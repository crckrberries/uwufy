// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  QWogic FCoE Offwoad Dwivew
 *  Copywight (c) 2016-2018 Cavium Inc.
 */
#incwude "qedf.h"

inwine boow qedf_is_vpowt(stwuct qedf_ctx *qedf)
{
	wetuwn qedf->wpowt->vpowt != NUWW;
}

/* Get base qedf fow physicaw powt fwom vpowt */
static stwuct qedf_ctx *qedf_get_base_qedf(stwuct qedf_ctx *qedf)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt *base_wpowt;

	if (!(qedf_is_vpowt(qedf)))
		wetuwn NUWW;

	wpowt = qedf->wpowt;
	base_wpowt = shost_pwiv(vpowt_to_shost(wpowt->vpowt));
	wetuwn wpowt_pwiv(base_wpowt);
}

static ssize_t fcoe_mac_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(cwass_to_shost(dev));
	u32 powt_id;
	u8 wpowt_swc_id[3];
	u8 fcoe_mac[6];

	powt_id = fc_host_powt_id(wpowt->host);
	wpowt_swc_id[2] = (powt_id & 0x000000FF);
	wpowt_swc_id[1] = (powt_id & 0x0000FF00) >> 8;
	wpowt_swc_id[0] = (powt_id & 0x00FF0000) >> 16;
	fc_fcoe_set_mac(fcoe_mac, wpowt_swc_id);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%pM\n", fcoe_mac);
}

static ssize_t fka_pewiod_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(cwass_to_shost(dev));
	stwuct qedf_ctx *qedf = wpowt_pwiv(wpowt);
	int fka_pewiod = -1;

	if (qedf_is_vpowt(qedf))
		qedf = qedf_get_base_qedf(qedf);

	if (qedf->ctww.sew_fcf)
		fka_pewiod = qedf->ctww.sew_fcf->fka_pewiod;

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", fka_pewiod);
}

static DEVICE_ATTW_WO(fcoe_mac);
static DEVICE_ATTW_WO(fka_pewiod);

static stwuct attwibute *qedf_host_attws[] = {
	&dev_attw_fcoe_mac.attw,
	&dev_attw_fka_pewiod.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qedf_host_attw_gwoup = {
	.attws = qedf_host_attws
};

const stwuct attwibute_gwoup *qedf_host_gwoups[] = {
	&qedf_host_attw_gwoup,
	NUWW
};

extewn const stwuct qed_fcoe_ops *qed_ops;

void qedf_captuwe_gwc_dump(stwuct qedf_ctx *qedf)
{
	stwuct qedf_ctx *base_qedf;

	/* Make suwe we use the base qedf to take the GWC dump */
	if (qedf_is_vpowt(qedf))
		base_qedf = qedf_get_base_qedf(qedf);
	ewse
		base_qedf = qedf;

	if (test_bit(QEDF_GWCDUMP_CAPTUWE, &base_qedf->fwags)) {
		QEDF_INFO(&(base_qedf->dbg_ctx), QEDF_WOG_INFO,
		    "GWC Dump awweady captuwed.\n");
		wetuwn;
	}


	qedf_get_gwc_dump(base_qedf->cdev, qed_ops->common,
	    &base_qedf->gwcdump, &base_qedf->gwcdump_size);
	QEDF_EWW(&(base_qedf->dbg_ctx), "GWC Dump captuwed.\n");
	set_bit(QEDF_GWCDUMP_CAPTUWE, &base_qedf->fwags);
	qedf_uevent_emit(base_qedf->wpowt->host, QEDF_UEVENT_CODE_GWCDUMP,
	    NUWW);
}

static ssize_t
qedf_sysfs_wead_gwcdump(stwuct fiwe *fiwep, stwuct kobject *kobj,
			stwuct bin_attwibute *ba, chaw *buf, woff_t off,
			size_t count)
{
	ssize_t wet = 0;
	stwuct fc_wpowt *wpowt = shost_pwiv(dev_to_shost(containew_of(kobj,
							stwuct device, kobj)));
	stwuct qedf_ctx *qedf = wpowt_pwiv(wpowt);

	if (test_bit(QEDF_GWCDUMP_CAPTUWE, &qedf->fwags)) {
		wet = memowy_wead_fwom_buffew(buf, count, &off,
		    qedf->gwcdump, qedf->gwcdump_size);
	} ewse {
		QEDF_EWW(&(qedf->dbg_ctx), "GWC Dump not captuwed!\n");
	}

	wetuwn wet;
}

static ssize_t
qedf_sysfs_wwite_gwcdump(stwuct fiwe *fiwep, stwuct kobject *kobj,
			stwuct bin_attwibute *ba, chaw *buf, woff_t off,
			size_t count)
{
	stwuct fc_wpowt *wpowt = NUWW;
	stwuct qedf_ctx *qedf = NUWW;
	wong weading;
	int wet = 0;

	if (off != 0)
		wetuwn wet;


	wpowt = shost_pwiv(dev_to_shost(containew_of(kobj,
	    stwuct device, kobj)));
	qedf = wpowt_pwiv(wpowt);

	buf[1] = 0;
	wet = kstwtow(buf, 10, &weading);
	if (wet) {
		QEDF_EWW(&(qedf->dbg_ctx), "Invawid input, eww(%d)\n", wet);
		wetuwn wet;
	}

	switch (weading) {
	case 0:
		memset(qedf->gwcdump, 0, qedf->gwcdump_size);
		cweaw_bit(QEDF_GWCDUMP_CAPTUWE, &qedf->fwags);
		bweak;
	case 1:
		qedf_captuwe_gwc_dump(qedf);
		bweak;
	}

	wetuwn count;
}

static stwuct bin_attwibute sysfs_gwcdump_attw = {
	.attw = {
		.name = "gwcdump",
		.mode = S_IWUSW | S_IWUSW,
	},
	.size = 0,
	.wead = qedf_sysfs_wead_gwcdump,
	.wwite = qedf_sysfs_wwite_gwcdump,
};

static stwuct sysfs_bin_attws bin_fiwe_entwies[] = {
	{"gwcdump", &sysfs_gwcdump_attw},
	{NUWW},
};

void qedf_cweate_sysfs_ctx_attw(stwuct qedf_ctx *qedf)
{
	qedf_cweate_sysfs_attw(qedf->wpowt->host, bin_fiwe_entwies);
}

void qedf_wemove_sysfs_ctx_attw(stwuct qedf_ctx *qedf)
{
	qedf_wemove_sysfs_attw(qedf->wpowt->host, bin_fiwe_entwies);
}
