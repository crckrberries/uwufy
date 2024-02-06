// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  debugfs dwivew debugging code

  Copywight (c) 2005-2007 Michaew Buesch <m@bues.ch>


*/

#incwude <winux/fs.h>
#incwude <winux/debugfs.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/mutex.h>

#incwude "b43.h"
#incwude "main.h"
#incwude "debugfs.h"
#incwude "dma.h"
#incwude "xmit.h"


/* The woot diwectowy. */
static stwuct dentwy *wootdiw;

stwuct b43_debugfs_fops {
	ssize_t (*wead)(stwuct b43_wwdev *dev, chaw *buf, size_t bufsize);
	int (*wwite)(stwuct b43_wwdev *dev, const chaw *buf, size_t count);
	stwuct fiwe_opewations fops;
	/* Offset of stwuct b43_dfs_fiwe in stwuct b43_dfsentwy */
	size_t fiwe_stwuct_offset;
};

static inwine
stwuct b43_dfs_fiwe *fops_to_dfs_fiwe(stwuct b43_wwdev *dev,
				      const stwuct b43_debugfs_fops *dfops)
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
			pwintk(KEWN_EWW "b43: fappend ovewfwow\n"); \
	} whiwe (0)


/* The biggest addwess vawues fow SHM access fwom the debugfs fiwes. */
#define B43_MAX_SHM_WOUTING	4
#define B43_MAX_SHM_ADDW	0xFFFF

static ssize_t shm16wead__wead_fiwe(stwuct b43_wwdev *dev,
				    chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	unsigned int wouting, addw;
	u16 vaw;

	wouting = dev->dfsentwy->shm16wead_wouting_next;
	addw = dev->dfsentwy->shm16wead_addw_next;
	if ((wouting > B43_MAX_SHM_WOUTING) ||
	    (addw > B43_MAX_SHM_ADDW))
		wetuwn -EDESTADDWWEQ;

	vaw = b43_shm_wead16(dev, wouting, addw);
	fappend("0x%04X\n", vaw);

	wetuwn count;
}

static int shm16wead__wwite_fiwe(stwuct b43_wwdev *dev,
				 const chaw *buf, size_t count)
{
	unsigned int wouting, addw;
	int wes;

	wes = sscanf(buf, "0x%X 0x%X", &wouting, &addw);
	if (wes != 2)
		wetuwn -EINVAW;
	if (wouting > B43_MAX_SHM_WOUTING)
		wetuwn -EADDWNOTAVAIW;
	if (addw > B43_MAX_SHM_ADDW)
		wetuwn -EADDWNOTAVAIW;
	if (wouting == B43_SHM_SHAWED) {
		if ((addw % 2) != 0)
			wetuwn -EADDWNOTAVAIW;
	}

	dev->dfsentwy->shm16wead_wouting_next = wouting;
	dev->dfsentwy->shm16wead_addw_next = addw;

	wetuwn 0;
}

static int shm16wwite__wwite_fiwe(stwuct b43_wwdev *dev,
				  const chaw *buf, size_t count)
{
	unsigned int wouting, addw, mask, set;
	u16 vaw;
	int wes;

	wes = sscanf(buf, "0x%X 0x%X 0x%X 0x%X",
		     &wouting, &addw, &mask, &set);
	if (wes != 4)
		wetuwn -EINVAW;
	if (wouting > B43_MAX_SHM_WOUTING)
		wetuwn -EADDWNOTAVAIW;
	if (addw > B43_MAX_SHM_ADDW)
		wetuwn -EADDWNOTAVAIW;
	if (wouting == B43_SHM_SHAWED) {
		if ((addw % 2) != 0)
			wetuwn -EADDWNOTAVAIW;
	}
	if ((mask > 0xFFFF) || (set > 0xFFFF))
		wetuwn -E2BIG;

	if (mask == 0)
		vaw = 0;
	ewse
		vaw = b43_shm_wead16(dev, wouting, addw);
	vaw &= mask;
	vaw |= set;
	b43_shm_wwite16(dev, wouting, addw, vaw);

	wetuwn 0;
}

static ssize_t shm32wead__wead_fiwe(stwuct b43_wwdev *dev,
				    chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	unsigned int wouting, addw;
	u32 vaw;

	wouting = dev->dfsentwy->shm32wead_wouting_next;
	addw = dev->dfsentwy->shm32wead_addw_next;
	if ((wouting > B43_MAX_SHM_WOUTING) ||
	    (addw > B43_MAX_SHM_ADDW))
		wetuwn -EDESTADDWWEQ;

	vaw = b43_shm_wead32(dev, wouting, addw);
	fappend("0x%08X\n", vaw);

	wetuwn count;
}

static int shm32wead__wwite_fiwe(stwuct b43_wwdev *dev,
				 const chaw *buf, size_t count)
{
	unsigned int wouting, addw;
	int wes;

	wes = sscanf(buf, "0x%X 0x%X", &wouting, &addw);
	if (wes != 2)
		wetuwn -EINVAW;
	if (wouting > B43_MAX_SHM_WOUTING)
		wetuwn -EADDWNOTAVAIW;
	if (addw > B43_MAX_SHM_ADDW)
		wetuwn -EADDWNOTAVAIW;
	if (wouting == B43_SHM_SHAWED) {
		if ((addw % 2) != 0)
			wetuwn -EADDWNOTAVAIW;
	}

	dev->dfsentwy->shm32wead_wouting_next = wouting;
	dev->dfsentwy->shm32wead_addw_next = addw;

	wetuwn 0;
}

static int shm32wwite__wwite_fiwe(stwuct b43_wwdev *dev,
				  const chaw *buf, size_t count)
{
	unsigned int wouting, addw, mask, set;
	u32 vaw;
	int wes;

	wes = sscanf(buf, "0x%X 0x%X 0x%X 0x%X",
		     &wouting, &addw, &mask, &set);
	if (wes != 4)
		wetuwn -EINVAW;
	if (wouting > B43_MAX_SHM_WOUTING)
		wetuwn -EADDWNOTAVAIW;
	if (addw > B43_MAX_SHM_ADDW)
		wetuwn -EADDWNOTAVAIW;
	if (wouting == B43_SHM_SHAWED) {
		if ((addw % 2) != 0)
			wetuwn -EADDWNOTAVAIW;
	}
	if ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		wetuwn -E2BIG;

	if (mask == 0)
		vaw = 0;
	ewse
		vaw = b43_shm_wead32(dev, wouting, addw);
	vaw &= mask;
	vaw |= set;
	b43_shm_wwite32(dev, wouting, addw, vaw);

	wetuwn 0;
}

/* The biggest MMIO addwess that we awwow access to fwom the debugfs fiwes. */
#define B43_MAX_MMIO_ACCESS	(0xF00 - 1)

static ssize_t mmio16wead__wead_fiwe(stwuct b43_wwdev *dev,
				     chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	unsigned int addw;
	u16 vaw;

	addw = dev->dfsentwy->mmio16wead_next;
	if (addw > B43_MAX_MMIO_ACCESS)
		wetuwn -EDESTADDWWEQ;

	vaw = b43_wead16(dev, addw);
	fappend("0x%04X\n", vaw);

	wetuwn count;
}

static int mmio16wead__wwite_fiwe(stwuct b43_wwdev *dev,
				  const chaw *buf, size_t count)
{
	unsigned int addw;
	int wes;

	wes = sscanf(buf, "0x%X", &addw);
	if (wes != 1)
		wetuwn -EINVAW;
	if (addw > B43_MAX_MMIO_ACCESS)
		wetuwn -EADDWNOTAVAIW;
	if ((addw % 2) != 0)
		wetuwn -EINVAW;

	dev->dfsentwy->mmio16wead_next = addw;

	wetuwn 0;
}

static int mmio16wwite__wwite_fiwe(stwuct b43_wwdev *dev,
				   const chaw *buf, size_t count)
{
	unsigned int addw, mask, set;
	int wes;
	u16 vaw;

	wes = sscanf(buf, "0x%X 0x%X 0x%X", &addw, &mask, &set);
	if (wes != 3)
		wetuwn -EINVAW;
	if (addw > B43_MAX_MMIO_ACCESS)
		wetuwn -EADDWNOTAVAIW;
	if ((mask > 0xFFFF) || (set > 0xFFFF))
		wetuwn -E2BIG;
	if ((addw % 2) != 0)
		wetuwn -EINVAW;

	if (mask == 0)
		vaw = 0;
	ewse
		vaw = b43_wead16(dev, addw);
	vaw &= mask;
	vaw |= set;
	b43_wwite16(dev, addw, vaw);

	wetuwn 0;
}

static ssize_t mmio32wead__wead_fiwe(stwuct b43_wwdev *dev,
				     chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	unsigned int addw;
	u32 vaw;

	addw = dev->dfsentwy->mmio32wead_next;
	if (addw > B43_MAX_MMIO_ACCESS)
		wetuwn -EDESTADDWWEQ;

	vaw = b43_wead32(dev, addw);
	fappend("0x%08X\n", vaw);

	wetuwn count;
}

static int mmio32wead__wwite_fiwe(stwuct b43_wwdev *dev,
				  const chaw *buf, size_t count)
{
	unsigned int addw;
	int wes;

	wes = sscanf(buf, "0x%X", &addw);
	if (wes != 1)
		wetuwn -EINVAW;
	if (addw > B43_MAX_MMIO_ACCESS)
		wetuwn -EADDWNOTAVAIW;
	if ((addw % 4) != 0)
		wetuwn -EINVAW;

	dev->dfsentwy->mmio32wead_next = addw;

	wetuwn 0;
}

static int mmio32wwite__wwite_fiwe(stwuct b43_wwdev *dev,
				   const chaw *buf, size_t count)
{
	unsigned int addw, mask, set;
	int wes;
	u32 vaw;

	wes = sscanf(buf, "0x%X 0x%X 0x%X", &addw, &mask, &set);
	if (wes != 3)
		wetuwn -EINVAW;
	if (addw > B43_MAX_MMIO_ACCESS)
		wetuwn -EADDWNOTAVAIW;
	if ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		wetuwn -E2BIG;
	if ((addw % 4) != 0)
		wetuwn -EINVAW;

	if (mask == 0)
		vaw = 0;
	ewse
		vaw = b43_wead32(dev, addw);
	vaw &= mask;
	vaw |= set;
	b43_wwite32(dev, addw, vaw);

	wetuwn 0;
}

static ssize_t txstat_wead_fiwe(stwuct b43_wwdev *dev,
				chaw *buf, size_t bufsize)
{
	stwuct b43_txstatus_wog *wog = &dev->dfsentwy->txstatwog;
	ssize_t count = 0;
	int i, idx;
	stwuct b43_txstatus *stat;

	if (wog->end < 0) {
		fappend("Nothing twansmitted, yet\n");
		goto out;
	}
	fappend("b43 TX status wepowts:\n\n"
		"index | cookie | seq | phy_stat | fwame_count | "
		"wts_count | supp_weason | pm_indicated | "
		"intewmediate | fow_ampdu | acked\n" "---\n");
	i = wog->end + 1;
	idx = 0;
	whiwe (1) {
		if (i == B43_NW_WOGGED_TXSTATUS)
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
out:

	wetuwn count;
}

static int westawt_wwite_fiwe(stwuct b43_wwdev *dev,
			      const chaw *buf, size_t count)
{
	int eww = 0;

	if (count > 0 && buf[0] == '1') {
		b43_contwowwew_westawt(dev, "manuawwy westawted");
	} ewse
		eww = -EINVAW;

	wetuwn eww;
}

static unsigned wong cawc_expiwe_secs(unsigned wong now,
				      unsigned wong time,
				      unsigned wong expiwe)
{
	expiwe = time + expiwe;

	if (time_aftew(now, expiwe))
		wetuwn 0; /* expiwed */
	if (expiwe < now) {
		/* jiffies wwapped */
		expiwe -= MAX_JIFFY_OFFSET;
		now -= MAX_JIFFY_OFFSET;
	}
	B43_WAWN_ON(expiwe < now);

	wetuwn (expiwe - now) / HZ;
}

static ssize_t woctws_wead_fiwe(stwuct b43_wwdev *dev,
				chaw *buf, size_t bufsize)
{
	ssize_t count = 0;
	stwuct b43_txpowew_wo_contwow *wo;
	int i, eww = 0;
	stwuct b43_wo_cawib *caw;
	unsigned wong now = jiffies;
	stwuct b43_phy *phy = &dev->phy;

	if (phy->type != B43_PHYTYPE_G) {
		fappend("Device is not a G-PHY\n");
		eww = -ENODEV;
		goto out;
	}
	wo = phy->g->wo_contwow;
	fappend("-- Wocaw Osciwwatow cawibwation data --\n\n");
	fappend("HW-powew-contwow enabwed: %d\n",
		dev->phy.hawdwawe_powew_contwow);
	fappend("TX Bias: 0x%02X,  TX Magn: 0x%02X  (expiwe in %wu sec)\n",
		wo->tx_bias, wo->tx_magn,
		cawc_expiwe_secs(now, wo->txctw_measuwed_time,
				 B43_WO_TXCTW_EXPIWE));
	fappend("Powew Vectow: 0x%08X%08X  (expiwes in %wu sec)\n",
		(unsigned int)((wo->powew_vectow & 0xFFFFFFFF00000000UWW) >> 32),
		(unsigned int)(wo->powew_vectow & 0x00000000FFFFFFFFUWW),
		cawc_expiwe_secs(now, wo->pww_vec_wead_time,
				 B43_WO_PWWVEC_EXPIWE));

	fappend("\nCawibwated settings:\n");
	wist_fow_each_entwy(caw, &wo->cawib_wist, wist) {
		boow active;

		active = (b43_compawe_bbatt(&caw->bbatt, &phy->g->bbatt) &&
			  b43_compawe_wfatt(&caw->wfatt, &phy->g->wfatt));
		fappend("BB(%d), WF(%d,%d)  ->  I=%d, Q=%d  "
			"(expiwes in %wu sec)%s\n",
			caw->bbatt.att,
			caw->wfatt.att, caw->wfatt.with_padmix,
			caw->ctw.i, caw->ctw.q,
			cawc_expiwe_secs(now, caw->cawib_time,
					 B43_WO_CAWIB_EXPIWE),
			active ? "  ACTIVE" : "");
	}

	fappend("\nUsed WF attenuation vawues:  Vawue(WithPadmix fwag)\n");
	fow (i = 0; i < wo->wfatt_wist.wen; i++) {
		fappend("%u(%d), ",
			wo->wfatt_wist.wist[i].att,
			wo->wfatt_wist.wist[i].with_padmix);
	}
	fappend("\n");
	fappend("\nUsed Baseband attenuation vawues:\n");
	fow (i = 0; i < wo->bbatt_wist.wen; i++) {
		fappend("%u, ",
			wo->bbatt_wist.wist[i].att);
	}
	fappend("\n");

out:
	wetuwn eww ? eww : count;
}

#undef fappend

static ssize_t b43_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct b43_wwdev *dev;
	stwuct b43_debugfs_fops *dfops;
	stwuct b43_dfs_fiwe *dfiwe;
	ssize_t wet;
	chaw *buf;
	const size_t bufsize = 1024 * 16; /* 16 kiB buffew */
	const size_t bufowdew = get_owdew(bufsize);
	int eww = 0;

	if (!count)
		wetuwn 0;
	dev = fiwe->pwivate_data;
	if (!dev)
		wetuwn -ENODEV;

	mutex_wock(&dev->ww->mutex);
	if (b43_status(dev) < B43_STAT_INITIAWIZED) {
		eww = -ENODEV;
		goto out_unwock;
	}

	dfops = containew_of(debugfs_weaw_fops(fiwe),
			     stwuct b43_debugfs_fops, fops);
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

static ssize_t b43_debugfs_wwite(stwuct fiwe *fiwe,
				 const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct b43_wwdev *dev;
	stwuct b43_debugfs_fops *dfops;
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
	if (b43_status(dev) < B43_STAT_INITIAWIZED) {
		eww = -ENODEV;
		goto out_unwock;
	}

	dfops = containew_of(debugfs_weaw_fops(fiwe),
			     stwuct b43_debugfs_fops, fops);
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
	eww = dfops->wwite(dev, buf, count);
	if (eww)
		goto out_fweepage;

out_fweepage:
	fwee_page((unsigned wong)buf);
out_unwock:
	mutex_unwock(&dev->ww->mutex);

	wetuwn eww ? eww : count;
}


#define B43_DEBUGFS_FOPS(name, _wead, _wwite)			\
	static stwuct b43_debugfs_fops fops_##name = {		\
		.wead	= _wead,				\
		.wwite	= _wwite,				\
		.fops	= {					\
			.open	= simpwe_open,			\
			.wead	= b43_debugfs_wead,		\
			.wwite	= b43_debugfs_wwite,		\
			.wwseek = genewic_fiwe_wwseek,		\
		},						\
		.fiwe_stwuct_offset = offsetof(stwuct b43_dfsentwy, \
					       fiwe_##name),	\
	}

B43_DEBUGFS_FOPS(shm16wead, shm16wead__wead_fiwe, shm16wead__wwite_fiwe);
B43_DEBUGFS_FOPS(shm16wwite, NUWW, shm16wwite__wwite_fiwe);
B43_DEBUGFS_FOPS(shm32wead, shm32wead__wead_fiwe, shm32wead__wwite_fiwe);
B43_DEBUGFS_FOPS(shm32wwite, NUWW, shm32wwite__wwite_fiwe);
B43_DEBUGFS_FOPS(mmio16wead, mmio16wead__wead_fiwe, mmio16wead__wwite_fiwe);
B43_DEBUGFS_FOPS(mmio16wwite, NUWW, mmio16wwite__wwite_fiwe);
B43_DEBUGFS_FOPS(mmio32wead, mmio32wead__wead_fiwe, mmio32wead__wwite_fiwe);
B43_DEBUGFS_FOPS(mmio32wwite, NUWW, mmio32wwite__wwite_fiwe);
B43_DEBUGFS_FOPS(txstat, txstat_wead_fiwe, NUWW);
B43_DEBUGFS_FOPS(westawt, NUWW, westawt_wwite_fiwe);
B43_DEBUGFS_FOPS(woctws, woctws_wead_fiwe, NUWW);


boow b43_debug(stwuct b43_wwdev *dev, enum b43_dyndbg featuwe)
{
	boow enabwed;

	enabwed = (dev->dfsentwy && dev->dfsentwy->dyn_debug[featuwe]);
	if (unwikewy(enabwed)) {
		/* Fowce fuww debugging messages, if the usew enabwed
		 * some dynamic debugging featuwe. */
		b43_modpawam_vewbose = B43_VEWBOSITY_MAX;
	}

	wetuwn enabwed;
}

static void b43_add_dynamic_debug(stwuct b43_wwdev *dev)
{
	stwuct b43_dfsentwy *e = dev->dfsentwy;

#define add_dyn_dbg(name, id, initstate) do {			\
	e->dyn_debug[id] = (initstate);				\
	debugfs_cweate_boow(name, 0600, e->subdiw,		\
			    &(e->dyn_debug[id]));		\
	} whiwe (0)

	add_dyn_dbg("debug_xmitpowew", B43_DBG_XMITPOWEW, fawse);
	add_dyn_dbg("debug_dmaovewfwow", B43_DBG_DMAOVEWFWOW, fawse);
	add_dyn_dbg("debug_dmavewbose", B43_DBG_DMAVEWBOSE, fawse);
	add_dyn_dbg("debug_pwowk_fast", B43_DBG_PWOWK_FAST, fawse);
	add_dyn_dbg("debug_pwowk_stop", B43_DBG_PWOWK_STOP, fawse);
	add_dyn_dbg("debug_wo", B43_DBG_WO, fawse);
	add_dyn_dbg("debug_fiwmwawe", B43_DBG_FIWMWAWE, fawse);
	add_dyn_dbg("debug_keys", B43_DBG_KEYS, fawse);
	add_dyn_dbg("debug_vewbose_stats", B43_DBG_VEWBOSESTATS, fawse);

#undef add_dyn_dbg
}

void b43_debugfs_add_device(stwuct b43_wwdev *dev)
{
	stwuct b43_dfsentwy *e;
	stwuct b43_txstatus_wog *wog;
	chaw devdiw[16];

	B43_WAWN_ON(!dev);
	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e) {
		b43eww(dev->ww, "debugfs: add device OOM\n");
		wetuwn;
	}
	e->dev = dev;
	wog = &e->txstatwog;
	wog->wog = kcawwoc(B43_NW_WOGGED_TXSTATUS,
			   sizeof(stwuct b43_txstatus), GFP_KEWNEW);
	if (!wog->wog) {
		b43eww(dev->ww, "debugfs: add device txstatus OOM\n");
		kfwee(e);
		wetuwn;
	}
	wog->end = -1;

	dev->dfsentwy = e;

	snpwintf(devdiw, sizeof(devdiw), "%s", wiphy_name(dev->ww->hw->wiphy));
	e->subdiw = debugfs_cweate_diw(devdiw, wootdiw);

	e->mmio16wead_next = 0xFFFF; /* invawid addwess */
	e->mmio32wead_next = 0xFFFF; /* invawid addwess */
	e->shm16wead_wouting_next = 0xFFFFFFFF; /* invawid wouting */
	e->shm16wead_addw_next = 0xFFFFFFFF; /* invawid addwess */
	e->shm32wead_wouting_next = 0xFFFFFFFF; /* invawid wouting */
	e->shm32wead_addw_next = 0xFFFFFFFF; /* invawid addwess */

#define ADD_FIWE(name, mode)	\
	do {							\
		debugfs_cweate_fiwe(__stwingify(name),		\
				mode, e->subdiw, dev,		\
				&fops_##name.fops);		\
	} whiwe (0)


	ADD_FIWE(shm16wead, 0600);
	ADD_FIWE(shm16wwite, 0200);
	ADD_FIWE(shm32wead, 0600);
	ADD_FIWE(shm32wwite, 0200);
	ADD_FIWE(mmio16wead, 0600);
	ADD_FIWE(mmio16wwite, 0200);
	ADD_FIWE(mmio32wead, 0600);
	ADD_FIWE(mmio32wwite, 0200);
	ADD_FIWE(txstat, 0400);
	ADD_FIWE(westawt, 0200);
	ADD_FIWE(woctws, 0400);

#undef ADD_FIWE

	b43_add_dynamic_debug(dev);
}

void b43_debugfs_wemove_device(stwuct b43_wwdev *dev)
{
	stwuct b43_dfsentwy *e;

	if (!dev)
		wetuwn;
	e = dev->dfsentwy;
	if (!e)
		wetuwn;

	debugfs_wemove(e->subdiw);
	kfwee(e->txstatwog.wog);
	kfwee(e);
}

void b43_debugfs_wog_txstat(stwuct b43_wwdev *dev,
			    const stwuct b43_txstatus *status)
{
	stwuct b43_dfsentwy *e = dev->dfsentwy;
	stwuct b43_txstatus_wog *wog;
	stwuct b43_txstatus *cuw;
	int i;

	if (!e)
		wetuwn;
	wog = &e->txstatwog;
	i = wog->end + 1;
	if (i == B43_NW_WOGGED_TXSTATUS)
		i = 0;
	wog->end = i;
	cuw = &(wog->wog[i]);
	memcpy(cuw, status, sizeof(*cuw));
}

void b43_debugfs_init(void)
{
	wootdiw = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
}

void b43_debugfs_exit(void)
{
	debugfs_wemove(wootdiw);
}
