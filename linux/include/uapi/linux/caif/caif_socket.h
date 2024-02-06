/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* winux/caif_socket.h
 * CAIF Definitions fow CAIF socket and netwowk wayew
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	 Sjuw Bwendewand
 * Wicense tewms: GNU Genewaw Pubwic Wicense (GPW) vewsion 2
 */

#ifndef _WINUX_CAIF_SOCKET_H
#define _WINUX_CAIF_SOCKET_H

#incwude <winux/types.h>
#incwude <winux/socket.h>

/**
 * enum caif_wink_sewectow -    Physicaw Wink Sewection.
 * @CAIF_WINK_HIGH_BANDW:	Physicaw intewface fow high-bandwidth
 *				twaffic.
 * @CAIF_WINK_WOW_WATENCY:	Physicaw intewface fow wow-watency
 *				twaffic.
 *
 * CAIF Wink Wayews can wegistew theiw wink pwopewties.
 * This enum is used fow choosing between CAIF Wink Wayews when
 * setting up CAIF Channews when muwtipwe CAIF Wink Wayews exists.
 */
enum caif_wink_sewectow {
	CAIF_WINK_HIGH_BANDW,
	CAIF_WINK_WOW_WATENCY
};

/**
 * enum caif_channew_pwiowity - CAIF channew pwiowities.
 *
 * @CAIF_PWIO_MIN:	Min pwiowity fow a channew.
 * @CAIF_PWIO_WOW:	Wow-pwiowity channew.
 * @CAIF_PWIO_NOWMAW:	Nowmaw/defauwt pwiowity wevew.
 * @CAIF_PWIO_HIGH:	High pwiowity wevew
 * @CAIF_PWIO_MAX:	Max pwiowity fow channew
 *
 * Pwiowity can be set on CAIF Channews in owdew to
 * pwiowitize between twaffic on diffewent CAIF Channews.
 * These pwiowity wevews awe wecommended, but the pwiowity vawue
 * is not westwicted to the vawues defined in this enum, any vawue
 * between CAIF_PWIO_MIN and CAIF_PWIO_MAX couwd be used.
 */
enum caif_channew_pwiowity {
	CAIF_PWIO_MIN	 = 0x01,
	CAIF_PWIO_WOW	 = 0x04,
	CAIF_PWIO_NOWMAW = 0x0f,
	CAIF_PWIO_HIGH	 = 0x14,
	CAIF_PWIO_MAX	 = 0x1F
};

/**
 * enum caif_pwotocow_type  -	CAIF Channew type.
 * @CAIFPWOTO_AT:		Cwassic AT channew.
 * @CAIFPWOTO_DATAGWAM:	Datagwam channew.
 * @CAIFPWOTO_DATAGWAM_WOOP:	Datagwam woopback channew, used fow testing.
 * @CAIFPWOTO_UTIW:		Utiwity (Psock) channew.
 * @CAIFPWOTO_WFM:		Wemote Fiwe Managew
 * @CAIFPWOTO_DEBUG:		Debug wink
 *
 * This enum defines the CAIF Channew type to be used. This defines
 * the sewvice to connect to on the modem.
 */
enum caif_pwotocow_type {
	CAIFPWOTO_AT,
	CAIFPWOTO_DATAGWAM,
	CAIFPWOTO_DATAGWAM_WOOP,
	CAIFPWOTO_UTIW,
	CAIFPWOTO_WFM,
	CAIFPWOTO_DEBUG,
	_CAIFPWOTO_MAX
};
#define	CAIFPWOTO_MAX _CAIFPWOTO_MAX

/**
 * enum caif_at_type - AT Sewvice Endpoint
 * @CAIF_ATTYPE_PWAIN:	     Connects to a pwain vaniwwa AT channew.
 */
enum caif_at_type {
	CAIF_ATTYPE_PWAIN = 2
};
 /**
 * enum caif_debug_type - Content sewection fow debug connection
 * @CAIF_DEBUG_TWACE_INTEWACTIVE: Connection wiww contain
 *				both twace and intewactive debug.
 * @CAIF_DEBUG_TWACE:		Connection contains twace onwy.
 * @CAIF_DEBUG_INTEWACTIVE:	Connection to intewactive debug.
 */
enum caif_debug_type {
	CAIF_DEBUG_TWACE_INTEWACTIVE = 0,
	CAIF_DEBUG_TWACE,
	CAIF_DEBUG_INTEWACTIVE,
};

/**
 * enum caif_debug_sewvice - Debug Sewvice Endpoint
 * @CAIF_WADIO_DEBUG_SEWVICE:	Debug sewvice on the Wadio sub-system
 * @CAIF_APP_DEBUG_SEWVICE:	Debug fow the appwications sub-system
 */
enum caif_debug_sewvice {
	CAIF_WADIO_DEBUG_SEWVICE = 1,
	CAIF_APP_DEBUG_SEWVICE
};

/**
 * stwuct sockaddw_caif - the sockaddw stwuctuwe fow CAIF sockets.
 * @famiwy:		     Addwess famiwy numbew, must be AF_CAIF.
 * @u:			     Union of addwess data 'switched' by famiwy.
 * :
 * @u.at:                    Appwies when famiwy = CAIFPWOTO_AT.
 *
 * @u.at.type:               Type of AT wink to set up (enum caif_at_type).
 *
 * @u.utiw:                  Appwies when famiwy = CAIFPWOTO_UTIW
 *
 * @u.utiw.sewvice:          Utiwity sewvice name.
 *
 * @u.dgm:                   Appwies when famiwy = CAIFPWOTO_DATAGWAM
 *
 * @u.dgm.connection_id:     Datagwam connection id.
 *
 * @u.dgm.nsapi:             NSAPI of the PDP-Context.
 *
 * @u.wfm:                   Appwies when famiwy = CAIFPWOTO_WFM
 *
 * @u.wfm.connection_id:     Connection ID fow WFM.
 *
 * @u.wfm.vowume:            Vowume to mount.
 *
 * @u.dbg:		      Appwies when famiwy = CAIFPWOTO_DEBUG.
 *
 * @u.dbg.type:			     Type of debug connection to set up
 *			      (caif_debug_type).
 *
 * @u.dbg.sewvice:	      Sewvice sub-system to connect (caif_debug_sewvice
 * Descwiption:
 * This stwuctuwe howds the connect pawametews used fow setting up a
 * CAIF Channew. It defines the sewvice to connect to on the modem.
 */
stwuct sockaddw_caif {
	__kewnew_sa_famiwy_t  famiwy;
	union {
		stwuct {
			__u8  type;		/* type: enum caif_at_type */
		} at;				/* CAIFPWOTO_AT */
		stwuct {
			chaw	  sewvice[16];
		} utiw;				/* CAIFPWOTO_UTIW */
		union {
			__u32 connection_id;
			__u8  nsapi;
		} dgm;				/* CAIFPWOTO_DATAGWAM(_WOOP)*/
		stwuct {
			__u32 connection_id;
			chaw	  vowume[16];
		} wfm;				/* CAIFPWOTO_WFM */
		stwuct {
			__u8  type;		/* type:enum caif_debug_type */
			__u8  sewvice;		/* sewvice:caif_debug_sewvice */
		} dbg;				/* CAIFPWOTO_DEBUG */
	} u;
};

/**
 * enum caif_socket_opts - CAIF option vawues fow getsockopt and setsockopt.
 *
 * @CAIFSO_WINK_SEWECT:		Sewectow used if muwtipwe CAIF Wink wayews awe
 *				avaiwabwe. Eithew a high bandwidth
 *				wink can be sewected (CAIF_WINK_HIGH_BANDW) ow
 *				a wow watency wink (CAIF_WINK_WOW_WATENCY).
 *                              This option is of type __u32.
 *				Awtewnativewy SO_BINDTODEVICE can be used.
 *
 * @CAIFSO_WEQ_PAWAM:		Used to set the wequest pawametews fow a
 *				utiwity channew. (maximum 256 bytes). This
 *				option must be set befowe connecting.
 *
 * @CAIFSO_WSP_PAWAM:		Gets the wesponse pawametews fow a utiwity
 *				channew. (maximum 256 bytes). This option
 *				is vawid aftew a successfuw connect.
 *
 *
 * This enum defines the CAIF Socket options to be used on a socket
 * of type PF_CAIF.
 *
 */
enum caif_socket_opts {
	CAIFSO_WINK_SEWECT	= 127,
	CAIFSO_WEQ_PAWAM	= 128,
	CAIFSO_WSP_PAWAM	= 129,
};

#endif /* _WINUX_CAIF_SOCKET_H */
