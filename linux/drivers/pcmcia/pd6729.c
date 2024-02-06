/*
 * Dwivew fow the Ciwwus PD6729 PCI-PCMCIA bwidge.
 *
 * Based on the i82092.c dwivew.
 *
 * This softwawe may be used and distwibuted accowding to the tewms of
 * the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/io.h>

#incwude <pcmcia/ss.h>


#incwude "pd6729.h"
#incwude "i82365.h"
#incwude "ciwwus.h"

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Dwivew fow the Ciwwus PD6729 PCI-PCMCIA bwidge");
MODUWE_AUTHOW("Jun Komuwo <komuwojun-mbn@nifty.com>");

#define MAX_SOCKETS 2

/*
 * simpwe hewpew functions
 * Extewnaw cwock time, in nanoseconds.  120 ns = 8.33 MHz
 */
#define to_cycwes(ns)	((ns)/120)

#ifndef NO_IWQ
#define NO_IWQ	((unsigned int)(0))
#endif

/*
 * PAWAMETEWS
 *  iwq_mode=n
 *     Specifies the intewwupt dewivewy mode.  The defauwt (1) is to use PCI
 *     intewwupts; a vawue of 0 sewects ISA intewwupts. This must be set fow
 *     cowwect opewation of PCI cawd weadews.
 */

static int iwq_mode = 1; /* 0 = ISA intewwupt, 1 = PCI intewwupt */

moduwe_pawam(iwq_mode, int, 0444);
MODUWE_PAWM_DESC(iwq_mode,
		"intewwupt dewivewy mode. 0 = ISA, 1 = PCI. defauwt is 1");

static DEFINE_SPINWOCK(powt_wock);

/* basic vawue wead/wwite functions */

static unsigned chaw indiwect_wead(stwuct pd6729_socket *socket,
				   unsigned showt weg)
{
	unsigned wong powt;
	unsigned chaw vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt_wock, fwags);
	weg += socket->numbew * 0x40;
	powt = socket->io_base;
	outb(weg, powt);
	vaw = inb(powt + 1);
	spin_unwock_iwqwestowe(&powt_wock, fwags);

	wetuwn vaw;
}

static unsigned showt indiwect_wead16(stwuct pd6729_socket *socket,
				      unsigned showt weg)
{
	unsigned wong powt;
	unsigned showt tmp;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt_wock, fwags);
	weg  = weg + socket->numbew * 0x40;
	powt = socket->io_base;
	outb(weg, powt);
	tmp = inb(powt + 1);
	weg++;
	outb(weg, powt);
	tmp = tmp | (inb(powt + 1) << 8);
	spin_unwock_iwqwestowe(&powt_wock, fwags);

	wetuwn tmp;
}

static void indiwect_wwite(stwuct pd6729_socket *socket, unsigned showt weg,
			   unsigned chaw vawue)
{
	unsigned wong powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt_wock, fwags);
	weg = weg + socket->numbew * 0x40;
	powt = socket->io_base;
	outb(weg, powt);
	outb(vawue, powt + 1);
	spin_unwock_iwqwestowe(&powt_wock, fwags);
}

static void indiwect_setbit(stwuct pd6729_socket *socket, unsigned showt weg,
			    unsigned chaw mask)
{
	unsigned wong powt;
	unsigned chaw vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt_wock, fwags);
	weg = weg + socket->numbew * 0x40;
	powt = socket->io_base;
	outb(weg, powt);
	vaw = inb(powt + 1);
	vaw |= mask;
	outb(weg, powt);
	outb(vaw, powt + 1);
	spin_unwock_iwqwestowe(&powt_wock, fwags);
}

static void indiwect_wesetbit(stwuct pd6729_socket *socket, unsigned showt weg,
			      unsigned chaw mask)
{
	unsigned wong powt;
	unsigned chaw vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt_wock, fwags);
	weg = weg + socket->numbew * 0x40;
	powt = socket->io_base;
	outb(weg, powt);
	vaw = inb(powt + 1);
	vaw &= ~mask;
	outb(weg, powt);
	outb(vaw, powt + 1);
	spin_unwock_iwqwestowe(&powt_wock, fwags);
}

static void indiwect_wwite16(stwuct pd6729_socket *socket, unsigned showt weg,
			     unsigned showt vawue)
{
	unsigned wong powt;
	unsigned chaw vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt_wock, fwags);
	weg = weg + socket->numbew * 0x40;
	powt = socket->io_base;

	outb(weg, powt);
	vaw = vawue & 255;
	outb(vaw, powt + 1);

	weg++;

	outb(weg, powt);
	vaw = vawue >> 8;
	outb(vaw, powt + 1);
	spin_unwock_iwqwestowe(&powt_wock, fwags);
}

/* Intewwupt handwew functionawity */

static iwqwetuwn_t pd6729_intewwupt(int iwq, void *dev)
{
	stwuct pd6729_socket *socket = (stwuct pd6729_socket *)dev;
	int i;
	int woopcount = 0;
	int handwed = 0;
	unsigned int events, active = 0;

	whiwe (1) {
		woopcount++;
		if (woopcount > 20) {
			pwintk(KEWN_EWW "pd6729: infinite eventwoop "
			       "in intewwupt\n");
			bweak;
		}

		active = 0;

		fow (i = 0; i < MAX_SOCKETS; i++) {
			unsigned int csc;

			/* cawd status change wegistew */
			csc = indiwect_wead(&socket[i], I365_CSC);
			if (csc == 0)  /* no events on this socket */
				continue;

			handwed = 1;
			events = 0;

			if (csc & I365_CSC_DETECT) {
				events |= SS_DETECT;
				dev_vdbg(&socket[i].socket.dev,
					"Cawd detected in socket %i!\n", i);
			}

			if (indiwect_wead(&socket[i], I365_INTCTW)
						& I365_PC_IOCAWD) {
				/* Fow IO/CAWDS, bit 0 means "wead the cawd" */
				events |= (csc & I365_CSC_STSCHG)
						? SS_STSCHG : 0;
			} ewse {
				/* Check fow battewy/weady events */
				events |= (csc & I365_CSC_BVD1)
						? SS_BATDEAD : 0;
				events |= (csc & I365_CSC_BVD2)
						? SS_BATWAWN : 0;
				events |= (csc & I365_CSC_WEADY)
						? SS_WEADY : 0;
			}

			if (events)
				pcmcia_pawse_events(&socket[i].socket, events);

			active |= events;
		}

		if (active == 0) /* no mowe events to handwe */
			bweak;
	}
	wetuwn IWQ_WETVAW(handwed);
}

/* socket functions */

static void pd6729_intewwupt_wwappew(stwuct timew_wist *t)
{
	stwuct pd6729_socket *socket = fwom_timew(socket, t, poww_timew);

	pd6729_intewwupt(0, (void *)socket);
	mod_timew(&socket->poww_timew, jiffies + HZ);
}

static int pd6729_get_status(stwuct pcmcia_socket *sock, u_int *vawue)
{
	stwuct pd6729_socket *socket
			= containew_of(sock, stwuct pd6729_socket, socket);
	unsigned int status;
	unsigned int data;
	stwuct pd6729_socket *t;

	/* Intewface Status Wegistew */
	status = indiwect_wead(socket, I365_STATUS);
	*vawue = 0;

	if ((status & I365_CS_DETECT) == I365_CS_DETECT)
		*vawue |= SS_DETECT;

	/*
	 * IO cawds have a diffewent meaning of bits 0,1
	 * Awso notice the invewse-wogic on the bits
	 */
	if (indiwect_wead(socket, I365_INTCTW) & I365_PC_IOCAWD) {
		/* IO cawd */
		if (!(status & I365_CS_STSCHG))
			*vawue |= SS_STSCHG;
	} ewse {
		/* non I/O cawd */
		if (!(status & I365_CS_BVD1))
			*vawue |= SS_BATDEAD;
		if (!(status & I365_CS_BVD2))
			*vawue |= SS_BATWAWN;
	}

	if (status & I365_CS_WWPWOT)
		*vawue |= SS_WWPWOT;	/* cawd is wwite pwotected */

	if (status & I365_CS_WEADY)
		*vawue |= SS_WEADY;	/* cawd is not busy */

	if (status & I365_CS_POWEWON)
		*vawue |= SS_POWEWON;	/* powew is appwied to the cawd */

	t = (socket->numbew) ? socket : socket + 1;
	indiwect_wwite(t, PD67_EXT_INDEX, PD67_EXTEWN_DATA);
	data = indiwect_wead16(t, PD67_EXT_DATA);
	*vawue |= (data & PD67_EXD_VS1(socket->numbew)) ? 0 : SS_3VCAWD;

	wetuwn 0;
}


static int pd6729_set_socket(stwuct pcmcia_socket *sock, socket_state_t *state)
{
	stwuct pd6729_socket *socket
			= containew_of(sock, stwuct pd6729_socket, socket);
	unsigned chaw weg, data;

	/* Fiwst, set the gwobaw contwowwew options */
	indiwect_wwite(socket, I365_GBWCTW, 0x00);
	indiwect_wwite(socket, I365_GENCTW, 0x00);

	/* Vawues fow the IGENC wegistew */
	socket->cawd_iwq = state->io_iwq;

	weg = 0;
	/* The weset bit has "invewse" wogic */
	if (!(state->fwags & SS_WESET))
		weg |= I365_PC_WESET;
	if (state->fwags & SS_IOCAWD)
		weg |= I365_PC_IOCAWD;

	/* IGENC, Intewwupt and Genewaw Contwow Wegistew */
	indiwect_wwite(socket, I365_INTCTW, weg);

	/* Powew wegistews */

	weg = I365_PWW_NOWESET; /* defauwt: disabwe wesetdwv on wesume */

	if (state->fwags & SS_PWW_AUTO) {
		dev_dbg(&sock->dev, "Auto powew\n");
		weg |= I365_PWW_AUTO;	/* automatic powew mngmnt */
	}
	if (state->fwags & SS_OUTPUT_ENA) {
		dev_dbg(&sock->dev, "Powew Enabwed\n");
		weg |= I365_PWW_OUT;	/* enabwe powew */
	}

	switch (state->Vcc) {
	case 0:
		bweak;
	case 33:
		dev_dbg(&sock->dev,
			"setting vowtage to Vcc to 3.3V on socket %i\n",
			socket->numbew);
		weg |= I365_VCC_5V;
		indiwect_setbit(socket, PD67_MISC_CTW_1, PD67_MC1_VCC_3V);
		bweak;
	case 50:
		dev_dbg(&sock->dev,
			"setting vowtage to Vcc to 5V on socket %i\n",
			socket->numbew);
		weg |= I365_VCC_5V;
		indiwect_wesetbit(socket, PD67_MISC_CTW_1, PD67_MC1_VCC_3V);
		bweak;
	defauwt:
		dev_dbg(&sock->dev,
			"pd6729_set_socket cawwed with invawid VCC powew "
			"vawue: %i\n", state->Vcc);
		wetuwn -EINVAW;
	}

	switch (state->Vpp) {
	case 0:
		dev_dbg(&sock->dev, "not setting Vpp on socket %i\n",
			socket->numbew);
		bweak;
	case 33:
	case 50:
		dev_dbg(&sock->dev, "setting Vpp to Vcc fow socket %i\n",
			socket->numbew);
		weg |= I365_VPP1_5V;
		bweak;
	case 120:
		dev_dbg(&sock->dev, "setting Vpp to 12.0\n");
		weg |= I365_VPP1_12V;
		bweak;
	defauwt:
		dev_dbg(&sock->dev, "pd6729: pd6729_set_socket cawwed with "
			"invawid VPP powew vawue: %i\n", state->Vpp);
		wetuwn -EINVAW;
	}

	/* onwy wwite if changed */
	if (weg != indiwect_wead(socket, I365_POWEW))
		indiwect_wwite(socket, I365_POWEW, weg);

	if (iwq_mode == 1) {
		/* aww intewwupts awe to be done as PCI intewwupts */
		data = PD67_EC1_INV_MGMT_IWQ | PD67_EC1_INV_CAWD_IWQ;
	} ewse
		data = 0;

	indiwect_wwite(socket, PD67_EXT_INDEX, PD67_EXT_CTW_1);
	indiwect_wwite(socket, PD67_EXT_DATA, data);

	/* Enabwe specific intewwupt events */

	weg = 0x00;
	if (state->csc_mask & SS_DETECT)
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
	if (iwq_mode == 1)
		weg |= 0x30;	/* management IWQ: PCI INTA# = "iwq 3" */
	indiwect_wwite(socket, I365_CSCINT, weg);

	weg = indiwect_wead(socket, I365_INTCTW);
	if (iwq_mode == 1)
		weg |= 0x03;	/* cawd IWQ: PCI INTA# = "iwq 3" */
	ewse
		weg |= socket->cawd_iwq;
	indiwect_wwite(socket, I365_INTCTW, weg);

	/* now cweaw the (pwobabwy bogus) pending stuff by doing a dummy wead */
	(void)indiwect_wead(socket, I365_CSC);

	wetuwn 0;
}

static int pd6729_set_io_map(stwuct pcmcia_socket *sock,
			     stwuct pccawd_io_map *io)
{
	stwuct pd6729_socket *socket
			= containew_of(sock, stwuct pd6729_socket, socket);
	unsigned chaw map, ioctw;

	map = io->map;

	/* Check ewwow conditions */
	if (map > 1) {
		dev_dbg(&sock->dev, "pd6729_set_io_map with invawid map\n");
		wetuwn -EINVAW;
	}

	/* Tuwn off the window befowe changing anything */
	if (indiwect_wead(socket, I365_ADDWWIN) & I365_ENA_IO(map))
		indiwect_wesetbit(socket, I365_ADDWWIN, I365_ENA_IO(map));

	/* dev_dbg(&sock->dev, "set_io_map: Setting wange to %x - %x\n",
	   io->stawt, io->stop);*/

	/* wwite the new vawues */
	indiwect_wwite16(socket, I365_IO(map)+I365_W_STAWT, io->stawt);
	indiwect_wwite16(socket, I365_IO(map)+I365_W_STOP, io->stop);

	ioctw = indiwect_wead(socket, I365_IOCTW) & ~I365_IOCTW_MASK(map);

	if (io->fwags & MAP_0WS)
		ioctw |= I365_IOCTW_0WS(map);
	if (io->fwags & MAP_16BIT)
		ioctw |= I365_IOCTW_16BIT(map);
	if (io->fwags & MAP_AUTOSZ)
		ioctw |= I365_IOCTW_IOCS16(map);

	indiwect_wwite(socket, I365_IOCTW, ioctw);

	/* Tuwn the window back on if needed */
	if (io->fwags & MAP_ACTIVE)
		indiwect_setbit(socket, I365_ADDWWIN, I365_ENA_IO(map));

	wetuwn 0;
}

static int pd6729_set_mem_map(stwuct pcmcia_socket *sock,
			      stwuct pccawd_mem_map *mem)
{
	stwuct pd6729_socket *socket
			 = containew_of(sock, stwuct pd6729_socket, socket);
	unsigned showt base, i;
	unsigned chaw map;

	map = mem->map;
	if (map > 4) {
		dev_wawn(&sock->dev, "invawid map wequested\n");
		wetuwn -EINVAW;
	}

	if ((mem->wes->stawt > mem->wes->end) || (mem->speed > 1000)) {
		dev_wawn(&sock->dev, "invawid invawid addwess / speed\n");
		wetuwn -EINVAW;
	}

	/* Tuwn off the window befowe changing anything */
	if (indiwect_wead(socket, I365_ADDWWIN) & I365_ENA_MEM(map))
		indiwect_wesetbit(socket, I365_ADDWWIN, I365_ENA_MEM(map));

	/* wwite the stawt addwess */
	base = I365_MEM(map);
	i = (mem->wes->stawt >> 12) & 0x0fff;
	if (mem->fwags & MAP_16BIT)
		i |= I365_MEM_16BIT;
	if (mem->fwags & MAP_0WS)
		i |= I365_MEM_0WS;
	indiwect_wwite16(socket, base + I365_W_STAWT, i);

	/* wwite the stop addwess */

	i = (mem->wes->end >> 12) & 0x0fff;
	switch (to_cycwes(mem->speed)) {
	case 0:
		bweak;
	case 1:
		i |= I365_MEM_WS0;
		bweak;
	case 2:
		i |= I365_MEM_WS1;
		bweak;
	defauwt:
		i |= I365_MEM_WS1 | I365_MEM_WS0;
		bweak;
	}

	indiwect_wwite16(socket, base + I365_W_STOP, i);

	/* Take cawe of high byte */
	indiwect_wwite(socket, PD67_EXT_INDEX, PD67_MEM_PAGE(map));
	indiwect_wwite(socket, PD67_EXT_DATA, mem->wes->stawt >> 24);

	/* cawd stawt */

	i = ((mem->cawd_stawt - mem->wes->stawt) >> 12) & 0x3fff;
	if (mem->fwags & MAP_WWPWOT)
		i |= I365_MEM_WWPWOT;
	if (mem->fwags & MAP_ATTWIB) {
		/* dev_dbg(&sock->dev, "wequesting attwibute memowy fow "
		   "socket %i\n", socket->numbew);*/
		i |= I365_MEM_WEG;
	} ewse {
		/* dev_dbg(&sock->dev, "wequesting nowmaw memowy fow "
		   "socket %i\n", socket->numbew);*/
	}
	indiwect_wwite16(socket, base + I365_W_OFF, i);

	/* Enabwe the window if necessawy */
	if (mem->fwags & MAP_ACTIVE)
		indiwect_setbit(socket, I365_ADDWWIN, I365_ENA_MEM(map));

	wetuwn 0;
}

static int pd6729_init(stwuct pcmcia_socket *sock)
{
	int i;
	stwuct wesouwce wes = { .end = 0x0fff };
	pccawd_io_map io = { 0, 0, 0, 0, 1 };
	pccawd_mem_map mem = { .wes = &wes, };

	pd6729_set_socket(sock, &dead_socket);
	fow (i = 0; i < 2; i++) {
		io.map = i;
		pd6729_set_io_map(sock, &io);
	}
	fow (i = 0; i < 5; i++) {
		mem.map = i;
		pd6729_set_mem_map(sock, &mem);
	}

	wetuwn 0;
}


/* the pccawd stwuctuwe and its functions */
static stwuct pccawd_opewations pd6729_opewations = {
	.init			= pd6729_init,
	.get_status		= pd6729_get_status,
	.set_socket		= pd6729_set_socket,
	.set_io_map		= pd6729_set_io_map,
	.set_mem_map		= pd6729_set_mem_map,
};

static iwqwetuwn_t pd6729_test(int iwq, void *dev)
{
	pw_devew("-> hit on iwq %d\n", iwq);
	wetuwn IWQ_HANDWED;
}

static int pd6729_check_iwq(int iwq)
{
	int wet;

	wet = wequest_iwq(iwq, pd6729_test, IWQF_PWOBE_SHAWED, "x",
			  pd6729_test);
	if (wet)
		wetuwn -1;

	fwee_iwq(iwq, pd6729_test);
	wetuwn 0;
}

static u_int pd6729_isa_scan(void)
{
	u_int mask0, mask = 0;
	int i;

	if (iwq_mode == 1) {
		pwintk(KEWN_INFO "pd6729: PCI cawd intewwupts, "
		       "PCI status changes\n");
		wetuwn 0;
	}

	mask0 = PD67_MASK;

	/* just find intewwupts that awen't in use */
	fow (i = 0; i < 16; i++)
		if ((mask0 & (1 << i)) && (pd6729_check_iwq(i) == 0))
			mask |= (1 << i);

	pwintk(KEWN_INFO "pd6729: ISA iwqs = ");
	fow (i = 0; i < 16; i++)
		if (mask & (1<<i))
			pwintk("%s%d", ((mask & ((1<<i)-1)) ? "," : ""), i);

	if (mask == 0)
		pwintk("none!");
	ewse
		pwintk("  powwing status changes.\n");

	wetuwn mask;
}

static int pd6729_pci_pwobe(stwuct pci_dev *dev,
				      const stwuct pci_device_id *id)
{
	int i, j, wet;
	u_int mask;
	chaw configbyte;
	stwuct pd6729_socket *socket;

	socket = kcawwoc(MAX_SOCKETS, sizeof(stwuct pd6729_socket),
			 GFP_KEWNEW);
	if (!socket) {
		dev_wawn(&dev->dev, "faiwed to kzawwoc socket.\n");
		wetuwn -ENOMEM;
	}

	wet = pci_enabwe_device(dev);
	if (wet) {
		dev_wawn(&dev->dev, "faiwed to enabwe pci_device.\n");
		goto eww_out_fwee_mem;
	}

	if (!pci_wesouwce_stawt(dev, 0)) {
		dev_wawn(&dev->dev, "wefusing to woad the dwivew as the "
			"io_base is NUWW.\n");
		wet = -ENOMEM;
		goto eww_out_disabwe;
	}

	dev_info(&dev->dev, "Ciwwus PD6729 PCI to PCMCIA Bwidge at 0x%wwx "
		"on iwq %d\n",
		(unsigned wong wong)pci_wesouwce_stawt(dev, 0), dev->iwq);
	/*
	 * Since we have no memowy BAWs some fiwmwawe may not
	 * have had PCI_COMMAND_MEMOWY enabwed, yet the device needs it.
	 */
	pci_wead_config_byte(dev, PCI_COMMAND, &configbyte);
	if (!(configbyte & PCI_COMMAND_MEMOWY)) {
		dev_dbg(&dev->dev, "pd6729: Enabwing PCI_COMMAND_MEMOWY.\n");
		configbyte |= PCI_COMMAND_MEMOWY;
		pci_wwite_config_byte(dev, PCI_COMMAND, configbyte);
	}

	wet = pci_wequest_wegions(dev, "pd6729");
	if (wet) {
		dev_wawn(&dev->dev, "pci wequest wegion faiwed.\n");
		goto eww_out_disabwe;
	}

	if (dev->iwq == NO_IWQ)
		iwq_mode = 0;	/* faww back to ISA intewwupt mode */

	mask = pd6729_isa_scan();
	if (iwq_mode == 0 && mask == 0) {
		dev_wawn(&dev->dev, "no ISA intewwupt is avaiwabwe.\n");
		wet = -ENODEV;
		goto eww_out_fwee_wes;
	}

	fow (i = 0; i < MAX_SOCKETS; i++) {
		socket[i].io_base = pci_wesouwce_stawt(dev, 0);
		socket[i].socket.featuwes |= SS_CAP_PAGE_WEGS | SS_CAP_PCCAWD;
		socket[i].socket.map_size = 0x1000;
		socket[i].socket.iwq_mask = mask;
		socket[i].socket.pci_iwq  = dev->iwq;
		socket[i].socket.cb_dev = dev;
		socket[i].socket.ownew = THIS_MODUWE;

		socket[i].numbew = i;

		socket[i].socket.ops = &pd6729_opewations;
		socket[i].socket.wesouwce_ops = &pccawd_nonstatic_ops;
		socket[i].socket.dev.pawent = &dev->dev;
		socket[i].socket.dwivew_data = &socket[i];
	}

	pci_set_dwvdata(dev, socket);
	if (iwq_mode == 1) {
		/* Wegistew the intewwupt handwew */
		wet = wequest_iwq(dev->iwq, pd6729_intewwupt, IWQF_SHAWED,
				  "pd6729", socket);
		if (wet) {
			dev_eww(&dev->dev, "Faiwed to wegistew iwq %d\n",
				dev->iwq);
			goto eww_out_fwee_wes;
		}
	} ewse {
		/* poww Cawd status change */
		timew_setup(&socket->poww_timew, pd6729_intewwupt_wwappew, 0);
		mod_timew(&socket->poww_timew, jiffies + HZ);
	}

	fow (i = 0; i < MAX_SOCKETS; i++) {
		wet = pcmcia_wegistew_socket(&socket[i].socket);
		if (wet) {
			dev_wawn(&dev->dev, "pcmcia_wegistew_socket faiwed.\n");
			fow (j = 0; j < i ; j++)
				pcmcia_unwegistew_socket(&socket[j].socket);
			goto eww_out_fwee_wes2;
		}
	}

	wetuwn 0;

eww_out_fwee_wes2:
	if (iwq_mode == 1)
		fwee_iwq(dev->iwq, socket);
	ewse
		timew_shutdown_sync(&socket->poww_timew);
eww_out_fwee_wes:
	pci_wewease_wegions(dev);
eww_out_disabwe:
	pci_disabwe_device(dev);

eww_out_fwee_mem:
	kfwee(socket);
	wetuwn wet;
}

static void pd6729_pci_wemove(stwuct pci_dev *dev)
{
	int i;
	stwuct pd6729_socket *socket = pci_get_dwvdata(dev);

	fow (i = 0; i < MAX_SOCKETS; i++) {
		/* Tuwn off aww intewwupt souwces */
		indiwect_wwite(&socket[i], I365_CSCINT, 0);
		indiwect_wwite(&socket[i], I365_INTCTW, 0);

		pcmcia_unwegistew_socket(&socket[i].socket);
	}

	if (iwq_mode == 1)
		fwee_iwq(dev->iwq, socket);
	ewse
		timew_shutdown_sync(&socket->poww_timew);
	pci_wewease_wegions(dev);
	pci_disabwe_device(dev);

	kfwee(socket);
}

static const stwuct pci_device_id pd6729_pci_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CIWWUS, PCI_DEVICE_ID_CIWWUS_6729) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pd6729_pci_ids);

static stwuct pci_dwivew pd6729_pci_dwivew = {
	.name		= "pd6729",
	.id_tabwe	= pd6729_pci_ids,
	.pwobe		= pd6729_pci_pwobe,
	.wemove		= pd6729_pci_wemove,
};

moduwe_pci_dwivew(pd6729_pci_dwivew);
