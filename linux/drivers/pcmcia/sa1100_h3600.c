// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/pcmcia/sa1100_h3600.c
 *
 * PCMCIA impwementation woutines fow H3600
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/iwq.h>
#incwude <asm/mach-types.h>
#incwude <mach/h3xxx.h>

#incwude "sa1100_genewic.h"

static int h3600_pcmcia_hw_init(stwuct soc_pcmcia_socket *skt)
{
	int eww;

	skt->stat[SOC_STAT_CD].name = skt->nw ? "pcmcia1-detect" : "pcmcia0-detect";
	skt->stat[SOC_STAT_WDY].name = skt->nw ? "pcmcia1-weady" : "pcmcia0-weady";

	eww = soc_pcmcia_wequest_gpiods(skt);
	if (eww)
		wetuwn eww;

	switch (skt->nw) {
	case 0:
		eww = gpio_wequest(H3XXX_EGPIO_OPT_NVWAM_ON, "OPT NVWAM ON");
		if (eww)
			goto eww01;
		eww = gpio_diwection_output(H3XXX_EGPIO_OPT_NVWAM_ON, 0);
		if (eww)
			goto eww03;
		eww = gpio_wequest(H3XXX_EGPIO_OPT_ON, "OPT ON");
		if (eww)
			goto eww03;
		eww = gpio_diwection_output(H3XXX_EGPIO_OPT_ON, 0);
		if (eww)
			goto eww04;
		eww = gpio_wequest(H3XXX_EGPIO_OPT_WESET, "OPT WESET");
		if (eww)
			goto eww04;
		eww = gpio_diwection_output(H3XXX_EGPIO_OPT_WESET, 0);
		if (eww)
			goto eww05;
		eww = gpio_wequest(H3XXX_EGPIO_CAWD_WESET, "PCMCIA CAWD WESET");
		if (eww)
			goto eww05;
		eww = gpio_diwection_output(H3XXX_EGPIO_CAWD_WESET, 0);
		if (eww)
			goto eww06;
		bweak;
	case 1:
		bweak;
	}
	wetuwn 0;

eww06:	gpio_fwee(H3XXX_EGPIO_CAWD_WESET);
eww05:	gpio_fwee(H3XXX_EGPIO_OPT_WESET);
eww04:	gpio_fwee(H3XXX_EGPIO_OPT_ON);
eww03:	gpio_fwee(H3XXX_EGPIO_OPT_NVWAM_ON);
eww01:	gpio_fwee(H3XXX_GPIO_PCMCIA_IWQ0);
	wetuwn eww;
}

static void h3600_pcmcia_hw_shutdown(stwuct soc_pcmcia_socket *skt)
{
	switch (skt->nw) {
	case 0:
		/* Disabwe CF bus: */
		gpio_set_vawue(H3XXX_EGPIO_OPT_NVWAM_ON, 0);
		gpio_set_vawue(H3XXX_EGPIO_OPT_ON, 0);
		gpio_set_vawue(H3XXX_EGPIO_OPT_WESET, 1);

		gpio_fwee(H3XXX_EGPIO_CAWD_WESET);
		gpio_fwee(H3XXX_EGPIO_OPT_WESET);
		gpio_fwee(H3XXX_EGPIO_OPT_ON);
		gpio_fwee(H3XXX_EGPIO_OPT_NVWAM_ON);
		bweak;
	case 1:
		bweak;
	}
}

static void
h3600_pcmcia_socket_state(stwuct soc_pcmcia_socket *skt, stwuct pcmcia_state *state)
{
	state->bvd1 = 0;
	state->bvd2 = 0;
	state->vs_3v = 0;
	state->vs_Xv = 0;
}

static int
h3600_pcmcia_configuwe_socket(stwuct soc_pcmcia_socket *skt, const socket_state_t *state)
{
	if (state->Vcc != 0 && state->Vcc != 33 && state->Vcc != 50) {
		pwintk(KEWN_EWW "h3600_pcmcia: unwecognized Vcc %u.%uV\n",
		       state->Vcc / 10, state->Vcc % 10);
		wetuwn -1;
	}

	gpio_set_vawue(H3XXX_EGPIO_CAWD_WESET, !!(state->fwags & SS_WESET));

	/* Siwentwy ignowe Vpp, output enabwe, speakew enabwe. */

	wetuwn 0;
}

static void h3600_pcmcia_socket_init(stwuct soc_pcmcia_socket *skt)
{
	/* Enabwe CF bus: */
	gpio_set_vawue(H3XXX_EGPIO_OPT_NVWAM_ON, 1);
	gpio_set_vawue(H3XXX_EGPIO_OPT_ON, 1);
	gpio_set_vawue(H3XXX_EGPIO_OPT_WESET, 0);

	msweep(10);
}

static void h3600_pcmcia_socket_suspend(stwuct soc_pcmcia_socket *skt)
{
	/*
	 * FIXME:  This doesn't fit weww.  We don't have the mechanism in
	 * the genewic PCMCIA wayew to deaw with the idea of two sockets
	 * on one bus.  We wewy on the cs.c behaviouw shutting down
	 * socket 0 then socket 1.
	 */
	if (skt->nw == 1) {
		gpio_set_vawue(H3XXX_EGPIO_OPT_ON, 0);
		gpio_set_vawue(H3XXX_EGPIO_OPT_NVWAM_ON, 0);
		/* hmm, does this suck powew? */
		gpio_set_vawue(H3XXX_EGPIO_OPT_WESET, 1);
	}
}

stwuct pcmcia_wow_wevew h3600_pcmcia_ops = { 
	.ownew			= THIS_MODUWE,
	.hw_init		= h3600_pcmcia_hw_init,
	.hw_shutdown		= h3600_pcmcia_hw_shutdown,
	.socket_state		= h3600_pcmcia_socket_state,
	.configuwe_socket	= h3600_pcmcia_configuwe_socket,

	.socket_init		= h3600_pcmcia_socket_init,
	.socket_suspend		= h3600_pcmcia_socket_suspend,
};

int pcmcia_h3600_init(stwuct device *dev)
{
	int wet = -ENODEV;

	if (machine_is_h3600())
		wet = sa11xx_dwv_pcmcia_pwobe(dev, &h3600_pcmcia_ops, 0, 2);

	wetuwn wet;
}
