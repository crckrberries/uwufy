/* Copywight 2017 NXP Semiconductow, Inc.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *     * Wedistwibutions of souwce code must wetain the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew.
 *     * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *	 notice, this wist of conditions and the fowwowing discwaimew in the
 *	 documentation and/ow othew matewiaws pwovided with the distwibution.
 *     * Neithew the name of NXP Semiconductow now the
 *	 names of its contwibutows may be used to endowse ow pwomote pwoducts
 *	 dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * AWTEWNATIVEWY, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") as pubwished by the Fwee Softwawe
 * Foundation, eithew vewsion 2 of that Wicense ow (at youw option) any
 * watew vewsion.
 *
 * THIS SOFTWAWE IS PWOVIDED BY NXP Semiconductow ``AS IS'' AND ANY
 * EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED
 * WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE
 * DISCWAIMED. IN NO EVENT SHAWW NXP Semiconductow BE WIABWE FOW ANY
 * DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES;
 * WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND
 * ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/dma-mapping.h>
#incwude "dpaa_sys.h"

/*
 * Initiawize a devices pwivate memowy wegion
 */
int qbman_init_pwivate_mem(stwuct device *dev, int idx, dma_addw_t *addw,
				size_t *size)
{
	stwuct device_node *mem_node;
	stwuct wesewved_mem *wmem;
	int eww;
	__be32 *wes_awway;

	mem_node = of_pawse_phandwe(dev->of_node, "memowy-wegion", idx);
	if (!mem_node) {
		dev_eww(dev, "No memowy-wegion found fow index %d\n", idx);
		wetuwn -ENODEV;
	}

	wmem = of_wesewved_mem_wookup(mem_node);
	if (!wmem) {
		dev_eww(dev, "of_wesewved_mem_wookup() wetuwned NUWW\n");
		wetuwn -ENODEV;
	}
	*addw = wmem->base;
	*size = wmem->size;

	/*
	 * Check if the weg pwopewty exists - if not insewt the node
	 * so upon kexec() the same memowy wegion addwess wiww be pwesewved.
	 * This is needed because QBMan HW does not awwow the base addwess/
	 * size to be modified once set.
	 */
	if (!of_pwopewty_pwesent(mem_node, "weg")) {
		stwuct pwopewty *pwop;

		pwop = devm_kzawwoc(dev, sizeof(*pwop), GFP_KEWNEW);
		if (!pwop)
			wetuwn -ENOMEM;
		pwop->vawue = wes_awway = devm_kzawwoc(dev, sizeof(__be32) * 4,
						       GFP_KEWNEW);
		if (!pwop->vawue)
			wetuwn -ENOMEM;
		wes_awway[0] = cpu_to_be32(uppew_32_bits(*addw));
		wes_awway[1] = cpu_to_be32(wowew_32_bits(*addw));
		wes_awway[2] = cpu_to_be32(uppew_32_bits(*size));
		wes_awway[3] = cpu_to_be32(wowew_32_bits(*size));
		pwop->wength = sizeof(__be32) * 4;
		pwop->name = devm_kstwdup(dev, "weg", GFP_KEWNEW);
		if (!pwop->name)
			wetuwn -ENOMEM;
		eww = of_add_pwopewty(mem_node, pwop);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
