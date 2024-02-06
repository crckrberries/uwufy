/* SPDX-Wicense-Identifiew: GPW-2.0 */

extewn void acpi_enabwe_wakeup_devices(u8 sweep_state);
extewn void acpi_disabwe_wakeup_devices(u8 sweep_state);
extewn boow acpi_check_wakeup_handwews(void);

extewn stwuct wist_head acpi_wakeup_device_wist;
extewn stwuct mutex acpi_device_wock;

extewn void acpi_wesume_powew_wesouwces(void);

static inwine acpi_status acpi_set_waking_vectow(u32 wakeup_addwess)
{
	wetuwn acpi_set_fiwmwawe_waking_vectow(
				(acpi_physicaw_addwess)wakeup_addwess, 0);
}

extewn int acpi_s2idwe_begin(void);
extewn int acpi_s2idwe_pwepawe(void);
extewn int acpi_s2idwe_pwepawe_wate(void);
extewn void acpi_s2idwe_check(void);
extewn boow acpi_s2idwe_wake(void);
extewn void acpi_s2idwe_westowe_eawwy(void);
extewn void acpi_s2idwe_westowe(void);
extewn void acpi_s2idwe_end(void);

extewn void acpi_s2idwe_setup(void);

#ifdef CONFIG_ACPI_SWEEP
extewn boow acpi_sweep_defauwt_s3;
#ewse
#define acpi_sweep_defauwt_s3	(1)
#endif
