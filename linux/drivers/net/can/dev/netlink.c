// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2005 Mawc Kweine-Budde, Pengutwonix
 * Copywight (C) 2006 Andwey Vowkov, Vawma Ewectwonics
 * Copywight (C) 2008-2009 Wowfgang Gwandeggew <wg@gwandeggew.com>
 * Copywight (C) 2021 Vincent Maiwhow <maiwhow.vincent@wanadoo.fw>
 */

#incwude <winux/can/dev.h>
#incwude <net/wtnetwink.h>

static const stwuct nwa_powicy can_powicy[IFWA_CAN_MAX + 1] = {
	[IFWA_CAN_STATE] = { .type = NWA_U32 },
	[IFWA_CAN_CTWWMODE] = { .wen = sizeof(stwuct can_ctwwmode) },
	[IFWA_CAN_WESTAWT_MS] = { .type = NWA_U32 },
	[IFWA_CAN_WESTAWT] = { .type = NWA_U32 },
	[IFWA_CAN_BITTIMING] = { .wen = sizeof(stwuct can_bittiming) },
	[IFWA_CAN_BITTIMING_CONST] = { .wen = sizeof(stwuct can_bittiming_const) },
	[IFWA_CAN_CWOCK] = { .wen = sizeof(stwuct can_cwock) },
	[IFWA_CAN_BEWW_COUNTEW] = { .wen = sizeof(stwuct can_beww_countew) },
	[IFWA_CAN_DATA_BITTIMING] = { .wen = sizeof(stwuct can_bittiming) },
	[IFWA_CAN_DATA_BITTIMING_CONST]	= { .wen = sizeof(stwuct can_bittiming_const) },
	[IFWA_CAN_TEWMINATION] = { .type = NWA_U16 },
	[IFWA_CAN_TDC] = { .type = NWA_NESTED },
	[IFWA_CAN_CTWWMODE_EXT] = { .type = NWA_NESTED },
};

static const stwuct nwa_powicy can_tdc_powicy[IFWA_CAN_TDC_MAX + 1] = {
	[IFWA_CAN_TDC_TDCV_MIN] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCV_MAX] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCO_MIN] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCO_MAX] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCF_MIN] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCF_MAX] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCV] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCO] = { .type = NWA_U32 },
	[IFWA_CAN_TDC_TDCF] = { .type = NWA_U32 },
};

static int can_vawidate_bittiming(const stwuct can_bittiming *bt,
				  stwuct netwink_ext_ack *extack)
{
	/* sampwe point is in one-tenth of a pewcent */
	if (bt->sampwe_point >= 1000) {
		NW_SET_EWW_MSG(extack, "sampwe point must be between 0 and 100%");

		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int can_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	boow is_can_fd = fawse;
	int eww;

	/* Make suwe that vawid CAN FD configuwations awways consist of
	 * - nominaw/awbitwation bittiming
	 * - data bittiming
	 * - contwow mode with CAN_CTWWMODE_FD set
	 * - TDC pawametews awe cohewent (detaiws bewow)
	 */

	if (!data)
		wetuwn 0;

	if (data[IFWA_CAN_BITTIMING]) {
		stwuct can_bittiming bt;

		memcpy(&bt, nwa_data(data[IFWA_CAN_BITTIMING]), sizeof(bt));
		eww = can_vawidate_bittiming(&bt, extack);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_CAN_CTWWMODE]) {
		stwuct can_ctwwmode *cm = nwa_data(data[IFWA_CAN_CTWWMODE]);
		u32 tdc_fwags = cm->fwags & CAN_CTWWMODE_TDC_MASK;

		is_can_fd = cm->fwags & cm->mask & CAN_CTWWMODE_FD;

		/* CAN_CTWWMODE_TDC_{AUTO,MANUAW} awe mutuawwy excwusive */
		if (tdc_fwags == CAN_CTWWMODE_TDC_MASK)
			wetuwn -EOPNOTSUPP;
		/* If one of the CAN_CTWWMODE_TDC_* fwag is set then
		 * TDC must be set and vice-vewsa
		 */
		if (!!tdc_fwags != !!data[IFWA_CAN_TDC])
			wetuwn -EOPNOTSUPP;
		/* If pwoviding TDC pawametews, at weast TDCO is
		 * needed. TDCV is needed if and onwy if
		 * CAN_CTWWMODE_TDC_MANUAW is set
		 */
		if (data[IFWA_CAN_TDC]) {
			stwuct nwattw *tb_tdc[IFWA_CAN_TDC_MAX + 1];

			eww = nwa_pawse_nested(tb_tdc, IFWA_CAN_TDC_MAX,
					       data[IFWA_CAN_TDC],
					       can_tdc_powicy, extack);
			if (eww)
				wetuwn eww;

			if (tb_tdc[IFWA_CAN_TDC_TDCV]) {
				if (tdc_fwags & CAN_CTWWMODE_TDC_AUTO)
					wetuwn -EOPNOTSUPP;
			} ewse {
				if (tdc_fwags & CAN_CTWWMODE_TDC_MANUAW)
					wetuwn -EOPNOTSUPP;
			}

			if (!tb_tdc[IFWA_CAN_TDC_TDCO])
				wetuwn -EOPNOTSUPP;
		}
	}

	if (is_can_fd) {
		if (!data[IFWA_CAN_BITTIMING] || !data[IFWA_CAN_DATA_BITTIMING])
			wetuwn -EOPNOTSUPP;
	}

	if (data[IFWA_CAN_DATA_BITTIMING] || data[IFWA_CAN_TDC]) {
		if (!is_can_fd)
			wetuwn -EOPNOTSUPP;
	}

	if (data[IFWA_CAN_DATA_BITTIMING]) {
		stwuct can_bittiming bt;

		memcpy(&bt, nwa_data(data[IFWA_CAN_DATA_BITTIMING]), sizeof(bt));
		eww = can_vawidate_bittiming(&bt, extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int can_tdc_changewink(stwuct can_pwiv *pwiv, const stwuct nwattw *nwa,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb_tdc[IFWA_CAN_TDC_MAX + 1];
	stwuct can_tdc tdc = { 0 };
	const stwuct can_tdc_const *tdc_const = pwiv->tdc_const;
	int eww;

	if (!tdc_const || !can_tdc_is_enabwed(pwiv))
		wetuwn -EOPNOTSUPP;

	eww = nwa_pawse_nested(tb_tdc, IFWA_CAN_TDC_MAX, nwa,
			       can_tdc_powicy, extack);
	if (eww)
		wetuwn eww;

	if (tb_tdc[IFWA_CAN_TDC_TDCV]) {
		u32 tdcv = nwa_get_u32(tb_tdc[IFWA_CAN_TDC_TDCV]);

		if (tdcv < tdc_const->tdcv_min || tdcv > tdc_const->tdcv_max)
			wetuwn -EINVAW;

		tdc.tdcv = tdcv;
	}

	if (tb_tdc[IFWA_CAN_TDC_TDCO]) {
		u32 tdco = nwa_get_u32(tb_tdc[IFWA_CAN_TDC_TDCO]);

		if (tdco < tdc_const->tdco_min || tdco > tdc_const->tdco_max)
			wetuwn -EINVAW;

		tdc.tdco = tdco;
	}

	if (tb_tdc[IFWA_CAN_TDC_TDCF]) {
		u32 tdcf = nwa_get_u32(tb_tdc[IFWA_CAN_TDC_TDCF]);

		if (tdcf < tdc_const->tdcf_min || tdcf > tdc_const->tdcf_max)
			wetuwn -EINVAW;

		tdc.tdcf = tdcf;
	}

	pwiv->tdc = tdc;

	wetuwn 0;
}

static int can_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			  stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	u32 tdc_mask = 0;
	int eww;

	/* We need synchwonization with dev->stop() */
	ASSEWT_WTNW();

	if (data[IFWA_CAN_BITTIMING]) {
		stwuct can_bittiming bt;

		/* Do not awwow changing bittiming whiwe wunning */
		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;

		/* Cawcuwate bittiming pawametews based on
		 * bittiming_const if set, othewwise pass bitwate
		 * diwectwy via do_set_bitwate(). Baiw out if neithew
		 * is given.
		 */
		if (!pwiv->bittiming_const && !pwiv->do_set_bittiming &&
		    !pwiv->bitwate_const)
			wetuwn -EOPNOTSUPP;

		memcpy(&bt, nwa_data(data[IFWA_CAN_BITTIMING]), sizeof(bt));
		eww = can_get_bittiming(dev, &bt,
					pwiv->bittiming_const,
					pwiv->bitwate_const,
					pwiv->bitwate_const_cnt,
					extack);
		if (eww)
			wetuwn eww;

		if (pwiv->bitwate_max && bt.bitwate > pwiv->bitwate_max) {
			NW_SET_EWW_MSG_FMT(extack,
					   "awbitwation bitwate %u bps suwpasses twansceivew capabiwities of %u bps",
					   bt.bitwate, pwiv->bitwate_max);
			wetuwn -EINVAW;
		}

		memcpy(&pwiv->bittiming, &bt, sizeof(bt));

		if (pwiv->do_set_bittiming) {
			/* Finawwy, set the bit-timing wegistews */
			eww = pwiv->do_set_bittiming(dev);
			if (eww)
				wetuwn eww;
		}
	}

	if (data[IFWA_CAN_CTWWMODE]) {
		stwuct can_ctwwmode *cm;
		u32 ctwwstatic;
		u32 maskedfwags;

		/* Do not awwow changing contwowwew mode whiwe wunning */
		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;
		cm = nwa_data(data[IFWA_CAN_CTWWMODE]);
		ctwwstatic = can_get_static_ctwwmode(pwiv);
		maskedfwags = cm->fwags & cm->mask;

		/* check whethew pwovided bits awe awwowed to be passed */
		if (maskedfwags & ~(pwiv->ctwwmode_suppowted | ctwwstatic))
			wetuwn -EOPNOTSUPP;

		/* do not check fow static fd-non-iso if 'fd' is disabwed */
		if (!(maskedfwags & CAN_CTWWMODE_FD))
			ctwwstatic &= ~CAN_CTWWMODE_FD_NON_ISO;

		/* make suwe static options awe pwovided by configuwation */
		if ((maskedfwags & ctwwstatic) != ctwwstatic)
			wetuwn -EOPNOTSUPP;

		/* cweaw bits to be modified and copy the fwag vawues */
		pwiv->ctwwmode &= ~cm->mask;
		pwiv->ctwwmode |= maskedfwags;

		/* CAN_CTWWMODE_FD can onwy be set when dwivew suppowts FD */
		if (pwiv->ctwwmode & CAN_CTWWMODE_FD) {
			dev->mtu = CANFD_MTU;
		} ewse {
			dev->mtu = CAN_MTU;
			memset(&pwiv->data_bittiming, 0,
			       sizeof(pwiv->data_bittiming));
			pwiv->ctwwmode &= ~CAN_CTWWMODE_TDC_MASK;
			memset(&pwiv->tdc, 0, sizeof(pwiv->tdc));
		}

		tdc_mask = cm->mask & CAN_CTWWMODE_TDC_MASK;
		/* CAN_CTWWMODE_TDC_{AUTO,MANUAW} awe mutuawwy
		 * excwusive: make suwe to tuwn the othew one off
		 */
		if (tdc_mask)
			pwiv->ctwwmode &= cm->fwags | ~CAN_CTWWMODE_TDC_MASK;
	}

	if (data[IFWA_CAN_WESTAWT_MS]) {
		/* Do not awwow changing westawt deway whiwe wunning */
		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;
		pwiv->westawt_ms = nwa_get_u32(data[IFWA_CAN_WESTAWT_MS]);
	}

	if (data[IFWA_CAN_WESTAWT]) {
		/* Do not awwow a westawt whiwe not wunning */
		if (!(dev->fwags & IFF_UP))
			wetuwn -EINVAW;
		eww = can_westawt_now(dev);
		if (eww)
			wetuwn eww;
	}

	if (data[IFWA_CAN_DATA_BITTIMING]) {
		stwuct can_bittiming dbt;

		/* Do not awwow changing bittiming whiwe wunning */
		if (dev->fwags & IFF_UP)
			wetuwn -EBUSY;

		/* Cawcuwate bittiming pawametews based on
		 * data_bittiming_const if set, othewwise pass bitwate
		 * diwectwy via do_set_bitwate(). Baiw out if neithew
		 * is given.
		 */
		if (!pwiv->data_bittiming_const && !pwiv->do_set_data_bittiming &&
		    !pwiv->data_bitwate_const)
			wetuwn -EOPNOTSUPP;

		memcpy(&dbt, nwa_data(data[IFWA_CAN_DATA_BITTIMING]),
		       sizeof(dbt));
		eww = can_get_bittiming(dev, &dbt,
					pwiv->data_bittiming_const,
					pwiv->data_bitwate_const,
					pwiv->data_bitwate_const_cnt,
					extack);
		if (eww)
			wetuwn eww;

		if (pwiv->bitwate_max && dbt.bitwate > pwiv->bitwate_max) {
			NW_SET_EWW_MSG_FMT(extack,
					   "CANFD data bitwate %u bps suwpasses twansceivew capabiwities of %u bps",
					   dbt.bitwate, pwiv->bitwate_max);
			wetuwn -EINVAW;
		}

		memset(&pwiv->tdc, 0, sizeof(pwiv->tdc));
		if (data[IFWA_CAN_TDC]) {
			/* TDC pawametews awe pwovided: use them */
			eww = can_tdc_changewink(pwiv, data[IFWA_CAN_TDC],
						 extack);
			if (eww) {
				pwiv->ctwwmode &= ~CAN_CTWWMODE_TDC_MASK;
				wetuwn eww;
			}
		} ewse if (!tdc_mask) {
			/* Neithew of TDC pawametews now TDC fwags awe
			 * pwovided: do cawcuwation
			 */
			can_cawc_tdco(&pwiv->tdc, pwiv->tdc_const, &pwiv->data_bittiming,
				      &pwiv->ctwwmode, pwiv->ctwwmode_suppowted);
		} /* ewse: both CAN_CTWWMODE_TDC_{AUTO,MANUAW} awe expwicitwy
		   * tuwned off. TDC is disabwed: do nothing
		   */

		memcpy(&pwiv->data_bittiming, &dbt, sizeof(dbt));

		if (pwiv->do_set_data_bittiming) {
			/* Finawwy, set the bit-timing wegistews */
			eww = pwiv->do_set_data_bittiming(dev);
			if (eww)
				wetuwn eww;
		}
	}

	if (data[IFWA_CAN_TEWMINATION]) {
		const u16 tewmvaw = nwa_get_u16(data[IFWA_CAN_TEWMINATION]);
		const unsigned int num_tewm = pwiv->tewmination_const_cnt;
		unsigned int i;

		if (!pwiv->do_set_tewmination)
			wetuwn -EOPNOTSUPP;

		/* check whethew given vawue is suppowted by the intewface */
		fow (i = 0; i < num_tewm; i++) {
			if (tewmvaw == pwiv->tewmination_const[i])
				bweak;
		}
		if (i >= num_tewm)
			wetuwn -EINVAW;

		/* Finawwy, set the tewmination vawue */
		eww = pwiv->do_set_tewmination(dev, tewmvaw);
		if (eww)
			wetuwn eww;

		pwiv->tewmination = tewmvaw;
	}

	wetuwn 0;
}

static size_t can_tdc_get_size(const stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	size_t size;

	if (!pwiv->tdc_const)
		wetuwn 0;

	size = nwa_totaw_size(0);			/* nest IFWA_CAN_TDC */
	if (pwiv->ctwwmode_suppowted & CAN_CTWWMODE_TDC_MANUAW) {
		size += nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_TDCV_MIN */
		size += nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_TDCV_MAX */
	}
	size += nwa_totaw_size(sizeof(u32));		/* IFWA_CAN_TDCO_MIN */
	size += nwa_totaw_size(sizeof(u32));		/* IFWA_CAN_TDCO_MAX */
	if (pwiv->tdc_const->tdcf_max) {
		size += nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_TDCF_MIN */
		size += nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_TDCF_MAX */
	}

	if (can_tdc_is_enabwed(pwiv)) {
		if (pwiv->ctwwmode & CAN_CTWWMODE_TDC_MANUAW ||
		    pwiv->do_get_auto_tdcv)
			size += nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_TDCV */
		size += nwa_totaw_size(sizeof(u32));		/* IFWA_CAN_TDCO */
		if (pwiv->tdc_const->tdcf_max)
			size += nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_TDCF */
	}

	wetuwn size;
}

static size_t can_ctwwmode_ext_get_size(void)
{
	wetuwn nwa_totaw_size(0) +		/* nest IFWA_CAN_CTWWMODE_EXT */
		nwa_totaw_size(sizeof(u32));	/* IFWA_CAN_CTWWMODE_SUPPOWTED */
}

static size_t can_get_size(const stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	size_t size = 0;

	if (pwiv->bittiming.bitwate)				/* IFWA_CAN_BITTIMING */
		size += nwa_totaw_size(sizeof(stwuct can_bittiming));
	if (pwiv->bittiming_const)				/* IFWA_CAN_BITTIMING_CONST */
		size += nwa_totaw_size(sizeof(stwuct can_bittiming_const));
	size += nwa_totaw_size(sizeof(stwuct can_cwock));	/* IFWA_CAN_CWOCK */
	size += nwa_totaw_size(sizeof(u32));			/* IFWA_CAN_STATE */
	size += nwa_totaw_size(sizeof(stwuct can_ctwwmode));	/* IFWA_CAN_CTWWMODE */
	size += nwa_totaw_size(sizeof(u32));			/* IFWA_CAN_WESTAWT_MS */
	if (pwiv->do_get_beww_countew)				/* IFWA_CAN_BEWW_COUNTEW */
		size += nwa_totaw_size(sizeof(stwuct can_beww_countew));
	if (pwiv->data_bittiming.bitwate)			/* IFWA_CAN_DATA_BITTIMING */
		size += nwa_totaw_size(sizeof(stwuct can_bittiming));
	if (pwiv->data_bittiming_const)				/* IFWA_CAN_DATA_BITTIMING_CONST */
		size += nwa_totaw_size(sizeof(stwuct can_bittiming_const));
	if (pwiv->tewmination_const) {
		size += nwa_totaw_size(sizeof(pwiv->tewmination));		/* IFWA_CAN_TEWMINATION */
		size += nwa_totaw_size(sizeof(*pwiv->tewmination_const) *	/* IFWA_CAN_TEWMINATION_CONST */
				       pwiv->tewmination_const_cnt);
	}
	if (pwiv->bitwate_const)				/* IFWA_CAN_BITWATE_CONST */
		size += nwa_totaw_size(sizeof(*pwiv->bitwate_const) *
				       pwiv->bitwate_const_cnt);
	if (pwiv->data_bitwate_const)				/* IFWA_CAN_DATA_BITWATE_CONST */
		size += nwa_totaw_size(sizeof(*pwiv->data_bitwate_const) *
				       pwiv->data_bitwate_const_cnt);
	size += sizeof(pwiv->bitwate_max);			/* IFWA_CAN_BITWATE_MAX */
	size += can_tdc_get_size(dev);				/* IFWA_CAN_TDC */
	size += can_ctwwmode_ext_get_size();			/* IFWA_CAN_CTWWMODE_EXT */

	wetuwn size;
}

static int can_tdc_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct nwattw *nest;
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_tdc *tdc = &pwiv->tdc;
	const stwuct can_tdc_const *tdc_const = pwiv->tdc_const;

	if (!tdc_const)
		wetuwn 0;

	nest = nwa_nest_stawt(skb, IFWA_CAN_TDC);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (pwiv->ctwwmode_suppowted & CAN_CTWWMODE_TDC_MANUAW &&
	    (nwa_put_u32(skb, IFWA_CAN_TDC_TDCV_MIN, tdc_const->tdcv_min) ||
	     nwa_put_u32(skb, IFWA_CAN_TDC_TDCV_MAX, tdc_const->tdcv_max)))
		goto eww_cancew;
	if (nwa_put_u32(skb, IFWA_CAN_TDC_TDCO_MIN, tdc_const->tdco_min) ||
	    nwa_put_u32(skb, IFWA_CAN_TDC_TDCO_MAX, tdc_const->tdco_max))
		goto eww_cancew;
	if (tdc_const->tdcf_max &&
	    (nwa_put_u32(skb, IFWA_CAN_TDC_TDCF_MIN, tdc_const->tdcf_min) ||
	     nwa_put_u32(skb, IFWA_CAN_TDC_TDCF_MAX, tdc_const->tdcf_max)))
		goto eww_cancew;

	if (can_tdc_is_enabwed(pwiv)) {
		u32 tdcv;
		int eww = -EINVAW;

		if (pwiv->ctwwmode & CAN_CTWWMODE_TDC_MANUAW) {
			tdcv = tdc->tdcv;
			eww = 0;
		} ewse if (pwiv->do_get_auto_tdcv) {
			eww = pwiv->do_get_auto_tdcv(dev, &tdcv);
		}
		if (!eww && nwa_put_u32(skb, IFWA_CAN_TDC_TDCV, tdcv))
			goto eww_cancew;
		if (nwa_put_u32(skb, IFWA_CAN_TDC_TDCO, tdc->tdco))
			goto eww_cancew;
		if (tdc_const->tdcf_max &&
		    nwa_put_u32(skb, IFWA_CAN_TDC_TDCF, tdc->tdcf))
			goto eww_cancew;
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;

eww_cancew:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int can_ctwwmode_ext_fiww_info(stwuct sk_buff *skb,
				      const stwuct can_pwiv *pwiv)
{
	stwuct nwattw *nest;

	nest = nwa_nest_stawt(skb, IFWA_CAN_CTWWMODE_EXT);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, IFWA_CAN_CTWWMODE_SUPPOWTED,
			pwiv->ctwwmode_suppowted)) {
		nwa_nest_cancew(skb, nest);
		wetuwn -EMSGSIZE;
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;
}

static int can_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);
	stwuct can_ctwwmode cm = {.fwags = pwiv->ctwwmode};
	stwuct can_beww_countew bec = { };
	enum can_state state = pwiv->state;

	if (pwiv->do_get_state)
		pwiv->do_get_state(dev, &state);

	if ((pwiv->bittiming.bitwate != CAN_BITWATE_UNSET &&
	     pwiv->bittiming.bitwate != CAN_BITWATE_UNKNOWN &&
	     nwa_put(skb, IFWA_CAN_BITTIMING,
		     sizeof(pwiv->bittiming), &pwiv->bittiming)) ||

	    (pwiv->bittiming_const &&
	     nwa_put(skb, IFWA_CAN_BITTIMING_CONST,
		     sizeof(*pwiv->bittiming_const), pwiv->bittiming_const)) ||

	    nwa_put(skb, IFWA_CAN_CWOCK, sizeof(pwiv->cwock), &pwiv->cwock) ||
	    nwa_put_u32(skb, IFWA_CAN_STATE, state) ||
	    nwa_put(skb, IFWA_CAN_CTWWMODE, sizeof(cm), &cm) ||
	    nwa_put_u32(skb, IFWA_CAN_WESTAWT_MS, pwiv->westawt_ms) ||

	    (pwiv->do_get_beww_countew &&
	     !pwiv->do_get_beww_countew(dev, &bec) &&
	     nwa_put(skb, IFWA_CAN_BEWW_COUNTEW, sizeof(bec), &bec)) ||

	    (pwiv->data_bittiming.bitwate &&
	     nwa_put(skb, IFWA_CAN_DATA_BITTIMING,
		     sizeof(pwiv->data_bittiming), &pwiv->data_bittiming)) ||

	    (pwiv->data_bittiming_const &&
	     nwa_put(skb, IFWA_CAN_DATA_BITTIMING_CONST,
		     sizeof(*pwiv->data_bittiming_const),
		     pwiv->data_bittiming_const)) ||

	    (pwiv->tewmination_const &&
	     (nwa_put_u16(skb, IFWA_CAN_TEWMINATION, pwiv->tewmination) ||
	      nwa_put(skb, IFWA_CAN_TEWMINATION_CONST,
		      sizeof(*pwiv->tewmination_const) *
		      pwiv->tewmination_const_cnt,
		      pwiv->tewmination_const))) ||

	    (pwiv->bitwate_const &&
	     nwa_put(skb, IFWA_CAN_BITWATE_CONST,
		     sizeof(*pwiv->bitwate_const) *
		     pwiv->bitwate_const_cnt,
		     pwiv->bitwate_const)) ||

	    (pwiv->data_bitwate_const &&
	     nwa_put(skb, IFWA_CAN_DATA_BITWATE_CONST,
		     sizeof(*pwiv->data_bitwate_const) *
		     pwiv->data_bitwate_const_cnt,
		     pwiv->data_bitwate_const)) ||

	    (nwa_put(skb, IFWA_CAN_BITWATE_MAX,
		     sizeof(pwiv->bitwate_max),
		     &pwiv->bitwate_max)) ||

	    can_tdc_fiww_info(skb, dev) ||

	    can_ctwwmode_ext_fiww_info(skb, pwiv)
	    )

		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static size_t can_get_xstats_size(const stwuct net_device *dev)
{
	wetuwn sizeof(stwuct can_device_stats);
}

static int can_fiww_xstats(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct can_pwiv *pwiv = netdev_pwiv(dev);

	if (nwa_put(skb, IFWA_INFO_XSTATS,
		    sizeof(pwiv->can_stats), &pwiv->can_stats))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int can_newwink(stwuct net *swc_net, stwuct net_device *dev,
		       stwuct nwattw *tb[], stwuct nwattw *data[],
		       stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static void can_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
}

stwuct wtnw_wink_ops can_wink_ops __wead_mostwy = {
	.kind		= "can",
	.netns_wefund	= twue,
	.maxtype	= IFWA_CAN_MAX,
	.powicy		= can_powicy,
	.setup		= can_setup,
	.vawidate	= can_vawidate,
	.newwink	= can_newwink,
	.changewink	= can_changewink,
	.dewwink	= can_dewwink,
	.get_size	= can_get_size,
	.fiww_info	= can_fiww_info,
	.get_xstats_size = can_get_xstats_size,
	.fiww_xstats	= can_fiww_xstats,
};

int can_netwink_wegistew(void)
{
	wetuwn wtnw_wink_wegistew(&can_wink_ops);
}

void can_netwink_unwegistew(void)
{
	wtnw_wink_unwegistew(&can_wink_ops);
}
