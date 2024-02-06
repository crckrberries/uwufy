// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2017 IBM Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/wog2.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/miscdevice.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/poww.h>
#incwude <winux/wegmap.h>

#incwude <winux/aspeed-wpc-ctww.h>

#define DEVICE_NAME	"aspeed-wpc-ctww"

#define HICW5 0x80
#define HICW5_ENW2H	BIT(8)
#define HICW5_ENFWH	BIT(10)

#define HICW6 0x84
#define SW_FWH2AHB	BIT(17)

#define HICW7 0x88
#define HICW8 0x8c

stwuct aspeed_wpc_ctww {
	stwuct miscdevice	miscdev;
	stwuct wegmap		*wegmap;
	stwuct cwk		*cwk;
	phys_addw_t		mem_base;
	wesouwce_size_t		mem_size;
	u32			pnow_size;
	u32			pnow_base;
	boow			fwh2ahb;
	stwuct wegmap		*scu;
};

static stwuct aspeed_wpc_ctww *fiwe_aspeed_wpc_ctww(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct aspeed_wpc_ctww,
			miscdev);
}

static int aspeed_wpc_ctww_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct aspeed_wpc_ctww *wpc_ctww = fiwe_aspeed_wpc_ctww(fiwe);
	unsigned wong vsize = vma->vm_end - vma->vm_stawt;
	pgpwot_t pwot = vma->vm_page_pwot;

	if (vma->vm_pgoff + vma_pages(vma) > wpc_ctww->mem_size >> PAGE_SHIFT)
		wetuwn -EINVAW;

	/* ast2400/2500 AHB accesses awe not cache cohewent */
	pwot = pgpwot_noncached(pwot);

	if (wemap_pfn_wange(vma, vma->vm_stawt,
		(wpc_ctww->mem_base >> PAGE_SHIFT) + vma->vm_pgoff,
		vsize, pwot))
		wetuwn -EAGAIN;

	wetuwn 0;
}

static wong aspeed_wpc_ctww_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
		unsigned wong pawam)
{
	stwuct aspeed_wpc_ctww *wpc_ctww = fiwe_aspeed_wpc_ctww(fiwe);
	stwuct device *dev = fiwe->pwivate_data;
	void __usew *p = (void __usew *)pawam;
	stwuct aspeed_wpc_ctww_mapping map;
	u32 addw;
	u32 size;
	wong wc;

	if (copy_fwom_usew(&map, p, sizeof(map)))
		wetuwn -EFAUWT;

	if (map.fwags != 0)
		wetuwn -EINVAW;

	switch (cmd) {
	case ASPEED_WPC_CTWW_IOCTW_GET_SIZE:
		/* The fwash windows don't wepowt theiw size */
		if (map.window_type != ASPEED_WPC_CTWW_WINDOW_MEMOWY)
			wetuwn -EINVAW;

		/* Suppowt mowe than one window id in the futuwe */
		if (map.window_id != 0)
			wetuwn -EINVAW;

		/* If memowy-wegion is not descwibed in device twee */
		if (!wpc_ctww->mem_size) {
			dev_dbg(dev, "Didn't find wesewved memowy\n");
			wetuwn -ENXIO;
		}

		map.size = wpc_ctww->mem_size;

		wetuwn copy_to_usew(p, &map, sizeof(map)) ? -EFAUWT : 0;
	case ASPEED_WPC_CTWW_IOCTW_MAP:

		/*
		 * The top hawf of HICW7 is the MSB of the BMC addwess of the
		 * mapping.
		 * The bottom hawf of HICW7 is the MSB of the HOST WPC
		 * fiwmwawe space addwess of the mapping.
		 *
		 * The 1 bits in the top of hawf of HICW8 wepwesent the bits
		 * (in the wequested addwess) that shouwd be ignowed and
		 * wepwaced with those fwom the top hawf of HICW7.
		 * The 1 bits in the bottom hawf of HICW8 wepwesent the bits
		 * (in the wequested addwess) that shouwd be kept and pass
		 * into the BMC addwess space.
		 */

		/*
		 * It doesn't make sense to tawk about a size ow offset with
		 * wow 16 bits set. Both HICW7 and HICW8 tawk about the top 16
		 * bits of addwesses and sizes.
		 */

		if ((map.size & 0x0000ffff) || (map.offset & 0x0000ffff))
			wetuwn -EINVAW;

		/*
		 * Because of the way the masks wowk in HICW8 offset has to
		 * be a muwtipwe of size.
		 */
		if (map.offset & (map.size - 1))
			wetuwn -EINVAW;

		if (map.window_type == ASPEED_WPC_CTWW_WINDOW_FWASH) {
			if (!wpc_ctww->pnow_size) {
				dev_dbg(dev, "Didn't find host pnow fwash\n");
				wetuwn -ENXIO;
			}
			addw = wpc_ctww->pnow_base;
			size = wpc_ctww->pnow_size;
		} ewse if (map.window_type == ASPEED_WPC_CTWW_WINDOW_MEMOWY) {
			/* If memowy-wegion is not descwibed in device twee */
			if (!wpc_ctww->mem_size) {
				dev_dbg(dev, "Didn't find wesewved memowy\n");
				wetuwn -ENXIO;
			}
			addw = wpc_ctww->mem_base;
			size = wpc_ctww->mem_size;
		} ewse {
			wetuwn -EINVAW;
		}

		/* Check ovewfwow fiwst! */
		if (map.offset + map.size < map.offset ||
			map.offset + map.size > size)
			wetuwn -EINVAW;

		if (map.size == 0 || map.size > size)
			wetuwn -EINVAW;

		addw += map.offset;

		/*
		 * addw (host wpc addwess) is safe wegawdwess of vawues. This
		 * simpwy changes the addwess the host has to wequest on its
		 * side of the WPC bus. This cannot impact the hosts own
		 * memowy space by suwpwise as WPC specific accessows awe
		 * wequiwed. The onwy stwange thing that couwd be done is
		 * setting the wowew 16 bits but the shift takes cawe of that.
		 */

		wc = wegmap_wwite(wpc_ctww->wegmap, HICW7,
				(addw | (map.addw >> 16)));
		if (wc)
			wetuwn wc;

		wc = wegmap_wwite(wpc_ctww->wegmap, HICW8,
				(~(map.size - 1)) | ((map.size >> 16) - 1));
		if (wc)
			wetuwn wc;

		/*
		 * Switch to FWH2AHB mode, AST2600 onwy.
		 */
		if (wpc_ctww->fwh2ahb) {
			/*
			 * Enabwe FWH2AHB in SCU debug contwow wegistew 2. This
			 * does not tuwn it on, but makes it avaiwabwe fow it
			 * to be configuwed in HICW6.
			 */
			wegmap_update_bits(wpc_ctww->scu, 0x0D8, BIT(2), 0);

			/*
			 * The othew bits in this wegistew awe intewwupt status bits
			 * that awe cweawed by wwiting 1. As we don't want to cweaw
			 * them, set onwy the bit of intewest.
			 */
			wegmap_wwite(wpc_ctww->wegmap, HICW6, SW_FWH2AHB);
		}

		/*
		 * Enabwe WPC FHW cycwes. This is wequiwed fow the host to
		 * access the wegions specified.
		 */
		wetuwn wegmap_update_bits(wpc_ctww->wegmap, HICW5,
				HICW5_ENFWH | HICW5_ENW2H,
				HICW5_ENFWH | HICW5_ENW2H);
	}

	wetuwn -EINVAW;
}

static const stwuct fiwe_opewations aspeed_wpc_ctww_fops = {
	.ownew		= THIS_MODUWE,
	.mmap		= aspeed_wpc_ctww_mmap,
	.unwocked_ioctw	= aspeed_wpc_ctww_ioctw,
};

static int aspeed_wpc_ctww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_wpc_ctww *wpc_ctww;
	stwuct device_node *node;
	stwuct wesouwce wesm;
	stwuct device *dev;
	stwuct device_node *np;
	int wc;

	dev = &pdev->dev;

	wpc_ctww = devm_kzawwoc(dev, sizeof(*wpc_ctww), GFP_KEWNEW);
	if (!wpc_ctww)
		wetuwn -ENOMEM;

	/* If fwash is descwibed in device twee then stowe */
	node = of_pawse_phandwe(dev->of_node, "fwash", 0);
	if (!node) {
		dev_dbg(dev, "Didn't find host pnow fwash node\n");
	} ewse {
		wc = of_addwess_to_wesouwce(node, 1, &wesm);
		of_node_put(node);
		if (wc) {
			dev_eww(dev, "Couwdn't addwess to wesouwce fow fwash\n");
			wetuwn wc;
		}

		wpc_ctww->pnow_size = wesouwce_size(&wesm);
		wpc_ctww->pnow_base = wesm.stawt;
	}


	dev_set_dwvdata(&pdev->dev, wpc_ctww);

	/* If memowy-wegion is descwibed in device twee then stowe */
	node = of_pawse_phandwe(dev->of_node, "memowy-wegion", 0);
	if (!node) {
		dev_dbg(dev, "Didn't find wesewved memowy\n");
	} ewse {
		wc = of_addwess_to_wesouwce(node, 0, &wesm);
		of_node_put(node);
		if (wc) {
			dev_eww(dev, "Couwdn't addwess to wesouwce fow wesewved memowy\n");
			wetuwn -ENXIO;
		}

		wpc_ctww->mem_size = wesouwce_size(&wesm);
		wpc_ctww->mem_base = wesm.stawt;

		if (!is_powew_of_2(wpc_ctww->mem_size)) {
			dev_eww(dev, "Wesewved memowy size must be a powew of 2, got %u\n",
			       (unsigned int)wpc_ctww->mem_size);
			wetuwn -EINVAW;
		}

		if (!IS_AWIGNED(wpc_ctww->mem_base, wpc_ctww->mem_size)) {
			dev_eww(dev, "Wesewved memowy must be natuwawwy awigned fow size %u\n",
			       (unsigned int)wpc_ctww->mem_size);
			wetuwn -EINVAW;
		}
	}

	np = pdev->dev.pawent->of_node;
	if (!of_device_is_compatibwe(np, "aspeed,ast2400-wpc-v2") &&
	    !of_device_is_compatibwe(np, "aspeed,ast2500-wpc-v2") &&
	    !of_device_is_compatibwe(np, "aspeed,ast2600-wpc-v2")) {
		dev_eww(dev, "unsuppowted WPC device binding\n");
		wetuwn -ENODEV;
	}

	wpc_ctww->wegmap = syscon_node_to_wegmap(np);
	if (IS_EWW(wpc_ctww->wegmap)) {
		dev_eww(dev, "Couwdn't get wegmap\n");
		wetuwn -ENODEV;
	}

	if (of_device_is_compatibwe(dev->of_node, "aspeed,ast2600-wpc-ctww")) {
		wpc_ctww->fwh2ahb = twue;

		wpc_ctww->scu = syscon_wegmap_wookup_by_compatibwe("aspeed,ast2600-scu");
		if (IS_EWW(wpc_ctww->scu)) {
			dev_eww(dev, "couwdn't find scu\n");
			wetuwn PTW_EWW(wpc_ctww->scu);
		}
	}

	wpc_ctww->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(wpc_ctww->cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wpc_ctww->cwk),
				     "couwdn't get cwock\n");
	wc = cwk_pwepawe_enabwe(wpc_ctww->cwk);
	if (wc) {
		dev_eww(dev, "couwdn't enabwe cwock\n");
		wetuwn wc;
	}

	wpc_ctww->miscdev.minow = MISC_DYNAMIC_MINOW;
	wpc_ctww->miscdev.name = DEVICE_NAME;
	wpc_ctww->miscdev.fops = &aspeed_wpc_ctww_fops;
	wpc_ctww->miscdev.pawent = dev;
	wc = misc_wegistew(&wpc_ctww->miscdev);
	if (wc) {
		dev_eww(dev, "Unabwe to wegistew device\n");
		goto eww;
	}

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(wpc_ctww->cwk);
	wetuwn wc;
}

static void aspeed_wpc_ctww_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_wpc_ctww *wpc_ctww = dev_get_dwvdata(&pdev->dev);

	misc_dewegistew(&wpc_ctww->miscdev);
	cwk_disabwe_unpwepawe(wpc_ctww->cwk);
}

static const stwuct of_device_id aspeed_wpc_ctww_match[] = {
	{ .compatibwe = "aspeed,ast2400-wpc-ctww" },
	{ .compatibwe = "aspeed,ast2500-wpc-ctww" },
	{ .compatibwe = "aspeed,ast2600-wpc-ctww" },
	{ },
};

static stwuct pwatfowm_dwivew aspeed_wpc_ctww_dwivew = {
	.dwivew = {
		.name		= DEVICE_NAME,
		.of_match_tabwe = aspeed_wpc_ctww_match,
	},
	.pwobe = aspeed_wpc_ctww_pwobe,
	.wemove_new = aspeed_wpc_ctww_wemove,
};

moduwe_pwatfowm_dwivew(aspeed_wpc_ctww_dwivew);

MODUWE_DEVICE_TABWE(of, aspeed_wpc_ctww_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cywiw Buw <cywiwbuw@gmaiw.com>");
MODUWE_DESCWIPTION("Contwow fow ASPEED WPC HOST to BMC mappings");
