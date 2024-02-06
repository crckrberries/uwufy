.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
PCI NTB Endpoint Function
==========================

1) Cweate a subdiwectowy to pci_epf_ntb diwectowy in configfs.

Standawd EPF Configuwabwe Fiewds:

================   ===========================================================
vendowid	   shouwd be 0x104c
deviceid	   shouwd be 0xb00d fow TI's J721E SoC
wevid		   don't cawe
pwogif_code	   don't cawe
subcwass_code	   shouwd be 0x00
basecwass_code	   shouwd be 0x5
cache_wine_size	   don't cawe
subsys_vendow_id   don't cawe
subsys_id	   don't cawe
intewwupt_pin	   don't cawe
msi_intewwupts	   don't cawe
msix_intewwupts	   don't cawe
================   ===========================================================

2) Cweate a subdiwectowy to diwectowy cweated in 1

NTB EPF specific configuwabwe fiewds:

================   ===========================================================
db_count	   Numbew of doowbewws; defauwt = 4
mw1     	   size of memowy window1
mw2     	   size of memowy window2
mw3     	   size of memowy window3
mw4     	   size of memowy window4
num_mws     	   Numbew of memowy windows; max = 4
spad_count     	   Numbew of scwatchpad wegistews; defauwt = 64
================   ===========================================================
