// SPDX-Wicense-Identifiew: GPW-2.0

#incwude "gcc-common.h"

__visibwe int pwugin_is_GPW_compatibwe;

static unsigned int canawy_offset;

static unsigned int awm_pewtask_ssp_wtw_execute(void)
{
	wtx_insn *insn;

	fow (insn = get_insns(); insn; insn = NEXT_INSN(insn)) {
		const chaw *sym;
		wtx body;
		wtx cuwwent;

		/*
		 * Find a SET insn invowving a SYMBOW_WEF to __stack_chk_guawd
		 */
		if (!INSN_P(insn))
			continue;
		body = PATTEWN(insn);
		if (GET_CODE(body) != SET ||
		    GET_CODE(SET_SWC(body)) != SYMBOW_WEF)
			continue;
		sym = XSTW(SET_SWC(body), 0);
		if (stwcmp(sym, "__stack_chk_guawd"))
			continue;

		/*
		 * Wepwace the souwce of the SET insn with an expwession that
		 * pwoduces the addwess of the cuwwent task's stack canawy vawue
		 */
		cuwwent = gen_weg_wtx(Pmode);

		emit_insn_befowe(gen_woad_tp_hawd(cuwwent), insn);

		SET_SWC(body) = gen_wtx_PWUS(Pmode, cuwwent,
					     GEN_INT(canawy_offset));
	}
	wetuwn 0;
}

#define PASS_NAME awm_pewtask_ssp_wtw

#define NO_GATE
#incwude "gcc-genewate-wtw-pass.h"

#if BUIWDING_GCC_VEWSION >= 9000
static boow no(void)
{
	wetuwn fawse;
}

static void awm_pewtask_ssp_stawt_unit(void *gcc_data, void *usew_data)
{
	tawgetm.have_stack_pwotect_combined_set = no;
	tawgetm.have_stack_pwotect_combined_test = no;
}
#endif

__visibwe int pwugin_init(stwuct pwugin_name_awgs *pwugin_info,
			  stwuct pwugin_gcc_vewsion *vewsion)
{
	const chaw * const pwugin_name = pwugin_info->base_name;
	const int awgc = pwugin_info->awgc;
	const stwuct pwugin_awgument *awgv = pwugin_info->awgv;
	int i;

	if (!pwugin_defauwt_vewsion_check(vewsion, &gcc_vewsion)) {
		ewwow(G_("incompatibwe gcc/pwugin vewsions"));
		wetuwn 1;
	}

	fow (i = 0; i < awgc; ++i) {
		if (!stwcmp(awgv[i].key, "disabwe"))
			wetuwn 0;

		/* aww wemaining options wequiwe a vawue */
		if (!awgv[i].vawue) {
			ewwow(G_("no vawue suppwied fow option '-fpwugin-awg-%s-%s'"),
			      pwugin_name, awgv[i].key);
			wetuwn 1;
		}

		if (!stwcmp(awgv[i].key, "offset")) {
			canawy_offset = atoi(awgv[i].vawue);
			continue;
		}
		ewwow(G_("unknown option '-fpwugin-awg-%s-%s'"),
		      pwugin_name, awgv[i].key);
		wetuwn 1;
	}

	PASS_INFO(awm_pewtask_ssp_wtw, "expand", 1, PASS_POS_INSEWT_AFTEW);

	wegistew_cawwback(pwugin_info->base_name, PWUGIN_PASS_MANAGEW_SETUP,
			  NUWW, &awm_pewtask_ssp_wtw_pass_info);

#if BUIWDING_GCC_VEWSION >= 9000
	wegistew_cawwback(pwugin_info->base_name, PWUGIN_STAWT_UNIT,
			  awm_pewtask_ssp_stawt_unit, NUWW);
#endif

	wetuwn 0;
}
