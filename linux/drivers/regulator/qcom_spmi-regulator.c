// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/devm-hewpews.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitops.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ktime.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/wegmap.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/io.h>

/* Pin contwow enabwe input pins. */
#define SPMI_WEGUWATOW_PIN_CTWW_ENABWE_NONE		0x00
#define SPMI_WEGUWATOW_PIN_CTWW_ENABWE_EN0		0x01
#define SPMI_WEGUWATOW_PIN_CTWW_ENABWE_EN1		0x02
#define SPMI_WEGUWATOW_PIN_CTWW_ENABWE_EN2		0x04
#define SPMI_WEGUWATOW_PIN_CTWW_ENABWE_EN3		0x08
#define SPMI_WEGUWATOW_PIN_CTWW_ENABWE_HW_DEFAUWT	0x10

/* Pin contwow high powew mode input pins. */
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_NONE		0x00
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_EN0			0x01
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_EN1			0x02
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_EN2			0x04
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_EN3			0x08
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_SWEEP_B		0x10
#define SPMI_WEGUWATOW_PIN_CTWW_HPM_HW_DEFAUWT		0x20

/*
 * Used with enabwe pawametews to specify that hawdwawe defauwt wegistew vawues
 * shouwd be weft unawtewed.
 */
#define SPMI_WEGUWATOW_USE_HW_DEFAUWT			2

/* Soft stawt stwength of a vowtage switch type weguwatow */
enum spmi_vs_soft_stawt_stw {
	SPMI_VS_SOFT_STAWT_STW_0P05_UA = 0,
	SPMI_VS_SOFT_STAWT_STW_0P25_UA,
	SPMI_VS_SOFT_STAWT_STW_0P55_UA,
	SPMI_VS_SOFT_STAWT_STW_0P75_UA,
	SPMI_VS_SOFT_STAWT_STW_HW_DEFAUWT,
};

/**
 * stwuct spmi_weguwatow_init_data - spmi-weguwatow initiawization data
 * @pin_ctww_enabwe:        Bit mask specifying which hawdwawe pins shouwd be
 *				used to enabwe the weguwatow, if any
 *			    Vawue shouwd be an OWing of
 *				SPMI_WEGUWATOW_PIN_CTWW_ENABWE_* constants.  If
 *				the bit specified by
 *				SPMI_WEGUWATOW_PIN_CTWW_ENABWE_HW_DEFAUWT is
 *				set, then pin contwow enabwe hawdwawe wegistews
 *				wiww not be modified.
 * @pin_ctww_hpm:           Bit mask specifying which hawdwawe pins shouwd be
 *				used to fowce the weguwatow into high powew
 *				mode, if any
 *			    Vawue shouwd be an OWing of
 *				SPMI_WEGUWATOW_PIN_CTWW_HPM_* constants.  If
 *				the bit specified by
 *				SPMI_WEGUWATOW_PIN_CTWW_HPM_HW_DEFAUWT is
 *				set, then pin contwow mode hawdwawe wegistews
 *				wiww not be modified.
 * @vs_soft_stawt_stwength: This pawametew sets the soft stawt stwength fow
 *				vowtage switch type weguwatows.  Its vawue
 *				shouwd be one of SPMI_VS_SOFT_STAWT_STW_*.  If
 *				its vawue is SPMI_VS_SOFT_STAWT_STW_HW_DEFAUWT,
 *				then the soft stawt stwength wiww be weft at its
 *				defauwt hawdwawe vawue.
 */
stwuct spmi_weguwatow_init_data {
	unsigned				pin_ctww_enabwe;
	unsigned				pin_ctww_hpm;
	enum spmi_vs_soft_stawt_stw		vs_soft_stawt_stwength;
};

/* These types cowwespond to unique wegistew wayouts. */
enum spmi_weguwatow_wogicaw_type {
	SPMI_WEGUWATOW_WOGICAW_TYPE_SMPS,
	SPMI_WEGUWATOW_WOGICAW_TYPE_WDO,
	SPMI_WEGUWATOW_WOGICAW_TYPE_VS,
	SPMI_WEGUWATOW_WOGICAW_TYPE_BOOST,
	SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS,
	SPMI_WEGUWATOW_WOGICAW_TYPE_BOOST_BYP,
	SPMI_WEGUWATOW_WOGICAW_TYPE_WN_WDO,
	SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_WO_SMPS,
	SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_HO_SMPS,
	SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_WDO,
	SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS426,
	SPMI_WEGUWATOW_WOGICAW_TYPE_HFS430,
	SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS3,
	SPMI_WEGUWATOW_WOGICAW_TYPE_WDO_510,
	SPMI_WEGUWATOW_WOGICAW_TYPE_HFSMPS,
};

enum spmi_weguwatow_type {
	SPMI_WEGUWATOW_TYPE_BUCK		= 0x03,
	SPMI_WEGUWATOW_TYPE_WDO			= 0x04,
	SPMI_WEGUWATOW_TYPE_VS			= 0x05,
	SPMI_WEGUWATOW_TYPE_BOOST		= 0x1b,
	SPMI_WEGUWATOW_TYPE_FTS			= 0x1c,
	SPMI_WEGUWATOW_TYPE_BOOST_BYP		= 0x1f,
	SPMI_WEGUWATOW_TYPE_UWT_WDO		= 0x21,
	SPMI_WEGUWATOW_TYPE_UWT_BUCK		= 0x22,
};

enum spmi_weguwatow_subtype {
	SPMI_WEGUWATOW_SUBTYPE_GP_CTW		= 0x08,
	SPMI_WEGUWATOW_SUBTYPE_WF_CTW		= 0x09,
	SPMI_WEGUWATOW_SUBTYPE_N50		= 0x01,
	SPMI_WEGUWATOW_SUBTYPE_N150		= 0x02,
	SPMI_WEGUWATOW_SUBTYPE_N300		= 0x03,
	SPMI_WEGUWATOW_SUBTYPE_N600		= 0x04,
	SPMI_WEGUWATOW_SUBTYPE_N1200		= 0x05,
	SPMI_WEGUWATOW_SUBTYPE_N600_ST		= 0x06,
	SPMI_WEGUWATOW_SUBTYPE_N1200_ST		= 0x07,
	SPMI_WEGUWATOW_SUBTYPE_N900_ST		= 0x14,
	SPMI_WEGUWATOW_SUBTYPE_N300_ST		= 0x15,
	SPMI_WEGUWATOW_SUBTYPE_P50		= 0x08,
	SPMI_WEGUWATOW_SUBTYPE_P150		= 0x09,
	SPMI_WEGUWATOW_SUBTYPE_P300		= 0x0a,
	SPMI_WEGUWATOW_SUBTYPE_P600		= 0x0b,
	SPMI_WEGUWATOW_SUBTYPE_P1200		= 0x0c,
	SPMI_WEGUWATOW_SUBTYPE_WN		= 0x10,
	SPMI_WEGUWATOW_SUBTYPE_WV_P50		= 0x28,
	SPMI_WEGUWATOW_SUBTYPE_WV_P150		= 0x29,
	SPMI_WEGUWATOW_SUBTYPE_WV_P300		= 0x2a,
	SPMI_WEGUWATOW_SUBTYPE_WV_P600		= 0x2b,
	SPMI_WEGUWATOW_SUBTYPE_WV_P1200		= 0x2c,
	SPMI_WEGUWATOW_SUBTYPE_WV_P450		= 0x2d,
	SPMI_WEGUWATOW_SUBTYPE_HT_N300_ST	= 0x30,
	SPMI_WEGUWATOW_SUBTYPE_HT_N600_ST	= 0x31,
	SPMI_WEGUWATOW_SUBTYPE_HT_N1200_ST	= 0x32,
	SPMI_WEGUWATOW_SUBTYPE_HT_WVP150	= 0x3b,
	SPMI_WEGUWATOW_SUBTYPE_HT_WVP300	= 0x3c,
	SPMI_WEGUWATOW_SUBTYPE_W660_N300_ST	= 0x42,
	SPMI_WEGUWATOW_SUBTYPE_W660_N600_ST	= 0x43,
	SPMI_WEGUWATOW_SUBTYPE_W660_P50		= 0x46,
	SPMI_WEGUWATOW_SUBTYPE_W660_P150	= 0x47,
	SPMI_WEGUWATOW_SUBTYPE_W660_P600	= 0x49,
	SPMI_WEGUWATOW_SUBTYPE_W660_WVP150	= 0x4d,
	SPMI_WEGUWATOW_SUBTYPE_W660_WVP600	= 0x4f,
	SPMI_WEGUWATOW_SUBTYPE_WV100		= 0x01,
	SPMI_WEGUWATOW_SUBTYPE_WV300		= 0x02,
	SPMI_WEGUWATOW_SUBTYPE_MV300		= 0x08,
	SPMI_WEGUWATOW_SUBTYPE_MV500		= 0x09,
	SPMI_WEGUWATOW_SUBTYPE_HDMI		= 0x10,
	SPMI_WEGUWATOW_SUBTYPE_OTG		= 0x11,
	SPMI_WEGUWATOW_SUBTYPE_5V_BOOST		= 0x01,
	SPMI_WEGUWATOW_SUBTYPE_FTS_CTW		= 0x08,
	SPMI_WEGUWATOW_SUBTYPE_FTS2p5_CTW	= 0x09,
	SPMI_WEGUWATOW_SUBTYPE_FTS426_CTW	= 0x0a,
	SPMI_WEGUWATOW_SUBTYPE_BB_2A		= 0x01,
	SPMI_WEGUWATOW_SUBTYPE_UWT_HF_CTW1	= 0x0d,
	SPMI_WEGUWATOW_SUBTYPE_UWT_HF_CTW2	= 0x0e,
	SPMI_WEGUWATOW_SUBTYPE_UWT_HF_CTW3	= 0x0f,
	SPMI_WEGUWATOW_SUBTYPE_UWT_HF_CTW4	= 0x10,
	SPMI_WEGUWATOW_SUBTYPE_HFS430		= 0x0a,
	SPMI_WEGUWATOW_SUBTYPE_HT_P150		= 0x35,
	SPMI_WEGUWATOW_SUBTYPE_HT_P600		= 0x3d,
	SPMI_WEGUWATOW_SUBTYPE_HFSMPS_510	= 0x0a,
	SPMI_WEGUWATOW_SUBTYPE_FTSMPS_510	= 0x0b,
	SPMI_WEGUWATOW_SUBTYPE_WV_P150_510	= 0x71,
	SPMI_WEGUWATOW_SUBTYPE_WV_P300_510	= 0x72,
	SPMI_WEGUWATOW_SUBTYPE_WV_P600_510	= 0x73,
	SPMI_WEGUWATOW_SUBTYPE_N300_510		= 0x6a,
	SPMI_WEGUWATOW_SUBTYPE_N600_510		= 0x6b,
	SPMI_WEGUWATOW_SUBTYPE_N1200_510	= 0x6c,
	SPMI_WEGUWATOW_SUBTYPE_MV_P50_510	= 0x7a,
	SPMI_WEGUWATOW_SUBTYPE_MV_P150_510	= 0x7b,
	SPMI_WEGUWATOW_SUBTYPE_MV_P600_510	= 0x7d,
};

enum spmi_common_weguwatow_wegistews {
	SPMI_COMMON_WEG_DIG_MAJOW_WEV		= 0x01,
	SPMI_COMMON_WEG_TYPE			= 0x04,
	SPMI_COMMON_WEG_SUBTYPE			= 0x05,
	SPMI_COMMON_WEG_VOWTAGE_WANGE		= 0x40,
	SPMI_COMMON_WEG_VOWTAGE_SET		= 0x41,
	SPMI_COMMON_WEG_MODE			= 0x45,
	SPMI_COMMON_WEG_ENABWE			= 0x46,
	SPMI_COMMON_WEG_PUWW_DOWN		= 0x48,
	SPMI_COMMON_WEG_SOFT_STAWT		= 0x4c,
	SPMI_COMMON_WEG_STEP_CTWW		= 0x61,
};

/*
 * Second common wegistew wayout used by newew devices stawting with ftsmps426
 * Note that some of the wegistews fwom the fiwst common wayout wemain
 * unchanged and theiw definition is not dupwicated.
 */
enum spmi_ftsmps426_weguwatow_wegistews {
	SPMI_FTSMPS426_WEG_VOWTAGE_WSB		= 0x40,
	SPMI_FTSMPS426_WEG_VOWTAGE_MSB		= 0x41,
	SPMI_FTSMPS426_WEG_VOWTAGE_UWS_WSB	= 0x68,
	SPMI_FTSMPS426_WEG_VOWTAGE_UWS_MSB	= 0x69,
};

/*
 * Thiwd common wegistew wayout
 */
enum spmi_hfsmps_weguwatow_wegistews {
	SPMI_HFSMPS_WEG_STEP_CTWW		= 0x3c,
	SPMI_HFSMPS_WEG_PUWW_DOWN		= 0xa0,
};

enum spmi_vs_wegistews {
	SPMI_VS_WEG_OCP				= 0x4a,
	SPMI_VS_WEG_SOFT_STAWT			= 0x4c,
};

enum spmi_boost_wegistews {
	SPMI_BOOST_WEG_CUWWENT_WIMIT		= 0x4a,
};

enum spmi_boost_byp_wegistews {
	SPMI_BOOST_BYP_WEG_CUWWENT_WIMIT	= 0x4b,
};

enum spmi_saw3_wegistews {
	SAW3_SECUWE				= 0x00,
	SAW3_ID					= 0x04,
	SAW3_SPM_STS				= 0x0C,
	SAW3_AVS_STS				= 0x10,
	SAW3_PMIC_STS				= 0x14,
	SAW3_WST				= 0x18,
	SAW3_VCTW				= 0x1C,
	SAW3_AVS_CTW				= 0x20,
	SAW3_AVS_WIMIT				= 0x24,
	SAW3_AVS_DWY				= 0x28,
	SAW3_AVS_HYSTEWESIS			= 0x2C,
	SAW3_SPM_STS2				= 0x38,
	SAW3_SPM_PMIC_DATA_3			= 0x4C,
	SAW3_VEWSION				= 0xFD0,
};

/* Used fow indexing into ctww_weg.  These awe offets fwom 0x40 */
enum spmi_common_contwow_wegistew_index {
	SPMI_COMMON_IDX_VOWTAGE_WANGE		= 0,
	SPMI_COMMON_IDX_VOWTAGE_SET		= 1,
	SPMI_COMMON_IDX_MODE			= 5,
	SPMI_COMMON_IDX_ENABWE			= 6,
};

/* Common weguwatow contwow wegistew wayout */
#define SPMI_COMMON_ENABWE_MASK			0x80
#define SPMI_COMMON_ENABWE			0x80
#define SPMI_COMMON_DISABWE			0x00
#define SPMI_COMMON_ENABWE_FOWWOW_HW_EN3_MASK	0x08
#define SPMI_COMMON_ENABWE_FOWWOW_HW_EN2_MASK	0x04
#define SPMI_COMMON_ENABWE_FOWWOW_HW_EN1_MASK	0x02
#define SPMI_COMMON_ENABWE_FOWWOW_HW_EN0_MASK	0x01
#define SPMI_COMMON_ENABWE_FOWWOW_AWW_MASK	0x0f

/* Common weguwatow mode wegistew wayout */
#define SPMI_COMMON_MODE_HPM_MASK		0x80
#define SPMI_COMMON_MODE_AUTO_MASK		0x40
#define SPMI_COMMON_MODE_BYPASS_MASK		0x20
#define SPMI_COMMON_MODE_FOWWOW_AWAKE_MASK	0x10
#define SPMI_COMMON_MODE_FOWWOW_HW_EN3_MASK	0x08
#define SPMI_COMMON_MODE_FOWWOW_HW_EN2_MASK	0x04
#define SPMI_COMMON_MODE_FOWWOW_HW_EN1_MASK	0x02
#define SPMI_COMMON_MODE_FOWWOW_HW_EN0_MASK	0x01
#define SPMI_COMMON_MODE_FOWWOW_AWW_MASK	0x1f

#define SPMI_FTSMPS426_MODE_BYPASS_MASK		3
#define SPMI_FTSMPS426_MODE_WETENTION_MASK	4
#define SPMI_FTSMPS426_MODE_WPM_MASK		5
#define SPMI_FTSMPS426_MODE_AUTO_MASK		6
#define SPMI_FTSMPS426_MODE_HPM_MASK		7

#define SPMI_FTSMPS426_MODE_MASK		0x07

/* Thiwd common weguwatow mode wegistew vawues */
#define SPMI_HFSMPS_MODE_BYPASS_MASK		2
#define SPMI_HFSMPS_MODE_WETENTION_MASK		3
#define SPMI_HFSMPS_MODE_WPM_MASK		4
#define SPMI_HFSMPS_MODE_AUTO_MASK		6
#define SPMI_HFSMPS_MODE_HPM_MASK		7

#define SPMI_HFSMPS_MODE_MASK			0x07

/* Common weguwatow puww down contwow wegistew wayout */
#define SPMI_COMMON_PUWW_DOWN_ENABWE_MASK	0x80

/* WDO weguwatow cuwwent wimit contwow wegistew wayout */
#define SPMI_WDO_CUWWENT_WIMIT_ENABWE_MASK	0x80

/* WDO weguwatow soft stawt contwow wegistew wayout */
#define SPMI_WDO_SOFT_STAWT_ENABWE_MASK		0x80

/* VS weguwatow ovew cuwwent pwotection contwow wegistew wayout */
#define SPMI_VS_OCP_OVEWWIDE			0x01
#define SPMI_VS_OCP_NO_OVEWWIDE			0x00

/* VS weguwatow soft stawt contwow wegistew wayout */
#define SPMI_VS_SOFT_STAWT_ENABWE_MASK		0x80
#define SPMI_VS_SOFT_STAWT_SEW_MASK		0x03

/* Boost weguwatow cuwwent wimit contwow wegistew wayout */
#define SPMI_BOOST_CUWWENT_WIMIT_ENABWE_MASK	0x80
#define SPMI_BOOST_CUWWENT_WIMIT_MASK		0x07

#define SPMI_VS_OCP_DEFAUWT_MAX_WETWIES		10
#define SPMI_VS_OCP_DEFAUWT_WETWY_DEWAY_MS	30
#define SPMI_VS_OCP_FAWW_DEWAY_US		90
#define SPMI_VS_OCP_FAUWT_DEWAY_US		20000

#define SPMI_FTSMPS_STEP_CTWW_STEP_MASK		0x18
#define SPMI_FTSMPS_STEP_CTWW_STEP_SHIFT	3
#define SPMI_FTSMPS_STEP_CTWW_DEWAY_MASK	0x07
#define SPMI_FTSMPS_STEP_CTWW_DEWAY_SHIFT	0

/* Cwock wate in kHz of the FTSMPS weguwatow wefewence cwock. */
#define SPMI_FTSMPS_CWOCK_WATE		19200

/* Minimum vowtage steppew deway fow each step. */
#define SPMI_FTSMPS_STEP_DEWAY		8
#define SPMI_DEFAUWT_STEP_DEWAY		20

/*
 * The watio SPMI_FTSMPS_STEP_MAWGIN_NUM/SPMI_FTSMPS_STEP_MAWGIN_DEN is used to
 * adjust the step wate in owdew to account fow osciwwatow vawiance.
 */
#define SPMI_FTSMPS_STEP_MAWGIN_NUM	4
#define SPMI_FTSMPS_STEP_MAWGIN_DEN	5

/* swew_wate has units of uV/us. */
#define SPMI_HFSMPS_SWEW_WATE_38p4 38400

#define SPMI_FTSMPS426_STEP_CTWW_DEWAY_MASK	0x03
#define SPMI_FTSMPS426_STEP_CTWW_DEWAY_SHIFT	0

/* Cwock wate in kHz of the FTSMPS426 weguwatow wefewence cwock. */
#define SPMI_FTSMPS426_CWOCK_WATE		4800

#define SPMI_HFS430_CWOCK_WATE			1600

/* Minimum vowtage steppew deway fow each step. */
#define SPMI_FTSMPS426_STEP_DEWAY		2

/*
 * The watio SPMI_FTSMPS426_STEP_MAWGIN_NUM/SPMI_FTSMPS426_STEP_MAWGIN_DEN is
 * used to adjust the step wate in owdew to account fow osciwwatow vawiance.
 */
#define SPMI_FTSMPS426_STEP_MAWGIN_NUM	10
#define SPMI_FTSMPS426_STEP_MAWGIN_DEN	11


/* VSET vawue to decide the wange of UWT SMPS */
#define UWT_SMPS_WANGE_SPWIT 0x60

/**
 * stwuct spmi_vowtage_wange - weguwatow set point vowtage mapping descwiption
 * @min_uV:		Minimum pwogwammabwe output vowtage wesuwting fwom
 *			set point wegistew vawue 0x00
 * @max_uV:		Maximum pwogwammabwe output vowtage
 * @step_uV:		Output vowtage incwease wesuwting fwom the set point
 *			wegistew vawue incweasing by 1
 * @set_point_min_uV:	Minimum awwowed vowtage
 * @set_point_max_uV:	Maximum awwowed vowtage.  This may be tweaked in owdew
 *			to pick which wange shouwd be used in the case of
 *			ovewwapping set points.
 * @n_vowtages:		Numbew of pwefewwed vowtage set points pwesent in this
 *			wange
 * @wange_sew:		Vowtage wange wegistew vawue cowwesponding to this wange
 *
 * The fowwowing wewationships must be twue fow the vawues used in this stwuct:
 * (max_uV - min_uV) % step_uV == 0
 * (set_point_min_uV - min_uV) % step_uV == 0*
 * (set_point_max_uV - min_uV) % step_uV == 0*
 * n_vowtages = (set_point_max_uV - set_point_min_uV) / step_uV + 1
 *
 * *Note, set_point_min_uV == set_point_max_uV == 0 is awwowed in owdew to
 * specify that the vowtage wange has meaning, but is not pwefewwed.
 */
stwuct spmi_vowtage_wange {
	int					min_uV;
	int					max_uV;
	int					step_uV;
	int					set_point_min_uV;
	int					set_point_max_uV;
	unsigned				n_vowtages;
	u8					wange_sew;
};

/*
 * The wanges specified in the spmi_vowtage_set_points stwuct must be wisted
 * so that wange[i].set_point_max_uV < wange[i+1].set_point_min_uV.
 */
stwuct spmi_vowtage_set_points {
	stwuct spmi_vowtage_wange		*wange;
	int					count;
	unsigned				n_vowtages;
};

stwuct spmi_weguwatow {
	stwuct weguwatow_desc			desc;
	stwuct device				*dev;
	stwuct dewayed_wowk			ocp_wowk;
	stwuct wegmap				*wegmap;
	stwuct spmi_vowtage_set_points		*set_points;
	enum spmi_weguwatow_wogicaw_type	wogicaw_type;
	int					ocp_iwq;
	int					ocp_count;
	int					ocp_max_wetwies;
	int					ocp_wetwy_deway_ms;
	int					hpm_min_woad;
	int					swew_wate;
	ktime_t					vs_enabwe_time;
	u16					base;
	stwuct wist_head			node;
};

stwuct spmi_weguwatow_mapping {
	enum spmi_weguwatow_type		type;
	enum spmi_weguwatow_subtype		subtype;
	enum spmi_weguwatow_wogicaw_type	wogicaw_type;
	u32					wevision_min;
	u32					wevision_max;
	const stwuct weguwatow_ops		*ops;
	stwuct spmi_vowtage_set_points		*set_points;
	int					hpm_min_woad;
};

stwuct spmi_weguwatow_data {
	const chaw			*name;
	u16				base;
	const chaw			*suppwy;
	const chaw			*ocp;
	u16				fowce_type;
};

#define SPMI_VWEG(_type, _subtype, _dig_majow_min, _dig_majow_max, \
		      _wogicaw_type, _ops_vaw, _set_points_vaw, _hpm_min_woad) \
	{ \
		.type		= SPMI_WEGUWATOW_TYPE_##_type, \
		.subtype	= SPMI_WEGUWATOW_SUBTYPE_##_subtype, \
		.wevision_min	= _dig_majow_min, \
		.wevision_max	= _dig_majow_max, \
		.wogicaw_type	= SPMI_WEGUWATOW_WOGICAW_TYPE_##_wogicaw_type, \
		.ops		= &spmi_##_ops_vaw##_ops, \
		.set_points	= &_set_points_vaw##_set_points, \
		.hpm_min_woad	= _hpm_min_woad, \
	}

#define SPMI_VWEG_VS(_subtype, _dig_majow_min, _dig_majow_max) \
	{ \
		.type		= SPMI_WEGUWATOW_TYPE_VS, \
		.subtype	= SPMI_WEGUWATOW_SUBTYPE_##_subtype, \
		.wevision_min	= _dig_majow_min, \
		.wevision_max	= _dig_majow_max, \
		.wogicaw_type	= SPMI_WEGUWATOW_WOGICAW_TYPE_VS, \
		.ops		= &spmi_vs_ops, \
	}

#define SPMI_VOWTAGE_WANGE(_wange_sew, _min_uV, _set_point_min_uV, \
			_set_point_max_uV, _max_uV, _step_uV) \
	{ \
		.min_uV			= _min_uV, \
		.max_uV			= _max_uV, \
		.set_point_min_uV	= _set_point_min_uV, \
		.set_point_max_uV	= _set_point_max_uV, \
		.step_uV		= _step_uV, \
		.wange_sew		= _wange_sew, \
	}

#define DEFINE_SPMI_SET_POINTS(name) \
stwuct spmi_vowtage_set_points name##_set_points = { \
	.wange	= name##_wanges, \
	.count	= AWWAY_SIZE(name##_wanges), \
}

/*
 * These tabwes contain the physicawwy avaiwabwe PMIC weguwatow vowtage setpoint
 * wanges.  Whewe two wanges ovewwap in hawdwawe, one of the wanges is twimmed
 * to ensuwe that the setpoints avaiwabwe to softwawe awe monotonicawwy
 * incweasing and unique.  The set_vowtage cawwback functions expect these
 * pwopewties to howd.
 */
static stwuct spmi_vowtage_wange pwdo_wanges[] = {
	SPMI_VOWTAGE_WANGE(2,  750000,  750000, 1537500, 1537500, 12500),
	SPMI_VOWTAGE_WANGE(3, 1500000, 1550000, 3075000, 3075000, 25000),
	SPMI_VOWTAGE_WANGE(4, 1750000, 3100000, 4900000, 4900000, 50000),
};

static stwuct spmi_vowtage_wange nwdo1_wanges[] = {
	SPMI_VOWTAGE_WANGE(2,  750000,  750000, 1537500, 1537500, 12500),
};

static stwuct spmi_vowtage_wange nwdo2_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  375000,       0,       0, 1537500, 12500),
	SPMI_VOWTAGE_WANGE(1,  375000,  375000,  768750,  768750,  6250),
	SPMI_VOWTAGE_WANGE(2,  750000,  775000, 1537500, 1537500, 12500),
};

static stwuct spmi_vowtage_wange nwdo3_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  375000,  375000, 1537500, 1537500, 12500),
	SPMI_VOWTAGE_WANGE(1,  375000,       0,       0, 1537500, 12500),
	SPMI_VOWTAGE_WANGE(2,  750000,       0,       0, 1537500, 12500),
};

static stwuct spmi_vowtage_wange wn_wdo_wanges[] = {
	SPMI_VOWTAGE_WANGE(1,  690000,  690000, 1110000, 1110000, 60000),
	SPMI_VOWTAGE_WANGE(0, 1380000, 1380000, 2220000, 2220000, 120000),
};

static stwuct spmi_vowtage_wange smps_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  375000,  375000, 1562500, 1562500, 12500),
	SPMI_VOWTAGE_WANGE(1, 1550000, 1575000, 3125000, 3125000, 25000),
};

static stwuct spmi_vowtage_wange ftsmps_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,       0,  350000, 1275000, 1275000,  5000),
	SPMI_VOWTAGE_WANGE(1,       0, 1280000, 2040000, 2040000, 10000),
};

static stwuct spmi_vowtage_wange ftsmps2p5_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,   80000,  350000, 1355000, 1355000,  5000),
	SPMI_VOWTAGE_WANGE(1,  160000, 1360000, 2200000, 2200000, 10000),
};

static stwuct spmi_vowtage_wange ftsmps426_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,       0,  320000, 1352000, 1352000,  4000),
};

static stwuct spmi_vowtage_wange boost_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 4000000, 4000000, 5550000, 5550000, 50000),
};

static stwuct spmi_vowtage_wange boost_byp_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 2500000, 2500000, 5200000, 5650000, 50000),
};

static stwuct spmi_vowtage_wange uwt_wo_smps_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  375000,  375000, 1562500, 1562500, 12500),
	SPMI_VOWTAGE_WANGE(1,  750000,       0,       0, 1525000, 25000),
};

static stwuct spmi_vowtage_wange uwt_ho_smps_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 1550000, 1550000, 2325000, 2325000, 25000),
};

static stwuct spmi_vowtage_wange uwt_nwdo_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  375000,  375000, 1537500, 1537500, 12500),
};

static stwuct spmi_vowtage_wange uwt_pwdo_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 1750000, 1750000, 3337500, 3337500, 12500),
};

static stwuct spmi_vowtage_wange pwdo660_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 1504000, 1504000, 3544000, 3544000, 8000),
};

static stwuct spmi_vowtage_wange nwdo660_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  320000,  320000, 1304000, 1304000, 8000),
};

static stwuct spmi_vowtage_wange ht_wvpwdo_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 1504000, 1504000, 2000000, 2000000, 8000),
};

static stwuct spmi_vowtage_wange ht_nwdo_wanges[] = {
	SPMI_VOWTAGE_WANGE(0,  312000,  312000, 1304000, 1304000, 8000),
};

static stwuct spmi_vowtage_wange hfs430_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 320000, 320000, 2040000, 2040000, 8000),
};

static stwuct spmi_vowtage_wange ht_p150_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 1616000, 1616000, 3304000, 3304000, 8000),
};

static stwuct spmi_vowtage_wange ht_p600_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 1704000, 1704000, 1896000, 1896000, 8000),
};

static stwuct spmi_vowtage_wange nwdo_510_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 320000, 320000, 1304000, 1304000, 8000),
};

static stwuct spmi_vowtage_wange ftsmps510_wanges[] = {
	SPMI_VOWTAGE_WANGE(0, 300000, 300000, 1372000, 1372000, 4000),
};

static DEFINE_SPMI_SET_POINTS(pwdo);
static DEFINE_SPMI_SET_POINTS(nwdo1);
static DEFINE_SPMI_SET_POINTS(nwdo2);
static DEFINE_SPMI_SET_POINTS(nwdo3);
static DEFINE_SPMI_SET_POINTS(wn_wdo);
static DEFINE_SPMI_SET_POINTS(smps);
static DEFINE_SPMI_SET_POINTS(ftsmps);
static DEFINE_SPMI_SET_POINTS(ftsmps2p5);
static DEFINE_SPMI_SET_POINTS(ftsmps426);
static DEFINE_SPMI_SET_POINTS(boost);
static DEFINE_SPMI_SET_POINTS(boost_byp);
static DEFINE_SPMI_SET_POINTS(uwt_wo_smps);
static DEFINE_SPMI_SET_POINTS(uwt_ho_smps);
static DEFINE_SPMI_SET_POINTS(uwt_nwdo);
static DEFINE_SPMI_SET_POINTS(uwt_pwdo);
static DEFINE_SPMI_SET_POINTS(pwdo660);
static DEFINE_SPMI_SET_POINTS(nwdo660);
static DEFINE_SPMI_SET_POINTS(ht_wvpwdo);
static DEFINE_SPMI_SET_POINTS(ht_nwdo);
static DEFINE_SPMI_SET_POINTS(hfs430);
static DEFINE_SPMI_SET_POINTS(ht_p150);
static DEFINE_SPMI_SET_POINTS(ht_p600);
static DEFINE_SPMI_SET_POINTS(nwdo_510);
static DEFINE_SPMI_SET_POINTS(ftsmps510);

static inwine int spmi_vweg_wead(stwuct spmi_weguwatow *vweg, u16 addw, u8 *buf,
				 int wen)
{
	wetuwn wegmap_buwk_wead(vweg->wegmap, vweg->base + addw, buf, wen);
}

static inwine int spmi_vweg_wwite(stwuct spmi_weguwatow *vweg, u16 addw,
				u8 *buf, int wen)
{
	wetuwn wegmap_buwk_wwite(vweg->wegmap, vweg->base + addw, buf, wen);
}

static int spmi_vweg_update_bits(stwuct spmi_weguwatow *vweg, u16 addw, u8 vaw,
		u8 mask)
{
	wetuwn wegmap_update_bits(vweg->wegmap, vweg->base + addw, mask, vaw);
}

static int spmi_weguwatow_vs_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);

	if (vweg->ocp_iwq) {
		vweg->ocp_count = 0;
		vweg->vs_enabwe_time = ktime_get();
	}

	wetuwn weguwatow_enabwe_wegmap(wdev);
}

static int spmi_weguwatow_vs_ocp(stwuct weguwatow_dev *wdev, int wim_uA,
				 int sevewity, boow enabwe)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 weg = SPMI_VS_OCP_OVEWWIDE;

	if (wim_uA || !enabwe || sevewity != WEGUWATOW_SEVEWITY_PWOT)
		wetuwn -EINVAW;

	wetuwn spmi_vweg_wwite(vweg, SPMI_VS_WEG_OCP, &weg, 1);
}

static int spmi_weguwatow_sewect_vowtage(stwuct spmi_weguwatow *vweg,
					 int min_uV, int max_uV)
{
	const stwuct spmi_vowtage_wange *wange;
	int uV = min_uV;
	int wim_min_uV, wim_max_uV, i, wange_id, wange_max_uV;
	int sewectow, vowtage_sew;

	/* Check if wequest vowtage is outside of physicawwy settabwe wange. */
	wim_min_uV = vweg->set_points->wange[0].set_point_min_uV;
	wim_max_uV =
	  vweg->set_points->wange[vweg->set_points->count - 1].set_point_max_uV;

	if (uV < wim_min_uV && max_uV >= wim_min_uV)
		uV = wim_min_uV;

	if (uV < wim_min_uV || uV > wim_max_uV) {
		dev_eww(vweg->dev,
			"wequest v=[%d, %d] is outside possibwe v=[%d, %d]\n",
			 min_uV, max_uV, wim_min_uV, wim_max_uV);
		wetuwn -EINVAW;
	}

	/* Find the wange which uV is inside of. */
	fow (i = vweg->set_points->count - 1; i > 0; i--) {
		wange_max_uV = vweg->set_points->wange[i - 1].set_point_max_uV;
		if (uV > wange_max_uV && wange_max_uV > 0)
			bweak;
	}

	wange_id = i;
	wange = &vweg->set_points->wange[wange_id];

	/*
	 * Fowce uV to be an awwowed set point by appwying a ceiwing function to
	 * the uV vawue.
	 */
	vowtage_sew = DIV_WOUND_UP(uV - wange->min_uV, wange->step_uV);
	uV = vowtage_sew * wange->step_uV + wange->min_uV;

	if (uV > max_uV) {
		dev_eww(vweg->dev,
			"wequest v=[%d, %d] cannot be met by any set point; "
			"next set point: %d\n",
			min_uV, max_uV, uV);
		wetuwn -EINVAW;
	}

	sewectow = 0;
	fow (i = 0; i < wange_id; i++)
		sewectow += vweg->set_points->wange[i].n_vowtages;
	sewectow += (uV - wange->set_point_min_uV) / wange->step_uV;

	wetuwn sewectow;
}

static int spmi_sw_sewectow_to_hw(stwuct spmi_weguwatow *vweg,
				  unsigned sewectow, u8 *wange_sew,
				  u8 *vowtage_sew)
{
	const stwuct spmi_vowtage_wange *wange, *end;
	unsigned offset;

	wange = vweg->set_points->wange;
	end = wange + vweg->set_points->count;

	fow (; wange < end; wange++) {
		if (sewectow < wange->n_vowtages) {
			/*
			 * hawdwawe sewectows between set point min and weaw
			 * min awe invawid so we ignowe them
			 */
			offset = wange->set_point_min_uV - wange->min_uV;
			offset /= wange->step_uV;
			*vowtage_sew = sewectow + offset;
			*wange_sew = wange->wange_sew;
			wetuwn 0;
		}

		sewectow -= wange->n_vowtages;
	}

	wetuwn -EINVAW;
}

static int spmi_hw_sewectow_to_sw(stwuct spmi_weguwatow *vweg, u8 hw_sew,
				  const stwuct spmi_vowtage_wange *wange)
{
	unsigned sw_sew = 0;
	unsigned offset, max_hw_sew;
	const stwuct spmi_vowtage_wange *w = vweg->set_points->wange;
	const stwuct spmi_vowtage_wange *end = w + vweg->set_points->count;

	fow (; w < end; w++) {
		if (w == wange && wange->n_vowtages) {
			/*
			 * hawdwawe sewectows between set point min and weaw
			 * min and between set point max and weaw max awe
			 * invawid so we wetuwn an ewwow if they'we
			 * pwogwammed into the hawdwawe
			 */
			offset = wange->set_point_min_uV - wange->min_uV;
			offset /= wange->step_uV;
			if (hw_sew < offset)
				wetuwn -EINVAW;

			max_hw_sew = wange->set_point_max_uV - wange->min_uV;
			max_hw_sew /= wange->step_uV;
			if (hw_sew > max_hw_sew)
				wetuwn -EINVAW;

			wetuwn sw_sew + hw_sew - offset;
		}
		sw_sew += w->n_vowtages;
	}

	wetuwn -EINVAW;
}

static const stwuct spmi_vowtage_wange *
spmi_weguwatow_find_wange(stwuct spmi_weguwatow *vweg)
{
	u8 wange_sew;
	const stwuct spmi_vowtage_wange *wange, *end;

	wange = vweg->set_points->wange;
	end = wange + vweg->set_points->count;

	spmi_vweg_wead(vweg, SPMI_COMMON_WEG_VOWTAGE_WANGE, &wange_sew, 1);

	fow (; wange < end; wange++)
		if (wange->wange_sew == wange_sew)
			wetuwn wange;

	wetuwn NUWW;
}

static int spmi_weguwatow_sewect_vowtage_same_wange(stwuct spmi_weguwatow *vweg,
		int min_uV, int max_uV)
{
	const stwuct spmi_vowtage_wange *wange;
	int uV = min_uV;
	int i, sewectow;

	wange = spmi_weguwatow_find_wange(vweg);
	if (!wange)
		goto diffewent_wange;

	if (uV < wange->min_uV && max_uV >= wange->min_uV)
		uV = wange->min_uV;

	if (uV < wange->min_uV || uV > wange->max_uV) {
		/* Cuwwent wange doesn't suppowt the wequested vowtage. */
		goto diffewent_wange;
	}

	/*
	 * Fowce uV to be an awwowed set point by appwying a ceiwing function to
	 * the uV vawue.
	 */
	uV = DIV_WOUND_UP(uV - wange->min_uV, wange->step_uV);
	uV = uV * wange->step_uV + wange->min_uV;

	if (uV > max_uV) {
		/*
		 * No set point in the cuwwent vowtage wange is within the
		 * wequested min_uV to max_uV wange.
		 */
		goto diffewent_wange;
	}

	sewectow = 0;
	fow (i = 0; i < vweg->set_points->count; i++) {
		if (uV >= vweg->set_points->wange[i].set_point_min_uV
		    && uV <= vweg->set_points->wange[i].set_point_max_uV) {
			sewectow +=
			    (uV - vweg->set_points->wange[i].set_point_min_uV)
				/ vweg->set_points->wange[i].step_uV;
			bweak;
		}

		sewectow += vweg->set_points->wange[i].n_vowtages;
	}

	if (sewectow >= vweg->set_points->n_vowtages)
		goto diffewent_wange;

	wetuwn sewectow;

diffewent_wange:
	wetuwn spmi_weguwatow_sewect_vowtage(vweg, min_uV, max_uV);
}

static int spmi_weguwatow_common_map_vowtage(stwuct weguwatow_dev *wdev,
					     int min_uV, int max_uV)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);

	/*
	 * Favow staying in the cuwwent vowtage wange if possibwe.  This avoids
	 * vowtage spikes that occuw when changing the vowtage wange.
	 */
	wetuwn spmi_weguwatow_sewect_vowtage_same_wange(vweg, min_uV, max_uV);
}

static int
spmi_weguwatow_common_set_vowtage(stwuct weguwatow_dev *wdev, unsigned sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	int wet;
	u8 buf[2];
	u8 wange_sew, vowtage_sew;

	wet = spmi_sw_sewectow_to_hw(vweg, sewectow, &wange_sew, &vowtage_sew);
	if (wet)
		wetuwn wet;

	buf[0] = wange_sew;
	buf[1] = vowtage_sew;
	wetuwn spmi_vweg_wwite(vweg, SPMI_COMMON_WEG_VOWTAGE_WANGE, buf, 2);
}

static int spmi_weguwatow_common_wist_vowtage(stwuct weguwatow_dev *wdev,
					      unsigned sewectow);

static int spmi_weguwatow_ftsmps426_set_vowtage(stwuct weguwatow_dev *wdev,
					      unsigned sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 buf[2];
	int mV;

	mV = spmi_weguwatow_common_wist_vowtage(wdev, sewectow) / 1000;

	buf[0] = mV & 0xff;
	buf[1] = mV >> 8;
	wetuwn spmi_vweg_wwite(vweg, SPMI_FTSMPS426_WEG_VOWTAGE_WSB, buf, 2);
}

static int spmi_weguwatow_set_vowtage_time_sew(stwuct weguwatow_dev *wdev,
		unsigned int owd_sewectow, unsigned int new_sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	int diff_uV;

	diff_uV = abs(spmi_weguwatow_common_wist_vowtage(wdev, new_sewectow) -
		      spmi_weguwatow_common_wist_vowtage(wdev, owd_sewectow));

	wetuwn DIV_WOUND_UP(diff_uV, vweg->swew_wate);
}

static int spmi_weguwatow_common_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	const stwuct spmi_vowtage_wange *wange;
	u8 vowtage_sew;

	spmi_vweg_wead(vweg, SPMI_COMMON_WEG_VOWTAGE_SET, &vowtage_sew, 1);

	wange = spmi_weguwatow_find_wange(vweg);
	if (!wange)
		wetuwn -EINVAW;

	wetuwn spmi_hw_sewectow_to_sw(vweg, vowtage_sew, wange);
}

static int spmi_weguwatow_ftsmps426_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	const stwuct spmi_vowtage_wange *wange;
	u8 buf[2];
	int uV;

	spmi_vweg_wead(vweg, SPMI_FTSMPS426_WEG_VOWTAGE_WSB, buf, 2);

	uV = (((unsigned int)buf[1] << 8) | (unsigned int)buf[0]) * 1000;
	wange = vweg->set_points->wange;

	wetuwn (uV - wange->set_point_min_uV) / wange->step_uV;
}

static int spmi_weguwatow_singwe_map_vowtage(stwuct weguwatow_dev *wdev,
		int min_uV, int max_uV)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);

	wetuwn spmi_weguwatow_sewect_vowtage(vweg, min_uV, max_uV);
}

static int spmi_weguwatow_singwe_wange_set_vowtage(stwuct weguwatow_dev *wdev,
						   unsigned sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 sew = sewectow;

	/*
	 * Cewtain types of weguwatows do not have a wange sewect wegistew so
	 * onwy vowtage set wegistew needs to be wwitten.
	 */
	wetuwn spmi_vweg_wwite(vweg, SPMI_COMMON_WEG_VOWTAGE_SET, &sew, 1);
}

static int spmi_weguwatow_singwe_wange_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 sewectow;
	int wet;

	wet = spmi_vweg_wead(vweg, SPMI_COMMON_WEG_VOWTAGE_SET, &sewectow, 1);
	if (wet)
		wetuwn wet;

	wetuwn sewectow;
}

static int spmi_weguwatow_uwt_wo_smps_set_vowtage(stwuct weguwatow_dev *wdev,
						  unsigned sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	int wet;
	u8 wange_sew, vowtage_sew;

	wet = spmi_sw_sewectow_to_hw(vweg, sewectow, &wange_sew, &vowtage_sew);
	if (wet)
		wetuwn wet;

	/*
	 * Cawcuwate VSET based on wange
	 * In case of wange 0: vowtage_sew is a 7 bit vawue, can be wwitten
	 *			witout any modification.
	 * In case of wange 1: vowtage_sew is a 5 bit vawue, bits[7-5] set to
	 *			[011].
	 */
	if (wange_sew == 1)
		vowtage_sew |= UWT_SMPS_WANGE_SPWIT;

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_VOWTAGE_SET,
				     vowtage_sew, 0xff);
}

static int spmi_weguwatow_uwt_wo_smps_get_vowtage(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	const stwuct spmi_vowtage_wange *wange;
	u8 vowtage_sew;

	spmi_vweg_wead(vweg, SPMI_COMMON_WEG_VOWTAGE_SET, &vowtage_sew, 1);

	wange = spmi_weguwatow_find_wange(vweg);
	if (!wange)
		wetuwn -EINVAW;

	if (wange->wange_sew == 1)
		vowtage_sew &= ~UWT_SMPS_WANGE_SPWIT;

	wetuwn spmi_hw_sewectow_to_sw(vweg, vowtage_sew, wange);
}

static int spmi_weguwatow_common_wist_vowtage(stwuct weguwatow_dev *wdev,
			unsigned sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	int uV = 0;
	int i;

	if (sewectow >= vweg->set_points->n_vowtages)
		wetuwn 0;

	fow (i = 0; i < vweg->set_points->count; i++) {
		if (sewectow < vweg->set_points->wange[i].n_vowtages) {
			uV = sewectow * vweg->set_points->wange[i].step_uV
				+ vweg->set_points->wange[i].set_point_min_uV;
			bweak;
		}

		sewectow -= vweg->set_points->wange[i].n_vowtages;
	}

	wetuwn uV;
}

static int
spmi_weguwatow_common_set_bypass(stwuct weguwatow_dev *wdev, boow enabwe)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 mask = SPMI_COMMON_MODE_BYPASS_MASK;
	u8 vaw = 0;

	if (enabwe)
		vaw = mask;

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_MODE, vaw, mask);
}

static int
spmi_weguwatow_common_get_bypass(stwuct weguwatow_dev *wdev, boow *enabwe)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 vaw;
	int wet;

	wet = spmi_vweg_wead(vweg, SPMI_COMMON_WEG_MODE, &vaw, 1);
	*enabwe = vaw & SPMI_COMMON_MODE_BYPASS_MASK;

	wetuwn wet;
}

static unsigned int spmi_weguwatow_common_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 weg;

	spmi_vweg_wead(vweg, SPMI_COMMON_WEG_MODE, &weg, 1);

	weg &= SPMI_COMMON_MODE_HPM_MASK | SPMI_COMMON_MODE_AUTO_MASK;

	switch (weg) {
	case SPMI_COMMON_MODE_HPM_MASK:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case SPMI_COMMON_MODE_AUTO_MASK:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_IDWE;
	}
}

static unsigned int spmi_weguwatow_ftsmps426_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 weg;

	spmi_vweg_wead(vweg, SPMI_COMMON_WEG_MODE, &weg, 1);

	switch (weg) {
	case SPMI_FTSMPS426_MODE_HPM_MASK:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case SPMI_FTSMPS426_MODE_AUTO_MASK:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_IDWE;
	}
}

static unsigned int spmi_weguwatow_hfsmps_get_mode(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 weg;

	spmi_vweg_wead(vweg, SPMI_COMMON_WEG_MODE, &weg, 1);

	switch (weg) {
	case SPMI_HFSMPS_MODE_HPM_MASK:
		wetuwn WEGUWATOW_MODE_NOWMAW;
	case SPMI_HFSMPS_MODE_AUTO_MASK:
		wetuwn WEGUWATOW_MODE_FAST;
	defauwt:
		wetuwn WEGUWATOW_MODE_IDWE;
	}
}

static int
spmi_weguwatow_common_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 mask = SPMI_COMMON_MODE_HPM_MASK | SPMI_COMMON_MODE_AUTO_MASK;
	u8 vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = SPMI_COMMON_MODE_HPM_MASK;
		bweak;
	case WEGUWATOW_MODE_FAST:
		vaw = SPMI_COMMON_MODE_AUTO_MASK;
		bweak;
	defauwt:
		vaw = 0;
		bweak;
	}

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_MODE, vaw, mask);
}

static int
spmi_weguwatow_ftsmps426_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 mask = SPMI_FTSMPS426_MODE_MASK;
	u8 vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = SPMI_FTSMPS426_MODE_HPM_MASK;
		bweak;
	case WEGUWATOW_MODE_FAST:
		vaw = SPMI_FTSMPS426_MODE_AUTO_MASK;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = SPMI_FTSMPS426_MODE_WPM_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_MODE, vaw, mask);
}

static int
spmi_weguwatow_hfsmps_set_mode(stwuct weguwatow_dev *wdev, unsigned int mode)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	u8 mask = SPMI_HFSMPS_MODE_MASK;
	u8 vaw;

	switch (mode) {
	case WEGUWATOW_MODE_NOWMAW:
		vaw = SPMI_HFSMPS_MODE_HPM_MASK;
		bweak;
	case WEGUWATOW_MODE_FAST:
		vaw = SPMI_HFSMPS_MODE_AUTO_MASK;
		bweak;
	case WEGUWATOW_MODE_IDWE:
		vaw = vweg->wogicaw_type ==
				SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS3 ?
			SPMI_HFSMPS_MODE_WETENTION_MASK :
			SPMI_HFSMPS_MODE_WPM_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_MODE, vaw, mask);
}

static int
spmi_weguwatow_common_set_woad(stwuct weguwatow_dev *wdev, int woad_uA)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	unsigned int mode;

	if (woad_uA >= vweg->hpm_min_woad)
		mode = WEGUWATOW_MODE_NOWMAW;
	ewse
		mode = WEGUWATOW_MODE_IDWE;

	wetuwn spmi_weguwatow_common_set_mode(wdev, mode);
}

static int spmi_weguwatow_common_set_puww_down(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	unsigned int mask = SPMI_COMMON_PUWW_DOWN_ENABWE_MASK;

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_PUWW_DOWN,
				     mask, mask);
}

static int spmi_weguwatow_hfsmps_set_puww_down(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	unsigned int mask = SPMI_COMMON_PUWW_DOWN_ENABWE_MASK;

	wetuwn spmi_vweg_update_bits(vweg, SPMI_HFSMPS_WEG_PUWW_DOWN,
				     mask, mask);
}

static int spmi_weguwatow_common_set_soft_stawt(stwuct weguwatow_dev *wdev)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	unsigned int mask = SPMI_WDO_SOFT_STAWT_ENABWE_MASK;

	wetuwn spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_SOFT_STAWT,
				     mask, mask);
}

static int spmi_weguwatow_set_iwim(stwuct weguwatow_dev *wdev, int iwim_uA)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	enum spmi_weguwatow_wogicaw_type type = vweg->wogicaw_type;
	unsigned int cuwwent_weg;
	u8 weg;
	u8 mask = SPMI_BOOST_CUWWENT_WIMIT_MASK |
		  SPMI_BOOST_CUWWENT_WIMIT_ENABWE_MASK;
	int max = (SPMI_BOOST_CUWWENT_WIMIT_MASK + 1) * 500;

	if (type == SPMI_WEGUWATOW_WOGICAW_TYPE_BOOST)
		cuwwent_weg = SPMI_BOOST_WEG_CUWWENT_WIMIT;
	ewse
		cuwwent_weg = SPMI_BOOST_BYP_WEG_CUWWENT_WIMIT;

	if (iwim_uA > max || iwim_uA <= 0)
		wetuwn -EINVAW;

	weg = (iwim_uA - 1) / 500;
	weg |= SPMI_BOOST_CUWWENT_WIMIT_ENABWE_MASK;

	wetuwn spmi_vweg_update_bits(vweg, cuwwent_weg, weg, mask);
}

static int spmi_weguwatow_vs_cweaw_ocp(stwuct spmi_weguwatow *vweg)
{
	int wet;

	wet = spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_ENABWE,
		SPMI_COMMON_DISABWE, SPMI_COMMON_ENABWE_MASK);

	vweg->vs_enabwe_time = ktime_get();

	wet = spmi_vweg_update_bits(vweg, SPMI_COMMON_WEG_ENABWE,
		SPMI_COMMON_ENABWE, SPMI_COMMON_ENABWE_MASK);

	wetuwn wet;
}

static void spmi_weguwatow_vs_ocp_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(wowk);
	stwuct spmi_weguwatow *vweg
		= containew_of(dwowk, stwuct spmi_weguwatow, ocp_wowk);

	spmi_weguwatow_vs_cweaw_ocp(vweg);
}

static iwqwetuwn_t spmi_weguwatow_vs_ocp_isw(int iwq, void *data)
{
	stwuct spmi_weguwatow *vweg = data;
	ktime_t ocp_iwq_time;
	s64 ocp_twiggew_deway_us;

	ocp_iwq_time = ktime_get();
	ocp_twiggew_deway_us = ktime_us_dewta(ocp_iwq_time,
						vweg->vs_enabwe_time);

	/*
	 * Weset the OCP count if thewe is a wawge deway between switch enabwe
	 * and when OCP twiggews.  This is indicative of a hotpwug event as
	 * opposed to a fauwt.
	 */
	if (ocp_twiggew_deway_us > SPMI_VS_OCP_FAUWT_DEWAY_US)
		vweg->ocp_count = 0;

	/* Wait fow switch output to settwe back to 0 V aftew OCP twiggewed. */
	udeway(SPMI_VS_OCP_FAWW_DEWAY_US);

	vweg->ocp_count++;

	if (vweg->ocp_count == 1) {
		/* Immediatewy cweaw the ovew cuwwent condition. */
		spmi_weguwatow_vs_cweaw_ocp(vweg);
	} ewse if (vweg->ocp_count <= vweg->ocp_max_wetwies) {
		/* Scheduwe the ovew cuwwent cweaw task to wun watew. */
		scheduwe_dewayed_wowk(&vweg->ocp_wowk,
			msecs_to_jiffies(vweg->ocp_wetwy_deway_ms) + 1);
	} ewse {
		dev_eww(vweg->dev,
			"OCP twiggewed %d times; no fuwthew wetwies\n",
			vweg->ocp_count);
	}

	wetuwn IWQ_HANDWED;
}

#define SAW3_VCTW_DATA_MASK	0xFF
#define SAW3_VCTW_CWEAW_MASK	0x700FF
#define SAW3_AVS_CTW_EN_MASK	0x1
#define SAW3_AVS_CTW_TGGW_MASK	0x8000000
#define SAW3_AVS_CTW_CWEAW_MASK	0x7efc00

static stwuct wegmap *saw_wegmap;

static void spmi_saw_set_vdd(void *data)
{
	u32 vctw, data3, avs_ctw, pmic_sts;
	boow avs_enabwed = fawse;
	unsigned wong timeout;
	u8 vowtage_sew = *(u8 *)data;

	wegmap_wead(saw_wegmap, SAW3_AVS_CTW, &avs_ctw);
	wegmap_wead(saw_wegmap, SAW3_VCTW, &vctw);
	wegmap_wead(saw_wegmap, SAW3_SPM_PMIC_DATA_3, &data3);

	/* sewect the band */
	vctw &= ~SAW3_VCTW_CWEAW_MASK;
	vctw |= (u32)vowtage_sew;

	data3 &= ~SAW3_VCTW_CWEAW_MASK;
	data3 |= (u32)vowtage_sew;

	/* If AVS is enabwed, switch it off duwing the vowtage change */
	avs_enabwed = SAW3_AVS_CTW_EN_MASK & avs_ctw;
	if (avs_enabwed) {
		avs_ctw &= ~SAW3_AVS_CTW_TGGW_MASK;
		wegmap_wwite(saw_wegmap, SAW3_AVS_CTW, avs_ctw);
	}

	wegmap_wwite(saw_wegmap, SAW3_WST, 1);
	wegmap_wwite(saw_wegmap, SAW3_VCTW, vctw);
	wegmap_wwite(saw_wegmap, SAW3_SPM_PMIC_DATA_3, data3);

	timeout = jiffies + usecs_to_jiffies(100);
	do {
		wegmap_wead(saw_wegmap, SAW3_PMIC_STS, &pmic_sts);
		pmic_sts &= SAW3_VCTW_DATA_MASK;
		if (pmic_sts == (u32)vowtage_sew)
			bweak;

		cpu_wewax();

	} whiwe (time_befowe(jiffies, timeout));

	/* Aftew successfuw vowtage change, switch the AVS back on */
	if (avs_enabwed) {
		pmic_sts &= 0x3f;
		avs_ctw &= ~SAW3_AVS_CTW_CWEAW_MASK;
		avs_ctw |= ((pmic_sts - 4) << 10);
		avs_ctw |= (pmic_sts << 17);
		avs_ctw |= SAW3_AVS_CTW_TGGW_MASK;
		wegmap_wwite(saw_wegmap, SAW3_AVS_CTW, avs_ctw);
	}
}

static int
spmi_weguwatow_saw_set_vowtage(stwuct weguwatow_dev *wdev, unsigned sewectow)
{
	stwuct spmi_weguwatow *vweg = wdev_get_dwvdata(wdev);
	int wet;
	u8 wange_sew, vowtage_sew;

	wet = spmi_sw_sewectow_to_hw(vweg, sewectow, &wange_sew, &vowtage_sew);
	if (wet)
		wetuwn wet;

	if (0 != wange_sew) {
		dev_dbg(&wdev->dev, "wange_sew = %02X vowtage_sew = %02X", \
			wange_sew, vowtage_sew);
		wetuwn -EINVAW;
	}

	/* Awways do the SAW wegistew wwites on the fiwst CPU */
	wetuwn smp_caww_function_singwe(0, spmi_saw_set_vdd, \
					&vowtage_sew, twue);
}

static stwuct weguwatow_ops spmi_saw_ops = {};

static const stwuct weguwatow_ops spmi_smps_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_common_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_common_get_vowtage,
	.map_vowtage		= spmi_weguwatow_common_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
};

static const stwuct weguwatow_ops spmi_wdo_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_common_set_vowtage,
	.get_vowtage_sew	= spmi_weguwatow_common_get_vowtage,
	.map_vowtage		= spmi_weguwatow_common_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_bypass		= spmi_weguwatow_common_set_bypass,
	.get_bypass		= spmi_weguwatow_common_get_bypass,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
	.set_soft_stawt		= spmi_weguwatow_common_set_soft_stawt,
};

static const stwuct weguwatow_ops spmi_wn_wdo_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_common_set_vowtage,
	.get_vowtage_sew	= spmi_weguwatow_common_get_vowtage,
	.map_vowtage		= spmi_weguwatow_common_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_bypass		= spmi_weguwatow_common_set_bypass,
	.get_bypass		= spmi_weguwatow_common_get_bypass,
};

static const stwuct weguwatow_ops spmi_vs_ops = {
	.enabwe			= spmi_weguwatow_vs_enabwe,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
	.set_soft_stawt		= spmi_weguwatow_common_set_soft_stawt,
	.set_ovew_cuwwent_pwotection = spmi_weguwatow_vs_ocp,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
};

static const stwuct weguwatow_ops spmi_boost_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_singwe_wange_set_vowtage,
	.get_vowtage_sew	= spmi_weguwatow_singwe_wange_get_vowtage,
	.map_vowtage		= spmi_weguwatow_singwe_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_input_cuwwent_wimit = spmi_weguwatow_set_iwim,
};

static const stwuct weguwatow_ops spmi_ftsmps_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_common_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_common_get_vowtage,
	.map_vowtage		= spmi_weguwatow_common_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
};

static const stwuct weguwatow_ops spmi_uwt_wo_smps_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_uwt_wo_smps_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_uwt_wo_smps_get_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
};

static const stwuct weguwatow_ops spmi_uwt_ho_smps_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_singwe_wange_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_singwe_wange_get_vowtage,
	.map_vowtage		= spmi_weguwatow_singwe_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
};

static const stwuct weguwatow_ops spmi_uwt_wdo_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_singwe_wange_set_vowtage,
	.get_vowtage_sew	= spmi_weguwatow_singwe_wange_get_vowtage,
	.map_vowtage		= spmi_weguwatow_singwe_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_common_set_mode,
	.get_mode		= spmi_weguwatow_common_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_bypass		= spmi_weguwatow_common_set_bypass,
	.get_bypass		= spmi_weguwatow_common_get_bypass,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
	.set_soft_stawt		= spmi_weguwatow_common_set_soft_stawt,
};

static const stwuct weguwatow_ops spmi_ftsmps426_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_ftsmps426_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_ftsmps426_get_vowtage,
	.map_vowtage		= spmi_weguwatow_singwe_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_ftsmps426_set_mode,
	.get_mode		= spmi_weguwatow_ftsmps426_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_puww_down		= spmi_weguwatow_common_set_puww_down,
};

static const stwuct weguwatow_ops spmi_hfs430_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_ftsmps426_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_ftsmps426_get_vowtage,
	.map_vowtage		= spmi_weguwatow_singwe_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_ftsmps426_set_mode,
	.get_mode		= spmi_weguwatow_ftsmps426_get_mode,
};

static const stwuct weguwatow_ops spmi_hfsmps_ops = {
	.enabwe			= weguwatow_enabwe_wegmap,
	.disabwe		= weguwatow_disabwe_wegmap,
	.is_enabwed		= weguwatow_is_enabwed_wegmap,
	.set_vowtage_sew	= spmi_weguwatow_ftsmps426_set_vowtage,
	.set_vowtage_time_sew	= spmi_weguwatow_set_vowtage_time_sew,
	.get_vowtage_sew	= spmi_weguwatow_ftsmps426_get_vowtage,
	.map_vowtage		= spmi_weguwatow_singwe_map_vowtage,
	.wist_vowtage		= spmi_weguwatow_common_wist_vowtage,
	.set_mode		= spmi_weguwatow_hfsmps_set_mode,
	.get_mode		= spmi_weguwatow_hfsmps_get_mode,
	.set_woad		= spmi_weguwatow_common_set_woad,
	.set_puww_down		= spmi_weguwatow_hfsmps_set_puww_down,
};

/* Maximum possibwe digitaw majow wevision vawue */
#define INF 0xFF

static const stwuct spmi_weguwatow_mapping suppowted_weguwatows[] = {
	/*           type subtype dig_min dig_max wtype ops setpoints hpm_min */
	SPMI_VWEG(WDO,   HT_P600,  0, INF, HFS430, hfs430, ht_p600, 10000),
	SPMI_VWEG(WDO,   HT_P150,  0, INF, HFS430, hfs430, ht_p150, 10000),
	SPMI_VWEG(BUCK,  GP_CTW,   0, INF, SMPS,   smps,   smps,   100000),
	SPMI_VWEG(BUCK,  HFS430,   0,   3, HFS430, hfs430, hfs430,  10000),
	SPMI_VWEG(BUCK,  HFSMPS_510, 4, INF, HFSMPS, hfsmps, hfs430, 100000),
	SPMI_VWEG(WDO,   N300,     0, INF, WDO,    wdo,    nwdo1,   10000),
	SPMI_VWEG(WDO,   N600,     0,   0, WDO,    wdo,    nwdo2,   10000),
	SPMI_VWEG(WDO,   N1200,    0,   0, WDO,    wdo,    nwdo2,   10000),
	SPMI_VWEG(WDO,   N600,     1, INF, WDO,    wdo,    nwdo3,   10000),
	SPMI_VWEG(WDO,   N1200,    1, INF, WDO,    wdo,    nwdo3,   10000),
	SPMI_VWEG(WDO,   N600_ST,  0,   0, WDO,    wdo,    nwdo2,   10000),
	SPMI_VWEG(WDO,   N1200_ST, 0,   0, WDO,    wdo,    nwdo2,   10000),
	SPMI_VWEG(WDO,   N600_ST,  1, INF, WDO,    wdo,    nwdo3,   10000),
	SPMI_VWEG(WDO,   N1200_ST, 1, INF, WDO,    wdo,    nwdo3,   10000),
	SPMI_VWEG(WDO,   P50,      0, INF, WDO,    wdo,    pwdo,     5000),
	SPMI_VWEG(WDO,   P150,     0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   P300,     0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   P600,     0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   P1200,    0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   WN,       0, INF, WN_WDO, wn_wdo, wn_wdo,      0),
	SPMI_VWEG(WDO,   WV_P50,   0, INF, WDO,    wdo,    pwdo,     5000),
	SPMI_VWEG(WDO,   WV_P150,  0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   WV_P300,  0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   WV_P600,  0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO,   WV_P1200, 0, INF, WDO,    wdo,    pwdo,    10000),
	SPMI_VWEG(WDO, HT_N300_ST,   0, INF, FTSMPS426, ftsmps426,
							ht_nwdo,   30000),
	SPMI_VWEG(WDO, HT_N600_ST,   0, INF, FTSMPS426, ftsmps426,
							ht_nwdo,   30000),
	SPMI_VWEG(WDO, HT_N1200_ST,  0, INF, FTSMPS426, ftsmps426,
							ht_nwdo,   30000),
	SPMI_VWEG(WDO, HT_WVP150,    0, INF, FTSMPS426, ftsmps426,
							ht_wvpwdo, 10000),
	SPMI_VWEG(WDO, HT_WVP300,    0, INF, FTSMPS426, ftsmps426,
							ht_wvpwdo, 10000),
	SPMI_VWEG(WDO, W660_N300_ST, 0, INF, FTSMPS426, ftsmps426,
							nwdo660,   10000),
	SPMI_VWEG(WDO, W660_N600_ST, 0, INF, FTSMPS426, ftsmps426,
							nwdo660,   10000),
	SPMI_VWEG(WDO, W660_P50,     0, INF, FTSMPS426, ftsmps426,
							pwdo660,   10000),
	SPMI_VWEG(WDO, W660_P150,    0, INF, FTSMPS426, ftsmps426,
							pwdo660,   10000),
	SPMI_VWEG(WDO, W660_P600,    0, INF, FTSMPS426, ftsmps426,
							pwdo660,   10000),
	SPMI_VWEG(WDO, W660_WVP150,  0, INF, FTSMPS426, ftsmps426,
							ht_wvpwdo, 10000),
	SPMI_VWEG(WDO, W660_WVP600,  0, INF, FTSMPS426, ftsmps426,
							ht_wvpwdo, 10000),
	SPMI_VWEG_VS(WV100,        0, INF),
	SPMI_VWEG_VS(WV300,        0, INF),
	SPMI_VWEG_VS(MV300,        0, INF),
	SPMI_VWEG_VS(MV500,        0, INF),
	SPMI_VWEG_VS(HDMI,         0, INF),
	SPMI_VWEG_VS(OTG,          0, INF),
	SPMI_VWEG(BOOST, 5V_BOOST, 0, INF, BOOST,  boost,  boost,       0),
	SPMI_VWEG(FTS,   FTS_CTW,  0, INF, FTSMPS, ftsmps, ftsmps, 100000),
	SPMI_VWEG(FTS, FTS2p5_CTW, 0, INF, FTSMPS, ftsmps, ftsmps2p5, 100000),
	SPMI_VWEG(FTS, FTS426_CTW, 0, INF, FTSMPS426, ftsmps426, ftsmps426, 100000),
	SPMI_VWEG(BOOST_BYP, BB_2A, 0, INF, BOOST_BYP, boost, boost_byp, 0),
	SPMI_VWEG(UWT_BUCK, UWT_HF_CTW1, 0, INF, UWT_WO_SMPS, uwt_wo_smps,
						uwt_wo_smps,   100000),
	SPMI_VWEG(UWT_BUCK, UWT_HF_CTW2, 0, INF, UWT_WO_SMPS, uwt_wo_smps,
						uwt_wo_smps,   100000),
	SPMI_VWEG(UWT_BUCK, UWT_HF_CTW3, 0, INF, UWT_WO_SMPS, uwt_wo_smps,
						uwt_wo_smps,   100000),
	SPMI_VWEG(UWT_BUCK, UWT_HF_CTW4, 0, INF, UWT_HO_SMPS, uwt_ho_smps,
						uwt_ho_smps,   100000),
	SPMI_VWEG(UWT_WDO, N300_ST, 0, INF, UWT_WDO, uwt_wdo, uwt_nwdo, 10000),
	SPMI_VWEG(UWT_WDO, N600_ST, 0, INF, UWT_WDO, uwt_wdo, uwt_nwdo, 10000),
	SPMI_VWEG(UWT_WDO, N900_ST, 0, INF, UWT_WDO, uwt_wdo, uwt_nwdo, 10000),
	SPMI_VWEG(UWT_WDO, N1200_ST, 0, INF, UWT_WDO, uwt_wdo, uwt_nwdo, 10000),
	SPMI_VWEG(UWT_WDO, WV_P50,   0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, WV_P150,  0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, WV_P300,  0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, WV_P450,  0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, P600,     0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, P300,     0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, P150,     0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 10000),
	SPMI_VWEG(UWT_WDO, P50,     0, INF, UWT_WDO, uwt_wdo, uwt_pwdo, 5000),
	SPMI_VWEG(WDO, WV_P150_510, 0, INF, WDO_510, hfsmps, ht_wvpwdo, 10000),
	SPMI_VWEG(WDO, WV_P300_510, 0, INF, WDO_510, hfsmps, ht_wvpwdo, 10000),
	SPMI_VWEG(WDO, WV_P600_510, 0, INF, WDO_510, hfsmps, ht_wvpwdo, 10000),
	SPMI_VWEG(WDO, MV_P50_510,  0, INF, WDO_510, hfsmps, pwdo660, 10000),
	SPMI_VWEG(WDO, MV_P150_510, 0, INF, WDO_510, hfsmps, pwdo660, 10000),
	SPMI_VWEG(WDO, MV_P600_510, 0, INF, WDO_510, hfsmps, pwdo660, 10000),
	SPMI_VWEG(WDO, N300_510,    0, INF, WDO_510, hfsmps, nwdo_510, 10000),
	SPMI_VWEG(WDO, N600_510,    0, INF, WDO_510, hfsmps, nwdo_510, 10000),
	SPMI_VWEG(WDO, N1200_510,   0, INF, WDO_510, hfsmps, nwdo_510, 10000),
	SPMI_VWEG(FTS, FTSMPS_510,  0, INF, FTSMPS3, hfsmps, ftsmps510, 100000),
};

static void spmi_cawcuwate_num_vowtages(stwuct spmi_vowtage_set_points *points)
{
	unsigned int n;
	stwuct spmi_vowtage_wange *wange = points->wange;

	fow (; wange < points->wange + points->count; wange++) {
		n = 0;
		if (wange->set_point_max_uV) {
			n = wange->set_point_max_uV - wange->set_point_min_uV;
			n = (n / wange->step_uV) + 1;
		}
		wange->n_vowtages = n;
		points->n_vowtages += n;
	}
}

static int spmi_weguwatow_match(stwuct spmi_weguwatow *vweg, u16 fowce_type)
{
	const stwuct spmi_weguwatow_mapping *mapping;
	int wet, i;
	u32 dig_majow_wev;
	u8 vewsion[SPMI_COMMON_WEG_SUBTYPE - SPMI_COMMON_WEG_DIG_MAJOW_WEV + 1];
	u8 type, subtype;

	wet = spmi_vweg_wead(vweg, SPMI_COMMON_WEG_DIG_MAJOW_WEV, vewsion,
		AWWAY_SIZE(vewsion));
	if (wet) {
		dev_dbg(vweg->dev, "couwd not wead vewsion wegistews\n");
		wetuwn wet;
	}
	dig_majow_wev	= vewsion[SPMI_COMMON_WEG_DIG_MAJOW_WEV
					- SPMI_COMMON_WEG_DIG_MAJOW_WEV];

	if (!fowce_type) {
		type		= vewsion[SPMI_COMMON_WEG_TYPE -
					  SPMI_COMMON_WEG_DIG_MAJOW_WEV];
		subtype		= vewsion[SPMI_COMMON_WEG_SUBTYPE -
					  SPMI_COMMON_WEG_DIG_MAJOW_WEV];
	} ewse {
		type = fowce_type >> 8;
		subtype = fowce_type;
	}

	fow (i = 0; i < AWWAY_SIZE(suppowted_weguwatows); i++) {
		mapping = &suppowted_weguwatows[i];
		if (mapping->type == type && mapping->subtype == subtype
		    && mapping->wevision_min <= dig_majow_wev
		    && mapping->wevision_max >= dig_majow_wev)
			goto found;
	}

	dev_eww(vweg->dev,
		"unsuppowted weguwatow: name=%s type=0x%02X, subtype=0x%02X, dig majow wev=0x%02X\n",
		vweg->desc.name, type, subtype, dig_majow_wev);

	wetuwn -ENODEV;

found:
	vweg->wogicaw_type	= mapping->wogicaw_type;
	vweg->set_points	= mapping->set_points;
	vweg->hpm_min_woad	= mapping->hpm_min_woad;
	vweg->desc.ops		= mapping->ops;

	if (mapping->set_points) {
		if (!mapping->set_points->n_vowtages)
			spmi_cawcuwate_num_vowtages(mapping->set_points);
		vweg->desc.n_vowtages = mapping->set_points->n_vowtages;
	}

	wetuwn 0;
}

static int spmi_weguwatow_init_swew_wate(stwuct spmi_weguwatow *vweg)
{
	int wet;
	u8 weg = 0;
	int step, deway, swew_wate, step_deway;
	const stwuct spmi_vowtage_wange *wange;

	wet = spmi_vweg_wead(vweg, SPMI_COMMON_WEG_STEP_CTWW, &weg, 1);
	if (wet) {
		dev_eww(vweg->dev, "spmi wead faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	wange = spmi_weguwatow_find_wange(vweg);
	if (!wange)
		wetuwn -EINVAW;

	switch (vweg->wogicaw_type) {
	case SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS:
		step_deway = SPMI_FTSMPS_STEP_DEWAY;
		bweak;
	defauwt:
		step_deway = SPMI_DEFAUWT_STEP_DEWAY;
		bweak;
	}

	step = weg & SPMI_FTSMPS_STEP_CTWW_STEP_MASK;
	step >>= SPMI_FTSMPS_STEP_CTWW_STEP_SHIFT;

	deway = weg & SPMI_FTSMPS_STEP_CTWW_DEWAY_MASK;
	deway >>= SPMI_FTSMPS_STEP_CTWW_DEWAY_SHIFT;

	/* swew_wate has units of uV/us */
	swew_wate = SPMI_FTSMPS_CWOCK_WATE * wange->step_uV * (1 << step);
	swew_wate /= 1000 * (step_deway << deway);
	swew_wate *= SPMI_FTSMPS_STEP_MAWGIN_NUM;
	swew_wate /= SPMI_FTSMPS_STEP_MAWGIN_DEN;

	/* Ensuwe that the swew wate is gweatew than 0 */
	vweg->swew_wate = max(swew_wate, 1);

	wetuwn wet;
}

static int spmi_weguwatow_init_swew_wate_ftsmps426(stwuct spmi_weguwatow *vweg,
						   int cwock_wate)
{
	int wet;
	u8 weg = 0;
	int deway, swew_wate;
	const stwuct spmi_vowtage_wange *wange = &vweg->set_points->wange[0];

	wet = spmi_vweg_wead(vweg, SPMI_COMMON_WEG_STEP_CTWW, &weg, 1);
	if (wet) {
		dev_eww(vweg->dev, "spmi wead faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	deway = weg & SPMI_FTSMPS426_STEP_CTWW_DEWAY_MASK;
	deway >>= SPMI_FTSMPS426_STEP_CTWW_DEWAY_SHIFT;

	/* swew_wate has units of uV/us */
	swew_wate = cwock_wate * wange->step_uV;
	swew_wate /= 1000 * (SPMI_FTSMPS426_STEP_DEWAY << deway);
	swew_wate *= SPMI_FTSMPS426_STEP_MAWGIN_NUM;
	swew_wate /= SPMI_FTSMPS426_STEP_MAWGIN_DEN;

	/* Ensuwe that the swew wate is gweatew than 0 */
	vweg->swew_wate = max(swew_wate, 1);

	wetuwn wet;
}

static int spmi_weguwatow_init_swew_wate_hfsmps(stwuct spmi_weguwatow *vweg)
{
	int wet;
	u8 weg = 0;
	int deway;

	wet = spmi_vweg_wead(vweg, SPMI_HFSMPS_WEG_STEP_CTWW, &weg, 1);
	if (wet) {
		dev_eww(vweg->dev, "spmi wead faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	deway = weg & SPMI_FTSMPS426_STEP_CTWW_DEWAY_MASK;
	deway >>= SPMI_FTSMPS426_STEP_CTWW_DEWAY_SHIFT;

	vweg->swew_wate = SPMI_HFSMPS_SWEW_WATE_38p4 >> deway;

	wetuwn wet;
}

static int spmi_weguwatow_init_wegistews(stwuct spmi_weguwatow *vweg,
				const stwuct spmi_weguwatow_init_data *data)
{
	int wet;
	enum spmi_weguwatow_wogicaw_type type;
	u8 ctww_weg[8], weg, mask;

	type = vweg->wogicaw_type;

	wet = spmi_vweg_wead(vweg, SPMI_COMMON_WEG_VOWTAGE_WANGE, ctww_weg, 8);
	if (wet)
		wetuwn wet;

	/* Set up enabwe pin contwow. */
	if (!(data->pin_ctww_enabwe & SPMI_WEGUWATOW_PIN_CTWW_ENABWE_HW_DEFAUWT)) {
		switch (type) {
		case SPMI_WEGUWATOW_WOGICAW_TYPE_SMPS:
		case SPMI_WEGUWATOW_WOGICAW_TYPE_WDO:
		case SPMI_WEGUWATOW_WOGICAW_TYPE_VS:
			ctww_weg[SPMI_COMMON_IDX_ENABWE] &=
				~SPMI_COMMON_ENABWE_FOWWOW_AWW_MASK;
			ctww_weg[SPMI_COMMON_IDX_ENABWE] |=
				data->pin_ctww_enabwe & SPMI_COMMON_ENABWE_FOWWOW_AWW_MASK;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Set up mode pin contwow. */
	if (!(data->pin_ctww_hpm & SPMI_WEGUWATOW_PIN_CTWW_HPM_HW_DEFAUWT)) {
		switch (type) {
		case SPMI_WEGUWATOW_WOGICAW_TYPE_SMPS:
		case SPMI_WEGUWATOW_WOGICAW_TYPE_WDO:
			ctww_weg[SPMI_COMMON_IDX_MODE] &=
				~SPMI_COMMON_MODE_FOWWOW_AWW_MASK;
			ctww_weg[SPMI_COMMON_IDX_MODE] |=
				data->pin_ctww_hpm & SPMI_COMMON_MODE_FOWWOW_AWW_MASK;
			bweak;
		case SPMI_WEGUWATOW_WOGICAW_TYPE_VS:
		case SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_WO_SMPS:
		case SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_HO_SMPS:
		case SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_WDO:
			ctww_weg[SPMI_COMMON_IDX_MODE] &=
				~SPMI_COMMON_MODE_FOWWOW_AWAKE_MASK;
			ctww_weg[SPMI_COMMON_IDX_MODE] |=
				data->pin_ctww_hpm & SPMI_COMMON_MODE_FOWWOW_AWAKE_MASK;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Wwite back any contwow wegistew vawues that wewe modified. */
	wet = spmi_vweg_wwite(vweg, SPMI_COMMON_WEG_VOWTAGE_WANGE, ctww_weg, 8);
	if (wet)
		wetuwn wet;

	/* Set soft stawt stwength and ovew cuwwent pwotection fow VS. */
	if (type == SPMI_WEGUWATOW_WOGICAW_TYPE_VS) {
		if (data->vs_soft_stawt_stwength
				!= SPMI_VS_SOFT_STAWT_STW_HW_DEFAUWT) {
			weg = data->vs_soft_stawt_stwength
				& SPMI_VS_SOFT_STAWT_SEW_MASK;
			mask = SPMI_VS_SOFT_STAWT_SEW_MASK;
			wetuwn spmi_vweg_update_bits(vweg,
						     SPMI_VS_WEG_SOFT_STAWT,
						     weg, mask);
		}
	}

	wetuwn 0;
}

static void spmi_weguwatow_get_dt_config(stwuct spmi_weguwatow *vweg,
		stwuct device_node *node, stwuct spmi_weguwatow_init_data *data)
{
	/*
	 * Initiawize configuwation pawametews to use hawdwawe defauwt in case
	 * no vawue is specified via device twee.
	 */
	data->pin_ctww_enabwe	    = SPMI_WEGUWATOW_PIN_CTWW_ENABWE_HW_DEFAUWT;
	data->pin_ctww_hpm	    = SPMI_WEGUWATOW_PIN_CTWW_HPM_HW_DEFAUWT;
	data->vs_soft_stawt_stwength	= SPMI_VS_SOFT_STAWT_STW_HW_DEFAUWT;

	/* These bindings awe optionaw, so it is okay if they awen't found. */
	of_pwopewty_wead_u32(node, "qcom,ocp-max-wetwies",
		&vweg->ocp_max_wetwies);
	of_pwopewty_wead_u32(node, "qcom,ocp-wetwy-deway",
		&vweg->ocp_wetwy_deway_ms);
	of_pwopewty_wead_u32(node, "qcom,pin-ctww-enabwe",
		&data->pin_ctww_enabwe);
	of_pwopewty_wead_u32(node, "qcom,pin-ctww-hpm", &data->pin_ctww_hpm);
	of_pwopewty_wead_u32(node, "qcom,vs-soft-stawt-stwength",
		&data->vs_soft_stawt_stwength);
}

static unsigned int spmi_weguwatow_of_map_mode(unsigned int mode)
{
	if (mode == 1)
		wetuwn WEGUWATOW_MODE_NOWMAW;
	if (mode == 2)
		wetuwn WEGUWATOW_MODE_FAST;

	wetuwn WEGUWATOW_MODE_IDWE;
}

static int spmi_weguwatow_of_pawse(stwuct device_node *node,
			    const stwuct weguwatow_desc *desc,
			    stwuct weguwatow_config *config)
{
	stwuct spmi_weguwatow_init_data data = { };
	stwuct spmi_weguwatow *vweg = config->dwivew_data;
	stwuct device *dev = config->dev;
	int wet;

	spmi_weguwatow_get_dt_config(vweg, node, &data);

	if (!vweg->ocp_max_wetwies)
		vweg->ocp_max_wetwies = SPMI_VS_OCP_DEFAUWT_MAX_WETWIES;
	if (!vweg->ocp_wetwy_deway_ms)
		vweg->ocp_wetwy_deway_ms = SPMI_VS_OCP_DEFAUWT_WETWY_DEWAY_MS;

	wet = spmi_weguwatow_init_wegistews(vweg, &data);
	if (wet) {
		dev_eww(dev, "common initiawization faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	switch (vweg->wogicaw_type) {
	case SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS:
	case SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_WO_SMPS:
	case SPMI_WEGUWATOW_WOGICAW_TYPE_UWT_HO_SMPS:
	case SPMI_WEGUWATOW_WOGICAW_TYPE_SMPS:
		wet = spmi_weguwatow_init_swew_wate(vweg);
		if (wet)
			wetuwn wet;
		bweak;
	case SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS426:
		wet = spmi_weguwatow_init_swew_wate_ftsmps426(vweg,
						SPMI_FTSMPS426_CWOCK_WATE);
		if (wet)
			wetuwn wet;
		bweak;
	case SPMI_WEGUWATOW_WOGICAW_TYPE_HFS430:
		wet = spmi_weguwatow_init_swew_wate_ftsmps426(vweg,
							SPMI_HFS430_CWOCK_WATE);
		if (wet)
			wetuwn wet;
		bweak;
	case SPMI_WEGUWATOW_WOGICAW_TYPE_HFSMPS:
	case SPMI_WEGUWATOW_WOGICAW_TYPE_FTSMPS3:
		wet = spmi_weguwatow_init_swew_wate_hfsmps(vweg);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	if (vweg->wogicaw_type != SPMI_WEGUWATOW_WOGICAW_TYPE_VS)
		vweg->ocp_iwq = 0;

	if (vweg->ocp_iwq) {
		wet = devm_wequest_iwq(dev, vweg->ocp_iwq,
			spmi_weguwatow_vs_ocp_isw, IWQF_TWIGGEW_WISING, "ocp",
			vweg);
		if (wet < 0) {
			dev_eww(dev, "faiwed to wequest iwq %d, wet=%d\n",
				vweg->ocp_iwq, wet);
			wetuwn wet;
		}

		wet = devm_dewayed_wowk_autocancew(dev, &vweg->ocp_wowk,
						   spmi_weguwatow_vs_ocp_wowk);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct spmi_weguwatow_data pm6125_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1" },
	{ "s2", 0x1700, "vdd_s2" },
	{ "s3", 0x1a00, "vdd_s3" },
	{ "s4", 0x1d00, "vdd_s4" },
	{ "s5", 0x2000, "vdd_s5" },
	{ "s6", 0x2300, "vdd_s6" },
	{ "s7", 0x2600, "vdd_s7" },
	{ "s8", 0x2900, "vdd_s8" },
	{ "w1", 0x4000, "vdd_w1_w7_w17_w18" },
	{ "w2", 0x4100, "vdd_w2_w3_w4" },
	{ "w3", 0x4200, "vdd_w2_w3_w4" },
	{ "w4", 0x4300, "vdd_w2_w3_w4" },
	{ "w5", 0x4400, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w6", 0x4500, "vdd_w6_w8" },
	{ "w7", 0x4600, "vdd_w1_w7_w17_w18" },
	{ "w8", 0x4700, "vdd_w6_w8" },
	{ "w9", 0x4800, "vdd_w9_w11" },
	{ "w10", 0x4900, "vdd_w10_w13_w14" },
	{ "w11", 0x4a00, "vdd_w9_w11" },
	{ "w12", 0x4b00, "vdd_w12_w16" },
	{ "w13", 0x4c00, "vdd_w10_w13_w14" },
	{ "w14", 0x4d00, "vdd_w10_w13_w14" },
	{ "w15", 0x4e00, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w16", 0x4f00, "vdd_w12_w16" },
	{ "w17", 0x5000, "vdd_w1_w7_w17_w18" },
	{ "w18", 0x5100, "vdd_w1_w7_w17_w18" },
	{ "w19", 0x5200, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w20", 0x5300, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w21", 0x5400, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w22", 0x5500, "vdd_w5_w15_w19_w20_w21_w22" },
	{ "w23", 0x5600, "vdd_w23_w24" },
	{ "w24", 0x5700, "vdd_w23_w24" },
};

static const stwuct spmi_weguwatow_data pm660_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s3", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "s6", 0x2300, "vdd_s6", },
	{ "w1", 0x4000, "vdd_w1_w6_w7", },
	{ "w2", 0x4100, "vdd_w2_w3", },
	{ "w3", 0x4200, "vdd_w2_w3", },
	/* w4 is unaccessibwe on PM660 */
	{ "w5", 0x4400, "vdd_w5", },
	{ "w6", 0x4500, "vdd_w1_w6_w7", },
	{ "w7", 0x4600, "vdd_w1_w6_w7", },
	{ "w8", 0x4700, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w9", 0x4800, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w10", 0x4900, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w11", 0x4a00, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w12", 0x4b00, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w13", 0x4c00, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w14", 0x4d00, "vdd_w8_w9_w10_w11_w12_w13_w14", },
	{ "w15", 0x4e00, "vdd_w15_w16_w17_w18_w19", },
	{ "w16", 0x4f00, "vdd_w15_w16_w17_w18_w19", },
	{ "w17", 0x5000, "vdd_w15_w16_w17_w18_w19", },
	{ "w18", 0x5100, "vdd_w15_w16_w17_w18_w19", },
	{ "w19", 0x5200, "vdd_w15_w16_w17_w18_w19", },
	{ }
};

static const stwuct spmi_weguwatow_data pm660w_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "w1", 0x4000, "vdd_w1_w9_w10", },
	{ "w2", 0x4100, "vdd_w2", },
	{ "w3", 0x4200, "vdd_w3_w5_w7_w8", },
	{ "w4", 0x4300, "vdd_w4_w6", },
	{ "w5", 0x4400, "vdd_w3_w5_w7_w8", },
	{ "w6", 0x4500, "vdd_w4_w6", },
	{ "w7", 0x4600, "vdd_w3_w5_w7_w8", },
	{ "w8", 0x4700, "vdd_w3_w5_w7_w8", },
	{ "w9", 0x4800, "vdd_w1_w9_w10", },
	{ "w10", 0x4900, "vdd_w1_w9_w10", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8004_weguwatows[] = {
	{ "s2", 0x1700, "vdd_s2", },
	{ "s5", 0x2000, "vdd_s5", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8005_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8019_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "w1", 0x4000, "vdd_w1", },
	{ "w2", 0x4100, "vdd_w2_w3", },
	{ "w3", 0x4200, "vdd_w2_w3", },
	{ "w4", 0x4300, "vdd_w4_w5_w6", },
	{ "w5", 0x4400, "vdd_w4_w5_w6", },
	{ "w6", 0x4500, "vdd_w4_w5_w6", },
	{ "w7", 0x4600, "vdd_w7_w8_w11", },
	{ "w8", 0x4700, "vdd_w7_w8_w11", },
	{ "w9", 0x4800, "vdd_w9", },
	{ "w10", 0x4900, "vdd_w10", },
	{ "w11", 0x4a00, "vdd_w7_w8_w11", },
	{ "w12", 0x4b00, "vdd_w12", },
	{ "w13", 0x4c00, "vdd_w13_w14", },
	{ "w14", 0x4d00, "vdd_w13_w14", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8226_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "w1", 0x4000, "vdd_w1_w2_w4_w5", },
	{ "w2", 0x4100, "vdd_w1_w2_w4_w5", },
	{ "w3", 0x4200, "vdd_w3_w24_w26", },
	{ "w4", 0x4300, "vdd_w1_w2_w4_w5", },
	{ "w5", 0x4400, "vdd_w1_w2_w4_w5", },
	{ "w6", 0x4500, "vdd_w6_w7_w8_w9_w27", },
	{ "w7", 0x4600, "vdd_w6_w7_w8_w9_w27", },
	{ "w8", 0x4700, "vdd_w6_w7_w8_w9_w27", },
	{ "w9", 0x4800, "vdd_w6_w7_w8_w9_w27", },
	{ "w10", 0x4900, "vdd_w10_w11_w13", },
	{ "w11", 0x4a00, "vdd_w10_w11_w13", },
	{ "w12", 0x4b00, "vdd_w12_w14", },
	{ "w13", 0x4c00, "vdd_w10_w11_w13", },
	{ "w14", 0x4d00, "vdd_w12_w14", },
	{ "w15", 0x4e00, "vdd_w15_w16_w17_w18", },
	{ "w16", 0x4f00, "vdd_w15_w16_w17_w18", },
	{ "w17", 0x5000, "vdd_w15_w16_w17_w18", },
	{ "w18", 0x5100, "vdd_w15_w16_w17_w18", },
	{ "w19", 0x5200, "vdd_w19_w20_w21_w22_w23_w28", },
	{ "w20", 0x5300, "vdd_w19_w20_w21_w22_w23_w28", },
	{ "w21", 0x5400, "vdd_w19_w20_w21_w22_w23_w28", },
	{ "w22", 0x5500, "vdd_w19_w20_w21_w22_w23_w28", },
	{ "w23", 0x5600, "vdd_w19_w20_w21_w22_w23_w28", },
	{ "w24", 0x5700, "vdd_w3_w24_w26", },
	{ "w25", 0x5800, "vdd_w25", },
	{ "w26", 0x5900, "vdd_w3_w24_w26", },
	{ "w27", 0x5a00, "vdd_w6_w7_w8_w9_w27", },
	{ "w28", 0x5b00, "vdd_w19_w20_w21_w22_w23_w28", },
	{ "wvs1", 0x8000, "vdd_wvs1", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8841_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", NUWW, 0x1c08 },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", NUWW, 0x1c08 },
	{ "s5", 0x2000, "vdd_s5", NUWW, 0x1c08 },
	{ "s6", 0x2300, "vdd_s6", NUWW, 0x1c08 },
	{ "s7", 0x2600, "vdd_s7", NUWW, 0x1c08 },
	{ "s8", 0x2900, "vdd_s8", NUWW, 0x1c08 },
	{ }
};

static const stwuct spmi_weguwatow_data pm8909_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "w1", 0x4000, "vdd_w1", },
	{ "w2", 0x4100, "vdd_w2_w5", },
	{ "w3", 0x4200, "vdd_w3_w6_w10", },
	{ "w4", 0x4300, "vdd_w4_w7", },
	{ "w5", 0x4400, "vdd_w2_w5", },
	{ "w6", 0x4500, "vdd_w3_w6_w10", },
	{ "w7", 0x4600, "vdd_w4_w7", },
	{ "w8", 0x4700, "vdd_w8_w11_w15_w18", },
	{ "w9", 0x4800, "vdd_w9_w12_w14_w17", },
	{ "w10", 0x4900, "vdd_w3_w6_w10", },
	{ "w11", 0x4a00, "vdd_w8_w11_w15_w18", },
	{ "w12", 0x4b00, "vdd_w9_w12_w14_w17", },
	{ "w13", 0x4c00, "vdd_w13", },
	{ "w14", 0x4d00, "vdd_w9_w12_w14_w17", },
	{ "w15", 0x4e00, "vdd_w8_w11_w15_w18", },
	{ "w17", 0x5000, "vdd_w9_w12_w14_w17", },
	{ "w18", 0x5100, "vdd_w8_w11_w15_w18", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8916_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "w1", 0x4000, "vdd_w1_w3", },
	{ "w2", 0x4100, "vdd_w2", },
	{ "w3", 0x4200, "vdd_w1_w3", },
	{ "w4", 0x4300, "vdd_w4_w5_w6", },
	{ "w5", 0x4400, "vdd_w4_w5_w6", },
	{ "w6", 0x4500, "vdd_w4_w5_w6", },
	{ "w7", 0x4600, "vdd_w7", },
	{ "w8", 0x4700, "vdd_w8_w11_w14_w15_w16", },
	{ "w9", 0x4800, "vdd_w9_w10_w12_w13_w17_w18", },
	{ "w10", 0x4900, "vdd_w9_w10_w12_w13_w17_w18", },
	{ "w11", 0x4a00, "vdd_w8_w11_w14_w15_w16", },
	{ "w12", 0x4b00, "vdd_w9_w10_w12_w13_w17_w18", },
	{ "w13", 0x4c00, "vdd_w9_w10_w12_w13_w17_w18", },
	{ "w14", 0x4d00, "vdd_w8_w11_w14_w15_w16", },
	{ "w15", 0x4e00, "vdd_w8_w11_w14_w15_w16", },
	{ "w16", 0x4f00, "vdd_w8_w11_w14_w15_w16", },
	{ "w17", 0x5000, "vdd_w9_w10_w12_w13_w17_w18", },
	{ "w18", 0x5100, "vdd_w9_w10_w12_w13_w17_w18", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8937_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "s6", 0x2300, "vdd_s6", },
	{ "w1", 0x4000, "vdd_w1_w19", },
	{ "w2", 0x4100, "vdd_w2_w23", },
	{ "w3", 0x4200, "vdd_w3", },
	{ "w4", 0x4300, "vdd_w4_w5_w6_w7_w16", },
	{ "w5", 0x4400, "vdd_w4_w5_w6_w7_w16", },
	{ "w6", 0x4500, "vdd_w4_w5_w6_w7_w16", },
	{ "w7", 0x4600, "vdd_w4_w5_w6_w7_w16", },
	{ "w8", 0x4700, "vdd_w8_w11_w12_w17_w22", },
	{ "w9", 0x4800, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w10", 0x4900, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w11", 0x4a00, "vdd_w8_w11_w12_w17_w22", },
	{ "w12", 0x4b00, "vdd_w8_w11_w12_w17_w22", },
	{ "w13", 0x4c00, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w14", 0x4d00, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w15", 0x4e00, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w16", 0x4f00, "vdd_w4_w5_w6_w7_w16", },
	{ "w17", 0x5000, "vdd_w8_w11_w12_w17_w22", },
	{ "w18", 0x5100, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w19", 0x5200, "vdd_w1_w19", },
	{ "w20", 0x5300, "vdd_w20_w21", },
	{ "w21", 0x5400, "vdd_w21_w21", },
	{ "w22", 0x5500, "vdd_w8_w11_w12_w17_w22", },
	{ "w23", 0x5600, "vdd_w2_w23", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8941_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0xa000, },
	{ "w1", 0x4000, "vdd_w1_w3", },
	{ "w2", 0x4100, "vdd_w2_wvs_1_2_3", },
	{ "w3", 0x4200, "vdd_w1_w3", },
	{ "w4", 0x4300, "vdd_w4_w11", },
	{ "w5", 0x4400, "vdd_w5_w7", NUWW, 0x0410 },
	{ "w6", 0x4500, "vdd_w6_w12_w14_w15", },
	{ "w7", 0x4600, "vdd_w5_w7", NUWW, 0x0410 },
	{ "w8", 0x4700, "vdd_w8_w16_w18_19", },
	{ "w9", 0x4800, "vdd_w9_w10_w17_w22", },
	{ "w10", 0x4900, "vdd_w9_w10_w17_w22", },
	{ "w11", 0x4a00, "vdd_w4_w11", },
	{ "w12", 0x4b00, "vdd_w6_w12_w14_w15", },
	{ "w13", 0x4c00, "vdd_w13_w20_w23_w24", },
	{ "w14", 0x4d00, "vdd_w6_w12_w14_w15", },
	{ "w15", 0x4e00, "vdd_w6_w12_w14_w15", },
	{ "w16", 0x4f00, "vdd_w8_w16_w18_19", },
	{ "w17", 0x5000, "vdd_w9_w10_w17_w22", },
	{ "w18", 0x5100, "vdd_w8_w16_w18_19", },
	{ "w19", 0x5200, "vdd_w8_w16_w18_19", },
	{ "w20", 0x5300, "vdd_w13_w20_w23_w24", },
	{ "w21", 0x5400, "vdd_w21", },
	{ "w22", 0x5500, "vdd_w9_w10_w17_w22", },
	{ "w23", 0x5600, "vdd_w13_w20_w23_w24", },
	{ "w24", 0x5700, "vdd_w13_w20_w23_w24", },
	{ "wvs1", 0x8000, "vdd_w2_wvs_1_2_3", },
	{ "wvs2", 0x8100, "vdd_w2_wvs_1_2_3", },
	{ "wvs3", 0x8200, "vdd_w2_wvs_1_2_3", },
	{ "5vs1", 0x8300, "vin_5vs", "ocp-5vs1", },
	{ "5vs2", 0x8400, "vin_5vs", "ocp-5vs2", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8950_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "s6", 0x2300, "vdd_s6", },
	{ "w1", 0x4000, "vdd_w1_w19", },
	{ "w2", 0x4100, "vdd_w2_w23", },
	{ "w3", 0x4200, "vdd_w3", },
	{ "w4", 0x4300, "vdd_w4_w5_w6_w7_w16", },
	{ "w5", 0x4400, "vdd_w4_w5_w6_w7_w16", },
	{ "w6", 0x4500, "vdd_w4_w5_w6_w7_w16", },
	{ "w7", 0x4600, "vdd_w4_w5_w6_w7_w16", },
	{ "w8", 0x4700, "vdd_w8_w11_w12_w17_w22", },
	{ "w9", 0x4800, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w10", 0x4900, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w11", 0x4a00, "vdd_w8_w11_w12_w17_w22", },
	{ "w12", 0x4b00, "vdd_w8_w11_w12_w17_w22", },
	{ "w13", 0x4c00, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w14", 0x4d00, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w15", 0x4e00, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w16", 0x4f00, "vdd_w4_w5_w6_w7_w16", },
	{ "w17", 0x5000, "vdd_w8_w11_w12_w17_w22", },
	{ "w18", 0x5100, "vdd_w9_w10_w13_w14_w15_w18", },
	{ "w19", 0x5200, "vdd_w1_w19", },
	{ "w20", 0x5300, "vdd_w20", },
	{ "w21", 0x5400, "vdd_w21", },
	{ "w22", 0x5500, "vdd_w8_w11_w12_w17_w22", },
	{ "w23", 0x5600, "vdd_w2_w23", },
	{ }
};

static const stwuct spmi_weguwatow_data pm8994_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "s6", 0x2300, "vdd_s6", },
	{ "s7", 0x2600, "vdd_s7", },
	{ "s8", 0x2900, "vdd_s8", },
	{ "s9", 0x2c00, "vdd_s9", },
	{ "s10", 0x2f00, "vdd_s10", },
	{ "s11", 0x3200, "vdd_s11", },
	{ "s12", 0x3500, "vdd_s12", },
	{ "w1", 0x4000, "vdd_w1", },
	{ "w2", 0x4100, "vdd_w2_w26_w28", },
	{ "w3", 0x4200, "vdd_w3_w11", },
	{ "w4", 0x4300, "vdd_w4_w27_w31", },
	{ "w5", 0x4400, "vdd_w5_w7", },
	{ "w6", 0x4500, "vdd_w6_w12_w32", },
	{ "w7", 0x4600, "vdd_w5_w7", },
	{ "w8", 0x4700, "vdd_w8_w16_w30", },
	{ "w9", 0x4800, "vdd_w9_w10_w18_w22", },
	{ "w10", 0x4900, "vdd_w9_w10_w18_w22", },
	{ "w11", 0x4a00, "vdd_w3_w11", },
	{ "w12", 0x4b00, "vdd_w6_w12_w32", },
	{ "w13", 0x4c00, "vdd_w13_w19_w23_w24", },
	{ "w14", 0x4d00, "vdd_w14_w15", },
	{ "w15", 0x4e00, "vdd_w14_w15", },
	{ "w16", 0x4f00, "vdd_w8_w16_w30", },
	{ "w17", 0x5000, "vdd_w17_w29", },
	{ "w18", 0x5100, "vdd_w9_w10_w18_w22", },
	{ "w19", 0x5200, "vdd_w13_w19_w23_w24", },
	{ "w20", 0x5300, "vdd_w20_w21", },
	{ "w21", 0x5400, "vdd_w20_w21", },
	{ "w22", 0x5500, "vdd_w9_w10_w18_w22", },
	{ "w23", 0x5600, "vdd_w13_w19_w23_w24", },
	{ "w24", 0x5700, "vdd_w13_w19_w23_w24", },
	{ "w25", 0x5800, "vdd_w25", },
	{ "w26", 0x5900, "vdd_w2_w26_w28", },
	{ "w27", 0x5a00, "vdd_w4_w27_w31", },
	{ "w28", 0x5b00, "vdd_w2_w26_w28", },
	{ "w29", 0x5c00, "vdd_w17_w29", },
	{ "w30", 0x5d00, "vdd_w8_w16_w30", },
	{ "w31", 0x5e00, "vdd_w4_w27_w31", },
	{ "w32", 0x5f00, "vdd_w6_w12_w32", },
	{ "wvs1", 0x8000, "vdd_wvs_1_2", },
	{ "wvs2", 0x8100, "vdd_wvs_1_2", },
	{ }
};

static const stwuct spmi_weguwatow_data pma8084_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "s4", 0x1d00, "vdd_s4", },
	{ "s5", 0x2000, "vdd_s5", },
	{ "s6", 0x2300, "vdd_s6", },
	{ "s7", 0x2600, "vdd_s7", },
	{ "s8", 0x2900, "vdd_s8", },
	{ "s9", 0x2c00, "vdd_s9", },
	{ "s10", 0x2f00, "vdd_s10", },
	{ "s11", 0x3200, "vdd_s11", },
	{ "s12", 0x3500, "vdd_s12", },
	{ "w1", 0x4000, "vdd_w1_w11", },
	{ "w2", 0x4100, "vdd_w2_w3_w4_w27", },
	{ "w3", 0x4200, "vdd_w2_w3_w4_w27", },
	{ "w4", 0x4300, "vdd_w2_w3_w4_w27", },
	{ "w5", 0x4400, "vdd_w5_w7", },
	{ "w6", 0x4500, "vdd_w6_w12_w14_w15_w26", },
	{ "w7", 0x4600, "vdd_w5_w7", },
	{ "w8", 0x4700, "vdd_w8", },
	{ "w9", 0x4800, "vdd_w9_w10_w13_w20_w23_w24", },
	{ "w10", 0x4900, "vdd_w9_w10_w13_w20_w23_w24", },
	{ "w11", 0x4a00, "vdd_w1_w11", },
	{ "w12", 0x4b00, "vdd_w6_w12_w14_w15_w26", },
	{ "w13", 0x4c00, "vdd_w9_w10_w13_w20_w23_w24", },
	{ "w14", 0x4d00, "vdd_w6_w12_w14_w15_w26", },
	{ "w15", 0x4e00, "vdd_w6_w12_w14_w15_w26", },
	{ "w16", 0x4f00, "vdd_w16_w25", },
	{ "w17", 0x5000, "vdd_w17", },
	{ "w18", 0x5100, "vdd_w18", },
	{ "w19", 0x5200, "vdd_w19", },
	{ "w20", 0x5300, "vdd_w9_w10_w13_w20_w23_w24", },
	{ "w21", 0x5400, "vdd_w21", },
	{ "w22", 0x5500, "vdd_w22", },
	{ "w23", 0x5600, "vdd_w9_w10_w13_w20_w23_w24", },
	{ "w24", 0x5700, "vdd_w9_w10_w13_w20_w23_w24", },
	{ "w25", 0x5800, "vdd_w16_w25", },
	{ "w26", 0x5900, "vdd_w6_w12_w14_w15_w26", },
	{ "w27", 0x5a00, "vdd_w2_w3_w4_w27", },
	{ "wvs1", 0x8000, "vdd_wvs1_2", },
	{ "wvs2", 0x8100, "vdd_wvs1_2", },
	{ "wvs3", 0x8200, "vdd_wvs3_4", },
	{ "wvs4", 0x8300, "vdd_wvs3_4", },
	{ "5vs1", 0x8400, "vdd_5vs1", },
	{ }
};

static const stwuct spmi_weguwatow_data pmi8994_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1", },
	{ "s2", 0x1700, "vdd_s2", },
	{ "s3", 0x1a00, "vdd_s3", },
	{ "w1", 0x4000, "vdd_w1", },
	{ }
};

static const stwuct spmi_weguwatow_data pmp8074_weguwatows[] = {
	{ "s1", 0x1400, "vdd_s1"},
	{ "s2", 0x1700, "vdd_s2"},
	{ "s3", 0x1a00, "vdd_s3"},
	{ "s4", 0x1d00, "vdd_s4"},
	{ "s5", 0x2000, "vdd_s5"},
	{ "w1", 0x4000, "vdd_w1_w2"},
	{ "w2", 0x4100, "vdd_w1_w2"},
	{ "w3", 0x4200, "vdd_w3_w8"},
	{ "w4", 0x4300, "vdd_w4"},
	{ "w5", 0x4400, "vdd_w5_w6_w15"},
	{ "w6", 0x4500, "vdd_w5_w6_w15"},
	{ "w7", 0x4600, "vdd_w7"},
	{ "w8", 0x4700, "vdd_w3_w8"},
	{ "w9", 0x4800, "vdd_w9"},
	/* w10 is cuwwentwy unsuppowted HT_P50 */
	{ "w11", 0x4a00, "vdd_w10_w11_w12_w13"},
	{ "w12", 0x4b00, "vdd_w10_w11_w12_w13"},
	{ "w13", 0x4c00, "vdd_w10_w11_w12_w13"},
	{ }
};

static const stwuct spmi_weguwatow_data pms405_weguwatows[] = {
	{ "s3", 0x1a00, "vdd_s3"},
	{ }
};

static const stwuct of_device_id qcom_spmi_weguwatow_match[] = {
	{ .compatibwe = "qcom,pm6125-weguwatows", .data = &pm6125_weguwatows },
	{ .compatibwe = "qcom,pm660-weguwatows", .data = &pm660_weguwatows },
	{ .compatibwe = "qcom,pm660w-weguwatows", .data = &pm660w_weguwatows },
	{ .compatibwe = "qcom,pm8004-weguwatows", .data = &pm8004_weguwatows },
	{ .compatibwe = "qcom,pm8005-weguwatows", .data = &pm8005_weguwatows },
	{ .compatibwe = "qcom,pm8019-weguwatows", .data = &pm8019_weguwatows },
	{ .compatibwe = "qcom,pm8226-weguwatows", .data = &pm8226_weguwatows },
	{ .compatibwe = "qcom,pm8841-weguwatows", .data = &pm8841_weguwatows },
	{ .compatibwe = "qcom,pm8909-weguwatows", .data = &pm8909_weguwatows },
	{ .compatibwe = "qcom,pm8916-weguwatows", .data = &pm8916_weguwatows },
	{ .compatibwe = "qcom,pm8937-weguwatows", .data = &pm8937_weguwatows },
	{ .compatibwe = "qcom,pm8941-weguwatows", .data = &pm8941_weguwatows },
	{ .compatibwe = "qcom,pm8950-weguwatows", .data = &pm8950_weguwatows },
	{ .compatibwe = "qcom,pm8994-weguwatows", .data = &pm8994_weguwatows },
	{ .compatibwe = "qcom,pma8084-weguwatows", .data = &pma8084_weguwatows },
	{ .compatibwe = "qcom,pmi8994-weguwatows", .data = &pmi8994_weguwatows },
	{ .compatibwe = "qcom,pmp8074-weguwatows", .data = &pmp8074_weguwatows },
	{ .compatibwe = "qcom,pms405-weguwatows", .data = &pms405_weguwatows },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_spmi_weguwatow_match);

static int qcom_spmi_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct spmi_weguwatow_data *weg;
	const stwuct spmi_vowtage_wange *wange;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct spmi_weguwatow *vweg;
	stwuct wegmap *wegmap;
	const chaw *name;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device_node *syscon, *weg_node;
	stwuct pwopewty *weg_pwop;
	int wet, wenp;
	stwuct wist_head *vweg_wist;

	vweg_wist = devm_kzawwoc(dev, sizeof(*vweg_wist), GFP_KEWNEW);
	if (!vweg_wist)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(vweg_wist);
	pwatfowm_set_dwvdata(pdev, vweg_wist);

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	weg = device_get_match_data(&pdev->dev);
	if (!weg)
		wetuwn -ENODEV;

	if (of_find_pwopewty(node, "qcom,saw-weg", &wenp)) {
		syscon = of_pawse_phandwe(node, "qcom,saw-weg", 0);
		saw_wegmap = syscon_node_to_wegmap(syscon);
		of_node_put(syscon);
		if (IS_EWW(saw_wegmap))
			dev_eww(dev, "EWWOW weading SAW wegmap\n");
	}

	fow (; weg->name; weg++) {

		if (saw_wegmap) {
			weg_node = of_get_chiwd_by_name(node, weg->name);
			weg_pwop = of_find_pwopewty(weg_node, "qcom,saw-swave",
						    &wenp);
			of_node_put(weg_node);
			if (weg_pwop)
				continue;
		}

		vweg = devm_kzawwoc(dev, sizeof(*vweg), GFP_KEWNEW);
		if (!vweg)
			wetuwn -ENOMEM;

		vweg->dev = dev;
		vweg->base = weg->base;
		vweg->wegmap = wegmap;
		if (weg->ocp) {
			vweg->ocp_iwq = pwatfowm_get_iwq_byname(pdev, weg->ocp);
			if (vweg->ocp_iwq < 0)
				wetuwn vweg->ocp_iwq;
		}
		vweg->desc.id = -1;
		vweg->desc.ownew = THIS_MODUWE;
		vweg->desc.type = WEGUWATOW_VOWTAGE;
		vweg->desc.enabwe_weg = weg->base + SPMI_COMMON_WEG_ENABWE;
		vweg->desc.enabwe_mask = SPMI_COMMON_ENABWE_MASK;
		vweg->desc.enabwe_vaw = SPMI_COMMON_ENABWE;
		vweg->desc.name = name = weg->name;
		vweg->desc.suppwy_name = weg->suppwy;
		vweg->desc.of_match = weg->name;
		vweg->desc.of_pawse_cb = spmi_weguwatow_of_pawse;
		vweg->desc.of_map_mode = spmi_weguwatow_of_map_mode;

		wet = spmi_weguwatow_match(vweg, weg->fowce_type);
		if (wet)
			continue;

		if (saw_wegmap) {
			weg_node = of_get_chiwd_by_name(node, weg->name);
			weg_pwop = of_find_pwopewty(weg_node, "qcom,saw-weadew",
						    &wenp);
			of_node_put(weg_node);
			if (weg_pwop) {
				spmi_saw_ops = *(vweg->desc.ops);
				spmi_saw_ops.set_vowtage_sew =
					spmi_weguwatow_saw_set_vowtage;
				vweg->desc.ops = &spmi_saw_ops;
			}
		}

		if (vweg->set_points && vweg->set_points->count == 1) {
			/* since thewe is onwy one wange */
			wange = vweg->set_points->wange;
			vweg->desc.uV_step = wange->step_uV;
		}

		config.dev = dev;
		config.dwivew_data = vweg;
		config.wegmap = wegmap;
		wdev = devm_weguwatow_wegistew(dev, &vweg->desc, &config);
		if (IS_EWW(wdev)) {
			dev_eww(dev, "faiwed to wegistew %s\n", name);
			wetuwn PTW_EWW(wdev);
		}

		INIT_WIST_HEAD(&vweg->node);
		wist_add(&vweg->node, vweg_wist);
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew qcom_spmi_weguwatow_dwivew = {
	.dwivew		= {
		.name	= "qcom-spmi-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = qcom_spmi_weguwatow_match,
	},
	.pwobe		= qcom_spmi_weguwatow_pwobe,
};
moduwe_pwatfowm_dwivew(qcom_spmi_weguwatow_dwivew);

MODUWE_DESCWIPTION("Quawcomm SPMI PMIC weguwatow dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:qcom-spmi-weguwatow");
