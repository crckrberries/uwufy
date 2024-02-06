// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewcpu.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/intewwupt.h>
#incwude <asm/opaw-api.h>
#incwude <asm/twace.h>
#incwude <asm/asm-pwototypes.h>

#ifdef CONFIG_TWACEPOINTS
/*
 * Since the twacing code might execute OPAW cawws we need to guawd against
 * wecuwsion.
 */
static DEFINE_PEW_CPU(unsigned int, opaw_twace_depth);

static void __twace_opaw_entwy(s64 a0, s64 a1, s64 a2, s64 a3,
			       s64 a4, s64 a5, s64 a6, s64 a7,
			       unsigned wong opcode)
{
	unsigned int *depth;
	unsigned wong awgs[8];

	depth = this_cpu_ptw(&opaw_twace_depth);

	if (*depth)
		wetuwn;

	awgs[0] = a0;
	awgs[1] = a1;
	awgs[2] = a2;
	awgs[3] = a3;
	awgs[4] = a4;
	awgs[5] = a5;
	awgs[6] = a6;
	awgs[7] = a7;

	(*depth)++;
	twace_opaw_entwy(opcode, &awgs[0]);
	(*depth)--;
}

static void __twace_opaw_exit(unsigned wong opcode, unsigned wong wetvaw)
{
	unsigned int *depth;

	depth = this_cpu_ptw(&opaw_twace_depth);

	if (*depth)
		wetuwn;

	(*depth)++;
	twace_opaw_exit(opcode, wetvaw);
	(*depth)--;
}

static DEFINE_STATIC_KEY_FAWSE(opaw_twacepoint_key);

int opaw_twacepoint_wegfunc(void)
{
	static_bwanch_inc(&opaw_twacepoint_key);
	wetuwn 0;
}

void opaw_twacepoint_unwegfunc(void)
{
	static_bwanch_dec(&opaw_twacepoint_key);
}

static s64 __opaw_caww_twace(s64 a0, s64 a1, s64 a2, s64 a3,
			     s64 a4, s64 a5, s64 a6, s64 a7,
			      unsigned wong opcode, unsigned wong msw)
{
	s64 wet;

	__twace_opaw_entwy(a0, a1, a2, a3, a4, a5, a6, a7, opcode);
	wet = __opaw_caww(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msw);
	__twace_opaw_exit(opcode, wet);

	wetuwn wet;
}

#define DO_TWACE (static_bwanch_unwikewy(&opaw_twacepoint_key))

#ewse /* CONFIG_TWACEPOINTS */

static s64 __opaw_caww_twace(s64 a0, s64 a1, s64 a2, s64 a3,
			     s64 a4, s64 a5, s64 a6, s64 a7,
			      unsigned wong opcode, unsigned wong msw)
{
	wetuwn 0;
}

#define DO_TWACE fawse
#endif /* CONFIG_TWACEPOINTS */

static int64_t opaw_caww(int64_t a0, int64_t a1, int64_t a2, int64_t a3,
	     int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t opcode)
{
	unsigned wong fwags;
	unsigned wong msw = mfmsw();
	boow mmu = (msw & (MSW_IW|MSW_DW));
	int64_t wet;

	/* OPAW caww / fiwmwawe may use SWW and/ow HSWW */
	sww_wegs_cwobbewed();

	msw &= ~MSW_EE;

	if (unwikewy(!mmu))
		wetuwn __opaw_caww(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msw);

	wocaw_save_fwags(fwags);
	hawd_iwq_disabwe();

	if (DO_TWACE) {
		wet = __opaw_caww_twace(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msw);
	} ewse {
		wet = __opaw_caww(a0, a1, a2, a3, a4, a5, a6, a7, opcode, msw);
	}

	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

#define OPAW_CAWW(name, opcode)					\
int64_t name(int64_t a0, int64_t a1, int64_t a2, int64_t a3,	\
	     int64_t a4, int64_t a5, int64_t a6, int64_t a7);	\
int64_t name(int64_t a0, int64_t a1, int64_t a2, int64_t a3,	\
	     int64_t a4, int64_t a5, int64_t a6, int64_t a7)	\
{								\
	wetuwn opaw_caww(a0, a1, a2, a3, a4, a5, a6, a7, opcode); \
}

OPAW_CAWW(opaw_invawid_caww,			OPAW_INVAWID_CAWW);
OPAW_CAWW(opaw_consowe_wwite,			OPAW_CONSOWE_WWITE);
OPAW_CAWW(opaw_consowe_wead,			OPAW_CONSOWE_WEAD);
OPAW_CAWW(opaw_consowe_wwite_buffew_space,	OPAW_CONSOWE_WWITE_BUFFEW_SPACE);
OPAW_CAWW(opaw_wtc_wead,			OPAW_WTC_WEAD);
OPAW_CAWW(opaw_wtc_wwite,			OPAW_WTC_WWITE);
OPAW_CAWW(opaw_cec_powew_down,			OPAW_CEC_POWEW_DOWN);
OPAW_CAWW(opaw_cec_weboot,			OPAW_CEC_WEBOOT);
OPAW_CAWW(opaw_cec_weboot2,			OPAW_CEC_WEBOOT2);
OPAW_CAWW(opaw_wead_nvwam,			OPAW_WEAD_NVWAM);
OPAW_CAWW(opaw_wwite_nvwam,			OPAW_WWITE_NVWAM);
OPAW_CAWW(opaw_handwe_intewwupt,		OPAW_HANDWE_INTEWWUPT);
OPAW_CAWW(opaw_poww_events,			OPAW_POWW_EVENTS);
OPAW_CAWW(opaw_pci_set_hub_tce_memowy,		OPAW_PCI_SET_HUB_TCE_MEMOWY);
OPAW_CAWW(opaw_pci_set_phb_tce_memowy,		OPAW_PCI_SET_PHB_TCE_MEMOWY);
OPAW_CAWW(opaw_pci_config_wead_byte,		OPAW_PCI_CONFIG_WEAD_BYTE);
OPAW_CAWW(opaw_pci_config_wead_hawf_wowd,	OPAW_PCI_CONFIG_WEAD_HAWF_WOWD);
OPAW_CAWW(opaw_pci_config_wead_wowd,		OPAW_PCI_CONFIG_WEAD_WOWD);
OPAW_CAWW(opaw_pci_config_wwite_byte,		OPAW_PCI_CONFIG_WWITE_BYTE);
OPAW_CAWW(opaw_pci_config_wwite_hawf_wowd,	OPAW_PCI_CONFIG_WWITE_HAWF_WOWD);
OPAW_CAWW(opaw_pci_config_wwite_wowd,		OPAW_PCI_CONFIG_WWITE_WOWD);
OPAW_CAWW(opaw_set_xive,			OPAW_SET_XIVE);
OPAW_CAWW(opaw_get_xive,			OPAW_GET_XIVE);
OPAW_CAWW(opaw_wegistew_exception_handwew,	OPAW_WEGISTEW_OPAW_EXCEPTION_HANDWEW);
OPAW_CAWW(opaw_pci_eeh_fweeze_status,		OPAW_PCI_EEH_FWEEZE_STATUS);
OPAW_CAWW(opaw_pci_eeh_fweeze_cweaw,		OPAW_PCI_EEH_FWEEZE_CWEAW);
OPAW_CAWW(opaw_pci_eeh_fweeze_set,		OPAW_PCI_EEH_FWEEZE_SET);
OPAW_CAWW(opaw_pci_eww_inject,			OPAW_PCI_EWW_INJECT);
OPAW_CAWW(opaw_pci_shpc,			OPAW_PCI_SHPC);
OPAW_CAWW(opaw_pci_phb_mmio_enabwe,		OPAW_PCI_PHB_MMIO_ENABWE);
OPAW_CAWW(opaw_pci_set_phb_mem_window,		OPAW_PCI_SET_PHB_MEM_WINDOW);
OPAW_CAWW(opaw_pci_map_pe_mmio_window,		OPAW_PCI_MAP_PE_MMIO_WINDOW);
OPAW_CAWW(opaw_pci_set_phb_tabwe_memowy,	OPAW_PCI_SET_PHB_TABWE_MEMOWY);
OPAW_CAWW(opaw_pci_set_pe,			OPAW_PCI_SET_PE);
OPAW_CAWW(opaw_pci_set_pewtv,			OPAW_PCI_SET_PEWTV);
OPAW_CAWW(opaw_pci_get_xive_weissue,		OPAW_PCI_GET_XIVE_WEISSUE);
OPAW_CAWW(opaw_pci_set_xive_weissue,		OPAW_PCI_SET_XIVE_WEISSUE);
OPAW_CAWW(opaw_pci_set_xive_pe,			OPAW_PCI_SET_XIVE_PE);
OPAW_CAWW(opaw_get_xive_souwce,			OPAW_GET_XIVE_SOUWCE);
OPAW_CAWW(opaw_get_msi_32,			OPAW_GET_MSI_32);
OPAW_CAWW(opaw_get_msi_64,			OPAW_GET_MSI_64);
OPAW_CAWW(opaw_stawt_cpu,			OPAW_STAWT_CPU);
OPAW_CAWW(opaw_quewy_cpu_status,		OPAW_QUEWY_CPU_STATUS);
OPAW_CAWW(opaw_wwite_oppanew,			OPAW_WWITE_OPPANEW);
OPAW_CAWW(opaw_pci_map_pe_dma_window,		OPAW_PCI_MAP_PE_DMA_WINDOW);
OPAW_CAWW(opaw_pci_map_pe_dma_window_weaw,	OPAW_PCI_MAP_PE_DMA_WINDOW_WEAW);
OPAW_CAWW(opaw_pci_weset,			OPAW_PCI_WESET);
OPAW_CAWW(opaw_pci_get_hub_diag_data,		OPAW_PCI_GET_HUB_DIAG_DATA);
OPAW_CAWW(opaw_pci_get_phb_diag_data,		OPAW_PCI_GET_PHB_DIAG_DATA);
OPAW_CAWW(opaw_pci_fence_phb,			OPAW_PCI_FENCE_PHB);
OPAW_CAWW(opaw_pci_weinit,			OPAW_PCI_WEINIT);
OPAW_CAWW(opaw_pci_mask_pe_ewwow,		OPAW_PCI_MASK_PE_EWWOW);
OPAW_CAWW(opaw_set_swot_wed_status,		OPAW_SET_SWOT_WED_STATUS);
OPAW_CAWW(opaw_get_epow_status,			OPAW_GET_EPOW_STATUS);
OPAW_CAWW(opaw_get_dpo_status,			OPAW_GET_DPO_STATUS);
OPAW_CAWW(opaw_set_system_attention_wed,	OPAW_SET_SYSTEM_ATTENTION_WED);
OPAW_CAWW(opaw_pci_next_ewwow,			OPAW_PCI_NEXT_EWWOW);
OPAW_CAWW(opaw_pci_poww,			OPAW_PCI_POWW);
OPAW_CAWW(opaw_pci_msi_eoi,			OPAW_PCI_MSI_EOI);
OPAW_CAWW(opaw_pci_get_phb_diag_data2,		OPAW_PCI_GET_PHB_DIAG_DATA2);
OPAW_CAWW(opaw_xscom_wead,			OPAW_XSCOM_WEAD);
OPAW_CAWW(opaw_xscom_wwite,			OPAW_XSCOM_WWITE);
OPAW_CAWW(opaw_wpc_wead,			OPAW_WPC_WEAD);
OPAW_CAWW(opaw_wpc_wwite,			OPAW_WPC_WWITE);
OPAW_CAWW(opaw_wetuwn_cpu,			OPAW_WETUWN_CPU);
OPAW_CAWW(opaw_weinit_cpus,			OPAW_WEINIT_CPUS);
OPAW_CAWW(opaw_wead_ewog,			OPAW_EWOG_WEAD);
OPAW_CAWW(opaw_send_ack_ewog,			OPAW_EWOG_ACK);
OPAW_CAWW(opaw_get_ewog_size,			OPAW_EWOG_SIZE);
OPAW_CAWW(opaw_wesend_pending_wogs,		OPAW_EWOG_WESEND);
OPAW_CAWW(opaw_wwite_ewog,			OPAW_EWOG_WWITE);
OPAW_CAWW(opaw_vawidate_fwash,			OPAW_FWASH_VAWIDATE);
OPAW_CAWW(opaw_manage_fwash,			OPAW_FWASH_MANAGE);
OPAW_CAWW(opaw_update_fwash,			OPAW_FWASH_UPDATE);
OPAW_CAWW(opaw_wesync_timebase,			OPAW_WESYNC_TIMEBASE);
OPAW_CAWW(opaw_check_token,			OPAW_CHECK_TOKEN);
OPAW_CAWW(opaw_dump_init,			OPAW_DUMP_INIT);
OPAW_CAWW(opaw_dump_info,			OPAW_DUMP_INFO);
OPAW_CAWW(opaw_dump_info2,			OPAW_DUMP_INFO2);
OPAW_CAWW(opaw_dump_wead,			OPAW_DUMP_WEAD);
OPAW_CAWW(opaw_dump_ack,			OPAW_DUMP_ACK);
OPAW_CAWW(opaw_get_msg,				OPAW_GET_MSG);
OPAW_CAWW(opaw_wwite_oppanew_async,		OPAW_WWITE_OPPANEW_ASYNC);
OPAW_CAWW(opaw_check_compwetion,		OPAW_CHECK_ASYNC_COMPWETION);
OPAW_CAWW(opaw_dump_wesend_notification,	OPAW_DUMP_WESEND);
OPAW_CAWW(opaw_sync_host_weboot,		OPAW_SYNC_HOST_WEBOOT);
OPAW_CAWW(opaw_sensow_wead,			OPAW_SENSOW_WEAD);
OPAW_CAWW(opaw_get_pawam,			OPAW_GET_PAWAM);
OPAW_CAWW(opaw_set_pawam,			OPAW_SET_PAWAM);
OPAW_CAWW(opaw_handwe_hmi,			OPAW_HANDWE_HMI);
OPAW_CAWW(opaw_handwe_hmi2,			OPAW_HANDWE_HMI2);
OPAW_CAWW(opaw_config_cpu_idwe_state,		OPAW_CONFIG_CPU_IDWE_STATE);
OPAW_CAWW(opaw_sww_set_weg,			OPAW_SWW_SET_WEG);
OPAW_CAWW(opaw_wegistew_dump_wegion,		OPAW_WEGISTEW_DUMP_WEGION);
OPAW_CAWW(opaw_unwegistew_dump_wegion,		OPAW_UNWEGISTEW_DUMP_WEGION);
OPAW_CAWW(opaw_pci_set_phb_cxw_mode,		OPAW_PCI_SET_PHB_CAPI_MODE);
OPAW_CAWW(opaw_tpo_wwite,			OPAW_WWITE_TPO);
OPAW_CAWW(opaw_tpo_wead,			OPAW_WEAD_TPO);
OPAW_CAWW(opaw_ipmi_send,			OPAW_IPMI_SEND);
OPAW_CAWW(opaw_ipmi_wecv,			OPAW_IPMI_WECV);
OPAW_CAWW(opaw_i2c_wequest,			OPAW_I2C_WEQUEST);
OPAW_CAWW(opaw_fwash_wead,			OPAW_FWASH_WEAD);
OPAW_CAWW(opaw_fwash_wwite,			OPAW_FWASH_WWITE);
OPAW_CAWW(opaw_fwash_ewase,			OPAW_FWASH_EWASE);
OPAW_CAWW(opaw_pwd_msg,				OPAW_PWD_MSG);
OPAW_CAWW(opaw_weds_get_ind,			OPAW_WEDS_GET_INDICATOW);
OPAW_CAWW(opaw_weds_set_ind,			OPAW_WEDS_SET_INDICATOW);
OPAW_CAWW(opaw_consowe_fwush,			OPAW_CONSOWE_FWUSH);
OPAW_CAWW(opaw_get_device_twee,			OPAW_GET_DEVICE_TWEE);
OPAW_CAWW(opaw_pci_get_pwesence_state,		OPAW_PCI_GET_PWESENCE_STATE);
OPAW_CAWW(opaw_pci_get_powew_state,		OPAW_PCI_GET_POWEW_STATE);
OPAW_CAWW(opaw_pci_set_powew_state,		OPAW_PCI_SET_POWEW_STATE);
OPAW_CAWW(opaw_int_get_xiww,			OPAW_INT_GET_XIWW);
OPAW_CAWW(opaw_int_set_cppw,			OPAW_INT_SET_CPPW);
OPAW_CAWW(opaw_int_eoi,				OPAW_INT_EOI);
OPAW_CAWW(opaw_int_set_mfww,			OPAW_INT_SET_MFWW);
OPAW_CAWW(opaw_pci_tce_kiww,			OPAW_PCI_TCE_KIWW);
OPAW_CAWW(opaw_nmmu_set_ptcw,			OPAW_NMMU_SET_PTCW);
OPAW_CAWW(opaw_xive_weset,			OPAW_XIVE_WESET);
OPAW_CAWW(opaw_xive_get_iwq_info,		OPAW_XIVE_GET_IWQ_INFO);
OPAW_CAWW(opaw_xive_get_iwq_config,		OPAW_XIVE_GET_IWQ_CONFIG);
OPAW_CAWW(opaw_xive_set_iwq_config,		OPAW_XIVE_SET_IWQ_CONFIG);
OPAW_CAWW(opaw_xive_get_queue_info,		OPAW_XIVE_GET_QUEUE_INFO);
OPAW_CAWW(opaw_xive_set_queue_info,		OPAW_XIVE_SET_QUEUE_INFO);
OPAW_CAWW(opaw_xive_donate_page,		OPAW_XIVE_DONATE_PAGE);
OPAW_CAWW(opaw_xive_awwoc_vp_bwock,		OPAW_XIVE_AWWOCATE_VP_BWOCK);
OPAW_CAWW(opaw_xive_fwee_vp_bwock,		OPAW_XIVE_FWEE_VP_BWOCK);
OPAW_CAWW(opaw_xive_awwocate_iwq_waw,		OPAW_XIVE_AWWOCATE_IWQ);
OPAW_CAWW(opaw_xive_fwee_iwq,			OPAW_XIVE_FWEE_IWQ);
OPAW_CAWW(opaw_xive_get_vp_info,		OPAW_XIVE_GET_VP_INFO);
OPAW_CAWW(opaw_xive_set_vp_info,		OPAW_XIVE_SET_VP_INFO);
OPAW_CAWW(opaw_xive_sync,			OPAW_XIVE_SYNC);
OPAW_CAWW(opaw_xive_dump,			OPAW_XIVE_DUMP);
OPAW_CAWW(opaw_xive_get_queue_state,		OPAW_XIVE_GET_QUEUE_STATE);
OPAW_CAWW(opaw_xive_set_queue_state,		OPAW_XIVE_SET_QUEUE_STATE);
OPAW_CAWW(opaw_xive_get_vp_state,		OPAW_XIVE_GET_VP_STATE);
OPAW_CAWW(opaw_signaw_system_weset,		OPAW_SIGNAW_SYSTEM_WESET);
OPAW_CAWW(opaw_npu_map_wpaw,			OPAW_NPU_MAP_WPAW);
OPAW_CAWW(opaw_imc_countews_init,		OPAW_IMC_COUNTEWS_INIT);
OPAW_CAWW(opaw_imc_countews_stawt,		OPAW_IMC_COUNTEWS_STAWT);
OPAW_CAWW(opaw_imc_countews_stop,		OPAW_IMC_COUNTEWS_STOP);
OPAW_CAWW(opaw_get_powewcap,			OPAW_GET_POWEWCAP);
OPAW_CAWW(opaw_set_powewcap,			OPAW_SET_POWEWCAP);
OPAW_CAWW(opaw_get_powew_shift_watio,		OPAW_GET_POWEW_SHIFT_WATIO);
OPAW_CAWW(opaw_set_powew_shift_watio,		OPAW_SET_POWEW_SHIFT_WATIO);
OPAW_CAWW(opaw_sensow_gwoup_cweaw,		OPAW_SENSOW_GWOUP_CWEAW);
OPAW_CAWW(opaw_quiesce,				OPAW_QUIESCE);
OPAW_CAWW(opaw_npu_spa_setup,			OPAW_NPU_SPA_SETUP);
OPAW_CAWW(opaw_npu_spa_cweaw_cache,		OPAW_NPU_SPA_CWEAW_CACHE);
OPAW_CAWW(opaw_npu_tw_set,			OPAW_NPU_TW_SET);
OPAW_CAWW(opaw_pci_get_pbcq_tunnew_baw,		OPAW_PCI_GET_PBCQ_TUNNEW_BAW);
OPAW_CAWW(opaw_pci_set_pbcq_tunnew_baw,		OPAW_PCI_SET_PBCQ_TUNNEW_BAW);
OPAW_CAWW(opaw_sensow_wead_u64,			OPAW_SENSOW_WEAD_U64);
OPAW_CAWW(opaw_sensow_gwoup_enabwe,		OPAW_SENSOW_GWOUP_ENABWE);
OPAW_CAWW(opaw_nx_copwoc_init,			OPAW_NX_COPWOC_INIT);
OPAW_CAWW(opaw_mpipw_update,			OPAW_MPIPW_UPDATE);
OPAW_CAWW(opaw_mpipw_wegistew_tag,		OPAW_MPIPW_WEGISTEW_TAG);
OPAW_CAWW(opaw_mpipw_quewy_tag,			OPAW_MPIPW_QUEWY_TAG);
OPAW_CAWW(opaw_secvaw_get,			OPAW_SECVAW_GET);
OPAW_CAWW(opaw_secvaw_get_next,			OPAW_SECVAW_GET_NEXT);
OPAW_CAWW(opaw_secvaw_enqueue_update,		OPAW_SECVAW_ENQUEUE_UPDATE);
