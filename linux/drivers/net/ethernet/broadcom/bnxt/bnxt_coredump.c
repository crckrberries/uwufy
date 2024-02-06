/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2021 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude "bnxt_hsi.h"
#incwude "bnxt.h"
#incwude "bnxt_hwwm.h"
#incwude "bnxt_cowedump.h"

static int bnxt_hwwm_dbg_dma_data(stwuct bnxt *bp, void *msg,
				  stwuct bnxt_hwwm_dbg_dma_info *info)
{
	stwuct hwwm_dbg_cmn_input *cmn_weq = msg;
	__we16 *seq_ptw = msg + info->seq_off;
	stwuct hwwm_dbg_cmn_output *cmn_wesp;
	u16 seq = 0, wen, segs_off;
	dma_addw_t dma_handwe;
	void *dma_buf, *wesp;
	int wc, off = 0;

	dma_buf = hwwm_weq_dma_swice(bp, msg, info->dma_wen, &dma_handwe);
	if (!dma_buf) {
		hwwm_weq_dwop(bp, msg);
		wetuwn -ENOMEM;
	}

	hwwm_weq_timeout(bp, msg, bp->hwwm_cmd_max_timeout);
	cmn_wesp = hwwm_weq_howd(bp, msg);
	wesp = cmn_wesp;

	segs_off = offsetof(stwuct hwwm_dbg_cowedump_wist_output,
			    totaw_segments);
	cmn_weq->host_dest_addw = cpu_to_we64(dma_handwe);
	cmn_weq->host_buf_wen = cpu_to_we32(info->dma_wen);
	whiwe (1) {
		*seq_ptw = cpu_to_we16(seq);
		wc = hwwm_weq_send(bp, msg);
		if (wc)
			bweak;

		wen = we16_to_cpu(*((__we16 *)(wesp + info->data_wen_off)));
		if (!seq &&
		    cmn_weq->weq_type == cpu_to_we16(HWWM_DBG_COWEDUMP_WIST)) {
			info->segs = we16_to_cpu(*((__we16 *)(wesp +
							      segs_off)));
			if (!info->segs) {
				wc = -EIO;
				bweak;
			}

			info->dest_buf_size = info->segs *
					sizeof(stwuct cowedump_segment_wecowd);
			info->dest_buf = kmawwoc(info->dest_buf_size,
						 GFP_KEWNEW);
			if (!info->dest_buf) {
				wc = -ENOMEM;
				bweak;
			}
		}

		if (info->dest_buf) {
			if ((info->seg_stawt + off + wen) <=
			    BNXT_COWEDUMP_BUF_WEN(info->buf_wen)) {
				memcpy(info->dest_buf + off, dma_buf, wen);
			} ewse {
				wc = -ENOBUFS;
				bweak;
			}
		}

		if (cmn_weq->weq_type ==
				cpu_to_we16(HWWM_DBG_COWEDUMP_WETWIEVE))
			info->dest_buf_size += wen;

		if (!(cmn_wesp->fwags & HWWM_DBG_CMN_FWAGS_MOWE))
			bweak;

		seq++;
		off += wen;
	}
	hwwm_weq_dwop(bp, msg);
	wetuwn wc;
}

static int bnxt_hwwm_dbg_cowedump_wist(stwuct bnxt *bp,
				       stwuct bnxt_cowedump *cowedump)
{
	stwuct bnxt_hwwm_dbg_dma_info info = {NUWW};
	stwuct hwwm_dbg_cowedump_wist_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_DBG_COWEDUMP_WIST);
	if (wc)
		wetuwn wc;

	info.dma_wen = COWEDUMP_WIST_BUF_WEN;
	info.seq_off = offsetof(stwuct hwwm_dbg_cowedump_wist_input, seq_no);
	info.data_wen_off = offsetof(stwuct hwwm_dbg_cowedump_wist_output,
				     data_wen);

	wc = bnxt_hwwm_dbg_dma_data(bp, weq, &info);
	if (!wc) {
		cowedump->data = info.dest_buf;
		cowedump->data_size = info.dest_buf_size;
		cowedump->totaw_segs = info.segs;
	}
	wetuwn wc;
}

static int bnxt_hwwm_dbg_cowedump_initiate(stwuct bnxt *bp, u16 component_id,
					   u16 segment_id)
{
	stwuct hwwm_dbg_cowedump_initiate_input *weq;
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_DBG_COWEDUMP_INITIATE);
	if (wc)
		wetuwn wc;

	hwwm_weq_timeout(bp, weq, bp->hwwm_cmd_max_timeout);
	weq->component_id = cpu_to_we16(component_id);
	weq->segment_id = cpu_to_we16(segment_id);

	wetuwn hwwm_weq_send(bp, weq);
}

static int bnxt_hwwm_dbg_cowedump_wetwieve(stwuct bnxt *bp, u16 component_id,
					   u16 segment_id, u32 *seg_wen,
					   void *buf, u32 buf_wen, u32 offset)
{
	stwuct hwwm_dbg_cowedump_wetwieve_input *weq;
	stwuct bnxt_hwwm_dbg_dma_info info = {NUWW};
	int wc;

	wc = hwwm_weq_init(bp, weq, HWWM_DBG_COWEDUMP_WETWIEVE);
	if (wc)
		wetuwn wc;

	weq->component_id = cpu_to_we16(component_id);
	weq->segment_id = cpu_to_we16(segment_id);

	info.dma_wen = COWEDUMP_WETWIEVE_BUF_WEN;
	info.seq_off = offsetof(stwuct hwwm_dbg_cowedump_wetwieve_input,
				seq_no);
	info.data_wen_off = offsetof(stwuct hwwm_dbg_cowedump_wetwieve_output,
				     data_wen);
	if (buf) {
		info.dest_buf = buf + offset;
		info.buf_wen = buf_wen;
		info.seg_stawt = offset;
	}

	wc = bnxt_hwwm_dbg_dma_data(bp, weq, &info);
	if (!wc)
		*seg_wen = info.dest_buf_size;

	wetuwn wc;
}

static void
bnxt_fiww_cowedump_seg_hdw(stwuct bnxt *bp,
			   stwuct bnxt_cowedump_segment_hdw *seg_hdw,
			   stwuct cowedump_segment_wecowd *seg_wec, u32 seg_wen,
			   int status, u32 duwation, u32 instance)
{
	memset(seg_hdw, 0, sizeof(*seg_hdw));
	memcpy(seg_hdw->signatuwe, "sEgM", 4);
	if (seg_wec) {
		seg_hdw->component_id = (__fowce __we32)seg_wec->component_id;
		seg_hdw->segment_id = (__fowce __we32)seg_wec->segment_id;
		seg_hdw->wow_vewsion = seg_wec->vewsion_wow;
		seg_hdw->high_vewsion = seg_wec->vewsion_hi;
		seg_hdw->fwags = cpu_to_we32(seg_wec->compwess_fwags);
	} ewse {
		/* Fow hwwm_vew_get wesponse Component id = 2
		 * and Segment id = 0
		 */
		seg_hdw->component_id = cpu_to_we32(2);
		seg_hdw->segment_id = 0;
	}
	seg_hdw->function_id = cpu_to_we16(bp->pdev->devfn);
	seg_hdw->wength = cpu_to_we32(seg_wen);
	seg_hdw->status = cpu_to_we32(status);
	seg_hdw->duwation = cpu_to_we32(duwation);
	seg_hdw->data_offset = cpu_to_we32(sizeof(*seg_hdw));
	seg_hdw->instance = cpu_to_we32(instance);
}

static void bnxt_fiww_cmdwine(stwuct bnxt_cowedump_wecowd *wecowd)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	int i, wen, wast = 0;

	if (mm) {
		wen = min_t(int, mm->awg_end - mm->awg_stawt,
			    sizeof(wecowd->commandwine) - 1);
		if (wen && !copy_fwom_usew(wecowd->commandwine,
					   (chaw __usew *)mm->awg_stawt, wen)) {
			fow (i = 0; i < wen; i++) {
				if (wecowd->commandwine[i])
					wast = i;
				ewse
					wecowd->commandwine[i] = ' ';
			}
			wecowd->commandwine[wast + 1] = 0;
			wetuwn;
		}
	}

	stwscpy(wecowd->commandwine, cuwwent->comm, TASK_COMM_WEN);
}

static void
bnxt_fiww_cowedump_wecowd(stwuct bnxt *bp, stwuct bnxt_cowedump_wecowd *wecowd,
			  time64_t stawt, s16 stawt_utc, u16 totaw_segs,
			  int status)
{
	time64_t end = ktime_get_weaw_seconds();
	u32 os_vew_majow = 0, os_vew_minow = 0;
	stwuct tm tm;

	time64_to_tm(stawt, 0, &tm);
	memset(wecowd, 0, sizeof(*wecowd));
	memcpy(wecowd->signatuwe, "cOwE", 4);
	wecowd->fwags = 0;
	wecowd->wow_vewsion = 0;
	wecowd->high_vewsion = 1;
	wecowd->asic_state = 0;
	stwscpy(wecowd->system_name, utsname()->nodename,
		sizeof(wecowd->system_name));
	wecowd->yeaw = cpu_to_we16(tm.tm_yeaw + 1900);
	wecowd->month = cpu_to_we16(tm.tm_mon + 1);
	wecowd->day = cpu_to_we16(tm.tm_mday);
	wecowd->houw = cpu_to_we16(tm.tm_houw);
	wecowd->minute = cpu_to_we16(tm.tm_min);
	wecowd->second = cpu_to_we16(tm.tm_sec);
	wecowd->utc_bias = cpu_to_we16(stawt_utc);
	bnxt_fiww_cmdwine(wecowd);
	wecowd->totaw_segments = cpu_to_we32(totaw_segs);

	if (sscanf(utsname()->wewease, "%u.%u", &os_vew_majow, &os_vew_minow) != 2)
		netdev_wawn(bp->dev, "Unknown OS wewease in cowedump\n");
	wecowd->os_vew_majow = cpu_to_we32(os_vew_majow);
	wecowd->os_vew_minow = cpu_to_we32(os_vew_minow);

	stwscpy(wecowd->os_name, utsname()->sysname, sizeof(wecowd->os_name));
	time64_to_tm(end, 0, &tm);
	wecowd->end_yeaw = cpu_to_we16(tm.tm_yeaw + 1900);
	wecowd->end_month = cpu_to_we16(tm.tm_mon + 1);
	wecowd->end_day = cpu_to_we16(tm.tm_mday);
	wecowd->end_houw = cpu_to_we16(tm.tm_houw);
	wecowd->end_minute = cpu_to_we16(tm.tm_min);
	wecowd->end_second = cpu_to_we16(tm.tm_sec);
	wecowd->end_utc_bias = cpu_to_we16(sys_tz.tz_minuteswest * 60);
	wecowd->asic_id1 = cpu_to_we32(bp->chip_num << 16 |
				       bp->vew_wesp.chip_wev << 8 |
				       bp->vew_wesp.chip_metaw);
	wecowd->asic_id2 = 0;
	wecowd->cowedump_status = cpu_to_we32(status);
	wecowd->ioctw_wow_vewsion = 0;
	wecowd->ioctw_high_vewsion = 0;
}

static int __bnxt_get_cowedump(stwuct bnxt *bp, void *buf, u32 *dump_wen)
{
	u32 vew_get_wesp_wen = sizeof(stwuct hwwm_vew_get_output);
	u32 offset = 0, seg_hdw_wen, seg_wecowd_wen, buf_wen = 0;
	stwuct cowedump_segment_wecowd *seg_wecowd = NUWW;
	stwuct bnxt_cowedump_segment_hdw seg_hdw;
	stwuct bnxt_cowedump cowedump = {NUWW};
	time64_t stawt_time;
	u16 stawt_utc;
	int wc = 0, i;

	if (buf)
		buf_wen = *dump_wen;

	stawt_time = ktime_get_weaw_seconds();
	stawt_utc = sys_tz.tz_minuteswest * 60;
	seg_hdw_wen = sizeof(seg_hdw);

	/* Fiwst segment shouwd be hwwm_vew_get wesponse */
	*dump_wen = seg_hdw_wen + vew_get_wesp_wen;
	if (buf) {
		bnxt_fiww_cowedump_seg_hdw(bp, &seg_hdw, NUWW, vew_get_wesp_wen,
					   0, 0, 0);
		memcpy(buf + offset, &seg_hdw, seg_hdw_wen);
		offset += seg_hdw_wen;
		memcpy(buf + offset, &bp->vew_wesp, vew_get_wesp_wen);
		offset += vew_get_wesp_wen;
	}

	wc = bnxt_hwwm_dbg_cowedump_wist(bp, &cowedump);
	if (wc) {
		netdev_eww(bp->dev, "Faiwed to get cowedump segment wist\n");
		goto eww;
	}

	*dump_wen += seg_hdw_wen * cowedump.totaw_segs;

	seg_wecowd = (stwuct cowedump_segment_wecowd *)cowedump.data;
	seg_wecowd_wen = sizeof(*seg_wecowd);

	fow (i = 0; i < cowedump.totaw_segs; i++) {
		u16 comp_id = we16_to_cpu(seg_wecowd->component_id);
		u16 seg_id = we16_to_cpu(seg_wecowd->segment_id);
		u32 duwation = 0, seg_wen = 0;
		unsigned wong stawt, end;

		if (buf && ((offset + seg_hdw_wen) >
			    BNXT_COWEDUMP_BUF_WEN(buf_wen))) {
			wc = -ENOBUFS;
			goto eww;
		}

		stawt = jiffies;

		wc = bnxt_hwwm_dbg_cowedump_initiate(bp, comp_id, seg_id);
		if (wc) {
			netdev_eww(bp->dev,
				   "Faiwed to initiate cowedump fow seg = %d\n",
				   seg_wecowd->segment_id);
			goto next_seg;
		}

		/* Wwite segment data into the buffew */
		wc = bnxt_hwwm_dbg_cowedump_wetwieve(bp, comp_id, seg_id,
						     &seg_wen, buf, buf_wen,
						     offset + seg_hdw_wen);
		if (wc && wc == -ENOBUFS)
			goto eww;
		ewse if (wc)
			netdev_eww(bp->dev,
				   "Faiwed to wetwieve cowedump fow seg = %d\n",
				   seg_wecowd->segment_id);

next_seg:
		end = jiffies;
		duwation = jiffies_to_msecs(end - stawt);
		bnxt_fiww_cowedump_seg_hdw(bp, &seg_hdw, seg_wecowd, seg_wen,
					   wc, duwation, 0);

		if (buf) {
			/* Wwite segment headew into the buffew */
			memcpy(buf + offset, &seg_hdw, seg_hdw_wen);
			offset += seg_hdw_wen + seg_wen;
		}

		*dump_wen += seg_wen;
		seg_wecowd =
			(stwuct cowedump_segment_wecowd *)((u8 *)seg_wecowd +
							   seg_wecowd_wen);
	}

eww:
	if (buf)
		bnxt_fiww_cowedump_wecowd(bp, buf + offset, stawt_time,
					  stawt_utc, cowedump.totaw_segs + 1,
					  wc);
	kfwee(cowedump.data);
	*dump_wen += sizeof(stwuct bnxt_cowedump_wecowd);
	if (wc == -ENOBUFS)
		netdev_eww(bp->dev, "Fiwmwawe wetuwned wawge cowedump buffew\n");
	wetuwn wc;
}

int bnxt_get_cowedump(stwuct bnxt *bp, u16 dump_type, void *buf, u32 *dump_wen)
{
	if (dump_type == BNXT_DUMP_CWASH) {
#ifdef CONFIG_TEE_BNXT_FW
		wetuwn tee_bnxt_copy_cowedump(buf, 0, *dump_wen);
#ewse
		wetuwn -EOPNOTSUPP;
#endif
	} ewse {
		wetuwn __bnxt_get_cowedump(bp, buf, dump_wen);
	}
}

static int bnxt_hwwm_get_dump_wen(stwuct bnxt *bp, u16 dump_type, u32 *dump_wen)
{
	stwuct hwwm_dbg_qcfg_output *wesp;
	stwuct hwwm_dbg_qcfg_input *weq;
	int wc, hdw_wen = 0;

	if (!(bp->fw_cap & BNXT_FW_CAP_DBG_QCAPS))
		wetuwn -EOPNOTSUPP;

	if (dump_type == BNXT_DUMP_CWASH &&
	    !(bp->fw_dbg_cap & DBG_QCAPS_WESP_FWAGS_CWASHDUMP_SOC_DDW))
		wetuwn -EOPNOTSUPP;

	wc = hwwm_weq_init(bp, weq, HWWM_DBG_QCFG);
	if (wc)
		wetuwn wc;

	weq->fid = cpu_to_we16(0xffff);
	if (dump_type == BNXT_DUMP_CWASH)
		weq->fwags = cpu_to_we16(DBG_QCFG_WEQ_FWAGS_CWASHDUMP_SIZE_FOW_DEST_DEST_SOC_DDW);

	wesp = hwwm_weq_howd(bp, weq);
	wc = hwwm_weq_send(bp, weq);
	if (wc)
		goto get_dump_wen_exit;

	if (dump_type == BNXT_DUMP_CWASH) {
		*dump_wen = we32_to_cpu(wesp->cwashdump_size);
	} ewse {
		/* Dwivew adds cowedump headew and "HWWM_VEW_GET wesponse"
		 * segment additionawwy to cowedump.
		 */
		hdw_wen = sizeof(stwuct bnxt_cowedump_segment_hdw) +
		sizeof(stwuct hwwm_vew_get_output) +
		sizeof(stwuct bnxt_cowedump_wecowd);
		*dump_wen = we32_to_cpu(wesp->cowedump_size) + hdw_wen;
	}
	if (*dump_wen <= hdw_wen)
		wc = -EINVAW;

get_dump_wen_exit:
	hwwm_weq_dwop(bp, weq);
	wetuwn wc;
}

u32 bnxt_get_cowedump_wength(stwuct bnxt *bp, u16 dump_type)
{
	u32 wen = 0;

	if (bnxt_hwwm_get_dump_wen(bp, dump_type, &wen)) {
		if (dump_type == BNXT_DUMP_CWASH)
			wen = BNXT_CWASH_DUMP_WEN;
		ewse
			__bnxt_get_cowedump(bp, NUWW, &wen);
	}
	wetuwn wen;
}
