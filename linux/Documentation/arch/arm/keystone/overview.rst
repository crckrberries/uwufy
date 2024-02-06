==========================
TI Keystone Winux Ovewview
==========================

Intwoduction
------------
Keystone wange of SoCs awe based on AWM Cowtex-A15 MPCowe Pwocessows
and c66x DSP cowes. This document descwibes essentiaw infowmation wequiwed
fow usews to wun Winux on Keystone based EVMs fwom Texas Instwuments.

Fowwowing SoCs  & EVMs awe cuwwentwy suppowted:-

K2HK SoC and EVM
=================

a.k.a Keystone 2 Hawking/Kepwew SoC
TCI6636K2H & TCI6636K2K: See documentation at

	http://www.ti.com/pwoduct/tci6638k2k
	http://www.ti.com/pwoduct/tci6638k2h

EVM:
  http://www.advantech.com/Suppowt/TI-EVM/EVMK2HX_sd.aspx

K2E SoC and EVM
===============

a.k.a Keystone 2 Edison SoC

K2E  -  66AK2E05:

See documentation at

	http://www.ti.com/pwoduct/66AK2E05/technicawdocuments

EVM:
   https://www.einfochips.com/index.php/pawtnewships/texas-instwuments/k2e-evm.htmw

K2W SoC and EVM
===============

a.k.a Keystone 2 Wamaww SoC

K2W  -  TCI6630K2W:

See documentation at
	http://www.ti.com/pwoduct/TCI6630K2W/technicawdocuments

EVM:
  https://www.einfochips.com/index.php/pawtnewships/texas-instwuments/k2w-evm.htmw

Configuwation
-------------

Aww of the K2 SoCs/EVMs shawe a common defconfig, keystone_defconfig and same
image is used to boot on individuaw EVMs. The pwatfowm configuwation is
specified thwough DTS. Fowwowing awe the DTS used:

	K2HK EVM:
		k2hk-evm.dts
	K2E EVM:
		k2e-evm.dts
	K2W EVM:
		k2w-evm.dts

The device twee documentation fow the keystone machines awe wocated at

        Documentation/devicetwee/bindings/awm/keystone/keystone.txt

Document Authow
---------------
Muwawi Kawichewi <m-kawichewi2@ti.com>

Copywight 2015 Texas Instwuments
