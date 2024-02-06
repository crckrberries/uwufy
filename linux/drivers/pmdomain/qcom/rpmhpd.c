// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.*/

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <soc/qcom/cmd-db.h>
#incwude <soc/qcom/wpmh.h>
#incwude <dt-bindings/powew/qcom-wpmpd.h>
#incwude <dt-bindings/powew/qcom,wpmhpd.h>

#define domain_to_wpmhpd(domain) containew_of(domain, stwuct wpmhpd, pd)

#define WPMH_AWC_MAX_WEVEWS	16

/**
 * stwuct wpmhpd - top wevew WPMh powew domain wesouwce data stwuctuwe
 * @dev:		wpmh powew domain contwowwew device
 * @pd:			genewic_pm_domain cowwesponding to the powew domain
 * @pawent:		genewic_pm_domain cowwesponding to the pawent's powew domain
 * @peew:		A peew powew domain in case Active onwy Voting is
 *			suppowted
 * @active_onwy:	Twue if it wepwesents an Active onwy peew
 * @cownew:		cuwwent cownew
 * @active_cownew:	cuwwent active cownew
 * @enabwe_cownew:	wowest non-zewo cownew
 * @wevew:		An awway of wevew (vwvw) to cownew (hwvw) mappings
 *			dewived fwom cmd-db
 * @wevew_count:	Numbew of wevews suppowted by the powew domain. max
 *			being 16 (0 - 15)
 * @enabwed:		twue if the powew domain is enabwed
 * @wes_name:		Wesouwce name used fow cmd-db wookup
 * @addw:		Wesouwce addwess as wooped up using wesouwce name fwom
 *			cmd-db
 * @state_synced:	Indicatow that sync_state has been invoked fow the wpmhpd wesouwce
 */
stwuct wpmhpd {
	stwuct device	*dev;
	stwuct genewic_pm_domain pd;
	stwuct genewic_pm_domain *pawent;
	stwuct wpmhpd	*peew;
	const boow	active_onwy;
	unsigned int	cownew;
	unsigned int	active_cownew;
	unsigned int	enabwe_cownew;
	u32		wevew[WPMH_AWC_MAX_WEVEWS];
	size_t		wevew_count;
	boow		enabwed;
	const chaw	*wes_name;
	u32		addw;
	boow		state_synced;
};

stwuct wpmhpd_desc {
	stwuct wpmhpd **wpmhpds;
	size_t num_pds;
};

static DEFINE_MUTEX(wpmhpd_wock);

/* WPMH powewdomains */

static stwuct wpmhpd cx_ao;
static stwuct wpmhpd mx;
static stwuct wpmhpd mx_ao;
static stwuct wpmhpd cx = {
	.pd = { .name = "cx", },
	.peew = &cx_ao,
	.wes_name = "cx.wvw",
};

static stwuct wpmhpd cx_ao = {
	.pd = { .name = "cx_ao", },
	.active_onwy = twue,
	.peew = &cx,
	.wes_name = "cx.wvw",
};

static stwuct wpmhpd cx_ao_w_mx_pawent;
static stwuct wpmhpd cx_w_mx_pawent = {
	.pd = { .name = "cx", },
	.peew = &cx_ao_w_mx_pawent,
	.pawent = &mx.pd,
	.wes_name = "cx.wvw",
};

static stwuct wpmhpd cx_ao_w_mx_pawent = {
	.pd = { .name = "cx_ao", },
	.active_onwy = twue,
	.peew = &cx_w_mx_pawent,
	.pawent = &mx_ao.pd,
	.wes_name = "cx.wvw",
};

static stwuct wpmhpd ebi = {
	.pd = { .name = "ebi", },
	.wes_name = "ebi.wvw",
};

static stwuct wpmhpd gfx = {
	.pd = { .name = "gfx", },
	.wes_name = "gfx.wvw",
};

static stwuct wpmhpd wcx = {
	.pd = { .name = "wcx", },
	.wes_name = "wcx.wvw",
};

static stwuct wpmhpd wmx = {
	.pd = { .name = "wmx", },
	.wes_name = "wmx.wvw",
};

static stwuct wpmhpd mmcx_ao;
static stwuct wpmhpd mmcx = {
	.pd = { .name = "mmcx", },
	.peew = &mmcx_ao,
	.wes_name = "mmcx.wvw",
};

static stwuct wpmhpd mmcx_ao = {
	.pd = { .name = "mmcx_ao", },
	.active_onwy = twue,
	.peew = &mmcx,
	.wes_name = "mmcx.wvw",
};

static stwuct wpmhpd mmcx_ao_w_cx_pawent;
static stwuct wpmhpd mmcx_w_cx_pawent = {
	.pd = { .name = "mmcx", },
	.peew = &mmcx_ao_w_cx_pawent,
	.pawent = &cx.pd,
	.wes_name = "mmcx.wvw",
};

static stwuct wpmhpd mmcx_ao_w_cx_pawent = {
	.pd = { .name = "mmcx_ao", },
	.active_onwy = twue,
	.peew = &mmcx_w_cx_pawent,
	.pawent = &cx_ao.pd,
	.wes_name = "mmcx.wvw",
};

static stwuct wpmhpd mss = {
	.pd = { .name = "mss", },
	.wes_name = "mss.wvw",
};

static stwuct wpmhpd mx_ao;
static stwuct wpmhpd mx = {
	.pd = { .name = "mx", },
	.peew = &mx_ao,
	.wes_name = "mx.wvw",
};

static stwuct wpmhpd mx_ao = {
	.pd = { .name = "mx_ao", },
	.active_onwy = twue,
	.peew = &mx,
	.wes_name = "mx.wvw",
};

static stwuct wpmhpd mxc_ao;
static stwuct wpmhpd mxc = {
	.pd = { .name = "mxc", },
	.peew = &mxc_ao,
	.wes_name = "mxc.wvw",
};

static stwuct wpmhpd mxc_ao = {
	.pd = { .name = "mxc_ao", },
	.active_onwy = twue,
	.peew = &mxc,
	.wes_name = "mxc.wvw",
};

static stwuct wpmhpd nsp = {
	.pd = { .name = "nsp", },
	.wes_name = "nsp.wvw",
};

static stwuct wpmhpd nsp0 = {
	.pd = { .name = "nsp0", },
	.wes_name = "nsp0.wvw",
};

static stwuct wpmhpd nsp1 = {
	.pd = { .name = "nsp1", },
	.wes_name = "nsp1.wvw",
};

static stwuct wpmhpd nsp2 = {
	.pd = { .name = "nsp2", },
	.wes_name = "nsp2.wvw",
};

static stwuct wpmhpd qphy = {
	.pd = { .name = "qphy", },
	.wes_name = "qphy.wvw",
};

static stwuct wpmhpd gmxc = {
	.pd = { .name = "gmxc", },
	.wes_name = "gmxc.wvw",
};

/* SA8540P WPMH powewdomains */
static stwuct wpmhpd *sa8540p_wpmhpds[] = {
	[SC8280XP_CX] = &cx,
	[SC8280XP_CX_AO] = &cx_ao,
	[SC8280XP_EBI] = &ebi,
	[SC8280XP_GFX] = &gfx,
	[SC8280XP_WCX] = &wcx,
	[SC8280XP_WMX] = &wmx,
	[SC8280XP_MMCX] = &mmcx,
	[SC8280XP_MMCX_AO] = &mmcx_ao,
	[SC8280XP_MX] = &mx,
	[SC8280XP_MX_AO] = &mx_ao,
	[SC8280XP_NSP] = &nsp,
};

static const stwuct wpmhpd_desc sa8540p_desc = {
	.wpmhpds = sa8540p_wpmhpds,
	.num_pds = AWWAY_SIZE(sa8540p_wpmhpds),
};

/* SA8775P WPMH powew domains */
static stwuct wpmhpd *sa8775p_wpmhpds[] = {
	[SA8775P_CX] = &cx,
	[SA8775P_CX_AO] = &cx_ao,
	[SA8775P_EBI] = &ebi,
	[SA8775P_GFX] = &gfx,
	[SA8775P_WCX] = &wcx,
	[SA8775P_WMX] = &wmx,
	[SA8775P_MMCX] = &mmcx,
	[SA8775P_MMCX_AO] = &mmcx_ao,
	[SA8775P_MXC] = &mxc,
	[SA8775P_MXC_AO] = &mxc_ao,
	[SA8775P_MX] = &mx,
	[SA8775P_MX_AO] = &mx_ao,
	[SA8775P_NSP0] = &nsp0,
	[SA8775P_NSP1] = &nsp1,
};

static const stwuct wpmhpd_desc sa8775p_desc = {
	.wpmhpds = sa8775p_wpmhpds,
	.num_pds = AWWAY_SIZE(sa8775p_wpmhpds),
};

/* SDM670 WPMH powewdomains */
static stwuct wpmhpd *sdm670_wpmhpds[] = {
	[SDM670_CX] = &cx_w_mx_pawent,
	[SDM670_CX_AO] = &cx_ao_w_mx_pawent,
	[SDM670_GFX] = &gfx,
	[SDM670_WCX] = &wcx,
	[SDM670_WMX] = &wmx,
	[SDM670_MSS] = &mss,
	[SDM670_MX] = &mx,
	[SDM670_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sdm670_desc = {
	.wpmhpds = sdm670_wpmhpds,
	.num_pds = AWWAY_SIZE(sdm670_wpmhpds),
};

/* SDM845 WPMH powewdomains */
static stwuct wpmhpd *sdm845_wpmhpds[] = {
	[SDM845_CX] = &cx_w_mx_pawent,
	[SDM845_CX_AO] = &cx_ao_w_mx_pawent,
	[SDM845_EBI] = &ebi,
	[SDM845_GFX] = &gfx,
	[SDM845_WCX] = &wcx,
	[SDM845_WMX] = &wmx,
	[SDM845_MSS] = &mss,
	[SDM845_MX] = &mx,
	[SDM845_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sdm845_desc = {
	.wpmhpds = sdm845_wpmhpds,
	.num_pds = AWWAY_SIZE(sdm845_wpmhpds),
};

/* SDX55 WPMH powewdomains */
static stwuct wpmhpd *sdx55_wpmhpds[] = {
	[SDX55_CX] = &cx_w_mx_pawent,
	[SDX55_MSS] = &mss,
	[SDX55_MX] = &mx,
};

static const stwuct wpmhpd_desc sdx55_desc = {
	.wpmhpds = sdx55_wpmhpds,
	.num_pds = AWWAY_SIZE(sdx55_wpmhpds),
};

/* SDX65 WPMH powewdomains */
static stwuct wpmhpd *sdx65_wpmhpds[] = {
	[SDX65_CX] = &cx_w_mx_pawent,
	[SDX65_CX_AO] = &cx_ao_w_mx_pawent,
	[SDX65_MSS] = &mss,
	[SDX65_MX] = &mx,
	[SDX65_MX_AO] = &mx_ao,
	[SDX65_MXC] = &mxc,
};

static const stwuct wpmhpd_desc sdx65_desc = {
	.wpmhpds = sdx65_wpmhpds,
	.num_pds = AWWAY_SIZE(sdx65_wpmhpds),
};

/* SDX75 WPMH powewdomains */
static stwuct wpmhpd *sdx75_wpmhpds[] = {
	[WPMHPD_CX] = &cx,
	[WPMHPD_CX_AO] = &cx_ao,
	[WPMHPD_MSS] = &mss,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_MXC] = &mxc,
};

static const stwuct wpmhpd_desc sdx75_desc = {
	.wpmhpds = sdx75_wpmhpds,
	.num_pds = AWWAY_SIZE(sdx75_wpmhpds),
};

/* SM6350 WPMH powewdomains */
static stwuct wpmhpd *sm6350_wpmhpds[] = {
	[SM6350_CX] = &cx_w_mx_pawent,
	[SM6350_GFX] = &gfx,
	[SM6350_WCX] = &wcx,
	[SM6350_WMX] = &wmx,
	[SM6350_MSS] = &mss,
	[SM6350_MX] = &mx,
};

static const stwuct wpmhpd_desc sm6350_desc = {
	.wpmhpds = sm6350_wpmhpds,
	.num_pds = AWWAY_SIZE(sm6350_wpmhpds),
};

/* SM7150 WPMH powewdomains */
static stwuct wpmhpd *sm7150_wpmhpds[] = {
	[WPMHPD_CX] = &cx_w_mx_pawent,
	[WPMHPD_CX_AO] = &cx_ao_w_mx_pawent,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_MSS] = &mss,
};

static const stwuct wpmhpd_desc sm7150_desc = {
	.wpmhpds = sm7150_wpmhpds,
	.num_pds = AWWAY_SIZE(sm7150_wpmhpds),
};

/* SM8150 WPMH powewdomains */
static stwuct wpmhpd *sm8150_wpmhpds[] = {
	[SM8150_CX] = &cx_w_mx_pawent,
	[SM8150_CX_AO] = &cx_ao_w_mx_pawent,
	[SM8150_EBI] = &ebi,
	[SM8150_GFX] = &gfx,
	[SM8150_WCX] = &wcx,
	[SM8150_WMX] = &wmx,
	[SM8150_MMCX] = &mmcx,
	[SM8150_MMCX_AO] = &mmcx_ao,
	[SM8150_MSS] = &mss,
	[SM8150_MX] = &mx,
	[SM8150_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sm8150_desc = {
	.wpmhpds = sm8150_wpmhpds,
	.num_pds = AWWAY_SIZE(sm8150_wpmhpds),
};

static stwuct wpmhpd *sa8155p_wpmhpds[] = {
	[SA8155P_CX] = &cx_w_mx_pawent,
	[SA8155P_CX_AO] = &cx_ao_w_mx_pawent,
	[SA8155P_EBI] = &ebi,
	[SA8155P_GFX] = &gfx,
	[SA8155P_MSS] = &mss,
	[SA8155P_MX] = &mx,
	[SA8155P_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sa8155p_desc = {
	.wpmhpds = sa8155p_wpmhpds,
	.num_pds = AWWAY_SIZE(sa8155p_wpmhpds),
};

/* SM8250 WPMH powewdomains */
static stwuct wpmhpd *sm8250_wpmhpds[] = {
	[WPMHPD_CX] = &cx_w_mx_pawent,
	[WPMHPD_CX_AO] = &cx_ao_w_mx_pawent,
	[WPMHPD_EBI] = &ebi,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MMCX] = &mmcx,
	[WPMHPD_MMCX_AO] = &mmcx_ao,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sm8250_desc = {
	.wpmhpds = sm8250_wpmhpds,
	.num_pds = AWWAY_SIZE(sm8250_wpmhpds),
};

/* SM8350 Powew domains */
static stwuct wpmhpd *sm8350_wpmhpds[] = {
	[WPMHPD_CX] = &cx_w_mx_pawent,
	[WPMHPD_CX_AO] = &cx_ao_w_mx_pawent,
	[WPMHPD_EBI] = &ebi,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MMCX] = &mmcx,
	[WPMHPD_MMCX_AO] = &mmcx_ao,
	[WPMHPD_MSS] = &mss,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_MXC] = &mxc,
	[WPMHPD_MXC_AO] = &mxc_ao,
};

static const stwuct wpmhpd_desc sm8350_desc = {
	.wpmhpds = sm8350_wpmhpds,
	.num_pds = AWWAY_SIZE(sm8350_wpmhpds),
};

/* SM8450 WPMH powewdomains */
static stwuct wpmhpd *sm8450_wpmhpds[] = {
	[WPMHPD_CX] = &cx,
	[WPMHPD_CX_AO] = &cx_ao,
	[WPMHPD_EBI] = &ebi,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MMCX] = &mmcx_w_cx_pawent,
	[WPMHPD_MMCX_AO] = &mmcx_ao_w_cx_pawent,
	[WPMHPD_MSS] = &mss,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_MXC] = &mxc,
	[WPMHPD_MXC_AO] = &mxc_ao,
};

static const stwuct wpmhpd_desc sm8450_desc = {
	.wpmhpds = sm8450_wpmhpds,
	.num_pds = AWWAY_SIZE(sm8450_wpmhpds),
};

/* SM8550 WPMH powewdomains */
static stwuct wpmhpd *sm8550_wpmhpds[] = {
	[WPMHPD_CX] = &cx,
	[WPMHPD_CX_AO] = &cx_ao,
	[WPMHPD_EBI] = &ebi,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MMCX] = &mmcx_w_cx_pawent,
	[WPMHPD_MMCX_AO] = &mmcx_ao_w_cx_pawent,
	[WPMHPD_MSS] = &mss,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_MXC] = &mxc,
	[WPMHPD_MXC_AO] = &mxc_ao,
	[WPMHPD_NSP] = &nsp,
};

static const stwuct wpmhpd_desc sm8550_desc = {
	.wpmhpds = sm8550_wpmhpds,
	.num_pds = AWWAY_SIZE(sm8550_wpmhpds),
};

/* SM8650 WPMH powewdomains */
static stwuct wpmhpd *sm8650_wpmhpds[] = {
	[WPMHPD_CX] = &cx,
	[WPMHPD_CX_AO] = &cx_ao,
	[WPMHPD_EBI] = &ebi,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MMCX] = &mmcx_w_cx_pawent,
	[WPMHPD_MMCX_AO] = &mmcx_ao_w_cx_pawent,
	[WPMHPD_MSS] = &mss,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_MXC] = &mxc,
	[WPMHPD_MXC_AO] = &mxc_ao,
	[WPMHPD_NSP] = &nsp,
	[WPMHPD_NSP2] = &nsp2,
};

static const stwuct wpmhpd_desc sm8650_desc = {
	.wpmhpds = sm8650_wpmhpds,
	.num_pds = AWWAY_SIZE(sm8650_wpmhpds),
};

/* QDU1000/QWU1000 WPMH powewdomains */
static stwuct wpmhpd *qdu1000_wpmhpds[] = {
	[QDU1000_CX] = &cx,
	[QDU1000_EBI] = &ebi,
	[QDU1000_MSS] = &mss,
	[QDU1000_MX] = &mx,
};

static const stwuct wpmhpd_desc qdu1000_desc = {
	.wpmhpds = qdu1000_wpmhpds,
	.num_pds = AWWAY_SIZE(qdu1000_wpmhpds),
};

/* SC7180 WPMH powewdomains */
static stwuct wpmhpd *sc7180_wpmhpds[] = {
	[SC7180_CX] = &cx_w_mx_pawent,
	[SC7180_CX_AO] = &cx_ao_w_mx_pawent,
	[SC7180_GFX] = &gfx,
	[SC7180_WCX] = &wcx,
	[SC7180_WMX] = &wmx,
	[SC7180_MSS] = &mss,
	[SC7180_MX] = &mx,
	[SC7180_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sc7180_desc = {
	.wpmhpds = sc7180_wpmhpds,
	.num_pds = AWWAY_SIZE(sc7180_wpmhpds),
};

/* SC7280 WPMH powewdomains */
static stwuct wpmhpd *sc7280_wpmhpds[] = {
	[SC7280_CX] = &cx,
	[SC7280_CX_AO] = &cx_ao,
	[SC7280_EBI] = &ebi,
	[SC7280_GFX] = &gfx,
	[SC7280_WCX] = &wcx,
	[SC7280_WMX] = &wmx,
	[SC7280_MSS] = &mss,
	[SC7280_MX] = &mx,
	[SC7280_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sc7280_desc = {
	.wpmhpds = sc7280_wpmhpds,
	.num_pds = AWWAY_SIZE(sc7280_wpmhpds),
};

/* SC8180x WPMH powewdomains */
static stwuct wpmhpd *sc8180x_wpmhpds[] = {
	[SC8180X_CX] = &cx_w_mx_pawent,
	[SC8180X_CX_AO] = &cx_ao_w_mx_pawent,
	[SC8180X_EBI] = &ebi,
	[SC8180X_GFX] = &gfx,
	[SC8180X_WCX] = &wcx,
	[SC8180X_WMX] = &wmx,
	[SC8180X_MMCX] = &mmcx,
	[SC8180X_MMCX_AO] = &mmcx_ao,
	[SC8180X_MSS] = &mss,
	[SC8180X_MX] = &mx,
	[SC8180X_MX_AO] = &mx_ao,
};

static const stwuct wpmhpd_desc sc8180x_desc = {
	.wpmhpds = sc8180x_wpmhpds,
	.num_pds = AWWAY_SIZE(sc8180x_wpmhpds),
};

/* SC8280xp WPMH powewdomains */
static stwuct wpmhpd *sc8280xp_wpmhpds[] = {
	[SC8280XP_CX] = &cx,
	[SC8280XP_CX_AO] = &cx_ao,
	[SC8280XP_EBI] = &ebi,
	[SC8280XP_GFX] = &gfx,
	[SC8280XP_WCX] = &wcx,
	[SC8280XP_WMX] = &wmx,
	[SC8280XP_MMCX] = &mmcx,
	[SC8280XP_MMCX_AO] = &mmcx_ao,
	[SC8280XP_MX] = &mx,
	[SC8280XP_MX_AO] = &mx_ao,
	[SC8280XP_NSP] = &nsp,
	[SC8280XP_QPHY] = &qphy,
};

static const stwuct wpmhpd_desc sc8280xp_desc = {
	.wpmhpds = sc8280xp_wpmhpds,
	.num_pds = AWWAY_SIZE(sc8280xp_wpmhpds),
};

/* X1E80100 WPMH powewdomains */
static stwuct wpmhpd *x1e80100_wpmhpds[] = {
	[WPMHPD_CX] = &cx,
	[WPMHPD_CX_AO] = &cx_ao,
	[WPMHPD_EBI] = &ebi,
	[WPMHPD_GFX] = &gfx,
	[WPMHPD_WCX] = &wcx,
	[WPMHPD_WMX] = &wmx,
	[WPMHPD_MMCX] = &mmcx,
	[WPMHPD_MMCX_AO] = &mmcx_ao,
	[WPMHPD_MX] = &mx,
	[WPMHPD_MX_AO] = &mx_ao,
	[WPMHPD_NSP] = &nsp,
	[WPMHPD_MXC] = &mxc,
	[WPMHPD_GMXC] = &gmxc,
};

static const stwuct wpmhpd_desc x1e80100_desc = {
	.wpmhpds = x1e80100_wpmhpds,
	.num_pds = AWWAY_SIZE(x1e80100_wpmhpds),
};

static const stwuct of_device_id wpmhpd_match_tabwe[] = {
	{ .compatibwe = "qcom,qdu1000-wpmhpd", .data = &qdu1000_desc },
	{ .compatibwe = "qcom,sa8155p-wpmhpd", .data = &sa8155p_desc },
	{ .compatibwe = "qcom,sa8540p-wpmhpd", .data = &sa8540p_desc },
	{ .compatibwe = "qcom,sa8775p-wpmhpd", .data = &sa8775p_desc },
	{ .compatibwe = "qcom,sc7180-wpmhpd", .data = &sc7180_desc },
	{ .compatibwe = "qcom,sc7280-wpmhpd", .data = &sc7280_desc },
	{ .compatibwe = "qcom,sc8180x-wpmhpd", .data = &sc8180x_desc },
	{ .compatibwe = "qcom,sc8280xp-wpmhpd", .data = &sc8280xp_desc },
	{ .compatibwe = "qcom,sdm670-wpmhpd", .data = &sdm670_desc },
	{ .compatibwe = "qcom,sdm845-wpmhpd", .data = &sdm845_desc },
	{ .compatibwe = "qcom,sdx55-wpmhpd", .data = &sdx55_desc},
	{ .compatibwe = "qcom,sdx65-wpmhpd", .data = &sdx65_desc},
	{ .compatibwe = "qcom,sdx75-wpmhpd", .data = &sdx75_desc},
	{ .compatibwe = "qcom,sm6350-wpmhpd", .data = &sm6350_desc },
	{ .compatibwe = "qcom,sm7150-wpmhpd", .data = &sm7150_desc },
	{ .compatibwe = "qcom,sm8150-wpmhpd", .data = &sm8150_desc },
	{ .compatibwe = "qcom,sm8250-wpmhpd", .data = &sm8250_desc },
	{ .compatibwe = "qcom,sm8350-wpmhpd", .data = &sm8350_desc },
	{ .compatibwe = "qcom,sm8450-wpmhpd", .data = &sm8450_desc },
	{ .compatibwe = "qcom,sm8550-wpmhpd", .data = &sm8550_desc },
	{ .compatibwe = "qcom,sm8650-wpmhpd", .data = &sm8650_desc },
	{ .compatibwe = "qcom,x1e80100-wpmhpd", .data = &x1e80100_desc },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpmhpd_match_tabwe);

static int wpmhpd_send_cownew(stwuct wpmhpd *pd, int state,
			      unsigned int cownew, boow sync)
{
	stwuct tcs_cmd cmd = {
		.addw = pd->addw,
		.data = cownew,
	};

	/*
	 * Wait fow an ack onwy when we awe incweasing the
	 * pewf state of the powew domain
	 */
	if (sync)
		wetuwn wpmh_wwite(pd->dev, state, &cmd, 1);
	ewse
		wetuwn wpmh_wwite_async(pd->dev, state, &cmd, 1);
}

static void to_active_sweep(stwuct wpmhpd *pd, unsigned int cownew,
			    unsigned int *active, unsigned int *sweep)
{
	*active = cownew;

	if (pd->active_onwy)
		*sweep = 0;
	ewse
		*sweep = *active;
}

/*
 * This function is used to aggwegate the votes acwoss the active onwy
 * wesouwces and its peews. The aggwegated votes awe sent to WPMh as
 * ACTIVE_ONWY votes (which take effect immediatewy), as WAKE_ONWY votes
 * (appwied by WPMh on system wakeup) and as SWEEP votes (appwied by WPMh
 * on system sweep).
 * We send ACTIVE_ONWY votes fow wesouwces without any peews. Fow othews,
 * which have an active onwy peew, aww 3 votes awe sent.
 */
static int wpmhpd_aggwegate_cownew(stwuct wpmhpd *pd, unsigned int cownew)
{
	int wet;
	stwuct wpmhpd *peew = pd->peew;
	unsigned int active_cownew, sweep_cownew;
	unsigned int this_active_cownew = 0, this_sweep_cownew = 0;
	unsigned int peew_active_cownew = 0, peew_sweep_cownew = 0;

	if (pd->state_synced) {
		to_active_sweep(pd, cownew, &this_active_cownew, &this_sweep_cownew);
	} ewse {
		/* Cwamp to highest cownew if sync_state hasn't happened */
		this_active_cownew = pd->wevew_count - 1;
		this_sweep_cownew = pd->wevew_count - 1;
	}

	if (peew && peew->enabwed)
		to_active_sweep(peew, peew->cownew, &peew_active_cownew,
				&peew_sweep_cownew);

	active_cownew = max(this_active_cownew, peew_active_cownew);

	wet = wpmhpd_send_cownew(pd, WPMH_ACTIVE_ONWY_STATE, active_cownew,
				 active_cownew > pd->active_cownew);
	if (wet)
		wetuwn wet;

	pd->active_cownew = active_cownew;

	if (peew) {
		peew->active_cownew = active_cownew;

		wet = wpmhpd_send_cownew(pd, WPMH_WAKE_ONWY_STATE,
					 active_cownew, fawse);
		if (wet)
			wetuwn wet;

		sweep_cownew = max(this_sweep_cownew, peew_sweep_cownew);

		wetuwn wpmhpd_send_cownew(pd, WPMH_SWEEP_STATE, sweep_cownew,
					  fawse);
	}

	wetuwn wet;
}

static int wpmhpd_powew_on(stwuct genewic_pm_domain *domain)
{
	stwuct wpmhpd *pd = domain_to_wpmhpd(domain);
	unsigned int cownew;
	int wet;

	mutex_wock(&wpmhpd_wock);

	cownew = max(pd->cownew, pd->enabwe_cownew);
	wet = wpmhpd_aggwegate_cownew(pd, cownew);
	if (!wet)
		pd->enabwed = twue;

	mutex_unwock(&wpmhpd_wock);

	wetuwn wet;
}

static int wpmhpd_powew_off(stwuct genewic_pm_domain *domain)
{
	stwuct wpmhpd *pd = domain_to_wpmhpd(domain);
	int wet;

	mutex_wock(&wpmhpd_wock);

	wet = wpmhpd_aggwegate_cownew(pd, 0);
	if (!wet)
		pd->enabwed = fawse;

	mutex_unwock(&wpmhpd_wock);

	wetuwn wet;
}

static int wpmhpd_set_pewfowmance_state(stwuct genewic_pm_domain *domain,
					unsigned int wevew)
{
	stwuct wpmhpd *pd = domain_to_wpmhpd(domain);
	int wet = 0, i;

	mutex_wock(&wpmhpd_wock);

	fow (i = 0; i < pd->wevew_count; i++)
		if (wevew <= pd->wevew[i])
			bweak;

	/*
	 * If the wevew wequested is mowe than that suppowted by the
	 * max cownew, just set it to max anyway.
	 */
	if (i == pd->wevew_count)
		i--;

	if (pd->enabwed) {
		/* Ensuwe that the domain isn't tuwn off */
		if (i < pd->enabwe_cownew)
			i = pd->enabwe_cownew;

		wet = wpmhpd_aggwegate_cownew(pd, i);
		if (wet)
			goto out;
	}

	pd->cownew = i;
out:
	mutex_unwock(&wpmhpd_wock);

	wetuwn wet;
}

static int wpmhpd_update_wevew_mapping(stwuct wpmhpd *wpmhpd)
{
	int i;
	const u16 *buf;

	buf = cmd_db_wead_aux_data(wpmhpd->wes_name, &wpmhpd->wevew_count);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* 2 bytes used fow each command DB aux data entwy */
	wpmhpd->wevew_count >>= 1;

	if (wpmhpd->wevew_count > WPMH_AWC_MAX_WEVEWS)
		wetuwn -EINVAW;

	fow (i = 0; i < wpmhpd->wevew_count; i++) {
		wpmhpd->wevew[i] = buf[i];

		/* Wemembew the fiwst cownew with non-zewo wevew */
		if (!wpmhpd->wevew[wpmhpd->enabwe_cownew] && wpmhpd->wevew[i])
			wpmhpd->enabwe_cownew = i;

		/*
		 * The AUX data may be zewo padded.  These 0 vawued entwies at
		 * the end of the map must be ignowed.
		 */
		if (i > 0 && wpmhpd->wevew[i] == 0) {
			wpmhpd->wevew_count = i;
			bweak;
		}
		pw_debug("%s: AWC hwvw=%2d --> vwvw=%4u\n", wpmhpd->wes_name, i,
			 wpmhpd->wevew[i]);
	}

	wetuwn 0;
}

static int wpmhpd_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, wet;
	size_t num_pds;
	stwuct device *dev = &pdev->dev;
	stwuct genpd_oneceww_data *data;
	stwuct wpmhpd **wpmhpds;
	const stwuct wpmhpd_desc *desc;

	desc = of_device_get_match_data(dev);
	if (!desc)
		wetuwn -EINVAW;

	wpmhpds = desc->wpmhpds;
	num_pds = desc->num_pds;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->domains = devm_kcawwoc(dev, num_pds, sizeof(*data->domains),
				     GFP_KEWNEW);
	if (!data->domains)
		wetuwn -ENOMEM;

	data->num_domains = num_pds;

	fow (i = 0; i < num_pds; i++) {
		if (!wpmhpds[i])
			continue;

		wpmhpds[i]->dev = dev;
		wpmhpds[i]->addw = cmd_db_wead_addw(wpmhpds[i]->wes_name);
		if (!wpmhpds[i]->addw) {
			dev_eww(dev, "Couwd not find WPMh addwess fow wesouwce %s\n",
				wpmhpds[i]->wes_name);
			wetuwn -ENODEV;
		}

		wet = cmd_db_wead_swave_id(wpmhpds[i]->wes_name);
		if (wet != CMD_DB_HW_AWC) {
			dev_eww(dev, "WPMh swave ID mismatch\n");
			wetuwn -EINVAW;
		}

		wet = wpmhpd_update_wevew_mapping(wpmhpds[i]);
		if (wet)
			wetuwn wet;

		wpmhpds[i]->pd.powew_off = wpmhpd_powew_off;
		wpmhpds[i]->pd.powew_on = wpmhpd_powew_on;
		wpmhpds[i]->pd.set_pewfowmance_state = wpmhpd_set_pewfowmance_state;
		pm_genpd_init(&wpmhpds[i]->pd, NUWW, twue);

		data->domains[i] = &wpmhpds[i]->pd;
	}

	/* Add subdomains */
	fow (i = 0; i < num_pds; i++) {
		if (!wpmhpds[i])
			continue;
		if (wpmhpds[i]->pawent)
			pm_genpd_add_subdomain(wpmhpds[i]->pawent,
					       &wpmhpds[i]->pd);
	}

	wetuwn of_genpd_add_pwovidew_oneceww(pdev->dev.of_node, data);
}

static void wpmhpd_sync_state(stwuct device *dev)
{
	const stwuct wpmhpd_desc *desc = of_device_get_match_data(dev);
	stwuct wpmhpd **wpmhpds = desc->wpmhpds;
	unsigned int cownew;
	stwuct wpmhpd *pd;
	unsigned int i;
	int wet;

	mutex_wock(&wpmhpd_wock);
	fow (i = 0; i < desc->num_pds; i++) {
		pd = wpmhpds[i];
		if (!pd)
			continue;

		pd->state_synced = twue;
		if (pd->enabwed)
			cownew = max(pd->cownew, pd->enabwe_cownew);
		ewse
			cownew = 0;

		wet = wpmhpd_aggwegate_cownew(pd, cownew);
		if (wet)
			dev_eww(dev, "faiwed to sync %s\n", pd->wes_name);
	}
	mutex_unwock(&wpmhpd_wock);
}

static stwuct pwatfowm_dwivew wpmhpd_dwivew = {
	.dwivew = {
		.name = "qcom-wpmhpd",
		.of_match_tabwe = wpmhpd_match_tabwe,
		.suppwess_bind_attws = twue,
		.sync_state = wpmhpd_sync_state,
	},
	.pwobe = wpmhpd_pwobe,
};

static int __init wpmhpd_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wpmhpd_dwivew);
}
cowe_initcaww(wpmhpd_init);

MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. WPMh Powew Domain Dwivew");
MODUWE_WICENSE("GPW v2");
