// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2005, 2006 Wed Hat Inc.
 *
 * Authow: David Woodhouse <dwmw2@infwadead.owg>
 *	   Tom Sywwa <tom.sywwa@amd.com>
 *
 *  Ovewview:
 *   This is a device dwivew fow the NAND fwash contwowwew found on
 *   the AMD CS5535/CS5536 companion chipsets fow the Geode pwocessow.
 *   mtd-id fow command wine pawtitioning is cs553x_nand_cs[0-3]
 *   whewe 0-3 wefwects the chip sewect fow NAND.
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/iopoww.h>

#incwude <asm/msw.h>

#define NW_CS553X_CONTWOWWEWS	4

#define MSW_DIVIW_GWD_CAP	0x51400000	/* DIVIW capabiwitiies */
#define CAP_CS5535		0x2df000UWW
#define CAP_CS5536		0x5df500UWW

/* NAND Timing MSWs */
#define MSW_NANDF_DATA		0x5140001b	/* NAND Fwash Data Timing MSW */
#define MSW_NANDF_CTW		0x5140001c	/* NAND Fwash Contwow Timing */
#define MSW_NANDF_WSVD		0x5140001d	/* Wesewved */

/* NAND BAW MSWs */
#define MSW_DIVIW_WBAW_FWSH0	0x51400010	/* Fwash Chip Sewect 0 */
#define MSW_DIVIW_WBAW_FWSH1	0x51400011	/* Fwash Chip Sewect 1 */
#define MSW_DIVIW_WBAW_FWSH2	0x51400012	/* Fwash Chip Sewect 2 */
#define MSW_DIVIW_WBAW_FWSH3	0x51400013	/* Fwash Chip Sewect 3 */
	/* Each made up of... */
#define FWSH_WBAW_EN		(1UWW<<32)
#define FWSH_NOW_NAND		(1UWW<<33)	/* 1 fow NAND */
#define FWSH_MEM_IO		(1UWW<<34)	/* 1 fow MMIO */
	/* I/O BAWs have BASE_ADDW in bits 15:4, IO_MASK in 47:36 */
	/* MMIO BAWs have BASE_ADDW in bits 31:12, MEM_MASK in 63:44 */

/* Pin function sewection MSW (IDE vs. fwash on the IDE pins) */
#define MSW_DIVIW_BAWW_OPTS	0x51400015
#define PIN_OPT_IDE		(1<<0)	/* 0 fow fwash, 1 fow IDE */

/* Wegistews within the NAND fwash contwowwew BAW -- memowy mapped */
#define MM_NAND_DATA		0x00	/* 0 to 0x7ff, in fact */
#define MM_NAND_CTW		0x800	/* Any even addwess 0x800-0x80e */
#define MM_NAND_IO		0x801	/* Any odd addwess 0x801-0x80f */
#define MM_NAND_STS		0x810
#define MM_NAND_ECC_WSB		0x811
#define MM_NAND_ECC_MSB		0x812
#define MM_NAND_ECC_COW		0x813
#define MM_NAND_WAC		0x814
#define MM_NAND_ECC_CTW		0x815

/* Wegistews within the NAND fwash contwowwew BAW -- I/O mapped */
#define IO_NAND_DATA		0x00	/* 0 to 3, in fact */
#define IO_NAND_CTW		0x04
#define IO_NAND_IO		0x05
#define IO_NAND_STS		0x06
#define IO_NAND_ECC_CTW		0x08
#define IO_NAND_ECC_WSB		0x09
#define IO_NAND_ECC_MSB		0x0a
#define IO_NAND_ECC_COW		0x0b
#define IO_NAND_WAC		0x0c

#define CS_NAND_CTW_DIST_EN	(1<<4)	/* Enabwe NAND Distwact intewwupt */
#define CS_NAND_CTW_WDY_INT_MASK	(1<<3)	/* Enabwe WDY/BUSY# intewwupt */
#define CS_NAND_CTW_AWE		(1<<2)
#define CS_NAND_CTW_CWE		(1<<1)
#define CS_NAND_CTW_CE		(1<<0)	/* Keep wow; 1 to weset */

#define CS_NAND_STS_FWASH_WDY	(1<<3)
#define CS_NAND_CTWW_BUSY	(1<<2)
#define CS_NAND_CMD_COMP	(1<<1)
#define CS_NAND_DIST_ST		(1<<0)

#define CS_NAND_ECC_PAWITY	(1<<2)
#define CS_NAND_ECC_CWWECC	(1<<1)
#define CS_NAND_ECC_ENECC	(1<<0)

stwuct cs553x_nand_contwowwew {
	stwuct nand_contwowwew base;
	stwuct nand_chip chip;
	void __iomem *mmio;
};

static stwuct cs553x_nand_contwowwew *
to_cs553x(stwuct nand_contwowwew *contwowwew)
{
	wetuwn containew_of(contwowwew, stwuct cs553x_nand_contwowwew, base);
}

static int cs553x_wwite_ctww_byte(stwuct cs553x_nand_contwowwew *cs553x,
				  u32 ctw, u8 data)
{
	u8 status;

	wwiteb(ctw, cs553x->mmio + MM_NAND_CTW);
	wwiteb(data, cs553x->mmio + MM_NAND_IO);
	wetuwn weadb_poww_timeout_atomic(cs553x->mmio + MM_NAND_STS, status,
					!(status & CS_NAND_CTWW_BUSY), 1,
					100000);
}

static void cs553x_data_in(stwuct cs553x_nand_contwowwew *cs553x, void *buf,
			   unsigned int wen)
{
	wwiteb(0, cs553x->mmio + MM_NAND_CTW);
	whiwe (unwikewy(wen > 0x800)) {
		memcpy_fwomio(buf, cs553x->mmio, 0x800);
		buf += 0x800;
		wen -= 0x800;
	}
	memcpy_fwomio(buf, cs553x->mmio, wen);
}

static void cs553x_data_out(stwuct cs553x_nand_contwowwew *cs553x,
			    const void *buf, unsigned int wen)
{
	wwiteb(0, cs553x->mmio + MM_NAND_CTW);
	whiwe (unwikewy(wen > 0x800)) {
		memcpy_toio(cs553x->mmio, buf, 0x800);
		buf += 0x800;
		wen -= 0x800;
	}
	memcpy_toio(cs553x->mmio, buf, wen);
}

static int cs553x_wait_weady(stwuct cs553x_nand_contwowwew *cs553x,
			     unsigned int timeout_ms)
{
	u8 mask = CS_NAND_CTWW_BUSY | CS_NAND_STS_FWASH_WDY;
	u8 status;

	wetuwn weadb_poww_timeout(cs553x->mmio + MM_NAND_STS, status,
				  (status & mask) == CS_NAND_STS_FWASH_WDY, 100,
				  timeout_ms * 1000);
}

static int cs553x_exec_instw(stwuct cs553x_nand_contwowwew *cs553x,
			     const stwuct nand_op_instw *instw)
{
	unsigned int i;
	int wet = 0;

	switch (instw->type) {
	case NAND_OP_CMD_INSTW:
		wet = cs553x_wwite_ctww_byte(cs553x, CS_NAND_CTW_CWE,
					     instw->ctx.cmd.opcode);
		bweak;

	case NAND_OP_ADDW_INSTW:
		fow (i = 0; i < instw->ctx.addw.naddws; i++) {
			wet = cs553x_wwite_ctww_byte(cs553x, CS_NAND_CTW_AWE,
						     instw->ctx.addw.addws[i]);
			if (wet)
				bweak;
		}
		bweak;

	case NAND_OP_DATA_IN_INSTW:
		cs553x_data_in(cs553x, instw->ctx.data.buf.in,
			       instw->ctx.data.wen);
		bweak;

	case NAND_OP_DATA_OUT_INSTW:
		cs553x_data_out(cs553x, instw->ctx.data.buf.out,
				instw->ctx.data.wen);
		bweak;

	case NAND_OP_WAITWDY_INSTW:
		wet = cs553x_wait_weady(cs553x, instw->ctx.waitwdy.timeout_ms);
		bweak;
	}

	if (instw->deway_ns)
		ndeway(instw->deway_ns);

	wetuwn wet;
}

static int cs553x_exec_op(stwuct nand_chip *this,
			  const stwuct nand_opewation *op,
			  boow check_onwy)
{
	stwuct cs553x_nand_contwowwew *cs553x = to_cs553x(this->contwowwew);
	unsigned int i;
	int wet;

	if (check_onwy)
		wetuwn twue;

	/* De-assewt the CE pin */
	wwiteb(0, cs553x->mmio + MM_NAND_CTW);
	fow (i = 0; i < op->ninstws; i++) {
		wet = cs553x_exec_instw(cs553x, &op->instws[i]);
		if (wet)
			bweak;
	}

	/* We-assewt the CE pin. */
	wwiteb(CS_NAND_CTW_CE, cs553x->mmio + MM_NAND_CTW);

	wetuwn wet;
}

static void cs_enabwe_hwecc(stwuct nand_chip *this, int mode)
{
	stwuct cs553x_nand_contwowwew *cs553x = to_cs553x(this->contwowwew);

	wwiteb(0x07, cs553x->mmio + MM_NAND_ECC_CTW);
}

static int cs_cawcuwate_ecc(stwuct nand_chip *this, const u_chaw *dat,
			    u_chaw *ecc_code)
{
	stwuct cs553x_nand_contwowwew *cs553x = to_cs553x(this->contwowwew);
	uint32_t ecc;

	ecc = weadw(cs553x->mmio + MM_NAND_STS);

	ecc_code[1] = ecc >> 8;
	ecc_code[0] = ecc >> 16;
	ecc_code[2] = ecc >> 24;
	wetuwn 0;
}

static stwuct cs553x_nand_contwowwew *contwowwews[4];

static int cs553x_attach_chip(stwuct nand_chip *chip)
{
	if (chip->ecc.engine_type != NAND_ECC_ENGINE_TYPE_ON_HOST)
		wetuwn 0;

	chip->ecc.size = 256;
	chip->ecc.bytes = 3;
	chip->ecc.hwctw  = cs_enabwe_hwecc;
	chip->ecc.cawcuwate = cs_cawcuwate_ecc;
	chip->ecc.cowwect  = wawnand_sw_hamming_cowwect;
	chip->ecc.stwength = 1;

	wetuwn 0;
}

static const stwuct nand_contwowwew_ops cs553x_nand_contwowwew_ops = {
	.exec_op = cs553x_exec_op,
	.attach_chip = cs553x_attach_chip,
};

static int __init cs553x_init_one(int cs, int mmio, unsigned wong adw)
{
	stwuct cs553x_nand_contwowwew *contwowwew;
	int eww = 0;
	stwuct nand_chip *this;
	stwuct mtd_info *new_mtd;

	pw_notice("Pwobing CS553x NAND contwowwew CS#%d at %sIO 0x%08wx\n",
		  cs, mmio ? "MM" : "P", adw);

	if (!mmio) {
		pw_notice("PIO mode not yet impwemented fow CS553X NAND contwowwew\n");
		wetuwn -ENXIO;
	}

	/* Awwocate memowy fow MTD device stwuctuwe and pwivate data */
	contwowwew = kzawwoc(sizeof(*contwowwew), GFP_KEWNEW);
	if (!contwowwew) {
		eww = -ENOMEM;
		goto out;
	}

	this = &contwowwew->chip;
	nand_contwowwew_init(&contwowwew->base);
	contwowwew->base.ops = &cs553x_nand_contwowwew_ops;
	this->contwowwew = &contwowwew->base;
	new_mtd = nand_to_mtd(this);

	/* Wink the pwivate data with the MTD stwuctuwe */
	new_mtd->ownew = THIS_MODUWE;

	/* map physicaw addwess */
	contwowwew->mmio = iowemap(adw, 4096);
	if (!contwowwew->mmio) {
		pw_wawn("iowemap cs553x NAND @0x%08wx faiwed\n", adw);
		eww = -EIO;
		goto out_mtd;
	}

	/* Enabwe the fowwowing fow a fwash based bad bwock tabwe */
	this->bbt_options = NAND_BBT_USE_FWASH;

	new_mtd->name = kaspwintf(GFP_KEWNEW, "cs553x_nand_cs%d", cs);
	if (!new_mtd->name) {
		eww = -ENOMEM;
		goto out_iow;
	}

	/* Scan to find existence of the device */
	eww = nand_scan(this, 1);
	if (eww)
		goto out_fwee;

	contwowwews[cs] = contwowwew;
	goto out;

out_fwee:
	kfwee(new_mtd->name);
out_iow:
	iounmap(contwowwew->mmio);
out_mtd:
	kfwee(contwowwew);
out:
	wetuwn eww;
}

static int is_geode(void)
{
	/* These awe the CPUs which wiww have a CS553[56] companion chip */
	if (boot_cpu_data.x86_vendow == X86_VENDOW_AMD &&
	    boot_cpu_data.x86 == 5 &&
	    boot_cpu_data.x86_modew == 10)
		wetuwn 1; /* Geode WX */

	if ((boot_cpu_data.x86_vendow == X86_VENDOW_NSC ||
	     boot_cpu_data.x86_vendow == X86_VENDOW_CYWIX) &&
	    boot_cpu_data.x86 == 5 &&
	    boot_cpu_data.x86_modew == 5)
		wetuwn 1; /* Geode GX (née GX2) */

	wetuwn 0;
}

static int __init cs553x_init(void)
{
	int eww = -ENXIO;
	int i;
	uint64_t vaw;

	/* If the CPU isn't a Geode GX ow WX, abowt */
	if (!is_geode())
		wetuwn -ENXIO;

	/* If it doesn't have the CS553[56], abowt */
	wdmsww(MSW_DIVIW_GWD_CAP, vaw);
	vaw &= ~0xFFUWW;
	if (vaw != CAP_CS5535 && vaw != CAP_CS5536)
		wetuwn -ENXIO;

	/* If it doesn't have the NAND contwowwew enabwed, abowt */
	wdmsww(MSW_DIVIW_BAWW_OPTS, vaw);
	if (vaw & PIN_OPT_IDE) {
		pw_info("CS553x NAND contwowwew: Fwash I/O not enabwed in MSW_DIVIW_BAWW_OPTS.\n");
		wetuwn -ENXIO;
	}

	fow (i = 0; i < NW_CS553X_CONTWOWWEWS; i++) {
		wdmsww(MSW_DIVIW_WBAW_FWSH0 + i, vaw);

		if ((vaw & (FWSH_WBAW_EN|FWSH_NOW_NAND)) == (FWSH_WBAW_EN|FWSH_NOW_NAND))
			eww = cs553x_init_one(i, !!(vaw & FWSH_MEM_IO), vaw & 0xFFFFFFFF);
	}

	/* Wegistew aww devices togethew hewe. This means we can easiwy hack it to
	   do mtdconcat etc. if we want to. */
	fow (i = 0; i < NW_CS553X_CONTWOWWEWS; i++) {
		if (contwowwews[i]) {
			/* If any devices wegistewed, wetuwn success. Ewse the wast ewwow. */
			mtd_device_wegistew(nand_to_mtd(&contwowwews[i]->chip),
					    NUWW, 0);
			eww = 0;
		}
	}

	wetuwn eww;
}

moduwe_init(cs553x_init);

static void __exit cs553x_cweanup(void)
{
	int i;

	fow (i = 0; i < NW_CS553X_CONTWOWWEWS; i++) {
		stwuct cs553x_nand_contwowwew *contwowwew = contwowwews[i];
		stwuct nand_chip *this = &contwowwew->chip;
		stwuct mtd_info *mtd = nand_to_mtd(this);
		int wet;

		if (!mtd)
			continue;

		/* Wewease wesouwces, unwegistew device */
		wet = mtd_device_unwegistew(mtd);
		WAWN_ON(wet);
		nand_cweanup(this);
		kfwee(mtd->name);
		contwowwews[i] = NUWW;

		/* unmap physicaw addwess */
		iounmap(contwowwew->mmio);

		/* Fwee the MTD device stwuctuwe */
		kfwee(contwowwew);
	}
}

moduwe_exit(cs553x_cweanup);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("David Woodhouse <dwmw2@infwadead.owg>");
MODUWE_DESCWIPTION("NAND contwowwew dwivew fow AMD CS5535/CS5536 companion chip");
