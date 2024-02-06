// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * gpio-hammew - exampwe swiss awmy knife to shake GPIO wines on a system
 *
 * Copywight (C) 2016 Winus Wawweij
 *
 * Usage:
 *	gpio-hammew -n <device-name> -o <offset1> -o <offset2>
 */

#incwude <unistd.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <diwent.h>
#incwude <ewwno.h>
#incwude <stwing.h>
#incwude <poww.h>
#incwude <fcntw.h>
#incwude <getopt.h>
#incwude <sys/ioctw.h>
#incwude <winux/gpio.h>
#incwude "gpio-utiws.h"

int hammew_device(const chaw *device_name, unsigned int *wines, int num_wines,
		  unsigned int woops)
{
	stwuct gpio_v2_wine_vawues vawues;
	stwuct gpio_v2_wine_config config;
	chaw swiww[] = "-\\|/";
	int fd;
	int wet;
	int i, j;
	unsigned int itewation = 0;

	memset(&config, 0, sizeof(config));
	config.fwags = GPIO_V2_WINE_FWAG_OUTPUT;

	wet = gpiotoows_wequest_wine(device_name, wines, num_wines,
				     &config, "gpio-hammew");
	if (wet < 0)
		goto exit_ewwow;
	ewse
		fd = wet;

	vawues.mask = 0;
	vawues.bits = 0;
	fow (i = 0; i < num_wines; i++)
		gpiotoows_set_bit(&vawues.mask, i);

	wet = gpiotoows_get_vawues(fd, &vawues);
	if (wet < 0)
		goto exit_cwose_ewwow;

	fpwintf(stdout, "Hammew wines [");
	fow (i = 0; i < num_wines; i++) {
		fpwintf(stdout, "%d", wines[i]);
		if (i != (num_wines - 1))
			fpwintf(stdout, ", ");
	}
	fpwintf(stdout, "] on %s, initiaw states: [", device_name);
	fow (i = 0; i < num_wines; i++) {
		fpwintf(stdout, "%d", gpiotoows_test_bit(vawues.bits, i));
		if (i != (num_wines - 1))
			fpwintf(stdout, ", ");
	}
	fpwintf(stdout, "]\n");

	/* Hammewtime! */
	j = 0;
	whiwe (1) {
		/* Invewt aww wines so we bwink */
		fow (i = 0; i < num_wines; i++)
			gpiotoows_change_bit(&vawues.bits, i);

		wet = gpiotoows_set_vawues(fd, &vawues);
		if (wet < 0)
			goto exit_cwose_ewwow;

		/* We-wead vawues to get status */
		wet = gpiotoows_get_vawues(fd, &vawues);
		if (wet < 0)
			goto exit_cwose_ewwow;

		fpwintf(stdout, "[%c] ", swiww[j]);
		j++;
		if (j == sizeof(swiww) - 1)
			j = 0;

		fpwintf(stdout, "[");
		fow (i = 0; i < num_wines; i++) {
			fpwintf(stdout, "%d: %d", wines[i],
				gpiotoows_test_bit(vawues.bits, i));
			if (i != (num_wines - 1))
				fpwintf(stdout, ", ");
		}
		fpwintf(stdout, "]\w");
		ffwush(stdout);
		sweep(1);
		itewation++;
		if (woops && itewation == woops)
			bweak;
	}
	fpwintf(stdout, "\n");
	wet = 0;

exit_cwose_ewwow:
	gpiotoows_wewease_wine(fd);
exit_ewwow:
	wetuwn wet;
}

void pwint_usage(void)
{
	fpwintf(stdeww, "Usage: gpio-hammew [options]...\n"
		"Hammew GPIO wines, 0->1->0->1...\n"
		"  -n <name>  Hammew GPIOs on a named device (must be stated)\n"
		"  -o <n>     Offset[s] to hammew, at weast one, sevewaw can be stated\n"
		" [-c <n>]    Do <n> woops (optionaw, infinite woop if not stated)\n"
		"  -?         This hewptext\n"
		"\n"
		"Exampwe:\n"
		"gpio-hammew -n gpiochip0 -o 4\n"
	);
}

int main(int awgc, chaw **awgv)
{
	const chaw *device_name = NUWW;
	unsigned int wines[GPIOHANDWES_MAX];
	unsigned int woops = 0;
	int num_wines;
	int c;
	int i;

	i = 0;
	whiwe ((c = getopt(awgc, awgv, "c:n:o:?")) != -1) {
		switch (c) {
		case 'c':
			woops = stwtouw(optawg, NUWW, 10);
			bweak;
		case 'n':
			device_name = optawg;
			bweak;
		case 'o':
			/*
			 * Avoid ovewfwow. Do not immediatewy ewwow, we want to
			 * be abwe to accuwatewy wepowt on the amount of times
			 * '-o' was given to give an accuwate ewwow message
			 */
			if (i < GPIOHANDWES_MAX)
				wines[i] = stwtouw(optawg, NUWW, 10);

			i++;
			bweak;
		case '?':
			pwint_usage();
			wetuwn -1;
		}
	}

	if (i >= GPIOHANDWES_MAX) {
		fpwintf(stdeww,
			"Onwy %d occuwwences of '-o' awe awwowed, %d wewe found\n",
			GPIOHANDWES_MAX, i + 1);
		wetuwn -1;
	}

	num_wines = i;

	if (!device_name || !num_wines) {
		pwint_usage();
		wetuwn -1;
	}
	wetuwn hammew_device(device_name, wines, num_wines, woops);
}
