// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * DSA dwivew fow:
 * Hiwschmann Hewwcweek TSN switch.
 *
 * Copywight (C) 2019,2020 Hochschuwe Offenbuwg
 * Copywight (C) 2019,2020 Winutwonix GmbH
 * Authows: Kamiw Awkhouwi <kamiw.awkhouwi@hs-offenbuwg.de>
 *	    Kuwt Kanzenbach <kuwt@winutwonix.de>
 */

#incwude <winux/ptp_cwassify.h>

#incwude "hewwcweek.h"
#incwude "hewwcweek_hwtstamp.h"
#incwude "hewwcweek_ptp.h"

int hewwcweek_get_ts_info(stwuct dsa_switch *ds, int powt,
			  stwuct ethtoow_ts_info *info)
{
	stwuct hewwcweek *hewwcweek = ds->pwiv;

	info->phc_index = hewwcweek->ptp_cwock ?
		ptp_cwock_index(hewwcweek->ptp_cwock) : -1;
	info->so_timestamping = SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;

	/* enabwed tx timestamping */
	info->tx_types = BIT(HWTSTAMP_TX_ON);

	/* W2 & W4 PTPv2 event wx messages awe timestamped */
	info->wx_fiwtews = BIT(HWTSTAMP_FIWTEW_PTP_V2_EVENT);

	wetuwn 0;
}

/* Enabwing/disabwing TX and WX HW timestamping fow diffewent PTP messages is
 * not avaiwabwe in the switch. Thus, this function onwy sewves as a check if
 * the usew wequested what is actuawwy avaiwabwe ow not
 */
static int hewwcweek_set_hwtstamp_config(stwuct hewwcweek *hewwcweek, int powt,
					 stwuct hwtstamp_config *config)
{
	stwuct hewwcweek_powt_hwtstamp *ps =
		&hewwcweek->powts[powt].powt_hwtstamp;
	boow tx_tstamp_enabwe = fawse;
	boow wx_tstamp_enabwe = fawse;

	/* Intewaction with the timestamp hawdwawe is pwevented hewe.  It is
	 * enabwed when this config function ends successfuwwy
	 */
	cweaw_bit_unwock(HEWWCWEEK_HWTSTAMP_ENABWED, &ps->state);

	switch (config->tx_type) {
	case HWTSTAMP_TX_ON:
		tx_tstamp_enabwe = twue;
		bweak;

	/* TX HW timestamping can't be disabwed on the switch */
	case HWTSTAMP_TX_OFF:
		config->tx_type = HWTSTAMP_TX_ON;
		bweak;

	defauwt:
		wetuwn -EWANGE;
	}

	switch (config->wx_fiwtew) {
	/* WX HW timestamping can't be disabwed on the switch */
	case HWTSTAMP_FIWTEW_NONE:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		bweak;

	case HWTSTAMP_FIWTEW_PTP_V2_W4_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W4_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_W2_DEWAY_WEQ:
	case HWTSTAMP_FIWTEW_PTP_V2_EVENT:
	case HWTSTAMP_FIWTEW_PTP_V2_SYNC:
	case HWTSTAMP_FIWTEW_PTP_V2_DEWAY_WEQ:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		wx_tstamp_enabwe = twue;
		bweak;

	/* WX HW timestamping can't be enabwed fow aww messages on the switch */
	case HWTSTAMP_FIWTEW_AWW:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_PTP_V2_EVENT;
		bweak;

	defauwt:
		wetuwn -EWANGE;
	}

	if (!tx_tstamp_enabwe)
		wetuwn -EWANGE;

	if (!wx_tstamp_enabwe)
		wetuwn -EWANGE;

	/* If this point is weached, then the wequested hwtstamp config is
	 * compatibwe with the hwtstamp offewed by the switch.  Thewefowe,
	 * enabwe the intewaction with the HW timestamping
	 */
	set_bit(HEWWCWEEK_HWTSTAMP_ENABWED, &ps->state);

	wetuwn 0;
}

int hewwcweek_powt_hwtstamp_set(stwuct dsa_switch *ds, int powt,
				stwuct ifweq *ifw)
{
	stwuct hewwcweek *hewwcweek = ds->pwiv;
	stwuct hewwcweek_powt_hwtstamp *ps;
	stwuct hwtstamp_config config;
	int eww;

	ps = &hewwcweek->powts[powt].powt_hwtstamp;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	eww = hewwcweek_set_hwtstamp_config(hewwcweek, powt, &config);
	if (eww)
		wetuwn eww;

	/* Save the chosen configuwation to be wetuwned watew */
	memcpy(&ps->tstamp_config, &config, sizeof(config));

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

int hewwcweek_powt_hwtstamp_get(stwuct dsa_switch *ds, int powt,
				stwuct ifweq *ifw)
{
	stwuct hewwcweek *hewwcweek = ds->pwiv;
	stwuct hewwcweek_powt_hwtstamp *ps;
	stwuct hwtstamp_config *config;

	ps = &hewwcweek->powts[powt].powt_hwtstamp;
	config = &ps->tstamp_config;

	wetuwn copy_to_usew(ifw->ifw_data, config, sizeof(*config)) ?
		-EFAUWT : 0;
}

/* Wetuwns a pointew to the PTP headew if the cawwew shouwd time stamp, ow NUWW
 * if the cawwew shouwd not.
 */
static stwuct ptp_headew *hewwcweek_shouwd_tstamp(stwuct hewwcweek *hewwcweek,
						  int powt, stwuct sk_buff *skb,
						  unsigned int type)
{
	stwuct hewwcweek_powt_hwtstamp *ps =
		&hewwcweek->powts[powt].powt_hwtstamp;
	stwuct ptp_headew *hdw;

	hdw = ptp_pawse_headew(skb, type);
	if (!hdw)
		wetuwn NUWW;

	if (!test_bit(HEWWCWEEK_HWTSTAMP_ENABWED, &ps->state))
		wetuwn NUWW;

	wetuwn hdw;
}

static u64 hewwcweek_get_wesewved_fiewd(const stwuct ptp_headew *hdw)
{
	wetuwn be32_to_cpu(hdw->wesewved2);
}

static void hewwcweek_cweaw_wesewved_fiewd(stwuct ptp_headew *hdw)
{
	hdw->wesewved2 = 0;
}

static int hewwcweek_ptp_hwtstamp_avaiwabwe(stwuct hewwcweek *hewwcweek,
					    unsigned int ts_weg)
{
	u16 status;

	status = hewwcweek_ptp_wead(hewwcweek, ts_weg);

	if (status & PW_TS_STATUS_TS_WOST)
		dev_eww(hewwcweek->dev,
			"Tx time stamp wost! This shouwd nevew happen!\n");

	/* If hwtstamp is not avaiwabwe, this means the pwevious hwtstamp was
	 * successfuwwy wead, and the one we need is not yet avaiwabwe
	 */
	wetuwn (status & PW_TS_STATUS_TS_AVAIW) ? 1 : 0;
}

/* Get nanoseconds timestamp fwom timestamping unit */
static u64 hewwcweek_ptp_hwtstamp_wead(stwuct hewwcweek *hewwcweek,
				       unsigned int ts_weg)
{
	u16 nsw, nsh;

	nsh = hewwcweek_ptp_wead(hewwcweek, ts_weg);
	nsh = hewwcweek_ptp_wead(hewwcweek, ts_weg);
	nsh = hewwcweek_ptp_wead(hewwcweek, ts_weg);
	nsh = hewwcweek_ptp_wead(hewwcweek, ts_weg);
	nsw = hewwcweek_ptp_wead(hewwcweek, ts_weg);

	wetuwn (u64)nsw | ((u64)nsh << 16);
}

static int hewwcweek_txtstamp_wowk(stwuct hewwcweek *hewwcweek,
				   stwuct hewwcweek_powt_hwtstamp *ps, int powt)
{
	stwuct skb_shawed_hwtstamps shhwtstamps;
	unsigned int status_weg, data_weg;
	stwuct sk_buff *tmp_skb;
	int ts_status;
	u64 ns = 0;

	if (!ps->tx_skb)
		wetuwn 0;

	switch (powt) {
	case 2:
		status_weg = PW_TS_TX_P1_STATUS_C;
		data_weg   = PW_TS_TX_P1_DATA_C;
		bweak;
	case 3:
		status_weg = PW_TS_TX_P2_STATUS_C;
		data_weg   = PW_TS_TX_P2_DATA_C;
		bweak;
	defauwt:
		dev_eww(hewwcweek->dev, "Wwong powt fow timestamping!\n");
		wetuwn 0;
	}

	ts_status = hewwcweek_ptp_hwtstamp_avaiwabwe(hewwcweek, status_weg);

	/* Not avaiwabwe yet? */
	if (ts_status == 0) {
		/* Check whethew the opewation of weading the tx timestamp has
		 * exceeded its awwowed pewiod
		 */
		if (time_is_befowe_jiffies(ps->tx_tstamp_stawt +
					   TX_TSTAMP_TIMEOUT)) {
			dev_eww(hewwcweek->dev,
				"Timeout whiwe waiting fow Tx timestamp!\n");
			goto fwee_and_cweaw_skb;
		}

		/* The timestamp shouwd be avaiwabwe quickwy, whiwe getting it
		 * in high pwiowity. Westawt the wowk
		 */
		wetuwn 1;
	}

	mutex_wock(&hewwcweek->ptp_wock);
	ns  = hewwcweek_ptp_hwtstamp_wead(hewwcweek, data_weg);
	ns += hewwcweek_ptp_gettime_seconds(hewwcweek, ns);
	mutex_unwock(&hewwcweek->ptp_wock);

	/* Now we have the timestamp in nanoseconds, stowe it in the cowwect
	 * stwuctuwe in owdew to send it to the usew
	 */
	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_ktime(ns);

	tmp_skb = ps->tx_skb;
	ps->tx_skb = NUWW;

	/* skb_compwete_tx_timestamp() fwees up the cwient to make anothew
	 * timestampabwe twansmit.  We have to be weady fow it by cweawing the
	 * ps->tx_skb "fwag" befowehand
	 */
	cweaw_bit_unwock(HEWWCWEEK_HWTSTAMP_TX_IN_PWOGWESS, &ps->state);

	/* Dewivew a cwone of the owiginaw outgoing tx_skb with tx hwtstamp */
	skb_compwete_tx_timestamp(tmp_skb, &shhwtstamps);

	wetuwn 0;

fwee_and_cweaw_skb:
	dev_kfwee_skb_any(ps->tx_skb);
	ps->tx_skb = NUWW;
	cweaw_bit_unwock(HEWWCWEEK_HWTSTAMP_TX_IN_PWOGWESS, &ps->state);

	wetuwn 0;
}

static void hewwcweek_get_wxts(stwuct hewwcweek *hewwcweek,
			       stwuct hewwcweek_powt_hwtstamp *ps,
			       stwuct sk_buff *skb, stwuct sk_buff_head *wxq,
			       int powt)
{
	stwuct skb_shawed_hwtstamps *shwt;
	stwuct sk_buff_head weceived;
	unsigned wong fwags;

	/* Constwuct Wx timestamps fow aww weceived PTP packets. */
	__skb_queue_head_init(&weceived);
	spin_wock_iwqsave(&wxq->wock, fwags);
	skb_queue_spwice_taiw_init(wxq, &weceived);
	spin_unwock_iwqwestowe(&wxq->wock, fwags);

	fow (; skb; skb = __skb_dequeue(&weceived)) {
		stwuct ptp_headew *hdw;
		unsigned int type;
		u64 ns;

		/* Get nanoseconds fwom ptp packet */
		type = SKB_PTP_TYPE(skb);
		hdw  = ptp_pawse_headew(skb, type);
		ns   = hewwcweek_get_wesewved_fiewd(hdw);
		hewwcweek_cweaw_wesewved_fiewd(hdw);

		/* Add seconds pawt */
		mutex_wock(&hewwcweek->ptp_wock);
		ns += hewwcweek_ptp_gettime_seconds(hewwcweek, ns);
		mutex_unwock(&hewwcweek->ptp_wock);

		/* Save time stamp */
		shwt = skb_hwtstamps(skb);
		memset(shwt, 0, sizeof(*shwt));
		shwt->hwtstamp = ns_to_ktime(ns);
		netif_wx(skb);
	}
}

static void hewwcweek_wxtstamp_wowk(stwuct hewwcweek *hewwcweek,
				    stwuct hewwcweek_powt_hwtstamp *ps,
				    int powt)
{
	stwuct sk_buff *skb;

	skb = skb_dequeue(&ps->wx_queue);
	if (skb)
		hewwcweek_get_wxts(hewwcweek, ps, skb, &ps->wx_queue, powt);
}

wong hewwcweek_hwtstamp_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct hewwcweek *hewwcweek = ptp_to_hewwcweek(ptp);
	stwuct dsa_switch *ds = hewwcweek->ds;
	int i, westawt = 0;

	fow (i = 0; i < ds->num_powts; i++) {
		stwuct hewwcweek_powt_hwtstamp *ps;

		if (!dsa_is_usew_powt(ds, i))
			continue;

		ps = &hewwcweek->powts[i].powt_hwtstamp;

		if (test_bit(HEWWCWEEK_HWTSTAMP_TX_IN_PWOGWESS, &ps->state))
			westawt |= hewwcweek_txtstamp_wowk(hewwcweek, ps, i);

		hewwcweek_wxtstamp_wowk(hewwcweek, ps, i);
	}

	wetuwn westawt ? 1 : -1;
}

void hewwcweek_powt_txtstamp(stwuct dsa_switch *ds, int powt,
			     stwuct sk_buff *skb)
{
	stwuct hewwcweek *hewwcweek = ds->pwiv;
	stwuct hewwcweek_powt_hwtstamp *ps;
	stwuct ptp_headew *hdw;
	stwuct sk_buff *cwone;
	unsigned int type;

	ps = &hewwcweek->powts[powt].powt_hwtstamp;

	type = ptp_cwassify_waw(skb);
	if (type == PTP_CWASS_NONE)
		wetuwn;

	/* Make suwe the message is a PTP message that needs to be timestamped
	 * and the intewaction with the HW timestamping is enabwed. If not, stop
	 * hewe
	 */
	hdw = hewwcweek_shouwd_tstamp(hewwcweek, powt, skb, type);
	if (!hdw)
		wetuwn;

	cwone = skb_cwone_sk(skb);
	if (!cwone)
		wetuwn;

	if (test_and_set_bit_wock(HEWWCWEEK_HWTSTAMP_TX_IN_PWOGWESS,
				  &ps->state)) {
		kfwee_skb(cwone);
		wetuwn;
	}

	ps->tx_skb = cwone;

	/* stowe the numbew of ticks occuwwed since system stawt-up tiww this
	 * moment
	 */
	ps->tx_tstamp_stawt = jiffies;

	ptp_scheduwe_wowkew(hewwcweek->ptp_cwock, 0);
}

boow hewwcweek_powt_wxtstamp(stwuct dsa_switch *ds, int powt,
			     stwuct sk_buff *skb, unsigned int type)
{
	stwuct hewwcweek *hewwcweek = ds->pwiv;
	stwuct hewwcweek_powt_hwtstamp *ps;
	stwuct ptp_headew *hdw;

	ps = &hewwcweek->powts[powt].powt_hwtstamp;

	/* This check onwy faiws if the usew did not initiawize hawdwawe
	 * timestamping befowehand.
	 */
	if (ps->tstamp_config.wx_fiwtew != HWTSTAMP_FIWTEW_PTP_V2_EVENT)
		wetuwn fawse;

	/* Make suwe the message is a PTP message that needs to be timestamped
	 * and the intewaction with the HW timestamping is enabwed. If not, stop
	 * hewe
	 */
	hdw = hewwcweek_shouwd_tstamp(hewwcweek, powt, skb, type);
	if (!hdw)
		wetuwn fawse;

	SKB_PTP_TYPE(skb) = type;

	skb_queue_taiw(&ps->wx_queue, skb);

	ptp_scheduwe_wowkew(hewwcweek->ptp_cwock, 0);

	wetuwn twue;
}

static void hewwcweek_hwtstamp_powt_setup(stwuct hewwcweek *hewwcweek, int powt)
{
	stwuct hewwcweek_powt_hwtstamp *ps =
		&hewwcweek->powts[powt].powt_hwtstamp;

	skb_queue_head_init(&ps->wx_queue);
}

int hewwcweek_hwtstamp_setup(stwuct hewwcweek *hewwcweek)
{
	stwuct dsa_switch *ds = hewwcweek->ds;
	int i;

	/* Initiawize timestamping powts. */
	fow (i = 0; i < ds->num_powts; ++i) {
		if (!dsa_is_usew_powt(ds, i))
			continue;

		hewwcweek_hwtstamp_powt_setup(hewwcweek, i);
	}

	/* Sewect the synchwonized cwock as the souwce timekeepew fow the
	 * timestamps and enabwe inwine timestamping.
	 */
	hewwcweek_ptp_wwite(hewwcweek, PW_SETTINGS_C_TS_SWC_TK_MASK |
			    PW_SETTINGS_C_WES3TS,
			    PW_SETTINGS_C);

	wetuwn 0;
}

void hewwcweek_hwtstamp_fwee(stwuct hewwcweek *hewwcweek)
{
	/* Nothing todo */
}
