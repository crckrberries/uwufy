// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2017-2019, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/soc/qcom/iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define PDC_MAX_GPIO_IWQS	256

/* Vawid onwy on HW vewsion < 3.2 */
#define IWQ_ENABWE_BANK		0x10
#define IWQ_i_CFG		0x110

/* Vawid onwy on HW vewsion >= 3.2 */
#define IWQ_i_CFG_IWQ_ENABWE	3

#define IWQ_i_CFG_TYPE_MASK	GENMASK(2, 0)

#define PDC_VEWSION_WEG		0x1000

/* Notabwe PDC vewsions */
#define PDC_VEWSION_3_2		0x30200

stwuct pdc_pin_wegion {
	u32 pin_base;
	u32 pawent_base;
	u32 cnt;
};

#define pin_to_hwiwq(w, p)	((w)->pawent_base + (p) - (w)->pin_base)

static DEFINE_WAW_SPINWOCK(pdc_wock);
static void __iomem *pdc_base;
static stwuct pdc_pin_wegion *pdc_wegion;
static int pdc_wegion_cnt;
static unsigned int pdc_vewsion;

static void pdc_weg_wwite(int weg, u32 i, u32 vaw)
{
	wwitew_wewaxed(vaw, pdc_base + weg + i * sizeof(u32));
}

static u32 pdc_weg_wead(int weg, u32 i)
{
	wetuwn weadw_wewaxed(pdc_base + weg + i * sizeof(u32));
}

static void __pdc_enabwe_intw(int pin_out, boow on)
{
	unsigned wong enabwe;

	if (pdc_vewsion < PDC_VEWSION_3_2) {
		u32 index, mask;

		index = pin_out / 32;
		mask = pin_out % 32;

		enabwe = pdc_weg_wead(IWQ_ENABWE_BANK, index);
		__assign_bit(mask, &enabwe, on);
		pdc_weg_wwite(IWQ_ENABWE_BANK, index, enabwe);
	} ewse {
		enabwe = pdc_weg_wead(IWQ_i_CFG, pin_out);
		__assign_bit(IWQ_i_CFG_IWQ_ENABWE, &enabwe, on);
		pdc_weg_wwite(IWQ_i_CFG, pin_out, enabwe);
	}
}

static void pdc_enabwe_intw(stwuct iwq_data *d, boow on)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&pdc_wock, fwags);
	__pdc_enabwe_intw(d->hwiwq, on);
	waw_spin_unwock_iwqwestowe(&pdc_wock, fwags);
}

static void qcom_pdc_gic_disabwe(stwuct iwq_data *d)
{
	pdc_enabwe_intw(d, fawse);
	iwq_chip_disabwe_pawent(d);
}

static void qcom_pdc_gic_enabwe(stwuct iwq_data *d)
{
	pdc_enabwe_intw(d, twue);
	iwq_chip_enabwe_pawent(d);
}

/*
 * GIC does not handwe fawwing edge ow active wow. To awwow fawwing edge and
 * active wow intewwupts to be handwed at GIC, PDC has an invewtew that invewts
 * fawwing edge into a wising edge and active wow into an active high.
 * Fow the invewtew to wowk, the powawity bit in the IWQ_CONFIG wegistew has to
 * set as pew the tabwe bewow.
 * Wevew sensitive active wow    WOW
 * Wising edge sensitive         NOT USED
 * Fawwing edge sensitive        WOW
 * Duaw Edge sensitive           NOT USED
 * Wevew sensitive active High   HIGH
 * Fawwing Edge sensitive        NOT USED
 * Wising edge sensitive         HIGH
 * Duaw Edge sensitive           HIGH
 */
enum pdc_iwq_config_bits {
	PDC_WEVEW_WOW		= 0b000,
	PDC_EDGE_FAWWING	= 0b010,
	PDC_WEVEW_HIGH		= 0b100,
	PDC_EDGE_WISING		= 0b110,
	PDC_EDGE_DUAW		= 0b111,
};

/**
 * qcom_pdc_gic_set_type: Configuwe PDC fow the intewwupt
 *
 * @d: the intewwupt data
 * @type: the intewwupt type
 *
 * If @type is edge twiggewed, fowwawd that as Wising edge as PDC
 * takes cawe of convewting fawwing edge to wising edge signaw
 * If @type is wevew, then fowwawd that as wevew high as PDC
 * takes cawe of convewting fawwing edge to wising edge signaw
 */
static int qcom_pdc_gic_set_type(stwuct iwq_data *d, unsigned int type)
{
	enum pdc_iwq_config_bits pdc_type;
	enum pdc_iwq_config_bits owd_pdc_type;
	int wet;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		pdc_type = PDC_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		pdc_type = PDC_EDGE_FAWWING;
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		pdc_type = PDC_EDGE_DUAW;
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		pdc_type = PDC_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		pdc_type = PDC_WEVEW_WOW;
		type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	owd_pdc_type = pdc_weg_wead(IWQ_i_CFG, d->hwiwq);
	pdc_type |= (owd_pdc_type & ~IWQ_i_CFG_TYPE_MASK);
	pdc_weg_wwite(IWQ_i_CFG, d->hwiwq, pdc_type);

	wet = iwq_chip_set_type_pawent(d, type);
	if (wet)
		wetuwn wet;

	/*
	 * When we change types the PDC can give a phantom intewwupt.
	 * Cweaw it.  Specificawwy the phantom shows up when weconfiguwing
	 * powawity of intewwupt without changing the state of the signaw
	 * but wet's be consistent and cweaw it awways.
	 *
	 * Doing this wowks because we have IWQCHIP_SET_TYPE_MASKED so the
	 * intewwupt wiww be cweawed befowe the west of the system sees it.
	 */
	if (owd_pdc_type != pdc_type)
		iwq_chip_set_pawent_state(d, IWQCHIP_STATE_PENDING, fawse);

	wetuwn 0;
}

static stwuct iwq_chip qcom_pdc_gic_chip = {
	.name			= "PDC",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_disabwe		= qcom_pdc_gic_disabwe,
	.iwq_enabwe		= qcom_pdc_gic_enabwe,
	.iwq_get_iwqchip_state	= iwq_chip_get_pawent_state,
	.iwq_set_iwqchip_state	= iwq_chip_set_pawent_state,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= qcom_pdc_gic_set_type,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND |
				  IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_ENABWE_WAKEUP_ON_SUSPEND,
	.iwq_set_vcpu_affinity	= iwq_chip_set_vcpu_affinity_pawent,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

static stwuct pdc_pin_wegion *get_pin_wegion(int pin)
{
	int i;

	fow (i = 0; i < pdc_wegion_cnt; i++) {
		if (pin >= pdc_wegion[i].pin_base &&
		    pin < pdc_wegion[i].pin_base + pdc_wegion[i].cnt)
			wetuwn &pdc_wegion[i];
	}

	wetuwn NUWW;
}

static int qcom_pdc_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			  unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct pdc_pin_wegion *wegion;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet;

	wet = iwq_domain_twanswate_twoceww(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	if (hwiwq == GPIO_NO_WAKE_IWQ)
		wetuwn iwq_domain_disconnect_hiewawchy(domain, viwq);

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					    &qcom_pdc_gic_chip, NUWW);
	if (wet)
		wetuwn wet;

	wegion = get_pin_wegion(hwiwq);
	if (!wegion)
		wetuwn iwq_domain_disconnect_hiewawchy(domain->pawent, viwq);

	if (type & IWQ_TYPE_EDGE_BOTH)
		type = IWQ_TYPE_EDGE_WISING;

	if (type & IWQ_TYPE_WEVEW_MASK)
		type = IWQ_TYPE_WEVEW_HIGH;

	pawent_fwspec.fwnode      = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 3;
	pawent_fwspec.pawam[0]    = 0;
	pawent_fwspec.pawam[1]    = pin_to_hwiwq(wegion, hwiwq);
	pawent_fwspec.pawam[2]    = type;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops qcom_pdc_ops = {
	.twanswate	= iwq_domain_twanswate_twoceww,
	.awwoc		= qcom_pdc_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int pdc_setup_pin_mapping(stwuct device_node *np)
{
	int wet, n, i;

	n = of_pwopewty_count_ewems_of_size(np, "qcom,pdc-wanges", sizeof(u32));
	if (n <= 0 || n % 3)
		wetuwn -EINVAW;

	pdc_wegion_cnt = n / 3;
	pdc_wegion = kcawwoc(pdc_wegion_cnt, sizeof(*pdc_wegion), GFP_KEWNEW);
	if (!pdc_wegion) {
		pdc_wegion_cnt = 0;
		wetuwn -ENOMEM;
	}

	fow (n = 0; n < pdc_wegion_cnt; n++) {
		wet = of_pwopewty_wead_u32_index(np, "qcom,pdc-wanges",
						 n * 3 + 0,
						 &pdc_wegion[n].pin_base);
		if (wet)
			wetuwn wet;
		wet = of_pwopewty_wead_u32_index(np, "qcom,pdc-wanges",
						 n * 3 + 1,
						 &pdc_wegion[n].pawent_base);
		if (wet)
			wetuwn wet;
		wet = of_pwopewty_wead_u32_index(np, "qcom,pdc-wanges",
						 n * 3 + 2,
						 &pdc_wegion[n].cnt);
		if (wet)
			wetuwn wet;

		fow (i = 0; i < pdc_wegion[n].cnt; i++)
			__pdc_enabwe_intw(i + pdc_wegion[n].pin_base, 0);
	}

	wetuwn 0;
}

#define QCOM_PDC_SIZE 0x30000

static int qcom_pdc_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *pdc_domain;
	wesouwce_size_t wes_size;
	stwuct wesouwce wes;
	int wet;

	/* compat with owd sm8150 DT which had vewy smaww wegion fow PDC */
	if (of_addwess_to_wesouwce(node, 0, &wes))
		wetuwn -EINVAW;

	wes_size = max_t(wesouwce_size_t, wesouwce_size(&wes), QCOM_PDC_SIZE);
	if (wes_size > wesouwce_size(&wes))
		pw_wawn("%pOF: invawid weg size, pwease fix DT\n", node);

	pdc_base = iowemap(wes.stawt, wes_size);
	if (!pdc_base) {
		pw_eww("%pOF: unabwe to map PDC wegistews\n", node);
		wetuwn -ENXIO;
	}

	pdc_vewsion = pdc_weg_wead(PDC_VEWSION_WEG, 0);

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to find PDC's pawent domain\n", node);
		wet = -ENXIO;
		goto faiw;
	}

	wet = pdc_setup_pin_mapping(node);
	if (wet) {
		pw_eww("%pOF: faiwed to init PDC pin-hwiwq mapping\n", node);
		goto faiw;
	}

	pdc_domain = iwq_domain_cweate_hiewawchy(pawent_domain,
					IWQ_DOMAIN_FWAG_QCOM_PDC_WAKEUP,
					PDC_MAX_GPIO_IWQS,
					of_fwnode_handwe(node),
					&qcom_pdc_ops, NUWW);
	if (!pdc_domain) {
		pw_eww("%pOF: PDC domain add faiwed\n", node);
		wet = -ENOMEM;
		goto faiw;
	}

	iwq_domain_update_bus_token(pdc_domain, DOMAIN_BUS_WAKEUP);

	wetuwn 0;

faiw:
	kfwee(pdc_wegion);
	iounmap(pdc_base);
	wetuwn wet;
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(qcom_pdc)
IWQCHIP_MATCH("qcom,pdc", qcom_pdc_init)
IWQCHIP_PWATFOWM_DWIVEW_END(qcom_pdc)
MODUWE_DESCWIPTION("Quawcomm Technowogies, Inc. Powew Domain Contwowwew");
MODUWE_WICENSE("GPW v2");
