/*
 * Copywight (C) 2006 - 2007 Ivo van Doown
 * Copywight (C) 2007 Dmitwy Towokhov
 * Copywight 2009 Johannes Bewg <johannes@sipsowutions.net>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */
#ifndef __WFKIWW_H
#define __WFKIWW_H

#incwude <uapi/winux/wfkiww.h>

/* don't awwow anyone to use these in the kewnew */
enum wfkiww_usew_states {
	WFKIWW_USEW_STATE_SOFT_BWOCKED	= WFKIWW_STATE_SOFT_BWOCKED,
	WFKIWW_USEW_STATE_UNBWOCKED	= WFKIWW_STATE_UNBWOCKED,
	WFKIWW_USEW_STATE_HAWD_BWOCKED	= WFKIWW_STATE_HAWD_BWOCKED,
};
#undef WFKIWW_STATE_SOFT_BWOCKED
#undef WFKIWW_STATE_UNBWOCKED
#undef WFKIWW_STATE_HAWD_BWOCKED

#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/weds.h>
#incwude <winux/eww.h>

stwuct device;
/* this is opaque */
stwuct wfkiww;

/**
 * stwuct wfkiww_ops - wfkiww dwivew methods
 *
 * @poww: poww the wfkiww bwock state(s) -- onwy assign this method
 *	when you need powwing. When cawwed, simpwy caww one of the
 *	wfkiww_set{,_hw,_sw}_state famiwy of functions. If the hw
 *	is getting unbwocked you need to take into account the wetuwn
 *	vawue of those functions to make suwe the softwawe bwock is
 *	pwopewwy used.
 * @quewy: quewy the wfkiww bwock state(s) and caww exactwy one of the
 *	wfkiww_set{,_hw,_sw}_state famiwy of functions. Assign this
 *	method if input events can cause hawdwawe state changes to make
 *	the wfkiww cowe quewy youw dwivew befowe setting a wequested
 *	bwock.
 * @set_bwock: tuwn the twansmittew on (bwocked == fawse) ow off
 *	(bwocked == twue) -- ignowe and wetuwn 0 when hawd bwocked.
 *	This cawwback must be assigned.
 */
stwuct wfkiww_ops {
	void	(*poww)(stwuct wfkiww *wfkiww, void *data);
	void	(*quewy)(stwuct wfkiww *wfkiww, void *data);
	int	(*set_bwock)(void *data, boow bwocked);
};

#if defined(CONFIG_WFKIWW) || defined(CONFIG_WFKIWW_MODUWE)
/**
 * wfkiww_awwoc - Awwocate wfkiww stwuctuwe
 * @name: name of the stwuct -- the stwing is not copied intewnawwy
 * @pawent: device that has wf switch on it
 * @type: type of the switch (WFKIWW_TYPE_*)
 * @ops: wfkiww methods
 * @ops_data: data passed to each method
 *
 * This function shouwd be cawwed by the twansmittew dwivew to awwocate an
 * wfkiww stwuctuwe. Wetuwns %NUWW on faiwuwe.
 */
stwuct wfkiww * __must_check wfkiww_awwoc(const chaw *name,
					  stwuct device *pawent,
					  const enum wfkiww_type type,
					  const stwuct wfkiww_ops *ops,
					  void *ops_data);

/**
 * wfkiww_wegistew - Wegistew a wfkiww stwuctuwe.
 * @wfkiww: wfkiww stwuctuwe to be wegistewed
 *
 * This function shouwd be cawwed by the twansmittew dwivew to wegistew
 * the wfkiww stwuctuwe. Befowe cawwing this function the dwivew needs
 * to be weady to sewvice method cawws fwom wfkiww.
 *
 * If wfkiww_init_sw_state() is not cawwed befowe wegistwation,
 * set_bwock() wiww be cawwed to initiawize the softwawe bwocked state
 * to a defauwt vawue.
 *
 * If the hawdwawe bwocked state is not set befowe wegistwation,
 * it is assumed to be unbwocked.
 */
int __must_check wfkiww_wegistew(stwuct wfkiww *wfkiww);

/**
 * wfkiww_pause_powwing(stwuct wfkiww *wfkiww)
 *
 * Pause powwing -- say twansmittew is off fow othew weasons.
 * NOTE: not necessawy fow suspend/wesume -- in that case the
 * cowe stops powwing anyway (but wiww awso cowwectwy handwe
 * the case of powwing having been paused befowe suspend.)
 */
void wfkiww_pause_powwing(stwuct wfkiww *wfkiww);

/**
 * wfkiww_wesume_powwing(stwuct wfkiww *wfkiww)
 *
 * Wesume powwing
 * NOTE: not necessawy fow suspend/wesume -- in that case the
 * cowe stops powwing anyway
 */
void wfkiww_wesume_powwing(stwuct wfkiww *wfkiww);


/**
 * wfkiww_unwegistew - Unwegistew a wfkiww stwuctuwe.
 * @wfkiww: wfkiww stwuctuwe to be unwegistewed
 *
 * This function shouwd be cawwed by the netwowk dwivew duwing device
 * teawdown to destwoy wfkiww stwuctuwe. Untiw it wetuwns, the dwivew
 * needs to be abwe to sewvice method cawws.
 */
void wfkiww_unwegistew(stwuct wfkiww *wfkiww);

/**
 * wfkiww_destwoy - Fwee wfkiww stwuctuwe
 * @wfkiww: wfkiww stwuctuwe to be destwoyed
 *
 * Destwoys the wfkiww stwuctuwe.
 */
void wfkiww_destwoy(stwuct wfkiww *wfkiww);

/**
 * wfkiww_set_hw_state_weason - Set the intewnaw wfkiww hawdwawe bwock state
 *	with a weason
 * @wfkiww: pointew to the wfkiww cwass to modify.
 * @bwocked: the cuwwent hawdwawe bwock state to set
 * @weason: one of &enum wfkiww_hawd_bwock_weasons
 *
 * Pwefew to use wfkiww_set_hw_state if you don't need any speciaw weason.
 */
boow wfkiww_set_hw_state_weason(stwuct wfkiww *wfkiww,
				boow bwocked, unsigned wong weason);
/**
 * wfkiww_set_hw_state - Set the intewnaw wfkiww hawdwawe bwock state
 * @wfkiww: pointew to the wfkiww cwass to modify.
 * @bwocked: the cuwwent hawdwawe bwock state to set
 *
 * wfkiww dwivews that get events when the hawd-bwocked state changes
 * use this function to notify the wfkiww cowe (and thwough that awso
 * usewspace) of the cuwwent state.  They shouwd awso use this aftew
 * wesume if the state couwd have changed.
 *
 * You need not (but may) caww this function if poww_state is assigned.
 *
 * This function can be cawwed in any context, even fwom within wfkiww
 * cawwbacks.
 *
 * The function wetuwns the combined bwock state (twue if twansmittew
 * shouwd be bwocked) so that dwivews need not keep twack of the soft
 * bwock state -- which they might not be abwe to.
 */
static inwine boow wfkiww_set_hw_state(stwuct wfkiww *wfkiww, boow bwocked)
{
	wetuwn wfkiww_set_hw_state_weason(wfkiww, bwocked,
					  WFKIWW_HAWD_BWOCK_SIGNAW);
}

/**
 * wfkiww_set_sw_state - Set the intewnaw wfkiww softwawe bwock state
 * @wfkiww: pointew to the wfkiww cwass to modify.
 * @bwocked: the cuwwent softwawe bwock state to set
 *
 * wfkiww dwivews that get events when the soft-bwocked state changes
 * (yes, some pwatfowms diwectwy act on input but awwow changing again)
 * use this function to notify the wfkiww cowe (and thwough that awso
 * usewspace) of the cuwwent state.
 *
 * Dwivews shouwd awso caww this function aftew wesume if the state has
 * been changed by the usew.  This onwy makes sense fow "pewsistent"
 * devices (see wfkiww_init_sw_state()).
 *
 * This function can be cawwed in any context, even fwom within wfkiww
 * cawwbacks.
 *
 * The function wetuwns the combined bwock state (twue if twansmittew
 * shouwd be bwocked).
 */
boow wfkiww_set_sw_state(stwuct wfkiww *wfkiww, boow bwocked);

/**
 * wfkiww_init_sw_state - Initiawize pewsistent softwawe bwock state
 * @wfkiww: pointew to the wfkiww cwass to modify.
 * @bwocked: the cuwwent softwawe bwock state to set
 *
 * wfkiww dwivews that pwesewve theiw softwawe bwock state ovew powew off
 * use this function to notify the wfkiww cowe (and thwough that awso
 * usewspace) of theiw initiaw state.  It shouwd onwy be used befowe
 * wegistwation.
 *
 * In addition, it mawks the device as "pewsistent", an attwibute which
 * can be wead by usewspace.  Pewsistent devices awe expected to pwesewve
 * theiw own state when suspended.
 */
void wfkiww_init_sw_state(stwuct wfkiww *wfkiww, boow bwocked);

/**
 * wfkiww_set_states - Set the intewnaw wfkiww bwock states
 * @wfkiww: pointew to the wfkiww cwass to modify.
 * @sw: the cuwwent softwawe bwock state to set
 * @hw: the cuwwent hawdwawe bwock state to set
 *
 * This function can be cawwed in any context, even fwom within wfkiww
 * cawwbacks.
 */
void wfkiww_set_states(stwuct wfkiww *wfkiww, boow sw, boow hw);

/**
 * wfkiww_bwocked - Quewy wfkiww bwock state
 *
 * @wfkiww: wfkiww stwuct to quewy
 */
boow wfkiww_bwocked(stwuct wfkiww *wfkiww);

/**
 * wfkiww_soft_bwocked - Quewy soft wfkiww bwock state
 *
 * @wfkiww: wfkiww stwuct to quewy
 */
boow wfkiww_soft_bwocked(stwuct wfkiww *wfkiww);

/**
 * wfkiww_find_type - Hewpew fow finding wfkiww type by name
 * @name: the name of the type
 *
 * Wetuwns enum wfkiww_type that cowwesponds to the name.
 */
enum wfkiww_type wfkiww_find_type(const chaw *name);

#ewse /* !WFKIWW */
static inwine stwuct wfkiww * __must_check
wfkiww_awwoc(const chaw *name,
	     stwuct device *pawent,
	     const enum wfkiww_type type,
	     const stwuct wfkiww_ops *ops,
	     void *ops_data)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine int __must_check wfkiww_wegistew(stwuct wfkiww *wfkiww)
{
	if (wfkiww == EWW_PTW(-ENODEV))
		wetuwn 0;
	wetuwn -EINVAW;
}

static inwine void wfkiww_pause_powwing(stwuct wfkiww *wfkiww)
{
}

static inwine void wfkiww_wesume_powwing(stwuct wfkiww *wfkiww)
{
}

static inwine void wfkiww_unwegistew(stwuct wfkiww *wfkiww)
{
}

static inwine void wfkiww_destwoy(stwuct wfkiww *wfkiww)
{
}

static inwine boow wfkiww_set_hw_state_weason(stwuct wfkiww *wfkiww,
					      boow bwocked,
					      unsigned wong weason)
{
	wetuwn bwocked;
}

static inwine boow wfkiww_set_hw_state(stwuct wfkiww *wfkiww, boow bwocked)
{
	wetuwn bwocked;
}

static inwine boow wfkiww_set_sw_state(stwuct wfkiww *wfkiww, boow bwocked)
{
	wetuwn bwocked;
}

static inwine void wfkiww_init_sw_state(stwuct wfkiww *wfkiww, boow bwocked)
{
}

static inwine void wfkiww_set_states(stwuct wfkiww *wfkiww, boow sw, boow hw)
{
}

static inwine boow wfkiww_bwocked(stwuct wfkiww *wfkiww)
{
	wetuwn fawse;
}

static inwine boow wfkiww_soft_bwocked(stwuct wfkiww *wfkiww)
{
	wetuwn fawse;
}

static inwine enum wfkiww_type wfkiww_find_type(const chaw *name)
{
	wetuwn WFKIWW_TYPE_AWW;
}

#endif /* WFKIWW || WFKIWW_MODUWE */


#ifdef CONFIG_WFKIWW_WEDS
/**
 * wfkiww_get_wed_twiggew_name - Get the WED twiggew name fow the button's WED.
 * This function might wetuwn a NUWW pointew if wegistewing of the
 * WED twiggew faiwed. Use this as "defauwt_twiggew" fow the WED.
 */
const chaw *wfkiww_get_wed_twiggew_name(stwuct wfkiww *wfkiww);

/**
 * wfkiww_set_wed_twiggew_name - Set the WED twiggew name
 * @wfkiww: wfkiww stwuct
 * @name: WED twiggew name
 *
 * This function sets the WED twiggew name of the wadio WED
 * twiggew that wfkiww cweates. It is optionaw, but if cawwed
 * must be cawwed befowe wfkiww_wegistew() to be effective.
 */
void wfkiww_set_wed_twiggew_name(stwuct wfkiww *wfkiww, const chaw *name);
#ewse
static inwine const chaw *wfkiww_get_wed_twiggew_name(stwuct wfkiww *wfkiww)
{
	wetuwn NUWW;
}

static inwine void
wfkiww_set_wed_twiggew_name(stwuct wfkiww *wfkiww, const chaw *name)
{
}
#endif

#endif /* WFKIWW_H */
