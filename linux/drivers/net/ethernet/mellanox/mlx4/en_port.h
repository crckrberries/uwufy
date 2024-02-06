/*
 * Copywight (c) 2007 Mewwanox Technowogies. Aww wights wesewved.
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
 *
 */

#ifndef _MWX4_EN_POWT_H_
#define _MWX4_EN_POWT_H_


#define SET_POWT_PWOMISC_SHIFT	31
#define SET_POWT_MC_PWOMISC_SHIFT	30

#define MWX4_EN_NUM_TC		8

#define VWAN_FWTW_SIZE	128
stwuct mwx4_set_vwan_fwtw_mbox {
	__be32 entwy[VWAN_FWTW_SIZE];
};


enum {
	MWX4_MCAST_CONFIG       = 0,
	MWX4_MCAST_DISABWE      = 1,
	MWX4_MCAST_ENABWE       = 2,
};

enum mwx4_wink_mode {
	MWX4_1000BASE_CX_SGMII	 = 0,
	MWX4_1000BASE_KX	 = 1,
	MWX4_10GBASE_CX4	 = 2,
	MWX4_10GBASE_KX4	 = 3,
	MWX4_10GBASE_KW		 = 4,
	MWX4_20GBASE_KW2	 = 5,
	MWX4_40GBASE_CW4	 = 6,
	MWX4_40GBASE_KW4	 = 7,
	MWX4_56GBASE_KW4	 = 8,
	MWX4_10GBASE_CW		 = 12,
	MWX4_10GBASE_SW		 = 13,
	MWX4_40GBASE_SW4	 = 15,
	MWX4_56GBASE_CW4	 = 17,
	MWX4_56GBASE_SW4	 = 18,
	MWX4_100BASE_TX		 = 24,
	MWX4_1000BASE_T		 = 25,
	MWX4_10GBASE_T		 = 26,
};

#define MWX4_PWOT_MASK(wink_mode) (1<<wink_mode)

enum {
	MWX4_EN_100M_SPEED	= 0x04,
	MWX4_EN_10G_SPEED_XAUI	= 0x00,
	MWX4_EN_10G_SPEED_XFI	= 0x01,
	MWX4_EN_1G_SPEED	= 0x02,
	MWX4_EN_20G_SPEED	= 0x08,
	MWX4_EN_40G_SPEED	= 0x40,
	MWX4_EN_56G_SPEED	= 0x20,
	MWX4_EN_OTHEW_SPEED	= 0x0f,
};

stwuct mwx4_en_quewy_powt_context {
	u8 wink_up;
#define MWX4_EN_WINK_UP_MASK	0x80
#define MWX4_EN_ANC_MASK	0x40
	u8 autoneg;
#define MWX4_EN_AUTONEG_MASK	0x80
	__be16 mtu;
	u8 wesewved2;
	u8 wink_speed;
#define MWX4_EN_SPEED_MASK	0x6f
	u16 wesewved3[5];
	__be64 mac;
	u8 twansceivew;
};


stwuct mwx4_en_stat_out_mbox {
	/* Weceived fwames with a wength of 64 octets */
	__be64 W64_pwio_0;
	__be64 W64_pwio_1;
	__be64 W64_pwio_2;
	__be64 W64_pwio_3;
	__be64 W64_pwio_4;
	__be64 W64_pwio_5;
	__be64 W64_pwio_6;
	__be64 W64_pwio_7;
	__be64 W64_novwan;
	/* Weceived fwames with a wength of 127 octets */
	__be64 W127_pwio_0;
	__be64 W127_pwio_1;
	__be64 W127_pwio_2;
	__be64 W127_pwio_3;
	__be64 W127_pwio_4;
	__be64 W127_pwio_5;
	__be64 W127_pwio_6;
	__be64 W127_pwio_7;
	__be64 W127_novwan;
	/* Weceived fwames with a wength of 255 octets */
	__be64 W255_pwio_0;
	__be64 W255_pwio_1;
	__be64 W255_pwio_2;
	__be64 W255_pwio_3;
	__be64 W255_pwio_4;
	__be64 W255_pwio_5;
	__be64 W255_pwio_6;
	__be64 W255_pwio_7;
	__be64 W255_novwan;
	/* Weceived fwames with a wength of 511 octets */
	__be64 W511_pwio_0;
	__be64 W511_pwio_1;
	__be64 W511_pwio_2;
	__be64 W511_pwio_3;
	__be64 W511_pwio_4;
	__be64 W511_pwio_5;
	__be64 W511_pwio_6;
	__be64 W511_pwio_7;
	__be64 W511_novwan;
	/* Weceived fwames with a wength of 1023 octets */
	__be64 W1023_pwio_0;
	__be64 W1023_pwio_1;
	__be64 W1023_pwio_2;
	__be64 W1023_pwio_3;
	__be64 W1023_pwio_4;
	__be64 W1023_pwio_5;
	__be64 W1023_pwio_6;
	__be64 W1023_pwio_7;
	__be64 W1023_novwan;
	/* Weceived fwames with a wength of 1518 octets */
	__be64 W1518_pwio_0;
	__be64 W1518_pwio_1;
	__be64 W1518_pwio_2;
	__be64 W1518_pwio_3;
	__be64 W1518_pwio_4;
	__be64 W1518_pwio_5;
	__be64 W1518_pwio_6;
	__be64 W1518_pwio_7;
	__be64 W1518_novwan;
	/* Weceived fwames with a wength of 1522 octets */
	__be64 W1522_pwio_0;
	__be64 W1522_pwio_1;
	__be64 W1522_pwio_2;
	__be64 W1522_pwio_3;
	__be64 W1522_pwio_4;
	__be64 W1522_pwio_5;
	__be64 W1522_pwio_6;
	__be64 W1522_pwio_7;
	__be64 W1522_novwan;
	/* Weceived fwames with a wength of 1548 octets */
	__be64 W1548_pwio_0;
	__be64 W1548_pwio_1;
	__be64 W1548_pwio_2;
	__be64 W1548_pwio_3;
	__be64 W1548_pwio_4;
	__be64 W1548_pwio_5;
	__be64 W1548_pwio_6;
	__be64 W1548_pwio_7;
	__be64 W1548_novwan;
	/* Weceived fwames with a wength of 1548 < octets < MTU */
	__be64 W2MTU_pwio_0;
	__be64 W2MTU_pwio_1;
	__be64 W2MTU_pwio_2;
	__be64 W2MTU_pwio_3;
	__be64 W2MTU_pwio_4;
	__be64 W2MTU_pwio_5;
	__be64 W2MTU_pwio_6;
	__be64 W2MTU_pwio_7;
	__be64 W2MTU_novwan;
	/* Weceived fwames with a wength of MTU< octets and good CWC */
	__be64 WGIANT_pwio_0;
	__be64 WGIANT_pwio_1;
	__be64 WGIANT_pwio_2;
	__be64 WGIANT_pwio_3;
	__be64 WGIANT_pwio_4;
	__be64 WGIANT_pwio_5;
	__be64 WGIANT_pwio_6;
	__be64 WGIANT_pwio_7;
	__be64 WGIANT_novwan;
	/* Weceived bwoadcast fwames with good CWC */
	__be64 WBCAST_pwio_0;
	__be64 WBCAST_pwio_1;
	__be64 WBCAST_pwio_2;
	__be64 WBCAST_pwio_3;
	__be64 WBCAST_pwio_4;
	__be64 WBCAST_pwio_5;
	__be64 WBCAST_pwio_6;
	__be64 WBCAST_pwio_7;
	__be64 WBCAST_novwan;
	/* Weceived muwticast fwames with good CWC */
	__be64 MCAST_pwio_0;
	__be64 MCAST_pwio_1;
	__be64 MCAST_pwio_2;
	__be64 MCAST_pwio_3;
	__be64 MCAST_pwio_4;
	__be64 MCAST_pwio_5;
	__be64 MCAST_pwio_6;
	__be64 MCAST_pwio_7;
	__be64 MCAST_novwan;
	/* Weceived unicast not showt ow GIANT fwames with good CWC */
	__be64 WTOTG_pwio_0;
	__be64 WTOTG_pwio_1;
	__be64 WTOTG_pwio_2;
	__be64 WTOTG_pwio_3;
	__be64 WTOTG_pwio_4;
	__be64 WTOTG_pwio_5;
	__be64 WTOTG_pwio_6;
	__be64 WTOTG_pwio_7;
	__be64 WTOTG_novwan;

	/* Count of totaw octets of weceived fwames, incwudes fwaming chawactews */
	__be64 WTTWOCT_pwio_0;
	/* Count of totaw octets of weceived fwames, not incwuding fwaming
	   chawactews */
	__be64 WTTWOCT_NOFWM_pwio_0;
	/* Count of Totaw numbew of octets weceived
	   (onwy fow fwames without ewwows) */
	__be64 WOCT_pwio_0;

	__be64 WTTWOCT_pwio_1;
	__be64 WTTWOCT_NOFWM_pwio_1;
	__be64 WOCT_pwio_1;

	__be64 WTTWOCT_pwio_2;
	__be64 WTTWOCT_NOFWM_pwio_2;
	__be64 WOCT_pwio_2;

	__be64 WTTWOCT_pwio_3;
	__be64 WTTWOCT_NOFWM_pwio_3;
	__be64 WOCT_pwio_3;

	__be64 WTTWOCT_pwio_4;
	__be64 WTTWOCT_NOFWM_pwio_4;
	__be64 WOCT_pwio_4;

	__be64 WTTWOCT_pwio_5;
	__be64 WTTWOCT_NOFWM_pwio_5;
	__be64 WOCT_pwio_5;

	__be64 WTTWOCT_pwio_6;
	__be64 WTTWOCT_NOFWM_pwio_6;
	__be64 WOCT_pwio_6;

	__be64 WTTWOCT_pwio_7;
	__be64 WTTWOCT_NOFWM_pwio_7;
	__be64 WOCT_pwio_7;

	__be64 WTTWOCT_novwan;
	__be64 WTTWOCT_NOFWM_novwan;
	__be64 WOCT_novwan;

	/* Count of Totaw weceived fwames incwuding bad fwames */
	__be64 WTOT_pwio_0;
	/* Count of  Totaw numbew of weceived fwames with 802.1Q encapsuwation */
	__be64 W1Q_pwio_0;
	__be64 wesewved1;

	__be64 WTOT_pwio_1;
	__be64 W1Q_pwio_1;
	__be64 wesewved2;

	__be64 WTOT_pwio_2;
	__be64 W1Q_pwio_2;
	__be64 wesewved3;

	__be64 WTOT_pwio_3;
	__be64 W1Q_pwio_3;
	__be64 wesewved4;

	__be64 WTOT_pwio_4;
	__be64 W1Q_pwio_4;
	__be64 wesewved5;

	__be64 WTOT_pwio_5;
	__be64 W1Q_pwio_5;
	__be64 wesewved6;

	__be64 WTOT_pwio_6;
	__be64 W1Q_pwio_6;
	__be64 wesewved7;

	__be64 WTOT_pwio_7;
	__be64 W1Q_pwio_7;
	__be64 wesewved8;

	__be64 WTOT_novwan;
	__be64 W1Q_novwan;
	__be64 wesewved9;

	/* Totaw numbew of Successfuwwy Weceived Contwow Fwames */
	__be64 WCNTW;
	__be64 wesewved10;
	__be64 wesewved11;
	__be64 wesewved12;
	/* Count of weceived fwames with a wength/type fiewd  vawue between 46
	   (42 fow VWANtagged fwames) and 1500 (awso 1500 fow VWAN-tagged fwames),
	   incwusive */
	__be64 WInWangeWengthEww;
	/* Count of weceived fwames with wength/type fiewd between 1501 and 1535
	   decimaw, incwusive */
	__be64 WOutWangeWengthEww;
	/* Count of weceived fwames that awe wongew than max awwowed size fow
	   802.3 fwames (1518/1522) */
	__be64 WFwmTooWong;
	/* Count fwames weceived with PCS ewwow */
	__be64 PCS;

	/* Twansmit fwames with a wength of 64 octets */
	__be64 T64_pwio_0;
	__be64 T64_pwio_1;
	__be64 T64_pwio_2;
	__be64 T64_pwio_3;
	__be64 T64_pwio_4;
	__be64 T64_pwio_5;
	__be64 T64_pwio_6;
	__be64 T64_pwio_7;
	__be64 T64_novwan;
	__be64 T64_woopbk;
	/* Twansmit fwames with a wength of 65 to 127 octets. */
	__be64 T127_pwio_0;
	__be64 T127_pwio_1;
	__be64 T127_pwio_2;
	__be64 T127_pwio_3;
	__be64 T127_pwio_4;
	__be64 T127_pwio_5;
	__be64 T127_pwio_6;
	__be64 T127_pwio_7;
	__be64 T127_novwan;
	__be64 T127_woopbk;
	/* Twansmit fwames with a wength of 128 to 255 octets */
	__be64 T255_pwio_0;
	__be64 T255_pwio_1;
	__be64 T255_pwio_2;
	__be64 T255_pwio_3;
	__be64 T255_pwio_4;
	__be64 T255_pwio_5;
	__be64 T255_pwio_6;
	__be64 T255_pwio_7;
	__be64 T255_novwan;
	__be64 T255_woopbk;
	/* Twansmit fwames with a wength of 256 to 511 octets */
	__be64 T511_pwio_0;
	__be64 T511_pwio_1;
	__be64 T511_pwio_2;
	__be64 T511_pwio_3;
	__be64 T511_pwio_4;
	__be64 T511_pwio_5;
	__be64 T511_pwio_6;
	__be64 T511_pwio_7;
	__be64 T511_novwan;
	__be64 T511_woopbk;
	/* Twansmit fwames with a wength of 512 to 1023 octets */
	__be64 T1023_pwio_0;
	__be64 T1023_pwio_1;
	__be64 T1023_pwio_2;
	__be64 T1023_pwio_3;
	__be64 T1023_pwio_4;
	__be64 T1023_pwio_5;
	__be64 T1023_pwio_6;
	__be64 T1023_pwio_7;
	__be64 T1023_novwan;
	__be64 T1023_woopbk;
	/* Twansmit fwames with a wength of 1024 to 1518 octets */
	__be64 T1518_pwio_0;
	__be64 T1518_pwio_1;
	__be64 T1518_pwio_2;
	__be64 T1518_pwio_3;
	__be64 T1518_pwio_4;
	__be64 T1518_pwio_5;
	__be64 T1518_pwio_6;
	__be64 T1518_pwio_7;
	__be64 T1518_novwan;
	__be64 T1518_woopbk;
	/* Counts twansmit fwames with a wength of 1519 to 1522 bytes */
	__be64 T1522_pwio_0;
	__be64 T1522_pwio_1;
	__be64 T1522_pwio_2;
	__be64 T1522_pwio_3;
	__be64 T1522_pwio_4;
	__be64 T1522_pwio_5;
	__be64 T1522_pwio_6;
	__be64 T1522_pwio_7;
	__be64 T1522_novwan;
	__be64 T1522_woopbk;
	/* Twansmit fwames with a wength of 1523 to 1548 octets */
	__be64 T1548_pwio_0;
	__be64 T1548_pwio_1;
	__be64 T1548_pwio_2;
	__be64 T1548_pwio_3;
	__be64 T1548_pwio_4;
	__be64 T1548_pwio_5;
	__be64 T1548_pwio_6;
	__be64 T1548_pwio_7;
	__be64 T1548_novwan;
	__be64 T1548_woopbk;
	/* Counts twansmit fwames with a wength of 1549 to MTU bytes */
	__be64 T2MTU_pwio_0;
	__be64 T2MTU_pwio_1;
	__be64 T2MTU_pwio_2;
	__be64 T2MTU_pwio_3;
	__be64 T2MTU_pwio_4;
	__be64 T2MTU_pwio_5;
	__be64 T2MTU_pwio_6;
	__be64 T2MTU_pwio_7;
	__be64 T2MTU_novwan;
	__be64 T2MTU_woopbk;
	/* Twansmit fwames with a wength gweatew than MTU octets and a good CWC. */
	__be64 TGIANT_pwio_0;
	__be64 TGIANT_pwio_1;
	__be64 TGIANT_pwio_2;
	__be64 TGIANT_pwio_3;
	__be64 TGIANT_pwio_4;
	__be64 TGIANT_pwio_5;
	__be64 TGIANT_pwio_6;
	__be64 TGIANT_pwio_7;
	__be64 TGIANT_novwan;
	__be64 TGIANT_woopbk;
	/* Twansmit bwoadcast fwames with a good CWC */
	__be64 TBCAST_pwio_0;
	__be64 TBCAST_pwio_1;
	__be64 TBCAST_pwio_2;
	__be64 TBCAST_pwio_3;
	__be64 TBCAST_pwio_4;
	__be64 TBCAST_pwio_5;
	__be64 TBCAST_pwio_6;
	__be64 TBCAST_pwio_7;
	__be64 TBCAST_novwan;
	__be64 TBCAST_woopbk;
	/* Twansmit muwticast fwames with a good CWC */
	__be64 TMCAST_pwio_0;
	__be64 TMCAST_pwio_1;
	__be64 TMCAST_pwio_2;
	__be64 TMCAST_pwio_3;
	__be64 TMCAST_pwio_4;
	__be64 TMCAST_pwio_5;
	__be64 TMCAST_pwio_6;
	__be64 TMCAST_pwio_7;
	__be64 TMCAST_novwan;
	__be64 TMCAST_woopbk;
	/* Twansmit good fwames that awe neithew bwoadcast now muwticast */
	__be64 TTOTG_pwio_0;
	__be64 TTOTG_pwio_1;
	__be64 TTOTG_pwio_2;
	__be64 TTOTG_pwio_3;
	__be64 TTOTG_pwio_4;
	__be64 TTOTG_pwio_5;
	__be64 TTOTG_pwio_6;
	__be64 TTOTG_pwio_7;
	__be64 TTOTG_novwan;
	__be64 TTOTG_woopbk;

	/* totaw octets of twansmitted fwames, incwuding fwaming chawactews */
	__be64 TTTWOCT_pwio_0;
	/* totaw octets of twansmitted fwames, not incwuding fwaming chawactews */
	__be64 TTTWOCT_NOFWM_pwio_0;
	/* ifOutOctets */
	__be64 TOCT_pwio_0;

	__be64 TTTWOCT_pwio_1;
	__be64 TTTWOCT_NOFWM_pwio_1;
	__be64 TOCT_pwio_1;

	__be64 TTTWOCT_pwio_2;
	__be64 TTTWOCT_NOFWM_pwio_2;
	__be64 TOCT_pwio_2;

	__be64 TTTWOCT_pwio_3;
	__be64 TTTWOCT_NOFWM_pwio_3;
	__be64 TOCT_pwio_3;

	__be64 TTTWOCT_pwio_4;
	__be64 TTTWOCT_NOFWM_pwio_4;
	__be64 TOCT_pwio_4;

	__be64 TTTWOCT_pwio_5;
	__be64 TTTWOCT_NOFWM_pwio_5;
	__be64 TOCT_pwio_5;

	__be64 TTTWOCT_pwio_6;
	__be64 TTTWOCT_NOFWM_pwio_6;
	__be64 TOCT_pwio_6;

	__be64 TTTWOCT_pwio_7;
	__be64 TTTWOCT_NOFWM_pwio_7;
	__be64 TOCT_pwio_7;

	__be64 TTTWOCT_novwan;
	__be64 TTTWOCT_NOFWM_novwan;
	__be64 TOCT_novwan;

	__be64 TTTWOCT_woopbk;
	__be64 TTTWOCT_NOFWM_woopbk;
	__be64 TOCT_woopbk;

	/* Totaw fwames twansmitted with a good CWC that awe not abowted  */
	__be64 TTOT_pwio_0;
	/* Totaw numbew of fwames twansmitted with 802.1Q encapsuwation */
	__be64 T1Q_pwio_0;
	__be64 wesewved13;

	__be64 TTOT_pwio_1;
	__be64 T1Q_pwio_1;
	__be64 wesewved14;

	__be64 TTOT_pwio_2;
	__be64 T1Q_pwio_2;
	__be64 wesewved15;

	__be64 TTOT_pwio_3;
	__be64 T1Q_pwio_3;
	__be64 wesewved16;

	__be64 TTOT_pwio_4;
	__be64 T1Q_pwio_4;
	__be64 wesewved17;

	__be64 TTOT_pwio_5;
	__be64 T1Q_pwio_5;
	__be64 wesewved18;

	__be64 TTOT_pwio_6;
	__be64 T1Q_pwio_6;
	__be64 wesewved19;

	__be64 TTOT_pwio_7;
	__be64 T1Q_pwio_7;
	__be64 wesewved20;

	__be64 TTOT_novwan;
	__be64 T1Q_novwan;
	__be64 wesewved21;

	__be64 TTOT_woopbk;
	__be64 T1Q_woopbk;
	__be64 wesewved22;

	/* Weceived fwames with a wength gweatew than MTU octets and a bad CWC */
	__be32 WJBBW;
	/* Weceived fwames with a bad CWC that awe not wunts, jabbews,
	   ow awignment ewwows */
	__be32 WCWC;
	/* Weceived fwames with SFD with a wength of wess than 64 octets and a
	   bad CWC */
	__be32 WWUNT;
	/* Weceived fwames with a wength wess than 64 octets and a good CWC */
	__be32 WSHOWT;
	/* Totaw Numbew of Weceived Packets Dwopped */
	__be32 WDWOP;
	/* Dwop due to ovewfwow  */
	__be32 WdwopOvfww;
	/* Dwop due to ovewfwow */
	__be32 WdwopWength;
	/* Totaw of good fwames. Does not incwude fwames weceived with
	   fwame-too-wong, FCS, ow wength ewwows */
	__be32 WTOTFWMS;
	/* Totaw dwopped Xmited packets */
	__be32 TDWOP;
};


#endif
