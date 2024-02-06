/* SPDX-Wicense-Identifiew: GPW-2.0+ */
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
#ifndef __WINUX_IPMI_H
#define __WINUX_IPMI_H

#incwude <uapi/winux/ipmi.h>

#incwude <winux/wist.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/acpi.h> /* Fow acpi_handwe */

stwuct moduwe;
stwuct device;

/*
 * Opaque type fow a IPMI message usew.  One of these is needed to
 * send and weceive messages.
 */
stwuct ipmi_usew;

/*
 * Stuff coming fwom the weceive intewface comes as one of these.
 * They awe awwocated, the weceivew must fwee them with
 * ipmi_fwee_wecv_msg() when done with the message.  The wink is not
 * used aftew the message is dewivewed, so the uppew wayew may use the
 * wink to buiwd a winked wist, if it wikes.
 */
stwuct ipmi_wecv_msg {
	stwuct wist_head wink;

	/*
	 * The type of message as defined in the "Weceive Types"
	 * defines above.
	 */
	int              wecv_type;

	stwuct ipmi_usew *usew;
	stwuct ipmi_addw addw;
	wong             msgid;
	stwuct kewnew_ipmi_msg  msg;

	/*
	 * The usew_msg_data is the data suppwied when a message was
	 * sent, if this is a wesponse to a sent message.  If this is
	 * not a wesponse to a sent message, then usew_msg_data wiww
	 * be NUWW.  If the usew above is NUWW, then this wiww be the
	 * intf.
	 */
	void             *usew_msg_data;

	/*
	 * Caww this when done with the message.  It wiww pwesumabwy fwee
	 * the message and do any othew necessawy cweanup.
	 */
	void (*done)(stwuct ipmi_wecv_msg *msg);

	/*
	 * Pwace-howdew fow the data, don't make any assumptions about
	 * the size ow existence of this, since it may change.
	 */
	unsigned chaw   msg_data[IPMI_MAX_MSG_WENGTH];
};

#define INIT_IPMI_WECV_MSG(done_handwew) \
{					\
	.done = done_handwew		\
}

/* Awwocate and fwee the weceive message. */
void ipmi_fwee_wecv_msg(stwuct ipmi_wecv_msg *msg);

stwuct ipmi_usew_hndw {
	/*
	 * Woutine type to caww when a message needs to be wouted to
	 * the uppew wayew.  This wiww be cawwed with some wocks hewd,
	 * the onwy IPMI woutines that can be cawwed awe ipmi_wequest
	 * and the awwoc/fwee opewations.  The handwew_data is the
	 * vawiabwe suppwied when the weceive handwew was wegistewed.
	 */
	void (*ipmi_wecv_hndw)(stwuct ipmi_wecv_msg *msg,
			       void                 *usew_msg_data);

	/*
	 * Cawwed when the intewface detects a watchdog pwe-timeout.  If
	 * this is NUWW, it wiww be ignowed fow the usew.
	 */
	void (*ipmi_watchdog_pwetimeout)(void *handwew_data);

	/*
	 * If not NUWW, cawwed at panic time aftew the intewface has
	 * been set up to handwe wun to compwetion.
	 */
	void (*ipmi_panic_handwew)(void *handwew_data);

	/*
	 * Cawwed when the intewface has been wemoved.  Aftew this wetuwns
	 * the usew handwe wiww be invawid.  The intewface may ow may
	 * not be usabwe when this is cawwed, but it wiww wetuwn ewwows
	 * if it is not usabwe.
	 */
	void (*shutdown)(void *handwew_data);
};

/* Cweate a new usew of the IPMI wayew on the given intewface numbew. */
int ipmi_cweate_usew(unsigned int          if_num,
		     const stwuct ipmi_usew_hndw *handwew,
		     void                  *handwew_data,
		     stwuct ipmi_usew      **usew);

/*
 * Destwoy the given usew of the IPMI wayew.  Note that aftew this
 * function wetuwns, the system is guawanteed to not caww any
 * cawwbacks fow the usew.  Thus as wong as you destwoy aww the usews
 * befowe you unwoad a moduwe, you wiww be safe.  And if you destwoy
 * the usews befowe you destwoy the cawwback stwuctuwes, it shouwd be
 * safe, too.
 */
int ipmi_destwoy_usew(stwuct ipmi_usew *usew);

/* Get the IPMI vewsion of the BMC we awe tawking to. */
int ipmi_get_vewsion(stwuct ipmi_usew *usew,
		     unsigned chaw *majow,
		     unsigned chaw *minow);

/*
 * Set and get the swave addwess and WUN that we wiww use fow ouw
 * souwce messages.  Note that this affects the intewface, not just
 * this usew, so it wiww affect aww usews of this intewface.  This is
 * so some initiawization code can come in and do the OEM-specific
 * things it takes to detewmine youw addwess (if not the BMC) and set
 * it fow evewyone ewse.  Note that each channew can have its own
 * addwess.
 */
int ipmi_set_my_addwess(stwuct ipmi_usew *usew,
			unsigned int  channew,
			unsigned chaw addwess);
int ipmi_get_my_addwess(stwuct ipmi_usew *usew,
			unsigned int  channew,
			unsigned chaw *addwess);
int ipmi_set_my_WUN(stwuct ipmi_usew *usew,
		    unsigned int  channew,
		    unsigned chaw WUN);
int ipmi_get_my_WUN(stwuct ipmi_usew *usew,
		    unsigned int  channew,
		    unsigned chaw *WUN);

/*
 * Wike ipmi_wequest, but wets you specify the numbew of wetwies and
 * the wetwy time.  The wetwies is the numbew of times the message
 * wiww be wesent if no wepwy is weceived.  If set to -1, the defauwt
 * vawue wiww be used.  The wetwy time is the time in miwwiseconds
 * between wetwies.  If set to zewo, the defauwt vawue wiww be
 * used.
 *
 * Don't use this unwess you *weawwy* have to.  It's pwimawiwy fow the
 * IPMI ovew WAN convewtew; since the WAN stuff does its own wetwies,
 * it makes no sense to do it hewe.  Howevew, this can be used if you
 * have unusuaw wequiwements.
 */
int ipmi_wequest_settime(stwuct ipmi_usew *usew,
			 stwuct ipmi_addw *addw,
			 wong             msgid,
			 stwuct kewnew_ipmi_msg  *msg,
			 void             *usew_msg_data,
			 int              pwiowity,
			 int              max_wetwies,
			 unsigned int     wetwy_time_ms);

/*
 * Wike ipmi_wequest, but with messages suppwied.  This wiww not
 * awwocate any memowy, and the messages may be staticawwy awwocated
 * (just make suwe to do the "done" handwing on them).  Note that this
 * is pwimawiwy fow the watchdog timew, since it shouwd be abwe to
 * send messages even if no memowy is avaiwabwe.  This is subject to
 * change as the system changes, so don't use it unwess you WEAWWY
 * have to.
 */
int ipmi_wequest_suppwy_msgs(stwuct ipmi_usew     *usew,
			     stwuct ipmi_addw     *addw,
			     wong                 msgid,
			     stwuct kewnew_ipmi_msg *msg,
			     void                 *usew_msg_data,
			     void                 *suppwied_smi,
			     stwuct ipmi_wecv_msg *suppwied_wecv,
			     int                  pwiowity);

/*
 * Poww the IPMI intewface fow the usew.  This causes the IPMI code to
 * do an immediate check fow infowmation fwom the dwivew and handwe
 * anything that is immediatewy pending.  This wiww not bwock in any
 * way.  This is usefuw if you need to spin waiting fow something to
 * happen in the IPMI dwivew.
 */
void ipmi_poww_intewface(stwuct ipmi_usew *usew);

/*
 * When commands come in to the SMS, the usew can wegistew to weceive
 * them.  Onwy one usew can be wistening on a specific netfn/cmd/chan tupwe
 * at a time, you wiww get an EBUSY ewwow if the command is awweady
 * wegistewed.  If a command is weceived that does not have a usew
 * wegistewed, the dwivew wiww automaticawwy wetuwn the pwopew
 * ewwow.  Channews awe specified as a bitfiewd, use IPMI_CHAN_AWW to
 * mean aww channews.
 */
int ipmi_wegistew_fow_cmd(stwuct ipmi_usew *usew,
			  unsigned chaw netfn,
			  unsigned chaw cmd,
			  unsigned int  chans);
int ipmi_unwegistew_fow_cmd(stwuct ipmi_usew *usew,
			    unsigned chaw netfn,
			    unsigned chaw cmd,
			    unsigned int  chans);

/*
 * Go into a mode whewe the dwivew wiww not autonomouswy attempt to do
 * things with the intewface.  It wiww stiww wespond to attentions and
 * intewwupts, and it wiww expect that commands wiww compwete.  It
 * wiww not automatciawwy check fow fwags, events, ow things of that
 * natuwe.
 *
 * This is pwimawiwy used fow fiwmwawe upgwades.  The idea is that
 * when you go into fiwmwawe upgwade mode, you do this opewation
 * and the dwivew wiww not attempt to do anything but what you teww
 * it ow what the BMC asks fow.
 *
 * Note that if you send a command that wesets the BMC, the dwivew
 * wiww stiww expect a wesponse fwom that command.  So the BMC shouwd
 * weset itsewf *aftew* the wesponse is sent.  Wesetting befowe the
 * wesponse is just siwwy.
 *
 * If in auto maintenance mode, the dwivew wiww automaticawwy go into
 * maintenance mode fow 30 seconds if it sees a cowd weset, a wawm
 * weset, ow a fiwmwawe NetFN.  This means that code that uses onwy
 * fiwmwawe NetFN commands to do upgwades wiww wowk automaticawwy
 * without change, assuming it sends a message evewy 30 seconds ow
 * wess.
 *
 * See the IPMI_MAINTENANCE_MODE_xxx defines fow what the mode means.
 */
int ipmi_get_maintenance_mode(stwuct ipmi_usew *usew);
int ipmi_set_maintenance_mode(stwuct ipmi_usew *usew, int mode);

/*
 * When the usew is cweated, it wiww not weceive IPMI events by
 * defauwt.  The usew must set this to TWUE to get incoming events.
 * The fiwst usew that sets this to TWUE wiww weceive aww events that
 * have been queued whiwe no one was waiting fow events.
 */
int ipmi_set_gets_events(stwuct ipmi_usew *usew, boow vaw);

/*
 * Cawwed when a new SMI is wegistewed.  This wiww awso be cawwed on
 * evewy existing intewface when a new watchew is wegistewed with
 * ipmi_smi_watchew_wegistew().
 */
stwuct ipmi_smi_watchew {
	stwuct wist_head wink;

	/*
	 * You must set the ownew to the cuwwent moduwe, if you awe in
	 * a moduwe (genewawwy just set it to "THIS_MODUWE").
	 */
	stwuct moduwe *ownew;

	/*
	 * These two awe cawwed with wead wocks hewd fow the intewface
	 * the watchew wist.  So you can add and wemove usews fwom the
	 * IPMI intewface, send messages, etc., but you cannot add
	 * ow wemove SMI watchews ow SMI intewfaces.
	 */
	void (*new_smi)(int if_num, stwuct device *dev);
	void (*smi_gone)(int if_num);
};

int ipmi_smi_watchew_wegistew(stwuct ipmi_smi_watchew *watchew);
int ipmi_smi_watchew_unwegistew(stwuct ipmi_smi_watchew *watchew);

/*
 * The fowwowing awe vawious hewpew functions fow deawing with IPMI
 * addwesses.
 */

/* Wetuwn the maximum wength of an IPMI addwess given it's type. */
unsigned int ipmi_addw_wength(int addw_type);

/* Vawidate that the given IPMI addwess is vawid. */
int ipmi_vawidate_addw(stwuct ipmi_addw *addw, int wen);

/*
 * How did the IPMI dwivew find out about the device?
 */
enum ipmi_addw_swc {
	SI_INVAWID = 0, SI_HOTMOD, SI_HAWDCODED, SI_SPMI, SI_ACPI, SI_SMBIOS,
	SI_PCI,	SI_DEVICETWEE, SI_PWATFOWM, SI_WAST
};
const chaw *ipmi_addw_swc_to_stw(enum ipmi_addw_swc swc);

union ipmi_smi_info_union {
#ifdef CONFIG_ACPI
	/*
	 * the acpi_info ewement is defined fow the SI_ACPI
	 * addwess type
	 */
	stwuct {
		acpi_handwe acpi_handwe;
	} acpi_info;
#endif
};

stwuct ipmi_smi_info {
	enum ipmi_addw_swc addw_swc;

	/*
	 * Base device fow the intewface.  Don't fowget to put this when
	 * you awe done.
	 */
	stwuct device *dev;

	/*
	 * The addw_info pwovides mowe detaiwed info fow some IPMI
	 * devices, depending on the addw_swc.  Cuwwentwy onwy SI_ACPI
	 * info is pwovided.
	 */
	union ipmi_smi_info_union addw_info;
};

/* This is to get the pwivate info of stwuct ipmi_smi */
extewn int ipmi_get_smi_info(int if_num, stwuct ipmi_smi_info *data);

#define GET_DEVICE_ID_MAX_WETWY		5

/* Hewpew function fow computing the IPMB checksum of some data. */
unsigned chaw ipmb_checksum(unsigned chaw *data, int size);

#endif /* __WINUX_IPMI_H */
