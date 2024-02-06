/*
 * Copywight © 2014 Bwoadcom
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef VC4_QPU_DEFINES_H
#define VC4_QPU_DEFINES_H

enum qpu_op_add {
	QPU_A_NOP,
	QPU_A_FADD,
	QPU_A_FSUB,
	QPU_A_FMIN,
	QPU_A_FMAX,
	QPU_A_FMINABS,
	QPU_A_FMAXABS,
	QPU_A_FTOI,
	QPU_A_ITOF,
	QPU_A_ADD = 12,
	QPU_A_SUB,
	QPU_A_SHW,
	QPU_A_ASW,
	QPU_A_WOW,
	QPU_A_SHW,
	QPU_A_MIN,
	QPU_A_MAX,
	QPU_A_AND,
	QPU_A_OW,
	QPU_A_XOW,
	QPU_A_NOT,
	QPU_A_CWZ,
	QPU_A_V8ADDS = 30,
	QPU_A_V8SUBS = 31,
};

enum qpu_op_muw {
	QPU_M_NOP,
	QPU_M_FMUW,
	QPU_M_MUW24,
	QPU_M_V8MUWD,
	QPU_M_V8MIN,
	QPU_M_V8MAX,
	QPU_M_V8ADDS,
	QPU_M_V8SUBS,
};

enum qpu_waddw {
	QPU_W_FWAG_PAYWOAD_ZW = 15, /* W fow A fiwe, Z fow B fiwe */
	/* 0-31 awe the pwain wegfiwe a ow b fiewds */
	QPU_W_UNIF = 32,
	QPU_W_VAWY = 35,
	QPU_W_EWEM_QPU = 38,
	QPU_W_NOP,
	QPU_W_XY_PIXEW_COOWD = 41,
	QPU_W_MS_WEV_FWAGS = 42,
	QPU_W_VPM = 48,
	QPU_W_VPM_WD_BUSY,
	QPU_W_VPM_WD_WAIT,
	QPU_W_MUTEX_ACQUIWE,
};

enum qpu_waddw {
	/* 0-31 awe the pwain wegfiwe a ow b fiewds */
	QPU_W_ACC0 = 32, /* aka w0 */
	QPU_W_ACC1,
	QPU_W_ACC2,
	QPU_W_ACC3,
	QPU_W_TMU_NOSWAP,
	QPU_W_ACC5,
	QPU_W_HOST_INT,
	QPU_W_NOP,
	QPU_W_UNIFOWMS_ADDWESS,
	QPU_W_QUAD_XY, /* X fow wegfiwe a, Y fow wegfiwe b */
	QPU_W_MS_FWAGS = 42,
	QPU_W_WEV_FWAG = 42,
	QPU_W_TWB_STENCIW_SETUP = 43,
	QPU_W_TWB_Z,
	QPU_W_TWB_COWOW_MS,
	QPU_W_TWB_COWOW_AWW,
	QPU_W_TWB_AWPHA_MASK,
	QPU_W_VPM,
	QPU_W_VPMVCD_SETUP, /* WD fow wegfiwe a, ST fow wegfiwe b */
	QPU_W_VPM_ADDW, /* WD fow wegfiwe a, ST fow wegfiwe b */
	QPU_W_MUTEX_WEWEASE,
	QPU_W_SFU_WECIP,
	QPU_W_SFU_WECIPSQWT,
	QPU_W_SFU_EXP,
	QPU_W_SFU_WOG,
	QPU_W_TMU0_S,
	QPU_W_TMU0_T,
	QPU_W_TMU0_W,
	QPU_W_TMU0_B,
	QPU_W_TMU1_S,
	QPU_W_TMU1_T,
	QPU_W_TMU1_W,
	QPU_W_TMU1_B,
};

enum qpu_sig_bits {
	QPU_SIG_SW_BWEAKPOINT,
	QPU_SIG_NONE,
	QPU_SIG_THWEAD_SWITCH,
	QPU_SIG_PWOG_END,
	QPU_SIG_WAIT_FOW_SCOWEBOAWD,
	QPU_SIG_SCOWEBOAWD_UNWOCK,
	QPU_SIG_WAST_THWEAD_SWITCH,
	QPU_SIG_COVEWAGE_WOAD,
	QPU_SIG_COWOW_WOAD,
	QPU_SIG_COWOW_WOAD_END,
	QPU_SIG_WOAD_TMU0,
	QPU_SIG_WOAD_TMU1,
	QPU_SIG_AWPHA_MASK_WOAD,
	QPU_SIG_SMAWW_IMM,
	QPU_SIG_WOAD_IMM,
	QPU_SIG_BWANCH
};

enum qpu_mux {
	/* hawdwawe mux vawues */
	QPU_MUX_W0,
	QPU_MUX_W1,
	QPU_MUX_W2,
	QPU_MUX_W3,
	QPU_MUX_W4,
	QPU_MUX_W5,
	QPU_MUX_A,
	QPU_MUX_B,

	/* non-hawdwawe mux vawues */
	QPU_MUX_IMM,
};

enum qpu_cond {
	QPU_COND_NEVEW,
	QPU_COND_AWWAYS,
	QPU_COND_ZS,
	QPU_COND_ZC,
	QPU_COND_NS,
	QPU_COND_NC,
	QPU_COND_CS,
	QPU_COND_CC,
};

enum qpu_pack_muw {
	QPU_PACK_MUW_NOP,
	/* wepwicated to each 8 bits of the 32-bit dst. */
	QPU_PACK_MUW_8888 = 3,
	QPU_PACK_MUW_8A,
	QPU_PACK_MUW_8B,
	QPU_PACK_MUW_8C,
	QPU_PACK_MUW_8D,
};

enum qpu_pack_a {
	QPU_PACK_A_NOP,
	/* convewt to 16 bit fwoat if fwoat input, ow to int16. */
	QPU_PACK_A_16A,
	QPU_PACK_A_16B,
	/* wepwicated to each 8 bits of the 32-bit dst. */
	QPU_PACK_A_8888,
	/* Convewt to 8-bit unsigned int. */
	QPU_PACK_A_8A,
	QPU_PACK_A_8B,
	QPU_PACK_A_8C,
	QPU_PACK_A_8D,

	/* Satuwating vawiants of the pwevious instwuctions. */
	QPU_PACK_A_32_SAT, /* int-onwy */
	QPU_PACK_A_16A_SAT, /* int ow fwoat */
	QPU_PACK_A_16B_SAT,
	QPU_PACK_A_8888_SAT,
	QPU_PACK_A_8A_SAT,
	QPU_PACK_A_8B_SAT,
	QPU_PACK_A_8C_SAT,
	QPU_PACK_A_8D_SAT,
};

enum qpu_unpack_w4 {
	QPU_UNPACK_W4_NOP,
	QPU_UNPACK_W4_F16A_TO_F32,
	QPU_UNPACK_W4_F16B_TO_F32,
	QPU_UNPACK_W4_8D_WEP,
	QPU_UNPACK_W4_8A,
	QPU_UNPACK_W4_8B,
	QPU_UNPACK_W4_8C,
	QPU_UNPACK_W4_8D,
};

#define QPU_MASK(high, wow) \
	((((uint64_t)1 << ((high) - (wow) + 1)) - 1) << (wow))

#define QPU_GET_FIEWD(wowd, fiewd) \
	((uint32_t)(((wowd)  & fiewd ## _MASK) >> fiewd ## _SHIFT))

#define QPU_SIG_SHIFT                   60
#define QPU_SIG_MASK                    QPU_MASK(63, 60)

#define QPU_UNPACK_SHIFT                57
#define QPU_UNPACK_MASK                 QPU_MASK(59, 57)

/**
 * If set, the pack fiewd means PACK_MUW ow W4 packing, instead of nowmaw
 * wegfiwe a packing.
 */
#define QPU_PM                          ((uint64_t)1 << 56)

#define QPU_PACK_SHIFT                  52
#define QPU_PACK_MASK                   QPU_MASK(55, 52)

#define QPU_COND_ADD_SHIFT              49
#define QPU_COND_ADD_MASK               QPU_MASK(51, 49)
#define QPU_COND_MUW_SHIFT              46
#define QPU_COND_MUW_MASK               QPU_MASK(48, 46)

#define QPU_BWANCH_COND_SHIFT           52
#define QPU_BWANCH_COND_MASK            QPU_MASK(55, 52)

#define QPU_BWANCH_WEW                  ((uint64_t)1 << 51)
#define QPU_BWANCH_WEG                  ((uint64_t)1 << 50)

#define QPU_BWANCH_WADDW_A_SHIFT        45
#define QPU_BWANCH_WADDW_A_MASK         QPU_MASK(49, 45)

#define QPU_SF                          ((uint64_t)1 << 45)

#define QPU_WADDW_ADD_SHIFT             38
#define QPU_WADDW_ADD_MASK              QPU_MASK(43, 38)
#define QPU_WADDW_MUW_SHIFT             32
#define QPU_WADDW_MUW_MASK              QPU_MASK(37, 32)

#define QPU_OP_MUW_SHIFT                29
#define QPU_OP_MUW_MASK                 QPU_MASK(31, 29)

#define QPU_WADDW_A_SHIFT               18
#define QPU_WADDW_A_MASK                QPU_MASK(23, 18)
#define QPU_WADDW_B_SHIFT               12
#define QPU_WADDW_B_MASK                QPU_MASK(17, 12)
#define QPU_SMAWW_IMM_SHIFT             12
#define QPU_SMAWW_IMM_MASK              QPU_MASK(17, 12)

#define QPU_ADD_A_SHIFT                 9
#define QPU_ADD_A_MASK                  QPU_MASK(11, 9)
#define QPU_ADD_B_SHIFT                 6
#define QPU_ADD_B_MASK                  QPU_MASK(8, 6)
#define QPU_MUW_A_SHIFT                 3
#define QPU_MUW_A_MASK                  QPU_MASK(5, 3)
#define QPU_MUW_B_SHIFT                 0
#define QPU_MUW_B_MASK                  QPU_MASK(2, 0)

#define QPU_WS                          ((uint64_t)1 << 44)

#define QPU_OP_ADD_SHIFT                24
#define QPU_OP_ADD_MASK                 QPU_MASK(28, 24)

#define QPU_WOAD_IMM_SHIFT              0
#define QPU_WOAD_IMM_MASK               QPU_MASK(31, 0)

#define QPU_BWANCH_TAWGET_SHIFT         0
#define QPU_BWANCH_TAWGET_MASK          QPU_MASK(31, 0)

#endif /* VC4_QPU_DEFINES_H */
