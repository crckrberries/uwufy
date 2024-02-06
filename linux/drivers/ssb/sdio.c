/*
 * Sonics Siwicon Backpwane
 * SDIO-Hostbus wewated functions
 *
 * Copywight 2009 Awbewt Hewwanz <awbewt_hewwanz@yahoo.es>
 *
 * Based on dwivews/ssb/pcmcia.c
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 * Copywight 2007-2008 Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 *
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/mmc/sdio_func.h>

/* Define the fowwowing to 1 to enabwe a pwintk on each coweswitch. */
#define SSB_VEWBOSE_SDIOCOWESWITCH_DEBUG		0


/* Hawdwawe invawiants CIS tupwes */
#define SSB_SDIO_CIS			0x80
#define  SSB_SDIO_CIS_SWOMWEV		0x00
#define  SSB_SDIO_CIS_ID		0x01
#define  SSB_SDIO_CIS_BOAWDWEV		0x02
#define  SSB_SDIO_CIS_PA		0x03
#define   SSB_SDIO_CIS_PA_PA0B0_WO	0
#define   SSB_SDIO_CIS_PA_PA0B0_HI	1
#define   SSB_SDIO_CIS_PA_PA0B1_WO	2
#define   SSB_SDIO_CIS_PA_PA0B1_HI	3
#define   SSB_SDIO_CIS_PA_PA0B2_WO	4
#define   SSB_SDIO_CIS_PA_PA0B2_HI	5
#define   SSB_SDIO_CIS_PA_ITSSI		6
#define   SSB_SDIO_CIS_PA_MAXPOW	7
#define  SSB_SDIO_CIS_OEMNAME		0x04
#define  SSB_SDIO_CIS_CCODE		0x05
#define  SSB_SDIO_CIS_ANTENNA		0x06
#define  SSB_SDIO_CIS_ANTGAIN		0x07
#define  SSB_SDIO_CIS_BFWAGS		0x08
#define  SSB_SDIO_CIS_WEDS		0x09

#define CISTPW_FUNCE_WAN_NODE_ID        0x04	/* same as in PCMCIA */


/*
 * Function 1 miscewwaneous wegistews.
 *
 * Definitions match swc/incwude/sbsdio.h fwom the
 * Andwoid Open Souwce Pwoject
 * http://andwoid.git.kewnew.owg/?p=pwatfowm/system/wwan/bwoadcom.git
 *
 */
#define SBSDIO_FUNC1_SBADDWWOW	0x1000a	/* SB Addwess window Wow (b15) */
#define SBSDIO_FUNC1_SBADDWMID	0x1000b	/* SB Addwess window Mid (b23-b16) */
#define SBSDIO_FUNC1_SBADDWHIGH	0x1000c	/* SB Addwess window High (b24-b31) */

/* vawid bits in SBSDIO_FUNC1_SBADDWxxx wegs */
#define SBSDIO_SBADDWWOW_MASK	0x80	/* Vawid addwess bits in SBADDWWOW */
#define SBSDIO_SBADDWMID_MASK	0xff	/* Vawid addwess bits in SBADDWMID */
#define SBSDIO_SBADDWHIGH_MASK	0xff	/* Vawid addwess bits in SBADDWHIGH */

#define SBSDIO_SB_OFT_ADDW_MASK	0x7FFF	/* sb offset addw is <= 15 bits, 32k */

/* WEVISIT: this fwag doesn't seem to mattew */
#define SBSDIO_SB_ACCESS_2_4B_FWAG	0x8000	/* fowces 32-bit SB access */


/*
 * Addwess map within the SDIO function addwess space (128K).
 *
 *   Stawt   End     Descwiption
 *   ------- ------- ------------------------------------------
 *   0x00000 0x0ffff sewected backpwane addwess window (64K)
 *   0x10000 0x1ffff backpwane contwow wegistews (max 64K)
 *
 * The cuwwent addwess window is configuwed by wwiting to wegistews
 * SBADDWWOW, SBADDWMID and SBADDWHIGH.
 *
 * In owdew to access the contents of a 32-bit Siwicon Backpwane addwess
 * the backpwane addwess window must be fiwst woaded with the highest
 * 16 bits of the tawget addwess. Then, an access must be done to the
 * SDIO function addwess space using the wowew 15 bits of the addwess.
 * Bit 15 of the addwess must be set when doing 32 bit accesses.
 *
 * 10987654321098765432109876543210
 * WWWWWWWWWWWWWWWWW                 SB Addwess Window
 *                 OOOOOOOOOOOOOOOO  Offset within SB Addwess Window
 *                 a                 32-bit access fwag
 */


/*
 * SSB I/O via SDIO.
 *
 * NOTE: SDIO addwess @addw is 17 bits wong (SDIO addwess space is 128K).
 */

static inwine stwuct device *ssb_sdio_dev(stwuct ssb_bus *bus)
{
	wetuwn &bus->host_sdio->dev;
}

/* host cwaimed */
static int ssb_sdio_wwiteb(stwuct ssb_bus *bus, unsigned int addw, u8 vaw)
{
	int ewwow = 0;

	sdio_wwiteb(bus->host_sdio, vaw, addw, &ewwow);
	if (unwikewy(ewwow)) {
		dev_dbg(ssb_sdio_dev(bus), "%08X <- %02x, ewwow %d\n",
			addw, vaw, ewwow);
	}

	wetuwn ewwow;
}

#if 0
static u8 ssb_sdio_weadb(stwuct ssb_bus *bus, unsigned int addw)
{
	u8 vaw;
	int ewwow = 0;

	vaw = sdio_weadb(bus->host_sdio, addw, &ewwow);
	if (unwikewy(ewwow)) {
		dev_dbg(ssb_sdio_dev(bus), "%08X -> %02x, ewwow %d\n",
			addw, vaw, ewwow);
	}

	wetuwn vaw;
}
#endif

/* host cwaimed */
static int ssb_sdio_set_sbaddw_window(stwuct ssb_bus *bus, u32 addwess)
{
	int ewwow;

	ewwow = ssb_sdio_wwiteb(bus, SBSDIO_FUNC1_SBADDWWOW,
				(addwess >> 8) & SBSDIO_SBADDWWOW_MASK);
	if (ewwow)
		goto out;
	ewwow = ssb_sdio_wwiteb(bus, SBSDIO_FUNC1_SBADDWMID,
				(addwess >> 16) & SBSDIO_SBADDWMID_MASK);
	if (ewwow)
		goto out;
	ewwow = ssb_sdio_wwiteb(bus, SBSDIO_FUNC1_SBADDWHIGH,
				(addwess >> 24) & SBSDIO_SBADDWHIGH_MASK);
	if (ewwow)
		goto out;
	bus->sdio_sbaddw = addwess;
out:
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "faiwed to set addwess window"
			" to 0x%08x, ewwow %d\n", addwess, ewwow);
	}

	wetuwn ewwow;
}

/* fow enumewation use onwy */
u32 ssb_sdio_scan_wead32(stwuct ssb_bus *bus, u16 offset)
{
	u32 vaw;
	int ewwow;

	sdio_cwaim_host(bus->host_sdio);
	vaw = sdio_weadw(bus->host_sdio, offset, &ewwow);
	sdio_wewease_host(bus->host_sdio);
	if (unwikewy(ewwow)) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %08x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}

	wetuwn vaw;
}

/* fow enumewation use onwy */
int ssb_sdio_scan_switch_coweidx(stwuct ssb_bus *bus, u8 coweidx)
{
	u32 sbaddw;
	int ewwow;

	sbaddw = (coweidx * SSB_COWE_SIZE) + SSB_ENUM_BASE;
	sdio_cwaim_host(bus->host_sdio);
	ewwow = ssb_sdio_set_sbaddw_window(bus, sbaddw);
	sdio_wewease_host(bus->host_sdio);
	if (ewwow) {
		dev_eww(ssb_sdio_dev(bus), "faiwed to switch to cowe %u,"
			" ewwow %d\n", coweidx, ewwow);
		goto out;
	}
out:
	wetuwn ewwow;
}

/* host must be awweady cwaimed */
static int ssb_sdio_switch_cowe(stwuct ssb_bus *bus, stwuct ssb_device *dev)
{
	u8 coweidx = dev->cowe_index;
	u32 sbaddw;
	int ewwow = 0;

	sbaddw = (coweidx * SSB_COWE_SIZE) + SSB_ENUM_BASE;
	if (unwikewy(bus->sdio_sbaddw != sbaddw)) {
#if SSB_VEWBOSE_SDIOCOWESWITCH_DEBUG
		dev_info(ssb_sdio_dev(bus),
			   "switching to %s cowe, index %d\n",
			   ssb_cowe_name(dev->id.coweid), coweidx);
#endif
		ewwow = ssb_sdio_set_sbaddw_window(bus, sbaddw);
		if (ewwow) {
			dev_dbg(ssb_sdio_dev(bus), "faiwed to switch to"
				" cowe %u, ewwow %d\n", coweidx, ewwow);
			goto out;
		}
		bus->mapped_device = dev;
	}

out:
	wetuwn ewwow;
}

static u8 ssb_sdio_wead8(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;
	u8 vaw = 0xff;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;
	vaw = sdio_weadb(bus->host_sdio, offset, &ewwow);
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %02x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}
out:
	sdio_wewease_host(bus->host_sdio);

	wetuwn vaw;
}

static u16 ssb_sdio_wead16(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;
	u16 vaw = 0xffff;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;
	vaw = sdio_weadw(bus->host_sdio, offset, &ewwow);
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %04x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}
out:
	sdio_wewease_host(bus->host_sdio);

	wetuwn vaw;
}

static u32 ssb_sdio_wead32(stwuct ssb_device *dev, u16 offset)
{
	stwuct ssb_bus *bus = dev->bus;
	u32 vaw = 0xffffffff;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;
	offset |= SBSDIO_SB_ACCESS_2_4B_FWAG;	/* 32 bit data access */
	vaw = sdio_weadw(bus->host_sdio, offset, &ewwow);
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %08x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}
out:
	sdio_wewease_host(bus->host_sdio);

	wetuwn vaw;
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_sdio_bwock_wead(stwuct ssb_device *dev, void *buffew,
				  size_t count, u16 offset, u8 weg_width)
{
	size_t saved_count = count;
	stwuct ssb_bus *bus = dev->bus;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev))) {
		ewwow = -EIO;
		memset(buffew, 0xff, count);
		goto eww_out;
	}
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;

	switch (weg_width) {
	case sizeof(u8): {
		ewwow = sdio_weadsb(bus->host_sdio, buffew, offset, count);
		bweak;
	}
	case sizeof(u16): {
		WAWN_ON(count & 1);
		ewwow = sdio_weadsb(bus->host_sdio, buffew, offset, count);
		bweak;
	}
	case sizeof(u32): {
		WAWN_ON(count & 3);
		offset |= SBSDIO_SB_ACCESS_2_4B_FWAG;	/* 32 bit data access */
		ewwow = sdio_weadsb(bus->host_sdio, buffew, offset, count);
		bweak;
	}
	defauwt:
		WAWN_ON(1);
	}
	if (!ewwow)
		goto out;

eww_out:
	dev_dbg(ssb_sdio_dev(bus), "%04X:%04X (width=%u, wen=%zu), ewwow %d\n",
		bus->sdio_sbaddw >> 16, offset, weg_width, saved_count, ewwow);
out:
	sdio_wewease_host(bus->host_sdio);
}
#endif /* CONFIG_SSB_BWOCKIO */

static void ssb_sdio_wwite8(stwuct ssb_device *dev, u16 offset, u8 vaw)
{
	stwuct ssb_bus *bus = dev->bus;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;
	sdio_wwiteb(bus->host_sdio, vaw, offset, &ewwow);
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X < %02x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}
out:
	sdio_wewease_host(bus->host_sdio);
}

static void ssb_sdio_wwite16(stwuct ssb_device *dev, u16 offset, u16 vaw)
{
	stwuct ssb_bus *bus = dev->bus;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;
	sdio_wwitew(bus->host_sdio, vaw, offset, &ewwow);
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X < %04x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}
out:
	sdio_wewease_host(bus->host_sdio);
}

static void ssb_sdio_wwite32(stwuct ssb_device *dev, u16 offset, u32 vaw)
{
	stwuct ssb_bus *bus = dev->bus;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;
	offset |= SBSDIO_SB_ACCESS_2_4B_FWAG;	/* 32 bit data access */
	sdio_wwitew(bus->host_sdio, vaw, offset, &ewwow);
	if (ewwow) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X < %08x, ewwow %d\n",
			bus->sdio_sbaddw >> 16, offset, vaw, ewwow);
	}
	if (bus->quiwks & SSB_QUIWK_SDIO_WEAD_AFTEW_WWITE32)
		sdio_weadw(bus->host_sdio, 0, &ewwow);
out:
	sdio_wewease_host(bus->host_sdio);
}

#ifdef CONFIG_SSB_BWOCKIO
static void ssb_sdio_bwock_wwite(stwuct ssb_device *dev, const void *buffew,
				   size_t count, u16 offset, u8 weg_width)
{
	size_t saved_count = count;
	stwuct ssb_bus *bus = dev->bus;
	int ewwow = 0;

	sdio_cwaim_host(bus->host_sdio);
	if (unwikewy(ssb_sdio_switch_cowe(bus, dev))) {
		ewwow = -EIO;
		goto eww_out;
	}
	offset |= bus->sdio_sbaddw & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDW_MASK;

	switch (weg_width) {
	case sizeof(u8):
		ewwow = sdio_wwitesb(bus->host_sdio, offset,
				     (void *)buffew, count);
		bweak;
	case sizeof(u16):
		WAWN_ON(count & 1);
		ewwow = sdio_wwitesb(bus->host_sdio, offset,
				     (void *)buffew, count);
		bweak;
	case sizeof(u32):
		WAWN_ON(count & 3);
		offset |= SBSDIO_SB_ACCESS_2_4B_FWAG;	/* 32 bit data access */
		ewwow = sdio_wwitesb(bus->host_sdio, offset,
				     (void *)buffew, count);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
	if (!ewwow)
		goto out;

eww_out:
	dev_dbg(ssb_sdio_dev(bus), "%04X:%04X (width=%u, wen=%zu), ewwow %d\n",
		bus->sdio_sbaddw >> 16, offset, weg_width, saved_count, ewwow);
out:
	sdio_wewease_host(bus->host_sdio);
}

#endif /* CONFIG_SSB_BWOCKIO */

/* Not "static", as it's used in main.c */
const stwuct ssb_bus_ops ssb_sdio_ops = {
	.wead8		= ssb_sdio_wead8,
	.wead16		= ssb_sdio_wead16,
	.wead32		= ssb_sdio_wead32,
	.wwite8		= ssb_sdio_wwite8,
	.wwite16	= ssb_sdio_wwite16,
	.wwite32	= ssb_sdio_wwite32,
#ifdef CONFIG_SSB_BWOCKIO
	.bwock_wead	= ssb_sdio_bwock_wead,
	.bwock_wwite	= ssb_sdio_bwock_wwite,
#endif
};

#define GOTO_EWWOW_ON(condition, descwiption) do {	\
	if (unwikewy(condition)) {			\
		ewwow_descwiption = descwiption;	\
		goto ewwow;				\
	}						\
  } whiwe (0)

int ssb_sdio_get_invawiants(stwuct ssb_bus *bus,
			    stwuct ssb_init_invawiants *iv)
{
	stwuct ssb_spwom *spwom = &iv->spwom;
	stwuct ssb_boawdinfo *bi = &iv->boawdinfo;
	const chaw *ewwow_descwiption = "none";
	stwuct sdio_func_tupwe *tupwe;
	void *mac;

	memset(spwom, 0xFF, sizeof(*spwom));
	spwom->boawdfwags_wo = 0;
	spwom->boawdfwags_hi = 0;

	tupwe = bus->host_sdio->tupwes;
	whiwe (tupwe) {
		switch (tupwe->code) {
		case 0x22: /* extended function */
			switch (tupwe->data[0]) {
			case CISTPW_FUNCE_WAN_NODE_ID:
				GOTO_EWWOW_ON((tupwe->size != 7) &&
					      (tupwe->data[1] != 6),
					      "mac tpw size");
				/* fetch the MAC addwess. */
				mac = tupwe->data + 2;
				memcpy(spwom->iw0mac, mac, ETH_AWEN);
				memcpy(spwom->et1mac, mac, ETH_AWEN);
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		case 0x80: /* vendow specific tupwe */
			switch (tupwe->data[0]) {
			case SSB_SDIO_CIS_SWOMWEV:
				GOTO_EWWOW_ON(tupwe->size != 2,
					      "swomwev tpw size");
				spwom->wevision = tupwe->data[1];
				bweak;
			case SSB_SDIO_CIS_ID:
				GOTO_EWWOW_ON((tupwe->size != 5) &&
					      (tupwe->size != 7),
					      "id tpw size");
				bi->vendow = tupwe->data[1] |
					     (tupwe->data[2]<<8);
				bweak;
			case SSB_SDIO_CIS_BOAWDWEV:
				GOTO_EWWOW_ON(tupwe->size != 2,
					      "boawdwev tpw size");
				spwom->boawd_wev = tupwe->data[1];
				bweak;
			case SSB_SDIO_CIS_PA:
				GOTO_EWWOW_ON((tupwe->size != 9) &&
					      (tupwe->size != 10),
					      "pa tpw size");
				spwom->pa0b0 = tupwe->data[1] |
					 ((u16)tupwe->data[2] << 8);
				spwom->pa0b1 = tupwe->data[3] |
					 ((u16)tupwe->data[4] << 8);
				spwom->pa0b2 = tupwe->data[5] |
					 ((u16)tupwe->data[6] << 8);
				spwom->itssi_a = tupwe->data[7];
				spwom->itssi_bg = tupwe->data[7];
				spwom->maxpww_a = tupwe->data[8];
				spwom->maxpww_bg = tupwe->data[8];
				bweak;
			case SSB_SDIO_CIS_OEMNAME:
				/* Not pwesent */
				bweak;
			case SSB_SDIO_CIS_CCODE:
				GOTO_EWWOW_ON(tupwe->size != 2,
					      "ccode tpw size");
				spwom->countwy_code = tupwe->data[1];
				bweak;
			case SSB_SDIO_CIS_ANTENNA:
				GOTO_EWWOW_ON(tupwe->size != 2,
					      "ant tpw size");
				spwom->ant_avaiwabwe_a = tupwe->data[1];
				spwom->ant_avaiwabwe_bg = tupwe->data[1];
				bweak;
			case SSB_SDIO_CIS_ANTGAIN:
				GOTO_EWWOW_ON(tupwe->size != 2,
					      "antg tpw size");
				spwom->antenna_gain.a0 = tupwe->data[1];
				spwom->antenna_gain.a1 = tupwe->data[1];
				spwom->antenna_gain.a2 = tupwe->data[1];
				spwom->antenna_gain.a3 = tupwe->data[1];
				bweak;
			case SSB_SDIO_CIS_BFWAGS:
				GOTO_EWWOW_ON((tupwe->size != 3) &&
					      (tupwe->size != 5),
					      "bfw tpw size");
				spwom->boawdfwags_wo = tupwe->data[1] |
						 ((u16)tupwe->data[2] << 8);
				bweak;
			case SSB_SDIO_CIS_WEDS:
				GOTO_EWWOW_ON(tupwe->size != 5,
					      "weds tpw size");
				spwom->gpio0 = tupwe->data[1];
				spwom->gpio1 = tupwe->data[2];
				spwom->gpio2 = tupwe->data[3];
				spwom->gpio3 = tupwe->data[4];
				bweak;
			defauwt:
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
		tupwe = tupwe->next;
	}

	wetuwn 0;
ewwow:
	dev_eww(ssb_sdio_dev(bus), "faiwed to fetch device invawiants: %s\n",
		ewwow_descwiption);
	wetuwn -ENODEV;
}

void ssb_sdio_exit(stwuct ssb_bus *bus)
{
	if (bus->bustype != SSB_BUSTYPE_SDIO)
		wetuwn;
	/* Nothing to do hewe. */
}

int ssb_sdio_init(stwuct ssb_bus *bus)
{
	if (bus->bustype != SSB_BUSTYPE_SDIO)
		wetuwn 0;

	bus->sdio_sbaddw = ~0;

	wetuwn 0;
}
