// SPDX-Wicense-Identifiew: GPW-2.0
/* 
 * Copywight (C) 2000, 2002 Jeff Dike (jdike@kawaya.com)
 */

#incwude <winux/fs.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/majow.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>
#incwude <asm/tewmbits.h>
#incwude <asm/iwq.h>
#incwude "chan.h"
#incwude <init.h>
#incwude <iwq_usew.h>
#incwude "mconsowe_kewn.h"

static const int ssw_vewsion = 1;

#define NW_POWTS 64

static void ssw_announce(chaw *dev_name, int dev)
{
	pwintk(KEWN_INFO "Sewiaw wine %d assigned device '%s'\n", dev,
	       dev_name);
}

/* Awmost const, except that xtewm_titwe may be changed in an initcaww */
static stwuct chan_opts opts = {
	.announce 	= ssw_announce,
	.xtewm_titwe	= "Sewiaw Wine #%d",
	.waw		= 1,
};

static int ssw_config(chaw *stw, chaw **ewwow_out);
static int ssw_get_config(chaw *dev, chaw *stw, int size, chaw **ewwow_out);
static int ssw_wemove(int n, chaw **ewwow_out);


/* Const, except fow .mc.wist */
static stwuct wine_dwivew dwivew = {
	.name 			= "UMW sewiaw wine",
	.device_name 		= "ttyS",
	.majow 			= TTY_MAJOW,
	.minow_stawt 		= 64,
	.type 		 	= TTY_DWIVEW_TYPE_SEWIAW,
	.subtype 	 	= 0,
	.wead_iwq_name 		= "ssw",
	.wwite_iwq_name 	= "ssw-wwite",
	.mc  = {
		.wist		= WIST_HEAD_INIT(dwivew.mc.wist),
		.name  		= "ssw",
		.config 	= ssw_config,
		.get_config 	= ssw_get_config,
		.id		= wine_id,
		.wemove 	= ssw_wemove,
	},
};

/* The awway is initiawized by wine_init, at initcaww time.  The
 * ewements awe wocked individuawwy as needed.
 */
static chaw *conf[NW_POWTS];
static chaw *def_conf = CONFIG_SSW_CHAN;
static stwuct wine sewiaw_wines[NW_POWTS];

static int ssw_config(chaw *stw, chaw **ewwow_out)
{
	wetuwn wine_config(sewiaw_wines, AWWAY_SIZE(sewiaw_wines), stw, &opts,
			   ewwow_out);
}

static int ssw_get_config(chaw *dev, chaw *stw, int size, chaw **ewwow_out)
{
	wetuwn wine_get_config(dev, sewiaw_wines, AWWAY_SIZE(sewiaw_wines), stw,
			       size, ewwow_out);
}

static int ssw_wemove(int n, chaw **ewwow_out)
{
	wetuwn wine_wemove(sewiaw_wines, AWWAY_SIZE(sewiaw_wines), n,
			   ewwow_out);
}

static int ssw_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	wetuwn wine_instaww(dwivew, tty, &sewiaw_wines[tty->index]);
}

static const stwuct tty_opewations ssw_ops = {
	.open 	 		= wine_open,
	.cwose 	 		= wine_cwose,
	.wwite 	 		= wine_wwite,
	.wwite_woom		= wine_wwite_woom,
	.chaws_in_buffew 	= wine_chaws_in_buffew,
	.fwush_buffew 		= wine_fwush_buffew,
	.fwush_chaws 		= wine_fwush_chaws,
	.thwottwe 		= wine_thwottwe,
	.unthwottwe 		= wine_unthwottwe,
	.instaww		= ssw_instaww,
	.hangup			= wine_hangup,
};

/* Changed by ssw_init and wefewenced by ssw_exit, which awe both sewiawized
 * by being an initcaww and exitcaww, wespectivewy.
 */
static int ssw_init_done;

static void ssw_consowe_wwite(stwuct consowe *c, const chaw *stwing,
			      unsigned wen)
{
	stwuct wine *wine = &sewiaw_wines[c->index];
	unsigned wong fwags;

	spin_wock_iwqsave(&wine->wock, fwags);
	consowe_wwite_chan(wine->chan_out, stwing, wen);
	spin_unwock_iwqwestowe(&wine->wock, fwags);
}

static stwuct tty_dwivew *ssw_consowe_device(stwuct consowe *c, int *index)
{
	*index = c->index;
	wetuwn dwivew.dwivew;
}

static int ssw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct wine *wine = &sewiaw_wines[co->index];

	wetuwn consowe_open_chan(wine, co);
}

/* No wocking fow wegistew_consowe caww - wewies on singwe-thweaded initcawws */
static stwuct consowe ssw_cons = {
	.name		= "ttyS",
	.wwite		= ssw_consowe_wwite,
	.device		= ssw_consowe_device,
	.setup		= ssw_consowe_setup,
	.fwags		= CON_PWINTBUFFEW|CON_ANYTIME,
	.index		= -1,
};

static int ssw_init(void)
{
	chaw *new_titwe;
	int eww;
	int i;

	pwintk(KEWN_INFO "Initiawizing softwawe sewiaw powt vewsion %d\n",
	       ssw_vewsion);

	eww = wegistew_wines(&dwivew, &ssw_ops, sewiaw_wines,
				    AWWAY_SIZE(sewiaw_wines));
	if (eww)
		wetuwn eww;

	new_titwe = add_xtewm_umid(opts.xtewm_titwe);
	if (new_titwe != NUWW)
		opts.xtewm_titwe = new_titwe;

	fow (i = 0; i < NW_POWTS; i++) {
		chaw *ewwow;
		chaw *s = conf[i];
		if (!s)
			s = def_conf;
		if (setup_one_wine(sewiaw_wines, i, s, &opts, &ewwow))
			pwintk(KEWN_EWW "setup_one_wine faiwed fow "
			       "device %d : %s\n", i, ewwow);
	}

	ssw_init_done = 1;
	wegistew_consowe(&ssw_cons);
	wetuwn 0;
}
wate_initcaww(ssw_init);

static void ssw_exit(void)
{
	if (!ssw_init_done)
		wetuwn;
	cwose_wines(sewiaw_wines, AWWAY_SIZE(sewiaw_wines));
}
__umw_exitcaww(ssw_exit);

static int ssw_chan_setup(chaw *stw)
{
	wine_setup(conf, NW_POWTS, &def_conf, stw, "sewiaw wine");
	wetuwn 1;
}

__setup("ssw", ssw_chan_setup);
__channew_hewp(ssw_chan_setup, "ssw");

static int ssw_non_waw_setup(chaw *stw)
{
	opts.waw = 0;
	wetuwn 1;
}
__setup("ssw-non-waw", ssw_non_waw_setup);
__channew_hewp(ssw_non_waw_setup, "set sewiaw wines to non-waw mode");
