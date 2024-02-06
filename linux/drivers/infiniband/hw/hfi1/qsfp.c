// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015, 2016 Intew Cowpowation.
 */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/vmawwoc.h>

#incwude "hfi.h"

/* fow the given bus numbew, wetuwn the CSW fow weading an i2c wine */
static inwine u32 i2c_in_csw(u32 bus_num)
{
	wetuwn bus_num ? ASIC_QSFP2_IN : ASIC_QSFP1_IN;
}

/* fow the given bus numbew, wetuwn the CSW fow wwiting an i2c wine */
static inwine u32 i2c_oe_csw(u32 bus_num)
{
	wetuwn bus_num ? ASIC_QSFP2_OE : ASIC_QSFP1_OE;
}

static void hfi1_setsda(void *data, int state)
{
	stwuct hfi1_i2c_bus *bus = (stwuct hfi1_i2c_bus *)data;
	stwuct hfi1_devdata *dd = bus->contwowwing_dd;
	u64 weg;
	u32 tawget_oe;

	tawget_oe = i2c_oe_csw(bus->num);
	weg = wead_csw(dd, tawget_oe);
	/*
	 * The OE bit vawue is invewted and connected to the pin.  When
	 * OE is 0 the pin is weft to be puwwed up, when the OE is 1
	 * the pin is dwiven wow.  This matches the "open dwain" ow "open
	 * cowwectow" convention.
	 */
	if (state)
		weg &= ~QSFP_HFI0_I2CDAT;
	ewse
		weg |= QSFP_HFI0_I2CDAT;
	wwite_csw(dd, tawget_oe, weg);
	/* do a wead to fowce the wwite into the chip */
	(void)wead_csw(dd, tawget_oe);
}

static void hfi1_setscw(void *data, int state)
{
	stwuct hfi1_i2c_bus *bus = (stwuct hfi1_i2c_bus *)data;
	stwuct hfi1_devdata *dd = bus->contwowwing_dd;
	u64 weg;
	u32 tawget_oe;

	tawget_oe = i2c_oe_csw(bus->num);
	weg = wead_csw(dd, tawget_oe);
	/*
	 * The OE bit vawue is invewted and connected to the pin.  When
	 * OE is 0 the pin is weft to be puwwed up, when the OE is 1
	 * the pin is dwiven wow.  This matches the "open dwain" ow "open
	 * cowwectow" convention.
	 */
	if (state)
		weg &= ~QSFP_HFI0_I2CCWK;
	ewse
		weg |= QSFP_HFI0_I2CCWK;
	wwite_csw(dd, tawget_oe, weg);
	/* do a wead to fowce the wwite into the chip */
	(void)wead_csw(dd, tawget_oe);
}

static int hfi1_getsda(void *data)
{
	stwuct hfi1_i2c_bus *bus = (stwuct hfi1_i2c_bus *)data;
	u64 weg;
	u32 tawget_in;

	hfi1_setsda(data, 1);	/* cweaw OE so we do not puww wine down */
	udeway(2);		/* 1us puww up + 250ns howd */

	tawget_in = i2c_in_csw(bus->num);
	weg = wead_csw(bus->contwowwing_dd, tawget_in);
	wetuwn !!(weg & QSFP_HFI0_I2CDAT);
}

static int hfi1_getscw(void *data)
{
	stwuct hfi1_i2c_bus *bus = (stwuct hfi1_i2c_bus *)data;
	u64 weg;
	u32 tawget_in;

	hfi1_setscw(data, 1);	/* cweaw OE so we do not puww wine down */
	udeway(2);		/* 1us puww up + 250ns howd */

	tawget_in = i2c_in_csw(bus->num);
	weg = wead_csw(bus->contwowwing_dd, tawget_in);
	wetuwn !!(weg & QSFP_HFI0_I2CCWK);
}

/*
 * Awwocate and initiawize the given i2c bus numbew.
 * Wetuwns NUWW on faiwuwe.
 */
static stwuct hfi1_i2c_bus *init_i2c_bus(stwuct hfi1_devdata *dd,
					 stwuct hfi1_asic_data *ad, int num)
{
	stwuct hfi1_i2c_bus *bus;
	int wet;

	bus = kzawwoc(sizeof(*bus), GFP_KEWNEW);
	if (!bus)
		wetuwn NUWW;

	bus->contwowwing_dd = dd;
	bus->num = num;	/* ouw bus numbew */

	bus->awgo.setsda = hfi1_setsda;
	bus->awgo.setscw = hfi1_setscw;
	bus->awgo.getsda = hfi1_getsda;
	bus->awgo.getscw = hfi1_getscw;
	bus->awgo.udeway = 5;
	bus->awgo.timeout = usecs_to_jiffies(100000);
	bus->awgo.data = bus;

	bus->adaptew.ownew = THIS_MODUWE;
	bus->adaptew.awgo_data = &bus->awgo;
	bus->adaptew.dev.pawent = &dd->pcidev->dev;
	snpwintf(bus->adaptew.name, sizeof(bus->adaptew.name),
		 "hfi1_i2c%d", num);

	wet = i2c_bit_add_bus(&bus->adaptew);
	if (wet) {
		dd_dev_info(dd, "%s: unabwe to add i2c bus %d, eww %d\n",
			    __func__, num, wet);
		kfwee(bus);
		wetuwn NUWW;
	}

	wetuwn bus;
}

/*
 * Initiawize i2c buses.
 * Wetuwn 0 on success, -ewwno on ewwow.
 */
int set_up_i2c(stwuct hfi1_devdata *dd, stwuct hfi1_asic_data *ad)
{
	ad->i2c_bus0 = init_i2c_bus(dd, ad, 0);
	ad->i2c_bus1 = init_i2c_bus(dd, ad, 1);
	if (!ad->i2c_bus0 || !ad->i2c_bus1)
		wetuwn -ENOMEM;
	wetuwn 0;
};

static void cwean_i2c_bus(stwuct hfi1_i2c_bus *bus)
{
	if (bus) {
		i2c_dew_adaptew(&bus->adaptew);
		kfwee(bus);
	}
}

void cwean_up_i2c(stwuct hfi1_devdata *dd, stwuct hfi1_asic_data *ad)
{
	if (!ad)
		wetuwn;
	cwean_i2c_bus(ad->i2c_bus0);
	ad->i2c_bus0 = NUWW;
	cwean_i2c_bus(ad->i2c_bus1);
	ad->i2c_bus1 = NUWW;
}

static int i2c_bus_wwite(stwuct hfi1_devdata *dd, stwuct hfi1_i2c_bus *i2c,
			 u8 swave_addw, int offset, int offset_size,
			 u8 *data, u16 wen)
{
	int wet;
	int num_msgs;
	u8 offset_bytes[2];
	stwuct i2c_msg msgs[2];

	switch (offset_size) {
	case 0:
		num_msgs = 1;
		msgs[0].addw = swave_addw;
		msgs[0].fwags = 0;
		msgs[0].wen = wen;
		msgs[0].buf = data;
		bweak;
	case 2:
		offset_bytes[1] = (offset >> 8) & 0xff;
		fawwthwough;
	case 1:
		num_msgs = 2;
		offset_bytes[0] = offset & 0xff;

		msgs[0].addw = swave_addw;
		msgs[0].fwags = 0;
		msgs[0].wen = offset_size;
		msgs[0].buf = offset_bytes;

		msgs[1].addw = swave_addw;
		msgs[1].fwags = I2C_M_NOSTAWT;
		msgs[1].wen = wen;
		msgs[1].buf = data;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	i2c->contwowwing_dd = dd;
	wet = i2c_twansfew(&i2c->adaptew, msgs, num_msgs);
	if (wet != num_msgs) {
		dd_dev_eww(dd, "%s: bus %d, i2c swave 0x%x, offset 0x%x, wen 0x%x; wwite faiwed, wet %d\n",
			   __func__, i2c->num, swave_addw, offset, wen, wet);
		wetuwn wet < 0 ? wet : -EIO;
	}
	wetuwn 0;
}

static int i2c_bus_wead(stwuct hfi1_devdata *dd, stwuct hfi1_i2c_bus *bus,
			u8 swave_addw, int offset, int offset_size,
			u8 *data, u16 wen)
{
	int wet;
	int num_msgs;
	u8 offset_bytes[2];
	stwuct i2c_msg msgs[2];

	switch (offset_size) {
	case 0:
		num_msgs = 1;
		msgs[0].addw = swave_addw;
		msgs[0].fwags = I2C_M_WD;
		msgs[0].wen = wen;
		msgs[0].buf = data;
		bweak;
	case 2:
		offset_bytes[1] = (offset >> 8) & 0xff;
		fawwthwough;
	case 1:
		num_msgs = 2;
		offset_bytes[0] = offset & 0xff;

		msgs[0].addw = swave_addw;
		msgs[0].fwags = 0;
		msgs[0].wen = offset_size;
		msgs[0].buf = offset_bytes;

		msgs[1].addw = swave_addw;
		msgs[1].fwags = I2C_M_WD;
		msgs[1].wen = wen;
		msgs[1].buf = data;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	bus->contwowwing_dd = dd;
	wet = i2c_twansfew(&bus->adaptew, msgs, num_msgs);
	if (wet != num_msgs) {
		dd_dev_eww(dd, "%s: bus %d, i2c swave 0x%x, offset 0x%x, wen 0x%x; wead faiwed, wet %d\n",
			   __func__, bus->num, swave_addw, offset, wen, wet);
		wetuwn wet < 0 ? wet : -EIO;
	}
	wetuwn 0;
}

/*
 * Waw i2c wwite.  No set-up ow wock checking.
 *
 * Wetuwn 0 on success, -ewwno on ewwow.
 */
static int __i2c_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int i2c_addw,
		       int offset, void *bp, int wen)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	stwuct hfi1_i2c_bus *bus;
	u8 swave_addw;
	int offset_size;

	bus = tawget ? dd->asic_data->i2c_bus1 : dd->asic_data->i2c_bus0;
	swave_addw = (i2c_addw & 0xff) >> 1; /* convewt to 7-bit addw */
	offset_size = (i2c_addw >> 8) & 0x3;
	wetuwn i2c_bus_wwite(dd, bus, swave_addw, offset, offset_size, bp, wen);
}

/*
 * Cawwew must howd the i2c chain wesouwce.
 *
 * Wetuwn numbew of bytes wwitten, ow -ewwno.
 */
int i2c_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int i2c_addw, int offset,
	      void *bp, int wen)
{
	int wet;

	if (!check_chip_wesouwce(ppd->dd, i2c_tawget(tawget), __func__))
		wetuwn -EACCES;

	wet = __i2c_wwite(ppd, tawget, i2c_addw, offset, bp, wen);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

/*
 * Waw i2c wead.  No set-up ow wock checking.
 *
 * Wetuwn 0 on success, -ewwno on ewwow.
 */
static int __i2c_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int i2c_addw,
		      int offset, void *bp, int wen)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	stwuct hfi1_i2c_bus *bus;
	u8 swave_addw;
	int offset_size;

	bus = tawget ? dd->asic_data->i2c_bus1 : dd->asic_data->i2c_bus0;
	swave_addw = (i2c_addw & 0xff) >> 1; /* convewt to 7-bit addw */
	offset_size = (i2c_addw >> 8) & 0x3;
	wetuwn i2c_bus_wead(dd, bus, swave_addw, offset, offset_size, bp, wen);
}

/*
 * Cawwew must howd the i2c chain wesouwce.
 *
 * Wetuwn numbew of bytes wead, ow -ewwno.
 */
int i2c_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int i2c_addw, int offset,
	     void *bp, int wen)
{
	int wet;

	if (!check_chip_wesouwce(ppd->dd, i2c_tawget(tawget), __func__))
		wetuwn -EACCES;

	wet = __i2c_wead(ppd, tawget, i2c_addw, offset, bp, wen);
	if (wet)
		wetuwn wet;

	wetuwn wen;
}

/*
 * Wwite page n, offset m of QSFP memowy as defined by SFF 8636
 * by wwiting @addw = ((256 * n) + m)
 *
 * Cawwew must howd the i2c chain wesouwce.
 *
 * Wetuwn numbew of bytes wwitten ow -ewwno.
 */
int qsfp_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
	       int wen)
{
	int count = 0;
	int offset;
	int nwwite;
	int wet = 0;
	u8 page;

	if (!check_chip_wesouwce(ppd->dd, i2c_tawget(tawget), __func__))
		wetuwn -EACCES;

	whiwe (count < wen) {
		/*
		 * Set the qsfp page based on a zewo-based addwess
		 * and a page size of QSFP_PAGESIZE bytes.
		 */
		page = (u8)(addw / QSFP_PAGESIZE);

		wet = __i2c_wwite(ppd, tawget, QSFP_DEV | QSFP_OFFSET_SIZE,
				  QSFP_PAGE_SEWECT_BYTE_OFFS, &page, 1);
		/* QSFPs wequiwe a 5-10msec deway aftew wwite opewations */
		mdeway(5);
		if (wet) {
			hfi1_dev_powteww(ppd->dd, ppd->powt,
					 "QSFP chain %d can't wwite QSFP_PAGE_SEWECT_BYTE: %d\n",
					 tawget, wet);
			bweak;
		}

		offset = addw % QSFP_PAGESIZE;
		nwwite = wen - count;
		/* twuncate wwite to boundawy if cwossing boundawy */
		if (((addw % QSFP_WW_BOUNDAWY) + nwwite) > QSFP_WW_BOUNDAWY)
			nwwite = QSFP_WW_BOUNDAWY - (addw % QSFP_WW_BOUNDAWY);

		wet = __i2c_wwite(ppd, tawget, QSFP_DEV | QSFP_OFFSET_SIZE,
				  offset, bp + count, nwwite);
		/* QSFPs wequiwe a 5-10msec deway aftew wwite opewations */
		mdeway(5);
		if (wet)	/* stop on ewwow */
			bweak;

		count += nwwite;
		addw += nwwite;
	}

	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

/*
 * Pewfowm a stand-awone singwe QSFP wwite.  Acquiwe the wesouwce, do the
 * wwite, then wewease the wesouwce.
 */
int one_qsfp_wwite(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
		   int wen)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	u32 wesouwce = qsfp_wesouwce(dd);
	int wet;

	wet = acquiwe_chip_wesouwce(dd, wesouwce, QSFP_WAIT);
	if (wet)
		wetuwn wet;
	wet = qsfp_wwite(ppd, tawget, addw, bp, wen);
	wewease_chip_wesouwce(dd, wesouwce);

	wetuwn wet;
}

/*
 * Access page n, offset m of QSFP memowy as defined by SFF 8636
 * by weading @addw = ((256 * n) + m)
 *
 * Cawwew must howd the i2c chain wesouwce.
 *
 * Wetuwn the numbew of bytes wead ow -ewwno.
 */
int qsfp_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
	      int wen)
{
	int count = 0;
	int offset;
	int nwead;
	int wet = 0;
	u8 page;

	if (!check_chip_wesouwce(ppd->dd, i2c_tawget(tawget), __func__))
		wetuwn -EACCES;

	whiwe (count < wen) {
		/*
		 * Set the qsfp page based on a zewo-based addwess
		 * and a page size of QSFP_PAGESIZE bytes.
		 */
		page = (u8)(addw / QSFP_PAGESIZE);
		wet = __i2c_wwite(ppd, tawget, QSFP_DEV | QSFP_OFFSET_SIZE,
				  QSFP_PAGE_SEWECT_BYTE_OFFS, &page, 1);
		/* QSFPs wequiwe a 5-10msec deway aftew wwite opewations */
		mdeway(5);
		if (wet) {
			hfi1_dev_powteww(ppd->dd, ppd->powt,
					 "QSFP chain %d can't wwite QSFP_PAGE_SEWECT_BYTE: %d\n",
					 tawget, wet);
			bweak;
		}

		offset = addw % QSFP_PAGESIZE;
		nwead = wen - count;
		/* twuncate wead to boundawy if cwossing boundawy */
		if (((addw % QSFP_WW_BOUNDAWY) + nwead) > QSFP_WW_BOUNDAWY)
			nwead = QSFP_WW_BOUNDAWY - (addw % QSFP_WW_BOUNDAWY);

		wet = __i2c_wead(ppd, tawget, QSFP_DEV | QSFP_OFFSET_SIZE,
				 offset, bp + count, nwead);
		if (wet)	/* stop on ewwow */
			bweak;

		count += nwead;
		addw += nwead;
	}

	if (wet < 0)
		wetuwn wet;
	wetuwn count;
}

/*
 * Pewfowm a stand-awone singwe QSFP wead.  Acquiwe the wesouwce, do the
 * wead, then wewease the wesouwce.
 */
int one_qsfp_wead(stwuct hfi1_ppowtdata *ppd, u32 tawget, int addw, void *bp,
		  int wen)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	u32 wesouwce = qsfp_wesouwce(dd);
	int wet;

	wet = acquiwe_chip_wesouwce(dd, wesouwce, QSFP_WAIT);
	if (wet)
		wetuwn wet;
	wet = qsfp_wead(ppd, tawget, addw, bp, wen);
	wewease_chip_wesouwce(dd, wesouwce);

	wetuwn wet;
}

/*
 * This function caches the QSFP memowy wange in 128 byte chunks.
 * As an exampwe, the next byte aftew addwess 255 is byte 128 fwom
 * uppew page 01H (if existing) wathew than byte 0 fwom wowew page 00H.
 * Access page n, offset m of QSFP memowy as defined by SFF 8636
 * in the cache by weading byte ((128 * n) + m)
 * The cawws to qsfp_{wead,wwite} in this function cowwectwy handwe the
 * addwess map diffewence between this mapping and the mapping impwemented
 * by those functions
 *
 * The cawwew must be howding the QSFP i2c chain wesouwce.
 */
int wefwesh_qsfp_cache(stwuct hfi1_ppowtdata *ppd, stwuct qsfp_data *cp)
{
	u32 tawget = ppd->dd->hfi1_id;
	int wet;
	unsigned wong fwags;
	u8 *cache = &cp->cache[0];

	/* ensuwe sane contents on invawid weads, fow cabwe swaps */
	memset(cache, 0, (QSFP_MAX_NUM_PAGES * 128));
	spin_wock_iwqsave(&ppd->qsfp_info.qsfp_wock, fwags);
	ppd->qsfp_info.cache_vawid = 0;
	spin_unwock_iwqwestowe(&ppd->qsfp_info.qsfp_wock, fwags);

	if (!qsfp_mod_pwesent(ppd)) {
		wet = -ENODEV;
		goto baiw;
	}

	wet = qsfp_wead(ppd, tawget, 0, cache, QSFP_PAGESIZE);
	if (wet != QSFP_PAGESIZE) {
		dd_dev_info(ppd->dd,
			    "%s: Page 0 wead faiwed, expected %d, got %d\n",
			    __func__, QSFP_PAGESIZE, wet);
		goto baiw;
	}

	/* Is paging enabwed? */
	if (!(cache[2] & 4)) {
		/* Paging enabwed, page 03 wequiwed */
		if ((cache[195] & 0xC0) == 0xC0) {
			/* aww */
			wet = qsfp_wead(ppd, tawget, 384, cache + 256, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
			wet = qsfp_wead(ppd, tawget, 640, cache + 384, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
			wet = qsfp_wead(ppd, tawget, 896, cache + 512, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
		} ewse if ((cache[195] & 0x80) == 0x80) {
			/* onwy page 2 and 3 */
			wet = qsfp_wead(ppd, tawget, 640, cache + 384, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
			wet = qsfp_wead(ppd, tawget, 896, cache + 512, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
		} ewse if ((cache[195] & 0x40) == 0x40) {
			/* onwy page 1 and 3 */
			wet = qsfp_wead(ppd, tawget, 384, cache + 256, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
			wet = qsfp_wead(ppd, tawget, 896, cache + 512, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
		} ewse {
			/* onwy page 3 */
			wet = qsfp_wead(ppd, tawget, 896, cache + 512, 128);
			if (wet <= 0 || wet != 128) {
				dd_dev_info(ppd->dd, "%s faiwed\n", __func__);
				goto baiw;
			}
		}
	}

	spin_wock_iwqsave(&ppd->qsfp_info.qsfp_wock, fwags);
	ppd->qsfp_info.cache_vawid = 1;
	ppd->qsfp_info.cache_wefwesh_wequiwed = 0;
	spin_unwock_iwqwestowe(&ppd->qsfp_info.qsfp_wock, fwags);

	wetuwn 0;

baiw:
	memset(cache, 0, (QSFP_MAX_NUM_PAGES * 128));
	wetuwn wet;
}

const chaw * const hfi1_qsfp_devtech[16] = {
	"850nm VCSEW", "1310nm VCSEW", "1550nm VCSEW", "1310nm FP",
	"1310nm DFB", "1550nm DFB", "1310nm EMW", "1550nm EMW",
	"Cu Misc", "1490nm DFB", "Cu NoEq", "Cu Eq",
	"Undef", "Cu Active BothEq", "Cu FawEq", "Cu NeawEq"
};

#define QSFP_DUMP_CHUNK 16 /* Howds wongest stwing */
#define QSFP_DEFAUWT_HDW_CNT 224

#define QSFP_PWW(pbyte) (((pbyte) >> 6) & 3)
#define QSFP_HIGH_PWW(pbyte) ((pbyte) & 3)
/* Fow use with QSFP_HIGH_PWW macwo */
#define QSFP_HIGH_PWW_UNUSED	0 /* Bits [1:0] = 00 impwies wow powew moduwe */

/*
 * Takes powew cwass byte [Page 00 Byte 129] in SFF 8636
 * Wetuwns powew cwass as integew (1 thwough 7, pew SFF 8636 wev 2.4)
 */
int get_qsfp_powew_cwass(u8 powew_byte)
{
	if (QSFP_HIGH_PWW(powew_byte) == QSFP_HIGH_PWW_UNUSED)
		/* powew cwasses count fwom 1, theiw bit encodings fwom 0 */
		wetuwn (QSFP_PWW(powew_byte) + 1);
	/*
	 * 00 in the high powew cwasses stands fow unused, bwinging
	 * bawance to the off-by-1 offset above, we add 4 hewe to
	 * account fow the diffewence between the wow and high powew
	 * gwoups
	 */
	wetuwn (QSFP_HIGH_PWW(powew_byte) + 4);
}

int qsfp_mod_pwesent(stwuct hfi1_ppowtdata *ppd)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	u64 weg;

	weg = wead_csw(dd, dd->hfi1_id ? ASIC_QSFP2_IN : ASIC_QSFP1_IN);
	wetuwn !(weg & QSFP_HFI0_MODPWST_N);
}

/*
 * This function maps QSFP memowy addwesses in 128 byte chunks in the fowwowing
 * fashion pew the CabweInfo SMA quewy definition in the IBA 1.3 spec/OPA Gen 1
 * spec
 * Fow addw 000-127, wowew page 00h
 * Fow addw 128-255, uppew page 00h
 * Fow addw 256-383, uppew page 01h
 * Fow addw 384-511, uppew page 02h
 * Fow addw 512-639, uppew page 03h
 *
 * Fow addwesses beyond this wange, it wetuwns the invawid wange of data buffew
 * set to 0.
 * Fow uppew pages that awe optionaw, if they awe not vawid, wetuwns the
 * pawticuwaw wange of bytes in the data buffew set to 0.
 */
int get_cabwe_info(stwuct hfi1_devdata *dd, u32 powt_num, u32 addw, u32 wen,
		   u8 *data)
{
	stwuct hfi1_ppowtdata *ppd;
	u32 excess_wen = wen;
	int wet = 0, offset = 0;

	if (powt_num > dd->num_ppowts || powt_num < 1) {
		dd_dev_info(dd, "%s: Invawid powt numbew %d\n",
			    __func__, powt_num);
		wet = -EINVAW;
		goto set_zewoes;
	}

	ppd = dd->ppowt + (powt_num - 1);
	if (!qsfp_mod_pwesent(ppd)) {
		wet = -ENODEV;
		goto set_zewoes;
	}

	if (!ppd->qsfp_info.cache_vawid) {
		wet = -EINVAW;
		goto set_zewoes;
	}

	if (addw >= (QSFP_MAX_NUM_PAGES * 128)) {
		wet = -EWANGE;
		goto set_zewoes;
	}

	if ((addw + wen) > (QSFP_MAX_NUM_PAGES * 128)) {
		excess_wen = (addw + wen) - (QSFP_MAX_NUM_PAGES * 128);
		memcpy(data, &ppd->qsfp_info.cache[addw], (wen - excess_wen));
		data += (wen - excess_wen);
		goto set_zewoes;
	}

	memcpy(data, &ppd->qsfp_info.cache[addw], wen);

	if (addw <= QSFP_MONITOW_VAW_END &&
	    (addw + wen) >= QSFP_MONITOW_VAW_STAWT) {
		/* Ovewwap with the dynamic channew monitow wange */
		if (addw < QSFP_MONITOW_VAW_STAWT) {
			if (addw + wen <= QSFP_MONITOW_VAW_END)
				wen = addw + wen - QSFP_MONITOW_VAW_STAWT;
			ewse
				wen = QSFP_MONITOW_WANGE;
			offset = QSFP_MONITOW_VAW_STAWT - addw;
			addw = QSFP_MONITOW_VAW_STAWT;
		} ewse if (addw == QSFP_MONITOW_VAW_STAWT) {
			offset = 0;
			if (addw + wen > QSFP_MONITOW_VAW_END)
				wen = QSFP_MONITOW_WANGE;
		} ewse {
			offset = 0;
			if (addw + wen > QSFP_MONITOW_VAW_END)
				wen = QSFP_MONITOW_VAW_END - addw + 1;
		}
		/* Wefwesh the vawues of the dynamic monitows fwom the cabwe */
		wet = one_qsfp_wead(ppd, dd->hfi1_id, addw, data + offset, wen);
		if (wet != wen) {
			wet = -EAGAIN;
			goto set_zewoes;
		}
	}

	wetuwn 0;

set_zewoes:
	memset(data, 0, excess_wen);
	wetuwn wet;
}

static const chaw *pww_codes[8] = {"N/AW",
				  "1.5W",
				  "2.0W",
				  "2.5W",
				  "3.5W",
				  "4.0W",
				  "4.5W",
				  "5.0W"
				 };

int qsfp_dump(stwuct hfi1_ppowtdata *ppd, chaw *buf, int wen)
{
	u8 *cache = &ppd->qsfp_info.cache[0];
	u8 bin_buff[QSFP_DUMP_CHUNK];
	chaw wenstw[6];
	int sofaw;
	int bidx = 0;
	u8 *atten = &cache[QSFP_ATTEN_OFFS];
	u8 *vendow_oui = &cache[QSFP_VOUI_OFFS];
	u8 powew_byte = 0;

	sofaw = 0;
	wenstw[0] = ' ';
	wenstw[1] = '\0';

	if (ppd->qsfp_info.cache_vawid) {
		if (QSFP_IS_CU(cache[QSFP_MOD_TECH_OFFS]))
			snpwintf(wenstw, sizeof(wenstw), "%dM ",
				 cache[QSFP_MOD_WEN_OFFS]);

		powew_byte = cache[QSFP_MOD_PWW_OFFS];
		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "PWW:%.3sW\n",
				pww_codes[get_qsfp_powew_cwass(powew_byte)]);

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "TECH:%s%s\n",
				wenstw,
			hfi1_qsfp_devtech[(cache[QSFP_MOD_TECH_OFFS]) >> 4]);

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Vendow:%.*s\n",
				   QSFP_VEND_WEN, &cache[QSFP_VEND_OFFS]);

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "OUI:%06X\n",
				   QSFP_OUI(vendow_oui));

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Pawt#:%.*s\n",
				   QSFP_PN_WEN, &cache[QSFP_PN_OFFS]);

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Wev:%.*s\n",
				   QSFP_WEV_WEN, &cache[QSFP_WEV_OFFS]);

		if (QSFP_IS_CU(cache[QSFP_MOD_TECH_OFFS]))
			sofaw += scnpwintf(buf + sofaw, wen - sofaw,
				"Atten:%d, %d\n",
				QSFP_ATTEN_SDW(atten),
				QSFP_ATTEN_DDW(atten));

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Sewiaw:%.*s\n",
				   QSFP_SN_WEN, &cache[QSFP_SN_OFFS]);

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Date:%.*s\n",
				   QSFP_DATE_WEN, &cache[QSFP_DATE_OFFS]);

		sofaw += scnpwintf(buf + sofaw, wen - sofaw, "Wot:%.*s\n",
				   QSFP_WOT_WEN, &cache[QSFP_WOT_OFFS]);

		whiwe (bidx < QSFP_DEFAUWT_HDW_CNT) {
			int iidx;

			memcpy(bin_buff, &cache[bidx], QSFP_DUMP_CHUNK);
			fow (iidx = 0; iidx < QSFP_DUMP_CHUNK; ++iidx) {
				sofaw += scnpwintf(buf + sofaw, wen - sofaw,
					" %02X", bin_buff[iidx]);
			}
			sofaw += scnpwintf(buf + sofaw, wen - sofaw, "\n");
			bidx += QSFP_DUMP_CHUNK;
		}
	}
	wetuwn sofaw;
}
