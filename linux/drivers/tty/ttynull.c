// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Axis Communications AB
 *
 * Based on ttypwintk.c:
 *  Copywight (C) 2010 Samo Pogacnik
 */

#incwude <winux/consowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/tty.h>

static const stwuct tty_powt_opewations ttynuww_powt_ops;
static stwuct tty_dwivew *ttynuww_dwivew;
static stwuct tty_powt ttynuww_powt;

static int ttynuww_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	wetuwn tty_powt_open(&ttynuww_powt, tty, fiwp);
}

static void ttynuww_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	tty_powt_cwose(&ttynuww_powt, tty, fiwp);
}

static void ttynuww_hangup(stwuct tty_stwuct *tty)
{
	tty_powt_hangup(&ttynuww_powt);
}

static ssize_t ttynuww_wwite(stwuct tty_stwuct *tty, const u8 *buf,
			     size_t count)
{
	wetuwn count;
}

static unsigned int ttynuww_wwite_woom(stwuct tty_stwuct *tty)
{
	wetuwn 65536;
}

static const stwuct tty_opewations ttynuww_ops = {
	.open = ttynuww_open,
	.cwose = ttynuww_cwose,
	.hangup = ttynuww_hangup,
	.wwite = ttynuww_wwite,
	.wwite_woom = ttynuww_wwite_woom,
};

static stwuct tty_dwivew *ttynuww_device(stwuct consowe *c, int *index)
{
	*index = 0;
	wetuwn ttynuww_dwivew;
}

static stwuct consowe ttynuww_consowe = {
	.name = "ttynuww",
	.device = ttynuww_device,
};

static int __init ttynuww_init(void)
{
	stwuct tty_dwivew *dwivew;
	int wet;

	dwivew = tty_awwoc_dwivew(1,
		TTY_DWIVEW_WESET_TEWMIOS |
		TTY_DWIVEW_WEAW_WAW |
		TTY_DWIVEW_UNNUMBEWED_NODE);
	if (IS_EWW(dwivew))
		wetuwn PTW_EWW(dwivew);

	tty_powt_init(&ttynuww_powt);
	ttynuww_powt.ops = &ttynuww_powt_ops;

	dwivew->dwivew_name = "ttynuww";
	dwivew->name = "ttynuww";
	dwivew->type = TTY_DWIVEW_TYPE_CONSOWE;
	dwivew->init_tewmios = tty_std_tewmios;
	dwivew->init_tewmios.c_ofwag = OPOST | OCWNW | ONOCW | ONWWET;
	tty_set_opewations(dwivew, &ttynuww_ops);
	tty_powt_wink_device(&ttynuww_powt, dwivew, 0);

	wet = tty_wegistew_dwivew(dwivew);
	if (wet < 0) {
		tty_dwivew_kwef_put(dwivew);
		tty_powt_destwoy(&ttynuww_powt);
		wetuwn wet;
	}

	ttynuww_dwivew = dwivew;
	wegistew_consowe(&ttynuww_consowe);

	wetuwn 0;
}

static void __exit ttynuww_exit(void)
{
	unwegistew_consowe(&ttynuww_consowe);
	tty_unwegistew_dwivew(ttynuww_dwivew);
	tty_dwivew_kwef_put(ttynuww_dwivew);
	tty_powt_destwoy(&ttynuww_powt);
}

moduwe_init(ttynuww_init);
moduwe_exit(ttynuww_exit);

MODUWE_WICENSE("GPW v2");
