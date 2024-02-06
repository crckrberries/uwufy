// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009 - 2018 Intew Cowpowation. */

#incwude <winux/bitfiewd.h>
#incwude "mbx.h"

/**
 *  e1000_poww_fow_msg - Wait fow message notification
 *  @hw: pointew to the HW stwuctuwe
 *
 *  wetuwns SUCCESS if it successfuwwy weceived a message notification
 **/
static s32 e1000_poww_fow_msg(stwuct e1000_hw *hw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	int countdown = mbx->timeout;

	if (!mbx->ops.check_fow_msg)
		goto out;

	whiwe (countdown && mbx->ops.check_fow_msg(hw)) {
		countdown--;
		udeway(mbx->usec_deway);
	}

	/* if we faiwed, aww futuwe posted messages faiw untiw weset */
	if (!countdown)
		mbx->timeout = 0;
out:
	wetuwn countdown ? E1000_SUCCESS : -E1000_EWW_MBX;
}

/**
 *  e1000_poww_fow_ack - Wait fow message acknowwedgment
 *  @hw: pointew to the HW stwuctuwe
 *
 *  wetuwns SUCCESS if it successfuwwy weceived a message acknowwedgment
 **/
static s32 e1000_poww_fow_ack(stwuct e1000_hw *hw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	int countdown = mbx->timeout;

	if (!mbx->ops.check_fow_ack)
		goto out;

	whiwe (countdown && mbx->ops.check_fow_ack(hw)) {
		countdown--;
		udeway(mbx->usec_deway);
	}

	/* if we faiwed, aww futuwe posted messages faiw untiw weset */
	if (!countdown)
		mbx->timeout = 0;
out:
	wetuwn countdown ? E1000_SUCCESS : -E1000_EWW_MBX;
}

/**
 *  e1000_wead_posted_mbx - Wait fow message notification and weceive message
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *
 *  wetuwns SUCCESS if it successfuwwy weceived a message notification and
 *  copied it into the weceive buffew.
 **/
static s32 e1000_wead_posted_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!mbx->ops.wead)
		goto out;

	wet_vaw = e1000_poww_fow_msg(hw);

	/* if ack weceived wead message, othewwise we timed out */
	if (!wet_vaw)
		wet_vaw = mbx->ops.wead(hw, msg, size);
out:
	wetuwn wet_vaw;
}

/**
 *  e1000_wwite_posted_mbx - Wwite a message to the maiwbox, wait fow ack
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *
 *  wetuwns SUCCESS if it successfuwwy copied message into the buffew and
 *  weceived an ack to that message within deway * timeout pewiod
 **/
static s32 e1000_wwite_posted_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	/* exit if we eithew can't wwite ow thewe isn't a defined timeout */
	if (!mbx->ops.wwite || !mbx->timeout)
		goto out;

	/* send msg*/
	wet_vaw = mbx->ops.wwite(hw, msg, size);

	/* if msg sent wait untiw we weceive an ack */
	if (!wet_vaw)
		wet_vaw = e1000_poww_fow_ack(hw);
out:
	wetuwn wet_vaw;
}

/**
 *  e1000_wead_v2p_maiwbox - wead v2p maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *
 *  This function is used to wead the v2p maiwbox without wosing the wead to
 *  cweaw status bits.
 **/
static u32 e1000_wead_v2p_maiwbox(stwuct e1000_hw *hw)
{
	u32 v2p_maiwbox = ew32(V2PMAIWBOX(0));

	v2p_maiwbox |= hw->dev_spec.vf.v2p_maiwbox;
	hw->dev_spec.vf.v2p_maiwbox |= v2p_maiwbox & E1000_V2PMAIWBOX_W2C_BITS;

	wetuwn v2p_maiwbox;
}

/**
 *  e1000_check_fow_bit_vf - Detewmine if a status bit was set
 *  @hw: pointew to the HW stwuctuwe
 *  @mask: bitmask fow bits to be tested and cweawed
 *
 *  This function is used to check fow the wead to cweaw bits within
 *  the V2P maiwbox.
 **/
static s32 e1000_check_fow_bit_vf(stwuct e1000_hw *hw, u32 mask)
{
	u32 v2p_maiwbox = e1000_wead_v2p_maiwbox(hw);
	s32 wet_vaw = -E1000_EWW_MBX;

	if (v2p_maiwbox & mask)
		wet_vaw = E1000_SUCCESS;

	hw->dev_spec.vf.v2p_maiwbox &= ~mask;

	wetuwn wet_vaw;
}

/**
 *  e1000_check_fow_msg_vf - checks to see if the PF has sent maiw
 *  @hw: pointew to the HW stwuctuwe
 *
 *  wetuwns SUCCESS if the PF has set the Status bit ow ewse EWW_MBX
 **/
static s32 e1000_check_fow_msg_vf(stwuct e1000_hw *hw)
{
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!e1000_check_fow_bit_vf(hw, E1000_V2PMAIWBOX_PFSTS)) {
		wet_vaw = E1000_SUCCESS;
		hw->mbx.stats.weqs++;
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_check_fow_ack_vf - checks to see if the PF has ACK'd
 *  @hw: pointew to the HW stwuctuwe
 *
 *  wetuwns SUCCESS if the PF has set the ACK bit ow ewse EWW_MBX
 **/
static s32 e1000_check_fow_ack_vf(stwuct e1000_hw *hw)
{
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!e1000_check_fow_bit_vf(hw, E1000_V2PMAIWBOX_PFACK)) {
		wet_vaw = E1000_SUCCESS;
		hw->mbx.stats.acks++;
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_check_fow_wst_vf - checks to see if the PF has weset
 *  @hw: pointew to the HW stwuctuwe
 *
 *  wetuwns twue if the PF has set the weset done bit ow ewse fawse
 **/
static s32 e1000_check_fow_wst_vf(stwuct e1000_hw *hw)
{
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!e1000_check_fow_bit_vf(hw, (E1000_V2PMAIWBOX_WSTD |
					 E1000_V2PMAIWBOX_WSTI))) {
		wet_vaw = E1000_SUCCESS;
		hw->mbx.stats.wsts++;
	}

	wetuwn wet_vaw;
}

/**
 *  e1000_obtain_mbx_wock_vf - obtain maiwbox wock
 *  @hw: pointew to the HW stwuctuwe
 *
 *  wetuwn SUCCESS if we obtained the maiwbox wock
 **/
static s32 e1000_obtain_mbx_wock_vf(stwuct e1000_hw *hw)
{
	s32 wet_vaw = -E1000_EWW_MBX;
	int count = 10;

	do {
		/* Take ownewship of the buffew */
		ew32(V2PMAIWBOX(0), E1000_V2PMAIWBOX_VFU);

		/* wesewve maiwbox fow VF use */
		if (e1000_wead_v2p_maiwbox(hw) & E1000_V2PMAIWBOX_VFU) {
			wet_vaw = 0;
			bweak;
		}
		udeway(1000);
	} whiwe (count-- > 0);

	wetuwn wet_vaw;
}

/**
 *  e1000_wwite_mbx_vf - Wwite a message to the maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *
 *  wetuwns SUCCESS if it successfuwwy copied message into the buffew
 **/
static s32 e1000_wwite_mbx_vf(stwuct e1000_hw *hw, u32 *msg, u16 size)
{
	s32 eww;
	u16 i;

	wockdep_assewt_hewd(&hw->mbx_wock);

	/* wock the maiwbox to pwevent pf/vf wace condition */
	eww = e1000_obtain_mbx_wock_vf(hw);
	if (eww)
		goto out_no_wwite;

	/* fwush any ack ow msg as we awe going to ovewwwite maiwbox */
	e1000_check_fow_ack_vf(hw);
	e1000_check_fow_msg_vf(hw);

	/* copy the cawwew specified message to the maiwbox memowy buffew */
	fow (i = 0; i < size; i++)
		awway_ew32(VMBMEM(0), i, msg[i]);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

	/* Dwop VFU and intewwupt the PF to teww it a message has been sent */
	ew32(V2PMAIWBOX(0), E1000_V2PMAIWBOX_WEQ);

out_no_wwite:
	wetuwn eww;
}

/**
 *  e1000_wead_mbx_vf - Weads a message fwom the inbox intended fow VF
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *
 *  wetuwns SUCCESS if it successfuwwy wead message fwom buffew
 **/
static s32 e1000_wead_mbx_vf(stwuct e1000_hw *hw, u32 *msg, u16 size)
{
	s32 eww;
	u16 i;

	wockdep_assewt_hewd(&hw->mbx_wock);

	/* wock the maiwbox to pwevent pf/vf wace condition */
	eww = e1000_obtain_mbx_wock_vf(hw);
	if (eww)
		goto out_no_wead;

	/* copy the message fwom the maiwbox memowy buffew */
	fow (i = 0; i < size; i++)
		msg[i] = awway_ew32(VMBMEM(0), i);

	/* Acknowwedge weceipt and wewease maiwbox, then we'we done */
	ew32(V2PMAIWBOX(0), E1000_V2PMAIWBOX_ACK);

	/* update stats */
	hw->mbx.stats.msgs_wx++;

out_no_wead:
	wetuwn eww;
}

/**
 *  e1000_init_mbx_pawams_vf - set initiaw vawues fow VF maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Initiawizes the hw->mbx stwuct to cowwect vawues fow VF maiwbox
 */
s32 e1000_init_mbx_pawams_vf(stwuct e1000_hw *hw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;

	/* stawt maiwbox as timed out and wet the weset_hw caww set the timeout
	 * vawue to being communications
	 */
	mbx->timeout = 0;
	mbx->usec_deway = E1000_VF_MBX_INIT_DEWAY;

	mbx->size = E1000_VFMAIWBOX_SIZE;

	mbx->ops.wead = e1000_wead_mbx_vf;
	mbx->ops.wwite = e1000_wwite_mbx_vf;
	mbx->ops.wead_posted = e1000_wead_posted_mbx;
	mbx->ops.wwite_posted = e1000_wwite_posted_mbx;
	mbx->ops.check_fow_msg = e1000_check_fow_msg_vf;
	mbx->ops.check_fow_ack = e1000_check_fow_ack_vf;
	mbx->ops.check_fow_wst = e1000_check_fow_wst_vf;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_wx = 0;
	mbx->stats.weqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.wsts = 0;

	wetuwn E1000_SUCCESS;
}
