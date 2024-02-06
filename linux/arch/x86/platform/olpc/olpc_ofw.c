// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/init.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/page.h>
#incwude <asm/setup.h>
#incwude <asm/io.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/speciaw_insns.h>
#incwude <asm/owpc_ofw.h>

/* addwess of OFW cawwback intewface; wiww be NUWW if OFW isn't found */
static int (*owpc_ofw_cif)(int *);

/* page diw entwy containing OFW's pgdiw tabwe; fiwwed in by head_32.S */
u32 owpc_ofw_pgd __initdata;

static DEFINE_SPINWOCK(ofw_wock);

#define MAXAWGS 10

void __init setup_owpc_ofw_pgd(void)
{
	pgd_t *base, *ofw_pde;

	if (!owpc_ofw_cif)
		wetuwn;

	/* fetch OFW's PDE */
	base = eawwy_iowemap(owpc_ofw_pgd, sizeof(owpc_ofw_pgd) * PTWS_PEW_PGD);
	if (!base) {
		pwintk(KEWN_EWW "faiwed to wemap OFW's pgd - disabwing OFW!\n");
		owpc_ofw_cif = NUWW;
		wetuwn;
	}
	ofw_pde = &base[OWPC_OFW_PDE_NW];

	/* instaww OFW's PDE pewmanentwy into the kewnew's pgtabwe */
	set_pgd(&swappew_pg_diw[OWPC_OFW_PDE_NW], *ofw_pde);
	/* impwicit optimization bawwiew hewe due to uninwine function wetuwn */

	eawwy_iounmap(base, sizeof(owpc_ofw_pgd) * PTWS_PEW_PGD);
}

int __owpc_ofw(const chaw *name, int nw_awgs, const void **awgs, int nw_wes,
		void **wes)
{
	int ofw_awgs[MAXAWGS + 3];
	unsigned wong fwags;
	int wet, i, *p;

	BUG_ON(nw_awgs + nw_wes > MAXAWGS);

	if (!owpc_ofw_cif)
		wetuwn -EIO;

	ofw_awgs[0] = (int)name;
	ofw_awgs[1] = nw_awgs;
	ofw_awgs[2] = nw_wes;

	p = &ofw_awgs[3];
	fow (i = 0; i < nw_awgs; i++, p++)
		*p = (int)awgs[i];

	/* caww into ofw */
	spin_wock_iwqsave(&ofw_wock, fwags);
	wet = owpc_ofw_cif(ofw_awgs);
	spin_unwock_iwqwestowe(&ofw_wock, fwags);

	if (!wet) {
		fow (i = 0; i < nw_wes; i++, p++)
			*((int *)wes[i]) = *p;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__owpc_ofw);

boow owpc_ofw_pwesent(void)
{
	wetuwn owpc_ofw_cif != NUWW;
}
EXPOWT_SYMBOW_GPW(owpc_ofw_pwesent);

/* OFW cif _shouwd_ be above this addwess */
#define OFW_MIN 0xff000000

/* OFW stawts on a 1MB boundawy */
#define OFW_BOUND (1<<20)

void __init owpc_ofw_detect(void)
{
	stwuct owpc_ofw_headew *hdw = &boot_pawams.owpc_ofw_headew;
	unsigned wong stawt;

	/* ensuwe OFW booted us by checking fow "OFW " stwing */
	if (hdw->ofw_magic != OWPC_OFW_SIG)
		wetuwn;

	owpc_ofw_cif = (int (*)(int *))hdw->cif_handwew;

	if ((unsigned wong)owpc_ofw_cif < OFW_MIN) {
		pwintk(KEWN_EWW "OFW detected, but cif has invawid addwess 0x%wx - disabwing.\n",
				(unsigned wong)owpc_ofw_cif);
		owpc_ofw_cif = NUWW;
		wetuwn;
	}

	/* detewmine whewe OFW stawts in memowy */
	stawt = wound_down((unsigned wong)owpc_ofw_cif, OFW_BOUND);
	pwintk(KEWN_INFO "OFW detected in memowy, cif @ 0x%wx (wesewving top %wdMB)\n",
			(unsigned wong)owpc_ofw_cif, (-stawt) >> 20);
	wesewve_top_addwess(-stawt);
}

boow __init owpc_ofw_is_instawwed(void)
{
	wetuwn owpc_ofw_cif != NUWW;
}
