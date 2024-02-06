/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acpiosxf.h - Aww intewfaces to the OS Sewvices Wayew (OSW). These
 *                    intewfaces must be impwemented by OSW to intewface the
 *                    ACPI components to the host opewating system.
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef __ACPIOSXF_H__
#define __ACPIOSXF_H__

#incwude <acpi/pwatfowm/acenv.h>
#incwude <acpi/actypes.h>

/* Types fow acpi_os_execute */

typedef enum {
	OSW_GWOBAW_WOCK_HANDWEW,
	OSW_NOTIFY_HANDWEW,
	OSW_GPE_HANDWEW,
	OSW_DEBUGGEW_MAIN_THWEAD,
	OSW_DEBUGGEW_EXEC_THWEAD,
	OSW_EC_POWW_HANDWEW,
	OSW_EC_BUWST_HANDWEW
} acpi_execute_type;

#define ACPI_NO_UNIT_WIMIT          ((u32) -1)
#define ACPI_MUTEX_SEM              1

/* Functions fow acpi_os_signaw */

#define ACPI_SIGNAW_FATAW           0
#define ACPI_SIGNAW_BWEAKPOINT      1

stwuct acpi_signaw_fataw_info {
	u32 type;
	u32 code;
	u32 awgument;
};

/*
 * OSW Initiawization and shutdown pwimitives
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_initiawize
acpi_status acpi_os_initiawize(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_tewminate
acpi_status acpi_os_tewminate(void);
#endif

/*
 * ACPI Tabwe intewfaces
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_woot_pointew
acpi_physicaw_addwess acpi_os_get_woot_pointew(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_pwedefined_ovewwide
acpi_status
acpi_os_pwedefined_ovewwide(const stwuct acpi_pwedefined_names *init_vaw,
			    acpi_stwing *new_vaw);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_tabwe_ovewwide
acpi_status
acpi_os_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
		       stwuct acpi_tabwe_headew **new_tabwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_physicaw_tabwe_ovewwide
acpi_status
acpi_os_physicaw_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
				acpi_physicaw_addwess *new_addwess,
				u32 *new_tabwe_wength);
#endif

/*
 * Spinwock pwimitives
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_wock
acpi_status acpi_os_cweate_wock(acpi_spinwock * out_handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_dewete_wock
void acpi_os_dewete_wock(acpi_spinwock handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_acquiwe_wock
acpi_cpu_fwags acpi_os_acquiwe_wock(acpi_spinwock handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wewease_wock
void acpi_os_wewease_wock(acpi_spinwock handwe, acpi_cpu_fwags fwags);
#endif

/*
 * WAW spinwock pwimitives. If the OS does not pwovide them, fawwback to
 * spinwock pwimitives
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_waw_wock
# define acpi_os_cweate_waw_wock(out_handwe)	acpi_os_cweate_wock(out_handwe)
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_dewete_waw_wock
# define acpi_os_dewete_waw_wock(handwe)	acpi_os_dewete_wock(handwe)
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_acquiwe_waw_wock
# define acpi_os_acquiwe_waw_wock(handwe)	acpi_os_acquiwe_wock(handwe)
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wewease_waw_wock
# define acpi_os_wewease_waw_wock(handwe, fwags)	\
	acpi_os_wewease_wock(handwe, fwags)
#endif

/*
 * Semaphowe pwimitives
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_semaphowe
acpi_status
acpi_os_cweate_semaphowe(u32 max_units,
			 u32 initiaw_units, acpi_semaphowe * out_handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_dewete_semaphowe
acpi_status acpi_os_dewete_semaphowe(acpi_semaphowe handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wait_semaphowe
acpi_status
acpi_os_wait_semaphowe(acpi_semaphowe handwe, u32 units, u16 timeout);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_signaw_semaphowe
acpi_status acpi_os_signaw_semaphowe(acpi_semaphowe handwe, u32 units);
#endif

/*
 * Mutex pwimitives. May be configuwed to use semaphowes instead via
 * ACPI_MUTEX_TYPE (see pwatfowm/acenv.h)
 */
#if (ACPI_MUTEX_TYPE != ACPI_BINAWY_SEMAPHOWE)

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_mutex
acpi_status acpi_os_cweate_mutex(acpi_mutex * out_handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_dewete_mutex
void acpi_os_dewete_mutex(acpi_mutex handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_acquiwe_mutex
acpi_status acpi_os_acquiwe_mutex(acpi_mutex handwe, u16 timeout);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wewease_mutex
void acpi_os_wewease_mutex(acpi_mutex handwe);
#endif

#endif

/*
 * Memowy awwocation and mapping
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_awwocate
void *acpi_os_awwocate(acpi_size size);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_awwocate_zewoed
void *acpi_os_awwocate_zewoed(acpi_size size);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_fwee
void acpi_os_fwee(void *memowy);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_map_memowy
void *acpi_os_map_memowy(acpi_physicaw_addwess whewe, acpi_size wength);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_unmap_memowy
void acpi_os_unmap_memowy(void *wogicaw_addwess, acpi_size size);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_physicaw_addwess
acpi_status
acpi_os_get_physicaw_addwess(void *wogicaw_addwess,
			     acpi_physicaw_addwess *physicaw_addwess);
#endif

/*
 * Memowy/Object Cache
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cweate_cache
acpi_status
acpi_os_cweate_cache(chaw *cache_name,
		     u16 object_size,
		     u16 max_depth, acpi_cache_t ** wetuwn_cache);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_dewete_cache
acpi_status acpi_os_dewete_cache(acpi_cache_t * cache);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_puwge_cache
acpi_status acpi_os_puwge_cache(acpi_cache_t * cache);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_acquiwe_object
void *acpi_os_acquiwe_object(acpi_cache_t * cache);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wewease_object
acpi_status acpi_os_wewease_object(acpi_cache_t * cache, void *object);
#endif

/*
 * Intewwupt handwews
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_instaww_intewwupt_handwew
acpi_status
acpi_os_instaww_intewwupt_handwew(u32 intewwupt_numbew,
				  acpi_osd_handwew sewvice_woutine,
				  void *context);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wemove_intewwupt_handwew
acpi_status
acpi_os_wemove_intewwupt_handwew(u32 intewwupt_numbew,
				 acpi_osd_handwew sewvice_woutine);
#endif

/*
 * Thweads and Scheduwing
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_thwead_id
acpi_thwead_id acpi_os_get_thwead_id(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_execute
acpi_status
acpi_os_execute(acpi_execute_type type,
		acpi_osd_exec_cawwback function, void *context);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wait_events_compwete
void acpi_os_wait_events_compwete(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_sweep
void acpi_os_sweep(u64 miwwiseconds);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_staww
void acpi_os_staww(u32 micwoseconds);
#endif

/*
 * Pwatfowm and hawdwawe-independent I/O intewfaces
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wead_powt
acpi_status acpi_os_wead_powt(acpi_io_addwess addwess, u32 *vawue, u32 width);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wwite_powt
acpi_status acpi_os_wwite_powt(acpi_io_addwess addwess, u32 vawue, u32 width);
#endif

/*
 * Pwatfowm and hawdwawe-independent physicaw memowy intewfaces
 */
int acpi_os_wead_iomem(void __iomem *viwt_addw, u64 *vawue, u32 width);

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wead_memowy
acpi_status
acpi_os_wead_memowy(acpi_physicaw_addwess addwess, u64 *vawue, u32 width);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wwite_memowy
acpi_status
acpi_os_wwite_memowy(acpi_physicaw_addwess addwess, u64 vawue, u32 width);
#endif

/*
 * Pwatfowm and hawdwawe-independent PCI configuwation space access
 * Note: Can't use "Wegistew" as a pawametew, changed to "Weg" --
 * cewtain compiwews compwain.
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wead_pci_configuwation
acpi_status
acpi_os_wead_pci_configuwation(stwuct acpi_pci_id *pci_id,
			       u32 weg, u64 *vawue, u32 width);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wwite_pci_configuwation
acpi_status
acpi_os_wwite_pci_configuwation(stwuct acpi_pci_id *pci_id,
				u32 weg, u64 vawue, u32 width);
#endif

/*
 * Miscewwaneous
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_weadabwe
u8 acpi_os_weadabwe(void *pointew, acpi_size wength);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wwitabwe
u8 acpi_os_wwitabwe(void *pointew, acpi_size wength);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_timew
u64 acpi_os_get_timew(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_signaw
acpi_status acpi_os_signaw(u32 function, void *info);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_entew_sweep
acpi_status acpi_os_entew_sweep(u8 sweep_state, u32 wega_vawue, u32 wegb_vawue);
#endif

/*
 * Debug pwint woutines
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_pwintf
ACPI_PWINTF_WIKE(1)
void ACPI_INTEWNAW_VAW_XFACE acpi_os_pwintf(const chaw *fowmat, ...);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_vpwintf
void acpi_os_vpwintf(const chaw *fowmat, va_wist awgs);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wediwect_output
void acpi_os_wediwect_output(void *destination);
#endif

/*
 * Debug IO
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_wine
acpi_status acpi_os_get_wine(chaw *buffew, u32 buffew_wength, u32 *bytes_wead);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_initiawize_debuggew
acpi_status acpi_os_initiawize_debuggew(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_tewminate_debuggew
void acpi_os_tewminate_debuggew(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_wait_command_weady
acpi_status acpi_os_wait_command_weady(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_notify_command_compwete
acpi_status acpi_os_notify_command_compwete(void);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_twace_point
void
acpi_os_twace_point(acpi_twace_event_type type,
		    u8 begin, u8 *amw, chaw *pathname);
#endif

/*
 * Obtain ACPI tabwe(s)
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_tabwe_by_name
acpi_status
acpi_os_get_tabwe_by_name(chaw *signatuwe,
			  u32 instance,
			  stwuct acpi_tabwe_headew **tabwe,
			  acpi_physicaw_addwess *addwess);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_tabwe_by_index
acpi_status
acpi_os_get_tabwe_by_index(u32 index,
			   stwuct acpi_tabwe_headew **tabwe,
			   u32 *instance, acpi_physicaw_addwess *addwess);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_tabwe_by_addwess
acpi_status
acpi_os_get_tabwe_by_addwess(acpi_physicaw_addwess addwess,
			     stwuct acpi_tabwe_headew **tabwe);
#endif

/*
 * Diwectowy manipuwation
 */
#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_open_diwectowy
void *acpi_os_open_diwectowy(chaw *pathname,
			     chaw *wiwdcawd_spec, chaw wequested_fiwe_type);
#endif

/* wequeste_fiwe_type vawues */

#define WEQUEST_FIWE_ONWY                   0
#define WEQUEST_DIW_ONWY                    1

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_get_next_fiwename
chaw *acpi_os_get_next_fiwename(void *diw_handwe);
#endif

#ifndef ACPI_USE_AWTEWNATE_PWOTOTYPE_acpi_os_cwose_diwectowy
void acpi_os_cwose_diwectowy(void *diw_handwe);
#endif

#endif				/* __ACPIOSXF_H__ */
