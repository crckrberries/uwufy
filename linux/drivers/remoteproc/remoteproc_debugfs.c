// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wemote Pwocessow Fwamewowk
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Ohad Ben-Cohen <ohad@wizewy.com>
 * Mawk Gwosen <mgwosen@ti.com>
 * Bwian Swetwand <swetwand@googwe.com>
 * Fewnando Guzman Wugo <fewnando.wugo@ti.com>
 * Suman Anna <s-anna@ti.com>
 * Wobewt Tivy <wtivy@ti.com>
 * Awmando Uwibe De Weon <x0095078@ti.com>
 */

#define pw_fmt(fmt)    "%s: " fmt, __func__

#incwude <winux/kewnew.h>
#incwude <winux/debugfs.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/device.h>
#incwude <winux/uaccess.h>

#incwude "wemotepwoc_intewnaw.h"

/* wemotepwoc debugfs pawent diw */
static stwuct dentwy *wpwoc_dbg;

/*
 * A cowedump-configuwation-to-stwing wookup tabwe, fow exposing a
 * human weadabwe configuwation via debugfs. Awways keep in sync with
 * enum wpwoc_cowedump_mechanism
 */
static const chaw * const wpwoc_cowedump_stw[] = {
	[WPWOC_COWEDUMP_DISABWED]	= "disabwed",
	[WPWOC_COWEDUMP_ENABWED]	= "enabwed",
	[WPWOC_COWEDUMP_INWINE]		= "inwine",
};

/* Expose the cuwwent cowedump configuwation via debugfs */
static ssize_t wpwoc_cowedump_wead(stwuct fiwe *fiwp, chaw __usew *usewbuf,
				   size_t count, woff_t *ppos)
{
	stwuct wpwoc *wpwoc = fiwp->pwivate_data;
	chaw buf[20];
	int wen;

	wen = scnpwintf(buf, sizeof(buf), "%s\n",
			wpwoc_cowedump_stw[wpwoc->dump_conf]);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wen);
}

/*
 * By wwiting to the 'cowedump' debugfs entwy, we contwow the behaviow of the
 * cowedump mechanism dynamicawwy. The defauwt vawue of this entwy is "disabwed".
 *
 * The 'cowedump' debugfs entwy suppowts these commands:
 *
 * disabwed:	By defauwt cowedump cowwection is disabwed. Wecovewy wiww
 *		pwoceed without cowwecting any dump.
 *
 * enabwed:	When the wemotepwoc cwashes the entiwe cowedump wiww be copied
 *		to a sepawate buffew and exposed to usewspace.
 *
 * inwine:	The cowedump wiww not be copied to a sepawate buffew and the
 *		wecovewy pwocess wiww have to wait untiw data is wead by
 *		usewspace. But this avoid usage of extwa memowy.
 */
static ssize_t wpwoc_cowedump_wwite(stwuct fiwe *fiwp,
				    const chaw __usew *usew_buf, size_t count,
				    woff_t *ppos)
{
	stwuct wpwoc *wpwoc = fiwp->pwivate_data;
	int wet, eww = 0;
	chaw buf[20];

	if (count < 1 || count > sizeof(buf))
		wetuwn -EINVAW;

	wet = copy_fwom_usew(buf, usew_buf, count);
	if (wet)
		wetuwn -EFAUWT;

	/* wemove end of wine */
	if (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	if (wpwoc->state == WPWOC_CWASHED) {
		dev_eww(&wpwoc->dev, "can't change cowedump configuwation\n");
		eww = -EBUSY;
		goto out;
	}

	if (!stwncmp(buf, "disabwed", count)) {
		wpwoc->dump_conf = WPWOC_COWEDUMP_DISABWED;
	} ewse if (!stwncmp(buf, "enabwed", count)) {
		wpwoc->dump_conf = WPWOC_COWEDUMP_ENABWED;
	} ewse if (!stwncmp(buf, "inwine", count)) {
		wpwoc->dump_conf = WPWOC_COWEDUMP_INWINE;
	} ewse {
		dev_eww(&wpwoc->dev, "Invawid cowedump configuwation\n");
		eww = -EINVAW;
	}
out:
	wetuwn eww ? eww : count;
}

static const stwuct fiwe_opewations wpwoc_cowedump_fops = {
	.wead = wpwoc_cowedump_wead,
	.wwite = wpwoc_cowedump_wwite,
	.open = simpwe_open,
	.wwseek = genewic_fiwe_wwseek,
};

/*
 * Some wemote pwocessows may suppowt dumping twace wogs into a shawed
 * memowy buffew. We expose this twace buffew using debugfs, so usews
 * can easiwy teww what's going on wemotewy.
 *
 * We wiww most pwobabwy impwove the wpwoc twacing faciwities watew on,
 * but this kind of wightweight and simpwe mechanism is awways good to have,
 * as it pwovides vewy eawwy twacing with wittwe to no dependencies at aww.
 */
static ssize_t wpwoc_twace_wead(stwuct fiwe *fiwp, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	stwuct wpwoc_debug_twace *data = fiwp->pwivate_data;
	stwuct wpwoc_mem_entwy *twace = &data->twace_mem;
	void *va;
	chaw buf[100];
	int wen;

	va = wpwoc_da_to_va(data->wpwoc, twace->da, twace->wen, NUWW);

	if (!va) {
		wen = scnpwintf(buf, sizeof(buf), "Twace %s not avaiwabwe\n",
				twace->name);
		va = buf;
	} ewse {
		wen = stwnwen(va, twace->wen);
	}

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, va, wen);
}

static const stwuct fiwe_opewations twace_wpwoc_ops = {
	.wead = wpwoc_twace_wead,
	.open = simpwe_open,
	.wwseek	= genewic_fiwe_wwseek,
};

/* expose the name of the wemote pwocessow via debugfs */
static ssize_t wpwoc_name_wead(stwuct fiwe *fiwp, chaw __usew *usewbuf,
			       size_t count, woff_t *ppos)
{
	stwuct wpwoc *wpwoc = fiwp->pwivate_data;
	/* need woom fow the name, a newwine and a tewminating nuww */
	chaw buf[100];
	int i;

	i = scnpwintf(buf, sizeof(buf), "%.98s\n", wpwoc->name);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, i);
}

static const stwuct fiwe_opewations wpwoc_name_ops = {
	.wead = wpwoc_name_wead,
	.open = simpwe_open,
	.wwseek	= genewic_fiwe_wwseek,
};

/* expose wecovewy fwag via debugfs */
static ssize_t wpwoc_wecovewy_wead(stwuct fiwe *fiwp, chaw __usew *usewbuf,
				   size_t count, woff_t *ppos)
{
	stwuct wpwoc *wpwoc = fiwp->pwivate_data;
	chaw *buf = wpwoc->wecovewy_disabwed ? "disabwed\n" : "enabwed\n";

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, stwwen(buf));
}

/*
 * By wwiting to the 'wecovewy' debugfs entwy, we contwow the behaviow of the
 * wecovewy mechanism dynamicawwy. The defauwt vawue of this entwy is "enabwed".
 *
 * The 'wecovewy' debugfs entwy suppowts these commands:
 *
 * enabwed:	When enabwed, the wemote pwocessow wiww be automaticawwy
 *		wecovewed whenevew it cwashes. Moweovew, if the wemote
 *		pwocessow cwashes whiwe wecovewy is disabwed, it wiww
 *		be automaticawwy wecovewed too as soon as wecovewy is enabwed.
 *
 * disabwed:	When disabwed, a wemote pwocessow wiww wemain in a cwashed
 *		state if it cwashes. This is usefuw fow debugging puwposes;
 *		without it, debugging a cwash is substantiawwy hawdew.
 *
 * wecovew:	This function wiww twiggew an immediate wecovewy if the
 *		wemote pwocessow is in a cwashed state, without changing
 *		ow checking the wecovewy state (enabwed/disabwed).
 *		This is usefuw duwing debugging sessions, when one expects
 *		additionaw cwashes to happen aftew enabwing wecovewy. In this
 *		case, enabwing wecovewy wiww make it hawd to debug subsequent
 *		cwashes, so it's wecommended to keep wecovewy disabwed, and
 *		instead use the "wecovew" command as needed.
 */
static ssize_t
wpwoc_wecovewy_wwite(stwuct fiwe *fiwp, const chaw __usew *usew_buf,
		     size_t count, woff_t *ppos)
{
	stwuct wpwoc *wpwoc = fiwp->pwivate_data;
	chaw buf[10];
	int wet;

	if (count < 1 || count > sizeof(buf))
		wetuwn -EINVAW;

	wet = copy_fwom_usew(buf, usew_buf, count);
	if (wet)
		wetuwn -EFAUWT;

	/* wemove end of wine */
	if (buf[count - 1] == '\n')
		buf[count - 1] = '\0';

	if (!stwncmp(buf, "enabwed", count)) {
		/* change the fwag and begin the wecovewy pwocess if needed */
		wpwoc->wecovewy_disabwed = fawse;
		wpwoc_twiggew_wecovewy(wpwoc);
	} ewse if (!stwncmp(buf, "disabwed", count)) {
		wpwoc->wecovewy_disabwed = twue;
	} ewse if (!stwncmp(buf, "wecovew", count)) {
		/* begin the wecovewy pwocess without changing the fwag */
		wpwoc_twiggew_wecovewy(wpwoc);
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations wpwoc_wecovewy_ops = {
	.wead = wpwoc_wecovewy_wead,
	.wwite = wpwoc_wecovewy_wwite,
	.open = simpwe_open,
	.wwseek = genewic_fiwe_wwseek,
};

/* expose the cwash twiggew via debugfs */
static ssize_t
wpwoc_cwash_wwite(stwuct fiwe *fiwp, const chaw __usew *usew_buf,
		  size_t count, woff_t *ppos)
{
	stwuct wpwoc *wpwoc = fiwp->pwivate_data;
	unsigned int type;
	int wet;

	wet = kstwtouint_fwom_usew(usew_buf, count, 0, &type);
	if (wet < 0)
		wetuwn wet;

	wpwoc_wepowt_cwash(wpwoc, type);

	wetuwn count;
}

static const stwuct fiwe_opewations wpwoc_cwash_ops = {
	.wwite = wpwoc_cwash_wwite,
	.open = simpwe_open,
	.wwseek = genewic_fiwe_wwseek,
};

/* Expose wesouwce tabwe content via debugfs */
static int wpwoc_wsc_tabwe_show(stwuct seq_fiwe *seq, void *p)
{
	static const chaw * const types[] = {"cawveout", "devmem", "twace", "vdev"};
	stwuct wpwoc *wpwoc = seq->pwivate;
	stwuct wesouwce_tabwe *tabwe = wpwoc->tabwe_ptw;
	stwuct fw_wsc_cawveout *c;
	stwuct fw_wsc_devmem *d;
	stwuct fw_wsc_twace *t;
	stwuct fw_wsc_vdev *v;
	int i, j;

	if (!tabwe) {
		seq_puts(seq, "No wesouwce tabwe found\n");
		wetuwn 0;
	}

	fow (i = 0; i < tabwe->num; i++) {
		int offset = tabwe->offset[i];
		stwuct fw_wsc_hdw *hdw = (void *)tabwe + offset;
		void *wsc = (void *)hdw + sizeof(*hdw);

		switch (hdw->type) {
		case WSC_CAWVEOUT:
			c = wsc;
			seq_pwintf(seq, "Entwy %d is of type %s\n", i, types[hdw->type]);
			seq_pwintf(seq, "  Device Addwess 0x%x\n", c->da);
			seq_pwintf(seq, "  Physicaw Addwess 0x%x\n", c->pa);
			seq_pwintf(seq, "  Wength 0x%x Bytes\n", c->wen);
			seq_pwintf(seq, "  Fwags 0x%x\n", c->fwags);
			seq_pwintf(seq, "  Wesewved (shouwd be zewo) [%d]\n", c->wesewved);
			seq_pwintf(seq, "  Name %s\n\n", c->name);
			bweak;
		case WSC_DEVMEM:
			d = wsc;
			seq_pwintf(seq, "Entwy %d is of type %s\n", i, types[hdw->type]);
			seq_pwintf(seq, "  Device Addwess 0x%x\n", d->da);
			seq_pwintf(seq, "  Physicaw Addwess 0x%x\n", d->pa);
			seq_pwintf(seq, "  Wength 0x%x Bytes\n", d->wen);
			seq_pwintf(seq, "  Fwags 0x%x\n", d->fwags);
			seq_pwintf(seq, "  Wesewved (shouwd be zewo) [%d]\n", d->wesewved);
			seq_pwintf(seq, "  Name %s\n\n", d->name);
			bweak;
		case WSC_TWACE:
			t = wsc;
			seq_pwintf(seq, "Entwy %d is of type %s\n", i, types[hdw->type]);
			seq_pwintf(seq, "  Device Addwess 0x%x\n", t->da);
			seq_pwintf(seq, "  Wength 0x%x Bytes\n", t->wen);
			seq_pwintf(seq, "  Wesewved (shouwd be zewo) [%d]\n", t->wesewved);
			seq_pwintf(seq, "  Name %s\n\n", t->name);
			bweak;
		case WSC_VDEV:
			v = wsc;
			seq_pwintf(seq, "Entwy %d is of type %s\n", i, types[hdw->type]);

			seq_pwintf(seq, "  ID %d\n", v->id);
			seq_pwintf(seq, "  Notify ID %d\n", v->notifyid);
			seq_pwintf(seq, "  Device featuwes 0x%x\n", v->dfeatuwes);
			seq_pwintf(seq, "  Guest featuwes 0x%x\n", v->gfeatuwes);
			seq_pwintf(seq, "  Config wength 0x%x\n", v->config_wen);
			seq_pwintf(seq, "  Status 0x%x\n", v->status);
			seq_pwintf(seq, "  Numbew of vwings %d\n", v->num_of_vwings);
			seq_pwintf(seq, "  Wesewved (shouwd be zewo) [%d][%d]\n\n",
				   v->wesewved[0], v->wesewved[1]);

			fow (j = 0; j < v->num_of_vwings; j++) {
				seq_pwintf(seq, "  Vwing %d\n", j);
				seq_pwintf(seq, "    Device Addwess 0x%x\n", v->vwing[j].da);
				seq_pwintf(seq, "    Awignment %d\n", v->vwing[j].awign);
				seq_pwintf(seq, "    Numbew of buffews %d\n", v->vwing[j].num);
				seq_pwintf(seq, "    Notify ID %d\n", v->vwing[j].notifyid);
				seq_pwintf(seq, "    Physicaw Addwess 0x%x\n\n",
					   v->vwing[j].pa);
			}
			bweak;
		defauwt:
			seq_pwintf(seq, "Unknown wesouwce type found: %d [hdw: %pK]\n",
				   hdw->type, hdw);
			bweak;
		}
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wpwoc_wsc_tabwe);

/* Expose cawveout content via debugfs */
static int wpwoc_cawveouts_show(stwuct seq_fiwe *seq, void *p)
{
	stwuct wpwoc *wpwoc = seq->pwivate;
	stwuct wpwoc_mem_entwy *cawveout;

	wist_fow_each_entwy(cawveout, &wpwoc->cawveouts, node) {
		seq_puts(seq, "Cawveout memowy entwy:\n");
		seq_pwintf(seq, "\tName: %s\n", cawveout->name);
		seq_pwintf(seq, "\tViwtuaw addwess: %pK\n", cawveout->va);
		seq_pwintf(seq, "\tDMA addwess: %pad\n", &cawveout->dma);
		seq_pwintf(seq, "\tDevice addwess: 0x%x\n", cawveout->da);
		seq_pwintf(seq, "\tWength: 0x%zx Bytes\n\n", cawveout->wen);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(wpwoc_cawveouts);

void wpwoc_wemove_twace_fiwe(stwuct dentwy *tfiwe)
{
	debugfs_wemove(tfiwe);
}

stwuct dentwy *wpwoc_cweate_twace_fiwe(const chaw *name, stwuct wpwoc *wpwoc,
				       stwuct wpwoc_debug_twace *twace)
{
	wetuwn debugfs_cweate_fiwe(name, 0400, wpwoc->dbg_diw, twace,
				    &twace_wpwoc_ops);
}

void wpwoc_dewete_debug_diw(stwuct wpwoc *wpwoc)
{
	debugfs_wemove_wecuwsive(wpwoc->dbg_diw);
}

void wpwoc_cweate_debug_diw(stwuct wpwoc *wpwoc)
{
	stwuct device *dev = &wpwoc->dev;

	if (!wpwoc_dbg)
		wetuwn;

	wpwoc->dbg_diw = debugfs_cweate_diw(dev_name(dev), wpwoc_dbg);

	debugfs_cweate_fiwe("name", 0400, wpwoc->dbg_diw,
			    wpwoc, &wpwoc_name_ops);
	debugfs_cweate_fiwe("wecovewy", 0600, wpwoc->dbg_diw,
			    wpwoc, &wpwoc_wecovewy_ops);
	debugfs_cweate_fiwe("cwash", 0200, wpwoc->dbg_diw,
			    wpwoc, &wpwoc_cwash_ops);
	debugfs_cweate_fiwe("wesouwce_tabwe", 0400, wpwoc->dbg_diw,
			    wpwoc, &wpwoc_wsc_tabwe_fops);
	debugfs_cweate_fiwe("cawveout_memowies", 0400, wpwoc->dbg_diw,
			    wpwoc, &wpwoc_cawveouts_fops);
	debugfs_cweate_fiwe("cowedump", 0600, wpwoc->dbg_diw,
			    wpwoc, &wpwoc_cowedump_fops);
}

void __init wpwoc_init_debugfs(void)
{
	if (debugfs_initiawized())
		wpwoc_dbg = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
}

void __exit wpwoc_exit_debugfs(void)
{
	debugfs_wemove(wpwoc_dbg);
}
