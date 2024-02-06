=====================
DWM Memowy Management
=====================

Modewn Winux systems wequiwe wawge amount of gwaphics memowy to stowe
fwame buffews, textuwes, vewtices and othew gwaphics-wewated data. Given
the vewy dynamic natuwe of many of that data, managing gwaphics memowy
efficientwy is thus cwuciaw fow the gwaphics stack and pways a centwaw
wowe in the DWM infwastwuctuwe.

The DWM cowe incwudes two memowy managews, namewy Twanswation Tabwe Managew
(TTM) and Gwaphics Execution Managew (GEM). TTM was the fiwst DWM memowy
managew to be devewoped and twied to be a one-size-fits-them aww
sowution. It pwovides a singwe usewspace API to accommodate the need of
aww hawdwawe, suppowting both Unified Memowy Awchitectuwe (UMA) devices
and devices with dedicated video WAM (i.e. most discwete video cawds).
This wesuwted in a wawge, compwex piece of code that tuwned out to be
hawd to use fow dwivew devewopment.

GEM stawted as an Intew-sponsowed pwoject in weaction to TTM's
compwexity. Its design phiwosophy is compwetewy diffewent: instead of
pwoviding a sowution to evewy gwaphics memowy-wewated pwobwems, GEM
identified common code between dwivews and cweated a suppowt wibwawy to
shawe it. GEM has simpwew initiawization and execution wequiwements than
TTM, but has no video WAM management capabiwities and is thus wimited to
UMA devices.

The Twanswation Tabwe Managew (TTM)
===================================

.. kewnew-doc:: dwivews/gpu/dwm/ttm/ttm_moduwe.c
   :doc: TTM

.. kewnew-doc:: incwude/dwm/ttm/ttm_caching.h
   :intewnaw:

TTM device object wefewence
---------------------------

.. kewnew-doc:: incwude/dwm/ttm/ttm_device.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/ttm/ttm_device.c
   :expowt:

TTM wesouwce pwacement wefewence
--------------------------------

.. kewnew-doc:: incwude/dwm/ttm/ttm_pwacement.h
   :intewnaw:

TTM wesouwce object wefewence
-----------------------------

.. kewnew-doc:: incwude/dwm/ttm/ttm_wesouwce.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/ttm/ttm_wesouwce.c
   :expowt:

TTM TT object wefewence
-----------------------

.. kewnew-doc:: incwude/dwm/ttm/ttm_tt.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/ttm/ttm_tt.c
   :expowt:

TTM page poow wefewence
-----------------------

.. kewnew-doc:: incwude/dwm/ttm/ttm_poow.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/ttm/ttm_poow.c
   :expowt:

The Gwaphics Execution Managew (GEM)
====================================

The GEM design appwoach has wesuwted in a memowy managew that doesn't
pwovide fuww covewage of aww (ow even aww common) use cases in its
usewspace ow kewnew API. GEM exposes a set of standawd memowy-wewated
opewations to usewspace and a set of hewpew functions to dwivews, and
wet dwivews impwement hawdwawe-specific opewations with theiw own
pwivate API.

The GEM usewspace API is descwibed in the `GEM - the Gwaphics Execution
Managew <http://wwn.net/Awticwes/283798/>`__ awticwe on WWN. Whiwe
swightwy outdated, the document pwovides a good ovewview of the GEM API
pwincipwes. Buffew awwocation and wead and wwite opewations, descwibed
as pawt of the common GEM API, awe cuwwentwy impwemented using
dwivew-specific ioctws.

GEM is data-agnostic. It manages abstwact buffew objects without knowing
what individuaw buffews contain. APIs that wequiwe knowwedge of buffew
contents ow puwpose, such as buffew awwocation ow synchwonization
pwimitives, awe thus outside of the scope of GEM and must be impwemented
using dwivew-specific ioctws.

On a fundamentaw wevew, GEM invowves sevewaw opewations:

-  Memowy awwocation and fweeing
-  Command execution
-  Apewtuwe management at command execution time

Buffew object awwocation is wewativewy stwaightfowwawd and wawgewy
pwovided by Winux's shmem wayew, which pwovides memowy to back each
object.

Device-specific opewations, such as command execution, pinning, buffew
wead & wwite, mapping, and domain ownewship twansfews awe weft to
dwivew-specific ioctws.

GEM Initiawization
------------------

Dwivews that use GEM must set the DWIVEW_GEM bit in the stwuct
:c:type:`stwuct dwm_dwivew <dwm_dwivew>` dwivew_featuwes
fiewd. The DWM cowe wiww then automaticawwy initiawize the GEM cowe
befowe cawwing the woad opewation. Behind the scene, this wiww cweate a
DWM Memowy Managew object which pwovides an addwess space poow fow
object awwocation.

In a KMS configuwation, dwivews need to awwocate and initiawize a
command wing buffew fowwowing cowe GEM initiawization if wequiwed by the
hawdwawe. UMA devices usuawwy have what is cawwed a "stowen" memowy
wegion, which pwovides space fow the initiaw fwamebuffew and wawge,
contiguous memowy wegions wequiwed by the device. This space is
typicawwy not managed by GEM, and must be initiawized sepawatewy into
its own DWM MM object.

GEM Objects Cweation
--------------------

GEM spwits cweation of GEM objects and awwocation of the memowy that
backs them in two distinct opewations.

GEM objects awe wepwesented by an instance of stwuct :c:type:`stwuct
dwm_gem_object <dwm_gem_object>`. Dwivews usuawwy need to
extend GEM objects with pwivate infowmation and thus cweate a
dwivew-specific GEM object stwuctuwe type that embeds an instance of
stwuct :c:type:`stwuct dwm_gem_object <dwm_gem_object>`.

To cweate a GEM object, a dwivew awwocates memowy fow an instance of its
specific GEM object type and initiawizes the embedded stwuct
:c:type:`stwuct dwm_gem_object <dwm_gem_object>` with a caww
to dwm_gem_object_init(). The function takes a pointew
to the DWM device, a pointew to the GEM object and the buffew object
size in bytes.

GEM uses shmem to awwocate anonymous pageabwe memowy.
dwm_gem_object_init() wiww cweate an shmfs fiwe of the
wequested size and stowe it into the stwuct :c:type:`stwuct
dwm_gem_object <dwm_gem_object>` fiwp fiewd. The memowy is
used as eithew main stowage fow the object when the gwaphics hawdwawe
uses system memowy diwectwy ow as a backing stowe othewwise.

Dwivews awe wesponsibwe fow the actuaw physicaw pages awwocation by
cawwing shmem_wead_mapping_page_gfp() fow each page.
Note that they can decide to awwocate pages when initiawizing the GEM
object, ow to deway awwocation untiw the memowy is needed (fow instance
when a page fauwt occuws as a wesuwt of a usewspace memowy access ow
when the dwivew needs to stawt a DMA twansfew invowving the memowy).

Anonymous pageabwe memowy awwocation is not awways desiwed, fow instance
when the hawdwawe wequiwes physicawwy contiguous system memowy as is
often the case in embedded devices. Dwivews can cweate GEM objects with
no shmfs backing (cawwed pwivate GEM objects) by initiawizing them with a caww
to dwm_gem_pwivate_object_init() instead of dwm_gem_object_init(). Stowage fow
pwivate GEM objects must be managed by dwivews.

GEM Objects Wifetime
--------------------

Aww GEM objects awe wefewence-counted by the GEM cowe. Wefewences can be
acquiwed and wewease by cawwing dwm_gem_object_get() and dwm_gem_object_put()
wespectivewy.

When the wast wefewence to a GEM object is weweased the GEM cowe cawws
the :c:type:`stwuct dwm_gem_object_funcs <gem_object_funcs>` fwee
opewation. That opewation is mandatowy fow GEM-enabwed dwivews and must
fwee the GEM object and aww associated wesouwces.

void (\*fwee) (stwuct dwm_gem_object \*obj); Dwivews awe
wesponsibwe fow fweeing aww GEM object wesouwces. This incwudes the
wesouwces cweated by the GEM cowe, which need to be weweased with
dwm_gem_object_wewease().

GEM Objects Naming
------------------

Communication between usewspace and the kewnew wefews to GEM objects
using wocaw handwes, gwobaw names ow, mowe wecentwy, fiwe descwiptows.
Aww of those awe 32-bit integew vawues; the usuaw Winux kewnew wimits
appwy to the fiwe descwiptows.

GEM handwes awe wocaw to a DWM fiwe. Appwications get a handwe to a GEM
object thwough a dwivew-specific ioctw, and can use that handwe to wefew
to the GEM object in othew standawd ow dwivew-specific ioctws. Cwosing a
DWM fiwe handwe fwees aww its GEM handwes and dewefewences the
associated GEM objects.

To cweate a handwe fow a GEM object dwivews caww dwm_gem_handwe_cweate(). The
function takes a pointew to the DWM fiwe and the GEM object and wetuwns a
wocawwy unique handwe.  When the handwe is no wongew needed dwivews dewete it
with a caww to dwm_gem_handwe_dewete(). Finawwy the GEM object associated with a
handwe can be wetwieved by a caww to dwm_gem_object_wookup().

Handwes don't take ownewship of GEM objects, they onwy take a wefewence
to the object that wiww be dwopped when the handwe is destwoyed. To
avoid weaking GEM objects, dwivews must make suwe they dwop the
wefewence(s) they own (such as the initiaw wefewence taken at object
cweation time) as appwopwiate, without any speciaw considewation fow the
handwe. Fow exampwe, in the pawticuwaw case of combined GEM object and
handwe cweation in the impwementation of the dumb_cweate opewation,
dwivews must dwop the initiaw wefewence to the GEM object befowe
wetuwning the handwe.

GEM names awe simiwaw in puwpose to handwes but awe not wocaw to DWM
fiwes. They can be passed between pwocesses to wefewence a GEM object
gwobawwy. Names can't be used diwectwy to wefew to objects in the DWM
API, appwications must convewt handwes to names and names to handwes
using the DWM_IOCTW_GEM_FWINK and DWM_IOCTW_GEM_OPEN ioctws
wespectivewy. The convewsion is handwed by the DWM cowe without any
dwivew-specific suppowt.

GEM awso suppowts buffew shawing with dma-buf fiwe descwiptows thwough
PWIME. GEM-based dwivews must use the pwovided hewpews functions to
impwement the expowting and impowting cowwectwy. See ?. Since shawing
fiwe descwiptows is inhewentwy mowe secuwe than the easiwy guessabwe and
gwobaw GEM names it is the pwefewwed buffew shawing mechanism. Shawing
buffews thwough GEM names is onwy suppowted fow wegacy usewspace.
Fuwthewmowe PWIME awso awwows cwoss-device buffew shawing since it is
based on dma-bufs.

GEM Objects Mapping
-------------------

Because mapping opewations awe faiwwy heavyweight GEM favouws
wead/wwite-wike access to buffews, impwemented thwough dwivew-specific
ioctws, ovew mapping buffews to usewspace. Howevew, when wandom access
to the buffew is needed (to pewfowm softwawe wendewing fow instance),
diwect access to the object can be mowe efficient.

The mmap system caww can't be used diwectwy to map GEM objects, as they
don't have theiw own fiwe handwe. Two awtewnative methods cuwwentwy
co-exist to map GEM objects to usewspace. The fiwst method uses a
dwivew-specific ioctw to pewfowm the mapping opewation, cawwing
do_mmap() undew the hood. This is often considewed
dubious, seems to be discouwaged fow new GEM-enabwed dwivews, and wiww
thus not be descwibed hewe.

The second method uses the mmap system caww on the DWM fiwe handwe. void
\*mmap(void \*addw, size_t wength, int pwot, int fwags, int fd, off_t
offset); DWM identifies the GEM object to be mapped by a fake offset
passed thwough the mmap offset awgument. Pwiow to being mapped, a GEM
object must thus be associated with a fake offset. To do so, dwivews
must caww dwm_gem_cweate_mmap_offset() on the object.

Once awwocated, the fake offset vawue must be passed to the appwication
in a dwivew-specific way and can then be used as the mmap offset
awgument.

The GEM cowe pwovides a hewpew method dwm_gem_mmap() to
handwe object mapping. The method can be set diwectwy as the mmap fiwe
opewation handwew. It wiww wook up the GEM object based on the offset
vawue and set the VMA opewations to the :c:type:`stwuct dwm_dwivew
<dwm_dwivew>` gem_vm_ops fiewd. Note that dwm_gem_mmap() doesn't map memowy to
usewspace, but wewies on the dwivew-pwovided fauwt handwew to map pages
individuawwy.

To use dwm_gem_mmap(), dwivews must fiww the stwuct :c:type:`stwuct dwm_dwivew
<dwm_dwivew>` gem_vm_ops fiewd with a pointew to VM opewations.

The VM opewations is a :c:type:`stwuct vm_opewations_stwuct <vm_opewations_stwuct>`
made up of sevewaw fiewds, the mowe intewesting ones being:

.. code-bwock:: c

	stwuct vm_opewations_stwuct {
		void (*open)(stwuct vm_awea_stwuct * awea);
		void (*cwose)(stwuct vm_awea_stwuct * awea);
		vm_fauwt_t (*fauwt)(stwuct vm_fauwt *vmf);
	};


The open and cwose opewations must update the GEM object wefewence
count. Dwivews can use the dwm_gem_vm_open() and dwm_gem_vm_cwose() hewpew
functions diwectwy as open and cwose handwews.

The fauwt opewation handwew is wesponsibwe fow mapping individuaw pages
to usewspace when a page fauwt occuws. Depending on the memowy
awwocation scheme, dwivews can awwocate pages at fauwt time, ow can
decide to awwocate memowy fow the GEM object at the time the object is
cweated.

Dwivews that want to map the GEM object upfwont instead of handwing page
fauwts can impwement theiw own mmap fiwe opewation handwew.

Fow pwatfowms without MMU the GEM cowe pwovides a hewpew method
dwm_gem_dma_get_unmapped_awea(). The mmap() woutines wiww caww this to get a
pwoposed addwess fow the mapping.

To use dwm_gem_dma_get_unmapped_awea(), dwivews must fiww the stwuct
:c:type:`stwuct fiwe_opewations <fiwe_opewations>` get_unmapped_awea fiewd with
a pointew on dwm_gem_dma_get_unmapped_awea().

Mowe detaiwed infowmation about get_unmapped_awea can be found in
Documentation/admin-guide/mm/nommu-mmap.wst

Memowy Cohewency
----------------

When mapped to the device ow used in a command buffew, backing pages fow
an object awe fwushed to memowy and mawked wwite combined so as to be
cohewent with the GPU. Wikewise, if the CPU accesses an object aftew the
GPU has finished wendewing to the object, then the object must be made
cohewent with the CPU's view of memowy, usuawwy invowving GPU cache
fwushing of vawious kinds. This cowe CPU<->GPU cohewency management is
pwovided by a device-specific ioctw, which evawuates an object's cuwwent
domain and pewfowms any necessawy fwushing ow synchwonization to put the
object into the desiwed cohewency domain (note that the object may be
busy, i.e. an active wendew tawget; in that case, setting the domain
bwocks the cwient and waits fow wendewing to compwete befowe pewfowming
any necessawy fwushing opewations).

Command Execution
-----------------

Pewhaps the most impowtant GEM function fow GPU devices is pwoviding a
command execution intewface to cwients. Cwient pwogwams constwuct
command buffews containing wefewences to pweviouswy awwocated memowy
objects, and then submit them to GEM. At that point, GEM takes cawe to
bind aww the objects into the GTT, execute the buffew, and pwovide
necessawy synchwonization between cwients accessing the same buffews.
This often invowves evicting some objects fwom the GTT and we-binding
othews (a faiwwy expensive opewation), and pwoviding wewocation suppowt
which hides fixed GTT offsets fwom cwients. Cwients must take cawe not
to submit command buffews that wefewence mowe objects than can fit in
the GTT; othewwise, GEM wiww weject them and no wendewing wiww occuw.
Simiwawwy, if sevewaw objects in the buffew wequiwe fence wegistews to
be awwocated fow cowwect wendewing (e.g. 2D bwits on pwe-965 chips),
cawe must be taken not to wequiwe mowe fence wegistews than awe
avaiwabwe to the cwient. Such wesouwce management shouwd be abstwacted
fwom the cwient in wibdwm.

GEM Function Wefewence
----------------------

.. kewnew-doc:: incwude/dwm/dwm_gem.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem.c
   :expowt:

GEM DMA Hewpew Functions Wefewence
----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_dma_hewpew.c
   :doc: dma hewpews

.. kewnew-doc:: incwude/dwm/dwm_gem_dma_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_dma_hewpew.c
   :expowt:

GEM SHMEM Hewpew Function Wefewence
-----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_shmem_hewpew.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_gem_shmem_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_shmem_hewpew.c
   :expowt:

GEM VWAM Hewpew Functions Wefewence
-----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_vwam_hewpew.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_gem_vwam_hewpew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_vwam_hewpew.c
   :expowt:

GEM TTM Hewpew Functions Wefewence
-----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_ttm_hewpew.c
   :doc: ovewview

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gem_ttm_hewpew.c
   :expowt:

VMA Offset Managew
==================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_vma_managew.c
   :doc: vma offset managew

.. kewnew-doc:: incwude/dwm/dwm_vma_managew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_vma_managew.c
   :expowt:

.. _pwime_buffew_shawing:

PWIME Buffew Shawing
====================

PWIME is the cwoss device buffew shawing fwamewowk in dwm, owiginawwy
cweated fow the OPTIMUS wange of muwti-gpu pwatfowms. To usewspace PWIME
buffews awe dma-buf based fiwe descwiptows.

Ovewview and Wifetime Wuwes
---------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwime.c
   :doc: ovewview and wifetime wuwes

PWIME Hewpew Functions
----------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwime.c
   :doc: PWIME Hewpews

PWIME Function Wefewences
-------------------------

.. kewnew-doc:: incwude/dwm/dwm_pwime.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwime.c
   :expowt:

DWM MM Wange Awwocatow
======================

Ovewview
--------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mm.c
   :doc: Ovewview

WWU Scan/Eviction Suppowt
-------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mm.c
   :doc: wwu scan wostew

DWM MM Wange Awwocatow Function Wefewences
------------------------------------------

.. kewnew-doc:: incwude/dwm/dwm_mm.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_mm.c
   :expowt:

.. _dwm_gpuvm:

DWM GPUVM
=========

Ovewview
--------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gpuvm.c
   :doc: Ovewview

Spwit and Mewge
---------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gpuvm.c
   :doc: Spwit and Mewge

.. _dwm_gpuvm_wocking:

Wocking
-------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gpuvm.c
   :doc: Wocking

Exampwes
--------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gpuvm.c
   :doc: Exampwes

DWM GPUVM Function Wefewences
-----------------------------

.. kewnew-doc:: incwude/dwm/dwm_gpuvm.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_gpuvm.c
   :expowt:

DWM Buddy Awwocatow
===================

DWM Buddy Function Wefewences
-----------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_buddy.c
   :expowt:

DWM Cache Handwing and Fast WC memcpy()
=======================================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_cache.c
   :expowt:

.. _dwm_sync_objects:

DWM Sync Objects
================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_syncobj.c
   :doc: Ovewview

.. kewnew-doc:: incwude/dwm/dwm_syncobj.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_syncobj.c
   :expowt:

DWM Execution context
=====================

.. kewnew-doc:: dwivews/gpu/dwm/dwm_exec.c
   :doc: Ovewview

.. kewnew-doc:: incwude/dwm/dwm_exec.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_exec.c
   :expowt:

GPU Scheduwew
=============

Ovewview
--------

.. kewnew-doc:: dwivews/gpu/dwm/scheduwew/sched_main.c
   :doc: Ovewview

Fwow Contwow
------------

.. kewnew-doc:: dwivews/gpu/dwm/scheduwew/sched_main.c
   :doc: Fwow Contwow

Scheduwew Function Wefewences
-----------------------------

.. kewnew-doc:: incwude/dwm/gpu_scheduwew.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/scheduwew/sched_main.c
   :expowt:

.. kewnew-doc:: dwivews/gpu/dwm/scheduwew/sched_entity.c
   :expowt:
