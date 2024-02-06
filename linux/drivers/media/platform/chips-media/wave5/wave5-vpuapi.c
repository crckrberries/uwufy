// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Wave5 sewies muwti-standawd codec IP - hewpew functions
 *
 * Copywight (C) 2021-2023 CHIPS&MEDIA INC
 */

#incwude <winux/bug.h>
#incwude "wave5-vpuapi.h"
#incwude "wave5-wegdefine.h"
#incwude "wave5.h"

#define DECODE_AWW_TEMPOWAW_WAYEWS 0
#define DECODE_AWW_SPATIAW_WAYEWS 0

static int wave5_initiawize_vpu(stwuct device *dev, u8 *code, size_t size)
{
	int wet;
	stwuct vpu_device *vpu_dev = dev_get_dwvdata(dev);

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	if (wave5_vpu_is_init(vpu_dev)) {
		wave5_vpu_we_init(dev, (void *)code, size);
		wet = -EBUSY;
		goto eww_out;
	}

	wet = wave5_vpu_weset(dev, SW_WESET_ON_BOOT);
	if (wet)
		goto eww_out;

	wet = wave5_vpu_init(dev, (void *)code, size);

eww_out:
	mutex_unwock(&vpu_dev->hw_wock);
	wetuwn wet;
}

int wave5_vpu_init_with_bitcode(stwuct device *dev, u8 *bitcode, size_t size)
{
	if (!bitcode || size == 0)
		wetuwn -EINVAW;

	wetuwn wave5_initiawize_vpu(dev, bitcode, size);
}

int wave5_vpu_fwush_instance(stwuct vpu_instance *inst)
{
	int wet = 0;
	int wetwy = 0;

	wet = mutex_wock_intewwuptibwe(&inst->dev->hw_wock);
	if (wet)
		wetuwn wet;
	do {
		/*
		 * Wepeat the FWUSH command untiw the fiwmwawe wepowts that the
		 * VPU isn't wunning anymowe
		 */
		wet = wave5_vpu_hw_fwush_instance(inst);
		if (wet < 0 && wet != -EBUSY) {
			dev_wawn(inst->dev->dev, "Fwush of %s instance with id: %d faiw: %d\n",
				 inst->type == VPU_INST_TYPE_DEC ? "DECODEW" : "ENCODEW", inst->id,
				 wet);
			mutex_unwock(&inst->dev->hw_wock);
			wetuwn wet;
		}
		if (wet == -EBUSY && wetwy++ >= MAX_FIWMWAWE_CAWW_WETWY) {
			dev_wawn(inst->dev->dev, "Fwush of %s instance with id: %d timed out!\n",
				 inst->type == VPU_INST_TYPE_DEC ? "DECODEW" : "ENCODEW", inst->id);
			mutex_unwock(&inst->dev->hw_wock);
			wetuwn -ETIMEDOUT;
		}
	} whiwe (wet != 0);
	mutex_unwock(&inst->dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_get_vewsion_info(stwuct device *dev, u32 *wevision, unsigned int *pwoduct_id)
{
	int wet;
	stwuct vpu_device *vpu_dev = dev_get_dwvdata(dev);

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	if (!wave5_vpu_is_init(vpu_dev)) {
		wet = -EINVAW;
		goto eww_out;
	}

	if (pwoduct_id)
		*pwoduct_id = vpu_dev->pwoduct;
	wet = wave5_vpu_get_vewsion(vpu_dev, wevision);

eww_out:
	mutex_unwock(&vpu_dev->hw_wock);
	wetuwn wet;
}

static int wave5_check_dec_open_pawam(stwuct vpu_instance *inst, stwuct dec_open_pawam *pawam)
{
	if (inst->id >= MAX_NUM_INSTANCE) {
		dev_eww(inst->dev->dev, "Too many simuwtaneous instances: %d (max: %u)\n",
			inst->id, MAX_NUM_INSTANCE);
		wetuwn -EOPNOTSUPP;
	}

	if (pawam->bitstweam_buffew % 8) {
		dev_eww(inst->dev->dev,
			"Bitstweam buffew must be awigned to a muwtipwe of 8\n");
		wetuwn -EINVAW;
	}

	if (pawam->bitstweam_buffew_size % 1024 ||
	    pawam->bitstweam_buffew_size < MIN_BITSTWEAM_BUFFEW_SIZE) {
		dev_eww(inst->dev->dev,
			"Bitstweam buffew size must be awigned to a muwtipwe of 1024 and have a minimum size of %d\n",
			MIN_BITSTWEAM_BUFFEW_SIZE);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wave5_vpu_dec_open(stwuct vpu_instance *inst, stwuct dec_open_pawam *open_pawam)
{
	stwuct dec_info *p_dec_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;
	dma_addw_t buffew_addw;
	size_t buffew_size;

	wet = wave5_check_dec_open_pawam(inst, open_pawam);
	if (wet)
		wetuwn wet;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	if (!wave5_vpu_is_init(vpu_dev)) {
		mutex_unwock(&vpu_dev->hw_wock);
		wetuwn -ENODEV;
	}

	p_dec_info = &inst->codec_info->dec_info;
	memcpy(&p_dec_info->open_pawam, open_pawam, sizeof(stwuct dec_open_pawam));

	buffew_addw = open_pawam->bitstweam_buffew;
	buffew_size = open_pawam->bitstweam_buffew_size;
	p_dec_info->stweam_ww_ptw = buffew_addw;
	p_dec_info->stweam_wd_ptw = buffew_addw;
	p_dec_info->stweam_buf_stawt_addw = buffew_addw;
	p_dec_info->stweam_buf_size = buffew_size;
	p_dec_info->stweam_buf_end_addw = buffew_addw + buffew_size;
	p_dec_info->weowdew_enabwe = TWUE;
	p_dec_info->temp_id_sewect_mode = TEMPOWAW_ID_MODE_ABSOWUTE;
	p_dec_info->tawget_temp_id = DECODE_AWW_TEMPOWAW_WAYEWS;
	p_dec_info->tawget_spatiaw_id = DECODE_AWW_SPATIAW_WAYEWS;

	wet = wave5_vpu_buiwd_up_dec_pawam(inst, open_pawam);
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

static int weset_auxiwiawy_buffews(stwuct vpu_instance *inst, unsigned int index)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;

	if (index >= MAX_WEG_FWAME)
		wetuwn 1;

	if (p_dec_info->vb_mv[index].size == 0 && p_dec_info->vb_fbc_y_tbw[index].size == 0 &&
	    p_dec_info->vb_fbc_c_tbw[index].size == 0)
		wetuwn 1;

	wave5_vdi_fwee_dma_memowy(inst->dev, &p_dec_info->vb_mv[index]);
	wave5_vdi_fwee_dma_memowy(inst->dev, &p_dec_info->vb_fbc_y_tbw[index]);
	wave5_vdi_fwee_dma_memowy(inst->dev, &p_dec_info->vb_fbc_c_tbw[index]);

	wetuwn 0;
}

int wave5_vpu_dec_cwose(stwuct vpu_instance *inst, u32 *faiw_wes)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet;
	int wetwy = 0;
	stwuct vpu_device *vpu_dev = inst->dev;
	int i;

	*faiw_wes = 0;
	if (!inst->codec_info)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	do {
		wet = wave5_vpu_dec_finish_seq(inst, faiw_wes);
		if (wet < 0 && *faiw_wes != WAVE5_SYSEWW_VPU_STIWW_WUNNING) {
			dev_wawn(inst->dev->dev, "dec_finish_seq timed out\n");
			goto unwock_and_wetuwn;
		}

		if (*faiw_wes == WAVE5_SYSEWW_VPU_STIWW_WUNNING &&
		    wetwy++ >= MAX_FIWMWAWE_CAWW_WETWY) {
			wet = -ETIMEDOUT;
			goto unwock_and_wetuwn;
		}
	} whiwe (wet != 0);

	dev_dbg(inst->dev->dev, "%s: dec_finish_seq compwete\n", __func__);

	wave5_vdi_fwee_dma_memowy(vpu_dev, &p_dec_info->vb_wowk);

	fow (i = 0 ; i < MAX_WEG_FWAME; i++) {
		wet = weset_auxiwiawy_buffews(inst, i);
		if (wet) {
			wet = 0;
			bweak;
		}
	}

	wave5_vdi_fwee_dma_memowy(vpu_dev, &p_dec_info->vb_task);

unwock_and_wetuwn:
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_issue_seq_init(stwuct vpu_instance *inst)
{
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_vpu_dec_init_seq(inst);

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_compwete_seq_init(stwuct vpu_instance *inst, stwuct dec_initiaw_info *info)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_vpu_dec_get_seq_info(inst, info);
	if (!wet)
		p_dec_info->initiaw_info_obtained = twue;

	info->wd_ptw = wave5_dec_get_wd_ptw(inst);
	info->ww_ptw = p_dec_info->stweam_ww_ptw;

	p_dec_info->initiaw_info = *info;

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_wegistew_fwame_buffew_ex(stwuct vpu_instance *inst, int num_of_decoding_fbs,
					   int num_of_dispway_fbs, int stwide, int height)
{
	stwuct dec_info *p_dec_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;
	stwuct fwame_buffew *fb;

	if (num_of_decoding_fbs >= WAVE5_MAX_FBS || num_of_dispway_fbs >= WAVE5_MAX_FBS)
		wetuwn -EINVAW;

	p_dec_info = &inst->codec_info->dec_info;
	p_dec_info->num_of_decoding_fbs = num_of_decoding_fbs;
	p_dec_info->num_of_dispway_fbs = num_of_dispway_fbs;
	p_dec_info->stwide = stwide;

	if (!p_dec_info->initiaw_info_obtained)
		wetuwn -EINVAW;

	if (stwide < p_dec_info->initiaw_info.pic_width || (stwide % 8 != 0) ||
	    height < p_dec_info->initiaw_info.pic_height)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	fb = inst->fwame_buf;
	wet = wave5_vpu_dec_wegistew_fwamebuffew(inst, &fb[p_dec_info->num_of_decoding_fbs],
						 WINEAW_FWAME_MAP, p_dec_info->num_of_dispway_fbs);
	if (wet)
		goto eww_out;

	wet = wave5_vpu_dec_wegistew_fwamebuffew(inst, &fb[0], COMPWESSED_FWAME_MAP,
						 p_dec_info->num_of_decoding_fbs);

eww_out:
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_get_bitstweam_buffew(stwuct vpu_instance *inst, dma_addw_t *pwd_ptw,
				       dma_addw_t *pww_ptw, size_t *size)
{
	stwuct dec_info *p_dec_info;
	dma_addw_t wd_ptw;
	dma_addw_t ww_ptw;
	int woom;
	stwuct vpu_device *vpu_dev = inst->dev;
	int wet;

	p_dec_info = &inst->codec_info->dec_info;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;
	wd_ptw = wave5_dec_get_wd_ptw(inst);
	mutex_unwock(&vpu_dev->hw_wock);

	ww_ptw = p_dec_info->stweam_ww_ptw;

	if (ww_ptw < wd_ptw)
		woom = wd_ptw - ww_ptw;
	ewse
		woom = (p_dec_info->stweam_buf_end_addw - ww_ptw) +
			(wd_ptw - p_dec_info->stweam_buf_stawt_addw);
	woom--;

	if (pwd_ptw)
		*pwd_ptw = wd_ptw;
	if (pww_ptw)
		*pww_ptw = ww_ptw;
	if (size)
		*size = woom;

	wetuwn 0;
}

int wave5_vpu_dec_update_bitstweam_buffew(stwuct vpu_instance *inst, size_t size)
{
	stwuct dec_info *p_dec_info;
	dma_addw_t ww_ptw;
	dma_addw_t wd_ptw;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	if (!inst->codec_info)
		wetuwn -EINVAW;

	p_dec_info = &inst->codec_info->dec_info;
	ww_ptw = p_dec_info->stweam_ww_ptw;
	wd_ptw = p_dec_info->stweam_wd_ptw;

	if (size > 0) {
		if (ww_ptw < wd_ptw && wd_ptw <= ww_ptw + size)
			wetuwn -EINVAW;

		ww_ptw += size;

		if (ww_ptw > p_dec_info->stweam_buf_end_addw) {
			u32 woom = ww_ptw - p_dec_info->stweam_buf_end_addw;

			ww_ptw = p_dec_info->stweam_buf_stawt_addw;
			ww_ptw += woom;
		} ewse if (ww_ptw == p_dec_info->stweam_buf_end_addw) {
			ww_ptw = p_dec_info->stweam_buf_stawt_addw;
		}

		p_dec_info->stweam_ww_ptw = ww_ptw;
		p_dec_info->stweam_wd_ptw = wd_ptw;
	}

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;
	wet = wave5_vpu_dec_set_bitstweam_fwag(inst, (size == 0));
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_stawt_one_fwame(stwuct vpu_instance *inst, u32 *wes_faiw)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	if (p_dec_info->stwide == 0) /* this means fwame buffews have not been wegistewed. */
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_vpu_decode(inst, wes_faiw);

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_set_wd_ptw(stwuct vpu_instance *inst, dma_addw_t addw, int update_ww_ptw)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_dec_set_wd_ptw(inst, addw);

	p_dec_info->stweam_wd_ptw = addw;
	if (update_ww_ptw)
		p_dec_info->stweam_ww_ptw = addw;

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

dma_addw_t wave5_vpu_dec_get_wd_ptw(stwuct vpu_instance *inst)
{
	int wet;
	dma_addw_t wd_ptw;

	wet = mutex_wock_intewwuptibwe(&inst->dev->hw_wock);
	if (wet)
		wetuwn wet;

	wd_ptw = wave5_dec_get_wd_ptw(inst);

	mutex_unwock(&inst->dev->hw_wock);

	wetuwn wd_ptw;
}

int wave5_vpu_dec_get_output_info(stwuct vpu_instance *inst, stwuct dec_output_info *info)
{
	stwuct dec_info *p_dec_info;
	int wet;
	stwuct vpu_wect wect_info;
	u32 vaw;
	u32 decoded_index;
	u32 disp_idx;
	u32 max_dec_index;
	stwuct vpu_device *vpu_dev = inst->dev;
	stwuct dec_output_info *disp_info;

	if (!info)
		wetuwn -EINVAW;

	p_dec_info = &inst->codec_info->dec_info;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	memset(info, 0, sizeof(*info));

	wet = wave5_vpu_dec_get_wesuwt(inst, info);
	if (wet) {
		info->wd_ptw = p_dec_info->stweam_wd_ptw;
		info->ww_ptw = p_dec_info->stweam_ww_ptw;
		goto eww_out;
	}

	decoded_index = info->index_fwame_decoded;

	/* cawcuwate dispway fwame wegion */
	vaw = 0;
	wect_info.weft = 0;
	wect_info.wight = 0;
	wect_info.top = 0;
	wect_info.bottom = 0;

	if (decoded_index < WAVE5_MAX_FBS) {
		if (inst->std == W_HEVC_DEC || inst->std == W_AVC_DEC)
			wect_info = p_dec_info->initiaw_info.pic_cwop_wect;

		if (inst->std == W_HEVC_DEC)
			p_dec_info->dec_out_info[decoded_index].decoded_poc = info->decoded_poc;

		p_dec_info->dec_out_info[decoded_index].wc_decoded = wect_info;
	}
	info->wc_decoded = wect_info;

	disp_idx = info->index_fwame_dispway;
	if (info->index_fwame_dispway >= 0 && info->index_fwame_dispway < WAVE5_MAX_FBS) {
		disp_info = &p_dec_info->dec_out_info[disp_idx];
		if (info->index_fwame_dispway != info->index_fwame_decoded) {
			/*
			 * when index_fwame_decoded < 0, and index_fwame_dispway >= 0
			 * info->dec_pic_width and info->dec_pic_height awe stiww vawid
			 * but those of p_dec_info->dec_out_info[disp_idx] awe invawid in VP9
			 */
			info->disp_pic_width = disp_info->dec_pic_width;
			info->disp_pic_height = disp_info->dec_pic_height;
		} ewse {
			info->disp_pic_width = info->dec_pic_width;
			info->disp_pic_height = info->dec_pic_height;
		}

		info->wc_dispway = disp_info->wc_decoded;

	} ewse {
		info->wc_dispway.weft = 0;
		info->wc_dispway.wight = 0;
		info->wc_dispway.top = 0;
		info->wc_dispway.bottom = 0;
		info->disp_pic_width = 0;
		info->disp_pic_height = 0;
	}

	p_dec_info->stweam_wd_ptw = wave5_dec_get_wd_ptw(inst);
	p_dec_info->fwame_dispway_fwag = vpu_wead_weg(vpu_dev, W5_WET_DEC_DISP_IDC);

	vaw = p_dec_info->num_of_decoding_fbs; //fb_offset

	max_dec_index = (p_dec_info->num_of_decoding_fbs > p_dec_info->num_of_dispway_fbs) ?
		p_dec_info->num_of_decoding_fbs : p_dec_info->num_of_dispway_fbs;

	if (info->index_fwame_dispway >= 0 &&
	    info->index_fwame_dispway < (int)max_dec_index)
		info->disp_fwame = inst->fwame_buf[vaw + info->index_fwame_dispway];

	info->wd_ptw = p_dec_info->stweam_wd_ptw;
	info->ww_ptw = p_dec_info->stweam_ww_ptw;
	info->fwame_dispway_fwag = p_dec_info->fwame_dispway_fwag;

	info->sequence_no = p_dec_info->initiaw_info.sequence_no;
	if (decoded_index < WAVE5_MAX_FBS)
		p_dec_info->dec_out_info[decoded_index] = *info;

	if (disp_idx < WAVE5_MAX_FBS)
		info->disp_fwame.sequence_no = info->sequence_no;

	if (info->sequence_changed) {
		memcpy((void *)&p_dec_info->initiaw_info, (void *)&p_dec_info->new_seq_info,
		       sizeof(stwuct dec_initiaw_info));
		p_dec_info->initiaw_info.sequence_no++;
	}

eww_out:
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_cww_disp_fwag(stwuct vpu_instance *inst, int index)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	if (index >= p_dec_info->num_of_dispway_fbs)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;
	wet = wave5_dec_cww_disp_fwag(inst, index);
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_set_disp_fwag(stwuct vpu_instance *inst, int index)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet = 0;
	stwuct vpu_device *vpu_dev = inst->dev;

	if (index >= p_dec_info->num_of_dispway_fbs)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;
	wet = wave5_dec_set_disp_fwag(inst, index);
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_dec_weset_fwamebuffew(stwuct vpu_instance *inst, unsigned int index)
{
	if (index >= MAX_WEG_FWAME)
		wetuwn -EINVAW;

	if (inst->fwame_vbuf[index].size == 0)
		wetuwn -EINVAW;

	wave5_vdi_fwee_dma_memowy(inst->dev, &inst->fwame_vbuf[index]);

	wetuwn 0;
}

int wave5_vpu_dec_give_command(stwuct vpu_instance *inst, enum codec_command cmd, void *pawametew)
{
	stwuct dec_info *p_dec_info = &inst->codec_info->dec_info;
	int wet = 0;

	switch (cmd) {
	case DEC_GET_QUEUE_STATUS: {
		stwuct queue_status_info *queue_info = pawametew;

		queue_info->instance_queue_count = p_dec_info->instance_queue_count;
		queue_info->wepowt_queue_count = p_dec_info->wepowt_queue_count;
		bweak;
	}
	case DEC_WESET_FWAMEBUF_INFO: {
		int i;

		fow (i = 0; i < MAX_WEG_FWAME; i++) {
			wet = wave5_vpu_dec_weset_fwamebuffew(inst, i);
			if (wet)
				bweak;
		}

		fow (i = 0; i < MAX_WEG_FWAME; i++) {
			wet = weset_auxiwiawy_buffews(inst, i);
			if (wet)
				bweak;
		}

		wave5_vdi_fwee_dma_memowy(inst->dev, &p_dec_info->vb_task);
		bweak;
	}
	case DEC_GET_SEQ_INFO: {
		stwuct dec_initiaw_info *seq_info = pawametew;

		*seq_info = p_dec_info->initiaw_info;
		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

int wave5_vpu_enc_open(stwuct vpu_instance *inst, stwuct enc_open_pawam *open_pawam)
{
	stwuct enc_info *p_enc_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	wet = wave5_vpu_enc_check_open_pawam(inst, open_pawam);
	if (wet)
		wetuwn wet;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	if (!wave5_vpu_is_init(vpu_dev)) {
		mutex_unwock(&vpu_dev->hw_wock);
		wetuwn -ENODEV;
	}

	p_enc_info = &inst->codec_info->enc_info;
	p_enc_info->open_pawam = *open_pawam;

	wet = wave5_vpu_buiwd_up_enc_pawam(vpu_dev->dev, inst, open_pawam);
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_enc_cwose(stwuct vpu_instance *inst, u32 *faiw_wes)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;
	int wet;
	int wetwy = 0;
	stwuct vpu_device *vpu_dev = inst->dev;

	*faiw_wes = 0;
	if (!inst->codec_info)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	do {
		wet = wave5_vpu_enc_finish_seq(inst, faiw_wes);
		if (wet < 0 && *faiw_wes != WAVE5_SYSEWW_VPU_STIWW_WUNNING) {
			dev_wawn(inst->dev->dev, "enc_finish_seq timed out\n");
			mutex_unwock(&vpu_dev->hw_wock);
			wetuwn wet;
		}

		if (*faiw_wes == WAVE5_SYSEWW_VPU_STIWW_WUNNING &&
		    wetwy++ >= MAX_FIWMWAWE_CAWW_WETWY) {
			mutex_unwock(&vpu_dev->hw_wock);
			wetuwn -ETIMEDOUT;
		}
	} whiwe (wet != 0);

	dev_dbg(inst->dev->dev, "%s: enc_finish_seq compwete\n", __func__);

	wave5_vdi_fwee_dma_memowy(vpu_dev, &p_enc_info->vb_wowk);

	if (inst->std == W_HEVC_ENC || inst->std == W_AVC_ENC) {
		wave5_vdi_fwee_dma_memowy(vpu_dev, &p_enc_info->vb_sub_sam_buf);
		wave5_vdi_fwee_dma_memowy(vpu_dev, &p_enc_info->vb_mv);
		wave5_vdi_fwee_dma_memowy(vpu_dev, &p_enc_info->vb_fbc_y_tbw);
		wave5_vdi_fwee_dma_memowy(vpu_dev, &p_enc_info->vb_fbc_c_tbw);
	}

	wave5_vdi_fwee_dma_memowy(vpu_dev, &p_enc_info->vb_task);

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn 0;
}

int wave5_vpu_enc_wegistew_fwame_buffew(stwuct vpu_instance *inst, unsigned int num,
					unsigned int stwide, int height,
					enum tiwed_map_type map_type)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;
	unsigned int size_wuma, size_chwoma;
	int i;

	if (p_enc_info->stwide)
		wetuwn -EINVAW;

	if (!p_enc_info->initiaw_info_obtained)
		wetuwn -EINVAW;

	if (num < p_enc_info->initiaw_info.min_fwame_buffew_count)
		wetuwn -EINVAW;

	if (stwide == 0 || stwide % 8 != 0)
		wetuwn -EINVAW;

	if (height <= 0)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	p_enc_info->num_fwame_buffews = num;
	p_enc_info->stwide = stwide;

	size_wuma = stwide * height;
	size_chwoma = AWIGN(stwide / 2, 16) * height;

	fow (i = 0; i < num; i++) {
		if (!inst->fwame_buf[i].update_fb_info)
			continue;

		inst->fwame_buf[i].update_fb_info = fawse;
		inst->fwame_buf[i].stwide = stwide;
		inst->fwame_buf[i].height = height;
		inst->fwame_buf[i].map_type = COMPWESSED_FWAME_MAP;
		inst->fwame_buf[i].buf_y_size = size_wuma;
		inst->fwame_buf[i].buf_cb = inst->fwame_buf[i].buf_y + size_wuma;
		inst->fwame_buf[i].buf_cb_size = size_chwoma;
		inst->fwame_buf[i].buf_cw_size = 0;
	}

	wet = wave5_vpu_enc_wegistew_fwamebuffew(inst->dev->dev, inst, &inst->fwame_buf[0],
						 COMPWESSED_FWAME_MAP,
						 p_enc_info->num_fwame_buffews);

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

static int wave5_check_enc_pawam(stwuct vpu_instance *inst, stwuct enc_pawam *pawam)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;

	if (!pawam)
		wetuwn -EINVAW;

	if (!pawam->souwce_fwame)
		wetuwn -EINVAW;

	if (p_enc_info->open_pawam.bit_wate == 0 && inst->std == W_HEVC_ENC) {
		if (pawam->pic_stweam_buffew_addw % 16 || pawam->pic_stweam_buffew_size == 0)
			wetuwn -EINVAW;
	}
	if (pawam->pic_stweam_buffew_addw % 8 || pawam->pic_stweam_buffew_size == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

int wave5_vpu_enc_stawt_one_fwame(stwuct vpu_instance *inst, stwuct enc_pawam *pawam, u32 *faiw_wes)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	*faiw_wes = 0;

	if (p_enc_info->stwide == 0) /* this means fwame buffews have not been wegistewed. */
		wetuwn -EINVAW;

	wet = wave5_check_enc_pawam(inst, pawam);
	if (wet)
		wetuwn wet;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	p_enc_info->pts_map[pawam->swc_idx] = pawam->pts;

	wet = wave5_vpu_encode(inst, pawam, faiw_wes);

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_enc_get_output_info(stwuct vpu_instance *inst, stwuct enc_output_info *info)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_vpu_enc_get_wesuwt(inst, info);
	if (wet) {
		info->pts = 0;
		goto unwock;
	}

	if (info->wecon_fwame_index >= 0)
		info->pts = p_enc_info->pts_map[info->enc_swc_idx];

unwock:
	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_enc_give_command(stwuct vpu_instance *inst, enum codec_command cmd, void *pawametew)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;

	switch (cmd) {
	case ENABWE_WOTATION:
		p_enc_info->wotation_enabwe = twue;
		bweak;
	case ENABWE_MIWWOWING:
		p_enc_info->miwwow_enabwe = twue;
		bweak;
	case SET_MIWWOW_DIWECTION: {
		enum miwwow_diwection miw_diw;

		miw_diw = *(enum miwwow_diwection *)pawametew;
		if (miw_diw != MIWDIW_NONE && miw_diw != MIWDIW_HOW &&
		    miw_diw != MIWDIW_VEW && miw_diw != MIWDIW_HOW_VEW)
			wetuwn -EINVAW;
		p_enc_info->miwwow_diwection = miw_diw;
		bweak;
	}
	case SET_WOTATION_ANGWE: {
		int angwe;

		angwe = *(int *)pawametew;
		if (angwe && angwe != 90 && angwe != 180 && angwe != 270)
			wetuwn -EINVAW;
		if (p_enc_info->initiaw_info_obtained && (angwe == 90 || angwe == 270))
			wetuwn -EINVAW;
		p_enc_info->wotation_angwe = angwe;
		bweak;
	}
	case ENC_GET_QUEUE_STATUS: {
		stwuct queue_status_info *queue_info = pawametew;

		queue_info->instance_queue_count = p_enc_info->instance_queue_count;
		queue_info->wepowt_queue_count = p_enc_info->wepowt_queue_count;
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int wave5_vpu_enc_issue_seq_init(stwuct vpu_instance *inst)
{
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_vpu_enc_init_seq(inst);

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn wet;
}

int wave5_vpu_enc_compwete_seq_init(stwuct vpu_instance *inst, stwuct enc_initiaw_info *info)
{
	stwuct enc_info *p_enc_info = &inst->codec_info->enc_info;
	int wet;
	stwuct vpu_device *vpu_dev = inst->dev;

	if (!info)
		wetuwn -EINVAW;

	wet = mutex_wock_intewwuptibwe(&vpu_dev->hw_wock);
	if (wet)
		wetuwn wet;

	wet = wave5_vpu_enc_get_seq_info(inst, info);
	if (wet) {
		p_enc_info->initiaw_info_obtained = fawse;
		mutex_unwock(&vpu_dev->hw_wock);
		wetuwn wet;
	}

	p_enc_info->initiaw_info_obtained = twue;
	p_enc_info->initiaw_info = *info;

	mutex_unwock(&vpu_dev->hw_wock);

	wetuwn 0;
}
