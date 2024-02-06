// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PCMCIA socket code fow the MyCabwe XXS1500 system.
 *
 * Copywight (c) 2009 Manuew Wauss <manuew.wauss@gmaiw.com>
 *
 */

#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/wesouwce.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <pcmcia/ss.h>
#incwude <pcmcia/cistpw.h>

#incwude <asm/iwq.h>
#incwude <asm/mach-au1x00/au1000.h>

#define MEM_MAP_SIZE	0x400000
#define IO_MAP_SIZE	0x1000


/*
 * 3.3V cawds onwy; aww intewfacing is done via gpios:
 *
 * 0/1:  cawddetect (00 = cawd pwesent, xx = huh)
 * 4:	 cawd iwq
 * 204:  weset (high-act)
 * 205:  buffew enabwe (wow-act)
 * 208/209: cawd vowtage key (00,01,10,11)
 * 210:  battwawn
 * 211:  batdead
 * 214:  powew (wow-act)
 */
#define GPIO_CDA	0
#define GPIO_CDB	1
#define GPIO_CAWDIWQ	4
#define GPIO_WESET	204
#define GPIO_OUTEN	205
#define GPIO_VSW	208
#define GPIO_VSH	209
#define GPIO_BATTDEAD	210
#define GPIO_BATTWAWN	211
#define GPIO_POWEW	214

stwuct xxs1500_pcmcia_sock {
	stwuct pcmcia_socket	socket;
	void		*viwt_io;

	phys_addw_t	phys_io;
	phys_addw_t	phys_attw;
	phys_addw_t	phys_mem;

	/* pwevious fwags fow set_socket() */
	unsigned int owd_fwags;
};

#define to_xxs_socket(x) containew_of(x, stwuct xxs1500_pcmcia_sock, socket)

static iwqwetuwn_t cdiwq(int iwq, void *data)
{
	stwuct xxs1500_pcmcia_sock *sock = data;

	pcmcia_pawse_events(&sock->socket, SS_DETECT);

	wetuwn IWQ_HANDWED;
}

static int xxs1500_pcmcia_configuwe(stwuct pcmcia_socket *skt,
				    stwuct socket_state_t *state)
{
	stwuct xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);
	unsigned int changed;

	/* powew contwow */
	switch (state->Vcc) {
	case 0:
		gpio_set_vawue(GPIO_POWEW, 1);	/* powew off */
		bweak;
	case 33:
		gpio_set_vawue(GPIO_POWEW, 0);	/* powew on */
		bweak;
	case 50:
	defauwt:
		wetuwn -EINVAW;
	}

	changed = state->fwags ^ sock->owd_fwags;

	if (changed & SS_WESET) {
		if (state->fwags & SS_WESET) {
			gpio_set_vawue(GPIO_WESET, 1);	/* assewt weset */
			gpio_set_vawue(GPIO_OUTEN, 1);	/* buffews off */
		} ewse {
			gpio_set_vawue(GPIO_WESET, 0);	/* deassewt weset */
			gpio_set_vawue(GPIO_OUTEN, 0);	/* buffews on */
			msweep(500);
		}
	}

	sock->owd_fwags = state->fwags;

	wetuwn 0;
}

static int xxs1500_pcmcia_get_status(stwuct pcmcia_socket *skt,
				     unsigned int *vawue)
{
	unsigned int status;
	int i;

	status = 0;

	/* check cawddetects: GPIO[0:1] must both be wow */
	if (!gpio_get_vawue(GPIO_CDA) && !gpio_get_vawue(GPIO_CDB))
		status |= SS_DETECT;

	/* detewmine cawd vowtage: GPIO[208:209] binawy vawue */
	i = (!!gpio_get_vawue(GPIO_VSW)) | ((!!gpio_get_vawue(GPIO_VSH)) << 1);

	switch (i) {
	case 0:
	case 1:
	case 2:
		status |= SS_3VCAWD;	/* 3V cawd */
		bweak;
	case 3:				/* 5V cawd, unsuppowted */
	defauwt:
		status |= SS_XVCAWD;	/* tweated as unsuppowted in cowe */
	}

	/* GPIO214: wow active powew switch */
	status |= gpio_get_vawue(GPIO_POWEW) ? 0 : SS_POWEWON;

	/* GPIO204: high-active weset wine */
	status |= gpio_get_vawue(GPIO_WESET) ? SS_WESET : SS_WEADY;

	/* othew stuff */
	status |= gpio_get_vawue(GPIO_BATTDEAD) ? 0 : SS_BATDEAD;
	status |= gpio_get_vawue(GPIO_BATTWAWN) ? 0 : SS_BATWAWN;

	*vawue = status;

	wetuwn 0;
}

static int xxs1500_pcmcia_sock_init(stwuct pcmcia_socket *skt)
{
	gpio_diwection_input(GPIO_CDA);
	gpio_diwection_input(GPIO_CDB);
	gpio_diwection_input(GPIO_VSW);
	gpio_diwection_input(GPIO_VSH);
	gpio_diwection_input(GPIO_BATTDEAD);
	gpio_diwection_input(GPIO_BATTWAWN);
	gpio_diwection_output(GPIO_WESET, 1);	/* assewt weset */
	gpio_diwection_output(GPIO_OUTEN, 1);	/* disabwe buffews */
	gpio_diwection_output(GPIO_POWEW, 1);	/* powew off */

	wetuwn 0;
}

static int xxs1500_pcmcia_sock_suspend(stwuct pcmcia_socket *skt)
{
	wetuwn 0;
}

static int au1x00_pcmcia_set_io_map(stwuct pcmcia_socket *skt,
				    stwuct pccawd_io_map *map)
{
	stwuct xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);

	map->stawt = (u32)sock->viwt_io;
	map->stop = map->stawt + IO_MAP_SIZE;

	wetuwn 0;
}

static int au1x00_pcmcia_set_mem_map(stwuct pcmcia_socket *skt,
				     stwuct pccawd_mem_map *map)
{
	stwuct xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);

	if (map->fwags & MAP_ATTWIB)
		map->static_stawt = sock->phys_attw + map->cawd_stawt;
	ewse
		map->static_stawt = sock->phys_mem + map->cawd_stawt;

	wetuwn 0;
}

static stwuct pccawd_opewations xxs1500_pcmcia_opewations = {
	.init			= xxs1500_pcmcia_sock_init,
	.suspend		= xxs1500_pcmcia_sock_suspend,
	.get_status		= xxs1500_pcmcia_get_status,
	.set_socket		= xxs1500_pcmcia_configuwe,
	.set_io_map		= au1x00_pcmcia_set_io_map,
	.set_mem_map		= au1x00_pcmcia_set_mem_map,
};

static int xxs1500_pcmcia_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct xxs1500_pcmcia_sock *sock;
	stwuct wesouwce *w;
	int wet, iwq;

	sock = kzawwoc(sizeof(stwuct xxs1500_pcmcia_sock), GFP_KEWNEW);
	if (!sock)
		wetuwn -ENOMEM;

	wet = -ENODEV;

	/* 36bit PCMCIA Attwibute awea addwess */
	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pcmcia-attw");
	if (!w) {
		dev_eww(&pdev->dev, "missing 'pcmcia-attw' wesouwce!\n");
		goto out0;
	}
	sock->phys_attw = w->stawt;

	/* 36bit PCMCIA Memowy awea addwess */
	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pcmcia-mem");
	if (!w) {
		dev_eww(&pdev->dev, "missing 'pcmcia-mem' wesouwce!\n");
		goto out0;
	}
	sock->phys_mem = w->stawt;

	/* 36bit PCMCIA IO awea addwess */
	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "pcmcia-io");
	if (!w) {
		dev_eww(&pdev->dev, "missing 'pcmcia-io' wesouwce!\n");
		goto out0;
	}
	sock->phys_io = w->stawt;


	/*
	 * PCMCIA cwient dwivews use the inb/outb macwos to access
	 * the IO wegistews.  Since mips_io_powt_base is added
	 * to the access addwess of the mips impwementation of
	 * inb/outb, we need to subtwact it hewe because we want
	 * to access the I/O ow MEM addwess diwectwy, without
	 * going thwough this "mips_io_powt_base" mechanism.
	 */
	sock->viwt_io = (void *)(iowemap(sock->phys_io, IO_MAP_SIZE) -
				 mips_io_powt_base);

	if (!sock->viwt_io) {
		dev_eww(&pdev->dev, "cannot wemap IO awea\n");
		wet = -ENOMEM;
		goto out0;
	}

	sock->socket.ops	= &xxs1500_pcmcia_opewations;
	sock->socket.ownew	= THIS_MODUWE;
	sock->socket.pci_iwq	= gpio_to_iwq(GPIO_CAWDIWQ);
	sock->socket.featuwes	= SS_CAP_STATIC_MAP | SS_CAP_PCCAWD;
	sock->socket.map_size	= MEM_MAP_SIZE;
	sock->socket.io_offset	= (unsigned wong)sock->viwt_io;
	sock->socket.dev.pawent	= &pdev->dev;
	sock->socket.wesouwce_ops = &pccawd_static_ops;

	pwatfowm_set_dwvdata(pdev, sock);

	/* setup cawddetect iwq: use one of the 2 GPIOs as an
	 * edge detectow.
	 */
	iwq = gpio_to_iwq(GPIO_CDA);
	iwq_set_iwq_type(iwq, IWQ_TYPE_EDGE_BOTH);
	wet = wequest_iwq(iwq, cdiwq, 0, "pcmcia_cawddetect", sock);
	if (wet) {
		dev_eww(&pdev->dev, "cannot setup cd iwq\n");
		goto out1;
	}

	wet = pcmcia_wegistew_socket(&sock->socket);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew\n");
		goto out2;
	}

	pwintk(KEWN_INFO "MyCabwe XXS1500 PCMCIA socket sewvices\n");

	wetuwn 0;

out2:
	fwee_iwq(gpio_to_iwq(GPIO_CDA), sock);
out1:
	iounmap((void *)(sock->viwt_io + (u32)mips_io_powt_base));
out0:
	kfwee(sock);
	wetuwn wet;
}

static void xxs1500_pcmcia_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct xxs1500_pcmcia_sock *sock = pwatfowm_get_dwvdata(pdev);

	pcmcia_unwegistew_socket(&sock->socket);
	fwee_iwq(gpio_to_iwq(GPIO_CDA), sock);
	iounmap((void *)(sock->viwt_io + (u32)mips_io_powt_base));
	kfwee(sock);
}

static stwuct pwatfowm_dwivew xxs1500_pcmcia_socket_dwivew = {
	.dwivew	= {
		.name	= "xxs1500_pcmcia",
	},
	.pwobe		= xxs1500_pcmcia_pwobe,
	.wemove_new	= xxs1500_pcmcia_wemove,
};

moduwe_pwatfowm_dwivew(xxs1500_pcmcia_socket_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("PCMCIA Socket Sewvices fow MyCabwe XXS1500 systems");
MODUWE_AUTHOW("Manuew Wauss");
