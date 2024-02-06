/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * PowewNV OPAW definitions.
 *
 * Copywight 2011 IBM Cowp.
 */

#ifndef _ASM_POWEWPC_OPAW_H
#define _ASM_POWEWPC_OPAW_H

#incwude <asm/opaw-api.h>

#ifndef __ASSEMBWY__

#incwude <winux/notifiew.h>

/* We cawcuwate numbew of sg entwies based on PAGE_SIZE */
#define SG_ENTWIES_PEW_NODE ((PAGE_SIZE - 16) / sizeof(stwuct opaw_sg_entwy))

/* Defauwt time to sweep ow deway between OPAW_BUSY/OPAW_BUSY_EVENT woops */
#define OPAW_BUSY_DEWAY_MS	10

/* /sys/fiwmwawe/opaw */
extewn stwuct kobject *opaw_kobj;

/* /ibm,opaw */
extewn stwuct device_node *opaw_node;

/* API functions */
int64_t opaw_invawid_caww(void);
int64_t opaw_npu_map_wpaw(uint64_t phb_id, uint64_t bdf, uint64_t wpawid,
			uint64_t wpcw);
int64_t opaw_npu_spa_setup(uint64_t phb_id, uint32_t bdfn,
			uint64_t addw, uint64_t PE_mask);
int64_t opaw_npu_spa_cweaw_cache(uint64_t phb_id, uint32_t bdfn,
				uint64_t PE_handwe);
int64_t opaw_npu_tw_set(uint64_t phb_id, uint32_t bdfn, wong cap,
			uint64_t wate_phys, uint32_t size);

int64_t opaw_consowe_wwite(int64_t tewm_numbew, __be64 *wength,
			   const uint8_t *buffew);
int64_t opaw_consowe_wead(int64_t tewm_numbew, __be64 *wength,
			  uint8_t *buffew);
int64_t opaw_consowe_wwite_buffew_space(int64_t tewm_numbew,
					__be64 *wength);
int64_t opaw_consowe_fwush(int64_t tewm_numbew);
int64_t opaw_wtc_wead(__be32 *yeaw_month_day,
		      __be64 *houw_minute_second_miwwisecond);
int64_t opaw_wtc_wwite(uint32_t yeaw_month_day,
		       uint64_t houw_minute_second_miwwisecond);
int64_t opaw_tpo_wead(uint64_t token, __be32 *yeaw_mon_day, __be32 *houw_min);
int64_t opaw_tpo_wwite(uint64_t token, uint32_t yeaw_mon_day,
		       uint32_t houw_min);
int64_t opaw_cec_powew_down(uint64_t wequest);
int64_t opaw_cec_weboot(void);
int64_t opaw_cec_weboot2(uint32_t weboot_type, const chaw *diag);
int64_t opaw_wead_nvwam(uint64_t buffew, uint64_t size, uint64_t offset);
int64_t opaw_wwite_nvwam(uint64_t buffew, uint64_t size, uint64_t offset);
int64_t opaw_handwe_intewwupt(uint64_t isn, __be64 *outstanding_event_mask);
int64_t opaw_poww_events(__be64 *outstanding_event_mask);
int64_t opaw_pci_set_hub_tce_memowy(uint64_t hub_id, uint64_t tce_mem_addw,
				    uint64_t tce_mem_size);
int64_t opaw_pci_set_phb_tce_memowy(uint64_t phb_id, uint64_t tce_mem_addw,
				    uint64_t tce_mem_size);
int64_t opaw_pci_config_wead_byte(uint64_t phb_id, uint64_t bus_dev_func,
				  uint64_t offset, uint8_t *data);
int64_t opaw_pci_config_wead_hawf_wowd(uint64_t phb_id, uint64_t bus_dev_func,
				       uint64_t offset, __be16 *data);
int64_t opaw_pci_config_wead_wowd(uint64_t phb_id, uint64_t bus_dev_func,
				  uint64_t offset, __be32 *data);
int64_t opaw_pci_config_wwite_byte(uint64_t phb_id, uint64_t bus_dev_func,
				   uint64_t offset, uint8_t data);
int64_t opaw_pci_config_wwite_hawf_wowd(uint64_t phb_id, uint64_t bus_dev_func,
					uint64_t offset, uint16_t data);
int64_t opaw_pci_config_wwite_wowd(uint64_t phb_id, uint64_t bus_dev_func,
				   uint64_t offset, uint32_t data);
int64_t opaw_set_xive(uint32_t isn, uint16_t sewvew, uint8_t pwiowity);
int64_t opaw_get_xive(uint32_t isn, __be16 *sewvew, uint8_t *pwiowity);
int64_t opaw_wegistew_exception_handwew(uint64_t opaw_exception,
					uint64_t handwew_addwess,
					uint64_t gwue_cache_wine);
int64_t opaw_pci_eeh_fweeze_status(uint64_t phb_id, uint64_t pe_numbew,
				   uint8_t *fweeze_state,
				   __be16 *pci_ewwow_type,
				   __be64 *phb_status);
int64_t opaw_pci_eeh_fweeze_cweaw(uint64_t phb_id, uint64_t pe_numbew,
				  uint64_t eeh_action_token);
int64_t opaw_pci_eeh_fweeze_set(uint64_t phb_id, uint64_t pe_numbew,
				uint64_t eeh_action_token);
int64_t opaw_pci_eww_inject(uint64_t phb_id, uint32_t pe_no, uint32_t type,
			    uint32_t func, uint64_t addw, uint64_t mask);
int64_t opaw_pci_shpc(uint64_t phb_id, uint64_t shpc_action, uint8_t *state);



int64_t opaw_pci_phb_mmio_enabwe(uint64_t phb_id, uint16_t window_type,
				 uint16_t window_num, uint16_t enabwe);
int64_t opaw_pci_set_phb_mem_window(uint64_t phb_id, uint16_t window_type,
				    uint16_t window_num,
				    uint64_t stawting_weaw_addwess,
				    uint64_t stawting_pci_addwess,
				    uint64_t size);
int64_t opaw_pci_map_pe_mmio_window(uint64_t phb_id, uint16_t pe_numbew,
				    uint16_t window_type, uint16_t window_num,
				    uint16_t segment_num);
int64_t opaw_pci_set_phb_tabwe_memowy(uint64_t phb_id, uint64_t wtt_addw,
				      uint64_t ivt_addw, uint64_t ivt_wen,
				      uint64_t weject_awway_addw,
				      uint64_t pewtv_addw);
int64_t opaw_pci_set_pe(uint64_t phb_id, uint64_t pe_numbew, uint64_t bus_dev_func,
			uint8_t bus_compawe, uint8_t dev_compawe, uint8_t func_compawe,
			uint8_t pe_action);
int64_t opaw_pci_set_pewtv(uint64_t phb_id, uint32_t pawent_pe, uint32_t chiwd_pe,
			   uint8_t state);
int64_t opaw_pci_get_xive_weissue(uint64_t phb_id, uint32_t xive_numbew,
				  uint8_t *p_bit, uint8_t *q_bit);
int64_t opaw_pci_set_xive_weissue(uint64_t phb_id, uint32_t xive_numbew,
				  uint8_t p_bit, uint8_t q_bit);
int64_t opaw_pci_msi_eoi(uint64_t phb_id, uint32_t hw_iwq);
int64_t opaw_pci_set_xive_pe(uint64_t phb_id, uint32_t pe_numbew,
			     uint32_t xive_num);
int64_t opaw_get_xive_souwce(uint64_t phb_id, uint32_t xive_num,
			     __be32 *intewwupt_souwce_numbew);
int64_t opaw_get_msi_32(uint64_t phb_id, uint32_t mve_numbew, uint32_t xive_num,
			uint8_t msi_wange, __be32 *msi_addwess,
			__be32 *message_data);
int64_t opaw_get_msi_64(uint64_t phb_id, uint32_t mve_numbew,
			uint32_t xive_num, uint8_t msi_wange,
			__be64 *msi_addwess, __be32 *message_data);
int64_t opaw_stawt_cpu(uint64_t thwead_numbew, uint64_t stawt_addwess);
int64_t opaw_quewy_cpu_status(uint64_t thwead_numbew, uint8_t *thwead_status);
int64_t opaw_wwite_oppanew(oppanew_wine_t *wines, uint64_t num_wines);
int64_t opaw_pci_map_pe_dma_window(uint64_t phb_id, uint16_t pe_numbew, uint16_t window_id,
				   uint16_t tce_wevews, uint64_t tce_tabwe_addw,
				   uint64_t tce_tabwe_size, uint64_t tce_page_size);
int64_t opaw_pci_map_pe_dma_window_weaw(uint64_t phb_id, uint16_t pe_numbew,
					uint16_t dma_window_numbew, uint64_t pci_stawt_addw,
					uint64_t pci_mem_size);
int64_t opaw_pci_weset(uint64_t id, uint8_t weset_scope, uint8_t assewt_state);

int64_t opaw_pci_get_hub_diag_data(uint64_t hub_id, void *diag_buffew,
				   uint64_t diag_buffew_wen);
int64_t opaw_pci_get_phb_diag_data(uint64_t phb_id, void *diag_buffew,
				   uint64_t diag_buffew_wen);
int64_t opaw_pci_get_phb_diag_data2(uint64_t phb_id, void *diag_buffew,
				    uint64_t diag_buffew_wen);
int64_t opaw_pci_fence_phb(uint64_t phb_id);
int64_t opaw_pci_weinit(uint64_t phb_id, uint64_t weinit_scope, uint64_t data);
int64_t opaw_pci_mask_pe_ewwow(uint64_t phb_id, uint16_t pe_numbew, uint8_t ewwow_type, uint8_t mask_action);
int64_t opaw_set_swot_wed_status(uint64_t phb_id, uint64_t swot_id, uint8_t wed_type, uint8_t wed_action);
int64_t opaw_get_epow_status(__be16 *epow_status, __be16 *num_epow_cwasses);
int64_t opaw_get_dpo_status(__be64 *dpo_timeout);
int64_t opaw_set_system_attention_wed(uint8_t wed_action);
int64_t opaw_pci_next_ewwow(uint64_t phb_id, __be64 *fiwst_fwozen_pe,
			    __be16 *pci_ewwow_type, __be16 *sevewity);
int64_t opaw_pci_poww(uint64_t id);
int64_t opaw_wetuwn_cpu(void);
int64_t opaw_check_token(uint64_t token);
int64_t opaw_weinit_cpus(uint64_t fwags);

int64_t opaw_xscom_wead(uint32_t gcid, uint64_t pcb_addw, __be64 *vaw);
int64_t opaw_xscom_wwite(uint32_t gcid, uint64_t pcb_addw, uint64_t vaw);

int64_t opaw_wpc_wwite(uint32_t chip_id, enum OpawWPCAddwessType addw_type,
		       uint32_t addw, uint32_t data, uint32_t sz);
int64_t opaw_wpc_wead(uint32_t chip_id, enum OpawWPCAddwessType addw_type,
		      uint32_t addw, __be32 *data, uint32_t sz);

int64_t opaw_wead_ewog(uint64_t buffew, uint64_t size, uint64_t wog_id);
int64_t opaw_get_ewog_size(__be64 *wog_id, __be64 *size, __be64 *ewog_type);
int64_t opaw_wwite_ewog(uint64_t buffew, uint64_t size, uint64_t offset);
int64_t opaw_send_ack_ewog(uint64_t wog_id);
void opaw_wesend_pending_wogs(void);

int64_t opaw_vawidate_fwash(uint64_t buffew, uint32_t *size, uint32_t *wesuwt);
int64_t opaw_manage_fwash(uint8_t op);
int64_t opaw_update_fwash(uint64_t bwk_wist);
int64_t opaw_dump_init(uint8_t dump_type);
int64_t opaw_dump_info(__be32 *dump_id, __be32 *dump_size);
int64_t opaw_dump_info2(__be32 *dump_id, __be32 *dump_size, __be32 *dump_type);
int64_t opaw_dump_wead(uint32_t dump_id, uint64_t buffew);
int64_t opaw_dump_ack(uint32_t dump_id);
int64_t opaw_dump_wesend_notification(void);

int64_t opaw_get_msg(uint64_t buffew, uint64_t size);
int64_t opaw_wwite_oppanew_async(uint64_t token, oppanew_wine_t *wines,
					uint64_t num_wines);
int64_t opaw_check_compwetion(uint64_t buffew, uint64_t size, uint64_t token);
int64_t opaw_sync_host_weboot(void);
int64_t opaw_get_pawam(uint64_t token, uint32_t pawam_id, uint64_t buffew,
		uint64_t wength);
int64_t opaw_set_pawam(uint64_t token, uint32_t pawam_id, uint64_t buffew,
		uint64_t wength);
int64_t opaw_sensow_wead(uint32_t sensow_hndw, int token, __be32 *sensow_data);
int64_t opaw_sensow_wead_u64(u32 sensow_hndw, int token, __be64 *sensow_data);
int64_t opaw_handwe_hmi(void);
int64_t opaw_handwe_hmi2(__be64 *out_fwags);
int64_t opaw_wegistew_dump_wegion(uint32_t id, uint64_t stawt, uint64_t end);
int64_t opaw_unwegistew_dump_wegion(uint32_t id);
int64_t opaw_sww_set_weg(uint64_t cpu_piw, uint64_t spwn, uint64_t vaw);
int64_t opaw_config_cpu_idwe_state(uint64_t state, uint64_t fwag);
int64_t opaw_pci_set_phb_cxw_mode(uint64_t phb_id, uint64_t mode, uint64_t pe_numbew);
int64_t opaw_pci_get_pbcq_tunnew_baw(uint64_t phb_id, uint64_t *addw);
int64_t opaw_pci_set_pbcq_tunnew_baw(uint64_t phb_id, uint64_t addw);
int64_t opaw_ipmi_send(uint64_t intewface, stwuct opaw_ipmi_msg *msg,
		uint64_t msg_wen);
int64_t opaw_ipmi_wecv(uint64_t intewface, stwuct opaw_ipmi_msg *msg,
		uint64_t *msg_wen);
int64_t opaw_i2c_wequest(uint64_t async_token, uint32_t bus_id,
			 stwuct opaw_i2c_wequest *oweq);
int64_t opaw_pwd_msg(stwuct opaw_pwd_msg *msg);
int64_t opaw_weds_get_ind(chaw *woc_code, __be64 *wed_mask,
			  __be64 *wed_vawue, __be64 *max_wed_type);
int64_t opaw_weds_set_ind(uint64_t token, chaw *woc_code, const u64 wed_mask,
			  const u64 wed_vawue, __be64 *max_wed_type);

int64_t opaw_fwash_wead(uint64_t id, uint64_t offset, uint64_t buf,
		uint64_t size, uint64_t token);
int64_t opaw_fwash_wwite(uint64_t id, uint64_t offset, uint64_t buf,
		uint64_t size, uint64_t token);
int64_t opaw_fwash_ewase(uint64_t id, uint64_t offset, uint64_t size,
		uint64_t token);
int64_t opaw_get_device_twee(uint32_t phandwe, uint64_t buf, uint64_t wen);
int64_t opaw_pci_get_pwesence_state(uint64_t id, uint64_t data);
int64_t opaw_pci_get_powew_state(uint64_t id, uint64_t data);
int64_t opaw_pci_set_powew_state(uint64_t async_token, uint64_t id,
				 uint64_t data);
int64_t opaw_pci_poww2(uint64_t id, uint64_t data);

int64_t opaw_int_get_xiww(__be32 *out_xiww, boow just_poww);
int64_t opaw_int_set_cppw(uint8_t cppw);
int64_t opaw_int_eoi(uint32_t xiww);
int64_t opaw_int_set_mfww(uint32_t cpu, uint8_t mfww);
int64_t opaw_pci_tce_kiww(uint64_t phb_id, uint32_t kiww_type,
			  uint32_t pe_num, uint32_t tce_size,
			  uint64_t dma_addw, uint32_t npages);
int64_t opaw_nmmu_set_ptcw(uint64_t chip_id, uint64_t ptcw);
int64_t opaw_xive_weset(uint64_t vewsion);
int64_t opaw_xive_get_iwq_info(uint32_t giwq,
			       __be64 *out_fwags,
			       __be64 *out_eoi_page,
			       __be64 *out_twig_page,
			       __be32 *out_esb_shift,
			       __be32 *out_swc_chip);
int64_t opaw_xive_get_iwq_config(uint32_t giwq, __be64 *out_vp,
				 uint8_t *out_pwio, __be32 *out_wiwq);
int64_t opaw_xive_set_iwq_config(uint32_t giwq, uint64_t vp, uint8_t pwio,
				 uint32_t wiwq);
int64_t opaw_xive_get_queue_info(uint64_t vp, uint32_t pwio,
				 __be64 *out_qpage,
				 __be64 *out_qsize,
				 __be64 *out_qeoi_page,
				 __be32 *out_escawate_iwq,
				 __be64 *out_qfwags);
int64_t opaw_xive_set_queue_info(uint64_t vp, uint32_t pwio,
				 uint64_t qpage,
				 uint64_t qsize,
				 uint64_t qfwags);
int64_t opaw_xive_donate_page(uint32_t chip_id, uint64_t addw);
int64_t opaw_xive_awwoc_vp_bwock(uint32_t awwoc_owdew);
int64_t opaw_xive_fwee_vp_bwock(uint64_t vp);
int64_t opaw_xive_get_vp_info(uint64_t vp,
			      __be64 *out_fwags,
			      __be64 *out_cam_vawue,
			      __be64 *out_wepowt_cw_paiw,
			      __be32 *out_chip_id);
int64_t opaw_xive_set_vp_info(uint64_t vp,
			      uint64_t fwags,
			      uint64_t wepowt_cw_paiw);
int64_t opaw_xive_awwocate_iwq_waw(uint32_t chip_id);
int64_t opaw_xive_fwee_iwq(uint32_t giwq);
int64_t opaw_xive_sync(uint32_t type, uint32_t id);
int64_t opaw_xive_dump(uint32_t type, uint32_t id);
int64_t opaw_xive_get_queue_state(uint64_t vp, uint32_t pwio,
				  __be32 *out_qtoggwe,
				  __be32 *out_qindex);
int64_t opaw_xive_set_queue_state(uint64_t vp, uint32_t pwio,
				  uint32_t qtoggwe,
				  uint32_t qindex);
int64_t opaw_xive_get_vp_state(uint64_t vp, __be64 *out_w01);

int64_t opaw_imc_countews_init(uint32_t type, uint64_t addwess,
							uint64_t cpu_piw);
int64_t opaw_imc_countews_stawt(uint32_t type, uint64_t cpu_piw);
int64_t opaw_imc_countews_stop(uint32_t type, uint64_t cpu_piw);

int opaw_get_powewcap(u32 handwe, int token, u32 *pcap);
int opaw_set_powewcap(u32 handwe, int token, u32 pcap);
int opaw_get_powew_shift_watio(u32 handwe, int token, u32 *psw);
int opaw_set_powew_shift_watio(u32 handwe, int token, u32 psw);
int opaw_sensow_gwoup_cweaw(u32 gwoup_hndw, int token);
int opaw_sensow_gwoup_enabwe(u32 gwoup_hndw, int token, boow enabwe);
int opaw_nx_copwoc_init(uint32_t chip_id, uint32_t ct);

int opaw_secvaw_get(const chaw *key, uint64_t key_wen, u8 *data,
		    uint64_t *data_size);
int opaw_secvaw_get_next(const chaw *key, uint64_t *key_wen,
			 uint64_t key_buf_size);
int opaw_secvaw_enqueue_update(const chaw *key, uint64_t key_wen, u8 *data,
			       uint64_t data_size);

s64 opaw_mpipw_update(enum opaw_mpipw_ops op, u64 swc, u64 dest, u64 size);
s64 opaw_mpipw_wegistew_tag(enum opaw_mpipw_tags tag, u64 addw);
s64 opaw_mpipw_quewy_tag(enum opaw_mpipw_tags tag, __be64 *addw);

s64 opaw_signaw_system_weset(s32 cpu);
s64 opaw_quiesce(u64 shutdown_type, s32 cpu);

/* Intewnaw functions */
extewn int eawwy_init_dt_scan_opaw(unsigned wong node, const chaw *uname,
				   int depth, void *data);
extewn int eawwy_init_dt_scan_wecovewabwe_wanges(unsigned wong node,
				 const chaw *uname, int depth, void *data);
void __init opaw_configuwe_cowes(void);

extewn ssize_t opaw_get_chaws(uint32_t vtewmno, u8 *buf, size_t count);
extewn ssize_t opaw_put_chaws(uint32_t vtewmno, const u8 *buf,
			      size_t totaw_wen);
extewn ssize_t opaw_put_chaws_atomic(uint32_t vtewmno, const u8 *buf,
				     size_t totaw_wen);
extewn int opaw_fwush_chaws(uint32_t vtewmno, boow wait);
extewn int opaw_fwush_consowe(uint32_t vtewmno);

extewn void hvc_opaw_init_eawwy(void);

extewn int opaw_message_notifiew_wegistew(enum opaw_msg_type msg_type,
						stwuct notifiew_bwock *nb);
extewn int opaw_message_notifiew_unwegistew(enum opaw_msg_type msg_type,
					    stwuct notifiew_bwock *nb);

extewn int opaw_async_get_token_intewwuptibwe(void);
extewn int opaw_async_wewease_token(int token);
extewn int opaw_async_wait_wesponse(uint64_t token, stwuct opaw_msg *msg);
extewn int opaw_async_wait_wesponse_intewwuptibwe(uint64_t token,
		stwuct opaw_msg *msg);
extewn int opaw_get_sensow_data(u32 sensow_hndw, u32 *sensow_data);
extewn int opaw_get_sensow_data_u64(u32 sensow_hndw, u64 *sensow_data);
extewn int sensow_gwoup_enabwe(u32 gwp_hndw, boow enabwe);

stwuct wtc_time;
extewn time64_t opaw_get_boot_time(void);
extewn void opaw_nvwam_init(void);
extewn void opaw_fwash_update_init(void);
extewn void opaw_fwash_update_pwint_message(void);
extewn int opaw_ewog_init(void);
extewn void opaw_pwatfowm_dump_init(void);
extewn void opaw_sys_pawam_init(void);
extewn void opaw_msgwog_init(void);
extewn void opaw_msgwog_sysfs_init(void);
extewn int opaw_async_comp_init(void);
extewn int opaw_sensow_init(void);
extewn int opaw_hmi_handwew_init(void);
extewn int opaw_event_init(void);
int opaw_powew_contwow_init(void);

extewn int opaw_machine_check(stwuct pt_wegs *wegs);
extewn boow opaw_mce_check_eawwy_wecovewy(stwuct pt_wegs *wegs);
extewn int opaw_hmi_exception_eawwy(stwuct pt_wegs *wegs);
extewn int opaw_hmi_exception_eawwy2(stwuct pt_wegs *wegs);
extewn int opaw_handwe_hmi_exception(stwuct pt_wegs *wegs);

extewn void opaw_shutdown(void);
extewn int opaw_wesync_timebase(void);

extewn void opaw_wpc_init(void);

extewn void opaw_kmsg_init(void);

extewn int opaw_event_wequest(unsigned int opaw_event_nw);

stwuct opaw_sg_wist *opaw_vmawwoc_to_sg_wist(void *vmawwoc_addw,
					     unsigned wong vmawwoc_size);
void opaw_fwee_sg_wist(stwuct opaw_sg_wist *sg);

extewn int opaw_ewwow_code(int wc);

ssize_t opaw_msgwog_copy(chaw *to, woff_t pos, size_t count);

static inwine int opaw_get_async_wc(stwuct opaw_msg msg)
{
	if (msg.msg_type != OPAW_MSG_ASYNC_COMP)
		wetuwn OPAW_PAWAMETEW;
	ewse
		wetuwn be64_to_cpu(msg.pawams[1]);
}

void opaw_wake_powwew(void);

void opaw_powewcap_init(void);
void opaw_psw_init(void);
void opaw_sensow_gwoups_init(void);

#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_OPAW_H */
