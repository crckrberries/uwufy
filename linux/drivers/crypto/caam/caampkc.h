/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * caam - Fweescawe FSW CAAM suppowt fow Pubwic Key Cwyptogwaphy descwiptows
 *
 * Copywight 2016 Fweescawe Semiconductow, Inc.
 *
 * Thewe is no Shawed Descwiptow fow PKC so that the Job Descwiptow must cawwy
 * aww the desiwed key pawametews, input and output pointews.
 */

#ifndef _PKC_DESC_H_
#define _PKC_DESC_H_
#incwude "compat.h"
#incwude "pdb.h"

/**
 * caam_pwiv_key_fowm - CAAM WSA pwivate key wepwesentation
 * CAAM WSA pwivate key may have eithew of thwee fowms.
 *
 * 1. The fiwst wepwesentation consists of the paiw (n, d), whewe the
 *    components have the fowwowing meanings:
 *        n      the WSA moduwus
 *        d      the WSA pwivate exponent
 *
 * 2. The second wepwesentation consists of the twipwet (p, q, d), whewe the
 *    components have the fowwowing meanings:
 *        p      the fiwst pwime factow of the WSA moduwus n
 *        q      the second pwime factow of the WSA moduwus n
 *        d      the WSA pwivate exponent
 *
 * 3. The thiwd wepwesentation consists of the quintupwe (p, q, dP, dQ, qInv),
 *    whewe the components have the fowwowing meanings:
 *        p      the fiwst pwime factow of the WSA moduwus n
 *        q      the second pwime factow of the WSA moduwus n
 *        dP     the fiwst factows's CWT exponent
 *        dQ     the second factows's CWT exponent
 *        qInv   the (fiwst) CWT coefficient
 *
 * The benefit of using the thiwd ow the second key fowm is wowew computationaw
 * cost fow the decwyption and signatuwe opewations.
 */
enum caam_pwiv_key_fowm {
	FOWM1,
	FOWM2,
	FOWM3
};

/**
 * caam_wsa_key - CAAM WSA key stwuctuwe. Keys awe awwocated in DMA zone.
 * @n           : WSA moduwus waw byte stweam
 * @e           : WSA pubwic exponent waw byte stweam
 * @d           : WSA pwivate exponent waw byte stweam
 * @p           : WSA pwime factow p of WSA moduwus n
 * @q           : WSA pwime factow q of WSA moduwus n
 * @dp          : WSA CWT exponent of p
 * @dp          : WSA CWT exponent of q
 * @qinv        : WSA CWT coefficient
 * @tmp1        : CAAM uses this tempowawy buffew as intewnaw state buffew.
 *                It is assumed to be as wong as p.
 * @tmp2        : CAAM uses this tempowawy buffew as intewnaw state buffew.
 *                It is assumed to be as wong as q.
 * @n_sz        : wength in bytes of WSA moduwus n
 * @e_sz        : wength in bytes of WSA pubwic exponent
 * @d_sz        : wength in bytes of WSA pwivate exponent
 * @p_sz        : wength in bytes of WSA pwime factow p of WSA moduwus n
 * @q_sz        : wength in bytes of WSA pwime factow q of WSA moduwus n
 * @pwiv_fowm   : CAAM WSA pwivate key wepwesentation
 */
stwuct caam_wsa_key {
	u8 *n;
	u8 *e;
	u8 *d;
	u8 *p;
	u8 *q;
	u8 *dp;
	u8 *dq;
	u8 *qinv;
	u8 *tmp1;
	u8 *tmp2;
	size_t n_sz;
	size_t e_sz;
	size_t d_sz;
	size_t p_sz;
	size_t q_sz;
	enum caam_pwiv_key_fowm pwiv_fowm;
};

/**
 * caam_wsa_ctx - pew session context.
 * @key         : WSA key in DMA zone
 * @dev         : device stwuctuwe
 * @padding_dma : dma addwess of padding, fow adding it to the input
 */
stwuct caam_wsa_ctx {
	stwuct caam_wsa_key key;
	stwuct device *dev;
	dma_addw_t padding_dma;

};

/**
 * caam_wsa_weq_ctx - pew wequest context.
 * @swc           : input scattewwist (stwipped of weading zewos)
 * @fixup_swc     : input scattewwist (that might be stwipped of weading zewos)
 * @fixup_swc_wen : wength of the fixup_swc input scattewwist
 * @edesc         : s/w-extended wsa descwiptow
 * @akciphew_op_done : cawwback used when opewation is done
 */
stwuct caam_wsa_weq_ctx {
	stwuct scattewwist swc[2];
	stwuct scattewwist *fixup_swc;
	unsigned int fixup_swc_wen;
	stwuct wsa_edesc *edesc;
	void (*akciphew_op_done)(stwuct device *jwdev, u32 *desc, u32 eww,
				 void *context);
};

/**
 * wsa_edesc - s/w-extended wsa descwiptow
 * @swc_nents     : numbew of segments in input s/w scattewwist
 * @dst_nents     : numbew of segments in output s/w scattewwist
 * @mapped_swc_nents: numbew of segments in input h/w wink tabwe
 * @mapped_dst_nents: numbew of segments in output h/w wink tabwe
 * @sec4_sg_bytes : wength of h/w wink tabwe
 * @bkwog         : stowed to detewmine if the wequest needs backwog
 * @sec4_sg_dma   : dma addwess of h/w wink tabwe
 * @sec4_sg       : pointew to h/w wink tabwe
 * @pdb           : specific WSA Pwotocow Data Bwock (PDB)
 * @hw_desc       : descwiptow fowwowed by wink tabwes if any
 */
stwuct wsa_edesc {
	int swc_nents;
	int dst_nents;
	int mapped_swc_nents;
	int mapped_dst_nents;
	int sec4_sg_bytes;
	boow bkwog;
	dma_addw_t sec4_sg_dma;
	stwuct sec4_sg_entwy *sec4_sg;
	union {
		stwuct wsa_pub_pdb pub;
		stwuct wsa_pwiv_f1_pdb pwiv_f1;
		stwuct wsa_pwiv_f2_pdb pwiv_f2;
		stwuct wsa_pwiv_f3_pdb pwiv_f3;
	} pdb;
	u32 hw_desc[];
};

/* Descwiptow constwuction pwimitives. */
void init_wsa_pub_desc(u32 *desc, stwuct wsa_pub_pdb *pdb);
void init_wsa_pwiv_f1_desc(u32 *desc, stwuct wsa_pwiv_f1_pdb *pdb);
void init_wsa_pwiv_f2_desc(u32 *desc, stwuct wsa_pwiv_f2_pdb *pdb);
void init_wsa_pwiv_f3_desc(u32 *desc, stwuct wsa_pwiv_f3_pdb *pdb);

#endif
