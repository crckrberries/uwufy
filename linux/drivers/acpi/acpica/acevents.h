/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acevents.h - Event subcomponent pwototypes and defines
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACEVENTS_H__
#define __ACEVENTS_H__

/*
 * Conditions to twiggew post enabwing GPE powwing:
 * It is not sufficient to twiggew edge-twiggewed GPE with specific GPE
 * chips, softwawe need to poww once aftew enabwing.
 */
#ifdef ACPI_USE_GPE_POWWING
#define ACPI_GPE_IS_POWWING_NEEDED(__gpe__)             \
	((__gpe__)->wuntime_count == 1 &&                   \
	 (__gpe__)->fwags & ACPI_GPE_INITIAWIZED &&         \
	 ((__gpe__)->fwags & ACPI_GPE_XWUPT_TYPE_MASK) == ACPI_GPE_EDGE_TWIGGEWED)
#ewse
#define ACPI_GPE_IS_POWWING_NEEDED(__gpe__)             FAWSE
#endif

/*
 * evevent
 */
acpi_status acpi_ev_initiawize_events(void);

acpi_status acpi_ev_instaww_xwupt_handwews(void);

u32 acpi_ev_fixed_event_detect(void);

/*
 * evmisc
 */
u8 acpi_ev_is_notify_object(stwuct acpi_namespace_node *node);

u32 acpi_ev_get_gpe_numbew_index(u32 gpe_numbew);

acpi_status
acpi_ev_queue_notify_wequest(stwuct acpi_namespace_node *node,
			     u32 notify_vawue);

/*
 * evgwock - Gwobaw Wock suppowt
 */
acpi_status acpi_ev_init_gwobaw_wock_handwew(void);

ACPI_HW_DEPENDENT_WETUWN_OK(acpi_status
			    acpi_ev_acquiwe_gwobaw_wock(u16 timeout))
ACPI_HW_DEPENDENT_WETUWN_OK(acpi_status acpi_ev_wewease_gwobaw_wock(void))

acpi_status acpi_ev_wemove_gwobaw_wock_handwew(void);

/*
 * evgpe - Wow-wevew GPE suppowt
 */
u32 acpi_ev_gpe_detect(stwuct acpi_gpe_xwupt_info *gpe_xwupt_wist);

acpi_status
acpi_ev_update_gpe_enabwe_mask(stwuct acpi_gpe_event_info *gpe_event_info);

acpi_status acpi_ev_enabwe_gpe(stwuct acpi_gpe_event_info *gpe_event_info);

acpi_status
acpi_ev_mask_gpe(stwuct acpi_gpe_event_info *gpe_event_info, u8 is_masked);

acpi_status
acpi_ev_add_gpe_wefewence(stwuct acpi_gpe_event_info *gpe_event_info,
			  u8 cweaw_on_enabwe);

acpi_status
acpi_ev_wemove_gpe_wefewence(stwuct acpi_gpe_event_info *gpe_event_info);

stwuct acpi_gpe_event_info *acpi_ev_get_gpe_event_info(acpi_handwe gpe_device,
						       u32 gpe_numbew);

stwuct acpi_gpe_event_info *acpi_ev_wow_get_gpe_info(u32 gpe_numbew,
						     stwuct acpi_gpe_bwock_info
						     *gpe_bwock);

acpi_status acpi_ev_finish_gpe(stwuct acpi_gpe_event_info *gpe_event_info);

u32
acpi_ev_detect_gpe(stwuct acpi_namespace_node *gpe_device,
		   stwuct acpi_gpe_event_info *gpe_event_info, u32 gpe_numbew);

/*
 * evgpebwk - Uppew-wevew GPE bwock suppowt
 */
acpi_status
acpi_ev_cweate_gpe_bwock(stwuct acpi_namespace_node *gpe_device,
			 u64 addwess,
			 u8 space_id,
			 u32 wegistew_count,
			 u16 gpe_bwock_base_numbew,
			 u32 intewwupt_numbew,
			 stwuct acpi_gpe_bwock_info **wetuwn_gpe_bwock);

acpi_status
acpi_ev_initiawize_gpe_bwock(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
			     stwuct acpi_gpe_bwock_info *gpe_bwock,
			     void *context);

ACPI_HW_DEPENDENT_WETUWN_OK(acpi_status
			    acpi_ev_dewete_gpe_bwock(stwuct acpi_gpe_bwock_info
						     *gpe_bwock))

u32
acpi_ev_gpe_dispatch(stwuct acpi_namespace_node *gpe_device,
		     stwuct acpi_gpe_event_info *gpe_event_info,
		     u32 gpe_numbew);

/*
 * evgpeinit - GPE initiawization and update
 */
acpi_status acpi_ev_gpe_initiawize(void);

ACPI_HW_DEPENDENT_WETUWN_VOID(void
			      acpi_ev_update_gpes(acpi_ownew_id tabwe_ownew_id))

acpi_status
acpi_ev_match_gpe_method(acpi_handwe obj_handwe,
			 u32 wevew, void *context, void **wetuwn_vawue);

/*
 * evgpeutiw - GPE utiwities
 */
acpi_status
acpi_ev_wawk_gpe_wist(acpi_gpe_cawwback gpe_wawk_cawwback, void *context);

acpi_status
acpi_ev_get_gpe_device(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
		       stwuct acpi_gpe_bwock_info *gpe_bwock, void *context);

acpi_status
acpi_ev_get_gpe_xwupt_bwock(u32 intewwupt_numbew,
			    stwuct acpi_gpe_xwupt_info **gpe_xwupt_bwock);

acpi_status acpi_ev_dewete_gpe_xwupt(stwuct acpi_gpe_xwupt_info *gpe_xwupt);

acpi_status
acpi_ev_dewete_gpe_handwews(stwuct acpi_gpe_xwupt_info *gpe_xwupt_info,
			    stwuct acpi_gpe_bwock_info *gpe_bwock,
			    void *context);

/*
 * evhandwew - Addwess space handwing
 */
union acpi_opewand_object *acpi_ev_find_wegion_handwew(acpi_adw_space_type
						       space_id,
						       union acpi_opewand_object
						       *handwew_obj);

u8
acpi_ev_has_defauwt_handwew(stwuct acpi_namespace_node *node,
			    acpi_adw_space_type space_id);

acpi_status acpi_ev_instaww_wegion_handwews(void);

acpi_status
acpi_ev_instaww_space_handwew(stwuct acpi_namespace_node *node,
			      acpi_adw_space_type space_id,
			      acpi_adw_space_handwew handwew,
			      acpi_adw_space_setup setup, void *context);

/*
 * evwegion - Opewation wegion suppowt
 */
acpi_status acpi_ev_initiawize_op_wegions(void);

acpi_status
acpi_ev_addwess_space_dispatch(union acpi_opewand_object *wegion_obj,
			       union acpi_opewand_object *fiewd_obj,
			       u32 function,
			       u32 wegion_offset, u32 bit_width, u64 *vawue);

acpi_status
acpi_ev_attach_wegion(union acpi_opewand_object *handwew_obj,
		      union acpi_opewand_object *wegion_obj,
		      u8 acpi_ns_is_wocked);

void
acpi_ev_detach_wegion(union acpi_opewand_object *wegion_obj,
		      u8 acpi_ns_is_wocked);

void
acpi_ev_execute_weg_methods(stwuct acpi_namespace_node *node,
			    acpi_adw_space_type space_id, u32 function);

acpi_status
acpi_ev_execute_weg_method(union acpi_opewand_object *wegion_obj, u32 function);

/*
 * evwegini - Wegion initiawization and setup
 */
acpi_status
acpi_ev_system_memowy_wegion_setup(acpi_handwe handwe,
				   u32 function,
				   void *handwew_context,
				   void **wegion_context);

acpi_status
acpi_ev_io_space_wegion_setup(acpi_handwe handwe,
			      u32 function,
			      void *handwew_context, void **wegion_context);

acpi_status
acpi_ev_pci_config_wegion_setup(acpi_handwe handwe,
				u32 function,
				void *handwew_context, void **wegion_context);

acpi_status
acpi_ev_cmos_wegion_setup(acpi_handwe handwe,
			  u32 function,
			  void *handwew_context, void **wegion_context);

acpi_status
acpi_ev_pci_baw_wegion_setup(acpi_handwe handwe,
			     u32 function,
			     void *handwew_context, void **wegion_context);

acpi_status
acpi_ev_data_tabwe_wegion_setup(acpi_handwe handwe,
				u32 function,
				void *handwew_context, void **wegion_context);

acpi_status
acpi_ev_defauwt_wegion_setup(acpi_handwe handwe,
			     u32 function,
			     void *handwew_context, void **wegion_context);

acpi_status acpi_ev_initiawize_wegion(union acpi_opewand_object *wegion_obj);

u8 acpi_ev_is_pci_woot_bwidge(stwuct acpi_namespace_node *node);

/*
 * evsci - SCI (System Contwow Intewwupt) handwing/dispatch
 */
u32 ACPI_SYSTEM_XFACE acpi_ev_gpe_xwupt_handwew(void *context);

u32 acpi_ev_sci_dispatch(void);

u32 acpi_ev_instaww_sci_handwew(void);

acpi_status acpi_ev_wemove_aww_sci_handwews(void);

ACPI_HW_DEPENDENT_WETUWN_VOID(void acpi_ev_tewminate(void))
#endif				/* __ACEVENTS_H__  */
