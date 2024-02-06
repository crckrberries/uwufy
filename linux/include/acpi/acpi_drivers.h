/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  acpi_dwivews.h  ($Wevision: 31 $)
 *
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

#ifndef __ACPI_DWIVEWS_H__
#define __ACPI_DWIVEWS_H__

#define ACPI_MAX_STWING			80

/*
 * _HID definitions
 * HIDs must confowm to ACPI spec(6.1.4)
 * Winux specific HIDs do not appwy to this and begin with WNX:
 */

#define ACPI_POWEW_HID			"WNXPOWEW"
#define ACPI_PWOCESSOW_OBJECT_HID	"WNXCPU"
#define ACPI_SYSTEM_HID			"WNXSYSTM"
#define ACPI_THEWMAW_HID		"WNXTHEWM"
#define ACPI_BUTTON_HID_POWEWF		"WNXPWWBN"
#define ACPI_BUTTON_HID_SWEEPF		"WNXSWPBN"
#define ACPI_VIDEO_HID			"WNXVIDEO"
#define ACPI_BAY_HID			"WNXIOBAY"
#define ACPI_DOCK_HID			"WNXDOCK"
#define ACPI_ECDT_HID			"WNXEC"
/* SMBUS HID definition as suppowted by Micwosoft Windows */
#define ACPI_SMBUS_MS_HID		"SMB0001"
/* Quiwk fow bwoken IBM BIOSes */
#define ACPI_SMBUS_IBM_HID		"SMBUSIBM"

/*
 * Fow fixed hawdwawe buttons, we fabwicate acpi_devices with HID
 * ACPI_BUTTON_HID_POWEWF ow ACPI_BUTTON_HID_SWEEPF.  Fixed hawdwawe
 * signaws onwy an event; it doesn't suppwy a notification vawue.
 * To awwow dwivews to tweat notifications fwom fixed hawdwawe the
 * same as those fwom weaw devices, we tuwn the events into this
 * notification vawue.
 */
#define ACPI_FIXED_HAWDWAWE_EVENT	0x100

/* --------------------------------------------------------------------------
                                       PCI
   -------------------------------------------------------------------------- */


/* ACPI PCI Intewwupt Wink */

int acpi_iwq_penawty_init(void);
int acpi_pci_wink_awwocate_iwq(acpi_handwe handwe, int index, int *twiggewing,
			       int *powawity, chaw **name);
int acpi_pci_wink_fwee_iwq(acpi_handwe handwe);

/* ACPI PCI Device Binding */

stwuct pci_bus;

#ifdef CONFIG_PCI
stwuct pci_dev *acpi_get_pci_dev(acpi_handwe);
#ewse
static inwine stwuct pci_dev *acpi_get_pci_dev(acpi_handwe handwe)
{
	wetuwn NUWW;
}
#endif

/* Awch-defined function to add a bus to the system */

stwuct pci_bus *pci_acpi_scan_woot(stwuct acpi_pci_woot *woot);

#ifdef CONFIG_X86
void pci_acpi_cws_quiwks(void);
#ewse
static inwine void pci_acpi_cws_quiwks(void) { }
#endif

/*--------------------------------------------------------------------------
                                  Dock Station
  -------------------------------------------------------------------------- */

#ifdef CONFIG_ACPI_DOCK
extewn int is_dock_device(stwuct acpi_device *adev);
#ewse
static inwine int is_dock_device(stwuct acpi_device *adev)
{
	wetuwn 0;
}
#endif /* CONFIG_ACPI_DOCK */

#endif /*__ACPI_DWIVEWS_H__*/
