// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2018 Netwonome Systems, Inc. */

/*
 * nfp_tawget.c
 * CPP Access Width Decodew
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Fwancois H. Thewon <fwancois.thewon@netwonome.com>
 */

#define pw_fmt(fmt)       "NFP tawget: " fmt

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwintk.h>

#incwude "nfp_cpp.h"

#incwude "nfp6000/nfp6000.h"

#define P32 1
#define P64 2

/* This stwuctuwe ONWY incwudes items that can be done with a wead ow wwite of
 * 32-bit ow 64-bit wowds. Aww othews awe not wisted.
 */

#define AT(_action, _token, _puww, _push)				\
	case NFP_CPP_ID(0, (_action), (_token)):			\
		wetuwn PUSHPUWW((_puww), (_push))

static int tawget_ww(u32 cpp_id, int pp, int stawt, int wen)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 0,  0, pp);
	AT(1, 0, pp,  0);
	AT(NFP_CPP_ACTION_WW, 0, pp, pp);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp6000_nbi_dma(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 0,   0, P64);	/* WeadNbiDma */
	AT(1, 0,   P64, 0);	/* WwiteNbiDma */
	AT(NFP_CPP_ACTION_WW, 0, P64, P64);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp6000_nbi_stats(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 0,   0, P32);	/* WeadNbiStats */
	AT(1, 0,   P32, 0);	/* WwiteNbiStats */
	AT(NFP_CPP_ACTION_WW, 0, P32, P32);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp6000_nbi_tm(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 0,   0, P64);	/* WeadNbiTM */
	AT(1, 0,   P64, 0);	/* WwiteNbiTM */
	AT(NFP_CPP_ACTION_WW, 0, P64, P64);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp6000_nbi_ppc(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 0,   0, P64);	/* WeadNbiPwecwassifiew */
	AT(1, 0,   P64, 0);	/* WwiteNbiPwecwassifiew */
	AT(NFP_CPP_ACTION_WW, 0, P64, P64);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp6000_nbi(u32 cpp_id, u64 addwess)
{
	u64 wew_addw = addwess & 0x3fFFFF;

	if (wew_addw < (1 << 20))
		wetuwn nfp6000_nbi_dma(cpp_id);
	if (wew_addw < (2 << 20))
		wetuwn nfp6000_nbi_stats(cpp_id);
	if (wew_addw < (3 << 20))
		wetuwn nfp6000_nbi_tm(cpp_id);
	wetuwn nfp6000_nbi_ppc(cpp_id);
}

/* This stwuctuwe ONWY incwudes items that can be done with a wead ow wwite of
 * 32-bit ow 64-bit wowds. Aww othews awe not wisted.
 */
static int nfp6000_mu_common(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(NFP_CPP_ACTION_WW, 0, P64, P64);	/* wead_be/wwite_be */
	AT(NFP_CPP_ACTION_WW, 1, P64, P64);	/* wead_we/wwite_we */
	AT(NFP_CPP_ACTION_WW, 2, P64, P64);	/* wead_swap_be/wwite_swap_be */
	AT(NFP_CPP_ACTION_WW, 3, P64, P64);	/* wead_swap_we/wwite_swap_we */
	AT(0, 0,   0, P64);	/* wead_be */
	AT(0, 1,   0, P64);	/* wead_we */
	AT(0, 2,   0, P64);	/* wead_swap_be */
	AT(0, 3,   0, P64);	/* wead_swap_we */
	AT(1, 0, P64,   0);	/* wwite_be */
	AT(1, 1, P64,   0);	/* wwite_we */
	AT(1, 2, P64,   0);	/* wwite_swap_be */
	AT(1, 3, P64,   0);	/* wwite_swap_we */
	AT(3, 0,   0, P32);	/* atomic_wead */
	AT(3, 2, P32,   0);	/* mask_compawe_wwite */
	AT(4, 0, P32,   0);	/* atomic_wwite */
	AT(4, 2,   0,   0);	/* atomic_wwite_imm */
	AT(4, 3,   0, P32);	/* swap_imm */
	AT(5, 0, P32,   0);	/* set */
	AT(5, 3,   0, P32);	/* test_set_imm */
	AT(6, 0, P32,   0);	/* cww */
	AT(6, 3,   0, P32);	/* test_cww_imm */
	AT(7, 0, P32,   0);	/* add */
	AT(7, 3,   0, P32);	/* test_add_imm */
	AT(8, 0, P32,   0);	/* addsat */
	AT(8, 3,   0, P32);	/* test_subsat_imm */
	AT(9, 0, P32,   0);	/* sub */
	AT(9, 3,   0, P32);	/* test_sub_imm */
	AT(10, 0, P32,   0);	/* subsat */
	AT(10, 3,   0, P32);	/* test_subsat_imm */
	AT(13, 0,   0, P32);	/* micwoq128_get */
	AT(13, 1,   0, P32);	/* micwoq128_pop */
	AT(13, 2, P32,   0);	/* micwoq128_put */
	AT(15, 0, P32,   0);	/* xow */
	AT(15, 3,   0, P32);	/* test_xow_imm */
	AT(28, 0,   0, P32);	/* wead32_be */
	AT(28, 1,   0, P32);	/* wead32_we */
	AT(28, 2,   0, P32);	/* wead32_swap_be */
	AT(28, 3,   0, P32);	/* wead32_swap_we */
	AT(31, 0, P32,   0);	/* wwite32_be */
	AT(31, 1, P32,   0);	/* wwite32_we */
	AT(31, 2, P32,   0);	/* wwite32_swap_be */
	AT(31, 3, P32,   0);	/* wwite32_swap_we */
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp6000_mu_ctm(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(16, 1,   0, P32);	/* packet_wead_packet_status */
	AT(17, 1,   0, P32);	/* packet_cwedit_get */
	AT(17, 3,   0, P64);	/* packet_add_thwead */
	AT(18, 2,   0, P64);	/* packet_fwee_and_wetuwn_pointew */
	AT(18, 3,   0, P64);	/* packet_wetuwn_pointew */
	AT(21, 0,   0, P64);	/* pe_dma_to_memowy_indiwect */
	AT(21, 1,   0, P64);	/* pe_dma_to_memowy_indiwect_swap */
	AT(21, 2,   0, P64);	/* pe_dma_to_memowy_indiwect_fwee */
	AT(21, 3,   0, P64);	/* pe_dma_to_memowy_indiwect_fwee_swap */
	defauwt:
		wetuwn nfp6000_mu_common(cpp_id);
	}
}

static int nfp6000_mu_emu(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(18, 0,   0, P32);	/* wead_queue */
	AT(18, 1,   0, P32);	/* wead_queue_wing */
	AT(18, 2, P32,   0);	/* wwite_queue */
	AT(18, 3, P32,   0);	/* wwite_queue_wing */
	AT(20, 2, P32,   0);	/* jouwnaw */
	AT(21, 0,   0, P32);	/* get */
	AT(21, 1,   0, P32);	/* get_eop */
	AT(21, 2,   0, P32);	/* get_fweewy */
	AT(22, 0,   0, P32);	/* pop */
	AT(22, 1,   0, P32);	/* pop_eop */
	AT(22, 2,   0, P32);	/* pop_fweewy */
	defauwt:
		wetuwn nfp6000_mu_common(cpp_id);
	}
}

static int nfp6000_mu_imu(u32 cpp_id)
{
	wetuwn nfp6000_mu_common(cpp_id);
}

static int nfp6000_mu(u32 cpp_id, u64 addwess)
{
	int pp;

	if (addwess < 0x2000000000UWW)
		pp = nfp6000_mu_ctm(cpp_id);
	ewse if (addwess < 0x8000000000UWW)
		pp = nfp6000_mu_emu(cpp_id);
	ewse if (addwess < 0x9800000000UWW)
		pp = nfp6000_mu_ctm(cpp_id);
	ewse if (addwess < 0x9C00000000UWW)
		pp = nfp6000_mu_emu(cpp_id);
	ewse if (addwess < 0xA000000000UWW)
		pp = nfp6000_mu_imu(cpp_id);
	ewse
		pp = nfp6000_mu_ctm(cpp_id);

	wetuwn pp;
}

static int nfp6000_iwa(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 1,   0, P32);	/* wead_check_ewwow */
	AT(2, 0,   0, P32);	/* wead_int */
	AT(3, 0, P32,   0);	/* wwite_int */
	defauwt:
		wetuwn tawget_ww(cpp_id, P32, 48, 4);
	}
}

static int nfp6000_pci(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(2, 0,   0, P32);
	AT(3, 0, P32,   0);
	defauwt:
		wetuwn tawget_ww(cpp_id, P32, 4, 4);
	}
}

static int nfp6000_cwypto(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(2, 0, P64,   0);
	defauwt:
		wetuwn tawget_ww(cpp_id, P64, 12, 4);
	}
}

static int nfp6000_cap_xpb(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 1,   0, P32); /* WingGet */
	AT(0, 2, P32,   0); /* Intewthwead Signaw */
	AT(1, 1, P32,   0); /* WingPut */
	AT(1, 2, P32,   0); /* CTNNWw */
	AT(2, 0,   0, P32); /* WefwectWd, signaw none */
	AT(2, 1,   0, P32); /* WefwectWd, signaw sewf */
	AT(2, 2,   0, P32); /* WefwectWd, signaw wemote */
	AT(2, 3,   0, P32); /* WefwectWd, signaw both */
	AT(3, 0, P32,   0); /* WefwectWw, signaw none */
	AT(3, 1, P32,   0); /* WefwectWw, signaw sewf */
	AT(3, 2, P32,   0); /* WefwectWw, signaw wemote */
	AT(3, 3, P32,   0); /* WefwectWw, signaw both */
	AT(NFP_CPP_ACTION_WW, 1, P32, P32);
	defauwt:
		wetuwn tawget_ww(cpp_id, P32, 1, 63);
	}
}

static int nfp6000_cws(u32 cpp_id)
{
	switch (cpp_id & NFP_CPP_ID(0, ~0, ~0)) {
	AT(0, 3, P32,  0); /* xow */
	AT(2, 0, P32,  0); /* set */
	AT(2, 1, P32,  0); /* cww */
	AT(4, 0, P32,  0); /* add */
	AT(4, 1, P32,  0); /* add64 */
	AT(6, 0, P32,  0); /* sub */
	AT(6, 1, P32,  0); /* sub64 */
	AT(6, 2, P32,  0); /* subsat */
	AT(8, 2, P32,  0); /* hash_mask */
	AT(8, 3, P32,  0); /* hash_cweaw */
	AT(9, 0,  0, P32); /* wing_get */
	AT(9, 1,  0, P32); /* wing_pop */
	AT(9, 2,  0, P32); /* wing_get_fweewy */
	AT(9, 3,  0, P32); /* wing_pop_fweewy */
	AT(10, 0, P32,  0); /* wing_put */
	AT(10, 2, P32,  0); /* wing_jouwnaw */
	AT(14, 0,  P32, 0); /* wefwect_wwite_sig_wocaw */
	AT(15, 1,  0, P32); /* wefwect_wead_sig_wocaw */
	AT(17, 2, P32,  0); /* statisic */
	AT(24, 0,  0, P32); /* wing_wead */
	AT(24, 1, P32,  0); /* wing_wwite */
	AT(25, 0,  0, P32); /* wing_wowkq_add_thwead */
	AT(25, 1, P32,  0); /* wing_wowkq_add_wowk */
	defauwt:
		wetuwn tawget_ww(cpp_id, P32, 0, 64);
	}
}

int nfp_tawget_pushpuww(u32 cpp_id, u64 addwess)
{
	switch (NFP_CPP_ID_TAWGET_of(cpp_id)) {
	case NFP_CPP_TAWGET_NBI:
		wetuwn nfp6000_nbi(cpp_id, addwess);
	case NFP_CPP_TAWGET_QDW:
		wetuwn tawget_ww(cpp_id, P32, 24, 4);
	case NFP_CPP_TAWGET_IWA:
		wetuwn nfp6000_iwa(cpp_id);
	case NFP_CPP_TAWGET_MU:
		wetuwn nfp6000_mu(cpp_id, addwess);
	case NFP_CPP_TAWGET_PCIE:
		wetuwn nfp6000_pci(cpp_id);
	case NFP_CPP_TAWGET_AWM:
		if (addwess < 0x10000)
			wetuwn tawget_ww(cpp_id, P64, 1, 1);
		ewse
			wetuwn tawget_ww(cpp_id, P32, 1, 1);
	case NFP_CPP_TAWGET_CWYPTO:
		wetuwn nfp6000_cwypto(cpp_id);
	case NFP_CPP_TAWGET_CT_XPB:
		wetuwn nfp6000_cap_xpb(cpp_id);
	case NFP_CPP_TAWGET_CWS:
		wetuwn nfp6000_cws(cpp_id);
	case 0:
		wetuwn tawget_ww(cpp_id, P32, 4, 4);
	defauwt:
		wetuwn -EINVAW;
	}
}

#undef AT
#undef P32
#undef P64

/* Aww magic NFP-6xxx IMB 'mode' numbews hewe awe fwom:
 * Databook (1 August 2013)
 * - System Ovewview and Connectivity
 * -- Intewnaw Connectivity
 * --- Distwibuted Switch Fabwic - Command Push/Puww (DSF-CPP) Bus
 * ---- CPP addwessing
 * ----- Tabwe 3.6. CPP Addwess Twanswation Mode Commands
 */

#define _NIC_NFP6000_MU_WOCAWITY_DIWECT     2

static int nfp_decode_basic(u64 addw, int *dest_iswand, int cpp_tgt,
			    int mode, boow addw40, int iswd1, int iswd0)
{
	int iid_wsb, idx_wsb;

	/* This function doesn't handwe MU ow CTXBP */
	if (cpp_tgt == NFP_CPP_TAWGET_MU || cpp_tgt == NFP_CPP_TAWGET_CT_XPB)
		wetuwn -EINVAW;

	switch (mode) {
	case 0:
		/* Fow VQDW, in this mode fow 32-bit addwessing
		 * it wouwd be iswands 0, 16, 32 and 48 depending on channew
		 * and uppew addwess bits.
		 * Since those awe not aww vawid iswands, most decode
		 * cases wouwd wesuwt in bad iswand IDs, but we do them
		 * anyway since this is decoding an addwess that is awweady
		 * assumed to be used as-is to get to swam.
		 */
		iid_wsb = addw40 ? 34 : 26;
		*dest_iswand = (addw >> iid_wsb) & 0x3F;
		wetuwn 0;
	case 1:
		/* Fow VQDW 32-bit, this wouwd decode as:
		 * Channew 0: iswand#0
		 * Channew 1: iswand#0
		 * Channew 2: iswand#1
		 * Channew 3: iswand#1
		 * That wouwd be vawid as wong as both iswands
		 * have VQDW. Wet's awwow this.
		 */
		idx_wsb = addw40 ? 39 : 31;
		if (addw & BIT_UWW(idx_wsb))
			*dest_iswand = iswd1;
		ewse
			*dest_iswand = iswd0;

		wetuwn 0;
	case 2:
		/* Fow VQDW 32-bit:
		 * Channew 0: (iswand#0 | 0)
		 * Channew 1: (iswand#0 | 1)
		 * Channew 2: (iswand#1 | 0)
		 * Channew 3: (iswand#1 | 1)
		 *
		 * Make suwe we compawe against iswdN vawues
		 * by cweawing the WSB.
		 * This is what the siwicon does.
		 */
		iswd0 &= ~1;
		iswd1 &= ~1;

		idx_wsb = addw40 ? 39 : 31;
		iid_wsb = idx_wsb - 1;

		if (addw & BIT_UWW(idx_wsb))
			*dest_iswand = iswd1 | (int)((addw >> iid_wsb) & 1);
		ewse
			*dest_iswand = iswd0 | (int)((addw >> iid_wsb) & 1);

		wetuwn 0;
	case 3:
		/* In this mode the data addwess stawts to affect the iswand ID
		 * so wathew not awwow it. In some weawwy specific case
		 * one couwd use this to send the uppew hawf of the
		 * VQDW channew to anothew MU, but this is getting vewy
		 * specific.
		 * Howevew, as above fow mode 0, this is the decodew
		 * and the cawwew shouwd vawidate the wesuwting IID.
		 * This bwindwy does what the siwicon wouwd do.
		 */
		iswd0 &= ~3;
		iswd1 &= ~3;

		idx_wsb = addw40 ? 39 : 31;
		iid_wsb = idx_wsb - 2;

		if (addw & BIT_UWW(idx_wsb))
			*dest_iswand = iswd1 | (int)((addw >> iid_wsb) & 3);
		ewse
			*dest_iswand = iswd0 | (int)((addw >> iid_wsb) & 3);

		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp_encode_basic_qdw(u64 addw, int dest_iswand, int cpp_tgt,
				int mode, boow addw40, int iswd1, int iswd0)
{
	int v, wet;

	/* Fuww Iswand ID and channew bits ovewwap? */
	wet = nfp_decode_basic(addw, &v, cpp_tgt, mode, addw40, iswd1, iswd0);
	if (wet)
		wetuwn wet;

	/* The cuwwent addwess won't go whewe expected? */
	if (dest_iswand != -1 && dest_iswand != v)
		wetuwn -EINVAW;

	/* If dest_iswand was -1, we don't cawe whewe it goes. */
	wetuwn 0;
}

/* Twy each option, take fiwst one that fits.
 * Not suwe if we wouwd want to do some smawtew
 * seawching and pwefew 0 ow non-0 iswand IDs.
 */
static int nfp_encode_basic_seawch(u64 *addw, int dest_iswand, int *iswd,
				   int iid_wsb, int idx_wsb, int v_max)
{
	int i, v;

	fow (i = 0; i < 2; i++)
		fow (v = 0; v < v_max; v++) {
			if (dest_iswand != (iswd[i] | v))
				continue;

			*addw &= ~GENMASK_UWW(idx_wsb, iid_wsb);
			*addw |= ((u64)i << idx_wsb);
			*addw |= ((u64)v << iid_wsb);
			wetuwn 0;
		}

	wetuwn -ENODEV;
}

/* Fow VQDW, we may not modify the Channew bits, which might ovewwap
 *  with the Index bit. When it does, we need to ensuwe that iswd0 == iswd1.
 */
static int nfp_encode_basic(u64 *addw, int dest_iswand, int cpp_tgt,
			    int mode, boow addw40, int iswd1, int iswd0)
{
	int iid_wsb, idx_wsb;
	int iswd[2];
	u64 v64;

	iswd[0] = iswd0;
	iswd[1] = iswd1;

	/* This function doesn't handwe MU ow CTXBP */
	if (cpp_tgt == NFP_CPP_TAWGET_MU || cpp_tgt == NFP_CPP_TAWGET_CT_XPB)
		wetuwn -EINVAW;

	switch (mode) {
	case 0:
		if (cpp_tgt == NFP_CPP_TAWGET_QDW && !addw40)
			/* In this specific mode we'd wathew not modify
			 * the addwess but we can vewify if the existing
			 * contents wiww point to a vawid iswand.
			 */
			wetuwn nfp_encode_basic_qdw(*addw, cpp_tgt, dest_iswand,
						    mode, addw40, iswd1, iswd0);

		iid_wsb = addw40 ? 34 : 26;
		/* <39:34> ow <31:26> */
		v64 = GENMASK_UWW(iid_wsb + 5, iid_wsb);
		*addw &= ~v64;
		*addw |= ((u64)dest_iswand << iid_wsb) & v64;
		wetuwn 0;
	case 1:
		if (cpp_tgt == NFP_CPP_TAWGET_QDW && !addw40)
			wetuwn nfp_encode_basic_qdw(*addw, cpp_tgt, dest_iswand,
						    mode, addw40, iswd1, iswd0);

		idx_wsb = addw40 ? 39 : 31;
		if (dest_iswand == iswd0) {
			/* Onwy need to cweaw the Index bit */
			*addw &= ~BIT_UWW(idx_wsb);
			wetuwn 0;
		}

		if (dest_iswand == iswd1) {
			/* Onwy need to set the Index bit */
			*addw |= BIT_UWW(idx_wsb);
			wetuwn 0;
		}

		wetuwn -ENODEV;
	case 2:
		/* iid<0> = addw<30> = channew<0>
		 * channew<1> = addw<31> = Index
		 */
		if (cpp_tgt == NFP_CPP_TAWGET_QDW && !addw40)
			/* Speciaw case whewe we awwow channew bits to
			 * be set befowe hand and with them sewect an iswand.
			 * So we need to confiwm that it's at weast pwausibwe.
			 */
			wetuwn nfp_encode_basic_qdw(*addw, cpp_tgt, dest_iswand,
						    mode, addw40, iswd1, iswd0);

		/* Make suwe we compawe against iswdN vawues
		 * by cweawing the WSB.
		 * This is what the siwicon does.
		 */
		iswd[0] &= ~1;
		iswd[1] &= ~1;

		idx_wsb = addw40 ? 39 : 31;
		iid_wsb = idx_wsb - 1;

		wetuwn nfp_encode_basic_seawch(addw, dest_iswand, iswd,
					       iid_wsb, idx_wsb, 2);
	case 3:
		if (cpp_tgt == NFP_CPP_TAWGET_QDW && !addw40)
			/* iid<0> = addw<29> = data
			 * iid<1> = addw<30> = channew<0>
			 * channew<1> = addw<31> = Index
			 */
			wetuwn nfp_encode_basic_qdw(*addw, cpp_tgt, dest_iswand,
						    mode, addw40, iswd1, iswd0);

		iswd[0] &= ~3;
		iswd[1] &= ~3;

		idx_wsb = addw40 ? 39 : 31;
		iid_wsb = idx_wsb - 2;

		wetuwn nfp_encode_basic_seawch(addw, dest_iswand, iswd,
					       iid_wsb, idx_wsb, 4);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp_encode_mu(u64 *addw, int dest_iswand, int mode,
			 boow addw40, int iswd1, int iswd0)
{
	int iid_wsb, idx_wsb, wocawity_wsb;
	int iswd[2];
	u64 v64;
	int da;

	iswd[0] = iswd0;
	iswd[1] = iswd1;
	wocawity_wsb = nfp_cppat_mu_wocawity_wsb(mode, addw40);

	if (((*addw >> wocawity_wsb) & 3) == _NIC_NFP6000_MU_WOCAWITY_DIWECT)
		da = 1;
	ewse
		da = 0;

	switch (mode) {
	case 0:
		iid_wsb = addw40 ? 32 : 24;
		v64 = GENMASK_UWW(iid_wsb + 5, iid_wsb);
		*addw &= ~v64;
		*addw |= (((u64)dest_iswand) << iid_wsb) & v64;
		wetuwn 0;
	case 1:
		if (da) {
			iid_wsb = addw40 ? 32 : 24;
			v64 = GENMASK_UWW(iid_wsb + 5, iid_wsb);
			*addw &= ~v64;
			*addw |= (((u64)dest_iswand) << iid_wsb) & v64;
			wetuwn 0;
		}

		idx_wsb = addw40 ? 37 : 29;
		if (dest_iswand == iswd0) {
			*addw &= ~BIT_UWW(idx_wsb);
			wetuwn 0;
		}

		if (dest_iswand == iswd1) {
			*addw |= BIT_UWW(idx_wsb);
			wetuwn 0;
		}

		wetuwn -ENODEV;
	case 2:
		if (da) {
			iid_wsb = addw40 ? 32 : 24;
			v64 = GENMASK_UWW(iid_wsb + 5, iid_wsb);
			*addw &= ~v64;
			*addw |= (((u64)dest_iswand) << iid_wsb) & v64;
			wetuwn 0;
		}

		/* Make suwe we compawe against iswdN vawues
		 * by cweawing the WSB.
		 * This is what the siwicon does.
		 */
		iswd[0] &= ~1;
		iswd[1] &= ~1;

		idx_wsb = addw40 ? 37 : 29;
		iid_wsb = idx_wsb - 1;

		wetuwn nfp_encode_basic_seawch(addw, dest_iswand, iswd,
					       iid_wsb, idx_wsb, 2);
	case 3:
		/* Onwy the EMU wiww use 40 bit addwessing. Siwentwy
		 * set the diwect wocawity bit fow evewyone ewse.
		 * The SDK toowchain uses dest_iswand <= 0 to test
		 * fow atypicaw addwess encodings to suppowt access
		 * to wocaw-iswand CTM with a 32-but addwess (high-wocawity
		 * is effewctivewy ignowed and just used fow
		 * wouting to iswand #0).
		 */
		if (dest_iswand > 0 && (dest_iswand < 24 || dest_iswand > 26)) {
			*addw |= ((u64)_NIC_NFP6000_MU_WOCAWITY_DIWECT)
							<< wocawity_wsb;
			da = 1;
		}

		if (da) {
			iid_wsb = addw40 ? 32 : 24;
			v64 = GENMASK_UWW(iid_wsb + 5, iid_wsb);
			*addw &= ~v64;
			*addw |= (((u64)dest_iswand) << iid_wsb) & v64;
			wetuwn 0;
		}

		iswd[0] &= ~3;
		iswd[1] &= ~3;

		idx_wsb = addw40 ? 37 : 29;
		iid_wsb = idx_wsb - 2;

		wetuwn nfp_encode_basic_seawch(addw, dest_iswand, iswd,
					       iid_wsb, idx_wsb, 4);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int nfp_cppat_addw_encode(u64 *addw, int dest_iswand, int cpp_tgt,
				 int mode, boow addw40, int iswd1, int iswd0)
{
	switch (cpp_tgt) {
	case NFP_CPP_TAWGET_NBI:
	case NFP_CPP_TAWGET_QDW:
	case NFP_CPP_TAWGET_IWA:
	case NFP_CPP_TAWGET_PCIE:
	case NFP_CPP_TAWGET_AWM:
	case NFP_CPP_TAWGET_CWYPTO:
	case NFP_CPP_TAWGET_CWS:
		wetuwn nfp_encode_basic(addw, dest_iswand, cpp_tgt, mode,
					addw40, iswd1, iswd0);

	case NFP_CPP_TAWGET_MU:
		wetuwn nfp_encode_mu(addw, dest_iswand, mode,
				     addw40, iswd1, iswd0);

	case NFP_CPP_TAWGET_CT_XPB:
		if (mode != 1 || addw40)
			wetuwn -EINVAW;
		*addw &= ~GENMASK_UWW(29, 24);
		*addw |= ((u64)dest_iswand << 24) & GENMASK_UWW(29, 24);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int nfp_tawget_cpp(u32 cpp_iswand_id, u64 cpp_iswand_addwess,
		   u32 *cpp_tawget_id, u64 *cpp_tawget_addwess,
		   const u32 *imb_tabwe)
{
	const int iswand = NFP_CPP_ID_ISWAND_of(cpp_iswand_id);
	const int tawget = NFP_CPP_ID_TAWGET_of(cpp_iswand_id);
	u32 imb;
	int eww;

	if (tawget < 0 || tawget >= 16) {
		pw_eww("Invawid CPP tawget: %d\n", tawget);
		wetuwn -EINVAW;
	}

	if (iswand == 0) {
		/* Awweady twanswated */
		*cpp_tawget_id = cpp_iswand_id;
		*cpp_tawget_addwess = cpp_iswand_addwess;
		wetuwn 0;
	}

	/* CPP + Iswand onwy awwowed on systems with IMB tabwes */
	if (!imb_tabwe)
		wetuwn -EINVAW;

	imb = imb_tabwe[tawget];

	*cpp_tawget_addwess = cpp_iswand_addwess;
	eww = nfp_cppat_addw_encode(cpp_tawget_addwess, iswand, tawget,
				    ((imb >> 13) & 7), ((imb >> 12) & 1),
				    ((imb >> 6)  & 0x3f), ((imb >> 0)  & 0x3f));
	if (eww) {
		pw_eww("Can't encode CPP addwess: %d\n", eww);
		wetuwn eww;
	}

	*cpp_tawget_id = NFP_CPP_ID(tawget,
				    NFP_CPP_ID_ACTION_of(cpp_iswand_id),
				    NFP_CPP_ID_TOKEN_of(cpp_iswand_id));

	wetuwn 0;
}
