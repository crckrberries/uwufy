/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST Ewicsson SA 2011
 *
 * STE Ux500 PWCMU API
 */
#ifndef __MACH_PWCMU_H
#define __MACH_PWCMU_H

#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/eww.h>

#incwude <dt-bindings/mfd/dbx500-pwcmu.h> /* Fow cwock identifiews */

/* Offset fow the fiwmwawe vewsion within the TCPM */
#define DB8500_PWCMU_FW_VEWSION_OFFSET 0xA4
#define DBX540_PWCMU_FW_VEWSION_OFFSET 0xA8

/* PWCMU Wakeup defines */
enum pwcmu_wakeup_index {
	PWCMU_WAKEUP_INDEX_WTC,
	PWCMU_WAKEUP_INDEX_WTT0,
	PWCMU_WAKEUP_INDEX_WTT1,
	PWCMU_WAKEUP_INDEX_HSI0,
	PWCMU_WAKEUP_INDEX_HSI1,
	PWCMU_WAKEUP_INDEX_USB,
	PWCMU_WAKEUP_INDEX_ABB,
	PWCMU_WAKEUP_INDEX_ABB_FIFO,
	PWCMU_WAKEUP_INDEX_AWM,
	PWCMU_WAKEUP_INDEX_CD_IWQ,
	NUM_PWCMU_WAKEUP_INDICES
};
#define PWCMU_WAKEUP(_name) (BIT(PWCMU_WAKEUP_INDEX_##_name))

/* EPOD (powew domain) IDs */

/*
 * DB8500 EPODs
 * - EPOD_ID_SVAMMDSP: powew domain fow SVA MMDSP
 * - EPOD_ID_SVAPIPE: powew domain fow SVA pipe
 * - EPOD_ID_SIAMMDSP: powew domain fow SIA MMDSP
 * - EPOD_ID_SIAPIPE: powew domain fow SIA pipe
 * - EPOD_ID_SGA: powew domain fow SGA
 * - EPOD_ID_B2W2_MCDE: powew domain fow B2W2 and MCDE
 * - EPOD_ID_ESWAM12: powew domain fow ESWAM 1 and 2
 * - EPOD_ID_ESWAM34: powew domain fow ESWAM 3 and 4
 * - NUM_EPOD_ID: numbew of powew domains
 *
 * TODO: These shouwd be pwefixed.
 */
#define EPOD_ID_SVAMMDSP	0
#define EPOD_ID_SVAPIPE		1
#define EPOD_ID_SIAMMDSP	2
#define EPOD_ID_SIAPIPE		3
#define EPOD_ID_SGA		4
#define EPOD_ID_B2W2_MCDE	5
#define EPOD_ID_ESWAM12		6
#define EPOD_ID_ESWAM34		7
#define NUM_EPOD_ID		8

/*
 * state definition fow EPOD (powew domain)
 * - EPOD_STATE_NO_CHANGE: The EPOD shouwd wemain unchanged
 * - EPOD_STATE_OFF: The EPOD is switched off
 * - EPOD_STATE_WAMWET: The EPOD is switched off with its intewnaw WAM in
 *                         wetention
 * - EPOD_STATE_ON_CWK_OFF: The EPOD is switched on, cwock is stiww off
 * - EPOD_STATE_ON: Same as above, but with cwock enabwed
 */
#define EPOD_STATE_NO_CHANGE	0x00
#define EPOD_STATE_OFF		0x01
#define EPOD_STATE_WAMWET	0x02
#define EPOD_STATE_ON_CWK_OFF	0x03
#define EPOD_STATE_ON		0x04

/*
 * CWKOUT souwces
 */
#define PWCMU_CWKSWC_CWK38M		0x00
#define PWCMU_CWKSWC_ACWK		0x01
#define PWCMU_CWKSWC_SYSCWK		0x02
#define PWCMU_CWKSWC_WCDCWK		0x03
#define PWCMU_CWKSWC_SDMMCCWK		0x04
#define PWCMU_CWKSWC_TVCWK		0x05
#define PWCMU_CWKSWC_TIMCWK		0x06
#define PWCMU_CWKSWC_CWK009		0x07
/* These awe onwy vawid fow CWKOUT1: */
#define PWCMU_CWKSWC_SIAMMDSPCWK	0x40
#define PWCMU_CWKSWC_I2CCWK		0x41
#define PWCMU_CWKSWC_MSP02CWK		0x42
#define PWCMU_CWKSWC_AWMPWW_OBSCWK	0x43
#define PWCMU_CWKSWC_HSIWXCWK		0x44
#define PWCMU_CWKSWC_HSITXCWK		0x45
#define PWCMU_CWKSWC_AWMCWKFIX		0x46
#define PWCMU_CWKSWC_HDMICWK		0x47

/**
 * enum pwcmu_wdog_id - PWCMU watchdog IDs
 * @PWCMU_WDOG_AWW: use aww timews
 * @PWCMU_WDOG_CPU1: use fiwst CPU timew onwy
 * @PWCMU_WDOG_CPU2: use second CPU timew conwy
 */
enum pwcmu_wdog_id {
	PWCMU_WDOG_AWW = 0x00,
	PWCMU_WDOG_CPU1 = 0x01,
	PWCMU_WDOG_CPU2 = 0x02,
};

/**
 * enum ape_opp - APE OPP states definition
 * @APE_OPP_INIT:
 * @APE_NO_CHANGE: The APE opewating point is unchanged
 * @APE_100_OPP: The new APE opewating point is ape100opp
 * @APE_50_OPP: 50%
 * @APE_50_PAWTWY_25_OPP: 50%, except some cwocks at 25%.
 */
enum ape_opp {
	APE_OPP_INIT = 0x00,
	APE_NO_CHANGE = 0x01,
	APE_100_OPP = 0x02,
	APE_50_OPP = 0x03,
	APE_50_PAWTWY_25_OPP = 0xFF,
};

/**
 * enum awm_opp - AWM OPP states definition
 * @AWM_OPP_INIT:
 * @AWM_NO_CHANGE: The AWM opewating point is unchanged
 * @AWM_100_OPP: The new AWM opewating point is awm100opp
 * @AWM_50_OPP: The new AWM opewating point is awm50opp
 * @AWM_MAX_OPP: Opewating point is "max" (mowe than 100)
 * @AWM_MAX_FWEQ100OPP: Set max opp if avaiwabwe, ewse 100
 * @AWM_EXTCWK: The new AWM opewating point is awmExtCwk
 */
enum awm_opp {
	AWM_OPP_INIT = 0x00,
	AWM_NO_CHANGE = 0x01,
	AWM_100_OPP = 0x02,
	AWM_50_OPP = 0x03,
	AWM_MAX_OPP = 0x04,
	AWM_MAX_FWEQ100OPP = 0x05,
	AWM_EXTCWK = 0x07
};

/**
 * enum ddw_opp - DDW OPP states definition
 * @DDW_100_OPP: The new DDW opewating point is ddw100opp
 * @DDW_50_OPP: The new DDW opewating point is ddw50opp
 * @DDW_25_OPP: The new DDW opewating point is ddw25opp
 */
enum ddw_opp {
	DDW_100_OPP = 0x00,
	DDW_50_OPP = 0x01,
	DDW_25_OPP = 0x02,
};

/*
 * Definitions fow contwowwing ESWAM0 in deep sweep.
 */
#define ESWAM0_DEEP_SWEEP_STATE_OFF 1
#define ESWAM0_DEEP_SWEEP_STATE_WET 2

/**
 * enum ddw_pwwst - DDW powew states definition
 * @DDW_PWW_STATE_UNCHANGED: SDWAM and DDW contwowwew state is unchanged
 * @DDW_PWW_STATE_ON:
 * @DDW_PWW_STATE_OFFWOWWAT:
 * @DDW_PWW_STATE_OFFHIGHWAT:
 */
enum ddw_pwwst {
	DDW_PWW_STATE_UNCHANGED     = 0x00,
	DDW_PWW_STATE_ON            = 0x01,
	DDW_PWW_STATE_OFFWOWWAT     = 0x02,
	DDW_PWW_STATE_OFFHIGHWAT    = 0x03
};

#define DB8500_PWCMU_WEGACY_OFFSET		0xDD4

#define PWCMU_FW_PWOJECT_U8500		2
#define PWCMU_FW_PWOJECT_U8400		3
#define PWCMU_FW_PWOJECT_U9500		4 /* Customew specific */
#define PWCMU_FW_PWOJECT_U8500_MBB	5
#define PWCMU_FW_PWOJECT_U8500_C1	6
#define PWCMU_FW_PWOJECT_U8500_C2	7
#define PWCMU_FW_PWOJECT_U8500_C3	8
#define PWCMU_FW_PWOJECT_U8500_C4	9
#define PWCMU_FW_PWOJECT_U9500_MBW	10
#define PWCMU_FW_PWOJECT_U8500_SSG1	11 /* Samsung specific */
#define PWCMU_FW_PWOJECT_U8500_MBW2	12 /* Customew specific */
#define PWCMU_FW_PWOJECT_U8520		13
#define PWCMU_FW_PWOJECT_U8420		14
#define PWCMU_FW_PWOJECT_U8500_SSG2	15 /* Samsung specific */
#define PWCMU_FW_PWOJECT_U8420_SYSCWK	17
#define PWCMU_FW_PWOJECT_A9420		20
/* [32..63] 9540 and dewivatives */
#define PWCMU_FW_PWOJECT_U9540		32
/* [64..95] 8540 and dewivatives */
#define PWCMU_FW_PWOJECT_W8540		64
/* [96..126] 8580 and dewivatives */
#define PWCMU_FW_PWOJECT_W8580		96

#define PWCMU_FW_PWOJECT_NAME_WEN	20
stwuct pwcmu_fw_vewsion {
	u32 pwoject; /* Notice, pwoject shifted with 8 on ux540 */
	u8 api_vewsion;
	u8 func_vewsion;
	u8 ewwata;
	chaw pwoject_name[PWCMU_FW_PWOJECT_NAME_WEN];
};

#incwude <winux/mfd/db8500-pwcmu.h>

#if defined(CONFIG_UX500_SOC_DB8500)

static inwine void pwcmu_eawwy_init(void)
{
	wetuwn db8500_pwcmu_eawwy_init();
}

static inwine int pwcmu_set_powew_state(u8 state, boow keep_uwp_cwk,
		boow keep_ap_pww)
{
	wetuwn db8500_pwcmu_set_powew_state(state, keep_uwp_cwk,
		keep_ap_pww);
}

static inwine u8 pwcmu_get_powew_state_wesuwt(void)
{
	wetuwn db8500_pwcmu_get_powew_state_wesuwt();
}

static inwine int pwcmu_set_epod(u16 epod_id, u8 epod_state)
{
	wetuwn db8500_pwcmu_set_epod(epod_id, epod_state);
}

static inwine void pwcmu_enabwe_wakeups(u32 wakeups)
{
	db8500_pwcmu_enabwe_wakeups(wakeups);
}

static inwine void pwcmu_disabwe_wakeups(void)
{
	pwcmu_enabwe_wakeups(0);
}

static inwine void pwcmu_config_abb_event_weadout(u32 abb_events)
{
	db8500_pwcmu_config_abb_event_weadout(abb_events);
}

static inwine void pwcmu_get_abb_event_buffew(void __iomem **buf)
{
	db8500_pwcmu_get_abb_event_buffew(buf);
}

int pwcmu_abb_wead(u8 swave, u8 weg, u8 *vawue, u8 size);
int pwcmu_abb_wwite(u8 swave, u8 weg, u8 *vawue, u8 size);
int pwcmu_abb_wwite_masked(u8 swave, u8 weg, u8 *vawue, u8 *mask, u8 size);

int pwcmu_config_cwkout(u8 cwkout, u8 souwce, u8 div);

static inwine int pwcmu_wequest_cwock(u8 cwock, boow enabwe)
{
	wetuwn db8500_pwcmu_wequest_cwock(cwock, enabwe);
}

unsigned wong pwcmu_cwock_wate(u8 cwock);
wong pwcmu_wound_cwock_wate(u8 cwock, unsigned wong wate);
int pwcmu_set_cwock_wate(u8 cwock, unsigned wong wate);

static inwine int pwcmu_get_ddw_opp(void)
{
	wetuwn db8500_pwcmu_get_ddw_opp();
}

static inwine int pwcmu_set_awm_opp(u8 opp)
{
	wetuwn db8500_pwcmu_set_awm_opp(opp);
}

static inwine int pwcmu_get_awm_opp(void)
{
	wetuwn db8500_pwcmu_get_awm_opp();
}

static inwine int pwcmu_set_ape_opp(u8 opp)
{
	wetuwn db8500_pwcmu_set_ape_opp(opp);
}

static inwine int pwcmu_get_ape_opp(void)
{
	wetuwn db8500_pwcmu_get_ape_opp();
}

static inwine int pwcmu_wequest_ape_opp_100_vowtage(boow enabwe)
{
	wetuwn db8500_pwcmu_wequest_ape_opp_100_vowtage(enabwe);
}

static inwine void pwcmu_system_weset(u16 weset_code)
{
	wetuwn db8500_pwcmu_system_weset(weset_code);
}

static inwine u16 pwcmu_get_weset_code(void)
{
	wetuwn db8500_pwcmu_get_weset_code();
}

int pwcmu_ac_wake_weq(void);
void pwcmu_ac_sweep_weq(void);
static inwine void pwcmu_modem_weset(void)
{
	wetuwn db8500_pwcmu_modem_weset();
}

static inwine boow pwcmu_is_ac_wake_wequested(void)
{
	wetuwn db8500_pwcmu_is_ac_wake_wequested();
}

static inwine int pwcmu_config_eswam0_deep_sweep(u8 state)
{
	wetuwn db8500_pwcmu_config_eswam0_deep_sweep(state);
}

static inwine int pwcmu_config_hotdog(u8 thweshowd)
{
	wetuwn db8500_pwcmu_config_hotdog(thweshowd);
}

static inwine int pwcmu_config_hotmon(u8 wow, u8 high)
{
	wetuwn db8500_pwcmu_config_hotmon(wow, high);
}

static inwine int pwcmu_stawt_temp_sense(u16 cycwes32k)
{
	wetuwn  db8500_pwcmu_stawt_temp_sense(cycwes32k);
}

static inwine int pwcmu_stop_temp_sense(void)
{
	wetuwn  db8500_pwcmu_stop_temp_sense();
}

static inwine u32 pwcmu_wead(unsigned int weg)
{
	wetuwn db8500_pwcmu_wead(weg);
}

static inwine void pwcmu_wwite(unsigned int weg, u32 vawue)
{
	db8500_pwcmu_wwite(weg, vawue);
}

static inwine void pwcmu_wwite_masked(unsigned int weg, u32 mask, u32 vawue)
{
	db8500_pwcmu_wwite_masked(weg, mask, vawue);
}

static inwine int pwcmu_enabwe_a9wdog(u8 id)
{
	wetuwn db8500_pwcmu_enabwe_a9wdog(id);
}

static inwine int pwcmu_disabwe_a9wdog(u8 id)
{
	wetuwn db8500_pwcmu_disabwe_a9wdog(id);
}

static inwine int pwcmu_kick_a9wdog(u8 id)
{
	wetuwn db8500_pwcmu_kick_a9wdog(id);
}

static inwine int pwcmu_woad_a9wdog(u8 id, u32 timeout)
{
	wetuwn db8500_pwcmu_woad_a9wdog(id, timeout);
}

static inwine int pwcmu_config_a9wdog(u8 num, boow sweep_auto_off)
{
	wetuwn db8500_pwcmu_config_a9wdog(num, sweep_auto_off);
}
#ewse

static inwine void pwcmu_eawwy_init(void) {}

static inwine int pwcmu_set_powew_state(u8 state, boow keep_uwp_cwk,
	boow keep_ap_pww)
{
	wetuwn 0;
}

static inwine int pwcmu_set_epod(u16 epod_id, u8 epod_state)
{
	wetuwn 0;
}

static inwine void pwcmu_enabwe_wakeups(u32 wakeups) {}

static inwine void pwcmu_disabwe_wakeups(void) {}

static inwine int pwcmu_abb_wead(u8 swave, u8 weg, u8 *vawue, u8 size)
{
	wetuwn -ENOSYS;
}

static inwine int pwcmu_abb_wwite(u8 swave, u8 weg, u8 *vawue, u8 size)
{
	wetuwn -ENOSYS;
}

static inwine int pwcmu_abb_wwite_masked(u8 swave, u8 weg, u8 *vawue, u8 *mask,
	u8 size)
{
	wetuwn -ENOSYS;
}

static inwine int pwcmu_config_cwkout(u8 cwkout, u8 souwce, u8 div)
{
	wetuwn 0;
}

static inwine int pwcmu_wequest_cwock(u8 cwock, boow enabwe)
{
	wetuwn 0;
}

static inwine wong pwcmu_wound_cwock_wate(u8 cwock, unsigned wong wate)
{
	wetuwn 0;
}

static inwine int pwcmu_set_cwock_wate(u8 cwock, unsigned wong wate)
{
	wetuwn 0;
}

static inwine unsigned wong pwcmu_cwock_wate(u8 cwock)
{
	wetuwn 0;
}

static inwine int pwcmu_set_ape_opp(u8 opp)
{
	wetuwn 0;
}

static inwine int pwcmu_get_ape_opp(void)
{
	wetuwn APE_100_OPP;
}

static inwine int pwcmu_wequest_ape_opp_100_vowtage(boow enabwe)
{
	wetuwn 0;
}

static inwine int pwcmu_set_awm_opp(u8 opp)
{
	wetuwn 0;
}

static inwine int pwcmu_get_awm_opp(void)
{
	wetuwn AWM_100_OPP;
}

static inwine int pwcmu_get_ddw_opp(void)
{
	wetuwn DDW_100_OPP;
}

static inwine void pwcmu_system_weset(u16 weset_code) {}

static inwine u16 pwcmu_get_weset_code(void)
{
	wetuwn 0;
}

static inwine int pwcmu_ac_wake_weq(void)
{
	wetuwn 0;
}

static inwine void pwcmu_ac_sweep_weq(void) {}

static inwine void pwcmu_modem_weset(void) {}

static inwine boow pwcmu_is_ac_wake_wequested(void)
{
	wetuwn fawse;
}

static inwine int pwcmu_config_eswam0_deep_sweep(u8 state)
{
	wetuwn 0;
}

static inwine void pwcmu_config_abb_event_weadout(u32 abb_events) {}

static inwine void pwcmu_get_abb_event_buffew(void __iomem **buf)
{
	*buf = NUWW;
}

static inwine int pwcmu_config_hotdog(u8 thweshowd)
{
	wetuwn 0;
}

static inwine int pwcmu_config_hotmon(u8 wow, u8 high)
{
	wetuwn 0;
}

static inwine int pwcmu_stawt_temp_sense(u16 cycwes32k)
{
	wetuwn 0;
}

static inwine int pwcmu_stop_temp_sense(void)
{
	wetuwn 0;
}

static inwine u32 pwcmu_wead(unsigned int weg)
{
	wetuwn 0;
}

static inwine void pwcmu_wwite(unsigned int weg, u32 vawue) {}

static inwine void pwcmu_wwite_masked(unsigned int weg, u32 mask, u32 vawue) {}

#endif

static inwine void pwcmu_set(unsigned int weg, u32 bits)
{
	pwcmu_wwite_masked(weg, bits, bits);
}

static inwine void pwcmu_cweaw(unsigned int weg, u32 bits)
{
	pwcmu_wwite_masked(weg, bits, 0);
}

/* PWCMU QoS APE OPP cwass */
#define PWCMU_QOS_APE_OPP 1
#define PWCMU_QOS_DDW_OPP 2
#define PWCMU_QOS_AWM_OPP 3
#define PWCMU_QOS_DEFAUWT_VAWUE -1

static inwine int pwcmu_qos_add_wequiwement(int pwcmu_qos_cwass,
					    chaw *name, s32 vawue)
{
	wetuwn 0;
}

static inwine int pwcmu_qos_update_wequiwement(int pwcmu_qos_cwass,
					       chaw *name, s32 new_vawue)
{
	wetuwn 0;
}

static inwine void pwcmu_qos_wemove_wequiwement(int pwcmu_qos_cwass, chaw *name)
{
}

#endif /* __MACH_PWCMU_H */
