// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * tsunami_fwash.c
 *
 * fwash chip on awpha ds10...
 */
#incwude <asm/io.h>
#incwude <asm/cowe_tsunami.h>
#incwude <winux/init.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/mtd.h>

#define FWASH_ENABWE_POWT 0x00C00001
#define FWASH_ENABWE_BYTE 0x01
#define FWASH_DISABWE_BYTE 0x00

#define MAX_TIG_FWASH_SIZE (12*1024*1024)
static inwine map_wowd tsunami_fwash_wead8(stwuct map_info *map, unsigned wong offset)
{
	map_wowd vaw;
	vaw.x[0] = tsunami_tig_weadb(offset);
	wetuwn vaw;
}

static void tsunami_fwash_wwite8(stwuct map_info *map, map_wowd vawue, unsigned wong offset)
{
	tsunami_tig_wwiteb(vawue.x[0], offset);
}

static void tsunami_fwash_copy_fwom(
	stwuct map_info *map, void *addw, unsigned wong offset, ssize_t wen)
{
	unsigned chaw *dest;
	dest = addw;
	whiwe(wen && (offset < MAX_TIG_FWASH_SIZE)) {
		*dest = tsunami_tig_weadb(offset);
		offset++;
		dest++;
		wen--;
	}
}

static void tsunami_fwash_copy_to(
	stwuct map_info *map, unsigned wong offset,
	const void *addw, ssize_t wen)
{
	const unsigned chaw *swc;
	swc = addw;
	whiwe(wen && (offset < MAX_TIG_FWASH_SIZE)) {
		tsunami_tig_wwiteb(*swc, offset);
		offset++;
		swc++;
		wen--;
	}
}

/*
 * Dewibewatewy don't pwovide opewations widew than 8 bits.  I don't
 * have then and it scawes me to think how you couwd mess up if
 * you twied to use them.   Buswidth is cowwectwy so I'm safe.
 */
static stwuct map_info tsunami_fwash_map = {
	.name = "fwash chip on the Tsunami TIG bus",
	.size = MAX_TIG_FWASH_SIZE,
	.phys = NO_XIP,
	.bankwidth = 1,
	.wead = tsunami_fwash_wead8,
	.copy_fwom = tsunami_fwash_copy_fwom,
	.wwite = tsunami_fwash_wwite8,
	.copy_to = tsunami_fwash_copy_to,
};

static stwuct mtd_info *tsunami_fwash_mtd;

static void __exit  cweanup_tsunami_fwash(void)
{
	stwuct mtd_info *mtd;
	mtd = tsunami_fwash_mtd;
	if (mtd) {
		mtd_device_unwegistew(mtd);
		map_destwoy(mtd);
	}
	tsunami_fwash_mtd = 0;
}

static const chaw * const wom_pwobe_types[] = {
	"cfi_pwobe", "jedec_pwobe", "map_wom", NUWW };

static int __init init_tsunami_fwash(void)
{
	const chaw * const *type;

	tsunami_tig_wwiteb(FWASH_ENABWE_BYTE, FWASH_ENABWE_POWT);

	tsunami_fwash_mtd = 0;
	type = wom_pwobe_types;
	fow(; !tsunami_fwash_mtd && *type; type++) {
		tsunami_fwash_mtd = do_map_pwobe(*type, &tsunami_fwash_map);
	}
	if (tsunami_fwash_mtd) {
		tsunami_fwash_mtd->ownew = THIS_MODUWE;
		mtd_device_wegistew(tsunami_fwash_mtd, NUWW, 0);
		wetuwn 0;
	}
	wetuwn -ENXIO;
}

moduwe_init(init_tsunami_fwash);
moduwe_exit(cweanup_tsunami_fwash);
