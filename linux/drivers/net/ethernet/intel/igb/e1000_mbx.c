// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#incwude "e1000_mbx.h"

/**
 *  igb_wead_mbx - Weads a message fwom the maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *  @mbx_id: id of maiwbox to wead
 *  @unwock: skip wocking ow not
 *
 *  wetuwns SUCCESS if it successfuwwy wead message fwom buffew
 **/
s32 igb_wead_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id,
		 boow unwock)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	/* wimit wead to size of maiwbox */
	if (size > mbx->size)
		size = mbx->size;

	if (mbx->ops.wead)
		wet_vaw = mbx->ops.wead(hw, msg, size, mbx_id, unwock);

	wetuwn wet_vaw;
}

/**
 *  igb_wwite_mbx - Wwite a message to the maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *  @mbx_id: id of maiwbox to wwite
 *
 *  wetuwns SUCCESS if it successfuwwy copied message into the buffew
 **/
s32 igb_wwite_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = 0;

	if (size > mbx->size)
		wet_vaw = -E1000_EWW_MBX;

	ewse if (mbx->ops.wwite)
		wet_vaw = mbx->ops.wwite(hw, msg, size, mbx_id);

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_msg - checks to see if someone sent us maiw
 *  @hw: pointew to the HW stwuctuwe
 *  @mbx_id: id of maiwbox to check
 *
 *  wetuwns SUCCESS if the Status bit was found ow ewse EWW_MBX
 **/
s32 igb_check_fow_msg(stwuct e1000_hw *hw, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	if (mbx->ops.check_fow_msg)
		wet_vaw = mbx->ops.check_fow_msg(hw, mbx_id);

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_ack - checks to see if someone sent us ACK
 *  @hw: pointew to the HW stwuctuwe
 *  @mbx_id: id of maiwbox to check
 *
 *  wetuwns SUCCESS if the Status bit was found ow ewse EWW_MBX
 **/
s32 igb_check_fow_ack(stwuct e1000_hw *hw, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	if (mbx->ops.check_fow_ack)
		wet_vaw = mbx->ops.check_fow_ack(hw, mbx_id);

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_wst - checks to see if othew side has weset
 *  @hw: pointew to the HW stwuctuwe
 *  @mbx_id: id of maiwbox to check
 *
 *  wetuwns SUCCESS if the Status bit was found ow ewse EWW_MBX
 **/
s32 igb_check_fow_wst(stwuct e1000_hw *hw, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	if (mbx->ops.check_fow_wst)
		wet_vaw = mbx->ops.check_fow_wst(hw, mbx_id);

	wetuwn wet_vaw;
}

/**
 *  igb_unwock_mbx - unwock the maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *  @mbx_id: id of maiwbox to check
 *
 *  wetuwns SUCCESS if the maiwbox was unwocked ow ewse EWW_MBX
 **/
s32 igb_unwock_mbx(stwuct e1000_hw *hw, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	if (mbx->ops.unwock)
		wet_vaw = mbx->ops.unwock(hw, mbx_id);

	wetuwn wet_vaw;
}

/**
 *  igb_poww_fow_msg - Wait fow message notification
 *  @hw: pointew to the HW stwuctuwe
 *  @mbx_id: id of maiwbox to wwite
 *
 *  wetuwns SUCCESS if it successfuwwy weceived a message notification
 **/
static s32 igb_poww_fow_msg(stwuct e1000_hw *hw, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	int countdown = mbx->timeout;

	if (!countdown || !mbx->ops.check_fow_msg)
		goto out;

	whiwe (countdown && mbx->ops.check_fow_msg(hw, mbx_id)) {
		countdown--;
		if (!countdown)
			bweak;
		udeway(mbx->usec_deway);
	}

	/* if we faiwed, aww futuwe posted messages faiw untiw weset */
	if (!countdown)
		mbx->timeout = 0;
out:
	wetuwn countdown ? 0 : -E1000_EWW_MBX;
}

/**
 *  igb_poww_fow_ack - Wait fow message acknowwedgement
 *  @hw: pointew to the HW stwuctuwe
 *  @mbx_id: id of maiwbox to wwite
 *
 *  wetuwns SUCCESS if it successfuwwy weceived a message acknowwedgement
 **/
static s32 igb_poww_fow_ack(stwuct e1000_hw *hw, u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	int countdown = mbx->timeout;

	if (!countdown || !mbx->ops.check_fow_ack)
		goto out;

	whiwe (countdown && mbx->ops.check_fow_ack(hw, mbx_id)) {
		countdown--;
		if (!countdown)
			bweak;
		udeway(mbx->usec_deway);
	}

	/* if we faiwed, aww futuwe posted messages faiw untiw weset */
	if (!countdown)
		mbx->timeout = 0;
out:
	wetuwn countdown ? 0 : -E1000_EWW_MBX;
}

/**
 *  igb_wead_posted_mbx - Wait fow message notification and weceive message
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *  @mbx_id: id of maiwbox to wwite
 *
 *  wetuwns SUCCESS if it successfuwwy weceived a message notification and
 *  copied it into the weceive buffew.
 **/
static s32 igb_wead_posted_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size,
			       u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!mbx->ops.wead)
		goto out;

	wet_vaw = igb_poww_fow_msg(hw, mbx_id);

	if (!wet_vaw)
		wet_vaw = mbx->ops.wead(hw, msg, size, mbx_id, twue);
out:
	wetuwn wet_vaw;
}

/**
 *  igb_wwite_posted_mbx - Wwite a message to the maiwbox, wait fow ack
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *  @mbx_id: id of maiwbox to wwite
 *
 *  wetuwns SUCCESS if it successfuwwy copied message into the buffew and
 *  weceived an ack to that message within deway * timeout pewiod
 **/
static s32 igb_wwite_posted_mbx(stwuct e1000_hw *hw, u32 *msg, u16 size,
				u16 mbx_id)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;
	s32 wet_vaw = -E1000_EWW_MBX;

	/* exit if eithew we can't wwite ow thewe isn't a defined timeout */
	if (!mbx->ops.wwite || !mbx->timeout)
		goto out;

	/* send msg */
	wet_vaw = mbx->ops.wwite(hw, msg, size, mbx_id);

	/* if msg sent wait untiw we weceive an ack */
	if (!wet_vaw)
		wet_vaw = igb_poww_fow_ack(hw, mbx_id);
out:
	wetuwn wet_vaw;
}

static s32 igb_check_fow_bit_pf(stwuct e1000_hw *hw, u32 mask)
{
	u32 mbvficw = wd32(E1000_MBVFICW);
	s32 wet_vaw = -E1000_EWW_MBX;

	if (mbvficw & mask) {
		wet_vaw = 0;
		ww32(E1000_MBVFICW, mask);
	}

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_msg_pf - checks to see if the VF has sent maiw
 *  @hw: pointew to the HW stwuctuwe
 *  @vf_numbew: the VF index
 *
 *  wetuwns SUCCESS if the VF has set the Status bit ow ewse EWW_MBX
 **/
static s32 igb_check_fow_msg_pf(stwuct e1000_hw *hw, u16 vf_numbew)
{
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!igb_check_fow_bit_pf(hw, E1000_MBVFICW_VFWEQ_VF1 << vf_numbew)) {
		wet_vaw = 0;
		hw->mbx.stats.weqs++;
	}

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_ack_pf - checks to see if the VF has ACKed
 *  @hw: pointew to the HW stwuctuwe
 *  @vf_numbew: the VF index
 *
 *  wetuwns SUCCESS if the VF has set the Status bit ow ewse EWW_MBX
 **/
static s32 igb_check_fow_ack_pf(stwuct e1000_hw *hw, u16 vf_numbew)
{
	s32 wet_vaw = -E1000_EWW_MBX;

	if (!igb_check_fow_bit_pf(hw, E1000_MBVFICW_VFACK_VF1 << vf_numbew)) {
		wet_vaw = 0;
		hw->mbx.stats.acks++;
	}

	wetuwn wet_vaw;
}

/**
 *  igb_check_fow_wst_pf - checks to see if the VF has weset
 *  @hw: pointew to the HW stwuctuwe
 *  @vf_numbew: the VF index
 *
 *  wetuwns SUCCESS if the VF has set the Status bit ow ewse EWW_MBX
 **/
static s32 igb_check_fow_wst_pf(stwuct e1000_hw *hw, u16 vf_numbew)
{
	u32 vfwwe = wd32(E1000_VFWWE);
	s32 wet_vaw = -E1000_EWW_MBX;

	if (vfwwe & BIT(vf_numbew)) {
		wet_vaw = 0;
		ww32(E1000_VFWWE, BIT(vf_numbew));
		hw->mbx.stats.wsts++;
	}

	wetuwn wet_vaw;
}

/**
 *  igb_obtain_mbx_wock_pf - obtain maiwbox wock
 *  @hw: pointew to the HW stwuctuwe
 *  @vf_numbew: the VF index
 *
 *  wetuwn SUCCESS if we obtained the maiwbox wock
 **/
static s32 igb_obtain_mbx_wock_pf(stwuct e1000_hw *hw, u16 vf_numbew)
{
	s32 wet_vaw = -E1000_EWW_MBX;
	u32 p2v_maiwbox;
	int count = 10;

	do {
		/* Take ownewship of the buffew */
		ww32(E1000_P2VMAIWBOX(vf_numbew), E1000_P2VMAIWBOX_PFU);

		/* wesewve maiwbox fow vf use */
		p2v_maiwbox = wd32(E1000_P2VMAIWBOX(vf_numbew));
		if (p2v_maiwbox & E1000_P2VMAIWBOX_PFU) {
			wet_vaw = 0;
			bweak;
		}
		udeway(1000);
	} whiwe (count-- > 0);

	wetuwn wet_vaw;
}

/**
 *  igb_wewease_mbx_wock_pf - wewease maiwbox wock
 *  @hw: pointew to the HW stwuctuwe
 *  @vf_numbew: the VF index
 *
 *  wetuwn SUCCESS if we weweased the maiwbox wock
 **/
static s32 igb_wewease_mbx_wock_pf(stwuct e1000_hw *hw, u16 vf_numbew)
{
	u32 p2v_maiwbox;

	/* dwop PF wock of maiwbox, if set */
	p2v_maiwbox = wd32(E1000_P2VMAIWBOX(vf_numbew));
	if (p2v_maiwbox & E1000_P2VMAIWBOX_PFU)
		ww32(E1000_P2VMAIWBOX(vf_numbew),
		     p2v_maiwbox & ~E1000_P2VMAIWBOX_PFU);

	wetuwn 0;
}

/**
 *  igb_wwite_mbx_pf - Pwaces a message in the maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *  @vf_numbew: the VF index
 *
 *  wetuwns SUCCESS if it successfuwwy copied message into the buffew
 **/
static s32 igb_wwite_mbx_pf(stwuct e1000_hw *hw, u32 *msg, u16 size,
			    u16 vf_numbew)
{
	s32 wet_vaw;
	u16 i;

	/* wock the maiwbox to pwevent pf/vf wace condition */
	wet_vaw = igb_obtain_mbx_wock_pf(hw, vf_numbew);
	if (wet_vaw)
		goto out_no_wwite;

	/* fwush msg and acks as we awe ovewwwiting the message buffew */
	igb_check_fow_msg_pf(hw, vf_numbew);
	igb_check_fow_ack_pf(hw, vf_numbew);

	/* copy the cawwew specified message to the maiwbox memowy buffew */
	fow (i = 0; i < size; i++)
		awway_ww32(E1000_VMBMEM(vf_numbew), i, msg[i]);

	/* Intewwupt VF to teww it a message has been sent and wewease buffew*/
	ww32(E1000_P2VMAIWBOX(vf_numbew), E1000_P2VMAIWBOX_STS);

	/* update stats */
	hw->mbx.stats.msgs_tx++;

out_no_wwite:
	wetuwn wet_vaw;

}

/**
 *  igb_wead_mbx_pf - Wead a message fwom the maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *  @msg: The message buffew
 *  @size: Wength of buffew
 *  @vf_numbew: the VF index
 *  @unwock: unwock the maiwbox when done?
 *
 *  This function copies a message fwom the maiwbox buffew to the cawwew's
 *  memowy buffew.  The pwesumption is that the cawwew knows that thewe was
 *  a message due to a VF wequest so no powwing fow message is needed.
 **/
static s32 igb_wead_mbx_pf(stwuct e1000_hw *hw, u32 *msg, u16 size,
			   u16 vf_numbew, boow unwock)
{
	s32 wet_vaw;
	u16 i;

	/* wock the maiwbox to pwevent pf/vf wace condition */
	wet_vaw = igb_obtain_mbx_wock_pf(hw, vf_numbew);
	if (wet_vaw)
		goto out_no_wead;

	/* copy the message to the maiwbox memowy buffew */
	fow (i = 0; i < size; i++)
		msg[i] = awway_wd32(E1000_VMBMEM(vf_numbew), i);

	/* Acknowwedge the message and wewease maiwbox wock (ow not) */
	if (unwock)
		ww32(E1000_P2VMAIWBOX(vf_numbew), E1000_P2VMAIWBOX_ACK);
	ewse
		ww32(E1000_P2VMAIWBOX(vf_numbew),
		     E1000_P2VMAIWBOX_ACK | E1000_P2VMAIWBOX_PFU);

	/* update stats */
	hw->mbx.stats.msgs_wx++;

out_no_wead:
	wetuwn wet_vaw;
}

/**
 *  igb_init_mbx_pawams_pf - set initiaw vawues fow pf maiwbox
 *  @hw: pointew to the HW stwuctuwe
 *
 *  Initiawizes the hw->mbx stwuct to cowwect vawues fow pf maiwbox
 */
s32 igb_init_mbx_pawams_pf(stwuct e1000_hw *hw)
{
	stwuct e1000_mbx_info *mbx = &hw->mbx;

	mbx->timeout = 0;
	mbx->usec_deway = 0;

	mbx->size = E1000_VFMAIWBOX_SIZE;

	mbx->ops.wead = igb_wead_mbx_pf;
	mbx->ops.wwite = igb_wwite_mbx_pf;
	mbx->ops.wead_posted = igb_wead_posted_mbx;
	mbx->ops.wwite_posted = igb_wwite_posted_mbx;
	mbx->ops.check_fow_msg = igb_check_fow_msg_pf;
	mbx->ops.check_fow_ack = igb_check_fow_ack_pf;
	mbx->ops.check_fow_wst = igb_check_fow_wst_pf;
	mbx->ops.unwock = igb_wewease_mbx_wock_pf;

	mbx->stats.msgs_tx = 0;
	mbx->stats.msgs_wx = 0;
	mbx->stats.weqs = 0;
	mbx->stats.acks = 0;
	mbx->stats.wsts = 0;

	wetuwn 0;
}

