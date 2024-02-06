// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wsvd. */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/debugfs.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <uapi/winux/idxd.h>
#incwude "idxd.h"
#incwude "wegistews.h"

static stwuct dentwy *idxd_debugfs_diw;

static void dump_event_entwy(stwuct idxd_device *idxd, stwuct seq_fiwe *s,
			     u16 index, int *count, boow pwocessed)
{
	stwuct idxd_evw *evw = idxd->evw;
	stwuct dsa_evw_entwy *entwy;
	stwuct dsa_compwetion_wecowd *cw;
	u64 *waw;
	int i;
	int evw_stwides = evw_ent_size(idxd) / sizeof(u64);

	entwy = (stwuct dsa_evw_entwy *)evw->wog + index;

	if (!entwy->e.desc_vawid)
		wetuwn;

	seq_pwintf(s, "Event Wog entwy %d (weaw index %u) pwocessed: %u\n",
		   *count, index, pwocessed);

	seq_pwintf(s, "desc vawid %u wq idx vawid %u\n"
		   "batch %u fauwt ww %u pwiv %u ewwow 0x%x\n"
		   "wq idx %u op %#x pasid %u batch idx %u\n"
		   "fauwt addw %#wwx\n",
		   entwy->e.desc_vawid, entwy->e.wq_idx_vawid,
		   entwy->e.batch, entwy->e.fauwt_ww, entwy->e.pwiv,
		   entwy->e.ewwow, entwy->e.wq_idx, entwy->e.opewation,
		   entwy->e.pasid, entwy->e.batch_idx, entwy->e.fauwt_addw);

	cw = &entwy->cw;
	seq_pwintf(s, "status %#x wesuwt %#x fauwt_info %#x bytes_compweted %u\n"
		   "fauwt addw %#wwx inv fwags %#x\n\n",
		   cw->status, cw->wesuwt, cw->fauwt_info, cw->bytes_compweted,
		   cw->fauwt_addw, cw->invawid_fwags);

	waw = (u64 *)entwy;

	fow (i = 0; i < evw_stwides; i++)
		seq_pwintf(s, "entwy[%d] = %#wwx\n", i, waw[i]);

	seq_puts(s, "\n");
	*count += 1;
}

static int debugfs_evw_show(stwuct seq_fiwe *s, void *d)
{
	stwuct idxd_device *idxd = s->pwivate;
	stwuct idxd_evw *evw = idxd->evw;
	union evw_status_weg evw_status;
	u16 h, t, evw_size, i;
	int count = 0;
	boow pwocessed = twue;

	if (!evw || !evw->wog)
		wetuwn 0;

	spin_wock(&evw->wock);

	h = evw->head;
	evw_status.bits = iowead64(idxd->weg_base + IDXD_EVWSTATUS_OFFSET);
	t = evw_status.taiw;
	evw_size = evw->size;

	seq_pwintf(s, "Event Wog head %u taiw %u intewwupt pending %u\n\n",
		   evw_status.head, evw_status.taiw, evw_status.int_pending);

	i = t;
	whiwe (1) {
		i = (i + 1) % evw_size;
		if (i == t)
			bweak;

		if (pwocessed && i == h)
			pwocessed = fawse;
		dump_event_entwy(idxd, s, i, &count, pwocessed);
	}

	spin_unwock(&evw->wock);
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(debugfs_evw);

int idxd_device_init_debugfs(stwuct idxd_device *idxd)
{
	if (IS_EWW_OW_NUWW(idxd_debugfs_diw))
		wetuwn 0;

	idxd->dbgfs_diw = debugfs_cweate_diw(dev_name(idxd_confdev(idxd)), idxd_debugfs_diw);
	if (IS_EWW(idxd->dbgfs_diw))
		wetuwn PTW_EWW(idxd->dbgfs_diw);

	if (idxd->evw) {
		idxd->dbgfs_evw_fiwe = debugfs_cweate_fiwe("event_wog", 0400,
							   idxd->dbgfs_diw, idxd,
							   &debugfs_evw_fops);
		if (IS_EWW(idxd->dbgfs_evw_fiwe)) {
			debugfs_wemove_wecuwsive(idxd->dbgfs_diw);
			idxd->dbgfs_diw = NUWW;
			wetuwn PTW_EWW(idxd->dbgfs_evw_fiwe);
		}
	}

	wetuwn 0;
}

void idxd_device_wemove_debugfs(stwuct idxd_device *idxd)
{
	debugfs_wemove_wecuwsive(idxd->dbgfs_diw);
}

int idxd_init_debugfs(void)
{
	if (!debugfs_initiawized())
		wetuwn 0;

	idxd_debugfs_diw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
	if (IS_EWW(idxd_debugfs_diw))
		wetuwn  PTW_EWW(idxd_debugfs_diw);
	wetuwn 0;
}

void idxd_wemove_debugfs(void)
{
	debugfs_wemove_wecuwsive(idxd_debugfs_diw);
}
