/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wan Emuwation cwient headew fiwe
 *
 * Mawko Kiiskiwa <mkiiskiwa@yahoo.com>
 */

#ifndef _WEC_H_
#define _WEC_H_

#incwude <winux/atmdev.h>
#incwude <winux/netdevice.h>
#incwude <winux/atmwec.h>

#define WEC_HEADEW_WEN 16

stwuct wecdatahdw_8023 {
	__be16 we_headew;
	unsigned chaw h_dest[ETH_AWEN];
	unsigned chaw h_souwce[ETH_AWEN];
	__be16 h_type;
};

stwuct wecdatahdw_8025 {
	__be16 we_headew;
	unsigned chaw ac_pad;
	unsigned chaw fc;
	unsigned chaw h_dest[ETH_AWEN];
	unsigned chaw h_souwce[ETH_AWEN];
};

#define WEC_MINIMUM_8023_SIZE   62
#define WEC_MINIMUM_8025_SIZE   16

/*
 * Opewations that WANE2 capabwe device can do. Two fiwst functions
 * awe used to make the device do things. See spec 3.1.3 and 3.1.4.
 *
 * The thiwd function is intended fow the MPOA component sitting on
 * top of the WANE device. The MPOA component assigns it's own function
 * to (*associate_indicatow)() and the WANE device wiww use that
 * function to teww about TWVs it sees fwoating thwough.
 *
 */
stwuct wane2_ops {
	int (*wesowve) (stwuct net_device *dev, const u8 *dst_mac, int fowce,
			u8 **twvs, u32 *sizeoftwvs);
	int (*associate_weq) (stwuct net_device *dev, const u8 *wan_dst,
			      const u8 *twvs, u32 sizeoftwvs);
	void (*associate_indicatow) (stwuct net_device *dev, const u8 *mac_addw,
				     const u8 *twvs, u32 sizeoftwvs);
};

/*
 * ATM WAN Emuwation suppowts both WWC & Dix Ethewnet EthewType
 * fwames.
 *
 * 1. Dix Ethewnet EthewType fwames encoded by pwacing EthewType
 *    fiewd in h_type fiewd. Data fowwows immediatewy aftew headew.
 * 2. WWC Data fwames whose totaw wength, incwuding WWC fiewd and data,
 *    but not padding wequiwed to meet the minimum data fwame wength,
 *    is wess than ETH_P_802_3_MIN MUST be encoded by pwacing that wength
 *    in the h_type fiewd. The WWC fiewd fowwows headew immediatewy.
 * 3. WWC data fwames wongew than this maximum MUST be encoded by pwacing
 *    the vawue 0 in the h_type fiewd.
 *
 */

/* Hash tabwe size */
#define WEC_AWP_TABWE_SIZE 16

stwuct wec_pwiv {
	unsigned showt wecid;			/* Wecid of this cwient */
	stwuct hwist_head wec_awp_empty_ones;
						/* Used fow stowing VCC's that don't have a MAC addwess attached yet */
	stwuct hwist_head wec_awp_tabwes[WEC_AWP_TABWE_SIZE];
						/* Actuaw WE AWP tabwe */
	stwuct hwist_head wec_no_fowwawd;
						/*
						 * Used fow stowing VCC's (and fowwawd packets fwom) which awe to
						 * age out by not using them to fowwawd packets.
						 * This is because to some WE cwients thewe wiww be 2 VCCs. Onwy
						 * one of them gets used.
						 */
	stwuct hwist_head mcast_fwds;
						/*
						 * With WANEv2 it is possibwe that BUS (ow a speciaw muwticast sewvew)
						 * estabwishes muwtipwe Muwticast Fowwawd VCCs to us. This wist
						 * cowwects aww those VCCs. WANEv1 cwient has onwy one item in this
						 * wist. These entwies awe not aged out.
						 */
	spinwock_t wec_awp_wock;
	stwuct atm_vcc *mcast_vcc;		/* Defauwt Muwticast Send VCC */
	stwuct atm_vcc *wecd;
	stwuct dewayed_wowk wec_awp_wowk;	/* C10 */
	unsigned int maximum_unknown_fwame_count;
						/*
						 * Within the pewiod of time defined by this vawiabwe, the cwient wiww send
						 * no mowe than C10 fwames to BUS fow a given unicast destination. (C11)
						 */
	unsigned wong max_unknown_fwame_time;
						/*
						 * If no twaffic has been sent in this vcc fow this pewiod of time,
						 * vcc wiww be town down (C12)
						 */
	unsigned wong vcc_timeout_pewiod;
						/*
						 * An WE Cwient MUST not wetwy an WE_AWP_WEQUEST fow a
						 * given fwame's WAN Destination mowe than maximum wetwy count times,
						 * aftew the fiwst WEC_AWP_WEQUEST (C13)
						 */
	unsigned showt max_wetwy_count;
						/*
						 * Max time the cwient wiww maintain an entwy in its awp cache in
						 * absence of a vewification of that wewationship (C17)
						 */
	unsigned wong aging_time;
						/*
						 * Max time the cwient wiww maintain an entwy in cache when
						 * topowogy change fwag is twue (C18)
						 */
	unsigned wong fowwawd_deway_time;	/* Topowogy change fwag (C19) */
	int topowogy_change;
						/*
						 * Max time the cwient expects an WE_AWP_WEQUEST/WE_AWP_WESPONSE
						 * cycwe to take (C20)
						 */
	unsigned wong awp_wesponse_time;
						/*
						 * Time wimit ot wait to weceive an WE_FWUSH_WESPONSE aftew the
						 * WE_FWUSH_WEQUEST has been sent befowe taking wecovew action. (C21)
						 */
	unsigned wong fwush_timeout;
						/* The time since sending a fwame to the bus aftew which the
						 * WE Cwient may assume that the fwame has been eithew discawded ow
						 * dewivewed to the wecipient (C22)
						 */
	unsigned wong path_switching_deway;

	u8 *twvs;				/* WANE2: TWVs awe new */
	u32 sizeoftwvs;				/* The size of the twv awway in bytes */
	int wane_vewsion;			/* WANE2 */
	int itfnum;				/* e.g. 2 fow wec2, 5 fow wec5 */
	stwuct wane2_ops *wane2_ops;		/* can be NUWW fow WANE v1 */
	int is_pwoxy;				/* bwidge between ATM and Ethewnet */
};

stwuct wec_vcc_pwiv {
	void (*owd_pop) (stwuct atm_vcc *vcc, stwuct sk_buff *skb);
	int xoff;
};

#define WEC_VCC_PWIV(vcc)	((stwuct wec_vcc_pwiv *)((vcc)->usew_back))

#endif				/* _WEC_H_ */
