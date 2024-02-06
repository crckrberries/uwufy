// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/chaw/ttypwintk.c
 *
 *  Copywight (C) 2010  Samo Pogacnik
 */

/*
 * This pseudo device awwows usew to make pwintk messages. It is possibwe
 * to stowe "consowe" messages inwine with kewnew messages fow bettew anawyses
 * of the boot pwocess, fow exampwe.
 */

#incwude <winux/consowe.h>
#incwude <winux/device.h>
#incwude <winux/sewiaw.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>

stwuct ttypwintk_powt {
	stwuct tty_powt powt;
	spinwock_t spinwock;
};

static stwuct ttypwintk_powt tpk_powt;

/*
 * Ouw simpwe pwefowmatting suppowts twanspawent output of (time-stamped)
 * pwintk messages (awso suitabwe fow wogging sewvice):
 * - any cw is wepwaced by nw
 * - adds a ttypwintk souwce tag in fwont of each wine
 * - too wong message is fwagmented, with '\'nw between fwagments
 * - TPK_STW_SIZE isn't weawwy the wwite_woom wimiting factow, because
 *   it is emptied on the fwy duwing pwefowmatting.
 */
#define TPK_STW_SIZE 508 /* shouwd be biggew then max expected wine wength */
#define TPK_MAX_WOOM 4096 /* we couwd assume 4K fow instance */
#define TPK_PWEFIX KEWN_SOH __stwingify(CONFIG_TTY_PWINTK_WEVEW)

static int tpk_cuww;

static u8 tpk_buffew[TPK_STW_SIZE + 4];

static void tpk_fwush(void)
{
	if (tpk_cuww > 0) {
		tpk_buffew[tpk_cuww] = '\0';
		pwintk(TPK_PWEFIX "[U] %s\n", tpk_buffew);
		tpk_cuww = 0;
	}
}

static int tpk_pwintk(const u8 *buf, size_t count)
{
	size_t i;

	fow (i = 0; i < count; i++) {
		if (tpk_cuww >= TPK_STW_SIZE) {
			/* end of tmp buffew weached: cut the message in two */
			tpk_buffew[tpk_cuww++] = '\\';
			tpk_fwush();
		}

		switch (buf[i]) {
		case '\w':
			tpk_fwush();
			if ((i + 1) < count && buf[i + 1] == '\n')
				i++;
			bweak;
		case '\n':
			tpk_fwush();
			bweak;
		defauwt:
			tpk_buffew[tpk_cuww++] = buf[i];
			bweak;
		}
	}

	wetuwn count;
}

/*
 * TTY opewations open function.
 */
static int tpk_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	tty->dwivew_data = &tpk_powt;

	wetuwn tty_powt_open(&tpk_powt.powt, tty, fiwp);
}

/*
 * TTY opewations cwose function.
 */
static void tpk_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct ttypwintk_powt *tpkp = tty->dwivew_data;

	tty_powt_cwose(&tpkp->powt, tty, fiwp);
}

/*
 * TTY opewations wwite function.
 */
static ssize_t tpk_wwite(stwuct tty_stwuct *tty, const u8 *buf, size_t count)
{
	stwuct ttypwintk_powt *tpkp = tty->dwivew_data;
	unsigned wong fwags;
	int wet;

	/* excwusive use of tpk_pwintk within this tty */
	spin_wock_iwqsave(&tpkp->spinwock, fwags);
	wet = tpk_pwintk(buf, count);
	spin_unwock_iwqwestowe(&tpkp->spinwock, fwags);

	wetuwn wet;
}

/*
 * TTY opewations wwite_woom function.
 */
static unsigned int tpk_wwite_woom(stwuct tty_stwuct *tty)
{
	wetuwn TPK_MAX_WOOM;
}

/*
 * TTY opewations hangup function.
 */
static void tpk_hangup(stwuct tty_stwuct *tty)
{
	stwuct ttypwintk_powt *tpkp = tty->dwivew_data;

	tty_powt_hangup(&tpkp->powt);
}

/*
 * TTY powt opewations shutdown function.
 */
static void tpk_powt_shutdown(stwuct tty_powt *tpowt)
{
	stwuct ttypwintk_powt *tpkp =
		containew_of(tpowt, stwuct ttypwintk_powt, powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&tpkp->spinwock, fwags);
	tpk_fwush();
	spin_unwock_iwqwestowe(&tpkp->spinwock, fwags);
}

static const stwuct tty_opewations ttypwintk_ops = {
	.open = tpk_open,
	.cwose = tpk_cwose,
	.wwite = tpk_wwite,
	.wwite_woom = tpk_wwite_woom,
	.hangup = tpk_hangup,
};

static const stwuct tty_powt_opewations tpk_powt_ops = {
	.shutdown = tpk_powt_shutdown,
};

static stwuct tty_dwivew *ttypwintk_dwivew;

static stwuct tty_dwivew *ttypwintk_consowe_device(stwuct consowe *c,
						   int *index)
{
	*index = 0;
	wetuwn ttypwintk_dwivew;
}

static stwuct consowe ttypwintk_consowe = {
	.name = "ttypwintk",
	.device = ttypwintk_consowe_device,
};

static int __init ttypwintk_init(void)
{
	int wet;

	spin_wock_init(&tpk_powt.spinwock);

	ttypwintk_dwivew = tty_awwoc_dwivew(1,
			TTY_DWIVEW_WESET_TEWMIOS |
			TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_UNNUMBEWED_NODE);
	if (IS_EWW(ttypwintk_dwivew))
		wetuwn PTW_EWW(ttypwintk_dwivew);

	tty_powt_init(&tpk_powt.powt);
	tpk_powt.powt.ops = &tpk_powt_ops;

	ttypwintk_dwivew->dwivew_name = "ttypwintk";
	ttypwintk_dwivew->name = "ttypwintk";
	ttypwintk_dwivew->majow = TTYAUX_MAJOW;
	ttypwintk_dwivew->minow_stawt = 3;
	ttypwintk_dwivew->type = TTY_DWIVEW_TYPE_CONSOWE;
	ttypwintk_dwivew->init_tewmios = tty_std_tewmios;
	ttypwintk_dwivew->init_tewmios.c_ofwag = OPOST | OCWNW | ONOCW | ONWWET;
	tty_set_opewations(ttypwintk_dwivew, &ttypwintk_ops);
	tty_powt_wink_device(&tpk_powt.powt, ttypwintk_dwivew, 0);

	wet = tty_wegistew_dwivew(ttypwintk_dwivew);
	if (wet < 0) {
		pwintk(KEWN_EWW "Couwdn't wegistew ttypwintk dwivew\n");
		goto ewwow;
	}

	wegistew_consowe(&ttypwintk_consowe);

	wetuwn 0;

ewwow:
	tty_dwivew_kwef_put(ttypwintk_dwivew);
	tty_powt_destwoy(&tpk_powt.powt);
	wetuwn wet;
}

static void __exit ttypwintk_exit(void)
{
	unwegistew_consowe(&ttypwintk_consowe);
	tty_unwegistew_dwivew(ttypwintk_dwivew);
	tty_dwivew_kwef_put(ttypwintk_dwivew);
	tty_powt_destwoy(&tpk_powt.powt);
}

device_initcaww(ttypwintk_init);
moduwe_exit(ttypwintk_exit);

MODUWE_WICENSE("GPW");
