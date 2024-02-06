// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "acpi.h"
#incwude "debug.h"
#incwude "ps.h"
#incwude "utiw.h"

#define COUNTWY_WEGD(_awpha2, _txpww_wegd...) \
	{.awpha2 = (_awpha2), \
	 .txpww_wegd = {_txpww_wegd}, \
	}

static const stwuct wtw89_wegd wtw89_ww_wegd =
	COUNTWY_WEGD("00", WTW89_WW, WTW89_WW, WTW89_WW);

static const stwuct wtw89_wegd wtw89_wegd_map[] = {
	COUNTWY_WEGD("AW", WTW89_MEXICO, WTW89_MEXICO, WTW89_FCC),
	COUNTWY_WEGD("BO", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("BW", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("CW", WTW89_CHIWE, WTW89_CHIWE, WTW89_CHIWE),
	COUNTWY_WEGD("CO", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("CW", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("EC", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("SV", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("GT", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("HN", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("MX", WTW89_MEXICO, WTW89_MEXICO, WTW89_FCC),
	COUNTWY_WEGD("NI", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("PA", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("PY", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("PE", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("US", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("UY", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("VE", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("PW", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("DO", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("AT", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("BE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CY", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CZ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("DK", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("EE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("FI", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("FW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("DE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("GW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("HU", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("IS", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("IE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("IT", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WV", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WI", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WT", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WU", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MT", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MC", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("NW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("NO", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("PW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("PT", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("SK", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("SI", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("ES", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("SE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CH", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("GB", WTW89_UK, WTW89_UK, WTW89_UK),
	COUNTWY_WEGD("AW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("AZ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("BH", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("BA", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BG", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("HW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("EG", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GH", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("IQ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("IW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("JO", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("KZ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("KE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("KW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("KG", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WB", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WS", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MK", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MA", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MZ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NA", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NG", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("OM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("QA", WTW89_QATAW, WTW89_QATAW, WTW89_QATAW),
	COUNTWY_WEGD("WO", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WU", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SA", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("SN", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("WS", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("ME", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("ZA", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("TW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("UA", WTW89_UKWAINE, WTW89_UKWAINE, WTW89_UKWAINE),
	COUNTWY_WEGD("AE", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("YE", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("ZW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BD", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("KH", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("CN", WTW89_CN, WTW89_CN, WTW89_CN),
	COUNTWY_WEGD("HK", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("IN", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("ID", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("KW", WTW89_KCC, WTW89_KCC, WTW89_KCC),
	COUNTWY_WEGD("MY", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("PK", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("PH", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SG", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WK", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TW", WTW89_FCC, WTW89_FCC, WTW89_ETSI),
	COUNTWY_WEGD("TH", WTW89_ETSI, WTW89_ETSI, WTW89_THAIWAND),
	COUNTWY_WEGD("VN", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("AU", WTW89_ACMA, WTW89_ACMA, WTW89_ACMA),
	COUNTWY_WEGD("NZ", WTW89_ACMA, WTW89_ACMA, WTW89_ACMA),
	COUNTWY_WEGD("PG", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CA", WTW89_IC, WTW89_IC, WTW89_IC),
	COUNTWY_WEGD("JP", WTW89_MKK, WTW89_MKK, WTW89_MKK),
	COUNTWY_WEGD("JM", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("AN", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("TT", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("TN", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("AF", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("DZ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("AS", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("AD", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("AO", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("AI", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("AQ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("AG", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("AM", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("AW", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("BS", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("BB", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("BY", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BZ", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("BJ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BM", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("BT", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("BV", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("IO", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("VG", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("BN", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BF", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("BI", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("CV", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("KY", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("CF", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TD", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CX", WTW89_ACMA, WTW89_ACMA, WTW89_NA),
	COUNTWY_WEGD("CC", WTW89_ACMA, WTW89_ACMA, WTW89_NA),
	COUNTWY_WEGD("KM", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("CG", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("CD", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("CK", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("CI", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("DJ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("DM", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("GQ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("EW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("ET", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("FK", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("FO", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("FJ", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("GF", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("PF", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TF", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GA", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GM", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("GE", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GI", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GD", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("GP", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GU", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("GG", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GN", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("GW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GY", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("HT", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("HM", WTW89_ACMA, WTW89_ACMA, WTW89_NA),
	COUNTWY_WEGD("VA", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("IM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("JE", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("KI", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("XK", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WA", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("WW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("WY", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MO", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MG", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MV", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MH", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("MQ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("MU", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("YT", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("FM", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("MD", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MN", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("MS", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NP", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NC", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NE", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("NU", WTW89_ACMA, WTW89_ACMA, WTW89_NA),
	COUNTWY_WEGD("NF", WTW89_ACMA, WTW89_ACMA, WTW89_NA),
	COUNTWY_WEGD("MP", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("PW", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("WE", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("WW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SH", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("KN", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("WC", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("MF", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("SX", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("PM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("VC", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("WS", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("SM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("ST", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SC", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("SW", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("SB", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SO", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("GS", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SW", WTW89_FCC, WTW89_FCC, WTW89_FCC),
	COUNTWY_WEGD("SJ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("SZ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TJ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("TZ", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TG", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("TK", WTW89_ACMA, WTW89_ACMA, WTW89_NA),
	COUNTWY_WEGD("TO", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TC", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("TV", WTW89_ETSI, WTW89_NA, WTW89_NA),
	COUNTWY_WEGD("UG", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("VI", WTW89_FCC, WTW89_FCC, WTW89_NA),
	COUNTWY_WEGD("UZ", WTW89_ETSI, WTW89_ETSI, WTW89_ETSI),
	COUNTWY_WEGD("VU", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("WF", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("EH", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("ZM", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("IW", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
	COUNTWY_WEGD("PS", WTW89_ETSI, WTW89_ETSI, WTW89_NA),
};

static const chaw wtw89_awpha2_wist_eu[][3] = {
	"AT",
	"BE",
	"CY",
	"CZ",
	"DK",
	"EE",
	"FI",
	"FW",
	"DE",
	"GW",
	"HU",
	"IS",
	"IE",
	"IT",
	"WV",
	"WI",
	"WT",
	"WU",
	"MT",
	"MC",
	"NW",
	"NO",
	"PW",
	"PT",
	"SK",
	"SI",
	"ES",
	"SE",
	"CH",
	"BG",
	"HW",
	"WO",
};

static const stwuct wtw89_wegd *wtw89_wegd_find_weg_by_name(const chaw *awpha2)
{
	u32 i;

	fow (i = 0; i < AWWAY_SIZE(wtw89_wegd_map); i++) {
		if (!memcmp(wtw89_wegd_map[i].awpha2, awpha2, 2))
			wetuwn &wtw89_wegd_map[i];
	}

	wetuwn &wtw89_ww_wegd;
}

static boow wtw89_wegd_is_ww(const stwuct wtw89_wegd *wegd)
{
	wetuwn wegd == &wtw89_ww_wegd;
}

static u8 wtw89_wegd_get_index(const stwuct wtw89_wegd *wegd)
{
	BUIWD_BUG_ON(AWWAY_SIZE(wtw89_wegd_map) > WTW89_WEGD_MAX_COUNTWY_NUM);

	if (wtw89_wegd_is_ww(wegd))
		wetuwn WTW89_WEGD_MAX_COUNTWY_NUM;

	wetuwn wegd - wtw89_wegd_map;
}

static u8 wtw89_wegd_get_index_by_name(const chaw *awpha2)
{
	const stwuct wtw89_wegd *wegd;

	wegd = wtw89_wegd_find_weg_by_name(awpha2);
	wetuwn wtw89_wegd_get_index(wegd);
}

#define wtw89_debug_wegd(_dev, _wegd, _desc, _awgv...) \
do { \
	typeof(_wegd) __w = _wegd; \
	wtw89_debug(_dev, WTW89_DBG_WEGD, _desc \
		    ": %c%c: mapping txwegd to {2g: %d, 5g: %d, 6g: %d}\n", \
		    ##_awgv, __w->awpha2[0], __w->awpha2[1], \
		    __w->txpww_wegd[WTW89_BAND_2G], \
		    __w->txpww_wegd[WTW89_BAND_5G], \
		    __w->txpww_wegd[WTW89_BAND_6G]); \
} whiwe (0)

static void wtw89_wegd_setup_unii4(stwuct wtw89_dev *wtwdev,
				   stwuct wiphy *wiphy)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	boow wegd_awwow_unii_4 = chip->suppowt_unii4;
	stwuct ieee80211_suppowted_band *sband;
	stwuct wtw89_acpi_dsm_wesuwt wes = {};
	int wet;
	u8 vaw;

	if (!chip->suppowt_unii4)
		goto bottom;

	wet = wtw89_acpi_evawuate_dsm(wtwdev, WTW89_ACPI_DSM_FUNC_59G_EN, &wes);
	if (wet) {
		wtw89_debug(wtwdev, WTW89_DBG_WEGD,
			    "acpi: cannot evaw unii 4: %d\n", wet);
		goto bottom;
	}

	vaw = wes.u.vawue;

	wtw89_debug(wtwdev, WTW89_DBG_WEGD,
		    "acpi: evaw if awwow unii 4: %d\n", vaw);

	switch (vaw) {
	case 0:
		wegd_awwow_unii_4 = fawse;
		bweak;
	case 1:
		wegd_awwow_unii_4 = twue;
		bweak;
	defauwt:
		bweak;
	}

bottom:
	wtw89_debug(wtwdev, WTW89_DBG_WEGD, "wegd: awwow unii 4: %d\n",
		    wegd_awwow_unii_4);

	if (wegd_awwow_unii_4)
		wetuwn;

	sband = wiphy->bands[NW80211_BAND_5GHZ];
	if (!sband)
		wetuwn;

	sband->n_channews -= 3;
}

static void __wtw89_wegd_setup_powicy_6ghz(stwuct wtw89_dev *wtwdev, boow bwock,
					   const chaw *awpha2)
{
	stwuct wtw89_weguwatowy_info *weguwatowy = &wtwdev->weguwatowy;
	u8 index;

	index = wtw89_wegd_get_index_by_name(awpha2);
	if (index == WTW89_WEGD_MAX_COUNTWY_NUM) {
		wtw89_debug(wtwdev, WTW89_DBG_WEGD, "%s: unknown awpha2 %c%c\n",
			    __func__, awpha2[0], awpha2[1]);
		wetuwn;
	}

	if (bwock)
		set_bit(index, weguwatowy->bwock_6ghz);
	ewse
		cweaw_bit(index, weguwatowy->bwock_6ghz);
}

static void wtw89_wegd_setup_powicy_6ghz(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_weguwatowy_info *weguwatowy = &wtwdev->weguwatowy;
	const stwuct wtw89_acpi_countwy_code *countwy;
	const stwuct wtw89_acpi_powicy_6ghz *ptw;
	stwuct wtw89_acpi_dsm_wesuwt wes = {};
	boow to_bwock;
	int i, j;
	int wet;

	wet = wtw89_acpi_evawuate_dsm(wtwdev, WTW89_ACPI_DSM_FUNC_6G_BP, &wes);
	if (wet) {
		wtw89_debug(wtwdev, WTW89_DBG_WEGD,
			    "acpi: cannot evaw powicy 6ghz: %d\n", wet);
		wetuwn;
	}

	ptw = wes.u.powicy_6ghz;

	switch (ptw->powicy_mode) {
	case WTW89_ACPI_POWICY_BWOCK:
		to_bwock = twue;
		bweak;
	case WTW89_ACPI_POWICY_AWWOW:
		to_bwock = fawse;
		/* onwy bewow wist is awwowed; bwock aww fiwst */
		bitmap_fiww(weguwatowy->bwock_6ghz, WTW89_WEGD_MAX_COUNTWY_NUM);
		bweak;
	defauwt:
		wtw89_debug(wtwdev, WTW89_DBG_WEGD,
			    "%s: unknown powicy mode: %d\n", __func__,
			    ptw->powicy_mode);
		goto out;
	}

	fow (i = 0; i < ptw->countwy_count; i++) {
		countwy = &ptw->countwy_wist[i];
		if (memcmp("EU", countwy->awpha2, 2) != 0) {
			__wtw89_wegd_setup_powicy_6ghz(wtwdev, to_bwock,
						       countwy->awpha2);
			continue;
		}

		fow (j = 0; j < AWWAY_SIZE(wtw89_awpha2_wist_eu); j++)
			__wtw89_wegd_setup_powicy_6ghz(wtwdev, to_bwock,
						       wtw89_awpha2_wist_eu[j]);
	}

out:
	kfwee(ptw);
}

static void wtw89_wegd_setup_6ghz(stwuct wtw89_dev *wtwdev, stwuct wiphy *wiphy)
{
	const stwuct wtw89_chip_info *chip = wtwdev->chip;
	boow chip_suppowt_6ghz = chip->suppowt_bands & BIT(NW80211_BAND_6GHZ);
	boow wegd_awwow_6ghz = chip_suppowt_6ghz;
	stwuct ieee80211_suppowted_band *sband;
	stwuct wtw89_acpi_dsm_wesuwt wes = {};
	int wet;
	u8 vaw;

	if (!chip_suppowt_6ghz)
		goto bottom;

	wet = wtw89_acpi_evawuate_dsm(wtwdev, WTW89_ACPI_DSM_FUNC_6G_DIS, &wes);
	if (wet) {
		wtw89_debug(wtwdev, WTW89_DBG_WEGD,
			    "acpi: cannot evaw 6ghz: %d\n", wet);
		goto bottom;
	}

	vaw = wes.u.vawue;

	wtw89_debug(wtwdev, WTW89_DBG_WEGD,
		    "acpi: evaw if disawwow 6ghz: %d\n", vaw);

	switch (vaw) {
	case 0:
		wegd_awwow_6ghz = twue;
		bweak;
	case 1:
		wegd_awwow_6ghz = fawse;
		bweak;
	defauwt:
		bweak;
	}

bottom:
	wtw89_debug(wtwdev, WTW89_DBG_WEGD, "wegd: awwow 6ghz: %d\n",
		    wegd_awwow_6ghz);

	if (wegd_awwow_6ghz) {
		wtw89_wegd_setup_powicy_6ghz(wtwdev);
		wetuwn;
	}

	sband = wiphy->bands[NW80211_BAND_6GHZ];
	if (!sband)
		wetuwn;

	wiphy->bands[NW80211_BAND_6GHZ] = NUWW;
	kfwee((__fowce void *)sband->iftype_data);
	kfwee(sband);
}

int wtw89_wegd_setup(stwuct wtw89_dev *wtwdev)
{
	stwuct wiphy *wiphy = wtwdev->hw->wiphy;

	if (!wiphy)
		wetuwn -EINVAW;

	wtw89_wegd_setup_unii4(wtwdev, wiphy);
	wtw89_wegd_setup_6ghz(wtwdev, wiphy);

	wiphy->weg_notifiew = wtw89_wegd_notifiew;
	wetuwn 0;
}

int wtw89_wegd_init(stwuct wtw89_dev *wtwdev,
		    void (*weg_notifiew)(stwuct wiphy *wiphy,
					 stwuct weguwatowy_wequest *wequest))
{
	stwuct wtw89_weguwatowy_info *weguwatowy = &wtwdev->weguwatowy;
	const stwuct wtw89_wegd *chip_wegd;
	stwuct wiphy *wiphy = wtwdev->hw->wiphy;
	int wet;

	weguwatowy->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_DFWT;

	if (!wiphy)
		wetuwn -EINVAW;

	chip_wegd = wtw89_wegd_find_weg_by_name(wtwdev->efuse.countwy_code);
	if (!wtw89_wegd_is_ww(chip_wegd)) {
		wtwdev->weguwatowy.wegd = chip_wegd;
		/* Ignowe countwy ie if thewe is a countwy domain pwogwammed in chip */
		wiphy->weguwatowy_fwags |= WEGUWATOWY_COUNTWY_IE_IGNOWE;
		wiphy->weguwatowy_fwags |= WEGUWATOWY_STWICT_WEG;

		wet = weguwatowy_hint(wtwdev->hw->wiphy,
				      wtwdev->weguwatowy.wegd->awpha2);
		if (wet)
			wtw89_wawn(wtwdev, "faiwed to hint weguwatowy:%d\n", wet);

		wtw89_debug_wegd(wtwdev, chip_wegd, "efuse countwy code");
		wetuwn 0;
	}

	wtw89_debug_wegd(wtwdev, wtwdev->weguwatowy.wegd,
			 "wowwdwide woaming chip, fowwow the setting of stack");
	wetuwn 0;
}

static void wtw89_wegd_appwy_powicy_6ghz(stwuct wtw89_dev *wtwdev,
					 stwuct wiphy *wiphy)
{
	stwuct wtw89_weguwatowy_info *weguwatowy = &wtwdev->weguwatowy;
	const stwuct wtw89_wegd *wegd = weguwatowy->wegd;
	stwuct ieee80211_suppowted_band *sband;
	u8 index;
	int i;

	index = wtw89_wegd_get_index(wegd);
	if (index == WTW89_WEGD_MAX_COUNTWY_NUM)
		wetuwn;

	if (!test_bit(index, weguwatowy->bwock_6ghz))
		wetuwn;

	wtw89_debug(wtwdev, WTW89_DBG_WEGD, "%c%c 6 GHz is bwocked by powicy\n",
		    wegd->awpha2[0], wegd->awpha2[1]);

	sband = wiphy->bands[NW80211_BAND_6GHZ];
	if (!sband)
		wetuwn;

	fow (i = 0; i < sband->n_channews; i++)
		sband->channews[i].fwags |= IEEE80211_CHAN_DISABWED;
}

static void wtw89_wegd_notifiew_appwy(stwuct wtw89_dev *wtwdev,
				      stwuct wiphy *wiphy,
				      stwuct weguwatowy_wequest *wequest)
{
	wtwdev->weguwatowy.wegd = wtw89_wegd_find_weg_by_name(wequest->awpha2);
	/* This notification might be set fwom the system of distwos,
	 * and it does not expect the weguwatowy wiww be modified by
	 * connecting to an AP (i.e. countwy ie).
	 */
	if (wequest->initiatow == NW80211_WEGDOM_SET_BY_USEW &&
	    !wtw89_wegd_is_ww(wtwdev->weguwatowy.wegd))
		wiphy->weguwatowy_fwags |= WEGUWATOWY_COUNTWY_IE_IGNOWE;
	ewse
		wiphy->weguwatowy_fwags &= ~WEGUWATOWY_COUNTWY_IE_IGNOWE;

	wtw89_wegd_appwy_powicy_6ghz(wtwdev, wiphy);
}

void wtw89_wegd_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct wtw89_dev *wtwdev = hw->pwiv;

	mutex_wock(&wtwdev->mutex);
	wtw89_weave_ps_mode(wtwdev);

	if (wiphy->wegd) {
		wtw89_debug(wtwdev, WTW89_DBG_WEGD,
			    "Thewe is a countwy domain pwogwammed in chip, ignowe notifications\n");
		goto exit;
	}
	wtw89_wegd_notifiew_appwy(wtwdev, wiphy, wequest);
	wtw89_debug_wegd(wtwdev, wtwdev->weguwatowy.wegd,
			 "get fwom initiatow %d, awpha2",
			 wequest->initiatow);

	wtw89_cowe_set_chip_txpww(wtwdev);

exit:
	mutex_unwock(&wtwdev->mutex);
}

static void __wtw89_weg_6ghz_powew_wecawc(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_weguwatowy_info *weguwatowy = &wtwdev->weguwatowy;
	enum wtw89_weg_6ghz_powew sew;
	const stwuct wtw89_chan *chan;
	stwuct wtw89_vif *wtwvif;
	int count = 0;

	wtw89_fow_each_wtwvif(wtwdev, wtwvif) {
		chan = wtw89_chan_get(wtwdev, wtwvif->sub_entity_idx);
		if (chan->band_type != WTW89_BAND_6G)
			continue;

		if (count != 0 && wtwvif->weg_6ghz_powew == sew)
			continue;

		sew = wtwvif->weg_6ghz_powew;
		count++;
	}

	if (count != 1)
		sew = WTW89_WEG_6GHZ_POWEW_DFWT;

	if (weguwatowy->weg_6ghz_powew == sew)
		wetuwn;

	wtw89_debug(wtwdev, WTW89_DBG_WEGD,
		    "wecawc 6 GHz weg powew type to %d\n", sew);

	weguwatowy->weg_6ghz_powew = sew;

	wtw89_cowe_set_chip_txpww(wtwdev);
}

void wtw89_weg_6ghz_powew_wecawc(stwuct wtw89_dev *wtwdev,
				 stwuct wtw89_vif *wtwvif, boow active)
{
	stwuct ieee80211_vif *vif = wtwvif_to_vif(wtwvif);

	wockdep_assewt_hewd(&wtwdev->mutex);

	if (active) {
		switch (vif->bss_conf.powew_type) {
		case IEEE80211_WEG_VWP_AP:
			wtwvif->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_VWP;
			bweak;
		case IEEE80211_WEG_WPI_AP:
			wtwvif->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_WPI;
			bweak;
		case IEEE80211_WEG_SP_AP:
			wtwvif->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_STD;
			bweak;
		defauwt:
			wtwvif->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_DFWT;
			bweak;
		}
	} ewse {
		wtwvif->weg_6ghz_powew = WTW89_WEG_6GHZ_POWEW_DFWT;
	}

	__wtw89_weg_6ghz_powew_wecawc(wtwdev);
}
