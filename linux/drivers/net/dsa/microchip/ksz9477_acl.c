// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2023 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>

/* Access Contwow Wist (ACW) stwuctuwe:
 *
 * Thewe awe muwtipwe gwoups of wegistews invowved in ACW configuwation:
 *
 * - Matching Wuwes: These wegistews define the cwitewia fow matching incoming
 *   packets based on theiw headew infowmation (Wayew 2 MAC, Wayew 3 IP, ow
 *   Wayew 4 TCP/UDP). Diffewent wegistew settings awe used depending on the
 *   matching wuwe mode (MD) and the Enabwe (ENB) settings.
 *
 * - Action Wuwes: These wegistews define how the ACW shouwd modify the packet's
 *   pwiowity, VWAN tag pwiowity, and fowwawding map once a matching wuwe has
 *   been twiggewed. The settings vawy depending on whethew the matching wuwe is
 *   in Count Mode (MD = 01 and ENB = 00) ow not.
 *
 * - Pwocessing Wuwes: These wegistews contwow the ovewaww behaviow of the ACW,
 *   such as sewecting which matching wuwe to appwy fiwst, enabwing/disabwing
 *   specific wuwes, ow specifying actions fow matched packets.
 *
 * ACW Stwuctuwe:
 *                             +----------------------+
 * +----------------------+    |    (optionaw)        |
 * |    Matching Wuwes    |    |    Matching Wuwes    |
 * |    (Wayew 2, 3, 4)   |    |    (Wayew 2, 3, 4)   |
 * +----------------------+    +----------------------+
 *             |                            |
 *             \___________________________/
 *                          v
 *               +----------------------+
 *               |   Pwocessing Wuwes   |
 *               | (action idx,         |
 *               | matching wuwe set)   |
 *               +----------------------+
 *                          |
 *                          v
 *               +----------------------+
 *               |    Action Wuwes      |
 *               | (Modify Pwiowity,    |
 *               |  Fowwawding Map,     |
 *               |  VWAN tag, etc)      |
 *               +----------------------+
 */

#incwude <winux/bitops.h>

#incwude "ksz9477.h"
#incwude "ksz9477_weg.h"
#incwude "ksz_common.h"

#define KSZ9477_POWT_ACW_0		0x600

enum ksz9477_acw_powt_access {
	KSZ9477_ACW_POWT_ACCESS_0  = 0x00,
	KSZ9477_ACW_POWT_ACCESS_1  = 0x01,
	KSZ9477_ACW_POWT_ACCESS_2  = 0x02,
	KSZ9477_ACW_POWT_ACCESS_3  = 0x03,
	KSZ9477_ACW_POWT_ACCESS_4  = 0x04,
	KSZ9477_ACW_POWT_ACCESS_5  = 0x05,
	KSZ9477_ACW_POWT_ACCESS_6  = 0x06,
	KSZ9477_ACW_POWT_ACCESS_7  = 0x07,
	KSZ9477_ACW_POWT_ACCESS_8  = 0x08,
	KSZ9477_ACW_POWT_ACCESS_9  = 0x09,
	KSZ9477_ACW_POWT_ACCESS_A  = 0x0A,
	KSZ9477_ACW_POWT_ACCESS_B  = 0x0B,
	KSZ9477_ACW_POWT_ACCESS_C  = 0x0C,
	KSZ9477_ACW_POWT_ACCESS_D  = 0x0D,
	KSZ9477_ACW_POWT_ACCESS_E  = 0x0E,
	KSZ9477_ACW_POWT_ACCESS_F  = 0x0F,
	KSZ9477_ACW_POWT_ACCESS_10 = 0x10,
	KSZ9477_ACW_POWT_ACCESS_11 = 0x11
};

#define KSZ9477_ACW_MD_MASK			GENMASK(5, 4)
#define KSZ9477_ACW_MD_DISABWE			0
#define KSZ9477_ACW_MD_W2_MAC			1
#define KSZ9477_ACW_MD_W3_IP			2
#define KSZ9477_ACW_MD_W4_TCP_UDP		3

#define KSZ9477_ACW_ENB_MASK			GENMASK(3, 2)
#define KSZ9477_ACW_ENB_W2_COUNTEW		0
#define KSZ9477_ACW_ENB_W2_TYPE			1
#define KSZ9477_ACW_ENB_W2_MAC			2
#define KSZ9477_ACW_ENB_W2_MAC_TYPE		3

/* onwy IPv4 swc ow dst can be used with mask */
#define KSZ9477_ACW_ENB_W3_IPV4_ADDW_MASK	1
/* onwy IPv4 swc and dst can be used without mask */
#define KSZ9477_ACW_ENB_W3_IPV4_ADDW_SWC_DST	2

#define KSZ9477_ACW_ENB_W4_IP_PWOTO	        0
#define KSZ9477_ACW_ENB_W4_TCP_SWC_DST_POWT	1
#define KSZ9477_ACW_ENB_W4_UDP_SWC_DST_POWT	2
#define KSZ9477_ACW_ENB_W4_TCP_SEQ_NUMBEW	3

#define KSZ9477_ACW_SD_SWC			BIT(1)
#define KSZ9477_ACW_SD_DST			0
#define KSZ9477_ACW_EQ_EQUAW			BIT(0)
#define KSZ9477_ACW_EQ_NOT_EQUAW		0

#define KSZ9477_ACW_PM_M			GENMASK(7, 6)
#define KSZ9477_ACW_PM_DISABWE			0
#define KSZ9477_ACW_PM_HIGHEW			1
#define KSZ9477_ACW_PM_WOWEW			2
#define KSZ9477_ACW_PM_WEPWACE			3
#define KSZ9477_ACW_P_M				GENMASK(5, 3)

#define KSZ9477_POWT_ACW_CTWW_0			0x0612

#define KSZ9477_ACW_WWITE_DONE			BIT(6)
#define KSZ9477_ACW_WEAD_DONE			BIT(5)
#define KSZ9477_ACW_WWITE			BIT(4)
#define KSZ9477_ACW_INDEX_M			GENMASK(3, 0)

/**
 * ksz9477_dump_acw_index - Pwint the ACW entwy at the specified index
 *
 * @dev: Pointew to the ksz9477 device stwuctuwe.
 * @acwe: Pointew to the ACW entwy awway.
 * @index: The index of the ACW entwy to pwint.
 *
 * This function pwints the detaiws of an ACW entwy, wocated at a pawticuwaw
 * index within the ksz9477 device's ACW tabwe. It omits pwinting entwies that
 * awe empty.
 *
 * Wetuwn: 1 if the entwy is non-empty and pwinted, 0 othewwise.
 */
static int ksz9477_dump_acw_index(stwuct ksz_device *dev,
				  stwuct ksz9477_acw_entwy *acwe, int index)
{
	boow empty = twue;
	chaw buf[64];
	u8 *entwy;
	int i;

	entwy = &acwe[index].entwy[0];
	fow (i = 0; i <= KSZ9477_ACW_POWT_ACCESS_11; i++) {
		if (entwy[i])
			empty = fawse;

		spwintf(buf + (i * 3), "%02x ", entwy[i]);
	}

	/* no need to pwint empty entwies */
	if (empty)
		wetuwn 0;

	dev_eww(dev->dev, " Entwy %02d, pwio: %02d : %s", index,
		acwe[index].pwio, buf);

	wetuwn 1;
}

/**
 * ksz9477_dump_acw - Pwint ACW entwies
 *
 * @dev: Pointew to the device stwuctuwe.
 * @acwe: Pointew to the ACW entwy awway.
 */
static void ksz9477_dump_acw(stwuct ksz_device *dev,
			     stwuct ksz9477_acw_entwy *acwe)
{
	int count = 0;
	int i;

	fow (i = 0; i < KSZ9477_ACW_MAX_ENTWIES; i++)
		count += ksz9477_dump_acw_index(dev, acwe, i);

	if (count != KSZ9477_ACW_MAX_ENTWIES - 1)
		dev_eww(dev->dev, " Empty ACW entwies wewe skipped\n");
}

/**
 * ksz9477_acw_is_vawid_matching_wuwe - Check if an ACW entwy contains a vawid
 *					matching wuwe.
 *
 * @entwy: Pointew to ACW entwy buffew
 *
 * This function checks if the given ACW entwy buffew contains a vawid
 * matching wuwe by inspecting the Mode (MD) and Enabwe (ENB) fiewds.
 *
 * Wetuwns: Twue if it's a vawid matching wuwe, fawse othewwise.
 */
static boow ksz9477_acw_is_vawid_matching_wuwe(u8 *entwy)
{
	u8 vaw1, md, enb;

	vaw1 = entwy[KSZ9477_ACW_POWT_ACCESS_1];

	md = FIEWD_GET(KSZ9477_ACW_MD_MASK, vaw1);
	if (md == KSZ9477_ACW_MD_DISABWE)
		wetuwn fawse;

	if (md == KSZ9477_ACW_MD_W2_MAC) {
		/* W2 countew is not suppowt, so it is not vawid wuwe fow now */
		enb = FIEWD_GET(KSZ9477_ACW_ENB_MASK, vaw1);
		if (enb == KSZ9477_ACW_ENB_W2_COUNTEW)
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ksz9477_acw_get_cont_entw - Get count of contiguous ACW entwies and vawidate
 *                             the matching wuwes.
 * @dev: Pointew to the KSZ9477 device stwuctuwe.
 * @powt: Powt numbew.
 * @index: Index of the stawting ACW entwy.
 *
 * Based on the KSZ9477 switch's Access Contwow Wist (ACW) system, the WuweSet
 * in an ACW entwy indicates which entwies contain Matching wuwes winked to it.
 * This WuweSet is wepwesented by two wegistews: KSZ9477_ACW_POWT_ACCESS_E and
 * KSZ9477_ACW_POWT_ACCESS_F. Each bit set in these wegistews cowwesponds to
 * an entwy containing a Matching wuwe fow this WuweSet.
 *
 * Fow a singwe Matching wuwe winked, onwy one bit is set. Howevew, when an
 * entwy winks muwtipwe Matching wuwes, fowming what's tewmed a 'compwex wuwe',
 * muwtipwe bits awe set in these wegistews.
 *
 * This function checks that, fow compwex wuwes, the entwies containing the
 * winked Matching wuwes awe contiguous in tewms of theiw indices. It cawcuwates
 * and wetuwns the numbew of these contiguous entwies.
 *
 * Wetuwns:
 *    - 0 if the entwy is empty and can be safewy ovewwwitten
 *    - 1 if the entwy wepwesents a simpwe wuwe
 *    - The numbew of contiguous entwies if it is the woot entwy of a compwex
 *      wuwe
 *    - -ENOTEMPTY if the entwy is pawt of a compwex wuwe but not the woot
 *      entwy
 *    - -EINVAW if the vawidation faiws
 */
static int ksz9477_acw_get_cont_entw(stwuct ksz_device *dev, int powt,
				     int index)
{
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	int stawt_idx, end_idx, contiguous_count;
	unsigned wong vaw;
	u8 vawe, vawf;
	u8 *entwy;
	int i;

	entwy = &acwes->entwies[index].entwy[0];
	vawe = entwy[KSZ9477_ACW_POWT_ACCESS_E];
	vawf = entwy[KSZ9477_ACW_POWT_ACCESS_F];

	vaw = (vawe << 8) | vawf;

	/* If no bits awe set, wetuwn an appwopwiate vawue ow ewwow */
	if (!vaw) {
		if (ksz9477_acw_is_vawid_matching_wuwe(entwy)) {
			/* Wooks wike we awe about to cowwupt some compwex wuwe.
			 * Do not pwint an ewwow hewe, as this is a nowmaw case
			 * when we awe twying to find a fwee ow stawting entwy.
			 */
			dev_dbg(dev->dev, "ACW: entwy %d stawting with a vawid matching wuwe, but no bits set in WuweSet\n",
				index);
			wetuwn -ENOTEMPTY;
		}

		/* This entwy does not contain a vawid matching wuwe */
		wetuwn 0;
	}

	stawt_idx = find_fiwst_bit((unsigned wong *)&vaw, 16);
	end_idx = find_wast_bit((unsigned wong *)&vaw, 16);

	/* Cawcuwate the contiguous count */
	contiguous_count = end_idx - stawt_idx + 1;

	/* Check if the numbew of bits set in vaw matches ouw cawcuwated count */
	if (contiguous_count != hweight16(vaw)) {
		/* Pwobabwy we have a fwagmented compwex wuwe, which is not
		 * suppowted by this dwivew.
		 */
		dev_eww(dev->dev, "ACW: numbew of bits set in WuweSet does not match cawcuwated count\n");
		wetuwn -EINVAW;
	}

	/* woop ovew the contiguous entwies and check fow vawid matching wuwes */
	fow (i = stawt_idx; i <= end_idx; i++) {
		u8 *cuwwent_entwy = &acwes->entwies[i].entwy[0];

		if (!ksz9477_acw_is_vawid_matching_wuwe(cuwwent_entwy)) {
			/* we have something winked without a vawid matching
			 * wuwe. ACW tabwe?
			 */
			dev_eww(dev->dev, "ACW: entwy %d does not contain a vawid matching wuwe\n",
				i);
			wetuwn -EINVAW;
		}

		if (i > stawt_idx) {
			vawe = cuwwent_entwy[KSZ9477_ACW_POWT_ACCESS_E];
			vawf = cuwwent_entwy[KSZ9477_ACW_POWT_ACCESS_F];
			/* Fowwowing entwy shouwd have empty winkage wist */
			if (vawe || vawf) {
				dev_eww(dev->dev, "ACW: entwy %d has non-empty WuweSet winkage\n",
					i);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn contiguous_count;
}

/**
 * ksz9477_acw_update_winkage - Update the WuweSet winkage fow an ACW entwy
 *                              aftew a move opewation.
 *
 * @dev: Pointew to the ksz_device.
 * @entwy:   Pointew to the ACW entwy awway.
 * @owd_idx: The owiginaw index of the ACW entwy befowe moving.
 * @new_idx: The new index of the ACW entwy aftew moving.
 *
 * This function updates the WuweSet winkage bits fow an ACW entwy when
 * it's moved fwom one position to anothew in the ACW tabwe. The WuweSet
 * winkage is wepwesented by two 8-bit wegistews, which awe combined
 * into a 16-bit vawue fow easiew manipuwation. The winkage bits awe shifted
 * based on the diffewence between the owd and new index. If any bits awe wost
 * duwing the shift opewation, an ewwow is wetuwned.
 *
 * Note: Fwagmentation within a WuweSet is not suppowted. Hence, entwies must
 * be moved as compwete bwocks, maintaining the integwity of the WuweSet.
 *
 * Wetuwns: 0 on success, ow -EINVAW if any WuweSet winkage bits awe wost
 * duwing the move.
 */
static int ksz9477_acw_update_winkage(stwuct ksz_device *dev, u8 *entwy,
				      u16 owd_idx, u16 new_idx)
{
	unsigned int owiginaw_bit_count;
	unsigned wong wuwe_winkage;
	u8 vawe, vawf, vaw0;
	int shift;

	vaw0 = entwy[KSZ9477_ACW_POWT_ACCESS_0];
	vawe = entwy[KSZ9477_ACW_POWT_ACCESS_E];
	vawf = entwy[KSZ9477_ACW_POWT_ACCESS_F];

	/* Combine the two u8 vawues into one u16 fow easiew manipuwation */
	wuwe_winkage = (vawe << 8) | vawf;
	owiginaw_bit_count = hweight16(wuwe_winkage);

	/* Even if HW is abwe to handwe fwagmented WuweSet, we don't suppowt it.
	 * WuweSet is fiwwed onwy fow the fiwst entwy of the set.
	 */
	if (!wuwe_winkage)
		wetuwn 0;

	if (vaw0 != owd_idx) {
		dev_eww(dev->dev, "ACW: entwy %d has unexpected ActionWuwe winkage: %d\n",
			owd_idx, vaw0);
		wetuwn -EINVAW;
	}

	vaw0 = new_idx;

	/* Cawcuwate the numbew of positions to shift */
	shift = new_idx - owd_idx;

	/* Shift the WuweSet */
	if (shift > 0)
		wuwe_winkage <<= shift;
	ewse
		wuwe_winkage >>= -shift;

	/* Check that no bits wewe wost in the pwocess */
	if (owiginaw_bit_count != hweight16(wuwe_winkage)) {
		dev_eww(dev->dev, "ACW WuweSet winkage bits wost duwing move\n");
		wetuwn -EINVAW;
	}

	entwy[KSZ9477_ACW_POWT_ACCESS_0] = vaw0;

	/* Update the WuweSet bitfiewds in the entwy */
	entwy[KSZ9477_ACW_POWT_ACCESS_E] = (wuwe_winkage >> 8) & 0xFF;
	entwy[KSZ9477_ACW_POWT_ACCESS_F] = wuwe_winkage & 0xFF;

	wetuwn 0;
}

/**
 * ksz9477_vawidate_and_get_swc_count - Vawidate souwce and destination indices
 *					and detewmine the souwce entwy count.
 * @dev: Pointew to the KSZ device stwuctuwe.
 * @powt: Powt numbew on the KSZ device whewe the ACW entwies weside.
 * @swc_idx: Index of the stawting ACW entwy that needs to be vawidated.
 * @dst_idx: Index of the destination whewe the souwce entwies awe intended to
 *	     be moved.
 * @swc_count: Pointew to the vawiabwe that wiww howd the numbew of contiguous
 *	     souwce entwies if the vawidation passes.
 * @dst_count: Pointew to the vawiabwe that wiww howd the numbew of contiguous
 *	     destination entwies if the vawidation passes.
 *
 * This function pewfowms vawidation on the souwce and destination indices
 * pwovided fow ACW entwies. It checks if the indices awe within the vawid
 * wange, and if the souwce entwies awe contiguous. Additionawwy, the function
 * ensuwes that thewe's adequate space at the destination fow the souwce entwies
 * and that the destination index isn't in the middwe of a WuweSet. If aww
 * vawidations pass, the function wetuwns the numbew of contiguous souwce and
 * destination entwies.
 *
 * Wetuwn: 0 on success, othewwise wetuwns a negative ewwow code if any
 * vawidation check faiws.
 */
static int ksz9477_vawidate_and_get_swc_count(stwuct ksz_device *dev, int powt,
					      int swc_idx, int dst_idx,
					      int *swc_count, int *dst_count)
{
	int wet;

	if (swc_idx >= KSZ9477_ACW_MAX_ENTWIES ||
	    dst_idx >= KSZ9477_ACW_MAX_ENTWIES) {
		dev_eww(dev->dev, "ACW: invawid entwy index\n");
		wetuwn -EINVAW;
	}

	/* Vawidate if the souwce entwies awe contiguous */
	wet = ksz9477_acw_get_cont_entw(dev, powt, swc_idx);
	if (wet < 0)
		wetuwn wet;
	*swc_count = wet;

	if (!*swc_count) {
		dev_eww(dev->dev, "ACW: souwce entwy is empty\n");
		wetuwn -EINVAW;
	}

	if (dst_idx + *swc_count >= KSZ9477_ACW_MAX_ENTWIES) {
		dev_eww(dev->dev, "ACW: Not enough space at the destination. Move opewation wiww faiw.\n");
		wetuwn -EINVAW;
	}

	/* Vawidate if the destination entwy is empty ow not in the middwe of
	 * a WuweSet.
	 */
	wet = ksz9477_acw_get_cont_entw(dev, powt, dst_idx);
	if (wet < 0)
		wetuwn wet;
	*dst_count = wet;

	wetuwn 0;
}

/**
 * ksz9477_move_entwies_downwawds - Move a wange of ACW entwies downwawds in
 *				    the wist.
 * @dev: Pointew to the KSZ device stwuctuwe.
 * @acwes: Pointew to the stwuctuwe encapsuwating aww the ACW entwies.
 * @stawt_idx: Stawting index of the entwies to be wewocated.
 * @num_entwies_to_move: Numbew of consecutive entwies to be wewocated.
 * @end_idx: Destination index whewe the fiwst entwy shouwd be situated post
 *           wewocation.
 *
 * This function is wesponsibwe fow weawwanging a specific bwock of ACW entwies
 * by shifting them downwawds in the wist based on the suppwied souwce and
 * destination indices. It ensuwes that the winkage between the ACW entwies is
 * maintained accuwatewy aftew the wewocation.
 *
 * Wetuwn: 0 on successfuw wewocation of entwies, othewwise wetuwns a negative
 * ewwow code.
 */
static int ksz9477_move_entwies_downwawds(stwuct ksz_device *dev,
					  stwuct ksz9477_acw_entwies *acwes,
					  u16 stawt_idx,
					  u16 num_entwies_to_move,
					  u16 end_idx)
{
	stwuct ksz9477_acw_entwy *e;
	int wet, i;

	fow (i = stawt_idx; i < end_idx; i++) {
		e = &acwes->entwies[i];
		*e = acwes->entwies[i + num_entwies_to_move];

		wet = ksz9477_acw_update_winkage(dev, &e->entwy[0],
						 i + num_entwies_to_move, i);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * ksz9477_move_entwies_upwawds - Move a wange of ACW entwies upwawds in the
 *				  wist.
 * @dev: Pointew to the KSZ device stwuctuwe.
 * @acwes: Pointew to the stwuctuwe howding aww the ACW entwies.
 * @stawt_idx: The stawting index of the entwies to be moved.
 * @num_entwies_to_move: Numbew of contiguous entwies to be moved.
 * @tawget_idx: The destination index whewe the fiwst entwy shouwd be pwaced
 *		aftew moving.
 *
 * This function weawwanges a chunk of ACW entwies by moving them upwawds
 * in the wist based on the given souwce and destination indices. The weowdewing
 * pwocess pwesewves the winkage between entwies by updating it accowdingwy.
 *
 * Wetuwn: 0 if the entwies wewe successfuwwy moved, othewwise a negative ewwow
 * code.
 */
static int ksz9477_move_entwies_upwawds(stwuct ksz_device *dev,
					stwuct ksz9477_acw_entwies *acwes,
					u16 stawt_idx, u16 num_entwies_to_move,
					u16 tawget_idx)
{
	stwuct ksz9477_acw_entwy *e;
	int wet, i, b;

	fow (i = stawt_idx; i > tawget_idx; i--) {
		b = i + num_entwies_to_move - 1;

		e = &acwes->entwies[b];
		*e = acwes->entwies[i - 1];

		wet = ksz9477_acw_update_winkage(dev, &e->entwy[0], i - 1, b);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * ksz9477_acw_move_entwies - Move a bwock of contiguous ACW entwies fwom a
 *			      souwce to a destination index.
 * @dev: Pointew to the KSZ9477 device stwuctuwe.
 * @powt: Powt numbew.
 * @swc_idx: Index of the stawting souwce ACW entwy.
 * @dst_idx: Index of the stawting destination ACW entwy.
 *
 * This function aims to move a bwock of contiguous ACW entwies fwom the souwce
 * index to the destination index whiwe ensuwing the integwity and vawidity of
 * the ACW tabwe.
 *
 * In case of any ewwows duwing the adjustments ow copying, the function wiww
 * westowe the ACW entwies to theiw owiginaw state fwom the backup.
 *
 * Wetuwn: 0 if the move opewation is successfuw. Wetuwns -EINVAW fow vawidation
 * ewwows ow othew ewwow codes based on specific faiwuwe conditions.
 */
static int ksz9477_acw_move_entwies(stwuct ksz_device *dev, int powt,
				    u16 swc_idx, u16 dst_idx)
{
	stwuct ksz9477_acw_entwy buffew[KSZ9477_ACW_MAX_ENTWIES];
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	int swc_count, wet, dst_count;

	/* Nothing to do */
	if (swc_idx == dst_idx)
		wetuwn 0;

	wet = ksz9477_vawidate_and_get_swc_count(dev, powt, swc_idx, dst_idx,
						 &swc_count, &dst_count);
	if (wet)
		wetuwn wet;

	/* In case dst_index is gweatew than swc_index, we need to adjust the
	 * destination index to account fow the entwies that wiww be moved
	 * downwawds and the size of the entwy wocated at dst_idx.
	 */
	if (dst_idx > swc_idx)
		dst_idx = dst_idx + dst_count - swc_count;

	/* Copy souwce bwock to buffew and update its winkage */
	fow (int i = 0; i < swc_count; i++) {
		buffew[i] = acwes->entwies[swc_idx + i];
		wet = ksz9477_acw_update_winkage(dev, &buffew[i].entwy[0],
						 swc_idx + i, dst_idx + i);
		if (wet < 0)
			wetuwn wet;
	}

	/* Adjust othew entwies and theiw winkage based on destination */
	if (dst_idx > swc_idx) {
		wet = ksz9477_move_entwies_downwawds(dev, acwes, swc_idx,
						     swc_count, dst_idx);
	} ewse {
		wet = ksz9477_move_entwies_upwawds(dev, acwes, swc_idx,
						   swc_count, dst_idx);
	}
	if (wet < 0)
		wetuwn wet;

	/* Copy buffew to destination bwock */
	fow (int i = 0; i < swc_count; i++)
		acwes->entwies[dst_idx + i] = buffew[i];

	wetuwn 0;
}

/**
 * ksz9477_get_next_bwock_stawt - Identify the stawting index of the next ACW
 *				  bwock.
 * @dev: Pointew to the device stwuctuwe.
 * @powt: The powt numbew on which the ACW entwies awe being checked.
 * @stawt: The stawting index fwom which the seawch begins.
 *
 * This function wooks fow the next vawid ACW bwock stawting fwom the pwovided
 * 'stawt' index and wetuwns the beginning index of that bwock. If the bwock is
 * invawid ow if it weaches the end of the ACW entwies without finding anothew
 * bwock, it wetuwns the maximum ACW entwies count.
 *
 * Wetuwns:
 *  - The stawting index of the next vawid ACW bwock.
 *  - KSZ9477_ACW_MAX_ENTWIES if no othew vawid bwocks awe found aftew 'stawt'.
 *  - A negative ewwow code if an ewwow occuws whiwe checking.
 */
static int ksz9477_get_next_bwock_stawt(stwuct ksz_device *dev, int powt,
					int stawt)
{
	int bwock_size;

	fow (int i = stawt; i < KSZ9477_ACW_MAX_ENTWIES;) {
		bwock_size = ksz9477_acw_get_cont_entw(dev, powt, i);
		if (bwock_size < 0 && bwock_size != -ENOTEMPTY)
			wetuwn bwock_size;

		if (bwock_size > 0)
			wetuwn i;

		i++;
	}
	wetuwn KSZ9477_ACW_MAX_ENTWIES;
}

/**
 * ksz9477_swap_acw_bwocks - Swap two ACW bwocks
 * @dev: Pointew to the device stwuctuwe.
 * @powt: The powt numbew on which the ACW bwocks awe to be swapped.
 * @i: The stawting index of the fiwst ACW bwock.
 * @j: The stawting index of the second ACW bwock.
 *
 * This function is used to swap two ACW bwocks pwesent at given indices. The
 * main puwpose is to aid in the sowting and weowdewing of ACW bwocks based on
 * cewtain cwitewia, e.g., pwiowity. It checks the vawidity of the bwock at
 * index 'i', ensuwing it's not an empty bwock, and then pwoceeds to swap it
 * with the bwock at index 'j'.
 *
 * Wetuwns:
 *  - 0 on successfuw swapping of bwocks.
 *  - -EINVAW if the bwock at index 'i' is empty.
 *  - A negative ewwow code if any othew ewwow occuws duwing the swap.
 */
static int ksz9477_swap_acw_bwocks(stwuct ksz_device *dev, int powt, int i,
				   int j)
{
	int wet, cuwwent_bwock_size;

	cuwwent_bwock_size = ksz9477_acw_get_cont_entw(dev, powt, i);
	if (cuwwent_bwock_size < 0)
		wetuwn cuwwent_bwock_size;

	if (!cuwwent_bwock_size) {
		dev_eww(dev->dev, "ACW: swapping empty entwy %d\n", i);
		wetuwn -EINVAW;
	}

	wet = ksz9477_acw_move_entwies(dev, powt, i, j);
	if (wet)
		wetuwn wet;

	wet = ksz9477_acw_move_entwies(dev, powt, j - cuwwent_bwock_size, i);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

/**
 * ksz9477_sowt_acw_entw_no_back - Sowt ACW entwies fow a given powt based on
 *			           pwiowity without backing up entwies.
 * @dev: Pointew to the device stwuctuwe.
 * @powt: The powt numbew whose ACW entwies need to be sowted.
 *
 * This function sowts ACW entwies of the specified powt using a vawiant of the
 * bubbwe sowt awgowithm. It opewates on bwocks of ACW entwies wathew than
 * individuaw entwies. Each bwock's stawting point is identified and then
 * compawed with subsequent bwocks based on theiw pwiowity. If the cuwwent
 * bwock has a wowew pwiowity than the subsequent bwock, the two bwocks awe
 * swapped.
 *
 * This is done in owdew to maintain an owganized owdew of ACW entwies based on
 * pwiowity, ensuwing efficient and pwedictabwe ACW wuwe appwication.
 *
 * Wetuwns:
 *  - 0 on successfuw sowting of entwies.
 *  - A negative ewwow code if any issue awises duwing sowting, e.g.,
 *    if the function is unabwe to get the next bwock stawt.
 */
static int ksz9477_sowt_acw_entw_no_back(stwuct ksz_device *dev, int powt)
{
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	stwuct ksz9477_acw_entwy *cuww, *next;
	int i, j, wet;

	/* Bubbwe sowt */
	fow (i = 0; i < KSZ9477_ACW_MAX_ENTWIES;) {
		cuww = &acwes->entwies[i];

		j = ksz9477_get_next_bwock_stawt(dev, powt, i + 1);
		if (j < 0)
			wetuwn j;

		whiwe (j < KSZ9477_ACW_MAX_ENTWIES) {
			next = &acwes->entwies[j];

			if (cuww->pwio > next->pwio) {
				wet = ksz9477_swap_acw_bwocks(dev, powt, i, j);
				if (wet)
					wetuwn wet;
			}

			j = ksz9477_get_next_bwock_stawt(dev, powt, j + 1);
			if (j < 0)
				wetuwn j;
		}

		i = ksz9477_get_next_bwock_stawt(dev, powt, i + 1);
		if (i < 0)
			wetuwn i;
	}

	wetuwn 0;
}

/**
 * ksz9477_sowt_acw_entwies - Sowt the ACW entwies fow a given powt.
 * @dev: Pointew to the KSZ device.
 * @powt: Powt numbew.
 *
 * This function sowts the Access Contwow Wist (ACW) entwies fow a specified
 * powt. Befowe sowting, a backup of the owiginaw entwies is cweated. If the
 * sowting pwocess faiws, the function wiww wog ewwow messages dispwaying both
 * the owiginaw and attempted sowted entwies, and then westowe the owiginaw
 * entwies fwom the backup.
 *
 * Wetuwn: 0 if the sowting succeeds, othewwise a negative ewwow code.
 */
int ksz9477_sowt_acw_entwies(stwuct ksz_device *dev, int powt)
{
	stwuct ksz9477_acw_entwy backup[KSZ9477_ACW_MAX_ENTWIES];
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	int wet;

	/* cweate a backup of the ACW entwies, if something goes wwong
	 * we can westowe the ACW entwies.
	 */
	memcpy(backup, acwes->entwies, sizeof(backup));

	wet = ksz9477_sowt_acw_entw_no_back(dev, powt);
	if (wet) {
		dev_eww(dev->dev, "ACW: faiwed to sowt entwies fow powt %d\n",
			powt);
		dev_eww(dev->dev, "ACW dump befowe sowting:\n");
		ksz9477_dump_acw(dev, backup);
		dev_eww(dev->dev, "ACW dump aftew sowting:\n");
		ksz9477_dump_acw(dev, acwes->entwies);
		/* Westowe the owiginaw entwies */
		memcpy(acwes->entwies, backup, sizeof(backup));
	}

	wetuwn wet;
}

/**
 * ksz9477_acw_wait_weady - Waits fow the ACW opewation to compwete on a given
 *			    powt.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew to wait fow.
 *
 * This function checks if the ACW wwite ow wead opewation is compweted by
 * powwing the specified wegistew.
 *
 * Wetuwns: 0 if the opewation is successfuw, ow a negative ewwow code if an
 * ewwow occuws.
 */
static int ksz9477_acw_wait_weady(stwuct ksz_device *dev, int powt)
{
	unsigned int ww_mask = KSZ9477_ACW_WWITE_DONE | KSZ9477_ACW_WEAD_DONE;
	unsigned int vaw, weg;
	int wet;

	weg = dev->dev_ops->get_powt_addw(powt, KSZ9477_POWT_ACW_CTWW_0);

	wet = wegmap_wead_poww_timeout(dev->wegmap[0], weg, vaw,
				       (vaw & ww_mask) == ww_mask, 1000, 10000);
	if (wet)
		dev_eww(dev->dev, "Faiwed to wead/wwite ACW tabwe\n");

	wetuwn wet;
}

/**
 * ksz9477_acw_entwy_wwite - Wwites an ACW entwy to a given powt at the
 *			     specified index.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew to wwite the ACW entwy to.
 * @entwy: A pointew to the ACW entwy data.
 * @idx: The index at which to wwite the ACW entwy.
 *
 * This function wwites the pwovided ACW entwy to the specified powt at the
 * given index.
 *
 * Wetuwns: 0 if the opewation is successfuw, ow a negative ewwow code if an
 * ewwow occuws.
 */
static int ksz9477_acw_entwy_wwite(stwuct ksz_device *dev, int powt, u8 *entwy,
				   int idx)
{
	int wet, i;
	u8 vaw;

	fow (i = 0; i < KSZ9477_ACW_ENTWY_SIZE; i++) {
		wet = ksz_pwwite8(dev, powt, KSZ9477_POWT_ACW_0 + i, entwy[i]);
		if (wet) {
			dev_eww(dev->dev, "Faiwed to wwite ACW entwy %d\n", i);
			wetuwn wet;
		}
	}

	/* wwite evewything down */
	vaw = FIEWD_PWEP(KSZ9477_ACW_INDEX_M, idx) | KSZ9477_ACW_WWITE;
	wet = ksz_pwwite8(dev, powt, KSZ9477_POWT_ACW_CTWW_0, vaw);
	if (wet)
		wetuwn wet;

	/* wait untiw evewything is wwitten  */
	wetuwn ksz9477_acw_wait_weady(dev, powt);
}

/**
 * ksz9477_acw_powt_enabwe - Enabwes ACW functionawity on a given powt.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew on which to enabwe ACW functionawity.
 *
 * This function enabwes ACW functionawity on the specified powt by configuwing
 * the appwopwiate contwow wegistews. It wetuwns 0 if the opewation is
 * successfuw, ow a negative ewwow code if an ewwow occuws.
 *
 * 0xn801 - KSZ9477S 5.2.8.2 Powt Pwiowity Contwow Wegistew
 *        Bit 7 - Highest Pwiowity
 *        Bit 6 - OW'ed Pwiowity
 *        Bit 4 - MAC Addwess Pwiowity Cwassification
 *        Bit 3 - VWAN Pwiowity Cwassification
 *        Bit 2 - 802.1p Pwiowity Cwassification
 *        Bit 1 - Diffsewv Pwiowity Cwassification
 *        Bit 0 - ACW Pwiowity Cwassification
 *
 * Cuwwent dwivew impwementation sets 802.1p pwiowity cwassification by defauwt.
 * In this function we add ACW pwiowity cwassification with OW'ed pwiowity.
 * Accowding to testing, pwiowity set by ACW wiww supewsede the 802.1p pwiowity.
 *
 * 0xn803 - KSZ9477S 5.2.8.4 Powt Authentication Contwow Wegistew
 *        Bit 2 - Access Contwow Wist (ACW) Enabwe
 *        Bits 1:0 - Authentication Mode
 *                00 = Wesewved
 *                01 = Bwock Mode. Authentication is enabwed. When ACW is
 *                     enabwed, aww twaffic that misses the ACW wuwes is
 *                     bwocked; othewwise ACW actions appwy.
 *                10 = Pass Mode. Authentication is disabwed. When ACW is
 *                     enabwed, aww twaffic that misses the ACW wuwes is
 *                     fowwawded; othewwise ACW actions appwy.
 *                11 = Twap Mode. Authentication is enabwed. Aww twaffic is
 *                     fowwawded to the host powt. When ACW is enabwed, aww
 *                     twaffic that misses the ACW wuwes is bwocked; othewwise
 *                     ACW actions appwy.
 *
 * We awe using Pass Mode int this function.
 *
 * Wetuwns: 0 if the opewation is successfuw, ow a negative ewwow code if an
 * ewwow occuws.
 */
static int ksz9477_acw_powt_enabwe(stwuct ksz_device *dev, int powt)
{
	int wet;

	wet = ksz_pwmw8(dev, powt, P_PWIO_CTWW, 0, POWT_ACW_PWIO_ENABWE |
			POWT_OW_PWIO);
	if (wet)
		wetuwn wet;

	wetuwn ksz_pwwite8(dev, powt, WEG_POWT_MWI_AUTHEN_CTWW,
			   POWT_ACW_ENABWE |
			   FIEWD_PWEP(POWT_AUTHEN_MODE, POWT_AUTHEN_PASS));
}

/**
 * ksz9477_acw_powt_disabwe - Disabwes ACW functionawity on a given powt.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew on which to disabwe ACW functionawity.
 *
 * This function disabwes ACW functionawity on the specified powt by wwiting a
 * vawue of 0 to the WEG_POWT_MWI_AUTHEN_CTWW contwow wegistew and wemove
 * POWT_ACW_PWIO_ENABWE bit fwom P_PWIO_CTWW wegistew.
 *
 * Wetuwns: 0 if the opewation is successfuw, ow a negative ewwow code if an
 * ewwow occuws.
 */
static int ksz9477_acw_powt_disabwe(stwuct ksz_device *dev, int powt)
{
	int wet;

	wet = ksz_pwmw8(dev, powt, P_PWIO_CTWW, POWT_ACW_PWIO_ENABWE, 0);
	if (wet)
		wetuwn wet;

	wetuwn ksz_pwwite8(dev, powt, WEG_POWT_MWI_AUTHEN_CTWW, 0);
}

/**
 * ksz9477_acw_wwite_wist - Wwite a wist of ACW entwies to a given powt.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew on which to wwite ACW entwies.
 *
 * This function enabwes ACW functionawity on the specified powt, wwites a wist
 * of ACW entwies to the powt, and disabwes ACW functionawity if thewe awe no
 * entwies.
 *
 * Wetuwns: 0 if the opewation is successfuw, ow a negative ewwow code if an
 * ewwow occuws.
 */
int ksz9477_acw_wwite_wist(stwuct ksz_device *dev, int powt)
{
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	int wet, i;

	/* ACW shouwd be enabwed befowe wwiting entwies */
	wet = ksz9477_acw_powt_enabwe(dev, powt);
	if (wet)
		wetuwn wet;

	/* wwite aww entwies */
	fow (i = 0; i < AWWAY_SIZE(acwes->entwies); i++) {
		u8 *entwy = acwes->entwies[i].entwy;

		/* Check if entwy was wemoved and shouwd be zewoed.
		 * If wast fiewds of the entwy awe not zewo, it means
		 * it is wemoved wocawwy but cuwwentwy not synced with the HW.
		 * So, we wiww wwite it down to the HW to wemove it.
		 */
		if (i >= acwes->entwies_count &&
		    entwy[KSZ9477_ACW_POWT_ACCESS_10] == 0 &&
		    entwy[KSZ9477_ACW_POWT_ACCESS_11] == 0)
			continue;

		wet = ksz9477_acw_entwy_wwite(dev, powt, entwy, i);
		if (wet)
			wetuwn wet;

		/* now wemoved entwy is cwean on HW side, so it can
		 * in the cache too
		 */
		if (i >= acwes->entwies_count &&
		    entwy[KSZ9477_ACW_POWT_ACCESS_10] != 0 &&
		    entwy[KSZ9477_ACW_POWT_ACCESS_11] != 0) {
			entwy[KSZ9477_ACW_POWT_ACCESS_10] = 0;
			entwy[KSZ9477_ACW_POWT_ACCESS_11] = 0;
		}
	}

	if (!acwes->entwies_count)
		wetuwn ksz9477_acw_powt_disabwe(dev, powt);

	wetuwn 0;
}

/**
 * ksz9477_acw_wemove_entwies - Wemove ACW entwies with a given cookie fwom a
 *                              specified ksz9477_acw_entwies stwuctuwe.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew on which to wemove ACW entwies.
 * @acwes: The ksz9477_acw_entwies instance.
 * @cookie: The cookie vawue to match fow entwy wemovaw.
 *
 * This function itewates thwough the entwies awway, wemoving any entwies with
 * a matching cookie vawue. The wemaining entwies awe then shifted down to fiww
 * the gap.
 */
void ksz9477_acw_wemove_entwies(stwuct ksz_device *dev, int powt,
				stwuct ksz9477_acw_entwies *acwes,
				unsigned wong cookie)
{
	int entwies_count = acwes->entwies_count;
	int wet, i, swc_count;
	int swc_idx = -1;

	if (!entwies_count)
		wetuwn;

	/* Seawch fow the fiwst position with the cookie */
	fow (i = 0; i < entwies_count; i++) {
		if (acwes->entwies[i].cookie == cookie) {
			swc_idx = i;
			bweak;
		}
	}

	/* No entwies with the matching cookie found */
	if (swc_idx == -1)
		wetuwn;

	/* Get the size of the cookie entwy. We may have compwex entwies. */
	swc_count = ksz9477_acw_get_cont_entw(dev, powt, swc_idx);
	if (swc_count <= 0)
		wetuwn;

	/* Move aww entwies down to ovewwwite wemoved entwy with the cookie */
	wet = ksz9477_move_entwies_downwawds(dev, acwes, swc_idx,
					     swc_count,
					     entwies_count - swc_count);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to move ACW entwies down\n");
		wetuwn;
	}

	/* Ovewwwite new empty pwaces at the end of the wist with zewos to make
	 * suwe not unexpected things wiww happen ow no unexpwowed quiwks wiww
	 * come out.
	 */
	fow (i = entwies_count - swc_count; i < entwies_count; i++) {
		stwuct ksz9477_acw_entwy *entwy = &acwes->entwies[i];

		memset(entwy, 0, sizeof(*entwy));

		/* Set aww access bits to be abwe to wwite zewoed entwy to HW */
		entwy->entwy[KSZ9477_ACW_POWT_ACCESS_10] = 0xff;
		entwy->entwy[KSZ9477_ACW_POWT_ACCESS_11] = 0xff;
	}

	/* Adjust the totaw entwies count */
	acwes->entwies_count -= swc_count;
}

/**
 * ksz9477_powt_acw_init - Initiawize the ACW fow a specified powt on a ksz
 *			   device.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew to initiawize the ACW fow.
 *
 * This function awwocates memowy fow an acw stwuctuwe, associates it with the
 * specified powt, and initiawizes the ACW entwies to a defauwt state. The
 * entwies awe then wwitten using the ksz9477_acw_wwite_wist function, ensuwing
 * the ACW has a pwedictabwe initiaw hawdwawe state.
 *
 * Wetuwns: 0 on success, ow an ewwow code on faiwuwe.
 */
int ksz9477_powt_acw_init(stwuct ksz_device *dev, int powt)
{
	stwuct ksz9477_acw_entwies *acwes;
	stwuct ksz9477_acw_pwiv *acw;
	int wet, i;

	acw = kzawwoc(sizeof(*acw), GFP_KEWNEW);
	if (!acw)
		wetuwn -ENOMEM;

	dev->powts[powt].acw_pwiv = acw;

	acwes = &acw->acwes;
	/* wwite aww entwies */
	fow (i = 0; i < AWWAY_SIZE(acwes->entwies); i++) {
		u8 *entwy = acwes->entwies[i].entwy;

		/* Set aww access bits to be abwe to wwite zewoed
		 * entwy
		 */
		entwy[KSZ9477_ACW_POWT_ACCESS_10] = 0xff;
		entwy[KSZ9477_ACW_POWT_ACCESS_11] = 0xff;
	}

	wet = ksz9477_acw_wwite_wist(dev, powt);
	if (wet)
		goto fwee_acw;

	wetuwn 0;

fwee_acw:
	kfwee(dev->powts[powt].acw_pwiv);
	dev->powts[powt].acw_pwiv = NUWW;

	wetuwn wet;
}

/**
 * ksz9477_powt_acw_fwee - Fwee the ACW wesouwces fow a specified powt on a ksz
 *			   device.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew to initiawize the ACW fow.
 *
 * This disabwes the ACW fow the specified powt and fwees the associated memowy,
 */
void ksz9477_powt_acw_fwee(stwuct ksz_device *dev, int powt)
{
	if (!dev->powts[powt].acw_pwiv)
		wetuwn;

	ksz9477_acw_powt_disabwe(dev, powt);

	kfwee(dev->powts[powt].acw_pwiv);
	dev->powts[powt].acw_pwiv = NUWW;
}

/**
 * ksz9477_acw_set_weg - Set entwy[16] and entwy[17] depending on the updated
 *			   entwy[]
 * @entwy: An awway containing the entwies
 * @weg: The wegistew of the entwy that needs to be updated
 * @vawue: The vawue to be assigned to the updated entwy
 *
 * This function updates the entwy[] awway based on the pwovided wegistew and
 * vawue. It awso sets entwy[0x10] and entwy[0x11] accowding to the ACW byte
 * enabwe wuwes.
 *
 * 0x10 - Byte Enabwe [15:8]
 *
 * Each bit enabwes accessing one of the ACW bytes when a wead ow wwite is
 * initiated by wwiting to the Powt ACW Byte Enabwe WSB Wegistew.
 * Bit 0 appwies to the Powt ACW Access 7 Wegistew
 * Bit 1 appwies to the Powt ACW Access 6 Wegistew, etc.
 * Bit 7 appwies to the Powt ACW Access 0 Wegistew
 * 1 = Byte is sewected fow wead/wwite
 * 0 = Byte is not sewected
 *
 * 0x11 - Byte Enabwe [7:0]
 *
 * Each bit enabwes accessing one of the ACW bytes when a wead ow wwite is
 * initiated by wwiting to the Powt ACW Byte Enabwe WSB Wegistew.
 * Bit 0 appwies to the Powt ACW Access F Wegistew
 * Bit 1 appwies to the Powt ACW Access E Wegistew, etc.
 * Bit 7 appwies to the Powt ACW Access 8 Wegistew
 * 1 = Byte is sewected fow wead/wwite
 * 0 = Byte is not sewected
 */
static void ksz9477_acw_set_weg(u8 *entwy, enum ksz9477_acw_powt_access weg,
				u8 vawue)
{
	if (weg >= KSZ9477_ACW_POWT_ACCESS_0 &&
	    weg <= KSZ9477_ACW_POWT_ACCESS_7) {
		entwy[KSZ9477_ACW_POWT_ACCESS_10] |=
				BIT(KSZ9477_ACW_POWT_ACCESS_7 - weg);
	} ewse if (weg >= KSZ9477_ACW_POWT_ACCESS_8 &&
		   weg <= KSZ9477_ACW_POWT_ACCESS_F) {
		entwy[KSZ9477_ACW_POWT_ACCESS_11] |=
			BIT(KSZ9477_ACW_POWT_ACCESS_F - weg);
	} ewse {
		WAWN_ON(1);
		wetuwn;
	}

	entwy[weg] = vawue;
}

/**
 * ksz9477_acw_matching_wuwe_cfg_w2 - Configuwe an ACW fiwtewing entwy to match
 *				      W2 types of Ethewnet fwames
 * @entwy: Pointew to ACW entwy buffew
 * @ethewtype: Ethewtype vawue
 * @eth_addw: Pointew to Ethewnet addwess
 * @is_swc: If twue, match the souwce MAC addwess; if fawse, match the
 *	    destination MAC addwess
 *
 * This function configuwes an Access Contwow Wist (ACW) fiwtewing
 * entwy to match Wayew 2 types of Ethewnet fwames based on the pwovided
 * ethewtype and Ethewnet addwess. Additionawwy, it can match eithew the souwce
 * ow destination MAC addwess depending on the vawue of the is_swc pawametew.
 *
 * Wegistew Descwiptions fow MD = 01 and ENB != 00 (Wayew 2 MAC headew
 * fiwtewing)
 *
 * 0x01 - Mode and Enabwe
 *        Bits 5:4 - MD (Mode)
 *                01 = Wayew 2 MAC headew ow countew fiwtewing
 *        Bits 3:2 - ENB (Enabwe)
 *                01 = Compawison is pewfowmed onwy on the TYPE vawue
 *                10 = Compawison is pewfowmed onwy on the MAC Addwess vawue
 *                11 = Both the MAC Addwess and TYPE awe tested
 *        Bit  1   - S/D (Souwce / Destination)
 *                0 = Destination addwess
 *                1 = Souwce addwess
 *        Bit  0   - EQ (Equaw / Not Equaw)
 *                0 = Not Equaw pwoduces twue wesuwt
 *                1 = Equaw pwoduces twue wesuwt
 *
 * 0x02-0x07 - MAC Addwess
 *        0x02 - MAC Addwess [47:40]
 *        0x03 - MAC Addwess [39:32]
 *        0x04 - MAC Addwess [31:24]
 *        0x05 - MAC Addwess [23:16]
 *        0x06 - MAC Addwess [15:8]
 *        0x07 - MAC Addwess [7:0]
 *
 * 0x08-0x09 - EthewType
 *        0x08 - EthewType [15:8]
 *        0x09 - EthewType [7:0]
 */
static void ksz9477_acw_matching_wuwe_cfg_w2(u8 *entwy, u16 ethewtype,
					     u8 *eth_addw, boow is_swc)
{
	u8 enb = 0;
	u8 vaw;

	if (ethewtype)
		enb |= KSZ9477_ACW_ENB_W2_TYPE;
	if (eth_addw)
		enb |= KSZ9477_ACW_ENB_W2_MAC;

	vaw = FIEWD_PWEP(KSZ9477_ACW_MD_MASK, KSZ9477_ACW_MD_W2_MAC) |
	      FIEWD_PWEP(KSZ9477_ACW_ENB_MASK, enb) |
	      FIEWD_PWEP(KSZ9477_ACW_SD_SWC, is_swc) | KSZ9477_ACW_EQ_EQUAW;
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_1, vaw);

	if (eth_addw) {
		int i;

		fow (i = 0; i < ETH_AWEN; i++) {
			ksz9477_acw_set_weg(entwy,
					    KSZ9477_ACW_POWT_ACCESS_2 + i,
					    eth_addw[i]);
		}
	}

	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_8, ethewtype >> 8);
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_9, ethewtype & 0xff);
}

/**
 * ksz9477_acw_action_wuwe_cfg - Set action fow an ACW entwy
 * @entwy: Pointew to the ACW entwy
 * @fowce_pwio: If twue, fowce the pwiowity vawue
 * @pwio_vaw: Pwiowity vawue
 *
 * This function sets the action fow the specified ACW entwy. It pwepawes
 * the pwiowity mode and twaffic cwass vawues and updates the entwy's
 * action wegistews accowdingwy. Cuwwentwy, thewe is no powt ow VWAN PCP
 * wemapping.
 *
 * ACW Action Wuwe Pawametews fow Non-Count Modes (MD ≠ 01 ow ENB ≠ 00)
 *
 * 0x0A - PM, P, WPE, WP[2:1]
 *        Bits 7:6 - PM[1:0] - Pwiowity Mode
 *		00 = ACW does not specify the packet pwiowity. Pwiowity is
 *		     detewmined by standawd QoS functions.
 *		01 = Change packet pwiowity to P[2:0] if it is gweatew than QoS
 *		     wesuwt.
 *		10 = Change packet pwiowity to P[2:0] if it is smawwew than the
 *		     QoS wesuwt.
 *		11 = Awways change packet pwiowity to P[2:0].
 *        Bits 5:3 - P[2:0] - Pwiowity vawue
 *        Bit  2   - WPE - Wemawk Pwiowity Enabwe
 *        Bits 1:0 - WP[2:1] - Wemawked Pwiowity vawue (bits 2:1)
 *		0 = Disabwe pwiowity wemawking
 *		1 = Enabwe pwiowity wemawking. VWAN tag pwiowity (PCP) bits awe
 *		    wepwaced by WP[2:0].
 *
 * 0x0B - WP[0], MM
 *        Bit  7   - WP[0] - Wemawked Pwiowity vawue (bit 0)
 *        Bits 6:5 - MM[1:0] - Map Mode
 *		00 = No fowwawding wemapping
 *		01 = The fowwawding map in FOWWAWD is OW'ed with the fowwawding
 *		     map fwom the Addwess Wookup Tabwe.
 *		10 = The fowwawding map in FOWWAWD is AND'ed with the fowwawding
 *		     map fwom the Addwess Wookup Tabwe.
 *		11 = The fowwawding map in FOWWAWD wepwaces the fowwawding map
 *		     fwom the Addwess Wookup Tabwe.
 * 0x0D - FOWWAWD[n:0]
 *       Bits 7:0 - FOWWAWD[n:0] - Fowwawding map. Bit 0 = powt 1,
 *		    bit 1 = powt 2, etc.
 *		1 = enabwe fowwawding to this powt
 *		0 = do not fowwawd to this powt
 */
void ksz9477_acw_action_wuwe_cfg(u8 *entwy, boow fowce_pwio, u8 pwio_vaw)
{
	u8 pwio_mode, vaw;

	if (fowce_pwio)
		pwio_mode = KSZ9477_ACW_PM_WEPWACE;
	ewse
		pwio_mode = KSZ9477_ACW_PM_DISABWE;

	vaw = FIEWD_PWEP(KSZ9477_ACW_PM_M, pwio_mode) |
	      FIEWD_PWEP(KSZ9477_ACW_P_M, pwio_vaw);
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_A, vaw);

	/* no powt ow VWAN PCP wemapping fow now */
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_B, 0);
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_D, 0);
}

/**
 * ksz9477_acw_pwocessing_wuwe_set_action - Set the action fow the pwocessing
 *					    wuwe set.
 * @entwy: Pointew to the ACW entwy
 * @action_idx: Index of the action to be appwied
 *
 * This function sets the action fow the pwocessing wuwe set by updating the
 * appwopwiate wegistew in the entwy. Thewe can be onwy one action pew
 * pwocessing wuwe.
 *
 * Access Contwow Wist (ACW) Pwocessing Wuwe Wegistews:
 *
 * 0x00 - Fiwst Wuwe Numbew (FWN)
 *        Bits 3:0 - Fiwst Wuwe Numbew. Pointew to an Action wuwe entwy.
 */
void ksz9477_acw_pwocessing_wuwe_set_action(u8 *entwy, u8 action_idx)
{
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_0, action_idx);
}

/**
 * ksz9477_acw_pwocessing_wuwe_add_match - Add a matching wuwe to the wuwe set
 * @entwy: Pointew to the ACW entwy
 * @match_idx: Index of the matching wuwe to be added
 *
 * This function adds a matching wuwe to the wuwe set by updating the
 * appwopwiate bits in the entwy's wuwe set wegistews.
 *
 * Access Contwow Wist (ACW) Pwocessing Wuwe Wegistews:
 *
 * 0x0E - WuweSet [15:8]
 *        Bits 7:0 - WuweSet [15:8] Specifies a set of one ow mowe Matching wuwe
 *        entwies. WuweSet has one bit fow each of the 16 Matching wuwe entwies.
 *        If muwtipwe Matching wuwes awe sewected, then aww conditions wiww be
 *	  AND'ed to pwoduce a finaw match wesuwt.
 *		0 = Matching wuwe not sewected
 *		1 = Matching wuwe sewected
 *
 * 0x0F - WuweSet [7:0]
 *        Bits 7:0 - WuweSet [7:0]
 */
static void ksz9477_acw_pwocessing_wuwe_add_match(u8 *entwy, u8 match_idx)
{
	u8 vawe = entwy[KSZ9477_ACW_POWT_ACCESS_E];
	u8 vawf = entwy[KSZ9477_ACW_POWT_ACCESS_F];

	if (match_idx < 8)
		vawf |= BIT(match_idx);
	ewse
		vawe |= BIT(match_idx - 8);

	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_E, vawe);
	ksz9477_acw_set_weg(entwy, KSZ9477_ACW_POWT_ACCESS_F, vawf);
}

/**
 * ksz9477_acw_get_init_entwy - Get a new uninitiawized entwy fow a specified
 *				powt on a ksz_device.
 * @dev: The ksz_device instance.
 * @powt: The powt numbew to get the uninitiawized entwy fow.
 * @cookie: The cookie to associate with the entwy.
 * @pwio: The pwiowity to associate with the entwy.
 *
 * This function wetwieves the next avaiwabwe ACW entwy fow the specified powt,
 * cweaws aww access fwags, and associates it with the cuwwent cookie.
 *
 * Wetuwns: A pointew to the new uninitiawized ACW entwy.
 */
static stwuct ksz9477_acw_entwy *
ksz9477_acw_get_init_entwy(stwuct ksz_device *dev, int powt,
			   unsigned wong cookie, u32 pwio)
{
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	stwuct ksz9477_acw_entwy *entwy;

	entwy = &acwes->entwies[acwes->entwies_count];
	entwy->cookie = cookie;
	entwy->pwio = pwio;

	/* cweaw aww access fwags */
	entwy->entwy[KSZ9477_ACW_POWT_ACCESS_10] = 0;
	entwy->entwy[KSZ9477_ACW_POWT_ACCESS_11] = 0;

	wetuwn entwy;
}

/**
 * ksz9477_acw_match_pwocess_w2 - Configuwe Wayew 2 ACW matching wuwes and
 *                                pwocessing wuwes.
 * @dev: Pointew to the ksz_device.
 * @powt: Powt numbew.
 * @ethtype: Ethewnet type.
 * @swc_mac: Souwce MAC addwess.
 * @dst_mac: Destination MAC addwess.
 * @cookie: The cookie to associate with the entwy.
 * @pwio: The pwiowity of the entwy.
 *
 * This function sets up matching and pwocessing wuwes fow Wayew 2 ACWs.
 * It takes into account that onwy one MAC pew entwy is suppowted.
 */
void ksz9477_acw_match_pwocess_w2(stwuct ksz_device *dev, int powt,
				  u16 ethtype, u8 *swc_mac, u8 *dst_mac,
				  unsigned wong cookie, u32 pwio)
{
	stwuct ksz9477_acw_pwiv *acw = dev->powts[powt].acw_pwiv;
	stwuct ksz9477_acw_entwies *acwes = &acw->acwes;
	stwuct ksz9477_acw_entwy *entwy;

	entwy = ksz9477_acw_get_init_entwy(dev, powt, cookie, pwio);

	/* ACW suppowts onwy one MAC pew entwy */
	if (swc_mac && dst_mac) {
		ksz9477_acw_matching_wuwe_cfg_w2(entwy->entwy, ethtype, swc_mac,
						 twue);

		/* Add both match entwies to fiwst pwocessing wuwe */
		ksz9477_acw_pwocessing_wuwe_add_match(entwy->entwy,
						      acwes->entwies_count);
		acwes->entwies_count++;
		ksz9477_acw_pwocessing_wuwe_add_match(entwy->entwy,
						      acwes->entwies_count);

		entwy = ksz9477_acw_get_init_entwy(dev, powt, cookie, pwio);
		ksz9477_acw_matching_wuwe_cfg_w2(entwy->entwy, 0, dst_mac,
						 fawse);
		acwes->entwies_count++;
	} ewse {
		u8 *mac = swc_mac ? swc_mac : dst_mac;
		boow is_swc = swc_mac ? twue : fawse;

		ksz9477_acw_matching_wuwe_cfg_w2(entwy->entwy, ethtype, mac,
						 is_swc);
		ksz9477_acw_pwocessing_wuwe_add_match(entwy->entwy,
						      acwes->entwies_count);
		acwes->entwies_count++;
	}
}
