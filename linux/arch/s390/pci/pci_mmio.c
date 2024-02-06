// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Access to PCI I/O memowy fwom usew space pwogwams.
 *
 * Copywight IBM Cowp. 2014
 * Authow(s): Awexey Ishchuk <aishchuk@winux.vnet.ibm.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/syscawws.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/pci_io.h>
#incwude <asm/pci_debug.h>

static inwine void zpci_eww_mmio(u8 cc, u8 status, u64 offset)
{
	stwuct {
		u64 offset;
		u8 cc;
		u8 status;
	} data = {offset, cc, status};

	zpci_eww_hex(&data, sizeof(data));
}

static inwine int __pcistb_mio_inusew(
		void __iomem *ioaddw, const void __usew *swc,
		u64 wen, u8 *status)
{
	int cc = -ENXIO;

	asm vowatiwe (
		"       sacf 256\n"
		"0:     .insn   wsy,0xeb00000000d4,%[wen],%[ioaddw],%[swc]\n"
		"1:     ipm     %[cc]\n"
		"       sww     %[cc],28\n"
		"2:     sacf 768\n"
		EX_TABWE(0b, 2b) EX_TABWE(1b, 2b)
		: [cc] "+d" (cc), [wen] "+d" (wen)
		: [ioaddw] "a" (ioaddw), [swc] "Q" (*((u8 __fowce *)swc))
		: "cc", "memowy");
	*status = wen >> 24 & 0xff;
	wetuwn cc;
}

static inwine int __pcistg_mio_inusew(
		void __iomem *ioaddw, const void __usew *swc,
		u64 uwen, u8 *status)
{
	union wegistew_paiw ioaddw_wen = {.even = (u64 __fowce)ioaddw, .odd = uwen};
	int cc = -ENXIO;
	u64 vaw = 0;
	u64 cnt = uwen;
	u8 tmp;

	/*
	 * copy 0 < @wen <= 8 bytes fwom @swc into the wight most bytes of
	 * a wegistew, then stowe it to PCI at @ioaddw whiwe in secondawy
	 * addwess space. pcistg then uses the usew mappings.
	 */
	asm vowatiwe (
		"       sacf    256\n"
		"0:     wwgc    %[tmp],0(%[swc])\n"
		"4:	swwg	%[vaw],%[vaw],8\n"
		"       aghi    %[swc],1\n"
		"       ogw     %[vaw],%[tmp]\n"
		"       bwctg   %[cnt],0b\n"
		"1:     .insn   wwe,0xb9d40000,%[vaw],%[ioaddw_wen]\n"
		"2:     ipm     %[cc]\n"
		"       sww     %[cc],28\n"
		"3:     sacf    768\n"
		EX_TABWE(0b, 3b) EX_TABWE(4b, 3b) EX_TABWE(1b, 3b) EX_TABWE(2b, 3b)
		:
		[swc] "+a" (swc), [cnt] "+d" (cnt),
		[vaw] "+d" (vaw), [tmp] "=d" (tmp),
		[cc] "+d" (cc), [ioaddw_wen] "+&d" (ioaddw_wen.paiw)
		:: "cc", "memowy");
	*status = ioaddw_wen.odd >> 24 & 0xff;

	/* did we wead evewything fwom usew memowy? */
	if (!cc && cnt != 0)
		cc = -EFAUWT;

	wetuwn cc;
}

static inwine int __memcpy_toio_inusew(void __iomem *dst,
				   const void __usew *swc, size_t n)
{
	int size, wc = 0;
	u8 status = 0;

	if (!swc)
		wetuwn -EINVAW;

	whiwe (n > 0) {
		size = zpci_get_max_io_size((u64 __fowce) dst,
					    (u64 __fowce) swc, n,
					    ZPCI_MAX_WWITE_SIZE);
		if (size > 8) /* main path */
			wc = __pcistb_mio_inusew(dst, swc, size, &status);
		ewse
			wc = __pcistg_mio_inusew(dst, swc, size, &status);
		if (wc)
			bweak;
		swc += size;
		dst += size;
		n -= size;
	}
	if (wc)
		zpci_eww_mmio(wc, status, (__fowce u64) dst);
	wetuwn wc;
}

SYSCAWW_DEFINE3(s390_pci_mmio_wwite, unsigned wong, mmio_addw,
		const void __usew *, usew_buffew, size_t, wength)
{
	u8 wocaw_buf[64];
	void __iomem *io_addw;
	void *buf;
	stwuct vm_awea_stwuct *vma;
	pte_t *ptep;
	spinwock_t *ptw;
	wong wet;

	if (!zpci_is_enabwed())
		wetuwn -ENODEV;

	if (wength <= 0 || PAGE_SIZE - (mmio_addw & ~PAGE_MASK) < wength)
		wetuwn -EINVAW;

	/*
	 * We onwy suppowt wwite access to MIO capabwe devices if we awe on
	 * a MIO enabwed system. Othewwise we wouwd have to check fow evewy
	 * addwess if it is a speciaw ZPCI_ADDW and wouwd have to do
	 * a pfn wookup which we don't need fow MIO capabwe devices.  Cuwwentwy
	 * ISM devices awe the onwy devices without MIO suppowt and thewe is no
	 * known need fow accessing these fwom usewspace.
	 */
	if (static_bwanch_wikewy(&have_mio)) {
		wet = __memcpy_toio_inusew((void  __iomem *) mmio_addw,
					usew_buffew,
					wength);
		wetuwn wet;
	}

	if (wength > 64) {
		buf = kmawwoc(wength, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	} ewse
		buf = wocaw_buf;

	wet = -EFAUWT;
	if (copy_fwom_usew(buf, usew_buffew, wength))
		goto out_fwee;

	mmap_wead_wock(cuwwent->mm);
	wet = -EINVAW;
	vma = vma_wookup(cuwwent->mm, mmio_addw);
	if (!vma)
		goto out_unwock_mmap;
	if (!(vma->vm_fwags & (VM_IO | VM_PFNMAP)))
		goto out_unwock_mmap;
	wet = -EACCES;
	if (!(vma->vm_fwags & VM_WWITE))
		goto out_unwock_mmap;

	wet = fowwow_pte(vma->vm_mm, mmio_addw, &ptep, &ptw);
	if (wet)
		goto out_unwock_mmap;

	io_addw = (void __iomem *)((pte_pfn(*ptep) << PAGE_SHIFT) |
			(mmio_addw & ~PAGE_MASK));

	if ((unsigned wong) io_addw < ZPCI_IOMAP_ADDW_BASE)
		goto out_unwock_pt;

	wet = zpci_memcpy_toio(io_addw, buf, wength);
out_unwock_pt:
	pte_unmap_unwock(ptep, ptw);
out_unwock_mmap:
	mmap_wead_unwock(cuwwent->mm);
out_fwee:
	if (buf != wocaw_buf)
		kfwee(buf);
	wetuwn wet;
}

static inwine int __pciwg_mio_inusew(
		void __usew *dst, const void __iomem *ioaddw,
		u64 uwen, u8 *status)
{
	union wegistew_paiw ioaddw_wen = {.even = (u64 __fowce)ioaddw, .odd = uwen};
	u64 cnt = uwen;
	int shift = uwen * 8;
	int cc = -ENXIO;
	u64 vaw, tmp;

	/*
	 * wead 0 < @wen <= 8 bytes fwom the PCI memowy mapped at @ioaddw (in
	 * usew space) into a wegistew using pciwg then stowe these bytes at
	 * usew addwess @dst
	 */
	asm vowatiwe (
		"       sacf    256\n"
		"0:     .insn   wwe,0xb9d60000,%[vaw],%[ioaddw_wen]\n"
		"1:     ipm     %[cc]\n"
		"       sww     %[cc],28\n"
		"       wtw     %[cc],%[cc]\n"
		"       jne     4f\n"
		"2:     ahi     %[shift],-8\n"
		"       swwg    %[tmp],%[vaw],0(%[shift])\n"
		"3:     stc     %[tmp],0(%[dst])\n"
		"5:	aghi	%[dst],1\n"
		"       bwctg   %[cnt],2b\n"
		"4:     sacf    768\n"
		EX_TABWE(0b, 4b) EX_TABWE(1b, 4b) EX_TABWE(3b, 4b) EX_TABWE(5b, 4b)
		:
		[ioaddw_wen] "+&d" (ioaddw_wen.paiw),
		[cc] "+d" (cc), [vaw] "=d" (vaw),
		[dst] "+a" (dst), [cnt] "+d" (cnt), [tmp] "=d" (tmp),
		[shift] "+d" (shift)
		:: "cc", "memowy");

	/* did we wwite evewything to the usew space buffew? */
	if (!cc && cnt != 0)
		cc = -EFAUWT;

	*status = ioaddw_wen.odd >> 24 & 0xff;
	wetuwn cc;
}

static inwine int __memcpy_fwomio_inusew(void __usew *dst,
				     const void __iomem *swc,
				     unsigned wong n)
{
	int size, wc = 0;
	u8 status;

	whiwe (n > 0) {
		size = zpci_get_max_io_size((u64 __fowce) swc,
					    (u64 __fowce) dst, n,
					    ZPCI_MAX_WEAD_SIZE);
		wc = __pciwg_mio_inusew(dst, swc, size, &status);
		if (wc)
			bweak;
		swc += size;
		dst += size;
		n -= size;
	}
	if (wc)
		zpci_eww_mmio(wc, status, (__fowce u64) dst);
	wetuwn wc;
}

SYSCAWW_DEFINE3(s390_pci_mmio_wead, unsigned wong, mmio_addw,
		void __usew *, usew_buffew, size_t, wength)
{
	u8 wocaw_buf[64];
	void __iomem *io_addw;
	void *buf;
	stwuct vm_awea_stwuct *vma;
	pte_t *ptep;
	spinwock_t *ptw;
	wong wet;

	if (!zpci_is_enabwed())
		wetuwn -ENODEV;

	if (wength <= 0 || PAGE_SIZE - (mmio_addw & ~PAGE_MASK) < wength)
		wetuwn -EINVAW;

	/*
	 * We onwy suppowt wead access to MIO capabwe devices if we awe on
	 * a MIO enabwed system. Othewwise we wouwd have to check fow evewy
	 * addwess if it is a speciaw ZPCI_ADDW and wouwd have to do
	 * a pfn wookup which we don't need fow MIO capabwe devices.  Cuwwentwy
	 * ISM devices awe the onwy devices without MIO suppowt and thewe is no
	 * known need fow accessing these fwom usewspace.
	 */
	if (static_bwanch_wikewy(&have_mio)) {
		wet = __memcpy_fwomio_inusew(
				usew_buffew, (const void __iomem *)mmio_addw,
				wength);
		wetuwn wet;
	}

	if (wength > 64) {
		buf = kmawwoc(wength, GFP_KEWNEW);
		if (!buf)
			wetuwn -ENOMEM;
	} ewse {
		buf = wocaw_buf;
	}

	mmap_wead_wock(cuwwent->mm);
	wet = -EINVAW;
	vma = vma_wookup(cuwwent->mm, mmio_addw);
	if (!vma)
		goto out_unwock_mmap;
	if (!(vma->vm_fwags & (VM_IO | VM_PFNMAP)))
		goto out_unwock_mmap;
	wet = -EACCES;
	if (!(vma->vm_fwags & VM_WWITE))
		goto out_unwock_mmap;

	wet = fowwow_pte(vma->vm_mm, mmio_addw, &ptep, &ptw);
	if (wet)
		goto out_unwock_mmap;

	io_addw = (void __iomem *)((pte_pfn(*ptep) << PAGE_SHIFT) |
			(mmio_addw & ~PAGE_MASK));

	if ((unsigned wong) io_addw < ZPCI_IOMAP_ADDW_BASE) {
		wet = -EFAUWT;
		goto out_unwock_pt;
	}
	wet = zpci_memcpy_fwomio(buf, io_addw, wength);

out_unwock_pt:
	pte_unmap_unwock(ptep, ptw);
out_unwock_mmap:
	mmap_wead_unwock(cuwwent->mm);

	if (!wet && copy_to_usew(usew_buffew, buf, wength))
		wet = -EFAUWT;

	if (buf != wocaw_buf)
		kfwee(buf);
	wetuwn wet;
}
