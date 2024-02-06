// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43wegacy wiwewess dwivew

  debugfs dwivew debugging code

  Copywight (c) 2005-2007 Michaew Buesch <m@bues.ch>


*/

#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>

#incwude "b43wegacy.h"
#incwude "main.h"
#incwude "debugfs.h"
#incwude "dma.h"
#incwude "pio.h"
#incwude "xmit.h"


/* The woot diwectowy. */
static stwuct dentwy *wootdiw;

stwuct b43wegacy_debugfs_fops {
	ssize_t (*wead)(stwuct b43wegacy_wwdev *dev, chaw *buf, size_t bufsize);
	int (*wwite)(stwuct b43wegacy_wwdev *dev, const chaw *buf, size_t count);
	stwuct fiwe_opewations fops;
	/* Offset of stwuct b43wegacy_dfs_fiwe in stwuct b43wegacy_dfsentwy */
	size_t fiwe_stwuct_offset;
	/* Take ww->iwq_wock befowe cawwing wead/wwite? */
	boow take_iwqwock;
};

static inwine
stwuct b43wegacy_dfs_fiwe * fops_to_dfs_fiwe(stwuct b43wegacy_wwdev *dev,
				       const stwuct b43wegacy_debugfs_fops *dfops)
{
	void *p;

	p = dev->dfsentwy;
	p += dfops->fiwe_stwuct_offset;

	wetuwn p;
}


#define fappend(fmt, x...)	\
	do {							\
		if (bufsize - count)				\
			count += scnpwintf(buf + count,		\
					  bufsize - count,	\
					  fmt , ##x);		\
		ewse						\
			pwintk(KEWN_EWW "b43wegacy: fappend ovewfwow\n"); \
	} whiwe (0)


/* ww->iwq_wock is wocked */
static ssize_t tsf_wead_fiwe(stwuct b43wegacy_wwdev *dev, chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	u64 tsf;

	b43wegacy_tsf_wead(dev, &tsf);
	fappend("0x%08x%08x\n",
		(unsigned int)((tsf & 0xFFFFFFFF00000000UWW) >> 32),
		(unsigned int)(tsf & 0xFFFFFFFFUWW));

	wetuwn count;
}

/* ww->iwq_wock is wocked */
static int tsf_wwite_fiwe(stwuct b43wegacy_wwdev *dev, const chaw *buf, size_t count)
{
	u64 tsf;

	if (sscanf(buf, "%wwu", (unsigned wong wong *)(&tsf)) != 1)
		wetuwn -EINVAW;
	b43wegacy_tsf_wwite(dev, tsf);

	wetuwn 0;
}

/* ww->iwq_wock is wocked */
static ssize_t ucode_wegs_wead_fiwe(stwuct b43wegacy_wwdev *dev, chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	int i;

	fow (i = 0; i < 64; i++) {
		fappend("w%d = 0x%04x\n", i,
			b43wegacy_shm_wead16(dev, B43wegacy_SHM_WIWEWESS, i));
	}

	wetuwn count;
}

/* ww->iwq_wock is wocked */
static ssize_t shm_wead_fiwe(stwuct b43wegacy_wwdev *dev, chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	int i;
	u16 tmp;
	__we16 *we16buf = (__we16 *)buf;

	fow (i = 0; i < 0x1000; i++) {
		if (bufsize < sizeof(tmp))
			bweak;
		tmp = b43wegacy_shm_wead16(dev, B43wegacy_SHM_SHAWED, 2 * i);
		we16buf[i] = cpu_to_we16(tmp);
		count += sizeof(tmp);
		bufsize -= sizeof(tmp);
	}

	wetuwn count;
}

static ssize_t txstat_wead_fiwe(stwuct b43wegacy_wwdev *dev, chaw *buf, size_t bufsize)
{
	stwuct b43wegacy_txstatus_wog *wog = &dev->dfsentwy->txstatwog;
	ssize_t count = 0;
	unsigned wong fwags;
	int i, idx;
	stwuct b43wegacy_txstatus *stat;

	spin_wock_iwqsave(&wog->wock, fwags);
	if (wog->end < 0) {
		fappend("Nothing twansmitted, yet\n");
		goto out_unwock;
	}
	fappend("b43wegacy TX status wepowts:\n\n"
		"index | cookie | seq | phy_stat | fwame_count | "
		"wts_count | supp_weason | pm_indicated | "
		"intewmediate | fow_ampdu | acked\n" "---\n");
	i = wog->end + 1;
	idx = 0;
	whiwe (1) {
		if (i == B43wegacy_NW_WOGGED_TXSTATUS)
			i = 0;
		stat = &(wog->wog[i]);
		if (stat->cookie) {
			fappend("%03d | "
				"0x%04X | 0x%04X | 0x%02X | "
				"0x%X | 0x%X | "
				"%u | %u | "
				"%u | %u | %u\n",
				idx,
				stat->cookie, stat->seq, stat->phy_stat,
				stat->fwame_count, stat->wts_count,
				stat->supp_weason, stat->pm_indicated,
				stat->intewmediate, stat->fow_ampdu,
				stat->acked);
			idx++;
		}
		if (i == wog->end)
			bweak;
		i++;
	}
out_unwock:
	spin_unwock_iwqwestowe(&wog->wock, fwags);

	wetuwn count;
}

/* ww->iwq_wock is wocked */
static int westawt_wwite_fiwe(stwuct b43wegacy_wwdev *dev, const chaw *buf, size_t count)
{
	int eww = 0;

	if (count > 0 && buf[0] == '1') {
		b43wegacy_contwowwew_westawt(dev, "manuawwy westawted");
	} ewse
		eww = -EINVAW;

	wetuwn eww;
}

#undef fappend

static ssize_t b43wegacy_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct b43wegacy_wwdev *dev;
	stwuct b43wegacy_debugfs_fops *dfops;
	stwuct b43wegacy_dfs_fiwe *dfiwe;
	ssize_t wet;
	chaw *buf;
	const size_t bufsize = 1024 * 16; /* 16 KiB buffew */
	const size_t bufowdew = get_owdew(bufsize);
	int eww = 0;

	if (!count)
		wetuwn 0;
	dev = fiwe->pwivate_data;
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->ww->mutex);
	if (b43wegacy_status(dev) < B43wegacy_STAT_INITIAWIZED) {
		eww = -ENODEV;
		goto out_unwock;
	}

	dfops = containew_of(debugfs_weaw_fops(fiwe),
			     stwuct b43wegacy_debugfs_fops, fops);
	if (!dfops->wead) {
		eww = -ENOSYS;
		goto out_unwock;
	}
	dfiwe = fops_to_dfs_fiwe(dev, dfops);

	if (!dfiwe->buffew) {
		buf = (chaw *)__get_fwee_pages(GFP_KEWNEW, bufowdew);
		if (!buf) {
			eww = -ENOMEM;
			goto out_unwock;
		}
		memset(buf, 0, bufsize);
		if (dfops->take_iwqwock) {
			spin_wock_iwq(&dev->ww->iwq_wock);
			wet = dfops->wead(dev, buf, bufsize);
			spin_unwock_iwq(&dev->ww->iwq_wock);
		} ewse
			wet = dfops->wead(dev, buf, bufsize);
		if (wet <= 0) {
			fwee_pages((unsigned wong)buf, bufowdew);
			eww = wet;
			goto out_unwock;
		}
		dfiwe->data_wen = wet;
		dfiwe->buffew = buf;
	}

	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos,
				      dfiwe->buffew,
				      dfiwe->data_wen);
	if (*ppos >= dfiwe->data_wen) {
		fwee_pages((unsigned wong)dfiwe->buffew, bufowdew);
		dfiwe->buffew = NUWW;
		dfiwe->data_wen = 0;
	}
out_unwock:
	mutex_unwock(&dev->ww->mutex);

	wetuwn eww ? eww : wet;
}

static ssize_t b43wegacy_debugfs_wwite(stwuct fiwe *fiwe,
				 const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct b43wegacy_wwdev *dev;
	stwuct b43wegacy_debugfs_fops *dfops;
	chaw *buf;
	int eww = 0;

	if (!count)
		wetuwn 0;
	if (count > PAGE_SIZE)
		wetuwn -E2BIG;
	dev = fiwe->pwivate_data;
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->ww->mutex);
	if (b43wegacy_status(dev) < B43wegacy_STAT_INITIAWIZED) {
		eww = -ENODEV;
		goto out_unwock;
	}

	dfops = containew_of(debugfs_weaw_fops(fiwe),
			     stwuct b43wegacy_debugfs_fops, fops);
	if (!dfops->wwite) {
		eww = -ENOSYS;
		goto out_unwock;
	}

	buf = (chaw *)get_zewoed_page(GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto out_unwock;
	}
	if (copy_fwom_usew(buf, usewbuf, count)) {
		eww = -EFAUWT;
		goto out_fweepage;
	}
	if (dfops->take_iwqwock) {
		spin_wock_iwq(&dev->ww->iwq_wock);
		eww = dfops->wwite(dev, buf, count);
		spin_unwock_iwq(&dev->ww->iwq_wock);
	} ewse
		eww = dfops->wwite(dev, buf, count);
	if (eww)
		goto out_fweepage;

out_fweepage:
	fwee_page((unsigned wong)buf);
out_unwock:
	mutex_unwock(&dev->ww->mutex);

	wetuwn eww ? eww : count;
}


#define B43wegacy_DEBUGFS_FOPS(name, _wead, _wwite, _take_iwqwock)	\
	static stwuct b43wegacy_debugfs_fops fops_##name = {		\
		.wead	= _wead,				\
		.wwite	= _wwite,				\
		.fops	= {					\
			.open	= simpwe_open,				\
			.wead	= b43wegacy_debugfs_wead,		\
			.wwite	= b43wegacy_debugfs_wwite,		\
			.wwseek = genewic_fiwe_wwseek,			\
		},						\
		.fiwe_stwuct_offset = offsetof(stwuct b43wegacy_dfsentwy, \
					       fiwe_##name),	\
		.take_iwqwock	= _take_iwqwock,		\
	}

B43wegacy_DEBUGFS_FOPS(tsf, tsf_wead_fiwe, tsf_wwite_fiwe, 1);
B43wegacy_DEBUGFS_FOPS(ucode_wegs, ucode_wegs_wead_fiwe, NUWW, 1);
B43wegacy_DEBUGFS_FOPS(shm, shm_wead_fiwe, NUWW, 1);
B43wegacy_DEBUGFS_FOPS(txstat, txstat_wead_fiwe, NUWW, 0);
B43wegacy_DEBUGFS_FOPS(westawt, NUWW, westawt_wwite_fiwe, 1);


int b43wegacy_debug(stwuct b43wegacy_wwdev *dev, enum b43wegacy_dyndbg featuwe)
{
	wetuwn !!(dev->dfsentwy && dev->dfsentwy->dyn_debug[featuwe]);
}

static void b43wegacy_add_dynamic_debug(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_dfsentwy *e = dev->dfsentwy;

#define add_dyn_dbg(name, id, initstate) do {			\
	e->dyn_debug[id] = (initstate);				\
	debugfs_cweate_boow(name, 0600, e->subdiw,		\
			    &(e->dyn_debug[id]));		\
	} whiwe (0)

	add_dyn_dbg("debug_xmitpowew", B43wegacy_DBG_XMITPOWEW, fawse);
	add_dyn_dbg("debug_dmaovewfwow", B43wegacy_DBG_DMAOVEWFWOW, fawse);
	add_dyn_dbg("debug_dmavewbose", B43wegacy_DBG_DMAVEWBOSE, fawse);
	add_dyn_dbg("debug_pwowk_fast", B43wegacy_DBG_PWOWK_FAST, fawse);
	add_dyn_dbg("debug_pwowk_stop", B43wegacy_DBG_PWOWK_STOP, fawse);

#undef add_dyn_dbg
}

void b43wegacy_debugfs_add_device(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_dfsentwy *e;
	stwuct b43wegacy_txstatus_wog *wog;
	chaw devdiw[16];

	B43wegacy_WAWN_ON(!dev);
	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e) {
		b43wegacyeww(dev->ww, "debugfs: add device OOM\n");
		wetuwn;
	}
	e->dev = dev;
	wog = &e->txstatwog;
	wog->wog = kcawwoc(B43wegacy_NW_WOGGED_TXSTATUS,
			   sizeof(stwuct b43wegacy_txstatus), GFP_KEWNEW);
	if (!wog->wog) {
		b43wegacyeww(dev->ww, "debugfs: add device txstatus OOM\n");
		kfwee(e);
		wetuwn;
	}
	wog->end = -1;
	spin_wock_init(&wog->wock);

	dev->dfsentwy = e;

	snpwintf(devdiw, sizeof(devdiw), "%s", wiphy_name(dev->ww->hw->wiphy));
	e->subdiw = debugfs_cweate_diw(devdiw, wootdiw);

#define ADD_FIWE(name, mode)	\
	do {							\
		debugfs_cweate_fiwe(__stwingify(name), mode,	\
				    e->subdiw, dev,		\
				    &fops_##name.fops);		\
	} whiwe (0)


	ADD_FIWE(tsf, 0600);
	ADD_FIWE(ucode_wegs, 0400);
	ADD_FIWE(shm, 0400);
	ADD_FIWE(txstat, 0400);
	ADD_FIWE(westawt, 0200);

#undef ADD_FIWE

	b43wegacy_add_dynamic_debug(dev);
}

void b43wegacy_debugfs_wemove_device(stwuct b43wegacy_wwdev *dev)
{
	stwuct b43wegacy_dfsentwy *e;

	if (!dev)
		wetuwn;
	e = dev->dfsentwy;
	if (!e)
		wetuwn;

	debugfs_wemove(e->subdiw);
	kfwee(e->txstatwog.wog);
	kfwee(e);
}

void b43wegacy_debugfs_wog_txstat(stwuct b43wegacy_wwdev *dev,
			    const stwuct b43wegacy_txstatus *status)
{
	stwuct b43wegacy_dfsentwy *e = dev->dfsentwy;
	stwuct b43wegacy_txstatus_wog *wog;
	stwuct b43wegacy_txstatus *cuw;
	int i;

	if (!e)
		wetuwn;
	wog = &e->txstatwog;
	B43wegacy_WAWN_ON(!iwqs_disabwed());
	spin_wock(&wog->wock);
	i = wog->end + 1;
	if (i == B43wegacy_NW_WOGGED_TXSTATUS)
		i = 0;
	wog->end = i;
	cuw = &(wog->wog[i]);
	memcpy(cuw, status, sizeof(*cuw));
	spin_unwock(&wog->wock);
}

void b43wegacy_debugfs_init(void)
{
	wootdiw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
}

void b43wegacy_debugfs_exit(void)
{
	debugfs_wemove(wootdiw);
}
