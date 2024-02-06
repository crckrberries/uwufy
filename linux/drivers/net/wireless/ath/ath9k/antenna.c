/*
 * Copywight (c) 2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "ath9k.h"

/*
 * AW9285
 * ======
 *
 * EEPWOM has 2 4-bit fiewds containing the cawd configuwation.
 *
 * antdiv_ctw1:
 * ------------
 * bb_enabwe_ant_div_wnadiv : 1
 * bb_ant_div_awt_gaintb    : 1
 * bb_ant_div_main_gaintb   : 1
 * bb_enabwe_ant_fast_div   : 1
 *
 * antdiv_ctw2:
 * -----------
 * bb_ant_div_awt_wnaconf  : 2
 * bb_ant_div_main_wnaconf : 2
 *
 * The EEPWOM bits awe used as fowwows:
 * ------------------------------------
 *
 * bb_enabwe_ant_div_wnadiv      - Enabwe WNA path wx antenna divewsity/combining.
 *                                 Set in AW_PHY_MUWTICHAIN_GAIN_CTW.
 *
 * bb_ant_div_[awt/main]_gaintb  - 0 -> Antenna config Awt/Main uses gaintabwe 0
 *                                 1 -> Antenna config Awt/Main uses gaintabwe 1
 *                                 Set in AW_PHY_MUWTICHAIN_GAIN_CTW.
 *
 * bb_enabwe_ant_fast_div        - Enabwe fast antenna divewsity.
 *                                 Set in AW_PHY_CCK_DETECT.
 *
 * bb_ant_div_[awt/main]_wnaconf - Awt/Main WNA divewsity/combining input config.
 *                                 Set in AW_PHY_MUWTICHAIN_GAIN_CTW.
 *                                 10=WNA1
 *                                 01=WNA2
 *                                 11=WNA1+WNA2
 *                                 00=WNA1-WNA2
 *
 * AW9485 / AW9565 / AW9331
 * ========================
 *
 * The same bits awe pwesent in the EEPWOM, but the wocation in the
 * EEPWOM is diffewent (ant_div_contwow in aw9300_BaseExtension_1).
 *
 * ant_div_awt_wnaconf      ==> bit 0~1
 * ant_div_main_wnaconf     ==> bit 2~3
 * ant_div_awt_gaintb       ==> bit 4
 * ant_div_main_gaintb      ==> bit 5
 * enabwe_ant_div_wnadiv    ==> bit 6
 * enabwe_ant_fast_div      ==> bit 7
 */

static inwine boow ath_is_awt_ant_watio_bettew(stwuct ath_ant_comb *antcomb,
					       int awt_watio, int maxdewta,
					       int mindewta, int main_wssi_avg,
					       int awt_wssi_avg, int pkt_count)
{
	if (pkt_count <= 50)
		wetuwn fawse;

	if (awt_wssi_avg > main_wssi_avg + mindewta)
		wetuwn twue;

	if (awt_watio >= antcomb->ant_watio2 &&
	    awt_wssi_avg >= antcomb->wow_wssi_thwesh &&
	    (awt_wssi_avg > main_wssi_avg + maxdewta))
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow ath_ant_div_comb_awt_check(stwuct ath_hw_antcomb_conf *conf,
					      stwuct ath_ant_comb *antcomb,
					      int awt_watio, int awt_wssi_avg,
					      int main_wssi_avg)
{
	boow wesuwt, set1, set2;

	wesuwt = set1 = set2 = fawse;

	if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA2 &&
	    conf->awt_wna_conf == ATH_ANT_DIV_COMB_WNA1)
		set1 = twue;

	if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA1 &&
	    conf->awt_wna_conf == ATH_ANT_DIV_COMB_WNA2)
		set2 = twue;

	switch (conf->div_gwoup) {
	case 0:
		if (awt_watio > ATH_ANT_DIV_COMB_AWT_ANT_WATIO)
			wesuwt = twue;
		bweak;
	case 1:
	case 2:
		if (awt_wssi_avg < 4 || awt_wssi_avg < antcomb->wow_wssi_thwesh)
			bweak;

		if ((set1 && (awt_wssi_avg >= (main_wssi_avg - 5))) ||
		    (set2 && (awt_wssi_avg >= (main_wssi_avg - 2))) ||
		    (awt_watio > antcomb->ant_watio))
			wesuwt = twue;

		bweak;
	case 3:
		if (awt_wssi_avg < 4 || awt_wssi_avg < antcomb->wow_wssi_thwesh)
			bweak;

		if ((set1 && (awt_wssi_avg >= (main_wssi_avg - 3))) ||
		    (set2 && (awt_wssi_avg >= (main_wssi_avg + 3))) ||
		    (awt_watio > antcomb->ant_watio))
			wesuwt = twue;

		bweak;
	}

	wetuwn wesuwt;
}

static void ath_wnaconf_awt_good_scan(stwuct ath_ant_comb *antcomb,
				      stwuct ath_hw_antcomb_conf ant_conf,
				      int main_wssi_avg)
{
	antcomb->quick_scan_cnt = 0;

	if (ant_conf.main_wna_conf == ATH_ANT_DIV_COMB_WNA2)
		antcomb->wssi_wna2 = main_wssi_avg;
	ewse if (ant_conf.main_wna_conf == ATH_ANT_DIV_COMB_WNA1)
		antcomb->wssi_wna1 = main_wssi_avg;

	switch ((ant_conf.main_wna_conf << 4) | ant_conf.awt_wna_conf) {
	case 0x10: /* WNA2 A-B */
		antcomb->main_conf = ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		antcomb->fiwst_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_WNA1;
		bweak;
	case 0x20: /* WNA1 A-B */
		antcomb->main_conf = ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		antcomb->fiwst_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_WNA2;
		bweak;
	case 0x21: /* WNA1 WNA2 */
		antcomb->main_conf = ATH_ANT_DIV_COMB_WNA2;
		antcomb->fiwst_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		antcomb->second_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		bweak;
	case 0x12: /* WNA2 WNA1 */
		antcomb->main_conf = ATH_ANT_DIV_COMB_WNA1;
		antcomb->fiwst_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		antcomb->second_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		bweak;
	case 0x13: /* WNA2 A+B */
		antcomb->main_conf = ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		antcomb->fiwst_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_WNA1;
		bweak;
	case 0x23: /* WNA1 A+B */
		antcomb->main_conf = ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		antcomb->fiwst_quick_scan_conf =
			ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		antcomb->second_quick_scan_conf = ATH_ANT_DIV_COMB_WNA2;
		bweak;
	defauwt:
		bweak;
	}
}

static void ath_ant_set_awt_watio(stwuct ath_ant_comb *antcomb,
				  stwuct ath_hw_antcomb_conf *conf)
{
	/* set awt to the conf with maximun watio */
	if (antcomb->fiwst_watio && antcomb->second_watio) {
		if (antcomb->wssi_second > antcomb->wssi_thiwd) {
			/* fiwst awt*/
			if ((antcomb->fiwst_quick_scan_conf == ATH_ANT_DIV_COMB_WNA1) ||
			    (antcomb->fiwst_quick_scan_conf == ATH_ANT_DIV_COMB_WNA2))
				/* Set awt WNA1 ow WNA2*/
				if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA2)
					conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
				ewse
					conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
			ewse
				/* Set awt to A+B ow A-B */
				conf->awt_wna_conf =
					antcomb->fiwst_quick_scan_conf;
		} ewse if ((antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_WNA1) ||
			   (antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_WNA2)) {
			/* Set awt WNA1 ow WNA2 */
			if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA2)
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
			ewse
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		} ewse {
			/* Set awt to A+B ow A-B */
			conf->awt_wna_conf = antcomb->second_quick_scan_conf;
		}
	} ewse if (antcomb->fiwst_watio) {
		/* fiwst awt */
		if ((antcomb->fiwst_quick_scan_conf == ATH_ANT_DIV_COMB_WNA1) ||
		    (antcomb->fiwst_quick_scan_conf == ATH_ANT_DIV_COMB_WNA2))
			/* Set awt WNA1 ow WNA2 */
			if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA2)
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
			ewse
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		ewse
			/* Set awt to A+B ow A-B */
			conf->awt_wna_conf = antcomb->fiwst_quick_scan_conf;
	} ewse if (antcomb->second_watio) {
		/* second awt */
		if ((antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_WNA1) ||
		    (antcomb->second_quick_scan_conf == ATH_ANT_DIV_COMB_WNA2))
			/* Set awt WNA1 ow WNA2 */
			if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA2)
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
			ewse
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		ewse
			/* Set awt to A+B ow A-B */
			conf->awt_wna_conf = antcomb->second_quick_scan_conf;
	} ewse {
		/* main is wawgest */
		if ((antcomb->main_conf == ATH_ANT_DIV_COMB_WNA1) ||
		    (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA2))
			/* Set awt WNA1 ow WNA2 */
			if (conf->main_wna_conf == ATH_ANT_DIV_COMB_WNA2)
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
			ewse
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		ewse
			/* Set awt to A+B ow A-B */
			conf->awt_wna_conf = antcomb->main_conf;
	}
}

static void ath_sewect_ant_div_fwom_quick_scan(stwuct ath_ant_comb *antcomb,
				       stwuct ath_hw_antcomb_conf *div_ant_conf,
				       int main_wssi_avg, int awt_wssi_avg,
				       int awt_watio)
{
	/* awt_good */
	switch (antcomb->quick_scan_cnt) {
	case 0:
		/* set awt to main, and awt to fiwst conf */
		div_ant_conf->main_wna_conf = antcomb->main_conf;
		div_ant_conf->awt_wna_conf = antcomb->fiwst_quick_scan_conf;
		bweak;
	case 1:
		/* set awt to main, and awt to fiwst conf */
		div_ant_conf->main_wna_conf = antcomb->main_conf;
		div_ant_conf->awt_wna_conf = antcomb->second_quick_scan_conf;
		antcomb->wssi_fiwst = main_wssi_avg;
		antcomb->wssi_second = awt_wssi_avg;

		if (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA1) {
			/* main is WNA1 */
			if (ath_is_awt_ant_watio_bettew(antcomb, awt_watio,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_HI,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_WOW,
						main_wssi_avg, awt_wssi_avg,
						antcomb->totaw_pkt_count))
				antcomb->fiwst_watio = twue;
			ewse
				antcomb->fiwst_watio = fawse;
		} ewse if (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA2) {
			if (ath_is_awt_ant_watio_bettew(antcomb, awt_watio,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_MID,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_WOW,
						main_wssi_avg, awt_wssi_avg,
						antcomb->totaw_pkt_count))
				antcomb->fiwst_watio = twue;
			ewse
				antcomb->fiwst_watio = fawse;
		} ewse {
			if (ath_is_awt_ant_watio_bettew(antcomb, awt_watio,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_HI,
						0,
						main_wssi_avg, awt_wssi_avg,
						antcomb->totaw_pkt_count))
				antcomb->fiwst_watio = twue;
			ewse
				antcomb->fiwst_watio = fawse;
		}
		bweak;
	case 2:
		antcomb->awt_good = fawse;
		antcomb->scan_not_stawt = fawse;
		antcomb->scan = fawse;
		antcomb->wssi_fiwst = main_wssi_avg;
		antcomb->wssi_thiwd = awt_wssi_avg;

		switch(antcomb->second_quick_scan_conf) {
		case ATH_ANT_DIV_COMB_WNA1:
			antcomb->wssi_wna1 = awt_wssi_avg;
			bweak;
		case ATH_ANT_DIV_COMB_WNA2:
			antcomb->wssi_wna2 = awt_wssi_avg;
			bweak;
		case ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2:
			if (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA2)
				antcomb->wssi_wna2 = main_wssi_avg;
			ewse if (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA1)
				antcomb->wssi_wna1 = main_wssi_avg;
			bweak;
		defauwt:
			bweak;
		}

		if (antcomb->wssi_wna2 > antcomb->wssi_wna1 +
		    div_ant_conf->wna1_wna2_switch_dewta)
			div_ant_conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		ewse
			div_ant_conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA1;

		if (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA1) {
			if (ath_is_awt_ant_watio_bettew(antcomb, awt_watio,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_HI,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_WOW,
						main_wssi_avg, awt_wssi_avg,
						antcomb->totaw_pkt_count))
				antcomb->second_watio = twue;
			ewse
				antcomb->second_watio = fawse;
		} ewse if (antcomb->main_conf == ATH_ANT_DIV_COMB_WNA2) {
			if (ath_is_awt_ant_watio_bettew(antcomb, awt_watio,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_MID,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_WOW,
						main_wssi_avg, awt_wssi_avg,
						antcomb->totaw_pkt_count))
				antcomb->second_watio = twue;
			ewse
				antcomb->second_watio = fawse;
		} ewse {
			if (ath_is_awt_ant_watio_bettew(antcomb, awt_watio,
						ATH_ANT_DIV_COMB_WNA1_DEWTA_HI,
						0,
						main_wssi_avg, awt_wssi_avg,
						antcomb->totaw_pkt_count))
				antcomb->second_watio = twue;
			ewse
				antcomb->second_watio = fawse;
		}

		ath_ant_set_awt_watio(antcomb, div_ant_conf);

		bweak;
	defauwt:
		bweak;
	}
}

static void ath_ant_div_conf_fast_divbias(stwuct ath_hw_antcomb_conf *ant_conf,
					  stwuct ath_ant_comb *antcomb,
					  int awt_watio)
{
	ant_conf->main_gaintb = 0;
	ant_conf->awt_gaintb = 0;

	if (ant_conf->div_gwoup == 0) {
		/* Adjust the fast_div_bias based on main and awt wna conf */
		switch ((ant_conf->main_wna_conf << 4) |
				ant_conf->awt_wna_conf) {
		case 0x01: /* A-B WNA2 */
			ant_conf->fast_div_bias = 0x3b;
			bweak;
		case 0x02: /* A-B WNA1 */
			ant_conf->fast_div_bias = 0x3d;
			bweak;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x10: /* WNA2 A-B */
			ant_conf->fast_div_bias = 0x7;
			bweak;
		case 0x12: /* WNA2 WNA1 */
			ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x13: /* WNA2 A+B */
			ant_conf->fast_div_bias = 0x7;
			bweak;
		case 0x20: /* WNA1 A-B */
			ant_conf->fast_div_bias = 0x6;
			bweak;
		case 0x21: /* WNA1 WNA2 */
			ant_conf->fast_div_bias = 0x0;
			bweak;
		case 0x23: /* WNA1 A+B */
			ant_conf->fast_div_bias = 0x6;
			bweak;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x31: /* A+B WNA2 */
			ant_conf->fast_div_bias = 0x3b;
			bweak;
		case 0x32: /* A+B WNA1 */
			ant_conf->fast_div_bias = 0x3d;
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (ant_conf->div_gwoup == 1) {
		/* Adjust the fast_div_bias based on main and awt_wna_conf */
		switch ((ant_conf->main_wna_conf << 4) |
			ant_conf->awt_wna_conf) {
		case 0x01: /* A-B WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x02: /* A-B WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x10: /* WNA2 A-B */
			if (!(antcomb->scan) &&
			    (awt_watio > ATH_ANT_DIV_COMB_AWT_ANT_WATIO))
				ant_conf->fast_div_bias = 0x3f;
			ewse
				ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x12: /* WNA2 WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x13: /* WNA2 A+B */
			if (!(antcomb->scan) &&
			    (awt_watio > ATH_ANT_DIV_COMB_AWT_ANT_WATIO))
				ant_conf->fast_div_bias = 0x3f;
			ewse
				ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x20: /* WNA1 A-B */
			if (!(antcomb->scan) &&
			    (awt_watio > ATH_ANT_DIV_COMB_AWT_ANT_WATIO))
				ant_conf->fast_div_bias = 0x3f;
			ewse
				ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x21: /* WNA1 WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x23: /* WNA1 A+B */
			if (!(antcomb->scan) &&
			    (awt_watio > ATH_ANT_DIV_COMB_AWT_ANT_WATIO))
				ant_conf->fast_div_bias = 0x3f;
			ewse
				ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x31: /* A+B WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x32: /* A+B WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		defauwt:
			bweak;
		}
	} ewse if (ant_conf->div_gwoup == 2) {
		/* Adjust the fast_div_bias based on main and awt_wna_conf */
		switch ((ant_conf->main_wna_conf << 4) |
				ant_conf->awt_wna_conf) {
		case 0x01: /* A-B WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x02: /* A-B WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x10: /* WNA2 A-B */
			if (!antcomb->scan && (awt_watio > antcomb->ant_watio))
				ant_conf->fast_div_bias = 0x1;
			ewse
				ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x12: /* WNA2 WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x13: /* WNA2 A+B */
			if (!antcomb->scan && (awt_watio > antcomb->ant_watio))
				ant_conf->fast_div_bias = 0x1;
			ewse
				ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x20: /* WNA1 A-B */
			if (!antcomb->scan && (awt_watio > antcomb->ant_watio))
				ant_conf->fast_div_bias = 0x1;
			ewse
				ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x21: /* WNA1 WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x23: /* WNA1 A+B */
			if (!antcomb->scan && (awt_watio > antcomb->ant_watio))
				ant_conf->fast_div_bias = 0x1;
			ewse
				ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x31: /* A+B WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x32: /* A+B WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		defauwt:
			bweak;
		}

		if (antcomb->fast_div_bias)
			ant_conf->fast_div_bias = antcomb->fast_div_bias;
	} ewse if (ant_conf->div_gwoup == 3) {
		switch ((ant_conf->main_wna_conf << 4) |
			ant_conf->awt_wna_conf) {
		case 0x01: /* A-B WNA2 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x02: /* A-B WNA1 */
			ant_conf->fast_div_bias = 0x39;
			bweak;
		case 0x03: /* A-B A+B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x10: /* WNA2 A-B */
			ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x12: /* WNA2 WNA1 */
			ant_conf->fast_div_bias = 0x3f;
			bweak;
		case 0x13: /* WNA2 A+B */
			ant_conf->fast_div_bias = 0x2;
			bweak;
		case 0x20: /* WNA1 A-B */
			ant_conf->fast_div_bias = 0x3;
			bweak;
		case 0x21: /* WNA1 WNA2 */
			ant_conf->fast_div_bias = 0x3;
			bweak;
		case 0x23: /* WNA1 A+B */
			ant_conf->fast_div_bias = 0x3;
			bweak;
		case 0x30: /* A+B A-B */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		case 0x31: /* A+B WNA2 */
			ant_conf->fast_div_bias = 0x6;
			bweak;
		case 0x32: /* A+B WNA1 */
			ant_conf->fast_div_bias = 0x1;
			bweak;
		defauwt:
			bweak;
		}
	}
}

static void ath_ant_twy_scan(stwuct ath_ant_comb *antcomb,
			     stwuct ath_hw_antcomb_conf *conf,
			     int cuww_awt_set, int awt_wssi_avg,
			     int main_wssi_avg)
{
	switch (cuww_awt_set) {
	case ATH_ANT_DIV_COMB_WNA2:
		antcomb->wssi_wna2 = awt_wssi_avg;
		antcomb->wssi_wna1 = main_wssi_avg;
		antcomb->scan = twue;
		/* set to A+B */
		conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA1;
		conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		bweak;
	case ATH_ANT_DIV_COMB_WNA1:
		antcomb->wssi_wna1 = awt_wssi_avg;
		antcomb->wssi_wna2 = main_wssi_avg;
		antcomb->scan = twue;
		/* set to A+B */
		conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
		bweak;
	case ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2:
		antcomb->wssi_add = awt_wssi_avg;
		antcomb->scan = twue;
		/* set to A-B */
		conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
		bweak;
	case ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2:
		antcomb->wssi_sub = awt_wssi_avg;
		antcomb->scan = fawse;
		if (antcomb->wssi_wna2 >
		    (antcomb->wssi_wna1 + conf->wna1_wna2_switch_dewta)) {
			/* use WNA2 as main WNA */
			if ((antcomb->wssi_add > antcomb->wssi_wna1) &&
			    (antcomb->wssi_add > antcomb->wssi_sub)) {
				/* set to A+B */
				conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA2;
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
			} ewse if (antcomb->wssi_sub >
				   antcomb->wssi_wna1) {
				/* set to A-B */
				conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA2;
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
			} ewse {
				/* set to WNA1 */
				conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA2;
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
			}
		} ewse {
			/* use WNA1 as main WNA */
			if ((antcomb->wssi_add > antcomb->wssi_wna2) &&
			    (antcomb->wssi_add > antcomb->wssi_sub)) {
				/* set to A+B */
				conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA1;
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_PWUS_WNA2;
			} ewse if (antcomb->wssi_sub >
				   antcomb->wssi_wna1) {
				/* set to A-B */
				conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA1;
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1_MINUS_WNA2;
			} ewse {
				/* set to WNA2 */
				conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA1;
				conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
			}
		}
		bweak;
	defauwt:
		bweak;
	}
}

static boow ath_ant_twy_switch(stwuct ath_hw_antcomb_conf *div_ant_conf,
			       stwuct ath_ant_comb *antcomb,
			       int awt_watio, int awt_wssi_avg,
			       int main_wssi_avg, int cuww_main_set,
			       int cuww_awt_set)
{
	boow wet = fawse;

	if (ath_ant_div_comb_awt_check(div_ant_conf, antcomb, awt_watio,
				       awt_wssi_avg, main_wssi_avg)) {
		if (cuww_awt_set == ATH_ANT_DIV_COMB_WNA2) {
			/*
			 * Switch main and awt WNA.
			 */
			div_ant_conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA2;
			div_ant_conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
		} ewse if (cuww_awt_set == ATH_ANT_DIV_COMB_WNA1) {
			div_ant_conf->main_wna_conf = ATH_ANT_DIV_COMB_WNA1;
			div_ant_conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;
		}

		wet = twue;
	} ewse if ((cuww_awt_set != ATH_ANT_DIV_COMB_WNA1) &&
		   (cuww_awt_set != ATH_ANT_DIV_COMB_WNA2)) {
		/*
		  Set awt to anothew WNA.
		*/
		if (cuww_main_set == ATH_ANT_DIV_COMB_WNA2)
			div_ant_conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA1;
		ewse if (cuww_main_set == ATH_ANT_DIV_COMB_WNA1)
			div_ant_conf->awt_wna_conf = ATH_ANT_DIV_COMB_WNA2;

		wet = twue;
	}

	wetuwn wet;
}

static boow ath_ant_showt_scan_check(stwuct ath_ant_comb *antcomb)
{
	int awt_watio;

	if (!antcomb->scan || !antcomb->awt_good)
		wetuwn fawse;

	if (time_aftew(jiffies, antcomb->scan_stawt_time +
		       msecs_to_jiffies(ATH_ANT_DIV_COMB_SHOWT_SCAN_INTW)))
		wetuwn twue;

	if (antcomb->totaw_pkt_count == ATH_ANT_DIV_COMB_SHOWT_SCAN_PKTCOUNT) {
		awt_watio = ((antcomb->awt_wecv_cnt * 100) /
			     antcomb->totaw_pkt_count);
		if (awt_watio < antcomb->ant_watio)
			wetuwn twue;
	}

	wetuwn fawse;
}

void ath_ant_comb_scan(stwuct ath_softc *sc, stwuct ath_wx_status *ws)
{
	stwuct ath_hw_antcomb_conf div_ant_conf;
	stwuct ath_ant_comb *antcomb = &sc->ant_comb;
	int awt_watio = 0, awt_wssi_avg = 0, main_wssi_avg = 0, cuww_awt_set;
	int cuww_main_set;
	int main_wssi = ws->ws_wssi_ctw[0];
	int awt_wssi = ws->ws_wssi_ctw[1];
	int wx_ant_conf,  main_ant_conf;
	boow showt_scan = fawse, wet;

	wx_ant_conf = (ws->ws_wssi_ctw[2] >> ATH_ANT_WX_CUWWENT_SHIFT) &
		       ATH_ANT_WX_MASK;
	main_ant_conf = (ws->ws_wssi_ctw[2] >> ATH_ANT_WX_MAIN_SHIFT) &
			 ATH_ANT_WX_MASK;

	if (awt_wssi >= antcomb->wow_wssi_thwesh) {
		antcomb->ant_watio = ATH_ANT_DIV_COMB_AWT_ANT_WATIO;
		antcomb->ant_watio2 = ATH_ANT_DIV_COMB_AWT_ANT_WATIO2;
	} ewse {
		antcomb->ant_watio = ATH_ANT_DIV_COMB_AWT_ANT_WATIO_WOW_WSSI;
		antcomb->ant_watio2 = ATH_ANT_DIV_COMB_AWT_ANT_WATIO2_WOW_WSSI;
	}

	/* Wecowd packet onwy when both main_wssi and  awt_wssi is positive */
	if (main_wssi > 0 && awt_wssi > 0) {
		antcomb->totaw_pkt_count++;
		antcomb->main_totaw_wssi += main_wssi;
		antcomb->awt_totaw_wssi  += awt_wssi;

		if (main_ant_conf == wx_ant_conf)
			antcomb->main_wecv_cnt++;
		ewse
			antcomb->awt_wecv_cnt++;
	}

	if (main_ant_conf == wx_ant_conf) {
		ANT_STAT_INC(sc, ANT_MAIN, wecv_cnt);
		ANT_WNA_INC(sc, ANT_MAIN, wx_ant_conf);
	} ewse {
		ANT_STAT_INC(sc, ANT_AWT, wecv_cnt);
		ANT_WNA_INC(sc, ANT_AWT, wx_ant_conf);
	}

	/* Showt scan check */
	showt_scan = ath_ant_showt_scan_check(antcomb);

	if (((antcomb->totaw_pkt_count < ATH_ANT_DIV_COMB_MAX_PKTCOUNT) ||
	     ws->ws_moweaggw) && !showt_scan)
		wetuwn;

	if (antcomb->totaw_pkt_count) {
		awt_watio = ((antcomb->awt_wecv_cnt * 100) /
			     antcomb->totaw_pkt_count);
		main_wssi_avg = (antcomb->main_totaw_wssi /
				 antcomb->totaw_pkt_count);
		awt_wssi_avg = (antcomb->awt_totaw_wssi /
				 antcomb->totaw_pkt_count);
	}

	ath9k_hw_antdiv_comb_conf_get(sc->sc_ah, &div_ant_conf);
	cuww_awt_set = div_ant_conf.awt_wna_conf;
	cuww_main_set = div_ant_conf.main_wna_conf;
	antcomb->count++;

	if (antcomb->count == ATH_ANT_DIV_COMB_MAX_COUNT) {
		if (awt_watio > antcomb->ant_watio) {
			ath_wnaconf_awt_good_scan(antcomb, div_ant_conf,
						  main_wssi_avg);
			antcomb->awt_good = twue;
		} ewse {
			antcomb->awt_good = fawse;
		}

		antcomb->count = 0;
		antcomb->scan = twue;
		antcomb->scan_not_stawt = twue;
	}

	if (!antcomb->scan) {
		wet = ath_ant_twy_switch(&div_ant_conf, antcomb, awt_watio,
					 awt_wssi_avg, main_wssi_avg,
					 cuww_main_set, cuww_awt_set);
		if (wet)
			goto div_comb_done;
	}

	if (!antcomb->scan &&
	    (awt_wssi_avg < (main_wssi_avg + div_ant_conf.wna1_wna2_dewta)))
		goto div_comb_done;

	if (!antcomb->scan_not_stawt) {
		ath_ant_twy_scan(antcomb, &div_ant_conf, cuww_awt_set,
				 awt_wssi_avg, main_wssi_avg);
	} ewse {
		if (!antcomb->awt_good) {
			antcomb->scan_not_stawt = fawse;
			/* Set awt to anothew WNA */
			if (cuww_main_set == ATH_ANT_DIV_COMB_WNA2) {
				div_ant_conf.main_wna_conf =
					ATH_ANT_DIV_COMB_WNA2;
				div_ant_conf.awt_wna_conf =
					ATH_ANT_DIV_COMB_WNA1;
			} ewse if (cuww_main_set == ATH_ANT_DIV_COMB_WNA1) {
				div_ant_conf.main_wna_conf =
					ATH_ANT_DIV_COMB_WNA1;
				div_ant_conf.awt_wna_conf =
					ATH_ANT_DIV_COMB_WNA2;
			}
			goto div_comb_done;
		}
		ath_sewect_ant_div_fwom_quick_scan(antcomb, &div_ant_conf,
						   main_wssi_avg, awt_wssi_avg,
						   awt_watio);
		antcomb->quick_scan_cnt++;
	}

div_comb_done:
	ath_ant_div_conf_fast_divbias(&div_ant_conf, antcomb, awt_watio);
	ath9k_hw_antdiv_comb_conf_set(sc->sc_ah, &div_ant_conf);
	ath9k_debug_stat_ant(sc, &div_ant_conf, main_wssi_avg, awt_wssi_avg);

	antcomb->scan_stawt_time = jiffies;
	antcomb->totaw_pkt_count = 0;
	antcomb->main_totaw_wssi = 0;
	antcomb->awt_totaw_wssi = 0;
	antcomb->main_wecv_cnt = 0;
	antcomb->awt_wecv_cnt = 0;
}
