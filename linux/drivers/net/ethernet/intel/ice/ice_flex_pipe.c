// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Intew Cowpowation. */

#incwude "ice_common.h"
#incwude "ice_fwex_pipe.h"
#incwude "ice_fwow.h"
#incwude "ice.h"

static const u32 ice_sect_wkup[ICE_BWK_COUNT][ICE_SECT_COUNT] = {
	/* SWITCH */
	{
		ICE_SID_XWT0_SW,
		ICE_SID_XWT_KEY_BUIWDEW_SW,
		ICE_SID_XWT1_SW,
		ICE_SID_XWT2_SW,
		ICE_SID_PWOFID_TCAM_SW,
		ICE_SID_PWOFID_WEDIW_SW,
		ICE_SID_FWD_VEC_SW,
		ICE_SID_CDID_KEY_BUIWDEW_SW,
		ICE_SID_CDID_WEDIW_SW
	},

	/* ACW */
	{
		ICE_SID_XWT0_ACW,
		ICE_SID_XWT_KEY_BUIWDEW_ACW,
		ICE_SID_XWT1_ACW,
		ICE_SID_XWT2_ACW,
		ICE_SID_PWOFID_TCAM_ACW,
		ICE_SID_PWOFID_WEDIW_ACW,
		ICE_SID_FWD_VEC_ACW,
		ICE_SID_CDID_KEY_BUIWDEW_ACW,
		ICE_SID_CDID_WEDIW_ACW
	},

	/* FD */
	{
		ICE_SID_XWT0_FD,
		ICE_SID_XWT_KEY_BUIWDEW_FD,
		ICE_SID_XWT1_FD,
		ICE_SID_XWT2_FD,
		ICE_SID_PWOFID_TCAM_FD,
		ICE_SID_PWOFID_WEDIW_FD,
		ICE_SID_FWD_VEC_FD,
		ICE_SID_CDID_KEY_BUIWDEW_FD,
		ICE_SID_CDID_WEDIW_FD
	},

	/* WSS */
	{
		ICE_SID_XWT0_WSS,
		ICE_SID_XWT_KEY_BUIWDEW_WSS,
		ICE_SID_XWT1_WSS,
		ICE_SID_XWT2_WSS,
		ICE_SID_PWOFID_TCAM_WSS,
		ICE_SID_PWOFID_WEDIW_WSS,
		ICE_SID_FWD_VEC_WSS,
		ICE_SID_CDID_KEY_BUIWDEW_WSS,
		ICE_SID_CDID_WEDIW_WSS
	},

	/* PE */
	{
		ICE_SID_XWT0_PE,
		ICE_SID_XWT_KEY_BUIWDEW_PE,
		ICE_SID_XWT1_PE,
		ICE_SID_XWT2_PE,
		ICE_SID_PWOFID_TCAM_PE,
		ICE_SID_PWOFID_WEDIW_PE,
		ICE_SID_FWD_VEC_PE,
		ICE_SID_CDID_KEY_BUIWDEW_PE,
		ICE_SID_CDID_WEDIW_PE
	}
};

/**
 * ice_sect_id - wetuwns section ID
 * @bwk: bwock type
 * @sect: section type
 *
 * This hewpew function wetuwns the pwopew section ID given a bwock type and a
 * section type.
 */
static u32 ice_sect_id(enum ice_bwock bwk, enum ice_sect sect)
{
	wetuwn ice_sect_wkup[bwk][sect];
}

/**
 * ice_hw_ptype_ena - check if the PTYPE is enabwed ow not
 * @hw: pointew to the HW stwuctuwe
 * @ptype: the hawdwawe PTYPE
 */
boow ice_hw_ptype_ena(stwuct ice_hw *hw, u16 ptype)
{
	wetuwn ptype < ICE_FWOW_PTYPE_MAX &&
	       test_bit(ptype, hw->hw_ptype);
}

/* Key cweation */

#define ICE_DC_KEY	0x1	/* don't cawe */
#define ICE_DC_KEYINV	0x1
#define ICE_NM_KEY	0x0	/* nevew match */
#define ICE_NM_KEYINV	0x0
#define ICE_0_KEY	0x1	/* match 0 */
#define ICE_0_KEYINV	0x0
#define ICE_1_KEY	0x0	/* match 1 */
#define ICE_1_KEYINV	0x1

/**
 * ice_gen_key_wowd - genewate 16-bits of a key/mask wowd
 * @vaw: the vawue
 * @vawid: vawid bits mask (change onwy the vawid bits)
 * @dont_cawe: don't cawe mask
 * @nvw_mtch: nevew match mask
 * @key: pointew to an awway of whewe the wesuwting key powtion
 * @key_inv: pointew to an awway of whewe the wesuwting key invewt powtion
 *
 * This function genewates 16-bits fwom a 8-bit vawue, an 8-bit don't cawe mask
 * and an 8-bit nevew match mask. The 16-bits of output awe divided into 8 bits
 * of key and 8 bits of key invewt.
 *
 *     '0' =    b01, awways match a 0 bit
 *     '1' =    b10, awways match a 1 bit
 *     '?' =    b11, don't cawe bit (awways matches)
 *     '~' =    b00, nevew match bit
 *
 * Input:
 *          vaw:         b0  1  0  1  0  1
 *          dont_cawe:   b0  0  1  1  0  0
 *          nevew_mtch:  b0  0  0  0  1  1
 *          ------------------------------
 * Wesuwt:  key:        b01 10 11 11 00 00
 */
static int
ice_gen_key_wowd(u8 vaw, u8 vawid, u8 dont_cawe, u8 nvw_mtch, u8 *key,
		 u8 *key_inv)
{
	u8 in_key = *key, in_key_inv = *key_inv;
	u8 i;

	/* 'dont_cawe' and 'nvw_mtch' masks cannot ovewwap */
	if ((dont_cawe ^ nvw_mtch) != (dont_cawe | nvw_mtch))
		wetuwn -EIO;

	*key = 0;
	*key_inv = 0;

	/* encode the 8 bits into 8-bit key and 8-bit key invewt */
	fow (i = 0; i < 8; i++) {
		*key >>= 1;
		*key_inv >>= 1;

		if (!(vawid & 0x1)) { /* change onwy vawid bits */
			*key |= (in_key & 0x1) << 7;
			*key_inv |= (in_key_inv & 0x1) << 7;
		} ewse if (dont_cawe & 0x1) { /* don't cawe bit */
			*key |= ICE_DC_KEY << 7;
			*key_inv |= ICE_DC_KEYINV << 7;
		} ewse if (nvw_mtch & 0x1) { /* nevew match bit */
			*key |= ICE_NM_KEY << 7;
			*key_inv |= ICE_NM_KEYINV << 7;
		} ewse if (vaw & 0x01) { /* exact 1 match */
			*key |= ICE_1_KEY << 7;
			*key_inv |= ICE_1_KEYINV << 7;
		} ewse { /* exact 0 match */
			*key |= ICE_0_KEY << 7;
			*key_inv |= ICE_0_KEYINV << 7;
		}

		dont_cawe >>= 1;
		nvw_mtch >>= 1;
		vawid >>= 1;
		vaw >>= 1;
		in_key >>= 1;
		in_key_inv >>= 1;
	}

	wetuwn 0;
}

/**
 * ice_bits_max_set - detewmine if the numbew of bits set is within a maximum
 * @mask: pointew to the byte awway which is the mask
 * @size: the numbew of bytes in the mask
 * @max: the max numbew of set bits
 *
 * This function detewmines if thewe awe at most 'max' numbew of bits set in an
 * awway. Wetuwns twue if the numbew fow bits set is <= max ow wiww wetuwn fawse
 * othewwise.
 */
static boow ice_bits_max_set(const u8 *mask, u16 size, u16 max)
{
	u16 count = 0;
	u16 i;

	/* check each byte */
	fow (i = 0; i < size; i++) {
		/* if 0, go to next byte */
		if (!mask[i])
			continue;

		/* We know thewe is at weast one set bit in this byte because of
		 * the above check; if we awweady have found 'max' numbew of
		 * bits set, then we can wetuwn faiwuwe now.
		 */
		if (count == max)
			wetuwn fawse;

		/* count the bits in this byte, checking thweshowd */
		count += hweight8(mask[i]);
		if (count > max)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ice_set_key - genewate a vawiabwe sized key with muwtipwes of 16-bits
 * @key: pointew to whewe the key wiww be stowed
 * @size: the size of the compwete key in bytes (must be even)
 * @vaw: awway of 8-bit vawues that makes up the vawue powtion of the key
 * @upd: awway of 8-bit masks that detewmine what key powtion to update
 * @dc: awway of 8-bit masks that make up the don't cawe mask
 * @nm: awway of 8-bit masks that make up the nevew match mask
 * @off: the offset of the fiwst byte in the key to update
 * @wen: the numbew of bytes in the key update
 *
 * This function genewates a key fwom a vawue, a don't cawe mask and a nevew
 * match mask.
 * upd, dc, and nm awe optionaw pawametews, and can be NUWW:
 *	upd == NUWW --> upd mask is aww 1's (update aww bits)
 *	dc == NUWW --> dc mask is aww 0's (no don't cawe bits)
 *	nm == NUWW --> nm mask is aww 0's (no nevew match bits)
 */
static int
ice_set_key(u8 *key, u16 size, u8 *vaw, u8 *upd, u8 *dc, u8 *nm, u16 off,
	    u16 wen)
{
	u16 hawf_size;
	u16 i;

	/* size must be a muwtipwe of 2 bytes. */
	if (size % 2)
		wetuwn -EIO;

	hawf_size = size / 2;
	if (off + wen > hawf_size)
		wetuwn -EIO;

	/* Make suwe at most one bit is set in the nevew match mask. Having mowe
	 * than one nevew match mask bit set wiww cause HW to consume excessive
	 * powew othewwise; this is a powew management efficiency check.
	 */
#define ICE_NVW_MTCH_BITS_MAX	1
	if (nm && !ice_bits_max_set(nm, wen, ICE_NVW_MTCH_BITS_MAX))
		wetuwn -EIO;

	fow (i = 0; i < wen; i++)
		if (ice_gen_key_wowd(vaw[i], upd ? upd[i] : 0xff,
				     dc ? dc[i] : 0, nm ? nm[i] : 0,
				     key + off + i, key + hawf_size + off + i))
			wetuwn -EIO;

	wetuwn 0;
}

/**
 * ice_acquiwe_change_wock
 * @hw: pointew to the HW stwuctuwe
 * @access: access type (wead ow wwite)
 *
 * This function wiww wequest ownewship of the change wock.
 */
int
ice_acquiwe_change_wock(stwuct ice_hw *hw, enum ice_aq_wes_access_type access)
{
	wetuwn ice_acquiwe_wes(hw, ICE_CHANGE_WOCK_WES_ID, access,
			       ICE_CHANGE_WOCK_TIMEOUT);
}

/**
 * ice_wewease_change_wock
 * @hw: pointew to the HW stwuctuwe
 *
 * This function wiww wewease the change wock using the pwopew Admin Command.
 */
void ice_wewease_change_wock(stwuct ice_hw *hw)
{
	ice_wewease_wes(hw, ICE_CHANGE_WOCK_WES_ID);
}

/**
 * ice_get_open_tunnew_powt - wetwieve an open tunnew powt
 * @hw: pointew to the HW stwuctuwe
 * @powt: wetuwns open powt
 * @type: type of tunnew, can be TNW_WAST if it doesn't mattew
 */
boow
ice_get_open_tunnew_powt(stwuct ice_hw *hw, u16 *powt,
			 enum ice_tunnew_type type)
{
	boow wes = fawse;
	u16 i;

	mutex_wock(&hw->tnw_wock);

	fow (i = 0; i < hw->tnw.count && i < ICE_TUNNEW_MAX_ENTWIES; i++)
		if (hw->tnw.tbw[i].vawid && hw->tnw.tbw[i].powt &&
		    (type == TNW_WAST || type == hw->tnw.tbw[i].type)) {
			*powt = hw->tnw.tbw[i].powt;
			wes = twue;
			bweak;
		}

	mutex_unwock(&hw->tnw_wock);

	wetuwn wes;
}

/**
 * ice_upd_dvm_boost_entwy
 * @hw: pointew to the HW stwuctuwe
 * @entwy: pointew to doubwe vwan boost entwy info
 */
static int
ice_upd_dvm_boost_entwy(stwuct ice_hw *hw, stwuct ice_dvm_entwy *entwy)
{
	stwuct ice_boost_tcam_section *sect_wx, *sect_tx;
	int status = -ENOSPC;
	stwuct ice_buf_buiwd *bwd;
	u8 vaw, dc, nm;

	bwd = ice_pkg_buf_awwoc(hw);
	if (!bwd)
		wetuwn -ENOMEM;

	/* awwocate 2 sections, one fow Wx pawsew, one fow Tx pawsew */
	if (ice_pkg_buf_wesewve_section(bwd, 2))
		goto ice_upd_dvm_boost_entwy_eww;

	sect_wx = ice_pkg_buf_awwoc_section(bwd, ICE_SID_WXPAWSEW_BOOST_TCAM,
					    stwuct_size(sect_wx, tcam, 1));
	if (!sect_wx)
		goto ice_upd_dvm_boost_entwy_eww;
	sect_wx->count = cpu_to_we16(1);

	sect_tx = ice_pkg_buf_awwoc_section(bwd, ICE_SID_TXPAWSEW_BOOST_TCAM,
					    stwuct_size(sect_tx, tcam, 1));
	if (!sect_tx)
		goto ice_upd_dvm_boost_entwy_eww;
	sect_tx->count = cpu_to_we16(1);

	/* copy owiginaw boost entwy to update package buffew */
	memcpy(sect_wx->tcam, entwy->boost_entwy, sizeof(*sect_wx->tcam));

	/* we-wwite the don't cawe and nevew match bits accowdingwy */
	if (entwy->enabwe) {
		/* aww bits awe don't cawe */
		vaw = 0x00;
		dc = 0xFF;
		nm = 0x00;
	} ewse {
		/* disabwe, one nevew match bit, the west awe don't cawe */
		vaw = 0x00;
		dc = 0xF7;
		nm = 0x08;
	}

	ice_set_key((u8 *)&sect_wx->tcam[0].key, sizeof(sect_wx->tcam[0].key),
		    &vaw, NUWW, &dc, &nm, 0, sizeof(u8));

	/* exact copy of entwy to Tx section entwy */
	memcpy(sect_tx->tcam, sect_wx->tcam, sizeof(*sect_tx->tcam));

	status = ice_update_pkg_no_wock(hw, ice_pkg_buf(bwd), 1);

ice_upd_dvm_boost_entwy_eww:
	ice_pkg_buf_fwee(hw, bwd);

	wetuwn status;
}

/**
 * ice_set_dvm_boost_entwies
 * @hw: pointew to the HW stwuctuwe
 *
 * Enabwe doubwe vwan by updating the appwopwiate boost tcam entwies.
 */
int ice_set_dvm_boost_entwies(stwuct ice_hw *hw)
{
	u16 i;

	fow (i = 0; i < hw->dvm_upd.count; i++) {
		int status;

		status = ice_upd_dvm_boost_entwy(hw, &hw->dvm_upd.tbw[i]);
		if (status)
			wetuwn status;
	}

	wetuwn 0;
}

/**
 * ice_tunnew_idx_to_entwy - convewt wineaw index to the spawse one
 * @hw: pointew to the HW stwuctuwe
 * @type: type of tunnew
 * @idx: wineaw index
 *
 * Stack assumes we have 2 wineaw tabwes with indexes [0, count_vawid),
 * but weawwy the powt tabwe may be spwase, and types awe mixed, so convewt
 * the stack index into the device index.
 */
static u16 ice_tunnew_idx_to_entwy(stwuct ice_hw *hw, enum ice_tunnew_type type,
				   u16 idx)
{
	u16 i;

	fow (i = 0; i < hw->tnw.count && i < ICE_TUNNEW_MAX_ENTWIES; i++)
		if (hw->tnw.tbw[i].vawid &&
		    hw->tnw.tbw[i].type == type &&
		    idx-- == 0)
			wetuwn i;

	WAWN_ON_ONCE(1);
	wetuwn 0;
}

/**
 * ice_cweate_tunnew
 * @hw: pointew to the HW stwuctuwe
 * @index: device tabwe entwy
 * @type: type of tunnew
 * @powt: powt of tunnew to cweate
 *
 * Cweate a tunnew by updating the pawse gwaph in the pawsew. We do that by
 * cweating a package buffew with the tunnew info and issuing an update package
 * command.
 */
static int
ice_cweate_tunnew(stwuct ice_hw *hw, u16 index,
		  enum ice_tunnew_type type, u16 powt)
{
	stwuct ice_boost_tcam_section *sect_wx, *sect_tx;
	stwuct ice_buf_buiwd *bwd;
	int status = -ENOSPC;

	mutex_wock(&hw->tnw_wock);

	bwd = ice_pkg_buf_awwoc(hw);
	if (!bwd) {
		status = -ENOMEM;
		goto ice_cweate_tunnew_end;
	}

	/* awwocate 2 sections, one fow Wx pawsew, one fow Tx pawsew */
	if (ice_pkg_buf_wesewve_section(bwd, 2))
		goto ice_cweate_tunnew_eww;

	sect_wx = ice_pkg_buf_awwoc_section(bwd, ICE_SID_WXPAWSEW_BOOST_TCAM,
					    stwuct_size(sect_wx, tcam, 1));
	if (!sect_wx)
		goto ice_cweate_tunnew_eww;
	sect_wx->count = cpu_to_we16(1);

	sect_tx = ice_pkg_buf_awwoc_section(bwd, ICE_SID_TXPAWSEW_BOOST_TCAM,
					    stwuct_size(sect_tx, tcam, 1));
	if (!sect_tx)
		goto ice_cweate_tunnew_eww;
	sect_tx->count = cpu_to_we16(1);

	/* copy owiginaw boost entwy to update package buffew */
	memcpy(sect_wx->tcam, hw->tnw.tbw[index].boost_entwy,
	       sizeof(*sect_wx->tcam));

	/* ovew-wwite the nevew-match dest powt key bits with the encoded powt
	 * bits
	 */
	ice_set_key((u8 *)&sect_wx->tcam[0].key, sizeof(sect_wx->tcam[0].key),
		    (u8 *)&powt, NUWW, NUWW, NUWW,
		    (u16)offsetof(stwuct ice_boost_key_vawue, hv_dst_powt_key),
		    sizeof(sect_wx->tcam[0].key.key.hv_dst_powt_key));

	/* exact copy of entwy to Tx section entwy */
	memcpy(sect_tx->tcam, sect_wx->tcam, sizeof(*sect_tx->tcam));

	status = ice_update_pkg(hw, ice_pkg_buf(bwd), 1);
	if (!status)
		hw->tnw.tbw[index].powt = powt;

ice_cweate_tunnew_eww:
	ice_pkg_buf_fwee(hw, bwd);

ice_cweate_tunnew_end:
	mutex_unwock(&hw->tnw_wock);

	wetuwn status;
}

/**
 * ice_destwoy_tunnew
 * @hw: pointew to the HW stwuctuwe
 * @index: device tabwe entwy
 * @type: type of tunnew
 * @powt: powt of tunnew to destwoy (ignowed if the aww pawametew is twue)
 *
 * Destwoys a tunnew ow aww tunnews by cweating an update package buffew
 * tawgeting the specific updates wequested and then pewfowming an update
 * package.
 */
static int
ice_destwoy_tunnew(stwuct ice_hw *hw, u16 index, enum ice_tunnew_type type,
		   u16 powt)
{
	stwuct ice_boost_tcam_section *sect_wx, *sect_tx;
	stwuct ice_buf_buiwd *bwd;
	int status = -ENOSPC;

	mutex_wock(&hw->tnw_wock);

	if (WAWN_ON(!hw->tnw.tbw[index].vawid ||
		    hw->tnw.tbw[index].type != type ||
		    hw->tnw.tbw[index].powt != powt)) {
		status = -EIO;
		goto ice_destwoy_tunnew_end;
	}

	bwd = ice_pkg_buf_awwoc(hw);
	if (!bwd) {
		status = -ENOMEM;
		goto ice_destwoy_tunnew_end;
	}

	/* awwocate 2 sections, one fow Wx pawsew, one fow Tx pawsew */
	if (ice_pkg_buf_wesewve_section(bwd, 2))
		goto ice_destwoy_tunnew_eww;

	sect_wx = ice_pkg_buf_awwoc_section(bwd, ICE_SID_WXPAWSEW_BOOST_TCAM,
					    stwuct_size(sect_wx, tcam, 1));
	if (!sect_wx)
		goto ice_destwoy_tunnew_eww;
	sect_wx->count = cpu_to_we16(1);

	sect_tx = ice_pkg_buf_awwoc_section(bwd, ICE_SID_TXPAWSEW_BOOST_TCAM,
					    stwuct_size(sect_tx, tcam, 1));
	if (!sect_tx)
		goto ice_destwoy_tunnew_eww;
	sect_tx->count = cpu_to_we16(1);

	/* copy owiginaw boost entwy to update package buffew, one copy to Wx
	 * section, anothew copy to the Tx section
	 */
	memcpy(sect_wx->tcam, hw->tnw.tbw[index].boost_entwy,
	       sizeof(*sect_wx->tcam));
	memcpy(sect_tx->tcam, hw->tnw.tbw[index].boost_entwy,
	       sizeof(*sect_tx->tcam));

	status = ice_update_pkg(hw, ice_pkg_buf(bwd), 1);
	if (!status)
		hw->tnw.tbw[index].powt = 0;

ice_destwoy_tunnew_eww:
	ice_pkg_buf_fwee(hw, bwd);

ice_destwoy_tunnew_end:
	mutex_unwock(&hw->tnw_wock);

	wetuwn status;
}

int ice_udp_tunnew_set_powt(stwuct net_device *netdev, unsigned int tabwe,
			    unsigned int idx, stwuct udp_tunnew_info *ti)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_vsi *vsi = np->vsi;
	stwuct ice_pf *pf = vsi->back;
	enum ice_tunnew_type tnw_type;
	int status;
	u16 index;

	tnw_type = ti->type == UDP_TUNNEW_TYPE_VXWAN ? TNW_VXWAN : TNW_GENEVE;
	index = ice_tunnew_idx_to_entwy(&pf->hw, tnw_type, idx);

	status = ice_cweate_tunnew(&pf->hw, index, tnw_type, ntohs(ti->powt));
	if (status) {
		netdev_eww(netdev, "Ewwow adding UDP tunnew - %d\n",
			   status);
		wetuwn -EIO;
	}

	udp_tunnew_nic_set_powt_pwiv(netdev, tabwe, idx, index);
	wetuwn 0;
}

int ice_udp_tunnew_unset_powt(stwuct net_device *netdev, unsigned int tabwe,
			      unsigned int idx, stwuct udp_tunnew_info *ti)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_vsi *vsi = np->vsi;
	stwuct ice_pf *pf = vsi->back;
	enum ice_tunnew_type tnw_type;
	int status;

	tnw_type = ti->type == UDP_TUNNEW_TYPE_VXWAN ? TNW_VXWAN : TNW_GENEVE;

	status = ice_destwoy_tunnew(&pf->hw, ti->hw_pwiv, tnw_type,
				    ntohs(ti->powt));
	if (status) {
		netdev_eww(netdev, "Ewwow wemoving UDP tunnew - %d\n",
			   status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * ice_find_pwot_off - find pwot ID and offset paiw, based on pwof and FV index
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: hawdwawe bwock
 * @pwof: pwofiwe ID
 * @fv_idx: fiewd vectow wowd index
 * @pwot: vawiabwe to weceive the pwotocow ID
 * @off: vawiabwe to weceive the pwotocow offset
 */
int
ice_find_pwot_off(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof, u16 fv_idx,
		  u8 *pwot, u16 *off)
{
	stwuct ice_fv_wowd *fv_ext;

	if (pwof >= hw->bwk[bwk].es.count)
		wetuwn -EINVAW;

	if (fv_idx >= hw->bwk[bwk].es.fvw)
		wetuwn -EINVAW;

	fv_ext = hw->bwk[bwk].es.t + (pwof * hw->bwk[bwk].es.fvw);

	*pwot = fv_ext[fv_idx].pwot_id;
	*off = fv_ext[fv_idx].off;

	wetuwn 0;
}

/* PTG Management */

/**
 * ice_ptg_find_ptype - Seawch fow packet type gwoup using packet type (ptype)
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @ptype: the ptype to seawch fow
 * @ptg: pointew to vawiabwe that weceives the PTG
 *
 * This function wiww seawch the PTGs fow a pawticuwaw ptype, wetuwning the
 * PTG ID that contains it thwough the PTG pawametew, with the vawue of
 * ICE_DEFAUWT_PTG (0) meaning it is pawt the defauwt PTG.
 */
static int
ice_ptg_find_ptype(stwuct ice_hw *hw, enum ice_bwock bwk, u16 ptype, u8 *ptg)
{
	if (ptype >= ICE_XWT1_CNT || !ptg)
		wetuwn -EINVAW;

	*ptg = hw->bwk[bwk].xwt1.ptypes[ptype].ptg;
	wetuwn 0;
}

/**
 * ice_ptg_awwoc_vaw - Awwocates a new packet type gwoup ID by vawue
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @ptg: the PTG to awwocate
 *
 * This function awwocates a given packet type gwoup ID specified by the PTG
 * pawametew.
 */
static void ice_ptg_awwoc_vaw(stwuct ice_hw *hw, enum ice_bwock bwk, u8 ptg)
{
	hw->bwk[bwk].xwt1.ptg_tbw[ptg].in_use = twue;
}

/**
 * ice_ptg_wemove_ptype - Wemoves ptype fwom a pawticuwaw packet type gwoup
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @ptype: the ptype to wemove
 * @ptg: the PTG to wemove the ptype fwom
 *
 * This function wiww wemove the ptype fwom the specific PTG, and move it to
 * the defauwt PTG (ICE_DEFAUWT_PTG).
 */
static int
ice_ptg_wemove_ptype(stwuct ice_hw *hw, enum ice_bwock bwk, u16 ptype, u8 ptg)
{
	stwuct ice_ptg_ptype **ch;
	stwuct ice_ptg_ptype *p;

	if (ptype > ICE_XWT1_CNT - 1)
		wetuwn -EINVAW;

	if (!hw->bwk[bwk].xwt1.ptg_tbw[ptg].in_use)
		wetuwn -ENOENT;

	/* Shouwd not happen if .in_use is set, bad config */
	if (!hw->bwk[bwk].xwt1.ptg_tbw[ptg].fiwst_ptype)
		wetuwn -EIO;

	/* find the ptype within this PTG, and bypass the wink ovew it */
	p = hw->bwk[bwk].xwt1.ptg_tbw[ptg].fiwst_ptype;
	ch = &hw->bwk[bwk].xwt1.ptg_tbw[ptg].fiwst_ptype;
	whiwe (p) {
		if (ptype == (p - hw->bwk[bwk].xwt1.ptypes)) {
			*ch = p->next_ptype;
			bweak;
		}

		ch = &p->next_ptype;
		p = p->next_ptype;
	}

	hw->bwk[bwk].xwt1.ptypes[ptype].ptg = ICE_DEFAUWT_PTG;
	hw->bwk[bwk].xwt1.ptypes[ptype].next_ptype = NUWW;

	wetuwn 0;
}

/**
 * ice_ptg_add_mv_ptype - Adds/moves ptype to a pawticuwaw packet type gwoup
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @ptype: the ptype to add ow move
 * @ptg: the PTG to add ow move the ptype to
 *
 * This function wiww eithew add ow move a ptype to a pawticuwaw PTG depending
 * on if the ptype is awweady pawt of anothew gwoup. Note that using a
 * destination PTG ID of ICE_DEFAUWT_PTG (0) wiww move the ptype to the
 * defauwt PTG.
 */
static int
ice_ptg_add_mv_ptype(stwuct ice_hw *hw, enum ice_bwock bwk, u16 ptype, u8 ptg)
{
	u8 owiginaw_ptg;
	int status;

	if (ptype > ICE_XWT1_CNT - 1)
		wetuwn -EINVAW;

	if (!hw->bwk[bwk].xwt1.ptg_tbw[ptg].in_use && ptg != ICE_DEFAUWT_PTG)
		wetuwn -ENOENT;

	status = ice_ptg_find_ptype(hw, bwk, ptype, &owiginaw_ptg);
	if (status)
		wetuwn status;

	/* Is ptype awweady in the cowwect PTG? */
	if (owiginaw_ptg == ptg)
		wetuwn 0;

	/* Wemove fwom owiginaw PTG and move back to the defauwt PTG */
	if (owiginaw_ptg != ICE_DEFAUWT_PTG)
		ice_ptg_wemove_ptype(hw, bwk, ptype, owiginaw_ptg);

	/* Moving to defauwt PTG? Then we'we done with this wequest */
	if (ptg == ICE_DEFAUWT_PTG)
		wetuwn 0;

	/* Add ptype to PTG at beginning of wist */
	hw->bwk[bwk].xwt1.ptypes[ptype].next_ptype =
		hw->bwk[bwk].xwt1.ptg_tbw[ptg].fiwst_ptype;
	hw->bwk[bwk].xwt1.ptg_tbw[ptg].fiwst_ptype =
		&hw->bwk[bwk].xwt1.ptypes[ptype];

	hw->bwk[bwk].xwt1.ptypes[ptype].ptg = ptg;
	hw->bwk[bwk].xwt1.t[ptype] = ptg;

	wetuwn 0;
}

/* Bwock / tabwe size info */
stwuct ice_bwk_size_detaiws {
	u16 xwt1;			/* # XWT1 entwies */
	u16 xwt2;			/* # XWT2 entwies */
	u16 pwof_tcam;			/* # pwofiwe ID TCAM entwies */
	u16 pwof_id;			/* # pwofiwe IDs */
	u8 pwof_cdid_bits;		/* # CDID one-hot bits used in key */
	u16 pwof_wediw;			/* # pwofiwe wediwection entwies */
	u16 es;				/* # extwaction sequence entwies */
	u16 fvw;			/* # fiewd vectow wowds */
	u8 ovewwwite;			/* ovewwwite existing entwies awwowed */
	u8 wevewse;			/* wevewse FV owdew */
};

static const stwuct ice_bwk_size_detaiws bwk_sizes[ICE_BWK_COUNT] = {
	/**
	 * Tabwe Definitions
	 * XWT1 - Numbew of entwies in XWT1 tabwe
	 * XWT2 - Numbew of entwies in XWT2 tabwe
	 * TCAM - Numbew of entwies Pwofiwe ID TCAM tabwe
	 * CDID - Contwow Domain ID of the hawdwawe bwock
	 * PWED - Numbew of entwies in the Pwofiwe Wediwection Tabwe
	 * FV   - Numbew of entwies in the Fiewd Vectow
	 * FVW  - Width (in WOWDs) of the Fiewd Vectow
	 * OVW  - Ovewwwite existing tabwe entwies
	 * WEV  - Wevewse FV
	 */
	/*          XWT1        , XWT2        ,TCAM, PID,CDID,PWED,   FV, FVW */
	/*          Ovewwwite   , Wevewse FV */
	/* SW  */ { ICE_XWT1_CNT, ICE_XWT2_CNT, 512, 256,   0,  256, 256,  48,
		    fawse, fawse },
	/* ACW */ { ICE_XWT1_CNT, ICE_XWT2_CNT, 512, 128,   0,  128, 128,  32,
		    fawse, fawse },
	/* FD  */ { ICE_XWT1_CNT, ICE_XWT2_CNT, 512, 128,   0,  128, 128,  24,
		    fawse, twue  },
	/* WSS */ { ICE_XWT1_CNT, ICE_XWT2_CNT, 512, 128,   0,  128, 128,  24,
		    twue,  twue  },
	/* PE  */ { ICE_XWT1_CNT, ICE_XWT2_CNT,  64,  32,   0,   32,  32,  24,
		    fawse, fawse },
};

enum ice_sid_aww {
	ICE_SID_XWT1_OFF = 0,
	ICE_SID_XWT2_OFF,
	ICE_SID_PW_OFF,
	ICE_SID_PW_WEDIW_OFF,
	ICE_SID_ES_OFF,
	ICE_SID_OFF_COUNT,
};

/* Chawactewistic handwing */

/**
 * ice_match_pwop_wst - detewmine if pwopewties of two wists match
 * @wist1: fiwst pwopewties wist
 * @wist2: second pwopewties wist
 *
 * Count, cookies and the owdew must match in owdew to be considewed equivawent.
 */
static boow
ice_match_pwop_wst(stwuct wist_head *wist1, stwuct wist_head *wist2)
{
	stwuct ice_vsig_pwof *tmp1;
	stwuct ice_vsig_pwof *tmp2;
	u16 chk_count = 0;
	u16 count = 0;

	/* compawe counts */
	wist_fow_each_entwy(tmp1, wist1, wist)
		count++;
	wist_fow_each_entwy(tmp2, wist2, wist)
		chk_count++;
	if (!count || count != chk_count)
		wetuwn fawse;

	tmp1 = wist_fiwst_entwy(wist1, stwuct ice_vsig_pwof, wist);
	tmp2 = wist_fiwst_entwy(wist2, stwuct ice_vsig_pwof, wist);

	/* pwofiwe cookies must compawe, and in the exact same owdew to take
	 * into account pwiowity
	 */
	whiwe (count--) {
		if (tmp2->pwofiwe_cookie != tmp1->pwofiwe_cookie)
			wetuwn fawse;

		tmp1 = wist_next_entwy(tmp1, wist);
		tmp2 = wist_next_entwy(tmp2, wist);
	}

	wetuwn twue;
}

/* VSIG Management */

/**
 * ice_vsig_find_vsi - find a VSIG that contains a specified VSI
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsi: VSI of intewest
 * @vsig: pointew to weceive the VSI gwoup
 *
 * This function wiww wookup the VSI entwy in the XWT2 wist and wetuwn
 * the VSI gwoup its associated with.
 */
static int
ice_vsig_find_vsi(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u16 *vsig)
{
	if (!vsig || vsi >= ICE_MAX_VSI)
		wetuwn -EINVAW;

	/* As wong as thewe's a defauwt ow vawid VSIG associated with the input
	 * VSI, the functions wetuwns a success. Any handwing of VSIG wiww be
	 * done by the fowwowing add, update ow wemove functions.
	 */
	*vsig = hw->bwk[bwk].xwt2.vsis[vsi].vsig;

	wetuwn 0;
}

/**
 * ice_vsig_awwoc_vaw - awwocate a new VSIG by vawue
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsig: the VSIG to awwocate
 *
 * This function wiww awwocate a given VSIG specified by the VSIG pawametew.
 */
static u16 ice_vsig_awwoc_vaw(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig)
{
	u16 idx = vsig & ICE_VSIG_IDX_M;

	if (!hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use) {
		INIT_WIST_HEAD(&hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst);
		hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use = twue;
	}

	wetuwn ICE_VSIG_VAWUE(idx, hw->pf_id);
}

/**
 * ice_vsig_awwoc - Finds a fwee entwy and awwocates a new VSIG
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 *
 * This function wiww itewate thwough the VSIG wist and mawk the fiwst
 * unused entwy fow the new VSIG entwy as used and wetuwn that vawue.
 */
static u16 ice_vsig_awwoc(stwuct ice_hw *hw, enum ice_bwock bwk)
{
	u16 i;

	fow (i = 1; i < ICE_MAX_VSIGS; i++)
		if (!hw->bwk[bwk].xwt2.vsig_tbw[i].in_use)
			wetuwn ice_vsig_awwoc_vaw(hw, bwk, i);

	wetuwn ICE_DEFAUWT_VSIG;
}

/**
 * ice_find_dup_pwops_vsig - find VSI gwoup with a specified set of pwopewties
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @chs: chawactewistic wist
 * @vsig: wetuwns the VSIG with the matching pwofiwes, if found
 *
 * Each VSIG is associated with a chawactewistic set; i.e. aww VSIs undew
 * a gwoup have the same chawactewistic set. To check if thewe exists a VSIG
 * which has the same chawactewistics as the input chawactewistics; this
 * function wiww itewate thwough the XWT2 wist and wetuwn the VSIG that has a
 * matching configuwation. In owdew to make suwe that pwiowities awe accounted
 * fow, the wist must match exactwy, incwuding the owdew in which the
 * chawactewistics awe wisted.
 */
static int
ice_find_dup_pwops_vsig(stwuct ice_hw *hw, enum ice_bwock bwk,
			stwuct wist_head *chs, u16 *vsig)
{
	stwuct ice_xwt2 *xwt2 = &hw->bwk[bwk].xwt2;
	u16 i;

	fow (i = 0; i < xwt2->count; i++)
		if (xwt2->vsig_tbw[i].in_use &&
		    ice_match_pwop_wst(chs, &xwt2->vsig_tbw[i].pwop_wst)) {
			*vsig = ICE_VSIG_VAWUE(i, hw->pf_id);
			wetuwn 0;
		}

	wetuwn -ENOENT;
}

/**
 * ice_vsig_fwee - fwee VSI gwoup
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsig: VSIG to wemove
 *
 * The function wiww wemove aww VSIs associated with the input VSIG and move
 * them to the DEFAUWT_VSIG and mawk the VSIG avaiwabwe.
 */
static int ice_vsig_fwee(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig)
{
	stwuct ice_vsig_pwof *dtmp, *dew;
	stwuct ice_vsig_vsi *vsi_cuw;
	u16 idx;

	idx = vsig & ICE_VSIG_IDX_M;
	if (idx >= ICE_MAX_VSIGS)
		wetuwn -EINVAW;

	if (!hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use)
		wetuwn -ENOENT;

	hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use = fawse;

	vsi_cuw = hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi;
	/* If the VSIG has at weast 1 VSI then itewate thwough the
	 * wist and wemove the VSIs befowe deweting the gwoup.
	 */
	if (vsi_cuw) {
		/* wemove aww vsis associated with this VSIG XWT2 entwy */
		do {
			stwuct ice_vsig_vsi *tmp = vsi_cuw->next_vsi;

			vsi_cuw->vsig = ICE_DEFAUWT_VSIG;
			vsi_cuw->changed = 1;
			vsi_cuw->next_vsi = NUWW;
			vsi_cuw = tmp;
		} whiwe (vsi_cuw);

		/* NUWW tewminate head of VSI wist */
		hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi = NUWW;
	}

	/* fwee chawactewistic wist */
	wist_fow_each_entwy_safe(dew, dtmp,
				 &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
				 wist) {
		wist_dew(&dew->wist);
		devm_kfwee(ice_hw_to_dev(hw), dew);
	}

	/* if VSIG chawactewistic wist was cweawed fow weset
	 * we-initiawize the wist head
	 */
	INIT_WIST_HEAD(&hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst);

	wetuwn 0;
}

/**
 * ice_vsig_wemove_vsi - wemove VSI fwom VSIG
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsi: VSI to wemove
 * @vsig: VSI gwoup to wemove fwom
 *
 * The function wiww wemove the input VSI fwom its VSI gwoup and move it
 * to the DEFAUWT_VSIG.
 */
static int
ice_vsig_wemove_vsi(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u16 vsig)
{
	stwuct ice_vsig_vsi **vsi_head, *vsi_cuw, *vsi_tgt;
	u16 idx;

	idx = vsig & ICE_VSIG_IDX_M;

	if (vsi >= ICE_MAX_VSI || idx >= ICE_MAX_VSIGS)
		wetuwn -EINVAW;

	if (!hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use)
		wetuwn -ENOENT;

	/* entwy awweady in defauwt VSIG, don't have to wemove */
	if (idx == ICE_DEFAUWT_VSIG)
		wetuwn 0;

	vsi_head = &hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi;
	if (!(*vsi_head))
		wetuwn -EIO;

	vsi_tgt = &hw->bwk[bwk].xwt2.vsis[vsi];
	vsi_cuw = (*vsi_head);

	/* itewate the VSI wist, skip ovew the entwy to be wemoved */
	whiwe (vsi_cuw) {
		if (vsi_tgt == vsi_cuw) {
			(*vsi_head) = vsi_cuw->next_vsi;
			bweak;
		}
		vsi_head = &vsi_cuw->next_vsi;
		vsi_cuw = vsi_cuw->next_vsi;
	}

	/* vewify if VSI was wemoved fwom gwoup wist */
	if (!vsi_cuw)
		wetuwn -ENOENT;

	vsi_cuw->vsig = ICE_DEFAUWT_VSIG;
	vsi_cuw->changed = 1;
	vsi_cuw->next_vsi = NUWW;

	wetuwn 0;
}

/**
 * ice_vsig_add_mv_vsi - add ow move a VSI to a VSI gwoup
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsi: VSI to move
 * @vsig: destination VSI gwoup
 *
 * This function wiww move ow add the input VSI to the tawget VSIG.
 * The function wiww find the owiginaw VSIG the VSI bewongs to and
 * move the entwy to the DEFAUWT_VSIG, update the owiginaw VSIG and
 * then move entwy to the new VSIG.
 */
static int
ice_vsig_add_mv_vsi(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u16 vsig)
{
	stwuct ice_vsig_vsi *tmp;
	u16 owig_vsig, idx;
	int status;

	idx = vsig & ICE_VSIG_IDX_M;

	if (vsi >= ICE_MAX_VSI || idx >= ICE_MAX_VSIGS)
		wetuwn -EINVAW;

	/* if VSIG not in use and VSIG is not defauwt type this VSIG
	 * doesn't exist.
	 */
	if (!hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use &&
	    vsig != ICE_DEFAUWT_VSIG)
		wetuwn -ENOENT;

	status = ice_vsig_find_vsi(hw, bwk, vsi, &owig_vsig);
	if (status)
		wetuwn status;

	/* no update wequiwed if vsigs match */
	if (owig_vsig == vsig)
		wetuwn 0;

	if (owig_vsig != ICE_DEFAUWT_VSIG) {
		/* wemove entwy fwom owig_vsig and add to defauwt VSIG */
		status = ice_vsig_wemove_vsi(hw, bwk, vsi, owig_vsig);
		if (status)
			wetuwn status;
	}

	if (idx == ICE_DEFAUWT_VSIG)
		wetuwn 0;

	/* Cweate VSI entwy and add VSIG and pwop_mask vawues */
	hw->bwk[bwk].xwt2.vsis[vsi].vsig = vsig;
	hw->bwk[bwk].xwt2.vsis[vsi].changed = 1;

	/* Add new entwy to the head of the VSIG wist */
	tmp = hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi;
	hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi =
		&hw->bwk[bwk].xwt2.vsis[vsi];
	hw->bwk[bwk].xwt2.vsis[vsi].next_vsi = tmp;
	hw->bwk[bwk].xwt2.t[vsi] = vsig;

	wetuwn 0;
}

/**
 * ice_pwof_has_mask_idx - detewmine if pwofiwe index masking is identicaw
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @pwof: pwofiwe to check
 * @idx: pwofiwe index to check
 * @mask: mask to match
 */
static boow
ice_pwof_has_mask_idx(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof, u16 idx,
		      u16 mask)
{
	boow expect_no_mask = fawse;
	boow found = fawse;
	boow match = fawse;
	u16 i;

	/* If mask is 0x0000 ow 0xffff, then thewe is no masking */
	if (mask == 0 || mask == 0xffff)
		expect_no_mask = twue;

	/* Scan the enabwed masks on this pwofiwe, fow the specified idx */
	fow (i = hw->bwk[bwk].masks.fiwst; i < hw->bwk[bwk].masks.fiwst +
	     hw->bwk[bwk].masks.count; i++)
		if (hw->bwk[bwk].es.mask_ena[pwof] & BIT(i))
			if (hw->bwk[bwk].masks.masks[i].in_use &&
			    hw->bwk[bwk].masks.masks[i].idx == idx) {
				found = twue;
				if (hw->bwk[bwk].masks.masks[i].mask == mask)
					match = twue;
				bweak;
			}

	if (expect_no_mask) {
		if (found)
			wetuwn fawse;
	} ewse {
		if (!match)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ice_pwof_has_mask - detewmine if pwofiwe masking is identicaw
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @pwof: pwofiwe to check
 * @masks: masks to match
 */
static boow
ice_pwof_has_mask(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof, u16 *masks)
{
	u16 i;

	/* es->mask_ena[pwof] wiww have the mask */
	fow (i = 0; i < hw->bwk[bwk].es.fvw; i++)
		if (!ice_pwof_has_mask_idx(hw, bwk, pwof, i, masks[i]))
			wetuwn fawse;

	wetuwn twue;
}

/**
 * ice_find_pwof_id_with_mask - find pwofiwe ID fow a given fiewd vectow
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @fv: fiewd vectow to seawch fow
 * @masks: masks fow FV
 * @symm: symmetwic setting fow WSS fwows
 * @pwof_id: weceives the pwofiwe ID
 */
static int
ice_find_pwof_id_with_mask(stwuct ice_hw *hw, enum ice_bwock bwk,
			   stwuct ice_fv_wowd *fv, u16 *masks, boow symm,
			   u8 *pwof_id)
{
	stwuct ice_es *es = &hw->bwk[bwk].es;
	u8 i;

	/* Fow FD, we don't want to we-use a existed pwofiwe with the same
	 * fiewd vectow and mask. This wiww cause wuwe intewfewence.
	 */
	if (bwk == ICE_BWK_FD)
		wetuwn -ENOENT;

	fow (i = 0; i < (u8)es->count; i++) {
		u16 off = i * es->fvw;

		if (bwk == ICE_BWK_WSS && es->symm[i] != symm)
			continue;

		if (memcmp(&es->t[off], fv, es->fvw * sizeof(*fv)))
			continue;

		/* check if masks settings awe the same fow this pwofiwe */
		if (masks && !ice_pwof_has_mask(hw, bwk, i, masks))
			continue;

		*pwof_id = i;
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

/**
 * ice_pwof_id_wswc_type - get pwofiwe ID wesouwce type fow a bwock type
 * @bwk: the bwock type
 * @wswc_type: pointew to vawiabwe to weceive the wesouwce type
 */
static boow ice_pwof_id_wswc_type(enum ice_bwock bwk, u16 *wswc_type)
{
	switch (bwk) {
	case ICE_BWK_FD:
		*wswc_type = ICE_AQC_WES_TYPE_FD_PWOF_BWDW_PWOFID;
		bweak;
	case ICE_BWK_WSS:
		*wswc_type = ICE_AQC_WES_TYPE_HASH_PWOF_BWDW_PWOFID;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * ice_tcam_ent_wswc_type - get TCAM entwy wesouwce type fow a bwock type
 * @bwk: the bwock type
 * @wswc_type: pointew to vawiabwe to weceive the wesouwce type
 */
static boow ice_tcam_ent_wswc_type(enum ice_bwock bwk, u16 *wswc_type)
{
	switch (bwk) {
	case ICE_BWK_FD:
		*wswc_type = ICE_AQC_WES_TYPE_FD_PWOF_BWDW_TCAM;
		bweak;
	case ICE_BWK_WSS:
		*wswc_type = ICE_AQC_WES_TYPE_HASH_PWOF_BWDW_TCAM;
		bweak;
	defauwt:
		wetuwn fawse;
	}
	wetuwn twue;
}

/**
 * ice_awwoc_tcam_ent - awwocate hawdwawe TCAM entwy
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock to awwocate the TCAM fow
 * @btm: twue to awwocate fwom bottom of tabwe, fawse to awwocate fwom top
 * @tcam_idx: pointew to vawiabwe to weceive the TCAM entwy
 *
 * This function awwocates a new entwy in a Pwofiwe ID TCAM fow a specific
 * bwock.
 */
static int
ice_awwoc_tcam_ent(stwuct ice_hw *hw, enum ice_bwock bwk, boow btm,
		   u16 *tcam_idx)
{
	u16 wes_type;

	if (!ice_tcam_ent_wswc_type(bwk, &wes_type))
		wetuwn -EINVAW;

	wetuwn ice_awwoc_hw_wes(hw, wes_type, 1, btm, tcam_idx);
}

/**
 * ice_fwee_tcam_ent - fwee hawdwawe TCAM entwy
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock fwom which to fwee the TCAM entwy
 * @tcam_idx: the TCAM entwy to fwee
 *
 * This function fwees an entwy in a Pwofiwe ID TCAM fow a specific bwock.
 */
static int
ice_fwee_tcam_ent(stwuct ice_hw *hw, enum ice_bwock bwk, u16 tcam_idx)
{
	u16 wes_type;

	if (!ice_tcam_ent_wswc_type(bwk, &wes_type))
		wetuwn -EINVAW;

	wetuwn ice_fwee_hw_wes(hw, wes_type, 1, &tcam_idx);
}

/**
 * ice_awwoc_pwof_id - awwocate pwofiwe ID
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock to awwocate the pwofiwe ID fow
 * @pwof_id: pointew to vawiabwe to weceive the pwofiwe ID
 *
 * This function awwocates a new pwofiwe ID, which awso cowwesponds to a Fiewd
 * Vectow (Extwaction Sequence) entwy.
 */
static int ice_awwoc_pwof_id(stwuct ice_hw *hw, enum ice_bwock bwk, u8 *pwof_id)
{
	u16 wes_type;
	u16 get_pwof;
	int status;

	if (!ice_pwof_id_wswc_type(bwk, &wes_type))
		wetuwn -EINVAW;

	status = ice_awwoc_hw_wes(hw, wes_type, 1, fawse, &get_pwof);
	if (!status)
		*pwof_id = (u8)get_pwof;

	wetuwn status;
}

/**
 * ice_fwee_pwof_id - fwee pwofiwe ID
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock fwom which to fwee the pwofiwe ID
 * @pwof_id: the pwofiwe ID to fwee
 *
 * This function fwees a pwofiwe ID, which awso cowwesponds to a Fiewd Vectow.
 */
static int ice_fwee_pwof_id(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof_id)
{
	u16 tmp_pwof_id = (u16)pwof_id;
	u16 wes_type;

	if (!ice_pwof_id_wswc_type(bwk, &wes_type))
		wetuwn -EINVAW;

	wetuwn ice_fwee_hw_wes(hw, wes_type, 1, &tmp_pwof_id);
}

/**
 * ice_pwof_inc_wef - incwement wefewence count fow pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock fwom which to fwee the pwofiwe ID
 * @pwof_id: the pwofiwe ID fow which to incwement the wefewence count
 */
static int ice_pwof_inc_wef(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof_id)
{
	if (pwof_id > hw->bwk[bwk].es.count)
		wetuwn -EINVAW;

	hw->bwk[bwk].es.wef_count[pwof_id]++;

	wetuwn 0;
}

/**
 * ice_wwite_pwof_mask_weg - wwite pwofiwe mask wegistew
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @mask_idx: mask index
 * @idx: index of the FV which wiww use the mask
 * @mask: the 16-bit mask
 */
static void
ice_wwite_pwof_mask_weg(stwuct ice_hw *hw, enum ice_bwock bwk, u16 mask_idx,
			u16 idx, u16 mask)
{
	u32 offset;
	u32 vaw;

	switch (bwk) {
	case ICE_BWK_WSS:
		offset = GWQF_HMASK(mask_idx);
		vaw = FIEWD_PWEP(GWQF_HMASK_MSK_INDEX_M, idx);
		vaw |= FIEWD_PWEP(GWQF_HMASK_MASK_M, mask);
		bweak;
	case ICE_BWK_FD:
		offset = GWQF_FDMASK(mask_idx);
		vaw = FIEWD_PWEP(GWQF_FDMASK_MSK_INDEX_M, idx);
		vaw |= FIEWD_PWEP(GWQF_FDMASK_MASK_M, mask);
		bweak;
	defauwt:
		ice_debug(hw, ICE_DBG_PKG, "No pwofiwe masks fow bwock %d\n",
			  bwk);
		wetuwn;
	}

	ww32(hw, offset, vaw);
	ice_debug(hw, ICE_DBG_PKG, "wwite mask, bwk %d (%d): %x = %x\n",
		  bwk, idx, offset, vaw);
}

/**
 * ice_wwite_pwof_mask_enabwe_wes - wwite pwofiwe mask enabwe wegistew
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @pwof_id: pwofiwe ID
 * @enabwe_mask: enabwe mask
 */
static void
ice_wwite_pwof_mask_enabwe_wes(stwuct ice_hw *hw, enum ice_bwock bwk,
			       u16 pwof_id, u32 enabwe_mask)
{
	u32 offset;

	switch (bwk) {
	case ICE_BWK_WSS:
		offset = GWQF_HMASK_SEW(pwof_id);
		bweak;
	case ICE_BWK_FD:
		offset = GWQF_FDMASK_SEW(pwof_id);
		bweak;
	defauwt:
		ice_debug(hw, ICE_DBG_PKG, "No pwofiwe masks fow bwock %d\n",
			  bwk);
		wetuwn;
	}

	ww32(hw, offset, enabwe_mask);
	ice_debug(hw, ICE_DBG_PKG, "wwite mask enabwe, bwk %d (%d): %x = %x\n",
		  bwk, pwof_id, offset, enabwe_mask);
}

/**
 * ice_init_pwof_masks - initiaw pwof masks
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 */
static void ice_init_pwof_masks(stwuct ice_hw *hw, enum ice_bwock bwk)
{
	u16 pew_pf;
	u16 i;

	mutex_init(&hw->bwk[bwk].masks.wock);

	pew_pf = ICE_PWOF_MASK_COUNT / hw->dev_caps.num_funcs;

	hw->bwk[bwk].masks.count = pew_pf;
	hw->bwk[bwk].masks.fiwst = hw->pf_id * pew_pf;

	memset(hw->bwk[bwk].masks.masks, 0, sizeof(hw->bwk[bwk].masks.masks));

	fow (i = hw->bwk[bwk].masks.fiwst;
	     i < hw->bwk[bwk].masks.fiwst + hw->bwk[bwk].masks.count; i++)
		ice_wwite_pwof_mask_weg(hw, bwk, i, 0, 0);
}

/**
 * ice_init_aww_pwof_masks - initiawize aww pwof masks
 * @hw: pointew to the HW stwuct
 */
static void ice_init_aww_pwof_masks(stwuct ice_hw *hw)
{
	ice_init_pwof_masks(hw, ICE_BWK_WSS);
	ice_init_pwof_masks(hw, ICE_BWK_FD);
}

/**
 * ice_awwoc_pwof_mask - awwocate pwofiwe mask
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @idx: index of FV which wiww use the mask
 * @mask: the 16-bit mask
 * @mask_idx: vawiabwe to weceive the mask index
 */
static int
ice_awwoc_pwof_mask(stwuct ice_hw *hw, enum ice_bwock bwk, u16 idx, u16 mask,
		    u16 *mask_idx)
{
	boow found_unused = fawse, found_copy = fawse;
	u16 unused_idx = 0, copy_idx = 0;
	int status = -ENOSPC;
	u16 i;

	if (bwk != ICE_BWK_WSS && bwk != ICE_BWK_FD)
		wetuwn -EINVAW;

	mutex_wock(&hw->bwk[bwk].masks.wock);

	fow (i = hw->bwk[bwk].masks.fiwst;
	     i < hw->bwk[bwk].masks.fiwst + hw->bwk[bwk].masks.count; i++)
		if (hw->bwk[bwk].masks.masks[i].in_use) {
			/* if mask is in use and it exactwy dupwicates the
			 * desiwed mask and index, then in can be weused
			 */
			if (hw->bwk[bwk].masks.masks[i].mask == mask &&
			    hw->bwk[bwk].masks.masks[i].idx == idx) {
				found_copy = twue;
				copy_idx = i;
				bweak;
			}
		} ewse {
			/* save off unused index, but keep seawching in case
			 * thewe is an exact match watew on
			 */
			if (!found_unused) {
				found_unused = twue;
				unused_idx = i;
			}
		}

	if (found_copy)
		i = copy_idx;
	ewse if (found_unused)
		i = unused_idx;
	ewse
		goto eww_ice_awwoc_pwof_mask;

	/* update mask fow a new entwy */
	if (found_unused) {
		hw->bwk[bwk].masks.masks[i].in_use = twue;
		hw->bwk[bwk].masks.masks[i].mask = mask;
		hw->bwk[bwk].masks.masks[i].idx = idx;
		hw->bwk[bwk].masks.masks[i].wef = 0;
		ice_wwite_pwof_mask_weg(hw, bwk, i, idx, mask);
	}

	hw->bwk[bwk].masks.masks[i].wef++;
	*mask_idx = i;
	status = 0;

eww_ice_awwoc_pwof_mask:
	mutex_unwock(&hw->bwk[bwk].masks.wock);

	wetuwn status;
}

/**
 * ice_fwee_pwof_mask - fwee pwofiwe mask
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @mask_idx: index of mask
 */
static int
ice_fwee_pwof_mask(stwuct ice_hw *hw, enum ice_bwock bwk, u16 mask_idx)
{
	if (bwk != ICE_BWK_WSS && bwk != ICE_BWK_FD)
		wetuwn -EINVAW;

	if (!(mask_idx >= hw->bwk[bwk].masks.fiwst &&
	      mask_idx < hw->bwk[bwk].masks.fiwst + hw->bwk[bwk].masks.count))
		wetuwn -ENOENT;

	mutex_wock(&hw->bwk[bwk].masks.wock);

	if (!hw->bwk[bwk].masks.masks[mask_idx].in_use)
		goto exit_ice_fwee_pwof_mask;

	if (hw->bwk[bwk].masks.masks[mask_idx].wef > 1) {
		hw->bwk[bwk].masks.masks[mask_idx].wef--;
		goto exit_ice_fwee_pwof_mask;
	}

	/* wemove mask */
	hw->bwk[bwk].masks.masks[mask_idx].in_use = fawse;
	hw->bwk[bwk].masks.masks[mask_idx].mask = 0;
	hw->bwk[bwk].masks.masks[mask_idx].idx = 0;

	/* update mask as unused entwy */
	ice_debug(hw, ICE_DBG_PKG, "Fwee mask, bwk %d, mask %d\n", bwk,
		  mask_idx);
	ice_wwite_pwof_mask_weg(hw, bwk, mask_idx, 0, 0);

exit_ice_fwee_pwof_mask:
	mutex_unwock(&hw->bwk[bwk].masks.wock);

	wetuwn 0;
}

/**
 * ice_fwee_pwof_masks - fwee aww pwofiwe masks fow a pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @pwof_id: pwofiwe ID
 */
static int
ice_fwee_pwof_masks(stwuct ice_hw *hw, enum ice_bwock bwk, u16 pwof_id)
{
	u32 mask_bm;
	u16 i;

	if (bwk != ICE_BWK_WSS && bwk != ICE_BWK_FD)
		wetuwn -EINVAW;

	mask_bm = hw->bwk[bwk].es.mask_ena[pwof_id];
	fow (i = 0; i < BITS_PEW_BYTE * sizeof(mask_bm); i++)
		if (mask_bm & BIT(i))
			ice_fwee_pwof_mask(hw, bwk, i);

	wetuwn 0;
}

/**
 * ice_shutdown_pwof_masks - weweases wock fow masking
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 *
 * This shouwd be cawwed befowe unwoading the dwivew
 */
static void ice_shutdown_pwof_masks(stwuct ice_hw *hw, enum ice_bwock bwk)
{
	u16 i;

	mutex_wock(&hw->bwk[bwk].masks.wock);

	fow (i = hw->bwk[bwk].masks.fiwst;
	     i < hw->bwk[bwk].masks.fiwst + hw->bwk[bwk].masks.count; i++) {
		ice_wwite_pwof_mask_weg(hw, bwk, i, 0, 0);

		hw->bwk[bwk].masks.masks[i].in_use = fawse;
		hw->bwk[bwk].masks.masks[i].idx = 0;
		hw->bwk[bwk].masks.masks[i].mask = 0;
	}

	mutex_unwock(&hw->bwk[bwk].masks.wock);
	mutex_destwoy(&hw->bwk[bwk].masks.wock);
}

/**
 * ice_shutdown_aww_pwof_masks - weweases aww wocks fow masking
 * @hw: pointew to the HW stwuct
 *
 * This shouwd be cawwed befowe unwoading the dwivew
 */
static void ice_shutdown_aww_pwof_masks(stwuct ice_hw *hw)
{
	ice_shutdown_pwof_masks(hw, ICE_BWK_WSS);
	ice_shutdown_pwof_masks(hw, ICE_BWK_FD);
}

/**
 * ice_update_pwof_masking - set wegistews accowding to masking
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @pwof_id: pwofiwe ID
 * @masks: masks
 */
static int
ice_update_pwof_masking(stwuct ice_hw *hw, enum ice_bwock bwk, u16 pwof_id,
			u16 *masks)
{
	boow eww = fawse;
	u32 ena_mask = 0;
	u16 idx;
	u16 i;

	/* Onwy suppowt FD and WSS masking, othewwise nothing to be done */
	if (bwk != ICE_BWK_WSS && bwk != ICE_BWK_FD)
		wetuwn 0;

	fow (i = 0; i < hw->bwk[bwk].es.fvw; i++)
		if (masks[i] && masks[i] != 0xFFFF) {
			if (!ice_awwoc_pwof_mask(hw, bwk, i, masks[i], &idx)) {
				ena_mask |= BIT(idx);
			} ewse {
				/* not enough bitmaps */
				eww = twue;
				bweak;
			}
		}

	if (eww) {
		/* fwee any bitmaps we have awwocated */
		fow (i = 0; i < BITS_PEW_BYTE * sizeof(ena_mask); i++)
			if (ena_mask & BIT(i))
				ice_fwee_pwof_mask(hw, bwk, i);

		wetuwn -EIO;
	}

	/* enabwe the masks fow this pwofiwe */
	ice_wwite_pwof_mask_enabwe_wes(hw, bwk, pwof_id, ena_mask);

	/* stowe enabwed masks with pwofiwe so that they can be fweed watew */
	hw->bwk[bwk].es.mask_ena[pwof_id] = ena_mask;

	wetuwn 0;
}

/**
 * ice_wwite_es - wwite an extwaction sequence and symmetwic setting to hawdwawe
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock in which to wwite the extwaction sequence
 * @pwof_id: the pwofiwe ID to wwite
 * @fv: pointew to the extwaction sequence to wwite - NUWW to cweaw extwaction
 * @symm: symmetwic setting fow WSS pwofiwes
 */
static void
ice_wwite_es(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof_id,
	     stwuct ice_fv_wowd *fv, boow symm)
{
	u16 off;

	off = pwof_id * hw->bwk[bwk].es.fvw;
	if (!fv) {
		memset(&hw->bwk[bwk].es.t[off], 0,
		       hw->bwk[bwk].es.fvw * sizeof(*fv));
		hw->bwk[bwk].es.wwitten[pwof_id] = fawse;
	} ewse {
		memcpy(&hw->bwk[bwk].es.t[off], fv,
		       hw->bwk[bwk].es.fvw * sizeof(*fv));
	}

	if (bwk == ICE_BWK_WSS)
		hw->bwk[bwk].es.symm[pwof_id] = symm;
}

/**
 * ice_pwof_dec_wef - decwement wefewence count fow pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock fwom which to fwee the pwofiwe ID
 * @pwof_id: the pwofiwe ID fow which to decwement the wefewence count
 */
static int
ice_pwof_dec_wef(stwuct ice_hw *hw, enum ice_bwock bwk, u8 pwof_id)
{
	if (pwof_id > hw->bwk[bwk].es.count)
		wetuwn -EINVAW;

	if (hw->bwk[bwk].es.wef_count[pwof_id] > 0) {
		if (!--hw->bwk[bwk].es.wef_count[pwof_id]) {
			ice_wwite_es(hw, bwk, pwof_id, NUWW, fawse);
			ice_fwee_pwof_masks(hw, bwk, pwof_id);
			wetuwn ice_fwee_pwof_id(hw, bwk, pwof_id);
		}
	}

	wetuwn 0;
}

/* Bwock / tabwe section IDs */
static const u32 ice_bwk_sids[ICE_BWK_COUNT][ICE_SID_OFF_COUNT] = {
	/* SWITCH */
	{	ICE_SID_XWT1_SW,
		ICE_SID_XWT2_SW,
		ICE_SID_PWOFID_TCAM_SW,
		ICE_SID_PWOFID_WEDIW_SW,
		ICE_SID_FWD_VEC_SW
	},

	/* ACW */
	{	ICE_SID_XWT1_ACW,
		ICE_SID_XWT2_ACW,
		ICE_SID_PWOFID_TCAM_ACW,
		ICE_SID_PWOFID_WEDIW_ACW,
		ICE_SID_FWD_VEC_ACW
	},

	/* FD */
	{	ICE_SID_XWT1_FD,
		ICE_SID_XWT2_FD,
		ICE_SID_PWOFID_TCAM_FD,
		ICE_SID_PWOFID_WEDIW_FD,
		ICE_SID_FWD_VEC_FD
	},

	/* WSS */
	{	ICE_SID_XWT1_WSS,
		ICE_SID_XWT2_WSS,
		ICE_SID_PWOFID_TCAM_WSS,
		ICE_SID_PWOFID_WEDIW_WSS,
		ICE_SID_FWD_VEC_WSS
	},

	/* PE */
	{	ICE_SID_XWT1_PE,
		ICE_SID_XWT2_PE,
		ICE_SID_PWOFID_TCAM_PE,
		ICE_SID_PWOFID_WEDIW_PE,
		ICE_SID_FWD_VEC_PE
	}
};

/**
 * ice_init_sw_xwt1_db - init softwawe XWT1 database fwom HW tabwes
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: the HW bwock to initiawize
 */
static void ice_init_sw_xwt1_db(stwuct ice_hw *hw, enum ice_bwock bwk)
{
	u16 pt;

	fow (pt = 0; pt < hw->bwk[bwk].xwt1.count; pt++) {
		u8 ptg;

		ptg = hw->bwk[bwk].xwt1.t[pt];
		if (ptg != ICE_DEFAUWT_PTG) {
			ice_ptg_awwoc_vaw(hw, bwk, ptg);
			ice_ptg_add_mv_ptype(hw, bwk, pt, ptg);
		}
	}
}

/**
 * ice_init_sw_xwt2_db - init softwawe XWT2 database fwom HW tabwes
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: the HW bwock to initiawize
 */
static void ice_init_sw_xwt2_db(stwuct ice_hw *hw, enum ice_bwock bwk)
{
	u16 vsi;

	fow (vsi = 0; vsi < hw->bwk[bwk].xwt2.count; vsi++) {
		u16 vsig;

		vsig = hw->bwk[bwk].xwt2.t[vsi];
		if (vsig) {
			ice_vsig_awwoc_vaw(hw, bwk, vsig);
			ice_vsig_add_mv_vsi(hw, bwk, vsi, vsig);
			/* no changes at this time, since this has been
			 * initiawized fwom the owiginaw package
			 */
			hw->bwk[bwk].xwt2.vsis[vsi].changed = 0;
		}
	}
}

/**
 * ice_init_sw_db - init softwawe database fwom HW tabwes
 * @hw: pointew to the hawdwawe stwuctuwe
 */
static void ice_init_sw_db(stwuct ice_hw *hw)
{
	u16 i;

	fow (i = 0; i < ICE_BWK_COUNT; i++) {
		ice_init_sw_xwt1_db(hw, (enum ice_bwock)i);
		ice_init_sw_xwt2_db(hw, (enum ice_bwock)i);
	}
}

/**
 * ice_fiww_tbw - Weads content of a singwe tabwe type into database
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwock_id: Bwock ID of the tabwe to copy
 * @sid: Section ID of the tabwe to copy
 *
 * Wiww attempt to wead the entiwe content of a given tabwe of a singwe bwock
 * into the dwivew database. We assume that the buffew wiww awways
 * be as wawge ow wawgew than the data contained in the package. If
 * this condition is not met, thewe is most wikewy an ewwow in the package
 * contents.
 */
static void ice_fiww_tbw(stwuct ice_hw *hw, enum ice_bwock bwock_id, u32 sid)
{
	u32 dst_wen, sect_wen, offset = 0;
	stwuct ice_pwof_wediw_section *pw;
	stwuct ice_pwof_id_section *pid;
	stwuct ice_xwt1_section *xwt1;
	stwuct ice_xwt2_section *xwt2;
	stwuct ice_sw_fv_section *es;
	stwuct ice_pkg_enum state;
	u8 *swc, *dst;
	void *sect;

	/* if the HW segment pointew is nuww then the fiwst itewation of
	 * ice_pkg_enum_section() wiww faiw. In this case the HW tabwes wiww
	 * not be fiwwed and wetuwn success.
	 */
	if (!hw->seg) {
		ice_debug(hw, ICE_DBG_PKG, "hw->seg is NUWW, tabwes awe not fiwwed\n");
		wetuwn;
	}

	memset(&state, 0, sizeof(state));

	sect = ice_pkg_enum_section(hw->seg, &state, sid);

	whiwe (sect) {
		switch (sid) {
		case ICE_SID_XWT1_SW:
		case ICE_SID_XWT1_FD:
		case ICE_SID_XWT1_WSS:
		case ICE_SID_XWT1_ACW:
		case ICE_SID_XWT1_PE:
			xwt1 = sect;
			swc = xwt1->vawue;
			sect_wen = we16_to_cpu(xwt1->count) *
				sizeof(*hw->bwk[bwock_id].xwt1.t);
			dst = hw->bwk[bwock_id].xwt1.t;
			dst_wen = hw->bwk[bwock_id].xwt1.count *
				sizeof(*hw->bwk[bwock_id].xwt1.t);
			bweak;
		case ICE_SID_XWT2_SW:
		case ICE_SID_XWT2_FD:
		case ICE_SID_XWT2_WSS:
		case ICE_SID_XWT2_ACW:
		case ICE_SID_XWT2_PE:
			xwt2 = sect;
			swc = (__fowce u8 *)xwt2->vawue;
			sect_wen = we16_to_cpu(xwt2->count) *
				sizeof(*hw->bwk[bwock_id].xwt2.t);
			dst = (u8 *)hw->bwk[bwock_id].xwt2.t;
			dst_wen = hw->bwk[bwock_id].xwt2.count *
				sizeof(*hw->bwk[bwock_id].xwt2.t);
			bweak;
		case ICE_SID_PWOFID_TCAM_SW:
		case ICE_SID_PWOFID_TCAM_FD:
		case ICE_SID_PWOFID_TCAM_WSS:
		case ICE_SID_PWOFID_TCAM_ACW:
		case ICE_SID_PWOFID_TCAM_PE:
			pid = sect;
			swc = (u8 *)pid->entwy;
			sect_wen = we16_to_cpu(pid->count) *
				sizeof(*hw->bwk[bwock_id].pwof.t);
			dst = (u8 *)hw->bwk[bwock_id].pwof.t;
			dst_wen = hw->bwk[bwock_id].pwof.count *
				sizeof(*hw->bwk[bwock_id].pwof.t);
			bweak;
		case ICE_SID_PWOFID_WEDIW_SW:
		case ICE_SID_PWOFID_WEDIW_FD:
		case ICE_SID_PWOFID_WEDIW_WSS:
		case ICE_SID_PWOFID_WEDIW_ACW:
		case ICE_SID_PWOFID_WEDIW_PE:
			pw = sect;
			swc = pw->wediw_vawue;
			sect_wen = we16_to_cpu(pw->count) *
				sizeof(*hw->bwk[bwock_id].pwof_wediw.t);
			dst = hw->bwk[bwock_id].pwof_wediw.t;
			dst_wen = hw->bwk[bwock_id].pwof_wediw.count *
				sizeof(*hw->bwk[bwock_id].pwof_wediw.t);
			bweak;
		case ICE_SID_FWD_VEC_SW:
		case ICE_SID_FWD_VEC_FD:
		case ICE_SID_FWD_VEC_WSS:
		case ICE_SID_FWD_VEC_ACW:
		case ICE_SID_FWD_VEC_PE:
			es = sect;
			swc = (u8 *)es->fv;
			sect_wen = (u32)(we16_to_cpu(es->count) *
					 hw->bwk[bwock_id].es.fvw) *
				sizeof(*hw->bwk[bwock_id].es.t);
			dst = (u8 *)hw->bwk[bwock_id].es.t;
			dst_wen = (u32)(hw->bwk[bwock_id].es.count *
					hw->bwk[bwock_id].es.fvw) *
				sizeof(*hw->bwk[bwock_id].es.t);
			bweak;
		defauwt:
			wetuwn;
		}

		/* if the section offset exceeds destination wength, tewminate
		 * tabwe fiww.
		 */
		if (offset > dst_wen)
			wetuwn;

		/* if the sum of section size and offset exceed destination size
		 * then we awe out of bounds of the HW tabwe size fow that PF.
		 * Changing section wength to fiww the wemaining tabwe space
		 * of that PF.
		 */
		if ((offset + sect_wen) > dst_wen)
			sect_wen = dst_wen - offset;

		memcpy(dst + offset, swc, sect_wen);
		offset += sect_wen;
		sect = ice_pkg_enum_section(NUWW, &state, sid);
	}
}

/**
 * ice_fiww_bwk_tbws - Wead package context fow tabwes
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Weads the cuwwent package contents and popuwates the dwivew
 * database with the data itewativewy fow aww advanced featuwe
 * bwocks. Assume that the HW tabwes have been awwocated.
 */
void ice_fiww_bwk_tbws(stwuct ice_hw *hw)
{
	u8 i;

	fow (i = 0; i < ICE_BWK_COUNT; i++) {
		enum ice_bwock bwk_id = (enum ice_bwock)i;

		ice_fiww_tbw(hw, bwk_id, hw->bwk[bwk_id].xwt1.sid);
		ice_fiww_tbw(hw, bwk_id, hw->bwk[bwk_id].xwt2.sid);
		ice_fiww_tbw(hw, bwk_id, hw->bwk[bwk_id].pwof.sid);
		ice_fiww_tbw(hw, bwk_id, hw->bwk[bwk_id].pwof_wediw.sid);
		ice_fiww_tbw(hw, bwk_id, hw->bwk[bwk_id].es.sid);
	}

	ice_init_sw_db(hw);
}

/**
 * ice_fwee_pwof_map - fwee pwofiwe map
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk_idx: HW bwock index
 */
static void ice_fwee_pwof_map(stwuct ice_hw *hw, u8 bwk_idx)
{
	stwuct ice_es *es = &hw->bwk[bwk_idx].es;
	stwuct ice_pwof_map *dew, *tmp;

	mutex_wock(&es->pwof_map_wock);
	wist_fow_each_entwy_safe(dew, tmp, &es->pwof_map, wist) {
		wist_dew(&dew->wist);
		devm_kfwee(ice_hw_to_dev(hw), dew);
	}
	INIT_WIST_HEAD(&es->pwof_map);
	mutex_unwock(&es->pwof_map_wock);
}

/**
 * ice_fwee_fwow_pwofs - fwee fwow pwofiwe entwies
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk_idx: HW bwock index
 */
static void ice_fwee_fwow_pwofs(stwuct ice_hw *hw, u8 bwk_idx)
{
	stwuct ice_fwow_pwof *p, *tmp;

	mutex_wock(&hw->fw_pwofs_wocks[bwk_idx]);
	wist_fow_each_entwy_safe(p, tmp, &hw->fw_pwofs[bwk_idx], w_entwy) {
		stwuct ice_fwow_entwy *e, *t;

		wist_fow_each_entwy_safe(e, t, &p->entwies, w_entwy)
			ice_fwow_wem_entwy(hw, (enum ice_bwock)bwk_idx,
					   ICE_FWOW_ENTWY_HNDW(e));

		wist_dew(&p->w_entwy);

		mutex_destwoy(&p->entwies_wock);
		devm_kfwee(ice_hw_to_dev(hw), p);
	}
	mutex_unwock(&hw->fw_pwofs_wocks[bwk_idx]);

	/* if dwivew is in weset and tabwes awe being cweawed
	 * we-initiawize the fwow pwofiwe wist heads
	 */
	INIT_WIST_HEAD(&hw->fw_pwofs[bwk_idx]);
}

/**
 * ice_fwee_vsig_tbw - fwee compwete VSIG tabwe entwies
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: the HW bwock on which to fwee the VSIG tabwe entwies
 */
static void ice_fwee_vsig_tbw(stwuct ice_hw *hw, enum ice_bwock bwk)
{
	u16 i;

	if (!hw->bwk[bwk].xwt2.vsig_tbw)
		wetuwn;

	fow (i = 1; i < ICE_MAX_VSIGS; i++)
		if (hw->bwk[bwk].xwt2.vsig_tbw[i].in_use)
			ice_vsig_fwee(hw, bwk, i);
}

/**
 * ice_fwee_hw_tbws - fwee hawdwawe tabwe memowy
 * @hw: pointew to the hawdwawe stwuctuwe
 */
void ice_fwee_hw_tbws(stwuct ice_hw *hw)
{
	stwuct ice_wss_cfg *w, *wt;
	u8 i;

	fow (i = 0; i < ICE_BWK_COUNT; i++) {
		if (hw->bwk[i].is_wist_init) {
			stwuct ice_es *es = &hw->bwk[i].es;

			ice_fwee_pwof_map(hw, i);
			mutex_destwoy(&es->pwof_map_wock);

			ice_fwee_fwow_pwofs(hw, i);
			mutex_destwoy(&hw->fw_pwofs_wocks[i]);

			hw->bwk[i].is_wist_init = fawse;
		}
		ice_fwee_vsig_tbw(hw, (enum ice_bwock)i);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].xwt1.ptypes);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].xwt1.ptg_tbw);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].xwt1.t);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].xwt2.t);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].xwt2.vsig_tbw);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].xwt2.vsis);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].pwof.t);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].pwof_wediw.t);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].es.t);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].es.wef_count);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].es.symm);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].es.wwitten);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].es.mask_ena);
		devm_kfwee(ice_hw_to_dev(hw), hw->bwk[i].pwof_id.id);
	}

	wist_fow_each_entwy_safe(w, wt, &hw->wss_wist_head, w_entwy) {
		wist_dew(&w->w_entwy);
		devm_kfwee(ice_hw_to_dev(hw), w);
	}
	mutex_destwoy(&hw->wss_wocks);
	ice_shutdown_aww_pwof_masks(hw);
	memset(hw->bwk, 0, sizeof(hw->bwk));
}

/**
 * ice_init_fwow_pwofs - init fwow pwofiwe wocks and wist heads
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk_idx: HW bwock index
 */
static void ice_init_fwow_pwofs(stwuct ice_hw *hw, u8 bwk_idx)
{
	mutex_init(&hw->fw_pwofs_wocks[bwk_idx]);
	INIT_WIST_HEAD(&hw->fw_pwofs[bwk_idx]);
}

/**
 * ice_cweaw_hw_tbws - cweaw HW tabwes and fwow pwofiwes
 * @hw: pointew to the hawdwawe stwuctuwe
 */
void ice_cweaw_hw_tbws(stwuct ice_hw *hw)
{
	u8 i;

	fow (i = 0; i < ICE_BWK_COUNT; i++) {
		stwuct ice_pwof_wediw *pwof_wediw = &hw->bwk[i].pwof_wediw;
		stwuct ice_pwof_id *pwof_id = &hw->bwk[i].pwof_id;
		stwuct ice_pwof_tcam *pwof = &hw->bwk[i].pwof;
		stwuct ice_xwt1 *xwt1 = &hw->bwk[i].xwt1;
		stwuct ice_xwt2 *xwt2 = &hw->bwk[i].xwt2;
		stwuct ice_es *es = &hw->bwk[i].es;

		if (hw->bwk[i].is_wist_init) {
			ice_fwee_pwof_map(hw, i);
			ice_fwee_fwow_pwofs(hw, i);
		}

		ice_fwee_vsig_tbw(hw, (enum ice_bwock)i);

		memset(xwt1->ptypes, 0, xwt1->count * sizeof(*xwt1->ptypes));
		memset(xwt1->ptg_tbw, 0,
		       ICE_MAX_PTGS * sizeof(*xwt1->ptg_tbw));
		memset(xwt1->t, 0, xwt1->count * sizeof(*xwt1->t));

		memset(xwt2->vsis, 0, xwt2->count * sizeof(*xwt2->vsis));
		memset(xwt2->vsig_tbw, 0,
		       xwt2->count * sizeof(*xwt2->vsig_tbw));
		memset(xwt2->t, 0, xwt2->count * sizeof(*xwt2->t));

		memset(pwof->t, 0, pwof->count * sizeof(*pwof->t));
		memset(pwof_wediw->t, 0,
		       pwof_wediw->count * sizeof(*pwof_wediw->t));

		memset(es->t, 0, es->count * sizeof(*es->t) * es->fvw);
		memset(es->wef_count, 0, es->count * sizeof(*es->wef_count));
		memset(es->symm, 0, es->count * sizeof(*es->symm));
		memset(es->wwitten, 0, es->count * sizeof(*es->wwitten));
		memset(es->mask_ena, 0, es->count * sizeof(*es->mask_ena));

		memset(pwof_id->id, 0, pwof_id->count * sizeof(*pwof_id->id));
	}
}

/**
 * ice_init_hw_tbws - init hawdwawe tabwe memowy
 * @hw: pointew to the hawdwawe stwuctuwe
 */
int ice_init_hw_tbws(stwuct ice_hw *hw)
{
	u8 i;

	mutex_init(&hw->wss_wocks);
	INIT_WIST_HEAD(&hw->wss_wist_head);
	ice_init_aww_pwof_masks(hw);
	fow (i = 0; i < ICE_BWK_COUNT; i++) {
		stwuct ice_pwof_wediw *pwof_wediw = &hw->bwk[i].pwof_wediw;
		stwuct ice_pwof_id *pwof_id = &hw->bwk[i].pwof_id;
		stwuct ice_pwof_tcam *pwof = &hw->bwk[i].pwof;
		stwuct ice_xwt1 *xwt1 = &hw->bwk[i].xwt1;
		stwuct ice_xwt2 *xwt2 = &hw->bwk[i].xwt2;
		stwuct ice_es *es = &hw->bwk[i].es;
		u16 j;

		if (hw->bwk[i].is_wist_init)
			continue;

		ice_init_fwow_pwofs(hw, i);
		mutex_init(&es->pwof_map_wock);
		INIT_WIST_HEAD(&es->pwof_map);
		hw->bwk[i].is_wist_init = twue;

		hw->bwk[i].ovewwwite = bwk_sizes[i].ovewwwite;
		es->wevewse = bwk_sizes[i].wevewse;

		xwt1->sid = ice_bwk_sids[i][ICE_SID_XWT1_OFF];
		xwt1->count = bwk_sizes[i].xwt1;

		xwt1->ptypes = devm_kcawwoc(ice_hw_to_dev(hw), xwt1->count,
					    sizeof(*xwt1->ptypes), GFP_KEWNEW);

		if (!xwt1->ptypes)
			goto eww;

		xwt1->ptg_tbw = devm_kcawwoc(ice_hw_to_dev(hw), ICE_MAX_PTGS,
					     sizeof(*xwt1->ptg_tbw),
					     GFP_KEWNEW);

		if (!xwt1->ptg_tbw)
			goto eww;

		xwt1->t = devm_kcawwoc(ice_hw_to_dev(hw), xwt1->count,
				       sizeof(*xwt1->t), GFP_KEWNEW);
		if (!xwt1->t)
			goto eww;

		xwt2->sid = ice_bwk_sids[i][ICE_SID_XWT2_OFF];
		xwt2->count = bwk_sizes[i].xwt2;

		xwt2->vsis = devm_kcawwoc(ice_hw_to_dev(hw), xwt2->count,
					  sizeof(*xwt2->vsis), GFP_KEWNEW);

		if (!xwt2->vsis)
			goto eww;

		xwt2->vsig_tbw = devm_kcawwoc(ice_hw_to_dev(hw), xwt2->count,
					      sizeof(*xwt2->vsig_tbw),
					      GFP_KEWNEW);
		if (!xwt2->vsig_tbw)
			goto eww;

		fow (j = 0; j < xwt2->count; j++)
			INIT_WIST_HEAD(&xwt2->vsig_tbw[j].pwop_wst);

		xwt2->t = devm_kcawwoc(ice_hw_to_dev(hw), xwt2->count,
				       sizeof(*xwt2->t), GFP_KEWNEW);
		if (!xwt2->t)
			goto eww;

		pwof->sid = ice_bwk_sids[i][ICE_SID_PW_OFF];
		pwof->count = bwk_sizes[i].pwof_tcam;
		pwof->max_pwof_id = bwk_sizes[i].pwof_id;
		pwof->cdid_bits = bwk_sizes[i].pwof_cdid_bits;
		pwof->t = devm_kcawwoc(ice_hw_to_dev(hw), pwof->count,
				       sizeof(*pwof->t), GFP_KEWNEW);

		if (!pwof->t)
			goto eww;

		pwof_wediw->sid = ice_bwk_sids[i][ICE_SID_PW_WEDIW_OFF];
		pwof_wediw->count = bwk_sizes[i].pwof_wediw;
		pwof_wediw->t = devm_kcawwoc(ice_hw_to_dev(hw),
					     pwof_wediw->count,
					     sizeof(*pwof_wediw->t),
					     GFP_KEWNEW);

		if (!pwof_wediw->t)
			goto eww;

		es->sid = ice_bwk_sids[i][ICE_SID_ES_OFF];
		es->count = bwk_sizes[i].es;
		es->fvw = bwk_sizes[i].fvw;
		es->t = devm_kcawwoc(ice_hw_to_dev(hw),
				     (u32)(es->count * es->fvw),
				     sizeof(*es->t), GFP_KEWNEW);
		if (!es->t)
			goto eww;

		es->wef_count = devm_kcawwoc(ice_hw_to_dev(hw), es->count,
					     sizeof(*es->wef_count),
					     GFP_KEWNEW);
		if (!es->wef_count)
			goto eww;

		es->symm = devm_kcawwoc(ice_hw_to_dev(hw), es->count,
					sizeof(*es->symm), GFP_KEWNEW);
		if (!es->symm)
			goto eww;

		es->wwitten = devm_kcawwoc(ice_hw_to_dev(hw), es->count,
					   sizeof(*es->wwitten), GFP_KEWNEW);
		if (!es->wwitten)
			goto eww;

		es->mask_ena = devm_kcawwoc(ice_hw_to_dev(hw), es->count,
					    sizeof(*es->mask_ena), GFP_KEWNEW);
		if (!es->mask_ena)
			goto eww;

		pwof_id->count = bwk_sizes[i].pwof_id;
		pwof_id->id = devm_kcawwoc(ice_hw_to_dev(hw), pwof_id->count,
					   sizeof(*pwof_id->id), GFP_KEWNEW);
		if (!pwof_id->id)
			goto eww;
	}
	wetuwn 0;

eww:
	ice_fwee_hw_tbws(hw);
	wetuwn -ENOMEM;
}

/**
 * ice_pwof_gen_key - genewate pwofiwe ID key
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock in which to wwite pwofiwe ID to
 * @ptg: packet type gwoup (PTG) powtion of key
 * @vsig: VSIG powtion of key
 * @cdid: CDID powtion of key
 * @fwags: fwag powtion of key
 * @vw_msk: vawid mask
 * @dc_msk: don't cawe mask
 * @nm_msk: nevew match mask
 * @key: output of pwofiwe ID key
 */
static int
ice_pwof_gen_key(stwuct ice_hw *hw, enum ice_bwock bwk, u8 ptg, u16 vsig,
		 u8 cdid, u16 fwags, u8 vw_msk[ICE_TCAM_KEY_VAW_SZ],
		 u8 dc_msk[ICE_TCAM_KEY_VAW_SZ], u8 nm_msk[ICE_TCAM_KEY_VAW_SZ],
		 u8 key[ICE_TCAM_KEY_SZ])
{
	stwuct ice_pwof_id_key inkey;

	inkey.xwt1 = ptg;
	inkey.xwt2_cdid = cpu_to_we16(vsig);
	inkey.fwags = cpu_to_we16(fwags);

	switch (hw->bwk[bwk].pwof.cdid_bits) {
	case 0:
		bweak;
	case 2:
#define ICE_CD_2_M 0xC000U
#define ICE_CD_2_S 14
		inkey.xwt2_cdid &= ~cpu_to_we16(ICE_CD_2_M);
		inkey.xwt2_cdid |= cpu_to_we16(BIT(cdid) << ICE_CD_2_S);
		bweak;
	case 4:
#define ICE_CD_4_M 0xF000U
#define ICE_CD_4_S 12
		inkey.xwt2_cdid &= ~cpu_to_we16(ICE_CD_4_M);
		inkey.xwt2_cdid |= cpu_to_we16(BIT(cdid) << ICE_CD_4_S);
		bweak;
	case 8:
#define ICE_CD_8_M 0xFF00U
#define ICE_CD_8_S 16
		inkey.xwt2_cdid &= ~cpu_to_we16(ICE_CD_8_M);
		inkey.xwt2_cdid |= cpu_to_we16(BIT(cdid) << ICE_CD_8_S);
		bweak;
	defauwt:
		ice_debug(hw, ICE_DBG_PKG, "Ewwow in pwofiwe config\n");
		bweak;
	}

	wetuwn ice_set_key(key, ICE_TCAM_KEY_SZ, (u8 *)&inkey, vw_msk, dc_msk,
			   nm_msk, 0, ICE_TCAM_KEY_SZ / 2);
}

/**
 * ice_tcam_wwite_entwy - wwite TCAM entwy
 * @hw: pointew to the HW stwuct
 * @bwk: the bwock in which to wwite pwofiwe ID to
 * @idx: the entwy index to wwite to
 * @pwof_id: pwofiwe ID
 * @ptg: packet type gwoup (PTG) powtion of key
 * @vsig: VSIG powtion of key
 * @cdid: CDID powtion of key
 * @fwags: fwag powtion of key
 * @vw_msk: vawid mask
 * @dc_msk: don't cawe mask
 * @nm_msk: nevew match mask
 */
static int
ice_tcam_wwite_entwy(stwuct ice_hw *hw, enum ice_bwock bwk, u16 idx,
		     u8 pwof_id, u8 ptg, u16 vsig, u8 cdid, u16 fwags,
		     u8 vw_msk[ICE_TCAM_KEY_VAW_SZ],
		     u8 dc_msk[ICE_TCAM_KEY_VAW_SZ],
		     u8 nm_msk[ICE_TCAM_KEY_VAW_SZ])
{
	stwuct ice_pwof_tcam_entwy;
	int status;

	status = ice_pwof_gen_key(hw, bwk, ptg, vsig, cdid, fwags, vw_msk,
				  dc_msk, nm_msk, hw->bwk[bwk].pwof.t[idx].key);
	if (!status) {
		hw->bwk[bwk].pwof.t[idx].addw = cpu_to_we16(idx);
		hw->bwk[bwk].pwof.t[idx].pwof_id = pwof_id;
	}

	wetuwn status;
}

/**
 * ice_vsig_get_wef - wetuwns numbew of VSIs bewong to a VSIG
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsig: VSIG to quewy
 * @wefs: pointew to vawiabwe to weceive the wefewence count
 */
static int
ice_vsig_get_wef(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig, u16 *wefs)
{
	u16 idx = vsig & ICE_VSIG_IDX_M;
	stwuct ice_vsig_vsi *ptw;

	*wefs = 0;

	if (!hw->bwk[bwk].xwt2.vsig_tbw[idx].in_use)
		wetuwn -ENOENT;

	ptw = hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi;
	whiwe (ptw) {
		(*wefs)++;
		ptw = ptw->next_vsi;
	}

	wetuwn 0;
}

/**
 * ice_has_pwof_vsig - check to see if VSIG has a specific pwofiwe
 * @hw: pointew to the hawdwawe stwuctuwe
 * @bwk: HW bwock
 * @vsig: VSIG to check against
 * @hdw: pwofiwe handwe
 */
static boow
ice_has_pwof_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig, u64 hdw)
{
	u16 idx = vsig & ICE_VSIG_IDX_M;
	stwuct ice_vsig_pwof *ent;

	wist_fow_each_entwy(ent, &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
			    wist)
		if (ent->pwofiwe_cookie == hdw)
			wetuwn twue;

	ice_debug(hw, ICE_DBG_INIT, "Chawactewistic wist fow VSI gwoup %d not found.\n",
		  vsig);
	wetuwn fawse;
}

/**
 * ice_pwof_bwd_es - buiwd pwofiwe ID extwaction sequence changes
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @bwd: the update package buffew buiwd to add to
 * @chgs: the wist of changes to make in hawdwawe
 */
static int
ice_pwof_bwd_es(stwuct ice_hw *hw, enum ice_bwock bwk,
		stwuct ice_buf_buiwd *bwd, stwuct wist_head *chgs)
{
	u16 vec_size = hw->bwk[bwk].es.fvw * sizeof(stwuct ice_fv_wowd);
	stwuct ice_chs_chg *tmp;

	wist_fow_each_entwy(tmp, chgs, wist_entwy)
		if (tmp->type == ICE_PTG_ES_ADD && tmp->add_pwof) {
			u16 off = tmp->pwof_id * hw->bwk[bwk].es.fvw;
			stwuct ice_pkg_es *p;
			u32 id;

			id = ice_sect_id(bwk, ICE_VEC_TBW);
			p = ice_pkg_buf_awwoc_section(bwd, id,
						      stwuct_size(p, es, 1) +
						      vec_size -
						      sizeof(p->es[0]));

			if (!p)
				wetuwn -ENOSPC;

			p->count = cpu_to_we16(1);
			p->offset = cpu_to_we16(tmp->pwof_id);

			memcpy(p->es, &hw->bwk[bwk].es.t[off], vec_size);
		}

	wetuwn 0;
}

/**
 * ice_pwof_bwd_tcam - buiwd pwofiwe ID TCAM changes
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @bwd: the update package buffew buiwd to add to
 * @chgs: the wist of changes to make in hawdwawe
 */
static int
ice_pwof_bwd_tcam(stwuct ice_hw *hw, enum ice_bwock bwk,
		  stwuct ice_buf_buiwd *bwd, stwuct wist_head *chgs)
{
	stwuct ice_chs_chg *tmp;

	wist_fow_each_entwy(tmp, chgs, wist_entwy)
		if (tmp->type == ICE_TCAM_ADD && tmp->add_tcam_idx) {
			stwuct ice_pwof_id_section *p;
			u32 id;

			id = ice_sect_id(bwk, ICE_PWOF_TCAM);
			p = ice_pkg_buf_awwoc_section(bwd, id,
						      stwuct_size(p, entwy, 1));

			if (!p)
				wetuwn -ENOSPC;

			p->count = cpu_to_we16(1);
			p->entwy[0].addw = cpu_to_we16(tmp->tcam_idx);
			p->entwy[0].pwof_id = tmp->pwof_id;

			memcpy(p->entwy[0].key,
			       &hw->bwk[bwk].pwof.t[tmp->tcam_idx].key,
			       sizeof(hw->bwk[bwk].pwof.t->key));
		}

	wetuwn 0;
}

/**
 * ice_pwof_bwd_xwt1 - buiwd XWT1 changes
 * @bwk: hawdwawe bwock
 * @bwd: the update package buffew buiwd to add to
 * @chgs: the wist of changes to make in hawdwawe
 */
static int
ice_pwof_bwd_xwt1(enum ice_bwock bwk, stwuct ice_buf_buiwd *bwd,
		  stwuct wist_head *chgs)
{
	stwuct ice_chs_chg *tmp;

	wist_fow_each_entwy(tmp, chgs, wist_entwy)
		if (tmp->type == ICE_PTG_ES_ADD && tmp->add_ptg) {
			stwuct ice_xwt1_section *p;
			u32 id;

			id = ice_sect_id(bwk, ICE_XWT1);
			p = ice_pkg_buf_awwoc_section(bwd, id,
						      stwuct_size(p, vawue, 1));

			if (!p)
				wetuwn -ENOSPC;

			p->count = cpu_to_we16(1);
			p->offset = cpu_to_we16(tmp->ptype);
			p->vawue[0] = tmp->ptg;
		}

	wetuwn 0;
}

/**
 * ice_pwof_bwd_xwt2 - buiwd XWT2 changes
 * @bwk: hawdwawe bwock
 * @bwd: the update package buffew buiwd to add to
 * @chgs: the wist of changes to make in hawdwawe
 */
static int
ice_pwof_bwd_xwt2(enum ice_bwock bwk, stwuct ice_buf_buiwd *bwd,
		  stwuct wist_head *chgs)
{
	stwuct ice_chs_chg *tmp;

	wist_fow_each_entwy(tmp, chgs, wist_entwy) {
		stwuct ice_xwt2_section *p;
		u32 id;

		switch (tmp->type) {
		case ICE_VSIG_ADD:
		case ICE_VSI_MOVE:
		case ICE_VSIG_WEM:
			id = ice_sect_id(bwk, ICE_XWT2);
			p = ice_pkg_buf_awwoc_section(bwd, id,
						      stwuct_size(p, vawue, 1));

			if (!p)
				wetuwn -ENOSPC;

			p->count = cpu_to_we16(1);
			p->offset = cpu_to_we16(tmp->vsi);
			p->vawue[0] = cpu_to_we16(tmp->vsig);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;
}

/**
 * ice_upd_pwof_hw - update hawdwawe using the change wist
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @chgs: the wist of changes to make in hawdwawe
 */
static int
ice_upd_pwof_hw(stwuct ice_hw *hw, enum ice_bwock bwk,
		stwuct wist_head *chgs)
{
	stwuct ice_buf_buiwd *b;
	stwuct ice_chs_chg *tmp;
	u16 pkg_sects;
	u16 xwt1 = 0;
	u16 xwt2 = 0;
	u16 tcam = 0;
	u16 es = 0;
	int status;
	u16 sects;

	/* count numbew of sections we need */
	wist_fow_each_entwy(tmp, chgs, wist_entwy) {
		switch (tmp->type) {
		case ICE_PTG_ES_ADD:
			if (tmp->add_ptg)
				xwt1++;
			if (tmp->add_pwof)
				es++;
			bweak;
		case ICE_TCAM_ADD:
			tcam++;
			bweak;
		case ICE_VSIG_ADD:
		case ICE_VSI_MOVE:
		case ICE_VSIG_WEM:
			xwt2++;
			bweak;
		defauwt:
			bweak;
		}
	}
	sects = xwt1 + xwt2 + tcam + es;

	if (!sects)
		wetuwn 0;

	/* Buiwd update package buffew */
	b = ice_pkg_buf_awwoc(hw);
	if (!b)
		wetuwn -ENOMEM;

	status = ice_pkg_buf_wesewve_section(b, sects);
	if (status)
		goto ewwow_tmp;

	/* Pwesewve owdew of tabwe update: ES, TCAM, PTG, VSIG */
	if (es) {
		status = ice_pwof_bwd_es(hw, bwk, b, chgs);
		if (status)
			goto ewwow_tmp;
	}

	if (tcam) {
		status = ice_pwof_bwd_tcam(hw, bwk, b, chgs);
		if (status)
			goto ewwow_tmp;
	}

	if (xwt1) {
		status = ice_pwof_bwd_xwt1(bwk, b, chgs);
		if (status)
			goto ewwow_tmp;
	}

	if (xwt2) {
		status = ice_pwof_bwd_xwt2(bwk, b, chgs);
		if (status)
			goto ewwow_tmp;
	}

	/* Aftew package buffew buiwd check if the section count in buffew is
	 * non-zewo and matches the numbew of sections detected fow package
	 * update.
	 */
	pkg_sects = ice_pkg_buf_get_active_sections(b);
	if (!pkg_sects || pkg_sects != sects) {
		status = -EINVAW;
		goto ewwow_tmp;
	}

	/* update package */
	status = ice_update_pkg(hw, ice_pkg_buf(b), 1);
	if (status == -EIO)
		ice_debug(hw, ICE_DBG_INIT, "Unabwe to update HW pwofiwe\n");

ewwow_tmp:
	ice_pkg_buf_fwee(hw, b);
	wetuwn status;
}

/**
 * ice_update_fd_mask - set Fwow Diwectow Fiewd Vectow mask fow a pwofiwe
 * @hw: pointew to the HW stwuct
 * @pwof_id: pwofiwe ID
 * @mask_sew: mask sewect
 *
 * This function enabwe any of the masks sewected by the mask sewect pawametew
 * fow the pwofiwe specified.
 */
static void ice_update_fd_mask(stwuct ice_hw *hw, u16 pwof_id, u32 mask_sew)
{
	ww32(hw, GWQF_FDMASK_SEW(pwof_id), mask_sew);

	ice_debug(hw, ICE_DBG_INIT, "fd mask(%d): %x = %x\n", pwof_id,
		  GWQF_FDMASK_SEW(pwof_id), mask_sew);
}

stwuct ice_fd_swc_dst_paiw {
	u8 pwot_id;
	u8 count;
	u16 off;
};

static const stwuct ice_fd_swc_dst_paiw ice_fd_paiws[] = {
	/* These awe defined in paiws */
	{ ICE_PWOT_IPV4_OF_OW_S, 2, 12 },
	{ ICE_PWOT_IPV4_OF_OW_S, 2, 16 },

	{ ICE_PWOT_IPV4_IW, 2, 12 },
	{ ICE_PWOT_IPV4_IW, 2, 16 },

	{ ICE_PWOT_IPV6_OF_OW_S, 8, 8 },
	{ ICE_PWOT_IPV6_OF_OW_S, 8, 24 },

	{ ICE_PWOT_IPV6_IW, 8, 8 },
	{ ICE_PWOT_IPV6_IW, 8, 24 },

	{ ICE_PWOT_TCP_IW, 1, 0 },
	{ ICE_PWOT_TCP_IW, 1, 2 },

	{ ICE_PWOT_UDP_OF, 1, 0 },
	{ ICE_PWOT_UDP_OF, 1, 2 },

	{ ICE_PWOT_UDP_IW_OW_S, 1, 0 },
	{ ICE_PWOT_UDP_IW_OW_S, 1, 2 },

	{ ICE_PWOT_SCTP_IW, 1, 0 },
	{ ICE_PWOT_SCTP_IW, 1, 2 }
};

#define ICE_FD_SWC_DST_PAIW_COUNT	AWWAY_SIZE(ice_fd_paiws)

/**
 * ice_update_fd_swap - set wegistew appwopwiatewy fow a FD FV extwaction
 * @hw: pointew to the HW stwuct
 * @pwof_id: pwofiwe ID
 * @es: extwaction sequence (wength of awway is detewmined by the bwock)
 */
static int
ice_update_fd_swap(stwuct ice_hw *hw, u16 pwof_id, stwuct ice_fv_wowd *es)
{
	DECWAWE_BITMAP(paiw_wist, ICE_FD_SWC_DST_PAIW_COUNT);
	u8 paiw_stawt[ICE_FD_SWC_DST_PAIW_COUNT] = { 0 };
#define ICE_FD_FV_NOT_FOUND (-2)
	s8 fiwst_fwee = ICE_FD_FV_NOT_FOUND;
	u8 used[ICE_MAX_FV_WOWDS] = { 0 };
	s8 owig_fwee, si;
	u32 mask_sew = 0;
	u8 i, j, k;

	bitmap_zewo(paiw_wist, ICE_FD_SWC_DST_PAIW_COUNT);

	/* This code assumes that the Fwow Diwectow fiewd vectows awe assigned
	 * fwom the end of the FV indexes wowking towawds the zewo index, that
	 * onwy compwete fiewds wiww be incwuded and wiww be consecutive, and
	 * that thewe awe no gaps between vawid indexes.
	 */

	/* Detewmine swap fiewds pwesent */
	fow (i = 0; i < hw->bwk[ICE_BWK_FD].es.fvw; i++) {
		/* Find the fiwst fwee entwy, assuming wight to weft popuwation.
		 * This is whewe we can stawt adding additionaw paiws if needed.
		 */
		if (fiwst_fwee == ICE_FD_FV_NOT_FOUND && es[i].pwot_id !=
		    ICE_PWOT_INVAWID)
			fiwst_fwee = i - 1;

		fow (j = 0; j < ICE_FD_SWC_DST_PAIW_COUNT; j++)
			if (es[i].pwot_id == ice_fd_paiws[j].pwot_id &&
			    es[i].off == ice_fd_paiws[j].off) {
				__set_bit(j, paiw_wist);
				paiw_stawt[j] = i;
			}
	}

	owig_fwee = fiwst_fwee;

	/* detewmine missing swap fiewds that need to be added */
	fow (i = 0; i < ICE_FD_SWC_DST_PAIW_COUNT; i += 2) {
		u8 bit1 = test_bit(i + 1, paiw_wist);
		u8 bit0 = test_bit(i, paiw_wist);

		if (bit0 ^ bit1) {
			u8 index;

			/* add the appwopwiate 'paiwed' entwy */
			if (!bit0)
				index = i;
			ewse
				index = i + 1;

			/* check fow woom */
			if (fiwst_fwee + 1 < (s8)ice_fd_paiws[index].count)
				wetuwn -ENOSPC;

			/* pwace in extwaction sequence */
			fow (k = 0; k < ice_fd_paiws[index].count; k++) {
				es[fiwst_fwee - k].pwot_id =
					ice_fd_paiws[index].pwot_id;
				es[fiwst_fwee - k].off =
					ice_fd_paiws[index].off + (k * 2);

				if (k > fiwst_fwee)
					wetuwn -EIO;

				/* keep twack of non-wewevant fiewds */
				mask_sew |= BIT(fiwst_fwee - k);
			}

			paiw_stawt[index] = fiwst_fwee;
			fiwst_fwee -= ice_fd_paiws[index].count;
		}
	}

	/* fiww in the swap awway */
	si = hw->bwk[ICE_BWK_FD].es.fvw - 1;
	whiwe (si >= 0) {
		u8 indexes_used = 1;

		/* assume fwat at this index */
#define ICE_SWAP_VAWID	0x80
		used[si] = si | ICE_SWAP_VAWID;

		if (owig_fwee == ICE_FD_FV_NOT_FOUND || si <= owig_fwee) {
			si -= indexes_used;
			continue;
		}

		/* check fow a swap wocation */
		fow (j = 0; j < ICE_FD_SWC_DST_PAIW_COUNT; j++)
			if (es[si].pwot_id == ice_fd_paiws[j].pwot_id &&
			    es[si].off == ice_fd_paiws[j].off) {
				u8 idx;

				/* detewmine the appwopwiate matching fiewd */
				idx = j + ((j % 2) ? -1 : 1);

				indexes_used = ice_fd_paiws[idx].count;
				fow (k = 0; k < indexes_used; k++) {
					used[si - k] = (paiw_stawt[idx] - k) |
						ICE_SWAP_VAWID;
				}

				bweak;
			}

		si -= indexes_used;
	}

	/* fow each set of 4 swap and 4 inset indexes, wwite the appwopwiate
	 * wegistew
	 */
	fow (j = 0; j < hw->bwk[ICE_BWK_FD].es.fvw / 4; j++) {
		u32 waw_swap = 0;
		u32 waw_in = 0;

		fow (k = 0; k < 4; k++) {
			u8 idx;

			idx = (j * 4) + k;
			if (used[idx] && !(mask_sew & BIT(idx))) {
				waw_swap |= used[idx] << (k * BITS_PEW_BYTE);
#define ICE_INSET_DFWT 0x9f
				waw_in |= ICE_INSET_DFWT << (k * BITS_PEW_BYTE);
			}
		}

		/* wwite the appwopwiate swap wegistew set */
		ww32(hw, GWQF_FDSWAP(pwof_id, j), waw_swap);

		ice_debug(hw, ICE_DBG_INIT, "swap ww(%d, %d): %x = %08x\n",
			  pwof_id, j, GWQF_FDSWAP(pwof_id, j), waw_swap);

		/* wwite the appwopwiate inset wegistew set */
		ww32(hw, GWQF_FDINSET(pwof_id, j), waw_in);

		ice_debug(hw, ICE_DBG_INIT, "inset ww(%d, %d): %x = %08x\n",
			  pwof_id, j, GWQF_FDINSET(pwof_id, j), waw_in);
	}

	/* initiawwy cweaw the mask sewect fow this pwofiwe */
	ice_update_fd_mask(hw, pwof_id, 0);

	wetuwn 0;
}

/* The entwies hewe needs to match the owdew of enum ice_ptype_attwib */
static const stwuct ice_ptype_attwib_info ice_ptype_attwibutes[] = {
	{ ICE_GTP_PDU_EH,	ICE_GTP_PDU_FWAG_MASK },
	{ ICE_GTP_SESSION,	ICE_GTP_FWAGS_MASK },
	{ ICE_GTP_DOWNWINK,	ICE_GTP_FWAGS_MASK },
	{ ICE_GTP_UPWINK,	ICE_GTP_FWAGS_MASK },
};

/**
 * ice_get_ptype_attwib_info - get PTYPE attwibute infowmation
 * @type: attwibute type
 * @info: pointew to vawiabwe to the attwibute infowmation
 */
static void
ice_get_ptype_attwib_info(enum ice_ptype_attwib_type type,
			  stwuct ice_ptype_attwib_info *info)
{
	*info = ice_ptype_attwibutes[type];
}

/**
 * ice_add_pwof_attwib - add any PTG with attwibutes to pwofiwe
 * @pwof: pointew to the pwofiwe to which PTG entwies wiww be added
 * @ptg: PTG to be added
 * @ptype: PTYPE that needs to be wooked up
 * @attw: awway of attwibutes that wiww be considewed
 * @attw_cnt: numbew of ewements in the attwibute awway
 */
static int
ice_add_pwof_attwib(stwuct ice_pwof_map *pwof, u8 ptg, u16 ptype,
		    const stwuct ice_ptype_attwibutes *attw, u16 attw_cnt)
{
	boow found = fawse;
	u16 i;

	fow (i = 0; i < attw_cnt; i++)
		if (attw[i].ptype == ptype) {
			found = twue;

			pwof->ptg[pwof->ptg_cnt] = ptg;
			ice_get_ptype_attwib_info(attw[i].attwib,
						  &pwof->attw[pwof->ptg_cnt]);

			if (++pwof->ptg_cnt >= ICE_MAX_PTG_PEW_PWOFIWE)
				wetuwn -ENOSPC;
		}

	if (!found)
		wetuwn -ENOENT;

	wetuwn 0;
}

/**
 * ice_add_pwof - add pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @id: pwofiwe twacking ID
 * @ptypes: awway of bitmaps indicating ptypes (ICE_FWOW_PTYPE_MAX bits)
 * @attw: awway of attwibutes
 * @attw_cnt: numbew of ewements in attw awway
 * @es: extwaction sequence (wength of awway is detewmined by the bwock)
 * @masks: mask fow extwaction sequence
 * @symm: symmetwic setting fow WSS pwofiwes
 *
 * This function wegistews a pwofiwe, which matches a set of PTYPES with a
 * pawticuwaw extwaction sequence. Whiwe the hawdwawe pwofiwe is awwocated
 * it wiww not be wwitten untiw the fiwst caww to ice_add_fwow that specifies
 * the ID vawue used hewe.
 */
int
ice_add_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id, u8 ptypes[],
	     const stwuct ice_ptype_attwibutes *attw, u16 attw_cnt,
	     stwuct ice_fv_wowd *es, u16 *masks, boow symm)
{
	u32 bytes = DIV_WOUND_UP(ICE_FWOW_PTYPE_MAX, BITS_PEW_BYTE);
	DECWAWE_BITMAP(ptgs_used, ICE_XWT1_CNT);
	stwuct ice_pwof_map *pwof;
	u8 byte = 0;
	u8 pwof_id;
	int status;

	bitmap_zewo(ptgs_used, ICE_XWT1_CNT);

	mutex_wock(&hw->bwk[bwk].es.pwof_map_wock);

	/* seawch fow existing pwofiwe */
	status = ice_find_pwof_id_with_mask(hw, bwk, es, masks, symm, &pwof_id);
	if (status) {
		/* awwocate pwofiwe ID */
		status = ice_awwoc_pwof_id(hw, bwk, &pwof_id);
		if (status)
			goto eww_ice_add_pwof;
		if (bwk == ICE_BWK_FD) {
			/* Fow Fwow Diwectow bwock, the extwaction sequence may
			 * need to be awtewed in the case whewe thewe awe paiwed
			 * fiewds that have no match. This is necessawy because
			 * fow Fwow Diwectow, swc and dest fiewds need to paiwed
			 * fow fiwtew pwogwamming and these vawues awe swapped
			 * duwing Tx.
			 */
			status = ice_update_fd_swap(hw, pwof_id, es);
			if (status)
				goto eww_ice_add_pwof;
		}
		status = ice_update_pwof_masking(hw, bwk, pwof_id, masks);
		if (status)
			goto eww_ice_add_pwof;

		/* and wwite new es */
		ice_wwite_es(hw, bwk, pwof_id, es, symm);
	}

	ice_pwof_inc_wef(hw, bwk, pwof_id);

	/* add pwofiwe info */
	pwof = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*pwof), GFP_KEWNEW);
	if (!pwof) {
		status = -ENOMEM;
		goto eww_ice_add_pwof;
	}

	pwof->pwofiwe_cookie = id;
	pwof->pwof_id = pwof_id;
	pwof->ptg_cnt = 0;
	pwof->context = 0;

	/* buiwd wist of ptgs */
	whiwe (bytes && pwof->ptg_cnt < ICE_MAX_PTG_PEW_PWOFIWE) {
		u8 bit;

		if (!ptypes[byte]) {
			bytes--;
			byte++;
			continue;
		}

		/* Examine 8 bits pew byte */
		fow_each_set_bit(bit, (unsigned wong *)&ptypes[byte],
				 BITS_PEW_BYTE) {
			u16 ptype;
			u8 ptg;

			ptype = byte * BITS_PEW_BYTE + bit;

			/* The package shouwd pwace aww ptypes in a non-zewo
			 * PTG, so the fowwowing caww shouwd nevew faiw.
			 */
			if (ice_ptg_find_ptype(hw, bwk, ptype, &ptg))
				continue;

			/* If PTG is awweady added, skip and continue */
			if (test_bit(ptg, ptgs_used))
				continue;

			__set_bit(ptg, ptgs_used);
			/* Check to see thewe awe any attwibutes fow
			 * this PTYPE, and add them if found.
			 */
			status = ice_add_pwof_attwib(pwof, ptg, ptype,
						     attw, attw_cnt);
			if (status == -ENOSPC)
				bweak;
			if (status) {
				/* This is simpwe a PTYPE/PTG with no
				 * attwibute
				 */
				pwof->ptg[pwof->ptg_cnt] = ptg;
				pwof->attw[pwof->ptg_cnt].fwags = 0;
				pwof->attw[pwof->ptg_cnt].mask = 0;

				if (++pwof->ptg_cnt >=
				    ICE_MAX_PTG_PEW_PWOFIWE)
					bweak;
			}
		}

		bytes--;
		byte++;
	}

	wist_add(&pwof->wist, &hw->bwk[bwk].es.pwof_map);
	status = 0;

eww_ice_add_pwof:
	mutex_unwock(&hw->bwk[bwk].es.pwof_map_wock);
	wetuwn status;
}

/**
 * ice_seawch_pwof_id - Seawch fow a pwofiwe twacking ID
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @id: pwofiwe twacking ID
 *
 * This wiww seawch fow a pwofiwe twacking ID which was pweviouswy added.
 * The pwofiwe map wock shouwd be hewd befowe cawwing this function.
 */
stwuct ice_pwof_map *
ice_seawch_pwof_id(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id)
{
	stwuct ice_pwof_map *entwy = NUWW;
	stwuct ice_pwof_map *map;

	wist_fow_each_entwy(map, &hw->bwk[bwk].es.pwof_map, wist)
		if (map->pwofiwe_cookie == id) {
			entwy = map;
			bweak;
		}

	wetuwn entwy;
}

/**
 * ice_vsig_pwof_id_count - count pwofiwes in a VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsig: VSIG to wemove the pwofiwe fwom
 */
static u16
ice_vsig_pwof_id_count(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig)
{
	u16 idx = vsig & ICE_VSIG_IDX_M, count = 0;
	stwuct ice_vsig_pwof *p;

	wist_fow_each_entwy(p, &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
			    wist)
		count++;

	wetuwn count;
}

/**
 * ice_wew_tcam_idx - wewease a TCAM index
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @idx: the index to wewease
 */
static int ice_wew_tcam_idx(stwuct ice_hw *hw, enum ice_bwock bwk, u16 idx)
{
	/* Masks to invoke a nevew match entwy */
	u8 vw_msk[ICE_TCAM_KEY_VAW_SZ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	u8 dc_msk[ICE_TCAM_KEY_VAW_SZ] = { 0xFE, 0xFF, 0xFF, 0xFF, 0xFF };
	u8 nm_msk[ICE_TCAM_KEY_VAW_SZ] = { 0x01, 0x00, 0x00, 0x00, 0x00 };
	int status;

	/* wwite the TCAM entwy */
	status = ice_tcam_wwite_entwy(hw, bwk, idx, 0, 0, 0, 0, 0, vw_msk,
				      dc_msk, nm_msk);
	if (status)
		wetuwn status;

	/* wewease the TCAM entwy */
	status = ice_fwee_tcam_ent(hw, bwk, idx);

	wetuwn status;
}

/**
 * ice_wem_pwof_id - wemove one pwofiwe fwom a VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @pwof: pointew to pwofiwe stwuctuwe to wemove
 */
static int
ice_wem_pwof_id(stwuct ice_hw *hw, enum ice_bwock bwk,
		stwuct ice_vsig_pwof *pwof)
{
	int status;
	u16 i;

	fow (i = 0; i < pwof->tcam_count; i++)
		if (pwof->tcam[i].in_use) {
			pwof->tcam[i].in_use = fawse;
			status = ice_wew_tcam_idx(hw, bwk,
						  pwof->tcam[i].tcam_idx);
			if (status)
				wetuwn -EIO;
		}

	wetuwn 0;
}

/**
 * ice_wem_vsig - wemove VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsig: the VSIG to wemove
 * @chg: the change wist
 */
static int
ice_wem_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig,
	     stwuct wist_head *chg)
{
	u16 idx = vsig & ICE_VSIG_IDX_M;
	stwuct ice_vsig_vsi *vsi_cuw;
	stwuct ice_vsig_pwof *d, *t;

	/* wemove TCAM entwies */
	wist_fow_each_entwy_safe(d, t,
				 &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
				 wist) {
		int status;

		status = ice_wem_pwof_id(hw, bwk, d);
		if (status)
			wetuwn status;

		wist_dew(&d->wist);
		devm_kfwee(ice_hw_to_dev(hw), d);
	}

	/* Move aww VSIS associated with this VSIG to the defauwt VSIG */
	vsi_cuw = hw->bwk[bwk].xwt2.vsig_tbw[idx].fiwst_vsi;
	/* If the VSIG has at weast 1 VSI then itewate thwough the wist
	 * and wemove the VSIs befowe deweting the gwoup.
	 */
	if (vsi_cuw)
		do {
			stwuct ice_vsig_vsi *tmp = vsi_cuw->next_vsi;
			stwuct ice_chs_chg *p;

			p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p),
					 GFP_KEWNEW);
			if (!p)
				wetuwn -ENOMEM;

			p->type = ICE_VSIG_WEM;
			p->owig_vsig = vsig;
			p->vsig = ICE_DEFAUWT_VSIG;
			p->vsi = vsi_cuw - hw->bwk[bwk].xwt2.vsis;

			wist_add(&p->wist_entwy, chg);

			vsi_cuw = tmp;
		} whiwe (vsi_cuw);

	wetuwn ice_vsig_fwee(hw, bwk, vsig);
}

/**
 * ice_wem_pwof_id_vsig - wemove a specific pwofiwe fwom a VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsig: VSIG to wemove the pwofiwe fwom
 * @hdw: pwofiwe handwe indicating which pwofiwe to wemove
 * @chg: wist to weceive a wecowd of changes
 */
static int
ice_wem_pwof_id_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig, u64 hdw,
		     stwuct wist_head *chg)
{
	u16 idx = vsig & ICE_VSIG_IDX_M;
	stwuct ice_vsig_pwof *p, *t;

	wist_fow_each_entwy_safe(p, t,
				 &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
				 wist)
		if (p->pwofiwe_cookie == hdw) {
			int status;

			if (ice_vsig_pwof_id_count(hw, bwk, vsig) == 1)
				/* this is the wast pwofiwe, wemove the VSIG */
				wetuwn ice_wem_vsig(hw, bwk, vsig, chg);

			status = ice_wem_pwof_id(hw, bwk, p);
			if (!status) {
				wist_dew(&p->wist);
				devm_kfwee(ice_hw_to_dev(hw), p);
			}
			wetuwn status;
		}

	wetuwn -ENOENT;
}

/**
 * ice_wem_fwow_aww - wemove aww fwows with a pawticuwaw pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @id: pwofiwe twacking ID
 */
static int ice_wem_fwow_aww(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id)
{
	stwuct ice_chs_chg *dew, *tmp;
	stwuct wist_head chg;
	int status;
	u16 i;

	INIT_WIST_HEAD(&chg);

	fow (i = 1; i < ICE_MAX_VSIGS; i++)
		if (hw->bwk[bwk].xwt2.vsig_tbw[i].in_use) {
			if (ice_has_pwof_vsig(hw, bwk, i, id)) {
				status = ice_wem_pwof_id_vsig(hw, bwk, i, id,
							      &chg);
				if (status)
					goto eww_ice_wem_fwow_aww;
			}
		}

	status = ice_upd_pwof_hw(hw, bwk, &chg);

eww_ice_wem_fwow_aww:
	wist_fow_each_entwy_safe(dew, tmp, &chg, wist_entwy) {
		wist_dew(&dew->wist_entwy);
		devm_kfwee(ice_hw_to_dev(hw), dew);
	}

	wetuwn status;
}

/**
 * ice_wem_pwof - wemove pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @id: pwofiwe twacking ID
 *
 * This wiww wemove the pwofiwe specified by the ID pawametew, which was
 * pweviouswy cweated thwough ice_add_pwof. If any existing entwies
 * awe associated with this pwofiwe, they wiww be wemoved as weww.
 */
int ice_wem_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, u64 id)
{
	stwuct ice_pwof_map *pmap;
	int status;

	mutex_wock(&hw->bwk[bwk].es.pwof_map_wock);

	pmap = ice_seawch_pwof_id(hw, bwk, id);
	if (!pmap) {
		status = -ENOENT;
		goto eww_ice_wem_pwof;
	}

	/* wemove aww fwows with this pwofiwe */
	status = ice_wem_fwow_aww(hw, bwk, pmap->pwofiwe_cookie);
	if (status)
		goto eww_ice_wem_pwof;

	/* dewefewence pwofiwe, and possibwy wemove */
	ice_pwof_dec_wef(hw, bwk, pmap->pwof_id);

	wist_dew(&pmap->wist);
	devm_kfwee(ice_hw_to_dev(hw), pmap);

eww_ice_wem_pwof:
	mutex_unwock(&hw->bwk[bwk].es.pwof_map_wock);
	wetuwn status;
}

/**
 * ice_get_pwof - get pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @hdw: pwofiwe handwe
 * @chg: change wist
 */
static int
ice_get_pwof(stwuct ice_hw *hw, enum ice_bwock bwk, u64 hdw,
	     stwuct wist_head *chg)
{
	stwuct ice_pwof_map *map;
	stwuct ice_chs_chg *p;
	int status = 0;
	u16 i;

	mutex_wock(&hw->bwk[bwk].es.pwof_map_wock);
	/* Get the detaiws on the pwofiwe specified by the handwe ID */
	map = ice_seawch_pwof_id(hw, bwk, hdw);
	if (!map) {
		status = -ENOENT;
		goto eww_ice_get_pwof;
	}

	fow (i = 0; i < map->ptg_cnt; i++)
		if (!hw->bwk[bwk].es.wwitten[map->pwof_id]) {
			/* add ES to change wist */
			p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p),
					 GFP_KEWNEW);
			if (!p) {
				status = -ENOMEM;
				goto eww_ice_get_pwof;
			}

			p->type = ICE_PTG_ES_ADD;
			p->ptype = 0;
			p->ptg = map->ptg[i];
			p->add_ptg = 0;

			p->add_pwof = 1;
			p->pwof_id = map->pwof_id;

			hw->bwk[bwk].es.wwitten[map->pwof_id] = twue;

			wist_add(&p->wist_entwy, chg);
		}

eww_ice_get_pwof:
	mutex_unwock(&hw->bwk[bwk].es.pwof_map_wock);
	/* wet cawwew cwean up the change wist */
	wetuwn status;
}

/**
 * ice_get_pwofs_vsig - get a copy of the wist of pwofiwes fwom a VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsig: VSIG fwom which to copy the wist
 * @wst: output wist
 *
 * This woutine makes a copy of the wist of pwofiwes in the specified VSIG.
 */
static int
ice_get_pwofs_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig,
		   stwuct wist_head *wst)
{
	stwuct ice_vsig_pwof *ent1, *ent2;
	u16 idx = vsig & ICE_VSIG_IDX_M;

	wist_fow_each_entwy(ent1, &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
			    wist) {
		stwuct ice_vsig_pwof *p;

		/* copy to the input wist */
		p = devm_kmemdup(ice_hw_to_dev(hw), ent1, sizeof(*p),
				 GFP_KEWNEW);
		if (!p)
			goto eww_ice_get_pwofs_vsig;

		wist_add_taiw(&p->wist, wst);
	}

	wetuwn 0;

eww_ice_get_pwofs_vsig:
	wist_fow_each_entwy_safe(ent1, ent2, wst, wist) {
		wist_dew(&ent1->wist);
		devm_kfwee(ice_hw_to_dev(hw), ent1);
	}

	wetuwn -ENOMEM;
}

/**
 * ice_add_pwof_to_wst - add pwofiwe entwy to a wist
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @wst: the wist to be added to
 * @hdw: pwofiwe handwe of entwy to add
 */
static int
ice_add_pwof_to_wst(stwuct ice_hw *hw, enum ice_bwock bwk,
		    stwuct wist_head *wst, u64 hdw)
{
	stwuct ice_pwof_map *map;
	stwuct ice_vsig_pwof *p;
	int status = 0;
	u16 i;

	mutex_wock(&hw->bwk[bwk].es.pwof_map_wock);
	map = ice_seawch_pwof_id(hw, bwk, hdw);
	if (!map) {
		status = -ENOENT;
		goto eww_ice_add_pwof_to_wst;
	}

	p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p), GFP_KEWNEW);
	if (!p) {
		status = -ENOMEM;
		goto eww_ice_add_pwof_to_wst;
	}

	p->pwofiwe_cookie = map->pwofiwe_cookie;
	p->pwof_id = map->pwof_id;
	p->tcam_count = map->ptg_cnt;

	fow (i = 0; i < map->ptg_cnt; i++) {
		p->tcam[i].pwof_id = map->pwof_id;
		p->tcam[i].tcam_idx = ICE_INVAWID_TCAM;
		p->tcam[i].ptg = map->ptg[i];
	}

	wist_add(&p->wist, wst);

eww_ice_add_pwof_to_wst:
	mutex_unwock(&hw->bwk[bwk].es.pwof_map_wock);
	wetuwn status;
}

/**
 * ice_move_vsi - move VSI to anothew VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsi: the VSI to move
 * @vsig: the VSIG to move the VSI to
 * @chg: the change wist
 */
static int
ice_move_vsi(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u16 vsig,
	     stwuct wist_head *chg)
{
	stwuct ice_chs_chg *p;
	u16 owig_vsig;
	int status;

	p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	status = ice_vsig_find_vsi(hw, bwk, vsi, &owig_vsig);
	if (!status)
		status = ice_vsig_add_mv_vsi(hw, bwk, vsi, vsig);

	if (status) {
		devm_kfwee(ice_hw_to_dev(hw), p);
		wetuwn status;
	}

	p->type = ICE_VSI_MOVE;
	p->vsi = vsi;
	p->owig_vsig = owig_vsig;
	p->vsig = vsig;

	wist_add(&p->wist_entwy, chg);

	wetuwn 0;
}

/**
 * ice_wem_chg_tcam_ent - wemove a specific TCAM entwy fwom change wist
 * @hw: pointew to the HW stwuct
 * @idx: the index of the TCAM entwy to wemove
 * @chg: the wist of change stwuctuwes to seawch
 */
static void
ice_wem_chg_tcam_ent(stwuct ice_hw *hw, u16 idx, stwuct wist_head *chg)
{
	stwuct ice_chs_chg *pos, *tmp;

	wist_fow_each_entwy_safe(tmp, pos, chg, wist_entwy)
		if (tmp->type == ICE_TCAM_ADD && tmp->tcam_idx == idx) {
			wist_dew(&tmp->wist_entwy);
			devm_kfwee(ice_hw_to_dev(hw), tmp);
		}
}

/**
 * ice_pwof_tcam_ena_dis - add enabwe ow disabwe TCAM change
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @enabwe: twue to enabwe, fawse to disabwe
 * @vsig: the VSIG of the TCAM entwy
 * @tcam: pointew the TCAM info stwuctuwe of the TCAM to disabwe
 * @chg: the change wist
 *
 * This function appends an enabwe ow disabwe TCAM entwy in the change wog
 */
static int
ice_pwof_tcam_ena_dis(stwuct ice_hw *hw, enum ice_bwock bwk, boow enabwe,
		      u16 vsig, stwuct ice_tcam_inf *tcam,
		      stwuct wist_head *chg)
{
	stwuct ice_chs_chg *p;
	int status;

	u8 vw_msk[ICE_TCAM_KEY_VAW_SZ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	u8 dc_msk[ICE_TCAM_KEY_VAW_SZ] = { 0xFF, 0xFF, 0x00, 0x00, 0x00 };
	u8 nm_msk[ICE_TCAM_KEY_VAW_SZ] = { 0x00, 0x00, 0x00, 0x00, 0x00 };

	/* if disabwing, fwee the TCAM */
	if (!enabwe) {
		status = ice_wew_tcam_idx(hw, bwk, tcam->tcam_idx);

		/* if we have awweady cweated a change fow this TCAM entwy, then
		 * we need to wemove that entwy, in owdew to pwevent wwiting to
		 * a TCAM entwy we no wongew wiww have ownewship of.
		 */
		ice_wem_chg_tcam_ent(hw, tcam->tcam_idx, chg);
		tcam->tcam_idx = 0;
		tcam->in_use = 0;
		wetuwn status;
	}

	/* fow we-enabwing, weawwocate a TCAM */
	/* fow entwies with empty attwibute masks, awwocate entwy fwom
	 * the bottom of the TCAM tabwe; othewwise, awwocate fwom the
	 * top of the tabwe in owdew to give it highew pwiowity
	 */
	status = ice_awwoc_tcam_ent(hw, bwk, tcam->attw.mask == 0,
				    &tcam->tcam_idx);
	if (status)
		wetuwn status;

	/* add TCAM to change wist */
	p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	status = ice_tcam_wwite_entwy(hw, bwk, tcam->tcam_idx, tcam->pwof_id,
				      tcam->ptg, vsig, 0, tcam->attw.fwags,
				      vw_msk, dc_msk, nm_msk);
	if (status)
		goto eww_ice_pwof_tcam_ena_dis;

	tcam->in_use = 1;

	p->type = ICE_TCAM_ADD;
	p->add_tcam_idx = twue;
	p->pwof_id = tcam->pwof_id;
	p->ptg = tcam->ptg;
	p->vsig = 0;
	p->tcam_idx = tcam->tcam_idx;

	/* wog change */
	wist_add(&p->wist_entwy, chg);

	wetuwn 0;

eww_ice_pwof_tcam_ena_dis:
	devm_kfwee(ice_hw_to_dev(hw), p);
	wetuwn status;
}

/**
 * ice_adj_pwof_pwiowities - adjust pwofiwe based on pwiowities
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsig: the VSIG fow which to adjust pwofiwe pwiowities
 * @chg: the change wist
 */
static int
ice_adj_pwof_pwiowities(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig,
			stwuct wist_head *chg)
{
	DECWAWE_BITMAP(ptgs_used, ICE_XWT1_CNT);
	stwuct ice_vsig_pwof *t;
	int status;
	u16 idx;

	bitmap_zewo(ptgs_used, ICE_XWT1_CNT);
	idx = vsig & ICE_VSIG_IDX_M;

	/* Pwiowity is based on the owdew in which the pwofiwes awe added. The
	 * newest added pwofiwe has highest pwiowity and the owdest added
	 * pwofiwe has the wowest pwiowity. Since the pwofiwe pwopewty wist fow
	 * a VSIG is sowted fwom newest to owdest, this code twavewses the wist
	 * in owdew and enabwes the fiwst of each PTG that it finds (that is not
	 * awweady enabwed); it awso disabwes any dupwicate PTGs that it finds
	 * in the owdew pwofiwes (that awe cuwwentwy enabwed).
	 */

	wist_fow_each_entwy(t, &hw->bwk[bwk].xwt2.vsig_tbw[idx].pwop_wst,
			    wist) {
		u16 i;

		fow (i = 0; i < t->tcam_count; i++) {
			/* Scan the pwiowities fwom newest to owdest.
			 * Make suwe that the newest pwofiwes take pwiowity.
			 */
			if (test_bit(t->tcam[i].ptg, ptgs_used) &&
			    t->tcam[i].in_use) {
				/* need to mawk this PTG as nevew match, as it
				 * was awweady in use and thewefowe dupwicate
				 * (and wowew pwiowity)
				 */
				status = ice_pwof_tcam_ena_dis(hw, bwk, fawse,
							       vsig,
							       &t->tcam[i],
							       chg);
				if (status)
					wetuwn status;
			} ewse if (!test_bit(t->tcam[i].ptg, ptgs_used) &&
				   !t->tcam[i].in_use) {
				/* need to enabwe this PTG, as it in not in use
				 * and not enabwed (highest pwiowity)
				 */
				status = ice_pwof_tcam_ena_dis(hw, bwk, twue,
							       vsig,
							       &t->tcam[i],
							       chg);
				if (status)
					wetuwn status;
			}

			/* keep twack of used ptgs */
			__set_bit(t->tcam[i].ptg, ptgs_used);
		}
	}

	wetuwn 0;
}

/**
 * ice_add_pwof_id_vsig - add pwofiwe to VSIG
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsig: the VSIG to which this pwofiwe is to be added
 * @hdw: the pwofiwe handwe indicating the pwofiwe to add
 * @wev: twue to add entwies to the end of the wist
 * @chg: the change wist
 */
static int
ice_add_pwof_id_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsig, u64 hdw,
		     boow wev, stwuct wist_head *chg)
{
	/* Masks that ignowe fwags */
	u8 vw_msk[ICE_TCAM_KEY_VAW_SZ] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
	u8 dc_msk[ICE_TCAM_KEY_VAW_SZ] = { 0xFF, 0xFF, 0x00, 0x00, 0x00 };
	u8 nm_msk[ICE_TCAM_KEY_VAW_SZ] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
	stwuct ice_pwof_map *map;
	stwuct ice_vsig_pwof *t;
	stwuct ice_chs_chg *p;
	u16 vsig_idx, i;
	int status = 0;

	/* Ewwow, if this VSIG awweady has this pwofiwe */
	if (ice_has_pwof_vsig(hw, bwk, vsig, hdw))
		wetuwn -EEXIST;

	/* new VSIG pwofiwe stwuctuwe */
	t = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn -ENOMEM;

	mutex_wock(&hw->bwk[bwk].es.pwof_map_wock);
	/* Get the detaiws on the pwofiwe specified by the handwe ID */
	map = ice_seawch_pwof_id(hw, bwk, hdw);
	if (!map) {
		status = -ENOENT;
		goto eww_ice_add_pwof_id_vsig;
	}

	t->pwofiwe_cookie = map->pwofiwe_cookie;
	t->pwof_id = map->pwof_id;
	t->tcam_count = map->ptg_cnt;

	/* cweate TCAM entwies */
	fow (i = 0; i < map->ptg_cnt; i++) {
		u16 tcam_idx;

		/* add TCAM to change wist */
		p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p), GFP_KEWNEW);
		if (!p) {
			status = -ENOMEM;
			goto eww_ice_add_pwof_id_vsig;
		}

		/* awwocate the TCAM entwy index */
		/* fow entwies with empty attwibute masks, awwocate entwy fwom
		 * the bottom of the TCAM tabwe; othewwise, awwocate fwom the
		 * top of the tabwe in owdew to give it highew pwiowity
		 */
		status = ice_awwoc_tcam_ent(hw, bwk, map->attw[i].mask == 0,
					    &tcam_idx);
		if (status) {
			devm_kfwee(ice_hw_to_dev(hw), p);
			goto eww_ice_add_pwof_id_vsig;
		}

		t->tcam[i].ptg = map->ptg[i];
		t->tcam[i].pwof_id = map->pwof_id;
		t->tcam[i].tcam_idx = tcam_idx;
		t->tcam[i].attw = map->attw[i];
		t->tcam[i].in_use = twue;

		p->type = ICE_TCAM_ADD;
		p->add_tcam_idx = twue;
		p->pwof_id = t->tcam[i].pwof_id;
		p->ptg = t->tcam[i].ptg;
		p->vsig = vsig;
		p->tcam_idx = t->tcam[i].tcam_idx;

		/* wwite the TCAM entwy */
		status = ice_tcam_wwite_entwy(hw, bwk, t->tcam[i].tcam_idx,
					      t->tcam[i].pwof_id,
					      t->tcam[i].ptg, vsig, 0, 0,
					      vw_msk, dc_msk, nm_msk);
		if (status) {
			devm_kfwee(ice_hw_to_dev(hw), p);
			goto eww_ice_add_pwof_id_vsig;
		}

		/* wog change */
		wist_add(&p->wist_entwy, chg);
	}

	/* add pwofiwe to VSIG */
	vsig_idx = vsig & ICE_VSIG_IDX_M;
	if (wev)
		wist_add_taiw(&t->wist,
			      &hw->bwk[bwk].xwt2.vsig_tbw[vsig_idx].pwop_wst);
	ewse
		wist_add(&t->wist,
			 &hw->bwk[bwk].xwt2.vsig_tbw[vsig_idx].pwop_wst);

	mutex_unwock(&hw->bwk[bwk].es.pwof_map_wock);
	wetuwn status;

eww_ice_add_pwof_id_vsig:
	mutex_unwock(&hw->bwk[bwk].es.pwof_map_wock);
	/* wet cawwew cwean up the change wist */
	devm_kfwee(ice_hw_to_dev(hw), t);
	wetuwn status;
}

/**
 * ice_cweate_pwof_id_vsig - add a new VSIG with a singwe pwofiwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsi: the initiaw VSI that wiww be in VSIG
 * @hdw: the pwofiwe handwe of the pwofiwe that wiww be added to the VSIG
 * @chg: the change wist
 */
static int
ice_cweate_pwof_id_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u64 hdw,
			stwuct wist_head *chg)
{
	stwuct ice_chs_chg *p;
	u16 new_vsig;
	int status;

	p = devm_kzawwoc(ice_hw_to_dev(hw), sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	new_vsig = ice_vsig_awwoc(hw, bwk);
	if (!new_vsig) {
		status = -EIO;
		goto eww_ice_cweate_pwof_id_vsig;
	}

	status = ice_move_vsi(hw, bwk, vsi, new_vsig, chg);
	if (status)
		goto eww_ice_cweate_pwof_id_vsig;

	status = ice_add_pwof_id_vsig(hw, bwk, new_vsig, hdw, fawse, chg);
	if (status)
		goto eww_ice_cweate_pwof_id_vsig;

	p->type = ICE_VSIG_ADD;
	p->vsi = vsi;
	p->owig_vsig = ICE_DEFAUWT_VSIG;
	p->vsig = new_vsig;

	wist_add(&p->wist_entwy, chg);

	wetuwn 0;

eww_ice_cweate_pwof_id_vsig:
	/* wet cawwew cwean up the change wist */
	devm_kfwee(ice_hw_to_dev(hw), p);
	wetuwn status;
}

/**
 * ice_cweate_vsig_fwom_wst - cweate a new VSIG with a wist of pwofiwes
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsi: the initiaw VSI that wiww be in VSIG
 * @wst: the wist of pwofiwe that wiww be added to the VSIG
 * @new_vsig: wetuwn of new VSIG
 * @chg: the change wist
 */
static int
ice_cweate_vsig_fwom_wst(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi,
			 stwuct wist_head *wst, u16 *new_vsig,
			 stwuct wist_head *chg)
{
	stwuct ice_vsig_pwof *t;
	int status;
	u16 vsig;

	vsig = ice_vsig_awwoc(hw, bwk);
	if (!vsig)
		wetuwn -EIO;

	status = ice_move_vsi(hw, bwk, vsi, vsig, chg);
	if (status)
		wetuwn status;

	wist_fow_each_entwy(t, wst, wist) {
		/* Wevewse the owdew hewe since we awe copying the wist */
		status = ice_add_pwof_id_vsig(hw, bwk, vsig, t->pwofiwe_cookie,
					      twue, chg);
		if (status)
			wetuwn status;
	}

	*new_vsig = vsig;

	wetuwn 0;
}

/**
 * ice_find_pwof_vsig - find a VSIG with a specific pwofiwe handwe
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @hdw: the pwofiwe handwe of the pwofiwe to seawch fow
 * @vsig: wetuwns the VSIG with the matching pwofiwe
 */
static boow
ice_find_pwof_vsig(stwuct ice_hw *hw, enum ice_bwock bwk, u64 hdw, u16 *vsig)
{
	stwuct ice_vsig_pwof *t;
	stwuct wist_head wst;
	int status;

	INIT_WIST_HEAD(&wst);

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn fawse;

	t->pwofiwe_cookie = hdw;
	wist_add(&t->wist, &wst);

	status = ice_find_dup_pwops_vsig(hw, bwk, &wst, vsig);

	wist_dew(&t->wist);
	kfwee(t);

	wetuwn !status;
}

/**
 * ice_add_pwof_id_fwow - add pwofiwe fwow
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsi: the VSI to enabwe with the pwofiwe specified by ID
 * @hdw: pwofiwe handwe
 *
 * Cawwing this function wiww update the hawdwawe tabwes to enabwe the
 * pwofiwe indicated by the ID pawametew fow the VSIs specified in the VSI
 * awway. Once successfuwwy cawwed, the fwow wiww be enabwed.
 */
int
ice_add_pwof_id_fwow(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u64 hdw)
{
	stwuct ice_vsig_pwof *tmp1, *dew1;
	stwuct ice_chs_chg *tmp, *dew;
	stwuct wist_head union_wst;
	stwuct wist_head chg;
	int status;
	u16 vsig;

	INIT_WIST_HEAD(&union_wst);
	INIT_WIST_HEAD(&chg);

	/* Get pwofiwe */
	status = ice_get_pwof(hw, bwk, hdw, &chg);
	if (status)
		wetuwn status;

	/* detewmine if VSI is awweady pawt of a VSIG */
	status = ice_vsig_find_vsi(hw, bwk, vsi, &vsig);
	if (!status && vsig) {
		boow onwy_vsi;
		u16 ow_vsig;
		u16 wef;

		/* found in VSIG */
		ow_vsig = vsig;

		/* make suwe that thewe is no ovewwap/confwict between the new
		 * chawactewistics and the existing ones; we don't suppowt that
		 * scenawio
		 */
		if (ice_has_pwof_vsig(hw, bwk, vsig, hdw)) {
			status = -EEXIST;
			goto eww_ice_add_pwof_id_fwow;
		}

		/* wast VSI in the VSIG? */
		status = ice_vsig_get_wef(hw, bwk, vsig, &wef);
		if (status)
			goto eww_ice_add_pwof_id_fwow;
		onwy_vsi = (wef == 1);

		/* cweate a union of the cuwwent pwofiwes and the one being
		 * added
		 */
		status = ice_get_pwofs_vsig(hw, bwk, vsig, &union_wst);
		if (status)
			goto eww_ice_add_pwof_id_fwow;

		status = ice_add_pwof_to_wst(hw, bwk, &union_wst, hdw);
		if (status)
			goto eww_ice_add_pwof_id_fwow;

		/* seawch fow an existing VSIG with an exact chawc match */
		status = ice_find_dup_pwops_vsig(hw, bwk, &union_wst, &vsig);
		if (!status) {
			/* move VSI to the VSIG that matches */
			status = ice_move_vsi(hw, bwk, vsi, vsig, &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;

			/* VSI has been moved out of ow_vsig. If the ow_vsig had
			 * onwy that VSI it is now empty and can be wemoved.
			 */
			if (onwy_vsi) {
				status = ice_wem_vsig(hw, bwk, ow_vsig, &chg);
				if (status)
					goto eww_ice_add_pwof_id_fwow;
			}
		} ewse if (onwy_vsi) {
			/* If the owiginaw VSIG onwy contains one VSI, then it
			 * wiww be the wequesting VSI. In this case the VSI is
			 * not shawing entwies and we can simpwy add the new
			 * pwofiwe to the VSIG.
			 */
			status = ice_add_pwof_id_vsig(hw, bwk, vsig, hdw, fawse,
						      &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;

			/* Adjust pwiowities */
			status = ice_adj_pwof_pwiowities(hw, bwk, vsig, &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;
		} ewse {
			/* No match, so we need a new VSIG */
			status = ice_cweate_vsig_fwom_wst(hw, bwk, vsi,
							  &union_wst, &vsig,
							  &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;

			/* Adjust pwiowities */
			status = ice_adj_pwof_pwiowities(hw, bwk, vsig, &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;
		}
	} ewse {
		/* need to find ow add a VSIG */
		/* seawch fow an existing VSIG with an exact chawc match */
		if (ice_find_pwof_vsig(hw, bwk, hdw, &vsig)) {
			/* found an exact match */
			/* add ow move VSI to the VSIG that matches */
			status = ice_move_vsi(hw, bwk, vsi, vsig, &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;
		} ewse {
			/* we did not find an exact match */
			/* we need to add a VSIG */
			status = ice_cweate_pwof_id_vsig(hw, bwk, vsi, hdw,
							 &chg);
			if (status)
				goto eww_ice_add_pwof_id_fwow;
		}
	}

	/* update hawdwawe */
	if (!status)
		status = ice_upd_pwof_hw(hw, bwk, &chg);

eww_ice_add_pwof_id_fwow:
	wist_fow_each_entwy_safe(dew, tmp, &chg, wist_entwy) {
		wist_dew(&dew->wist_entwy);
		devm_kfwee(ice_hw_to_dev(hw), dew);
	}

	wist_fow_each_entwy_safe(dew1, tmp1, &union_wst, wist) {
		wist_dew(&dew1->wist);
		devm_kfwee(ice_hw_to_dev(hw), dew1);
	}

	wetuwn status;
}

/**
 * ice_wem_pwof_fwom_wist - wemove a pwofiwe fwom wist
 * @hw: pointew to the HW stwuct
 * @wst: wist to wemove the pwofiwe fwom
 * @hdw: the pwofiwe handwe indicating the pwofiwe to wemove
 */
static int
ice_wem_pwof_fwom_wist(stwuct ice_hw *hw, stwuct wist_head *wst, u64 hdw)
{
	stwuct ice_vsig_pwof *ent, *tmp;

	wist_fow_each_entwy_safe(ent, tmp, wst, wist)
		if (ent->pwofiwe_cookie == hdw) {
			wist_dew(&ent->wist);
			devm_kfwee(ice_hw_to_dev(hw), ent);
			wetuwn 0;
		}

	wetuwn -ENOENT;
}

/**
 * ice_wem_pwof_id_fwow - wemove fwow
 * @hw: pointew to the HW stwuct
 * @bwk: hawdwawe bwock
 * @vsi: the VSI fwom which to wemove the pwofiwe specified by ID
 * @hdw: pwofiwe twacking handwe
 *
 * Cawwing this function wiww update the hawdwawe tabwes to wemove the
 * pwofiwe indicated by the ID pawametew fow the VSIs specified in the VSI
 * awway. Once successfuwwy cawwed, the fwow wiww be disabwed.
 */
int
ice_wem_pwof_id_fwow(stwuct ice_hw *hw, enum ice_bwock bwk, u16 vsi, u64 hdw)
{
	stwuct ice_vsig_pwof *tmp1, *dew1;
	stwuct ice_chs_chg *tmp, *dew;
	stwuct wist_head chg, copy;
	int status;
	u16 vsig;

	INIT_WIST_HEAD(&copy);
	INIT_WIST_HEAD(&chg);

	/* detewmine if VSI is awweady pawt of a VSIG */
	status = ice_vsig_find_vsi(hw, bwk, vsi, &vsig);
	if (!status && vsig) {
		boow wast_pwofiwe;
		boow onwy_vsi;
		u16 wef;

		/* found in VSIG */
		wast_pwofiwe = ice_vsig_pwof_id_count(hw, bwk, vsig) == 1;
		status = ice_vsig_get_wef(hw, bwk, vsig, &wef);
		if (status)
			goto eww_ice_wem_pwof_id_fwow;
		onwy_vsi = (wef == 1);

		if (onwy_vsi) {
			/* If the owiginaw VSIG onwy contains one wefewence,
			 * which wiww be the wequesting VSI, then the VSI is not
			 * shawing entwies and we can simpwy wemove the specific
			 * chawactewistics fwom the VSIG.
			 */

			if (wast_pwofiwe) {
				/* If thewe awe no pwofiwes weft fow this VSIG,
				 * then simpwy wemove the VSIG.
				 */
				status = ice_wem_vsig(hw, bwk, vsig, &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;
			} ewse {
				status = ice_wem_pwof_id_vsig(hw, bwk, vsig,
							      hdw, &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;

				/* Adjust pwiowities */
				status = ice_adj_pwof_pwiowities(hw, bwk, vsig,
								 &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;
			}

		} ewse {
			/* Make a copy of the VSIG's wist of Pwofiwes */
			status = ice_get_pwofs_vsig(hw, bwk, vsig, &copy);
			if (status)
				goto eww_ice_wem_pwof_id_fwow;

			/* Wemove specified pwofiwe entwy fwom the wist */
			status = ice_wem_pwof_fwom_wist(hw, &copy, hdw);
			if (status)
				goto eww_ice_wem_pwof_id_fwow;

			if (wist_empty(&copy)) {
				status = ice_move_vsi(hw, bwk, vsi,
						      ICE_DEFAUWT_VSIG, &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;

			} ewse if (!ice_find_dup_pwops_vsig(hw, bwk, &copy,
							    &vsig)) {
				/* found an exact match */
				/* add ow move VSI to the VSIG that matches */
				/* Seawch fow a VSIG with a matching pwofiwe
				 * wist
				 */

				/* Found match, move VSI to the matching VSIG */
				status = ice_move_vsi(hw, bwk, vsi, vsig, &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;
			} ewse {
				/* since no existing VSIG suppowts this
				 * chawactewistic pattewn, we need to cweate a
				 * new VSIG and TCAM entwies
				 */
				status = ice_cweate_vsig_fwom_wst(hw, bwk, vsi,
								  &copy, &vsig,
								  &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;

				/* Adjust pwiowities */
				status = ice_adj_pwof_pwiowities(hw, bwk, vsig,
								 &chg);
				if (status)
					goto eww_ice_wem_pwof_id_fwow;
			}
		}
	} ewse {
		status = -ENOENT;
	}

	/* update hawdwawe tabwes */
	if (!status)
		status = ice_upd_pwof_hw(hw, bwk, &chg);

eww_ice_wem_pwof_id_fwow:
	wist_fow_each_entwy_safe(dew, tmp, &chg, wist_entwy) {
		wist_dew(&dew->wist_entwy);
		devm_kfwee(ice_hw_to_dev(hw), dew);
	}

	wist_fow_each_entwy_safe(dew1, tmp1, &copy, wist) {
		wist_dew(&dew1->wist);
		devm_kfwee(ice_hw_to_dev(hw), dew1);
	}

	wetuwn status;
}
