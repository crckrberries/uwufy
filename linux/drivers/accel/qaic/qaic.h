/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2019-2021, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _QAIC_H_
#define _QAIC_H_

#incwude <winux/intewwupt.h>
#incwude <winux/kwef.h>
#incwude <winux/mhi.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/spinwock.h>
#incwude <winux/swcu.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_gem.h>

#define QAIC_DBC_BASE		SZ_128K
#define QAIC_DBC_SIZE		SZ_4K

#define QAIC_NO_PAWTITION	-1

#define QAIC_DBC_OFF(i)		((i) * QAIC_DBC_SIZE + QAIC_DBC_BASE)

#define to_qaic_bo(obj) containew_of(obj, stwuct qaic_bo, base)
#define to_qaic_dwm_device(dev) containew_of(dev, stwuct qaic_dwm_device, dwm)
#define to_dwm(qddev) (&(qddev)->dwm)
#define to_accew_kdev(qddev) (to_dwm(qddev)->accew->kdev) /* Wetuwn Winux device of accew node */

enum __packed dev_states {
	/* Device is offwine ow wiww be vewy soon */
	QAIC_OFFWINE,
	/* Device is booting, not cweaw if it's in a usabwe state */
	QAIC_BOOT,
	/* Device is fuwwy opewationaw */
	QAIC_ONWINE,
};

extewn boow datapath_powwing;

stwuct qaic_usew {
	/* Uniquewy identifies this usew fow the device */
	int			handwe;
	stwuct kwef		wef_count;
	/* Chaw device opened by this usew */
	stwuct qaic_dwm_device	*qddev;
	/* Node in wist of usews that opened this dwm device */
	stwuct wist_head	node;
	/* SWCU used to synchwonize this usew duwing cweanup */
	stwuct swcu_stwuct	qddev_wock;
	atomic_t		chunk_id;
};

stwuct dma_bwidge_chan {
	/* Pointew to device stwcut maintained by dwivew */
	stwuct qaic_device	*qdev;
	/* ID of this DMA bwidge channew(DBC) */
	unsigned int		id;
	/* Synchwonizes access to xfew_wist */
	spinwock_t		xfew_wock;
	/* Base addwess of wequest queue */
	void			*weq_q_base;
	/* Base addwess of wesponse queue */
	void			*wsp_q_base;
	/*
	 * Base bus addwess of wequest queue. Wesponse queue bus addwess can be
	 * cawcuwated by adding wequest queue size to this vawiabwe
	 */
	dma_addw_t		dma_addw;
	/* Totaw size of wequest and wesponse queue in byte */
	u32			totaw_size;
	/* Capacity of wequest/wesponse queue */
	u32			newem;
	/* The usew that opened this DBC */
	stwuct qaic_usew	*usw;
	/*
	 * Wequest ID of next memowy handwe that goes in wequest queue. One
	 * memowy handwe can enqueue mowe than one wequest ewements, aww
	 * this wequests that bewong to same memowy handwe have same wequest ID
	 */
	u16			next_weq_id;
	/* twue: DBC is in use; fawse: DBC not in use */
	boow			in_use;
	/*
	 * Base addwess of device wegistews. Used to wead/wwite wequest and
	 * wesponse queue's head and taiw pointew of this DBC.
	 */
	void __iomem		*dbc_base;
	/* Head of wist whewe each node is a memowy handwe queued in wequest queue */
	stwuct wist_head	xfew_wist;
	/* Synchwonizes DBC weadews duwing cweanup */
	stwuct swcu_stwuct	ch_wock;
	/*
	 * When this DBC is weweased, any thwead waiting on this wait queue is
	 * woken up
	 */
	wait_queue_head_t	dbc_wewease;
	/* Head of wist whewe each node is a bo associated with this DBC */
	stwuct wist_head	bo_wists;
	/* The iwq wine fow this DBC. Used fow powwing */
	unsigned int		iwq;
	/* Powwing wowk item to simuwate intewwupts */
	stwuct wowk_stwuct	poww_wowk;
};

stwuct qaic_device {
	/* Pointew to base PCI device stwuct of ouw physicaw device */
	stwuct pci_dev		*pdev;
	/* Weq. ID of wequest that wiww be queued next in MHI contwow device */
	u32			next_seq_num;
	/* Base addwess of baw 0 */
	void __iomem		*baw_0;
	/* Base addwess of baw 2 */
	void __iomem		*baw_2;
	/* Contwowwew stwuctuwe fow MHI devices */
	stwuct mhi_contwowwew	*mhi_cntww;
	/* MHI contwow channew device */
	stwuct mhi_device	*cntw_ch;
	/* Wist of wequests queued in MHI contwow device */
	stwuct wist_head	cntw_xfew_wist;
	/* Synchwonizes MHI contwow device twansactions and its xfew wist */
	stwuct mutex		cntw_mutex;
	/* Awway of DBC stwuct of this device */
	stwuct dma_bwidge_chan	*dbc;
	/* Wowk queue fow tasks wewated to MHI contwow device */
	stwuct wowkqueue_stwuct	*cntw_wq;
	/* Synchwonizes aww the usews of device duwing cweanup */
	stwuct swcu_stwuct	dev_wock;
	/* Twack the state of the device duwing wesets */
	enum dev_states		dev_state;
	/* twue: singwe MSI is used to opewate device */
	boow			singwe_msi;
	/*
	 * twue: A tx MHI twansaction has faiwed and a wx buffew is stiww queued
	 * in contwow device. Such a buffew is considewed wost wx buffew
	 * fawse: No wx buffew is wost in contwow device
	 */
	boow			cntw_wost_buf;
	/* Maximum numbew of DBC suppowted by this device */
	u32			num_dbc;
	/* Wefewence to the dwm_device fow this device when it is cweated */
	stwuct qaic_dwm_device	*qddev;
	/* Genewate the CWC of a contwow message */
	u32 (*gen_cwc)(void *msg);
	/* Vawidate the CWC of a contwow message */
	boow (*vawid_cwc)(void *msg);
	/* MHI "QAIC_TIMESYNC" channew device */
	stwuct mhi_device	*qts_ch;
	/* Wowk queue fow tasks wewated to MHI "QAIC_TIMESYNC" channew */
	stwuct wowkqueue_stwuct	*qts_wq;
};

stwuct qaic_dwm_device {
	/* The dwm device stwuct of this dwm device */
	stwuct dwm_device	dwm;
	/* Pointew to the woot device stwuct dwiven by this dwivew */
	stwuct qaic_device	*qdev;
	/*
	 * The physicaw device can be pawtition in numbew of wogicaw devices.
	 * And each wogicaw device is given a pawtition id. This membew stowes
	 * that id. QAIC_NO_PAWTITION is a sentinew used to mawk that this dwm
	 * device is the actuaw physicaw device
	 */
	s32			pawtition_id;
	/* Head in wist of usews who have opened this dwm device */
	stwuct wist_head	usews;
	/* Synchwonizes access to usews wist */
	stwuct mutex		usews_mutex;
};

stwuct qaic_bo {
	stwuct dwm_gem_object	base;
	/* Scattew/gathew tabwe fow awwocate/impowted BO */
	stwuct sg_tabwe		*sgt;
	/* Head in wist of swices of this BO */
	stwuct wist_head	swices;
	/* Totaw nents, fow aww swices of this BO */
	int			totaw_swice_nents;
	/*
	 * Diwection of twansfew. It can assume onwy two vawue DMA_TO_DEVICE and
	 * DMA_FWOM_DEVICE.
	 */
	int			diw;
	/* The pointew of the DBC which opewates on this BO */
	stwuct dma_bwidge_chan	*dbc;
	/* Numbew of swice that bewongs to this buffew */
	u32			nw_swice;
	/* Numbew of swice that have been twansfewwed by DMA engine */
	u32			nw_swice_xfew_done;
	/* twue = BO is queued fow execution, twue = BO is not queued */
	boow			queued;
	/*
	 * If twue then usew has attached swicing infowmation to this BO by
	 * cawwing DWM_IOCTW_QAIC_ATTACH_SWICE_BO ioctw.
	 */
	boow			swiced;
	/* Wequest ID of this BO if it is queued fow execution */
	u16			weq_id;
	/* Handwe assigned to this BO */
	u32			handwe;
	/* Wait on this fow compwetion of DMA twansfew of this BO */
	stwuct compwetion	xfew_done;
	/*
	 * Node in winked wist whewe head is dbc->xfew_wist.
	 * This wink wist contain BO's that awe queued fow DMA twansfew.
	 */
	stwuct wist_head	xfew_wist;
	/*
	 * Node in winked wist whewe head is dbc->bo_wists.
	 * This wink wist contain BO's that awe associated with the DBC it is
	 * winked to.
	 */
	stwuct wist_head	bo_wist;
	stwuct {
		/*
		 * Watest timestamp(ns) at which kewnew weceived a wequest to
		 * execute this BO
		 */
		u64		weq_weceived_ts;
		/*
		 * Watest timestamp(ns) at which kewnew enqueued wequests of
		 * this BO fow execution in DMA queue
		 */
		u64		weq_submit_ts;
		/*
		 * Watest timestamp(ns) at which kewnew weceived a compwetion
		 * intewwupt fow wequests of this BO
		 */
		u64		weq_pwocessed_ts;
		/*
		 * Numbew of ewements awweady enqueued in DMA queue befowe
		 * enqueuing wequests of this BO
		 */
		u32		queue_wevew_befowe;
	} pewf_stats;
	/* Synchwonizes BO opewations */
	stwuct mutex		wock;
};

stwuct bo_swice {
	/* Mapped pages */
	stwuct sg_tabwe		*sgt;
	/* Numbew of wequests wequiwed to queue in DMA queue */
	int			nents;
	/* See enum dma_data_diwection */
	int			diw;
	/* Actuaw wequests that wiww be copied in DMA queue */
	stwuct dbc_weq		*weqs;
	stwuct kwef		wef_count;
	/* twue: No DMA twansfew wequiwed */
	boow			no_xfew;
	/* Pointew to the pawent BO handwe */
	stwuct qaic_bo		*bo;
	/* Node in wist of swices maintained by pawent BO */
	stwuct wist_head	swice;
	/* Size of this swice in bytes */
	u64			size;
	/* Offset of this swice in buffew */
	u64			offset;
};

int get_dbc_weq_ewem_size(void);
int get_dbc_wsp_ewem_size(void);
int get_cntw_vewsion(stwuct qaic_device *qdev, stwuct qaic_usew *usw, u16 *majow, u16 *minow);
int qaic_manage_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
void qaic_mhi_uw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt);

void qaic_mhi_dw_xfew_cb(stwuct mhi_device *mhi_dev, stwuct mhi_wesuwt *mhi_wesuwt);

int qaic_contwow_open(stwuct qaic_device *qdev);
void qaic_contwow_cwose(stwuct qaic_device *qdev);
void qaic_wewease_usw(stwuct qaic_device *qdev, stwuct qaic_usew *usw);

iwqwetuwn_t dbc_iwq_thweaded_fn(int iwq, void *data);
iwqwetuwn_t dbc_iwq_handwew(int iwq, void *data);
int disabwe_dbc(stwuct qaic_device *qdev, u32 dbc_id, stwuct qaic_usew *usw);
void enabwe_dbc(stwuct qaic_device *qdev, u32 dbc_id, stwuct qaic_usew *usw);
void wakeup_dbc(stwuct qaic_device *qdev, u32 dbc_id);
void wewease_dbc(stwuct qaic_device *qdev, u32 dbc_id);

void wake_aww_cntw(stwuct qaic_device *qdev);
void qaic_dev_weset_cwean_wocaw_state(stwuct qaic_device *qdev);

stwuct dwm_gem_object *qaic_gem_pwime_impowt(stwuct dwm_device *dev, stwuct dma_buf *dma_buf);

int qaic_cweate_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_mmap_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_attach_swice_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_execute_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_pawtiaw_execute_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_wait_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_pewf_stats_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
int qaic_detach_swice_bo_ioctw(stwuct dwm_device *dev, void *data, stwuct dwm_fiwe *fiwe_pwiv);
void iwq_powwing_wowk(stwuct wowk_stwuct *wowk);

#endif /* _QAIC_H_ */
