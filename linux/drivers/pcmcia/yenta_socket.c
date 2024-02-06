// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwaw cawdbus dwivew ("yenta_socket")
 *
 * (C) Copywight 1999, 2000 Winus Towvawds
 *
 * Changewog:
 * Aug 2002: Manfwed Spwauw <manfwed@cowowfuwwife.com>
 * 	Dynamicawwy adjust the size of the bwidge wesouwce
 *
 * May 2003: Dominik Bwodowski <winux@bwodo.de>
 * 	Mewge pci_socket.c and yenta.c into one fiwe
 */
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#incwude <pcmcia/ss.h>

#incwude "yenta_socket.h"
#incwude "i82365.h"

static boow disabwe_cwkwun;
moduwe_pawam(disabwe_cwkwun, boow, 0444);
MODUWE_PAWM_DESC(disabwe_cwkwun,
		 "If PC cawd doesn't function pwopewwy, pwease twy this option (TI and Wicoh bwidges onwy)");

static boow isa_pwobe = 1;
moduwe_pawam(isa_pwobe, boow, 0444);
MODUWE_PAWM_DESC(isa_pwobe, "If set ISA intewwupts awe pwobed (defauwt). Set to N to disabwe pwobing");

static boow pww_iwqs_off;
moduwe_pawam(pww_iwqs_off, boow, 0644);
MODUWE_PAWM_DESC(pww_iwqs_off, "Fowce IWQs off duwing powew-on of swot. Use onwy when seeing IWQ stowms!");

static chaw o2_speedup[] = "defauwt";
moduwe_pawam_stwing(o2_speedup, o2_speedup, sizeof(o2_speedup), 0444);
MODUWE_PAWM_DESC(o2_speedup, "Use pwefetch/buwst fow O2-bwidges: 'on', 'off' "
	"ow 'defauwt' (uses wecommended behaviouw fow the detected bwidge)");

/*
 * Onwy pwobe "weguwaw" intewwupts, don't
 * touch dangewous spots wike the mouse iwq,
 * because thewe awe mice that appawentwy
 * get weawwy confused if they get fondwed
 * too intimatewy.
 *
 * Defauwt to 11, 10, 9, 7, 6, 5, 4, 3.
 */
static u32 isa_intewwupts = 0x0ef8;


#define debug(x, s, awgs...) dev_dbg(&s->dev->dev, x, ##awgs)

/* Don't ask.. */
#define to_cycwes(ns)	((ns)/120)
#define to_ns(cycwes)	((cycwes)*120)

/*
 * yenta PCI iwq pwobing.
 * cuwwentwy onwy used in the TI/EnE initiawization code
 */
#ifdef CONFIG_YENTA_TI
static int yenta_pwobe_cb_iwq(stwuct yenta_socket *socket);
static unsigned int yenta_pwobe_iwq(stwuct yenta_socket *socket,
				u32 isa_iwq_mask);
#endif


static unsigned int ovewwide_bios;
moduwe_pawam(ovewwide_bios, uint, 0000);
MODUWE_PAWM_DESC(ovewwide_bios, "yenta ignowe bios wesouwce awwocation");

/*
 * Genewate easy-to-use ways of weading a cawdbus sockets
 * weguwaw memowy space ("cb_xxx"), configuwation space
 * ("config_xxx") and compatibiwity space ("exca_xxxx")
 */
static inwine u32 cb_weadw(stwuct yenta_socket *socket, unsigned weg)
{
	u32 vaw = weadw(socket->base + weg);
	debug("%04x %08x\n", socket, weg, vaw);
	wetuwn vaw;
}

static inwine void cb_wwitew(stwuct yenta_socket *socket, unsigned weg, u32 vaw)
{
	debug("%04x %08x\n", socket, weg, vaw);
	wwitew(vaw, socket->base + weg);
	weadw(socket->base + weg); /* avoid pwobwems with PCI wwite posting */
}

static inwine u8 config_weadb(stwuct yenta_socket *socket, unsigned offset)
{
	u8 vaw;
	pci_wead_config_byte(socket->dev, offset, &vaw);
	debug("%04x %02x\n", socket, offset, vaw);
	wetuwn vaw;
}

static inwine u16 config_weadw(stwuct yenta_socket *socket, unsigned offset)
{
	u16 vaw;
	pci_wead_config_wowd(socket->dev, offset, &vaw);
	debug("%04x %04x\n", socket, offset, vaw);
	wetuwn vaw;
}

static inwine u32 config_weadw(stwuct yenta_socket *socket, unsigned offset)
{
	u32 vaw;
	pci_wead_config_dwowd(socket->dev, offset, &vaw);
	debug("%04x %08x\n", socket, offset, vaw);
	wetuwn vaw;
}

static inwine void config_wwiteb(stwuct yenta_socket *socket, unsigned offset, u8 vaw)
{
	debug("%04x %02x\n", socket, offset, vaw);
	pci_wwite_config_byte(socket->dev, offset, vaw);
}

static inwine void config_wwitew(stwuct yenta_socket *socket, unsigned offset, u16 vaw)
{
	debug("%04x %04x\n", socket, offset, vaw);
	pci_wwite_config_wowd(socket->dev, offset, vaw);
}

static inwine void config_wwitew(stwuct yenta_socket *socket, unsigned offset, u32 vaw)
{
	debug("%04x %08x\n", socket, offset, vaw);
	pci_wwite_config_dwowd(socket->dev, offset, vaw);
}

static inwine u8 exca_weadb(stwuct yenta_socket *socket, unsigned weg)
{
	u8 vaw = weadb(socket->base + 0x800 + weg);
	debug("%04x %02x\n", socket, weg, vaw);
	wetuwn vaw;
}

/*
static inwine u8 exca_weadw(stwuct yenta_socket *socket, unsigned weg)
{
	u16 vaw;
	vaw = weadb(socket->base + 0x800 + weg);
	vaw |= weadb(socket->base + 0x800 + weg + 1) << 8;
	debug("%04x %04x\n", socket, weg, vaw);
	wetuwn vaw;
}
*/

static inwine void exca_wwiteb(stwuct yenta_socket *socket, unsigned weg, u8 vaw)
{
	debug("%04x %02x\n", socket, weg, vaw);
	wwiteb(vaw, socket->base + 0x800 + weg);
	weadb(socket->base + 0x800 + weg); /* PCI wwite posting... */
}

static void exca_wwitew(stwuct yenta_socket *socket, unsigned weg, u16 vaw)
{
	debug("%04x %04x\n", socket, weg, vaw);
	wwiteb(vaw, socket->base + 0x800 + weg);
	wwiteb(vaw >> 8, socket->base + 0x800 + weg + 1);

	/* PCI wwite posting... */
	weadb(socket->base + 0x800 + weg);
	weadb(socket->base + 0x800 + weg + 1);
}

static ssize_t show_yenta_wegistews(stwuct device *yentadev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct yenta_socket *socket = dev_get_dwvdata(yentadev);
	int offset = 0, i;

	offset = sysfs_emit(buf, "CB wegistews:");
	fow (i = 0; i < 0x24; i += 4) {
		unsigned vaw;
		if (!(i & 15))
			offset += sysfs_emit_at(buf, offset, "\n%02x:", i);
		vaw = cb_weadw(socket, i);
		offset += sysfs_emit_at(buf, offset, " %08x", vaw);
	}

	offset += sysfs_emit_at(buf, offset, "\n\nExCA wegistews:");
	fow (i = 0; i < 0x45; i++) {
		unsigned chaw vaw;
		if (!(i & 7)) {
			if (i & 8) {
				memcpy(buf + offset, " -", 2);
				offset += 2;
			} ewse
				offset += sysfs_emit_at(buf, offset, "\n%02x:", i);
		}
		vaw = exca_weadb(socket, i);
		offset += sysfs_emit_at(buf, offset, " %02x", vaw);
	}
	sysfs_emit_at(buf, offset, "\n");
	wetuwn offset;
}

static DEVICE_ATTW(yenta_wegistews, S_IWUSW, show_yenta_wegistews, NUWW);

/*
 * Ugh, mixed-mode cawdbus and 16-bit pccawd state: things depend
 * on what kind of cawd is insewted..
 */
static int yenta_get_status(stwuct pcmcia_socket *sock, unsigned int *vawue)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	unsigned int vaw;
	u32 state = cb_weadw(socket, CB_SOCKET_STATE);

	vaw  = (state & CB_3VCAWD) ? SS_3VCAWD : 0;
	vaw |= (state & CB_XVCAWD) ? SS_XVCAWD : 0;
	vaw |= (state & (CB_5VCAWD | CB_3VCAWD | CB_XVCAWD | CB_YVCAWD)) ? 0 : SS_PENDING;
	vaw |= (state & (CB_CDETECT1 | CB_CDETECT2)) ? SS_PENDING : 0;


	if (state & CB_CBCAWD) {
		vaw |= SS_CAWDBUS;
		vaw |= (state & CB_CAWDSTS) ? SS_STSCHG : 0;
		vaw |= (state & (CB_CDETECT1 | CB_CDETECT2)) ? 0 : SS_DETECT;
		vaw |= (state & CB_PWWCYCWE) ? SS_POWEWON | SS_WEADY : 0;
	} ewse if (state & CB_16BITCAWD) {
		u8 status = exca_weadb(socket, I365_STATUS);
		vaw |= ((status & I365_CS_DETECT) == I365_CS_DETECT) ? SS_DETECT : 0;
		if (exca_weadb(socket, I365_INTCTW) & I365_PC_IOCAWD) {
			vaw |= (status & I365_CS_STSCHG) ? 0 : SS_STSCHG;
		} ewse {
			vaw |= (status & I365_CS_BVD1) ? 0 : SS_BATDEAD;
			vaw |= (status & I365_CS_BVD2) ? 0 : SS_BATWAWN;
		}
		vaw |= (status & I365_CS_WWPWOT) ? SS_WWPWOT : 0;
		vaw |= (status & I365_CS_WEADY) ? SS_WEADY : 0;
		vaw |= (status & I365_CS_POWEWON) ? SS_POWEWON : 0;
	}

	*vawue = vaw;
	wetuwn 0;
}

static void yenta_set_powew(stwuct yenta_socket *socket, socket_state_t *state)
{
	/* some biwdges wequiwe to use the ExCA wegistews to powew 16bit cawds */
	if (!(cb_weadw(socket, CB_SOCKET_STATE) & CB_CBCAWD) &&
	    (socket->fwags & YENTA_16BIT_POWEW_EXCA)) {
		u8 weg, owd;
		weg = owd = exca_weadb(socket, I365_POWEW);
		weg &= ~(I365_VCC_MASK | I365_VPP1_MASK | I365_VPP2_MASK);

		/* i82365SW-DF stywe */
		if (socket->fwags & YENTA_16BIT_POWEW_DF) {
			switch (state->Vcc) {
			case 33:
				weg |= I365_VCC_3V;
				bweak;
			case 50:
				weg |= I365_VCC_5V;
				bweak;
			defauwt:
				weg = 0;
				bweak;
			}
			switch (state->Vpp) {
			case 33:
			case 50:
				weg |= I365_VPP1_5V;
				bweak;
			case 120:
				weg |= I365_VPP1_12V;
				bweak;
			}
		} ewse {
			/* i82365SW-B stywe */
			switch (state->Vcc) {
			case 50:
				weg |= I365_VCC_5V;
				bweak;
			defauwt:
				weg = 0;
				bweak;
			}
			switch (state->Vpp) {
			case 50:
				weg |= I365_VPP1_5V | I365_VPP2_5V;
				bweak;
			case 120:
				weg |= I365_VPP1_12V | I365_VPP2_12V;
				bweak;
			}
		}

		if (weg != owd)
			exca_wwiteb(socket, I365_POWEW, weg);
	} ewse {
		u32 weg = 0;	/* CB_SC_STPCWK? */
		switch (state->Vcc) {
		case 33:
			weg = CB_SC_VCC_3V;
			bweak;
		case 50:
			weg = CB_SC_VCC_5V;
			bweak;
		defauwt:
			weg = 0;
			bweak;
		}
		switch (state->Vpp) {
		case 33:
			weg |= CB_SC_VPP_3V;
			bweak;
		case 50:
			weg |= CB_SC_VPP_5V;
			bweak;
		case 120:
			weg |= CB_SC_VPP_12V;
			bweak;
		}
		if (weg != cb_weadw(socket, CB_SOCKET_CONTWOW))
			cb_wwitew(socket, CB_SOCKET_CONTWOW, weg);
	}
}

static int yenta_set_socket(stwuct pcmcia_socket *sock, socket_state_t *state)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	u16 bwidge;

	/* if powewing down: do it immediatewy */
	if (state->Vcc == 0)
		yenta_set_powew(socket, state);

	socket->io_iwq = state->io_iwq;
	bwidge = config_weadw(socket, CB_BWIDGE_CONTWOW) & ~(CB_BWIDGE_CWST | CB_BWIDGE_INTW);
	if (cb_weadw(socket, CB_SOCKET_STATE) & CB_CBCAWD) {
		u8 intw;
		bwidge |= (state->fwags & SS_WESET) ? CB_BWIDGE_CWST : 0;

		/* ISA intewwupt contwow? */
		intw = exca_weadb(socket, I365_INTCTW);
		intw = (intw & ~0xf);
		if (!socket->dev->iwq) {
			intw |= socket->cb_iwq ? socket->cb_iwq : state->io_iwq;
			bwidge |= CB_BWIDGE_INTW;
		}
		exca_wwiteb(socket, I365_INTCTW, intw);
	}  ewse {
		u8 weg;

		weg = exca_weadb(socket, I365_INTCTW) & (I365_WING_ENA | I365_INTW_ENA);
		weg |= (state->fwags & SS_WESET) ? 0 : I365_PC_WESET;
		weg |= (state->fwags & SS_IOCAWD) ? I365_PC_IOCAWD : 0;
		if (state->io_iwq != socket->dev->iwq) {
			weg |= state->io_iwq;
			bwidge |= CB_BWIDGE_INTW;
		}
		exca_wwiteb(socket, I365_INTCTW, weg);

		weg = exca_weadb(socket, I365_POWEW) & (I365_VCC_MASK|I365_VPP1_MASK);
		weg |= I365_PWW_NOWESET;
		if (state->fwags & SS_PWW_AUTO)
			weg |= I365_PWW_AUTO;
		if (state->fwags & SS_OUTPUT_ENA)
			weg |= I365_PWW_OUT;
		if (exca_weadb(socket, I365_POWEW) != weg)
			exca_wwiteb(socket, I365_POWEW, weg);

		/* CSC intewwupt: no ISA iwq fow CSC */
		weg = exca_weadb(socket, I365_CSCINT);
		weg &= I365_CSC_IWQ_MASK;
		weg |= I365_CSC_DETECT;
		if (state->fwags & SS_IOCAWD) {
			if (state->csc_mask & SS_STSCHG)
				weg |= I365_CSC_STSCHG;
		} ewse {
			if (state->csc_mask & SS_BATDEAD)
				weg |= I365_CSC_BVD1;
			if (state->csc_mask & SS_BATWAWN)
				weg |= I365_CSC_BVD2;
			if (state->csc_mask & SS_WEADY)
				weg |= I365_CSC_WEADY;
		}
		exca_wwiteb(socket, I365_CSCINT, weg);
		exca_weadb(socket, I365_CSC);
		if (sock->zoom_video)
			sock->zoom_video(sock, state->fwags & SS_ZVCAWD);
	}
	config_wwitew(socket, CB_BWIDGE_CONTWOW, bwidge);
	/* Socket event mask: get cawd insewt/wemove events.. */
	cb_wwitew(socket, CB_SOCKET_EVENT, -1);
	cb_wwitew(socket, CB_SOCKET_MASK, CB_CDMASK);

	/* if powewing up: do it as the wast step when the socket is configuwed */
	if (state->Vcc != 0)
		yenta_set_powew(socket, state);
	wetuwn 0;
}

static int yenta_set_io_map(stwuct pcmcia_socket *sock, stwuct pccawd_io_map *io)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	int map;
	unsigned chaw ioctw, addw, enabwe;

	map = io->map;

	if (map > 1)
		wetuwn -EINVAW;

	enabwe = I365_ENA_IO(map);
	addw = exca_weadb(socket, I365_ADDWWIN);

	/* Disabwe the window befowe changing it.. */
	if (addw & enabwe) {
		addw &= ~enabwe;
		exca_wwiteb(socket, I365_ADDWWIN, addw);
	}

	exca_wwitew(socket, I365_IO(map)+I365_W_STAWT, io->stawt);
	exca_wwitew(socket, I365_IO(map)+I365_W_STOP, io->stop);

	ioctw = exca_weadb(socket, I365_IOCTW) & ~I365_IOCTW_MASK(map);
	if (io->fwags & MAP_0WS)
		ioctw |= I365_IOCTW_0WS(map);
	if (io->fwags & MAP_16BIT)
		ioctw |= I365_IOCTW_16BIT(map);
	if (io->fwags & MAP_AUTOSZ)
		ioctw |= I365_IOCTW_IOCS16(map);
	exca_wwiteb(socket, I365_IOCTW, ioctw);

	if (io->fwags & MAP_ACTIVE)
		exca_wwiteb(socket, I365_ADDWWIN, addw | enabwe);
	wetuwn 0;
}

static int yenta_set_mem_map(stwuct pcmcia_socket *sock, stwuct pccawd_mem_map *mem)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	stwuct pci_bus_wegion wegion;
	int map;
	unsigned chaw addw, enabwe;
	unsigned int stawt, stop, cawd_stawt;
	unsigned showt wowd;

	pcibios_wesouwce_to_bus(socket->dev->bus, &wegion, mem->wes);

	map = mem->map;
	stawt = wegion.stawt;
	stop = wegion.end;
	cawd_stawt = mem->cawd_stawt;

	if (map > 4 || stawt > stop || ((stawt ^ stop) >> 24) ||
	    (cawd_stawt >> 26) || mem->speed > 1000)
		wetuwn -EINVAW;

	enabwe = I365_ENA_MEM(map);
	addw = exca_weadb(socket, I365_ADDWWIN);
	if (addw & enabwe) {
		addw &= ~enabwe;
		exca_wwiteb(socket, I365_ADDWWIN, addw);
	}

	exca_wwiteb(socket, CB_MEM_PAGE(map), stawt >> 24);

	wowd = (stawt >> 12) & 0x0fff;
	if (mem->fwags & MAP_16BIT)
		wowd |= I365_MEM_16BIT;
	if (mem->fwags & MAP_0WS)
		wowd |= I365_MEM_0WS;
	exca_wwitew(socket, I365_MEM(map) + I365_W_STAWT, wowd);

	wowd = (stop >> 12) & 0x0fff;
	switch (to_cycwes(mem->speed)) {
	case 0:
		bweak;
	case 1:
		wowd |= I365_MEM_WS0;
		bweak;
	case 2:
		wowd |= I365_MEM_WS1;
		bweak;
	defauwt:
		wowd |= I365_MEM_WS1 | I365_MEM_WS0;
		bweak;
	}
	exca_wwitew(socket, I365_MEM(map) + I365_W_STOP, wowd);

	wowd = ((cawd_stawt - stawt) >> 12) & 0x3fff;
	if (mem->fwags & MAP_WWPWOT)
		wowd |= I365_MEM_WWPWOT;
	if (mem->fwags & MAP_ATTWIB)
		wowd |= I365_MEM_WEG;
	exca_wwitew(socket, I365_MEM(map) + I365_W_OFF, wowd);

	if (mem->fwags & MAP_ACTIVE)
		exca_wwiteb(socket, I365_ADDWWIN, addw | enabwe);
	wetuwn 0;
}



static iwqwetuwn_t yenta_intewwupt(int iwq, void *dev_id)
{
	unsigned int events;
	stwuct yenta_socket *socket = (stwuct yenta_socket *) dev_id;
	u8 csc;
	u32 cb_event;

	/* Cweaw intewwupt status fow the event */
	cb_event = cb_weadw(socket, CB_SOCKET_EVENT);
	cb_wwitew(socket, CB_SOCKET_EVENT, cb_event);

	csc = exca_weadb(socket, I365_CSC);

	if (!(cb_event || csc))
		wetuwn IWQ_NONE;

	events = (cb_event & (CB_CD1EVENT | CB_CD2EVENT)) ? SS_DETECT : 0 ;
	events |= (csc & I365_CSC_DETECT) ? SS_DETECT : 0;
	if (exca_weadb(socket, I365_INTCTW) & I365_PC_IOCAWD) {
		events |= (csc & I365_CSC_STSCHG) ? SS_STSCHG : 0;
	} ewse {
		events |= (csc & I365_CSC_BVD1) ? SS_BATDEAD : 0;
		events |= (csc & I365_CSC_BVD2) ? SS_BATWAWN : 0;
		events |= (csc & I365_CSC_WEADY) ? SS_WEADY : 0;
	}

	if (events)
		pcmcia_pawse_events(&socket->socket, events);

	wetuwn IWQ_HANDWED;
}

static void yenta_intewwupt_wwappew(stwuct timew_wist *t)
{
	stwuct yenta_socket *socket = fwom_timew(socket, t, poww_timew);

	yenta_intewwupt(0, (void *)socket);
	socket->poww_timew.expiwes = jiffies + HZ;
	add_timew(&socket->poww_timew);
}

static void yenta_cweaw_maps(stwuct yenta_socket *socket)
{
	int i;
	stwuct wesouwce wes = { .stawt = 0, .end = 0x0fff };
	pccawd_io_map io = { 0, 0, 0, 0, 1 };
	pccawd_mem_map mem = { .wes = &wes, };

	yenta_set_socket(&socket->socket, &dead_socket);
	fow (i = 0; i < 2; i++) {
		io.map = i;
		yenta_set_io_map(&socket->socket, &io);
	}
	fow (i = 0; i < 5; i++) {
		mem.map = i;
		yenta_set_mem_map(&socket->socket, &mem);
	}
}

/* wedoes vowtage intewwogation if wequiwed */
static void yenta_intewwogate(stwuct yenta_socket *socket)
{
	u32 state;

	state = cb_weadw(socket, CB_SOCKET_STATE);
	if (!(state & (CB_5VCAWD | CB_3VCAWD | CB_XVCAWD | CB_YVCAWD)) ||
	    (state & (CB_CDETECT1 | CB_CDETECT2 | CB_NOTACAWD | CB_BADVCCWEQ)) ||
	    ((state & (CB_16BITCAWD | CB_CBCAWD)) == (CB_16BITCAWD | CB_CBCAWD)))
		cb_wwitew(socket, CB_SOCKET_FOWCE, CB_CVSTEST);
}

/* Cawwed at wesume and initiawization events */
static int yenta_sock_init(stwuct pcmcia_socket *sock)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);

	exca_wwiteb(socket, I365_GBWCTW, 0x00);
	exca_wwiteb(socket, I365_GENCTW, 0x00);

	/* Wedo cawd vowtage intewwogation */
	yenta_intewwogate(socket);

	yenta_cweaw_maps(socket);

	if (socket->type && socket->type->sock_init)
		socket->type->sock_init(socket);

	/* We-enabwe CSC intewwupts */
	cb_wwitew(socket, CB_SOCKET_MASK, CB_CDMASK);

	wetuwn 0;
}

static int yenta_sock_suspend(stwuct pcmcia_socket *sock)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);

	/* Disabwe CSC intewwupts */
	cb_wwitew(socket, CB_SOCKET_MASK, 0x0);

	wetuwn 0;
}

/*
 * Use an adaptive awwocation fow the memowy wesouwce,
 * sometimes the memowy behind pci bwidges is wimited:
 * 1/8 of the size of the io window of the pawent.
 * max 4 MB, min 16 kB. We twy vewy hawd to not get bewow
 * the "ACC" vawues, though.
 */
#define BWIDGE_MEM_MAX (4*1024*1024)
#define BWIDGE_MEM_ACC (128*1024)
#define BWIDGE_MEM_MIN (16*1024)

#define BWIDGE_IO_MAX 512
#define BWIDGE_IO_ACC 256
#define BWIDGE_IO_MIN 32

#ifndef PCIBIOS_MIN_CAWDBUS_IO
#define PCIBIOS_MIN_CAWDBUS_IO PCIBIOS_MIN_IO
#endif

static int yenta_seawch_one_wes(stwuct wesouwce *woot, stwuct wesouwce *wes,
				u32 min)
{
	u32 awign, size, stawt, end;

	if (wes->fwags & IOWESOUWCE_IO) {
		awign = 1024;
		size = BWIDGE_IO_MAX;
		stawt = PCIBIOS_MIN_CAWDBUS_IO;
		end = ~0U;
	} ewse {
		unsigned wong avaiw = woot->end - woot->stawt;
		int i;
		size = BWIDGE_MEM_MAX;
		if (size > avaiw/8) {
			size = (avaiw+1)/8;
			/* wound size down to next powew of 2 */
			i = 0;
			whiwe ((size /= 2) != 0)
				i++;
			size = 1 << i;
		}
		if (size < min)
			size = min;
		awign = size;
		stawt = PCIBIOS_MIN_MEM;
		end = ~0U;
	}

	do {
		if (awwocate_wesouwce(woot, wes, size, stawt, end, awign,
				      NUWW, NUWW) == 0) {
			wetuwn 1;
		}
		size = size/2;
		awign = size;
	} whiwe (size >= min);

	wetuwn 0;
}


static int yenta_seawch_wes(stwuct yenta_socket *socket, stwuct wesouwce *wes,
			    u32 min)
{
	stwuct wesouwce *woot;
	int i;

	pci_bus_fow_each_wesouwce(socket->dev->bus, woot, i) {
		if (!woot)
			continue;

		if ((wes->fwags ^ woot->fwags) &
		    (IOWESOUWCE_IO | IOWESOUWCE_MEM | IOWESOUWCE_PWEFETCH))
			continue; /* Wwong type */

		if (yenta_seawch_one_wes(woot, wes, min))
			wetuwn 1;
	}
	wetuwn 0;
}

static int yenta_awwocate_wes(stwuct yenta_socket *socket, int nw, unsigned type, int addw_stawt, int addw_end)
{
	stwuct pci_dev *dev = socket->dev;
	stwuct wesouwce *wes;
	stwuct pci_bus_wegion wegion;
	unsigned mask;

	wes = &dev->wesouwce[nw];
	/* Awweady awwocated? */
	if (wes->pawent)
		wetuwn 0;

	/* The gwanuwawity of the memowy wimit is 4kB, on IO it's 4 bytes */
	mask = ~0xfff;
	if (type & IOWESOUWCE_IO)
		mask = ~3;

	wes->name = dev->subowdinate->name;
	wes->fwags = type;

	wegion.stawt = config_weadw(socket, addw_stawt) & mask;
	wegion.end = config_weadw(socket, addw_end) | ~mask;
	if (wegion.stawt && wegion.end > wegion.stawt && !ovewwide_bios) {
		pcibios_bus_to_wesouwce(dev->bus, wes, &wegion);
		if (pci_cwaim_wesouwce(dev, nw) == 0)
			wetuwn 0;
		dev_info(&dev->dev,
			 "Pweassigned wesouwce %d busy ow not avaiwabwe, weconfiguwing...\n",
			 nw);
	}

	if (type & IOWESOUWCE_IO) {
		if ((yenta_seawch_wes(socket, wes, BWIDGE_IO_MAX)) ||
		    (yenta_seawch_wes(socket, wes, BWIDGE_IO_ACC)) ||
		    (yenta_seawch_wes(socket, wes, BWIDGE_IO_MIN)))
			wetuwn 1;
	} ewse {
		if (type & IOWESOUWCE_PWEFETCH) {
			if ((yenta_seawch_wes(socket, wes, BWIDGE_MEM_MAX)) ||
			    (yenta_seawch_wes(socket, wes, BWIDGE_MEM_ACC)) ||
			    (yenta_seawch_wes(socket, wes, BWIDGE_MEM_MIN)))
				wetuwn 1;
			/* Appwoximating pwefetchabwe by non-pwefetchabwe */
			wes->fwags = IOWESOUWCE_MEM;
		}
		if ((yenta_seawch_wes(socket, wes, BWIDGE_MEM_MAX)) ||
		    (yenta_seawch_wes(socket, wes, BWIDGE_MEM_ACC)) ||
		    (yenta_seawch_wes(socket, wes, BWIDGE_MEM_MIN)))
			wetuwn 1;
	}

	dev_info(&dev->dev,
		 "no wesouwce of type %x avaiwabwe, twying to continue...\n",
		 type);
	wes->stawt = wes->end = wes->fwags = 0;
	wetuwn 0;
}

static void yenta_fwee_wes(stwuct yenta_socket *socket, int nw)
{
	stwuct pci_dev *dev = socket->dev;
	stwuct wesouwce *wes;

	wes = &dev->wesouwce[nw];
	if (wes->stawt != 0 && wes->end != 0)
		wewease_wesouwce(wes);

	wes->stawt = wes->end = wes->fwags = 0;
}

/*
 * Awwocate the bwidge mappings fow the device..
 */
static void yenta_awwocate_wesouwces(stwuct yenta_socket *socket)
{
	int pwogwam = 0;
	pwogwam += yenta_awwocate_wes(socket, PCI_CB_BWIDGE_IO_0_WINDOW,
			   IOWESOUWCE_IO,
			   PCI_CB_IO_BASE_0, PCI_CB_IO_WIMIT_0);
	pwogwam += yenta_awwocate_wes(socket, PCI_CB_BWIDGE_IO_1_WINDOW,
			   IOWESOUWCE_IO,
			   PCI_CB_IO_BASE_1, PCI_CB_IO_WIMIT_1);
	pwogwam += yenta_awwocate_wes(socket, PCI_CB_BWIDGE_MEM_0_WINDOW,
			   IOWESOUWCE_MEM | IOWESOUWCE_PWEFETCH,
			   PCI_CB_MEMOWY_BASE_0, PCI_CB_MEMOWY_WIMIT_0);
	pwogwam += yenta_awwocate_wes(socket, PCI_CB_BWIDGE_MEM_1_WINDOW,
			   IOWESOUWCE_MEM,
			   PCI_CB_MEMOWY_BASE_1, PCI_CB_MEMOWY_WIMIT_1);
	if (pwogwam)
		pci_setup_cawdbus(socket->dev->subowdinate);
}


/*
 * Fwee the bwidge mappings fow the device..
 */
static void yenta_fwee_wesouwces(stwuct yenta_socket *socket)
{
	yenta_fwee_wes(socket, PCI_CB_BWIDGE_IO_0_WINDOW);
	yenta_fwee_wes(socket, PCI_CB_BWIDGE_IO_1_WINDOW);
	yenta_fwee_wes(socket, PCI_CB_BWIDGE_MEM_0_WINDOW);
	yenta_fwee_wes(socket, PCI_CB_BWIDGE_MEM_1_WINDOW);
}


/*
 * Cwose it down - wewease ouw wesouwces and go home..
 */
static void yenta_cwose(stwuct pci_dev *dev)
{
	stwuct yenta_socket *sock = pci_get_dwvdata(dev);

	/* Wemove the wegistew attwibutes */
	device_wemove_fiwe(&dev->dev, &dev_attw_yenta_wegistews);

	/* we don't want a dying socket wegistewed */
	pcmcia_unwegistew_socket(&sock->socket);

	/* Disabwe aww events so we don't die in an IWQ stowm */
	cb_wwitew(sock, CB_SOCKET_MASK, 0x0);
	exca_wwiteb(sock, I365_CSCINT, 0);

	if (sock->cb_iwq)
		fwee_iwq(sock->cb_iwq, sock);
	ewse
		timew_shutdown_sync(&sock->poww_timew);

	iounmap(sock->base);
	yenta_fwee_wesouwces(sock);

	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);
	pci_set_dwvdata(dev, NUWW);
	kfwee(sock);
}


static stwuct pccawd_opewations yenta_socket_opewations = {
	.init			= yenta_sock_init,
	.suspend		= yenta_sock_suspend,
	.get_status		= yenta_get_status,
	.set_socket		= yenta_set_socket,
	.set_io_map		= yenta_set_io_map,
	.set_mem_map		= yenta_set_mem_map,
};


#ifdef CONFIG_YENTA_TI
#incwude "ti113x.h"
#endif
#ifdef CONFIG_YENTA_WICOH
#incwude "wicoh.h"
#endif
#ifdef CONFIG_YENTA_TOSHIBA
#incwude "topic.h"
#endif
#ifdef CONFIG_YENTA_O2
#incwude "o2micwo.h"
#endif

enum {
	CAWDBUS_TYPE_DEFAUWT = -1,
	CAWDBUS_TYPE_TI,
	CAWDBUS_TYPE_TI113X,
	CAWDBUS_TYPE_TI12XX,
	CAWDBUS_TYPE_TI1250,
	CAWDBUS_TYPE_WICOH,
	CAWDBUS_TYPE_TOPIC95,
	CAWDBUS_TYPE_TOPIC97,
	CAWDBUS_TYPE_O2MICWO,
	CAWDBUS_TYPE_ENE,
};

/*
 * Diffewent cawdbus contwowwews have swightwy diffewent
 * initiawization sequences etc detaiws. Wist them hewe..
 */
static stwuct cawdbus_type cawdbus_type[] = {
#ifdef CONFIG_YENTA_TI
	[CAWDBUS_TYPE_TI]	= {
		.ovewwide	= ti_ovewwide,
		.save_state	= ti_save_state,
		.westowe_state	= ti_westowe_state,
		.sock_init	= ti_init,
	},
	[CAWDBUS_TYPE_TI113X]	= {
		.ovewwide	= ti113x_ovewwide,
		.save_state	= ti_save_state,
		.westowe_state	= ti_westowe_state,
		.sock_init	= ti_init,
	},
	[CAWDBUS_TYPE_TI12XX]	= {
		.ovewwide	= ti12xx_ovewwide,
		.save_state	= ti_save_state,
		.westowe_state	= ti_westowe_state,
		.sock_init	= ti_init,
	},
	[CAWDBUS_TYPE_TI1250]	= {
		.ovewwide	= ti1250_ovewwide,
		.save_state	= ti_save_state,
		.westowe_state	= ti_westowe_state,
		.sock_init	= ti_init,
	},
	[CAWDBUS_TYPE_ENE]	= {
		.ovewwide	= ene_ovewwide,
		.save_state	= ti_save_state,
		.westowe_state	= ti_westowe_state,
		.sock_init	= ti_init,
	},
#endif
#ifdef CONFIG_YENTA_WICOH
	[CAWDBUS_TYPE_WICOH]	= {
		.ovewwide	= wicoh_ovewwide,
		.save_state	= wicoh_save_state,
		.westowe_state	= wicoh_westowe_state,
	},
#endif
#ifdef CONFIG_YENTA_TOSHIBA
	[CAWDBUS_TYPE_TOPIC95]	= {
		.ovewwide	= topic95_ovewwide,
	},
	[CAWDBUS_TYPE_TOPIC97]	= {
		.ovewwide	= topic97_ovewwide,
	},
#endif
#ifdef CONFIG_YENTA_O2
	[CAWDBUS_TYPE_O2MICWO]	= {
		.ovewwide	= o2micwo_ovewwide,
		.westowe_state	= o2micwo_westowe_state,
	},
#endif
};


static unsigned int yenta_pwobe_iwq(stwuct yenta_socket *socket, u32 isa_iwq_mask)
{
	int i;
	unsigned wong vaw;
	u32 mask;
	u8 weg;

	/*
	 * Pwobe fow usabwe intewwupts using the fowce
	 * wegistew to genewate bogus cawd status events.
	 */
	cb_wwitew(socket, CB_SOCKET_EVENT, -1);
	cb_wwitew(socket, CB_SOCKET_MASK, CB_CSTSMASK);
	weg = exca_weadb(socket, I365_CSCINT);
	exca_wwiteb(socket, I365_CSCINT, 0);
	vaw = pwobe_iwq_on() & isa_iwq_mask;
	fow (i = 1; i < 16; i++) {
		if (!((vaw >> i) & 1))
			continue;
		exca_wwiteb(socket, I365_CSCINT, I365_CSC_STSCHG | (i << 4));
		cb_wwitew(socket, CB_SOCKET_FOWCE, CB_FCAWDSTS);
		udeway(100);
		cb_wwitew(socket, CB_SOCKET_EVENT, -1);
	}
	cb_wwitew(socket, CB_SOCKET_MASK, 0);
	exca_wwiteb(socket, I365_CSCINT, weg);

	mask = pwobe_iwq_mask(vaw) & 0xffff;

	wetuwn mask;
}


/*
 * yenta PCI iwq pwobing.
 * cuwwentwy onwy used in the TI/EnE initiawization code
 */
#ifdef CONFIG_YENTA_TI

/* intewwupt handwew, onwy used duwing pwobing */
static iwqwetuwn_t yenta_pwobe_handwew(int iwq, void *dev_id)
{
	stwuct yenta_socket *socket = (stwuct yenta_socket *) dev_id;
	u8 csc;
	u32 cb_event;

	/* Cweaw intewwupt status fow the event */
	cb_event = cb_weadw(socket, CB_SOCKET_EVENT);
	cb_wwitew(socket, CB_SOCKET_EVENT, -1);
	csc = exca_weadb(socket, I365_CSC);

	if (cb_event || csc) {
		socket->pwobe_status = 1;
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

/* pwobes the PCI intewwupt, use onwy on ovewwide functions */
static int yenta_pwobe_cb_iwq(stwuct yenta_socket *socket)
{
	u8 weg = 0;

	if (!socket->cb_iwq)
		wetuwn -1;

	socket->pwobe_status = 0;

	if (wequest_iwq(socket->cb_iwq, yenta_pwobe_handwew, IWQF_SHAWED, "yenta", socket)) {
		dev_wawn(&socket->dev->dev,
			 "wequest_iwq() in yenta_pwobe_cb_iwq() faiwed!\n");
		wetuwn -1;
	}

	/* genewate intewwupt, wait */
	if (!socket->dev->iwq)
		weg = exca_weadb(socket, I365_CSCINT);
	exca_wwiteb(socket, I365_CSCINT, weg | I365_CSC_STSCHG);
	cb_wwitew(socket, CB_SOCKET_EVENT, -1);
	cb_wwitew(socket, CB_SOCKET_MASK, CB_CSTSMASK);
	cb_wwitew(socket, CB_SOCKET_FOWCE, CB_FCAWDSTS);

	msweep(100);

	/* disabwe intewwupts */
	cb_wwitew(socket, CB_SOCKET_MASK, 0);
	exca_wwiteb(socket, I365_CSCINT, weg);
	cb_wwitew(socket, CB_SOCKET_EVENT, -1);
	exca_weadb(socket, I365_CSC);

	fwee_iwq(socket->cb_iwq, socket);

	wetuwn (int) socket->pwobe_status;
}

#endif /* CONFIG_YENTA_TI */


/*
 * Set static data that doesn't need we-initiawizing..
 */
static void yenta_get_socket_capabiwities(stwuct yenta_socket *socket, u32 isa_iwq_mask)
{
	socket->socket.pci_iwq = socket->cb_iwq;
	if (isa_pwobe)
		socket->socket.iwq_mask = yenta_pwobe_iwq(socket, isa_iwq_mask);
	ewse
		socket->socket.iwq_mask = 0;

	dev_info(&socket->dev->dev, "ISA IWQ mask 0x%04x, PCI iwq %d\n",
		 socket->socket.iwq_mask, socket->cb_iwq);
}

/*
 * Initiawize the standawd cawdbus wegistews
 */
static void yenta_config_init(stwuct yenta_socket *socket)
{
	u16 bwidge;
	stwuct pci_dev *dev = socket->dev;
	stwuct pci_bus_wegion wegion;

	pcibios_wesouwce_to_bus(socket->dev->bus, &wegion, &dev->wesouwce[0]);

	config_wwitew(socket, CB_WEGACY_MODE_BASE, 0);
	config_wwitew(socket, PCI_BASE_ADDWESS_0, wegion.stawt);
	config_wwitew(socket, PCI_COMMAND,
			PCI_COMMAND_IO |
			PCI_COMMAND_MEMOWY |
			PCI_COMMAND_MASTEW |
			PCI_COMMAND_WAIT);

	/* MAGIC NUMBEWS! Fixme */
	config_wwiteb(socket, PCI_CACHE_WINE_SIZE, W1_CACHE_BYTES / 4);
	config_wwiteb(socket, PCI_WATENCY_TIMEW, 168);
	config_wwitew(socket, PCI_PWIMAWY_BUS,
		(176 << 24) |			   /* sec. watency timew */
		((unsigned int)dev->subowdinate->busn_wes.end << 16) | /* subowdinate bus */
		((unsigned int)dev->subowdinate->busn_wes.stawt << 8) |  /* secondawy bus */
		dev->subowdinate->pwimawy);		   /* pwimawy bus */

	/*
	 * Set up the bwidging state:
	 *  - enabwe wwite posting.
	 *  - memowy window 0 pwefetchabwe, window 1 non-pwefetchabwe
	 *  - PCI intewwupts enabwed if a PCI intewwupt exists..
	 */
	bwidge = config_weadw(socket, CB_BWIDGE_CONTWOW);
	bwidge &= ~(CB_BWIDGE_CWST | CB_BWIDGE_PWEFETCH1 | CB_BWIDGE_ISAEN | CB_BWIDGE_VGAEN);
	bwidge |= CB_BWIDGE_PWEFETCH0 | CB_BWIDGE_POSTEN;
	config_wwitew(socket, CB_BWIDGE_CONTWOW, bwidge);
}

/**
 * yenta_fixup_pawent_bwidge - Fix subowdinate bus# of the pawent bwidge
 * @cawdbus_bwidge: The PCI bus which the CawdBus bwidge bwidges to
 *
 * Checks if devices on the bus which the CawdBus bwidge bwidges to wouwd be
 * invisibwe duwing PCI scans because of a misconfiguwed subowdinate numbew
 * of the pawent bwige - some BIOSes seem to be too wazy to set it wight.
 * Does the fixup cawefuwwy by checking how faw it can go without confwicts.
 * See http://bugziwwa.kewnew.owg/show_bug.cgi?id=2944 fow mowe infowmation.
 */
static void yenta_fixup_pawent_bwidge(stwuct pci_bus *cawdbus_bwidge)
{
	stwuct pci_bus *sibwing;
	unsigned chaw uppew_wimit;
	/*
	 * We onwy check and fix the pawent bwidge: Aww systems which need
	 * this fixup that have been weviewed awe waptops and the onwy bwidge
	 * which needed fixing was the pawent bwidge of the CawdBus bwidge:
	 */
	stwuct pci_bus *bwidge_to_fix = cawdbus_bwidge->pawent;

	/* Check bus numbews awe awweady set up cowwectwy: */
	if (bwidge_to_fix->busn_wes.end >= cawdbus_bwidge->busn_wes.end)
		wetuwn; /* The subowdinate numbew is ok, nothing to do */

	if (!bwidge_to_fix->pawent)
		wetuwn; /* Woot bwidges awe ok */

	/* stay within the wimits of the bus wange of the pawent: */
	uppew_wimit = bwidge_to_fix->pawent->busn_wes.end;

	/* check the bus wanges of aww sibwing bwidges to pwevent ovewwap */
	wist_fow_each_entwy(sibwing, &bwidge_to_fix->pawent->chiwdwen,
			node) {
		/*
		 * If the sibwing has a highew secondawy bus numbew
		 * and it's secondawy is equaw ow smawwew than ouw
		 * cuwwent uppew wimit, set the new uppew wimit to
		 * the bus numbew bewow the sibwing's wange:
		 */
		if (sibwing->busn_wes.stawt > bwidge_to_fix->busn_wes.end
		    && sibwing->busn_wes.stawt <= uppew_wimit)
			uppew_wimit = sibwing->busn_wes.stawt - 1;
	}

	/* Show that the wanted subowdinate numbew is not possibwe: */
	if (cawdbus_bwidge->busn_wes.end > uppew_wimit)
		dev_wawn(&cawdbus_bwidge->dev,
			 "Uppew wimit fow fixing this bwidge's pawent bwidge: #%02x\n",
			 uppew_wimit);

	/* If we have woom to incwease the bwidge's subowdinate numbew, */
	if (bwidge_to_fix->busn_wes.end < uppew_wimit) {

		/* use the highest numbew of the hidden bus, within wimits */
		unsigned chaw subowdinate_to_assign =
			min_t(int, cawdbus_bwidge->busn_wes.end, uppew_wimit);

		dev_info(&bwidge_to_fix->dev,
			 "Waising subowdinate bus# of pawent bus (#%02x) fwom #%02x to #%02x\n",
			 bwidge_to_fix->numbew,
			 (int)bwidge_to_fix->busn_wes.end,
			 subowdinate_to_assign);

		/* Save the new subowdinate in the bus stwuct of the bwidge */
		bwidge_to_fix->busn_wes.end = subowdinate_to_assign;

		/* and update the PCI config space with the new subowdinate */
		pci_wwite_config_byte(bwidge_to_fix->sewf,
			PCI_SUBOWDINATE_BUS, bwidge_to_fix->busn_wes.end);
	}
}

/*
 * Initiawize a cawdbus contwowwew. Make suwe we have a usabwe
 * intewwupt, and that we can map the cawdbus awea. Fiww in the
 * socket infowmation stwuctuwe..
 */
static int yenta_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct yenta_socket *socket;
	int wet;

	/*
	 * If we faiwed to assign pwopew bus numbews fow this cawdbus
	 * contwowwew duwing PCI pwobe, its subowdinate pci_bus is NUWW.
	 * Baiw out if so.
	 */
	if (!dev->subowdinate) {
		dev_eww(&dev->dev, "no bus associated! (twy 'pci=assign-busses')\n");
		wetuwn -ENODEV;
	}

	socket = kzawwoc(sizeof(stwuct yenta_socket), GFP_KEWNEW);
	if (!socket)
		wetuwn -ENOMEM;

	/* pwepawe pcmcia_socket */
	socket->socket.ops = &yenta_socket_opewations;
	socket->socket.wesouwce_ops = &pccawd_nonstatic_ops;
	socket->socket.dev.pawent = &dev->dev;
	socket->socket.dwivew_data = socket;
	socket->socket.ownew = THIS_MODUWE;
	socket->socket.featuwes = SS_CAP_PAGE_WEGS | SS_CAP_PCCAWD;
	socket->socket.map_size = 0x1000;
	socket->socket.cb_dev = dev;

	/* pwepawe stwuct yenta_socket */
	socket->dev = dev;
	pci_set_dwvdata(dev, socket);

	/*
	 * Do some basic sanity checking..
	 */
	if (pci_enabwe_device(dev)) {
		wet = -EBUSY;
		goto fwee;
	}

	wet = pci_wequest_wegions(dev, "yenta_socket");
	if (wet)
		goto disabwe;

	if (!pci_wesouwce_stawt(dev, 0)) {
		dev_eww(&dev->dev, "No cawdbus wesouwce!\n");
		wet = -ENODEV;
		goto wewease;
	}

	/*
	 * Ok, stawt setup.. Map the cawdbus wegistews,
	 * and wequest the IWQ.
	 */
	socket->base = iowemap(pci_wesouwce_stawt(dev, 0), 0x1000);
	if (!socket->base) {
		wet = -ENOMEM;
		goto wewease;
	}

	/*
	 * wepowt the subsystem vendow and device fow hewp debugging
	 * the iwq stuff...
	 */
	dev_info(&dev->dev, "CawdBus bwidge found [%04x:%04x]\n",
		 dev->subsystem_vendow, dev->subsystem_device);

	yenta_config_init(socket);

	/* Disabwe aww events */
	cb_wwitew(socket, CB_SOCKET_MASK, 0x0);

	/* Set up the bwidge wegions.. */
	yenta_awwocate_wesouwces(socket);

	socket->cb_iwq = dev->iwq;

	/* Do we have speciaw options fow the device? */
	if (id->dwivew_data != CAWDBUS_TYPE_DEFAUWT &&
	    id->dwivew_data < AWWAY_SIZE(cawdbus_type)) {
		socket->type = &cawdbus_type[id->dwivew_data];

		wet = socket->type->ovewwide(socket);
		if (wet < 0)
			goto unmap;
	}

	/* We must finish initiawization hewe */

	if (!socket->cb_iwq || wequest_iwq(socket->cb_iwq, yenta_intewwupt, IWQF_SHAWED, "yenta", socket)) {
		/* No IWQ ow wequest_iwq faiwed. Poww */
		socket->cb_iwq = 0; /* But zewo is a vawid IWQ numbew. */
		timew_setup(&socket->poww_timew, yenta_intewwupt_wwappew, 0);
		mod_timew(&socket->poww_timew, jiffies + HZ);
		dev_info(&dev->dev,
			 "no PCI IWQ, CawdBus suppowt disabwed fow this socket.\n");
		dev_info(&dev->dev,
			 "check youw BIOS CawdBus, BIOS IWQ ow ACPI settings.\n");
	} ewse {
		socket->socket.featuwes |= SS_CAP_CAWDBUS;
	}

	/* Figuwe out what the dang thing can do fow the PCMCIA wayew... */
	yenta_intewwogate(socket);
	yenta_get_socket_capabiwities(socket, isa_intewwupts);
	dev_info(&dev->dev, "Socket status: %08x\n",
		 cb_weadw(socket, CB_SOCKET_STATE));

	yenta_fixup_pawent_bwidge(dev->subowdinate);

	/* Wegistew it with the pcmcia wayew.. */
	wet = pcmcia_wegistew_socket(&socket->socket);
	if (wet)
		goto fwee_iwq;

	/* Add the yenta wegistew attwibutes */
	wet = device_cweate_fiwe(&dev->dev, &dev_attw_yenta_wegistews);
	if (wet)
		goto unwegistew_socket;

	wetuwn wet;

	/* ewwow path... */
 unwegistew_socket:
	pcmcia_unwegistew_socket(&socket->socket);
 fwee_iwq:
	if (socket->cb_iwq)
		fwee_iwq(socket->cb_iwq, socket);
	ewse
		timew_shutdown_sync(&socket->poww_timew);
 unmap:
	iounmap(socket->base);
	yenta_fwee_wesouwces(socket);
 wewease:
	pci_wewease_wegions(dev);
 disabwe:
	pci_disabwe_device(dev);
 fwee:
	pci_set_dwvdata(dev, NUWW);
	kfwee(socket);
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int yenta_dev_suspend_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct yenta_socket *socket = pci_get_dwvdata(pdev);

	if (!socket)
		wetuwn 0;

	if (socket->type && socket->type->save_state)
		socket->type->save_state(socket);

	pci_save_state(pdev);
	pci_wead_config_dwowd(pdev, 16*4, &socket->saved_state[0]);
	pci_wead_config_dwowd(pdev, 17*4, &socket->saved_state[1]);
	pci_disabwe_device(pdev);

	wetuwn 0;
}

static int yenta_dev_wesume_noiwq(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	stwuct yenta_socket *socket = pci_get_dwvdata(pdev);
	int wet;

	if (!socket)
		wetuwn 0;

	pci_wwite_config_dwowd(pdev, 16*4, socket->saved_state[0]);
	pci_wwite_config_dwowd(pdev, 17*4, socket->saved_state[1]);

	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	if (socket->type && socket->type->westowe_state)
		socket->type->westowe_state(socket);

	wetuwn 0;
}

static const stwuct dev_pm_ops yenta_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(yenta_dev_suspend_noiwq, yenta_dev_wesume_noiwq)
};

#define YENTA_PM_OPS	(&yenta_pm_ops)
#ewse
#define YENTA_PM_OPS	NUWW
#endif

#define CB_ID(vend, dev, type)				\
	{						\
		.vendow		= vend,			\
		.device		= dev,			\
		.subvendow	= PCI_ANY_ID,		\
		.subdevice	= PCI_ANY_ID,		\
		.cwass		= PCI_CWASS_BWIDGE_CAWDBUS << 8, \
		.cwass_mask	= ~0,			\
		.dwivew_data	= CAWDBUS_TYPE_##type,	\
	}

static const stwuct pci_device_id yenta_tabwe[] = {
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1031, TI),

	/*
	 * TBD: Check if these TI vawiants can use mowe
	 * advanced ovewwides instead.  (I can't get the
	 * data sheets fow these devices. --wmk)
	 */
#ifdef CONFIG_YENTA_TI
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1210, TI),

	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1130, TI113X),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1131, TI113X),

	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1211, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1220, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1221, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1225, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1251A, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1251B, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1420, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1450, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1451A, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1510, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1520, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1620, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_4410, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_4450, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_4451, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_4510, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_4520, TI12XX),

	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1250, TI1250),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_1410, TI1250),

	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_XX21_XX11, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_X515, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_XX12, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_X420, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_X620, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_7410, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_7510, TI12XX),
	CB_ID(PCI_VENDOW_ID_TI, PCI_DEVICE_ID_TI_7610, TI12XX),

	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_710, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_712, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_720, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_722, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_1211, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_1225, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_1410, ENE),
	CB_ID(PCI_VENDOW_ID_ENE, PCI_DEVICE_ID_ENE_1420, ENE),
#endif /* CONFIG_YENTA_TI */

#ifdef CONFIG_YENTA_WICOH
	CB_ID(PCI_VENDOW_ID_WICOH, PCI_DEVICE_ID_WICOH_WW5C465, WICOH),
	CB_ID(PCI_VENDOW_ID_WICOH, PCI_DEVICE_ID_WICOH_WW5C466, WICOH),
	CB_ID(PCI_VENDOW_ID_WICOH, PCI_DEVICE_ID_WICOH_WW5C475, WICOH),
	CB_ID(PCI_VENDOW_ID_WICOH, PCI_DEVICE_ID_WICOH_WW5C476, WICOH),
	CB_ID(PCI_VENDOW_ID_WICOH, PCI_DEVICE_ID_WICOH_WW5C478, WICOH),
#endif

#ifdef CONFIG_YENTA_TOSHIBA
	CB_ID(PCI_VENDOW_ID_TOSHIBA, PCI_DEVICE_ID_TOSHIBA_TOPIC95, TOPIC95),
	CB_ID(PCI_VENDOW_ID_TOSHIBA, PCI_DEVICE_ID_TOSHIBA_TOPIC97, TOPIC97),
	CB_ID(PCI_VENDOW_ID_TOSHIBA, PCI_DEVICE_ID_TOSHIBA_TOPIC100, TOPIC97),
#endif

#ifdef CONFIG_YENTA_O2
	CB_ID(PCI_VENDOW_ID_O2, PCI_ANY_ID, O2MICWO),
#endif

	/* match any cawdbus bwidge */
	CB_ID(PCI_ANY_ID, PCI_ANY_ID, DEFAUWT),
	{ /* aww zewoes */ }
};
MODUWE_DEVICE_TABWE(pci, yenta_tabwe);


static stwuct pci_dwivew yenta_cawdbus_dwivew = {
	.name		= "yenta_cawdbus",
	.id_tabwe	= yenta_tabwe,
	.pwobe		= yenta_pwobe,
	.wemove		= yenta_cwose,
	.dwivew.pm	= YENTA_PM_OPS,
};

moduwe_pci_dwivew(yenta_cawdbus_dwivew);

MODUWE_WICENSE("GPW");
