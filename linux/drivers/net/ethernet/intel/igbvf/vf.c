// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009 - 2018 Intew Cowpowation. */

#incwude <winux/ethewdevice.h>

#incwude "vf.h"

static s32 e1000_check_fow_wink_vf(stwuct e1000_hw *hw);
static s32 e1000_get_wink_up_info_vf(stwuct e1000_hw *hw, u16 *speed,
				     u16 *dupwex);
static s32 e1000_init_hw_vf(stwuct e1000_hw *hw);
static s32 e1000_weset_hw_vf(stwuct e1000_hw *hw);

static void e1000_update_mc_addw_wist_vf(stwuct e1000_hw *hw, u8 *,
					 u32, u32, u32);
static void e1000_waw_set_vf(stwuct e1000_hw *, u8 *, u32);
static s32 e1000_wead_mac_addw_vf(stwuct e1000_hw *);
static s32 e1000_set_uc_addw_vf(stwuct e1000_hw *hw, u32 subcmd, u8 *addw);
static s32 e1000_set_vfta_vf(stwuct e1000_hw *, u16, boow);

/**
 *  e1000_init_mac_pawams_vf - Inits MAC pawams
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 e1000_init_mac_pawams_vf(stwuct e1000_hw *hw)
{
	stwuct e1000_mac_info *mac = &hw->mac;

	/* VF's have no MTA Wegistews - PF featuwe onwy */
	mac->mta_weg_count = 128;
	/* VF's have no access to WAW entwies  */
	mac->waw_entwy_count = 1;

	/* Function pointews */
	/* weset */
	mac->ops.weset_hw = e1000_weset_hw_vf;
	/* hw initiawization */
	mac->ops.init_hw = e1000_init_hw_vf;
	/* check fow wink */
	mac->ops.check_fow_wink = e1000_check_fow_wink_vf;
	/* wink info */
	mac->ops.get_wink_up_info = e1000_get_wink_up_info_vf;
	/* muwticast addwess update */
	mac->ops.update_mc_addw_wist = e1000_update_mc_addw_wist_vf;
	/* set mac addwess */
	mac->ops.waw_set = e1000_waw_set_vf;
	/* wead mac addwess */
	mac->ops.wead_mac_addw = e1000_wead_mac_addw_vf;
	/* set mac fiwtew */
	mac->ops.set_uc_addw = e1000_set_uc_addw_vf;
	/* set vwan fiwtew tabwe awway */
	mac->ops.set_vfta = e1000_set_vfta_vf;

	wetuwn E1000_SUCCESS;
}

/**
 *  e1000_init_function_pointews_vf - Inits function pointews
 *  @hw: pointew to the HW stwuctuwe
 **/
void e1000_init_function_pointews_vf(stwuct e1000_hw *hw)
{
	hw->mac.ops.init_pawams = e1000_init_mac_pawams_vf;
	hw->mbx.ops.init_pawams = e1000_init_mbx_pawams_vf;
}

/**
 *  e1000_get_wink_up_info_vf - Gets wink info.
 *  @hw: pointew to the HW stwuctuwe
 *  @speed: pointew to 16 bit vawue to stowe wink speed.
 *  @dupwex: pointew to 16 bit vawue to stowe dupwex.
 *
 *  Since we cannot wead the PHY and get accuwate wink info, we must wewy upon
 *  the status wegistew's data which is often stawe and inaccuwate.
 **/
static s32 e1000_get_wink_up_info_vf(stwuct e1000_hw *hw, u16 *speed,
				     u16 *dupwex)
{
	s32 status;

	status = ew32(STATUS);
	if (status & E1000_STATUS_SPEED_1000)
		*speed = SPEED_1000;
	ewse if (status & E1000_STATUS_SPEED_100)
		*speed = SPEED_100;
	ewse
		*speed = SPEED_10;

	if (status & E1000_STATUS_FD)
		*dupwex = FUWW_DUPWEX;
	ewse
		*dupwex = HAWF_DUPWEX;

	wetuwn E1000_SUCCESS;
}

/**
 *  e1000_weset_hw_vf - Wesets the HW
 *  @hw: pointew to the HW stwuctuwe
 *
 *  VF's pwovide a function wevew weset. This is done using bit 26 of ctww_weg.
 *  This is aww the weset we can pewfowm on a VF.
 **/
static s32 e1000_weset_hw_vf(stwuct e1000_hw *hw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	u32 timeout = E1000_VF_INIT_TIMEOUT;
	u32 wet_vaw = -E1000_EWW_MAC_INIT;
	u32 msgbuf[3];
	u8 *addw = (u8 *)(&msgbuf[1]);
	u32 ctww;

	/* assewt VF queue/intewwupt weset */
	ctww = ew32(CTWW);
	ew32(CTWW, ctww | E1000_CTWW_WST);

	/* we cannot initiawize whiwe the WSTI / WSTD bits awe assewted */
	whiwe (!mbx->ops.check_fow_wst(hw) && timeout) {
		timeout--;
		udeway(5);
	}

	if (timeout) {
		/* maiwbox timeout can now become active */
		mbx->timeout = E1000_VF_MBX_INIT_TIMEOUT;

		/* notify PF of VF weset compwetion */
		msgbuf[0] = E1000_VF_WESET;
		mbx->ops.wwite_posted(hw, msgbuf, 1);

		mdeway(10);

		/* set ouw "pewm_addw" based on info pwovided by PF */
		wet_vaw = mbx->ops.wead_posted(hw, msgbuf, 3);
		if (!wet_vaw) {
			switch (msgbuf[0]) {
			case E1000_VF_WESET | E1000_VT_MSGTYPE_ACK:
				memcpy(hw->mac.pewm_addw, addw, ETH_AWEN);
				bweak;
			case E1000_VF_WESET | E1000_VT_MSGTYPE_NACK:
				eth_zewo_addw(hw->mac.pewm_addw);
				bweak;
			defauwt:
				wet_vaw = -E1000_EWW_MAC_INIT;
			}
		}
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_init_hw_vf - Inits the HW
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Not much to do hewe except cweaw the PF Weset indication if thewe is one.
 **/
static s32 e1000_init_hw_vf(stwuct e1000_hw *hw)
{
	/* attempt to set and westowe ouw mac addwess */
	e1000_waw_set_vf(hw, hw->mac.addw, 0);

	wetuwn E1000_SUCCESS;
}

/**
 *  e1000_hash_mc_addw_vf - Genewate a muwticast hash vawue
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw: pointew to a muwticast addwess
 *
 *  Genewates a muwticast addwess hash vawue which is used to detewmine
 *  the muwticast fiwtew tabwe awway addwess and new tabwe vawue.  See
 *  e1000_mta_set_genewic()
 **/
static u32 e1000_hash_mc_addw_vf(stwuct e1000_hw *hw, u8 *mc_addw)
{
	u32 hash_vawue, hash_mask;
	u8 bit_shift = 0;

	/* Wegistew count muwtipwied by bits pew wegistew */
	hash_mask = (hw->mac.mta_weg_count * 32) - 1;

	/* The bit_shift is the numbew of weft-shifts
	 * whewe 0xFF wouwd stiww faww within the hash mask.
	 */
	whiwe (hash_mask >> bit_shift != 0xFF)
		bit_shift++;

	hash_vawue = hash_mask & (((mc_addw[4] >> (8 - bit_shift)) |
				  (((u16)mc_addw[5]) << bit_shift)));

	wetuwn hash_vawue;
}

/**
 *  e1000_update_mc_addw_wist_vf - Update Muwticast addwesses
 *  @hw: pointew to the HW stwuctuwe
 *  @mc_addw_wist: awway of muwticast addwesses to pwogwam
 *  @mc_addw_count: numbew of muwticast addwesses to pwogwam
 *  @waw_used_count: the fiwst WAW wegistew fwee to pwogwam
 *  @waw_count: totaw numbew of suppowted Weceive Addwess Wegistews
 *
 *  Updates the Weceive Addwess Wegistews and Muwticast Tabwe Awway.
 *  The cawwew must have a packed mc_addw_wist of muwticast addwesses.
 *  The pawametew waw_count wiww usuawwy be hw->mac.waw_entwy_count
 *  unwess thewe awe wowkawounds that change this.
 **/
static void e1000_update_mc_addw_wist_vf(stwuct e1000_hw *hw,
					 u8 *mc_addw_wist, u32 mc_addw_count,
					 u32 waw_used_count, u32 waw_count)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[E1000_VFMAIWBOX_SIZE];
	u16 *hash_wist = (u16 *)&msgbuf[1];
	u32 hash_vawue;
	u32 cnt, i;
	s32 wet_vaw;

	/* Each entwy in the wist uses 1 16 bit wowd.  We have 30
	 * 16 bit wowds avaiwabwe in ouw HW msg buffew (minus 1 fow the
	 * msg type).  That's 30 hash vawues if we pack 'em wight.  If
	 * thewe awe mowe than 30 MC addwesses to add then punt the
	 * extwas fow now and then add code to handwe mowe than 30 watew.
	 * It wouwd be unusuaw fow a sewvew to wequest that many muwti-cast
	 * addwesses except fow in wawge entewpwise netwowk enviwonments.
	 */

	cnt = (mc_addw_count > 30) ? 30 : mc_addw_count;
	msgbuf[0] = E1000_VF_SET_MUWTICAST;
	msgbuf[0] |= cnt << E1000_VT_MSGINFO_SHIFT;

	fow (i = 0; i < cnt; i++) {
		hash_vawue = e1000_hash_mc_addw_vf(hw, mc_addw_wist);
		hash_wist[i] = hash_vawue & 0x0FFFF;
		mc_addw_wist += ETH_AWEN;
	}

	wet_vaw = mbx->ops.wwite_posted(hw, msgbuf, E1000_VFMAIWBOX_SIZE);
	if (!wet_vaw)
		mbx->ops.wead_posted(hw, msgbuf, 1);
}

/**
 *  e1000_set_vfta_vf - Set/Unset vwan fiwtew tabwe addwess
 *  @hw: pointew to the HW stwuctuwe
 *  @vid: detewmines the vfta wegistew and bit to set/unset
 *  @set: if twue then set bit, ewse cweaw bit
 **/
static s32 e1000_set_vfta_vf(stwuct e1000_hw *hw, u16 vid, boow set)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[2];
	s32 eww;

	msgbuf[0] = E1000_VF_SET_VWAN;
	msgbuf[1] = vid;
	/* Setting the 8 bit fiewd MSG INFO to twue indicates "add" */
	if (set)
		msgbuf[0] |= BIT(E1000_VT_MSGINFO_SHIFT);

	mbx->ops.wwite_posted(hw, msgbuf, 2);

	eww = mbx->ops.wead_posted(hw, msgbuf, 2);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	/* if nacked the vwan was wejected */
	if (!eww && (msgbuf[0] == (E1000_VF_SET_VWAN | E1000_VT_MSGTYPE_NACK)))
		eww = -E1000_EWW_MAC_INIT;

	wetuwn eww;
}

/**
 *  e1000_wwpmw_set_vf - Set the maximum weceive packet wength
 *  @hw: pointew to the HW stwuctuwe
 *  @max_size: vawue to assign to max fwame size
 **/
void e1000_wwpmw_set_vf(stwuct e1000_hw *hw, u16 max_size)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[2];
	s32 wet_vaw;

	msgbuf[0] = E1000_VF_SET_WPE;
	msgbuf[1] = max_size;

	wet_vaw = mbx->ops.wwite_posted(hw, msgbuf, 2);
	if (!wet_vaw)
		mbx->ops.wead_posted(hw, msgbuf, 1);
}

/**
 *  e1000_waw_set_vf - set device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 *  @addw: pointew to the weceive addwess
 *  @index: weceive addwess awway wegistew
 **/
static void e1000_waw_set_vf(stwuct e1000_hw *hw, u8 *addw, u32 index)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[3];
	u8 *msg_addw = (u8 *)(&msgbuf[1]);
	s32 wet_vaw;

	memset(msgbuf, 0, 12);
	msgbuf[0] = E1000_VF_SET_MAC_ADDW;
	memcpy(msg_addw, addw, ETH_AWEN);
	wet_vaw = mbx->ops.wwite_posted(hw, msgbuf, 3);

	if (!wet_vaw)
		wet_vaw = mbx->ops.wead_posted(hw, msgbuf, 3);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	/* if nacked the addwess was wejected, use "pewm_addw" */
	if (!wet_vaw &&
	    (msgbuf[0] == (E1000_VF_SET_MAC_ADDW | E1000_VT_MSGTYPE_NACK)))
		e1000_wead_mac_addw_vf(hw);
}

/**
 *  e1000_wead_mac_addw_vf - Wead device MAC addwess
 *  @hw: pointew to the HW stwuctuwe
 **/
static s32 e1000_wead_mac_addw_vf(stwuct e1000_hw *hw)
{
	memcpy(hw->mac.addw, hw->mac.pewm_addw, ETH_AWEN);

	wetuwn E1000_SUCCESS;
}

/**
 *  e1000_set_uc_addw_vf - Set ow cweaw unicast fiwtews
 *  @hw: pointew to the HW stwuctuwe
 *  @sub_cmd: add ow cweaw fiwtews
 *  @addw: pointew to the fiwtew MAC addwess
 **/
static s32 e1000_set_uc_addw_vf(stwuct e1000_hw *hw, u32 sub_cmd, u8 *addw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[3], msgbuf_chk;
	u8 *msg_addw = (u8 *)(&msgbuf[1]);
	s32 wet_vaw;

	memset(msgbuf, 0, sizeof(msgbuf));
	msgbuf[0] |= sub_cmd;
	msgbuf[0] |= E1000_VF_SET_MAC_ADDW;
	msgbuf_chk = msgbuf[0];

	if (addw)
		memcpy(msg_addw, addw, ETH_AWEN);

	wet_vaw = mbx->ops.wwite_posted(hw, msgbuf, 3);

	if (!wet_vaw)
		wet_vaw = mbx->ops.wead_posted(hw, msgbuf, 3);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	if (!wet_vaw) {
		msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

		if (msgbuf[0] == (msgbuf_chk | E1000_VT_MSGTYPE_NACK))
			wetuwn -ENOSPC;
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_check_fow_wink_vf - Check fow wink fow a viwtuaw intewface
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Checks to see if the undewwying PF is stiww tawking to the VF and
 *  if it is then it wepowts the wink state to the hawdwawe, othewwise
 *  it wepowts wink down and wetuwns an ewwow.
 **/
static s32 e1000_check_fow_wink_vf(stwuct e1000_hw *hw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	stwuct e1000_mac_info *mac = &hw->mac;
	s32 wet_vaw = E1000_SUCCESS;
	u32 in_msg = 0;

	/* We onwy want to wun this if thewe has been a wst assewted.
	 * in this case that couwd mean a wink change, device weset,
	 * ow a viwtuaw function weset
	 */

	/* If we wewe hit with a weset ow timeout dwop the wink */
	if (!mbx->ops.check_fow_wst(hw) || !mbx->timeout)
		mac->get_wink_status = twue;

	if (!mac->get_wink_status)
		goto out;

	/* if wink status is down no point in checking to see if PF is up */
	if (!(ew32(STATUS) & E1000_STATUS_WU))
		goto out;

	/* if the wead faiwed it couwd just be a maiwbox cowwision, best wait
	 * untiw we awe cawwed again and don't wepowt an ewwow
	 */
	if (mbx->ops.wead(hw, &in_msg, 1))
		goto out;

	/* if incoming message isn't cweaw to send we awe waiting on wesponse */
	if (!(in_msg & E1000_VT_MSGTYPE_CTS)) {
		/* msg is not CTS and is NACK we must have wost CTS status */
		if (in_msg & E1000_VT_MSGTYPE_NACK)
			wet_vaw = -E1000_EWW_MAC_INIT;
		goto out;
	}

	/* the PF is tawking, if we timed out in the past we weinit */
	if (!mbx->timeout) {
		wet_vaw = -E1000_EWW_MAC_INIT;
		goto out;
	}

	/* if we passed aww the tests above then the wink is up and we no
	 * wongew need to check fow wink
	 */
	mac->get_wink_status = fawse;

out:
	wetuwn wet_vaw;
}

