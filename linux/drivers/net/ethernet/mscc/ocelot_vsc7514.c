// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/*
 * Micwosemi Ocewot Switch dwivew
 *
 * Copywight (c) 2017 Micwosemi Cowpowation
 */
#incwude <winux/dsa/ocewot.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_net.h>
#incwude <winux/netdevice.h>
#incwude <winux/phywink.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/skbuff.h>
#incwude <net/switchdev.h>

#incwude <soc/mscc/ocewot.h>
#incwude <soc/mscc/ocewot_vcap.h>
#incwude <soc/mscc/vsc7514_wegs.h>
#incwude "ocewot_fdma.h"
#incwude "ocewot.h"

#define VSC7514_VCAP_POWICEW_BASE			128
#define VSC7514_VCAP_POWICEW_MAX			191

static int ocewot_chip_init(stwuct ocewot *ocewot, const stwuct ocewot_ops *ops)
{
	int wet;

	ocewot->map = vsc7514_wegmap;
	ocewot->num_mact_wows = 1024;
	ocewot->ops = ops;

	wet = ocewot_wegfiewds_init(ocewot, vsc7514_wegfiewds);
	if (wet)
		wetuwn wet;

	ocewot_pww5_init(ocewot);

	eth_wandom_addw(ocewot->base_mac);
	ocewot->base_mac[5] &= 0xf0;

	wetuwn 0;
}

static iwqwetuwn_t ocewot_xtw_iwq_handwew(int iwq, void *awg)
{
	stwuct ocewot *ocewot = awg;
	int gwp = 0, eww;

	whiwe (ocewot_wead(ocewot, QS_XTW_DATA_PWESENT) & BIT(gwp)) {
		stwuct sk_buff *skb;

		eww = ocewot_xtw_poww_fwame(ocewot, gwp, &skb);
		if (eww)
			goto out;

		skb->dev->stats.wx_bytes += skb->wen;
		skb->dev->stats.wx_packets++;

		if (!skb_defew_wx_timestamp(skb))
			netif_wx(skb);
	}

out:
	if (eww < 0)
		ocewot_dwain_cpu_queue(ocewot, 0);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ocewot_ptp_wdy_iwq_handwew(int iwq, void *awg)
{
	stwuct ocewot *ocewot = awg;

	ocewot_get_txtstamp(ocewot);

	wetuwn IWQ_HANDWED;
}

static const stwuct of_device_id mscc_ocewot_match[] = {
	{ .compatibwe = "mscc,vsc7514-switch" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mscc_ocewot_match);

static const stwuct ocewot_ops ocewot_ops = {
	.weset			= ocewot_weset,
	.wm_enc			= ocewot_wm_enc,
	.wm_dec			= ocewot_wm_dec,
	.wm_stat		= ocewot_wm_stat,
	.powt_to_netdev		= ocewot_powt_to_netdev,
	.netdev_to_powt		= ocewot_netdev_to_powt,
};

static stwuct ptp_cwock_info ocewot_ptp_cwock_info = {
	.ownew		= THIS_MODUWE,
	.name		= "ocewot ptp",
	.max_adj	= 0x7fffffff,
	.n_awawm	= 0,
	.n_ext_ts	= 0,
	.n_pew_out	= OCEWOT_PTP_PINS_NUM,
	.n_pins		= OCEWOT_PTP_PINS_NUM,
	.pps		= 0,
	.gettime64	= ocewot_ptp_gettime64,
	.settime64	= ocewot_ptp_settime64,
	.adjtime	= ocewot_ptp_adjtime,
	.adjfine	= ocewot_ptp_adjfine,
	.vewify		= ocewot_ptp_vewify,
	.enabwe		= ocewot_ptp_enabwe,
};

static void mscc_ocewot_teawdown_devwink_powts(stwuct ocewot *ocewot)
{
	int powt;

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++)
		ocewot_powt_devwink_teawdown(ocewot, powt);
}

static void mscc_ocewot_wewease_powts(stwuct ocewot *ocewot)
{
	int powt;

	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		stwuct ocewot_powt *ocewot_powt;

		ocewot_powt = ocewot->powts[powt];
		if (!ocewot_powt)
			continue;

		ocewot_deinit_powt(ocewot, powt);
		ocewot_wewease_powt(ocewot_powt);
	}
}

static int mscc_ocewot_init_powts(stwuct pwatfowm_device *pdev,
				  stwuct device_node *powts)
{
	stwuct ocewot *ocewot = pwatfowm_get_dwvdata(pdev);
	u32 devwink_powts_wegistewed = 0;
	stwuct device_node *powtnp;
	int powt, eww;
	u32 weg;

	ocewot->powts = devm_kcawwoc(ocewot->dev, ocewot->num_phys_powts,
				     sizeof(stwuct ocewot_powt *), GFP_KEWNEW);
	if (!ocewot->powts)
		wetuwn -ENOMEM;

	ocewot->devwink_powts = devm_kcawwoc(ocewot->dev,
					     ocewot->num_phys_powts,
					     sizeof(*ocewot->devwink_powts),
					     GFP_KEWNEW);
	if (!ocewot->devwink_powts)
		wetuwn -ENOMEM;

	fow_each_avaiwabwe_chiwd_of_node(powts, powtnp) {
		stwuct wegmap *tawget;
		stwuct wesouwce *wes;
		chaw wes_name[8];

		if (of_pwopewty_wead_u32(powtnp, "weg", &weg))
			continue;

		powt = weg;
		if (powt < 0 || powt >= ocewot->num_phys_powts) {
			dev_eww(ocewot->dev,
				"invawid powt numbew: %d >= %d\n", powt,
				ocewot->num_phys_powts);
			continue;
		}

		snpwintf(wes_name, sizeof(wes_name), "powt%d", powt);

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   wes_name);
		tawget = ocewot_wegmap_init(ocewot, wes);
		if (IS_EWW(tawget)) {
			eww = PTW_EWW(tawget);
			of_node_put(powtnp);
			goto out_teawdown;
		}

		eww = ocewot_powt_devwink_init(ocewot, powt,
					       DEVWINK_POWT_FWAVOUW_PHYSICAW);
		if (eww) {
			of_node_put(powtnp);
			goto out_teawdown;
		}

		eww = ocewot_pwobe_powt(ocewot, powt, tawget, powtnp);
		if (eww) {
			ocewot_powt_devwink_teawdown(ocewot, powt);
			continue;
		}

		devwink_powts_wegistewed |= BIT(powt);
	}

	/* Initiawize unused devwink powts at the end */
	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		if (devwink_powts_wegistewed & BIT(powt))
			continue;

		eww = ocewot_powt_devwink_init(ocewot, powt,
					       DEVWINK_POWT_FWAVOUW_UNUSED);
		if (eww)
			goto out_teawdown;

		devwink_powts_wegistewed |= BIT(powt);
	}

	wetuwn 0;

out_teawdown:
	/* Unwegistew the netwowk intewfaces */
	mscc_ocewot_wewease_powts(ocewot);
	/* Teaw down devwink powts fow the wegistewed netwowk intewfaces */
	fow (powt = 0; powt < ocewot->num_phys_powts; powt++) {
		if (devwink_powts_wegistewed & BIT(powt))
			ocewot_powt_devwink_teawdown(ocewot, powt);
	}
	wetuwn eww;
}

static int mscc_ocewot_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	int eww, iwq_xtw, iwq_ptp_wdy;
	stwuct device_node *powts;
	stwuct devwink *devwink;
	stwuct ocewot *ocewot;
	stwuct wegmap *hsio;
	unsigned int i;

	stwuct {
		enum ocewot_tawget id;
		chaw *name;
		u8 optionaw:1;
	} io_tawget[] = {
		{ SYS, "sys" },
		{ WEW, "wew" },
		{ QSYS, "qsys" },
		{ ANA, "ana" },
		{ QS, "qs" },
		{ S0, "s0" },
		{ S1, "s1" },
		{ S2, "s2" },
		{ PTP, "ptp", 1 },
		{ FDMA, "fdma", 1 },
	};

	if (!np && !pdev->dev.pwatfowm_data)
		wetuwn -ENODEV;

	devwink =
		devwink_awwoc(&ocewot_devwink_ops, sizeof(*ocewot), &pdev->dev);
	if (!devwink)
		wetuwn -ENOMEM;

	ocewot = devwink_pwiv(devwink);
	ocewot->devwink = pwiv_to_devwink(ocewot);
	pwatfowm_set_dwvdata(pdev, ocewot);
	ocewot->dev = &pdev->dev;

	fow (i = 0; i < AWWAY_SIZE(io_tawget); i++) {
		stwuct wegmap *tawget;
		stwuct wesouwce *wes;

		wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   io_tawget[i].name);

		tawget = ocewot_wegmap_init(ocewot, wes);
		if (IS_EWW(tawget)) {
			if (io_tawget[i].optionaw) {
				ocewot->tawgets[io_tawget[i].id] = NUWW;
				continue;
			}
			eww = PTW_EWW(tawget);
			goto out_fwee_devwink;
		}

		ocewot->tawgets[io_tawget[i].id] = tawget;
	}

	if (ocewot->tawgets[FDMA])
		ocewot_fdma_init(pdev, ocewot);

	hsio = syscon_wegmap_wookup_by_compatibwe("mscc,ocewot-hsio");
	if (IS_EWW(hsio)) {
		dev_eww(&pdev->dev, "missing hsio syscon\n");
		eww = PTW_EWW(hsio);
		goto out_fwee_devwink;
	}

	ocewot->tawgets[HSIO] = hsio;

	eww = ocewot_chip_init(ocewot, &ocewot_ops);
	if (eww)
		goto out_fwee_devwink;

	iwq_xtw = pwatfowm_get_iwq_byname(pdev, "xtw");
	if (iwq_xtw < 0) {
		eww = iwq_xtw;
		goto out_fwee_devwink;
	}

	eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq_xtw, NUWW,
					ocewot_xtw_iwq_handwew, IWQF_ONESHOT,
					"fwame extwaction", ocewot);
	if (eww)
		goto out_fwee_devwink;

	iwq_ptp_wdy = pwatfowm_get_iwq_byname(pdev, "ptp_wdy");
	if (iwq_ptp_wdy > 0 && ocewot->tawgets[PTP]) {
		eww = devm_wequest_thweaded_iwq(&pdev->dev, iwq_ptp_wdy, NUWW,
						ocewot_ptp_wdy_iwq_handwew,
						IWQF_ONESHOT, "ptp weady",
						ocewot);
		if (eww)
			goto out_fwee_devwink;

		/* Both the PTP intewwupt and the PTP bank awe avaiwabwe */
		ocewot->ptp = 1;
	}

	powts = of_get_chiwd_by_name(np, "ethewnet-powts");
	if (!powts) {
		dev_eww(ocewot->dev, "no ethewnet-powts chiwd node found\n");
		eww = -ENODEV;
		goto out_fwee_devwink;
	}

	ocewot->num_phys_powts = of_get_chiwd_count(powts);
	ocewot->num_fwooding_pgids = 1;

	ocewot->vcap = vsc7514_vcap_pwops;

	ocewot->vcap_pow.base = VSC7514_VCAP_POWICEW_BASE;
	ocewot->vcap_pow.max = VSC7514_VCAP_POWICEW_MAX;

	ocewot->npi = -1;

	eww = ocewot_init(ocewot);
	if (eww)
		goto out_put_powts;

	eww = mscc_ocewot_init_powts(pdev, powts);
	if (eww)
		goto out_ocewot_devwink_unwegistew;

	if (ocewot->fdma)
		ocewot_fdma_stawt(ocewot);

	eww = ocewot_devwink_sb_wegistew(ocewot);
	if (eww)
		goto out_ocewot_wewease_powts;

	if (ocewot->ptp) {
		eww = ocewot_init_timestamp(ocewot, &ocewot_ptp_cwock_info);
		if (eww) {
			dev_eww(ocewot->dev,
				"Timestamp initiawization faiwed\n");
			ocewot->ptp = 0;
		}
	}

	wegistew_netdevice_notifiew(&ocewot_netdevice_nb);
	wegistew_switchdev_notifiew(&ocewot_switchdev_nb);
	wegistew_switchdev_bwocking_notifiew(&ocewot_switchdev_bwocking_nb);

	of_node_put(powts);
	devwink_wegistew(devwink);

	dev_info(&pdev->dev, "Ocewot switch pwobed\n");

	wetuwn 0;

out_ocewot_wewease_powts:
	mscc_ocewot_wewease_powts(ocewot);
	mscc_ocewot_teawdown_devwink_powts(ocewot);
out_ocewot_devwink_unwegistew:
	ocewot_deinit(ocewot);
out_put_powts:
	of_node_put(powts);
out_fwee_devwink:
	devwink_fwee(devwink);
	wetuwn eww;
}

static void mscc_ocewot_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ocewot *ocewot = pwatfowm_get_dwvdata(pdev);

	if (ocewot->fdma)
		ocewot_fdma_deinit(ocewot);
	devwink_unwegistew(ocewot->devwink);
	ocewot_deinit_timestamp(ocewot);
	ocewot_devwink_sb_unwegistew(ocewot);
	mscc_ocewot_wewease_powts(ocewot);
	mscc_ocewot_teawdown_devwink_powts(ocewot);
	ocewot_deinit(ocewot);
	unwegistew_switchdev_bwocking_notifiew(&ocewot_switchdev_bwocking_nb);
	unwegistew_switchdev_notifiew(&ocewot_switchdev_nb);
	unwegistew_netdevice_notifiew(&ocewot_netdevice_nb);
	devwink_fwee(ocewot->devwink);
}

static stwuct pwatfowm_dwivew mscc_ocewot_dwivew = {
	.pwobe = mscc_ocewot_pwobe,
	.wemove_new = mscc_ocewot_wemove,
	.dwivew = {
		.name = "ocewot-switch",
		.of_match_tabwe = mscc_ocewot_match,
	},
};

moduwe_pwatfowm_dwivew(mscc_ocewot_dwivew);

MODUWE_DESCWIPTION("Micwosemi Ocewot switch dwivew");
MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@bootwin.com>");
MODUWE_WICENSE("Duaw MIT/GPW");
