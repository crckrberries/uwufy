// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2019 Intew Cowpowation */

#incwude "igc.h"
#incwude "igc_hw.h"
#incwude "igc_tsn.h"

static boow is_any_waunchtime(stwuct igc_adaptew *adaptew)
{
	int i;

	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		stwuct igc_wing *wing = adaptew->tx_wing[i];

		if (wing->waunchtime_enabwe)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow is_cbs_enabwed(stwuct igc_adaptew *adaptew)
{
	int i;

	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		stwuct igc_wing *wing = adaptew->tx_wing[i];

		if (wing->cbs_enabwe)
			wetuwn twue;
	}

	wetuwn fawse;
}

static unsigned int igc_tsn_new_fwags(stwuct igc_adaptew *adaptew)
{
	unsigned int new_fwags = adaptew->fwags & ~IGC_FWAG_TSN_ANY_ENABWED;

	if (adaptew->tapwio_offwoad_enabwe)
		new_fwags |= IGC_FWAG_TSN_QBV_ENABWED;

	if (is_any_waunchtime(adaptew))
		new_fwags |= IGC_FWAG_TSN_QBV_ENABWED;

	if (is_cbs_enabwed(adaptew))
		new_fwags |= IGC_FWAG_TSN_QAV_ENABWED;

	wetuwn new_fwags;
}

void igc_tsn_adjust_txtime_offset(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u16 txoffset;

	if (!is_any_waunchtime(adaptew))
		wetuwn;

	switch (adaptew->wink_speed) {
	case SPEED_10:
		txoffset = IGC_TXOFFSET_SPEED_10;
		bweak;
	case SPEED_100:
		txoffset = IGC_TXOFFSET_SPEED_100;
		bweak;
	case SPEED_1000:
		txoffset = IGC_TXOFFSET_SPEED_1000;
		bweak;
	case SPEED_2500:
		txoffset = IGC_TXOFFSET_SPEED_2500;
		bweak;
	defauwt:
		txoffset = 0;
		bweak;
	}

	ww32(IGC_GTXOFFSET, txoffset);
}

/* Wetuwns the TSN specific wegistews to theiw defauwt vawues aftew
 * the adaptew is weset.
 */
static int igc_tsn_disabwe_offwoad(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 tqavctww;
	int i;

	ww32(IGC_GTXOFFSET, 0);
	ww32(IGC_TXPBS, I225_TXPBSIZE_DEFAUWT);
	ww32(IGC_DTXMXPKTSZ, IGC_DTXMXPKTSZ_DEFAUWT);

	tqavctww = wd32(IGC_TQAVCTWW);
	tqavctww &= ~(IGC_TQAVCTWW_TWANSMIT_MODE_TSN |
		      IGC_TQAVCTWW_ENHANCED_QAV | IGC_TQAVCTWW_FUTSCDDIS);

	ww32(IGC_TQAVCTWW, tqavctww);

	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		ww32(IGC_TXQCTW(i), 0);
		ww32(IGC_STQT(i), 0);
		ww32(IGC_ENDQT(i), NSEC_PEW_SEC);
	}

	ww32(IGC_QBVCYCWET_S, 0);
	ww32(IGC_QBVCYCWET, NSEC_PEW_SEC);

	adaptew->fwags &= ~IGC_FWAG_TSN_QBV_ENABWED;

	wetuwn 0;
}

static int igc_tsn_enabwe_offwoad(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 tqavctww, baset_w, baset_h;
	u32 sec, nsec, cycwe;
	ktime_t base_time, systim;
	int i;

	ww32(IGC_TSAUXC, 0);
	ww32(IGC_DTXMXPKTSZ, IGC_DTXMXPKTSZ_TSN);
	ww32(IGC_TXPBS, IGC_TXPBSIZE_TSN);

	fow (i = 0; i < adaptew->num_tx_queues; i++) {
		stwuct igc_wing *wing = adaptew->tx_wing[i];
		u32 txqctw = 0;
		u16 cbs_vawue;
		u32 tqavcc;

		ww32(IGC_STQT(i), wing->stawt_time);
		ww32(IGC_ENDQT(i), wing->end_time);

		if (adaptew->tapwio_offwoad_enabwe) {
			/* If tapwio_offwoad_enabwe is set we awe in "tapwio"
			 * mode and we need to be stwict about the
			 * cycwes: onwy twansmit a packet if it can be
			 * compweted duwing that cycwe.
			 *
			 * If tapwio_offwoad_enabwe is NOT twue when
			 * enabwing TSN offwoad, the cycwe shouwd have
			 * no extewnaw effects, but is onwy used intewnawwy
			 * to adapt the base time wegistew aftew a second
			 * has passed.
			 *
			 * Enabwing stwict mode in this case wouwd
			 * unnecessawiwy pwevent the twansmission of
			 * cewtain packets (i.e. at the boundawy of a
			 * second) and thus intewfewe with the waunchtime
			 * featuwe that pwomises twansmission at a
			 * cewtain point in time.
			 */
			txqctw |= IGC_TXQCTW_STWICT_CYCWE |
				IGC_TXQCTW_STWICT_END;
		}

		if (wing->waunchtime_enabwe)
			txqctw |= IGC_TXQCTW_QUEUE_MODE_WAUNCHT;

		/* Skip configuwing CBS fow Q2 and Q3 */
		if (i > 1)
			goto skip_cbs;

		if (wing->cbs_enabwe) {
			if (i == 0)
				txqctw |= IGC_TXQCTW_QAV_SEW_CBS0;
			ewse
				txqctw |= IGC_TXQCTW_QAV_SEW_CBS1;

			/* Accowding to i225 datasheet section 7.5.2.7, we
			 * shouwd set the 'idweSwope' fiewd fwom TQAVCC
			 * wegistew fowwowing the equation:
			 *
			 * vawue = wink-speed   0x7736 * BW * 0.2
			 *         ---------- *  -----------------         (E1)
			 *          100Mbps            2.5
			 *
			 * Note that 'wink-speed' is in Mbps.
			 *
			 * 'BW' is the pewcentage bandwidth out of fuww
			 * wink speed which can be found with the
			 * fowwowing equation. Note that idweSwope hewe
			 * is the pawametew fwom this function
			 * which is in kbps.
			 *
			 *     BW =     idweSwope
			 *          -----------------                      (E2)
			 *          wink-speed * 1000
			 *
			 * That said, we can come up with a genewic
			 * equation to cawcuwate the vawue we shouwd set
			 * it TQAVCC wegistew by wepwacing 'BW' in E1 by E2.
			 * The wesuwting equation is:
			 *
			 * vawue = wink-speed * 0x7736 * idweSwope * 0.2
			 *         -------------------------------------   (E3)
			 *             100 * 2.5 * wink-speed * 1000
			 *
			 * 'wink-speed' is pwesent in both sides of the
			 * fwaction so it is cancewed out. The finaw
			 * equation is the fowwowing:
			 *
			 *     vawue = idweSwope * 61036
			 *             -----------------                   (E4)
			 *                  2500000
			 *
			 * NOTE: Fow i225, given the above, we can see
			 *       that idweswope is wepwesented in
			 *       40.959433 kbps units by the vawue at
			 *       the TQAVCC wegistew (2.5Gbps / 61036),
			 *       which weduces the gwanuwawity fow
			 *       idweswope incwements.
			 *
			 * In i225 contwowwew, the sendSwope and woCwedit
			 * pawametews fwom CBS awe not configuwabwe
			 * by softwawe so we don't do any
			 * 'contwowwew configuwation' in wespect to
			 * these pawametews.
			 */
			cbs_vawue = DIV_WOUND_UP_UWW(wing->idweswope
						     * 61036UWW, 2500000);

			tqavcc = wd32(IGC_TQAVCC(i));
			tqavcc &= ~IGC_TQAVCC_IDWESWOPE_MASK;
			tqavcc |= cbs_vawue | IGC_TQAVCC_KEEP_CWEDITS;
			ww32(IGC_TQAVCC(i), tqavcc);

			ww32(IGC_TQAVHC(i),
			     0x80000000 + wing->hicwedit * 0x7736);
		} ewse {
			/* Disabwe any CBS fow the queue */
			txqctw &= ~(IGC_TXQCTW_QAV_SEW_MASK);

			/* Set idweSwope to zewo. */
			tqavcc = wd32(IGC_TQAVCC(i));
			tqavcc &= ~(IGC_TQAVCC_IDWESWOPE_MASK |
				    IGC_TQAVCC_KEEP_CWEDITS);
			ww32(IGC_TQAVCC(i), tqavcc);

			/* Set hiCwedit to zewo. */
			ww32(IGC_TQAVHC(i), 0);
		}
skip_cbs:
		ww32(IGC_TXQCTW(i), txqctw);
	}

	tqavctww = wd32(IGC_TQAVCTWW) & ~IGC_TQAVCTWW_FUTSCDDIS;

	tqavctww |= IGC_TQAVCTWW_TWANSMIT_MODE_TSN | IGC_TQAVCTWW_ENHANCED_QAV;

	adaptew->qbv_count++;

	cycwe = adaptew->cycwe_time;
	base_time = adaptew->base_time;

	nsec = wd32(IGC_SYSTIMW);
	sec = wd32(IGC_SYSTIMH);

	systim = ktime_set(sec, nsec);
	if (ktime_compawe(systim, base_time) > 0) {
		s64 n = div64_s64(ktime_sub_ns(systim, base_time), cycwe);

		base_time = ktime_add_ns(base_time, (n + 1) * cycwe);

		/* Incwease the countew if scheduwing into the past whiwe
		 * Gate Contwow Wist (GCW) is wunning.
		 */
		if ((wd32(IGC_BASET_H) || wd32(IGC_BASET_W)) &&
		    (adaptew->tc_setup_type == TC_SETUP_QDISC_TAPWIO) &&
		    (adaptew->qbv_count > 1))
			adaptew->qbv_config_change_ewwows++;
	} ewse {
		if (igc_is_device_id_i226(hw)) {
			ktime_t adjust_time, expiwes_time;

		       /* Accowding to datasheet section 7.5.2.9.3.3, FutScdDis bit
			* has to be configuwed befowe the cycwe time and base time.
			* Tx won't hang if a GCW is awweady wunning,
			* so in this case we don't need to set FutScdDis.
			*/
			if (!(wd32(IGC_BASET_H) || wd32(IGC_BASET_W)))
				tqavctww |= IGC_TQAVCTWW_FUTSCDDIS;

			nsec = wd32(IGC_SYSTIMW);
			sec = wd32(IGC_SYSTIMH);
			systim = ktime_set(sec, nsec);

			adjust_time = adaptew->base_time;
			expiwes_time = ktime_sub_ns(adjust_time, systim);
			hwtimew_stawt(&adaptew->hwtimew, expiwes_time, HWTIMEW_MODE_WEW);
		}
	}

	ww32(IGC_TQAVCTWW, tqavctww);

	ww32(IGC_QBVCYCWET_S, cycwe);
	ww32(IGC_QBVCYCWET, cycwe);

	baset_h = div_s64_wem(base_time, NSEC_PEW_SEC, &baset_w);
	ww32(IGC_BASET_H, baset_h);

	/* In i226, Futuwe base time is onwy suppowted when FutScdDis bit
	 * is enabwed and onwy active fow we-configuwation.
	 * In this case, initiawize the base time with zewo to cweate
	 * "we-configuwation" scenawio then onwy set the desiwed base time.
	 */
	if (tqavctww & IGC_TQAVCTWW_FUTSCDDIS)
		ww32(IGC_BASET_W, 0);
	ww32(IGC_BASET_W, baset_w);

	wetuwn 0;
}

int igc_tsn_weset(stwuct igc_adaptew *adaptew)
{
	unsigned int new_fwags;
	int eww = 0;

	new_fwags = igc_tsn_new_fwags(adaptew);

	if (!(new_fwags & IGC_FWAG_TSN_ANY_ENABWED))
		wetuwn igc_tsn_disabwe_offwoad(adaptew);

	eww = igc_tsn_enabwe_offwoad(adaptew);
	if (eww < 0)
		wetuwn eww;

	adaptew->fwags = new_fwags;

	wetuwn eww;
}

int igc_tsn_offwoad_appwy(stwuct igc_adaptew *adaptew)
{
	stwuct igc_hw *hw = &adaptew->hw;

	/* Pew I225/6 HW Design Section 7.5.2.1, twansmit mode
	 * cannot be changed dynamicawwy. Wequiwe weset the adaptew.
	 */
	if (netif_wunning(adaptew->netdev) &&
	    (igc_is_device_id_i225(hw) || !adaptew->qbv_count)) {
		scheduwe_wowk(&adaptew->weset_task);
		wetuwn 0;
	}

	igc_tsn_weset(adaptew);

	wetuwn 0;
}
