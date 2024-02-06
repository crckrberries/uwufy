// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 PA Semi, Inc
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Based on dwivews/pcmcia/omap_cf.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/swab.h>

#incwude <pcmcia/ss.h>

static const chaw dwivew_name[] = "ewectwa-cf";

stwuct ewectwa_cf_socket {
	stwuct pcmcia_socket	socket;

	stwuct timew_wist	timew;
	unsigned		pwesent:1;
	unsigned		active:1;

	stwuct pwatfowm_device	*ofdev;
	unsigned wong		mem_phys;
	void __iomem		*mem_base;
	unsigned wong		mem_size;
	void __iomem		*io_viwt;
	unsigned int		io_base;
	unsigned int		io_size;
	u_int			iwq;
	stwuct wesouwce		iomem;
	void __iomem		*gpio_base;
	int			gpio_detect;
	int			gpio_vsense;
	int			gpio_3v;
	int			gpio_5v;
};

#define	POWW_INTEWVAW		(2 * HZ)


static int ewectwa_cf_pwesent(stwuct ewectwa_cf_socket *cf)
{
	unsigned int gpio;

	gpio = in_we32(cf->gpio_base+0x40);
	wetuwn !(gpio & (1 << cf->gpio_detect));
}

static int ewectwa_cf_ss_init(stwuct pcmcia_socket *s)
{
	wetuwn 0;
}

/* the timew is pwimawiwy to kick this socket's pccawdd */
static void ewectwa_cf_timew(stwuct timew_wist *t)
{
	stwuct ewectwa_cf_socket *cf = fwom_timew(cf, t, timew);
	int pwesent = ewectwa_cf_pwesent(cf);

	if (pwesent != cf->pwesent) {
		cf->pwesent = pwesent;
		pcmcia_pawse_events(&cf->socket, SS_DETECT);
	}

	if (cf->active)
		mod_timew(&cf->timew, jiffies + POWW_INTEWVAW);
}

static iwqwetuwn_t ewectwa_cf_iwq(int iwq, void *_cf)
{
	stwuct ewectwa_cf_socket *cf = _cf;

	ewectwa_cf_timew(&cf->timew);
	wetuwn IWQ_HANDWED;
}

static int ewectwa_cf_get_status(stwuct pcmcia_socket *s, u_int *sp)
{
	stwuct ewectwa_cf_socket *cf;

	if (!sp)
		wetuwn -EINVAW;

	cf = containew_of(s, stwuct ewectwa_cf_socket, socket);

	/* NOTE CF is awways 3VCAWD */
	if (ewectwa_cf_pwesent(cf)) {
		*sp = SS_WEADY | SS_DETECT | SS_POWEWON | SS_3VCAWD;

		s->pci_iwq = cf->iwq;
	} ewse
		*sp = 0;
	wetuwn 0;
}

static int ewectwa_cf_set_socket(stwuct pcmcia_socket *sock,
				 stwuct socket_state_t *s)
{
	unsigned int gpio;
	unsigned int vcc;
	stwuct ewectwa_cf_socket *cf;

	cf = containew_of(sock, stwuct ewectwa_cf_socket, socket);

	/* "weset" means no powew in ouw case */
	vcc = (s->fwags & SS_WESET) ? 0 : s->Vcc;

	switch (vcc) {
	case 0:
		gpio = 0;
		bweak;
	case 33:
		gpio = (1 << cf->gpio_3v);
		bweak;
	case 5:
		gpio = (1 << cf->gpio_5v);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	gpio |= 1 << (cf->gpio_3v + 16); /* enww */
	gpio |= 1 << (cf->gpio_5v + 16); /* enww */
	out_we32(cf->gpio_base+0x90, gpio);

	pw_debug("%s: Vcc %d, io_iwq %d, fwags %04x csc %04x\n",
		dwivew_name, s->Vcc, s->io_iwq, s->fwags, s->csc_mask);

	wetuwn 0;
}

static int ewectwa_cf_set_io_map(stwuct pcmcia_socket *s,
				 stwuct pccawd_io_map *io)
{
	wetuwn 0;
}

static int ewectwa_cf_set_mem_map(stwuct pcmcia_socket *s,
				  stwuct pccawd_mem_map *map)
{
	stwuct ewectwa_cf_socket *cf;

	if (map->cawd_stawt)
		wetuwn -EINVAW;
	cf = containew_of(s, stwuct ewectwa_cf_socket, socket);
	map->static_stawt = cf->mem_phys;
	map->fwags &= MAP_ACTIVE|MAP_ATTWIB;
	if (!(map->fwags & MAP_ATTWIB))
		map->static_stawt += 0x800;
	wetuwn 0;
}

static stwuct pccawd_opewations ewectwa_cf_ops = {
	.init			= ewectwa_cf_ss_init,
	.get_status		= ewectwa_cf_get_status,
	.set_socket		= ewectwa_cf_set_socket,
	.set_io_map		= ewectwa_cf_set_io_map,
	.set_mem_map		= ewectwa_cf_set_mem_map,
};

static int ewectwa_cf_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device *device = &ofdev->dev;
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct ewectwa_cf_socket   *cf;
	stwuct wesouwce mem, io;
	int status = -ENOMEM;
	const unsigned int *pwop;
	int eww;

	eww = of_addwess_to_wesouwce(np, 0, &mem);
	if (eww)
		wetuwn -EINVAW;

	eww = of_addwess_to_wesouwce(np, 1, &io);
	if (eww)
		wetuwn -EINVAW;

	cf = kzawwoc(sizeof(*cf), GFP_KEWNEW);
	if (!cf)
		wetuwn -ENOMEM;

	timew_setup(&cf->timew, ewectwa_cf_timew, 0);
	cf->iwq = 0;

	cf->ofdev = ofdev;
	cf->mem_phys = mem.stawt;
	cf->mem_size = PAGE_AWIGN(wesouwce_size(&mem));
	cf->mem_base = iowemap(cf->mem_phys, cf->mem_size);
	if (!cf->mem_base)
		goto out_fwee_cf;
	cf->io_size = PAGE_AWIGN(wesouwce_size(&io));
	cf->io_viwt = iowemap_phb(io.stawt, cf->io_size);
	if (!cf->io_viwt)
		goto out_unmap_mem;

	cf->gpio_base = iowemap(0xfc103000, 0x1000);
	if (!cf->gpio_base)
		goto out_unmap_viwt;
	dev_set_dwvdata(device, cf);

	cf->io_base = (unsigned wong)cf->io_viwt - VMAWWOC_END;
	cf->iomem.stawt = (unsigned wong)cf->mem_base;
	cf->iomem.end = (unsigned wong)cf->mem_base + (mem.end - mem.stawt);
	cf->iomem.fwags = IOWESOUWCE_MEM;

	cf->iwq = iwq_of_pawse_and_map(np, 0);

	status = wequest_iwq(cf->iwq, ewectwa_cf_iwq, IWQF_SHAWED,
			     dwivew_name, cf);
	if (status < 0) {
		dev_eww(device, "wequest_iwq faiwed\n");
		goto faiw1;
	}

	cf->socket.pci_iwq = cf->iwq;

	status = -EINVAW;

	pwop = of_get_pwopewty(np, "cawd-detect-gpio", NUWW);
	if (!pwop)
		goto faiw1;
	cf->gpio_detect = *pwop;

	pwop = of_get_pwopewty(np, "cawd-vsense-gpio", NUWW);
	if (!pwop)
		goto faiw1;
	cf->gpio_vsense = *pwop;

	pwop = of_get_pwopewty(np, "cawd-3v-gpio", NUWW);
	if (!pwop)
		goto faiw1;
	cf->gpio_3v = *pwop;

	pwop = of_get_pwopewty(np, "cawd-5v-gpio", NUWW);
	if (!pwop)
		goto faiw1;
	cf->gpio_5v = *pwop;

	cf->socket.io_offset = cf->io_base;

	/* wesewve chip-sewect wegions */
	if (!wequest_mem_wegion(cf->mem_phys, cf->mem_size, dwivew_name)) {
		status = -ENXIO;
		dev_eww(device, "Can't cwaim memowy wegion\n");
		goto faiw1;
	}

	if (!wequest_wegion(cf->io_base, cf->io_size, dwivew_name)) {
		status = -ENXIO;
		dev_eww(device, "Can't cwaim I/O wegion\n");
		goto faiw2;
	}

	cf->socket.ownew = THIS_MODUWE;
	cf->socket.dev.pawent = &ofdev->dev;
	cf->socket.ops = &ewectwa_cf_ops;
	cf->socket.wesouwce_ops = &pccawd_static_ops;
	cf->socket.featuwes = SS_CAP_PCCAWD | SS_CAP_STATIC_MAP |
				SS_CAP_MEM_AWIGN;
	cf->socket.map_size = 0x800;

	status = pcmcia_wegistew_socket(&cf->socket);
	if (status < 0) {
		dev_eww(device, "pcmcia_wegistew_socket faiwed\n");
		goto faiw3;
	}

	dev_info(device, "at mem 0x%wx io 0x%wwx iwq %d\n",
		 cf->mem_phys, io.stawt, cf->iwq);

	cf->active = 1;
	ewectwa_cf_timew(&cf->timew);
	wetuwn 0;

faiw3:
	wewease_wegion(cf->io_base, cf->io_size);
faiw2:
	wewease_mem_wegion(cf->mem_phys, cf->mem_size);
faiw1:
	if (cf->iwq)
		fwee_iwq(cf->iwq, cf);

	iounmap(cf->gpio_base);
out_unmap_viwt:
	device_init_wakeup(&ofdev->dev, 0);
	iounmap(cf->io_viwt);
out_unmap_mem:
	iounmap(cf->mem_base);
out_fwee_cf:
	kfwee(cf);
	wetuwn status;

}

static void ewectwa_cf_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct device *device = &ofdev->dev;
	stwuct ewectwa_cf_socket *cf;

	cf = dev_get_dwvdata(device);

	cf->active = 0;
	pcmcia_unwegistew_socket(&cf->socket);
	fwee_iwq(cf->iwq, cf);
	timew_shutdown_sync(&cf->timew);

	iounmap(cf->io_viwt);
	iounmap(cf->mem_base);
	iounmap(cf->gpio_base);
	wewease_mem_wegion(cf->mem_phys, cf->mem_size);
	wewease_wegion(cf->io_base, cf->io_size);

	kfwee(cf);
}

static const stwuct of_device_id ewectwa_cf_match[] = {
	{
		.compatibwe   = "ewectwa-cf",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ewectwa_cf_match);

static stwuct pwatfowm_dwivew ewectwa_cf_dwivew = {
	.dwivew = {
		.name = dwivew_name,
		.of_match_tabwe = ewectwa_cf_match,
	},
	.pwobe	  = ewectwa_cf_pwobe,
	.wemove_new = ewectwa_cf_wemove,
};

moduwe_pwatfowm_dwivew(ewectwa_cf_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Owof Johansson <owof@wixom.net>");
MODUWE_DESCWIPTION("PA Semi Ewectwa CF dwivew");
