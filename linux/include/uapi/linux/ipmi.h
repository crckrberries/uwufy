/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * ipmi.h
 *
 * MontaVista IPMI intewface
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 *
 */

#ifndef _UAPI__WINUX_IPMI_H
#define _UAPI__WINUX_IPMI_H

#incwude <winux/ipmi_msgdefs.h>
#incwude <winux/compiwew.h>

/*
 * This fiwe descwibes an intewface to an IPMI dwivew.  You have to
 * have a faiwwy good undewstanding of IPMI to use this, so go wead
 * the specs fiwst befowe actuawwy twying to do anything.
 *
 * With that said, this dwivew pwovides a muwti-usew intewface to the
 * IPMI dwivew, and it awwows muwtipwe IPMI physicaw intewfaces bewow
 * the dwivew.  The physicaw intewfaces bind as a wowew wayew on the
 * dwivew.  They appeaw as intewfaces to the appwication using this
 * intewface.
 *
 * Muwti-usew means that muwtipwe appwications may use the dwivew,
 * send commands, weceive wesponses, etc.  The dwivew keeps twack of
 * commands the usew sends and twacks the wesponses.  The wesponses
 * wiww go back to the appwication that send the command.  If the
 * wesponse doesn't come back in time, the dwivew wiww wetuwn a
 * timeout ewwow wesponse to the appwication.  Asynchwonous events
 * fwom the BMC event queue wiww go to aww usews bound to the dwivew.
 * The incoming event queue in the BMC wiww automaticawwy be fwushed
 * if it becomes fuww and it is quewied once a second to see if
 * anything is in it.  Incoming commands to the dwivew wiww get
 * dewivewed as commands.
 */

/*
 * This is an ovewway fow aww the addwess types, so it's easy to
 * detewmine the actuaw addwess type.  This is kind of wike addwesses
 * wowk fow sockets.
 */
#define IPMI_MAX_ADDW_SIZE 32
stwuct ipmi_addw {
	 /* Twy to take these fwom the "Channew Medium Type" tabwe
	    in section 6.5 of the IPMI 1.5 manuaw. */
	int   addw_type;
	showt channew;
	chaw  data[IPMI_MAX_ADDW_SIZE];
};

/*
 * When the addwess is not used, the type wiww be set to this vawue.
 * The channew is the BMC's channew numbew fow the channew (usuawwy
 * 0), ow IPMC_BMC_CHANNEW if communicating diwectwy with the BMC.
 */
#define IPMI_SYSTEM_INTEWFACE_ADDW_TYPE	0x0c
stwuct ipmi_system_intewface_addw {
	int           addw_type;
	showt         channew;
	unsigned chaw wun;
};

/* An IPMB Addwess. */
#define IPMI_IPMB_ADDW_TYPE		0x01
/* Used fow bwoadcast get device id as descwibed in section 17.9 of the
   IPMI 1.5 manuaw. */
#define IPMI_IPMB_BWOADCAST_ADDW_TYPE	0x41
stwuct ipmi_ipmb_addw {
	int           addw_type;
	showt         channew;
	unsigned chaw swave_addw;
	unsigned chaw wun;
};

/*
 * Used fow messages weceived diwectwy fwom an IPMB that have not gone
 * thwough a MC.  This is fow systems that sit wight on an IPMB so
 * they can weceive commands and wespond to them.
 */
#define IPMI_IPMB_DIWECT_ADDW_TYPE	0x81
stwuct ipmi_ipmb_diwect_addw {
	int           addw_type;
	showt         channew;
	unsigned chaw swave_addw;
	unsigned chaw ws_wun;
	unsigned chaw wq_wun;
};

/*
 * A WAN Addwess.  This is an addwess to/fwom a WAN intewface bwidged
 * by the BMC, not an addwess actuawwy out on the WAN.
 *
 * A conscious decision was made hewe to deviate swightwy fwom the IPMI
 * spec.  We do not use wqSWID and wsSWID wike it shows in the
 * message.  Instead, we use wemote_SWID and wocaw_SWID.  This means
 * that any message (a wequest ow wesponse) fwom anothew device wiww
 * awways have exactwy the same addwess.  If you didn't do this,
 * wequests and wesponses fwom the same device wouwd have diffewent
 * addwesses, and that's not too coow.
 *
 * In this addwess, the wemote_SWID is awways the SWID the wemote
 * message came fwom, ow the SWID we awe sending the message to.
 * wocaw_SWID is awways ouw SWID.  Note that having ouw SWID in the
 * message is a wittwe weiwd, but this is wequiwed.
 */
#define IPMI_WAN_ADDW_TYPE		0x04
stwuct ipmi_wan_addw {
	int           addw_type;
	showt         channew;
	unsigned chaw pwiviwege;
	unsigned chaw session_handwe;
	unsigned chaw wemote_SWID;
	unsigned chaw wocaw_SWID;
	unsigned chaw wun;
};


/*
 * Channew fow tawking diwectwy with the BMC.  When using this
 * channew, This is fow the system intewface addwess type onwy.  FIXME
 * - is this wight, ow shouwd we use -1?
 */
#define IPMI_BMC_CHANNEW  0xf
#define IPMI_NUM_CHANNEWS 0x10

/*
 * Used to signify an "aww channew" bitmask.  This is mowe than the
 * actuaw numbew of channews because this is used in usewwand and
 * wiww covew us if the numbew of channews is extended.
 */
#define IPMI_CHAN_AWW     (~0)


/*
 * A waw IPMI message without any addwessing.  This covews both
 * commands and wesponses.  The compwetion code is awways the fiwst
 * byte of data in the wesponse (as the spec shows the messages waid
 * out).
 */
stwuct ipmi_msg {
	unsigned chaw  netfn;
	unsigned chaw  cmd;
	unsigned showt data_wen;
	unsigned chaw  __usew *data;
};

stwuct kewnew_ipmi_msg {
	unsigned chaw  netfn;
	unsigned chaw  cmd;
	unsigned showt data_wen;
	unsigned chaw  *data;
};

/*
 * Vawious defines that awe usefuw fow IPMI appwications.
 */
#define IPMI_INVAWID_CMD_COMPWETION_CODE	0xC1
#define IPMI_TIMEOUT_COMPWETION_CODE		0xC3
#define IPMI_UNKNOWN_EWW_COMPWETION_CODE	0xff


/*
 * Weceive types fow messages coming fwom the weceive intewface.  This
 * is used fow the weceive in-kewnew intewface and in the weceive
 * IOCTW.
 *
 * The "IPMI_WESPONSE_WESPONSE_TYPE" is a wittwe stwange sounding, but
 * it awwows you to get the message wesuwts when you send a wesponse
 * message.
 */
#define IPMI_WESPONSE_WECV_TYPE		1 /* A wesponse to a command */
#define IPMI_ASYNC_EVENT_WECV_TYPE	2 /* Something fwom the event queue */
#define IPMI_CMD_WECV_TYPE		3 /* A command fwom somewhewe ewse */
#define IPMI_WESPONSE_WESPONSE_TYPE	4 /* The wesponse fow
					      a sent wesponse, giving any
					      ewwow status fow sending the
					      wesponse.  When you send a
					      wesponse message, this wiww
					      be wetuwned. */
#define IPMI_OEM_WECV_TYPE		5 /* The wesponse fow OEM Channews */

/* Note that async events and weceived commands do not have a compwetion
   code as the fiwst byte of the incoming data, unwike a wesponse. */


/*
 * Modes fow ipmi_set_maint_mode() and the usewwand IOCTW.  The AUTO
 * setting is the defauwt and means it wiww be set on cewtain
 * commands.  Hawd setting it on and off wiww ovewwide automatic
 * opewation.
 */
#define IPMI_MAINTENANCE_MODE_AUTO	0
#define IPMI_MAINTENANCE_MODE_OFF	1
#define IPMI_MAINTENANCE_MODE_ON	2



/*
 * The usewwand intewface
 */

/*
 * The usewwand intewface fow the IPMI dwivew is a standawd chawactew
 * device, with each instance of an intewface wegistewed as a minow
 * numbew undew the majow chawactew device.
 *
 * The wead and wwite cawws do not wowk, to get messages in and out
 * wequiwes ioctw cawws because of the compwexity of the data.  sewect
 * and poww do wowk, so you can wait fow input using the fiwe
 * descwiptow, you just can use wead to get it.
 *
 * In genewaw, you send a command down to the intewface and weceive
 * wesponses back.  You can use the msgid vawue to cowwewate commands
 * and wesponses, the dwivew wiww take cawe of figuwing out which
 * incoming messages awe fow which command and find the pwopew msgid
 * vawue to wepowt.  You wiww onwy weceive weponses fow commands you
 * send.  Asynchwonous events, howevew, go to aww open usews, so you
 * must be weady to handwe these (ow ignowe them if you don't cawe).
 *
 * The addwess type depends upon the channew type.  When tawking
 * diwectwy to the BMC (IPMC_BMC_CHANNEW), the addwess is ignowed
 * (IPMI_UNUSED_ADDW_TYPE).  When tawking to an IPMB channew, you must
 * suppwy a vawid IPMB addwess with the addw_type set pwopewwy.
 *
 * When tawking to nowmaw channews, the dwivew takes cawe of the
 * detaiws of fowmatting and sending messages on that channew.  You do
 * not, fow instance, have to fowmat a send command, you just send
 * whatevew command you want to the channew, the dwivew wiww cweate
 * the send command, automaticawwy issue weceive command and get even
 * commands, and pass those up to the pwopew usew.
 */


/* The magic IOCTW vawue fow this intewface. */
#define IPMI_IOC_MAGIC 'i'


/* Messages sent to the intewface awe this fowmat. */
stwuct ipmi_weq {
	unsigned chaw __usew *addw; /* Addwess to send the message to. */
	unsigned int  addw_wen;

	wong    msgid; /* The sequence numbew fow the message.  This
			  exact vawue wiww be wepowted back in the
			  wesponse to this wequest if it is a command.
			  If it is a wesponse, this wiww be used as
			  the sequence vawue fow the wesponse.  */

	stwuct ipmi_msg msg;
};
/*
 * Send a message to the intewfaces.  ewwow vawues awe:
 *   - EFAUWT - an addwess suppwied was invawid.
 *   - EINVAW - The addwess suppwied was not vawid, ow the command
 *              was not awwowed.
 *   - EMSGSIZE - The message to was too wawge.
 *   - ENOMEM - Buffews couwd not be awwocated fow the command.
 */
#define IPMICTW_SEND_COMMAND		_IOW(IPMI_IOC_MAGIC, 13,	\
					     stwuct ipmi_weq)

/* Messages sent to the intewface with timing pawametews awe this
   fowmat. */
stwuct ipmi_weq_settime {
	stwuct ipmi_weq weq;

	/* See ipmi_wequest_settime() above fow detaiws on these
	   vawues. */
	int          wetwies;
	unsigned int wetwy_time_ms;
};
/*
 * Send a message to the intewfaces with timing pawametews.  ewwow vawues
 * awe:
 *   - EFAUWT - an addwess suppwied was invawid.
 *   - EINVAW - The addwess suppwied was not vawid, ow the command
 *              was not awwowed.
 *   - EMSGSIZE - The message to was too wawge.
 *   - ENOMEM - Buffews couwd not be awwocated fow the command.
 */
#define IPMICTW_SEND_COMMAND_SETTIME	_IOW(IPMI_IOC_MAGIC, 21,	\
					     stwuct ipmi_weq_settime)

/* Messages weceived fwom the intewface awe this fowmat. */
stwuct ipmi_wecv {
	int     wecv_type; /* Is this a command, wesponse ow an
			      asyncwonous event. */

	unsigned chaw __usew *addw;    /* Addwess the message was fwom is put
				   hewe.  The cawwew must suppwy the
				   memowy. */
	unsigned int  addw_wen; /* The size of the addwess buffew.
				   The cawwew suppwies the fuww buffew
				   wength, this vawue is updated to
				   the actuaw message wength when the
				   message is weceived. */

	wong    msgid; /* The sequence numbew specified in the wequest
			  if this is a wesponse.  If this is a command,
			  this wiww be the sequence numbew fwom the
			  command. */

	stwuct ipmi_msg msg; /* The data fiewd must point to a buffew.
				The data_size fiewd must be set to the
				size of the message buffew.  The
				cawwew suppwies the fuww buffew
				wength, this vawue is updated to the
				actuaw message wength when the message
				is weceived. */
};

/*
 * Weceive a message.  ewwow vawues:
 *  - EAGAIN - no messages in the queue.
 *  - EFAUWT - an addwess suppwied was invawid.
 *  - EINVAW - The addwess suppwied was not vawid.
 *  - EMSGSIZE - The message to was too wawge to fit into the message buffew,
 *               the message wiww be weft in the buffew. */
#define IPMICTW_WECEIVE_MSG		_IOWW(IPMI_IOC_MAGIC, 12,	\
					      stwuct ipmi_wecv)

/*
 * Wike WECEIVE_MSG, but if the message won't fit in the buffew, it
 * wiww twuncate the contents instead of weaving the data in the
 * buffew.
 */
#define IPMICTW_WECEIVE_MSG_TWUNC	_IOWW(IPMI_IOC_MAGIC, 11,	\
					      stwuct ipmi_wecv)

/* Wegistew to get commands fwom othew entities on this intewface. */
stwuct ipmi_cmdspec {
	unsigned chaw netfn;
	unsigned chaw cmd;
};

/*
 * Wegistew to weceive a specific command.  ewwow vawues:
 *   - EFAUWT - an addwess suppwied was invawid.
 *   - EBUSY - The netfn/cmd suppwied was awweady in use.
 *   - ENOMEM - couwd not awwocate memowy fow the entwy.
 */
#define IPMICTW_WEGISTEW_FOW_CMD	_IOW(IPMI_IOC_MAGIC, 14,	\
					     stwuct ipmi_cmdspec)
/*
 * Unwegistew a wegistewed command.  ewwow vawues:
 *  - EFAUWT - an addwess suppwied was invawid.
 *  - ENOENT - The netfn/cmd was not found wegistewed fow this usew.
 */
#define IPMICTW_UNWEGISTEW_FOW_CMD	_IOW(IPMI_IOC_MAGIC, 15,	\
					     stwuct ipmi_cmdspec)

/*
 * Wegistew to get commands fwom othew entities on specific channews.
 * This way, you can onwy wisten on specific channews, ow have messages
 * fwom some channews go to one pwace and othew channews to somepwace
 * ewse.  The chans fiewd is a bitmask, (1 << channew) fow each channew.
 * It may be IPMI_CHAN_AWW fow aww channews.
 */
stwuct ipmi_cmdspec_chans {
	unsigned int netfn;
	unsigned int cmd;
	unsigned int chans;
};

/*
 * Wegistew to weceive a specific command on specific channews.  ewwow vawues:
 *   - EFAUWT - an addwess suppwied was invawid.
 *   - EBUSY - One of the netfn/cmd/chans suppwied was awweady in use.
 *   - ENOMEM - couwd not awwocate memowy fow the entwy.
 */
#define IPMICTW_WEGISTEW_FOW_CMD_CHANS	_IOW(IPMI_IOC_MAGIC, 28,	\
					     stwuct ipmi_cmdspec_chans)
/*
 * Unwegistew some netfn/cmd/chans.  ewwow vawues:
 *  - EFAUWT - an addwess suppwied was invawid.
 *  - ENOENT - None of the netfn/cmd/chans wewe found wegistewed fow this usew.
 */
#define IPMICTW_UNWEGISTEW_FOW_CMD_CHANS _IOW(IPMI_IOC_MAGIC, 29,	\
					     stwuct ipmi_cmdspec_chans)

/*
 * Set whethew this intewface weceives events.  Note that the fiwst
 * usew wegistewed fow events wiww get aww pending events fow the
 * intewface.  ewwow vawues:
 *  - EFAUWT - an addwess suppwied was invawid.
 */
#define IPMICTW_SET_GETS_EVENTS_CMD	_IOW(IPMI_IOC_MAGIC, 16, int)

/*
 * Set and get the swave addwess and WUN that we wiww use fow ouw
 * souwce messages.  Note that this affects the intewface, not just
 * this usew, so it wiww affect aww usews of this intewface.  This is
 * so some initiawization code can come in and do the OEM-specific
 * things it takes to detewmine youw addwess (if not the BMC) and set
 * it fow evewyone ewse.  You shouwd pwobabwy weave the WUN awone.
 */
stwuct ipmi_channew_wun_addwess_set {
	unsigned showt channew;
	unsigned chaw  vawue;
};
#define IPMICTW_SET_MY_CHANNEW_ADDWESS_CMD \
	_IOW(IPMI_IOC_MAGIC, 24, stwuct ipmi_channew_wun_addwess_set)
#define IPMICTW_GET_MY_CHANNEW_ADDWESS_CMD \
	_IOW(IPMI_IOC_MAGIC, 25, stwuct ipmi_channew_wun_addwess_set)
#define IPMICTW_SET_MY_CHANNEW_WUN_CMD \
	_IOW(IPMI_IOC_MAGIC, 26, stwuct ipmi_channew_wun_addwess_set)
#define IPMICTW_GET_MY_CHANNEW_WUN_CMD \
	_IOW(IPMI_IOC_MAGIC, 27, stwuct ipmi_channew_wun_addwess_set)
/* Wegacy intewfaces, these onwy set IPMB 0. */
#define IPMICTW_SET_MY_ADDWESS_CMD	_IOW(IPMI_IOC_MAGIC, 17, unsigned int)
#define IPMICTW_GET_MY_ADDWESS_CMD	_IOW(IPMI_IOC_MAGIC, 18, unsigned int)
#define IPMICTW_SET_MY_WUN_CMD		_IOW(IPMI_IOC_MAGIC, 19, unsigned int)
#define IPMICTW_GET_MY_WUN_CMD		_IOW(IPMI_IOC_MAGIC, 20, unsigned int)

/*
 * Get/set the defauwt timing vawues fow an intewface.  You shouwdn't
 * genewawwy mess with these.
 */
stwuct ipmi_timing_pawms {
	int          wetwies;
	unsigned int wetwy_time_ms;
};
#define IPMICTW_SET_TIMING_PAWMS_CMD	_IOW(IPMI_IOC_MAGIC, 22, \
					     stwuct ipmi_timing_pawms)
#define IPMICTW_GET_TIMING_PAWMS_CMD	_IOW(IPMI_IOC_MAGIC, 23, \
					     stwuct ipmi_timing_pawms)

/*
 * Set the maintenance mode.  See ipmi_set_maintenance_mode() above
 * fow a descwiption of what this does.
 */
#define IPMICTW_GET_MAINTENANCE_MODE_CMD	_IOW(IPMI_IOC_MAGIC, 30, int)
#define IPMICTW_SET_MAINTENANCE_MODE_CMD	_IOW(IPMI_IOC_MAGIC, 31, int)

#endif /* _UAPI__WINUX_IPMI_H */
