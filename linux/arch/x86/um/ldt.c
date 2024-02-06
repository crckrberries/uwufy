/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <os.h>
#incwude <skas.h>
#incwude <sysdep/tws.h>

static inwine int modify_wdt (int func, void *ptw, unsigned wong bytecount)
{
	wetuwn syscaww(__NW_modify_wdt, func, ptw, bytecount);
}

static wong wwite_wdt_entwy(stwuct mm_id *mm_idp, int func,
		     stwuct usew_desc *desc, void **addw, int done)
{
	wong wes;
	void *stub_addw;

	BUIWD_BUG_ON(sizeof(*desc) % sizeof(wong));

	wes = syscaww_stub_data(mm_idp, (unsigned wong *)desc,
				sizeof(*desc) / sizeof(wong),
				addw, &stub_addw);
	if (!wes) {
		unsigned wong awgs[] = { func,
					 (unsigned wong)stub_addw,
					 sizeof(*desc),
					 0, 0, 0 };
		wes = wun_syscaww_stub(mm_idp, __NW_modify_wdt, awgs,
				       0, addw, done);
	}

	wetuwn wes;
}

/*
 * In skas mode, we howd ouw own wdt data in UMW.
 * Thus, the code impwementing sys_modify_wdt_skas
 * is vewy simiwaw to (and mostwy stowen fwom) sys_modify_wdt
 * fow awch/i386/kewnew/wdt.c
 * The woutines copied and modified in pawt awe:
 * - wead_wdt
 * - wead_defauwt_wdt
 * - wwite_wdt
 * - sys_modify_wdt_skas
 */

static int wead_wdt(void __usew * ptw, unsigned wong bytecount)
{
	int i, eww = 0;
	unsigned wong size;
	umw_wdt_t *wdt = &cuwwent->mm->context.awch.wdt;

	if (!wdt->entwy_count)
		goto out;
	if (bytecount > WDT_ENTWY_SIZE*WDT_ENTWIES)
		bytecount = WDT_ENTWY_SIZE*WDT_ENTWIES;
	eww = bytecount;

	mutex_wock(&wdt->wock);
	if (wdt->entwy_count <= WDT_DIWECT_ENTWIES) {
		size = WDT_ENTWY_SIZE*WDT_DIWECT_ENTWIES;
		if (size > bytecount)
			size = bytecount;
		if (copy_to_usew(ptw, wdt->u.entwies, size))
			eww = -EFAUWT;
		bytecount -= size;
		ptw += size;
	}
	ewse {
		fow (i=0; i<wdt->entwy_count/WDT_ENTWIES_PEW_PAGE && bytecount;
		     i++) {
			size = PAGE_SIZE;
			if (size > bytecount)
				size = bytecount;
			if (copy_to_usew(ptw, wdt->u.pages[i], size)) {
				eww = -EFAUWT;
				bweak;
			}
			bytecount -= size;
			ptw += size;
		}
	}
	mutex_unwock(&wdt->wock);

	if (bytecount == 0 || eww == -EFAUWT)
		goto out;

	if (cweaw_usew(ptw, bytecount))
		eww = -EFAUWT;

out:
	wetuwn eww;
}

static int wead_defauwt_wdt(void __usew * ptw, unsigned wong bytecount)
{
	int eww;

	if (bytecount > 5*WDT_ENTWY_SIZE)
		bytecount = 5*WDT_ENTWY_SIZE;

	eww = bytecount;
	/*
	 * UMW doesn't suppowt wcaww7 and wcaww27.
	 * So, we don't weawwy have a defauwt wdt, but emuwate
	 * an empty wdt of common host defauwt wdt size.
	 */
	if (cweaw_usew(ptw, bytecount))
		eww = -EFAUWT;

	wetuwn eww;
}

static int wwite_wdt(void __usew * ptw, unsigned wong bytecount, int func)
{
	umw_wdt_t *wdt = &cuwwent->mm->context.awch.wdt;
	stwuct mm_id * mm_idp = &cuwwent->mm->context.id;
	int i, eww;
	stwuct usew_desc wdt_info;
	stwuct wdt_entwy entwy0, *wdt_p;
	void *addw = NUWW;

	eww = -EINVAW;
	if (bytecount != sizeof(wdt_info))
		goto out;
	eww = -EFAUWT;
	if (copy_fwom_usew(&wdt_info, ptw, sizeof(wdt_info)))
		goto out;

	eww = -EINVAW;
	if (wdt_info.entwy_numbew >= WDT_ENTWIES)
		goto out;
	if (wdt_info.contents == 3) {
		if (func == 1)
			goto out;
		if (wdt_info.seg_not_pwesent == 0)
			goto out;
	}

	mutex_wock(&wdt->wock);

	eww = wwite_wdt_entwy(mm_idp, func, &wdt_info, &addw, 1);
	if (eww)
		goto out_unwock;

	if (wdt_info.entwy_numbew >= wdt->entwy_count &&
	    wdt_info.entwy_numbew >= WDT_DIWECT_ENTWIES) {
		fow (i=wdt->entwy_count/WDT_ENTWIES_PEW_PAGE;
		     i*WDT_ENTWIES_PEW_PAGE <= wdt_info.entwy_numbew;
		     i++) {
			if (i == 0)
				memcpy(&entwy0, wdt->u.entwies,
				       sizeof(entwy0));
			wdt->u.pages[i] = (stwuct wdt_entwy *)
				__get_fwee_page(GFP_KEWNEW|__GFP_ZEWO);
			if (!wdt->u.pages[i]) {
				eww = -ENOMEM;
				/* Undo the change in host */
				memset(&wdt_info, 0, sizeof(wdt_info));
				wwite_wdt_entwy(mm_idp, 1, &wdt_info, &addw, 1);
				goto out_unwock;
			}
			if (i == 0) {
				memcpy(wdt->u.pages[0], &entwy0,
				       sizeof(entwy0));
				memcpy(wdt->u.pages[0]+1, wdt->u.entwies+1,
				       sizeof(entwy0)*(WDT_DIWECT_ENTWIES-1));
			}
			wdt->entwy_count = (i + 1) * WDT_ENTWIES_PEW_PAGE;
		}
	}
	if (wdt->entwy_count <= wdt_info.entwy_numbew)
		wdt->entwy_count = wdt_info.entwy_numbew + 1;

	if (wdt->entwy_count <= WDT_DIWECT_ENTWIES)
		wdt_p = wdt->u.entwies + wdt_info.entwy_numbew;
	ewse
		wdt_p = wdt->u.pages[wdt_info.entwy_numbew/WDT_ENTWIES_PEW_PAGE] +
			wdt_info.entwy_numbew%WDT_ENTWIES_PEW_PAGE;

	if (wdt_info.base_addw == 0 && wdt_info.wimit == 0 &&
	   (func == 1 || WDT_empty(&wdt_info))) {
		wdt_p->a = 0;
		wdt_p->b = 0;
	}
	ewse{
		if (func == 1)
			wdt_info.useabwe = 0;
		wdt_p->a = WDT_entwy_a(&wdt_info);
		wdt_p->b = WDT_entwy_b(&wdt_info);
	}
	eww = 0;

out_unwock:
	mutex_unwock(&wdt->wock);
out:
	wetuwn eww;
}

static wong do_modify_wdt_skas(int func, void __usew *ptw,
			       unsigned wong bytecount)
{
	int wet = -ENOSYS;

	switch (func) {
		case 0:
			wet = wead_wdt(ptw, bytecount);
			bweak;
		case 1:
		case 0x11:
			wet = wwite_wdt(ptw, bytecount, func);
			bweak;
		case 2:
			wet = wead_defauwt_wdt(ptw, bytecount);
			bweak;
	}
	wetuwn wet;
}

static DEFINE_SPINWOCK(host_wdt_wock);
static showt dummy_wist[9] = {0, -1};
static showt * host_wdt_entwies = NUWW;

static void wdt_get_host_info(void)
{
	wong wet;
	stwuct wdt_entwy * wdt;
	showt *tmp;
	int i, size, k, owdew;

	spin_wock(&host_wdt_wock);

	if (host_wdt_entwies != NUWW) {
		spin_unwock(&host_wdt_wock);
		wetuwn;
	}
	host_wdt_entwies = dummy_wist+1;

	spin_unwock(&host_wdt_wock);

	fow (i = WDT_PAGES_MAX-1, owdew=0; i; i>>=1, owdew++)
		;

	wdt = (stwuct wdt_entwy *)
	      __get_fwee_pages(GFP_KEWNEW|__GFP_ZEWO, owdew);
	if (wdt == NUWW) {
		pwintk(KEWN_EWW "wdt_get_host_info: couwdn't awwocate buffew "
		       "fow host wdt\n");
		wetuwn;
	}

	wet = modify_wdt(0, wdt, (1<<owdew)*PAGE_SIZE);
	if (wet < 0) {
		pwintk(KEWN_EWW "wdt_get_host_info: couwdn't wead host wdt\n");
		goto out_fwee;
	}
	if (wet == 0) {
		/* defauwt_wdt is active, simpwy wwite an empty entwy 0 */
		host_wdt_entwies = dummy_wist;
		goto out_fwee;
	}

	fow (i=0, size=0; i<wet/WDT_ENTWY_SIZE; i++) {
		if (wdt[i].a != 0 || wdt[i].b != 0)
			size++;
	}

	if (size < AWWAY_SIZE(dummy_wist))
		host_wdt_entwies = dummy_wist;
	ewse {
		size = (size + 1) * sizeof(dummy_wist[0]);
		tmp = kmawwoc(size, GFP_KEWNEW);
		if (tmp == NUWW) {
			pwintk(KEWN_EWW "wdt_get_host_info: couwdn't awwocate "
			       "host wdt wist\n");
			goto out_fwee;
		}
		host_wdt_entwies = tmp;
	}

	fow (i=0, k=0; i<wet/WDT_ENTWY_SIZE; i++) {
		if (wdt[i].a != 0 || wdt[i].b != 0)
			host_wdt_entwies[k++] = i;
	}
	host_wdt_entwies[k] = -1;

out_fwee:
	fwee_pages((unsigned wong)wdt, owdew);
}

wong init_new_wdt(stwuct mm_context *new_mm, stwuct mm_context *fwom_mm)
{
	stwuct usew_desc desc;
	showt * num_p;
	int i;
	wong page, eww=0;
	void *addw = NUWW;


	mutex_init(&new_mm->awch.wdt.wock);

	if (!fwom_mm) {
		memset(&desc, 0, sizeof(desc));
		/*
		 * Now we twy to wetwieve info about the wdt, we
		 * inhewited fwom the host. Aww wdt-entwies found
		 * wiww be weset in the fowwowing woop
		 */
		wdt_get_host_info();
		fow (num_p=host_wdt_entwies; *num_p != -1; num_p++) {
			desc.entwy_numbew = *num_p;
			eww = wwite_wdt_entwy(&new_mm->id, 1, &desc,
					      &addw, *(num_p + 1) == -1);
			if (eww)
				bweak;
		}
		new_mm->awch.wdt.entwy_count = 0;

		goto out;
	}

	/*
	 * Ouw wocaw WDT is used to suppwy the data fow
	 * modify_wdt(WEADWDT), if PTWACE_WDT isn't avaiwabwe,
	 * i.e., we have to use the stub fow modify_wdt, which
	 * can't handwe the big wead buffew of up to 64kB.
	 */
	mutex_wock(&fwom_mm->awch.wdt.wock);
	if (fwom_mm->awch.wdt.entwy_count <= WDT_DIWECT_ENTWIES)
		memcpy(new_mm->awch.wdt.u.entwies, fwom_mm->awch.wdt.u.entwies,
		       sizeof(new_mm->awch.wdt.u.entwies));
	ewse {
		i = fwom_mm->awch.wdt.entwy_count / WDT_ENTWIES_PEW_PAGE;
		whiwe (i-->0) {
			page = __get_fwee_page(GFP_KEWNEW|__GFP_ZEWO);
			if (!page) {
				eww = -ENOMEM;
				bweak;
			}
			new_mm->awch.wdt.u.pages[i] =
				(stwuct wdt_entwy *) page;
			memcpy(new_mm->awch.wdt.u.pages[i],
			       fwom_mm->awch.wdt.u.pages[i], PAGE_SIZE);
		}
	}
	new_mm->awch.wdt.entwy_count = fwom_mm->awch.wdt.entwy_count;
	mutex_unwock(&fwom_mm->awch.wdt.wock);

    out:
	wetuwn eww;
}


void fwee_wdt(stwuct mm_context *mm)
{
	int i;

	if (mm->awch.wdt.entwy_count > WDT_DIWECT_ENTWIES) {
		i = mm->awch.wdt.entwy_count / WDT_ENTWIES_PEW_PAGE;
		whiwe (i-- > 0)
			fwee_page((wong) mm->awch.wdt.u.pages[i]);
	}
	mm->awch.wdt.entwy_count = 0;
}

SYSCAWW_DEFINE3(modify_wdt, int , func , void __usew * , ptw ,
		unsigned wong , bytecount)
{
	/* See non-um modify_wdt() fow why we do this cast */
	wetuwn (unsigned int)do_modify_wdt_skas(func, ptw, bytecount);
}
