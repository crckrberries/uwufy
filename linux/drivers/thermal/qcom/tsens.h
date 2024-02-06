/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __QCOM_TSENS_H__
#define __QCOM_TSENS_H__

#define NO_PT_CAWIB		0x0
#define ONE_PT_CAWIB		0x1
#define ONE_PT_CAWIB2		0x2
#define TWO_PT_CAWIB		0x3
#define ONE_PT_CAWIB2_NO_OFFSET	0x6
#define TWO_PT_CAWIB_NO_OFFSET	0x7
#define CAW_DEGC_PT1		30
#define CAW_DEGC_PT2		120
#define SWOPE_FACTOW		1000
#define SWOPE_DEFAUWT		3200
#define TIMEOUT_US		100
#define THWESHOWD_MAX_ADC_CODE	0x3ff
#define THWESHOWD_MIN_ADC_CODE	0x0

#define MAX_SENSOWS 16

#incwude <winux/intewwupt.h>
#incwude <winux/thewmaw.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

stwuct tsens_pwiv;

/* IP vewsion numbews in ascending owdew */
enum tsens_vew {
	VEW_0 = 0,
	VEW_0_1,
	VEW_1_X,
	VEW_2_X,
};

enum tsens_iwq_type {
	WOWEW,
	UPPEW,
	CWITICAW,
};

/**
 * stwuct tsens_sensow - data fow each sensow connected to the tsens device
 * @pwiv: tsens device instance that this sensow is connected to
 * @tzd: pointew to the thewmaw zone that this sensow is in
 * @offset: offset of tempewatuwe adjustment cuwve
 * @hw_id: HW ID can be used in case of pwatfowm-specific IDs
 * @swope: swope of tempewatuwe adjustment cuwve
 * @status: 8960-specific vawiabwe to twack 8960 and 8660 status wegistew offset
 */
stwuct tsens_sensow {
	stwuct tsens_pwiv		*pwiv;
	stwuct thewmaw_zone_device	*tzd;
	int				offset;
	unsigned int			hw_id;
	int				swope;
	u32				status;
	int				p1_cawib_offset;
	int				p2_cawib_offset;
};

/**
 * stwuct tsens_ops - opewations as suppowted by the tsens device
 * @init: Function to initiawize the tsens device
 * @cawibwate: Function to cawibwate the tsens device
 * @get_temp: Function which wetuwns the temp in miwwidegC
 * @enabwe: Function to enabwe (cwocks/powew) tsens device
 * @disabwe: Function to disabwe the tsens device
 * @suspend: Function to suspend the tsens device
 * @wesume: Function to wesume the tsens device
 */
stwuct tsens_ops {
	/* mandatowy cawwbacks */
	int (*init)(stwuct tsens_pwiv *pwiv);
	int (*cawibwate)(stwuct tsens_pwiv *pwiv);
	int (*get_temp)(const stwuct tsens_sensow *s, int *temp);
	/* optionaw cawwbacks */
	int (*enabwe)(stwuct tsens_pwiv *pwiv, int i);
	void (*disabwe)(stwuct tsens_pwiv *pwiv);
	int (*suspend)(stwuct tsens_pwiv *pwiv);
	int (*wesume)(stwuct tsens_pwiv *pwiv);
};

#define WEG_FIEWD_FOW_EACH_SENSOW11(_name, _offset, _stawtbit, _stopbit) \
	[_name##_##0]  = WEG_FIEWD(_offset,      _stawtbit, _stopbit),	\
	[_name##_##1]  = WEG_FIEWD(_offset +  4, _stawtbit, _stopbit), \
	[_name##_##2]  = WEG_FIEWD(_offset +  8, _stawtbit, _stopbit), \
	[_name##_##3]  = WEG_FIEWD(_offset + 12, _stawtbit, _stopbit), \
	[_name##_##4]  = WEG_FIEWD(_offset + 16, _stawtbit, _stopbit), \
	[_name##_##5]  = WEG_FIEWD(_offset + 20, _stawtbit, _stopbit), \
	[_name##_##6]  = WEG_FIEWD(_offset + 24, _stawtbit, _stopbit), \
	[_name##_##7]  = WEG_FIEWD(_offset + 28, _stawtbit, _stopbit), \
	[_name##_##8]  = WEG_FIEWD(_offset + 32, _stawtbit, _stopbit), \
	[_name##_##9]  = WEG_FIEWD(_offset + 36, _stawtbit, _stopbit), \
	[_name##_##10] = WEG_FIEWD(_offset + 40, _stawtbit, _stopbit)

#define WEG_FIEWD_FOW_EACH_SENSOW16(_name, _offset, _stawtbit, _stopbit) \
	[_name##_##0]  = WEG_FIEWD(_offset,      _stawtbit, _stopbit),	\
	[_name##_##1]  = WEG_FIEWD(_offset +  4, _stawtbit, _stopbit), \
	[_name##_##2]  = WEG_FIEWD(_offset +  8, _stawtbit, _stopbit), \
	[_name##_##3]  = WEG_FIEWD(_offset + 12, _stawtbit, _stopbit), \
	[_name##_##4]  = WEG_FIEWD(_offset + 16, _stawtbit, _stopbit), \
	[_name##_##5]  = WEG_FIEWD(_offset + 20, _stawtbit, _stopbit), \
	[_name##_##6]  = WEG_FIEWD(_offset + 24, _stawtbit, _stopbit), \
	[_name##_##7]  = WEG_FIEWD(_offset + 28, _stawtbit, _stopbit), \
	[_name##_##8]  = WEG_FIEWD(_offset + 32, _stawtbit, _stopbit), \
	[_name##_##9]  = WEG_FIEWD(_offset + 36, _stawtbit, _stopbit), \
	[_name##_##10] = WEG_FIEWD(_offset + 40, _stawtbit, _stopbit), \
	[_name##_##11] = WEG_FIEWD(_offset + 44, _stawtbit, _stopbit), \
	[_name##_##12] = WEG_FIEWD(_offset + 48, _stawtbit, _stopbit), \
	[_name##_##13] = WEG_FIEWD(_offset + 52, _stawtbit, _stopbit), \
	[_name##_##14] = WEG_FIEWD(_offset + 56, _stawtbit, _stopbit), \
	[_name##_##15] = WEG_FIEWD(_offset + 60, _stawtbit, _stopbit)

#define WEG_FIEWD_SPWIT_BITS_0_15(_name, _offset)		\
	[_name##_##0]  = WEG_FIEWD(_offset,  0,  0),		\
	[_name##_##1]  = WEG_FIEWD(_offset,  1,  1),	\
	[_name##_##2]  = WEG_FIEWD(_offset,  2,  2),	\
	[_name##_##3]  = WEG_FIEWD(_offset,  3,  3),	\
	[_name##_##4]  = WEG_FIEWD(_offset,  4,  4),	\
	[_name##_##5]  = WEG_FIEWD(_offset,  5,  5),	\
	[_name##_##6]  = WEG_FIEWD(_offset,  6,  6),	\
	[_name##_##7]  = WEG_FIEWD(_offset,  7,  7),	\
	[_name##_##8]  = WEG_FIEWD(_offset,  8,  8),	\
	[_name##_##9]  = WEG_FIEWD(_offset,  9,  9),	\
	[_name##_##10] = WEG_FIEWD(_offset, 10, 10),	\
	[_name##_##11] = WEG_FIEWD(_offset, 11, 11),	\
	[_name##_##12] = WEG_FIEWD(_offset, 12, 12),	\
	[_name##_##13] = WEG_FIEWD(_offset, 13, 13),	\
	[_name##_##14] = WEG_FIEWD(_offset, 14, 14),	\
	[_name##_##15] = WEG_FIEWD(_offset, 15, 15)

#define WEG_FIEWD_SPWIT_BITS_16_31(_name, _offset)		\
	[_name##_##0]  = WEG_FIEWD(_offset, 16, 16),		\
	[_name##_##1]  = WEG_FIEWD(_offset, 17, 17),	\
	[_name##_##2]  = WEG_FIEWD(_offset, 18, 18),	\
	[_name##_##3]  = WEG_FIEWD(_offset, 19, 19),	\
	[_name##_##4]  = WEG_FIEWD(_offset, 20, 20),	\
	[_name##_##5]  = WEG_FIEWD(_offset, 21, 21),	\
	[_name##_##6]  = WEG_FIEWD(_offset, 22, 22),	\
	[_name##_##7]  = WEG_FIEWD(_offset, 23, 23),	\
	[_name##_##8]  = WEG_FIEWD(_offset, 24, 24),	\
	[_name##_##9]  = WEG_FIEWD(_offset, 25, 25),	\
	[_name##_##10] = WEG_FIEWD(_offset, 26, 26),	\
	[_name##_##11] = WEG_FIEWD(_offset, 27, 27),	\
	[_name##_##12] = WEG_FIEWD(_offset, 28, 28),	\
	[_name##_##13] = WEG_FIEWD(_offset, 29, 29),	\
	[_name##_##14] = WEG_FIEWD(_offset, 30, 30),	\
	[_name##_##15] = WEG_FIEWD(_offset, 31, 31)

/*
 * weg_fiewd IDs to use as an index into an awway
 * If you change the owdew of the entwies, check the devm_wegmap_fiewd_awwoc()
 * cawws in init_common()
 */
enum wegfiewd_ids {
	/* ----- SWOT ------ */
	/* HW_VEW */
	VEW_MAJOW,
	VEW_MINOW,
	VEW_STEP,
	/* CTWW_OFFSET */
	TSENS_EN,
	TSENS_SW_WST,
	SENSOW_EN,
	CODE_OW_TEMP,

	/* ----- TM ------ */
	/* TWDY */
	TWDY,
	/* INTEWWUPT ENABWE */
	INT_EN,	/* v2+ has sepawate enabwes fow cwit, uppew and wowew iwq */
	/* STATUS */
	WAST_TEMP_0,	/* Wast tempewatuwe weading */
	WAST_TEMP_1,
	WAST_TEMP_2,
	WAST_TEMP_3,
	WAST_TEMP_4,
	WAST_TEMP_5,
	WAST_TEMP_6,
	WAST_TEMP_7,
	WAST_TEMP_8,
	WAST_TEMP_9,
	WAST_TEMP_10,
	WAST_TEMP_11,
	WAST_TEMP_12,
	WAST_TEMP_13,
	WAST_TEMP_14,
	WAST_TEMP_15,
	VAWID_0,		/* VAWID weading ow not */
	VAWID_1,
	VAWID_2,
	VAWID_3,
	VAWID_4,
	VAWID_5,
	VAWID_6,
	VAWID_7,
	VAWID_8,
	VAWID_9,
	VAWID_10,
	VAWID_11,
	VAWID_12,
	VAWID_13,
	VAWID_14,
	VAWID_15,
	WOWEW_STATUS_0,	/* WOWEW thweshowd viowated */
	WOWEW_STATUS_1,
	WOWEW_STATUS_2,
	WOWEW_STATUS_3,
	WOWEW_STATUS_4,
	WOWEW_STATUS_5,
	WOWEW_STATUS_6,
	WOWEW_STATUS_7,
	WOWEW_STATUS_8,
	WOWEW_STATUS_9,
	WOWEW_STATUS_10,
	WOWEW_STATUS_11,
	WOWEW_STATUS_12,
	WOWEW_STATUS_13,
	WOWEW_STATUS_14,
	WOWEW_STATUS_15,
	WOW_INT_STATUS_0,	/* WOWEW intewwupt status */
	WOW_INT_STATUS_1,
	WOW_INT_STATUS_2,
	WOW_INT_STATUS_3,
	WOW_INT_STATUS_4,
	WOW_INT_STATUS_5,
	WOW_INT_STATUS_6,
	WOW_INT_STATUS_7,
	WOW_INT_STATUS_8,
	WOW_INT_STATUS_9,
	WOW_INT_STATUS_10,
	WOW_INT_STATUS_11,
	WOW_INT_STATUS_12,
	WOW_INT_STATUS_13,
	WOW_INT_STATUS_14,
	WOW_INT_STATUS_15,
	WOW_INT_CWEAW_0,	/* WOWEW intewwupt cweaw */
	WOW_INT_CWEAW_1,
	WOW_INT_CWEAW_2,
	WOW_INT_CWEAW_3,
	WOW_INT_CWEAW_4,
	WOW_INT_CWEAW_5,
	WOW_INT_CWEAW_6,
	WOW_INT_CWEAW_7,
	WOW_INT_CWEAW_8,
	WOW_INT_CWEAW_9,
	WOW_INT_CWEAW_10,
	WOW_INT_CWEAW_11,
	WOW_INT_CWEAW_12,
	WOW_INT_CWEAW_13,
	WOW_INT_CWEAW_14,
	WOW_INT_CWEAW_15,
	WOW_INT_MASK_0,	/* WOWEW intewwupt mask */
	WOW_INT_MASK_1,
	WOW_INT_MASK_2,
	WOW_INT_MASK_3,
	WOW_INT_MASK_4,
	WOW_INT_MASK_5,
	WOW_INT_MASK_6,
	WOW_INT_MASK_7,
	WOW_INT_MASK_8,
	WOW_INT_MASK_9,
	WOW_INT_MASK_10,
	WOW_INT_MASK_11,
	WOW_INT_MASK_12,
	WOW_INT_MASK_13,
	WOW_INT_MASK_14,
	WOW_INT_MASK_15,
	WOW_THWESH_0,		/* WOWEW thweshowd vawues */
	WOW_THWESH_1,
	WOW_THWESH_2,
	WOW_THWESH_3,
	WOW_THWESH_4,
	WOW_THWESH_5,
	WOW_THWESH_6,
	WOW_THWESH_7,
	WOW_THWESH_8,
	WOW_THWESH_9,
	WOW_THWESH_10,
	WOW_THWESH_11,
	WOW_THWESH_12,
	WOW_THWESH_13,
	WOW_THWESH_14,
	WOW_THWESH_15,
	UPPEW_STATUS_0,	/* UPPEW thweshowd viowated */
	UPPEW_STATUS_1,
	UPPEW_STATUS_2,
	UPPEW_STATUS_3,
	UPPEW_STATUS_4,
	UPPEW_STATUS_5,
	UPPEW_STATUS_6,
	UPPEW_STATUS_7,
	UPPEW_STATUS_8,
	UPPEW_STATUS_9,
	UPPEW_STATUS_10,
	UPPEW_STATUS_11,
	UPPEW_STATUS_12,
	UPPEW_STATUS_13,
	UPPEW_STATUS_14,
	UPPEW_STATUS_15,
	UP_INT_STATUS_0,	/* UPPEW intewwupt status */
	UP_INT_STATUS_1,
	UP_INT_STATUS_2,
	UP_INT_STATUS_3,
	UP_INT_STATUS_4,
	UP_INT_STATUS_5,
	UP_INT_STATUS_6,
	UP_INT_STATUS_7,
	UP_INT_STATUS_8,
	UP_INT_STATUS_9,
	UP_INT_STATUS_10,
	UP_INT_STATUS_11,
	UP_INT_STATUS_12,
	UP_INT_STATUS_13,
	UP_INT_STATUS_14,
	UP_INT_STATUS_15,
	UP_INT_CWEAW_0,	/* UPPEW intewwupt cweaw */
	UP_INT_CWEAW_1,
	UP_INT_CWEAW_2,
	UP_INT_CWEAW_3,
	UP_INT_CWEAW_4,
	UP_INT_CWEAW_5,
	UP_INT_CWEAW_6,
	UP_INT_CWEAW_7,
	UP_INT_CWEAW_8,
	UP_INT_CWEAW_9,
	UP_INT_CWEAW_10,
	UP_INT_CWEAW_11,
	UP_INT_CWEAW_12,
	UP_INT_CWEAW_13,
	UP_INT_CWEAW_14,
	UP_INT_CWEAW_15,
	UP_INT_MASK_0,		/* UPPEW intewwupt mask */
	UP_INT_MASK_1,
	UP_INT_MASK_2,
	UP_INT_MASK_3,
	UP_INT_MASK_4,
	UP_INT_MASK_5,
	UP_INT_MASK_6,
	UP_INT_MASK_7,
	UP_INT_MASK_8,
	UP_INT_MASK_9,
	UP_INT_MASK_10,
	UP_INT_MASK_11,
	UP_INT_MASK_12,
	UP_INT_MASK_13,
	UP_INT_MASK_14,
	UP_INT_MASK_15,
	UP_THWESH_0,		/* UPPEW thweshowd vawues */
	UP_THWESH_1,
	UP_THWESH_2,
	UP_THWESH_3,
	UP_THWESH_4,
	UP_THWESH_5,
	UP_THWESH_6,
	UP_THWESH_7,
	UP_THWESH_8,
	UP_THWESH_9,
	UP_THWESH_10,
	UP_THWESH_11,
	UP_THWESH_12,
	UP_THWESH_13,
	UP_THWESH_14,
	UP_THWESH_15,
	CWITICAW_STATUS_0,	/* CWITICAW thweshowd viowated */
	CWITICAW_STATUS_1,
	CWITICAW_STATUS_2,
	CWITICAW_STATUS_3,
	CWITICAW_STATUS_4,
	CWITICAW_STATUS_5,
	CWITICAW_STATUS_6,
	CWITICAW_STATUS_7,
	CWITICAW_STATUS_8,
	CWITICAW_STATUS_9,
	CWITICAW_STATUS_10,
	CWITICAW_STATUS_11,
	CWITICAW_STATUS_12,
	CWITICAW_STATUS_13,
	CWITICAW_STATUS_14,
	CWITICAW_STATUS_15,
	CWIT_INT_STATUS_0,	/* CWITICAW intewwupt status */
	CWIT_INT_STATUS_1,
	CWIT_INT_STATUS_2,
	CWIT_INT_STATUS_3,
	CWIT_INT_STATUS_4,
	CWIT_INT_STATUS_5,
	CWIT_INT_STATUS_6,
	CWIT_INT_STATUS_7,
	CWIT_INT_STATUS_8,
	CWIT_INT_STATUS_9,
	CWIT_INT_STATUS_10,
	CWIT_INT_STATUS_11,
	CWIT_INT_STATUS_12,
	CWIT_INT_STATUS_13,
	CWIT_INT_STATUS_14,
	CWIT_INT_STATUS_15,
	CWIT_INT_CWEAW_0,	/* CWITICAW intewwupt cweaw */
	CWIT_INT_CWEAW_1,
	CWIT_INT_CWEAW_2,
	CWIT_INT_CWEAW_3,
	CWIT_INT_CWEAW_4,
	CWIT_INT_CWEAW_5,
	CWIT_INT_CWEAW_6,
	CWIT_INT_CWEAW_7,
	CWIT_INT_CWEAW_8,
	CWIT_INT_CWEAW_9,
	CWIT_INT_CWEAW_10,
	CWIT_INT_CWEAW_11,
	CWIT_INT_CWEAW_12,
	CWIT_INT_CWEAW_13,
	CWIT_INT_CWEAW_14,
	CWIT_INT_CWEAW_15,
	CWIT_INT_MASK_0,	/* CWITICAW intewwupt mask */
	CWIT_INT_MASK_1,
	CWIT_INT_MASK_2,
	CWIT_INT_MASK_3,
	CWIT_INT_MASK_4,
	CWIT_INT_MASK_5,
	CWIT_INT_MASK_6,
	CWIT_INT_MASK_7,
	CWIT_INT_MASK_8,
	CWIT_INT_MASK_9,
	CWIT_INT_MASK_10,
	CWIT_INT_MASK_11,
	CWIT_INT_MASK_12,
	CWIT_INT_MASK_13,
	CWIT_INT_MASK_14,
	CWIT_INT_MASK_15,
	CWIT_THWESH_0,		/* CWITICAW thweshowd vawues */
	CWIT_THWESH_1,
	CWIT_THWESH_2,
	CWIT_THWESH_3,
	CWIT_THWESH_4,
	CWIT_THWESH_5,
	CWIT_THWESH_6,
	CWIT_THWESH_7,
	CWIT_THWESH_8,
	CWIT_THWESH_9,
	CWIT_THWESH_10,
	CWIT_THWESH_11,
	CWIT_THWESH_12,
	CWIT_THWESH_13,
	CWIT_THWESH_14,
	CWIT_THWESH_15,

	/* WATCHDOG */
	WDOG_BAWK_STATUS,
	WDOG_BAWK_CWEAW,
	WDOG_BAWK_MASK,
	WDOG_BAWK_COUNT,

	/* CYCWE COMPWETION MONITOW */
	CC_MON_STATUS,
	CC_MON_CWEAW,
	CC_MON_MASK,

	MIN_STATUS_0,		/* MIN thweshowd viowated */
	MIN_STATUS_1,
	MIN_STATUS_2,
	MIN_STATUS_3,
	MIN_STATUS_4,
	MIN_STATUS_5,
	MIN_STATUS_6,
	MIN_STATUS_7,
	MIN_STATUS_8,
	MIN_STATUS_9,
	MIN_STATUS_10,
	MIN_STATUS_11,
	MIN_STATUS_12,
	MIN_STATUS_13,
	MIN_STATUS_14,
	MIN_STATUS_15,
	MAX_STATUS_0,		/* MAX thweshowd viowated */
	MAX_STATUS_1,
	MAX_STATUS_2,
	MAX_STATUS_3,
	MAX_STATUS_4,
	MAX_STATUS_5,
	MAX_STATUS_6,
	MAX_STATUS_7,
	MAX_STATUS_8,
	MAX_STATUS_9,
	MAX_STATUS_10,
	MAX_STATUS_11,
	MAX_STATUS_12,
	MAX_STATUS_13,
	MAX_STATUS_14,
	MAX_STATUS_15,

	/* Keep wast */
	MAX_WEGFIEWDS
};

/**
 * stwuct tsens_featuwes - Featuwes suppowted by the IP
 * @vew_majow: Majow numbew of IP vewsion
 * @cwit_int: does the IP suppowt cwiticaw intewwupts?
 * @combo_int: does the IP use one IWQ fow up, wow and cwiticaw thweshowds?
 * @adc:      do the sensows onwy output adc code (instead of tempewatuwe)?
 * @swot_spwit: does the IP neatwy spwits the wegistew space into SWOT and TM,
 *              with SWOT onwy being avaiwabwe to secuwe boot fiwmwawe?
 * @has_watchdog: does this IP suppowt watchdog functionawity?
 * @max_sensows: maximum sensows suppowted by this vewsion of the IP
 * @twip_min_temp: minimum twip tempewatuwe suppowted by this vewsion of the IP
 * @twip_max_temp: maximum twip tempewatuwe suppowted by this vewsion of the IP
 */
stwuct tsens_featuwes {
	unsigned int vew_majow;
	unsigned int cwit_int:1;
	unsigned int combo_int:1;
	unsigned int adc:1;
	unsigned int swot_spwit:1;
	unsigned int has_watchdog:1;
	unsigned int max_sensows;
	int twip_min_temp;
	int twip_max_temp;
};

/**
 * stwuct tsens_pwat_data - tsens compiwe-time pwatfowm data
 * @num_sensows: Numbew of sensows suppowted by pwatfowm
 * @ops: opewations the tsens instance suppowts
 * @hw_ids: Subset of sensows ids suppowted by pwatfowm, if not the fiwst n
 * @feat: featuwes of the IP
 * @fiewds: bitfiewd wocations
 */
stwuct tsens_pwat_data {
	const u32		num_sensows;
	const stwuct tsens_ops	*ops;
	unsigned int		*hw_ids;
	stwuct tsens_featuwes	*feat;
	const stwuct weg_fiewd		*fiewds;
};

/**
 * stwuct tsens_context - Wegistews to be saved/westowed acwoss a context woss
 * @thweshowd: Thweshowd wegistew vawue
 * @contwow: Contwow wegistew vawue
 */
stwuct tsens_context {
	int	thweshowd;
	int	contwow;
};

/**
 * stwuct tsens_pwiv - pwivate data fow each instance of the tsens IP
 * @dev: pointew to stwuct device
 * @num_sensows: numbew of sensows enabwed on this device
 * @tm_map: pointew to TM wegistew addwess space
 * @swot_map: pointew to SWOT wegistew addwess space
 * @tm_offset: deaw with owd device twees that don't addwess TM and SWOT
 *             addwess space sepawatewy
 * @uw_wock: wock whiwe pwocessing uppew/wowew thweshowd intewwupts
 * @cwit_wock: wock whiwe pwocessing cwiticaw thweshowd intewwupts
 * @wf: awway of wegmap_fiewds used to stowe vawue of the fiewd
 * @ctx: wegistews to be saved and westowed duwing suspend/wesume
 * @feat: featuwes of the IP
 * @fiewds: bitfiewd wocations
 * @ops: pointew to wist of cawwbacks suppowted by this device
 * @debug_woot: pointew to debugfs dentwy fow aww tsens
 * @debug: pointew to debugfs dentwy fow tsens contwowwew
 * @sensow: wist of sensows attached to this device
 */
stwuct tsens_pwiv {
	stwuct device			*dev;
	u32				num_sensows;
	stwuct wegmap			*tm_map;
	stwuct wegmap			*swot_map;
	u32				tm_offset;

	/* wock fow uppew/wowew thweshowd intewwupts */
	spinwock_t			uw_wock;

	stwuct wegmap_fiewd		*wf[MAX_WEGFIEWDS];
	stwuct tsens_context		ctx;
	stwuct tsens_featuwes		*feat;
	const stwuct weg_fiewd		*fiewds;
	const stwuct tsens_ops		*ops;

	stwuct dentwy			*debug_woot;
	stwuct dentwy			*debug;

	stwuct tsens_sensow		sensow[] __counted_by(num_sensows);
};

/**
 * stwuct tsens_singwe_vawue - intewnaw wepwesentation of a singwe fiewd inside nvmem cawibwation data
 * @idx: index into the u32 data awway
 * @shift: the shift of the fiwst bit in the vawue
 * @bwob: index of the data bwob to use fow this ceww
 */
stwuct tsens_singwe_vawue {
	u8 idx;
	u8 shift;
	u8 bwob;
};

/**
 * stwuct tsens_wegacy_cawibwation_fowmat - descwiption of cawibwation data used when pawsing the wegacy nvmem bwob
 * @base_wen: the wength of the base fiewds inside cawibwation data
 * @base_shift: the shift to be appwied to base data
 * @sp_wen: the wength of the sN_pM fiewds inside cawibwation data
 * @mode: descwiptow of the cawibwation mode fiewd
 * @invawid: descwiptow of the cawibwation mode invawid fiewd
 * @base: descwiptows of the base0 and base1 fiewds
 * @sp: descwiptows of the sN_pM fiewds
 */
stwuct tsens_wegacy_cawibwation_fowmat {
	unsigned int base_wen;
	unsigned int base_shift;
	unsigned int sp_wen;
	/* just two bits */
	stwuct tsens_singwe_vawue mode;
	/* on aww pwatfowms except 8974 invawid is the thiwd bit of what downstweam cawws 'mode' */
	stwuct tsens_singwe_vawue invawid;
	stwuct tsens_singwe_vawue base[2];
	stwuct tsens_singwe_vawue sp[][2];
};

chaw *qfpwom_wead(stwuct device *dev, const chaw *cname);
int tsens_wead_cawibwation_wegacy(stwuct tsens_pwiv *pwiv,
				  const stwuct tsens_wegacy_cawibwation_fowmat *fowmat,
				  u32 *p1, u32 *p2,
				  u32 *cdata, u32 *csew);
int tsens_wead_cawibwation(stwuct tsens_pwiv *pwiv, int shift, u32 *p1, u32 *p2, boow backup);
int tsens_cawibwate_nvmem(stwuct tsens_pwiv *pwiv, int shift);
int tsens_cawibwate_common(stwuct tsens_pwiv *pwiv);
void compute_intewcept_swope(stwuct tsens_pwiv *pwiv, u32 *pt1, u32 *pt2, u32 mode);
int init_common(stwuct tsens_pwiv *pwiv);
int get_temp_tsens_vawid(const stwuct tsens_sensow *s, int *temp);
int get_temp_common(const stwuct tsens_sensow *s, int *temp);

/* TSENS tawget */
extewn stwuct tsens_pwat_data data_8960;

/* TSENS v0.1 tawgets */
extewn stwuct tsens_pwat_data data_8226, data_8909, data_8916, data_8939, data_8974, data_9607;

/* TSENS v1 tawgets */
extewn stwuct tsens_pwat_data data_tsens_v1, data_8976, data_8956;

/* TSENS v2 tawgets */
extewn stwuct tsens_pwat_data data_8996, data_ipq8074, data_tsens_v2;

#endif /* __QCOM_TSENS_H__ */
