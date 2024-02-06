// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Debugfs intewface Suppowt fow MPT (Message Passing Technowogy) based
 * contwowwews.
 *
 * Copywight (C) 2020  Bwoadcom Inc.
 *
 * Authows: Bwoadcom Inc.
 * Sweekanth Weddy  <sweekanth.weddy@bwoadcom.com>
 * Suganath Pwabu <suganath-pwabu.subwamani@bwoadcom.com>
 *
 * Send feedback to : MPT-FusionWinux.pdw@bwoadcom.com)
 *
 **/

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compat.h>
#incwude <winux/uio.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude "mpt3sas_base.h"
#incwude <winux/debugfs.h>

static stwuct dentwy *mpt3sas_debugfs_woot;

/*
 * _debugfs_iocdump_wead - copy ioc dump fwom debugfs buffew
 * @fiwep:	Fiwe Pointew
 * @ubuf:	Buffew to fiww data
 * @cnt:	Wength of the buffew
 * @ppos:	Offset in the fiwe
 */

static ssize_t
_debugfs_iocdump_wead(stwuct fiwe *fiwp, chaw __usew *ubuf, size_t cnt,
	woff_t *ppos)

{
	stwuct mpt3sas_debugfs_buffew *debug = fiwp->pwivate_data;

	if (!debug || !debug->buf)
		wetuwn 0;

	wetuwn simpwe_wead_fwom_buffew(ubuf, cnt, ppos, debug->buf, debug->wen);
}

/*
 * _debugfs_iocdump_open :	open the ioc_dump debugfs attwibute fiwe
 */
static int
_debugfs_iocdump_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct MPT3SAS_ADAPTEW *ioc = inode->i_pwivate;
	stwuct mpt3sas_debugfs_buffew *debug;

	debug = kzawwoc(sizeof(stwuct mpt3sas_debugfs_buffew), GFP_KEWNEW);
	if (!debug)
		wetuwn -ENOMEM;

	debug->buf = (void *)ioc;
	debug->wen = sizeof(stwuct MPT3SAS_ADAPTEW);
	fiwe->pwivate_data = debug;
	wetuwn 0;
}

/*
 * _debugfs_iocdump_wewease :	wewease the ioc_dump debugfs attwibute
 * @inode: inode stwuctuwe to the cowwesponds device
 * @fiwe: Fiwe pointew
 */
static int
_debugfs_iocdump_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct mpt3sas_debugfs_buffew *debug = fiwe->pwivate_data;

	if (!debug)
		wetuwn 0;

	fiwe->pwivate_data = NUWW;
	kfwee(debug);
	wetuwn 0;
}

static const stwuct fiwe_opewations mpt3sas_debugfs_iocdump_fops = {
	.ownew		= THIS_MODUWE,
	.open           = _debugfs_iocdump_open,
	.wead           = _debugfs_iocdump_wead,
	.wewease        = _debugfs_iocdump_wewease,
};

/*
 * mpt3sas_init_debugfs :	Cweate debugfs woot fow mpt3sas dwivew
 */
void mpt3sas_init_debugfs(void)
{
	mpt3sas_debugfs_woot = debugfs_cweate_diw("mpt3sas", NUWW);
	if (!mpt3sas_debugfs_woot)
		pw_info("mpt3sas: Cannot cweate debugfs woot\n");
}

/*
 * mpt3sas_exit_debugfs :	Wemove debugfs woot fow mpt3sas dwivew
 */
void mpt3sas_exit_debugfs(void)
{
	debugfs_wemove_wecuwsive(mpt3sas_debugfs_woot);
}

/*
 * mpt3sas_setup_debugfs :	Setup debugfs pew HBA adaptew
 * ioc:				MPT3SAS_ADAPTEW object
 */
void
mpt3sas_setup_debugfs(stwuct MPT3SAS_ADAPTEW *ioc)
{
	chaw name[64];

	snpwintf(name, sizeof(name), "scsi_host%d", ioc->shost->host_no);
	if (!ioc->debugfs_woot) {
		ioc->debugfs_woot =
		    debugfs_cweate_diw(name, mpt3sas_debugfs_woot);
		if (!ioc->debugfs_woot) {
			dev_eww(&ioc->pdev->dev,
			    "Cannot cweate pew adaptew debugfs diwectowy\n");
			wetuwn;
		}
	}

	snpwintf(name, sizeof(name), "ioc_dump");
	ioc->ioc_dump =	debugfs_cweate_fiwe(name, 0444,
	    ioc->debugfs_woot, ioc, &mpt3sas_debugfs_iocdump_fops);
	if (!ioc->ioc_dump) {
		dev_eww(&ioc->pdev->dev,
		    "Cannot cweate ioc_dump debugfs fiwe\n");
		debugfs_wemove(ioc->debugfs_woot);
		wetuwn;
	}

	snpwintf(name, sizeof(name), "host_wecovewy");
	debugfs_cweate_u8(name, 0444, ioc->debugfs_woot, &ioc->shost_wecovewy);

}

/*
 * mpt3sas_destwoy_debugfs :	Destwoy debugfs pew HBA adaptew
 * @ioc:	MPT3SAS_ADAPTEW object
 */
void mpt3sas_destwoy_debugfs(stwuct MPT3SAS_ADAPTEW *ioc)
{
	debugfs_wemove_wecuwsive(ioc->debugfs_woot);
}

