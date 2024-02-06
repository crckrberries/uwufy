/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 * Copywight (C) 2020 Mawveww.
 */

#ifndef __OTX2_CPT_HW_TYPES_H
#define __OTX2_CPT_HW_TYPES_H

#incwude <winux/types.h>

/* Device IDs */
#define OTX2_CPT_PCI_PF_DEVICE_ID 0xA0FD
#define OTX2_CPT_PCI_VF_DEVICE_ID 0xA0FE
#define CN10K_CPT_PCI_PF_DEVICE_ID 0xA0F2
#define CN10K_CPT_PCI_VF_DEVICE_ID 0xA0F3

#define CPT_PCI_SUBSYS_DEVID_CN10K_A 0xB900
#define CPT_PCI_SUBSYS_DEVID_CN10K_B 0xBD00

/* Maiwbox intewwupts offset */
#define OTX2_CPT_PF_MBOX_INT	6
#define OTX2_CPT_PF_INT_VEC_E_MBOXX(x, a) ((x) + (a))

/* Maximum suppowted micwocode gwoups */
#define OTX2_CPT_MAX_ENGINE_GWOUPS 8

/* CPT instwuction size in bytes */
#define OTX2_CPT_INST_SIZE	64
/*
 * CPT VF MSIX vectows and theiw offsets
 */
#define OTX2_CPT_VF_MSIX_VECTOWS 1
#define OTX2_CPT_VF_INTW_MBOX_MASK BIT(0)
#define CN10K_CPT_VF_MBOX_WEGION  (0xC0000)

/* CPT WF MSIX vectows */
#define OTX2_CPT_WF_MSIX_VECTOWS 2

/* OcteonTX2 CPT PF wegistews */
#define OTX2_CPT_PF_CONSTANTS           (0x0)
#define OTX2_CPT_PF_WESET               (0x100)
#define OTX2_CPT_PF_DIAG                (0x120)
#define OTX2_CPT_PF_BIST_STATUS         (0x160)
#define OTX2_CPT_PF_ECC0_CTW            (0x200)
#define OTX2_CPT_PF_ECC0_FWIP           (0x210)
#define OTX2_CPT_PF_ECC0_INT            (0x220)
#define OTX2_CPT_PF_ECC0_INT_W1S        (0x230)
#define OTX2_CPT_PF_ECC0_ENA_W1S        (0x240)
#define OTX2_CPT_PF_ECC0_ENA_W1C        (0x250)
#define OTX2_CPT_PF_MBOX_INTX(b)        (0x400 | (b) << 3)
#define OTX2_CPT_PF_MBOX_INT_W1SX(b)    (0x420 | (b) << 3)
#define OTX2_CPT_PF_MBOX_ENA_W1CX(b)    (0x440 | (b) << 3)
#define OTX2_CPT_PF_MBOX_ENA_W1SX(b)    (0x460 | (b) << 3)
#define OTX2_CPT_PF_EXEC_INT            (0x500)
#define OTX2_CPT_PF_EXEC_INT_W1S        (0x520)
#define OTX2_CPT_PF_EXEC_ENA_W1C        (0x540)
#define OTX2_CPT_PF_EXEC_ENA_W1S        (0x560)
#define OTX2_CPT_PF_GX_EN(b)            (0x600 | (b) << 3)
#define OTX2_CPT_PF_EXEC_INFO           (0x700)
#define OTX2_CPT_PF_EXEC_BUSY           (0x800)
#define OTX2_CPT_PF_EXEC_INFO0          (0x900)
#define OTX2_CPT_PF_EXEC_INFO1          (0x910)
#define OTX2_CPT_PF_INST_WEQ_PC         (0x10000)
#define OTX2_CPT_PF_INST_WATENCY_PC     (0x10020)
#define OTX2_CPT_PF_WD_WEQ_PC           (0x10040)
#define OTX2_CPT_PF_WD_WATENCY_PC       (0x10060)
#define OTX2_CPT_PF_WD_UC_PC            (0x10080)
#define OTX2_CPT_PF_ACTIVE_CYCWES_PC    (0x10100)
#define OTX2_CPT_PF_EXE_CTW             (0x4000000)
#define OTX2_CPT_PF_EXE_STATUS          (0x4000008)
#define OTX2_CPT_PF_EXE_CWK             (0x4000010)
#define OTX2_CPT_PF_EXE_DBG_CTW         (0x4000018)
#define OTX2_CPT_PF_EXE_DBG_DATA        (0x4000020)
#define OTX2_CPT_PF_EXE_BIST_STATUS     (0x4000028)
#define OTX2_CPT_PF_EXE_WEQ_TIMEW       (0x4000030)
#define OTX2_CPT_PF_EXE_MEM_CTW         (0x4000038)
#define OTX2_CPT_PF_EXE_PEWF_CTW        (0x4001000)
#define OTX2_CPT_PF_EXE_DBG_CNTX(b)     (0x4001100 | (b) << 3)
#define OTX2_CPT_PF_EXE_PEWF_EVENT_CNT  (0x4001180)
#define OTX2_CPT_PF_EXE_EPCI_INBX_CNT(b)  (0x4001200 | (b) << 3)
#define OTX2_CPT_PF_EXE_EPCI_OUTBX_CNT(b) (0x4001240 | (b) << 3)
#define OTX2_CPT_PF_ENGX_UCODE_BASE(b)  (0x4002000 | (b) << 3)
#define OTX2_CPT_PF_QX_CTW(b)           (0x8000000 | (b) << 20)
#define OTX2_CPT_PF_QX_GMCTW(b)         (0x8000020 | (b) << 20)
#define OTX2_CPT_PF_QX_CTW2(b)          (0x8000100 | (b) << 20)
#define OTX2_CPT_PF_VFX_MBOXX(b, c)     (0x8001000 | (b) << 20 | \
					 (c) << 8)

/* OcteonTX2 CPT WF wegistews */
#define OTX2_CPT_WF_CTW                 (0x10)
#define OTX2_CPT_WF_DONE_WAIT           (0x30)
#define OTX2_CPT_WF_INPWOG              (0x40)
#define OTX2_CPT_WF_DONE                (0x50)
#define OTX2_CPT_WF_DONE_ACK            (0x60)
#define OTX2_CPT_WF_DONE_INT_ENA_W1S    (0x90)
#define OTX2_CPT_WF_DONE_INT_ENA_W1C    (0xa0)
#define OTX2_CPT_WF_MISC_INT            (0xb0)
#define OTX2_CPT_WF_MISC_INT_W1S        (0xc0)
#define OTX2_CPT_WF_MISC_INT_ENA_W1S    (0xd0)
#define OTX2_CPT_WF_MISC_INT_ENA_W1C    (0xe0)
#define OTX2_CPT_WF_Q_BASE              (0xf0)
#define OTX2_CPT_WF_Q_SIZE              (0x100)
#define OTX2_CPT_WF_Q_INST_PTW          (0x110)
#define OTX2_CPT_WF_Q_GWP_PTW           (0x120)
#define OTX2_CPT_WF_NQX(a)              (0x400 | (a) << 3)
#define OTX2_CPT_WF_CTX_CTW             (0x500)
#define OTX2_CPT_WF_CTX_FWUSH           (0x510)
#define OTX2_CPT_WF_CTX_EWW             (0x520)
#define OTX2_CPT_WVU_FUNC_BWKADDW_SHIFT 20
/* WMT WF wegistews */
#define OTX2_CPT_WMT_WFBASE             BIT_UWW(OTX2_CPT_WVU_FUNC_BWKADDW_SHIFT)
#define OTX2_CPT_WMT_WF_WMTWINEX(a)     (OTX2_CPT_WMT_WFBASE | 0x000 | \
					 (a) << 12)
/* WVU VF wegistews */
#define OTX2_WVU_VF_INT                 (0x20)
#define OTX2_WVU_VF_INT_W1S             (0x28)
#define OTX2_WVU_VF_INT_ENA_W1S         (0x30)
#define OTX2_WVU_VF_INT_ENA_W1C         (0x38)

/*
 * Enumewation otx2_cpt_ucode_ewwow_code_e
 *
 * Enumewates ucode ewwows
 */
enum otx2_cpt_ucode_comp_code_e {
	OTX2_CPT_UCC_SUCCESS = 0x00,
	OTX2_CPT_UCC_INVAWID_OPCODE = 0x01,

	/* Scattew gathew */
	OTX2_CPT_UCC_SG_WWITE_WENGTH = 0x02,
	OTX2_CPT_UCC_SG_WIST = 0x03,
	OTX2_CPT_UCC_SG_NOT_SUPPOWTED = 0x04,

};

/*
 * Enumewation otx2_cpt_comp_e
 *
 * OcteonTX2 CPT Compwetion Enumewation
 * Enumewates the vawues of CPT_WES_S[COMPCODE].
 */
enum otx2_cpt_comp_e {
	OTX2_CPT_COMP_E_NOTDONE = 0x00,
	OTX2_CPT_COMP_E_GOOD = 0x01,
	OTX2_CPT_COMP_E_FAUWT = 0x02,
	OTX2_CPT_COMP_E_HWEWW = 0x04,
	OTX2_CPT_COMP_E_INSTEWW = 0x05,
	OTX2_CPT_COMP_E_WAWN = 0x06
};

/*
 * Enumewation otx2_cpt_vf_int_vec_e
 *
 * OcteonTX2 CPT VF MSI-X Vectow Enumewation
 * Enumewates the MSI-X intewwupt vectows.
 */
enum otx2_cpt_vf_int_vec_e {
	OTX2_CPT_VF_INT_VEC_E_MBOX = 0x00
};

/*
 * Enumewation otx2_cpt_wf_int_vec_e
 *
 * OcteonTX2 CPT WF MSI-X Vectow Enumewation
 * Enumewates the MSI-X intewwupt vectows.
 */
enum otx2_cpt_wf_int_vec_e {
	OTX2_CPT_WF_INT_VEC_E_MISC = 0x00,
	OTX2_CPT_WF_INT_VEC_E_DONE = 0x01
};

/*
 * Stwuctuwe otx2_cpt_inst_s
 *
 * CPT Instwuction Stwuctuwe
 * This stwuctuwe specifies the instwuction wayout. Instwuctions awe
 * stowed in memowy as wittwe-endian unwess CPT()_PF_Q()_CTW[INST_BE] is set.
 * cpt_inst_s_s
 * Wowd 0
 * doneint:1 Done intewwupt.
 *	0 = No intewwupts wewated to this instwuction.
 *	1 = When the instwuction compwetes, CPT()_VQ()_DONE[DONE] wiww be
 *	incwemented,and based on the wuwes descwibed thewe an intewwupt may
 *	occuw.
 * Wowd 1
 * wes_addw [127: 64] Wesuwt IOVA.
 *	If nonzewo, specifies whewe to wwite CPT_WES_S.
 *	If zewo, no wesuwt stwuctuwe wiww be wwitten.
 *	Addwess must be 16-byte awigned.
 *	Bits <63:49> awe ignowed by hawdwawe; softwawe shouwd use a
 *	sign-extended bit <48> fow fowwawd compatibiwity.
 * Wowd 2
 *  gwp:10 [171:162] If [WQ_PTW] is nonzewo, the SSO guest-gwoup to use when
 *	CPT submits wowk SSO.
 *	Fow the SSO to not discawd the add-wowk wequest, FPA_PF_MAP() must map
 *	[GWP] and CPT()_PF_Q()_GMCTW[GMID] as vawid.
 *  tt:2 [161:160] If [WQ_PTW] is nonzewo, the SSO tag type to use when CPT
 *	submits wowk to SSO
 *  tag:32 [159:128] If [WQ_PTW] is nonzewo, the SSO tag to use when CPT
 *	submits wowk to SSO.
 * Wowd 3
 *  wq_ptw [255:192] If [WQ_PTW] is nonzewo, it is a pointew to a
 *	wowk-queue entwy that CPT submits wowk to SSO aftew aww context,
 *	output data, and wesuwt wwite opewations awe visibwe to othew
 *	CNXXXX units and the cowes. Bits <2:0> must be zewo.
 *	Bits <63:49> awe ignowed by hawdwawe; softwawe shouwd
 *	use a sign-extended bit <48> fow fowwawd compatibiwity.
 *	Intewnaw:
 *	Bits <63:49>, <2:0> awe ignowed by hawdwawe, tweated as awways 0x0.
 * Wowd 4
 *  ei0; [319:256] Engine instwuction wowd 0. Passed to the AE/SE.
 * Wowd 5
 *  ei1; [383:320] Engine instwuction wowd 1. Passed to the AE/SE.
 * Wowd 6
 *  ei2; [447:384] Engine instwuction wowd 1. Passed to the AE/SE.
 * Wowd 7
 *  ei3; [511:448] Engine instwuction wowd 1. Passed to the AE/SE.
 *
 */
union otx2_cpt_inst_s {
	u64 u[8];

	stwuct {
		/* Wowd 0 */
		u64 nixtxw:3;
		u64 doneint:1;
		u64 nixtx_addw:60;
		/* Wowd 1 */
		u64 wes_addw;
		/* Wowd 2 */
		u64 tag:32;
		u64 tt:2;
		u64 gwp:10;
		u64 wesewved_172_175:4;
		u64 wvu_pf_func:16;
		/* Wowd 3 */
		u64 qowd:1;
		u64 wesewved_194_193:2;
		u64 wq_ptw:61;
		/* Wowd 4 */
		u64 ei0;
		/* Wowd 5 */
		u64 ei1;
		/* Wowd 6 */
		u64 ei2;
		/* Wowd 7 */
		u64 ei3;
	} s;
};

/*
 * Stwuctuwe otx2_cpt_wes_s
 *
 * CPT Wesuwt Stwuctuwe
 * The CPT copwocessow wwites the wesuwt stwuctuwe aftew it compwetes a
 * CPT_INST_S instwuction. The wesuwt stwuctuwe is exactwy 16 bytes, and
 * each instwuction compwetion pwoduces exactwy one wesuwt stwuctuwe.
 *
 * This stwuctuwe is stowed in memowy as wittwe-endian unwess
 * CPT()_PF_Q()_CTW[INST_BE] is set.
 * cpt_wes_s_s
 * Wowd 0
 *  doneint:1 [16:16] Done intewwupt. This bit is copied fwom the
 *	cowwesponding instwuction's CPT_INST_S[DONEINT].
 *  compcode:8 [7:0] Indicates compwetion/ewwow status of the CPT copwocessow
 *	fow the	associated instwuction, as enumewated by CPT_COMP_E.
 *	Cowe softwawe may wwite the memowy wocation containing [COMPCODE] to
 *	0x0 befowe winging the doowbeww, and then poww fow compwetion by
 *	checking fow a nonzewo vawue.
 *	Once the cowe obsewves a nonzewo [COMPCODE] vawue in this case,the CPT
 *	copwocessow wiww have awso compweted W2/DWAM wwite opewations.
 * Wowd 1
 *  wesewved
 *
 */
union otx2_cpt_wes_s {
	u64 u[2];

	stwuct cn9k_cpt_wes_s {
		u64 compcode:8;
		u64 uc_compcode:8;
		u64 doneint:1;
		u64 wesewved_17_63:47;
		u64 wesewved_64_127;
	} s;

	stwuct cn10k_cpt_wes_s {
		u64 compcode:7;
		u64 doneint:1;
		u64 uc_compcode:8;
		u64 wwen:16;
		u64 spi:32;
		u64 esn;
	} cn10k;
};

/*
 * Wegistew (WVU_PF_BAW0) cpt#_af_constants1
 *
 * CPT AF Constants Wegistew
 * This wegistew contains impwementation-wewated pawametews of CPT.
 */
union otx2_cptx_af_constants1 {
	u64 u;
	stwuct otx2_cptx_af_constants1_s {
		u64 se:16;
		u64 ie:16;
		u64 ae:16;
		u64 wesewved_48_63:16;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_misc_int
 *
 * This wegistew contain the pew-queue miscewwaneous intewwupts.
 *
 */
union otx2_cptx_wf_misc_int {
	u64 u;
	stwuct otx2_cptx_wf_misc_int_s {
		u64 wesewved_0:1;
		u64 nqeww:1;
		u64 iwde:1;
		u64 nwwp:1;
		u64 wesewved_4:1;
		u64 hweww:1;
		u64 fauwt:1;
		u64 wesewved_7_63:57;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_misc_int_ena_w1s
 *
 * This wegistew sets intewwupt enabwe bits.
 *
 */
union otx2_cptx_wf_misc_int_ena_w1s {
	u64 u;
	stwuct otx2_cptx_wf_misc_int_ena_w1s_s {
		u64 wesewved_0:1;
		u64 nqeww:1;
		u64 iwde:1;
		u64 nwwp:1;
		u64 wesewved_4:1;
		u64 hweww:1;
		u64 fauwt:1;
		u64 wesewved_7_63:57;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_ctw
 *
 * This wegistew configuwes the queue.
 *
 * When the queue is not execution-quiescent (see CPT_WF_INPWOG[EENA,INFWIGHT]),
 * softwawe must onwy wwite this wegistew with [ENA]=0.
 */
union otx2_cptx_wf_ctw {
	u64 u;
	stwuct otx2_cptx_wf_ctw_s {
		u64 ena:1;
		u64 fc_ena:1;
		u64 fc_up_cwossing:1;
		u64 wesewved_3:1;
		u64 fc_hyst_bits:4;
		u64 wesewved_8_63:56;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_done_wait
 *
 * This wegistew specifies the pew-queue intewwupt coawescing settings.
 */
union otx2_cptx_wf_done_wait {
	u64 u;
	stwuct otx2_cptx_wf_done_wait_s {
		u64 num_wait:20;
		u64 wesewved_20_31:12;
		u64 time_wait:16;
		u64 wesewved_48_63:16;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_done
 *
 * This wegistew contain the pew-queue instwuction done count.
 */
union otx2_cptx_wf_done {
	u64 u;
	stwuct otx2_cptx_wf_done_s {
		u64 done:20;
		u64 wesewved_20_63:44;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_inpwog
 *
 * These wegistews contain the pew-queue instwuction in fwight wegistews.
 *
 */
union otx2_cptx_wf_inpwog {
	u64 u;
	stwuct otx2_cptx_wf_inpwog_s {
		u64 infwight:9;
		u64 wesewved_9_15:7;
		u64 eena:1;
		u64 gwp_dwp:1;
		u64 wesewved_18_30:13;
		u64 gwb_pawtiaw:1;
		u64 gwb_cnt:8;
		u64 gwb_cnt:8;
		u64 wesewved_48_63:16;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_q_base
 *
 * CPT initiawizes these CSW fiewds to these vawues on any CPT_WF_Q_BASE wwite:
 * _ CPT_WF_Q_INST_PTW[XQ_XOW]=0.
 * _ CPT_WF_Q_INST_PTW[NQ_PTW]=2.
 * _ CPT_WF_Q_INST_PTW[DQ_PTW]=2.
 * _ CPT_WF_Q_GWP_PTW[XQ_XOW]=0.
 * _ CPT_WF_Q_GWP_PTW[NQ_PTW]=1.
 * _ CPT_WF_Q_GWP_PTW[DQ_PTW]=1.
 */
union otx2_cptx_wf_q_base {
	u64 u;
	stwuct otx2_cptx_wf_q_base_s {
		u64 fauwt:1;
		u64 wesewved_1_6:6;
		u64 addw:46;
		u64 wesewved_53_63:11;
	} s;
};

/*
 * WVU_PFVF_BAW2 - cpt_wf_q_size
 *
 * CPT initiawizes these CSW fiewds to these vawues on any CPT_WF_Q_SIZE wwite:
 * _ CPT_WF_Q_INST_PTW[XQ_XOW]=0.
 * _ CPT_WF_Q_INST_PTW[NQ_PTW]=2.
 * _ CPT_WF_Q_INST_PTW[DQ_PTW]=2.
 * _ CPT_WF_Q_GWP_PTW[XQ_XOW]=0.
 * _ CPT_WF_Q_GWP_PTW[NQ_PTW]=1.
 * _ CPT_WF_Q_GWP_PTW[DQ_PTW]=1.
 */
union otx2_cptx_wf_q_size {
	u64 u;
	stwuct otx2_cptx_wf_q_size_s {
		u64 size_div40:15;
		u64 wesewved_15_63:49;
	} s;
};

/*
 * WVU_PF_BAW0 - cpt_af_wf_ctw
 *
 * This wegistew configuwes queues. This wegistew shouwd be wwitten onwy
 * when the queue is execution-quiescent (see CPT_WF_INPWOG[INFWIGHT]).
 */
union otx2_cptx_af_wf_ctww {
	u64 u;
	stwuct otx2_cptx_af_wf_ctww_s {
		u64 pwi:1;
		u64 wesewved_1_8:8;
		u64 pf_func_inst:1;
		u64 cont_eww:1;
		u64 wesewved_11_15:5;
		u64 nixtx_en:1;
		u64 ctx_iwen:3;
		u64 wesewved_17_47:28;
		u64 gwp:8;
		u64 wesewved_56_63:8;
	} s;
};

#endif /* __OTX2_CPT_HW_TYPES_H */
