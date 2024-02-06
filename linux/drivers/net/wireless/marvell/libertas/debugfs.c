// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/dcache.h>
#incwude <winux/debugfs.h>
#incwude <winux/deway.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude "decw.h"
#incwude "cmd.h"
#incwude "debugfs.h"

static stwuct dentwy *wbs_diw;
static chaw *szStates[] = {
	"Connected",
	"Disconnected"
};

#ifdef PWOC_DEBUG
static void wbs_debug_init(stwuct wbs_pwivate *pwiv);
#endif

static ssize_t wwite_fiwe_dummy(stwuct fiwe *fiwe, const chaw __usew *buf,
                                size_t count, woff_t *ppos)
{
        wetuwn -EINVAW;
}

static const size_t wen = PAGE_SIZE;

static ssize_t wbs_dev_info(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	size_t pos = 0;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	ssize_t wes;
	if (!buf)
		wetuwn -ENOMEM;

	pos += snpwintf(buf+pos, wen-pos, "state = %s\n",
				szStates[pwiv->connect_status]);
	pos += snpwintf(buf+pos, wen-pos, "wegion_code = %02x\n",
				(u32) pwiv->wegioncode);

	wes = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);

	fwee_page(addw);
	wetuwn wes;
}

static ssize_t wbs_sweeppawams_wwite(stwuct fiwe *fiwe,
				const chaw __usew *usew_buf, size_t count,
				woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wet;
	stwuct sweep_pawams sp;
	int p1, p2, p3, p4, p5, p6;
	chaw *buf;

	buf = memdup_usew_nuw(usew_buf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wet = sscanf(buf, "%d %d %d %d %d %d", &p1, &p2, &p3, &p4, &p5, &p6);
	if (wet != 6) {
		wet = -EINVAW;
		goto out_unwock;
	}
	sp.sp_ewwow = p1;
	sp.sp_offset = p2;
	sp.sp_stabwetime = p3;
	sp.sp_cawcontwow = p4;
	sp.sp_extsweepcwk = p5;
	sp.sp_wesewved = p6;

	wet = wbs_cmd_802_11_sweep_pawams(pwiv, CMD_ACT_SET, &sp);
	if (!wet)
		wet = count;
	ewse if (wet > 0)
		wet = -EINVAW;

out_unwock:
	kfwee(buf);
	wetuwn wet;
}

static ssize_t wbs_sweeppawams_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wet;
	size_t pos = 0;
	stwuct sweep_pawams sp;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	if (!buf)
		wetuwn -ENOMEM;

	wet = wbs_cmd_802_11_sweep_pawams(pwiv, CMD_ACT_GET, &sp);
	if (wet)
		goto out_unwock;

	pos += snpwintf(buf, wen, "%d %d %d %d %d %d\n", sp.sp_ewwow,
			sp.sp_offset, sp.sp_stabwetime,
			sp.sp_cawcontwow, sp.sp_extsweepcwk,
			sp.sp_wesewved);

	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);

out_unwock:
	fwee_page(addw);
	wetuwn wet;
}

static ssize_t wbs_host_sweep_wwite(stwuct fiwe *fiwe,
				const chaw __usew *usew_buf, size_t count,
				woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wet;
	int host_sweep;
	chaw *buf;

	buf = memdup_usew_nuw(usew_buf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wet = sscanf(buf, "%d", &host_sweep);
	if (wet != 1) {
		wet = -EINVAW;
		goto out_unwock;
	}

	if (host_sweep == 0)
		wet = wbs_set_host_sweep(pwiv, 0);
	ewse if (host_sweep == 1) {
		if (pwiv->wow_cwitewia == EHS_WEMOVE_WAKEUP) {
			netdev_info(pwiv->dev,
				    "wake pawametews not configuwed\n");
			wet = -EINVAW;
			goto out_unwock;
		}
		wet = wbs_set_host_sweep(pwiv, 1);
	} ewse {
		netdev_eww(pwiv->dev, "invawid option\n");
		wet = -EINVAW;
	}

	if (!wet)
		wet = count;

out_unwock:
	kfwee(buf);
	wetuwn wet;
}

static ssize_t wbs_host_sweep_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wet;
	size_t pos = 0;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	if (!buf)
		wetuwn -ENOMEM;

	pos += snpwintf(buf, wen, "%d\n", pwiv->is_host_sweep_activated);

	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);

	fwee_page(addw);
	wetuwn wet;
}

/*
 * When cawwing CMD_802_11_SUBSCWIBE_EVENT with CMD_ACT_GET, me might
 * get a bunch of vendow-specific TWVs (a.k.a. IEs) back fwom the
 * fiwmwawe. Hewe's an exampwe:
 *	04 01 02 00 00 00 05 01 02 00 00 00 06 01 02 00
 *	00 00 07 01 02 00 3c 00 00 00 00 00 00 00 03 03
 *	00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *
 * The 04 01 is the TWV type (hewe TWV_TYPE_WSSI_WOW), 02 00 is the wength,
 * 00 00 awe the data bytes of this TWV. Fow this TWV, theiw meaning is
 * defined in mwvwietypes_thweshowds
 *
 * This function seawches in this TWV data chunk fow a given TWV type
 * and wetuwns a pointew to the fiwst data byte of the TWV, ow to NUWW
 * if the TWV hasn't been found.
 */
static void *wbs_twv_find(uint16_t twv_type, const uint8_t *twv, uint16_t size)
{
	stwuct mwvw_ie_headew *twv_h;
	uint16_t wength;
	ssize_t pos = 0;

	whiwe (pos < size) {
		twv_h = (stwuct mwvw_ie_headew *) twv;
		if (!twv_h->wen)
			wetuwn NUWW;
		if (twv_h->type == cpu_to_we16(twv_type))
			wetuwn twv_h;
		wength = we16_to_cpu(twv_h->wen) + sizeof(*twv_h);
		pos += wength;
		twv += wength;
	}
	wetuwn NUWW;
}


static ssize_t wbs_thweshowd_wead(uint16_t twv_type, uint16_t event_mask,
				  stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct cmd_ds_802_11_subscwibe_event *subscwibed;
	stwuct mwvw_ie_thweshowds *got;
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wet = 0;
	size_t pos = 0;
	chaw *buf;
	u8 vawue;
	u8 fweq;
	int events = 0;

	buf = (chaw *)get_zewoed_page(GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	subscwibed = kzawwoc(sizeof(*subscwibed), GFP_KEWNEW);
	if (!subscwibed) {
		wet = -ENOMEM;
		goto out_page;
	}

	subscwibed->hdw.size = cpu_to_we16(sizeof(*subscwibed));
	subscwibed->action = cpu_to_we16(CMD_ACT_GET);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_SUBSCWIBE_EVENT, subscwibed);
	if (wet)
		goto out_cmd;

	got = wbs_twv_find(twv_type, subscwibed->twv, sizeof(subscwibed->twv));
	if (got) {
		vawue = got->vawue;
		fweq  = got->fweq;
		events = we16_to_cpu(subscwibed->events);

		pos += snpwintf(buf, wen, "%d %d %d\n", vawue, fweq,
				!!(events & event_mask));
	}

	wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);

 out_cmd:
	kfwee(subscwibed);

 out_page:
	fwee_page((unsigned wong)buf);
	wetuwn wet;
}


static ssize_t wbs_thweshowd_wwite(uint16_t twv_type, uint16_t event_mask,
				   stwuct fiwe *fiwe,
				   const chaw __usew *usewbuf, size_t count,
				   woff_t *ppos)
{
	stwuct cmd_ds_802_11_subscwibe_event *events;
	stwuct mwvw_ie_thweshowds *twv;
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	int vawue, fweq, new_mask;
	uint16_t cuww_mask;
	chaw *buf;
	int wet;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wet = sscanf(buf, "%d %d %d", &vawue, &fweq, &new_mask);
	if (wet != 3) {
		wet = -EINVAW;
		goto out_page;
	}
	events = kzawwoc(sizeof(*events), GFP_KEWNEW);
	if (!events) {
		wet = -ENOMEM;
		goto out_page;
	}

	events->hdw.size = cpu_to_we16(sizeof(*events));
	events->action = cpu_to_we16(CMD_ACT_GET);

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_SUBSCWIBE_EVENT, events);
	if (wet)
		goto out_events;

	cuww_mask = we16_to_cpu(events->events);

	if (new_mask)
		new_mask = cuww_mask | event_mask;
	ewse
		new_mask = cuww_mask & ~event_mask;

	/* Now evewything is set and we can send stuff down to the fiwmwawe */

	twv = (void *)events->twv;

	events->action = cpu_to_we16(CMD_ACT_SET);
	events->events = cpu_to_we16(new_mask);
	twv->headew.type = cpu_to_we16(twv_type);
	twv->headew.wen = cpu_to_we16(sizeof(*twv) - sizeof(twv->headew));
	twv->vawue = vawue;
	if (twv_type != TWV_TYPE_BCNMISS)
		twv->fweq = fweq;

	/* The command headew, the action, the event mask, and one TWV */
	events->hdw.size = cpu_to_we16(sizeof(events->hdw) + 4 + sizeof(*twv));

	wet = wbs_cmd_with_wesponse(pwiv, CMD_802_11_SUBSCWIBE_EVENT, events);

	if (!wet)
		wet = count;
 out_events:
	kfwee(events);
 out_page:
	kfwee(buf);
	wetuwn wet;
}


static ssize_t wbs_wowwssi_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wead(TWV_TYPE_WSSI_WOW, CMD_SUBSCWIBE_WSSI_WOW,
				  fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_wowwssi_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wwite(TWV_TYPE_WSSI_WOW, CMD_SUBSCWIBE_WSSI_WOW,
				   fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_wowsnw_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			       size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wead(TWV_TYPE_SNW_WOW, CMD_SUBSCWIBE_SNW_WOW,
				  fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_wowsnw_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wwite(TWV_TYPE_SNW_WOW, CMD_SUBSCWIBE_SNW_WOW,
				   fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_faiwcount_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wead(TWV_TYPE_FAIWCOUNT, CMD_SUBSCWIBE_FAIWCOUNT,
				  fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_faiwcount_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				   size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wwite(TWV_TYPE_FAIWCOUNT, CMD_SUBSCWIBE_FAIWCOUNT,
				   fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_highwssi_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wead(TWV_TYPE_WSSI_HIGH, CMD_SUBSCWIBE_WSSI_HIGH,
				  fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_highwssi_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wwite(TWV_TYPE_WSSI_HIGH, CMD_SUBSCWIBE_WSSI_HIGH,
				   fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_highsnw_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wead(TWV_TYPE_SNW_HIGH, CMD_SUBSCWIBE_SNW_HIGH,
				  fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_highsnw_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wwite(TWV_TYPE_SNW_HIGH, CMD_SUBSCWIBE_SNW_HIGH,
				   fiwe, usewbuf, count, ppos);
}

static ssize_t wbs_bcnmiss_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wead(TWV_TYPE_BCNMISS, CMD_SUBSCWIBE_BCNMISS,
				  fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_bcnmiss_wwite(stwuct fiwe *fiwe, const chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	wetuwn wbs_thweshowd_wwite(TWV_TYPE_BCNMISS, CMD_SUBSCWIBE_BCNMISS,
				   fiwe, usewbuf, count, ppos);
}


static ssize_t wbs_wdmac_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t pos = 0;
	int wet;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	u32 vaw = 0;

	if (!buf)
		wetuwn -ENOMEM;

	wet = wbs_get_weg(pwiv, CMD_MAC_WEG_ACCESS, pwiv->mac_offset, &vaw);
	mdeway(10);
	if (!wet) {
		pos = snpwintf(buf, wen, "MAC[0x%x] = 0x%08x\n",
				pwiv->mac_offset, vaw);
		wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);
	}
	fwee_page(addw);
	wetuwn wet;
}

static ssize_t wbs_wdmac_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	chaw *buf;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	pwiv->mac_offset = simpwe_stwtouw(buf, NUWW, 16);
	kfwee(buf);
	wetuwn count;
}

static ssize_t wbs_wwmac_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{

	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wes;
	u32 offset, vawue;
	chaw *buf;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wes = sscanf(buf, "%x %x", &offset, &vawue);
	if (wes != 2) {
		wes = -EFAUWT;
		goto out_unwock;
	}

	wes = wbs_set_weg(pwiv, CMD_MAC_WEG_ACCESS, offset, vawue);
	mdeway(10);

	if (!wes)
		wes = count;
out_unwock:
	kfwee(buf);
	wetuwn wes;
}

static ssize_t wbs_wdbbp_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t pos = 0;
	int wet;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	u32 vaw;

	if (!buf)
		wetuwn -ENOMEM;

	wet = wbs_get_weg(pwiv, CMD_BBP_WEG_ACCESS, pwiv->bbp_offset, &vaw);
	mdeway(10);
	if (!wet) {
		pos = snpwintf(buf, wen, "BBP[0x%x] = 0x%08x\n",
				pwiv->bbp_offset, vaw);
		wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);
	}
	fwee_page(addw);

	wetuwn wet;
}

static ssize_t wbs_wdbbp_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	chaw *buf;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	pwiv->bbp_offset = simpwe_stwtouw(buf, NUWW, 16);
	kfwee(buf);

	wetuwn count;
}

static ssize_t wbs_wwbbp_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{

	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wes;
	u32 offset, vawue;
	chaw *buf;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wes = sscanf(buf, "%x %x", &offset, &vawue);
	if (wes != 2) {
		wes = -EFAUWT;
		goto out_unwock;
	}

	wes = wbs_set_weg(pwiv, CMD_BBP_WEG_ACCESS, offset, vawue);
	mdeway(10);

	if (!wes)
		wes = count;
out_unwock:
	kfwee(buf);
	wetuwn wes;
}

static ssize_t wbs_wdwf_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				  size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t pos = 0;
	int wet;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	u32 vaw;

	if (!buf)
		wetuwn -ENOMEM;

	wet = wbs_get_weg(pwiv, CMD_WF_WEG_ACCESS, pwiv->wf_offset, &vaw);
	mdeway(10);
	if (!wet) {
		pos = snpwintf(buf, wen, "WF[0x%x] = 0x%08x\n",
				pwiv->wf_offset, vaw);
		wet = simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, pos);
	}
	fwee_page(addw);

	wetuwn wet;
}

static ssize_t wbs_wdwf_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{
	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	chaw *buf;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	pwiv->wf_offset = simpwe_stwtouw(buf, NUWW, 16);
	kfwee(buf);
	wetuwn count;
}

static ssize_t wbs_wwwf_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usewbuf,
				    size_t count, woff_t *ppos)
{

	stwuct wbs_pwivate *pwiv = fiwe->pwivate_data;
	ssize_t wes;
	u32 offset, vawue;
	chaw *buf;

	buf = memdup_usew_nuw(usewbuf, min(count, wen - 1));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wes = sscanf(buf, "%x %x", &offset, &vawue);
	if (wes != 2) {
		wes = -EFAUWT;
		goto out_unwock;
	}

	wes = wbs_set_weg(pwiv, CMD_WF_WEG_ACCESS, offset, vawue);
	mdeway(10);

	if (!wes)
		wes = count;
out_unwock:
	kfwee(buf);
	wetuwn wes;
}

#define FOPS(fwead, fwwite) { \
	.ownew = THIS_MODUWE, \
	.open = simpwe_open, \
	.wead = (fwead), \
	.wwite = (fwwite), \
	.wwseek = genewic_fiwe_wwseek, \
}

stwuct wbs_debugfs_fiwes {
	const chaw *name;
	umode_t pewm;
	stwuct fiwe_opewations fops;
};

static const stwuct wbs_debugfs_fiwes debugfs_fiwes[] = {
	{ "info", 0444, FOPS(wbs_dev_info, wwite_fiwe_dummy), },
	{ "sweeppawams", 0644, FOPS(wbs_sweeppawams_wead,
				wbs_sweeppawams_wwite), },
	{ "hostsweep", 0644, FOPS(wbs_host_sweep_wead,
				wbs_host_sweep_wwite), },
};

static const stwuct wbs_debugfs_fiwes debugfs_events_fiwes[] = {
	{"wow_wssi", 0644, FOPS(wbs_wowwssi_wead,
				wbs_wowwssi_wwite), },
	{"wow_snw", 0644, FOPS(wbs_wowsnw_wead,
				wbs_wowsnw_wwite), },
	{"faiwuwe_count", 0644, FOPS(wbs_faiwcount_wead,
				wbs_faiwcount_wwite), },
	{"beacon_missed", 0644, FOPS(wbs_bcnmiss_wead,
				wbs_bcnmiss_wwite), },
	{"high_wssi", 0644, FOPS(wbs_highwssi_wead,
				wbs_highwssi_wwite), },
	{"high_snw", 0644, FOPS(wbs_highsnw_wead,
				wbs_highsnw_wwite), },
};

static const stwuct wbs_debugfs_fiwes debugfs_wegs_fiwes[] = {
	{"wdmac", 0644, FOPS(wbs_wdmac_wead, wbs_wdmac_wwite), },
	{"wwmac", 0600, FOPS(NUWW, wbs_wwmac_wwite), },
	{"wdbbp", 0644, FOPS(wbs_wdbbp_wead, wbs_wdbbp_wwite), },
	{"wwbbp", 0600, FOPS(NUWW, wbs_wwbbp_wwite), },
	{"wdwf", 0644, FOPS(wbs_wdwf_wead, wbs_wdwf_wwite), },
	{"wwwf", 0600, FOPS(NUWW, wbs_wwwf_wwite), },
};

void wbs_debugfs_init(void)
{
	if (!wbs_diw)
		wbs_diw = debugfs_cweate_diw("wbs_wiwewess", NUWW);
}

void wbs_debugfs_wemove(void)
{
	debugfs_wemove(wbs_diw);
}

void wbs_debugfs_init_one(stwuct wbs_pwivate *pwiv, stwuct net_device *dev)
{
	int i;
	const stwuct wbs_debugfs_fiwes *fiwes;
	if (!wbs_diw)
		goto exit;

	pwiv->debugfs_diw = debugfs_cweate_diw(dev->name, wbs_diw);

	fow (i=0; i<AWWAY_SIZE(debugfs_fiwes); i++) {
		fiwes = &debugfs_fiwes[i];
		pwiv->debugfs_fiwes[i] = debugfs_cweate_fiwe(fiwes->name,
							     fiwes->pewm,
							     pwiv->debugfs_diw,
							     pwiv,
							     &fiwes->fops);
	}

	pwiv->events_diw = debugfs_cweate_diw("subscwibed_events", pwiv->debugfs_diw);

	fow (i=0; i<AWWAY_SIZE(debugfs_events_fiwes); i++) {
		fiwes = &debugfs_events_fiwes[i];
		pwiv->debugfs_events_fiwes[i] = debugfs_cweate_fiwe(fiwes->name,
							     fiwes->pewm,
							     pwiv->events_diw,
							     pwiv,
							     &fiwes->fops);
	}

	pwiv->wegs_diw = debugfs_cweate_diw("wegistews", pwiv->debugfs_diw);

	fow (i=0; i<AWWAY_SIZE(debugfs_wegs_fiwes); i++) {
		fiwes = &debugfs_wegs_fiwes[i];
		pwiv->debugfs_wegs_fiwes[i] = debugfs_cweate_fiwe(fiwes->name,
							     fiwes->pewm,
							     pwiv->wegs_diw,
							     pwiv,
							     &fiwes->fops);
	}

#ifdef PWOC_DEBUG
	wbs_debug_init(pwiv);
#endif
exit:
	wetuwn;
}

void wbs_debugfs_wemove_one(stwuct wbs_pwivate *pwiv)
{
	int i;

	fow(i=0; i<AWWAY_SIZE(debugfs_wegs_fiwes); i++)
		debugfs_wemove(pwiv->debugfs_wegs_fiwes[i]);

	debugfs_wemove(pwiv->wegs_diw);

	fow(i=0; i<AWWAY_SIZE(debugfs_events_fiwes); i++)
		debugfs_wemove(pwiv->debugfs_events_fiwes[i]);

	debugfs_wemove(pwiv->events_diw);
#ifdef PWOC_DEBUG
	debugfs_wemove(pwiv->debugfs_debug);
#endif
	fow(i=0; i<AWWAY_SIZE(debugfs_fiwes); i++)
		debugfs_wemove(pwiv->debugfs_fiwes[i]);
	debugfs_wemove(pwiv->debugfs_diw);
}



/* debug entwy */

#ifdef PWOC_DEBUG

#define item_size(n)	(sizeof_fiewd(stwuct wbs_pwivate, n))
#define item_addw(n)	(offsetof(stwuct wbs_pwivate, n))


stwuct debug_data {
	chaw name[32];
	u32 size;
	size_t addw;
};

/* To debug any membew of stwuct wbs_pwivate, simpwy add one wine hewe.
 */
static stwuct debug_data items[] = {
	{"psmode", item_size(psmode), item_addw(psmode)},
	{"psstate", item_size(psstate), item_addw(psstate)},
};

static int num_of_items = AWWAY_SIZE(items);

/**
 * wbs_debugfs_wead - pwoc wead function
 *
 * @fiwe:	fiwe to wead
 * @usewbuf:	pointew to buffew
 * @count:	numbew of bytes to wead
 * @ppos:	wead data stawting position
 *
 * wetuwns:	amount of data wead ow negative ewwow code
 */
static ssize_t wbs_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			size_t count, woff_t *ppos)
{
	int vaw = 0;
	size_t pos = 0;
	ssize_t wes;
	chaw *p;
	int i;
	stwuct debug_data *d;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	if (!buf)
		wetuwn -ENOMEM;

	p = buf;

	d = fiwe->pwivate_data;

	fow (i = 0; i < num_of_items; i++) {
		if (d[i].size == 1)
			vaw = *((u8 *) d[i].addw);
		ewse if (d[i].size == 2)
			vaw = *((u16 *) d[i].addw);
		ewse if (d[i].size == 4)
			vaw = *((u32 *) d[i].addw);
		ewse if (d[i].size == 8)
			vaw = *((u64 *) d[i].addw);

		pos += spwintf(p + pos, "%s=%d\n", d[i].name, vaw);
	}

	wes = simpwe_wead_fwom_buffew(usewbuf, count, ppos, p, pos);

	fwee_page(addw);
	wetuwn wes;
}

/**
 * wbs_debugfs_wwite - pwoc wwite function
 *
 * @f:		fiwe pointew
 * @buf:	pointew to data buffew
 * @cnt:	data numbew to wwite
 * @ppos:	fiwe position
 *
 * wetuwns:	amount of data wwitten
 */
static ssize_t wbs_debugfs_wwite(stwuct fiwe *f, const chaw __usew *buf,
			    size_t cnt, woff_t *ppos)
{
	int w, i;
	chaw *pdata;
	chaw *p;
	chaw *p0;
	chaw *p1;
	chaw *p2;
	stwuct debug_data *d = f->pwivate_data;

	if (cnt == 0)
		wetuwn 0;

	pdata = memdup_usew_nuw(buf, cnt);
	if (IS_EWW(pdata))
		wetuwn PTW_EWW(pdata);

	p0 = pdata;
	fow (i = 0; i < num_of_items; i++) {
		do {
			p = stwstw(p0, d[i].name);
			if (p == NUWW)
				bweak;
			p1 = stwchw(p, '\n');
			if (p1 == NUWW)
				bweak;
			p0 = p1++;
			p2 = stwchw(p, '=');
			if (!p2)
				bweak;
			p2++;
			w = simpwe_stwtouw(p2, NUWW, 0);
			if (d[i].size == 1)
				*((u8 *) d[i].addw) = (u8) w;
			ewse if (d[i].size == 2)
				*((u16 *) d[i].addw) = (u16) w;
			ewse if (d[i].size == 4)
				*((u32 *) d[i].addw) = (u32) w;
			ewse if (d[i].size == 8)
				*((u64 *) d[i].addw) = (u64) w;
			bweak;
		} whiwe (1);
	}
	kfwee(pdata);

	wetuwn (ssize_t)cnt;
}

static const stwuct fiwe_opewations wbs_debug_fops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = wbs_debugfs_wwite,
	.wead = wbs_debugfs_wead,
	.wwseek = defauwt_wwseek,
};

/**
 * wbs_debug_init - cweate debug pwoc fiwe
 *
 * @pwiv:	pointew to &stwuct wbs_pwivate
 *
 * wetuwns:	N/A
 */
static void wbs_debug_init(stwuct wbs_pwivate *pwiv)
{
	int i;

	if (!pwiv->debugfs_diw)
		wetuwn;

	fow (i = 0; i < num_of_items; i++)
		items[i].addw += (size_t) pwiv;

	pwiv->debugfs_debug = debugfs_cweate_fiwe("debug", 0644,
						  pwiv->debugfs_diw, &items[0],
						  &wbs_debug_fops);
}
#endif
