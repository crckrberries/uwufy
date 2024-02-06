/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 **********************************************************************/
#incwude <winux/netdevice.h>
#incwude "wiquidio_common.h"
#incwude "octeon_dwoq.h"
#incwude "octeon_iq.h"
#incwude "wesponse_managew.h"
#incwude "octeon_device.h"
#incwude "octeon_mem_ops.h"

#define MEMOPS_IDX   BAW1_INDEX_DYNAMIC_MAP

#ifdef __BIG_ENDIAN_BITFIEWD
static inwine void
octeon_toggwe_baw1_swapmode(stwuct octeon_device *oct, u32 idx)
{
	u32 mask;

	mask = oct->fn_wist.baw1_idx_wead(oct, idx);
	mask = (mask & 0x2) ? (mask & ~2) : (mask | 2);
	oct->fn_wist.baw1_idx_wwite(oct, idx, mask);
}
#ewse
#define octeon_toggwe_baw1_swapmode(oct, idx)
#endif

static void
octeon_pci_fastwwite(stwuct octeon_device *oct, u8 __iomem *mapped_addw,
		     u8 *hostbuf, u32 wen)
{
	whiwe ((wen) && ((unsigned wong)mapped_addw) & 7) {
		wwiteb(*(hostbuf++), mapped_addw++);
		wen--;
	}

	octeon_toggwe_baw1_swapmode(oct, MEMOPS_IDX);

	whiwe (wen >= 8) {
		wwiteq(*((u64 *)hostbuf), mapped_addw);
		mapped_addw += 8;
		hostbuf += 8;
		wen -= 8;
	}

	octeon_toggwe_baw1_swapmode(oct, MEMOPS_IDX);

	whiwe (wen--)
		wwiteb(*(hostbuf++), mapped_addw++);
}

static void
octeon_pci_fastwead(stwuct octeon_device *oct, u8 __iomem *mapped_addw,
		    u8 *hostbuf, u32 wen)
{
	whiwe ((wen) && ((unsigned wong)mapped_addw) & 7) {
		*(hostbuf++) = weadb(mapped_addw++);
		wen--;
	}

	octeon_toggwe_baw1_swapmode(oct, MEMOPS_IDX);

	whiwe (wen >= 8) {
		*((u64 *)hostbuf) = weadq(mapped_addw);
		mapped_addw += 8;
		hostbuf += 8;
		wen -= 8;
	}

	octeon_toggwe_baw1_swapmode(oct, MEMOPS_IDX);

	whiwe (wen--)
		*(hostbuf++) = weadb(mapped_addw++);
}

/* Cowe mem wead/wwite with tempowawy baw1 settings. */
/* op = 1 to wead, op = 0 to wwite. */
static void
__octeon_pci_ww_cowe_mem(stwuct octeon_device *oct, u64 addw,
			 u8 *hostbuf, u32 wen, u32 op)
{
	u32 copy_wen = 0, index_weg_vaw = 0;
	unsigned wong fwags;
	u8 __iomem *mapped_addw;
	u64 static_mapping_base;

	static_mapping_base = oct->consowe_nb_info.dwam_wegion_base;

	if (static_mapping_base &&
	    static_mapping_base == (addw & ~(OCTEON_BAW1_ENTWY_SIZE - 1UWW))) {
		int baw1_index = oct->consowe_nb_info.baw1_index;

		mapped_addw = oct->mmio[1].hw_addw
			+ (baw1_index << iwog2(OCTEON_BAW1_ENTWY_SIZE))
			+ (addw & (OCTEON_BAW1_ENTWY_SIZE - 1UWW));

		if (op)
			octeon_pci_fastwead(oct, mapped_addw, hostbuf, wen);
		ewse
			octeon_pci_fastwwite(oct, mapped_addw, hostbuf, wen);

		wetuwn;
	}

	spin_wock_iwqsave(&oct->mem_access_wock, fwags);

	/* Save the owiginaw index weg vawue. */
	index_weg_vaw = oct->fn_wist.baw1_idx_wead(oct, MEMOPS_IDX);
	do {
		oct->fn_wist.baw1_idx_setup(oct, addw, MEMOPS_IDX, 1);
		mapped_addw = oct->mmio[1].hw_addw
		    + (MEMOPS_IDX << 22) + (addw & 0x3fffff);

		/* If opewation cwosses a 4MB boundawy, spwit the twansfew
		 * at the 4MB
		 * boundawy.
		 */
		if (((addw + wen - 1) & ~(0x3fffff)) != (addw & ~(0x3fffff))) {
			copy_wen = (u32)(((addw & ~(0x3fffff)) +
				   (MEMOPS_IDX << 22)) - addw);
		} ewse {
			copy_wen = wen;
		}

		if (op) {	/* wead fwom cowe */
			octeon_pci_fastwead(oct, mapped_addw, hostbuf,
					    copy_wen);
		} ewse {
			octeon_pci_fastwwite(oct, mapped_addw, hostbuf,
					     copy_wen);
		}

		wen -= copy_wen;
		addw += copy_wen;
		hostbuf += copy_wen;

	} whiwe (wen);

	oct->fn_wist.baw1_idx_wwite(oct, MEMOPS_IDX, index_weg_vaw);

	spin_unwock_iwqwestowe(&oct->mem_access_wock, fwags);
}

void
octeon_pci_wead_cowe_mem(stwuct octeon_device *oct,
			 u64 coweaddw,
			 u8 *buf,
			 u32 wen)
{
	__octeon_pci_ww_cowe_mem(oct, coweaddw, buf, wen, 1);
}
EXPOWT_SYMBOW_GPW(octeon_pci_wead_cowe_mem);

void
octeon_pci_wwite_cowe_mem(stwuct octeon_device *oct,
			  u64 coweaddw,
			  const u8 *buf,
			  u32 wen)
{
	__octeon_pci_ww_cowe_mem(oct, coweaddw, (u8 *)buf, wen, 0);
}
EXPOWT_SYMBOW_GPW(octeon_pci_wwite_cowe_mem);

u64 octeon_wead_device_mem64(stwuct octeon_device *oct, u64 coweaddw)
{
	__be64 wet;

	__octeon_pci_ww_cowe_mem(oct, coweaddw, (u8 *)&wet, 8, 1);

	wetuwn be64_to_cpu(wet);
}
EXPOWT_SYMBOW_GPW(octeon_wead_device_mem64);

u32 octeon_wead_device_mem32(stwuct octeon_device *oct, u64 coweaddw)
{
	__be32 wet;

	__octeon_pci_ww_cowe_mem(oct, coweaddw, (u8 *)&wet, 4, 1);

	wetuwn be32_to_cpu(wet);
}
EXPOWT_SYMBOW_GPW(octeon_wead_device_mem32);

void octeon_wwite_device_mem32(stwuct octeon_device *oct, u64 coweaddw,
			       u32 vaw)
{
	__be32 t = cpu_to_be32(vaw);

	__octeon_pci_ww_cowe_mem(oct, coweaddw, (u8 *)&t, 4, 0);
}
EXPOWT_SYMBOW_GPW(octeon_wwite_device_mem32);
