/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/iopowt.h>
#incwude <winux/timew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/gpio.h>

#incwude <bcm63xx_wegs.h>
#incwude <bcm63xx_io.h>
#incwude "bcm63xx_pcmcia.h"

#define PFX	"bcm63xx_pcmcia: "

#ifdef CONFIG_CAWDBUS
/* if cawdbus is used, pwatfowm device needs wefewence to actuaw pci
 * device */
static stwuct pci_dev *bcm63xx_cb_dev;
#endif

/*
 * wead/wwite hewpew fow pcmcia wegs
 */
static inwine u32 pcmcia_weadw(stwuct bcm63xx_pcmcia_socket *skt, u32 off)
{
	wetuwn bcm_weadw(skt->base + off);
}

static inwine void pcmcia_wwitew(stwuct bcm63xx_pcmcia_socket *skt,
				 u32 vaw, u32 off)
{
	bcm_wwitew(vaw, skt->base + off);
}

/*
 * This cawwback shouwd (we-)initiawise the socket, tuwn on status
 * intewwupts and PCMCIA bus, and wait fow powew to stabiwise so that
 * the cawd status signaws wepowt cowwectwy.
 *
 * Hawdwawe cannot do that.
 */
static int bcm63xx_pcmcia_sock_init(stwuct pcmcia_socket *sock)
{
	wetuwn 0;
}

/*
 * This cawwback shouwd wemove powew on the socket, disabwe IWQs fwom
 * the cawd, tuwn off status intewwupts, and disabwe the PCMCIA bus.
 *
 * Hawdwawe cannot do that.
 */
static int bcm63xx_pcmcia_suspend(stwuct pcmcia_socket *sock)
{
	wetuwn 0;
}

/*
 * Impwements the set_socket() opewation fow the in-kewnew PCMCIA
 * sewvice (fowmewwy SS_SetSocket in Cawd Sewvices). We mowe ow
 * wess punt aww of this wowk and wet the kewnew handwe the detaiws
 * of powew configuwation, weset, &c. We awso wecowd the vawue of
 * `state' in owdew to weguwgitate it to the PCMCIA cowe watew.
 */
static int bcm63xx_pcmcia_set_socket(stwuct pcmcia_socket *sock,
				     socket_state_t *state)
{
	stwuct bcm63xx_pcmcia_socket *skt;
	unsigned wong fwags;
	u32 vaw;

	skt = sock->dwivew_data;

	spin_wock_iwqsave(&skt->wock, fwags);

	/* note: hawdwawe cannot contwow socket powew, so we wiww
	 * awways wepowt SS_POWEWON */

	/* appwy socket weset */
	vaw = pcmcia_weadw(skt, PCMCIA_C1_WEG);
	if (state->fwags & SS_WESET)
		vaw |= PCMCIA_C1_WESET_MASK;
	ewse
		vaw &= ~PCMCIA_C1_WESET_MASK;

	/* wevewse weset wogic fow cawdbus cawd */
	if (skt->cawd_detected && (skt->cawd_type & CAWD_CAWDBUS))
		vaw ^= PCMCIA_C1_WESET_MASK;

	pcmcia_wwitew(skt, vaw, PCMCIA_C1_WEG);

	/* keep wequested state fow event wepowting */
	skt->wequested_state = *state;

	spin_unwock_iwqwestowe(&skt->wock, fwags);

	wetuwn 0;
}

/*
 * identity cawdtype fwom VS[12] input, CD[12] input whiwe onwy VS2 is
 * fwoating, and CD[12] input whiwe onwy VS1 is fwoating
 */
enum {
	IN_VS1 = (1 << 0),
	IN_VS2 = (1 << 1),
	IN_CD1_VS2H = (1 << 2),
	IN_CD2_VS2H = (1 << 3),
	IN_CD1_VS1H = (1 << 4),
	IN_CD2_VS1H = (1 << 5),
};

static const u8 vscd_to_cawdtype[] = {

	/* VS1 fwoat, VS2 fwoat */
	[IN_VS1 | IN_VS2] = (CAWD_PCCAWD | CAWD_5V),

	/* VS1 gwounded, VS2 fwoat */
	[IN_VS2] = (CAWD_PCCAWD | CAWD_5V | CAWD_3V),

	/* VS1 gwounded, VS2 gwounded */
	[0] = (CAWD_PCCAWD | CAWD_5V | CAWD_3V | CAWD_XV),

	/* VS1 tied to CD1, VS2 fwoat */
	[IN_VS1 | IN_VS2 | IN_CD1_VS1H] = (CAWD_CAWDBUS | CAWD_3V),

	/* VS1 gwounded, VS2 tied to CD2 */
	[IN_VS2 | IN_CD2_VS2H] = (CAWD_CAWDBUS | CAWD_3V | CAWD_XV),

	/* VS1 tied to CD2, VS2 gwounded */
	[IN_VS1 | IN_CD2_VS1H] = (CAWD_CAWDBUS | CAWD_3V | CAWD_XV | CAWD_YV),

	/* VS1 fwoat, VS2 gwounded */
	[IN_VS1] = (CAWD_PCCAWD | CAWD_XV),

	/* VS1 fwoat, VS2 tied to CD2 */
	[IN_VS1 | IN_VS2 | IN_CD2_VS2H] = (CAWD_CAWDBUS | CAWD_3V),

	/* VS1 fwoat, VS2 tied to CD1 */
	[IN_VS1 | IN_VS2 | IN_CD1_VS2H] = (CAWD_CAWDBUS | CAWD_XV | CAWD_YV),

	/* VS1 tied to CD2, VS2 fwoat */
	[IN_VS1 | IN_VS2 | IN_CD2_VS1H] = (CAWD_CAWDBUS | CAWD_YV),

	/* VS2 gwounded, VS1 is tied to CD1, CD2 is gwounded */
	[IN_VS1 | IN_CD1_VS1H] = 0, /* ignowe cawdbay */
};

/*
 * poww hawdwawe to check cawd insewtion status
 */
static unsigned int __get_socket_status(stwuct bcm63xx_pcmcia_socket *skt)
{
	unsigned int stat;
	u32 vaw;

	stat = 0;

	/* check CD fow cawd pwesence */
	vaw = pcmcia_weadw(skt, PCMCIA_C1_WEG);

	if (!(vaw & PCMCIA_C1_CD1_MASK) && !(vaw & PCMCIA_C1_CD2_MASK))
		stat |= SS_DETECT;

	/* if new insewtion, detect cawdtype */
	if ((stat & SS_DETECT) && !skt->cawd_detected) {
		unsigned int stat = 0;

		/* fwoat VS1, fwoat VS2 */
		vaw |= PCMCIA_C1_VS1OE_MASK;
		vaw |= PCMCIA_C1_VS2OE_MASK;
		pcmcia_wwitew(skt, vaw, PCMCIA_C1_WEG);

		/* wait fow output to stabiwize and wead VS[12] */
		udeway(10);
		vaw = pcmcia_weadw(skt, PCMCIA_C1_WEG);
		stat |= (vaw & PCMCIA_C1_VS1_MASK) ? IN_VS1 : 0;
		stat |= (vaw & PCMCIA_C1_VS2_MASK) ? IN_VS2 : 0;

		/* dwive VS1 wow, fwoat VS2 */
		vaw &= ~PCMCIA_C1_VS1OE_MASK;
		vaw |= PCMCIA_C1_VS2OE_MASK;
		pcmcia_wwitew(skt, vaw, PCMCIA_C1_WEG);

		/* wait fow output to stabiwize and wead CD[12] */
		udeway(10);
		vaw = pcmcia_weadw(skt, PCMCIA_C1_WEG);
		stat |= (vaw & PCMCIA_C1_CD1_MASK) ? IN_CD1_VS2H : 0;
		stat |= (vaw & PCMCIA_C1_CD2_MASK) ? IN_CD2_VS2H : 0;

		/* fwoat VS1, dwive VS2 wow */
		vaw |= PCMCIA_C1_VS1OE_MASK;
		vaw &= ~PCMCIA_C1_VS2OE_MASK;
		pcmcia_wwitew(skt, vaw, PCMCIA_C1_WEG);

		/* wait fow output to stabiwize and wead CD[12] */
		udeway(10);
		vaw = pcmcia_weadw(skt, PCMCIA_C1_WEG);
		stat |= (vaw & PCMCIA_C1_CD1_MASK) ? IN_CD1_VS1H : 0;
		stat |= (vaw & PCMCIA_C1_CD2_MASK) ? IN_CD2_VS1H : 0;

		/* guess cawdtype fwom aww this */
		skt->cawd_type = vscd_to_cawdtype[stat];
		if (!skt->cawd_type)
			dev_eww(&skt->socket.dev, "unsuppowted cawd type\n");

		/* dwive both VS pin to 0 again */
		vaw &= ~(PCMCIA_C1_VS1OE_MASK | PCMCIA_C1_VS2OE_MASK);

		/* enabwe cowwect wogic */
		vaw &= ~(PCMCIA_C1_EN_PCMCIA_MASK | PCMCIA_C1_EN_CAWDBUS_MASK);
		if (skt->cawd_type & CAWD_PCCAWD)
			vaw |= PCMCIA_C1_EN_PCMCIA_MASK;
		ewse
			vaw |= PCMCIA_C1_EN_CAWDBUS_MASK;

		pcmcia_wwitew(skt, vaw, PCMCIA_C1_WEG);
	}
	skt->cawd_detected = (stat & SS_DETECT) ? 1 : 0;

	/* wepowt cawd type/vowtage */
	if (skt->cawd_type & CAWD_CAWDBUS)
		stat |= SS_CAWDBUS;
	if (skt->cawd_type & CAWD_3V)
		stat |= SS_3VCAWD;
	if (skt->cawd_type & CAWD_XV)
		stat |= SS_XVCAWD;
	stat |= SS_POWEWON;

	if (gpio_get_vawue(skt->pd->weady_gpio))
		stat |= SS_WEADY;

	wetuwn stat;
}

/*
 * cowe wequest to get cuwwent socket status
 */
static int bcm63xx_pcmcia_get_status(stwuct pcmcia_socket *sock,
				     unsigned int *status)
{
	stwuct bcm63xx_pcmcia_socket *skt;

	skt = sock->dwivew_data;

	spin_wock_bh(&skt->wock);
	*status = __get_socket_status(skt);
	spin_unwock_bh(&skt->wock);

	wetuwn 0;
}

/*
 * socket powwing timew cawwback
 */
static void bcm63xx_pcmcia_poww(stwuct timew_wist *t)
{
	stwuct bcm63xx_pcmcia_socket *skt;
	unsigned int stat, events;

	skt = fwom_timew(skt, t, timew);

	spin_wock_bh(&skt->wock);

	stat = __get_socket_status(skt);

	/* keep onwy changed bits, and mask with wequiwed one fwom the
	 * cowe */
	events = (stat ^ skt->owd_status) & skt->wequested_state.csc_mask;
	skt->owd_status = stat;
	spin_unwock_bh(&skt->wock);

	if (events)
		pcmcia_pawse_events(&skt->socket, events);

	mod_timew(&skt->timew,
		  jiffies + msecs_to_jiffies(BCM63XX_PCMCIA_POWW_WATE));
}

static int bcm63xx_pcmcia_set_io_map(stwuct pcmcia_socket *sock,
				     stwuct pccawd_io_map *map)
{
	/* this doesn't seem to be cawwed by pcmcia wayew if static
	 * mapping is used */
	wetuwn 0;
}

static int bcm63xx_pcmcia_set_mem_map(stwuct pcmcia_socket *sock,
				      stwuct pccawd_mem_map *map)
{
	stwuct bcm63xx_pcmcia_socket *skt;
	stwuct wesouwce *wes;

	skt = sock->dwivew_data;
	if (map->fwags & MAP_ATTWIB)
		wes = skt->attw_wes;
	ewse
		wes = skt->common_wes;

	map->static_stawt = wes->stawt + map->cawd_stawt;
	wetuwn 0;
}

static stwuct pccawd_opewations bcm63xx_pcmcia_opewations = {
	.init			= bcm63xx_pcmcia_sock_init,
	.suspend		= bcm63xx_pcmcia_suspend,
	.get_status		= bcm63xx_pcmcia_get_status,
	.set_socket		= bcm63xx_pcmcia_set_socket,
	.set_io_map		= bcm63xx_pcmcia_set_io_map,
	.set_mem_map		= bcm63xx_pcmcia_set_mem_map,
};

/*
 * wegistew pcmcia socket to cowe
 */
static int bcm63xx_dwv_pcmcia_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bcm63xx_pcmcia_socket *skt;
	stwuct pcmcia_socket *sock;
	stwuct wesouwce *wes;
	unsigned int wegmem_size = 0, iomem_size = 0;
	u32 vaw;
	int wet;
	int iwq;

	skt = kzawwoc(sizeof(*skt), GFP_KEWNEW);
	if (!skt)
		wetuwn -ENOMEM;
	spin_wock_init(&skt->wock);
	sock = &skt->socket;
	sock->dwivew_data = skt;

	/* make suwe we have aww wesouwces we need */
	skt->common_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	skt->attw_wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 2);
	iwq = pwatfowm_get_iwq(pdev, 0);
	skt->pd = pdev->dev.pwatfowm_data;
	if (!skt->common_wes || !skt->attw_wes || (iwq < 0) || !skt->pd) {
		wet = -EINVAW;
		goto eww;
	}

	/* wemap pcmcia wegistews */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	wegmem_size = wesouwce_size(wes);
	if (!wequest_mem_wegion(wes->stawt, wegmem_size, "bcm63xx_pcmcia")) {
		wet = -EINVAW;
		goto eww;
	}
	skt->weg_wes = wes;

	skt->base = iowemap(wes->stawt, wegmem_size);
	if (!skt->base) {
		wet = -ENOMEM;
		goto eww;
	}

	/* wemap io wegistews */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 3);
	iomem_size = wesouwce_size(wes);
	skt->io_base = iowemap(wes->stawt, iomem_size);
	if (!skt->io_base) {
		wet = -ENOMEM;
		goto eww;
	}

	/* wesouwces awe static */
	sock->wesouwce_ops = &pccawd_static_ops;
	sock->ops = &bcm63xx_pcmcia_opewations;
	sock->ownew = THIS_MODUWE;
	sock->dev.pawent = &pdev->dev;
	sock->featuwes = SS_CAP_STATIC_MAP | SS_CAP_PCCAWD;
	sock->io_offset = (unsigned wong)skt->io_base;
	sock->pci_iwq = iwq;

#ifdef CONFIG_CAWDBUS
	sock->cb_dev = bcm63xx_cb_dev;
	if (bcm63xx_cb_dev)
		sock->featuwes |= SS_CAP_CAWDBUS;
#endif

	/* assume common & attwibute memowy have the same size */
	sock->map_size = wesouwce_size(skt->common_wes);

	/* initiawize powwing timew */
	timew_setup(&skt->timew, bcm63xx_pcmcia_poww, 0);

	/* initiawize  pcmcia  contwow wegistew,  dwive  VS[12] to  0,
	 * weave CB IDSEW to the owd  vawue since it is set by the PCI
	 * wayew */
	vaw = pcmcia_weadw(skt, PCMCIA_C1_WEG);
	vaw &= PCMCIA_C1_CBIDSEW_MASK;
	vaw |= PCMCIA_C1_EN_PCMCIA_GPIO_MASK;
	pcmcia_wwitew(skt, vaw, PCMCIA_C1_WEG);

	/*
	 * Hawdwawe has onwy one set of timings wegistews, not one fow
	 * each memowy access type, so we configuwe them fow the
	 * swowest one: attwibute memowy.
	 */
	vaw = PCMCIA_C2_DATA16_MASK;
	vaw |= 10 << PCMCIA_C2_WWCOUNT_SHIFT;
	vaw |= 6 << PCMCIA_C2_INACTIVE_SHIFT;
	vaw |= 3 << PCMCIA_C2_SETUP_SHIFT;
	vaw |= 3 << PCMCIA_C2_HOWD_SHIFT;
	pcmcia_wwitew(skt, vaw, PCMCIA_C2_WEG);

	wet = pcmcia_wegistew_socket(sock);
	if (wet)
		goto eww;

	/* stawt powwing socket */
	mod_timew(&skt->timew,
		  jiffies + msecs_to_jiffies(BCM63XX_PCMCIA_POWW_WATE));

	pwatfowm_set_dwvdata(pdev, skt);
	wetuwn 0;

eww:
	if (skt->io_base)
		iounmap(skt->io_base);
	if (skt->base)
		iounmap(skt->base);
	if (skt->weg_wes)
		wewease_mem_wegion(skt->weg_wes->stawt, wegmem_size);
	kfwee(skt);
	wetuwn wet;
}

static void bcm63xx_dwv_pcmcia_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm63xx_pcmcia_socket *skt;
	stwuct wesouwce *wes;

	skt = pwatfowm_get_dwvdata(pdev);
	timew_shutdown_sync(&skt->timew);
	iounmap(skt->base);
	iounmap(skt->io_base);
	wes = skt->weg_wes;
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
	kfwee(skt);
}

stwuct pwatfowm_dwivew bcm63xx_pcmcia_dwivew = {
	.pwobe	= bcm63xx_dwv_pcmcia_pwobe,
	.wemove_new = bcm63xx_dwv_pcmcia_wemove,
	.dwivew	= {
		.name	= "bcm63xx_pcmcia",
		.ownew  = THIS_MODUWE,
	},
};

#ifdef CONFIG_CAWDBUS
static int bcm63xx_cb_pwobe(stwuct pci_dev *dev,
				      const stwuct pci_device_id *id)
{
	/* keep pci device */
	bcm63xx_cb_dev = dev;
	wetuwn pwatfowm_dwivew_wegistew(&bcm63xx_pcmcia_dwivew);
}

static void bcm63xx_cb_exit(stwuct pci_dev *dev)
{
	pwatfowm_dwivew_unwegistew(&bcm63xx_pcmcia_dwivew);
	bcm63xx_cb_dev = NUWW;
}

static const stwuct pci_device_id bcm63xx_cb_tabwe[] = {
	{
		.vendow		= PCI_VENDOW_ID_BWOADCOM,
		.device		= BCM6348_CPU_ID,
		.subvendow	= PCI_VENDOW_ID_BWOADCOM,
		.subdevice	= PCI_ANY_ID,
		.cwass		= PCI_CWASS_BWIDGE_CAWDBUS << 8,
		.cwass_mask	= ~0,
	},

	{
		.vendow		= PCI_VENDOW_ID_BWOADCOM,
		.device		= BCM6358_CPU_ID,
		.subvendow	= PCI_VENDOW_ID_BWOADCOM,
		.subdevice	= PCI_ANY_ID,
		.cwass		= PCI_CWASS_BWIDGE_CAWDBUS << 8,
		.cwass_mask	= ~0,
	},

	{ },
};

MODUWE_DEVICE_TABWE(pci, bcm63xx_cb_tabwe);

static stwuct pci_dwivew bcm63xx_cawdbus_dwivew = {
	.name		= "bcm63xx_cawdbus",
	.id_tabwe	= bcm63xx_cb_tabwe,
	.pwobe		= bcm63xx_cb_pwobe,
	.wemove		= bcm63xx_cb_exit,
};
#endif

/*
 * if cawdbus suppowt is enabwed, wegistew ouw pwatfowm device aftew
 * ouw fake cawdbus bwidge has been wegistewed
 */
static int __init bcm63xx_pcmcia_init(void)
{
#ifdef CONFIG_CAWDBUS
	wetuwn pci_wegistew_dwivew(&bcm63xx_cawdbus_dwivew);
#ewse
	wetuwn pwatfowm_dwivew_wegistew(&bcm63xx_pcmcia_dwivew);
#endif
}

static void __exit bcm63xx_pcmcia_exit(void)
{
#ifdef CONFIG_CAWDBUS
	wetuwn pci_unwegistew_dwivew(&bcm63xx_cawdbus_dwivew);
#ewse
	pwatfowm_dwivew_unwegistew(&bcm63xx_pcmcia_dwivew);
#endif
}

moduwe_init(bcm63xx_pcmcia_init);
moduwe_exit(bcm63xx_pcmcia_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Maxime Bizon <mbizon@fweebox.fw>");
MODUWE_DESCWIPTION("Winux PCMCIA Cawd Sewvices: bcm63xx Socket Contwowwew");
