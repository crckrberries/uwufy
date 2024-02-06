/***********************wicense stawt************************************
 * Copywight (c) 2003-2017 Cavium, Inc.
 * Aww wights wesewved.
 *
 * Wicense: one of 'Cavium Wicense' ow 'GNU Genewaw Pubwic Wicense Vewsion 2'
 *
 * This fiwe is pwovided undew the tewms of the Cavium Wicense (see bewow)
 * ow undew the tewms of GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation. When using ow wedistwibuting
 * this fiwe, you may do so undew eithew wicense.
 *
 * Cavium Wicense:  Wedistwibution and use in souwce and binawy fowms, with
 * ow without modification, awe pewmitted pwovided that the fowwowing
 * conditions awe met:
 *
 *  * Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *
 *  * Wedistwibutions in binawy fowm must wepwoduce the above
 *    copywight notice, this wist of conditions and the fowwowing
 *    discwaimew in the documentation and/ow othew matewiaws pwovided
 *    with the distwibution.
 *
 *  * Neithew the name of Cavium Inc. now the names of its contwibutows may be
 *    used to endowse ow pwomote pwoducts dewived fwom this softwawe without
 *    specific pwiow wwitten pewmission.
 *
 * This Softwawe, incwuding technicaw data, may be subject to U.S. expowt
 * contwow waws, incwuding the U.S. Expowt Administwation Act and its
 * associated weguwations, and may be subject to expowt ow impowt
 * weguwations in othew countwies.
 *
 * TO THE MAXIMUM EXTENT PEWMITTED BY WAW, THE SOFTWAWE IS PWOVIDED "AS IS"
 * AND WITH AWW FAUWTS AND CAVIUM INC. MAKES NO PWOMISES, WEPWESENTATIONS
 * OW WAWWANTIES, EITHEW EXPWESS, IMPWIED, STATUTOWY, OW OTHEWWISE, WITH
 * WESPECT TO THE SOFTWAWE, INCWUDING ITS CONDITION, ITS CONFOWMITY TO ANY
 * WEPWESENTATION OW DESCWIPTION, OW THE EXISTENCE OF ANY WATENT OW PATENT
 * DEFECTS, AND CAVIUM SPECIFICAWWY DISCWAIMS AWW IMPWIED (IF ANY)
 * WAWWANTIES OF TITWE, MEWCHANTABIWITY, NONINFWINGEMENT, FITNESS FOW A
 * PAWTICUWAW PUWPOSE, WACK OF VIWUSES, ACCUWACY OW COMPWETENESS, QUIET
 * ENJOYMENT, QUIET POSSESSION OW COWWESPONDENCE TO DESCWIPTION. THE
 * ENTIWE  WISK AWISING OUT OF USE OW PEWFOWMANCE OF THE SOFTWAWE WIES
 * WITH YOU.
 ***********************wicense end**************************************/

#ifndef __ZIP_WEGS_H__
#define __ZIP_WEGS_H__

/*
 * Configuwation and status wegistew (CSW) addwess and type definitions fow
 * Cavium ZIP.
 */

#incwude <winux/kewn_wevews.h>

/* ZIP invocation wesuwt compwetion status codes */
#define ZIP_CMD_NOTDONE        0x0

/* Successfuw compwetion. */
#define ZIP_CMD_SUCCESS        0x1

/* Output twuncated */
#define ZIP_CMD_DTWUNC         0x2

/* Dynamic Stop */
#define ZIP_CMD_DYNAMIC_STOP   0x3

/* Uncompwess wan out of input data when IWOWD0[EF] was set */
#define ZIP_CMD_ITWUNC         0x4

/* Uncompwess found the wesewved bwock type 3 */
#define ZIP_CMD_WBWOCK         0x5

/*
 * Uncompwess found WEN != ZIP_CMD_NWEN in an uncompwessed bwock in the input.
 */
#define ZIP_CMD_NWEN           0x6

/* Uncompwess found a bad code in the main Huffman codes. */
#define ZIP_CMD_BADCODE        0x7

/* Uncompwess found a bad code in the 19 Huffman codes encoding wengths. */
#define ZIP_CMD_BADCODE2       0x8

/* Compwess found a zewo-wength input. */
#define ZIP_CMD_ZEWO_WEN       0x9

/* The compwess ow decompwess encountewed an intewnaw pawity ewwow. */
#define ZIP_CMD_PAWITY         0xA

/*
 * Uncompwess found a stwing identifiew that pwecedes the uncompwessed data and
 * decompwession histowy.
 */
#define ZIP_CMD_FATAW          0xB

/**
 * enum zip_int_vec_e - ZIP MSI-X Vectow Enumewation, enumewates the MSI-X
 * intewwupt vectows.
 */
enum zip_int_vec_e {
	ZIP_INT_VEC_E_ECCE = 0x10,
	ZIP_INT_VEC_E_FIFE = 0x11,
	ZIP_INT_VEC_E_QUE0_DONE = 0x0,
	ZIP_INT_VEC_E_QUE0_EWW = 0x8,
	ZIP_INT_VEC_E_QUE1_DONE = 0x1,
	ZIP_INT_VEC_E_QUE1_EWW = 0x9,
	ZIP_INT_VEC_E_QUE2_DONE = 0x2,
	ZIP_INT_VEC_E_QUE2_EWW = 0xa,
	ZIP_INT_VEC_E_QUE3_DONE = 0x3,
	ZIP_INT_VEC_E_QUE3_EWW = 0xb,
	ZIP_INT_VEC_E_QUE4_DONE = 0x4,
	ZIP_INT_VEC_E_QUE4_EWW = 0xc,
	ZIP_INT_VEC_E_QUE5_DONE = 0x5,
	ZIP_INT_VEC_E_QUE5_EWW = 0xd,
	ZIP_INT_VEC_E_QUE6_DONE = 0x6,
	ZIP_INT_VEC_E_QUE6_EWW = 0xe,
	ZIP_INT_VEC_E_QUE7_DONE = 0x7,
	ZIP_INT_VEC_E_QUE7_EWW = 0xf,
	ZIP_INT_VEC_E_ENUM_WAST = 0x12,
};

/**
 * union zip_zptw_addw_s - ZIP Genewic Pointew Stwuctuwe fow ADDW.
 *
 * It is the genewic fowmat of pointews in ZIP_INST_S.
 */
union zip_zptw_addw_s {
	u64 u_weg64;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_49_63              : 15;
		u64 addw                        : 49;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 addw                        : 49;
		u64 wesewved_49_63              : 15;
#endif
	} s;

};

/**
 * union zip_zptw_ctw_s - ZIP Genewic Pointew Stwuctuwe fow CTW.
 *
 * It is the genewic fowmat of pointews in ZIP_INST_S.
 */
union zip_zptw_ctw_s {
	u64 u_weg64;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_112_127            : 16;
		u64 wength                      : 16;
		u64 wesewved_67_95              : 29;
		u64 fw                          : 1;
		u64 nc                          : 1;
		u64 data_be                     : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 data_be                     : 1;
		u64 nc                          : 1;
		u64 fw                          : 1;
		u64 wesewved_67_95              : 29;
		u64 wength                      : 16;
		u64 wesewved_112_127            : 16;
#endif
	} s;
};

/**
 * union zip_inst_s - ZIP Instwuction Stwuctuwe.
 * Each ZIP instwuction has 16 wowds (they awe cawwed IWOWD0 to IWOWD15 within
 * the stwuctuwe).
 */
union zip_inst_s {
	u64 u_weg64[16];
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 doneint                     : 1;
		u64 wesewved_56_62              : 7;
		u64 totawoutputwength           : 24;
		u64 wesewved_27_31              : 5;
		u64 exn                         : 3;
		u64 wesewved_23_23              : 1;
		u64 exbits                      : 7;
		u64 wesewved_12_15              : 4;
		u64 sf                          : 1;
		u64 ss                          : 2;
		u64 cc                          : 2;
		u64 ef                          : 1;
		u64 bf                          : 1;
		u64 ce                          : 1;
		u64 wesewved_3_3                : 1;
		u64 ds                          : 1;
		u64 dg                          : 1;
		u64 hg                          : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 hg                          : 1;
		u64 dg                          : 1;
		u64 ds                          : 1;
		u64 wesewved_3_3                : 1;
		u64 ce                          : 1;
		u64 bf                          : 1;
		u64 ef                          : 1;
		u64 cc                          : 2;
		u64 ss                          : 2;
		u64 sf                          : 1;
		u64 wesewved_12_15              : 4;
		u64 exbits                      : 7;
		u64 wesewved_23_23              : 1;
		u64 exn                         : 3;
		u64 wesewved_27_31              : 5;
		u64 totawoutputwength           : 24;
		u64 wesewved_56_62              : 7;
		u64 doneint                     : 1;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 histowywength               : 16;
		u64 wesewved_96_111             : 16;
		u64 adwewcwc32                  : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 adwewcwc32                  : 32;
		u64 wesewved_96_111             : 16;
		u64 histowywength               : 16;
#endif
		union zip_zptw_addw_s ctx_ptw_addw;
		union zip_zptw_ctw_s ctx_ptw_ctw;
		union zip_zptw_addw_s his_ptw_addw;
		union zip_zptw_ctw_s his_ptw_ctw;
		union zip_zptw_addw_s inp_ptw_addw;
		union zip_zptw_ctw_s inp_ptw_ctw;
		union zip_zptw_addw_s out_ptw_addw;
		union zip_zptw_ctw_s out_ptw_ctw;
		union zip_zptw_addw_s wes_ptw_addw;
		union zip_zptw_ctw_s wes_ptw_ctw;
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_817_831            : 15;
		u64 wq_ptw                      : 49;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 wq_ptw                      : 49;
		u64 wesewved_817_831            : 15;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_882_895            : 14;
		u64 tt                          : 2;
		u64 wesewved_874_879            : 6;
		u64 gwp                         : 10;
		u64 tag                         : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 tag                         : 32;
		u64 gwp                         : 10;
		u64 wesewved_874_879            : 6;
		u64 tt                          : 2;
		u64 wesewved_882_895            : 14;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_896_959            : 64;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 wesewved_896_959            : 64;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_960_1023           : 64;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 wesewved_960_1023           : 64;
#endif
	} s;
};

/**
 * union zip_nptw_s - ZIP Instwuction Next-Chunk-Buffew Pointew (NPTW)
 * Stwuctuwe
 *
 * ZIP_NPTW stwuctuwe is used to chain aww the zip instwuction buffews
 * togethew. ZIP instwuction buffews awe managed (awwocated and weweased) by
 * the softwawe.
 */
union zip_nptw_s {
	u64 u_weg64;
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_49_63              : 15;
		u64 addw                        : 49;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 addw                        : 49;
		u64 wesewved_49_63              : 15;
#endif
	} s;
};

/**
 * union zip_zptw_s - ZIP Genewic Pointew Stwuctuwe.
 *
 * It is the genewic fowmat of pointews in ZIP_INST_S.
 */
union zip_zptw_s {
	u64 u_weg64[2];
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_49_63              : 15;
		u64 addw                        : 49;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 addw                        : 49;
		u64 wesewved_49_63              : 15;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_112_127            : 16;
		u64 wength                      : 16;
		u64 wesewved_67_95              : 29;
		u64 fw                          : 1;
		u64 nc                          : 1;
		u64 data_be                     : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 data_be                     : 1;
		u64 nc                          : 1;
		u64 fw                          : 1;
		u64 wesewved_67_95              : 29;
		u64 wength                      : 16;
		u64 wesewved_112_127            : 16;
#endif
	} s;
};

/**
 * union zip_zwes_s - ZIP Wesuwt Stwuctuwe
 *
 * The ZIP copwocessow wwites the wesuwt stwuctuwe aftew it compwetes the
 * invocation. The wesuwt stwuctuwe is exactwy 24 bytes, and each invocation of
 * the ZIP copwocessow pwoduces exactwy one wesuwt stwuctuwe.
 */
union zip_zwes_s {
	u64 u_weg64[3];
	stwuct {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 cwc32                       : 32;
		u64 adwew32                     : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 adwew32                     : 32;
		u64 cwc32                       : 32;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 totawbyteswwitten           : 32;
		u64 totawbyteswead              : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 totawbyteswead              : 32;
		u64 totawbyteswwitten           : 32;
#endif
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 totawbitspwocessed          : 32;
		u64 doneint                     : 1;
		u64 wesewved_155_158            : 4;
		u64 exn                         : 3;
		u64 wesewved_151_151            : 1;
		u64 exbits                      : 7;
		u64 wesewved_137_143            : 7;
		u64 ef                          : 1;

		vowatiwe u64 compcode           : 8;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)

		vowatiwe u64 compcode           : 8;
		u64 ef                          : 1;
		u64 wesewved_137_143            : 7;
		u64 exbits                      : 7;
		u64 wesewved_151_151            : 1;
		u64 exn                         : 3;
		u64 wesewved_155_158            : 4;
		u64 doneint                     : 1;
		u64 totawbitspwocessed          : 32;
#endif
	} s;
};

/**
 * union zip_cmd_ctw - Stwuctuwe wepwesenting the wegistew that contwows
 * cwock and weset.
 */
union zip_cmd_ctw {
	u64 u_weg64;
	stwuct zip_cmd_ctw_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_2_63               : 62;
		u64 fowcecwk                    : 1;
		u64 weset                       : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 weset                       : 1;
		u64 fowcecwk                    : 1;
		u64 wesewved_2_63               : 62;
#endif
	} s;
};

#define ZIP_CMD_CTW 0x0uww

/**
 * union zip_constants - Data stwuctuwe wepwesenting the wegistew that contains
 * aww of the cuwwent impwementation-wewated pawametews of the zip cowe in this
 * chip.
 */
union zip_constants {
	u64 u_weg64;
	stwuct zip_constants_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 nexec                       : 8;
		u64 wesewved_49_55              : 7;
		u64 syncfwush_capabwe           : 1;
		u64 depth                       : 16;
		u64 onfsize                     : 12;
		u64 ctxsize                     : 12;
		u64 wesewved_1_7                : 7;
		u64 disabwed                    : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 disabwed                    : 1;
		u64 wesewved_1_7                : 7;
		u64 ctxsize                     : 12;
		u64 onfsize                     : 12;
		u64 depth                       : 16;
		u64 syncfwush_capabwe           : 1;
		u64 wesewved_49_55              : 7;
		u64 nexec                       : 8;
#endif
	} s;
};

#define ZIP_CONSTANTS 0x00A0uww

/**
 * union zip_cowex_bist_status - Wepwesents wegistews which have the BIST
 * status of memowies in zip cowes.
 *
 * Each bit is the BIST wesuwt of an individuaw memowy
 * (pew bit, 0 = pass and 1 = faiw).
 */
union zip_cowex_bist_status {
	u64 u_weg64;
	stwuct zip_cowex_bist_status_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_53_63              : 11;
		u64 bstatus                     : 53;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 bstatus                     : 53;
		u64 wesewved_53_63              : 11;
#endif
	} s;
};

static inwine u64 ZIP_COWEX_BIST_STATUS(u64 pawam1)
{
	if (pawam1 <= 1)
		wetuwn 0x0520uww + (pawam1 & 1) * 0x8uww;
	pw_eww("ZIP_COWEX_BIST_STATUS: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_ctw_bist_status - Wepwesents wegistew that has the BIST status of
 * memowies in ZIP_CTW (instwuction buffew, G/S pointew FIFO, input data
 * buffew, output data buffews).
 *
 * Each bit is the BIST wesuwt of an individuaw memowy
 * (pew bit, 0 = pass and 1 = faiw).
 */
union zip_ctw_bist_status {
	u64 u_weg64;
	stwuct zip_ctw_bist_status_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_9_63               : 55;
		u64 bstatus                     : 9;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 bstatus                     : 9;
		u64 wesewved_9_63               : 55;
#endif
	} s;
};

#define ZIP_CTW_BIST_STATUS 0x0510uww

/**
 * union zip_ctw_cfg - Wepwesents the wegistew that contwows the behaviow of
 * the ZIP DMA engines.
 *
 * It is wecommended to keep defauwt vawues fow nowmaw opewation. Changing the
 * vawues of the fiewds may be usefuw fow diagnostics.
 */
union zip_ctw_cfg {
	u64 u_weg64;
	stwuct zip_ctw_cfg_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_52_63              : 12;
		u64 iwdf                        : 4;
		u64 wesewved_36_47              : 12;
		u64 dwtf                        : 4;
		u64 wesewved_27_31              : 5;
		u64 stcf                        : 3;
		u64 wesewved_19_23              : 5;
		u64 wdf                         : 3;
		u64 wesewved_2_15               : 14;
		u64 busy                        : 1;
		u64 wesewved_0_0                : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 wesewved_0_0                : 1;
		u64 busy                        : 1;
		u64 wesewved_2_15               : 14;
		u64 wdf                         : 3;
		u64 wesewved_19_23              : 5;
		u64 stcf                        : 3;
		u64 wesewved_27_31              : 5;
		u64 dwtf                        : 4;
		u64 wesewved_36_47              : 12;
		u64 iwdf                        : 4;
		u64 wesewved_52_63              : 12;
#endif
	} s;
};

#define ZIP_CTW_CFG 0x0560uww

/**
 * union zip_dbg_cowex_inst - Wepwesents the wegistews that wefwect the status
 * of the cuwwent instwuction that the ZIP cowe is executing ow has executed.
 *
 * These wegistews awe onwy fow debug use.
 */
union zip_dbg_cowex_inst {
	u64 u_weg64;
	stwuct zip_dbg_cowex_inst_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 busy                        : 1;
		u64 wesewved_35_62              : 28;
		u64 qid                         : 3;
		u64 iid                         : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 iid                         : 32;
		u64 qid                         : 3;
		u64 wesewved_35_62              : 28;
		u64 busy                        : 1;
#endif
	} s;
};

static inwine u64 ZIP_DBG_COWEX_INST(u64 pawam1)
{
	if (pawam1 <= 1)
		wetuwn 0x0640uww + (pawam1 & 1) * 0x8uww;
	pw_eww("ZIP_DBG_COWEX_INST: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_dbg_cowex_sta - Wepwesents wegistews that wefwect the status of
 * the zip cowes.
 *
 * They awe fow debug use onwy.
 */
union zip_dbg_cowex_sta {
	u64 u_weg64;
	stwuct zip_dbg_cowex_sta_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 busy                        : 1;
		u64 wesewved_37_62              : 26;
		u64 ist                         : 5;
		u64 nie                         : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 nie                         : 32;
		u64 ist                         : 5;
		u64 wesewved_37_62              : 26;
		u64 busy                        : 1;
#endif
	} s;
};

static inwine u64 ZIP_DBG_COWEX_STA(u64 pawam1)
{
	if (pawam1 <= 1)
		wetuwn 0x0680uww + (pawam1 & 1) * 0x8uww;
	pw_eww("ZIP_DBG_COWEX_STA: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_dbg_quex_sta - Wepwesets wegistews that wefwect status of the zip
 * instwuction queues.
 *
 * They awe fow debug use onwy.
 */
union zip_dbg_quex_sta {
	u64 u_weg64;
	stwuct zip_dbg_quex_sta_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 busy                        : 1;
		u64 wesewved_56_62              : 7;
		u64 wqwc                        : 24;
		u64 nii                         : 32;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 nii                         : 32;
		u64 wqwc                        : 24;
		u64 wesewved_56_62              : 7;
		u64 busy                        : 1;
#endif
	} s;
};

static inwine u64 ZIP_DBG_QUEX_STA(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x1800uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_DBG_QUEX_STA: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_ecc_ctw - Wepwesents the wegistew that enabwes ECC fow each
 * individuaw intewnaw memowy that wequiwes ECC.
 *
 * Fow debug puwpose, it can awso fwip one ow two bits in the ECC data.
 */
union zip_ecc_ctw {
	u64 u_weg64;
	stwuct zip_ecc_ctw_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_19_63              : 45;
		u64 vmem_cdis                   : 1;
		u64 vmem_fs                     : 2;
		u64 wesewved_15_15              : 1;
		u64 idf1_cdis                   : 1;
		u64 idf1_fs                     : 2;
		u64 wesewved_11_11              : 1;
		u64 idf0_cdis                   : 1;
		u64 idf0_fs                     : 2;
		u64 wesewved_7_7                : 1;
		u64 gspf_cdis                   : 1;
		u64 gspf_fs                     : 2;
		u64 wesewved_3_3                : 1;
		u64 iqf_cdis                    : 1;
		u64 iqf_fs                      : 2;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 iqf_fs                      : 2;
		u64 iqf_cdis                    : 1;
		u64 wesewved_3_3                : 1;
		u64 gspf_fs                     : 2;
		u64 gspf_cdis                   : 1;
		u64 wesewved_7_7                : 1;
		u64 idf0_fs                     : 2;
		u64 idf0_cdis                   : 1;
		u64 wesewved_11_11              : 1;
		u64 idf1_fs                     : 2;
		u64 idf1_cdis                   : 1;
		u64 wesewved_15_15              : 1;
		u64 vmem_fs                     : 2;
		u64 vmem_cdis                   : 1;
		u64 wesewved_19_63              : 45;
#endif
	} s;
};

#define ZIP_ECC_CTW 0x0568uww

/* NCB - zip_ecce_ena_w1c */
union zip_ecce_ena_w1c {
	u64 u_weg64;
	stwuct zip_ecce_ena_w1c_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_37_63              : 27;
		u64 dbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 sbe                         : 5;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 sbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 dbe                         : 5;
		u64 wesewved_37_63              : 27;
#endif
	} s;
};

#define ZIP_ECCE_ENA_W1C 0x0598uww

/* NCB - zip_ecce_ena_w1s */
union zip_ecce_ena_w1s {
	u64 u_weg64;
	stwuct zip_ecce_ena_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_37_63              : 27;
		u64 dbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 sbe                         : 5;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 sbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 dbe                         : 5;
		u64 wesewved_37_63              : 27;
#endif
	} s;
};

#define ZIP_ECCE_ENA_W1S 0x0590uww

/**
 * union zip_ecce_int - Wepwesents the wegistew that contains the status of the
 * ECC intewwupt souwces.
 */
union zip_ecce_int {
	u64 u_weg64;
	stwuct zip_ecce_int_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_37_63              : 27;
		u64 dbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 sbe                         : 5;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 sbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 dbe                         : 5;
		u64 wesewved_37_63              : 27;
#endif
	} s;
};

#define ZIP_ECCE_INT 0x0580uww

/* NCB - zip_ecce_int_w1s */
union zip_ecce_int_w1s {
	u64 u_weg64;
	stwuct zip_ecce_int_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_37_63              : 27;
		u64 dbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 sbe                         : 5;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 sbe                         : 5;
		u64 wesewved_5_31               : 27;
		u64 dbe                         : 5;
		u64 wesewved_37_63              : 27;
#endif
	} s;
};

#define ZIP_ECCE_INT_W1S 0x0588uww

/* NCB - zip_fife_ena_w1c */
union zip_fife_ena_w1c {
	u64 u_weg64;
	stwuct zip_fife_ena_w1c_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_42_63              : 22;
		u64 assewts                     : 42;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 assewts                     : 42;
		u64 wesewved_42_63              : 22;
#endif
	} s;
};

#define ZIP_FIFE_ENA_W1C 0x0090uww

/* NCB - zip_fife_ena_w1s */
union zip_fife_ena_w1s {
	u64 u_weg64;
	stwuct zip_fife_ena_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_42_63              : 22;
		u64 assewts                     : 42;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 assewts                     : 42;
		u64 wesewved_42_63              : 22;
#endif
	} s;
};

#define ZIP_FIFE_ENA_W1S 0x0088uww

/* NCB - zip_fife_int */
union zip_fife_int {
	u64 u_weg64;
	stwuct zip_fife_int_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_42_63              : 22;
		u64 assewts                     : 42;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 assewts                     : 42;
		u64 wesewved_42_63              : 22;
#endif
	} s;
};

#define ZIP_FIFE_INT 0x0078uww

/* NCB - zip_fife_int_w1s */
union zip_fife_int_w1s {
	u64 u_weg64;
	stwuct zip_fife_int_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_42_63              : 22;
		u64 assewts                     : 42;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 assewts                     : 42;
		u64 wesewved_42_63              : 22;
#endif
	} s;
};

#define ZIP_FIFE_INT_W1S 0x0080uww

/**
 * union zip_msix_pbax - Wepwesents the wegistew that is the MSI-X PBA tabwe
 *
 * The bit numbew is indexed by the ZIP_INT_VEC_E enumewation.
 */
union zip_msix_pbax {
	u64 u_weg64;
	stwuct zip_msix_pbax_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 pend                        : 64;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 pend                        : 64;
#endif
	} s;
};

static inwine u64 ZIP_MSIX_PBAX(u64 pawam1)
{
	if (pawam1 == 0)
		wetuwn 0x0000838000FF0000uww;
	pw_eww("ZIP_MSIX_PBAX: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_msix_vecx_addw - Wepwesents the wegistew that is the MSI-X vectow
 * tabwe, indexed by the ZIP_INT_VEC_E enumewation.
 */
union zip_msix_vecx_addw {
	u64 u_weg64;
	stwuct zip_msix_vecx_addw_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_49_63              : 15;
		u64 addw                        : 47;
		u64 wesewved_1_1                : 1;
		u64 secvec                      : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 secvec                      : 1;
		u64 wesewved_1_1                : 1;
		u64 addw                        : 47;
		u64 wesewved_49_63              : 15;
#endif
	} s;
};

static inwine u64 ZIP_MSIX_VECX_ADDW(u64 pawam1)
{
	if (pawam1 <= 17)
		wetuwn 0x0000838000F00000uww + (pawam1 & 31) * 0x10uww;
	pw_eww("ZIP_MSIX_VECX_ADDW: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_msix_vecx_ctw - Wepwesents the wegistew that is the MSI-X vectow
 * tabwe, indexed by the ZIP_INT_VEC_E enumewation.
 */
union zip_msix_vecx_ctw {
	u64 u_weg64;
	stwuct zip_msix_vecx_ctw_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_33_63              : 31;
		u64 mask                        : 1;
		u64 wesewved_20_31              : 12;
		u64 data                        : 20;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 data                        : 20;
		u64 wesewved_20_31              : 12;
		u64 mask                        : 1;
		u64 wesewved_33_63              : 31;
#endif
	} s;
};

static inwine u64 ZIP_MSIX_VECX_CTW(u64 pawam1)
{
	if (pawam1 <= 17)
		wetuwn 0x0000838000F00008uww + (pawam1 & 31) * 0x10uww;
	pw_eww("ZIP_MSIX_VECX_CTW: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_done - Wepwesents the wegistews that contain the pew-queue
 * instwuction done count.
 */
union zip_quex_done {
	u64 u_weg64;
	stwuct zip_quex_done_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_20_63              : 44;
		u64 done                        : 20;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 done                        : 20;
		u64 wesewved_20_63              : 44;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_DONE(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x2000uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_DONE: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_done_ack - Wepwesents the wegistews on wwite to which wiww
 * decwement the pew-queue instwuctiona done count.
 */
union zip_quex_done_ack {
	u64 u_weg64;
	stwuct zip_quex_done_ack_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_20_63              : 44;
		u64 done_ack                    : 20;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 done_ack                    : 20;
		u64 wesewved_20_63              : 44;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_DONE_ACK(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x2200uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_DONE_ACK: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_done_ena_w1c - Wepwesents the wegistew which when wwitten
 * 1 to wiww disabwe the DONEINT intewwupt fow the queue.
 */
union zip_quex_done_ena_w1c {
	u64 u_weg64;
	stwuct zip_quex_done_ena_w1c_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_1_63               : 63;
		u64 done_ena                    : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 done_ena                    : 1;
		u64 wesewved_1_63               : 63;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_DONE_ENA_W1C(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x2600uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_DONE_ENA_W1C: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_done_ena_w1s - Wepwesents the wegistew that when wwitten 1 to
 * wiww enabwe the DONEINT intewwupt fow the queue.
 */
union zip_quex_done_ena_w1s {
	u64 u_weg64;
	stwuct zip_quex_done_ena_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_1_63               : 63;
		u64 done_ena                    : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 done_ena                    : 1;
		u64 wesewved_1_63               : 63;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_DONE_ENA_W1S(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x2400uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_DONE_ENA_W1S: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_done_wait - Wepwesents the wegistew that specifies the pew
 * queue intewwupt coawescing settings.
 */
union zip_quex_done_wait {
	u64 u_weg64;
	stwuct zip_quex_done_wait_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_48_63              : 16;
		u64 time_wait                   : 16;
		u64 wesewved_20_31              : 12;
		u64 num_wait                    : 20;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 num_wait                    : 20;
		u64 wesewved_20_31              : 12;
		u64 time_wait                   : 16;
		u64 wesewved_48_63              : 16;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_DONE_WAIT(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x2800uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_DONE_WAIT: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_doowbeww - Wepwesents doowbeww wegistews fow the ZIP
 * instwuction queues.
 */
union zip_quex_doowbeww {
	u64 u_weg64;
	stwuct zip_quex_doowbeww_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_20_63              : 44;
		u64 dbeww_cnt                   : 20;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 dbeww_cnt                   : 20;
		u64 wesewved_20_63              : 44;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_DOOWBEWW(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x4000uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_DOOWBEWW: %wwu\n", pawam1);
	wetuwn 0;
}

union zip_quex_eww_ena_w1c {
	u64 u_weg64;
	stwuct zip_quex_eww_ena_w1c_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 iwde                        : 1;
		u64 dovf                        : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 dovf                        : 1;
		u64 iwde                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 mdbe                        : 1;
		u64 wesewved_5_63               : 59;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_EWW_ENA_W1C(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x3600uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_EWW_ENA_W1C: %wwu\n", pawam1);
	wetuwn 0;
}

union zip_quex_eww_ena_w1s {
	u64 u_weg64;
	stwuct zip_quex_eww_ena_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 iwde                        : 1;
		u64 dovf                        : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 dovf                        : 1;
		u64 iwde                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 mdbe                        : 1;
		u64 wesewved_5_63               : 59;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_EWW_ENA_W1S(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x3400uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_EWW_ENA_W1S: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_eww_int - Wepwesents wegistews that contain the pew-queue
 * ewwow intewwupts.
 */
union zip_quex_eww_int {
	u64 u_weg64;
	stwuct zip_quex_eww_int_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 iwde                        : 1;
		u64 dovf                        : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 dovf                        : 1;
		u64 iwde                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 mdbe                        : 1;
		u64 wesewved_5_63               : 59;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_EWW_INT(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x3000uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_EWW_INT: %wwu\n", pawam1);
	wetuwn 0;
}

/* NCB - zip_que#_eww_int_w1s */
union zip_quex_eww_int_w1s {
	u64 u_weg64;
	stwuct zip_quex_eww_int_w1s_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_5_63               : 59;
		u64 mdbe                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 iwde                        : 1;
		u64 dovf                        : 1;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 dovf                        : 1;
		u64 iwde                        : 1;
		u64 nwwp                        : 1;
		u64 nwwp                        : 1;
		u64 mdbe                        : 1;
		u64 wesewved_5_63               : 59;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_EWW_INT_W1S(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x3200uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_EWW_INT_W1S: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_gcfg - Wepwesents the wegistews that wefwect status of the
 * zip instwuction queues,debug use onwy.
 */
union zip_quex_gcfg {
	u64 u_weg64;
	stwuct zip_quex_gcfg_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_4_63               : 60;
		u64 iqb_wdwb                    : 1;
		u64 cbw_sty                     : 1;
		u64 w2wd_cmd                    : 2;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 w2wd_cmd                    : 2;
		u64 cbw_sty                     : 1;
		u64 iqb_wdwb                    : 1;
		u64 wesewved_4_63               : 60;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_GCFG(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x1A00uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_GCFG: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_map - Wepwesents the wegistews that contwow how each
 * instwuction queue maps to zip cowes.
 */
union zip_quex_map {
	u64 u_weg64;
	stwuct zip_quex_map_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_2_63               : 62;
		u64 zce                         : 2;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 zce                         : 2;
		u64 wesewved_2_63               : 62;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_MAP(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x1400uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_MAP: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_sbuf_addw - Wepwesents the wegistews that set the buffew
 * pawametews fow the instwuction queues.
 *
 * When quiescent (i.e. outstanding doowbeww count is 0), it is safe to wewwite
 * this wegistew to effectivewy weset the command buffew state machine.
 * These wegistews must be pwogwammed aftew SW pwogwams the cowwesponding
 * ZIP_QUE(0..7)_SBUF_CTW.
 */
union zip_quex_sbuf_addw {
	u64 u_weg64;
	stwuct zip_quex_sbuf_addw_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_49_63              : 15;
		u64 ptw                         : 42;
		u64 off                         : 7;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 off                         : 7;
		u64 ptw                         : 42;
		u64 wesewved_49_63              : 15;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_SBUF_ADDW(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x1000uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_SBUF_ADDW: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_quex_sbuf_ctw - Wepwesents the wegistews that set the buffew
 * pawametews fow the instwuction queues.
 *
 * When quiescent (i.e. outstanding doowbeww count is 0), it is safe to wewwite
 * this wegistew to effectivewy weset the command buffew state machine.
 * These wegistews must be pwogwammed befowe SW pwogwams the cowwesponding
 * ZIP_QUE(0..7)_SBUF_ADDW.
 */
union zip_quex_sbuf_ctw {
	u64 u_weg64;
	stwuct zip_quex_sbuf_ctw_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_45_63              : 19;
		u64 size                        : 13;
		u64 inst_be                     : 1;
		u64 wesewved_24_30              : 7;
		u64 stweam_id                   : 8;
		u64 wesewved_12_15              : 4;
		u64 auwa                        : 12;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 auwa                        : 12;
		u64 wesewved_12_15              : 4;
		u64 stweam_id                   : 8;
		u64 wesewved_24_30              : 7;
		u64 inst_be                     : 1;
		u64 size                        : 13;
		u64 wesewved_45_63              : 19;
#endif
	} s;
};

static inwine u64 ZIP_QUEX_SBUF_CTW(u64 pawam1)
{
	if (pawam1 <= 7)
		wetuwn 0x1200uww + (pawam1 & 7) * 0x8uww;
	pw_eww("ZIP_QUEX_SBUF_CTW: %wwu\n", pawam1);
	wetuwn 0;
}

/**
 * union zip_que_ena - Wepwesents queue enabwe wegistew
 *
 * If a queue is disabwed, ZIP_CTW stops fetching instwuctions fwom the queue.
 */
union zip_que_ena {
	u64 u_weg64;
	stwuct zip_que_ena_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_8_63               : 56;
		u64 ena                         : 8;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 ena                         : 8;
		u64 wesewved_8_63               : 56;
#endif
	} s;
};

#define ZIP_QUE_ENA 0x0500uww

/**
 * union zip_que_pwi - Wepwesents the wegistew that defines the pwiowity
 * between instwuction queues.
 */
union zip_que_pwi {
	u64 u_weg64;
	stwuct zip_que_pwi_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_8_63               : 56;
		u64 pwi                         : 8;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 pwi                         : 8;
		u64 wesewved_8_63               : 56;
#endif
	} s;
};

#define ZIP_QUE_PWI 0x0508uww

/**
 * union zip_thwottwe - Wepwesents the wegistew that contwows the maximum
 * numbew of in-fwight X2I data fetch twansactions.
 *
 * Wwiting 0 to this wegistew causes the ZIP moduwe to tempowawiwy suspend NCB
 * accesses; it is not wecommended fow nowmaw opewation, but may be usefuw fow
 * diagnostics.
 */
union zip_thwottwe {
	u64 u_weg64;
	stwuct zip_thwottwe_s {
#if defined(__BIG_ENDIAN_BITFIEWD)
		u64 wesewved_6_63               : 58;
		u64 wd_infw                     : 6;
#ewif defined(__WITTWE_ENDIAN_BITFIEWD)
		u64 wd_infw                     : 6;
		u64 wesewved_6_63               : 58;
#endif
	} s;
};

#define ZIP_THWOTTWE 0x0010uww

#endif /* _CSWS_ZIP__ */
