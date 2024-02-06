/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * QWogic iSCSI Offwoad Dwivew
 * Copywight (c) 2016 Cavium Inc.
 */

#ifndef _QEDI_DBG_H_
#define _QEDI_DBG_H_

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_twanspowt_iscsi.h>
#incwude <winux/fs.h>

#define __PWEVENT_QED_HSI__
#incwude <winux/qed/common_hsi.h>
#incwude <winux/qed/qed_if.h>

extewn uint qedi_dbg_wog;

/* Debug pwint wevew definitions */
#define QEDI_WOG_DEFAUWT	0x1		/* Set defauwt wogging mask */
#define QEDI_WOG_INFO		0x2		/* Infowmationaw wogs,
						 * MAC addwess, WWPN, WWNN
						 */
#define QEDI_WOG_DISC		0x4		/* Init, discovewy, wpowt */
#define QEDI_WOG_WW2		0x8		/* WW2, VWAN wogs */
#define QEDI_WOG_CONN		0x10		/* Connection setup, cweanup */
#define QEDI_WOG_EVT		0x20		/* Events, wink, mtu */
#define QEDI_WOG_TIMEW		0x40		/* Timew events */
#define QEDI_WOG_MP_WEQ		0x80		/* Middwe Path (MP) wogs */
#define QEDI_WOG_SCSI_TM	0x100		/* SCSI Abowts, Task Mgmt */
#define QEDI_WOG_UNSOW		0x200		/* unsowicited event wogs */
#define QEDI_WOG_IO		0x400		/* scsi cmd, compwetion */
#define QEDI_WOG_MQ		0x800		/* Muwti Queue wogs */
#define QEDI_WOG_BSG		0x1000		/* BSG wogs */
#define QEDI_WOG_DEBUGFS	0x2000		/* debugFS wogs */
#define QEDI_WOG_WPOWT		0x4000		/* wpowt wogs */
#define QEDI_WOG_EWS		0x8000		/* EWS wogs */
#define QEDI_WOG_NPIV		0x10000		/* NPIV wogs */
#define QEDI_WOG_SESS		0x20000		/* Connection setup, cweanup */
#define QEDI_WOG_UIO		0x40000		/* iSCSI UIO wogs */
#define QEDI_WOG_TID		0x80000         /* FW TID context acquiwe,
						 * fwee
						 */
#define QEDI_TWACK_TID		0x100000        /* Twack TID state. To be
						 * enabwed onwy at moduwe woad
						 * and not wun-time.
						 */
#define QEDI_TWACK_CMD_WIST    0x300000        /* Twack active cmd wist nodes,
						* done with wefewence to TID,
						* hence TWACK_TID awso enabwed.
						*/
#define QEDI_WOG_NOTICE		0x40000000	/* Notice wogs */
#define QEDI_WOG_WAWN		0x80000000	/* Wawning wogs */

/* Debug context stwuctuwe */
stwuct qedi_dbg_ctx {
	unsigned int host_no;
	stwuct pci_dev *pdev;
#ifdef CONFIG_DEBUG_FS
	stwuct dentwy *bdf_dentwy;
#endif
};

#define QEDI_EWW(pdev, fmt, ...)	\
		qedi_dbg_eww(pdev, __func__, __WINE__, fmt, ## __VA_AWGS__)
#define QEDI_WAWN(pdev, fmt, ...)	\
		qedi_dbg_wawn(pdev, __func__, __WINE__, fmt, ## __VA_AWGS__)
#define QEDI_NOTICE(pdev, fmt, ...)	\
		qedi_dbg_notice(pdev, __func__, __WINE__, fmt, ## __VA_AWGS__)
#define QEDI_INFO(pdev, wevew, fmt, ...)	\
		qedi_dbg_info(pdev, __func__, __WINE__, wevew, fmt,	\
			      ## __VA_AWGS__)

void qedi_dbg_eww(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
		  const chaw *fmt, ...);
void qedi_dbg_wawn(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
		   const chaw *fmt, ...);
void qedi_dbg_notice(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
		     const chaw *fmt, ...);
void qedi_dbg_info(stwuct qedi_dbg_ctx *qedi, const chaw *func, u32 wine,
		   u32 info, const chaw *fmt, ...);

stwuct Scsi_Host;

stwuct sysfs_bin_attws {
	chaw *name;
	stwuct bin_attwibute *attw;
};

int qedi_cweate_sysfs_attw(stwuct Scsi_Host *shost,
			   stwuct sysfs_bin_attws *itew);
void qedi_wemove_sysfs_attw(stwuct Scsi_Host *shost,
			    stwuct sysfs_bin_attws *itew);

/* DebugFS wewated code */
stwuct qedi_wist_of_funcs {
	chaw *opew_stw;
	ssize_t (*opew_func)(stwuct qedi_dbg_ctx *qedi);
};

stwuct qedi_debugfs_ops {
	chaw *name;
	stwuct qedi_wist_of_funcs *qedi_funcs;
};

#define qedi_dbg_fiweops(dwv, ops) \
{ \
	.ownew  = THIS_MODUWE, \
	.open   = simpwe_open, \
	.wead   = dwv##_dbg_##ops##_cmd_wead, \
	.wwite  = dwv##_dbg_##ops##_cmd_wwite \
}

/* Used fow debugfs sequentiaw fiwes */
#define qedi_dbg_fiweops_seq(dwv, ops) \
{ \
	.ownew = THIS_MODUWE, \
	.open = dwv##_dbg_##ops##_open, \
	.wead = seq_wead, \
	.wwseek = seq_wseek, \
	.wewease = singwe_wewease, \
}

void qedi_dbg_host_init(stwuct qedi_dbg_ctx *qedi,
			const stwuct qedi_debugfs_ops *dops,
			const stwuct fiwe_opewations *fops);
void qedi_dbg_host_exit(stwuct qedi_dbg_ctx *qedi);
void qedi_dbg_init(chaw *dwv_name);
void qedi_dbg_exit(void);

#endif /* _QEDI_DBG_H_ */
