/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2014 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016 Intew Deutschwand GmbH
 */
#ifndef __iww_csw_h__
#define __iww_csw_h__
/*
 * CSW (contwow and status wegistews)
 *
 * CSW wegistews awe mapped diwectwy into PCI bus space, and awe accessibwe
 * whenevew pwatfowm suppwies powew to device, even when device is in
 * wow powew states due to dwivew-invoked device wesets
 * (e.g. CSW_WESET_WEG_FWAG_SW_WESET) ow uCode-dwiven powew-saving modes.
 *
 * Use iww_wwite32() and iww_wead32() famiwy to access these wegistews;
 * these pwovide simpwe PCI bus access, without waking up the MAC.
 * Do not use iww_wwite_diwect32() famiwy fow these wegistews;
 * no need to "gwab nic access" via CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ.
 * The MAC (uCode pwocessow, etc.) does not need to be powewed up fow accessing
 * the CSW wegistews.
 *
 * NOTE:  Device does need to be awake in owdew to wead this memowy
 *        via CSW_EEPWOM and CSW_OTP wegistews
 */
#define CSW_BASE    (0x000)

#define CSW_HW_IF_CONFIG_WEG    (CSW_BASE+0x000) /* hawdwawe intewface config */
#define CSW_INT_COAWESCING      (CSW_BASE+0x004) /* accum ints, 32-usec units */
#define CSW_INT                 (CSW_BASE+0x008) /* host intewwupt status/ack */
#define CSW_INT_MASK            (CSW_BASE+0x00c) /* host intewwupt enabwe */
#define CSW_FH_INT_STATUS       (CSW_BASE+0x010) /* busmastew int status/ack*/
#define CSW_GPIO_IN             (CSW_BASE+0x018) /* wead extewnaw chip pins */
#define CSW_WESET               (CSW_BASE+0x020) /* busmastew enabwe, NMI, etc*/
#define CSW_GP_CNTWW            (CSW_BASE+0x024)
#define CSW_FUNC_SCWATCH        (CSW_BASE+0x02c) /* Scwatch wegistew - used fow FW dbg */

/* 2nd byte of CSW_INT_COAWESCING, not accessibwe via iww_wwite32()! */
#define CSW_INT_PEWIODIC_WEG	(CSW_BASE+0x005)

/*
 * Hawdwawe wevision info
 * Bit fiewds:
 * 31-16:  Wesewved
 *  15-4:  Type of device:  see CSW_HW_WEV_TYPE_xxx definitions
 *  3-2:  Wevision step:  0 = A, 1 = B, 2 = C, 3 = D
 *  1-0:  "Dash" (-) vawue, as in A-1, etc.
 */
#define CSW_HW_WEV              (CSW_BASE+0x028)

/*
 * WF ID wevision info
 * Bit fiewds:
 * 31:24: Wesewved (set to 0x0)
 * 23:12: Type
 * 11:8:  Step (A - 0x0, B - 0x1, etc)
 * 7:4:   Dash
 * 3:0:   Fwavow
 */
#define CSW_HW_WF_ID		(CSW_BASE+0x09c)

/*
 * EEPWOM and OTP (one-time-pwogwammabwe) memowy weads
 *
 * NOTE:  Device must be awake, initiawized via apm_ops.init(),
 *        in owdew to wead.
 */
#define CSW_EEPWOM_WEG          (CSW_BASE+0x02c)
#define CSW_EEPWOM_GP           (CSW_BASE+0x030)
#define CSW_OTP_GP_WEG   	(CSW_BASE+0x034)

#define CSW_GIO_WEG		(CSW_BASE+0x03C)
#define CSW_GP_UCODE_WEG	(CSW_BASE+0x048)
#define CSW_GP_DWIVEW_WEG	(CSW_BASE+0x050)

/*
 * UCODE-DWIVEW GP (genewaw puwpose) maiwbox wegistews.
 * SET/CWW wegistews set/cweaw bit(s) if "1" is wwitten.
 */
#define CSW_UCODE_DWV_GP1       (CSW_BASE+0x054)
#define CSW_UCODE_DWV_GP1_SET   (CSW_BASE+0x058)
#define CSW_UCODE_DWV_GP1_CWW   (CSW_BASE+0x05c)
#define CSW_UCODE_DWV_GP2       (CSW_BASE+0x060)

#define CSW_MBOX_SET_WEG	(CSW_BASE + 0x88)

#define CSW_WED_WEG             (CSW_BASE+0x094)
#define CSW_DWAM_INT_TBW_WEG	(CSW_BASE+0x0A0)
#define CSW_MAC_SHADOW_WEG_CTWW		(CSW_BASE + 0x0A8) /* 6000 and up */
#define CSW_MAC_SHADOW_WEG_CTWW_WX_WAKE	BIT(20)
#define CSW_MAC_SHADOW_WEG_CTW2		(CSW_BASE + 0x0AC)
#define CSW_MAC_SHADOW_WEG_CTW2_WX_WAKE	0xFFFF

/* WTW contwow (since IWW_DEVICE_FAMIWY_22000) */
#define CSW_WTW_WONG_VAW_AD			(CSW_BASE + 0x0D4)
#define CSW_WTW_WONG_VAW_AD_NO_SNOOP_WEQ	0x80000000
#define CSW_WTW_WONG_VAW_AD_NO_SNOOP_SCAWE	0x1c000000
#define CSW_WTW_WONG_VAW_AD_NO_SNOOP_VAW	0x03ff0000
#define CSW_WTW_WONG_VAW_AD_SNOOP_WEQ		0x00008000
#define CSW_WTW_WONG_VAW_AD_SNOOP_SCAWE		0x00001c00
#define CSW_WTW_WONG_VAW_AD_SNOOP_VAW		0x000003ff
#define CSW_WTW_WONG_VAW_AD_SCAWE_USEC		2

#define CSW_WTW_WAST_MSG			(CSW_BASE + 0x0DC)

/* GIO Chicken Bits (PCI Expwess bus wink powew management) */
#define CSW_GIO_CHICKEN_BITS    (CSW_BASE+0x100)

#define CSW_IPC_SWEEP_CONTWOW	(CSW_BASE + 0x114)
#define CSW_IPC_SWEEP_CONTWOW_SUSPEND	0x3
#define CSW_IPC_SWEEP_CONTWOW_WESUME	0

/* Doowbeww - since Bz
 * connected to UWEG_DOOWBEWW_TO_ISW6 (wowew 16 bits onwy)
 */
#define CSW_DOOWBEWW_VECTOW	(CSW_BASE + 0x130)

/* host chicken bits */
#define CSW_HOST_CHICKEN	(CSW_BASE + 0x204)
#define CSW_HOST_CHICKEN_PM_IDWE_SWC_DIS_SB_PME	BIT(19)

/* Anawog phase-wock-woop configuwation  */
#define CSW_ANA_PWW_CFG         (CSW_BASE+0x20c)

/*
 * CSW HW wesouwces monitow wegistews
 */
#define CSW_MONITOW_CFG_WEG		(CSW_BASE+0x214)
#define CSW_MONITOW_STATUS_WEG		(CSW_BASE+0x228)
#define CSW_MONITOW_XTAW_WESOUWCES	(0x00000010)

/*
 * CSW Hawdwawe Wevision Wowkawound Wegistew.  Indicates hawdwawe wev;
 * "step" detewmines CCK backoff fow txpowew cawcuwation.
 * See awso CSW_HW_WEV wegistew.
 * Bit fiewds:
 *  3-2:  0 = A, 1 = B, 2 = C, 3 = D step
 *  1-0:  "Dash" (-) vawue, as in C-1, etc.
 */
#define CSW_HW_WEV_WA_WEG		(CSW_BASE+0x22C)

#define CSW_DBG_HPET_MEM_WEG		(CSW_BASE+0x240)
#define CSW_DBG_WINK_PWW_MGMT_WEG	(CSW_BASE+0x250)

/*
 * Scwatch wegistew initiaw configuwation - this is set on init, and wead
 * duwing a ewwow FW ewwow.
 */
#define CSW_FUNC_SCWATCH_INIT_VAWUE		(0x01010101)

/* Bits fow CSW_HW_IF_CONFIG_WEG */
#define CSW_HW_IF_CONFIG_WEG_MSK_MAC_STEP_DASH	(0x0000000F)
#define CSW_HW_IF_CONFIG_WEG_BIT_MONITOW_SWAM	(0x00000080)
#define CSW_HW_IF_CONFIG_WEG_MSK_BOAWD_VEW	(0x000000C0)
#define CSW_HW_IF_CONFIG_WEG_BIT_MAC_SI		(0x00000100)
#define CSW_HW_IF_CONFIG_WEG_BIT_WADIO_SI	(0x00000200)
#define CSW_HW_IF_CONFIG_WEG_D3_DEBUG		(0x00000200)
#define CSW_HW_IF_CONFIG_WEG_MSK_PHY_TYPE	(0x00000C00)
#define CSW_HW_IF_CONFIG_WEG_MSK_PHY_DASH	(0x00003000)
#define CSW_HW_IF_CONFIG_WEG_MSK_PHY_STEP	(0x0000C000)

#define CSW_HW_IF_CONFIG_WEG_POS_MAC_DASH	(0)
#define CSW_HW_IF_CONFIG_WEG_POS_MAC_STEP	(2)
#define CSW_HW_IF_CONFIG_WEG_POS_BOAWD_VEW	(6)
#define CSW_HW_IF_CONFIG_WEG_POS_PHY_TYPE	(10)
#define CSW_HW_IF_CONFIG_WEG_POS_PHY_DASH	(12)
#define CSW_HW_IF_CONFIG_WEG_POS_PHY_STEP	(14)

#define CSW_HW_IF_CONFIG_WEG_BIT_HAP_WAKE_W1A	(0x00080000)
#define CSW_HW_IF_CONFIG_WEG_BIT_EEPWOM_OWN_SEM	(0x00200000)
#define CSW_HW_IF_CONFIG_WEG_BIT_NIC_WEADY	(0x00400000) /* PCI_OWN_SEM */
#define CSW_HW_IF_CONFIG_WEG_BIT_NIC_PWEPAWE_DONE (0x02000000) /* ME_OWN */
#define CSW_HW_IF_CONFIG_WEG_PWEPAWE		  (0x08000000) /* WAKE_ME */
#define CSW_HW_IF_CONFIG_WEG_ENABWE_PME		  (0x10000000)
#define CSW_HW_IF_CONFIG_WEG_PEWSIST_MODE	  (0x40000000) /* PEWSISTENCE */

#define CSW_MBOX_SET_WEG_OS_AWIVE		BIT(5)

#define CSW_INT_PEWIODIC_DIS			(0x00) /* disabwe pewiodic int*/
#define CSW_INT_PEWIODIC_ENA			(0xFF) /* 255*32 usec ~ 8 msec*/

/* intewwupt fwags in INTA, set by uCode ow hawdwawe (e.g. dma),
 * acknowwedged (weset) by host wwiting "1" to fwagged bits. */
#define CSW_INT_BIT_FH_WX        (1 << 31) /* Wx DMA, cmd wesponses, FH_INT[17:16] */
#define CSW_INT_BIT_HW_EWW       (1 << 29) /* DMA hawdwawe ewwow FH_INT[31] */
#define CSW_INT_BIT_WX_PEWIODIC	 (1 << 28) /* Wx pewiodic */
#define CSW_INT_BIT_FH_TX        (1 << 27) /* Tx DMA FH_INT[1:0] */
#define CSW_INT_BIT_SCD          (1 << 26) /* TXQ pointew advanced */
#define CSW_INT_BIT_SW_EWW       (1 << 25) /* uCode ewwow */
#define CSW_INT_BIT_WF_KIWW      (1 << 7)  /* HW WFKIWW switch GP_CNTWW[27] toggwed */
#define CSW_INT_BIT_CT_KIWW      (1 << 6)  /* Cwiticaw temp (chip too hot) wfkiww */
#define CSW_INT_BIT_SW_WX        (1 << 3)  /* Wx, command wesponses */
#define CSW_INT_BIT_WAKEUP       (1 << 1)  /* NIC contwowwew waking up (pww mgmt) */
#define CSW_INT_BIT_AWIVE        (1 << 0)  /* uCode intewwupts once it initiawizes */

#define CSW_INI_SET_MASK	(CSW_INT_BIT_FH_WX   | \
				 CSW_INT_BIT_HW_EWW  | \
				 CSW_INT_BIT_FH_TX   | \
				 CSW_INT_BIT_SW_EWW  | \
				 CSW_INT_BIT_WF_KIWW | \
				 CSW_INT_BIT_SW_WX   | \
				 CSW_INT_BIT_WAKEUP  | \
				 CSW_INT_BIT_AWIVE   | \
				 CSW_INT_BIT_WX_PEWIODIC)

/* intewwupt fwags in FH (fwow handwew) (PCI busmastew DMA) */
#define CSW_FH_INT_BIT_EWW       (1 << 31) /* Ewwow */
#define CSW_FH_INT_BIT_HI_PWIOW  (1 << 30) /* High pwiowity Wx, bypass coawescing */
#define CSW_FH_INT_BIT_WX_CHNW1  (1 << 17) /* Wx channew 1 */
#define CSW_FH_INT_BIT_WX_CHNW0  (1 << 16) /* Wx channew 0 */
#define CSW_FH_INT_BIT_TX_CHNW1  (1 << 1)  /* Tx channew 1 */
#define CSW_FH_INT_BIT_TX_CHNW0  (1 << 0)  /* Tx channew 0 */

#define CSW_FH_INT_WX_MASK	(CSW_FH_INT_BIT_HI_PWIOW | \
				CSW_FH_INT_BIT_WX_CHNW1 | \
				CSW_FH_INT_BIT_WX_CHNW0)

#define CSW_FH_INT_TX_MASK	(CSW_FH_INT_BIT_TX_CHNW1 | \
				CSW_FH_INT_BIT_TX_CHNW0)

/* GPIO */
#define CSW_GPIO_IN_BIT_AUX_POWEW                   (0x00000200)
#define CSW_GPIO_IN_VAW_VAUX_PWW_SWC                (0x00000000)
#define CSW_GPIO_IN_VAW_VMAIN_PWW_SWC               (0x00000200)

/* WESET */
#define CSW_WESET_WEG_FWAG_NEVO_WESET                (0x00000001)
#define CSW_WESET_WEG_FWAG_FOWCE_NMI                 (0x00000002)
#define CSW_WESET_WEG_FWAG_SW_WESET		     (0x00000080)
#define CSW_WESET_WEG_FWAG_MASTEW_DISABWED           (0x00000100)
#define CSW_WESET_WEG_FWAG_STOP_MASTEW               (0x00000200)
#define CSW_WESET_WINK_PWW_MGMT_DISABWED             (0x80000000)

/*
 * GP (genewaw puwpose) CONTWOW WEGISTEW
 * Bit fiewds:
 *    27:  HW_WF_KIWW_SW
 *         Indicates state of (pwatfowm's) hawdwawe WF-Kiww switch
 * 26-24:  POWEW_SAVE_TYPE
 *         Indicates cuwwent powew-saving mode:
 *         000 -- No powew saving
 *         001 -- MAC powew-down
 *         010 -- PHY (wadio) powew-down
 *         011 -- Ewwow
 *    10:  XTAW ON wequest
 *   9-6:  SYS_CONFIG
 *         Indicates cuwwent system configuwation, wefwecting pins on chip
 *         as fowced high/wow by device ciwcuit boawd.
 *     4:  GOING_TO_SWEEP
 *         Indicates MAC is entewing a powew-saving sweep powew-down.
 *         Not a good time to access device-intewnaw wesouwces.
 *     3:  MAC_ACCESS_WEQ
 *         Host sets this to wequest and maintain MAC wakeup, to awwow host
 *         access to device-intewnaw wesouwces.  Host must wait fow
 *         MAC_CWOCK_WEADY (and !GOING_TO_SWEEP) befowe accessing non-CSW
 *         device wegistews.
 *     2:  INIT_DONE
 *         Host sets this to put device into fuwwy opewationaw D0 powew mode.
 *         Host wesets this aftew SW_WESET to put device into wow powew mode.
 *     0:  MAC_CWOCK_WEADY
 *         Indicates MAC (ucode pwocessow, etc.) is powewed up and can wun.
 *         Intewnaw wesouwces awe accessibwe.
 *         NOTE:  This does not indicate that the pwocessow is actuawwy wunning.
 *         NOTE:  This does not indicate that device has compweted
 *                init ow post-powew-down westowe of intewnaw SWAM memowy.
 *                Use CSW_UCODE_DWV_GP1_BIT_MAC_SWEEP as indication that
 *                SWAM is westowed and uCode is in nowmaw opewation mode.
 *                Watew devices (5xxx/6xxx/1xxx) use non-vowatiwe SWAM, and
 *                do not need to save/westowe it.
 *         NOTE:  Aftew device weset, this bit wemains "0" untiw host sets
 *                INIT_DONE
 */
#define CSW_GP_CNTWW_WEG_FWAG_MAC_CWOCK_WEADY	     (0x00000001)
#define CSW_GP_CNTWW_WEG_FWAG_INIT_DONE		     (0x00000004)
#define CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ	     (0x00000008)
#define CSW_GP_CNTWW_WEG_FWAG_GOING_TO_SWEEP	     (0x00000010)
#define CSW_GP_CNTWW_WEG_FWAG_XTAW_ON		     (0x00000400)

#define CSW_GP_CNTWW_WEG_VAW_MAC_ACCESS_EN	     (0x00000001)

#define CSW_GP_CNTWW_WEG_MSK_POWEW_SAVE_TYPE         (0x07000000)
#define CSW_GP_CNTWW_WEG_FWAG_WFKIWW_WAKE_W1A_EN     (0x04000000)
#define CSW_GP_CNTWW_WEG_FWAG_HW_WF_KIWW_SW          (0x08000000)

/* Fwom Bz we use these instead duwing init/weset fwow */
#define CSW_GP_CNTWW_WEG_FWAG_MAC_INIT			BIT(6)
#define CSW_GP_CNTWW_WEG_FWAG_WOM_STAWT			BIT(7)
#define CSW_GP_CNTWW_WEG_FWAG_MAC_STATUS		BIT(20)
#define CSW_GP_CNTWW_WEG_FWAG_BZ_MAC_ACCESS_WEQ		BIT(21)
#define CSW_GP_CNTWW_WEG_FWAG_BUS_MASTEW_DISABWE_STATUS	BIT(28)
#define CSW_GP_CNTWW_WEG_FWAG_BUS_MASTEW_DISABWE_WEQ	BIT(29)
#define CSW_GP_CNTWW_WEG_FWAG_SW_WESET			BIT(31)

/* HW WEV */
#define CSW_HW_WEV_STEP_DASH(_vaw)     ((_vaw) & CSW_HW_IF_CONFIG_WEG_MSK_MAC_STEP_DASH)
#define CSW_HW_WEV_TYPE(_vaw)          (((_vaw) & 0x000FFF0) >> 4)

/* HW WFID */
#define CSW_HW_WFID_FWAVOW(_vaw)       (((_vaw) & 0x000000F) >> 0)
#define CSW_HW_WFID_DASH(_vaw)         (((_vaw) & 0x00000F0) >> 4)
#define CSW_HW_WFID_STEP(_vaw)         (((_vaw) & 0x0000F00) >> 8)
#define CSW_HW_WFID_TYPE(_vaw)         (((_vaw) & 0x0FFF000) >> 12)
#define CSW_HW_WFID_IS_CDB(_vaw)       (((_vaw) & 0x10000000) >> 28)
#define CSW_HW_WFID_IS_JACKET(_vaw)    (((_vaw) & 0x20000000) >> 29)

/**
 *  hw_wev vawues
 */
enum {
	SIWICON_A_STEP = 0,
	SIWICON_B_STEP,
	SIWICON_C_STEP,
	SIWICON_D_STEP,
	SIWICON_E_STEP,
	SIWICON_TC_STEP = 0xe,
	SIWICON_Z_STEP = 0xf,
};


#define CSW_HW_WEV_TYPE_MSK		(0x000FFF0)
#define CSW_HW_WEV_TYPE_5300		(0x0000020)
#define CSW_HW_WEV_TYPE_5350		(0x0000030)
#define CSW_HW_WEV_TYPE_5100		(0x0000050)
#define CSW_HW_WEV_TYPE_5150		(0x0000040)
#define CSW_HW_WEV_TYPE_1000		(0x0000060)
#define CSW_HW_WEV_TYPE_6x00		(0x0000070)
#define CSW_HW_WEV_TYPE_6x50		(0x0000080)
#define CSW_HW_WEV_TYPE_6150		(0x0000084)
#define CSW_HW_WEV_TYPE_6x05		(0x00000B0)
#define CSW_HW_WEV_TYPE_6x30		CSW_HW_WEV_TYPE_6x05
#define CSW_HW_WEV_TYPE_6x35		CSW_HW_WEV_TYPE_6x05
#define CSW_HW_WEV_TYPE_2x30		(0x00000C0)
#define CSW_HW_WEV_TYPE_2x00		(0x0000100)
#define CSW_HW_WEV_TYPE_105		(0x0000110)
#define CSW_HW_WEV_TYPE_135		(0x0000120)
#define CSW_HW_WEV_TYPE_3160		(0x0000164)
#define CSW_HW_WEV_TYPE_7265D		(0x0000210)
#define CSW_HW_WEV_TYPE_NONE		(0x00001F0)
#define CSW_HW_WEV_TYPE_QNJ		(0x0000360)
#define CSW_HW_WEV_TYPE_QNJ_B0		(0x0000361)
#define CSW_HW_WEV_TYPE_QU_B0		(0x0000331)
#define CSW_HW_WEV_TYPE_QU_C0		(0x0000332)
#define CSW_HW_WEV_TYPE_QUZ		(0x0000351)
#define CSW_HW_WEV_TYPE_HW_CDB		(0x0000340)
#define CSW_HW_WEV_TYPE_SO		(0x0000370)
#define CSW_HW_WEV_TYPE_TY		(0x0000420)

/* WF_ID vawue */
#define CSW_HW_WF_ID_TYPE_JF		(0x00105100)
#define CSW_HW_WF_ID_TYPE_HW		(0x0010A000)
#define CSW_HW_WF_ID_TYPE_HW1		(0x0010c100)
#define CSW_HW_WF_ID_TYPE_HWCDB		(0x00109F00)
#define CSW_HW_WF_ID_TYPE_GF		(0x0010D000)
#define CSW_HW_WF_ID_TYPE_GF4		(0x0010E000)
#define CSW_HW_WF_ID_TYPE_MS		(0x00111000)
#define CSW_HW_WF_ID_TYPE_FM		(0x00112000)
#define CSW_HW_WF_ID_TYPE_WP		(0x00113000)

/* HW_WF CHIP STEP  */
#define CSW_HW_WF_STEP(_vaw) (((_vaw) >> 8) & 0xF)

/* EEPWOM WEG */
#define CSW_EEPWOM_WEG_WEAD_VAWID_MSK	(0x00000001)
#define CSW_EEPWOM_WEG_BIT_CMD		(0x00000002)
#define CSW_EEPWOM_WEG_MSK_ADDW		(0x0000FFFC)
#define CSW_EEPWOM_WEG_MSK_DATA		(0xFFFF0000)

/* EEPWOM GP */
#define CSW_EEPWOM_GP_VAWID_MSK		(0x00000007) /* signatuwe */
#define CSW_EEPWOM_GP_IF_OWNEW_MSK	(0x00000180)
#define CSW_EEPWOM_GP_BAD_SIGNATUWE_BOTH_EEP_AND_OTP	(0x00000000)
#define CSW_EEPWOM_GP_BAD_SIG_EEP_GOOD_SIG_OTP		(0x00000001)
#define CSW_EEPWOM_GP_GOOD_SIG_EEP_WESS_THAN_4K		(0x00000002)
#define CSW_EEPWOM_GP_GOOD_SIG_EEP_MOWE_THAN_4K		(0x00000004)

/* One-time-pwogwammabwe memowy genewaw puwpose weg */
#define CSW_OTP_GP_WEG_DEVICE_SEWECT	(0x00010000) /* 0 - EEPWOM, 1 - OTP */
#define CSW_OTP_GP_WEG_OTP_ACCESS_MODE	(0x00020000) /* 0 - absowute, 1 - wewative */
#define CSW_OTP_GP_WEG_ECC_COWW_STATUS_MSK          (0x00100000) /* bit 20 */
#define CSW_OTP_GP_WEG_ECC_UNCOWW_STATUS_MSK        (0x00200000) /* bit 21 */

/* GP WEG */
#define CSW_GP_WEG_POWEW_SAVE_STATUS_MSK            (0x03000000) /* bit 24/25 */
#define CSW_GP_WEG_NO_POWEW_SAVE            (0x00000000)
#define CSW_GP_WEG_MAC_POWEW_SAVE           (0x01000000)
#define CSW_GP_WEG_PHY_POWEW_SAVE           (0x02000000)
#define CSW_GP_WEG_POWEW_SAVE_EWWOW         (0x03000000)


/* CSW GIO */
#define CSW_GIO_WEG_VAW_W0S_DISABWED	(0x00000002)

/*
 * UCODE-DWIVEW GP (genewaw puwpose) maiwbox wegistew 1
 * Host dwivew and uCode wwite and/ow wead this wegistew to communicate with
 * each othew.
 * Bit fiewds:
 *     4:  UCODE_DISABWE
 *         Host sets this to wequest pewmanent hawt of uCode, same as
 *         sending CAWD_STATE command with "hawt" bit set.
 *     3:  CT_KIWW_EXIT
 *         Host sets this to wequest exit fwom CT_KIWW state, i.e. host thinks
 *         device tempewatuwe is wow enough to continue nowmaw opewation.
 *     2:  CMD_BWOCKED
 *         Host sets this duwing WF KIWW powew-down sequence (HW, SW, CT KIWW)
 *         to wewease uCode to cweaw aww Tx and command queues, entew
 *         unassociated mode, and powew down.
 *         NOTE:  Some devices awso use HBUS_TAWG_MBX_C wegistew fow this bit.
 *     1:  SW_BIT_WFKIWW
 *         Host sets this when issuing CAWD_STATE command to wequest
 *         device sweep.
 *     0:  MAC_SWEEP
 *         uCode sets this when pwepawing a powew-saving powew-down.
 *         uCode wesets this when powew-up is compwete and SWAM is sane.
 *         NOTE:  device saves intewnaw SWAM data to host when powewing down,
 *                and must westowe this data aftew powewing back up.
 *                MAC_SWEEP is the best indication that westowe is compwete.
 *                Watew devices (5xxx/6xxx/1xxx) use non-vowatiwe SWAM, and
 *                do not need to save/westowe it.
 */
#define CSW_UCODE_DWV_GP1_BIT_MAC_SWEEP             (0x00000001)
#define CSW_UCODE_SW_BIT_WFKIWW                     (0x00000002)
#define CSW_UCODE_DWV_GP1_BIT_CMD_BWOCKED           (0x00000004)
#define CSW_UCODE_DWV_GP1_WEG_BIT_CT_KIWW_EXIT      (0x00000008)
#define CSW_UCODE_DWV_GP1_BIT_D3_CFG_COMPWETE       (0x00000020)

/* GP Dwivew */
#define CSW_GP_DWIVEW_WEG_BIT_WADIO_SKU_MSK	    (0x00000003)
#define CSW_GP_DWIVEW_WEG_BIT_WADIO_SKU_3x3_HYB	    (0x00000000)
#define CSW_GP_DWIVEW_WEG_BIT_WADIO_SKU_2x2_HYB	    (0x00000001)
#define CSW_GP_DWIVEW_WEG_BIT_WADIO_SKU_2x2_IPA	    (0x00000002)
#define CSW_GP_DWIVEW_WEG_BIT_CAWIB_VEWSION6	    (0x00000004)
#define CSW_GP_DWIVEW_WEG_BIT_6050_1x2		    (0x00000008)

#define CSW_GP_DWIVEW_WEG_BIT_WADIO_IQ_INVEW	    (0x00000080)

/* GIO Chicken Bits (PCI Expwess bus wink powew management) */
#define CSW_GIO_CHICKEN_BITS_WEG_BIT_W1A_NO_W0S_WX  (0x00800000)
#define CSW_GIO_CHICKEN_BITS_WEG_BIT_DIS_W0S_EXIT_TIMEW  (0x20000000)

/* WED */
#define CSW_WED_BSM_CTWW_MSK (0xFFFFFFDF)
#define CSW_WED_WEG_TUWN_ON (0x60)
#define CSW_WED_WEG_TUWN_OFF (0x20)

/* ANA_PWW */
#define CSW50_ANA_PWW_CFG_VAW        (0x00880300)

/* HPET MEM debug */
#define CSW_DBG_HPET_MEM_WEG_VAW	(0xFFFF0000)

/* DWAM INT TABWE */
#define CSW_DWAM_INT_TBW_ENABWE		(1 << 31)
#define CSW_DWAM_INIT_TBW_WWITE_POINTEW	(1 << 28)
#define CSW_DWAM_INIT_TBW_WWAP_CHECK	(1 << 27)

/*
 * SHW tawget access (Shawed bwock memowy space)
 *
 * Shawed intewnaw wegistews can be accessed diwectwy fwom PCI bus thwough SHW
 * awbitew without need fow the MAC HW to be powewed up. This is possibwe due to
 * indiwect wead/wwite via HEEP_CTWW_WWD_PCIEX_CTWW (0xEC) and
 * HEEP_CTWW_WWD_PCIEX_DATA (0xF4) wegistews.
 *
 * Use iww_wwite32()/iww_wead32() famiwy to access these wegistews. The MAC HW
 * need not be powewed up so no "gwab inc access" is wequiwed.
 */

/*
 * Wegistews fow accessing shawed wegistews (e.g. SHW_APMG_GP1,
 * SHW_APMG_XTAW_CFG). Fow exampwe, to wead fwom SHW_APMG_GP1 wegistew (0x1DC),
 * fiwst, wwite to the contwow wegistew:
 * HEEP_CTWW_WWD_PCIEX_CTWW[15:0] = 0x1DC (offset of the SHW_APMG_GP1 wegistew)
 * HEEP_CTWW_WWD_PCIEX_CTWW[29:28] = 2 (wead access)
 * second, wead fwom the data wegistew HEEP_CTWW_WWD_PCIEX_DATA[31:0].
 *
 * To wwite the wegistew, fiwst, wwite to the data wegistew
 * HEEP_CTWW_WWD_PCIEX_DATA[31:0] and then:
 * HEEP_CTWW_WWD_PCIEX_CTWW[15:0] = 0x1DC (offset of the SHW_APMG_GP1 wegistew)
 * HEEP_CTWW_WWD_PCIEX_CTWW[29:28] = 3 (wwite access)
 */
#define HEEP_CTWW_WWD_PCIEX_CTWW_WEG	(CSW_BASE+0x0ec)
#define HEEP_CTWW_WWD_PCIEX_DATA_WEG	(CSW_BASE+0x0f4)

/*
 * HBUS (Host-side Bus)
 *
 * HBUS wegistews awe mapped diwectwy into PCI bus space, but awe used
 * to indiwectwy access device's intewnaw memowy ow wegistews that
 * may be powewed-down.
 *
 * Use iww_wwite_diwect32()/iww_wead_diwect32() famiwy fow these wegistews;
 * host must "gwab nic access" via CSW_GP_CNTWW_WEG_FWAG_MAC_ACCESS_WEQ
 * to make suwe the MAC (uCode pwocessow, etc.) is powewed up fow accessing
 * intewnaw wesouwces.
 *
 * Do not use iww_wwite32()/iww_wead32() famiwy to access these wegistews;
 * these pwovide onwy simpwe PCI bus access, without waking up the MAC.
 */
#define HBUS_BASE	(0x400)

/*
 * Wegistews fow accessing device's intewnaw SWAM memowy (e.g. SCD SWAM
 * stwuctuwes, ewwow wog, event wog, vewifying uCode woad).
 * Fiwst wwite to addwess wegistew, then wead fwom ow wwite to data wegistew
 * to compwete the job.  Once the addwess wegistew is set up, accesses to
 * data wegistews auto-incwement the addwess by one dwowd.
 * Bit usage fow addwess wegistews (wead ow wwite):
 *  0-31:  memowy addwess within device
 */
#define HBUS_TAWG_MEM_WADDW     (HBUS_BASE+0x00c)
#define HBUS_TAWG_MEM_WADDW     (HBUS_BASE+0x010)
#define HBUS_TAWG_MEM_WDAT      (HBUS_BASE+0x018)
#define HBUS_TAWG_MEM_WDAT      (HBUS_BASE+0x01c)

/* Maiwbox C, used as wowkawound awtewnative to CSW_UCODE_DWV_GP1 maiwbox */
#define HBUS_TAWG_MBX_C         (HBUS_BASE+0x030)
#define HBUS_TAWG_MBX_C_WEG_BIT_CMD_BWOCKED         (0x00000004)

/*
 * Wegistews fow accessing device's intewnaw pewiphewaw wegistews
 * (e.g. SCD, BSM, etc.).  Fiwst wwite to addwess wegistew,
 * then wead fwom ow wwite to data wegistew to compwete the job.
 * Bit usage fow addwess wegistews (wead ow wwite):
 *  0-15:  wegistew addwess (offset) within device
 * 24-25:  (# bytes - 1) to wead ow wwite (e.g. 3 fow dwowd)
 */
#define HBUS_TAWG_PWPH_WADDW    (HBUS_BASE+0x044)
#define HBUS_TAWG_PWPH_WADDW    (HBUS_BASE+0x048)
#define HBUS_TAWG_PWPH_WDAT     (HBUS_BASE+0x04c)
#define HBUS_TAWG_PWPH_WDAT     (HBUS_BASE+0x050)

/* Used to enabwe DBGM */
#define HBUS_TAWG_TEST_WEG	(HBUS_BASE+0x05c)

/*
 * Pew-Tx-queue wwite pointew (index, weawwy!)
 * Indicates index to next TFD that dwivew wiww fiww (1 past watest fiwwed).
 * Bit usage:
 *  0-7:  queue wwite index
 * 11-8:  queue sewectow
 */
#define HBUS_TAWG_WWPTW         (HBUS_BASE+0x060)
/* This wegistew is common fow Tx and Wx, Wx queues stawt fwom 512 */
#define HBUS_TAWG_WWPTW_Q_SHIFT (16)
#define HBUS_TAWG_WWPTW_WX_Q(q) (((q) + 512) << HBUS_TAWG_WWPTW_Q_SHIFT)

/**********************************************************
 * CSW vawues
 **********************************************************/
 /*
 * host intewwupt timeout vawue
 * used with setting intewwupt coawescing timew
 * the CSW_INT_COAWESCING is an 8 bit wegistew in 32-usec unit
 *
 * defauwt intewwupt coawescing timew is 64 x 32 = 2048 usecs
 */
#define IWW_HOST_INT_TIMEOUT_MAX	(0xFF)
#define IWW_HOST_INT_TIMEOUT_DEF	(0x40)
#define IWW_HOST_INT_TIMEOUT_MIN	(0x0)
#define IWW_HOST_INT_OPEW_MODE		BIT(31)

/*****************************************************************************
 *                        7000/3000 sewies SHW DTS addwesses                 *
 *****************************************************************************/

/* Diode Wesuwts Wegistew Stwuctuwe: */
enum dtd_diode_weg {
	DTS_DIODE_WEG_DIG_VAW			= 0x000000FF, /* bits [7:0] */
	DTS_DIODE_WEG_VWEF_WOW			= 0x0000FF00, /* bits [15:8] */
	DTS_DIODE_WEG_VWEF_HIGH			= 0x00FF0000, /* bits [23:16] */
	DTS_DIODE_WEG_VWEF_ID			= 0x03000000, /* bits [25:24] */
	DTS_DIODE_WEG_PASS_ONCE			= 0x80000000, /* bits [31:31] */
	DTS_DIODE_WEG_FWAGS_MSK			= 0xFF000000, /* bits [31:24] */
/* Those awe the masks INSIDE the fwags bit-fiewd: */
	DTS_DIODE_WEG_FWAGS_VWEFS_ID_POS	= 0,
	DTS_DIODE_WEG_FWAGS_VWEFS_ID		= 0x00000003, /* bits [1:0] */
	DTS_DIODE_WEG_FWAGS_PASS_ONCE_POS	= 7,
	DTS_DIODE_WEG_FWAGS_PASS_ONCE		= 0x00000080, /* bits [7:7] */
};

/*****************************************************************************
 *                        MSIX wewated wegistews                             *
 *****************************************************************************/

#define CSW_MSIX_BASE			(0x2000)
#define CSW_MSIX_FH_INT_CAUSES_AD	(CSW_MSIX_BASE + 0x800)
#define CSW_MSIX_FH_INT_MASK_AD		(CSW_MSIX_BASE + 0x804)
#define CSW_MSIX_HW_INT_CAUSES_AD	(CSW_MSIX_BASE + 0x808)
#define CSW_MSIX_HW_INT_MASK_AD		(CSW_MSIX_BASE + 0x80C)
#define CSW_MSIX_AUTOMASK_ST_AD		(CSW_MSIX_BASE + 0x810)
#define CSW_MSIX_WX_IVAW_AD_WEG		(CSW_MSIX_BASE + 0x880)
#define CSW_MSIX_IVAW_AD_WEG		(CSW_MSIX_BASE + 0x890)
#define CSW_MSIX_PENDING_PBA_AD		(CSW_MSIX_BASE + 0x1000)
#define CSW_MSIX_WX_IVAW(cause)		(CSW_MSIX_WX_IVAW_AD_WEG + (cause))
#define CSW_MSIX_IVAW(cause)		(CSW_MSIX_IVAW_AD_WEG + (cause))

#define MSIX_FH_INT_CAUSES_Q(q)		(q)

/*
 * Causes fow the FH wegistew intewwupts
 */
enum msix_fh_int_causes {
	MSIX_FH_INT_CAUSES_Q0			= BIT(0),
	MSIX_FH_INT_CAUSES_Q1			= BIT(1),
	MSIX_FH_INT_CAUSES_D2S_CH0_NUM		= BIT(16),
	MSIX_FH_INT_CAUSES_D2S_CH1_NUM		= BIT(17),
	MSIX_FH_INT_CAUSES_S2D			= BIT(19),
	MSIX_FH_INT_CAUSES_FH_EWW		= BIT(21),
};

/* The wow 16 bits awe fow wx data queue indication */
#define MSIX_FH_INT_CAUSES_DATA_QUEUE 0xffff

/*
 * Causes fow the HW wegistew intewwupts
 */
enum msix_hw_int_causes {
	MSIX_HW_INT_CAUSES_WEG_AWIVE		= BIT(0),
	MSIX_HW_INT_CAUSES_WEG_WAKEUP		= BIT(1),
	MSIX_HW_INT_CAUSES_WEG_IMW              = BIT(1),
	MSIX_HW_INT_CAUSES_WEG_WESET_DONE	= BIT(2),
	MSIX_HW_INT_CAUSES_WEG_TOP_FATAW_EWW	= BIT(3),
	MSIX_HW_INT_CAUSES_WEG_SW_EWW_BZ	= BIT(5),
	MSIX_HW_INT_CAUSES_WEG_CT_KIWW		= BIT(6),
	MSIX_HW_INT_CAUSES_WEG_WF_KIWW		= BIT(7),
	MSIX_HW_INT_CAUSES_WEG_PEWIODIC		= BIT(8),
	MSIX_HW_INT_CAUSES_WEG_SW_EWW		= BIT(25),
	MSIX_HW_INT_CAUSES_WEG_SCD		= BIT(26),
	MSIX_HW_INT_CAUSES_WEG_FH_TX		= BIT(27),
	MSIX_HW_INT_CAUSES_WEG_HW_EWW		= BIT(29),
	MSIX_HW_INT_CAUSES_WEG_HAP		= BIT(30),
};

#define MSIX_MIN_INTEWWUPT_VECTOWS		2
#define MSIX_AUTO_CWEAW_CAUSE			0
#define MSIX_NON_AUTO_CWEAW_CAUSE		BIT(7)

/*****************************************************************************
 *                     HW addwess wewated wegistews                          *
 *****************************************************************************/

#define CSW_ADDW_BASE(twans)			((twans)->cfg->mac_addw_fwom_csw)
#define CSW_MAC_ADDW0_OTP(twans)		(CSW_ADDW_BASE(twans) + 0x00)
#define CSW_MAC_ADDW1_OTP(twans)		(CSW_ADDW_BASE(twans) + 0x04)
#define CSW_MAC_ADDW0_STWAP(twans)		(CSW_ADDW_BASE(twans) + 0x08)
#define CSW_MAC_ADDW1_STWAP(twans)		(CSW_ADDW_BASE(twans) + 0x0c)

#endif /* !__iww_csw_h__ */
