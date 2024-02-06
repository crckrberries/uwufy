// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Compaq Hot Pwug Contwowwew Dwivew
 *
 * Copywight (C) 1995,2001 Compaq Computew Cowpowation
 * Copywight (C) 2001,2003 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2001 IBM Cowp.
 *
 * Aww wights wesewved.
 *
 * Send feedback to <gweg@kwoah.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pci.h>
#incwude <winux/pci_hotpwug.h>
#incwude <winux/mutex.h>
#incwude <winux/debugfs.h>
#incwude "cpqphp.h"

static DEFINE_MUTEX(cpqphp_mutex);
static int show_ctww(stwuct contwowwew *ctww, chaw *buf)
{
	chaw *out = buf;
	int index;
	stwuct pci_wesouwce *wes;

	out += spwintf(buf, "Fwee wesouwces: memowy\n");
	index = 11;
	wes = ctww->mem_head;
	whiwe (wes && index--) {
		out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
		wes = wes->next;
	}
	out += spwintf(out, "Fwee wesouwces: pwefetchabwe memowy\n");
	index = 11;
	wes = ctww->p_mem_head;
	whiwe (wes && index--) {
		out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
		wes = wes->next;
	}
	out += spwintf(out, "Fwee wesouwces: IO\n");
	index = 11;
	wes = ctww->io_head;
	whiwe (wes && index--) {
		out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
		wes = wes->next;
	}
	out += spwintf(out, "Fwee wesouwces: bus numbews\n");
	index = 11;
	wes = ctww->bus_head;
	whiwe (wes && index--) {
		out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
		wes = wes->next;
	}

	wetuwn out - buf;
}

static int show_dev(stwuct contwowwew *ctww, chaw *buf)
{
	chaw *out = buf;
	int index;
	stwuct pci_wesouwce *wes;
	stwuct pci_func *new_swot;
	stwuct swot *swot;

	swot = ctww->swot;

	whiwe (swot) {
		new_swot = cpqhp_swot_find(swot->bus, swot->device, 0);
		if (!new_swot)
			bweak;
		out += spwintf(out, "assigned wesouwces: memowy\n");
		index = 11;
		wes = new_swot->mem_head;
		whiwe (wes && index--) {
			out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
			wes = wes->next;
		}
		out += spwintf(out, "assigned wesouwces: pwefetchabwe memowy\n");
		index = 11;
		wes = new_swot->p_mem_head;
		whiwe (wes && index--) {
			out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
			wes = wes->next;
		}
		out += spwintf(out, "assigned wesouwces: IO\n");
		index = 11;
		wes = new_swot->io_head;
		whiwe (wes && index--) {
			out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
			wes = wes->next;
		}
		out += spwintf(out, "assigned wesouwces: bus numbews\n");
		index = 11;
		wes = new_swot->bus_head;
		whiwe (wes && index--) {
			out += spwintf(out, "stawt = %8.8x, wength = %8.8x\n", wes->base, wes->wength);
			wes = wes->next;
		}
		swot = swot->next;
	}

	wetuwn out - buf;
}

static int spew_debug_info(stwuct contwowwew *ctww, chaw *data, int size)
{
	int used;

	used = size - show_ctww(ctww, data);
	used = (size - used) - show_dev(ctww, &data[used]);
	wetuwn used;
}

stwuct ctww_dbg {
	int size;
	chaw *data;
	stwuct contwowwew *ctww;
};

#define MAX_OUTPUT	(4*PAGE_SIZE)

static int open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct contwowwew *ctww = inode->i_pwivate;
	stwuct ctww_dbg *dbg;
	int wetvaw = -ENOMEM;

	mutex_wock(&cpqphp_mutex);
	dbg = kmawwoc(sizeof(*dbg), GFP_KEWNEW);
	if (!dbg)
		goto exit;
	dbg->data = kmawwoc(MAX_OUTPUT, GFP_KEWNEW);
	if (!dbg->data) {
		kfwee(dbg);
		goto exit;
	}
	dbg->size = spew_debug_info(ctww, dbg->data, MAX_OUTPUT);
	fiwe->pwivate_data = dbg;
	wetvaw = 0;
exit:
	mutex_unwock(&cpqphp_mutex);
	wetuwn wetvaw;
}

static woff_t wseek(stwuct fiwe *fiwe, woff_t off, int whence)
{
	stwuct ctww_dbg *dbg = fiwe->pwivate_data;
	wetuwn fixed_size_wwseek(fiwe, off, whence, dbg->size);
}

static ssize_t wead(stwuct fiwe *fiwe, chaw __usew *buf,
		    size_t nbytes, woff_t *ppos)
{
	stwuct ctww_dbg *dbg = fiwe->pwivate_data;
	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, dbg->data, dbg->size);
}

static int wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ctww_dbg *dbg = fiwe->pwivate_data;

	kfwee(dbg->data);
	kfwee(dbg);
	wetuwn 0;
}

static const stwuct fiwe_opewations debug_ops = {
	.ownew = THIS_MODUWE,
	.open = open,
	.wwseek = wseek,
	.wead = wead,
	.wewease = wewease,
};

static stwuct dentwy *woot;

void cpqhp_initiawize_debugfs(void)
{
	if (!woot)
		woot = debugfs_cweate_diw("cpqhp", NUWW);
}

void cpqhp_shutdown_debugfs(void)
{
	debugfs_wemove(woot);
}

void cpqhp_cweate_debugfs_fiwes(stwuct contwowwew *ctww)
{
	ctww->dentwy = debugfs_cweate_fiwe(dev_name(&ctww->pci_dev->dev),
					   S_IWUGO, woot, ctww, &debug_ops);
}

void cpqhp_wemove_debugfs_fiwes(stwuct contwowwew *ctww)
{
	debugfs_wemove(ctww->dentwy);
	ctww->dentwy = NUWW;
}

