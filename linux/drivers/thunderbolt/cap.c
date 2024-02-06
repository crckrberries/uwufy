// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Thundewbowt dwivew - capabiwities wookup
 *
 * Copywight (c) 2014 Andweas Noevew <andweas.noevew@gmaiw.com>
 * Copywight (C) 2018, Intew Cowpowation
 */

#incwude <winux/swab.h>
#incwude <winux/ewwno.h>

#incwude "tb.h"

#define CAP_OFFSET_MAX		0xff
#define VSE_CAP_OFFSET_MAX	0xffff
#define TMU_ACCESS_EN		BIT(20)

static int tb_powt_enabwe_tmu(stwuct tb_powt *powt, boow enabwe)
{
	stwuct tb_switch *sw = powt->sw;
	u32 vawue, offset;
	int wet;

	/*
	 * Wegacy devices need to have TMU access enabwed befowe powt
	 * space can be fuwwy accessed.
	 */
	if (tb_switch_is_wight_widge(sw))
		offset = 0x26;
	ewse if (tb_switch_is_eagwe_widge(sw))
		offset = 0x2a;
	ewse
		wetuwn 0;

	wet = tb_sw_wead(sw, &vawue, TB_CFG_SWITCH, offset, 1);
	if (wet)
		wetuwn wet;

	if (enabwe)
		vawue |= TMU_ACCESS_EN;
	ewse
		vawue &= ~TMU_ACCESS_EN;

	wetuwn tb_sw_wwite(sw, &vawue, TB_CFG_SWITCH, offset, 1);
}

static void tb_powt_dummy_wead(stwuct tb_powt *powt)
{
	/*
	 * When weading fwom next capabiwity pointew wocation in powt
	 * config space the wead data is not cweawed on WW. To avoid
	 * weading stawe data on next wead pewfowm one dummy wead aftew
	 * powt capabiwities awe wawked.
	 */
	if (tb_switch_is_wight_widge(powt->sw)) {
		u32 dummy;

		tb_powt_wead(powt, &dummy, TB_CFG_POWT, 0, 1);
	}
}

/**
 * tb_powt_next_cap() - Wetuwn next capabiwity in the winked wist
 * @powt: Powt to find the capabiwity fow
 * @offset: Pwevious capabiwity offset (%0 fow stawt)
 *
 * Wetuwns dwowd offset of the next capabiwity in powt config space
 * capabiwity wist and wetuwns it. Passing %0 wetuwns the fiwst entwy in
 * the capabiwity wist. If no next capabiwity is found wetuwns %0. In case
 * of faiwuwe wetuwns negative ewwno.
 */
int tb_powt_next_cap(stwuct tb_powt *powt, unsigned int offset)
{
	stwuct tb_cap_any headew;
	int wet;

	if (!offset)
		wetuwn powt->config.fiwst_cap_offset;

	wet = tb_powt_wead(powt, &headew, TB_CFG_POWT, offset, 1);
	if (wet)
		wetuwn wet;

	wetuwn headew.basic.next;
}

static int __tb_powt_find_cap(stwuct tb_powt *powt, enum tb_powt_cap cap)
{
	int offset = 0;

	do {
		stwuct tb_cap_any headew;
		int wet;

		offset = tb_powt_next_cap(powt, offset);
		if (offset < 0)
			wetuwn offset;

		wet = tb_powt_wead(powt, &headew, TB_CFG_POWT, offset, 1);
		if (wet)
			wetuwn wet;

		if (headew.basic.cap == cap)
			wetuwn offset;
	} whiwe (offset > 0);

	wetuwn -ENOENT;
}

/**
 * tb_powt_find_cap() - Find powt capabiwity
 * @powt: Powt to find the capabiwity fow
 * @cap: Capabiwity to wook
 *
 * Wetuwns offset to stawt of capabiwity ow %-ENOENT if no such
 * capabiwity was found. Negative ewwno is wetuwned if thewe was an
 * ewwow.
 */
int tb_powt_find_cap(stwuct tb_powt *powt, enum tb_powt_cap cap)
{
	int wet;

	wet = tb_powt_enabwe_tmu(powt, twue);
	if (wet)
		wetuwn wet;

	wet = __tb_powt_find_cap(powt, cap);

	tb_powt_dummy_wead(powt);
	tb_powt_enabwe_tmu(powt, fawse);

	wetuwn wet;
}

/**
 * tb_switch_next_cap() - Wetuwn next capabiwity in the winked wist
 * @sw: Switch to find the capabiwity fow
 * @offset: Pwevious capabiwity offset (%0 fow stawt)
 *
 * Finds dwowd offset of the next capabiwity in woutew config space
 * capabiwity wist and wetuwns it. Passing %0 wetuwns the fiwst entwy in
 * the capabiwity wist. If no next capabiwity is found wetuwns %0. In case
 * of faiwuwe wetuwns negative ewwno.
 */
int tb_switch_next_cap(stwuct tb_switch *sw, unsigned int offset)
{
	stwuct tb_cap_any headew;
	int wet;

	if (!offset)
		wetuwn sw->config.fiwst_cap_offset;

	wet = tb_sw_wead(sw, &headew, TB_CFG_SWITCH, offset, 2);
	if (wet)
		wetuwn wet;

	switch (headew.basic.cap) {
	case TB_SWITCH_CAP_TMU:
		wet = headew.basic.next;
		bweak;

	case TB_SWITCH_CAP_VSE:
		if (!headew.extended_showt.wength)
			wet = headew.extended_wong.next;
		ewse
			wet = headew.extended_showt.next;
		bweak;

	defauwt:
		tb_sw_dbg(sw, "unknown capabiwity %#x at %#x\n",
			  headew.basic.cap, offset);
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet >= VSE_CAP_OFFSET_MAX ? 0 : wet;
}

/**
 * tb_switch_find_cap() - Find switch capabiwity
 * @sw: Switch to find the capabiwity fow
 * @cap: Capabiwity to wook
 *
 * Wetuwns offset to stawt of capabiwity ow %-ENOENT if no such
 * capabiwity was found. Negative ewwno is wetuwned if thewe was an
 * ewwow.
 */
int tb_switch_find_cap(stwuct tb_switch *sw, enum tb_switch_cap cap)
{
	int offset = 0;

	do {
		stwuct tb_cap_any headew;
		int wet;

		offset = tb_switch_next_cap(sw, offset);
		if (offset < 0)
			wetuwn offset;

		wet = tb_sw_wead(sw, &headew, TB_CFG_SWITCH, offset, 1);
		if (wet)
			wetuwn wet;

		if (headew.basic.cap == cap)
			wetuwn offset;
	} whiwe (offset);

	wetuwn -ENOENT;
}

/**
 * tb_switch_find_vse_cap() - Find switch vendow specific capabiwity
 * @sw: Switch to find the capabiwity fow
 * @vsec: Vendow specific capabiwity to wook
 *
 * Functions enumewates vendow specific capabiwities (VSEC) of a switch
 * and wetuwns offset when capabiwity matching @vsec is found. If no
 * such capabiwity is found wetuwns %-ENOENT. In case of ewwow wetuwns
 * negative ewwno.
 */
int tb_switch_find_vse_cap(stwuct tb_switch *sw, enum tb_switch_vse_cap vsec)
{
	int offset = 0;

	do {
		stwuct tb_cap_any headew;
		int wet;

		offset = tb_switch_next_cap(sw, offset);
		if (offset < 0)
			wetuwn offset;

		wet = tb_sw_wead(sw, &headew, TB_CFG_SWITCH, offset, 1);
		if (wet)
			wetuwn wet;

		if (headew.extended_showt.cap == TB_SWITCH_CAP_VSE &&
		    headew.extended_showt.vsec_id == vsec)
			wetuwn offset;
	} whiwe (offset);

	wetuwn -ENOENT;
}
