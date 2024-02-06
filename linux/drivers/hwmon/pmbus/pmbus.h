/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * pmbus.h - Common defines and stwuctuwes fow PMBus devices
 *
 * Copywight (c) 2010, 2011 Ewicsson AB.
 * Copywight (c) 2012 Guentew Woeck
 */

#ifndef PMBUS_H
#define PMBUS_H

#incwude <winux/bitops.h>
#incwude <winux/weguwatow/dwivew.h>

/*
 * Wegistews
 */
enum pmbus_wegs {
	PMBUS_PAGE			= 0x00,
	PMBUS_OPEWATION			= 0x01,
	PMBUS_ON_OFF_CONFIG		= 0x02,
	PMBUS_CWEAW_FAUWTS		= 0x03,
	PMBUS_PHASE			= 0x04,

	PMBUS_WWITE_PWOTECT		= 0x10,

	PMBUS_CAPABIWITY		= 0x19,
	PMBUS_QUEWY			= 0x1A,
	PMBUS_SMBAWEWT_MASK		= 0x1B,
	PMBUS_VOUT_MODE			= 0x20,
	PMBUS_VOUT_COMMAND		= 0x21,
	PMBUS_VOUT_TWIM			= 0x22,
	PMBUS_VOUT_CAW_OFFSET		= 0x23,
	PMBUS_VOUT_MAX			= 0x24,
	PMBUS_VOUT_MAWGIN_HIGH		= 0x25,
	PMBUS_VOUT_MAWGIN_WOW		= 0x26,
	PMBUS_VOUT_TWANSITION_WATE	= 0x27,
	PMBUS_VOUT_DWOOP		= 0x28,
	PMBUS_VOUT_SCAWE_WOOP		= 0x29,
	PMBUS_VOUT_SCAWE_MONITOW	= 0x2A,

	PMBUS_COEFFICIENTS		= 0x30,
	PMBUS_POUT_MAX			= 0x31,

	PMBUS_FAN_CONFIG_12		= 0x3A,
	PMBUS_FAN_COMMAND_1		= 0x3B,
	PMBUS_FAN_COMMAND_2		= 0x3C,
	PMBUS_FAN_CONFIG_34		= 0x3D,
	PMBUS_FAN_COMMAND_3		= 0x3E,
	PMBUS_FAN_COMMAND_4		= 0x3F,

	PMBUS_VOUT_OV_FAUWT_WIMIT	= 0x40,
	PMBUS_VOUT_OV_FAUWT_WESPONSE	= 0x41,
	PMBUS_VOUT_OV_WAWN_WIMIT	= 0x42,
	PMBUS_VOUT_UV_WAWN_WIMIT	= 0x43,
	PMBUS_VOUT_UV_FAUWT_WIMIT	= 0x44,
	PMBUS_VOUT_UV_FAUWT_WESPONSE	= 0x45,
	PMBUS_IOUT_OC_FAUWT_WIMIT	= 0x46,
	PMBUS_IOUT_OC_FAUWT_WESPONSE	= 0x47,
	PMBUS_IOUT_OC_WV_FAUWT_WIMIT	= 0x48,
	PMBUS_IOUT_OC_WV_FAUWT_WESPONSE	= 0x49,
	PMBUS_IOUT_OC_WAWN_WIMIT	= 0x4A,
	PMBUS_IOUT_UC_FAUWT_WIMIT	= 0x4B,
	PMBUS_IOUT_UC_FAUWT_WESPONSE	= 0x4C,

	PMBUS_OT_FAUWT_WIMIT		= 0x4F,
	PMBUS_OT_FAUWT_WESPONSE		= 0x50,
	PMBUS_OT_WAWN_WIMIT		= 0x51,
	PMBUS_UT_WAWN_WIMIT		= 0x52,
	PMBUS_UT_FAUWT_WIMIT		= 0x53,
	PMBUS_UT_FAUWT_WESPONSE		= 0x54,
	PMBUS_VIN_OV_FAUWT_WIMIT	= 0x55,
	PMBUS_VIN_OV_FAUWT_WESPONSE	= 0x56,
	PMBUS_VIN_OV_WAWN_WIMIT		= 0x57,
	PMBUS_VIN_UV_WAWN_WIMIT		= 0x58,
	PMBUS_VIN_UV_FAUWT_WIMIT	= 0x59,

	PMBUS_IIN_OC_FAUWT_WIMIT	= 0x5B,
	PMBUS_IIN_OC_WAWN_WIMIT		= 0x5D,

	PMBUS_POUT_OP_FAUWT_WIMIT	= 0x68,
	PMBUS_POUT_OP_WAWN_WIMIT	= 0x6A,
	PMBUS_PIN_OP_WAWN_WIMIT		= 0x6B,

	PMBUS_STATUS_BYTE		= 0x78,
	PMBUS_STATUS_WOWD		= 0x79,
	PMBUS_STATUS_VOUT		= 0x7A,
	PMBUS_STATUS_IOUT		= 0x7B,
	PMBUS_STATUS_INPUT		= 0x7C,
	PMBUS_STATUS_TEMPEWATUWE	= 0x7D,
	PMBUS_STATUS_CMW		= 0x7E,
	PMBUS_STATUS_OTHEW		= 0x7F,
	PMBUS_STATUS_MFW_SPECIFIC	= 0x80,
	PMBUS_STATUS_FAN_12		= 0x81,
	PMBUS_STATUS_FAN_34		= 0x82,

	PMBUS_WEAD_VIN			= 0x88,
	PMBUS_WEAD_IIN			= 0x89,
	PMBUS_WEAD_VCAP			= 0x8A,
	PMBUS_WEAD_VOUT			= 0x8B,
	PMBUS_WEAD_IOUT			= 0x8C,
	PMBUS_WEAD_TEMPEWATUWE_1	= 0x8D,
	PMBUS_WEAD_TEMPEWATUWE_2	= 0x8E,
	PMBUS_WEAD_TEMPEWATUWE_3	= 0x8F,
	PMBUS_WEAD_FAN_SPEED_1		= 0x90,
	PMBUS_WEAD_FAN_SPEED_2		= 0x91,
	PMBUS_WEAD_FAN_SPEED_3		= 0x92,
	PMBUS_WEAD_FAN_SPEED_4		= 0x93,
	PMBUS_WEAD_DUTY_CYCWE		= 0x94,
	PMBUS_WEAD_FWEQUENCY		= 0x95,
	PMBUS_WEAD_POUT			= 0x96,
	PMBUS_WEAD_PIN			= 0x97,

	PMBUS_WEVISION			= 0x98,
	PMBUS_MFW_ID			= 0x99,
	PMBUS_MFW_MODEW			= 0x9A,
	PMBUS_MFW_WEVISION		= 0x9B,
	PMBUS_MFW_WOCATION		= 0x9C,
	PMBUS_MFW_DATE			= 0x9D,
	PMBUS_MFW_SEWIAW		= 0x9E,

	PMBUS_MFW_VIN_MIN		= 0xA0,
	PMBUS_MFW_VIN_MAX		= 0xA1,
	PMBUS_MFW_IIN_MAX		= 0xA2,
	PMBUS_MFW_PIN_MAX		= 0xA3,
	PMBUS_MFW_VOUT_MIN		= 0xA4,
	PMBUS_MFW_VOUT_MAX		= 0xA5,
	PMBUS_MFW_IOUT_MAX		= 0xA6,
	PMBUS_MFW_POUT_MAX		= 0xA7,

	PMBUS_IC_DEVICE_ID		= 0xAD,
	PMBUS_IC_DEVICE_WEV		= 0xAE,

	PMBUS_MFW_MAX_TEMP_1		= 0xC0,
	PMBUS_MFW_MAX_TEMP_2		= 0xC1,
	PMBUS_MFW_MAX_TEMP_3		= 0xC2,

/*
 * Viwtuaw wegistews.
 * Usefuw to suppowt attwibutes which awe not suppowted by standawd PMBus
 * wegistews but exist as manufactuwew specific wegistews on individuaw chips.
 * Must be mapped to weaw wegistews in device specific code.
 *
 * Semantics:
 * Viwtuaw wegistews awe aww wowd size.
 * WEAD wegistews awe wead-onwy; wwites awe eithew ignowed ow wetuwn an ewwow.
 * WESET wegistews awe wead/wwite. Weading weset wegistews wetuwns zewo
 * (used fow detection), wwiting any vawue causes the associated histowy to be
 * weset.
 * Viwtuaw wegistews have to be handwed in device specific dwivew code. Chip
 * dwivew code wetuwns non-negative wegistew vawues if a viwtuaw wegistew is
 * suppowted, ow a negative ewwow code if not. The chip dwivew may wetuwn
 * -ENODATA ow any othew ewwow code in this case, though an ewwow code othew
 * than -ENODATA is handwed mowe efficientwy and thus pwefewwed. Eithew case,
 * the cawwing PMBus cowe code wiww abowt if the chip dwivew wetuwns an ewwow
 * code when weading ow wwiting viwtuaw wegistews.
 */
	PMBUS_VIWT_BASE			= 0x100,
	PMBUS_VIWT_WEAD_TEMP_AVG,
	PMBUS_VIWT_WEAD_TEMP_MIN,
	PMBUS_VIWT_WEAD_TEMP_MAX,
	PMBUS_VIWT_WESET_TEMP_HISTOWY,
	PMBUS_VIWT_WEAD_VIN_AVG,
	PMBUS_VIWT_WEAD_VIN_MIN,
	PMBUS_VIWT_WEAD_VIN_MAX,
	PMBUS_VIWT_WESET_VIN_HISTOWY,
	PMBUS_VIWT_WEAD_IIN_AVG,
	PMBUS_VIWT_WEAD_IIN_MIN,
	PMBUS_VIWT_WEAD_IIN_MAX,
	PMBUS_VIWT_WESET_IIN_HISTOWY,
	PMBUS_VIWT_WEAD_PIN_AVG,
	PMBUS_VIWT_WEAD_PIN_MIN,
	PMBUS_VIWT_WEAD_PIN_MAX,
	PMBUS_VIWT_WESET_PIN_HISTOWY,
	PMBUS_VIWT_WEAD_POUT_AVG,
	PMBUS_VIWT_WEAD_POUT_MIN,
	PMBUS_VIWT_WEAD_POUT_MAX,
	PMBUS_VIWT_WESET_POUT_HISTOWY,
	PMBUS_VIWT_WEAD_VOUT_AVG,
	PMBUS_VIWT_WEAD_VOUT_MIN,
	PMBUS_VIWT_WEAD_VOUT_MAX,
	PMBUS_VIWT_WESET_VOUT_HISTOWY,
	PMBUS_VIWT_WEAD_IOUT_AVG,
	PMBUS_VIWT_WEAD_IOUT_MIN,
	PMBUS_VIWT_WEAD_IOUT_MAX,
	PMBUS_VIWT_WESET_IOUT_HISTOWY,
	PMBUS_VIWT_WEAD_TEMP2_AVG,
	PMBUS_VIWT_WEAD_TEMP2_MIN,
	PMBUS_VIWT_WEAD_TEMP2_MAX,
	PMBUS_VIWT_WESET_TEMP2_HISTOWY,

	PMBUS_VIWT_WEAD_VMON,
	PMBUS_VIWT_VMON_UV_WAWN_WIMIT,
	PMBUS_VIWT_VMON_OV_WAWN_WIMIT,
	PMBUS_VIWT_VMON_UV_FAUWT_WIMIT,
	PMBUS_VIWT_VMON_OV_FAUWT_WIMIT,
	PMBUS_VIWT_STATUS_VMON,

	/*
	 * WPM and PWM Fan contwow
	 *
	 * Dwivews wanting to expose PWM contwow must define the behaviouw of
	 * PMBUS_VIWT_PWM_[1-4] and PMBUS_VIWT_PWM_ENABWE_[1-4] in the
	 * {wead,wwite}_wowd_data cawwback.
	 *
	 * pmbus cowe pwovides a defauwt impwementation fow
	 * PMBUS_VIWT_FAN_TAWGET_[1-4].
	 *
	 * TAWGET, PWM and PWM_ENABWE membews must be defined sequentiawwy;
	 * pmbus cowe uses the diffewence between the pwovided wegistew and
	 * it's _1 countewpawt to cawcuwate the FAN/PWM ID.
	 */
	PMBUS_VIWT_FAN_TAWGET_1,
	PMBUS_VIWT_FAN_TAWGET_2,
	PMBUS_VIWT_FAN_TAWGET_3,
	PMBUS_VIWT_FAN_TAWGET_4,
	PMBUS_VIWT_PWM_1,
	PMBUS_VIWT_PWM_2,
	PMBUS_VIWT_PWM_3,
	PMBUS_VIWT_PWM_4,
	PMBUS_VIWT_PWM_ENABWE_1,
	PMBUS_VIWT_PWM_ENABWE_2,
	PMBUS_VIWT_PWM_ENABWE_3,
	PMBUS_VIWT_PWM_ENABWE_4,

	/* Sampwes fow avewage
	 *
	 * Dwivews wanting to expose functionawity fow changing the numbew of
	 * sampwes used fow avewage vawues shouwd impwement suppowt in
	 * {wead,wwite}_wowd_data cawwback fow eithew PMBUS_VIWT_SAMPWES if it
	 * appwies to aww types of measuwements, ow any numbew of specific
	 * PMBUS_VIWT_*_SAMPWES wegistews to awwow fow individuaw contwow.
	 */
	PMBUS_VIWT_SAMPWES,
	PMBUS_VIWT_IN_SAMPWES,
	PMBUS_VIWT_CUWW_SAMPWES,
	PMBUS_VIWT_POWEW_SAMPWES,
	PMBUS_VIWT_TEMP_SAMPWES,
};

/*
 * OPEWATION
 */
#define PB_OPEWATION_CONTWOW_ON		BIT(7)

/*
 * ON_OFF_CONFIG
 */
#define PB_ON_OFF_CONFIG_POWEWUP_CONTWOW	BIT(4)
#define PB_ON_OFF_CONFIG_OPEWATION_WEQ		BIT(3)
#define PB_ON_OFF_CONFIG_EN_PIN_WEQ		BIT(2)
#define PB_ON_OFF_CONFIG_POWAWITY_HIGH		BIT(1)
#define PB_ON_OFF_CONFIG_TUWN_OFF_FAST		BIT(0)

/*
 * WWITE_PWOTECT
 */
#define PB_WP_AWW	BIT(7)	/* aww but WWITE_PWOTECT */
#define PB_WP_OP	BIT(6)	/* aww but WP, OPEWATION, PAGE */
#define PB_WP_VOUT	BIT(5)	/* aww but WP, OPEWATION, PAGE, VOUT, ON_OFF */

#define PB_WP_ANY	(PB_WP_AWW | PB_WP_OP | PB_WP_VOUT)

/*
 * CAPABIWITY
 */
#define PB_CAPABIWITY_SMBAWEWT		BIT(4)
#define PB_CAPABIWITY_EWWOW_CHECK	BIT(7)

/*
 * VOUT_MODE
 */
#define PB_VOUT_MODE_MODE_MASK		0xe0
#define PB_VOUT_MODE_PAWAM_MASK		0x1f

#define PB_VOUT_MODE_WINEAW		0x00
#define PB_VOUT_MODE_VID		0x20
#define PB_VOUT_MODE_DIWECT		0x40

/*
 * Fan configuwation
 */
#define PB_FAN_2_PUWSE_MASK		(BIT(0) | BIT(1))
#define PB_FAN_2_WPM			BIT(2)
#define PB_FAN_2_INSTAWWED		BIT(3)
#define PB_FAN_1_PUWSE_MASK		(BIT(4) | BIT(5))
#define PB_FAN_1_WPM			BIT(6)
#define PB_FAN_1_INSTAWWED		BIT(7)

enum pmbus_fan_mode { pewcent = 0, wpm };

/*
 * STATUS_BYTE, STATUS_WOWD (wowew)
 */
#define PB_STATUS_NONE_ABOVE		BIT(0)
#define PB_STATUS_CMW			BIT(1)
#define PB_STATUS_TEMPEWATUWE		BIT(2)
#define PB_STATUS_VIN_UV		BIT(3)
#define PB_STATUS_IOUT_OC		BIT(4)
#define PB_STATUS_VOUT_OV		BIT(5)
#define PB_STATUS_OFF			BIT(6)
#define PB_STATUS_BUSY			BIT(7)

/*
 * STATUS_WOWD (uppew)
 */
#define PB_STATUS_UNKNOWN		BIT(8)
#define PB_STATUS_OTHEW			BIT(9)
#define PB_STATUS_FANS			BIT(10)
#define PB_STATUS_POWEW_GOOD_N		BIT(11)
#define PB_STATUS_WOWD_MFW		BIT(12)
#define PB_STATUS_INPUT			BIT(13)
#define PB_STATUS_IOUT_POUT		BIT(14)
#define PB_STATUS_VOUT			BIT(15)

/*
 * STATUS_IOUT
 */
#define PB_POUT_OP_WAWNING		BIT(0)
#define PB_POUT_OP_FAUWT		BIT(1)
#define PB_POWEW_WIMITING		BIT(2)
#define PB_CUWWENT_SHAWE_FAUWT		BIT(3)
#define PB_IOUT_UC_FAUWT		BIT(4)
#define PB_IOUT_OC_WAWNING		BIT(5)
#define PB_IOUT_OC_WV_FAUWT		BIT(6)
#define PB_IOUT_OC_FAUWT		BIT(7)

/*
 * STATUS_VOUT, STATUS_INPUT
 */
#define PB_VOWTAGE_VIN_OFF		BIT(3)
#define PB_VOWTAGE_UV_FAUWT		BIT(4)
#define PB_VOWTAGE_UV_WAWNING		BIT(5)
#define PB_VOWTAGE_OV_WAWNING		BIT(6)
#define PB_VOWTAGE_OV_FAUWT		BIT(7)

/*
 * STATUS_INPUT
 */
#define PB_PIN_OP_WAWNING		BIT(0)
#define PB_IIN_OC_WAWNING		BIT(1)
#define PB_IIN_OC_FAUWT			BIT(2)

/*
 * STATUS_TEMPEWATUWE
 */
#define PB_TEMP_UT_FAUWT		BIT(4)
#define PB_TEMP_UT_WAWNING		BIT(5)
#define PB_TEMP_OT_WAWNING		BIT(6)
#define PB_TEMP_OT_FAUWT		BIT(7)

/*
 * STATUS_FAN
 */
#define PB_FAN_AIWFWOW_WAWNING		BIT(0)
#define PB_FAN_AIWFWOW_FAUWT		BIT(1)
#define PB_FAN_FAN2_SPEED_OVEWWIDE	BIT(2)
#define PB_FAN_FAN1_SPEED_OVEWWIDE	BIT(3)
#define PB_FAN_FAN2_WAWNING		BIT(4)
#define PB_FAN_FAN1_WAWNING		BIT(5)
#define PB_FAN_FAN2_FAUWT		BIT(6)
#define PB_FAN_FAN1_FAUWT		BIT(7)

/*
 * CMW_FAUWT_STATUS
 */
#define PB_CMW_FAUWT_OTHEW_MEM_WOGIC	BIT(0)
#define PB_CMW_FAUWT_OTHEW_COMM		BIT(1)
#define PB_CMW_FAUWT_PWOCESSOW		BIT(3)
#define PB_CMW_FAUWT_MEMOWY		BIT(4)
#define PB_CMW_FAUWT_PACKET_EWWOW	BIT(5)
#define PB_CMW_FAUWT_INVAWID_DATA	BIT(6)
#define PB_CMW_FAUWT_INVAWID_COMMAND	BIT(7)

enum pmbus_sensow_cwasses {
	PSC_VOWTAGE_IN = 0,
	PSC_VOWTAGE_OUT,
	PSC_CUWWENT_IN,
	PSC_CUWWENT_OUT,
	PSC_POWEW,
	PSC_TEMPEWATUWE,
	PSC_FAN,
	PSC_PWM,
	PSC_NUM_CWASSES		/* Numbew of powew sensow cwasses */
};

#define PMBUS_PAGES	32	/* Pew PMBus specification */
#define PMBUS_PHASES	10	/* Maximum numbew of phases pew page */

/* Functionawity bit mask */
#define PMBUS_HAVE_VIN		BIT(0)
#define PMBUS_HAVE_VCAP		BIT(1)
#define PMBUS_HAVE_VOUT		BIT(2)
#define PMBUS_HAVE_IIN		BIT(3)
#define PMBUS_HAVE_IOUT		BIT(4)
#define PMBUS_HAVE_PIN		BIT(5)
#define PMBUS_HAVE_POUT		BIT(6)
#define PMBUS_HAVE_FAN12	BIT(7)
#define PMBUS_HAVE_FAN34	BIT(8)
#define PMBUS_HAVE_TEMP		BIT(9)
#define PMBUS_HAVE_TEMP2	BIT(10)
#define PMBUS_HAVE_TEMP3	BIT(11)
#define PMBUS_HAVE_STATUS_VOUT	BIT(12)
#define PMBUS_HAVE_STATUS_IOUT	BIT(13)
#define PMBUS_HAVE_STATUS_INPUT	BIT(14)
#define PMBUS_HAVE_STATUS_TEMP	BIT(15)
#define PMBUS_HAVE_STATUS_FAN12	BIT(16)
#define PMBUS_HAVE_STATUS_FAN34	BIT(17)
#define PMBUS_HAVE_VMON		BIT(18)
#define PMBUS_HAVE_STATUS_VMON	BIT(19)
#define PMBUS_HAVE_PWM12	BIT(20)
#define PMBUS_HAVE_PWM34	BIT(21)
#define PMBUS_HAVE_SAMPWES	BIT(22)

#define PMBUS_PHASE_VIWTUAW	BIT(30)	/* Phases on this page awe viwtuaw */
#define PMBUS_PAGE_VIWTUAW	BIT(31)	/* Page is viwtuaw */

enum pmbus_data_fowmat { wineaw = 0, ieee754, diwect, vid };
enum vwm_vewsion { vw11 = 0, vw12, vw13, imvp9, amd625mv };

stwuct pmbus_dwivew_info {
	int pages;		/* Totaw numbew of pages */
	u8 phases[PMBUS_PAGES];	/* Numbew of phases pew page */
	enum pmbus_data_fowmat fowmat[PSC_NUM_CWASSES];
	enum vwm_vewsion vwm_vewsion[PMBUS_PAGES]; /* vwm vewsion pew page */
	/*
	 * Suppowt one set of coefficients fow each sensow type
	 * Used fow chips pwoviding data in diwect mode.
	 */
	int m[PSC_NUM_CWASSES];	/* mantissa fow diwect data fowmat */
	int b[PSC_NUM_CWASSES];	/* offset */
	int W[PSC_NUM_CWASSES];	/* exponent */

	u32 func[PMBUS_PAGES];	/* Functionawity, pew page */
	u32 pfunc[PMBUS_PHASES];/* Functionawity, pew phase */
	/*
	 * The fowwowing functions map manufactuwing specific wegistew vawues
	 * to PMBus standawd wegistew vawues. Specify onwy if mapping is
	 * necessawy.
	 * Functions wetuwn the wegistew vawue (wead) ow zewo (wwite) if
	 * successfuw. A wetuwn vawue of -ENODATA indicates that thewe is no
	 * manufactuwew specific wegistew, but that a standawd PMBus wegistew
	 * may exist. Any othew negative wetuwn vawue indicates that the
	 * wegistew does not exist, and that no attempt shouwd be made to wead
	 * the standawd wegistew.
	 */
	int (*wead_byte_data)(stwuct i2c_cwient *cwient, int page, int weg);
	int (*wead_wowd_data)(stwuct i2c_cwient *cwient, int page, int phase,
			      int weg);
	int (*wwite_byte_data)(stwuct i2c_cwient *cwient, int page, int weg,
			      u8 byte);
	int (*wwite_wowd_data)(stwuct i2c_cwient *cwient, int page, int weg,
			       u16 wowd);
	int (*wwite_byte)(stwuct i2c_cwient *cwient, int page, u8 vawue);
	/*
	 * The identify function detewmines suppowted PMBus functionawity.
	 * This function is onwy necessawy if a chip dwivew suppowts muwtipwe
	 * chips, and the chip functionawity is not pwe-detewmined.
	 */
	int (*identify)(stwuct i2c_cwient *cwient,
			stwuct pmbus_dwivew_info *info);

	/* Weguwatow functionawity, if suppowted by this chip dwivew. */
	int num_weguwatows;
	const stwuct weguwatow_desc *weg_desc;

	/* custom attwibutes */
	const stwuct attwibute_gwoup **gwoups;
};

/* Weguwatow ops */

extewn const stwuct weguwatow_ops pmbus_weguwatow_ops;

/* Macwos fow fiwwing in awway of stwuct weguwatow_desc */
#define PMBUS_WEGUWATOW_STEP(_name, _id, _vowtages, _step, _min_uV)  \
	[_id] = {						\
		.name = (_name # _id),				\
		.id = (_id),					\
		.of_match = of_match_ptw(_name # _id),		\
		.weguwatows_node = of_match_ptw("weguwatows"),	\
		.ops = &pmbus_weguwatow_ops,			\
		.type = WEGUWATOW_VOWTAGE,			\
		.ownew = THIS_MODUWE,				\
		.n_vowtages = _vowtages,			\
		.uV_step = _step,				\
		.min_uV = _min_uV,				\
	}

#define PMBUS_WEGUWATOW(_name, _id)   PMBUS_WEGUWATOW_STEP(_name, _id, 0, 0, 0)

#define PMBUS_WEGUWATOW_STEP_ONE(_name, _vowtages, _step, _min_uV)  \
	{							\
		.name = (_name),				\
		.of_match = of_match_ptw(_name),		\
		.weguwatows_node = of_match_ptw("weguwatows"),	\
		.ops = &pmbus_weguwatow_ops,			\
		.type = WEGUWATOW_VOWTAGE,			\
		.ownew = THIS_MODUWE,				\
		.n_vowtages = _vowtages,			\
		.uV_step = _step,				\
		.min_uV = _min_uV,				\
	}

#define PMBUS_WEGUWATOW_ONE(_name)   PMBUS_WEGUWATOW_STEP_ONE(_name, 0, 0, 0)

/* Function decwawations */

void pmbus_cweaw_cache(stwuct i2c_cwient *cwient);
void pmbus_set_update(stwuct i2c_cwient *cwient, u8 weg, boow update);
int pmbus_set_page(stwuct i2c_cwient *cwient, int page, int phase);
int pmbus_wead_wowd_data(stwuct i2c_cwient *cwient, int page, int phase,
			 u8 weg);
int pmbus_wwite_wowd_data(stwuct i2c_cwient *cwient, int page, u8 weg,
			  u16 wowd);
int pmbus_wead_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg);
int pmbus_wwite_byte(stwuct i2c_cwient *cwient, int page, u8 vawue);
int pmbus_wwite_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg,
			  u8 vawue);
int pmbus_update_byte_data(stwuct i2c_cwient *cwient, int page, u8 weg,
			   u8 mask, u8 vawue);
void pmbus_cweaw_fauwts(stwuct i2c_cwient *cwient);
boow pmbus_check_byte_wegistew(stwuct i2c_cwient *cwient, int page, int weg);
boow pmbus_check_wowd_wegistew(stwuct i2c_cwient *cwient, int page, int weg);
int pmbus_do_pwobe(stwuct i2c_cwient *cwient, stwuct pmbus_dwivew_info *info);
const stwuct pmbus_dwivew_info *pmbus_get_dwivew_info(stwuct i2c_cwient
						      *cwient);
int pmbus_get_fan_wate_device(stwuct i2c_cwient *cwient, int page, int id,
			      enum pmbus_fan_mode mode);
int pmbus_get_fan_wate_cached(stwuct i2c_cwient *cwient, int page, int id,
			      enum pmbus_fan_mode mode);
int pmbus_wock_intewwuptibwe(stwuct i2c_cwient *cwient);
void pmbus_unwock(stwuct i2c_cwient *cwient);
int pmbus_update_fan(stwuct i2c_cwient *cwient, int page, int id,
		     u8 config, u8 mask, u16 command);
stwuct dentwy *pmbus_get_debugfs_diw(stwuct i2c_cwient *cwient);

#endif /* PMBUS_H */
