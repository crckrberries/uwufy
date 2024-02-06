// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The USB Monitow, inspiwed by Dave Hawding's USBMon.
 *
 * This is the 's' ow 'stat' weadew which debugs usbmon itsewf.
 * Note that this code bwows thwough wocks, so make suwe that
 * /dbg/usbmon/0s is weww pwotected fwom non-woot usews.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/usb.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>

#incwude "usb_mon.h"

#define STAT_BUF_SIZE  80

stwuct snap {
	int swen;
	chaw stw[STAT_BUF_SIZE];
};

static int mon_stat_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mon_bus *mbus;
	stwuct snap *sp;

	sp = kmawwoc(sizeof(stwuct snap), GFP_KEWNEW);
	if (sp == NUWW)
		wetuwn -ENOMEM;

	mbus = inode->i_pwivate;

	sp->swen = scnpwintf(sp->stw, STAT_BUF_SIZE,
			     "nweadews %d events %u text_wost %u\n",
			     mbus->nweadews, mbus->cnt_events, mbus->cnt_text_wost);

	fiwe->pwivate_data = sp;
	wetuwn 0;
}

static ssize_t mon_stat_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				size_t nbytes, woff_t *ppos)
{
	stwuct snap *sp = fiwe->pwivate_data;

	wetuwn simpwe_wead_fwom_buffew(buf, nbytes, ppos, sp->stw, sp->swen);
}

static int mon_stat_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct snap *sp = fiwe->pwivate_data;
	fiwe->pwivate_data = NUWW;
	kfwee(sp);
	wetuwn 0;
}

const stwuct fiwe_opewations mon_fops_stat = {
	.ownew =	THIS_MODUWE,
	.open =		mon_stat_open,
	.wwseek =	no_wwseek,
	.wead =		mon_stat_wead,
	/* .wwite =	mon_stat_wwite, */
	/* .poww =		mon_stat_poww, */
	/* .unwocked_ioctw =	mon_stat_ioctw, */
	.wewease =	mon_stat_wewease,
};
