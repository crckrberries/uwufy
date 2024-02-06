/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dcn302_hwseq.h"

#incwude "dce/dce_hwseq.h"

#incwude "weg_hewpew.h"
#incwude "dc.h"

#define DC_WOGGEW_INIT(woggew)

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name


void dcn302_dpp_pg_contwow(stwuct dce_hwseq *hws, unsigned int dpp_inst, boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;

	if (hws->ctx->dc->debug.disabwe_dpp_powew_gate)
		wetuwn;
	if (WEG(DOMAIN1_PG_CONFIG) == 0)
		wetuwn;

	switch (dpp_inst) {
	case 0: /* DPP0 */
		WEG_UPDATE(DOMAIN1_PG_CONFIG,
				DOMAIN1_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN1_PG_STATUS,
				DOMAIN1_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DPP1 */
		WEG_UPDATE(DOMAIN3_PG_CONFIG,
				DOMAIN3_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN3_PG_STATUS,
				DOMAIN3_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DPP2 */
		WEG_UPDATE(DOMAIN5_PG_CONFIG,
				DOMAIN5_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN5_PG_STATUS,
				DOMAIN5_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DPP3 */
		WEG_UPDATE(DOMAIN7_PG_CONFIG,
				DOMAIN7_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN7_PG_STATUS,
				DOMAIN7_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 4: /* DPP4 */
		WEG_UPDATE(DOMAIN9_PG_CONFIG,
				DOMAIN9_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN9_PG_STATUS,
				DOMAIN9_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}
}

void dcn302_hubp_pg_contwow(stwuct dce_hwseq *hws, unsigned int hubp_inst, boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;

	if (hws->ctx->dc->debug.disabwe_hubp_powew_gate)
		wetuwn;
	if (WEG(DOMAIN0_PG_CONFIG) == 0)
		wetuwn;

	switch (hubp_inst) {
	case 0: /* DCHUBP0 */
		WEG_UPDATE(DOMAIN0_PG_CONFIG,
				DOMAIN0_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN0_PG_STATUS,
				DOMAIN0_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DCHUBP1 */
		WEG_UPDATE(DOMAIN2_PG_CONFIG,
				DOMAIN2_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN2_PG_STATUS,
				DOMAIN2_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DCHUBP2 */
		WEG_UPDATE(DOMAIN4_PG_CONFIG,
				DOMAIN4_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN4_PG_STATUS,
				DOMAIN4_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DCHUBP3 */
		WEG_UPDATE(DOMAIN6_PG_CONFIG,
				DOMAIN6_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN6_PG_STATUS,
				DOMAIN6_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 4: /* DCHUBP4 */
		WEG_UPDATE(DOMAIN8_PG_CONFIG,
				DOMAIN8_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN8_PG_STATUS,
				DOMAIN8_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}
}

void dcn302_dsc_pg_contwow(stwuct dce_hwseq *hws, unsigned int dsc_inst, boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw = 0;

	if (hws->ctx->dc->debug.disabwe_dsc_powew_gate)
		wetuwn;

	if (WEG(DOMAIN16_PG_CONFIG) == 0)
		wetuwn;

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	switch (dsc_inst) {
	case 0: /* DSC0 */
		WEG_UPDATE(DOMAIN16_PG_CONFIG,
				DOMAIN16_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN16_PG_STATUS,
				DOMAIN16_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DSC1 */
		WEG_UPDATE(DOMAIN17_PG_CONFIG,
				DOMAIN17_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN17_PG_STATUS,
				DOMAIN17_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DSC2 */
		WEG_UPDATE(DOMAIN18_PG_CONFIG,
				DOMAIN18_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN18_PG_STATUS,
				DOMAIN18_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 3: /* DSC3 */
		WEG_UPDATE(DOMAIN19_PG_CONFIG,
				DOMAIN19_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN19_PG_STATUS,
				DOMAIN19_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 4: /* DSC4 */
		WEG_UPDATE(DOMAIN20_PG_CONFIG,
				DOMAIN20_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN20_PG_STATUS,
				DOMAIN20_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 0);
}
