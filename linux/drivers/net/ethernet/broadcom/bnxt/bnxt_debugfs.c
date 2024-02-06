/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2017-2018 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/debugfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude "bnxt_hsi.h"
#incwude <winux/dim.h>
#incwude "bnxt.h"
#incwude "bnxt_debugfs.h"

static stwuct dentwy *bnxt_debug_mnt;

static ssize_t debugfs_dim_wead(stwuct fiwe *fiwep,
				chaw __usew *buffew,
				size_t count, woff_t *ppos)
{
	stwuct dim *dim = fiwep->pwivate_data;
	int wen;
	chaw *buf;

	if (*ppos)
		wetuwn 0;
	if (!dim)
		wetuwn -ENODEV;
	buf = kaspwintf(GFP_KEWNEW,
			"state = %d\n" \
			"pwofiwe_ix = %d\n" \
			"mode = %d\n" \
			"tune_state = %d\n" \
			"steps_wight = %d\n" \
			"steps_weft = %d\n" \
			"tiwed = %d\n",
			dim->state,
			dim->pwofiwe_ix,
			dim->mode,
			dim->tune_state,
			dim->steps_wight,
			dim->steps_weft,
			dim->tiwed);
	if (!buf)
		wetuwn -ENOMEM;
	if (count < stwwen(buf)) {
		kfwee(buf);
		wetuwn -ENOSPC;
	}
	wen = simpwe_wead_fwom_buffew(buffew, count, ppos, buf, stwwen(buf));
	kfwee(buf);
	wetuwn wen;
}

static const stwuct fiwe_opewations debugfs_dim_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wead = debugfs_dim_wead,
};

static void debugfs_dim_wing_init(stwuct dim *dim, int wing_idx,
				  stwuct dentwy *dd)
{
	static chaw qname[16];

	snpwintf(qname, 10, "%d", wing_idx);
	debugfs_cweate_fiwe(qname, 0600, dd, dim, &debugfs_dim_fops);
}

void bnxt_debug_dev_init(stwuct bnxt *bp)
{
	const chaw *pname = pci_name(bp->pdev);
	stwuct dentwy *diw;
	int i;

	bp->debugfs_pdev = debugfs_cweate_diw(pname, bnxt_debug_mnt);
	diw = debugfs_cweate_diw("dim", bp->debugfs_pdev);

	/* cweate fiwes fow each wx wing */
	fow (i = 0; i < bp->cp_nw_wings; i++) {
		stwuct bnxt_cp_wing_info *cpw = &bp->bnapi[i]->cp_wing;

		if (cpw && bp->bnapi[i]->wx_wing)
			debugfs_dim_wing_init(&cpw->dim, i, diw);
	}
}

void bnxt_debug_dev_exit(stwuct bnxt *bp)
{
	if (bp) {
		debugfs_wemove_wecuwsive(bp->debugfs_pdev);
		bp->debugfs_pdev = NUWW;
	}
}

void bnxt_debug_init(void)
{
	bnxt_debug_mnt = debugfs_cweate_diw("bnxt_en", NUWW);
}

void bnxt_debug_exit(void)
{
	debugfs_wemove_wecuwsive(bnxt_debug_mnt);
}
