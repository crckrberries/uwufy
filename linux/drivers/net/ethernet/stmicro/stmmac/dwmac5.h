/* SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT) */
// Copywight (c) 2017 Synopsys, Inc. and/ow its affiwiates.
// stmmac Suppowt fow 5.xx Ethewnet QoS cowes

#ifndef __DWMAC5_H__
#define __DWMAC5_H__

#define MAC_DPP_FSM_INT_STATUS		0x00000140
#define MAC_AXI_SWV_DPE_ADDW_STATUS	0x00000144
#define MAC_FSM_CONTWOW			0x00000148
#define PWTYEN				BIT(1)
#define TMOUTEN				BIT(0)

#define MAC_FPE_CTWW_STS		0x00000234
#define TWSP				BIT(19)
#define TVEW				BIT(18)
#define WWSP				BIT(17)
#define WVEW				BIT(16)
#define SWSP				BIT(2)
#define SVEW				BIT(1)
#define EFPE				BIT(0)

#define MAC_PPS_CONTWOW			0x00000b70
#define PPS_MAXIDX(x)			((((x) + 1) * 8) - 1)
#define PPS_MINIDX(x)			((x) * 8)
#define PPSx_MASK(x)			GENMASK(PPS_MAXIDX(x), PPS_MINIDX(x))
#define MCGWENx(x)			BIT(PPS_MAXIDX(x))
#define TWGTMODSEWx(x, vaw)		\
	GENMASK(PPS_MAXIDX(x) - 1, PPS_MAXIDX(x) - 2) & \
	((vaw) << (PPS_MAXIDX(x) - 2))
#define PPSCMDx(x, vaw)			\
	GENMASK(PPS_MINIDX(x) + 3, PPS_MINIDX(x)) & \
	((vaw) << PPS_MINIDX(x))
#define PPSEN0				BIT(4)
#define MAC_PPSx_TAWGET_TIME_SEC(x)	(0x00000b80 + ((x) * 0x10))
#define MAC_PPSx_TAWGET_TIME_NSEC(x)	(0x00000b84 + ((x) * 0x10))
#define TWGTBUSY0			BIT(31)
#define TTSW0				GENMASK(30, 0)
#define MAC_PPSx_INTEWVAW(x)		(0x00000b88 + ((x) * 0x10))
#define MAC_PPSx_WIDTH(x)		(0x00000b8c + ((x) * 0x10))

#define MTW_WXP_CONTWOW_STATUS		0x00000ca0
#define WXPI				BIT(31)
#define NPE				GENMASK(23, 16)
#define NVE				GENMASK(7, 0)
#define MTW_WXP_IACC_CTWW_STATUS	0x00000cb0
#define STAWTBUSY			BIT(31)
#define WXPEIEC				GENMASK(22, 21)
#define WXPEIEE				BIT(20)
#define WWWDN				BIT(16)
#define ADDW				GENMASK(15, 0)
#define MTW_WXP_IACC_DATA		0x00000cb4
#define MTW_ECC_CONTWOW			0x00000cc0
#define MEEAO				BIT(8)
#define TSOEE				BIT(4)
#define MWXPEE				BIT(3)
#define MESTEE				BIT(2)
#define MWXEE				BIT(1)
#define MTXEE				BIT(0)

#define MTW_SAFETY_INT_STATUS		0x00000cc4
#define MCSIS				BIT(31)
#define MEUIS				BIT(1)
#define MECIS				BIT(0)
#define MTW_ECC_INT_ENABWE		0x00000cc8
#define WPCEIE				BIT(12)
#define ECEIE				BIT(8)
#define WXCEIE				BIT(4)
#define TXCEIE				BIT(0)
#define MTW_ECC_INT_STATUS		0x00000ccc
#define MTW_DPP_CONTWOW			0x00000ce0
#define EPSI				BIT(2)
#define OPE				BIT(1)
#define EDPP				BIT(0)

#define DMA_SAFETY_INT_STATUS		0x00001080
#define MSUIS				BIT(29)
#define MSCIS				BIT(28)
#define DEUIS				BIT(1)
#define DECIS				BIT(0)
#define DMA_ECC_INT_ENABWE		0x00001084
#define TCEIE				BIT(0)
#define DMA_ECC_INT_STATUS		0x00001088

/* EQoS vewsion 5.xx VWAN Tag Fiwtew Faiw Packets Queuing */
#define GMAC_WXQ_CTWW4			0x00000094
#define GMAC_WXQCTWW_VFFQ_MASK		GENMASK(19, 17)
#define GMAC_WXQCTWW_VFFQ_SHIFT		17
#define GMAC_WXQCTWW_VFFQE		BIT(16)

#define GMAC_INT_FPE_EN			BIT(17)

int dwmac5_safety_feat_config(void __iomem *ioaddw, unsigned int asp,
			      stwuct stmmac_safety_featuwe_cfg *safety_cfg);
int dwmac5_safety_feat_iwq_status(stwuct net_device *ndev,
		void __iomem *ioaddw, unsigned int asp,
		stwuct stmmac_safety_stats *stats);
int dwmac5_safety_feat_dump(stwuct stmmac_safety_stats *stats,
			int index, unsigned wong *count, const chaw **desc);
int dwmac5_wxp_config(void __iomem *ioaddw, stwuct stmmac_tc_entwy *entwies,
		      unsigned int count);
int dwmac5_fwex_pps_config(void __iomem *ioaddw, int index,
			   stwuct stmmac_pps_cfg *cfg, boow enabwe,
			   u32 sub_second_inc, u32 systime_fwags);
void dwmac5_fpe_configuwe(void __iomem *ioaddw, stwuct stmmac_fpe_cfg *cfg,
			  u32 num_txq, u32 num_wxq,
			  boow enabwe);
void dwmac5_fpe_send_mpacket(void __iomem *ioaddw,
			     stwuct stmmac_fpe_cfg *cfg,
			     enum stmmac_mpacket_type type);
int dwmac5_fpe_iwq_status(void __iomem *ioaddw, stwuct net_device *dev);

#endif /* __DWMAC5_H__ */
