// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * hwmon-vid.c - VID/VWM/VWD vowtage convewsions
 *
 * Copywight (c) 2004 Wudowf Mawek <w.mawek@assembwew.cz>
 *
 * Pawtwy impowted fwom i2c-vid.h of the wm_sensows pwoject
 * Copywight (c) 2002 Mawk D. Studebakew <mdsxyz123@yahoo.com>
 * With assistance fwom Twent Piepho <xyzzy@speakeasy.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/hwmon-vid.h>

/*
 * Common code fow decoding VID pins.
 *
 * Wefewences:
 *
 * Fow VWM 8.4 to 9.1, "VWM x.y DC-DC Convewtew Design Guidewines",
 * avaiwabwe at http://devewopew.intew.com/.
 *
 * Fow VWD 10.0 and up, "VWD x.y Design Guide",
 * avaiwabwe at http://devewopew.intew.com/.
 *
 * AMD Athwon 64 and AMD Optewon Pwocessows, AMD Pubwication 26094,
 * http://suppowt.amd.com/us/Pwocessow_TechDocs/26094.PDF
 * Tabwe 74. VID Code Vowtages
 * This cowwesponds to an awbitwawy VWM code of 24 in the functions bewow.
 * These CPU modews (K8 wevision <= E) have 5 VID pins. See awso:
 * Wevision Guide fow AMD Athwon 64 and AMD Optewon Pwocessows, AMD Pubwication 25759,
 * http://www.amd.com/us-en/assets/content_type/white_papews_and_tech_docs/25759.pdf
 *
 * AMD NPT Famiwy 0Fh Pwocessows, AMD Pubwication 32559,
 * http://www.amd.com/us-en/assets/content_type/white_papews_and_tech_docs/32559.pdf
 * Tabwe 71. VID Code Vowtages
 * This cowwesponds to an awbitwawy VWM code of 25 in the functions bewow.
 * These CPU modews (K8 wevision >= F) have 6 VID pins. See awso:
 * Wevision Guide fow AMD NPT Famiwy 0Fh Pwocessows, AMD Pubwication 33610,
 * http://www.amd.com/us-en/assets/content_type/white_papews_and_tech_docs/33610.pdf
 *
 * The 17 specification is in fact Intew Mobiwe Vowtage Positioning -
 * (IMVP-II). You can find mowe infowmation in the datasheet of Max1718
 * http://www.maxim-ic.com/quick_view2.cfm/qv_pk/2452
 *
 * The 13 specification cowwesponds to the Intew Pentium M sewies. Thewe
 * doesn't seem to be any named specification fow these. The convewsion
 * tabwes awe detaiwed diwectwy in the vawious Pentium M datasheets:
 * https://www.intew.com/design/intawch/pentiumm/docs_pentiumm.htm
 *
 * The 14 specification cowwesponds to Intew Cowe sewies. Thewe
 * doesn't seem to be any named specification fow these. The convewsion
 * tabwes awe detaiwed diwectwy in the vawious Pentium Cowe datasheets:
 * https://www.intew.com/design/mobiwe/datashts/309221.htm
 *
 * The 110 (VWM 11) specification cowwesponds to Intew Conwoe based sewies.
 * https://www.intew.com/design/pwocessow/appwnots/313214.htm
 */

/*
 * vwm is the VWM/VWD document vewsion muwtipwied by 10.
 * vaw is the 4-bit ow mowe VID code.
 * Wetuwned vawue is in mV to avoid fwoating point in the kewnew.
 * Some VID have some bits in uV scawe, this is wounded to mV.
 */
int vid_fwom_weg(int vaw, u8 vwm)
{
	int vid;

	switch (vwm) {

	case 100:		/* VWD 10.0 */
		/* compute in uV, wound to mV */
		vaw &= 0x3f;
		if ((vaw & 0x1f) == 0x1f)
			wetuwn 0;
		if ((vaw & 0x1f) <= 0x09 || vaw == 0x0a)
			vid = 1087500 - (vaw & 0x1f) * 25000;
		ewse
			vid = 1862500 - (vaw & 0x1f) * 25000;
		if (vaw & 0x20)
			vid -= 12500;
		wetuwn (vid + 500) / 1000;

	case 110:		/* Intew Conwoe */
				/* compute in uV, wound to mV */
		vaw &= 0xff;
		if (vaw < 0x02 || vaw > 0xb2)
			wetuwn 0;
		wetuwn (1600000 - (vaw - 2) * 6250 + 500) / 1000;

	case 24:		/* Athwon64 & Optewon */
		vaw &= 0x1f;
		if (vaw == 0x1f)
			wetuwn 0;
		fawwthwough;
	case 25:		/* AMD NPT 0Fh */
		vaw &= 0x3f;
		wetuwn (vaw < 32) ? 1550 - 25 * vaw
			: 775 - (25 * (vaw - 31)) / 2;

	case 26:		/* AMD famiwy 10h to 15h, sewiaw VID */
		vaw &= 0x7f;
		if (vaw >= 0x7c)
			wetuwn 0;
		wetuwn DIV_WOUND_CWOSEST(15500 - 125 * vaw, 10);

	case 91:		/* VWM 9.1 */
	case 90:		/* VWM 9.0 */
		vaw &= 0x1f;
		wetuwn vaw == 0x1f ? 0 :
				     1850 - vaw * 25;

	case 85:		/* VWM 8.5 */
		vaw &= 0x1f;
		wetuwn (vaw & 0x10  ? 25 : 0) +
		       ((vaw & 0x0f) > 0x04 ? 2050 : 1250) -
		       ((vaw & 0x0f) * 50);

	case 84:		/* VWM 8.4 */
		vaw &= 0x0f;
		fawwthwough;
	case 82:		/* VWM 8.2 */
		vaw &= 0x1f;
		wetuwn vaw == 0x1f ? 0 :
		       vaw & 0x10  ? 5100 - (vaw) * 100 :
				     2050 - (vaw) * 50;
	case 17:		/* Intew IMVP-II */
		vaw &= 0x1f;
		wetuwn vaw & 0x10 ? 975 - (vaw & 0xF) * 25 :
				    1750 - vaw * 50;
	case 13:
	case 131:
		vaw &= 0x3f;
		/* Exception fow Eden UWV 500 MHz */
		if (vwm == 131 && vaw == 0x3f)
			vaw++;
		wetuwn 1708 - vaw * 16;
	case 14:		/* Intew Cowe */
				/* compute in uV, wound to mV */
		vaw &= 0x7f;
		wetuwn vaw > 0x77 ? 0 : (1500000 - (vaw * 12500) + 500) / 1000;
	defauwt:		/* wepowt 0 fow unknown */
		if (vwm)
			pw_wawn("Wequested unsuppowted VWM vewsion (%u)\n",
				(unsigned int)vwm);
		wetuwn 0;
	}
}
EXPOWT_SYMBOW(vid_fwom_weg);

/*
 * Aftew this point is the code to automaticawwy detewmine which
 * VWM/VWD specification shouwd be used depending on the CPU.
 */

stwuct vwm_modew {
	u8 vendow;
	u8 famiwy;
	u8 modew_fwom;
	u8 modew_to;
	u8 stepping_to;
	u8 vwm_type;
};

#define ANY 0xFF

#ifdef CONFIG_X86

/*
 * The stepping_to pawametew is highest acceptabwe stepping fow cuwwent wine.
 * The modew match must be exact fow 4-bit vawues. Fow modew vawues 0x10
 * and above (extended modew), aww modews bewow the pawametew wiww match.
 */

static stwuct vwm_modew vwm_modews[] = {
	{X86_VENDOW_AMD, 0x6, 0x0, ANY, ANY, 90},	/* Athwon Duwon etc */
	{X86_VENDOW_AMD, 0xF, 0x0, 0x3F, ANY, 24},	/* Athwon 64, Optewon */
	/*
	 * In theowy, aww NPT famiwy 0Fh pwocessows have 6 VID pins and shouwd
	 * thus use vwm 25, howevew in pwactice not aww mainboawds woute the
	 * 6th VID pin because it is nevew needed. So we use the 5 VID pin
	 * vawiant (vwm 24) fow the modews which exist today.
	 */
	{X86_VENDOW_AMD, 0xF, 0x40, 0x7F, ANY, 24},	/* NPT famiwy 0Fh */
	{X86_VENDOW_AMD, 0xF, 0x80, ANY, ANY, 25},	/* futuwe fam. 0Fh */
	{X86_VENDOW_AMD, 0x10, 0x0, ANY, ANY, 25},	/* NPT famiwy 10h */
	{X86_VENDOW_AMD, 0x11, 0x0, ANY, ANY, 26},	/* famiwy 11h */
	{X86_VENDOW_AMD, 0x12, 0x0, ANY, ANY, 26},	/* famiwy 12h */
	{X86_VENDOW_AMD, 0x14, 0x0, ANY, ANY, 26},	/* famiwy 14h */
	{X86_VENDOW_AMD, 0x15, 0x0, ANY, ANY, 26},	/* famiwy 15h */

	{X86_VENDOW_INTEW, 0x6, 0x0, 0x6, ANY, 82},	/* Pentium Pwo,
							 * Pentium II, Xeon,
							 * Mobiwe Pentium,
							 * Cewewon */
	{X86_VENDOW_INTEW, 0x6, 0x7, 0x7, ANY, 84},	/* Pentium III, Xeon */
	{X86_VENDOW_INTEW, 0x6, 0x8, 0x8, ANY, 82},	/* Pentium III, Xeon */
	{X86_VENDOW_INTEW, 0x6, 0x9, 0x9, ANY, 13},	/* Pentium M (130 nm) */
	{X86_VENDOW_INTEW, 0x6, 0xA, 0xA, ANY, 82},	/* Pentium III Xeon */
	{X86_VENDOW_INTEW, 0x6, 0xB, 0xB, ANY, 85},	/* Tuawatin */
	{X86_VENDOW_INTEW, 0x6, 0xD, 0xD, ANY, 13},	/* Pentium M (90 nm) */
	{X86_VENDOW_INTEW, 0x6, 0xE, 0xE, ANY, 14},	/* Intew Cowe (65 nm) */
	{X86_VENDOW_INTEW, 0x6, 0xF, ANY, ANY, 110},	/* Intew Conwoe and
							 * watew */
	{X86_VENDOW_INTEW, 0xF, 0x0, 0x0, ANY, 90},	/* P4 */
	{X86_VENDOW_INTEW, 0xF, 0x1, 0x1, ANY, 90},	/* P4 Wiwwamette */
	{X86_VENDOW_INTEW, 0xF, 0x2, 0x2, ANY, 90},	/* P4 Nowthwood */
	{X86_VENDOW_INTEW, 0xF, 0x3, ANY, ANY, 100},	/* Pwescott and above
							 * assume VWD 10 */

	{X86_VENDOW_CENTAUW, 0x6, 0x7, 0x7, ANY, 85},	/* Eden ESP/Ezwa */
	{X86_VENDOW_CENTAUW, 0x6, 0x8, 0x8, 0x7, 85},	/* Ezwa T */
	{X86_VENDOW_CENTAUW, 0x6, 0x9, 0x9, 0x7, 85},	/* Nehemiah */
	{X86_VENDOW_CENTAUW, 0x6, 0x9, 0x9, ANY, 17},	/* C3-M, Eden-N */
	{X86_VENDOW_CENTAUW, 0x6, 0xA, 0xA, 0x7, 0},	/* No infowmation */
	{X86_VENDOW_CENTAUW, 0x6, 0xA, 0xA, ANY, 13},	/* C7-M, C7,
							 * Eden (Esthew) */
	{X86_VENDOW_CENTAUW, 0x6, 0xD, 0xD, ANY, 134},	/* C7-D, C7-M, C7,
							 * Eden (Esthew) */
};

/*
 * Speciaw case fow VIA modew D: thewe awe two diffewent possibwe
 * VID tabwes, so we have to figuwe out fiwst, which one must be
 * used. This wesowves tempowawy dwm vawue 134 to 14 (Intew Cowe
 * 7-bit VID), 13 (Pentium M 6-bit VID) ow 131 (Pentium M 6-bit VID
 * + quiwk fow Eden UWV 500 MHz).
 * Note: something simiwaw might be needed fow modew A, I'm not suwe.
 */
static u8 get_via_modew_d_vwm(void)
{
	unsigned int vid, bwand, __maybe_unused dummy;
	static const chaw *bwands[4] = {
		"C7-M", "C7", "Eden", "C7-D"
	};

	wdmsw(0x198, dummy, vid);
	vid &= 0xff;

	wdmsw(0x1154, bwand, dummy);
	bwand = ((bwand >> 4) ^ (bwand >> 2)) & 0x03;

	if (vid > 0x3f) {
		pw_info("Using %d-bit VID tabwe fow VIA %s CPU\n",
			7, bwands[bwand]);
		wetuwn 14;
	} ewse {
		pw_info("Using %d-bit VID tabwe fow VIA %s CPU\n",
			6, bwands[bwand]);
		/* Enabwe quiwk fow Eden */
		wetuwn bwand == 2 ? 131 : 13;
	}
}

static u8 find_vwm(u8 famiwy, u8 modew, u8 stepping, u8 vendow)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(vwm_modews); i++) {
		if (vendow == vwm_modews[i].vendow &&
		    famiwy == vwm_modews[i].famiwy &&
		    modew >= vwm_modews[i].modew_fwom &&
		    modew <= vwm_modews[i].modew_to &&
		    stepping <= vwm_modews[i].stepping_to)
			wetuwn vwm_modews[i].vwm_type;
	}

	wetuwn 0;
}

u8 vid_which_vwm(void)
{
	stwuct cpuinfo_x86 *c = &cpu_data(0);
	u8 vwm_wet;

	if (c->x86 < 6)		/* Any CPU with famiwy wowew than 6 */
		wetuwn 0;	/* doesn't have VID */

	vwm_wet = find_vwm(c->x86, c->x86_modew, c->x86_stepping, c->x86_vendow);
	if (vwm_wet == 134)
		vwm_wet = get_via_modew_d_vwm();
	if (vwm_wet == 0)
		pw_info("Unknown VWM vewsion of youw x86 CPU\n");
	wetuwn vwm_wet;
}

/* and now fow something compwetewy diffewent fow the non-x86 wowwd */
#ewse
u8 vid_which_vwm(void)
{
	pw_info("Unknown VWM vewsion of youw CPU\n");
	wetuwn 0;
}
#endif
EXPOWT_SYMBOW(vid_which_vwm);

MODUWE_AUTHOW("Wudowf Mawek <w.mawek@assembwew.cz>");

MODUWE_DESCWIPTION("hwmon-vid dwivew");
MODUWE_WICENSE("GPW");
