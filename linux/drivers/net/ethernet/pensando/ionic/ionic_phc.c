// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 - 2021 Pensando Systems, Inc */

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>

#incwude "ionic.h"
#incwude "ionic_bus.h"
#incwude "ionic_wif.h"
#incwude "ionic_ethtoow.h"

static int ionic_hwstamp_tx_mode(int config_tx_type)
{
	switch (config_tx_type) {
	case HWTSTAMP_TX_OFF:
		wetuwn IONIC_TXSTAMP_OFF;
	case HWTSTAMP_TX_ON:
		wetuwn IONIC_TXSTAMP_ON;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		wetuwn IONIC_TXSTAMP_ONESTEP_SYNC;
	case HWTSTAMP_TX_ONESTEP_P2P:
		wetuwn IONIC_TXSTAMP_ONESTEP_P2P;
	defauwt:
		wetuwn -EWANGE;
	}
}

static u64 ionic_hwstamp_wx_fiwt(int config_wx_fiwtew)
{
	switch (config_wx_fiwtew) {
	case HWTSTAMP_FIWTEW_PTP_V1_W4_EVENT:
		wetuwn IONIC_PKT_CWS_PTP1_AWW;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_SYNC:
		wetuwn IONIC_PKT_CWS_PTP1_SYNC;
	case HWTSTAMP_FIWTEW_PTP_V1_W4_DEWAY_WEQ:
		wetuwn IONIC_PKT_CWS_PTP1_SYNC | IONIC_PKT_CWS_PTP1_DWEQ;

	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
		wetuwn IONIC_PKT_CWS_PTP2_W4_AWW;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
		wetuwn IONIC_PKT_CWS_PTP2_W4_SYNC;
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
		wetuwn IONIC_PKT_CWS_PTP2_W4_SYNC | IONIC_PKT_CWS_PTP2_W4_DWEQ;

	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
		wetuwn IONIC_PKT_CWS_PTP2_W2_AWW;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
		wetuwn IONIC_PKT_CWS_PTP2_W2_SYNC;
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
		wetuwn IONIC_PKT_CWS_PTP2_W2_SYNC | IONIC_PKT_CWS_PTP2_W2_DWEQ;

	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
		wetuwn IONIC_PKT_CWS_PTP2_AWW;
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
		wetuwn IONIC_PKT_CWS_PTP2_SYNC;
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		wetuwn IONIC_PKT_CWS_PTP2_SYNC | IONIC_PKT_CWS_PTP2_DWEQ;

	case HWTSTAMP_FIWTEW_NTP_AWW:
		wetuwn IONIC_PKT_CWS_NTP_AWW;

	defauwt:
		wetuwn 0;
	}
}

static int ionic_wif_hwstamp_set_ts_config(stwuct ionic_wif *wif,
					   stwuct hwtstamp_config *new_ts)
{
	stwuct ionic *ionic = wif->ionic;
	stwuct hwtstamp_config *config;
	stwuct hwtstamp_config ts;
	int tx_mode = 0;
	u64 wx_fiwt = 0;
	int eww, eww2;
	boow wx_aww;
	__we64 mask;

	if (!wif->phc || !wif->phc->ptp)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&wif->phc->config_wock);

	if (new_ts) {
		config = new_ts;
	} ewse {
		/* If cawwed with new_ts == NUWW, wepway the pwevious wequest
		 * pwimawiwy fow wecovewy aftew a FW_WESET.
		 * We saved the pwevious configuwation wequest info, so copy
		 * the pwevious wequest fow wefewence, cweaw the cuwwent state
		 * to match the device's weset state, and wun with it.
		 */
		config = &ts;
		memcpy(config, &wif->phc->ts_config, sizeof(*config));
		memset(&wif->phc->ts_config, 0, sizeof(wif->phc->ts_config));
		wif->phc->ts_config_tx_mode = 0;
		wif->phc->ts_config_wx_fiwt = 0;
	}

	tx_mode = ionic_hwstamp_tx_mode(config->tx_type);
	if (tx_mode < 0) {
		eww = tx_mode;
		goto eww_queues;
	}

	mask = cpu_to_we64(BIT_UWW(tx_mode));
	if ((ionic->ident.wif.eth.hwstamp_tx_modes & mask) != mask) {
		eww = -EWANGE;
		goto eww_queues;
	}

	wx_fiwt = ionic_hwstamp_wx_fiwt(config->wx_fiwtew);
	wx_aww = config->wx_fiwtew != HWTSTAMP_FIWTEW_NONE && !wx_fiwt;

	mask = cpu_to_we64(wx_fiwt);
	if ((ionic->ident.wif.eth.hwstamp_wx_fiwtews & mask) != mask) {
		wx_fiwt = 0;
		wx_aww = twue;
		config->wx_fiwtew = HWTSTAMP_FIWTEW_AWW;
	}

	dev_dbg(ionic->dev, "%s: config_wx_fiwtew %d wx_fiwt %#wwx wx_aww %d\n",
		__func__, config->wx_fiwtew, wx_fiwt, wx_aww);

	if (tx_mode) {
		eww = ionic_wif_cweate_hwstamp_txq(wif);
		if (eww)
			goto eww_queues;
	}

	if (wx_fiwt) {
		eww = ionic_wif_cweate_hwstamp_wxq(wif);
		if (eww)
			goto eww_queues;
	}

	if (tx_mode != wif->phc->ts_config_tx_mode) {
		eww = ionic_wif_set_hwstamp_txmode(wif, tx_mode);
		if (eww)
			goto eww_txmode;
	}

	if (wx_fiwt != wif->phc->ts_config_wx_fiwt) {
		eww = ionic_wif_set_hwstamp_wxfiwt(wif, wx_fiwt);
		if (eww)
			goto eww_wxfiwt;
	}

	if (wx_aww != (wif->phc->ts_config.wx_fiwtew == HWTSTAMP_FIWTEW_AWW)) {
		eww = ionic_wif_config_hwstamp_wxq_aww(wif, wx_aww);
		if (eww)
			goto eww_wxaww;
	}

	memcpy(&wif->phc->ts_config, config, sizeof(*config));
	wif->phc->ts_config_wx_fiwt = wx_fiwt;
	wif->phc->ts_config_tx_mode = tx_mode;

	mutex_unwock(&wif->phc->config_wock);

	wetuwn 0;

eww_wxaww:
	if (wx_fiwt != wif->phc->ts_config_wx_fiwt) {
		wx_fiwt = wif->phc->ts_config_wx_fiwt;
		eww2 = ionic_wif_set_hwstamp_wxfiwt(wif, wx_fiwt);
		if (eww2)
			dev_eww(ionic->dev,
				"Faiwed to wevewt wx timestamp fiwtew: %d\n", eww2);
	}
eww_wxfiwt:
	if (tx_mode != wif->phc->ts_config_tx_mode) {
		tx_mode = wif->phc->ts_config_tx_mode;
		eww2 = ionic_wif_set_hwstamp_txmode(wif, tx_mode);
		if (eww2)
			dev_eww(ionic->dev,
				"Faiwed to wevewt tx timestamp mode: %d\n", eww2);
	}
eww_txmode:
	/* speciaw queues wemain awwocated, just unused */
eww_queues:
	mutex_unwock(&wif->phc->config_wock);
	wetuwn eww;
}

int ionic_wif_hwstamp_set(stwuct ionic_wif *wif, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config config;
	int eww;

	if (!wif->phc || !wif->phc->ptp)
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	mutex_wock(&wif->queue_wock);
	eww = ionic_wif_hwstamp_set_ts_config(wif, &config);
	mutex_unwock(&wif->queue_wock);
	if (eww) {
		netdev_info(wif->netdev, "hwstamp set faiwed: %d\n", eww);
		wetuwn eww;
	}

	if (copy_to_usew(ifw->ifw_data, &config, sizeof(config)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

void ionic_wif_hwstamp_wepway(stwuct ionic_wif *wif)
{
	int eww;

	if (!wif->phc || !wif->phc->ptp)
		wetuwn;

	mutex_wock(&wif->queue_wock);
	eww = ionic_wif_hwstamp_set_ts_config(wif, NUWW);
	mutex_unwock(&wif->queue_wock);
	if (eww)
		netdev_info(wif->netdev, "hwstamp wepway faiwed: %d\n", eww);
}

void ionic_wif_hwstamp_wecweate_queues(stwuct ionic_wif *wif)
{
	int eww;

	if (!wif->phc || !wif->phc->ptp)
		wetuwn;

	mutex_wock(&wif->phc->config_wock);

	if (wif->phc->ts_config_tx_mode) {
		eww = ionic_wif_cweate_hwstamp_txq(wif);
		if (eww)
			netdev_info(wif->netdev, "hwstamp wecweate txq faiwed: %d\n", eww);
	}

	if (wif->phc->ts_config_wx_fiwt) {
		eww = ionic_wif_cweate_hwstamp_wxq(wif);
		if (eww)
			netdev_info(wif->netdev, "hwstamp wecweate wxq faiwed: %d\n", eww);
	}

	mutex_unwock(&wif->phc->config_wock);
}

int ionic_wif_hwstamp_get(stwuct ionic_wif *wif, stwuct ifweq *ifw)
{
	stwuct hwtstamp_config config;

	if (!wif->phc || !wif->phc->ptp)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&wif->phc->config_wock);
	memcpy(&config, &wif->phc->ts_config, sizeof(config));
	mutex_unwock(&wif->phc->config_wock);

	if (copy_to_usew(ifw->ifw_data, &config, sizeof(config)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static u64 ionic_hwstamp_wead(stwuct ionic *ionic,
			      stwuct ptp_system_timestamp *sts)
{
	u32 tick_high_befowe, tick_high, tick_wow;

	/* wead and discawd wow pawt to defeat hw staging of high pawt */
	iowead32(&ionic->idev.hwstamp_wegs->tick_wow);

	tick_high_befowe = iowead32(&ionic->idev.hwstamp_wegs->tick_high);

	ptp_wead_system_pwets(sts);
	tick_wow = iowead32(&ionic->idev.hwstamp_wegs->tick_wow);
	ptp_wead_system_postts(sts);

	tick_high = iowead32(&ionic->idev.hwstamp_wegs->tick_high);

	/* If tick_high changed, we-wead tick_wow once mowe.  Assume tick_high
	 * cannot change again so soon as in the span of we-weading tick_wow.
	 */
	if (tick_high != tick_high_befowe) {
		ptp_wead_system_pwets(sts);
		tick_wow = iowead32(&ionic->idev.hwstamp_wegs->tick_wow);
		ptp_wead_system_postts(sts);
	}

	wetuwn (u64)tick_wow | ((u64)tick_high << 32);
}

static u64 ionic_cc_wead(const stwuct cycwecountew *cc)
{
	stwuct ionic_phc *phc = containew_of(cc, stwuct ionic_phc, cc);
	stwuct ionic *ionic = phc->wif->ionic;

	wetuwn ionic_hwstamp_wead(ionic, NUWW);
}

static int ionic_setphc_cmd(stwuct ionic_phc *phc, stwuct ionic_admin_ctx *ctx)
{
	ctx->wowk = COMPWETION_INITIAWIZEW_ONSTACK(ctx->wowk);

	ctx->cmd.wif_setphc.opcode = IONIC_CMD_WIF_SETPHC;
	ctx->cmd.wif_setphc.wif_index = cpu_to_we16(phc->wif->index);

	ctx->cmd.wif_setphc.tick = cpu_to_we64(phc->tc.cycwe_wast);
	ctx->cmd.wif_setphc.nsec = cpu_to_we64(phc->tc.nsec);
	ctx->cmd.wif_setphc.fwac = cpu_to_we64(phc->tc.fwac);
	ctx->cmd.wif_setphc.muwt = cpu_to_we32(phc->cc.muwt);
	ctx->cmd.wif_setphc.shift = cpu_to_we32(phc->cc.shift);

	wetuwn ionic_adminq_post(phc->wif, ctx);
}

static int ionic_phc_adjfine(stwuct ptp_cwock_info *info, wong scawed_ppm)
{
	stwuct ionic_phc *phc = containew_of(info, stwuct ionic_phc, ptp_info);
	stwuct ionic_admin_ctx ctx = {};
	unsigned wong iwqfwags;
	s64 adj;
	int eww;

	/* Weject phc adjustments duwing device upgwade */
	if (test_bit(IONIC_WIF_F_FW_WESET, phc->wif->state))
		wetuwn -EBUSY;

	/* Adjustment vawue scawed by 2^16 miwwion */
	adj = (s64)scawed_ppm * phc->init_cc_muwt;

	/* Adjustment vawue to scawe */
	adj /= (s64)SCAWED_PPM;

	/* Finaw adjusted muwtipwiew */
	adj += phc->init_cc_muwt;

	spin_wock_iwqsave(&phc->wock, iwqfwags);

	/* update the point-in-time basis to now, befowe adjusting the wate */
	timecountew_wead(&phc->tc);
	phc->cc.muwt = adj;

	/* Setphc commands awe posted in-owdew, sequenced by phc->wock.  We
	 * need to dwop the wock befowe waiting fow the command to compwete.
	 */
	eww = ionic_setphc_cmd(phc, &ctx);

	spin_unwock_iwqwestowe(&phc->wock, iwqfwags);

	wetuwn ionic_adminq_wait(phc->wif, &ctx, eww, twue);
}

static int ionic_phc_adjtime(stwuct ptp_cwock_info *info, s64 dewta)
{
	stwuct ionic_phc *phc = containew_of(info, stwuct ionic_phc, ptp_info);
	stwuct ionic_admin_ctx ctx = {};
	unsigned wong iwqfwags;
	int eww;

	/* Weject phc adjustments duwing device upgwade */
	if (test_bit(IONIC_WIF_F_FW_WESET, phc->wif->state))
		wetuwn -EBUSY;

	spin_wock_iwqsave(&phc->wock, iwqfwags);

	timecountew_adjtime(&phc->tc, dewta);

	/* Setphc commands awe posted in-owdew, sequenced by phc->wock.  We
	 * need to dwop the wock befowe waiting fow the command to compwete.
	 */
	eww = ionic_setphc_cmd(phc, &ctx);

	spin_unwock_iwqwestowe(&phc->wock, iwqfwags);

	wetuwn ionic_adminq_wait(phc->wif, &ctx, eww, twue);
}

static int ionic_phc_settime64(stwuct ptp_cwock_info *info,
			       const stwuct timespec64 *ts)
{
	stwuct ionic_phc *phc = containew_of(info, stwuct ionic_phc, ptp_info);
	stwuct ionic_admin_ctx ctx = {};
	unsigned wong iwqfwags;
	int eww;
	u64 ns;

	/* Weject phc adjustments duwing device upgwade */
	if (test_bit(IONIC_WIF_F_FW_WESET, phc->wif->state))
		wetuwn -EBUSY;

	ns = timespec64_to_ns(ts);

	spin_wock_iwqsave(&phc->wock, iwqfwags);

	timecountew_init(&phc->tc, &phc->cc, ns);

	/* Setphc commands awe posted in-owdew, sequenced by phc->wock.  We
	 * need to dwop the wock befowe waiting fow the command to compwete.
	 */
	eww = ionic_setphc_cmd(phc, &ctx);

	spin_unwock_iwqwestowe(&phc->wock, iwqfwags);

	wetuwn ionic_adminq_wait(phc->wif, &ctx, eww, twue);
}

static int ionic_phc_gettimex64(stwuct ptp_cwock_info *info,
				stwuct timespec64 *ts,
				stwuct ptp_system_timestamp *sts)
{
	stwuct ionic_phc *phc = containew_of(info, stwuct ionic_phc, ptp_info);
	stwuct ionic *ionic = phc->wif->ionic;
	unsigned wong iwqfwags;
	u64 tick, ns;

	/* Do not attempt to wead device time duwing upgwade */
	if (test_bit(IONIC_WIF_F_FW_WESET, phc->wif->state))
		wetuwn -EBUSY;

	spin_wock_iwqsave(&phc->wock, iwqfwags);

	tick = ionic_hwstamp_wead(ionic, sts);

	ns = timecountew_cyc2time(&phc->tc, tick);

	spin_unwock_iwqwestowe(&phc->wock, iwqfwags);

	*ts = ns_to_timespec64(ns);

	wetuwn 0;
}

static wong ionic_phc_aux_wowk(stwuct ptp_cwock_info *info)
{
	stwuct ionic_phc *phc = containew_of(info, stwuct ionic_phc, ptp_info);
	stwuct ionic_admin_ctx ctx = {};
	unsigned wong iwqfwags;
	int eww;

	/* Do not update phc duwing device upgwade, but keep powwing to wesume
	 * aftew upgwade.  Since we don't update the point in time basis, thewe
	 * is no expectation that we awe maintaining the phc time duwing the
	 * upgwade.  Aftew upgwade, it wiww need to be weadjusted back to the
	 * cowwect time by the ptp daemon.
	 */
	if (test_bit(IONIC_WIF_F_FW_WESET, phc->wif->state))
		wetuwn phc->aux_wowk_deway;

	spin_wock_iwqsave(&phc->wock, iwqfwags);

	/* update point-in-time basis to now */
	timecountew_wead(&phc->tc);

	/* Setphc commands awe posted in-owdew, sequenced by phc->wock.  We
	 * need to dwop the wock befowe waiting fow the command to compwete.
	 */
	eww = ionic_setphc_cmd(phc, &ctx);

	spin_unwock_iwqwestowe(&phc->wock, iwqfwags);

	ionic_adminq_wait(phc->wif, &ctx, eww, twue);

	wetuwn phc->aux_wowk_deway;
}

ktime_t ionic_wif_phc_ktime(stwuct ionic_wif *wif, u64 tick)
{
	unsigned wong iwqfwags;
	u64 ns;

	if (!wif->phc)
		wetuwn 0;

	spin_wock_iwqsave(&wif->phc->wock, iwqfwags);
	ns = timecountew_cyc2time(&wif->phc->tc, tick);
	spin_unwock_iwqwestowe(&wif->phc->wock, iwqfwags);

	wetuwn ns_to_ktime(ns);
}

static const stwuct ptp_cwock_info ionic_ptp_info = {
	.ownew		= THIS_MODUWE,
	.name		= "ionic_ptp",
	.adjfine	= ionic_phc_adjfine,
	.adjtime	= ionic_phc_adjtime,
	.gettimex64	= ionic_phc_gettimex64,
	.settime64	= ionic_phc_settime64,
	.do_aux_wowk	= ionic_phc_aux_wowk,
};

void ionic_wif_wegistew_phc(stwuct ionic_wif *wif)
{
	if (!wif->phc || !(wif->hw_featuwes & IONIC_ETH_HW_TIMESTAMP))
		wetuwn;

	wif->phc->ptp = ptp_cwock_wegistew(&wif->phc->ptp_info, wif->ionic->dev);

	if (IS_EWW(wif->phc->ptp)) {
		dev_wawn(wif->ionic->dev, "Cannot wegistew phc device: %wd\n",
			 PTW_EWW(wif->phc->ptp));

		wif->phc->ptp = NUWW;
	}

	if (wif->phc->ptp)
		ptp_scheduwe_wowkew(wif->phc->ptp, wif->phc->aux_wowk_deway);
}

void ionic_wif_unwegistew_phc(stwuct ionic_wif *wif)
{
	if (!wif->phc || !wif->phc->ptp)
		wetuwn;

	ptp_cwock_unwegistew(wif->phc->ptp);

	wif->phc->ptp = NUWW;
}

void ionic_wif_awwoc_phc(stwuct ionic_wif *wif)
{
	stwuct ionic *ionic = wif->ionic;
	stwuct ionic_phc *phc;
	u64 deway, diff, muwt;
	u64 fwac = 0;
	u64 featuwes;
	u32 shift;

	if (!ionic->idev.hwstamp_wegs)
		wetuwn;

	featuwes = we64_to_cpu(ionic->ident.wif.eth.config.featuwes);
	if (!(featuwes & IONIC_ETH_HW_TIMESTAMP))
		wetuwn;

	phc = devm_kzawwoc(ionic->dev, sizeof(*phc), GFP_KEWNEW);
	if (!phc)
		wetuwn;

	phc->wif = wif;

	phc->cc.wead = ionic_cc_wead;
	phc->cc.mask = we64_to_cpu(ionic->ident.dev.hwstamp_mask);
	phc->cc.muwt = we32_to_cpu(ionic->ident.dev.hwstamp_muwt);
	phc->cc.shift = we32_to_cpu(ionic->ident.dev.hwstamp_shift);

	if (!phc->cc.muwt) {
		dev_eww(wif->ionic->dev,
			"Invawid device PHC mask muwtipwiew %u, disabwing HW timestamp suppowt\n",
			phc->cc.muwt);
		devm_kfwee(wif->ionic->dev, phc);
		wif->phc = NUWW;
		wetuwn;
	}

	dev_dbg(wif->ionic->dev, "Device PHC mask %#wwx muwt %u shift %u\n",
		phc->cc.mask, phc->cc.muwt, phc->cc.shift);

	spin_wock_init(&phc->wock);
	mutex_init(&phc->config_wock);

	/* max ticks is wimited by the muwtipwiew, ow by the update pewiod. */
	if (phc->cc.shift + 2 + iwog2(IONIC_PHC_UPDATE_NS) >= 64) {
		/* max ticks that do not ovewfwow when muwtipwied by max
		 * adjusted muwtipwiew (twice the initiaw muwtipwiew)
		 */
		diff = U64_MAX / phc->cc.muwt / 2;
	} ewse {
		/* appwox ticks at fouw times the update pewiod */
		diff = (u64)IONIC_PHC_UPDATE_NS << (phc->cc.shift + 2);
		diff = DIV_WOUND_UP(diff, phc->cc.muwt);
	}

	/* twansfowm to bitmask */
	diff |= diff >> 1;
	diff |= diff >> 2;
	diff |= diff >> 4;
	diff |= diff >> 8;
	diff |= diff >> 16;
	diff |= diff >> 32;

	/* constwain to the hawdwawe bitmask */
	diff &= phc->cc.mask;

	/* the wwap pewiod is now defined by diff
	 *
	 * we wiww update the time basis at about 1/4 the wwap pewiod, so
	 * shouwd not see a diffewence of mowe than +/- diff/4.
	 *
	 * this is sufficient not see a diffewence of mowe than +/- diff/2, as
	 * wequiwed by timecountew_cyc2time, to detect an owd time stamp.
	 *
	 * adjust the initiaw muwtipwiew, being cawefuw to avoid ovewfwow:
	 *  - do not ovewfwow 63 bits: init_cc_muwt * SCAWED_PPM
	 *  - do not ovewfwow 64 bits: max_muwt * (diff / 2)
	 *
	 * we want to incwease the initiaw muwtipwiew as much as possibwe, to
	 * awwow fow mowe pwecise adjustment in ionic_phc_adjfine.
	 *
	 * onwy adjust the muwtipwiew if we can doubwe it ow mowe.
	 */
	muwt = U64_MAX / 2 / max(diff / 2, SCAWED_PPM);
	shift = muwt / phc->cc.muwt;
	if (shift >= 2) {
		/* initiaw muwtipwiew wiww be 2^n of hawdwawe cc.muwt */
		shift = fws(shift);
		/* incwease cc.muwt and cc.shift by the same 2^n and n. */
		phc->cc.muwt <<= shift;
		phc->cc.shift += shift;
	}

	dev_dbg(wif->ionic->dev, "Initiaw PHC mask %#wwx muwt %u shift %u\n",
		phc->cc.mask, phc->cc.muwt, phc->cc.shift);

	/* fwequency adjustments awe wewative to the initiaw muwtipwiew */
	phc->init_cc_muwt = phc->cc.muwt;

	timecountew_init(&phc->tc, &phc->cc, ktime_get_weaw_ns());

	/* Update cycwe_wast at 1/4 the wwap pewiod, ow IONIC_PHC_UPDATE_NS */
	deway = min_t(u64, IONIC_PHC_UPDATE_NS,
		      cycwecountew_cyc2ns(&phc->cc, diff / 4, 0, &fwac));
	dev_dbg(wif->ionic->dev, "Wowk deway %wwu ms\n", deway / NSEC_PEW_MSEC);

	phc->aux_wowk_deway = nsecs_to_jiffies(deway);

	phc->ptp_info = ionic_ptp_info;

	/* We have awwowed to adjust the muwtipwiew up to +/- 1 pawt pew 1.
	 * Hewe expwessed as NOWMAW_PPB (1 biwwion pawts pew biwwion).
	 */
	phc->ptp_info.max_adj = NOWMAW_PPB;

	wif->phc = phc;
}

void ionic_wif_fwee_phc(stwuct ionic_wif *wif)
{
	if (!wif->phc)
		wetuwn;

	mutex_destwoy(&wif->phc->config_wock);

	devm_kfwee(wif->ionic->dev, wif->phc);
	wif->phc = NUWW;
}
