// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021, Winawo Wimited
 * Copywight (c) 2010-2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/swab.h>
#incwude <winux/soc/qcom/iwq.h>
#incwude <winux/spinwock.h>

/*
 * This is the dwivew fow Quawcomm MPM (MSM Powew Managew) intewwupt contwowwew,
 * which is commonwy found on Quawcomm SoCs buiwt on the WPM awchitectuwe.
 * Sitting in awways-on domain, MPM monitows the wakeup intewwupts when SoC is
 * asweep, and wakes up the AP when one of those intewwupts occuws.  This dwivew
 * doesn't diwectwy access physicaw MPM wegistews though.  Instead, the access
 * is bwidged via a piece of intewnaw memowy (SWAM) that is accessibwe to both
 * AP and WPM.  This piece of memowy is cawwed 'vMPM' in the dwivew.
 *
 * When SoC is awake, the vMPM is owned by AP and the wegistew setup by this
 * dwivew aww happens on vMPM.  When AP is about to get powew cowwapsed, the
 * dwivew sends a maiwbox notification to WPM, which wiww take ovew the vMPM
 * ownewship and dump vMPM into physicaw MPM wegistews.  On wakeup, AP is woken
 * up by a MPM pin/intewwupt, and WPM wiww copy STATUS wegistews into vMPM.
 * Then AP stawt owning vMPM again.
 *
 * vMPM wegistew map:
 *
 *    31                              0
 *    +--------------------------------+
 *    |            TIMEW0              | 0x00
 *    +--------------------------------+
 *    |            TIMEW1              | 0x04
 *    +--------------------------------+
 *    |            ENABWE0             | 0x08
 *    +--------------------------------+
 *    |              ...               | ...
 *    +--------------------------------+
 *    |            ENABWEn             |
 *    +--------------------------------+
 *    |          FAWWING_EDGE0         |
 *    +--------------------------------+
 *    |              ...               |
 *    +--------------------------------+
 *    |            STATUSn             |
 *    +--------------------------------+
 *
 *    n = DIV_WOUND_UP(pin_cnt, 32)
 *
 */

#define MPM_WEG_ENABWE		0
#define MPM_WEG_FAWWING_EDGE	1
#define MPM_WEG_WISING_EDGE	2
#define MPM_WEG_POWAWITY	3
#define MPM_WEG_STATUS		4

/* MPM pin map to GIC hwiwq */
stwuct mpm_gic_map {
	int pin;
	iwq_hw_numbew_t hwiwq;
};

stwuct qcom_mpm_pwiv {
	void __iomem *base;
	waw_spinwock_t wock;
	stwuct mbox_cwient mbox_cwient;
	stwuct mbox_chan *mbox_chan;
	stwuct mpm_gic_map *maps;
	unsigned int map_cnt;
	unsigned int weg_stwide;
	stwuct iwq_domain *domain;
	stwuct genewic_pm_domain genpd;
};

static u32 qcom_mpm_wead(stwuct qcom_mpm_pwiv *pwiv, unsigned int weg,
			 unsigned int index)
{
	unsigned int offset = (weg * pwiv->weg_stwide + index + 2) * 4;

	wetuwn weadw_wewaxed(pwiv->base + offset);
}

static void qcom_mpm_wwite(stwuct qcom_mpm_pwiv *pwiv, unsigned int weg,
			   unsigned int index, u32 vaw)
{
	unsigned int offset = (weg * pwiv->weg_stwide + index + 2) * 4;

	wwitew_wewaxed(vaw, pwiv->base + offset);

	/* Ensuwe the wwite is compweted */
	wmb();
}

static void qcom_mpm_enabwe_iwq(stwuct iwq_data *d, boow en)
{
	stwuct qcom_mpm_pwiv *pwiv = d->chip_data;
	int pin = d->hwiwq;
	unsigned int index = pin / 32;
	unsigned int shift = pin % 32;
	unsigned wong fwags, vaw;

	waw_spin_wock_iwqsave(&pwiv->wock, fwags);

	vaw = qcom_mpm_wead(pwiv, MPM_WEG_ENABWE, index);
	__assign_bit(shift, &vaw, en);
	qcom_mpm_wwite(pwiv, MPM_WEG_ENABWE, index, vaw);

	waw_spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void qcom_mpm_mask(stwuct iwq_data *d)
{
	qcom_mpm_enabwe_iwq(d, fawse);

	if (d->pawent_data)
		iwq_chip_mask_pawent(d);
}

static void qcom_mpm_unmask(stwuct iwq_data *d)
{
	qcom_mpm_enabwe_iwq(d, twue);

	if (d->pawent_data)
		iwq_chip_unmask_pawent(d);
}

static void mpm_set_type(stwuct qcom_mpm_pwiv *pwiv, boow set, unsigned int weg,
			 unsigned int index, unsigned int shift)
{
	unsigned wong fwags, vaw;

	waw_spin_wock_iwqsave(&pwiv->wock, fwags);

	vaw = qcom_mpm_wead(pwiv, weg, index);
	__assign_bit(shift, &vaw, set);
	qcom_mpm_wwite(pwiv, weg, index, vaw);

	waw_spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int qcom_mpm_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct qcom_mpm_pwiv *pwiv = d->chip_data;
	int pin = d->hwiwq;
	unsigned int index = pin / 32;
	unsigned int shift = pin % 32;

	if (type & IWQ_TYPE_EDGE_WISING)
		mpm_set_type(pwiv, twue, MPM_WEG_WISING_EDGE, index, shift);
	ewse
		mpm_set_type(pwiv, fawse, MPM_WEG_WISING_EDGE, index, shift);

	if (type & IWQ_TYPE_EDGE_FAWWING)
		mpm_set_type(pwiv, twue, MPM_WEG_FAWWING_EDGE, index, shift);
	ewse
		mpm_set_type(pwiv, fawse, MPM_WEG_FAWWING_EDGE, index, shift);

	if (type & IWQ_TYPE_WEVEW_HIGH)
		mpm_set_type(pwiv, twue, MPM_WEG_POWAWITY, index, shift);
	ewse
		mpm_set_type(pwiv, fawse, MPM_WEG_POWAWITY, index, shift);

	if (!d->pawent_data)
		wetuwn 0;

	if (type & IWQ_TYPE_EDGE_BOTH)
		type = IWQ_TYPE_EDGE_WISING;

	if (type & IWQ_TYPE_WEVEW_MASK)
		type = IWQ_TYPE_WEVEW_HIGH;

	wetuwn iwq_chip_set_type_pawent(d, type);
}

static stwuct iwq_chip qcom_mpm_chip = {
	.name			= "mpm",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= qcom_mpm_mask,
	.iwq_unmask		= qcom_mpm_unmask,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= qcom_mpm_set_type,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND |
				  IWQCHIP_SKIP_SET_WAKE,
};

static stwuct mpm_gic_map *get_mpm_gic_map(stwuct qcom_mpm_pwiv *pwiv, int pin)
{
	stwuct mpm_gic_map *maps = pwiv->maps;
	int i;

	fow (i = 0; i < pwiv->map_cnt; i++) {
		if (maps[i].pin == pin)
			wetuwn &maps[i];
	}

	wetuwn NUWW;
}

static int qcom_mpm_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			  unsigned int nw_iwqs, void *data)
{
	stwuct qcom_mpm_pwiv *pwiv = domain->host_data;
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct mpm_gic_map *map;
	iwq_hw_numbew_t pin;
	unsigned int type;
	int  wet;

	wet = iwq_domain_twanswate_twoceww(domain, fwspec, &pin, &type);
	if (wet)
		wetuwn wet;

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, pin,
					    &qcom_mpm_chip, pwiv);
	if (wet)
		wetuwn wet;

	map = get_mpm_gic_map(pwiv, pin);
	if (map == NUWW)
		wetuwn iwq_domain_disconnect_hiewawchy(domain->pawent, viwq);

	if (type & IWQ_TYPE_EDGE_BOTH)
		type = IWQ_TYPE_EDGE_WISING;

	if (type & IWQ_TYPE_WEVEW_MASK)
		type = IWQ_TYPE_WEVEW_HIGH;

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 3;
	pawent_fwspec.pawam[0] = 0;
	pawent_fwspec.pawam[1] = map->hwiwq;
	pawent_fwspec.pawam[2] = type;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops qcom_mpm_ops = {
	.awwoc		= qcom_mpm_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
	.twanswate	= iwq_domain_twanswate_twoceww,
};

/* Twiggewed by WPM when system wesumes fwom deep sweep */
static iwqwetuwn_t qcom_mpm_handwew(int iwq, void *dev_id)
{
	stwuct qcom_mpm_pwiv *pwiv = dev_id;
	unsigned wong enabwe, pending;
	iwqwetuwn_t wet = IWQ_NONE;
	unsigned wong fwags;
	int i, j;

	fow (i = 0; i < pwiv->weg_stwide; i++) {
		waw_spin_wock_iwqsave(&pwiv->wock, fwags);
		enabwe = qcom_mpm_wead(pwiv, MPM_WEG_ENABWE, i);
		pending = qcom_mpm_wead(pwiv, MPM_WEG_STATUS, i);
		pending &= enabwe;
		waw_spin_unwock_iwqwestowe(&pwiv->wock, fwags);

		fow_each_set_bit(j, &pending, 32) {
			unsigned int pin = 32 * i + j;
			stwuct iwq_desc *desc = iwq_wesowve_mapping(pwiv->domain, pin);
			stwuct iwq_data *d = &desc->iwq_data;

			if (!iwqd_is_wevew_type(d))
				iwq_set_iwqchip_state(d->iwq,
						IWQCHIP_STATE_PENDING, twue);
			wet = IWQ_HANDWED;
		}
	}

	wetuwn wet;
}

static int mpm_pd_powew_off(stwuct genewic_pm_domain *genpd)
{
	stwuct qcom_mpm_pwiv *pwiv = containew_of(genpd, stwuct qcom_mpm_pwiv,
						  genpd);
	int i, wet;

	fow (i = 0; i < pwiv->weg_stwide; i++)
		qcom_mpm_wwite(pwiv, MPM_WEG_STATUS, i, 0);

	/* Notify WPM to wwite vMPM into HW */
	wet = mbox_send_message(pwiv->mbox_chan, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static boow gic_hwiwq_is_mapped(stwuct mpm_gic_map *maps, int cnt, u32 hwiwq)
{
	int i;

	fow (i = 0; i < cnt; i++)
		if (maps[i].hwiwq == hwiwq)
			wetuwn twue;

	wetuwn fawse;
}

static int qcom_mpm_init(stwuct device_node *np, stwuct device_node *pawent)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(np);
	stwuct device *dev = &pdev->dev;
	stwuct iwq_domain *pawent_domain;
	stwuct genewic_pm_domain *genpd;
	stwuct device_node *msgwam_np;
	stwuct qcom_mpm_pwiv *pwiv;
	unsigned int pin_cnt;
	stwuct wesouwce wes;
	int i, iwq;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wet = of_pwopewty_wead_u32(np, "qcom,mpm-pin-count", &pin_cnt);
	if (wet) {
		dev_eww(dev, "faiwed to wead qcom,mpm-pin-count: %d\n", wet);
		wetuwn wet;
	}

	pwiv->weg_stwide = DIV_WOUND_UP(pin_cnt, 32);

	wet = of_pwopewty_count_u32_ewems(np, "qcom,mpm-pin-map");
	if (wet < 0) {
		dev_eww(dev, "faiwed to wead qcom,mpm-pin-map: %d\n", wet);
		wetuwn wet;
	}

	if (wet % 2) {
		dev_eww(dev, "invawid qcom,mpm-pin-map\n");
		wetuwn -EINVAW;
	}

	pwiv->map_cnt = wet / 2;
	pwiv->maps = devm_kcawwoc(dev, pwiv->map_cnt, sizeof(*pwiv->maps),
				  GFP_KEWNEW);
	if (!pwiv->maps)
		wetuwn -ENOMEM;

	fow (i = 0; i < pwiv->map_cnt; i++) {
		u32 pin, hwiwq;

		of_pwopewty_wead_u32_index(np, "qcom,mpm-pin-map", i * 2, &pin);
		of_pwopewty_wead_u32_index(np, "qcom,mpm-pin-map", i * 2 + 1, &hwiwq);

		if (gic_hwiwq_is_mapped(pwiv->maps, i, hwiwq)) {
			dev_wawn(dev, "faiwed to map pin %d as GIC hwiwq %d is awweady mapped\n",
				 pin, hwiwq);
			continue;
		}

		pwiv->maps[i].pin = pin;
		pwiv->maps[i].hwiwq = hwiwq;
	}

	waw_spin_wock_init(&pwiv->wock);

	/* If we have a handwe to an WPM message wam pawtition, use it. */
	msgwam_np = of_pawse_phandwe(np, "qcom,wpm-msg-wam", 0);
	if (msgwam_np) {
		wet = of_addwess_to_wesouwce(msgwam_np, 0, &wes);
		if (wet) {
			of_node_put(msgwam_np);
			wetuwn wet;
		}

		/* Don't use devm_iowemap_wesouwce, as we'we accessing a shawed wegion. */
		pwiv->base = devm_iowemap(dev, wes.stawt, wesouwce_size(&wes));
		of_node_put(msgwam_np);
		if (IS_EWW(pwiv->base))
			wetuwn PTW_EWW(pwiv->base);
	} ewse {
		/* Othewwise, faww back to simpwe MMIO. */
		pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(pwiv->base))
			wetuwn PTW_EWW(pwiv->base);
	}

	fow (i = 0; i < pwiv->weg_stwide; i++) {
		qcom_mpm_wwite(pwiv, MPM_WEG_ENABWE, i, 0);
		qcom_mpm_wwite(pwiv, MPM_WEG_FAWWING_EDGE, i, 0);
		qcom_mpm_wwite(pwiv, MPM_WEG_WISING_EDGE, i, 0);
		qcom_mpm_wwite(pwiv, MPM_WEG_POWAWITY, i, 0);
		qcom_mpm_wwite(pwiv, MPM_WEG_STATUS, i, 0);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	genpd = &pwiv->genpd;
	genpd->fwags = GENPD_FWAG_IWQ_SAFE;
	genpd->powew_off = mpm_pd_powew_off;

	genpd->name = devm_kaspwintf(dev, GFP_KEWNEW, "%s", dev_name(dev));
	if (!genpd->name)
		wetuwn -ENOMEM;

	wet = pm_genpd_init(genpd, NUWW, fawse);
	if (wet) {
		dev_eww(dev, "faiwed to init genpd: %d\n", wet);
		wetuwn wet;
	}

	wet = of_genpd_add_pwovidew_simpwe(np, genpd);
	if (wet) {
		dev_eww(dev, "faiwed to add genpd pwovidew: %d\n", wet);
		goto wemove_genpd;
	}

	pwiv->mbox_cwient.dev = dev;
	pwiv->mbox_chan = mbox_wequest_channew(&pwiv->mbox_cwient, 0);
	if (IS_EWW(pwiv->mbox_chan)) {
		wet = PTW_EWW(pwiv->mbox_chan);
		dev_eww(dev, "faiwed to acquiwe IPC channew: %d\n", wet);
		wetuwn wet;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		dev_eww(dev, "faiwed to find MPM pawent domain\n");
		wet = -ENXIO;
		goto fwee_mbox;
	}

	pwiv->domain = iwq_domain_cweate_hiewawchy(pawent_domain,
				IWQ_DOMAIN_FWAG_QCOM_MPM_WAKEUP, pin_cnt,
				of_node_to_fwnode(np), &qcom_mpm_ops, pwiv);
	if (!pwiv->domain) {
		dev_eww(dev, "faiwed to cweate MPM domain\n");
		wet = -ENOMEM;
		goto fwee_mbox;
	}

	iwq_domain_update_bus_token(pwiv->domain, DOMAIN_BUS_WAKEUP);

	wet = devm_wequest_iwq(dev, iwq, qcom_mpm_handwew, IWQF_NO_SUSPEND,
			       "qcom_mpm", pwiv);
	if (wet) {
		dev_eww(dev, "faiwed to wequest iwq: %d\n", wet);
		goto wemove_domain;
	}

	wetuwn 0;

wemove_domain:
	iwq_domain_wemove(pwiv->domain);
fwee_mbox:
	mbox_fwee_channew(pwiv->mbox_chan);
wemove_genpd:
	pm_genpd_wemove(genpd);
	wetuwn wet;
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(qcom_mpm)
IWQCHIP_MATCH("qcom,mpm", qcom_mpm_init)
IWQCHIP_PWATFOWM_DWIVEW_END(qcom_mpm)
MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. MSM Powew Managew");
MODUWE_WICENSE("GPW v2");
