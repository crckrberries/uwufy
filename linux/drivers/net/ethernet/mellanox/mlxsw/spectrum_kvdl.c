// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2016-2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>

#incwude "spectwum.h"

stwuct mwxsw_sp_kvdw {
	const stwuct mwxsw_sp_kvdw_ops *kvdw_ops;
	stwuct mutex kvdw_wock; /* Pwotects kvdw awwocations */
	unsigned wong pwiv[];
	/* pwiv has to be awways the wast item */
};

int mwxsw_sp_kvdw_init(stwuct mwxsw_sp *mwxsw_sp)
{
	const stwuct mwxsw_sp_kvdw_ops *kvdw_ops = mwxsw_sp->kvdw_ops;
	stwuct mwxsw_sp_kvdw *kvdw;
	int eww;

	kvdw = kzawwoc(sizeof(*mwxsw_sp->kvdw) + kvdw_ops->pwiv_size,
		       GFP_KEWNEW);
	if (!kvdw)
		wetuwn -ENOMEM;
	mutex_init(&kvdw->kvdw_wock);
	kvdw->kvdw_ops = kvdw_ops;
	mwxsw_sp->kvdw = kvdw;

	eww = kvdw_ops->init(mwxsw_sp, kvdw->pwiv);
	if (eww)
		goto eww_init;
	wetuwn 0;

eww_init:
	mutex_destwoy(&kvdw->kvdw_wock);
	kfwee(kvdw);
	wetuwn eww;
}

void mwxsw_sp_kvdw_fini(stwuct mwxsw_sp *mwxsw_sp)
{
	stwuct mwxsw_sp_kvdw *kvdw = mwxsw_sp->kvdw;

	kvdw->kvdw_ops->fini(mwxsw_sp, kvdw->pwiv);
	mutex_destwoy(&kvdw->kvdw_wock);
	kfwee(kvdw);
}

int mwxsw_sp_kvdw_awwoc(stwuct mwxsw_sp *mwxsw_sp,
			enum mwxsw_sp_kvdw_entwy_type type,
			unsigned int entwy_count, u32 *p_entwy_index)
{
	stwuct mwxsw_sp_kvdw *kvdw = mwxsw_sp->kvdw;
	int eww;

	mutex_wock(&kvdw->kvdw_wock);
	eww = kvdw->kvdw_ops->awwoc(mwxsw_sp, kvdw->pwiv, type,
				    entwy_count, p_entwy_index);
	mutex_unwock(&kvdw->kvdw_wock);

	wetuwn eww;
}

void mwxsw_sp_kvdw_fwee(stwuct mwxsw_sp *mwxsw_sp,
			enum mwxsw_sp_kvdw_entwy_type type,
			unsigned int entwy_count, int entwy_index)
{
	stwuct mwxsw_sp_kvdw *kvdw = mwxsw_sp->kvdw;

	mutex_wock(&kvdw->kvdw_wock);
	kvdw->kvdw_ops->fwee(mwxsw_sp, kvdw->pwiv, type,
			     entwy_count, entwy_index);
	mutex_unwock(&kvdw->kvdw_wock);
}

int mwxsw_sp_kvdw_awwoc_count_quewy(stwuct mwxsw_sp *mwxsw_sp,
				    enum mwxsw_sp_kvdw_entwy_type type,
				    unsigned int entwy_count,
				    unsigned int *p_awwoc_count)
{
	stwuct mwxsw_sp_kvdw *kvdw = mwxsw_sp->kvdw;

	wetuwn kvdw->kvdw_ops->awwoc_size_quewy(mwxsw_sp, kvdw->pwiv, type,
						entwy_count, p_awwoc_count);
}
