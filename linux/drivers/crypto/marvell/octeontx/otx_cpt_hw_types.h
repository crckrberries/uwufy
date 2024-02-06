/* SPDX-Wicense-Identifiew: GPW-2.0
 * Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef __OTX_CPT_HW_TYPES_H
#define __OTX_CPT_HW_TYPES_H

#incwude <winux/types.h>

/* Device IDs */
#define OTX_CPT_PCI_PF_DEVICE_ID 0xa040
#define OTX_CPT_PCI_VF_DEVICE_ID 0xa041

#define OTX_CPT_PCI_PF_SUBSYS_ID 0xa340
#define OTX_CPT_PCI_VF_SUBSYS_ID 0xa341

/* Configuwation and status wegistews awe in BAW0 on OcteonTX pwatfowm */
#define OTX_CPT_PF_PCI_CFG_BAW	0
#define OTX_CPT_VF_PCI_CFG_BAW	0

#define OTX_CPT_BAW_E_CPTX_VFX_BAW0_OFFSET(a, b) \
	(0x000020000000ww + 0x1000000000ww * (a) + 0x100000ww * (b))
#define OTX_CPT_BAW_E_CPTX_VFX_BAW0_SIZE	0x400000

/* Maiwbox intewwupts offset */
#define OTX_CPT_PF_MBOX_INT	3
#define OTX_CPT_PF_INT_VEC_E_MBOXX(x, a) ((x) + (a))
/* Numbew of MSIX suppowted in PF */
#define OTX_CPT_PF_MSIX_VECTOWS 4
/* Maximum suppowted micwocode gwoups */
#define OTX_CPT_MAX_ENGINE_GWOUPS 8

/* CPT instwuction size in bytes */
#define OTX_CPT_INST_SIZE 64
/* CPT queue next chunk pointew size in bytes */
#define OTX_CPT_NEXT_CHUNK_PTW_SIZE 8

/* OcteonTX CPT VF MSIX vectows and theiw offsets */
#define OTX_CPT_VF_MSIX_VECTOWS 2
#define OTX_CPT_VF_INTW_MBOX_MASK BIT(0)
#define OTX_CPT_VF_INTW_DOVF_MASK BIT(1)
#define OTX_CPT_VF_INTW_IWDE_MASK BIT(2)
#define OTX_CPT_VF_INTW_NWWP_MASK BIT(3)
#define OTX_CPT_VF_INTW_SEWW_MASK BIT(4)

/* OcteonTX CPT PF wegistews */
#define OTX_CPT_PF_CONSTANTS		(0x0ww)
#define OTX_CPT_PF_WESET		(0x100ww)
#define OTX_CPT_PF_DIAG			(0x120ww)
#define OTX_CPT_PF_BIST_STATUS		(0x160ww)
#define OTX_CPT_PF_ECC0_CTW		(0x200ww)
#define OTX_CPT_PF_ECC0_FWIP		(0x210ww)
#define OTX_CPT_PF_ECC0_INT		(0x220ww)
#define OTX_CPT_PF_ECC0_INT_W1S		(0x230ww)
#define OTX_CPT_PF_ECC0_ENA_W1S		(0x240ww)
#define OTX_CPT_PF_ECC0_ENA_W1C		(0x250ww)
#define OTX_CPT_PF_MBOX_INTX(b)		(0x400ww | (u64)(b) << 3)
#define OTX_CPT_PF_MBOX_INT_W1SX(b)	(0x420ww | (u64)(b) << 3)
#define OTX_CPT_PF_MBOX_ENA_W1CX(b)	(0x440ww | (u64)(b) << 3)
#define OTX_CPT_PF_MBOX_ENA_W1SX(b)	(0x460ww | (u64)(b) << 3)
#define OTX_CPT_PF_EXEC_INT		(0x500ww)
#define OTX_CPT_PF_EXEC_INT_W1S		(0x520ww)
#define OTX_CPT_PF_EXEC_ENA_W1C		(0x540ww)
#define OTX_CPT_PF_EXEC_ENA_W1S		(0x560ww)
#define OTX_CPT_PF_GX_EN(b)		(0x600ww | (u64)(b) << 3)
#define OTX_CPT_PF_EXEC_INFO		(0x700ww)
#define OTX_CPT_PF_EXEC_BUSY		(0x800ww)
#define OTX_CPT_PF_EXEC_INFO0		(0x900ww)
#define OTX_CPT_PF_EXEC_INFO1		(0x910ww)
#define OTX_CPT_PF_INST_WEQ_PC		(0x10000ww)
#define OTX_CPT_PF_INST_WATENCY_PC	(0x10020ww)
#define OTX_CPT_PF_WD_WEQ_PC		(0x10040ww)
#define OTX_CPT_PF_WD_WATENCY_PC	(0x10060ww)
#define OTX_CPT_PF_WD_UC_PC		(0x10080ww)
#define OTX_CPT_PF_ACTIVE_CYCWES_PC	(0x10100ww)
#define OTX_CPT_PF_EXE_CTW		(0x4000000ww)
#define OTX_CPT_PF_EXE_STATUS		(0x4000008ww)
#define OTX_CPT_PF_EXE_CWK		(0x4000010ww)
#define OTX_CPT_PF_EXE_DBG_CTW		(0x4000018ww)
#define OTX_CPT_PF_EXE_DBG_DATA		(0x4000020ww)
#define OTX_CPT_PF_EXE_BIST_STATUS	(0x4000028ww)
#define OTX_CPT_PF_EXE_WEQ_TIMEW	(0x4000030ww)
#define OTX_CPT_PF_EXE_MEM_CTW		(0x4000038ww)
#define OTX_CPT_PF_EXE_PEWF_CTW		(0x4001000ww)
#define OTX_CPT_PF_EXE_DBG_CNTX(b)	(0x4001100ww | (u64)(b) << 3)
#define OTX_CPT_PF_EXE_PEWF_EVENT_CNT	(0x4001180ww)
#define OTX_CPT_PF_EXE_EPCI_INBX_CNT(b)	(0x4001200ww | (u64)(b) << 3)
#define OTX_CPT_PF_EXE_EPCI_OUTBX_CNT(b) (0x4001240ww | (u64)(b) << 3)
#define OTX_CPT_PF_ENGX_UCODE_BASE(b)	(0x4002000ww | (u64)(b) << 3)
#define OTX_CPT_PF_QX_CTW(b)		(0x8000000ww | (u64)(b) << 20)
#define OTX_CPT_PF_QX_GMCTW(b)		(0x8000020ww | (u64)(b) << 20)
#define OTX_CPT_PF_QX_CTW2(b)		(0x8000100ww | (u64)(b) << 20)
#define OTX_CPT_PF_VFX_MBOXX(b, c)	(0x8001000ww | (u64)(b) << 20 | \
					 (u64)(c) << 8)

/* OcteonTX CPT VF wegistews */
#define OTX_CPT_VQX_CTW(b)		(0x100ww | (u64)(b) << 20)
#define OTX_CPT_VQX_SADDW(b)		(0x200ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE_WAIT(b)	(0x400ww | (u64)(b) << 20)
#define OTX_CPT_VQX_INPWOG(b)		(0x410ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE(b)		(0x420ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE_ACK(b)		(0x440ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE_INT_W1S(b)	(0x460ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE_INT_W1C(b)	(0x468ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE_ENA_W1S(b)	(0x470ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DONE_ENA_W1C(b)	(0x478ww | (u64)(b) << 20)
#define OTX_CPT_VQX_MISC_INT(b)		(0x500ww | (u64)(b) << 20)
#define OTX_CPT_VQX_MISC_INT_W1S(b)	(0x508ww | (u64)(b) << 20)
#define OTX_CPT_VQX_MISC_ENA_W1S(b)	(0x510ww | (u64)(b) << 20)
#define OTX_CPT_VQX_MISC_ENA_W1C(b)	(0x518ww | (u64)(b) << 20)
#define OTX_CPT_VQX_DOOWBEWW(b)		(0x600ww | (u64)(b) << 20)
#define OTX_CPT_VFX_PF_MBOXX(b, c)	(0x1000ww | ((b) << 20) | ((c) << 3))

/*
 * Enumewation otx_cpt_ucode_ewwow_code_e
 *
 * Enumewates ucode ewwows
 */
enum otx_cpt_ucode_ewwow_code_e {
	CPT_NO_UCODE_EWWOW = 0x00,
	EWW_OPCODE_UNSUPPOWTED = 0x01,

	/* Scattew gathew */
	EWW_SCATTEW_GATHEW_WWITE_WENGTH = 0x02,
	EWW_SCATTEW_GATHEW_WIST = 0x03,
	EWW_SCATTEW_GATHEW_NOT_SUPPOWTED = 0x04,

};

/*
 * Enumewation otx_cpt_comp_e
 *
 * CPT OcteonTX Compwetion Enumewation
 * Enumewates the vawues of CPT_WES_S[COMPCODE].
 */
enum otx_cpt_comp_e {
	CPT_COMP_E_NOTDONE = 0x00,
	CPT_COMP_E_GOOD = 0x01,
	CPT_COMP_E_FAUWT = 0x02,
	CPT_COMP_E_SWEWW = 0x03,
	CPT_COMP_E_HWEWW = 0x04,
	CPT_COMP_E_WAST_ENTWY = 0x05
};

/*
 * Enumewation otx_cpt_vf_int_vec_e
 *
 * CPT OcteonTX VF MSI-X Vectow Enumewation
 * Enumewates the MSI-X intewwupt vectows.
 */
enum otx_cpt_vf_int_vec_e {
	CPT_VF_INT_VEC_E_MISC = 0x00,
	CPT_VF_INT_VEC_E_DONE = 0x01
};

/*
 * Stwuctuwe cpt_inst_s
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
union otx_cpt_inst_s {
	u64 u[8];

	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_17_63:47;
		u64 doneint:1;
		u64 wesewved_0_15:16;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 wesewved_0_15:16;
		u64 doneint:1;
		u64 wesewved_17_63:47;
#endif /* Wowd 0 - End */
		u64 wes_addw;
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 2 - Big Endian */
		u64 wesewved_172_191:20;
		u64 gwp:10;
		u64 tt:2;
		u64 tag:32;
#ewse /* Wowd 2 - Wittwe Endian */
		u64 tag:32;
		u64 tt:2;
		u64 gwp:10;
		u64 wesewved_172_191:20;
#endif /* Wowd 2 - End */
		u64 wq_ptw;
		u64 ei0;
		u64 ei1;
		u64 ei2;
		u64 ei3;
	} s;
};

/*
 * Stwuctuwe cpt_wes_s
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
union otx_cpt_wes_s {
	u64 u[2];
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_17_63:47;
		u64 doneint:1;
		u64 wesewved_8_15:8;
		u64 compcode:8;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 compcode:8;
		u64 wesewved_8_15:8;
		u64 doneint:1;
		u64 wesewved_17_63:47;
#endif /* Wowd 0 - End */
		u64 wesewved_64_127;
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_pf_bist_status
 *
 * CPT PF Contwow Bist Status Wegistew
 * This wegistew has the BIST status of memowies. Each bit is the BIST wesuwt
 * of an individuaw memowy (pew bit, 0 = pass and 1 = faiw).
 * otx_cptx_pf_bist_status_s
 * Wowd0
 *  bstatus [29:0](WO/H) BIST status. One bit pew memowy, enumewated by
 *	CPT_WAMS_E.
 */
union otx_cptx_pf_bist_status {
	u64 u;
	stwuct otx_cptx_pf_bist_status_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_30_63:34;
		u64 bstatus:30;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 bstatus:30;
		u64 wesewved_30_63:34;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_pf_constants
 *
 * CPT PF Constants Wegistew
 * This wegistew contains impwementation-wewated pawametews of CPT in CNXXXX.
 * otx_cptx_pf_constants_s
 * Wowd 0
 *  wesewved_40_63:24 [63:40] Wesewved.
 *  epcis:8 [39:32](WO) Numbew of EPCI busses.
 *  gwps:8 [31:24](WO) Numbew of engine gwoups impwemented.
 *  ae:8 [23:16](WO/H) Numbew of AEs. In CNXXXX, fow CPT0 wetuwns 0x0,
 *	fow CPT1 wetuwns 0x18, ow wess if thewe awe fuse-disabwes.
 *  se:8 [15:8](WO/H) Numbew of SEs. In CNXXXX, fow CPT0 wetuwns 0x30,
 *	ow wess if thewe awe fuse-disabwes, fow CPT1 wetuwns 0x0.
 *  vq:8 [7:0](WO) Numbew of VQs.
 */
union otx_cptx_pf_constants {
	u64 u;
	stwuct otx_cptx_pf_constants_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_40_63:24;
		u64 epcis:8;
		u64 gwps:8;
		u64 ae:8;
		u64 se:8;
		u64 vq:8;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 vq:8;
		u64 se:8;
		u64 ae:8;
		u64 gwps:8;
		u64 epcis:8;
		u64 wesewved_40_63:24;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_pf_exe_bist_status
 *
 * CPT PF Engine Bist Status Wegistew
 * This wegistew has the BIST status of each engine.  Each bit is the
 * BIST wesuwt of an individuaw engine (pew bit, 0 = pass and 1 = faiw).
 * otx_cptx_pf_exe_bist_status_s
 * Wowd0
 *  wesewved_48_63:16 [63:48] wesewved
 *  bstatus:48 [47:0](WO/H) BIST status. One bit pew engine.
 *
 */
union otx_cptx_pf_exe_bist_status {
	u64 u;
	stwuct otx_cptx_pf_exe_bist_status_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_48_63:16;
		u64 bstatus:48;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 bstatus:48;
		u64 wesewved_48_63:16;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_pf_q#_ctw
 *
 * CPT Queue Contwow Wegistew
 * This wegistew configuwes queues. This wegistew shouwd be changed onwy
 * when quiescent (see CPT()_VQ()_INPWOG[INFWIGHT]).
 * otx_cptx_pf_qx_ctw_s
 * Wowd0
 *  wesewved_60_63:4 [63:60] wesewved.
 *  auwa:12; [59:48](W/W) Guest-auwa fow wetuwning this queue's
 *	instwuction-chunk buffews to FPA. Onwy used when [INST_FWEE] is set.
 *	Fow the FPA to not discawd the wequest, FPA_PF_MAP() must map
 *	[AUWA] and CPT()_PF_Q()_GMCTW[GMID] as vawid.
 *  wesewved_45_47:3 [47:45] wesewved.
 *  size:13 [44:32](W/W) Command-buffew size, in numbew of 64-bit wowds pew
 *	command buffew segment. Must be 8*n + 1, whewe n is the numbew of
 *	instwuctions pew buffew segment.
 *  wesewved_11_31:21 [31:11] Wesewved.
 *  cont_eww:1 [10:10](W/W) Continue on ewwow.
 *	0 = When CPT()_VQ()_MISC_INT[NWWP], CPT()_VQ()_MISC_INT[IWDE] ow
 *	CPT()_VQ()_MISC_INT[DOVF] awe set by hawdwawe ow softwawe via
 *	CPT()_VQ()_MISC_INT_W1S, then CPT()_VQ()_CTW[ENA] is cweawed.  Due to
 *	pipewining, additionaw instwuctions may have been pwocessed between the
 *	instwuction causing the ewwow and the next instwuction in the disabwed
 *	queue (the instwuction at CPT()_VQ()_SADDW).
 *	1 = Ignowe ewwows and continue pwocessing instwuctions.
 *	Fow diagnostic use onwy.
 *  inst_fwee:1 [9:9](W/W) Instwuction FPA fwee. When set, when CPT weaches the
 *	end of an instwuction chunk, that chunk wiww be fweed to the FPA.
 *  inst_be:1 [8:8](W/W) Instwuction big-endian contwow. When set, instwuctions,
 *	instwuction next chunk pointews, and wesuwt stwuctuwes awe stowed in
 *	big-endian fowmat in memowy.
 *  iqb_wdwb:1 [7:7](W/W) Instwuction woad don't wwite back.
 *	0 = The hawdwawe issues NCB twansient woad (WDT) towawds the cache,
 *	which if the wine hits and is diwty wiww cause the wine to be
 *	wwitten back befowe being wepwaced.
 *	1 = The hawdwawe issues NCB WDWB wead-and-invawidate command towawds
 *	the cache when fetching the wast wowd of instwuctions; as a wesuwt the
 *	wine wiww not be wwitten back when wepwaced.  This impwoves
 *	pewfowmance, but softwawe must not wead the instwuctions aftew they awe
 *	posted to the hawdwawe.	Weads that do not consume the wast wowd of a
 *	cache wine awways use WDI.
 *  wesewved_4_6:3 [6:4] Wesewved.
 *  gwp:3; [3:1](W/W) Engine gwoup.
 *  pwi:1; [0:0](W/W) Queue pwiowity.
 *	1 = This queue has highew pwiowity. Wound-wobin between highew
 *	pwiowity queues.
 *	0 = This queue has wowew pwiowity. Wound-wobin between wowew
 *	pwiowity queues.
 */
union otx_cptx_pf_qx_ctw {
	u64 u;
	stwuct otx_cptx_pf_qx_ctw_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_60_63:4;
		u64 auwa:12;
		u64 wesewved_45_47:3;
		u64 size:13;
		u64 wesewved_11_31:21;
		u64 cont_eww:1;
		u64 inst_fwee:1;
		u64 inst_be:1;
		u64 iqb_wdwb:1;
		u64 wesewved_4_6:3;
		u64 gwp:3;
		u64 pwi:1;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 pwi:1;
		u64 gwp:3;
		u64 wesewved_4_6:3;
		u64 iqb_wdwb:1;
		u64 inst_be:1;
		u64 inst_fwee:1;
		u64 cont_eww:1;
		u64 wesewved_11_31:21;
		u64 size:13;
		u64 wesewved_45_47:3;
		u64 auwa:12;
		u64 wesewved_60_63:4;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_saddw
 *
 * CPT Queue Stawting Buffew Addwess Wegistews
 * These wegistews set the instwuction buffew stawting addwess.
 * otx_cptx_vqx_saddw_s
 * Wowd0
 *  wesewved_49_63:15 [63:49] Wesewved.
 *  ptw:43 [48:6](W/W/H) Instwuction buffew IOVA <48:6> (64-byte awigned).
 *	When wwitten, it is the initiaw buffew stawting addwess; when wead,
 *	it is the next wead pointew to be wequested fwom W2C. The PTW fiewd
 *	is ovewwwitten with the next pointew each time that the command buffew
 *	segment is exhausted. New commands wiww then be wead fwom the newwy
 *	specified command buffew pointew.
 *  wesewved_0_5:6 [5:0] Wesewved.
 *
 */
union otx_cptx_vqx_saddw {
	u64 u;
	stwuct otx_cptx_vqx_saddw_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_49_63:15;
		u64 ptw:43;
		u64 wesewved_0_5:6;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 wesewved_0_5:6;
		u64 ptw:43;
		u64 wesewved_49_63:15;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_misc_ena_w1s
 *
 * CPT Queue Misc Intewwupt Enabwe Set Wegistew
 * This wegistew sets intewwupt enabwe bits.
 * otx_cptx_vqx_misc_ena_w1s_s
 * Wowd0
 * wesewved_5_63:59 [63:5] Wesewved.
 * sweww:1 [4:4](W/W1S/H) Weads ow sets enabwe fow
 *	CPT(0..1)_VQ(0..63)_MISC_INT[SWEWW].
 * nwwp:1 [3:3](W/W1S/H) Weads ow sets enabwe fow
 *	CPT(0..1)_VQ(0..63)_MISC_INT[NWWP].
 * iwde:1 [2:2](W/W1S/H) Weads ow sets enabwe fow
 *	CPT(0..1)_VQ(0..63)_MISC_INT[IWDE].
 * dovf:1 [1:1](W/W1S/H) Weads ow sets enabwe fow
 *	CPT(0..1)_VQ(0..63)_MISC_INT[DOVF].
 * mbox:1 [0:0](W/W1S/H) Weads ow sets enabwe fow
 *	CPT(0..1)_VQ(0..63)_MISC_INT[MBOX].
 *
 */
union otx_cptx_vqx_misc_ena_w1s {
	u64 u;
	stwuct otx_cptx_vqx_misc_ena_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_5_63:59;
		u64 sweww:1;
		u64 nwwp:1;
		u64 iwde:1;
		u64 dovf:1;
		u64 mbox:1;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 mbox:1;
		u64 dovf:1;
		u64 iwde:1;
		u64 nwwp:1;
		u64 sweww:1;
		u64 wesewved_5_63:59;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_doowbeww
 *
 * CPT Queue Doowbeww Wegistews
 * Doowbewws fow the CPT instwuction queues.
 * otx_cptx_vqx_doowbeww_s
 * Wowd0
 *  wesewved_20_63:44 [63:20] Wesewved.
 *  dbeww_cnt:20 [19:0](W/W/H) Numbew of instwuction queue 64-bit wowds to add
 *	to the CPT instwuction doowbeww count. Weadback vawue is the
 *	cuwwent numbew of pending doowbeww wequests. If countew ovewfwows
 *	CPT()_VQ()_MISC_INT[DBEWW_DOVF] is set. To weset the count back to
 *	zewo, wwite one to cweaw CPT()_VQ()_MISC_INT_ENA_W1C[DBEWW_DOVF],
 *	then wwite a vawue of 2^20 minus the wead [DBEWW_CNT], then wwite one
 *	to CPT()_VQ()_MISC_INT_W1C[DBEWW_DOVF] and
 *	CPT()_VQ()_MISC_INT_ENA_W1S[DBEWW_DOVF]. Must be a muwtipwe of 8.
 *	Aww CPT instwuctions awe 8 wowds and wequiwe a doowbeww count of
 *	muwtipwe of 8.
 */
union otx_cptx_vqx_doowbeww {
	u64 u;
	stwuct otx_cptx_vqx_doowbeww_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_20_63:44;
		u64 dbeww_cnt:20;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 dbeww_cnt:20;
		u64 wesewved_20_63:44;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_inpwog
 *
 * CPT Queue In Pwogwess Count Wegistews
 * These wegistews contain the pew-queue instwuction in fwight wegistews.
 * otx_cptx_vqx_inpwog_s
 * Wowd0
 *  wesewved_8_63:56 [63:8] Wesewved.
 *  infwight:8 [7:0](WO/H) Infwight count. Counts the numbew of instwuctions
 *	fow the VF fow which CPT is fetching, executing ow wesponding to
 *	instwuctions. Howevew this does not incwude any intewwupts that awe
 *	awaiting softwawe handwing (CPT()_VQ()_DONE[DONE] != 0x0).
 *	A queue may not be weconfiguwed untiw:
 *	1. CPT()_VQ()_CTW[ENA] is cweawed by softwawe.
 *	2. [INFWIGHT] is powwed untiw equaws to zewo.
 */
union otx_cptx_vqx_inpwog {
	u64 u;
	stwuct otx_cptx_vqx_inpwog_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_8_63:56;
		u64 infwight:8;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 infwight:8;
		u64 wesewved_8_63:56;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_misc_int
 *
 * CPT Queue Misc Intewwupt Wegistew
 * These wegistews contain the pew-queue miscewwaneous intewwupts.
 * otx_cptx_vqx_misc_int_s
 * Wowd 0
 *  wesewved_5_63:59 [63:5] Wesewved.
 *  sweww:1 [4:4](W/W1C/H) Softwawe ewwow fwom engines.
 *  nwwp:1  [3:3](W/W1C/H) NCB wesuwt wwite wesponse ewwow.
 *  iwde:1  [2:2](W/W1C/H) Instwuction NCB wead wesponse ewwow.
 *  dovf:1 [1:1](W/W1C/H) Doowbeww ovewfwow.
 *  mbox:1 [0:0](W/W1C/H) PF to VF maiwbox intewwupt. Set when
 *	CPT()_VF()_PF_MBOX(0) is wwitten.
 *
 */
union otx_cptx_vqx_misc_int {
	u64 u;
	stwuct otx_cptx_vqx_misc_int_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_5_63:59;
		u64 sweww:1;
		u64 nwwp:1;
		u64 iwde:1;
		u64 dovf:1;
		u64 mbox:1;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 mbox:1;
		u64 dovf:1;
		u64 iwde:1;
		u64 nwwp:1;
		u64 sweww:1;
		u64 wesewved_5_63:59;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_done_ack
 *
 * CPT Queue Done Count Ack Wegistews
 * This wegistew is wwitten by softwawe to acknowwedge intewwupts.
 * otx_cptx_vqx_done_ack_s
 * Wowd0
 *  wesewved_20_63:44 [63:20] Wesewved.
 *  done_ack:20 [19:0](W/W/H) Numbew of decwements to CPT()_VQ()_DONE[DONE].
 *	Weads CPT()_VQ()_DONE[DONE]. Wwitten by softwawe to acknowwedge
 *	intewwupts. If CPT()_VQ()_DONE[DONE] is stiww nonzewo the intewwupt
 *	wiww be we-sent if the conditions descwibed in CPT()_VQ()_DONE[DONE]
 *	awe satisfied.
 *
 */
union otx_cptx_vqx_done_ack {
	u64 u;
	stwuct otx_cptx_vqx_done_ack_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_20_63:44;
		u64 done_ack:20;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 done_ack:20;
		u64 wesewved_20_63:44;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_done
 *
 * CPT Queue Done Count Wegistews
 * These wegistews contain the pew-queue instwuction done count.
 * cptx_vqx_done_s
 * Wowd0
 *  wesewved_20_63:44 [63:20] Wesewved.
 *  done:20 [19:0](W/W/H) Done count. When CPT_INST_S[DONEINT] set and that
 *	instwuction compwetes, CPT()_VQ()_DONE[DONE] is incwemented when the
 *	instwuction finishes. Wwite to this fiewd awe fow diagnostic use onwy;
 *	instead softwawe wwites CPT()_VQ()_DONE_ACK with the numbew of
 *	decwements fow this fiewd.
 *	Intewwupts awe sent as fowwows:
 *	* When CPT()_VQ()_DONE[DONE] = 0, then no wesuwts awe pending, the
 *	intewwupt coawescing timew is hewd to zewo, and an intewwupt is not
 *	sent.
 *	* When CPT()_VQ()_DONE[DONE] != 0, then the intewwupt coawescing timew
 *	counts. If the countew is >= CPT()_VQ()_DONE_WAIT[TIME_WAIT]*1024, ow
 *	CPT()_VQ()_DONE[DONE] >= CPT()_VQ()_DONE_WAIT[NUM_WAIT], i.e. enough
 *	time has passed ow enough wesuwts have awwived, then the intewwupt is
 *	sent.
 *	* When CPT()_VQ()_DONE_ACK is wwitten (ow CPT()_VQ()_DONE is wwitten
 *	but this is not typicaw), the intewwupt coawescing timew westawts.
 *	Note aftew decwementing this intewwupt equation is wecomputed,
 *	fow exampwe if CPT()_VQ()_DONE[DONE] >= CPT()_VQ()_DONE_WAIT[NUM_WAIT]
 *	and because the timew is zewo, the intewwupt wiww be wesent immediatewy.
 *	(This covews the wace case between softwawe acknowwedging an intewwupt
 *	and a wesuwt wetuwning.)
 *	* When CPT()_VQ()_DONE_ENA_W1S[DONE] = 0, intewwupts awe not sent,
 *	but the counting descwibed above stiww occuws.
 *	Since CPT instwuctions compwete out-of-owdew, if softwawe is using
 *	compwetion intewwupts the suggested scheme is to wequest a DONEINT on
 *	each wequest, and when an intewwupt awwives pewfowm a "gweedy" scan fow
 *	compwetions; even if a watew command is acknowwedged fiwst this wiww
 *	not wesuwt in missing a compwetion.
 *	Softwawe is wesponsibwe fow making suwe [DONE] does not ovewfwow;
 *	fow exampwe by insuwing thewe awe not mowe than 2^20-1 instwuctions in
 *	fwight that may wequest intewwupts.
 *
 */
union otx_cptx_vqx_done {
	u64 u;
	stwuct otx_cptx_vqx_done_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_20_63:44;
		u64 done:20;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 done:20;
		u64 wesewved_20_63:44;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_done_wait
 *
 * CPT Queue Done Intewwupt Coawescing Wait Wegistews
 * Specifies the pew queue intewwupt coawescing settings.
 * cptx_vqx_done_wait_s
 * Wowd0
 *  wesewved_48_63:16 [63:48] Wesewved.
 *  time_wait:16; [47:32](W/W) Time howd-off. When CPT()_VQ()_DONE[DONE] = 0
 *	ow CPT()_VQ()_DONE_ACK is wwitten a timew is cweawed. When the timew
 *	weaches [TIME_WAIT]*1024 then intewwupt coawescing ends.
 *	see CPT()_VQ()_DONE[DONE]. If 0x0, time coawescing is disabwed.
 *  wesewved_20_31:12 [31:20] Wesewved.
 *  num_wait:20 [19:0](W/W) Numbew of messages howd-off.
 *	When CPT()_VQ()_DONE[DONE] >= [NUM_WAIT] then intewwupt coawescing ends
 *	see CPT()_VQ()_DONE[DONE]. If 0x0, same behaviow as 0x1.
 *
 */
union otx_cptx_vqx_done_wait {
	u64 u;
	stwuct otx_cptx_vqx_done_wait_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_48_63:16;
		u64 time_wait:16;
		u64 wesewved_20_31:12;
		u64 num_wait:20;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 num_wait:20;
		u64 wesewved_20_31:12;
		u64 time_wait:16;
		u64 wesewved_48_63:16;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_done_ena_w1s
 *
 * CPT Queue Done Intewwupt Enabwe Set Wegistews
 * Wwite 1 to these wegistews wiww enabwe the DONEINT intewwupt fow the queue.
 * cptx_vqx_done_ena_w1s_s
 * Wowd0
 *  wesewved_1_63:63 [63:1] Wesewved.
 *  done:1 [0:0](W/W1S/H) Wwite 1 wiww enabwe DONEINT fow this queue.
 *	Wwite 0 has no effect. Wead wiww wetuwn the enabwe bit.
 */
union otx_cptx_vqx_done_ena_w1s {
	u64 u;
	stwuct otx_cptx_vqx_done_ena_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_1_63:63;
		u64 done:1;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 done:1;
		u64 wesewved_1_63:63;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Wegistew (NCB) otx_cpt#_vq#_ctw
 *
 * CPT VF Queue Contwow Wegistews
 * This wegistew configuwes queues. This wegistew shouwd be changed (othew than
 * cweawing [ENA]) onwy when quiescent (see CPT()_VQ()_INPWOG[INFWIGHT]).
 * cptx_vqx_ctw_s
 * Wowd0
 *  wesewved_1_63:63 [63:1] Wesewved.
 *  ena:1 [0:0](W/W/H) Enabwes the wogicaw instwuction queue.
 *	See awso CPT()_PF_Q()_CTW[CONT_EWW] and	CPT()_VQ()_INPWOG[INFWIGHT].
 *	1 = Queue is enabwed.
 *	0 = Queue is disabwed.
 */
union otx_cptx_vqx_ctw {
	u64 u;
	stwuct otx_cptx_vqx_ctw_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		u64 wesewved_1_63:63;
		u64 ena:1;
#ewse /* Wowd 0 - Wittwe Endian */
		u64 ena:1;
		u64 wesewved_1_63:63;
#endif /* Wowd 0 - End */
	} s;
};

/*
 * Ewwow Addwess/Ewwow Codes
 *
 * In the event of a sevewe ewwow, micwocode wwites an 8-byte Ewwow Code
 * vawue (ECODE) to host memowy at the Wptw addwess specified by the host
 * system (in the 64-byte wequest).
 *
 * Wowd0
 *  [63:56](W) 8-bit compwetion code
 *  [55:48](W) Numbew of the cowe that wepowted the sevewe ewwow
 *  [47:0] Wowew 6 bytes of M-Inst wowd2. Used to assist in uniquewy
 *  identifying which specific instwuction caused the ewwow. This assumes
 *  that each instwuction has a unique wesuwt wocation (WPTW), at weast
 *  fow a given pewiod of time.
 */
union otx_cpt_ewwow_code {
	u64 u;
	stwuct otx_cpt_ewwow_code_s {
#if defined(__BIG_ENDIAN_BITFIEWD) /* Wowd 0 - Big Endian */
		uint64_t ccode:8;
		uint64_t coweid:8;
		uint64_t wptw6:48;
#ewse /* Wowd 0 - Wittwe Endian */
		uint64_t wptw6:48;
		uint64_t coweid:8;
		uint64_t ccode:8;
#endif /* Wowd 0 - End */
	} s;
};

#endif /*__OTX_CPT_HW_TYPES_H */
