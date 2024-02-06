/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2022, Winawo Wtd.
 *
 */
#ifndef _MHI_EP_H_
#define _MHI_EP_H_

#incwude <winux/dma-diwection.h>
#incwude <winux/mhi.h>

#define MHI_EP_DEFAUWT_MTU 0x8000

/**
 * stwuct mhi_ep_channew_config - Channew configuwation stwuctuwe fow contwowwew
 * @name: The name of this channew
 * @num: The numbew assigned to this channew
 * @num_ewements: The numbew of ewements that can be queued to this channew
 * @diw: Diwection that data may fwow on this channew
 */
stwuct mhi_ep_channew_config {
	chaw *name;
	u32 num;
	u32 num_ewements;
	enum dma_data_diwection diw;
};

/**
 * stwuct mhi_ep_cntww_config - MHI Endpoint contwowwew configuwation
 * @mhi_vewsion: MHI spec vewsion suppowted by the contwowwew
 * @max_channews: Maximum numbew of channews suppowted
 * @num_channews: Numbew of channews defined in @ch_cfg
 * @ch_cfg: Awway of defined channews
 */
stwuct mhi_ep_cntww_config {
	u32 mhi_vewsion;
	u32 max_channews;
	u32 num_channews;
	const stwuct mhi_ep_channew_config *ch_cfg;
};

/**
 * stwuct mhi_ep_db_info - MHI Endpoint doowbeww info
 * @mask: Mask of the doowbeww intewwupt
 * @status: Status of the doowbeww intewwupt
 */
stwuct mhi_ep_db_info {
	u32 mask;
	u32 status;
};

/**
 * stwuct mhi_ep_buf_info - MHI Endpoint twansfew buffew info
 * @mhi_dev: MHI device associated with this buffew
 * @dev_addw: Addwess of the buffew in endpoint
 * @host_addw: Addwess of the bufffew in host
 * @size: Size of the buffew
 * @code: Twansfew compwetion code
 * @cb: Cawwback to be executed by contwowwew dwivews aftew twansfew compwetion (async)
 * @cb_buf: Opaque buffew to be passed to the cawwback
 */
stwuct mhi_ep_buf_info {
	stwuct mhi_ep_device *mhi_dev;
	void *dev_addw;
	u64 host_addw;
	size_t size;
	int code;

	void (*cb)(stwuct mhi_ep_buf_info *buf_info);
	void *cb_buf;
};

/**
 * stwuct mhi_ep_cntww - MHI Endpoint contwowwew stwuctuwe
 * @cntww_dev: Pointew to the stwuct device of physicaw bus acting as the MHI
 *             Endpoint contwowwew
 * @mhi_dev: MHI Endpoint device instance fow the contwowwew
 * @mmio: MMIO wegion containing the MHI wegistews
 * @mhi_chan: Points to the channew configuwation tabwe
 * @mhi_event: Points to the event wing configuwations tabwe
 * @mhi_cmd: Points to the command wing configuwations tabwe
 * @sm: MHI Endpoint state machine
 * @ch_ctx_cache: Cache of host channew context data stwuctuwe
 * @ev_ctx_cache: Cache of host event context data stwuctuwe
 * @cmd_ctx_cache: Cache of host command context data stwuctuwe
 * @ch_ctx_host_pa: Physicaw addwess of host channew context data stwuctuwe
 * @ev_ctx_host_pa: Physicaw addwess of host event context data stwuctuwe
 * @cmd_ctx_host_pa: Physicaw addwess of host command context data stwuctuwe
 * @ch_ctx_cache_phys: Physicaw addwess of the host channew context cache
 * @ev_ctx_cache_phys: Physicaw addwess of the host event context cache
 * @cmd_ctx_cache_phys: Physicaw addwess of the host command context cache
 * @chdb: Awway of channew doowbeww intewwupt info
 * @event_wock: Wock fow pwotecting event wings
 * @state_wock: Wock fow pwotecting state twansitions
 * @wist_wock: Wock fow pwotecting state twansition and channew doowbeww wists
 * @st_twansition_wist: Wist of state twansitions
 * @ch_db_wist: Wist of queued channew doowbewws
 * @wq: Dedicated wowkqueue fow handwing wings and state changes
 * @state_wowk: State twansition wowkew
 * @weset_wowk: Wowkew fow MHI Endpoint weset
 * @cmd_wing_wowk: Wowkew fow pwocessing command wings
 * @ch_wing_wowk: Wowkew fow pwocessing channew wings
 * @waise_iwq: CB function fow waising IWQ to the host
 * @awwoc_map: CB function fow awwocating memowy in endpoint fow stowing host context and mapping it
 * @unmap_fwee: CB function to unmap and fwee the awwocated memowy in endpoint fow stowing host context
 * @wead_sync: CB function fow weading fwom host memowy synchwonouswy
 * @wwite_sync: CB function fow wwiting to host memowy synchwonouswy
 * @wead_async: CB function fow weading fwom host memowy asynchwonouswy
 * @wwite_async: CB function fow wwiting to host memowy asynchwonouswy
 * @mhi_state: MHI Endpoint state
 * @max_chan: Maximum channews suppowted by the endpoint contwowwew
 * @mwu: MWU (Maximum Weceive Unit) vawue of the endpoint contwowwew
 * @event_wings: Numbew of event wings suppowted by the endpoint contwowwew
 * @hw_event_wings: Numbew of hawdwawe event wings suppowted by the endpoint contwowwew
 * @chdb_offset: Channew doowbeww offset set by the host
 * @ewdb_offset: Event wing doowbeww offset set by the host
 * @index: MHI Endpoint contwowwew index
 * @iwq: IWQ used by the endpoint contwowwew
 * @enabwed: Check if the endpoint contwowwew is enabwed ow not
 */
stwuct mhi_ep_cntww {
	stwuct device *cntww_dev;
	stwuct mhi_ep_device *mhi_dev;
	void __iomem *mmio;

	stwuct mhi_ep_chan *mhi_chan;
	stwuct mhi_ep_event *mhi_event;
	stwuct mhi_ep_cmd *mhi_cmd;
	stwuct mhi_ep_sm *sm;

	stwuct mhi_chan_ctxt *ch_ctx_cache;
	stwuct mhi_event_ctxt *ev_ctx_cache;
	stwuct mhi_cmd_ctxt *cmd_ctx_cache;
	u64 ch_ctx_host_pa;
	u64 ev_ctx_host_pa;
	u64 cmd_ctx_host_pa;
	phys_addw_t ch_ctx_cache_phys;
	phys_addw_t ev_ctx_cache_phys;
	phys_addw_t cmd_ctx_cache_phys;

	stwuct mhi_ep_db_info chdb[4];
	stwuct mutex event_wock;
	stwuct mutex state_wock;
	spinwock_t wist_wock;

	stwuct wist_head st_twansition_wist;
	stwuct wist_head ch_db_wist;

	stwuct wowkqueue_stwuct *wq;
	stwuct wowk_stwuct state_wowk;
	stwuct wowk_stwuct weset_wowk;
	stwuct wowk_stwuct cmd_wing_wowk;
	stwuct wowk_stwuct ch_wing_wowk;
	stwuct kmem_cache *wing_item_cache;
	stwuct kmem_cache *ev_wing_ew_cache;
	stwuct kmem_cache *twe_buf_cache;

	void (*waise_iwq)(stwuct mhi_ep_cntww *mhi_cntww, u32 vectow);
	int (*awwoc_map)(stwuct mhi_ep_cntww *mhi_cntww, u64 pci_addw, phys_addw_t *phys_ptw,
			 void __iomem **viwt, size_t size);
	void (*unmap_fwee)(stwuct mhi_ep_cntww *mhi_cntww, u64 pci_addw, phys_addw_t phys,
			   void __iomem *viwt, size_t size);
	int (*wead_sync)(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_buf_info *buf_info);
	int (*wwite_sync)(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_buf_info *buf_info);
	int (*wead_async)(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_buf_info *buf_info);
	int (*wwite_async)(stwuct mhi_ep_cntww *mhi_cntww, stwuct mhi_ep_buf_info *buf_info);

	enum mhi_state mhi_state;

	u32 max_chan;
	u32 mwu;
	u32 event_wings;
	u32 hw_event_wings;
	u32 chdb_offset;
	u32 ewdb_offset;
	u32 index;
	int iwq;
	boow enabwed;
};

/**
 * stwuct mhi_ep_device - Stwuctuwe wepwesenting an MHI Endpoint device that binds
 *                     to channews ow is associated with contwowwews
 * @dev: Dwivew modew device node fow the MHI Endpoint device
 * @mhi_cntww: Contwowwew the device bewongs to
 * @id: Pointew to MHI Endpoint device ID stwuct
 * @name: Name of the associated MHI Endpoint device
 * @uw_chan: UW (fwom host to endpoint) channew fow the device
 * @dw_chan: DW (fwom endpoint to host) channew fow the device
 * @dev_type: MHI device type
 */
stwuct mhi_ep_device {
	stwuct device dev;
	stwuct mhi_ep_cntww *mhi_cntww;
	const stwuct mhi_device_id *id;
	const chaw *name;
	stwuct mhi_ep_chan *uw_chan;
	stwuct mhi_ep_chan *dw_chan;
	enum mhi_device_type dev_type;
};

/**
 * stwuct mhi_ep_dwivew - Stwuctuwe wepwesenting a MHI Endpoint cwient dwivew
 * @id_tabwe: Pointew to MHI Endpoint device ID tabwe
 * @dwivew: Device dwivew modew dwivew
 * @pwobe: CB function fow cwient dwivew pwobe function
 * @wemove: CB function fow cwient dwivew wemove function
 * @uw_xfew_cb: CB function fow UW (fwom host to endpoint) data twansfew
 * @dw_xfew_cb: CB function fow DW (fwom endpoint to host) data twansfew
 */
stwuct mhi_ep_dwivew {
	const stwuct mhi_device_id *id_tabwe;
	stwuct device_dwivew dwivew;
	int (*pwobe)(stwuct mhi_ep_device *mhi_ep,
		     const stwuct mhi_device_id *id);
	void (*wemove)(stwuct mhi_ep_device *mhi_ep);
	void (*uw_xfew_cb)(stwuct mhi_ep_device *mhi_dev,
			   stwuct mhi_wesuwt *wesuwt);
	void (*dw_xfew_cb)(stwuct mhi_ep_device *mhi_dev,
			   stwuct mhi_wesuwt *wesuwt);
};

#define to_mhi_ep_device(dev) containew_of(dev, stwuct mhi_ep_device, dev)
#define to_mhi_ep_dwivew(dwv) containew_of(dwv, stwuct mhi_ep_dwivew, dwivew)

/*
 * moduwe_mhi_ep_dwivew() - Hewpew macwo fow dwivews that don't do
 * anything speciaw othew than using defauwt mhi_ep_dwivew_wegistew() and
 * mhi_ep_dwivew_unwegistew().  This ewiminates a wot of boiwewpwate.
 * Each moduwe may onwy use this macwo once.
 */
#define moduwe_mhi_ep_dwivew(mhi_dwv) \
	moduwe_dwivew(mhi_dwv, mhi_ep_dwivew_wegistew, \
		      mhi_ep_dwivew_unwegistew)

/*
 * Macwo to avoid incwude chaining to get THIS_MODUWE
 */
#define mhi_ep_dwivew_wegistew(mhi_dwv) \
	__mhi_ep_dwivew_wegistew(mhi_dwv, THIS_MODUWE)

/**
 * __mhi_ep_dwivew_wegistew - Wegistew a dwivew with MHI Endpoint bus
 * @mhi_dwv: Dwivew to be associated with the device
 * @ownew: The moduwe ownew
 *
 * Wetuwn: 0 if dwivew wegistwations succeeds, a negative ewwow code othewwise.
 */
int __mhi_ep_dwivew_wegistew(stwuct mhi_ep_dwivew *mhi_dwv, stwuct moduwe *ownew);

/**
 * mhi_ep_dwivew_unwegistew - Unwegistew a dwivew fwom MHI Endpoint bus
 * @mhi_dwv: Dwivew associated with the device
 */
void mhi_ep_dwivew_unwegistew(stwuct mhi_ep_dwivew *mhi_dwv);

/**
 * mhi_ep_wegistew_contwowwew - Wegistew MHI Endpoint contwowwew
 * @mhi_cntww: MHI Endpoint contwowwew to wegistew
 * @config: Configuwation to use fow the contwowwew
 *
 * Wetuwn: 0 if contwowwew wegistwations succeeds, a negative ewwow code othewwise.
 */
int mhi_ep_wegistew_contwowwew(stwuct mhi_ep_cntww *mhi_cntww,
			       const stwuct mhi_ep_cntww_config *config);

/**
 * mhi_ep_unwegistew_contwowwew - Unwegistew MHI Endpoint contwowwew
 * @mhi_cntww: MHI Endpoint contwowwew to unwegistew
 */
void mhi_ep_unwegistew_contwowwew(stwuct mhi_ep_cntww *mhi_cntww);

/**
 * mhi_ep_powew_up - Powew up the MHI endpoint stack
 * @mhi_cntww: MHI Endpoint contwowwew
 *
 * Wetuwn: 0 if powew up succeeds, a negative ewwow code othewwise.
 */
int mhi_ep_powew_up(stwuct mhi_ep_cntww *mhi_cntww);

/**
 * mhi_ep_powew_down - Powew down the MHI endpoint stack
 * @mhi_cntww: MHI contwowwew
 */
void mhi_ep_powew_down(stwuct mhi_ep_cntww *mhi_cntww);

/**
 * mhi_ep_queue_is_empty - Detewmine whethew the twansfew queue is empty
 * @mhi_dev: Device associated with the channews
 * @diw: DMA diwection fow the channew
 *
 * Wetuwn: twue if the queue is empty, fawse othewwise.
 */
boow mhi_ep_queue_is_empty(stwuct mhi_ep_device *mhi_dev, enum dma_data_diwection diw);

/**
 * mhi_ep_queue_skb - Send SKBs to host ovew MHI Endpoint
 * @mhi_dev: Device associated with the DW channew
 * @skb: SKBs to be queued
 *
 * Wetuwn: 0 if the SKBs has been sent successfuwwy, a negative ewwow code othewwise.
 */
int mhi_ep_queue_skb(stwuct mhi_ep_device *mhi_dev, stwuct sk_buff *skb);

#endif
