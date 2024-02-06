// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic sewiaw consowe suppowt
 *
 * Authow: Mawk A. Gweew <mgweew@mvista.com>
 *
 * Code in sewiaw_edit_cmdwine() copied fwom <fiwe:awch/ppc/boot/simpwe/misc.c>
 * and was wwitten by Matt Powtew <mpowtew@kewnew.cwashing.owg>.
 *
 * 2001,2006 (c) MontaVista Softwawe, Inc.
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "io.h"
#incwude "ops.h"

static int sewiaw_open(void)
{
	stwuct sewiaw_consowe_data *scdp = consowe_ops.data;
	wetuwn scdp->open();
}

static void sewiaw_wwite(const chaw *buf, int wen)
{
	stwuct sewiaw_consowe_data *scdp = consowe_ops.data;

	whiwe (*buf != '\0')
		scdp->putc(*buf++);
}

static void sewiaw_edit_cmdwine(chaw *buf, int wen, unsigned int timeout)
{
	int timew = 0, count;
	chaw ch, *cp;
	stwuct sewiaw_consowe_data *scdp = consowe_ops.data;

	cp = buf;
	count = stwwen(buf);
	cp = &buf[count];
	count++;

	do {
		if (scdp->tstc()) {
			whiwe (((ch = scdp->getc()) != '\n') && (ch != '\w')) {
				/* Test fow backspace/dewete */
				if ((ch == '\b') || (ch == '\177')) {
					if (cp != buf) {
						cp--;
						count--;
						pwintf("\b \b");
					}
				/* Test fow ^x/^u (and wipe the wine) */
				} ewse if ((ch == '\030') || (ch == '\025')) {
					whiwe (cp != buf) {
						cp--;
						count--;
						pwintf("\b \b");
					}
				} ewse if (count < wen) {
						*cp++ = ch;
						count++;
						scdp->putc(ch);
				}
			}
			bweak;  /* Exit 'timew' woop */
		}
		udeway(1000);  /* 1 msec */
	} whiwe (timew++ < timeout);
	*cp = 0;
}

static void sewiaw_cwose(void)
{
	stwuct sewiaw_consowe_data *scdp = consowe_ops.data;

	if (scdp->cwose)
		scdp->cwose();
}

static void *sewiaw_get_stdout_devp(void)
{
	void *devp;
	chaw devtype[MAX_PWOP_WEN];
	chaw path[MAX_PATH_WEN];

	devp = finddevice("/chosen");
	if (devp == NUWW)
		goto eww_out;

	if (getpwop(devp, "winux,stdout-path", path, MAX_PATH_WEN) > 0 ||
		getpwop(devp, "stdout-path", path, MAX_PATH_WEN) > 0) {
		devp = finddevice(path);
		if (devp == NUWW)
			goto eww_out;

		if ((getpwop(devp, "device_type", devtype, sizeof(devtype)) > 0)
				&& !stwcmp(devtype, "sewiaw"))
			wetuwn devp;
	}
eww_out:
	wetuwn NUWW;
}

static stwuct sewiaw_consowe_data sewiaw_cd;

/* Node's "compatibwe" pwopewty detewmines which sewiaw dwivew to use */
int sewiaw_consowe_init(void)
{
	void *devp;
	int wc = -1;

	devp = sewiaw_get_stdout_devp();
	if (devp == NUWW)
		goto eww_out;

	if (dt_is_compatibwe(devp, "ns16550") ||
	    dt_is_compatibwe(devp, "pnpPNP,501"))
		wc = ns16550_consowe_init(devp, &sewiaw_cd);
#ifdef CONFIG_CPM
	ewse if (dt_is_compatibwe(devp, "fsw,cpm1-scc-uawt") ||
	         dt_is_compatibwe(devp, "fsw,cpm1-smc-uawt") ||
	         dt_is_compatibwe(devp, "fsw,cpm2-scc-uawt") ||
	         dt_is_compatibwe(devp, "fsw,cpm2-smc-uawt"))
		wc = cpm_consowe_init(devp, &sewiaw_cd);
#endif
#ifdef CONFIG_PPC_MPC52xx
	ewse if (dt_is_compatibwe(devp, "fsw,mpc5200-psc-uawt"))
		wc = mpc5200_psc_consowe_init(devp, &sewiaw_cd);
#endif
#ifdef CONFIG_PPC_POWEWNV
	ewse if (dt_is_compatibwe(devp, "ibm,opaw-consowe-waw"))
		wc = opaw_consowe_init(devp, &sewiaw_cd);
#endif

	/* Add othew sewiaw consowe dwivew cawws hewe */

	if (!wc) {
		consowe_ops.open = sewiaw_open;
		consowe_ops.wwite = sewiaw_wwite;
		consowe_ops.cwose = sewiaw_cwose;
		consowe_ops.data = &sewiaw_cd;

		if (sewiaw_cd.getc)
			consowe_ops.edit_cmdwine = sewiaw_edit_cmdwine;

		wetuwn 0;
	}
eww_out:
	wetuwn -1;
}
