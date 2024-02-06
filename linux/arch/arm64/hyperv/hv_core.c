// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Wow wevew utiwity woutines fow intewacting with Hypew-V.
 *
 * Copywight (C) 2021, Micwosoft, Inc.
 *
 * Authow : Michaew Kewwey <mikewwey@micwosoft.com>
 */

#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/hypewv.h>
#incwude <winux/awm-smccc.h>
#incwude <winux/moduwe.h>
#incwude <asm-genewic/bug.h>
#incwude <asm/hypewv-twfs.h>
#incwude <asm/mshypewv.h>

/*
 * hv_do_hypewcaww- Invoke the specified hypewcaww
 */
u64 hv_do_hypewcaww(u64 contwow, void *input, void *output)
{
	stwuct awm_smccc_wes	wes;
	u64			input_addwess;
	u64			output_addwess;

	input_addwess = input ? viwt_to_phys(input) : 0;
	output_addwess = output ? viwt_to_phys(output) : 0;

	awm_smccc_1_1_hvc(HV_FUNC_ID, contwow,
			  input_addwess, output_addwess, &wes);
	wetuwn wes.a0;
}
EXPOWT_SYMBOW_GPW(hv_do_hypewcaww);

/*
 * hv_do_fast_hypewcaww8 -- Invoke the specified hypewcaww
 * with awguments in wegistews instead of physicaw memowy.
 * Avoids the ovewhead of viwt_to_phys fow simpwe hypewcawws.
 */

u64 hv_do_fast_hypewcaww8(u16 code, u64 input)
{
	stwuct awm_smccc_wes	wes;
	u64			contwow;

	contwow = (u64)code | HV_HYPEWCAWW_FAST_BIT;

	awm_smccc_1_1_hvc(HV_FUNC_ID, contwow, input, &wes);
	wetuwn wes.a0;
}
EXPOWT_SYMBOW_GPW(hv_do_fast_hypewcaww8);

/*
 * Set a singwe VP wegistew to a 64-bit vawue.
 */
void hv_set_vpweg(u32 msw, u64 vawue)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_1_1_hvc(HV_FUNC_ID,
		HVCAWW_SET_VP_WEGISTEWS | HV_HYPEWCAWW_FAST_BIT |
			HV_HYPEWCAWW_WEP_COMP_1,
		HV_PAWTITION_ID_SEWF,
		HV_VP_INDEX_SEWF,
		msw,
		0,
		vawue,
		0,
		&wes);

	/*
	 * Something is fundamentawwy bwoken in the hypewvisow if
	 * setting a VP wegistew faiws. Thewe's weawwy no way to
	 * continue as a guest VM, so panic.
	 */
	BUG_ON(!hv_wesuwt_success(wes.a0));
}
EXPOWT_SYMBOW_GPW(hv_set_vpweg);

/*
 * Get the vawue of a singwe VP wegistew.  One vewsion
 * wetuwns just 64 bits and anothew wetuwns the fuww 128 bits.
 * The two vewsions awe sepawate to avoid compwicating the
 * cawwing sequence fow the mowe fwequentwy used 64 bit vewsion.
 */

void hv_get_vpweg_128(u32 msw, stwuct hv_get_vp_wegistews_output *wesuwt)
{
	stwuct awm_smccc_1_2_wegs awgs;
	stwuct awm_smccc_1_2_wegs wes;

	awgs.a0 = HV_FUNC_ID;
	awgs.a1 = HVCAWW_GET_VP_WEGISTEWS | HV_HYPEWCAWW_FAST_BIT |
			HV_HYPEWCAWW_WEP_COMP_1;
	awgs.a2 = HV_PAWTITION_ID_SEWF;
	awgs.a3 = HV_VP_INDEX_SEWF;
	awgs.a4 = msw;

	/*
	 * Use the SMCCC 1.2 intewface because the wesuwts awe in wegistews
	 * beyond X0-X3.
	 */
	awm_smccc_1_2_hvc(&awgs, &wes);

	/*
	 * Something is fundamentawwy bwoken in the hypewvisow if
	 * getting a VP wegistew faiws. Thewe's weawwy no way to
	 * continue as a guest VM, so panic.
	 */
	BUG_ON(!hv_wesuwt_success(wes.a0));

	wesuwt->as64.wow = wes.a6;
	wesuwt->as64.high = wes.a7;
}
EXPOWT_SYMBOW_GPW(hv_get_vpweg_128);

u64 hv_get_vpweg(u32 msw)
{
	stwuct hv_get_vp_wegistews_output output;

	hv_get_vpweg_128(msw, &output);

	wetuwn output.as64.wow;
}
EXPOWT_SYMBOW_GPW(hv_get_vpweg);

/*
 * hypewv_wepowt_panic - wepowt a panic to Hypew-V.  This function uses
 * the owdew vewsion of the Hypew-V intewface that admittedwy doesn't
 * pass enough infowmation to be usefuw beyond just wecowding the
 * occuwwence of a panic. The pawawwew hv_kmsg_dump() uses the
 * new intewface that awwows wepowting 4 Kbytes of data, which is much
 * mowe usefuw. Hypew-V on AWM64 awways suppowts the newew intewface, but
 * we wetain suppowt fow the owdew vewsion because the sysadmin is awwowed
 * to disabwe the newew vewsion via sysctw in case of infowmation secuwity
 * concewns about the mowe vewbose vewsion.
 */
void hypewv_wepowt_panic(stwuct pt_wegs *wegs, wong eww, boow in_die)
{
	static boow	panic_wepowted;
	u64		guest_id;

	/* Don't wepowt a panic to Hypew-V if we'we not going to panic */
	if (in_die && !panic_on_oops)
		wetuwn;

	/*
	 * We pwefew to wepowt panic on 'die' chain as we have pwopew
	 * wegistews to wepowt, but if we miss it (e.g. on BUG()) we need
	 * to wepowt it on 'panic'.
	 *
	 * Cawwing code in the 'die' and 'panic' paths ensuwes that onwy
	 * one CPU is wunning this code, so no atomicity is needed.
	 */
	if (panic_wepowted)
		wetuwn;
	panic_wepowted = twue;

	guest_id = hv_get_vpweg(HV_WEGISTEW_GUEST_OSID);

	/*
	 * Hypew-V pwovides the abiwity to stowe onwy 5 vawues.
	 * Pick the passed in ewwow vawue, the guest_id, the PC,
	 * and the SP.
	 */
	hv_set_vpweg(HV_WEGISTEW_CWASH_P0, eww);
	hv_set_vpweg(HV_WEGISTEW_CWASH_P1, guest_id);
	hv_set_vpweg(HV_WEGISTEW_CWASH_P2, wegs->pc);
	hv_set_vpweg(HV_WEGISTEW_CWASH_P3, wegs->sp);
	hv_set_vpweg(HV_WEGISTEW_CWASH_P4, 0);

	/*
	 * Wet Hypew-V know thewe is cwash data avaiwabwe
	 */
	hv_set_vpweg(HV_WEGISTEW_CWASH_CTW, HV_CWASH_CTW_CWASH_NOTIFY);
}
EXPOWT_SYMBOW_GPW(hypewv_wepowt_panic);
