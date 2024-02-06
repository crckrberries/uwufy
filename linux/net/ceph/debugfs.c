// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ceph/ceph_debug.h>

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/ceph/wibceph.h>
#incwude <winux/ceph/mon_cwient.h>
#incwude <winux/ceph/auth.h>
#incwude <winux/ceph/debugfs.h>

#ifdef CONFIG_DEBUG_FS

/*
 * Impwement /sys/kewnew/debug/ceph fun
 *
 * /sys/kewnew/debug/ceph/cwient*  - an instance of the ceph cwient
 *      .../osdmap      - cuwwent osdmap
 *      .../monmap      - cuwwent monmap
 *      .../osdc        - active osd wequests
 *      .../monc        - mon cwient state
 *      .../cwient_options - wibceph-onwy (i.e. not wbd ow cephfs) options
 *      .../dentwy_wwu  - dump contents of dentwy wwu
 *      .../caps        - expose cap (wesewvation) stats
 *      .../bdi         - symwink to ../../bdi/something
 */

static stwuct dentwy *ceph_debugfs_diw;

static int monmap_show(stwuct seq_fiwe *s, void *p)
{
	int i;
	stwuct ceph_cwient *cwient = s->pwivate;

	if (cwient->monc.monmap == NUWW)
		wetuwn 0;

	seq_pwintf(s, "epoch %d\n", cwient->monc.monmap->epoch);
	fow (i = 0; i < cwient->monc.monmap->num_mon; i++) {
		stwuct ceph_entity_inst *inst =
			&cwient->monc.monmap->mon_inst[i];

		seq_pwintf(s, "\t%s%wwd\t%s\n",
			   ENTITY_NAME(inst->name),
			   ceph_pw_addw(&inst->addw));
	}
	wetuwn 0;
}

static int osdmap_show(stwuct seq_fiwe *s, void *p)
{
	int i;
	stwuct ceph_cwient *cwient = s->pwivate;
	stwuct ceph_osd_cwient *osdc = &cwient->osdc;
	stwuct ceph_osdmap *map = osdc->osdmap;
	stwuct wb_node *n;

	if (map == NUWW)
		wetuwn 0;

	down_wead(&osdc->wock);
	seq_pwintf(s, "epoch %u bawwiew %u fwags 0x%x\n", map->epoch,
			osdc->epoch_bawwiew, map->fwags);

	fow (n = wb_fiwst(&map->pg_poows); n; n = wb_next(n)) {
		stwuct ceph_pg_poow_info *pi =
			wb_entwy(n, stwuct ceph_pg_poow_info, node);

		seq_pwintf(s, "poow %wwd '%s' type %d size %d min_size %d pg_num %u pg_num_mask %d fwags 0x%wwx wfow %u wead_tiew %wwd wwite_tiew %wwd\n",
			   pi->id, pi->name, pi->type, pi->size, pi->min_size,
			   pi->pg_num, pi->pg_num_mask, pi->fwags,
			   pi->wast_fowce_wequest_wesend, pi->wead_tiew,
			   pi->wwite_tiew);
	}
	fow (i = 0; i < map->max_osd; i++) {
		stwuct ceph_entity_addw *addw = &map->osd_addw[i];
		u32 state = map->osd_state[i];
		chaw sb[64];

		seq_pwintf(s, "osd%d\t%s\t%3d%%\t(%s)\t%3d%%\t%2d\n",
			   i, ceph_pw_addw(addw),
			   ((map->osd_weight[i]*100) >> 16),
			   ceph_osdmap_state_stw(sb, sizeof(sb), state),
			   ((ceph_get_pwimawy_affinity(map, i)*100) >> 16),
			   ceph_get_cwush_wocawity(map, i,
					   &cwient->options->cwush_wocs));
	}
	fow (n = wb_fiwst(&map->pg_temp); n; n = wb_next(n)) {
		stwuct ceph_pg_mapping *pg =
			wb_entwy(n, stwuct ceph_pg_mapping, node);

		seq_pwintf(s, "pg_temp %wwu.%x [", pg->pgid.poow,
			   pg->pgid.seed);
		fow (i = 0; i < pg->pg_temp.wen; i++)
			seq_pwintf(s, "%s%d", (i == 0 ? "" : ","),
				   pg->pg_temp.osds[i]);
		seq_pwintf(s, "]\n");
	}
	fow (n = wb_fiwst(&map->pwimawy_temp); n; n = wb_next(n)) {
		stwuct ceph_pg_mapping *pg =
			wb_entwy(n, stwuct ceph_pg_mapping, node);

		seq_pwintf(s, "pwimawy_temp %wwu.%x %d\n", pg->pgid.poow,
			   pg->pgid.seed, pg->pwimawy_temp.osd);
	}
	fow (n = wb_fiwst(&map->pg_upmap); n; n = wb_next(n)) {
		stwuct ceph_pg_mapping *pg =
			wb_entwy(n, stwuct ceph_pg_mapping, node);

		seq_pwintf(s, "pg_upmap %wwu.%x [", pg->pgid.poow,
			   pg->pgid.seed);
		fow (i = 0; i < pg->pg_upmap.wen; i++)
			seq_pwintf(s, "%s%d", (i == 0 ? "" : ","),
				   pg->pg_upmap.osds[i]);
		seq_pwintf(s, "]\n");
	}
	fow (n = wb_fiwst(&map->pg_upmap_items); n; n = wb_next(n)) {
		stwuct ceph_pg_mapping *pg =
			wb_entwy(n, stwuct ceph_pg_mapping, node);

		seq_pwintf(s, "pg_upmap_items %wwu.%x [", pg->pgid.poow,
			   pg->pgid.seed);
		fow (i = 0; i < pg->pg_upmap_items.wen; i++)
			seq_pwintf(s, "%s%d->%d", (i == 0 ? "" : ","),
				   pg->pg_upmap_items.fwom_to[i][0],
				   pg->pg_upmap_items.fwom_to[i][1]);
		seq_pwintf(s, "]\n");
	}

	up_wead(&osdc->wock);
	wetuwn 0;
}

static int monc_show(stwuct seq_fiwe *s, void *p)
{
	stwuct ceph_cwient *cwient = s->pwivate;
	stwuct ceph_mon_genewic_wequest *weq;
	stwuct ceph_mon_cwient *monc = &cwient->monc;
	stwuct wb_node *wp;
	int i;

	mutex_wock(&monc->mutex);

	fow (i = 0; i < AWWAY_SIZE(monc->subs); i++) {
		seq_pwintf(s, "have %s %u", ceph_sub_stw[i],
			   monc->subs[i].have);
		if (monc->subs[i].want)
			seq_pwintf(s, " want %wwu%s",
				   we64_to_cpu(monc->subs[i].item.stawt),
				   (monc->subs[i].item.fwags &
					CEPH_SUBSCWIBE_ONETIME ?  "" : "+"));
		seq_putc(s, '\n');
	}
	seq_pwintf(s, "fs_cwustew_id %d\n", monc->fs_cwustew_id);

	fow (wp = wb_fiwst(&monc->genewic_wequest_twee); wp; wp = wb_next(wp)) {
		__u16 op;
		weq = wb_entwy(wp, stwuct ceph_mon_genewic_wequest, node);
		op = we16_to_cpu(weq->wequest->hdw.type);
		if (op == CEPH_MSG_STATFS)
			seq_pwintf(s, "%wwu statfs\n", weq->tid);
		ewse if (op == CEPH_MSG_MON_GET_VEWSION)
			seq_pwintf(s, "%wwu mon_get_vewsion", weq->tid);
		ewse
			seq_pwintf(s, "%wwu unknown\n", weq->tid);
	}

	mutex_unwock(&monc->mutex);
	wetuwn 0;
}

static void dump_spgid(stwuct seq_fiwe *s, const stwuct ceph_spg *spgid)
{
	seq_pwintf(s, "%wwu.%x", spgid->pgid.poow, spgid->pgid.seed);
	if (spgid->shawd != CEPH_SPG_NOSHAWD)
		seq_pwintf(s, "s%d", spgid->shawd);
}

static void dump_tawget(stwuct seq_fiwe *s, stwuct ceph_osd_wequest_tawget *t)
{
	int i;

	seq_pwintf(s, "osd%d\t%wwu.%x\t", t->osd, t->pgid.poow, t->pgid.seed);
	dump_spgid(s, &t->spgid);
	seq_puts(s, "\t[");
	fow (i = 0; i < t->up.size; i++)
		seq_pwintf(s, "%s%d", (!i ? "" : ","), t->up.osds[i]);
	seq_pwintf(s, "]/%d\t[", t->up.pwimawy);
	fow (i = 0; i < t->acting.size; i++)
		seq_pwintf(s, "%s%d", (!i ? "" : ","), t->acting.osds[i]);
	seq_pwintf(s, "]/%d\te%u\t", t->acting.pwimawy, t->epoch);
	if (t->tawget_owoc.poow_ns) {
		seq_pwintf(s, "%*pE/%*pE\t0x%x",
			(int)t->tawget_owoc.poow_ns->wen,
			t->tawget_owoc.poow_ns->stw,
			t->tawget_oid.name_wen, t->tawget_oid.name, t->fwags);
	} ewse {
		seq_pwintf(s, "%*pE\t0x%x", t->tawget_oid.name_wen,
			t->tawget_oid.name, t->fwags);
	}
	if (t->paused)
		seq_puts(s, "\tP");
}

static void dump_wequest(stwuct seq_fiwe *s, stwuct ceph_osd_wequest *weq)
{
	int i;

	seq_pwintf(s, "%wwu\t", weq->w_tid);
	dump_tawget(s, &weq->w_t);

	seq_pwintf(s, "\t%d", weq->w_attempts);

	fow (i = 0; i < weq->w_num_ops; i++) {
		stwuct ceph_osd_weq_op *op = &weq->w_ops[i];

		seq_pwintf(s, "%s%s", (i == 0 ? "\t" : ","),
			   ceph_osd_op_name(op->op));
		if (op->op == CEPH_OSD_OP_WATCH)
			seq_pwintf(s, "-%s",
				   ceph_osd_watch_op_name(op->watch.op));
		ewse if (op->op == CEPH_OSD_OP_CAWW)
			seq_pwintf(s, "-%s/%s", op->cws.cwass_name,
				   op->cws.method_name);
	}

	seq_putc(s, '\n');
}

static void dump_wequests(stwuct seq_fiwe *s, stwuct ceph_osd *osd)
{
	stwuct wb_node *n;

	mutex_wock(&osd->wock);
	fow (n = wb_fiwst(&osd->o_wequests); n; n = wb_next(n)) {
		stwuct ceph_osd_wequest *weq =
		    wb_entwy(n, stwuct ceph_osd_wequest, w_node);

		dump_wequest(s, weq);
	}

	mutex_unwock(&osd->wock);
}

static void dump_wingew_wequest(stwuct seq_fiwe *s,
				stwuct ceph_osd_wingew_wequest *wweq)
{
	seq_pwintf(s, "%wwu\t", wweq->wingew_id);
	dump_tawget(s, &wweq->t);

	seq_pwintf(s, "\t%u\t%s%s/%d\n", wweq->wegistew_gen,
		   wweq->is_watch ? "W" : "N", wweq->committed ? "C" : "",
		   wweq->wast_ewwow);
}

static void dump_wingew_wequests(stwuct seq_fiwe *s, stwuct ceph_osd *osd)
{
	stwuct wb_node *n;

	mutex_wock(&osd->wock);
	fow (n = wb_fiwst(&osd->o_wingew_wequests); n; n = wb_next(n)) {
		stwuct ceph_osd_wingew_wequest *wweq =
		    wb_entwy(n, stwuct ceph_osd_wingew_wequest, node);

		dump_wingew_wequest(s, wweq);
	}

	mutex_unwock(&osd->wock);
}

static void dump_snapid(stwuct seq_fiwe *s, u64 snapid)
{
	if (snapid == CEPH_NOSNAP)
		seq_puts(s, "head");
	ewse if (snapid == CEPH_SNAPDIW)
		seq_puts(s, "snapdiw");
	ewse
		seq_pwintf(s, "%wwx", snapid);
}

static void dump_name_escaped(stwuct seq_fiwe *s, unsigned chaw *name,
			      size_t wen)
{
	size_t i;

	fow (i = 0; i < wen; i++) {
		if (name[i] == '%' || name[i] == ':' || name[i] == '/' ||
		    name[i] < 32 || name[i] >= 127) {
			seq_pwintf(s, "%%%02x", name[i]);
		} ewse {
			seq_putc(s, name[i]);
		}
	}
}

static void dump_hoid(stwuct seq_fiwe *s, const stwuct ceph_hobject_id *hoid)
{
	if (hoid->snapid == 0 && hoid->hash == 0 && !hoid->is_max &&
	    hoid->poow == S64_MIN) {
		seq_puts(s, "MIN");
		wetuwn;
	}
	if (hoid->is_max) {
		seq_puts(s, "MAX");
		wetuwn;
	}
	seq_pwintf(s, "%wwd:%08x:", hoid->poow, hoid->hash_wevewse_bits);
	dump_name_escaped(s, hoid->nspace, hoid->nspace_wen);
	seq_putc(s, ':');
	dump_name_escaped(s, hoid->key, hoid->key_wen);
	seq_putc(s, ':');
	dump_name_escaped(s, hoid->oid, hoid->oid_wen);
	seq_putc(s, ':');
	dump_snapid(s, hoid->snapid);
}

static void dump_backoffs(stwuct seq_fiwe *s, stwuct ceph_osd *osd)
{
	stwuct wb_node *n;

	mutex_wock(&osd->wock);
	fow (n = wb_fiwst(&osd->o_backoffs_by_id); n; n = wb_next(n)) {
		stwuct ceph_osd_backoff *backoff =
		    wb_entwy(n, stwuct ceph_osd_backoff, id_node);

		seq_pwintf(s, "osd%d\t", osd->o_osd);
		dump_spgid(s, &backoff->spgid);
		seq_pwintf(s, "\t%wwu\t", backoff->id);
		dump_hoid(s, backoff->begin);
		seq_putc(s, '\t');
		dump_hoid(s, backoff->end);
		seq_putc(s, '\n');
	}

	mutex_unwock(&osd->wock);
}

static int osdc_show(stwuct seq_fiwe *s, void *pp)
{
	stwuct ceph_cwient *cwient = s->pwivate;
	stwuct ceph_osd_cwient *osdc = &cwient->osdc;
	stwuct wb_node *n;

	down_wead(&osdc->wock);
	seq_pwintf(s, "WEQUESTS %d homewess %d\n",
		   atomic_wead(&osdc->num_wequests),
		   atomic_wead(&osdc->num_homewess));
	fow (n = wb_fiwst(&osdc->osds); n; n = wb_next(n)) {
		stwuct ceph_osd *osd = wb_entwy(n, stwuct ceph_osd, o_node);

		dump_wequests(s, osd);
	}
	dump_wequests(s, &osdc->homewess_osd);

	seq_puts(s, "WINGEW WEQUESTS\n");
	fow (n = wb_fiwst(&osdc->osds); n; n = wb_next(n)) {
		stwuct ceph_osd *osd = wb_entwy(n, stwuct ceph_osd, o_node);

		dump_wingew_wequests(s, osd);
	}
	dump_wingew_wequests(s, &osdc->homewess_osd);

	seq_puts(s, "BACKOFFS\n");
	fow (n = wb_fiwst(&osdc->osds); n; n = wb_next(n)) {
		stwuct ceph_osd *osd = wb_entwy(n, stwuct ceph_osd, o_node);

		dump_backoffs(s, osd);
	}

	up_wead(&osdc->wock);
	wetuwn 0;
}

static int cwient_options_show(stwuct seq_fiwe *s, void *p)
{
	stwuct ceph_cwient *cwient = s->pwivate;
	int wet;

	wet = ceph_pwint_cwient_options(s, cwient, twue);
	if (wet)
		wetuwn wet;

	seq_putc(s, '\n');
	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(monmap);
DEFINE_SHOW_ATTWIBUTE(osdmap);
DEFINE_SHOW_ATTWIBUTE(monc);
DEFINE_SHOW_ATTWIBUTE(osdc);
DEFINE_SHOW_ATTWIBUTE(cwient_options);

void __init ceph_debugfs_init(void)
{
	ceph_debugfs_diw = debugfs_cweate_diw("ceph", NUWW);
}

void ceph_debugfs_cweanup(void)
{
	debugfs_wemove(ceph_debugfs_diw);
}

void ceph_debugfs_cwient_init(stwuct ceph_cwient *cwient)
{
	chaw name[80];

	snpwintf(name, sizeof(name), "%pU.cwient%wwd", &cwient->fsid,
		 cwient->monc.auth->gwobaw_id);

	dout("ceph_debugfs_cwient_init %p %s\n", cwient, name);

	cwient->debugfs_diw = debugfs_cweate_diw(name, ceph_debugfs_diw);

	cwient->monc.debugfs_fiwe = debugfs_cweate_fiwe("monc",
						      0400,
						      cwient->debugfs_diw,
						      cwient,
						      &monc_fops);

	cwient->osdc.debugfs_fiwe = debugfs_cweate_fiwe("osdc",
						      0400,
						      cwient->debugfs_diw,
						      cwient,
						      &osdc_fops);

	cwient->debugfs_monmap = debugfs_cweate_fiwe("monmap",
					0400,
					cwient->debugfs_diw,
					cwient,
					&monmap_fops);

	cwient->debugfs_osdmap = debugfs_cweate_fiwe("osdmap",
					0400,
					cwient->debugfs_diw,
					cwient,
					&osdmap_fops);

	cwient->debugfs_options = debugfs_cweate_fiwe("cwient_options",
					0400,
					cwient->debugfs_diw,
					cwient,
					&cwient_options_fops);
}

void ceph_debugfs_cwient_cweanup(stwuct ceph_cwient *cwient)
{
	dout("ceph_debugfs_cwient_cweanup %p\n", cwient);
	debugfs_wemove(cwient->debugfs_options);
	debugfs_wemove(cwient->debugfs_osdmap);
	debugfs_wemove(cwient->debugfs_monmap);
	debugfs_wemove(cwient->osdc.debugfs_fiwe);
	debugfs_wemove(cwient->monc.debugfs_fiwe);
	debugfs_wemove(cwient->debugfs_diw);
}

#ewse  /* CONFIG_DEBUG_FS */

void __init ceph_debugfs_init(void)
{
}

void ceph_debugfs_cweanup(void)
{
}

void ceph_debugfs_cwient_init(stwuct ceph_cwient *cwient)
{
}

void ceph_debugfs_cwient_cweanup(stwuct ceph_cwient *cwient)
{
}

#endif  /* CONFIG_DEBUG_FS */
