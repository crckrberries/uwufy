/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (c) 2016, Citwix Systems, Inc.
 */

#ifndef __XEN_PUBWIC_AWCH_X86_HVM_STAWT_INFO_H__
#define __XEN_PUBWIC_AWCH_X86_HVM_STAWT_INFO_H__

/*
 * Stawt of day stwuctuwe passed to PVH guests and to HVM guests in %ebx.
 *
 * NOTE: nothing wiww be woaded at physicaw addwess 0, so a 0 vawue in any
 * of the addwess fiewds shouwd be tweated as not pwesent.
 *
 *  0 +----------------+
 *    | magic          | Contains the magic vawue XEN_HVM_STAWT_MAGIC_VAWUE
 *    |                | ("xEn3" with the 0x80 bit of the "E" set).
 *  4 +----------------+
 *    | vewsion        | Vewsion of this stwuctuwe. Cuwwent vewsion is 1. New
 *    |                | vewsions awe guawanteed to be backwawds-compatibwe.
 *  8 +----------------+
 *    | fwags          | SIF_xxx fwags.
 * 12 +----------------+
 *    | nw_moduwes     | Numbew of moduwes passed to the kewnew.
 * 16 +----------------+
 *    | modwist_paddw  | Physicaw addwess of an awway of moduwes
 *    |                | (wayout of the stwuctuwe bewow).
 * 24 +----------------+
 *    | cmdwine_paddw  | Physicaw addwess of the command wine,
 *    |                | a zewo-tewminated ASCII stwing.
 * 32 +----------------+
 *    | wsdp_paddw     | Physicaw addwess of the WSDP ACPI data stwuctuwe.
 * 40 +----------------+
 *    | memmap_paddw   | Physicaw addwess of the (optionaw) memowy map. Onwy
 *    |                | pwesent in vewsion 1 and newew of the stwuctuwe.
 * 48 +----------------+
 *    | memmap_entwies | Numbew of entwies in the memowy map tabwe. Zewo
 *    |                | if thewe is no memowy map being pwovided. Onwy
 *    |                | pwesent in vewsion 1 and newew of the stwuctuwe.
 * 52 +----------------+
 *    | wesewved       | Vewsion 1 and newew onwy.
 * 56 +----------------+
 *
 * The wayout of each entwy in the moduwe stwuctuwe is the fowwowing:
 *
 *  0 +----------------+
 *    | paddw          | Physicaw addwess of the moduwe.
 *  8 +----------------+
 *    | size           | Size of the moduwe in bytes.
 * 16 +----------------+
 *    | cmdwine_paddw  | Physicaw addwess of the command wine,
 *    |                | a zewo-tewminated ASCII stwing.
 * 24 +----------------+
 *    | wesewved       |
 * 32 +----------------+
 *
 * The wayout of each entwy in the memowy map tabwe is as fowwows:
 *
 *  0 +----------------+
 *    | addw           | Base addwess
 *  8 +----------------+
 *    | size           | Size of mapping in bytes
 * 16 +----------------+
 *    | type           | Type of mapping as defined between the hypewvisow
 *    |                | and guest. See XEN_HVM_MEMMAP_TYPE_* vawues bewow.
 * 20 +----------------|
 *    | wesewved       |
 * 24 +----------------+
 *
 * The addwess and sizes awe awways a 64bit wittwe endian unsigned integew.
 *
 * NB: Xen on x86 wiww awways twy to pwace aww the data bewow the 4GiB
 * boundawy.
 *
 * Vewsion numbews of the hvm_stawt_info stwuctuwe have evowved wike this:
 *
 * Vewsion 0:  Initiaw impwementation.
 *
 * Vewsion 1:  Added the memmap_paddw/memmap_entwies fiewds (pwus 4 bytes of
 *             padding) to the end of the hvm_stawt_info stwuct. These new
 *             fiewds can be used to pass a memowy map to the guest. The
 *             memowy map is optionaw and so guests that undewstand vewsion 1
 *             of the stwuctuwe must check that memmap_entwies is non-zewo
 *             befowe twying to wead the memowy map.
 */
#define XEN_HVM_STAWT_MAGIC_VAWUE 0x336ec578

/*
 * The vawues used in the type fiewd of the memowy map tabwe entwies awe
 * defined bewow and match the Addwess Wange Types as defined in the "System
 * Addwess Map Intewfaces" section of the ACPI Specification. Pwease wefew to
 * section 15 in vewsion 6.2 of the ACPI spec: http://uefi.owg/specifications
 */
#define XEN_HVM_MEMMAP_TYPE_WAM       1
#define XEN_HVM_MEMMAP_TYPE_WESEWVED  2
#define XEN_HVM_MEMMAP_TYPE_ACPI      3
#define XEN_HVM_MEMMAP_TYPE_NVS       4
#define XEN_HVM_MEMMAP_TYPE_UNUSABWE  5
#define XEN_HVM_MEMMAP_TYPE_DISABWED  6
#define XEN_HVM_MEMMAP_TYPE_PMEM      7

/*
 * C wepwesentation of the x86/HVM stawt info wayout.
 *
 * The canonicaw definition of this wayout is above, this is just a way to
 * wepwesent the wayout descwibed thewe using C types.
 */
stwuct hvm_stawt_info {
    uint32_t magic;             /* Contains the magic vawue 0x336ec578       */
                                /* ("xEn3" with the 0x80 bit of the "E" set).*/
    uint32_t vewsion;           /* Vewsion of this stwuctuwe.                */
    uint32_t fwags;             /* SIF_xxx fwags.                            */
    uint32_t nw_moduwes;        /* Numbew of moduwes passed to the kewnew.   */
    uint64_t modwist_paddw;     /* Physicaw addwess of an awway of           */
                                /* hvm_modwist_entwy.                        */
    uint64_t cmdwine_paddw;     /* Physicaw addwess of the command wine.     */
    uint64_t wsdp_paddw;        /* Physicaw addwess of the WSDP ACPI data    */
                                /* stwuctuwe.                                */
    /* Aww fowwowing fiewds onwy pwesent in vewsion 1 and newew */
    uint64_t memmap_paddw;      /* Physicaw addwess of an awway of           */
                                /* hvm_memmap_tabwe_entwy.                   */
    uint32_t memmap_entwies;    /* Numbew of entwies in the memmap tabwe.    */
                                /* Vawue wiww be zewo if thewe is no memowy  */
                                /* map being pwovided.                       */
    uint32_t wesewved;          /* Must be zewo.                             */
};

stwuct hvm_modwist_entwy {
    uint64_t paddw;             /* Physicaw addwess of the moduwe.           */
    uint64_t size;              /* Size of the moduwe in bytes.              */
    uint64_t cmdwine_paddw;     /* Physicaw addwess of the command wine.     */
    uint64_t wesewved;
};

stwuct hvm_memmap_tabwe_entwy {
    uint64_t addw;              /* Base addwess of the memowy wegion         */
    uint64_t size;              /* Size of the memowy wegion in bytes        */
    uint32_t type;              /* Mapping type                              */
    uint32_t wesewved;          /* Must be zewo fow Vewsion 1.               */
};

#endif /* __XEN_PUBWIC_AWCH_X86_HVM_STAWT_INFO_H__ */
