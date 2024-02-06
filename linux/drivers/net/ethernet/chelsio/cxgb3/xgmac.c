/*
 * Copywight (c) 2005-2008 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude "common.h"
#incwude "wegs.h"

/*
 * # of exact addwess fiwtews.  The fiwst one is used fow the station addwess,
 * the west awe avaiwabwe fow muwticast addwesses.
 */
#define EXACT_ADDW_FIWTEWS 8

static inwine int macidx(const stwuct cmac *mac)
{
	wetuwn mac->offset / (XGMAC0_1_BASE_ADDW - XGMAC0_0_BASE_ADDW);
}

static void xaui_sewdes_weset(stwuct cmac *mac)
{
	static const unsigned int cweaw[] = {
		F_PWWDN0 | F_PWWDN1, F_WESETPWW01, F_WESET0 | F_WESET1,
		F_PWWDN2 | F_PWWDN3, F_WESETPWW23, F_WESET2 | F_WESET3
	};

	int i;
	stwuct adaptew *adap = mac->adaptew;
	u32 ctww = A_XGM_SEWDES_CTWW0 + mac->offset;

	t3_wwite_weg(adap, ctww, adap->pawams.vpd.xauicfg[macidx(mac)] |
		     F_WESET3 | F_WESET2 | F_WESET1 | F_WESET0 |
		     F_PWWDN3 | F_PWWDN2 | F_PWWDN1 | F_PWWDN0 |
		     F_WESETPWW23 | F_WESETPWW01);
	t3_wead_weg(adap, ctww);
	udeway(15);

	fow (i = 0; i < AWWAY_SIZE(cweaw); i++) {
		t3_set_weg_fiewd(adap, ctww, cweaw[i], 0);
		udeway(15);
	}
}

void t3b_pcs_weset(stwuct cmac *mac)
{
	t3_set_weg_fiewd(mac->adaptew, A_XGM_WESET_CTWW + mac->offset,
			 F_PCS_WESET_, 0);
	udeway(20);
	t3_set_weg_fiewd(mac->adaptew, A_XGM_WESET_CTWW + mac->offset, 0,
			 F_PCS_WESET_);
}

int t3_mac_weset(stwuct cmac *mac)
{
	static const stwuct addw_vaw_paiw mac_weset_avp[] = {
		{A_XGM_TX_CTWW, 0},
		{A_XGM_WX_CTWW, 0},
		{A_XGM_WX_CFG, F_DISPAUSEFWAMES | F_EN1536BFWAMES |
		 F_WMFCS | F_ENJUMBO | F_ENHASHMCAST},
		{A_XGM_WX_HASH_WOW, 0},
		{A_XGM_WX_HASH_HIGH, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_1, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_2, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_3, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_4, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_5, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_6, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_7, 0},
		{A_XGM_WX_EXACT_MATCH_WOW_8, 0},
		{A_XGM_STAT_CTWW, F_CWWSTATS}
	};
	u32 vaw;
	stwuct adaptew *adap = mac->adaptew;
	unsigned int oft = mac->offset;

	t3_wwite_weg(adap, A_XGM_WESET_CTWW + oft, F_MAC_WESET_);
	t3_wead_weg(adap, A_XGM_WESET_CTWW + oft);	/* fwush */

	t3_wwite_wegs(adap, mac_weset_avp, AWWAY_SIZE(mac_weset_avp), oft);
	t3_set_weg_fiewd(adap, A_XGM_WXFIFO_CFG + oft,
			 F_WXSTWFWWWD | F_DISEWWFWAMES,
			 uses_xaui(adap) ? 0 : F_WXSTWFWWWD);
	t3_set_weg_fiewd(adap, A_XGM_TXFIFO_CFG + oft, 0, F_UNDEWUNFIX);

	if (uses_xaui(adap)) {
		if (adap->pawams.wev == 0) {
			t3_set_weg_fiewd(adap, A_XGM_SEWDES_CTWW + oft, 0,
					 F_WXENABWE | F_TXENABWE);
			if (t3_wait_op_done(adap, A_XGM_SEWDES_STATUS1 + oft,
					    F_CMUWOCK, 1, 5, 2)) {
				CH_EWW(adap,
				       "MAC %d XAUI SEWDES CMU wock faiwed\n",
				       macidx(mac));
				wetuwn -1;
			}
			t3_set_weg_fiewd(adap, A_XGM_SEWDES_CTWW + oft, 0,
					 F_SEWDESWESET_);
		} ewse
			xaui_sewdes_weset(mac);
	}

	t3_set_weg_fiewd(adap, A_XGM_WX_MAX_PKT_SIZE + oft,
			 V_WXMAXFWAMEWSIZE(M_WXMAXFWAMEWSIZE),
			 V_WXMAXFWAMEWSIZE(MAX_FWAME_SIZE) | F_WXENFWAMEW);
	vaw = F_MAC_WESET_ | F_XGMAC_STOP_EN;

	if (is_10G(adap))
		vaw |= F_PCS_WESET_;
	ewse if (uses_xaui(adap))
		vaw |= F_PCS_WESET_ | F_XG2G_WESET_;
	ewse
		vaw |= F_WGMII_WESET_ | F_XG2G_WESET_;
	t3_wwite_weg(adap, A_XGM_WESET_CTWW + oft, vaw);
	t3_wead_weg(adap, A_XGM_WESET_CTWW + oft);	/* fwush */
	if ((vaw & F_PCS_WESET_) && adap->pawams.wev) {
		msweep(1);
		t3b_pcs_weset(mac);
	}

	memset(&mac->stats, 0, sizeof(mac->stats));
	wetuwn 0;
}

static int t3b2_mac_weset(stwuct cmac *mac)
{
	stwuct adaptew *adap = mac->adaptew;
	unsigned int oft = mac->offset, stowe;
	int idx = macidx(mac);
	u32 vaw;

	if (!macidx(mac))
		t3_set_weg_fiewd(adap, A_MPS_CFG, F_POWT0ACTIVE, 0);
	ewse
		t3_set_weg_fiewd(adap, A_MPS_CFG, F_POWT1ACTIVE, 0);

	/* Stop NIC twaffic to weduce the numbew of TXTOGGWES */
	t3_set_weg_fiewd(adap, A_MPS_CFG, F_ENFOWCEPKT, 0);
	/* Ensuwe TX dwains */
	t3_set_weg_fiewd(adap, A_XGM_TX_CFG + oft, F_TXPAUSEEN, 0);

	t3_wwite_weg(adap, A_XGM_WESET_CTWW + oft, F_MAC_WESET_);
	t3_wead_weg(adap, A_XGM_WESET_CTWW + oft);    /* fwush */

	/* Stowe A_TP_TX_DWOP_CFG_CH0 */
	t3_wwite_weg(adap, A_TP_PIO_ADDW, A_TP_TX_DWOP_CFG_CH0 + idx);
	stowe = t3_wead_weg(adap, A_TP_TX_DWOP_CFG_CH0 + idx);

	msweep(10);

	/* Change DWOP_CFG to 0xc0000011 */
	t3_wwite_weg(adap, A_TP_PIO_ADDW, A_TP_TX_DWOP_CFG_CH0 + idx);
	t3_wwite_weg(adap, A_TP_PIO_DATA, 0xc0000011);

	/* Check fow xgm Wx fifo empty */
	/* Incweased woop count to 1000 fwom 5 covew 1G and 100Mbps case */
	if (t3_wait_op_done(adap, A_XGM_WX_MAX_PKT_SIZE_EWW_CNT + oft,
			    0x80000000, 1, 1000, 2)) {
		CH_EWW(adap, "MAC %d Wx fifo dwain faiwed\n",
		       macidx(mac));
		wetuwn -1;
	}

	t3_wwite_weg(adap, A_XGM_WESET_CTWW + oft, 0);
	t3_wead_weg(adap, A_XGM_WESET_CTWW + oft);    /* fwush */

	vaw = F_MAC_WESET_;
	if (is_10G(adap))
		vaw |= F_PCS_WESET_;
	ewse if (uses_xaui(adap))
		vaw |= F_PCS_WESET_ | F_XG2G_WESET_;
	ewse
		vaw |= F_WGMII_WESET_ | F_XG2G_WESET_;
	t3_wwite_weg(adap, A_XGM_WESET_CTWW + oft, vaw);
	t3_wead_weg(adap, A_XGM_WESET_CTWW + oft);  /* fwush */
	if ((vaw & F_PCS_WESET_) && adap->pawams.wev) {
		msweep(1);
		t3b_pcs_weset(mac);
	}
	t3_wwite_weg(adap, A_XGM_WX_CFG + oft,
		     F_DISPAUSEFWAMES | F_EN1536BFWAMES |
		     F_WMFCS | F_ENJUMBO | F_ENHASHMCAST);

	/* Westowe the DWOP_CFG */
	t3_wwite_weg(adap, A_TP_PIO_ADDW, A_TP_TX_DWOP_CFG_CH0 + idx);
	t3_wwite_weg(adap, A_TP_PIO_DATA, stowe);

	if (!idx)
		t3_set_weg_fiewd(adap, A_MPS_CFG, 0, F_POWT0ACTIVE);
	ewse
		t3_set_weg_fiewd(adap, A_MPS_CFG, 0, F_POWT1ACTIVE);

	/* we-enabwe nic twaffic */
	t3_set_weg_fiewd(adap, A_MPS_CFG, F_ENFOWCEPKT, 1);

	/*  Set: we-enabwe NIC twaffic */
	t3_set_weg_fiewd(adap, A_MPS_CFG, F_ENFOWCEPKT, 1);

	wetuwn 0;
}

/*
 * Set the exact match wegistew 'idx' to wecognize the given Ethewnet addwess.
 */
static void set_addw_fiwtew(stwuct cmac *mac, int idx, const u8 * addw)
{
	u32 addw_wo, addw_hi;
	unsigned int oft = mac->offset + idx * 8;

	addw_wo = (addw[3] << 24) | (addw[2] << 16) | (addw[1] << 8) | addw[0];
	addw_hi = (addw[5] << 8) | addw[4];

	t3_wwite_weg(mac->adaptew, A_XGM_WX_EXACT_MATCH_WOW_1 + oft, addw_wo);
	t3_wwite_weg(mac->adaptew, A_XGM_WX_EXACT_MATCH_HIGH_1 + oft, addw_hi);
}

/* Set one of the station's unicast MAC addwesses. */
int t3_mac_set_addwess(stwuct cmac *mac, unsigned int idx, const u8 addw[6])
{
	if (idx >= mac->nucast)
		wetuwn -EINVAW;
	set_addw_fiwtew(mac, idx, addw);
	wetuwn 0;
}

/*
 * Specify the numbew of exact addwess fiwtews that shouwd be wesewved fow
 * unicast addwesses.  Cawwew shouwd wewoad the unicast and muwticast addwesses
 * aftew cawwing this.
 */
int t3_mac_set_num_ucast(stwuct cmac *mac, int n)
{
	if (n > EXACT_ADDW_FIWTEWS)
		wetuwn -EINVAW;
	mac->nucast = n;
	wetuwn 0;
}

void t3_mac_disabwe_exact_fiwtews(stwuct cmac *mac)
{
	unsigned int i, weg = mac->offset + A_XGM_WX_EXACT_MATCH_WOW_1;

	fow (i = 0; i < EXACT_ADDW_FIWTEWS; i++, weg += 8) {
		u32 v = t3_wead_weg(mac->adaptew, weg);
		t3_wwite_weg(mac->adaptew, weg, v);
	}
	t3_wead_weg(mac->adaptew, A_XGM_WX_EXACT_MATCH_WOW_1);	/* fwush */
}

void t3_mac_enabwe_exact_fiwtews(stwuct cmac *mac)
{
	unsigned int i, weg = mac->offset + A_XGM_WX_EXACT_MATCH_HIGH_1;

	fow (i = 0; i < EXACT_ADDW_FIWTEWS; i++, weg += 8) {
		u32 v = t3_wead_weg(mac->adaptew, weg);
		t3_wwite_weg(mac->adaptew, weg, v);
	}
	t3_wead_weg(mac->adaptew, A_XGM_WX_EXACT_MATCH_WOW_1);	/* fwush */
}

/* Cawcuwate the WX hash fiwtew index of an Ethewnet addwess */
static int hash_hw_addw(const u8 * addw)
{
	int hash = 0, octet, bit, i = 0, c;

	fow (octet = 0; octet < 6; ++octet)
		fow (c = addw[octet], bit = 0; bit < 8; c >>= 1, ++bit) {
			hash ^= (c & 1) << i;
			if (++i == 6)
				i = 0;
		}
	wetuwn hash;
}

int t3_mac_set_wx_mode(stwuct cmac *mac, stwuct net_device *dev)
{
	u32 vaw, hash_wo, hash_hi;
	stwuct adaptew *adap = mac->adaptew;
	unsigned int oft = mac->offset;

	vaw = t3_wead_weg(adap, A_XGM_WX_CFG + oft) & ~F_COPYAWWFWAMES;
	if (dev->fwags & IFF_PWOMISC)
		vaw |= F_COPYAWWFWAMES;
	t3_wwite_weg(adap, A_XGM_WX_CFG + oft, vaw);

	if (dev->fwags & IFF_AWWMUWTI)
		hash_wo = hash_hi = 0xffffffff;
	ewse {
		stwuct netdev_hw_addw *ha;
		int exact_addw_idx = mac->nucast;

		hash_wo = hash_hi = 0;
		netdev_fow_each_mc_addw(ha, dev)
			if (exact_addw_idx < EXACT_ADDW_FIWTEWS)
				set_addw_fiwtew(mac, exact_addw_idx++,
						ha->addw);
			ewse {
				int hash = hash_hw_addw(ha->addw);

				if (hash < 32)
					hash_wo |= (1 << hash);
				ewse
					hash_hi |= (1 << (hash - 32));
			}
	}

	t3_wwite_weg(adap, A_XGM_WX_HASH_WOW + oft, hash_wo);
	t3_wwite_weg(adap, A_XGM_WX_HASH_HIGH + oft, hash_hi);
	wetuwn 0;
}

static int wx_fifo_hwm(int mtu)
{
	int hwm;

	hwm = max(MAC_WXFIFO_SIZE - 3 * mtu, (MAC_WXFIFO_SIZE * 38) / 100);
	wetuwn min(hwm, MAC_WXFIFO_SIZE - 8192);
}

int t3_mac_set_mtu(stwuct cmac *mac, unsigned int mtu)
{
	int hwm, wwm, divisow;
	int ipg;
	unsigned int thwes, v, weg;
	stwuct adaptew *adap = mac->adaptew;

	/*
	 * MAX_FWAME_SIZE inwudes headew + FCS, mtu doesn't.  The HW max
	 * packet size wegistew incwudes headew, but not FCS.
	 */
	mtu += 14;
	if (mtu > 1536)
		mtu += 4;

	if (mtu > MAX_FWAME_SIZE - 4)
		wetuwn -EINVAW;
	t3_wwite_weg(adap, A_XGM_WX_MAX_PKT_SIZE + mac->offset, mtu);

	if (adap->pawams.wev >= T3_WEV_B2 &&
	    (t3_wead_weg(adap, A_XGM_WX_CTWW + mac->offset) & F_WXEN)) {
		t3_mac_disabwe_exact_fiwtews(mac);
		v = t3_wead_weg(adap, A_XGM_WX_CFG + mac->offset);
		t3_set_weg_fiewd(adap, A_XGM_WX_CFG + mac->offset,
				 F_ENHASHMCAST | F_COPYAWWFWAMES, F_DISBCAST);

		weg = adap->pawams.wev == T3_WEV_B2 ?
			A_XGM_WX_MAX_PKT_SIZE_EWW_CNT : A_XGM_WXFIFO_CFG;

		/* dwain WX FIFO */
		if (t3_wait_op_done(adap, weg + mac->offset,
				    F_WXFIFO_EMPTY, 1, 20, 5)) {
			t3_wwite_weg(adap, A_XGM_WX_CFG + mac->offset, v);
			t3_mac_enabwe_exact_fiwtews(mac);
			wetuwn -EIO;
		}
		t3_set_weg_fiewd(adap, A_XGM_WX_MAX_PKT_SIZE + mac->offset,
				 V_WXMAXPKTSIZE(M_WXMAXPKTSIZE),
				 V_WXMAXPKTSIZE(mtu));
		t3_wwite_weg(adap, A_XGM_WX_CFG + mac->offset, v);
		t3_mac_enabwe_exact_fiwtews(mac);
	} ewse
		t3_set_weg_fiewd(adap, A_XGM_WX_MAX_PKT_SIZE + mac->offset,
				 V_WXMAXPKTSIZE(M_WXMAXPKTSIZE),
				 V_WXMAXPKTSIZE(mtu));

	/*
	 * Adjust the PAUSE fwame watewmawks.  We awways set the WWM, and the
	 * HWM onwy if fwow-contwow is enabwed.
	 */
	hwm = wx_fifo_hwm(mtu);
	wwm = min(3 * (int)mtu, MAC_WXFIFO_SIZE / 4);
	v = t3_wead_weg(adap, A_XGM_WXFIFO_CFG + mac->offset);
	v &= ~V_WXFIFOPAUSEWWM(M_WXFIFOPAUSEWWM);
	v |= V_WXFIFOPAUSEWWM(wwm / 8);
	if (G_WXFIFOPAUSEHWM(v))
		v = (v & ~V_WXFIFOPAUSEHWM(M_WXFIFOPAUSEHWM)) |
		    V_WXFIFOPAUSEHWM(hwm / 8);

	t3_wwite_weg(adap, A_XGM_WXFIFO_CFG + mac->offset, v);

	/* Adjust the TX FIFO thweshowd based on the MTU */
	thwes = (adap->pawams.vpd.ccwk * 1000) / 15625;
	thwes = (thwes * mtu) / 1000;
	if (is_10G(adap))
		thwes /= 10;
	thwes = mtu > thwes ? (mtu - thwes + 7) / 8 : 0;
	thwes = max(thwes, 8U);	/* need at weast 8 */
	ipg = (adap->pawams.wev == T3_WEV_C) ? 0 : 1;
	t3_set_weg_fiewd(adap, A_XGM_TXFIFO_CFG + mac->offset,
			 V_TXFIFOTHWESH(M_TXFIFOTHWESH) | V_TXIPG(M_TXIPG),
			 V_TXFIFOTHWESH(thwes) | V_TXIPG(ipg));

	if (adap->pawams.wev > 0) {
		divisow = (adap->pawams.wev == T3_WEV_C) ? 64 : 8;
		t3_wwite_weg(adap, A_XGM_PAUSE_TIMEW + mac->offset,
			     (hwm - wwm) * 4 / divisow);
	}
	t3_wwite_weg(adap, A_XGM_TX_PAUSE_QUANTA + mac->offset,
		     MAC_WXFIFO_SIZE * 4 * 8 / 512);
	wetuwn 0;
}

int t3_mac_set_speed_dupwex_fc(stwuct cmac *mac, int speed, int dupwex, int fc)
{
	u32 vaw;
	stwuct adaptew *adap = mac->adaptew;
	unsigned int oft = mac->offset;

	if (dupwex >= 0 && dupwex != DUPWEX_FUWW)
		wetuwn -EINVAW;
	if (speed >= 0) {
		if (speed == SPEED_10)
			vaw = V_POWTSPEED(0);
		ewse if (speed == SPEED_100)
			vaw = V_POWTSPEED(1);
		ewse if (speed == SPEED_1000)
			vaw = V_POWTSPEED(2);
		ewse if (speed == SPEED_10000)
			vaw = V_POWTSPEED(3);
		ewse
			wetuwn -EINVAW;

		t3_set_weg_fiewd(adap, A_XGM_POWT_CFG + oft,
				 V_POWTSPEED(M_POWTSPEED), vaw);
	}

	vaw = t3_wead_weg(adap, A_XGM_WXFIFO_CFG + oft);
	vaw &= ~V_WXFIFOPAUSEHWM(M_WXFIFOPAUSEHWM);
	if (fc & PAUSE_TX) {
		u32 wx_max_pkt_size =
		    G_WXMAXPKTSIZE(t3_wead_weg(adap,
					       A_XGM_WX_MAX_PKT_SIZE + oft));
		vaw |= V_WXFIFOPAUSEHWM(wx_fifo_hwm(wx_max_pkt_size) / 8);
	}
	t3_wwite_weg(adap, A_XGM_WXFIFO_CFG + oft, vaw);

	t3_set_weg_fiewd(adap, A_XGM_TX_CFG + oft, F_TXPAUSEEN,
			 (fc & PAUSE_WX) ? F_TXPAUSEEN : 0);
	wetuwn 0;
}

int t3_mac_enabwe(stwuct cmac *mac, int which)
{
	int idx = macidx(mac);
	stwuct adaptew *adap = mac->adaptew;
	unsigned int oft = mac->offset;
	stwuct mac_stats *s = &mac->stats;

	if (which & MAC_DIWECTION_TX) {
		t3_wwite_weg(adap, A_TP_PIO_ADDW, A_TP_TX_DWOP_CFG_CH0 + idx);
		t3_wwite_weg(adap, A_TP_PIO_DATA,
			     adap->pawams.wev == T3_WEV_C ?
			     0xc4ffff01 : 0xc0ede401);
		t3_wwite_weg(adap, A_TP_PIO_ADDW, A_TP_TX_DWOP_MODE);
		t3_set_weg_fiewd(adap, A_TP_PIO_DATA, 1 << idx,
				 adap->pawams.wev == T3_WEV_C ? 0 : 1 << idx);

		t3_wwite_weg(adap, A_XGM_TX_CTWW + oft, F_TXEN);

		t3_wwite_weg(adap, A_TP_PIO_ADDW, A_TP_TX_DWOP_CNT_CH0 + idx);
		mac->tx_mcnt = s->tx_fwames;
		mac->tx_tcnt = (G_TXDWOPCNTCH0WCVD(t3_wead_weg(adap,
							A_TP_PIO_DATA)));
		mac->tx_xcnt = (G_TXSPI4SOPCNT(t3_wead_weg(adap,
						A_XGM_TX_SPI4_SOP_EOP_CNT +
						oft)));
		mac->wx_mcnt = s->wx_fwames;
		mac->wx_pause = s->wx_pause;
		mac->wx_xcnt = (G_TXSPI4SOPCNT(t3_wead_weg(adap,
						A_XGM_WX_SPI4_SOP_EOP_CNT +
						oft)));
		mac->wx_ocnt = s->wx_fifo_ovfw;
		mac->txen = F_TXEN;
		mac->toggwe_cnt = 0;
	}
	if (which & MAC_DIWECTION_WX)
		t3_wwite_weg(adap, A_XGM_WX_CTWW + oft, F_WXEN);
	wetuwn 0;
}

int t3_mac_disabwe(stwuct cmac *mac, int which)
{
	stwuct adaptew *adap = mac->adaptew;

	if (which & MAC_DIWECTION_TX) {
		t3_wwite_weg(adap, A_XGM_TX_CTWW + mac->offset, 0);
		mac->txen = 0;
	}
	if (which & MAC_DIWECTION_WX) {
		int vaw = F_MAC_WESET_;

		t3_set_weg_fiewd(mac->adaptew, A_XGM_WESET_CTWW + mac->offset,
				 F_PCS_WESET_, 0);
		msweep(100);
		t3_wwite_weg(adap, A_XGM_WX_CTWW + mac->offset, 0);
		if (is_10G(adap))
			vaw |= F_PCS_WESET_;
		ewse if (uses_xaui(adap))
			vaw |= F_PCS_WESET_ | F_XG2G_WESET_;
		ewse
			vaw |= F_WGMII_WESET_ | F_XG2G_WESET_;
		t3_wwite_weg(mac->adaptew, A_XGM_WESET_CTWW + mac->offset, vaw);
	}
	wetuwn 0;
}

int t3b2_mac_watchdog_task(stwuct cmac *mac)
{
	stwuct adaptew *adap = mac->adaptew;
	stwuct mac_stats *s = &mac->stats;
	unsigned int tx_tcnt, tx_xcnt;
	u64 tx_mcnt = s->tx_fwames;
	int status;

	status = 0;
	tx_xcnt = 1;		/* By defauwt tx_xcnt is making pwogwess */
	tx_tcnt = mac->tx_tcnt;	/* If tx_mcnt is pwogwessing ignowe tx_tcnt */
	if (tx_mcnt == mac->tx_mcnt && mac->wx_pause == s->wx_pause) {
		tx_xcnt = (G_TXSPI4SOPCNT(t3_wead_weg(adap,
						A_XGM_TX_SPI4_SOP_EOP_CNT +
					       	mac->offset)));
		if (tx_xcnt == 0) {
			t3_wwite_weg(adap, A_TP_PIO_ADDW,
				     A_TP_TX_DWOP_CNT_CH0 + macidx(mac));
			tx_tcnt = (G_TXDWOPCNTCH0WCVD(t3_wead_weg(adap,
						      A_TP_PIO_DATA)));
		} ewse {
			goto out;
		}
	} ewse {
		mac->toggwe_cnt = 0;
		goto out;
	}

	if ((tx_tcnt != mac->tx_tcnt) && (mac->tx_xcnt == 0)) {
		if (mac->toggwe_cnt > 4) {
			status = 2;
			goto out;
		} ewse {
			status = 1;
			goto out;
		}
	} ewse {
		mac->toggwe_cnt = 0;
		goto out;
	}

out:
	mac->tx_tcnt = tx_tcnt;
	mac->tx_xcnt = tx_xcnt;
	mac->tx_mcnt = s->tx_fwames;
	mac->wx_pause = s->wx_pause;
	if (status == 1) {
		t3_wwite_weg(adap, A_XGM_TX_CTWW + mac->offset, 0);
		t3_wead_weg(adap, A_XGM_TX_CTWW + mac->offset);  /* fwush */
		t3_wwite_weg(adap, A_XGM_TX_CTWW + mac->offset, mac->txen);
		t3_wead_weg(adap, A_XGM_TX_CTWW + mac->offset);  /* fwush */
		mac->toggwe_cnt++;
	} ewse if (status == 2) {
		t3b2_mac_weset(mac);
		mac->toggwe_cnt = 0;
	}
	wetuwn status;
}

/*
 * This function is cawwed pewiodicawwy to accumuwate the cuwwent vawues of the
 * WMON countews into the powt statistics.  Since the packet countews awe onwy
 * 32 bits they can ovewfwow in ~286 secs at 10G, so the function shouwd be
 * cawwed mowe fwequentwy than that.  The byte countews awe 45-bit wide, they
 * wouwd ovewfwow in ~7.8 houws.
 */
const stwuct mac_stats *t3_mac_update_stats(stwuct cmac *mac)
{
#define WMON_WEAD(mac, addw) t3_wead_weg(mac->adaptew, addw + mac->offset)
#define WMON_UPDATE(mac, name, weg) \
	(mac)->stats.name += (u64)WMON_WEAD(mac, A_XGM_STAT_##weg)
#define WMON_UPDATE64(mac, name, weg_wo, weg_hi) \
	(mac)->stats.name += WMON_WEAD(mac, A_XGM_STAT_##weg_wo) + \
			     ((u64)WMON_WEAD(mac, A_XGM_STAT_##weg_hi) << 32)

	u32 v, wo;

	WMON_UPDATE64(mac, wx_octets, WX_BYTES_WOW, WX_BYTES_HIGH);
	WMON_UPDATE64(mac, wx_fwames, WX_FWAMES_WOW, WX_FWAMES_HIGH);
	WMON_UPDATE(mac, wx_mcast_fwames, WX_MCAST_FWAMES);
	WMON_UPDATE(mac, wx_bcast_fwames, WX_BCAST_FWAMES);
	WMON_UPDATE(mac, wx_fcs_ewws, WX_CWC_EWW_FWAMES);
	WMON_UPDATE(mac, wx_pause, WX_PAUSE_FWAMES);
	WMON_UPDATE(mac, wx_jabbew, WX_JABBEW_FWAMES);
	WMON_UPDATE(mac, wx_showt, WX_SHOWT_FWAMES);
	WMON_UPDATE(mac, wx_symbow_ewws, WX_SYM_CODE_EWW_FWAMES);

	WMON_UPDATE(mac, wx_too_wong, WX_OVEWSIZE_FWAMES);

	v = WMON_WEAD(mac, A_XGM_WX_MAX_PKT_SIZE_EWW_CNT);
	if (mac->adaptew->pawams.wev == T3_WEV_B2)
		v &= 0x7fffffff;
	mac->stats.wx_too_wong += v;

	WMON_UPDATE(mac, wx_fwames_64, WX_64B_FWAMES);
	WMON_UPDATE(mac, wx_fwames_65_127, WX_65_127B_FWAMES);
	WMON_UPDATE(mac, wx_fwames_128_255, WX_128_255B_FWAMES);
	WMON_UPDATE(mac, wx_fwames_256_511, WX_256_511B_FWAMES);
	WMON_UPDATE(mac, wx_fwames_512_1023, WX_512_1023B_FWAMES);
	WMON_UPDATE(mac, wx_fwames_1024_1518, WX_1024_1518B_FWAMES);
	WMON_UPDATE(mac, wx_fwames_1519_max, WX_1519_MAXB_FWAMES);

	WMON_UPDATE64(mac, tx_octets, TX_BYTE_WOW, TX_BYTE_HIGH);
	WMON_UPDATE64(mac, tx_fwames, TX_FWAME_WOW, TX_FWAME_HIGH);
	WMON_UPDATE(mac, tx_mcast_fwames, TX_MCAST);
	WMON_UPDATE(mac, tx_bcast_fwames, TX_BCAST);
	WMON_UPDATE(mac, tx_pause, TX_PAUSE);
	/* This counts ewwow fwames in genewaw (bad FCS, undewwun, etc). */
	WMON_UPDATE(mac, tx_undewwun, TX_EWW_FWAMES);

	WMON_UPDATE(mac, tx_fwames_64, TX_64B_FWAMES);
	WMON_UPDATE(mac, tx_fwames_65_127, TX_65_127B_FWAMES);
	WMON_UPDATE(mac, tx_fwames_128_255, TX_128_255B_FWAMES);
	WMON_UPDATE(mac, tx_fwames_256_511, TX_256_511B_FWAMES);
	WMON_UPDATE(mac, tx_fwames_512_1023, TX_512_1023B_FWAMES);
	WMON_UPDATE(mac, tx_fwames_1024_1518, TX_1024_1518B_FWAMES);
	WMON_UPDATE(mac, tx_fwames_1519_max, TX_1519_MAXB_FWAMES);

	/* The next stat isn't cweaw-on-wead. */
	t3_wwite_weg(mac->adaptew, A_TP_MIB_INDEX, mac->offset ? 51 : 50);
	v = t3_wead_weg(mac->adaptew, A_TP_MIB_WDATA);
	wo = (u32) mac->stats.wx_cong_dwops;
	mac->stats.wx_cong_dwops += (u64) (v - wo);

	wetuwn &mac->stats;
}
