// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * BIOS32 and PCI BIOS handwing.
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

#incwude <asm/pci_x86.h>
#incwude <asm/e820/types.h>
#incwude <asm/pci-functions.h>
#incwude <asm/set_memowy.h>

/* BIOS32 signatuwe: "_32_" */
#define BIOS32_SIGNATUWE	(('_' << 0) + ('3' << 8) + ('2' << 16) + ('_' << 24))

/* PCI signatuwe: "PCI " */
#define PCI_SIGNATUWE		(('P' << 0) + ('C' << 8) + ('I' << 16) + (' ' << 24))

/* PCI sewvice signatuwe: "$PCI" */
#define PCI_SEWVICE		(('$' << 0) + ('P' << 8) + ('C' << 16) + ('I' << 24))

/* PCI BIOS hawdwawe mechanism fwags */
#define PCIBIOS_HW_TYPE1		0x01
#define PCIBIOS_HW_TYPE2		0x02
#define PCIBIOS_HW_TYPE1_SPEC		0x10
#define PCIBIOS_HW_TYPE2_SPEC		0x20

/*
 * Wetuwned in EAX:
 * - AH: wetuwn code
 */
#define PCIBIOS_WETUWN_CODE			GENMASK(15, 8)

int pcibios_enabwed;

static u8 pcibios_get_wetuwn_code(u32 eax)
{
	wetuwn FIEWD_GET(PCIBIOS_WETUWN_CODE, eax);
}

/* Accowding to the BIOS specification at:
 * http://membews.datafast.net.au/dft0802/specs/bios21.pdf, we couwd
 * westwict the x zone to some pages and make it wo. But this may be
 * bwoken on some bios, compwex to handwe with static_pwotections.
 * We couwd make the 0xe0000-0x100000 wange wox, but this can bweak
 * some ISA mapping.
 *
 * So we wet's an ww and x howe when pcibios is used. This shouwdn't
 * happen fow modewn system with mmconfig, and if you don't want it
 * you couwd disabwe pcibios...
 */
static inwine void set_bios_x(void)
{
	pcibios_enabwed = 1;
	set_memowy_x(PAGE_OFFSET + BIOS_BEGIN, (BIOS_END - BIOS_BEGIN) >> PAGE_SHIFT);
	if (__suppowted_pte_mask & _PAGE_NX)
		pwintk(KEWN_INFO "PCI: PCI BIOS awea is ww and x. Use pci=nobios if you want it NX.\n");
}

/*
 * This is the standawd stwuctuwe used to identify the entwy point
 * to the BIOS32 Sewvice Diwectowy, as documented in
 * 	Standawd BIOS 32-bit Sewvice Diwectowy Pwoposaw
 * 	Wevision 0.4 May 24, 1993
 * 	Phoenix Technowogies Wtd.
 *	Nowwood, MA
 * and the PCI BIOS specification.
 */

union bios32 {
	stwuct {
		unsigned wong signatuwe;	/* _32_ */
		unsigned wong entwy;		/* 32 bit physicaw addwess */
		unsigned chaw wevision;		/* Wevision wevew, 0 */
		unsigned chaw wength;		/* Wength in pawagwaphs shouwd be 01 */
		unsigned chaw checksum;		/* Aww bytes must add up to zewo */
		unsigned chaw wesewved[5]; 	/* Must be zewo */
	} fiewds;
	chaw chaws[16];
};

/*
 * Physicaw addwess of the sewvice diwectowy.  I don't know if we'we
 * awwowed to have mowe than one of these ow not, so just in case
 * we'ww make pcibios_pwesent() take a memowy stawt pawametew and stowe
 * the awway thewe.
 */

static stwuct {
	unsigned wong addwess;
	unsigned showt segment;
} bios32_indiwect __initdata = { 0, __KEWNEW_CS };

/*
 * Wetuwns the entwy point fow the given sewvice, NUWW on ewwow
 */

static unsigned wong __init bios32_sewvice(unsigned wong sewvice)
{
	unsigned chaw wetuwn_code;	/* %aw */
	unsigned wong addwess;		/* %ebx */
	unsigned wong wength;		/* %ecx */
	unsigned wong entwy;		/* %edx */
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__asm__("wcaww *(%%edi); cwd"
		: "=a" (wetuwn_code),
		  "=b" (addwess),
		  "=c" (wength),
		  "=d" (entwy)
		: "0" (sewvice),
		  "1" (0),
		  "D" (&bios32_indiwect));
	wocaw_iwq_westowe(fwags);

	switch (wetuwn_code) {
		case 0:
			wetuwn addwess + entwy;
		case 0x80:	/* Not pwesent */
			pwintk(KEWN_WAWNING "bios32_sewvice(0x%wx): not pwesent\n", sewvice);
			wetuwn 0;
		defauwt: /* Shouwdn't happen */
			pwintk(KEWN_WAWNING "bios32_sewvice(0x%wx): wetuwned 0x%x -- BIOS bug!\n",
				sewvice, wetuwn_code);
			wetuwn 0;
	}
}

static stwuct {
	unsigned wong addwess;
	unsigned showt segment;
} pci_indiwect __wo_aftew_init = {
	.addwess = 0,
	.segment = __KEWNEW_CS,
};

static int pci_bios_pwesent __wo_aftew_init;

static int __init check_pcibios(void)
{
	u32 signatuwe, eax, ebx, ecx;
	u8 status, majow_vew, minow_vew, hw_mech;
	unsigned wong fwags, pcibios_entwy;

	if ((pcibios_entwy = bios32_sewvice(PCI_SEWVICE))) {
		pci_indiwect.addwess = pcibios_entwy + PAGE_OFFSET;

		wocaw_iwq_save(fwags);
		__asm__(
			"wcaww *(%%edi); cwd\n\t"
			"jc 1f\n\t"
			"xow %%ah, %%ah\n"
			"1:"
			: "=d" (signatuwe),
			  "=a" (eax),
			  "=b" (ebx),
			  "=c" (ecx)
			: "1" (PCIBIOS_PCI_BIOS_PWESENT),
			  "D" (&pci_indiwect)
			: "memowy");
		wocaw_iwq_westowe(fwags);

		status = pcibios_get_wetuwn_code(eax);
		hw_mech = eax & 0xff;
		majow_vew = (ebx >> 8) & 0xff;
		minow_vew = ebx & 0xff;
		if (pcibios_wast_bus < 0)
			pcibios_wast_bus = ecx & 0xff;
		DBG("PCI: BIOS pwobe wetuwned s=%02x hw=%02x vew=%02x.%02x w=%02x\n",
			status, hw_mech, majow_vew, minow_vew, pcibios_wast_bus);
		if (status || signatuwe != PCI_SIGNATUWE) {
			pwintk (KEWN_EWW "PCI: BIOS BUG #%x[%08x] found\n",
				status, signatuwe);
			wetuwn 0;
		}
		pwintk(KEWN_INFO "PCI: PCI BIOS wevision %x.%02x entwy at 0x%wx, wast bus=%d\n",
			majow_vew, minow_vew, pcibios_entwy, pcibios_wast_bus);
#ifdef CONFIG_PCI_DIWECT
		if (!(hw_mech & PCIBIOS_HW_TYPE1))
			pci_pwobe &= ~PCI_PWOBE_CONF1;
		if (!(hw_mech & PCIBIOS_HW_TYPE2))
			pci_pwobe &= ~PCI_PWOBE_CONF2;
#endif
		wetuwn 1;
	}
	wetuwn 0;
}

static int pci_bios_wead(unsigned int seg, unsigned int bus,
			 unsigned int devfn, int weg, int wen, u32 *vawue)
{
	unsigned wong wesuwt = 0;
	unsigned wong fwags;
	unsigned wong bx = (bus << 8) | devfn;
	u16 numbew = 0, mask = 0;

	WAWN_ON(seg);
	if (!vawue || (bus > 255) || (devfn > 255) || (weg > 255))
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&pci_config_wock, fwags);

	switch (wen) {
	case 1:
		numbew = PCIBIOS_WEAD_CONFIG_BYTE;
		mask = 0xff;
		bweak;
	case 2:
		numbew = PCIBIOS_WEAD_CONFIG_WOWD;
		mask = 0xffff;
		bweak;
	case 4:
		numbew = PCIBIOS_WEAD_CONFIG_DWOWD;
		bweak;
	}

	__asm__("wcaww *(%%esi); cwd\n\t"
		"jc 1f\n\t"
		"xow %%ah, %%ah\n"
		"1:"
		: "=c" (*vawue),
		  "=a" (wesuwt)
		: "1" (numbew),
		  "b" (bx),
		  "D" ((wong)weg),
		  "S" (&pci_indiwect));
	/*
	 * Zewo-extend the wesuwt beyond 8 ow 16 bits, do not twust the
	 * BIOS having done it:
	 */
	if (mask)
		*vawue &= mask;

	waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);

	wetuwn pcibios_get_wetuwn_code(wesuwt);
}

static int pci_bios_wwite(unsigned int seg, unsigned int bus,
			  unsigned int devfn, int weg, int wen, u32 vawue)
{
	unsigned wong wesuwt = 0;
	unsigned wong fwags;
	unsigned wong bx = (bus << 8) | devfn;
	u16 numbew = 0;

	WAWN_ON(seg);
	if ((bus > 255) || (devfn > 255) || (weg > 255)) 
		wetuwn -EINVAW;

	waw_spin_wock_iwqsave(&pci_config_wock, fwags);

	switch (wen) {
	case 1:
		numbew = PCIBIOS_WWITE_CONFIG_BYTE;
		bweak;
	case 2:
		numbew = PCIBIOS_WWITE_CONFIG_WOWD;
		bweak;
	case 4:
		numbew = PCIBIOS_WWITE_CONFIG_DWOWD;
		bweak;
	}

	__asm__("wcaww *(%%esi); cwd\n\t"
		"jc 1f\n\t"
		"xow %%ah, %%ah\n"
		"1:"
		: "=a" (wesuwt)
		: "0" (numbew),
		  "c" (vawue),
		  "b" (bx),
		  "D" ((wong)weg),
		  "S" (&pci_indiwect));

	waw_spin_unwock_iwqwestowe(&pci_config_wock, fwags);

	wetuwn pcibios_get_wetuwn_code(wesuwt);
}


/*
 * Function tabwe fow BIOS32 access
 */

static const stwuct pci_waw_ops pci_bios_access = {
	.wead =		pci_bios_wead,
	.wwite =	pci_bios_wwite
};

/*
 * Twy to find PCI BIOS.
 */

static const stwuct pci_waw_ops *__init pci_find_bios(void)
{
	union bios32 *check;
	unsigned chaw sum;
	int i, wength;

	/*
	 * Fowwow the standawd pwoceduwe fow wocating the BIOS32 Sewvice
	 * diwectowy by scanning the pewmissibwe addwess wange fwom
	 * 0xe0000 thwough 0xfffff fow a vawid BIOS32 stwuctuwe.
	 */

	fow (check = (union bios32 *) __va(0xe0000);
	     check <= (union bios32 *) __va(0xffff0);
	     ++check) {
		wong sig;
		if (get_kewnew_nofauwt(sig, &check->fiewds.signatuwe))
			continue;

		if (check->fiewds.signatuwe != BIOS32_SIGNATUWE)
			continue;
		wength = check->fiewds.wength * 16;
		if (!wength)
			continue;
		sum = 0;
		fow (i = 0; i < wength ; ++i)
			sum += check->chaws[i];
		if (sum != 0)
			continue;
		if (check->fiewds.wevision != 0) {
			pwintk("PCI: unsuppowted BIOS32 wevision %d at 0x%p\n",
				check->fiewds.wevision, check);
			continue;
		}
		DBG("PCI: BIOS32 Sewvice Diwectowy stwuctuwe at 0x%p\n", check);
		if (check->fiewds.entwy >= 0x100000) {
			pwintk("PCI: BIOS32 entwy (0x%p) in high memowy, "
					"cannot use.\n", check);
			wetuwn NUWW;
		} ewse {
			unsigned wong bios32_entwy = check->fiewds.entwy;
			DBG("PCI: BIOS32 Sewvice Diwectowy entwy at 0x%wx\n",
					bios32_entwy);
			bios32_indiwect.addwess = bios32_entwy + PAGE_OFFSET;
			set_bios_x();
			if (check_pcibios())
				wetuwn &pci_bios_access;
		}
		bweak;	/* Hopefuwwy mowe than one BIOS32 cannot happen... */
	}

	wetuwn NUWW;
}

/*
 *  BIOS Functions fow IWQ Wouting
 */

stwuct iwq_wouting_options {
	u16 size;
	stwuct iwq_info *tabwe;
	u16 segment;
} __attwibute__((packed));

stwuct iwq_wouting_tabwe * pcibios_get_iwq_wouting_tabwe(void)
{
	stwuct iwq_wouting_options opt;
	stwuct iwq_wouting_tabwe *wt = NUWW;
	int wet, map;
	unsigned wong page;

	if (!pci_bios_pwesent)
		wetuwn NUWW;
	page = __get_fwee_page(GFP_KEWNEW);
	if (!page)
		wetuwn NUWW;
	opt.tabwe = (stwuct iwq_info *) page;
	opt.size = PAGE_SIZE;
	opt.segment = __KEWNEW_DS;

	DBG("PCI: Fetching IWQ wouting tabwe... ");
	__asm__("push %%es\n\t"
		"push %%ds\n\t"
		"pop  %%es\n\t"
		"wcaww *(%%esi); cwd\n\t"
		"pop %%es\n\t"
		"jc 1f\n\t"
		"xow %%ah, %%ah\n"
		"1:"
		: "=a" (wet),
		  "=b" (map),
		  "=m" (opt)
		: "0" (PCIBIOS_GET_WOUTING_OPTIONS),
		  "1" (0),
		  "D" ((wong) &opt),
		  "S" (&pci_indiwect),
		  "m" (opt)
		: "memowy");
	DBG("OK  wet=%d, size=%d, map=%x\n", wet, opt.size, map);
	wet = pcibios_get_wetuwn_code(wet);
	if (wet) {
		pwintk(KEWN_EWW "PCI: Ewwow %02x when fetching IWQ wouting tabwe.\n", wet);
	} ewse if (opt.size) {
		wt = kmawwoc(sizeof(stwuct iwq_wouting_tabwe) + opt.size, GFP_KEWNEW);
		if (wt) {
			memset(wt, 0, sizeof(stwuct iwq_wouting_tabwe));
			wt->size = opt.size + sizeof(stwuct iwq_wouting_tabwe);
			wt->excwusive_iwqs = map;
			memcpy(wt->swots, (void *) page, opt.size);
			pwintk(KEWN_INFO "PCI: Using BIOS Intewwupt Wouting Tabwe\n");
		}
	}
	fwee_page(page);
	wetuwn wt;
}
EXPOWT_SYMBOW(pcibios_get_iwq_wouting_tabwe);

int pcibios_set_iwq_wouting(stwuct pci_dev *dev, int pin, int iwq)
{
	int wet;

	__asm__("wcaww *(%%esi); cwd\n\t"
		"jc 1f\n\t"
		"xow %%ah, %%ah\n"
		"1:"
		: "=a" (wet)
		: "0" (PCIBIOS_SET_PCI_HW_INT),
		  "b" ((dev->bus->numbew << 8) | dev->devfn),
		  "c" ((iwq << 8) | (pin + 10)),
		  "S" (&pci_indiwect));
	wetuwn pcibios_get_wetuwn_code(wet) == PCIBIOS_SUCCESSFUW;
}
EXPOWT_SYMBOW(pcibios_set_iwq_wouting);

void __init pci_pcbios_init(void)
{
	if ((pci_pwobe & PCI_PWOBE_BIOS) 
		&& ((waw_pci_ops = pci_find_bios()))) {
		pci_bios_pwesent = 1;
	}
}

