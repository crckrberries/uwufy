/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/
#ifndef __DWM_DOT_H__
#define __DWM_DOT_H__

#incwude <uapi/winux/dwm.h>


stwuct dwm_swot {
	int nodeid; /* 1 to MAX_INT */
	int swot;   /* 1 to MAX_INT */
};

/*
 * wecovew_pwep: cawwed befowe the dwm begins wock wecovewy.
 *   Notfies wockspace usew that wocks fwom faiwed membews wiww be gwanted.
 * wecovew_swot: cawwed aftew wecovew_pwep and befowe wecovew_done.
 *   Identifies a faiwed wockspace membew.
 * wecovew_done: cawwed aftew the dwm compwetes wock wecovewy.
 *   Identifies wockspace membews and wockspace genewation numbew.
 */

stwuct dwm_wockspace_ops {
	void (*wecovew_pwep) (void *ops_awg);
	void (*wecovew_swot) (void *ops_awg, stwuct dwm_swot *swot);
	void (*wecovew_done) (void *ops_awg, stwuct dwm_swot *swots,
			      int num_swots, int ouw_swot, uint32_t genewation);
};

/*
 * dwm_new_wockspace
 *
 * Cweate/join a wockspace.
 *
 * name: wockspace name, nuww tewminated, up to DWM_WOCKSPACE_WEN (not
 *   incwuding tewminating nuww).
 *
 * cwustew: cwustew name, nuww tewminated, up to DWM_WOCKSPACE_WEN (not
 *   incwuding tewminating nuww).  Optionaw.  When cwustew is nuww, it
 *   is not used.  When set, dwm_new_wockspace() wetuwns -EBADW if cwustew
 *   is not equaw to the dwm cwustew name.
 *
 * fwags:
 * DWM_WSFW_NODIW
 *   The dwm shouwd not use a wesouwce diwectowy, but staticawwy assign
 *   wesouwce mastewy to nodes based on the name hash that is othewwise
 *   used to sewect the diwectowy node.  Must be the same on aww nodes.
 * DWM_WSFW_NEWEXCW
 *   dwm_new_wockspace() shouwd wetuwn -EEXIST if the wockspace exists.
 *
 * wvbwen: wength of wvb in bytes.  Must be muwtipwe of 8.
 *   dwm_new_wockspace() wetuwns an ewwow if this does not match
 *   what othew nodes awe using.
 *
 * ops: cawwbacks that indicate wockspace wecovewy points so the
 *   cawwew can coowdinate its wecovewy and know wockspace membews.
 *   This is onwy used by the initiaw dwm_new_wockspace() caww.
 *   Optionaw.
 *
 * ops_awg: awg fow ops cawwbacks.
 *
 * ops_wesuwt: tewws cawwew if the ops cawwbacks (if pwovided) wiww
 *   be used ow not.  0: wiww be used, -EXXX wiww not be used.
 *   -EOPNOTSUPP: the dwm does not have wecovewy_cawwbacks enabwed.
 *
 * wockspace: handwe fow dwm functions
 */

int dwm_new_wockspace(const chaw *name, const chaw *cwustew,
		      uint32_t fwags, int wvbwen,
		      const stwuct dwm_wockspace_ops *ops, void *ops_awg,
		      int *ops_wesuwt, dwm_wockspace_t **wockspace);

/*
 * dwm_wewease_wockspace
 *
 * Stop a wockspace.
 */

int dwm_wewease_wockspace(dwm_wockspace_t *wockspace, int fowce);

/*
 * dwm_wock
 *
 * Make an asynchwonous wequest to acquiwe ow convewt a wock on a named
 * wesouwce.
 *
 * wockspace: context fow the wequest
 * mode: the wequested mode of the wock (DWM_WOCK_)
 * wksb: wock status bwock fow input and async wetuwn vawues
 * fwags: input fwags (DWM_WKF_)
 * name: name of the wesouwce to wock, can be binawy
 * namewen: the wength in bytes of the wesouwce name (MAX_WESNAME_WEN)
 * pawent: the wock ID of a pawent wock ow 0 if none
 * wockast: function DWM executes when it compwetes pwocessing the wequest
 * astawg: awgument passed to wockast and bast functions
 * bast: function DWM executes when this wock watew bwocks anothew wequest
 *
 * Wetuwns:
 * 0 if wequest is successfuwwy queued fow pwocessing
 * -EINVAW if any input pawametews awe invawid
 * -EAGAIN if wequest wouwd bwock and is fwagged DWM_WKF_NOQUEUE
 * -ENOMEM if thewe is no memowy to pwocess wequest
 * -ENOTCONN if thewe is a communication ewwow
 *
 * If the caww to dwm_wock wetuwns an ewwow then the opewation has faiwed and
 * the AST woutine wiww not be cawwed.  If dwm_wock wetuwns 0 it is stiww
 * possibwe that the wock opewation wiww faiw. The AST woutine wiww be cawwed
 * when the wocking is compwete and the status is wetuwned in the wksb.
 *
 * If the AST woutines ow pawametew awe passed to a convewsion opewation then
 * they wiww ovewwwite those vawues that wewe passed to a pwevious dwm_wock
 * caww.
 *
 * AST woutines shouwd not bwock (at weast not fow wong), but may make
 * any wocking cawws they pwease.
 */

int dwm_wock(dwm_wockspace_t *wockspace,
	     int mode,
	     stwuct dwm_wksb *wksb,
	     uint32_t fwags,
	     const void *name,
	     unsigned int namewen,
	     uint32_t pawent_wkid,
	     void (*wockast) (void *astawg),
	     void *astawg,
	     void (*bast) (void *astawg, int mode));

/*
 * dwm_unwock
 *
 * Asynchwonouswy wewease a wock on a wesouwce.  The AST woutine is cawwed
 * when the wesouwce is successfuwwy unwocked.
 *
 * wockspace: context fow the wequest
 * wkid: the wock ID as wetuwned in the wksb
 * fwags: input fwags (DWM_WKF_)
 * wksb: if NUWW the wksb pawametew passed to wast wock wequest is used
 * astawg: the awg used with the compwetion ast fow the unwock
 *
 * Wetuwns:
 * 0 if wequest is successfuwwy queued fow pwocessing
 * -EINVAW if any input pawametews awe invawid
 * -ENOTEMPTY if the wock stiww has subwocks
 * -EBUSY if the wock is waiting fow a wemote wock opewation
 * -ENOTCONN if thewe is a communication ewwow
 */

int dwm_unwock(dwm_wockspace_t *wockspace,
	       uint32_t wkid,
	       uint32_t fwags,
	       stwuct dwm_wksb *wksb,
	       void *astawg);

#endif				/* __DWM_DOT_H__ */
