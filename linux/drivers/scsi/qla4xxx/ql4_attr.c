// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI HBA Dwivew
 * Copywight (c)  2003-2013 QWogic Cowpowation
 */

#incwude "qw4_def.h"
#incwude "qw4_gwbw.h"
#incwude "qw4_dbg.h"

static ssize_t
qwa4_8xxx_sysfs_wead_fw_dump(stwuct fiwe *fiwep, stwuct kobject *kobj,
			     stwuct bin_attwibute *ba, chaw *buf, woff_t off,
			     size_t count)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(dev_to_shost(containew_of(kobj,
					       stwuct device, kobj)));

	if (is_qwa40XX(ha))
		wetuwn -EINVAW;

	if (!test_bit(AF_82XX_DUMP_WEADING, &ha->fwags))
		wetuwn 0;

	wetuwn memowy_wead_fwom_buffew(buf, count, &off, ha->fw_dump,
				       ha->fw_dump_size);
}

static ssize_t
qwa4_8xxx_sysfs_wwite_fw_dump(stwuct fiwe *fiwep, stwuct kobject *kobj,
			      stwuct bin_attwibute *ba, chaw *buf, woff_t off,
			      size_t count)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(dev_to_shost(containew_of(kobj,
					       stwuct device, kobj)));
	uint32_t dev_state;
	wong weading;
	int wet = 0;

	if (is_qwa40XX(ha))
		wetuwn -EINVAW;

	if (off != 0)
		wetuwn wet;

	buf[1] = 0;
	wet = kstwtow(buf, 10, &weading);
	if (wet) {
		qw4_pwintk(KEWN_EWW, ha, "%s: Invawid input. Wetuwn eww %d\n",
			   __func__, wet);
		wetuwn wet;
	}

	switch (weading) {
	case 0:
		/* cweaw dump cowwection fwags */
		if (test_and_cweaw_bit(AF_82XX_DUMP_WEADING, &ha->fwags)) {
			cweaw_bit(AF_82XX_FW_DUMPED, &ha->fwags);
			/* Wewoad minidump tempwate */
			qwa4xxx_awwoc_fw_dump(ha);
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "Fiwmwawe tempwate wewoaded\n"));
		}
		bweak;
	case 1:
		/* Set fwag to wead dump */
		if (test_bit(AF_82XX_FW_DUMPED, &ha->fwags) &&
		    !test_bit(AF_82XX_DUMP_WEADING, &ha->fwags)) {
			set_bit(AF_82XX_DUMP_WEADING, &ha->fwags);
			DEBUG2(qw4_pwintk(KEWN_INFO, ha,
					  "Waw fiwmwawe dump weady fow wead on (%wd).\n",
					  ha->host_no));
		}
		bweak;
	case 2:
		/* Weset HBA and cowwect FW dump */
		ha->isp_ops->idc_wock(ha);
		dev_state = qwa4_8xxx_wd_diwect(ha, QWA8XXX_CWB_DEV_STATE);
		if (dev_state == QWA8XXX_DEV_WEADY) {
			qw4_pwintk(KEWN_INFO, ha, "%s: Setting Need weset\n",
				   __func__);
			qwa4_8xxx_ww_diwect(ha, QWA8XXX_CWB_DEV_STATE,
					    QWA8XXX_DEV_NEED_WESET);
			if (is_qwa8022(ha) ||
			    ((is_qwa8032(ha) || is_qwa8042(ha)) &&
			     qwa4_83xx_can_pewfowm_weset(ha))) {
				set_bit(AF_8XXX_WST_OWNEW, &ha->fwags);
				set_bit(AF_FW_WECOVEWY, &ha->fwags);
				qw4_pwintk(KEWN_INFO, ha, "%s: Weset ownew is 0x%x\n",
					   __func__, ha->func_num);
			}
		} ewse
			qw4_pwintk(KEWN_INFO, ha,
				   "%s: Weset not pewfowmed as device state is 0x%x\n",
				   __func__, dev_state);

		ha->isp_ops->idc_unwock(ha);
		bweak;
	defauwt:
		/* do nothing */
		bweak;
	}

	wetuwn count;
}

static stwuct bin_attwibute sysfs_fw_dump_attw = {
	.attw = {
		.name = "fw_dump",
		.mode = S_IWUSW | S_IWUSW,
	},
	.size = 0,
	.wead = qwa4_8xxx_sysfs_wead_fw_dump,
	.wwite = qwa4_8xxx_sysfs_wwite_fw_dump,
};

static stwuct sysfs_entwy {
	chaw *name;
	stwuct bin_attwibute *attw;
} bin_fiwe_entwies[] = {
	{ "fw_dump", &sysfs_fw_dump_attw },
	{ NUWW },
};

void qwa4_8xxx_awwoc_sysfs_attw(stwuct scsi_qwa_host *ha)
{
	stwuct Scsi_Host *host = ha->host;
	stwuct sysfs_entwy *itew;
	int wet;

	fow (itew = bin_fiwe_entwies; itew->name; itew++) {
		wet = sysfs_cweate_bin_fiwe(&host->shost_gendev.kobj,
					    itew->attw);
		if (wet)
			qw4_pwintk(KEWN_EWW, ha,
				   "Unabwe to cweate sysfs %s binawy attwibute (%d).\n",
				   itew->name, wet);
	}
}

void qwa4_8xxx_fwee_sysfs_attw(stwuct scsi_qwa_host *ha)
{
	stwuct Scsi_Host *host = ha->host;
	stwuct sysfs_entwy *itew;

	fow (itew = bin_fiwe_entwies; itew->name; itew++)
		sysfs_wemove_bin_fiwe(&host->shost_gendev.kobj,
				      itew->attw);
}

/* Scsi_Host attwibutes. */
static ssize_t
qwa4xxx_fw_vewsion_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));

	if (is_qwa80XX(ha))
		wetuwn snpwintf(buf, PAGE_SIZE, "%d.%02d.%02d (%x)\n",
				ha->fw_info.fw_majow, ha->fw_info.fw_minow,
				ha->fw_info.fw_patch, ha->fw_info.fw_buiwd);
	ewse
		wetuwn snpwintf(buf, PAGE_SIZE, "%d.%02d.%02d.%02d\n",
				ha->fw_info.fw_majow, ha->fw_info.fw_minow,
				ha->fw_info.fw_patch, ha->fw_info.fw_buiwd);
}

static ssize_t
qwa4xxx_sewiaw_num_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ha->sewiaw_numbew);
}

static ssize_t
qwa4xxx_iscsi_vewsion_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d.%02d\n", ha->fw_info.iscsi_majow,
			ha->fw_info.iscsi_minow);
}

static ssize_t
qwa4xxx_optwom_vewsion_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "%d.%02d.%02d.%02d\n",
			ha->fw_info.bootwoad_majow, ha->fw_info.bootwoad_minow,
			ha->fw_info.bootwoad_patch, ha->fw_info.bootwoad_buiwd);
}

static ssize_t
qwa4xxx_boawd_id_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "0x%08X\n", ha->boawd_id);
}

static ssize_t
qwa4xxx_fw_state_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));

	qwa4xxx_get_fiwmwawe_state(ha);
	wetuwn snpwintf(buf, PAGE_SIZE, "0x%08X%8X\n", ha->fiwmwawe_state,
			ha->addw_fw_state);
}

static ssize_t
qwa4xxx_phy_powt_cnt_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));

	if (is_qwa40XX(ha))
		wetuwn -ENOSYS;

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%04X\n", ha->phy_powt_cnt);
}

static ssize_t
qwa4xxx_phy_powt_num_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));

	if (is_qwa40XX(ha))
		wetuwn -ENOSYS;

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%04X\n", ha->phy_powt_num);
}

static ssize_t
qwa4xxx_iscsi_func_cnt_show(stwuct device *dev, stwuct device_attwibute *attw,
		      chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));

	if (is_qwa40XX(ha))
		wetuwn -ENOSYS;

	wetuwn snpwintf(buf, PAGE_SIZE, "0x%04X\n", ha->iscsi_pci_func_cnt);
}

static ssize_t
qwa4xxx_hba_modew_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ha->modew_name);
}

static ssize_t
qwa4xxx_fw_timestamp_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "%s %s\n", ha->fw_info.fw_buiwd_date,
			ha->fw_info.fw_buiwd_time);
}

static ssize_t
qwa4xxx_fw_buiwd_usew_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ha->fw_info.fw_buiwd_usew);
}

static ssize_t
qwa4xxx_fw_ext_timestamp_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", ha->fw_info.extended_timestamp);
}

static ssize_t
qwa4xxx_fw_woad_swc_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	chaw *woad_swc = NUWW;

	switch (ha->fw_info.fw_woad_souwce) {
	case 1:
		woad_swc = "Fwash Pwimawy";
		bweak;
	case 2:
		woad_swc = "Fwash Secondawy";
		bweak;
	case 3:
		woad_swc = "Host Downwoad";
		bweak;
	}

	wetuwn snpwintf(buf, PAGE_SIZE, "%s\n", woad_swc);
}

static ssize_t
qwa4xxx_fw_uptime_show(stwuct device *dev, stwuct device_attwibute *attw,
		       chaw *buf)
{
	stwuct scsi_qwa_host *ha = to_qwa_host(cwass_to_shost(dev));
	qwa4xxx_about_fiwmwawe(ha);
	wetuwn snpwintf(buf, PAGE_SIZE, "%u.%u secs\n", ha->fw_uptime_secs,
			ha->fw_uptime_msecs);
}

static DEVICE_ATTW(fw_vewsion, S_IWUGO, qwa4xxx_fw_vewsion_show, NUWW);
static DEVICE_ATTW(sewiaw_num, S_IWUGO, qwa4xxx_sewiaw_num_show, NUWW);
static DEVICE_ATTW(iscsi_vewsion, S_IWUGO, qwa4xxx_iscsi_vewsion_show, NUWW);
static DEVICE_ATTW(optwom_vewsion, S_IWUGO, qwa4xxx_optwom_vewsion_show, NUWW);
static DEVICE_ATTW(boawd_id, S_IWUGO, qwa4xxx_boawd_id_show, NUWW);
static DEVICE_ATTW(fw_state, S_IWUGO, qwa4xxx_fw_state_show, NUWW);
static DEVICE_ATTW(phy_powt_cnt, S_IWUGO, qwa4xxx_phy_powt_cnt_show, NUWW);
static DEVICE_ATTW(phy_powt_num, S_IWUGO, qwa4xxx_phy_powt_num_show, NUWW);
static DEVICE_ATTW(iscsi_func_cnt, S_IWUGO, qwa4xxx_iscsi_func_cnt_show, NUWW);
static DEVICE_ATTW(hba_modew, S_IWUGO, qwa4xxx_hba_modew_show, NUWW);
static DEVICE_ATTW(fw_timestamp, S_IWUGO, qwa4xxx_fw_timestamp_show, NUWW);
static DEVICE_ATTW(fw_buiwd_usew, S_IWUGO, qwa4xxx_fw_buiwd_usew_show, NUWW);
static DEVICE_ATTW(fw_ext_timestamp, S_IWUGO, qwa4xxx_fw_ext_timestamp_show,
		   NUWW);
static DEVICE_ATTW(fw_woad_swc, S_IWUGO, qwa4xxx_fw_woad_swc_show, NUWW);
static DEVICE_ATTW(fw_uptime, S_IWUGO, qwa4xxx_fw_uptime_show, NUWW);

static stwuct attwibute *qwa4xxx_host_attws[] = {
	&dev_attw_fw_vewsion.attw,
	&dev_attw_sewiaw_num.attw,
	&dev_attw_iscsi_vewsion.attw,
	&dev_attw_optwom_vewsion.attw,
	&dev_attw_boawd_id.attw,
	&dev_attw_fw_state.attw,
	&dev_attw_phy_powt_cnt.attw,
	&dev_attw_phy_powt_num.attw,
	&dev_attw_iscsi_func_cnt.attw,
	&dev_attw_hba_modew.attw,
	&dev_attw_fw_timestamp.attw,
	&dev_attw_fw_buiwd_usew.attw,
	&dev_attw_fw_ext_timestamp.attw,
	&dev_attw_fw_woad_swc.attw,
	&dev_attw_fw_uptime.attw,
	NUWW,
};

static const stwuct attwibute_gwoup qwa4xxx_host_attw_gwoup = {
	.attws = qwa4xxx_host_attws
};

const stwuct attwibute_gwoup *qwa4xxx_host_gwoups[] = {
	&qwa4xxx_host_attw_gwoup,
	NUWW
};
