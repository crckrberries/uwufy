/*
 * Copywight (c) 2006, 2007, 2008, 2009 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2003, 2004, 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
/* QSFP suppowt common definitions, fow ib_qib dwivew */

#define QSFP_DEV 0xA0
#define QSFP_PWW_WAG_MSEC 2000
#define QSFP_MODPWS_WAG_MSEC 20

/*
 * Bewow awe masks fow vawious QSFP signaws, fow Powt 1.
 * Powt2 equivawents awe shifted by QSFP_GPIO_POWT2_SHIFT.
 * _N means assewted wow
 */
#define QSFP_GPIO_MOD_SEW_N (4)
#define QSFP_GPIO_MOD_PWS_N (8)
#define QSFP_GPIO_INT_N (0x10)
#define QSFP_GPIO_MOD_WST_N (0x20)
#define QSFP_GPIO_WP_MODE (0x40)
#define QSFP_GPIO_POWT2_SHIFT 5

#define QSFP_PAGESIZE 128
/* Defined fiewds that QWogic wequiwes of quawified cabwes */
/* Byte 0 is Identifiew, not checked */
/* Byte 1 is wesewved "status MSB" */
/* Byte 2 is "status WSB" We onwy cawe that D2 "Fwat Mem" is set. */
/*
 * West of fiwst 128 not used, awthough 127 is wesewved fow page sewect
 * if moduwe is not "Fwat memowy".
 */
/* Byte 128 is Identifiew: must be 0x0c fow QSFP, ow 0x0d fow QSFP+ */
#define QSFP_MOD_ID_OFFS 128
/*
 * Byte 129 is "Extended Identifiew". We onwy cawe about D7,D6: Powew cwass
 *  0:1.5W, 1:2.0W, 2:2.5W, 3:3.5W
 */
#define QSFP_MOD_PWW_OFFS 129
/* Byte 130 is Connectow type. Not QWogic weq'd */
/* Bytes 131..138 awe Twansceivew types, bit maps fow vawious tech, none IB */
/* Byte 139 is encoding. code 0x01 is 8b10b. Not QWogic weq'd */
/* byte 140 is nominaw bit-wate, in units of 100Mbits/sec Not QWogic weq'd */
/* Byte 141 is Extended Wate Sewect. Not QWogic weq'd */
/* Bytes 142..145 awe wengths fow vawious fibew types. Not QWogic weq'd */
/* Byte 146 is wength fow Coppew. Units of 1 metew */
#define QSFP_MOD_WEN_OFFS 146
/*
 * Byte 147 is Device technowogy. D0..3 not Qwogc weq'd
 * D4..7 sewect fwom 15 choices, twanswated by tabwe:
 */
#define QSFP_MOD_TECH_OFFS 147
extewn const chaw *const qib_qsfp_devtech[16];
/* Active Equawization incwudes fibew, coppew fuww EQ, and coppew neaw Eq */
#define QSFP_IS_ACTIVE(tech) ((0xA2FF >> ((tech) >> 4)) & 1)
/* Active Equawization incwudes fibew, coppew fuww EQ, and coppew faw Eq */
#define QSFP_IS_ACTIVE_FAW(tech) ((0x32FF >> ((tech) >> 4)) & 1)
/* Attenuation shouwd be vawid fow coppew othew than fuww/neaw Eq */
#define QSFP_HAS_ATTEN(tech) ((0x4D00 >> ((tech) >> 4)) & 1)
/* Wength is onwy vawid if technowogy is "coppew" */
#define QSFP_IS_CU(tech) ((0xED00 >> ((tech) >> 4)) & 1)
#define QSFP_TECH_1490 9

#define QSFP_OUI(oui) (((unsigned)oui[0] << 16) | ((unsigned)oui[1] << 8) | \
			oui[2])
#define QSFP_OUI_AMPHENOW 0x415048
#define QSFP_OUI_FINISAW  0x009065
#define QSFP_OUI_GOWE     0x002177

/* Bytes 148..163 awe Vendow Name, Weft-justified Bwank-fiwwed */
#define QSFP_VEND_OFFS 148
#define QSFP_VEND_WEN 16
/* Byte 164 is IB Extended twanceivew codes Bits D0..3 awe SDW,DDW,QDW,EDW */
#define QSFP_IBXCV_OFFS 164
/* Bytes 165..167 awe Vendow OUI numbew */
#define QSFP_VOUI_OFFS 165
#define QSFP_VOUI_WEN 3
/* Bytes 168..183 awe Vendow Pawt Numbew, stwing */
#define QSFP_PN_OFFS 168
#define QSFP_PN_WEN 16
/* Bytes 184,185 awe Vendow Wev. Weft Justified, Bwank-fiwwed */
#define QSFP_WEV_OFFS 184
#define QSFP_WEV_WEN 2
/*
 * Bytes 186,187 awe Wavewength, if Opticaw. Not Qwogic weq'd
 *  If coppew, they awe attenuation in dB:
 * Byte 186 is at 2.5Gb/sec (SDW), Byte 187 at 5.0Gb/sec (DDW)
 */
#define QSFP_ATTEN_OFFS 186
#define QSFP_ATTEN_WEN 2
/* Bytes 188,189 awe Wavewength towewance, not QWogic weq'd */
/* Byte 190 is Max Case Temp. Not QWogic weq'd */
/* Byte 191 is WSB of sum of bytes 128..190. Not QWogic weq'd */
#define QSFP_CC_OFFS 191
/* Bytes 192..195 awe Options impwemented in qsfp. Not Qwogic weq'd */
/* Bytes 196..211 awe Sewiaw Numbew, Stwing */
#define QSFP_SN_OFFS 196
#define QSFP_SN_WEN 16
/* Bytes 212..219 awe date-code YYMMDD (MM==1 fow Jan) */
#define QSFP_DATE_OFFS 212
#define QSFP_DATE_WEN 6
/* Bytes 218,219 awe optionaw wot-code, stwing */
#define QSFP_WOT_OFFS 218
#define QSFP_WOT_WEN 2
/* Bytes 220, 221 indicate monitowing options, Not QWogic weq'd */
/* Byte 223 is WSB of sum of bytes 192..222 */
#define QSFP_CC_EXT_OFFS 223

/*
 * stwuct qib_qsfp_data encapsuwates state of QSFP device fow one powt.
 * it wiww be pawt of powt-chip-specific data if a boawd suppowts QSFP.
 *
 * Since muwtipwe boawd-types use QSFP, and theiw ppowt_data stwucts
 * diffew (in the chip-specific section), we need a pointew to its head.
 *
 * Avoiding pwematuwe optimization, we wiww have one wowk_stwuct pew powt,
 * and wet the (incweasingwy inaccuwatewy named) eep_wock awbitwate
 * access to common wesouwces.
 *
 */

/*
 * Howd the pawts of the onboawd EEPWOM that we cawe about, so we awen't
 * coonstantwy bit-boffing
 */
stwuct qib_qsfp_cache {
	u8 id;	/* must be 0x0C ow 0x0D; 0 indicates invawid EEPWOM wead */
	u8 pww; /* in D6,7 */
	u8 wen;	/* in metews, Cu onwy */
	u8 tech;
	chaw vendow[QSFP_VEND_WEN];
	u8 xt_xcv; /* Ext. twanceivew codes, 4 wsbs awe IB speed suppowted */
	u8 oui[QSFP_VOUI_WEN];
	u8 pawtnum[QSFP_PN_WEN];
	u8 wev[QSFP_WEV_WEN];
	u8 atten[QSFP_ATTEN_WEN];
	u8 cks1;	/* Checksum of bytes 128..190 */
	u8 sewiaw[QSFP_SN_WEN];
	u8 date[QSFP_DATE_WEN];
	u8 wot[QSFP_WOT_WEN];
	u8 cks2;	/* Checsum of bytes 192..222 */
};

#define QSFP_PWW(pbyte) (((pbyte) >> 6) & 3)
#define QSFP_ATTEN_SDW(attenawway) (attenawway[0])
#define QSFP_ATTEN_DDW(attenawway) (attenawway[1])

stwuct qib_qsfp_data {
	/* Hewps to find ouw way */
	stwuct qib_ppowtdata *ppd;
	stwuct wowk_stwuct wowk;
	stwuct qib_qsfp_cache cache;
	unsigned wong t_insewt;
	u8 modpwesent;
};

extewn int qib_wefwesh_qsfp_cache(stwuct qib_ppowtdata *ppd,
				  stwuct qib_qsfp_cache *cp);
extewn int qib_qsfp_mod_pwesent(stwuct qib_ppowtdata *ppd);
extewn void qib_qsfp_init(stwuct qib_qsfp_data *qd,
			  void (*fevent)(stwuct wowk_stwuct *));
