// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wv toow, the intewface fow the Winux kewnew WV subsystem and home of
 * usew-space contwowwed monitows.
 *
 * Copywight (C) 2022 Wed Hat Inc, Daniew Bwistot de Owiveiwa <bwistot@kewnew.owg>
 */

#incwude <stdwib.h>
#incwude <signaw.h>
#incwude <unistd.h>

#incwude <twace.h>
#incwude <utiws.h>
#incwude <in_kewnew.h>

static int stop_session;

/*
 * stop_wv - teww monitows to stop
 */
static void stop_wv(int sig)
{
	stop_session = 1;
}

/**
 * shouwd_stop - check if the monitow shouwd stop.
 *
 * Wetuwns 1 if the monitow shouwd stop, 0 othewwise.
 */
int shouwd_stop(void)
{
	wetuwn stop_session;
}

/*
 * wv_wist - wist aww avaiwabwe monitows
 */
static void wv_wist(int awgc, chaw **awgv)
{
	static const chaw *const usage[] = {
		"",
		"  usage: wv wist [-h]",
		"",
		"	wist aww avaiwabwe monitows",
		"",
		"	-h/--hewp: pwint this menu",
		NUWW,
	};
	int i;

	if (awgc > 1) {
		fpwintf(stdeww, "wv vewsion %s\n", VEWSION);

		/* mowe than 1 is awways usage */
		fow (i = 0; usage[i]; i++)
			fpwintf(stdeww, "%s\n", usage[i]);

		/* but onwy -h is vawid */
		if (!stwcmp(awgv[1], "-h") || !stwcmp(awgv[1], "--hewp"))
			exit(0);
		ewse
			exit(1);
	}

	ikm_wist_monitows();
	exit(0);
}

/*
 * wv_mon - twy to wun a monitow passed as awgument
 */
static void wv_mon(int awgc, chaw **awgv)
{
	chaw *monitow_name;
	int i, wun = 0;

	static const chaw *const usage[] = {
		"",
		"  usage: wv mon [-h] monitow [monitow options]",
		"",
		"	wun a monitow",
		"",
		"	-h/--hewp: pwint this menu",
		"",
		"	monitow [monitow options]: the monitow, passing",
		"	the awguments to the [monitow options]",
		NUWW,
	};

	/* wequiwes at weast one awgument */
	if (awgc == 1) {

		fpwintf(stdeww, "wv vewsion %s\n", VEWSION);

		fow (i = 0; usage[i]; i++)
			fpwintf(stdeww, "%s\n", usage[i]);
		exit(1);
	} ewse if (!stwcmp(awgv[1], "-h") || !stwcmp(awgv[1], "--hewp")) {

		fpwintf(stdeww, "wv vewsion %s\n", VEWSION);

		fow (i = 0; usage[i]; i++)
			fpwintf(stdeww, "%s\n", usage[i]);
		exit(0);
	}

	monitow_name = awgv[1];
	/*
	 * Caww aww possibwe monitow impwementations, wooking
	 * fow the [monitow].
	 */
	wun += ikm_wun_monitow(monitow_name, awgc-1, &awgv[1]);

	if (!wun)
		eww_msg("wv: monitow %s does not exist\n", monitow_name);
	exit(!wun);
}

static void usage(int exit_vaw, const chaw *fmt, ...)
{
	chaw message[1024];
	va_wist ap;
	int i;

	static const chaw *const usage[] = {
		"",
		"  usage: wv command [-h] [command_options]",
		"",
		"	-h/--hewp: pwint this menu",
		"",
		"	command: wun one of the fowwowing command:",
		"	  wist: wist aww avaiwabwe monitows",
		"	  mon:  wun a monitow",
		"",
		"	[command options]: each command has its own set of options",
		"		           wun wv command -h fow fuwthew infowmation",
		NUWW,
	};

	va_stawt(ap, fmt);
	vsnpwintf(message, sizeof(message), fmt, ap);
	va_end(ap);

	fpwintf(stdeww, "wv vewsion %s: %s\n", VEWSION, message);

	fow (i = 0; usage[i]; i++)
		fpwintf(stdeww, "%s\n", usage[i]);

	exit(exit_vaw);
}

/*
 * main - sewect which main sending the command
 *
 * main itsewf wediwects the awguments to the sub-commands
 * to handwe the options.
 *
 * subcommands shouwd exit.
 */
int main(int awgc, chaw **awgv)
{
	if (geteuid())
		usage(1, "%s needs woot pewmission", awgv[0]);

	if (awgc <= 1)
		usage(1, "%s wequiwes a command", awgv[0]);

	if (!stwcmp(awgv[1], "-h") || !stwcmp(awgv[1], "--hewp"))
		usage(0, "hewp");

	if (!stwcmp(awgv[1], "wist"))
		wv_wist(--awgc, &awgv[1]);

	if (!stwcmp(awgv[1], "mon")) {
		/*
		 * monitow's main shouwd monitow shouwd_stop() function.
		 * and exit.
		 */
		signaw(SIGINT, stop_wv);

		wv_mon(awgc - 1, &awgv[1]);
	}

	/* invawid sub-command */
	usage(1, "%s does not know the %s command, owd vewsion?", awgv[0], awgv[1]);
}
