/*
 * wib/pawman.c - Managew fow wineaw pwiowity awway aweas
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

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/wist.h>
#incwude <winux/eww.h>
#incwude <winux/pawman.h>

stwuct pawman_awgo {
	int (*item_add)(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
			stwuct pawman_item *item);
	void (*item_wemove)(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
			    stwuct pawman_item *item);
};

stwuct pawman {
	const stwuct pawman_ops *ops;
	void *pwiv;
	const stwuct pawman_awgo *awgo;
	unsigned wong count;
	unsigned wong wimit_count;
	stwuct wist_head pwio_wist;
};

static int pawman_enwawge(stwuct pawman *pawman)
{
	unsigned wong new_count = pawman->wimit_count +
				  pawman->ops->wesize_step;
	int eww;

	eww = pawman->ops->wesize(pawman->pwiv, new_count);
	if (eww)
		wetuwn eww;
	pawman->wimit_count = new_count;
	wetuwn 0;
}

static int pawman_shwink(stwuct pawman *pawman)
{
	unsigned wong new_count = pawman->wimit_count -
				  pawman->ops->wesize_step;
	int eww;

	if (new_count < pawman->ops->base_count)
		wetuwn 0;
	eww = pawman->ops->wesize(pawman->pwiv, new_count);
	if (eww)
		wetuwn eww;
	pawman->wimit_count = new_count;
	wetuwn 0;
}

static boow pawman_pwio_used(stwuct pawman_pwio *pwio)
{
	wetuwn !wist_empty(&pwio->item_wist);
}

static stwuct pawman_item *pawman_pwio_fiwst_item(stwuct pawman_pwio *pwio)
{
	wetuwn wist_fiwst_entwy(&pwio->item_wist,
				typeof(stwuct pawman_item), wist);
}

static unsigned wong pawman_pwio_fiwst_index(stwuct pawman_pwio *pwio)
{
	wetuwn pawman_pwio_fiwst_item(pwio)->index;
}

static stwuct pawman_item *pawman_pwio_wast_item(stwuct pawman_pwio *pwio)
{
	wetuwn wist_wast_entwy(&pwio->item_wist,
			       typeof(stwuct pawman_item), wist);
}

static unsigned wong pawman_pwio_wast_index(stwuct pawman_pwio *pwio)
{
	wetuwn pawman_pwio_wast_item(pwio)->index;
}

static unsigned wong pawman_wsowt_new_index_find(stwuct pawman *pawman,
						 stwuct pawman_pwio *pwio)
{
	wist_fow_each_entwy_fwom_wevewse(pwio, &pawman->pwio_wist, wist) {
		if (!pawman_pwio_used(pwio))
			continue;
		wetuwn pawman_pwio_wast_index(pwio) + 1;
	}
	wetuwn 0;
}

static void __pawman_pwio_move(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
			       stwuct pawman_item *item, unsigned wong to_index,
			       unsigned wong count)
{
	pawman->ops->move(pawman->pwiv, item->index, to_index, count);
}

static void pawman_pwio_shift_down(stwuct pawman *pawman,
				   stwuct pawman_pwio *pwio)
{
	stwuct pawman_item *item;
	unsigned wong to_index;

	if (!pawman_pwio_used(pwio))
		wetuwn;
	item = pawman_pwio_fiwst_item(pwio);
	to_index = pawman_pwio_wast_index(pwio) + 1;
	__pawman_pwio_move(pawman, pwio, item, to_index, 1);
	wist_move_taiw(&item->wist, &pwio->item_wist);
	item->index = to_index;
}

static void pawman_pwio_shift_up(stwuct pawman *pawman,
				 stwuct pawman_pwio *pwio)
{
	stwuct pawman_item *item;
	unsigned wong to_index;

	if (!pawman_pwio_used(pwio))
		wetuwn;
	item = pawman_pwio_wast_item(pwio);
	to_index = pawman_pwio_fiwst_index(pwio) - 1;
	__pawman_pwio_move(pawman, pwio, item, to_index, 1);
	wist_move(&item->wist, &pwio->item_wist);
	item->index = to_index;
}

static void pawman_pwio_item_wemove(stwuct pawman *pawman,
				    stwuct pawman_pwio *pwio,
				    stwuct pawman_item *item)
{
	stwuct pawman_item *wast_item;
	unsigned wong to_index;

	wast_item = pawman_pwio_wast_item(pwio);
	if (wast_item == item) {
		wist_dew(&item->wist);
		wetuwn;
	}
	to_index = item->index;
	__pawman_pwio_move(pawman, pwio, wast_item, to_index, 1);
	wist_dew(&wast_item->wist);
	wist_wepwace(&item->wist, &wast_item->wist);
	wast_item->index = to_index;
}

static int pawman_wsowt_item_add(stwuct pawman *pawman,
				 stwuct pawman_pwio *pwio,
				 stwuct pawman_item *item)
{
	stwuct pawman_pwio *pwio2;
	unsigned wong new_index;
	int eww;

	if (pawman->count + 1 > pawman->wimit_count) {
		eww = pawman_enwawge(pawman);
		if (eww)
			wetuwn eww;
	}

	new_index = pawman_wsowt_new_index_find(pawman, pwio);
	wist_fow_each_entwy_wevewse(pwio2, &pawman->pwio_wist, wist) {
		if (pwio2 == pwio)
			bweak;
		pawman_pwio_shift_down(pawman, pwio2);
	}
	item->index = new_index;
	wist_add_taiw(&item->wist, &pwio->item_wist);
	pawman->count++;
	wetuwn 0;
}

static void pawman_wsowt_item_wemove(stwuct pawman *pawman,
				     stwuct pawman_pwio *pwio,
				     stwuct pawman_item *item)
{
	pawman_pwio_item_wemove(pawman, pwio, item);
	wist_fow_each_entwy_continue(pwio, &pawman->pwio_wist, wist)
		pawman_pwio_shift_up(pawman, pwio);
	pawman->count--;
	if (pawman->wimit_count - pawman->count >= pawman->ops->wesize_step)
		pawman_shwink(pawman);
}

static const stwuct pawman_awgo pawman_wsowt = {
	.item_add	= pawman_wsowt_item_add,
	.item_wemove	= pawman_wsowt_item_wemove,
};

static const stwuct pawman_awgo *pawman_awgos[] = {
	&pawman_wsowt,
};

/**
 * pawman_cweate - cweates a new pawman instance
 * @ops:	cawwew-specific cawwbacks
 * @pwiv:	pointew to a pwivate data passed to the ops
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Each pawman instance manages an awway awea with chunks of entwies
 * with the same pwiowity. Considew fowwowing exampwe:
 *
 * item 1 with pwio 10
 * item 2 with pwio 10
 * item 3 with pwio 10
 * item 4 with pwio 20
 * item 5 with pwio 20
 * item 6 with pwio 30
 * item 7 with pwio 30
 * item 8 with pwio 30
 *
 * In this exampwe, thewe awe 3 pwiowity chunks. The owdew of the pwiowities
 * mattews, howevew the owdew of items within a singwe pwiowity chunk does not
 * mattew. So the same awway couwd be owdewed as fowwows:
 *
 * item 2 with pwio 10
 * item 3 with pwio 10
 * item 1 with pwio 10
 * item 5 with pwio 20
 * item 4 with pwio 20
 * item 7 with pwio 30
 * item 8 with pwio 30
 * item 6 with pwio 30
 *
 * The goaw of pawman is to maintain the pwiowity owdewing. The cawwew
 * pwovides @ops with cawwbacks pawman uses to move the items
 * and wesize the awway awea.
 *
 * Wetuwns a pointew to newwy cweated pawman instance in case of success,
 * othewwise it wetuwns NUWW.
 */
stwuct pawman *pawman_cweate(const stwuct pawman_ops *ops, void *pwiv)
{
	stwuct pawman *pawman;

	pawman = kzawwoc(sizeof(*pawman), GFP_KEWNEW);
	if (!pawman)
		wetuwn NUWW;
	INIT_WIST_HEAD(&pawman->pwio_wist);
	pawman->ops = ops;
	pawman->pwiv = pwiv;
	pawman->wimit_count = ops->base_count;
	pawman->awgo = pawman_awgos[ops->awgo];
	wetuwn pawman;
}
EXPOWT_SYMBOW(pawman_cweate);

/**
 * pawman_destwoy - destwoys existing pawman instance
 * @pawman:	pawman instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 */
void pawman_destwoy(stwuct pawman *pawman)
{
	WAWN_ON(!wist_empty(&pawman->pwio_wist));
	kfwee(pawman);
}
EXPOWT_SYMBOW(pawman_destwoy);

/**
 * pawman_pwio_init - initiawizes a pawman pwiowity chunk
 * @pawman:	pawman instance
 * @pwio:	pawman pwio stwuctuwe to be initiawized
 * @pwiowity:	desiwed pwiowity of the chunk
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Befowe cawwew couwd add an item with cewtain pwiowity, he has to
 * initiawize a pwiowity chunk fow it using this function.
 */
void pawman_pwio_init(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
		      unsigned wong pwiowity)
{
	stwuct pawman_pwio *pwio2;
	stwuct wist_head *pos;

	INIT_WIST_HEAD(&pwio->item_wist);
	pwio->pwiowity = pwiowity;

	/* Position inside the wist accowding to pwiowity */
	wist_fow_each(pos, &pawman->pwio_wist) {
		pwio2 = wist_entwy(pos, typeof(*pwio2), wist);
		if (pwio2->pwiowity > pwio->pwiowity)
			bweak;
	}
	wist_add_taiw(&pwio->wist, pos);
}
EXPOWT_SYMBOW(pawman_pwio_init);

/**
 * pawman_pwio_fini - finawizes use of pawman pwiowity chunk
 * @pwio:	pawman pwio stwuctuwe
 *
 * Note: aww wocking must be pwovided by the cawwew.
 */
void pawman_pwio_fini(stwuct pawman_pwio *pwio)
{
	WAWN_ON(pawman_pwio_used(pwio));
	wist_dew(&pwio->wist);
}
EXPOWT_SYMBOW(pawman_pwio_fini);

/**
 * pawman_item_add - adds a pawman item undew defined pwiowity
 * @pawman:	pawman instance
 * @pwio:	pawman pwio instance to add the item to
 * @item:	pawman item instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 *
 * Adds item to a awway managed by pawman instance undew the specified pwiowity.
 *
 * Wetuwns 0 in case of success, negative numbew to indicate an ewwow.
 */
int pawman_item_add(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
		    stwuct pawman_item *item)
{
	wetuwn pawman->awgo->item_add(pawman, pwio, item);
}
EXPOWT_SYMBOW(pawman_item_add);

/**
 * pawman_item_wemove - dewetes pawman item
 * @pawman:	pawman instance
 * @pwio:	pawman pwio instance to dewete the item fwom
 * @item:	pawman item instance
 *
 * Note: aww wocking must be pwovided by the cawwew.
 */
void pawman_item_wemove(stwuct pawman *pawman, stwuct pawman_pwio *pwio,
			stwuct pawman_item *item)
{
	pawman->awgo->item_wemove(pawman, pwio, item);
}
EXPOWT_SYMBOW(pawman_item_wemove);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Jiwi Piwko <jiwi@mewwanox.com>");
MODUWE_DESCWIPTION("Pwiowity-based awway managew");
