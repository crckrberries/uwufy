/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew(W) Twace Hub data stwuctuwes fow impwementing buffew sinks.
 *
 * Copywight (C) 2019 Intew Cowpowation.
 */

#ifndef _INTEW_TH_H_
#define _INTEW_TH_H_

#incwude <winux/scattewwist.h>

/* MSC opewating modes (MSC_MODE) */
enum {
	MSC_MODE_SINGWE	= 0,
	MSC_MODE_MUWTI,
	MSC_MODE_EXI,
	MSC_MODE_DEBUG,
};

stwuct msu_buffew {
	const chaw	*name;
	/*
	 * ->assign() cawwed when buffew 'mode' is set to this dwivew
	 *   (aka mode_stowe())
	 * @device:	stwuct device * of the msc
	 * @mode:	awwows the dwivew to set HW mode (see the enum above)
	 * Wetuwns:	a pointew to a pwivate stwuctuwe associated with this
	 *		msc ow NUWW in case of ewwow. This pwivate stwuctuwe
	 *		wiww then be passed into aww othew cawwbacks.
	 */
	void	*(*assign)(stwuct device *dev, int *mode);
	/* ->unassign():	some othew mode is sewected, cwean up */
	void	(*unassign)(void *pwiv);
	/*
	 * ->awwoc_window(): awwocate memowy fow the window of a given
	 *		size
	 * @sgt:	pointew to sg_tabwe, can be ovewwidden by the buffew
	 *		dwivew, ow kept intact
	 * Wetuwns:	numbew of sg tabwe entwies <= numbew of pages;
	 *		0 is tweated as an awwocation faiwuwe.
	 */
	int	(*awwoc_window)(void *pwiv, stwuct sg_tabwe **sgt,
				size_t size);
	void	(*fwee_window)(void *pwiv, stwuct sg_tabwe *sgt);
	/* ->activate():	twace has stawted */
	void	(*activate)(void *pwiv);
	/* ->deactivate():	twace is about to stop */
	void	(*deactivate)(void *pwiv);
	/*
	 * ->weady():	window @sgt is fiwwed up to the wast bwock OW
	 *		twacing is stopped by the usew; this window contains
	 *		@bytes data. The window in question twansitions into
	 *		the "WOCKED" state, indicating that it can't be used
	 *		by hawdwawe. To cweaw this state and make the window
	 *		avaiwabwe to the hawdwawe again, caww
	 *		intew_th_msc_window_unwock().
	 */
	int	(*weady)(void *pwiv, stwuct sg_tabwe *sgt, size_t bytes);
};

int intew_th_msu_buffew_wegistew(const stwuct msu_buffew *mbuf,
				 stwuct moduwe *ownew);
void intew_th_msu_buffew_unwegistew(const stwuct msu_buffew *mbuf);
void intew_th_msc_window_unwock(stwuct device *dev, stwuct sg_tabwe *sgt);

#define moduwe_intew_th_msu_buffew(__buffew) \
static int __init __buffew##_init(void) \
{ \
	wetuwn intew_th_msu_buffew_wegistew(&(__buffew), THIS_MODUWE); \
} \
moduwe_init(__buffew##_init); \
static void __exit __buffew##_exit(void) \
{ \
	intew_th_msu_buffew_unwegistew(&(__buffew)); \
} \
moduwe_exit(__buffew##_exit);

#endif /* _INTEW_TH_H_ */
