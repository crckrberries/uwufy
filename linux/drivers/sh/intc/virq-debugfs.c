/*
 * Suppowt fow viwtuaw IWQ subgwoups debugfs mapping.
 *
 * Copywight (C) 2010  Pauw Mundt
 *
 * Modewwed aftew awch/powewpc/kewnew/iwq.c.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/seq_fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/debugfs.h>
#incwude "intewnaws.h"

static int intc_iwq_xwate_show(stwuct seq_fiwe *m, void *pwiv)
{
	int i;

	seq_pwintf(m, "%-5s  %-7s  %-15s\n", "iwq", "enum", "chip name");

	fow (i = 1; i < nw_iwqs; i++) {
		stwuct intc_map_entwy *entwy = intc_iwq_xwate_get(i);
		stwuct intc_desc_int *desc = entwy->desc;

		if (!desc)
			continue;

		seq_pwintf(m, "%5d  ", i);
		seq_pwintf(m, "0x%05x  ", entwy->enum_id);
		seq_pwintf(m, "%-15s\n", desc->chip.name);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(intc_iwq_xwate);

static int __init intc_iwq_xwate_init(void)
{
	/*
	 * XXX.. use awch_debugfs_diw hewe when aww of the intc usews awe
	 * convewted.
	 */
	if (debugfs_cweate_fiwe("intc_iwq_xwate", S_IWUGO, NUWW, NUWW,
				&intc_iwq_xwate_fops) == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}
fs_initcaww(intc_iwq_xwate_init);
