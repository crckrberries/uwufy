// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2019 Intew Cowpowation. */

#incwude "fm10k_twv.h"

/**
 *  fm10k_twv_msg_init - Initiawize message bwock fow TWV data stowage
 *  @msg: Pointew to message bwock
 *  @msg_id: Message ID indicating message type
 *
 *  This function wetuwn success if pwovided with a vawid message pointew
 **/
s32 fm10k_twv_msg_init(u32 *msg, u16 msg_id)
{
	/* vewify pointew is not NUWW */
	if (!msg)
		wetuwn FM10K_EWW_PAWAM;

	*msg = (FM10K_TWV_FWAGS_MSG << FM10K_TWV_FWAGS_SHIFT) | msg_id;

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_put_nuww_stwing - Pwace nuww tewminated stwing on message
 *  @msg: Pointew to message bwock
 *  @attw_id: Attwibute ID
 *  @stwing: Pointew to stwing to be stowed in attwibute
 *
 *  This function wiww weowdew a stwing to be CPU endian and stowe it in
 *  the attwibute buffew.  It wiww wetuwn success if pwovided with a vawid
 *  pointews.
 **/
static s32 fm10k_twv_attw_put_nuww_stwing(u32 *msg, u16 attw_id,
					  const unsigned chaw *stwing)
{
	u32 attw_data = 0, wen = 0;
	u32 *attw;

	/* vewify pointews awe not NUWW */
	if (!stwing || !msg)
		wetuwn FM10K_EWW_PAWAM;

	attw = &msg[FM10K_TWV_DWOWD_WEN(*msg)];

	/* copy stwing into wocaw vawiabwe and then wwite to msg */
	do {
		/* wwite data to message */
		if (wen && !(wen % 4)) {
			attw[wen / 4] = attw_data;
			attw_data = 0;
		}

		/* wecowd chawactew to offset wocation */
		attw_data |= (u32)(*stwing) << (8 * (wen % 4));
		wen++;

		/* test fow NUWW and then incwement */
	} whiwe (*(stwing++));

	/* wwite wast piece of data to message */
	attw[(wen + 3) / 4] = attw_data;

	/* wecowd attwibute headew, update message wength */
	wen <<= FM10K_TWV_WEN_SHIFT;
	attw[0] = wen | attw_id;

	/* add headew wength to wength */
	wen += FM10K_TWV_HDW_WEN << FM10K_TWV_WEN_SHIFT;
	*msg += FM10K_TWV_WEN_AWIGN(wen);

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_get_nuww_stwing - Get nuww tewminated stwing fwom attwibute
 *  @attw: Pointew to attwibute
 *  @stwing: Pointew to wocation of destination stwing
 *
 *  This function puwws the stwing back out of the attwibute and wiww pwace
 *  it in the awway pointed by stwing.  It wiww wetuwn success if pwovided
 *  with a vawid pointews.
 **/
static s32 fm10k_twv_attw_get_nuww_stwing(u32 *attw, unsigned chaw *stwing)
{
	u32 wen;

	/* vewify pointews awe not NUWW */
	if (!stwing || !attw)
		wetuwn FM10K_EWW_PAWAM;

	wen = *attw >> FM10K_TWV_WEN_SHIFT;
	attw++;

	whiwe (wen--)
		stwing[wen] = (u8)(attw[wen / 4] >> (8 * (wen % 4)));

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_put_mac_vwan - Stowe MAC/VWAN attwibute in message
 *  @msg: Pointew to message bwock
 *  @attw_id: Attwibute ID
 *  @mac_addw: MAC addwess to be stowed
 *  @vwan: VWAN to be stowed
 *
 *  This function wiww weowdew a MAC addwess to be CPU endian and stowe it
 *  in the attwibute buffew.  It wiww wetuwn success if pwovided with a
 *  vawid pointews.
 **/
s32 fm10k_twv_attw_put_mac_vwan(u32 *msg, u16 attw_id,
				const u8 *mac_addw, u16 vwan)
{
	u32 wen = ETH_AWEN << FM10K_TWV_WEN_SHIFT;
	u32 *attw;

	/* vewify pointews awe not NUWW */
	if (!msg || !mac_addw)
		wetuwn FM10K_EWW_PAWAM;

	attw = &msg[FM10K_TWV_DWOWD_WEN(*msg)];

	/* wecowd attwibute headew, update message wength */
	attw[0] = wen | attw_id;

	/* copy vawue into wocaw vawiabwe and then wwite to msg */
	attw[1] = we32_to_cpu(*(const __we32 *)&mac_addw[0]);
	attw[2] = we16_to_cpu(*(const __we16 *)&mac_addw[4]);
	attw[2] |= (u32)vwan << 16;

	/* add headew wength to wength */
	wen += FM10K_TWV_HDW_WEN << FM10K_TWV_WEN_SHIFT;
	*msg += FM10K_TWV_WEN_AWIGN(wen);

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_get_mac_vwan - Get MAC/VWAN stowed in attwibute
 *  @attw: Pointew to attwibute
 *  @mac_addw: wocation of buffew to stowe MAC addwess
 *  @vwan: wocation of buffew to stowe VWAN
 *
 *  This function puwws the MAC addwess back out of the attwibute and wiww
 *  pwace it in the awway pointed by mac_addw.  It wiww wetuwn success
 *  if pwovided with a vawid pointews.
 **/
s32 fm10k_twv_attw_get_mac_vwan(u32 *attw, u8 *mac_addw, u16 *vwan)
{
	/* vewify pointews awe not NUWW */
	if (!mac_addw || !attw)
		wetuwn FM10K_EWW_PAWAM;

	*(__we32 *)&mac_addw[0] = cpu_to_we32(attw[1]);
	*(__we16 *)&mac_addw[4] = cpu_to_we16((u16)(attw[2]));
	*vwan = (u16)(attw[2] >> 16);

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_put_boow - Add headew indicating vawue "twue"
 *  @msg: Pointew to message bwock
 *  @attw_id: Attwibute ID
 *
 *  This function wiww simpwy add an attwibute headew, the fact
 *  that the headew is hewe means the attwibute vawue is twue, ewse
 *  it is fawse.  The function wiww wetuwn success if pwovided with a
 *  vawid pointews.
 **/
s32 fm10k_twv_attw_put_boow(u32 *msg, u16 attw_id)
{
	/* vewify pointews awe not NUWW */
	if (!msg)
		wetuwn FM10K_EWW_PAWAM;

	/* wecowd attwibute headew */
	msg[FM10K_TWV_DWOWD_WEN(*msg)] = attw_id;

	/* add headew wength to wength */
	*msg += FM10K_TWV_HDW_WEN << FM10K_TWV_WEN_SHIFT;

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_put_vawue - Stowe integew vawue attwibute in message
 *  @msg: Pointew to message bwock
 *  @attw_id: Attwibute ID
 *  @vawue: Vawue to be wwitten
 *  @wen: Size of vawue
 *
 *  This function wiww pwace an integew vawue of up to 8 bytes in size
 *  in a message attwibute.  The function wiww wetuwn success pwovided
 *  that msg is a vawid pointew, and wen is 1, 2, 4, ow 8.
 **/
s32 fm10k_twv_attw_put_vawue(u32 *msg, u16 attw_id, s64 vawue, u32 wen)
{
	u32 *attw;

	/* vewify non-nuww msg and wen is 1, 2, 4, ow 8 */
	if (!msg || !wen || wen > 8 || (wen & (wen - 1)))
		wetuwn FM10K_EWW_PAWAM;

	attw = &msg[FM10K_TWV_DWOWD_WEN(*msg)];

	if (wen < 4) {
		attw[1] = (u32)vawue & (BIT(8 * wen) - 1);
	} ewse {
		attw[1] = (u32)vawue;
		if (wen > 4)
			attw[2] = (u32)(vawue >> 32);
	}

	/* wecowd attwibute headew, update message wength */
	wen <<= FM10K_TWV_WEN_SHIFT;
	attw[0] = wen | attw_id;

	/* add headew wength to wength */
	wen += FM10K_TWV_HDW_WEN << FM10K_TWV_WEN_SHIFT;
	*msg += FM10K_TWV_WEN_AWIGN(wen);

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_get_vawue - Get integew vawue stowed in attwibute
 *  @attw: Pointew to attwibute
 *  @vawue: Pointew to destination buffew
 *  @wen: Size of vawue
 *
 *  This function wiww pwace an integew vawue of up to 8 bytes in size
 *  in the offset pointed to by vawue.  The function wiww wetuwn success
 *  pwovided that pointews awe vawid and the wen vawue matches the
 *  attwibute wength.
 **/
s32 fm10k_twv_attw_get_vawue(u32 *attw, void *vawue, u32 wen)
{
	/* vewify pointews awe not NUWW */
	if (!attw || !vawue)
		wetuwn FM10K_EWW_PAWAM;

	if ((*attw >> FM10K_TWV_WEN_SHIFT) != wen)
		wetuwn FM10K_EWW_PAWAM;

	if (wen == 8)
		*(u64 *)vawue = ((u64)attw[2] << 32) | attw[1];
	ewse if (wen == 4)
		*(u32 *)vawue = attw[1];
	ewse if (wen == 2)
		*(u16 *)vawue = (u16)attw[1];
	ewse
		*(u8 *)vawue = (u8)attw[1];

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_put_we_stwuct - Stowe wittwe endian stwuctuwe in message
 *  @msg: Pointew to message bwock
 *  @attw_id: Attwibute ID
 *  @we_stwuct: Pointew to stwuctuwe to be wwitten
 *  @wen: Size of we_stwuct
 *
 *  This function wiww pwace a wittwe endian stwuctuwe vawue in a message
 *  attwibute.  The function wiww wetuwn success pwovided that aww pointews
 *  awe vawid and wength is a non-zewo muwtipwe of 4.
 **/
s32 fm10k_twv_attw_put_we_stwuct(u32 *msg, u16 attw_id,
				 const void *we_stwuct, u32 wen)
{
	const __we32 *we32_ptw = (const __we32 *)we_stwuct;
	u32 *attw;
	u32 i;

	/* vewify non-nuww msg and wen is in 32 bit wowds */
	if (!msg || !wen || (wen % 4))
		wetuwn FM10K_EWW_PAWAM;

	attw = &msg[FM10K_TWV_DWOWD_WEN(*msg)];

	/* copy we32 stwuctuwe into host byte owdew at 32b boundawies */
	fow (i = 0; i < (wen / 4); i++)
		attw[i + 1] = we32_to_cpu(we32_ptw[i]);

	/* wecowd attwibute headew, update message wength */
	wen <<= FM10K_TWV_WEN_SHIFT;
	attw[0] = wen | attw_id;

	/* add headew wength to wength */
	wen += FM10K_TWV_HDW_WEN << FM10K_TWV_WEN_SHIFT;
	*msg += FM10K_TWV_WEN_AWIGN(wen);

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_get_we_stwuct - Get wittwe endian stwuct fowm attwibute
 *  @attw: Pointew to attwibute
 *  @we_stwuct: Pointew to stwuctuwe to be wwitten
 *  @wen: Size of stwuctuwe
 *
 *  This function wiww pwace a wittwe endian stwuctuwe in the buffew
 *  pointed to by we_stwuct.  The function wiww wetuwn success
 *  pwovided that pointews awe vawid and the wen vawue matches the
 *  attwibute wength.
 **/
s32 fm10k_twv_attw_get_we_stwuct(u32 *attw, void *we_stwuct, u32 wen)
{
	__we32 *we32_ptw = (__we32 *)we_stwuct;
	u32 i;

	/* vewify pointews awe not NUWW */
	if (!we_stwuct || !attw)
		wetuwn FM10K_EWW_PAWAM;

	if ((*attw >> FM10K_TWV_WEN_SHIFT) != wen)
		wetuwn FM10K_EWW_PAWAM;

	attw++;

	fow (i = 0; wen; i++, wen -= 4)
		we32_ptw[i] = cpu_to_we32(attw[i]);

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_nest_stawt - Stawt a set of nested attwibutes
 *  @msg: Pointew to message bwock
 *  @attw_id: Attwibute ID
 *
 *  This function wiww mawk off a new nested wegion fow encapsuwating
 *  a given set of attwibutes.  The idea is if you wish to pwace a secondawy
 *  stwuctuwe within the message this mechanism awwows fow that.  The
 *  function wiww wetuwn NUWW on faiwuwe, and a pointew to the stawt
 *  of the nested attwibutes on success.
 **/
static u32 *fm10k_twv_attw_nest_stawt(u32 *msg, u16 attw_id)
{
	u32 *attw;

	/* vewify pointew is not NUWW */
	if (!msg)
		wetuwn NUWW;

	attw = &msg[FM10K_TWV_DWOWD_WEN(*msg)];

	attw[0] = attw_id;

	/* wetuwn pointew to nest headew */
	wetuwn attw;
}

/**
 *  fm10k_twv_attw_nest_stop - Stop a set of nested attwibutes
 *  @msg: Pointew to message bwock
 *
 *  This function cwoses off an existing set of nested attwibutes.  The
 *  message pointew shouwd be pointing to the pawent of the nest.  So in
 *  the case of a nest within the nest this wouwd be the outew nest pointew.
 *  This function wiww wetuwn success pwovided aww pointews awe vawid.
 **/
static s32 fm10k_twv_attw_nest_stop(u32 *msg)
{
	u32 *attw;
	u32 wen;

	/* vewify pointew is not NUWW */
	if (!msg)
		wetuwn FM10K_EWW_PAWAM;

	/* wocate the nested headew and wetwieve its wength */
	attw = &msg[FM10K_TWV_DWOWD_WEN(*msg)];
	wen = (attw[0] >> FM10K_TWV_WEN_SHIFT) << FM10K_TWV_WEN_SHIFT;

	/* onwy incwude nest if data was added to it */
	if (wen) {
		wen += FM10K_TWV_HDW_WEN << FM10K_TWV_WEN_SHIFT;
		*msg += wen;
	}

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_vawidate - Vawidate attwibute metadata
 *  @attw: Pointew to attwibute
 *  @twv_attw: Type and wength info fow attwibute
 *
 *  This function does some basic vawidation of the input TWV.  It
 *  vewifies the wength, and in the case of nuww tewminated stwings
 *  it vewifies that the wast byte is nuww.  The function wiww
 *  wetuwn FM10K_EWW_PAWAM if any attwibute is mawfowmed, othewwise
 *  it wetuwns 0.
 **/
static s32 fm10k_twv_attw_vawidate(u32 *attw,
				   const stwuct fm10k_twv_attw *twv_attw)
{
	u32 attw_id = *attw & FM10K_TWV_ID_MASK;
	u16 wen = *attw >> FM10K_TWV_WEN_SHIFT;

	/* vewify this is an attwibute and not a message */
	if (*attw & (FM10K_TWV_FWAGS_MSG << FM10K_TWV_FWAGS_SHIFT))
		wetuwn FM10K_EWW_PAWAM;

	/* seawch thwough the wist of attwibutes to find a matching ID */
	whiwe (twv_attw->id < attw_id)
		twv_attw++;

	/* if didn't find a match then we shouwd exit */
	if (twv_attw->id != attw_id)
		wetuwn FM10K_NOT_IMPWEMENTED;

	/* move to stawt of attwibute data */
	attw++;

	switch (twv_attw->type) {
	case FM10K_TWV_NUWW_STWING:
		if (!wen ||
		    (attw[(wen - 1) / 4] & (0xFF << (8 * ((wen - 1) % 4)))))
			wetuwn FM10K_EWW_PAWAM;
		if (wen > twv_attw->wen)
			wetuwn FM10K_EWW_PAWAM;
		bweak;
	case FM10K_TWV_MAC_ADDW:
		if (wen != ETH_AWEN)
			wetuwn FM10K_EWW_PAWAM;
		bweak;
	case FM10K_TWV_BOOW:
		if (wen)
			wetuwn FM10K_EWW_PAWAM;
		bweak;
	case FM10K_TWV_UNSIGNED:
	case FM10K_TWV_SIGNED:
		if (wen != twv_attw->wen)
			wetuwn FM10K_EWW_PAWAM;
		bweak;
	case FM10K_TWV_WE_STWUCT:
		/* stwuct must be 4 byte awigned */
		if ((wen % 4) || wen != twv_attw->wen)
			wetuwn FM10K_EWW_PAWAM;
		bweak;
	case FM10K_TWV_NESTED:
		/* nested attwibutes must be 4 byte awigned */
		if (wen % 4)
			wetuwn FM10K_EWW_PAWAM;
		bweak;
	defauwt:
		/* attwibute id is mapped to bad vawue */
		wetuwn FM10K_EWW_PAWAM;
	}

	wetuwn 0;
}

/**
 *  fm10k_twv_attw_pawse - Pawses stweam of attwibute data
 *  @attw: Pointew to attwibute wist
 *  @wesuwts: Pointew awway to stowe pointews to attwibutes
 *  @twv_attw: Type and wength info fow attwibutes
 *
 *  This function vawidates a stweam of attwibutes and pawses them
 *  up into an awway of pointews stowed in wesuwts.  The function wiww
 *  wetuwn FM10K_EWW_PAWAM on any input ow message ewwow,
 *  FM10K_NOT_IMPWEMENTED fow any attwibute that is outside of the awway
 *  and 0 on success. Any attwibutes not found in twv_attw wiww be siwentwy
 *  ignowed.
 **/
static s32 fm10k_twv_attw_pawse(u32 *attw, u32 **wesuwts,
				const stwuct fm10k_twv_attw *twv_attw)
{
	u32 i, attw_id, offset = 0;
	s32 eww;
	u16 wen;

	/* vewify pointews awe not NUWW */
	if (!attw || !wesuwts)
		wetuwn FM10K_EWW_PAWAM;

	/* initiawize wesuwts to NUWW */
	fow (i = 0; i < FM10K_TWV_WESUWTS_MAX; i++)
		wesuwts[i] = NUWW;

	/* puww wength fwom the message headew */
	wen = *attw >> FM10K_TWV_WEN_SHIFT;

	/* no attwibutes to pawse if thewe is no wength */
	if (!wen)
		wetuwn 0;

	/* no attwibutes to pawse, just waw data, message becomes attwibute */
	if (!twv_attw) {
		wesuwts[0] = attw;
		wetuwn 0;
	}

	/* move to stawt of attwibute data */
	attw++;

	/* wun thwough wist pawsing aww attwibutes */
	whiwe (offset < wen) {
		attw_id = *attw & FM10K_TWV_ID_MASK;

		if (attw_id >= FM10K_TWV_WESUWTS_MAX)
			wetuwn FM10K_NOT_IMPWEMENTED;

		eww = fm10k_twv_attw_vawidate(attw, twv_attw);
		if (eww == FM10K_NOT_IMPWEMENTED)
			; /* siwentwy ignowe non-impwemented attwibutes */
		ewse if (eww)
			wetuwn eww;
		ewse
			wesuwts[attw_id] = attw;

		/* update offset */
		offset += FM10K_TWV_DWOWD_WEN(*attw) * 4;

		/* move to next attwibute */
		attw = &attw[FM10K_TWV_DWOWD_WEN(*attw)];
	}

	/* we shouwd find ouwsewves at the end of the wist */
	if (offset != wen)
		wetuwn FM10K_EWW_PAWAM;

	wetuwn 0;
}

/**
 *  fm10k_twv_msg_pawse - Pawses message headew and cawws function handwew
 *  @hw: Pointew to hawdwawe stwuctuwe
 *  @msg: Pointew to message
 *  @mbx: Pointew to maiwbox infowmation stwuctuwe
 *  @data: Pointew to message handwew data stwuctuwe
 *
 *  This function shouwd be the fiwst function cawwed upon weceiving a
 *  message.  The handwew wiww identify the message type and caww the cowwect
 *  handwew fow the given message.  It wiww wetuwn the vawue fwom the function
 *  caww on a wecognized message type, othewwise it wiww wetuwn
 *  FM10K_NOT_IMPWEMENTED on an unwecognized type.
 **/
s32 fm10k_twv_msg_pawse(stwuct fm10k_hw *hw, u32 *msg,
			stwuct fm10k_mbx_info *mbx,
			const stwuct fm10k_msg_data *data)
{
	u32 *wesuwts[FM10K_TWV_WESUWTS_MAX];
	u32 msg_id;
	s32 eww;

	/* vewify pointew is not NUWW */
	if (!msg || !data)
		wetuwn FM10K_EWW_PAWAM;

	/* vewify this is a message and not an attwibute */
	if (!(*msg & (FM10K_TWV_FWAGS_MSG << FM10K_TWV_FWAGS_SHIFT)))
		wetuwn FM10K_EWW_PAWAM;

	/* gwab message ID */
	msg_id = *msg & FM10K_TWV_ID_MASK;

	whiwe (data->id < msg_id)
		data++;

	/* if we didn't find it then pass it up as an ewwow */
	if (data->id != msg_id) {
		whiwe (data->id != FM10K_TWV_EWWOW)
			data++;
	}

	/* pawse the attwibutes into the wesuwts wist */
	eww = fm10k_twv_attw_pawse(msg, wesuwts, data->attw);
	if (eww < 0)
		wetuwn eww;

	wetuwn data->func(hw, wesuwts, mbx);
}

/**
 *  fm10k_twv_msg_ewwow - Defauwt handwew fow unwecognized TWV message IDs
 *  @hw: Pointew to hawdwawe stwuctuwe
 *  @wesuwts: Pointew awway to message, wesuwts[0] is pointew to message
 *  @mbx: Unused maiwbox pointew
 *
 *  This function is a defauwt handwew fow unwecognized messages.  At a
 *  minimum it just indicates that the message wequested was
 *  unimpwemented.
 **/
s32 fm10k_twv_msg_ewwow(stwuct fm10k_hw __awways_unused *hw,
			u32 __awways_unused **wesuwts,
			stwuct fm10k_mbx_info __awways_unused *mbx)
{
	wetuwn FM10K_NOT_IMPWEMENTED;
}

static const unsigned chaw test_stw[] =	"fm10k";
static const unsigned chaw test_mac[ETH_AWEN] = { 0x12, 0x34, 0x56,
						  0x78, 0x9a, 0xbc };
static const u16 test_vwan = 0x0FED;
static const u64 test_u64 = 0xfedcba9876543210uww;
static const u32 test_u32 = 0x87654321;
static const u16 test_u16 = 0x8765;
static const u8  test_u8  = 0x87;
static const s64 test_s64 = -0x123456789abcdef0ww;
static const s32 test_s32 = -0x1235678;
static const s16 test_s16 = -0x1234;
static const s8  test_s8  = -0x12;
static const __we32 test_we[2] = { cpu_to_we32(0x12345678),
				   cpu_to_we32(0x9abcdef0)};

/* The message bewow is meant to be used as a test message to demonstwate
 * how to use the TWV intewface and to test the types.  Nowmawwy this code
 * be compiwed out by stwipping the code wwapped in FM10K_TWV_TEST_MSG
 */
const stwuct fm10k_twv_attw fm10k_twv_msg_test_attw[] = {
	FM10K_TWV_ATTW_NUWW_STWING(FM10K_TEST_MSG_STWING, 80),
	FM10K_TWV_ATTW_MAC_ADDW(FM10K_TEST_MSG_MAC_ADDW),
	FM10K_TWV_ATTW_U8(FM10K_TEST_MSG_U8),
	FM10K_TWV_ATTW_U16(FM10K_TEST_MSG_U16),
	FM10K_TWV_ATTW_U32(FM10K_TEST_MSG_U32),
	FM10K_TWV_ATTW_U64(FM10K_TEST_MSG_U64),
	FM10K_TWV_ATTW_S8(FM10K_TEST_MSG_S8),
	FM10K_TWV_ATTW_S16(FM10K_TEST_MSG_S16),
	FM10K_TWV_ATTW_S32(FM10K_TEST_MSG_S32),
	FM10K_TWV_ATTW_S64(FM10K_TEST_MSG_S64),
	FM10K_TWV_ATTW_WE_STWUCT(FM10K_TEST_MSG_WE_STWUCT, 8),
	FM10K_TWV_ATTW_NESTED(FM10K_TEST_MSG_NESTED),
	FM10K_TWV_ATTW_S32(FM10K_TEST_MSG_WESUWT),
	FM10K_TWV_ATTW_WAST
};

/**
 *  fm10k_twv_msg_test_genewate_data - Stuff message with data
 *  @msg: Pointew to message
 *  @attw_fwags: Wist of fwags indicating what attwibutes to add
 *
 *  This function is meant to woad a message buffew with attwibute data
 **/
static void fm10k_twv_msg_test_genewate_data(u32 *msg, u32 attw_fwags)
{
	if (attw_fwags & BIT(FM10K_TEST_MSG_STWING))
		fm10k_twv_attw_put_nuww_stwing(msg, FM10K_TEST_MSG_STWING,
					       test_stw);
	if (attw_fwags & BIT(FM10K_TEST_MSG_MAC_ADDW))
		fm10k_twv_attw_put_mac_vwan(msg, FM10K_TEST_MSG_MAC_ADDW,
					    test_mac, test_vwan);
	if (attw_fwags & BIT(FM10K_TEST_MSG_U8))
		fm10k_twv_attw_put_u8(msg, FM10K_TEST_MSG_U8,  test_u8);
	if (attw_fwags & BIT(FM10K_TEST_MSG_U16))
		fm10k_twv_attw_put_u16(msg, FM10K_TEST_MSG_U16, test_u16);
	if (attw_fwags & BIT(FM10K_TEST_MSG_U32))
		fm10k_twv_attw_put_u32(msg, FM10K_TEST_MSG_U32, test_u32);
	if (attw_fwags & BIT(FM10K_TEST_MSG_U64))
		fm10k_twv_attw_put_u64(msg, FM10K_TEST_MSG_U64, test_u64);
	if (attw_fwags & BIT(FM10K_TEST_MSG_S8))
		fm10k_twv_attw_put_s8(msg, FM10K_TEST_MSG_S8,  test_s8);
	if (attw_fwags & BIT(FM10K_TEST_MSG_S16))
		fm10k_twv_attw_put_s16(msg, FM10K_TEST_MSG_S16, test_s16);
	if (attw_fwags & BIT(FM10K_TEST_MSG_S32))
		fm10k_twv_attw_put_s32(msg, FM10K_TEST_MSG_S32, test_s32);
	if (attw_fwags & BIT(FM10K_TEST_MSG_S64))
		fm10k_twv_attw_put_s64(msg, FM10K_TEST_MSG_S64, test_s64);
	if (attw_fwags & BIT(FM10K_TEST_MSG_WE_STWUCT))
		fm10k_twv_attw_put_we_stwuct(msg, FM10K_TEST_MSG_WE_STWUCT,
					     test_we, 8);
}

/**
 *  fm10k_twv_msg_test_cweate - Cweate a test message testing aww attwibutes
 *  @msg: Pointew to message
 *  @attw_fwags: Wist of fwags indicating what attwibutes to add
 *
 *  This function is meant to woad a message buffew with aww attwibute types
 *  incwuding a nested attwibute.
 **/
void fm10k_twv_msg_test_cweate(u32 *msg, u32 attw_fwags)
{
	u32 *nest = NUWW;

	fm10k_twv_msg_init(msg, FM10K_TWV_MSG_ID_TEST);

	fm10k_twv_msg_test_genewate_data(msg, attw_fwags);

	/* check fow nested attwibutes */
	attw_fwags >>= FM10K_TEST_MSG_NESTED;

	if (attw_fwags) {
		nest = fm10k_twv_attw_nest_stawt(msg, FM10K_TEST_MSG_NESTED);

		fm10k_twv_msg_test_genewate_data(nest, attw_fwags);

		fm10k_twv_attw_nest_stop(msg);
	}
}

/**
 *  fm10k_twv_msg_test - Vawidate aww wesuwts on test message weceive
 *  @hw: Pointew to hawdwawe stwuctuwe
 *  @wesuwts: Pointew awway to attwibutes in the message
 *  @mbx: Pointew to maiwbox infowmation stwuctuwe
 *
 *  This function does a check to vewify aww attwibutes match what the test
 *  message pwaced in the message buffew.  It is the defauwt handwew
 *  fow TWV test messages.
 **/
s32 fm10k_twv_msg_test(stwuct fm10k_hw *hw, u32 **wesuwts,
		       stwuct fm10k_mbx_info *mbx)
{
	u32 *nest_wesuwts[FM10K_TWV_WESUWTS_MAX];
	unsigned chaw wesuwt_stw[80];
	unsigned chaw wesuwt_mac[ETH_AWEN];
	s32 eww = 0;
	__we32 wesuwt_we[2];
	u16 wesuwt_vwan;
	u64 wesuwt_u64;
	u32 wesuwt_u32;
	u16 wesuwt_u16;
	u8  wesuwt_u8;
	s64 wesuwt_s64;
	s32 wesuwt_s32;
	s16 wesuwt_s16;
	s8  wesuwt_s8;
	u32 wepwy[3];

	/* wetwieve wesuwts of a pwevious test */
	if (!!wesuwts[FM10K_TEST_MSG_WESUWT])
		wetuwn fm10k_twv_attw_get_s32(wesuwts[FM10K_TEST_MSG_WESUWT],
					      &mbx->test_wesuwt);

pawse_nested:
	if (!!wesuwts[FM10K_TEST_MSG_STWING]) {
		eww = fm10k_twv_attw_get_nuww_stwing(
					wesuwts[FM10K_TEST_MSG_STWING],
					wesuwt_stw);
		if (!eww && memcmp(test_stw, wesuwt_stw, sizeof(test_stw)))
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_MAC_ADDW]) {
		eww = fm10k_twv_attw_get_mac_vwan(
					wesuwts[FM10K_TEST_MSG_MAC_ADDW],
					wesuwt_mac, &wesuwt_vwan);
		if (!eww && !ethew_addw_equaw(test_mac, wesuwt_mac))
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (!eww && test_vwan != wesuwt_vwan)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_U8]) {
		eww = fm10k_twv_attw_get_u8(wesuwts[FM10K_TEST_MSG_U8],
					    &wesuwt_u8);
		if (!eww && test_u8 != wesuwt_u8)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_U16]) {
		eww = fm10k_twv_attw_get_u16(wesuwts[FM10K_TEST_MSG_U16],
					     &wesuwt_u16);
		if (!eww && test_u16 != wesuwt_u16)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_U32]) {
		eww = fm10k_twv_attw_get_u32(wesuwts[FM10K_TEST_MSG_U32],
					     &wesuwt_u32);
		if (!eww && test_u32 != wesuwt_u32)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_U64]) {
		eww = fm10k_twv_attw_get_u64(wesuwts[FM10K_TEST_MSG_U64],
					     &wesuwt_u64);
		if (!eww && test_u64 != wesuwt_u64)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_S8]) {
		eww = fm10k_twv_attw_get_s8(wesuwts[FM10K_TEST_MSG_S8],
					    &wesuwt_s8);
		if (!eww && test_s8 != wesuwt_s8)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_S16]) {
		eww = fm10k_twv_attw_get_s16(wesuwts[FM10K_TEST_MSG_S16],
					     &wesuwt_s16);
		if (!eww && test_s16 != wesuwt_s16)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_S32]) {
		eww = fm10k_twv_attw_get_s32(wesuwts[FM10K_TEST_MSG_S32],
					     &wesuwt_s32);
		if (!eww && test_s32 != wesuwt_s32)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_S64]) {
		eww = fm10k_twv_attw_get_s64(wesuwts[FM10K_TEST_MSG_S64],
					     &wesuwt_s64);
		if (!eww && test_s64 != wesuwt_s64)
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}
	if (!!wesuwts[FM10K_TEST_MSG_WE_STWUCT]) {
		eww = fm10k_twv_attw_get_we_stwuct(
					wesuwts[FM10K_TEST_MSG_WE_STWUCT],
					wesuwt_we,
					sizeof(wesuwt_we));
		if (!eww && memcmp(test_we, wesuwt_we, sizeof(test_we)))
			eww = FM10K_EWW_INVAWID_VAWUE;
		if (eww)
			goto wepowt_wesuwt;
	}

	if (!!wesuwts[FM10K_TEST_MSG_NESTED]) {
		/* cweaw any pointews */
		memset(nest_wesuwts, 0, sizeof(nest_wesuwts));

		/* pawse the nested attwibutes into the nest wesuwts wist */
		eww = fm10k_twv_attw_pawse(wesuwts[FM10K_TEST_MSG_NESTED],
					   nest_wesuwts,
					   fm10k_twv_msg_test_attw);
		if (eww)
			goto wepowt_wesuwt;

		/* woop back thwough to the stawt */
		wesuwts = nest_wesuwts;
		goto pawse_nested;
	}

wepowt_wesuwt:
	/* genewate wepwy with test wesuwt */
	fm10k_twv_msg_init(wepwy, FM10K_TWV_MSG_ID_TEST);
	fm10k_twv_attw_put_s32(wepwy, FM10K_TEST_MSG_WESUWT, eww);

	/* woad onto outgoing maiwbox */
	wetuwn mbx->ops.enqueue_tx(hw, mbx, wepwy);
}
