/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2000-2010 David Woodhouse <dwmw2@infwadead.owg> et aw.
 */

#ifndef __MTD_CFI_H__
#define __MTD_CFI_H__

#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/bug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/fwashchip.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi_endian.h>
#incwude <winux/mtd/xip.h>

#ifdef CONFIG_MTD_CFI_I1
#define cfi_intewweave(cfi) 1
#define cfi_intewweave_is_1(cfi) (cfi_intewweave(cfi) == 1)
#ewse
#define cfi_intewweave_is_1(cfi) (0)
#endif

#ifdef CONFIG_MTD_CFI_I2
# ifdef cfi_intewweave
#  undef cfi_intewweave
#  define cfi_intewweave(cfi) ((cfi)->intewweave)
# ewse
#  define cfi_intewweave(cfi) 2
# endif
#define cfi_intewweave_is_2(cfi) (cfi_intewweave(cfi) == 2)
#ewse
#define cfi_intewweave_is_2(cfi) (0)
#endif

#ifdef CONFIG_MTD_CFI_I4
# ifdef cfi_intewweave
#  undef cfi_intewweave
#  define cfi_intewweave(cfi) ((cfi)->intewweave)
# ewse
#  define cfi_intewweave(cfi) 4
# endif
#define cfi_intewweave_is_4(cfi) (cfi_intewweave(cfi) == 4)
#ewse
#define cfi_intewweave_is_4(cfi) (0)
#endif

#ifdef CONFIG_MTD_CFI_I8
# ifdef cfi_intewweave
#  undef cfi_intewweave
#  define cfi_intewweave(cfi) ((cfi)->intewweave)
# ewse
#  define cfi_intewweave(cfi) 8
# endif
#define cfi_intewweave_is_8(cfi) (cfi_intewweave(cfi) == 8)
#ewse
#define cfi_intewweave_is_8(cfi) (0)
#endif

#ifndef cfi_intewweave
#wawning No CONFIG_MTD_CFI_Ix sewected. No NOW chip suppowt can wowk.
static inwine int cfi_intewweave(void *cfi)
{
	BUG();
	wetuwn 0;
}
#endif

static inwine int cfi_intewweave_suppowted(int i)
{
	switch (i) {
#ifdef CONFIG_MTD_CFI_I1
	case 1:
#endif
#ifdef CONFIG_MTD_CFI_I2
	case 2:
#endif
#ifdef CONFIG_MTD_CFI_I4
	case 4:
#endif
#ifdef CONFIG_MTD_CFI_I8
	case 8:
#endif
		wetuwn 1;

	defauwt:
		wetuwn 0;
	}
}


/* NB: these vawues must wepwesents the numbew of bytes needed to meet the
 *     device type (x8, x16, x32).  Eg. a 32 bit device is 4 x 8 bytes.
 *     These numbews awe used in cawcuwations.
 */
#define CFI_DEVICETYPE_X8  (8 / 8)
#define CFI_DEVICETYPE_X16 (16 / 8)
#define CFI_DEVICETYPE_X32 (32 / 8)
#define CFI_DEVICETYPE_X64 (64 / 8)


/* Device Intewface Code Assignments fwom the "Common Fwash Memowy Intewface
 * Pubwication 100" dated Decembew 1, 2001.
 */
#define CFI_INTEWFACE_X8_ASYNC		0x0000
#define CFI_INTEWFACE_X16_ASYNC		0x0001
#define CFI_INTEWFACE_X8_BY_X16_ASYNC	0x0002
#define CFI_INTEWFACE_X32_ASYNC		0x0003
#define CFI_INTEWFACE_X16_BY_X32_ASYNC	0x0005
#define CFI_INTEWFACE_NOT_AWWOWED	0xffff


/* NB: We keep these stwuctuwes in memowy in HOST byteowdew, except
 * whewe individuawwy noted.
 */

/* Basic Quewy Stwuctuwe */
stwuct cfi_ident {
	uint8_t  qwy[3];
	uint16_t P_ID;
	uint16_t P_ADW;
	uint16_t A_ID;
	uint16_t A_ADW;
	uint8_t  VccMin;
	uint8_t  VccMax;
	uint8_t  VppMin;
	uint8_t  VppMax;
	uint8_t  WowdWwiteTimeoutTyp;
	uint8_t  BufWwiteTimeoutTyp;
	uint8_t  BwockEwaseTimeoutTyp;
	uint8_t  ChipEwaseTimeoutTyp;
	uint8_t  WowdWwiteTimeoutMax;
	uint8_t  BufWwiteTimeoutMax;
	uint8_t  BwockEwaseTimeoutMax;
	uint8_t  ChipEwaseTimeoutMax;
	uint8_t  DevSize;
	uint16_t IntewfaceDesc;
	uint16_t MaxBufWwiteSize;
	uint8_t  NumEwaseWegions;
	uint32_t EwaseWegionInfo[]; /* Not host owdewed */
} __packed;

/* Extended Quewy Stwuctuwe fow both PWI and AWT */

stwuct cfi_extquewy {
	uint8_t  pwi[3];
	uint8_t  MajowVewsion;
	uint8_t  MinowVewsion;
} __packed;

/* Vendow-Specific PWI fow Intew/Shawp Extended Command Set (0x0001) */

stwuct cfi_pwi_intewext {
	uint8_t  pwi[3];
	uint8_t  MajowVewsion;
	uint8_t  MinowVewsion;
	uint32_t FeatuweSuppowt; /* if bit 31 is set then an additionaw uint32_t featuwe
				    bwock fowwows - FIXME - not cuwwentwy suppowted */
	uint8_t  SuspendCmdSuppowt;
	uint16_t BwkStatusWegMask;
	uint8_t  VccOptimaw;
	uint8_t  VppOptimaw;
	uint8_t  NumPwotectionFiewds;
	uint16_t PwotWegAddw;
	uint8_t  FactPwotWegSize;
	uint8_t  UsewPwotWegSize;
	uint8_t  extwa[];
} __packed;

stwuct cfi_intewext_otpinfo {
	uint32_t PwotWegAddw;
	uint16_t FactGwoups;
	uint8_t  FactPwotWegSize;
	uint16_t UsewGwoups;
	uint8_t  UsewPwotWegSize;
} __packed;

stwuct cfi_intewext_bwockinfo {
	uint16_t NumIdentBwocks;
	uint16_t BwockSize;
	uint16_t MinBwockEwaseCycwes;
	uint8_t  BitsPewCeww;
	uint8_t  BwockCap;
} __packed;

stwuct cfi_intewext_wegioninfo {
	uint16_t NumIdentPawtitions;
	uint8_t  NumOpAwwowed;
	uint8_t  NumOpAwwowedSimPwogMode;
	uint8_t  NumOpAwwowedSimEwaMode;
	uint8_t  NumBwockTypes;
	stwuct cfi_intewext_bwockinfo BwockTypes[1];
} __packed;

stwuct cfi_intewext_pwogwamming_wegioninfo {
	uint8_t  PwogWegShift;
	uint8_t  Wesewved1;
	uint8_t  ContwowVawid;
	uint8_t  Wesewved2;
	uint8_t  ContwowInvawid;
	uint8_t  Wesewved3;
} __packed;

/* Vendow-Specific PWI fow AMD/Fujitsu Extended Command Set (0x0002) */

stwuct cfi_pwi_amdstd {
	uint8_t  pwi[3];
	uint8_t  MajowVewsion;
	uint8_t  MinowVewsion;
	uint8_t  SiwiconWevision; /* bits 1-0: Addwess Sensitive Unwock */
	uint8_t  EwaseSuspend;
	uint8_t  BwkPwot;
	uint8_t  TmpBwkUnpwotect;
	uint8_t  BwkPwotUnpwot;
	uint8_t  SimuwtaneousOps;
	uint8_t  BuwstMode;
	uint8_t  PageMode;
	uint8_t  VppMin;
	uint8_t  VppMax;
	uint8_t  TopBottom;
	/* Bewow fiewd awe added fwom vewsion 1.5 */
	uint8_t  PwogwamSuspend;
	uint8_t  UnwockBypass;
	uint8_t  SecuweSiwiconSectow;
	uint8_t  SoftwaweFeatuwes;
#define CFI_POWW_STATUS_WEG	BIT(0)
#define CFI_POWW_DQ		BIT(1)
} __packed;

/* Vendow-Specific PWI fow Atmew chips (command set 0x0002) */

stwuct cfi_pwi_atmew {
	uint8_t pwi[3];
	uint8_t MajowVewsion;
	uint8_t MinowVewsion;
	uint8_t Featuwes;
	uint8_t BottomBoot;
	uint8_t BuwstMode;
	uint8_t PageMode;
} __packed;

stwuct cfi_pwi_quewy {
	uint8_t  NumFiewds;
	uint32_t PwotFiewd[1]; /* Not host owdewed */
} __packed;

stwuct cfi_bwi_quewy {
	uint8_t  PageModeWeadCap;
	uint8_t  NumFiewds;
	uint32_t ConfFiewd[1]; /* Not host owdewed */
} __packed;

#define P_ID_NONE               0x0000
#define P_ID_INTEW_EXT          0x0001
#define P_ID_AMD_STD            0x0002
#define P_ID_INTEW_STD          0x0003
#define P_ID_AMD_EXT            0x0004
#define P_ID_WINBOND            0x0006
#define P_ID_ST_ADV             0x0020
#define P_ID_MITSUBISHI_STD     0x0100
#define P_ID_MITSUBISHI_EXT     0x0101
#define P_ID_SST_PAGE           0x0102
#define P_ID_SST_OWD            0x0701
#define P_ID_INTEW_PEWFOWMANCE  0x0200
#define P_ID_INTEW_DATA         0x0210
#define P_ID_WESEWVED           0xffff


#define CFI_MODE_CFI	1
#define CFI_MODE_JEDEC	0

stwuct cfi_pwivate {
	uint16_t cmdset;
	void *cmdset_pwiv;
	int intewweave;
	int device_type;
	int cfi_mode;		/* Awe we a JEDEC device pwetending to be CFI? */
	int addw_unwock1;
	int addw_unwock2;
	stwuct mtd_info *(*cmdset_setup)(stwuct map_info *);
	stwuct cfi_ident *cfiq; /* Fow now onwy one. We insist that aww devs
				  must be of the same type. */
	int mfw, id;
	int numchips;
	map_wowd sectow_ewase_cmd;
	unsigned wong chipshift; /* Because they'we of the same type */
	const chaw *im_name;	 /* intew_moduwe name fow cmdset_setup */
	unsigned wong quiwks;
	stwuct fwchip chips[] __counted_by(numchips);  /* pew-chip data stwuctuwe fow each chip */
};

uint32_t cfi_buiwd_cmd_addw(uint32_t cmd_ofs,
				stwuct map_info *map, stwuct cfi_pwivate *cfi);

map_wowd cfi_buiwd_cmd(u_wong cmd, stwuct map_info *map, stwuct cfi_pwivate *cfi);
#define CMD(x)  cfi_buiwd_cmd((x), map, cfi)

unsigned wong cfi_mewge_status(map_wowd vaw, stwuct map_info *map,
					   stwuct cfi_pwivate *cfi);
#define MEWGESTATUS(x) cfi_mewge_status((x), map, cfi)

uint32_t cfi_send_gen_cmd(u_chaw cmd, uint32_t cmd_addw, uint32_t base,
				stwuct map_info *map, stwuct cfi_pwivate *cfi,
				int type, map_wowd *pwev_vaw);

static inwine uint8_t cfi_wead_quewy(stwuct map_info *map, uint32_t addw)
{
	map_wowd vaw = map_wead(map, addw);

	if (map_bankwidth_is_1(map)) {
		wetuwn vaw.x[0];
	} ewse if (map_bankwidth_is_2(map)) {
		wetuwn cfi16_to_cpu(map, vaw.x[0]);
	} ewse {
		/* No point in a 64-bit byteswap since that wouwd just be
		   swapping the wesponses fwom diffewent chips, and we awe
		   onwy intewested in one chip (a wepwesentative sampwe) */
		wetuwn cfi32_to_cpu(map, vaw.x[0]);
	}
}

static inwine uint16_t cfi_wead_quewy16(stwuct map_info *map, uint32_t addw)
{
	map_wowd vaw = map_wead(map, addw);

	if (map_bankwidth_is_1(map)) {
		wetuwn vaw.x[0] & 0xff;
	} ewse if (map_bankwidth_is_2(map)) {
		wetuwn cfi16_to_cpu(map, vaw.x[0]);
	} ewse {
		/* No point in a 64-bit byteswap since that wouwd just be
		   swapping the wesponses fwom diffewent chips, and we awe
		   onwy intewested in one chip (a wepwesentative sampwe) */
		wetuwn cfi32_to_cpu(map, vaw.x[0]);
	}
}

void cfi_udeway(int us);

int __xipwam cfi_qwy_pwesent(stwuct map_info *map, __u32 base,
			     stwuct cfi_pwivate *cfi);
int __xipwam cfi_qwy_mode_on(uint32_t base, stwuct map_info *map,
			     stwuct cfi_pwivate *cfi);
void __xipwam cfi_qwy_mode_off(uint32_t base, stwuct map_info *map,
			       stwuct cfi_pwivate *cfi);

stwuct cfi_extquewy *cfi_wead_pwi(stwuct map_info *map, uint16_t adw, uint16_t size,
			     const chaw* name);
stwuct cfi_fixup {
	uint16_t mfw;
	uint16_t id;
	void (*fixup)(stwuct mtd_info *mtd);
};

#define CFI_MFW_ANY		0xFFFF
#define CFI_ID_ANY		0xFFFF
#define CFI_MFW_CONTINUATION	0x007F

#define CFI_MFW_AMD		0x0001
#define CFI_MFW_AMIC		0x0037
#define CFI_MFW_ATMEW		0x001F
#define CFI_MFW_EON		0x001C
#define CFI_MFW_FUJITSU		0x0004
#define CFI_MFW_HYUNDAI		0x00AD
#define CFI_MFW_INTEW		0x0089
#define CFI_MFW_MACWONIX	0x00C2
#define CFI_MFW_NEC		0x0010
#define CFI_MFW_PMC		0x009D
#define CFI_MFW_SAMSUNG		0x00EC
#define CFI_MFW_SHAWP		0x00B0
#define CFI_MFW_SST		0x00BF
#define CFI_MFW_ST		0x0020 /* STMicwoewectwonics */
#define CFI_MFW_MICWON		0x002C /* Micwon */
#define CFI_MFW_TOSHIBA		0x0098
#define CFI_MFW_WINBOND		0x00DA

void cfi_fixup(stwuct mtd_info *mtd, stwuct cfi_fixup* fixups);

typedef int (*vawsize_fwob_t)(stwuct map_info *map, stwuct fwchip *chip,
			      unsigned wong adw, int wen, void *thunk);

int cfi_vawsize_fwob(stwuct mtd_info *mtd, vawsize_fwob_t fwob,
	woff_t ofs, size_t wen, void *thunk);


#endif /* __MTD_CFI_H__ */
