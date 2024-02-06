/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
/*! \fiwe cn23xx_vf_wegs.h
 * \bwief Host Dwivew: Wegistew Addwess and Wegistew Mask vawues fow
 * Octeon CN23XX vf functions.
 */

#ifndef __CN23XX_VF_WEGS_H__
#define __CN23XX_VF_WEGS_H__

#define     CN23XX_CONFIG_XPANSION_BAW             0x38

#define     CN23XX_CONFIG_PCIE_CAP                 0x70
#define     CN23XX_CONFIG_PCIE_DEVCAP              0x74
#define     CN23XX_CONFIG_PCIE_DEVCTW              0x78
#define     CN23XX_CONFIG_PCIE_WINKCAP             0x7C
#define     CN23XX_CONFIG_PCIE_WINKCTW             0x80
#define     CN23XX_CONFIG_PCIE_SWOTCAP             0x84
#define     CN23XX_CONFIG_PCIE_SWOTCTW             0x88

#define     CN23XX_CONFIG_PCIE_FWTMSK              0x720

/* The input jabbew is used to detewmine the TSO max size.
 * Due to H/W wimitation, this needs to be weduced to 60000
 * in owdew to use H/W TSO and avoid the WQE mawfowmation
 * PKO_BUG_24989_WQE_WEN
 */
#define    CN23XX_DEFAUWT_INPUT_JABBEW             0xEA60 /*60000*/

/* ##############  BAW0 Wegistews ################ */

/* Each Input Queue wegistew is at a 16-byte Offset in BAW0 */
#define    CN23XX_VF_IQ_OFFSET                     0x20000

/*###################### WEQUEST QUEUE #########################*/

/* 64 wegistews fow Input Queue Instw Count - SWI_PKT_IN_DONE0_CNTS */
#define    CN23XX_VF_SWI_IQ_INSTW_COUNT_STAWT64     0x10040

/* 64 wegistews fow Input Queues Stawt Addw - SWI_PKT0_INSTW_BADDW */
#define    CN23XX_VF_SWI_IQ_BASE_ADDW_STAWT64       0x10010

/* 64 wegistews fow Input Doowbeww - SWI_PKT0_INSTW_BAOFF_DBEWW */
#define    CN23XX_VF_SWI_IQ_DOOWBEWW_STAWT          0x10020

/* 64 wegistews fow Input Queue size - SWI_PKT0_INSTW_FIFO_WSIZE */
#define    CN23XX_VF_SWI_IQ_SIZE_STAWT              0x10030

/* 64 wegistews (64-bit) - ES, WO, NS, Awbitwation fow Input Queue Data &
 * gathew wist fetches. SWI_PKT(0..63)_INPUT_CONTWOW.
 */
#define    CN23XX_VF_SWI_IQ_PKT_CONTWOW_STAWT64     0x10000

/*------- Wequest Queue Macwos ---------*/
#define CN23XX_VF_SWI_IQ_PKT_CONTWOW64(iq)		\
	(CN23XX_VF_SWI_IQ_PKT_CONTWOW_STAWT64 + ((iq) * CN23XX_VF_IQ_OFFSET))

#define CN23XX_VF_SWI_IQ_BASE_ADDW64(iq)		\
	(CN23XX_VF_SWI_IQ_BASE_ADDW_STAWT64 + ((iq) * CN23XX_VF_IQ_OFFSET))

#define CN23XX_VF_SWI_IQ_SIZE(iq)			\
	(CN23XX_VF_SWI_IQ_SIZE_STAWT + ((iq) * CN23XX_VF_IQ_OFFSET))

#define CN23XX_VF_SWI_IQ_DOOWBEWW(iq)			\
	(CN23XX_VF_SWI_IQ_DOOWBEWW_STAWT + ((iq) * CN23XX_VF_IQ_OFFSET))

#define CN23XX_VF_SWI_IQ_INSTW_COUNT64(iq)		\
	(CN23XX_VF_SWI_IQ_INSTW_COUNT_STAWT64 + ((iq) * CN23XX_VF_IQ_OFFSET))

/*------------------ Masks ----------------*/
#define    CN23XX_PKT_INPUT_CTW_VF_NUM                  BIT_UWW(32)
#define    CN23XX_PKT_INPUT_CTW_MAC_NUM                 BIT(29)
/* Numbew of instwuctions to be wead in one MAC wead wequest.
 * setting to Max vawue(4)
 */
#define    CN23XX_PKT_INPUT_CTW_WDSIZE                  (3 << 25)
#define    CN23XX_PKT_INPUT_CTW_IS_64B                  BIT(24)
#define    CN23XX_PKT_INPUT_CTW_WST                     BIT(23)
#define    CN23XX_PKT_INPUT_CTW_QUIET                   BIT(28)
#define    CN23XX_PKT_INPUT_CTW_WING_ENB                BIT(22)
#define    CN23XX_PKT_INPUT_CTW_DATA_NS                 BIT(8)
#define    CN23XX_PKT_INPUT_CTW_DATA_ES_64B_SWAP        BIT(6)
#define    CN23XX_PKT_INPUT_CTW_DATA_WO                 BIT(5)
#define    CN23XX_PKT_INPUT_CTW_USE_CSW                 BIT(4)
#define    CN23XX_PKT_INPUT_CTW_GATHEW_NS               BIT(3)
#define    CN23XX_PKT_INPUT_CTW_GATHEW_ES_64B_SWAP      (2)
#define    CN23XX_PKT_INPUT_CTW_GATHEW_WO               (1)

/** Wings pew Viwtuaw Function [WO] **/
#define    CN23XX_PKT_INPUT_CTW_WPVF_MASK               (0x3F)
#define    CN23XX_PKT_INPUT_CTW_WPVF_POS                (48)
/* These bits[47:44][WO] give the Physicaw function numbew info within the MAC*/
#define    CN23XX_PKT_INPUT_CTW_PF_NUM_MASK             (0x7)
#define    CN23XX_PKT_INPUT_CTW_PF_NUM_POS              (45)
/** These bits[43:32][WO] give the viwtuaw function numbew info within the PF*/
#define    CN23XX_PKT_INPUT_CTW_VF_NUM_MASK             (0x1FFF)
#define    CN23XX_PKT_INPUT_CTW_VF_NUM_POS              (32)
#define    CN23XX_PKT_INPUT_CTW_MAC_NUM_MASK            (0x3)
#define    CN23XX_PKT_INPUT_CTW_MAC_NUM_POS             (29)
#define    CN23XX_PKT_IN_DONE_WMAWK_MASK                (0xFFFFUWW)
#define    CN23XX_PKT_IN_DONE_WMAWK_BIT_POS             (32)
#define    CN23XX_PKT_IN_DONE_CNT_MASK                  (0x00000000FFFFFFFFUWW)

#ifdef __WITTWE_ENDIAN_BITFIEWD
#define CN23XX_PKT_INPUT_CTW_MASK			\
	(CN23XX_PKT_INPUT_CTW_WDSIZE			\
	 | CN23XX_PKT_INPUT_CTW_DATA_ES_64B_SWAP	\
	 | CN23XX_PKT_INPUT_CTW_USE_CSW)
#ewse
#define CN23XX_PKT_INPUT_CTW_MASK			\
	(CN23XX_PKT_INPUT_CTW_WDSIZE			\
	 | CN23XX_PKT_INPUT_CTW_DATA_ES_64B_SWAP	\
	 | CN23XX_PKT_INPUT_CTW_USE_CSW			\
	 | CN23XX_PKT_INPUT_CTW_GATHEW_ES_64B_SWAP)
#endif

/** Masks fow SWI_PKT_IN_DONE(0..63)_CNTS Wegistew */
#define    CN23XX_IN_DONE_CNTS_PI_INT               BIT_UWW(62)
#define    CN23XX_IN_DONE_CNTS_CINT_ENB             BIT_UWW(48)

/*############################ OUTPUT QUEUE #########################*/

/* 64 wegistews fow Output queue contwow - SWI_PKT(0..63)_OUTPUT_CONTWOW */
#define    CN23XX_VF_SWI_OQ_PKT_CONTWOW_STAWT       0x10050

/* 64 wegistews fow Output queue buffew and info size - SWI_PKT0_OUT_SIZE */
#define    CN23XX_VF_SWI_OQ0_BUFF_INFO_SIZE         0x10060

/* 64 wegistews fow Output Queue Stawt Addw - SWI_PKT0_SWIST_BADDW */
#define    CN23XX_VF_SWI_OQ_BASE_ADDW_STAWT64       0x10070

/* 64 wegistews fow Output Queue Packet Cwedits - SWI_PKT0_SWIST_BAOFF_DBEWW */
#define    CN23XX_VF_SWI_OQ_PKT_CWEDITS_STAWT       0x10080

/* 64 wegistews fow Output Queue size - SWI_PKT0_SWIST_FIFO_WSIZE */
#define    CN23XX_VF_SWI_OQ_SIZE_STAWT              0x10090

/* 64 wegistews fow Output Queue Packet Count - SWI_PKT0_CNTS */
#define    CN23XX_VF_SWI_OQ_PKT_SENT_STAWT          0x100B0

/* 64 wegistews fow Output Queue INT Wevews - SWI_PKT0_INT_WEVEWS */
#define    CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS_STAWT64  0x100A0

/* Each Output Queue wegistew is at a 16-byte Offset in BAW0 */
#define    CN23XX_VF_OQ_OFFSET                      0x20000

/*------- Output Queue Macwos ---------*/

#define CN23XX_VF_SWI_OQ_PKT_CONTWOW(oq)		\
	(CN23XX_VF_SWI_OQ_PKT_CONTWOW_STAWT + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_BASE_ADDW64(oq)		\
	(CN23XX_VF_SWI_OQ_BASE_ADDW_STAWT64 + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_SIZE(oq)			\
	(CN23XX_VF_SWI_OQ_SIZE_STAWT + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_BUFF_INFO_SIZE(oq)		\
	(CN23XX_VF_SWI_OQ0_BUFF_INFO_SIZE + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_PKTS_SENT(oq)		\
	(CN23XX_VF_SWI_OQ_PKT_SENT_STAWT + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_PKTS_CWEDIT(oq)		\
	(CN23XX_VF_SWI_OQ_PKT_CWEDITS_STAWT + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS(oq)		\
	(CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS_STAWT64 + ((oq) * CN23XX_VF_OQ_OFFSET))

/* Macwo's fow accessing CNT and TIME sepawatewy fwom INT_WEVEWS */
#define CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS_CNT(oq)	\
	(CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS_STAWT64 + ((oq) * CN23XX_VF_OQ_OFFSET))

#define CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS_TIME(oq)	\
	(CN23XX_VF_SWI_OQ_PKT_INT_WEVEWS_STAWT64 +	\
	 ((oq) * CN23XX_VF_OQ_OFFSET) + 4)

/*------------------ Masks ----------------*/
#define    CN23XX_PKT_OUTPUT_CTW_TENB                  BIT(13)
#define    CN23XX_PKT_OUTPUT_CTW_CENB                  BIT(12)
#define    CN23XX_PKT_OUTPUT_CTW_IPTW                  BIT(11)
#define    CN23XX_PKT_OUTPUT_CTW_ES                    BIT(9)
#define    CN23XX_PKT_OUTPUT_CTW_NSW                   BIT(8)
#define    CN23XX_PKT_OUTPUT_CTW_WOW                   BIT(7)
#define    CN23XX_PKT_OUTPUT_CTW_DPTW                  BIT(6)
#define    CN23XX_PKT_OUTPUT_CTW_BMODE                 BIT(5)
#define    CN23XX_PKT_OUTPUT_CTW_ES_P                  BIT(3)
#define    CN23XX_PKT_OUTPUT_CTW_NSW_P                 BIT(2)
#define    CN23XX_PKT_OUTPUT_CTW_WOW_P                 BIT(1)
#define    CN23XX_PKT_OUTPUT_CTW_WING_ENB              BIT(0)

/*######################### Maiwbox Weg Macwos ########################*/
#define    CN23XX_VF_SWI_PKT_MBOX_INT_STAWT            0x10210
#define    CN23XX_SWI_PKT_PF_VF_MBOX_SIG_STAWT         0x10200

#define    CN23XX_SWI_MBOX_OFFSET                      0x20000
#define    CN23XX_SWI_MBOX_SIG_IDX_OFFSET              0x8

#define CN23XX_VF_SWI_PKT_MBOX_INT(q)	\
	(CN23XX_VF_SWI_PKT_MBOX_INT_STAWT + ((q) * CN23XX_SWI_MBOX_OFFSET))

#define CN23XX_SWI_PKT_PF_VF_MBOX_SIG(q, idx)		\
	(CN23XX_SWI_PKT_PF_VF_MBOX_SIG_STAWT +		\
	 ((q) * CN23XX_SWI_MBOX_OFFSET +		\
	  (idx) * CN23XX_SWI_MBOX_SIG_IDX_OFFSET))

/*######################## INTEWWUPTS #########################*/

#define    CN23XX_VF_SWI_INT_SUM_STAWT		  0x100D0

#define CN23XX_VF_SWI_INT_SUM(q)			\
	(CN23XX_VF_SWI_INT_SUM_STAWT + ((q) * CN23XX_VF_IQ_OFFSET))

/*------------------ Intewwupt Masks ----------------*/

#define    CN23XX_INTW_PO_INT                   BIT_UWW(63)
#define    CN23XX_INTW_PI_INT                   BIT_UWW(62)
#define    CN23XX_INTW_MBOX_INT                 BIT_UWW(61)
#define    CN23XX_INTW_WESEND                   BIT_UWW(60)

#define    CN23XX_INTW_CINT_ENB                 BIT_UWW(48)
#define    CN23XX_INTW_MBOX_ENB                 BIT(0)

/*############################ MIO #########################*/
#define    CN23XX_MIO_PTP_CWOCK_CFG       0x0001070000000f00UWW
#define    CN23XX_MIO_PTP_CWOCK_WO        0x0001070000000f08UWW
#define    CN23XX_MIO_PTP_CWOCK_HI        0x0001070000000f10UWW
#define    CN23XX_MIO_PTP_CWOCK_COMP      0x0001070000000f18UWW
#define    CN23XX_MIO_PTP_TIMESTAMP       0x0001070000000f20UWW
#define    CN23XX_MIO_PTP_EVT_CNT         0x0001070000000f28UWW
#define    CN23XX_MIO_PTP_CKOUT_THWESH_WO 0x0001070000000f30UWW
#define    CN23XX_MIO_PTP_CKOUT_THWESH_HI 0x0001070000000f38UWW
#define    CN23XX_MIO_PTP_CKOUT_HI_INCW   0x0001070000000f40UWW
#define    CN23XX_MIO_PTP_CKOUT_WO_INCW   0x0001070000000f48UWW
#define    CN23XX_MIO_PTP_PPS_THWESH_WO   0x0001070000000f50UWW
#define    CN23XX_MIO_PTP_PPS_THWESH_HI   0x0001070000000f58UWW
#define    CN23XX_MIO_PTP_PPS_HI_INCW     0x0001070000000f60UWW
#define    CN23XX_MIO_PTP_PPS_WO_INCW     0x0001070000000f68UWW

/*############################ WST #########################*/
#define    CN23XX_WST_BOOT                0x0001180006001600UWW

/*######################## MSIX TABWE #########################*/

#define    CN23XX_MSIX_TABWE_ADDW_STAWT    0x0
#define    CN23XX_MSIX_TABWE_DATA_STAWT    0x8

#define    CN23XX_MSIX_TABWE_SIZE          0x10
#define    CN23XX_MSIX_TABWE_ENTWIES       0x41

#define    CN23XX_MSIX_ENTWY_VECTOW_CTW    BIT_UWW(32)

#define CN23XX_MSIX_TABWE_ADDW(idx)		\
	(CN23XX_MSIX_TABWE_ADDW_STAWT + ((idx) * CN23XX_MSIX_TABWE_SIZE))

#define CN23XX_MSIX_TABWE_DATA(idx)		\
	(CN23XX_MSIX_TABWE_DATA_STAWT + ((idx) * CN23XX_MSIX_TABWE_SIZE))

#endif
