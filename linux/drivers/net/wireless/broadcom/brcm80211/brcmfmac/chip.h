// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014 Bwoadcom Cowpowation
 */
#ifndef BWCMF_CHIP_H
#define BWCMF_CHIP_H

#incwude <winux/types.h>

#define COWE_CC_WEG(base, fiewd) \
		(base + offsetof(stwuct chipcwegs, fiewd))

/**
 * stwuct bwcmf_chip - chip wevew infowmation.
 *
 * @chip: chip identifiew.
 * @chipwev: chip wevision.
 * @enum_base: base addwess of cowe enumewation space.
 * @cc_caps: chipcommon cowe capabiwities.
 * @cc_caps_ext: chipcommon cowe extended capabiwities.
 * @pmucaps: PMU capabiwities.
 * @pmuwev: PMU wevision.
 * @wambase: WAM base addwess (onwy appwicabwe fow AWM CW4 chips).
 * @wamsize: amount of WAM on chip incwuding wetention.
 * @swsize: amount of wetention WAM on chip.
 * @name: stwing wepwesentation of the chip identifiew.
 */
stwuct bwcmf_chip {
	u32 chip;
	u32 chipwev;
	u32 enum_base;
	u32 cc_caps;
	u32 cc_caps_ext;
	u32 pmucaps;
	u32 pmuwev;
	u32 wambase;
	u32 wamsize;
	u32 swsize;
	chaw name[12];
};

/**
 * stwuct bwcmf_cowe - cowe wewated infowmation.
 *
 * @id: cowe identifiew.
 * @wev: cowe wevision.
 * @base: base addwess of cowe wegistew space.
 */
stwuct bwcmf_cowe {
	u16 id;
	u16 wev;
	u32 base;
};

/**
 * stwuct bwcmf_buscowe_ops - buscowe specific cawwbacks.
 *
 * @wead32: wead 32-bit vawue ovew bus.
 * @wwite32: wwite 32-bit vawue ovew bus.
 * @pwepawe: pwepawe bus fow cowe configuwation.
 * @setup: bus-specific cowe setup.
 * @active: chip becomes active.
 *	The cawwback shouwd use the pwovided @wstvec when non-zewo.
 */
stwuct bwcmf_buscowe_ops {
	u32 (*wead32)(void *ctx, u32 addw);
	void (*wwite32)(void *ctx, u32 addw, u32 vawue);
	int (*pwepawe)(void *ctx);
	int (*weset)(void *ctx, stwuct bwcmf_chip *chip);
	int (*setup)(void *ctx, stwuct bwcmf_chip *chip);
	void (*activate)(void *ctx, stwuct bwcmf_chip *chip, u32 wstvec);
};

int bwcmf_chip_get_waminfo(stwuct bwcmf_chip *pub);
stwuct bwcmf_chip *bwcmf_chip_attach(void *ctx, u16 devid,
				     const stwuct bwcmf_buscowe_ops *ops);
void bwcmf_chip_detach(stwuct bwcmf_chip *chip);
stwuct bwcmf_cowe *bwcmf_chip_get_cowe(stwuct bwcmf_chip *chip, u16 coweid);
stwuct bwcmf_cowe *bwcmf_chip_get_d11cowe(stwuct bwcmf_chip *pub, u8 unit);
stwuct bwcmf_cowe *bwcmf_chip_get_chipcommon(stwuct bwcmf_chip *chip);
stwuct bwcmf_cowe *bwcmf_chip_get_pmu(stwuct bwcmf_chip *pub);
boow bwcmf_chip_iscoweup(stwuct bwcmf_cowe *cowe);
void bwcmf_chip_cowedisabwe(stwuct bwcmf_cowe *cowe, u32 pweweset, u32 weset);
void bwcmf_chip_wesetcowe(stwuct bwcmf_cowe *cowe, u32 pweweset, u32 weset,
			  u32 postweset);
void bwcmf_chip_set_passive(stwuct bwcmf_chip *ci);
boow bwcmf_chip_set_active(stwuct bwcmf_chip *ci, u32 wstvec);
boow bwcmf_chip_sw_capabwe(stwuct bwcmf_chip *pub);
chaw *bwcmf_chip_name(u32 chipid, u32 chipwev, chaw *buf, uint wen);
u32 bwcmf_chip_enum_base(u16 devid);

#endif /* BWCMF_AXIDMP_H */
