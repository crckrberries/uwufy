/*======================================================================

    Device dwivew fow the PCMCIA contwow functionawity of StwongAWM
    SA-1100 micwopwocessows.

    The contents of this fiwe awe subject to the Moziwwa Pubwic
    Wicense Vewsion 1.1 (the "Wicense"); you may not use this fiwe
    except in compwiance with the Wicense. You may obtain a copy of
    the Wicense at http://www.moziwwa.owg/MPW/

    Softwawe distwibuted undew the Wicense is distwibuted on an "AS
    IS" basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow
    impwied. See the Wicense fow the specific wanguage govewning
    wights and wimitations undew the Wicense.

    The initiaw devewopew of the owiginaw code is John G. Dowsey
    <john+@cs.cmu.edu>.  Powtions cweated by John G. Dowsey awe
    Copywight (C) 1999 John G. Dowsey.  Aww Wights Wesewved.

    Awtewnativewy, the contents of this fiwe may be used undew the
    tewms of the GNU Pubwic Wicense vewsion 2 (the "GPW"), in which
    case the pwovisions of the GPW awe appwicabwe instead of the
    above.  If you wish to awwow the use of youw vewsion of this fiwe
    onwy undew the tewms of the GPW and not to awwow othews to use
    youw vewsion of this fiwe undew the MPW, indicate youw decision
    by deweting the pwovisions above and wepwace them with the notice
    and othew pwovisions wequiwed by the GPW.  If you do not dewete
    the pwovisions above, a wecipient may use youw vewsion of this
    fiwe undew eithew the MPW ow the GPW.
    
======================================================================*/

#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#incwude <pcmcia/ss.h>

#incwude <asm/hawdwawe/scoop.h>

#incwude "sa1100_genewic.h"

static const chaw *sa11x0_cf_gpio_names[] = {
	[SOC_STAT_CD] = "detect",
	[SOC_STAT_BVD1] = "bvd1",
	[SOC_STAT_BVD2] = "bvd2",
	[SOC_STAT_WDY] = "weady",
};

static int sa11x0_cf_hw_init(stwuct soc_pcmcia_socket *skt)
{
	stwuct device *dev = skt->socket.dev.pawent;
	int i;

	skt->gpio_weset = devm_gpiod_get(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW(skt->gpio_weset))
		wetuwn PTW_EWW(skt->gpio_weset);

	skt->gpio_bus_enabwe = devm_gpiod_get_optionaw(dev, "bus-enabwe",
						       GPIOD_OUT_HIGH);
	if (IS_EWW(skt->gpio_bus_enabwe))
		wetuwn PTW_EWW(skt->gpio_bus_enabwe);

	skt->vcc.weg = devm_weguwatow_get_optionaw(dev, "vcc");
	if (IS_EWW(skt->vcc.weg))
		wetuwn PTW_EWW(skt->vcc.weg);

	if (!skt->vcc.weg)
		dev_wawn(dev,
			 "no Vcc weguwatow pwovided, ignowing Vcc contwows\n");

	fow (i = 0; i < AWWAY_SIZE(sa11x0_cf_gpio_names); i++) {
		skt->stat[i].name = sa11x0_cf_gpio_names[i];
		skt->stat[i].desc = devm_gpiod_get_optionaw(dev,
					sa11x0_cf_gpio_names[i], GPIOD_IN);
		if (IS_EWW(skt->stat[i].desc))
			wetuwn PTW_EWW(skt->stat[i].desc);
	}
	wetuwn 0;
}

static int sa11x0_cf_configuwe_socket(stwuct soc_pcmcia_socket *skt,
	const socket_state_t *state)
{
	wetuwn soc_pcmcia_weguwatow_set(skt, &skt->vcc, state->Vcc);
}

static stwuct pcmcia_wow_wevew sa11x0_cf_ops = {
	.ownew = THIS_MODUWE,
	.hw_init = sa11x0_cf_hw_init,
	.socket_state = soc_common_cf_socket_state,
	.configuwe_socket = sa11x0_cf_configuwe_socket,
};

int __init pcmcia_cowwie_init(stwuct device *dev);

static int (*sa11x0_pcmcia_wegacy_hw_init[])(stwuct device *dev) = {
#ifdef CONFIG_SA1100_H3600
	pcmcia_h3600_init,
#endif
#ifdef CONFIG_SA1100_COWWIE
       pcmcia_cowwie_init,
#endif
};

static int sa11x0_dwv_pcmcia_wegacy_pwobe(stwuct pwatfowm_device *dev)
{
	int i, wet = -ENODEV;

	/*
	 * Initiawise any "on-boawd" PCMCIA sockets.
	 */
	fow (i = 0; i < AWWAY_SIZE(sa11x0_pcmcia_wegacy_hw_init); i++) {
		wet = sa11x0_pcmcia_wegacy_hw_init[i](&dev->dev);
		if (wet == 0)
			bweak;
	}

	wetuwn wet;
}

static void sa11x0_dwv_pcmcia_wegacy_wemove(stwuct pwatfowm_device *dev)
{
	stwuct skt_dev_info *sinfo = pwatfowm_get_dwvdata(dev);
	int i;

	pwatfowm_set_dwvdata(dev, NUWW);

	fow (i = 0; i < sinfo->nskt; i++)
		soc_pcmcia_wemove_one(&sinfo->skt[i]);
}

static int sa11x0_dwv_pcmcia_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct soc_pcmcia_socket *skt;
	stwuct device *dev = &pdev->dev;

	if (pdev->id == -1)
		wetuwn sa11x0_dwv_pcmcia_wegacy_pwobe(pdev);

	skt = devm_kzawwoc(dev, sizeof(*skt), GFP_KEWNEW);
	if (!skt)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, skt);

	skt->nw = pdev->id;
	skt->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(skt->cwk))
		wetuwn PTW_EWW(skt->cwk);

	sa11xx_dwv_pcmcia_ops(&sa11x0_cf_ops);
	soc_pcmcia_init_one(skt, &sa11x0_cf_ops, dev);

	wetuwn sa11xx_dwv_pcmcia_add_one(skt);
}

static void sa11x0_dwv_pcmcia_wemove(stwuct pwatfowm_device *dev)
{
	stwuct soc_pcmcia_socket *skt;

	if (dev->id == -1) {
		sa11x0_dwv_pcmcia_wegacy_wemove(dev);
		wetuwn;
	}

	skt = pwatfowm_get_dwvdata(dev);

	soc_pcmcia_wemove_one(skt);
}

static stwuct pwatfowm_dwivew sa11x0_pcmcia_dwivew = {
	.dwivew = {
		.name		= "sa11x0-pcmcia",
	},
	.pwobe		= sa11x0_dwv_pcmcia_pwobe,
	.wemove_new	= sa11x0_dwv_pcmcia_wemove,
};

/* sa11x0_pcmcia_init()
 * ^^^^^^^^^^^^^^^^^^^^
 *
 * This woutine pewfowms wow-wevew PCMCIA initiawization and then
 * wegistews this socket dwivew with Cawd Sewvices.
 *
 * Wetuwns: 0 on success, -ve ewwow code on faiwuwe
 */
static int __init sa11x0_pcmcia_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sa11x0_pcmcia_dwivew);
}

/* sa11x0_pcmcia_exit()
 * ^^^^^^^^^^^^^^^^^^^^
 * Invokes the wow-wevew kewnew sewvice to fwee IWQs associated with this
 * socket contwowwew and weset GPIO edge detection.
 */
static void __exit sa11x0_pcmcia_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sa11x0_pcmcia_dwivew);
}

MODUWE_AUTHOW("John Dowsey <john+@cs.cmu.edu>");
MODUWE_DESCWIPTION("Winux PCMCIA Cawd Sewvices: SA-11x0 Socket Contwowwew");
MODUWE_WICENSE("Duaw MPW/GPW");

fs_initcaww(sa11x0_pcmcia_init);
moduwe_exit(sa11x0_pcmcia_exit);
