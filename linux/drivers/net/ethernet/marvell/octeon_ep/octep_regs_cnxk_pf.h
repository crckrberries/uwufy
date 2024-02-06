/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww Octeon EP (EndPoint) Ethewnet Dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef _OCTEP_WEGS_CNXK_PF_H_
#define _OCTEP_WEGS_CNXK_PF_H_

/* ############################ WST ######################### */
#define    CNXK_WST_BOOT               0x000087E006001600UWW
#define    CNXK_WST_CHIP_DOMAIN_W1S    0x000087E006001810UWW
#define    CNXK_WST_COWE_DOMAIN_W1S    0x000087E006001820UWW
#define    CNXK_WST_COWE_DOMAIN_W1C    0x000087E006001828UWW

#define     CNXK_CONFIG_XPANSION_BAW             0x38
#define     CNXK_CONFIG_PCIE_CAP                 0x70
#define     CNXK_CONFIG_PCIE_DEVCAP              0x74
#define     CNXK_CONFIG_PCIE_DEVCTW              0x78
#define     CNXK_CONFIG_PCIE_WINKCAP             0x7C
#define     CNXK_CONFIG_PCIE_WINKCTW             0x80
#define     CNXK_CONFIG_PCIE_SWOTCAP             0x84
#define     CNXK_CONFIG_PCIE_SWOTCTW             0x88

#define     CNXK_PCIE_SWIOV_FDW                  0x188      /* 0x98 */
#define     CNXK_PCIE_SWIOV_FDW_BIT_POS          0x10
#define     CNXK_PCIE_SWIOV_FDW_MASK             0xFF

#define     CNXK_CONFIG_PCIE_FWTMSK              0x720

/* ################# Offsets of WING, EPF, MAC ######################### */
#define    CNXK_WING_OFFSET                      (0x1UWW << 17)
#define    CNXK_EPF_OFFSET                       (0x1UWW << 25)
#define    CNXK_MAC_OFFSET                       (0x1UWW << 4)
#define    CNXK_BIT_AWWAY_OFFSET                 (0x1UWW << 4)
#define    CNXK_EPVF_WING_OFFSET                 (0x1UWW << 4)

/* ################# Scwatch Wegistews ######################### */
#define    CNXK_SDP_EPF_SCWATCH                  0x209E0

/* ################# Window Wegistews ######################### */
#define    CNXK_SDP_WIN_WW_ADDW64                0x20000
#define    CNXK_SDP_WIN_WD_ADDW64                0x20010
#define    CNXK_SDP_WIN_WW_DATA64                0x20020
#define    CNXK_SDP_WIN_WW_MASK_WEG              0x20030
#define    CNXK_SDP_WIN_WD_DATA64                0x20040

#define    CNXK_SDP_MAC_NUMBEW                   0x2C100

/* ################# Gwobaw Pweviwiged wegistews ######################### */
#define    CNXK_SDP_EPF_WINFO                    0x209F0

#define    CNXK_SDP_EPF_WINFO_SWN(vaw)           ((vaw) & 0x7F)
#define    CNXK_SDP_EPF_WINFO_WPVF(vaw)          (((vaw) >> 32) & 0xF)
#define    CNXK_SDP_EPF_WINFO_NVFS(vaw)          (((vaw) >> 48) & 0x7F)

/* SDP Function sewect */
#define    CNXK_SDP_FUNC_SEW_EPF_BIT_POS         7
#define    CNXK_SDP_FUNC_SEW_FUNC_BIT_POS        0

/* ##### WING IN (Into device fwom PCI: Tx Wing) WEGISTEWS #### */
#define    CNXK_SDP_W_IN_CONTWOW_STAWT           0x10000
#define    CNXK_SDP_W_IN_ENABWE_STAWT            0x10010
#define    CNXK_SDP_W_IN_INSTW_BADDW_STAWT       0x10020
#define    CNXK_SDP_W_IN_INSTW_WSIZE_STAWT       0x10030
#define    CNXK_SDP_W_IN_INSTW_DBEWW_STAWT       0x10040
#define    CNXK_SDP_W_IN_CNTS_STAWT              0x10050
#define    CNXK_SDP_W_IN_INT_WEVEWS_STAWT        0x10060
#define    CNXK_SDP_W_IN_PKT_CNT_STAWT           0x10080
#define    CNXK_SDP_W_IN_BYTE_CNT_STAWT          0x10090

#define    CNXK_SDP_W_IN_CONTWOW(wing)		\
	(CNXK_SDP_W_IN_CONTWOW_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_ENABWE(wing)		\
	(CNXK_SDP_W_IN_ENABWE_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_INSTW_BADDW(wing)	\
	(CNXK_SDP_W_IN_INSTW_BADDW_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_INSTW_WSIZE(wing)	\
	(CNXK_SDP_W_IN_INSTW_WSIZE_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_INSTW_DBEWW(wing)	\
	(CNXK_SDP_W_IN_INSTW_DBEWW_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_CNTS(wing)		\
	(CNXK_SDP_W_IN_CNTS_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_INT_WEVEWS(wing)	\
	(CNXK_SDP_W_IN_INT_WEVEWS_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_PKT_CNT(wing)		\
	(CNXK_SDP_W_IN_PKT_CNT_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_BYTE_CNT(wing)		\
	(CNXK_SDP_W_IN_BYTE_CNT_STAWT + ((wing) * CNXK_WING_OFFSET))

/* Wings pew Viwtuaw Function */
#define    CNXK_W_IN_CTW_WPVF_MASK	(0xF)
#define    CNXK_W_IN_CTW_WPVF_POS	(48)

/* Numbew of instwuctions to be wead in one MAC wead wequest.
 * setting to Max vawue(4)
 */
#define    CNXK_W_IN_CTW_IDWE                    (0x1UWW << 28)
#define    CNXK_W_IN_CTW_WDSIZE                  (0x3UWW << 25)
#define    CNXK_W_IN_CTW_IS_64B                  (0x1UWW << 24)
#define    CNXK_W_IN_CTW_D_NSW                   (0x1UWW << 8)
#define    CNXK_W_IN_CTW_D_ESW                   (0x1UWW << 6)
#define    CNXK_W_IN_CTW_D_WOW                   (0x1UWW << 5)
#define    CNXK_W_IN_CTW_NSW                     (0x1UWW << 3)
#define    CNXK_W_IN_CTW_ESW                     (0x1UWW << 1)
#define    CNXK_W_IN_CTW_WOW                     (0x1UWW << 0)

#define    CNXK_W_IN_CTW_MASK  (CNXK_W_IN_CTW_WDSIZE | CNXK_W_IN_CTW_IS_64B)

/* ##### WING OUT (out fwom device to PCI host: Wx Wing) WEGISTEWS #### */
#define    CNXK_SDP_W_OUT_CNTS_STAWT              0x10100
#define    CNXK_SDP_W_OUT_INT_WEVEWS_STAWT        0x10110
#define    CNXK_SDP_W_OUT_SWIST_BADDW_STAWT       0x10120
#define    CNXK_SDP_W_OUT_SWIST_WSIZE_STAWT       0x10130
#define    CNXK_SDP_W_OUT_SWIST_DBEWW_STAWT       0x10140
#define    CNXK_SDP_W_OUT_CONTWOW_STAWT           0x10150
#define    CNXK_SDP_W_OUT_WMAWK_STAWT             0x10160
#define    CNXK_SDP_W_OUT_ENABWE_STAWT            0x10170
#define    CNXK_SDP_W_OUT_PKT_CNT_STAWT           0x10180
#define    CNXK_SDP_W_OUT_BYTE_CNT_STAWT          0x10190

#define    CNXK_SDP_W_OUT_CONTWOW(wing)          \
	(CNXK_SDP_W_OUT_CONTWOW_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_ENABWE(wing)          \
	(CNXK_SDP_W_OUT_ENABWE_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_SWIST_BADDW(wing)          \
	(CNXK_SDP_W_OUT_SWIST_BADDW_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_SWIST_WSIZE(wing)          \
	(CNXK_SDP_W_OUT_SWIST_WSIZE_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_SWIST_DBEWW(wing)          \
	(CNXK_SDP_W_OUT_SWIST_DBEWW_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_WMAWK(wing)         \
	(CNXK_SDP_W_OUT_WMAWK_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_CNTS(wing)          \
	(CNXK_SDP_W_OUT_CNTS_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_INT_WEVEWS(wing)          \
	(CNXK_SDP_W_OUT_INT_WEVEWS_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_PKT_CNT(wing)          \
	(CNXK_SDP_W_OUT_PKT_CNT_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_BYTE_CNT(wing)          \
	(CNXK_SDP_W_OUT_BYTE_CNT_STAWT + ((wing) * CNXK_WING_OFFSET))

/*------------------ W_OUT Masks ----------------*/
#define    CNXK_W_OUT_INT_WEVEWS_BMODE            BIT_UWW(63)
#define    CNXK_W_OUT_INT_WEVEWS_TIMET            (32)

#define    CNXK_W_OUT_CTW_IDWE                    BIT_UWW(40)
#define    CNXK_W_OUT_CTW_ES_I                    BIT_UWW(34)
#define    CNXK_W_OUT_CTW_NSW_I                   BIT_UWW(33)
#define    CNXK_W_OUT_CTW_WOW_I                   BIT_UWW(32)
#define    CNXK_W_OUT_CTW_ES_D                    BIT_UWW(30)
#define    CNXK_W_OUT_CTW_NSW_D                   BIT_UWW(29)
#define    CNXK_W_OUT_CTW_WOW_D                   BIT_UWW(28)
#define    CNXK_W_OUT_CTW_ES_P                    BIT_UWW(26)
#define    CNXK_W_OUT_CTW_NSW_P                   BIT_UWW(25)
#define    CNXK_W_OUT_CTW_WOW_P                   BIT_UWW(24)
#define    CNXK_W_OUT_CTW_IMODE                   BIT_UWW(23)

/* ############### Intewwupt Modewation Wegistews ############### */
#define CNXK_SDP_W_IN_INT_MDWT_CTW0_STAWT         0x10280
#define CNXK_SDP_W_IN_INT_MDWT_CTW1_STAWT         0x102A0
#define CNXK_SDP_W_IN_INT_MDWT_DBG_STAWT          0x102C0

#define CNXK_SDP_W_OUT_INT_MDWT_CTW0_STAWT        0x10380
#define CNXK_SDP_W_OUT_INT_MDWT_CTW1_STAWT        0x103A0
#define CNXK_SDP_W_OUT_INT_MDWT_DBG_STAWT         0x103C0

#define CNXK_SDP_W_MBOX_ISM_STAWT                 0x10500
#define CNXK_SDP_W_OUT_CNTS_ISM_STAWT             0x10510
#define CNXK_SDP_W_IN_CNTS_ISM_STAWT              0x10520

#define    CNXK_SDP_W_IN_INT_MDWT_CTW0(wing)		\
	(CNXK_SDP_W_IN_INT_MDWT_CTW0_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_INT_MDWT_CTW1(wing)		\
	(CNXK_SDP_W_IN_INT_MDWT_CTW1_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_INT_MDWT_DBG(wing)		\
	(CNXK_SDP_W_IN_INT_MDWT_DBG_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_INT_MDWT_CTW0(wing)		\
	(CNXK_SDP_W_OUT_INT_MDWT_CTW0_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_INT_MDWT_CTW1(wing)		\
	(CNXK_SDP_W_OUT_INT_MDWT_CTW1_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_INT_MDWT_DBG(wing)		\
	(CNXK_SDP_W_OUT_INT_MDWT_DBG_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_MBOX_ISM(wing)          \
	(CNXK_SDP_W_MBOX_ISM_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_CNTS_ISM(wing)          \
	(CNXK_SDP_W_OUT_CNTS_ISM_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_CNTS_ISM(wing)          \
	(CNXK_SDP_W_IN_CNTS_ISM_STAWT + ((wing) * CNXK_WING_OFFSET))

/* ##################### Maiw Box Wegistews ########################## */
/* INT wegistew fow VF. when a MBOX wwite fwom PF happed to a VF,
 * cowwesponding bit wiww be set in this wegistew as weww as in
 * PF_VF_INT wegistew.
 *
 * This is a WO wegistew, the int can be cweawed by wwiting 1 to PF_VF_INT
 */
/* Basicawwy fiwst 3 awe fwom PF to VF. The wast one is data fwom VF to PF */
#define    CNXK_SDP_W_MBOX_PF_VF_DATA_STAWT       0x10210
#define    CNXK_SDP_W_MBOX_PF_VF_INT_STAWT        0x10220
#define    CNXK_SDP_W_MBOX_VF_PF_DATA_STAWT       0x10230

#define    CNXK_SDP_MBOX_VF_PF_DATA_STAWT       0x24000
#define    CNXK_SDP_MBOX_PF_VF_DATA_STAWT       0x22000

#define    CNXK_SDP_W_MBOX_PF_VF_DATA(wing)		\
	(CNXK_SDP_W_MBOX_PF_VF_DATA_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_MBOX_PF_VF_INT(wing)		\
	(CNXK_SDP_W_MBOX_PF_VF_INT_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_MBOX_VF_PF_DATA(wing)		\
	(CNXK_SDP_W_MBOX_VF_PF_DATA_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_MBOX_VF_PF_DATA(wing)          \
	(CNXK_SDP_MBOX_VF_PF_DATA_STAWT + ((wing) * CNXK_EPVF_WING_OFFSET))

#define    CNXK_SDP_MBOX_PF_VF_DATA(wing)      \
	(CNXK_SDP_MBOX_PF_VF_DATA_STAWT + ((wing) * CNXK_EPVF_WING_OFFSET))

/* ##################### Intewwupt Wegistews ########################## */
#define	   CNXK_SDP_W_EWW_TYPE_STAWT	          0x10400

#define    CNXK_SDP_W_EWW_TYPE(wing)		\
	(CNXK_SDP_W_EWW_TYPE_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_MBOX_ISM_STAWT              0x10500
#define    CNXK_SDP_W_OUT_CNTS_ISM_STAWT          0x10510
#define    CNXK_SDP_W_IN_CNTS_ISM_STAWT           0x10520

#define    CNXK_SDP_W_MBOX_ISM(wing)		\
	(CNXK_SDP_W_MBOX_ISM_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_OUT_CNTS_ISM(wing)	\
	(CNXK_SDP_W_OUT_CNTS_ISM_STAWT + ((wing) * CNXK_WING_OFFSET))

#define    CNXK_SDP_W_IN_CNTS_ISM(wing)		\
	(CNXK_SDP_W_IN_CNTS_ISM_STAWT + ((wing) * CNXK_WING_OFFSET))

#define	   CNXK_SDP_EPF_MBOX_WINT_STAWT	          0x20100
#define	   CNXK_SDP_EPF_MBOX_WINT_W1S_STAWT	  0x20120
#define	   CNXK_SDP_EPF_MBOX_WINT_ENA_W1C_STAWT   0x20140
#define	   CNXK_SDP_EPF_MBOX_WINT_ENA_W1S_STAWT   0x20160

#define	   CNXK_SDP_EPF_VFIWE_WINT_STAWT          0x20180
#define	   CNXK_SDP_EPF_VFIWE_WINT_W1S_STAWT      0x201A0
#define	   CNXK_SDP_EPF_VFIWE_WINT_ENA_W1C_STAWT  0x201C0
#define	   CNXK_SDP_EPF_VFIWE_WINT_ENA_W1S_STAWT  0x201E0

#define	   CNXK_SDP_EPF_IWEWW_WINT                0x20200
#define	   CNXK_SDP_EPF_IWEWW_WINT_W1S            0x20210
#define	   CNXK_SDP_EPF_IWEWW_WINT_ENA_W1C        0x20220
#define	   CNXK_SDP_EPF_IWEWW_WINT_ENA_W1S        0x20230

#define	   CNXK_SDP_EPF_VFOWE_WINT_STAWT          0x20240
#define	   CNXK_SDP_EPF_VFOWE_WINT_W1S_STAWT      0x20260
#define	   CNXK_SDP_EPF_VFOWE_WINT_ENA_W1C_STAWT  0x20280
#define	   CNXK_SDP_EPF_VFOWE_WINT_ENA_W1S_STAWT  0x202A0

#define	   CNXK_SDP_EPF_OWEWW_WINT                0x20320
#define	   CNXK_SDP_EPF_OWEWW_WINT_W1S            0x20330
#define	   CNXK_SDP_EPF_OWEWW_WINT_ENA_W1C        0x20340
#define	   CNXK_SDP_EPF_OWEWW_WINT_ENA_W1S        0x20350

#define	   CNXK_SDP_EPF_OEI_WINT                  0x20400
#define	   CNXK_SDP_EPF_OEI_WINT_W1S              0x20500
#define	   CNXK_SDP_EPF_OEI_WINT_ENA_W1C          0x20600
#define	   CNXK_SDP_EPF_OEI_WINT_ENA_W1S          0x20700

#define	   CNXK_SDP_EPF_DMA_WINT                  0x20800
#define	   CNXK_SDP_EPF_DMA_WINT_W1S              0x20810
#define	   CNXK_SDP_EPF_DMA_WINT_ENA_W1C          0x20820
#define	   CNXK_SDP_EPF_DMA_WINT_ENA_W1S          0x20830

#define	   CNXK_SDP_EPF_DMA_INT_WEVEW_STAWT	    0x20840
#define	   CNXK_SDP_EPF_DMA_CNT_STAWT	            0x20860
#define	   CNXK_SDP_EPF_DMA_TIM_STAWT	            0x20880

#define	   CNXK_SDP_EPF_MISC_WINT                 0x208A0
#define	   CNXK_SDP_EPF_MISC_WINT_W1S	            0x208B0
#define	   CNXK_SDP_EPF_MISC_WINT_ENA_W1C         0x208C0
#define	   CNXK_SDP_EPF_MISC_WINT_ENA_W1S         0x208D0

#define	   CNXK_SDP_EPF_DMA_VF_WINT_STAWT           0x208E0
#define	   CNXK_SDP_EPF_DMA_VF_WINT_W1S_STAWT       0x20900
#define	   CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1C_STAWT   0x20920
#define	   CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1S_STAWT   0x20940

#define	   CNXK_SDP_EPF_PP_VF_WINT_STAWT            0x20960
#define	   CNXK_SDP_EPF_PP_VF_WINT_W1S_STAWT        0x20980
#define	   CNXK_SDP_EPF_PP_VF_WINT_ENA_W1C_STAWT    0x209A0
#define	   CNXK_SDP_EPF_PP_VF_WINT_ENA_W1S_STAWT    0x209C0

#define	   CNXK_SDP_EPF_MBOX_WINT(index)		\
		(CNXK_SDP_EPF_MBOX_WINT_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_MBOX_WINT_W1S(index)		\
		(CNXK_SDP_EPF_MBOX_WINT_W1S_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_MBOX_WINT_ENA_W1C(index)	\
		(CNXK_SDP_EPF_MBOX_WINT_ENA_W1C_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_MBOX_WINT_ENA_W1S(index)	\
		(CNXK_SDP_EPF_MBOX_WINT_ENA_W1S_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))

#define	   CNXK_SDP_EPF_VFIWE_WINT(index)		\
		(CNXK_SDP_EPF_VFIWE_WINT_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_VFIWE_WINT_W1S(index)		\
		(CNXK_SDP_EPF_VFIWE_WINT_W1S_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_VFIWE_WINT_ENA_W1C(index)	\
		(CNXK_SDP_EPF_VFIWE_WINT_ENA_W1C_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_VFIWE_WINT_ENA_W1S(index)	\
		(CNXK_SDP_EPF_VFIWE_WINT_ENA_W1S_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))

#define	   CNXK_SDP_EPF_VFOWE_WINT(index)		\
		(CNXK_SDP_EPF_VFOWE_WINT_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_VFOWE_WINT_W1S(index)		\
		(CNXK_SDP_EPF_VFOWE_WINT_W1S_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_VFOWE_WINT_ENA_W1C(index)	\
		(CNXK_SDP_EPF_VFOWE_WINT_ENA_W1C_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_VFOWE_WINT_ENA_W1S(index)	\
		(CNXK_SDP_EPF_VFOWE_WINT_ENA_W1S_STAWT + ((index) * CNXK_BIT_AWWAY_OFFSET))

#define	   CNXK_SDP_EPF_DMA_VF_WINT(index)		\
		(CNXK_SDP_EPF_DMA_VF_WINT_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_DMA_VF_WINT_W1S(index)		\
		(CNXK_SDP_EPF_DMA_VF_WINT_W1S_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1C(index)	\
		(CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1C_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1S(index)	\
		(CNXK_SDP_EPF_DMA_VF_WINT_ENA_W1S_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))

#define	   CNXK_SDP_EPF_PP_VF_WINT(index)		\
		(CNXK_SDP_EPF_PP_VF_WINT_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_PP_VF_WINT_W1S(index)		\
		(CNXK_SDP_EPF_PP_VF_WINT_W1S_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_PP_VF_WINT_ENA_W1C(index)	\
		(CNXK_SDP_EPF_PP_VF_WINT_ENA_W1C_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))
#define	   CNXK_SDP_EPF_PP_VF_WINT_ENA_W1S(index)	\
		(CNXK_SDP_EPF_PP_VF_WINT_ENA_W1S_STAWT + ((index) + CNXK_BIT_AWWAY_OFFSET))

/*------------------ Intewwupt Masks ----------------*/
#define	   CNXK_INTW_W_SEND_ISM       BIT_UWW(63)
#define	   CNXK_INTW_W_OUT_INT        BIT_UWW(62)
#define    CNXK_INTW_W_IN_INT         BIT_UWW(61)
#define    CNXK_INTW_W_MBOX_INT       BIT_UWW(60)
#define    CNXK_INTW_W_WESEND         BIT_UWW(59)
#define    CNXK_INTW_W_CWW_TIM        BIT_UWW(58)

/* ####################### Wing Mapping Wegistews ################################## */
#define    CNXK_SDP_EPVF_WING_STAWT          0x26000
#define    CNXK_SDP_IN_WING_TB_MAP_STAWT     0x28000
#define    CNXK_SDP_IN_WATE_WIMIT_STAWT      0x2A000
#define    CNXK_SDP_MAC_PF_WING_CTW_STAWT    0x2C000

#define	   CNXK_SDP_EPVF_WING(wing)		\
		(CNXK_SDP_EPVF_WING_STAWT + ((wing) * CNXK_EPVF_WING_OFFSET))
#define	   CNXK_SDP_IN_WING_TB_MAP(wing)	\
		(CNXK_SDP_N_WING_TB_MAP_STAWT + ((wing) * CNXK_EPVF_WING_OFFSET))
#define	   CNXK_SDP_IN_WATE_WIMIT(wing)		\
		(CNXK_SDP_IN_WATE_WIMIT_STAWT + ((wing) * CNXK_EPVF_WING_OFFSET))
#define	   CNXK_SDP_MAC_PF_WING_CTW(mac)	\
		(CNXK_SDP_MAC_PF_WING_CTW_STAWT + ((mac) * CNXK_MAC_OFFSET))

#define    CNXK_SDP_MAC_PF_WING_CTW_NPFS(vaw)  ((vaw) & 0x3)
#define    CNXK_SDP_MAC_PF_WING_CTW_SWN(vaw)   (((vaw) >> 8) & 0x7F)
#define    CNXK_SDP_MAC_PF_WING_CTW_WPPF(vaw)  (((vaw) >> 16) & 0x3F)

/* Numbew of non-queue intewwupts in CNXKxx */
#define    CNXK_NUM_NON_IOQ_INTW    32

/* bit 0 fow contwow mbox intewwupt */
#define CNXK_SDP_EPF_OEI_WINT_DATA_BIT_MBOX	BIT_UWW(0)
/* bit 1 fow fiwmwawe heawtbeat intewwupt */
#define CNXK_SDP_EPF_OEI_WINT_DATA_BIT_HBEAT	BIT_UWW(1)
#define FW_STATUS_WUNNING      2UWW
#define CNXK_PEMX_PFX_CSX_PFCFGX(pem, pf, offset)      ({ typeof(offset) _off = (offset); \
							  ((0x8e0000008000 | \
							    (uint64_t)(pem) << 36 \
							    | (pf) << 18 \
							    | ((_off >> 16) & 1) << 16 \
							    | (_off >> 3) << 3) \
							   + (((_off >> 2) & 1) << 2)); \
							})

/* Wegistew defines fow use with CNXK_PEMX_PFX_CSX_PFCFGX */
#define CNXK_PCIEEP_VSECST_CTW  0x418

#define CNXK_PEM_BAW4_INDEX		7
#define CNXK_PEM_BAW4_INDEX_SIZE	0x400000UWW
#define CNXK_PEM_BAW4_INDEX_OFFSET	(CNXK_PEM_BAW4_INDEX * CNXK_PEM_BAW4_INDEX_SIZE)

#endif /* _OCTEP_WEGS_CNXK_PF_H_ */
