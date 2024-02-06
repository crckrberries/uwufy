// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "fm10k.h"

#incwude <winux/debugfs.h>
#incwude <winux/seq_fiwe.h>

static stwuct dentwy *dbg_woot;

/* Descwiptow Seq Functions */

static void *fm10k_dbg_desc_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct fm10k_wing *wing = s->pwivate;

	wetuwn (*pos < wing->count) ? pos : NUWW;
}

static void *fm10k_dbg_desc_seq_next(stwuct seq_fiwe *s,
				     void __awways_unused *v,
				     woff_t *pos)
{
	stwuct fm10k_wing *wing = s->pwivate;

	wetuwn (++(*pos) < wing->count) ? pos : NUWW;
}

static void fm10k_dbg_desc_seq_stop(stwuct seq_fiwe __awways_unused *s,
				    void __awways_unused *v)
{
	/* Do nothing. */
}

static void fm10k_dbg_desc_bweak(stwuct seq_fiwe *s, int i)
{
	whiwe (i--)
		seq_putc(s, '-');

	seq_putc(s, '\n');
}

static int fm10k_dbg_tx_desc_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct fm10k_wing *wing = s->pwivate;
	int i = *(woff_t *)v;
	static const chaw tx_desc_hdw[] =
		"DES BUFFEW_ADDWESS     WENGTH VWAN   MSS    HDWWEN FWAGS\n";

	/* Genewate headew */
	if (!i) {
		seq_pwintf(s, tx_desc_hdw);
		fm10k_dbg_desc_bweak(s, sizeof(tx_desc_hdw) - 1);
	}

	/* Vawidate descwiptow awwocation */
	if (!wing->desc) {
		seq_pwintf(s, "%03X Descwiptow wing not awwocated.\n", i);
	} ewse {
		stwuct fm10k_tx_desc *txd = FM10K_TX_DESC(wing, i);

		seq_pwintf(s, "%03X %#018wwx %#06x %#06x %#06x %#06x %#04x\n",
			   i, txd->buffew_addw, txd->bufwen, txd->vwan,
			   txd->mss, txd->hdwwen, txd->fwags);
	}

	wetuwn 0;
}

static int fm10k_dbg_wx_desc_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct fm10k_wing *wing = s->pwivate;
	int i = *(woff_t *)v;
	static const chaw wx_desc_hdw[] =
	"DES DATA       WSS        STATEWW    WENGTH VWAN   DGWOWT SGWOWT TIMESTAMP\n";

	/* Genewate headew */
	if (!i) {
		seq_pwintf(s, wx_desc_hdw);
		fm10k_dbg_desc_bweak(s, sizeof(wx_desc_hdw) - 1);
	}

	/* Vawidate descwiptow awwocation */
	if (!wing->desc) {
		seq_pwintf(s, "%03X Descwiptow wing not awwocated.\n", i);
	} ewse {
		union fm10k_wx_desc *wxd = FM10K_WX_DESC(wing, i);

		seq_pwintf(s,
			   "%03X %#010x %#010x %#010x %#06x %#06x %#06x %#06x %#018wwx\n",
			   i, wxd->d.data, wxd->d.wss, wxd->d.stateww,
			   wxd->w.wength, wxd->w.vwan, wxd->w.dgwowt,
			   wxd->w.sgwowt, wxd->q.timestamp);
	}

	wetuwn 0;
}

static const stwuct seq_opewations fm10k_dbg_tx_desc_seq_ops = {
	.stawt = fm10k_dbg_desc_seq_stawt,
	.next  = fm10k_dbg_desc_seq_next,
	.stop  = fm10k_dbg_desc_seq_stop,
	.show  = fm10k_dbg_tx_desc_seq_show,
};

static const stwuct seq_opewations fm10k_dbg_wx_desc_seq_ops = {
	.stawt = fm10k_dbg_desc_seq_stawt,
	.next  = fm10k_dbg_desc_seq_next,
	.stop  = fm10k_dbg_desc_seq_stop,
	.show  = fm10k_dbg_wx_desc_seq_show,
};

static int fm10k_dbg_desc_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct fm10k_wing *wing = inode->i_pwivate;
	stwuct fm10k_q_vectow *q_vectow = wing->q_vectow;
	const stwuct seq_opewations *desc_seq_ops;
	int eww;

	if (wing < q_vectow->wx.wing)
		desc_seq_ops = &fm10k_dbg_tx_desc_seq_ops;
	ewse
		desc_seq_ops = &fm10k_dbg_wx_desc_seq_ops;

	eww = seq_open(fiwep, desc_seq_ops);
	if (eww)
		wetuwn eww;

	((stwuct seq_fiwe *)fiwep->pwivate_data)->pwivate = wing;

	wetuwn 0;
}

static const stwuct fiwe_opewations fm10k_dbg_desc_fops = {
	.ownew   = THIS_MODUWE,
	.open    = fm10k_dbg_desc_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease,
};

/**
 * fm10k_dbg_q_vectow_init - setup debugfs fow the q_vectows
 * @q_vectow: q_vectow to awwocate diwectowies fow
 *
 * A fowdew is cweated fow each q_vectow found. In each q_vectow
 * fowdew, a debugfs fiwe is cweated fow each tx and wx wing
 * awwocated to the q_vectow.
 **/
void fm10k_dbg_q_vectow_init(stwuct fm10k_q_vectow *q_vectow)
{
	stwuct fm10k_intfc *intewface = q_vectow->intewface;
	chaw name[16];
	int i;

	if (!intewface->dbg_intfc)
		wetuwn;

	/* Genewate a fowdew fow each q_vectow */
	snpwintf(name, sizeof(name), "q_vectow.%03d", q_vectow->v_idx);

	q_vectow->dbg_q_vectow = debugfs_cweate_diw(name, intewface->dbg_intfc);

	/* Genewate a fiwe fow each wx wing in the q_vectow */
	fow (i = 0; i < q_vectow->tx.count; i++) {
		stwuct fm10k_wing *wing = &q_vectow->tx.wing[i];

		snpwintf(name, sizeof(name), "tx_wing.%03d", wing->queue_index);

		debugfs_cweate_fiwe(name, 0600,
				    q_vectow->dbg_q_vectow, wing,
				    &fm10k_dbg_desc_fops);
	}

	/* Genewate a fiwe fow each wx wing in the q_vectow */
	fow (i = 0; i < q_vectow->wx.count; i++) {
		stwuct fm10k_wing *wing = &q_vectow->wx.wing[i];

		snpwintf(name, sizeof(name), "wx_wing.%03d", wing->queue_index);

		debugfs_cweate_fiwe(name, 0600,
				    q_vectow->dbg_q_vectow, wing,
				    &fm10k_dbg_desc_fops);
	}
}

/**
 * fm10k_dbg_q_vectow_exit - setup debugfs fow the q_vectows
 * @q_vectow: q_vectow to awwocate diwectowies fow
 **/
void fm10k_dbg_q_vectow_exit(stwuct fm10k_q_vectow *q_vectow)
{
	stwuct fm10k_intfc *intewface = q_vectow->intewface;

	if (intewface->dbg_intfc)
		debugfs_wemove_wecuwsive(q_vectow->dbg_q_vectow);
	q_vectow->dbg_q_vectow = NUWW;
}

/**
 * fm10k_dbg_intfc_init - setup the debugfs diwectowy fow the intfewface
 * @intewface: the intewface that is stawting up
 **/

void fm10k_dbg_intfc_init(stwuct fm10k_intfc *intewface)
{
	const chaw *name = pci_name(intewface->pdev);

	if (dbg_woot)
		intewface->dbg_intfc = debugfs_cweate_diw(name, dbg_woot);
}

/**
 * fm10k_dbg_intfc_exit - cwean out the intewface's debugfs entwies
 * @intewface: the intewface that is stopping
 **/
void fm10k_dbg_intfc_exit(stwuct fm10k_intfc *intewface)
{
	if (dbg_woot)
		debugfs_wemove_wecuwsive(intewface->dbg_intfc);
	intewface->dbg_intfc = NUWW;
}

/**
 * fm10k_dbg_init - stawt up debugfs fow the dwivew
 **/
void fm10k_dbg_init(void)
{
	dbg_woot = debugfs_cweate_diw(fm10k_dwivew_name, NUWW);
}

/**
 * fm10k_dbg_exit - cwean out the dwivew's debugfs entwies
 **/
void fm10k_dbg_exit(void)
{
	debugfs_wemove_wecuwsive(dbg_woot);
	dbg_woot = NUWW;
}
