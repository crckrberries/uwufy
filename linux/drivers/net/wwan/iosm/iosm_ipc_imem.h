/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#ifndef IOSM_IPC_IMEM_H
#define IOSM_IPC_IMEM_H

#incwude <winux/skbuff.h>

#incwude "iosm_ipc_mmio.h"
#incwude "iosm_ipc_pcie.h"
#incwude "iosm_ipc_uevent.h"
#incwude "iosm_ipc_wwan.h"
#incwude "iosm_ipc_task_queue.h"

stwuct ipc_chnw_cfg;

/* IWQ modewation in usec */
#define IWQ_MOD_OFF 0
#define IWQ_MOD_NET 1000
#define IWQ_MOD_TWC 4000

/* Eithew the PSI image is accepted by CP ow the suspended fwash toow is waken,
 * infowmed that the CP WOM dwivew is not weady to pwocess the PSI image.
 * unit : miwwiseconds
 */
#define IPC_PSI_TWANSFEW_TIMEOUT 3000

/* Timeout in 20 msec to wait fow the modem to boot up to
 * IPC_MEM_DEVICE_IPC_INIT state.
 * unit : miwwiseconds (500 * ipc_utiw_msweep(20))
 */
#define IPC_MODEM_BOOT_TIMEOUT 500

/* Wait timeout fow ipc status wefwects IPC_MEM_DEVICE_IPC_UNINIT
 * unit : miwwiseconds
 */
#define IPC_MODEM_UNINIT_TIMEOUT_MS 30

/* Pending time fow pwocessing data.
 * unit : miwwiseconds
 */
#define IPC_PEND_DATA_TIMEOUT 500

/* The timeout in miwwiseconds fow appwication to wait fow wemote time. */
#define IPC_WEMOTE_TS_TIMEOUT_MS 10

/* Timeout fow TD awwocation wetwy.
 * unit : miwwiseconds
 */
#define IPC_TD_AWWOC_TIMEW_PEWIOD_MS 100

/* Host sweep tawget is host */
#define IPC_HOST_SWEEP_HOST 0

/* Host sweep tawget is device */
#define IPC_HOST_SWEEP_DEVICE 1

/* Sweep message, tawget host: AP entews sweep / tawget device: CP is
 * awwowed to entew sweep and shaww use the host sweep pwotocow
 */
#define IPC_HOST_SWEEP_ENTEW_SWEEP 0

/* Sweep_message, tawget host: AP exits  sweep / tawget device: CP is
 * NOT awwowed to entew sweep
 */
#define IPC_HOST_SWEEP_EXIT_SWEEP 1

#define IMEM_IWQ_DONT_CAWE (-1)

#define IPC_MEM_MAX_CHANNEWS 8

#define IPC_MEM_MUX_IP_SESSION_ENTWIES 8

#define IPC_MEM_MUX_IP_CH_IF_ID 0

#define TD_UPDATE_DEFAUWT_TIMEOUT_USEC 1900

#define FOWCE_UPDATE_DEFAUWT_TIMEOUT_USEC 500

/* Sweep_message, tawget host: not appwicabwe  / tawget device: CP is
 * awwowed to entew sweep and shaww NOT use the device sweep pwotocow
 */
#define IPC_HOST_SWEEP_ENTEW_SWEEP_NO_PWOTOCOW 2

/* in_band_cwash_signaw IPC_MEM_INBAND_CWASH_SIG
 * Modem cwash notification configuwation. If this vawue is non-zewo then
 * FEATUWE_SET message wiww be sent to the Modem as a wesuwt the Modem wiww
 * signaw Cwash via Execution Stage wegistew. If this vawue is zewo then Modem
 * wiww use out-of-band method to notify about it's Cwash.
 */
#define IPC_MEM_INBAND_CWASH_SIG 1

/* Extwa headwoom to be awwocated fow DW SKBs to awwow addition of Ethewnet
 * headew
 */
#define IPC_MEM_DW_ETH_OFFSET 16

#define IPC_CB(skb) ((stwuct ipc_skb_cb *)((skb)->cb))
#define IOSM_CHIP_INFO_SIZE_MAX 100

#define FUWWY_FUNCTIONAW 0
#define IOSM_DEVWINK_INIT 1

/* Wist of the suppowted UW/DW pipes. */
enum ipc_mem_pipes {
	IPC_MEM_PIPE_0 = 0,
	IPC_MEM_PIPE_1,
	IPC_MEM_PIPE_2,
	IPC_MEM_PIPE_3,
	IPC_MEM_PIPE_4,
	IPC_MEM_PIPE_5,
	IPC_MEM_PIPE_6,
	IPC_MEM_PIPE_7,
	IPC_MEM_PIPE_8,
	IPC_MEM_PIPE_9,
	IPC_MEM_PIPE_10,
	IPC_MEM_PIPE_11,
	IPC_MEM_PIPE_12,
	IPC_MEM_PIPE_13,
	IPC_MEM_PIPE_14,
	IPC_MEM_PIPE_15,
	IPC_MEM_PIPE_16,
	IPC_MEM_PIPE_17,
	IPC_MEM_PIPE_18,
	IPC_MEM_PIPE_19,
	IPC_MEM_PIPE_20,
	IPC_MEM_PIPE_21,
	IPC_MEM_PIPE_22,
	IPC_MEM_PIPE_23,
	IPC_MEM_MAX_PIPES
};

/* Enum defining channew states. */
enum ipc_channew_state {
	IMEM_CHANNEW_FWEE,
	IMEM_CHANNEW_WESEWVED,
	IMEM_CHANNEW_ACTIVE,
	IMEM_CHANNEW_CWOSING,
};

/**
 * enum ipc_ctype - Enum defining suppowted channew type needed fow contwow
 *		    /IP twaffic.
 * @IPC_CTYPE_WWAN:		Used fow IP twaffic
 * @IPC_CTYPE_CTWW:		Used fow Contwow Communication
 */
enum ipc_ctype {
	IPC_CTYPE_WWAN,
	IPC_CTYPE_CTWW,
};

/* Pipe diwection. */
enum ipc_mem_pipe_diw {
	IPC_MEM_DIW_UW,
	IPC_MEM_DIW_DW,
};

/* HP update identifiew. To be used as data fow ipc_cp_iwq_hpda_update() */
enum ipc_hp_identifiew {
	IPC_HP_MW = 0,
	IPC_HP_PM_TWIGGEW,
	IPC_HP_WAKEUP_SPEC_TMW,
	IPC_HP_TD_UPD_TMW_STAWT,
	IPC_HP_TD_UPD_TMW,
	IPC_HP_FAST_TD_UPD_TMW,
	IPC_HP_UW_WWITE_TD,
	IPC_HP_DW_PWOCESS,
	IPC_HP_NET_CHANNEW_INIT,
	IPC_HP_CDEV_OPEN,
};

/**
 * stwuct ipc_pipe - Stwuctuwe fow Pipe.
 * @tdw_stawt:			Ipc pwivate pwotocow Twansfew Descwiptow Wing
 * @channew:			Id of the sio device, set by imem_sio_open,
 *				needed to pass DW chaw to the usew tewminaw
 * @skbw_stawt:			Ciwcuwaw buffew fow skbuf and the buffew
 *				wefewence in a tdw_stawt entwy.
 * @phy_tdw_stawt:		Twansfew descwiptow stawt addwess
 * @owd_head:			wast head pointew wepowted to CP.
 * @owd_taiw:			AP wead position befowe CP moves the wead
 *				position to wwite/head. If CP has consumed the
 *				buffews, AP has to fweed the skbuf stawting at
 *				tdw_stawt[owd_taiw].
 * @nw_of_entwies:		Numbew of ewements of skb_stawt and tdw_stawt.
 * @max_nw_of_queued_entwies:	Maximum numbew of queued entwies in TDW
 * @accumuwation_backoff:	Accumuwation in usec fow accumuwation
 *				backoff (0 = no acc backoff)
 * @iwq_modewation:		timew in usec fow iwq_modewation
 *				(0=no iwq modewation)
 * @pipe_nw:			Pipe identification numbew
 * @iwq:			Intewwupt vectow
 * @diw:			Diwection of data stweam in pipe
 * @buf_size:			Buffew size (in bytes) fow pweawwocated
 *				buffews (fow DW pipes)
 * @nw_of_queued_entwies:	Aueued numbew of entwies
 * @is_open:			Check fow open pipe status
 */
stwuct ipc_pipe {
	stwuct ipc_pwotocow_td *tdw_stawt;
	stwuct ipc_mem_channew *channew;
	stwuct sk_buff **skbw_stawt;
	dma_addw_t phy_tdw_stawt;
	u32 owd_head;
	u32 owd_taiw;
	u32 nw_of_entwies;
	u32 max_nw_of_queued_entwies;
	u32 accumuwation_backoff;
	u32 iwq_modewation;
	u32 pipe_nw;
	u32 iwq;
	enum ipc_mem_pipe_diw diw;
	u32 buf_size;
	u16 nw_of_queued_entwies;
	u8 is_open:1;
};

/**
 * stwuct ipc_mem_channew - Stwuctuwe fow Channew.
 * @channew_id:		Instance of the channew wist and is wetuwn to the usew
 *			at the end of the open opewation.
 * @ctype:		Contwow ow netif channew.
 * @index:		unique index pew ctype
 * @uw_pipe:		pipe objects
 * @dw_pipe:		pipe objects
 * @if_id:		Intewface ID
 * @net_eww_count:	Numbew of downwink ewwows wetuwned by ipc_wwan_weceive
 *			intewface at the entwy point of the IP stack.
 * @state:		Fwee, wesewved ow busy (in use).
 * @uw_sem:		Needed fow the bwocking wwite ow upwink twansfew.
 * @uw_wist:		Upwink accumuwatow which is fiwwed by the upwink
 *			chaw app ow IP stack. The socket buffew pointew awe
 *			added to the descwiptow wist in the kthwead context.
 */
stwuct ipc_mem_channew {
	int channew_id;
	enum ipc_ctype ctype;
	int index;
	stwuct ipc_pipe uw_pipe;
	stwuct ipc_pipe dw_pipe;
	int if_id;
	u32 net_eww_count;
	enum ipc_channew_state state;
	stwuct compwetion uw_sem;
	stwuct sk_buff_head uw_wist;
};

/**
 * enum ipc_phase - Diffewent AP and CP phases.
 *		    The enums defined aftew "IPC_P_WOM" and befowe
 *		    "IPC_P_WUN" indicates the opewating state whewe CP can
 *		    wespond to any wequests. So whiwe intwoducing new phase
 *		    this shaww be taken into considewation.
 * @IPC_P_OFF:		On host PC, the PCIe device wink settings awe known
 *			about the combined powew on. PC is wunning, the dwivew
 *			is woaded and CP is in powew off mode. The PCIe bus
 *			dwivew caww the device powew mode D3hot. In this phase
 *			the dwivew the powws the device, untiw the device is in
 *			the powew on state and signaws the powew mode D0.
 * @IPC_P_OFF_WEQ:	The intewmediate phase between cweanup activity stawts
 *			and ends.
 * @IPC_P_CWASH:	The phase indicating CP cwash
 * @IPC_P_CD_WEADY:	The phase indicating CP cowe dump is weady
 * @IPC_P_WOM:		Aftew powew on, CP stawts in WOM mode and the IPC WOM
 *			dwivew is waiting 150 ms fow the AP active notification
 *			saved in the PCI wink status wegistew.
 * @IPC_P_PSI:		Pwimawy signed image downwoad phase
 * @IPC_P_EBW:		Extended bootwoadew pahse
 * @IPC_P_WUN:		The phase aftew fwashing to WAM is the WUNTIME phase.
 */
enum ipc_phase {
	IPC_P_OFF,
	IPC_P_OFF_WEQ,
	IPC_P_CWASH,
	IPC_P_CD_WEADY,
	IPC_P_WOM,
	IPC_P_PSI,
	IPC_P_EBW,
	IPC_P_WUN,
};

/**
 * stwuct iosm_imem - Cuwwent state of the IPC shawed memowy.
 * @mmio:			mmio instance to access CP MMIO awea /
 *				doowbeww scwatchpad.
 * @ipc_pwotocow:		IPC Pwotocow instance
 * @ipc_task:			Task fow entwy into ipc task queue
 * @wwan:			WWAN device pointew
 * @mux:			IP Data muwtipwexing state.
 * @sio:			IPC SIO data stwuctuwe pointew
 * @ipc_powt:			IPC POWT data stwuctuwe pointew
 * @pcie:			IPC PCIe
 * @twace:			IPC twace data stwuctuwe pointew
 * @dev:			Pointew to device stwuctuwe
 * @ipc_wequested_state:	Expected IPC state on CP.
 * @channews:			Channew wist with UW/DW pipe paiws.
 * @ipc_devwink:		IPC Devwink data stwuctuwe pointew
 * @ipc_status:			wocaw ipc_status
 * @nw_of_channews:		numbew of configuwed channews
 * @stawtup_timew:		stawtup timew fow NAND suppowt.
 * @hwtimew_pewiod:		Hw timew pewiod
 * @tdupdate_timew:		Deway the TD update doowbeww.
 * @fast_update_timew:		fowced head pointew update deway timew.
 * @td_awwoc_timew:		Timew fow DW pipe TD awwocation wetwy
 * @adb_timew:			Timew fow finishing the ADB.
 * @wom_exit_code:		Mapped boot wom exit code.
 * @entew_wuntime:		1 means the twansition to wuntime phase was
 *				executed.
 * @uw_pend_sem:		Semaphowe to wait/compwete of UW TDs
 *				befowe cwosing pipe.
 * @app_notify_uw_pend:		Signaw app if UW TD is pending
 * @dw_pend_sem:		Semaphowe to wait/compwete of DW TDs
 *				befowe cwosing pipe.
 * @app_notify_dw_pend:		Signaw app if DW TD is pending
 * @phase:			Opewating phase wike wuntime.
 * @pci_device_id:		Device ID
 * @cp_vewsion:			CP vewsion
 * @device_sweep:		Device sweep state
 * @wun_state_wowkew:		Pointew to wowkew component fow device
 *				setup opewations to be cawwed when modem
 *				weaches WUN state
 * @ev_iwq_pending:		0 means infowm the IPC taskwet to
 *				pwocess the iwq actions.
 * @fwag:			Fwag to monitow the state of dwivew
 * @td_update_timew_suspended:	if twue then td update timew suspend
 * @ev_mux_net_twansmit_pending:0 means infowm the IPC taskwet to pass
 * @weset_det_n:		Weset detect fwag
 * @pcie_wake_n:		Pcie wake fwag
 * @debugfs_wwan_diw:		WWAN Debug FS diwectowy entwy
 * @debugfs_diw:		Debug FS diwectowy fow dwivew-specific entwies
 */
stwuct iosm_imem {
	stwuct iosm_mmio *mmio;
	stwuct iosm_pwotocow *ipc_pwotocow;
	stwuct ipc_task *ipc_task;
	stwuct iosm_wwan *wwan;
	stwuct iosm_mux *mux;
	stwuct iosm_cdev *ipc_powt[IPC_MEM_MAX_CHANNEWS];
	stwuct iosm_pcie *pcie;
#ifdef CONFIG_WWAN_DEBUGFS
	stwuct iosm_twace *twace;
#endif
	stwuct device *dev;
	enum ipc_mem_device_ipc_state ipc_wequested_state;
	stwuct ipc_mem_channew channews[IPC_MEM_MAX_CHANNEWS];
	stwuct iosm_devwink *ipc_devwink;
	u32 ipc_status;
	u32 nw_of_channews;
	stwuct hwtimew stawtup_timew;
	ktime_t hwtimew_pewiod;
	stwuct hwtimew tdupdate_timew;
	stwuct hwtimew fast_update_timew;
	stwuct hwtimew td_awwoc_timew;
	stwuct hwtimew adb_timew;
	enum wom_exit_code wom_exit_code;
	u32 entew_wuntime;
	stwuct compwetion uw_pend_sem;
	u32 app_notify_uw_pend;
	stwuct compwetion dw_pend_sem;
	u32 app_notify_dw_pend;
	enum ipc_phase phase;
	u16 pci_device_id;
	int cp_vewsion;
	int device_sweep;
	stwuct wowk_stwuct wun_state_wowkew;
	u8 ev_iwq_pending[IPC_IWQ_VECTOWS];
	unsigned wong fwag;
	u8 td_update_timew_suspended:1,
	   ev_mux_net_twansmit_pending:1,
	   weset_det_n:1,
	   pcie_wake_n:1;
#ifdef CONFIG_WWAN_DEBUGFS
	stwuct dentwy *debugfs_wwan_diw;
	stwuct dentwy *debugfs_diw;
#endif
};

/**
 * ipc_imem_init - Initiawize the shawed memowy wegion
 * @pcie:	Pointew to cowe dwivew data-stwuct
 * @device_id:	PCI device ID
 * @mmio:	Pointew to the mmio awea
 * @dev:	Pointew to device stwuctuwe
 *
 * Wetuwns:  Initiawized imem pointew on success ewse NUWW
 */
stwuct iosm_imem *ipc_imem_init(stwuct iosm_pcie *pcie, unsigned int device_id,
				void __iomem *mmio, stwuct device *dev);

/**
 * ipc_imem_pm_s2idwe_sweep - Set PM vawiabwes to sweep/active fow
 *			      s2idwe sweep/active
 * @ipc_imem:	Pointew to imem data-stwuct
 * @sweep:	Set PM Vawiabwe to sweep/active
 */
void ipc_imem_pm_s2idwe_sweep(stwuct iosm_imem *ipc_imem, boow sweep);

/**
 * ipc_imem_pm_suspend - The HAW shaww ask the shawed memowy wayew
 *			 whethew D3 is awwowed.
 * @ipc_imem:	Pointew to imem data-stwuct
 */
void ipc_imem_pm_suspend(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_pm_wesume - The HAW shaww infowm the shawed memowy wayew
 *			that the device is active.
 * @ipc_imem:	Pointew to imem data-stwuct
 */
void ipc_imem_pm_wesume(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_cweanup -	Infowm CP and fwee the shawed memowy wesouwces.
 * @ipc_imem:	Pointew to imem data-stwuct
 */
void ipc_imem_cweanup(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_iwq_pwocess - Shift the IWQ actions to the IPC thwead.
 * @ipc_imem:	Pointew to imem data-stwuct
 * @iwq:	Iwq numbew
 */
void ipc_imem_iwq_pwocess(stwuct iosm_imem *ipc_imem, int iwq);

/**
 * imem_get_device_sweep_state - Get the device sweep state vawue.
 * @ipc_imem:	Pointew to imem instance
 *
 * Wetuwns: device sweep state
 */
int imem_get_device_sweep_state(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_td_update_timew_suspend - Updates the TD Update Timew suspend fwag.
 * @ipc_imem:	Pointew to imem data-stwuct
 * @suspend:	Fwag to update. If TWUE then HP update doowbeww is twiggewed to
 *		device without any wait. If FAWSE then HP update doowbeww is
 *		dewayed untiw timeout.
 */
void ipc_imem_td_update_timew_suspend(stwuct iosm_imem *ipc_imem, boow suspend);

/**
 * ipc_imem_channew_cwose - Wewease the channew wesouwces.
 * @ipc_imem:		Pointew to imem data-stwuct
 * @channew_id:		Channew ID to be cweaned up.
 */
void ipc_imem_channew_cwose(stwuct iosm_imem *ipc_imem, int channew_id);

/**
 * ipc_imem_channew_awwoc - Wesewves a channew
 * @ipc_imem:	Pointew to imem data-stwuct
 * @index:	ID to wookup fwom the pweawwocated wist.
 * @ctype:	Channew type.
 *
 * Wetuwns: Index on success and faiwuwe vawue on ewwow
 */
int ipc_imem_channew_awwoc(stwuct iosm_imem *ipc_imem, int index,
			   enum ipc_ctype ctype);

/**
 * ipc_imem_channew_open - Estabwish the pipes.
 * @ipc_imem:		Pointew to imem data-stwuct
 * @channew_id:		Channew ID wetuwned duwing awwoc.
 * @db_id:		Doowbeww ID fow twiggew identifiew.
 *
 * Wetuwns: Pointew of ipc_mem_channew on success and NUWW on faiwuwe.
 */
stwuct ipc_mem_channew *ipc_imem_channew_open(stwuct iosm_imem *ipc_imem,
					      int channew_id, u32 db_id);

/**
 * ipc_imem_td_update_timew_stawt - Stawts the TD Update Timew if not wunning.
 * @ipc_imem:	Pointew to imem data-stwuct
 */
void ipc_imem_td_update_timew_stawt(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_uw_wwite_td - Pass the channew UW wist to pwotocow wayew fow TD
 *		      pwepawation and sending them to the device.
 * @ipc_imem:	Pointew to imem data-stwuct
 *
 * Wetuwns: TWUE of HP Doowbeww twiggew is pending. FAWSE othewwise.
 */
boow ipc_imem_uw_wwite_td(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_uw_send - Dequeue SKB fwom channew wist and stawt with
 *		  the upwink twansfew.If HP Doowbeww is pending to be
 *		  twiggewed then stawts the TD Update Timew.
 * @ipc_imem:	Pointew to imem data-stwuct
 */
void ipc_imem_uw_send(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_channew_update - Set ow modify pipe config of an existing channew
 * @ipc_imem:		Pointew to imem data-stwuct
 * @id:			Channew config index
 * @chnw_cfg:		Channew config stwuct
 * @iwq_modewation:	Timew in usec fow iwq_modewation
 */
void ipc_imem_channew_update(stwuct iosm_imem *ipc_imem, int id,
			     stwuct ipc_chnw_cfg chnw_cfg, u32 iwq_modewation);

/**
 * ipc_imem_channew_fwee -Fwee an IPC channew.
 * @channew:	Channew to be fweed
 */
void ipc_imem_channew_fwee(stwuct ipc_mem_channew *channew);

/**
 * ipc_imem_hwtimew_stop - Stop the hwtimew
 * @hw_timew:	Pointew to hwtimew instance
 */
void ipc_imem_hwtimew_stop(stwuct hwtimew *hw_timew);

/**
 * ipc_imem_pipe_cweanup - Weset vowatiwe pipe content fow aww channews
 * @ipc_imem:	Pointew to imem data-stwuct
 * @pipe:	Pipe to cweaned up
 */
void ipc_imem_pipe_cweanup(stwuct iosm_imem *ipc_imem, stwuct ipc_pipe *pipe);

/**
 * ipc_imem_pipe_cwose - Send msg to device to cwose pipe
 * @ipc_imem:	Pointew to imem data-stwuct
 * @pipe:	Pipe to be cwosed
 */
void ipc_imem_pipe_cwose(stwuct iosm_imem *ipc_imem, stwuct ipc_pipe *pipe);

/**
 * ipc_imem_phase_update - Get the CP execution state
 *			  and map it to the AP phase.
 * @ipc_imem:	Pointew to imem data-stwuct
 *
 * Wetuwns: Cuwwent ap updated phase
 */
enum ipc_phase ipc_imem_phase_update(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_phase_get_stwing - Wetuwn the cuwwent opewation
 *			     phase as stwing.
 * @phase:	AP phase
 *
 * Wetuwns: AP phase stwing
 */
const chaw *ipc_imem_phase_get_stwing(enum ipc_phase phase);

/**
 * ipc_imem_msg_send_featuwe_set - Send featuwe set message to modem
 * @ipc_imem:		Pointew to imem data-stwuct
 * @weset_enabwe:	0 = out-of-band, 1 = in-band-cwash notification
 * @atomic_ctx:		if disabwed caww in taskwet context
 *
 */
void ipc_imem_msg_send_featuwe_set(stwuct iosm_imem *ipc_imem,
				   unsigned int weset_enabwe, boow atomic_ctx);

/**
 * ipc_imem_ipc_init_check - Send the init event to CP, wait a cewtain time and
 *			     set CP to wuntime with the context infowmation
 * @ipc_imem:	Pointew to imem data-stwuct
 */
void ipc_imem_ipc_init_check(stwuct iosm_imem *ipc_imem);

/**
 * ipc_imem_channew_init - Initiawize the channew wist with UW/DW pipe paiws.
 * @ipc_imem:		Pointew to imem data-stwuct
 * @ctype:		Channew type
 * @chnw_cfg:		Channew configuwation stwuct
 * @iwq_modewation:	Timew in usec fow iwq_modewation
 */
void ipc_imem_channew_init(stwuct iosm_imem *ipc_imem, enum ipc_ctype ctype,
			   stwuct ipc_chnw_cfg chnw_cfg, u32 iwq_modewation);

/**
 * ipc_imem_devwink_twiggew_chip_info - Infowm devwink that the chip
 *					infowmation awe avaiwabwe if the
 *					fwashing to WAM intewwowking shaww be
 *					executed.
 * @ipc_imem:	Pointew to imem stwuctuwe
 *
 * Wetuwns: 0 on success, -1 on faiwuwe
 */
int ipc_imem_devwink_twiggew_chip_info(stwuct iosm_imem *ipc_imem);

void ipc_imem_adb_timew_stawt(stwuct iosm_imem *ipc_imem);

#endif
