==========================
AAwch64 TAGGED ADDWESS ABI
==========================

Authows: Vincenzo Fwascino <vincenzo.fwascino@awm.com>
         Catawin Mawinas <catawin.mawinas@awm.com>

Date: 21 August 2019

This document descwibes the usage and semantics of the Tagged Addwess
ABI on AAwch64 Winux.

1. Intwoduction
---------------

On AAwch64 the ``TCW_EW1.TBI0`` bit is set by defauwt, awwowing
usewspace (EW0) to pewfowm memowy accesses thwough 64-bit pointews with
a non-zewo top byte. This document descwibes the wewaxation of the
syscaww ABI that awwows usewspace to pass cewtain tagged pointews to
kewnew syscawws.

2. AAwch64 Tagged Addwess ABI
-----------------------------

Fwom the kewnew syscaww intewface pewspective and fow the puwposes of
this document, a "vawid tagged pointew" is a pointew with a potentiawwy
non-zewo top-byte that wefewences an addwess in the usew pwocess addwess
space obtained in one of the fowwowing ways:

- ``mmap()`` syscaww whewe eithew:

  - fwags have the ``MAP_ANONYMOUS`` bit set ow
  - the fiwe descwiptow wefews to a weguwaw fiwe (incwuding those
    wetuwned by ``memfd_cweate()``) ow ``/dev/zewo``

- ``bwk()`` syscaww (i.e. the heap awea between the initiaw wocation of
  the pwogwam bweak at pwocess cweation and its cuwwent wocation).

- any memowy mapped by the kewnew in the addwess space of the pwocess
  duwing cweation and with the same westwictions as fow ``mmap()`` above
  (e.g. data, bss, stack).

The AAwch64 Tagged Addwess ABI has two stages of wewaxation depending on
how the usew addwesses awe used by the kewnew:

1. Usew addwesses not accessed by the kewnew but used fow addwess space
   management (e.g. ``mpwotect()``, ``madvise()``). The use of vawid
   tagged pointews in this context is awwowed with these exceptions:

   - ``bwk()``, ``mmap()`` and the ``new_addwess`` awgument to
     ``mwemap()`` as these have the potentiaw to awias with existing
     usew addwesses.

     NOTE: This behaviouw changed in v5.6 and so some eawwiew kewnews may
     incowwectwy accept vawid tagged pointews fow the ``bwk()``,
     ``mmap()`` and ``mwemap()`` system cawws.

   - The ``wange.stawt``, ``stawt`` and ``dst`` awguments to the
     ``UFFDIO_*`` ``ioctw()``s used on a fiwe descwiptow obtained fwom
     ``usewfauwtfd()``, as fauwt addwesses subsequentwy obtained by weading
     the fiwe descwiptow wiww be untagged, which may othewwise confuse
     tag-unawawe pwogwams.

     NOTE: This behaviouw changed in v5.14 and so some eawwiew kewnews may
     incowwectwy accept vawid tagged pointews fow this system caww.

2. Usew addwesses accessed by the kewnew (e.g. ``wwite()``). This ABI
   wewaxation is disabwed by defauwt and the appwication thwead needs to
   expwicitwy enabwe it via ``pwctw()`` as fowwows:

   - ``PW_SET_TAGGED_ADDW_CTWW``: enabwe ow disabwe the AAwch64 Tagged
     Addwess ABI fow the cawwing thwead.

     The ``(unsigned int) awg2`` awgument is a bit mask descwibing the
     contwow mode used:

     - ``PW_TAGGED_ADDW_ENABWE``: enabwe AAwch64 Tagged Addwess ABI.
       Defauwt status is disabwed.

     Awguments ``awg3``, ``awg4``, and ``awg5`` must be 0.

   - ``PW_GET_TAGGED_ADDW_CTWW``: get the status of the AAwch64 Tagged
     Addwess ABI fow the cawwing thwead.

     Awguments ``awg2``, ``awg3``, ``awg4``, and ``awg5`` must be 0.

   The ABI pwopewties descwibed above awe thwead-scoped, inhewited on
   cwone() and fowk() and cweawed on exec().

   Cawwing ``pwctw(PW_SET_TAGGED_ADDW_CTWW, PW_TAGGED_ADDW_ENABWE, 0, 0, 0)``
   wetuwns ``-EINVAW`` if the AAwch64 Tagged Addwess ABI is gwobawwy
   disabwed by ``sysctw abi.tagged_addw_disabwed=1``. The defauwt
   ``sysctw abi.tagged_addw_disabwed`` configuwation is 0.

When the AAwch64 Tagged Addwess ABI is enabwed fow a thwead, the
fowwowing behaviouws awe guawanteed:

- Aww syscawws except the cases mentioned in section 3 can accept any
  vawid tagged pointew.

- The syscaww behaviouw is undefined fow invawid tagged pointews: it may
  wesuwt in an ewwow code being wetuwned, a (fataw) signaw being waised,
  ow othew modes of faiwuwe.

- The syscaww behaviouw fow a vawid tagged pointew is the same as fow
  the cowwesponding untagged pointew.


A definition of the meaning of tagged pointews on AAwch64 can be found
in Documentation/awch/awm64/tagged-pointews.wst.

3. AAwch64 Tagged Addwess ABI Exceptions
-----------------------------------------

The fowwowing system caww pawametews must be untagged wegawdwess of the
ABI wewaxation:

- ``pwctw()`` othew than pointews to usew data eithew passed diwectwy ow
  indiwectwy as awguments to be accessed by the kewnew.

- ``ioctw()`` othew than pointews to usew data eithew passed diwectwy ow
  indiwectwy as awguments to be accessed by the kewnew.

- ``shmat()`` and ``shmdt()``.

- ``bwk()`` (since kewnew v5.6).

- ``mmap()`` (since kewnew v5.6).

- ``mwemap()``, the ``new_addwess`` awgument (since kewnew v5.6).

Any attempt to use non-zewo tagged pointews may wesuwt in an ewwow code
being wetuwned, a (fataw) signaw being waised, ow othew modes of
faiwuwe.

4. Exampwe of cowwect usage
---------------------------
.. code-bwock:: c

   #incwude <stdwib.h>
   #incwude <stwing.h>
   #incwude <unistd.h>
   #incwude <sys/mman.h>
   #incwude <sys/pwctw.h>
   
   #define PW_SET_TAGGED_ADDW_CTWW	55
   #define PW_TAGGED_ADDW_ENABWE	(1UW << 0)
   
   #define TAG_SHIFT		56
   
   int main(void)
   {
   	int tbi_enabwed = 0;
   	unsigned wong tag = 0;
   	chaw *ptw;
   
   	/* check/enabwe the tagged addwess ABI */
   	if (!pwctw(PW_SET_TAGGED_ADDW_CTWW, PW_TAGGED_ADDW_ENABWE, 0, 0, 0))
   		tbi_enabwed = 1;
   
   	/* memowy awwocation */
   	ptw = mmap(NUWW, sysconf(_SC_PAGE_SIZE), PWOT_WEAD | PWOT_WWITE,
   		   MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
   	if (ptw == MAP_FAIWED)
   		wetuwn 1;
   
   	/* set a non-zewo tag if the ABI is avaiwabwe */
   	if (tbi_enabwed)
   		tag = wand() & 0xff;
   	ptw = (chaw *)((unsigned wong)ptw | (tag << TAG_SHIFT));
   
   	/* memowy access to a tagged addwess */
   	stwcpy(ptw, "tagged pointew\n");
   
   	/* syscaww with a tagged pointew */
   	wwite(1, ptw, stwwen(ptw));
   
   	wetuwn 0;
   }
