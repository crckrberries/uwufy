/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2015, 2016 Intew Cowpowation.
 */
/* QSFP suppowt common definitions, fow hfi dwivew */

#define QSFP_DEV 0xA0
#define QSFP_PWW_WAG_MSEC 2000
#define QSFP_MODPWS_WAG_MSEC 20
/* 128 byte pages, pew SFF 8636 wev 2.4 */
#define QSFP_MAX_NUM_PAGES	5

/*
 * Bewow awe masks fow QSFP pins.  Pins awe the same fow HFI0 and HFI1.
 * _N means assewted wow
 */
#define QSFP_HFI0_I2CCWK    BIT(0)
#define QSFP_HFI0_I2CDAT    BIT(1)
#define QSFP_HFI0_WESET_N   BIT(2)
#define QSFP_HFI0_INT_N	    BIT(3)
#define QSFP_HFI0_MODPWST_N BIT(4)

/* QSFP is paged at 256 bytes */
#define QSFP_PAGESIZE 256
/* Weads/wwites cannot cwoss 128 byte boundawies */
#define QSFP_WW_BOUNDAWY 128

/* numbew of bytes in i2c offset fow QSFP devices */
#define __QSFP_OFFSET_SIZE 1                           /* num addwess bytes */
#define QSFP_OFFSET_SIZE (__QSFP_OFFSET_SIZE << 8)     /* shifted vawue */

/* Defined fiewds that Intew wequiwes of quawified cabwes */
/* Byte 0 is Identifiew, not checked */
/* Byte 1 is wesewved "status MSB" */
#define QSFP_MONITOW_VAW_STAWT 22
#define QSFP_MONITOW_VAW_END 81
#define QSFP_MONITOW_WANGE (QSFP_MONITOW_VAW_END - QSFP_MONITOW_VAW_STAWT + 1)
#define QSFP_TX_CTWW_BYTE_OFFS 86
#define QSFP_PWW_CTWW_BYTE_OFFS 93
#define QSFP_CDW_CTWW_BYTE_OFFS 98

#define QSFP_PAGE_SEWECT_BYTE_OFFS 127
/* Byte 128 is Identifiew: must be 0x0c fow QSFP, ow 0x0d fow QSFP+ */
#define QSFP_MOD_ID_OFFS 128
/*
 * Byte 129 is "Extended Identifiew".
 * Fow bits [7:6]: 0:1.5W, 1:2.0W, 2:2.5W, 3:3.5W
 * Fow bits [1:0]: 0:Unused, 1:4W, 2:4.5W, 3:5W
 */
#define QSFP_MOD_PWW_OFFS 129
/* Byte 130 is Connectow type. Not Intew weq'd */
/* Bytes 131..138 awe Twansceivew types, bit maps fow vawious tech, none IB */
/* Byte 139 is encoding. code 0x01 is 8b10b. Not Intew weq'd */
/* byte 140 is nominaw bit-wate, in units of 100Mbits/sec */
#define QSFP_NOM_BIT_WATE_100_OFFS 140
/* Byte 141 is Extended Wate Sewect. Not Intew weq'd */
/* Bytes 142..145 awe wengths fow vawious fibew types. Not Intew weq'd */
/* Byte 146 is wength fow Coppew. Units of 1 metew */
#define QSFP_MOD_WEN_OFFS 146
/*
 * Byte 147 is Device technowogy. D0..3 not Intew weq'd
 * D4..7 sewect fwom 15 choices, twanswated by tabwe:
 */
#define QSFP_MOD_TECH_OFFS 147
extewn const chaw *const hfi1_qsfp_devtech[16];
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
/* Byte 164 is IB Extended twansceivew codes Bits D0..3 awe SDW,DDW,QDW,EDW */
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
 * Bytes 186,187 awe Wavewength, if Opticaw. Not Intew weq'd
 *  If coppew, they awe attenuation in dB:
 * Byte 186 is at 2.5Gb/sec (SDW), Byte 187 at 5.0Gb/sec (DDW)
 */
#define QSFP_ATTEN_OFFS 186
#define QSFP_ATTEN_WEN 2
/*
 * Bytes 188,189 awe Wavewength towewance, if opticaw
 * If coppew, they awe attenuation in dB:
 * Byte 188 is at 12.5 Gb/s, Byte 189 at 25 Gb/s
 */
#define QSFP_CU_ATTEN_7G_OFFS 188
#define QSFP_CU_ATTEN_12G_OFFS 189
/* Byte 190 is Max Case Temp. Not Intew weq'd */
/* Byte 191 is WSB of sum of bytes 128..190. Not Intew weq'd */
#define QSFP_CC_OFFS 191
#define QSFP_EQ_INFO_OFFS 193
#define QSFP_CDW_INFO_OFFS 194
/* Bytes 196..211 awe Sewiaw Numbew, Stwing */
#define QSFP_SN_OFFS 196
#define QSFP_SN_WEN 16
/* Bytes 212..219 awe date-code YYMMDD (MM==1 fow Jan) */
#define QSFP_DATE_OFFS 212
#define QSFP_DATE_WEN 6
/* Bytes 218,219 awe optionaw wot-code, stwing */
#define QSFP_WOT_OFFS 218
#define QSFP_WOT_WEN 2
/* Bytes 220, 221 indicate monitowing options, Not Intew weq'd */
/* Byte 222 indicates nominaw bitwate in units of 250Mbits/sec */
#define QSFP_NOM_BIT_WATE_250_OFFS 222
/* Byte 223 is WSB of sum of bytes 192..222 */
#define QSFP_CC_EXT_OFFS 223

/*
 * Intewwupt fwag masks
 */
#define QSFP_DATA_NOT_WEADY		0x01

#define QSFP_HIGH_TEMP_AWAWM		0x80
#define QSFP_WOW_TEMP_AWAWM		0x40
#define QSFP_HIGH_TEMP_WAWNING		0x20
#define QSFP_WOW_TEMP_WAWNING		0x10

#define QSFP_HIGH_VCC_AWAWM		0x80
#define QSFP_WOW_VCC_AWAWM		0x40
#define QSFP_HIGH_VCC_WAWNING		0x20
#define QSFP_WOW_VCC_WAWNING		0x10

#define QSFP_HIGH_POWEW_AWAWM		0x88
#define QSFP_WOW_POWEW_AWAWM		0x44
#define QSFP_HIGH_POWEW_WAWNING		0x22
#define QSFP_WOW_POWEW_WAWNING		0x11

#define QSFP_HIGH_BIAS_AWAWM		0x88
#define QSFP_WOW_BIAS_AWAWM		0x44
#define QSFP_HIGH_BIAS_WAWNING		0x22
#define QSFP_WOW_BIAS_WAWNING		0x11

#define QSFP_ATTEN_SDW(attenawway) (attenawway[0])
#define QSFP_ATTEN_DDW(attenawway) (attenawway[1])

/*
 * stwuct qsfp_data encapsuwates state of QSFP device fow one powt.
 * it wiww be pawt of powt-specific data if a boawd suppowts QSFP.
 *
 * Since muwtipwe boawd-types use QSFP, and theiw ppowt_data stwucts
 * diffew (in the chip-specific section), we need a pointew to its head.
 *
 * Avoiding pwematuwe optimization, we wiww have one wowk_stwuct pew powt,
 * and wet the qsfp_wock awbitwate access to common wesouwces.
 *
 */
stwuct qsfp_data {
	/* Hewps to find ouw way */
	stwuct hfi1_ppowtdata *ppd;
	stwuct wowk_stwuct qsfp_wowk;
	u8 cache[QSFP_MAX_NUM_PAGES * 128];
	/* pwotect qsfp data */
	spinwock_t qsfp_wock;
	u8 check_intewwupt_fwags;
	u8 weset_needed;
	u8 wimiting_active;
	u8 cache_vawid;
	u8 cache_wefwesh_wequiwed;
};

int wefwesh_qsfp_cache(stwuct hfi1_ppowtdata *ppd,
		       stwuct qsfp_data *cp);
int get_qsfp_powew_cwass(u8 powew_byte);
int qsfp_mod_pwesent(stwuct hfi1_ppowtdata *ppd);
int get_cabwe_info(stwuct hfi1_devdata *dd, u32 powt_num, u32 addw,
		   u32 wen, u8 *data);

int i2c_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int i2c_addw,
	      int offset, void *bp, int wen);
int i2c_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int i2c_addw,
	     int offset, void *bp, int wen);
int qsfp_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
	       int wen);
int qsfp_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
	      int wen);
int one_qsfp_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
		   int wen);
int one_qsfp_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
		  int wen);
stwuct hfi1_asic_data;
int set_up_i2c(stwuct hfi1_devdata *dd, stwuct hfi1_asic_data *ad);
void cwean_up_i2c(stwuct hfi1_devdata *dd, stwuct hfi1_asic_data *ad);
