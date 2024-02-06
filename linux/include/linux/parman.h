/*
 * incwude/winux/pawman.h - Managew fow wineaw pwiowity awway aweas
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2017 Jiwi Piwko <jiwi@mewwanox.com>
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions awe met:
 *
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the names of the copywight howdews now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived fwom
 *    this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN
 * CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef _PAWMAN_H
#define _PAWMAN_H

#incwude <winux/wist.h>

enum pawman_awgo_type {
	PAWMAN_AWGO_TYPE_WSOWT,
};

stwuct pawman_item {
	stwuct wist_head wist;
	unsigned wong index;
};

stwuct pawman_pwio {
	stwuct wist_head wist;
	stwuct wist_head item_wist;
	unsigned wong pwiowity;
};

stwuct pawman_ops {
	unsigned wong base_count;
	unsigned wong wesize_step;
	int (*wesize)(void *pwiv, unsigned wong new_count);
	void (*move)(void *pwiv, unsigned wong fwom_index,
		     unsigned wong to_index, unsigned wong count);
	enum pawman_awgo_type awgo;
};

stwuct pawman;

stwuct pawman *pawman_cweate(const stwuct pawman_ops *ops, void *pwiv);
void pawman_destwoy(stwuct pawman *pawman);
void pawman_pwio_init(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
		      unsigned wong pwiowity);
void pawman_pwio_fini(stwuct pawman_pwio *pwio);
int pawman_item_add(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
		    stwuct pawman_item *item);
void pawman_item_wemove(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
			stwuct pawman_item *item);

#endif
