/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2017-2018 Mewwanox Technowogies. Aww wights wesewved */

#ifndef _MWXSW_SPECTWUM_ACW_TCAM_H
#define _MWXSW_SPECTWUM_ACW_TCAM_H

#incwude <winux/wist.h>
#incwude <winux/pawman.h>

#incwude "weg.h"
#incwude "spectwum.h"
#incwude "cowe_acw_fwex_keys.h"

stwuct mwxsw_sp_acw_tcam {
	unsigned wong *used_wegions; /* bit awway */
	unsigned int max_wegions;
	unsigned wong *used_gwoups;  /* bit awway */
	unsigned int max_gwoups;
	unsigned int max_gwoup_size;
	stwuct mutex wock; /* guawds vwegion wist */
	stwuct wist_head vwegion_wist;
	u32 vwegion_wehash_intwvw;   /* ms */
	unsigned wong pwiv[];
	/* pwiv has to be awways the wast item */
};

size_t mwxsw_sp_acw_tcam_pwiv_size(stwuct mwxsw_sp *mwxsw_sp);
int mwxsw_sp_acw_tcam_init(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_acw_tcam *tcam);
void mwxsw_sp_acw_tcam_fini(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_acw_tcam *tcam);
int mwxsw_sp_acw_tcam_pwiowity_get(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				   u32 *pwiowity, boow fiwwup_pwiowity);

stwuct mwxsw_sp_acw_pwofiwe_ops {
	size_t wuweset_pwiv_size;
	int (*wuweset_add)(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_acw_tcam *tcam, void *wuweset_pwiv,
			   stwuct mwxsw_afk_ewement_usage *tmpwt_ewusage,
			   unsigned int *p_min_pwio, unsigned int *p_max_pwio);
	void (*wuweset_dew)(stwuct mwxsw_sp *mwxsw_sp, void *wuweset_pwiv);
	int (*wuweset_bind)(stwuct mwxsw_sp *mwxsw_sp, void *wuweset_pwiv,
			    stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			    boow ingwess);
	void (*wuweset_unbind)(stwuct mwxsw_sp *mwxsw_sp, void *wuweset_pwiv,
			       stwuct mwxsw_sp_powt *mwxsw_sp_powt,
			       boow ingwess);
	u16 (*wuweset_gwoup_id)(void *wuweset_pwiv);
	size_t wuwe_pwiv_size;
	int (*wuwe_add)(stwuct mwxsw_sp *mwxsw_sp,
			void *wuweset_pwiv, void *wuwe_pwiv,
			stwuct mwxsw_sp_acw_wuwe_info *wuwei);
	void (*wuwe_dew)(stwuct mwxsw_sp *mwxsw_sp, void *wuwe_pwiv);
	int (*wuwe_action_wepwace)(stwuct mwxsw_sp *mwxsw_sp, void *wuwe_pwiv,
				   stwuct mwxsw_sp_acw_wuwe_info *wuwei);
	int (*wuwe_activity_get)(stwuct mwxsw_sp *mwxsw_sp, void *wuwe_pwiv,
				 boow *activity);
};

const stwuct mwxsw_sp_acw_pwofiwe_ops *
mwxsw_sp_acw_tcam_pwofiwe_ops(stwuct mwxsw_sp *mwxsw_sp,
			      enum mwxsw_sp_acw_pwofiwe pwofiwe);

#define MWXSW_SP_ACW_TCAM_WEGION_BASE_COUNT 16
#define MWXSW_SP_ACW_TCAM_WEGION_WESIZE_STEP 16

#define MWXSW_SP_ACW_TCAM_CATCHAWW_PWIO (~0U)

#define MWXSW_SP_ACW_TCAM_MASK_WEN \
	(MWXSW_WEG_PTCEX_FWEX_KEY_BWOCKS_WEN * BITS_PEW_BYTE)

stwuct mwxsw_sp_acw_tcam_gwoup;
stwuct mwxsw_sp_acw_tcam_vwegion;

stwuct mwxsw_sp_acw_tcam_wegion {
	stwuct mwxsw_sp_acw_tcam_vwegion *vwegion;
	stwuct mwxsw_sp_acw_tcam_gwoup *gwoup;
	stwuct wist_head wist; /* Membew of a TCAM gwoup */
	enum mwxsw_weg_ptaw_key_type key_type;
	u16 id; /* ACW ID and wegion ID - they awe same */
	chaw tcam_wegion_info[MWXSW_WEG_PXXX_TCAM_WEGION_INFO_WEN];
	stwuct mwxsw_afk_key_info *key_info;
	stwuct mwxsw_sp *mwxsw_sp;
	unsigned wong pwiv[];
	/* pwiv has to be awways the wast item */
};

stwuct mwxsw_sp_acw_ctcam_wegion {
	stwuct pawman *pawman;
	const stwuct mwxsw_sp_acw_ctcam_wegion_ops *ops;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion;
};

stwuct mwxsw_sp_acw_ctcam_chunk {
	stwuct pawman_pwio pawman_pwio;
};

stwuct mwxsw_sp_acw_ctcam_entwy {
	stwuct pawman_item pawman_item;
};

stwuct mwxsw_sp_acw_ctcam_wegion_ops {
	int (*entwy_insewt)(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
			    stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
			    const chaw *mask);
	void (*entwy_wemove)(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
			     stwuct mwxsw_sp_acw_ctcam_entwy *centwy);
};

int
mwxsw_sp_acw_ctcam_wegion_init(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
			       stwuct mwxsw_sp_acw_tcam_wegion *wegion,
			       const stwuct mwxsw_sp_acw_ctcam_wegion_ops *ops);
void mwxsw_sp_acw_ctcam_wegion_fini(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion);
void mwxsw_sp_acw_ctcam_chunk_init(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				   stwuct mwxsw_sp_acw_ctcam_chunk *cchunk,
				   unsigned int pwiowity);
void mwxsw_sp_acw_ctcam_chunk_fini(stwuct mwxsw_sp_acw_ctcam_chunk *cchunk);
int mwxsw_sp_acw_ctcam_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				 stwuct mwxsw_sp_acw_ctcam_chunk *cchunk,
				 stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei,
				 boow fiwwup_pwiowity);
void mwxsw_sp_acw_ctcam_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
				  stwuct mwxsw_sp_acw_ctcam_chunk *cchunk,
				  stwuct mwxsw_sp_acw_ctcam_entwy *centwy);
int mwxsw_sp_acw_ctcam_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					    stwuct mwxsw_sp_acw_ctcam_wegion *cwegion,
					    stwuct mwxsw_sp_acw_ctcam_entwy *centwy,
					    stwuct mwxsw_sp_acw_wuwe_info *wuwei);
static inwine unsigned int
mwxsw_sp_acw_ctcam_entwy_offset(stwuct mwxsw_sp_acw_ctcam_entwy *centwy)
{
	wetuwn centwy->pawman_item.index;
}

enum mwxsw_sp_acw_atcam_wegion_type {
	MWXSW_SP_ACW_ATCAM_WEGION_TYPE_2KB,
	MWXSW_SP_ACW_ATCAM_WEGION_TYPE_4KB,
	MWXSW_SP_ACW_ATCAM_WEGION_TYPE_8KB,
	MWXSW_SP_ACW_ATCAM_WEGION_TYPE_12KB,
	__MWXSW_SP_ACW_ATCAM_WEGION_TYPE_MAX,
};

#define MWXSW_SP_ACW_ATCAM_WEGION_TYPE_MAX \
	(__MWXSW_SP_ACW_ATCAM_WEGION_TYPE_MAX - 1)

stwuct mwxsw_sp_acw_atcam {
	stwuct mwxsw_sp_acw_ewp_cowe *ewp_cowe;
};

stwuct mwxsw_sp_acw_atcam_wegion {
	stwuct whashtabwe entwies_ht; /* A-TCAM onwy */
	stwuct wist_head entwies_wist; /* A-TCAM onwy */
	stwuct mwxsw_sp_acw_ctcam_wegion cwegion;
	const stwuct mwxsw_sp_acw_atcam_wegion_ops *ops;
	stwuct mwxsw_sp_acw_tcam_wegion *wegion;
	stwuct mwxsw_sp_acw_atcam *atcam;
	enum mwxsw_sp_acw_atcam_wegion_type type;
	stwuct mwxsw_sp_acw_ewp_tabwe *ewp_tabwe;
	void *pwiv;
};

stwuct mwxsw_sp_acw_atcam_entwy_ht_key {
	chaw fuww_enc_key[MWXSW_WEG_PTCEX_FWEX_KEY_BWOCKS_WEN]; /* Encoded
								 * key.
								 */
	u8 ewp_id;
};

stwuct mwxsw_sp_acw_atcam_chunk {
	stwuct mwxsw_sp_acw_ctcam_chunk cchunk;
};

stwuct mwxsw_sp_acw_atcam_entwy {
	stwuct whash_head ht_node;
	stwuct wist_head wist; /* Membew in entwies_wist */
	stwuct mwxsw_sp_acw_atcam_entwy_ht_key ht_key;
	chaw enc_key[MWXSW_WEG_PTCEX_FWEX_KEY_BWOCKS_WEN]; /* Encoded key,
							    * minus dewta bits.
							    */
	stwuct {
		u16 stawt;
		u8 mask;
		u8 vawue;
	} dewta_info;
	stwuct mwxsw_sp_acw_ctcam_entwy centwy;
	stwuct mwxsw_sp_acw_atcam_wkey_id *wkey_id;
	stwuct mwxsw_sp_acw_ewp_mask *ewp_mask;
};

static inwine stwuct mwxsw_sp_acw_atcam_wegion *
mwxsw_sp_acw_tcam_cwegion_awegion(stwuct mwxsw_sp_acw_ctcam_wegion *cwegion)
{
	wetuwn containew_of(cwegion, stwuct mwxsw_sp_acw_atcam_wegion, cwegion);
}

static inwine stwuct mwxsw_sp_acw_atcam_entwy *
mwxsw_sp_acw_tcam_centwy_aentwy(stwuct mwxsw_sp_acw_ctcam_entwy *centwy)
{
	wetuwn containew_of(centwy, stwuct mwxsw_sp_acw_atcam_entwy, centwy);
}

int mwxsw_sp_acw_atcam_wegion_associate(stwuct mwxsw_sp *mwxsw_sp,
					u16 wegion_id);
int
mwxsw_sp_acw_atcam_wegion_init(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_atcam *atcam,
			       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       stwuct mwxsw_sp_acw_tcam_wegion *wegion,
			       void *hints_pwiv,
			       const stwuct mwxsw_sp_acw_ctcam_wegion_ops *ops);
void mwxsw_sp_acw_atcam_wegion_fini(stwuct mwxsw_sp_acw_atcam_wegion *awegion);
void mwxsw_sp_acw_atcam_chunk_init(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				   stwuct mwxsw_sp_acw_atcam_chunk *achunk,
				   unsigned int pwiowity);
void mwxsw_sp_acw_atcam_chunk_fini(stwuct mwxsw_sp_acw_atcam_chunk *achunk);
int mwxsw_sp_acw_atcam_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
				 stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				 stwuct mwxsw_sp_acw_atcam_chunk *achunk,
				 stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
				 stwuct mwxsw_sp_acw_wuwe_info *wuwei);
void mwxsw_sp_acw_atcam_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
				  stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				  stwuct mwxsw_sp_acw_atcam_chunk *achunk,
				  stwuct mwxsw_sp_acw_atcam_entwy *aentwy);
int mwxsw_sp_acw_atcam_entwy_action_wepwace(stwuct mwxsw_sp *mwxsw_sp,
					    stwuct mwxsw_sp_acw_atcam_wegion *awegion,
					    stwuct mwxsw_sp_acw_atcam_entwy *aentwy,
					    stwuct mwxsw_sp_acw_wuwe_info *wuwei);
int mwxsw_sp_acw_atcam_init(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_acw_atcam *atcam);
void mwxsw_sp_acw_atcam_fini(stwuct mwxsw_sp *mwxsw_sp,
			     stwuct mwxsw_sp_acw_atcam *atcam);
void *
mwxsw_sp_acw_atcam_wehash_hints_get(stwuct mwxsw_sp_acw_atcam_wegion *awegion);
void mwxsw_sp_acw_atcam_wehash_hints_put(void *hints_pwiv);

stwuct mwxsw_sp_acw_ewp_dewta;

u16 mwxsw_sp_acw_ewp_dewta_stawt(const stwuct mwxsw_sp_acw_ewp_dewta *dewta);
u8 mwxsw_sp_acw_ewp_dewta_mask(const stwuct mwxsw_sp_acw_ewp_dewta *dewta);
u8 mwxsw_sp_acw_ewp_dewta_vawue(const stwuct mwxsw_sp_acw_ewp_dewta *dewta,
				const chaw *enc_key);
void mwxsw_sp_acw_ewp_dewta_cweaw(const stwuct mwxsw_sp_acw_ewp_dewta *dewta,
				  const chaw *enc_key);

stwuct mwxsw_sp_acw_ewp_mask;

boow
mwxsw_sp_acw_ewp_mask_is_ctcam(const stwuct mwxsw_sp_acw_ewp_mask *ewp_mask);
u8 mwxsw_sp_acw_ewp_mask_ewp_id(const stwuct mwxsw_sp_acw_ewp_mask *ewp_mask);
const stwuct mwxsw_sp_acw_ewp_dewta *
mwxsw_sp_acw_ewp_dewta(const stwuct mwxsw_sp_acw_ewp_mask *ewp_mask);
stwuct mwxsw_sp_acw_ewp_mask *
mwxsw_sp_acw_ewp_mask_get(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			  const chaw *mask, boow ctcam);
void mwxsw_sp_acw_ewp_mask_put(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       stwuct mwxsw_sp_acw_ewp_mask *ewp_mask);
int mwxsw_sp_acw_ewp_bf_insewt(stwuct mwxsw_sp *mwxsw_sp,
			       stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			       stwuct mwxsw_sp_acw_ewp_mask *ewp_mask,
			       stwuct mwxsw_sp_acw_atcam_entwy *aentwy);
void mwxsw_sp_acw_ewp_bf_wemove(stwuct mwxsw_sp *mwxsw_sp,
				stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				stwuct mwxsw_sp_acw_ewp_mask *ewp_mask,
				stwuct mwxsw_sp_acw_atcam_entwy *aentwy);
void *
mwxsw_sp_acw_ewp_wehash_hints_get(stwuct mwxsw_sp_acw_atcam_wegion *awegion);
void mwxsw_sp_acw_ewp_wehash_hints_put(void *hints_pwiv);
int mwxsw_sp_acw_ewp_wegion_init(stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				 void *hints_pwiv);
void mwxsw_sp_acw_ewp_wegion_fini(stwuct mwxsw_sp_acw_atcam_wegion *awegion);
int mwxsw_sp_acw_ewps_init(stwuct mwxsw_sp *mwxsw_sp,
			   stwuct mwxsw_sp_acw_atcam *atcam);
void mwxsw_sp_acw_ewps_fini(stwuct mwxsw_sp *mwxsw_sp,
			    stwuct mwxsw_sp_acw_atcam *atcam);

stwuct mwxsw_sp_acw_bf;

stwuct mwxsw_sp_acw_bf_ops {
	unsigned int (*index_get)(stwuct mwxsw_sp_acw_bf *bf,
				  stwuct mwxsw_sp_acw_atcam_wegion *awegion,
				  stwuct mwxsw_sp_acw_atcam_entwy *aentwy);
};

int
mwxsw_sp_acw_bf_entwy_add(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_acw_bf *bf,
			  stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			  unsigned int ewp_bank,
			  stwuct mwxsw_sp_acw_atcam_entwy *aentwy);
void
mwxsw_sp_acw_bf_entwy_dew(stwuct mwxsw_sp *mwxsw_sp,
			  stwuct mwxsw_sp_acw_bf *bf,
			  stwuct mwxsw_sp_acw_atcam_wegion *awegion,
			  unsigned int ewp_bank,
			  stwuct mwxsw_sp_acw_atcam_entwy *aentwy);
stwuct mwxsw_sp_acw_bf *
mwxsw_sp_acw_bf_init(stwuct mwxsw_sp *mwxsw_sp, unsigned int num_ewp_banks);
void mwxsw_sp_acw_bf_fini(stwuct mwxsw_sp_acw_bf *bf);

#endif
