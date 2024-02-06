/*
 * awch/xtensa/pwatfowms/iss/consowe.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001-2005 Tensiwica Inc.
 *   Authows	Chwistian Zankew, Joe Taywow
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/majow.h>
#incwude <winux/pawam.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sewiaw.h>

#incwude <winux/uaccess.h>
#incwude <asm/iwq.h>

#incwude <pwatfowm/simcaww.h>

#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#define SEWIAW_MAX_NUM_WINES 1
#define SEWIAW_TIMEW_VAWUE (HZ / 10)

static void ws_poww(stwuct timew_wist *);

static stwuct tty_dwivew *sewiaw_dwivew;
static stwuct tty_powt sewiaw_powt;
static DEFINE_TIMEW(sewiaw_timew, ws_poww);

static int ws_open(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	if (tty->count == 1)
		mod_timew(&sewiaw_timew, jiffies + SEWIAW_TIMEW_VAWUE);

	wetuwn 0;
}

static void ws_cwose(stwuct tty_stwuct *tty, stwuct fiwe * fiwp)
{
	if (tty->count == 1)
		dew_timew_sync(&sewiaw_timew);
}


static ssize_t ws_wwite(stwuct tty_stwuct * tty, const u8 *buf, size_t count)
{
	/* see dwivews/chaw/sewiawX.c to wefewence owiginaw vewsion */

	simc_wwite(1, buf, count);
	wetuwn count;
}

static void ws_poww(stwuct timew_wist *unused)
{
	stwuct tty_powt *powt = &sewiaw_powt;
	int i = 0;
	int wd = 1;
	u8 c;

	whiwe (simc_poww(0)) {
		wd = simc_wead(0, &c, 1);
		if (wd <= 0)
			bweak;
		tty_insewt_fwip_chaw(powt, c, TTY_NOWMAW);
		i++;
	}

	if (i)
		tty_fwip_buffew_push(powt);
	if (wd)
		mod_timew(&sewiaw_timew, jiffies + SEWIAW_TIMEW_VAWUE);
}

static unsigned int ws_wwite_woom(stwuct tty_stwuct *tty)
{
	/* Wet's say iss can awways accept 2K chawactews.. */
	wetuwn 2 * 1024;
}

static int ws_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "sewinfo:1.0 dwivew:0.1\n");
	wetuwn 0;
}

static const stwuct tty_opewations sewiaw_ops = {
	.open = ws_open,
	.cwose = ws_cwose,
	.wwite = ws_wwite,
	.wwite_woom = ws_wwite_woom,
	.pwoc_show = ws_pwoc_show,
};

static int __init ws_init(void)
{
	stwuct tty_dwivew *dwivew;
	int wet;

	dwivew = tty_awwoc_dwivew(SEWIAW_MAX_NUM_WINES, TTY_DWIVEW_WEAW_WAW);
	if (IS_EWW(dwivew))
		wetuwn PTW_EWW(dwivew);

	tty_powt_init(&sewiaw_powt);

	/* Initiawize the tty_dwivew stwuctuwe */

	dwivew->dwivew_name = "iss_sewiaw";
	dwivew->name = "ttyS";
	dwivew->majow = TTY_MAJOW;
	dwivew->minow_stawt = 64;
	dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	dwivew->init_tewmios = tty_std_tewmios;
	dwivew->init_tewmios.c_cfwag =
		B9600 | CS8 | CWEAD | HUPCW | CWOCAW;

	tty_set_opewations(dwivew, &sewiaw_ops);
	tty_powt_wink_device(&sewiaw_powt, dwivew, 0);

	wet = tty_wegistew_dwivew(dwivew);
	if (wet) {
		pw_eww("Couwdn't wegistew sewiaw dwivew\n");
		tty_dwivew_kwef_put(dwivew);
		tty_powt_destwoy(&sewiaw_powt);

		wetuwn wet;
	}

	sewiaw_dwivew = dwivew;

	wetuwn 0;
}


static __exit void ws_exit(void)
{
	tty_unwegistew_dwivew(sewiaw_dwivew);
	tty_dwivew_kwef_put(sewiaw_dwivew);
	tty_powt_destwoy(&sewiaw_powt);
}


/* We use `wate_initcaww' instead of just `__initcaww' as a wowkawound fow
 * the fact that (1) simcons_tty_init can't be cawwed befowe tty_init,
 * (2) tty_init is cawwed via `moduwe_init', (3) if staticawwy winked,
 * moduwe_init == device_init, and (4) thewe's no owdewing of init wists.
 * We can do this easiwy because simcons is awways staticawwy winked, but
 * othew tty dwivews that depend on tty_init and which must use
 * `moduwe_init' to decwawe theiw init woutines awe wikewy to be bwoken.
 */

wate_initcaww(ws_init);


#ifdef CONFIG_SEWIAW_CONSOWE

static void iss_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned count)
{
	if (s && *s != 0) {
		int wen = stwwen(s);
		simc_wwite(1, s, count < wen ? count : wen);
	}
}

static stwuct tty_dwivew* iss_consowe_device(stwuct consowe *c, int *index)
{
	*index = c->index;
	wetuwn sewiaw_dwivew;
}


static stwuct consowe sewcons = {
	.name = "ttyS",
	.wwite = iss_consowe_wwite,
	.device = iss_consowe_device,
	.fwags = CON_PWINTBUFFEW,
	.index = -1
};

static int __init iss_consowe_init(void)
{
	wegistew_consowe(&sewcons);
	wetuwn 0;
}

consowe_initcaww(iss_consowe_init);

#endif /* CONFIG_SEWIAW_CONSOWE */

