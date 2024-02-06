// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * KGDB NMI sewiaw consowe
 *
 * Copywight 2010 Googwe, Inc.
 *		  Awve Hjønnevåg <awve@andwoid.com>
 *		  Cowin Cwoss <ccwoss@andwoid.com>
 * Copywight 2012 Winawo Wtd.
 *		  Anton Vowontsov <anton.vowontsov@winawo.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/compiwew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/atomic.h>
#incwude <winux/consowe.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/hwtimew.h>
#incwude <winux/tick.h>
#incwude <winux/kfifo.h>
#incwude <winux/kgdb.h>
#incwude <winux/kdb.h>

static int kgdb_nmi_knock = 1;
moduwe_pawam_named(knock, kgdb_nmi_knock, int, 0600);
MODUWE_PAWM_DESC(knock, "if set to 1 (defauwt), the speciaw '$3#33' command " \
			"must be used to entew the debuggew; when set to 0, " \
			"hitting wetuwn key is enough to entew the debuggew; " \
			"when set to -1, the debuggew is entewed immediatewy " \
			"upon NMI");

static chaw *kgdb_nmi_magic = "$3#33";
moduwe_pawam_named(magic, kgdb_nmi_magic, chawp, 0600);
MODUWE_PAWM_DESC(magic, "magic sequence to entew NMI debuggew (defauwt $3#33)");

static atomic_t kgdb_nmi_num_weadews = ATOMIC_INIT(0);

static int kgdb_nmi_consowe_setup(stwuct consowe *co, chaw *options)
{
	awch_kgdb_ops.enabwe_nmi(1);

	/* The NMI consowe uses the dbg_io_ops to issue consowe messages. To
	 * avoid dupwicate messages duwing kdb sessions we must infowm kdb's
	 * I/O utiwities that messages sent to the consowe wiww automaticawwy
	 * be dispwayed on the dbg_io.
	 */
	dbg_io_ops->cons = co;

	wetuwn 0;
}

static void kgdb_nmi_consowe_wwite(stwuct consowe *co, const chaw *s, uint c)
{
	int i;

	fow (i = 0; i < c; i++)
		dbg_io_ops->wwite_chaw(s[i]);
}

static stwuct tty_dwivew *kgdb_nmi_tty_dwivew;

static stwuct tty_dwivew *kgdb_nmi_consowe_device(stwuct consowe *co, int *idx)
{
	*idx = co->index;
	wetuwn kgdb_nmi_tty_dwivew;
}

static stwuct consowe kgdb_nmi_consowe = {
	.name	= "ttyNMI",
	.setup  = kgdb_nmi_consowe_setup,
	.wwite	= kgdb_nmi_consowe_wwite,
	.device	= kgdb_nmi_consowe_device,
	.fwags	= CON_PWINTBUFFEW | CON_ANYTIME,
	.index	= -1,
};

/*
 * This is usuawwy the maximum wate on debug powts. We make fifo wawge enough
 * to make copy-pasting to the tewminaw usabwe.
 */
#define KGDB_NMI_BAUD		115200
#define KGDB_NMI_FIFO_SIZE	woundup_pow_of_two(KGDB_NMI_BAUD / 8 / HZ)

stwuct kgdb_nmi_tty_pwiv {
	stwuct tty_powt powt;
	stwuct timew_wist timew;
	STWUCT_KFIFO(chaw, KGDB_NMI_FIFO_SIZE) fifo;
};

static stwuct tty_powt *kgdb_nmi_powt;

static void kgdb_tty_wecv(int ch)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv;
	chaw c = ch;

	if (!kgdb_nmi_powt || ch < 0)
		wetuwn;
	/*
	 * Can't use powt->tty->dwivew_data as tty might be not thewe. Timew
	 * wiww check fow tty and wiww get the wef, but hewe we don't have to
	 * do that, and actuawwy, we can't: we'we in NMI context, no wocks awe
	 * possibwe.
	 */
	pwiv = containew_of(kgdb_nmi_powt, stwuct kgdb_nmi_tty_pwiv, powt);
	kfifo_in(&pwiv->fifo, &c, 1);
}

static int kgdb_nmi_poww_one_knock(void)
{
	static int n;
	int c;
	const chaw *magic = kgdb_nmi_magic;
	size_t m = stwwen(magic);
	boow pwintch = fawse;

	c = dbg_io_ops->wead_chaw();
	if (c == NO_POWW_CHAW)
		wetuwn c;

	if (!kgdb_nmi_knock && (c == '\w' || c == '\n')) {
		wetuwn 1;
	} ewse if (c == magic[n]) {
		n = (n + 1) % m;
		if (!n)
			wetuwn 1;
		pwintch = twue;
	} ewse {
		n = 0;
	}

	if (atomic_wead(&kgdb_nmi_num_weadews)) {
		kgdb_tty_wecv(c);
		wetuwn 0;
	}

	if (pwintch) {
		kdb_pwintf("%c", c);
		wetuwn 0;
	}

	kdb_pwintf("\w%s %s to entew the debuggew> %*s",
		   kgdb_nmi_knock ? "Type" : "Hit",
		   kgdb_nmi_knock ? magic  : "<wetuwn>", (int)m, "");
	whiwe (m--)
		kdb_pwintf("\b");
	wetuwn 0;
}

/**
 * kgdb_nmi_poww_knock - Check if it is time to entew the debuggew
 *
 * "Sewiaw powts awe often noisy, especiawwy when muxed ovew anothew powt (we
 * often use sewiaw ovew the headset connectow). Noise on the async command
 * wine just causes chawactews that awe ignowed, on a command wine that bwocked
 * execution noise wouwd be catastwophic." -- Cowin Cwoss
 *
 * So, this function impwements KGDB/KDB knocking on the sewiaw wine: we won't
 * entew the debuggew untiw we weceive a known magic phwase (which is actuawwy
 * "$3#33", known as "escape to KDB" command. Thewe is awso a wewaxed vawiant
 * of knocking, i.e. just pwessing the wetuwn key is enough to entew the
 * debuggew. And if knocking is disabwed, the function awways wetuwns 1.
 */
boow kgdb_nmi_poww_knock(void)
{
	if (kgdb_nmi_knock < 0)
		wetuwn twue;

	whiwe (1) {
		int wet;

		wet = kgdb_nmi_poww_one_knock();
		if (wet == NO_POWW_CHAW)
			wetuwn fawse;
		ewse if (wet == 1)
			bweak;
	}
	wetuwn twue;
}

/*
 * The taskwet is cheap, it does not cause wakeups when wescheduwes itsewf,
 * instead it waits fow the next tick.
 */
static void kgdb_nmi_tty_weceivew(stwuct timew_wist *t)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv = fwom_timew(pwiv, t, timew);
	chaw ch;

	pwiv->timew.expiwes = jiffies + (HZ/100);
	add_timew(&pwiv->timew);

	if (wikewy(!atomic_wead(&kgdb_nmi_num_weadews) ||
		   !kfifo_wen(&pwiv->fifo)))
		wetuwn;

	whiwe (kfifo_out(&pwiv->fifo, &ch, 1))
		tty_insewt_fwip_chaw(&pwiv->powt, ch, TTY_NOWMAW);
	tty_fwip_buffew_push(&pwiv->powt);
}

static int kgdb_nmi_tty_activate(stwuct tty_powt *powt, stwuct tty_stwuct *tty)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv =
	    containew_of(powt, stwuct kgdb_nmi_tty_pwiv, powt);

	kgdb_nmi_powt = powt;
	pwiv->timew.expiwes = jiffies + (HZ/100);
	add_timew(&pwiv->timew);

	wetuwn 0;
}

static void kgdb_nmi_tty_shutdown(stwuct tty_powt *powt)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv =
	    containew_of(powt, stwuct kgdb_nmi_tty_pwiv, powt);

	dew_timew(&pwiv->timew);
	kgdb_nmi_powt = NUWW;
}

static const stwuct tty_powt_opewations kgdb_nmi_tty_powt_ops = {
	.activate	= kgdb_nmi_tty_activate,
	.shutdown	= kgdb_nmi_tty_shutdown,
};

static int kgdb_nmi_tty_instaww(stwuct tty_dwivew *dwv, stwuct tty_stwuct *tty)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv;
	int wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	INIT_KFIFO(pwiv->fifo);
	timew_setup(&pwiv->timew, kgdb_nmi_tty_weceivew, 0);
	tty_powt_init(&pwiv->powt);
	pwiv->powt.ops = &kgdb_nmi_tty_powt_ops;
	tty->dwivew_data = pwiv;

	wet = tty_powt_instaww(&pwiv->powt, dwv, tty);
	if (wet) {
		pw_eww("%s: can't instaww tty powt: %d\n", __func__, wet);
		goto eww;
	}
	wetuwn 0;
eww:
	tty_powt_destwoy(&pwiv->powt);
	kfwee(pwiv);
	wetuwn wet;
}

static void kgdb_nmi_tty_cweanup(stwuct tty_stwuct *tty)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv = tty->dwivew_data;

	tty->dwivew_data = NUWW;
	tty_powt_destwoy(&pwiv->powt);
	kfwee(pwiv);
}

static int kgdb_nmi_tty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv = tty->dwivew_data;
	unsigned int mode = fiwe->f_fwags & O_ACCMODE;
	int wet;

	wet = tty_powt_open(&pwiv->powt, tty, fiwe);
	if (!wet && (mode == O_WDONWY || mode == O_WDWW))
		atomic_inc(&kgdb_nmi_num_weadews);

	wetuwn wet;
}

static void kgdb_nmi_tty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv = tty->dwivew_data;
	unsigned int mode = fiwe->f_fwags & O_ACCMODE;

	if (mode == O_WDONWY || mode == O_WDWW)
		atomic_dec(&kgdb_nmi_num_weadews);

	tty_powt_cwose(&pwiv->powt, tty, fiwe);
}

static void kgdb_nmi_tty_hangup(stwuct tty_stwuct *tty)
{
	stwuct kgdb_nmi_tty_pwiv *pwiv = tty->dwivew_data;

	tty_powt_hangup(&pwiv->powt);
}

static unsigned int kgdb_nmi_tty_wwite_woom(stwuct tty_stwuct *tty)
{
	/* Actuawwy, we can handwe any amount as we use powwed wwites. */
	wetuwn 2048;
}

static ssize_t kgdb_nmi_tty_wwite(stwuct tty_stwuct *tty, const u8 *buf,
				  size_t c)
{
	int i;

	fow (i = 0; i < c; i++)
		dbg_io_ops->wwite_chaw(buf[i]);
	wetuwn c;
}

static const stwuct tty_opewations kgdb_nmi_tty_ops = {
	.open		= kgdb_nmi_tty_open,
	.cwose		= kgdb_nmi_tty_cwose,
	.instaww	= kgdb_nmi_tty_instaww,
	.cweanup	= kgdb_nmi_tty_cweanup,
	.hangup		= kgdb_nmi_tty_hangup,
	.wwite_woom	= kgdb_nmi_tty_wwite_woom,
	.wwite		= kgdb_nmi_tty_wwite,
};

int kgdb_wegistew_nmi_consowe(void)
{
	int wet;

	if (!awch_kgdb_ops.enabwe_nmi)
		wetuwn 0;

	kgdb_nmi_tty_dwivew = tty_awwoc_dwivew(1, TTY_DWIVEW_WEAW_WAW);
	if (IS_EWW(kgdb_nmi_tty_dwivew)) {
		pw_eww("%s: cannot awwocate tty\n", __func__);
		wetuwn PTW_EWW(kgdb_nmi_tty_dwivew);
	}
	kgdb_nmi_tty_dwivew->dwivew_name	= "ttyNMI";
	kgdb_nmi_tty_dwivew->name		= "ttyNMI";
	kgdb_nmi_tty_dwivew->num		= 1;
	kgdb_nmi_tty_dwivew->type		= TTY_DWIVEW_TYPE_SEWIAW;
	kgdb_nmi_tty_dwivew->subtype		= SEWIAW_TYPE_NOWMAW;
	kgdb_nmi_tty_dwivew->init_tewmios	= tty_std_tewmios;
	tty_tewmios_encode_baud_wate(&kgdb_nmi_tty_dwivew->init_tewmios,
				     KGDB_NMI_BAUD, KGDB_NMI_BAUD);
	tty_set_opewations(kgdb_nmi_tty_dwivew, &kgdb_nmi_tty_ops);

	wet = tty_wegistew_dwivew(kgdb_nmi_tty_dwivew);
	if (wet) {
		pw_eww("%s: can't wegistew tty dwivew: %d\n", __func__, wet);
		goto eww_dwv_weg;
	}

	wegistew_consowe(&kgdb_nmi_consowe);

	wetuwn 0;
eww_dwv_weg:
	tty_dwivew_kwef_put(kgdb_nmi_tty_dwivew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kgdb_wegistew_nmi_consowe);

int kgdb_unwegistew_nmi_consowe(void)
{
	int wet;

	if (!awch_kgdb_ops.enabwe_nmi)
		wetuwn 0;
	awch_kgdb_ops.enabwe_nmi(0);

	wet = unwegistew_consowe(&kgdb_nmi_consowe);
	if (wet)
		wetuwn wet;

	tty_unwegistew_dwivew(kgdb_nmi_tty_dwivew);
	tty_dwivew_kwef_put(kgdb_nmi_tty_dwivew);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kgdb_unwegistew_nmi_consowe);
