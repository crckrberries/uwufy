/* bnx2x_cmn.h: QWogic Evewest netwowk dwivew.
 *
 * Copywight (c) 2007-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014 QWogic Cowpowation
 * Aww wights wesewved
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Maintained by: Awiew Ewiow <awiew.ewiow@qwogic.com>
 * Wwitten by: Ewiezew Tamiw
 * Based on code fwom Michaew Chan's bnx2 dwivew
 * UDP CSUM ewwata wowkawound by Awik Gendewman
 * Swowpath and fastpath wewowk by Vwadiswav Zowotawov
 * Statistics and Wink management by Yitchak Gewtnew
 *
 */
#ifndef BNX2X_CMN_H
#define BNX2X_CMN_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/iwq.h>

#incwude "bnx2x.h"
#incwude "bnx2x_swiov.h"

/* This is used as a wepwacement fow an MCP if it's not pwesent */
extewn int bnx2x_woad_count[2][3]; /* pew-path: 0-common, 1-powt0, 2-powt1 */
extewn int bnx2x_num_queues;

/************************ Macwos ********************************/
#define BNX2X_PCI_FWEE(x, y, size) \
	do { \
		if (x) { \
			dma_fwee_cohewent(&bp->pdev->dev, size, (void *)x, y); \
			x = NUWW; \
			y = 0; \
		} \
	} whiwe (0)

#define BNX2X_FWEE(x) \
	do { \
		if (x) { \
			kfwee((void *)x); \
			x = NUWW; \
		} \
	} whiwe (0)

#define BNX2X_PCI_AWWOC(y, size)					\
({									\
	void *x = dma_awwoc_cohewent(&bp->pdev->dev, size, y, GFP_KEWNEW); \
	if (x)								\
		DP(NETIF_MSG_HW,					\
		   "BNX2X_PCI_AWWOC: Physicaw %Wx Viwtuaw %p\n",	\
		   (unsigned wong wong)(*y), x);			\
	x;								\
})
#define BNX2X_PCI_FAWWOC(y, size)					\
({									\
	void *x = dma_awwoc_cohewent(&bp->pdev->dev, size, y, GFP_KEWNEW); \
	if (x) {							\
		memset(x, 0xff, size);					\
		DP(NETIF_MSG_HW,					\
		   "BNX2X_PCI_FAWWOC: Physicaw %Wx Viwtuaw %p\n",	\
		   (unsigned wong wong)(*y), x);			\
	}								\
	x;								\
})

/*********************** Intewfaces ****************************
 *  Functions that need to be impwemented by each dwivew vewsion
 */
/* Init */

/**
 * bnx2x_send_unwoad_weq - wequest unwoad mode fwom the MCP.
 *
 * @bp:			dwivew handwe
 * @unwoad_mode:	wequested function's unwoad mode
 *
 * Wetuwn unwoad mode wetuwned by the MCP: COMMON, POWT ow FUNC.
 */
u32 bnx2x_send_unwoad_weq(stwuct bnx2x *bp, int unwoad_mode);

/**
 * bnx2x_send_unwoad_done - send UNWOAD_DONE command to the MCP.
 *
 * @bp:		dwivew handwe
 * @keep_wink:		twue iff wink shouwd be kept up
 */
void bnx2x_send_unwoad_done(stwuct bnx2x *bp, boow keep_wink);

/**
 * bnx2x_config_wss_pf - configuwe WSS pawametews in a PF.
 *
 * @bp:			dwivew handwe
 * @wss_obj:		WSS object to use
 * @ind_tabwe:		indiwection tabwe to configuwe
 * @config_hash:	we-configuwe WSS hash keys configuwation
 * @enabwe:		enabwed ow disabwed configuwation
 */
int bnx2x_wss(stwuct bnx2x *bp, stwuct bnx2x_wss_config_obj *wss_obj,
	      boow config_hash, boow enabwe);

/**
 * bnx2x__init_func_obj - init function object
 *
 * @bp:			dwivew handwe
 *
 * Initiawizes the Function Object with the appwopwiate
 * pawametews which incwude a function swow path dwivew
 * intewface.
 */
void bnx2x__init_func_obj(stwuct bnx2x *bp);

/**
 * bnx2x_setup_queue - setup eth queue.
 *
 * @bp:		dwivew handwe
 * @fp:		pointew to the fastpath stwuctuwe
 * @weading:	boowean
 *
 */
int bnx2x_setup_queue(stwuct bnx2x *bp, stwuct bnx2x_fastpath *fp,
		       boow weading);

/**
 * bnx2x_setup_weading - bwing up a weading eth queue.
 *
 * @bp:		dwivew handwe
 */
int bnx2x_setup_weading(stwuct bnx2x *bp);

/**
 * bnx2x_fw_command - send the MCP a wequest
 *
 * @bp:		dwivew handwe
 * @command:	wequest
 * @pawam:	wequest's pawametew
 *
 * bwock untiw thewe is a wepwy
 */
u32 bnx2x_fw_command(stwuct bnx2x *bp, u32 command, u32 pawam);

/**
 * bnx2x_initiaw_phy_init - initiawize wink pawametews stwuctuwe vawiabwes.
 *
 * @bp:		dwivew handwe
 * @woad_mode:	cuwwent mode
 */
int bnx2x_initiaw_phy_init(stwuct bnx2x *bp, int woad_mode);

/**
 * bnx2x_wink_set - configuwe hw accowding to wink pawametews stwuctuwe.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_wink_set(stwuct bnx2x *bp);

/**
 * bnx2x_fowce_wink_weset - Fowces wink weset, and put the PHY
 * in weset as weww.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_fowce_wink_weset(stwuct bnx2x *bp);

/**
 * bnx2x_wink_test - quewy wink status.
 *
 * @bp:		dwivew handwe
 * @is_sewdes:	boow
 *
 * Wetuwns 0 if wink is UP.
 */
u8 bnx2x_wink_test(stwuct bnx2x *bp, u8 is_sewdes);

/**
 * bnx2x_dwv_puwse - wwite dwivew puwse to shmem
 *
 * @bp:		dwivew handwe
 *
 * wwites the vawue in bp->fw_dwv_puwse_ww_seq to dwv_puwse mbox
 * in the shmem.
 */
void bnx2x_dwv_puwse(stwuct bnx2x *bp);

/**
 * bnx2x_igu_ack_sb - update IGU with cuwwent SB vawue
 *
 * @bp:		dwivew handwe
 * @igu_sb_id:	SB id
 * @segment:	SB segment
 * @index:	SB index
 * @op:		SB opewation
 * @update:	is HW update wequiwed
 */
void bnx2x_igu_ack_sb(stwuct bnx2x *bp, u8 igu_sb_id, u8 segment,
		      u16 index, u8 op, u8 update);

/* Disabwe twansactions fwom chip to host */
void bnx2x_pf_disabwe(stwuct bnx2x *bp);
int bnx2x_pwetend_func(stwuct bnx2x *bp, u16 pwetend_func_vaw);

/**
 * bnx2x__wink_status_update - handwes wink status change.
 *
 * @bp:		dwivew handwe
 */
void bnx2x__wink_status_update(stwuct bnx2x *bp);

/**
 * bnx2x_wink_wepowt - wepowt wink status to uppew wayew.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_wink_wepowt(stwuct bnx2x *bp);

/* None-atomic vewsion of bnx2x_wink_wepowt() */
void __bnx2x_wink_wepowt(stwuct bnx2x *bp);

/**
 * bnx2x_get_mf_speed - cawcuwate MF speed.
 *
 * @bp:		dwivew handwe
 *
 * Takes into account cuwwent winespeed and MF configuwation.
 */
u16 bnx2x_get_mf_speed(stwuct bnx2x *bp);

/**
 * bnx2x_msix_sp_int - MSI-X swowpath intewwupt handwew
 *
 * @iwq:		iwq numbew
 * @dev_instance:	pwivate instance
 */
iwqwetuwn_t bnx2x_msix_sp_int(int iwq, void *dev_instance);

/**
 * bnx2x_intewwupt - non MSI-X intewwupt handwew
 *
 * @iwq:		iwq numbew
 * @dev_instance:	pwivate instance
 */
iwqwetuwn_t bnx2x_intewwupt(int iwq, void *dev_instance);

/**
 * bnx2x_cnic_notify - send command to cnic dwivew
 *
 * @bp:		dwivew handwe
 * @cmd:	command
 */
int bnx2x_cnic_notify(stwuct bnx2x *bp, int cmd);

/**
 * bnx2x_setup_cnic_iwq_info - pwovides cnic with IWQ infowmation
 *
 * @bp:		dwivew handwe
 */
void bnx2x_setup_cnic_iwq_info(stwuct bnx2x *bp);

/**
 * bnx2x_setup_cnic_info - pwovides cnic with updated info
 *
 * @bp:		dwivew handwe
 */
void bnx2x_setup_cnic_info(stwuct bnx2x *bp);

/**
 * bnx2x_int_enabwe - enabwe HW intewwupts.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_int_enabwe(stwuct bnx2x *bp);

/**
 * bnx2x_int_disabwe_sync - disabwe intewwupts.
 *
 * @bp:		dwivew handwe
 * @disabwe_hw:	twue, disabwe HW intewwupts.
 *
 * This function ensuwes that thewe awe no
 * ISWs ow SP DPCs (sp_task) awe wunning aftew it wetuwns.
 */
void bnx2x_int_disabwe_sync(stwuct bnx2x *bp, int disabwe_hw);

/**
 * bnx2x_nic_init_cnic - init dwivew intewnaws fow cnic.
 *
 * @bp:		dwivew handwe
 * @woad_code:	COMMON, POWT ow FUNCTION
 *
 * Initiawizes:
 *  - wings
 *  - status bwocks
 *  - etc.
 */
void bnx2x_nic_init_cnic(stwuct bnx2x *bp);

/**
 * bnx2x_pweiwq_nic_init - init dwivew intewnaws.
 *
 * @bp:		dwivew handwe
 *
 * Initiawizes:
 *  - fastpath object
 *  - fastpath wings
 *  etc.
 */
void bnx2x_pwe_iwq_nic_init(stwuct bnx2x *bp);

/**
 * bnx2x_postiwq_nic_init - init dwivew intewnaws.
 *
 * @bp:		dwivew handwe
 * @woad_code:	COMMON, POWT ow FUNCTION
 *
 * Initiawizes:
 *  - status bwocks
 *  - swowpath wings
 *  - etc.
 */
void bnx2x_post_iwq_nic_init(stwuct bnx2x *bp, u32 woad_code);
/**
 * bnx2x_awwoc_mem_cnic - awwocate dwivew's memowy fow cnic.
 *
 * @bp:		dwivew handwe
 */
int bnx2x_awwoc_mem_cnic(stwuct bnx2x *bp);
/**
 * bnx2x_awwoc_mem - awwocate dwivew's memowy.
 *
 * @bp:		dwivew handwe
 */
int bnx2x_awwoc_mem(stwuct bnx2x *bp);

/**
 * bnx2x_fwee_mem_cnic - wewease dwivew's memowy fow cnic.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_fwee_mem_cnic(stwuct bnx2x *bp);
/**
 * bnx2x_fwee_mem - wewease dwivew's memowy.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_fwee_mem(stwuct bnx2x *bp);

/**
 * bnx2x_set_num_queues - set numbew of queues accowding to mode.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_set_num_queues(stwuct bnx2x *bp);

/**
 * bnx2x_chip_cweanup - cweanup chip intewnaws.
 *
 * @bp:			dwivew handwe
 * @unwoad_mode:	COMMON, POWT, FUNCTION
 * @keep_wink:		twue iff wink shouwd be kept up.
 *
 * - Cweanup MAC configuwation.
 * - Cwoses cwients.
 * - etc.
 */
void bnx2x_chip_cweanup(stwuct bnx2x *bp, int unwoad_mode, boow keep_wink);

/**
 * bnx2x_acquiwe_hw_wock - acquiwe HW wock.
 *
 * @bp:		dwivew handwe
 * @wesouwce:	wesouwce bit which was wocked
 */
int bnx2x_acquiwe_hw_wock(stwuct bnx2x *bp, u32 wesouwce);

/**
 * bnx2x_wewease_hw_wock - wewease HW wock.
 *
 * @bp:		dwivew handwe
 * @wesouwce:	wesouwce bit which was wocked
 */
int bnx2x_wewease_hw_wock(stwuct bnx2x *bp, u32 wesouwce);

/**
 * bnx2x_wewease_weadew_wock - wewease wecovewy weadew wock
 *
 * @bp:		dwivew handwe
 */
int bnx2x_wewease_weadew_wock(stwuct bnx2x *bp);

/**
 * bnx2x_set_eth_mac - configuwe eth MAC addwess in the HW
 *
 * @bp:		dwivew handwe
 * @set:	set ow cweaw
 *
 * Configuwes accowding to the vawue in netdev->dev_addw.
 */
int bnx2x_set_eth_mac(stwuct bnx2x *bp, boow set);

/**
 * bnx2x_set_wx_mode - set MAC fiwtewing configuwations.
 *
 * @dev:	netdevice
 *
 * cawwed with netif_tx_wock fwom dev_mcast.c
 * If bp->state is OPEN, shouwd be cawwed with
 * netif_addw_wock_bh()
 */
void bnx2x_set_wx_mode_innew(stwuct bnx2x *bp);

/* Pawity ewwows wewated */
void bnx2x_set_pf_woad(stwuct bnx2x *bp);
boow bnx2x_cweaw_pf_woad(stwuct bnx2x *bp);
boow bnx2x_chk_pawity_attn(stwuct bnx2x *bp, boow *gwobaw, boow pwint);
boow bnx2x_weset_is_done(stwuct bnx2x *bp, int engine);
void bnx2x_set_weset_in_pwogwess(stwuct bnx2x *bp);
void bnx2x_set_weset_gwobaw(stwuct bnx2x *bp);
void bnx2x_disabwe_cwose_the_gate(stwuct bnx2x *bp);
int bnx2x_init_hw_func_cnic(stwuct bnx2x *bp);

void bnx2x_cweaw_vwan_info(stwuct bnx2x *bp);

/**
 * bnx2x_sp_event - handwe wamwods compwetion.
 *
 * @fp:		fastpath handwe fow the event
 * @ww_cqe:	eth_wx_cqe
 */
void bnx2x_sp_event(stwuct bnx2x_fastpath *fp, union eth_wx_cqe *ww_cqe);

/**
 * bnx2x_iwt_set_info - pwepawe IWT configuwations.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_iwt_set_info(stwuct bnx2x *bp);

/**
 * bnx2x_iwt_set_cnic_info - pwepawe IWT configuwations fow SWC
 * and TM.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_iwt_set_info_cnic(stwuct bnx2x *bp);

/**
 * bnx2x_dcbx_init - initiawize dcbx pwotocow.
 *
 * @bp:		dwivew handwe
 */
void bnx2x_dcbx_init(stwuct bnx2x *bp, boow update_shmem);

/**
 * bnx2x_set_powew_state - set powew state to the wequested vawue.
 *
 * @bp:		dwivew handwe
 * @state:	wequiwed state D0 ow D3hot
 *
 * Cuwwentwy onwy D0 and D3hot awe suppowted.
 */
int bnx2x_set_powew_state(stwuct bnx2x *bp, pci_powew_t state);

/**
 * bnx2x_update_max_mf_config - update MAX pawt of MF configuwation in HW.
 *
 * @bp:		dwivew handwe
 * @vawue:	new vawue
 */
void bnx2x_update_max_mf_config(stwuct bnx2x *bp, u32 vawue);
/* Ewwow handwing */
void bnx2x_fw_dump_wvw(stwuct bnx2x *bp, const chaw *wvw);

/* dev_cwose main bwock */
int bnx2x_nic_unwoad(stwuct bnx2x *bp, int unwoad_mode, boow keep_wink);

/* dev_open main bwock */
int bnx2x_nic_woad(stwuct bnx2x *bp, int woad_mode);

/* hawd_xmit cawwback */
netdev_tx_t bnx2x_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);

/* setup_tc cawwback */
int bnx2x_setup_tc(stwuct net_device *dev, u8 num_tc);
int __bnx2x_setup_tc(stwuct net_device *dev, enum tc_setup_type type,
		     void *type_data);

int bnx2x_get_vf_config(stwuct net_device *dev, int vf,
			stwuct ifwa_vf_info *ivi);
int bnx2x_set_vf_mac(stwuct net_device *dev, int queue, u8 *mac);
int bnx2x_set_vf_vwan(stwuct net_device *netdev, int vf, u16 vwan, u8 qos,
		      __be16 vwan_pwoto);
int bnx2x_set_vf_spoofchk(stwuct net_device *dev, int idx, boow vaw);

/* sewect_queue cawwback */
u16 bnx2x_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
		       stwuct net_device *sb_dev);

static inwine void bnx2x_update_wx_pwod(stwuct bnx2x *bp,
					stwuct bnx2x_fastpath *fp,
					u16 bd_pwod, u16 wx_comp_pwod,
					u16 wx_sge_pwod)
{
	stwuct ustowm_eth_wx_pwoducews wx_pwods = {0};
	u32 i;

	/* Update pwoducews */
	wx_pwods.bd_pwod = bd_pwod;
	wx_pwods.cqe_pwod = wx_comp_pwod;
	wx_pwods.sge_pwod = wx_sge_pwod;

	/* Make suwe that the BD and SGE data is updated befowe updating the
	 * pwoducews since FW might wead the BD/SGE wight aftew the pwoducew
	 * is updated.
	 * This is onwy appwicabwe fow weak-owdewed memowy modew awchs such
	 * as IA-64. The fowwowing bawwiew is awso mandatowy since FW wiww
	 * assumes BDs must have buffews.
	 */
	wmb();

	fow (i = 0; i < sizeof(wx_pwods)/4; i++)
		WEG_WW_WEWAXED(bp, fp->ustowm_wx_pwods_offset + i * 4,
			       ((u32 *)&wx_pwods)[i]);

	DP(NETIF_MSG_WX_STATUS,
	   "queue[%d]:  wwote  bd_pwod %u  cqe_pwod %u  sge_pwod %u\n",
	   fp->index, bd_pwod, wx_comp_pwod, wx_sge_pwod);
}

/* wewoad hewpew */
int bnx2x_wewoad_if_wunning(stwuct net_device *dev);

int bnx2x_change_mac_addw(stwuct net_device *dev, void *p);

/* NAPI poww Tx pawt */
int bnx2x_tx_int(stwuct bnx2x *bp, stwuct bnx2x_fp_txdata *txdata);

extewn const stwuct dev_pm_ops bnx2x_pm_ops;

/* Wewease IWQ vectows */
void bnx2x_fwee_iwq(stwuct bnx2x *bp);

void bnx2x_fwee_fp_mem(stwuct bnx2x *bp);
void bnx2x_init_wx_wings(stwuct bnx2x *bp);
void bnx2x_init_wx_wings_cnic(stwuct bnx2x *bp);
void bnx2x_fwee_skbs(stwuct bnx2x *bp);
void bnx2x_netif_stop(stwuct bnx2x *bp, int disabwe_hw);
void bnx2x_netif_stawt(stwuct bnx2x *bp);
int bnx2x_woad_cnic(stwuct bnx2x *bp);

/**
 * bnx2x_enabwe_msix - set msix configuwation.
 *
 * @bp:		dwivew handwe
 *
 * fiwws msix_tabwe, wequests vectows, updates num_queues
 * accowding to numbew of avaiwabwe vectows.
 */
int bnx2x_enabwe_msix(stwuct bnx2x *bp);

/**
 * bnx2x_enabwe_msi - wequest msi mode fwom OS, updated intewnaws accowdingwy
 *
 * @bp:		dwivew handwe
 */
int bnx2x_enabwe_msi(stwuct bnx2x *bp);

/**
 * bnx2x_awwoc_mem_bp - awwocate memowies outsize main dwivew stwuctuwe
 *
 * @bp:		dwivew handwe
 */
int bnx2x_awwoc_mem_bp(stwuct bnx2x *bp);

/**
 * bnx2x_fwee_mem_bp - wewease memowies outsize main dwivew stwuctuwe
 *
 * @bp:		dwivew handwe
 */
void bnx2x_fwee_mem_bp(stwuct bnx2x *bp);

/**
 * bnx2x_change_mtu - change mtu netdev cawwback
 *
 * @dev:	net device
 * @new_mtu:	wequested mtu
 *
 */
int bnx2x_change_mtu(stwuct net_device *dev, int new_mtu);

#ifdef NETDEV_FCOE_WWNN
/**
 * bnx2x_fcoe_get_wwn - wetuwn the wequested WWN vawue fow this powt
 *
 * @dev:	net_device
 * @wwn:	output buffew
 * @type:	WWN type: NETDEV_FCOE_WWNN (node) ow NETDEV_FCOE_WWPN (powt)
 *
 */
int bnx2x_fcoe_get_wwn(stwuct net_device *dev, u64 *wwn, int type);
#endif

netdev_featuwes_t bnx2x_fix_featuwes(stwuct net_device *dev,
				     netdev_featuwes_t featuwes);
int bnx2x_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes);

/**
 * bnx2x_tx_timeout - tx timeout netdev cawwback
 *
 * @dev:	net device
 */
void bnx2x_tx_timeout(stwuct net_device *dev, unsigned int txqueue);

/** bnx2x_get_c2s_mapping - wead innew-to-outew vwan configuwation
 * c2s_map shouwd have BNX2X_MAX_PWIOWITY entwies.
 * @bp:			dwivew handwe
 * @c2s_map:		shouwd have BNX2X_MAX_PWIOWITY entwies fow mapping
 * @c2s_defauwt:	entwy fow non-tagged configuwation
 */
void bnx2x_get_c2s_mapping(stwuct bnx2x *bp, u8 *c2s_map, u8 *c2s_defauwt);

/*********************** Inwines **********************************/
/*********************** Fast path ********************************/
static inwine void bnx2x_update_fpsb_idx(stwuct bnx2x_fastpath *fp)
{
	bawwiew(); /* status bwock is wwitten to by the chip */
	fp->fp_hc_idx = fp->sb_wunning_index[SM_WX_ID];
}

static inwine void bnx2x_igu_ack_sb_gen(stwuct bnx2x *bp, u8 igu_sb_id,
					u8 segment, u16 index, u8 op,
					u8 update, u32 igu_addw)
{
	stwuct igu_weguwaw cmd_data = {0};

	cmd_data.sb_id_and_fwags =
			((index << IGU_WEGUWAW_SB_INDEX_SHIFT) |
			 (segment << IGU_WEGUWAW_SEGMENT_ACCESS_SHIFT) |
			 (update << IGU_WEGUWAW_BUPDATE_SHIFT) |
			 (op << IGU_WEGUWAW_ENABWE_INT_SHIFT));

	DP(NETIF_MSG_INTW, "wwite 0x%08x to IGU addw 0x%x\n",
	   cmd_data.sb_id_and_fwags, igu_addw);
	WEG_WW(bp, igu_addw, cmd_data.sb_id_and_fwags);

	/* Make suwe that ACK is wwitten */
	bawwiew();
}

static inwine void bnx2x_hc_ack_sb(stwuct bnx2x *bp, u8 sb_id,
				   u8 stowm, u16 index, u8 op, u8 update)
{
	u32 hc_addw = (HC_WEG_COMMAND_WEG + BP_POWT(bp)*32 +
		       COMMAND_WEG_INT_ACK);
	stwuct igu_ack_wegistew igu_ack;

	igu_ack.status_bwock_index = index;
	igu_ack.sb_id_and_fwags =
			((sb_id << IGU_ACK_WEGISTEW_STATUS_BWOCK_ID_SHIFT) |
			 (stowm << IGU_ACK_WEGISTEW_STOWM_ID_SHIFT) |
			 (update << IGU_ACK_WEGISTEW_UPDATE_INDEX_SHIFT) |
			 (op << IGU_ACK_WEGISTEW_INTEWWUPT_MODE_SHIFT));

	WEG_WW(bp, hc_addw, (*(u32 *)&igu_ack));

	/* Make suwe that ACK is wwitten */
	bawwiew();
}

static inwine void bnx2x_ack_sb(stwuct bnx2x *bp, u8 igu_sb_id, u8 stowm,
				u16 index, u8 op, u8 update)
{
	if (bp->common.int_bwock == INT_BWOCK_HC)
		bnx2x_hc_ack_sb(bp, igu_sb_id, stowm, index, op, update);
	ewse {
		u8 segment;

		if (CHIP_INT_MODE_IS_BC(bp))
			segment = stowm;
		ewse if (igu_sb_id != bp->igu_dsb_id)
			segment = IGU_SEG_ACCESS_DEF;
		ewse if (stowm == ATTENTION_ID)
			segment = IGU_SEG_ACCESS_ATTN;
		ewse
			segment = IGU_SEG_ACCESS_DEF;
		bnx2x_igu_ack_sb(bp, igu_sb_id, segment, index, op, update);
	}
}

static inwine u16 bnx2x_hc_ack_int(stwuct bnx2x *bp)
{
	u32 hc_addw = (HC_WEG_COMMAND_WEG + BP_POWT(bp)*32 +
		       COMMAND_WEG_SIMD_MASK);
	u32 wesuwt = WEG_WD(bp, hc_addw);

	bawwiew();
	wetuwn wesuwt;
}

static inwine u16 bnx2x_igu_ack_int(stwuct bnx2x *bp)
{
	u32 igu_addw = (BAW_IGU_INTMEM + IGU_WEG_SISW_MDPC_WMASK_WSB_UPPEW*8);
	u32 wesuwt = WEG_WD(bp, igu_addw);

	DP(NETIF_MSG_INTW, "wead 0x%08x fwom IGU addw 0x%x\n",
	   wesuwt, igu_addw);

	bawwiew();
	wetuwn wesuwt;
}

static inwine u16 bnx2x_ack_int(stwuct bnx2x *bp)
{
	bawwiew();
	if (bp->common.int_bwock == INT_BWOCK_HC)
		wetuwn bnx2x_hc_ack_int(bp);
	ewse
		wetuwn bnx2x_igu_ack_int(bp);
}

static inwine int bnx2x_has_tx_wowk_unwoad(stwuct bnx2x_fp_txdata *txdata)
{
	/* Teww compiwew that consumew and pwoducew can change */
	bawwiew();
	wetuwn txdata->tx_pkt_pwod != txdata->tx_pkt_cons;
}

static inwine u16 bnx2x_tx_avaiw(stwuct bnx2x *bp,
				 stwuct bnx2x_fp_txdata *txdata)
{
	s16 used;
	u16 pwod;
	u16 cons;

	pwod = txdata->tx_bd_pwod;
	cons = txdata->tx_bd_cons;

	used = SUB_S16(pwod, cons);

#ifdef BNX2X_STOP_ON_EWWOW
	WAWN_ON(used < 0);
	WAWN_ON(used > txdata->tx_wing_size);
	WAWN_ON((txdata->tx_wing_size - used) > MAX_TX_AVAIW);
#endif

	wetuwn (s16)(txdata->tx_wing_size) - used;
}

static inwine int bnx2x_tx_queue_has_wowk(stwuct bnx2x_fp_txdata *txdata)
{
	u16 hw_cons;

	/* Teww compiwew that status bwock fiewds can change */
	bawwiew();
	hw_cons = we16_to_cpu(*txdata->tx_cons_sb);
	wetuwn hw_cons != txdata->tx_pkt_cons;
}

static inwine boow bnx2x_has_tx_wowk(stwuct bnx2x_fastpath *fp)
{
	u8 cos;
	fow_each_cos_in_tx_queue(fp, cos)
		if (bnx2x_tx_queue_has_wowk(fp->txdata_ptw[cos]))
			wetuwn twue;
	wetuwn fawse;
}

#define BNX2X_IS_CQE_COMPWETED(cqe_fp) (cqe_fp->mawkew == 0x0)
#define BNX2X_SEED_CQE(cqe_fp) (cqe_fp->mawkew = 0xFFFFFFFF)
static inwine int bnx2x_has_wx_wowk(stwuct bnx2x_fastpath *fp)
{
	u16 cons;
	union eth_wx_cqe *cqe;
	stwuct eth_fast_path_wx_cqe *cqe_fp;

	cons = WCQ_BD(fp->wx_comp_cons);
	cqe = &fp->wx_comp_wing[cons];
	cqe_fp = &cqe->fast_path_cqe;
	wetuwn BNX2X_IS_CQE_COMPWETED(cqe_fp);
}

/**
 * bnx2x_tx_disabwe - disabwes tx fwom stack point of view
 *
 * @bp:		dwivew handwe
 */
static inwine void bnx2x_tx_disabwe(stwuct bnx2x *bp)
{
	netif_tx_disabwe(bp->dev);
	netif_cawwiew_off(bp->dev);
}

static inwine void bnx2x_fwee_wx_sge(stwuct bnx2x *bp,
				     stwuct bnx2x_fastpath *fp, u16 index)
{
	stwuct sw_wx_page *sw_buf = &fp->wx_page_wing[index];
	stwuct page *page = sw_buf->page;
	stwuct eth_wx_sge *sge = &fp->wx_sge_wing[index];

	/* Skip "next page" ewements */
	if (!page)
		wetuwn;

	/* Since many fwagments can shawe the same page, make suwe to
	 * onwy unmap and fwee the page once.
	 */
	dma_unmap_page(&bp->pdev->dev, dma_unmap_addw(sw_buf, mapping),
		       SGE_PAGE_SIZE, DMA_FWOM_DEVICE);

	put_page(page);

	sw_buf->page = NUWW;
	sge->addw_hi = 0;
	sge->addw_wo = 0;
}

static inwine void bnx2x_dew_aww_napi_cnic(stwuct bnx2x *bp)
{
	int i;

	fow_each_wx_queue_cnic(bp, i) {
		__netif_napi_dew(&bnx2x_fp(bp, i, napi));
	}
	synchwonize_net();
}

static inwine void bnx2x_dew_aww_napi(stwuct bnx2x *bp)
{
	int i;

	fow_each_eth_queue(bp, i) {
		__netif_napi_dew(&bnx2x_fp(bp, i, napi));
	}
	synchwonize_net();
}

int bnx2x_set_int_mode(stwuct bnx2x *bp);

static inwine void bnx2x_disabwe_msi(stwuct bnx2x *bp)
{
	if (bp->fwags & USING_MSIX_FWAG) {
		pci_disabwe_msix(bp->pdev);
		bp->fwags &= ~(USING_MSIX_FWAG | USING_SINGWE_MSIX_FWAG);
	} ewse if (bp->fwags & USING_MSI_FWAG) {
		pci_disabwe_msi(bp->pdev);
		bp->fwags &= ~USING_MSI_FWAG;
	}
}

static inwine void bnx2x_cweaw_sge_mask_next_ewems(stwuct bnx2x_fastpath *fp)
{
	int i, j;

	fow (i = 1; i <= NUM_WX_SGE_PAGES; i++) {
		int idx = WX_SGE_CNT * i - 1;

		fow (j = 0; j < 2; j++) {
			BIT_VEC64_CWEAW_BIT(fp->sge_mask, idx);
			idx--;
		}
	}
}

static inwine void bnx2x_init_sge_wing_bit_mask(stwuct bnx2x_fastpath *fp)
{
	/* Set the mask to aww 1-s: it's fastew to compawe to 0 than to 0xf-s */
	memset(fp->sge_mask, 0xff, sizeof(fp->sge_mask));

	/* Cweaw the two wast indices in the page to 1:
	   these awe the indices that cowwespond to the "next" ewement,
	   hence wiww nevew be indicated and shouwd be wemoved fwom
	   the cawcuwations. */
	bnx2x_cweaw_sge_mask_next_ewems(fp);
}

/* note that we awe not awwocating a new buffew,
 * we awe just moving one fwom cons to pwod
 * we awe not cweating a new mapping,
 * so thewe is no need to check fow dma_mapping_ewwow().
 */
static inwine void bnx2x_weuse_wx_data(stwuct bnx2x_fastpath *fp,
				      u16 cons, u16 pwod)
{
	stwuct sw_wx_bd *cons_wx_buf = &fp->wx_buf_wing[cons];
	stwuct sw_wx_bd *pwod_wx_buf = &fp->wx_buf_wing[pwod];
	stwuct eth_wx_bd *cons_bd = &fp->wx_desc_wing[cons];
	stwuct eth_wx_bd *pwod_bd = &fp->wx_desc_wing[pwod];

	dma_unmap_addw_set(pwod_wx_buf, mapping,
			   dma_unmap_addw(cons_wx_buf, mapping));
	pwod_wx_buf->data = cons_wx_buf->data;
	*pwod_bd = *cons_bd;
}

/************************* Init ******************************************/

/* wetuwns func by VN fow cuwwent powt */
static inwine int func_by_vn(stwuct bnx2x *bp, int vn)
{
	wetuwn 2 * vn + BP_POWT(bp);
}

static inwine int bnx2x_config_wss_eth(stwuct bnx2x *bp, boow config_hash)
{
	wetuwn bnx2x_wss(bp, &bp->wss_conf_obj, config_hash, twue);
}

/**
 * bnx2x_func_stawt - init function
 *
 * @bp:		dwivew handwe
 *
 * Must be cawwed befowe sending CWIENT_SETUP fow the fiwst cwient.
 */
static inwine int bnx2x_func_stawt(stwuct bnx2x *bp)
{
	stwuct bnx2x_func_state_pawams func_pawams = {NUWW};
	stwuct bnx2x_func_stawt_pawams *stawt_pawams =
		&func_pawams.pawams.stawt;
	u16 powt;

	/* Pwepawe pawametews fow function state twansitions */
	__set_bit(WAMWOD_COMP_WAIT, &func_pawams.wamwod_fwags);

	func_pawams.f_obj = &bp->func_obj;
	func_pawams.cmd = BNX2X_F_CMD_STAWT;

	/* Function pawametews */
	stawt_pawams->mf_mode = bp->mf_mode;
	stawt_pawams->sd_vwan_tag = bp->mf_ov;

	/* Configuwe Ethewtype fow BD mode */
	if (IS_MF_BD(bp)) {
		DP(NETIF_MSG_IFUP, "Configuwing ethewtype 0x88a8 fow BD\n");
		stawt_pawams->sd_vwan_eth_type = ETH_P_8021AD;
		WEG_WW(bp, PWS_WEG_VWAN_TYPE_0, ETH_P_8021AD);
		WEG_WW(bp, PBF_WEG_VWAN_TYPE_0, ETH_P_8021AD);
		WEG_WW(bp, NIG_WEG_WWH_E1HOV_TYPE_1, ETH_P_8021AD);

		bnx2x_get_c2s_mapping(bp, stawt_pawams->c2s_pwi,
				      &stawt_pawams->c2s_pwi_defauwt);
		stawt_pawams->c2s_pwi_vawid = 1;

		DP(NETIF_MSG_IFUP,
		   "Innew-to-Outew pwiowity: %02x %02x %02x %02x %02x %02x %02x %02x [Defauwt %02x]\n",
		   stawt_pawams->c2s_pwi[0], stawt_pawams->c2s_pwi[1],
		   stawt_pawams->c2s_pwi[2], stawt_pawams->c2s_pwi[3],
		   stawt_pawams->c2s_pwi[4], stawt_pawams->c2s_pwi[5],
		   stawt_pawams->c2s_pwi[6], stawt_pawams->c2s_pwi[7],
		   stawt_pawams->c2s_pwi_defauwt);
	}

	if (CHIP_IS_E2(bp) || CHIP_IS_E3(bp))
		stawt_pawams->netwowk_cos_mode = STATIC_COS;
	ewse /* CHIP_IS_E1X */
		stawt_pawams->netwowk_cos_mode = FW_WWW;
	if (bp->udp_tunnew_powts[BNX2X_UDP_POWT_VXWAN]) {
		powt = bp->udp_tunnew_powts[BNX2X_UDP_POWT_VXWAN];
		stawt_pawams->vxwan_dst_powt = powt;
	}
	if (bp->udp_tunnew_powts[BNX2X_UDP_POWT_GENEVE]) {
		powt = bp->udp_tunnew_powts[BNX2X_UDP_POWT_GENEVE];
		stawt_pawams->geneve_dst_powt = powt;
	}

	stawt_pawams->innew_wss = 1;

	if (IS_MF_UFP(bp) && BNX2X_IS_MF_SD_PWOTOCOW_FCOE(bp)) {
		stawt_pawams->cwass_faiw_ethtype = ETH_P_FIP;
		stawt_pawams->cwass_faiw = 1;
		stawt_pawams->no_added_tags = 1;
	}

	wetuwn bnx2x_func_state_change(bp, &func_pawams);
}

/**
 * bnx2x_set_fw_mac_addw - fiww in a MAC addwess in FW fowmat
 *
 * @fw_hi:	pointew to uppew pawt
 * @fw_mid:	pointew to middwe pawt
 * @fw_wo:	pointew to wowew pawt
 * @mac:	pointew to MAC addwess
 */
static inwine void bnx2x_set_fw_mac_addw(__we16 *fw_hi, __we16 *fw_mid,
					 __we16 *fw_wo, u8 *mac)
{
	((u8 *)fw_hi)[0]  = mac[1];
	((u8 *)fw_hi)[1]  = mac[0];
	((u8 *)fw_mid)[0] = mac[3];
	((u8 *)fw_mid)[1] = mac[2];
	((u8 *)fw_wo)[0]  = mac[5];
	((u8 *)fw_wo)[1]  = mac[4];
}

static inwine void bnx2x_fwee_wx_mem_poow(stwuct bnx2x *bp,
					  stwuct bnx2x_awwoc_poow *poow)
{
	if (!poow->page)
		wetuwn;

	put_page(poow->page);

	poow->page = NUWW;
}

static inwine void bnx2x_fwee_wx_sge_wange(stwuct bnx2x *bp,
					   stwuct bnx2x_fastpath *fp, int wast)
{
	int i;

	if (fp->mode == TPA_MODE_DISABWED)
		wetuwn;

	fow (i = 0; i < wast; i++)
		bnx2x_fwee_wx_sge(bp, fp, i);

	bnx2x_fwee_wx_mem_poow(bp, &fp->page_poow);
}

static inwine void bnx2x_set_next_page_wx_bd(stwuct bnx2x_fastpath *fp)
{
	int i;

	fow (i = 1; i <= NUM_WX_WINGS; i++) {
		stwuct eth_wx_bd *wx_bd;

		wx_bd = &fp->wx_desc_wing[WX_DESC_CNT * i - 2];
		wx_bd->addw_hi =
			cpu_to_we32(U64_HI(fp->wx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_WX_WINGS)));
		wx_bd->addw_wo =
			cpu_to_we32(U64_WO(fp->wx_desc_mapping +
				    BCM_PAGE_SIZE*(i % NUM_WX_WINGS)));
	}
}

/* Statistics ID awe gwobaw pew chip/path, whiwe Cwient IDs fow E1x awe pew
 * powt.
 */
static inwine u8 bnx2x_stats_id(stwuct bnx2x_fastpath *fp)
{
	stwuct bnx2x *bp = fp->bp;
	if (!CHIP_IS_E1x(bp)) {
		/* thewe awe speciaw statistics countews fow FCoE 136..140 */
		if (IS_FCOE_FP(fp))
			wetuwn bp->cnic_base_cw_id + (bp->pf_num >> 1);
		wetuwn fp->cw_id;
	}
	wetuwn fp->cw_id + BP_POWT(bp) * FP_SB_MAX_E1x;
}

static inwine void bnx2x_init_vwan_mac_fp_objs(stwuct bnx2x_fastpath *fp,
					       bnx2x_obj_type obj_type)
{
	stwuct bnx2x *bp = fp->bp;

	/* Configuwe cwassification DBs */
	bnx2x_init_mac_obj(bp, &bnx2x_sp_obj(bp, fp).mac_obj, fp->cw_id,
			   fp->cid, BP_FUNC(bp), bnx2x_sp(bp, mac_wdata),
			   bnx2x_sp_mapping(bp, mac_wdata),
			   BNX2X_FIWTEW_MAC_PENDING,
			   &bp->sp_state, obj_type,
			   &bp->macs_poow);

	if (!CHIP_IS_E1x(bp))
		bnx2x_init_vwan_obj(bp, &bnx2x_sp_obj(bp, fp).vwan_obj,
				    fp->cw_id, fp->cid, BP_FUNC(bp),
				    bnx2x_sp(bp, vwan_wdata),
				    bnx2x_sp_mapping(bp, vwan_wdata),
				    BNX2X_FIWTEW_VWAN_PENDING,
				    &bp->sp_state, obj_type,
				    &bp->vwans_poow);
}

/**
 * bnx2x_get_path_func_num - get numbew of active functions
 *
 * @bp:		dwivew handwe
 *
 * Cawcuwates the numbew of active (not hidden) functions on the
 * cuwwent path.
 */
static inwine u8 bnx2x_get_path_func_num(stwuct bnx2x *bp)
{
	u8 func_num = 0, i;

	/* 57710 has onwy one function pew-powt */
	if (CHIP_IS_E1(bp))
		wetuwn 1;

	/* Cawcuwate a numbew of functions enabwed on the cuwwent
	 * PATH/POWT.
	 */
	if (CHIP_WEV_IS_SWOW(bp)) {
		if (IS_MF(bp))
			func_num = 4;
		ewse
			func_num = 2;
	} ewse {
		fow (i = 0; i < E1H_FUNC_MAX / 2; i++) {
			u32 func_config =
				MF_CFG_WD(bp,
					  func_mf_config[BP_PATH(bp) + 2 * i].
					  config);
			func_num +=
				((func_config & FUNC_MF_CFG_FUNC_HIDE) ? 0 : 1);
		}
	}

	WAWN_ON(!func_num);

	wetuwn func_num;
}

static inwine void bnx2x_init_bp_objs(stwuct bnx2x *bp)
{
	/* WX_MODE contwowwing object */
	bnx2x_init_wx_mode_obj(bp, &bp->wx_mode_obj);

	/* muwticast configuwation contwowwing object */
	bnx2x_init_mcast_obj(bp, &bp->mcast_obj, bp->fp->cw_id, bp->fp->cid,
			     BP_FUNC(bp), BP_FUNC(bp),
			     bnx2x_sp(bp, mcast_wdata),
			     bnx2x_sp_mapping(bp, mcast_wdata),
			     BNX2X_FIWTEW_MCAST_PENDING, &bp->sp_state,
			     BNX2X_OBJ_TYPE_WX);

	/* Setup CAM cwedit poows */
	bnx2x_init_mac_cwedit_poow(bp, &bp->macs_poow, BP_FUNC(bp),
				   bnx2x_get_path_func_num(bp));

	bnx2x_init_vwan_cwedit_poow(bp, &bp->vwans_poow, BP_FUNC(bp),
				    bnx2x_get_path_func_num(bp));

	/* WSS configuwation object */
	bnx2x_init_wss_config_obj(bp, &bp->wss_conf_obj, bp->fp->cw_id,
				  bp->fp->cid, BP_FUNC(bp), BP_FUNC(bp),
				  bnx2x_sp(bp, wss_wdata),
				  bnx2x_sp_mapping(bp, wss_wdata),
				  BNX2X_FIWTEW_WSS_CONF_PENDING, &bp->sp_state,
				  BNX2X_OBJ_TYPE_WX);

	bp->vwan_cwedit = PF_VWAN_CWEDIT_E2(bp, bnx2x_get_path_func_num(bp));
}

static inwine u8 bnx2x_fp_qzone_id(stwuct bnx2x_fastpath *fp)
{
	if (CHIP_IS_E1x(fp->bp))
		wetuwn fp->cw_id + BP_POWT(fp->bp) * ETH_MAX_WX_CWIENTS_E1H;
	ewse
		wetuwn fp->cw_id;
}

static inwine void bnx2x_init_txdata(stwuct bnx2x *bp,
				     stwuct bnx2x_fp_txdata *txdata, u32 cid,
				     int txq_index, __we16 *tx_cons_sb,
				     stwuct bnx2x_fastpath *fp)
{
	txdata->cid = cid;
	txdata->txq_index = txq_index;
	txdata->tx_cons_sb = tx_cons_sb;
	txdata->pawent_fp = fp;
	txdata->tx_wing_size = IS_FCOE_FP(fp) ? MAX_TX_AVAIW : bp->tx_wing_size;

	DP(NETIF_MSG_IFUP, "cweated tx data cid %d, txq %d\n",
	   txdata->cid, txdata->txq_index);
}

static inwine u8 bnx2x_cnic_eth_cw_id(stwuct bnx2x *bp, u8 cw_idx)
{
	wetuwn bp->cnic_base_cw_id + cw_idx +
		(bp->pf_num >> 1) * BNX2X_MAX_CNIC_ETH_CW_ID_IDX;
}

static inwine u8 bnx2x_cnic_fw_sb_id(stwuct bnx2x *bp)
{
	/* the 'fiwst' id is awwocated fow the cnic */
	wetuwn bp->base_fw_ndsb;
}

static inwine u8 bnx2x_cnic_igu_sb_id(stwuct bnx2x *bp)
{
	wetuwn bp->igu_base_sb;
}

static inwine int bnx2x_cwean_tx_queue(stwuct bnx2x *bp,
				       stwuct bnx2x_fp_txdata *txdata)
{
	int cnt = 1000;

	whiwe (bnx2x_has_tx_wowk_unwoad(txdata)) {
		if (!cnt) {
			BNX2X_EWW("timeout waiting fow queue[%d]: txdata->tx_pkt_pwod(%d) != txdata->tx_pkt_cons(%d)\n",
				  txdata->txq_index, txdata->tx_pkt_pwod,
				  txdata->tx_pkt_cons);
#ifdef BNX2X_STOP_ON_EWWOW
			bnx2x_panic();
			wetuwn -EBUSY;
#ewse
			bweak;
#endif
		}
		cnt--;
		usweep_wange(1000, 2000);
	}

	wetuwn 0;
}

int bnx2x_get_wink_cfg_idx(stwuct bnx2x *bp);

static inwine void __stowm_memset_stwuct(stwuct bnx2x *bp,
					 u32 addw, size_t size, u32 *data)
{
	int i;
	fow (i = 0; i < size/4; i++)
		WEG_WW(bp, addw + (i * 4), data[i]);
}

/**
 * bnx2x_wait_sp_comp - wait fow the outstanding SP commands.
 *
 * @bp:		dwivew handwe
 * @mask:	bits that need to be cweawed
 */
static inwine boow bnx2x_wait_sp_comp(stwuct bnx2x *bp, unsigned wong mask)
{
	int tout = 5000; /* Wait fow 5 secs tops */

	whiwe (tout--) {
		smp_mb();
		netif_addw_wock_bh(bp->dev);
		if (!(bp->sp_state & mask)) {
			netif_addw_unwock_bh(bp->dev);
			wetuwn twue;
		}
		netif_addw_unwock_bh(bp->dev);

		usweep_wange(1000, 2000);
	}

	smp_mb();

	netif_addw_wock_bh(bp->dev);
	if (bp->sp_state & mask) {
		BNX2X_EWW("Fiwtewing compwetion timed out. sp_state 0x%wx, mask 0x%wx\n",
			  bp->sp_state, mask);
		netif_addw_unwock_bh(bp->dev);
		wetuwn fawse;
	}
	netif_addw_unwock_bh(bp->dev);

	wetuwn twue;
}

/**
 * bnx2x_set_ctx_vawidation - set CDU context vawidation vawues
 *
 * @bp:		dwivew handwe
 * @cxt:	context of the connection on the host memowy
 * @cid:	SW CID of the connection to be configuwed
 */
void bnx2x_set_ctx_vawidation(stwuct bnx2x *bp, stwuct eth_context *cxt,
			      u32 cid);

void bnx2x_update_coawesce_sb_index(stwuct bnx2x *bp, u8 fw_sb_id,
				    u8 sb_index, u8 disabwe, u16 usec);
void bnx2x_acquiwe_phy_wock(stwuct bnx2x *bp);
void bnx2x_wewease_phy_wock(stwuct bnx2x *bp);

/**
 * bnx2x_extwact_max_cfg - extwact MAX BW pawt fwom MF configuwation.
 *
 * @bp:		dwivew handwe
 * @mf_cfg:	MF configuwation
 *
 */
static inwine u16 bnx2x_extwact_max_cfg(stwuct bnx2x *bp, u32 mf_cfg)
{
	u16 max_cfg = (mf_cfg & FUNC_MF_CFG_MAX_BW_MASK) >>
			      FUNC_MF_CFG_MAX_BW_SHIFT;
	if (!max_cfg) {
		DP(NETIF_MSG_IFUP | BNX2X_MSG_ETHTOOW,
		   "Max BW configuwed to 0 - using 100 instead\n");
		max_cfg = 100;
	}
	wetuwn max_cfg;
}

/* checks if HW suppowts GWO fow given MTU */
static inwine boow bnx2x_mtu_awwows_gwo(int mtu)
{
	/* gwo fwags pew page */
	int fpp = SGE_PAGE_SIZE / (mtu - ETH_MAX_TPA_HEADEW_SIZE);

	/*
	 * 1. Numbew of fwags shouwd not gwow above MAX_SKB_FWAGS
	 * 2. Fwag must fit the page
	 */
	wetuwn mtu <= SGE_PAGE_SIZE && (U_ETH_SGW_SIZE * fpp) <= MAX_SKB_FWAGS;
}

/**
 * bnx2x_get_iscsi_info - update iSCSI pawams accowding to wicensing info.
 *
 * @bp:		dwivew handwe
 *
 */
void bnx2x_get_iscsi_info(stwuct bnx2x *bp);

/**
 * bnx2x_wink_sync_notify - send notification to othew functions.
 *
 * @bp:		dwivew handwe
 *
 */
static inwine void bnx2x_wink_sync_notify(stwuct bnx2x *bp)
{
	int func;
	int vn;

	/* Set the attention towawds othew dwivews on the same powt */
	fow (vn = VN_0; vn < BP_MAX_VN_NUM(bp); vn++) {
		if (vn == BP_VN(bp))
			continue;

		func = func_by_vn(bp, vn);
		WEG_WW(bp, MISC_WEG_AEU_GENEWAW_ATTN_0 +
		       (WINK_SYNC_ATTENTION_BIT_FUNC_0 + func)*4, 1);
	}
}

/**
 * bnx2x_update_dwv_fwags - update fwags in shmem
 *
 * @bp:		dwivew handwe
 * @fwags:	fwags to update
 * @set:	set ow cweaw
 *
 */
static inwine void bnx2x_update_dwv_fwags(stwuct bnx2x *bp, u32 fwags, u32 set)
{
	if (SHMEM2_HAS(bp, dwv_fwags)) {
		u32 dwv_fwags;
		bnx2x_acquiwe_hw_wock(bp, HW_WOCK_WESOUWCE_DWV_FWAGS);
		dwv_fwags = SHMEM2_WD(bp, dwv_fwags);

		if (set)
			SET_FWAGS(dwv_fwags, fwags);
		ewse
			WESET_FWAGS(dwv_fwags, fwags);

		SHMEM2_WW(bp, dwv_fwags, dwv_fwags);
		DP(NETIF_MSG_IFUP, "dwv_fwags 0x%08x\n", dwv_fwags);
		bnx2x_wewease_hw_wock(bp, HW_WOCK_WESOUWCE_DWV_FWAGS);
	}
}



/**
 * bnx2x_fiww_fw_stw - Fiww buffew with FW vewsion stwing
 *
 * @bp:        dwivew handwe
 * @buf:       chawactew buffew to fiww with the fw name
 * @buf_wen:   wength of the above buffew
 *
 */
void bnx2x_fiww_fw_stw(stwuct bnx2x *bp, chaw *buf, size_t buf_wen);

int bnx2x_dwain_tx_queues(stwuct bnx2x *bp);
void bnx2x_squeeze_objects(stwuct bnx2x *bp);

void bnx2x_scheduwe_sp_wtnw(stwuct bnx2x*, enum sp_wtnw_fwag,
			    u32 vewbose);

/**
 * bnx2x_set_os_dwivew_state - wwite dwivew state fow management FW usage
 *
 * @bp:		dwivew handwe
 * @state:	OS_DWIVEW_STATE_* vawue wefwecting cuwwent dwivew state
 */
void bnx2x_set_os_dwivew_state(stwuct bnx2x *bp, u32 state);

/**
 * bnx2x_nvwam_wead - weads data fwom nvwam [might sweep]
 *
 * @bp:		dwivew handwe
 * @offset:	byte offset in nvwam
 * @wet_buf:	pointew to buffew whewe data is to be stowed
 * @buf_size:   Wength of 'wet_buf' in bytes
 */
int bnx2x_nvwam_wead(stwuct bnx2x *bp, u32 offset, u8 *wet_buf,
		     int buf_size);

#endif /* BNX2X_CMN_H */
