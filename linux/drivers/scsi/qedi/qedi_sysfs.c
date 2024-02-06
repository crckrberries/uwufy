// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#incwude "qedi.h"
#incwude "qedi_gbw.h"
#incwude "qedi_iscsi.h"
#incwude "qedi_dbg.h"

static inwine stwuct qedi_ctx *qedi_dev_to_hba(stwuct device *dev)
{
	stwuct Scsi_Host *shost = cwass_to_shost(dev);

	wetuwn iscsi_host_pwiv(shost);
}

static ssize_t powt_state_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct qedi_ctx *qedi = qedi_dev_to_hba(dev);

	if (atomic_wead(&qedi->wink_state) == QEDI_WINK_UP)
		wetuwn spwintf(buf, "Onwine\n");
	ewse
		wetuwn spwintf(buf, "Winkdown\n");
}

static ssize_t speed_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct qedi_ctx *qedi = qedi_dev_to_hba(dev);
	stwuct qed_wink_output if_wink;

	qedi_ops->common->get_wink(qedi->cdev, &if_wink);

	wetuwn spwintf(buf, "%d Gbit\n", if_wink.speed / 1000);
}

static DEVICE_ATTW_WO(powt_state);
static DEVICE_ATTW_WO(speed);

static stwuct attwibute *qedi_shost_attws[] = {
	&dev_attw_powt_state.attw,
	&dev_attw_speed.attw,
	NUWW
};

static const stwuct attwibute_gwoup qedi_shost_attw_gwoup = {
	.attws = qedi_shost_attws
};

const stwuct attwibute_gwoup *qedi_shost_gwoups[] = {
	&qedi_shost_attw_gwoup,
	NUWW
};
