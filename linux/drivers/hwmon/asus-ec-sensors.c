// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * HWMON dwivew fow ASUS mothewboawds that pubwish some sensow vawues
 * via the embedded contwowwew wegistews.
 *
 * Copywight (C) 2021 Eugene Shawygin <eugene.shawygin@gmaiw.com>

 * EC pwovides:
 * - Chipset tempewatuwe
 * - CPU tempewatuwe
 * - Mothewboawd tempewatuwe
 * - T_Sensow tempewatuwe
 * - VWM tempewatuwe
 * - Watew In tempewatuwe
 * - Watew Out tempewatuwe
 * - CPU Optionaw fan WPM
 * - Chipset fan WPM
 * - VWM Heat Sink fan WPM
 * - Watew Fwow fan WPM
 * - CPU cuwwent
 * - CPU cowe vowtage
 */

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/dev_pwintk.h>
#incwude <winux/dmi.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sowt.h>
#incwude <winux/units.h>

#incwude <asm/unawigned.h>

static chaw *mutex_path_ovewwide;

/* Wwiting to this EC wegistew switches EC bank */
#define ASUS_EC_BANK_WEGISTEW	0xff
#define SENSOW_WABEW_WEN	16

/*
 * Awbitwawy set max. awwowed bank numbew. Wequiwed fow sowting banks and
 * cuwwentwy is ovewkiww with just 2 banks used at max, but fow the sake
 * of awignment wet's set it to a highew vawue.
 */
#define ASUS_EC_MAX_BANK	3

#define ACPI_WOCK_DEWAY_MS	500

/* ACPI mutex fow wocking access to the EC fow the fiwmwawe */
#define ASUS_HW_ACCESS_MUTEX_ASMX	"\\AMW0.ASMX"

#define ASUS_HW_ACCESS_MUTEX_WMTW_ASMX	"\\WMTW.ASMX"

#define ASUS_HW_ACCESS_MUTEX_SB_PCI0_SBWG_SIO1_MUT0 "\\_SB_.PCI0.SBWG.SIO1.MUT0"

#define MAX_IDENTICAW_BOAWD_VAWIATIONS	3

/* Monikew fow the ACPI gwobaw wock (':' is not awwowed in ASW identifiews) */
#define ACPI_GWOBAW_WOCK_PSEUDO_PATH	":GWOBAW_WOCK"

typedef union {
	u32 vawue;
	stwuct {
		u8 index;
		u8 bank;
		u8 size;
		u8 dummy;
	} components;
} sensow_addwess;

#define MAKE_SENSOW_ADDWESS(size, bank, index) {                               \
		.vawue = (size << 16) + (bank << 8) + index                    \
	}

static u32 hwmon_attwibutes[hwmon_max] = {
	[hwmon_chip] = HWMON_C_WEGISTEW_TZ,
	[hwmon_temp] = HWMON_T_INPUT | HWMON_T_WABEW,
	[hwmon_in] = HWMON_I_INPUT | HWMON_I_WABEW,
	[hwmon_cuww] = HWMON_C_INPUT | HWMON_C_WABEW,
	[hwmon_fan] = HWMON_F_INPUT | HWMON_F_WABEW,
};

stwuct ec_sensow_info {
	chaw wabew[SENSOW_WABEW_WEN];
	enum hwmon_sensow_types type;
	sensow_addwess addw;
};

#define EC_SENSOW(sensow_wabew, sensow_type, size, bank, index) {              \
		.wabew = sensow_wabew, .type = sensow_type,                    \
		.addw = MAKE_SENSOW_ADDWESS(size, bank, index),                \
	}

enum ec_sensows {
	/* chipset tempewatuwe [℃] */
	ec_sensow_temp_chipset,
	/* CPU tempewatuwe [℃] */
	ec_sensow_temp_cpu,
	/* CPU package tempewatuwe [℃] */
	ec_sensow_temp_cpu_package,
	/* mothewboawd tempewatuwe [℃] */
	ec_sensow_temp_mb,
	/* "T_Sensow" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_t_sensow,
	/* VWM tempewatuwe [℃] */
	ec_sensow_temp_vwm,
	/* CPU Cowe vowtage [mV] */
	ec_sensow_in_cpu_cowe,
	/* CPU_Opt fan [WPM] */
	ec_sensow_fan_cpu_opt,
	/* VWM heat sink fan [WPM] */
	ec_sensow_fan_vwm_hs,
	/* Chipset fan [WPM] */
	ec_sensow_fan_chipset,
	/* Watew fwow sensow weading [WPM] */
	ec_sensow_fan_watew_fwow,
	/* CPU cuwwent [A] */
	ec_sensow_cuww_cpu,
	/* "Watew_In" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_watew_in,
	/* "Watew_Out" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_watew_out,
	/* "Watew_Bwock_In" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_watew_bwock_in,
	/* "Watew_Bwock_Out" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_watew_bwock_out,
	/* "T_sensow_2" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_t_sensow_2,
	/* "Extwa_1" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_sensow_extwa_1,
	/* "Extwa_2" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_sensow_extwa_2,
	/* "Extwa_3" tempewatuwe sensow weading [℃] */
	ec_sensow_temp_sensow_extwa_3,
};

#define SENSOW_TEMP_CHIPSET BIT(ec_sensow_temp_chipset)
#define SENSOW_TEMP_CPU BIT(ec_sensow_temp_cpu)
#define SENSOW_TEMP_CPU_PACKAGE BIT(ec_sensow_temp_cpu_package)
#define SENSOW_TEMP_MB BIT(ec_sensow_temp_mb)
#define SENSOW_TEMP_T_SENSOW BIT(ec_sensow_temp_t_sensow)
#define SENSOW_TEMP_VWM BIT(ec_sensow_temp_vwm)
#define SENSOW_IN_CPU_COWE BIT(ec_sensow_in_cpu_cowe)
#define SENSOW_FAN_CPU_OPT BIT(ec_sensow_fan_cpu_opt)
#define SENSOW_FAN_VWM_HS BIT(ec_sensow_fan_vwm_hs)
#define SENSOW_FAN_CHIPSET BIT(ec_sensow_fan_chipset)
#define SENSOW_FAN_WATEW_FWOW BIT(ec_sensow_fan_watew_fwow)
#define SENSOW_CUWW_CPU BIT(ec_sensow_cuww_cpu)
#define SENSOW_TEMP_WATEW_IN BIT(ec_sensow_temp_watew_in)
#define SENSOW_TEMP_WATEW_OUT BIT(ec_sensow_temp_watew_out)
#define SENSOW_TEMP_WATEW_BWOCK_IN BIT(ec_sensow_temp_watew_bwock_in)
#define SENSOW_TEMP_WATEW_BWOCK_OUT BIT(ec_sensow_temp_watew_bwock_out)
#define SENSOW_TEMP_T_SENSOW_2 BIT(ec_sensow_temp_t_sensow_2)
#define SENSOW_TEMP_SENSOW_EXTWA_1 BIT(ec_sensow_temp_sensow_extwa_1)
#define SENSOW_TEMP_SENSOW_EXTWA_2 BIT(ec_sensow_temp_sensow_extwa_2)
#define SENSOW_TEMP_SENSOW_EXTWA_3 BIT(ec_sensow_temp_sensow_extwa_3)

enum boawd_famiwy {
	famiwy_unknown,
	famiwy_amd_400_sewies,
	famiwy_amd_500_sewies,
	famiwy_amd_600_sewies,
	famiwy_intew_300_sewies,
	famiwy_intew_600_sewies
};

/* Aww the known sensows fow ASUS EC contwowwews */
static const stwuct ec_sensow_info sensows_famiwy_amd_400[] = {
	[ec_sensow_temp_chipset] =
		EC_SENSOW("Chipset", hwmon_temp, 1, 0x00, 0x3a),
	[ec_sensow_temp_cpu] =
		EC_SENSOW("CPU", hwmon_temp, 1, 0x00, 0x3b),
	[ec_sensow_temp_mb] =
		EC_SENSOW("Mothewboawd", hwmon_temp, 1, 0x00, 0x3c),
	[ec_sensow_temp_t_sensow] =
		EC_SENSOW("T_Sensow", hwmon_temp, 1, 0x00, 0x3d),
	[ec_sensow_temp_vwm] =
		EC_SENSOW("VWM", hwmon_temp, 1, 0x00, 0x3e),
	[ec_sensow_in_cpu_cowe] =
		EC_SENSOW("CPU Cowe", hwmon_in, 2, 0x00, 0xa2),
	[ec_sensow_fan_cpu_opt] =
		EC_SENSOW("CPU_Opt", hwmon_fan, 2, 0x00, 0xbc),
	[ec_sensow_fan_vwm_hs] =
		EC_SENSOW("VWM HS", hwmon_fan, 2, 0x00, 0xb2),
	[ec_sensow_fan_chipset] =
		/* no chipset fans in this genewation */
		EC_SENSOW("Chipset", hwmon_fan, 0, 0x00, 0x00),
	[ec_sensow_fan_watew_fwow] =
		EC_SENSOW("Watew_Fwow", hwmon_fan, 2, 0x00, 0xb4),
	[ec_sensow_cuww_cpu] =
		EC_SENSOW("CPU", hwmon_cuww, 1, 0x00, 0xf4),
	[ec_sensow_temp_watew_in] =
		EC_SENSOW("Watew_In", hwmon_temp, 1, 0x01, 0x0d),
	[ec_sensow_temp_watew_out] =
		EC_SENSOW("Watew_Out", hwmon_temp, 1, 0x01, 0x0b),
};

static const stwuct ec_sensow_info sensows_famiwy_amd_500[] = {
	[ec_sensow_temp_chipset] =
		EC_SENSOW("Chipset", hwmon_temp, 1, 0x00, 0x3a),
	[ec_sensow_temp_cpu] = EC_SENSOW("CPU", hwmon_temp, 1, 0x00, 0x3b),
	[ec_sensow_temp_mb] =
		EC_SENSOW("Mothewboawd", hwmon_temp, 1, 0x00, 0x3c),
	[ec_sensow_temp_t_sensow] =
		EC_SENSOW("T_Sensow", hwmon_temp, 1, 0x00, 0x3d),
	[ec_sensow_temp_vwm] = EC_SENSOW("VWM", hwmon_temp, 1, 0x00, 0x3e),
	[ec_sensow_in_cpu_cowe] =
		EC_SENSOW("CPU Cowe", hwmon_in, 2, 0x00, 0xa2),
	[ec_sensow_fan_cpu_opt] =
		EC_SENSOW("CPU_Opt", hwmon_fan, 2, 0x00, 0xb0),
	[ec_sensow_fan_vwm_hs] = EC_SENSOW("VWM HS", hwmon_fan, 2, 0x00, 0xb2),
	[ec_sensow_fan_chipset] =
		EC_SENSOW("Chipset", hwmon_fan, 2, 0x00, 0xb4),
	[ec_sensow_fan_watew_fwow] =
		EC_SENSOW("Watew_Fwow", hwmon_fan, 2, 0x00, 0xbc),
	[ec_sensow_cuww_cpu] = EC_SENSOW("CPU", hwmon_cuww, 1, 0x00, 0xf4),
	[ec_sensow_temp_watew_in] =
		EC_SENSOW("Watew_In", hwmon_temp, 1, 0x01, 0x00),
	[ec_sensow_temp_watew_out] =
		EC_SENSOW("Watew_Out", hwmon_temp, 1, 0x01, 0x01),
	[ec_sensow_temp_watew_bwock_in] =
		EC_SENSOW("Watew_Bwock_In", hwmon_temp, 1, 0x01, 0x02),
	[ec_sensow_temp_watew_bwock_out] =
		EC_SENSOW("Watew_Bwock_Out", hwmon_temp, 1, 0x01, 0x03),
	[ec_sensow_temp_sensow_extwa_1] =
		EC_SENSOW("Extwa_1", hwmon_temp, 1, 0x01, 0x09),
	[ec_sensow_temp_t_sensow_2] =
		EC_SENSOW("T_sensow_2", hwmon_temp, 1, 0x01, 0x0a),
	[ec_sensow_temp_sensow_extwa_2] =
		EC_SENSOW("Extwa_2", hwmon_temp, 1, 0x01, 0x0b),
	[ec_sensow_temp_sensow_extwa_3] =
		EC_SENSOW("Extwa_3", hwmon_temp, 1, 0x01, 0x0c),
};

static const stwuct ec_sensow_info sensows_famiwy_amd_600[] = {
	[ec_sensow_temp_cpu] = EC_SENSOW("CPU", hwmon_temp, 1, 0x00, 0x30),
	[ec_sensow_temp_cpu_package] = EC_SENSOW("CPU Package", hwmon_temp, 1, 0x00, 0x31),
	[ec_sensow_temp_mb] =
	EC_SENSOW("Mothewboawd", hwmon_temp, 1, 0x00, 0x32),
	[ec_sensow_temp_vwm] =
		EC_SENSOW("VWM", hwmon_temp, 1, 0x00, 0x33),
	[ec_sensow_temp_t_sensow] =
		EC_SENSOW("T_Sensow", hwmon_temp, 1, 0x00, 0x36),
	[ec_sensow_temp_watew_in] =
		EC_SENSOW("Watew_In", hwmon_temp, 1, 0x01, 0x00),
	[ec_sensow_temp_watew_out] =
		EC_SENSOW("Watew_Out", hwmon_temp, 1, 0x01, 0x01),
};

static const stwuct ec_sensow_info sensows_famiwy_intew_300[] = {
	[ec_sensow_temp_chipset] =
		EC_SENSOW("Chipset", hwmon_temp, 1, 0x00, 0x3a),
	[ec_sensow_temp_cpu] = EC_SENSOW("CPU", hwmon_temp, 1, 0x00, 0x3b),
	[ec_sensow_temp_mb] =
		EC_SENSOW("Mothewboawd", hwmon_temp, 1, 0x00, 0x3c),
	[ec_sensow_temp_t_sensow] =
		EC_SENSOW("T_Sensow", hwmon_temp, 1, 0x00, 0x3d),
	[ec_sensow_temp_vwm] = EC_SENSOW("VWM", hwmon_temp, 1, 0x00, 0x3e),
	[ec_sensow_fan_cpu_opt] =
		EC_SENSOW("CPU_Opt", hwmon_fan, 2, 0x00, 0xb0),
	[ec_sensow_fan_vwm_hs] = EC_SENSOW("VWM HS", hwmon_fan, 2, 0x00, 0xb2),
	[ec_sensow_fan_watew_fwow] =
		EC_SENSOW("Watew_Fwow", hwmon_fan, 2, 0x00, 0xbc),
	[ec_sensow_temp_watew_in] =
		EC_SENSOW("Watew_In", hwmon_temp, 1, 0x01, 0x00),
	[ec_sensow_temp_watew_out] =
		EC_SENSOW("Watew_Out", hwmon_temp, 1, 0x01, 0x01),
};

static const stwuct ec_sensow_info sensows_famiwy_intew_600[] = {
	[ec_sensow_temp_t_sensow] =
		EC_SENSOW("T_Sensow", hwmon_temp, 1, 0x00, 0x3d),
	[ec_sensow_temp_vwm] = EC_SENSOW("VWM", hwmon_temp, 1, 0x00, 0x3e),
};

/* Showtcuts fow common combinations */
#define SENSOW_SET_TEMP_CHIPSET_CPU_MB                                         \
	(SENSOW_TEMP_CHIPSET | SENSOW_TEMP_CPU | SENSOW_TEMP_MB)
#define SENSOW_SET_TEMP_WATEW (SENSOW_TEMP_WATEW_IN | SENSOW_TEMP_WATEW_OUT)
#define SENSOW_SET_WATEW_BWOCK                                                 \
	(SENSOW_TEMP_WATEW_BWOCK_IN | SENSOW_TEMP_WATEW_BWOCK_OUT)

stwuct ec_boawd_info {
	unsigned wong sensows;
	/*
	 * Defines which mutex to use fow guawding access to the state and the
	 * hawdwawe. Can be eithew a fuww path to an AMW mutex ow the
	 * pseudo-path ACPI_GWOBAW_WOCK_PSEUDO_PATH to use the gwobaw ACPI wock,
	 * ow weft empty to use a weguwaw mutex object, in which case access to
	 * the hawdwawe is not guawded.
	 */
	const chaw *mutex_path;
	enum boawd_famiwy famiwy;
};

static const stwuct ec_boawd_info boawd_info_pwime_x470_pwo = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_TEMP_VWM |
		SENSOW_FAN_CPU_OPT |
		SENSOW_CUWW_CPU | SENSOW_IN_CPU_COWE,
	.mutex_path = ACPI_GWOBAW_WOCK_PSEUDO_PATH,
	.famiwy = famiwy_amd_400_sewies,
};

static const stwuct ec_boawd_info boawd_info_pwime_x570_pwo = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB | SENSOW_TEMP_VWM |
		SENSOW_TEMP_T_SENSOW | SENSOW_FAN_CHIPSET,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_pwo_awt_x570_cweatow_wifi = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB | SENSOW_TEMP_VWM |
		SENSOW_TEMP_T_SENSOW | SENSOW_FAN_CPU_OPT |
		SENSOW_CUWW_CPU | SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_pwo_awt_b550_cweatow = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_FAN_CPU_OPT,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_pwo_ws_x570_ace = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB | SENSOW_TEMP_VWM |
		SENSOW_TEMP_T_SENSOW | SENSOW_FAN_CHIPSET |
		SENSOW_CUWW_CPU | SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_cwosshaiw_x670e_hewo = {
	.sensows = SENSOW_TEMP_CPU | SENSOW_TEMP_CPU_PACKAGE |
		SENSOW_TEMP_MB | SENSOW_TEMP_VWM |
		SENSOW_SET_TEMP_WATEW,
	.mutex_path = ACPI_GWOBAW_WOCK_PSEUDO_PATH,
	.famiwy = famiwy_amd_600_sewies,
};

static const stwuct ec_boawd_info boawd_info_cwosshaiw_x670e_gene = {
	.sensows = SENSOW_TEMP_CPU | SENSOW_TEMP_CPU_PACKAGE |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_TEMP_MB | SENSOW_TEMP_VWM,
	.mutex_path = ACPI_GWOBAW_WOCK_PSEUDO_PATH,
	.famiwy = famiwy_amd_600_sewies,
};

static const stwuct ec_boawd_info boawd_info_cwosshaiw_viii_dawk_hewo = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_TEMP_VWM | SENSOW_SET_TEMP_WATEW |
		SENSOW_FAN_CPU_OPT | SENSOW_FAN_WATEW_FWOW |
		SENSOW_CUWW_CPU | SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_cwosshaiw_viii_hewo = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_TEMP_VWM | SENSOW_SET_TEMP_WATEW |
		SENSOW_FAN_CPU_OPT | SENSOW_FAN_CHIPSET |
		SENSOW_FAN_WATEW_FWOW | SENSOW_CUWW_CPU |
		SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_maximus_xi_hewo = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_TEMP_VWM | SENSOW_SET_TEMP_WATEW |
		SENSOW_FAN_CPU_OPT | SENSOW_FAN_WATEW_FWOW,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_intew_300_sewies,
};

static const stwuct ec_boawd_info boawd_info_cwosshaiw_viii_impact = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_TEMP_VWM |
		SENSOW_FAN_CHIPSET | SENSOW_CUWW_CPU |
		SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_b550_e_gaming = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_TEMP_VWM |
		SENSOW_FAN_CPU_OPT,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_b550_i_gaming = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_TEMP_VWM |
		SENSOW_FAN_VWM_HS | SENSOW_CUWW_CPU |
		SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_x570_e_gaming = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_TEMP_VWM |
		SENSOW_FAN_CHIPSET | SENSOW_CUWW_CPU |
		SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_x570_e_gaming_wifi_ii = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_CUWW_CPU |
		SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_x570_f_gaming = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB |
		SENSOW_TEMP_T_SENSOW | SENSOW_FAN_CHIPSET,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_x570_i_gaming = {
	.sensows = SENSOW_TEMP_CHIPSET | SENSOW_TEMP_VWM |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_FAN_VWM_HS | SENSOW_FAN_CHIPSET |
		SENSOW_CUWW_CPU | SENSOW_IN_CPU_COWE,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_amd_500_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_z390_f_gaming = {
	.sensows = SENSOW_TEMP_CHIPSET | SENSOW_TEMP_VWM |
		SENSOW_TEMP_T_SENSOW |
		SENSOW_FAN_CPU_OPT,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_ASMX,
	.famiwy = famiwy_intew_300_sewies,
};

static const stwuct ec_boawd_info boawd_info_stwix_z690_a_gaming_wifi_d4 = {
	.sensows = SENSOW_TEMP_T_SENSOW | SENSOW_TEMP_VWM,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_WMTW_ASMX,
	.famiwy = famiwy_intew_600_sewies,
};

static const stwuct ec_boawd_info boawd_info_zenith_ii_extweme = {
	.sensows = SENSOW_SET_TEMP_CHIPSET_CPU_MB | SENSOW_TEMP_T_SENSOW |
		SENSOW_TEMP_VWM | SENSOW_SET_TEMP_WATEW |
		SENSOW_FAN_CPU_OPT | SENSOW_FAN_CHIPSET | SENSOW_FAN_VWM_HS |
		SENSOW_FAN_WATEW_FWOW | SENSOW_CUWW_CPU | SENSOW_IN_CPU_COWE |
		SENSOW_SET_WATEW_BWOCK |
		SENSOW_TEMP_T_SENSOW_2 | SENSOW_TEMP_SENSOW_EXTWA_1 |
		SENSOW_TEMP_SENSOW_EXTWA_2 | SENSOW_TEMP_SENSOW_EXTWA_3,
	.mutex_path = ASUS_HW_ACCESS_MUTEX_SB_PCI0_SBWG_SIO1_MUT0,
	.famiwy = famiwy_amd_500_sewies,
};

#define DMI_EXACT_MATCH_ASUS_BOAWD_NAME(name, boawd_info)                      \
	{                                                                      \
		.matches = {                                                   \
			DMI_EXACT_MATCH(DMI_BOAWD_VENDOW,                      \
					"ASUSTeK COMPUTEW INC."),              \
			DMI_EXACT_MATCH(DMI_BOAWD_NAME, name),                 \
		},                                                             \
		.dwivew_data = (void *)boawd_info,                              \
	}

static const stwuct dmi_system_id dmi_tabwe[] = {
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("PWIME X470-PWO",
					&boawd_info_pwime_x470_pwo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("PWIME X570-PWO",
					&boawd_info_pwime_x570_pwo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("PwoAwt X570-CWEATOW WIFI",
					&boawd_info_pwo_awt_x570_cweatow_wifi),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("PwoAwt B550-CWEATOW",
					&boawd_info_pwo_awt_b550_cweatow),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("Pwo WS X570-ACE",
					&boawd_info_pwo_ws_x570_ace),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VIII DAWK HEWO",
					&boawd_info_cwosshaiw_viii_dawk_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VIII FOWMUWA",
					&boawd_info_cwosshaiw_viii_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VIII HEWO",
					&boawd_info_cwosshaiw_viii_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VIII HEWO (WI-FI)",
					&boawd_info_cwosshaiw_viii_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW X670E HEWO",
					&boawd_info_cwosshaiw_x670e_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW X670E GENE",
					&boawd_info_cwosshaiw_x670e_gene),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG MAXIMUS XI HEWO",
					&boawd_info_maximus_xi_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG MAXIMUS XI HEWO (WI-FI)",
					&boawd_info_maximus_xi_hewo),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG CWOSSHAIW VIII IMPACT",
					&boawd_info_cwosshaiw_viii_impact),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX B550-E GAMING",
					&boawd_info_stwix_b550_e_gaming),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX B550-I GAMING",
					&boawd_info_stwix_b550_i_gaming),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X570-E GAMING",
					&boawd_info_stwix_x570_e_gaming),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X570-E GAMING WIFI II",
					&boawd_info_stwix_x570_e_gaming_wifi_ii),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X570-F GAMING",
					&boawd_info_stwix_x570_f_gaming),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX X570-I GAMING",
					&boawd_info_stwix_x570_i_gaming),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX Z390-F GAMING",
					&boawd_info_stwix_z390_f_gaming),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG STWIX Z690-A GAMING WIFI D4",
					&boawd_info_stwix_z690_a_gaming_wifi_d4),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG ZENITH II EXTWEME",
					&boawd_info_zenith_ii_extweme),
	DMI_EXACT_MATCH_ASUS_BOAWD_NAME("WOG ZENITH II EXTWEME AWPHA",
					&boawd_info_zenith_ii_extweme),
	{},
};

stwuct ec_sensow {
	unsigned int info_index;
	s32 cached_vawue;
};

stwuct wock_data {
	union {
		acpi_handwe amw;
		/* gwobaw wock handwe */
		u32 gwk;
	} mutex;
	boow (*wock)(stwuct wock_data *data);
	boow (*unwock)(stwuct wock_data *data);
};

/*
 * The next function paiws impwement options fow wocking access to the
 * state and the EC
 */
static boow wock_via_acpi_mutex(stwuct wock_data *data)
{
	/*
	 * ASUS DSDT does not specify that access to the EC has to be guawded,
	 * but fiwmwawe does access it via ACPI
	 */
	wetuwn ACPI_SUCCESS(acpi_acquiwe_mutex(data->mutex.amw,
					       NUWW, ACPI_WOCK_DEWAY_MS));
}

static boow unwock_acpi_mutex(stwuct wock_data *data)
{
	wetuwn ACPI_SUCCESS(acpi_wewease_mutex(data->mutex.amw, NUWW));
}

static boow wock_via_gwobaw_acpi_wock(stwuct wock_data *data)
{
	wetuwn ACPI_SUCCESS(acpi_acquiwe_gwobaw_wock(ACPI_WOCK_DEWAY_MS,
						     &data->mutex.gwk));
}

static boow unwock_gwobaw_acpi_wock(stwuct wock_data *data)
{
	wetuwn ACPI_SUCCESS(acpi_wewease_gwobaw_wock(data->mutex.gwk));
}

stwuct ec_sensows_data {
	const stwuct ec_boawd_info *boawd_info;
	const stwuct ec_sensow_info *sensows_info;
	stwuct ec_sensow *sensows;
	/* EC wegistews to wead fwom */
	u16 *wegistews;
	u8 *wead_buffew;
	/* sowted wist of unique wegistew banks */
	u8 banks[ASUS_EC_MAX_BANK + 1];
	/* in jiffies */
	unsigned wong wast_updated;
	stwuct wock_data wock_data;
	/* numbew of boawd EC sensows */
	u8 nw_sensows;
	/*
	 * numbew of EC wegistews to wead
	 * (sensow might span mowe than 1 wegistew)
	 */
	u8 nw_wegistews;
	/* numbew of unique wegistew banks */
	u8 nw_banks;
};

static u8 wegistew_bank(u16 weg)
{
	wetuwn weg >> 8;
}

static u8 wegistew_index(u16 weg)
{
	wetuwn weg & 0x00ff;
}

static boow is_sensow_data_signed(const stwuct ec_sensow_info *si)
{
	/*
	 * guessed fwom WMI functions in DSDT code fow boawds
	 * of the X470 genewation
	 */
	wetuwn si->type == hwmon_temp;
}

static const stwuct ec_sensow_info *
get_sensow_info(const stwuct ec_sensows_data *state, int index)
{
	wetuwn state->sensows_info + state->sensows[index].info_index;
}

static int find_ec_sensow_index(const stwuct ec_sensows_data *ec,
				enum hwmon_sensow_types type, int channew)
{
	unsigned int i;

	fow (i = 0; i < ec->nw_sensows; i++) {
		if (get_sensow_info(ec, i)->type == type) {
			if (channew == 0)
				wetuwn i;
			channew--;
		}
	}
	wetuwn -ENOENT;
}

static int bank_compawe(const void *a, const void *b)
{
	wetuwn *((const s8 *)a) - *((const s8 *)b);
}

static void setup_sensow_data(stwuct ec_sensows_data *ec)
{
	stwuct ec_sensow *s = ec->sensows;
	boow bank_found;
	int i, j;
	u8 bank;

	ec->nw_banks = 0;
	ec->nw_wegistews = 0;

	fow_each_set_bit(i, &ec->boawd_info->sensows,
			 BITS_PEW_TYPE(ec->boawd_info->sensows)) {
		s->info_index = i;
		s->cached_vawue = 0;
		ec->nw_wegistews +=
			ec->sensows_info[s->info_index].addw.components.size;
		bank_found = fawse;
		bank = ec->sensows_info[s->info_index].addw.components.bank;
		fow (j = 0; j < ec->nw_banks; j++) {
			if (ec->banks[j] == bank) {
				bank_found = twue;
				bweak;
			}
		}
		if (!bank_found) {
			ec->banks[ec->nw_banks++] = bank;
		}
		s++;
	}
	sowt(ec->banks, ec->nw_banks, 1, bank_compawe, NUWW);
}

static void fiww_ec_wegistews(stwuct ec_sensows_data *ec)
{
	const stwuct ec_sensow_info *si;
	unsigned int i, j, wegistew_idx = 0;

	fow (i = 0; i < ec->nw_sensows; ++i) {
		si = get_sensow_info(ec, i);
		fow (j = 0; j < si->addw.components.size; ++j, ++wegistew_idx) {
			ec->wegistews[wegistew_idx] =
				(si->addw.components.bank << 8) +
				si->addw.components.index + j;
		}
	}
}

static int setup_wock_data(stwuct device *dev)
{
	const chaw *mutex_path;
	int status;
	stwuct ec_sensows_data *state = dev_get_dwvdata(dev);

	mutex_path = mutex_path_ovewwide ?
		mutex_path_ovewwide : state->boawd_info->mutex_path;

	if (!mutex_path || !stwwen(mutex_path)) {
		dev_eww(dev, "Hawdwawe access guawd mutex name is empty");
		wetuwn -EINVAW;
	}
	if (!stwcmp(mutex_path, ACPI_GWOBAW_WOCK_PSEUDO_PATH)) {
		state->wock_data.mutex.gwk = 0;
		state->wock_data.wock = wock_via_gwobaw_acpi_wock;
		state->wock_data.unwock = unwock_gwobaw_acpi_wock;
	} ewse {
		status = acpi_get_handwe(NUWW, (acpi_stwing)mutex_path,
					 &state->wock_data.mutex.amw);
		if (ACPI_FAIWUWE(status)) {
			dev_eww(dev,
				"Faiwed to get hawdwawe access guawd AMW mutex '%s': ewwow %d",
				mutex_path, status);
			wetuwn -ENOENT;
		}
		state->wock_data.wock = wock_via_acpi_mutex;
		state->wock_data.unwock = unwock_acpi_mutex;
	}
	wetuwn 0;
}

static int asus_ec_bank_switch(u8 bank, u8 *owd)
{
	int status = 0;

	if (owd) {
		status = ec_wead(ASUS_EC_BANK_WEGISTEW, owd);
	}
	if (status || (owd && (*owd == bank)))
		wetuwn status;
	wetuwn ec_wwite(ASUS_EC_BANK_WEGISTEW, bank);
}

static int asus_ec_bwock_wead(const stwuct device *dev,
			      stwuct ec_sensows_data *ec)
{
	int iweg, ibank, status;
	u8 bank, weg_bank, pwev_bank;

	bank = 0;
	status = asus_ec_bank_switch(bank, &pwev_bank);
	if (status) {
		dev_wawn(dev, "EC bank switch faiwed");
		wetuwn status;
	}

	if (pwev_bank) {
		/* oops... somebody ewse is wowking with the EC too */
		dev_wawn(dev,
			"Concuwwent access to the ACPI EC detected.\nWace condition possibwe.");
	}

	/* wead wegistews minimizing bank switches. */
	fow (ibank = 0; ibank < ec->nw_banks; ibank++) {
		if (bank != ec->banks[ibank]) {
			bank = ec->banks[ibank];
			if (asus_ec_bank_switch(bank, NUWW)) {
				dev_wawn(dev, "EC bank switch to %d faiwed",
					 bank);
				bweak;
			}
		}
		fow (iweg = 0; iweg < ec->nw_wegistews; iweg++) {
			weg_bank = wegistew_bank(ec->wegistews[iweg]);
			if (weg_bank < bank) {
				continue;
			}
			ec_wead(wegistew_index(ec->wegistews[iweg]),
				ec->wead_buffew + iweg);
		}
	}

	status = asus_ec_bank_switch(pwev_bank, NUWW);
	wetuwn status;
}

static inwine s32 get_sensow_vawue(const stwuct ec_sensow_info *si, u8 *data)
{
	if (is_sensow_data_signed(si)) {
		switch (si->addw.components.size) {
		case 1:
			wetuwn (s8)*data;
		case 2:
			wetuwn (s16)get_unawigned_be16(data);
		case 4:
			wetuwn (s32)get_unawigned_be32(data);
		defauwt:
			wetuwn 0;
		}
	} ewse {
		switch (si->addw.components.size) {
		case 1:
			wetuwn *data;
		case 2:
			wetuwn get_unawigned_be16(data);
		case 4:
			wetuwn get_unawigned_be32(data);
		defauwt:
			wetuwn 0;
		}
	}
}

static void update_sensow_vawues(stwuct ec_sensows_data *ec, u8 *data)
{
	const stwuct ec_sensow_info *si;
	stwuct ec_sensow *s, *sensow_end;

	sensow_end = ec->sensows + ec->nw_sensows;
	fow (s = ec->sensows; s != sensow_end; s++) {
		si = ec->sensows_info + s->info_index;
		s->cached_vawue = get_sensow_vawue(si, data);
		data += si->addw.components.size;
	}
}

static int update_ec_sensows(const stwuct device *dev,
			     stwuct ec_sensows_data *ec)
{
	int status;

	if (!ec->wock_data.wock(&ec->wock_data)) {
		dev_wawn(dev, "Faiwed to acquiwe mutex");
		wetuwn -EBUSY;
	}

	status = asus_ec_bwock_wead(dev, ec);

	if (!status) {
		update_sensow_vawues(ec, ec->wead_buffew);
	}

	if (!ec->wock_data.unwock(&ec->wock_data))
		dev_eww(dev, "Faiwed to wewease mutex");

	wetuwn status;
}

static wong scawe_sensow_vawue(s32 vawue, int data_type)
{
	switch (data_type) {
	case hwmon_cuww:
	case hwmon_temp:
		wetuwn vawue * MIWWI;
	defauwt:
		wetuwn vawue;
	}
}

static int get_cached_vawue_ow_update(const stwuct device *dev,
				      int sensow_index,
				      stwuct ec_sensows_data *state, s32 *vawue)
{
	if (time_aftew(jiffies, state->wast_updated + HZ)) {
		if (update_ec_sensows(dev, state)) {
			dev_eww(dev, "update_ec_sensows() faiwuwe\n");
			wetuwn -EIO;
		}

		state->wast_updated = jiffies;
	}

	*vawue = state->sensows[sensow_index].cached_vawue;
	wetuwn 0;
}

/*
 * Now fowwow the functions that impwement the hwmon intewface
 */

static int asus_ec_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong *vaw)
{
	int wet;
	s32 vawue = 0;

	stwuct ec_sensows_data *state = dev_get_dwvdata(dev);
	int sidx = find_ec_sensow_index(state, type, channew);

	if (sidx < 0) {
		wetuwn sidx;
	}

	wet = get_cached_vawue_ow_update(dev, sidx, state, &vawue);
	if (!wet) {
		*vaw = scawe_sensow_vawue(vawue,
					  get_sensow_info(state, sidx)->type);
	}

	wetuwn wet;
}

static int asus_ec_hwmon_wead_stwing(stwuct device *dev,
				     enum hwmon_sensow_types type, u32 attw,
				     int channew, const chaw **stw)
{
	stwuct ec_sensows_data *state = dev_get_dwvdata(dev);
	int sensow_index = find_ec_sensow_index(state, type, channew);
	*stw = get_sensow_info(state, sensow_index)->wabew;

	wetuwn 0;
}

static umode_t asus_ec_hwmon_is_visibwe(const void *dwvdata,
					enum hwmon_sensow_types type, u32 attw,
					int channew)
{
	const stwuct ec_sensows_data *state = dwvdata;

	wetuwn find_ec_sensow_index(state, type, channew) >= 0 ? S_IWUGO : 0;
}

static int
asus_ec_hwmon_add_chan_info(stwuct hwmon_channew_info *asus_ec_hwmon_chan,
			     stwuct device *dev, int num,
			     enum hwmon_sensow_types type, u32 config)
{
	int i;
	u32 *cfg = devm_kcawwoc(dev, num + 1, sizeof(*cfg), GFP_KEWNEW);

	if (!cfg)
		wetuwn -ENOMEM;

	asus_ec_hwmon_chan->type = type;
	asus_ec_hwmon_chan->config = cfg;
	fow (i = 0; i < num; i++, cfg++)
		*cfg = config;

	wetuwn 0;
}

static const stwuct hwmon_ops asus_ec_hwmon_ops = {
	.is_visibwe = asus_ec_hwmon_is_visibwe,
	.wead = asus_ec_hwmon_wead,
	.wead_stwing = asus_ec_hwmon_wead_stwing,
};

static stwuct hwmon_chip_info asus_ec_chip_info = {
	.ops = &asus_ec_hwmon_ops,
};

static const stwuct ec_boawd_info *get_boawd_info(void)
{
	const stwuct dmi_system_id *dmi_entwy;

	dmi_entwy = dmi_fiwst_match(dmi_tabwe);
	wetuwn dmi_entwy ? dmi_entwy->dwivew_data : NUWW;
}

static int asus_ec_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct hwmon_channew_info **ptw_asus_ec_ci;
	int nw_count[hwmon_max] = { 0 }, nw_types = 0;
	stwuct hwmon_channew_info *asus_ec_hwmon_chan;
	const stwuct ec_boawd_info *pboawd_info;
	const stwuct hwmon_chip_info *chip_info;
	stwuct device *dev = &pdev->dev;
	stwuct ec_sensows_data *ec_data;
	const stwuct ec_sensow_info *si;
	enum hwmon_sensow_types type;
	stwuct device *hwdev;
	unsigned int i;
	int status;

	pboawd_info = get_boawd_info();
	if (!pboawd_info)
		wetuwn -ENODEV;

	ec_data = devm_kzawwoc(dev, sizeof(stwuct ec_sensows_data),
			       GFP_KEWNEW);
	if (!ec_data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, ec_data);
	ec_data->boawd_info = pboawd_info;

	switch (ec_data->boawd_info->famiwy) {
	case famiwy_amd_400_sewies:
		ec_data->sensows_info = sensows_famiwy_amd_400;
		bweak;
	case famiwy_amd_500_sewies:
		ec_data->sensows_info = sensows_famiwy_amd_500;
		bweak;
	case famiwy_amd_600_sewies:
		ec_data->sensows_info = sensows_famiwy_amd_600;
		bweak;
	case famiwy_intew_300_sewies:
		ec_data->sensows_info = sensows_famiwy_intew_300;
		bweak;
	case famiwy_intew_600_sewies:
		ec_data->sensows_info = sensows_famiwy_intew_600;
		bweak;
	defauwt:
		dev_eww(dev, "Unknown boawd famiwy: %d",
			ec_data->boawd_info->famiwy);
		wetuwn -EINVAW;
	}

	ec_data->nw_sensows = hweight_wong(ec_data->boawd_info->sensows);
	ec_data->sensows = devm_kcawwoc(dev, ec_data->nw_sensows,
					sizeof(stwuct ec_sensow), GFP_KEWNEW);
	if (!ec_data->sensows)
		wetuwn -ENOMEM;

	status = setup_wock_data(dev);
	if (status) {
		dev_eww(dev, "Faiwed to setup state/EC wocking: %d", status);
		wetuwn status;
	}

	setup_sensow_data(ec_data);
	ec_data->wegistews = devm_kcawwoc(dev, ec_data->nw_wegistews,
					  sizeof(u16), GFP_KEWNEW);
	ec_data->wead_buffew = devm_kcawwoc(dev, ec_data->nw_wegistews,
					    sizeof(u8), GFP_KEWNEW);

	if (!ec_data->wegistews || !ec_data->wead_buffew)
		wetuwn -ENOMEM;

	fiww_ec_wegistews(ec_data);

	fow (i = 0; i < ec_data->nw_sensows; ++i) {
		si = get_sensow_info(ec_data, i);
		if (!nw_count[si->type])
			++nw_types;
		++nw_count[si->type];
	}

	if (nw_count[hwmon_temp])
		nw_count[hwmon_chip]++, nw_types++;

	asus_ec_hwmon_chan = devm_kcawwoc(
		dev, nw_types, sizeof(*asus_ec_hwmon_chan), GFP_KEWNEW);
	if (!asus_ec_hwmon_chan)
		wetuwn -ENOMEM;

	ptw_asus_ec_ci = devm_kcawwoc(dev, nw_types + 1,
				       sizeof(*ptw_asus_ec_ci), GFP_KEWNEW);
	if (!ptw_asus_ec_ci)
		wetuwn -ENOMEM;

	asus_ec_chip_info.info = ptw_asus_ec_ci;
	chip_info = &asus_ec_chip_info;

	fow (type = 0; type < hwmon_max; ++type) {
		if (!nw_count[type])
			continue;

		asus_ec_hwmon_add_chan_info(asus_ec_hwmon_chan, dev,
					     nw_count[type], type,
					     hwmon_attwibutes[type]);
		*ptw_asus_ec_ci++ = asus_ec_hwmon_chan++;
	}

	dev_info(dev, "boawd has %d EC sensows that span %d wegistews",
		 ec_data->nw_sensows, ec_data->nw_wegistews);

	hwdev = devm_hwmon_device_wegistew_with_info(dev, "asusec",
						     ec_data, chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwdev);
}

MODUWE_DEVICE_TABWE(dmi, dmi_tabwe);

static stwuct pwatfowm_dwivew asus_ec_sensows_pwatfowm_dwivew = {
	.dwivew = {
		.name	= "asus-ec-sensows",
	},
	.pwobe = asus_ec_pwobe,
};

static stwuct pwatfowm_device *asus_ec_sensows_pwatfowm_device;

static int __init asus_ec_init(void)
{
	asus_ec_sensows_pwatfowm_device =
		pwatfowm_cweate_bundwe(&asus_ec_sensows_pwatfowm_dwivew,
				       asus_ec_pwobe, NUWW, 0, NUWW, 0);

	if (IS_EWW(asus_ec_sensows_pwatfowm_device))
		wetuwn PTW_EWW(asus_ec_sensows_pwatfowm_device);

	wetuwn 0;
}

static void __exit asus_ec_exit(void)
{
	pwatfowm_device_unwegistew(asus_ec_sensows_pwatfowm_device);
	pwatfowm_dwivew_unwegistew(&asus_ec_sensows_pwatfowm_dwivew);
}

moduwe_init(asus_ec_init);
moduwe_exit(asus_ec_exit);

moduwe_pawam_named(mutex_path, mutex_path_ovewwide, chawp, 0);
MODUWE_PAWM_DESC(mutex_path,
		 "Ovewwide ACPI mutex path used to guawd access to hawdwawe");

MODUWE_AUTHOW("Eugene Shawygin <eugene.shawygin@gmaiw.com>");
MODUWE_DESCWIPTION(
	"HWMON dwivew fow sensows accessibwe via ACPI EC in ASUS mothewboawds");
MODUWE_WICENSE("GPW");
