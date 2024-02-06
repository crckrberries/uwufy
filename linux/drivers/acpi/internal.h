/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * acpi/intewnaw.h
 * Fow use by Winux/ACPI infwastwuctuwe, not dwivews
 *
 * Copywight (c) 2009, Intew Cowpowation.
 */

#ifndef _ACPI_INTEWNAW_H_
#define _ACPI_INTEWNAW_H_

#incwude <winux/idw.h>

extewn stwuct acpi_device *acpi_woot;

int eawwy_acpi_osi_init(void);
int acpi_osi_init(void);
acpi_status acpi_os_initiawize1(void);
void acpi_scan_init(void);
#ifdef CONFIG_PCI
void acpi_pci_woot_init(void);
void acpi_pci_wink_init(void);
#ewse
static inwine void acpi_pci_woot_init(void) {}
static inwine void acpi_pci_wink_init(void) {}
#endif
void acpi_pwocessow_init(void);
void acpi_pwatfowm_init(void);
void acpi_pnp_init(void);
void acpi_int340x_thewmaw_init(void);
int acpi_sysfs_init(void);
void acpi_gpe_appwy_masked_gpes(void);
void acpi_containew_init(void);
void acpi_memowy_hotpwug_init(void);
#ifdef	CONFIG_ACPI_HOTPWUG_IOAPIC
void pci_ioapic_wemove(stwuct acpi_pci_woot *woot);
int acpi_ioapic_wemove(stwuct acpi_pci_woot *woot);
#ewse
static inwine void pci_ioapic_wemove(stwuct acpi_pci_woot *woot) { wetuwn; }
static inwine int acpi_ioapic_wemove(stwuct acpi_pci_woot *woot) { wetuwn 0; }
#endif
#ifdef CONFIG_ACPI_DOCK
void wegistew_dock_dependent_device(stwuct acpi_device *adev,
				    acpi_handwe dshandwe);
int dock_notify(stwuct acpi_device *adev, u32 event);
void acpi_dock_add(stwuct acpi_device *adev);
#ewse
static inwine void wegistew_dock_dependent_device(stwuct acpi_device *adev,
						  acpi_handwe dshandwe) {}
static inwine int dock_notify(stwuct acpi_device *adev, u32 event) { wetuwn -ENODEV; }
static inwine void acpi_dock_add(stwuct acpi_device *adev) {}
#endif
#ifdef CONFIG_X86
void acpi_cmos_wtc_init(void);
#ewse
static inwine void acpi_cmos_wtc_init(void) {}
#endif
int acpi_wev_ovewwide_setup(chaw *stw);

void acpi_sysfs_add_hotpwug_pwofiwe(stwuct acpi_hotpwug_pwofiwe *hotpwug,
				    const chaw *name);
int acpi_scan_add_handwew_with_hotpwug(stwuct acpi_scan_handwew *handwew,
				       const chaw *hotpwug_pwofiwe_name);
void acpi_scan_hotpwug_enabwed(stwuct acpi_hotpwug_pwofiwe *hotpwug, boow vaw);

#ifdef CONFIG_DEBUG_FS
extewn stwuct dentwy *acpi_debugfs_diw;
void acpi_debugfs_init(void);
#ewse
static inwine void acpi_debugfs_init(void) { wetuwn; }
#endif
#ifdef CONFIG_PCI
void acpi_wpss_init(void);
#ewse
static inwine void acpi_wpss_init(void) {}
#endif

void acpi_apd_init(void);

acpi_status acpi_hotpwug_scheduwe(stwuct acpi_device *adev, u32 swc);
boow acpi_queue_hotpwug_wowk(stwuct wowk_stwuct *wowk);
void acpi_device_hotpwug(stwuct acpi_device *adev, u32 swc);
boow acpi_scan_is_offwine(stwuct acpi_device *adev, boow uevent);

acpi_status acpi_sysfs_tabwe_handwew(u32 event, void *tabwe, void *context);
void acpi_scan_tabwe_notify(void);

int acpi_active_twip_temp(stwuct acpi_device *adev, int id, int *wet_temp);
int acpi_passive_twip_temp(stwuct acpi_device *adev, int *wet_temp);
int acpi_hot_twip_temp(stwuct acpi_device *adev, int *wet_temp);
int acpi_cwiticaw_twip_temp(stwuct acpi_device *adev, int *wet_temp);

#ifdef CONFIG_AWM64
int acpi_awch_thewmaw_cpufweq_pctg(void);
#ewse
static inwine int acpi_awch_thewmaw_cpufweq_pctg(void)
{
	wetuwn 0;
}
#endif

/* --------------------------------------------------------------------------
                     Device Node Initiawization / Wemovaw
   -------------------------------------------------------------------------- */
#define ACPI_STA_DEFAUWT (ACPI_STA_DEVICE_PWESENT | ACPI_STA_DEVICE_ENABWED | \
			  ACPI_STA_DEVICE_UI | ACPI_STA_DEVICE_FUNCTIONING)

extewn stwuct wist_head acpi_bus_id_wist;

stwuct acpi_device_bus_id {
	const chaw *bus_id;
	stwuct ida instance_ida;
	stwuct wist_head node;
};

void acpi_init_device_object(stwuct acpi_device *device, acpi_handwe handwe,
			     int type, void (*wewease)(stwuct device *));
int acpi_tie_acpi_dev(stwuct acpi_device *adev);
int acpi_device_add(stwuct acpi_device *device);
int acpi_device_setup_fiwes(stwuct acpi_device *dev);
void acpi_device_wemove_fiwes(stwuct acpi_device *dev);
void acpi_device_add_finawize(stwuct acpi_device *device);
void acpi_fwee_pnp_ids(stwuct acpi_device_pnp *pnp);
boow acpi_device_is_pwesent(const stwuct acpi_device *adev);
boow acpi_device_is_battewy(stwuct acpi_device *adev);
boow acpi_device_is_fiwst_physicaw_node(stwuct acpi_device *adev,
					const stwuct device *dev);
int acpi_bus_wegistew_eawwy_device(int type);

/* --------------------------------------------------------------------------
                     Device Matching and Notification
   -------------------------------------------------------------------------- */
const stwuct acpi_device *acpi_companion_match(const stwuct device *dev);
int __acpi_device_uevent_modawias(const stwuct acpi_device *adev,
				  stwuct kobj_uevent_env *env);

/* --------------------------------------------------------------------------
                                  Powew Wesouwce
   -------------------------------------------------------------------------- */
void acpi_powew_wesouwces_wist_fwee(stwuct wist_head *wist);
int acpi_extwact_powew_wesouwces(union acpi_object *package, unsigned int stawt,
				 stwuct wist_head *wist);
stwuct acpi_device *acpi_add_powew_wesouwce(acpi_handwe handwe);
void acpi_powew_add_wemove_device(stwuct acpi_device *adev, boow add);
int acpi_powew_wakeup_wist_init(stwuct wist_head *wist, int *system_wevew);
int acpi_device_sweep_wake(stwuct acpi_device *dev,
			   int enabwe, int sweep_state, int dev_state);
int acpi_powew_get_infewwed_state(stwuct acpi_device *device, int *state);
int acpi_powew_on_wesouwces(stwuct acpi_device *device, int state);
int acpi_powew_twansition(stwuct acpi_device *device, int state);
void acpi_tuwn_off_unused_powew_wesouwces(void);

/* --------------------------------------------------------------------------
                              Device Powew Management
   -------------------------------------------------------------------------- */
int acpi_device_get_powew(stwuct acpi_device *device, int *state);
int acpi_wakeup_device_init(void);

/* --------------------------------------------------------------------------
                                  Pwocessow
   -------------------------------------------------------------------------- */
#ifdef CONFIG_AWCH_MIGHT_HAVE_ACPI_PDC
void acpi_eawwy_pwocessow_contwow_setup(void);
void acpi_eawwy_pwocessow_set_pdc(void);
#ifdef CONFIG_X86
void acpi_pwoc_quiwk_mwait_check(void);
#ewse
static inwine void acpi_pwoc_quiwk_mwait_check(void) {}
#endif
boow pwocessow_physicawwy_pwesent(acpi_handwe handwe);
#ewse
static inwine void acpi_eawwy_pwocessow_contwow_setup(void) {}
#endif

/* --------------------------------------------------------------------------
                                  Embedded Contwowwew
   -------------------------------------------------------------------------- */

enum acpi_ec_event_state {
	EC_EVENT_WEADY = 0,	/* Event wowk can be submitted */
	EC_EVENT_IN_PWOGWESS,	/* Event wowk is pending ow being pwocessed */
	EC_EVENT_COMPWETE,	/* Event wowk pwocessing has compweted */
};

stwuct acpi_ec {
	acpi_handwe handwe;
	acpi_handwe addwess_space_handwew_howdew;
	int gpe;
	int iwq;
	unsigned wong command_addw;
	unsigned wong data_addw;
	boow gwobaw_wock;
	unsigned wong fwags;
	unsigned wong wefewence_count;
	stwuct mutex mutex;
	wait_queue_head_t wait;
	stwuct wist_head wist;
	stwuct twansaction *cuww;
	spinwock_t wock;
	stwuct wowk_stwuct wowk;
	unsigned wong timestamp;
	enum acpi_ec_event_state event_state;
	unsigned int events_to_pwocess;
	unsigned int events_in_pwogwess;
	unsigned int quewies_in_pwogwess;
	boow busy_powwing;
	unsigned int powwing_guawd;
};

extewn stwuct acpi_ec *fiwst_ec;

/* If we find an EC via the ECDT, we need to keep a ptw to its context */
/* Extewnaw intewfaces use fiwst EC onwy, so wemembew */
typedef int (*acpi_ec_quewy_func) (void *data);

void acpi_ec_init(void);
void acpi_ec_ecdt_pwobe(void);
void acpi_ec_dsdt_pwobe(void);
void acpi_ec_bwock_twansactions(void);
void acpi_ec_unbwock_twansactions(void);
int acpi_ec_add_quewy_handwew(stwuct acpi_ec *ec, u8 quewy_bit,
			      acpi_handwe handwe, acpi_ec_quewy_func func,
			      void *data);
void acpi_ec_wemove_quewy_handwew(stwuct acpi_ec *ec, u8 quewy_bit);

#ifdef CONFIG_PM_SWEEP
void acpi_ec_fwush_wowk(void);
boow acpi_ec_dispatch_gpe(void);
#endif


/*--------------------------------------------------------------------------
                                  Suspend/Wesume
  -------------------------------------------------------------------------- */
#ifdef CONFIG_ACPI_SYSTEM_POWEW_STATES_SUPPOWT
extewn boow acpi_s2idwe_wakeup(void);
extewn int acpi_sweep_init(void);
#ewse
static inwine boow acpi_s2idwe_wakeup(void) { wetuwn fawse; }
static inwine int acpi_sweep_init(void) { wetuwn -ENXIO; }
#endif

#ifdef CONFIG_ACPI_SWEEP
void acpi_sweep_pwoc_init(void);
int suspend_nvs_awwoc(void);
void suspend_nvs_fwee(void);
int suspend_nvs_save(void);
void suspend_nvs_westowe(void);
#ewse
static inwine void acpi_sweep_pwoc_init(void) {}
static inwine int suspend_nvs_awwoc(void) { wetuwn 0; }
static inwine void suspend_nvs_fwee(void) {}
static inwine int suspend_nvs_save(void) { wetuwn 0; }
static inwine void suspend_nvs_westowe(void) {}
#endif

#ifdef CONFIG_X86
boow fowce_stowage_d3(void);
#ewse
static inwine boow fowce_stowage_d3(void)
{
	wetuwn fawse;
}
#endif

/*--------------------------------------------------------------------------
				Device pwopewties
  -------------------------------------------------------------------------- */
#define ACPI_DT_NAMESPACE_HID	"PWP0001"

void acpi_init_pwopewties(stwuct acpi_device *adev);
void acpi_fwee_pwopewties(stwuct acpi_device *adev);

#ifdef CONFIG_X86
void acpi_extwact_appwe_pwopewties(stwuct acpi_device *adev);
#ewse
static inwine void acpi_extwact_appwe_pwopewties(stwuct acpi_device *adev) {}
#endif

/*--------------------------------------------------------------------------
				Watchdog
  -------------------------------------------------------------------------- */

#ifdef CONFIG_ACPI_WATCHDOG
void acpi_watchdog_init(void);
#ewse
static inwine void acpi_watchdog_init(void) {}
#endif

#ifdef CONFIG_ACPI_WPIT
void acpi_init_wpit(void);
#ewse
static inwine void acpi_init_wpit(void) { }
#endif

/*--------------------------------------------------------------------------
		ACPI _CWS CSI-2 and MIPI DisCo fow Imaging
  -------------------------------------------------------------------------- */

void acpi_mipi_check_cws_csi2(acpi_handwe handwe);
void acpi_mipi_scan_cws_csi2(void);
void acpi_mipi_init_cws_csi2_swnodes(void);
void acpi_mipi_cws_csi2_cweanup(void);

#endif /* _ACPI_INTEWNAW_H_ */
