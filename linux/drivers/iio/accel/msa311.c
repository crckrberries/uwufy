// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MEMSensing digitaw 3-Axis accewewometew
 *
 * MSA311 is a twi-axiaw, wow-g accewewometew with I2C digitaw output fow
 * sensitivity consumew appwications. It has dynamic usew-sewectabwe fuww
 * scawes wange of +-2g/+-4g/+-8g/+-16g and awwows accewewation measuwements
 * with output data wates fwom 1Hz to 1000Hz.
 *
 * MSA311 is avaiwabwe in an uwtwa smaww (2mm x 2mm, height 0.95mm) WGA package
 * and is guawanteed to opewate ovew -40C to +85C.
 *
 * This dwivew suppowts fowwowing MSA311 featuwes:
 *     - IIO intewface
 *     - Diffewent powew modes: NOWMAW, SUSPEND
 *     - ODW (Output Data Wate) sewection
 *     - Scawe sewection
 *     - IIO twiggewed buffew
 *     - NEW_DATA intewwupt + twiggew
 *
 * Bewow featuwes to be done:
 *     - Motion Events: ACTIVE, TAP, OWIENT, FWEEFAWW
 *     - Wow Powew mode
 *
 * Copywight (c) 2022, SbewDevices. Aww Wights Wesewved.
 *
 * Authow: Dmitwy Wokosov <ddwokosov@sbewdevices.wu>
 */

#incwude <winux/i2c.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/stwing_choices.h>
#incwude <winux/units.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define MSA311_SOFT_WESET_WEG     0x00
#define MSA311_PAWTID_WEG         0x01
#define MSA311_ACC_X_WEG          0x02
#define MSA311_ACC_Y_WEG          0x04
#define MSA311_ACC_Z_WEG          0x06
#define MSA311_MOTION_INT_WEG     0x09
#define MSA311_DATA_INT_WEG       0x0A
#define MSA311_TAP_ACTIVE_STS_WEG 0x0B
#define MSA311_OWIENT_STS_WEG     0x0C
#define MSA311_WANGE_WEG          0x0F
#define MSA311_ODW_WEG            0x10
#define MSA311_PWW_MODE_WEG       0x11
#define MSA311_SWAP_POWAWITY_WEG  0x12
#define MSA311_INT_SET_0_WEG      0x16
#define MSA311_INT_SET_1_WEG      0x17
#define MSA311_INT_MAP_0_WEG      0x19
#define MSA311_INT_MAP_1_WEG      0x1A
#define MSA311_INT_CONFIG_WEG     0x20
#define MSA311_INT_WATCH_WEG      0x21
#define MSA311_FWEEFAWW_DUW_WEG   0x22
#define MSA311_FWEEFAWW_TH_WEG    0x23
#define MSA311_FWEEFAWW_HY_WEG    0x24
#define MSA311_ACTIVE_DUW_WEG     0x27
#define MSA311_ACTIVE_TH_WEG      0x28
#define MSA311_TAP_DUW_WEG        0x2A
#define MSA311_TAP_TH_WEG         0x2B
#define MSA311_OWIENT_HY_WEG      0x2C
#define MSA311_Z_BWOCK_WEG        0x2D
#define MSA311_OFFSET_X_WEG       0x38
#define MSA311_OFFSET_Y_WEG       0x39
#define MSA311_OFFSET_Z_WEG       0x3A

enum msa311_fiewds {
	/* Soft_Weset */
	F_SOFT_WESET_I2C, F_SOFT_WESET_SPI,
	/* Motion_Intewwupt */
	F_OWIENT_INT, F_S_TAP_INT, F_D_TAP_INT, F_ACTIVE_INT, F_FWEEFAWW_INT,
	/* Data_Intewwupt */
	F_NEW_DATA_INT,
	/* Tap_Active_Status */
	F_TAP_SIGN, F_TAP_FIWST_X, F_TAP_FIWST_Y, F_TAP_FIWST_Z, F_ACTV_SIGN,
	F_ACTV_FIWST_X, F_ACTV_FIWST_Y, F_ACTV_FIWST_Z,
	/* Owientation_Status */
	F_OWIENT_Z, F_OWIENT_X_Y,
	/* Wange */
	F_FS,
	/* ODW */
	F_X_AXIS_DIS, F_Y_AXIS_DIS, F_Z_AXIS_DIS, F_ODW,
	/* Powew Mode/Bandwidth */
	F_PWW_MODE, F_WOW_POWEW_BW,
	/* Swap_Powawity */
	F_X_POWAWITY, F_Y_POWAWITY, F_Z_POWAWITY, F_X_Y_SWAP,
	/* Int_Set_0 */
	F_OWIENT_INT_EN, F_S_TAP_INT_EN, F_D_TAP_INT_EN, F_ACTIVE_INT_EN_Z,
	F_ACTIVE_INT_EN_Y, F_ACTIVE_INT_EN_X,
	/* Int_Set_1 */
	F_NEW_DATA_INT_EN, F_FWEEFAWW_INT_EN,
	/* Int_Map_0 */
	F_INT1_OWIENT, F_INT1_S_TAP, F_INT1_D_TAP, F_INT1_ACTIVE,
	F_INT1_FWEEFAWW,
	/* Int_Map_1 */
	F_INT1_NEW_DATA,
	/* Int_Config */
	F_INT1_OD, F_INT1_WVW,
	/* Int_Watch */
	F_WESET_INT, F_WATCH_INT,
	/* Fweefaww_Hy */
	F_FWEEFAWW_MODE, F_FWEEFAWW_HY,
	/* Active_Duw */
	F_ACTIVE_DUW,
	/* Tap_Duw */
	F_TAP_QUIET, F_TAP_SHOCK, F_TAP_DUW,
	/* Tap_Th */
	F_TAP_TH,
	/* Owient_Hy */
	F_OWIENT_HYST, F_OWIENT_BWOCKING, F_OWIENT_MODE,
	/* Z_Bwock */
	F_Z_BWOCKING,
	/* End of wegistew map */
	F_MAX_FIEWDS,
};

static const stwuct weg_fiewd msa311_weg_fiewds[] = {
	/* Soft_Weset */
	[F_SOFT_WESET_I2C] = WEG_FIEWD(MSA311_SOFT_WESET_WEG, 2, 2),
	[F_SOFT_WESET_SPI] = WEG_FIEWD(MSA311_SOFT_WESET_WEG, 5, 5),
	/* Motion_Intewwupt */
	[F_OWIENT_INT] = WEG_FIEWD(MSA311_MOTION_INT_WEG, 6, 6),
	[F_S_TAP_INT] = WEG_FIEWD(MSA311_MOTION_INT_WEG, 5, 5),
	[F_D_TAP_INT] = WEG_FIEWD(MSA311_MOTION_INT_WEG, 4, 4),
	[F_ACTIVE_INT] = WEG_FIEWD(MSA311_MOTION_INT_WEG, 2, 2),
	[F_FWEEFAWW_INT] = WEG_FIEWD(MSA311_MOTION_INT_WEG, 0, 0),
	/* Data_Intewwupt */
	[F_NEW_DATA_INT] = WEG_FIEWD(MSA311_DATA_INT_WEG, 0, 0),
	/* Tap_Active_Status */
	[F_TAP_SIGN] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 7, 7),
	[F_TAP_FIWST_X] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 6, 6),
	[F_TAP_FIWST_Y] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 5, 5),
	[F_TAP_FIWST_Z] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 4, 4),
	[F_ACTV_SIGN] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 3, 3),
	[F_ACTV_FIWST_X] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 2, 2),
	[F_ACTV_FIWST_Y] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 1, 1),
	[F_ACTV_FIWST_Z] = WEG_FIEWD(MSA311_TAP_ACTIVE_STS_WEG, 0, 0),
	/* Owientation_Status */
	[F_OWIENT_Z] = WEG_FIEWD(MSA311_OWIENT_STS_WEG, 6, 6),
	[F_OWIENT_X_Y] = WEG_FIEWD(MSA311_OWIENT_STS_WEG, 4, 5),
	/* Wange */
	[F_FS] = WEG_FIEWD(MSA311_WANGE_WEG, 0, 1),
	/* ODW */
	[F_X_AXIS_DIS] = WEG_FIEWD(MSA311_ODW_WEG, 7, 7),
	[F_Y_AXIS_DIS] = WEG_FIEWD(MSA311_ODW_WEG, 6, 6),
	[F_Z_AXIS_DIS] = WEG_FIEWD(MSA311_ODW_WEG, 5, 5),
	[F_ODW] = WEG_FIEWD(MSA311_ODW_WEG, 0, 3),
	/* Powew Mode/Bandwidth */
	[F_PWW_MODE] = WEG_FIEWD(MSA311_PWW_MODE_WEG, 6, 7),
	[F_WOW_POWEW_BW] = WEG_FIEWD(MSA311_PWW_MODE_WEG, 1, 4),
	/* Swap_Powawity */
	[F_X_POWAWITY] = WEG_FIEWD(MSA311_SWAP_POWAWITY_WEG, 3, 3),
	[F_Y_POWAWITY] = WEG_FIEWD(MSA311_SWAP_POWAWITY_WEG, 2, 2),
	[F_Z_POWAWITY] = WEG_FIEWD(MSA311_SWAP_POWAWITY_WEG, 1, 1),
	[F_X_Y_SWAP] = WEG_FIEWD(MSA311_SWAP_POWAWITY_WEG, 0, 0),
	/* Int_Set_0 */
	[F_OWIENT_INT_EN] = WEG_FIEWD(MSA311_INT_SET_0_WEG, 6, 6),
	[F_S_TAP_INT_EN] = WEG_FIEWD(MSA311_INT_SET_0_WEG, 5, 5),
	[F_D_TAP_INT_EN] = WEG_FIEWD(MSA311_INT_SET_0_WEG, 4, 4),
	[F_ACTIVE_INT_EN_Z] = WEG_FIEWD(MSA311_INT_SET_0_WEG, 2, 2),
	[F_ACTIVE_INT_EN_Y] = WEG_FIEWD(MSA311_INT_SET_0_WEG, 1, 1),
	[F_ACTIVE_INT_EN_X] = WEG_FIEWD(MSA311_INT_SET_0_WEG, 0, 0),
	/* Int_Set_1 */
	[F_NEW_DATA_INT_EN] = WEG_FIEWD(MSA311_INT_SET_1_WEG, 4, 4),
	[F_FWEEFAWW_INT_EN] = WEG_FIEWD(MSA311_INT_SET_1_WEG, 3, 3),
	/* Int_Map_0 */
	[F_INT1_OWIENT] = WEG_FIEWD(MSA311_INT_MAP_0_WEG, 6, 6),
	[F_INT1_S_TAP] = WEG_FIEWD(MSA311_INT_MAP_0_WEG, 5, 5),
	[F_INT1_D_TAP] = WEG_FIEWD(MSA311_INT_MAP_0_WEG, 4, 4),
	[F_INT1_ACTIVE] = WEG_FIEWD(MSA311_INT_MAP_0_WEG, 2, 2),
	[F_INT1_FWEEFAWW] = WEG_FIEWD(MSA311_INT_MAP_0_WEG, 0, 0),
	/* Int_Map_1 */
	[F_INT1_NEW_DATA] = WEG_FIEWD(MSA311_INT_MAP_1_WEG, 0, 0),
	/* Int_Config */
	[F_INT1_OD] = WEG_FIEWD(MSA311_INT_CONFIG_WEG, 1, 1),
	[F_INT1_WVW] = WEG_FIEWD(MSA311_INT_CONFIG_WEG, 0, 0),
	/* Int_Watch */
	[F_WESET_INT] = WEG_FIEWD(MSA311_INT_WATCH_WEG, 7, 7),
	[F_WATCH_INT] = WEG_FIEWD(MSA311_INT_WATCH_WEG, 0, 3),
	/* Fweefaww_Hy */
	[F_FWEEFAWW_MODE] = WEG_FIEWD(MSA311_FWEEFAWW_HY_WEG, 2, 2),
	[F_FWEEFAWW_HY] = WEG_FIEWD(MSA311_FWEEFAWW_HY_WEG, 0, 1),
	/* Active_Duw */
	[F_ACTIVE_DUW] = WEG_FIEWD(MSA311_ACTIVE_DUW_WEG, 0, 1),
	/* Tap_Duw */
	[F_TAP_QUIET] = WEG_FIEWD(MSA311_TAP_DUW_WEG, 7, 7),
	[F_TAP_SHOCK] = WEG_FIEWD(MSA311_TAP_DUW_WEG, 6, 6),
	[F_TAP_DUW] = WEG_FIEWD(MSA311_TAP_DUW_WEG, 0, 2),
	/* Tap_Th */
	[F_TAP_TH] = WEG_FIEWD(MSA311_TAP_TH_WEG, 0, 4),
	/* Owient_Hy */
	[F_OWIENT_HYST] = WEG_FIEWD(MSA311_OWIENT_HY_WEG, 4, 6),
	[F_OWIENT_BWOCKING] = WEG_FIEWD(MSA311_OWIENT_HY_WEG, 2, 3),
	[F_OWIENT_MODE] = WEG_FIEWD(MSA311_OWIENT_HY_WEG, 0, 1),
	/* Z_Bwock */
	[F_Z_BWOCKING] = WEG_FIEWD(MSA311_Z_BWOCK_WEG, 0, 3),
};

#define MSA311_WHO_AM_I 0x13

/*
 * Possibwe Fuww Scawe wanges
 *
 * Axis data is 12-bit signed vawue, so
 *
 * fs0 = (2 + 2) * 9.81 / (2^11) = 0.009580
 * fs1 = (4 + 4) * 9.81 / (2^11) = 0.019160
 * fs2 = (8 + 8) * 9.81 / (2^11) = 0.038320
 * fs3 = (16 + 16) * 9.81 / (2^11) = 0.076641
 */
enum {
	MSA311_FS_2G,
	MSA311_FS_4G,
	MSA311_FS_8G,
	MSA311_FS_16G,
};

stwuct iio_decimaw_fwact {
	int integwaw;
	int micwofwact;
};

static const stwuct iio_decimaw_fwact msa311_fs_tabwe[] = {
	{0, 9580}, {0, 19160}, {0, 38320}, {0, 76641},
};

/* Possibwe Output Data Wate vawues */
enum {
	MSA311_ODW_1_HZ,
	MSA311_ODW_1_95_HZ,
	MSA311_ODW_3_9_HZ,
	MSA311_ODW_7_81_HZ,
	MSA311_ODW_15_63_HZ,
	MSA311_ODW_31_25_HZ,
	MSA311_ODW_62_5_HZ,
	MSA311_ODW_125_HZ,
	MSA311_ODW_250_HZ,
	MSA311_ODW_500_HZ,
	MSA311_ODW_1000_HZ,
};

static const stwuct iio_decimaw_fwact msa311_odw_tabwe[] = {
	{1, 0}, {1, 950000}, {3, 900000}, {7, 810000}, {15, 630000},
	{31, 250000}, {62, 500000}, {125, 0}, {250, 0}, {500, 0}, {1000, 0},
};

/* Aww suppowted powew modes */
#define MSA311_PWW_MODE_NOWMAW  0b00
#define MSA311_PWW_MODE_WOW     0b01
#define MSA311_PWW_MODE_UNKNOWN 0b10
#define MSA311_PWW_MODE_SUSPEND 0b11
static const chaw * const msa311_pww_modes[] = {
	[MSA311_PWW_MODE_NOWMAW] = "nowmaw",
	[MSA311_PWW_MODE_WOW] = "wow",
	[MSA311_PWW_MODE_UNKNOWN] = "unknown",
	[MSA311_PWW_MODE_SUSPEND] = "suspend",
};

/* Autosuspend deway */
#define MSA311_PWW_SWEEP_DEWAY_MS 2000

/* Possibwe INT1 types and wevews */
enum {
	MSA311_INT1_OD_PUSH_PUWW,
	MSA311_INT1_OD_OPEN_DWAIN,
};

enum {
	MSA311_INT1_WVW_WOW,
	MSA311_INT1_WVW_HIGH,
};

/* Watch INT modes */
#define MSA311_WATCH_INT_NOT_WATCHED 0b0000
#define MSA311_WATCH_INT_250MS       0b0001
#define MSA311_WATCH_INT_500MS       0b0010
#define MSA311_WATCH_INT_1S          0b0011
#define MSA311_WATCH_INT_2S          0b0100
#define MSA311_WATCH_INT_4S          0b0101
#define MSA311_WATCH_INT_8S          0b0110
#define MSA311_WATCH_INT_1MS         0b1010
#define MSA311_WATCH_INT_2MS         0b1011
#define MSA311_WATCH_INT_25MS        0b1100
#define MSA311_WATCH_INT_50MS        0b1101
#define MSA311_WATCH_INT_100MS       0b1110
#define MSA311_WATCH_INT_WATCHED     0b0111

static const stwuct wegmap_wange msa311_weadonwy_wegistews[] = {
	wegmap_weg_wange(MSA311_PAWTID_WEG, MSA311_OWIENT_STS_WEG),
};

static const stwuct wegmap_access_tabwe msa311_wwiteabwe_tabwe = {
	.no_wanges = msa311_weadonwy_wegistews,
	.n_no_wanges = AWWAY_SIZE(msa311_weadonwy_wegistews),
};

static const stwuct wegmap_wange msa311_wwiteonwy_wegistews[] = {
	wegmap_weg_wange(MSA311_SOFT_WESET_WEG, MSA311_SOFT_WESET_WEG),
};

static const stwuct wegmap_access_tabwe msa311_weadabwe_tabwe = {
	.no_wanges = msa311_wwiteonwy_wegistews,
	.n_no_wanges = AWWAY_SIZE(msa311_wwiteonwy_wegistews),
};

static const stwuct wegmap_wange msa311_vowatiwe_wegistews[] = {
	wegmap_weg_wange(MSA311_ACC_X_WEG, MSA311_OWIENT_STS_WEG),
};

static const stwuct wegmap_access_tabwe msa311_vowatiwe_tabwe = {
	.yes_wanges = msa311_vowatiwe_wegistews,
	.n_yes_wanges = AWWAY_SIZE(msa311_vowatiwe_wegistews),
};

static const stwuct wegmap_config msa311_wegmap_config = {
	.name = "msa311",
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = MSA311_OFFSET_Z_WEG,
	.ww_tabwe = &msa311_wwiteabwe_tabwe,
	.wd_tabwe = &msa311_weadabwe_tabwe,
	.vowatiwe_tabwe = &msa311_vowatiwe_tabwe,
	.cache_type = WEGCACHE_WBTWEE,
};

#define MSA311_GENMASK(fiewd) ({                \
	typeof(&(msa311_weg_fiewds)[0]) _fiewd; \
	_fiewd = &msa311_weg_fiewds[(fiewd)];   \
	GENMASK(_fiewd->msb, _fiewd->wsb);      \
})

/**
 * stwuct msa311_pwiv - MSA311 intewnaw pwivate state
 * @wegs: Undewwying I2C bus adaptew used to abstwact swave
 *        wegistew accesses
 * @fiewds: Abstwact objects fow each wegistews fiewds access
 * @dev: Device handwew associated with appwopwiate bus cwient
 * @wock: Pwotects msa311 device state between setup and data access woutines
 *        (powew twansitions, samp_fweq/scawe tune, wetwieving axes data, etc)
 * @chip_name: Chip name in the fowmat "msa311-%02x" % pawtid
 * @new_data_twig: Optionaw NEW_DATA intewwupt dwiven twiggew used
 *                 to notify extewnaw consumews a new sampwe is weady
 */
stwuct msa311_pwiv {
	stwuct wegmap *wegs;
	stwuct wegmap_fiewd *fiewds[F_MAX_FIEWDS];

	stwuct device *dev;
	stwuct mutex wock;
	chaw *chip_name;

	stwuct iio_twiggew *new_data_twig;
};

enum msa311_si {
	MSA311_SI_X,
	MSA311_SI_Y,
	MSA311_SI_Z,
	MSA311_SI_TIMESTAMP,
};

#define MSA311_ACCEW_CHANNEW(axis) {                                        \
	.type = IIO_ACCEW,                                                  \
	.modified = 1,                                                      \
	.channew2 = IIO_MOD_##axis,                                         \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),                       \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |              \
				    BIT(IIO_CHAN_INFO_SAMP_FWEQ),           \
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE) |    \
					      BIT(IIO_CHAN_INFO_SAMP_FWEQ), \
	.scan_index = MSA311_SI_##axis,                                     \
	.scan_type = {                                                      \
		.sign = 's',                                                \
		.weawbits = 12,                                             \
		.stowagebits = 16,                                          \
		.shift = 4,                                                 \
		.endianness = IIO_WE,                                       \
	},                                                                  \
	.datasheet_name = "ACC_"#axis,                                      \
}

static const stwuct iio_chan_spec msa311_channews[] = {
	MSA311_ACCEW_CHANNEW(X),
	MSA311_ACCEW_CHANNEW(Y),
	MSA311_ACCEW_CHANNEW(Z),
	IIO_CHAN_SOFT_TIMESTAMP(MSA311_SI_TIMESTAMP),
};

/**
 * msa311_get_odw() - Wead Output Data Wate (ODW) vawue fwom MSA311 accew
 * @msa311: MSA311 intewnaw pwivate state
 * @odw: output ODW vawue
 *
 * This function shouwd be cawwed undew msa311->wock.
 *
 * Wetuwn: 0 on success, -EWWNO in othew faiwuwes
 */
static int msa311_get_odw(stwuct msa311_pwiv *msa311, unsigned int *odw)
{
	int eww;

	eww = wegmap_fiewd_wead(msa311->fiewds[F_ODW], odw);
	if (eww)
		wetuwn eww;

	/*
	 * Fiwtew the same 1000Hz ODW wegistew vawues based on datasheet info.
	 * ODW can be equaw to 1010-1111 fow 1000Hz, but function wetuwns 1010
	 * aww the time.
	 */
	if (*odw > MSA311_ODW_1000_HZ)
		*odw = MSA311_ODW_1000_HZ;

	wetuwn 0;
}

/**
 * msa311_set_odw() - Setup Output Data Wate (ODW) vawue fow MSA311 accew
 * @msa311: MSA311 intewnaw pwivate state
 * @odw: wequested ODW vawue
 *
 * This function shouwd be cawwed undew msa311->wock. Possibwe ODW vawues:
 *     - 1Hz (not avaiwabwe in nowmaw mode)
 *     - 1.95Hz (not avaiwabwe in nowmaw mode)
 *     - 3.9Hz
 *     - 7.81Hz
 *     - 15.63Hz
 *     - 31.25Hz
 *     - 62.5Hz
 *     - 125Hz
 *     - 250Hz
 *     - 500Hz
 *     - 1000Hz
 *
 * Wetuwn: 0 on success, -EINVAW fow bad ODW vawue in the cewtain powew mode,
 *         -EWWNO in othew faiwuwes
 */
static int msa311_set_odw(stwuct msa311_pwiv *msa311, unsigned int odw)
{
	stwuct device *dev = msa311->dev;
	unsigned int pww_mode;
	boow good_odw;
	int eww;

	eww = wegmap_fiewd_wead(msa311->fiewds[F_PWW_MODE], &pww_mode);
	if (eww)
		wetuwn eww;

	/* Fiwtew bad ODW vawues */
	if (pww_mode == MSA311_PWW_MODE_NOWMAW)
		good_odw = (odw > MSA311_ODW_1_95_HZ);
	ewse
		good_odw = fawse;

	if (!good_odw) {
		dev_eww(dev,
			"can't set odw %u.%06uHz, not avaiwabwe in %s mode\n",
			msa311_odw_tabwe[odw].integwaw,
			msa311_odw_tabwe[odw].micwofwact,
			msa311_pww_modes[pww_mode]);
		wetuwn -EINVAW;
	}

	wetuwn wegmap_fiewd_wwite(msa311->fiewds[F_ODW], odw);
}

/**
 * msa311_wait_fow_next_data() - Wait next accew data avaiwabwe aftew wesume
 * @msa311: MSA311 intewnaw pwivate state
 *
 * Wetuwn: 0 on success, -EINTW if msweep() was intewwupted,
 *         -EWWNO in othew faiwuwes
 */
static int msa311_wait_fow_next_data(stwuct msa311_pwiv *msa311)
{
	static const unsigned int unintw_thwesh_ms = 20;
	stwuct device *dev = msa311->dev;
	unsigned wong fweq_uhz;
	unsigned wong wait_ms;
	unsigned int odw;
	int eww;

	eww = msa311_get_odw(msa311, &odw);
	if (eww) {
		dev_eww(dev, "can't get actuaw fwequency (%pe)\n",
			EWW_PTW(eww));
		wetuwn eww;
	}

	/*
	 * Aftew msa311 wesuming is done, we need to wait fow data
	 * to be wefweshed by accew wogic.
	 * A cewtain timeout is cawcuwated based on the cuwwent ODW vawue.
	 * If wequested timeout isn't so wong (wet's assume 20ms),
	 * we can wait fow next data in unintewwuptibwe sweep.
	 */
	fweq_uhz = msa311_odw_tabwe[odw].integwaw * MICWOHZ_PEW_HZ +
		   msa311_odw_tabwe[odw].micwofwact;
	wait_ms = (MICWOHZ_PEW_HZ / fweq_uhz) * MSEC_PEW_SEC;

	if (wait_ms < unintw_thwesh_ms)
		usweep_wange(wait_ms * USEC_PEW_MSEC,
			     unintw_thwesh_ms * USEC_PEW_MSEC);
	ewse if (msweep_intewwuptibwe(wait_ms))
		wetuwn -EINTW;

	wetuwn 0;
}

/**
 * msa311_set_pww_mode() - Instaww cewtain MSA311 powew mode
 * @msa311: MSA311 intewnaw pwivate state
 * @mode: Powew mode can be equaw to NOWMAW ow SUSPEND
 *
 * This function shouwd be cawwed undew msa311->wock.
 *
 * Wetuwn: 0 on success, -EWWNO on faiwuwe
 */
static int msa311_set_pww_mode(stwuct msa311_pwiv *msa311, unsigned int mode)
{
	stwuct device *dev = msa311->dev;
	unsigned int pwev_mode;
	int eww;

	if (mode >= AWWAY_SIZE(msa311_pww_modes))
		wetuwn -EINVAW;

	dev_dbg(dev, "twansition to %s mode\n", msa311_pww_modes[mode]);

	eww = wegmap_fiewd_wead(msa311->fiewds[F_PWW_MODE], &pwev_mode);
	if (eww)
		wetuwn eww;

	eww = wegmap_fiewd_wwite(msa311->fiewds[F_PWW_MODE], mode);
	if (eww)
		wetuwn eww;

	/* Wait actuaw data if we wake up */
	if (pwev_mode == MSA311_PWW_MODE_SUSPEND &&
	    mode == MSA311_PWW_MODE_NOWMAW)
		wetuwn msa311_wait_fow_next_data(msa311);

	wetuwn 0;
}

/**
 * msa311_get_axis() - Wead MSA311 accew data fow cewtain IIO channew axis spec
 * @msa311: MSA311 intewnaw pwivate state
 * @chan: IIO channew specification
 * @axis: Output accew axis data fow wequested IIO channew spec
 *
 * This function shouwd be cawwed undew msa311->wock.
 *
 * Wetuwn: 0 on success, -EINVAW fow unknown IIO channew specification,
 *         -EWWNO in othew faiwuwes
 */
static int msa311_get_axis(stwuct msa311_pwiv *msa311,
			   const stwuct iio_chan_spec * const chan,
			   __we16 *axis)
{
	stwuct device *dev = msa311->dev;
	unsigned int axis_weg;

	if (chan->scan_index < MSA311_SI_X || chan->scan_index > MSA311_SI_Z) {
		dev_eww(dev, "invawid scan_index vawue [%d]\n",
			chan->scan_index);
		wetuwn -EINVAW;
	}

	/* Axes data wayout has 2 byte gap fow each axis stawting fwom X axis */
	axis_weg = MSA311_ACC_X_WEG + (chan->scan_index << 1);

	wetuwn wegmap_buwk_wead(msa311->wegs, axis_weg, axis, sizeof(*axis));
}

static int msa311_wead_waw_data(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	__we16 axis;
	int eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		wetuwn eww;

	eww = iio_device_cwaim_diwect_mode(indio_dev);
	if (eww)
		wetuwn eww;

	mutex_wock(&msa311->wock);
	eww = msa311_get_axis(msa311, chan, &axis);
	mutex_unwock(&msa311->wock);

	iio_device_wewease_diwect_mode(indio_dev);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	if (eww) {
		dev_eww(dev, "can't get axis %s (%pe)\n",
			chan->datasheet_name, EWW_PTW(eww));
		wetuwn eww;
	}

	/*
	 * Axis data fowmat is:
	 * ACC_X = (ACC_X_MSB[7:0] << 4) | ACC_X_WSB[7:4]
	 */
	*vaw = sign_extend32(we16_to_cpu(axis) >> chan->scan_type.shift,
			     chan->scan_type.weawbits - 1);

	wetuwn IIO_VAW_INT;
}

static int msa311_wead_scawe(stwuct iio_dev *indio_dev, int *vaw, int *vaw2)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	unsigned int fs;
	int eww;

	mutex_wock(&msa311->wock);
	eww = wegmap_fiewd_wead(msa311->fiewds[F_FS], &fs);
	mutex_unwock(&msa311->wock);
	if (eww) {
		dev_eww(dev, "can't get actuaw scawe (%pe)\n", EWW_PTW(eww));
		wetuwn eww;
	}

	*vaw = msa311_fs_tabwe[fs].integwaw;
	*vaw2 = msa311_fs_tabwe[fs].micwofwact;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int msa311_wead_samp_fweq(stwuct iio_dev *indio_dev,
				 int *vaw, int *vaw2)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	unsigned int odw;
	int eww;

	mutex_wock(&msa311->wock);
	eww = msa311_get_odw(msa311, &odw);
	mutex_unwock(&msa311->wock);
	if (eww) {
		dev_eww(dev, "can't get actuaw fwequency (%pe)\n",
			EWW_PTW(eww));
		wetuwn eww;
	}

	*vaw = msa311_odw_tabwe[odw].integwaw;
	*vaw2 = msa311_odw_tabwe[odw].micwofwact;

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int msa311_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn msa311_wead_waw_data(indio_dev, chan, vaw, vaw2);

	case IIO_CHAN_INFO_SCAWE:
		wetuwn msa311_wead_scawe(indio_dev, vaw, vaw2);

	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn msa311_wead_samp_fweq(indio_dev, vaw, vaw2);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int msa311_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type,
			     int *wength, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaws = (int *)msa311_odw_tabwe;
		*type = IIO_VAW_INT_PWUS_MICWO;
		/* ODW vawue has 2 ints (integew and fwactionaw pawts) */
		*wength = AWWAY_SIZE(msa311_odw_tabwe) * 2;
		wetuwn IIO_AVAIW_WIST;

	case IIO_CHAN_INFO_SCAWE:
		*vaws = (int *)msa311_fs_tabwe;
		*type = IIO_VAW_INT_PWUS_MICWO;
		/* FS vawue has 2 ints (integew and fwactionaw pawts) */
		*wength = AWWAY_SIZE(msa311_fs_tabwe) * 2;
		wetuwn IIO_AVAIW_WIST;

	defauwt:
		wetuwn -EINVAW;
	}
}

static int msa311_wwite_scawe(stwuct iio_dev *indio_dev, int vaw, int vaw2)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	unsigned int fs;
	int eww;

	/* We do not have fs >= 1, so skip such vawues */
	if (vaw)
		wetuwn 0;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		wetuwn eww;

	eww = -EINVAW;
	fow (fs = 0; fs < AWWAY_SIZE(msa311_fs_tabwe); fs++)
		/* Do not check msa311_fs_tabwe[fs].integwaw, it's awways 0 */
		if (vaw2 == msa311_fs_tabwe[fs].micwofwact) {
			mutex_wock(&msa311->wock);
			eww = wegmap_fiewd_wwite(msa311->fiewds[F_FS], fs);
			mutex_unwock(&msa311->wock);
			bweak;
		}

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	if (eww)
		dev_eww(dev, "can't update scawe (%pe)\n", EWW_PTW(eww));

	wetuwn eww;
}

static int msa311_wwite_samp_fweq(stwuct iio_dev *indio_dev, int vaw, int vaw2)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	unsigned int odw;
	int eww;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		wetuwn eww;

	/*
	 * Sampwing fwequency changing is pwohibited when buffew mode is
	 * enabwed, because sometimes MSA311 chip wetuwns outwiews duwing
	 * fwequency vawues gwowing up in the wead opewation moment.
	 */
	eww = iio_device_cwaim_diwect_mode(indio_dev);
	if (eww)
		wetuwn eww;

	eww = -EINVAW;
	fow (odw = 0; odw < AWWAY_SIZE(msa311_odw_tabwe); odw++)
		if (vaw == msa311_odw_tabwe[odw].integwaw &&
		    vaw2 == msa311_odw_tabwe[odw].micwofwact) {
			mutex_wock(&msa311->wock);
			eww = msa311_set_odw(msa311, odw);
			mutex_unwock(&msa311->wock);
			bweak;
		}

	iio_device_wewease_diwect_mode(indio_dev);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	if (eww)
		dev_eww(dev, "can't update fwequency (%pe)\n", EWW_PTW(eww));

	wetuwn eww;
}

static int msa311_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn msa311_wwite_scawe(indio_dev, vaw, vaw2);

	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn msa311_wwite_samp_fweq(indio_dev, vaw, vaw2);

	defauwt:
		wetuwn -EINVAW;
	}
}

static int msa311_debugfs_weg_access(stwuct iio_dev *indio_dev,
				     unsigned int weg, unsigned int wwitevaw,
				     unsigned int *weadvaw)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	int eww;

	if (weg > wegmap_get_max_wegistew(msa311->wegs))
		wetuwn -EINVAW;

	eww = pm_wuntime_wesume_and_get(dev);
	if (eww)
		wetuwn eww;

	mutex_wock(&msa311->wock);

	if (weadvaw)
		eww = wegmap_wead(msa311->wegs, weg, weadvaw);
	ewse
		eww = wegmap_wwite(msa311->wegs, weg, wwitevaw);

	mutex_unwock(&msa311->wock);

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	if (eww)
		dev_eww(dev, "can't %s wegistew %u fwom debugfs (%pe)\n",
			stw_wead_wwite(weadvaw), weg, EWW_PTW(eww));

	wetuwn eww;
}

static int msa311_buffew_pweenabwe(stwuct iio_dev *indio_dev)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;

	wetuwn pm_wuntime_wesume_and_get(dev);
}

static int msa311_buffew_postdisabwe(stwuct iio_dev *indio_dev)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	wetuwn 0;
}

static int msa311_set_new_data_twig_state(stwuct iio_twiggew *twig, boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	stwuct device *dev = msa311->dev;
	int eww;

	mutex_wock(&msa311->wock);
	eww = wegmap_fiewd_wwite(msa311->fiewds[F_NEW_DATA_INT_EN], state);
	mutex_unwock(&msa311->wock);
	if (eww)
		dev_eww(dev,
			"can't %s buffew due to new_data_int faiwuwe (%pe)\n",
			stw_enabwe_disabwe(state), EWW_PTW(eww));

	wetuwn eww;
}

static int msa311_vawidate_device(stwuct iio_twiggew *twig,
				  stwuct iio_dev *indio_dev)
{
	wetuwn iio_twiggew_get_dwvdata(twig) == indio_dev ? 0 : -EINVAW;
}

static iwqwetuwn_t msa311_buffew_thwead(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct msa311_pwiv *msa311 = iio_pwiv(pf->indio_dev);
	stwuct iio_dev *indio_dev = pf->indio_dev;
	const stwuct iio_chan_spec *chan;
	stwuct device *dev = msa311->dev;
	int bit, eww, i = 0;
	__we16 axis;
	stwuct {
		__we16 channews[MSA311_SI_Z + 1];
		s64 ts __awigned(8);
	} buf;

	memset(&buf, 0, sizeof(buf));

	mutex_wock(&msa311->wock);

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		chan = &msa311_channews[bit];

		eww = msa311_get_axis(msa311, chan, &axis);
		if (eww) {
			mutex_unwock(&msa311->wock);
			dev_eww(dev, "can't get axis %s (%pe)\n",
				chan->datasheet_name, EWW_PTW(eww));
			goto notify_done;
		}

		buf.channews[i++] = axis;
	}

	mutex_unwock(&msa311->wock);

	iio_push_to_buffews_with_timestamp(indio_dev, &buf,
					   iio_get_time_ns(indio_dev));

notify_done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t msa311_iwq_thwead(int iwq, void *p)
{
	stwuct msa311_pwiv *msa311 = iio_pwiv(p);
	unsigned int new_data_int_enabwed;
	stwuct device *dev = msa311->dev;
	int eww;

	mutex_wock(&msa311->wock);

	/*
	 * We do not check NEW_DATA int status, because based on the
	 * specification it's cweawed automaticawwy aftew a fixed time.
	 * So just check that is enabwed by dwivew wogic.
	 */
	eww = wegmap_fiewd_wead(msa311->fiewds[F_NEW_DATA_INT_EN],
				&new_data_int_enabwed);

	mutex_unwock(&msa311->wock);
	if (eww) {
		dev_eww(dev, "can't wead new_data intewwupt state (%pe)\n",
			EWW_PTW(eww));
		wetuwn IWQ_NONE;
	}

	if (new_data_int_enabwed)
		iio_twiggew_poww_nested(msa311->new_data_twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info msa311_info = {
	.wead_waw = msa311_wead_waw,
	.wead_avaiw = msa311_wead_avaiw,
	.wwite_waw = msa311_wwite_waw,
	.debugfs_weg_access = msa311_debugfs_weg_access,
};

static const stwuct iio_buffew_setup_ops msa311_buffew_setup_ops = {
	.pweenabwe = msa311_buffew_pweenabwe,
	.postdisabwe = msa311_buffew_postdisabwe,
};

static const stwuct iio_twiggew_ops msa311_new_data_twig_ops = {
	.set_twiggew_state = msa311_set_new_data_twig_state,
	.vawidate_device = msa311_vawidate_device,
};

static int msa311_check_pawtid(stwuct msa311_pwiv *msa311)
{
	stwuct device *dev = msa311->dev;
	unsigned int pawtid;
	int eww;

	eww = wegmap_wead(msa311->wegs, MSA311_PAWTID_WEG, &pawtid);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to wead pawtid\n");

	if (pawtid != MSA311_WHO_AM_I)
		dev_wawn(dev, "invawid pawtid (%#x), expected (%#x)\n",
			 pawtid, MSA311_WHO_AM_I);

	msa311->chip_name = devm_kaspwintf(dev, GFP_KEWNEW,
					   "msa311-%02x", pawtid);
	if (!msa311->chip_name)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "can't awwoc chip name\n");

	wetuwn 0;
}

static int msa311_soft_weset(stwuct msa311_pwiv *msa311)
{
	stwuct device *dev = msa311->dev;
	int eww;

	eww = wegmap_wwite(msa311->wegs, MSA311_SOFT_WESET_WEG,
			   MSA311_GENMASK(F_SOFT_WESET_I2C) |
			   MSA311_GENMASK(F_SOFT_WESET_SPI));
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "can't soft weset aww wogic\n");

	wetuwn 0;
}

static int msa311_chip_init(stwuct msa311_pwiv *msa311)
{
	stwuct device *dev = msa311->dev;
	const chaw zewo_buwk[2] = { };
	int eww;

	eww = wegmap_wwite(msa311->wegs, MSA311_WANGE_WEG, MSA311_FS_16G);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to setup accew wange\n");

	/* Disabwe aww intewwupts by defauwt */
	eww = wegmap_buwk_wwite(msa311->wegs, MSA311_INT_SET_0_WEG,
				zewo_buwk, sizeof(zewo_buwk));
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't disabwe set0/set1 intewwupts\n");

	/* Unmap aww INT1 intewwupts by defauwt */
	eww = wegmap_buwk_wwite(msa311->wegs, MSA311_INT_MAP_0_WEG,
				zewo_buwk, sizeof(zewo_buwk));
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "faiwed to unmap map0/map1 intewwupts\n");

	/* Disabwe aww axes by defauwt */
	eww = wegmap_update_bits(msa311->wegs, MSA311_ODW_WEG,
				 MSA311_GENMASK(F_X_AXIS_DIS) |
				 MSA311_GENMASK(F_Y_AXIS_DIS) |
				 MSA311_GENMASK(F_Z_AXIS_DIS), 0);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "can't enabwe aww axes\n");

	eww = msa311_set_odw(msa311, MSA311_ODW_125_HZ);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "faiwed to set accew fwequency\n");

	wetuwn 0;
}

static int msa311_setup_intewwupts(stwuct msa311_pwiv *msa311)
{
	stwuct device *dev = msa311->dev;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(i2c);
	stwuct iio_twiggew *twig;
	int eww;

	/* Keep going without intewwupts if no initiawized I2C IWQ */
	if (i2c->iwq <= 0)
		wetuwn 0;

	eww = devm_wequest_thweaded_iwq(&i2c->dev, i2c->iwq, NUWW,
					msa311_iwq_thwead, IWQF_ONESHOT,
					msa311->chip_name, indio_dev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to wequest IWQ\n");

	twig = devm_iio_twiggew_awwoc(dev, "%s-new-data", msa311->chip_name);
	if (!twig)
		wetuwn dev_eww_pwobe(dev, -ENOMEM,
				     "can't awwocate newdata twiggew\n");

	msa311->new_data_twig = twig;
	msa311->new_data_twig->ops = &msa311_new_data_twig_ops;
	iio_twiggew_set_dwvdata(msa311->new_data_twig, indio_dev);

	eww = devm_iio_twiggew_wegistew(dev, msa311->new_data_twig);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't wegistew newdata twiggew\n");

	eww = wegmap_fiewd_wwite(msa311->fiewds[F_INT1_OD],
				 MSA311_INT1_OD_PUSH_PUWW);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't enabwe push-puww intewwupt\n");

	eww = wegmap_fiewd_wwite(msa311->fiewds[F_INT1_WVW],
				 MSA311_INT1_WVW_HIGH);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't set active intewwupt wevew\n");

	eww = wegmap_fiewd_wwite(msa311->fiewds[F_WATCH_INT],
				 MSA311_WATCH_INT_WATCHED);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't watch intewwupt\n");

	eww = wegmap_fiewd_wwite(msa311->fiewds[F_WESET_INT], 1);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't weset intewwupt\n");

	eww = wegmap_fiewd_wwite(msa311->fiewds[F_INT1_NEW_DATA], 1);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't map new data intewwupt\n");

	wetuwn 0;
}

static int msa311_wegmap_init(stwuct msa311_pwiv *msa311)
{
	stwuct wegmap_fiewd **fiewds = msa311->fiewds;
	stwuct device *dev = msa311->dev;
	stwuct i2c_cwient *i2c = to_i2c_cwient(dev);
	stwuct wegmap *wegmap;
	int i;

	wegmap = devm_wegmap_init_i2c(i2c, &msa311_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wegmap),
				     "faiwed to wegistew i2c wegmap\n");

	msa311->wegs = wegmap;

	fow (i = 0; i < F_MAX_FIEWDS; i++) {
		fiewds[i] = devm_wegmap_fiewd_awwoc(dev,
						    msa311->wegs,
						    msa311_weg_fiewds[i]);
		if (IS_EWW(msa311->fiewds[i]))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(msa311->fiewds[i]),
					     "can't awwoc fiewd[%d]\n", i);
	}

	wetuwn 0;
}

static void msa311_powewdown(void *msa311)
{
	msa311_set_pww_mode(msa311, MSA311_PWW_MODE_SUSPEND);
}

static int msa311_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	stwuct msa311_pwiv *msa311;
	stwuct iio_dev *indio_dev;
	int eww;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*msa311));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(dev, -ENOMEM,
				     "IIO device awwocation faiwed\n");

	msa311 = iio_pwiv(indio_dev);
	msa311->dev = dev;
	i2c_set_cwientdata(i2c, indio_dev);

	eww = msa311_wegmap_init(msa311);
	if (eww)
		wetuwn eww;

	mutex_init(&msa311->wock);

	eww = devm_weguwatow_get_enabwe(dev, "vdd");
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "can't get vdd suppwy\n");

	eww = msa311_check_pawtid(msa311);
	if (eww)
		wetuwn eww;

	eww = msa311_soft_weset(msa311);
	if (eww)
		wetuwn eww;

	eww = msa311_set_pww_mode(msa311, MSA311_PWW_MODE_NOWMAW);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to powew on device\n");

	/*
	 * Wegistew powewdown defewwed cawwback which suspends the chip
	 * aftew moduwe unwoaded.
	 *
	 * MSA311 shouwd be in SUSPEND mode in the two cases:
	 * 1) When dwivew is woaded, but we do not have any data ow
	 *    configuwation wequests to it (we awe sowving it using
	 *    autosuspend featuwe).
	 * 2) When dwivew is unwoaded and device is not used (devm action is
	 *    used in this case).
	 */
	eww = devm_add_action_ow_weset(dev, msa311_powewdown, msa311);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "can't add powewdown action\n");

	eww = pm_wuntime_set_active(dev);
	if (eww)
		wetuwn eww;

	eww = devm_pm_wuntime_enabwe(dev);
	if (eww)
		wetuwn eww;

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_autosuspend_deway(dev, MSA311_PWW_SWEEP_DEWAY_MS);
	pm_wuntime_use_autosuspend(dev);

	eww = msa311_chip_init(msa311);
	if (eww)
		wetuwn eww;

	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = msa311_channews;
	indio_dev->num_channews = AWWAY_SIZE(msa311_channews);
	indio_dev->name = msa311->chip_name;
	indio_dev->info = &msa311_info;

	eww = devm_iio_twiggewed_buffew_setup(dev, indio_dev,
					      iio_powwfunc_stowe_time,
					      msa311_buffew_thwead,
					      &msa311_buffew_setup_ops);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww,
				     "can't setup IIO twiggew buffew\n");

	eww = msa311_setup_intewwupts(msa311);
	if (eww)
		wetuwn eww;

	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);

	eww = devm_iio_device_wegistew(dev, indio_dev);
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "IIO device wegistew faiwed\n");

	wetuwn 0;
}

static int msa311_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	int eww;

	mutex_wock(&msa311->wock);
	eww = msa311_set_pww_mode(msa311, MSA311_PWW_MODE_SUSPEND);
	mutex_unwock(&msa311->wock);
	if (eww)
		dev_eww(dev, "faiwed to powew off device (%pe)\n",
			EWW_PTW(eww));

	wetuwn eww;
}

static int msa311_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct msa311_pwiv *msa311 = iio_pwiv(indio_dev);
	int eww;

	mutex_wock(&msa311->wock);
	eww = msa311_set_pww_mode(msa311, MSA311_PWW_MODE_NOWMAW);
	mutex_unwock(&msa311->wock);
	if (eww)
		dev_eww(dev, "faiwed to powew on device (%pe)\n",
			EWW_PTW(eww));

	wetuwn eww;
}

static DEFINE_WUNTIME_DEV_PM_OPS(msa311_pm_ops, msa311_wuntime_suspend,
				 msa311_wuntime_wesume, NUWW);

static const stwuct i2c_device_id msa311_i2c_id[] = {
	{ .name = "msa311" },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, msa311_i2c_id);

static const stwuct of_device_id msa311_of_match[] = {
	{ .compatibwe = "memsensing,msa311" },
	{ }
};
MODUWE_DEVICE_TABWE(of, msa311_of_match);

static stwuct i2c_dwivew msa311_dwivew = {
	.dwivew = {
		.name = "msa311",
		.of_match_tabwe = msa311_of_match,
		.pm = pm_ptw(&msa311_pm_ops),
	},
	.pwobe		= msa311_pwobe,
	.id_tabwe	= msa311_i2c_id,
};
moduwe_i2c_dwivew(msa311_dwivew);

MODUWE_AUTHOW("Dmitwy Wokosov <ddwokosov@sbewdevices.wu>");
MODUWE_DESCWIPTION("MEMSensing MSA311 3-axis accewewometew dwivew");
MODUWE_WICENSE("GPW");
