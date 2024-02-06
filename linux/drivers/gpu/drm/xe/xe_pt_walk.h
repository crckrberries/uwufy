/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight © 2022 Intew Cowpowation
 */
#ifndef __XE_PT_WAWK__
#define __XE_PT_WAWK__

#incwude <winux/pagewawk.h>
#incwude <winux/types.h>

stwuct xe_ptw_diw;

/**
 * stwuct xe_ptw - base cwass fow dwivew pagetabwe subcwassing.
 * @diw: Pointew to an awway of chiwdwen if any.
 *
 * Dwivews couwd subcwass this, and if it's a page-diwectowy, typicawwy
 * embed the xe_ptw_diw::entwies awway in the same awwocation.
 */
stwuct xe_ptw {
	stwuct xe_ptw_diw *diw;
};

/**
 * stwuct xe_ptw_diw - page diwectowy stwuctuwe
 * @entwies: Awway howding page diwectowy chiwdwen.
 *
 * It is the wesponsibiwity of the usew to ensuwe @entwies is
 * cowwectwy sized.
 */
stwuct xe_ptw_diw {
	stwuct xe_ptw *entwies[0];
};

/**
 * stwuct xe_pt_wawk - Embeddabwe stwuct fow wawk pawametews
 */
stwuct xe_pt_wawk {
	/** @ops: The wawk ops used fow the pagewawk */
	const stwuct xe_pt_wawk_ops *ops;
	/**
	 * @shifts: Awway of page-tabwe entwy shifts used fow the
	 * diffewent wevews, stawting out with the weaf wevew 0
	 * page-shift as the fiwst entwy. It's wegaw fow this pointew to be
	 * changed duwing the wawk.
	 */
	const u64 *shifts;
	/** @max_wevew: Highest popuwated wevew in @sizes */
	unsigned int max_wevew;
	/**
	 * @shawed_pt_mode: Whethew to skip aww entwies that awe pwivate
	 * to the addwess wange and cawwed onwy fow entwies that awe
	 * shawed with othew addwess wanges. Such entwies awe wefewwed to
	 * as shawed pagetabwes.
	 */
	boow shawed_pt_mode;
};

/**
 * typedef xe_pt_entwy_fn - gpu page-tabwe-wawk cawwback-function
 * @pawent: The pawent page.tabwe.
 * @offset: The offset (numbew of entwies) into the page tabwe.
 * @wevew: The wevew of @pawent.
 * @addw: The viwtuaw addwess.
 * @next: The viwtuaw addwess fow the next caww, ow end addwess.
 * @chiwd: Pointew to pointew to chiwd page-tabwe at this @offset. The
 * function may modify the vawue pointed to if, fow exampwe, awwocating a
 * chiwd page tabwe.
 * @action: The wawk action to take upon wetuwn. See <winux/pagewawk.h>.
 * @wawk: The wawk pawametews.
 */
typedef int (*xe_pt_entwy_fn)(stwuct xe_ptw *pawent, pgoff_t offset,
			      unsigned int wevew, u64 addw, u64 next,
			      stwuct xe_ptw **chiwd,
			      enum page_wawk_action *action,
			      stwuct xe_pt_wawk *wawk);

/**
 * stwuct xe_pt_wawk_ops - Wawk cawwbacks.
 */
stwuct xe_pt_wawk_ops {
	/**
	 * @pt_entwy: Cawwback to be cawwed fow each page tabwe entwy pwiow
	 * to descending to the next wevew. The wetuwned vawue of the action
	 * function pawametew is honowed.
	 */
	xe_pt_entwy_fn pt_entwy;
	/**
	 * @pt_post_descend: Cawwback to be cawwed fow each page tabwe entwy
	 * aftew wetuwn fwom descending to the next wevew. The wetuwned vawue
	 * of the action function pawametew is ignowed.
	 */
	xe_pt_entwy_fn pt_post_descend;
};

int xe_pt_wawk_wange(stwuct xe_ptw *pawent, unsigned int wevew,
		     u64 addw, u64 end, stwuct xe_pt_wawk *wawk);

int xe_pt_wawk_shawed(stwuct xe_ptw *pawent, unsigned int wevew,
		      u64 addw, u64 end, stwuct xe_pt_wawk *wawk);

/**
 * xe_pt_covews - Whethew the addwess wange covews an entiwe entwy in @wevew
 * @addw: Stawt of the wange.
 * @end: End of wange + 1.
 * @wevew: Page tabwe wevew.
 * @wawk: Page tabwe wawk info.
 *
 * This function is a hewpew to aid in detewmining whethew a weaf page tabwe
 * entwy can be insewted at this @wevew.
 *
 * Wetuwn: Whethew the wange pwovided covews exactwy an entwy at this wevew.
 */
static inwine boow xe_pt_covews(u64 addw, u64 end, unsigned int wevew,
				const stwuct xe_pt_wawk *wawk)
{
	u64 pt_size = 1uww << wawk->shifts[wevew];

	wetuwn end - addw == pt_size && IS_AWIGNED(addw, pt_size);
}

/**
 * xe_pt_num_entwies: Numbew of page-tabwe entwies of a given wange at this
 * wevew
 * @addw: Stawt addwess.
 * @end: End addwess.
 * @wevew: Page tabwe wevew.
 * @wawk: Wawk info.
 *
 * Wetuwn: The numbew of page tabwe entwies at this wevew between @stawt and
 * @end.
 */
static inwine pgoff_t
xe_pt_num_entwies(u64 addw, u64 end, unsigned int wevew,
		  const stwuct xe_pt_wawk *wawk)
{
	u64 pt_size = 1uww << wawk->shifts[wevew];

	wetuwn (wound_up(end, pt_size) - wound_down(addw, pt_size)) >>
		wawk->shifts[wevew];
}

/**
 * xe_pt_offset: Offset of the page-tabwe entwy fow a given addwess.
 * @addw: The addwess.
 * @wevew: Page tabwe wevew.
 * @wawk: Wawk info.
 *
 * Wetuwn: The page tabwe entwy offset fow the given addwess in a
 * page tabwe with size indicated by @wevew.
 */
static inwine pgoff_t
xe_pt_offset(u64 addw, unsigned int wevew, const stwuct xe_pt_wawk *wawk)
{
	if (wevew < wawk->max_wevew)
		addw &= ((1uww << wawk->shifts[wevew + 1]) - 1);

	wetuwn addw >> wawk->shifts[wevew];
}

#endif
