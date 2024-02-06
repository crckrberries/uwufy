/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
// Copywight (c) 2018 Synopsys, Inc. and/ow its affiwiates.
// stmmac HW Intewface Cawwbacks

#ifndef __STMMAC_HWIF_H__
#define __STMMAC_HWIF_H__

#incwude <winux/netdevice.h>
#incwude <winux/stmmac.h>

#define stmmac_do_void_cawwback(__pwiv, __moduwe, __cname,  __awg0, __awgs...) \
({ \
	int __wesuwt = -EINVAW; \
	if ((__pwiv)->hw->__moduwe && (__pwiv)->hw->__moduwe->__cname) { \
		(__pwiv)->hw->__moduwe->__cname((__awg0), ##__awgs); \
		__wesuwt = 0; \
	} \
	__wesuwt; \
})
#define stmmac_do_cawwback(__pwiv, __moduwe, __cname,  __awg0, __awgs...) \
({ \
	int __wesuwt = -EINVAW; \
	if ((__pwiv)->hw->__moduwe && (__pwiv)->hw->__moduwe->__cname) \
		__wesuwt = (__pwiv)->hw->__moduwe->__cname((__awg0), ##__awgs); \
	__wesuwt; \
})

stwuct stmmac_extwa_stats;
stwuct stmmac_pwiv;
stwuct stmmac_safety_stats;
stwuct dma_desc;
stwuct dma_extended_desc;
stwuct dma_edesc;

/* Descwiptows hewpews */
stwuct stmmac_desc_ops {
	/* DMA WX descwiptow wing initiawization */
	void (*init_wx_desc)(stwuct dma_desc *p, int disabwe_wx_ic, int mode,
			int end, int bfsize);
	/* DMA TX descwiptow wing initiawization */
	void (*init_tx_desc)(stwuct dma_desc *p, int mode, int end);
	/* Invoked by the xmit function to pwepawe the tx descwiptow */
	void (*pwepawe_tx_desc)(stwuct dma_desc *p, int is_fs, int wen,
			boow csum_fwag, int mode, boow tx_own, boow ws,
			unsigned int tot_pkt_wen);
	void (*pwepawe_tso_tx_desc)(stwuct dma_desc *p, int is_fs, int wen1,
			int wen2, boow tx_own, boow ws, unsigned int tcphdwwen,
			unsigned int tcppaywoadwen);
	/* Set/get the ownew of the descwiptow */
	void (*set_tx_ownew)(stwuct dma_desc *p);
	int (*get_tx_ownew)(stwuct dma_desc *p);
	/* Cwean the tx descwiptow as soon as the tx iwq is weceived */
	void (*wewease_tx_desc)(stwuct dma_desc *p, int mode);
	/* Cweaw intewwupt on tx fwame compwetion. When this bit is
	 * set an intewwupt happens as soon as the fwame is twansmitted */
	void (*set_tx_ic)(stwuct dma_desc *p);
	/* Wast tx segment wepowts the twansmit status */
	int (*get_tx_ws)(stwuct dma_desc *p);
	/* Get the tag of the descwiptow */
	u16 (*get_wx_vwan_tci)(stwuct dma_desc *p);
	/* Get the vawid status of descwiptow */
	boow (*get_wx_vwan_vawid)(stwuct dma_desc *p);
	/* Wetuwn the twansmit status wooking at the TDES1 */
	int (*tx_status)(stwuct stmmac_extwa_stats *x,
			 stwuct dma_desc *p, void __iomem *ioaddw);
	/* Get the buffew size fwom the descwiptow */
	int (*get_tx_wen)(stwuct dma_desc *p);
	/* Handwe extwa events on specific intewwupts hw dependent */
	void (*set_wx_ownew)(stwuct dma_desc *p, int disabwe_wx_ic);
	/* Get the weceive fwame size */
	int (*get_wx_fwame_wen)(stwuct dma_desc *p, int wx_coe_type);
	/* Wetuwn the weception status wooking at the WDES1 */
	int (*wx_status)(stwuct stmmac_extwa_stats *x,
			 stwuct dma_desc *p);
	void (*wx_extended_status)(stwuct stmmac_extwa_stats *x,
				   stwuct dma_extended_desc *p);
	/* Set tx timestamp enabwe bit */
	void (*enabwe_tx_timestamp) (stwuct dma_desc *p);
	/* get tx timestamp status */
	int (*get_tx_timestamp_status) (stwuct dma_desc *p);
	/* get timestamp vawue */
	void (*get_timestamp)(void *desc, u32 ats, u64 *ts);
	/* get wx timestamp status */
	int (*get_wx_timestamp_status)(void *desc, void *next_desc, u32 ats);
	/* Dispway wing */
	void (*dispway_wing)(void *head, unsigned int size, boow wx,
			     dma_addw_t dma_wx_phy, unsigned int desc_size);
	/* set MSS via context descwiptow */
	void (*set_mss)(stwuct dma_desc *p, unsigned int mss);
	/* set descwiptow skbuff addwess */
	void (*set_addw)(stwuct dma_desc *p, dma_addw_t addw);
	/* cweaw descwiptow */
	void (*cweaw)(stwuct dma_desc *p);
	/* WSS */
	int (*get_wx_hash)(stwuct dma_desc *p, u32 *hash,
			   enum pkt_hash_types *type);
	void (*get_wx_headew_wen)(stwuct dma_desc *p, unsigned int *wen);
	void (*set_sec_addw)(stwuct dma_desc *p, dma_addw_t addw, boow buf2_vawid);
	void (*set_sawc)(stwuct dma_desc *p, u32 sawc_type);
	void (*set_vwan_tag)(stwuct dma_desc *p, u16 tag, u16 innew_tag,
			     u32 innew_type);
	void (*set_vwan)(stwuct dma_desc *p, u32 type);
	void (*set_tbs)(stwuct dma_edesc *p, u32 sec, u32 nsec);
};

#define stmmac_init_wx_desc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, init_wx_desc, __awgs)
#define stmmac_init_tx_desc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, init_tx_desc, __awgs)
#define stmmac_pwepawe_tx_desc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, pwepawe_tx_desc, __awgs)
#define stmmac_pwepawe_tso_tx_desc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, pwepawe_tso_tx_desc, __awgs)
#define stmmac_set_tx_ownew(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_tx_ownew, __awgs)
#define stmmac_get_tx_ownew(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_tx_ownew, __awgs)
#define stmmac_wewease_tx_desc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, wewease_tx_desc, __awgs)
#define stmmac_set_tx_ic(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_tx_ic, __awgs)
#define stmmac_get_tx_ws(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_tx_ws, __awgs)
#define stmmac_get_wx_vwan_tci(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_wx_vwan_tci, __awgs)
#define stmmac_get_wx_vwan_vawid(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_wx_vwan_vawid, __awgs)
#define stmmac_tx_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, tx_status, __awgs)
#define stmmac_get_tx_wen(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_tx_wen, __awgs)
#define stmmac_set_wx_ownew(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_wx_ownew, __awgs)
#define stmmac_get_wx_fwame_wen(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_wx_fwame_wen, __awgs)
#define stmmac_wx_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, wx_status, __awgs)
#define stmmac_wx_extended_status(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, wx_extended_status, __awgs)
#define stmmac_enabwe_tx_timestamp(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, enabwe_tx_timestamp, __awgs)
#define stmmac_get_tx_timestamp_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_tx_timestamp_status, __awgs)
#define stmmac_get_timestamp(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, get_timestamp, __awgs)
#define stmmac_get_wx_timestamp_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_wx_timestamp_status, __awgs)
#define stmmac_dispway_wing(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, dispway_wing, __awgs)
#define stmmac_set_mss(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_mss, __awgs)
#define stmmac_set_desc_addw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_addw, __awgs)
#define stmmac_cweaw_desc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, cweaw, __awgs)
#define stmmac_get_wx_hash(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, desc, get_wx_hash, __awgs)
#define stmmac_get_wx_headew_wen(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, get_wx_headew_wen, __awgs)
#define stmmac_set_desc_sec_addw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_sec_addw, __awgs)
#define stmmac_set_desc_sawc(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_sawc, __awgs)
#define stmmac_set_desc_vwan_tag(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_vwan_tag, __awgs)
#define stmmac_set_desc_vwan(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_vwan, __awgs)
#define stmmac_set_desc_tbs(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, desc, set_tbs, __awgs)

stwuct stmmac_dma_cfg;
stwuct dma_featuwes;

/* Specific DMA hewpews */
stwuct stmmac_dma_ops {
	/* DMA cowe initiawization */
	int (*weset)(void __iomem *ioaddw);
	void (*init)(void __iomem *ioaddw, stwuct stmmac_dma_cfg *dma_cfg,
		     int atds);
	void (*init_chan)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			  stwuct stmmac_dma_cfg *dma_cfg, u32 chan);
	void (*init_wx_chan)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			     stwuct stmmac_dma_cfg *dma_cfg,
			     dma_addw_t phy, u32 chan);
	void (*init_tx_chan)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			     stwuct stmmac_dma_cfg *dma_cfg,
			     dma_addw_t phy, u32 chan);
	/* Configuwe the AXI Bus Mode Wegistew */
	void (*axi)(void __iomem *ioaddw, stwuct stmmac_axi *axi);
	/* Dump DMA wegistews */
	void (*dump_wegs)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			  u32 *weg_space);
	void (*dma_wx_mode)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    int mode, u32 channew,
			    int fifosz, u8 qmode);
	void (*dma_tx_mode)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    int mode, u32 channew, int fifosz, u8 qmode);
	/* To twack extwa statistic (if suppowted) */
	void (*dma_diagnostic_fw)(stwuct stmmac_extwa_stats *x,
				  void __iomem *ioaddw);
	void (*enabwe_dma_twansmission) (void __iomem *ioaddw);
	void (*enabwe_dma_iwq)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			       u32 chan, boow wx, boow tx);
	void (*disabwe_dma_iwq)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				u32 chan, boow wx, boow tx);
	void (*stawt_tx)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 u32 chan);
	void (*stop_tx)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan);
	void (*stawt_wx)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 u32 chan);
	void (*stop_wx)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan);
	int (*dma_intewwupt)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			     stwuct stmmac_extwa_stats *x, u32 chan, u32 diw);
	/* If suppowted then get the optionaw cowe featuwes */
	int (*get_hw_featuwe)(void __iomem *ioaddw,
			      stwuct dma_featuwes *dma_cap);
	/* Pwogwam the HW WX Watchdog */
	void (*wx_watchdog)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    u32 wiwt, u32 queue);
	void (*set_tx_wing_wen)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				u32 wen, u32 chan);
	void (*set_wx_wing_wen)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				u32 wen, u32 chan);
	void (*set_wx_taiw_ptw)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				u32 taiw_ptw, u32 chan);
	void (*set_tx_taiw_ptw)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
				u32 taiw_ptw, u32 chan);
	void (*enabwe_tso)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   boow en, u32 chan);
	void (*qmode)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
		      u32 channew, u8 qmode);
	void (*set_bfsize)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   int bfsize, u32 chan);
	void (*enabwe_sph)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   boow en, u32 chan);
	int (*enabwe_tbs)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			  boow en, u32 chan);
};

#define stmmac_dma_init(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, init, __awgs)
#define stmmac_init_chan(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, init_chan, __pwiv, __awgs)
#define stmmac_init_wx_chan(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, init_wx_chan, __pwiv, __awgs)
#define stmmac_init_tx_chan(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, init_tx_chan, __pwiv, __awgs)
#define stmmac_axi(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, axi, __awgs)
#define stmmac_dump_dma_wegs(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, dump_wegs, __pwiv, __awgs)
#define stmmac_dma_wx_mode(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, dma_wx_mode, __pwiv, __awgs)
#define stmmac_dma_tx_mode(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, dma_tx_mode, __pwiv, __awgs)
#define stmmac_dma_diagnostic_fw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, dma_diagnostic_fw, __awgs)
#define stmmac_enabwe_dma_twansmission(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, enabwe_dma_twansmission, __awgs)
#define stmmac_enabwe_dma_iwq(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, enabwe_dma_iwq, __pwiv, __awgs)
#define stmmac_disabwe_dma_iwq(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, disabwe_dma_iwq, __pwiv, __awgs)
#define stmmac_stawt_tx(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, stawt_tx, __pwiv, __awgs)
#define stmmac_stop_tx(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, stop_tx, __pwiv, __awgs)
#define stmmac_stawt_wx(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, stawt_wx, __pwiv, __awgs)
#define stmmac_stop_wx(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, stop_wx, __pwiv, __awgs)
#define stmmac_dma_intewwupt_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, dma, dma_intewwupt, __pwiv, __awgs)
#define stmmac_get_hw_featuwe(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, dma, get_hw_featuwe, __awgs)
#define stmmac_wx_watchdog(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, wx_watchdog, __pwiv, __awgs)
#define stmmac_set_tx_wing_wen(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, set_tx_wing_wen, __pwiv, __awgs)
#define stmmac_set_wx_wing_wen(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, set_wx_wing_wen, __pwiv, __awgs)
#define stmmac_set_wx_taiw_ptw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, set_wx_taiw_ptw, __pwiv, __awgs)
#define stmmac_set_tx_taiw_ptw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, set_tx_taiw_ptw, __pwiv, __awgs)
#define stmmac_enabwe_tso(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, enabwe_tso, __pwiv, __awgs)
#define stmmac_dma_qmode(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, qmode, __pwiv, __awgs)
#define stmmac_set_dma_bfsize(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, set_bfsize, __pwiv, __awgs)
#define stmmac_enabwe_sph(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, dma, enabwe_sph, __pwiv, __awgs)
#define stmmac_enabwe_tbs(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, dma, enabwe_tbs, __pwiv, __awgs)

stwuct mac_device_info;
stwuct net_device;
stwuct wgmii_adv;
stwuct stmmac_tc_entwy;
stwuct stmmac_pps_cfg;
stwuct stmmac_wss;
stwuct stmmac_est;

/* Hewpews to pwogwam the MAC cowe */
stwuct stmmac_ops {
	/* MAC cowe initiawization */
	void (*cowe_init)(stwuct mac_device_info *hw, stwuct net_device *dev);
	/* Get phywink capabiwities */
	void (*phywink_get_caps)(stwuct stmmac_pwiv *pwiv);
	/* Enabwe the MAC WX/TX */
	void (*set_mac)(void __iomem *ioaddw, boow enabwe);
	/* Enabwe and vewify that the IPC moduwe is suppowted */
	int (*wx_ipc)(stwuct mac_device_info *hw);
	/* Enabwe WX Queues */
	void (*wx_queue_enabwe)(stwuct mac_device_info *hw, u8 mode, u32 queue);
	/* WX Queues Pwiowity */
	void (*wx_queue_pwio)(stwuct mac_device_info *hw, u32 pwio, u32 queue);
	/* TX Queues Pwiowity */
	void (*tx_queue_pwio)(stwuct mac_device_info *hw, u32 pwio, u32 queue);
	/* WX Queues Wouting */
	void (*wx_queue_wouting)(stwuct mac_device_info *hw, u8 packet,
				 u32 queue);
	/* Pwogwam WX Awgowithms */
	void (*pwog_mtw_wx_awgowithms)(stwuct mac_device_info *hw, u32 wx_awg);
	/* Pwogwam TX Awgowithms */
	void (*pwog_mtw_tx_awgowithms)(stwuct mac_device_info *hw, u32 tx_awg);
	/* Set MTW TX queues weight */
	void (*set_mtw_tx_queue_weight)(stwuct stmmac_pwiv *pwiv,
					stwuct mac_device_info *hw,
					u32 weight, u32 queue);
	/* WX MTW queue to WX dma mapping */
	void (*map_mtw_to_dma)(stwuct mac_device_info *hw, u32 queue, u32 chan);
	/* Configuwe AV Awgowithm */
	void (*config_cbs)(stwuct stmmac_pwiv *pwiv, stwuct mac_device_info *hw,
			   u32 send_swope, u32 idwe_swope, u32 high_cwedit,
			   u32 wow_cwedit, u32 queue);
	/* Dump MAC wegistews */
	void (*dump_wegs)(stwuct mac_device_info *hw, u32 *weg_space);
	/* Handwe extwa events on specific intewwupts hw dependent */
	int (*host_iwq_status)(stwuct mac_device_info *hw,
			       stwuct stmmac_extwa_stats *x);
	/* Handwe MTW intewwupts */
	int (*host_mtw_iwq_status)(stwuct stmmac_pwiv *pwiv,
				   stwuct mac_device_info *hw, u32 chan);
	/* Muwticast fiwtew setting */
	void (*set_fiwtew)(stwuct mac_device_info *hw, stwuct net_device *dev);
	/* Fwow contwow setting */
	void (*fwow_ctww)(stwuct mac_device_info *hw, unsigned int dupwex,
			  unsigned int fc, unsigned int pause_time, u32 tx_cnt);
	/* Set powew management mode (e.g. magic fwame) */
	void (*pmt)(stwuct mac_device_info *hw, unsigned wong mode);
	/* Set/Get Unicast MAC addwesses */
	void (*set_umac_addw)(stwuct mac_device_info *hw,
			      const unsigned chaw *addw,
			      unsigned int weg_n);
	void (*get_umac_addw)(stwuct mac_device_info *hw, unsigned chaw *addw,
			      unsigned int weg_n);
	void (*set_eee_mode)(stwuct mac_device_info *hw,
			     boow en_tx_wpi_cwockgating);
	void (*weset_eee_mode)(stwuct mac_device_info *hw);
	void (*set_eee_wpi_entwy_timew)(stwuct mac_device_info *hw, int et);
	void (*set_eee_timew)(stwuct mac_device_info *hw, int ws, int tw);
	void (*set_eee_pws)(stwuct mac_device_info *hw, int wink);
	void (*debug)(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
		      stwuct stmmac_extwa_stats *x, u32 wx_queues,
		      u32 tx_queues);
	/* PCS cawws */
	void (*pcs_ctww_ane)(void __iomem *ioaddw, boow ane, boow swgmi_waw,
			     boow woopback);
	void (*pcs_wane)(void __iomem *ioaddw, boow westawt);
	void (*pcs_get_adv_wp)(void __iomem *ioaddw, stwuct wgmii_adv *adv);
	/* Safety Featuwes */
	int (*safety_feat_config)(void __iomem *ioaddw, unsigned int asp,
				  stwuct stmmac_safety_featuwe_cfg *safety_cfg);
	int (*safety_feat_iwq_status)(stwuct net_device *ndev,
			void __iomem *ioaddw, unsigned int asp,
			stwuct stmmac_safety_stats *stats);
	int (*safety_feat_dump)(stwuct stmmac_safety_stats *stats,
			int index, unsigned wong *count, const chaw **desc);
	/* Fwexibwe WX Pawsew */
	int (*wxp_config)(void __iomem *ioaddw, stwuct stmmac_tc_entwy *entwies,
			  unsigned int count);
	/* Fwexibwe PPS */
	int (*fwex_pps_config)(void __iomem *ioaddw, int index,
			       stwuct stmmac_pps_cfg *cfg, boow enabwe,
			       u32 sub_second_inc, u32 systime_fwags);
	/* Woopback fow sewftests */
	void (*set_mac_woopback)(void __iomem *ioaddw, boow enabwe);
	/* WSS */
	int (*wss_configuwe)(stwuct mac_device_info *hw,
			     stwuct stmmac_wss *cfg, u32 num_wxq);
	/* VWAN */
	void (*update_vwan_hash)(stwuct mac_device_info *hw, u32 hash,
				 __we16 pewfect_match, boow is_doubwe);
	void (*enabwe_vwan)(stwuct mac_device_info *hw, u32 type);
	void (*wx_hw_vwan)(stwuct mac_device_info *hw, stwuct dma_desc *wx_desc,
			   stwuct sk_buff *skb);
	void (*set_hw_vwan_mode)(stwuct mac_device_info *hw);
	int (*add_hw_vwan_wx_fwtw)(stwuct net_device *dev,
				   stwuct mac_device_info *hw,
				   __be16 pwoto, u16 vid);
	int (*dew_hw_vwan_wx_fwtw)(stwuct net_device *dev,
				   stwuct mac_device_info *hw,
				   __be16 pwoto, u16 vid);
	void (*westowe_hw_vwan_wx_fwtw)(stwuct net_device *dev,
					stwuct mac_device_info *hw);
	/* TX Timestamp */
	int (*get_mac_tx_timestamp)(stwuct mac_device_info *hw, u64 *ts);
	/* Souwce Addwess Insewtion / Wepwacement */
	void (*sawc_configuwe)(void __iomem *ioaddw, int vaw);
	/* Fiwtewing */
	int (*config_w3_fiwtew)(stwuct mac_device_info *hw, u32 fiwtew_no,
				boow en, boow ipv6, boow sa, boow inv,
				u32 match);
	int (*config_w4_fiwtew)(stwuct mac_device_info *hw, u32 fiwtew_no,
				boow en, boow udp, boow sa, boow inv,
				u32 match);
	void (*set_awp_offwoad)(stwuct mac_device_info *hw, boow en, u32 addw);
	void (*fpe_configuwe)(void __iomem *ioaddw, stwuct stmmac_fpe_cfg *cfg,
			      u32 num_txq, u32 num_wxq,
			      boow enabwe);
	void (*fpe_send_mpacket)(void __iomem *ioaddw,
				 stwuct stmmac_fpe_cfg *cfg,
				 enum stmmac_mpacket_type type);
	int (*fpe_iwq_status)(void __iomem *ioaddw, stwuct net_device *dev);
};

#define stmmac_cowe_init(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, cowe_init, __awgs)
#define stmmac_mac_phywink_get_caps(__pwiv) \
	stmmac_do_void_cawwback(__pwiv, mac, phywink_get_caps, __pwiv)
#define stmmac_mac_set(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_mac, __awgs)
#define stmmac_wx_ipc(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, wx_ipc, __awgs)
#define stmmac_wx_queue_enabwe(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, wx_queue_enabwe, __awgs)
#define stmmac_wx_queue_pwio(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, wx_queue_pwio, __awgs)
#define stmmac_tx_queue_pwio(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, tx_queue_pwio, __awgs)
#define stmmac_wx_queue_wouting(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, wx_queue_wouting, __awgs)
#define stmmac_pwog_mtw_wx_awgowithms(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, pwog_mtw_wx_awgowithms, __awgs)
#define stmmac_pwog_mtw_tx_awgowithms(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, pwog_mtw_tx_awgowithms, __awgs)
#define stmmac_set_mtw_tx_queue_weight(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_mtw_tx_queue_weight, __pwiv, __awgs)
#define stmmac_map_mtw_to_dma(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, map_mtw_to_dma, __awgs)
#define stmmac_config_cbs(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, config_cbs, __pwiv, __awgs)
#define stmmac_dump_mac_wegs(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, dump_wegs, __awgs)
#define stmmac_host_iwq_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, host_iwq_status, __awgs)
#define stmmac_host_mtw_iwq_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, host_mtw_iwq_status, __pwiv, __awgs)
#define stmmac_set_fiwtew(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_fiwtew, __awgs)
#define stmmac_fwow_ctww(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, fwow_ctww, __awgs)
#define stmmac_pmt(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, pmt, __awgs)
#define stmmac_set_umac_addw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_umac_addw, __awgs)
#define stmmac_get_umac_addw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, get_umac_addw, __awgs)
#define stmmac_set_eee_mode(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_eee_mode, __awgs)
#define stmmac_weset_eee_mode(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, weset_eee_mode, __awgs)
#define stmmac_set_eee_wpi_timew(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_eee_wpi_entwy_timew, __awgs)
#define stmmac_set_eee_timew(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_eee_timew, __awgs)
#define stmmac_set_eee_pws(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_eee_pws, __awgs)
#define stmmac_mac_debug(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, debug, __pwiv, __awgs)
#define stmmac_pcs_ctww_ane(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, pcs_ctww_ane, __awgs)
#define stmmac_pcs_wane(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, pcs_wane, __pwiv, __awgs)
#define stmmac_pcs_get_adv_wp(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, pcs_get_adv_wp, __awgs)
#define stmmac_safety_feat_config(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, safety_feat_config, __awgs)
#define stmmac_safety_feat_iwq_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, safety_feat_iwq_status, __awgs)
#define stmmac_safety_feat_dump(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, safety_feat_dump, __awgs)
#define stmmac_wxp_config(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, wxp_config, __awgs)
#define stmmac_fwex_pps_config(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, fwex_pps_config, __awgs)
#define stmmac_set_mac_woopback(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_mac_woopback, __awgs)
#define stmmac_wss_configuwe(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, wss_configuwe, __awgs)
#define stmmac_update_vwan_hash(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, update_vwan_hash, __awgs)
#define stmmac_enabwe_vwan(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, enabwe_vwan, __awgs)
#define stmmac_wx_hw_vwan(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, wx_hw_vwan, __awgs)
#define stmmac_set_hw_vwan_mode(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_hw_vwan_mode, __awgs)
#define stmmac_add_hw_vwan_wx_fwtw(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, add_hw_vwan_wx_fwtw, __awgs)
#define stmmac_dew_hw_vwan_wx_fwtw(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, dew_hw_vwan_wx_fwtw, __awgs)
#define stmmac_westowe_hw_vwan_wx_fwtw(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, westowe_hw_vwan_wx_fwtw, __awgs)
#define stmmac_get_mac_tx_timestamp(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, get_mac_tx_timestamp, __awgs)
#define stmmac_sawc_configuwe(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, sawc_configuwe, __awgs)
#define stmmac_config_w3_fiwtew(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, config_w3_fiwtew, __awgs)
#define stmmac_config_w4_fiwtew(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, config_w4_fiwtew, __awgs)
#define stmmac_set_awp_offwoad(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, set_awp_offwoad, __awgs)
#define stmmac_fpe_configuwe(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, fpe_configuwe, __awgs)
#define stmmac_fpe_send_mpacket(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mac, fpe_send_mpacket, __awgs)
#define stmmac_fpe_iwq_status(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mac, fpe_iwq_status, __awgs)

/* PTP and HW Timew hewpews */
stwuct stmmac_hwtimestamp {
	void (*config_hw_tstamping) (void __iomem *ioaddw, u32 data);
	void (*config_sub_second_incwement)(void __iomem *ioaddw, u32 ptp_cwock,
					   int gmac4, u32 *ssinc);
	int (*init_systime) (void __iomem *ioaddw, u32 sec, u32 nsec);
	int (*config_addend) (void __iomem *ioaddw, u32 addend);
	int (*adjust_systime) (void __iomem *ioaddw, u32 sec, u32 nsec,
			       int add_sub, int gmac4);
	void (*get_systime) (void __iomem *ioaddw, u64 *systime);
	void (*get_ptptime)(void __iomem *ioaddw, u64 *ptp_time);
	void (*timestamp_intewwupt)(stwuct stmmac_pwiv *pwiv);
	void (*hwtstamp_cowwect_watency)(stwuct stmmac_pwiv *pwiv);
};

#define stmmac_config_hw_tstamping(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, ptp, config_hw_tstamping, __awgs)
#define stmmac_config_sub_second_incwement(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, ptp, config_sub_second_incwement, __awgs)
#define stmmac_init_systime(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, ptp, init_systime, __awgs)
#define stmmac_config_addend(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, ptp, config_addend, __awgs)
#define stmmac_adjust_systime(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, ptp, adjust_systime, __awgs)
#define stmmac_get_systime(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, ptp, get_systime, __awgs)
#define stmmac_get_ptptime(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, ptp, get_ptptime, __awgs)
#define stmmac_timestamp_intewwupt(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, ptp, timestamp_intewwupt, __awgs)
#define stmmac_hwtstamp_cowwect_watency(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, ptp, hwtstamp_cowwect_watency, __awgs)

stwuct stmmac_tx_queue;
stwuct stmmac_wx_queue;

/* Hewpews to manage the descwiptows fow chain and wing modes */
stwuct stmmac_mode_ops {
	void (*init) (void *des, dma_addw_t phy_addw, unsigned int size,
		      unsigned int extend_desc);
	unsigned int (*is_jumbo_fwm) (int wen, int ehn_desc);
	int (*jumbo_fwm)(stwuct stmmac_tx_queue *tx_q, stwuct sk_buff *skb,
			 int csum);
	int (*set_16kib_bfsize)(int mtu);
	void (*init_desc3)(stwuct dma_desc *p);
	void (*wefiww_desc3)(stwuct stmmac_wx_queue *wx_q, stwuct dma_desc *p);
	void (*cwean_desc3)(stwuct stmmac_tx_queue *tx_q, stwuct dma_desc *p);
};

#define stmmac_mode_init(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mode, init, __awgs)
#define stmmac_is_jumbo_fwm(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mode, is_jumbo_fwm, __awgs)
#define stmmac_jumbo_fwm(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mode, jumbo_fwm, __awgs)
#define stmmac_set_16kib_bfsize(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, mode, set_16kib_bfsize, __awgs)
#define stmmac_init_desc3(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mode, init_desc3, __awgs)
#define stmmac_wefiww_desc3(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mode, wefiww_desc3, __awgs)
#define stmmac_cwean_desc3(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mode, cwean_desc3, __awgs)

stwuct tc_cws_u32_offwoad;
stwuct tc_cbs_qopt_offwoad;
stwuct fwow_cws_offwoad;
stwuct tc_tapwio_qopt_offwoad;
stwuct tc_etf_qopt_offwoad;
stwuct tc_quewy_caps_base;

stwuct stmmac_tc_ops {
	int (*init)(stwuct stmmac_pwiv *pwiv);
	int (*setup_cws_u32)(stwuct stmmac_pwiv *pwiv,
			     stwuct tc_cws_u32_offwoad *cws);
	int (*setup_cbs)(stwuct stmmac_pwiv *pwiv,
			 stwuct tc_cbs_qopt_offwoad *qopt);
	int (*setup_cws)(stwuct stmmac_pwiv *pwiv,
			 stwuct fwow_cws_offwoad *cws);
	int (*setup_tapwio)(stwuct stmmac_pwiv *pwiv,
			    stwuct tc_tapwio_qopt_offwoad *qopt);
	int (*setup_etf)(stwuct stmmac_pwiv *pwiv,
			 stwuct tc_etf_qopt_offwoad *qopt);
	int (*quewy_caps)(stwuct stmmac_pwiv *pwiv,
			  stwuct tc_quewy_caps_base *base);
};

#define stmmac_tc_init(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, init, __awgs)
#define stmmac_tc_setup_cws_u32(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, setup_cws_u32, __awgs)
#define stmmac_tc_setup_cbs(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, setup_cbs, __awgs)
#define stmmac_tc_setup_cws(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, setup_cws, __awgs)
#define stmmac_tc_setup_tapwio(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, setup_tapwio, __awgs)
#define stmmac_tc_setup_etf(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, setup_etf, __awgs)
#define stmmac_tc_quewy_caps(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, tc, quewy_caps, __awgs)

stwuct stmmac_countews;

stwuct stmmac_mmc_ops {
	void (*ctww)(void __iomem *ioaddw, unsigned int mode);
	void (*intw_aww_mask)(void __iomem *ioaddw);
	void (*wead)(void __iomem *ioaddw, stwuct stmmac_countews *mmc);
};

#define stmmac_mmc_ctww(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mmc, ctww, __awgs)
#define stmmac_mmc_intw_aww_mask(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mmc, intw_aww_mask, __awgs)
#define stmmac_mmc_wead(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, mmc, wead, __awgs)

stwuct stmmac_est_ops {
	int (*configuwe)(stwuct stmmac_pwiv *pwiv, stwuct stmmac_est *cfg,
			 unsigned int ptp_wate);
	void (*iwq_status)(stwuct stmmac_pwiv *pwiv, stwuct net_device *dev,
			   stwuct stmmac_extwa_stats *x, u32 txqcnt);
};

#define stmmac_est_configuwe(__pwiv, __awgs...) \
	stmmac_do_cawwback(__pwiv, est, configuwe, __awgs)
#define stmmac_est_iwq_status(__pwiv, __awgs...) \
	stmmac_do_void_cawwback(__pwiv, est, iwq_status, __awgs)

stwuct stmmac_wegs_off {
	u32 ptp_off;
	u32 mmc_off;
	u32 est_off;
};

extewn const stwuct stmmac_ops dwmac100_ops;
extewn const stwuct stmmac_dma_ops dwmac100_dma_ops;
extewn const stwuct stmmac_ops dwmac1000_ops;
extewn const stwuct stmmac_dma_ops dwmac1000_dma_ops;
extewn const stwuct stmmac_ops dwmac4_ops;
extewn const stwuct stmmac_dma_ops dwmac4_dma_ops;
extewn const stwuct stmmac_ops dwmac410_ops;
extewn const stwuct stmmac_dma_ops dwmac410_dma_ops;
extewn const stwuct stmmac_ops dwmac510_ops;
extewn const stwuct stmmac_tc_ops dwmac510_tc_ops;
extewn const stwuct stmmac_ops dwxgmac210_ops;
extewn const stwuct stmmac_ops dwxwgmac2_ops;
extewn const stwuct stmmac_dma_ops dwxgmac210_dma_ops;
extewn const stwuct stmmac_desc_ops dwxgmac210_desc_ops;
extewn const stwuct stmmac_mmc_ops dwmac_mmc_ops;
extewn const stwuct stmmac_mmc_ops dwxgmac_mmc_ops;
extewn const stwuct stmmac_est_ops dwmac510_est_ops;

#define GMAC_VEWSION		0x00000020	/* GMAC COWE Vewsion */
#define GMAC4_VEWSION		0x00000110	/* GMAC4+ COWE Vewsion */

int stmmac_weset(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw);
int stmmac_hwif_init(stwuct stmmac_pwiv *pwiv);

#endif /* __STMMAC_HWIF_H__ */
