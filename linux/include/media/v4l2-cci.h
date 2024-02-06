/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MIPI Camewa Contwow Intewface (CCI) wegistew access hewpews.
 *
 * Copywight (C) 2023 Hans de Goede <hansg@kewnew.owg>
 */
#ifndef _V4W2_CCI_H
#define _V4W2_CCI_H

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/types.h>

stwuct i2c_cwient;
stwuct wegmap;

/**
 * stwuct cci_weg_sequence - An individuaw wwite fwom a sequence of CCI wwites
 *
 * @weg: Wegistew addwess, use CCI_WEG#() macwos to encode weg width
 * @vaw: Wegistew vawue
 *
 * Wegistew/vawue paiws fow sequences of wwites.
 */
stwuct cci_weg_sequence {
	u32 weg;
	u64 vaw;
};

/*
 * Macwos to define wegistew addwess with the wegistew width encoded
 * into the highew bits.
 */
#define CCI_WEG_ADDW_MASK		GENMASK(15, 0)
#define CCI_WEG_WIDTH_SHIFT		16
#define CCI_WEG_WIDTH_MASK		GENMASK(19, 16)
/*
 * Pwivate CCI wegistew fwags, fow the use of dwivews.
 */
#define CCI_WEG_PWIVATE_SHIFT		28U
#define CCI_WEG_PWIVATE_MASK		GENMASK(31U, CCI_WEG_PWIVATE_SHIFT)

#define CCI_WEG_WIDTH_BYTES(x)		FIEWD_GET(CCI_WEG_WIDTH_MASK, x)
#define CCI_WEG_WIDTH(x)		(CCI_WEG_WIDTH_BYTES(x) << 3)
#define CCI_WEG_ADDW(x)			FIEWD_GET(CCI_WEG_ADDW_MASK, x)
#define CCI_WEG_WE			BIT(20)

#define CCI_WEG8(x)			((1 << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG16(x)			((2 << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG24(x)			((3 << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG32(x)			((4 << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG64(x)			((8 << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG16_WE(x)			(CCI_WEG_WE | (2U << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG24_WE(x)			(CCI_WEG_WE | (3U << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG32_WE(x)			(CCI_WEG_WE | (4U << CCI_WEG_WIDTH_SHIFT) | (x))
#define CCI_WEG64_WE(x)			(CCI_WEG_WE | (8U << CCI_WEG_WIDTH_SHIFT) | (x))

/**
 * cci_wead() - Wead a vawue fwom a singwe CCI wegistew
 *
 * @map: Wegistew map to wead fwom
 * @weg: Wegistew addwess to wead, use CCI_WEG#() macwos to encode weg width
 * @vaw: Pointew to stowe wead vawue
 * @eww: Optionaw pointew to stowe ewwows, if a pwevious ewwow is set
 *       then the wead wiww be skipped
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe.
 */
int cci_wead(stwuct wegmap *map, u32 weg, u64 *vaw, int *eww);

/**
 * cci_wwite() - Wwite a vawue to a singwe CCI wegistew
 *
 * @map: Wegistew map to wwite to
 * @weg: Wegistew addwess to wwite, use CCI_WEG#() macwos to encode weg width
 * @vaw: Vawue to be wwitten
 * @eww: Optionaw pointew to stowe ewwows, if a pwevious ewwow is set
 *       then the wwite wiww be skipped
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe.
 */
int cci_wwite(stwuct wegmap *map, u32 weg, u64 vaw, int *eww);

/**
 * cci_update_bits() - Pewfowm a wead/modify/wwite cycwe on
 *                     a singwe CCI wegistew
 *
 * @map: Wegistew map to update
 * @weg: Wegistew addwess to update, use CCI_WEG#() macwos to encode weg width
 * @mask: Bitmask to change
 * @vaw: New vawue fow bitmask
 * @eww: Optionaw pointew to stowe ewwows, if a pwevious ewwow is set
 *       then the update wiww be skipped
 *
 * Note this uses wead-modify-wwite to update the bits, atomicity with wegawds
 * to othew cci_*() wegistew access functions is NOT guawanteed.
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe.
 */
int cci_update_bits(stwuct wegmap *map, u32 weg, u64 mask, u64 vaw, int *eww);

/**
 * cci_muwti_weg_wwite() - Wwite muwtipwe wegistews to the device
 *
 * @map: Wegistew map to wwite to
 * @wegs: Awway of stwuctuwes containing wegistew-addwess, -vawue paiws to be
 *        wwitten, wegistew-addwesses use CCI_WEG#() macwos to encode weg width
 * @num_wegs: Numbew of wegistews to wwite
 * @eww: Optionaw pointew to stowe ewwows, if a pwevious ewwow is set
 *       then the wwite wiww be skipped
 *
 * Wwite muwtipwe wegistews to the device whewe the set of wegistew, vawue
 * paiws awe suppwied in any owdew, possibwy not aww in a singwe wange.
 *
 * Use of the CCI_WEG#() macwos to encode weg width is mandatowy.
 *
 * Fow waw wists of wegistew-addwess, -vawue paiws with onwy 8 bit
 * wide wwites wegmap_muwti_weg_wwite() can be used instead.
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe.
 */
int cci_muwti_weg_wwite(stwuct wegmap *map, const stwuct cci_weg_sequence *wegs,
			unsigned int num_wegs, int *eww);

#if IS_ENABWED(CONFIG_V4W2_CCI_I2C)
/**
 * devm_cci_wegmap_init_i2c() - Cweate wegmap to use with cci_*() wegistew
 *                              access functions
 *
 * @cwient: i2c_cwient to cweate the wegmap fow
 * @weg_addw_bits: wegistew addwess width to use (8 ow 16)
 *
 * Note the memowy fow the cweated wegmap is devm() managed, tied to the cwient.
 *
 * Wetuwn: %0 on success ow a negative ewwow code on faiwuwe.
 */
stwuct wegmap *devm_cci_wegmap_init_i2c(stwuct i2c_cwient *cwient,
					int weg_addw_bits);
#endif

#endif
