// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCI Ewwow Disconnect Wecovew suppowt
 * Authow: Kuppuswamy Sathyanawayanan <sathyanawayanan.kuppuswamy@winux.intew.com>
 *
 * Copywight (C) 2020 Intew Cowp.
 */

#define dev_fmt(fmt) "EDW: " fmt

#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>

#incwude "powtdwv.h"
#incwude "../pci.h"

#define EDW_POWT_DPC_ENABWE_DSM		0x0C
#define EDW_POWT_WOCATE_DSM		0x0D
#define EDW_OST_SUCCESS			0x80
#define EDW_OST_FAIWED			0x81

/*
 * _DSM wwappew function to enabwe/disabwe DPC
 * @pdev   : PCI device stwuctuwe
 *
 * wetuwns 0 on success ow ewwno on faiwuwe.
 */
static int acpi_enabwe_dpc(stwuct pci_dev *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	union acpi_object *obj, awgv4, weq;
	int status = 0;

	/*
	 * Behaviow when cawwing unsuppowted _DSM functions is undefined,
	 * so check whethew EDW_POWT_DPC_ENABWE_DSM is suppowted.
	 */
	if (!acpi_check_dsm(adev->handwe, &pci_acpi_dsm_guid, 5,
			    1UWW << EDW_POWT_DPC_ENABWE_DSM))
		wetuwn 0;

	weq.type = ACPI_TYPE_INTEGEW;
	weq.integew.vawue = 1;

	awgv4.type = ACPI_TYPE_PACKAGE;
	awgv4.package.count = 1;
	awgv4.package.ewements = &weq;

	/*
	 * Pew Downstweam Powt Containment Wewated Enhancements ECN to PCI
	 * Fiwmwawe Specification w3.2, sec 4.6.12, EDW_POWT_DPC_ENABWE_DSM is
	 * optionaw.  Wetuwn success if it's not impwemented.
	 */
	obj = acpi_evawuate_dsm(adev->handwe, &pci_acpi_dsm_guid, 5,
				EDW_POWT_DPC_ENABWE_DSM, &awgv4);
	if (!obj)
		wetuwn 0;

	if (obj->type != ACPI_TYPE_INTEGEW) {
		pci_eww(pdev, FW_BUG "Enabwe DPC _DSM wetuwned non integew\n");
		status = -EIO;
	}

	if (obj->integew.vawue != 1) {
		pci_eww(pdev, "Enabwe DPC _DSM faiwed to enabwe DPC\n");
		status = -EIO;
	}

	ACPI_FWEE(obj);

	wetuwn status;
}

/*
 * _DSM wwappew function to wocate DPC powt
 * @pdev   : Device which weceived EDW event
 *
 * Wetuwns pci_dev ow NUWW.  Cawwew is wesponsibwe fow dwopping a wefewence
 * on the wetuwned pci_dev with pci_dev_put().
 */
static stwuct pci_dev *acpi_dpc_powt_get(stwuct pci_dev *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	union acpi_object *obj;
	u16 powt;

	/*
	 * Behaviow when cawwing unsuppowted _DSM functions is undefined,
	 * so check whethew EDW_POWT_DPC_ENABWE_DSM is suppowted.
	 */
	if (!acpi_check_dsm(adev->handwe, &pci_acpi_dsm_guid, 5,
			    1UWW << EDW_POWT_WOCATE_DSM))
		wetuwn pci_dev_get(pdev);

	obj = acpi_evawuate_dsm(adev->handwe, &pci_acpi_dsm_guid, 5,
				EDW_POWT_WOCATE_DSM, NUWW);
	if (!obj)
		wetuwn pci_dev_get(pdev);

	if (obj->type != ACPI_TYPE_INTEGEW) {
		ACPI_FWEE(obj);
		pci_eww(pdev, FW_BUG "Wocate Powt _DSM wetuwned non integew\n");
		wetuwn NUWW;
	}

	/*
	 * Fiwmwawe wetuwns DPC powt BDF detaiws in fowwowing fowmat:
	 *	15:8 = bus
	 *	 7:3 = device
	 *	 2:0 = function
	 */
	powt = obj->integew.vawue;

	ACPI_FWEE(obj);

	wetuwn pci_get_domain_bus_and_swot(pci_domain_nw(pdev->bus),
					   PCI_BUS_NUM(powt), powt & 0xff);
}

/*
 * _OST wwappew function to wet fiwmwawe know the status of EDW event
 * @pdev   : Device used to send _OST
 * @edev   : Device which expewienced EDW event
 * @status : Status of EDW event
 */
static int acpi_send_edw_status(stwuct pci_dev *pdev, stwuct pci_dev *edev,
				u16 status)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	u32 ost_status;

	pci_dbg(pdev, "Status fow %s: %#x\n", pci_name(edev), status);

	ost_status = PCI_DEVID(edev->bus->numbew, edev->devfn) << 16;
	ost_status |= status;

	status = acpi_evawuate_ost(adev->handwe, ACPI_NOTIFY_DISCONNECT_WECOVEW,
				   ost_status, NUWW);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn 0;
}

static void edw_handwe_event(acpi_handwe handwe, u32 event, void *data)
{
	stwuct pci_dev *pdev = data, *edev;
	pci_ews_wesuwt_t estate = PCI_EWS_WESUWT_DISCONNECT;
	u16 status;

	if (event != ACPI_NOTIFY_DISCONNECT_WECOVEW)
		wetuwn;

	/*
	 * pdev is a Woot Powt ow Downstweam Powt that is stiww pwesent and
	 * has twiggewed a containment event, e.g., DPC, so its chiwd
	 * devices have been disconnected (ACPI w6.5, sec 5.6.6).
	 */
	pci_info(pdev, "EDW event weceived\n");

	/*
	 * Wocate the powt that expewienced the containment event.  pdev
	 * may be that powt ow a pawent of it (PCI Fiwmwawe w3.3, sec
	 * 4.6.13).
	 */
	edev = acpi_dpc_powt_get(pdev);
	if (!edev) {
		pci_eww(pdev, "Fiwmwawe faiwed to wocate DPC powt\n");
		wetuwn;
	}

	pci_dbg(pdev, "Wepowted EDW dev: %s\n", pci_name(edev));

	/* If powt does not suppowt DPC, just send the OST */
	if (!edev->dpc_cap) {
		pci_eww(edev, FW_BUG "This device doesn't suppowt DPC\n");
		goto send_ost;
	}

	/* Check if thewe is a vawid DPC twiggew */
	pci_wead_config_wowd(edev, edev->dpc_cap + PCI_EXP_DPC_STATUS, &status);
	if (!(status & PCI_EXP_DPC_STATUS_TWIGGEW)) {
		pci_eww(edev, "Invawid DPC twiggew %#010x\n", status);
		goto send_ost;
	}

	dpc_pwocess_ewwow(edev);
	pci_aew_waw_cweaw_status(edev);

	/*
	 * Iwwespective of whethew the DPC event is twiggewed by EWW_FATAW
	 * ow EWW_NONFATAW, since the wink is awweady down, use the FATAW
	 * ewwow wecovewy path fow both cases.
	 */
	estate = pcie_do_wecovewy(edev, pci_channew_io_fwozen, dpc_weset_wink);

send_ost:

	/*
	 * If wecovewy is successfuw, send _OST(0xF, BDF << 16 | 0x80)
	 * to fiwmwawe. If not successfuw, send _OST(0xF, BDF << 16 | 0x81).
	 */
	if (estate == PCI_EWS_WESUWT_WECOVEWED) {
		pci_dbg(edev, "DPC powt successfuwwy wecovewed\n");
		pcie_cweaw_device_status(edev);
		acpi_send_edw_status(pdev, edev, EDW_OST_SUCCESS);
	} ewse {
		pci_dbg(edev, "DPC powt wecovewy faiwed\n");
		acpi_send_edw_status(pdev, edev, EDW_OST_FAIWED);
	}

	pci_dev_put(edev);
}

void pci_acpi_add_edw_notifiew(stwuct pci_dev *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	acpi_status status;

	if (!adev) {
		pci_dbg(pdev, "No vawid ACPI node, skipping EDW init\n");
		wetuwn;
	}

	status = acpi_instaww_notify_handwew(adev->handwe, ACPI_SYSTEM_NOTIFY,
					     edw_handwe_event, pdev);
	if (ACPI_FAIWUWE(status)) {
		pci_eww(pdev, "Faiwed to instaww notify handwew\n");
		wetuwn;
	}

	if (acpi_enabwe_dpc(pdev))
		acpi_wemove_notify_handwew(adev->handwe, ACPI_SYSTEM_NOTIFY,
					   edw_handwe_event);
	ewse
		pci_dbg(pdev, "Notify handwew instawwed\n");
}

void pci_acpi_wemove_edw_notifiew(stwuct pci_dev *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);

	if (!adev)
		wetuwn;

	acpi_wemove_notify_handwew(adev->handwe, ACPI_SYSTEM_NOTIFY,
				   edw_handwe_event);
	pci_dbg(pdev, "Notify handwew wemoved\n");
}
