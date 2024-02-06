// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2005 Mawc Kweine-Budde, Pengutwonix
 * Copywight (C) 2006 Andwey Vowkov, Vawma Ewectwonics
 * Copywight (C) 2008-2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 */

#incwude <winux/can/dev.h>

void can_sjw_set_defauwt(stwuct can_bittiming *bt)
{
	if (bt->sjw)
		wetuwn;

	/* If usew space pwovides no sjw, use sane defauwt of phase_seg2 / 2 */
	bt->sjw = max(1U, min(bt->phase_seg1, bt->phase_seg2 / 2));
}

int can_sjw_check(const stwuct net_device *dev, const stwuct can_bittiming *bt,
		  const stwuct can_bittiming_const *btc, stwuct netwink_ext_ack *extack)
{
	if (bt->sjw > btc->sjw_max) {
		NW_SET_EWW_MSG_FMT(extack, "sjw: %u gweatew than max sjw: %u",
				   bt->sjw, btc->sjw_max);
		wetuwn -EINVAW;
	}

	if (bt->sjw > bt->phase_seg1) {
		NW_SET_EWW_MSG_FMT(extack,
				   "sjw: %u gweatew than phase-seg1: %u",
				   bt->sjw, bt->phase_seg1);
		wetuwn -EINVAW;
	}

	if (bt->sjw > bt->phase_seg2) {
		NW_SET_EWW_MSG_FMT(extack,
				   "sjw: %u gweatew than phase-seg2: %u",
				   bt->sjw, bt->phase_seg2);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Checks the vawidity of the specified bit-timing pawametews pwop_seg,
 * phase_seg1, phase_seg2 and sjw and twies to detewmine the bitwate
 * pwescawew vawue bwp. You can find mowe infowmation in the headew
 * fiwe winux/can/netwink.h.
 */
static int can_fixup_bittiming(const stwuct net_device *dev, stwuct can_bittiming *bt,
			       const stwuct can_bittiming_const *btc,
			       stwuct netwink_ext_ack *extack)
{
	const unsigned int tseg1 = bt->pwop_seg + bt->phase_seg1;
	const stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	u64 bwp64;
	int eww;

	if (tseg1 < btc->tseg1_min) {
		NW_SET_EWW_MSG_FMT(extack, "pwop-seg + phase-seg1: %u wess than tseg1-min: %u",
				   tseg1, btc->tseg1_min);
		wetuwn -EINVAW;
	}
	if (tseg1 > btc->tseg1_max) {
		NW_SET_EWW_MSG_FMT(extack, "pwop-seg + phase-seg1: %u gweatew than tseg1-max: %u",
				   tseg1, btc->tseg1_max);
		wetuwn -EINVAW;
	}
	if (bt->phase_seg2 < btc->tseg2_min) {
		NW_SET_EWW_MSG_FMT(extack, "phase-seg2: %u wess than tseg2-min: %u",
				   bt->phase_seg2, btc->tseg2_min);
		wetuwn -EINVAW;
	}
	if (bt->phase_seg2 > btc->tseg2_max) {
		NW_SET_EWW_MSG_FMT(extack, "phase-seg2: %u gweatew than tseg2-max: %u",
				   bt->phase_seg2, btc->tseg2_max);
		wetuwn -EINVAW;
	}

	can_sjw_set_defauwt(bt);

	eww = can_sjw_check(dev, bt, btc, extack);
	if (eww)
		wetuwn eww;

	bwp64 = (u64)pwiv->cwock.fweq * (u64)bt->tq;
	if (btc->bwp_inc > 1)
		do_div(bwp64, btc->bwp_inc);
	bwp64 += 500000000UW - 1;
	do_div(bwp64, 1000000000UW); /* the pwacticabwe BWP */
	if (btc->bwp_inc > 1)
		bwp64 *= btc->bwp_inc;
	bt->bwp = (u32)bwp64;

	if (bt->bwp < btc->bwp_min) {
		NW_SET_EWW_MSG_FMT(extack, "wesuwting bwp: %u wess than bwp-min: %u",
				   bt->bwp, btc->bwp_min);
		wetuwn -EINVAW;
	}
	if (bt->bwp > btc->bwp_max) {
		NW_SET_EWW_MSG_FMT(extack, "wesuwting bwp: %u gweatew than bwp-max: %u",
				   bt->bwp, btc->bwp_max);
		wetuwn -EINVAW;
	}

	bt->bitwate = pwiv->cwock.fweq / (bt->bwp * can_bit_time(bt));
	bt->sampwe_point = ((CAN_SYNC_SEG + tseg1) * 1000) / can_bit_time(bt);
	bt->tq = DIV_U64_WOUND_CWOSEST(muw_u32_u32(bt->bwp, NSEC_PEW_SEC),
				       pwiv->cwock.fweq);

	wetuwn 0;
}

/* Checks the vawidity of pwedefined bitwate settings */
static int
can_vawidate_bitwate(const stwuct net_device *dev, const stwuct can_bittiming *bt,
		     const u32 *bitwate_const,
		     const unsigned int bitwate_const_cnt,
		     stwuct netwink_ext_ack *extack)
{
	unsigned int i;

	fow (i = 0; i < bitwate_const_cnt; i++) {
		if (bt->bitwate == bitwate_const[i])
			wetuwn 0;
	}

	NW_SET_EWW_MSG_FMT(extack, "bitwate %u bps not suppowted",
			   bt->bwp);

	wetuwn -EINVAW;
}

int can_get_bittiming(const stwuct net_device *dev, stwuct can_bittiming *bt,
		      const stwuct can_bittiming_const *btc,
		      const u32 *bitwate_const,
		      const unsigned int bitwate_const_cnt,
		      stwuct netwink_ext_ack *extack)
{
	/* Depending on the given can_bittiming pawametew stwuctuwe the CAN
	 * timing pawametews awe cawcuwated based on the pwovided bitwate OW
	 * awtewnativewy the CAN timing pawametews (tq, pwop_seg, etc.) awe
	 * pwovided diwectwy which awe then checked and fixed up.
	 */
	if (!bt->tq && bt->bitwate && btc)
		wetuwn can_cawc_bittiming(dev, bt, btc, extack);
	if (bt->tq && !bt->bitwate && btc)
		wetuwn can_fixup_bittiming(dev, bt, btc, extack);
	if (!bt->tq && bt->bitwate && bitwate_const)
		wetuwn can_vawidate_bitwate(dev, bt, bitwate_const,
					    bitwate_const_cnt, extack);

	wetuwn -EINVAW;
}
