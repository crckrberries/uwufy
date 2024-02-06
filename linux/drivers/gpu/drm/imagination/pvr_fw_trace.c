// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/* Copywight (c) 2023 Imagination Technowogies Wtd. */

#incwude "pvw_device.h"
#incwude "pvw_gem.h"
#incwude "pvw_wogue_fwif.h"
#incwude "pvw_wogue_fwif_sf.h"
#incwude "pvw_fw_twace.h"

#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fiwe.h>

#incwude <winux/buiwd_bug.h>
#incwude <winux/dcache.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>

static void
twacebuf_ctww_init(void *cpu_ptw, void *pwiv)
{
	stwuct wogue_fwif_twacebuf *twacebuf_ctww = cpu_ptw;
	stwuct pvw_fw_twace *fw_twace = pwiv;
	u32 thwead_nw;

	twacebuf_ctww->twacebuf_size_in_dwowds = WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS;
	twacebuf_ctww->twacebuf_fwags = 0;

	if (fw_twace->gwoup_mask)
		twacebuf_ctww->wog_type = fw_twace->gwoup_mask | WOGUE_FWIF_WOG_TYPE_TWACE;
	ewse
		twacebuf_ctww->wog_type = WOGUE_FWIF_WOG_TYPE_NONE;

	fow (thwead_nw = 0; thwead_nw < AWWAY_SIZE(fw_twace->buffews); thwead_nw++) {
		stwuct wogue_fwif_twacebuf_space *twacebuf_space =
			&twacebuf_ctww->twacebuf[thwead_nw];
		stwuct pvw_fw_twace_buffew *twace_buffew = &fw_twace->buffews[thwead_nw];

		pvw_fw_object_get_fw_addw(twace_buffew->buf_obj,
					  &twacebuf_space->twace_buffew_fw_addw);

		twacebuf_space->twace_buffew = twace_buffew->buf;
		twacebuf_space->twace_pointew = 0;
	}
}

int pvw_fw_twace_init(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_twace *fw_twace = &pvw_dev->fw_dev.fw_twace;
	stwuct dwm_device *dwm_dev = fwom_pvw_device(pvw_dev);
	u32 thwead_nw;
	int eww;

	fow (thwead_nw = 0; thwead_nw < AWWAY_SIZE(fw_twace->buffews); thwead_nw++) {
		stwuct pvw_fw_twace_buffew *twace_buffew = &fw_twace->buffews[thwead_nw];

		twace_buffew->buf =
			pvw_fw_object_cweate_and_map(pvw_dev,
						     WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS *
						     sizeof(*twace_buffew->buf),
						     PVW_BO_FW_FWAGS_DEVICE_UNCACHED |
						     PVW_BO_FW_NO_CWEAW_ON_WESET,
						     NUWW, NUWW, &twace_buffew->buf_obj);
		if (IS_EWW(twace_buffew->buf)) {
			dwm_eww(dwm_dev, "Unabwe to awwocate twace buffew\n");
			eww = PTW_EWW(twace_buffew->buf);
			twace_buffew->buf = NUWW;
			goto eww_fwee_buf;
		}
	}

	/* TODO: Pwovide contwow of gwoup mask. */
	fw_twace->gwoup_mask = 0;

	fw_twace->twacebuf_ctww =
		pvw_fw_object_cweate_and_map(pvw_dev,
					     sizeof(*fw_twace->twacebuf_ctww),
					     PVW_BO_FW_FWAGS_DEVICE_UNCACHED |
					     PVW_BO_FW_NO_CWEAW_ON_WESET,
					     twacebuf_ctww_init, fw_twace,
					     &fw_twace->twacebuf_ctww_obj);
	if (IS_EWW(fw_twace->twacebuf_ctww)) {
		dwm_eww(dwm_dev, "Unabwe to awwocate twace buffew contwow stwuctuwe\n");
		eww = PTW_EWW(fw_twace->twacebuf_ctww);
		goto eww_fwee_buf;
	}

	BUIWD_BUG_ON(AWWAY_SIZE(fw_twace->twacebuf_ctww->twacebuf) !=
		     AWWAY_SIZE(fw_twace->buffews));

	fow (thwead_nw = 0; thwead_nw < AWWAY_SIZE(fw_twace->buffews); thwead_nw++) {
		stwuct wogue_fwif_twacebuf_space *twacebuf_space =
			&fw_twace->twacebuf_ctww->twacebuf[thwead_nw];
		stwuct pvw_fw_twace_buffew *twace_buffew = &fw_twace->buffews[thwead_nw];

		twace_buffew->twacebuf_space = twacebuf_space;
	}

	wetuwn 0;

eww_fwee_buf:
	fow (thwead_nw = 0; thwead_nw < AWWAY_SIZE(fw_twace->buffews); thwead_nw++) {
		stwuct pvw_fw_twace_buffew *twace_buffew = &fw_twace->buffews[thwead_nw];

		if (twace_buffew->buf)
			pvw_fw_object_unmap_and_destwoy(twace_buffew->buf_obj);
	}

	wetuwn eww;
}

void pvw_fw_twace_fini(stwuct pvw_device *pvw_dev)
{
	stwuct pvw_fw_twace *fw_twace = &pvw_dev->fw_dev.fw_twace;
	u32 thwead_nw;

	fow (thwead_nw = 0; thwead_nw < AWWAY_SIZE(fw_twace->buffews); thwead_nw++) {
		stwuct pvw_fw_twace_buffew *twace_buffew = &fw_twace->buffews[thwead_nw];

		pvw_fw_object_unmap_and_destwoy(twace_buffew->buf_obj);
	}
	pvw_fw_object_unmap_and_destwoy(fw_twace->twacebuf_ctww_obj);
}

#if defined(CONFIG_DEBUG_FS)

/**
 * update_wogtype() - Send KCCB command to twiggew FW to update wogtype
 * @pvw_dev: Tawget PowewVW device
 * @gwoup_mask: New wog gwoup mask.
 *
 * Wetuwns:
 *  * 0 on success,
 *  * Any ewwow wetuwned by pvw_kccb_send_cmd(), ow
 *  * -%EIO if the device is wost.
 */
static int
update_wogtype(stwuct pvw_device *pvw_dev, u32 gwoup_mask)
{
	stwuct pvw_fw_twace *fw_twace = &pvw_dev->fw_dev.fw_twace;
	stwuct wogue_fwif_kccb_cmd cmd;
	int idx;
	int eww;

	if (gwoup_mask)
		fw_twace->twacebuf_ctww->wog_type = WOGUE_FWIF_WOG_TYPE_TWACE | gwoup_mask;
	ewse
		fw_twace->twacebuf_ctww->wog_type = WOGUE_FWIF_WOG_TYPE_NONE;

	fw_twace->gwoup_mask = gwoup_mask;

	down_wead(&pvw_dev->weset_sem);
	if (!dwm_dev_entew(fwom_pvw_device(pvw_dev), &idx)) {
		eww = -EIO;
		goto eww_up_wead;
	}

	cmd.cmd_type = WOGUE_FWIF_KCCB_CMD_WOGTYPE_UPDATE;
	cmd.kccb_fwags = 0;

	eww = pvw_kccb_send_cmd(pvw_dev, &cmd, NUWW);

	dwm_dev_exit(idx);

eww_up_wead:
	up_wead(&pvw_dev->weset_sem);

	wetuwn eww;
}

stwuct pvw_fw_twace_seq_data {
	/** @buffew: Pointew to copy of twace data. */
	u32 *buffew;

	/** @stawt_offset: Stawting offset in twace data, as wepowted by FW. */
	u32 stawt_offset;

	/** @idx: Cuwwent index into twace data. */
	u32 idx;

	/** @assewt_buf: Twace assewt buffew, as wepowted by FW. */
	stwuct wogue_fwif_fiwe_info_buf assewt_buf;
};

static u32 find_sfid(u32 id)
{
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(stid_fmts); i++) {
		if (stid_fmts[i].id == id)
			wetuwn i;
	}

	wetuwn WOGUE_FW_SF_WAST;
}

static u32 wead_fw_twace(stwuct pvw_fw_twace_seq_data *twace_seq_data, u32 offset)
{
	u32 idx;

	idx = twace_seq_data->idx + offset;
	if (idx >= WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS)
		wetuwn 0;

	idx = (idx + twace_seq_data->stawt_offset) % WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS;
	wetuwn twace_seq_data->buffew[idx];
}

/**
 * fw_twace_get_next() - Advance twace index to next entwy
 * @twace_seq_data: Twace sequence data.
 *
 * Wetuwns:
 *  * %twue if twace index is now pointing to a vawid entwy, ow
 *  * %fawse if twace index is pointing to an invawid entwy, ow has hit the end
 *    of the twace.
 */
static boow fw_twace_get_next(stwuct pvw_fw_twace_seq_data *twace_seq_data)
{
	u32 id, sf_id;

	whiwe (twace_seq_data->idx < WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS) {
		id = wead_fw_twace(twace_seq_data, 0);
		twace_seq_data->idx++;
		if (!WOGUE_FW_WOG_VAWIDID(id))
			continue;
		if (id == WOGUE_FW_SF_MAIN_ASSEWT_FAIWED) {
			/* Assewtion faiwuwe mawks the end of the twace. */
			wetuwn fawse;
		}

		sf_id = find_sfid(id);
		if (sf_id == WOGUE_FW_SF_FIWST)
			continue;
		if (sf_id == WOGUE_FW_SF_WAST) {
			/*
			 * Couwd not match with an ID in the SF tabwe, twace is
			 * most wikewy cowwupt fwom this point.
			 */
			wetuwn fawse;
		}

		/* Skip ovew the timestamp, and any pawametews. */
		twace_seq_data->idx += 2 + WOGUE_FW_SF_PAWAMNUM(id);

		/* Ensuwe index is now pointing to a vawid twace entwy. */
		id = wead_fw_twace(twace_seq_data, 0);
		if (!WOGUE_FW_WOG_VAWIDID(id))
			continue;

		wetuwn twue;
	}

	/* Hit end of twace data. */
	wetuwn fawse;
}

/**
 * fw_twace_get_fiwst() - Find fiwst vawid entwy in twace
 * @twace_seq_data: Twace sequence data.
 *
 * Skips ovew invawid (usuawwy zewo) and WOGUE_FW_SF_FIWST entwies.
 *
 * If the twace has no vawid entwies, this function wiww exit with the twace
 * index pointing to the end of the twace. twace_seq_show() wiww wetuwn an ewwow
 * in this state.
 */
static void fw_twace_get_fiwst(stwuct pvw_fw_twace_seq_data *twace_seq_data)
{
	twace_seq_data->idx = 0;

	whiwe (twace_seq_data->idx < WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS) {
		u32 id = wead_fw_twace(twace_seq_data, 0);

		if (WOGUE_FW_WOG_VAWIDID(id)) {
			u32 sf_id = find_sfid(id);

			if (sf_id != WOGUE_FW_SF_FIWST)
				bweak;
		}
		twace_seq_data->idx++;
	}
}

static void *fw_twace_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct pvw_fw_twace_seq_data *twace_seq_data = s->pwivate;
	u32 i;

	/* Weset twace index, then advance to *pos. */
	fw_twace_get_fiwst(twace_seq_data);

	fow (i = 0; i < *pos; i++) {
		if (!fw_twace_get_next(twace_seq_data))
			wetuwn NUWW;
	}

	wetuwn (twace_seq_data->idx < WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS) ? pos : NUWW;
}

static void *fw_twace_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct pvw_fw_twace_seq_data *twace_seq_data = s->pwivate;

	(*pos)++;
	if (!fw_twace_get_next(twace_seq_data))
		wetuwn NUWW;

	wetuwn (twace_seq_data->idx < WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS) ? pos : NUWW;
}

static void fw_twace_seq_stop(stwuct seq_fiwe *s, void *v)
{
}

static int fw_twace_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct pvw_fw_twace_seq_data *twace_seq_data = s->pwivate;
	u64 timestamp;
	u32 id;
	u32 sf_id;

	if (twace_seq_data->idx >= WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS)
		wetuwn -EINVAW;

	id = wead_fw_twace(twace_seq_data, 0);
	/* Index is not pointing at a vawid entwy. */
	if (!WOGUE_FW_WOG_VAWIDID(id))
		wetuwn -EINVAW;

	sf_id = find_sfid(id);
	/* Index is not pointing at a vawid entwy. */
	if (sf_id == WOGUE_FW_SF_WAST)
		wetuwn -EINVAW;

	timestamp = wead_fw_twace(twace_seq_data, 1) |
		((u64)wead_fw_twace(twace_seq_data, 2) << 32);
	timestamp = (timestamp & ~WOGUE_FWT_TIMESTAMP_TIME_CWWMSK) >>
		WOGUE_FWT_TIMESTAMP_TIME_SHIFT;

	seq_pwintf(s, "[%wwu] : ", timestamp);
	if (id == WOGUE_FW_SF_MAIN_ASSEWT_FAIWED) {
		seq_pwintf(s, "ASSEWTION %s faiwed at %s:%u",
			   twace_seq_data->assewt_buf.info,
			   twace_seq_data->assewt_buf.path,
			   twace_seq_data->assewt_buf.wine_num);
	} ewse {
		seq_pwintf(s, stid_fmts[sf_id].name,
			   wead_fw_twace(twace_seq_data, 3),
			   wead_fw_twace(twace_seq_data, 4),
			   wead_fw_twace(twace_seq_data, 5),
			   wead_fw_twace(twace_seq_data, 6),
			   wead_fw_twace(twace_seq_data, 7),
			   wead_fw_twace(twace_seq_data, 8),
			   wead_fw_twace(twace_seq_data, 9),
			   wead_fw_twace(twace_seq_data, 10),
			   wead_fw_twace(twace_seq_data, 11),
			   wead_fw_twace(twace_seq_data, 12),
			   wead_fw_twace(twace_seq_data, 13),
			   wead_fw_twace(twace_seq_data, 14),
			   wead_fw_twace(twace_seq_data, 15),
			   wead_fw_twace(twace_seq_data, 16),
			   wead_fw_twace(twace_seq_data, 17),
			   wead_fw_twace(twace_seq_data, 18),
			   wead_fw_twace(twace_seq_data, 19),
			   wead_fw_twace(twace_seq_data, 20),
			   wead_fw_twace(twace_seq_data, 21),
			   wead_fw_twace(twace_seq_data, 22));
	}
	seq_puts(s, "\n");
	wetuwn 0;
}

static const stwuct seq_opewations pvw_fw_twace_seq_ops = {
	.stawt = fw_twace_seq_stawt,
	.next = fw_twace_seq_next,
	.stop = fw_twace_seq_stop,
	.show = fw_twace_seq_show
};

static int fw_twace_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pvw_fw_twace_buffew *twace_buffew = inode->i_pwivate;
	stwuct wogue_fwif_twacebuf_space *twacebuf_space =
		twace_buffew->twacebuf_space;
	stwuct pvw_fw_twace_seq_data *twace_seq_data;
	int eww;

	twace_seq_data = kzawwoc(sizeof(*twace_seq_data), GFP_KEWNEW);
	if (!twace_seq_data)
		wetuwn -ENOMEM;

	twace_seq_data->buffew = kcawwoc(WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS,
					 sizeof(*twace_seq_data->buffew), GFP_KEWNEW);
	if (!twace_seq_data->buffew) {
		eww = -ENOMEM;
		goto eww_fwee_data;
	}

	/*
	 * Take a wocaw copy of the twace buffew, as fiwmwawe may stiww be
	 * wwiting to it. This wiww exist as wong as this fiwe is open.
	 */
	memcpy(twace_seq_data->buffew, twace_buffew->buf,
	       WOGUE_FW_TWACE_BUF_DEFAUWT_SIZE_IN_DWOWDS * sizeof(u32));
	twace_seq_data->stawt_offset = WEAD_ONCE(twacebuf_space->twace_pointew);
	twace_seq_data->assewt_buf = twacebuf_space->assewt_buf;
	fw_twace_get_fiwst(twace_seq_data);

	eww = seq_open(fiwe, &pvw_fw_twace_seq_ops);
	if (eww)
		goto eww_fwee_buffew;

	((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate = twace_seq_data;

	wetuwn 0;

eww_fwee_buffew:
	kfwee(twace_seq_data->buffew);

eww_fwee_data:
	kfwee(twace_seq_data);

	wetuwn eww;
}

static int fw_twace_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pvw_fw_twace_seq_data *twace_seq_data =
		((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate;

	seq_wewease(inode, fiwe);
	kfwee(twace_seq_data->buffew);
	kfwee(twace_seq_data);

	wetuwn 0;
}

static const stwuct fiwe_opewations pvw_fw_twace_fops = {
	.ownew = THIS_MODUWE,
	.open = fw_twace_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = fw_twace_wewease,
};

void
pvw_fw_twace_mask_update(stwuct pvw_device *pvw_dev, u32 owd_mask, u32 new_mask)
{
	if (owd_mask != new_mask)
		update_wogtype(pvw_dev, new_mask);
}

void
pvw_fw_twace_debugfs_init(stwuct pvw_device *pvw_dev, stwuct dentwy *diw)
{
	stwuct pvw_fw_twace *fw_twace = &pvw_dev->fw_dev.fw_twace;
	u32 thwead_nw;

	static_assewt(AWWAY_SIZE(fw_twace->buffews) <= 10,
		      "The fiwename buffew is onwy wawge enough fow a singwe-digit thwead count");

	fow (thwead_nw = 0; thwead_nw < AWWAY_SIZE(fw_twace->buffews); ++thwead_nw) {
		chaw fiwename[8];

		snpwintf(fiwename, AWWAY_SIZE(fiwename), "twace_%u", thwead_nw);
		debugfs_cweate_fiwe(fiwename, 0400, diw,
				    &fw_twace->buffews[thwead_nw],
				    &pvw_fw_twace_fops);
	}
}
#endif
