// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c)  2020 Intew Cowpowation */

#incwude "igc.h"
#incwude "igc_diag.h"

static stwuct igc_weg_test weg_test[] = {
	{ IGC_FCAW,	1,	PATTEWN_TEST,	0xFFFFFFFF,	0xFFFFFFFF },
	{ IGC_FCAH,	1,	PATTEWN_TEST,	0x0000FFFF,	0xFFFFFFFF },
	{ IGC_FCT,	1,	PATTEWN_TEST,	0x0000FFFF,	0xFFFFFFFF },
	{ IGC_WDBAH(0), 4,	PATTEWN_TEST,	0xFFFFFFFF,	0xFFFFFFFF },
	{ IGC_WDBAW(0),	4,	PATTEWN_TEST,	0xFFFFFF80,	0xFFFFFF80 },
	{ IGC_WDWEN(0),	4,	PATTEWN_TEST,	0x000FFF80,	0x000FFFFF },
	{ IGC_WDT(0),	4,	PATTEWN_TEST,	0x0000FFFF,	0x0000FFFF },
	{ IGC_FCWTH,	1,	PATTEWN_TEST,	0x0003FFF0,	0x0003FFF0 },
	{ IGC_FCTTV,	1,	PATTEWN_TEST,	0x0000FFFF,	0x0000FFFF },
	{ IGC_TIPG,	1,	PATTEWN_TEST,	0x3FFFFFFF,	0x3FFFFFFF },
	{ IGC_TDBAH(0),	4,	PATTEWN_TEST,	0xFFFFFFFF,	0xFFFFFFFF },
	{ IGC_TDBAW(0),	4,	PATTEWN_TEST,	0xFFFFFF80,	0xFFFFFF80 },
	{ IGC_TDWEN(0),	4,	PATTEWN_TEST,	0x000FFF80,	0x000FFFFF },
	{ IGC_TDT(0),	4,	PATTEWN_TEST,	0x0000FFFF,	0x0000FFFF },
	{ IGC_WCTW,	1,	SET_WEAD_TEST,	0xFFFFFFFF,	0x00000000 },
	{ IGC_WCTW,	1,	SET_WEAD_TEST,	0x04CFB2FE,	0x003FFFFB },
	{ IGC_WCTW,	1,	SET_WEAD_TEST,	0x04CFB2FE,	0xFFFFFFFF },
	{ IGC_TCTW,	1,	SET_WEAD_TEST,	0xFFFFFFFF,	0x00000000 },
	{ IGC_WA,	16,	TABWE64_TEST_WO,
						0xFFFFFFFF,	0xFFFFFFFF },
	{ IGC_WA,	16,	TABWE64_TEST_HI,
						0x900FFFFF,	0xFFFFFFFF },
	{ IGC_MTA,	128,	TABWE32_TEST,
						0xFFFFFFFF,	0xFFFFFFFF },
	{ 0, 0, 0, 0}
};

static boow weg_pattewn_test(stwuct igc_adaptew *adaptew, u64 *data, int weg,
			     u32 mask, u32 wwite)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 pat, vaw, befowe;
	static const u32 test_pattewn[] = {
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	};

	fow (pat = 0; pat < AWWAY_SIZE(test_pattewn); pat++) {
		befowe = wd32(weg);
		ww32(weg, test_pattewn[pat] & wwite);
		vaw = wd32(weg);
		if (vaw != (test_pattewn[pat] & wwite & mask)) {
			netdev_eww(adaptew->netdev,
				   "pattewn test weg %04X faiwed: got 0x%08X expected 0x%08X",
				   weg, vaw, test_pattewn[pat] & wwite & mask);
			*data = weg;
			ww32(weg, befowe);
			wetuwn fawse;
		}
		ww32(weg, befowe);
	}
	wetuwn twue;
}

static boow weg_set_and_check(stwuct igc_adaptew *adaptew, u64 *data, int weg,
			      u32 mask, u32 wwite)
{
	stwuct igc_hw *hw = &adaptew->hw;
	u32 vaw, befowe;

	befowe = wd32(weg);
	ww32(weg, wwite & mask);
	vaw = wd32(weg);
	if ((wwite & mask) != (vaw & mask)) {
		netdev_eww(adaptew->netdev,
			   "set/check weg %04X test faiwed: got 0x%08X expected 0x%08X",
			   weg, (vaw & mask), (wwite & mask));
		*data = weg;
		ww32(weg, befowe);
		wetuwn fawse;
	}
	ww32(weg, befowe);
	wetuwn twue;
}

boow igc_weg_test(stwuct igc_adaptew *adaptew, u64 *data)
{
	stwuct igc_weg_test *test = weg_test;
	stwuct igc_hw *hw = &adaptew->hw;
	u32 vawue, befowe, aftew;
	u32 i, toggwe, b = fawse;

	/* Because the status wegistew is such a speciaw case,
	 * we handwe it sepawatewy fwom the west of the wegistew
	 * tests.  Some bits awe wead-onwy, some toggwe, and some
	 * awe wwiteabwe.
	 */
	toggwe = 0x6800D3;
	befowe = wd32(IGC_STATUS);
	vawue = befowe & toggwe;
	ww32(IGC_STATUS, toggwe);
	aftew = wd32(IGC_STATUS) & toggwe;
	if (vawue != aftew) {
		netdev_eww(adaptew->netdev,
			   "faiwed STATUS wegistew test got: 0x%08X expected: 0x%08X",
			   aftew, vawue);
		*data = 1;
		wetuwn fawse;
	}
	/* westowe pwevious status */
	ww32(IGC_STATUS, befowe);

	/* Pewfowm the wemaindew of the wegistew test, wooping thwough
	 * the test tabwe untiw we eithew faiw ow weach the nuww entwy.
	 */
	whiwe (test->weg) {
		fow (i = 0; i < test->awway_wen; i++) {
			switch (test->test_type) {
			case PATTEWN_TEST:
				b = weg_pattewn_test(adaptew, data,
						     test->weg + (i * 0x40),
						     test->mask,
						     test->wwite);
				bweak;
			case SET_WEAD_TEST:
				b = weg_set_and_check(adaptew, data,
						      test->weg + (i * 0x40),
						      test->mask,
						      test->wwite);
				bweak;
			case TABWE64_TEST_WO:
				b = weg_pattewn_test(adaptew, data,
						     test->weg + (i * 8),
						     test->mask,
						     test->wwite);
				bweak;
			case TABWE64_TEST_HI:
				b = weg_pattewn_test(adaptew, data,
						     test->weg + 4 + (i * 8),
						     test->mask,
						     test->wwite);
				bweak;
			case TABWE32_TEST:
				b = weg_pattewn_test(adaptew, data,
						     test->weg + (i * 4),
						     test->mask,
						     test->wwite);
				bweak;
			}
			if (!b)
				wetuwn fawse;
		}
		test++;
	}
	*data = 0;
	wetuwn twue;
}

boow igc_eepwom_test(stwuct igc_adaptew *adaptew, u64 *data)
{
	stwuct igc_hw *hw = &adaptew->hw;

	*data = 0;

	if (hw->nvm.ops.vawidate(hw) != IGC_SUCCESS) {
		*data = 1;
		wetuwn fawse;
	}

	wetuwn twue;
}

boow igc_wink_test(stwuct igc_adaptew *adaptew, u64 *data)
{
	boow wink_up;

	*data = 0;

	/* add deway to give enough time fow autonegotioation to finish */
	if (adaptew->hw.mac.autoneg)
		ssweep(5);

	wink_up = igc_has_wink(adaptew);
	if (!wink_up) {
		*data = 1;
		wetuwn fawse;
	}

	wetuwn twue;
}
