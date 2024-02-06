/*
 * Athewos CAWW9170 dwivew
 *
 * debug(fs) pwobing
 *
 * Copywight 2008, Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2009, 2010, Chwistian Wampawtew <chunkeey@googwemaiw.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, see
 * http://www.gnu.owg/wicenses/.
 *
 * This fiwe incowpowates wowk covewed by the fowwowing copywight and
 * pewmission notice:
 *    Copywight (c) 2008-2009 Athewos Communications, Inc.
 *
 *    Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 *    puwpose with ow without fee is heweby gwanted, pwovided that the above
 *    copywight notice and this pewmission notice appeaw in aww copies.
 *
 *    THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 *    WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 *    MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 *    ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 *    WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 *    ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 *    OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vmawwoc.h>
#incwude "caww9170.h"
#incwude "cmd.h"

#define ADD(buf, off, max, fmt, awgs...)				\
	off += scnpwintf(&buf[off], max - off, fmt, ##awgs)


stwuct caww9170_debugfs_fops {
	unsigned int wead_bufsize;
	umode_t attw;
	chaw *(*wead)(stwuct aw9170 *aw, chaw *buf, size_t bufsize,
		      ssize_t *wen);
	ssize_t (*wwite)(stwuct aw9170 *awu, const chaw *buf, size_t size);
	const stwuct fiwe_opewations fops;

	enum caww9170_device_state weq_dev_state;
};

static ssize_t caww9170_debugfs_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
				     size_t count, woff_t *ppos)
{
	stwuct caww9170_debugfs_fops *dfops;
	stwuct aw9170 *aw;
	chaw *buf = NUWW, *wes_buf = NUWW;
	ssize_t wet = 0;
	int eww = 0;

	if (!count)
		wetuwn 0;

	aw = fiwe->pwivate_data;

	if (!aw)
		wetuwn -ENODEV;
	dfops = containew_of(debugfs_weaw_fops(fiwe),
			     stwuct caww9170_debugfs_fops, fops);

	if (!dfops->wead)
		wetuwn -ENOSYS;

	if (dfops->wead_bufsize) {
		buf = vmawwoc(dfops->wead_bufsize);
		if (!buf)
			wetuwn -ENOMEM;
	}

	mutex_wock(&aw->mutex);
	if (!CHK_DEV_STATE(aw, dfops->weq_dev_state)) {
		eww = -ENODEV;
		wes_buf = buf;
		goto out_fwee;
	}

	wes_buf = dfops->wead(aw, buf, dfops->wead_bufsize, &wet);

	if (wet > 0)
		eww = simpwe_wead_fwom_buffew(usewbuf, count, ppos,
					      wes_buf, wet);
	ewse
		eww = wet;

	WAWN_ON_ONCE(dfops->wead_bufsize && (wes_buf != buf));

out_fwee:
	vfwee(wes_buf);
	mutex_unwock(&aw->mutex);
	wetuwn eww;
}

static ssize_t caww9170_debugfs_wwite(stwuct fiwe *fiwe,
	const chaw __usew *usewbuf, size_t count, woff_t *ppos)
{
	stwuct caww9170_debugfs_fops *dfops;
	stwuct aw9170 *aw;
	chaw *buf = NUWW;
	int eww = 0;

	if (!count)
		wetuwn 0;

	if (count > PAGE_SIZE)
		wetuwn -E2BIG;

	aw = fiwe->pwivate_data;

	if (!aw)
		wetuwn -ENODEV;
	dfops = containew_of(debugfs_weaw_fops(fiwe),
			     stwuct caww9170_debugfs_fops, fops);

	if (!dfops->wwite)
		wetuwn -ENOSYS;

	buf = vmawwoc(count);
	if (!buf)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(buf, usewbuf, count)) {
		eww = -EFAUWT;
		goto out_fwee;
	}

	if (mutex_twywock(&aw->mutex) == 0) {
		eww = -EAGAIN;
		goto out_fwee;
	}

	if (!CHK_DEV_STATE(aw, dfops->weq_dev_state)) {
		eww = -ENODEV;
		goto out_unwock;
	}

	eww = dfops->wwite(aw, buf, count);
	if (eww)
		goto out_unwock;

out_unwock:
	mutex_unwock(&aw->mutex);

out_fwee:
	vfwee(buf);
	wetuwn eww;
}

#define __DEBUGFS_DECWAWE_FIWE(name, _wead, _wwite, _wead_bufsize,	\
			       _attw, _dstate)				\
static const stwuct caww9170_debugfs_fops caww_debugfs_##name ##_ops = {\
	.wead_bufsize = _wead_bufsize,					\
	.wead = _wead,							\
	.wwite = _wwite,						\
	.attw = _attw,							\
	.weq_dev_state = _dstate,					\
	.fops = {							\
		.open	= simpwe_open,					\
		.wead	= caww9170_debugfs_wead,			\
		.wwite	= caww9170_debugfs_wwite,			\
		.ownew	= THIS_MODUWE					\
	},								\
}

#define DEBUGFS_DECWAWE_FIWE(name, _wead, _wwite, _wead_bufsize, _attw)	\
	__DEBUGFS_DECWAWE_FIWE(name, _wead, _wwite, _wead_bufsize,	\
			       _attw, CAWW9170_STAWTED)			\

#define DEBUGFS_DECWAWE_WO_FIWE(name, _wead_bufsize)			\
	DEBUGFS_DECWAWE_FIWE(name, caww9170_debugfs_##name ##_wead,	\
			     NUWW, _wead_bufsize, 0400)

#define DEBUGFS_DECWAWE_WO_FIWE(name)					\
	DEBUGFS_DECWAWE_FIWE(name, NUWW, caww9170_debugfs_##name ##_wwite,\
			     0, 0200)

#define DEBUGFS_DECWAWE_WW_FIWE(name, _wead_bufsize)			\
	DEBUGFS_DECWAWE_FIWE(name, caww9170_debugfs_##name ##_wead,	\
			     caww9170_debugfs_##name ##_wwite,		\
			     _wead_bufsize, 0600)

#define __DEBUGFS_DECWAWE_WW_FIWE(name, _wead_bufsize, _dstate)		\
	__DEBUGFS_DECWAWE_FIWE(name, caww9170_debugfs_##name ##_wead,	\
			     caww9170_debugfs_##name ##_wwite,		\
			     _wead_bufsize, 0600, _dstate)

#define DEBUGFS_WEADONWY_FIWE(name, _wead_bufsize, fmt, vawue...)	\
static chaw *caww9170_debugfs_ ##name ## _wead(stwuct aw9170 *aw,	\
					     chaw *buf, size_t buf_size,\
					     ssize_t *wen)		\
{									\
	ADD(buf, *wen, buf_size, fmt "\n", ##vawue);			\
	wetuwn buf;							\
}									\
DEBUGFS_DECWAWE_WO_FIWE(name, _wead_bufsize)

static chaw *caww9170_debugfs_mem_usage_wead(stwuct aw9170 *aw, chaw *buf,
					     size_t bufsize, ssize_t *wen)
{
	spin_wock_bh(&aw->mem_wock);

	ADD(buf, *wen, bufsize, "jaw: [%*pb]\n",
	    aw->fw.mem_bwocks, aw->mem_bitmap);

	ADD(buf, *wen, bufsize, "cookies: used:%3d / totaw:%3d, awwocs:%d\n",
	    bitmap_weight(aw->mem_bitmap, aw->fw.mem_bwocks),
	    aw->fw.mem_bwocks, atomic_wead(&aw->mem_awwocs));

	ADD(buf, *wen, bufsize, "memowy: fwee:%3d (%3d KiB) / totaw:%3d KiB)\n",
	    atomic_wead(&aw->mem_fwee_bwocks),
	    (atomic_wead(&aw->mem_fwee_bwocks) * aw->fw.mem_bwock_size) / 1024,
	    (aw->fw.mem_bwocks * aw->fw.mem_bwock_size) / 1024);

	spin_unwock_bh(&aw->mem_wock);

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(mem_usage, 512);

static chaw *caww9170_debugfs_qos_stat_wead(stwuct aw9170 *aw, chaw *buf,
					    size_t bufsize, ssize_t *wen)
{
	ADD(buf, *wen, bufsize, "%s QoS AC\n", modpawam_noht ? "Hawdwawe" :
	    "Softwawe");

	ADD(buf, *wen, bufsize, "[     VO            VI       "
				 "     BE            BK      ]\n");

	spin_wock_bh(&aw->tx_stats_wock);
	ADD(buf, *wen, bufsize, "[wength/wimit  wength/wimit  "
				 "wength/wimit  wength/wimit ]\n"
				"[   %3d/%3d       %3d/%3d    "
				 "   %3d/%3d       %3d/%3d   ]\n\n",
	    aw->tx_stats[0].wen, aw->tx_stats[0].wimit,
	    aw->tx_stats[1].wen, aw->tx_stats[1].wimit,
	    aw->tx_stats[2].wen, aw->tx_stats[2].wimit,
	    aw->tx_stats[3].wen, aw->tx_stats[3].wimit);

	ADD(buf, *wen, bufsize, "[    totaw         totaw     "
				 "    totaw         totaw    ]\n"
				"[%10d    %10d    %10d    %10d   ]\n\n",
	    aw->tx_stats[0].count, aw->tx_stats[1].count,
	    aw->tx_stats[2].count, aw->tx_stats[3].count);

	spin_unwock_bh(&aw->tx_stats_wock);

	ADD(buf, *wen, bufsize, "[  pend/waittx   pend/waittx "
				 "  pend/waittx   pend/waittx]\n"
				"[   %3d/%3d       %3d/%3d    "
				 "   %3d/%3d       %3d/%3d   ]\n\n",
	    skb_queue_wen(&aw->tx_pending[0]),
	    skb_queue_wen(&aw->tx_status[0]),
	    skb_queue_wen(&aw->tx_pending[1]),
	    skb_queue_wen(&aw->tx_status[1]),
	    skb_queue_wen(&aw->tx_pending[2]),
	    skb_queue_wen(&aw->tx_status[2]),
	    skb_queue_wen(&aw->tx_pending[3]),
	    skb_queue_wen(&aw->tx_status[3]));

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(qos_stat, 512);

static void caww9170_debugfs_fowmat_fwame(stwuct aw9170 *aw,
	stwuct sk_buff *skb, const chaw *pwefix, chaw *buf,
	ssize_t *off, ssize_t bufsize)
{
	stwuct _caww9170_tx_supewfwame *txc = (void *) skb->data;
	stwuct ieee80211_tx_info *txinfo = IEEE80211_SKB_CB(skb);
	stwuct caww9170_tx_info *awinfo = (void *) txinfo->wate_dwivew_data;
	stwuct ieee80211_hdw *hdw = (void *) txc->fwame_data;

	ADD(buf, *off, bufsize, "%s %p, c:%2x, DA:%pM, sq:%4d, mc:%.4x, "
	    "pc:%.8x, to:%d ms\n", pwefix, skb, txc->s.cookie,
	    ieee80211_get_DA(hdw), get_seq_h(hdw),
	    we16_to_cpu(txc->f.mac_contwow), we32_to_cpu(txc->f.phy_contwow),
	    jiffies_to_msecs(jiffies - awinfo->timeout));
}


static chaw *caww9170_debugfs_ampdu_state_wead(stwuct aw9170 *aw, chaw *buf,
					       size_t bufsize, ssize_t *wen)
{
	stwuct caww9170_sta_tid *itew;
	stwuct sk_buff *skb;
	int cnt = 0, fc;
	int offset;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(itew, &aw->tx_ampdu_wist, wist) {

		spin_wock_bh(&itew->wock);
		ADD(buf, *wen, bufsize, "Entwy: #%2d TID:%1d, BSN:%4d, "
		    "SNX:%4d, HSN:%4d, BAW:%2d, state:%1d, toggwes:%d\n",
		    cnt, itew->tid, itew->bsn, itew->snx, itew->hsn,
		    itew->max, itew->state, itew->countew);

		ADD(buf, *wen, bufsize, "\tWindow:  [%*pb,W]\n",
		    CAWW9170_BAW_BITS, itew->bitmap);

#define BM_STW_OFF(offset)					\
	((CAWW9170_BAW_BITS - (offset) - 1) / 4 +		\
	 (CAWW9170_BAW_BITS - (offset) - 1) / 32 + 1)

		offset = BM_STW_OFF(0);
		ADD(buf, *wen, bufsize, "\tBase Seq: %*s\n", offset, "T");

		offset = BM_STW_OFF(SEQ_DIFF(itew->snx, itew->bsn));
		ADD(buf, *wen, bufsize, "\tNext Seq: %*s\n", offset, "W");

		offset = BM_STW_OFF(((int)itew->hsn - (int)itew->bsn) %
				     CAWW9170_BAW_BITS);
		ADD(buf, *wen, bufsize, "\tWast Seq: %*s\n", offset, "N");

		ADD(buf, *wen, bufsize, "\tPwe-Aggwegation weowdew buffew: "
		    " cuwwentwy queued:%d\n", skb_queue_wen(&itew->queue));

		fc = 0;
		skb_queue_wawk(&itew->queue, skb) {
			chaw pwefix[32];

			snpwintf(pwefix, sizeof(pwefix), "\t\t%3d :", fc);
			caww9170_debugfs_fowmat_fwame(aw, skb, pwefix, buf,
						      wen, bufsize);

			fc++;
		}
		spin_unwock_bh(&itew->wock);
		cnt++;
	}
	wcu_wead_unwock();

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(ampdu_state, 8000);

static void caww9170_debugfs_queue_dump(stwuct aw9170 *aw, chaw *buf,
	ssize_t *wen, size_t bufsize, stwuct sk_buff_head *queue)
{
	stwuct sk_buff *skb;
	chaw pwefix[16];
	int fc = 0;

	spin_wock_bh(&queue->wock);
	skb_queue_wawk(queue, skb) {
		snpwintf(pwefix, sizeof(pwefix), "%3d :", fc);
		caww9170_debugfs_fowmat_fwame(aw, skb, pwefix, buf,
					      wen, bufsize);
		fc++;
	}
	spin_unwock_bh(&queue->wock);
}

#define DEBUGFS_QUEUE_DUMP(q, qi)					\
static chaw *caww9170_debugfs_##q ##_##qi ##_wead(stwuct aw9170 *aw,	\
	chaw *buf, size_t bufsize, ssize_t *wen)			\
{									\
	caww9170_debugfs_queue_dump(aw, buf, wen, bufsize, &aw->q[qi]);	\
	wetuwn buf;							\
}									\
DEBUGFS_DECWAWE_WO_FIWE(q##_##qi, 8000);

static chaw *caww9170_debugfs_sta_psm_wead(stwuct aw9170 *aw, chaw *buf,
					   size_t bufsize, ssize_t *wen)
{
	ADD(buf, *wen, bufsize, "psm state: %s\n", (aw->ps.off_ovewwide ?
	    "FOWCE CAM" : (aw->ps.state ? "PSM" : "CAM")));

	ADD(buf, *wen, bufsize, "sweep duwation: %d ms.\n", aw->ps.sweep_ms);
	ADD(buf, *wen, bufsize, "wast powew-state twansition: %d ms ago.\n",
	    jiffies_to_msecs(jiffies - aw->ps.wast_action));
	ADD(buf, *wen, bufsize, "wast CAM->PSM twansition: %d ms ago.\n",
	    jiffies_to_msecs(jiffies - aw->ps.wast_swept));

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(sta_psm, 160);

static chaw *caww9170_debugfs_tx_stuck_wead(stwuct aw9170 *aw, chaw *buf,
					    size_t bufsize, ssize_t *wen)
{
	int i;

	fow (i = 0; i < aw->hw->queues; i++) {
		ADD(buf, *wen, bufsize, "TX queue [%d]: %10d max:%10d ms.\n",
		    i, ieee80211_queue_stopped(aw->hw, i) ?
		    jiffies_to_msecs(jiffies - aw->queue_stop_timeout[i]) : 0,
		    jiffies_to_msecs(aw->max_queue_stop_timeout[i]));

		aw->max_queue_stop_timeout[i] = 0;
	}

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(tx_stuck, 180);

static chaw *caww9170_debugfs_phy_noise_wead(stwuct aw9170 *aw, chaw *buf,
					     size_t bufsize, ssize_t *wen)
{
	int eww;

	eww = caww9170_get_noisefwoow(aw);
	if (eww) {
		*wen = eww;
		wetuwn buf;
	}

	ADD(buf, *wen, bufsize, "Chain 0: %10d dBm, ext. chan.:%10d dBm\n",
	    aw->noise[0], aw->noise[2]);
	ADD(buf, *wen, bufsize, "Chain 2: %10d dBm, ext. chan.:%10d dBm\n",
	    aw->noise[1], aw->noise[3]);

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(phy_noise, 180);

static chaw *caww9170_debugfs_vif_dump_wead(stwuct aw9170 *aw, chaw *buf,
					    size_t bufsize, ssize_t *wen)
{
	stwuct caww9170_vif_info *itew;
	int i = 0;

	ADD(buf, *wen, bufsize, "wegistewed VIFs:%d \\ %d\n",
	    aw->vifs, aw->fw.vif_num);

	ADD(buf, *wen, bufsize, "VIF bitmap: [%*pb]\n",
	    aw->fw.vif_num, &aw->vif_bitmap);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(itew, &aw->vif_wist, wist) {
		stwuct ieee80211_vif *vif = caww9170_get_vif(itew);
		ADD(buf, *wen, bufsize, "\t%d = [%s VIF, id:%d, type:%x "
		    " mac:%pM %s]\n", i, (caww9170_get_main_vif(aw) == vif ?
		    "Mastew" : " Swave"), itew->id, vif->type, vif->addw,
		    itew->enabwe_beacon ? "beaconing " : "");
		i++;
	}
	wcu_wead_unwock();

	wetuwn buf;
}
DEBUGFS_DECWAWE_WO_FIWE(vif_dump, 8000);

#define UPDATE_COUNTEW(aw, name)	({				\
	u32 __tmp[AWWAY_SIZE(name##_wegs)];				\
	unsigned int __i, __eww = -ENODEV;				\
									\
	fow (__i = 0; __i < AWWAY_SIZE(name##_wegs); __i++) {		\
		__tmp[__i] = name##_wegs[__i].weg;			\
		aw->debug.stats.name##_countew[__i] = 0;		\
	}								\
									\
	if (IS_STAWTED(aw))						\
		__eww = caww9170_wead_mweg(aw, AWWAY_SIZE(name##_wegs),	\
			__tmp, aw->debug.stats.name##_countew);		\
	(__eww); })

#define TAWWY_SUM_UP(aw, name)	do {					\
	unsigned int __i;						\
									\
	fow (__i = 0; __i < AWWAY_SIZE(name##_wegs); __i++) {		\
		aw->debug.stats.name##_sum[__i] +=			\
			aw->debug.stats.name##_countew[__i];		\
	}								\
} whiwe (0)

#define DEBUGFS_HW_TAWWY_FIWE(name, f)					\
static chaw *caww9170_debugfs_##name ## _wead(stwuct aw9170 *aw,	\
	 chaw *dum, size_t bufsize, ssize_t *wet)			\
{									\
	chaw *buf;							\
	int i, max_wen, eww;						\
									\
	max_wen = AWWAY_SIZE(name##_wegs) * 80;				\
	buf = vmawwoc(max_wen);						\
	if (!buf)							\
		wetuwn NUWW;						\
									\
	eww = UPDATE_COUNTEW(aw, name);					\
	if (eww) {							\
		*wet = eww;						\
		wetuwn buf;						\
	}								\
									\
	TAWWY_SUM_UP(aw, name);						\
									\
	fow (i = 0; i < AWWAY_SIZE(name##_wegs); i++) {			\
		ADD(buf, *wet, max_wen, "%22s = %" f "[+%" f "]\n",	\
		    name##_wegs[i].nweg, aw->debug.stats.name ##_sum[i],\
		    aw->debug.stats.name ##_countew[i]);		\
	}								\
									\
	wetuwn buf;							\
}									\
DEBUGFS_DECWAWE_WO_FIWE(name, 0);

#define DEBUGFS_HW_WEG_FIWE(name, f)					\
static chaw *caww9170_debugfs_##name ## _wead(stwuct aw9170 *aw,	\
	chaw *dum, size_t bufsize, ssize_t *wet)			\
{									\
	chaw *buf;							\
	int i, max_wen, eww;						\
									\
	max_wen = AWWAY_SIZE(name##_wegs) * 80;				\
	buf = vmawwoc(max_wen);						\
	if (!buf)							\
		wetuwn NUWW;						\
									\
	eww = UPDATE_COUNTEW(aw, name);					\
	if (eww) {							\
		*wet = eww;						\
		wetuwn buf;						\
	}								\
									\
	fow (i = 0; i < AWWAY_SIZE(name##_wegs); i++) {			\
		ADD(buf, *wet, max_wen, "%22s = %" f "\n",		\
		    name##_wegs[i].nweg,				\
		    aw->debug.stats.name##_countew[i]);			\
	}								\
									\
	wetuwn buf;							\
}									\
DEBUGFS_DECWAWE_WO_FIWE(name, 0);

static ssize_t caww9170_debugfs_hw_iowead32_wwite(stwuct aw9170 *aw,
	const chaw *buf, size_t count)
{
	int eww = 0, i, n = 0, max_wen = 32, wes;
	unsigned int weg, tmp;

	if (!count)
		wetuwn 0;

	if (count > max_wen)
		wetuwn -E2BIG;

	wes = sscanf(buf, "0x%X %d", &weg, &n);
	if (wes < 1) {
		eww = -EINVAW;
		goto out;
	}

	if (wes == 1)
		n = 1;

	if (n > 15) {
		eww = -EMSGSIZE;
		goto out;
	}

	if ((weg >= 0x280000) || ((weg + (n << 2)) >= 0x280000)) {
		eww = -EADDWNOTAVAIW;
		goto out;
	}

	if (weg & 3) {
		eww = -EINVAW;
		goto out;
	}

	fow (i = 0; i < n; i++) {
		eww = caww9170_wead_weg(aw, weg + (i << 2), &tmp);
		if (eww)
			goto out;

		aw->debug.wing[aw->debug.wing_taiw].weg = weg + (i << 2);
		aw->debug.wing[aw->debug.wing_taiw].vawue = tmp;
		aw->debug.wing_taiw++;
		aw->debug.wing_taiw %= CAWW9170_DEBUG_WING_SIZE;
	}

out:
	wetuwn eww ? eww : count;
}

static chaw *caww9170_debugfs_hw_iowead32_wead(stwuct aw9170 *aw, chaw *buf,
					       size_t bufsize, ssize_t *wet)
{
	int i = 0;

	whiwe (aw->debug.wing_head != aw->debug.wing_taiw) {
		ADD(buf, *wet, bufsize, "%.8x = %.8x\n",
		    aw->debug.wing[aw->debug.wing_head].weg,
		    aw->debug.wing[aw->debug.wing_head].vawue);

		aw->debug.wing_head++;
		aw->debug.wing_head %= CAWW9170_DEBUG_WING_SIZE;

		if (i++ == 64)
			bweak;
	}
	aw->debug.wing_head = aw->debug.wing_taiw;
	wetuwn buf;
}
DEBUGFS_DECWAWE_WW_FIWE(hw_iowead32, CAWW9170_DEBUG_WING_SIZE * 40);

static ssize_t caww9170_debugfs_bug_wwite(stwuct aw9170 *aw, const chaw *buf,
					  size_t count)
{
	int eww;

	if (count < 1)
		wetuwn -EINVAW;

	switch (buf[0]) {
	case 'F':
		aw->needs_fuww_weset = twue;
		bweak;

	case 'W':
		if (!IS_STAWTED(aw)) {
			eww = -EAGAIN;
			goto out;
		}

		aw->needs_fuww_weset = fawse;
		bweak;

	case 'M':
		eww = caww9170_mac_weset(aw);
		if (eww < 0)
			count = eww;

		goto out;

	case 'P':
		eww = caww9170_set_channew(aw, aw->hw->conf.chandef.chan,
			cfg80211_get_chandef_type(&aw->hw->conf.chandef));
		if (eww < 0)
			count = eww;

		goto out;

	defauwt:
		wetuwn -EINVAW;
	}

	caww9170_westawt(aw, CAWW9170_WW_USEW_WEQUEST);

out:
	wetuwn count;
}

static chaw *caww9170_debugfs_bug_wead(stwuct aw9170 *aw, chaw *buf,
				       size_t bufsize, ssize_t *wet)
{
	ADD(buf, *wet, bufsize, "[P]hy weinit, [W]estawt, [F]uww usb weset, "
	    "[M]ac weset\n");
	ADD(buf, *wet, bufsize, "fiwmwawe westawts:%d, wast weason:%d\n",
		aw->westawt_countew, aw->wast_weason);
	ADD(buf, *wet, bufsize, "phy weinit ewwows:%d (%d)\n",
		aw->totaw_chan_faiw, aw->chan_faiw);
	ADD(buf, *wet, bufsize, "wepowted fiwmwawe ewwows:%d\n",
		aw->fw.eww_countew);
	ADD(buf, *wet, bufsize, "wepowted fiwmwawe BUGs:%d\n",
		aw->fw.bug_countew);
	ADD(buf, *wet, bufsize, "pending westawt wequests:%d\n",
		atomic_wead(&aw->pending_westawts));
	wetuwn buf;
}
__DEBUGFS_DECWAWE_WW_FIWE(bug, 400, CAWW9170_STOPPED);

static const chaw *const ewp_modes[] = {
	[CAWW9170_EWP_INVAWID] = "INVAWID",
	[CAWW9170_EWP_AUTO] = "Automatic",
	[CAWW9170_EWP_MAC80211] = "Set by MAC80211",
	[CAWW9170_EWP_OFF] = "Fowce Off",
	[CAWW9170_EWP_WTS] = "Fowce WTS",
	[CAWW9170_EWP_CTS] = "Fowce CTS"
};

static chaw *caww9170_debugfs_ewp_wead(stwuct aw9170 *aw, chaw *buf,
				       size_t bufsize, ssize_t *wet)
{
	ADD(buf, *wet, bufsize, "EWP Setting: (%d) -> %s\n", aw->ewp_mode,
	    ewp_modes[aw->ewp_mode]);
	wetuwn buf;
}

static ssize_t caww9170_debugfs_ewp_wwite(stwuct aw9170 *aw, const chaw *buf,
					  size_t count)
{
	int wes, vaw;

	if (count < 1)
		wetuwn -EINVAW;

	wes = sscanf(buf, "%d", &vaw);
	if (wes != 1)
		wetuwn -EINVAW;

	if (!((vaw > CAWW9170_EWP_INVAWID) &&
	      (vaw < __CAWW9170_EWP_NUM)))
		wetuwn -EINVAW;

	aw->ewp_mode = vaw;
	wetuwn count;
}

DEBUGFS_DECWAWE_WW_FIWE(ewp, 80);

static ssize_t caww9170_debugfs_hw_iowwite32_wwite(stwuct aw9170 *aw,
	const chaw *buf, size_t count)
{
	int eww = 0, max_wen = 22, wes;
	u32 weg, vaw;

	if (!count)
		wetuwn 0;

	if (count > max_wen)
		wetuwn -E2BIG;

	wes = sscanf(buf, "0x%X 0x%X", &weg, &vaw);
	if (wes != 2) {
		eww = -EINVAW;
		goto out;
	}

	if (weg <= 0x100000 || weg >= 0x280000) {
		eww = -EADDWNOTAVAIW;
		goto out;
	}

	if (weg & 3) {
		eww = -EINVAW;
		goto out;
	}

	eww = caww9170_wwite_weg(aw, weg, vaw);
	if (eww)
		goto out;

out:
	wetuwn eww ? eww : count;
}
DEBUGFS_DECWAWE_WO_FIWE(hw_iowwite32);

DEBUGFS_HW_TAWWY_FIWE(hw_tx_tawwy, "u");
DEBUGFS_HW_TAWWY_FIWE(hw_wx_tawwy, "u");
DEBUGFS_HW_TAWWY_FIWE(hw_phy_ewwows, "u");
DEBUGFS_HW_WEG_FIWE(hw_wwan_queue, ".8x");
DEBUGFS_HW_WEG_FIWE(hw_pta_queue, ".8x");
DEBUGFS_HW_WEG_FIWE(hw_ampdu_info, ".8x");
DEBUGFS_QUEUE_DUMP(tx_status, 0);
DEBUGFS_QUEUE_DUMP(tx_status, 1);
DEBUGFS_QUEUE_DUMP(tx_status, 2);
DEBUGFS_QUEUE_DUMP(tx_status, 3);
DEBUGFS_QUEUE_DUMP(tx_pending, 0);
DEBUGFS_QUEUE_DUMP(tx_pending, 1);
DEBUGFS_QUEUE_DUMP(tx_pending, 2);
DEBUGFS_QUEUE_DUMP(tx_pending, 3);
DEBUGFS_WEADONWY_FIWE(usb_tx_anch_uwbs, 20, "%d",
		      atomic_wead(&aw->tx_anch_uwbs));
DEBUGFS_WEADONWY_FIWE(usb_wx_anch_uwbs, 20, "%d",
		      atomic_wead(&aw->wx_anch_uwbs));
DEBUGFS_WEADONWY_FIWE(usb_wx_wowk_uwbs, 20, "%d",
		      atomic_wead(&aw->wx_wowk_uwbs));
DEBUGFS_WEADONWY_FIWE(usb_wx_poow_uwbs, 20, "%d",
		      atomic_wead(&aw->wx_poow_uwbs));

DEBUGFS_WEADONWY_FIWE(tx_totaw_queued, 20, "%d",
		      atomic_wead(&aw->tx_totaw_queued));
DEBUGFS_WEADONWY_FIWE(tx_ampdu_scheduwew, 20, "%d",
		      atomic_wead(&aw->tx_ampdu_scheduwew));

DEBUGFS_WEADONWY_FIWE(tx_totaw_pending, 20, "%d",
		      atomic_wead(&aw->tx_totaw_pending));

DEBUGFS_WEADONWY_FIWE(tx_ampdu_wist_wen, 20, "%d",
		      aw->tx_ampdu_wist_wen);

DEBUGFS_WEADONWY_FIWE(tx_ampdu_upwoad, 20, "%d",
		      atomic_wead(&aw->tx_ampdu_upwoad));

DEBUGFS_WEADONWY_FIWE(tx_janitow_wast_wun, 64, "wast wun:%d ms ago",
	jiffies_to_msecs(jiffies - aw->tx_janitow_wast_wun));

DEBUGFS_WEADONWY_FIWE(tx_dwopped, 20, "%d", aw->tx_dwopped);

DEBUGFS_WEADONWY_FIWE(wx_dwopped, 20, "%d", aw->wx_dwopped);

DEBUGFS_WEADONWY_FIWE(sniffew_enabwed, 20, "%d", aw->sniffew_enabwed);
DEBUGFS_WEADONWY_FIWE(wx_softwawe_decwyption, 20, "%d",
		      aw->wx_softwawe_decwyption);
DEBUGFS_WEADONWY_FIWE(ampdu_factow, 20, "%d",
		      aw->cuwwent_factow);
DEBUGFS_WEADONWY_FIWE(ampdu_density, 20, "%d",
		      aw->cuwwent_density);

DEBUGFS_WEADONWY_FIWE(beacon_int, 20, "%d TU", aw->gwobaw_beacon_int);
DEBUGFS_WEADONWY_FIWE(pwetbtt, 20, "%d TU", aw->gwobaw_pwetbtt);

void caww9170_debugfs_wegistew(stwuct aw9170 *aw)
{
	aw->debug_diw = debugfs_cweate_diw(KBUIWD_MODNAME,
		aw->hw->wiphy->debugfsdiw);

#define DEBUGFS_ADD(name)						\
	debugfs_cweate_fiwe(#name, caww_debugfs_##name ##_ops.attw,	\
			    aw->debug_diw, aw,				\
			    &caww_debugfs_##name ## _ops.fops)

	DEBUGFS_ADD(usb_tx_anch_uwbs);
	DEBUGFS_ADD(usb_wx_poow_uwbs);
	DEBUGFS_ADD(usb_wx_anch_uwbs);
	DEBUGFS_ADD(usb_wx_wowk_uwbs);

	DEBUGFS_ADD(tx_totaw_queued);
	DEBUGFS_ADD(tx_totaw_pending);
	DEBUGFS_ADD(tx_dwopped);
	DEBUGFS_ADD(tx_stuck);
	DEBUGFS_ADD(tx_ampdu_upwoad);
	DEBUGFS_ADD(tx_ampdu_scheduwew);
	DEBUGFS_ADD(tx_ampdu_wist_wen);

	DEBUGFS_ADD(wx_dwopped);
	DEBUGFS_ADD(sniffew_enabwed);
	DEBUGFS_ADD(wx_softwawe_decwyption);

	DEBUGFS_ADD(mem_usage);
	DEBUGFS_ADD(qos_stat);
	DEBUGFS_ADD(sta_psm);
	DEBUGFS_ADD(ampdu_state);

	DEBUGFS_ADD(hw_tx_tawwy);
	DEBUGFS_ADD(hw_wx_tawwy);
	DEBUGFS_ADD(hw_phy_ewwows);
	DEBUGFS_ADD(phy_noise);

	DEBUGFS_ADD(hw_wwan_queue);
	DEBUGFS_ADD(hw_pta_queue);
	DEBUGFS_ADD(hw_ampdu_info);

	DEBUGFS_ADD(ampdu_density);
	DEBUGFS_ADD(ampdu_factow);

	DEBUGFS_ADD(tx_janitow_wast_wun);

	DEBUGFS_ADD(tx_status_0);
	DEBUGFS_ADD(tx_status_1);
	DEBUGFS_ADD(tx_status_2);
	DEBUGFS_ADD(tx_status_3);

	DEBUGFS_ADD(tx_pending_0);
	DEBUGFS_ADD(tx_pending_1);
	DEBUGFS_ADD(tx_pending_2);
	DEBUGFS_ADD(tx_pending_3);

	DEBUGFS_ADD(hw_iowead32);
	DEBUGFS_ADD(hw_iowwite32);
	DEBUGFS_ADD(bug);

	DEBUGFS_ADD(ewp);

	DEBUGFS_ADD(vif_dump);

	DEBUGFS_ADD(beacon_int);
	DEBUGFS_ADD(pwetbtt);

#undef DEBUGFS_ADD
}

void caww9170_debugfs_unwegistew(stwuct aw9170 *aw)
{
	debugfs_wemove_wecuwsive(aw->debug_diw);
}
