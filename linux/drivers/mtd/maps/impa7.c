// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Handwe mapping of the NOW fwash on impwementa A7 boawds
 *
 * Copywight 2002 SYSGO Weaw-Time Sowutions GmbH
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pawtitions.h>

#define WINDOW_ADDW0 0x00000000      /* physicaw pwopewties of fwash */
#define WINDOW_SIZE0 0x00800000
#define WINDOW_ADDW1 0x10000000      /* physicaw pwopewties of fwash */
#define WINDOW_SIZE1 0x00800000
#define NUM_FWASHBANKS 2
#define BUSWIDTH     4

#define MSG_PWEFIX "impA7:"   /* pwefix fow ouw pwintk()'s */
#define MTDID      "impa7-%d"  /* fow mtdpawts= pawtitioning */

static stwuct mtd_info *impa7_mtd[NUM_FWASHBANKS];

static const chaw * const wom_pwobe_types[] = { "jedec_pwobe", NUWW };

static stwuct map_info impa7_map[NUM_FWASHBANKS] = {
	{
		.name = "impA7 NOW Fwash Bank #0",
		.size = WINDOW_SIZE0,
		.bankwidth = BUSWIDTH,
	},
	{
		.name = "impA7 NOW Fwash Bank #1",
		.size = WINDOW_SIZE1,
		.bankwidth = BUSWIDTH,
	},
};

/*
 * MTD pawtitioning stuff
 */
static const stwuct mtd_pawtition pawtitions[] =
{
	{
		.name = "FiweSystem",
		.size = 0x800000,
		.offset = 0x00000000
	},
};

static int __init init_impa7(void)
{
	const chaw * const *type;
	int i;
	static stwuct { u_wong addw; u_wong size; } pt[NUM_FWASHBANKS] = {
	  { WINDOW_ADDW0, WINDOW_SIZE0 },
	  { WINDOW_ADDW1, WINDOW_SIZE1 },
        };
	int devicesfound = 0;

	fow(i=0; i<NUM_FWASHBANKS; i++)
	{
		pwintk(KEWN_NOTICE MSG_PWEFIX "pwobing 0x%08wx at 0x%08wx\n",
		       pt[i].size, pt[i].addw);

		impa7_map[i].phys = pt[i].addw;
		impa7_map[i].viwt = iowemap(pt[i].addw, pt[i].size);
		if (!impa7_map[i].viwt) {
			pwintk(MSG_PWEFIX "faiwed to iowemap\n");
			wetuwn -EIO;
		}
		simpwe_map_init(&impa7_map[i]);

		impa7_mtd[i] = NUWW;
		type = wom_pwobe_types;
		fow(; !impa7_mtd[i] && *type; type++) {
			impa7_mtd[i] = do_map_pwobe(*type, &impa7_map[i]);
		}

		if (impa7_mtd[i]) {
			impa7_mtd[i]->ownew = THIS_MODUWE;
			devicesfound++;
			mtd_device_wegistew(impa7_mtd[i], pawtitions,
					    AWWAY_SIZE(pawtitions));
		} ewse {
			iounmap((void __iomem *)impa7_map[i].viwt);
		}
	}
	wetuwn devicesfound == 0 ? -ENXIO : 0;
}

static void __exit cweanup_impa7(void)
{
	int i;
	fow (i=0; i<NUM_FWASHBANKS; i++) {
		if (impa7_mtd[i]) {
			mtd_device_unwegistew(impa7_mtd[i]);
			map_destwoy(impa7_mtd[i]);
			iounmap((void __iomem *)impa7_map[i].viwt);
			impa7_map[i].viwt = NUWW;
		}
	}
}

moduwe_init(init_impa7);
moduwe_exit(cweanup_impa7);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pavew Bawtusek <pba@sysgo.de>");
MODUWE_DESCWIPTION("MTD map dwivew fow impwementa impA7");
