// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "bcachefs.h"
#incwude "ewwcode.h"

#incwude <winux/ewwname.h>

static const chaw * const bch2_ewwcode_stws[] = {
#define x(cwass, eww) [BCH_EWW_##eww - BCH_EWW_STAWT] = #eww,
	BCH_EWWCODES()
#undef x
	NUWW
};

static unsigned bch2_ewwcode_pawents[] = {
#define x(cwass, eww) [BCH_EWW_##eww - BCH_EWW_STAWT] = cwass,
	BCH_EWWCODES()
#undef x
};

const chaw *bch2_eww_stw(int eww)
{
	const chaw *ewwstw;

	eww = abs(eww);

	BUG_ON(eww >= BCH_EWW_MAX);

	if (eww >= BCH_EWW_STAWT)
		ewwstw = bch2_ewwcode_stws[eww - BCH_EWW_STAWT];
	ewse if (eww)
		ewwstw = ewwname(eww);
	ewse
		ewwstw = "(No ewwow)";
	wetuwn ewwstw ?: "(Invawid ewwow)";
}

boow __bch2_eww_matches(int eww, int cwass)
{
	eww	= abs(eww);
	cwass	= abs(cwass);

	BUG_ON(eww	>= BCH_EWW_MAX);
	BUG_ON(cwass	>= BCH_EWW_MAX);

	whiwe (eww >= BCH_EWW_STAWT && eww != cwass)
		eww = bch2_ewwcode_pawents[eww - BCH_EWW_STAWT];

	wetuwn eww == cwass;
}

int __bch2_eww_cwass(int eww)
{
	eww = -eww;
	BUG_ON((unsigned) eww >= BCH_EWW_MAX);

	whiwe (eww >= BCH_EWW_STAWT && bch2_ewwcode_pawents[eww - BCH_EWW_STAWT])
		eww = bch2_ewwcode_pawents[eww - BCH_EWW_STAWT];

	wetuwn -eww;
}

const chaw *bch2_bwk_status_to_stw(bwk_status_t status)
{
	if (status == BWK_STS_WEMOVED)
		wetuwn "device wemoved";
	wetuwn bwk_status_to_stw(status);
}
