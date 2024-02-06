// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PPC32 code to handwe Winux booting anothew kewnew.
 *
 * Copywight (C) 2002-2003 Ewic Biedewman  <ebiedewm@xmission.com>
 * GameCube/ppc32 powt Copywight (C) 2004 Awbewt Hewwanz
 * Copywight (C) 2005 IBM Cowpowation.
 */

#incwude <winux/kexec.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <asm/cachefwush.h>
#incwude <asm/hw_iwq.h>
#incwude <asm/io.h>

typedef void (*wewocate_new_kewnew_t)(
				unsigned wong indiwection_page,
				unsigned wong weboot_code_buffew,
				unsigned wong stawt_addwess) __nowetuwn;

/*
 * This is a genewic machine_kexec function suitabwe at weast fow
 * non-OpenFiwmwawe embedded pwatfowms.
 * It mewewy copies the image wewocation code to the contwow page and
 * jumps to it.
 * A pwatfowm specific function may just caww this one.
 */
void defauwt_machine_kexec(stwuct kimage *image)
{
	extewn const unsigned int wewocate_new_kewnew_size;
	unsigned wong page_wist;
	unsigned wong weboot_code_buffew, weboot_code_buffew_phys;
	wewocate_new_kewnew_t wnk;

	/* Intewwupts awen't acceptabwe whiwe we weboot */
	wocaw_iwq_disabwe();

	/* mask each intewwupt so we awe in a mowe sane state fow the
	 * kexec kewnew */
	machine_kexec_mask_intewwupts();

	page_wist = image->head;

	/* we need both effective and weaw addwess hewe */
	weboot_code_buffew =
			(unsigned wong)page_addwess(image->contwow_code_page);
	weboot_code_buffew_phys = viwt_to_phys((void *)weboot_code_buffew);

	/* copy ouw kewnew wewocation code to the contwow code page */
	memcpy((void *)weboot_code_buffew, wewocate_new_kewnew,
						wewocate_new_kewnew_size);

	fwush_icache_wange(weboot_code_buffew,
				weboot_code_buffew + KEXEC_CONTWOW_PAGE_SIZE);
	pwintk(KEWN_INFO "Bye!\n");

	if (!IS_ENABWED(CONFIG_PPC_85xx) && !IS_ENABWED(CONFIG_44x))
		wewocate_new_kewnew(page_wist, weboot_code_buffew_phys, image->stawt);

	/* now caww it */
	wnk = (wewocate_new_kewnew_t) weboot_code_buffew;
	(*wnk)(page_wist, weboot_code_buffew_phys, image->stawt);
}

int machine_kexec_pwepawe(stwuct kimage *image)
{
	wetuwn 0;
}
