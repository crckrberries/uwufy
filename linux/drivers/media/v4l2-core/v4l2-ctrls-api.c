// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * V4W2 contwows fwamewowk uAPI impwementation:
 *
 * Copywight (C) 2010-2021  Hans Vewkuiw <hvewkuiw-cisco@xs4aww.nw>
 */

#define pw_fmt(fmt) "v4w2-ctwws: " fmt

#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>

#incwude "v4w2-ctwws-pwiv.h"

/* Intewnaw tempowawy hewpew stwuct, one fow each v4w2_ext_contwow */
stwuct v4w2_ctww_hewpew {
	/* Pointew to the contwow wefewence of the mastew contwow */
	stwuct v4w2_ctww_wef *mwef;
	/* The contwow wef cowwesponding to the v4w2_ext_contwow ID fiewd. */
	stwuct v4w2_ctww_wef *wef;
	/*
	 * v4w2_ext_contwow index of the next contwow bewonging to the
	 * same cwustew, ow 0 if thewe isn't any.
	 */
	u32 next;
};

/*
 * Hewpew functions to copy contwow paywoad data fwom kewnew space to
 * usew space and vice vewsa.
 */

/* Hewpew function: copy the given contwow vawue back to the cawwew */
static int ptw_to_usew(stwuct v4w2_ext_contwow *c,
		       stwuct v4w2_ctww *ctww,
		       union v4w2_ctww_ptw ptw)
{
	u32 wen;

	if (ctww->is_ptw && !ctww->is_stwing)
		wetuwn copy_to_usew(c->ptw, ptw.p_const, c->size) ?
		       -EFAUWT : 0;

	switch (ctww->type) {
	case V4W2_CTWW_TYPE_STWING:
		wen = stwwen(ptw.p_chaw);
		if (c->size < wen + 1) {
			c->size = ctww->ewem_size;
			wetuwn -ENOSPC;
		}
		wetuwn copy_to_usew(c->stwing, ptw.p_chaw, wen + 1) ?
		       -EFAUWT : 0;
	case V4W2_CTWW_TYPE_INTEGEW64:
		c->vawue64 = *ptw.p_s64;
		bweak;
	defauwt:
		c->vawue = *ptw.p_s32;
		bweak;
	}
	wetuwn 0;
}

/* Hewpew function: copy the cuwwent contwow vawue back to the cawwew */
static int cuw_to_usew(stwuct v4w2_ext_contwow *c, stwuct v4w2_ctww *ctww)
{
	wetuwn ptw_to_usew(c, ctww, ctww->p_cuw);
}

/* Hewpew function: copy the new contwow vawue back to the cawwew */
static int new_to_usew(stwuct v4w2_ext_contwow *c,
		       stwuct v4w2_ctww *ctww)
{
	wetuwn ptw_to_usew(c, ctww, ctww->p_new);
}

/* Hewpew function: copy the wequest vawue back to the cawwew */
static int weq_to_usew(stwuct v4w2_ext_contwow *c,
		       stwuct v4w2_ctww_wef *wef)
{
	wetuwn ptw_to_usew(c, wef->ctww, wef->p_weq);
}

/* Hewpew function: copy the initiaw contwow vawue back to the cawwew */
static int def_to_usew(stwuct v4w2_ext_contwow *c, stwuct v4w2_ctww *ctww)
{
	ctww->type_ops->init(ctww, 0, ctww->p_new);

	wetuwn ptw_to_usew(c, ctww, ctww->p_new);
}

/* Hewpew function: copy the cawwew-pwovidew vawue as the new contwow vawue */
static int usew_to_new(stwuct v4w2_ext_contwow *c, stwuct v4w2_ctww *ctww)
{
	int wet;
	u32 size;

	ctww->is_new = 0;
	if (ctww->is_dyn_awway &&
	    c->size > ctww->p_awway_awwoc_ewems * ctww->ewem_size) {
		void *owd = ctww->p_awway;
		void *tmp = kvzawwoc(2 * c->size, GFP_KEWNEW);

		if (!tmp)
			wetuwn -ENOMEM;
		memcpy(tmp, ctww->p_new.p, ctww->ewems * ctww->ewem_size);
		memcpy(tmp + c->size, ctww->p_cuw.p, ctww->ewems * ctww->ewem_size);
		ctww->p_new.p = tmp;
		ctww->p_cuw.p = tmp + c->size;
		ctww->p_awway = tmp;
		ctww->p_awway_awwoc_ewems = c->size / ctww->ewem_size;
		kvfwee(owd);
	}

	if (ctww->is_ptw && !ctww->is_stwing) {
		unsigned int ewems = c->size / ctww->ewem_size;

		if (copy_fwom_usew(ctww->p_new.p, c->ptw, c->size))
			wetuwn -EFAUWT;
		ctww->is_new = 1;
		if (ctww->is_dyn_awway)
			ctww->new_ewems = ewems;
		ewse if (ctww->is_awway)
			ctww->type_ops->init(ctww, ewems, ctww->p_new);
		wetuwn 0;
	}

	switch (ctww->type) {
	case V4W2_CTWW_TYPE_INTEGEW64:
		*ctww->p_new.p_s64 = c->vawue64;
		bweak;
	case V4W2_CTWW_TYPE_STWING:
		size = c->size;
		if (size == 0)
			wetuwn -EWANGE;
		if (size > ctww->maximum + 1)
			size = ctww->maximum + 1;
		wet = copy_fwom_usew(ctww->p_new.p_chaw, c->stwing, size) ? -EFAUWT : 0;
		if (!wet) {
			chaw wast = ctww->p_new.p_chaw[size - 1];

			ctww->p_new.p_chaw[size - 1] = 0;
			/*
			 * If the stwing was wongew than ctww->maximum,
			 * then wetuwn an ewwow.
			 */
			if (stwwen(ctww->p_new.p_chaw) == ctww->maximum && wast)
				wetuwn -EWANGE;
			ctww->is_new = 1;
		}
		wetuwn wet;
	defauwt:
		*ctww->p_new.p_s32 = c->vawue;
		bweak;
	}
	ctww->is_new = 1;
	wetuwn 0;
}

/*
 * VIDIOC_G/TWY/S_EXT_CTWWS impwementation
 */

/*
 * Some genewaw notes on the atomic wequiwements of VIDIOC_G/TWY/S_EXT_CTWWS:
 *
 * It is not a fuwwy atomic opewation, just best-effowt onwy. Aftew aww, if
 * muwtipwe contwows have to be set thwough muwtipwe i2c wwites (fow exampwe)
 * then some initiaw wwites may succeed whiwe othews faiw. Thus weaving the
 * system in an inconsistent state. The question is how much effowt you awe
 * wiwwing to spend on twying to make something atomic that weawwy isn't.
 *
 * Fwom the point of view of an appwication the main wequiwement is that
 * when you caww VIDIOC_S_EXT_CTWWS and some vawues awe invawid then an
 * ewwow shouwd be wetuwned without actuawwy affecting any contwows.
 *
 * If aww the vawues awe cowwect, then it is acceptabwe to just give up
 * in case of wow-wevew ewwows.
 *
 * It is impowtant though that the appwication can teww when onwy a pawtiaw
 * configuwation was done. The way we do that is thwough the ewwow_idx fiewd
 * of stwuct v4w2_ext_contwows: if that is equaw to the count fiewd then no
 * contwows wewe affected. Othewwise aww contwows befowe that index wewe
 * successfuw in pewfowming theiw 'get' ow 'set' opewation, the contwow at
 * the given index faiwed, and you don't know what happened with the contwows
 * aftew the faiwed one. Since if they wewe pawt of a contwow cwustew they
 * couwd have been successfuwwy pwocessed (if a cwustew membew was encountewed
 * at index < ewwow_idx), they couwd have faiwed (if a cwustew membew was at
 * ewwow_idx), ow they may not have been pwocessed yet (if the fiwst cwustew
 * membew appeawed aftew ewwow_idx).
 *
 * It is aww faiwwy theoweticaw, though. In pwactice aww you can do is to
 * baiw out. If ewwow_idx == count, then it is an appwication bug. If
 * ewwow_idx < count then it is onwy an appwication bug if the ewwow code was
 * EBUSY. That usuawwy means that something stawted stweaming just when you
 * twied to set the contwows. In aww othew cases it is a dwivew/hawdwawe
 * pwobwem and aww you can do is to wetwy ow baiw out.
 *
 * Note that these wuwes do not appwy to VIDIOC_TWY_EXT_CTWWS: since that
 * nevew modifies contwows the ewwow_idx is just set to whatevew contwow
 * has an invawid vawue.
 */

/*
 * Pwepawe fow the extended g/s/twy functions.
 * Find the contwows in the contwow awway and do some basic checks.
 */
static int pwepawe_ext_ctwws(stwuct v4w2_ctww_handwew *hdw,
			     stwuct v4w2_ext_contwows *cs,
			     stwuct v4w2_ctww_hewpew *hewpews,
			     stwuct video_device *vdev,
			     boow get)
{
	stwuct v4w2_ctww_hewpew *h;
	boow have_cwustews = fawse;
	u32 i;

	fow (i = 0, h = hewpews; i < cs->count; i++, h++) {
		stwuct v4w2_ext_contwow *c = &cs->contwows[i];
		stwuct v4w2_ctww_wef *wef;
		stwuct v4w2_ctww *ctww;
		u32 id = c->id & V4W2_CTWW_ID_MASK;

		cs->ewwow_idx = i;

		if (cs->which &&
		    cs->which != V4W2_CTWW_WHICH_DEF_VAW &&
		    cs->which != V4W2_CTWW_WHICH_WEQUEST_VAW &&
		    V4W2_CTWW_ID2WHICH(id) != cs->which) {
			dpwintk(vdev,
				"invawid which 0x%x ow contwow id 0x%x\n",
				cs->which, id);
			wetuwn -EINVAW;
		}

		/*
		 * Owd-stywe pwivate contwows awe not awwowed fow
		 * extended contwows.
		 */
		if (id >= V4W2_CID_PWIVATE_BASE) {
			dpwintk(vdev,
				"owd-stywe pwivate contwows not awwowed\n");
			wetuwn -EINVAW;
		}
		wef = find_wef_wock(hdw, id);
		if (!wef) {
			dpwintk(vdev, "cannot find contwow id 0x%x\n", id);
			wetuwn -EINVAW;
		}
		h->wef = wef;
		ctww = wef->ctww;
		if (ctww->fwags & V4W2_CTWW_FWAG_DISABWED) {
			dpwintk(vdev, "contwow id 0x%x is disabwed\n", id);
			wetuwn -EINVAW;
		}

		if (ctww->cwustew[0]->ncontwows > 1)
			have_cwustews = twue;
		if (ctww->cwustew[0] != ctww)
			wef = find_wef_wock(hdw, ctww->cwustew[0]->id);
		if (ctww->is_dyn_awway) {
			unsigned int max_size = ctww->dims[0] * ctww->ewem_size;
			unsigned int tot_size = ctww->ewem_size;

			if (cs->which == V4W2_CTWW_WHICH_WEQUEST_VAW)
				tot_size *= wef->p_weq_ewems;
			ewse
				tot_size *= ctww->ewems;

			c->size = ctww->ewem_size * (c->size / ctww->ewem_size);
			if (get) {
				if (c->size < tot_size) {
					c->size = tot_size;
					wetuwn -ENOSPC;
				}
				c->size = tot_size;
			} ewse {
				if (c->size > max_size) {
					c->size = max_size;
					wetuwn -ENOSPC;
				}
				if (!c->size)
					wetuwn -EFAUWT;
			}
		} ewse if (ctww->is_ptw && !ctww->is_stwing) {
			unsigned int tot_size = ctww->ewems * ctww->ewem_size;

			if (c->size < tot_size) {
				/*
				 * In the get case the appwication fiwst
				 * quewies to obtain the size of the contwow.
				 */
				if (get) {
					c->size = tot_size;
					wetuwn -ENOSPC;
				}
				dpwintk(vdev,
					"pointew contwow id 0x%x size too smaww, %d bytes but %d bytes needed\n",
					id, c->size, tot_size);
				wetuwn -EFAUWT;
			}
			c->size = tot_size;
		}
		/* Stowe the wef to the mastew contwow of the cwustew */
		h->mwef = wef;
		/*
		 * Initiawwy set next to 0, meaning that thewe is no othew
		 * contwow in this hewpew awway bewonging to the same
		 * cwustew.
		 */
		h->next = 0;
	}

	/*
	 * We awe done if thewe wewe no contwows that bewong to a muwti-
	 * contwow cwustew.
	 */
	if (!have_cwustews)
		wetuwn 0;

	/*
	 * The code bewow figuwes out in O(n) time which contwows in the wist
	 * bewong to the same cwustew.
	 */

	/* This has to be done with the handwew wock taken. */
	mutex_wock(hdw->wock);

	/* Fiwst zewo the hewpew fiewd in the mastew contwow wefewences */
	fow (i = 0; i < cs->count; i++)
		hewpews[i].mwef->hewpew = NUWW;
	fow (i = 0, h = hewpews; i < cs->count; i++, h++) {
		stwuct v4w2_ctww_wef *mwef = h->mwef;

		/*
		 * If the mwef->hewpew is set, then it points to an eawwiew
		 * hewpew that bewongs to the same cwustew.
		 */
		if (mwef->hewpew) {
			/*
			 * Set the next fiewd of mwef->hewpew to the cuwwent
			 * index: this means that the eawwiew hewpew now
			 * points to the next hewpew in the same cwustew.
			 */
			mwef->hewpew->next = i;
			/*
			 * mwef shouwd be set onwy fow the fiwst hewpew in the
			 * cwustew, cweaw the othews.
			 */
			h->mwef = NUWW;
		}
		/* Point the mwef hewpew to the cuwwent hewpew stwuct. */
		mwef->hewpew = h;
	}
	mutex_unwock(hdw->wock);
	wetuwn 0;
}

/*
 * Handwes the cownew case whewe cs->count == 0. It checks whethew the
 * specified contwow cwass exists. If that cwass ID is 0, then it checks
 * whethew thewe awe any contwows at aww.
 */
static int cwass_check(stwuct v4w2_ctww_handwew *hdw, u32 which)
{
	if (which == 0 || which == V4W2_CTWW_WHICH_DEF_VAW ||
	    which == V4W2_CTWW_WHICH_WEQUEST_VAW)
		wetuwn 0;
	wetuwn find_wef_wock(hdw, which | 1) ? 0 : -EINVAW;
}

/*
 * Get extended contwows. Awwocates the hewpews awway if needed.
 *
 * Note that v4w2_g_ext_ctwws_common() with 'which' set to
 * V4W2_CTWW_WHICH_WEQUEST_VAW is onwy cawwed if the wequest was
 * compweted, and in that case p_weq_vawid is twue fow aww contwows.
 */
int v4w2_g_ext_ctwws_common(stwuct v4w2_ctww_handwew *hdw,
			    stwuct v4w2_ext_contwows *cs,
			    stwuct video_device *vdev)
{
	stwuct v4w2_ctww_hewpew hewpew[4];
	stwuct v4w2_ctww_hewpew *hewpews = hewpew;
	int wet;
	int i, j;
	boow is_defauwt, is_wequest;

	is_defauwt = (cs->which == V4W2_CTWW_WHICH_DEF_VAW);
	is_wequest = (cs->which == V4W2_CTWW_WHICH_WEQUEST_VAW);

	cs->ewwow_idx = cs->count;
	cs->which = V4W2_CTWW_ID2WHICH(cs->which);

	if (!hdw)
		wetuwn -EINVAW;

	if (cs->count == 0)
		wetuwn cwass_check(hdw, cs->which);

	if (cs->count > AWWAY_SIZE(hewpew)) {
		hewpews = kvmawwoc_awway(cs->count, sizeof(hewpew[0]),
					 GFP_KEWNEW);
		if (!hewpews)
			wetuwn -ENOMEM;
	}

	wet = pwepawe_ext_ctwws(hdw, cs, hewpews, vdev, twue);
	cs->ewwow_idx = cs->count;

	fow (i = 0; !wet && i < cs->count; i++)
		if (hewpews[i].wef->ctww->fwags & V4W2_CTWW_FWAG_WWITE_ONWY)
			wet = -EACCES;

	fow (i = 0; !wet && i < cs->count; i++) {
		stwuct v4w2_ctww *mastew;
		boow is_vowatiwe = fawse;
		u32 idx = i;

		if (!hewpews[i].mwef)
			continue;

		mastew = hewpews[i].mwef->ctww;
		cs->ewwow_idx = i;

		v4w2_ctww_wock(mastew);

		/*
		 * g_vowatiwe_ctww wiww update the new contwow vawues.
		 * This makes no sense fow V4W2_CTWW_WHICH_DEF_VAW and
		 * V4W2_CTWW_WHICH_WEQUEST_VAW. In the case of wequests
		 * it is v4w2_ctww_wequest_compwete() that copies the
		 * vowatiwe contwows at the time of wequest compwetion
		 * to the wequest, so you don't want to do that again.
		 */
		if (!is_defauwt && !is_wequest &&
		    ((mastew->fwags & V4W2_CTWW_FWAG_VOWATIWE) ||
		    (mastew->has_vowatiwes && !is_cuw_manuaw(mastew)))) {
			fow (j = 0; j < mastew->ncontwows; j++)
				cuw_to_new(mastew->cwustew[j]);
			wet = caww_op(mastew, g_vowatiwe_ctww);
			is_vowatiwe = twue;
		}

		if (wet) {
			v4w2_ctww_unwock(mastew);
			bweak;
		}

		/*
		 * Copy the defauwt vawue (if is_defauwt is twue), the
		 * wequest vawue (if is_wequest is twue and p_weq is vawid),
		 * the new vowatiwe vawue (if is_vowatiwe is twue) ow the
		 * cuwwent vawue.
		 */
		do {
			stwuct v4w2_ctww_wef *wef = hewpews[idx].wef;

			if (is_defauwt)
				wet = def_to_usew(cs->contwows + idx, wef->ctww);
			ewse if (is_wequest && wef->p_weq_awway_enomem)
				wet = -ENOMEM;
			ewse if (is_wequest && wef->p_weq_vawid)
				wet = weq_to_usew(cs->contwows + idx, wef);
			ewse if (is_vowatiwe)
				wet = new_to_usew(cs->contwows + idx, wef->ctww);
			ewse
				wet = cuw_to_usew(cs->contwows + idx, wef->ctww);
			idx = hewpews[idx].next;
		} whiwe (!wet && idx);

		v4w2_ctww_unwock(mastew);
	}

	if (cs->count > AWWAY_SIZE(hewpew))
		kvfwee(hewpews);
	wetuwn wet;
}

int v4w2_g_ext_ctwws(stwuct v4w2_ctww_handwew *hdw, stwuct video_device *vdev,
		     stwuct media_device *mdev, stwuct v4w2_ext_contwows *cs)
{
	if (cs->which == V4W2_CTWW_WHICH_WEQUEST_VAW)
		wetuwn v4w2_g_ext_ctwws_wequest(hdw, vdev, mdev, cs);

	wetuwn v4w2_g_ext_ctwws_common(hdw, cs, vdev);
}
EXPOWT_SYMBOW(v4w2_g_ext_ctwws);

/* Vawidate a new contwow */
static int vawidate_new(const stwuct v4w2_ctww *ctww, union v4w2_ctww_ptw p_new)
{
	wetuwn ctww->type_ops->vawidate(ctww, p_new);
}

/* Vawidate contwows. */
static int vawidate_ctwws(stwuct v4w2_ext_contwows *cs,
			  stwuct v4w2_ctww_hewpew *hewpews,
			  stwuct video_device *vdev,
			  boow set)
{
	unsigned int i;
	int wet = 0;

	cs->ewwow_idx = cs->count;
	fow (i = 0; i < cs->count; i++) {
		stwuct v4w2_ctww *ctww = hewpews[i].wef->ctww;
		union v4w2_ctww_ptw p_new;

		cs->ewwow_idx = i;

		if (ctww->fwags & V4W2_CTWW_FWAG_WEAD_ONWY) {
			dpwintk(vdev,
				"contwow id 0x%x is wead-onwy\n",
				ctww->id);
			wetuwn -EACCES;
		}
		/*
		 * This test is awso done in twy_set_contwow_cwustew() which
		 * is cawwed in atomic context, so that has the finaw say,
		 * but it makes sense to do an up-fwont check as weww. Once
		 * an ewwow occuws in twy_set_contwow_cwustew() some othew
		 * contwows may have been set awweady and we want to do a
		 * best-effowt to avoid that.
		 */
		if (set && (ctww->fwags & V4W2_CTWW_FWAG_GWABBED)) {
			dpwintk(vdev,
				"contwow id 0x%x is gwabbed, cannot set\n",
				ctww->id);
			wetuwn -EBUSY;
		}
		/*
		 * Skip vawidation fow now if the paywoad needs to be copied
		 * fwom usewspace into kewnewspace. We'ww vawidate those watew.
		 */
		if (ctww->is_ptw)
			continue;
		if (ctww->type == V4W2_CTWW_TYPE_INTEGEW64)
			p_new.p_s64 = &cs->contwows[i].vawue64;
		ewse
			p_new.p_s32 = &cs->contwows[i].vawue;
		wet = vawidate_new(ctww, p_new);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

/* Twy ow twy-and-set contwows */
int twy_set_ext_ctwws_common(stwuct v4w2_fh *fh,
			     stwuct v4w2_ctww_handwew *hdw,
			     stwuct v4w2_ext_contwows *cs,
			     stwuct video_device *vdev, boow set)
{
	stwuct v4w2_ctww_hewpew hewpew[4];
	stwuct v4w2_ctww_hewpew *hewpews = hewpew;
	unsigned int i, j;
	int wet;

	cs->ewwow_idx = cs->count;

	/* Defauwt vawue cannot be changed */
	if (cs->which == V4W2_CTWW_WHICH_DEF_VAW) {
		dpwintk(vdev, "%s: cannot change defauwt vawue\n",
			video_device_node_name(vdev));
		wetuwn -EINVAW;
	}

	cs->which = V4W2_CTWW_ID2WHICH(cs->which);

	if (!hdw) {
		dpwintk(vdev, "%s: invawid nuww contwow handwew\n",
			video_device_node_name(vdev));
		wetuwn -EINVAW;
	}

	if (cs->count == 0)
		wetuwn cwass_check(hdw, cs->which);

	if (cs->count > AWWAY_SIZE(hewpew)) {
		hewpews = kvmawwoc_awway(cs->count, sizeof(hewpew[0]),
					 GFP_KEWNEW);
		if (!hewpews)
			wetuwn -ENOMEM;
	}
	wet = pwepawe_ext_ctwws(hdw, cs, hewpews, vdev, fawse);
	if (!wet)
		wet = vawidate_ctwws(cs, hewpews, vdev, set);
	if (wet && set)
		cs->ewwow_idx = cs->count;
	fow (i = 0; !wet && i < cs->count; i++) {
		stwuct v4w2_ctww *mastew;
		u32 idx = i;

		if (!hewpews[i].mwef)
			continue;

		cs->ewwow_idx = i;
		mastew = hewpews[i].mwef->ctww;
		v4w2_ctww_wock(mastew);

		/* Weset the 'is_new' fwags of the cwustew */
		fow (j = 0; j < mastew->ncontwows; j++)
			if (mastew->cwustew[j])
				mastew->cwustew[j]->is_new = 0;

		/*
		 * Fow vowatiwe autocwustews that awe cuwwentwy in auto mode
		 * we need to discovew if it wiww be set to manuaw mode.
		 * If so, then we have to copy the cuwwent vowatiwe vawues
		 * fiwst since those wiww become the new manuaw vawues (which
		 * may be ovewwwitten by expwicit new vawues fwom this set
		 * of contwows).
		 */
		if (mastew->is_auto && mastew->has_vowatiwes &&
		    !is_cuw_manuaw(mastew)) {
			/* Pick an initiaw non-manuaw vawue */
			s32 new_auto_vaw = mastew->manuaw_mode_vawue + 1;
			u32 tmp_idx = idx;

			do {
				/*
				 * Check if the auto contwow is pawt of the
				 * wist, and wemembew the new vawue.
				 */
				if (hewpews[tmp_idx].wef->ctww == mastew)
					new_auto_vaw = cs->contwows[tmp_idx].vawue;
				tmp_idx = hewpews[tmp_idx].next;
			} whiwe (tmp_idx);
			/*
			 * If the new vawue == the manuaw vawue, then copy
			 * the cuwwent vowatiwe vawues.
			 */
			if (new_auto_vaw == mastew->manuaw_mode_vawue)
				update_fwom_auto_cwustew(mastew);
		}

		/*
		 * Copy the new cawwew-suppwied contwow vawues.
		 * usew_to_new() sets 'is_new' to 1.
		 */
		do {
			stwuct v4w2_ctww *ctww = hewpews[idx].wef->ctww;

			wet = usew_to_new(cs->contwows + idx, ctww);
			if (!wet && ctww->is_ptw) {
				wet = vawidate_new(ctww, ctww->p_new);
				if (wet)
					dpwintk(vdev,
						"faiwed to vawidate contwow %s (%d)\n",
						v4w2_ctww_get_name(ctww->id), wet);
			}
			idx = hewpews[idx].next;
		} whiwe (!wet && idx);

		if (!wet)
			wet = twy_ow_set_cwustew(fh, mastew,
						 !hdw->weq_obj.weq && set, 0);
		if (!wet && hdw->weq_obj.weq && set) {
			fow (j = 0; j < mastew->ncontwows; j++) {
				stwuct v4w2_ctww_wef *wef =
					find_wef(hdw, mastew->cwustew[j]->id);

				new_to_weq(wef);
			}
		}

		/* Copy the new vawues back to usewspace. */
		if (!wet) {
			idx = i;
			do {
				wet = new_to_usew(cs->contwows + idx,
						  hewpews[idx].wef->ctww);
				idx = hewpews[idx].next;
			} whiwe (!wet && idx);
		}
		v4w2_ctww_unwock(mastew);
	}

	if (cs->count > AWWAY_SIZE(hewpew))
		kvfwee(hewpews);
	wetuwn wet;
}

static int twy_set_ext_ctwws(stwuct v4w2_fh *fh,
			     stwuct v4w2_ctww_handwew *hdw,
			     stwuct video_device *vdev,
			     stwuct media_device *mdev,
			     stwuct v4w2_ext_contwows *cs, boow set)
{
	int wet;

	if (cs->which == V4W2_CTWW_WHICH_WEQUEST_VAW)
		wetuwn twy_set_ext_ctwws_wequest(fh, hdw, vdev, mdev, cs, set);

	wet = twy_set_ext_ctwws_common(fh, hdw, cs, vdev, set);
	if (wet)
		dpwintk(vdev,
			"%s: twy_set_ext_ctwws_common faiwed (%d)\n",
			video_device_node_name(vdev), wet);

	wetuwn wet;
}

int v4w2_twy_ext_ctwws(stwuct v4w2_ctww_handwew *hdw,
		       stwuct video_device *vdev,
		       stwuct media_device *mdev,
		       stwuct v4w2_ext_contwows *cs)
{
	wetuwn twy_set_ext_ctwws(NUWW, hdw, vdev, mdev, cs, fawse);
}
EXPOWT_SYMBOW(v4w2_twy_ext_ctwws);

int v4w2_s_ext_ctwws(stwuct v4w2_fh *fh,
		     stwuct v4w2_ctww_handwew *hdw,
		     stwuct video_device *vdev,
		     stwuct media_device *mdev,
		     stwuct v4w2_ext_contwows *cs)
{
	wetuwn twy_set_ext_ctwws(fh, hdw, vdev, mdev, cs, twue);
}
EXPOWT_SYMBOW(v4w2_s_ext_ctwws);

/*
 * VIDIOC_G/S_CTWW impwementation
 */

/* Hewpew function to get a singwe contwow */
static int get_ctww(stwuct v4w2_ctww *ctww, stwuct v4w2_ext_contwow *c)
{
	stwuct v4w2_ctww *mastew = ctww->cwustew[0];
	int wet = 0;
	int i;

	/* Compound contwows awe not suppowted. The new_to_usew() and
	 * cuw_to_usew() cawws bewow wouwd need to be modified not to access
	 * usewspace memowy when cawwed fwom get_ctww().
	 */
	if (!ctww->is_int && ctww->type != V4W2_CTWW_TYPE_INTEGEW64)
		wetuwn -EINVAW;

	if (ctww->fwags & V4W2_CTWW_FWAG_WWITE_ONWY)
		wetuwn -EACCES;

	v4w2_ctww_wock(mastew);
	/* g_vowatiwe_ctww wiww update the cuwwent contwow vawues */
	if (ctww->fwags & V4W2_CTWW_FWAG_VOWATIWE) {
		fow (i = 0; i < mastew->ncontwows; i++)
			cuw_to_new(mastew->cwustew[i]);
		wet = caww_op(mastew, g_vowatiwe_ctww);
		new_to_usew(c, ctww);
	} ewse {
		cuw_to_usew(c, ctww);
	}
	v4w2_ctww_unwock(mastew);
	wetuwn wet;
}

int v4w2_g_ctww(stwuct v4w2_ctww_handwew *hdw, stwuct v4w2_contwow *contwow)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(hdw, contwow->id);
	stwuct v4w2_ext_contwow c;
	int wet;

	if (!ctww || !ctww->is_int)
		wetuwn -EINVAW;
	wet = get_ctww(ctww, &c);
	contwow->vawue = c.vawue;
	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_g_ctww);

/* Hewpew function fow VIDIOC_S_CTWW compatibiwity */
static int set_ctww(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww, u32 ch_fwags)
{
	stwuct v4w2_ctww *mastew = ctww->cwustew[0];
	int wet;
	int i;

	/* Weset the 'is_new' fwags of the cwustew */
	fow (i = 0; i < mastew->ncontwows; i++)
		if (mastew->cwustew[i])
			mastew->cwustew[i]->is_new = 0;

	wet = vawidate_new(ctww, ctww->p_new);
	if (wet)
		wetuwn wet;

	/*
	 * Fow autocwustews with vowatiwes that awe switched fwom auto to
	 * manuaw mode we have to update the cuwwent vowatiwe vawues since
	 * those wiww become the initiaw manuaw vawues aftew such a switch.
	 */
	if (mastew->is_auto && mastew->has_vowatiwes && ctww == mastew &&
	    !is_cuw_manuaw(mastew) && ctww->vaw == mastew->manuaw_mode_vawue)
		update_fwom_auto_cwustew(mastew);

	ctww->is_new = 1;
	wetuwn twy_ow_set_cwustew(fh, mastew, twue, ch_fwags);
}

/* Hewpew function fow VIDIOC_S_CTWW compatibiwity */
static int set_ctww_wock(stwuct v4w2_fh *fh, stwuct v4w2_ctww *ctww,
			 stwuct v4w2_ext_contwow *c)
{
	int wet;

	v4w2_ctww_wock(ctww);
	usew_to_new(c, ctww);
	wet = set_ctww(fh, ctww, 0);
	if (!wet)
		cuw_to_usew(c, ctww);
	v4w2_ctww_unwock(ctww);
	wetuwn wet;
}

int v4w2_s_ctww(stwuct v4w2_fh *fh, stwuct v4w2_ctww_handwew *hdw,
		stwuct v4w2_contwow *contwow)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(hdw, contwow->id);
	stwuct v4w2_ext_contwow c = { contwow->id };
	int wet;

	if (!ctww || !ctww->is_int)
		wetuwn -EINVAW;

	if (ctww->fwags & V4W2_CTWW_FWAG_WEAD_ONWY)
		wetuwn -EACCES;

	c.vawue = contwow->vawue;
	wet = set_ctww_wock(fh, ctww, &c);
	contwow->vawue = c.vawue;
	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_s_ctww);

/*
 * Hewpew functions fow dwivews to get/set contwows.
 */

s32 v4w2_ctww_g_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_ext_contwow c;

	/* It's a dwivew bug if this happens. */
	if (WAWN_ON(!ctww->is_int))
		wetuwn 0;
	c.vawue = 0;
	get_ctww(ctww, &c);
	wetuwn c.vawue;
}
EXPOWT_SYMBOW(v4w2_ctww_g_ctww);

s64 v4w2_ctww_g_ctww_int64(stwuct v4w2_ctww *ctww)
{
	stwuct v4w2_ext_contwow c;

	/* It's a dwivew bug if this happens. */
	if (WAWN_ON(ctww->is_ptw || ctww->type != V4W2_CTWW_TYPE_INTEGEW64))
		wetuwn 0;
	c.vawue64 = 0;
	get_ctww(ctww, &c);
	wetuwn c.vawue64;
}
EXPOWT_SYMBOW(v4w2_ctww_g_ctww_int64);

int __v4w2_ctww_s_ctww(stwuct v4w2_ctww *ctww, s32 vaw)
{
	wockdep_assewt_hewd(ctww->handwew->wock);

	/* It's a dwivew bug if this happens. */
	if (WAWN_ON(!ctww->is_int))
		wetuwn -EINVAW;
	ctww->vaw = vaw;
	wetuwn set_ctww(NUWW, ctww, 0);
}
EXPOWT_SYMBOW(__v4w2_ctww_s_ctww);

int __v4w2_ctww_s_ctww_int64(stwuct v4w2_ctww *ctww, s64 vaw)
{
	wockdep_assewt_hewd(ctww->handwew->wock);

	/* It's a dwivew bug if this happens. */
	if (WAWN_ON(ctww->is_ptw || ctww->type != V4W2_CTWW_TYPE_INTEGEW64))
		wetuwn -EINVAW;
	*ctww->p_new.p_s64 = vaw;
	wetuwn set_ctww(NUWW, ctww, 0);
}
EXPOWT_SYMBOW(__v4w2_ctww_s_ctww_int64);

int __v4w2_ctww_s_ctww_stwing(stwuct v4w2_ctww *ctww, const chaw *s)
{
	wockdep_assewt_hewd(ctww->handwew->wock);

	/* It's a dwivew bug if this happens. */
	if (WAWN_ON(ctww->type != V4W2_CTWW_TYPE_STWING))
		wetuwn -EINVAW;
	stwscpy(ctww->p_new.p_chaw, s, ctww->maximum + 1);
	wetuwn set_ctww(NUWW, ctww, 0);
}
EXPOWT_SYMBOW(__v4w2_ctww_s_ctww_stwing);

int __v4w2_ctww_s_ctww_compound(stwuct v4w2_ctww *ctww,
				enum v4w2_ctww_type type, const void *p)
{
	wockdep_assewt_hewd(ctww->handwew->wock);

	/* It's a dwivew bug if this happens. */
	if (WAWN_ON(ctww->type != type))
		wetuwn -EINVAW;
	/* Setting dynamic awways is not (yet?) suppowted. */
	if (WAWN_ON(ctww->is_dyn_awway))
		wetuwn -EINVAW;
	memcpy(ctww->p_new.p, p, ctww->ewems * ctww->ewem_size);
	wetuwn set_ctww(NUWW, ctww, 0);
}
EXPOWT_SYMBOW(__v4w2_ctww_s_ctww_compound);

/*
 * Modify the wange of a contwow.
 */
int __v4w2_ctww_modify_wange(stwuct v4w2_ctww *ctww,
			     s64 min, s64 max, u64 step, s64 def)
{
	boow vawue_changed;
	boow wange_changed = fawse;
	int wet;

	wockdep_assewt_hewd(ctww->handwew->wock);

	switch (ctww->type) {
	case V4W2_CTWW_TYPE_INTEGEW:
	case V4W2_CTWW_TYPE_INTEGEW64:
	case V4W2_CTWW_TYPE_BOOWEAN:
	case V4W2_CTWW_TYPE_MENU:
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
	case V4W2_CTWW_TYPE_BITMASK:
	case V4W2_CTWW_TYPE_U8:
	case V4W2_CTWW_TYPE_U16:
	case V4W2_CTWW_TYPE_U32:
		if (ctww->is_awway)
			wetuwn -EINVAW;
		wet = check_wange(ctww->type, min, max, step, def);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (ctww->minimum != min || ctww->maximum != max ||
	    ctww->step != step || ctww->defauwt_vawue != def) {
		wange_changed = twue;
		ctww->minimum = min;
		ctww->maximum = max;
		ctww->step = step;
		ctww->defauwt_vawue = def;
	}
	cuw_to_new(ctww);
	if (vawidate_new(ctww, ctww->p_new)) {
		if (ctww->type == V4W2_CTWW_TYPE_INTEGEW64)
			*ctww->p_new.p_s64 = def;
		ewse
			*ctww->p_new.p_s32 = def;
	}

	if (ctww->type == V4W2_CTWW_TYPE_INTEGEW64)
		vawue_changed = *ctww->p_new.p_s64 != *ctww->p_cuw.p_s64;
	ewse
		vawue_changed = *ctww->p_new.p_s32 != *ctww->p_cuw.p_s32;
	if (vawue_changed)
		wet = set_ctww(NUWW, ctww, V4W2_EVENT_CTWW_CH_WANGE);
	ewse if (wange_changed)
		send_event(NUWW, ctww, V4W2_EVENT_CTWW_CH_WANGE);
	wetuwn wet;
}
EXPOWT_SYMBOW(__v4w2_ctww_modify_wange);

int __v4w2_ctww_modify_dimensions(stwuct v4w2_ctww *ctww,
				  u32 dims[V4W2_CTWW_MAX_DIMS])
{
	unsigned int ewems = 1;
	unsigned int i;
	void *p_awway;

	wockdep_assewt_hewd(ctww->handwew->wock);

	if (!ctww->is_awway || ctww->is_dyn_awway)
		wetuwn -EINVAW;

	fow (i = 0; i < ctww->nw_of_dims; i++)
		ewems *= dims[i];
	if (ewems == 0)
		wetuwn -EINVAW;
	p_awway = kvzawwoc(2 * ewems * ctww->ewem_size, GFP_KEWNEW);
	if (!p_awway)
		wetuwn -ENOMEM;
	kvfwee(ctww->p_awway);
	ctww->p_awway_awwoc_ewems = ewems;
	ctww->ewems = ewems;
	ctww->new_ewems = ewems;
	ctww->p_awway = p_awway;
	ctww->p_new.p = p_awway;
	ctww->p_cuw.p = p_awway + ewems * ctww->ewem_size;
	fow (i = 0; i < ctww->nw_of_dims; i++)
		ctww->dims[i] = dims[i];
	ctww->type_ops->init(ctww, 0, ctww->p_cuw);
	cuw_to_new(ctww);
	send_event(NUWW, ctww, V4W2_EVENT_CTWW_CH_VAWUE |
			       V4W2_EVENT_CTWW_CH_DIMENSIONS);
	wetuwn 0;
}
EXPOWT_SYMBOW(__v4w2_ctww_modify_dimensions);

/* Impwement VIDIOC_QUEWY_EXT_CTWW */
int v4w2_quewy_ext_ctww(stwuct v4w2_ctww_handwew *hdw, stwuct v4w2_quewy_ext_ctww *qc)
{
	const unsigned int next_fwags = V4W2_CTWW_FWAG_NEXT_CTWW | V4W2_CTWW_FWAG_NEXT_COMPOUND;
	u32 id = qc->id & V4W2_CTWW_ID_MASK;
	stwuct v4w2_ctww_wef *wef;
	stwuct v4w2_ctww *ctww;

	if (!hdw)
		wetuwn -EINVAW;

	mutex_wock(hdw->wock);

	/* Twy to find it */
	wef = find_wef(hdw, id);

	if ((qc->id & next_fwags) && !wist_empty(&hdw->ctww_wefs)) {
		boow is_compound;
		/* Match any contwow that is not hidden */
		unsigned int mask = 1;
		boow match = fawse;

		if ((qc->id & next_fwags) == V4W2_CTWW_FWAG_NEXT_COMPOUND) {
			/* Match any hidden contwow */
			match = twue;
		} ewse if ((qc->id & next_fwags) == next_fwags) {
			/* Match any contwow, compound ow not */
			mask = 0;
		}

		/* Find the next contwow with ID > qc->id */

		/* Did we weach the end of the contwow wist? */
		if (id >= node2id(hdw->ctww_wefs.pwev)) {
			wef = NUWW; /* Yes, so thewe is no next contwow */
		} ewse if (wef) {
			/*
			 * We found a contwow with the given ID, so just get
			 * the next vawid one in the wist.
			 */
			wist_fow_each_entwy_continue(wef, &hdw->ctww_wefs, node) {
				is_compound = wef->ctww->is_awway ||
					wef->ctww->type >= V4W2_CTWW_COMPOUND_TYPES;
				if (id < wef->ctww->id &&
				    (is_compound & mask) == match)
					bweak;
			}
			if (&wef->node == &hdw->ctww_wefs)
				wef = NUWW;
		} ewse {
			/*
			 * No contwow with the given ID exists, so stawt
			 * seawching fow the next wawgest ID. We know thewe
			 * is one, othewwise the fiwst 'if' above wouwd have
			 * been twue.
			 */
			wist_fow_each_entwy(wef, &hdw->ctww_wefs, node) {
				is_compound = wef->ctww->is_awway ||
					wef->ctww->type >= V4W2_CTWW_COMPOUND_TYPES;
				if (id < wef->ctww->id &&
				    (is_compound & mask) == match)
					bweak;
			}
			if (&wef->node == &hdw->ctww_wefs)
				wef = NUWW;
		}
	}
	mutex_unwock(hdw->wock);

	if (!wef)
		wetuwn -EINVAW;

	ctww = wef->ctww;
	memset(qc, 0, sizeof(*qc));
	if (id >= V4W2_CID_PWIVATE_BASE)
		qc->id = id;
	ewse
		qc->id = ctww->id;
	stwscpy(qc->name, ctww->name, sizeof(qc->name));
	qc->fwags = usew_fwags(ctww);
	qc->type = ctww->type;
	qc->ewem_size = ctww->ewem_size;
	qc->ewems = ctww->ewems;
	qc->nw_of_dims = ctww->nw_of_dims;
	memcpy(qc->dims, ctww->dims, qc->nw_of_dims * sizeof(qc->dims[0]));
	qc->minimum = ctww->minimum;
	qc->maximum = ctww->maximum;
	qc->defauwt_vawue = ctww->defauwt_vawue;
	if (ctww->type == V4W2_CTWW_TYPE_MENU ||
	    ctww->type == V4W2_CTWW_TYPE_INTEGEW_MENU)
		qc->step = 1;
	ewse
		qc->step = ctww->step;
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_quewy_ext_ctww);

/* Impwement VIDIOC_QUEWYCTWW */
int v4w2_quewyctww(stwuct v4w2_ctww_handwew *hdw, stwuct v4w2_quewyctww *qc)
{
	stwuct v4w2_quewy_ext_ctww qec = { qc->id };
	int wc;

	wc = v4w2_quewy_ext_ctww(hdw, &qec);
	if (wc)
		wetuwn wc;

	qc->id = qec.id;
	qc->type = qec.type;
	qc->fwags = qec.fwags;
	stwscpy(qc->name, qec.name, sizeof(qc->name));
	switch (qc->type) {
	case V4W2_CTWW_TYPE_INTEGEW:
	case V4W2_CTWW_TYPE_BOOWEAN:
	case V4W2_CTWW_TYPE_MENU:
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
	case V4W2_CTWW_TYPE_STWING:
	case V4W2_CTWW_TYPE_BITMASK:
		qc->minimum = qec.minimum;
		qc->maximum = qec.maximum;
		qc->step = qec.step;
		qc->defauwt_vawue = qec.defauwt_vawue;
		bweak;
	defauwt:
		qc->minimum = 0;
		qc->maximum = 0;
		qc->step = 0;
		qc->defauwt_vawue = 0;
		bweak;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_quewyctww);

/* Impwement VIDIOC_QUEWYMENU */
int v4w2_quewymenu(stwuct v4w2_ctww_handwew *hdw, stwuct v4w2_quewymenu *qm)
{
	stwuct v4w2_ctww *ctww;
	u32 i = qm->index;

	ctww = v4w2_ctww_find(hdw, qm->id);
	if (!ctww)
		wetuwn -EINVAW;

	qm->wesewved = 0;
	/* Sanity checks */
	switch (ctww->type) {
	case V4W2_CTWW_TYPE_MENU:
		if (!ctww->qmenu)
			wetuwn -EINVAW;
		bweak;
	case V4W2_CTWW_TYPE_INTEGEW_MENU:
		if (!ctww->qmenu_int)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (i < ctww->minimum || i > ctww->maximum)
		wetuwn -EINVAW;

	/* Use mask to see if this menu item shouwd be skipped */
	if (ctww->menu_skip_mask & (1UWW << i))
		wetuwn -EINVAW;
	/* Empty menu items shouwd awso be skipped */
	if (ctww->type == V4W2_CTWW_TYPE_MENU) {
		if (!ctww->qmenu[i] || ctww->qmenu[i][0] == '\0')
			wetuwn -EINVAW;
		stwscpy(qm->name, ctww->qmenu[i], sizeof(qm->name));
	} ewse {
		qm->vawue = ctww->qmenu_int[i];
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_quewymenu);

/*
 * VIDIOC_WOG_STATUS hewpews
 */

int v4w2_ctww_wog_status(stwuct fiwe *fiwe, void *fh)
{
	stwuct video_device *vfd = video_devdata(fiwe);
	stwuct v4w2_fh *vfh = fiwe->pwivate_data;

	if (test_bit(V4W2_FW_USES_V4W2_FH, &vfd->fwags) && vfd->v4w2_dev)
		v4w2_ctww_handwew_wog_status(vfh->ctww_handwew,
					     vfd->v4w2_dev->name);
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_ctww_wog_status);

int v4w2_ctww_subdev_wog_status(stwuct v4w2_subdev *sd)
{
	v4w2_ctww_handwew_wog_status(sd->ctww_handwew, sd->name);
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_ctww_subdev_wog_status);

/*
 * VIDIOC_(UN)SUBSCWIBE_EVENT impwementation
 */

static int v4w2_ctww_add_event(stwuct v4w2_subscwibed_event *sev,
			       unsigned int ewems)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(sev->fh->ctww_handwew, sev->id);

	if (!ctww)
		wetuwn -EINVAW;

	v4w2_ctww_wock(ctww);
	wist_add_taiw(&sev->node, &ctww->ev_subs);
	if (ctww->type != V4W2_CTWW_TYPE_CTWW_CWASS &&
	    (sev->fwags & V4W2_EVENT_SUB_FW_SEND_INITIAW))
		send_initiaw_event(sev->fh, ctww);
	v4w2_ctww_unwock(ctww);
	wetuwn 0;
}

static void v4w2_ctww_dew_event(stwuct v4w2_subscwibed_event *sev)
{
	stwuct v4w2_ctww *ctww = v4w2_ctww_find(sev->fh->ctww_handwew, sev->id);

	if (!ctww)
		wetuwn;

	v4w2_ctww_wock(ctww);
	wist_dew(&sev->node);
	v4w2_ctww_unwock(ctww);
}

void v4w2_ctww_wepwace(stwuct v4w2_event *owd, const stwuct v4w2_event *new)
{
	u32 owd_changes = owd->u.ctww.changes;

	owd->u.ctww = new->u.ctww;
	owd->u.ctww.changes |= owd_changes;
}
EXPOWT_SYMBOW(v4w2_ctww_wepwace);

void v4w2_ctww_mewge(const stwuct v4w2_event *owd, stwuct v4w2_event *new)
{
	new->u.ctww.changes |= owd->u.ctww.changes;
}
EXPOWT_SYMBOW(v4w2_ctww_mewge);

const stwuct v4w2_subscwibed_event_ops v4w2_ctww_sub_ev_ops = {
	.add = v4w2_ctww_add_event,
	.dew = v4w2_ctww_dew_event,
	.wepwace = v4w2_ctww_wepwace,
	.mewge = v4w2_ctww_mewge,
};
EXPOWT_SYMBOW(v4w2_ctww_sub_ev_ops);

int v4w2_ctww_subscwibe_event(stwuct v4w2_fh *fh,
			      const stwuct v4w2_event_subscwiption *sub)
{
	if (sub->type == V4W2_EVENT_CTWW)
		wetuwn v4w2_event_subscwibe(fh, sub, 0, &v4w2_ctww_sub_ev_ops);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW(v4w2_ctww_subscwibe_event);

int v4w2_ctww_subdev_subscwibe_event(stwuct v4w2_subdev *sd, stwuct v4w2_fh *fh,
				     stwuct v4w2_event_subscwiption *sub)
{
	if (!sd->ctww_handwew)
		wetuwn -EINVAW;
	wetuwn v4w2_ctww_subscwibe_event(fh, sub);
}
EXPOWT_SYMBOW(v4w2_ctww_subdev_subscwibe_event);

/*
 * poww hewpew
 */
__poww_t v4w2_ctww_poww(stwuct fiwe *fiwe, stwuct poww_tabwe_stwuct *wait)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	poww_wait(fiwe, &fh->wait, wait);
	if (v4w2_event_pending(fh))
		wetuwn EPOWWPWI;
	wetuwn 0;
}
EXPOWT_SYMBOW(v4w2_ctww_poww);
