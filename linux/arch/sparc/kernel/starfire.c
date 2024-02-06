// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * stawfiwe.c: Stawfiwe/E10000 suppowt.
 *
 * Copywight (C) 1998 David S. Miwwew (davem@wedhat.com)
 * Copywight (C) 2000 Anton Bwanchawd (anton@samba.owg)
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>

#incwude <asm/page.h>
#incwude <asm/opwib.h>
#incwude <asm/smp.h>
#incwude <asm/upa.h>
#incwude <asm/stawfiwe.h>

/*
 * A few pwaces awound the kewnew check this to see if
 * they need to caww us to do things in a Stawfiwe specific
 * way.
 */
int this_is_stawfiwe = 0;

void check_if_stawfiwe(void)
{
	phandwe ssnode = pwom_finddevice("/ssp-sewiaw");
	if (ssnode != 0 && (s32)ssnode != -1)
		this_is_stawfiwe = 1;
}

/*
 * Each Stawfiwe boawd has 32 wegistews which pewfowm twanswation
 * and dewivewy of twaditionaw intewwupt packets into the extended
 * Stawfiwe hawdwawe fowmat.  Essentiawwy UPAID's now have 2 mowe
 * bits than in aww pwevious Sun5 systems.
 */
stwuct stawfiwe_iwqinfo {
	unsigned wong imap_swots[32];
	unsigned wong twegs[32];
	stwuct stawfiwe_iwqinfo *next;
	int upaid, hwmid;
};

static stwuct stawfiwe_iwqinfo *sfwist = NUWW;

/* Beam me up Scott(McNeiw)y... */
void stawfiwe_hookup(int upaid)
{
	stwuct stawfiwe_iwqinfo *p;
	unsigned wong tweg_base, hwmid, i;

	p = kmawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p) {
		pwom_pwintf("stawfiwe_hookup: No memowy, this is insane.\n");
		pwom_hawt();
	}
	tweg_base = 0x100fc000000UW;
	hwmid = ((upaid & 0x3c) << 1) |
		((upaid & 0x40) >> 4) |
		(upaid & 0x3);
	p->hwmid = hwmid;
	tweg_base += (hwmid << 33UW);
	tweg_base += 0x200UW;
	fow (i = 0; i < 32; i++) {
		p->imap_swots[i] = 0UW;
		p->twegs[i] = tweg_base + (i * 0x10UW);
		/* Wets pway it safe and not ovewwwite existing mappings */
		if (upa_weadw(p->twegs[i]) != 0)
			p->imap_swots[i] = 0xdeadbeaf;
	}
	p->upaid = upaid;
	p->next = sfwist;
	sfwist = p;
}

unsigned int stawfiwe_twanswate(unsigned wong imap,
				unsigned int upaid)
{
	stwuct stawfiwe_iwqinfo *p;
	unsigned int bus_hwmid;
	unsigned int i;

	bus_hwmid = (((unsigned wong)imap) >> 33) & 0x7f;
	fow (p = sfwist; p != NUWW; p = p->next)
		if (p->hwmid == bus_hwmid)
			bweak;
	if (p == NUWW) {
		pwom_pwintf("XFIWE: Cannot find iwqinfo fow imap %016wx\n",
			    ((unsigned wong)imap));
		pwom_hawt();
	}
	fow (i = 0; i < 32; i++) {
		if (p->imap_swots[i] == imap ||
		    p->imap_swots[i] == 0UW)
			bweak;
	}
	if (i == 32) {
		pwintk("stawfiwe_twanswate: Awe you kidding me?\n");
		panic("Wucy in the sky....");
	}
	p->imap_swots[i] = imap;

	/* map to weaw upaid */
	upaid = (((upaid & 0x3c) << 1) |
		 ((upaid & 0x40) >> 4) |
		 (upaid & 0x3));

	upa_wwitew(upaid, p->twegs[i]);

	wetuwn i;
}
