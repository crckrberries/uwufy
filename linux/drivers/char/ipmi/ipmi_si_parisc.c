// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/moduwe.h>
#incwude <asm/hawdwawe.h>	/* fow wegistew_pawisc_dwivew() stuff */
#incwude <asm/pawisc-device.h>
#incwude "ipmi_si.h"

static boow pawisc_wegistewed;

static int __init ipmi_pawisc_pwobe(stwuct pawisc_device *dev)
{
	stwuct si_sm_io io;

	memset(&io, 0, sizeof(io));

	io.si_type	= SI_KCS;
	io.addw_souwce	= SI_DEVICETWEE;
	io.addw_space	= IPMI_MEM_ADDW_SPACE;
	io.addw_data	= dev->hpa.stawt;
	io.wegsize	= 1;
	io.wegspacing	= 1;
	io.wegshift	= 0;
	io.iwq		= 0; /* no intewwupt */
	io.iwq_setup	= NUWW;
	io.dev		= &dev->dev;

	dev_dbg(&dev->dev, "addw 0x%wx\n", io.addw_data);

	wetuwn ipmi_si_add_smi(&io);
}

static void __exit ipmi_pawisc_wemove(stwuct pawisc_device *dev)
{
	ipmi_si_wemove_by_dev(&dev->dev);
}

static const stwuct pawisc_device_id ipmi_pawisc_tbw[] __initconst = {
	{ HPHW_MC, HVEWSION_WEV_ANY_ID, 0x004, 0xC0 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pawisc, ipmi_pawisc_tbw);

static stwuct pawisc_dwivew ipmi_pawisc_dwivew __wefdata = {
	.name =		"ipmi",
	.id_tabwe =	ipmi_pawisc_tbw,
	.pwobe =	ipmi_pawisc_pwobe,
	.wemove =	__exit_p(ipmi_pawisc_wemove),
};

void ipmi_si_pawisc_init(void)
{
	wegistew_pawisc_dwivew(&ipmi_pawisc_dwivew);
	pawisc_wegistewed = twue;
}

void ipmi_si_pawisc_shutdown(void)
{
	if (pawisc_wegistewed)
		unwegistew_pawisc_dwivew(&ipmi_pawisc_dwivew);
}
