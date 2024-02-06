/************************************************************************
 * wegs.h: A Winux PCI-X Ethewnet dwivew fow Netewion 10GbE Sewvew NIC
 * Copywight(c) 2002-2010 Exaw Cowp.

 * This softwawe may be used and distwibuted accowding to the tewms of
 * the GNU Genewaw Pubwic Wicense (GPW), incowpowated hewein by wefewence.
 * Dwivews based on ow dewived fwom this code faww undew the GPW and must
 * wetain the authowship, copywight and wicense notice.  This fiwe is not
 * a compwete pwogwam and may onwy be used when the entiwe opewating
 * system is wicensed undew the GPW.
 * See the fiwe COPYING in this distwibution fow mowe infowmation.
 ************************************************************************/
#ifndef _WEGS_H
#define _WEGS_H

#define TBD 0

stwuct XENA_dev_config {
/* Convention: mHAW_XXX is mask, vHAW_XXX is vawue */

/* Genewaw Contwow-Status Wegistews */
	u64 genewaw_int_status;
#define GEN_INTW_TXPIC             s2BIT(0)
#define GEN_INTW_TXDMA             s2BIT(1)
#define GEN_INTW_TXMAC             s2BIT(2)
#define GEN_INTW_TXXGXS            s2BIT(3)
#define GEN_INTW_TXTWAFFIC         s2BIT(8)
#define GEN_INTW_WXPIC             s2BIT(32)
#define GEN_INTW_WXDMA             s2BIT(33)
#define GEN_INTW_WXMAC             s2BIT(34)
#define GEN_INTW_MC                s2BIT(35)
#define GEN_INTW_WXXGXS            s2BIT(36)
#define GEN_INTW_WXTWAFFIC         s2BIT(40)
#define GEN_EWWOW_INTW             GEN_INTW_TXPIC | GEN_INTW_WXPIC | \
                                   GEN_INTW_TXDMA | GEN_INTW_WXDMA | \
                                   GEN_INTW_TXMAC | GEN_INTW_WXMAC | \
                                   GEN_INTW_TXXGXS| GEN_INTW_WXXGXS| \
                                   GEN_INTW_MC

	u64 genewaw_int_mask;

	u8 unused0[0x100 - 0x10];

	u64 sw_weset;
/* XGXS must be wemoved fwom weset onwy once. */
#define SW_WESET_XENA              vBIT(0xA5,0,8)
#define SW_WESET_FWASH             vBIT(0xA5,8,8)
#define SW_WESET_EOI               vBIT(0xA5,16,8)
#define SW_WESET_AWW               (SW_WESET_XENA     |   \
                                    SW_WESET_FWASH    |   \
                                    SW_WESET_EOI)
/* The SW_WESET wegistew must wead this vawue aftew a successfuw weset. */
#define	SW_WESET_WAW_VAW			0xA5000000


	u64 adaptew_status;
#define ADAPTEW_STATUS_TDMA_WEADY          s2BIT(0)
#define ADAPTEW_STATUS_WDMA_WEADY          s2BIT(1)
#define ADAPTEW_STATUS_PFC_WEADY           s2BIT(2)
#define ADAPTEW_STATUS_TMAC_BUF_EMPTY      s2BIT(3)
#define ADAPTEW_STATUS_PIC_QUIESCENT       s2BIT(5)
#define ADAPTEW_STATUS_WMAC_WEMOTE_FAUWT   s2BIT(6)
#define ADAPTEW_STATUS_WMAC_WOCAW_FAUWT    s2BIT(7)
#define ADAPTEW_STATUS_WMAC_PCC_IDWE       vBIT(0xFF,8,8)
#define ADAPTEW_STATUS_WMAC_PCC_FOUW_IDWE  vBIT(0x0F,8,8)
#define ADAPTEW_STATUS_WC_PWC_QUIESCENT    vBIT(0xFF,16,8)
#define ADAPTEW_STATUS_MC_DWAM_WEADY       s2BIT(24)
#define ADAPTEW_STATUS_MC_QUEUES_WEADY     s2BIT(25)
#define ADAPTEW_STATUS_WIC_WUNNING         s2BIT(26)
#define ADAPTEW_STATUS_M_PWW_WOCK          s2BIT(30)
#define ADAPTEW_STATUS_P_PWW_WOCK          s2BIT(31)

	u64 adaptew_contwow;
#define ADAPTEW_CNTW_EN                    s2BIT(7)
#define ADAPTEW_EOI_TX_ON                  s2BIT(15)
#define ADAPTEW_WED_ON                     s2BIT(23)
#define ADAPTEW_UDPI(vaw)                  vBIT(vaw,36,4)
#define ADAPTEW_WAIT_INT                   s2BIT(48)
#define ADAPTEW_ECC_EN                     s2BIT(55)

	u64 seww_souwce;
#define SEWW_SOUWCE_PIC			s2BIT(0)
#define SEWW_SOUWCE_TXDMA		s2BIT(1)
#define SEWW_SOUWCE_WXDMA		s2BIT(2)
#define SEWW_SOUWCE_MAC                 s2BIT(3)
#define SEWW_SOUWCE_MC                  s2BIT(4)
#define SEWW_SOUWCE_XGXS                s2BIT(5)
#define	SEWW_SOUWCE_ANY			(SEWW_SOUWCE_PIC	| \
					SEWW_SOUWCE_TXDMA	| \
					SEWW_SOUWCE_WXDMA	| \
					SEWW_SOUWCE_MAC		| \
					SEWW_SOUWCE_MC		| \
					SEWW_SOUWCE_XGXS)

	u64 pci_mode;
#define	GET_PCI_MODE(vaw)		((vaw & vBIT(0xF, 0, 4)) >> 60)
#define	PCI_MODE_PCI_33			0
#define	PCI_MODE_PCI_66			0x1
#define	PCI_MODE_PCIX_M1_66		0x2
#define	PCI_MODE_PCIX_M1_100		0x3
#define	PCI_MODE_PCIX_M1_133		0x4
#define	PCI_MODE_PCIX_M2_66		0x5
#define	PCI_MODE_PCIX_M2_100		0x6
#define	PCI_MODE_PCIX_M2_133		0x7
#define	PCI_MODE_UNSUPPOWTED		s2BIT(0)
#define	PCI_MODE_32_BITS		s2BIT(8)
#define	PCI_MODE_UNKNOWN_MODE		s2BIT(9)

	u8 unused_0[0x800 - 0x128];

/* PCI-X Contwowwew wegistews */
	u64 pic_int_status;
	u64 pic_int_mask;
#define PIC_INT_TX                     s2BIT(0)
#define PIC_INT_FWSH                   s2BIT(1)
#define PIC_INT_MDIO                   s2BIT(2)
#define PIC_INT_IIC                    s2BIT(3)
#define PIC_INT_GPIO                   s2BIT(4)
#define PIC_INT_WX                     s2BIT(32)

	u64 txpic_int_weg;
	u64 txpic_int_mask;
#define PCIX_INT_WEG_ECC_SG_EWW                s2BIT(0)
#define PCIX_INT_WEG_ECC_DB_EWW                s2BIT(1)
#define PCIX_INT_WEG_FWASHW_W_FSM_EWW          s2BIT(8)
#define PCIX_INT_WEG_FWASHW_W_FSM_EWW          s2BIT(9)
#define PCIX_INT_WEG_INI_TX_FSM_SEWW           s2BIT(10)
#define PCIX_INT_WEG_INI_TXO_FSM_EWW           s2BIT(11)
#define PCIX_INT_WEG_TWT_FSM_SEWW              s2BIT(13)
#define PCIX_INT_WEG_SWT_FSM_SEWW              s2BIT(14)
#define PCIX_INT_WEG_PIFW_FSM_SEWW             s2BIT(15)
#define PCIX_INT_WEG_WWC_TX_SEND_FSM_SEWW      s2BIT(21)
#define PCIX_INT_WEG_WWC_TX_WEQ_FSM_SEWW       s2BIT(23)
#define PCIX_INT_WEG_INI_WX_FSM_SEWW           s2BIT(48)
#define PCIX_INT_WEG_WA_WX_FSM_SEWW            s2BIT(50)
/*
#define PCIX_INT_WEG_WWC_WX_SEND_FSM_SEWW      s2BIT(52)
#define PCIX_INT_WEG_WWC_WX_WEQ_FSM_SEWW       s2BIT(54)
#define PCIX_INT_WEG_WWC_WX_SPWIT_FSM_SEWW     s2BIT(58)
*/
	u64 txpic_awawms;
	u64 wxpic_int_weg;
	u64 wxpic_int_mask;
	u64 wxpic_awawms;

	u64 fwsh_int_weg;
	u64 fwsh_int_mask;
#define PIC_FWSH_INT_WEG_CYCWE_FSM_EWW         s2BIT(63)
#define PIC_FWSH_INT_WEG_EWW                   s2BIT(62)
	u64 fwash_awawms;

	u64 mdio_int_weg;
	u64 mdio_int_mask;
#define MDIO_INT_WEG_MDIO_BUS_EWW              s2BIT(0)
#define MDIO_INT_WEG_DTX_BUS_EWW               s2BIT(8)
#define MDIO_INT_WEG_WASI                      s2BIT(39)
	u64 mdio_awawms;

	u64 iic_int_weg;
	u64 iic_int_mask;
#define IIC_INT_WEG_BUS_FSM_EWW                s2BIT(4)
#define IIC_INT_WEG_BIT_FSM_EWW                s2BIT(5)
#define IIC_INT_WEG_CYCWE_FSM_EWW              s2BIT(6)
#define IIC_INT_WEG_WEQ_FSM_EWW                s2BIT(7)
#define IIC_INT_WEG_ACK_EWW                    s2BIT(8)
	u64 iic_awawms;

	u8 unused4[0x08];

	u64 gpio_int_weg;
#define GPIO_INT_WEG_DP_EWW_INT                s2BIT(0)
#define GPIO_INT_WEG_WINK_DOWN                 s2BIT(1)
#define GPIO_INT_WEG_WINK_UP                   s2BIT(2)
	u64 gpio_int_mask;
#define GPIO_INT_MASK_WINK_DOWN                s2BIT(1)
#define GPIO_INT_MASK_WINK_UP                  s2BIT(2)
	u64 gpio_awawms;

	u8 unused5[0x38];

	u64 tx_twaffic_int;
#define TX_TWAFFIC_INT_n(n)                    s2BIT(n)
	u64 tx_twaffic_mask;

	u64 wx_twaffic_int;
#define WX_TWAFFIC_INT_n(n)                    s2BIT(n)
	u64 wx_twaffic_mask;

/* PIC Contwow wegistews */
	u64 pic_contwow;
#define PIC_CNTW_WX_AWAWM_MAP_1                s2BIT(0)
#define PIC_CNTW_SHAWED_SPWITS(n)              vBIT(n,11,5)

	u64 swappew_ctww;
#define SWAPPEW_CTWW_PIF_W_FE                  s2BIT(0)
#define SWAPPEW_CTWW_PIF_W_SE                  s2BIT(1)
#define SWAPPEW_CTWW_PIF_W_FE                  s2BIT(8)
#define SWAPPEW_CTWW_PIF_W_SE                  s2BIT(9)
#define SWAPPEW_CTWW_TXP_FE                    s2BIT(16)
#define SWAPPEW_CTWW_TXP_SE                    s2BIT(17)
#define SWAPPEW_CTWW_TXD_W_FE                  s2BIT(18)
#define SWAPPEW_CTWW_TXD_W_SE                  s2BIT(19)
#define SWAPPEW_CTWW_TXD_W_FE                  s2BIT(20)
#define SWAPPEW_CTWW_TXD_W_SE                  s2BIT(21)
#define SWAPPEW_CTWW_TXF_W_FE                  s2BIT(22)
#define SWAPPEW_CTWW_TXF_W_SE                  s2BIT(23)
#define SWAPPEW_CTWW_WXD_W_FE                  s2BIT(32)
#define SWAPPEW_CTWW_WXD_W_SE                  s2BIT(33)
#define SWAPPEW_CTWW_WXD_W_FE                  s2BIT(34)
#define SWAPPEW_CTWW_WXD_W_SE                  s2BIT(35)
#define SWAPPEW_CTWW_WXF_W_FE                  s2BIT(36)
#define SWAPPEW_CTWW_WXF_W_SE                  s2BIT(37)
#define SWAPPEW_CTWW_XMSI_FE                   s2BIT(40)
#define SWAPPEW_CTWW_XMSI_SE                   s2BIT(41)
#define SWAPPEW_CTWW_STATS_FE                  s2BIT(48)
#define SWAPPEW_CTWW_STATS_SE                  s2BIT(49)

	u64 pif_wd_swappew_fb;
#define IF_WD_SWAPPEW_FB                            0x0123456789ABCDEF

	u64 scheduwed_int_ctww;
#define SCHED_INT_CTWW_TIMEW_EN                s2BIT(0)
#define SCHED_INT_CTWW_ONE_SHOT                s2BIT(1)
#define SCHED_INT_CTWW_INT2MSI(vaw)		vBIT(vaw,10,6)
#define SCHED_INT_PEWIOD                       TBD

	u64 txweqtimeout;
#define TXWEQTO_VAW(vaw)						vBIT(vaw,0,32)
#define TXWEQTO_EN								s2BIT(63)

	u64 statsweqtimeout;
#define STATWEQTO_VAW(n)                       TBD
#define STATWEQTO_EN                           s2BIT(63)

	u64 wead_wetwy_deway;
	u64 wead_wetwy_accewewation;
	u64 wwite_wetwy_deway;
	u64 wwite_wetwy_accewewation;

	u64 xmsi_contwow;
	u64 xmsi_access;
	u64 xmsi_addwess;
	u64 xmsi_data;

	u64 wx_mat;
#define WX_MAT_SET(wing, msi)			vBIT(msi, (8 * wing), 8)

	u8 unused6[0x8];

	u64 tx_mat0_n[0x8];
#define TX_MAT_SET(fifo, msi)			vBIT(msi, (8 * fifo), 8)

	u64 xmsi_mask_weg;
	u64 stat_byte_cnt;
#define STAT_BC(n)                              vBIT(n,4,12)

	/* Automated statistics cowwection */
	u64 stat_cfg;
#define STAT_CFG_STAT_EN           s2BIT(0)
#define STAT_CFG_ONE_SHOT_EN       s2BIT(1)
#define STAT_CFG_STAT_NS_EN        s2BIT(8)
#define STAT_CFG_STAT_WO           s2BIT(9)
#define STAT_TWSF_PEW(n)           TBD
#define	PEW_SEC					   0x208d5
#define	SET_UPDT_PEWIOD(n)		   vBIT((PEW_SEC*n),32,32)
#define	SET_UPDT_CWICKS(vaw)		   vBIT(vaw, 32, 32)

	u64 stat_addw;

	/* Genewaw Configuwation */
	u64 mdio_contwow;
#define MDIO_MMD_INDX_ADDW(vaw)		vBIT(vaw, 0, 16)
#define MDIO_MMD_DEV_ADDW(vaw)		vBIT(vaw, 19, 5)
#define MDIO_MMS_PWT_ADDW(vaw)		vBIT(vaw, 27, 5)
#define MDIO_CTWW_STAWT_TWANS(vaw)	vBIT(vaw, 56, 4)
#define MDIO_OP(vaw)			vBIT(vaw, 60, 2)
#define MDIO_OP_ADDW_TWANS		0x0
#define MDIO_OP_WWITE_TWANS		0x1
#define MDIO_OP_WEAD_POST_INC_TWANS	0x2
#define MDIO_OP_WEAD_TWANS		0x3
#define MDIO_MDIO_DATA(vaw)		vBIT(vaw, 32, 16)

	u64 dtx_contwow;

	u64 i2c_contwow;
#define	I2C_CONTWOW_DEV_ID(id)		vBIT(id,1,3)
#define	I2C_CONTWOW_ADDW(addw)		vBIT(addw,5,11)
#define	I2C_CONTWOW_BYTE_CNT(cnt)	vBIT(cnt,22,2)
#define	I2C_CONTWOW_WEAD			s2BIT(24)
#define	I2C_CONTWOW_NACK			s2BIT(25)
#define	I2C_CONTWOW_CNTW_STAWT		vBIT(0xE,28,4)
#define	I2C_CONTWOW_CNTW_END(vaw)	(vaw & vBIT(0x1,28,4))
#define	I2C_CONTWOW_GET_DATA(vaw)	(u32)(vaw & 0xFFFFFFFF)
#define	I2C_CONTWOW_SET_DATA(vaw)	vBIT(vaw,32,32)

	u64 gpio_contwow;
#define GPIO_CTWW_GPIO_0		s2BIT(8)
	u64 misc_contwow;
#define FAUWT_BEHAVIOUW			s2BIT(0)
#define EXT_WEQ_EN			s2BIT(1)
#define MISC_WINK_STABIWITY_PWD(vaw)   vBIT(vaw,29,3)

	u8 unused7_1[0x230 - 0x208];

	u64 pic_contwow2;
	u64 ini_dpeww_ctww;

	u64 wweq_spwit_mask;
#define	WWEQ_SPWIT_MASK_SET_MASK(vaw)	vBIT(vaw, 52, 12)

	u8 unused7_2[0x800 - 0x248];

/* TxDMA wegistews */
	u64 txdma_int_status;
	u64 txdma_int_mask;
#define TXDMA_PFC_INT                  s2BIT(0)
#define TXDMA_TDA_INT                  s2BIT(1)
#define TXDMA_PCC_INT                  s2BIT(2)
#define TXDMA_TTI_INT                  s2BIT(3)
#define TXDMA_WSO_INT                  s2BIT(4)
#define TXDMA_TPA_INT                  s2BIT(5)
#define TXDMA_SM_INT                   s2BIT(6)
	u64 pfc_eww_weg;
#define PFC_ECC_SG_EWW			s2BIT(7)
#define PFC_ECC_DB_EWW			s2BIT(15)
#define PFC_SM_EWW_AWAWM		s2BIT(23)
#define PFC_MISC_0_EWW			s2BIT(31)
#define PFC_MISC_1_EWW			s2BIT(32)
#define PFC_PCIX_EWW			s2BIT(39)
	u64 pfc_eww_mask;
	u64 pfc_eww_awawm;

	u64 tda_eww_weg;
#define TDA_Fn_ECC_SG_EWW		vBIT(0xff,0,8)
#define TDA_Fn_ECC_DB_EWW		vBIT(0xff,8,8)
#define TDA_SM0_EWW_AWAWM		s2BIT(22)
#define TDA_SM1_EWW_AWAWM		s2BIT(23)
#define TDA_PCIX_EWW			s2BIT(39)
	u64 tda_eww_mask;
	u64 tda_eww_awawm;

	u64 pcc_eww_weg;
#define PCC_FB_ECC_SG_EWW		vBIT(0xFF,0,8)
#define PCC_TXB_ECC_SG_EWW		vBIT(0xFF,8,8)
#define PCC_FB_ECC_DB_EWW		vBIT(0xFF,16, 8)
#define PCC_TXB_ECC_DB_EWW		vBIT(0xff,24,8)
#define PCC_SM_EWW_AWAWM		vBIT(0xff,32,8)
#define PCC_WW_EWW_AWAWM		vBIT(0xff,40,8)
#define PCC_N_SEWW			vBIT(0xff,48,8)
#define PCC_6_COF_OV_EWW		s2BIT(56)
#define PCC_7_COF_OV_EWW		s2BIT(57)
#define PCC_6_WSO_OV_EWW		s2BIT(58)
#define PCC_7_WSO_OV_EWW		s2BIT(59)
#define PCC_ENABWE_FOUW			vBIT(0x0F,0,8)
	u64 pcc_eww_mask;
	u64 pcc_eww_awawm;

	u64 tti_eww_weg;
#define TTI_ECC_SG_EWW			s2BIT(7)
#define TTI_ECC_DB_EWW			s2BIT(15)
#define TTI_SM_EWW_AWAWM		s2BIT(23)
	u64 tti_eww_mask;
	u64 tti_eww_awawm;

	u64 wso_eww_weg;
#define WSO6_SEND_OFWOW			s2BIT(12)
#define WSO7_SEND_OFWOW			s2BIT(13)
#define WSO6_ABOWT			s2BIT(14)
#define WSO7_ABOWT			s2BIT(15)
#define WSO6_SM_EWW_AWAWM		s2BIT(22)
#define WSO7_SM_EWW_AWAWM		s2BIT(23)
	u64 wso_eww_mask;
	u64 wso_eww_awawm;

	u64 tpa_eww_weg;
#define TPA_TX_FWM_DWOP			s2BIT(7)
#define TPA_SM_EWW_AWAWM		s2BIT(23)

	u64 tpa_eww_mask;
	u64 tpa_eww_awawm;

	u64 sm_eww_weg;
#define SM_SM_EWW_AWAWM			s2BIT(15)
	u64 sm_eww_mask;
	u64 sm_eww_awawm;

	u8 unused8[0x100 - 0xB8];

/* TxDMA awbitew */
	u64 tx_dma_wwap_stat;

/* Tx FIFO contwowwew */
#define X_MAX_FIFOS                        8
#define X_FIFO_MAX_WEN                     0x1FFF	/*8191 */
	u64 tx_fifo_pawtition_0;
#define TX_FIFO_PAWTITION_EN               s2BIT(0)
#define TX_FIFO_PAWTITION_0_PWI(vaw)       vBIT(vaw,5,3)
#define TX_FIFO_PAWTITION_0_WEN(vaw)       vBIT(vaw,19,13)
#define TX_FIFO_PAWTITION_1_PWI(vaw)       vBIT(vaw,37,3)
#define TX_FIFO_PAWTITION_1_WEN(vaw)       vBIT(vaw,51,13  )

	u64 tx_fifo_pawtition_1;
#define TX_FIFO_PAWTITION_2_PWI(vaw)       vBIT(vaw,5,3)
#define TX_FIFO_PAWTITION_2_WEN(vaw)       vBIT(vaw,19,13)
#define TX_FIFO_PAWTITION_3_PWI(vaw)       vBIT(vaw,37,3)
#define TX_FIFO_PAWTITION_3_WEN(vaw)       vBIT(vaw,51,13)

	u64 tx_fifo_pawtition_2;
#define TX_FIFO_PAWTITION_4_PWI(vaw)       vBIT(vaw,5,3)
#define TX_FIFO_PAWTITION_4_WEN(vaw)       vBIT(vaw,19,13)
#define TX_FIFO_PAWTITION_5_PWI(vaw)       vBIT(vaw,37,3)
#define TX_FIFO_PAWTITION_5_WEN(vaw)       vBIT(vaw,51,13)

	u64 tx_fifo_pawtition_3;
#define TX_FIFO_PAWTITION_6_PWI(vaw)       vBIT(vaw,5,3)
#define TX_FIFO_PAWTITION_6_WEN(vaw)       vBIT(vaw,19,13)
#define TX_FIFO_PAWTITION_7_PWI(vaw)       vBIT(vaw,37,3)
#define TX_FIFO_PAWTITION_7_WEN(vaw)       vBIT(vaw,51,13)

#define TX_FIFO_PAWTITION_PWI_0                 0	/* highest */
#define TX_FIFO_PAWTITION_PWI_1                 1
#define TX_FIFO_PAWTITION_PWI_2                 2
#define TX_FIFO_PAWTITION_PWI_3                 3
#define TX_FIFO_PAWTITION_PWI_4                 4
#define TX_FIFO_PAWTITION_PWI_5                 5
#define TX_FIFO_PAWTITION_PWI_6                 6
#define TX_FIFO_PAWTITION_PWI_7                 7	/* wowest */

	u64 tx_w_wound_wobin_0;
	u64 tx_w_wound_wobin_1;
	u64 tx_w_wound_wobin_2;
	u64 tx_w_wound_wobin_3;
	u64 tx_w_wound_wobin_4;

	u64 tti_command_mem;
#define TTI_CMD_MEM_WE                     s2BIT(7)
#define TTI_CMD_MEM_STWOBE_NEW_CMD         s2BIT(15)
#define TTI_CMD_MEM_STWOBE_BEING_EXECUTED  s2BIT(15)
#define TTI_CMD_MEM_OFFSET(n)              vBIT(n,26,6)

	u64 tti_data1_mem;
#define TTI_DATA1_MEM_TX_TIMEW_VAW(n)      vBIT(n,6,26)
#define TTI_DATA1_MEM_TX_TIMEW_AC_CI(n)    vBIT(n,38,2)
#define TTI_DATA1_MEM_TX_TIMEW_AC_EN       s2BIT(38)
#define TTI_DATA1_MEM_TX_TIMEW_CI_EN       s2BIT(39)
#define TTI_DATA1_MEM_TX_UWNG_A(n)         vBIT(n,41,7)
#define TTI_DATA1_MEM_TX_UWNG_B(n)         vBIT(n,49,7)
#define TTI_DATA1_MEM_TX_UWNG_C(n)         vBIT(n,57,7)

	u64 tti_data2_mem;
#define TTI_DATA2_MEM_TX_UFC_A(n)          vBIT(n,0,16)
#define TTI_DATA2_MEM_TX_UFC_B(n)          vBIT(n,16,16)
#define TTI_DATA2_MEM_TX_UFC_C(n)          vBIT(n,32,16)
#define TTI_DATA2_MEM_TX_UFC_D(n)          vBIT(n,48,16)

/* Tx Pwotocow assist */
	u64 tx_pa_cfg;
#define TX_PA_CFG_IGNOWE_FWM_EWW           s2BIT(1)
#define TX_PA_CFG_IGNOWE_SNAP_OUI          s2BIT(2)
#define TX_PA_CFG_IGNOWE_WWC_CTWW          s2BIT(3)
#define	TX_PA_CFG_IGNOWE_W2_EWW			   s2BIT(6)
#define WX_PA_CFG_STWIP_VWAN_TAG		s2BIT(15)

/* Wecent add, used onwy debug puwposes. */
	u64 pcc_enabwe;

	u8 unused9[0x700 - 0x178];

	u64 txdma_debug_ctww;

	u8 unused10[0x1800 - 0x1708];

/* WxDMA Wegistews */
	u64 wxdma_int_status;
	u64 wxdma_int_mask;
#define WXDMA_INT_WC_INT_M             s2BIT(0)
#define WXDMA_INT_WPA_INT_M            s2BIT(1)
#define WXDMA_INT_WDA_INT_M            s2BIT(2)
#define WXDMA_INT_WTI_INT_M            s2BIT(3)

	u64 wda_eww_weg;
#define WDA_WXDn_ECC_SG_EWW		vBIT(0xFF,0,8)
#define WDA_WXDn_ECC_DB_EWW		vBIT(0xFF,8,8)
#define WDA_FWM_ECC_SG_EWW		s2BIT(23)
#define WDA_FWM_ECC_DB_N_AEWW		s2BIT(31)
#define WDA_SM1_EWW_AWAWM		s2BIT(38)
#define WDA_SM0_EWW_AWAWM		s2BIT(39)
#define WDA_MISC_EWW			s2BIT(47)
#define WDA_PCIX_EWW			s2BIT(55)
#define WDA_WXD_ECC_DB_SEWW		s2BIT(63)
	u64 wda_eww_mask;
	u64 wda_eww_awawm;

	u64 wc_eww_weg;
#define WC_PWCn_ECC_SG_EWW		vBIT(0xFF,0,8)
#define WC_PWCn_ECC_DB_EWW		vBIT(0xFF,8,8)
#define WC_FTC_ECC_SG_EWW		s2BIT(23)
#define WC_FTC_ECC_DB_EWW		s2BIT(31)
#define WC_PWCn_SM_EWW_AWAWM		vBIT(0xFF,32,8)
#define WC_FTC_SM_EWW_AWAWM		s2BIT(47)
#define WC_WDA_FAIW_WW_Wn		vBIT(0xFF,48,8)
	u64 wc_eww_mask;
	u64 wc_eww_awawm;

	u64 pwc_pcix_eww_weg;
#define PWC_PCI_AB_WD_Wn		vBIT(0xFF,0,8)
#define PWC_PCI_DP_WD_Wn		vBIT(0xFF,8,8)
#define PWC_PCI_AB_WW_Wn		vBIT(0xFF,16,8)
#define PWC_PCI_DP_WW_Wn		vBIT(0xFF,24,8)
#define PWC_PCI_AB_F_WW_Wn		vBIT(0xFF,32,8)
#define PWC_PCI_DP_F_WW_Wn		vBIT(0xFF,40,8)
	u64 pwc_pcix_eww_mask;
	u64 pwc_pcix_eww_awawm;

	u64 wpa_eww_weg;
#define WPA_ECC_SG_EWW			s2BIT(7)
#define WPA_ECC_DB_EWW			s2BIT(15)
#define WPA_FWUSH_WEQUEST		s2BIT(22)
#define WPA_SM_EWW_AWAWM		s2BIT(23)
#define WPA_CWEDIT_EWW			s2BIT(31)
	u64 wpa_eww_mask;
	u64 wpa_eww_awawm;

	u64 wti_eww_weg;
#define WTI_ECC_SG_EWW			s2BIT(7)
#define WTI_ECC_DB_EWW			s2BIT(15)
#define WTI_SM_EWW_AWAWM		s2BIT(23)
	u64 wti_eww_mask;
	u64 wti_eww_awawm;

	u8 unused11[0x100 - 0x88];

/* DMA awbitew */
	u64 wx_queue_pwiowity;
#define WX_QUEUE_0_PWIOWITY(vaw)       vBIT(vaw,5,3)
#define WX_QUEUE_1_PWIOWITY(vaw)       vBIT(vaw,13,3)
#define WX_QUEUE_2_PWIOWITY(vaw)       vBIT(vaw,21,3)
#define WX_QUEUE_3_PWIOWITY(vaw)       vBIT(vaw,29,3)
#define WX_QUEUE_4_PWIOWITY(vaw)       vBIT(vaw,37,3)
#define WX_QUEUE_5_PWIOWITY(vaw)       vBIT(vaw,45,3)
#define WX_QUEUE_6_PWIOWITY(vaw)       vBIT(vaw,53,3)
#define WX_QUEUE_7_PWIOWITY(vaw)       vBIT(vaw,61,3)

#define WX_QUEUE_PWI_0                 0	/* highest */
#define WX_QUEUE_PWI_1                 1
#define WX_QUEUE_PWI_2                 2
#define WX_QUEUE_PWI_3                 3
#define WX_QUEUE_PWI_4                 4
#define WX_QUEUE_PWI_5                 5
#define WX_QUEUE_PWI_6                 6
#define WX_QUEUE_PWI_7                 7	/* wowest */

	u64 wx_w_wound_wobin_0;
	u64 wx_w_wound_wobin_1;
	u64 wx_w_wound_wobin_2;
	u64 wx_w_wound_wobin_3;
	u64 wx_w_wound_wobin_4;

	/* Pew-wing contwowwew wegs */
#define WX_MAX_WINGS                8
#if 0
#define WX_MAX_WINGS_SZ             0xFFFF	/* 65536 */
#define WX_MIN_WINGS_SZ             0x3F	/* 63 */
#endif
	u64 pwc_wxd0_n[WX_MAX_WINGS];
	u64 pwc_ctww_n[WX_MAX_WINGS];
#define PWC_CTWW_WC_ENABWED                    s2BIT(7)
#define PWC_CTWW_WING_MODE                     (s2BIT(14)|s2BIT(15))
#define PWC_CTWW_WING_MODE_1                   vBIT(0,14,2)
#define PWC_CTWW_WING_MODE_3                   vBIT(1,14,2)
#define PWC_CTWW_WING_MODE_5                   vBIT(2,14,2)
#define PWC_CTWW_WING_MODE_x                   vBIT(3,14,2)
#define PWC_CTWW_NO_SNOOP                      (s2BIT(22)|s2BIT(23))
#define PWC_CTWW_NO_SNOOP_DESC                 s2BIT(22)
#define PWC_CTWW_NO_SNOOP_BUFF                 s2BIT(23)
#define PWC_CTWW_BIMODAW_INTEWWUPT             s2BIT(37)
#define PWC_CTWW_GWOUP_WEADS                   s2BIT(38)
#define PWC_CTWW_WXD_BACKOFF_INTEWVAW(vaw)     vBIT(vaw,40,24)

	u64 pwc_awawm_action;
#define PWC_AWAWM_ACTION_WW_W0_STOP            s2BIT(3)
#define PWC_AWAWM_ACTION_WW_W0_STOP            s2BIT(7)
#define PWC_AWAWM_ACTION_WW_W1_STOP            s2BIT(11)
#define PWC_AWAWM_ACTION_WW_W1_STOP            s2BIT(15)
#define PWC_AWAWM_ACTION_WW_W2_STOP            s2BIT(19)
#define PWC_AWAWM_ACTION_WW_W2_STOP            s2BIT(23)
#define PWC_AWAWM_ACTION_WW_W3_STOP            s2BIT(27)
#define PWC_AWAWM_ACTION_WW_W3_STOP            s2BIT(31)
#define PWC_AWAWM_ACTION_WW_W4_STOP            s2BIT(35)
#define PWC_AWAWM_ACTION_WW_W4_STOP            s2BIT(39)
#define PWC_AWAWM_ACTION_WW_W5_STOP            s2BIT(43)
#define PWC_AWAWM_ACTION_WW_W5_STOP            s2BIT(47)
#define PWC_AWAWM_ACTION_WW_W6_STOP            s2BIT(51)
#define PWC_AWAWM_ACTION_WW_W6_STOP            s2BIT(55)
#define PWC_AWAWM_ACTION_WW_W7_STOP            s2BIT(59)
#define PWC_AWAWM_ACTION_WW_W7_STOP            s2BIT(63)

/* Weceive twaffic intewwupts */
	u64 wti_command_mem;
#define WTI_CMD_MEM_WE                          s2BIT(7)
#define WTI_CMD_MEM_STWOBE                      s2BIT(15)
#define WTI_CMD_MEM_STWOBE_NEW_CMD              s2BIT(15)
#define WTI_CMD_MEM_STWOBE_CMD_BEING_EXECUTED   s2BIT(15)
#define WTI_CMD_MEM_OFFSET(n)                   vBIT(n,29,3)

	u64 wti_data1_mem;
#define WTI_DATA1_MEM_WX_TIMEW_VAW(n)      vBIT(n,3,29)
#define WTI_DATA1_MEM_WX_TIMEW_AC_EN       s2BIT(38)
#define WTI_DATA1_MEM_WX_TIMEW_CI_EN       s2BIT(39)
#define WTI_DATA1_MEM_WX_UWNG_A(n)         vBIT(n,41,7)
#define WTI_DATA1_MEM_WX_UWNG_B(n)         vBIT(n,49,7)
#define WTI_DATA1_MEM_WX_UWNG_C(n)         vBIT(n,57,7)

	u64 wti_data2_mem;
#define WTI_DATA2_MEM_WX_UFC_A(n)          vBIT(n,0,16)
#define WTI_DATA2_MEM_WX_UFC_B(n)          vBIT(n,16,16)
#define WTI_DATA2_MEM_WX_UFC_C(n)          vBIT(n,32,16)
#define WTI_DATA2_MEM_WX_UFC_D(n)          vBIT(n,48,16)

	u64 wx_pa_cfg;
#define WX_PA_CFG_IGNOWE_FWM_EWW           s2BIT(1)
#define WX_PA_CFG_IGNOWE_SNAP_OUI          s2BIT(2)
#define WX_PA_CFG_IGNOWE_WWC_CTWW          s2BIT(3)
#define WX_PA_CFG_IGNOWE_W2_EWW            s2BIT(6)

	u64 unused_11_1;

	u64 wing_bump_countew1;
	u64 wing_bump_countew2;

	u8 unused12[0x700 - 0x1F0];

	u64 wxdma_debug_ctww;

	u8 unused13[0x2000 - 0x1f08];

/* Media Access Contwowwew Wegistew */
	u64 mac_int_status;
	u64 mac_int_mask;
#define MAC_INT_STATUS_TMAC_INT            s2BIT(0)
#define MAC_INT_STATUS_WMAC_INT            s2BIT(1)

	u64 mac_tmac_eww_weg;
#define TMAC_ECC_SG_EWW				s2BIT(7)
#define TMAC_ECC_DB_EWW				s2BIT(15)
#define TMAC_TX_BUF_OVWN			s2BIT(23)
#define TMAC_TX_CWI_EWW				s2BIT(31)
#define TMAC_TX_SM_EWW				s2BIT(39)
#define TMAC_DESC_ECC_SG_EWW			s2BIT(47)
#define TMAC_DESC_ECC_DB_EWW			s2BIT(55)

	u64 mac_tmac_eww_mask;
	u64 mac_tmac_eww_awawm;

	u64 mac_wmac_eww_weg;
#define WMAC_WX_BUFF_OVWN			s2BIT(0)
#define WMAC_FWM_WCVD_INT			s2BIT(1)
#define WMAC_UNUSED_INT				s2BIT(2)
#define WMAC_WTS_PNUM_ECC_SG_EWW		s2BIT(5)
#define WMAC_WTS_DS_ECC_SG_EWW			s2BIT(6)
#define WMAC_WD_BUF_ECC_SG_EWW			s2BIT(7)
#define WMAC_WTH_MAP_ECC_SG_EWW			s2BIT(8)
#define WMAC_WTH_SPDM_ECC_SG_EWW		s2BIT(9)
#define WMAC_WTS_VID_ECC_SG_EWW			s2BIT(10)
#define WMAC_DA_SHADOW_ECC_SG_EWW		s2BIT(11)
#define WMAC_WTS_PNUM_ECC_DB_EWW		s2BIT(13)
#define WMAC_WTS_DS_ECC_DB_EWW			s2BIT(14)
#define WMAC_WD_BUF_ECC_DB_EWW			s2BIT(15)
#define WMAC_WTH_MAP_ECC_DB_EWW			s2BIT(16)
#define WMAC_WTH_SPDM_ECC_DB_EWW		s2BIT(17)
#define WMAC_WTS_VID_ECC_DB_EWW			s2BIT(18)
#define WMAC_DA_SHADOW_ECC_DB_EWW		s2BIT(19)
#define WMAC_WINK_STATE_CHANGE_INT		s2BIT(31)
#define WMAC_WX_SM_EWW				s2BIT(39)
#define WMAC_SINGWE_ECC_EWW			(s2BIT(5) | s2BIT(6) | s2BIT(7) |\
						s2BIT(8)  | s2BIT(9) | s2BIT(10)|\
						s2BIT(11))
#define WMAC_DOUBWE_ECC_EWW			(s2BIT(13) | s2BIT(14) | s2BIT(15) |\
						s2BIT(16)  | s2BIT(17) | s2BIT(18)|\
						s2BIT(19))
	u64 mac_wmac_eww_mask;
	u64 mac_wmac_eww_awawm;

	u8 unused14[0x100 - 0x40];

	u64 mac_cfg;
#define MAC_CFG_TMAC_ENABWE             s2BIT(0)
#define MAC_CFG_WMAC_ENABWE             s2BIT(1)
#define MAC_CFG_WAN_NOT_WAN             s2BIT(2)
#define MAC_CFG_TMAC_WOOPBACK           s2BIT(3)
#define MAC_CFG_TMAC_APPEND_PAD         s2BIT(4)
#define MAC_CFG_WMAC_STWIP_FCS          s2BIT(5)
#define MAC_CFG_WMAC_STWIP_PAD          s2BIT(6)
#define MAC_CFG_WMAC_PWOM_ENABWE        s2BIT(7)
#define MAC_WMAC_DISCAWD_PFWM           s2BIT(8)
#define MAC_WMAC_BCAST_ENABWE           s2BIT(9)
#define MAC_WMAC_AWW_ADDW_ENABWE        s2BIT(10)
#define MAC_WMAC_INVWD_IPG_THW(vaw)     vBIT(vaw,16,8)

	u64 tmac_avg_ipg;
#define TMAC_AVG_IPG(vaw)           vBIT(vaw,0,8)

	u64 wmac_max_pywd_wen;
#define WMAC_MAX_PYWD_WEN(vaw)      vBIT(vaw,2,14)
#define WMAC_MAX_PYWD_WEN_DEF       vBIT(1500,2,14)
#define WMAC_MAX_PYWD_WEN_JUMBO_DEF vBIT(9600,2,14)

	u64 wmac_eww_cfg;
#define WMAC_EWW_FCS                    s2BIT(0)
#define WMAC_EWW_FCS_ACCEPT             s2BIT(1)
#define WMAC_EWW_TOO_WONG               s2BIT(1)
#define WMAC_EWW_TOO_WONG_ACCEPT        s2BIT(1)
#define WMAC_EWW_WUNT                   s2BIT(2)
#define WMAC_EWW_WUNT_ACCEPT            s2BIT(2)
#define WMAC_EWW_WEN_MISMATCH           s2BIT(3)
#define WMAC_EWW_WEN_MISMATCH_ACCEPT    s2BIT(3)

	u64 wmac_cfg_key;
#define WMAC_CFG_KEY(vaw)               vBIT(vaw,0,16)

#define S2IO_MAC_ADDW_STAWT_OFFSET	0

#define S2IO_XENA_MAX_MC_ADDWESSES	64	/* muwticast addwesses */
#define S2IO_HEWC_MAX_MC_ADDWESSES	256

#define S2IO_XENA_MAX_MAC_ADDWESSES	16
#define S2IO_HEWC_MAX_MAC_ADDWESSES	64

#define S2IO_XENA_MC_ADDW_STAWT_OFFSET	16
#define S2IO_HEWC_MC_ADDW_STAWT_OFFSET	64

	u64 wmac_addw_cmd_mem;
#define WMAC_ADDW_CMD_MEM_WE                    s2BIT(7)
#define WMAC_ADDW_CMD_MEM_WD                    0
#define WMAC_ADDW_CMD_MEM_STWOBE_NEW_CMD        s2BIT(15)
#define WMAC_ADDW_CMD_MEM_STWOBE_CMD_EXECUTING  s2BIT(15)
#define WMAC_ADDW_CMD_MEM_OFFSET(n)             vBIT(n,26,6)

	u64 wmac_addw_data0_mem;
#define WMAC_ADDW_DATA0_MEM_ADDW(n)    vBIT(n,0,48)
#define WMAC_ADDW_DATA0_MEM_USEW       s2BIT(48)

	u64 wmac_addw_data1_mem;
#define WMAC_ADDW_DATA1_MEM_MASK(n)    vBIT(n,0,48)

	u8 unused15[0x8];

/*
        u64 wmac_addw_cfg;
#define WMAC_ADDW_UCASTn_EN(n)     mBIT(0)_n(n)
#define WMAC_ADDW_MCASTn_EN(n)     mBIT(0)_n(n)
#define WMAC_ADDW_BCAST_EN         vBIT(0)_48
#define WMAC_ADDW_AWW_ADDW_EN      vBIT(0)_49
*/
	u64 tmac_ipg_cfg;

	u64 wmac_pause_cfg;
#define WMAC_PAUSE_GEN             s2BIT(0)
#define WMAC_PAUSE_GEN_ENABWE      s2BIT(0)
#define WMAC_PAUSE_WX              s2BIT(1)
#define WMAC_PAUSE_WX_ENABWE       s2BIT(1)
#define WMAC_PAUSE_HG_PTIME_DEF    vBIT(0xFFFF,16,16)
#define WMAC_PAUSE_HG_PTIME(vaw)    vBIT(vaw,16,16)

	u64 wmac_wed_cfg;

	u64 wmac_wed_wate_q0q3;
	u64 wmac_wed_wate_q4q7;

	u64 mac_wink_utiw;
#define MAC_TX_WINK_UTIW           vBIT(0xFE,1,7)
#define MAC_TX_WINK_UTIW_DISABWE   vBIT(0xF, 8,4)
#define MAC_TX_WINK_UTIW_VAW( n )  vBIT(n,8,4)
#define MAC_WX_WINK_UTIW           vBIT(0xFE,33,7)
#define MAC_WX_WINK_UTIW_DISABWE   vBIT(0xF,40,4)
#define MAC_WX_WINK_UTIW_VAW( n )  vBIT(n,40,4)

#define MAC_WINK_UTIW_DISABWE      MAC_TX_WINK_UTIW_DISABWE | \
                                   MAC_WX_WINK_UTIW_DISABWE

	u64 wmac_invawid_ipg;

/* wx twaffic steewing */
#define	MAC_WTS_FWM_WEN_SET(wen)	vBIT(wen,2,14)
	u64 wts_fwm_wen_n[8];

	u64 wts_qos_steewing;

#define MAX_DIX_MAP                         4
	u64 wts_dix_map_n[MAX_DIX_MAP];
#define WTS_DIX_MAP_ETYPE(vaw)             vBIT(vaw,0,16)
#define WTS_DIX_MAP_SCW(vaw)               s2BIT(vaw,21)

	u64 wts_q_awtewnates;
	u64 wts_defauwt_q;

	u64 wts_ctww;
#define WTS_CTWW_IGNOWE_SNAP_OUI           s2BIT(2)
#define WTS_CTWW_IGNOWE_WWC_CTWW           s2BIT(3)

	u64 wts_pn_cam_ctww;
#define WTS_PN_CAM_CTWW_WE                 s2BIT(7)
#define WTS_PN_CAM_CTWW_STWOBE_NEW_CMD     s2BIT(15)
#define WTS_PN_CAM_CTWW_STWOBE_BEING_EXECUTED   s2BIT(15)
#define WTS_PN_CAM_CTWW_OFFSET(n)          vBIT(n,24,8)
	u64 wts_pn_cam_data;
#define WTS_PN_CAM_DATA_TCP_SEWECT         s2BIT(7)
#define WTS_PN_CAM_DATA_POWT(vaw)          vBIT(vaw,8,16)
#define WTS_PN_CAM_DATA_SCW(vaw)           vBIT(vaw,24,8)

	u64 wts_ds_mem_ctww;
#define WTS_DS_MEM_CTWW_WE                 s2BIT(7)
#define WTS_DS_MEM_CTWW_STWOBE_NEW_CMD     s2BIT(15)
#define WTS_DS_MEM_CTWW_STWOBE_CMD_BEING_EXECUTED   s2BIT(15)
#define WTS_DS_MEM_CTWW_OFFSET(n)          vBIT(n,26,6)
	u64 wts_ds_mem_data;
#define WTS_DS_MEM_DATA(n)                 vBIT(n,0,8)

	u8 unused16[0x700 - 0x220];

	u64 mac_debug_ctww;
#define MAC_DBG_ACTIVITY_VAWUE		   0x411040400000000UWW

	u8 unused17[0x2800 - 0x2708];

/* memowy contwowwew wegistews */
	u64 mc_int_status;
#define MC_INT_STATUS_MC_INT               s2BIT(0)
	u64 mc_int_mask;
#define MC_INT_MASK_MC_INT                 s2BIT(0)

	u64 mc_eww_weg;
#define MC_EWW_WEG_ECC_DB_EWW_W            s2BIT(14)
#define MC_EWW_WEG_ECC_DB_EWW_U            s2BIT(15)
#define MC_EWW_WEG_MIWI_ECC_DB_EWW_0       s2BIT(18)
#define MC_EWW_WEG_MIWI_ECC_DB_EWW_1       s2BIT(20)
#define MC_EWW_WEG_MIWI_CWI_EWW_0          s2BIT(22)
#define MC_EWW_WEG_MIWI_CWI_EWW_1          s2BIT(23)
#define MC_EWW_WEG_SM_EWW                  s2BIT(31)
#define MC_EWW_WEG_ECC_AWW_SNG		   (s2BIT(2) | s2BIT(3) | s2BIT(4) | s2BIT(5) |\
					s2BIT(17) | s2BIT(19))
#define MC_EWW_WEG_ECC_AWW_DBW		   (s2BIT(10) | s2BIT(11) | s2BIT(12) |\
					s2BIT(13) | s2BIT(18) | s2BIT(20))
#define PWW_WOCK_N			s2BIT(39)
	u64 mc_eww_mask;
	u64 mc_eww_awawm;

	u8 unused18[0x100 - 0x28];

/* MC configuwation */
	u64 wx_queue_cfg;
#define WX_QUEUE_CFG_Q0_SZ(n)              vBIT(n,0,8)
#define WX_QUEUE_CFG_Q1_SZ(n)              vBIT(n,8,8)
#define WX_QUEUE_CFG_Q2_SZ(n)              vBIT(n,16,8)
#define WX_QUEUE_CFG_Q3_SZ(n)              vBIT(n,24,8)
#define WX_QUEUE_CFG_Q4_SZ(n)              vBIT(n,32,8)
#define WX_QUEUE_CFG_Q5_SZ(n)              vBIT(n,40,8)
#define WX_QUEUE_CFG_Q6_SZ(n)              vBIT(n,48,8)
#define WX_QUEUE_CFG_Q7_SZ(n)              vBIT(n,56,8)

	u64 mc_wwdwam_mws;
#define	MC_WWDWAM_QUEUE_SIZE_ENABWE			s2BIT(39)
#define	MC_WWDWAM_MWS_ENABWE				s2BIT(47)

	u64 mc_wwdwam_intewweave;

	u64 mc_pause_thwesh_q0q3;
	u64 mc_pause_thwesh_q4q7;

	u64 mc_wed_thwesh_q[8];

	u8 unused19[0x200 - 0x168];
	u64 mc_wwdwam_wef_pew;
	u8 unused20[0x220 - 0x208];
	u64 mc_wwdwam_test_ctww;
#define MC_WWDWAM_TEST_MODE		s2BIT(47)
#define MC_WWDWAM_TEST_WWITE	s2BIT(7)
#define MC_WWDWAM_TEST_GO		s2BIT(15)
#define MC_WWDWAM_TEST_DONE		s2BIT(23)
#define MC_WWDWAM_TEST_PASS		s2BIT(31)

	u8 unused21[0x240 - 0x228];
	u64 mc_wwdwam_test_add;
	u8 unused22[0x260 - 0x248];
	u64 mc_wwdwam_test_d0;
	u8 unused23[0x280 - 0x268];
	u64 mc_wwdwam_test_d1;
	u8 unused24[0x300 - 0x288];
	u64 mc_wwdwam_test_d2;

	u8 unused24_1[0x360 - 0x308];
	u64 mc_wwdwam_ctww;
#define	MC_WWDWAM_ENABWE_ODT		s2BIT(7)

	u8 unused24_2[0x640 - 0x368];
	u64 mc_wwdwam_wef_pew_hewc;
#define	MC_WWDWAM_SET_WEF_PEWIOD(vaw)	vBIT(vaw, 0, 16)

	u8 unused24_3[0x660 - 0x648];
	u64 mc_wwdwam_mws_hewc;

	u8 unused25[0x700 - 0x668];
	u64 mc_debug_ctww;

	u8 unused26[0x3000 - 0x2f08];

/* XGXG */
	/* XGXS contwow wegistews */

	u64 xgxs_int_status;
#define XGXS_INT_STATUS_TXGXS              s2BIT(0)
#define XGXS_INT_STATUS_WXGXS              s2BIT(1)
	u64 xgxs_int_mask;
#define XGXS_INT_MASK_TXGXS                s2BIT(0)
#define XGXS_INT_MASK_WXGXS                s2BIT(1)

	u64 xgxs_txgxs_eww_weg;
#define TXGXS_ECC_SG_EWW		s2BIT(7)
#define TXGXS_ECC_DB_EWW		s2BIT(15)
#define TXGXS_ESTOWE_UFWOW		s2BIT(31)
#define TXGXS_TX_SM_EWW			s2BIT(39)

	u64 xgxs_txgxs_eww_mask;
	u64 xgxs_txgxs_eww_awawm;

	u64 xgxs_wxgxs_eww_weg;
#define WXGXS_ESTOWE_OFWOW		s2BIT(7)
#define WXGXS_WX_SM_EWW			s2BIT(39)
	u64 xgxs_wxgxs_eww_mask;
	u64 xgxs_wxgxs_eww_awawm;

	u8 unused27[0x100 - 0x40];

	u64 xgxs_cfg;
	u64 xgxs_status;

	u64 xgxs_cfg_key;
	u64 xgxs_efifo_cfg;	/* CHANGED */
	u64 wxgxs_bew_0;	/* CHANGED */
	u64 wxgxs_bew_1;	/* CHANGED */

	u64 spi_contwow;
#define SPI_CONTWOW_KEY(key)		vBIT(key,0,4)
#define SPI_CONTWOW_BYTECNT(cnt)	vBIT(cnt,29,3)
#define SPI_CONTWOW_CMD(cmd)		vBIT(cmd,32,8)
#define SPI_CONTWOW_ADDW(addw)		vBIT(addw,40,24)
#define SPI_CONTWOW_SEW1		s2BIT(4)
#define SPI_CONTWOW_WEQ			s2BIT(7)
#define SPI_CONTWOW_NACK		s2BIT(5)
#define SPI_CONTWOW_DONE		s2BIT(6)
	u64 spi_data;
#define SPI_DATA_WWITE(data,wen)	vBIT(data,0,wen)
};

#define XENA_WEG_SPACE	sizeof(stwuct XENA_dev_config)
#define	XENA_EEPWOM_SPACE (0x01 << 11)

#endif				/* _WEGS_H */
