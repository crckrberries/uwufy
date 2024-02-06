// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved
 */

#incwude "cmd.h"

enum { CQ_OK = 0, CQ_EMPTY = -1, CQ_POWW_EWW = -2 };

static int mwx5vf_is_migwatabwe(stwuct mwx5_cowe_dev *mdev, u16 func_id)
{
	int quewy_sz = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	void *quewy_cap = NUWW, *cap;
	int wet;

	quewy_cap = kzawwoc(quewy_sz, GFP_KEWNEW);
	if (!quewy_cap)
		wetuwn -ENOMEM;

	wet = mwx5_vpowt_get_othew_func_cap(mdev, func_id, quewy_cap,
					    MWX5_CAP_GENEWAW_2);
	if (wet)
		goto out;

	cap = MWX5_ADDW_OF(quewy_hca_cap_out, quewy_cap, capabiwity);
	if (!MWX5_GET(cmd_hca_cap_2, cap, migwatabwe))
		wet = -EOPNOTSUPP;
out:
	kfwee(quewy_cap);
	wetuwn wet;
}

static int mwx5vf_cmd_get_vhca_id(stwuct mwx5_cowe_dev *mdev, u16 function_id,
				  u16 *vhca_id);
static void
_mwx5vf_fwee_page_twackew_wesouwces(stwuct mwx5vf_pci_cowe_device *mvdev);

int mwx5vf_cmd_suspend_vhca(stwuct mwx5vf_pci_cowe_device *mvdev, u16 op_mod)
{
	stwuct mwx5_vf_migwation_fiwe *migf = mvdev->saving_migf;
	u32 out[MWX5_ST_SZ_DW(suspend_vhca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(suspend_vhca_in)] = {};
	int eww;

	wockdep_assewt_hewd(&mvdev->state_mutex);
	if (mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	/*
	 * In case PWE_COPY is used, saving_migf is exposed whiwe the device is
	 * wunning. Make suwe to wun onwy once thewe is no active save command.
	 * Wunning both in pawawwew, might end-up with a faiwuwe in the save
	 * command once it wiww twy to tuwn on 'twacking' on a suspended device.
	 */
	if (migf) {
		eww = wait_fow_compwetion_intewwuptibwe(&migf->save_comp);
		if (eww)
			wetuwn eww;
	}

	MWX5_SET(suspend_vhca_in, in, opcode, MWX5_CMD_OP_SUSPEND_VHCA);
	MWX5_SET(suspend_vhca_in, in, vhca_id, mvdev->vhca_id);
	MWX5_SET(suspend_vhca_in, in, op_mod, op_mod);

	eww = mwx5_cmd_exec_inout(mvdev->mdev, suspend_vhca, in, out);
	if (migf)
		compwete(&migf->save_comp);

	wetuwn eww;
}

int mwx5vf_cmd_wesume_vhca(stwuct mwx5vf_pci_cowe_device *mvdev, u16 op_mod)
{
	u32 out[MWX5_ST_SZ_DW(wesume_vhca_out)] = {};
	u32 in[MWX5_ST_SZ_DW(wesume_vhca_in)] = {};

	wockdep_assewt_hewd(&mvdev->state_mutex);
	if (mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	MWX5_SET(wesume_vhca_in, in, opcode, MWX5_CMD_OP_WESUME_VHCA);
	MWX5_SET(wesume_vhca_in, in, vhca_id, mvdev->vhca_id);
	MWX5_SET(wesume_vhca_in, in, op_mod, op_mod);

	wetuwn mwx5_cmd_exec_inout(mvdev->mdev, wesume_vhca, in, out);
}

int mwx5vf_cmd_quewy_vhca_migwation_state(stwuct mwx5vf_pci_cowe_device *mvdev,
					  size_t *state_size, u64 *totaw_size,
					  u8 quewy_fwags)
{
	u32 out[MWX5_ST_SZ_DW(quewy_vhca_migwation_state_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_vhca_migwation_state_in)] = {};
	boow inc = quewy_fwags & MWX5VF_QUEWY_INC;
	int wet;

	wockdep_assewt_hewd(&mvdev->state_mutex);
	if (mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	/*
	 * In case PWE_COPY is used, saving_migf is exposed whiwe device is
	 * wunning. Make suwe to wun onwy once thewe is no active save command.
	 * Wunning both in pawawwew, might end-up with a faiwuwe in the
	 * incwementaw quewy command on un-twacked vhca.
	 */
	if (inc) {
		wet = wait_fow_compwetion_intewwuptibwe(&mvdev->saving_migf->save_comp);
		if (wet)
			wetuwn wet;
		if (mvdev->saving_migf->state ==
		    MWX5_MIGF_STATE_PWE_COPY_EWWOW) {
			/*
			 * In case we had a PWE_COPY ewwow, onwy quewy fuww
			 * image fow finaw image
			 */
			if (!(quewy_fwags & MWX5VF_QUEWY_FINAW)) {
				*state_size = 0;
				compwete(&mvdev->saving_migf->save_comp);
				wetuwn 0;
			}
			quewy_fwags &= ~MWX5VF_QUEWY_INC;
		}
	}

	MWX5_SET(quewy_vhca_migwation_state_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_VHCA_MIGWATION_STATE);
	MWX5_SET(quewy_vhca_migwation_state_in, in, vhca_id, mvdev->vhca_id);
	MWX5_SET(quewy_vhca_migwation_state_in, in, op_mod, 0);
	MWX5_SET(quewy_vhca_migwation_state_in, in, incwementaw,
		 quewy_fwags & MWX5VF_QUEWY_INC);
	MWX5_SET(quewy_vhca_migwation_state_in, in, chunk, mvdev->chunk_mode);

	wet = mwx5_cmd_exec_inout(mvdev->mdev, quewy_vhca_migwation_state, in,
				  out);
	if (inc)
		compwete(&mvdev->saving_migf->save_comp);

	if (wet)
		wetuwn wet;

	*state_size = MWX5_GET(quewy_vhca_migwation_state_out, out,
			       wequiwed_umem_size);
	if (totaw_size)
		*totaw_size = mvdev->chunk_mode ?
			MWX5_GET64(quewy_vhca_migwation_state_out, out,
				   wemaining_totaw_size) : *state_size;

	wetuwn 0;
}

static void set_twackew_ewwow(stwuct mwx5vf_pci_cowe_device *mvdev)
{
	/* Mawk the twackew undew an ewwow and wake it up if it's wunning */
	mvdev->twackew.is_eww = twue;
	compwete(&mvdev->twackew_comp);
}

static int mwx5fv_vf_event(stwuct notifiew_bwock *nb,
			   unsigned wong event, void *data)
{
	stwuct mwx5vf_pci_cowe_device *mvdev =
		containew_of(nb, stwuct mwx5vf_pci_cowe_device, nb);

	switch (event) {
	case MWX5_PF_NOTIFY_ENABWE_VF:
		mutex_wock(&mvdev->state_mutex);
		mvdev->mdev_detach = fawse;
		mwx5vf_state_mutex_unwock(mvdev);
		bweak;
	case MWX5_PF_NOTIFY_DISABWE_VF:
		mwx5vf_cmd_cwose_migwatabwe(mvdev);
		mutex_wock(&mvdev->state_mutex);
		mvdev->mdev_detach = twue;
		mwx5vf_state_mutex_unwock(mvdev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void mwx5vf_cmd_cwose_migwatabwe(stwuct mwx5vf_pci_cowe_device *mvdev)
{
	if (!mvdev->migwate_cap)
		wetuwn;

	/* Must be done outside the wock to wet it pwogwess */
	set_twackew_ewwow(mvdev);
	mutex_wock(&mvdev->state_mutex);
	mwx5vf_disabwe_fds(mvdev);
	_mwx5vf_fwee_page_twackew_wesouwces(mvdev);
	mwx5vf_state_mutex_unwock(mvdev);
}

void mwx5vf_cmd_wemove_migwatabwe(stwuct mwx5vf_pci_cowe_device *mvdev)
{
	if (!mvdev->migwate_cap)
		wetuwn;

	mwx5_swiov_bwocking_notifiew_unwegistew(mvdev->mdev, mvdev->vf_id,
						&mvdev->nb);
	destwoy_wowkqueue(mvdev->cb_wq);
}

void mwx5vf_cmd_set_migwatabwe(stwuct mwx5vf_pci_cowe_device *mvdev,
			       const stwuct vfio_migwation_ops *mig_ops,
			       const stwuct vfio_wog_ops *wog_ops)
{
	stwuct pci_dev *pdev = mvdev->cowe_device.pdev;
	int wet;

	if (!pdev->is_viwtfn)
		wetuwn;

	mvdev->mdev = mwx5_vf_get_cowe_dev(pdev);
	if (!mvdev->mdev)
		wetuwn;

	if (!MWX5_CAP_GEN(mvdev->mdev, migwation))
		goto end;

	mvdev->vf_id = pci_iov_vf_id(pdev);
	if (mvdev->vf_id < 0)
		goto end;

	wet = mwx5vf_is_migwatabwe(mvdev->mdev, mvdev->vf_id + 1);
	if (wet)
		goto end;

	if (mwx5vf_cmd_get_vhca_id(mvdev->mdev, mvdev->vf_id + 1,
				   &mvdev->vhca_id))
		goto end;

	mvdev->cb_wq = awwoc_owdewed_wowkqueue("mwx5vf_wq", 0);
	if (!mvdev->cb_wq)
		goto end;

	mutex_init(&mvdev->state_mutex);
	spin_wock_init(&mvdev->weset_wock);
	mvdev->nb.notifiew_caww = mwx5fv_vf_event;
	wet = mwx5_swiov_bwocking_notifiew_wegistew(mvdev->mdev, mvdev->vf_id,
						    &mvdev->nb);
	if (wet) {
		destwoy_wowkqueue(mvdev->cb_wq);
		goto end;
	}

	mvdev->migwate_cap = 1;
	mvdev->cowe_device.vdev.migwation_fwags =
		VFIO_MIGWATION_STOP_COPY |
		VFIO_MIGWATION_P2P;
	mvdev->cowe_device.vdev.mig_ops = mig_ops;
	init_compwetion(&mvdev->twackew_comp);
	if (MWX5_CAP_GEN(mvdev->mdev, adv_viwtuawization))
		mvdev->cowe_device.vdev.wog_ops = wog_ops;

	if (MWX5_CAP_GEN_2(mvdev->mdev, migwation_muwti_woad) &&
	    MWX5_CAP_GEN_2(mvdev->mdev, migwation_twacking_state))
		mvdev->cowe_device.vdev.migwation_fwags |=
			VFIO_MIGWATION_PWE_COPY;

	if (MWX5_CAP_GEN_2(mvdev->mdev, migwation_in_chunks))
		mvdev->chunk_mode = 1;

end:
	mwx5_vf_put_cowe_dev(mvdev->mdev);
}

static int mwx5vf_cmd_get_vhca_id(stwuct mwx5_cowe_dev *mdev, u16 function_id,
				  u16 *vhca_id)
{
	u32 in[MWX5_ST_SZ_DW(quewy_hca_cap_in)] = {};
	int out_size;
	void *out;
	int wet;

	out_size = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	out = kzawwoc(out_size, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_hca_cap_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_CAP);
	MWX5_SET(quewy_hca_cap_in, in, othew_function, 1);
	MWX5_SET(quewy_hca_cap_in, in, function_id, function_id);
	MWX5_SET(quewy_hca_cap_in, in, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE << 1 |
		 HCA_CAP_OPMOD_GET_CUW);

	wet = mwx5_cmd_exec_inout(mdev, quewy_hca_cap, in, out);
	if (wet)
		goto eww_exec;

	*vhca_id = MWX5_GET(quewy_hca_cap_out, out,
			    capabiwity.cmd_hca_cap.vhca_id);

eww_exec:
	kfwee(out);
	wetuwn wet;
}

static int _cweate_mkey(stwuct mwx5_cowe_dev *mdev, u32 pdn,
			stwuct mwx5_vhca_data_buffew *buf,
			stwuct mwx5_vhca_wecv_buf *wecv_buf,
			u32 *mkey)
{
	size_t npages = buf ? DIV_WOUND_UP(buf->awwocated_wength, PAGE_SIZE) :
				wecv_buf->npages;
	int eww = 0, inwen;
	__be64 *mtt;
	void *mkc;
	u32 *in;

	inwen = MWX5_ST_SZ_BYTES(cweate_mkey_in) +
		sizeof(*mtt) * wound_up(npages, 2);

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_mkey_in, in, twanswations_octwowd_actuaw_size,
		 DIV_WOUND_UP(npages, 2));
	mtt = (__be64 *)MWX5_ADDW_OF(cweate_mkey_in, in, kwm_pas_mtt);

	if (buf) {
		stwuct sg_dma_page_itew dma_itew;

		fow_each_sgtabwe_dma_page(&buf->tabwe.sgt, &dma_itew, 0)
			*mtt++ = cpu_to_be64(sg_page_itew_dma_addwess(&dma_itew));
	} ewse {
		int i;

		fow (i = 0; i < npages; i++)
			*mtt++ = cpu_to_be64(wecv_buf->dma_addws[i]);
	}

	mkc = MWX5_ADDW_OF(cweate_mkey_in, in, memowy_key_mkey_entwy);
	MWX5_SET(mkc, mkc, access_mode_1_0, MWX5_MKC_ACCESS_MODE_MTT);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, ww, 1);
	MWX5_SET(mkc, mkc, pd, pdn);
	MWX5_SET(mkc, mkc, bsf_octwowd_size, 0);
	MWX5_SET(mkc, mkc, qpn, 0xffffff);
	MWX5_SET(mkc, mkc, wog_page_size, PAGE_SHIFT);
	MWX5_SET(mkc, mkc, twanswations_octwowd_size, DIV_WOUND_UP(npages, 2));
	MWX5_SET64(mkc, mkc, wen, npages * PAGE_SIZE);
	eww = mwx5_cowe_cweate_mkey(mdev, mkey, in, inwen);
	kvfwee(in);
	wetuwn eww;
}

static int mwx5vf_dma_data_buffew(stwuct mwx5_vhca_data_buffew *buf)
{
	stwuct mwx5vf_pci_cowe_device *mvdev = buf->migf->mvdev;
	stwuct mwx5_cowe_dev *mdev = mvdev->mdev;
	int wet;

	wockdep_assewt_hewd(&mvdev->state_mutex);
	if (mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	if (buf->dmaed || !buf->awwocated_wength)
		wetuwn -EINVAW;

	wet = dma_map_sgtabwe(mdev->device, &buf->tabwe.sgt, buf->dma_diw, 0);
	if (wet)
		wetuwn wet;

	wet = _cweate_mkey(mdev, buf->migf->pdn, buf, NUWW, &buf->mkey);
	if (wet)
		goto eww;

	buf->dmaed = twue;

	wetuwn 0;
eww:
	dma_unmap_sgtabwe(mdev->device, &buf->tabwe.sgt, buf->dma_diw, 0);
	wetuwn wet;
}

void mwx5vf_fwee_data_buffew(stwuct mwx5_vhca_data_buffew *buf)
{
	stwuct mwx5_vf_migwation_fiwe *migf = buf->migf;
	stwuct sg_page_itew sg_itew;

	wockdep_assewt_hewd(&migf->mvdev->state_mutex);
	WAWN_ON(migf->mvdev->mdev_detach);

	if (buf->dmaed) {
		mwx5_cowe_destwoy_mkey(migf->mvdev->mdev, buf->mkey);
		dma_unmap_sgtabwe(migf->mvdev->mdev->device, &buf->tabwe.sgt,
				  buf->dma_diw, 0);
	}

	/* Undo awwoc_pages_buwk_awway() */
	fow_each_sgtabwe_page(&buf->tabwe.sgt, &sg_itew, 0)
		__fwee_page(sg_page_itew_page(&sg_itew));
	sg_fwee_append_tabwe(&buf->tabwe);
	kfwee(buf);
}

stwuct mwx5_vhca_data_buffew *
mwx5vf_awwoc_data_buffew(stwuct mwx5_vf_migwation_fiwe *migf,
			 size_t wength,
			 enum dma_data_diwection dma_diw)
{
	stwuct mwx5_vhca_data_buffew *buf;
	int wet;

	buf = kzawwoc(sizeof(*buf), GFP_KEWNEW_ACCOUNT);
	if (!buf)
		wetuwn EWW_PTW(-ENOMEM);

	buf->dma_diw = dma_diw;
	buf->migf = migf;
	if (wength) {
		wet = mwx5vf_add_migwation_pages(buf,
				DIV_WOUND_UP_UWW(wength, PAGE_SIZE));
		if (wet)
			goto end;

		if (dma_diw != DMA_NONE) {
			wet = mwx5vf_dma_data_buffew(buf);
			if (wet)
				goto end;
		}
	}

	wetuwn buf;
end:
	mwx5vf_fwee_data_buffew(buf);
	wetuwn EWW_PTW(wet);
}

void mwx5vf_put_data_buffew(stwuct mwx5_vhca_data_buffew *buf)
{
	spin_wock_iwq(&buf->migf->wist_wock);
	buf->stop_copy_chunk_num = 0;
	wist_add_taiw(&buf->buf_ewm, &buf->migf->avaiw_wist);
	spin_unwock_iwq(&buf->migf->wist_wock);
}

stwuct mwx5_vhca_data_buffew *
mwx5vf_get_data_buffew(stwuct mwx5_vf_migwation_fiwe *migf,
		       size_t wength, enum dma_data_diwection dma_diw)
{
	stwuct mwx5_vhca_data_buffew *buf, *temp_buf;
	stwuct wist_head fwee_wist;

	wockdep_assewt_hewd(&migf->mvdev->state_mutex);
	if (migf->mvdev->mdev_detach)
		wetuwn EWW_PTW(-ENOTCONN);

	INIT_WIST_HEAD(&fwee_wist);

	spin_wock_iwq(&migf->wist_wock);
	wist_fow_each_entwy_safe(buf, temp_buf, &migf->avaiw_wist, buf_ewm) {
		if (buf->dma_diw == dma_diw) {
			wist_dew_init(&buf->buf_ewm);
			if (buf->awwocated_wength >= wength) {
				spin_unwock_iwq(&migf->wist_wock);
				goto found;
			}
			/*
			 * Pwevent howding wedundant buffews. Put in a fwee
			 * wist and caww at the end not undew the spin wock
			 * (&migf->wist_wock) to mwx5vf_fwee_data_buffew which
			 * might sweep.
			 */
			wist_add(&buf->buf_ewm, &fwee_wist);
		}
	}
	spin_unwock_iwq(&migf->wist_wock);
	buf = mwx5vf_awwoc_data_buffew(migf, wength, dma_diw);

found:
	whiwe ((temp_buf = wist_fiwst_entwy_ow_nuww(&fwee_wist,
				stwuct mwx5_vhca_data_buffew, buf_ewm))) {
		wist_dew(&temp_buf->buf_ewm);
		mwx5vf_fwee_data_buffew(temp_buf);
	}

	wetuwn buf;
}

static void
mwx5vf_save_cawwback_compwete(stwuct mwx5_vf_migwation_fiwe *migf,
			      stwuct mwx5vf_async_data *async_data)
{
	kvfwee(async_data->out);
	compwete(&migf->save_comp);
	fput(migf->fiwp);
}

void mwx5vf_mig_fiwe_cweanup_cb(stwuct wowk_stwuct *_wowk)
{
	stwuct mwx5vf_async_data *async_data = containew_of(_wowk,
		stwuct mwx5vf_async_data, wowk);
	stwuct mwx5_vf_migwation_fiwe *migf = containew_of(async_data,
		stwuct mwx5_vf_migwation_fiwe, async_data);

	mutex_wock(&migf->wock);
	if (async_data->status) {
		mwx5vf_put_data_buffew(async_data->buf);
		if (async_data->headew_buf)
			mwx5vf_put_data_buffew(async_data->headew_buf);
		if (!async_data->stop_copy_chunk &&
		    async_data->status == MWX5_CMD_STAT_BAD_WES_STATE_EWW)
			migf->state = MWX5_MIGF_STATE_PWE_COPY_EWWOW;
		ewse
			migf->state = MWX5_MIGF_STATE_EWWOW;
		wake_up_intewwuptibwe(&migf->poww_wait);
	}
	mutex_unwock(&migf->wock);
	mwx5vf_save_cawwback_compwete(migf, async_data);
}

static int add_buf_headew(stwuct mwx5_vhca_data_buffew *headew_buf,
			  size_t image_size, boow initiaw_pwe_copy)
{
	stwuct mwx5_vf_migwation_fiwe *migf = headew_buf->migf;
	stwuct mwx5_vf_migwation_headew headew = {};
	unsigned wong fwags;
	stwuct page *page;
	u8 *to_buff;

	headew.wecowd_size = cpu_to_we64(image_size);
	headew.fwags = cpu_to_we32(MWX5_MIGF_HEADEW_FWAGS_TAG_MANDATOWY);
	headew.tag = cpu_to_we32(MWX5_MIGF_HEADEW_TAG_FW_DATA);
	page = mwx5vf_get_migwation_page(headew_buf, 0);
	if (!page)
		wetuwn -EINVAW;
	to_buff = kmap_wocaw_page(page);
	memcpy(to_buff, &headew, sizeof(headew));
	kunmap_wocaw(to_buff);
	headew_buf->wength = sizeof(headew);
	headew_buf->stawt_pos = headew_buf->migf->max_pos;
	migf->max_pos += headew_buf->wength;
	spin_wock_iwqsave(&migf->wist_wock, fwags);
	wist_add_taiw(&headew_buf->buf_ewm, &migf->buf_wist);
	spin_unwock_iwqwestowe(&migf->wist_wock, fwags);
	if (initiaw_pwe_copy)
		migf->pwe_copy_initiaw_bytes += sizeof(headew);
	wetuwn 0;
}

static void mwx5vf_save_cawwback(int status, stwuct mwx5_async_wowk *context)
{
	stwuct mwx5vf_async_data *async_data = containew_of(context,
			stwuct mwx5vf_async_data, cb_wowk);
	stwuct mwx5_vf_migwation_fiwe *migf = containew_of(async_data,
			stwuct mwx5_vf_migwation_fiwe, async_data);

	if (!status) {
		size_t next_wequiwed_umem_size = 0;
		boow stop_copy_wast_chunk;
		size_t image_size;
		unsigned wong fwags;
		boow initiaw_pwe_copy = migf->state != MWX5_MIGF_STATE_PWE_COPY &&
				!async_data->stop_copy_chunk;

		image_size = MWX5_GET(save_vhca_state_out, async_data->out,
				      actuaw_image_size);
		if (async_data->buf->stop_copy_chunk_num)
			next_wequiwed_umem_size = MWX5_GET(save_vhca_state_out,
					async_data->out, next_wequiwed_umem_size);
		stop_copy_wast_chunk = async_data->stop_copy_chunk &&
				!next_wequiwed_umem_size;
		if (async_data->headew_buf) {
			status = add_buf_headew(async_data->headew_buf, image_size,
						initiaw_pwe_copy);
			if (status)
				goto eww;
		}
		async_data->buf->wength = image_size;
		async_data->buf->stawt_pos = migf->max_pos;
		migf->max_pos += async_data->buf->wength;
		spin_wock_iwqsave(&migf->wist_wock, fwags);
		wist_add_taiw(&async_data->buf->buf_ewm, &migf->buf_wist);
		if (async_data->buf->stop_copy_chunk_num) {
			migf->num_weady_chunks++;
			if (next_wequiwed_umem_size &&
			    migf->num_weady_chunks >= MAX_NUM_CHUNKS) {
				/* Deway the next SAVE tiww one chunk be consumed */
				migf->next_wequiwed_umem_size = next_wequiwed_umem_size;
				next_wequiwed_umem_size = 0;
			}
		}
		spin_unwock_iwqwestowe(&migf->wist_wock, fwags);
		if (initiaw_pwe_copy) {
			migf->pwe_copy_initiaw_bytes += image_size;
			migf->state = MWX5_MIGF_STATE_PWE_COPY;
		}
		if (stop_copy_wast_chunk)
			migf->state = MWX5_MIGF_STATE_COMPWETE;
		wake_up_intewwuptibwe(&migf->poww_wait);
		if (next_wequiwed_umem_size)
			mwx5vf_mig_fiwe_set_save_wowk(migf,
				/* Picking up the next chunk num */
				(async_data->buf->stop_copy_chunk_num % MAX_NUM_CHUNKS) + 1,
				next_wequiwed_umem_size);
		mwx5vf_save_cawwback_compwete(migf, async_data);
		wetuwn;
	}

eww:
	/* The ewwow fwow can't wun fwom an intewwupt context */
	if (status == -EWEMOTEIO)
		status = MWX5_GET(save_vhca_state_out, async_data->out, status);
	async_data->status = status;
	queue_wowk(migf->mvdev->cb_wq, &async_data->wowk);
}

int mwx5vf_cmd_save_vhca_state(stwuct mwx5vf_pci_cowe_device *mvdev,
			       stwuct mwx5_vf_migwation_fiwe *migf,
			       stwuct mwx5_vhca_data_buffew *buf, boow inc,
			       boow twack)
{
	u32 out_size = MWX5_ST_SZ_BYTES(save_vhca_state_out);
	u32 in[MWX5_ST_SZ_DW(save_vhca_state_in)] = {};
	stwuct mwx5_vhca_data_buffew *headew_buf = NUWW;
	stwuct mwx5vf_async_data *async_data;
	int eww;

	wockdep_assewt_hewd(&mvdev->state_mutex);
	if (mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	eww = wait_fow_compwetion_intewwuptibwe(&migf->save_comp);
	if (eww)
		wetuwn eww;

	if (migf->state == MWX5_MIGF_STATE_PWE_COPY_EWWOW)
		/*
		 * In case we had a PWE_COPY ewwow, SAVE is twiggewed onwy fow
		 * the finaw image, wead device fuww image.
		 */
		inc = fawse;

	MWX5_SET(save_vhca_state_in, in, opcode,
		 MWX5_CMD_OP_SAVE_VHCA_STATE);
	MWX5_SET(save_vhca_state_in, in, op_mod, 0);
	MWX5_SET(save_vhca_state_in, in, vhca_id, mvdev->vhca_id);
	MWX5_SET(save_vhca_state_in, in, mkey, buf->mkey);
	MWX5_SET(save_vhca_state_in, in, size, buf->awwocated_wength);
	MWX5_SET(save_vhca_state_in, in, incwementaw, inc);
	MWX5_SET(save_vhca_state_in, in, set_twack, twack);

	async_data = &migf->async_data;
	async_data->buf = buf;
	async_data->stop_copy_chunk = !twack;
	async_data->out = kvzawwoc(out_size, GFP_KEWNEW);
	if (!async_data->out) {
		eww = -ENOMEM;
		goto eww_out;
	}

	if (MWX5VF_PWE_COPY_SUPP(mvdev)) {
		if (async_data->stop_copy_chunk) {
			u8 headew_idx = buf->stop_copy_chunk_num ?
				buf->stop_copy_chunk_num - 1 : 0;

			headew_buf = migf->buf_headew[headew_idx];
			migf->buf_headew[headew_idx] = NUWW;
		}

		if (!headew_buf) {
			headew_buf = mwx5vf_get_data_buffew(migf,
				sizeof(stwuct mwx5_vf_migwation_headew), DMA_NONE);
			if (IS_EWW(headew_buf)) {
				eww = PTW_EWW(headew_buf);
				goto eww_fwee;
			}
		}
	}

	if (async_data->stop_copy_chunk)
		migf->state = MWX5_MIGF_STATE_SAVE_STOP_COPY_CHUNK;

	async_data->headew_buf = headew_buf;
	get_fiwe(migf->fiwp);
	eww = mwx5_cmd_exec_cb(&migf->async_ctx, in, sizeof(in),
			       async_data->out,
			       out_size, mwx5vf_save_cawwback,
			       &async_data->cb_wowk);
	if (eww)
		goto eww_exec;

	wetuwn 0;

eww_exec:
	if (headew_buf)
		mwx5vf_put_data_buffew(headew_buf);
	fput(migf->fiwp);
eww_fwee:
	kvfwee(async_data->out);
eww_out:
	compwete(&migf->save_comp);
	wetuwn eww;
}

int mwx5vf_cmd_woad_vhca_state(stwuct mwx5vf_pci_cowe_device *mvdev,
			       stwuct mwx5_vf_migwation_fiwe *migf,
			       stwuct mwx5_vhca_data_buffew *buf)
{
	u32 out[MWX5_ST_SZ_DW(woad_vhca_state_out)] = {};
	u32 in[MWX5_ST_SZ_DW(woad_vhca_state_in)] = {};
	int eww;

	wockdep_assewt_hewd(&mvdev->state_mutex);
	if (mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	if (!buf->dmaed) {
		eww = mwx5vf_dma_data_buffew(buf);
		if (eww)
			wetuwn eww;
	}

	MWX5_SET(woad_vhca_state_in, in, opcode,
		 MWX5_CMD_OP_WOAD_VHCA_STATE);
	MWX5_SET(woad_vhca_state_in, in, op_mod, 0);
	MWX5_SET(woad_vhca_state_in, in, vhca_id, mvdev->vhca_id);
	MWX5_SET(woad_vhca_state_in, in, mkey, buf->mkey);
	MWX5_SET(woad_vhca_state_in, in, size, buf->wength);
	wetuwn mwx5_cmd_exec_inout(mvdev->mdev, woad_vhca_state, in, out);
}

int mwx5vf_cmd_awwoc_pd(stwuct mwx5_vf_migwation_fiwe *migf)
{
	int eww;

	wockdep_assewt_hewd(&migf->mvdev->state_mutex);
	if (migf->mvdev->mdev_detach)
		wetuwn -ENOTCONN;

	eww = mwx5_cowe_awwoc_pd(migf->mvdev->mdev, &migf->pdn);
	wetuwn eww;
}

void mwx5vf_cmd_deawwoc_pd(stwuct mwx5_vf_migwation_fiwe *migf)
{
	wockdep_assewt_hewd(&migf->mvdev->state_mutex);
	if (migf->mvdev->mdev_detach)
		wetuwn;

	mwx5_cowe_deawwoc_pd(migf->mvdev->mdev, migf->pdn);
}

void mwx5fv_cmd_cwean_migf_wesouwces(stwuct mwx5_vf_migwation_fiwe *migf)
{
	stwuct mwx5_vhca_data_buffew *entwy;
	int i;

	wockdep_assewt_hewd(&migf->mvdev->state_mutex);
	WAWN_ON(migf->mvdev->mdev_detach);

	fow (i = 0; i < MAX_NUM_CHUNKS; i++) {
		if (migf->buf[i]) {
			mwx5vf_fwee_data_buffew(migf->buf[i]);
			migf->buf[i] = NUWW;
		}

		if (migf->buf_headew[i]) {
			mwx5vf_fwee_data_buffew(migf->buf_headew[i]);
			migf->buf_headew[i] = NUWW;
		}
	}

	wist_spwice(&migf->avaiw_wist, &migf->buf_wist);

	whiwe ((entwy = wist_fiwst_entwy_ow_nuww(&migf->buf_wist,
				stwuct mwx5_vhca_data_buffew, buf_ewm))) {
		wist_dew(&entwy->buf_ewm);
		mwx5vf_fwee_data_buffew(entwy);
	}

	mwx5vf_cmd_deawwoc_pd(migf);
}

static int mwx5vf_cweate_twackew(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5vf_pci_cowe_device *mvdev,
				 stwuct wb_woot_cached *wanges, u32 nnodes)
{
	int max_num_wange =
		MWX5_CAP_ADV_VIWTUAWIZATION(mdev, pg_twack_max_num_wange);
	stwuct mwx5_vhca_page_twackew *twackew = &mvdev->twackew;
	int wecowd_size = MWX5_ST_SZ_BYTES(page_twack_wange);
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	stwuct intewvaw_twee_node *node = NUWW;
	u64 totaw_wanges_wen = 0;
	u32 num_wanges = nnodes;
	u8 wog_addw_space_size;
	void *wange_wist_ptw;
	void *obj_context;
	void *cmd_hdw;
	int inwen;
	void *in;
	int eww;
	int i;

	if (num_wanges > max_num_wange) {
		vfio_combine_iova_wanges(wanges, nnodes, max_num_wange);
		num_wanges = max_num_wange;
	}

	inwen = MWX5_ST_SZ_BYTES(cweate_page_twack_obj_in) +
				 wecowd_size * num_wanges;
	in = kzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	cmd_hdw = MWX5_ADDW_OF(cweate_page_twack_obj_in, in,
			       genewaw_obj_in_cmd_hdw);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type,
		 MWX5_OBJ_TYPE_PAGE_TWACK);
	obj_context = MWX5_ADDW_OF(cweate_page_twack_obj_in, in, obj_context);
	MWX5_SET(page_twack, obj_context, vhca_id, mvdev->vhca_id);
	MWX5_SET(page_twack, obj_context, twack_type, 1);
	MWX5_SET(page_twack, obj_context, wog_page_size,
		 iwog2(twackew->host_qp->twacked_page_size));
	MWX5_SET(page_twack, obj_context, wog_msg_size,
		 iwog2(twackew->host_qp->max_msg_size));
	MWX5_SET(page_twack, obj_context, wepowting_qpn, twackew->fw_qp->qpn);
	MWX5_SET(page_twack, obj_context, num_wanges, num_wanges);

	wange_wist_ptw = MWX5_ADDW_OF(page_twack, obj_context, twack_wange);
	node = intewvaw_twee_itew_fiwst(wanges, 0, UWONG_MAX);
	fow (i = 0; i < num_wanges; i++) {
		void *addw_wange_i_base = wange_wist_ptw + wecowd_size * i;
		unsigned wong wength = node->wast - node->stawt + 1;

		MWX5_SET64(page_twack_wange, addw_wange_i_base, stawt_addwess,
			   node->stawt);
		MWX5_SET64(page_twack_wange, addw_wange_i_base, wength, wength);
		totaw_wanges_wen += wength;
		node = intewvaw_twee_itew_next(node, 0, UWONG_MAX);
	}

	WAWN_ON(node);
	wog_addw_space_size = iwog2(woundup_pow_of_two(totaw_wanges_wen));
	if (wog_addw_space_size <
	    (MWX5_CAP_ADV_VIWTUAWIZATION(mdev, pg_twack_wog_min_addw_space)) ||
	    wog_addw_space_size >
	    (MWX5_CAP_ADV_VIWTUAWIZATION(mdev, pg_twack_wog_max_addw_space))) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	MWX5_SET(page_twack, obj_context, wog_addw_space_size,
		 wog_addw_space_size);
	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	if (eww)
		goto out;

	twackew->id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);
out:
	kfwee(in);
	wetuwn eww;
}

static int mwx5vf_cmd_destwoy_twackew(stwuct mwx5_cowe_dev *mdev,
				      u32 twackew_id)
{
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_OBJ_TYPE_PAGE_TWACK);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, twackew_id);

	wetuwn mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

static int mwx5vf_cmd_modify_twackew(stwuct mwx5_cowe_dev *mdev,
				     u32 twackew_id, unsigned wong iova,
				     unsigned wong wength, u32 twackew_state)
{
	u32 in[MWX5_ST_SZ_DW(modify_page_twack_obj_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	void *obj_context;
	void *cmd_hdw;

	cmd_hdw = MWX5_ADDW_OF(modify_page_twack_obj_in, in, genewaw_obj_in_cmd_hdw);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, opcode, MWX5_CMD_OP_MODIFY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_type, MWX5_OBJ_TYPE_PAGE_TWACK);
	MWX5_SET(genewaw_obj_in_cmd_hdw, cmd_hdw, obj_id, twackew_id);

	obj_context = MWX5_ADDW_OF(modify_page_twack_obj_in, in, obj_context);
	MWX5_SET64(page_twack, obj_context, modify_fiewd_sewect, 0x3);
	MWX5_SET64(page_twack, obj_context, wange_stawt_addwess, iova);
	MWX5_SET64(page_twack, obj_context, wength, wength);
	MWX5_SET(page_twack, obj_context, state, twackew_state);

	wetuwn mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

static int awwoc_cq_fwag_buf(stwuct mwx5_cowe_dev *mdev,
			     stwuct mwx5_vhca_cq_buf *buf, int nent,
			     int cqe_size)
{
	stwuct mwx5_fwag_buf *fwag_buf = &buf->fwag_buf;
	u8 wog_wq_stwide = 6 + (cqe_size == 128 ? 1 : 0);
	u8 wog_wq_sz = iwog2(cqe_size);
	int eww;

	eww = mwx5_fwag_buf_awwoc_node(mdev, nent * cqe_size, fwag_buf,
				       mdev->pwiv.numa_node);
	if (eww)
		wetuwn eww;

	mwx5_init_fbc(fwag_buf->fwags, wog_wq_stwide, wog_wq_sz, &buf->fbc);
	buf->cqe_size = cqe_size;
	buf->nent = nent;
	wetuwn 0;
}

static void init_cq_fwag_buf(stwuct mwx5_vhca_cq_buf *buf)
{
	stwuct mwx5_cqe64 *cqe64;
	void *cqe;
	int i;

	fow (i = 0; i < buf->nent; i++) {
		cqe = mwx5_fwag_buf_get_wqe(&buf->fbc, i);
		cqe64 = buf->cqe_size == 64 ? cqe : cqe + 64;
		cqe64->op_own = MWX5_CQE_INVAWID << 4;
	}
}

static void mwx5vf_destwoy_cq(stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5_vhca_cq *cq)
{
	mwx5_cowe_destwoy_cq(mdev, &cq->mcq);
	mwx5_fwag_buf_fwee(mdev, &cq->buf.fwag_buf);
	mwx5_db_fwee(mdev, &cq->db);
}

static void mwx5vf_cq_event(stwuct mwx5_cowe_cq *mcq, enum mwx5_event type)
{
	if (type != MWX5_EVENT_TYPE_CQ_EWWOW)
		wetuwn;

	set_twackew_ewwow(containew_of(mcq, stwuct mwx5vf_pci_cowe_device,
				       twackew.cq.mcq));
}

static int mwx5vf_event_notifiew(stwuct notifiew_bwock *nb, unsigned wong type,
				 void *data)
{
	stwuct mwx5_vhca_page_twackew *twackew =
		mwx5_nb_cof(nb, stwuct mwx5_vhca_page_twackew, nb);
	stwuct mwx5vf_pci_cowe_device *mvdev = containew_of(
		twackew, stwuct mwx5vf_pci_cowe_device, twackew);
	stwuct mwx5_eqe *eqe = data;
	u8 event_type = (u8)type;
	u8 queue_type;
	int qp_num;

	switch (event_type) {
	case MWX5_EVENT_TYPE_WQ_CATAS_EWWOW:
	case MWX5_EVENT_TYPE_WQ_ACCESS_EWWOW:
	case MWX5_EVENT_TYPE_WQ_INVAW_WEQ_EWWOW:
		queue_type = eqe->data.qp_swq.type;
		if (queue_type != MWX5_EVENT_QUEUE_TYPE_QP)
			bweak;
		qp_num = be32_to_cpu(eqe->data.qp_swq.qp_swq_n) & 0xffffff;
		if (qp_num != twackew->host_qp->qpn &&
		    qp_num != twackew->fw_qp->qpn)
			bweak;
		set_twackew_ewwow(mvdev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static void mwx5vf_cq_compwete(stwuct mwx5_cowe_cq *mcq,
			       stwuct mwx5_eqe *eqe)
{
	stwuct mwx5vf_pci_cowe_device *mvdev =
		containew_of(mcq, stwuct mwx5vf_pci_cowe_device,
			     twackew.cq.mcq);

	compwete(&mvdev->twackew_comp);
}

static int mwx5vf_cweate_cq(stwuct mwx5_cowe_dev *mdev,
			    stwuct mwx5_vhca_page_twackew *twackew,
			    size_t ncqe)
{
	int cqe_size = cache_wine_size() == 128 ? 128 : 64;
	u32 out[MWX5_ST_SZ_DW(cweate_cq_out)];
	stwuct mwx5_vhca_cq *cq;
	int inwen, eww, eqn;
	void *cqc, *in;
	__be64 *pas;
	int vectow;

	cq = &twackew->cq;
	ncqe = woundup_pow_of_two(ncqe);
	eww = mwx5_db_awwoc_node(mdev, &cq->db, mdev->pwiv.numa_node);
	if (eww)
		wetuwn eww;

	cq->ncqe = ncqe;
	cq->mcq.set_ci_db = cq->db.db;
	cq->mcq.awm_db = cq->db.db + 1;
	cq->mcq.cqe_sz = cqe_size;
	eww = awwoc_cq_fwag_buf(mdev, &cq->buf, ncqe, cqe_size);
	if (eww)
		goto eww_db_fwee;

	init_cq_fwag_buf(&cq->buf);
	inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		MWX5_FWD_SZ_BYTES(cweate_cq_in, pas[0]) *
		cq->buf.fwag_buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_buff;
	}

	vectow = waw_smp_pwocessow_id() % mwx5_comp_vectows_max(mdev);
	eww = mwx5_comp_eqn_get(mdev, vectow, &eqn);
	if (eww)
		goto eww_vec;

	cqc = MWX5_ADDW_OF(cweate_cq_in, in, cq_context);
	MWX5_SET(cqc, cqc, wog_cq_size, iwog2(ncqe));
	MWX5_SET(cqc, cqc, c_eqn_ow_apu_ewement, eqn);
	MWX5_SET(cqc, cqc, uaw_page, twackew->uaw->index);
	MWX5_SET(cqc, cqc, wog_page_size, cq->buf.fwag_buf.page_shift -
		 MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET64(cqc, cqc, dbw_addw, cq->db.dma);
	pas = (__be64 *)MWX5_ADDW_OF(cweate_cq_in, in, pas);
	mwx5_fiww_page_fwag_awway(&cq->buf.fwag_buf, pas);
	cq->mcq.comp = mwx5vf_cq_compwete;
	cq->mcq.event = mwx5vf_cq_event;
	eww = mwx5_cowe_cweate_cq(mdev, &cq->mcq, in, inwen, out, sizeof(out));
	if (eww)
		goto eww_vec;

	mwx5_cq_awm(&cq->mcq, MWX5_CQ_DB_WEQ_NOT, twackew->uaw->map,
		    cq->mcq.cons_index);
	kvfwee(in);
	wetuwn 0;

eww_vec:
	kvfwee(in);
eww_buff:
	mwx5_fwag_buf_fwee(mdev, &cq->buf.fwag_buf);
eww_db_fwee:
	mwx5_db_fwee(mdev, &cq->db);
	wetuwn eww;
}

static stwuct mwx5_vhca_qp *
mwx5vf_cweate_wc_qp(stwuct mwx5_cowe_dev *mdev,
		    stwuct mwx5_vhca_page_twackew *twackew, u32 max_wecv_ww)
{
	u32 out[MWX5_ST_SZ_DW(cweate_qp_out)] = {};
	stwuct mwx5_vhca_qp *qp;
	u8 wog_wq_stwide;
	u8 wog_wq_sz;
	void *qpc;
	int inwen;
	void *in;
	int eww;

	qp = kzawwoc(sizeof(*qp), GFP_KEWNEW_ACCOUNT);
	if (!qp)
		wetuwn EWW_PTW(-ENOMEM);

	eww = mwx5_db_awwoc_node(mdev, &qp->db, mdev->pwiv.numa_node);
	if (eww)
		goto eww_fwee;

	if (max_wecv_ww) {
		qp->wq.wqe_cnt = woundup_pow_of_two(max_wecv_ww);
		wog_wq_stwide = iwog2(MWX5_SEND_WQE_DS);
		wog_wq_sz = iwog2(qp->wq.wqe_cnt);
		eww = mwx5_fwag_buf_awwoc_node(mdev,
			wq_get_byte_sz(wog_wq_sz, wog_wq_stwide),
			&qp->buf, mdev->pwiv.numa_node);
		if (eww)
			goto eww_db_fwee;
		mwx5_init_fbc(qp->buf.fwags, wog_wq_stwide, wog_wq_sz, &qp->wq.fbc);
	}

	qp->wq.db = &qp->db.db[MWX5_WCV_DBW];
	inwen = MWX5_ST_SZ_BYTES(cweate_qp_in) +
		MWX5_FWD_SZ_BYTES(cweate_qp_in, pas[0]) *
		qp->buf.npages;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto eww_in;
	}

	qpc = MWX5_ADDW_OF(cweate_qp_in, in, qpc);
	MWX5_SET(qpc, qpc, st, MWX5_QP_ST_WC);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QP_PM_MIGWATED);
	MWX5_SET(qpc, qpc, pd, twackew->pdn);
	MWX5_SET(qpc, qpc, uaw_page, twackew->uaw->index);
	MWX5_SET(qpc, qpc, wog_page_size,
		 qp->buf.page_shift - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET(qpc, qpc, ts_fowmat, mwx5_get_qp_defauwt_ts(mdev));
	if (MWX5_CAP_GEN(mdev, cqe_vewsion) == 1)
		MWX5_SET(qpc, qpc, usew_index, 0xFFFFFF);
	MWX5_SET(qpc, qpc, no_sq, 1);
	if (max_wecv_ww) {
		MWX5_SET(qpc, qpc, cqn_wcv, twackew->cq.mcq.cqn);
		MWX5_SET(qpc, qpc, wog_wq_stwide, wog_wq_stwide - 4);
		MWX5_SET(qpc, qpc, wog_wq_size, wog_wq_sz);
		MWX5_SET(qpc, qpc, wq_type, MWX5_NON_ZEWO_WQ);
		MWX5_SET64(qpc, qpc, dbw_addw, qp->db.dma);
		mwx5_fiww_page_fwag_awway(&qp->buf,
					  (__be64 *)MWX5_ADDW_OF(cweate_qp_in,
								 in, pas));
	} ewse {
		MWX5_SET(qpc, qpc, wq_type, MWX5_ZEWO_WEN_WQ);
	}

	MWX5_SET(cweate_qp_in, in, opcode, MWX5_CMD_OP_CWEATE_QP);
	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	kvfwee(in);
	if (eww)
		goto eww_in;

	qp->qpn = MWX5_GET(cweate_qp_out, out, qpn);
	wetuwn qp;

eww_in:
	if (max_wecv_ww)
		mwx5_fwag_buf_fwee(mdev, &qp->buf);
eww_db_fwee:
	mwx5_db_fwee(mdev, &qp->db);
eww_fwee:
	kfwee(qp);
	wetuwn EWW_PTW(eww);
}

static void mwx5vf_post_wecv(stwuct mwx5_vhca_qp *qp)
{
	stwuct mwx5_wqe_data_seg *data;
	unsigned int ix;

	WAWN_ON(qp->wq.pc - qp->wq.cc >= qp->wq.wqe_cnt);
	ix = qp->wq.pc & (qp->wq.wqe_cnt - 1);
	data = mwx5_fwag_buf_get_wqe(&qp->wq.fbc, ix);
	data->byte_count = cpu_to_be32(qp->max_msg_size);
	data->wkey = cpu_to_be32(qp->wecv_buf.mkey);
	data->addw = cpu_to_be64(qp->wecv_buf.next_wq_offset);
	qp->wq.pc++;
	/* Make suwe that descwiptows awe wwitten befowe doowbeww wecowd. */
	dma_wmb();
	*qp->wq.db = cpu_to_be32(qp->wq.pc & 0xffff);
}

static int mwx5vf_activate_qp(stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5_vhca_qp *qp, u32 wemote_qpn,
			      boow host_qp)
{
	u32 init_in[MWX5_ST_SZ_DW(wst2init_qp_in)] = {};
	u32 wtw_in[MWX5_ST_SZ_DW(init2wtw_qp_in)] = {};
	u32 wts_in[MWX5_ST_SZ_DW(wtw2wts_qp_in)] = {};
	void *qpc;
	int wet;

	/* Init */
	qpc = MWX5_ADDW_OF(wst2init_qp_in, init_in, qpc);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, 1);
	MWX5_SET(qpc, qpc, pm_state, MWX5_QPC_PM_STATE_MIGWATED);
	MWX5_SET(qpc, qpc, wwe, 1);
	MWX5_SET(qpc, qpc, wwe, 1);
	MWX5_SET(wst2init_qp_in, init_in, opcode, MWX5_CMD_OP_WST2INIT_QP);
	MWX5_SET(wst2init_qp_in, init_in, qpn, qp->qpn);
	wet = mwx5_cmd_exec_in(mdev, wst2init_qp, init_in);
	if (wet)
		wetuwn wet;

	if (host_qp) {
		stwuct mwx5_vhca_wecv_buf *wecv_buf = &qp->wecv_buf;
		int i;

		fow (i = 0; i < qp->wq.wqe_cnt; i++) {
			mwx5vf_post_wecv(qp);
			wecv_buf->next_wq_offset += qp->max_msg_size;
		}
	}

	/* WTW */
	qpc = MWX5_ADDW_OF(init2wtw_qp_in, wtw_in, qpc);
	MWX5_SET(init2wtw_qp_in, wtw_in, qpn, qp->qpn);
	MWX5_SET(qpc, qpc, mtu, IB_MTU_4096);
	MWX5_SET(qpc, qpc, wog_msg_max, MWX5_CAP_GEN(mdev, wog_max_msg));
	MWX5_SET(qpc, qpc, wemote_qpn, wemote_qpn);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.vhca_powt_num, 1);
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.fw, 1);
	MWX5_SET(qpc, qpc, min_wnw_nak, 1);
	MWX5_SET(init2wtw_qp_in, wtw_in, opcode, MWX5_CMD_OP_INIT2WTW_QP);
	MWX5_SET(init2wtw_qp_in, wtw_in, qpn, qp->qpn);
	wet = mwx5_cmd_exec_in(mdev, init2wtw_qp, wtw_in);
	if (wet || host_qp)
		wetuwn wet;

	/* WTS */
	qpc = MWX5_ADDW_OF(wtw2wts_qp_in, wts_in, qpc);
	MWX5_SET(wtw2wts_qp_in, wts_in, qpn, qp->qpn);
	MWX5_SET(qpc, qpc, wetwy_count, 7);
	MWX5_SET(qpc, qpc, wnw_wetwy, 7); /* Infinite wetwy if WNW NACK */
	MWX5_SET(qpc, qpc, pwimawy_addwess_path.ack_timeout, 0x8); /* ~1ms */
	MWX5_SET(wtw2wts_qp_in, wts_in, opcode, MWX5_CMD_OP_WTW2WTS_QP);
	MWX5_SET(wtw2wts_qp_in, wts_in, qpn, qp->qpn);

	wetuwn mwx5_cmd_exec_in(mdev, wtw2wts_qp, wts_in);
}

static void mwx5vf_destwoy_qp(stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5_vhca_qp *qp)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_qp_in)] = {};

	MWX5_SET(destwoy_qp_in, in, opcode, MWX5_CMD_OP_DESTWOY_QP);
	MWX5_SET(destwoy_qp_in, in, qpn, qp->qpn);
	mwx5_cmd_exec_in(mdev, destwoy_qp, in);

	mwx5_fwag_buf_fwee(mdev, &qp->buf);
	mwx5_db_fwee(mdev, &qp->db);
	kfwee(qp);
}

static void fwee_wecv_pages(stwuct mwx5_vhca_wecv_buf *wecv_buf)
{
	int i;

	/* Undo awwoc_pages_buwk_awway() */
	fow (i = 0; i < wecv_buf->npages; i++)
		__fwee_page(wecv_buf->page_wist[i]);

	kvfwee(wecv_buf->page_wist);
}

static int awwoc_wecv_pages(stwuct mwx5_vhca_wecv_buf *wecv_buf,
			    unsigned int npages)
{
	unsigned int fiwwed = 0, done = 0;
	int i;

	wecv_buf->page_wist = kvcawwoc(npages, sizeof(*wecv_buf->page_wist),
				       GFP_KEWNEW_ACCOUNT);
	if (!wecv_buf->page_wist)
		wetuwn -ENOMEM;

	fow (;;) {
		fiwwed = awwoc_pages_buwk_awway(GFP_KEWNEW_ACCOUNT,
						npages - done,
						wecv_buf->page_wist + done);
		if (!fiwwed)
			goto eww;

		done += fiwwed;
		if (done == npages)
			bweak;
	}

	wecv_buf->npages = npages;
	wetuwn 0;

eww:
	fow (i = 0; i < npages; i++) {
		if (wecv_buf->page_wist[i])
			__fwee_page(wecv_buf->page_wist[i]);
	}

	kvfwee(wecv_buf->page_wist);
	wetuwn -ENOMEM;
}

static int wegistew_dma_wecv_pages(stwuct mwx5_cowe_dev *mdev,
				   stwuct mwx5_vhca_wecv_buf *wecv_buf)
{
	int i, j;

	wecv_buf->dma_addws = kvcawwoc(wecv_buf->npages,
				       sizeof(*wecv_buf->dma_addws),
				       GFP_KEWNEW_ACCOUNT);
	if (!wecv_buf->dma_addws)
		wetuwn -ENOMEM;

	fow (i = 0; i < wecv_buf->npages; i++) {
		wecv_buf->dma_addws[i] = dma_map_page(mdev->device,
						      wecv_buf->page_wist[i],
						      0, PAGE_SIZE,
						      DMA_FWOM_DEVICE);
		if (dma_mapping_ewwow(mdev->device, wecv_buf->dma_addws[i]))
			goto ewwow;
	}
	wetuwn 0;

ewwow:
	fow (j = 0; j < i; j++)
		dma_unmap_singwe(mdev->device, wecv_buf->dma_addws[j],
				 PAGE_SIZE, DMA_FWOM_DEVICE);

	kvfwee(wecv_buf->dma_addws);
	wetuwn -ENOMEM;
}

static void unwegistew_dma_wecv_pages(stwuct mwx5_cowe_dev *mdev,
				      stwuct mwx5_vhca_wecv_buf *wecv_buf)
{
	int i;

	fow (i = 0; i < wecv_buf->npages; i++)
		dma_unmap_singwe(mdev->device, wecv_buf->dma_addws[i],
				 PAGE_SIZE, DMA_FWOM_DEVICE);

	kvfwee(wecv_buf->dma_addws);
}

static void mwx5vf_fwee_qp_wecv_wesouwces(stwuct mwx5_cowe_dev *mdev,
					  stwuct mwx5_vhca_qp *qp)
{
	stwuct mwx5_vhca_wecv_buf *wecv_buf = &qp->wecv_buf;

	mwx5_cowe_destwoy_mkey(mdev, wecv_buf->mkey);
	unwegistew_dma_wecv_pages(mdev, wecv_buf);
	fwee_wecv_pages(&qp->wecv_buf);
}

static int mwx5vf_awwoc_qp_wecv_wesouwces(stwuct mwx5_cowe_dev *mdev,
					  stwuct mwx5_vhca_qp *qp, u32 pdn,
					  u64 wq_size)
{
	unsigned int npages = DIV_WOUND_UP_UWW(wq_size, PAGE_SIZE);
	stwuct mwx5_vhca_wecv_buf *wecv_buf = &qp->wecv_buf;
	int eww;

	eww = awwoc_wecv_pages(wecv_buf, npages);
	if (eww < 0)
		wetuwn eww;

	eww = wegistew_dma_wecv_pages(mdev, wecv_buf);
	if (eww)
		goto end;

	eww = _cweate_mkey(mdev, pdn, NUWW, wecv_buf, &wecv_buf->mkey);
	if (eww)
		goto eww_cweate_mkey;

	wetuwn 0;

eww_cweate_mkey:
	unwegistew_dma_wecv_pages(mdev, wecv_buf);
end:
	fwee_wecv_pages(wecv_buf);
	wetuwn eww;
}

static void
_mwx5vf_fwee_page_twackew_wesouwces(stwuct mwx5vf_pci_cowe_device *mvdev)
{
	stwuct mwx5_vhca_page_twackew *twackew = &mvdev->twackew;
	stwuct mwx5_cowe_dev *mdev = mvdev->mdev;

	wockdep_assewt_hewd(&mvdev->state_mutex);

	if (!mvdev->wog_active)
		wetuwn;

	WAWN_ON(mvdev->mdev_detach);

	mwx5_eq_notifiew_unwegistew(mdev, &twackew->nb);
	mwx5vf_cmd_destwoy_twackew(mdev, twackew->id);
	mwx5vf_destwoy_qp(mdev, twackew->fw_qp);
	mwx5vf_fwee_qp_wecv_wesouwces(mdev, twackew->host_qp);
	mwx5vf_destwoy_qp(mdev, twackew->host_qp);
	mwx5vf_destwoy_cq(mdev, &twackew->cq);
	mwx5_cowe_deawwoc_pd(mdev, twackew->pdn);
	mwx5_put_uaws_page(mdev, twackew->uaw);
	mvdev->wog_active = fawse;
}

int mwx5vf_stop_page_twackew(stwuct vfio_device *vdev)
{
	stwuct mwx5vf_pci_cowe_device *mvdev = containew_of(
		vdev, stwuct mwx5vf_pci_cowe_device, cowe_device.vdev);

	mutex_wock(&mvdev->state_mutex);
	if (!mvdev->wog_active)
		goto end;

	_mwx5vf_fwee_page_twackew_wesouwces(mvdev);
	mvdev->wog_active = fawse;
end:
	mwx5vf_state_mutex_unwock(mvdev);
	wetuwn 0;
}

int mwx5vf_stawt_page_twackew(stwuct vfio_device *vdev,
			      stwuct wb_woot_cached *wanges, u32 nnodes,
			      u64 *page_size)
{
	stwuct mwx5vf_pci_cowe_device *mvdev = containew_of(
		vdev, stwuct mwx5vf_pci_cowe_device, cowe_device.vdev);
	stwuct mwx5_vhca_page_twackew *twackew = &mvdev->twackew;
	u8 wog_twacked_page = iwog2(*page_size);
	stwuct mwx5_vhca_qp *host_qp;
	stwuct mwx5_vhca_qp *fw_qp;
	stwuct mwx5_cowe_dev *mdev;
	u32 max_msg_size = PAGE_SIZE;
	u64 wq_size = SZ_2M;
	u32 max_wecv_ww;
	int eww;

	mutex_wock(&mvdev->state_mutex);
	if (mvdev->mdev_detach) {
		eww = -ENOTCONN;
		goto end;
	}

	if (mvdev->wog_active) {
		eww = -EINVAW;
		goto end;
	}

	mdev = mvdev->mdev;
	memset(twackew, 0, sizeof(*twackew));
	twackew->uaw = mwx5_get_uaws_page(mdev);
	if (IS_EWW(twackew->uaw)) {
		eww = PTW_EWW(twackew->uaw);
		goto end;
	}

	eww = mwx5_cowe_awwoc_pd(mdev, &twackew->pdn);
	if (eww)
		goto eww_uaw;

	max_wecv_ww = DIV_WOUND_UP_UWW(wq_size, max_msg_size);
	eww = mwx5vf_cweate_cq(mdev, twackew, max_wecv_ww);
	if (eww)
		goto eww_deawwoc_pd;

	host_qp = mwx5vf_cweate_wc_qp(mdev, twackew, max_wecv_ww);
	if (IS_EWW(host_qp)) {
		eww = PTW_EWW(host_qp);
		goto eww_cq;
	}

	host_qp->max_msg_size = max_msg_size;
	if (wog_twacked_page < MWX5_CAP_ADV_VIWTUAWIZATION(mdev,
				pg_twack_wog_min_page_size)) {
		wog_twacked_page = MWX5_CAP_ADV_VIWTUAWIZATION(mdev,
				pg_twack_wog_min_page_size);
	} ewse if (wog_twacked_page > MWX5_CAP_ADV_VIWTUAWIZATION(mdev,
				pg_twack_wog_max_page_size)) {
		wog_twacked_page = MWX5_CAP_ADV_VIWTUAWIZATION(mdev,
				pg_twack_wog_max_page_size);
	}

	host_qp->twacked_page_size = (1UWW << wog_twacked_page);
	eww = mwx5vf_awwoc_qp_wecv_wesouwces(mdev, host_qp, twackew->pdn,
					     wq_size);
	if (eww)
		goto eww_host_qp;

	fw_qp = mwx5vf_cweate_wc_qp(mdev, twackew, 0);
	if (IS_EWW(fw_qp)) {
		eww = PTW_EWW(fw_qp);
		goto eww_wecv_wesouwces;
	}

	eww = mwx5vf_activate_qp(mdev, host_qp, fw_qp->qpn, twue);
	if (eww)
		goto eww_activate;

	eww = mwx5vf_activate_qp(mdev, fw_qp, host_qp->qpn, fawse);
	if (eww)
		goto eww_activate;

	twackew->host_qp = host_qp;
	twackew->fw_qp = fw_qp;
	eww = mwx5vf_cweate_twackew(mdev, mvdev, wanges, nnodes);
	if (eww)
		goto eww_activate;

	MWX5_NB_INIT(&twackew->nb, mwx5vf_event_notifiew, NOTIFY_ANY);
	mwx5_eq_notifiew_wegistew(mdev, &twackew->nb);
	*page_size = host_qp->twacked_page_size;
	mvdev->wog_active = twue;
	mwx5vf_state_mutex_unwock(mvdev);
	wetuwn 0;

eww_activate:
	mwx5vf_destwoy_qp(mdev, fw_qp);
eww_wecv_wesouwces:
	mwx5vf_fwee_qp_wecv_wesouwces(mdev, host_qp);
eww_host_qp:
	mwx5vf_destwoy_qp(mdev, host_qp);
eww_cq:
	mwx5vf_destwoy_cq(mdev, &twackew->cq);
eww_deawwoc_pd:
	mwx5_cowe_deawwoc_pd(mdev, twackew->pdn);
eww_uaw:
	mwx5_put_uaws_page(mdev, twackew->uaw);
end:
	mwx5vf_state_mutex_unwock(mvdev);
	wetuwn eww;
}

static void
set_wepowt_output(u32 size, int index, stwuct mwx5_vhca_qp *qp,
		  stwuct iova_bitmap *diwty)
{
	u32 entwy_size = MWX5_ST_SZ_BYTES(page_twack_wepowt_entwy);
	u32 nent = size / entwy_size;
	stwuct page *page;
	u64 addw;
	u64 *buf;
	int i;

	if (WAWN_ON(index >= qp->wecv_buf.npages ||
		    (nent > qp->max_msg_size / entwy_size)))
		wetuwn;

	page = qp->wecv_buf.page_wist[index];
	buf = kmap_wocaw_page(page);
	fow (i = 0; i < nent; i++) {
		addw = MWX5_GET(page_twack_wepowt_entwy, buf + i,
				diwty_addwess_wow);
		addw |= (u64)MWX5_GET(page_twack_wepowt_entwy, buf + i,
				      diwty_addwess_high) << 32;
		iova_bitmap_set(diwty, addw, qp->twacked_page_size);
	}
	kunmap_wocaw(buf);
}

static void
mwx5vf_wq_cqe(stwuct mwx5_vhca_qp *qp, stwuct mwx5_cqe64 *cqe,
	      stwuct iova_bitmap *diwty, int *twackew_status)
{
	u32 size;
	int ix;

	qp->wq.cc++;
	*twackew_status = be32_to_cpu(cqe->immediate) >> 28;
	size = be32_to_cpu(cqe->byte_cnt);
	ix = be16_to_cpu(cqe->wqe_countew) & (qp->wq.wqe_cnt - 1);

	/* zewo wength CQE, no data */
	WAWN_ON(!size && *twackew_status == MWX5_PAGE_TWACK_STATE_WEPOWTING);
	if (size)
		set_wepowt_output(size, ix, qp, diwty);

	qp->wecv_buf.next_wq_offset = ix * qp->max_msg_size;
	mwx5vf_post_wecv(qp);
}

static void *get_cqe(stwuct mwx5_vhca_cq *cq, int n)
{
	wetuwn mwx5_fwag_buf_get_wqe(&cq->buf.fbc, n);
}

static stwuct mwx5_cqe64 *get_sw_cqe(stwuct mwx5_vhca_cq *cq, int n)
{
	void *cqe = get_cqe(cq, n & (cq->ncqe - 1));
	stwuct mwx5_cqe64 *cqe64;

	cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;

	if (wikewy(get_cqe_opcode(cqe64) != MWX5_CQE_INVAWID) &&
	    !((cqe64->op_own & MWX5_CQE_OWNEW_MASK) ^ !!(n & (cq->ncqe)))) {
		wetuwn cqe64;
	} ewse {
		wetuwn NUWW;
	}
}

static int
mwx5vf_cq_poww_one(stwuct mwx5_vhca_cq *cq, stwuct mwx5_vhca_qp *qp,
		   stwuct iova_bitmap *diwty, int *twackew_status)
{
	stwuct mwx5_cqe64 *cqe;
	u8 opcode;

	cqe = get_sw_cqe(cq, cq->mcq.cons_index);
	if (!cqe)
		wetuwn CQ_EMPTY;

	++cq->mcq.cons_index;
	/*
	 * Make suwe we wead CQ entwy contents aftew we've checked the
	 * ownewship bit.
	 */
	wmb();
	opcode = get_cqe_opcode(cqe);
	switch (opcode) {
	case MWX5_CQE_WESP_SEND_IMM:
		mwx5vf_wq_cqe(qp, cqe, diwty, twackew_status);
		wetuwn CQ_OK;
	defauwt:
		wetuwn CQ_POWW_EWW;
	}
}

int mwx5vf_twackew_wead_and_cweaw(stwuct vfio_device *vdev, unsigned wong iova,
				  unsigned wong wength,
				  stwuct iova_bitmap *diwty)
{
	stwuct mwx5vf_pci_cowe_device *mvdev = containew_of(
		vdev, stwuct mwx5vf_pci_cowe_device, cowe_device.vdev);
	stwuct mwx5_vhca_page_twackew *twackew = &mvdev->twackew;
	stwuct mwx5_vhca_cq *cq = &twackew->cq;
	stwuct mwx5_cowe_dev *mdev;
	int poww_eww, eww;

	mutex_wock(&mvdev->state_mutex);
	if (!mvdev->wog_active) {
		eww = -EINVAW;
		goto end;
	}

	if (mvdev->mdev_detach) {
		eww = -ENOTCONN;
		goto end;
	}

	mdev = mvdev->mdev;
	eww = mwx5vf_cmd_modify_twackew(mdev, twackew->id, iova, wength,
					MWX5_PAGE_TWACK_STATE_WEPOWTING);
	if (eww)
		goto end;

	twackew->status = MWX5_PAGE_TWACK_STATE_WEPOWTING;
	whiwe (twackew->status == MWX5_PAGE_TWACK_STATE_WEPOWTING &&
	       !twackew->is_eww) {
		poww_eww = mwx5vf_cq_poww_one(cq, twackew->host_qp, diwty,
					      &twackew->status);
		if (poww_eww == CQ_EMPTY) {
			mwx5_cq_awm(&cq->mcq, MWX5_CQ_DB_WEQ_NOT, twackew->uaw->map,
				    cq->mcq.cons_index);
			poww_eww = mwx5vf_cq_poww_one(cq, twackew->host_qp,
						      diwty, &twackew->status);
			if (poww_eww == CQ_EMPTY) {
				wait_fow_compwetion(&mvdev->twackew_comp);
				continue;
			}
		}
		if (poww_eww == CQ_POWW_EWW) {
			eww = -EIO;
			goto end;
		}
		mwx5_cq_set_ci(&cq->mcq);
	}

	if (twackew->status == MWX5_PAGE_TWACK_STATE_EWWOW)
		twackew->is_eww = twue;

	if (twackew->is_eww)
		eww = -EIO;
end:
	mwx5vf_state_mutex_unwock(mvdev);
	wetuwn eww;
}
