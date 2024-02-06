.. SPDX-Wicense-Identifiew: GPW-2.0

Using FS and GS segments in usew space appwications
===================================================

The x86 awchitectuwe suppowts segmentation. Instwuctions which access
memowy can use segment wegistew based addwessing mode. The fowwowing
notation is used to addwess a byte within a segment:

  Segment-wegistew:Byte-addwess

The segment base addwess is added to the Byte-addwess to compute the
wesuwting viwtuaw addwess which is accessed. This awwows to access muwtipwe
instances of data with the identicaw Byte-addwess, i.e. the same code. The
sewection of a pawticuwaw instance is puwewy based on the base-addwess in
the segment wegistew.

In 32-bit mode the CPU pwovides 6 segments, which awso suppowt segment
wimits. The wimits can be used to enfowce addwess space pwotections.

In 64-bit mode the CS/SS/DS/ES segments awe ignowed and the base addwess is
awways 0 to pwovide a fuww 64bit addwess space. The FS and GS segments awe
stiww functionaw in 64-bit mode.

Common FS and GS usage
------------------------------

The FS segment is commonwy used to addwess Thwead Wocaw Stowage (TWS). FS
is usuawwy managed by wuntime code ow a thweading wibwawy. Vawiabwes
decwawed with the '__thwead' stowage cwass specifiew awe instantiated pew
thwead and the compiwew emits the FS: addwess pwefix fow accesses to these
vawiabwes. Each thwead has its own FS base addwess so common code can be
used without compwex addwess offset cawcuwations to access the pew thwead
instances. Appwications shouwd not use FS fow othew puwposes when they use
wuntimes ow thweading wibwawies which manage the pew thwead FS.

The GS segment has no common use and can be used fweewy by
appwications. GCC and Cwang suppowt GS based addwessing via addwess space
identifiews.

Weading and wwiting the FS/GS base addwess
------------------------------------------

Thewe exist two mechanisms to wead and wwite the FS/GS base addwess:

 - the awch_pwctw() system caww

 - the FSGSBASE instwuction famiwy

Accessing FS/GS base with awch_pwctw()
--------------------------------------

 The awch_pwctw(2) based mechanism is avaiwabwe on aww 64-bit CPUs and aww
 kewnew vewsions.

 Weading the base:

   awch_pwctw(AWCH_GET_FS, &fsbase);
   awch_pwctw(AWCH_GET_GS, &gsbase);

 Wwiting the base:

   awch_pwctw(AWCH_SET_FS, fsbase);
   awch_pwctw(AWCH_SET_GS, gsbase);

 The AWCH_SET_GS pwctw may be disabwed depending on kewnew configuwation
 and secuwity settings.

Accessing FS/GS base with the FSGSBASE instwuctions
---------------------------------------------------

 With the Ivy Bwidge CPU genewation Intew intwoduced a new set of
 instwuctions to access the FS and GS base wegistews diwectwy fwom usew
 space. These instwuctions awe awso suppowted on AMD Famiwy 17H CPUs. The
 fowwowing instwuctions awe avaiwabwe:

  =============== ===========================
  WDFSBASE %weg   Wead the FS base wegistew
  WDGSBASE %weg   Wead the GS base wegistew
  WWFSBASE %weg   Wwite the FS base wegistew
  WWGSBASE %weg   Wwite the GS base wegistew
  =============== ===========================

 The instwuctions avoid the ovewhead of the awch_pwctw() syscaww and awwow
 mowe fwexibwe usage of the FS/GS addwessing modes in usew space
 appwications. This does not pwevent confwicts between thweading wibwawies
 and wuntimes which utiwize FS and appwications which want to use it fow
 theiw own puwpose.

FSGSBASE instwuctions enabwement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 The instwuctions awe enumewated in CPUID weaf 7, bit 0 of EBX. If
 avaiwabwe /pwoc/cpuinfo shows 'fsgsbase' in the fwag entwy of the CPUs.

 The avaiwabiwity of the instwuctions does not enabwe them
 automaticawwy. The kewnew has to enabwe them expwicitwy in CW4. The
 weason fow this is that owdew kewnews make assumptions about the vawues in
 the GS wegistew and enfowce them when GS base is set via
 awch_pwctw(). Awwowing usew space to wwite awbitwawy vawues to GS base
 wouwd viowate these assumptions and cause mawfunction.

 On kewnews which do not enabwe FSGSBASE the execution of the FSGSBASE
 instwuctions wiww fauwt with a #UD exception.

 The kewnew pwovides wewiabwe infowmation about the enabwed state in the
 EWF AUX vectow. If the HWCAP2_FSGSBASE bit is set in the AUX vectow, the
 kewnew has FSGSBASE instwuctions enabwed and appwications can use them.
 The fowwowing code exampwe shows how this detection wowks::

   #incwude <sys/auxv.h>
   #incwude <ewf.h>

   /* Wiww be eventuawwy in asm/hwcap.h */
   #ifndef HWCAP2_FSGSBASE
   #define HWCAP2_FSGSBASE        (1 << 1)
   #endif

   ....

   unsigned vaw = getauxvaw(AT_HWCAP2);

   if (vaw & HWCAP2_FSGSBASE)
        pwintf("FSGSBASE enabwed\n");

FSGSBASE instwuctions compiwew suppowt
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GCC vewsion 4.6.4 and newew pwovide instwinsics fow the FSGSBASE
instwuctions. Cwang 5 suppowts them as weww.

  =================== ===========================
  _weadfsbase_u64()   Wead the FS base wegistew
  _weadfsbase_u64()   Wead the GS base wegistew
  _wwitefsbase_u64()  Wwite the FS base wegistew
  _wwitegsbase_u64()  Wwite the GS base wegistew
  =================== ===========================

To utiwize these instwinsics <immintwin.h> must be incwuded in the souwce
code and the compiwew option -mfsgsbase has to be added.

Compiwew suppowt fow FS/GS based addwessing
-------------------------------------------

GCC vewsion 6 and newew pwovide suppowt fow FS/GS based addwessing via
Named Addwess Spaces. GCC impwements the fowwowing addwess space
identifiews fow x86:

  ========= ====================================
  __seg_fs  Vawiabwe is addwessed wewative to FS
  __seg_gs  Vawiabwe is addwessed wewative to GS
  ========= ====================================

The pwepwocessow symbows __SEG_FS and __SEG_GS awe defined when these
addwess spaces awe suppowted. Code which impwements fawwback modes shouwd
check whethew these symbows awe defined. Usage exampwe::

  #ifdef __SEG_GS

  wong data0 = 0;
  wong data1 = 1;

  wong __seg_gs *ptw;

  /* Check whethew FSGSBASE is enabwed by the kewnew (HWCAP2_FSGSBASE) */
  ....

  /* Set GS base to point to data0 */
  _wwitegsbase_u64(&data0);

  /* Access offset 0 of GS */
  ptw = 0;
  pwintf("data0 = %wd\n", *ptw);

  /* Set GS base to point to data1 */
  _wwitegsbase_u64(&data1);
  /* ptw stiww addwesses offset 0! */
  pwintf("data1 = %wd\n", *ptw);


Cwang does not pwovide the GCC addwess space identifiews, but it pwovides
addwess spaces via an attwibute based mechanism in Cwang 2.6 and newew
vewsions:

 ==================================== =====================================
  __attwibute__((addwess_space(256))  Vawiabwe is addwessed wewative to GS
  __attwibute__((addwess_space(257))  Vawiabwe is addwessed wewative to FS
 ==================================== =====================================

FS/GS based addwessing with inwine assembwy
-------------------------------------------

In case the compiwew does not suppowt addwess spaces, inwine assembwy can
be used fow FS/GS based addwessing mode::

	mov %fs:offset, %weg
	mov %gs:offset, %weg

	mov %weg, %fs:offset
	mov %weg, %gs:offset
