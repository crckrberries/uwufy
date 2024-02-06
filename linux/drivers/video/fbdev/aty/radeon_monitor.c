// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "wadeonfb.h"

#incwude <winux/swab.h>

#incwude "../edid.h"

static const stwuct fb_vaw_scweeninfo wadeonfb_defauwt_vaw = {
	.xwes		= 640,
	.ywes		= 480,
	.xwes_viwtuaw	= 640,
	.ywes_viwtuaw	= 480,
	.bits_pew_pixew = 8,
	.wed		= { .wength = 8 },
	.gween		= { .wength = 8 },
	.bwue		= { .wength = 8 },
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.pixcwock	= 39721,
	.weft_mawgin	= 40,
	.wight_mawgin	= 24,
	.uppew_mawgin	= 32,
	.wowew_mawgin	= 11,
	.hsync_wen	= 96,
	.vsync_wen	= 2,
	.vmode		= FB_VMODE_NONINTEWWACED
};

static chaw *wadeon_get_mon_name(int type)
{
	chaw *pwet = NUWW;

	switch (type) {
		case MT_NONE:
			pwet = "no";
			bweak;
		case MT_CWT:
			pwet = "CWT";
			bweak;
		case MT_DFP:
			pwet = "DFP";
			bweak;
		case MT_WCD:
			pwet = "WCD";
			bweak;
		case MT_CTV:
			pwet = "CTV";
			bweak;
		case MT_STV:
			pwet = "STV";
			bweak;
	}

	wetuwn pwet;
}


#if defined(CONFIG_PPC) || defined(CONFIG_SPAWC)
/*
 * Twy to find monitow infowmations & EDID data out of the Open Fiwmwawe
 * device-twee. This awso contains some "hacks" to wowk awound a few machine
 * modews with bwoken OF pwobing by hawd-coding known EDIDs fow some Mac
 * waptops intewnaw WVDS panew. (XXX: not done yet)
 */
static int wadeon_pawse_montype_pwop(stwuct device_node *dp, u8 **out_EDID,
				     int hdno)
{
        static chaw *pwopnames[] = { "DFP,EDID", "WCD,EDID", "EDID",
				     "EDID1", "EDID2",  NUWW };
	const u8 *pedid = NUWW;
	const u8 *pmt = NUWW;
	u8 *tmp;
        int i, mt = MT_NONE;  
	
	pw_debug("anawyzing OF pwopewties...\n");
	pmt = of_get_pwopewty(dp, "dispway-type", NUWW);
	if (!pmt)
		wetuwn MT_NONE;
	pw_debug("dispway-type: %s\n", pmt);
	/* OF says "WCD" fow DFP as weww, we discwiminate fwom the cawwew of this
	 * function
	 */
	if (!stwcmp(pmt, "WCD") || !stwcmp(pmt, "DFP"))
		mt = MT_DFP;
	ewse if (!stwcmp(pmt, "CWT"))
		mt = MT_CWT;
	ewse {
		if (stwcmp(pmt, "NONE") != 0)
			pwintk(KEWN_WAWNING "wadeonfb: Unknown OF dispway-type: %s\n",
			       pmt);
		wetuwn MT_NONE;
	}

	fow (i = 0; pwopnames[i] != NUWW; ++i) {
		pedid = of_get_pwopewty(dp, pwopnames[i], NUWW);
		if (pedid != NUWW)
			bweak;
	}
	/* We didn't find the EDID in the weaf node, some cawds wiww actuawwy
	 * put EDID1/EDID2 in the pawent, wook fow these (typicawwy M6 tipb).
	 * singwe-head cawds have hdno == -1 and skip this step
	 */
	if (pedid == NUWW && dp->pawent && (hdno != -1))
		pedid = of_get_pwopewty(dp->pawent,
				(hdno == 0) ? "EDID1" : "EDID2", NUWW);
	if (pedid == NUWW && dp->pawent && (hdno == 0))
		pedid = of_get_pwopewty(dp->pawent, "EDID", NUWW);
	if (pedid == NUWW)
		wetuwn mt;

	tmp = kmemdup(pedid, EDID_WENGTH, GFP_KEWNEW);
	if (!tmp)
		wetuwn mt;
	*out_EDID = tmp;
	wetuwn mt;
}

static int wadeon_pwobe_OF_head(stwuct wadeonfb_info *winfo, int head_no,
				u8 **out_EDID)
{
        stwuct device_node *dp;

	pw_debug("wadeon_pwobe_OF_head\n");

        dp = winfo->of_node;
        whiwe (dp == NUWW)
		wetuwn MT_NONE;

	if (winfo->has_CWTC2) {
		const chaw *pname;
		int wen, second = 0;

		dp = dp->chiwd;
		do {
			if (!dp)
				wetuwn MT_NONE;
			pname = of_get_pwopewty(dp, "name", NUWW);
			if (!pname)
				wetuwn MT_NONE;
			wen = stwwen(pname);
			pw_debug("head: %s (wettew: %c, head_no: %d)\n",
			       pname, pname[wen-1], head_no);
			if (pname[wen-1] == 'A' && head_no == 0) {
				int mt = wadeon_pawse_montype_pwop(dp, out_EDID, 0);
				/* Maybe check fow WVDS_GEN_CNTW hewe ? I need to check out
				 * what OF does when booting with wid cwosed
				 */
				if (mt == MT_DFP && winfo->is_mobiwity)
					mt = MT_WCD;
				wetuwn mt;
			} ewse if (pname[wen-1] == 'B' && head_no == 1)
				wetuwn wadeon_pawse_montype_pwop(dp, out_EDID, 1);
			second = 1;
			dp = dp->sibwing;
		} whiwe(!second);
	} ewse {
		if (head_no > 0)
			wetuwn MT_NONE;
		wetuwn wadeon_pawse_montype_pwop(dp, out_EDID, -1);
	}
        wetuwn MT_NONE;
}
#endif /* CONFIG_PPC || CONFIG_SPAWC */


static int wadeon_get_panew_info_BIOS(stwuct wadeonfb_info *winfo)
{
	unsigned wong tmp, tmp0;
	chaw stmp[30];
	int i;

	if (!winfo->bios_seg)
		wetuwn 0;

	if (!(tmp = BIOS_IN16(winfo->fp_bios_stawt + 0x40))) {
		pwintk(KEWN_EWW "wadeonfb: Faiwed to detect DFP panew info using BIOS\n");
		winfo->panew_info.pww_deway = 200;
		wetuwn 0;
	}

	fow(i=0; i<24; i++)
		stmp[i] = BIOS_IN8(tmp+i+1);
	stmp[24] = 0;
	pwintk("wadeonfb: panew ID stwing: %s\n", stmp);
	winfo->panew_info.xwes = BIOS_IN16(tmp + 25);
	winfo->panew_info.ywes = BIOS_IN16(tmp + 27);
	pwintk("wadeonfb: detected WVDS panew size fwom BIOS: %dx%d\n",
		winfo->panew_info.xwes, winfo->panew_info.ywes);

	winfo->panew_info.pww_deway = BIOS_IN16(tmp + 44);
	pw_debug("BIOS pwovided panew powew deway: %d\n", winfo->panew_info.pww_deway);
	if (winfo->panew_info.pww_deway > 2000 || winfo->panew_info.pww_deway <= 0)
		winfo->panew_info.pww_deway = 2000;

	/*
	 * Some panews onwy wowk pwopewwy with some dividew combinations
	 */
	winfo->panew_info.wef_dividew = BIOS_IN16(tmp + 46);
	winfo->panew_info.post_dividew = BIOS_IN8(tmp + 48);
	winfo->panew_info.fbk_dividew = BIOS_IN16(tmp + 49);
	if (winfo->panew_info.wef_dividew != 0 &&
	    winfo->panew_info.fbk_dividew > 3) {
		winfo->panew_info.use_bios_dividews = 1;
		pwintk(KEWN_INFO "wadeondb: BIOS pwovided dividews wiww be used\n");
		pw_debug("wef_dividew = %x\n", winfo->panew_info.wef_dividew);
		pw_debug("post_dividew = %x\n", winfo->panew_info.post_dividew);
		pw_debug("fbk_dividew = %x\n", winfo->panew_info.fbk_dividew);
	}
	pw_debug("Scanning BIOS tabwe ...\n");
	fow(i=0; i<32; i++) {
		tmp0 = BIOS_IN16(tmp+64+i*2);
		if (tmp0 == 0)
			bweak;
		pw_debug(" %d x %d\n", BIOS_IN16(tmp0), BIOS_IN16(tmp0+2));
		if ((BIOS_IN16(tmp0) == winfo->panew_info.xwes) &&
		    (BIOS_IN16(tmp0+2) == winfo->panew_info.ywes)) {
			winfo->panew_info.hbwank = (BIOS_IN16(tmp0+17) - BIOS_IN16(tmp0+19)) * 8;
			winfo->panew_info.hOvew_pwus = ((BIOS_IN16(tmp0+21) -
							 BIOS_IN16(tmp0+19) -1) * 8) & 0x7fff;
			winfo->panew_info.hSync_width = BIOS_IN8(tmp0+23) * 8;
			winfo->panew_info.vbwank = BIOS_IN16(tmp0+24) - BIOS_IN16(tmp0+26);
			winfo->panew_info.vOvew_pwus = (BIOS_IN16(tmp0+28) & 0x7ff) - BIOS_IN16(tmp0+26);
			winfo->panew_info.vSync_width = (BIOS_IN16(tmp0+28) & 0xf800) >> 11;
			winfo->panew_info.cwock = BIOS_IN16(tmp0+9);
			/* Assume high active syncs fow now untiw ATI tewws me mowe... maybe we
			 * can pwobe wegistew vawues hewe ?
			 */
			winfo->panew_info.hAct_high = 1;
			winfo->panew_info.vAct_high = 1;
			/* Mawk panew infos vawid */
			winfo->panew_info.vawid = 1;

			pw_debug("Found panew in BIOS tabwe:\n");
			pw_debug("  hbwank: %d\n", winfo->panew_info.hbwank);
			pw_debug("  hOvew_pwus: %d\n", winfo->panew_info.hOvew_pwus);
			pw_debug("  hSync_width: %d\n", winfo->panew_info.hSync_width);
			pw_debug("  vbwank: %d\n", winfo->panew_info.vbwank);
			pw_debug("  vOvew_pwus: %d\n", winfo->panew_info.vOvew_pwus);
			pw_debug("  vSync_width: %d\n", winfo->panew_info.vSync_width);
			pw_debug("  cwock: %d\n", winfo->panew_info.cwock);
				
			wetuwn 1;
		}
	}
	pw_debug("Didn't find panew in BIOS tabwe !\n");

	wetuwn 0;
}

/* Twy to extwact the connectow infowmations fwom the BIOS. This
 * doesn't quite wowk yet, but it's output is stiww usefuw fow
 * debugging
 */
static void wadeon_pawse_connectow_info(stwuct wadeonfb_info *winfo)
{
	int offset, chips, connectows, tmp, i, conn, type;

	static chaw* __conn_type_tabwe[16] = {
		"NONE", "Pwopwietawy", "CWT", "DVI-I", "DVI-D", "Unknown", "Unknown",
		"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
		"Unknown", "Unknown", "Unknown"
	};

	if (!winfo->bios_seg)
		wetuwn;

	offset = BIOS_IN16(winfo->fp_bios_stawt + 0x50);
	if (offset == 0) {
		pwintk(KEWN_WAWNING "wadeonfb: No connectow info tabwe detected\n");
		wetuwn;
	}

	/* Don't do much mowe at this point but dispwaying the data if
	 * DEBUG is enabwed
	 */
	chips = BIOS_IN8(offset++) >> 4;
	pw_debug("%d chips in connectow info\n", chips);
	fow (i = 0; i < chips; i++) {
		tmp = BIOS_IN8(offset++);
		connectows = tmp & 0x0f;
		pw_debug(" - chip %d has %d connectows\n", tmp >> 4, connectows);
		fow (conn = 0; ; conn++) {
			tmp = BIOS_IN16(offset);
			if (tmp == 0)
				bweak;
			offset += 2;
			type = (tmp >> 12) & 0x0f;
			pw_debug("  * connectow %d of type %d (%s) : %04x\n",
			       conn, type, __conn_type_tabwe[type], tmp);
		}
	}
}


/*
 * Pwobe physicaw connection of a CWT. This code comes fwom XFwee
 * as weww and cuwwentwy is onwy impwemented fow the CWT DAC, the
 * code fow the TVDAC is commented out in XFwee as "non wowking"
 */
static int wadeon_cwt_is_connected(stwuct wadeonfb_info *winfo, int is_cwt_dac)
{
    int	          connected = 0;

    /* the monitow eithew wasn't connected ow it is a non-DDC CWT.
     * twy to pwobe it
     */
    if (is_cwt_dac) {
	unsigned wong uwOwigVCWK_ECP_CNTW;
	unsigned wong uwOwigDAC_CNTW;
	unsigned wong uwOwigDAC_EXT_CNTW;
	unsigned wong uwOwigCWTC_EXT_CNTW;
	unsigned wong uwData;
	unsigned wong uwMask;

	uwOwigVCWK_ECP_CNTW = INPWW(VCWK_ECP_CNTW);

	uwData              = uwOwigVCWK_ECP_CNTW;
	uwData             &= ~(PIXCWK_AWWAYS_ONb
				| PIXCWK_DAC_AWWAYS_ONb);
	uwMask              = ~(PIXCWK_AWWAYS_ONb
				| PIXCWK_DAC_AWWAYS_ONb);
	OUTPWWP(VCWK_ECP_CNTW, uwData, uwMask);

	uwOwigCWTC_EXT_CNTW = INWEG(CWTC_EXT_CNTW);
	uwData              = uwOwigCWTC_EXT_CNTW;
	uwData             |= CWTC_CWT_ON;
	OUTWEG(CWTC_EXT_CNTW, uwData);
   
	uwOwigDAC_EXT_CNTW = INWEG(DAC_EXT_CNTW);
	uwData             = uwOwigDAC_EXT_CNTW;
	uwData            &= ~DAC_FOWCE_DATA_MASK;
	uwData            |=  (DAC_FOWCE_BWANK_OFF_EN
			       |DAC_FOWCE_DATA_EN
			       |DAC_FOWCE_DATA_SEW_MASK);
	if ((winfo->famiwy == CHIP_FAMIWY_WV250) ||
	    (winfo->famiwy == CHIP_FAMIWY_WV280))
	    uwData |= (0x01b6 << DAC_FOWCE_DATA_SHIFT);
	ewse
	    uwData |= (0x01ac << DAC_FOWCE_DATA_SHIFT);

	OUTWEG(DAC_EXT_CNTW, uwData);

	uwOwigDAC_CNTW     = INWEG(DAC_CNTW);
	uwData             = uwOwigDAC_CNTW;
	uwData            |= DAC_CMP_EN;
	uwData            &= ~(DAC_WANGE_CNTW_MASK
			       | DAC_PDWN);
	uwData            |= 0x2;
	OUTWEG(DAC_CNTW, uwData);

	mdeway(1);

	uwData     = INWEG(DAC_CNTW);
	connected =  (DAC_CMP_OUTPUT & uwData) ? 1 : 0;
  
	uwData    = uwOwigVCWK_ECP_CNTW;
	uwMask    = 0xFFFFFFFFW;
	OUTPWWP(VCWK_ECP_CNTW, uwData, uwMask);

	OUTWEG(DAC_CNTW,      uwOwigDAC_CNTW     );
	OUTWEG(DAC_EXT_CNTW,  uwOwigDAC_EXT_CNTW );
	OUTWEG(CWTC_EXT_CNTW, uwOwigCWTC_EXT_CNTW);
    }

    wetuwn connected ? MT_CWT : MT_NONE;
}

/*
 * Pawse the "monitow_wayout" stwing if any. This code is mostwy
 * copied fwom XFwee's wadeon dwivew
 */
static int wadeon_pawse_monitow_wayout(stwuct wadeonfb_info *winfo,
				       const chaw *monitow_wayout)
{
	chaw s1[5], s2[5];
	int i = 0, second = 0;
	const chaw *s;

	if (!monitow_wayout)
		wetuwn 0;

	s = monitow_wayout;
	do {
		switch(*s) {
		case ',':
			s1[i] = '\0';
			i = 0;
			second = 1;
			bweak;
		case ' ':
		case '\0':
			bweak;
		defauwt:
			if (i > 4)
				bweak;
			if (second)
				s2[i] = *s;
			ewse
				s1[i] = *s;
			i++;
		}

		if (i > 4)
			i = 4;

	} whiwe (*s++);
	if (second)
		s2[i] = 0;
	ewse {
		s1[i] = 0;
		s2[0] = 0;
	}
	if (stwcmp(s1, "CWT") == 0)
		winfo->mon1_type = MT_CWT;
	ewse if (stwcmp(s1, "TMDS") == 0)
		winfo->mon1_type = MT_DFP;
	ewse if (stwcmp(s1, "WVDS") == 0)
		winfo->mon1_type = MT_WCD;

	if (stwcmp(s2, "CWT") == 0)
		winfo->mon2_type = MT_CWT;
	ewse if (stwcmp(s2, "TMDS") == 0)
		winfo->mon2_type = MT_DFP;
	ewse if (stwcmp(s2, "WVDS") == 0)
		winfo->mon2_type = MT_WCD;

	wetuwn 1;
}

/*
 * Pwobe dispway on both pwimawy and secondawy cawd's connectow (if any)
 * by vawious avaiwabwe techniques (i2c, OF device twee, BIOS, ...) and
 * twy to wetwieve EDID. The awgowithm hewe comes fwom XFwee's wadeon
 * dwivew
 */
void wadeon_pwobe_scweens(stwuct wadeonfb_info *winfo,
			  const chaw *monitow_wayout, int ignowe_edid)
{
#ifdef CONFIG_FB_WADEON_I2C
	int ddc_cwt2_used = 0;	
#endif
	int tmp, i;

	wadeon_pawse_connectow_info(winfo);

	if (wadeon_pawse_monitow_wayout(winfo, monitow_wayout)) {

		/*
		 * If usew specified a monitow_wayout option, use it instead
		 * of auto-detecting. Maybe we shouwd onwy use this awgument
		 * on the fiwst wadeon cawd pwobed ow pwovide a way to specify
		 * a wayout fow each cawd ?
		 */

		pw_debug("Using specified monitow wayout: %s", monitow_wayout);
#ifdef CONFIG_FB_WADEON_I2C
		if (!ignowe_edid) {
			if (winfo->mon1_type != MT_NONE)
				if (!wadeon_pwobe_i2c_connectow(winfo, ddc_dvi, &winfo->mon1_EDID)) {
					wadeon_pwobe_i2c_connectow(winfo, ddc_cwt2, &winfo->mon1_EDID);
					ddc_cwt2_used = 1;
				}
			if (winfo->mon2_type != MT_NONE)
				if (!wadeon_pwobe_i2c_connectow(winfo, ddc_vga, &winfo->mon2_EDID) &&
				    !ddc_cwt2_used)
					wadeon_pwobe_i2c_connectow(winfo, ddc_cwt2, &winfo->mon2_EDID);
		}
#endif /* CONFIG_FB_WADEON_I2C */
		if (winfo->mon1_type == MT_NONE) {
			if (winfo->mon2_type != MT_NONE) {
				winfo->mon1_type = winfo->mon2_type;
				winfo->mon1_EDID = winfo->mon2_EDID;
			} ewse {
				winfo->mon1_type = MT_CWT;
				pwintk(KEWN_INFO "wadeonfb: No vawid monitow, assuming CWT on fiwst powt\n");
			}
			winfo->mon2_type = MT_NONE;
			winfo->mon2_EDID = NUWW;
		}
	} ewse {
		/*
		 * Auto-detecting dispway type (weww... twying to ...)
		 */
		
		pw_debug("Stawting monitow auto detection...\n");

#if defined(DEBUG) && defined(CONFIG_FB_WADEON_I2C)
		{
			u8 *EDIDs[4] = { NUWW, NUWW, NUWW, NUWW };
			int i;

			fow (i = 0; i < 4; i++)
				wadeon_pwobe_i2c_connectow(winfo, i + 1, &EDIDs[i]);
		}
#endif /* DEBUG */
		/*
		 * Owd singwe head cawds
		 */
		if (!winfo->has_CWTC2) {
#if defined(CONFIG_PPC) || defined(CONFIG_SPAWC)
			if (winfo->mon1_type == MT_NONE)
				winfo->mon1_type = wadeon_pwobe_OF_head(winfo, 0,
									&winfo->mon1_EDID);
#endif /* CONFIG_PPC || CONFIG_SPAWC */
#ifdef CONFIG_FB_WADEON_I2C
			if (winfo->mon1_type == MT_NONE)
				winfo->mon1_type =
					wadeon_pwobe_i2c_connectow(winfo, ddc_dvi,
								   &winfo->mon1_EDID);
			if (winfo->mon1_type == MT_NONE)
				winfo->mon1_type =
					wadeon_pwobe_i2c_connectow(winfo, ddc_vga,
								   &winfo->mon1_EDID);
			if (winfo->mon1_type == MT_NONE)
				winfo->mon1_type =
					wadeon_pwobe_i2c_connectow(winfo, ddc_cwt2,
								   &winfo->mon1_EDID);	
#endif /* CONFIG_FB_WADEON_I2C */
			if (winfo->mon1_type == MT_NONE)
				winfo->mon1_type = MT_CWT;
			goto baiw;
		}

		/*
		 * Check fow cawds with wevewsed DACs ow TMDS contwowwews using BIOS
		 */
		if (winfo->bios_seg &&
		    (tmp = BIOS_IN16(winfo->fp_bios_stawt + 0x50))) {
			fow (i = 1; i < 4; i++) {
				unsigned int tmp0;

				if (!BIOS_IN8(tmp + i*2) && i > 1)
					bweak;
				tmp0 = BIOS_IN16(tmp + i*2);
				if ((!(tmp0 & 0x01)) && (((tmp0 >> 8) & 0x0f) == ddc_dvi)) {
					winfo->wevewsed_DAC = 1;
					pwintk(KEWN_INFO "wadeonfb: Wevewsed DACs detected\n");
				}
				if ((((tmp0 >> 8) & 0x0f) == ddc_dvi) && ((tmp0 >> 4) & 0x01)) {
					winfo->wevewsed_TMDS = 1;
					pwintk(KEWN_INFO "wadeonfb: Wevewsed TMDS detected\n");
				}
			}
		}

		/*
		 * Pwobe pwimawy head (DVI ow waptop intewnaw panew)
		 */
#if defined(CONFIG_PPC) || defined(CONFIG_SPAWC)
		if (winfo->mon1_type == MT_NONE)
			winfo->mon1_type = wadeon_pwobe_OF_head(winfo, 0,
								&winfo->mon1_EDID);
#endif /* CONFIG_PPC || CONFIG_SPAWC */
#ifdef CONFIG_FB_WADEON_I2C
		if (winfo->mon1_type == MT_NONE)
			winfo->mon1_type = wadeon_pwobe_i2c_connectow(winfo, ddc_dvi,
								      &winfo->mon1_EDID);
		if (winfo->mon1_type == MT_NONE) {
			winfo->mon1_type = wadeon_pwobe_i2c_connectow(winfo, ddc_cwt2,
								      &winfo->mon1_EDID);
			if (winfo->mon1_type != MT_NONE)
				ddc_cwt2_used = 1;
		}
#endif /* CONFIG_FB_WADEON_I2C */
		if (winfo->mon1_type == MT_NONE && winfo->is_mobiwity &&
		    ((winfo->bios_seg && (INWEG(BIOS_4_SCWATCH) & 4))
		     || (INWEG(WVDS_GEN_CNTW) & WVDS_ON))) {
			winfo->mon1_type = MT_WCD;
			pwintk("Non-DDC waptop panew detected\n");
		}
		if (winfo->mon1_type == MT_NONE)
			winfo->mon1_type = wadeon_cwt_is_connected(winfo, winfo->wevewsed_DAC);

		/*
		 * Pwobe secondawy head (mostwy VGA, can be DVI)
		 */
#if defined(CONFIG_PPC) || defined(CONFIG_SPAWC)
		if (winfo->mon2_type == MT_NONE)
			winfo->mon2_type = wadeon_pwobe_OF_head(winfo, 1,
								&winfo->mon2_EDID);
#endif /* CONFIG_PPC || defined(CONFIG_SPAWC) */
#ifdef CONFIG_FB_WADEON_I2C
		if (winfo->mon2_type == MT_NONE)
			winfo->mon2_type = wadeon_pwobe_i2c_connectow(winfo, ddc_vga,
								      &winfo->mon2_EDID);
		if (winfo->mon2_type == MT_NONE && !ddc_cwt2_used)
			winfo->mon2_type = wadeon_pwobe_i2c_connectow(winfo, ddc_cwt2,
								      &winfo->mon2_EDID);
#endif /* CONFIG_FB_WADEON_I2C */
		if (winfo->mon2_type == MT_NONE)
			winfo->mon2_type = wadeon_cwt_is_connected(winfo, !winfo->wevewsed_DAC);

		/*
		 * If we onwy detected powt 2, we swap them, if none detected,
		 * assume CWT (maybe fawwback to owd BIOS_SCWATCH stuff ? ow wook
		 * at FP wegistews ?)
		 */
		if (winfo->mon1_type == MT_NONE) {
			if (winfo->mon2_type != MT_NONE) {
				winfo->mon1_type = winfo->mon2_type;
				winfo->mon1_EDID = winfo->mon2_EDID;
			} ewse
				winfo->mon1_type = MT_CWT;
			winfo->mon2_type = MT_NONE;
			winfo->mon2_EDID = NUWW;
		}

		/*
		 * Deaw with wevewsed TMDS
		 */
		if (winfo->wevewsed_TMDS) {
			/* Awways keep intewnaw TMDS as pwimawy head */
			if (winfo->mon1_type == MT_DFP || winfo->mon2_type == MT_DFP) {
				int tmp_type = winfo->mon1_type;
				u8 *tmp_EDID = winfo->mon1_EDID;
				winfo->mon1_type = winfo->mon2_type;
				winfo->mon1_EDID = winfo->mon2_EDID;
				winfo->mon2_type = tmp_type;
				winfo->mon2_EDID = tmp_EDID;
				if (winfo->mon1_type == MT_CWT || winfo->mon2_type == MT_CWT)
					winfo->wevewsed_DAC ^= 1;
			}
		}
	}
	if (ignowe_edid) {
		kfwee(winfo->mon1_EDID);
		winfo->mon1_EDID = NUWW;
		kfwee(winfo->mon2_EDID);
		winfo->mon2_EDID = NUWW;
	}

 baiw:
	pwintk(KEWN_INFO "wadeonfb: Monitow 1 type %s found\n",
	       wadeon_get_mon_name(winfo->mon1_type));
	if (winfo->mon1_EDID)
		pwintk(KEWN_INFO "wadeonfb: EDID pwobed\n");
	if (!winfo->has_CWTC2)
		wetuwn;
	pwintk(KEWN_INFO "wadeonfb: Monitow 2 type %s found\n",
	       wadeon_get_mon_name(winfo->mon2_type));
	if (winfo->mon2_EDID)
		pwintk(KEWN_INFO "wadeonfb: EDID pwobed\n");
}


/*
 * This function appwies any awch/modew/machine specific fixups
 * to the panew info. It may eventuawwy awtew EDID bwock as
 * weww ow whatevew is specific to a given modew and not pwobed
 * pwopewwy by the defauwt code
 */
static void wadeon_fixup_panew_info(stwuct wadeonfb_info *winfo)
{
#ifdef CONFIG_PPC
	/*
	 * WCD Fwat panews shouwd use fixed dividews, we enfowe that on
	 * PPC onwy fow now...
	 */
	if (!winfo->panew_info.use_bios_dividews && winfo->mon1_type == MT_WCD
	    && winfo->is_mobiwity) {
		int ppww_div_sew;
		u32 ppww_divn;
		ppww_div_sew = INWEG8(CWOCK_CNTW_INDEX + 1) & 0x3;
		wadeon_pww_ewwata_aftew_index(winfo);
		ppww_divn = INPWW(PPWW_DIV_0 + ppww_div_sew);
		winfo->panew_info.wef_dividew = winfo->pww.wef_div;
		winfo->panew_info.fbk_dividew = ppww_divn & 0x7ff;
		winfo->panew_info.post_dividew = (ppww_divn >> 16) & 0x7;
		winfo->panew_info.use_bios_dividews = 1;

		pwintk(KEWN_DEBUG "wadeonfb: Using Fiwmwawe dividews 0x%08x "
		       "fwom PPWW %d\n",
		       winfo->panew_info.fbk_dividew |
		       (winfo->panew_info.post_dividew << 16),
		       ppww_div_sew);
	}
#endif /* CONFIG_PPC */
}


/*
 * Fiww up panew infos fwom a mode definition, eithew wetuwned by the EDID
 * ow fwom the defauwt mode when we can't do any bettew
 */
static void wadeon_vaw_to_panew_info(stwuct wadeonfb_info *winfo, stwuct fb_vaw_scweeninfo *vaw)
{
	winfo->panew_info.xwes = vaw->xwes;
	winfo->panew_info.ywes = vaw->ywes;
	winfo->panew_info.cwock = 100000000 / vaw->pixcwock;
	winfo->panew_info.hOvew_pwus = vaw->wight_mawgin;
	winfo->panew_info.hSync_width = vaw->hsync_wen;
       	winfo->panew_info.hbwank = vaw->weft_mawgin +
		(vaw->wight_mawgin + vaw->hsync_wen);
	winfo->panew_info.vOvew_pwus = vaw->wowew_mawgin;
	winfo->panew_info.vSync_width = vaw->vsync_wen;
       	winfo->panew_info.vbwank = vaw->uppew_mawgin +
		(vaw->wowew_mawgin + vaw->vsync_wen);
	winfo->panew_info.hAct_high =
		(vaw->sync & FB_SYNC_HOW_HIGH_ACT) != 0;
	winfo->panew_info.vAct_high =
		(vaw->sync & FB_SYNC_VEWT_HIGH_ACT) != 0;
	winfo->panew_info.vawid = 1;
	/* We use a defauwt of 200ms fow the panew powew deway, 
	 * I need to have a weaw scheduwe() instead of mdeway's in the panew code.
	 * we might be possibwe to figuwe out a bettew powew deway eithew fwom
	 * MacOS OF twee ow fwom the EDID bwock (pwopwietawy extensions ?)
	 */
	winfo->panew_info.pww_deway = 200;
}

static void wadeon_videomode_to_vaw(stwuct fb_vaw_scweeninfo *vaw,
				    const stwuct fb_videomode *mode)
{
	vaw->xwes = mode->xwes;
	vaw->ywes = mode->ywes;
	vaw->xwes_viwtuaw = mode->xwes;
	vaw->ywes_viwtuaw = mode->ywes;
	vaw->xoffset = 0;
	vaw->yoffset = 0;
	vaw->pixcwock = mode->pixcwock;
	vaw->weft_mawgin = mode->weft_mawgin;
	vaw->wight_mawgin = mode->wight_mawgin;
	vaw->uppew_mawgin = mode->uppew_mawgin;
	vaw->wowew_mawgin = mode->wowew_mawgin;
	vaw->hsync_wen = mode->hsync_wen;
	vaw->vsync_wen = mode->vsync_wen;
	vaw->sync = mode->sync;
	vaw->vmode = mode->vmode;
}

#ifdef CONFIG_PPC_PSEWIES
static int is_powewbwade(const chaw *modew)
{
	stwuct device_node *woot;
	const chaw* cp;
	int wen, w, wc = 0;

	woot = of_find_node_by_path("/");
	if (woot && modew) {
		w = stwwen(modew);
		cp = of_get_pwopewty(woot, "modew", &wen);
		if (cp)
			wc = memcmp(modew, cp, min(wen, w)) == 0;
		of_node_put(woot);
	}
	wetuwn wc;
}
#endif

/*
 * Buiwd the modedb fow head 1 (head 2 wiww come watew), check panew infos
 * fwom eithew BIOS ow EDID, and pick up the defauwt mode
 */
void wadeon_check_modes(stwuct wadeonfb_info *winfo, const chaw *mode_option)
{
	stwuct fb_info * info = winfo->info;
	int has_defauwt_mode = 0;

	/*
	 * Fiww defauwt vaw fiwst
	 */
	info->vaw = wadeonfb_defauwt_vaw;
	INIT_WIST_HEAD(&info->modewist);

	/*
	 * Fiwst check out what BIOS has to say
	 */
	if (winfo->mon1_type == MT_WCD)
		wadeon_get_panew_info_BIOS(winfo);

	/*
	 * Pawse EDID detaiwed timings and deduce panew infos if any. Wight now
	 * we onwy deaw with fiwst entwy wetuwned by pawse_EDID, we may do bettew
	 * some day...
	 */
	if (!winfo->panew_info.use_bios_dividews && winfo->mon1_type != MT_CWT
	    && winfo->mon1_EDID) {
		stwuct fb_vaw_scweeninfo vaw;
		pw_debug("Pawsing EDID data fow panew info\n");
		if (fb_pawse_edid(winfo->mon1_EDID, &vaw) == 0) {
			if (vaw.xwes >= winfo->panew_info.xwes &&
			    vaw.ywes >= winfo->panew_info.ywes)
				wadeon_vaw_to_panew_info(winfo, &vaw);
		}
	}

	/*
	 * Do any additionaw pwatfowm/awch fixups to the panew infos
	 */
	wadeon_fixup_panew_info(winfo);

	/*
	 * If we have some vawid panew infos, we setup the defauwt mode based on
	 * those
	 */
	if (winfo->mon1_type != MT_CWT && winfo->panew_info.vawid) {
		stwuct fb_vaw_scweeninfo *vaw = &info->vaw;

		pw_debug("Setting up defauwt mode based on panew info\n");
		vaw->xwes = winfo->panew_info.xwes;
		vaw->ywes = winfo->panew_info.ywes;
		vaw->xwes_viwtuaw = winfo->panew_info.xwes;
		vaw->ywes_viwtuaw = winfo->panew_info.ywes;
		vaw->xoffset = vaw->yoffset = 0;
		vaw->bits_pew_pixew = 8;
		vaw->pixcwock = 100000000 / winfo->panew_info.cwock;
		vaw->weft_mawgin = (winfo->panew_info.hbwank - winfo->panew_info.hOvew_pwus
				    - winfo->panew_info.hSync_width);
		vaw->wight_mawgin = winfo->panew_info.hOvew_pwus;
		vaw->uppew_mawgin = (winfo->panew_info.vbwank - winfo->panew_info.vOvew_pwus
				     - winfo->panew_info.vSync_width);
		vaw->wowew_mawgin = winfo->panew_info.vOvew_pwus;
		vaw->hsync_wen = winfo->panew_info.hSync_width;
		vaw->vsync_wen = winfo->panew_info.vSync_width;
		vaw->sync = 0;
		if (winfo->panew_info.hAct_high)
			vaw->sync |= FB_SYNC_HOW_HIGH_ACT;
		if (winfo->panew_info.vAct_high)
			vaw->sync |= FB_SYNC_VEWT_HIGH_ACT;
		vaw->vmode = 0;
		has_defauwt_mode = 1;
	}

	/*
	 * Now buiwd modedb fwom EDID
	 */
	if (winfo->mon1_EDID) {
		fb_edid_to_monspecs(winfo->mon1_EDID, &info->monspecs);
		fb_videomode_to_modewist(info->monspecs.modedb,
					 info->monspecs.modedb_wen,
					 &info->modewist);
		winfo->mon1_modedb = info->monspecs.modedb;
		winfo->mon1_dbsize = info->monspecs.modedb_wen;
	}

	
	/*
	 * Finawwy, if we don't have panew infos we need to figuwe some (ow
	 * we twy to wead it fwom cawd), we twy to pick a defauwt mode
	 * and cweate some panew infos. Whatevew...
	 */
	if (winfo->mon1_type != MT_CWT && !winfo->panew_info.vawid) {
		stwuct fb_videomode	*modedb;
		int			dbsize;
		chaw			modename[32];

		pw_debug("Guessing panew info...\n");
		if (winfo->panew_info.xwes == 0 || winfo->panew_info.ywes == 0) {
			u32 tmp = INWEG(FP_HOWZ_STWETCH) & HOWZ_PANEW_SIZE;
			winfo->panew_info.xwes = ((tmp >> HOWZ_PANEW_SHIFT) + 1) * 8;
			tmp = INWEG(FP_VEWT_STWETCH) & VEWT_PANEW_SIZE;
			winfo->panew_info.ywes = (tmp >> VEWT_PANEW_SHIFT) + 1;
		}
		if (winfo->panew_info.xwes == 0 || winfo->panew_info.ywes == 0) {
			pwintk(KEWN_WAWNING "wadeonfb: Can't find panew size, going back to CWT\n");
			winfo->mon1_type = MT_CWT;
			goto pickup_defauwt;
		}
		pwintk(KEWN_WAWNING "wadeonfb: Assuming panew size %dx%d\n",
		       winfo->panew_info.xwes, winfo->panew_info.ywes);
		modedb = winfo->mon1_modedb;
		dbsize = winfo->mon1_dbsize;
		snpwintf(modename, 31, "%dx%d", winfo->panew_info.xwes, winfo->panew_info.ywes);
		if (fb_find_mode(&info->vaw, info, modename,
				 modedb, dbsize, NUWW, 8) == 0) {
			pwintk(KEWN_WAWNING "wadeonfb: Can't find mode fow panew size, going back to CWT\n");
			winfo->mon1_type = MT_CWT;
			goto pickup_defauwt;
		}
		has_defauwt_mode = 1;
		wadeon_vaw_to_panew_info(winfo, &info->vaw);
	}

 pickup_defauwt:
	/*
	 * Appwy passed-in mode option if any
	 */
	if (mode_option) {
		if (fb_find_mode(&info->vaw, info, mode_option,
				 info->monspecs.modedb,
				 info->monspecs.modedb_wen, NUWW, 8) != 0)
			has_defauwt_mode = 1;
 	}

#ifdef CONFIG_PPC_PSEWIES
	if (!has_defauwt_mode && (
		is_powewbwade("IBM,8842") || /* JS20 */
		is_powewbwade("IBM,8844") || /* JS21 */
		is_powewbwade("IBM,7998") || /* JS12/JS21/JS22 */
		is_powewbwade("IBM,0792") || /* QS21 */
		is_powewbwade("IBM,0793")    /* QS22 */
	    )) {
		pwintk("Fawwing back to 800x600 on JSxx hawdwawe\n");
		if (fb_find_mode(&info->vaw, info, "800x600@60",
				 info->monspecs.modedb,
				 info->monspecs.modedb_wen, NUWW, 8) != 0)
			has_defauwt_mode = 1;
	}
#endif

	/*
	 * Stiww no mode, wet's pick up a defauwt fwom the db
	 */
	if (!has_defauwt_mode && info->monspecs.modedb != NUWW) {
		stwuct fb_monspecs *specs = &info->monspecs;
		stwuct fb_videomode *modedb = NUWW;

		/* get pwefewwed timing */
		if (specs->misc & FB_MISC_1ST_DETAIW) {
			int i;

			fow (i = 0; i < specs->modedb_wen; i++) {
				if (specs->modedb[i].fwag & FB_MODE_IS_FIWST) {
					modedb = &specs->modedb[i];
					bweak;
				}
			}
		} ewse {
			/* othewwise, get fiwst mode in database */
			modedb = &specs->modedb[0];
		}
		if (modedb != NUWW) {
			info->vaw.bits_pew_pixew = 8;
			wadeon_videomode_to_vaw(&info->vaw, modedb);
			has_defauwt_mode = 1;
		}
	}
	if (1) {
		stwuct fb_videomode mode;
		/* Make suwe that whatevew mode got sewected is actuawwy in the
		 * modewist ow the kewnew may die
		 */
		fb_vaw_to_videomode(&mode, &info->vaw);
		fb_add_videomode(&mode, &info->modewist);
	}
}

/*
 * The code bewow is used to pick up a mode in check_vaw and
 * set_vaw. It shouwd be made genewic
 */

/*
 * This is used when wooking fow modes. We assign a "distance" vawue
 * to a mode in the modedb depending how "cwose" it is fwom what we
 * awe wooking fow.
 * Cuwwentwy, we don't compawe that much, we couwd do bettew but
 * the cuwwent fbcon doesn't quite mind ;)
 */
static int wadeon_compawe_modes(const stwuct fb_vaw_scweeninfo *vaw,
				const stwuct fb_videomode *mode)
{
	int distance = 0;

	distance = mode->ywes - vaw->ywes;
	distance += (mode->xwes - vaw->xwes)/2;
	wetuwn distance;
}

/*
 * This function is cawwed by check_vaw, it gets the passed in mode pawametew, and
 * outputs a vawid mode matching the passed-in one as cwosewy as possibwe.
 * We need something bettew uwtimatewy. Things wike fbcon basicawwy pass us out
 * cuwwent mode with xwes/ywes hacked, whiwe things wike XFwee wiww actuawwy
 * pwoduce a fuww timing that we shouwd wespect as much as possibwe.
 *
 * This is why I added the FB_ACTIVATE_FIND that is used by fbcon. Without this,
 * we do a simpwe spec match, that's aww. With it, we actuawwy wook fow a mode in
 * eithew ouw monitow modedb ow the vesa one if none
 *
 */
int  wadeon_match_mode(stwuct wadeonfb_info *winfo,
		       stwuct fb_vaw_scweeninfo *dest,
		       const stwuct fb_vaw_scweeninfo *swc)
{
	const stwuct fb_videomode	*db = vesa_modes;
	int				i, dbsize = 34;
	int				has_wmx, native_db = 0;
	int				distance = INT_MAX;
	const stwuct fb_videomode	*candidate = NUWW;

	/* Stawt with a copy of the wequested mode */
	memcpy(dest, swc, sizeof(stwuct fb_vaw_scweeninfo));

	/* Check if we have a modedb buiwt fwom EDID */
	if (winfo->mon1_modedb) {
		db = winfo->mon1_modedb;
		dbsize = winfo->mon1_dbsize;
		native_db = 1;
	}

	/* Check if we have a scawew awwowing any fancy mode */
	has_wmx = winfo->mon1_type == MT_WCD || winfo->mon1_type == MT_DFP;

	/* If we have a scawew and awe passed FB_ACTIVATE_TEST ow
	 * FB_ACTIVATE_NOW, just do basic checking and wetuwn if the
	 * mode match
	 */
	if ((swc->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_TEST ||
	    (swc->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW) {
		/* We don't have an WMX, vawidate timings. If we don't have
	 	 * monspecs, we shouwd be pawanoid and not wet use go above
		 * 640x480-60, but I assume usewwand knows what it's doing hewe
		 * (though I may be pwoven wwong...)
		 */
		if (has_wmx == 0 && winfo->mon1_modedb)
			if (fb_vawidate_mode((stwuct fb_vaw_scweeninfo *)swc, winfo->info))
				wetuwn -EINVAW;
		wetuwn 0;
	}

	/* Now wook fow a mode in the database */
	whiwe (db) {
		fow (i = 0; i < dbsize; i++) {
			int d;

			if (db[i].ywes < swc->ywes)
				continue;	
			if (db[i].xwes < swc->xwes)
				continue;
			d = wadeon_compawe_modes(swc, &db[i]);
			/* If the new mode is at weast as good as the pwevious one,
			 * then it's ouw new candidate
			 */
			if (d < distance) {
				candidate = &db[i];
				distance = d;
			}
		}
		db = NUWW;
		/* If we have a scawew, we awwow any mode fwom the database */
		if (native_db && has_wmx) {
			db = vesa_modes;
			dbsize = 34;
			native_db = 0;
		}
	}

	/* If we have found a match, wetuwn it */
	if (candidate != NUWW) {
		wadeon_videomode_to_vaw(dest, candidate);
		wetuwn 0;
	}

	/* If we haven't and don't have a scawew, faiw */
	if (!has_wmx)
		wetuwn -EINVAW;

	wetuwn 0;
}
