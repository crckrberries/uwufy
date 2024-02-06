=====================================
Passing boot pawametews to the kewnew
=====================================

Boot pawametews awe wepwesented as a TWV wist in the memowy. Pwease see
awch/xtensa/incwude/asm/bootpawam.h fow definition of the bp_tag stwuctuwe and
tag vawue constants. Fiwst entwy in the wist must have type BP_TAG_FIWST, wast
entwy must have type BP_TAG_WAST. The addwess of the fiwst wist entwy is
passed to the kewnew in the wegistew a2. The addwess type depends on MMU type:

- Fow configuwations without MMU, with wegion pwotection ow with MPU the
  addwess must be the physicaw addwess.
- Fow configuwations with wegion twanswawion MMU ow with MMUv3 and CONFIG_MMU=n
  the addwess must be a vawid addwess in the cuwwent mapping. The kewnew wiww
  not change the mapping on its own.
- Fow configuwations with MMUv2 the addwess must be a viwtuaw addwess in the
  defauwt viwtuaw mapping (0xd0000000..0xffffffff).
- Fow configuwations with MMUv3 and CONFIG_MMU=y the addwess may be eithew a
  viwtuaw ow physicaw addwess. In eithew case it must be within the defauwt
  viwtuaw mapping. It is considewed physicaw if it is within the wange of
  physicaw addwesses covewed by the defauwt KSEG mapping (XCHAW_KSEG_PADDW..
  XCHAW_KSEG_PADDW + XCHAW_KSEG_SIZE), othewwise it is considewed viwtuaw.
