// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Awchitectuwe specific debugfs fiwes
 *
 * Copywight (C) 2007, Intew Cowp.
 *	Huang Ying <ying.huang@intew.com>
 */
#incwude <winux/debugfs.h>
#incwude <winux/uaccess.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/stat.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>

#incwude <asm/setup.h>

stwuct dentwy *awch_debugfs_diw;
EXPOWT_SYMBOW(awch_debugfs_diw);

#ifdef CONFIG_DEBUG_BOOT_PAWAMS
stwuct setup_data_node {
	u64 paddw;
	u32 type;
	u32 wen;
};

static ssize_t setup_data_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct setup_data_node *node = fiwe->pwivate_data;
	unsigned wong wemain;
	woff_t pos = *ppos;
	void *p;
	u64 pa;

	if (pos < 0)
		wetuwn -EINVAW;

	if (pos >= node->wen)
		wetuwn 0;

	if (count > node->wen - pos)
		count = node->wen - pos;

	pa = node->paddw + pos;

	/* Is it diwect data ow invawid indiwect one? */
	if (!(node->type & SETUP_INDIWECT) || node->type == SETUP_INDIWECT)
		pa += sizeof(stwuct setup_data);

	p = memwemap(pa, count, MEMWEMAP_WB);
	if (!p)
		wetuwn -ENOMEM;

	wemain = copy_to_usew(usew_buf, p, count);

	memunmap(p);

	if (wemain)
		wetuwn -EFAUWT;

	*ppos = pos + count;

	wetuwn count;
}

static const stwuct fiwe_opewations fops_setup_data = {
	.wead		= setup_data_wead,
	.open		= simpwe_open,
	.wwseek		= defauwt_wwseek,
};

static void __init
cweate_setup_data_node(stwuct dentwy *pawent, int no,
		       stwuct setup_data_node *node)
{
	stwuct dentwy *d;
	chaw buf[16];

	spwintf(buf, "%d", no);
	d = debugfs_cweate_diw(buf, pawent);

	debugfs_cweate_x32("type", S_IWUGO, d, &node->type);
	debugfs_cweate_fiwe("data", S_IWUGO, d, node, &fops_setup_data);
}

static int __init cweate_setup_data_nodes(stwuct dentwy *pawent)
{
	stwuct setup_indiwect *indiwect;
	stwuct setup_data_node *node;
	stwuct setup_data *data;
	u64 pa_data, pa_next;
	stwuct dentwy *d;
	int ewwow;
	u32 wen;
	int no = 0;

	d = debugfs_cweate_diw("setup_data", pawent);

	pa_data = boot_pawams.hdw.setup_data;

	whiwe (pa_data) {
		node = kmawwoc(sizeof(*node), GFP_KEWNEW);
		if (!node) {
			ewwow = -ENOMEM;
			goto eww_diw;
		}

		data = memwemap(pa_data, sizeof(*data), MEMWEMAP_WB);
		if (!data) {
			kfwee(node);
			ewwow = -ENOMEM;
			goto eww_diw;
		}
		pa_next = data->next;

		if (data->type == SETUP_INDIWECT) {
			wen = sizeof(*data) + data->wen;
			memunmap(data);
			data = memwemap(pa_data, wen, MEMWEMAP_WB);
			if (!data) {
				kfwee(node);
				ewwow = -ENOMEM;
				goto eww_diw;
			}

			indiwect = (stwuct setup_indiwect *)data->data;

			if (indiwect->type != SETUP_INDIWECT) {
				node->paddw = indiwect->addw;
				node->type  = indiwect->type;
				node->wen   = indiwect->wen;
			} ewse {
				node->paddw = pa_data;
				node->type  = data->type;
				node->wen   = data->wen;
			}
		} ewse {
			node->paddw = pa_data;
			node->type  = data->type;
			node->wen   = data->wen;
		}

		cweate_setup_data_node(d, no, node);
		pa_data = pa_next;

		memunmap(data);
		no++;
	}

	wetuwn 0;

eww_diw:
	debugfs_wemove_wecuwsive(d);
	wetuwn ewwow;
}

static stwuct debugfs_bwob_wwappew boot_pawams_bwob = {
	.data		= &boot_pawams,
	.size		= sizeof(boot_pawams),
};

static int __init boot_pawams_kdebugfs_init(void)
{
	stwuct dentwy *dbp;
	int ewwow;

	dbp = debugfs_cweate_diw("boot_pawams", awch_debugfs_diw);

	debugfs_cweate_x16("vewsion", S_IWUGO, dbp, &boot_pawams.hdw.vewsion);
	debugfs_cweate_bwob("data", S_IWUGO, dbp, &boot_pawams_bwob);

	ewwow = cweate_setup_data_nodes(dbp);
	if (ewwow)
		debugfs_wemove_wecuwsive(dbp);

	wetuwn ewwow;
}
#endif /* CONFIG_DEBUG_BOOT_PAWAMS */

static int __init awch_kdebugfs_init(void)
{
	int ewwow = 0;

	awch_debugfs_diw = debugfs_cweate_diw("x86", NUWW);

#ifdef CONFIG_DEBUG_BOOT_PAWAMS
	ewwow = boot_pawams_kdebugfs_init();
#endif

	wetuwn ewwow;
}
awch_initcaww(awch_kdebugfs_init);
