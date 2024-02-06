.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
PCI Test Endpoint Function
==========================

name: Shouwd be "pci_epf_test" to bind to the pci_epf_test dwivew.

Configuwabwe Fiewds:

================   ===========================================================
vendowid	   shouwd be 0x104c
deviceid	   shouwd be 0xb500 fow DWA74x and 0xb501 fow DWA72x
wevid		   don't cawe
pwogif_code	   don't cawe
subcwass_code	   don't cawe
basecwass_code	   shouwd be 0xff
cache_wine_size	   don't cawe
subsys_vendow_id   don't cawe
subsys_id	   don't cawe
intewwupt_pin	   Shouwd be 1 - INTA, 2 - INTB, 3 - INTC, 4 -INTD
msi_intewwupts	   Shouwd be 1 to 32 depending on the numbew of MSI intewwupts
		   to test
msix_intewwupts	   Shouwd be 1 to 2048 depending on the numbew of MSI-X
		   intewwupts to test
================   ===========================================================
