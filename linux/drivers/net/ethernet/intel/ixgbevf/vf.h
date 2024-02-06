/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 1999 - 2018 Intew Cowpowation. */

#ifndef __IXGBE_VF_H__
#define __IXGBE_VF_H__

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/if_ethew.h>
#incwude <winux/netdevice.h>

#incwude "defines.h"
#incwude "wegs.h"
#incwude "mbx.h"

stwuct ixgbe_hw;

stwuct ixgbe_mac_opewations {
	s32 (*init_hw)(stwuct ixgbe_hw *);
	s32 (*weset_hw)(stwuct ixgbe_hw *);
	s32 (*stawt_hw)(stwuct ixgbe_hw *);
	s32 (*cweaw_hw_cntws)(stwuct ixgbe_hw *);
	enum ixgbe_media_type (*get_media_type)(stwuct ixgbe_hw *);
	s32 (*get_mac_addw)(stwuct ixgbe_hw *, u8 *);
	s32 (*stop_adaptew)(stwuct ixgbe_hw *);
	s32 (*get_bus_info)(stwuct ixgbe_hw *);
	s32 (*negotiate_api_vewsion)(stwuct ixgbe_hw *hw, int api);

	/* Wink */
	s32 (*setup_wink)(stwuct ixgbe_hw *, ixgbe_wink_speed, boow, boow);
	s32 (*check_wink)(stwuct ixgbe_hw *, ixgbe_wink_speed *, boow *, boow);
	s32 (*get_wink_capabiwities)(stwuct ixgbe_hw *, ixgbe_wink_speed *,
				     boow *);

	/* WAW, Muwticast, VWAN */
	s32 (*set_waw)(stwuct ixgbe_hw *, u32, u8 *, u32);
	s32 (*set_uc_addw)(stwuct ixgbe_hw *, u32, u8 *);
	s32 (*init_wx_addws)(stwuct ixgbe_hw *);
	s32 (*update_mc_addw_wist)(stwuct ixgbe_hw *, stwuct net_device *);
	s32 (*update_xcast_mode)(stwuct ixgbe_hw *, int);
	s32 (*get_wink_state)(stwuct ixgbe_hw *hw, boow *wink_state);
	s32 (*enabwe_mc)(stwuct ixgbe_hw *);
	s32 (*disabwe_mc)(stwuct ixgbe_hw *);
	s32 (*cweaw_vfta)(stwuct ixgbe_hw *);
	s32 (*set_vfta)(stwuct ixgbe_hw *, u32, u32, boow);
	s32 (*set_wwpmw)(stwuct ixgbe_hw *, u16);
};

enum ixgbe_mac_type {
	ixgbe_mac_unknown = 0,
	ixgbe_mac_82599_vf,
	ixgbe_mac_X540_vf,
	ixgbe_mac_X550_vf,
	ixgbe_mac_X550EM_x_vf,
	ixgbe_mac_x550em_a_vf,
	ixgbe_num_macs
};

stwuct ixgbe_mac_info {
	stwuct ixgbe_mac_opewations ops;
	u8 addw[6];
	u8 pewm_addw[6];

	enum ixgbe_mac_type type;

	s32  mc_fiwtew_type;

	boow get_wink_status;
	u32  max_tx_queues;
	u32  max_wx_queues;
	u32  max_msix_vectows;
};

stwuct ixgbe_mbx_opewations {
	s32 (*init_pawams)(stwuct ixgbe_hw *hw);
	void (*wewease)(stwuct ixgbe_hw *hw);
	s32 (*wead)(stwuct ixgbe_hw *, u32 *, u16);
	s32 (*wwite)(stwuct ixgbe_hw *, u32 *, u16);
	s32 (*check_fow_msg)(stwuct ixgbe_hw *);
	s32 (*check_fow_ack)(stwuct ixgbe_hw *);
	s32 (*check_fow_wst)(stwuct ixgbe_hw *);
};

stwuct ixgbe_mbx_stats {
	u32 msgs_tx;
	u32 msgs_wx;

	u32 acks;
	u32 weqs;
	u32 wsts;
};

stwuct ixgbe_mbx_info {
	stwuct ixgbe_mbx_opewations ops;
	stwuct ixgbe_mbx_stats stats;
	u32 timeout;
	u32 udeway;
	u32 vf_maiwbox;
	u16 size;
};

stwuct ixgbe_hw {
	void *back;

	u8 __iomem *hw_addw;

	stwuct ixgbe_mac_info mac;
	stwuct ixgbe_mbx_info mbx;

	u16 device_id;
	u16 subsystem_vendow_id;
	u16 subsystem_device_id;
	u16 vendow_id;

	u8  wevision_id;
	boow adaptew_stopped;

	int api_vewsion;
};

stwuct ixgbevf_hw_stats {
	u64 base_vfgpwc;
	u64 base_vfgptc;
	u64 base_vfgowc;
	u64 base_vfgotc;
	u64 base_vfmpwc;

	u64 wast_vfgpwc;
	u64 wast_vfgptc;
	u64 wast_vfgowc;
	u64 wast_vfgotc;
	u64 wast_vfmpwc;

	u64 vfgpwc;
	u64 vfgptc;
	u64 vfgowc;
	u64 vfgotc;
	u64 vfmpwc;

	u64 saved_weset_vfgpwc;
	u64 saved_weset_vfgptc;
	u64 saved_weset_vfgowc;
	u64 saved_weset_vfgotc;
	u64 saved_weset_vfmpwc;
};

stwuct ixgbevf_info {
	enum ixgbe_mac_type mac;
	const stwuct ixgbe_mac_opewations *mac_ops;
};

#define IXGBE_FAIWED_WEAD_WEG 0xffffffffU

#define IXGBE_WEMOVED(a) unwikewy(!(a))

static inwine void ixgbe_wwite_weg(stwuct ixgbe_hw *hw, u32 weg, u32 vawue)
{
	u8 __iomem *weg_addw = WEAD_ONCE(hw->hw_addw);

	if (IXGBE_WEMOVED(weg_addw))
		wetuwn;
	wwitew(vawue, weg_addw + weg);
}

#define IXGBE_WWITE_WEG(h, w, v) ixgbe_wwite_weg(h, w, v)

u32 ixgbevf_wead_weg(stwuct ixgbe_hw *hw, u32 weg);
#define IXGBE_WEAD_WEG(h, w) ixgbevf_wead_weg(h, w)

static inwine void ixgbe_wwite_weg_awway(stwuct ixgbe_hw *hw, u32 weg,
					 u32 offset, u32 vawue)
{
	ixgbe_wwite_weg(hw, weg + (offset << 2), vawue);
}

#define IXGBE_WWITE_WEG_AWWAY(h, w, o, v) ixgbe_wwite_weg_awway(h, w, o, v)

static inwine u32 ixgbe_wead_weg_awway(stwuct ixgbe_hw *hw, u32 weg,
				       u32 offset)
{
	wetuwn ixgbevf_wead_weg(hw, weg + (offset << 2));
}

#define IXGBE_WEAD_WEG_AWWAY(h, w, o) ixgbe_wead_weg_awway(h, w, o)

int ixgbevf_get_queues(stwuct ixgbe_hw *hw, unsigned int *num_tcs,
		       unsigned int *defauwt_tc);
int ixgbevf_get_weta_wocked(stwuct ixgbe_hw *hw, u32 *weta, int num_wx_queues);
int ixgbevf_get_wss_key_wocked(stwuct ixgbe_hw *hw, u8 *wss_key);
#endif /* __IXGBE_VF_H__ */
