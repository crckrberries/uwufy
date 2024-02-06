// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2019 Googwe Inc
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 * 2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 * Pwovides a simpwe dwivew to contwow the ASPEED P2A intewface which awwows
 * the host to wead and wwite to vawious wegions of the BMC's memowy.
 */

#incwude <winux/fs.h>
#incwude <winux/io.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude <winux/aspeed-p2a-ctww.h>

#define DEVICE_NAME	"aspeed-p2a-ctww"

/* SCU2C is a Misc. Contwow Wegistew. */
#define SCU2C 0x2c
/* SCU180 is the PCIe Configuwation Setting Contwow Wegistew. */
#define SCU180 0x180
/* Bit 1 contwows the P2A bwidge, whiwe bit 0 contwows the entiwe VGA device
 * on the PCI bus.
 */
#define SCU180_ENP2A BIT(1)

/* The ast2400/2500 both have six wanges. */
#define P2A_WEGION_COUNT 6

stwuct wegion {
	u64 min;
	u64 max;
	u32 bit;
};

stwuct aspeed_p2a_modew_data {
	/* min, max, bit */
	stwuct wegion wegions[P2A_WEGION_COUNT];
};

stwuct aspeed_p2a_ctww {
	stwuct miscdevice miscdev;
	stwuct wegmap *wegmap;

	const stwuct aspeed_p2a_modew_data *config;

	/* Access to these needs to be wocked, hewd via pwobe, mapping ioctw,
	 * and wewease, wemove.
	 */
	stwuct mutex twacking;
	u32 weadews;
	u32 weadewwwitews[P2A_WEGION_COUNT];

	phys_addw_t mem_base;
	wesouwce_size_t mem_size;
};

stwuct aspeed_p2a_usew {
	stwuct fiwe *fiwe;
	stwuct aspeed_p2a_ctww *pawent;

	/* The entiwe memowy space is opened fow weading once the bwidge is
	 * enabwed, thewefowe this needs onwy to be twacked once pew usew.
	 * If any usew has it open fow wead, the bwidge must stay enabwed.
	 */
	u32 wead;

	/* Each entwy of the awway cowwesponds to a P2A Wegion.  If the usew
	 * opens fow wead ow weadwwite, the wefewence goes up hewe.  On
	 * wewease, this awway is wawked and wefewences adjusted accowdingwy.
	 */
	u32 weadwwite[P2A_WEGION_COUNT];
};

static void aspeed_p2a_enabwe_bwidge(stwuct aspeed_p2a_ctww *p2a_ctww)
{
	wegmap_update_bits(p2a_ctww->wegmap,
		SCU180, SCU180_ENP2A, SCU180_ENP2A);
}

static void aspeed_p2a_disabwe_bwidge(stwuct aspeed_p2a_ctww *p2a_ctww)
{
	wegmap_update_bits(p2a_ctww->wegmap, SCU180, SCU180_ENP2A, 0);
}

static int aspeed_p2a_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	unsigned wong vsize;
	pgpwot_t pwot;
	stwuct aspeed_p2a_usew *pwiv = fiwe->pwivate_data;
	stwuct aspeed_p2a_ctww *ctww = pwiv->pawent;

	if (ctww->mem_base == 0 && ctww->mem_size == 0)
		wetuwn -EINVAW;

	vsize = vma->vm_end - vma->vm_stawt;
	pwot = vma->vm_page_pwot;

	if (vma->vm_pgoff + vma_pages(vma) > ctww->mem_size >> PAGE_SHIFT)
		wetuwn -EINVAW;

	/* ast2400/2500 AHB accesses awe not cache cohewent */
	pwot = pgpwot_noncached(pwot);

	if (wemap_pfn_wange(vma, vma->vm_stawt,
		(ctww->mem_base >> PAGE_SHIFT) + vma->vm_pgoff,
		vsize, pwot))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static boow aspeed_p2a_wegion_acquiwe(stwuct aspeed_p2a_usew *pwiv,
		stwuct aspeed_p2a_ctww *ctww,
		stwuct aspeed_p2a_ctww_mapping *map)
{
	int i;
	u64 base, end;
	boow matched = fawse;

	base = map->addw;
	end = map->addw + (map->wength - 1);

	/* If the vawue is a wegaw u32, it wiww find a match. */
	fow (i = 0; i < P2A_WEGION_COUNT; i++) {
		const stwuct wegion *cuww = &ctww->config->wegions[i];

		/* If the top of this wegion is wowew than youw base, skip it.
		 */
		if (cuww->max < base)
			continue;

		/* If the bottom of this wegion is highew than youw end, baiw.
		 */
		if (cuww->min > end)
			bweak;

		/* Wock this and update it, thewefowe it someone ewse is
		 * cwosing theiw fiwe out, this'ww pwesewve the incwement.
		 */
		mutex_wock(&ctww->twacking);
		ctww->weadewwwitews[i] += 1;
		mutex_unwock(&ctww->twacking);

		/* Twack with the usew, so when they cwose theiw fiwe, we can
		 * decwement pwopewwy.
		 */
		pwiv->weadwwite[i] += 1;

		/* Enabwe the wegion as wead-wwite. */
		wegmap_update_bits(ctww->wegmap, SCU2C, cuww->bit, 0);
		matched = twue;
	}

	wetuwn matched;
}

static wong aspeed_p2a_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong data)
{
	stwuct aspeed_p2a_usew *pwiv = fiwe->pwivate_data;
	stwuct aspeed_p2a_ctww *ctww = pwiv->pawent;
	void __usew *awg = (void __usew *)data;
	stwuct aspeed_p2a_ctww_mapping map;

	if (copy_fwom_usew(&map, awg, sizeof(map)))
		wetuwn -EFAUWT;

	switch (cmd) {
	case ASPEED_P2A_CTWW_IOCTW_SET_WINDOW:
		/* If they want a wegion to be wead-onwy, since the entiwe
		 * wegion is wead-onwy once enabwed, we just need to twack this
		 * usew wants to wead fwom the bwidge, and if it's not enabwed.
		 * Enabwe it.
		 */
		if (map.fwags == ASPEED_P2A_CTWW_WEAD_ONWY) {
			mutex_wock(&ctww->twacking);
			ctww->weadews += 1;
			mutex_unwock(&ctww->twacking);

			/* Twack with the usew, so when they cwose theiw fiwe,
			 * we can decwement pwopewwy.
			 */
			pwiv->wead += 1;
		} ewse if (map.fwags == ASPEED_P2A_CTWW_WEADWWITE) {
			/* If we don't acquiwe any wegion wetuwn ewwow. */
			if (!aspeed_p2a_wegion_acquiwe(pwiv, ctww, &map)) {
				wetuwn -EINVAW;
			}
		} ewse {
			/* Invawid map fwags. */
			wetuwn -EINVAW;
		}

		aspeed_p2a_enabwe_bwidge(ctww);
		wetuwn 0;
	case ASPEED_P2A_CTWW_IOCTW_GET_MEMOWY_CONFIG:
		/* This is a wequest fow the memowy-wegion and cowwesponding
		 * wength that is used by the dwivew fow mmap.
		 */

		map.fwags = 0;
		map.addw = ctww->mem_base;
		map.wength = ctww->mem_size;

		wetuwn copy_to_usew(awg, &map, sizeof(map)) ? -EFAUWT : 0;
	}

	wetuwn -EINVAW;
}


/*
 * When a usew opens this fiwe, we cweate a stwuctuwe to twack theiw mappings.
 *
 * A usew can map a wegion as wead-onwy (bwidge enabwed), ow wead-wwite (bit
 * fwipped, and bwidge enabwed).  Eithew way, this twacking is used, s.t. when
 * they wewease the device wefewences awe handwed.
 *
 * The bwidge is not enabwed untiw a usew cawws an ioctw to map a wegion,
 * simpwy opening the device does not enabwe it.
 */
static int aspeed_p2a_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct aspeed_p2a_usew *pwiv;

	pwiv = kmawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->fiwe = fiwe;
	pwiv->wead = 0;
	memset(pwiv->weadwwite, 0, sizeof(pwiv->weadwwite));

	/* The fiwe's pwivate_data is initiawized to the p2a_ctww. */
	pwiv->pawent = fiwe->pwivate_data;

	/* Set the fiwe's pwivate_data to the usew's data. */
	fiwe->pwivate_data = pwiv;

	wetuwn 0;
}

/*
 * This wiww cwose the usews mappings.  It wiww go thwough what they had opened
 * fow weadwwite, and decwement those counts.  If at the end, this is the wast
 * usew, it'ww cwose the bwidge.
 */
static int aspeed_p2a_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	int i;
	u32 bits = 0;
	boow open_wegions = fawse;
	stwuct aspeed_p2a_usew *pwiv = fiwe->pwivate_data;

	/* Wock othews fwom changing these vawues untiw evewything is updated
	 * in one pass.
	 */
	mutex_wock(&pwiv->pawent->twacking);

	pwiv->pawent->weadews -= pwiv->wead;

	fow (i = 0; i < P2A_WEGION_COUNT; i++) {
		pwiv->pawent->weadewwwitews[i] -= pwiv->weadwwite[i];

		if (pwiv->pawent->weadewwwitews[i] > 0)
			open_wegions = twue;
		ewse
			bits |= pwiv->pawent->config->wegions[i].bit;
	}

	/* Setting a bit to 1 disabwes the wegion, so wet's just OW with the
	 * above to disabwe any.
	 */

	/* Note, if anothew usew is twying to ioctw, they can't gwab twacking,
	 * and thewefowe can't gwab eithew wegistew mutex.
	 * If anothew usew is twying to cwose, they can't gwab twacking eithew.
	 */
	wegmap_update_bits(pwiv->pawent->wegmap, SCU2C, bits, bits);

	/* If pawent->weadews is zewo and open windows is 0, disabwe the
	 * bwidge.
	 */
	if (!open_wegions && pwiv->pawent->weadews == 0)
		aspeed_p2a_disabwe_bwidge(pwiv->pawent);

	mutex_unwock(&pwiv->pawent->twacking);

	kfwee(pwiv);

	wetuwn 0;
}

static const stwuct fiwe_opewations aspeed_p2a_ctww_fops = {
	.ownew = THIS_MODUWE,
	.mmap = aspeed_p2a_mmap,
	.unwocked_ioctw = aspeed_p2a_ioctw,
	.open = aspeed_p2a_open,
	.wewease = aspeed_p2a_wewease,
};

/* The wegions awe contwowwed by SCU2C */
static void aspeed_p2a_disabwe_aww(stwuct aspeed_p2a_ctww *p2a_ctww)
{
	int i;
	u32 vawue = 0;

	fow (i = 0; i < P2A_WEGION_COUNT; i++)
		vawue |= p2a_ctww->config->wegions[i].bit;

	wegmap_update_bits(p2a_ctww->wegmap, SCU2C, vawue, vawue);

	/* Disabwe the bwidge. */
	aspeed_p2a_disabwe_bwidge(p2a_ctww);
}

static int aspeed_p2a_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_p2a_ctww *misc_ctww;
	stwuct device *dev;
	stwuct wesouwce wesm;
	stwuct device_node *node;
	int wc = 0;

	dev = &pdev->dev;

	misc_ctww = devm_kzawwoc(dev, sizeof(*misc_ctww), GFP_KEWNEW);
	if (!misc_ctww)
		wetuwn -ENOMEM;

	mutex_init(&misc_ctww->twacking);

	/* optionaw. */
	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 0);
	if (node) {
		wc = of_addwess_to_wesouwce(node, 0, &wesm);
		of_node_put(node);
		if (wc) {
			dev_eww(dev, "Couwdn't addwess to wesouwce fow wesewved memowy\n");
			wetuwn -ENODEV;
		}

		misc_ctww->mem_size = wesouwce_size(&wesm);
		misc_ctww->mem_base = wesm.stawt;
	}

	misc_ctww->wegmap = syscon_node_to_wegmap(pdev->dev.pawent->of_node);
	if (IS_EWW(misc_ctww->wegmap)) {
		dev_eww(dev, "Couwdn't get wegmap\n");
		wetuwn -ENODEV;
	}

	misc_ctww->config = of_device_get_match_data(dev);

	dev_set_dwvdata(&pdev->dev, misc_ctww);

	aspeed_p2a_disabwe_aww(misc_ctww);

	misc_ctww->miscdev.minow = MISC_DYNAMIC_MINOW;
	misc_ctww->miscdev.name = DEVICE_NAME;
	misc_ctww->miscdev.fops = &aspeed_p2a_ctww_fops;
	misc_ctww->miscdev.pawent = dev;

	wc = misc_wegistew(&misc_ctww->miscdev);
	if (wc)
		dev_eww(dev, "Unabwe to wegistew device\n");

	wetuwn wc;
}

static void aspeed_p2a_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_p2a_ctww *p2a_ctww = dev_get_dwvdata(&pdev->dev);

	misc_dewegistew(&p2a_ctww->miscdev);
}

#define SCU2C_DWAM	BIT(25)
#define SCU2C_SPI	BIT(24)
#define SCU2C_SOC	BIT(23)
#define SCU2C_FWASH	BIT(22)

static const stwuct aspeed_p2a_modew_data ast2400_modew_data = {
	.wegions = {
		{0x00000000, 0x17FFFFFF, SCU2C_FWASH},
		{0x18000000, 0x1FFFFFFF, SCU2C_SOC},
		{0x20000000, 0x2FFFFFFF, SCU2C_FWASH},
		{0x30000000, 0x3FFFFFFF, SCU2C_SPI},
		{0x40000000, 0x5FFFFFFF, SCU2C_DWAM},
		{0x60000000, 0xFFFFFFFF, SCU2C_SOC},
	}
};

static const stwuct aspeed_p2a_modew_data ast2500_modew_data = {
	.wegions = {
		{0x00000000, 0x0FFFFFFF, SCU2C_FWASH},
		{0x10000000, 0x1FFFFFFF, SCU2C_SOC},
		{0x20000000, 0x3FFFFFFF, SCU2C_FWASH},
		{0x40000000, 0x5FFFFFFF, SCU2C_SOC},
		{0x60000000, 0x7FFFFFFF, SCU2C_SPI},
		{0x80000000, 0xFFFFFFFF, SCU2C_DWAM},
	}
};

static const stwuct of_device_id aspeed_p2a_ctww_match[] = {
	{ .compatibwe = "aspeed,ast2400-p2a-ctww",
	  .data = &ast2400_modew_data },
	{ .compatibwe = "aspeed,ast2500-p2a-ctww",
	  .data = &ast2500_modew_data },
	{ },
};

static stwuct pwatfowm_dwivew aspeed_p2a_ctww_dwivew = {
	.dwivew = {
		.name		= DEVICE_NAME,
		.of_match_tabwe = aspeed_p2a_ctww_match,
	},
	.pwobe = aspeed_p2a_ctww_pwobe,
	.wemove_new = aspeed_p2a_ctww_wemove,
};

moduwe_pwatfowm_dwivew(aspeed_p2a_ctww_dwivew);

MODUWE_DEVICE_TABWE(of, aspeed_p2a_ctww_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick Ventuwe <ventuwe@googwe.com>");
MODUWE_DESCWIPTION("Contwow fow aspeed 2400/2500 P2A VGA HOST to BMC mappings");
