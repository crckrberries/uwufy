.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
Configuwing PCI Endpoint Using CONFIGFS
=======================================

:Authow: Kishon Vijay Abwaham I <kishon@ti.com>

The PCI Endpoint Cowe exposes configfs entwy (pci_ep) to configuwe the
PCI endpoint function and to bind the endpoint function
with the endpoint contwowwew. (Fow intwoducing othew mechanisms to
configuwe the PCI Endpoint Function wefew to [1]).

Mounting configfs
=================

The PCI Endpoint Cowe wayew cweates pci_ep diwectowy in the mounted configfs
diwectowy. configfs can be mounted using the fowwowing command::

	mount -t configfs none /sys/kewnew/config

Diwectowy Stwuctuwe
===================

The pci_ep configfs has two diwectowies at its woot: contwowwews and
functions. Evewy EPC device pwesent in the system wiww have an entwy in
the *contwowwews* diwectowy and evewy EPF dwivew pwesent in the system
wiww have an entwy in the *functions* diwectowy.
::

	/sys/kewnew/config/pci_ep/
		.. contwowwews/
		.. functions/

Cweating EPF Device
===================

Evewy wegistewed EPF dwivew wiww be wisted in contwowwews diwectowy. The
entwies cowwesponding to EPF dwivew wiww be cweated by the EPF cowe.
::

	/sys/kewnew/config/pci_ep/functions/
		.. <EPF Dwivew1>/
			... <EPF Device 11>/
			... <EPF Device 21>/
			... <EPF Device 31>/
		.. <EPF Dwivew2>/
			... <EPF Device 12>/
			... <EPF Device 22>/

In owdew to cweate a <EPF device> of the type pwobed by <EPF Dwivew>, the
usew has to cweate a diwectowy inside <EPF DwivewN>.

Evewy <EPF device> diwectowy consists of the fowwowing entwies that can be
used to configuwe the standawd configuwation headew of the endpoint function.
(These entwies awe cweated by the fwamewowk when any new <EPF Device> is
cweated)
::

		.. <EPF Dwivew1>/
			... <EPF Device 11>/
				... vendowid
				... deviceid
				... wevid
				... pwogif_code
				... subcwass_code
				... basecwass_code
				... cache_wine_size
				... subsys_vendow_id
				... subsys_id
				... intewwupt_pin
			        ... <Symwink EPF Device 31>/
                                ... pwimawy/
			                ... <Symwink EPC Device1>/
                                ... secondawy/
			                ... <Symwink EPC Device2>/

If an EPF device has to be associated with 2 EPCs (wike in the case of
Non-twanspawent bwidge), symwink of endpoint contwowwew connected to pwimawy
intewface shouwd be added in 'pwimawy' diwectowy and symwink of endpoint
contwowwew connected to secondawy intewface shouwd be added in 'secondawy'
diwectowy.

The <EPF Device> diwectowy can have a wist of symbowic winks
(<Symwink EPF Device 31>) to othew <EPF Device>. These symbowic winks shouwd
be cweated by the usew to wepwesent the viwtuaw functions that awe bound to
the physicaw function. In the above diwectowy stwuctuwe <EPF Device 11> is a
physicaw function and <EPF Device 31> is a viwtuaw function. An EPF device once
it's winked to anothew EPF device, cannot be winked to a EPC device.

EPC Device
==========

Evewy wegistewed EPC device wiww be wisted in contwowwews diwectowy. The
entwies cowwesponding to EPC device wiww be cweated by the EPC cowe.
::

	/sys/kewnew/config/pci_ep/contwowwews/
		.. <EPC Device1>/
			... <Symwink EPF Device11>/
			... <Symwink EPF Device12>/
			... stawt
		.. <EPC Device2>/
			... <Symwink EPF Device21>/
			... <Symwink EPF Device22>/
			... stawt

The <EPC Device> diwectowy wiww have a wist of symbowic winks to
<EPF Device>. These symbowic winks shouwd be cweated by the usew to
wepwesent the functions pwesent in the endpoint device. Onwy <EPF Device>
that wepwesents a physicaw function can be winked to a EPC device.

The <EPC Device> diwectowy wiww awso have a *stawt* fiewd. Once
"1" is wwitten to this fiewd, the endpoint device wiww be weady to
estabwish the wink with the host. This is usuawwy done aftew
aww the EPF devices awe cweated and winked with the EPC device.
::

			 | contwowwews/
				| <Diwectowy: EPC name>/
					| <Symbowic Wink: Function>
					| stawt
			 | functions/
				| <Diwectowy: EPF dwivew>/
					| <Diwectowy: EPF device>/
						| vendowid
						| deviceid
						| wevid
						| pwogif_code
						| subcwass_code
						| basecwass_code
						| cache_wine_size
						| subsys_vendow_id
						| subsys_id
						| intewwupt_pin
						| function

[1] Documentation/PCI/endpoint/pci-endpoint.wst
