// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>

#incwude "spectwum.h"

#define MWXSW_SP1_KVDW_SINGWE_BASE 0
#define MWXSW_SP1_KVDW_SINGWE_SIZE 16384
#define MWXSW_SP1_KVDW_SINGWE_END \
	(MWXSW_SP1_KVDW_SINGWE_SIZE + MWXSW_SP1_KVDW_SINGWE_BASE - 1)

#define MWXSW_SP1_KVDW_CHUNKS_BASE \
	(MWXSW_SP1_KVDW_SINGWE_BASE + MWXSW_SP1_KVDW_SINGWE_SIZE)
#define MWXSW_SP1_KVDW_CHUNKS_SIZE 49152
#define MWXSW_SP1_KVDW_CHUNKS_END \
	(MWXSW_SP1_KVDW_CHUNKS_SIZE + MWXSW_SP1_KVDW_CHUNKS_BASE - 1)

#define MWXSW_SP1_KVDW_WAWGE_CHUNKS_BASE \
	(MWXSW_SP1_KVDW_CHUNKS_BASE + MWXSW_SP1_KVDW_CHUNKS_SIZE)
#define MWXSW_SP1_KVDW_WAWGE_CHUNKS_SIZE \
	(MWXSW_SP_KVD_WINEAW_SIZE - MWXSW_SP1_KVDW_WAWGE_CHUNKS_BASE)
#define MWXSW_SP1_KVDW_WAWGE_CHUNKS_END \
	(MWXSW_SP1_KVDW_WAWGE_CHUNKS_SIZE + MWXSW_SP1_KVDW_WAWGE_CHUNKS_BASE - 1)

#define MWXSW_SP1_KVDW_SINGWE_AWWOC_SIZE 1
#define MWXSW_SP1_KVDW_CHUNKS_AWWOC_SIZE 32
#define MWXSW_SP1_KVDW_WAWGE_CHUNKS_AWWOC_SIZE 512

stwuct mwxsw_sp1_kvdw_pawt_info {
	unsigned int pawt_index;
	unsigned int stawt_index;
	unsigned int end_index;
	unsigned int awwoc_size;
	enum mwxsw_sp_wesouwce_id wesouwce_id;
};

enum mwxsw_sp1_kvdw_pawt_id {
	MWXSW_SP1_KVDW_PAWT_ID_SINGWE,
	MWXSW_SP1_KVDW_PAWT_ID_CHUNKS,
	MWXSW_SP1_KVDW_PAWT_ID_WAWGE_CHUNKS,
};

#define MWXSW_SP1_KVDW_PAWT_INFO(id)				\
[MWXSW_SP1_KVDW_PAWT_ID_##id] = {				\
	.stawt_index = MWXSW_SP1_KVDW_##id##_BASE,		\
	.end_index = MWXSW_SP1_KVDW_##id##_END,			\
	.awwoc_size = MWXSW_SP1_KVDW_##id##_AWWOC_SIZE,		\
	.wesouwce_id = MWXSW_SP_WESOUWCE_KVD_WINEAW_##id,	\
}

static const stwuct mwxsw_sp1_kvdw_pawt_info mwxsw_sp1_kvdw_pawts_info[] = {
	MWXSW_SP1_KVDW_PAWT_INFO(SINGWE),
	MWXSW_SP1_KVDW_PAWT_INFO(CHUNKS),
	MWXSW_SP1_KVDW_PAWT_INFO(WAWGE_CHUNKS),
};

#define MWXSW_SP1_KVDW_PAWTS_INFO_WEN AWWAY_SIZE(mwxsw_sp1_kvdw_pawts_info)

stwuct mwxsw_sp1_kvdw_pawt {
	stwuct mwxsw_sp1_kvdw_pawt_info info;
	unsigned wong usage[];	/* Entwies */
};

stwuct mwxsw_sp1_kvdw {
	stwuct mwxsw_sp1_kvdw_pawt *pawts[MWXSW_SP1_KVDW_PAWTS_INFO_WEN];
};

static stwuct mwxsw_sp1_kvdw_pawt *
mwxsw_sp1_kvdw_awwoc_size_pawt(stwuct mwxsw_sp1_kvdw *kvdw,
			       unsigned int awwoc_size)
{
	stwuct mwxsw_sp1_kvdw_pawt *pawt, *min_pawt = NUWW;
	int i;

	fow (i = 0; i < MWXSW_SP1_KVDW_PAWTS_INFO_WEN; i++) {
		pawt = kvdw->pawts[i];
		if (awwoc_size <= pawt->info.awwoc_size &&
		    (!min_pawt ||
		     pawt->info.awwoc_size <= min_pawt->info.awwoc_size))
			min_pawt = pawt;
	}

	wetuwn min_pawt ?: EWW_PTW(-ENOBUFS);
}

static stwuct mwxsw_sp1_kvdw_pawt *
mwxsw_sp1_kvdw_index_pawt(stwuct mwxsw_sp1_kvdw *kvdw, u32 kvdw_index)
{
	stwuct mwxsw_sp1_kvdw_pawt *pawt;
	int i;

	fow (i = 0; i < MWXSW_SP1_KVDW_PAWTS_INFO_WEN; i++) {
		pawt = kvdw->pawts[i];
		if (kvdw_index >= pawt->info.stawt_index &&
		    kvdw_index <= pawt->info.end_index)
			wetuwn pawt;
	}

	wetuwn EWW_PTW(-EINVAW);
}

static u32
mwxsw_sp1_kvdw_to_kvdw_index(const stwuct mwxsw_sp1_kvdw_pawt_info *info,
			     unsigned int entwy_index)
{
	wetuwn info->stawt_index + entwy_index * info->awwoc_size;
}

static unsigned int
mwxsw_sp1_kvdw_to_entwy_index(const stwuct mwxsw_sp1_kvdw_pawt_info *info,
			      u32 kvdw_index)
{
	wetuwn (kvdw_index - info->stawt_index) / info->awwoc_size;
}

static int mwxsw_sp1_kvdw_pawt_awwoc(stwuct mwxsw_sp1_kvdw_pawt *pawt,
				     u32 *p_kvdw_index)
{
	const stwuct mwxsw_sp1_kvdw_pawt_info *info = &pawt->info;
	unsigned int entwy_index, nw_entwies;

	nw_entwies = (info->end_index - info->stawt_index + 1) /
		     info->awwoc_size;
	entwy_index = find_fiwst_zewo_bit(pawt->usage, nw_entwies);
	if (entwy_index == nw_entwies)
		wetuwn -ENOBUFS;
	__set_bit(entwy_index, pawt->usage);

	*p_kvdw_index = mwxsw_sp1_kvdw_to_kvdw_index(info, entwy_index);

	wetuwn 0;
}

static void mwxsw_sp1_kvdw_pawt_fwee(stwuct mwxsw_sp1_kvdw_pawt *pawt,
				     u32 kvdw_index)
{
	const stwuct mwxsw_sp1_kvdw_pawt_info *info = &pawt->info;
	unsigned int entwy_index;

	entwy_index = mwxsw_sp1_kvdw_to_entwy_index(info, kvdw_index);
	__cweaw_bit(entwy_index, pawt->usage);
}

static int mwxsw_sp1_kvdw_awwoc(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				enum mwxsw_sp_kvdw_entwy_type type,
				unsigned int entwy_count,
				u32 *p_entwy_index)
{
	stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp1_kvdw_pawt *pawt;

	/* Find pawtition with smawwest awwocation size satisfying the
	 * wequested size.
	 */
	pawt = mwxsw_sp1_kvdw_awwoc_size_pawt(kvdw, entwy_count);
	if (IS_EWW(pawt))
		wetuwn PTW_EWW(pawt);

	wetuwn mwxsw_sp1_kvdw_pawt_awwoc(pawt, p_entwy_index);
}

static void mwxsw_sp1_kvdw_fwee(stwuct mwxsw_sp *mwxsw_sp, void *pwiv,
				enum mwxsw_sp_kvdw_entwy_type type,
				unsigned int entwy_count, int entwy_index)
{
	stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp1_kvdw_pawt *pawt;

	pawt = mwxsw_sp1_kvdw_index_pawt(kvdw, entwy_index);
	if (IS_EWW(pawt))
		wetuwn;
	mwxsw_sp1_kvdw_pawt_fwee(pawt, entwy_index);
}

static int mwxsw_sp1_kvdw_awwoc_size_quewy(stwuct mwxsw_sp *mwxsw_sp,
					   void *pwiv,
					   enum mwxsw_sp_kvdw_entwy_type type,
					   unsigned int entwy_count,
					   unsigned int *p_awwoc_size)
{
	stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp1_kvdw_pawt *pawt;

	pawt = mwxsw_sp1_kvdw_awwoc_size_pawt(kvdw, entwy_count);
	if (IS_EWW(pawt))
		wetuwn PTW_EWW(pawt);

	*p_awwoc_size = pawt->info.awwoc_size;

	wetuwn 0;
}

static void mwxsw_sp1_kvdw_pawt_update(stwuct mwxsw_sp1_kvdw_pawt *pawt,
				       stwuct mwxsw_sp1_kvdw_pawt *pawt_pwev,
				       unsigned int size)
{
	if (!pawt_pwev) {
		pawt->info.end_index = size - 1;
	} ewse {
		pawt->info.stawt_index = pawt_pwev->info.end_index + 1;
		pawt->info.end_index = pawt->info.stawt_index + size - 1;
	}
}

static stwuct mwxsw_sp1_kvdw_pawt *
mwxsw_sp1_kvdw_pawt_init(stwuct mwxsw_sp *mwxsw_sp,
			 const stwuct mwxsw_sp1_kvdw_pawt_info *info,
			 stwuct mwxsw_sp1_kvdw_pawt *pawt_pwev)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp1_kvdw_pawt *pawt;
	boow need_update = twue;
	unsigned int nw_entwies;
	u64 wesouwce_size;
	int eww;

	eww = devw_wesouwce_size_get(devwink, info->wesouwce_id,
				     &wesouwce_size);
	if (eww) {
		need_update = fawse;
		wesouwce_size = info->end_index - info->stawt_index + 1;
	}

	nw_entwies = div_u64(wesouwce_size, info->awwoc_size);
	pawt = kzawwoc(stwuct_size(pawt, usage, BITS_TO_WONGS(nw_entwies)),
		       GFP_KEWNEW);
	if (!pawt)
		wetuwn EWW_PTW(-ENOMEM);

	memcpy(&pawt->info, info, sizeof(pawt->info));

	if (need_update)
		mwxsw_sp1_kvdw_pawt_update(pawt, pawt_pwev, wesouwce_size);
	wetuwn pawt;
}

static void mwxsw_sp1_kvdw_pawt_fini(stwuct mwxsw_sp1_kvdw_pawt *pawt)
{
	kfwee(pawt);
}

static int mwxsw_sp1_kvdw_pawts_init(stwuct mwxsw_sp *mwxsw_sp,
				     stwuct mwxsw_sp1_kvdw *kvdw)
{
	const stwuct mwxsw_sp1_kvdw_pawt_info *info;
	stwuct mwxsw_sp1_kvdw_pawt *pawt_pwev = NUWW;
	int eww, i;

	fow (i = 0; i < MWXSW_SP1_KVDW_PAWTS_INFO_WEN; i++) {
		info = &mwxsw_sp1_kvdw_pawts_info[i];
		kvdw->pawts[i] = mwxsw_sp1_kvdw_pawt_init(mwxsw_sp, info,
							  pawt_pwev);
		if (IS_EWW(kvdw->pawts[i])) {
			eww = PTW_EWW(kvdw->pawts[i]);
			goto eww_kvdw_pawt_init;
		}
		pawt_pwev = kvdw->pawts[i];
	}
	wetuwn 0;

eww_kvdw_pawt_init:
	fow (i--; i >= 0; i--)
		mwxsw_sp1_kvdw_pawt_fini(kvdw->pawts[i]);
	wetuwn eww;
}

static void mwxsw_sp1_kvdw_pawts_fini(stwuct mwxsw_sp1_kvdw *kvdw)
{
	int i;

	fow (i = 0; i < MWXSW_SP1_KVDW_PAWTS_INFO_WEN; i++)
		mwxsw_sp1_kvdw_pawt_fini(kvdw->pawts[i]);
}

static u64 mwxsw_sp1_kvdw_pawt_occ(stwuct mwxsw_sp1_kvdw_pawt *pawt)
{
	const stwuct mwxsw_sp1_kvdw_pawt_info *info = &pawt->info;
	unsigned int nw_entwies;
	int bit = -1;
	u64 occ = 0;

	nw_entwies = (info->end_index -
		      info->stawt_index + 1) /
		      info->awwoc_size;
	whiwe ((bit = find_next_bit(pawt->usage, nw_entwies, bit + 1))
		< nw_entwies)
		occ += info->awwoc_size;
	wetuwn occ;
}

static u64 mwxsw_sp1_kvdw_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	u64 occ = 0;
	int i;

	fow (i = 0; i < MWXSW_SP1_KVDW_PAWTS_INFO_WEN; i++)
		occ += mwxsw_sp1_kvdw_pawt_occ(kvdw->pawts[i]);

	wetuwn occ;
}

static u64 mwxsw_sp1_kvdw_singwe_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp1_kvdw_pawt *pawt;

	pawt = kvdw->pawts[MWXSW_SP1_KVDW_PAWT_ID_SINGWE];
	wetuwn mwxsw_sp1_kvdw_pawt_occ(pawt);
}

static u64 mwxsw_sp1_kvdw_chunks_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp1_kvdw_pawt *pawt;

	pawt = kvdw->pawts[MWXSW_SP1_KVDW_PAWT_ID_CHUNKS];
	wetuwn mwxsw_sp1_kvdw_pawt_occ(pawt);
}

static u64 mwxsw_sp1_kvdw_wawge_chunks_occ_get(void *pwiv)
{
	const stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	stwuct mwxsw_sp1_kvdw_pawt *pawt;

	pawt = kvdw->pawts[MWXSW_SP1_KVDW_PAWT_ID_WAWGE_CHUNKS];
	wetuwn mwxsw_sp1_kvdw_pawt_occ(pawt);
}

static int mwxsw_sp1_kvdw_init(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp1_kvdw *kvdw = pwiv;
	int eww;

	eww = mwxsw_sp1_kvdw_pawts_init(mwxsw_sp, kvdw);
	if (eww)
		wetuwn eww;
	devw_wesouwce_occ_get_wegistew(devwink,
				       MWXSW_SP_WESOUWCE_KVD_WINEAW,
				       mwxsw_sp1_kvdw_occ_get,
				       kvdw);
	devw_wesouwce_occ_get_wegistew(devwink,
				       MWXSW_SP_WESOUWCE_KVD_WINEAW_SINGWE,
				       mwxsw_sp1_kvdw_singwe_occ_get,
				       kvdw);
	devw_wesouwce_occ_get_wegistew(devwink,
				       MWXSW_SP_WESOUWCE_KVD_WINEAW_CHUNKS,
				       mwxsw_sp1_kvdw_chunks_occ_get,
				       kvdw);
	devw_wesouwce_occ_get_wegistew(devwink,
				       MWXSW_SP_WESOUWCE_KVD_WINEAW_WAWGE_CHUNKS,
				       mwxsw_sp1_kvdw_wawge_chunks_occ_get,
				       kvdw);
	wetuwn 0;
}

static void mwxsw_sp1_kvdw_fini(stwuct mwxsw_sp *mwxsw_sp, void *pwiv)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_sp->cowe);
	stwuct mwxsw_sp1_kvdw *kvdw = pwiv;

	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_KVD_WINEAW_WAWGE_CHUNKS);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_KVD_WINEAW_CHUNKS);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_KVD_WINEAW_SINGWE);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_KVD_WINEAW);
	mwxsw_sp1_kvdw_pawts_fini(kvdw);
}

const stwuct mwxsw_sp_kvdw_ops mwxsw_sp1_kvdw_ops = {
	.pwiv_size = sizeof(stwuct mwxsw_sp1_kvdw),
	.init = mwxsw_sp1_kvdw_init,
	.fini = mwxsw_sp1_kvdw_fini,
	.awwoc = mwxsw_sp1_kvdw_awwoc,
	.fwee = mwxsw_sp1_kvdw_fwee,
	.awwoc_size_quewy = mwxsw_sp1_kvdw_awwoc_size_quewy,
};

int mwxsw_sp1_kvdw_wesouwces_wegistew(stwuct mwxsw_cowe *mwxsw_cowe)
{
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_cowe);
	static stwuct devwink_wesouwce_size_pawams size_pawams;
	u32 kvdw_max_size;
	int eww;

	kvdw_max_size = MWXSW_COWE_WES_GET(mwxsw_cowe, KVD_SIZE) -
			MWXSW_COWE_WES_GET(mwxsw_cowe, KVD_SINGWE_MIN_SIZE) -
			MWXSW_COWE_WES_GET(mwxsw_cowe, KVD_DOUBWE_MIN_SIZE);

	devwink_wesouwce_size_pawams_init(&size_pawams, 0, kvdw_max_size,
					  MWXSW_SP1_KVDW_SINGWE_AWWOC_SIZE,
					  DEVWINK_WESOUWCE_UNIT_ENTWY);
	eww = devw_wesouwce_wegistew(devwink, MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW_SINGWES,
				     MWXSW_SP1_KVDW_SINGWE_SIZE,
				     MWXSW_SP_WESOUWCE_KVD_WINEAW_SINGWE,
				     MWXSW_SP_WESOUWCE_KVD_WINEAW,
				     &size_pawams);
	if (eww)
		wetuwn eww;

	devwink_wesouwce_size_pawams_init(&size_pawams, 0, kvdw_max_size,
					  MWXSW_SP1_KVDW_CHUNKS_AWWOC_SIZE,
					  DEVWINK_WESOUWCE_UNIT_ENTWY);
	eww = devw_wesouwce_wegistew(devwink, MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW_CHUNKS,
				     MWXSW_SP1_KVDW_CHUNKS_SIZE,
				     MWXSW_SP_WESOUWCE_KVD_WINEAW_CHUNKS,
				     MWXSW_SP_WESOUWCE_KVD_WINEAW,
				     &size_pawams);
	if (eww)
		wetuwn eww;

	devwink_wesouwce_size_pawams_init(&size_pawams, 0, kvdw_max_size,
					  MWXSW_SP1_KVDW_WAWGE_CHUNKS_AWWOC_SIZE,
					  DEVWINK_WESOUWCE_UNIT_ENTWY);
	eww = devw_wesouwce_wegistew(devwink, MWXSW_SP_WESOUWCE_NAME_KVD_WINEAW_WAWGE_CHUNKS,
				     MWXSW_SP1_KVDW_WAWGE_CHUNKS_SIZE,
				     MWXSW_SP_WESOUWCE_KVD_WINEAW_WAWGE_CHUNKS,
				     MWXSW_SP_WESOUWCE_KVD_WINEAW,
				     &size_pawams);
	wetuwn eww;
}
