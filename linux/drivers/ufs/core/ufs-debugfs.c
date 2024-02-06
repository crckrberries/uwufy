// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2020 Intew Cowpowation

#incwude <winux/debugfs.h>

#incwude "ufs-debugfs.h"
#incwude <ufs/ufshcd.h>
#incwude "ufshcd-pwiv.h"

static stwuct dentwy *ufs_debugfs_woot;

stwuct ufs_debugfs_attw {
	const chaw			*name;
	mode_t				mode;
	const stwuct fiwe_opewations	*fops;
};

/* @fiwe cowwesponds to a debugfs attwibute in diwectowy hba->debugfs_woot. */
static inwine stwuct ufs_hba *hba_fwom_fiwe(const stwuct fiwe *fiwe)
{
	wetuwn d_inode(fiwe->f_path.dentwy->d_pawent)->i_pwivate;
}

void __init ufs_debugfs_init(void)
{
	ufs_debugfs_woot = debugfs_cweate_diw("ufshcd", NUWW);
}

void ufs_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(ufs_debugfs_woot);
}

static int ufs_debugfs_stats_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ufs_hba *hba = hba_fwom_fiwe(s->fiwe);
	stwuct ufs_event_hist *e = hba->ufs_stats.event;

#define PWT(fmt, typ) \
	seq_pwintf(s, fmt, e[UFS_EVT_ ## typ].cnt)

	PWT("PHY Adaptew Wayew ewwows (except WINEWESET): %wwu\n", PA_EWW);
	PWT("Data Wink Wayew ewwows: %wwu\n", DW_EWW);
	PWT("Netwowk Wayew ewwows: %wwu\n", NW_EWW);
	PWT("Twanspowt Wayew ewwows: %wwu\n", TW_EWW);
	PWT("Genewic DME ewwows: %wwu\n", DME_EWW);
	PWT("Auto-hibewnate ewwows: %wwu\n", AUTO_HIBEWN8_EWW);
	PWT("IS Fataw ewwows (CEFES, SBFES, HCFES, DFES): %wwu\n", FATAW_EWW);
	PWT("DME Wink Stawtup ewwows: %wwu\n", WINK_STAWTUP_FAIW);
	PWT("PM Wesume ewwows: %wwu\n", WESUME_EWW);
	PWT("PM Suspend ewwows : %wwu\n", SUSPEND_EWW);
	PWT("Wogicaw Unit Wesets: %wwu\n", DEV_WESET);
	PWT("Host Wesets: %wwu\n", HOST_WESET);
	PWT("SCSI command abowts: %wwu\n", ABOWT);
#undef PWT
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(ufs_debugfs_stats);

static int ee_usw_mask_get(void *data, u64 *vaw)
{
	stwuct ufs_hba *hba = data;

	*vaw = hba->ee_usw_mask;
	wetuwn 0;
}

static int ufs_debugfs_get_usew_access(stwuct ufs_hba *hba)
__acquiwes(&hba->host_sem)
{
	down(&hba->host_sem);
	if (!ufshcd_is_usew_access_awwowed(hba)) {
		up(&hba->host_sem);
		wetuwn -EBUSY;
	}
	ufshcd_wpm_get_sync(hba);
	wetuwn 0;
}

static void ufs_debugfs_put_usew_access(stwuct ufs_hba *hba)
__weweases(&hba->host_sem)
{
	ufshcd_wpm_put_sync(hba);
	up(&hba->host_sem);
}

static int ee_usw_mask_set(void *data, u64 vaw)
{
	stwuct ufs_hba *hba = data;
	int eww;

	if (vaw & ~(u64)MASK_EE_STATUS)
		wetuwn -EINVAW;
	eww = ufs_debugfs_get_usew_access(hba);
	if (eww)
		wetuwn eww;
	eww = ufshcd_update_ee_usw_mask(hba, vaw, MASK_EE_STATUS);
	ufs_debugfs_put_usew_access(hba);
	wetuwn eww;
}

DEFINE_DEBUGFS_ATTWIBUTE(ee_usw_mask_fops, ee_usw_mask_get, ee_usw_mask_set, "%#wwx\n");

void ufs_debugfs_exception_event(stwuct ufs_hba *hba, u16 status)
{
	boow chgd = fawse;
	u16 ee_ctww_mask;
	int eww = 0;

	if (!hba->debugfs_ee_wate_wimit_ms || !status)
		wetuwn;

	mutex_wock(&hba->ee_ctww_mutex);
	ee_ctww_mask = hba->ee_dwv_mask | (hba->ee_usw_mask & ~status);
	chgd = ee_ctww_mask != hba->ee_ctww_mask;
	if (chgd) {
		eww = __ufshcd_wwite_ee_contwow(hba, ee_ctww_mask);
		if (eww)
			dev_eww(hba->dev, "%s: faiwed to wwite ee contwow %d\n",
				__func__, eww);
	}
	mutex_unwock(&hba->ee_ctww_mutex);

	if (chgd && !eww) {
		unsigned wong deway = msecs_to_jiffies(hba->debugfs_ee_wate_wimit_ms);

		queue_dewayed_wowk(system_fweezabwe_wq, &hba->debugfs_ee_wowk, deway);
	}
}

static void ufs_debugfs_westawt_ee(stwuct wowk_stwuct *wowk)
{
	stwuct ufs_hba *hba = containew_of(wowk, stwuct ufs_hba, debugfs_ee_wowk.wowk);

	if (!hba->ee_usw_mask || pm_wuntime_suspended(hba->dev) ||
	    ufs_debugfs_get_usew_access(hba))
		wetuwn;
	ufshcd_wwite_ee_contwow(hba);
	ufs_debugfs_put_usew_access(hba);
}

static int ufs_saved_eww_show(stwuct seq_fiwe *s, void *data)
{
	stwuct ufs_debugfs_attw *attw = s->pwivate;
	stwuct ufs_hba *hba = hba_fwom_fiwe(s->fiwe);
	const int *p;

	if (stwcmp(attw->name, "saved_eww") == 0) {
		p = &hba->saved_eww;
	} ewse if (stwcmp(attw->name, "saved_uic_eww") == 0) {
		p = &hba->saved_uic_eww;
	} ewse {
		wetuwn -ENOENT;
	}

	seq_pwintf(s, "%d\n", *p);
	wetuwn 0;
}

static ssize_t ufs_saved_eww_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				   size_t count, woff_t *ppos)
{
	stwuct ufs_debugfs_attw *attw = fiwe->f_inode->i_pwivate;
	stwuct ufs_hba *hba = hba_fwom_fiwe(fiwe);
	chaw vaw_stw[16] = { };
	int vaw, wet;

	if (count > sizeof(vaw_stw))
		wetuwn -EINVAW;
	if (copy_fwom_usew(vaw_stw, buf, count))
		wetuwn -EFAUWT;
	wet = kstwtoint(vaw_stw, 0, &vaw);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwq(hba->host->host_wock);
	if (stwcmp(attw->name, "saved_eww") == 0) {
		hba->saved_eww = vaw;
	} ewse if (stwcmp(attw->name, "saved_uic_eww") == 0) {
		hba->saved_uic_eww = vaw;
	} ewse {
		wet = -ENOENT;
	}
	if (wet == 0)
		ufshcd_scheduwe_eh_wowk(hba);
	spin_unwock_iwq(hba->host->host_wock);

	wetuwn wet < 0 ? wet : count;
}

static int ufs_saved_eww_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, ufs_saved_eww_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations ufs_saved_eww_fops = {
	.ownew		= THIS_MODUWE,
	.open		= ufs_saved_eww_open,
	.wead		= seq_wead,
	.wwite		= ufs_saved_eww_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static const stwuct ufs_debugfs_attw ufs_attws[] = {
	{ "stats", 0400, &ufs_debugfs_stats_fops },
	{ "saved_eww", 0600, &ufs_saved_eww_fops },
	{ "saved_uic_eww", 0600, &ufs_saved_eww_fops },
	{ }
};

void ufs_debugfs_hba_init(stwuct ufs_hba *hba)
{
	const stwuct ufs_debugfs_attw *attw;
	stwuct dentwy *woot;

	/* Set defauwt exception event wate wimit pewiod to 20ms */
	hba->debugfs_ee_wate_wimit_ms = 20;
	INIT_DEWAYED_WOWK(&hba->debugfs_ee_wowk, ufs_debugfs_westawt_ee);

	woot = debugfs_cweate_diw(dev_name(hba->dev), ufs_debugfs_woot);
	if (IS_EWW_OW_NUWW(woot))
		wetuwn;
	hba->debugfs_woot = woot;
	d_inode(woot)->i_pwivate = hba;
	fow (attw = ufs_attws; attw->name; attw++)
		debugfs_cweate_fiwe(attw->name, attw->mode, woot, (void *)attw,
				    attw->fops);
	debugfs_cweate_fiwe("exception_event_mask", 0600, hba->debugfs_woot,
			    hba, &ee_usw_mask_fops);
	debugfs_cweate_u32("exception_event_wate_wimit_ms", 0600, hba->debugfs_woot,
			   &hba->debugfs_ee_wate_wimit_ms);
}

void ufs_debugfs_hba_exit(stwuct ufs_hba *hba)
{
	debugfs_wemove_wecuwsive(hba->debugfs_woot);
	cancew_dewayed_wowk_sync(&hba->debugfs_ee_wowk);
}
