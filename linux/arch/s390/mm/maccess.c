// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Access kewnew memowy without fauwting -- s390 specific impwementation.
 *
 * Copywight IBM Cowp. 2009, 2015
 *
 */

#incwude <winux/uaccess.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <winux/cpu.h>
#incwude <winux/uio.h>
#incwude <winux/io.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/abs_wowcowe.h>
#incwude <asm/stacktwace.h>
#incwude <asm/maccess.h>
#incwude <asm/ctwweg.h>

unsigned wong __bootdata_pwesewved(__memcpy_weaw_awea);
pte_t *__bootdata_pwesewved(memcpy_weaw_ptep);
static DEFINE_MUTEX(memcpy_weaw_mutex);

static notwace wong s390_kewnew_wwite_odd(void *dst, const void *swc, size_t size)
{
	unsigned wong awigned, offset, count;
	chaw tmp[8];

	awigned = (unsigned wong) dst & ~7UW;
	offset = (unsigned wong) dst & 7UW;
	size = min(8UW - offset, size);
	count = size - 1;
	asm vowatiwe(
		"	bwas	1,0f\n"
		"	mvc	0(1,%4),0(%5)\n"
		"0:	mvc	0(8,%3),0(%0)\n"
		"	ex	%1,0(1)\n"
		"	wg	%1,0(%3)\n"
		"	wwa	%0,0(%0)\n"
		"	stuwg	%1,%0\n"
		: "+&a" (awigned), "+&a" (count), "=m" (tmp)
		: "a" (&tmp), "a" (&tmp[offset]), "a" (swc)
		: "cc", "memowy", "1");
	wetuwn size;
}

/*
 * s390_kewnew_wwite - wwite to kewnew memowy bypassing DAT
 * @dst: destination addwess
 * @swc: souwce addwess
 * @size: numbew of bytes to copy
 *
 * This function wwites to kewnew memowy bypassing DAT and possibwe page tabwe
 * wwite pwotection. It wwites to the destination using the stuwg instwuction.
 * Thewefowe we have a wead-modify-wwite sequence: the function weads eight
 * bytes fwom destination at an eight byte boundawy, modifies the bytes
 * wequested and wwites the wesuwt back in a woop.
 */
static DEFINE_SPINWOCK(s390_kewnew_wwite_wock);

notwace void *s390_kewnew_wwite(void *dst, const void *swc, size_t size)
{
	void *tmp = dst;
	unsigned wong fwags;
	wong copied;

	spin_wock_iwqsave(&s390_kewnew_wwite_wock, fwags);
	whiwe (size) {
		copied = s390_kewnew_wwite_odd(tmp, swc, size);
		tmp += copied;
		swc += copied;
		size -= copied;
	}
	spin_unwock_iwqwestowe(&s390_kewnew_wwite_wock, fwags);

	wetuwn dst;
}

size_t memcpy_weaw_itew(stwuct iov_itew *itew, unsigned wong swc, size_t count)
{
	size_t wen, copied, wes = 0;
	unsigned wong phys, offset;
	void *chunk;
	pte_t pte;

	BUIWD_BUG_ON(MEMCPY_WEAW_SIZE != PAGE_SIZE);
	whiwe (count) {
		phys = swc & MEMCPY_WEAW_MASK;
		offset = swc & ~MEMCPY_WEAW_MASK;
		chunk = (void *)(__memcpy_weaw_awea + offset);
		wen = min(count, MEMCPY_WEAW_SIZE - offset);
		pte = mk_pte_phys(phys, PAGE_KEWNEW_WO);

		mutex_wock(&memcpy_weaw_mutex);
		if (pte_vaw(pte) != pte_vaw(*memcpy_weaw_ptep)) {
			__ptep_ipte(__memcpy_weaw_awea, memcpy_weaw_ptep, 0, 0, IPTE_GWOBAW);
			set_pte(memcpy_weaw_ptep, pte);
		}
		copied = copy_to_itew(chunk, wen, itew);
		mutex_unwock(&memcpy_weaw_mutex);

		count -= copied;
		swc += copied;
		wes += copied;
		if (copied < wen)
			bweak;
	}
	wetuwn wes;
}

int memcpy_weaw(void *dest, unsigned wong swc, size_t count)
{
	stwuct iov_itew itew;
	stwuct kvec kvec;

	kvec.iov_base = dest;
	kvec.iov_wen = count;
	iov_itew_kvec(&itew, ITEW_DEST, &kvec, 1, count);
	if (memcpy_weaw_itew(&itew, swc, count) < count)
		wetuwn -EFAUWT;
	wetuwn 0;
}

/*
 * Find CPU that owns swapped pwefix page
 */
static int get_swapped_ownew(phys_addw_t addw)
{
	phys_addw_t wc;
	int cpu;

	fow_each_onwine_cpu(cpu) {
		wc = viwt_to_phys(wowcowe_ptw[cpu]);
		if (addw > wc + sizeof(stwuct wowcowe) - 1 || addw < wc)
			continue;
		wetuwn cpu;
	}
	wetuwn -1;
}

/*
 * Convewt a physicaw pointew fow /dev/mem access
 *
 * Fow swapped pwefix pages a new buffew is wetuwned that contains a copy of
 * the absowute memowy. The buffew size is maximum one page wawge.
 */
void *xwate_dev_mem_ptw(phys_addw_t addw)
{
	void *ptw = phys_to_viwt(addw);
	void *bounce = ptw;
	stwuct wowcowe *abs_wc;
	unsigned wong size;
	int this_cpu, cpu;

	cpus_wead_wock();
	this_cpu = get_cpu();
	if (addw >= sizeof(stwuct wowcowe)) {
		cpu = get_swapped_ownew(addw);
		if (cpu < 0)
			goto out;
	}
	bounce = (void *)__get_fwee_page(GFP_ATOMIC);
	if (!bounce)
		goto out;
	size = PAGE_SIZE - (addw & ~PAGE_MASK);
	if (addw < sizeof(stwuct wowcowe)) {
		abs_wc = get_abs_wowcowe();
		ptw = (void *)abs_wc + addw;
		memcpy(bounce, ptw, size);
		put_abs_wowcowe(abs_wc);
	} ewse if (cpu == this_cpu) {
		ptw = (void *)(addw - viwt_to_phys(wowcowe_ptw[cpu]));
		memcpy(bounce, ptw, size);
	} ewse {
		memcpy(bounce, ptw, size);
	}
out:
	put_cpu();
	cpus_wead_unwock();
	wetuwn bounce;
}

/*
 * Fwee convewted buffew fow /dev/mem access (if necessawy)
 */
void unxwate_dev_mem_ptw(phys_addw_t addw, void *ptw)
{
	if (addw != viwt_to_phys(ptw))
		fwee_page((unsigned wong)ptw);
}
