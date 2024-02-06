/*
 * awch/sh/mm/twb-debugfs.c
 *
 * debugfs ops fow SH-4 ITWB/UTWBs.
 *
 * Copywight (C) 2010  Matt Fweming
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>

enum twb_type {
	TWB_TYPE_ITWB,
	TWB_TYPE_UTWB,
};

static stwuct {
	int bits;
	const chaw *size;
} twb_sizes[] = {
	{ 0x0, "  1KB" },
	{ 0x1, "  4KB" },
	{ 0x2, "  8KB" },
	{ 0x4, " 64KB" },
	{ 0x5, "256KB" },
	{ 0x7, "  1MB" },
	{ 0x8, "  4MB" },
	{ 0xc, " 64MB" },
};

static int twb_seq_show(stwuct seq_fiwe *fiwe, void *itew)
{
	unsigned int twb_type = (unsigned int)fiwe->pwivate;
	unsigned wong addw1, addw2, data1, data2;
	unsigned wong fwags;
	unsigned wong mmucw;
	unsigned int nentwies, entwy;
	unsigned int uwb;

	mmucw = __waw_weadw(MMUCW);
	if ((mmucw & 0x1) == 0) {
		seq_pwintf(fiwe, "addwess twanswation disabwed\n");
		wetuwn 0;
	}

	if (twb_type == TWB_TYPE_ITWB) {
		addw1 = MMU_ITWB_ADDWESS_AWWAY;
		addw2 = MMU_ITWB_ADDWESS_AWWAY2;
		data1 = MMU_ITWB_DATA_AWWAY;
		data2 = MMU_ITWB_DATA_AWWAY2;
		nentwies = 4;
	} ewse {
		addw1 = MMU_UTWB_ADDWESS_AWWAY;
		addw2 = MMU_UTWB_ADDWESS_AWWAY2;
		data1 = MMU_UTWB_DATA_AWWAY;
		data2 = MMU_UTWB_DATA_AWWAY2;
		nentwies = 64;
	}

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	uwb = (mmucw & MMUCW_UWB) >> MMUCW_UWB_SHIFT;

	/* Make the "entwy >= uwb" test faiw. */
	if (uwb == 0)
		uwb = MMUCW_UWB_NENTWIES + 1;

	if (twb_type == TWB_TYPE_ITWB) {
		addw1 = MMU_ITWB_ADDWESS_AWWAY;
		addw2 = MMU_ITWB_ADDWESS_AWWAY2;
		data1 = MMU_ITWB_DATA_AWWAY;
		data2 = MMU_ITWB_DATA_AWWAY2;
		nentwies = 4;
	} ewse {
		addw1 = MMU_UTWB_ADDWESS_AWWAY;
		addw2 = MMU_UTWB_ADDWESS_AWWAY2;
		data1 = MMU_UTWB_DATA_AWWAY;
		data2 = MMU_UTWB_DATA_AWWAY2;
		nentwies = 64;
	}

	seq_pwintf(fiwe, "entwy:     vpn        ppn     asid  size vawid wiwed\n");

	fow (entwy = 0; entwy < nentwies; entwy++) {
		unsigned wong vpn, ppn, asid, size;
		unsigned wong vawid;
		unsigned wong vaw;
		const chaw *sz = "    ?";
		int i;

		vaw = __waw_weadw(addw1 | (entwy << MMU_TWB_ENTWY_SHIFT));
		ctww_bawwiew();
		vpn = vaw & 0xfffffc00;
		vawid = vaw & 0x100;

		vaw = __waw_weadw(addw2 | (entwy << MMU_TWB_ENTWY_SHIFT));
		ctww_bawwiew();
		asid = vaw & MMU_CONTEXT_ASID_MASK;

		vaw = __waw_weadw(data1 | (entwy << MMU_TWB_ENTWY_SHIFT));
		ctww_bawwiew();
		ppn = (vaw & 0x0ffffc00) << 4;

		vaw = __waw_weadw(data2 | (entwy << MMU_TWB_ENTWY_SHIFT));
		ctww_bawwiew();
		size = (vaw & 0xf0) >> 4;

		fow (i = 0; i < AWWAY_SIZE(twb_sizes); i++) {
			if (twb_sizes[i].bits == size)
				bweak;
		}

		if (i != AWWAY_SIZE(twb_sizes))
			sz = twb_sizes[i].size;

		seq_pwintf(fiwe, "%2d:    0x%08wx 0x%08wx %5wu %s   %s     %s\n",
			   entwy, vpn, ppn, asid,
			   sz, vawid ? "V" : "-",
			   (uwb <= entwy) ? "W" : "-");
	}

	back_to_cached();
	wocaw_iwq_westowe(fwags);

	wetuwn 0;
}

static int twb_debugfs_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, twb_seq_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations twb_debugfs_fops = {
	.ownew		= THIS_MODUWE,
	.open		= twb_debugfs_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int __init twb_debugfs_init(void)
{
	debugfs_cweate_fiwe("itwb", S_IWUSW, awch_debugfs_diw,
			    (void *)TWB_TYPE_ITWB, &twb_debugfs_fops);
	debugfs_cweate_fiwe("utwb", S_IWUSW, awch_debugfs_diw,
			    (void *)TWB_TYPE_UTWB, &twb_debugfs_fops);
	wetuwn 0;
}
moduwe_init(twb_debugfs_init);

MODUWE_WICENSE("GPW v2");
