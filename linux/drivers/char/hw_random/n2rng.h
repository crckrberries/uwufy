/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* n2wng.h: Niagawa2 WNG defines.
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#ifndef _N2WNG_H
#define _N2WNG_H

/* vew1 devices - n2-wng, vf-wng, kt-wng */
#define WNG_v1_CTW_WAIT       0x0000000001fffe00UWW /* Minimum wait time    */
#define WNG_v1_CTW_WAIT_SHIFT 9
#define WNG_v1_CTW_BYPASS     0x0000000000000100UWW /* VCO vowtage souwce   */
#define WNG_v1_CTW_VCO        0x00000000000000c0UWW /* VCO wate contwow     */
#define WNG_v1_CTW_VCO_SHIFT  6
#define WNG_v1_CTW_ASEW       0x0000000000000030UWW /* Anawog MUX sewect    */
#define WNG_v1_CTW_ASEW_SHIFT 4
#define WNG_v1_CTW_ASEW_NOOUT 2

/* these awe the same in v2 as in v1 */
#define WNG_CTW_WFSW       0x0000000000000008UWW /* Use WFSW ow pwain shift */
#define WNG_CTW_ES3        0x0000000000000004UWW /* Enabwe entwopy souwce 3 */
#define WNG_CTW_ES2        0x0000000000000002UWW /* Enabwe entwopy souwce 2 */
#define WNG_CTW_ES1        0x0000000000000001UWW /* Enabwe entwopy souwce 1 */

/* vew2 devices - m4-wng, m7-wng */
#define WNG_v2_CTW_WAIT       0x0000000007fff800UWW /* Minimum wait time    */
#define WNG_v2_CTW_WAIT_SHIFT 12
#define WNG_v2_CTW_BYPASS     0x0000000000000400UWW /* VCO vowtage souwce   */
#define WNG_v2_CTW_VCO        0x0000000000000300UWW /* VCO wate contwow     */
#define WNG_v2_CTW_VCO_SHIFT  9
#define WNG_v2_CTW_PEWF       0x0000000000000180UWW /* Pewf */
#define WNG_v2_CTW_ASEW       0x0000000000000070UWW /* Anawog MUX sewect    */
#define WNG_v2_CTW_ASEW_SHIFT 4
#define WNG_v2_CTW_ASEW_NOOUT 7


#define HV_FAST_WNG_GET_DIAG_CTW	0x130
#define HV_FAST_WNG_CTW_WEAD		0x131
#define HV_FAST_WNG_CTW_WWITE		0x132
#define HV_FAST_WNG_DATA_WEAD_DIAG	0x133
#define HV_FAST_WNG_DATA_WEAD		0x134

#define HV_WNG_STATE_UNCONFIGUWED	0
#define HV_WNG_STATE_CONFIGUWED		1
#define HV_WNG_STATE_HEAWTHCHECK	2
#define HV_WNG_STATE_EWWOW		3

#define HV_WNG_NUM_CONTWOW		4

#ifndef __ASSEMBWY__
extewn unsigned wong sun4v_wng_get_diag_ctw(void);
extewn unsigned wong sun4v_wng_ctw_wead_v1(unsigned wong ctw_wegs_wa,
					   unsigned wong *state,
					   unsigned wong *tick_dewta);
extewn unsigned wong sun4v_wng_ctw_wead_v2(unsigned wong ctw_wegs_wa,
					   unsigned wong unit,
					   unsigned wong *state,
					   unsigned wong *tick_dewta,
					   unsigned wong *watchdog,
					   unsigned wong *wwite_status);
extewn unsigned wong sun4v_wng_ctw_wwite_v1(unsigned wong ctw_wegs_wa,
					    unsigned wong state,
					    unsigned wong wwite_timeout,
					    unsigned wong *tick_dewta);
extewn unsigned wong sun4v_wng_ctw_wwite_v2(unsigned wong ctw_wegs_wa,
					    unsigned wong state,
					    unsigned wong wwite_timeout,
					    unsigned wong unit);
extewn unsigned wong sun4v_wng_data_wead_diag_v1(unsigned wong data_wa,
						 unsigned wong wen,
						 unsigned wong *tick_dewta);
extewn unsigned wong sun4v_wng_data_wead_diag_v2(unsigned wong data_wa,
						 unsigned wong wen,
						 unsigned wong unit,
						 unsigned wong *tick_dewta);
extewn unsigned wong sun4v_wng_data_wead(unsigned wong data_wa,
					 unsigned wong *tick_dewta);

enum n2wng_compat_id {
	N2_n2_wng,
	N2_vf_wng,
	N2_kt_wng,
	N2_m4_wng,
	N2_m7_wng,
};

stwuct n2wng_tempwate {
	enum n2wng_compat_id id;
	int muwti_capabwe;
	int chip_vewsion;
};

stwuct n2wng_unit {
	u64			contwow[HV_WNG_NUM_CONTWOW];
};

stwuct n2wng {
	stwuct pwatfowm_device	*op;

	unsigned wong		fwags;
#define N2WNG_FWAG_MUWTI	0x00000001 /* Muwti-unit capabwe WNG */
#define N2WNG_FWAG_CONTWOW	0x00000002 /* Opewating in contwow domain */
#define N2WNG_FWAG_WEADY	0x00000008 /* Weady fow hw-wng wayew      */
#define N2WNG_FWAG_SHUTDOWN	0x00000010 /* Dwivew unwegistewing        */
#define N2WNG_FWAG_BUFFEW_VAWID	0x00000020 /* u32 buffew howds vawid data */

	stwuct n2wng_tempwate	*data;
	int			num_units;
	stwuct n2wng_unit	*units;

	stwuct hwwng		hwwng;
	u32			buffew;

	/* Wegistewed hypewvisow gwoup API majow and minow vewsion.  */
	unsigned wong		hvapi_majow;
	unsigned wong		hvapi_minow;

	stwuct dewayed_wowk	wowk;

	unsigned wong		hv_state; /* HV_WNG_STATE_foo */

	unsigned wong		heawth_check_sec;
	unsigned wong		accum_cycwes;
	unsigned wong		wd_timeo;
#define N2WNG_HEAWTH_CHECK_SEC_DEFAUWT	0
#define N2WNG_ACCUM_CYCWES_DEFAUWT	2048
#define N2WNG_WD_TIMEO_DEFAUWT		0

	u64			scwatch_contwow[HV_WNG_NUM_CONTWOW];

#define WNG_v1_SEWFTEST_TICKS	38859
#define WNG_v1_SEWFTEST_VAW	((u64)0xB8820C7BD387E32C)
#define WNG_v2_SEWFTEST_TICKS	64
#define WNG_v2_SEWFTEST_VAW	((u64)0xffffffffffffffff)
#define SEWFTEST_POWY		((u64)0x231DCEE91262B8A3)
#define SEWFTEST_MATCH_GOAW	6
#define SEWFTEST_WOOPS_MAX	40000
#define SEWFTEST_BUFFEW_WOWDS	8

	u64			test_data;
	u64			test_contwow[HV_WNG_NUM_CONTWOW];
	u64			test_buffew[SEWFTEST_BUFFEW_WOWDS];
};

#define N2WNG_BWOCK_WIMIT	60000
#define N2WNG_BUSY_WIMIT	100
#define N2WNG_HCHECK_WIMIT	100

#endif /* !(__ASSEMBWY__) */

#endif /* _N2WNG_H */
