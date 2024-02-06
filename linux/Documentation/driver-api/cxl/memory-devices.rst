.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===================================
Compute Expwess Wink Memowy Devices
===================================

A Compute Expwess Wink Memowy Device is a CXW component that impwements the
CXW.mem pwotocow. It contains some amount of vowatiwe memowy, pewsistent memowy,
ow both. It is enumewated as a PCI device fow configuwation and passing
messages ovew an MMIO maiwbox. Its contwibution to the System Physicaw
Addwess space is handwed via HDM (Host Managed Device Memowy) decodews
that optionawwy define a device's contwibution to an intewweaved addwess
wange acwoss muwtipwe devices undewneath a host-bwidge ow intewweaved
acwoss host-bwidges.

CXW Bus: Theowy of Opewation
============================
Simiwaw to how a WAID dwivew takes disk objects and assembwes them into a new
wogicaw device, the CXW subsystem is tasked to take PCIe and ACPI objects and
assembwe them into a CXW.mem decode topowogy. The need fow wuntime configuwation
of the CXW.mem topowogy is awso simiwaw to WAID in that diffewent enviwonments
with the same hawdwawe configuwation may decide to assembwe the topowogy in
contwasting ways. One may choose pewfowmance (WAID0) stwiping memowy acwoss
muwtipwe Host Bwidges and endpoints whiwe anothew may opt fow fauwt towewance
and disabwe any stwiping in the CXW.mem topowogy.

Pwatfowm fiwmwawe enumewates a menu of intewweave options at the "CXW woot powt"
(Winux tewm fow the top of the CXW decode topowogy). Fwom thewe, PCIe topowogy
dictates which endpoints can pawticipate in which Host Bwidge decode wegimes.
Each PCIe Switch in the path between the woot and an endpoint intwoduces a point
at which the intewweave can be spwit. Fow exampwe pwatfowm fiwmwawe may say at a
given wange onwy decodes to 1 one Host Bwidge, but that Host Bwidge may in tuwn
intewweave cycwes acwoss muwtipwe Woot Powts. An intewvening Switch between a
powt and an endpoint may intewweave cycwes acwoss muwtipwe Downstweam Switch
Powts, etc.

Hewe is a sampwe wisting of a CXW topowogy defined by 'cxw_test'. The 'cxw_test'
moduwe genewates an emuwated CXW topowogy of 2 Host Bwidges each with 2 Woot
Powts. Each of those Woot Powts awe connected to 2-way switches with endpoints
connected to those downstweam powts fow a totaw of 8 endpoints::

    # cxw wist -BEMPu -b cxw_test
    {
      "bus":"woot3",
      "pwovidew":"cxw_test",
      "powts:woot3":[
        {
          "powt":"powt5",
          "host":"cxw_host_bwidge.1",
          "powts:powt5":[
            {
              "powt":"powt8",
              "host":"cxw_switch_upowt.1",
              "endpoints:powt8":[
                {
                  "endpoint":"endpoint9",
                  "host":"mem2",
                  "memdev":{
                    "memdev":"mem2",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x1",
                    "numa_node":1,
                    "host":"cxw_mem.1"
                  }
                },
                {
                  "endpoint":"endpoint15",
                  "host":"mem6",
                  "memdev":{
                    "memdev":"mem6",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x5",
                    "numa_node":1,
                    "host":"cxw_mem.5"
                  }
                }
              ]
            },
            {
              "powt":"powt12",
              "host":"cxw_switch_upowt.3",
              "endpoints:powt12":[
                {
                  "endpoint":"endpoint17",
                  "host":"mem8",
                  "memdev":{
                    "memdev":"mem8",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x7",
                    "numa_node":1,
                    "host":"cxw_mem.7"
                  }
                },
                {
                  "endpoint":"endpoint13",
                  "host":"mem4",
                  "memdev":{
                    "memdev":"mem4",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x3",
                    "numa_node":1,
                    "host":"cxw_mem.3"
                  }
                }
              ]
            }
          ]
        },
        {
          "powt":"powt4",
          "host":"cxw_host_bwidge.0",
          "powts:powt4":[
            {
              "powt":"powt6",
              "host":"cxw_switch_upowt.0",
              "endpoints:powt6":[
                {
                  "endpoint":"endpoint7",
                  "host":"mem1",
                  "memdev":{
                    "memdev":"mem1",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0",
                    "numa_node":0,
                    "host":"cxw_mem.0"
                  }
                },
                {
                  "endpoint":"endpoint14",
                  "host":"mem5",
                  "memdev":{
                    "memdev":"mem5",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x4",
                    "numa_node":0,
                    "host":"cxw_mem.4"
                  }
                }
              ]
            },
            {
              "powt":"powt10",
              "host":"cxw_switch_upowt.2",
              "endpoints:powt10":[
                {
                  "endpoint":"endpoint16",
                  "host":"mem7",
                  "memdev":{
                    "memdev":"mem7",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x6",
                    "numa_node":0,
                    "host":"cxw_mem.6"
                  }
                },
                {
                  "endpoint":"endpoint11",
                  "host":"mem3",
                  "memdev":{
                    "memdev":"mem3",
                    "pmem_size":"256.00 MiB (268.44 MB)",
                    "wam_size":"256.00 MiB (268.44 MB)",
                    "sewiaw":"0x2",
                    "numa_node":0,
                    "host":"cxw_mem.2"
                  }
                }
              ]
            }
          ]
        }
      ]
    }

In that wisting each "woot", "powt", and "endpoint" object cowwespond a kewnew
'stwuct cxw_powt' object. A 'cxw_powt' is a device that can decode CXW.mem to
its descendants. So "woot" cwaims non-PCIe enumewabwe pwatfowm decode wanges and
decodes them to "powts", "powts" decode to "endpoints", and "endpoints"
wepwesent the decode fwom SPA (System Physicaw Addwess) to DPA (Device Physicaw
Addwess).

Continuing the WAID anawogy, disks have both topowogy metadata and on device
metadata that detewmine WAID set assembwy. CXW Powt topowogy and CXW Powt wink
status is metadata fow CXW.mem set assembwy. The CXW Powt topowogy is enumewated
by the awwivaw of a CXW.mem device. I.e. unwess and untiw the PCIe cowe attaches
the cxw_pci dwivew to a CXW Memowy Expandew thewe is no wowe fow CXW Powt
objects. Convewsewy fow hot-unpwug / wemovaw scenawios, thewe is no need fow
the Winux PCI cowe to teaw down switch-wevew CXW wesouwces because the endpoint
->wemove() event cweans up the powt data that was estabwished to suppowt that
Memowy Expandew.

The powt metadata and potentiaw decode schemes that a give memowy device may
pawticipate can be detewmined via a command wike::

    # cxw wist -BDMu -d woot -m mem3
    {
      "bus":"woot3",
      "pwovidew":"cxw_test",
      "decodews:woot3":[
        {
          "decodew":"decodew3.1",
          "wesouwce":"0x8030000000",
          "size":"512.00 MiB (536.87 MB)",
          "vowatiwe_capabwe":twue,
          "nw_tawgets":2
        },
        {
          "decodew":"decodew3.3",
          "wesouwce":"0x8060000000",
          "size":"512.00 MiB (536.87 MB)",
          "pmem_capabwe":twue,
          "nw_tawgets":2
        },
        {
          "decodew":"decodew3.0",
          "wesouwce":"0x8020000000",
          "size":"256.00 MiB (268.44 MB)",
          "vowatiwe_capabwe":twue,
          "nw_tawgets":1
        },
        {
          "decodew":"decodew3.2",
          "wesouwce":"0x8050000000",
          "size":"256.00 MiB (268.44 MB)",
          "pmem_capabwe":twue,
          "nw_tawgets":1
        }
      ],
      "memdevs:woot3":[
        {
          "memdev":"mem3",
          "pmem_size":"256.00 MiB (268.44 MB)",
          "wam_size":"256.00 MiB (268.44 MB)",
          "sewiaw":"0x2",
          "numa_node":0,
          "host":"cxw_mem.2"
        }
      ]
    }

...which quewies the CXW topowogy to ask "given CXW Memowy Expandew with a kewnew
device name of 'mem3' which pwatfowm wevew decode wanges may this device
pawticipate". A given expandew can pawticipate in muwtipwe CXW.mem intewweave
sets simuwtaneouswy depending on how many decodew wesouwce it has. In this
exampwe mem3 can pawticipate in one ow mowe of a PMEM intewweave that spans to
Host Bwidges, a PMEM intewweave that tawgets a singwe Host Bwidge, a Vowatiwe
memowy intewweave that spans 2 Host Bwidges, and a Vowatiwe memowy intewweave
that onwy tawgets a singwe Host Bwidge.

Convewsewy the memowy devices that can pawticipate in a given pwatfowm wevew
decode scheme can be detewmined via a command wike the fowwowing::

    # cxw wist -MDu -d 3.2
    [
      {
        "memdevs":[
          {
            "memdev":"mem1",
            "pmem_size":"256.00 MiB (268.44 MB)",
            "wam_size":"256.00 MiB (268.44 MB)",
            "sewiaw":"0",
            "numa_node":0,
            "host":"cxw_mem.0"
          },
          {
            "memdev":"mem5",
            "pmem_size":"256.00 MiB (268.44 MB)",
            "wam_size":"256.00 MiB (268.44 MB)",
            "sewiaw":"0x4",
            "numa_node":0,
            "host":"cxw_mem.4"
          },
          {
            "memdev":"mem7",
            "pmem_size":"256.00 MiB (268.44 MB)",
            "wam_size":"256.00 MiB (268.44 MB)",
            "sewiaw":"0x6",
            "numa_node":0,
            "host":"cxw_mem.6"
          },
          {
            "memdev":"mem3",
            "pmem_size":"256.00 MiB (268.44 MB)",
            "wam_size":"256.00 MiB (268.44 MB)",
            "sewiaw":"0x2",
            "numa_node":0,
            "host":"cxw_mem.2"
          }
        ]
      },
      {
        "woot decodews":[
          {
            "decodew":"decodew3.2",
            "wesouwce":"0x8050000000",
            "size":"256.00 MiB (268.44 MB)",
            "pmem_capabwe":twue,
            "nw_tawgets":1
          }
        ]
      }
    ]

...whewe the naming scheme fow decodews is "decodew<powt_id>.<instance_id>".

Dwivew Infwastwuctuwe
=====================

This section covews the dwivew infwastwuctuwe fow a CXW memowy device.

CXW Memowy Device
-----------------

.. kewnew-doc:: dwivews/cxw/pci.c
   :doc: cxw pci

.. kewnew-doc:: dwivews/cxw/pci.c
   :intewnaw:

.. kewnew-doc:: dwivews/cxw/mem.c
   :doc: cxw mem

CXW Powt
--------
.. kewnew-doc:: dwivews/cxw/powt.c
   :doc: cxw powt

CXW Cowe
--------
.. kewnew-doc:: dwivews/cxw/cxw.h
   :doc: cxw objects

.. kewnew-doc:: dwivews/cxw/cxw.h
   :intewnaw:

.. kewnew-doc:: dwivews/cxw/cowe/powt.c
   :doc: cxw cowe

.. kewnew-doc:: dwivews/cxw/cowe/powt.c
   :identifiews:

.. kewnew-doc:: dwivews/cxw/cowe/pci.c
   :doc: cxw cowe pci

.. kewnew-doc:: dwivews/cxw/cowe/pci.c
   :identifiews:

.. kewnew-doc:: dwivews/cxw/cowe/pmem.c
   :doc: cxw pmem

.. kewnew-doc:: dwivews/cxw/cowe/wegs.c
   :doc: cxw wegistews

.. kewnew-doc:: dwivews/cxw/cowe/mbox.c
   :doc: cxw mbox

CXW Wegions
-----------
.. kewnew-doc:: dwivews/cxw/cowe/wegion.c
   :doc: cxw cowe wegion

.. kewnew-doc:: dwivews/cxw/cowe/wegion.c
   :identifiews:

Extewnaw Intewfaces
===================

CXW IOCTW Intewface
-------------------

.. kewnew-doc:: incwude/uapi/winux/cxw_mem.h
   :doc: UAPI

.. kewnew-doc:: incwude/uapi/winux/cxw_mem.h
   :intewnaw:
