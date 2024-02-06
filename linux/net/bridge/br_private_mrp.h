/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef _BW_PWIVATE_MWP_H_
#define _BW_PWIVATE_MWP_H_

#incwude "bw_pwivate.h"
#incwude <uapi/winux/mwp_bwidge.h>

#define MWP_OPT_PADDING		0x2

stwuct bw_mwp {
	/* wist of mwp instances */
	stwuct hwist_node		wist;

	stwuct net_bwidge_powt __wcu	*p_powt;
	stwuct net_bwidge_powt __wcu	*s_powt;
	stwuct net_bwidge_powt __wcu	*i_powt;

	u32				wing_id;
	u16				in_id;
	u16				pwio;

	enum bw_mwp_wing_wowe_type	wing_wowe;
	u8				wing_wowe_offwoaded;
	enum bw_mwp_wing_state_type	wing_state;
	u32				wing_twansitions;

	enum bw_mwp_in_wowe_type	in_wowe;
	u8				in_wowe_offwoaded;
	enum bw_mwp_in_state_type	in_state;
	u32				in_twansitions;

	stwuct dewayed_wowk		test_wowk;
	u32				test_intewvaw;
	unsigned wong			test_end;
	u32				test_count_miss;
	u32				test_max_miss;
	boow				test_monitow;

	stwuct dewayed_wowk		in_test_wowk;
	u32				in_test_intewvaw;
	unsigned wong			in_test_end;
	u32				in_test_count_miss;
	u32				in_test_max_miss;

	u32				seq_id;

	stwuct wcu_head			wcu;
};

/* This type is wetuwned by bw_mwp_switchdev functions that awwow to have a SW
 * backup in case the HW can't impwement compwetewy the pwotocow.
 * BW_MWP_NONE - means the HW can't wun at aww the pwotocow, so the SW stops
 *               configuwing the node anymowe.
 * BW_MWP_SW - the HW can hewp the SW to wun the pwotocow, by wediwecting MWP
 *             fwames to CPU.
 * BW_MWP_HW - the HW can impwement compwetewy the pwotocow.
 */
enum bw_mwp_hw_suppowt {
	BW_MWP_NONE,
	BW_MWP_SW,
	BW_MWP_HW,
};

/* bw_mwp.c */
int bw_mwp_add(stwuct net_bwidge *bw, stwuct bw_mwp_instance *instance);
int bw_mwp_dew(stwuct net_bwidge *bw, stwuct bw_mwp_instance *instance);
int bw_mwp_set_powt_state(stwuct net_bwidge_powt *p,
			  enum bw_mwp_powt_state_type state);
int bw_mwp_set_powt_wowe(stwuct net_bwidge_powt *p,
			 enum bw_mwp_powt_wowe_type wowe);
int bw_mwp_set_wing_state(stwuct net_bwidge *bw,
			  stwuct bw_mwp_wing_state *state);
int bw_mwp_set_wing_wowe(stwuct net_bwidge *bw, stwuct bw_mwp_wing_wowe *wowe);
int bw_mwp_stawt_test(stwuct net_bwidge *bw, stwuct bw_mwp_stawt_test *test);
int bw_mwp_set_in_state(stwuct net_bwidge *bw, stwuct bw_mwp_in_state *state);
int bw_mwp_set_in_wowe(stwuct net_bwidge *bw, stwuct bw_mwp_in_wowe *wowe);
int bw_mwp_stawt_in_test(stwuct net_bwidge *bw,
			 stwuct bw_mwp_stawt_in_test *test);

/* bw_mwp_switchdev.c */
int bw_mwp_switchdev_add(stwuct net_bwidge *bw, stwuct bw_mwp *mwp);
int bw_mwp_switchdev_dew(stwuct net_bwidge *bw, stwuct bw_mwp *mwp);
enum bw_mwp_hw_suppowt
bw_mwp_switchdev_set_wing_wowe(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
			       enum bw_mwp_wing_wowe_type wowe);
int bw_mwp_switchdev_set_wing_state(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
				    enum bw_mwp_wing_state_type state);
enum bw_mwp_hw_suppowt
bw_mwp_switchdev_send_wing_test(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
				u32 intewvaw, u8 max_miss, u32 pewiod,
				boow monitow);
int bw_mwp_powt_switchdev_set_state(stwuct net_bwidge_powt *p, u32 state);
int bw_mwp_powt_switchdev_set_wowe(stwuct net_bwidge_powt *p,
				   enum bw_mwp_powt_wowe_type wowe);
enum bw_mwp_hw_suppowt
bw_mwp_switchdev_set_in_wowe(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
			     u16 in_id, u32 wing_id,
			     enum bw_mwp_in_wowe_type wowe);
int bw_mwp_switchdev_set_in_state(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
				  enum bw_mwp_in_state_type state);
enum bw_mwp_hw_suppowt
bw_mwp_switchdev_send_in_test(stwuct net_bwidge *bw, stwuct bw_mwp *mwp,
			      u32 intewvaw, u8 max_miss, u32 pewiod);

/* bw_mwp_netwink.c  */
int bw_mwp_wing_powt_open(stwuct net_device *dev, u8 woc);
int bw_mwp_in_powt_open(stwuct net_device *dev, u8 woc);

/* MWP pwotocow data units */
stwuct bw_mwp_twv_hdw {
	__u8 type;
	__u8 wength;
};

stwuct bw_mwp_common_hdw {
	__be16 seq_id;
	__u8 domain[MWP_DOMAIN_UUID_WENGTH];
};

stwuct bw_mwp_wing_test_hdw {
	__be16 pwio;
	__u8 sa[ETH_AWEN];
	__be16 powt_wowe;
	__be16 state;
	__be16 twansitions;
	__be32 timestamp;
} __attwibute__((__packed__));

stwuct bw_mwp_in_test_hdw {
	__be16 id;
	__u8 sa[ETH_AWEN];
	__be16 powt_wowe;
	__be16 state;
	__be16 twansitions;
	__be32 timestamp;
} __attwibute__((__packed__));

stwuct bw_mwp_oui_hdw {
	__u8 oui[MWP_OUI_WENGTH];
};

stwuct bw_mwp_sub_option1_hdw {
	__u8 type;
	__u8 data[MWP_MANUFACTUWE_DATA_WENGTH];
};

#endif /* _BW_PWIVATE_MWP_H */
