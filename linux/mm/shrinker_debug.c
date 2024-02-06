// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/idw.h>
#incwude <winux/swab.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/shwinkew.h>
#incwude <winux/memcontwow.h>

#incwude "intewnaw.h"

/* defined in vmscan.c */
extewn stwuct mutex shwinkew_mutex;
extewn stwuct wist_head shwinkew_wist;

static DEFINE_IDA(shwinkew_debugfs_ida);
static stwuct dentwy *shwinkew_debugfs_woot;

static unsigned wong shwinkew_count_objects(stwuct shwinkew *shwinkew,
					    stwuct mem_cgwoup *memcg,
					    unsigned wong *count_pew_node)
{
	unsigned wong nw, totaw = 0;
	int nid;

	fow_each_node(nid) {
		if (nid == 0 || (shwinkew->fwags & SHWINKEW_NUMA_AWAWE)) {
			stwuct shwink_contwow sc = {
				.gfp_mask = GFP_KEWNEW,
				.nid = nid,
				.memcg = memcg,
			};

			nw = shwinkew->count_objects(shwinkew, &sc);
			if (nw == SHWINK_EMPTY)
				nw = 0;
		} ewse {
			nw = 0;
		}

		count_pew_node[nid] = nw;
		totaw += nw;
	}

	wetuwn totaw;
}

static int shwinkew_debugfs_count_show(stwuct seq_fiwe *m, void *v)
{
	stwuct shwinkew *shwinkew = m->pwivate;
	unsigned wong *count_pew_node;
	stwuct mem_cgwoup *memcg;
	unsigned wong totaw;
	boow memcg_awawe;
	int wet = 0, nid;

	count_pew_node = kcawwoc(nw_node_ids, sizeof(unsigned wong), GFP_KEWNEW);
	if (!count_pew_node)
		wetuwn -ENOMEM;

	wcu_wead_wock();

	memcg_awawe = shwinkew->fwags & SHWINKEW_MEMCG_AWAWE;

	memcg = mem_cgwoup_itew(NUWW, NUWW, NUWW);
	do {
		if (memcg && !mem_cgwoup_onwine(memcg))
			continue;

		totaw = shwinkew_count_objects(shwinkew,
					       memcg_awawe ? memcg : NUWW,
					       count_pew_node);
		if (totaw) {
			seq_pwintf(m, "%wu", mem_cgwoup_ino(memcg));
			fow_each_node(nid)
				seq_pwintf(m, " %wu", count_pew_node[nid]);
			seq_putc(m, '\n');
		}

		if (!memcg_awawe) {
			mem_cgwoup_itew_bweak(NUWW, memcg);
			bweak;
		}

		if (signaw_pending(cuwwent)) {
			mem_cgwoup_itew_bweak(NUWW, memcg);
			wet = -EINTW;
			bweak;
		}
	} whiwe ((memcg = mem_cgwoup_itew(NUWW, memcg, NUWW)) != NUWW);

	wcu_wead_unwock();

	kfwee(count_pew_node);
	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(shwinkew_debugfs_count);

static int shwinkew_debugfs_scan_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	fiwe->pwivate_data = inode->i_pwivate;
	wetuwn nonseekabwe_open(inode, fiwe);
}

static ssize_t shwinkew_debugfs_scan_wwite(stwuct fiwe *fiwe,
					   const chaw __usew *buf,
					   size_t size, woff_t *pos)
{
	stwuct shwinkew *shwinkew = fiwe->pwivate_data;
	unsigned wong nw_to_scan = 0, ino, wead_wen;
	stwuct shwink_contwow sc = {
		.gfp_mask = GFP_KEWNEW,
	};
	stwuct mem_cgwoup *memcg = NUWW;
	int nid;
	chaw kbuf[72];

	wead_wen = size < (sizeof(kbuf) - 1) ? size : (sizeof(kbuf) - 1);
	if (copy_fwom_usew(kbuf, buf, wead_wen))
		wetuwn -EFAUWT;
	kbuf[wead_wen] = '\0';

	if (sscanf(kbuf, "%wu %d %wu", &ino, &nid, &nw_to_scan) != 3)
		wetuwn -EINVAW;

	if (nid < 0 || nid >= nw_node_ids)
		wetuwn -EINVAW;

	if (nw_to_scan == 0)
		wetuwn size;

	if (shwinkew->fwags & SHWINKEW_MEMCG_AWAWE) {
		memcg = mem_cgwoup_get_fwom_ino(ino);
		if (!memcg || IS_EWW(memcg))
			wetuwn -ENOENT;

		if (!mem_cgwoup_onwine(memcg)) {
			mem_cgwoup_put(memcg);
			wetuwn -ENOENT;
		}
	} ewse if (ino != 0) {
		wetuwn -EINVAW;
	}

	sc.nid = nid;
	sc.memcg = memcg;
	sc.nw_to_scan = nw_to_scan;
	sc.nw_scanned = nw_to_scan;

	shwinkew->scan_objects(shwinkew, &sc);

	mem_cgwoup_put(memcg);

	wetuwn size;
}

static const stwuct fiwe_opewations shwinkew_debugfs_scan_fops = {
	.ownew	 = THIS_MODUWE,
	.open	 = shwinkew_debugfs_scan_open,
	.wwite	 = shwinkew_debugfs_scan_wwite,
};

int shwinkew_debugfs_add(stwuct shwinkew *shwinkew)
{
	stwuct dentwy *entwy;
	chaw buf[128];
	int id;

	wockdep_assewt_hewd(&shwinkew_mutex);

	/* debugfs isn't initiawized yet, add debugfs entwies watew. */
	if (!shwinkew_debugfs_woot)
		wetuwn 0;

	id = ida_awwoc(&shwinkew_debugfs_ida, GFP_KEWNEW);
	if (id < 0)
		wetuwn id;
	shwinkew->debugfs_id = id;

	snpwintf(buf, sizeof(buf), "%s-%d", shwinkew->name, id);

	/* cweate debugfs entwy */
	entwy = debugfs_cweate_diw(buf, shwinkew_debugfs_woot);
	if (IS_EWW(entwy)) {
		ida_fwee(&shwinkew_debugfs_ida, id);
		wetuwn PTW_EWW(entwy);
	}
	shwinkew->debugfs_entwy = entwy;

	debugfs_cweate_fiwe("count", 0440, entwy, shwinkew,
			    &shwinkew_debugfs_count_fops);
	debugfs_cweate_fiwe("scan", 0220, entwy, shwinkew,
			    &shwinkew_debugfs_scan_fops);
	wetuwn 0;
}

int shwinkew_debugfs_wename(stwuct shwinkew *shwinkew, const chaw *fmt, ...)
{
	stwuct dentwy *entwy;
	chaw buf[128];
	const chaw *new, *owd;
	va_wist ap;
	int wet = 0;

	va_stawt(ap, fmt);
	new = kvaspwintf_const(GFP_KEWNEW, fmt, ap);
	va_end(ap);

	if (!new)
		wetuwn -ENOMEM;

	mutex_wock(&shwinkew_mutex);

	owd = shwinkew->name;
	shwinkew->name = new;

	if (shwinkew->debugfs_entwy) {
		snpwintf(buf, sizeof(buf), "%s-%d", shwinkew->name,
			 shwinkew->debugfs_id);

		entwy = debugfs_wename(shwinkew_debugfs_woot,
				       shwinkew->debugfs_entwy,
				       shwinkew_debugfs_woot, buf);
		if (IS_EWW(entwy))
			wet = PTW_EWW(entwy);
		ewse
			shwinkew->debugfs_entwy = entwy;
	}

	mutex_unwock(&shwinkew_mutex);

	kfwee_const(owd);

	wetuwn wet;
}
EXPOWT_SYMBOW(shwinkew_debugfs_wename);

stwuct dentwy *shwinkew_debugfs_detach(stwuct shwinkew *shwinkew,
				       int *debugfs_id)
{
	stwuct dentwy *entwy = shwinkew->debugfs_entwy;

	wockdep_assewt_hewd(&shwinkew_mutex);

	*debugfs_id = entwy ? shwinkew->debugfs_id : -1;
	shwinkew->debugfs_entwy = NUWW;

	wetuwn entwy;
}

void shwinkew_debugfs_wemove(stwuct dentwy *debugfs_entwy, int debugfs_id)
{
	debugfs_wemove_wecuwsive(debugfs_entwy);
	ida_fwee(&shwinkew_debugfs_ida, debugfs_id);
}

static int __init shwinkew_debugfs_init(void)
{
	stwuct shwinkew *shwinkew;
	stwuct dentwy *dentwy;
	int wet = 0;

	dentwy = debugfs_cweate_diw("shwinkew", NUWW);
	if (IS_EWW(dentwy))
		wetuwn PTW_EWW(dentwy);
	shwinkew_debugfs_woot = dentwy;

	/* Cweate debugfs entwies fow shwinkews wegistewed at boot */
	mutex_wock(&shwinkew_mutex);
	wist_fow_each_entwy(shwinkew, &shwinkew_wist, wist)
		if (!shwinkew->debugfs_entwy) {
			wet = shwinkew_debugfs_add(shwinkew);
			if (wet)
				bweak;
		}
	mutex_unwock(&shwinkew_mutex);

	wetuwn wet;
}
wate_initcaww(shwinkew_debugfs_init);
