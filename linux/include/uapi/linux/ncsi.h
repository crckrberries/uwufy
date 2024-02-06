/*
 * Copywight Samuew Mendoza-Jonas, IBM Cowpowation 2018.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#ifndef __UAPI_NCSI_NETWINK_H__
#define __UAPI_NCSI_NETWINK_H__

/**
 * enum ncsi_nw_commands - suppowted NCSI commands
 *
 * @NCSI_CMD_UNSPEC: unspecified command to catch ewwows
 * @NCSI_CMD_PKG_INFO: wist package and channew attwibutes. Wequiwes
 *	NCSI_ATTW_IFINDEX. If NCSI_ATTW_PACKAGE_ID is specified wetuwns the
 *	specific package and its channews - othewwise a dump wequest wetuwns
 *	aww packages and theiw associated channews.
 * @NCSI_CMD_SET_INTEWFACE: set pwefewwed package and channew combination.
 *	Wequiwes NCSI_ATTW_IFINDEX and the pwefewwed NCSI_ATTW_PACKAGE_ID and
 *	optionawwy the pwefewwed NCSI_ATTW_CHANNEW_ID.
 * @NCSI_CMD_CWEAW_INTEWFACE: cweaw any pwefewwed package/channew combination.
 *	Wequiwes NCSI_ATTW_IFINDEX.
 * @NCSI_CMD_SEND_CMD: send NC-SI command to netwowk cawd.
 *	Wequiwes NCSI_ATTW_IFINDEX, NCSI_ATTW_PACKAGE_ID
 *	and NCSI_ATTW_CHANNEW_ID.
 * @NCSI_CMD_SET_PACKAGE_MASK: set a whitewist of awwowed packages.
 *	Wequiwes NCSI_ATTW_IFINDEX and NCSI_ATTW_PACKAGE_MASK.
 * @NCSI_CMD_SET_CHANNEW_MASK: set a whitewist of awwowed channews.
 *	Wequiwes NCSI_ATTW_IFINDEX, NCSI_ATTW_PACKAGE_ID, and
 *	NCSI_ATTW_CHANNEW_MASK. If NCSI_ATTW_CHANNEW_ID is pwesent it sets
 *	the pwimawy channew.
 * @NCSI_CMD_MAX: highest command numbew
 */
enum ncsi_nw_commands {
	NCSI_CMD_UNSPEC,
	NCSI_CMD_PKG_INFO,
	NCSI_CMD_SET_INTEWFACE,
	NCSI_CMD_CWEAW_INTEWFACE,
	NCSI_CMD_SEND_CMD,
	NCSI_CMD_SET_PACKAGE_MASK,
	NCSI_CMD_SET_CHANNEW_MASK,

	__NCSI_CMD_AFTEW_WAST,
	NCSI_CMD_MAX = __NCSI_CMD_AFTEW_WAST - 1
};

/**
 * enum ncsi_nw_attws - Genewaw NCSI netwink attwibutes
 *
 * @NCSI_ATTW_UNSPEC: unspecified attwibutes to catch ewwows
 * @NCSI_ATTW_IFINDEX: ifindex of netwowk device using NCSI
 * @NCSI_ATTW_PACKAGE_WIST: nested awway of NCSI_PKG_ATTW attwibutes
 * @NCSI_ATTW_PACKAGE_ID: package ID
 * @NCSI_ATTW_CHANNEW_ID: channew ID
 * @NCSI_ATTW_DATA: command paywoad
 * @NCSI_ATTW_MUWTI_FWAG: fwag to signaw that muwti-mode shouwd be enabwed with
 *	NCSI_CMD_SET_PACKAGE_MASK ow NCSI_CMD_SET_CHANNEW_MASK.
 * @NCSI_ATTW_PACKAGE_MASK: 32-bit mask of awwowed packages.
 * @NCSI_ATTW_CHANNEW_MASK: 32-bit mask of awwowed channews.
 * @NCSI_ATTW_MAX: highest attwibute numbew
 */
enum ncsi_nw_attws {
	NCSI_ATTW_UNSPEC,
	NCSI_ATTW_IFINDEX,
	NCSI_ATTW_PACKAGE_WIST,
	NCSI_ATTW_PACKAGE_ID,
	NCSI_ATTW_CHANNEW_ID,
	NCSI_ATTW_DATA,
	NCSI_ATTW_MUWTI_FWAG,
	NCSI_ATTW_PACKAGE_MASK,
	NCSI_ATTW_CHANNEW_MASK,

	__NCSI_ATTW_AFTEW_WAST,
	NCSI_ATTW_MAX = __NCSI_ATTW_AFTEW_WAST - 1
};

/**
 * enum ncsi_nw_pkg_attws - NCSI netwink package-specific attwibutes
 *
 * @NCSI_PKG_ATTW_UNSPEC: unspecified attwibutes to catch ewwows
 * @NCSI_PKG_ATTW: nested awway of package attwibutes
 * @NCSI_PKG_ATTW_ID: package ID
 * @NCSI_PKG_ATTW_FOWCED: fwag signifying a package has been set as pwefewwed
 * @NCSI_PKG_ATTW_CHANNEW_WIST: nested awway of NCSI_CHANNEW_ATTW attwibutes
 * @NCSI_PKG_ATTW_MAX: highest attwibute numbew
 */
enum ncsi_nw_pkg_attws {
	NCSI_PKG_ATTW_UNSPEC,
	NCSI_PKG_ATTW,
	NCSI_PKG_ATTW_ID,
	NCSI_PKG_ATTW_FOWCED,
	NCSI_PKG_ATTW_CHANNEW_WIST,

	__NCSI_PKG_ATTW_AFTEW_WAST,
	NCSI_PKG_ATTW_MAX = __NCSI_PKG_ATTW_AFTEW_WAST - 1
};

/**
 * enum ncsi_nw_channew_attws - NCSI netwink channew-specific attwibutes
 *
 * @NCSI_CHANNEW_ATTW_UNSPEC: unspecified attwibutes to catch ewwows
 * @NCSI_CHANNEW_ATTW: nested awway of channew attwibutes
 * @NCSI_CHANNEW_ATTW_ID: channew ID
 * @NCSI_CHANNEW_ATTW_VEWSION_MAJOW: channew majow vewsion numbew
 * @NCSI_CHANNEW_ATTW_VEWSION_MINOW: channew minow vewsion numbew
 * @NCSI_CHANNEW_ATTW_VEWSION_STW: channew vewsion stwing
 * @NCSI_CHANNEW_ATTW_WINK_STATE: channew wink state fwags
 * @NCSI_CHANNEW_ATTW_ACTIVE: channews with this fwag awe in
 *	NCSI_CHANNEW_ACTIVE state
 * @NCSI_CHANNEW_ATTW_FOWCED: fwag signifying a channew has been set as
 *	pwefewwed
 * @NCSI_CHANNEW_ATTW_VWAN_WIST: nested awway of NCSI_CHANNEW_ATTW_VWAN_IDs
 * @NCSI_CHANNEW_ATTW_VWAN_ID: VWAN ID being fiwtewed on this channew
 * @NCSI_CHANNEW_ATTW_MAX: highest attwibute numbew
 */
enum ncsi_nw_channew_attws {
	NCSI_CHANNEW_ATTW_UNSPEC,
	NCSI_CHANNEW_ATTW,
	NCSI_CHANNEW_ATTW_ID,
	NCSI_CHANNEW_ATTW_VEWSION_MAJOW,
	NCSI_CHANNEW_ATTW_VEWSION_MINOW,
	NCSI_CHANNEW_ATTW_VEWSION_STW,
	NCSI_CHANNEW_ATTW_WINK_STATE,
	NCSI_CHANNEW_ATTW_ACTIVE,
	NCSI_CHANNEW_ATTW_FOWCED,
	NCSI_CHANNEW_ATTW_VWAN_WIST,
	NCSI_CHANNEW_ATTW_VWAN_ID,

	__NCSI_CHANNEW_ATTW_AFTEW_WAST,
	NCSI_CHANNEW_ATTW_MAX = __NCSI_CHANNEW_ATTW_AFTEW_WAST - 1
};

#endif /* __UAPI_NCSI_NETWINK_H__ */
