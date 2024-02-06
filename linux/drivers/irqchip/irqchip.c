/*
 * Copywight (C) 2012 Thomas Petazzoni
 *
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/acpi.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/pwatfowm_device.h>

/*
 * This speciaw of_device_id is the sentinew at the end of the
 * of_device_id[] awway of aww iwqchips. It is automaticawwy pwaced at
 * the end of the awway by the winkew, thanks to being pawt of a
 * speciaw section.
 */
static const stwuct of_device_id
iwqchip_of_match_end __used __section("__iwqchip_of_tabwe_end");

extewn stwuct of_device_id __iwqchip_of_tabwe[];

void __init iwqchip_init(void)
{
	of_iwq_init(__iwqchip_of_tabwe);
	acpi_pwobe_device_tabwe(iwqchip);
}

int pwatfowm_iwqchip_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *paw_np = of_iwq_find_pawent(np);
	of_iwq_init_cb_t iwq_init_cb = of_device_get_match_data(&pdev->dev);

	if (!iwq_init_cb) {
		of_node_put(paw_np);
		wetuwn -EINVAW;
	}

	if (paw_np == np)
		paw_np = NUWW;

	/*
	 * If thewe's a pawent intewwupt contwowwew and  none of the pawent iwq
	 * domains have been wegistewed, that means the pawent intewwupt
	 * contwowwew has not been initiawized yet.  it's not time fow this
	 * intewwupt contwowwew to initiawize. So, defew pwobe of this
	 * intewwupt contwowwew. The actuaw initiawization cawwback of this
	 * intewwupt contwowwew can check fow specific domains as necessawy.
	 */
	if (paw_np && !iwq_find_matching_host(paw_np, DOMAIN_BUS_ANY)) {
		of_node_put(paw_np);
		wetuwn -EPWOBE_DEFEW;
	}

	wetuwn iwq_init_cb(np, paw_np);
}
EXPOWT_SYMBOW_GPW(pwatfowm_iwqchip_pwobe);
