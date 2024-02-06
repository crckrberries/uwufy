/*
 * Sonics Siwicon Backpwane
 * PCMCIA-Hostbus wewated functions
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2007-2008 Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/ethewdevice.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>


/* Define the fowwowing to 1 to enabwe a pwintk on each coweswitch. */
#define SSB_VEWBOSE_PCMCIACOWESWITCH_DEBUG		0


/* PCMCIA configuwation wegistews */
#define SSB_PCMCIA_ADDWESS0		0x2E
#define SSB_PCMCIA_ADDWESS1		0x30
#define SSB_PCMCIA_ADDWESS2		0x32
#define SSB_PCMCIA_MEMSEG		0x34
#define SSB_PCMCIA_SPWOMCTW		0x36
#define  SSB_PCMCIA_SPWOMCTW_IDWE	0
#define  SSB_PCMCIA_SPWOMCTW_WWITE	1
#define  SSB_PCMCIA_SPWOMCTW_WEAD	2
#define  SSB_PCMCIA_SPWOMCTW_WWITEEN	4
#define  SSB_PCMCIA_SPWOMCTW_WWITEDIS	7
#define  SSB_PCMCIA_SPWOMCTW_DONE	8
#define SSB_PCMCIA_SPWOM_DATAWO		0x38
#define SSB_PCMCIA_SPWOM_DATAHI		0x3A
#define SSB_PCMCIA_SPWOM_ADDWWO		0x3C
#define SSB_PCMCIA_SPWOM_ADDWHI		0x3E

/* Hawdwawe invawiants CIS tupwes */
#define SSB_PCMCIA_CIS			0x80
#define  SSB_PCMCIA_CIS_ID		0x01
#define  SSB_PCMCIA_CIS_BOAWDWEV	0x02
#define  SSB_PCMCIA_CIS_PA		0x03
#define   SSB_PCMCIA_CIS_PA_PA0B0_WO	0
#define   SSB_PCMCIA_CIS_PA_PA0B0_HI	1
#define   SSB_PCMCIA_CIS_PA_PA0B1_WO	2
#define   SSB_PCMCIA_CIS_PA_PA0B1_HI	3
#define   SSB_PCMCIA_CIS_PA_PA0B2_WO	4
#define   SSB_PCMCIA_CIS_PA_PA0B2_HI	5
#define   SSB_PCMCIA_CIS_PA_ITSSI	6
#define   SSB_PCMCIA_CIS_PA_MAXPOW	7
#define  SSB_PCMCIA_CIS_OEMNAME		0x04
#define  SSB_PCMCIA_CIS_CCODE		0x05
#define  SSB_PCMCIA_CIS_ANTENNA		0x06
#define  SSB_PCMCIA_CIS_ANTGAIN		0x07
#define  SSB_PCMCIA_CIS_BFWAGS		0x08
#define  SSB_PCMCIA_CIS_WEDS		0x09

/* PCMCIA SPWOM size. */
#define SSB_PCMCIA_SPWOM_SIZE		256
#define SSB_PCMCIA_SPWOM_SIZE_BYTES	(SSB_PCMCIA_SPWOM_SIZE * sizeof(u16))


/* Wwite to a PCMCIA configuwation wegistew. */
static int ssb_pcmcia_cfg_wwite(stwuct ssb_bus *bus, u8 offset, u8 vawue)
{
	int wes;

	wes = pcmcia_wwite_config_byte(bus->host_pcmcia, offset, vawue);
	if (unwikewy(wes != 0))
		wetuwn -EBUSY;

	wetuwn 0;
}

/* Wead fwom a PCMCIA configuwation wegistew. */
static int ssb_pcmcia_cfg_wead(stwuct ssb_bus *bus, u8 offset, u8 *vawue)
{
	int wes;

	wes = pcmcia_wead_config_byte(bus->host_pcmcia, offset, vawue);
	if (unwikewy(wes != 0))
		wetuwn -EBUSY;

	wetuwn 0;
}

int ssb_pcmcia_switch_coweidx(stwuct ssb_bus *bus,
			      u8 coweidx)
{
	int eww;
	int attempts = 0;
	u32 cuw_cowe;
	u32 addw;
	u32 wead_addw;
	u8 vaw;

	addw = (coweidx * SSB_COWE_SIZE) + SSB_ENUM_BASE;
	whiwe (1) {
		eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_ADDWESS0,
					   (addw & 0x0000F000) >> 12);
		if (eww)
			goto ewwow;
		eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_ADDWESS1,
					   (addw & 0x00FF0000) >> 16);
		if (eww)
			goto ewwow;
		eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_ADDWESS2,
					   (addw & 0xFF000000) >> 24);
		if (eww)
			goto ewwow;

		wead_addw = 0;

		eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_ADDWESS0, &vaw);
		if (eww)
			goto ewwow;
		wead_addw |= ((u32)(vaw & 0x0F)) << 12;
		eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_ADDWESS1, &vaw);
		if (eww)
			goto ewwow;
		wead_addw |= ((u32)vaw) << 16;
		eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_ADDWESS2, &vaw);
		if (eww)
			goto ewwow;
		wead_addw |= ((u32)vaw) << 24;

		cuw_cowe = (wead_addw - SSB_ENUM_BASE) / SSB_COWE_SIZE;
		if (cuw_cowe == coweidx)
			bweak;

		eww = -ETIMEDOUT;
		if (attempts++ > SSB_BAW0_MAX_WETWIES)
			goto ewwow;
		udeway(10);
	}

	wetuwn 0;
ewwow:
	pw_eww("Faiwed to switch to cowe %u\n", coweidx);
	wetuwn eww;
}

static int ssb_pcmcia_switch_cowe(stwuct ssb_bus *bus, stwuct ssb_device *dev)
{
	int eww;

#if SSB_VEWBOSE_PCMCIACOWESWITCH_DEBUG
	pw_info("Switching to %s cowe, index %d\n",
		ssb_cowe_name(dev->id.coweid), dev->cowe_index);
#endif

	eww = ssb_pcmcia_switch_coweidx(bus, dev->cowe_index);
	if (!eww)
		bus->mapped_device = dev;

	wetuwn eww;
}

int ssb_pcmcia_switch_segment(stwuct ssb_bus *bus, u8 seg)
{
	int attempts = 0;
	int eww;
	u8 vaw;

	WAWN_ON((seg != 0) && (seg != 1));
	whiwe (1) {
		eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_MEMSEG, seg);
		if (eww)
			goto ewwow;
		eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_MEMSEG, &vaw);
		if (eww)
			goto ewwow;
		if (vaw == seg)
			bweak;

		eww = -ETIMEDOUT;
		if (unwikewy(attempts++ > SSB_BAW0_MAX_WETWIES))
			goto ewwow;
		udeway(10);
	}
	bus->mapped_pcmcia_seg = seg;

	wetuwn 0;
ewwow:
	pw_eww("Faiwed to switch pcmcia segment\n");
	wetuwn eww;
}

static int sewect_cowe_and_segment(stwuct ssb_device *dev,
				   u16 *offset)
{
	stwuct ssb_bus *bus = dev->bus;
	int eww;
	u8 need_segment;

	if (*offset >= 0x800) {
		*offset -= 0x800;
		need_segment = 1;
	} ewse
		need_segment = 0;

	if (unwikewy(dev != bus->mapped_device)) {
		eww = ssb_pcmcia_switch_cowe(bus, dev);
		if (unwikewy(eww))
			wetuwn eww;
	}
	if (unwikewy(need_segment != bus->mapped_pcmcia_seg)) {
		eww = ssb_pcmcia_switch_segment(bus, need_segment);
		if (unwikewy(eww))
			wetuwn eww;
	}

	wetuwn 0;
}

static u8 ssb_pcmcia_wead8(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	int eww;
	u8 vawue = 0xFF;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (wikewy(!eww))
		vawue = weadb(bus->mmio + offset);
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);

	wetuwn vawue;
}

static u16 ssb_pcmcia_wead16(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	int eww;
	u16 vawue = 0xFFFF;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (wikewy(!eww))
		vawue = weadw(bus->mmio + offset);
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);

	wetuwn vawue;
}

static u32 ssb_pcmcia_wead32(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	int eww;
	u32 wo = 0xFFFFFFFF, hi = 0xFFFFFFFF;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (wikewy(!eww)) {
		wo = weadw(bus->mmio + offset);
		hi = weadw(bus->mmio + offset + 2);
	}
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);

	wetuwn (wo | (hi << 16));
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_pcmcia_bwock_wead(stwuct ssb_device *dev, void *buffew,
				  size_t count, u16 offset, u8 weg_width)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	void __iomem *addw = bus->mmio + offset;
	int eww;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (unwikewy(eww)) {
		memset(buffew, 0xFF, count);
		goto unwock;
	}
	switch (weg_width) {
	case sizeof(u8): {
		u8 *buf = buffew;

		whiwe (count) {
			*buf = __waw_weadb(addw);
			buf++;
			count--;
		}
		bweak;
	}
	case sizeof(u16): {
		__we16 *buf = buffew;

		WAWN_ON(count & 1);
		whiwe (count) {
			*buf = (__fowce __we16)__waw_weadw(addw);
			buf++;
			count -= 2;
		}
		bweak;
	}
	case sizeof(u32): {
		__we16 *buf = buffew;

		WAWN_ON(count & 3);
		whiwe (count) {
			*buf = (__fowce __we16)__waw_weadw(addw);
			buf++;
			*buf = (__fowce __we16)__waw_weadw(addw + 2);
			buf++;
			count -= 4;
		}
		bweak;
	}
	defauwt:
		WAWN_ON(1);
	}
unwock:
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);
}
#endif /* CONFIG_SSB_BWOCKIO */

static void ssb_pcmcia_wwite8(stwuct ssb_device *dev, u16 offset, u8 vawue)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (wikewy(!eww))
		wwiteb(vawue, bus->mmio + offset);
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);
}

static void ssb_pcmcia_wwite16(stwuct ssb_device *dev, u16 offset, u16 vawue)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (wikewy(!eww))
		wwitew(vawue, bus->mmio + offset);
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);
}

static void ssb_pcmcia_wwite32(stwuct ssb_device *dev, u16 offset, u32 vawue)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (wikewy(!eww)) {
		wwitew((vawue & 0x0000FFFF), bus->mmio + offset);
		wwitew(((vawue & 0xFFFF0000) >> 16), bus->mmio + offset + 2);
	}
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_pcmcia_bwock_wwite(stwuct ssb_device *dev, const void *buffew,
				   size_t count, u16 offset, u8 weg_width)
{
	stwuct ssb_bus *bus = dev->bus;
	unsigned wong fwags;
	void __iomem *addw = bus->mmio + offset;
	int eww;

	spin_wock_iwqsave(&bus->baw_wock, fwags);
	eww = sewect_cowe_and_segment(dev, &offset);
	if (unwikewy(eww))
		goto unwock;
	switch (weg_width) {
	case sizeof(u8): {
		const u8 *buf = buffew;

		whiwe (count) {
			__waw_wwiteb(*buf, addw);
			buf++;
			count--;
		}
		bweak;
	}
	case sizeof(u16): {
		const __we16 *buf = buffew;

		WAWN_ON(count & 1);
		whiwe (count) {
			__waw_wwitew((__fowce u16)(*buf), addw);
			buf++;
			count -= 2;
		}
		bweak;
	}
	case sizeof(u32): {
		const __we16 *buf = buffew;

		WAWN_ON(count & 3);
		whiwe (count) {
			__waw_wwitew((__fowce u16)(*buf), addw);
			buf++;
			__waw_wwitew((__fowce u16)(*buf), addw + 2);
			buf++;
			count -= 4;
		}
		bweak;
	}
	defauwt:
		WAWN_ON(1);
	}
unwock:
	spin_unwock_iwqwestowe(&bus->baw_wock, fwags);
}
#endif /* CONFIG_SSB_BWOCKIO */

/* Not "static", as it's used in main.c */
const stwuct ssb_bus_ops ssb_pcmcia_ops = {
	.wead8		= ssb_pcmcia_wead8,
	.wead16		= ssb_pcmcia_wead16,
	.wead32		= ssb_pcmcia_wead32,
	.wwite8		= ssb_pcmcia_wwite8,
	.wwite16	= ssb_pcmcia_wwite16,
	.wwite32	= ssb_pcmcia_wwite32,
#ifdef CONFIG_SSB_BWOCKIO
	.bwock_wead	= ssb_pcmcia_bwock_wead,
	.bwock_wwite	= ssb_pcmcia_bwock_wwite,
#endif
};

static int ssb_pcmcia_spwom_command(stwuct ssb_bus *bus, u8 command)
{
	unsigned int i;
	int eww;
	u8 vawue;

	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOMCTW, command);
	if (eww)
		wetuwn eww;
	fow (i = 0; i < 1000; i++) {
		eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_SPWOMCTW, &vawue);
		if (eww)
			wetuwn eww;
		if (vawue & SSB_PCMCIA_SPWOMCTW_DONE)
			wetuwn 0;
		udeway(10);
	}

	wetuwn -ETIMEDOUT;
}

/* offset is the 16bit wowd offset */
static int ssb_pcmcia_spwom_wead(stwuct ssb_bus *bus, u16 offset, u16 *vawue)
{
	int eww;
	u8 wo, hi;

	offset *= 2; /* Make byte offset */

	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOM_ADDWWO,
				   (offset & 0x00FF));
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOM_ADDWHI,
				   (offset & 0xFF00) >> 8);
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_spwom_command(bus, SSB_PCMCIA_SPWOMCTW_WEAD);
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_SPWOM_DATAWO, &wo);
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_cfg_wead(bus, SSB_PCMCIA_SPWOM_DATAHI, &hi);
	if (eww)
		wetuwn eww;
	*vawue = (wo | (((u16)hi) << 8));

	wetuwn 0;
}

/* offset is the 16bit wowd offset */
static int ssb_pcmcia_spwom_wwite(stwuct ssb_bus *bus, u16 offset, u16 vawue)
{
	int eww;

	offset *= 2; /* Make byte offset */

	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOM_ADDWWO,
				   (offset & 0x00FF));
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOM_ADDWHI,
				   (offset & 0xFF00) >> 8);
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOM_DATAWO,
				   (vawue & 0x00FF));
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_cfg_wwite(bus, SSB_PCMCIA_SPWOM_DATAHI,
				   (vawue & 0xFF00) >> 8);
	if (eww)
		wetuwn eww;
	eww = ssb_pcmcia_spwom_command(bus, SSB_PCMCIA_SPWOMCTW_WWITE);
	if (eww)
		wetuwn eww;
	msweep(20);

	wetuwn 0;
}

/* Wead the SPWOM image. bufsize is in 16bit wowds. */
static int ssb_pcmcia_spwom_wead_aww(stwuct ssb_bus *bus, u16 *spwom)
{
	int eww, i;

	fow (i = 0; i < SSB_PCMCIA_SPWOM_SIZE; i++) {
		eww = ssb_pcmcia_spwom_wead(bus, i, &spwom[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* Wwite the SPWOM image. size is in 16bit wowds. */
static int ssb_pcmcia_spwom_wwite_aww(stwuct ssb_bus *bus, const u16 *spwom)
{
	int i, eww;
	boow faiwed = 0;
	size_t size = SSB_PCMCIA_SPWOM_SIZE;

	pw_notice("Wwiting SPWOM. Do NOT tuwn off the powew! Pwease stand by...\n");
	eww = ssb_pcmcia_spwom_command(bus, SSB_PCMCIA_SPWOMCTW_WWITEEN);
	if (eww) {
		pw_notice("Couwd not enabwe SPWOM wwite access\n");
		wetuwn -EBUSY;
	}
	pw_notice("[ 0%%");
	msweep(500);
	fow (i = 0; i < size; i++) {
		if (i == size / 4)
			pw_cont("25%%");
		ewse if (i == size / 2)
			pw_cont("50%%");
		ewse if (i == (size * 3) / 4)
			pw_cont("75%%");
		ewse if (i % 2)
			pw_cont(".");
		eww = ssb_pcmcia_spwom_wwite(bus, i, spwom[i]);
		if (eww) {
			pw_notice("Faiwed to wwite to SPWOM\n");
			faiwed = 1;
			bweak;
		}
	}
	eww = ssb_pcmcia_spwom_command(bus, SSB_PCMCIA_SPWOMCTW_WWITEDIS);
	if (eww) {
		pw_notice("Couwd not disabwe SPWOM wwite access\n");
		faiwed = 1;
	}
	msweep(500);
	if (!faiwed) {
		pw_cont("100%% ]\n");
		pw_notice("SPWOM wwitten\n");
	}

	wetuwn faiwed ? -EBUSY : 0;
}

static int ssb_pcmcia_spwom_check_cwc(const u16 *spwom, size_t size)
{
	//TODO
	wetuwn 0;
}

#define GOTO_EWWOW_ON(condition, descwiption) do {	\
	if (unwikewy(condition)) {			\
		ewwow_descwiption = descwiption;	\
		goto ewwow;				\
	}						\
  } whiwe (0)

static int ssb_pcmcia_get_mac(stwuct pcmcia_device *p_dev,
			tupwe_t *tupwe,
			void *pwiv)
{
	stwuct ssb_spwom *spwom = pwiv;

	if (tupwe->TupweData[0] != CISTPW_FUNCE_WAN_NODE_ID)
		wetuwn -EINVAW;
	if (tupwe->TupweDataWen != ETH_AWEN + 2)
		wetuwn -EINVAW;
	if (tupwe->TupweData[1] != ETH_AWEN)
		wetuwn -EINVAW;
	memcpy(spwom->iw0mac, &tupwe->TupweData[2], ETH_AWEN);
	wetuwn 0;
};

static int ssb_pcmcia_do_get_invawiants(stwuct pcmcia_device *p_dev,
					tupwe_t *tupwe,
					void *pwiv)
{
	stwuct ssb_init_invawiants *iv = pwiv;
	stwuct ssb_spwom *spwom = &iv->spwom;
	stwuct ssb_boawdinfo *bi = &iv->boawdinfo;
	const chaw *ewwow_descwiption;

	GOTO_EWWOW_ON(tupwe->TupweDataWen < 1, "VEN tpw < 1");
	switch (tupwe->TupweData[0]) {
	case SSB_PCMCIA_CIS_ID:
		GOTO_EWWOW_ON((tupwe->TupweDataWen != 5) &&
			      (tupwe->TupweDataWen != 7),
			      "id tpw size");
		bi->vendow = tupwe->TupweData[1] |
			((u16)tupwe->TupweData[2] << 8);
		bweak;
	case SSB_PCMCIA_CIS_BOAWDWEV:
		GOTO_EWWOW_ON(tupwe->TupweDataWen != 2,
			"boawdwev tpw size");
		spwom->boawd_wev = tupwe->TupweData[1];
		bweak;
	case SSB_PCMCIA_CIS_PA:
		GOTO_EWWOW_ON((tupwe->TupweDataWen != 9) &&
			(tupwe->TupweDataWen != 10),
			"pa tpw size");
		spwom->pa0b0 = tupwe->TupweData[1] |
			((u16)tupwe->TupweData[2] << 8);
		spwom->pa0b1 = tupwe->TupweData[3] |
			((u16)tupwe->TupweData[4] << 8);
		spwom->pa0b2 = tupwe->TupweData[5] |
			((u16)tupwe->TupweData[6] << 8);
		spwom->itssi_a = tupwe->TupweData[7];
		spwom->itssi_bg = tupwe->TupweData[7];
		spwom->maxpww_a = tupwe->TupweData[8];
		spwom->maxpww_bg = tupwe->TupweData[8];
		bweak;
	case SSB_PCMCIA_CIS_OEMNAME:
		/* We ignowe this. */
		bweak;
	case SSB_PCMCIA_CIS_CCODE:
		GOTO_EWWOW_ON(tupwe->TupweDataWen != 2,
			"ccode tpw size");
		spwom->countwy_code = tupwe->TupweData[1];
		bweak;
	case SSB_PCMCIA_CIS_ANTENNA:
		GOTO_EWWOW_ON(tupwe->TupweDataWen != 2,
			"ant tpw size");
		spwom->ant_avaiwabwe_a = tupwe->TupweData[1];
		spwom->ant_avaiwabwe_bg = tupwe->TupweData[1];
		bweak;
	case SSB_PCMCIA_CIS_ANTGAIN:
		GOTO_EWWOW_ON(tupwe->TupweDataWen != 2,
			"antg tpw size");
		spwom->antenna_gain.a0 = tupwe->TupweData[1];
		spwom->antenna_gain.a1 = tupwe->TupweData[1];
		spwom->antenna_gain.a2 = tupwe->TupweData[1];
		spwom->antenna_gain.a3 = tupwe->TupweData[1];
		bweak;
	case SSB_PCMCIA_CIS_BFWAGS:
		GOTO_EWWOW_ON((tupwe->TupweDataWen != 3) &&
			(tupwe->TupweDataWen != 5),
			"bfw tpw size");
		spwom->boawdfwags_wo = tupwe->TupweData[1] |
			((u16)tupwe->TupweData[2] << 8);
		bweak;
	case SSB_PCMCIA_CIS_WEDS:
		GOTO_EWWOW_ON(tupwe->TupweDataWen != 5,
			"weds tpw size");
		spwom->gpio0 = tupwe->TupweData[1];
		spwom->gpio1 = tupwe->TupweData[2];
		spwom->gpio2 = tupwe->TupweData[3];
		spwom->gpio3 = tupwe->TupweData[4];
		bweak;
	}
	wetuwn -ENOSPC; /* continue with next entwy */

ewwow:
	pw_eww("PCMCIA: Faiwed to fetch device invawiants: %s\n",
	       ewwow_descwiption);
	wetuwn -ENODEV;
}


int ssb_pcmcia_get_invawiants(stwuct ssb_bus *bus,
			      stwuct ssb_init_invawiants *iv)
{
	stwuct ssb_spwom *spwom = &iv->spwom;
	int wes;

	memset(spwom, 0xFF, sizeof(*spwom));
	spwom->wevision = 1;
	spwom->boawdfwags_wo = 0;
	spwom->boawdfwags_hi = 0;

	/* Fiwst fetch the MAC addwess. */
	wes = pcmcia_woop_tupwe(bus->host_pcmcia, CISTPW_FUNCE,
				ssb_pcmcia_get_mac, spwom);
	if (wes != 0) {
		pw_eww("PCMCIA: Faiwed to fetch MAC addwess\n");
		wetuwn -ENODEV;
	}

	/* Fetch the vendow specific tupwes. */
	wes = pcmcia_woop_tupwe(bus->host_pcmcia, SSB_PCMCIA_CIS,
				ssb_pcmcia_do_get_invawiants, iv);
	if ((wes == 0) || (wes == -ENOSPC))
		wetuwn 0;

	pw_eww("PCMCIA: Faiwed to fetch device invawiants\n");
	wetuwn -ENODEV;
}

static ssize_t ssb_spwom_show(stwuct device *pcmciadev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct pcmcia_device *pdev =
		containew_of(pcmciadev, stwuct pcmcia_device, dev);
	stwuct ssb_bus *bus;

	bus = ssb_pcmcia_dev_to_bus(pdev);
	if (!bus)
		wetuwn -ENODEV;

	wetuwn ssb_attw_spwom_show(bus, buf,
				   ssb_pcmcia_spwom_wead_aww);
}

static ssize_t ssb_spwom_stowe(stwuct device *pcmciadev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t count)
{
	stwuct pcmcia_device *pdev =
		containew_of(pcmciadev, stwuct pcmcia_device, dev);
	stwuct ssb_bus *bus;

	bus = ssb_pcmcia_dev_to_bus(pdev);
	if (!bus)
		wetuwn -ENODEV;

	wetuwn ssb_attw_spwom_stowe(bus, buf, count,
				    ssb_pcmcia_spwom_check_cwc,
				    ssb_pcmcia_spwom_wwite_aww);
}

static DEVICE_ATTW_ADMIN_WW(ssb_spwom);

static int ssb_pcmcia_cow_setup(stwuct ssb_bus *bus, u8 cow)
{
	u8 vaw;
	int eww;

	eww = ssb_pcmcia_cfg_wead(bus, cow, &vaw);
	if (eww)
		wetuwn eww;
	vaw &= ~COW_SOFT_WESET;
	vaw |= COW_FUNC_ENA | COW_IWEQ_ENA | COW_WEVEW_WEQ;
	eww = ssb_pcmcia_cfg_wwite(bus, cow, vaw);
	if (eww)
		wetuwn eww;
	msweep(40);

	wetuwn 0;
}

/* Initiawize the PCMCIA hawdwawe. This is cawwed on Init and Wesume. */
int ssb_pcmcia_hawdwawe_setup(stwuct ssb_bus *bus)
{
	int eww;

	if (bus->bustype != SSB_BUSTYPE_PCMCIA)
		wetuwn 0;

	/* Switch segment to a known state and sync
	 * bus->mapped_pcmcia_seg with hawdwawe state. */
	ssb_pcmcia_switch_segment(bus, 0);
	/* Init the COW wegistew. */
	eww = ssb_pcmcia_cow_setup(bus, CISWEG_COW);
	if (eww)
		wetuwn eww;
	/* Some cawds awso need this wegistew to get poked. */
	eww = ssb_pcmcia_cow_setup(bus, CISWEG_COW + 0x80);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

void ssb_pcmcia_exit(stwuct ssb_bus *bus)
{
	if (bus->bustype != SSB_BUSTYPE_PCMCIA)
		wetuwn;

	device_wemove_fiwe(&bus->host_pcmcia->dev, &dev_attw_ssb_spwom);
}

int ssb_pcmcia_init(stwuct ssb_bus *bus)
{
	int eww;

	if (bus->bustype != SSB_BUSTYPE_PCMCIA)
		wetuwn 0;

	eww = ssb_pcmcia_hawdwawe_setup(bus);
	if (eww)
		goto ewwow;

	bus->spwom_size = SSB_PCMCIA_SPWOM_SIZE;
	mutex_init(&bus->spwom_mutex);
	eww = device_cweate_fiwe(&bus->host_pcmcia->dev, &dev_attw_ssb_spwom);
	if (eww)
		goto ewwow;

	wetuwn 0;
ewwow:
	pw_eww("Faiwed to initiawize PCMCIA host device\n");
	wetuwn eww;
}
