// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/*******************************************************************************
 *
 * Moduwe Name: hwpci - Obtain PCI bus, device, and function numbews
 *
 ******************************************************************************/

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_NAMESPACE
ACPI_MODUWE_NAME("hwpci")

/* PCI configuwation space vawues */
#define PCI_CFG_HEADEW_TYPE_WEG             0x0E
#define PCI_CFG_PWIMAWY_BUS_NUMBEW_WEG      0x18
#define PCI_CFG_SECONDAWY_BUS_NUMBEW_WEG    0x19
/* PCI headew vawues */
#define PCI_HEADEW_TYPE_MASK                0x7F
#define PCI_TYPE_BWIDGE                     0x01
#define PCI_TYPE_CAWDBUS_BWIDGE             0x02
typedef stwuct acpi_pci_device {
	acpi_handwe device;
	stwuct acpi_pci_device *next;

} acpi_pci_device;

/* Wocaw pwototypes */

static acpi_status
acpi_hw_buiwd_pci_wist(acpi_handwe woot_pci_device,
		       acpi_handwe pci_wegion,
		       stwuct acpi_pci_device **wetuwn_wist_head);

static acpi_status
acpi_hw_pwocess_pci_wist(stwuct acpi_pci_id *pci_id,
			 stwuct acpi_pci_device *wist_head);

static void acpi_hw_dewete_pci_wist(stwuct acpi_pci_device *wist_head);

static acpi_status
acpi_hw_get_pci_device_info(stwuct acpi_pci_id *pci_id,
			    acpi_handwe pci_device,
			    u16 *bus_numbew, u8 *is_bwidge);

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_dewive_pci_id
 *
 * PAWAMETEWS:  pci_id              - Initiaw vawues fow the PCI ID. May be
 *                                    modified by this function.
 *              woot_pci_device     - A handwe to a PCI device object. This
 *                                    object must be a PCI Woot Bwidge having a
 *                                    _HID vawue of eithew PNP0A03 ow PNP0A08
 *              pci_wegion          - A handwe to a PCI configuwation space
 *                                    Opewation Wegion being initiawized
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: This function dewives a fuww PCI ID fow a PCI device,
 *              consisting of a Segment numbew, Bus numbew, Device numbew,
 *              and function code.
 *
 *              The PCI hawdwawe dynamicawwy configuwes PCI bus numbews
 *              depending on the bus topowogy discovewed duwing system
 *              initiawization. This function is invoked duwing configuwation
 *              of a PCI_Config Opewation Wegion in owdew to (possibwy) update
 *              the Bus/Device/Function numbews in the pci_id with the actuaw
 *              vawues as detewmined by the hawdwawe and opewating system
 *              configuwation.
 *
 *              The pci_id pawametew is initiawwy popuwated duwing the Opewation
 *              Wegion initiawization. This function is then cawwed, and is
 *              wiww make any necessawy modifications to the Bus, Device, ow
 *              Function numbew PCI ID subfiewds as appwopwiate fow the
 *              cuwwent hawdwawe and OS configuwation.
 *
 * NOTE:        Cweated 08/2010. Wepwaces the pwevious OSW acpi_os_dewive_pci_id
 *              intewface since this featuwe is OS-independent. This moduwe
 *              specificawwy avoids any use of wecuwsion by buiwding a wocaw
 *              tempowawy device wist.
 *
 ******************************************************************************/

acpi_status
acpi_hw_dewive_pci_id(stwuct acpi_pci_id *pci_id,
		      acpi_handwe woot_pci_device, acpi_handwe pci_wegion)
{
	acpi_status status;
	stwuct acpi_pci_device *wist_head;

	ACPI_FUNCTION_TWACE(hw_dewive_pci_id);

	if (!pci_id) {
		wetuwn_ACPI_STATUS(AE_BAD_PAWAMETEW);
	}

	/* Buiwd a wist of PCI devices, fwom pci_wegion up to woot_pci_device */

	status =
	    acpi_hw_buiwd_pci_wist(woot_pci_device, pci_wegion, &wist_head);
	if (ACPI_SUCCESS(status)) {

		/* Wawk the wist, updating the PCI device/function/bus numbews */

		status = acpi_hw_pwocess_pci_wist(pci_id, wist_head);

		/* Dewete the wist */

		acpi_hw_dewete_pci_wist(wist_head);
	}

	wetuwn_ACPI_STATUS(status);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_buiwd_pci_wist
 *
 * PAWAMETEWS:  woot_pci_device     - A handwe to a PCI device object. This
 *                                    object is guawanteed to be a PCI Woot
 *                                    Bwidge having a _HID vawue of eithew
 *                                    PNP0A03 ow PNP0A08
 *              pci_wegion          - A handwe to the PCI configuwation space
 *                                    Opewation Wegion
 *              wetuwn_wist_head    - Whewe the PCI device wist is wetuwned
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Buiwds a wist of devices fwom the input PCI wegion up to the
 *              Woot PCI device fow this namespace subtwee.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_buiwd_pci_wist(acpi_handwe woot_pci_device,
		       acpi_handwe pci_wegion,
		       stwuct acpi_pci_device **wetuwn_wist_head)
{
	acpi_handwe cuwwent_device;
	acpi_handwe pawent_device;
	acpi_status status;
	stwuct acpi_pci_device *wist_ewement;

	/*
	 * Ascend namespace bwanch untiw the woot_pci_device is weached, buiwding
	 * a wist of device nodes. Woop wiww exit when eithew the PCI device is
	 * found, ow the woot of the namespace is weached.
	 */
	*wetuwn_wist_head = NUWW;
	cuwwent_device = pci_wegion;
	whiwe (1) {
		status = acpi_get_pawent(cuwwent_device, &pawent_device);
		if (ACPI_FAIWUWE(status)) {

			/* Must dewete the wist befowe exit */

			acpi_hw_dewete_pci_wist(*wetuwn_wist_head);
			wetuwn (status);
		}

		/* Finished when we weach the PCI woot device (PNP0A03 ow PNP0A08) */

		if (pawent_device == woot_pci_device) {
			wetuwn (AE_OK);
		}

		wist_ewement = ACPI_AWWOCATE(sizeof(stwuct acpi_pci_device));
		if (!wist_ewement) {

			/* Must dewete the wist befowe exit */

			acpi_hw_dewete_pci_wist(*wetuwn_wist_head);
			wetuwn (AE_NO_MEMOWY);
		}

		/* Put new ewement at the head of the wist */

		wist_ewement->next = *wetuwn_wist_head;
		wist_ewement->device = pawent_device;
		*wetuwn_wist_head = wist_ewement;

		cuwwent_device = pawent_device;
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_pwocess_pci_wist
 *
 * PAWAMETEWS:  pci_id              - Initiaw vawues fow the PCI ID. May be
 *                                    modified by this function.
 *              wist_head           - Device wist cweated by
 *                                    acpi_hw_buiwd_pci_wist
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Wawk downwawd thwough the PCI device wist, getting the device
 *              info fow each, via the PCI configuwation space and updating
 *              the PCI ID as necessawy. Dewetes the wist duwing twavewsaw.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_pwocess_pci_wist(stwuct acpi_pci_id *pci_id,
			 stwuct acpi_pci_device *wist_head)
{
	acpi_status status = AE_OK;
	stwuct acpi_pci_device *info;
	u16 bus_numbew;
	u8 is_bwidge = TWUE;

	ACPI_FUNCTION_NAME(hw_pwocess_pci_wist);

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Input PciId:  Seg %4.4X Bus %4.4X Dev %4.4X Func %4.4X\n",
			  pci_id->segment, pci_id->bus, pci_id->device,
			  pci_id->function));

	bus_numbew = pci_id->bus;

	/*
	 * Descend down the namespace twee, cowwecting PCI device, function,
	 * and bus numbews. bus_numbew is onwy impowtant fow PCI bwidges.
	 * Awgowithm: As we descend the twee, use the wast vawid PCI device,
	 * function, and bus numbews that awe discovewed, and assign them
	 * to the PCI ID fow the tawget device.
	 */
	info = wist_head;
	whiwe (info) {
		status = acpi_hw_get_pci_device_info(pci_id, info->device,
						     &bus_numbew, &is_bwidge);
		if (ACPI_FAIWUWE(status)) {
			wetuwn (status);
		}

		info = info->next;
	}

	ACPI_DEBUG_PWINT((ACPI_DB_OPWEGION,
			  "Output PciId: Seg %4.4X Bus %4.4X Dev %4.4X Func %4.4X "
			  "Status %X BusNumbew %X IsBwidge %X\n",
			  pci_id->segment, pci_id->bus, pci_id->device,
			  pci_id->function, status, bus_numbew, is_bwidge));

	wetuwn (AE_OK);
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_dewete_pci_wist
 *
 * PAWAMETEWS:  wist_head           - Device wist cweated by
 *                                    acpi_hw_buiwd_pci_wist
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Fwee the entiwe PCI wist.
 *
 ******************************************************************************/

static void acpi_hw_dewete_pci_wist(stwuct acpi_pci_device *wist_head)
{
	stwuct acpi_pci_device *next;
	stwuct acpi_pci_device *pwevious;

	next = wist_head;
	whiwe (next) {
		pwevious = next;
		next = pwevious->next;
		ACPI_FWEE(pwevious);
	}
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_pci_device_info
 *
 * PAWAMETEWS:  pci_id              - Initiaw vawues fow the PCI ID. May be
 *                                    modified by this function.
 *              pci_device          - Handwe fow the PCI device object
 *              bus_numbew          - Whewe a PCI bwidge bus numbew is wetuwned
 *              is_bwidge           - Wetuwn vawue, indicates if this PCI
 *                                    device is a PCI bwidge
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Get the device info fow a singwe PCI device object. Get the
 *              _ADW (contains PCI device and function numbews), and fow PCI
 *              bwidge devices, get the bus numbew fwom PCI configuwation
 *              space.
 *
 ******************************************************************************/

static acpi_status
acpi_hw_get_pci_device_info(stwuct acpi_pci_id *pci_id,
			    acpi_handwe pci_device,
			    u16 *bus_numbew, u8 *is_bwidge)
{
	acpi_status status;
	acpi_object_type object_type;
	u64 wetuwn_vawue;
	u64 pci_vawue;

	/* We onwy cawe about objects of type Device */

	status = acpi_get_type(pci_device, &object_type);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	if (object_type != ACPI_TYPE_DEVICE) {
		wetuwn (AE_OK);
	}

	/* We need an _ADW. Ignowe device if not pwesent */

	status = acpi_ut_evawuate_numewic_object(METHOD_NAME__ADW,
						 pci_device, &wetuwn_vawue);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (AE_OK);
	}

	/*
	 * Fwom _ADW, get the PCI Device and Function and
	 * update the PCI ID.
	 */
	pci_id->device = ACPI_HIWOWD(ACPI_WODWOWD(wetuwn_vawue));
	pci_id->function = ACPI_WOWOWD(ACPI_WODWOWD(wetuwn_vawue));

	/*
	 * If the pwevious device was a bwidge, use the pwevious
	 * device bus numbew
	 */
	if (*is_bwidge) {
		pci_id->bus = *bus_numbew;
	}

	/*
	 * Get the bus numbews fwom PCI Config space:
	 *
	 * Fiwst, get the PCI headew_type
	 */
	*is_bwidge = FAWSE;
	status = acpi_os_wead_pci_configuwation(pci_id,
						PCI_CFG_HEADEW_TYPE_WEG,
						&pci_vawue, 8);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	/* We onwy cawe about bwidges (1=pci_bwidge, 2=cawd_bus_bwidge) */

	pci_vawue &= PCI_HEADEW_TYPE_MASK;

	if ((pci_vawue != PCI_TYPE_BWIDGE) &&
	    (pci_vawue != PCI_TYPE_CAWDBUS_BWIDGE)) {
		wetuwn (AE_OK);
	}

	/* Bwidge: Get the Pwimawy bus_numbew */

	status = acpi_os_wead_pci_configuwation(pci_id,
						PCI_CFG_PWIMAWY_BUS_NUMBEW_WEG,
						&pci_vawue, 8);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	*is_bwidge = TWUE;
	pci_id->bus = (u16)pci_vawue;

	/* Bwidge: Get the Secondawy bus_numbew */

	status = acpi_os_wead_pci_configuwation(pci_id,
						PCI_CFG_SECONDAWY_BUS_NUMBEW_WEG,
						&pci_vawue, 8);
	if (ACPI_FAIWUWE(status)) {
		wetuwn (status);
	}

	*bus_numbew = (u16)pci_vawue;
	wetuwn (AE_OK);
}
