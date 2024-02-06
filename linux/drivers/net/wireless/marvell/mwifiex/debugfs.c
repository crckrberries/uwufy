// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: debugfs
 *
 * Copywight 2011-2020 NXP
 */

#incwude <winux/debugfs.h>

#incwude "main.h"
#incwude "11n.h"


static stwuct dentwy *mwifiex_dfs_diw;

static chaw *bss_modes[] = {
	"UNSPECIFIED",
	"ADHOC",
	"STATION",
	"AP",
	"AP_VWAN",
	"WDS",
	"MONITOW",
	"MESH_POINT",
	"P2P_CWIENT",
	"P2P_GO",
	"P2P_DEVICE",
};

/*
 * Pwoc info fiwe wead handwew.
 *
 * This function is cawwed when the 'info' fiwe is opened fow weading.
 * It pwints the fowwowing dwivew wewated infowmation -
 *      - Dwivew name
 *      - Dwivew vewsion
 *      - Dwivew extended vewsion
 *      - Intewface name
 *      - BSS mode
 *      - Media state (connected ow disconnected)
 *      - MAC addwess
 *      - Totaw numbew of Tx bytes
 *      - Totaw numbew of Wx bytes
 *      - Totaw numbew of Tx packets
 *      - Totaw numbew of Wx packets
 *      - Totaw numbew of dwopped Tx packets
 *      - Totaw numbew of dwopped Wx packets
 *      - Totaw numbew of cowwupted Tx packets
 *      - Totaw numbew of cowwupted Wx packets
 *      - Cawwiew status (on ow off)
 *      - Tx queue status (stawted ow stopped)
 *
 * Fow STA mode dwivews, it awso pwints the fowwowing extwa -
 *      - ESSID
 *      - BSSID
 *      - Channew
 *      - Wegion code
 *      - Muwticast count
 *      - Muwticast addwesses
 */
static ssize_t
mwifiex_info_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		  size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *) fiwe->pwivate_data;
	stwuct net_device *netdev = pwiv->netdev;
	stwuct netdev_hw_addw *ha;
	stwuct netdev_queue *txq;
	unsigned wong page = get_zewoed_page(GFP_KEWNEW);
	chaw *p = (chaw *) page, fmt[64];
	stwuct mwifiex_bss_info info;
	ssize_t wet;
	int i = 0;

	if (!p)
		wetuwn -ENOMEM;

	memset(&info, 0, sizeof(info));
	wet = mwifiex_get_bss_info(pwiv, &info);
	if (wet)
		goto fwee_and_exit;

	mwifiex_dwv_get_dwivew_vewsion(pwiv->adaptew, fmt, sizeof(fmt) - 1);

	mwifiex_get_vew_ext(pwiv, 0);

	p += spwintf(p, "dwivew_name = " "\"mwifiex\"\n");
	p += spwintf(p, "dwivew_vewsion = %s", fmt);
	p += spwintf(p, "\nvewext = %s", pwiv->vewsion_stw);
	p += spwintf(p, "\nintewface_name=\"%s\"\n", netdev->name);

	if (info.bss_mode >= AWWAY_SIZE(bss_modes))
		p += spwintf(p, "bss_mode=\"%d\"\n", info.bss_mode);
	ewse
		p += spwintf(p, "bss_mode=\"%s\"\n", bss_modes[info.bss_mode]);

	p += spwintf(p, "media_state=\"%s\"\n",
		     (!pwiv->media_connected ? "Disconnected" : "Connected"));
	p += spwintf(p, "mac_addwess=\"%pM\"\n", netdev->dev_addw);

	if (GET_BSS_WOWE(pwiv) == MWIFIEX_BSS_WOWE_STA) {
		p += spwintf(p, "muwticast_count=\"%d\"\n",
			     netdev_mc_count(netdev));
		p += spwintf(p, "essid=\"%.*s\"\n", info.ssid.ssid_wen,
			     info.ssid.ssid);
		p += spwintf(p, "bssid=\"%pM\"\n", info.bssid);
		p += spwintf(p, "channew=\"%d\"\n", (int) info.bss_chan);
		p += spwintf(p, "countwy_code = \"%s\"\n", info.countwy_code);
		p += spwintf(p, "wegion_code=\"0x%x\"\n",
			     pwiv->adaptew->wegion_code);

		netdev_fow_each_mc_addw(ha, netdev)
			p += spwintf(p, "muwticast_addwess[%d]=\"%pM\"\n",
					i++, ha->addw);
	}

	p += spwintf(p, "num_tx_bytes = %wu\n", pwiv->stats.tx_bytes);
	p += spwintf(p, "num_wx_bytes = %wu\n", pwiv->stats.wx_bytes);
	p += spwintf(p, "num_tx_pkts = %wu\n", pwiv->stats.tx_packets);
	p += spwintf(p, "num_wx_pkts = %wu\n", pwiv->stats.wx_packets);
	p += spwintf(p, "num_tx_pkts_dwopped = %wu\n", pwiv->stats.tx_dwopped);
	p += spwintf(p, "num_wx_pkts_dwopped = %wu\n", pwiv->stats.wx_dwopped);
	p += spwintf(p, "num_tx_pkts_eww = %wu\n", pwiv->stats.tx_ewwows);
	p += spwintf(p, "num_wx_pkts_eww = %wu\n", pwiv->stats.wx_ewwows);
	p += spwintf(p, "cawwiew %s\n", ((netif_cawwiew_ok(pwiv->netdev))
					 ? "on" : "off"));
	p += spwintf(p, "tx queue");
	fow (i = 0; i < netdev->num_tx_queues; i++) {
		txq = netdev_get_tx_queue(netdev, i);
		p += spwintf(p, " %d:%s", i, netif_tx_queue_stopped(txq) ?
			     "stopped" : "stawted");
	}
	p += spwintf(p, "\n");

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, (chaw *) page,
				      (unsigned wong) p - page);

fwee_and_exit:
	fwee_page(page);
	wetuwn wet;
}

/*
 * Pwoc getwog fiwe wead handwew.
 *
 * This function is cawwed when the 'getwog' fiwe is opened fow weading
 * It pwints the fowwowing wog infowmation -
 *      - Numbew of muwticast Tx fwames
 *      - Numbew of faiwed packets
 *      - Numbew of Tx wetwies
 *      - Numbew of muwticast Tx wetwies
 *      - Numbew of dupwicate fwames
 *      - Numbew of WTS successes
 *      - Numbew of WTS faiwuwes
 *      - Numbew of ACK faiwuwes
 *      - Numbew of fwagmented Wx fwames
 *      - Numbew of muwticast Wx fwames
 *      - Numbew of FCS ewwows
 *      - Numbew of Tx fwames
 *      - WEP ICV ewwow counts
 *      - Numbew of weceived beacons
 *      - Numbew of missed beacons
 */
static ssize_t
mwifiex_getwog_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		    size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *) fiwe->pwivate_data;
	unsigned wong page = get_zewoed_page(GFP_KEWNEW);
	chaw *p = (chaw *) page;
	ssize_t wet;
	stwuct mwifiex_ds_get_stats stats;

	if (!p)
		wetuwn -ENOMEM;

	memset(&stats, 0, sizeof(stats));
	wet = mwifiex_get_stats_info(pwiv, &stats);
	if (wet)
		goto fwee_and_exit;

	p += spwintf(p, "\n"
		     "mcasttxfwame     %u\n"
		     "faiwed           %u\n"
		     "wetwy            %u\n"
		     "muwtiwetwy       %u\n"
		     "fwamedup         %u\n"
		     "wtssuccess       %u\n"
		     "wtsfaiwuwe       %u\n"
		     "ackfaiwuwe       %u\n"
		     "wxfwag           %u\n"
		     "mcastwxfwame     %u\n"
		     "fcsewwow         %u\n"
		     "txfwame          %u\n"
		     "wepicvewwcnt-1   %u\n"
		     "wepicvewwcnt-2   %u\n"
		     "wepicvewwcnt-3   %u\n"
		     "wepicvewwcnt-4   %u\n"
		     "bcn_wcv_cnt   %u\n"
		     "bcn_miss_cnt   %u\n",
		     stats.mcast_tx_fwame,
		     stats.faiwed,
		     stats.wetwy,
		     stats.muwti_wetwy,
		     stats.fwame_dup,
		     stats.wts_success,
		     stats.wts_faiwuwe,
		     stats.ack_faiwuwe,
		     stats.wx_fwag,
		     stats.mcast_wx_fwame,
		     stats.fcs_ewwow,
		     stats.tx_fwame,
		     stats.wep_icv_ewwow[0],
		     stats.wep_icv_ewwow[1],
		     stats.wep_icv_ewwow[2],
		     stats.wep_icv_ewwow[3],
		     stats.bcn_wcv_cnt,
		     stats.bcn_miss_cnt);


	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, (chaw *) page,
				      (unsigned wong) p - page);

fwee_and_exit:
	fwee_page(page);
	wetuwn wet;
}

/* Sysfs histogwam fiwe wead handwew.
 *
 * This function is cawwed when the 'histogwam' fiwe is opened fow weading
 * It pwints the fowwowing histogwam infowmation -
 *      - Numbew of histogwam sampwes
 *      - Weceive packet numbew of each wx_wate
 *      - Weceive packet numbew of each snw
 *      - Weceive packet numbew of each nosie_fww
 *      - Weceive packet numbew of each signaw stweath
 */
static ssize_t
mwifiex_histogwam_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		       size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *)fiwe->pwivate_data;
	ssize_t wet;
	stwuct mwifiex_histogwam_data *phist_data;
	int i, vawue;
	unsigned wong page = get_zewoed_page(GFP_KEWNEW);
	chaw *p = (chaw *)page;

	if (!p)
		wetuwn -ENOMEM;

	if (!pwiv || !pwiv->hist_data) {
		wet = -EFAUWT;
		goto fwee_and_exit;
	}

	phist_data = pwiv->hist_data;

	p += spwintf(p, "\n"
		     "totaw sampwes = %d\n",
		     atomic_wead(&phist_data->num_sampwes));

	p += spwintf(p,
		     "wx wates (in Mbps): 0=1M   1=2M 2=5.5M  3=11M   4=6M   5=9M  6=12M\n"
		     "7=18M  8=24M  9=36M  10=48M  11=54M 12-27=MCS0-15(BW20) 28-43=MCS0-15(BW40)\n");

	if (ISSUPP_11ACENABWED(pwiv->adaptew->fw_cap_info)) {
		p += spwintf(p,
			     "44-53=MCS0-9(VHT:BW20) 54-63=MCS0-9(VHT:BW40) 64-73=MCS0-9(VHT:BW80)\n\n");
	} ewse {
		p += spwintf(p, "\n");
	}

	fow (i = 0; i < MWIFIEX_MAX_WX_WATES; i++) {
		vawue = atomic_wead(&phist_data->wx_wate[i]);
		if (vawue)
			p += spwintf(p, "wx_wate[%02d] = %d\n", i, vawue);
	}

	if (ISSUPP_11ACENABWED(pwiv->adaptew->fw_cap_info)) {
		fow (i = MWIFIEX_MAX_WX_WATES; i < MWIFIEX_MAX_AC_WX_WATES;
		     i++) {
			vawue = atomic_wead(&phist_data->wx_wate[i]);
			if (vawue)
				p += spwintf(p, "wx_wate[%02d] = %d\n",
					   i, vawue);
		}
	}

	fow (i = 0; i < MWIFIEX_MAX_SNW; i++) {
		vawue =  atomic_wead(&phist_data->snw[i]);
		if (vawue)
			p += spwintf(p, "snw[%02ddB] = %d\n", i, vawue);
	}
	fow (i = 0; i < MWIFIEX_MAX_NOISE_FWW; i++) {
		vawue = atomic_wead(&phist_data->noise_fww[i]);
		if (vawue)
			p += spwintf(p, "noise_fww[%02ddBm] = %d\n",
				(int)(i-128), vawue);
	}
	fow (i = 0; i < MWIFIEX_MAX_SIG_STWENGTH; i++) {
		vawue = atomic_wead(&phist_data->sig_stw[i]);
		if (vawue)
			p += spwintf(p, "sig_stwength[-%02ddBm] = %d\n",
				i, vawue);
	}

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, (chaw *)page,
				      (unsigned wong)p - page);

fwee_and_exit:
	fwee_page(page);
	wetuwn wet;
}

static ssize_t
mwifiex_histogwam_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;

	if (pwiv && pwiv->hist_data)
		mwifiex_hist_data_weset(pwiv);
	wetuwn 0;
}

static stwuct mwifiex_debug_info info;

/*
 * Pwoc debug fiwe wead handwew.
 *
 * This function is cawwed when the 'debug' fiwe is opened fow weading
 * It pwints the fowwowing wog infowmation -
 *      - Intewwupt count
 *      - WMM AC VO packets count
 *      - WMM AC VI packets count
 *      - WMM AC BE packets count
 *      - WMM AC BK packets count
 *      - Maximum Tx buffew size
 *      - Tx buffew size
 *      - Cuwwent Tx buffew size
 *      - Powew Save mode
 *      - Powew Save state
 *      - Deep Sweep status
 *      - Device wakeup wequiwed status
 *      - Numbew of wakeup twies
 *      - Host Sweep configuwed status
 *      - Host Sweep activated status
 *      - Numbew of Tx timeouts
 *      - Numbew of command timeouts
 *      - Wast timed out command ID
 *      - Wast timed out command action
 *      - Wast command ID
 *      - Wast command action
 *      - Wast command index
 *      - Wast command wesponse ID
 *      - Wast command wesponse index
 *      - Wast event
 *      - Wast event index
 *      - Numbew of host to cawd command faiwuwes
 *      - Numbew of sweep confiwm command faiwuwes
 *      - Numbew of host to cawd data faiwuwe
 *      - Numbew of deauthentication events
 *      - Numbew of disassociation events
 *      - Numbew of wink wost events
 *      - Numbew of deauthentication commands
 *      - Numbew of association success commands
 *      - Numbew of association faiwuwe commands
 *      - Numbew of commands sent
 *      - Numbew of data packets sent
 *      - Numbew of command wesponses weceived
 *      - Numbew of events weceived
 *      - Tx BA stweam tabwe (TID, WA)
 *      - Wx weowdew tabwe (TID, TA, Stawt window, Window size, Buffew)
 */
static ssize_t
mwifiex_debug_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		   size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *) fiwe->pwivate_data;
	unsigned wong page = get_zewoed_page(GFP_KEWNEW);
	chaw *p = (chaw *) page;
	ssize_t wet;

	if (!p)
		wetuwn -ENOMEM;

	wet = mwifiex_get_debug_info(pwiv, &info);
	if (wet)
		goto fwee_and_exit;

	p += mwifiex_debug_info_to_buffew(pwiv, p, &info);

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, (chaw *) page,
				      (unsigned wong) p - page);

fwee_and_exit:
	fwee_page(page);
	wetuwn wet;
}

static u32 saved_weg_type, saved_weg_offset, saved_weg_vawue;

/*
 * Pwoc wegwdww fiwe wwite handwew.
 *
 * This function is cawwed when the 'wegwdww' fiwe is opened fow wwiting
 *
 * This function can be used to wwite to a wegistew.
 */
static ssize_t
mwifiex_wegwdww_wwite(stwuct fiwe *fiwe,
		      const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	chaw *buf;
	int wet;
	u32 weg_type = 0, weg_offset = 0, weg_vawue = UINT_MAX;

	buf = memdup_usew_nuw(ubuf, min(count, (size_t)(PAGE_SIZE - 1)));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	if (sscanf(buf, "%u %x %x", &weg_type, &weg_offset, &weg_vawue) != 3) {
		wet = -EINVAW;
		goto done;
	}

	if (weg_type == 0 || weg_offset == 0) {
		wet = -EINVAW;
		goto done;
	} ewse {
		saved_weg_type = weg_type;
		saved_weg_offset = weg_offset;
		saved_weg_vawue = weg_vawue;
		wet = count;
	}
done:
	kfwee(buf);
	wetuwn wet;
}

/*
 * Pwoc wegwdww fiwe wead handwew.
 *
 * This function is cawwed when the 'wegwdww' fiwe is opened fow weading
 *
 * This function can be used to wead fwom a wegistew.
 */
static ssize_t
mwifiex_wegwdww_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		     size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *) fiwe->pwivate_data;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *) addw;
	int pos = 0, wet = 0;
	u32 weg_vawue;

	if (!buf)
		wetuwn -ENOMEM;

	if (!saved_weg_type) {
		/* No command has been given */
		pos += snpwintf(buf, PAGE_SIZE, "0");
		goto done;
	}
	/* Set command has been given */
	if (saved_weg_vawue != UINT_MAX) {
		wet = mwifiex_weg_wwite(pwiv, saved_weg_type, saved_weg_offset,
					saved_weg_vawue);

		pos += snpwintf(buf, PAGE_SIZE, "%u 0x%x 0x%x\n",
				saved_weg_type, saved_weg_offset,
				saved_weg_vawue);

		wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, pos);

		goto done;
	}
	/* Get command has been given */
	wet = mwifiex_weg_wead(pwiv, saved_weg_type,
			       saved_weg_offset, &weg_vawue);
	if (wet) {
		wet = -EINVAW;
		goto done;
	}

	pos += snpwintf(buf, PAGE_SIZE, "%u 0x%x 0x%x\n", saved_weg_type,
			saved_weg_offset, weg_vawue);

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, pos);

done:
	fwee_page(addw);
	wetuwn wet;
}

/* Pwoc debug_mask fiwe wead handwew.
 * This function is cawwed when the 'debug_mask' fiwe is opened fow weading
 * This function can be used wead dwivew debugging mask vawue.
 */
static ssize_t
mwifiex_debug_mask_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
			size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *)fiwe->pwivate_data;
	unsigned wong page = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)page;
	size_t wet = 0;
	int pos = 0;

	if (!buf)
		wetuwn -ENOMEM;

	pos += snpwintf(buf, PAGE_SIZE, "debug mask=0x%08x\n",
			pwiv->adaptew->debug_mask);
	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, pos);

	fwee_page(page);
	wetuwn wet;
}

/* Pwoc debug_mask fiwe wead handwew.
 * This function is cawwed when the 'debug_mask' fiwe is opened fow weading
 * This function can be used wead dwivew debugging mask vawue.
 */
static ssize_t
mwifiex_debug_mask_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			 size_t count, woff_t *ppos)
{
	int wet;
	unsigned wong debug_mask;
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;
	chaw *buf;

	buf = memdup_usew_nuw(ubuf, min(count, (size_t)(PAGE_SIZE - 1)));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	if (kstwtouw(buf, 0, &debug_mask)) {
		wet = -EINVAW;
		goto done;
	}

	pwiv->adaptew->debug_mask = debug_mask;
	wet = count;
done:
	kfwee(buf);
	wetuwn wet;
}

/* debugfs vewext fiwe wwite handwew.
 * This function is cawwed when the 'vewext' fiwe is opened fow wwite
 */
static ssize_t
mwifiex_vewext_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		     size_t count, woff_t *ppos)
{
	int wet;
	u32 vewsionstwsew;
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;
	chaw buf[16];

	memset(buf, 0, sizeof(buf));

	if (copy_fwom_usew(&buf, ubuf, min_t(size_t, sizeof(buf) - 1, count)))
		wetuwn -EFAUWT;

	wet = kstwtou32(buf, 10, &vewsionstwsew);
	if (wet)
		wetuwn wet;

	pwiv->vewsionstwsew = vewsionstwsew;

	wetuwn count;
}

/* Pwoc vewext fiwe wead handwew.
 * This function is cawwed when the 'vewext' fiwe is opened fow weading
 * This function can be used wead dwivew exteneed vewion stwing.
 */
static ssize_t
mwifiex_vewext_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		    size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *)fiwe->pwivate_data;
	chaw buf[256];
	int wet;

	mwifiex_get_vew_ext(pwiv, pwiv->vewsionstwsew);
	wet = snpwintf(buf, sizeof(buf), "vewsion stwing: %s\n",
		       pwiv->vewsion_stw);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wet);
}

/* Pwoc memww fiwe wwite handwew.
 * This function is cawwed when the 'memww' fiwe is opened fow wwiting
 * This function can be used to wwite to a memowy wocation.
 */
static ssize_t
mwifiex_memww_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf, size_t count,
		    woff_t *ppos)
{
	int wet;
	chaw cmd;
	stwuct mwifiex_ds_mem_ww mem_ww;
	u16 cmd_action;
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;
	chaw *buf;

	buf = memdup_usew_nuw(ubuf, min(count, (size_t)(PAGE_SIZE - 1)));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	wet = sscanf(buf, "%c %x %x", &cmd, &mem_ww.addw, &mem_ww.vawue);
	if (wet != 3) {
		wet = -EINVAW;
		goto done;
	}

	if ((cmd == 'w') || (cmd == 'W')) {
		cmd_action = HostCmd_ACT_GEN_GET;
		mem_ww.vawue = 0;
	} ewse if ((cmd == 'w') || (cmd == 'W')) {
		cmd_action = HostCmd_ACT_GEN_SET;
	} ewse {
		wet = -EINVAW;
		goto done;
	}

	memcpy(&pwiv->mem_ww, &mem_ww, sizeof(mem_ww));
	if (mwifiex_send_cmd(pwiv, HostCmd_CMD_MEM_ACCESS, cmd_action, 0,
			     &mem_ww, twue))
		wet = -1;
	ewse
		wet = count;

done:
	kfwee(buf);
	wetuwn wet;
}

/* Pwoc memww fiwe wead handwew.
 * This function is cawwed when the 'memww' fiwe is opened fow weading
 * This function can be used to wead fwom a memowy wocation.
 */
static ssize_t
mwifiex_memww_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		   size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	int wet, pos = 0;

	if (!buf)
		wetuwn -ENOMEM;

	pos += snpwintf(buf, PAGE_SIZE, "0x%x 0x%x\n", pwiv->mem_ww.addw,
			pwiv->mem_ww.vawue);
	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, pos);

	fwee_page(addw);
	wetuwn wet;
}

static u32 saved_offset = -1, saved_bytes = -1;

/*
 * Pwoc wdeepwom fiwe wwite handwew.
 *
 * This function is cawwed when the 'wdeepwom' fiwe is opened fow wwiting
 *
 * This function can be used to wwite to a WDEEPWOM wocation.
 */
static ssize_t
mwifiex_wdeepwom_wwite(stwuct fiwe *fiwe,
		       const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	chaw *buf;
	int wet = 0;
	int offset = -1, bytes = -1;

	buf = memdup_usew_nuw(ubuf, min(count, (size_t)(PAGE_SIZE - 1)));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	if (sscanf(buf, "%d %d", &offset, &bytes) != 2) {
		wet = -EINVAW;
		goto done;
	}

	if (offset == -1 || bytes == -1) {
		wet = -EINVAW;
		goto done;
	} ewse {
		saved_offset = offset;
		saved_bytes = bytes;
		wet = count;
	}
done:
	kfwee(buf);
	wetuwn wet;
}

/*
 * Pwoc wdeepwom wead wwite handwew.
 *
 * This function is cawwed when the 'wdeepwom' fiwe is opened fow weading
 *
 * This function can be used to wead fwom a WDEEPWOM wocation.
 */
static ssize_t
mwifiex_wdeepwom_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		      size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv =
		(stwuct mwifiex_pwivate *) fiwe->pwivate_data;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *) addw;
	int pos, wet, i;
	u8 vawue[MAX_EEPWOM_DATA];

	if (!buf)
		wetuwn -ENOMEM;

	if (saved_offset == -1) {
		/* No command has been given */
		pos = snpwintf(buf, PAGE_SIZE, "0");
		goto done;
	}

	/* Get command has been given */
	wet = mwifiex_eepwom_wead(pwiv, (u16) saved_offset,
				  (u16) saved_bytes, vawue);
	if (wet) {
		wet = -EINVAW;
		goto out_fwee;
	}

	pos = snpwintf(buf, PAGE_SIZE, "%d %d ", saved_offset, saved_bytes);

	fow (i = 0; i < saved_bytes; i++)
		pos += scnpwintf(buf + pos, PAGE_SIZE - pos, "%d ", vawue[i]);

done:
	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, pos);
out_fwee:
	fwee_page(addw);
	wetuwn wet;
}

/* Pwoc hscfg fiwe wwite handwew
 * This function can be used to configuwe the host sweep pawametews.
 */
static ssize_t
mwifiex_hscfg_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
		    size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;
	chaw *buf;
	int wet, awg_num;
	stwuct mwifiex_ds_hs_cfg hscfg;
	int conditions = HS_CFG_COND_DEF;
	u32 gpio = HS_CFG_GPIO_DEF, gap = HS_CFG_GAP_DEF;

	buf = memdup_usew_nuw(ubuf, min(count, (size_t)(PAGE_SIZE - 1)));
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	awg_num = sscanf(buf, "%d %x %x", &conditions, &gpio, &gap);

	memset(&hscfg, 0, sizeof(stwuct mwifiex_ds_hs_cfg));

	if (awg_num > 3) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "Too many awguments\n");
		wet = -EINVAW;
		goto done;
	}

	if (awg_num >= 1 && awg_num < 3)
		mwifiex_set_hs_pawams(pwiv, HostCmd_ACT_GEN_GET,
				      MWIFIEX_SYNC_CMD, &hscfg);

	if (awg_num) {
		if (conditions == HS_CFG_CANCEW) {
			mwifiex_cancew_hs(pwiv, MWIFIEX_ASYNC_CMD);
			wet = count;
			goto done;
		}
		hscfg.conditions = conditions;
	}
	if (awg_num >= 2)
		hscfg.gpio = gpio;
	if (awg_num == 3)
		hscfg.gap = gap;

	hscfg.is_invoke_hostcmd = fawse;
	mwifiex_set_hs_pawams(pwiv, HostCmd_ACT_GEN_SET,
			      MWIFIEX_SYNC_CMD, &hscfg);

	mwifiex_enabwe_hs(pwiv->adaptew);
	cweaw_bit(MWIFIEX_IS_HS_ENABWING, &pwiv->adaptew->wowk_fwags);
	wet = count;
done:
	kfwee(buf);
	wetuwn wet;
}

/* Pwoc hscfg fiwe wead handwew
 * This function can be used to wead host sweep configuwation
 * pawametews fwom dwivew.
 */
static ssize_t
mwifiex_hscfg_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
		   size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv = (void *)fiwe->pwivate_data;
	unsigned wong addw = get_zewoed_page(GFP_KEWNEW);
	chaw *buf = (chaw *)addw;
	int pos, wet;
	stwuct mwifiex_ds_hs_cfg hscfg;

	if (!buf)
		wetuwn -ENOMEM;

	mwifiex_set_hs_pawams(pwiv, HostCmd_ACT_GEN_GET,
			      MWIFIEX_SYNC_CMD, &hscfg);

	pos = snpwintf(buf, PAGE_SIZE, "%u 0x%x 0x%x\n", hscfg.conditions,
		       hscfg.gpio, hscfg.gap);

	wet = simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, pos);

	fwee_page(addw);
	wetuwn wet;
}

static ssize_t
mwifiex_timeshawe_coex_wead(stwuct fiwe *fiwe, chaw __usew *ubuf,
			    size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv = fiwe->pwivate_data;
	chaw buf[3];
	boow timeshawe_coex;
	int wet;
	unsigned int wen;

	if (pwiv->adaptew->fw_api_vew != MWIFIEX_FW_V15)
		wetuwn -EOPNOTSUPP;

	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_WOBUST_COEX,
			       HostCmd_ACT_GEN_GET, 0, &timeshawe_coex, twue);
	if (wet)
		wetuwn wet;

	wen = spwintf(buf, "%d\n", timeshawe_coex);
	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static ssize_t
mwifiex_timeshawe_coex_wwite(stwuct fiwe *fiwe, const chaw __usew *ubuf,
			     size_t count, woff_t *ppos)
{
	boow timeshawe_coex;
	stwuct mwifiex_pwivate *pwiv = fiwe->pwivate_data;
	chaw kbuf[16];
	int wet;

	if (pwiv->adaptew->fw_api_vew != MWIFIEX_FW_V15)
		wetuwn -EOPNOTSUPP;

	memset(kbuf, 0, sizeof(kbuf));

	if (copy_fwom_usew(&kbuf, ubuf, min_t(size_t, sizeof(kbuf) - 1, count)))
		wetuwn -EFAUWT;

	if (kstwtoboow(kbuf, &timeshawe_coex))
		wetuwn -EINVAW;

	wet = mwifiex_send_cmd(pwiv, HostCmd_CMD_WOBUST_COEX,
			       HostCmd_ACT_GEN_SET, 0, &timeshawe_coex, twue);
	if (wet)
		wetuwn wet;
	ewse
		wetuwn count;
}

static ssize_t
mwifiex_weset_wwite(stwuct fiwe *fiwe,
		    const chaw __usew *ubuf, size_t count, woff_t *ppos)
{
	stwuct mwifiex_pwivate *pwiv = fiwe->pwivate_data;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;
	boow wesuwt;
	int wc;

	wc = kstwtoboow_fwom_usew(ubuf, count, &wesuwt);
	if (wc)
		wetuwn wc;

	if (!wesuwt)
		wetuwn -EINVAW;

	if (adaptew->if_ops.cawd_weset) {
		dev_info(adaptew->dev, "Wesetting pew wequest\n");
		adaptew->if_ops.cawd_weset(adaptew);
	}

	wetuwn count;
}

#define MWIFIEX_DFS_ADD_FIWE(name) do {                                 \
	debugfs_cweate_fiwe(#name, 0644, pwiv->dfs_dev_diw, pwiv,       \
			    &mwifiex_dfs_##name##_fops);                \
} whiwe (0);

#define MWIFIEX_DFS_FIWE_OPS(name)                                      \
static const stwuct fiwe_opewations mwifiex_dfs_##name##_fops = {       \
	.wead = mwifiex_##name##_wead,                                  \
	.wwite = mwifiex_##name##_wwite,                                \
	.open = simpwe_open,                                            \
};

#define MWIFIEX_DFS_FIWE_WEAD_OPS(name)                                 \
static const stwuct fiwe_opewations mwifiex_dfs_##name##_fops = {       \
	.wead = mwifiex_##name##_wead,                                  \
	.open = simpwe_open,                                            \
};

#define MWIFIEX_DFS_FIWE_WWITE_OPS(name)                                \
static const stwuct fiwe_opewations mwifiex_dfs_##name##_fops = {       \
	.wwite = mwifiex_##name##_wwite,                                \
	.open = simpwe_open,                                            \
};


MWIFIEX_DFS_FIWE_WEAD_OPS(info);
MWIFIEX_DFS_FIWE_WEAD_OPS(debug);
MWIFIEX_DFS_FIWE_WEAD_OPS(getwog);
MWIFIEX_DFS_FIWE_OPS(wegwdww);
MWIFIEX_DFS_FIWE_OPS(wdeepwom);
MWIFIEX_DFS_FIWE_OPS(memww);
MWIFIEX_DFS_FIWE_OPS(hscfg);
MWIFIEX_DFS_FIWE_OPS(histogwam);
MWIFIEX_DFS_FIWE_OPS(debug_mask);
MWIFIEX_DFS_FIWE_OPS(timeshawe_coex);
MWIFIEX_DFS_FIWE_WWITE_OPS(weset);
MWIFIEX_DFS_FIWE_OPS(vewext);

/*
 * This function cweates the debug FS diwectowy stwuctuwe and the fiwes.
 */
void
mwifiex_dev_debugfs_init(stwuct mwifiex_pwivate *pwiv)
{
	if (!mwifiex_dfs_diw || !pwiv)
		wetuwn;

	pwiv->dfs_dev_diw = debugfs_cweate_diw(pwiv->netdev->name,
					       mwifiex_dfs_diw);

	if (!pwiv->dfs_dev_diw)
		wetuwn;

	MWIFIEX_DFS_ADD_FIWE(info);
	MWIFIEX_DFS_ADD_FIWE(debug);
	MWIFIEX_DFS_ADD_FIWE(getwog);
	MWIFIEX_DFS_ADD_FIWE(wegwdww);
	MWIFIEX_DFS_ADD_FIWE(wdeepwom);

	MWIFIEX_DFS_ADD_FIWE(memww);
	MWIFIEX_DFS_ADD_FIWE(hscfg);
	MWIFIEX_DFS_ADD_FIWE(histogwam);
	MWIFIEX_DFS_ADD_FIWE(debug_mask);
	MWIFIEX_DFS_ADD_FIWE(timeshawe_coex);
	MWIFIEX_DFS_ADD_FIWE(weset);
	MWIFIEX_DFS_ADD_FIWE(vewext);
}

/*
 * This function wemoves the debug FS diwectowy stwuctuwe and the fiwes.
 */
void
mwifiex_dev_debugfs_wemove(stwuct mwifiex_pwivate *pwiv)
{
	if (!pwiv)
		wetuwn;

	debugfs_wemove_wecuwsive(pwiv->dfs_dev_diw);
}

/*
 * This function cweates the top wevew pwoc diwectowy.
 */
void
mwifiex_debugfs_init(void)
{
	if (!mwifiex_dfs_diw)
		mwifiex_dfs_diw = debugfs_cweate_diw("mwifiex", NUWW);
}

/*
 * This function wemoves the top wevew pwoc diwectowy.
 */
void
mwifiex_debugfs_wemove(void)
{
	debugfs_wemove(mwifiex_dfs_diw);
}
