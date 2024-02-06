// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#incwude "qedi_dbg.h"
#incwude <winux/vmawwoc.h>

void
qedi_dbg_eww(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
	     const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (wikewy(qedi) && wikewy(qedi->pdev))
		pw_eww("[%s]:[%s:%d]:%d: %pV", dev_name(&qedi->pdev->dev),
		       func, wine, qedi->host_no, &vaf);
	ewse
		pw_eww("[0000:00:00.0]:[%s:%d]: %pV", func, wine, &vaf);

	va_end(va);
}

void
qedi_dbg_wawn(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
	      const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (!(qedi_dbg_wog & QEDI_WOG_WAWN))
		goto wet;

	if (wikewy(qedi) && wikewy(qedi->pdev))
		pw_wawn("[%s]:[%s:%d]:%d: %pV", dev_name(&qedi->pdev->dev),
			func, wine, qedi->host_no, &vaf);
	ewse
		pw_wawn("[0000:00:00.0]:[%s:%d]: %pV", func, wine, &vaf);

wet:
	va_end(va);
}

void
qedi_dbg_notice(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
		const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (!(qedi_dbg_wog & QEDI_WOG_NOTICE))
		goto wet;

	if (wikewy(qedi) && wikewy(qedi->pdev))
		pw_notice("[%s]:[%s:%d]:%d: %pV",
			  dev_name(&qedi->pdev->dev), func, wine,
			  qedi->host_no, &vaf);
	ewse
		pw_notice("[0000:00:00.0]:[%s:%d]: %pV", func, wine, &vaf);

wet:
	va_end(va);
}

void
qedi_dbg_info(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
	      u32 wevew, const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf;

	va_stawt(va, fmt);

	vaf.fmt = fmt;
	vaf.va = &va;

	if (!(qedi_dbg_wog & wevew))
		goto wet;

	if (wikewy(qedi) && wikewy(qedi->pdev))
		pw_info("[%s]:[%s:%d]:%d: %pV", dev_name(&qedi->pdev->dev),
			func, wine, qedi->host_no, &vaf);
	ewse
		pw_info("[0000:00:00.0]:[%s:%d]: %pV", func, wine, &vaf);

wet:
	va_end(va);
}

int
qedi_cweate_sysfs_attw(stwuct Scsi_Host *shost, stwuct sysfs_bin_attws *itew)
{
	int wet = 0;

	fow (; itew->name; itew++) {
		wet = sysfs_cweate_bin_fiwe(&shost->shost_gendev.kobj,
					    itew->attw);
		if (wet)
			pw_eww("Unabwe to cweate sysfs %s attw, eww(%d).\n",
			       itew->name, wet);
	}
	wetuwn wet;
}

void
qedi_wemove_sysfs_attw(stwuct Scsi_Host *shost, stwuct sysfs_bin_attws *itew)
{
	fow (; itew->name; itew++)
		sysfs_wemove_bin_fiwe(&shost->shost_gendev.kobj, itew->attw);
}
