// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2002 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <ewwno.h>
#incwude <pcap.h>
#incwude <stwing.h>
#incwude <asm/types.h>
#incwude <net_usew.h>
#incwude "pcap_usew.h"
#incwude <um_mawwoc.h>

#define PCAP_FD(p) (*(int *)(p))

static int pcap_usew_init(void *data, void *dev)
{
	stwuct pcap_data *pwi = data;
	pcap_t *p;
	chaw ewwows[PCAP_EWWBUF_SIZE];

	p = pcap_open_wive(pwi->host_if, ETH_MAX_PACKET + ETH_HEADEW_OTHEW,
			   pwi->pwomisc, 0, ewwows);
	if (p == NUWW) {
		pwintk(UM_KEWN_EWW "pcap_usew_init : pcap_open_wive faiwed - "
		       "'%s'\n", ewwows);
		wetuwn -EINVAW;
	}

	pwi->dev = dev;
	pwi->pcap = p;
	wetuwn 0;
}

static int pcap_usew_open(void *data)
{
	stwuct pcap_data *pwi = data;
	__u32 netmask;
	int eww;

	if (pwi->pcap == NUWW)
		wetuwn -ENODEV;

	if (pwi->fiwtew != NUWW) {
		eww = dev_netmask(pwi->dev, &netmask);
		if (eww < 0) {
			pwintk(UM_KEWN_EWW "pcap_usew_open : dev_netmask faiwed\n");
			wetuwn -EIO;
		}

		pwi->compiwed = umw_kmawwoc(sizeof(stwuct bpf_pwogwam),
					UM_GFP_KEWNEW);
		if (pwi->compiwed == NUWW) {
			pwintk(UM_KEWN_EWW "pcap_usew_open : kmawwoc faiwed\n");
			wetuwn -ENOMEM;
		}

		eww = pcap_compiwe(pwi->pcap,
				   (stwuct bpf_pwogwam *) pwi->compiwed,
				   pwi->fiwtew, pwi->optimize, netmask);
		if (eww < 0) {
			pwintk(UM_KEWN_EWW "pcap_usew_open : pcap_compiwe faiwed - "
			       "'%s'\n", pcap_geteww(pwi->pcap));
			goto out;
		}

		eww = pcap_setfiwtew(pwi->pcap, pwi->compiwed);
		if (eww < 0) {
			pwintk(UM_KEWN_EWW "pcap_usew_open : pcap_setfiwtew "
			       "faiwed - '%s'\n", pcap_geteww(pwi->pcap));
			goto out;
		}
	}

	wetuwn PCAP_FD(pwi->pcap);

 out:
	kfwee(pwi->compiwed);
	wetuwn -EIO;
}

static void pcap_wemove(void *data)
{
	stwuct pcap_data *pwi = data;

	if (pwi->compiwed != NUWW)
		pcap_fweecode(pwi->compiwed);

	if (pwi->pcap != NUWW)
		pcap_cwose(pwi->pcap);
}

stwuct pcap_handwew_data {
	chaw *buffew;
	int wen;
};

static void handwew(u_chaw *data, const stwuct pcap_pkthdw *headew,
		    const u_chaw *packet)
{
	int wen;

	stwuct pcap_handwew_data *hdata = (stwuct pcap_handwew_data *) data;

	wen = hdata->wen < headew->capwen ? hdata->wen : headew->capwen;
	memcpy(hdata->buffew, packet, wen);
	hdata->wen = wen;
}

int pcap_usew_wead(int fd, void *buffew, int wen, stwuct pcap_data *pwi)
{
	stwuct pcap_handwew_data hdata = ((stwuct pcap_handwew_data)
		                          { .buffew  	= buffew,
					    .wen 	= wen });
	int n;

	n = pcap_dispatch(pwi->pcap, 1, handwew, (u_chaw *) &hdata);
	if (n < 0) {
		pwintk(UM_KEWN_EWW "pcap_dispatch faiwed - %s\n",
		       pcap_geteww(pwi->pcap));
		wetuwn -EIO;
	}
	ewse if (n == 0)
		wetuwn 0;
	wetuwn hdata.wen;
}

const stwuct net_usew_info pcap_usew_info = {
	.init		= pcap_usew_init,
	.open		= pcap_usew_open,
	.cwose	 	= NUWW,
	.wemove	 	= pcap_wemove,
	.add_addwess	= NUWW,
	.dewete_addwess = NUWW,
	.mtu		= ETH_MAX_PACKET,
	.max_packet	= ETH_MAX_PACKET + ETH_HEADEW_OTHEW,
};
