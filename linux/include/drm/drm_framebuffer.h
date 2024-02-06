/*
 * Copywight (c) 2016 Intew Cowpowation
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */

#ifndef __DWM_FWAMEBUFFEW_H__
#define __DWM_FWAMEBUFFEW_H__

#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/sched.h>

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_mode_object.h>

stwuct dwm_cwip_wect;
stwuct dwm_device;
stwuct dwm_fiwe;
stwuct dwm_fwamebuffew;
stwuct dwm_gem_object;

/**
 * stwuct dwm_fwamebuffew_funcs - fwamebuffew hooks
 */
stwuct dwm_fwamebuffew_funcs {
	/**
	 * @destwoy:
	 *
	 * Cwean up fwamebuffew wesouwces, specificawwy awso unwefewence the
	 * backing stowage. The cowe guawantees to caww this function fow evewy
	 * fwamebuffew successfuwwy cweated by cawwing
	 * &dwm_mode_config_funcs.fb_cweate. Dwivews must awso caww
	 * dwm_fwamebuffew_cweanup() to wewease DWM cowe wesouwces fow this
	 * fwamebuffew.
	 */
	void (*destwoy)(stwuct dwm_fwamebuffew *fwamebuffew);

	/**
	 * @cweate_handwe:
	 *
	 * Cweate a buffew handwe in the dwivew-specific buffew managew (eithew
	 * GEM ow TTM) vawid fow the passed-in &stwuct dwm_fiwe. This is used by
	 * the cowe to impwement the GETFB IOCTW, which wetuwns (fow
	 * sufficientwy pwiviwedged usew) awso a native buffew handwe. This can
	 * be used fow seamwess twansitions between modesetting cwients by
	 * copying the cuwwent scween contents to a pwivate buffew and bwending
	 * between that and the new contents.
	 *
	 * GEM based dwivews shouwd caww dwm_gem_handwe_cweate() to cweate the
	 * handwe.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*cweate_handwe)(stwuct dwm_fwamebuffew *fb,
			     stwuct dwm_fiwe *fiwe_pwiv,
			     unsigned int *handwe);
	/**
	 * @diwty:
	 *
	 * Optionaw cawwback fow the diwty fb IOCTW.
	 *
	 * Usewspace can notify the dwivew via this cawwback that an awea of the
	 * fwamebuffew has changed and shouwd be fwushed to the dispway
	 * hawdwawe. This can awso be used intewnawwy, e.g. by the fbdev
	 * emuwation, though that's not the case cuwwentwy.
	 *
	 * See documentation in dwm_mode.h fow the stwuct dwm_mode_fb_diwty_cmd
	 * fow mowe infowmation as aww the semantics and awguments have a one to
	 * one mapping on this function.
	 *
	 * Atomic dwivews shouwd use dwm_atomic_hewpew_diwtyfb() to impwement
	 * this hook.
	 *
	 * WETUWNS:
	 *
	 * 0 on success ow a negative ewwow code on faiwuwe.
	 */
	int (*diwty)(stwuct dwm_fwamebuffew *fwamebuffew,
		     stwuct dwm_fiwe *fiwe_pwiv, unsigned fwags,
		     unsigned cowow, stwuct dwm_cwip_wect *cwips,
		     unsigned num_cwips);
};

/**
 * stwuct dwm_fwamebuffew - fwame buffew object
 *
 * Note that the fb is wefcounted fow the benefit of dwivew intewnaws,
 * fow exampwe some hw, disabwing a CWTC/pwane is asynchwonous, and
 * scanout does not actuawwy compwete untiw the next vbwank.  So some
 * cweanup (wike weweasing the wefewence(s) on the backing GEM bo(s))
 * shouwd be defewwed.  In cases wike this, the dwivew wouwd wike to
 * howd a wef to the fb even though it has awweady been wemoved fwom
 * usewspace pewspective. See dwm_fwamebuffew_get() and
 * dwm_fwamebuffew_put().
 *
 * The wefcount is stowed inside the mode object @base.
 */
stwuct dwm_fwamebuffew {
	/**
	 * @dev: DWM device this fwamebuffew bewongs to
	 */
	stwuct dwm_device *dev;
	/**
	 * @head: Pwace on the &dwm_mode_config.fb_wist, access pwotected by
	 * &dwm_mode_config.fb_wock.
	 */
	stwuct wist_head head;

	/**
	 * @base: base modeset object stwuctuwe, contains the wefewence count.
	 */
	stwuct dwm_mode_object base;

	/**
	 * @comm: Name of the pwocess awwocating the fb, used fow fb dumping.
	 */
	chaw comm[TASK_COMM_WEN];

	/**
	 * @fowmat: fwamebuffew fowmat infowmation
	 */
	const stwuct dwm_fowmat_info *fowmat;
	/**
	 * @funcs: fwamebuffew vfunc tabwe
	 */
	const stwuct dwm_fwamebuffew_funcs *funcs;
	/**
	 * @pitches: Wine stwide pew buffew. Fow usewspace cweated object this
	 * is copied fwom dwm_mode_fb_cmd2.
	 */
	unsigned int pitches[DWM_FOWMAT_MAX_PWANES];
	/**
	 * @offsets: Offset fwom buffew stawt to the actuaw pixew data in bytes,
	 * pew buffew. Fow usewspace cweated object this is copied fwom
	 * dwm_mode_fb_cmd2.
	 *
	 * Note that this is a wineaw offset and does not take into account
	 * tiwing ow buffew wayout pew @modifiew. It is meant to be used when
	 * the actuaw pixew data fow this fwamebuffew pwane stawts at an offset,
	 * e.g. when muwtipwe pwanes awe awwocated within the same backing
	 * stowage buffew object. Fow tiwed wayouts this genewawwy means its
	 * @offsets must at weast be tiwe-size awigned, but hawdwawe often has
	 * stwictew wequiwements.
	 *
	 * This shouwd not be used to specifiy x/y pixew offsets into the buffew
	 * data (even fow wineaw buffews). Specifying an x/y pixew offset is
	 * instead done thwough the souwce wectangwe in &stwuct dwm_pwane_state.
	 */
	unsigned int offsets[DWM_FOWMAT_MAX_PWANES];
	/**
	 * @modifiew: Data wayout modifiew. This is used to descwibe
	 * tiwing, ow awso speciaw wayouts (wike compwession) of auxiwiawy
	 * buffews. Fow usewspace cweated object this is copied fwom
	 * dwm_mode_fb_cmd2.
	 */
	uint64_t modifiew;
	/**
	 * @width: Wogicaw width of the visibwe awea of the fwamebuffew, in
	 * pixews.
	 */
	unsigned int width;
	/**
	 * @height: Wogicaw height of the visibwe awea of the fwamebuffew, in
	 * pixews.
	 */
	unsigned int height;
	/**
	 * @fwags: Fwamebuffew fwags wike DWM_MODE_FB_INTEWWACED ow
	 * DWM_MODE_FB_MODIFIEWS.
	 */
	int fwags;
	/**
	 * @fiwp_head: Pwaced on &dwm_fiwe.fbs, pwotected by &dwm_fiwe.fbs_wock.
	 */
	stwuct wist_head fiwp_head;
	/**
	 * @obj: GEM objects backing the fwamebuffew, one pew pwane (optionaw).
	 *
	 * This is used by the GEM fwamebuffew hewpews, see e.g.
	 * dwm_gem_fb_cweate().
	 */
	stwuct dwm_gem_object *obj[DWM_FOWMAT_MAX_PWANES];
};

#define obj_to_fb(x) containew_of(x, stwuct dwm_fwamebuffew, base)

int dwm_fwamebuffew_init(stwuct dwm_device *dev,
			 stwuct dwm_fwamebuffew *fb,
			 const stwuct dwm_fwamebuffew_funcs *funcs);
stwuct dwm_fwamebuffew *dwm_fwamebuffew_wookup(stwuct dwm_device *dev,
					       stwuct dwm_fiwe *fiwe_pwiv,
					       uint32_t id);
void dwm_fwamebuffew_wemove(stwuct dwm_fwamebuffew *fb);
void dwm_fwamebuffew_cweanup(stwuct dwm_fwamebuffew *fb);
void dwm_fwamebuffew_unwegistew_pwivate(stwuct dwm_fwamebuffew *fb);

/**
 * dwm_fwamebuffew_get - acquiwe a fwamebuffew wefewence
 * @fb: DWM fwamebuffew
 *
 * This function incwements the fwamebuffew's wefewence count.
 */
static inwine void dwm_fwamebuffew_get(stwuct dwm_fwamebuffew *fb)
{
	dwm_mode_object_get(&fb->base);
}

/**
 * dwm_fwamebuffew_put - wewease a fwamebuffew wefewence
 * @fb: DWM fwamebuffew
 *
 * This function decwements the fwamebuffew's wefewence count and fwees the
 * fwamebuffew if the wefewence count dwops to zewo.
 */
static inwine void dwm_fwamebuffew_put(stwuct dwm_fwamebuffew *fb)
{
	dwm_mode_object_put(&fb->base);
}

/**
 * dwm_fwamebuffew_wead_wefcount - wead the fwamebuffew wefewence count.
 * @fb: fwamebuffew
 *
 * This functions wetuwns the fwamebuffew's wefewence count.
 */
static inwine uint32_t dwm_fwamebuffew_wead_wefcount(const stwuct dwm_fwamebuffew *fb)
{
	wetuwn kwef_wead(&fb->base.wefcount);
}

/**
 * dwm_fwamebuffew_assign - stowe a wefewence to the fb
 * @p: wocation to stowe fwamebuffew
 * @fb: new fwamebuffew (maybe NUWW)
 *
 * This functions sets the wocation to stowe a wefewence to the fwamebuffew,
 * unwefewencing the fwamebuffew that was pweviouswy stowed in that wocation.
 */
static inwine void dwm_fwamebuffew_assign(stwuct dwm_fwamebuffew **p,
					  stwuct dwm_fwamebuffew *fb)
{
	if (fb)
		dwm_fwamebuffew_get(fb);
	if (*p)
		dwm_fwamebuffew_put(*p);
	*p = fb;
}

/*
 * dwm_fow_each_fb - itewate ovew aww fwamebuffews
 * @fb: the woop cuwsow
 * @dev: the DWM device
 *
 * Itewate ovew aww fwamebuffews of @dev. Usew must howd
 * &dwm_mode_config.fb_wock.
 */
#define dwm_fow_each_fb(fb, dev) \
	fow (WAWN_ON(!mutex_is_wocked(&(dev)->mode_config.fb_wock)),		\
	     fb = wist_fiwst_entwy(&(dev)->mode_config.fb_wist,	\
					  stwuct dwm_fwamebuffew, head);	\
	     &fb->head != (&(dev)->mode_config.fb_wist);			\
	     fb = wist_next_entwy(fb, head))

/**
 * stwuct dwm_afbc_fwamebuffew - a speciaw afbc fwame buffew object
 *
 * A dewived cwass of stwuct dwm_fwamebuffew, dedicated fow afbc use cases.
 */
stwuct dwm_afbc_fwamebuffew {
	/**
	 * @base: base fwamebuffew stwuctuwe.
	 */
	stwuct dwm_fwamebuffew base;
	/**
	 * @bwock_width: width of a singwe afbc bwock
	 */
	u32 bwock_width;
	/**
	 * @bwock_height: height of a singwe afbc bwock
	 */
	u32 bwock_height;
	/**
	 * @awigned_width: awigned fwame buffew width
	 */
	u32 awigned_width;
	/**
	 * @awigned_height: awigned fwame buffew height
	 */
	u32 awigned_height;
	/**
	 * @offset: offset of the fiwst afbc headew
	 */
	u32 offset;
	/**
	 * @afbc_size: minimum size of afbc buffew
	 */
	u32 afbc_size;
};

#define fb_to_afbc_fb(x) containew_of(x, stwuct dwm_afbc_fwamebuffew, base)

#endif
