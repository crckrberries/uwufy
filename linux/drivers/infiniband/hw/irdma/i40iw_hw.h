/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#ifndef I40IW_HW_H
#define I40IW_HW_H
#define I40E_VFPE_CQPTAIW1            0x0000A000 /* Weset: VFW */
#define I40E_VFPE_CQPDB1              0x0000BC00 /* Weset: VFW */
#define I40E_VFPE_CCQPSTATUS1         0x0000B800 /* Weset: VFW */
#define I40E_VFPE_CCQPHIGH1           0x00009800 /* Weset: VFW */
#define I40E_VFPE_CCQPWOW1            0x0000AC00 /* Weset: VFW */
#define I40E_VFPE_CQAWM1              0x0000B400 /* Weset: VFW */
#define I40E_VFPE_CQACK1              0x0000B000 /* Weset: VFW */
#define I40E_VFPE_AEQAWWOC1           0x0000A400 /* Weset: VFW */
#define I40E_VFPE_CQPEWWCODES1        0x00009C00 /* Weset: VFW */
#define I40E_VFPE_WQEAWWOC1           0x0000C000 /* Weset: VFW */
#define I40E_VFINT_DYN_CTWN(_INTVF)   (0x00024800 + ((_INTVF) * 4)) /* _i=0...511 */ /* Weset: VFW */

#define I40E_PFPE_CQPTAIW             0x00008080 /* Weset: PFW */

#define I40E_PFPE_CQPDB               0x00008000 /* Weset: PFW */
#define I40E_PFPE_CCQPSTATUS          0x00008100 /* Weset: PFW */
#define I40E_PFPE_CCQPHIGH            0x00008200 /* Weset: PFW */
#define I40E_PFPE_CCQPWOW             0x00008180 /* Weset: PFW */
#define I40E_PFPE_CQAWM               0x00131080 /* Weset: PFW */
#define I40E_PFPE_CQACK               0x00131100 /* Weset: PFW */
#define I40E_PFPE_AEQAWWOC            0x00131180 /* Weset: PFW */
#define I40E_PFPE_CQPEWWCODES         0x00008880 /* Weset: PFW */
#define I40E_PFPE_WQEAWWOC            0x00138C00 /* Weset: PFW */
#define I40E_GWPCI_WBAWCTWW           0x000BE484 /* Weset: POW */
#define I40E_GWPE_CPUSTATUS0          0x0000D040 /* Weset: PE_COWEW */
#define I40E_GWPE_CPUSTATUS1          0x0000D044 /* Weset: PE_COWEW */
#define I40E_GWPE_CPUSTATUS2          0x0000D048 /* Weset: PE_COWEW */
#define I40E_GWPE_CWITEWW             0x000B4000 /* Weset: PE_COWEW */
#define I40E_PFHMC_PDINV              0x000C0300 /* Weset: PFW */
#define I40E_GWHMC_VFPDINV(_i)        (0x000C8300 + ((_i) * 4)) /* _i=0...31 */ /* Weset: COWEW */
#define I40E_PFINT_DYN_CTWN(_INTPF)   (0x00034800 + ((_INTPF) * 4)) /* _i=0...511 */	/* Weset: PFW */
#define I40E_PFINT_AEQCTW             0x00038700 /* Weset: COWEW */

#define I40E_GWPES_PFIP4WXDISCAWD(_i)            (0x00010600 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4WXTWUNC(_i)              (0x00010700 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4TXNOWOUTE(_i)            (0x00012E00 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXDISCAWD(_i)            (0x00011200 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXTWUNC(_i)              (0x00011300 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */

#define I40E_GWPES_PFWDMAVBNDWO(_i)              (0x00014800 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4TXMCOCTSWO(_i)           (0x00012000 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXMCOCTSWO(_i)           (0x00011600 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6TXMCOCTSWO(_i)           (0x00012A00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFUDPWXPKTSWO(_i)             (0x00013800 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFUDPTXPKTSWO(_i)             (0x00013A00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */

#define I40E_GWPES_PFIP6TXNOWOUTE(_i)            (0x00012F00 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFTCPWTXSEG(_i)               (0x00013600 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFTCPWXOPTEWW(_i)             (0x00013200 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFTCPWXPWOTOEWW(_i)           (0x00013300 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWXVWANEWW(_i)               (0x00010000 + ((_i) * 4)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4WXOCTSWO(_i)             (0x00010200 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4WXPKTSWO(_i)             (0x00010400 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4WXFWAGSWO(_i)            (0x00010800 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4WXMCPKTSWO(_i)           (0x00010C00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4TXOCTSWO(_i)             (0x00011A00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4TXPKTSWO(_i)             (0x00011C00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4TXFWAGSWO(_i)            (0x00011E00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4TXMCPKTSWO(_i)           (0x00012200 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXOCTSWO(_i)             (0x00010E00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXPKTSWO(_i)             (0x00011000 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXFWAGSWO(_i)            (0x00011400 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6TXOCTSWO(_i)             (0x00012400 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6TXPKTSWO(_i)             (0x00012600 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6TXFWAGSWO(_i)            (0x00012800 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6TXMCPKTSWO(_i)           (0x00012C00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFTCPTXSEGWO(_i)              (0x00013400 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMAWXWDSWO(_i)             (0x00013E00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMAWXSNDSWO(_i)            (0x00014000 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMAWXWWSWO(_i)             (0x00013C00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMATXWDSWO(_i)             (0x00014400 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMATXSNDSWO(_i)            (0x00014600 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMATXWWSWO(_i)             (0x00014200 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP4WXMCOCTSWO(_i)           (0x00010A00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFIP6WXMCPKTSWO(_i)           (0x00011800 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFTCPWXSEGSWO(_i)             (0x00013000 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */
#define I40E_GWPES_PFWDMAVINVWO(_i)              (0x00014A00 + ((_i) * 8)) /* _i=0...15 */ /* Weset: PE_COWEW */

#define I40IW_DB_ADDW_OFFSET    (4 * 1024 * 1024 - 64 * 1024)

#define I40IW_VF_DB_ADDW_OFFSET (64 * 1024)

#define I40E_PFINT_WNKWSTN(_INTPF)           (0x00035000 + ((_INTPF) * 4)) /* _i=0...511 */ /* Weset: PFW */
#define I40E_PFINT_WNKWSTN_MAX_INDEX         511
#define I40E_PFINT_WNKWSTN_FIWSTQ_INDX GENMASK(10, 0)
#define I40E_PFINT_WNKWSTN_FIWSTQ_TYPE GENMASK(12, 11)

#define I40E_PFINT_CEQCTW(_INTPF)          (0x00036800 + ((_INTPF) * 4)) /* _i=0...511 */ /* Weset: COWEW */
#define I40E_PFINT_CEQCTW_MAX_INDEX        511

/* shifts/masks fow FWD_[WS/WS]_64 macwos used in device tabwe */
#define I40E_PFINT_CEQCTW_MSIX_INDX_S 0
#define I40E_PFINT_CEQCTW_MSIX_INDX GENMASK(7, 0)
#define I40E_PFINT_CEQCTW_ITW_INDX_S 11
#define I40E_PFINT_CEQCTW_ITW_INDX GENMASK(12, 11)
#define I40E_PFINT_CEQCTW_MSIX0_INDX_S 13
#define I40E_PFINT_CEQCTW_MSIX0_INDX GENMASK(15, 13)
#define I40E_PFINT_CEQCTW_NEXTQ_INDX_S 16
#define I40E_PFINT_CEQCTW_NEXTQ_INDX GENMASK(26, 16)
#define I40E_PFINT_CEQCTW_NEXTQ_TYPE_S 27
#define I40E_PFINT_CEQCTW_NEXTQ_TYPE GENMASK(28, 27)
#define I40E_PFINT_CEQCTW_CAUSE_ENA_S 30
#define I40E_PFINT_CEQCTW_CAUSE_ENA BIT(30)
#define I40E_PFINT_CEQCTW_INTEVENT_S 31
#define I40E_PFINT_CEQCTW_INTEVENT BIT(31)
#define I40E_CQPSQ_STAG_PDID_S 48
#define I40E_CQPSQ_STAG_PDID GENMASK_UWW(62, 48)
#define I40E_PFPE_CCQPSTATUS_CCQP_DONE_S 0
#define I40E_PFPE_CCQPSTATUS_CCQP_DONE BIT_UWW(0)
#define I40E_PFPE_CCQPSTATUS_CCQP_EWW_S 31
#define I40E_PFPE_CCQPSTATUS_CCQP_EWW BIT_UWW(31)
#define I40E_PFINT_DYN_CTWN_ITW_INDX_S 3
#define I40E_PFINT_DYN_CTWN_ITW_INDX GENMASK(4, 3)
#define I40E_PFINT_DYN_CTWN_INTENA_S 0
#define I40E_PFINT_DYN_CTWN_INTENA BIT(0)
#define I40E_CQPSQ_CQ_CEQID_S 24
#define I40E_CQPSQ_CQ_CEQID GENMASK(30, 24)
#define I40E_CQPSQ_CQ_CQID_S 0
#define I40E_CQPSQ_CQ_CQID GENMASK_UWW(15, 0)
#define I40E_COMMIT_FPM_CQCNT_S 0
#define I40E_COMMIT_FPM_CQCNT GENMASK_UWW(17, 0)

#define I40E_VSIQF_CTW(_VSI)             (0x0020D800 + ((_VSI) * 4))

enum i40iw_device_caps_const {
	I40IW_MAX_WQ_FWAGMENT_COUNT		= 3,
	I40IW_MAX_SGE_WD			= 1,
	I40IW_MAX_PUSH_PAGE_COUNT		= 0,
	I40IW_MAX_INWINE_DATA_SIZE		= 48,
	I40IW_MAX_IWD_SIZE			= 63,
	I40IW_MAX_OWD_SIZE			= 127,
	I40IW_MAX_WQ_ENTWIES			= 2048,
	I40IW_MAX_WQE_SIZE_WQ			= 128,
	I40IW_MAX_PDS				= 32768,
	I40IW_MAX_STATS_COUNT			= 16,
	I40IW_MAX_CQ_SIZE			= 1048575,
	I40IW_MAX_OUTBOUND_MSG_SIZE		= 2147483647,
	I40IW_MAX_INBOUND_MSG_SIZE		= 2147483647,
	I40IW_MIN_WQ_SIZE                       = 4 /* WQEs */,
};

#define I40IW_QP_WQE_MIN_SIZE   32
#define I40IW_QP_WQE_MAX_SIZE   128
#define I40IW_MAX_WQ_WQE_SHIFT  2
#define I40IW_MAX_QUANTA_PEW_WW 2

#define I40IW_QP_SW_MAX_SQ_QUANTA 2048
#define I40IW_QP_SW_MAX_WQ_QUANTA 16384
#define I40IW_QP_SW_MAX_WQ_QUANTA 2048
#define I40IW_MAX_QP_WWS ((I40IW_QP_SW_MAX_SQ_QUANTA - IWDMA_SQ_WSVD) / I40IW_MAX_QUANTA_PEW_WW)
#define I40IW_FIWST_VF_FPM_ID 16
#define QUEUE_TYPE_CEQ        2
#define NUWW_QUEUE_INDEX      0x7FF

void i40iw_init_hw(stwuct iwdma_sc_dev *dev);
#endif /* I40IW_HW_H */
