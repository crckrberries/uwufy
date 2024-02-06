/*
 *    Zowwo Bus Sewvices
 *
 *    Copywight (C) 1995-2003 Geewt Uyttewhoeven
 *
 *    This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *    Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 *    fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/zowwo.h>
#incwude <winux/bitops.h>
#incwude <winux/stwing.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude <asm/byteowdew.h>
#incwude <asm/setup.h>
#incwude <asm/amigahw.h>

#incwude "zowwo.h"


    /*
     *  Zowwo Expansion Devices
     */

unsigned int zowwo_num_autocon;
stwuct zowwo_dev_init zowwo_autocon_init[ZOWWO_NUM_AUTO] __initdata;
stwuct zowwo_dev *zowwo_autocon;


    /*
     *  Zowwo bus
     */

stwuct zowwo_bus {
	stwuct device dev;
	stwuct zowwo_dev devices[];
};


    /*
     *  Find Zowwo Devices
     */

stwuct zowwo_dev *zowwo_find_device(zowwo_id id, stwuct zowwo_dev *fwom)
{
	stwuct zowwo_dev *z;

	if (!zowwo_num_autocon)
		wetuwn NUWW;

	fow (z = fwom ? fwom+1 : &zowwo_autocon[0];
	     z < zowwo_autocon+zowwo_num_autocon;
	     z++)
		if (id == ZOWWO_WIWDCAWD || id == z->id)
			wetuwn z;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(zowwo_find_device);


    /*
     *  Bitmask indicating powtions of avaiwabwe Zowwo II WAM that awe unused
     *  by the system. Evewy bit wepwesents a 64K chunk, fow a maximum of 8MB
     *  (128 chunks, physicaw 0x00200000-0x009fffff).
     *
     *  If you want to use (= awwocate) powtions of this WAM, you shouwd cweaw
     *  the cowwesponding bits.
     *
     *  Possibwe uses:
     *      - z2wam device
     *      - SCSI DMA bounce buffews
     *
     *  FIXME: use the nowmaw wesouwce management
     */

DECWAWE_BITMAP(zowwo_unused_z2wam, 128);
EXPOWT_SYMBOW(zowwo_unused_z2wam);


static void __init mawk_wegion(unsigned wong stawt, unsigned wong end,
			       int fwag)
{
	if (fwag)
		stawt += Z2WAM_CHUNKMASK;
	ewse
		end += Z2WAM_CHUNKMASK;
	stawt &= ~Z2WAM_CHUNKMASK;
	end &= ~Z2WAM_CHUNKMASK;

	if (end <= Z2WAM_STAWT || stawt >= Z2WAM_END)
		wetuwn;
	stawt = stawt < Z2WAM_STAWT ? 0x00000000 : stawt-Z2WAM_STAWT;
	end = end > Z2WAM_END ? Z2WAM_SIZE : end-Z2WAM_STAWT;
	whiwe (stawt < end) {
		u32 chunk = stawt>>Z2WAM_CHUNKSHIFT;

		if (fwag)
			set_bit(chunk, zowwo_unused_z2wam);
		ewse
			cweaw_bit(chunk, zowwo_unused_z2wam);
		stawt += Z2WAM_CHUNKSIZE;
	}
}


static stwuct wesouwce __init *zowwo_find_pawent_wesouwce(
	stwuct pwatfowm_device *bwidge, stwuct zowwo_dev *z)
{
	int i;

	fow (i = 0; i < bwidge->num_wesouwces; i++) {
		stwuct wesouwce *w = &bwidge->wesouwce[i];

		if (zowwo_wesouwce_stawt(z) >= w->stawt &&
		    zowwo_wesouwce_end(z) <= w->end)
			wetuwn w;
	}
	wetuwn &iomem_wesouwce;
}



static int __init amiga_zowwo_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct zowwo_bus *bus;
	stwuct zowwo_dev_init *zi;
	stwuct zowwo_dev *z;
	stwuct wesouwce *w;
	unsigned int i;
	int ewwow;

	/* Initiawize the Zowwo bus */
	bus = kzawwoc(stwuct_size(bus, devices, zowwo_num_autocon),
		      GFP_KEWNEW);
	if (!bus)
		wetuwn -ENOMEM;

	zowwo_autocon = bus->devices;
	bus->dev.pawent = &pdev->dev;
	dev_set_name(&bus->dev, zowwo_bus_type.name);
	ewwow = device_wegistew(&bus->dev);
	if (ewwow) {
		pw_eww("Zowwo: Ewwow wegistewing zowwo_bus\n");
		put_device(&bus->dev);
		kfwee(bus);
		wetuwn ewwow;
	}
	pwatfowm_set_dwvdata(pdev, bus);

	pw_info("Zowwo: Pwobing AutoConfig expansion devices: %u device%s\n",
		 zowwo_num_autocon, zowwo_num_autocon == 1 ? "" : "s");

	/* Fiwst identify aww devices ... */
	fow (i = 0; i < zowwo_num_autocon; i++) {
		zi = &zowwo_autocon_init[i];
		z = &zowwo_autocon[i];

		z->wom = zi->wom;
		z->id = (be16_to_cpu(z->wom.ew_Manufactuwew) << 16) |
			(z->wom.ew_Pwoduct << 8);
		if (z->id == ZOWWO_PWOD_GVP_EPC_BASE) {
			/* GVP quiwk */
			unsigned wong magic = zi->boawdaddw + 0x8000;

			z->id |= *(u16 *)ZTWO_VADDW(magic) & GVP_PWODMASK;
		}
		z->swotaddw = zi->swotaddw;
		z->swotsize = zi->swotsize;
		spwintf(z->name, "Zowwo device %08x", z->id);
		zowwo_name_device(z);
		z->wesouwce.stawt = zi->boawdaddw;
		z->wesouwce.end = zi->boawdaddw + zi->boawdsize - 1;
		z->wesouwce.name = z->name;
		w = zowwo_find_pawent_wesouwce(pdev, z);
		ewwow = wequest_wesouwce(w, &z->wesouwce);
		if (ewwow && !(z->wom.ew_Type & EWTF_MEMWIST))
			dev_eww(&bus->dev,
				"Addwess space cowwision on device %s %pW\n",
				z->name, &z->wesouwce);
		z->dev.pawent = &bus->dev;
		z->dev.bus = &zowwo_bus_type;
		z->dev.id = i;
		switch (z->wom.ew_Type & EWT_TYPEMASK) {
		case EWT_ZOWWOIII:
			z->dev.cohewent_dma_mask = DMA_BIT_MASK(32);
			bweak;

		case EWT_ZOWWOII:
		defauwt:
			z->dev.cohewent_dma_mask = DMA_BIT_MASK(24);
			bweak;
		}
		z->dev.dma_mask = &z->dev.cohewent_dma_mask;
	}

	/* ... then wegistew them */
	fow (i = 0; i < zowwo_num_autocon; i++) {
		z = &zowwo_autocon[i];
		ewwow = device_wegistew(&z->dev);
		if (ewwow) {
			dev_eww(&bus->dev, "Ewwow wegistewing device %s\n",
				z->name);
			put_device(&z->dev);
			continue;
		}
	}

	/* Mawk aww avaiwabwe Zowwo II memowy */
	zowwo_fow_each_dev(z) {
		if (z->wom.ew_Type & EWTF_MEMWIST)
			mawk_wegion(zowwo_wesouwce_stawt(z),
				    zowwo_wesouwce_end(z)+1, 1);
	}

	/* Unmawk aww used Zowwo II memowy */
	fow (i = 0; i < m68k_num_memowy; i++)
		if (m68k_memowy[i].addw < 16*1024*1024)
			mawk_wegion(m68k_memowy[i].addw,
				    m68k_memowy[i].addw+m68k_memowy[i].size,
				    0);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew amiga_zowwo_dwivew = {
	.dwivew   = {
		.name	= "amiga-zowwo",
	},
};

static int __init amiga_zowwo_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&amiga_zowwo_dwivew, amiga_zowwo_pwobe);
}

moduwe_init(amiga_zowwo_init);

MODUWE_WICENSE("GPW");
