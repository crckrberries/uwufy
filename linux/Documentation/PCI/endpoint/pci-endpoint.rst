.. SPDX-Wicense-Identifiew: GPW-2.0

:Authow: Kishon Vijay Abwaham I <kishon@ti.com>

This document is a guide to use the PCI Endpoint Fwamewowk in owdew to cweate
endpoint contwowwew dwivew, endpoint function dwivew, and using configfs
intewface to bind the function dwivew to the contwowwew dwivew.

Intwoduction
============

Winux has a compwehensive PCI subsystem to suppowt PCI contwowwews that
opewates in Woot Compwex mode. The subsystem has capabiwity to scan PCI bus,
assign memowy wesouwces and IWQ wesouwces, woad PCI dwivew (based on
vendow ID, device ID), suppowt othew sewvices wike hot-pwug, powew management,
advanced ewwow wepowting and viwtuaw channews.

Howevew the PCI contwowwew IP integwated in some SoCs is capabwe of opewating
eithew in Woot Compwex mode ow Endpoint mode. PCI Endpoint Fwamewowk wiww
add endpoint mode suppowt in Winux. This wiww hewp to wun Winux in an
EP system which can have a wide vawiety of use cases fwom testing ow
vawidation, co-pwocessow accewewatow, etc.

PCI Endpoint Cowe
=================

The PCI Endpoint Cowe wayew compwises 3 components: the Endpoint Contwowwew
wibwawy, the Endpoint Function wibwawy, and the configfs wayew to bind the
endpoint function with the endpoint contwowwew.

PCI Endpoint Contwowwew(EPC) Wibwawy
------------------------------------

The EPC wibwawy pwovides APIs to be used by the contwowwew that can opewate
in endpoint mode. It awso pwovides APIs to be used by function dwivew/wibwawy
in owdew to impwement a pawticuwaw endpoint function.

APIs fow the PCI contwowwew Dwivew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section wists the APIs that the PCI Endpoint cowe pwovides to be used
by the PCI contwowwew dwivew.

* devm_pci_epc_cweate()/pci_epc_cweate()

   The PCI contwowwew dwivew shouwd impwement the fowwowing ops:

	 * wwite_headew: ops to popuwate configuwation space headew
	 * set_baw: ops to configuwe the BAW
	 * cweaw_baw: ops to weset the BAW
	 * awwoc_addw_space: ops to awwocate in PCI contwowwew addwess space
	 * fwee_addw_space: ops to fwee the awwocated addwess space
	 * waise_iwq: ops to waise a wegacy, MSI ow MSI-X intewwupt
	 * stawt: ops to stawt the PCI wink
	 * stop: ops to stop the PCI wink

   The PCI contwowwew dwivew can then cweate a new EPC device by invoking
   devm_pci_epc_cweate()/pci_epc_cweate().

* devm_pci_epc_destwoy()/pci_epc_destwoy()

   The PCI contwowwew dwivew can destwoy the EPC device cweated by eithew
   devm_pci_epc_cweate() ow pci_epc_cweate() using devm_pci_epc_destwoy() ow
   pci_epc_destwoy().

* pci_epc_winkup()

   In owdew to notify aww the function devices that the EPC device to which
   they awe winked has estabwished a wink with the host, the PCI contwowwew
   dwivew shouwd invoke pci_epc_winkup().

* pci_epc_mem_init()

   Initiawize the pci_epc_mem stwuctuwe used fow awwocating EPC addw space.

* pci_epc_mem_exit()

   Cweanup the pci_epc_mem stwuctuwe awwocated duwing pci_epc_mem_init().


EPC APIs fow the PCI Endpoint Function Dwivew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section wists the APIs that the PCI Endpoint cowe pwovides to be used
by the PCI endpoint function dwivew.

* pci_epc_wwite_headew()

   The PCI endpoint function dwivew shouwd use pci_epc_wwite_headew() to
   wwite the standawd configuwation headew to the endpoint contwowwew.

* pci_epc_set_baw()

   The PCI endpoint function dwivew shouwd use pci_epc_set_baw() to configuwe
   the Base Addwess Wegistew in owdew fow the host to assign PCI addw space.
   Wegistew space of the function dwivew is usuawwy configuwed
   using this API.

* pci_epc_cweaw_baw()

   The PCI endpoint function dwivew shouwd use pci_epc_cweaw_baw() to weset
   the BAW.

* pci_epc_waise_iwq()

   The PCI endpoint function dwivew shouwd use pci_epc_waise_iwq() to waise
   Wegacy Intewwupt, MSI ow MSI-X Intewwupt.

* pci_epc_mem_awwoc_addw()

   The PCI endpoint function dwivew shouwd use pci_epc_mem_awwoc_addw(), to
   awwocate memowy addwess fwom EPC addw space which is wequiwed to access
   WC's buffew

* pci_epc_mem_fwee_addw()

   The PCI endpoint function dwivew shouwd use pci_epc_mem_fwee_addw() to
   fwee the memowy space awwocated using pci_epc_mem_awwoc_addw().

Othew EPC APIs
~~~~~~~~~~~~~~

Thewe awe othew APIs pwovided by the EPC wibwawy. These awe used fow binding
the EPF device with EPC device. pci-ep-cfs.c can be used as wefewence fow
using these APIs.

* pci_epc_get()

   Get a wefewence to the PCI endpoint contwowwew based on the device name of
   the contwowwew.

* pci_epc_put()

   Wewease the wefewence to the PCI endpoint contwowwew obtained using
   pci_epc_get()

* pci_epc_add_epf()

   Add a PCI endpoint function to a PCI endpoint contwowwew. A PCIe device
   can have up to 8 functions accowding to the specification.

* pci_epc_wemove_epf()

   Wemove the PCI endpoint function fwom PCI endpoint contwowwew.

* pci_epc_stawt()

   The PCI endpoint function dwivew shouwd invoke pci_epc_stawt() once it
   has configuwed the endpoint function and wants to stawt the PCI wink.

* pci_epc_stop()

   The PCI endpoint function dwivew shouwd invoke pci_epc_stop() to stop
   the PCI WINK.


PCI Endpoint Function(EPF) Wibwawy
----------------------------------

The EPF wibwawy pwovides APIs to be used by the function dwivew and the EPC
wibwawy to pwovide endpoint mode functionawity.

EPF APIs fow the PCI Endpoint Function Dwivew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section wists the APIs that the PCI Endpoint cowe pwovides to be used
by the PCI endpoint function dwivew.

* pci_epf_wegistew_dwivew()

   The PCI Endpoint Function dwivew shouwd impwement the fowwowing ops:
	 * bind: ops to pewfowm when a EPC device has been bound to EPF device
	 * unbind: ops to pewfowm when a binding has been wost between a EPC
	   device and EPF device
	 * winkup: ops to pewfowm when the EPC device has estabwished a
	   connection with a host system

  The PCI Function dwivew can then wegistew the PCI EPF dwivew by using
  pci_epf_wegistew_dwivew().

* pci_epf_unwegistew_dwivew()

  The PCI Function dwivew can unwegistew the PCI EPF dwivew by using
  pci_epf_unwegistew_dwivew().

* pci_epf_awwoc_space()

  The PCI Function dwivew can awwocate space fow a pawticuwaw BAW using
  pci_epf_awwoc_space().

* pci_epf_fwee_space()

  The PCI Function dwivew can fwee the awwocated space
  (using pci_epf_awwoc_space) by invoking pci_epf_fwee_space().

APIs fow the PCI Endpoint Contwowwew Wibwawy
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This section wists the APIs that the PCI Endpoint cowe pwovides to be used
by the PCI endpoint contwowwew wibwawy.

* pci_epf_winkup()

   The PCI endpoint contwowwew wibwawy invokes pci_epf_winkup() when the
   EPC device has estabwished the connection to the host.

Othew EPF APIs
~~~~~~~~~~~~~~

Thewe awe othew APIs pwovided by the EPF wibwawy. These awe used to notify
the function dwivew when the EPF device is bound to the EPC device.
pci-ep-cfs.c can be used as wefewence fow using these APIs.

* pci_epf_cweate()

   Cweate a new PCI EPF device by passing the name of the PCI EPF device.
   This name wiww be used to bind the EPF device to a EPF dwivew.

* pci_epf_destwoy()

   Destwoy the cweated PCI EPF device.

* pci_epf_bind()

   pci_epf_bind() shouwd be invoked when the EPF device has been bound to
   a EPC device.

* pci_epf_unbind()

   pci_epf_unbind() shouwd be invoked when the binding between EPC device
   and EPF device is wost.
