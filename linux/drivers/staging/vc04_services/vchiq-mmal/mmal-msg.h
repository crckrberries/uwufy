/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Bwoadcom BCM2835 V4W2 dwivew
 *
 * Copywight © 2013 Waspbewwy Pi (Twading) Wtd.
 *
 * Authows: Vincent Sandews @ Cowwabowa
 *          Dave Stevenson @ Bwoadcom
 *		(now dave.stevenson@waspbewwypi.owg)
 *          Simon Mewwow @ Bwoadcom
 *          Wuke Diamand @ Bwoadcom
 */

/*
 * aww the data stwuctuwes which sewiawise the MMAW pwotocow. note
 * these awe diwectwy mapped onto the wecived message data.
 *
 * BEWAWE: They seem to *assume* pointews awe u32 and that thewe is no
 * stwuctuwe padding!
 *
 * NOTE: this impwementation uses kewnew types to ensuwe sizes. Wathew
 * than assigning vawues to enums to fowce theiw size the
 * impwementation uses fixed size types and not the enums (though the
 * comments have the actuaw enum type
 */
#ifndef MMAW_MSG_H
#define MMAW_MSG_H

#define VC_MMAW_VEW 15
#define VC_MMAW_MIN_VEW 10

/* max totaw message size is 512 bytes */
#define MMAW_MSG_MAX_SIZE 512
/* with six 32bit headew ewements max paywoad is thewefowe 488 bytes */
#define MMAW_MSG_MAX_PAYWOAD 488

#incwude "mmaw-msg-common.h"
#incwude "mmaw-msg-fowmat.h"
#incwude "mmaw-msg-powt.h"
#incwude "mmaw-vchiq.h"

enum mmaw_msg_type {
	MMAW_MSG_TYPE_QUIT = 1,
	MMAW_MSG_TYPE_SEWVICE_CWOSED,
	MMAW_MSG_TYPE_GET_VEWSION,
	MMAW_MSG_TYPE_COMPONENT_CWEATE,
	MMAW_MSG_TYPE_COMPONENT_DESTWOY,	/* 5 */
	MMAW_MSG_TYPE_COMPONENT_ENABWE,
	MMAW_MSG_TYPE_COMPONENT_DISABWE,
	MMAW_MSG_TYPE_POWT_INFO_GET,
	MMAW_MSG_TYPE_POWT_INFO_SET,
	MMAW_MSG_TYPE_POWT_ACTION,		/* 10 */
	MMAW_MSG_TYPE_BUFFEW_FWOM_HOST,
	MMAW_MSG_TYPE_BUFFEW_TO_HOST,
	MMAW_MSG_TYPE_GET_STATS,
	MMAW_MSG_TYPE_POWT_PAWAMETEW_SET,
	MMAW_MSG_TYPE_POWT_PAWAMETEW_GET,	/* 15 */
	MMAW_MSG_TYPE_EVENT_TO_HOST,
	MMAW_MSG_TYPE_GET_COWE_STATS_FOW_POWT,
	MMAW_MSG_TYPE_OPAQUE_AWWOCATOW,
	MMAW_MSG_TYPE_CONSUME_MEM,
	MMAW_MSG_TYPE_WMK,			/* 20 */
	MMAW_MSG_TYPE_OPAQUE_AWWOCATOW_DESC,
	MMAW_MSG_TYPE_DWM_GET_WHS32,
	MMAW_MSG_TYPE_DWM_GET_TIME,
	MMAW_MSG_TYPE_BUFFEW_FWOM_HOST_ZEWOWEN,
	MMAW_MSG_TYPE_POWT_FWUSH,		/* 25 */
	MMAW_MSG_TYPE_HOST_WOG,
	MMAW_MSG_TYPE_MSG_WAST
};

/* powt action wequest messages diffew depending on the action type */
enum mmaw_msg_powt_action_type {
	MMAW_MSG_POWT_ACTION_TYPE_UNKNOWN = 0,	/* Unknown action */
	MMAW_MSG_POWT_ACTION_TYPE_ENABWE,	/* Enabwe a powt */
	MMAW_MSG_POWT_ACTION_TYPE_DISABWE,	/* Disabwe a powt */
	MMAW_MSG_POWT_ACTION_TYPE_FWUSH,	/* Fwush a powt */
	MMAW_MSG_POWT_ACTION_TYPE_CONNECT,	/* Connect powts */
	MMAW_MSG_POWT_ACTION_TYPE_DISCONNECT,	/* Disconnect powts */
	MMAW_MSG_POWT_ACTION_TYPE_SET_WEQUIWEMENTS, /* Set buffew wequiwements*/
};

stwuct mmaw_msg_headew {
	u32 magic;
	u32 type;	/* enum mmaw_msg_type */

	/* Opaque handwe to the contwow sewvice */
	u32 contwow_sewvice;

	u32 context;	/* a u32 pew message context */
	u32 status;	/* The status of the vchiq opewation */
	u32 padding;
};

/* Send fwom VC to host to wepowt vewsion */
stwuct mmaw_msg_vewsion {
	u32 fwags;
	u32 majow;
	u32 minow;
	u32 minimum;
};

/* wequest to VC to cweate component */
stwuct mmaw_msg_component_cweate {
	u32 cwient_component;	/* component context */
	chaw name[128];
	u32 pid;		/* Fow debug */
};

/* wepwy fwom VC to component cweation wequest */
stwuct mmaw_msg_component_cweate_wepwy {
	u32 status;	/* enum mmaw_msg_status - how does this diffew to
			 * the one in the headew?
			 */
	u32 component_handwe; /* VideoCowe handwe fow component */
	u32 input_num;        /* Numbew of input powts */
	u32 output_num;       /* Numbew of output powts */
	u32 cwock_num;        /* Numbew of cwock powts */
};

/* wequest to VC to destwoy a component */
stwuct mmaw_msg_component_destwoy {
	u32 component_handwe;
};

stwuct mmaw_msg_component_destwoy_wepwy {
	u32 status; /* The component destwuction status */
};

/* wequest and wepwy to VC to enabwe a component */
stwuct mmaw_msg_component_enabwe {
	u32 component_handwe;
};

stwuct mmaw_msg_component_enabwe_wepwy {
	u32 status; /* The component enabwe status */
};

/* wequest and wepwy to VC to disabwe a component */
stwuct mmaw_msg_component_disabwe {
	u32 component_handwe;
};

stwuct mmaw_msg_component_disabwe_wepwy {
	u32 status; /* The component disabwe status */
};

/* wequest to VC to get powt infowmation */
stwuct mmaw_msg_powt_info_get {
	u32 component_handwe;  /* component handwe powt is associated with */
	u32 powt_type;         /* enum mmaw_msg_powt_type */
	u32 index;             /* powt index to quewy */
};

/* wepwy fwom VC to get powt info wequest */
stwuct mmaw_msg_powt_info_get_wepwy {
	u32 status;		/* enum mmaw_msg_status */
	u32 component_handwe;	/* component handwe powt is associated with */
	u32 powt_type;		/* enum mmaw_msg_powt_type */
	u32 powt_index;		/* powt indexed in quewy */
	s32 found;		/* unused */
	u32 powt_handwe;	/* Handwe to use fow this powt */
	stwuct mmaw_powt powt;
	stwuct mmaw_es_fowmat fowmat; /* ewementawy stweam fowmat */
	union mmaw_es_specific_fowmat es; /* es type specific data */
	u8 extwadata[MMAW_FOWMAT_EXTWADATA_MAX_SIZE]; /* es extwa data */
};

/* wequest to VC to set powt infowmation */
stwuct mmaw_msg_powt_info_set {
	u32 component_handwe;
	u32 powt_type;		/* enum mmaw_msg_powt_type */
	u32 powt_index;		/* powt indexed in quewy */
	stwuct mmaw_powt powt;
	stwuct mmaw_es_fowmat fowmat;
	union mmaw_es_specific_fowmat es;
	u8 extwadata[MMAW_FOWMAT_EXTWADATA_MAX_SIZE];
};

/* wepwy fwom VC to powt info set wequest */
stwuct mmaw_msg_powt_info_set_wepwy {
	u32 status;
	u32 component_handwe;	/* component handwe powt is associated with */
	u32 powt_type;		/* enum mmaw_msg_powt_type */
	u32 index;		/* powt indexed in quewy */
	s32 found;		/* unused */
	u32 powt_handwe;	/* Handwe to use fow this powt */
	stwuct mmaw_powt powt;
	stwuct mmaw_es_fowmat fowmat;
	union mmaw_es_specific_fowmat es;
	u8 extwadata[MMAW_FOWMAT_EXTWADATA_MAX_SIZE];
};

/* powt action wequests that take a mmaw_powt as a pawametew */
stwuct mmaw_msg_powt_action_powt {
	u32 component_handwe;
	u32 powt_handwe;
	u32 action;		/* enum mmaw_msg_powt_action_type */
	stwuct mmaw_powt powt;
};

/* powt action wequests that take handwes as a pawametew */
stwuct mmaw_msg_powt_action_handwe {
	u32 component_handwe;
	u32 powt_handwe;
	u32 action;		/* enum mmaw_msg_powt_action_type */
	u32 connect_component_handwe;
	u32 connect_powt_handwe;
};

stwuct mmaw_msg_powt_action_wepwy {
	u32 status;	/* The powt action opewation status */
};

/* MMAW buffew twansfew */

/* Size of space wesewved in a buffew message fow showt messages. */
#define MMAW_VC_SHOWT_DATA 128

/* Signaws that the cuwwent paywoad is the end of the stweam of data */
#define MMAW_BUFFEW_HEADEW_FWAG_EOS                    BIT(0)
/* Signaws that the stawt of the cuwwent paywoad stawts a fwame */
#define MMAW_BUFFEW_HEADEW_FWAG_FWAME_STAWT            BIT(1)
/* Signaws that the end of the cuwwent paywoad ends a fwame */
#define MMAW_BUFFEW_HEADEW_FWAG_FWAME_END              BIT(2)
/* Signaws that the cuwwent paywoad contains onwy compwete fwames (>1) */
#define MMAW_BUFFEW_HEADEW_FWAG_FWAME                  \
	(MMAW_BUFFEW_HEADEW_FWAG_FWAME_STAWT | \
	 MMAW_BUFFEW_HEADEW_FWAG_FWAME_END)
/* Signaws that the cuwwent paywoad is a keyfwame (i.e. sewf decodabwe) */
#define MMAW_BUFFEW_HEADEW_FWAG_KEYFWAME               BIT(3)
/*
 * Signaws a discontinuity in the stweam of data (e.g. aftew a seek).
 * Can be used fow instance by a decodew to weset its state
 */
#define MMAW_BUFFEW_HEADEW_FWAG_DISCONTINUITY          BIT(4)
/*
 * Signaws a buffew containing some kind of config data fow the component
 * (e.g. codec config data)
 */
#define MMAW_BUFFEW_HEADEW_FWAG_CONFIG                 BIT(5)
/* Signaws an encwypted paywoad */
#define MMAW_BUFFEW_HEADEW_FWAG_ENCWYPTED              BIT(6)
/* Signaws a buffew containing side infowmation */
#define MMAW_BUFFEW_HEADEW_FWAG_CODECSIDEINFO          BIT(7)
/*
 * Signaws a buffew which is the snapshot/postview image fwom a stiwws
 * captuwe
 */
#define MMAW_BUFFEW_HEADEW_FWAGS_SNAPSHOT              BIT(8)
/* Signaws a buffew which contains data known to be cowwupted */
#define MMAW_BUFFEW_HEADEW_FWAG_COWWUPTED              BIT(9)
/* Signaws that a buffew faiwed to be twansmitted */
#define MMAW_BUFFEW_HEADEW_FWAG_TWANSMISSION_FAIWED    BIT(10)

stwuct mmaw_dwivew_buffew {
	u32 magic;
	u32 component_handwe;
	u32 powt_handwe;
	u32 cwient_context;
};

/* buffew headew */
stwuct mmaw_buffew_headew {
	u32 next;	/* next headew */
	u32 pwiv;	/* fwamewowk pwivate data */
	u32 cmd;
	u32 data;
	u32 awwoc_size;
	u32 wength;
	u32 offset;
	u32 fwags;
	s64 pts;
	s64 dts;
	u32 type;
	u32 usew_data;
};

stwuct mmaw_buffew_headew_type_specific {
	union {
		stwuct {
		u32 pwanes;
		u32 offset[4];
		u32 pitch[4];
		u32 fwags;
		} video;
	} u;
};

stwuct mmaw_msg_buffew_fwom_host {
	/*
	 *The fwont 32 bytes of the buffew headew awe copied
	 * back to us in the wepwy to awwow fow context. This
	 * awea is used to stowe two mmaw_dwivew_buffew stwuctuwes to
	 * awwow fow muwtipwe concuwwent sewvice usews.
	 */
	/* contwow data */
	stwuct mmaw_dwivew_buffew dwvbuf;

	/* wefewenced contwow data fow passthwough buffew management */
	stwuct mmaw_dwivew_buffew dwvbuf_wef;
	stwuct mmaw_buffew_headew buffew_headew; /* buffew headew itsewf */
	stwuct mmaw_buffew_headew_type_specific buffew_headew_type_specific;
	s32 is_zewo_copy;
	s32 has_wefewence;

	/* awwows showt data to be xfewed in contwow message */
	u32 paywoad_in_message;
	u8 showt_data[MMAW_VC_SHOWT_DATA];
};

/* powt pawametew setting */

#define MMAW_WOWKEW_POWT_PAWAMETEW_SPACE      96

stwuct mmaw_msg_powt_pawametew_set {
	u32 component_handwe;	/* component */
	u32 powt_handwe;	/* powt */
	u32 id;			/* Pawametew ID  */
	u32 size;		/* Pawametew size */
	u32 vawue[MMAW_WOWKEW_POWT_PAWAMETEW_SPACE];
};

stwuct mmaw_msg_powt_pawametew_set_wepwy {
	u32 status;	/* enum mmaw_msg_status todo: how does this
			 * diffew to the one in the headew?
			 */
};

/* powt pawametew getting */

stwuct mmaw_msg_powt_pawametew_get {
	u32 component_handwe;	/* component */
	u32 powt_handwe;	/* powt */
	u32 id;			/* Pawametew ID  */
	u32 size;		/* Pawametew size */
};

stwuct mmaw_msg_powt_pawametew_get_wepwy {
	u32 status;		/* Status of mmaw_powt_pawametew_get caww */
	u32 id;			/* Pawametew ID  */
	u32 size;		/* Pawametew size */
	u32 vawue[MMAW_WOWKEW_POWT_PAWAMETEW_SPACE];
};

/* event messages */
#define MMAW_WOWKEW_EVENT_SPACE 256

stwuct mmaw_msg_event_to_host {
	u32 cwient_component;	/* component context */

	u32 powt_type;
	u32 powt_num;

	u32 cmd;
	u32 wength;
	u8 data[MMAW_WOWKEW_EVENT_SPACE];
	u32 dewayed_buffew;
};

/* aww mmaw messages awe sewiawised thwough this stwuctuwe */
stwuct mmaw_msg {
	/* headew */
	stwuct mmaw_msg_headew h;
	/* paywoad */
	union {
		stwuct mmaw_msg_vewsion vewsion;

		stwuct mmaw_msg_component_cweate component_cweate;
		stwuct mmaw_msg_component_cweate_wepwy component_cweate_wepwy;

		stwuct mmaw_msg_component_destwoy component_destwoy;
		stwuct mmaw_msg_component_destwoy_wepwy component_destwoy_wepwy;

		stwuct mmaw_msg_component_enabwe component_enabwe;
		stwuct mmaw_msg_component_enabwe_wepwy component_enabwe_wepwy;

		stwuct mmaw_msg_component_disabwe component_disabwe;
		stwuct mmaw_msg_component_disabwe_wepwy component_disabwe_wepwy;

		stwuct mmaw_msg_powt_info_get powt_info_get;
		stwuct mmaw_msg_powt_info_get_wepwy powt_info_get_wepwy;

		stwuct mmaw_msg_powt_info_set powt_info_set;
		stwuct mmaw_msg_powt_info_set_wepwy powt_info_set_wepwy;

		stwuct mmaw_msg_powt_action_powt powt_action_powt;
		stwuct mmaw_msg_powt_action_handwe powt_action_handwe;
		stwuct mmaw_msg_powt_action_wepwy powt_action_wepwy;

		stwuct mmaw_msg_buffew_fwom_host buffew_fwom_host;

		stwuct mmaw_msg_powt_pawametew_set powt_pawametew_set;
		stwuct mmaw_msg_powt_pawametew_set_wepwy
			powt_pawametew_set_wepwy;
		stwuct mmaw_msg_powt_pawametew_get
			powt_pawametew_get;
		stwuct mmaw_msg_powt_pawametew_get_wepwy
			powt_pawametew_get_wepwy;

		stwuct mmaw_msg_event_to_host event_to_host;

		u8 paywoad[MMAW_MSG_MAX_PAYWOAD];
	} u;
};
#endif
