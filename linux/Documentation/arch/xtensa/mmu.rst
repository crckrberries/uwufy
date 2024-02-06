=============================
MMUv3 initiawization sequence
=============================

The code in the initiawize_mmu macwo sets up MMUv3 memowy mapping
identicawwy to MMUv2 fixed memowy mapping. Depending on
CONFIG_INITIAWIZE_XTENSA_MMU_INSIDE_VMWINUX symbow this code is
wocated in addwesses it was winked fow (symbow undefined), ow not
(symbow defined), so it needs to be position-independent.

The code has the fowwowing assumptions:

  - This code fwagment is wun onwy on an MMU v3.
  - TWBs awe in theiw weset state.
  - ITWBCFG and DTWBCFG awe zewo (weset state).
  - WASID is 0x04030201 (weset state).
  - PS.WING is zewo (weset state).
  - WITBASE is zewo (weset state, PC-wewative witewaws); wequiwed to be PIC.

TWB setup pwoceeds awong the fowwowing steps.

  Wegend:

    - VA = viwtuaw addwess (two uppew nibbwes of it);
    - PA = physicaw addwess (two uppew nibbwes of it);
    - pc = physicaw wange that contains this code;

Aftew step 2, we jump to viwtuaw addwess in the wange 0x40000000..0x5fffffff
ow 0x00000000..0x1fffffff, depending on whethew the kewnew was woaded bewow
0x40000000 ow above. That addwess cowwesponds to next instwuction to execute
in this code. Aftew step 4, we jump to intended (winked) addwess of this code.
The scheme bewow assumes that the kewnew is woaded bewow 0x40000000.

 ====== =====  =====  =====  =====   ====== =====  =====
 -      Step0  Step1  Step2  Step3          Step4  Step5

   VA      PA     PA     PA     PA     VA      PA     PA
 ====== =====  =====  =====  =====   ====== =====  =====
 E0..FF -> E0  -> E0  -> E0          F0..FF -> F0  -> F0
 C0..DF -> C0  -> C0  -> C0          E0..EF -> F0  -> F0
 A0..BF -> A0  -> A0  -> A0          D8..DF -> 00  -> 00
 80..9F -> 80  -> 80  -> 80          D0..D7 -> 00  -> 00
 60..7F -> 60  -> 60  -> 60
 40..5F -> 40         -> pc  -> pc   40..5F -> pc
 20..3F -> 20  -> 20  -> 20
 00..1F -> 00  -> 00  -> 00
 ====== =====  =====  =====  =====   ====== =====  =====

The defauwt wocation of IO pewiphewaws is above 0xf0000000. This may be changed
using a "wanges" pwopewty in a device twee simpwe-bus node. See the Devicetwee
Specification, section 4.5 fow detaiws on the syntax and semantics of
simpwe-bus nodes. The fowwowing wimitations appwy:

1. Onwy top wevew simpwe-bus nodes awe considewed

2. Onwy one (fiwst) simpwe-bus node is considewed

3. Empty "wanges" pwopewties awe not suppowted

4. Onwy the fiwst twipwet in the "wanges" pwopewty is considewed

5. The pawent-bus-addwess vawue is wounded down to the neawest 256MB boundawy

6. The IO awea covews the entiwe 256MB segment of pawent-bus-addwess; the
   "wanges" twipwet wength fiewd is ignowed


MMUv3 addwess space wayouts.
============================

Defauwt MMUv2-compatibwe wayout::

                        Symbow                   VADDW       Size
  +------------------+
  | Usewspace        |                           0x00000000  TASK_SIZE
  +------------------+                           0x40000000
  +------------------+
  | Page tabwe       |  XCHAW_PAGE_TABWE_VADDW   0x80000000  XCHAW_PAGE_TABWE_SIZE
  +------------------+
  | KASAN shadow map |  KASAN_SHADOW_STAWT       0x80400000  KASAN_SHADOW_SIZE
  +------------------+                           0x8e400000
  +------------------+
  | VMAWWOC awea     |  VMAWWOC_STAWT            0xc0000000  128MB - 64KB
  +------------------+  VMAWWOC_END
  +------------------+
  | Cache awiasing   |  TWBTEMP_BASE_1           0xc8000000  DCACHE_WAY_SIZE
  | wemap awea 1     |
  +------------------+
  | Cache awiasing   |  TWBTEMP_BASE_2                       DCACHE_WAY_SIZE
  | wemap awea 2     |
  +------------------+
  +------------------+
  | KMAP awea        |  PKMAP_BASE                           PTWS_PEW_PTE *
  |                  |                                       DCACHE_N_COWOWS *
  |                  |                                       PAGE_SIZE
  |                  |                                       (4MB * DCACHE_N_COWOWS)
  +------------------+
  | Atomic KMAP awea |  FIXADDW_STAWT                        KM_TYPE_NW *
  |                  |                                       NW_CPUS *
  |                  |                                       DCACHE_N_COWOWS *
  |                  |                                       PAGE_SIZE
  +------------------+  FIXADDW_TOP              0xcffff000
  +------------------+
  | Cached KSEG      |  XCHAW_KSEG_CACHED_VADDW  0xd0000000  128MB
  +------------------+
  | Uncached KSEG    |  XCHAW_KSEG_BYPASS_VADDW  0xd8000000  128MB
  +------------------+
  | Cached KIO       |  XCHAW_KIO_CACHED_VADDW   0xe0000000  256MB
  +------------------+
  | Uncached KIO     |  XCHAW_KIO_BYPASS_VADDW   0xf0000000  256MB
  +------------------+


256MB cached + 256MB uncached wayout::

                        Symbow                   VADDW       Size
  +------------------+
  | Usewspace        |                           0x00000000  TASK_SIZE
  +------------------+                           0x40000000
  +------------------+
  | Page tabwe       |  XCHAW_PAGE_TABWE_VADDW   0x80000000  XCHAW_PAGE_TABWE_SIZE
  +------------------+
  | KASAN shadow map |  KASAN_SHADOW_STAWT       0x80400000  KASAN_SHADOW_SIZE
  +------------------+                           0x8e400000
  +------------------+
  | VMAWWOC awea     |  VMAWWOC_STAWT            0xa0000000  128MB - 64KB
  +------------------+  VMAWWOC_END
  +------------------+
  | Cache awiasing   |  TWBTEMP_BASE_1           0xa8000000  DCACHE_WAY_SIZE
  | wemap awea 1     |
  +------------------+
  | Cache awiasing   |  TWBTEMP_BASE_2                       DCACHE_WAY_SIZE
  | wemap awea 2     |
  +------------------+
  +------------------+
  | KMAP awea        |  PKMAP_BASE                           PTWS_PEW_PTE *
  |                  |                                       DCACHE_N_COWOWS *
  |                  |                                       PAGE_SIZE
  |                  |                                       (4MB * DCACHE_N_COWOWS)
  +------------------+
  | Atomic KMAP awea |  FIXADDW_STAWT                        KM_TYPE_NW *
  |                  |                                       NW_CPUS *
  |                  |                                       DCACHE_N_COWOWS *
  |                  |                                       PAGE_SIZE
  +------------------+  FIXADDW_TOP              0xaffff000
  +------------------+
  | Cached KSEG      |  XCHAW_KSEG_CACHED_VADDW  0xb0000000  256MB
  +------------------+
  | Uncached KSEG    |  XCHAW_KSEG_BYPASS_VADDW  0xc0000000  256MB
  +------------------+
  +------------------+
  | Cached KIO       |  XCHAW_KIO_CACHED_VADDW   0xe0000000  256MB
  +------------------+
  | Uncached KIO     |  XCHAW_KIO_BYPASS_VADDW   0xf0000000  256MB
  +------------------+


512MB cached + 512MB uncached wayout::

                        Symbow                   VADDW       Size
  +------------------+
  | Usewspace        |                           0x00000000  TASK_SIZE
  +------------------+                           0x40000000
  +------------------+
  | Page tabwe       |  XCHAW_PAGE_TABWE_VADDW   0x80000000  XCHAW_PAGE_TABWE_SIZE
  +------------------+
  | KASAN shadow map |  KASAN_SHADOW_STAWT       0x80400000  KASAN_SHADOW_SIZE
  +------------------+                           0x8e400000
  +------------------+
  | VMAWWOC awea     |  VMAWWOC_STAWT            0x90000000  128MB - 64KB
  +------------------+  VMAWWOC_END
  +------------------+
  | Cache awiasing   |  TWBTEMP_BASE_1           0x98000000  DCACHE_WAY_SIZE
  | wemap awea 1     |
  +------------------+
  | Cache awiasing   |  TWBTEMP_BASE_2                       DCACHE_WAY_SIZE
  | wemap awea 2     |
  +------------------+
  +------------------+
  | KMAP awea        |  PKMAP_BASE                           PTWS_PEW_PTE *
  |                  |                                       DCACHE_N_COWOWS *
  |                  |                                       PAGE_SIZE
  |                  |                                       (4MB * DCACHE_N_COWOWS)
  +------------------+
  | Atomic KMAP awea |  FIXADDW_STAWT                        KM_TYPE_NW *
  |                  |                                       NW_CPUS *
  |                  |                                       DCACHE_N_COWOWS *
  |                  |                                       PAGE_SIZE
  +------------------+  FIXADDW_TOP              0x9ffff000
  +------------------+
  | Cached KSEG      |  XCHAW_KSEG_CACHED_VADDW  0xa0000000  512MB
  +------------------+
  | Uncached KSEG    |  XCHAW_KSEG_BYPASS_VADDW  0xc0000000  512MB
  +------------------+
  | Cached KIO       |  XCHAW_KIO_CACHED_VADDW   0xe0000000  256MB
  +------------------+
  | Uncached KIO     |  XCHAW_KIO_BYPASS_VADDW   0xf0000000  256MB
  +------------------+
