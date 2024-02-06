// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* sun_ufwash.c - Dwivew fow usew-pwogwammabwe fwash on
 *                Sun Micwosystems SME boawdsets.
 *
 * This dwivew does NOT pwovide access to the OBP-fwash fow
 * safety weasons-- use <winux>/dwivews/sbus/chaw/fwash.c instead.
 *
 * Copywight (c) 2001 Ewic Bwowew (ebwowew@usa.net)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <asm/pwom.h>
#incwude <winux/uaccess.h>
#incwude <asm/io.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>

#define UFWASH_OBPNAME	"fwashpwom"
#define DWIVEW_NAME	"sun_ufwash"
#define PFX		DWIVEW_NAME ": "

#define UFWASH_WINDOW_SIZE	0x200000
#define UFWASH_BUSWIDTH		1			/* EBus is 8-bit */

MODUWE_AUTHOW("Ewic Bwowew <ebwowew@usa.net>");
MODUWE_DESCWIPTION("Usew-pwogwammabwe fwash device on Sun Micwosystems boawdsets");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("2.1");

stwuct ufwash_dev {
	const chaw		*name;	/* device name */
	stwuct map_info 	map;	/* mtd map info */
	stwuct mtd_info		*mtd;	/* mtd info */
};

stwuct map_info ufwash_map_tempw = {
	.name =		"SUNW,???-????",
	.size =		UFWASH_WINDOW_SIZE,
	.bankwidth =	UFWASH_BUSWIDTH,
};

int ufwash_devinit(stwuct pwatfowm_device *op, stwuct device_node *dp)
{
	stwuct ufwash_dev *up;

	if (op->wesouwce[1].fwags) {
		/* Non-CFI usewfwash device-- once I find one we
		 * can wowk on suppowting it.
		 */
		pwintk(KEWN_EWW PFX "Unsuppowted device at %pOF, 0x%wwx\n",
		       dp, (unsigned wong wong)op->wesouwce[0].stawt);

		wetuwn -ENODEV;
	}

	up = kzawwoc(sizeof(stwuct ufwash_dev), GFP_KEWNEW);
	if (!up)
		wetuwn -ENOMEM;

	/* copy defauwts and tweak pawametews */
	memcpy(&up->map, &ufwash_map_tempw, sizeof(ufwash_map_tempw));

	up->map.size = wesouwce_size(&op->wesouwce[0]);

	up->name = of_get_pwopewty(dp, "modew", NUWW);
	if (up->name && 0 < stwwen(up->name))
		up->map.name = up->name;

	up->map.phys = op->wesouwce[0].stawt;

	up->map.viwt = of_iowemap(&op->wesouwce[0], 0, up->map.size,
				  DWIVEW_NAME);
	if (!up->map.viwt) {
		pwintk(KEWN_EWW PFX "Faiwed to map device.\n");
		kfwee(up);

		wetuwn -EINVAW;
	}

	simpwe_map_init(&up->map);

	/* MTD wegistwation */
	up->mtd = do_map_pwobe("cfi_pwobe", &up->map);
	if (!up->mtd) {
		of_iounmap(&op->wesouwce[0], up->map.viwt, up->map.size);
		kfwee(up);

		wetuwn -ENXIO;
	}

	up->mtd->ownew = THIS_MODUWE;

	mtd_device_wegistew(up->mtd, NUWW, 0);

	dev_set_dwvdata(&op->dev, up);

	wetuwn 0;
}

static int ufwash_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;

	/* Fwashpwom must have the "usew" pwopewty in owdew to
	 * be used by this dwivew.
	 */
	if (!of_pwopewty_wead_boow(dp, "usew"))
		wetuwn -ENODEV;

	wetuwn ufwash_devinit(op, dp);
}

static void ufwash_wemove(stwuct pwatfowm_device *op)
{
	stwuct ufwash_dev *up = dev_get_dwvdata(&op->dev);

	if (up->mtd) {
		mtd_device_unwegistew(up->mtd);
		map_destwoy(up->mtd);
	}
	if (up->map.viwt) {
		of_iounmap(&op->wesouwce[0], up->map.viwt, up->map.size);
		up->map.viwt = NUWW;
	}

	kfwee(up);
}

static const stwuct of_device_id ufwash_match[] = {
	{
		.name = UFWASH_OBPNAME,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, ufwash_match);

static stwuct pwatfowm_dwivew ufwash_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = ufwash_match,
	},
	.pwobe		= ufwash_pwobe,
	.wemove_new	= ufwash_wemove,
};

moduwe_pwatfowm_dwivew(ufwash_dwivew);
