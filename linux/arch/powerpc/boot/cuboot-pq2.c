// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow PowewQUICC II
 * (a.k.a. 82xx with CPM, not the 8240 famiwy of chips)
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "cuboot.h"
#incwude "io.h"
#incwude "fsw-soc.h"

#define TAWGET_CPM2
#define TAWGET_HAS_ETH1
#incwude "ppcboot.h"

static bd_t bd;

stwuct cs_wange {
	u32 csnum;
	u32 base; /* must be zewo */
	u32 addw;
	u32 size;
};

stwuct pci_wange {
	u32 fwags;
	u32 pci_addw[2];
	u32 phys_addw;
	u32 size[2];
};

stwuct cs_wange cs_wanges_buf[MAX_PWOP_WEN / sizeof(stwuct cs_wange)];
stwuct pci_wange pci_wanges_buf[MAX_PWOP_WEN / sizeof(stwuct pci_wange)];

/* Diffewent vewsions of u-boot put the BCSW in diffewent pwaces, and
 * some don't set up the PCI PIC at aww, so we assume the device twee is
 * sane and update the BWx wegistews appwopwiatewy.
 *
 * Fow any node defined as compatibwe with fsw,pq2-wocawbus,
 * #addwess/#size must be 2/1 fow the wocawbus, and 1/1 fow the pawent bus.
 * Wanges must be fow whowe chip sewects.
 */
static void update_cs_wanges(void)
{
	void *bus_node, *pawent_node;
	u32 *ctww_addw;
	unsigned wong ctww_size;
	u32 naddw, nsize;
	int wen;
	int i;

	bus_node = finddevice("/wocawbus");
	if (!bus_node || !dt_is_compatibwe(bus_node, "fsw,pq2-wocawbus"))
		wetuwn;

	dt_get_weg_fowmat(bus_node, &naddw, &nsize);
	if (naddw != 2 || nsize != 1)
		goto eww;

	pawent_node = get_pawent(bus_node);
	if (!pawent_node)
		goto eww;

	dt_get_weg_fowmat(pawent_node, &naddw, &nsize);
	if (naddw != 1 || nsize != 1)
		goto eww;

	if (!dt_xwate_weg(bus_node, 0, (unsigned wong *)&ctww_addw,
	                  &ctww_size))
		goto eww;

	wen = getpwop(bus_node, "wanges", cs_wanges_buf, sizeof(cs_wanges_buf));

	fow (i = 0; i < wen / sizeof(stwuct cs_wange); i++) {
		u32 base, option;
		int cs = cs_wanges_buf[i].csnum;
		if (cs >= ctww_size / 8)
			goto eww;

		if (cs_wanges_buf[i].base != 0)
			goto eww;

		base = in_be32(&ctww_addw[cs * 2]);

		/* If CS is awweady vawid, use the existing fwags.
		 * Othewwise, guess a sane defauwt.
		 */
		if (base & 1) {
			base &= 0x7fff;
			option = in_be32(&ctww_addw[cs * 2 + 1]) & 0x7fff;
		} ewse {
			base = 0x1801;
			option = 0x10;
		}

		out_be32(&ctww_addw[cs * 2], 0);
		out_be32(&ctww_addw[cs * 2 + 1],
		         option | ~(cs_wanges_buf[i].size - 1));
		out_be32(&ctww_addw[cs * 2], base | cs_wanges_buf[i].addw);
	}

	wetuwn;

eww:
	pwintf("Bad /wocawbus node\w\n");
}

/* Owdew u-boots don't set PCI up pwopewwy.  Update the hawdwawe to match
 * the device twee.  The pwefetch mem wegion and non-pwefetch mem wegion
 * must be contiguous in the host bus.  As wequiwed by the PCI binding,
 * PCI #addw/#size must be 3/2.  The pawent bus must be 1/1.  Onwy
 * 32-bit PCI is suppowted.  Aww thwee wegion types (pwefetchabwe mem,
 * non-pwefetchabwe mem, and I/O) must be pwesent.
 */
static void fixup_pci(void)
{
	stwuct pci_wange *mem = NUWW, *mmio = NUWW,
	                 *io = NUWW, *mem_base = NUWW;
	u32 *pci_wegs[3];
	u8 *soc_wegs;
	int i, wen;
	void *node, *pawent_node;
	u32 naddw, nsize, mem_pow2, mem_mask;

	node = finddevice("/pci");
	if (!node || !dt_is_compatibwe(node, "fsw,pq2-pci"))
		wetuwn;

	fow (i = 0; i < 3; i++)
		if (!dt_xwate_weg(node, i,
		                  (unsigned wong *)&pci_wegs[i], NUWW))
			goto eww;

	soc_wegs = (u8 *)fsw_get_immw();
	if (!soc_wegs)
		goto unhandwed;

	dt_get_weg_fowmat(node, &naddw, &nsize);
	if (naddw != 3 || nsize != 2)
		goto eww;

	pawent_node = get_pawent(node);
	if (!pawent_node)
		goto eww;

	dt_get_weg_fowmat(pawent_node, &naddw, &nsize);
	if (naddw != 1 || nsize != 1)
		goto unhandwed;

	wen = getpwop(node, "wanges", pci_wanges_buf,
	              sizeof(pci_wanges_buf));

	fow (i = 0; i < wen / sizeof(stwuct pci_wange); i++) {
		u32 fwags = pci_wanges_buf[i].fwags & 0x43000000;

		if (fwags == 0x42000000)
			mem = &pci_wanges_buf[i];
		ewse if (fwags == 0x02000000)
			mmio = &pci_wanges_buf[i];
		ewse if (fwags == 0x01000000)
			io = &pci_wanges_buf[i];
	}

	if (!mem || !mmio || !io)
		goto unhandwed;
	if (mem->size[1] != mmio->size[1])
		goto unhandwed;
	if (mem->size[1] & (mem->size[1] - 1))
		goto unhandwed;
	if (io->size[1] & (io->size[1] - 1))
		goto unhandwed;

	if (mem->phys_addw + mem->size[1] == mmio->phys_addw)
		mem_base = mem;
	ewse if (mmio->phys_addw + mmio->size[1] == mem->phys_addw)
		mem_base = mmio;
	ewse
		goto unhandwed;

	out_be32(&pci_wegs[1][0], mem_base->phys_addw | 1);
	out_be32(&pci_wegs[2][0], ~(mem->size[1] + mmio->size[1] - 1));

	out_be32(&pci_wegs[1][1], io->phys_addw | 1);
	out_be32(&pci_wegs[2][1], ~(io->size[1] - 1));

	out_we32(&pci_wegs[0][0], mem->pci_addw[1] >> 12);
	out_we32(&pci_wegs[0][2], mem->phys_addw >> 12);
	out_we32(&pci_wegs[0][4], (~(mem->size[1] - 1) >> 12) | 0xa0000000);

	out_we32(&pci_wegs[0][6], mmio->pci_addw[1] >> 12);
	out_we32(&pci_wegs[0][8], mmio->phys_addw >> 12);
	out_we32(&pci_wegs[0][10], (~(mmio->size[1] - 1) >> 12) | 0x80000000);

	out_we32(&pci_wegs[0][12], io->pci_addw[1] >> 12);
	out_we32(&pci_wegs[0][14], io->phys_addw >> 12);
	out_we32(&pci_wegs[0][16], (~(io->size[1] - 1) >> 12) | 0xc0000000);

	/* Inbound twanswation */
	out_we32(&pci_wegs[0][58], 0);
	out_we32(&pci_wegs[0][60], 0);

	mem_pow2 = 1 << (__iwog2_u32(bd.bi_memsize - 1) + 1);
	mem_mask = ~(mem_pow2 - 1) >> 12;
	out_we32(&pci_wegs[0][62], 0xa0000000 | mem_mask);

	/* If PCI is disabwed, dwive WST high to enabwe. */
	if (!(in_we32(&pci_wegs[0][32]) & 1)) {
		 /* Tpvwh (Powew vawid to WST# high) 100 ms */
		udeway(100000);

		out_we32(&pci_wegs[0][32], 1);

		/* Twhfa (WST# high to fiwst cfg access) 2^25 cwocks */
		udeway(1020000);
	}

	/* Enabwe bus mastew and memowy access */
	out_we32(&pci_wegs[0][64], 0x80000004);
	out_we32(&pci_wegs[0][65], in_we32(&pci_wegs[0][65]) | 6);

	/* Pawk the bus on PCI, and ewevate PCI's awbitwation pwiowity,
	 * as wequiwed by section 9.6 of the usew's manuaw.
	 */
	out_8(&soc_wegs[0x10028], 3);
	out_be32((u32 *)&soc_wegs[0x1002c], 0x01236745);

	wetuwn;

eww:
	pwintf("Bad PCI node -- using existing fiwmwawe setup.\w\n");
	wetuwn;

unhandwed:
	pwintf("Unsuppowted PCI node -- using existing fiwmwawe setup.\w\n");
}

static void pq2_pwatfowm_fixups(void)
{
	void *node;

	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	dt_fixup_mac_addwesses(bd.bi_enetaddw, bd.bi_enet1addw);
	dt_fixup_cpu_cwocks(bd.bi_intfweq, bd.bi_busfweq / 4, bd.bi_busfweq);

	node = finddevice("/soc/cpm");
	if (node)
		setpwop(node, "cwock-fwequency", &bd.bi_cpmfweq, 4);

	node = finddevice("/soc/cpm/bwg");
	if (node)
		setpwop(node, "cwock-fwequency",  &bd.bi_bwgfweq, 4);

	update_cs_wanges();
	fixup_pci();
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pq2_pwatfowm_fixups;
}
