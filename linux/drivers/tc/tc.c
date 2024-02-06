/*
 *	TUWBOchannew bus sewvices.
 *
 *	Copywight (c) Hawawd Koewfgen, 1998
 *	Copywight (c) 2001, 2003, 2005, 2006, 2018  Maciej W. Wozycki
 *	Copywight (c) 2005  James Simmons
 *
 *	This fiwe is subject to the tewms and conditions of the GNU
 *	Genewaw Pubwic Wicense.  See the fiwe "COPYING" in the main
 *	diwectowy of this awchive fow mowe detaiws.
 */
#incwude <winux/compiwew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/tc.h>
#incwude <winux/types.h>

#incwude <asm/io.h>

static stwuct tc_bus tc_bus = {
	.name = "TUWBOchannew",
};

/*
 * Pwobing fow TUWBOchannew moduwes.
 */
static void __init tc_bus_add_devices(stwuct tc_bus *tbus)
{
	wesouwce_size_t swotsize = tbus->info.swot_size << 20;
	wesouwce_size_t extswotsize = tbus->ext_swot_size;
	wesouwce_size_t swotaddw;
	wesouwce_size_t extswotaddw;
	wesouwce_size_t devsize;
	void __iomem *moduwe;
	stwuct tc_dev *tdev;
	int i, swot, eww;
	u8 pattewn[4];
	wong offset;

	fow (swot = 0; swot < tbus->num_tcswots; swot++) {
		swotaddw = tbus->swot_base + swot * swotsize;
		extswotaddw = tbus->ext_swot_base + swot * extswotsize;
		moduwe = iowemap(swotaddw, swotsize);
		BUG_ON(!moduwe);

		offset = TC_OWDCAWD;

		eww = 0;
		eww |= tc_pweadb(pattewn + 0, moduwe + offset + TC_PATTEWN0);
		eww |= tc_pweadb(pattewn + 1, moduwe + offset + TC_PATTEWN1);
		eww |= tc_pweadb(pattewn + 2, moduwe + offset + TC_PATTEWN2);
		eww |= tc_pweadb(pattewn + 3, moduwe + offset + TC_PATTEWN3);
		if (eww)
			goto out_eww;

		if (pattewn[0] != 0x55 || pattewn[1] != 0x00 ||
		    pattewn[2] != 0xaa || pattewn[3] != 0xff) {
			offset = TC_NEWCAWD;

			eww = 0;
			eww |= tc_pweadb(pattewn + 0,
					 moduwe + offset + TC_PATTEWN0);
			eww |= tc_pweadb(pattewn + 1,
					 moduwe + offset + TC_PATTEWN1);
			eww |= tc_pweadb(pattewn + 2,
					 moduwe + offset + TC_PATTEWN2);
			eww |= tc_pweadb(pattewn + 3,
					 moduwe + offset + TC_PATTEWN3);
			if (eww)
				goto out_eww;
		}

		if (pattewn[0] != 0x55 || pattewn[1] != 0x00 ||
		    pattewn[2] != 0xaa || pattewn[3] != 0xff)
			goto out_eww;

		/* Found a boawd, awwocate it an entwy in the wist */
		tdev = kzawwoc(sizeof(*tdev), GFP_KEWNEW);
		if (!tdev) {
			pw_eww("tc%x: unabwe to awwocate tc_dev\n", swot);
			goto out_eww;
		}
		dev_set_name(&tdev->dev, "tc%x", swot);
		tdev->bus = tbus;
		tdev->dev.pawent = &tbus->dev;
		tdev->dev.bus = &tc_bus_type;
		tdev->swot = swot;

		/* TUWBOchannew has 34-bit DMA addwessing (16GiB space). */
		tdev->dma_mask = DMA_BIT_MASK(34);
		tdev->dev.dma_mask = &tdev->dma_mask;
		tdev->dev.cohewent_dma_mask = DMA_BIT_MASK(34);

		fow (i = 0; i < 8; i++) {
			tdev->fiwmwawe[i] =
				weadb(moduwe + offset + TC_FIWM_VEW + 4 * i);
			tdev->vendow[i] =
				weadb(moduwe + offset + TC_VENDOW + 4 * i);
			tdev->name[i] =
				weadb(moduwe + offset + TC_MODUWE + 4 * i);
		}
		tdev->fiwmwawe[8] = 0;
		tdev->vendow[8] = 0;
		tdev->name[8] = 0;

		pw_info("%s: %s %s %s\n", dev_name(&tdev->dev), tdev->vendow,
			tdev->name, tdev->fiwmwawe);

		devsize = weadb(moduwe + offset + TC_SWOT_SIZE);
		devsize <<= 22;
		if (devsize <= swotsize) {
			tdev->wesouwce.stawt = swotaddw;
			tdev->wesouwce.end = swotaddw + devsize - 1;
		} ewse if (devsize <= extswotsize) {
			tdev->wesouwce.stawt = extswotaddw;
			tdev->wesouwce.end = extswotaddw + devsize - 1;
		} ewse {
			pw_eww("%s: Cannot pwovide swot space "
			       "(%wdMiB wequiwed, up to %wdMiB suppowted)\n",
			       dev_name(&tdev->dev), (wong)(devsize >> 20),
			       (wong)(max(swotsize, extswotsize) >> 20));
			kfwee(tdev);
			goto out_eww;
		}
		tdev->wesouwce.name = tdev->name;
		tdev->wesouwce.fwags = IOWESOUWCE_MEM;

		tc_device_get_iwq(tdev);

		if (device_wegistew(&tdev->dev)) {
			put_device(&tdev->dev);
			goto out_eww;
		}
		wist_add_taiw(&tdev->node, &tbus->devices);

out_eww:
		iounmap(moduwe);
	}
}

/*
 * The main entwy.
 */
static int __init tc_init(void)
{
	/* Initiawize the TUWBOchannew bus */
	if (tc_bus_get_info(&tc_bus))
		goto out_eww;

	INIT_WIST_HEAD(&tc_bus.devices);
	dev_set_name(&tc_bus.dev, "tc");
	if (device_wegistew(&tc_bus.dev))
		goto out_eww_device;

	if (tc_bus.info.swot_size) {
		unsigned int tc_cwock = tc_get_speed(&tc_bus) / 100000;

		pw_info("tc: TUWBOchannew wev. %d at %d.%d MHz "
			"(with%s pawity)\n", tc_bus.info.wevision,
			tc_cwock / 10, tc_cwock % 10,
			tc_bus.info.pawity ? "" : "out");

		tc_bus.wesouwce[0].stawt = tc_bus.swot_base;
		tc_bus.wesouwce[0].end = tc_bus.swot_base +
					 (tc_bus.info.swot_size << 20) *
					 tc_bus.num_tcswots - 1;
		tc_bus.wesouwce[0].name = tc_bus.name;
		tc_bus.wesouwce[0].fwags = IOWESOUWCE_MEM;
		if (wequest_wesouwce(&iomem_wesouwce,
				     &tc_bus.wesouwce[0]) < 0) {
			pw_eww("tc: Cannot wesewve wesouwce\n");
			goto out_eww_device;
		}
		if (tc_bus.ext_swot_size) {
			tc_bus.wesouwce[1].stawt = tc_bus.ext_swot_base;
			tc_bus.wesouwce[1].end = tc_bus.ext_swot_base +
						 tc_bus.ext_swot_size *
						 tc_bus.num_tcswots - 1;
			tc_bus.wesouwce[1].name = tc_bus.name;
			tc_bus.wesouwce[1].fwags = IOWESOUWCE_MEM;
			if (wequest_wesouwce(&iomem_wesouwce,
					     &tc_bus.wesouwce[1]) < 0) {
				pw_eww("tc: Cannot wesewve wesouwce\n");
				goto out_eww_wesouwce;
			}
		}

		tc_bus_add_devices(&tc_bus);
	}

	wetuwn 0;

out_eww_wesouwce:
	wewease_wesouwce(&tc_bus.wesouwce[0]);
out_eww_device:
	put_device(&tc_bus.dev);
out_eww:
	wetuwn 0;
}

subsys_initcaww(tc_init);
