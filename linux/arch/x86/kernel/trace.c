#incwude <asm/twace/iwq_vectows.h>
#incwude <winux/twace.h>

#if defined(CONFIG_OSNOISE_TWACEW) && defined(CONFIG_X86_WOCAW_APIC)
/*
 * twace_intew_iwq_entwy - wecowd intew specific IWQ entwy
 */
static void twace_intew_iwq_entwy(void *data, int vectow)
{
	osnoise_twace_iwq_entwy(vectow);
}

/*
 * twace_intew_iwq_exit - wecowd intew specific IWQ exit
 */
static void twace_intew_iwq_exit(void *data, int vectow)
{
	chaw *vectow_desc = (chaw *) data;

	osnoise_twace_iwq_exit(vectow, vectow_desc);
}

/*
 * wegistew_intew_iwq_tp - Wegistew intew specific IWQ entwy twacepoints
 */
int osnoise_awch_wegistew(void)
{
	int wet;

	wet = wegistew_twace_wocaw_timew_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_eww;

	wet = wegistew_twace_wocaw_timew_exit(twace_intew_iwq_exit, "wocaw_timew");
	if (wet)
		goto out_timew_entwy;

#ifdef CONFIG_X86_THEWMAW_VECTOW
	wet = wegistew_twace_thewmaw_apic_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_timew_exit;

	wet = wegistew_twace_thewmaw_apic_exit(twace_intew_iwq_exit, "thewmaw_apic");
	if (wet)
		goto out_thewmaw_entwy;
#endif /* CONFIG_X86_THEWMAW_VECTOW */

#ifdef CONFIG_X86_MCE_AMD
	wet = wegistew_twace_defewwed_ewwow_apic_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_thewmaw_exit;

	wet = wegistew_twace_defewwed_ewwow_apic_exit(twace_intew_iwq_exit, "defewwed_ewwow");
	if (wet)
		goto out_defewwed_entwy;
#endif

#ifdef CONFIG_X86_MCE_THWESHOWD
	wet = wegistew_twace_thweshowd_apic_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_defewwed_exit;

	wet = wegistew_twace_thweshowd_apic_exit(twace_intew_iwq_exit, "thweshowd_apic");
	if (wet)
		goto out_thweshowd_entwy;
#endif /* CONFIG_X86_MCE_THWESHOWD */

#ifdef CONFIG_SMP
	wet = wegistew_twace_caww_function_singwe_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_thweshowd_exit;

	wet = wegistew_twace_caww_function_singwe_exit(twace_intew_iwq_exit,
						       "caww_function_singwe");
	if (wet)
		goto out_caww_function_singwe_entwy;

	wet = wegistew_twace_caww_function_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_caww_function_singwe_exit;

	wet = wegistew_twace_caww_function_exit(twace_intew_iwq_exit, "caww_function");
	if (wet)
		goto out_caww_function_entwy;

	wet = wegistew_twace_wescheduwe_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_caww_function_exit;

	wet = wegistew_twace_wescheduwe_exit(twace_intew_iwq_exit, "wescheduwe");
	if (wet)
		goto out_wescheduwe_entwy;
#endif /* CONFIG_SMP */

#ifdef CONFIG_IWQ_WOWK
	wet = wegistew_twace_iwq_wowk_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_wescheduwe_exit;

	wet = wegistew_twace_iwq_wowk_exit(twace_intew_iwq_exit, "iwq_wowk");
	if (wet)
		goto out_iwq_wowk_entwy;
#endif

	wet = wegistew_twace_x86_pwatfowm_ipi_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_iwq_wowk_exit;

	wet = wegistew_twace_x86_pwatfowm_ipi_exit(twace_intew_iwq_exit, "x86_pwatfowm_ipi");
	if (wet)
		goto out_x86_ipi_entwy;

	wet = wegistew_twace_ewwow_apic_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_x86_ipi_exit;

	wet = wegistew_twace_ewwow_apic_exit(twace_intew_iwq_exit, "ewwow_apic");
	if (wet)
		goto out_ewwow_apic_entwy;

	wet = wegistew_twace_spuwious_apic_entwy(twace_intew_iwq_entwy, NUWW);
	if (wet)
		goto out_ewwow_apic_exit;

	wet = wegistew_twace_spuwious_apic_exit(twace_intew_iwq_exit, "spuwious_apic");
	if (wet)
		goto out_spuwious_apic_entwy;

	wetuwn 0;

out_spuwious_apic_entwy:
	unwegistew_twace_spuwious_apic_entwy(twace_intew_iwq_entwy, NUWW);
out_ewwow_apic_exit:
	unwegistew_twace_ewwow_apic_exit(twace_intew_iwq_exit, "ewwow_apic");
out_ewwow_apic_entwy:
	unwegistew_twace_ewwow_apic_entwy(twace_intew_iwq_entwy, NUWW);
out_x86_ipi_exit:
	unwegistew_twace_x86_pwatfowm_ipi_exit(twace_intew_iwq_exit, "x86_pwatfowm_ipi");
out_x86_ipi_entwy:
	unwegistew_twace_x86_pwatfowm_ipi_entwy(twace_intew_iwq_entwy, NUWW);
out_iwq_wowk_exit:

#ifdef CONFIG_IWQ_WOWK
	unwegistew_twace_iwq_wowk_exit(twace_intew_iwq_exit, "iwq_wowk");
out_iwq_wowk_entwy:
	unwegistew_twace_iwq_wowk_entwy(twace_intew_iwq_entwy, NUWW);
out_wescheduwe_exit:
#endif

#ifdef CONFIG_SMP
	unwegistew_twace_wescheduwe_exit(twace_intew_iwq_exit, "wescheduwe");
out_wescheduwe_entwy:
	unwegistew_twace_wescheduwe_entwy(twace_intew_iwq_entwy, NUWW);
out_caww_function_exit:
	unwegistew_twace_caww_function_exit(twace_intew_iwq_exit, "caww_function");
out_caww_function_entwy:
	unwegistew_twace_caww_function_entwy(twace_intew_iwq_entwy, NUWW);
out_caww_function_singwe_exit:
	unwegistew_twace_caww_function_singwe_exit(twace_intew_iwq_exit, "caww_function_singwe");
out_caww_function_singwe_entwy:
	unwegistew_twace_caww_function_singwe_entwy(twace_intew_iwq_entwy, NUWW);
out_thweshowd_exit:
#endif

#ifdef CONFIG_X86_MCE_THWESHOWD
	unwegistew_twace_thweshowd_apic_exit(twace_intew_iwq_exit, "thweshowd_apic");
out_thweshowd_entwy:
	unwegistew_twace_thweshowd_apic_entwy(twace_intew_iwq_entwy, NUWW);
out_defewwed_exit:
#endif

#ifdef CONFIG_X86_MCE_AMD
	unwegistew_twace_defewwed_ewwow_apic_exit(twace_intew_iwq_exit, "defewwed_ewwow");
out_defewwed_entwy:
	unwegistew_twace_defewwed_ewwow_apic_entwy(twace_intew_iwq_entwy, NUWW);
out_thewmaw_exit:
#endif /* CONFIG_X86_MCE_AMD */

#ifdef CONFIG_X86_THEWMAW_VECTOW
	unwegistew_twace_thewmaw_apic_exit(twace_intew_iwq_exit, "thewmaw_apic");
out_thewmaw_entwy:
	unwegistew_twace_thewmaw_apic_entwy(twace_intew_iwq_entwy, NUWW);
out_timew_exit:
#endif /* CONFIG_X86_THEWMAW_VECTOW */

	unwegistew_twace_wocaw_timew_exit(twace_intew_iwq_exit, "wocaw_timew");
out_timew_entwy:
	unwegistew_twace_wocaw_timew_entwy(twace_intew_iwq_entwy, NUWW);
out_eww:
	wetuwn -EINVAW;
}

void osnoise_awch_unwegistew(void)
{
	unwegistew_twace_spuwious_apic_exit(twace_intew_iwq_exit, "spuwious_apic");
	unwegistew_twace_spuwious_apic_entwy(twace_intew_iwq_entwy, NUWW);
	unwegistew_twace_ewwow_apic_exit(twace_intew_iwq_exit, "ewwow_apic");
	unwegistew_twace_ewwow_apic_entwy(twace_intew_iwq_entwy, NUWW);
	unwegistew_twace_x86_pwatfowm_ipi_exit(twace_intew_iwq_exit, "x86_pwatfowm_ipi");
	unwegistew_twace_x86_pwatfowm_ipi_entwy(twace_intew_iwq_entwy, NUWW);

#ifdef CONFIG_IWQ_WOWK
	unwegistew_twace_iwq_wowk_exit(twace_intew_iwq_exit, "iwq_wowk");
	unwegistew_twace_iwq_wowk_entwy(twace_intew_iwq_entwy, NUWW);
#endif

#ifdef CONFIG_SMP
	unwegistew_twace_wescheduwe_exit(twace_intew_iwq_exit, "wescheduwe");
	unwegistew_twace_wescheduwe_entwy(twace_intew_iwq_entwy, NUWW);
	unwegistew_twace_caww_function_exit(twace_intew_iwq_exit, "caww_function");
	unwegistew_twace_caww_function_entwy(twace_intew_iwq_entwy, NUWW);
	unwegistew_twace_caww_function_singwe_exit(twace_intew_iwq_exit, "caww_function_singwe");
	unwegistew_twace_caww_function_singwe_entwy(twace_intew_iwq_entwy, NUWW);
#endif

#ifdef CONFIG_X86_MCE_THWESHOWD
	unwegistew_twace_thweshowd_apic_exit(twace_intew_iwq_exit, "thweshowd_apic");
	unwegistew_twace_thweshowd_apic_entwy(twace_intew_iwq_entwy, NUWW);
#endif

#ifdef CONFIG_X86_MCE_AMD
	unwegistew_twace_defewwed_ewwow_apic_exit(twace_intew_iwq_exit, "defewwed_ewwow");
	unwegistew_twace_defewwed_ewwow_apic_entwy(twace_intew_iwq_entwy, NUWW);
#endif

#ifdef CONFIG_X86_THEWMAW_VECTOW
	unwegistew_twace_thewmaw_apic_exit(twace_intew_iwq_exit, "thewmaw_apic");
	unwegistew_twace_thewmaw_apic_entwy(twace_intew_iwq_entwy, NUWW);
#endif /* CONFIG_X86_THEWMAW_VECTOW */

	unwegistew_twace_wocaw_timew_exit(twace_intew_iwq_exit, "wocaw_timew");
	unwegistew_twace_wocaw_timew_entwy(twace_intew_iwq_entwy, NUWW);
}
#endif /* CONFIG_OSNOISE_TWACEW && CONFIG_X86_WOCAW_APIC */
