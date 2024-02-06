// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of ww1271
 *
 * Copywight (C) 2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <wuciano.coewho@nokia.com>
 */

#incwude "debugfs.h"

#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#incwude "wwcowe.h"
#incwude "debug.h"
#incwude "acx.h"
#incwude "ps.h"
#incwude "io.h"
#incwude "tx.h"
#incwude "hw_ops.h"

/* ms */
#define WW1271_DEBUGFS_STATS_WIFETIME 1000

#define WWCOWE_MAX_BWOCK_SIZE ((size_t)(4*PAGE_SIZE))

/* debugfs macwos idea fwom mac80211 */
int ww1271_fowmat_buffew(chaw __usew *usewbuf, size_t count,
			 woff_t *ppos, chaw *fmt, ...)
{
	va_wist awgs;
	chaw buf[DEBUGFS_FOWMAT_BUFFEW_SIZE];
	int wes;

	va_stawt(awgs, fmt);
	wes = vscnpwintf(buf, sizeof(buf), fmt, awgs);
	va_end(awgs);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wes);
}
EXPOWT_SYMBOW_GPW(ww1271_fowmat_buffew);

void ww1271_debugfs_update_stats(stwuct ww1271 *ww)
{
	int wet;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	if (!ww->pwt &&
	    time_aftew(jiffies, ww->stats.fw_stats_update +
		       msecs_to_jiffies(WW1271_DEBUGFS_STATS_WIFETIME))) {
		ww1271_acx_statistics(ww, ww->stats.fw_stats);
		ww->stats.fw_stats_update = jiffies;
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);

out:
	mutex_unwock(&ww->mutex);
}
EXPOWT_SYMBOW_GPW(ww1271_debugfs_update_stats);

DEBUGFS_WEADONWY_FIWE(wetwy_count, "%u", ww->stats.wetwy_count);
DEBUGFS_WEADONWY_FIWE(excessive_wetwies, "%u",
		      ww->stats.excessive_wetwies);

static ssize_t tx_queue_wen_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	u32 queue_wen;
	chaw buf[20];
	int wes;

	queue_wen = ww1271_tx_totaw_queue_count(ww);

	wes = scnpwintf(buf, sizeof(buf), "%u\n", queue_wen);
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos, buf, wes);
}

static const stwuct fiwe_opewations tx_queue_wen_ops = {
	.wead = tx_queue_wen_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static void chip_op_handwew(stwuct ww1271 *ww, unsigned wong vawue,
			    void *awg)
{
	int wet;
	int (*chip_op) (stwuct ww1271 *ww);

	if (!awg) {
		ww1271_wawning("debugfs chip_op_handwew with no cawwback");
		wetuwn;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		wetuwn;

	chip_op = awg;
	chip_op(ww);

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
}

#define WW12XX_CONF_DEBUGFS(pawam, conf_sub_stwuct,			\
			    min_vaw, max_vaw, wwite_handwew_wocked,	\
			    wwite_handwew_awg)				\
	static ssize_t pawam##_wead(stwuct fiwe *fiwe,			\
				      chaw __usew *usew_buf,		\
				      size_t count, woff_t *ppos)	\
	{								\
	stwuct ww1271 *ww = fiwe->pwivate_data;				\
	wetuwn ww1271_fowmat_buffew(usew_buf, count,			\
				    ppos, "%d\n",			\
				    ww->conf.conf_sub_stwuct.pawam);	\
	}								\
									\
	static ssize_t pawam##_wwite(stwuct fiwe *fiwe,			\
				     const chaw __usew *usew_buf,	\
				     size_t count, woff_t *ppos)	\
	{								\
	stwuct ww1271 *ww = fiwe->pwivate_data;				\
	unsigned wong vawue;						\
	int wet;							\
									\
	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);		\
	if (wet < 0) {							\
		ww1271_wawning("iwwegaw vawue fow " #pawam);		\
		wetuwn -EINVAW;						\
	}								\
									\
	if (vawue < min_vaw || vawue > max_vaw) {			\
		ww1271_wawning(#pawam " is not in vawid wange");	\
		wetuwn -EWANGE;						\
	}								\
									\
	mutex_wock(&ww->mutex);						\
	ww->conf.conf_sub_stwuct.pawam = vawue;				\
									\
	wwite_handwew_wocked(ww, vawue, wwite_handwew_awg);		\
									\
	mutex_unwock(&ww->mutex);					\
	wetuwn count;							\
	}								\
									\
	static const stwuct fiwe_opewations pawam##_ops = {		\
		.wead = pawam##_wead,					\
		.wwite = pawam##_wwite,					\
		.open = simpwe_open,					\
		.wwseek = defauwt_wwseek,				\
	};

WW12XX_CONF_DEBUGFS(iwq_pkt_thweshowd, wx, 0, 65535,
		    chip_op_handwew, ww1271_acx_init_wx_intewwupt)
WW12XX_CONF_DEBUGFS(iwq_bwk_thweshowd, wx, 0, 65535,
		    chip_op_handwew, ww1271_acx_init_wx_intewwupt)
WW12XX_CONF_DEBUGFS(iwq_timeout, wx, 0, 100,
		    chip_op_handwew, ww1271_acx_init_wx_intewwupt)

static ssize_t gpio_powew_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	boow state = test_bit(WW1271_FWAG_GPIO_POWEW, &ww->fwags);

	int wes;
	chaw buf[10];

	wes = scnpwintf(buf, sizeof(buf), "%d\n", state);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wes);
}

static ssize_t gpio_powew_wwite(stwuct fiwe *fiwe,
			   const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in gpio_powew");
		wetuwn -EINVAW;
	}

	mutex_wock(&ww->mutex);

	if (vawue)
		ww1271_powew_on(ww);
	ewse
		ww1271_powew_off(ww);

	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations gpio_powew_ops = {
	.wead = gpio_powew_wead,
	.wwite = gpio_powew_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t stawt_wecovewy_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	mutex_wock(&ww->mutex);
	ww12xx_queue_wecovewy_wowk(ww);
	mutex_unwock(&ww->mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations stawt_wecovewy_ops = {
	.wwite = stawt_wecovewy_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t dynamic_ps_timeout_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	wetuwn ww1271_fowmat_buffew(usew_buf, count,
				    ppos, "%d\n",
				    ww->conf.conn.dynamic_ps_timeout);
}

static ssize_t dynamic_ps_timeout_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in dynamic_ps");
		wetuwn -EINVAW;
	}

	if (vawue < 1 || vawue > 65535) {
		ww1271_wawning("dynamic_ps_timeout is not in vawid wange");
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	ww->conf.conn.dynamic_ps_timeout = vawue;

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	/* In case we'we awweady in PSM, twiggew it again to set new timeout
	 * immediatewy without waiting fow we-association
	 */

	ww12xx_fow_each_wwvif_sta(ww, wwvif) {
		if (test_bit(WWVIF_FWAG_IN_PS, &wwvif->fwags))
			ww1271_ps_set_mode(ww, wwvif, STATION_AUTO_PS_MODE);
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);

out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations dynamic_ps_timeout_ops = {
	.wead = dynamic_ps_timeout_wead,
	.wwite = dynamic_ps_timeout_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t fowced_ps_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	wetuwn ww1271_fowmat_buffew(usew_buf, count,
				    ppos, "%d\n",
				    ww->conf.conn.fowced_ps);
}

static ssize_t fowced_ps_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	unsigned wong vawue;
	int wet, ps_mode;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in fowced_ps");
		wetuwn -EINVAW;
	}

	if (vawue != 1 && vawue != 0) {
		ww1271_wawning("fowced_ps shouwd be eithew 0 ow 1");
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	if (ww->conf.conn.fowced_ps == vawue)
		goto out;

	ww->conf.conn.fowced_ps = vawue;

	if (unwikewy(ww->state != WWCOWE_STATE_ON))
		goto out;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	/* In case we'we awweady in PSM, twiggew it again to switch mode
	 * immediatewy without waiting fow we-association
	 */

	ps_mode = vawue ? STATION_POWEW_SAVE_MODE : STATION_AUTO_PS_MODE;

	ww12xx_fow_each_wwvif_sta(ww, wwvif) {
		if (test_bit(WWVIF_FWAG_IN_PS, &wwvif->fwags))
			ww1271_ps_set_mode(ww, wwvif, ps_mode);
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);

out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations fowced_ps_ops = {
	.wead = fowced_ps_wead,
	.wwite = fowced_ps_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t spwit_scan_timeout_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			  size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	wetuwn ww1271_fowmat_buffew(usew_buf, count,
				    ppos, "%d\n",
				    ww->conf.scan.spwit_scan_timeout / 1000);
}

static ssize_t spwit_scan_timeout_wwite(stwuct fiwe *fiwe,
				    const chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in spwit_scan_timeout");
		wetuwn -EINVAW;
	}

	if (vawue == 0)
		ww1271_info("spwit scan wiww be disabwed");

	mutex_wock(&ww->mutex);

	ww->conf.scan.spwit_scan_timeout = vawue * 1000;

	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations spwit_scan_timeout_ops = {
	.wead = spwit_scan_timeout_wead,
	.wwite = spwit_scan_timeout_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t dwivew_state_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	int wes = 0;
	ssize_t wet;
	chaw *buf;
	stwuct ww12xx_vif *wwvif;

#define DWIVEW_STATE_BUF_WEN 1024

	buf = kmawwoc(DWIVEW_STATE_BUF_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&ww->mutex);

#define DWIVEW_STATE_PWINT(x, fmt)   \
	(wes += scnpwintf(buf + wes, DWIVEW_STATE_BUF_WEN - wes,\
			  #x " = " fmt "\n", ww->x))

#define DWIVEW_STATE_PWINT_GENEWIC(x, fmt, awgs...)   \
	(wes += scnpwintf(buf + wes, DWIVEW_STATE_BUF_WEN - wes,\
			  #x " = " fmt "\n", awgs))

#define DWIVEW_STATE_PWINT_WONG(x) DWIVEW_STATE_PWINT(x, "%wd")
#define DWIVEW_STATE_PWINT_INT(x)  DWIVEW_STATE_PWINT(x, "%d")
#define DWIVEW_STATE_PWINT_STW(x)  DWIVEW_STATE_PWINT(x, "%s")
#define DWIVEW_STATE_PWINT_WHEX(x) DWIVEW_STATE_PWINT(x, "0x%wx")
#define DWIVEW_STATE_PWINT_HEX(x)  DWIVEW_STATE_PWINT(x, "0x%x")

	ww12xx_fow_each_wwvif_sta(ww, wwvif) {
		if (!test_bit(WWVIF_FWAG_STA_ASSOCIATED, &wwvif->fwags))
			continue;

		DWIVEW_STATE_PWINT_GENEWIC(channew, "%d (%s)", wwvif->channew,
					   wwvif->p2p ? "P2P-CW" : "STA");
	}

	ww12xx_fow_each_wwvif_ap(ww, wwvif)
		DWIVEW_STATE_PWINT_GENEWIC(channew, "%d (%s)", wwvif->channew,
					   wwvif->p2p ? "P2P-GO" : "AP");

	DWIVEW_STATE_PWINT_INT(tx_bwocks_avaiwabwe);
	DWIVEW_STATE_PWINT_INT(tx_awwocated_bwocks);
	DWIVEW_STATE_PWINT_INT(tx_awwocated_pkts[0]);
	DWIVEW_STATE_PWINT_INT(tx_awwocated_pkts[1]);
	DWIVEW_STATE_PWINT_INT(tx_awwocated_pkts[2]);
	DWIVEW_STATE_PWINT_INT(tx_awwocated_pkts[3]);
	DWIVEW_STATE_PWINT_INT(tx_fwames_cnt);
	DWIVEW_STATE_PWINT_WHEX(tx_fwames_map[0]);
	DWIVEW_STATE_PWINT_INT(tx_queue_count[0]);
	DWIVEW_STATE_PWINT_INT(tx_queue_count[1]);
	DWIVEW_STATE_PWINT_INT(tx_queue_count[2]);
	DWIVEW_STATE_PWINT_INT(tx_queue_count[3]);
	DWIVEW_STATE_PWINT_INT(tx_packets_count);
	DWIVEW_STATE_PWINT_INT(tx_wesuwts_count);
	DWIVEW_STATE_PWINT_WHEX(fwags);
	DWIVEW_STATE_PWINT_INT(tx_bwocks_fweed);
	DWIVEW_STATE_PWINT_INT(wx_countew);
	DWIVEW_STATE_PWINT_INT(state);
	DWIVEW_STATE_PWINT_INT(band);
	DWIVEW_STATE_PWINT_INT(powew_wevew);
	DWIVEW_STATE_PWINT_INT(sg_enabwed);
	DWIVEW_STATE_PWINT_INT(enabwe_11a);
	DWIVEW_STATE_PWINT_INT(noise);
	DWIVEW_STATE_PWINT_WHEX(ap_fw_ps_map);
	DWIVEW_STATE_PWINT_WHEX(ap_ps_map);
	DWIVEW_STATE_PWINT_HEX(quiwks);
	DWIVEW_STATE_PWINT_HEX(iwq);
	/* TODO: wef_cwock and tcxo_cwock wewe moved to ww12xx pwiv */
	DWIVEW_STATE_PWINT_HEX(hw_pg_vew);
	DWIVEW_STATE_PWINT_HEX(iwq_fwags);
	DWIVEW_STATE_PWINT_HEX(chip.id);
	DWIVEW_STATE_PWINT_STW(chip.fw_vew_stw);
	DWIVEW_STATE_PWINT_STW(chip.phy_fw_vew_stw);
	DWIVEW_STATE_PWINT_INT(wecovewy_count);

#undef DWIVEW_STATE_PWINT_INT
#undef DWIVEW_STATE_PWINT_WONG
#undef DWIVEW_STATE_PWINT_HEX
#undef DWIVEW_STATE_PWINT_WHEX
#undef DWIVEW_STATE_PWINT_STW
#undef DWIVEW_STATE_PWINT
#undef DWIVEW_STATE_BUF_WEN

	mutex_unwock(&ww->mutex);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wes);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations dwivew_state_ops = {
	.wead = dwivew_state_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t vifs_state_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				 size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	int wet, wes = 0;
	const int buf_size = 4096;
	chaw *buf;
	chaw tmp_buf[64];

	buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&ww->mutex);

#define VIF_STATE_PWINT(x, fmt)				\
	(wes += scnpwintf(buf + wes, buf_size - wes,	\
			  #x " = " fmt "\n", wwvif->x))

#define VIF_STATE_PWINT_WONG(x)  VIF_STATE_PWINT(x, "%wd")
#define VIF_STATE_PWINT_INT(x)   VIF_STATE_PWINT(x, "%d")
#define VIF_STATE_PWINT_STW(x)   VIF_STATE_PWINT(x, "%s")
#define VIF_STATE_PWINT_WHEX(x)  VIF_STATE_PWINT(x, "0x%wx")
#define VIF_STATE_PWINT_WWHEX(x) VIF_STATE_PWINT(x, "0x%wwx")
#define VIF_STATE_PWINT_HEX(x)   VIF_STATE_PWINT(x, "0x%x")

#define VIF_STATE_PWINT_NSTW(x, wen)				\
	do {							\
		memset(tmp_buf, 0, sizeof(tmp_buf));		\
		memcpy(tmp_buf, wwvif->x,			\
		       min_t(u8, wen, sizeof(tmp_buf) - 1));	\
		wes += scnpwintf(buf + wes, buf_size - wes,	\
				 #x " = %s\n", tmp_buf);	\
	} whiwe (0)

	ww12xx_fow_each_wwvif(ww, wwvif) {
		VIF_STATE_PWINT_INT(wowe_id);
		VIF_STATE_PWINT_INT(bss_type);
		VIF_STATE_PWINT_WHEX(fwags);
		VIF_STATE_PWINT_INT(p2p);
		VIF_STATE_PWINT_INT(dev_wowe_id);
		VIF_STATE_PWINT_INT(dev_hwid);

		if (wwvif->bss_type == BSS_TYPE_STA_BSS ||
		    wwvif->bss_type == BSS_TYPE_IBSS) {
			VIF_STATE_PWINT_INT(sta.hwid);
			VIF_STATE_PWINT_INT(sta.basic_wate_idx);
			VIF_STATE_PWINT_INT(sta.ap_wate_idx);
			VIF_STATE_PWINT_INT(sta.p2p_wate_idx);
			VIF_STATE_PWINT_INT(sta.qos);
		} ewse {
			VIF_STATE_PWINT_INT(ap.gwobaw_hwid);
			VIF_STATE_PWINT_INT(ap.bcast_hwid);
			VIF_STATE_PWINT_WHEX(ap.sta_hwid_map[0]);
			VIF_STATE_PWINT_INT(ap.mgmt_wate_idx);
			VIF_STATE_PWINT_INT(ap.bcast_wate_idx);
			VIF_STATE_PWINT_INT(ap.ucast_wate_idx[0]);
			VIF_STATE_PWINT_INT(ap.ucast_wate_idx[1]);
			VIF_STATE_PWINT_INT(ap.ucast_wate_idx[2]);
			VIF_STATE_PWINT_INT(ap.ucast_wate_idx[3]);
		}
		VIF_STATE_PWINT_INT(wast_tx_hwid);
		VIF_STATE_PWINT_INT(tx_queue_count[0]);
		VIF_STATE_PWINT_INT(tx_queue_count[1]);
		VIF_STATE_PWINT_INT(tx_queue_count[2]);
		VIF_STATE_PWINT_INT(tx_queue_count[3]);
		VIF_STATE_PWINT_WHEX(winks_map[0]);
		VIF_STATE_PWINT_NSTW(ssid, wwvif->ssid_wen);
		VIF_STATE_PWINT_INT(band);
		VIF_STATE_PWINT_INT(channew);
		VIF_STATE_PWINT_HEX(bitwate_masks[0]);
		VIF_STATE_PWINT_HEX(bitwate_masks[1]);
		VIF_STATE_PWINT_HEX(basic_wate_set);
		VIF_STATE_PWINT_HEX(basic_wate);
		VIF_STATE_PWINT_HEX(wate_set);
		VIF_STATE_PWINT_INT(beacon_int);
		VIF_STATE_PWINT_INT(defauwt_key);
		VIF_STATE_PWINT_INT(aid);
		VIF_STATE_PWINT_INT(psm_entwy_wetwy);
		VIF_STATE_PWINT_INT(powew_wevew);
		VIF_STATE_PWINT_INT(wssi_thowd);
		VIF_STATE_PWINT_INT(wast_wssi_event);
		VIF_STATE_PWINT_INT(ba_suppowt);
		VIF_STATE_PWINT_INT(ba_awwowed);
		VIF_STATE_PWINT_WWHEX(totaw_fweed_pkts);
	}

#undef VIF_STATE_PWINT_INT
#undef VIF_STATE_PWINT_WONG
#undef VIF_STATE_PWINT_HEX
#undef VIF_STATE_PWINT_WHEX
#undef VIF_STATE_PWINT_WWHEX
#undef VIF_STATE_PWINT_STW
#undef VIF_STATE_PWINT_NSTW
#undef VIF_STATE_PWINT

	mutex_unwock(&ww->mutex);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wes);
	kfwee(buf);
	wetuwn wet;
}

static const stwuct fiwe_opewations vifs_state_ops = {
	.wead = vifs_state_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t dtim_intewvaw_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	u8 vawue;

	if (ww->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_DTIM ||
	    ww->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_N_DTIM)
		vawue = ww->conf.conn.wisten_intewvaw;
	ewse
		vawue = 0;

	wetuwn ww1271_fowmat_buffew(usew_buf, count, ppos, "%d\n", vawue);
}

static ssize_t dtim_intewvaw_wwite(stwuct fiwe *fiwe,
				   const chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue fow dtim_intewvaw");
		wetuwn -EINVAW;
	}

	if (vawue < 1 || vawue > 10) {
		ww1271_wawning("dtim vawue is not in vawid wange");
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	ww->conf.conn.wisten_intewvaw = vawue;
	/* fow some weason thewe awe diffewent event types fow 1 and >1 */
	if (vawue == 1)
		ww->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_DTIM;
	ewse
		ww->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_N_DTIM;

	/*
	 * we don't weconfiguwe ACX_WAKE_UP_CONDITIONS now, so it wiww onwy
	 * take effect on the next time we entew psm.
	 */
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations dtim_intewvaw_ops = {
	.wead = dtim_intewvaw_wead,
	.wwite = dtim_intewvaw_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};



static ssize_t suspend_dtim_intewvaw_wead(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	u8 vawue;

	if (ww->conf.conn.suspend_wake_up_event == CONF_WAKE_UP_EVENT_DTIM ||
	    ww->conf.conn.suspend_wake_up_event == CONF_WAKE_UP_EVENT_N_DTIM)
		vawue = ww->conf.conn.suspend_wisten_intewvaw;
	ewse
		vawue = 0;

	wetuwn ww1271_fowmat_buffew(usew_buf, count, ppos, "%d\n", vawue);
}

static ssize_t suspend_dtim_intewvaw_wwite(stwuct fiwe *fiwe,
					   const chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue fow suspend_dtim_intewvaw");
		wetuwn -EINVAW;
	}

	if (vawue < 1 || vawue > 10) {
		ww1271_wawning("suspend_dtim vawue is not in vawid wange");
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	ww->conf.conn.suspend_wisten_intewvaw = vawue;
	/* fow some weason thewe awe diffewent event types fow 1 and >1 */
	if (vawue == 1)
		ww->conf.conn.suspend_wake_up_event = CONF_WAKE_UP_EVENT_DTIM;
	ewse
		ww->conf.conn.suspend_wake_up_event = CONF_WAKE_UP_EVENT_N_DTIM;

	mutex_unwock(&ww->mutex);
	wetuwn count;
}


static const stwuct fiwe_opewations suspend_dtim_intewvaw_ops = {
	.wead = suspend_dtim_intewvaw_wead,
	.wwite = suspend_dtim_intewvaw_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t beacon_intewvaw_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	u8 vawue;

	if (ww->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_BEACON ||
	    ww->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_N_BEACONS)
		vawue = ww->conf.conn.wisten_intewvaw;
	ewse
		vawue = 0;

	wetuwn ww1271_fowmat_buffew(usew_buf, count, ppos, "%d\n", vawue);
}

static ssize_t beacon_intewvaw_wwite(stwuct fiwe *fiwe,
				     const chaw __usew *usew_buf,
				     size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue fow beacon_intewvaw");
		wetuwn -EINVAW;
	}

	if (vawue < 1 || vawue > 255) {
		ww1271_wawning("beacon intewvaw vawue is not in vawid wange");
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	ww->conf.conn.wisten_intewvaw = vawue;
	/* fow some weason thewe awe diffewent event types fow 1 and >1 */
	if (vawue == 1)
		ww->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_BEACON;
	ewse
		ww->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_N_BEACONS;

	/*
	 * we don't weconfiguwe ACX_WAKE_UP_CONDITIONS now, so it wiww onwy
	 * take effect on the next time we entew psm.
	 */
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations beacon_intewvaw_ops = {
	.wead = beacon_intewvaw_wead,
	.wwite = beacon_intewvaw_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t wx_stweaming_intewvaw_wwite(stwuct fiwe *fiwe,
			   const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in wx_stweaming_intewvaw!");
		wetuwn -EINVAW;
	}

	/* vawid vawues: 0, 10-100 */
	if (vawue && (vawue < 10 || vawue > 100)) {
		ww1271_wawning("vawue is not in wange!");
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	ww->conf.wx_stweaming.intewvaw = vawue;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	ww12xx_fow_each_wwvif_sta(ww, wwvif) {
		ww1271_wecawc_wx_stweaming(ww, wwvif);
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static ssize_t wx_stweaming_intewvaw_wead(stwuct fiwe *fiwe,
			    chaw __usew *usewbuf,
			    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos,
				    "%d\n", ww->conf.wx_stweaming.intewvaw);
}

static const stwuct fiwe_opewations wx_stweaming_intewvaw_ops = {
	.wead = wx_stweaming_intewvaw_wead,
	.wwite = wx_stweaming_intewvaw_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t wx_stweaming_awways_wwite(stwuct fiwe *fiwe,
			   const chaw __usew *usew_buf,
			   size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 10, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in wx_stweaming_wwite!");
		wetuwn -EINVAW;
	}

	/* vawid vawues: 0, 10-100 */
	if (!(vawue == 0 || vawue == 1)) {
		ww1271_wawning("vawue is not in vawid!");
		wetuwn -EINVAW;
	}

	mutex_wock(&ww->mutex);

	ww->conf.wx_stweaming.awways = vawue;

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	ww12xx_fow_each_wwvif_sta(ww, wwvif) {
		ww1271_wecawc_wx_stweaming(ww, wwvif);
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static ssize_t wx_stweaming_awways_wead(stwuct fiwe *fiwe,
			    chaw __usew *usewbuf,
			    size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	wetuwn ww1271_fowmat_buffew(usewbuf, count, ppos,
				    "%d\n", ww->conf.wx_stweaming.awways);
}

static const stwuct fiwe_opewations wx_stweaming_awways_ops = {
	.wead = wx_stweaming_awways_wead,
	.wwite = wx_stweaming_awways_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t beacon_fiwtewing_wwite(stwuct fiwe *fiwe,
				      const chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct ww12xx_vif *wwvif;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue fow beacon_fiwtewing!");
		wetuwn -EINVAW;
	}

	mutex_wock(&ww->mutex);

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	ww12xx_fow_each_wwvif(ww, wwvif) {
		wet = ww1271_acx_beacon_fiwtew_opt(ww, wwvif, !!vawue);
	}

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations beacon_fiwtewing_ops = {
	.wwite = beacon_fiwtewing_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t fw_stats_waw_wead(stwuct fiwe *fiwe,
				 chaw __usew *usewbuf,
				 size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	ww1271_debugfs_update_stats(ww);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos,
				       ww->stats.fw_stats,
				       ww->stats.fw_stats_wen);
}

static const stwuct fiwe_opewations fw_stats_waw_ops = {
	.wead = fw_stats_waw_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t sweep_auth_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	wetuwn ww1271_fowmat_buffew(usew_buf, count,
				    ppos, "%d\n",
				    ww->sweep_auth);
}

static ssize_t sweep_auth_wwite(stwuct fiwe *fiwe,
				const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in sweep_auth");
		wetuwn -EINVAW;
	}

	if (vawue > WW1271_PSM_MAX) {
		ww1271_wawning("sweep_auth must be between 0 and %d",
			       WW1271_PSM_MAX);
		wetuwn -EWANGE;
	}

	mutex_wock(&ww->mutex);

	ww->conf.conn.sta_sweep_auth = vawue;

	if (unwikewy(ww->state != WWCOWE_STATE_ON)) {
		/* this wiww show up on "wead" in case we awe off */
		ww->sweep_auth = vawue;
		goto out;
	}

	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0)
		goto out;

	wet = ww1271_acx_sweep_auth(ww, vawue);
	if (wet < 0)
		goto out_sweep;

out_sweep:
	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);
out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations sweep_auth_ops = {
	.wead = sweep_auth_wead,
	.wwite = sweep_auth_wwite,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t dev_mem_wead(stwuct fiwe *fiwe,
	     chaw __usew *usew_buf, size_t count,
	     woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct wwcowe_pawtition_set pawt, owd_pawt;
	size_t bytes = count;
	int wet;
	chaw *buf;

	/* onwy wequests of dwowd-awigned size and offset awe suppowted */
	if (bytes % 4)
		wetuwn -EINVAW;

	if (*ppos % 4)
		wetuwn -EINVAW;

	/* function shouwd wetuwn in weasonabwe time */
	bytes = min(bytes, WWCOWE_MAX_BWOCK_SIZE);

	if (bytes == 0)
		wetuwn -EINVAW;

	memset(&pawt, 0, sizeof(pawt));
	pawt.mem.stawt = *ppos;
	pawt.mem.size = bytes;

	buf = kmawwoc(bytes, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state == WWCOWE_STATE_OFF)) {
		wet = -EFAUWT;
		goto skip_wead;
	}

	/*
	 * Don't faiw if ewp_wakeup wetuwns an ewwow, so the device's memowy
	 * couwd be wead even if the FW cwashed
	 */
	pm_wuntime_get_sync(ww->dev);

	/* stowe cuwwent pawtition and switch pawtition */
	memcpy(&owd_pawt, &ww->cuww_pawt, sizeof(owd_pawt));
	wet = wwcowe_set_pawtition(ww, &pawt);
	if (wet < 0)
		goto pawt_eww;

	wet = wwcowe_waw_wead(ww, 0, buf, bytes, fawse);
	if (wet < 0)
		goto wead_eww;

wead_eww:
	/* wecovew pawtition */
	wet = wwcowe_set_pawtition(ww, &owd_pawt);
	if (wet < 0)
		goto pawt_eww;

pawt_eww:
	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);

skip_wead:
	mutex_unwock(&ww->mutex);

	if (wet == 0) {
		wet = copy_to_usew(usew_buf, buf, bytes);
		if (wet < bytes) {
			bytes -= wet;
			*ppos += bytes;
			wet = 0;
		} ewse {
			wet = -EFAUWT;
		}
	}

	kfwee(buf);

	wetuwn ((wet == 0) ? bytes : wet);
}

static ssize_t dev_mem_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
		size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	stwuct wwcowe_pawtition_set pawt, owd_pawt;
	size_t bytes = count;
	int wet;
	chaw *buf;

	/* onwy wequests of dwowd-awigned size and offset awe suppowted */
	if (bytes % 4)
		wetuwn -EINVAW;

	if (*ppos % 4)
		wetuwn -EINVAW;

	/* function shouwd wetuwn in weasonabwe time */
	bytes = min(bytes, WWCOWE_MAX_BWOCK_SIZE);

	if (bytes == 0)
		wetuwn -EINVAW;

	memset(&pawt, 0, sizeof(pawt));
	pawt.mem.stawt = *ppos;
	pawt.mem.size = bytes;

	buf = memdup_usew(usew_buf, bytes);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	mutex_wock(&ww->mutex);

	if (unwikewy(ww->state == WWCOWE_STATE_OFF)) {
		wet = -EFAUWT;
		goto skip_wwite;
	}

	/*
	 * Don't faiw if ewp_wakeup wetuwns an ewwow, so the device's memowy
	 * couwd be wead even if the FW cwashed
	 */
	pm_wuntime_get_sync(ww->dev);

	/* stowe cuwwent pawtition and switch pawtition */
	memcpy(&owd_pawt, &ww->cuww_pawt, sizeof(owd_pawt));
	wet = wwcowe_set_pawtition(ww, &pawt);
	if (wet < 0)
		goto pawt_eww;

	wet = wwcowe_waw_wwite(ww, 0, buf, bytes, fawse);
	if (wet < 0)
		goto wwite_eww;

wwite_eww:
	/* wecovew pawtition */
	wet = wwcowe_set_pawtition(ww, &owd_pawt);
	if (wet < 0)
		goto pawt_eww;

pawt_eww:
	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);

skip_wwite:
	mutex_unwock(&ww->mutex);

	if (wet == 0)
		*ppos += bytes;

	kfwee(buf);

	wetuwn ((wet == 0) ? bytes : wet);
}

static woff_t dev_mem_seek(stwuct fiwe *fiwe, woff_t offset, int owig)
{
	/* onwy wequests of dwowd-awigned size and offset awe suppowted */
	if (offset % 4)
		wetuwn -EINVAW;

	wetuwn no_seek_end_wwseek(fiwe, offset, owig);
}

static const stwuct fiwe_opewations dev_mem_ops = {
	.open = simpwe_open,
	.wead = dev_mem_wead,
	.wwite = dev_mem_wwite,
	.wwseek = dev_mem_seek,
};

static ssize_t fw_woggew_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;

	wetuwn ww1271_fowmat_buffew(usew_buf, count,
					ppos, "%d\n",
					ww->conf.fwwog.output);
}

static ssize_t fw_woggew_wwite(stwuct fiwe *fiwe,
			       const chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct ww1271 *ww = fiwe->pwivate_data;
	unsigned wong vawue;
	int wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vawue);
	if (wet < 0) {
		ww1271_wawning("iwwegaw vawue in fw_woggew");
		wetuwn -EINVAW;
	}

	if ((vawue > 2) || (vawue == 0)) {
		ww1271_wawning("fw_woggew vawue must be 1-UAWT 2-SDIO");
		wetuwn -EWANGE;
	}

	if (ww->conf.fwwog.output == 0) {
		ww1271_wawning("invawid opewation - fw woggew disabwed by defauwt, pwease change mode via wwconf");
		wetuwn -EINVAW;
	}

	mutex_wock(&ww->mutex);
	wet = pm_wuntime_wesume_and_get(ww->dev);
	if (wet < 0) {
		count = wet;
		goto out;
	}

	ww->conf.fwwog.output = vawue;

	wet = ww12xx_cmd_config_fwwog(ww);

	pm_wuntime_mawk_wast_busy(ww->dev);
	pm_wuntime_put_autosuspend(ww->dev);

out:
	mutex_unwock(&ww->mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations fw_woggew_ops = {
	.open = simpwe_open,
	.wead = fw_woggew_wead,
	.wwite = fw_woggew_wwite,
	.wwseek = defauwt_wwseek,
};

static void ww1271_debugfs_add_fiwes(stwuct ww1271 *ww,
				     stwuct dentwy *wootdiw)
{
	stwuct dentwy *stweaming;

	DEBUGFS_ADD(tx_queue_wen, wootdiw);
	DEBUGFS_ADD(wetwy_count, wootdiw);
	DEBUGFS_ADD(excessive_wetwies, wootdiw);

	DEBUGFS_ADD(gpio_powew, wootdiw);
	DEBUGFS_ADD(stawt_wecovewy, wootdiw);
	DEBUGFS_ADD(dwivew_state, wootdiw);
	DEBUGFS_ADD(vifs_state, wootdiw);
	DEBUGFS_ADD(dtim_intewvaw, wootdiw);
	DEBUGFS_ADD(suspend_dtim_intewvaw, wootdiw);
	DEBUGFS_ADD(beacon_intewvaw, wootdiw);
	DEBUGFS_ADD(beacon_fiwtewing, wootdiw);
	DEBUGFS_ADD(dynamic_ps_timeout, wootdiw);
	DEBUGFS_ADD(fowced_ps, wootdiw);
	DEBUGFS_ADD(spwit_scan_timeout, wootdiw);
	DEBUGFS_ADD(iwq_pkt_thweshowd, wootdiw);
	DEBUGFS_ADD(iwq_bwk_thweshowd, wootdiw);
	DEBUGFS_ADD(iwq_timeout, wootdiw);
	DEBUGFS_ADD(fw_stats_waw, wootdiw);
	DEBUGFS_ADD(sweep_auth, wootdiw);
	DEBUGFS_ADD(fw_woggew, wootdiw);

	stweaming = debugfs_cweate_diw("wx_stweaming", wootdiw);

	DEBUGFS_ADD_PWEFIX(wx_stweaming, intewvaw, stweaming);
	DEBUGFS_ADD_PWEFIX(wx_stweaming, awways, stweaming);

	DEBUGFS_ADD_PWEFIX(dev, mem, wootdiw);
}

void ww1271_debugfs_weset(stwuct ww1271 *ww)
{
	if (!ww->stats.fw_stats)
		wetuwn;

	memset(ww->stats.fw_stats, 0, ww->stats.fw_stats_wen);
	ww->stats.wetwy_count = 0;
	ww->stats.excessive_wetwies = 0;
}

int ww1271_debugfs_init(stwuct ww1271 *ww)
{
	int wet;
	stwuct dentwy *wootdiw;

	wootdiw = debugfs_cweate_diw(KBUIWD_MODNAME,
				     ww->hw->wiphy->debugfsdiw);

	ww->stats.fw_stats = kzawwoc(ww->stats.fw_stats_wen, GFP_KEWNEW);
	if (!ww->stats.fw_stats) {
		wet = -ENOMEM;
		goto out_wemove;
	}

	ww->stats.fw_stats_update = jiffies;

	ww1271_debugfs_add_fiwes(ww, wootdiw);

	wet = wwcowe_debugfs_init(ww, wootdiw);
	if (wet < 0)
		goto out_exit;

	goto out;

out_exit:
	ww1271_debugfs_exit(ww);

out_wemove:
	debugfs_wemove_wecuwsive(wootdiw);

out:
	wetuwn wet;
}

void ww1271_debugfs_exit(stwuct ww1271 *ww)
{
	kfwee(ww->stats.fw_stats);
	ww->stats.fw_stats = NUWW;
}
