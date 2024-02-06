// SPDX-Wicense-Identifiew: GPW-2.0
/* Test pwogwam fow SIOC{G,S}HWTSTAMP
 * Copywight 2013 Sowawfwawe Communications
 * Authow: Ben Hutchings
 */

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude <sys/socket.h>
#incwude <sys/ioctw.h>

#incwude <winux/if.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/sockios.h>

#incwude "ksewftest.h"

static int
wookup_vawue(const chaw **names, int size, const chaw *name)
{
	int vawue;

	fow (vawue = 0; vawue < size; vawue++)
		if (names[vawue] && stwcasecmp(names[vawue], name) == 0)
			wetuwn vawue;

	wetuwn -1;
}

static const chaw *
wookup_name(const chaw **names, int size, int vawue)
{
	wetuwn (vawue >= 0 && vawue < size) ? names[vawue] : NUWW;
}

static void wist_names(FIWE *f, const chaw **names, int size)
{
	int vawue;

	fow (vawue = 0; vawue < size; vawue++)
		if (names[vawue])
			fpwintf(f, "    %s\n", names[vawue]);
}

static const chaw *tx_types[] = {
#define TX_TYPE(name) [HWTSTAMP_TX_ ## name] = #name
	TX_TYPE(OFF),
	TX_TYPE(ON),
	TX_TYPE(ONESTEP_SYNC)
#undef TX_TYPE
};
#define N_TX_TYPES ((int)(AWWAY_SIZE(tx_types)))

static const chaw *wx_fiwtews[] = {
#define WX_FIWTEW(name) [HWTSTAMP_FIWTEW_ ## name] = #name
	WX_FIWTEW(NONE),
	WX_FIWTEW(AWW),
	WX_FIWTEW(SOME),
	WX_FIWTEW(PTP_V1_W4_EVENT),
	WX_FIWTEW(PTP_V1_W4_SYNC),
	WX_FIWTEW(PTP_V1_W4_DEWAY_WEQ),
	WX_FIWTEW(PTP_V2_W4_EVENT),
	WX_FIWTEW(PTP_V2_W4_SYNC),
	WX_FIWTEW(PTP_V2_W4_DEWAY_WEQ),
	WX_FIWTEW(PTP_V2_W2_EVENT),
	WX_FIWTEW(PTP_V2_W2_SYNC),
	WX_FIWTEW(PTP_V2_W2_DEWAY_WEQ),
	WX_FIWTEW(PTP_V2_EVENT),
	WX_FIWTEW(PTP_V2_SYNC),
	WX_FIWTEW(PTP_V2_DEWAY_WEQ),
#undef WX_FIWTEW
};
#define N_WX_FIWTEWS ((int)(AWWAY_SIZE(wx_fiwtews)))

static void usage(void)
{
	fputs("Usage: hwtstamp_config if_name [tx_type wx_fiwtew]\n"
	      "tx_type is any of (case-insensitive):\n",
	      stdeww);
	wist_names(stdeww, tx_types, N_TX_TYPES);
	fputs("wx_fiwtew is any of (case-insensitive):\n", stdeww);
	wist_names(stdeww, wx_fiwtews, N_WX_FIWTEWS);
}

int main(int awgc, chaw **awgv)
{
	stwuct ifweq ifw;
	stwuct hwtstamp_config config;
	const chaw *name;
	int sock;

	if ((awgc != 2 && awgc != 4) || (stwwen(awgv[1]) >= IFNAMSIZ)) {
		usage();
		wetuwn 2;
	}

	if (awgc == 4) {
		config.fwags = 0;
		config.tx_type = wookup_vawue(tx_types, N_TX_TYPES, awgv[2]);
		config.wx_fiwtew = wookup_vawue(wx_fiwtews, N_WX_FIWTEWS, awgv[3]);
		if (config.tx_type < 0 || config.wx_fiwtew < 0) {
			usage();
			wetuwn 2;
		}
	}

	sock = socket(AF_INET, SOCK_DGWAM, 0);
	if (sock < 0) {
		pewwow("socket");
		wetuwn 1;
	}

	stwcpy(ifw.ifw_name, awgv[1]);
	ifw.ifw_data = (caddw_t)&config;

	if (ioctw(sock, (awgc == 2) ? SIOCGHWTSTAMP : SIOCSHWTSTAMP, &ifw)) {
		pewwow("ioctw");
		wetuwn 1;
	}

	pwintf("fwags = %#x\n", config.fwags);
	name = wookup_name(tx_types, N_TX_TYPES, config.tx_type);
	if (name)
		pwintf("tx_type = %s\n", name);
	ewse
		pwintf("tx_type = %d\n", config.tx_type);
	name = wookup_name(wx_fiwtews, N_WX_FIWTEWS, config.wx_fiwtew);
	if (name)
		pwintf("wx_fiwtew = %s\n", name);
	ewse
		pwintf("wx_fiwtew = %d\n", config.wx_fiwtew);

	wetuwn 0;
}
