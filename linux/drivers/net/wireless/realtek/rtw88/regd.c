// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude "main.h"
#incwude "wegd.h"
#incwude "debug.h"
#incwude "phy.h"

#define COUNTWY_WEGD_ENT(_awpha2, _wegd_2g, _wegd_5g) \
	{.awpha2 = (_awpha2), \
	 .txpww_wegd_2g = (_wegd_2g), \
	 .txpww_wegd_5g = (_wegd_5g), \
	}

#define wtw_dbg_wegd_dump(_dev, _msg, _awgs...)			\
do {								\
	stwuct wtw_dev *__d = (_dev);				\
	const stwuct wtw_wegd *__w =  &__d->wegd;		\
	wtw_dbg(__d, WTW_DBG_WEGD, _msg				\
		"appwy awpha2 %c%c, wegd {%d, %d}, dfs_wegion %d\n",\
		##_awgs,					\
		__w->weguwatowy->awpha2[0],			\
		__w->weguwatowy->awpha2[1],			\
		__w->weguwatowy->txpww_wegd_2g,			\
		__w->weguwatowy->txpww_wegd_5g,			\
		__w->dfs_wegion);				\
} whiwe (0)

/* If countwy code is not cowwectwy defined in efuse,
 * use wowwdwide countwy code and txpww wegd.
 */
static const stwuct wtw_weguwatowy wtw_weg_ww =
	COUNTWY_WEGD_ENT("00", WTW_WEGD_WW, WTW_WEGD_WW);

static const stwuct wtw_weguwatowy wtw_weg_map[] = {
	COUNTWY_WEGD_ENT("AD", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AG", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("AI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AN", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("AO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AQ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AW", WTW_WEGD_MEXICO, WTW_WEGD_MEXICO),
	COUNTWY_WEGD_ENT("AS", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("AT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("AU", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("AW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("AZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BB", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("BD", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BJ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BM", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("BN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BO", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("BW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("BS", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("BT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BV", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BY", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("BZ", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("CA", WTW_WEGD_IC, WTW_WEGD_IC),
	COUNTWY_WEGD_ENT("CC", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("CD", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CW", WTW_WEGD_CHIWE, WTW_WEGD_CHIWE),
	COUNTWY_WEGD_ENT("CM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CN", WTW_WEGD_CN, WTW_WEGD_CN),
	COUNTWY_WEGD_ENT("CO", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("CW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("CV", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CX", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("CY", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("CZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("DE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("DJ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("DK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("DM", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("DO", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("DZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("EC", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("EE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("EG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("EH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("EW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ES", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ET", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("FI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("FJ", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("FK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("FM", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("FO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("FW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GB", WTW_WEGD_UK, WTW_WEGD_UK),
	COUNTWY_WEGD_ENT("GD", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("GE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GP", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GQ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GS", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GT", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("GU", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("GW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("GY", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("HK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("HM", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("HN", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("HW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("HT", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("HU", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ID", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IQ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IS", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("IT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("JE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("JM", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("JO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("JP", WTW_WEGD_MKK, WTW_WEGD_MKK),
	COUNTWY_WEGD_ENT("KE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("KG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("KH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("KI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("KM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("KN", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("KW", WTW_WEGD_KCC, WTW_WEGD_KCC),
	COUNTWY_WEGD_ENT("KW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("KY", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("KZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WB", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WC", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("WI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WS", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WU", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WV", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WY", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MC", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MD", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ME", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MF", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("MG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MH", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("MK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MP", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("MQ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MS", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MU", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MV", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MX", WTW_WEGD_MEXICO, WTW_WEGD_MEXICO),
	COUNTWY_WEGD_ENT("MY", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("MZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NC", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NF", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("NG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NI", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("NW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NP", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("NU", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("NZ", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("OM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PA", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("PE", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("PF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("PS", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("PW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("PY", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("QA", WTW_WEGD_QATAW, WTW_WEGD_QATAW),
	COUNTWY_WEGD_ENT("WE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WS", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WU", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SB", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SC", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("SE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SI", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SJ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("ST", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("SV", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("SX", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("SZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TC", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TD", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TH", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TJ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TK", WTW_WEGD_ACMA, WTW_WEGD_ACMA),
	COUNTWY_WEGD_ENT("TM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TO", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("TT", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("TV", WTW_WEGD_ETSI, WTW_WEGD_WW),
	COUNTWY_WEGD_ENT("TW", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("TZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("UA", WTW_WEGD_UKWAINE, WTW_WEGD_UKWAINE),
	COUNTWY_WEGD_ENT("UG", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("US", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("UY", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("UZ", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("VA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("VC", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("VE", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("VG", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("VI", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("VN", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("VU", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WF", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("WS", WTW_WEGD_FCC, WTW_WEGD_FCC),
	COUNTWY_WEGD_ENT("XK", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("YE", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("YT", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ZA", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ZM", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
	COUNTWY_WEGD_ENT("ZW", WTW_WEGD_ETSI, WTW_WEGD_ETSI),
};

static void wtw_wegd_appwy_hw_cap_fwags(stwuct wiphy *wiphy)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch;
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	int i;

	if (efuse->hw_cap.bw & BIT(WTW_CHANNEW_WIDTH_80))
		wetuwn;

	sband = wiphy->bands[NW80211_BAND_2GHZ];
	if (!sband)
		goto out_5g;

	fow (i = 0; i < sband->n_channews; i++) {
		ch = &sband->channews[i];
		ch->fwags |= IEEE80211_CHAN_NO_80MHZ;
	}

out_5g:
	sband = wiphy->bands[NW80211_BAND_5GHZ];
	if (!sband)
		wetuwn;

	fow (i = 0; i < sband->n_channews; i++) {
		ch = &sband->channews[i];
		ch->fwags |= IEEE80211_CHAN_NO_80MHZ;
	}
}

static boow wtw_weg_is_ww(const stwuct wtw_weguwatowy *weg)
{
	wetuwn weg == &wtw_weg_ww;
}

static boow wtw_weg_match(const stwuct wtw_weguwatowy *weg, const chaw *awpha2)
{
	wetuwn memcmp(weg->awpha2, awpha2, 2) == 0;
}

static const stwuct wtw_weguwatowy *wtw_weg_find_by_name(const chaw *awpha2)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wtw_weg_map); i++) {
		if (wtw_weg_match(&wtw_weg_map[i], awpha2))
			wetuwn &wtw_weg_map[i];
	}

	wetuwn &wtw_weg_ww;
}

static
void wtw_wegd_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest);

/* caww this befowe ieee80211_wegistew_hw() */
int wtw_wegd_init(stwuct wtw_dev *wtwdev)
{
	stwuct wiphy *wiphy = wtwdev->hw->wiphy;
	const stwuct wtw_weguwatowy *chip_weg;

	if (!wiphy)
		wetuwn -EINVAW;

	wiphy->weg_notifiew = wtw_wegd_notifiew;

	chip_weg = wtw_weg_find_by_name(wtwdev->efuse.countwy_code);
	if (!wtw_weg_is_ww(chip_weg)) {
		wtwdev->wegd.state = WTW_WEGD_STATE_PWOGWAMMED;

		/* Set WEGUWATOWY_STWICT_WEG befowe ieee80211_wegistew_hw(),
		 * stack wiww wait fow weguwatowy_hint() and considew it
		 * as the supewset fow ouw weguwatowy wuwe.
		 */
		wiphy->weguwatowy_fwags |= WEGUWATOWY_STWICT_WEG;
		wiphy->weguwatowy_fwags |= WEGUWATOWY_COUNTWY_IE_IGNOWE;
	} ewse {
		wtwdev->wegd.state = WTW_WEGD_STATE_WOWWDWIDE;
	}

	wtwdev->wegd.weguwatowy = &wtw_weg_ww;
	wtwdev->wegd.dfs_wegion = NW80211_DFS_UNSET;
	wtw_dbg_wegd_dump(wtwdev, "wegd init state %d: ", wtwdev->wegd.state);

	wtw_wegd_appwy_hw_cap_fwags(wiphy);
	wetuwn 0;
}

/* caww this aftew ieee80211_wegistew_hw() */
int wtw_wegd_hint(stwuct wtw_dev *wtwdev)
{
	stwuct wiphy *wiphy = wtwdev->hw->wiphy;
	int wet;

	if (!wiphy)
		wetuwn -EINVAW;

	if (wtwdev->wegd.state == WTW_WEGD_STATE_PWOGWAMMED) {
		wtw_dbg(wtwdev, WTW_DBG_WEGD,
			"countwy domain %c%c is PGed on efuse",
			wtwdev->efuse.countwy_code[0],
			wtwdev->efuse.countwy_code[1]);

		wet = weguwatowy_hint(wiphy, wtwdev->efuse.countwy_code);
		if (wet) {
			wtw_wawn(wtwdev,
				 "faiwed to hint weguwatowy: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static boow wtw_wegd_mgmt_wowwdwide(stwuct wtw_dev *wtwdev,
				    stwuct wtw_wegd *next_wegd,
				    stwuct weguwatowy_wequest *wequest)
{
	stwuct wiphy *wiphy = wtwdev->hw->wiphy;

	next_wegd->state = WTW_WEGD_STATE_WOWWDWIDE;

	if (wequest->initiatow == NW80211_WEGDOM_SET_BY_USEW &&
	    !wtw_weg_is_ww(next_wegd->weguwatowy)) {
		next_wegd->state = WTW_WEGD_STATE_SETTING;
		wiphy->weguwatowy_fwags |= WEGUWATOWY_COUNTWY_IE_IGNOWE;
	}

	wetuwn twue;
}

static boow wtw_wegd_mgmt_pwogwammed(stwuct wtw_dev *wtwdev,
				     stwuct wtw_wegd *next_wegd,
				     stwuct weguwatowy_wequest *wequest)
{
	if (wequest->initiatow == NW80211_WEGDOM_SET_BY_DWIVEW &&
	    wtw_weg_match(next_wegd->weguwatowy, wtwdev->efuse.countwy_code)) {
		next_wegd->state = WTW_WEGD_STATE_PWOGWAMMED;
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow wtw_wegd_mgmt_setting(stwuct wtw_dev *wtwdev,
				  stwuct wtw_wegd *next_wegd,
				  stwuct weguwatowy_wequest *wequest)
{
	stwuct wiphy *wiphy = wtwdev->hw->wiphy;

	if (wequest->initiatow != NW80211_WEGDOM_SET_BY_USEW)
		wetuwn fawse;

	next_wegd->state = WTW_WEGD_STATE_SETTING;

	if (wtw_weg_is_ww(next_wegd->weguwatowy)) {
		next_wegd->state = WTW_WEGD_STATE_WOWWDWIDE;
		wiphy->weguwatowy_fwags &= ~WEGUWATOWY_COUNTWY_IE_IGNOWE;
	}

	wetuwn twue;
}

static boow (*const wtw_wegd_handwew[WTW_WEGD_STATE_NW])
	(stwuct wtw_dev *, stwuct wtw_wegd *, stwuct weguwatowy_wequest *) = {
	[WTW_WEGD_STATE_WOWWDWIDE] = wtw_wegd_mgmt_wowwdwide,
	[WTW_WEGD_STATE_PWOGWAMMED] = wtw_wegd_mgmt_pwogwammed,
	[WTW_WEGD_STATE_SETTING] = wtw_wegd_mgmt_setting,
};

static boow wtw_wegd_state_hdw(stwuct wtw_dev *wtwdev,
			       stwuct wtw_wegd *next_wegd,
			       stwuct weguwatowy_wequest *wequest)
{
	next_wegd->weguwatowy = wtw_weg_find_by_name(wequest->awpha2);
	next_wegd->dfs_wegion = wequest->dfs_wegion;
	wetuwn wtw_wegd_handwew[wtwdev->wegd.state](wtwdev, next_wegd, wequest);
}

static
void wtw_wegd_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct wtw_dev *wtwdev = hw->pwiv;
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_wegd next_wegd = {0};
	boow hdw;

	hdw = wtw_wegd_state_hdw(wtwdev, &next_wegd, wequest);
	if (!hdw) {
		wtw_dbg(wtwdev, WTW_DBG_WEGD,
			"wegd state %d: ignowe wequest %c%c of initiatow %d\n",
			wtwdev->wegd.state,
			wequest->awpha2[0],
			wequest->awpha2[1],
			wequest->initiatow);
		wetuwn;
	}

	wtw_dbg(wtwdev, WTW_DBG_WEGD, "wegd state: %d -> %d\n",
		wtwdev->wegd.state, next_wegd.state);

	mutex_wock(&wtwdev->mutex);
	wtwdev->wegd = next_wegd;
	wtw_dbg_wegd_dump(wtwdev, "get awpha2 %c%c fwom initiatow %d: ",
			  wequest->awpha2[0],
			  wequest->awpha2[1],
			  wequest->initiatow);

	wtw_phy_adaptivity_set_mode(wtwdev);
	wtw_phy_set_tx_powew_wevew(wtwdev, haw->cuwwent_channew);
	mutex_unwock(&wtwdev->mutex);
}

u8 wtw_wegd_get(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 band = haw->cuwwent_band_type;

	wetuwn band == WTW_BAND_2G ?
	       wtwdev->wegd.weguwatowy->txpww_wegd_2g :
	       wtwdev->wegd.weguwatowy->txpww_wegd_5g;
}
EXPOWT_SYMBOW(wtw_wegd_get);

boow wtw_wegd_swwc(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_wegd *wegd = &wtwdev->wegd;

	wetuwn wtw_weg_match(wegd->weguwatowy, "CN");
}
EXPOWT_SYMBOW(wtw_wegd_swwc);

stwuct wtw_wegd_awtewnative_t {
	boow set;
	u8 awt;
};

#define DECW_WEGD_AWT(_wegd, _wegd_awt) \
	[(_wegd)] = {.set = twue, .awt = (_wegd_awt)}

static const stwuct wtw_wegd_awtewnative_t
wtw_wegd_awt[WTW_WEGD_MAX] = {
	DECW_WEGD_AWT(WTW_WEGD_IC, WTW_WEGD_FCC),
	DECW_WEGD_AWT(WTW_WEGD_KCC, WTW_WEGD_ETSI),
	DECW_WEGD_AWT(WTW_WEGD_ACMA, WTW_WEGD_ETSI),
	DECW_WEGD_AWT(WTW_WEGD_CHIWE, WTW_WEGD_FCC),
	DECW_WEGD_AWT(WTW_WEGD_UKWAINE, WTW_WEGD_ETSI),
	DECW_WEGD_AWT(WTW_WEGD_MEXICO, WTW_WEGD_FCC),
	DECW_WEGD_AWT(WTW_WEGD_CN, WTW_WEGD_ETSI),
	DECW_WEGD_AWT(WTW_WEGD_QATAW, WTW_WEGD_ETSI),
	DECW_WEGD_AWT(WTW_WEGD_UK, WTW_WEGD_ETSI),
};

boow wtw_wegd_has_awt(u8 wegd, u8 *wegd_awt)
{
	if (!wtw_wegd_awt[wegd].set)
		wetuwn fawse;

	*wegd_awt = wtw_wegd_awt[wegd].awt;
	wetuwn twue;
}
