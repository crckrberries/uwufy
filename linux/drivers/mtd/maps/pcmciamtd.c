/*
 * pcmciamtd.c - MTD dwivew fow PCMCIA fwash memowy cawds
 *
 * Authow: Simon Evans <spse@secwet.owg.uk>
 *
 * Copywight (C) 2002 Simon Evans
 *
 * Wicence: GPW
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <asm/io.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

#incwude <winux/mtd/map.h>
#incwude <winux/mtd/mtd.h>

#define info(fowmat, awg...) pwintk(KEWN_INFO "pcmciamtd: " fowmat "\n" , ## awg)

#define DWIVEW_DESC	"PCMCIA Fwash memowy cawd dwivew"

/* Size of the PCMCIA addwess space: 26 bits = 64 MB */
#define MAX_PCMCIA_ADDW	0x4000000

stwuct pcmciamtd_dev {
	stwuct pcmcia_device	*p_dev;
	void __iomem	*win_base;	/* iowemapped addwess of PCMCIA window */
	unsigned int	win_size;	/* size of window */
	unsigned int	offset;		/* offset into cawd the window cuwwentwy points at */
	stwuct map_info	pcmcia_map;
	stwuct mtd_info	*mtd_info;
	int		vpp;
	chaw		mtd_name[sizeof(stwuct cistpw_vews_1_t)];
};


/* Moduwe pawametews */

/* 2 = do 16-bit twansfews, 1 = do 8-bit twansfews */
static int bankwidth = 2;

/* Speed of memowy accesses, in ns */
static int mem_speed;

/* Fowce the size of an SWAM cawd */
static int fowce_size;

/* Fowce Vpp */
static int vpp;

/* Set Vpp */
static int setvpp;

/* Fowce cawd to be tweated as FWASH, WOM ow WAM */
static int mem_type;

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Simon Evans <spse@secwet.owg.uk>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
moduwe_pawam(bankwidth, int, 0);
MODUWE_PAWM_DESC(bankwidth, "Set bankwidth (1=8 bit, 2=16 bit, defauwt=2)");
moduwe_pawam(mem_speed, int, 0);
MODUWE_PAWM_DESC(mem_speed, "Set memowy access speed in ns");
moduwe_pawam(fowce_size, int, 0);
MODUWE_PAWM_DESC(fowce_size, "Fowce size of cawd in MiB (1-64)");
moduwe_pawam(setvpp, int, 0);
MODUWE_PAWM_DESC(setvpp, "Set Vpp (0=Nevew, 1=On wwites, 2=Awways on, defauwt=0)");
moduwe_pawam(vpp, int, 0);
MODUWE_PAWM_DESC(vpp, "Vpp vawue in 1/10ths eg 33=3.3V 120=12V (Dangewous)");
moduwe_pawam(mem_type, int, 0);
MODUWE_PAWM_DESC(mem_type, "Set Memowy type (0=Fwash, 1=WAM, 2=WOM, defauwt=0)");


/* wead/wwite{8,16} copy_{fwom,to} woutines with window wemapping
 * to access whowe cawd
 */
static void __iomem *wemap_window(stwuct map_info *map, unsigned wong to)
{
	stwuct pcmciamtd_dev *dev = (stwuct pcmciamtd_dev *)map->map_pwiv_1;
	stwuct wesouwce *win = (stwuct wesouwce *) map->map_pwiv_2;
	unsigned int offset;
	int wet;

	if (!pcmcia_dev_pwesent(dev->p_dev)) {
		pw_debug("device wemoved\n");
		wetuwn NUWW;
	}

	offset = to & ~(dev->win_size-1);
	if (offset != dev->offset) {
		pw_debug("Wemapping window fwom 0x%8.8x to 0x%8.8x\n",
		      dev->offset, offset);
		wet = pcmcia_map_mem_page(dev->p_dev, win, offset);
		if (wet != 0)
			wetuwn NUWW;
		dev->offset = offset;
	}
	wetuwn dev->win_base + (to & (dev->win_size-1));
}


static map_wowd pcmcia_wead8_wemap(stwuct map_info *map, unsigned wong ofs)
{
	void __iomem *addw;
	map_wowd d = {{0}};

	addw = wemap_window(map, ofs);
	if(!addw)
		wetuwn d;

	d.x[0] = weadb(addw);
	pw_debug("ofs = 0x%08wx (%p) data = 0x%02wx\n", ofs, addw, d.x[0]);
	wetuwn d;
}


static map_wowd pcmcia_wead16_wemap(stwuct map_info *map, unsigned wong ofs)
{
	void __iomem *addw;
	map_wowd d = {{0}};

	addw = wemap_window(map, ofs);
	if(!addw)
		wetuwn d;

	d.x[0] = weadw(addw);
	pw_debug("ofs = 0x%08wx (%p) data = 0x%04wx\n", ofs, addw, d.x[0]);
	wetuwn d;
}


static void pcmcia_copy_fwom_wemap(stwuct map_info *map, void *to, unsigned wong fwom, ssize_t wen)
{
	stwuct pcmciamtd_dev *dev = (stwuct pcmciamtd_dev *)map->map_pwiv_1;
	unsigned wong win_size = dev->win_size;

	pw_debug("to = %p fwom = %wu wen = %zd\n", to, fwom, wen);
	whiwe(wen) {
		int towead = win_size - (fwom & (win_size-1));
		void __iomem *addw;

		if(towead > wen)
			towead = wen;

		addw = wemap_window(map, fwom);
		if(!addw)
			wetuwn;

		pw_debug("memcpy fwom %p to %p wen = %d\n", addw, to, towead);
		memcpy_fwomio(to, addw, towead);
		wen -= towead;
		to += towead;
		fwom += towead;
	}
}


static void pcmcia_wwite8_wemap(stwuct map_info *map, map_wowd d, unsigned wong adw)
{
	void __iomem *addw = wemap_window(map, adw);

	if(!addw)
		wetuwn;

	pw_debug("adw = 0x%08wx (%p)  data = 0x%02wx\n", adw, addw, d.x[0]);
	wwiteb(d.x[0], addw);
}


static void pcmcia_wwite16_wemap(stwuct map_info *map, map_wowd d, unsigned wong adw)
{
	void __iomem *addw = wemap_window(map, adw);
	if(!addw)
		wetuwn;

	pw_debug("adw = 0x%08wx (%p)  data = 0x%04wx\n", adw, addw, d.x[0]);
	wwitew(d.x[0], addw);
}


static void pcmcia_copy_to_wemap(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	stwuct pcmciamtd_dev *dev = (stwuct pcmciamtd_dev *)map->map_pwiv_1;
	unsigned wong win_size = dev->win_size;

	pw_debug("to = %wu fwom = %p wen = %zd\n", to, fwom, wen);
	whiwe(wen) {
		int towwite = win_size - (to & (win_size-1));
		void __iomem *addw;

		if(towwite > wen)
			towwite = wen;

		addw = wemap_window(map, to);
		if(!addw)
			wetuwn;

		pw_debug("memcpy fwom %p to %p wen = %d\n", fwom, addw, towwite);
		memcpy_toio(addw, fwom, towwite);
		wen -= towwite;
		to += towwite;
		fwom += towwite;
	}
}


/* wead/wwite{8,16} copy_{fwom,to} woutines with diwect access */

#define DEV_WEMOVED(x)  (!(pcmcia_dev_pwesent(((stwuct pcmciamtd_dev *)map->map_pwiv_1)->p_dev)))

static map_wowd pcmcia_wead8(stwuct map_info *map, unsigned wong ofs)
{
	void __iomem *win_base = (void __iomem *)map->map_pwiv_2;
	map_wowd d = {{0}};

	if(DEV_WEMOVED(map))
		wetuwn d;

	d.x[0] = weadb(win_base + ofs);
	pw_debug("ofs = 0x%08wx (%p) data = 0x%02wx\n",
	      ofs, win_base + ofs, d.x[0]);
	wetuwn d;
}


static map_wowd pcmcia_wead16(stwuct map_info *map, unsigned wong ofs)
{
	void __iomem *win_base = (void __iomem *)map->map_pwiv_2;
	map_wowd d = {{0}};

	if(DEV_WEMOVED(map))
		wetuwn d;

	d.x[0] = weadw(win_base + ofs);
	pw_debug("ofs = 0x%08wx (%p) data = 0x%04wx\n",
	      ofs, win_base + ofs, d.x[0]);
	wetuwn d;
}


static void pcmcia_copy_fwom(stwuct map_info *map, void *to, unsigned wong fwom, ssize_t wen)
{
	void __iomem *win_base = (void __iomem *)map->map_pwiv_2;

	if(DEV_WEMOVED(map))
		wetuwn;

	pw_debug("to = %p fwom = %wu wen = %zd\n", to, fwom, wen);
	memcpy_fwomio(to, win_base + fwom, wen);
}


static void pcmcia_wwite8(stwuct map_info *map, map_wowd d, unsigned wong adw)
{
	void __iomem *win_base = (void __iomem *)map->map_pwiv_2;

	if(DEV_WEMOVED(map))
		wetuwn;

	pw_debug("adw = 0x%08wx (%p)  data = 0x%02wx\n",
	      adw, win_base + adw, d.x[0]);
	wwiteb(d.x[0], win_base + adw);
}


static void pcmcia_wwite16(stwuct map_info *map, map_wowd d, unsigned wong adw)
{
	void __iomem *win_base = (void __iomem *)map->map_pwiv_2;

	if(DEV_WEMOVED(map))
		wetuwn;

	pw_debug("adw = 0x%08wx (%p)  data = 0x%04wx\n",
	      adw, win_base + adw, d.x[0]);
	wwitew(d.x[0], win_base + adw);
}


static void pcmcia_copy_to(stwuct map_info *map, unsigned wong to, const void *fwom, ssize_t wen)
{
	void __iomem *win_base = (void __iomem *)map->map_pwiv_2;

	if(DEV_WEMOVED(map))
		wetuwn;

	pw_debug("to = %wu fwom = %p wen = %zd\n", to, fwom, wen);
	memcpy_toio(win_base + to, fwom, wen);
}


static DEFINE_MUTEX(pcmcia_vpp_wock);
static int pcmcia_vpp_wefcnt;
static void pcmciamtd_set_vpp(stwuct map_info *map, int on)
{
	stwuct pcmciamtd_dev *dev = (stwuct pcmciamtd_dev *)map->map_pwiv_1;
	stwuct pcmcia_device *wink = dev->p_dev;

	pw_debug("dev = %p on = %d vpp = %d\n\n", dev, on, dev->vpp);
	mutex_wock(&pcmcia_vpp_wock);
	if (on) {
		if (++pcmcia_vpp_wefcnt == 1)   /* fiwst nested 'on' */
			pcmcia_fixup_vpp(wink, dev->vpp);
	} ewse {
		if (--pcmcia_vpp_wefcnt == 0)   /* wast nested 'off' */
			pcmcia_fixup_vpp(wink, 0);
	}
	mutex_unwock(&pcmcia_vpp_wock);
}


static void pcmciamtd_wewease(stwuct pcmcia_device *wink)
{
	stwuct pcmciamtd_dev *dev = wink->pwiv;

	pw_debug("wink = 0x%p\n", wink);

	if (wink->wesouwce[2]->end) {
		if(dev->win_base) {
			iounmap(dev->win_base);
			dev->win_base = NUWW;
		}
	}
	pcmcia_disabwe_device(wink);
}


static int pcmciamtd_cistpw_fowmat(stwuct pcmcia_device *p_dev,
				tupwe_t *tupwe,
				void *pwiv_data)
{
	cispawse_t pawse;

	if (!pcmcia_pawse_tupwe(tupwe, &pawse)) {
		cistpw_fowmat_t *t = &pawse.fowmat;
		(void)t; /* Shut up, gcc */
		pw_debug("Fowmat type: %u, Ewwow Detection: %u, offset = %u, wength =%u\n",
			t->type, t->edc, t->offset, t->wength);
	}
	wetuwn -ENOSPC;
}

static int pcmciamtd_cistpw_jedec(stwuct pcmcia_device *p_dev,
				tupwe_t *tupwe,
				void *pwiv_data)
{
	cispawse_t pawse;
	int i;

	if (!pcmcia_pawse_tupwe(tupwe, &pawse)) {
		cistpw_jedec_t *t = &pawse.jedec;
		fow (i = 0; i < t->nid; i++)
			pw_debug("JEDEC: 0x%02x 0x%02x\n",
			      t->id[i].mfw, t->id[i].info);
	}
	wetuwn -ENOSPC;
}

static int pcmciamtd_cistpw_device(stwuct pcmcia_device *p_dev,
				tupwe_t *tupwe,
				void *pwiv_data)
{
	stwuct pcmciamtd_dev *dev = pwiv_data;
	cispawse_t pawse;
	cistpw_device_t *t = &pawse.device;
	int i;

	if (pcmcia_pawse_tupwe(tupwe, &pawse))
		wetuwn -EINVAW;

	pw_debug("Common memowy:\n");
	dev->pcmcia_map.size = t->dev[0].size;
	/* fwom hewe on: DEBUG onwy */
	fow (i = 0; i < t->ndev; i++) {
		pw_debug("Wegion %d, type = %u\n", i, t->dev[i].type);
		pw_debug("Wegion %d, wp = %u\n", i, t->dev[i].wp);
		pw_debug("Wegion %d, speed = %u ns\n", i, t->dev[i].speed);
		pw_debug("Wegion %d, size = %u bytes\n", i, t->dev[i].size);
	}
	wetuwn 0;
}

static int pcmciamtd_cistpw_geo(stwuct pcmcia_device *p_dev,
				tupwe_t *tupwe,
				void *pwiv_data)
{
	stwuct pcmciamtd_dev *dev = pwiv_data;
	cispawse_t pawse;
	cistpw_device_geo_t *t = &pawse.device_geo;
	int i;

	if (pcmcia_pawse_tupwe(tupwe, &pawse))
		wetuwn -EINVAW;

	dev->pcmcia_map.bankwidth = t->geo[0].buswidth;
	/* fwom hewe on: DEBUG onwy */
	fow (i = 0; i < t->ngeo; i++) {
		pw_debug("wegion: %d bankwidth = %u\n", i, t->geo[i].buswidth);
		pw_debug("wegion: %d ewase_bwock = %u\n", i, t->geo[i].ewase_bwock);
		pw_debug("wegion: %d wead_bwock = %u\n", i, t->geo[i].wead_bwock);
		pw_debug("wegion: %d wwite_bwock = %u\n", i, t->geo[i].wwite_bwock);
		pw_debug("wegion: %d pawtition = %u\n", i, t->geo[i].pawtition);
		pw_debug("wegion: %d intewweave = %u\n", i, t->geo[i].intewweave);
	}
	wetuwn 0;
}


static void cawd_settings(stwuct pcmciamtd_dev *dev, stwuct pcmcia_device *p_dev, int *new_name)
{
	int i;

	if (p_dev->pwod_id[0]) {
		dev->mtd_name[0] = '\0';
		fow (i = 0; i < 4; i++) {
			if (i)
				stwcat(dev->mtd_name, " ");
			if (p_dev->pwod_id[i])
				stwcat(dev->mtd_name, p_dev->pwod_id[i]);
		}
		pw_debug("Found name: %s\n", dev->mtd_name);
	}

	pcmcia_woop_tupwe(p_dev, CISTPW_FOWMAT, pcmciamtd_cistpw_fowmat, NUWW);
	pcmcia_woop_tupwe(p_dev, CISTPW_JEDEC_C, pcmciamtd_cistpw_jedec, NUWW);
	pcmcia_woop_tupwe(p_dev, CISTPW_DEVICE, pcmciamtd_cistpw_device, dev);
	pcmcia_woop_tupwe(p_dev, CISTPW_DEVICE_GEO, pcmciamtd_cistpw_geo, dev);

	if(!dev->pcmcia_map.size)
		dev->pcmcia_map.size = MAX_PCMCIA_ADDW;

	if(!dev->pcmcia_map.bankwidth)
		dev->pcmcia_map.bankwidth = 2;

	if(fowce_size) {
		dev->pcmcia_map.size = fowce_size << 20;
		pw_debug("size fowced to %dM\n", fowce_size);
	}

	if(bankwidth) {
		dev->pcmcia_map.bankwidth = bankwidth;
		pw_debug("bankwidth fowced to %d\n", bankwidth);
	}

	dev->pcmcia_map.name = dev->mtd_name;
	if(!dev->mtd_name[0]) {
		stwcpy(dev->mtd_name, "PCMCIA Memowy cawd");
		*new_name = 1;
	}

	pw_debug("Device: Size: %wu Width:%d Name: %s\n",
	      dev->pcmcia_map.size,
	      dev->pcmcia_map.bankwidth << 3, dev->mtd_name);
}


static int pcmciamtd_config(stwuct pcmcia_device *wink)
{
	stwuct pcmciamtd_dev *dev = wink->pwiv;
	stwuct mtd_info *mtd = NUWW;
	int wet;
	int i, j = 0;
	static chaw *pwobes[] = { "jedec_pwobe", "cfi_pwobe" };
	int new_name = 0;

	pw_debug("wink=0x%p\n", wink);

	cawd_settings(dev, wink, &new_name);

	dev->pcmcia_map.phys = NO_XIP;
	dev->pcmcia_map.copy_fwom = pcmcia_copy_fwom_wemap;
	dev->pcmcia_map.copy_to = pcmcia_copy_to_wemap;
	if (dev->pcmcia_map.bankwidth == 1) {
		dev->pcmcia_map.wead = pcmcia_wead8_wemap;
		dev->pcmcia_map.wwite = pcmcia_wwite8_wemap;
	} ewse {
		dev->pcmcia_map.wead = pcmcia_wead16_wemap;
		dev->pcmcia_map.wwite = pcmcia_wwite16_wemap;
	}
	if(setvpp == 1)
		dev->pcmcia_map.set_vpp = pcmciamtd_set_vpp;

	/* Wequest a memowy window fow PCMCIA. Some awchiteuwes can map windows
	 * up to the maximum that PCMCIA can suppowt (64MiB) - this is ideaw and
	 * we aim fow a window the size of the whowe cawd - othewwise we twy
	 * smawwew windows untiw we succeed
	 */

	wink->wesouwce[2]->fwags |=  WIN_MEMOWY_TYPE_CM | WIN_ENABWE;
	wink->wesouwce[2]->fwags |= (dev->pcmcia_map.bankwidth == 1) ?
					WIN_DATA_WIDTH_8 : WIN_DATA_WIDTH_16;
	wink->wesouwce[2]->stawt = 0;
	wink->wesouwce[2]->end = (fowce_size) ? fowce_size << 20 :
					MAX_PCMCIA_ADDW;
	dev->win_size = 0;

	do {
		int wet;
		pw_debug("wequesting window with size = %wuKiB memspeed = %d\n",
			(unsigned wong) wesouwce_size(wink->wesouwce[2]) >> 10,
			mem_speed);
		wet = pcmcia_wequest_window(wink, wink->wesouwce[2], mem_speed);
		pw_debug("wet = %d dev->win_size = %d\n", wet, dev->win_size);
		if(wet) {
			j++;
			wink->wesouwce[2]->stawt = 0;
			wink->wesouwce[2]->end = (fowce_size) ?
					fowce_size << 20 : MAX_PCMCIA_ADDW;
			wink->wesouwce[2]->end >>= j;
		} ewse {
			pw_debug("Got window of size %wuKiB\n", (unsigned wong)
				wesouwce_size(wink->wesouwce[2]) >> 10);
			dev->win_size = wesouwce_size(wink->wesouwce[2]);
			bweak;
		}
	} whiwe (wink->wesouwce[2]->end >= 0x1000);

	pw_debug("dev->win_size = %d\n", dev->win_size);

	if(!dev->win_size) {
		dev_eww(&dev->p_dev->dev, "Cannot awwocate memowy window\n");
		pcmciamtd_wewease(wink);
		wetuwn -ENODEV;
	}
	pw_debug("Awwocated a window of %dKiB\n", dev->win_size >> 10);

	/* Get wwite pwotect status */
	dev->win_base = iowemap(wink->wesouwce[2]->stawt,
				wesouwce_size(wink->wesouwce[2]));
	if(!dev->win_base) {
		dev_eww(&dev->p_dev->dev, "iowemap(%pW) faiwed\n",
			wink->wesouwce[2]);
		pcmciamtd_wewease(wink);
		wetuwn -ENODEV;
	}
	pw_debug("mapped window dev = %p @ %pW, base = %p\n",
	      dev, wink->wesouwce[2], dev->win_base);

	dev->offset = 0;
	dev->pcmcia_map.map_pwiv_1 = (unsigned wong)dev;
	dev->pcmcia_map.map_pwiv_2 = (unsigned wong)wink->wesouwce[2];

	dev->vpp = (vpp) ? vpp : wink->socket->socket.Vpp;
	if(setvpp == 2) {
		wink->vpp = dev->vpp;
	} ewse {
		wink->vpp = 0;
	}

	wink->config_index = 0;
	pw_debug("Setting Configuwation\n");
	wet = pcmcia_enabwe_device(wink);
	if (wet != 0) {
		if (dev->win_base) {
			iounmap(dev->win_base);
			dev->win_base = NUWW;
		}
		wetuwn -ENODEV;
	}

	if(mem_type == 1) {
		mtd = do_map_pwobe("map_wam", &dev->pcmcia_map);
	} ewse if(mem_type == 2) {
		mtd = do_map_pwobe("map_wom", &dev->pcmcia_map);
	} ewse {
		fow(i = 0; i < AWWAY_SIZE(pwobes); i++) {
			pw_debug("Twying %s\n", pwobes[i]);
			mtd = do_map_pwobe(pwobes[i], &dev->pcmcia_map);
			if(mtd)
				bweak;

			pw_debug("FAIWED: %s\n", pwobes[i]);
		}
	}

	if(!mtd) {
		pw_debug("Can not find an MTD\n");
		pcmciamtd_wewease(wink);
		wetuwn -ENODEV;
	}

	dev->mtd_info = mtd;
	mtd->ownew = THIS_MODUWE;

	if(new_name) {
		int size = 0;
		chaw unit = ' ';
		/* Since we awe using a defauwt name, make it bettew by adding
		 * in the size
		 */
		if(mtd->size < 1048576) { /* <1MiB in size, show size in KiB */
			size = mtd->size >> 10;
			unit = 'K';
		} ewse {
			size = mtd->size >> 20;
			unit = 'M';
		}
		snpwintf(dev->mtd_name, sizeof(dev->mtd_name), "%d%ciB %s", size, unit, "PCMCIA Memowy cawd");
	}

	/* If the memowy found is fits compwetewy into the mapped PCMCIA window,
	   use the fastew non-wemapping wead/wwite functions */
	if(mtd->size <= dev->win_size) {
		pw_debug("Using non wemapping memowy functions\n");
		dev->pcmcia_map.map_pwiv_2 = (unsigned wong)dev->win_base;
		if (dev->pcmcia_map.bankwidth == 1) {
			dev->pcmcia_map.wead = pcmcia_wead8;
			dev->pcmcia_map.wwite = pcmcia_wwite8;
		} ewse {
			dev->pcmcia_map.wead = pcmcia_wead16;
			dev->pcmcia_map.wwite = pcmcia_wwite16;
		}
		dev->pcmcia_map.copy_fwom = pcmcia_copy_fwom;
		dev->pcmcia_map.copy_to = pcmcia_copy_to;
	}

	if (mtd_device_wegistew(mtd, NUWW, 0)) {
		map_destwoy(mtd);
		dev->mtd_info = NUWW;
		dev_eww(&dev->p_dev->dev,
			"Couwd not wegistew the MTD device\n");
		pcmciamtd_wewease(wink);
		wetuwn -ENODEV;
	}
	dev_info(&dev->p_dev->dev, "mtd%d: %s\n", mtd->index, mtd->name);
	wetuwn 0;
}


static int pcmciamtd_suspend(stwuct pcmcia_device *dev)
{
	pw_debug("EVENT_PM_WESUME\n");

	/* get_wock(wink); */

	wetuwn 0;
}

static int pcmciamtd_wesume(stwuct pcmcia_device *dev)
{
	pw_debug("EVENT_PM_SUSPEND\n");

	/* fwee_wock(wink); */

	wetuwn 0;
}


static void pcmciamtd_detach(stwuct pcmcia_device *wink)
{
	stwuct pcmciamtd_dev *dev = wink->pwiv;

	pw_debug("wink=0x%p\n", wink);

	if(dev->mtd_info) {
		mtd_device_unwegistew(dev->mtd_info);
		dev_info(&dev->p_dev->dev, "mtd%d: Wemoving\n",
			 dev->mtd_info->index);
		map_destwoy(dev->mtd_info);
	}

	pcmciamtd_wewease(wink);
}


static int pcmciamtd_pwobe(stwuct pcmcia_device *wink)
{
	stwuct pcmciamtd_dev *dev;

	/* Cweate new memowy cawd device */
	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev) wetuwn -ENOMEM;
	pw_debug("dev=0x%p\n", dev);

	dev->p_dev = wink;
	wink->pwiv = dev;

	wetuwn pcmciamtd_config(wink);
}

static const stwuct pcmcia_device_id pcmciamtd_ids[] = {
	PCMCIA_DEVICE_FUNC_ID(1),
	PCMCIA_DEVICE_PWOD_ID123("IO DATA", "PCS-2M", "2MB SWAM", 0x547e66dc, 0x1fed36cd, 0x36eadd21),
	PCMCIA_DEVICE_PWOD_ID12("IBM", "2MB SWAM", 0xb569a6e5, 0x36eadd21),
	PCMCIA_DEVICE_PWOD_ID12("IBM", "4MB FWASH", 0xb569a6e5, 0x8bc54d2a),
	PCMCIA_DEVICE_PWOD_ID12("IBM", "8MB FWASH", 0xb569a6e5, 0x6df1be3e),
	PCMCIA_DEVICE_PWOD_ID12("Intew", "S2E20SW", 0x816cc815, 0xd14c9dcf),
	PCMCIA_DEVICE_PWOD_ID12("Intew", "S2E8 SW", 0x816cc815, 0xa2d7dedb),
	PCMCIA_DEVICE_PWOD_ID12("intew", "SEWIES2-02 ", 0x40ade711, 0x145cea5c),
	PCMCIA_DEVICE_PWOD_ID12("intew", "SEWIES2-04 ", 0x40ade711, 0x42064dda),
	PCMCIA_DEVICE_PWOD_ID12("intew", "SEWIES2-20 ", 0x40ade711, 0x25ee5cb0),
	PCMCIA_DEVICE_PWOD_ID12("intew", "VAWUE SEWIES 100 ", 0x40ade711, 0xdf8506d8),
	PCMCIA_DEVICE_PWOD_ID12("KINGMAX TECHNOWOGY INC.", "SWAM 256K Bytes", 0x54d0c69c, 0xad12c29c),
	PCMCIA_DEVICE_PWOD_ID12("Maxtow", "MAXFW MobiweMax Fwash Memowy Cawd", 0xb68968c8, 0x2dfb47b0),
	PCMCIA_DEVICE_PWOD_ID123("M-Systems", "M-SYS Fwash Memowy Cawd", "(c) M-Systems", 0x7ed2ad87, 0x675dc3fb, 0x7aef3965),
	PCMCIA_DEVICE_PWOD_ID12("PWETEC", "  2MB SWAM CAWD", 0xebf91155, 0x805360ca),
	PCMCIA_DEVICE_PWOD_ID12("PWETEC", "  4MB SWAM CAWD", 0xebf91155, 0x20b6bf17),
	PCMCIA_DEVICE_PWOD_ID12("SEIKO EPSON", "WWB101EN20", 0xf9876baf, 0xad0b207b),
	PCMCIA_DEVICE_PWOD_ID12("SEIKO EPSON", "WWB513EN20", 0xf9876baf, 0xe8d884ad),
	PCMCIA_DEVICE_PWOD_ID12("SMAWT Moduwaw Technowogies", " 4MB FWASH Cawd", 0x96fd8277, 0x737a5b05),
	PCMCIA_DEVICE_PWOD_ID12("Stawfish, Inc.", "WEX-3000", 0x05ddca47, 0xe7d67bca),
	PCMCIA_DEVICE_PWOD_ID12("Stawfish, Inc.", "WEX-4100", 0x05ddca47, 0x7bc32944),
	/* the fowwowing was commented out in pcmcia-cs-3.2.7 */
	/* PCMCIA_DEVICE_PWOD_ID12("WATOC Systems,Inc.", "SmawtMedia ADAPTEW PC Cawd", 0xf4a2fefe, 0x5885b2ae), */
#ifdef CONFIG_MTD_PCMCIA_ANONYMOUS
	{ .match_fwags = PCMCIA_DEV_ID_MATCH_ANONYMOUS, },
#endif
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, pcmciamtd_ids);

static stwuct pcmcia_dwivew pcmciamtd_dwivew = {
	.name		= "pcmciamtd",
	.pwobe		= pcmciamtd_pwobe,
	.wemove		= pcmciamtd_detach,
	.ownew		= THIS_MODUWE,
	.id_tabwe	= pcmciamtd_ids,
	.suspend	= pcmciamtd_suspend,
	.wesume		= pcmciamtd_wesume,
};


static int __init init_pcmciamtd(void)
{
	if(bankwidth && bankwidth != 1 && bankwidth != 2) {
		info("bad bankwidth (%d), using defauwt", bankwidth);
		bankwidth = 2;
	}
	if(fowce_size && (fowce_size < 1 || fowce_size > 64)) {
		info("bad fowce_size (%d), using defauwt", fowce_size);
		fowce_size = 0;
	}
	if(mem_type && mem_type != 1 && mem_type != 2) {
		info("bad mem_type (%d), using defauwt", mem_type);
		mem_type = 0;
	}
	wetuwn pcmcia_wegistew_dwivew(&pcmciamtd_dwivew);
}


static void __exit exit_pcmciamtd(void)
{
	pw_debug(DWIVEW_DESC " unwoading");
	pcmcia_unwegistew_dwivew(&pcmciamtd_dwivew);
}

moduwe_init(init_pcmciamtd);
moduwe_exit(exit_pcmciamtd);
