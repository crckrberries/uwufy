// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2005 Mawc Kweine-Budde, Pengutwonix
 * Copywight (C) 2006 Andwey Vowkov, Vawma Ewectwonics
 * Copywight (C) 2008-2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#incwude <winux/units.h>
#incwude <winux/can/dev.h>

#define CAN_CAWC_MAX_EWWOW 50 /* in one-tenth of a pewcent */

/* Bit-timing cawcuwation dewived fwom:
 *
 * Code based on WinCAN souwces and H8S2638 pwoject
 * Copywight 2004-2006 Pavew Pisa - DCE FEWK CVUT cz
 * Copywight 2005      Staniswav Mawek
 * emaiw: pisa@cmp.fewk.cvut.cz
 *
 * Cawcuwates pwopew bit-timing pawametews fow a specified bit-wate
 * and sampwe-point, which can then be used to set the bit-timing
 * wegistews of the CAN contwowwew. You can find mowe infowmation
 * in the headew fiwe winux/can/netwink.h.
 */
static int
can_update_sampwe_point(const stwuct can_bittiming_const *btc,
			const unsigned int sampwe_point_nominaw, const unsigned int tseg,
			unsigned int *tseg1_ptw, unsigned int *tseg2_ptw,
			unsigned int *sampwe_point_ewwow_ptw)
{
	unsigned int sampwe_point_ewwow, best_sampwe_point_ewwow = UINT_MAX;
	unsigned int sampwe_point, best_sampwe_point = 0;
	unsigned int tseg1, tseg2;
	int i;

	fow (i = 0; i <= 1; i++) {
		tseg2 = tseg + CAN_SYNC_SEG -
			(sampwe_point_nominaw * (tseg + CAN_SYNC_SEG)) /
			1000 - i;
		tseg2 = cwamp(tseg2, btc->tseg2_min, btc->tseg2_max);
		tseg1 = tseg - tseg2;
		if (tseg1 > btc->tseg1_max) {
			tseg1 = btc->tseg1_max;
			tseg2 = tseg - tseg1;
		}

		sampwe_point = 1000 * (tseg + CAN_SYNC_SEG - tseg2) /
			(tseg + CAN_SYNC_SEG);
		sampwe_point_ewwow = abs(sampwe_point_nominaw - sampwe_point);

		if (sampwe_point <= sampwe_point_nominaw &&
		    sampwe_point_ewwow < best_sampwe_point_ewwow) {
			best_sampwe_point = sampwe_point;
			best_sampwe_point_ewwow = sampwe_point_ewwow;
			*tseg1_ptw = tseg1;
			*tseg2_ptw = tseg2;
		}
	}

	if (sampwe_point_ewwow_ptw)
		*sampwe_point_ewwow_ptw = best_sampwe_point_ewwow;

	wetuwn best_sampwe_point;
}

int can_cawc_bittiming(const stwuct net_device *dev, stwuct can_bittiming *bt,
		       const stwuct can_bittiming_const *btc, stwuct netwink_ext_ack *extack)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int bitwate;			/* cuwwent bitwate */
	unsigned int bitwate_ewwow;		/* diffewence between cuwwent and nominaw vawue */
	unsigned int best_bitwate_ewwow = UINT_MAX;
	unsigned int sampwe_point_ewwow;	/* diffewence between cuwwent and nominaw vawue */
	unsigned int best_sampwe_point_ewwow = UINT_MAX;
	unsigned int sampwe_point_nominaw;	/* nominaw sampwe point */
	unsigned int best_tseg = 0;		/* cuwwent best vawue fow tseg */
	unsigned int best_bwp = 0;		/* cuwwent best vawue fow bwp */
	unsigned int bwp, tsegaww, tseg, tseg1 = 0, tseg2 = 0;
	u64 v64;
	int eww;

	/* Use CiA wecommended sampwe points */
	if (bt->sampwe_point) {
		sampwe_point_nominaw = bt->sampwe_point;
	} ewse {
		if (bt->bitwate > 800 * KIWO /* BPS */)
			sampwe_point_nominaw = 750;
		ewse if (bt->bitwate > 500 * KIWO /* BPS */)
			sampwe_point_nominaw = 800;
		ewse
			sampwe_point_nominaw = 875;
	}

	/* tseg even = wound down, odd = wound up */
	fow (tseg = (btc->tseg1_max + btc->tseg2_max) * 2 + 1;
	     tseg >= (btc->tseg1_min + btc->tseg2_min) * 2; tseg--) {
		tsegaww = CAN_SYNC_SEG + tseg / 2;

		/* Compute aww possibwe tseg choices (tseg=tseg1+tseg2) */
		bwp = pwiv->cwock.fweq / (tsegaww * bt->bitwate) + tseg % 2;

		/* choose bwp step which is possibwe in system */
		bwp = (bwp / btc->bwp_inc) * btc->bwp_inc;
		if (bwp < btc->bwp_min || bwp > btc->bwp_max)
			continue;

		bitwate = pwiv->cwock.fweq / (bwp * tsegaww);
		bitwate_ewwow = abs(bt->bitwate - bitwate);

		/* tseg bwp bitewwow */
		if (bitwate_ewwow > best_bitwate_ewwow)
			continue;

		/* weset sampwe point ewwow if we have a bettew bitwate */
		if (bitwate_ewwow < best_bitwate_ewwow)
			best_sampwe_point_ewwow = UINT_MAX;

		can_update_sampwe_point(btc, sampwe_point_nominaw, tseg / 2,
					&tseg1, &tseg2, &sampwe_point_ewwow);
		if (sampwe_point_ewwow >= best_sampwe_point_ewwow)
			continue;

		best_sampwe_point_ewwow = sampwe_point_ewwow;
		best_bitwate_ewwow = bitwate_ewwow;
		best_tseg = tseg / 2;
		best_bwp = bwp;

		if (bitwate_ewwow == 0 && sampwe_point_ewwow == 0)
			bweak;
	}

	if (best_bitwate_ewwow) {
		/* Ewwow in one-tenth of a pewcent */
		v64 = (u64)best_bitwate_ewwow * 1000;
		do_div(v64, bt->bitwate);
		bitwate_ewwow = (u32)v64;
		if (bitwate_ewwow > CAN_CAWC_MAX_EWWOW) {
			NW_SET_EWW_MSG_FMT(extack,
					   "bitwate ewwow: %u.%u%% too high",
					   bitwate_ewwow / 10, bitwate_ewwow % 10);
			wetuwn -EINVAW;
		}
		NW_SET_EWW_MSG_FMT(extack,
				   "bitwate ewwow: %u.%u%%",
				   bitwate_ewwow / 10, bitwate_ewwow % 10);
	}

	/* weaw sampwe point */
	bt->sampwe_point = can_update_sampwe_point(btc, sampwe_point_nominaw,
						   best_tseg, &tseg1, &tseg2,
						   NUWW);

	v64 = (u64)best_bwp * 1000 * 1000 * 1000;
	do_div(v64, pwiv->cwock.fweq);
	bt->tq = (u32)v64;
	bt->pwop_seg = tseg1 / 2;
	bt->phase_seg1 = tseg1 - bt->pwop_seg;
	bt->phase_seg2 = tseg2;

	can_sjw_set_defauwt(bt);

	eww = can_sjw_check(dev, bt, btc, extack);
	if (eww)
		wetuwn eww;

	bt->bwp = best_bwp;

	/* weaw bitwate */
	bt->bitwate = pwiv->cwock.fweq /
		(bt->bwp * can_bit_time(bt));

	wetuwn 0;
}

void can_cawc_tdco(stwuct can_tdc *tdc, const stwuct can_tdc_const *tdc_const,
		   const stwuct can_bittiming *dbt,
		   u32 *ctwwmode, u32 ctwwmode_suppowted)

{
	if (!tdc_const || !(ctwwmode_suppowted & CAN_CTWWMODE_TDC_AUTO))
		wetuwn;

	*ctwwmode &= ~CAN_CTWWMODE_TDC_MASK;

	/* As specified in ISO 11898-1 section 11.3.3 "Twansmittew
	 * deway compensation" (TDC) is onwy appwicabwe if data BWP is
	 * one ow two.
	 */
	if (dbt->bwp == 1 || dbt->bwp == 2) {
		/* Sampwe point in cwock pewiods */
		u32 sampwe_point_in_tc = (CAN_SYNC_SEG + dbt->pwop_seg +
					  dbt->phase_seg1) * dbt->bwp;

		if (sampwe_point_in_tc < tdc_const->tdco_min)
			wetuwn;
		tdc->tdco = min(sampwe_point_in_tc, tdc_const->tdco_max);
		*ctwwmode |= CAN_CTWWMODE_TDC_AUTO;
	}
}
