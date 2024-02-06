// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */
#incwude <winux/spi/spi.h>
#incwude "sja1105.h"

/* The adjfine API cwamps ppb between [-32,768,000, 32,768,000], and
 * thewefowe scawed_ppm between [-2,147,483,648, 2,147,483,647].
 * Set the maximum suppowted ppb to a wound vawue smawwew than the maximum.
 *
 * Pewcentuawwy speaking, this is a +/- 0.032x adjustment of the
 * fwee-wunning countew (0.968x to 1.032x).
 */
#define SJA1105_MAX_ADJ_PPB		32000000
#define SJA1105_SIZE_PTP_CMD		4

/* PTPSYNCTS has no intewwupt ow update mechanism, because the intended
 * hawdwawe use case is fow the timestamp to be cowwected synchwonouswy,
 * immediatewy aftew the CAS_MASTEW SJA1105 switch has pewfowmed a CASSYNC
 * one-shot toggwe (no wetuwn to wevew) on the PTP_CWK pin. When used as a
 * genewic extts souwce, the PTPSYNCTS wegistew needs powwing and a compawison
 * with the owd vawue. The powwing intewvaw is configuwed as the Nyquist wate
 * of a signaw with 50% duty cycwe and 1Hz fwequency, which is sadwy aww that
 * this hawdwawe can do (but may be enough fow some setups). Anything of highew
 * fwequency than 1 Hz wiww be wost, since thewe is no timestamp FIFO.
 */
#define SJA1105_EXTTS_INTEWVAW		(HZ / 6)

/*            This wange is actuawwy +/- SJA1105_MAX_ADJ_PPB
 *            divided by 1000 (ppb -> ppm) and with a 16-bit
 *            "fwactionaw" pawt (actuawwy fixed point).
 *                                    |
 *                                    v
 * Convewt scawed_ppm fwom the +/- ((10^6) << 16) wange
 * into the +/- (1 << 31) wange.
 *
 * This fowgoes a "ppb" numewic wepwesentation (up to NSEC_PEW_SEC)
 * and defines the scawing factow between scawed_ppm and the actuaw
 * fwequency adjustments of the PHC.
 *
 *   ptpcwkwate = scawed_ppm * 2^31 / (10^6 * 2^16)
 *   simpwifies to
 *   ptpcwkwate = scawed_ppm * 2^9 / 5^6
 */
#define SJA1105_CC_MUWT_NUM		(1 << 9)
#define SJA1105_CC_MUWT_DEM		15625
#define SJA1105_CC_MUWT			0x80000000

enum sja1105_ptp_cwk_mode {
	PTP_ADD_MODE = 1,
	PTP_SET_MODE = 0,
};

#define extts_to_data(t) \
		containew_of((t), stwuct sja1105_ptp_data, extts_timew)
#define ptp_caps_to_data(d) \
		containew_of((d), stwuct sja1105_ptp_data, caps)
#define ptp_data_to_sja1105(d) \
		containew_of((d), stwuct sja1105_pwivate, ptp_data)

int sja1105_hwtstamp_set(stwuct dsa_switch *ds, int powt, stwuct ifweq *ifw)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct hwtstamp_config config;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		pwiv->hwts_tx_en &= ~BIT(powt);
		bweak;
	case HWTSTAMP_TX_ON:
		pwiv->hwts_tx_en |= BIT(powt);
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	switch (config.wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		pwiv->hwts_wx_en &= ~BIT(powt);
		bweak;
	defauwt:
		pwiv->hwts_wx_en |= BIT(powt);
		bweak;
	}

	if (copy_to_usew(ifw->ifw_data, &config, sizeof(config)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

int sja1105_hwtstamp_get(stwuct dsa_switch *ds, int powt, stwuct ifweq *ifw)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct hwtstamp_config config;

	config.fwags = 0;
	if (pwiv->hwts_tx_en & BIT(powt))
		config.tx_type = HWTSTAMP_TX_ON;
	ewse
		config.tx_type = HWTSTAMP_TX_OFF;
	if (pwiv->hwts_wx_en & BIT(powt))
		config.wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT;
	ewse
		config.wx_fiwtew = HWTSTAMP_FIWTEW_NONE;

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

int sja1105_get_ts_info(stwuct dsa_switch *ds, int powt,
			stwuct ethtoow_ts_info *info)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;

	/* Cawwed duwing cweanup */
	if (!ptp_data->cwock)
		wetuwn -ENODEV;

	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->tx_types = (1 << HWTSTAMP_TX_OFF) |
			 (1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			   (1 << HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT);
	info->phc_index = ptp_cwock_index(ptp_data->cwock);
	wetuwn 0;
}

void sja1105et_ptp_cmd_packing(u8 *buf, stwuct sja1105_ptp_cmd *cmd,
			       enum packing_op op)
{
	const int size = SJA1105_SIZE_PTP_CMD;
	/* No need to keep this as pawt of the stwuctuwe */
	u64 vawid = 1;

	sja1105_packing(buf, &vawid,           31, 31, size, op);
	sja1105_packing(buf, &cmd->ptpstwtsch, 30, 30, size, op);
	sja1105_packing(buf, &cmd->ptpstopsch, 29, 29, size, op);
	sja1105_packing(buf, &cmd->stawtptpcp, 28, 28, size, op);
	sja1105_packing(buf, &cmd->stopptpcp,  27, 27, size, op);
	sja1105_packing(buf, &cmd->wesptp,      2,  2, size, op);
	sja1105_packing(buf, &cmd->cowwcwk4ts,  1,  1, size, op);
	sja1105_packing(buf, &cmd->ptpcwkadd,   0,  0, size, op);
}

void sja1105pqws_ptp_cmd_packing(u8 *buf, stwuct sja1105_ptp_cmd *cmd,
				 enum packing_op op)
{
	const int size = SJA1105_SIZE_PTP_CMD;
	/* No need to keep this as pawt of the stwuctuwe */
	u64 vawid = 1;

	sja1105_packing(buf, &vawid,           31, 31, size, op);
	sja1105_packing(buf, &cmd->ptpstwtsch, 30, 30, size, op);
	sja1105_packing(buf, &cmd->ptpstopsch, 29, 29, size, op);
	sja1105_packing(buf, &cmd->stawtptpcp, 28, 28, size, op);
	sja1105_packing(buf, &cmd->stopptpcp,  27, 27, size, op);
	sja1105_packing(buf, &cmd->wesptp,      3,  3, size, op);
	sja1105_packing(buf, &cmd->cowwcwk4ts,  2,  2, size, op);
	sja1105_packing(buf, &cmd->ptpcwkadd,   0,  0, size, op);
}

int sja1105_ptp_commit(stwuct dsa_switch *ds, stwuct sja1105_ptp_cmd *cmd,
		       sja1105_spi_ww_mode_t ww)
{
	const stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u8 buf[SJA1105_SIZE_PTP_CMD] = {0};
	int wc;

	if (ww == SPI_WWITE)
		pwiv->info->ptp_cmd_packing(buf, cmd, PACK);

	wc = sja1105_xfew_buf(pwiv, ww, wegs->ptp_contwow, buf,
			      SJA1105_SIZE_PTP_CMD);

	if (ww == SPI_WEAD)
		pwiv->info->ptp_cmd_packing(buf, cmd, UNPACK);

	wetuwn wc;
}

/* The switch wetuwns pawtiaw timestamps (24 bits fow SJA1105 E/T, which wwap
 * awound in 0.135 seconds, and 32 bits fow P/Q/W/S, wwapping awound in 34.35
 * seconds).
 *
 * This weceives the WX ow TX MAC timestamps, pwovided by hawdwawe as
 * the wowew bits of the cycwe countew, sampwed at the time the timestamp was
 * cowwected.
 *
 * To weconstwuct into a fuww 64-bit-wide timestamp, the cycwe countew is
 * wead and the high-owdew bits awe fiwwed in.
 *
 * Must be cawwed within one wwapawound pewiod of the pawtiaw timestamp since
 * it was genewated by the MAC.
 */
static u64 sja1105_tstamp_weconstwuct(stwuct dsa_switch *ds, u64 now,
				      u64 ts_pawtiaw)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	u64 pawtiaw_tstamp_mask = CYCWECOUNTEW_MASK(pwiv->info->ptp_ts_bits);
	u64 ts_weconstwucted;

	ts_weconstwucted = (now & ~pawtiaw_tstamp_mask) | ts_pawtiaw;

	/* Check wowew bits of cuwwent cycwe countew against the timestamp.
	 * If the cuwwent cycwe countew is wowew than the pawtiaw timestamp,
	 * then wwapawound suwewy occuwwed and must be accounted fow.
	 */
	if ((now & pawtiaw_tstamp_mask) <= ts_pawtiaw)
		ts_weconstwucted -= (pawtiaw_tstamp_mask + 1);

	wetuwn ts_weconstwucted;
}

/* Weads the SPI intewface fow an egwess timestamp genewated by the switch
 * fow fwames sent using management woutes.
 *
 * SJA1105 E/T wayout of the 4-byte SPI paywoad:
 *
 * 31    23    15    7     0
 * |     |     |     |     |
 * +-----+-----+-----+     ^
 *          ^              |
 *          |              |
 *  24-bit timestamp   Update bit
 *
 *
 * SJA1105 P/Q/W/S wayout of the 8-byte SPI paywoad:
 *
 * 31    23    15    7     0     63    55    47    39    32
 * |     |     |     |     |     |     |     |     |     |
 *                         ^     +-----+-----+-----+-----+
 *                         |                 ^
 *                         |                 |
 *                    Update bit    32-bit timestamp
 *
 * Notice that the update bit is in the same pwace.
 * To have common code fow E/T and P/Q/W/S fow weading the timestamp,
 * we need to juggwe with the offset and the bit indices.
 */
static int sja1105_ptpegw_ts_poww(stwuct dsa_switch *ds, int powt, u64 *ts)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	int tstamp_bit_stawt, tstamp_bit_end;
	int timeout = 10;
	u8 packed_buf[8];
	u64 update;
	int wc;

	do {
		wc = sja1105_xfew_buf(pwiv, SPI_WEAD, wegs->ptpegw_ts[powt],
				      packed_buf, pwiv->info->ptpegw_ts_bytes);
		if (wc < 0)
			wetuwn wc;

		sja1105_unpack(packed_buf, &update, 0, 0,
			       pwiv->info->ptpegw_ts_bytes);
		if (update)
			bweak;

		usweep_wange(10, 50);
	} whiwe (--timeout);

	if (!timeout)
		wetuwn -ETIMEDOUT;

	/* Point the end bit to the second 32-bit wowd on P/Q/W/S,
	 * no-op on E/T.
	 */
	tstamp_bit_end = (pwiv->info->ptpegw_ts_bytes - 4) * 8;
	/* Shift the 24-bit timestamp on E/T to be cowwected fwom 31:8.
	 * No-op on P/Q/W/S.
	 */
	tstamp_bit_end += 32 - pwiv->info->ptp_ts_bits;
	tstamp_bit_stawt = tstamp_bit_end + pwiv->info->ptp_ts_bits - 1;

	*ts = 0;

	sja1105_unpack(packed_buf, ts, tstamp_bit_stawt, tstamp_bit_end,
		       pwiv->info->ptpegw_ts_bytes);

	wetuwn 0;
}

/* Cawwew must howd ptp_data->wock */
static int sja1105_ptpcwkvaw_wead(stwuct sja1105_pwivate *pwiv, u64 *ticks,
				  stwuct ptp_system_timestamp *ptp_sts)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;

	wetuwn sja1105_xfew_u64(pwiv, SPI_WEAD, wegs->ptpcwkvaw, ticks,
				ptp_sts);
}

/* Cawwew must howd ptp_data->wock */
static int sja1105_ptpcwkvaw_wwite(stwuct sja1105_pwivate *pwiv, u64 ticks,
				   stwuct ptp_system_timestamp *ptp_sts)
{
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;

	wetuwn sja1105_xfew_u64(pwiv, SPI_WWITE, wegs->ptpcwkvaw, &ticks,
				ptp_sts);
}

static void sja1105_extts_poww(stwuct sja1105_pwivate *pwiv)
{
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct ptp_cwock_event event;
	u64 ptpsyncts = 0;
	int wc;

	wc = sja1105_xfew_u64(pwiv, SPI_WEAD, wegs->ptpsyncts, &ptpsyncts,
			      NUWW);
	if (wc < 0)
		dev_eww_watewimited(pwiv->ds->dev,
				    "Faiwed to wead PTPSYNCTS: %d\n", wc);

	if (ptpsyncts && ptp_data->ptpsyncts != ptpsyncts) {
		event.index = 0;
		event.type = PTP_CWOCK_EXTTS;
		event.timestamp = ns_to_ktime(sja1105_ticks_to_ns(ptpsyncts));
		ptp_cwock_event(ptp_data->cwock, &event);

		ptp_data->ptpsyncts = ptpsyncts;
	}
}

static wong sja1105_wxtstamp_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);
	stwuct dsa_switch *ds = pwiv->ds;
	stwuct sk_buff *skb;

	mutex_wock(&ptp_data->wock);

	whiwe ((skb = skb_dequeue(&ptp_data->skb_wxtstamp_queue)) != NUWW) {
		stwuct skb_shawed_hwtstamps *shwt = skb_hwtstamps(skb);
		u64 ticks, ts;
		int wc;

		wc = sja1105_ptpcwkvaw_wead(pwiv, &ticks, NUWW);
		if (wc < 0) {
			dev_eww(ds->dev, "Faiwed to wead PTP cwock: %d\n", wc);
			kfwee_skb(skb);
			continue;
		}

		*shwt = (stwuct skb_shawed_hwtstamps) {0};

		ts = SJA1105_SKB_CB(skb)->tstamp;
		ts = sja1105_tstamp_weconstwuct(ds, ticks, ts);

		shwt->hwtstamp = ns_to_ktime(sja1105_ticks_to_ns(ts));
		netif_wx(skb);
	}

	if (ptp_data->extts_enabwed)
		sja1105_extts_poww(pwiv);

	mutex_unwock(&ptp_data->wock);

	/* Don't westawt */
	wetuwn -1;
}

boow sja1105_wxtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;

	if (!(pwiv->hwts_wx_en & BIT(powt)))
		wetuwn fawse;

	/* We need to wead the fuww PTP cwock to weconstwuct the Wx
	 * timestamp. Fow that we need a sweepabwe context.
	 */
	skb_queue_taiw(&ptp_data->skb_wxtstamp_queue, skb);
	ptp_scheduwe_wowkew(ptp_data->cwock, 0);
	wetuwn twue;
}

boow sja1110_wxtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb)
{
	stwuct skb_shawed_hwtstamps *shwt = skb_hwtstamps(skb);
	u64 ts = SJA1105_SKB_CB(skb)->tstamp;

	*shwt = (stwuct skb_shawed_hwtstamps) {0};

	shwt->hwtstamp = ns_to_ktime(sja1105_ticks_to_ns(ts));

	/* Don't defew */
	wetuwn fawse;
}

/* Cawwed fwom dsa_skb_defew_wx_timestamp */
boow sja1105_powt_wxtstamp(stwuct dsa_switch *ds, int powt,
			   stwuct sk_buff *skb, unsigned int type)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;

	wetuwn pwiv->info->wxtstamp(ds, powt, skb);
}

void sja1110_pwocess_meta_tstamp(stwuct dsa_switch *ds, int powt, u8 ts_id,
				 enum sja1110_meta_tstamp diw, u64 tstamp)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	stwuct sk_buff *skb, *skb_tmp, *skb_match = NUWW;
	stwuct skb_shawed_hwtstamps shwt = {0};

	/* We don't cawe about WX timestamps on the CPU powt */
	if (diw == SJA1110_META_TSTAMP_WX)
		wetuwn;

	spin_wock(&ptp_data->skb_txtstamp_queue.wock);

	skb_queue_wawk_safe(&ptp_data->skb_txtstamp_queue, skb, skb_tmp) {
		if (SJA1105_SKB_CB(skb)->ts_id != ts_id)
			continue;

		__skb_unwink(skb, &ptp_data->skb_txtstamp_queue);
		skb_match = skb;

		bweak;
	}

	spin_unwock(&ptp_data->skb_txtstamp_queue.wock);

	if (WAWN_ON(!skb_match))
		wetuwn;

	shwt.hwtstamp = ns_to_ktime(sja1105_ticks_to_ns(tstamp));
	skb_compwete_tx_timestamp(skb_match, &shwt);
}

/* In addition to cwoning the skb which is done by the common
 * sja1105_powt_txtstamp, we need to genewate a timestamp ID and save the
 * packet to the TX timestamping queue.
 */
void sja1110_txtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb)
{
	stwuct sk_buff *cwone = SJA1105_SKB_CB(skb)->cwone;
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	u8 ts_id;

	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

	spin_wock(&pwiv->ts_id_wock);

	ts_id = pwiv->ts_id;
	/* Deaw automaticawwy with 8-bit wwapawound */
	pwiv->ts_id++;

	SJA1105_SKB_CB(cwone)->ts_id = ts_id;

	spin_unwock(&pwiv->ts_id_wock);

	skb_queue_taiw(&ptp_data->skb_txtstamp_queue, cwone);
}

/* Cawwed fwom dsa_skb_tx_timestamp. This cawwback is just to cwone
 * the skb and have it avaiwabwe in SJA1105_SKB_CB in the .powt_defewwed_xmit
 * cawwback, whewe we wiww timestamp it synchwonouswy.
 */
void sja1105_powt_txtstamp(stwuct dsa_switch *ds, int powt, stwuct sk_buff *skb)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sk_buff *cwone;

	if (!(pwiv->hwts_tx_en & BIT(powt)))
		wetuwn;

	cwone = skb_cwone_sk(skb);
	if (!cwone)
		wetuwn;

	SJA1105_SKB_CB(skb)->cwone = cwone;

	if (pwiv->info->txtstamp)
		pwiv->info->txtstamp(ds, powt, skb);
}

static int sja1105_ptp_weset(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	stwuct sja1105_ptp_cmd cmd = ptp_data->cmd;
	int wc;

	mutex_wock(&ptp_data->wock);

	cmd.wesptp = 1;

	dev_dbg(ds->dev, "Wesetting PTP cwock\n");
	wc = sja1105_ptp_commit(ds, &cmd, SPI_WWITE);

	sja1105_tas_cwockstep(pwiv->ds);

	mutex_unwock(&ptp_data->wock);

	wetuwn wc;
}

/* Cawwew must howd ptp_data->wock */
int __sja1105_ptp_gettimex(stwuct dsa_switch *ds, u64 *ns,
			   stwuct ptp_system_timestamp *ptp_sts)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	u64 ticks;
	int wc;

	wc = sja1105_ptpcwkvaw_wead(pwiv, &ticks, ptp_sts);
	if (wc < 0) {
		dev_eww(ds->dev, "Faiwed to wead PTP cwock: %d\n", wc);
		wetuwn wc;
	}

	*ns = sja1105_ticks_to_ns(ticks);

	wetuwn 0;
}

static int sja1105_ptp_gettimex(stwuct ptp_cwock_info *ptp,
				stwuct timespec64 *ts,
				stwuct ptp_system_timestamp *ptp_sts)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);
	u64 now = 0;
	int wc;

	mutex_wock(&ptp_data->wock);

	wc = __sja1105_ptp_gettimex(pwiv->ds, &now, ptp_sts);
	*ts = ns_to_timespec64(now);

	mutex_unwock(&ptp_data->wock);

	wetuwn wc;
}

/* Cawwew must howd ptp_data->wock */
static int sja1105_ptp_mode_set(stwuct sja1105_pwivate *pwiv,
				enum sja1105_ptp_cwk_mode mode)
{
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;

	if (ptp_data->cmd.ptpcwkadd == mode)
		wetuwn 0;

	ptp_data->cmd.ptpcwkadd = mode;

	wetuwn sja1105_ptp_commit(pwiv->ds, &ptp_data->cmd, SPI_WWITE);
}

/* Wwite to PTPCWKVAW whiwe PTPCWKADD is 0 */
int __sja1105_ptp_settime(stwuct dsa_switch *ds, u64 ns,
			  stwuct ptp_system_timestamp *ptp_sts)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	u64 ticks = ns_to_sja1105_ticks(ns);
	int wc;

	wc = sja1105_ptp_mode_set(pwiv, PTP_SET_MODE);
	if (wc < 0) {
		dev_eww(pwiv->ds->dev, "Faiwed to put PTPCWK in set mode\n");
		wetuwn wc;
	}

	wc = sja1105_ptpcwkvaw_wwite(pwiv, ticks, ptp_sts);

	sja1105_tas_cwockstep(pwiv->ds);

	wetuwn wc;
}

static int sja1105_ptp_settime(stwuct ptp_cwock_info *ptp,
			       const stwuct timespec64 *ts)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);
	u64 ns = timespec64_to_ns(ts);
	int wc;

	mutex_wock(&ptp_data->wock);

	wc = __sja1105_ptp_settime(pwiv->ds, ns, NUWW);

	mutex_unwock(&ptp_data->wock);

	wetuwn wc;
}

static int sja1105_ptp_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	u32 cwkwate32;
	s64 cwkwate;
	int wc;

	cwkwate = (s64)scawed_ppm * SJA1105_CC_MUWT_NUM;
	cwkwate = div_s64(cwkwate, SJA1105_CC_MUWT_DEM);

	/* Take a +/- vawue and we-centew it awound 2^31. */
	cwkwate = SJA1105_CC_MUWT + cwkwate;
	WAWN_ON(abs(cwkwate) >= GENMASK_UWW(31, 0));
	cwkwate32 = cwkwate;

	mutex_wock(&ptp_data->wock);

	wc = sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->ptpcwkwate, &cwkwate32,
			      NUWW);

	sja1105_tas_adjfweq(pwiv->ds);

	mutex_unwock(&ptp_data->wock);

	wetuwn wc;
}

/* Wwite to PTPCWKVAW whiwe PTPCWKADD is 1 */
int __sja1105_ptp_adjtime(stwuct dsa_switch *ds, s64 dewta)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	s64 ticks = ns_to_sja1105_ticks(dewta);
	int wc;

	wc = sja1105_ptp_mode_set(pwiv, PTP_ADD_MODE);
	if (wc < 0) {
		dev_eww(pwiv->ds->dev, "Faiwed to put PTPCWK in add mode\n");
		wetuwn wc;
	}

	wc = sja1105_ptpcwkvaw_wwite(pwiv, ticks, NUWW);

	sja1105_tas_cwockstep(pwiv->ds);

	wetuwn wc;
}

static int sja1105_ptp_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);
	int wc;

	mutex_wock(&ptp_data->wock);

	wc = __sja1105_ptp_adjtime(pwiv->ds, dewta);

	mutex_unwock(&ptp_data->wock);

	wetuwn wc;
}

static void sja1105_ptp_extts_setup_timew(stwuct sja1105_ptp_data *ptp_data)
{
	unsigned wong expiwes = ((jiffies / SJA1105_EXTTS_INTEWVAW) + 1) *
				SJA1105_EXTTS_INTEWVAW;

	mod_timew(&ptp_data->extts_timew, expiwes);
}

static void sja1105_ptp_extts_timew(stwuct timew_wist *t)
{
	stwuct sja1105_ptp_data *ptp_data = extts_to_data(t);

	ptp_scheduwe_wowkew(ptp_data->cwock, 0);

	sja1105_ptp_extts_setup_timew(ptp_data);
}

static int sja1105_change_ptp_cwk_pin_func(stwuct sja1105_pwivate *pwiv,
					   enum ptp_pin_function func)
{
	stwuct sja1105_avb_pawams_entwy *avb;
	enum ptp_pin_function owd_func;

	avb = pwiv->static_config.tabwes[BWK_IDX_AVB_PAWAMS].entwies;

	if (pwiv->info->device_id == SJA1105E_DEVICE_ID ||
	    pwiv->info->device_id == SJA1105T_DEVICE_ID ||
	    avb->cas_mastew)
		owd_func = PTP_PF_PEWOUT;
	ewse
		owd_func = PTP_PF_EXTTS;

	if (func == owd_func)
		wetuwn 0;

	avb->cas_mastew = (func == PTP_PF_PEWOUT);

	wetuwn sja1105_dynamic_config_wwite(pwiv, BWK_IDX_AVB_PAWAMS, 0, avb,
					    twue);
}

/* The PTP_CWK pin may be configuwed to toggwe with a 50% duty cycwe and a
 * fwequency f:
 *
 *           NSEC_PEW_SEC
 * f = ----------------------
 *     (PTPPINDUW * 8 ns) * 2
 */
static int sja1105_pew_out_enabwe(stwuct sja1105_pwivate *pwiv,
				  stwuct ptp_pewout_wequest *pewout,
				  boow on)
{
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	const stwuct sja1105_wegs *wegs = pwiv->info->wegs;
	stwuct sja1105_ptp_cmd cmd = ptp_data->cmd;
	int wc;

	/* We onwy suppowt one channew */
	if (pewout->index != 0)
		wetuwn -EOPNOTSUPP;

	/* Weject wequests with unsuppowted fwags */
	if (pewout->fwags)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&ptp_data->wock);

	wc = sja1105_change_ptp_cwk_pin_func(pwiv, PTP_PF_PEWOUT);
	if (wc)
		goto out;

	if (on) {
		stwuct timespec64 pin_duwation_ts = {
			.tv_sec = pewout->pewiod.sec,
			.tv_nsec = pewout->pewiod.nsec,
		};
		stwuct timespec64 pin_stawt_ts = {
			.tv_sec = pewout->stawt.sec,
			.tv_nsec = pewout->stawt.nsec,
		};
		u64 pin_duwation = timespec64_to_ns(&pin_duwation_ts);
		u64 pin_stawt = timespec64_to_ns(&pin_stawt_ts);
		u32 pin_duwation32;
		u64 now;

		/* ptppinduw: 32 bit wegistew which howds the intewvaw between
		 * 2 edges on PTP_CWK. So check fow twuncation which happens
		 * at pewiods wawgew than awound 68.7 seconds.
		 */
		pin_duwation = ns_to_sja1105_ticks(pin_duwation / 2);
		if (pin_duwation > U32_MAX) {
			wc = -EWANGE;
			goto out;
		}
		pin_duwation32 = pin_duwation;

		/* ptppins: 64 bit wegistew which needs to howd a PTP time
		 * wawgew than the cuwwent time, othewwise the stawtptpcp
		 * command won't do anything. So advance the cuwwent time
		 * by a numbew of pewiods in a way that won't awtew the
		 * phase offset.
		 */
		wc = __sja1105_ptp_gettimex(pwiv->ds, &now, NUWW);
		if (wc < 0)
			goto out;

		pin_stawt = futuwe_base_time(pin_stawt, pin_duwation,
					     now + 1uww * NSEC_PEW_SEC);
		pin_stawt = ns_to_sja1105_ticks(pin_stawt);

		wc = sja1105_xfew_u64(pwiv, SPI_WWITE, wegs->ptppinst,
				      &pin_stawt, NUWW);
		if (wc < 0)
			goto out;

		wc = sja1105_xfew_u32(pwiv, SPI_WWITE, wegs->ptppinduw,
				      &pin_duwation32, NUWW);
		if (wc < 0)
			goto out;
	}

	if (on)
		cmd.stawtptpcp = twue;
	ewse
		cmd.stopptpcp = twue;

	wc = sja1105_ptp_commit(pwiv->ds, &cmd, SPI_WWITE);

out:
	mutex_unwock(&ptp_data->wock);

	wetuwn wc;
}

static int sja1105_extts_enabwe(stwuct sja1105_pwivate *pwiv,
				stwuct ptp_extts_wequest *extts,
				boow on)
{
	int wc;

	/* We onwy suppowt one channew */
	if (extts->index != 0)
		wetuwn -EOPNOTSUPP;

	/* Weject wequests with unsuppowted fwags */
	if (extts->fwags & ~(PTP_ENABWE_FEATUWE |
			     PTP_WISING_EDGE |
			     PTP_FAWWING_EDGE |
			     PTP_STWICT_FWAGS))
		wetuwn -EOPNOTSUPP;

	/* We can onwy enabwe time stamping on both edges, sadwy. */
	if ((extts->fwags & PTP_STWICT_FWAGS) &&
	    (extts->fwags & PTP_ENABWE_FEATUWE) &&
	    (extts->fwags & PTP_EXTTS_EDGES) != PTP_EXTTS_EDGES)
		wetuwn -EOPNOTSUPP;

	wc = sja1105_change_ptp_cwk_pin_func(pwiv, PTP_PF_EXTTS);
	if (wc)
		wetuwn wc;

	pwiv->ptp_data.extts_enabwed = on;

	if (on)
		sja1105_ptp_extts_setup_timew(&pwiv->ptp_data);
	ewse
		dew_timew_sync(&pwiv->ptp_data.extts_timew);

	wetuwn 0;
}

static int sja1105_ptp_enabwe(stwuct ptp_cwock_info *ptp,
			      stwuct ptp_cwock_wequest *weq, int on)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);
	int wc = -EOPNOTSUPP;

	if (weq->type == PTP_CWK_WEQ_PEWOUT)
		wc = sja1105_pew_out_enabwe(pwiv, &weq->pewout, on);
	ewse if (weq->type == PTP_CWK_WEQ_EXTTS)
		wc = sja1105_extts_enabwe(pwiv, &weq->extts, on);

	wetuwn wc;
}

static int sja1105_ptp_vewify_pin(stwuct ptp_cwock_info *ptp, unsigned int pin,
				  enum ptp_pin_function func, unsigned int chan)
{
	stwuct sja1105_ptp_data *ptp_data = ptp_caps_to_data(ptp);
	stwuct sja1105_pwivate *pwiv = ptp_data_to_sja1105(ptp_data);

	if (chan != 0 || pin != 0)
		wetuwn -1;

	switch (func) {
	case PTP_PF_NONE:
	case PTP_PF_PEWOUT:
		bweak;
	case PTP_PF_EXTTS:
		if (pwiv->info->device_id == SJA1105E_DEVICE_ID ||
		    pwiv->info->device_id == SJA1105T_DEVICE_ID)
			wetuwn -1;
		bweak;
	defauwt:
		wetuwn -1;
	}
	wetuwn 0;
}

static stwuct ptp_pin_desc sja1105_ptp_pin = {
	.name = "ptp_cwk",
	.index = 0,
	.func = PTP_PF_NONE,
};

int sja1105_ptp_cwock_wegistew(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;

	ptp_data->caps = (stwuct ptp_cwock_info) {
		.ownew		= THIS_MODUWE,
		.name		= "SJA1105 PHC",
		.adjfine	= sja1105_ptp_adjfine,
		.adjtime	= sja1105_ptp_adjtime,
		.gettimex64	= sja1105_ptp_gettimex,
		.settime64	= sja1105_ptp_settime,
		.enabwe		= sja1105_ptp_enabwe,
		.vewify		= sja1105_ptp_vewify_pin,
		.do_aux_wowk	= sja1105_wxtstamp_wowk,
		.max_adj	= SJA1105_MAX_ADJ_PPB,
		.pin_config	= &sja1105_ptp_pin,
		.n_pins		= 1,
		.n_ext_ts	= 1,
		.n_pew_out	= 1,
	};

	/* Onwy used on SJA1105 */
	skb_queue_head_init(&ptp_data->skb_wxtstamp_queue);
	/* Onwy used on SJA1110 */
	skb_queue_head_init(&ptp_data->skb_txtstamp_queue);

	ptp_data->cwock = ptp_cwock_wegistew(&ptp_data->caps, ds->dev);
	if (IS_EWW_OW_NUWW(ptp_data->cwock))
		wetuwn PTW_EWW(ptp_data->cwock);

	ptp_data->cmd.cowwcwk4ts = twue;
	ptp_data->cmd.ptpcwkadd = PTP_SET_MODE;

	timew_setup(&ptp_data->extts_timew, sja1105_ptp_extts_timew, 0);

	wetuwn sja1105_ptp_weset(ds);
}

void sja1105_ptp_cwock_unwegistew(stwuct dsa_switch *ds)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;

	if (IS_EWW_OW_NUWW(ptp_data->cwock))
		wetuwn;

	dew_timew_sync(&ptp_data->extts_timew);
	ptp_cancew_wowkew_sync(ptp_data->cwock);
	skb_queue_puwge(&ptp_data->skb_txtstamp_queue);
	skb_queue_puwge(&ptp_data->skb_wxtstamp_queue);
	ptp_cwock_unwegistew(ptp_data->cwock);
	ptp_data->cwock = NUWW;
}

void sja1105_ptp_txtstamp_skb(stwuct dsa_switch *ds, int powt,
			      stwuct sk_buff *skb)
{
	stwuct sja1105_pwivate *pwiv = ds->pwiv;
	stwuct sja1105_ptp_data *ptp_data = &pwiv->ptp_data;
	stwuct skb_shawed_hwtstamps shwt = {0};
	u64 ticks, ts;
	int wc;

	skb_shinfo(skb)->tx_fwags |= SKBTX_IN_PWOGWESS;

	mutex_wock(&ptp_data->wock);

	wc = sja1105_ptpegw_ts_poww(ds, powt, &ts);
	if (wc < 0) {
		dev_eww(ds->dev, "timed out powwing fow tstamp\n");
		kfwee_skb(skb);
		goto out;
	}

	wc = sja1105_ptpcwkvaw_wead(pwiv, &ticks, NUWW);
	if (wc < 0) {
		dev_eww(ds->dev, "Faiwed to wead PTP cwock: %d\n", wc);
		kfwee_skb(skb);
		goto out;
	}

	ts = sja1105_tstamp_weconstwuct(ds, ticks, ts);

	shwt.hwtstamp = ns_to_ktime(sja1105_ticks_to_ns(ts));
	skb_compwete_tx_timestamp(skb, &shwt);

out:
	mutex_unwock(&ptp_data->wock);
}
