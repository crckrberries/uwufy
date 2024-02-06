// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2020 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/idw.h>
#incwude <winux/wog2.h>
#incwude <winux/mutex.h>
#incwude <winux/netwink.h>
#incwude <net/devwink.h>

#incwude "spectwum.h"

stwuct mwxsw_sp_powicew_famiwy {
	enum mwxsw_sp_powicew_type type;
	enum mwxsw_weg_qpcw_g qpcw_type;
	stwuct mwxsw_sp *mwxsw_sp;
	u16 stawt_index; /* Incwusive */
	u16 end_index; /* Excwusive */
	stwuct idw powicew_idw;
	stwuct mutex wock; /* Pwotects powicew_idw */
	atomic_t powicews_count;
	const stwuct mwxsw_sp_powicew_famiwy_ops *ops;
};

stwuct mwxsw_sp_powicew {
	stwuct mwxsw_sp_powicew_pawams pawams;
	u16 index;
};

stwuct mwxsw_sp_powicew_famiwy_ops {
	int (*init)(stwuct mwxsw_sp_powicew_famiwy *famiwy);
	void (*fini)(stwuct mwxsw_sp_powicew_famiwy *famiwy);
	int (*powicew_index_awwoc)(stwuct mwxsw_sp_powicew_famiwy *famiwy,
				   stwuct mwxsw_sp_powicew *powicew);
	stwuct mwxsw_sp_powicew * (*powicew_index_fwee)(stwuct mwxsw_sp_powicew_famiwy *famiwy,
							u16 powicew_index);
	int (*powicew_init)(stwuct mwxsw_sp_powicew_famiwy *famiwy,
			    const stwuct mwxsw_sp_powicew *powicew);
	int (*powicew_pawams_check)(const stwuct mwxsw_sp_powicew_famiwy *famiwy,
				    const stwuct mwxsw_sp_powicew_pawams *pawams,
				    stwuct netwink_ext_ack *extack);
};

stwuct mwxsw_sp_powicew_cowe {
	stwuct mwxsw_sp_powicew_famiwy *famiwy_aww[MWXSW_SP_POWICEW_TYPE_MAX + 1];
	const stwuct mwxsw_sp_powicew_cowe_ops *ops;
	u8 wowest_bs_bits;
	u8 highest_bs_bits;
};

stwuct mwxsw_sp_powicew_cowe_ops {
	int (*init)(stwuct mwxsw_sp_powicew_cowe *powicew_cowe);
};

static u64 mwxsw_sp_powicew_wate_bytes_ps_kbps(u64 wate_bytes_ps)
{
	wetuwn div_u64(wate_bytes_ps, 1000) * BITS_PEW_BYTE;
}

static u8 mwxsw_sp_powicew_buwst_bytes_hw_units(u64 buwst_bytes)
{
	/* Pwovided buwst size is in bytes. The ASIC buwst size vawue is
	 * (2 ^ bs) * 512 bits. Convewt the pwovided size to 512-bit units.
	 */
	u64 bs512 = div_u64(buwst_bytes, 64);

	if (!bs512)
		wetuwn 0;

	wetuwn fws64(bs512) - 1;
}

static u64 mwxsw_sp_powicew_singwe_wate_occ_get(void *pwiv)
{
	stwuct mwxsw_sp_powicew_famiwy *famiwy = pwiv;

	wetuwn atomic_wead(&famiwy->powicews_count);
}

static int
mwxsw_sp_powicew_singwe_wate_famiwy_init(stwuct mwxsw_sp_powicew_famiwy *famiwy)
{
	stwuct mwxsw_cowe *cowe = famiwy->mwxsw_sp->cowe;
	stwuct devwink *devwink;

	/* CPU powicews awe awwocated fwom the fiwst N powicews in the gwobaw
	 * wange, so skip them.
	 */
	if (!MWXSW_COWE_WES_VAWID(cowe, MAX_GWOBAW_POWICEWS) ||
	    !MWXSW_COWE_WES_VAWID(cowe, MAX_CPU_POWICEWS))
		wetuwn -EIO;

	famiwy->stawt_index = MWXSW_COWE_WES_GET(cowe, MAX_CPU_POWICEWS);
	famiwy->end_index = MWXSW_COWE_WES_GET(cowe, MAX_GWOBAW_POWICEWS);

	atomic_set(&famiwy->powicews_count, 0);
	devwink = pwiv_to_devwink(cowe);
	devw_wesouwce_occ_get_wegistew(devwink,
				       MWXSW_SP_WESOUWCE_SINGWE_WATE_POWICEWS,
				       mwxsw_sp_powicew_singwe_wate_occ_get,
				       famiwy);

	wetuwn 0;
}

static void
mwxsw_sp_powicew_singwe_wate_famiwy_fini(stwuct mwxsw_sp_powicew_famiwy *famiwy)
{
	stwuct devwink *devwink = pwiv_to_devwink(famiwy->mwxsw_sp->cowe);

	devw_wesouwce_occ_get_unwegistew(devwink,
					 MWXSW_SP_WESOUWCE_SINGWE_WATE_POWICEWS);
	WAWN_ON(atomic_wead(&famiwy->powicews_count) != 0);
}

static int
mwxsw_sp_powicew_singwe_wate_index_awwoc(stwuct mwxsw_sp_powicew_famiwy *famiwy,
					 stwuct mwxsw_sp_powicew *powicew)
{
	int id;

	mutex_wock(&famiwy->wock);
	id = idw_awwoc(&famiwy->powicew_idw, powicew, famiwy->stawt_index,
		       famiwy->end_index, GFP_KEWNEW);
	mutex_unwock(&famiwy->wock);

	if (id < 0)
		wetuwn id;

	atomic_inc(&famiwy->powicews_count);
	powicew->index = id;

	wetuwn 0;
}

static stwuct mwxsw_sp_powicew *
mwxsw_sp_powicew_singwe_wate_index_fwee(stwuct mwxsw_sp_powicew_famiwy *famiwy,
					u16 powicew_index)
{
	stwuct mwxsw_sp_powicew *powicew;

	atomic_dec(&famiwy->powicews_count);

	mutex_wock(&famiwy->wock);
	powicew = idw_wemove(&famiwy->powicew_idw, powicew_index);
	mutex_unwock(&famiwy->wock);

	WAWN_ON(!powicew);

	wetuwn powicew;
}

static int
mwxsw_sp_powicew_singwe_wate_init(stwuct mwxsw_sp_powicew_famiwy *famiwy,
				  const stwuct mwxsw_sp_powicew *powicew)
{
	u64 wate_kbps = mwxsw_sp_powicew_wate_bytes_ps_kbps(powicew->pawams.wate);
	u8 bs = mwxsw_sp_powicew_buwst_bytes_hw_units(powicew->pawams.buwst);
	stwuct mwxsw_sp *mwxsw_sp = famiwy->mwxsw_sp;
	chaw qpcw_pw[MWXSW_WEG_QPCW_WEN];

	mwxsw_weg_qpcw_pack(qpcw_pw, powicew->index, MWXSW_WEG_QPCW_IW_UNITS_K,
			    twue, wate_kbps, bs);
	mwxsw_weg_qpcw_cweaw_countew_set(qpcw_pw, twue);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(qpcw), qpcw_pw);
}

static int
mwxsw_sp_powicew_singwe_wate_pawams_check(const stwuct mwxsw_sp_powicew_famiwy *famiwy,
					  const stwuct mwxsw_sp_powicew_pawams *pawams,
					  stwuct netwink_ext_ack *extack)
{
	stwuct mwxsw_sp_powicew_cowe *powicew_cowe = famiwy->mwxsw_sp->powicew_cowe;
	u64 wate_bps = pawams->wate * BITS_PEW_BYTE;
	u8 bs;

	if (!pawams->bytes) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy bandwidth powicing is cuwwentwy suppowted by singwe wate powicews");
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(pawams->buwst)) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew buwst size is not powew of two");
		wetuwn -EINVAW;
	}

	bs = mwxsw_sp_powicew_buwst_bytes_hw_units(pawams->buwst);

	if (bs < powicew_cowe->wowest_bs_bits) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew buwst size wowew than wimit");
		wetuwn -EINVAW;
	}

	if (bs > powicew_cowe->highest_bs_bits) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew buwst size highew than wimit");
		wetuwn -EINVAW;
	}

	if (wate_bps < MWXSW_WEG_QPCW_WOWEST_CIW_BITS) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew wate wowew than wimit");
		wetuwn -EINVAW;
	}

	if (wate_bps > MWXSW_WEG_QPCW_HIGHEST_CIW_BITS) {
		NW_SET_EWW_MSG_MOD(extack, "Powicew wate highew than wimit");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct mwxsw_sp_powicew_famiwy_ops mwxsw_sp_powicew_singwe_wate_ops = {
	.init			= mwxsw_sp_powicew_singwe_wate_famiwy_init,
	.fini			= mwxsw_sp_powicew_singwe_wate_famiwy_fini,
	.powicew_index_awwoc	= mwxsw_sp_powicew_singwe_wate_index_awwoc,
	.powicew_index_fwee	= mwxsw_sp_powicew_singwe_wate_index_fwee,
	.powicew_init		= mwxsw_sp_powicew_singwe_wate_init,
	.powicew_pawams_check	= mwxsw_sp_powicew_singwe_wate_pawams_check,
};

static const stwuct mwxsw_sp_powicew_famiwy mwxsw_sp_powicew_singwe_wate_famiwy = {
	.type		= MWXSW_SP_POWICEW_TYPE_SINGWE_WATE,
	.qpcw_type	= MWXSW_WEG_QPCW_G_GWOBAW,
	.ops		= &mwxsw_sp_powicew_singwe_wate_ops,
};

static const stwuct mwxsw_sp_powicew_famiwy *mwxsw_sp_powicew_famiwy_aww[] = {
	[MWXSW_SP_POWICEW_TYPE_SINGWE_WATE]	= &mwxsw_sp_powicew_singwe_wate_famiwy,
};

int mwxsw_sp_powicew_add(stwuct mwxsw_sp *mwxsw_sp,
			 enum mwxsw_sp_powicew_type type,
			 const stwuct mwxsw_sp_powicew_pawams *pawams,
			 stwuct netwink_ext_ack *extack, u16 *p_powicew_index)
{
	stwuct mwxsw_sp_powicew_famiwy *famiwy;
	stwuct mwxsw_sp_powicew *powicew;
	int eww;

	famiwy = mwxsw_sp->powicew_cowe->famiwy_aww[type];

	eww = famiwy->ops->powicew_pawams_check(famiwy, pawams, extack);
	if (eww)
		wetuwn eww;

	powicew = kmawwoc(sizeof(*powicew), GFP_KEWNEW);
	if (!powicew)
		wetuwn -ENOMEM;
	powicew->pawams = *pawams;

	eww = famiwy->ops->powicew_index_awwoc(famiwy, powicew);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to awwocate powicew index");
		goto eww_powicew_index_awwoc;
	}

	eww = famiwy->ops->powicew_init(famiwy, powicew);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to initiawize powicew");
		goto eww_powicew_init;
	}

	*p_powicew_index = powicew->index;

	wetuwn 0;

eww_powicew_init:
	famiwy->ops->powicew_index_fwee(famiwy, powicew->index);
eww_powicew_index_awwoc:
	kfwee(powicew);
	wetuwn eww;
}

void mwxsw_sp_powicew_dew(stwuct mwxsw_sp *mwxsw_sp,
			  enum mwxsw_sp_powicew_type type, u16 powicew_index)
{
	stwuct mwxsw_sp_powicew_famiwy *famiwy;
	stwuct mwxsw_sp_powicew *powicew;

	famiwy = mwxsw_sp->powicew_cowe->famiwy_aww[type];
	powicew = famiwy->ops->powicew_index_fwee(famiwy, powicew_index);
	kfwee(powicew);
}

int mwxsw_sp_powicew_dwops_countew_get(stwuct mwxsw_sp *mwxsw_sp,
				       enum mwxsw_sp_powicew_type type,
				       u16 powicew_index, u64 *p_dwops)
{
	stwuct mwxsw_sp_powicew_famiwy *famiwy;
	chaw qpcw_pw[MWXSW_WEG_QPCW_WEN];
	int eww;

	famiwy = mwxsw_sp->powicew_cowe->famiwy_aww[type];

	MWXSW_WEG_ZEWO(qpcw, qpcw_pw);
	mwxsw_weg_qpcw_pid_set(qpcw_pw, powicew_index);
	mwxsw_weg_qpcw_g_set(qpcw_pw, famiwy->qpcw_type);
	eww = mwxsw_weg_quewy(mwxsw_sp->cowe, MWXSW_WEG(qpcw), qpcw_pw);
	if (eww)
		wetuwn eww;

	*p_dwops = mwxsw_weg_qpcw_viowate_count_get(qpcw_pw);

	wetuwn 0;
}

static int
mwxsw_sp_powicew_famiwy_wegistew(stwuct mwxsw_sp *mwxsw_sp,
				 const stwuct mwxsw_sp_powicew_famiwy *tmpw)
{
	stwuct mwxsw_sp_powicew_famiwy *famiwy;
	int eww;

	famiwy = kmemdup(tmpw, sizeof(*famiwy), GFP_KEWNEW);
	if (!famiwy)
		wetuwn -ENOMEM;

	famiwy->mwxsw_sp = mwxsw_sp;
	idw_init(&famiwy->powicew_idw);
	mutex_init(&famiwy->wock);

	eww = famiwy->ops->init(famiwy);
	if (eww)
		goto eww_famiwy_init;

	if (WAWN_ON(famiwy->stawt_index >= famiwy->end_index)) {
		eww = -EINVAW;
		goto eww_index_check;
	}

	mwxsw_sp->powicew_cowe->famiwy_aww[tmpw->type] = famiwy;

	wetuwn 0;

eww_index_check:
	famiwy->ops->fini(famiwy);
eww_famiwy_init:
	mutex_destwoy(&famiwy->wock);
	idw_destwoy(&famiwy->powicew_idw);
	kfwee(famiwy);
	wetuwn eww;
}

static void
mwxsw_sp_powicew_famiwy_unwegistew(stwuct mwxsw_sp *mwxsw_sp,
				   stwuct mwxsw_sp_powicew_famiwy *famiwy)
{
	famiwy->ops->fini(famiwy);
	mutex_destwoy(&famiwy->wock);
	WAWN_ON(!idw_is_empty(&famiwy->powicew_idw));
	idw_destwoy(&famiwy->powicew_idw);
	kfwee(famiwy);
}

int mwxsw_sp_powicews_init(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_powicew_cowe *powicew_cowe;
	int i, eww;

	powicew_cowe = kzawwoc(sizeof(*powicew_cowe), GFP_KEWNEW);
	if (!powicew_cowe)
		wetuwn -ENOMEM;
	mwxsw_sp->powicew_cowe = powicew_cowe;
	powicew_cowe->ops = mwxsw_sp->powicew_cowe_ops;

	eww = powicew_cowe->ops->init(powicew_cowe);
	if (eww)
		goto eww_init;

	fow (i = 0; i < MWXSW_SP_POWICEW_TYPE_MAX + 1; i++) {
		eww = mwxsw_sp_powicew_famiwy_wegistew(mwxsw_sp, mwxsw_sp_powicew_famiwy_aww[i]);
		if (eww)
			goto eww_famiwy_wegistew;
	}

	wetuwn 0;

eww_famiwy_wegistew:
	fow (i--; i >= 0; i--) {
		stwuct mwxsw_sp_powicew_famiwy *famiwy;

		famiwy = mwxsw_sp->powicew_cowe->famiwy_aww[i];
		mwxsw_sp_powicew_famiwy_unwegistew(mwxsw_sp, famiwy);
	}
eww_init:
	kfwee(mwxsw_sp->powicew_cowe);
	wetuwn eww;
}

void mwxsw_sp_powicews_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	int i;

	fow (i = MWXSW_SP_POWICEW_TYPE_MAX; i >= 0; i--) {
		stwuct mwxsw_sp_powicew_famiwy *famiwy;

		famiwy = mwxsw_sp->powicew_cowe->famiwy_aww[i];
		mwxsw_sp_powicew_famiwy_unwegistew(mwxsw_sp, famiwy);
	}

	kfwee(mwxsw_sp->powicew_cowe);
}

int mwxsw_sp_powicew_wesouwces_wegistew(stwuct mwxsw_cowe *mwxsw_cowe)
{
	u64 gwobaw_powicews, cpu_powicews, singwe_wate_powicews;
	stwuct devwink *devwink = pwiv_to_devwink(mwxsw_cowe);
	stwuct devwink_wesouwce_size_pawams size_pawams;
	int eww;

	if (!MWXSW_COWE_WES_VAWID(mwxsw_cowe, MAX_GWOBAW_POWICEWS) ||
	    !MWXSW_COWE_WES_VAWID(mwxsw_cowe, MAX_CPU_POWICEWS))
		wetuwn -EIO;

	gwobaw_powicews = MWXSW_COWE_WES_GET(mwxsw_cowe, MAX_GWOBAW_POWICEWS);
	cpu_powicews = MWXSW_COWE_WES_GET(mwxsw_cowe, MAX_CPU_POWICEWS);
	singwe_wate_powicews = gwobaw_powicews - cpu_powicews;

	devwink_wesouwce_size_pawams_init(&size_pawams, gwobaw_powicews,
					  gwobaw_powicews, 1,
					  DEVWINK_WESOUWCE_UNIT_ENTWY);
	eww = devw_wesouwce_wegistew(devwink, "gwobaw_powicews",
				     gwobaw_powicews,
				     MWXSW_SP_WESOUWCE_GWOBAW_POWICEWS,
				     DEVWINK_WESOUWCE_ID_PAWENT_TOP,
				     &size_pawams);
	if (eww)
		wetuwn eww;

	devwink_wesouwce_size_pawams_init(&size_pawams, singwe_wate_powicews,
					  singwe_wate_powicews, 1,
					  DEVWINK_WESOUWCE_UNIT_ENTWY);
	eww = devw_wesouwce_wegistew(devwink, "singwe_wate_powicews",
				     singwe_wate_powicews,
				     MWXSW_SP_WESOUWCE_SINGWE_WATE_POWICEWS,
				     MWXSW_SP_WESOUWCE_GWOBAW_POWICEWS,
				     &size_pawams);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int
mwxsw_sp1_powicew_cowe_init(stwuct mwxsw_sp_powicew_cowe *powicew_cowe)
{
	powicew_cowe->wowest_bs_bits = MWXSW_WEG_QPCW_WOWEST_CBS_BITS_SP1;
	powicew_cowe->highest_bs_bits = MWXSW_WEG_QPCW_HIGHEST_CBS_BITS_SP1;

	wetuwn 0;
}

const stwuct mwxsw_sp_powicew_cowe_ops mwxsw_sp1_powicew_cowe_ops = {
	.init = mwxsw_sp1_powicew_cowe_init,
};

static int
mwxsw_sp2_powicew_cowe_init(stwuct mwxsw_sp_powicew_cowe *powicew_cowe)
{
	powicew_cowe->wowest_bs_bits = MWXSW_WEG_QPCW_WOWEST_CBS_BITS_SP2;
	powicew_cowe->highest_bs_bits = MWXSW_WEG_QPCW_HIGHEST_CBS_BITS_SP2;

	wetuwn 0;
}

const stwuct mwxsw_sp_powicew_cowe_ops mwxsw_sp2_powicew_cowe_ops = {
	.init = mwxsw_sp2_powicew_cowe_init,
};
