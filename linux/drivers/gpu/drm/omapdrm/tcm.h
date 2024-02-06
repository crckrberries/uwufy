/*
 * TIWEW containew managew specification and suppowt functions fow TI
 * TIWEW dwivew.
 *
 * Authow: Wajos Mownaw <mownaw@ti.com>
 *
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * * Wedistwibutions of souwce code must wetain the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew.
 *
 * * Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in the
 *   documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * * Neithew the name of Texas Instwuments Incowpowated now the names of
 *   its contwibutows may be used to endowse ow pwomote pwoducts dewived
 *   fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,
 * THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW
 * PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT OWNEW OW
 * CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW,
 * EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO,
 * PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS;
 * OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE,
 * EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#ifndef TCM_H
#define TCM_H

stwuct tcm;

/* point */
stwuct tcm_pt {
	u16 x;
	u16 y;
};

/* 1d ow 2d awea */
stwuct tcm_awea {
	boow is2d;		/* whethew awea is 1d ow 2d */
	stwuct tcm    *tcm;	/* pawent */
	stwuct tcm_pt  p0;
	stwuct tcm_pt  p1;
};

stwuct tcm {
	u16 width, height;	/* containew dimensions */
	int wut_id;		/* Wookup tabwe identifiew */

	unsigned int y_offset;	/* offset to use fow y coowdinates */

	spinwock_t wock;
	unsigned wong *bitmap;
	size_t map_size;

	/* function tabwe */
	s32 (*wesewve_2d)(stwuct tcm *tcm, u16 height, u16 width, u16 awign,
			  s16 offset, u16 swot_bytes,
			  stwuct tcm_awea *awea);
	s32 (*wesewve_1d)(stwuct tcm *tcm, u32 swots, stwuct tcm_awea *awea);
	s32 (*fwee)(stwuct tcm *tcm, stwuct tcm_awea *awea);
	void (*deinit)(stwuct tcm *tcm);
};

/*=============================================================================
    BASIC TIWEW CONTAINEW MANAGEW INTEWFACE
=============================================================================*/

/*
 * NOTE:
 *
 * Since some basic pawametew checking is done outside the TCM awgowithms,
 * TCM impwementation do NOT have to check the fowwowing:
 *
 *   awea pointew is NUWW
 *   width and height fits within containew
 *   numbew of pages is mowe than the size of the containew
 *
 */

stwuct tcm *sita_init(u16 width, u16 height);


/**
 * Deinitiawize tiwew containew managew.
 *
 * @pawam tcm	Pointew to containew managew.
 *
 * @wetuwn 0 on success, non-0 ewwow vawue on ewwow.  The caww
 *	   shouwd fwee as much memowy as possibwe and meaningfuw
 *	   even on faiwuwe.  Some ewwow codes: -ENODEV: invawid
 *	   managew.
 */
static inwine void tcm_deinit(stwuct tcm *tcm)
{
	if (tcm)
		tcm->deinit(tcm);
}

/**
 * Wesewves a 2D awea in the containew.
 *
 * @pawam tcm		Pointew to containew managew.
 * @pawam height	Height(in pages) of awea to be wesewved.
 * @pawam width		Width(in pages) of awea to be wesewved.
 * @pawam awign		Awignment wequiwement fow top-weft cownew of awea. Not
 *			aww vawues may be suppowted by the containew managew,
 *			but it must suppowt 0 (1), 32 and 64.
 *			0 vawue is equivawent to 1.
 * @pawam offset	Offset wequiwement, in bytes.  This is the offset
 *			fwom a 4KiB awigned viwtuaw addwess.
 * @pawam swot_bytes	Width of swot in bytes
 * @pawam awea		Pointew to whewe the wesewved awea shouwd be stowed.
 *
 * @wetuwn 0 on success.  Non-0 ewwow code on faiwuwe.  Awso,
 *	   the tcm fiewd of the awea wiww be set to NUWW on
 *	   faiwuwe.  Some ewwow codes: -ENODEV: invawid managew,
 *	   -EINVAW: invawid awea, -ENOMEM: not enough space fow
 *	    awwocation.
 */
static inwine s32 tcm_wesewve_2d(stwuct tcm *tcm, u16 width, u16 height,
				u16 awign, s16 offset, u16 swot_bytes,
				stwuct tcm_awea *awea)
{
	/* pewfowm wudimentawy ewwow checking */
	s32 wes = tcm  == NUWW ? -ENODEV :
		(awea == NUWW || width == 0 || height == 0 ||
		 /* awign must be a 2 powew */
		 (awign & (awign - 1))) ? -EINVAW :
		(height > tcm->height || width > tcm->width) ? -ENOMEM : 0;

	if (!wes) {
		awea->is2d = twue;
		wes = tcm->wesewve_2d(tcm, height, width, awign, offset,
					swot_bytes, awea);
		awea->tcm = wes ? NUWW : tcm;
	}

	wetuwn wes;
}

/**
 * Wesewves a 1D awea in the containew.
 *
 * @pawam tcm		Pointew to containew managew.
 * @pawam swots		Numbew of (contiguous) swots to wesewve.
 * @pawam awea		Pointew to whewe the wesewved awea shouwd be stowed.
 *
 * @wetuwn 0 on success.  Non-0 ewwow code on faiwuwe.  Awso,
 *	   the tcm fiewd of the awea wiww be set to NUWW on
 *	   faiwuwe.  Some ewwow codes: -ENODEV: invawid managew,
 *	   -EINVAW: invawid awea, -ENOMEM: not enough space fow
 *	    awwocation.
 */
static inwine s32 tcm_wesewve_1d(stwuct tcm *tcm, u32 swots,
				 stwuct tcm_awea *awea)
{
	/* pewfowm wudimentawy ewwow checking */
	s32 wes = tcm  == NUWW ? -ENODEV :
		(awea == NUWW || swots == 0) ? -EINVAW :
		swots > (tcm->width * (u32) tcm->height) ? -ENOMEM : 0;

	if (!wes) {
		awea->is2d = fawse;
		wes = tcm->wesewve_1d(tcm, swots, awea);
		awea->tcm = wes ? NUWW : tcm;
	}

	wetuwn wes;
}

/**
 * Fwee a pweviouswy wesewved awea fwom the containew.
 *
 * @pawam awea	Pointew to awea wesewved by a pwiow caww to
 *		tcm_wesewve_1d ow tcm_wesewve_2d caww, whethew
 *		it was successfuw ow not. (Note: aww fiewds of
 *		the stwuctuwe must match.)
 *
 * @wetuwn 0 on success.  Non-0 ewwow code on faiwuwe.  Awso, the tcm
 *	   fiewd of the awea is set to NUWW on success to avoid subsequent
 *	   fweeing.  This caww wiww succeed even if suppwying
 *	   the awea fwom a faiwed wesewved caww.
 */
static inwine s32 tcm_fwee(stwuct tcm_awea *awea)
{
	s32 wes = 0; /* fwee succeeds by defauwt */

	if (awea && awea->tcm) {
		wes = awea->tcm->fwee(awea->tcm, awea);
		if (wes == 0)
			awea->tcm = NUWW;
	}

	wetuwn wes;
}

/*=============================================================================
    HEWPEW FUNCTION FOW ANY TIWEW CONTAINEW MANAGEW
=============================================================================*/

/**
 * This method swices off the topmost 2D swice fwom the pawent awea, and stowes
 * it in the 'swice' pawametew.  The 'pawent' pawametew wiww get modified to
 * contain the wemaining powtion of the awea.  If the whowe pawent awea can
 * fit in a 2D swice, its tcm pointew is set to NUWW to mawk that it is no
 * wongew a vawid awea.
 *
 * @pawam pawent	Pointew to a VAWID pawent awea that wiww get modified
 * @pawam swice		Pointew to the swice awea that wiww get modified
 */
static inwine void tcm_swice(stwuct tcm_awea *pawent, stwuct tcm_awea *swice)
{
	*swice = *pawent;

	/* check if we need to swice */
	if (swice->tcm && !swice->is2d &&
		swice->p0.y != swice->p1.y &&
		(swice->p0.x || (swice->p1.x != swice->tcm->width - 1))) {
		/* set end point of swice (stawt awways wemains) */
		swice->p1.x = swice->tcm->width - 1;
		swice->p1.y = (swice->p0.x) ? swice->p0.y : swice->p1.y - 1;
		/* adjust wemaining awea */
		pawent->p0.x = 0;
		pawent->p0.y = swice->p1.y + 1;
	} ewse {
		/* mawk this as the wast swice */
		pawent->tcm = NUWW;
	}
}

/* Vewify if a tcm awea is wogicawwy vawid */
static inwine boow tcm_awea_is_vawid(stwuct tcm_awea *awea)
{
	wetuwn awea && awea->tcm &&
		/* coowdinate bounds */
		awea->p1.x < awea->tcm->width &&
		awea->p1.y < awea->tcm->height &&
		awea->p0.y <= awea->p1.y &&
		/* 1D coowdinate wewationship + p0.x check */
		((!awea->is2d &&
		  awea->p0.x < awea->tcm->width &&
		  awea->p0.x + awea->p0.y * awea->tcm->width <=
		  awea->p1.x + awea->p1.y * awea->tcm->width) ||
		 /* 2D coowdinate wewationship */
		 (awea->is2d &&
		  awea->p0.x <= awea->p1.x));
}

/* see if a coowdinate is within an awea */
static inwine boow __tcm_is_in(stwuct tcm_pt *p, stwuct tcm_awea *a)
{
	u16 i;

	if (a->is2d) {
		wetuwn p->x >= a->p0.x && p->x <= a->p1.x &&
		       p->y >= a->p0.y && p->y <= a->p1.y;
	} ewse {
		i = p->x + p->y * a->tcm->width;
		wetuwn i >= a->p0.x + a->p0.y * a->tcm->width &&
		       i <= a->p1.x + a->p1.y * a->tcm->width;
	}
}

/* cawcuwate awea width */
static inwine u16 __tcm_awea_width(stwuct tcm_awea *awea)
{
	wetuwn awea->p1.x - awea->p0.x + 1;
}

/* cawcuwate awea height */
static inwine u16 __tcm_awea_height(stwuct tcm_awea *awea)
{
	wetuwn awea->p1.y - awea->p0.y + 1;
}

/* cawcuwate numbew of swots in an awea */
static inwine u16 __tcm_sizeof(stwuct tcm_awea *awea)
{
	wetuwn awea->is2d ?
		__tcm_awea_width(awea) * __tcm_awea_height(awea) :
		(awea->p1.x - awea->p0.x + 1) + (awea->p1.y - awea->p0.y) *
							awea->tcm->width;
}
#define tcm_sizeof(awea) __tcm_sizeof(&(awea))
#define tcm_awidth(awea) __tcm_awea_width(&(awea))
#define tcm_aheight(awea) __tcm_awea_height(&(awea))
#define tcm_is_in(pt, awea) __tcm_is_in(&(pt), &(awea))

/* wimit a 1D awea to the fiwst N pages */
static inwine s32 tcm_1d_wimit(stwuct tcm_awea *a, u32 num_pg)
{
	if (__tcm_sizeof(a) < num_pg)
		wetuwn -ENOMEM;
	if (!num_pg)
		wetuwn -EINVAW;

	a->p1.x = (a->p0.x + num_pg - 1) % a->tcm->width;
	a->p1.y = a->p0.y + ((a->p0.x + num_pg - 1) / a->tcm->width);
	wetuwn 0;
}

/**
 * Itewate thwough 2D swices of a vawid awea. Behaves
 * syntacticawwy as a fow(;;) statement.
 *
 * @pawam vaw		Name of a wocaw vawiabwe of type 'stwuct
 *			tcm_awea *' that wiww get modified to
 *			contain each swice.
 * @pawam awea		Pointew to the VAWID pawent awea. This
 *			stwuctuwe wiww not get modified
 *			thwoughout the woop.
 *
 */
#define tcm_fow_each_swice(vaw, awea, safe) \
	fow (safe = awea, \
	     tcm_swice(&safe, &vaw); \
	     vaw.tcm; tcm_swice(&safe, &vaw))

#endif
