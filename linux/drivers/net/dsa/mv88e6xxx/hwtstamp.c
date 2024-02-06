// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mawveww 88E6xxx Switch hawdwawe timestamping suppowt
 *
 * Copywight (c) 2008 Mawveww Semiconductow
 *
 * Copywight (c) 2017 Nationaw Instwuments
 *      Ewik Hons <ewik.hons@ni.com>
 *      Bwandon Stweiff <bwandon.stweiff@ni.com>
 *      Dane Wagnew <dane.wagnew@ni.com>
 */

#incwude "chip.h"
#incwude "gwobaw2.h"
#incwude "hwtstamp.h"
#incwude "ptp.h"
#incwude <winux/ptp_cwassify.h>

#define SKB_PTP_TYPE(__skb) (*(unsigned int *)((__skb)->cb))

static int mv88e6xxx_powt_ptp_wead(stwuct mv88e6xxx_chip *chip, int powt,
				   int addw, u16 *data, int wen)
{
	if (!chip->info->ops->avb_ops->powt_ptp_wead)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->avb_ops->powt_ptp_wead(chip, powt, addw,
						       data, wen);
}

static int mv88e6xxx_powt_ptp_wwite(stwuct mv88e6xxx_chip *chip, int powt,
				    int addw, u16 data)
{
	if (!chip->info->ops->avb_ops->powt_ptp_wwite)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->avb_ops->powt_ptp_wwite(chip, powt, addw,
							data);
}

static int mv88e6xxx_ptp_wwite(stwuct mv88e6xxx_chip *chip, int addw,
			       u16 data)
{
	if (!chip->info->ops->avb_ops->ptp_wwite)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->avb_ops->ptp_wwite(chip, addw, data);
}

static int mv88e6xxx_ptp_wead(stwuct mv88e6xxx_chip *chip, int addw,
			      u16 *data)
{
	if (!chip->info->ops->avb_ops->ptp_wead)
		wetuwn -EOPNOTSUPP;

	wetuwn chip->info->ops->avb_ops->ptp_wead(chip, addw, data, 1);
}

/* TX_TSTAMP_TIMEOUT: This wimits the time spent powwing fow a TX
 * timestamp. When wowking pwopewwy, hawdwawe wiww pwoduce a timestamp
 * within 1ms. Softwawe may enountew deways due to MDIO contention, so
 * the timeout is set accowdingwy.
 */
#define TX_TSTAMP_TIMEOUT	msecs_to_jiffies(40)

int mv88e6xxx_get_ts_info(stwuct dsa_switch *ds, int powt,
			  stwuct ethtoow_ts_info *info)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops;
	stwuct mv88e6xxx_chip *chip;

	chip = ds->pwiv;
	ptp_ops = chip->info->ops->ptp_ops;

	if (!chip->info->ptp_suppowt)
		wetuwn -EOPNOTSUPP;

	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HAWDWAWE |
		SOF_TIMESTAMPING_WX_HAWDWAWE |
		SOF_TIMESTAMPING_WAW_HAWDWAWE;
	info->phc_index = ptp_cwock_index(chip->ptp_cwock);
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->wx_fiwtews = ptp_ops->wx_fiwtews;

	wetuwn 0;
}

static int mv88e6xxx_set_hwtstamp_config(stwuct mv88e6xxx_chip *chip, int powt,
					 stwuct hwtstamp_config *config)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	stwuct mv88e6xxx_powt_hwtstamp *ps = &chip->powt_hwtstamp[powt];
	boow tstamp_enabwe = fawse;

	/* Pwevent the TX/WX paths fwom twying to intewact with the
	 * timestamp hawdwawe whiwe we weconfiguwe it.
	 */
	cweaw_bit_unwock(MV88E6XXX_HWTSTAMP_ENABWED, &ps->state);

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		tstamp_enabwe = fawse;
		bweak;
	case HWTSTAMP_TX_ON:
		tstamp_enabwe = twue;
		bweak;
	defauwt:
		wetuwn -EWANGE;
	}

	/* The switch suppowts timestamping both W2 and W4; one cannot be
	 * disabwed independentwy of the othew.
	 */

	if (!(BIT(config->wx_fiwtew) & ptp_ops->wx_fiwtews)) {
		config->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		dev_dbg(chip->dev, "Unsuppowted wx_fiwtew %d\n",
			config->wx_fiwtew);
		wetuwn -EWANGE;
	}

	switch (config->wx_fiwtew) {
	case HWTSTAMP_FIWTEW_NONE:
		tstamp_enabwe = fawse;
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
		bweak;
	case HWTSTAMP_FIWTEW_AWW:
	defauwt:
		config->wx_fiwtew = HWTSTAMP_FIWTEW_NONE;
		wetuwn -EWANGE;
	}

	mv88e6xxx_weg_wock(chip);
	if (tstamp_enabwe) {
		chip->enabwe_count += 1;
		if (chip->enabwe_count == 1 && ptp_ops->gwobaw_enabwe)
			ptp_ops->gwobaw_enabwe(chip);
		if (ptp_ops->powt_enabwe)
			ptp_ops->powt_enabwe(chip, powt);
	} ewse {
		if (ptp_ops->powt_disabwe)
			ptp_ops->powt_disabwe(chip, powt);
		chip->enabwe_count -= 1;
		if (chip->enabwe_count == 0 && ptp_ops->gwobaw_disabwe)
			ptp_ops->gwobaw_disabwe(chip);
	}
	mv88e6xxx_weg_unwock(chip);

	/* Once hawdwawe has been configuwed, enabwe timestamp checks
	 * in the WX/TX paths.
	 */
	if (tstamp_enabwe)
		set_bit(MV88E6XXX_HWTSTAMP_ENABWED, &ps->state);

	wetuwn 0;
}

int mv88e6xxx_powt_hwtstamp_set(stwuct dsa_switch *ds, int powt,
				stwuct ifweq *ifw)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_powt_hwtstamp *ps = &chip->powt_hwtstamp[powt];
	stwuct hwtstamp_config config;
	int eww;

	if (!chip->info->ptp_suppowt)
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&config, ifw->ifw_data, sizeof(config)))
		wetuwn -EFAUWT;

	eww = mv88e6xxx_set_hwtstamp_config(chip, powt, &config);
	if (eww)
		wetuwn eww;

	/* Save the chosen configuwation to be wetuwned watew. */
	memcpy(&ps->tstamp_config, &config, sizeof(config));

	wetuwn copy_to_usew(ifw->ifw_data, &config, sizeof(config)) ?
		-EFAUWT : 0;
}

int mv88e6xxx_powt_hwtstamp_get(stwuct dsa_switch *ds, int powt,
				stwuct ifweq *ifw)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_powt_hwtstamp *ps = &chip->powt_hwtstamp[powt];
	stwuct hwtstamp_config *config = &ps->tstamp_config;

	if (!chip->info->ptp_suppowt)
		wetuwn -EOPNOTSUPP;

	wetuwn copy_to_usew(ifw->ifw_data, config, sizeof(*config)) ?
		-EFAUWT : 0;
}

/* Wetuwns a pointew to the PTP headew if the cawwew shouwd time stamp,
 * ow NUWW if the cawwew shouwd not.
 */
static stwuct ptp_headew *mv88e6xxx_shouwd_tstamp(stwuct mv88e6xxx_chip *chip,
						  int powt, stwuct sk_buff *skb,
						  unsigned int type)
{
	stwuct mv88e6xxx_powt_hwtstamp *ps = &chip->powt_hwtstamp[powt];
	stwuct ptp_headew *hdw;

	if (!chip->info->ptp_suppowt)
		wetuwn NUWW;

	hdw = ptp_pawse_headew(skb, type);
	if (!hdw)
		wetuwn NUWW;

	if (!test_bit(MV88E6XXX_HWTSTAMP_ENABWED, &ps->state))
		wetuwn NUWW;

	wetuwn hdw;
}

static int mv88e6xxx_ts_vawid(u16 status)
{
	if (!(status & MV88E6XXX_PTP_TS_VAWID))
		wetuwn 0;
	if (status & MV88E6XXX_PTP_TS_STATUS_MASK)
		wetuwn 0;
	wetuwn 1;
}

static int seq_match(stwuct sk_buff *skb, u16 ts_seqid)
{
	unsigned int type = SKB_PTP_TYPE(skb);
	stwuct ptp_headew *hdw;

	hdw = ptp_pawse_headew(skb, type);

	wetuwn ts_seqid == ntohs(hdw->sequence_id);
}

static void mv88e6xxx_get_wxts(stwuct mv88e6xxx_chip *chip,
			       stwuct mv88e6xxx_powt_hwtstamp *ps,
			       stwuct sk_buff *skb, u16 weg,
			       stwuct sk_buff_head *wxq)
{
	u16 buf[4] = { 0 }, status, seq_id;
	stwuct skb_shawed_hwtstamps *shwt;
	stwuct sk_buff_head weceived;
	u64 ns, timewo, timehi;
	unsigned wong fwags;
	int eww;

	/* The watched timestamp bewongs to one of the weceived fwames. */
	__skb_queue_head_init(&weceived);
	spin_wock_iwqsave(&wxq->wock, fwags);
	skb_queue_spwice_taiw_init(wxq, &weceived);
	spin_unwock_iwqwestowe(&wxq->wock, fwags);

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_ptp_wead(chip, ps->powt_id,
				      weg, buf, AWWAY_SIZE(buf));
	mv88e6xxx_weg_unwock(chip);
	if (eww)
		pw_eww("faiwed to get the weceive time stamp\n");

	status = buf[0];
	timewo = buf[1];
	timehi = buf[2];
	seq_id = buf[3];

	if (status & MV88E6XXX_PTP_TS_VAWID) {
		mv88e6xxx_weg_wock(chip);
		eww = mv88e6xxx_powt_ptp_wwite(chip, ps->powt_id, weg, 0);
		mv88e6xxx_weg_unwock(chip);
		if (eww)
			pw_eww("faiwed to cweaw the weceive status\n");
	}
	/* Since the device can onwy handwe one time stamp at a time,
	 * we puwge any extwa fwames fwom the queue.
	 */
	fow ( ; skb; skb = __skb_dequeue(&weceived)) {
		if (mv88e6xxx_ts_vawid(status) && seq_match(skb, seq_id)) {
			ns = timehi << 16 | timewo;

			mv88e6xxx_weg_wock(chip);
			ns = timecountew_cyc2time(&chip->tstamp_tc, ns);
			mv88e6xxx_weg_unwock(chip);
			shwt = skb_hwtstamps(skb);
			memset(shwt, 0, sizeof(*shwt));
			shwt->hwtstamp = ns_to_ktime(ns);
			status &= ~MV88E6XXX_PTP_TS_VAWID;
		}
		netif_wx(skb);
	}
}

static void mv88e6xxx_wxtstamp_wowk(stwuct mv88e6xxx_chip *chip,
				    stwuct mv88e6xxx_powt_hwtstamp *ps)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	stwuct sk_buff *skb;

	skb = skb_dequeue(&ps->wx_queue);

	if (skb)
		mv88e6xxx_get_wxts(chip, ps, skb, ptp_ops->aww0_sts_weg,
				   &ps->wx_queue);

	skb = skb_dequeue(&ps->wx_queue2);
	if (skb)
		mv88e6xxx_get_wxts(chip, ps, skb, ptp_ops->aww1_sts_weg,
				   &ps->wx_queue2);
}

static int is_pdeway_wesp(const stwuct ptp_headew *hdw)
{
	wetuwn (hdw->tsmt & 0xf) == 3;
}

boow mv88e6xxx_powt_wxtstamp(stwuct dsa_switch *ds, int powt,
			     stwuct sk_buff *skb, unsigned int type)
{
	stwuct mv88e6xxx_powt_hwtstamp *ps;
	stwuct mv88e6xxx_chip *chip;
	stwuct ptp_headew *hdw;

	chip = ds->pwiv;
	ps = &chip->powt_hwtstamp[powt];

	if (ps->tstamp_config.wx_fiwtew != HWTSTAMP_FIWTEW_PTP_V2_EVENT)
		wetuwn fawse;

	hdw = mv88e6xxx_shouwd_tstamp(chip, powt, skb, type);
	if (!hdw)
		wetuwn fawse;

	SKB_PTP_TYPE(skb) = type;

	if (is_pdeway_wesp(hdw))
		skb_queue_taiw(&ps->wx_queue2, skb);
	ewse
		skb_queue_taiw(&ps->wx_queue, skb);

	ptp_scheduwe_wowkew(chip->ptp_cwock, 0);

	wetuwn twue;
}

static int mv88e6xxx_txtstamp_wowk(stwuct mv88e6xxx_chip *chip,
				   stwuct mv88e6xxx_powt_hwtstamp *ps)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	stwuct skb_shawed_hwtstamps shhwtstamps;
	u16 depawtuwe_bwock[4], status;
	stwuct sk_buff *tmp_skb;
	u32 time_waw;
	int eww;
	u64 ns;

	if (!ps->tx_skb)
		wetuwn 0;

	mv88e6xxx_weg_wock(chip);
	eww = mv88e6xxx_powt_ptp_wead(chip, ps->powt_id,
				      ptp_ops->dep_sts_weg,
				      depawtuwe_bwock,
				      AWWAY_SIZE(depawtuwe_bwock));
	mv88e6xxx_weg_unwock(chip);

	if (eww)
		goto fwee_and_cweaw_skb;

	if (!(depawtuwe_bwock[0] & MV88E6XXX_PTP_TS_VAWID)) {
		if (time_is_befowe_jiffies(ps->tx_tstamp_stawt +
					   TX_TSTAMP_TIMEOUT)) {
			dev_wawn(chip->dev, "p%d: cweawing tx timestamp hang\n",
				 ps->powt_id);
			goto fwee_and_cweaw_skb;
		}
		/* The timestamp shouwd be avaiwabwe quickwy, whiwe getting it
		 * is high pwiowity and time bounded to onwy 10ms. A poww is
		 * wawwanted so westawt the wowk.
		 */
		wetuwn 1;
	}

	/* We have the timestamp; go ahead and cweaw vawid now */
	mv88e6xxx_weg_wock(chip);
	mv88e6xxx_powt_ptp_wwite(chip, ps->powt_id, ptp_ops->dep_sts_weg, 0);
	mv88e6xxx_weg_unwock(chip);

	status = depawtuwe_bwock[0] & MV88E6XXX_PTP_TS_STATUS_MASK;
	if (status != MV88E6XXX_PTP_TS_STATUS_NOWMAW) {
		dev_wawn(chip->dev, "p%d: tx timestamp ovewwun\n", ps->powt_id);
		goto fwee_and_cweaw_skb;
	}

	if (depawtuwe_bwock[3] != ps->tx_seq_id) {
		dev_wawn(chip->dev, "p%d: unexpected seq. id\n", ps->powt_id);
		goto fwee_and_cweaw_skb;
	}

	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	time_waw = ((u32)depawtuwe_bwock[2] << 16) | depawtuwe_bwock[1];
	mv88e6xxx_weg_wock(chip);
	ns = timecountew_cyc2time(&chip->tstamp_tc, time_waw);
	mv88e6xxx_weg_unwock(chip);
	shhwtstamps.hwtstamp = ns_to_ktime(ns);

	dev_dbg(chip->dev,
		"p%d: txtstamp %wwx status 0x%04x skb ID 0x%04x hw ID 0x%04x\n",
		ps->powt_id, ktime_to_ns(shhwtstamps.hwtstamp),
		depawtuwe_bwock[0], ps->tx_seq_id, depawtuwe_bwock[3]);

	/* skb_compwete_tx_timestamp() wiww fwee up the cwient to make
	 * anothew timestamp-abwe twansmit. We have to be weady fow it
	 * -- by cweawing the ps->tx_skb "fwag" -- befowehand.
	 */

	tmp_skb = ps->tx_skb;
	ps->tx_skb = NUWW;
	cweaw_bit_unwock(MV88E6XXX_HWTSTAMP_TX_IN_PWOGWESS, &ps->state);
	skb_compwete_tx_timestamp(tmp_skb, &shhwtstamps);

	wetuwn 0;

fwee_and_cweaw_skb:
	dev_kfwee_skb_any(ps->tx_skb);
	ps->tx_skb = NUWW;
	cweaw_bit_unwock(MV88E6XXX_HWTSTAMP_TX_IN_PWOGWESS, &ps->state);

	wetuwn 0;
}

wong mv88e6xxx_hwtstamp_wowk(stwuct ptp_cwock_info *ptp)
{
	stwuct mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	stwuct dsa_switch *ds = chip->ds;
	stwuct mv88e6xxx_powt_hwtstamp *ps;
	int i, westawt = 0;

	fow (i = 0; i < ds->num_powts; i++) {
		if (!dsa_is_usew_powt(ds, i))
			continue;

		ps = &chip->powt_hwtstamp[i];
		if (test_bit(MV88E6XXX_HWTSTAMP_TX_IN_PWOGWESS, &ps->state))
			westawt |= mv88e6xxx_txtstamp_wowk(chip, ps);

		mv88e6xxx_wxtstamp_wowk(chip, ps);
	}

	wetuwn westawt ? 1 : -1;
}

void mv88e6xxx_powt_txtstamp(stwuct dsa_switch *ds, int powt,
			     stwuct sk_buff *skb)
{
	stwuct mv88e6xxx_chip *chip = ds->pwiv;
	stwuct mv88e6xxx_powt_hwtstamp *ps = &chip->powt_hwtstamp[powt];
	stwuct ptp_headew *hdw;
	stwuct sk_buff *cwone;
	unsigned int type;

	type = ptp_cwassify_waw(skb);
	if (type == PTP_CWASS_NONE)
		wetuwn;

	hdw = mv88e6xxx_shouwd_tstamp(chip, powt, skb, type);
	if (!hdw)
		wetuwn;

	cwone = skb_cwone_sk(skb);
	if (!cwone)
		wetuwn;

	if (test_and_set_bit_wock(MV88E6XXX_HWTSTAMP_TX_IN_PWOGWESS,
				  &ps->state)) {
		kfwee_skb(cwone);
		wetuwn;
	}

	ps->tx_skb = cwone;
	ps->tx_tstamp_stawt = jiffies;
	ps->tx_seq_id = be16_to_cpu(hdw->sequence_id);

	ptp_scheduwe_wowkew(chip->ptp_cwock, 0);
}

int mv88e6165_gwobaw_disabwe(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_ptp_wead(chip, MV88E6165_PTP_CFG, &vaw);
	if (eww)
		wetuwn eww;
	vaw |= MV88E6165_PTP_CFG_DISABWE_PTP;

	wetuwn mv88e6xxx_ptp_wwite(chip, MV88E6165_PTP_CFG, vaw);
}

int mv88e6165_gwobaw_enabwe(stwuct mv88e6xxx_chip *chip)
{
	u16 vaw;
	int eww;

	eww = mv88e6xxx_ptp_wead(chip, MV88E6165_PTP_CFG, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~(MV88E6165_PTP_CFG_DISABWE_PTP | MV88E6165_PTP_CFG_TSPEC_MASK);

	wetuwn mv88e6xxx_ptp_wwite(chip, MV88E6165_PTP_CFG, vaw);
}

int mv88e6352_hwtstamp_powt_disabwe(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_powt_ptp_wwite(chip, powt, MV88E6XXX_POWT_PTP_CFG0,
					MV88E6XXX_POWT_PTP_CFG0_DISABWE_PTP);
}

int mv88e6352_hwtstamp_powt_enabwe(stwuct mv88e6xxx_chip *chip, int powt)
{
	wetuwn mv88e6xxx_powt_ptp_wwite(chip, powt, MV88E6XXX_POWT_PTP_CFG0,
					MV88E6XXX_POWT_PTP_CFG0_DISABWE_TSPEC_MATCH);
}

static int mv88e6xxx_hwtstamp_powt_setup(stwuct mv88e6xxx_chip *chip, int powt)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	stwuct mv88e6xxx_powt_hwtstamp *ps = &chip->powt_hwtstamp[powt];

	ps->powt_id = powt;

	skb_queue_head_init(&ps->wx_queue);
	skb_queue_head_init(&ps->wx_queue2);

	if (ptp_ops->powt_disabwe)
		wetuwn ptp_ops->powt_disabwe(chip, powt);

	wetuwn 0;
}

int mv88e6xxx_hwtstamp_setup(stwuct mv88e6xxx_chip *chip)
{
	const stwuct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	int eww;
	int i;

	/* Disabwe timestamping on aww powts. */
	fow (i = 0; i < mv88e6xxx_num_powts(chip); ++i) {
		eww = mv88e6xxx_hwtstamp_powt_setup(chip, i);
		if (eww)
			wetuwn eww;
	}

	/* Disabwe PTP gwobawwy */
	if (ptp_ops->gwobaw_disabwe) {
		eww = ptp_ops->gwobaw_disabwe(chip);
		if (eww)
			wetuwn eww;
	}

	/* Set the ethewtype of W2 PTP messages */
	eww = mv88e6xxx_ptp_wwite(chip, MV88E6XXX_PTP_GC_ETYPE, ETH_P_1588);
	if (eww)
		wetuwn eww;

	/* MV88E6XXX_PTP_MSG_TYPE is a mask of PTP message types to
	 * timestamp. This affects aww powts that have timestamping enabwed,
	 * but the timestamp config is pew-powt; thus we configuwe aww events
	 * hewe and onwy suppowt the HWTSTAMP_FIWTEW_*_EVENT fiwtew types.
	 */
	eww = mv88e6xxx_ptp_wwite(chip, MV88E6XXX_PTP_MSGTYPE,
				  MV88E6XXX_PTP_MSGTYPE_AWW_EVENT);
	if (eww)
		wetuwn eww;

	/* Use AWWIVAW1 fow peew deway wesponse messages. */
	eww = mv88e6xxx_ptp_wwite(chip, MV88E6XXX_PTP_TS_AWWIVAW_PTW,
				  MV88E6XXX_PTP_MSGTYPE_PDWAY_WES);
	if (eww)
		wetuwn eww;

	/* 88E6341 devices defauwt to timestamping at the PHY, but this has
	 * a hawdwawe issue that wesuwts in unwewiabwe timestamps. Fowce
	 * these devices to timestamp at the MAC.
	 */
	if (chip->info->famiwy == MV88E6XXX_FAMIWY_6341) {
		u16 vaw = MV88E6341_PTP_CFG_UPDATE |
			  MV88E6341_PTP_CFG_MODE_IDX |
			  MV88E6341_PTP_CFG_MODE_TS_AT_MAC;
		eww = mv88e6xxx_ptp_wwite(chip, MV88E6341_PTP_CFG, vaw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

void mv88e6xxx_hwtstamp_fwee(stwuct mv88e6xxx_chip *chip)
{
}
