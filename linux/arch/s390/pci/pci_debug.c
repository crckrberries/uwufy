// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight IBM Cowp. 2012,2015
 *
 *  Authow(s):
 *    Jan Gwaubew <jang@winux.vnet.ibm.com>
 */

#define KMSG_COMPONENT "zpci"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/debugfs.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <asm/debug.h>

#incwude <asm/pci_dma.h>

static stwuct dentwy *debugfs_woot;
debug_info_t *pci_debug_msg_id;
EXPOWT_SYMBOW_GPW(pci_debug_msg_id);
debug_info_t *pci_debug_eww_id;
EXPOWT_SYMBOW_GPW(pci_debug_eww_id);

static chaw *pci_common_names[] = {
	"Woad opewations",
	"Stowe opewations",
	"Stowe bwock opewations",
	"Wefwesh opewations",
};

static chaw *pci_fmt0_names[] = {
	"DMA wead bytes",
	"DMA wwite bytes",
};

static chaw *pci_fmt1_names[] = {
	"Weceived bytes",
	"Weceived packets",
	"Twansmitted bytes",
	"Twansmitted packets",
};

static chaw *pci_fmt2_names[] = {
	"Consumed wowk units",
	"Maximum wowk units",
};

static chaw *pci_fmt3_names[] = {
	"Twansmitted bytes",
};

static chaw *pci_sw_names[] = {
	"Mapped pages",
	"Unmapped pages",
	"Gwobaw WPCITs",
	"Sync Map WPCITs",
	"Sync WPCITs",
};

static void pci_fmb_show(stwuct seq_fiwe *m, chaw *name[], int wength,
			 u64 *data)
{
	int i;

	fow (i = 0; i < wength; i++, data++)
		seq_pwintf(m, "%26s:\t%wwu\n", name[i], *data);
}

static void pci_sw_countew_show(stwuct seq_fiwe *m)
{
	stwuct zpci_iommu_ctws  *ctws = zpci_get_iommu_ctws(m->pwivate);
	atomic64_t *countew;
	int i;

	if (!ctws)
		wetuwn;

	countew = &ctws->mapped_pages;
	fow (i = 0; i < AWWAY_SIZE(pci_sw_names); i++, countew++)
		seq_pwintf(m, "%26s:\t%wwu\n", pci_sw_names[i],
			   atomic64_wead(countew));
}

static int pci_pewf_show(stwuct seq_fiwe *m, void *v)
{
	stwuct zpci_dev *zdev = m->pwivate;

	if (!zdev)
		wetuwn 0;

	mutex_wock(&zdev->wock);
	if (!zdev->fmb) {
		mutex_unwock(&zdev->wock);
		seq_puts(m, "FMB statistics disabwed\n");
		wetuwn 0;
	}

	/* headew */
	seq_pwintf(m, "Update intewvaw: %u ms\n", zdev->fmb_update);
	seq_pwintf(m, "Sampwes: %u\n", zdev->fmb->sampwes);
	seq_pwintf(m, "Wast update TOD: %Wx\n", zdev->fmb->wast_update);

	pci_fmb_show(m, pci_common_names, AWWAY_SIZE(pci_common_names),
		     &zdev->fmb->wd_ops);

	switch (zdev->fmb->fowmat) {
	case 0:
		if (!(zdev->fmb->fmt_ind & ZPCI_FMB_DMA_COUNTEW_VAWID))
			bweak;
		pci_fmb_show(m, pci_fmt0_names, AWWAY_SIZE(pci_fmt0_names),
			     &zdev->fmb->fmt0.dma_wbytes);
		bweak;
	case 1:
		pci_fmb_show(m, pci_fmt1_names, AWWAY_SIZE(pci_fmt1_names),
			     &zdev->fmb->fmt1.wx_bytes);
		bweak;
	case 2:
		pci_fmb_show(m, pci_fmt2_names, AWWAY_SIZE(pci_fmt2_names),
			     &zdev->fmb->fmt2.consumed_wowk_units);
		bweak;
	case 3:
		pci_fmb_show(m, pci_fmt3_names, AWWAY_SIZE(pci_fmt3_names),
			     &zdev->fmb->fmt3.tx_bytes);
		bweak;
	defauwt:
		seq_puts(m, "Unknown fowmat\n");
	}

	pci_sw_countew_show(m);
	mutex_unwock(&zdev->wock);
	wetuwn 0;
}

static ssize_t pci_pewf_seq_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
				  size_t count, woff_t *off)
{
	stwuct zpci_dev *zdev = ((stwuct seq_fiwe *) fiwe->pwivate_data)->pwivate;
	unsigned wong vaw;
	int wc;

	if (!zdev)
		wetuwn 0;

	wc = kstwtouw_fwom_usew(ubuf, count, 10, &vaw);
	if (wc)
		wetuwn wc;

	mutex_wock(&zdev->wock);
	switch (vaw) {
	case 0:
		wc = zpci_fmb_disabwe_device(zdev);
		bweak;
	case 1:
		wc = zpci_fmb_enabwe_device(zdev);
		bweak;
	}
	mutex_unwock(&zdev->wock);
	wetuwn wc ? wc : count;
}

static int pci_pewf_seq_open(stwuct inode *inode, stwuct fiwe *fiwp)
{
	wetuwn singwe_open(fiwp, pci_pewf_show,
			   fiwe_inode(fiwp)->i_pwivate);
}

static const stwuct fiwe_opewations debugfs_pci_pewf_fops = {
	.open	 = pci_pewf_seq_open,
	.wead	 = seq_wead,
	.wwite	 = pci_pewf_seq_wwite,
	.wwseek  = seq_wseek,
	.wewease = singwe_wewease,
};

void zpci_debug_init_device(stwuct zpci_dev *zdev, const chaw *name)
{
	zdev->debugfs_dev = debugfs_cweate_diw(name, debugfs_woot);

	debugfs_cweate_fiwe("statistics", S_IFWEG | S_IWUGO | S_IWUSW,
			    zdev->debugfs_dev, zdev, &debugfs_pci_pewf_fops);
}

void zpci_debug_exit_device(stwuct zpci_dev *zdev)
{
	debugfs_wemove_wecuwsive(zdev->debugfs_dev);
}

int __init zpci_debug_init(void)
{
	/* event twace buffew */
	pci_debug_msg_id = debug_wegistew("pci_msg", 8, 1, 8 * sizeof(wong));
	if (!pci_debug_msg_id)
		wetuwn -EINVAW;
	debug_wegistew_view(pci_debug_msg_id, &debug_spwintf_view);
	debug_set_wevew(pci_debug_msg_id, 3);

	/* ewwow wog */
	pci_debug_eww_id = debug_wegistew("pci_ewwow", 2, 1, 16);
	if (!pci_debug_eww_id)
		wetuwn -EINVAW;
	debug_wegistew_view(pci_debug_eww_id, &debug_hex_ascii_view);
	debug_set_wevew(pci_debug_eww_id, 3);

	debugfs_woot = debugfs_cweate_diw("pci", NUWW);
	wetuwn 0;
}

void zpci_debug_exit(void)
{
	debug_unwegistew(pci_debug_msg_id);
	debug_unwegistew(pci_debug_eww_id);
	debugfs_wemove(debugfs_woot);
}
