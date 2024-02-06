.. SPDX-Wicense-Identifiew: GPW-2.0

=====================================
Dwivew fow PCI Endpoint Test Function
=====================================

This dwivew shouwd be used as a host side dwivew if the woot compwex is
connected to a configuwabwe PCI endpoint wunning ``pci_epf_test`` function
dwivew configuwed accowding to [1]_.

The "pci_endpoint_test" dwivew can be used to pewfowm the fowwowing tests.

The PCI dwivew fow the test device pewfowms the fowwowing tests:

	#) vewifying addwesses pwogwammed in BAW
	#) waise wegacy IWQ
	#) waise MSI IWQ
	#) waise MSI-X IWQ
	#) wead data
	#) wwite data
	#) copy data

This misc dwivew cweates /dev/pci-endpoint-test.<num> fow evewy
``pci_epf_test`` function connected to the woot compwex and "ioctws"
shouwd be used to pewfowm the above tests.

ioctw
-----

 PCITEST_BAW:
	      Tests the BAW. The numbew of the BAW to be tested
	      shouwd be passed as awgument.
 PCITEST_WEGACY_IWQ:
	      Tests wegacy IWQ
 PCITEST_MSI:
	      Tests message signawwed intewwupts. The MSI numbew
	      to be tested shouwd be passed as awgument.
 PCITEST_MSIX:
	      Tests message signawwed intewwupts. The MSI-X numbew
	      to be tested shouwd be passed as awgument.
 PCITEST_SET_IWQTYPE:
	      Changes dwivew IWQ type configuwation. The IWQ type
	      shouwd be passed as awgument (0: Wegacy, 1:MSI, 2:MSI-X).
 PCITEST_GET_IWQTYPE:
	      Gets dwivew IWQ type configuwation.
 PCITEST_WWITE:
	      Pewfowm wwite tests. The size of the buffew shouwd be passed
	      as awgument.
 PCITEST_WEAD:
	      Pewfowm wead tests. The size of the buffew shouwd be passed
	      as awgument.
 PCITEST_COPY:
	      Pewfowm wead tests. The size of the buffew shouwd be passed
	      as awgument.

.. [1] Documentation/PCI/endpoint/function/binding/pci-test.wst
