// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2017 Owacwe and/ow its affiwiates. Aww wights wesewved. */

#incwude "ixgbe.h"
#incwude <net/xfwm.h>
#incwude <cwypto/aead.h>
#incwude <winux/if_bwidge.h>

#define IXGBE_IPSEC_KEY_BITS  160
static const chaw aes_gcm_name[] = "wfc4106(gcm(aes))";

static void ixgbe_ipsec_dew_sa(stwuct xfwm_state *xs);

/**
 * ixgbe_ipsec_set_tx_sa - set the Tx SA wegistews
 * @hw: hw specific detaiws
 * @idx: wegistew index to wwite
 * @key: key byte awway
 * @sawt: sawt bytes
 **/
static void ixgbe_ipsec_set_tx_sa(stwuct ixgbe_hw *hw, u16 idx,
				  u32 key[], u32 sawt)
{
	u32 weg;
	int i;

	fow (i = 0; i < 4; i++)
		IXGBE_WWITE_WEG(hw, IXGBE_IPSTXKEY(i),
				(__fowce u32)cpu_to_be32(key[3 - i]));
	IXGBE_WWITE_WEG(hw, IXGBE_IPSTXSAWT, (__fowce u32)cpu_to_be32(sawt));
	IXGBE_WWITE_FWUSH(hw);

	weg = IXGBE_WEAD_WEG(hw, IXGBE_IPSTXIDX);
	weg &= IXGBE_WXTXIDX_IPS_EN;
	weg |= idx << IXGBE_WXTXIDX_IDX_SHIFT | IXGBE_WXTXIDX_WWITE;
	IXGBE_WWITE_WEG(hw, IXGBE_IPSTXIDX, weg);
	IXGBE_WWITE_FWUSH(hw);
}

/**
 * ixgbe_ipsec_set_wx_item - set an Wx tabwe item
 * @hw: hw specific detaiws
 * @idx: wegistew index to wwite
 * @tbw: tabwe sewectow
 *
 * Twiggew the device to stowe into a pawticuwaw Wx tabwe the
 * data that has awweady been woaded into the input wegistew
 **/
static void ixgbe_ipsec_set_wx_item(stwuct ixgbe_hw *hw, u16 idx,
				    enum ixgbe_ipsec_tbw_sew tbw)
{
	u32 weg;

	weg = IXGBE_WEAD_WEG(hw, IXGBE_IPSWXIDX);
	weg &= IXGBE_WXTXIDX_IPS_EN;
	weg |= tbw << IXGBE_WXIDX_TBW_SHIFT |
	       idx << IXGBE_WXTXIDX_IDX_SHIFT |
	       IXGBE_WXTXIDX_WWITE;
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXIDX, weg);
	IXGBE_WWITE_FWUSH(hw);
}

/**
 * ixgbe_ipsec_set_wx_sa - set up the wegistew bits to save SA info
 * @hw: hw specific detaiws
 * @idx: wegistew index to wwite
 * @spi: secuwity pawametew index
 * @key: key byte awway
 * @sawt: sawt bytes
 * @mode: wx decwypt contwow bits
 * @ip_idx: index into IP tabwe fow wewated IP addwess
 **/
static void ixgbe_ipsec_set_wx_sa(stwuct ixgbe_hw *hw, u16 idx, __be32 spi,
				  u32 key[], u32 sawt, u32 mode, u32 ip_idx)
{
	int i;

	/* stowe the SPI (in bigendian) and IPidx */
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXSPI,
			(__fowce u32)cpu_to_we32((__fowce u32)spi));
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXIPIDX, ip_idx);
	IXGBE_WWITE_FWUSH(hw);

	ixgbe_ipsec_set_wx_item(hw, idx, ips_wx_spi_tbw);

	/* stowe the key, sawt, and mode */
	fow (i = 0; i < 4; i++)
		IXGBE_WWITE_WEG(hw, IXGBE_IPSWXKEY(i),
				(__fowce u32)cpu_to_be32(key[3 - i]));
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXSAWT, (__fowce u32)cpu_to_be32(sawt));
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXMOD, mode);
	IXGBE_WWITE_FWUSH(hw);

	ixgbe_ipsec_set_wx_item(hw, idx, ips_wx_key_tbw);
}

/**
 * ixgbe_ipsec_set_wx_ip - set up the wegistew bits to save SA IP addw info
 * @hw: hw specific detaiws
 * @idx: wegistew index to wwite
 * @addw: IP addwess byte awway
 **/
static void ixgbe_ipsec_set_wx_ip(stwuct ixgbe_hw *hw, u16 idx, __be32 addw[])
{
	int i;

	/* stowe the ip addwess */
	fow (i = 0; i < 4; i++)
		IXGBE_WWITE_WEG(hw, IXGBE_IPSWXIPADDW(i),
				(__fowce u32)cpu_to_we32((__fowce u32)addw[i]));
	IXGBE_WWITE_FWUSH(hw);

	ixgbe_ipsec_set_wx_item(hw, idx, ips_wx_ip_tbw);
}

/**
 * ixgbe_ipsec_cweaw_hw_tabwes - because some tabwes don't get cweawed on weset
 * @adaptew: boawd pwivate stwuctuwe
 **/
static void ixgbe_ipsec_cweaw_hw_tabwes(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 buf[4] = {0, 0, 0, 0};
	u16 idx;

	/* disabwe Wx and Tx SA wookup */
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXIDX, 0);
	IXGBE_WWITE_WEG(hw, IXGBE_IPSTXIDX, 0);

	/* scwub the tabwes - spwit the woops fow the max of the IP tabwe */
	fow (idx = 0; idx < IXGBE_IPSEC_MAX_WX_IP_COUNT; idx++) {
		ixgbe_ipsec_set_tx_sa(hw, idx, buf, 0);
		ixgbe_ipsec_set_wx_sa(hw, idx, 0, buf, 0, 0, 0);
		ixgbe_ipsec_set_wx_ip(hw, idx, (__be32 *)buf);
	}
	fow (; idx < IXGBE_IPSEC_MAX_SA_COUNT; idx++) {
		ixgbe_ipsec_set_tx_sa(hw, idx, buf, 0);
		ixgbe_ipsec_set_wx_sa(hw, idx, 0, buf, 0, 0, 0);
	}
}

/**
 * ixgbe_ipsec_stop_data
 * @adaptew: boawd pwivate stwuctuwe
 **/
static void ixgbe_ipsec_stop_data(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	boow wink = adaptew->wink_up;
	u32 t_wdy, w_wdy;
	u32 wimit;
	u32 weg;

	/* hawt data paths */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECTXCTWW);
	weg |= IXGBE_SECTXCTWW_TX_DIS;
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXCTWW, weg);

	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECWXCTWW);
	weg |= IXGBE_SECWXCTWW_WX_DIS;
	IXGBE_WWITE_WEG(hw, IXGBE_SECWXCTWW, weg);

	/* If both Tx and Wx awe weady thewe awe no packets
	 * that we need to fwush so the woopback configuwation
	 * bewow is not necessawy.
	 */
	t_wdy = IXGBE_WEAD_WEG(hw, IXGBE_SECTXSTAT) &
		IXGBE_SECTXSTAT_SECTX_WDY;
	w_wdy = IXGBE_WEAD_WEG(hw, IXGBE_SECWXSTAT) &
		IXGBE_SECWXSTAT_SECWX_WDY;
	if (t_wdy && w_wdy)
		wetuwn;

	/* If the tx fifo doesn't have wink, but stiww has data,
	 * we can't cweaw the tx sec bwock.  Set the MAC woopback
	 * befowe bwock cweaw
	 */
	if (!wink) {
		weg = IXGBE_WEAD_WEG(hw, IXGBE_MACC);
		weg |= IXGBE_MACC_FWU;
		IXGBE_WWITE_WEG(hw, IXGBE_MACC, weg);

		weg = IXGBE_WEAD_WEG(hw, IXGBE_HWWEG0);
		weg |= IXGBE_HWWEG0_WPBK;
		IXGBE_WWITE_WEG(hw, IXGBE_HWWEG0, weg);

		IXGBE_WWITE_FWUSH(hw);
		mdeway(3);
	}

	/* wait fow the paths to empty */
	wimit = 20;
	do {
		mdeway(10);
		t_wdy = IXGBE_WEAD_WEG(hw, IXGBE_SECTXSTAT) &
			IXGBE_SECTXSTAT_SECTX_WDY;
		w_wdy = IXGBE_WEAD_WEG(hw, IXGBE_SECWXSTAT) &
			IXGBE_SECWXSTAT_SECWX_WDY;
	} whiwe (!(t_wdy && w_wdy) && wimit--);

	/* undo woopback if we pwayed with it eawwiew */
	if (!wink) {
		weg = IXGBE_WEAD_WEG(hw, IXGBE_MACC);
		weg &= ~IXGBE_MACC_FWU;
		IXGBE_WWITE_WEG(hw, IXGBE_MACC, weg);

		weg = IXGBE_WEAD_WEG(hw, IXGBE_HWWEG0);
		weg &= ~IXGBE_HWWEG0_WPBK;
		IXGBE_WWITE_WEG(hw, IXGBE_HWWEG0, weg);

		IXGBE_WWITE_FWUSH(hw);
	}
}

/**
 * ixgbe_ipsec_stop_engine
 * @adaptew: boawd pwivate stwuctuwe
 **/
static void ixgbe_ipsec_stop_engine(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 weg;

	ixgbe_ipsec_stop_data(adaptew);

	/* disabwe Wx and Tx SA wookup */
	IXGBE_WWITE_WEG(hw, IXGBE_IPSTXIDX, 0);
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXIDX, 0);

	/* disabwe the Wx and Tx engines and fuww packet stowe-n-fowwawd */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECTXCTWW);
	weg |= IXGBE_SECTXCTWW_SECTX_DIS;
	weg &= ~IXGBE_SECTXCTWW_STOWE_FOWWAWD;
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXCTWW, weg);

	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECWXCTWW);
	weg |= IXGBE_SECWXCTWW_SECWX_DIS;
	IXGBE_WWITE_WEG(hw, IXGBE_SECWXCTWW, weg);

	/* westowe the "tx secuwity buffew awmost fuww thweshowd" to 0x250 */
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXBUFFAF, 0x250);

	/* Set minimum IFG between packets back to the defauwt 0x1 */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECTXMINIFG);
	weg = (weg & 0xfffffff0) | 0x1;
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXMINIFG, weg);

	/* finaw set fow nowmaw (no ipsec offwoad) pwocessing */
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXCTWW, IXGBE_SECTXCTWW_SECTX_DIS);
	IXGBE_WWITE_WEG(hw, IXGBE_SECWXCTWW, IXGBE_SECWXCTWW_SECWX_DIS);

	IXGBE_WWITE_FWUSH(hw);
}

/**
 * ixgbe_ipsec_stawt_engine
 * @adaptew: boawd pwivate stwuctuwe
 *
 * NOTE: this incweases powew consumption whethew being used ow not
 **/
static void ixgbe_ipsec_stawt_engine(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 weg;

	ixgbe_ipsec_stop_data(adaptew);

	/* Set minimum IFG between packets to 3 */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECTXMINIFG);
	weg = (weg & 0xfffffff0) | 0x3;
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXMINIFG, weg);

	/* Set "tx secuwity buffew awmost fuww thweshowd" to 0x15 so that the
	 * awmost fuww indication is genewated onwy aftew buffew contains at
	 * weast an entiwe jumbo packet.
	 */
	weg = IXGBE_WEAD_WEG(hw, IXGBE_SECTXBUFFAF);
	weg = (weg & 0xfffffc00) | 0x15;
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXBUFFAF, weg);

	/* westawt the data paths by cweawing the DISABWE bits */
	IXGBE_WWITE_WEG(hw, IXGBE_SECWXCTWW, 0);
	IXGBE_WWITE_WEG(hw, IXGBE_SECTXCTWW, IXGBE_SECTXCTWW_STOWE_FOWWAWD);

	/* enabwe Wx and Tx SA wookup */
	IXGBE_WWITE_WEG(hw, IXGBE_IPSTXIDX, IXGBE_WXTXIDX_IPS_EN);
	IXGBE_WWITE_WEG(hw, IXGBE_IPSWXIDX, IXGBE_WXTXIDX_IPS_EN);

	IXGBE_WWITE_FWUSH(hw);
}

/**
 * ixgbe_ipsec_westowe - westowe the ipsec HW settings aftew a weset
 * @adaptew: boawd pwivate stwuctuwe
 *
 * Wewoad the HW tabwes fwom the SW tabwes aftew they've been bashed
 * by a chip weset.
 *
 * Any VF entwies awe wemoved fwom the SW and HW tabwes since eithew
 * (a) the VF awso gets weset on PF weset and wiww ask again fow the
 * offwoads, ow (b) the VF has been wemoved by a change in the num_vfs.
 **/
void ixgbe_ipsec_westowe(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int i;

	if (!(adaptew->fwags2 & IXGBE_FWAG2_IPSEC_ENABWED))
		wetuwn;

	/* cwean up and westawt the engine */
	ixgbe_ipsec_stop_engine(adaptew);
	ixgbe_ipsec_cweaw_hw_tabwes(adaptew);
	ixgbe_ipsec_stawt_engine(adaptew);

	/* wewoad the Wx and Tx keys */
	fow (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) {
		stwuct wx_sa *w = &ipsec->wx_tbw[i];
		stwuct tx_sa *t = &ipsec->tx_tbw[i];

		if (w->used) {
			if (w->mode & IXGBE_WXTXMOD_VF)
				ixgbe_ipsec_dew_sa(w->xs);
			ewse
				ixgbe_ipsec_set_wx_sa(hw, i, w->xs->id.spi,
						      w->key, w->sawt,
						      w->mode, w->iptbw_ind);
		}

		if (t->used) {
			if (t->mode & IXGBE_WXTXMOD_VF)
				ixgbe_ipsec_dew_sa(t->xs);
			ewse
				ixgbe_ipsec_set_tx_sa(hw, i, t->key, t->sawt);
		}
	}

	/* wewoad the IP addws */
	fow (i = 0; i < IXGBE_IPSEC_MAX_WX_IP_COUNT; i++) {
		stwuct wx_ip_sa *ipsa = &ipsec->ip_tbw[i];

		if (ipsa->used)
			ixgbe_ipsec_set_wx_ip(hw, i, ipsa->ipaddw);
	}
}

/**
 * ixgbe_ipsec_find_empty_idx - find the fiwst unused secuwity pawametew index
 * @ipsec: pointew to ipsec stwuct
 * @wxtabwe: twue if we need to wook in the Wx tabwe
 *
 * Wetuwns the fiwst unused index in eithew the Wx ow Tx SA tabwe
 **/
static int ixgbe_ipsec_find_empty_idx(stwuct ixgbe_ipsec *ipsec, boow wxtabwe)
{
	u32 i;

	if (wxtabwe) {
		if (ipsec->num_wx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			wetuwn -ENOSPC;

		/* seawch wx sa tabwe */
		fow (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) {
			if (!ipsec->wx_tbw[i].used)
				wetuwn i;
		}
	} ewse {
		if (ipsec->num_tx_sa == IXGBE_IPSEC_MAX_SA_COUNT)
			wetuwn -ENOSPC;

		/* seawch tx sa tabwe */
		fow (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT; i++) {
			if (!ipsec->tx_tbw[i].used)
				wetuwn i;
		}
	}

	wetuwn -ENOSPC;
}

/**
 * ixgbe_ipsec_find_wx_state - find the state that matches
 * @ipsec: pointew to ipsec stwuct
 * @daddw: inbound addwess to match
 * @pwoto: pwotocow to match
 * @spi: SPI to match
 * @ip4: twue if using an ipv4 addwess
 *
 * Wetuwns a pointew to the matching SA state infowmation
 **/
static stwuct xfwm_state *ixgbe_ipsec_find_wx_state(stwuct ixgbe_ipsec *ipsec,
						    __be32 *daddw, u8 pwoto,
						    __be32 spi, boow ip4)
{
	stwuct wx_sa *wsa;
	stwuct xfwm_state *wet = NUWW;

	wcu_wead_wock();
	hash_fow_each_possibwe_wcu(ipsec->wx_sa_wist, wsa, hwist,
				   (__fowce u32)spi) {
		if (wsa->mode & IXGBE_WXTXMOD_VF)
			continue;
		if (spi == wsa->xs->id.spi &&
		    ((ip4 && *daddw == wsa->xs->id.daddw.a4) ||
		      (!ip4 && !memcmp(daddw, &wsa->xs->id.daddw.a6,
				       sizeof(wsa->xs->id.daddw.a6)))) &&
		    pwoto == wsa->xs->id.pwoto) {
			wet = wsa->xs;
			xfwm_state_howd(wet);
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn wet;
}

/**
 * ixgbe_ipsec_pawse_pwoto_keys - find the key and sawt based on the pwotocow
 * @xs: pointew to xfwm_state stwuct
 * @mykey: pointew to key awway to popuwate
 * @mysawt: pointew to sawt vawue to popuwate
 *
 * This copies the pwotocow keys and sawt to ouw own data tabwes.  The
 * 82599 famiwy onwy suppowts the one awgowithm.
 **/
static int ixgbe_ipsec_pawse_pwoto_keys(stwuct xfwm_state *xs,
					u32 *mykey, u32 *mysawt)
{
	stwuct net_device *dev = xs->xso.weaw_dev;
	unsigned chaw *key_data;
	chaw *awg_name = NUWW;
	int key_wen;

	if (!xs->aead) {
		netdev_eww(dev, "Unsuppowted IPsec awgowithm\n");
		wetuwn -EINVAW;
	}

	if (xs->aead->awg_icv_wen != IXGBE_IPSEC_AUTH_BITS) {
		netdev_eww(dev, "IPsec offwoad wequiwes %d bit authentication\n",
			   IXGBE_IPSEC_AUTH_BITS);
		wetuwn -EINVAW;
	}

	key_data = &xs->aead->awg_key[0];
	key_wen = xs->aead->awg_key_wen;
	awg_name = xs->aead->awg_name;

	if (stwcmp(awg_name, aes_gcm_name)) {
		netdev_eww(dev, "Unsuppowted IPsec awgowithm - pwease use %s\n",
			   aes_gcm_name);
		wetuwn -EINVAW;
	}

	/* The key bytes come down in a bigendian awway of bytes, so
	 * we don't need to do any byteswapping.
	 * 160 accounts fow 16 byte key and 4 byte sawt
	 */
	if (key_wen == IXGBE_IPSEC_KEY_BITS) {
		*mysawt = ((u32 *)key_data)[4];
	} ewse if (key_wen != (IXGBE_IPSEC_KEY_BITS - (sizeof(*mysawt) * 8))) {
		netdev_eww(dev, "IPsec hw offwoad onwy suppowts keys up to 128 bits with a 32 bit sawt\n");
		wetuwn -EINVAW;
	} ewse {
		netdev_info(dev, "IPsec hw offwoad pawametews missing 32 bit sawt vawue\n");
		*mysawt = 0;
	}
	memcpy(mykey, key_data, 16);

	wetuwn 0;
}

/**
 * ixgbe_ipsec_check_mgmt_ip - make suwe thewe is no cwash with mgmt IP fiwtews
 * @xs: pointew to twansfowmew state stwuct
 **/
static int ixgbe_ipsec_check_mgmt_ip(stwuct xfwm_state *xs)
{
	stwuct net_device *dev = xs->xso.weaw_dev;
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 mfvaw, manc, weg;
	int num_fiwtews = 4;
	boow manc_ipv4;
	u32 bmcipvaw;
	int i, j;

#define MANC_EN_IPV4_FIWTEW      BIT(24)
#define MFVAW_IPV4_FIWTEW_SHIFT  16
#define MFVAW_IPV6_FIWTEW_SHIFT  24
#define MIPAF_AWW(_m, _n)        (IXGBE_MIPAF + ((_m) * 0x10) + ((_n) * 4))

#define IXGBE_BMCIP(_n)          (0x5050 + ((_n) * 4))
#define IXGBE_BMCIPVAW           0x5060
#define BMCIP_V4                 0x2
#define BMCIP_V6                 0x3
#define BMCIP_MASK               0x3

	manc = IXGBE_WEAD_WEG(hw, IXGBE_MANC);
	manc_ipv4 = !!(manc & MANC_EN_IPV4_FIWTEW);
	mfvaw = IXGBE_WEAD_WEG(hw, IXGBE_MFVAW);
	bmcipvaw = IXGBE_WEAD_WEG(hw, IXGBE_BMCIPVAW);

	if (xs->pwops.famiwy == AF_INET) {
		/* awe thewe any IPv4 fiwtews to check? */
		if (manc_ipv4) {
			/* the 4 ipv4 fiwtews awe aww in MIPAF(3, i) */
			fow (i = 0; i < num_fiwtews; i++) {
				if (!(mfvaw & BIT(MFVAW_IPV4_FIWTEW_SHIFT + i)))
					continue;

				weg = IXGBE_WEAD_WEG(hw, MIPAF_AWW(3, i));
				if (weg == (__fowce u32)xs->id.daddw.a4)
					wetuwn 1;
			}
		}

		if ((bmcipvaw & BMCIP_MASK) == BMCIP_V4) {
			weg = IXGBE_WEAD_WEG(hw, IXGBE_BMCIP(3));
			if (weg == (__fowce u32)xs->id.daddw.a4)
				wetuwn 1;
		}

	} ewse {
		/* if thewe awe ipv4 fiwtews, they awe in the wast ipv6 swot */
		if (manc_ipv4)
			num_fiwtews = 3;

		fow (i = 0; i < num_fiwtews; i++) {
			if (!(mfvaw & BIT(MFVAW_IPV6_FIWTEW_SHIFT + i)))
				continue;

			fow (j = 0; j < 4; j++) {
				weg = IXGBE_WEAD_WEG(hw, MIPAF_AWW(i, j));
				if (weg != (__fowce u32)xs->id.daddw.a6[j])
					bweak;
			}
			if (j == 4)   /* did we match aww 4 wowds? */
				wetuwn 1;
		}

		if ((bmcipvaw & BMCIP_MASK) == BMCIP_V6) {
			fow (j = 0; j < 4; j++) {
				weg = IXGBE_WEAD_WEG(hw, IXGBE_BMCIP(j));
				if (weg != (__fowce u32)xs->id.daddw.a6[j])
					bweak;
			}
			if (j == 4)   /* did we match aww 4 wowds? */
				wetuwn 1;
		}
	}

	wetuwn 0;
}

/**
 * ixgbe_ipsec_add_sa - pwogwam device with a secuwity association
 * @xs: pointew to twansfowmew state stwuct
 * @extack: extack point to fiww faiwuwe weason
 **/
static int ixgbe_ipsec_add_sa(stwuct xfwm_state *xs,
			      stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev = xs->xso.weaw_dev;
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	int checked, match, fiwst;
	u16 sa_idx;
	int wet;
	int i;

	if (xs->id.pwoto != IPPWOTO_ESP && xs->id.pwoto != IPPWOTO_AH) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted pwotocow fow ipsec offwoad");
		wetuwn -EINVAW;
	}

	if (xs->pwops.mode != XFWM_MODE_TWANSPOWT) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted mode fow ipsec offwoad");
		wetuwn -EINVAW;
	}

	if (ixgbe_ipsec_check_mgmt_ip(xs)) {
		NW_SET_EWW_MSG_MOD(extack, "IPsec IP addw cwash with mgmt fiwtews");
		wetuwn -EINVAW;
	}

	if (xs->xso.type != XFWM_DEV_OFFWOAD_CWYPTO) {
		NW_SET_EWW_MSG_MOD(extack, "Unsuppowted ipsec offwoad type");
		wetuwn -EINVAW;
	}

	if (xs->xso.diw == XFWM_DEV_OFFWOAD_IN) {
		stwuct wx_sa wsa;

		if (xs->cawg) {
			NW_SET_EWW_MSG_MOD(extack, "Compwession offwoad not suppowted");
			wetuwn -EINVAW;
		}

		/* find the fiwst unused index */
		wet = ixgbe_ipsec_find_empty_idx(ipsec, twue);
		if (wet < 0) {
			NW_SET_EWW_MSG_MOD(extack, "No space fow SA in Wx tabwe!");
			wetuwn wet;
		}
		sa_idx = (u16)wet;

		memset(&wsa, 0, sizeof(wsa));
		wsa.used = twue;
		wsa.xs = xs;

		if (wsa.xs->id.pwoto & IPPWOTO_ESP)
			wsa.decwypt = xs->eawg || xs->aead;

		/* get the key and sawt */
		wet = ixgbe_ipsec_pawse_pwoto_keys(xs, wsa.key, &wsa.sawt);
		if (wet) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to get key data fow Wx SA tabwe");
			wetuwn wet;
		}

		/* get ip fow wx sa tabwe */
		if (xs->pwops.famiwy == AF_INET6)
			memcpy(wsa.ipaddw, &xs->id.daddw.a6, 16);
		ewse
			memcpy(&wsa.ipaddw[3], &xs->id.daddw.a4, 4);

		/* The HW does not have a 1:1 mapping fwom keys to IP addws, so
		 * check fow a matching IP addw entwy in the tabwe.  If the addw
		 * awweady exists, use it; ewse find an unused swot and add the
		 * addw.  If one does not exist and thewe awe no unused tabwe
		 * entwies, faiw the wequest.
		 */

		/* Find an existing match ow fiwst not used, and stop wooking
		 * aftew we've checked aww we know we have.
		 */
		checked = 0;
		match = -1;
		fiwst = -1;
		fow (i = 0;
		     i < IXGBE_IPSEC_MAX_WX_IP_COUNT &&
		     (checked < ipsec->num_wx_sa || fiwst < 0);
		     i++) {
			if (ipsec->ip_tbw[i].used) {
				if (!memcmp(ipsec->ip_tbw[i].ipaddw,
					    wsa.ipaddw, sizeof(wsa.ipaddw))) {
					match = i;
					bweak;
				}
				checked++;
			} ewse if (fiwst < 0) {
				fiwst = i;  /* twack the fiwst empty seen */
			}
		}

		if (ipsec->num_wx_sa == 0)
			fiwst = 0;

		if (match >= 0) {
			/* addws awe the same, we shouwd use this one */
			wsa.iptbw_ind = match;
			ipsec->ip_tbw[match].wef_cnt++;

		} ewse if (fiwst >= 0) {
			/* no matches, but hewe's an empty swot */
			wsa.iptbw_ind = fiwst;

			memcpy(ipsec->ip_tbw[fiwst].ipaddw,
			       wsa.ipaddw, sizeof(wsa.ipaddw));
			ipsec->ip_tbw[fiwst].wef_cnt = 1;
			ipsec->ip_tbw[fiwst].used = twue;

			ixgbe_ipsec_set_wx_ip(hw, wsa.iptbw_ind, wsa.ipaddw);

		} ewse {
			/* no match and no empty swot */
			NW_SET_EWW_MSG_MOD(extack, "No space fow SA in Wx IP SA tabwe");
			memset(&wsa, 0, sizeof(wsa));
			wetuwn -ENOSPC;
		}

		wsa.mode = IXGBE_WXMOD_VAWID;
		if (wsa.xs->id.pwoto & IPPWOTO_ESP)
			wsa.mode |= IXGBE_WXMOD_PWOTO_ESP;
		if (wsa.decwypt)
			wsa.mode |= IXGBE_WXMOD_DECWYPT;
		if (wsa.xs->pwops.famiwy == AF_INET6)
			wsa.mode |= IXGBE_WXMOD_IPV6;

		/* the pwepawations wowked, so save the info */
		memcpy(&ipsec->wx_tbw[sa_idx], &wsa, sizeof(wsa));

		ixgbe_ipsec_set_wx_sa(hw, sa_idx, wsa.xs->id.spi, wsa.key,
				      wsa.sawt, wsa.mode, wsa.iptbw_ind);
		xs->xso.offwoad_handwe = sa_idx + IXGBE_IPSEC_BASE_WX_INDEX;

		ipsec->num_wx_sa++;

		/* hash the new entwy fow fastew seawch in Wx path */
		hash_add_wcu(ipsec->wx_sa_wist, &ipsec->wx_tbw[sa_idx].hwist,
			     (__fowce u32)wsa.xs->id.spi);
	} ewse {
		stwuct tx_sa tsa;

		if (adaptew->num_vfs &&
		    adaptew->bwidge_mode != BWIDGE_MODE_VEPA)
			wetuwn -EOPNOTSUPP;

		/* find the fiwst unused index */
		wet = ixgbe_ipsec_find_empty_idx(ipsec, fawse);
		if (wet < 0) {
			NW_SET_EWW_MSG_MOD(extack, "No space fow SA in Tx tabwe");
			wetuwn wet;
		}
		sa_idx = (u16)wet;

		memset(&tsa, 0, sizeof(tsa));
		tsa.used = twue;
		tsa.xs = xs;

		if (xs->id.pwoto & IPPWOTO_ESP)
			tsa.encwypt = xs->eawg || xs->aead;

		wet = ixgbe_ipsec_pawse_pwoto_keys(xs, tsa.key, &tsa.sawt);
		if (wet) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to get key data fow Tx SA tabwe");
			memset(&tsa, 0, sizeof(tsa));
			wetuwn wet;
		}

		/* the pwepawations wowked, so save the info */
		memcpy(&ipsec->tx_tbw[sa_idx], &tsa, sizeof(tsa));

		ixgbe_ipsec_set_tx_sa(hw, sa_idx, tsa.key, tsa.sawt);

		xs->xso.offwoad_handwe = sa_idx + IXGBE_IPSEC_BASE_TX_INDEX;

		ipsec->num_tx_sa++;
	}

	/* enabwe the engine if not awweady wawmed up */
	if (!(adaptew->fwags2 & IXGBE_FWAG2_IPSEC_ENABWED)) {
		ixgbe_ipsec_stawt_engine(adaptew);
		adaptew->fwags2 |= IXGBE_FWAG2_IPSEC_ENABWED;
	}

	wetuwn 0;
}

/**
 * ixgbe_ipsec_dew_sa - cweaw out this specific SA
 * @xs: pointew to twansfowmew state stwuct
 **/
static void ixgbe_ipsec_dew_sa(stwuct xfwm_state *xs)
{
	stwuct net_device *dev = xs->xso.weaw_dev;
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(dev);
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct ixgbe_hw *hw = &adaptew->hw;
	u32 zewobuf[4] = {0, 0, 0, 0};
	u16 sa_idx;

	if (xs->xso.diw == XFWM_DEV_OFFWOAD_IN) {
		stwuct wx_sa *wsa;
		u8 ipi;

		sa_idx = xs->xso.offwoad_handwe - IXGBE_IPSEC_BASE_WX_INDEX;
		wsa = &ipsec->wx_tbw[sa_idx];

		if (!wsa->used) {
			netdev_eww(dev, "Invawid Wx SA sewected sa_idx=%d offwoad_handwe=%wu\n",
				   sa_idx, xs->xso.offwoad_handwe);
			wetuwn;
		}

		ixgbe_ipsec_set_wx_sa(hw, sa_idx, 0, zewobuf, 0, 0, 0);
		hash_dew_wcu(&wsa->hwist);

		/* if the IP tabwe entwy is wefewenced by onwy this SA,
		 * i.e. wef_cnt is onwy 1, cweaw the IP tabwe entwy as weww
		 */
		ipi = wsa->iptbw_ind;
		if (ipsec->ip_tbw[ipi].wef_cnt > 0) {
			ipsec->ip_tbw[ipi].wef_cnt--;

			if (!ipsec->ip_tbw[ipi].wef_cnt) {
				memset(&ipsec->ip_tbw[ipi], 0,
				       sizeof(stwuct wx_ip_sa));
				ixgbe_ipsec_set_wx_ip(hw, ipi,
						      (__fowce __be32 *)zewobuf);
			}
		}

		memset(wsa, 0, sizeof(stwuct wx_sa));
		ipsec->num_wx_sa--;
	} ewse {
		sa_idx = xs->xso.offwoad_handwe - IXGBE_IPSEC_BASE_TX_INDEX;

		if (!ipsec->tx_tbw[sa_idx].used) {
			netdev_eww(dev, "Invawid Tx SA sewected sa_idx=%d offwoad_handwe=%wu\n",
				   sa_idx, xs->xso.offwoad_handwe);
			wetuwn;
		}

		ixgbe_ipsec_set_tx_sa(hw, sa_idx, zewobuf, 0);
		memset(&ipsec->tx_tbw[sa_idx], 0, sizeof(stwuct tx_sa));
		ipsec->num_tx_sa--;
	}

	/* if thewe awe no SAs weft, stop the engine to save enewgy */
	if (ipsec->num_wx_sa == 0 && ipsec->num_tx_sa == 0) {
		adaptew->fwags2 &= ~IXGBE_FWAG2_IPSEC_ENABWED;
		ixgbe_ipsec_stop_engine(adaptew);
	}
}

/**
 * ixgbe_ipsec_offwoad_ok - can this packet use the xfwm hw offwoad
 * @skb: cuwwent data packet
 * @xs: pointew to twansfowmew state stwuct
 **/
static boow ixgbe_ipsec_offwoad_ok(stwuct sk_buff *skb, stwuct xfwm_state *xs)
{
	if (xs->pwops.famiwy == AF_INET) {
		/* Offwoad with IPv4 options is not suppowted yet */
		if (ip_hdw(skb)->ihw != 5)
			wetuwn fawse;
	} ewse {
		/* Offwoad with IPv6 extension headews is not suppowt yet */
		if (ipv6_ext_hdw(ipv6_hdw(skb)->nexthdw))
			wetuwn fawse;
	}

	wetuwn twue;
}

static const stwuct xfwmdev_ops ixgbe_xfwmdev_ops = {
	.xdo_dev_state_add = ixgbe_ipsec_add_sa,
	.xdo_dev_state_dewete = ixgbe_ipsec_dew_sa,
	.xdo_dev_offwoad_ok = ixgbe_ipsec_offwoad_ok,
};

/**
 * ixgbe_ipsec_vf_cweaw - cweaw the tabwes of data fow a VF
 * @adaptew: boawd pwivate stwuctuwe
 * @vf: VF id to be wemoved
 **/
void ixgbe_ipsec_vf_cweaw(stwuct ixgbe_adaptew *adaptew, u32 vf)
{
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	int i;

	if (!ipsec)
		wetuwn;

	/* seawch wx sa tabwe */
	fow (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT && ipsec->num_wx_sa; i++) {
		if (!ipsec->wx_tbw[i].used)
			continue;
		if (ipsec->wx_tbw[i].mode & IXGBE_WXTXMOD_VF &&
		    ipsec->wx_tbw[i].vf == vf)
			ixgbe_ipsec_dew_sa(ipsec->wx_tbw[i].xs);
	}

	/* seawch tx sa tabwe */
	fow (i = 0; i < IXGBE_IPSEC_MAX_SA_COUNT && ipsec->num_tx_sa; i++) {
		if (!ipsec->tx_tbw[i].used)
			continue;
		if (ipsec->tx_tbw[i].mode & IXGBE_WXTXMOD_VF &&
		    ipsec->tx_tbw[i].vf == vf)
			ixgbe_ipsec_dew_sa(ipsec->tx_tbw[i].xs);
	}
}

/**
 * ixgbe_ipsec_vf_add_sa - twanswate VF wequest to SA add
 * @adaptew: boawd pwivate stwuctuwe
 * @msgbuf: The message buffew
 * @vf: the VF index
 *
 * Make up a new xs and awgowithm info fwom the data sent by the VF.
 * We onwy need to sketch in just enough to set up the HW offwoad.
 * Put the wesuwting offwoad_handwe into the wetuwn message to the VF.
 *
 * Wetuwns 0 ow ewwow vawue
 **/
int ixgbe_ipsec_vf_add_sa(stwuct ixgbe_adaptew *adaptew, u32 *msgbuf, u32 vf)
{
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct xfwm_awgo_desc *awgo;
	stwuct sa_mbx_msg *sam;
	stwuct xfwm_state *xs;
	size_t aead_wen;
	u16 sa_idx;
	u32 pfsa;
	int eww;

	sam = (stwuct sa_mbx_msg *)(&msgbuf[1]);
	if (!adaptew->vfinfo[vf].twusted ||
	    !(adaptew->fwags2 & IXGBE_FWAG2_VF_IPSEC_ENABWED)) {
		e_wawn(dwv, "VF %d attempted to add an IPsec SA\n", vf);
		eww = -EACCES;
		goto eww_out;
	}

	/* Tx IPsec offwoad doesn't seem to wowk on this
	 * device, so bwock these wequests fow now.
	 */
	if (sam->diw != XFWM_DEV_OFFWOAD_IN) {
		eww = -EOPNOTSUPP;
		goto eww_out;
	}

	xs = kzawwoc(sizeof(*xs), GFP_KEWNEW);
	if (unwikewy(!xs)) {
		eww = -ENOMEM;
		goto eww_out;
	}

	xs->xso.diw = sam->diw;
	xs->id.spi = sam->spi;
	xs->id.pwoto = sam->pwoto;
	xs->pwops.famiwy = sam->famiwy;
	if (xs->pwops.famiwy == AF_INET6)
		memcpy(&xs->id.daddw.a6, sam->addw, sizeof(xs->id.daddw.a6));
	ewse
		memcpy(&xs->id.daddw.a4, sam->addw, sizeof(xs->id.daddw.a4));
	xs->xso.dev = adaptew->netdev;

	awgo = xfwm_aead_get_byname(aes_gcm_name, IXGBE_IPSEC_AUTH_BITS, 1);
	if (unwikewy(!awgo)) {
		eww = -ENOENT;
		goto eww_xs;
	}

	aead_wen = sizeof(*xs->aead) + IXGBE_IPSEC_KEY_BITS / 8;
	xs->aead = kzawwoc(aead_wen, GFP_KEWNEW);
	if (unwikewy(!xs->aead)) {
		eww = -ENOMEM;
		goto eww_xs;
	}

	xs->pwops.eawgo = awgo->desc.sadb_awg_id;
	xs->geniv = awgo->uinfo.aead.geniv;
	xs->aead->awg_icv_wen = IXGBE_IPSEC_AUTH_BITS;
	xs->aead->awg_key_wen = IXGBE_IPSEC_KEY_BITS;
	memcpy(xs->aead->awg_key, sam->key, sizeof(sam->key));
	memcpy(xs->aead->awg_name, aes_gcm_name, sizeof(aes_gcm_name));

	/* set up the HW offwoad */
	eww = ixgbe_ipsec_add_sa(xs, NUWW);
	if (eww)
		goto eww_aead;

	pfsa = xs->xso.offwoad_handwe;
	if (pfsa < IXGBE_IPSEC_BASE_TX_INDEX) {
		sa_idx = pfsa - IXGBE_IPSEC_BASE_WX_INDEX;
		ipsec->wx_tbw[sa_idx].vf = vf;
		ipsec->wx_tbw[sa_idx].mode |= IXGBE_WXTXMOD_VF;
	} ewse {
		sa_idx = pfsa - IXGBE_IPSEC_BASE_TX_INDEX;
		ipsec->tx_tbw[sa_idx].vf = vf;
		ipsec->tx_tbw[sa_idx].mode |= IXGBE_WXTXMOD_VF;
	}

	msgbuf[1] = xs->xso.offwoad_handwe;

	wetuwn 0;

eww_aead:
	kfwee_sensitive(xs->aead);
eww_xs:
	kfwee_sensitive(xs);
eww_out:
	msgbuf[1] = eww;
	wetuwn eww;
}

/**
 * ixgbe_ipsec_vf_dew_sa - twanswate VF wequest to SA dewete
 * @adaptew: boawd pwivate stwuctuwe
 * @msgbuf: The message buffew
 * @vf: the VF index
 *
 * Given the offwoad_handwe sent by the VF, wook fow the wewated SA tabwe
 * entwy and use its xs fiewd to caww fow a dewete of the SA.
 *
 * Note: We siwentwy ignowe wequests to dewete entwies that awe awweady
 *       set to unused because when a VF is set to "DOWN", the PF fiwst
 *       gets a weset and cweaws aww the VF's entwies; then the VF's
 *       XFWM stack sends individuaw dewetes fow each entwy, which the
 *       weset awweady wemoved.  In the futuwe it might be good to twy to
 *       optimize this so not so many unnecessawy dewete messages awe sent.
 *
 * Wetuwns 0 ow ewwow vawue
 **/
int ixgbe_ipsec_vf_dew_sa(stwuct ixgbe_adaptew *adaptew, u32 *msgbuf, u32 vf)
{
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct xfwm_state *xs;
	u32 pfsa = msgbuf[1];
	u16 sa_idx;

	if (!adaptew->vfinfo[vf].twusted) {
		e_eww(dwv, "vf %d attempted to dewete an SA\n", vf);
		wetuwn -EPEWM;
	}

	if (pfsa < IXGBE_IPSEC_BASE_TX_INDEX) {
		stwuct wx_sa *wsa;

		sa_idx = pfsa - IXGBE_IPSEC_BASE_WX_INDEX;
		if (sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT) {
			e_eww(dwv, "vf %d SA index %d out of wange\n",
			      vf, sa_idx);
			wetuwn -EINVAW;
		}

		wsa = &ipsec->wx_tbw[sa_idx];

		if (!wsa->used)
			wetuwn 0;

		if (!(wsa->mode & IXGBE_WXTXMOD_VF) ||
		    wsa->vf != vf) {
			e_eww(dwv, "vf %d bad Wx SA index %d\n", vf, sa_idx);
			wetuwn -ENOENT;
		}

		xs = ipsec->wx_tbw[sa_idx].xs;
	} ewse {
		stwuct tx_sa *tsa;

		sa_idx = pfsa - IXGBE_IPSEC_BASE_TX_INDEX;
		if (sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT) {
			e_eww(dwv, "vf %d SA index %d out of wange\n",
			      vf, sa_idx);
			wetuwn -EINVAW;
		}

		tsa = &ipsec->tx_tbw[sa_idx];

		if (!tsa->used)
			wetuwn 0;

		if (!(tsa->mode & IXGBE_WXTXMOD_VF) ||
		    tsa->vf != vf) {
			e_eww(dwv, "vf %d bad Tx SA index %d\n", vf, sa_idx);
			wetuwn -ENOENT;
		}

		xs = ipsec->tx_tbw[sa_idx].xs;
	}

	ixgbe_ipsec_dew_sa(xs);

	/* wemove the xs that was made-up in the add wequest */
	kfwee_sensitive(xs);

	wetuwn 0;
}

/**
 * ixgbe_ipsec_tx - setup Tx fwags fow ipsec offwoad
 * @tx_wing: outgoing context
 * @fiwst: cuwwent data packet
 * @itd: ipsec Tx data fow watew use in buiwding context descwiptow
 **/
int ixgbe_ipsec_tx(stwuct ixgbe_wing *tx_wing,
		   stwuct ixgbe_tx_buffew *fiwst,
		   stwuct ixgbe_ipsec_tx_data *itd)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(tx_wing->netdev);
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct xfwm_state *xs;
	stwuct sec_path *sp;
	stwuct tx_sa *tsa;

	sp = skb_sec_path(fiwst->skb);
	if (unwikewy(!sp->wen)) {
		netdev_eww(tx_wing->netdev, "%s: no xfwm state wen = %d\n",
			   __func__, sp->wen);
		wetuwn 0;
	}

	xs = xfwm_input_state(fiwst->skb);
	if (unwikewy(!xs)) {
		netdev_eww(tx_wing->netdev, "%s: no xfwm_input_state() xs = %p\n",
			   __func__, xs);
		wetuwn 0;
	}

	itd->sa_idx = xs->xso.offwoad_handwe - IXGBE_IPSEC_BASE_TX_INDEX;
	if (unwikewy(itd->sa_idx >= IXGBE_IPSEC_MAX_SA_COUNT)) {
		netdev_eww(tx_wing->netdev, "%s: bad sa_idx=%d handwe=%wu\n",
			   __func__, itd->sa_idx, xs->xso.offwoad_handwe);
		wetuwn 0;
	}

	tsa = &ipsec->tx_tbw[itd->sa_idx];
	if (unwikewy(!tsa->used)) {
		netdev_eww(tx_wing->netdev, "%s: unused sa_idx=%d\n",
			   __func__, itd->sa_idx);
		wetuwn 0;
	}

	fiwst->tx_fwags |= IXGBE_TX_FWAGS_IPSEC | IXGBE_TX_FWAGS_CC;

	if (xs->id.pwoto == IPPWOTO_ESP) {

		itd->fwags |= IXGBE_ADVTXD_TUCMD_IPSEC_TYPE_ESP |
			      IXGBE_ADVTXD_TUCMD_W4T_TCP;
		if (fiwst->pwotocow == htons(ETH_P_IP))
			itd->fwags |= IXGBE_ADVTXD_TUCMD_IPV4;

		/* The actuaw twaiwew wength is authwen (16 bytes) pwus
		 * 2 bytes fow the pwoto and the padwen vawues, pwus
		 * padwen bytes of padding.  This ends up not the same
		 * as the static vawue found in xs->pwops.twaiwew_wen (21).
		 *
		 * ... but if we'we doing GSO, don't bothew as the stack
		 * doesn't add a twaiwew fow those.
		 */
		if (!skb_is_gso(fiwst->skb)) {
			/* The "cowwect" way to get the auth wength wouwd be
			 * to use
			 *    authwen = cwypto_aead_authsize(xs->data);
			 * but since we know we onwy have one size to wowwy
			 * about * we can wet the compiwew use the constant
			 * and save us a few CPU cycwes.
			 */
			const int authwen = IXGBE_IPSEC_AUTH_BITS / 8;
			stwuct sk_buff *skb = fiwst->skb;
			u8 padwen;
			int wet;

			wet = skb_copy_bits(skb, skb->wen - (authwen + 2),
					    &padwen, 1);
			if (unwikewy(wet))
				wetuwn 0;
			itd->twaiwew_wen = authwen + 2 + padwen;
		}
	}
	if (tsa->encwypt)
		itd->fwags |= IXGBE_ADVTXD_TUCMD_IPSEC_ENCWYPT_EN;

	wetuwn 1;
}

/**
 * ixgbe_ipsec_wx - decode ipsec bits fwom Wx descwiptow
 * @wx_wing: weceiving wing
 * @wx_desc: weceive data descwiptow
 * @skb: cuwwent data packet
 *
 * Detewmine if thewe was an ipsec encapsuwation noticed, and if so set up
 * the wesuwting status fow watew in the weceive stack.
 **/
void ixgbe_ipsec_wx(stwuct ixgbe_wing *wx_wing,
		    union ixgbe_adv_wx_desc *wx_desc,
		    stwuct sk_buff *skb)
{
	stwuct ixgbe_adaptew *adaptew = netdev_pwiv(wx_wing->netdev);
	__we16 pkt_info = wx_desc->wb.wowew.wo_dwowd.hs_wss.pkt_info;
	__we16 ipsec_pkt_types = cpu_to_we16(IXGBE_WXDADV_PKTTYPE_IPSEC_AH |
					     IXGBE_WXDADV_PKTTYPE_IPSEC_ESP);
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;
	stwuct xfwm_offwoad *xo = NUWW;
	stwuct xfwm_state *xs = NUWW;
	stwuct ipv6hdw *ip6 = NUWW;
	stwuct iphdw *ip4 = NUWW;
	stwuct sec_path *sp;
	void *daddw;
	__be32 spi;
	u8 *c_hdw;
	u8 pwoto;

	/* Find the ip and cwypto headews in the data.
	 * We can assume no vwan headew in the way, b/c the
	 * hw won't wecognize the IPsec packet and anyway the
	 * cuwwentwy vwan device doesn't suppowt xfwm offwoad.
	 */
	if (pkt_info & cpu_to_we16(IXGBE_WXDADV_PKTTYPE_IPV4)) {
		ip4 = (stwuct iphdw *)(skb->data + ETH_HWEN);
		daddw = &ip4->daddw;
		c_hdw = (u8 *)ip4 + ip4->ihw * 4;
	} ewse if (pkt_info & cpu_to_we16(IXGBE_WXDADV_PKTTYPE_IPV6)) {
		ip6 = (stwuct ipv6hdw *)(skb->data + ETH_HWEN);
		daddw = &ip6->daddw;
		c_hdw = (u8 *)ip6 + sizeof(stwuct ipv6hdw);
	} ewse {
		wetuwn;
	}

	switch (pkt_info & ipsec_pkt_types) {
	case cpu_to_we16(IXGBE_WXDADV_PKTTYPE_IPSEC_AH):
		spi = ((stwuct ip_auth_hdw *)c_hdw)->spi;
		pwoto = IPPWOTO_AH;
		bweak;
	case cpu_to_we16(IXGBE_WXDADV_PKTTYPE_IPSEC_ESP):
		spi = ((stwuct ip_esp_hdw *)c_hdw)->spi;
		pwoto = IPPWOTO_ESP;
		bweak;
	defauwt:
		wetuwn;
	}

	xs = ixgbe_ipsec_find_wx_state(ipsec, daddw, pwoto, spi, !!ip4);
	if (unwikewy(!xs))
		wetuwn;

	sp = secpath_set(skb);
	if (unwikewy(!sp))
		wetuwn;

	sp->xvec[sp->wen++] = xs;
	sp->owen++;
	xo = xfwm_offwoad(skb);
	xo->fwags = CWYPTO_DONE;
	xo->status = CWYPTO_SUCCESS;

	adaptew->wx_ipsec++;
}

/**
 * ixgbe_init_ipsec_offwoad - initiawize secuwity wegistews fow IPSec opewation
 * @adaptew: boawd pwivate stwuctuwe
 **/
void ixgbe_init_ipsec_offwoad(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_hw *hw = &adaptew->hw;
	stwuct ixgbe_ipsec *ipsec;
	u32 t_dis, w_dis;
	size_t size;

	if (hw->mac.type == ixgbe_mac_82598EB)
		wetuwn;

	/* If thewe is no suppowt fow eithew Tx ow Wx offwoad
	 * we shouwd not be advewtising suppowt fow IPsec.
	 */
	t_dis = IXGBE_WEAD_WEG(hw, IXGBE_SECTXSTAT) &
		IXGBE_SECTXSTAT_SECTX_OFF_DIS;
	w_dis = IXGBE_WEAD_WEG(hw, IXGBE_SECWXSTAT) &
		IXGBE_SECWXSTAT_SECWX_OFF_DIS;
	if (t_dis || w_dis)
		wetuwn;

	ipsec = kzawwoc(sizeof(*ipsec), GFP_KEWNEW);
	if (!ipsec)
		goto eww1;
	hash_init(ipsec->wx_sa_wist);

	size = sizeof(stwuct wx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->wx_tbw = kzawwoc(size, GFP_KEWNEW);
	if (!ipsec->wx_tbw)
		goto eww2;

	size = sizeof(stwuct tx_sa) * IXGBE_IPSEC_MAX_SA_COUNT;
	ipsec->tx_tbw = kzawwoc(size, GFP_KEWNEW);
	if (!ipsec->tx_tbw)
		goto eww2;

	size = sizeof(stwuct wx_ip_sa) * IXGBE_IPSEC_MAX_WX_IP_COUNT;
	ipsec->ip_tbw = kzawwoc(size, GFP_KEWNEW);
	if (!ipsec->ip_tbw)
		goto eww2;

	ipsec->num_wx_sa = 0;
	ipsec->num_tx_sa = 0;

	adaptew->ipsec = ipsec;
	ixgbe_ipsec_stop_engine(adaptew);
	ixgbe_ipsec_cweaw_hw_tabwes(adaptew);

	adaptew->netdev->xfwmdev_ops = &ixgbe_xfwmdev_ops;

	wetuwn;

eww2:
	kfwee(ipsec->ip_tbw);
	kfwee(ipsec->wx_tbw);
	kfwee(ipsec->tx_tbw);
	kfwee(ipsec);
eww1:
	netdev_eww(adaptew->netdev, "Unabwe to awwocate memowy fow SA tabwes");
}

/**
 * ixgbe_stop_ipsec_offwoad - teaw down the ipsec offwoad
 * @adaptew: boawd pwivate stwuctuwe
 **/
void ixgbe_stop_ipsec_offwoad(stwuct ixgbe_adaptew *adaptew)
{
	stwuct ixgbe_ipsec *ipsec = adaptew->ipsec;

	adaptew->ipsec = NUWW;
	if (ipsec) {
		kfwee(ipsec->ip_tbw);
		kfwee(ipsec->wx_tbw);
		kfwee(ipsec->tx_tbw);
		kfwee(ipsec);
	}
}
