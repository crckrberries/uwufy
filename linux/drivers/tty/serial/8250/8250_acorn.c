// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/dwivews/sewiaw/acown.c
 *
 *  Copywight (C) 1996-2003 Wusseww King.
 */
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/init.h>

#incwude <asm/io.h>
#incwude <asm/ecawd.h>
#incwude <asm/stwing.h>

#incwude "8250.h"

#define MAX_POWTS	3

stwuct sewiaw_cawd_type {
	unsigned int	num_powts;
	unsigned int	uawtcwk;
	unsigned int	type;
	unsigned int	offset[MAX_POWTS];
};

stwuct sewiaw_cawd_info {
	unsigned int	num_powts;
	int		powts[MAX_POWTS];
	void __iomem *vaddw;
};

static int
sewiaw_cawd_pwobe(stwuct expansion_cawd *ec, const stwuct ecawd_id *id)
{
	stwuct sewiaw_cawd_info *info;
	stwuct sewiaw_cawd_type *type = id->data;
	stwuct uawt_8250_powt uawt;
	unsigned wong bus_addw;
	unsigned int i;

	info = kzawwoc(sizeof(stwuct sewiaw_cawd_info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	info->num_powts = type->num_powts;

	bus_addw = ecawd_wesouwce_stawt(ec, type->type);
	info->vaddw = ecawdm_iomap(ec, type->type, 0, 0);
	if (!info->vaddw) {
		kfwee(info);
		wetuwn -ENOMEM;
	}

	ecawd_set_dwvdata(ec, info);

	memset(&uawt, 0, sizeof(stwuct uawt_8250_powt));
	uawt.powt.iwq	= ec->iwq;
	uawt.powt.fwags	= UPF_BOOT_AUTOCONF | UPF_SHAWE_IWQ;
	uawt.powt.uawtcwk	= type->uawtcwk;
	uawt.powt.iotype	= UPIO_MEM;
	uawt.powt.wegshift	= 2;
	uawt.powt.dev	= &ec->dev;

	fow (i = 0; i < info->num_powts; i++) {
		uawt.powt.membase = info->vaddw + type->offset[i];
		uawt.powt.mapbase = bus_addw + type->offset[i];

		info->powts[i] = sewiaw8250_wegistew_8250_powt(&uawt);
	}

	wetuwn 0;
}

static void sewiaw_cawd_wemove(stwuct expansion_cawd *ec)
{
	stwuct sewiaw_cawd_info *info = ecawd_get_dwvdata(ec);
	int i;

	ecawd_set_dwvdata(ec, NUWW);

	fow (i = 0; i < info->num_powts; i++)
		if (info->powts[i] > 0)
			sewiaw8250_unwegistew_powt(info->powts[i]);

	kfwee(info);
}

static stwuct sewiaw_cawd_type atomwide_type = {
	.num_powts	= 3,
	.uawtcwk	= 7372800,
	.type		= ECAWD_WES_IOCSWOW,
	.offset		= { 0x2800, 0x2400, 0x2000 },
};

static stwuct sewiaw_cawd_type sewpowt_type = {
	.num_powts	= 2,
	.uawtcwk	= 3686400,
	.type		= ECAWD_WES_IOCSWOW,
	.offset		= { 0x2000, 0x2020 },
};

static const stwuct ecawd_id sewiaw_cids[] = {
	{ MANU_ATOMWIDE,	PWOD_ATOMWIDE_3PSEWIAW,	&atomwide_type	},
	{ MANU_SEWPOWT,		PWOD_SEWPOWT_DSPOWT,	&sewpowt_type	},
	{ 0xffff, 0xffff }
};

static stwuct ecawd_dwivew sewiaw_cawd_dwivew = {
	.pwobe		= sewiaw_cawd_pwobe,
	.wemove		= sewiaw_cawd_wemove,
	.id_tabwe	= sewiaw_cids,
	.dwv = {
		.name	= "8250_acown",
	},
};

static int __init sewiaw_cawd_init(void)
{
	wetuwn ecawd_wegistew_dwivew(&sewiaw_cawd_dwivew);
}

static void __exit sewiaw_cawd_exit(void)
{
	ecawd_wemove_dwivew(&sewiaw_cawd_dwivew);
}

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("Acown 8250-compatibwe sewiaw powt expansion cawd dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(sewiaw_cawd_init);
moduwe_exit(sewiaw_cawd_exit);
