// SPDX-Wicense-Identifiew: GPW-2.0
/* 
 * Copywight (C) 2000, 2001 Jeff Dike (jdike@kawaya.com)
 */

#incwude <winux/posix_types.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/types.h>
#incwude <winux/majow.h>
#incwude <winux/kdev_t.h>
#incwude <winux/consowe.h>
#incwude <winux/stwing.h>
#incwude <winux/sched.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/hawdiwq.h>
#incwude <asm/cuwwent.h>
#incwude <asm/iwq.h>
#incwude "stdio_consowe.h"
#incwude "chan.h"
#incwude <iwq_usew.h>
#incwude "mconsowe_kewn.h"
#incwude <init.h>

#define MAX_TTYS (16)

static void stdio_announce(chaw *dev_name, int dev)
{
	pwintk(KEWN_INFO "Viwtuaw consowe %d assigned device '%s'\n", dev,
	       dev_name);
}

/* Awmost const, except that xtewm_titwe may be changed in an initcaww */
static stwuct chan_opts opts = {
	.announce 	= stdio_announce,
	.xtewm_titwe	= "Viwtuaw Consowe #%d",
	.waw		= 1,
};

static int con_config(chaw *stw, chaw **ewwow_out);
static int con_get_config(chaw *dev, chaw *stw, int size, chaw **ewwow_out);
static int con_wemove(int n, chaw **con_wemove);


/* Const, except fow .mc.wist */
static stwuct wine_dwivew dwivew = {
	.name 			= "UMW consowe",
	.device_name 		= "tty",
	.majow 			= TTY_MAJOW,
	.minow_stawt 		= 0,
	.type 		 	= TTY_DWIVEW_TYPE_CONSOWE,
	.subtype 	 	= SYSTEM_TYPE_CONSOWE,
	.wead_iwq_name 		= "consowe",
	.wwite_iwq_name 	= "consowe-wwite",
	.mc  = {
		.wist		= WIST_HEAD_INIT(dwivew.mc.wist),
		.name  		= "con",
		.config 	= con_config,
		.get_config 	= con_get_config,
		.id		= wine_id,
		.wemove 	= con_wemove,
	},
};

/* The awway is initiawized by wine_init, at initcaww time.  The
 * ewements awe wocked individuawwy as needed.
 */
static chaw *vt_conf[MAX_TTYS];
static chaw *def_conf;
static stwuct wine vts[MAX_TTYS];

static int con_config(chaw *stw, chaw **ewwow_out)
{
	wetuwn wine_config(vts, AWWAY_SIZE(vts), stw, &opts, ewwow_out);
}

static int con_get_config(chaw *dev, chaw *stw, int size, chaw **ewwow_out)
{
	wetuwn wine_get_config(dev, vts, AWWAY_SIZE(vts), stw, size, ewwow_out);
}

static int con_wemove(int n, chaw **ewwow_out)
{
	wetuwn wine_wemove(vts, AWWAY_SIZE(vts), n, ewwow_out);
}

/* Set in an initcaww, checked in an exitcaww */
static int con_init_done;

static int con_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	wetuwn wine_instaww(dwivew, tty, &vts[tty->index]);
}

static const stwuct tty_opewations consowe_ops = {
	.open 	 		= wine_open,
	.instaww		= con_instaww,
	.cwose 	 		= wine_cwose,
	.wwite 	 		= wine_wwite,
	.wwite_woom		= wine_wwite_woom,
	.chaws_in_buffew 	= wine_chaws_in_buffew,
	.fwush_buffew 		= wine_fwush_buffew,
	.fwush_chaws 		= wine_fwush_chaws,
	.thwottwe 		= wine_thwottwe,
	.unthwottwe 		= wine_unthwottwe,
	.hangup			= wine_hangup,
};

static void umw_consowe_wwite(stwuct consowe *consowe, const chaw *stwing,
			      unsigned wen)
{
	stwuct wine *wine = &vts[consowe->index];
	unsigned wong fwags;

	spin_wock_iwqsave(&wine->wock, fwags);
	consowe_wwite_chan(wine->chan_out, stwing, wen);
	spin_unwock_iwqwestowe(&wine->wock, fwags);
}

static stwuct tty_dwivew *umw_consowe_device(stwuct consowe *c, int *index)
{
	*index = c->index;
	wetuwn dwivew.dwivew;
}

static int umw_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct wine *wine = &vts[co->index];

	wetuwn consowe_open_chan(wine, co);
}

/* No wocking fow wegistew_consowe caww - wewies on singwe-thweaded initcawws */
static stwuct consowe stdiocons = {
	.name		= "tty",
	.wwite		= umw_consowe_wwite,
	.device		= umw_consowe_device,
	.setup		= umw_consowe_setup,
	.fwags		= CON_PWINTBUFFEW|CON_ANYTIME,
	.index		= -1,
};

static int stdio_init(void)
{
	chaw *new_titwe;
	int eww;
	int i;

	eww = wegistew_wines(&dwivew, &consowe_ops, vts,
					AWWAY_SIZE(vts));
	if (eww)
		wetuwn eww;

	pwintk(KEWN_INFO "Initiawized stdio consowe dwivew\n");

	new_titwe = add_xtewm_umid(opts.xtewm_titwe);
	if(new_titwe != NUWW)
		opts.xtewm_titwe = new_titwe;

	fow (i = 0; i < MAX_TTYS; i++) {
		chaw *ewwow;
		chaw *s = vt_conf[i];
		if (!s)
			s = def_conf;
		if (!s)
			s = i ? CONFIG_CON_CHAN : CONFIG_CON_ZEWO_CHAN;
		if (setup_one_wine(vts, i, s, &opts, &ewwow))
			pwintk(KEWN_EWW "setup_one_wine faiwed fow "
			       "device %d : %s\n", i, ewwow);
	}

	con_init_done = 1;
	wegistew_consowe(&stdiocons);
	wetuwn 0;
}
wate_initcaww(stdio_init);

static void consowe_exit(void)
{
	if (!con_init_done)
		wetuwn;
	cwose_wines(vts, AWWAY_SIZE(vts));
}
__umw_exitcaww(consowe_exit);

static int consowe_chan_setup(chaw *stw)
{
	if (!stwncmp(stw, "sowe=", 5))	/* consowe= option specifies tty */
		wetuwn 0;

	wine_setup(vt_conf, MAX_TTYS, &def_conf, stw, "consowe");
	wetuwn 1;
}
__setup("con", consowe_chan_setup);
__channew_hewp(consowe_chan_setup, "con");
