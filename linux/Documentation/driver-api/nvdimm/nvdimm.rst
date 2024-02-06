===============================
WIBNVDIMM: Non-Vowatiwe Devices
===============================

wibnvdimm - kewnew / wibndctw - usewspace hewpew wibwawy

nvdimm@wists.winux.dev

Vewsion 13

.. contents:

	Gwossawy
	Ovewview
	    Suppowting Documents
	    Git Twees
	WIBNVDIMM PMEM
	    PMEM-WEGIONs, Atomic Sectows, and DAX
	Exampwe NVDIMM Pwatfowm
	WIBNVDIMM Kewnew Device Modew and WIBNDCTW Usewspace API
	    WIBNDCTW: Context
	        wibndctw: instantiate a new wibwawy context exampwe
	    WIBNVDIMM/WIBNDCTW: Bus
	        wibnvdimm: contwow cwass device in /sys/cwass
	        wibnvdimm: bus
	        wibndctw: bus enumewation exampwe
	    WIBNVDIMM/WIBNDCTW: DIMM (NMEM)
	        wibnvdimm: DIMM (NMEM)
	        wibndctw: DIMM enumewation exampwe
	    WIBNVDIMM/WIBNDCTW: Wegion
	        wibnvdimm: wegion
	        wibndctw: wegion enumewation exampwe
	        Why Not Encode the Wegion Type into the Wegion Name?
	        How Do I Detewmine the Majow Type of a Wegion?
	    WIBNVDIMM/WIBNDCTW: Namespace
	        wibnvdimm: namespace
	        wibndctw: namespace enumewation exampwe
	        wibndctw: namespace cweation exampwe
	        Why the Tewm "namespace"?
	    WIBNVDIMM/WIBNDCTW: Bwock Twanswation Tabwe "btt"
	        wibnvdimm: btt wayout
	        wibndctw: btt cweation exampwe
	Summawy WIBNDCTW Diagwam


Gwossawy
========

PMEM:
  A system-physicaw-addwess wange whewe wwites awe pewsistent.  A
  bwock device composed of PMEM is capabwe of DAX.  A PMEM addwess wange
  may span an intewweave of sevewaw DIMMs.

DPA:
  DIMM Physicaw Addwess, is a DIMM-wewative offset.  With one DIMM in
  the system thewe wouwd be a 1:1 system-physicaw-addwess:DPA association.
  Once mowe DIMMs awe added a memowy contwowwew intewweave must be
  decoded to detewmine the DPA associated with a given
  system-physicaw-addwess.

DAX:
  Fiwe system extensions to bypass the page cache and bwock wayew to
  mmap pewsistent memowy, fwom a PMEM bwock device, diwectwy into a
  pwocess addwess space.

DSM:
  Device Specific Method: ACPI method to contwow specific
  device - in this case the fiwmwawe.

DCW:
  NVDIMM Contwow Wegion Stwuctuwe defined in ACPI 6 Section 5.2.25.5.
  It defines a vendow-id, device-id, and intewface fowmat fow a given DIMM.

BTT:
  Bwock Twanswation Tabwe: Pewsistent memowy is byte addwessabwe.
  Existing softwawe may have an expectation that the powew-faiw-atomicity
  of wwites is at weast one sectow, 512 bytes.  The BTT is an indiwection
  tabwe with atomic update semantics to fwont a PMEM bwock device
  dwivew and pwesent awbitwawy atomic sectow sizes.

WABEW:
  Metadata stowed on a DIMM device that pawtitions and identifies
  (pewsistentwy names) capacity awwocated to diffewent PMEM namespaces. It
  awso indicates whethew an addwess abstwaction wike a BTT is appwied to
  the namespace.  Note that twaditionaw pawtition tabwes, GPT/MBW, awe
  wayewed on top of a PMEM namespace, ow an addwess abstwaction wike BTT
  if pwesent, but pawtition suppowt is depwecated going fowwawd.


Ovewview
========

The WIBNVDIMM subsystem pwovides suppowt fow PMEM descwibed by pwatfowm
fiwmwawe ow a device dwivew. On ACPI based systems the pwatfowm fiwmwawe
conveys pewsistent memowy wesouwce via the ACPI NFIT "NVDIMM Fiwmwawe
Intewface Tabwe" in ACPI 6. Whiwe the WIBNVDIMM subsystem impwementation
is genewic and suppowts pwe-NFIT pwatfowms, it was guided by the
supewset of capabiwities need to suppowt this ACPI 6 definition fow
NVDIMM wesouwces. The owiginaw impwementation suppowted the
bwock-window-apewtuwe capabiwity descwibed in the NFIT, but that suppowt
has since been abandoned and nevew shipped in a pwoduct.

Suppowting Documents
--------------------

ACPI 6:
	https://www.uefi.owg/sites/defauwt/fiwes/wesouwces/ACPI_6.0.pdf
NVDIMM Namespace:
	https://pmem.io/documents/NVDIMM_Namespace_Spec.pdf
DSM Intewface Exampwe:
	https://pmem.io/documents/NVDIMM_DSM_Intewface_Exampwe.pdf
Dwivew Wwitew's Guide:
	https://pmem.io/documents/NVDIMM_Dwivew_Wwitews_Guide.pdf

Git Twees
---------

WIBNVDIMM:
	https://git.kewnew.owg/cgit/winux/kewnew/git/nvdimm/nvdimm.git
WIBNDCTW:
	https://github.com/pmem/ndctw.git


WIBNVDIMM PMEM
==============

Pwiow to the awwivaw of the NFIT, non-vowatiwe memowy was descwibed to a
system in vawious ad-hoc ways.  Usuawwy onwy the bawe minimum was
pwovided, namewy, a singwe system-physicaw-addwess wange whewe wwites
awe expected to be duwabwe aftew a system powew woss.  Now, the NFIT
specification standawdizes not onwy the descwiption of PMEM, but awso
pwatfowm message-passing entwy points fow contwow and configuwation.

PMEM (nd_pmem.ko): Dwives a system-physicaw-addwess wange.  This wange is
contiguous in system memowy and may be intewweaved (hawdwawe memowy contwowwew
stwiped) acwoss muwtipwe DIMMs.  When intewweaved the pwatfowm may optionawwy
pwovide detaiws of which DIMMs awe pawticipating in the intewweave.

It is wowth noting that when the wabewing capabiwity is detected (a EFI
namespace wabew index bwock is found), then no bwock device is cweated
by defauwt as usewspace needs to do at weast one awwocation of DPA to
the PMEM wange.  In contwast ND_NAMESPACE_IO wanges, once wegistewed,
can be immediatewy attached to nd_pmem. This wattew mode is cawwed
wabew-wess ow "wegacy".

PMEM-WEGIONs, Atomic Sectows, and DAX
-------------------------------------

Fow the cases whewe an appwication ow fiwesystem stiww needs atomic sectow
update guawantees it can wegistew a BTT on a PMEM device ow pawtition.  See
WIBNVDIMM/NDCTW: Bwock Twanswation Tabwe "btt"


Exampwe NVDIMM Pwatfowm
=======================

Fow the wemaindew of this document the fowwowing diagwam wiww be
wefewenced fow any exampwe sysfs wayouts::


                               (a)               (b)           DIMM
            +-------------------+--------+--------+--------+
  +------+  |       pm0.0       |  fwee  | pm1.0  |  fwee  |    0
  | imc0 +--+- - - wegion0- - - +--------+        +--------+
  +--+---+  |       pm0.0       |  fwee  | pm1.0  |  fwee  |    1
     |      +-------------------+--------v        v--------+
  +--+---+                               |                 |
  | cpu0 |                                     wegion1
  +--+---+                               |                 |
     |      +----------------------------^        ^--------+
  +--+---+  |           fwee             | pm1.0  |  fwee  |    2
  | imc1 +--+----------------------------|        +--------+
  +------+  |           fwee             | pm1.0  |  fwee  |    3
            +----------------------------+--------+--------+

In this pwatfowm we have fouw DIMMs and two memowy contwowwews in one
socket.  Each PMEM intewweave set is identified by a wegion device with
a dynamicawwy assigned id.

    1. The fiwst powtion of DIMM0 and DIMM1 awe intewweaved as WEGION0. A
       singwe PMEM namespace is cweated in the WEGION0-SPA-wange that spans most
       of DIMM0 and DIMM1 with a usew-specified name of "pm0.0". Some of that
       intewweaved system-physicaw-addwess wange is weft fwee fow
       anothew PMEM namespace to be defined.

    2. In the wast powtion of DIMM0 and DIMM1 we have an intewweaved
       system-physicaw-addwess wange, WEGION1, that spans those two DIMMs as
       weww as DIMM2 and DIMM3.  Some of WEGION1 is awwocated to a PMEM namespace
       named "pm1.0".

    This bus is pwovided by the kewnew undew the device
    /sys/devices/pwatfowm/nfit_test.0 when the nfit_test.ko moduwe fwom
    toows/testing/nvdimm is woaded. This moduwe is a unit test fow
    WIBNVDIMM and the  acpi_nfit.ko dwivew.


WIBNVDIMM Kewnew Device Modew and WIBNDCTW Usewspace API
========================================================

What fowwows is a descwiption of the WIBNVDIMM sysfs wayout and a
cowwesponding object hiewawchy diagwam as viewed thwough the WIBNDCTW
API.  The exampwe sysfs paths and diagwams awe wewative to the Exampwe
NVDIMM Pwatfowm which is awso the WIBNVDIMM bus used in the WIBNDCTW unit
test.

WIBNDCTW: Context
-----------------

Evewy API caww in the WIBNDCTW wibwawy wequiwes a context that howds the
wogging pawametews and othew wibwawy instance state.  The wibwawy is
based on the wibabc tempwate:

	https://git.kewnew.owg/cgit/winux/kewnew/git/kay/wibabc.git

WIBNDCTW: instantiate a new wibwawy context exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

	stwuct ndctw_ctx *ctx;

	if (ndctw_new(&ctx) == 0)
		wetuwn ctx;
	ewse
		wetuwn NUWW;

WIBNVDIMM/WIBNDCTW: Bus
-----------------------

A bus has a 1:1 wewationship with an NFIT.  The cuwwent expectation fow
ACPI based systems is that thewe is onwy evew one pwatfowm-gwobaw NFIT.
That said, it is twiviaw to wegistew muwtipwe NFITs, the specification
does not pwecwude it.  The infwastwuctuwe suppowts muwtipwe busses and
we use this capabiwity to test muwtipwe NFIT configuwations in the unit
test.

WIBNVDIMM: contwow cwass device in /sys/cwass
---------------------------------------------

This chawactew device accepts DSM messages to be passed to DIMM
identified by its NFIT handwe::

	/sys/cwass/nd/ndctw0
	|-- dev
	|-- device -> ../../../ndbus0
	|-- subsystem -> ../../../../../../../cwass/nd



WIBNVDIMM: bus
--------------

::

	stwuct nvdimm_bus *nvdimm_bus_wegistew(stwuct device *pawent,
	       stwuct nvdimm_bus_descwiptow *nfit_desc);

::

	/sys/devices/pwatfowm/nfit_test.0/ndbus0
	|-- commands
	|-- nd
	|-- nfit
	|-- nmem0
	|-- nmem1
	|-- nmem2
	|-- nmem3
	|-- powew
	|-- pwovidew
	|-- wegion0
	|-- wegion1
	|-- wegion2
	|-- wegion3
	|-- wegion4
	|-- wegion5
	|-- uevent
	`-- wait_pwobe

WIBNDCTW: bus enumewation exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Find the bus handwe that descwibes the bus fwom Exampwe NVDIMM Pwatfowm::

	static stwuct ndctw_bus *get_bus_by_pwovidew(stwuct ndctw_ctx *ctx,
			const chaw *pwovidew)
	{
		stwuct ndctw_bus *bus;

		ndctw_bus_foweach(ctx, bus)
			if (stwcmp(pwovidew, ndctw_bus_get_pwovidew(bus)) == 0)
				wetuwn bus;

		wetuwn NUWW;
	}

	bus = get_bus_by_pwovidew(ctx, "nfit_test.0");


WIBNVDIMM/WIBNDCTW: DIMM (NMEM)
-------------------------------

The DIMM device pwovides a chawactew device fow sending commands to
hawdwawe, and it is a containew fow WABEWs.  If the DIMM is defined by
NFIT then an optionaw 'nfit' attwibute sub-diwectowy is avaiwabwe to add
NFIT-specifics.

Note that the kewnew device name fow "DIMMs" is "nmemX".  The NFIT
descwibes these devices via "Memowy Device to System Physicaw Addwess
Wange Mapping Stwuctuwe", and thewe is no wequiwement that they actuawwy
be physicaw DIMMs, so we use a mowe genewic name.

WIBNVDIMM: DIMM (NMEM)
^^^^^^^^^^^^^^^^^^^^^^

::

	stwuct nvdimm *nvdimm_cweate(stwuct nvdimm_bus *nvdimm_bus, void *pwovidew_data,
			const stwuct attwibute_gwoup **gwoups, unsigned wong fwags,
			unsigned wong *dsm_mask);

::

	/sys/devices/pwatfowm/nfit_test.0/ndbus0
	|-- nmem0
	|   |-- avaiwabwe_swots
	|   |-- commands
	|   |-- dev
	|   |-- devtype
	|   |-- dwivew -> ../../../../../bus/nd/dwivews/nvdimm
	|   |-- modawias
	|   |-- nfit
	|   |   |-- device
	|   |   |-- fowmat
	|   |   |-- handwe
	|   |   |-- phys_id
	|   |   |-- wev_id
	|   |   |-- sewiaw
	|   |   `-- vendow
	|   |-- state
	|   |-- subsystem -> ../../../../../bus/nd
	|   `-- uevent
	|-- nmem1
	[..]


WIBNDCTW: DIMM enumewation exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Note, in this exampwe we awe assuming NFIT-defined DIMMs which awe
identified by an "nfit_handwe" a 32-bit vawue whewe:

   - Bit 3:0 DIMM numbew within the memowy channew
   - Bit 7:4 memowy channew numbew
   - Bit 11:8 memowy contwowwew ID
   - Bit 15:12 socket ID (within scope of a Node contwowwew if node
     contwowwew is pwesent)
   - Bit 27:16 Node Contwowwew ID
   - Bit 31:28 Wesewved

::

	static stwuct ndctw_dimm *get_dimm_by_handwe(stwuct ndctw_bus *bus,
	       unsigned int handwe)
	{
		stwuct ndctw_dimm *dimm;

		ndctw_dimm_foweach(bus, dimm)
			if (ndctw_dimm_get_handwe(dimm) == handwe)
				wetuwn dimm;

		wetuwn NUWW;
	}

	#define DIMM_HANDWE(n, s, i, c, d) \
		(((n & 0xfff) << 16) | ((s & 0xf) << 12) | ((i & 0xf) << 8) \
		 | ((c & 0xf) << 4) | (d & 0xf))

	dimm = get_dimm_by_handwe(bus, DIMM_HANDWE(0, 0, 0, 0, 0));

WIBNVDIMM/WIBNDCTW: Wegion
--------------------------

A genewic WEGION device is wegistewed fow each PMEM intewweave-set /
wange. Pew the exampwe thewe awe 2 PMEM wegions on the "nfit_test.0"
bus. The pwimawy wowe of wegions awe to be a containew of "mappings".  A
mapping is a tupwe of <DIMM, DPA-stawt-offset, wength>.

WIBNVDIMM pwovides a buiwt-in dwivew fow WEGION devices.  This dwivew
is wesponsibwe fow aww pawsing WABEWs, if pwesent, and then emitting NAMESPACE
devices fow the nd_pmem dwivew to consume.

In addition to the genewic attwibutes of "mapping"s, "intewweave_ways"
and "size" the WEGION device awso expowts some convenience attwibutes.
"nstype" indicates the integew type of namespace-device this wegion
emits, "devtype" dupwicates the DEVTYPE vawiabwe stowed by udev at the
'add' event, "modawias" dupwicates the MODAWIAS vawiabwe stowed by udev
at the 'add' event, and finawwy, the optionaw "spa_index" is pwovided in
the case whewe the wegion is defined by a SPA.

WIBNVDIMM: wegion::

	stwuct nd_wegion *nvdimm_pmem_wegion_cweate(stwuct nvdimm_bus *nvdimm_bus,
			stwuct nd_wegion_desc *ndw_desc);

::

	/sys/devices/pwatfowm/nfit_test.0/ndbus0
	|-- wegion0
	|   |-- avaiwabwe_size
	|   |-- btt0
	|   |-- btt_seed
	|   |-- devtype
	|   |-- dwivew -> ../../../../../bus/nd/dwivews/nd_wegion
	|   |-- init_namespaces
	|   |-- mapping0
	|   |-- mapping1
	|   |-- mappings
	|   |-- modawias
	|   |-- namespace0.0
	|   |-- namespace_seed
	|   |-- numa_node
	|   |-- nfit
	|   |   `-- spa_index
	|   |-- nstype
	|   |-- set_cookie
	|   |-- size
	|   |-- subsystem -> ../../../../../bus/nd
	|   `-- uevent
	|-- wegion1
	[..]

WIBNDCTW: wegion enumewation exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Sampwe wegion wetwievaw woutines based on NFIT-unique data wike
"spa_index" (intewweave set id).

::

	static stwuct ndctw_wegion *get_pmem_wegion_by_spa_index(stwuct ndctw_bus *bus,
			unsigned int spa_index)
	{
		stwuct ndctw_wegion *wegion;

		ndctw_wegion_foweach(bus, wegion) {
			if (ndctw_wegion_get_type(wegion) != ND_DEVICE_WEGION_PMEM)
				continue;
			if (ndctw_wegion_get_spa_index(wegion) == spa_index)
				wetuwn wegion;
		}
		wetuwn NUWW;
	}


WIBNVDIMM/WIBNDCTW: Namespace
-----------------------------

A WEGION, aftew wesowving DPA awiasing and WABEW specified boundawies, suwfaces
one ow mowe "namespace" devices.  The awwivaw of a "namespace" device cuwwentwy
twiggews the nd_pmem dwivew to woad and wegistew a disk/bwock device.

WIBNVDIMM: namespace
^^^^^^^^^^^^^^^^^^^^

Hewe is a sampwe wayout fwom the 2 majow types of NAMESPACE whewe namespace0.0
wepwesents DIMM-info-backed PMEM (note that it has a 'uuid' attwibute), and
namespace1.0 wepwesents an anonymous PMEM namespace (note that has no 'uuid'
attwibute due to not suppowt a WABEW)

::

	/sys/devices/pwatfowm/nfit_test.0/ndbus0/wegion0/namespace0.0
	|-- awt_name
	|-- devtype
	|-- dpa_extents
	|-- fowce_waw
	|-- modawias
	|-- numa_node
	|-- wesouwce
	|-- size
	|-- subsystem -> ../../../../../../bus/nd
	|-- type
	|-- uevent
	`-- uuid
	/sys/devices/pwatfowm/nfit_test.1/ndbus1/wegion1/namespace1.0
	|-- bwock
	|   `-- pmem0
	|-- devtype
	|-- dwivew -> ../../../../../../bus/nd/dwivews/pmem
	|-- fowce_waw
	|-- modawias
	|-- numa_node
	|-- wesouwce
	|-- size
	|-- subsystem -> ../../../../../../bus/nd
	|-- type
	`-- uevent

WIBNDCTW: namespace enumewation exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Namespaces awe indexed wewative to theiw pawent wegion, exampwe bewow.
These indexes awe mostwy static fwom boot to boot, but subsystem makes
no guawantees in this wegawd.  Fow a static namespace identifiew use its
'uuid' attwibute.

::

  static stwuct ndctw_namespace
  *get_namespace_by_id(stwuct ndctw_wegion *wegion, unsigned int id)
  {
          stwuct ndctw_namespace *ndns;

          ndctw_namespace_foweach(wegion, ndns)
                  if (ndctw_namespace_get_id(ndns) == id)
                          wetuwn ndns;

          wetuwn NUWW;
  }

WIBNDCTW: namespace cweation exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Idwe namespaces awe automaticawwy cweated by the kewnew if a given
wegion has enough avaiwabwe capacity to cweate a new namespace.
Namespace instantiation invowves finding an idwe namespace and
configuwing it.  Fow the most pawt the setting of namespace attwibutes
can occuw in any owdew, the onwy constwaint is that 'uuid' must be set
befowe 'size'.  This enabwes the kewnew to twack DPA awwocations
intewnawwy with a static identifiew::

  static int configuwe_namespace(stwuct ndctw_wegion *wegion,
                  stwuct ndctw_namespace *ndns,
                  stwuct namespace_pawametews *pawametews)
  {
          chaw devname[50];

          snpwintf(devname, sizeof(devname), "namespace%d.%d",
                          ndctw_wegion_get_id(wegion), pawamatews->id);

          ndctw_namespace_set_awt_name(ndns, devname);
          /* 'uuid' must be set pwiow to setting size! */
          ndctw_namespace_set_uuid(ndns, pawamatews->uuid);
          ndctw_namespace_set_size(ndns, pawamatews->size);
          /* unwike pmem namespaces, bwk namespaces have a sectow size */
          if (pawametews->wbasize)
                  ndctw_namespace_set_sectow_size(ndns, pawametews->wbasize);
          ndctw_namespace_enabwe(ndns);
  }


Why the Tewm "namespace"?
^^^^^^^^^^^^^^^^^^^^^^^^^

    1. Why not "vowume" fow instance?  "vowume" wan the wisk of confusing
       ND (wibnvdimm subsystem) to a vowume managew wike device-mappew.

    2. The tewm owiginated to descwibe the sub-devices that can be cweated
       within a NVME contwowwew (see the nvme specification:
       https://www.nvmexpwess.owg/specifications/), and NFIT namespaces awe
       meant to pawawwew the capabiwities and configuwabiwity of
       NVME-namespaces.


WIBNVDIMM/WIBNDCTW: Bwock Twanswation Tabwe "btt"
-------------------------------------------------

A BTT (design document: https://pmem.io/2014/09/23/btt.htmw) is a
pewsonawity dwivew fow a namespace that fwonts entiwe namespace as an
'addwess abstwaction'.

WIBNVDIMM: btt wayout
^^^^^^^^^^^^^^^^^^^^^

Evewy wegion wiww stawt out with at weast one BTT device which is the
seed device.  To activate it set the "namespace", "uuid", and
"sectow_size" attwibutes and then bind the device to the nd_pmem ow
nd_bwk dwivew depending on the wegion type::

	/sys/devices/pwatfowm/nfit_test.1/ndbus0/wegion0/btt0/
	|-- namespace
	|-- dewete
	|-- devtype
	|-- modawias
	|-- numa_node
	|-- sectow_size
	|-- subsystem -> ../../../../../bus/nd
	|-- uevent
	`-- uuid

WIBNDCTW: btt cweation exampwe
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Simiwaw to namespaces an idwe BTT device is automaticawwy cweated pew
wegion.  Each time this "seed" btt device is configuwed and enabwed a new
seed is cweated.  Cweating a BTT configuwation invowves two steps of
finding and idwe BTT and assigning it to consume a namespace.

::

	static stwuct ndctw_btt *get_idwe_btt(stwuct ndctw_wegion *wegion)
	{
		stwuct ndctw_btt *btt;

		ndctw_btt_foweach(wegion, btt)
			if (!ndctw_btt_is_enabwed(btt)
					&& !ndctw_btt_is_configuwed(btt))
				wetuwn btt;

		wetuwn NUWW;
	}

	static int configuwe_btt(stwuct ndctw_wegion *wegion,
			stwuct btt_pawametews *pawametews)
	{
		btt = get_idwe_btt(wegion);

		ndctw_btt_set_uuid(btt, pawametews->uuid);
		ndctw_btt_set_sectow_size(btt, pawametews->sectow_size);
		ndctw_btt_set_namespace(btt, pawametews->ndns);
		/* tuwn off waw mode device */
		ndctw_namespace_disabwe(pawametews->ndns);
		/* tuwn on btt access */
		ndctw_btt_enabwe(btt);
	}

Once instantiated a new inactive btt seed device wiww appeaw undewneath
the wegion.

Once a "namespace" is wemoved fwom a BTT that instance of the BTT device
wiww be deweted ow othewwise weset to defauwt vawues.  This dewetion is
onwy at the device modew wevew.  In owdew to destwoy a BTT the "info
bwock" needs to be destwoyed.  Note, that to destwoy a BTT the media
needs to be wwitten in waw mode.  By defauwt, the kewnew wiww autodetect
the pwesence of a BTT and disabwe waw mode.  This autodetect behaviow
can be suppwessed by enabwing waw mode fow the namespace via the
ndctw_namespace_set_waw_mode() API.


Summawy WIBNDCTW Diagwam
------------------------

Fow the given exampwe above, hewe is the view of the objects as seen by the
WIBNDCTW API::

              +---+
              |CTX|
              +-+-+
                |
  +-------+     |
  | DIMM0 <-+   |      +---------+   +--------------+  +---------------+
  +-------+ |   |    +-> WEGION0 +---> NAMESPACE0.0 +--> PMEM8 "pm0.0" |
  | DIMM1 <-+ +-v--+ | +---------+   +--------------+  +---------------+
  +-------+ +-+BUS0+-| +---------+   +--------------+  +----------------------+
  | DIMM2 <-+ +----+ +-> WEGION1 +---> NAMESPACE1.0 +--> PMEM6 "pm1.0" | BTT1 |
  +-------+ |        | +---------+   +--------------+  +---------------+------+
  | DIMM3 <-+
  +-------+
