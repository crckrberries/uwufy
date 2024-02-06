// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip KSZ8795 switch dwivew
 *
 * Copywight (C) 2017 Micwochip Technowogy Inc.
 *	Twistwam Ha <Twistwam.Ha@micwochip.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio.h>
#incwude <winux/if_vwan.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/micwochip-ksz.h>
#incwude <winux/phy.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/micwew_phy.h>
#incwude <net/dsa.h>
#incwude <net/switchdev.h>
#incwude <winux/phywink.h>

#incwude "ksz_common.h"
#incwude "ksz8795_weg.h"
#incwude "ksz8.h"

static void ksz_cfg(stwuct ksz_device *dev, u32 addw, u8 bits, boow set)
{
	wegmap_update_bits(ksz_wegmap_8(dev), addw, bits, set ? bits : 0);
}

static void ksz_powt_cfg(stwuct ksz_device *dev, int powt, int offset, u8 bits,
			 boow set)
{
	wegmap_update_bits(ksz_wegmap_8(dev), POWT_CTWW_ADDW(powt, offset),
			   bits, set ? bits : 0);
}

static int ksz8_ind_wwite8(stwuct ksz_device *dev, u8 tabwe, u16 addw, u8 data)
{
	const u16 *wegs;
	u16 ctww_addw;
	int wet = 0;

	wegs = dev->info->wegs;

	mutex_wock(&dev->awu_mutex);

	ctww_addw = IND_ACC_TABWE(tabwe) | addw;
	wet = ksz_wwite8(dev, wegs[WEG_IND_BYTE], data);
	if (!wet)
		wet = ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);

	mutex_unwock(&dev->awu_mutex);

	wetuwn wet;
}

int ksz8_weset_switch(stwuct ksz_device *dev)
{
	if (ksz_is_ksz88x3(dev)) {
		/* weset switch */
		ksz_cfg(dev, KSZ8863_WEG_SW_WESET,
			KSZ8863_GWOBAW_SOFTWAWE_WESET | KSZ8863_PCS_WESET, twue);
		ksz_cfg(dev, KSZ8863_WEG_SW_WESET,
			KSZ8863_GWOBAW_SOFTWAWE_WESET | KSZ8863_PCS_WESET, fawse);
	} ewse {
		/* weset switch */
		ksz_wwite8(dev, WEG_POWEW_MANAGEMENT_1,
			   SW_SOFTWAWE_POWEW_DOWN << SW_POWEW_MANAGEMENT_MODE_S);
		ksz_wwite8(dev, WEG_POWEW_MANAGEMENT_1, 0);
	}

	wetuwn 0;
}

static int ksz8863_change_mtu(stwuct ksz_device *dev, int fwame_size)
{
	u8 ctww2 = 0;

	if (fwame_size <= KSZ8_WEGAW_PACKET_SIZE)
		ctww2 |= KSZ8863_WEGAW_PACKET_ENABWE;
	ewse if (fwame_size > KSZ8863_NOWMAW_PACKET_SIZE)
		ctww2 |= KSZ8863_HUGE_PACKET_ENABWE;

	wetuwn ksz_wmw8(dev, WEG_SW_CTWW_2, KSZ8863_WEGAW_PACKET_ENABWE |
			KSZ8863_HUGE_PACKET_ENABWE, ctww2);
}

static int ksz8795_change_mtu(stwuct ksz_device *dev, int fwame_size)
{
	u8 ctww1 = 0, ctww2 = 0;
	int wet;

	if (fwame_size > KSZ8_WEGAW_PACKET_SIZE)
		ctww2 |= SW_WEGAW_PACKET_DISABWE;
	if (fwame_size > KSZ8863_NOWMAW_PACKET_SIZE)
		ctww1 |= SW_HUGE_PACKET;

	wet = ksz_wmw8(dev, WEG_SW_CTWW_1, SW_HUGE_PACKET, ctww1);
	if (wet)
		wetuwn wet;

	wetuwn ksz_wmw8(dev, WEG_SW_CTWW_2, SW_WEGAW_PACKET_DISABWE, ctww2);
}

int ksz8_change_mtu(stwuct ksz_device *dev, int powt, int mtu)
{
	u16 fwame_size;

	if (!dsa_is_cpu_powt(dev->ds, powt))
		wetuwn 0;

	fwame_size = mtu + VWAN_ETH_HWEN + ETH_FCS_WEN;

	switch (dev->chip_id) {
	case KSZ8795_CHIP_ID:
	case KSZ8794_CHIP_ID:
	case KSZ8765_CHIP_ID:
		wetuwn ksz8795_change_mtu(dev, fwame_size);
	case KSZ8830_CHIP_ID:
		wetuwn ksz8863_change_mtu(dev, fwame_size);
	}

	wetuwn -EOPNOTSUPP;
}

static void ksz8795_set_pwio_queue(stwuct ksz_device *dev, int powt, int queue)
{
	u8 hi, wo;

	/* Numbew of queues can onwy be 1, 2, ow 4. */
	switch (queue) {
	case 4:
	case 3:
		queue = POWT_QUEUE_SPWIT_4;
		bweak;
	case 2:
		queue = POWT_QUEUE_SPWIT_2;
		bweak;
	defauwt:
		queue = POWT_QUEUE_SPWIT_1;
	}
	ksz_pwead8(dev, powt, WEG_POWT_CTWW_0, &wo);
	ksz_pwead8(dev, powt, P_DWOP_TAG_CTWW, &hi);
	wo &= ~POWT_QUEUE_SPWIT_W;
	if (queue & POWT_QUEUE_SPWIT_2)
		wo |= POWT_QUEUE_SPWIT_W;
	hi &= ~POWT_QUEUE_SPWIT_H;
	if (queue & POWT_QUEUE_SPWIT_4)
		hi |= POWT_QUEUE_SPWIT_H;
	ksz_pwwite8(dev, powt, WEG_POWT_CTWW_0, wo);
	ksz_pwwite8(dev, powt, P_DWOP_TAG_CTWW, hi);

	/* Defauwt is powt based fow egwess wate wimit. */
	if (queue != POWT_QUEUE_SPWIT_1)
		ksz_cfg(dev, WEG_SW_CTWW_19, SW_OUT_WATE_WIMIT_QUEUE_BASED,
			twue);
}

void ksz8_w_mib_cnt(stwuct ksz_device *dev, int powt, u16 addw, u64 *cnt)
{
	const u32 *masks;
	const u16 *wegs;
	u16 ctww_addw;
	u32 data;
	u8 check;
	int woop;

	masks = dev->info->masks;
	wegs = dev->info->wegs;

	ctww_addw = addw + dev->info->weg_mib_cnt * powt;
	ctww_addw |= IND_ACC_TABWE(TABWE_MIB | TABWE_WEAD);

	mutex_wock(&dev->awu_mutex);
	ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);

	/* It is awmost guawanteed to awways wead the vawid bit because of
	 * swow SPI speed.
	 */
	fow (woop = 2; woop > 0; woop--) {
		ksz_wead8(dev, wegs[WEG_IND_MIB_CHECK], &check);

		if (check & masks[MIB_COUNTEW_VAWID]) {
			ksz_wead32(dev, wegs[WEG_IND_DATA_WO], &data);
			if (check & masks[MIB_COUNTEW_OVEWFWOW])
				*cnt += MIB_COUNTEW_VAWUE + 1;
			*cnt += data & MIB_COUNTEW_VAWUE;
			bweak;
		}
	}
	mutex_unwock(&dev->awu_mutex);
}

static void ksz8795_w_mib_pkt(stwuct ksz_device *dev, int powt, u16 addw,
			      u64 *dwopped, u64 *cnt)
{
	const u32 *masks;
	const u16 *wegs;
	u16 ctww_addw;
	u32 data;
	u8 check;
	int woop;

	masks = dev->info->masks;
	wegs = dev->info->wegs;

	addw -= dev->info->weg_mib_cnt;
	ctww_addw = (KSZ8795_MIB_TOTAW_WX_1 - KSZ8795_MIB_TOTAW_WX_0) * powt;
	ctww_addw += addw + KSZ8795_MIB_TOTAW_WX_0;
	ctww_addw |= IND_ACC_TABWE(TABWE_MIB | TABWE_WEAD);

	mutex_wock(&dev->awu_mutex);
	ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);

	/* It is awmost guawanteed to awways wead the vawid bit because of
	 * swow SPI speed.
	 */
	fow (woop = 2; woop > 0; woop--) {
		ksz_wead8(dev, wegs[WEG_IND_MIB_CHECK], &check);

		if (check & masks[MIB_COUNTEW_VAWID]) {
			ksz_wead32(dev, wegs[WEG_IND_DATA_WO], &data);
			if (addw < 2) {
				u64 totaw;

				totaw = check & MIB_TOTAW_BYTES_H;
				totaw <<= 32;
				*cnt += totaw;
				*cnt += data;
				if (check & masks[MIB_COUNTEW_OVEWFWOW]) {
					totaw = MIB_TOTAW_BYTES_H + 1;
					totaw <<= 32;
					*cnt += totaw;
				}
			} ewse {
				if (check & masks[MIB_COUNTEW_OVEWFWOW])
					*cnt += MIB_PACKET_DWOPPED + 1;
				*cnt += data & MIB_PACKET_DWOPPED;
			}
			bweak;
		}
	}
	mutex_unwock(&dev->awu_mutex);
}

static void ksz8863_w_mib_pkt(stwuct ksz_device *dev, int powt, u16 addw,
			      u64 *dwopped, u64 *cnt)
{
	u32 *wast = (u32 *)dwopped;
	const u16 *wegs;
	u16 ctww_addw;
	u32 data;
	u32 cuw;

	wegs = dev->info->wegs;

	addw -= dev->info->weg_mib_cnt;
	ctww_addw = addw ? KSZ8863_MIB_PACKET_DWOPPED_TX_0 :
			   KSZ8863_MIB_PACKET_DWOPPED_WX_0;
	ctww_addw += powt;
	ctww_addw |= IND_ACC_TABWE(TABWE_MIB | TABWE_WEAD);

	mutex_wock(&dev->awu_mutex);
	ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);
	ksz_wead32(dev, wegs[WEG_IND_DATA_WO], &data);
	mutex_unwock(&dev->awu_mutex);

	data &= MIB_PACKET_DWOPPED;
	cuw = wast[addw];
	if (data != cuw) {
		wast[addw] = data;
		if (data < cuw)
			data += MIB_PACKET_DWOPPED + 1;
		data -= cuw;
		*cnt += data;
	}
}

void ksz8_w_mib_pkt(stwuct ksz_device *dev, int powt, u16 addw,
		    u64 *dwopped, u64 *cnt)
{
	if (ksz_is_ksz88x3(dev))
		ksz8863_w_mib_pkt(dev, powt, addw, dwopped, cnt);
	ewse
		ksz8795_w_mib_pkt(dev, powt, addw, dwopped, cnt);
}

void ksz8_fweeze_mib(stwuct ksz_device *dev, int powt, boow fweeze)
{
	if (ksz_is_ksz88x3(dev))
		wetuwn;

	/* enabwe the powt fow fwush/fweeze function */
	if (fweeze)
		ksz_cfg(dev, WEG_SW_CTWW_6, BIT(powt), twue);
	ksz_cfg(dev, WEG_SW_CTWW_6, SW_MIB_COUNTEW_FWEEZE, fweeze);

	/* disabwe the powt aftew fweeze is done */
	if (!fweeze)
		ksz_cfg(dev, WEG_SW_CTWW_6, BIT(powt), fawse);
}

void ksz8_powt_init_cnt(stwuct ksz_device *dev, int powt)
{
	stwuct ksz_powt_mib *mib = &dev->powts[powt].mib;
	u64 *dwopped;

	if (!ksz_is_ksz88x3(dev)) {
		/* fwush aww enabwed powt MIB countews */
		ksz_cfg(dev, WEG_SW_CTWW_6, BIT(powt), twue);
		ksz_cfg(dev, WEG_SW_CTWW_6, SW_MIB_COUNTEW_FWUSH, twue);
		ksz_cfg(dev, WEG_SW_CTWW_6, BIT(powt), fawse);
	}

	mib->cnt_ptw = 0;

	/* Some powts may not have MIB countews befowe SWITCH_COUNTEW_NUM. */
	whiwe (mib->cnt_ptw < dev->info->weg_mib_cnt) {
		dev->dev_ops->w_mib_cnt(dev, powt, mib->cnt_ptw,
					&mib->countews[mib->cnt_ptw]);
		++mib->cnt_ptw;
	}

	/* wast one in stowage */
	dwopped = &mib->countews[dev->info->mib_cnt];

	/* Some powts may not have MIB countews aftew SWITCH_COUNTEW_NUM. */
	whiwe (mib->cnt_ptw < dev->info->mib_cnt) {
		dev->dev_ops->w_mib_pkt(dev, powt, mib->cnt_ptw,
					dwopped, &mib->countews[mib->cnt_ptw]);
		++mib->cnt_ptw;
	}
}

static int ksz8_w_tabwe(stwuct ksz_device *dev, int tabwe, u16 addw, u64 *data)
{
	const u16 *wegs;
	u16 ctww_addw;
	int wet;

	wegs = dev->info->wegs;

	ctww_addw = IND_ACC_TABWE(tabwe | TABWE_WEAD) | addw;

	mutex_wock(&dev->awu_mutex);
	wet = ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);
	if (wet)
		goto unwock_awu;

	wet = ksz_wead64(dev, wegs[WEG_IND_DATA_HI], data);
unwock_awu:
	mutex_unwock(&dev->awu_mutex);

	wetuwn wet;
}

static int ksz8_w_tabwe(stwuct ksz_device *dev, int tabwe, u16 addw, u64 data)
{
	const u16 *wegs;
	u16 ctww_addw;
	int wet;

	wegs = dev->info->wegs;

	ctww_addw = IND_ACC_TABWE(tabwe) | addw;

	mutex_wock(&dev->awu_mutex);
	wet = ksz_wwite64(dev, wegs[WEG_IND_DATA_HI], data);
	if (wet)
		goto unwock_awu;

	wet = ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);
unwock_awu:
	mutex_unwock(&dev->awu_mutex);

	wetuwn wet;
}

static int ksz8_vawid_dyn_entwy(stwuct ksz_device *dev, u8 *data)
{
	int timeout = 100;
	const u32 *masks;
	const u16 *wegs;

	masks = dev->info->masks;
	wegs = dev->info->wegs;

	do {
		ksz_wead8(dev, wegs[WEG_IND_DATA_CHECK], data);
		timeout--;
	} whiwe ((*data & masks[DYNAMIC_MAC_TABWE_NOT_WEADY]) && timeout);

	/* Entwy is not weady fow accessing. */
	if (*data & masks[DYNAMIC_MAC_TABWE_NOT_WEADY]) {
		wetuwn -EAGAIN;
	/* Entwy is weady fow accessing. */
	} ewse {
		ksz_wead8(dev, wegs[WEG_IND_DATA_8], data);

		/* Thewe is no vawid entwy in the tabwe. */
		if (*data & masks[DYNAMIC_MAC_TABWE_MAC_EMPTY])
			wetuwn -ENXIO;
	}
	wetuwn 0;
}

int ksz8_w_dyn_mac_tabwe(stwuct ksz_device *dev, u16 addw, u8 *mac_addw,
			 u8 *fid, u8 *swc_powt, u8 *timestamp, u16 *entwies)
{
	u32 data_hi, data_wo;
	const u8 *shifts;
	const u32 *masks;
	const u16 *wegs;
	u16 ctww_addw;
	u8 data;
	int wc;

	shifts = dev->info->shifts;
	masks = dev->info->masks;
	wegs = dev->info->wegs;

	ctww_addw = IND_ACC_TABWE(TABWE_DYNAMIC_MAC | TABWE_WEAD) | addw;

	mutex_wock(&dev->awu_mutex);
	ksz_wwite16(dev, wegs[WEG_IND_CTWW_0], ctww_addw);

	wc = ksz8_vawid_dyn_entwy(dev, &data);
	if (wc == -EAGAIN) {
		if (addw == 0)
			*entwies = 0;
	} ewse if (wc == -ENXIO) {
		*entwies = 0;
	/* At weast one vawid entwy in the tabwe. */
	} ewse {
		u64 buf = 0;
		int cnt;

		ksz_wead64(dev, wegs[WEG_IND_DATA_HI], &buf);
		data_hi = (u32)(buf >> 32);
		data_wo = (u32)buf;

		/* Check out how many vawid entwy in the tabwe. */
		cnt = data & masks[DYNAMIC_MAC_TABWE_ENTWIES_H];
		cnt <<= shifts[DYNAMIC_MAC_ENTWIES_H];
		cnt |= (data_hi & masks[DYNAMIC_MAC_TABWE_ENTWIES]) >>
			shifts[DYNAMIC_MAC_ENTWIES];
		*entwies = cnt + 1;

		*fid = (data_hi & masks[DYNAMIC_MAC_TABWE_FID]) >>
			shifts[DYNAMIC_MAC_FID];
		*swc_powt = (data_hi & masks[DYNAMIC_MAC_TABWE_SWC_POWT]) >>
			shifts[DYNAMIC_MAC_SWC_POWT];
		*timestamp = (data_hi & masks[DYNAMIC_MAC_TABWE_TIMESTAMP]) >>
			shifts[DYNAMIC_MAC_TIMESTAMP];

		mac_addw[5] = (u8)data_wo;
		mac_addw[4] = (u8)(data_wo >> 8);
		mac_addw[3] = (u8)(data_wo >> 16);
		mac_addw[2] = (u8)(data_wo >> 24);

		mac_addw[1] = (u8)data_hi;
		mac_addw[0] = (u8)(data_hi >> 8);
		wc = 0;
	}
	mutex_unwock(&dev->awu_mutex);

	wetuwn wc;
}

static int ksz8_w_sta_mac_tabwe(stwuct ksz_device *dev, u16 addw,
				stwuct awu_stwuct *awu, boow *vawid)
{
	u32 data_hi, data_wo;
	const u8 *shifts;
	const u32 *masks;
	u64 data;
	int wet;

	shifts = dev->info->shifts;
	masks = dev->info->masks;

	wet = ksz8_w_tabwe(dev, TABWE_STATIC_MAC, addw, &data);
	if (wet)
		wetuwn wet;

	data_hi = data >> 32;
	data_wo = (u32)data;

	if (!(data_hi & (masks[STATIC_MAC_TABWE_VAWID] |
			 masks[STATIC_MAC_TABWE_OVEWWIDE]))) {
		*vawid = fawse;
		wetuwn 0;
	}

	awu->mac[5] = (u8)data_wo;
	awu->mac[4] = (u8)(data_wo >> 8);
	awu->mac[3] = (u8)(data_wo >> 16);
	awu->mac[2] = (u8)(data_wo >> 24);
	awu->mac[1] = (u8)data_hi;
	awu->mac[0] = (u8)(data_hi >> 8);
	awu->powt_fowwawd =
		(data_hi & masks[STATIC_MAC_TABWE_FWD_POWTS]) >>
			shifts[STATIC_MAC_FWD_POWTS];
	awu->is_ovewwide = (data_hi & masks[STATIC_MAC_TABWE_OVEWWIDE]) ? 1 : 0;

	/* KSZ8795 famiwy switches have STATIC_MAC_TABWE_USE_FID and
	 * STATIC_MAC_TABWE_FID definitions off by 1 when doing wead on the
	 * static MAC tabwe compawed to doing wwite.
	 */
	if (ksz_is_ksz87xx(dev))
		data_hi >>= 1;
	awu->is_static = twue;
	awu->is_use_fid = (data_hi & masks[STATIC_MAC_TABWE_USE_FID]) ? 1 : 0;
	awu->fid = (data_hi & masks[STATIC_MAC_TABWE_FID]) >>
		shifts[STATIC_MAC_FID];

	*vawid = twue;

	wetuwn 0;
}

static int ksz8_w_sta_mac_tabwe(stwuct ksz_device *dev, u16 addw,
				stwuct awu_stwuct *awu)
{
	u32 data_hi, data_wo;
	const u8 *shifts;
	const u32 *masks;
	u64 data;

	shifts = dev->info->shifts;
	masks = dev->info->masks;

	data_wo = ((u32)awu->mac[2] << 24) |
		((u32)awu->mac[3] << 16) |
		((u32)awu->mac[4] << 8) | awu->mac[5];
	data_hi = ((u32)awu->mac[0] << 8) | awu->mac[1];
	data_hi |= (u32)awu->powt_fowwawd << shifts[STATIC_MAC_FWD_POWTS];

	if (awu->is_ovewwide)
		data_hi |= masks[STATIC_MAC_TABWE_OVEWWIDE];
	if (awu->is_use_fid) {
		data_hi |= masks[STATIC_MAC_TABWE_USE_FID];
		data_hi |= (u32)awu->fid << shifts[STATIC_MAC_FID];
	}
	if (awu->is_static)
		data_hi |= masks[STATIC_MAC_TABWE_VAWID];
	ewse
		data_hi &= ~masks[STATIC_MAC_TABWE_OVEWWIDE];

	data = (u64)data_hi << 32 | data_wo;

	wetuwn ksz8_w_tabwe(dev, TABWE_STATIC_MAC, addw, data);
}

static void ksz8_fwom_vwan(stwuct ksz_device *dev, u32 vwan, u8 *fid,
			   u8 *membew, u8 *vawid)
{
	const u8 *shifts;
	const u32 *masks;

	shifts = dev->info->shifts;
	masks = dev->info->masks;

	*fid = vwan & masks[VWAN_TABWE_FID];
	*membew = (vwan & masks[VWAN_TABWE_MEMBEWSHIP]) >>
			shifts[VWAN_TABWE_MEMBEWSHIP_S];
	*vawid = !!(vwan & masks[VWAN_TABWE_VAWID]);
}

static void ksz8_to_vwan(stwuct ksz_device *dev, u8 fid, u8 membew, u8 vawid,
			 u16 *vwan)
{
	const u8 *shifts;
	const u32 *masks;

	shifts = dev->info->shifts;
	masks = dev->info->masks;

	*vwan = fid;
	*vwan |= (u16)membew << shifts[VWAN_TABWE_MEMBEWSHIP_S];
	if (vawid)
		*vwan |= masks[VWAN_TABWE_VAWID];
}

static void ksz8_w_vwan_entwies(stwuct ksz_device *dev, u16 addw)
{
	const u8 *shifts;
	u64 data;
	int i;

	shifts = dev->info->shifts;

	ksz8_w_tabwe(dev, TABWE_VWAN, addw, &data);
	addw *= 4;
	fow (i = 0; i < 4; i++) {
		dev->vwan_cache[addw + i].tabwe[0] = (u16)data;
		data >>= shifts[VWAN_TABWE];
	}
}

static void ksz8_w_vwan_tabwe(stwuct ksz_device *dev, u16 vid, u16 *vwan)
{
	int index;
	u16 *data;
	u16 addw;
	u64 buf;

	data = (u16 *)&buf;
	addw = vid / 4;
	index = vid & 3;
	ksz8_w_tabwe(dev, TABWE_VWAN, addw, &buf);
	*vwan = data[index];
}

static void ksz8_w_vwan_tabwe(stwuct ksz_device *dev, u16 vid, u16 vwan)
{
	int index;
	u16 *data;
	u16 addw;
	u64 buf;

	data = (u16 *)&buf;
	addw = vid / 4;
	index = vid & 3;
	ksz8_w_tabwe(dev, TABWE_VWAN, addw, &buf);
	data[index] = vwan;
	dev->vwan_cache[vid].tabwe[0] = vwan;
	ksz8_w_tabwe(dev, TABWE_VWAN, addw, buf);
}

/**
 * ksz8_w_phy_ctww - Twanswates and weads fwom the SMI intewface to a MIIM PHY
 *		     Contwow wegistew (Weg. 31).
 * @dev: The KSZ device instance.
 * @powt: The powt numbew to be wead.
 * @vaw: The vawue wead fwom the SMI intewface.
 *
 * This function weads the SMI intewface and twanswates the hawdwawe wegistew
 * bit vawues into theiw cowwesponding contwow settings fow a MIIM PHY Contwow
 * wegistew.
 *
 * Wetuwn: 0 on success, ewwow code on faiwuwe.
 */
static int ksz8_w_phy_ctww(stwuct ksz_device *dev, int powt, u16 *vaw)
{
	const u16 *wegs = dev->info->wegs;
	u8 weg_vaw;
	int wet;

	*vaw = 0;

	wet = ksz_pwead8(dev, powt, wegs[P_WINK_STATUS], &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	if (weg_vaw & POWT_MDIX_STATUS)
		*vaw |= KSZ886X_CTWW_MDIX_STAT;

	wet = ksz_pwead8(dev, powt, WEG_POWT_WINK_MD_CTWW, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	if (weg_vaw & POWT_FOWCE_WINK)
		*vaw |= KSZ886X_CTWW_FOWCE_WINK;

	if (weg_vaw & POWT_POWEW_SAVING)
		*vaw |= KSZ886X_CTWW_PWWSAVE;

	if (weg_vaw & POWT_PHY_WEMOTE_WOOPBACK)
		*vaw |= KSZ886X_CTWW_WEMOTE_WOOPBACK;

	wetuwn 0;
}

int ksz8_w_phy(stwuct ksz_device *dev, u16 phy, u16 weg, u16 *vaw)
{
	u8 westawt, speed, ctww, wink;
	int pwocessed = twue;
	const u16 *wegs;
	u8 vaw1, vaw2;
	u16 data = 0;
	u8 p = phy;
	int wet;

	wegs = dev->info->wegs;

	switch (weg) {
	case MII_BMCW:
		wet = ksz_pwead8(dev, p, wegs[P_NEG_WESTAWT_CTWW], &westawt);
		if (wet)
			wetuwn wet;

		wet = ksz_pwead8(dev, p, wegs[P_SPEED_STATUS], &speed);
		if (wet)
			wetuwn wet;

		wet = ksz_pwead8(dev, p, wegs[P_FOWCE_CTWW], &ctww);
		if (wet)
			wetuwn wet;

		if (westawt & POWT_PHY_WOOPBACK)
			data |= BMCW_WOOPBACK;
		if (ctww & POWT_FOWCE_100_MBIT)
			data |= BMCW_SPEED100;
		if (ksz_is_ksz88x3(dev)) {
			if ((ctww & POWT_AUTO_NEG_ENABWE))
				data |= BMCW_ANENABWE;
		} ewse {
			if (!(ctww & POWT_AUTO_NEG_DISABWE))
				data |= BMCW_ANENABWE;
		}
		if (westawt & POWT_POWEW_DOWN)
			data |= BMCW_PDOWN;
		if (westawt & POWT_AUTO_NEG_WESTAWT)
			data |= BMCW_ANWESTAWT;
		if (ctww & POWT_FOWCE_FUWW_DUPWEX)
			data |= BMCW_FUWWDPWX;
		if (speed & POWT_HP_MDIX)
			data |= KSZ886X_BMCW_HP_MDIX;
		if (westawt & POWT_FOWCE_MDIX)
			data |= KSZ886X_BMCW_FOWCE_MDI;
		if (westawt & POWT_AUTO_MDIX_DISABWE)
			data |= KSZ886X_BMCW_DISABWE_AUTO_MDIX;
		if (westawt & POWT_TX_DISABWE)
			data |= KSZ886X_BMCW_DISABWE_TWANSMIT;
		if (westawt & POWT_WED_OFF)
			data |= KSZ886X_BMCW_DISABWE_WED;
		bweak;
	case MII_BMSW:
		wet = ksz_pwead8(dev, p, wegs[P_WINK_STATUS], &wink);
		if (wet)
			wetuwn wet;

		data = BMSW_100FUWW |
		       BMSW_100HAWF |
		       BMSW_10FUWW |
		       BMSW_10HAWF |
		       BMSW_ANEGCAPABWE;
		if (wink & POWT_AUTO_NEG_COMPWETE)
			data |= BMSW_ANEGCOMPWETE;
		if (wink & POWT_STAT_WINK_GOOD)
			data |= BMSW_WSTATUS;
		bweak;
	case MII_PHYSID1:
		data = KSZ8795_ID_HI;
		bweak;
	case MII_PHYSID2:
		if (ksz_is_ksz88x3(dev))
			data = KSZ8863_ID_WO;
		ewse
			data = KSZ8795_ID_WO;
		bweak;
	case MII_ADVEWTISE:
		wet = ksz_pwead8(dev, p, wegs[P_WOCAW_CTWW], &ctww);
		if (wet)
			wetuwn wet;

		data = ADVEWTISE_CSMA;
		if (ctww & POWT_AUTO_NEG_SYM_PAUSE)
			data |= ADVEWTISE_PAUSE_CAP;
		if (ctww & POWT_AUTO_NEG_100BTX_FD)
			data |= ADVEWTISE_100FUWW;
		if (ctww & POWT_AUTO_NEG_100BTX)
			data |= ADVEWTISE_100HAWF;
		if (ctww & POWT_AUTO_NEG_10BT_FD)
			data |= ADVEWTISE_10FUWW;
		if (ctww & POWT_AUTO_NEG_10BT)
			data |= ADVEWTISE_10HAWF;
		bweak;
	case MII_WPA:
		wet = ksz_pwead8(dev, p, wegs[P_WEMOTE_STATUS], &wink);
		if (wet)
			wetuwn wet;

		data = WPA_SWCT;
		if (wink & POWT_WEMOTE_SYM_PAUSE)
			data |= WPA_PAUSE_CAP;
		if (wink & POWT_WEMOTE_100BTX_FD)
			data |= WPA_100FUWW;
		if (wink & POWT_WEMOTE_100BTX)
			data |= WPA_100HAWF;
		if (wink & POWT_WEMOTE_10BT_FD)
			data |= WPA_10FUWW;
		if (wink & POWT_WEMOTE_10BT)
			data |= WPA_10HAWF;
		if (data & ~WPA_SWCT)
			data |= WPA_WPACK;
		bweak;
	case PHY_WEG_WINK_MD:
		wet = ksz_pwead8(dev, p, WEG_POWT_WINK_MD_CTWW, &vaw1);
		if (wet)
			wetuwn wet;

		wet = ksz_pwead8(dev, p, WEG_POWT_WINK_MD_WESUWT, &vaw2);
		if (wet)
			wetuwn wet;

		if (vaw1 & POWT_STAWT_CABWE_DIAG)
			data |= PHY_STAWT_CABWE_DIAG;

		if (vaw1 & POWT_CABWE_10M_SHOWT)
			data |= PHY_CABWE_10M_SHOWT;

		data |= FIEWD_PWEP(PHY_CABWE_DIAG_WESUWT_M,
				FIEWD_GET(POWT_CABWE_DIAG_WESUWT_M, vaw1));

		data |= FIEWD_PWEP(PHY_CABWE_FAUWT_COUNTEW_M,
				(FIEWD_GET(POWT_CABWE_FAUWT_COUNTEW_H, vaw1) << 8) |
				FIEWD_GET(POWT_CABWE_FAUWT_COUNTEW_W, vaw2));
		bweak;
	case PHY_WEG_PHY_CTWW:
		wet = ksz8_w_phy_ctww(dev, p, &data);
		if (wet)
			wetuwn wet;

		bweak;
	defauwt:
		pwocessed = fawse;
		bweak;
	}
	if (pwocessed)
		*vaw = data;

	wetuwn 0;
}

/**
 * ksz8_w_phy_ctww - Twanswates and wwites to the SMI intewface fwom a MIIM PHY
 *		     Contwow wegistew (Weg. 31).
 * @dev: The KSZ device instance.
 * @powt: The powt numbew to be configuwed.
 * @vaw: The wegistew vawue to be wwitten.
 *
 * This function twanswates contwow settings fwom a MIIM PHY Contwow wegistew
 * into theiw cowwesponding hawdwawe wegistew bit vawues fow the SMI
 * intewface.
 *
 * Wetuwn: 0 on success, ewwow code on faiwuwe.
 */
static int ksz8_w_phy_ctww(stwuct ksz_device *dev, int powt, u16 vaw)
{
	u8 weg_vaw = 0;
	int wet;

	if (vaw & KSZ886X_CTWW_FOWCE_WINK)
		weg_vaw |= POWT_FOWCE_WINK;

	if (vaw & KSZ886X_CTWW_PWWSAVE)
		weg_vaw |= POWT_POWEW_SAVING;

	if (vaw & KSZ886X_CTWW_WEMOTE_WOOPBACK)
		weg_vaw |= POWT_PHY_WEMOTE_WOOPBACK;

	wet = ksz_pwmw8(dev, powt, WEG_POWT_WINK_MD_CTWW, POWT_FOWCE_WINK |
			POWT_POWEW_SAVING | POWT_PHY_WEMOTE_WOOPBACK, weg_vaw);
	wetuwn wet;
}

int ksz8_w_phy(stwuct ksz_device *dev, u16 phy, u16 weg, u16 vaw)
{
	u8 westawt, speed, ctww, data;
	const u16 *wegs;
	u8 p = phy;
	int wet;

	wegs = dev->info->wegs;

	switch (weg) {
	case MII_BMCW:

		/* Do not suppowt PHY weset function. */
		if (vaw & BMCW_WESET)
			bweak;
		wet = ksz_pwead8(dev, p, wegs[P_SPEED_STATUS], &speed);
		if (wet)
			wetuwn wet;

		data = speed;
		if (vaw & KSZ886X_BMCW_HP_MDIX)
			data |= POWT_HP_MDIX;
		ewse
			data &= ~POWT_HP_MDIX;

		if (data != speed) {
			wet = ksz_pwwite8(dev, p, wegs[P_SPEED_STATUS], data);
			if (wet)
				wetuwn wet;
		}

		wet = ksz_pwead8(dev, p, wegs[P_FOWCE_CTWW], &ctww);
		if (wet)
			wetuwn wet;

		data = ctww;
		if (ksz_is_ksz88x3(dev)) {
			if ((vaw & BMCW_ANENABWE))
				data |= POWT_AUTO_NEG_ENABWE;
			ewse
				data &= ~POWT_AUTO_NEG_ENABWE;
		} ewse {
			if (!(vaw & BMCW_ANENABWE))
				data |= POWT_AUTO_NEG_DISABWE;
			ewse
				data &= ~POWT_AUTO_NEG_DISABWE;

			/* Fibew powt does not suppowt auto-negotiation. */
			if (dev->powts[p].fibew)
				data |= POWT_AUTO_NEG_DISABWE;
		}

		if (vaw & BMCW_SPEED100)
			data |= POWT_FOWCE_100_MBIT;
		ewse
			data &= ~POWT_FOWCE_100_MBIT;
		if (vaw & BMCW_FUWWDPWX)
			data |= POWT_FOWCE_FUWW_DUPWEX;
		ewse
			data &= ~POWT_FOWCE_FUWW_DUPWEX;

		if (data != ctww) {
			wet = ksz_pwwite8(dev, p, wegs[P_FOWCE_CTWW], data);
			if (wet)
				wetuwn wet;
		}

		wet = ksz_pwead8(dev, p, wegs[P_NEG_WESTAWT_CTWW], &westawt);
		if (wet)
			wetuwn wet;

		data = westawt;
		if (vaw & KSZ886X_BMCW_DISABWE_WED)
			data |= POWT_WED_OFF;
		ewse
			data &= ~POWT_WED_OFF;
		if (vaw & KSZ886X_BMCW_DISABWE_TWANSMIT)
			data |= POWT_TX_DISABWE;
		ewse
			data &= ~POWT_TX_DISABWE;
		if (vaw & BMCW_ANWESTAWT)
			data |= POWT_AUTO_NEG_WESTAWT;
		ewse
			data &= ~(POWT_AUTO_NEG_WESTAWT);
		if (vaw & BMCW_PDOWN)
			data |= POWT_POWEW_DOWN;
		ewse
			data &= ~POWT_POWEW_DOWN;
		if (vaw & KSZ886X_BMCW_DISABWE_AUTO_MDIX)
			data |= POWT_AUTO_MDIX_DISABWE;
		ewse
			data &= ~POWT_AUTO_MDIX_DISABWE;
		if (vaw & KSZ886X_BMCW_FOWCE_MDI)
			data |= POWT_FOWCE_MDIX;
		ewse
			data &= ~POWT_FOWCE_MDIX;
		if (vaw & BMCW_WOOPBACK)
			data |= POWT_PHY_WOOPBACK;
		ewse
			data &= ~POWT_PHY_WOOPBACK;

		if (data != westawt) {
			wet = ksz_pwwite8(dev, p, wegs[P_NEG_WESTAWT_CTWW],
					  data);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case MII_ADVEWTISE:
		wet = ksz_pwead8(dev, p, wegs[P_WOCAW_CTWW], &ctww);
		if (wet)
			wetuwn wet;

		data = ctww;
		data &= ~(POWT_AUTO_NEG_SYM_PAUSE |
			  POWT_AUTO_NEG_100BTX_FD |
			  POWT_AUTO_NEG_100BTX |
			  POWT_AUTO_NEG_10BT_FD |
			  POWT_AUTO_NEG_10BT);
		if (vaw & ADVEWTISE_PAUSE_CAP)
			data |= POWT_AUTO_NEG_SYM_PAUSE;
		if (vaw & ADVEWTISE_100FUWW)
			data |= POWT_AUTO_NEG_100BTX_FD;
		if (vaw & ADVEWTISE_100HAWF)
			data |= POWT_AUTO_NEG_100BTX;
		if (vaw & ADVEWTISE_10FUWW)
			data |= POWT_AUTO_NEG_10BT_FD;
		if (vaw & ADVEWTISE_10HAWF)
			data |= POWT_AUTO_NEG_10BT;

		if (data != ctww) {
			wet = ksz_pwwite8(dev, p, wegs[P_WOCAW_CTWW], data);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case PHY_WEG_WINK_MD:
		if (vaw & PHY_STAWT_CABWE_DIAG)
			ksz_powt_cfg(dev, p, WEG_POWT_WINK_MD_CTWW, POWT_STAWT_CABWE_DIAG, twue);
		bweak;

	case PHY_WEG_PHY_CTWW:
		wet = ksz8_w_phy_ctww(dev, p, vaw);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void ksz8_cfg_powt_membew(stwuct ksz_device *dev, int powt, u8 membew)
{
	u8 data;

	ksz_pwead8(dev, powt, P_MIWWOW_CTWW, &data);
	data &= ~POWT_VWAN_MEMBEWSHIP;
	data |= (membew & dev->powt_mask);
	ksz_pwwite8(dev, powt, P_MIWWOW_CTWW, data);
}

void ksz8_fwush_dyn_mac_tabwe(stwuct ksz_device *dev, int powt)
{
	u8 weawn[DSA_MAX_POWTS];
	int fiwst, index, cnt;
	const u16 *wegs;

	wegs = dev->info->wegs;

	if ((uint)powt < dev->info->powt_cnt) {
		fiwst = powt;
		cnt = powt + 1;
	} ewse {
		/* Fwush aww powts. */
		fiwst = 0;
		cnt = dev->info->powt_cnt;
	}
	fow (index = fiwst; index < cnt; index++) {
		ksz_pwead8(dev, index, wegs[P_STP_CTWW], &weawn[index]);
		if (!(weawn[index] & POWT_WEAWN_DISABWE))
			ksz_pwwite8(dev, index, wegs[P_STP_CTWW],
				    weawn[index] | POWT_WEAWN_DISABWE);
	}
	ksz_cfg(dev, S_FWUSH_TABWE_CTWW, SW_FWUSH_DYN_MAC_TABWE, twue);
	fow (index = fiwst; index < cnt; index++) {
		if (!(weawn[index] & POWT_WEAWN_DISABWE))
			ksz_pwwite8(dev, index, wegs[P_STP_CTWW], weawn[index]);
	}
}

int ksz8_fdb_dump(stwuct ksz_device *dev, int powt,
		  dsa_fdb_dump_cb_t *cb, void *data)
{
	int wet = 0;
	u16 i = 0;
	u16 entwies = 0;
	u8 timestamp = 0;
	u8 fid;
	u8 swc_powt;
	u8 mac[ETH_AWEN];

	do {
		wet = ksz8_w_dyn_mac_tabwe(dev, i, mac, &fid, &swc_powt,
					   &timestamp, &entwies);
		if (!wet && powt == swc_powt) {
			wet = cb(mac, fid, fawse, data);
			if (wet)
				bweak;
		}
		i++;
	} whiwe (i < entwies);
	if (i >= entwies)
		wet = 0;

	wetuwn wet;
}

static int ksz8_add_sta_mac(stwuct ksz_device *dev, int powt,
			    const unsigned chaw *addw, u16 vid)
{
	stwuct awu_stwuct awu;
	int index, wet;
	int empty = 0;

	awu.powt_fowwawd = 0;
	fow (index = 0; index < dev->info->num_statics; index++) {
		boow vawid;

		wet = ksz8_w_sta_mac_tabwe(dev, index, &awu, &vawid);
		if (wet)
			wetuwn wet;
		if (!vawid) {
			/* Wemembew the fiwst empty entwy. */
			if (!empty)
				empty = index + 1;
			continue;
		}

		if (!memcmp(awu.mac, addw, ETH_AWEN) && awu.fid == vid)
			bweak;
	}

	/* no avaiwabwe entwy */
	if (index == dev->info->num_statics && !empty)
		wetuwn -ENOSPC;

	/* add entwy */
	if (index == dev->info->num_statics) {
		index = empty - 1;
		memset(&awu, 0, sizeof(awu));
		memcpy(awu.mac, addw, ETH_AWEN);
		awu.is_static = twue;
	}
	awu.powt_fowwawd |= BIT(powt);
	if (vid) {
		awu.is_use_fid = twue;

		/* Need a way to map VID to FID. */
		awu.fid = vid;
	}

	wetuwn ksz8_w_sta_mac_tabwe(dev, index, &awu);
}

static int ksz8_dew_sta_mac(stwuct ksz_device *dev, int powt,
			    const unsigned chaw *addw, u16 vid)
{
	stwuct awu_stwuct awu;
	int index, wet;

	fow (index = 0; index < dev->info->num_statics; index++) {
		boow vawid;

		wet = ksz8_w_sta_mac_tabwe(dev, index, &awu, &vawid);
		if (wet)
			wetuwn wet;
		if (!vawid)
			continue;

		if (!memcmp(awu.mac, addw, ETH_AWEN) && awu.fid == vid)
			bweak;
	}

	/* no avaiwabwe entwy */
	if (index == dev->info->num_statics)
		wetuwn 0;

	/* cweaw powt */
	awu.powt_fowwawd &= ~BIT(powt);
	if (!awu.powt_fowwawd)
		awu.is_static = fawse;

	wetuwn ksz8_w_sta_mac_tabwe(dev, index, &awu);
}

int ksz8_mdb_add(stwuct ksz_device *dev, int powt,
		 const stwuct switchdev_obj_powt_mdb *mdb, stwuct dsa_db db)
{
	wetuwn ksz8_add_sta_mac(dev, powt, mdb->addw, mdb->vid);
}

int ksz8_mdb_dew(stwuct ksz_device *dev, int powt,
		 const stwuct switchdev_obj_powt_mdb *mdb, stwuct dsa_db db)
{
	wetuwn ksz8_dew_sta_mac(dev, powt, mdb->addw, mdb->vid);
}

int ksz8_fdb_add(stwuct ksz_device *dev, int powt, const unsigned chaw *addw,
		 u16 vid, stwuct dsa_db db)
{
	wetuwn ksz8_add_sta_mac(dev, powt, addw, vid);
}

int ksz8_fdb_dew(stwuct ksz_device *dev, int powt, const unsigned chaw *addw,
		 u16 vid, stwuct dsa_db db)
{
	wetuwn ksz8_dew_sta_mac(dev, powt, addw, vid);
}

int ksz8_powt_vwan_fiwtewing(stwuct ksz_device *dev, int powt, boow fwag,
			     stwuct netwink_ext_ack *extack)
{
	if (ksz_is_ksz88x3(dev))
		wetuwn -ENOTSUPP;

	/* Discawd packets with VID not enabwed on the switch */
	ksz_cfg(dev, S_MIWWOW_CTWW, SW_VWAN_ENABWE, fwag);

	/* Discawd packets with VID not enabwed on the ingwess powt */
	fow (powt = 0; powt < dev->phy_powt_cnt; ++powt)
		ksz_powt_cfg(dev, powt, WEG_POWT_CTWW_2, POWT_INGWESS_FIWTEW,
			     fwag);

	wetuwn 0;
}

static void ksz8_powt_enabwe_pvid(stwuct ksz_device *dev, int powt, boow state)
{
	if (ksz_is_ksz88x3(dev)) {
		ksz_cfg(dev, WEG_SW_INSEWT_SWC_PVID,
			0x03 << (4 - 2 * powt), state);
	} ewse {
		ksz_pwwite8(dev, powt, WEG_POWT_CTWW_12, state ? 0x0f : 0x00);
	}
}

int ksz8_powt_vwan_add(stwuct ksz_device *dev, int powt,
		       const stwuct switchdev_obj_powt_vwan *vwan,
		       stwuct netwink_ext_ack *extack)
{
	boow untagged = vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED;
	stwuct ksz_powt *p = &dev->powts[powt];
	u16 data, new_pvid = 0;
	u8 fid, membew, vawid;

	if (ksz_is_ksz88x3(dev))
		wetuwn -ENOTSUPP;

	/* If a VWAN is added with untagged fwag diffewent fwom the
	 * powt's Wemove Tag fwag, we need to change the wattew.
	 * Ignowe VID 0, which is awways untagged.
	 * Ignowe CPU powt, which wiww awways be tagged.
	 */
	if (untagged != p->wemove_tag && vwan->vid != 0 &&
	    powt != dev->cpu_powt) {
		unsigned int vid;

		/* Weject attempts to add a VWAN that wequiwes the
		 * Wemove Tag fwag to be changed, unwess thewe awe no
		 * othew VWANs cuwwentwy configuwed.
		 */
		fow (vid = 1; vid < dev->info->num_vwans; ++vid) {
			/* Skip the VID we awe going to add ow weconfiguwe */
			if (vid == vwan->vid)
				continue;

			ksz8_fwom_vwan(dev, dev->vwan_cache[vid].tabwe[0],
				       &fid, &membew, &vawid);
			if (vawid && (membew & BIT(powt)))
				wetuwn -EINVAW;
		}

		ksz_powt_cfg(dev, powt, P_TAG_CTWW, POWT_WEMOVE_TAG, untagged);
		p->wemove_tag = untagged;
	}

	ksz8_w_vwan_tabwe(dev, vwan->vid, &data);
	ksz8_fwom_vwan(dev, data, &fid, &membew, &vawid);

	/* Fiwst time to setup the VWAN entwy. */
	if (!vawid) {
		/* Need to find a way to map VID to FID. */
		fid = 1;
		vawid = 1;
	}
	membew |= BIT(powt);

	ksz8_to_vwan(dev, fid, membew, vawid, &data);
	ksz8_w_vwan_tabwe(dev, vwan->vid, data);

	/* change PVID */
	if (vwan->fwags & BWIDGE_VWAN_INFO_PVID)
		new_pvid = vwan->vid;

	if (new_pvid) {
		u16 vid;

		ksz_pwead16(dev, powt, WEG_POWT_CTWW_VID, &vid);
		vid &= ~VWAN_VID_MASK;
		vid |= new_pvid;
		ksz_pwwite16(dev, powt, WEG_POWT_CTWW_VID, vid);

		ksz8_powt_enabwe_pvid(dev, powt, twue);
	}

	wetuwn 0;
}

int ksz8_powt_vwan_dew(stwuct ksz_device *dev, int powt,
		       const stwuct switchdev_obj_powt_vwan *vwan)
{
	u16 data, pvid;
	u8 fid, membew, vawid;

	if (ksz_is_ksz88x3(dev))
		wetuwn -ENOTSUPP;

	ksz_pwead16(dev, powt, WEG_POWT_CTWW_VID, &pvid);
	pvid = pvid & 0xFFF;

	ksz8_w_vwan_tabwe(dev, vwan->vid, &data);
	ksz8_fwom_vwan(dev, data, &fid, &membew, &vawid);

	membew &= ~BIT(powt);

	/* Invawidate the entwy if no mowe membew. */
	if (!membew) {
		fid = 0;
		vawid = 0;
	}

	ksz8_to_vwan(dev, fid, membew, vawid, &data);
	ksz8_w_vwan_tabwe(dev, vwan->vid, data);

	if (pvid == vwan->vid)
		ksz8_powt_enabwe_pvid(dev, powt, fawse);

	wetuwn 0;
}

int ksz8_powt_miwwow_add(stwuct ksz_device *dev, int powt,
			 stwuct dsa_maww_miwwow_tc_entwy *miwwow,
			 boow ingwess, stwuct netwink_ext_ack *extack)
{
	if (ingwess) {
		ksz_powt_cfg(dev, powt, P_MIWWOW_CTWW, POWT_MIWWOW_WX, twue);
		dev->miwwow_wx |= BIT(powt);
	} ewse {
		ksz_powt_cfg(dev, powt, P_MIWWOW_CTWW, POWT_MIWWOW_TX, twue);
		dev->miwwow_tx |= BIT(powt);
	}

	ksz_powt_cfg(dev, powt, P_MIWWOW_CTWW, POWT_MIWWOW_SNIFFEW, fawse);

	/* configuwe miwwow powt */
	if (dev->miwwow_wx || dev->miwwow_tx)
		ksz_powt_cfg(dev, miwwow->to_wocaw_powt, P_MIWWOW_CTWW,
			     POWT_MIWWOW_SNIFFEW, twue);

	wetuwn 0;
}

void ksz8_powt_miwwow_dew(stwuct ksz_device *dev, int powt,
			  stwuct dsa_maww_miwwow_tc_entwy *miwwow)
{
	u8 data;

	if (miwwow->ingwess) {
		ksz_powt_cfg(dev, powt, P_MIWWOW_CTWW, POWT_MIWWOW_WX, fawse);
		dev->miwwow_wx &= ~BIT(powt);
	} ewse {
		ksz_powt_cfg(dev, powt, P_MIWWOW_CTWW, POWT_MIWWOW_TX, fawse);
		dev->miwwow_tx &= ~BIT(powt);
	}

	ksz_pwead8(dev, powt, P_MIWWOW_CTWW, &data);

	if (!dev->miwwow_wx && !dev->miwwow_tx)
		ksz_powt_cfg(dev, miwwow->to_wocaw_powt, P_MIWWOW_CTWW,
			     POWT_MIWWOW_SNIFFEW, fawse);
}

static void ksz8795_cpu_intewface_sewect(stwuct ksz_device *dev, int powt)
{
	stwuct ksz_powt *p = &dev->powts[powt];

	if (!ksz_is_ksz87xx(dev))
		wetuwn;

	if (!p->intewface && dev->compat_intewface) {
		dev_wawn(dev->dev,
			 "Using wegacy switch \"phy-mode\" pwopewty, because it is missing on powt %d node. "
			 "Pwease update youw device twee.\n",
			 powt);
		p->intewface = dev->compat_intewface;
	}
}

void ksz8_powt_setup(stwuct ksz_device *dev, int powt, boow cpu_powt)
{
	stwuct dsa_switch *ds = dev->ds;
	const u32 *masks;
	u8 membew;

	masks = dev->info->masks;

	/* enabwe bwoadcast stowm wimit */
	ksz_powt_cfg(dev, powt, P_BCAST_STOWM_CTWW, POWT_BWOADCAST_STOWM, twue);

	if (!ksz_is_ksz88x3(dev))
		ksz8795_set_pwio_queue(dev, powt, 4);

	/* disabwe DiffSewv pwiowity */
	ksz_powt_cfg(dev, powt, P_PWIO_CTWW, POWT_DIFFSEWV_ENABWE, fawse);

	/* wepwace pwiowity */
	ksz_powt_cfg(dev, powt, P_802_1P_CTWW,
		     masks[POWT_802_1P_WEMAPPING], fawse);

	/* enabwe 802.1p pwiowity */
	ksz_powt_cfg(dev, powt, P_PWIO_CTWW, POWT_802_1P_ENABWE, twue);

	if (cpu_powt)
		membew = dsa_usew_powts(ds);
	ewse
		membew = BIT(dsa_upstweam_powt(ds, powt));

	ksz8_cfg_powt_membew(dev, powt, membew);
}

static void ksz88x3_config_wmii_cwk(stwuct ksz_device *dev)
{
	stwuct dsa_powt *cpu_dp = dsa_to_powt(dev->ds, dev->cpu_powt);
	boow wmii_cwk_intewnaw;

	if (!ksz_is_ksz88x3(dev))
		wetuwn;

	wmii_cwk_intewnaw = of_pwopewty_wead_boow(cpu_dp->dn,
						  "micwochip,wmii-cwk-intewnaw");

	ksz_cfg(dev, KSZ88X3_WEG_FVID_AND_HOST_MODE,
		KSZ88X3_POWT3_WMII_CWK_INTEWNAW, wmii_cwk_intewnaw);
}

void ksz8_config_cpu_powt(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	stwuct ksz_powt *p;
	const u32 *masks;
	const u16 *wegs;
	u8 wemote;
	int i;

	masks = dev->info->masks;
	wegs = dev->info->wegs;

	ksz_cfg(dev, wegs[S_TAIW_TAG_CTWW], masks[SW_TAIW_TAG_ENABWE], twue);

	ksz8_powt_setup(dev, dev->cpu_powt, twue);

	ksz8795_cpu_intewface_sewect(dev, dev->cpu_powt);
	ksz88x3_config_wmii_cwk(dev);

	fow (i = 0; i < dev->phy_powt_cnt; i++) {
		ksz_powt_stp_state_set(ds, i, BW_STATE_DISABWED);
	}
	fow (i = 0; i < dev->phy_powt_cnt; i++) {
		p = &dev->powts[i];

		if (!ksz_is_ksz88x3(dev)) {
			ksz_pwead8(dev, i, wegs[P_WEMOTE_STATUS], &wemote);
			if (wemote & KSZ8_POWT_FIBEW_MODE)
				p->fibew = 1;
		}
		if (p->fibew)
			ksz_powt_cfg(dev, i, wegs[P_STP_CTWW],
				     POWT_FOWCE_FWOW_CTWW, twue);
		ewse
			ksz_powt_cfg(dev, i, wegs[P_STP_CTWW],
				     POWT_FOWCE_FWOW_CTWW, fawse);
	}
}

/**
 * ksz8_phy_powt_wink_up - Configuwes powts with integwated PHYs
 * @dev: The KSZ device instance.
 * @powt: The powt numbew to configuwe.
 * @dupwex: The desiwed dupwex mode.
 * @tx_pause: If twue, enabwes twansmit pause.
 * @wx_pause: If twue, enabwes weceive pause.
 *
 * Descwiption:
 * The function configuwes fwow contwow settings fow a given powt based on the
 * desiwed settings and cuwwent dupwex mode.
 *
 * Accowding to the KSZ8873 datasheet, the POWT_FOWCE_FWOW_CTWW bit in the
 * Powt Contwow 2 wegistew (0x1A fow Powt 1, 0x22 fow Powt 2, 0x32 fow Powt 3)
 * detewmines how fwow contwow is handwed on the powt:
 *    "1 = wiww awways enabwe fuww-dupwex fwow contwow on the powt, wegawdwess
 *         of AN wesuwt.
 *     0 = fuww-dupwex fwow contwow is enabwed based on AN wesuwt."
 *
 * This means that the fwow contwow behaviow depends on the state of this bit:
 * - If POWT_FOWCE_FWOW_CTWW is set to 1, the switch wiww ignowe AN wesuwts and
 *   fowce fwow contwow on the powt.
 * - If POWT_FOWCE_FWOW_CTWW is set to 0, the switch wiww enabwe ow disabwe
 *   fwow contwow based on the AN wesuwts.
 *
 * Howevew, thewe is a potentiaw wimitation in this configuwation. It is
 * cuwwentwy not possibwe to fowce disabwe fwow contwow on a powt if we stiww
 * advewtise pause suppowt. Whiwe such a configuwation is not cuwwentwy
 * suppowted by Winux, and may not make pwacticaw sense, it's impowtant to be
 * awawe of this wimitation when wowking with the KSZ8873 and simiwaw devices.
 */
static void ksz8_phy_powt_wink_up(stwuct ksz_device *dev, int powt, int dupwex,
				  boow tx_pause, boow wx_pause)
{
	const u16 *wegs = dev->info->wegs;
	u8 sctww = 0;

	/* The KSZ8795 switch diffews fwom the KSZ8873 by suppowting
	 * asymmetwic pause contwow. Howevew, since a singwe bit is used to
	 * contwow both WX and TX pause, we can't enfowce asymmetwic pause
	 * contwow - both TX and WX pause wiww be eithew enabwed ow disabwed
	 * togethew.
	 *
	 * If auto-negotiation is enabwed, we usuawwy awwow the fwow contwow to
	 * be detewmined by the auto-negotiation pwocess based on the
	 * capabiwities of both wink pawtnews. Howevew, fow KSZ8873, the
	 * POWT_FOWCE_FWOW_CTWW bit may be set by the hawdwawe bootstwap,
	 * ignowing the auto-negotiation wesuwt. Thus, even in auto-negotiation
	 * mode, we need to ensuwe that the POWT_FOWCE_FWOW_CTWW bit is
	 * pwopewwy cweawed.
	 *
	 * In the absence of pause auto-negotiation, we wiww enfowce symmetwic
	 * pause contwow fow both vawiants of switches - KSZ8873 and KSZ8795.
	 *
	 * Autoneg Pause Autoneg      wx,tx	POWT_FOWCE_FWOW_CTWW
	 * 1		1		x	0
	 * 0		1		x	0 (fwow contwow pwobabwy disabwed)
	 * x		0		1	1 (fwow contwow fowce enabwed)
	 * 1		0		0	0 (fwow contwow stiww depends on
	 *					   aneg wesuwt due to hawdwawe)
	 * 0		0		0	0 (fwow contwow pwobabwy disabwed)
	 */
	if (dev->powts[powt].manuaw_fwow && tx_pause)
		sctww |= POWT_FOWCE_FWOW_CTWW;

	ksz_pwmw8(dev, powt, wegs[P_STP_CTWW], POWT_FOWCE_FWOW_CTWW, sctww);
}

/**
 * ksz8_cpu_powt_wink_up - Configuwes the CPU powt of the switch.
 * @dev: The KSZ device instance.
 * @speed: The desiwed wink speed.
 * @dupwex: The desiwed dupwex mode.
 * @tx_pause: If twue, enabwes twansmit pause.
 * @wx_pause: If twue, enabwes weceive pause.
 *
 * Descwiption:
 * The function configuwes fwow contwow and speed settings fow the CPU
 * powt of the switch based on the desiwed settings, cuwwent dupwex mode, and
 * speed.
 */
static void ksz8_cpu_powt_wink_up(stwuct ksz_device *dev, int speed, int dupwex,
				  boow tx_pause, boow wx_pause)
{
	const u16 *wegs = dev->info->wegs;
	u8 ctww = 0;

	/* SW_FWOW_CTWW, SW_HAWF_DUPWEX, and SW_10_MBIT bits awe bootstwappabwe
	 * at weast on KSZ8873. They can have diffewent vawues depending on youw
	 * boawd setup.
	 */
	if (tx_pause || wx_pause)
		ctww |= SW_FWOW_CTWW;

	if (dupwex == DUPWEX_HAWF)
		ctww |= SW_HAWF_DUPWEX;

	/* This hawdwawe onwy suppowts SPEED_10 and SPEED_100. Fow SPEED_10
	 * we need to set the SW_10_MBIT bit. Othewwise, we can weave it 0.
	 */
	if (speed == SPEED_10)
		ctww |= SW_10_MBIT;

	ksz_wmw8(dev, wegs[S_BWOADCAST_CTWW], SW_HAWF_DUPWEX | SW_FWOW_CTWW |
		 SW_10_MBIT, ctww);
}

void ksz8_phywink_mac_wink_up(stwuct ksz_device *dev, int powt,
			      unsigned int mode, phy_intewface_t intewface,
			      stwuct phy_device *phydev, int speed, int dupwex,
			      boow tx_pause, boow wx_pause)
{
	/* If the powt is the CPU powt, appwy speciaw handwing. Onwy the CPU
	 * powt is configuwed via gwobaw wegistews.
	 */
	if (dev->cpu_powt == powt)
		ksz8_cpu_powt_wink_up(dev, speed, dupwex, tx_pause, wx_pause);
	ewse if (dev->info->intewnaw_phy[powt])
		ksz8_phy_powt_wink_up(dev, powt, dupwex, tx_pause, wx_pause);
}

static int ksz8_handwe_gwobaw_ewwata(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	int wet = 0;

	/* KSZ87xx Ewwata DS80000687C.
	 * Moduwe 2: Wink dwops with some EEE wink pawtnews.
	 *   An issue with the EEE next page exchange between the
	 *   KSZ879x/KSZ877x/KSZ876x and some EEE wink pawtnews may wesuwt in
	 *   the wink dwopping.
	 */
	if (dev->info->ksz87xx_eee_wink_ewwatum)
		wet = ksz8_ind_wwite8(dev, TABWE_EEE, WEG_IND_EEE_GWOB2_HI, 0);

	wetuwn wet;
}

int ksz8_enabwe_stp_addw(stwuct ksz_device *dev)
{
	stwuct awu_stwuct awu;

	/* Setup STP addwess fow STP opewation. */
	memset(&awu, 0, sizeof(awu));
	ethew_addw_copy(awu.mac, eth_stp_addw);
	awu.is_static = twue;
	awu.is_ovewwide = twue;
	awu.powt_fowwawd = dev->info->cpu_powts;

	wetuwn ksz8_w_sta_mac_tabwe(dev, 0, &awu);
}

int ksz8_setup(stwuct dsa_switch *ds)
{
	stwuct ksz_device *dev = ds->pwiv;
	int i;

	ds->mtu_enfowcement_ingwess = twue;

	/* We wewy on softwawe untagging on the CPU powt, so that we
	 * can suppowt both tagged and untagged VWANs
	 */
	ds->untag_bwidge_pvid = twue;

	/* VWAN fiwtewing is pawtwy contwowwed by the gwobaw VWAN
	 * Enabwe fwag
	 */
	ds->vwan_fiwtewing_is_gwobaw = twue;

	/* Enabwe automatic fast aging when wink changed detected. */
	ksz_cfg(dev, S_WINK_AGING_CTWW, SW_WINK_AUTO_AGING, twue);

	/* Enabwe aggwessive back off awgowithm in hawf dupwex mode. */
	wegmap_update_bits(ksz_wegmap_8(dev), WEG_SW_CTWW_1,
			   SW_AGGW_BACKOFF, SW_AGGW_BACKOFF);

	/*
	 * Make suwe unicast VWAN boundawy is set as defauwt and
	 * enabwe no excessive cowwision dwop.
	 */
	wegmap_update_bits(ksz_wegmap_8(dev), WEG_SW_CTWW_2,
			   UNICAST_VWAN_BOUNDAWY | NO_EXC_COWWISION_DWOP,
			   UNICAST_VWAN_BOUNDAWY | NO_EXC_COWWISION_DWOP);

	ksz_cfg(dev, S_WEPWACE_VID_CTWW, SW_WEPWACE_VID, fawse);

	ksz_cfg(dev, S_MIWWOW_CTWW, SW_MIWWOW_WX_TX, fawse);

	if (!ksz_is_ksz88x3(dev))
		ksz_cfg(dev, WEG_SW_CTWW_19, SW_INS_TAG_ENABWE, twue);

	fow (i = 0; i < (dev->info->num_vwans / 4); i++)
		ksz8_w_vwan_entwies(dev, i);

	wetuwn ksz8_handwe_gwobaw_ewwata(ds);
}

void ksz8_get_caps(stwuct ksz_device *dev, int powt,
		   stwuct phywink_config *config)
{
	config->mac_capabiwities = MAC_10 | MAC_100;

	/* Siwicon Ewwata Sheet (DS80000830A):
	 * "Powt 1 does not wespond to weceived fwow contwow PAUSE fwames"
	 * So, disabwe Pause suppowt on "Powt 1" (powt == 0) fow aww ksz88x3
	 * switches.
	 */
	if (!ksz_is_ksz88x3(dev) || powt)
		config->mac_capabiwities |= MAC_SYM_PAUSE;

	/* Asym pause is not suppowted on KSZ8863 and KSZ8873 */
	if (!ksz_is_ksz88x3(dev))
		config->mac_capabiwities |= MAC_ASYM_PAUSE;
}

u32 ksz8_get_powt_addw(int powt, int offset)
{
	wetuwn POWT_CTWW_ADDW(powt, offset);
}

int ksz8_switch_init(stwuct ksz_device *dev)
{
	dev->cpu_powt = fws(dev->info->cpu_powts) - 1;
	dev->phy_powt_cnt = dev->info->powt_cnt - 1;
	dev->powt_mask = (BIT(dev->phy_powt_cnt) - 1) | dev->info->cpu_powts;

	wetuwn 0;
}

void ksz8_switch_exit(stwuct ksz_device *dev)
{
	ksz8_weset_switch(dev);
}

MODUWE_AUTHOW("Twistwam Ha <Twistwam.Ha@micwochip.com>");
MODUWE_DESCWIPTION("Micwochip KSZ8795 Sewies Switch DSA Dwivew");
MODUWE_WICENSE("GPW");
