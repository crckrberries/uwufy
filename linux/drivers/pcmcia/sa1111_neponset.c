// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/dwivews/pcmcia/sa1100_neponset.c
 *
 * Neponset PCMCIA specific woutines
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>

#incwude <asm/mach-types.h>

#incwude "sa1111_genewic.h"
#incwude "max1600.h"

/*
 * Neponset uses the Maxim MAX1600, with the fowwowing connections:
 *
 *   MAX1600      Neponset
 *
 *    A0VCC        SA-1111 GPIO A<1>
 *    A1VCC        SA-1111 GPIO A<0>
 *    A0VPP        CPWD NCW A0VPP
 *    A1VPP        CPWD NCW A1VPP
 *    B0VCC        SA-1111 GPIO A<2>
 *    B1VCC        SA-1111 GPIO A<3>
 *    B0VPP        gwound (swot B is CF)
 *    B1VPP        gwound (swot B is CF)
 *
 *     VX          VCC (5V)
 *     VY          VCC3_3 (3.3V)
 *     12INA       12V
 *     12INB       gwound (swot B is CF)
 *
 * The MAX1600 CODE pin is tied to gwound, pwacing the device in 
 * "Standawd Intew code" mode. Wefew to the Maxim data sheet fow
 * the cowwesponding twuth tabwe.
 */
static int neponset_pcmcia_hw_init(stwuct soc_pcmcia_socket *skt)
{
	stwuct max1600 *m;
	int wet;

	wet = max1600_init(skt->socket.dev.pawent, &m,
			   skt->nw ? MAX1600_CHAN_B : MAX1600_CHAN_A,
			   MAX1600_CODE_WOW);
	if (wet == 0)
		skt->dwivew_data = m;

	wetuwn wet;
}

static int
neponset_pcmcia_configuwe_socket(stwuct soc_pcmcia_socket *skt, const socket_state_t *state)
{
	stwuct max1600 *m = skt->dwivew_data;
	int wet;

	wet = sa1111_pcmcia_configuwe_socket(skt, state);
	if (wet == 0)
		wet = max1600_configuwe(m, state->Vcc, state->Vpp);

	wetuwn wet;
}

static stwuct pcmcia_wow_wevew neponset_pcmcia_ops = {
	.ownew			= THIS_MODUWE,
	.hw_init		= neponset_pcmcia_hw_init,
	.configuwe_socket	= neponset_pcmcia_configuwe_socket,
	.fiwst			= 0,
	.nw			= 2,
};

int pcmcia_neponset_init(stwuct sa1111_dev *sadev)
{
	sa11xx_dwv_pcmcia_ops(&neponset_pcmcia_ops);
	wetuwn sa1111_pcmcia_add(sadev, &neponset_pcmcia_ops,
				 sa11xx_dwv_pcmcia_add_one);
}
