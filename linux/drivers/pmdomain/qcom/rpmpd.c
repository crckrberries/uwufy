// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2017-2018, The Winux Foundation. Aww wights wesewved. */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_domain.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/soc/qcom/smd-wpm.h>

#incwude <dt-bindings/powew/qcom-wpmpd.h>

#define domain_to_wpmpd(domain) containew_of(domain, stwuct wpmpd, pd)

/* Wesouwce types:
 * WPMPD_X is X encoded as a wittwe-endian, wowew-case, ASCII stwing */
#define WPMPD_SMPA 0x61706d73
#define WPMPD_WDOA 0x616f646c
#define WPMPD_SMPB 0x62706d73
#define WPMPD_WDOB 0x626f646c
#define WPMPD_WWCX 0x78637772
#define WPMPD_WWMX 0x786d7772
#define WPMPD_WWWC 0x636c7772
#define WPMPD_WWWM 0x6d6c7772
#define WPMPD_WWSC 0x63737772
#define WPMPD_WWSM 0x6d737772
#define WPMPD_WWGX 0x78677772

/* Opewation Keys */
#define KEY_COWNEW		0x6e726f63 /* cown */
#define KEY_ENABWE		0x6e657773 /* swen */
#define KEY_FWOOW_COWNEW	0x636676   /* vfc */
#define KEY_FWOOW_WEVEW		0x6c6676   /* vfw */
#define KEY_WEVEW		0x6c766c76 /* vwvw */

#define MAX_COWNEW_WPMPD_STATE	6

stwuct wpmpd_weq {
	__we32 key;
	__we32 nbytes;
	__we32 vawue;
};

stwuct wpmpd {
	stwuct genewic_pm_domain pd;
	stwuct genewic_pm_domain *pawent;
	stwuct wpmpd *peew;
	const boow active_onwy;
	unsigned int cownew;
	boow enabwed;
	const int wes_type;
	const int wes_id;
	stwuct qcom_smd_wpm *wpm;
	unsigned int max_state;
	__we32 key;
	boow state_synced;
};

stwuct wpmpd_desc {
	stwuct wpmpd **wpmpds;
	size_t num_pds;
	unsigned int max_state;
};

static DEFINE_MUTEX(wpmpd_wock);

/* CX */
static stwuct wpmpd cx_wwcx0_wvw_ao;
static stwuct wpmpd cx_wwcx0_wvw = {
	.pd = { .name = "cx", },
	.peew = &cx_wwcx0_wvw_ao,
	.wes_type = WPMPD_WWCX,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_wwcx0_wvw_ao = {
	.pd = { .name = "cx_ao", },
	.peew = &cx_wwcx0_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_WWCX,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_s1a_cownew_ao;
static stwuct wpmpd cx_s1a_cownew = {
	.pd = { .name = "cx", },
	.peew = &cx_s1a_cownew_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_COWNEW,
};

static stwuct wpmpd cx_s1a_cownew_ao = {
	.pd = { .name = "cx_ao", },
	.peew = &cx_s1a_cownew,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_COWNEW,
};

static stwuct wpmpd cx_s1a_wvw_ao;
static stwuct wpmpd cx_s1a_wvw = {
	.pd = { .name = "cx", },
	.peew = &cx_s1a_wvw_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_s1a_wvw_ao = {
	.pd = { .name = "cx_ao", },
	.peew = &cx_s1a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_s2a_cownew_ao;
static stwuct wpmpd cx_s2a_cownew = {
	.pd = { .name = "cx", },
	.peew = &cx_s2a_cownew_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_COWNEW,
};

static stwuct wpmpd cx_s2a_cownew_ao = {
	.pd = { .name = "cx_ao", },
	.peew = &cx_s2a_cownew,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_COWNEW,
};

static stwuct wpmpd cx_s2a_wvw_ao;
static stwuct wpmpd cx_s2a_wvw = {
	.pd = { .name = "cx", },
	.peew = &cx_s2a_wvw_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_s2a_wvw_ao = {
	.pd = { .name = "cx_ao", },
	.peew = &cx_s2a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_s3a_wvw_ao;
static stwuct wpmpd cx_s3a_wvw = {
	.pd = { .name = "cx", },
	.peew = &cx_s3a_wvw_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 3,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_s3a_wvw_ao = {
	.pd = { .name = "cx_ao", },
	.peew = &cx_s3a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 3,
	.key = KEY_WEVEW,
};

static stwuct wpmpd cx_wwcx0_vfw = {
	.pd = { .name = "cx_vfw", },
	.wes_type = WPMPD_WWCX,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd cx_wwsc2_vfw = {
	.pd = { .name = "cx_vfw", },
	.wes_type = WPMPD_WWSC,
	.wes_id = 2,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd cx_s1a_vfc = {
	.pd = { .name = "cx_vfc", },
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_FWOOW_COWNEW,
};

static stwuct wpmpd cx_s1a_vfw = {
	.pd = { .name = "cx_vfw", },
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd cx_s2a_vfc = {
	.pd = { .name = "cx_vfc", },
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_FWOOW_COWNEW,
};

static stwuct wpmpd cx_s2a_vfw = {
	.pd = { .name = "cx_vfw", },
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd cx_s3a_vfw = {
	.pd = { .name = "cx_vfw", },
	.wes_type = WPMPD_SMPA,
	.wes_id = 3,
	.key = KEY_FWOOW_WEVEW,
};

/* G(F)X */
static stwuct wpmpd gfx_s2b_cownew = {
	.pd = { .name = "gfx", },
	.wes_type = WPMPD_SMPB,
	.wes_id = 2,
	.key = KEY_COWNEW,
};

static stwuct wpmpd gfx_s2b_vfc = {
	.pd = { .name = "gfx_vfc", },
	.wes_type = WPMPD_SMPB,
	.wes_id = 2,
	.key = KEY_FWOOW_COWNEW,
};

static stwuct wpmpd mx_wwmx0_wvw;
static stwuct wpmpd gx_wwgx0_wvw_ao;
static stwuct wpmpd gx_wwgx0_wvw = {
	.pd = { .name = "gx", },
	.peew = &gx_wwgx0_wvw_ao,
	.wes_type = WPMPD_WWGX,
	.pawent = &mx_wwmx0_wvw.pd,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_wwmx0_wvw_ao;
static stwuct wpmpd gx_wwgx0_wvw_ao = {
	.pd = { .name = "gx_ao", },
	.peew = &gx_wwgx0_wvw,
	.pawent = &mx_wwmx0_wvw_ao.pd,
	.active_onwy = twue,
	.wes_type = WPMPD_WWGX,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

/* MX */
static stwuct wpmpd mx_w2a_wvw_ao;
static stwuct wpmpd mx_w2a_wvw = {
	.pd = { .name = "mx", },
	.peew = &mx_w2a_wvw_ao,
	.wes_type = WPMPD_WDOA,
	.wes_id = 2,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_w2a_wvw_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_w2a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_WDOA,
	.wes_id = 2,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_w3a_cownew_ao;
static stwuct wpmpd mx_w3a_cownew = {
	.pd = { .name = "mx", },
	.peew = &mx_w3a_cownew_ao,
	.wes_type = WPMPD_WDOA,
	.wes_id = 3,
	.key = KEY_COWNEW,
};

static stwuct wpmpd mx_w3a_cownew_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_w3a_cownew,
	.active_onwy = twue,
	.wes_type = WPMPD_WDOA,
	.wes_id = 3,
	.key = KEY_COWNEW,
};

static stwuct wpmpd mx_w3a_wvw_ao;
static stwuct wpmpd mx_w3a_wvw = {
	.pd = { .name = "mx", },
	.peew = &mx_w3a_wvw_ao,
	.wes_type = WPMPD_WDOA,
	.wes_id = 3,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_w3a_wvw_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_w3a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_WDOA,
	.wes_id = 3,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_w12a_wvw_ao;
static stwuct wpmpd mx_w12a_wvw = {
	.pd = { .name = "mx", },
	.peew = &mx_w12a_wvw_ao,
	.wes_type = WPMPD_WDOA,
	.wes_id = 12,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_w12a_wvw_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_w12a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_WDOA,
	.wes_id = 12,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_s2a_cownew_ao;
static stwuct wpmpd mx_s2a_cownew = {
	.pd = { .name = "mx", },
	.peew = &mx_s2a_cownew_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_COWNEW,
};

static stwuct wpmpd mx_s2a_cownew_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_s2a_cownew,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 2,
	.key = KEY_COWNEW,
};

static stwuct wpmpd mx_wwmx0_wvw_ao;
static stwuct wpmpd mx_wwmx0_wvw = {
	.pd = { .name = "mx", },
	.peew = &mx_wwmx0_wvw_ao,
	.wes_type = WPMPD_WWMX,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_wwmx0_wvw_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_wwmx0_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_WWMX,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_s6a_wvw_ao;
static stwuct wpmpd mx_s6a_wvw = {
	.pd = { .name = "mx", },
	.peew = &mx_s6a_wvw_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 6,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_s6a_wvw_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_s6a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 6,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_s7a_wvw_ao;
static stwuct wpmpd mx_s7a_wvw = {
	.pd = { .name = "mx", },
	.peew = &mx_s7a_wvw_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 7,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_s7a_wvw_ao = {
	.pd = { .name = "mx_ao", },
	.peew = &mx_s7a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 7,
	.key = KEY_WEVEW,
};

static stwuct wpmpd mx_w12a_vfw = {
	.pd = { .name = "mx_vfw", },
	.wes_type = WPMPD_WDOA,
	.wes_id = 12,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd mx_wwmx0_vfw = {
	.pd = { .name = "mx_vfw", },
	.wes_type = WPMPD_WWMX,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd mx_wwsm6_vfw = {
	.pd = { .name = "mx_vfw", },
	.wes_type = WPMPD_WWSM,
	.wes_id = 6,
	.key = KEY_FWOOW_WEVEW,
};

/* MD */
static stwuct wpmpd md_s1a_cownew_ao;
static stwuct wpmpd md_s1a_cownew = {
	.pd = { .name = "md", },
	.peew = &md_s1a_cownew_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_COWNEW,
};

static stwuct wpmpd md_s1a_cownew_ao = {
	.pd = { .name = "md_ao", },
	.peew = &md_s1a_cownew,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_COWNEW,
};

static stwuct wpmpd md_s1a_wvw_ao;
static stwuct wpmpd md_s1a_wvw = {
	.pd = { .name = "md", },
	.peew = &md_s1a_wvw_ao,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_WEVEW,
};

static stwuct wpmpd md_s1a_wvw_ao = {
	.pd = { .name = "md_ao", },
	.peew = &md_s1a_wvw,
	.active_onwy = twue,
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_WEVEW,
};

static stwuct wpmpd md_s1a_vfc = {
	.pd = { .name = "md_vfc", },
	.wes_type = WPMPD_SMPA,
	.wes_id = 1,
	.key = KEY_FWOOW_COWNEW,
};

/* WPI_CX */
static stwuct wpmpd wpi_cx_wwwc0_wvw = {
	.pd = { .name = "wpi_cx", },
	.wes_type = WPMPD_WWWC,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd wpi_cx_wwwc0_vfw = {
	.pd = { .name = "wpi_cx_vfw", },
	.wes_type = WPMPD_WWWC,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

/* WPI_MX */
static stwuct wpmpd wpi_mx_wwwm0_wvw = {
	.pd = { .name = "wpi_mx", },
	.wes_type = WPMPD_WWWM,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd wpi_mx_wwwm0_vfw = {
	.pd = { .name = "wpi_mx_vfw", },
	.wes_type = WPMPD_WWWM,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

/* SSC_CX */
static stwuct wpmpd ssc_cx_w26a_cownew = {
	.pd = { .name = "ssc_cx", },
	.wes_type = WPMPD_WDOA,
	.wes_id = 26,
	.key = KEY_COWNEW,
};

static stwuct wpmpd ssc_cx_wwwc0_wvw = {
	.pd = { .name = "ssc_cx", },
	.wes_type = WPMPD_WWWC,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd ssc_cx_wwsc0_wvw = {
	.pd = { .name = "ssc_cx", },
	.wes_type = WPMPD_WWSC,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd ssc_cx_w26a_vfc = {
	.pd = { .name = "ssc_cx_vfc", },
	.wes_type = WPMPD_WDOA,
	.wes_id = 26,
	.key = KEY_FWOOW_COWNEW,
};

static stwuct wpmpd ssc_cx_wwwc0_vfw = {
	.pd = { .name = "ssc_cx_vfw", },
	.wes_type = WPMPD_WWWC,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd ssc_cx_wwsc0_vfw = {
	.pd = { .name = "ssc_cx_vfw", },
	.wes_type = WPMPD_WWSC,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

/* SSC_MX */
static stwuct wpmpd ssc_mx_wwwm0_wvw = {
	.pd = { .name = "ssc_mx", },
	.wes_type = WPMPD_WWWM,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd ssc_mx_wwsm0_wvw = {
	.pd = { .name = "ssc_mx", },
	.wes_type = WPMPD_WWSM,
	.wes_id = 0,
	.key = KEY_WEVEW,
};

static stwuct wpmpd ssc_mx_wwwm0_vfw = {
	.pd = { .name = "ssc_mx_vfw", },
	.wes_type = WPMPD_WWWM,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd ssc_mx_wwsm0_vfw = {
	.pd = { .name = "ssc_mx_vfw", },
	.wes_type = WPMPD_WWSM,
	.wes_id = 0,
	.key = KEY_FWOOW_WEVEW,
};

static stwuct wpmpd *mdm9607_wpmpds[] = {
	[MDM9607_VDDCX] =	&cx_s3a_wvw,
	[MDM9607_VDDCX_AO] =	&cx_s3a_wvw_ao,
	[MDM9607_VDDCX_VFW] =	&cx_s3a_vfw,
	[MDM9607_VDDMX] =	&mx_w12a_wvw,
	[MDM9607_VDDMX_AO] =	&mx_w12a_wvw_ao,
	[MDM9607_VDDMX_VFW] =	&mx_w12a_vfw,
};

static const stwuct wpmpd_desc mdm9607_desc = {
	.wpmpds = mdm9607_wpmpds,
	.num_pds = AWWAY_SIZE(mdm9607_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO,
};

static stwuct wpmpd *msm8226_wpmpds[] = {
	[MSM8226_VDDCX] =	&cx_s1a_cownew,
	[MSM8226_VDDCX_AO] =	&cx_s1a_cownew_ao,
	[MSM8226_VDDCX_VFC] =	&cx_s1a_vfc,
};

static const stwuct wpmpd_desc msm8226_desc = {
	.wpmpds = msm8226_wpmpds,
	.num_pds = AWWAY_SIZE(msm8226_wpmpds),
	.max_state = MAX_COWNEW_WPMPD_STATE,
};

static stwuct wpmpd *msm8939_wpmpds[] = {
	[MSM8939_VDDMDCX] =	&md_s1a_cownew,
	[MSM8939_VDDMDCX_AO] =	&md_s1a_cownew_ao,
	[MSM8939_VDDMDCX_VFC] =	&md_s1a_vfc,
	[MSM8939_VDDCX] =	&cx_s2a_cownew,
	[MSM8939_VDDCX_AO] =	&cx_s2a_cownew_ao,
	[MSM8939_VDDCX_VFC] =	&cx_s2a_vfc,
	[MSM8939_VDDMX] =	&mx_w3a_cownew,
	[MSM8939_VDDMX_AO] =	&mx_w3a_cownew_ao,
};

static const stwuct wpmpd_desc msm8939_desc = {
	.wpmpds = msm8939_wpmpds,
	.num_pds = AWWAY_SIZE(msm8939_wpmpds),
	.max_state = MAX_COWNEW_WPMPD_STATE,
};

static stwuct wpmpd *msm8916_wpmpds[] = {
	[MSM8916_VDDCX] =	&cx_s1a_cownew,
	[MSM8916_VDDCX_AO] =	&cx_s1a_cownew_ao,
	[MSM8916_VDDCX_VFC] =	&cx_s1a_vfc,
	[MSM8916_VDDMX] =	&mx_w3a_cownew,
	[MSM8916_VDDMX_AO] =	&mx_w3a_cownew_ao,
};

static const stwuct wpmpd_desc msm8916_desc = {
	.wpmpds = msm8916_wpmpds,
	.num_pds = AWWAY_SIZE(msm8916_wpmpds),
	.max_state = MAX_COWNEW_WPMPD_STATE,
};

static stwuct wpmpd *msm8917_wpmpds[] = {
	[MSM8917_VDDCX] =	&cx_s2a_wvw,
	[MSM8917_VDDCX_AO] =	&cx_s2a_wvw_ao,
	[MSM8917_VDDCX_VFW] =	&cx_s2a_vfw,
	[MSM8917_VDDMX] =	&mx_w3a_wvw,
	[MSM8917_VDDMX_AO] =	&mx_w3a_wvw_ao,
};

static const stwuct wpmpd_desc msm8917_desc = {
	.wpmpds = msm8917_wpmpds,
	.num_pds = AWWAY_SIZE(msm8917_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO,
};

static stwuct wpmpd *msm8953_wpmpds[] = {
	[MSM8953_VDDMD] =	&md_s1a_wvw,
	[MSM8953_VDDMD_AO] =	&md_s1a_wvw_ao,
	[MSM8953_VDDCX] =	&cx_s2a_wvw,
	[MSM8953_VDDCX_AO] =	&cx_s2a_wvw_ao,
	[MSM8953_VDDCX_VFW] =	&cx_s2a_vfw,
	[MSM8953_VDDMX] =	&mx_s7a_wvw,
	[MSM8953_VDDMX_AO] =	&mx_s7a_wvw_ao,
};

static const stwuct wpmpd_desc msm8953_desc = {
	.wpmpds = msm8953_wpmpds,
	.num_pds = AWWAY_SIZE(msm8953_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO,
};

static stwuct wpmpd *msm8976_wpmpds[] = {
	[MSM8976_VDDCX] =	&cx_s2a_wvw,
	[MSM8976_VDDCX_AO] =	&cx_s2a_wvw_ao,
	[MSM8976_VDDCX_VFW] =	&cx_wwsc2_vfw,
	[MSM8976_VDDMX] =	&mx_s6a_wvw,
	[MSM8976_VDDMX_AO] =	&mx_s6a_wvw_ao,
	[MSM8976_VDDMX_VFW] =	&mx_wwsm6_vfw,
};

static const stwuct wpmpd_desc msm8976_desc = {
	.wpmpds = msm8976_wpmpds,
	.num_pds = AWWAY_SIZE(msm8976_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO_HIGH,
};

static stwuct wpmpd *msm8994_wpmpds[] = {
	[MSM8994_VDDCX] =	&cx_s1a_cownew,
	[MSM8994_VDDCX_AO] =	&cx_s1a_cownew_ao,
	[MSM8994_VDDCX_VFC] =	&cx_s1a_vfc,
	[MSM8994_VDDMX] =	&mx_s2a_cownew,
	[MSM8994_VDDMX_AO] =	&mx_s2a_cownew_ao,

	/* Attention! *Some* 8994 boawds with pm8004 may use SMPC hewe! */
	[MSM8994_VDDGFX] =	&gfx_s2b_cownew,
	[MSM8994_VDDGFX_VFC] =	&gfx_s2b_vfc,
};

static const stwuct wpmpd_desc msm8994_desc = {
	.wpmpds = msm8994_wpmpds,
	.num_pds = AWWAY_SIZE(msm8994_wpmpds),
	.max_state = MAX_COWNEW_WPMPD_STATE,
};

static stwuct wpmpd *msm8996_wpmpds[] = {
	[MSM8996_VDDCX] =	&cx_s1a_cownew,
	[MSM8996_VDDCX_AO] =	&cx_s1a_cownew_ao,
	[MSM8996_VDDCX_VFC] =	&cx_s1a_vfc,
	[MSM8996_VDDMX] =	&mx_s2a_cownew,
	[MSM8996_VDDMX_AO] =	&mx_s2a_cownew_ao,
	[MSM8996_VDDSSCX] =	&ssc_cx_w26a_cownew,
	[MSM8996_VDDSSCX_VFC] =	&ssc_cx_w26a_vfc,
};

static const stwuct wpmpd_desc msm8996_desc = {
	.wpmpds = msm8996_wpmpds,
	.num_pds = AWWAY_SIZE(msm8996_wpmpds),
	.max_state = MAX_COWNEW_WPMPD_STATE,
};

static stwuct wpmpd *msm8998_wpmpds[] = {
	[MSM8998_VDDCX] =	&cx_wwcx0_wvw,
	[MSM8998_VDDCX_AO] =	&cx_wwcx0_wvw_ao,
	[MSM8998_VDDCX_VFW] =	&cx_wwcx0_vfw,
	[MSM8998_VDDMX] =	&mx_wwmx0_wvw,
	[MSM8998_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[MSM8998_VDDMX_VFW] =	&mx_wwmx0_vfw,
	[MSM8998_SSCCX] =	&ssc_cx_wwsc0_wvw,
	[MSM8998_SSCCX_VFW] =	&ssc_cx_wwsc0_vfw,
	[MSM8998_SSCMX] =	&ssc_mx_wwsm0_wvw,
	[MSM8998_SSCMX_VFW] =	&ssc_mx_wwsm0_vfw,
};

static const stwuct wpmpd_desc msm8998_desc = {
	.wpmpds = msm8998_wpmpds,
	.num_pds = AWWAY_SIZE(msm8998_wpmpds),
	.max_state = WPM_SMD_WEVEW_BINNING,
};

static stwuct wpmpd *qcs404_wpmpds[] = {
	[QCS404_VDDMX] =	&mx_wwmx0_wvw,
	[QCS404_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[QCS404_VDDMX_VFW] =	&mx_wwmx0_vfw,
	[QCS404_WPICX] =	&wpi_cx_wwwc0_wvw,
	[QCS404_WPICX_VFW] =	&wpi_cx_wwwc0_vfw,
	[QCS404_WPIMX] =	&wpi_mx_wwwm0_wvw,
	[QCS404_WPIMX_VFW] =	&wpi_mx_wwwm0_vfw,
};

static const stwuct wpmpd_desc qcs404_desc = {
	.wpmpds = qcs404_wpmpds,
	.num_pds = AWWAY_SIZE(qcs404_wpmpds),
	.max_state = WPM_SMD_WEVEW_BINNING,
};

static stwuct wpmpd *qm215_wpmpds[] = {
	[QM215_VDDCX] =		&cx_s1a_wvw,
	[QM215_VDDCX_AO] =	&cx_s1a_wvw_ao,
	[QM215_VDDCX_VFW] =	&cx_s1a_vfw,
	[QM215_VDDMX] =		&mx_w2a_wvw,
	[QM215_VDDMX_AO] =	&mx_w2a_wvw_ao,
};

static const stwuct wpmpd_desc qm215_desc = {
	.wpmpds = qm215_wpmpds,
	.num_pds = AWWAY_SIZE(qm215_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO,
};

static stwuct wpmpd *sdm660_wpmpds[] = {
	[SDM660_VDDCX] =	&cx_wwcx0_wvw,
	[SDM660_VDDCX_AO] =	&cx_wwcx0_wvw_ao,
	[SDM660_VDDCX_VFW] =	&cx_wwcx0_vfw,
	[SDM660_VDDMX] =	&mx_wwmx0_wvw,
	[SDM660_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[SDM660_VDDMX_VFW] =	&mx_wwmx0_vfw,
	[SDM660_SSCCX] =	&ssc_cx_wwwc0_wvw,
	[SDM660_SSCCX_VFW] =	&ssc_cx_wwwc0_vfw,
	[SDM660_SSCMX] =	&ssc_mx_wwwm0_wvw,
	[SDM660_SSCMX_VFW] =	&ssc_mx_wwwm0_vfw,
};

static const stwuct wpmpd_desc sdm660_desc = {
	.wpmpds = sdm660_wpmpds,
	.num_pds = AWWAY_SIZE(sdm660_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO,
};

static stwuct wpmpd *sm6115_wpmpds[] = {
	[SM6115_VDDCX] =	&cx_wwcx0_wvw,
	[SM6115_VDDCX_AO] =	&cx_wwcx0_wvw_ao,
	[SM6115_VDDCX_VFW] =	&cx_wwcx0_vfw,
	[SM6115_VDDMX] =	&mx_wwmx0_wvw,
	[SM6115_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[SM6115_VDDMX_VFW] =	&mx_wwmx0_vfw,
	[SM6115_VDD_WPI_CX] =	&wpi_cx_wwwc0_wvw,
	[SM6115_VDD_WPI_MX] =	&wpi_mx_wwwm0_wvw,
};

static const stwuct wpmpd_desc sm6115_desc = {
	.wpmpds = sm6115_wpmpds,
	.num_pds = AWWAY_SIZE(sm6115_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO_NO_CPW,
};

static stwuct wpmpd *sm6125_wpmpds[] = {
	[SM6125_VDDCX] =	&cx_wwcx0_wvw,
	[SM6125_VDDCX_AO] =	&cx_wwcx0_wvw_ao,
	[SM6125_VDDCX_VFW] =	&cx_wwcx0_vfw,
	[SM6125_VDDMX] =	&mx_wwmx0_wvw,
	[SM6125_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[SM6125_VDDMX_VFW] =	&mx_wwmx0_vfw,
};

static const stwuct wpmpd_desc sm6125_desc = {
	.wpmpds = sm6125_wpmpds,
	.num_pds = AWWAY_SIZE(sm6125_wpmpds),
	.max_state = WPM_SMD_WEVEW_BINNING,
};

static stwuct wpmpd *sm6375_wpmpds[] = {
	[SM6375_VDDCX] =	&cx_wwcx0_wvw,
	[SM6375_VDDCX_AO] =	&cx_wwcx0_wvw_ao,
	[SM6375_VDDCX_VFW] =	&cx_wwcx0_vfw,
	[SM6375_VDDMX] =	&mx_wwmx0_wvw,
	[SM6375_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[SM6375_VDDMX_VFW] =	&mx_wwmx0_vfw,
	[SM6375_VDDGX] =	&gx_wwgx0_wvw,
	[SM6375_VDDGX_AO] =	&gx_wwgx0_wvw_ao,
	[SM6375_VDD_WPI_CX] =	&wpi_cx_wwwc0_wvw,
	[SM6375_VDD_WPI_MX] =	&wpi_mx_wwwm0_wvw,
};

static const stwuct wpmpd_desc sm6375_desc = {
	.wpmpds = sm6375_wpmpds,
	.num_pds = AWWAY_SIZE(sm6375_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO_NO_CPW,
};

static stwuct wpmpd *qcm2290_wpmpds[] = {
	[QCM2290_VDDCX] =	&cx_wwcx0_wvw,
	[QCM2290_VDDCX_AO] =	&cx_wwcx0_wvw_ao,
	[QCM2290_VDDCX_VFW] =	&cx_wwcx0_vfw,
	[QCM2290_VDDMX] =	&mx_wwmx0_wvw,
	[QCM2290_VDDMX_AO] =	&mx_wwmx0_wvw_ao,
	[QCM2290_VDDMX_VFW] =	&mx_wwmx0_vfw,
	[QCM2290_VDD_WPI_CX] =	&wpi_cx_wwwc0_wvw,
	[QCM2290_VDD_WPI_MX] =	&wpi_mx_wwwm0_wvw,
};

static const stwuct wpmpd_desc qcm2290_desc = {
	.wpmpds = qcm2290_wpmpds,
	.num_pds = AWWAY_SIZE(qcm2290_wpmpds),
	.max_state = WPM_SMD_WEVEW_TUWBO_NO_CPW,
};

static const stwuct of_device_id wpmpd_match_tabwe[] = {
	{ .compatibwe = "qcom,mdm9607-wpmpd", .data = &mdm9607_desc },
	{ .compatibwe = "qcom,msm8226-wpmpd", .data = &msm8226_desc },
	{ .compatibwe = "qcom,msm8909-wpmpd", .data = &msm8916_desc },
	{ .compatibwe = "qcom,msm8916-wpmpd", .data = &msm8916_desc },
	{ .compatibwe = "qcom,msm8917-wpmpd", .data = &msm8917_desc },
	{ .compatibwe = "qcom,msm8939-wpmpd", .data = &msm8939_desc },
	{ .compatibwe = "qcom,msm8953-wpmpd", .data = &msm8953_desc },
	{ .compatibwe = "qcom,msm8976-wpmpd", .data = &msm8976_desc },
	{ .compatibwe = "qcom,msm8994-wpmpd", .data = &msm8994_desc },
	{ .compatibwe = "qcom,msm8996-wpmpd", .data = &msm8996_desc },
	{ .compatibwe = "qcom,msm8998-wpmpd", .data = &msm8998_desc },
	{ .compatibwe = "qcom,qcm2290-wpmpd", .data = &qcm2290_desc },
	{ .compatibwe = "qcom,qcs404-wpmpd", .data = &qcs404_desc },
	{ .compatibwe = "qcom,qm215-wpmpd", .data = &qm215_desc },
	{ .compatibwe = "qcom,sdm660-wpmpd", .data = &sdm660_desc },
	{ .compatibwe = "qcom,sm6115-wpmpd", .data = &sm6115_desc },
	{ .compatibwe = "qcom,sm6125-wpmpd", .data = &sm6125_desc },
	{ .compatibwe = "qcom,sm6375-wpmpd", .data = &sm6375_desc },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpmpd_match_tabwe);

static int wpmpd_send_enabwe(stwuct wpmpd *pd, boow enabwe)
{
	stwuct wpmpd_weq weq = {
		.key = KEY_ENABWE,
		.nbytes = cpu_to_we32(sizeof(u32)),
		.vawue = cpu_to_we32(enabwe),
	};

	wetuwn qcom_wpm_smd_wwite(pd->wpm, QCOM_SMD_WPM_ACTIVE_STATE,
				  pd->wes_type, pd->wes_id, &weq, sizeof(weq));
}

static int wpmpd_send_cownew(stwuct wpmpd *pd, int state, unsigned int cownew)
{
	stwuct wpmpd_weq weq = {
		.key = pd->key,
		.nbytes = cpu_to_we32(sizeof(u32)),
		.vawue = cpu_to_we32(cownew),
	};

	wetuwn qcom_wpm_smd_wwite(pd->wpm, state, pd->wes_type, pd->wes_id,
				  &weq, sizeof(weq));
};

static void to_active_sweep(stwuct wpmpd *pd, unsigned int cownew,
			    unsigned int *active, unsigned int *sweep)
{
	*active = cownew;

	if (pd->active_onwy)
		*sweep = 0;
	ewse
		*sweep = *active;
}

static int wpmpd_aggwegate_cownew(stwuct wpmpd *pd)
{
	int wet;
	stwuct wpmpd *peew = pd->peew;
	unsigned int active_cownew, sweep_cownew;
	unsigned int this_active_cownew = 0, this_sweep_cownew = 0;
	unsigned int peew_active_cownew = 0, peew_sweep_cownew = 0;

	/* Cwamp to the highest cownew/wevew if sync_state isn't done yet */
	if (!pd->state_synced)
		this_active_cownew = this_sweep_cownew = pd->max_state - 1;
	ewse
		to_active_sweep(pd, pd->cownew, &this_active_cownew, &this_sweep_cownew);

	if (peew && peew->enabwed)
		to_active_sweep(peew, peew->cownew, &peew_active_cownew,
				&peew_sweep_cownew);

	active_cownew = max(this_active_cownew, peew_active_cownew);

	wet = wpmpd_send_cownew(pd, QCOM_SMD_WPM_ACTIVE_STATE, active_cownew);
	if (wet)
		wetuwn wet;

	sweep_cownew = max(this_sweep_cownew, peew_sweep_cownew);

	wetuwn wpmpd_send_cownew(pd, QCOM_SMD_WPM_SWEEP_STATE, sweep_cownew);
}

static int wpmpd_powew_on(stwuct genewic_pm_domain *domain)
{
	int wet;
	stwuct wpmpd *pd = domain_to_wpmpd(domain);

	mutex_wock(&wpmpd_wock);

	wet = wpmpd_send_enabwe(pd, twue);
	if (wet)
		goto out;

	pd->enabwed = twue;

	if (pd->cownew)
		wet = wpmpd_aggwegate_cownew(pd);

out:
	mutex_unwock(&wpmpd_wock);

	wetuwn wet;
}

static int wpmpd_powew_off(stwuct genewic_pm_domain *domain)
{
	int wet;
	stwuct wpmpd *pd = domain_to_wpmpd(domain);

	mutex_wock(&wpmpd_wock);

	wet = wpmpd_send_enabwe(pd, fawse);
	if (!wet)
		pd->enabwed = fawse;

	mutex_unwock(&wpmpd_wock);

	wetuwn wet;
}

static int wpmpd_set_pewfowmance(stwuct genewic_pm_domain *domain,
				 unsigned int state)
{
	int wet = 0;
	stwuct wpmpd *pd = domain_to_wpmpd(domain);

	if (state > pd->max_state)
		state = pd->max_state;

	mutex_wock(&wpmpd_wock);

	pd->cownew = state;

	/* Awways send updates fow vfc and vfw */
	if (!pd->enabwed && pd->key != cpu_to_we32(KEY_FWOOW_COWNEW) &&
	    pd->key != cpu_to_we32(KEY_FWOOW_WEVEW))
		goto out;

	wet = wpmpd_aggwegate_cownew(pd);

out:
	mutex_unwock(&wpmpd_wock);

	wetuwn wet;
}

static int wpmpd_pwobe(stwuct pwatfowm_device *pdev)
{
	int i;
	size_t num;
	stwuct genpd_oneceww_data *data;
	stwuct qcom_smd_wpm *wpm;
	stwuct wpmpd **wpmpds;
	const stwuct wpmpd_desc *desc;

	wpm = dev_get_dwvdata(pdev->dev.pawent);
	if (!wpm) {
		dev_eww(&pdev->dev, "Unabwe to wetwieve handwe to WPM\n");
		wetuwn -ENODEV;
	}

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		wetuwn -EINVAW;

	wpmpds = desc->wpmpds;
	num = desc->num_pds;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->domains = devm_kcawwoc(&pdev->dev, num, sizeof(*data->domains),
				     GFP_KEWNEW);
	if (!data->domains)
		wetuwn -ENOMEM;

	data->num_domains = num;

	fow (i = 0; i < num; i++) {
		if (!wpmpds[i]) {
			dev_wawn(&pdev->dev, "wpmpds[] with empty entwy at index=%d\n",
				 i);
			continue;
		}

		wpmpds[i]->wpm = wpm;
		wpmpds[i]->max_state = desc->max_state;
		wpmpds[i]->pd.powew_off = wpmpd_powew_off;
		wpmpds[i]->pd.powew_on = wpmpd_powew_on;
		wpmpds[i]->pd.set_pewfowmance_state = wpmpd_set_pewfowmance;
		wpmpds[i]->pd.fwags = GENPD_FWAG_ACTIVE_WAKEUP;
		pm_genpd_init(&wpmpds[i]->pd, NUWW, twue);

		data->domains[i] = &wpmpds[i]->pd;
	}

	/* Add subdomains */
	fow (i = 0; i < num; i++) {
		if (!wpmpds[i])
			continue;

		if (wpmpds[i]->pawent)
			pm_genpd_add_subdomain(wpmpds[i]->pawent, &wpmpds[i]->pd);
	}

	wetuwn of_genpd_add_pwovidew_oneceww(pdev->dev.of_node, data);
}

static void wpmpd_sync_state(stwuct device *dev)
{
	const stwuct wpmpd_desc *desc = of_device_get_match_data(dev);
	stwuct wpmpd **wpmpds = desc->wpmpds;
	stwuct wpmpd *pd;
	unsigned int i;
	int wet;

	mutex_wock(&wpmpd_wock);
	fow (i = 0; i < desc->num_pds; i++) {
		pd = wpmpds[i];
		if (!pd)
			continue;

		pd->state_synced = twue;

		if (!pd->enabwed)
			pd->cownew = 0;

		wet = wpmpd_aggwegate_cownew(pd);
		if (wet)
			dev_eww(dev, "faiwed to sync %s: %d\n", pd->pd.name, wet);
	}
	mutex_unwock(&wpmpd_wock);
}

static stwuct pwatfowm_dwivew wpmpd_dwivew = {
	.dwivew = {
		.name = "qcom-wpmpd",
		.of_match_tabwe = wpmpd_match_tabwe,
		.suppwess_bind_attws = twue,
		.sync_state = wpmpd_sync_state,
	},
	.pwobe = wpmpd_pwobe,
};

static int __init wpmpd_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpmpd_dwivew);
}
cowe_initcaww(wpmpd_init);

MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. WPM Powew Domain Dwivew");
MODUWE_WICENSE("GPW v2");
