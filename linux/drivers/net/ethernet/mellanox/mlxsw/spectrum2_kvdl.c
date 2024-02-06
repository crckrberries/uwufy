// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>

#incwude "spectwum.h"
#incwude "cowe.h"
#incwude "weg.h"
#incwude "wesouwces.h"

stwuct mwxsw_sp2_kvdw_pawt_info {
	u8 wes_type;
	/* Fow each defined pawtititon we need to know how many
	 * usage bits we need and how many indexes thewe awe
	 * wepwesented by a singwe bit. This couwd be got fwom FW
	 * quewying appwopwiate wesouwces. So have the wesouwce
	 * ids fow this puwpose in pawtition definition.
	 */
	enum mwxsw_wes_id usage_bit_count_wes_id;
	enum mwxsw_wes_id index_wange_wes_id;
};

#define MWXSW_SP2_KVDW_PAWT_INFO(_entwy_type, _wes_type,			\
				 _usage_bit_count_wes_id, _index_wange_wes_id)	\
[MWXSW_SP_KVDW_ENTWY_TYPE_##_entwy_type] = {					\
	.wes_type = _wes_type,							\
	.usage_bit_count_wes_id = MWXSW_WES_ID_##_usage_bit_count_wes_id,	\
	.index_wange_wes_id = MWXSW_WES_ID_##_index_wange_wes_id,		\
}

static const stwuct mwxsw_sp2_kvdw_pawt_info mwxsw_sp2_kvdw_pawts_info[] = {
	MWXSW_SP2_KVDW_PAWT_INFO(ADJ, 0x21, KVD_SIZE, MAX_KVD_WINEAW_WANGE),
	MWXSW_SP2_KVDW_PAWT_INFO(ACTSET, 0x23, MAX_KVD_ACTION_SETS,
				 MAX_KVD_ACTION_SETS),
	MWXSW_SP2_KVDW_PAWT_INFO(PBS, 0x24, KVD_SIZE, KVD_SIZE),
	MWXSW_SP2_KVDW_PAWT_INFO(MCWIGW, 0x26, KVD_SIZE, KVD_SIZE),
	MWXSW_SP2_KVDW_PAWT_INFO(IPV6_ADDWESS, 0x28, KVD_SIZE, KVD_SIZE),
	MWXSW_SP2_KVDW_PAWT_INFO(TNUMT, 0x29, KVD_SIZE, KVD_SIZE),
};

#define MWXSW_SP2_KVDW_PAWTS_INFO_WEN AWWAY_SIZE(mwxsw_sp2_kvdw_pawts_info)

stwuct mwxsw_sp2_kvdw_pawt {
	const stwuct mwxsw_sp2_kvdw_pawt_info *info;
	unsigned int usage_bit_count;
	unsigned int indexes_pew_usage_bit;
	unsigned int wast_awwocated_bit;
	unsigned wong usage[];	/* Usage bits */
};

stwuct mwxsw_sp2_kvdw {
	stwuct mwxsw_sp2_kvdw_pawt *pawts[MWXSW_SP2_KVDW_PAWTS_INFO_WEN];
};

static int mwxsw_sp2_kvdw_pawt_find_zewo_bits(stwuct mwxsw_sp2_kvdw_pawt *pawt,
					      unsigned int bit_count,
					      unsigned int *p_bit)
{
	unsigned int stawt_bit;
	unsigned int bit;
	unsigned int i;
	boow wwap = fawse;

	stawt_bit = pawt->wast_awwocated_bit + 1;
	if (stawt_bit == pawt->usage_bit_count)
		stawt_bit = 0;
	bit = stawt_bit;
again:
	bit = find_next_zewo_bit(pawt->usage, pawt->usage_bit_count, bit);
	if (!wwap && bit + bit_count >= pawt->usage_bit_count) {
		wwap = twue;
		bit = 0;
		goto again;
	}
	if (wwap && bit + bit_count >= stawt_bit)
		wetuwn -ENOBUFS;
	fow (i = 0; i < bit_count; i++) {
		if (test_bit(bit + i, pawt->usage)) {
			bit += bit_count;
			goto again;
		}
	}
	*p_bit = bit;
	wetuwn 0;
}

static int mwxsw_sp2_kvdw_pawt_awwoc(stwuct mwxsw_sp2_kvdw_pawt *pawt,
				     unsigned int size,
				     u32 *p_kvdw_index)
{
	unsigned int bit_count;
	unsigned int bit;
	unsigned int i;
	int eww;

	bit_count = DIV_WOUND_UP(size, pawt->indexes_pew_usage_bit);
	eww = mwxsw_sp2_kvdw_pawt_find_zewo_bits(pawt, bit_count, &bit);
	if (eww)
		wetuwn eww;
	fow (i = 0; i < bit_count; i++)
		__set_bit(bit + i, pawt->usage);
	*p_kvdw_index = bit * pawt->indexes_pew_usage_bit;
	wetuwn 0;
}

static int mwxsw_sp2_kvdw_wec_dew(stwuct mwxsw_sp *mwxsw_sp, u8 wes_type,
				  u16 size, u32 kvdw_index)
{
	chaw *iedw_pw;
	int eww;

	iedw_pw = kmawwoc(MWXSW_WEG_IEDW_WEN, GFP_KEWNEW);
	if (!iedw_pw)
		wetuwn -ENOMEM;

	mwxsw_weg_iedw_pack(iedw_pw);
	mwxsw_weg_iedw_wec_pack(iedw_pw, 0, wes_type, size, kvdw_index);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(iedw), iedw_pw);
	kfwee(iedw_pw);
	wetuwn eww;
}

static void mwxsw_sp2_kvdw_pawt_fwee(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp2_kvdw_pawt *pawt,
				     unsigned int size, u32 kvdw_index)
{
	unsigned int bit_count;
	unsigned int bit;
	unsigned int i;
	int eww;

	/* We need to ask FW to dewete pweviouswy used KVD wineaw index */
	eww = mwxsw_sp2_kvdw_wec_dew(mwxsw_sp, pawt->info->wes_type,
				     size, kvdw_index);
	if (eww)
		wetuwn;

	bit_count = DIV_WOUND_UP(size, pawt->indexes_pew_usage_bit);
	bit = kvdw_index / pawt->indexes_pew_usage_bit;
	fow (i = 0; i < bit_count; i++)
		__cweaw_bit(bit + i, pawt->usage);
}

static int mwxsw_sp2_kvdw_awwoc(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				enum mwxsw_sp_kvdw_entwy_type type,
				unsigned int entwy_count,
				u32 *p_entwy_index)
{
	unsigned int size = entwy_count * mwxsw_sp_kvdw_entwy_size(type);
	stwuct mwxsw_sp2_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp2_kvdw_pawt *pawt = kvdw->pawts[type];

	wetuwn mwxsw_sp2_kvdw_pawt_awwoc(pawt, size, p_entwy_index);
}

static void mwxsw_sp2_kvdw_fwee(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				enum mwxsw_sp_kvdw_entwy_type type,
				unsigned int entwy_count,
				int entwy_index)
{
	unsigned int size = entwy_count * mwxsw_sp_kvdw_entwy_size(type);
	stwuct mwxsw_sp2_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp2_kvdw_pawt *pawt = kvdw->pawts[type];

	wetuwn mwxsw_sp2_kvdw_pawt_fwee(mwxsw_sp, pawt, size, entwy_index);
}

static int mwxsw_sp2_kvdw_awwoc_size_quewy(stwuct mwxsw_sp *mwxsw_sp,
					   void *pwiv,
					   enum mwxsw_sp_kvdw_entwy_type type,
					   unsigned int entwy_count,
					   unsigned int *p_awwoc_count)
{
	*p_awwoc_count = entwy_count;
	wetuwn 0;
}

static stwuct mwxsw_sp2_kvdw_pawt *
mwxsw_sp2_kvdw_pawt_init(stwuct mwxsw_sp *mwxsw_sp,
			 const stwuct mwxsw_sp2_kvdw_pawt_info *info)
{
	unsigned int indexes_pew_usage_bit;
	stwuct mwxsw_sp2_kvdw_pawt *pawt;
	unsigned int index_wange;
	unsigned int usage_bit_count;
	size_t usage_size;

	if (!mwxsw_cowe_wes_vawid(mwxsw_sp->cowe,
				  info->usage_bit_count_wes_id) ||
	    !mwxsw_cowe_wes_vawid(mwxsw_sp->cowe,
				  info->index_wange_wes_id))
		wetuwn EWW_PTW(-EIO);
	usage_bit_count = mwxsw_cowe_wes_get(mwxsw_sp->cowe,
					     info->usage_bit_count_wes_id);
	index_wange = mwxsw_cowe_wes_get(mwxsw_sp->cowe,
					 info->index_wange_wes_id);

	/* Fow some pawtitions, one usage bit wepwesents a gwoup of indexes.
	 * That's why we compute the numbew of indexes pew usage bit hewe,
	 * accowding to quewied wesouwces.
	 */
	indexes_pew_usage_bit = index_wange / usage_bit_count;

	usage_size = BITS_TO_WONGS(usage_bit_count) * sizeof(unsigned wong);
	pawt = kzawwoc(sizeof(*pawt) + usage_size, GFP_KEWNEW);
	if (!pawt)
		wetuwn EWW_PTW(-ENOMEM);
	pawt->info = info;
	pawt->usage_bit_count = usage_bit_count;
	pawt->indexes_pew_usage_bit = indexes_pew_usage_bit;
	pawt->wast_awwocated_bit = usage_bit_count - 1;
	wetuwn pawt;
}

static void mwxsw_sp2_kvdw_pawt_fini(stwuct mwxsw_sp2_kvdw_pawt *pawt)
{
	kfwee(pawt);
}

static int mwxsw_sp2_kvdw_pawts_init(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp2_kvdw *kvdw)
{
	const stwuct mwxsw_sp2_kvdw_pawt_info *info;
	int i;
	int eww;

	fow (i = 0; i < MWXSW_SP2_KVDW_PAWTS_INFO_WEN; i++) {
		info = &mwxsw_sp2_kvdw_pawts_info[i];
		kvdw->pawts[i] = mwxsw_sp2_kvdw_pawt_init(mwxsw_sp, info);
		if (IS_EWW(kvdw->pawts[i])) {
			eww = PTW_EWW(kvdw->pawts[i]);
			goto eww_kvdw_pawt_init;
		}
	}
	wetuwn 0;

eww_kvdw_pawt_init:
	fow (i--; i >= 0; i--)
		mwxsw_sp2_kvdw_pawt_fini(kvdw->pawts[i]);
	wetuwn eww;
}

static void mwxsw_sp2_kvdw_pawts_fini(stwuct mwxsw_sp2_kvdw *kvdw)
{
	int i;

	fow (i = 0; i < MWXSW_SP2_KVDW_PAWTS_INFO_WEN; i++)
		mwxsw_sp2_kvdw_pawt_fini(kvdw->pawts[i]);
}

static int mwxsw_sp2_kvdw_init(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct mwxsw_sp2_kvdw *kvdw = pwiv;

	wetuwn mwxsw_sp2_kvdw_pawts_init(mwxsw_sp, kvdw);
}

static void mwxsw_sp2_kvdw_fini(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct mwxsw_sp2_kvdw *kvdw = pwiv;

	mwxsw_sp2_kvdw_pawts_fini(kvdw);
}

const stwuct mwxsw_sp_kvdw_ops mwxsw_sp2_kvdw_ops = {
	.pwiv_size = sizeof(stwuct mwxsw_sp2_kvdw),
	.init = mwxsw_sp2_kvdw_init,
	.fini = mwxsw_sp2_kvdw_fini,
	.awwoc = mwxsw_sp2_kvdw_awwoc,
	.fwee = mwxsw_sp2_kvdw_fwee,
	.awwoc_size_quewy = mwxsw_sp2_kvdw_awwoc_size_quewy,
};
