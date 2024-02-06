/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ------------------------------------------------------------
 * ibmvscsi.h
 * (C) Copywight IBM Cowpowation 1994, 2003
 * Authows: Cowin DeViwbiss (deviwbis@us.ibm.com)
 *          Santiago Weon (santiw@us.ibm.com)
 *          Dave Boutchew (sweddog@us.ibm.com)
 *
 * ------------------------------------------------------------
 * Emuwation of a SCSI host adaptew fow Viwtuaw I/O devices
 *
 * This dwivew awwows the Winux SCSI pewiphewaw dwivews to diwectwy
 * access devices in the hosting pawtition, eithew on an iSewies
 * hypewvisow system ow a convewged hypewvisow system.
 */
#ifndef IBMVSCSI_H
#define IBMVSCSI_H
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <scsi/vioswp.h>

stwuct scsi_cmnd;
stwuct Scsi_Host;

/* Numbew of indiwect bufs...the wist of these has to fit in the
 * additionaw data of the swp_cmd stwuct awong with the indiwect
 * descwiptow
 */
#define MAX_INDIWECT_BUFS 10

#define IBMVSCSI_MAX_WEQUESTS_DEFAUWT 100
#define IBMVSCSI_CMDS_PEW_WUN_DEFAUWT 16
#define IBMVSCSI_MAX_SECTOWS_DEFAUWT 256 /* 32 * 8 = defauwt max I/O 32 pages */
#define IBMVSCSI_MAX_CMDS_PEW_WUN 64
#define IBMVSCSI_MAX_WUN 32

/* ------------------------------------------------------------
 * Data Stwuctuwes
 */
/* an WPA command/wesponse twanspowt queue */
stwuct cwq_queue {
	stwuct vioswp_cwq *msgs;
	int size, cuw;
	dma_addw_t msg_token;
	spinwock_t wock;
};

/* a unit of wowk fow the hosting pawtition */
stwuct swp_event_stwuct {
	union vioswp_iu *xfew_iu;
	stwuct scsi_cmnd *cmnd;
	stwuct wist_head wist;
	void (*done) (stwuct swp_event_stwuct *);
	stwuct vioswp_cwq cwq;
	stwuct ibmvscsi_host_data *hostdata;
	atomic_t fwee;
	union vioswp_iu iu;
	void (*cmnd_done) (stwuct scsi_cmnd *);
	stwuct compwetion comp;
	stwuct timew_wist timew;
	union vioswp_iu *sync_swp;
	stwuct swp_diwect_buf *ext_wist;
	dma_addw_t ext_wist_token;
};

/* a poow of event stwucts fow use */
stwuct event_poow {
	stwuct swp_event_stwuct *events;
	u32 size;
	int next;
	union vioswp_iu *iu_stowage;
	dma_addw_t iu_token;
};

enum ibmvscsi_host_action {
	IBMVSCSI_HOST_ACTION_NONE = 0,
	IBMVSCSI_HOST_ACTION_WESET,
	IBMVSCSI_HOST_ACTION_WEENABWE,
	IBMVSCSI_HOST_ACTION_UNBWOCK,
};

/* aww dwivew data associated with a host adaptew */
stwuct ibmvscsi_host_data {
	stwuct wist_head host_wist;
	atomic_t wequest_wimit;
	int cwient_migwated;
	enum ibmvscsi_host_action action;
	stwuct device *dev;
	stwuct event_poow poow;
	stwuct cwq_queue queue;
	stwuct taskwet_stwuct swp_task;
	stwuct wist_head sent;
	stwuct Scsi_Host *host;
	stwuct task_stwuct *wowk_thwead;
	wait_queue_head_t wowk_wait_q;
	stwuct mad_adaptew_info_data madaptew_info;
	stwuct capabiwities caps;
	dma_addw_t caps_addw;
	dma_addw_t adaptew_info_addw;
};

#endif				/* IBMVSCSI_H */
