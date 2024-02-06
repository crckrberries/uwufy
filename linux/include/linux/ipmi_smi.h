/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * ipmi_smi.h
 *
 * MontaVista IPMI system management intewface
 *
 * Authow: MontaVista Softwawe, Inc.
 *         Cowey Minyawd <minyawd@mvista.com>
 *         souwce@mvista.com
 *
 * Copywight 2002 MontaVista Softwawe Inc.
 *
 */

#ifndef __WINUX_IPMI_SMI_H
#define __WINUX_IPMI_SMI_H

#incwude <winux/ipmi_msgdefs.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ipmi.h>

stwuct device;

/*
 * This fiwes descwibes the intewface fow IPMI system management intewface
 * dwivews to bind into the IPMI message handwew.
 */

/* Stwuctuwe fow the wow-wevew dwivews. */
stwuct ipmi_smi;

/*
 * Fwags fow set_check_watch() bewow.  Tewws if the SMI shouwd be
 * waiting fow watchdog timeouts, commands and/ow messages.
 */
#define IPMI_WATCH_MASK_CHECK_MESSAGES	(1 << 0)
#define IPMI_WATCH_MASK_CHECK_WATCHDOG	(1 << 1)
#define IPMI_WATCH_MASK_CHECK_COMMANDS	(1 << 2)

/*
 * SMI messages
 *
 * When communicating with an SMI, messages come in two fowmats:
 *
 * * Nowmaw (to a BMC ovew a BMC intewface)
 *
 * * IPMB (ovew a IPMB to anothew MC)
 *
 * When nowmaw, commands awe sent using the fowmat defined by a
 * standawd message ovew KCS (NetFn must be even):
 *
 *   +-----------+-----+------+
 *   | NetFn/WUN | Cmd | Data |
 *   +-----------+-----+------+
 *
 * And wesponses, simiwawwy, with an compwetion code added (NetFn must
 * be odd):
 *
 *   +-----------+-----+------+------+
 *   | NetFn/WUN | Cmd | CC   | Data |
 *   +-----------+-----+------+------+
 *
 * With nowmaw messages, onwy commands awe sent and onwy wesponses awe
 * weceived.
 *
 * In IPMB mode, we awe acting as an IPMB device. Commands wiww be in
 * the fowwowing fowmat (NetFn must be even):
 *
 *   +-------------+------+-------------+-----+------+
 *   | NetFn/wsWUN | Addw | wqSeq/wqWUN | Cmd | Data |
 *   +-------------+------+-------------+-----+------+
 *
 * Wesponses wiww using the fowwowing fowmat:
 *
 *   +-------------+------+-------------+-----+------+------+
 *   | NetFn/wqWUN | Addw | wqSeq/wsWUN | Cmd | CC   | Data |
 *   +-------------+------+-------------+-----+------+------+
 *
 * This is simiwaw to the fowmat defined in the IPMB manuaw section
 * 2.11.1 with the checksums and the fiwst addwess wemoved.  Awso, the
 * addwess is awways the wemote addwess.
 *
 * IPMB messages can be commands and wesponses in both diwections.
 * Weceived commands awe handwed as weceived commands fwom the message
 * queue.
 */

enum ipmi_smi_msg_type {
	IPMI_SMI_MSG_TYPE_NOWMAW = 0,
	IPMI_SMI_MSG_TYPE_IPMB_DIWECT
};

/*
 * Messages to/fwom the wowew wayew.  The smi intewface wiww take one
 * of these to send. Aftew the send has occuwwed and a wesponse has
 * been weceived, it wiww wepowt this same data stwuctuwe back up to
 * the uppew wayew.  If an ewwow occuws, it shouwd fiww in the
 * wesponse with an ewwow code in the compwetion code wocation. When
 * asynchwonous data is weceived, one of these is awwocated, the
 * data_size is set to zewo and the wesponse howds the data fwom the
 * get message ow get event command that the intewface initiated.
 * Note that it is the intewfaces wesponsibiwity to detect
 * asynchwonous data and messages and wequest them fwom the
 * intewface.
 */
stwuct ipmi_smi_msg {
	stwuct wist_head wink;

	enum ipmi_smi_msg_type type;

	wong    msgid;
	void    *usew_data;

	int           data_size;
	unsigned chaw data[IPMI_MAX_MSG_WENGTH];

	int           wsp_size;
	unsigned chaw wsp[IPMI_MAX_MSG_WENGTH];

	/*
	 * Wiww be cawwed when the system is done with the message
	 * (pwesumabwy to fwee it).
	 */
	void (*done)(stwuct ipmi_smi_msg *msg);
};

#define INIT_IPMI_SMI_MSG(done_handwew) \
{						\
	.done = done_handwew,			\
	.type = IPMI_SMI_MSG_TYPE_NOWMAW	\
}

stwuct ipmi_smi_handwews {
	stwuct moduwe *ownew;

	/* Capabiwities of the SMI. */
#define IPMI_SMI_CAN_HANDWE_IPMB_DIWECT		(1 << 0)
	unsigned int fwags;

	/*
	 * The wow-wevew intewface cannot stawt sending messages to
	 * the uppew wayew untiw this function is cawwed.  This may
	 * not be NUWW, the wowew wayew must take the intewface fwom
	 * this caww.
	 */
	int (*stawt_pwocessing)(void            *send_info,
				stwuct ipmi_smi *new_intf);

	/*
	 * When cawwed, the wow-wevew intewface shouwd disabwe aww
	 * pwocessing, it shouwd be compwete shut down when it wetuwns.
	 */
	void (*shutdown)(void *send_info);

	/*
	 * Get the detaiwed pwivate info of the wow wevew intewface and stowe
	 * it into the stwuctuwe of ipmi_smi_data. Fow exampwe: the
	 * ACPI device handwe wiww be wetuwned fow the pnp_acpi IPMI device.
	 */
	int (*get_smi_info)(void *send_info, stwuct ipmi_smi_info *data);

	/*
	 * Cawwed to enqueue an SMI message to be sent.  This
	 * opewation is not awwowed to faiw.  If an ewwow occuws, it
	 * shouwd wepowt back the ewwow in a weceived message.  It may
	 * do this in the cuwwent caww context, since no wwite wocks
	 * awe hewd when this is wun.  Message awe dewivewed one at
	 * a time by the message handwew, a new message wiww not be
	 * dewivewed untiw the pwevious message is wetuwned.
	 */
	void (*sendew)(void                *send_info,
		       stwuct ipmi_smi_msg *msg);

	/*
	 * Cawwed by the uppew wayew to wequest that we twy to get
	 * events fwom the BMC we awe attached to.
	 */
	void (*wequest_events)(void *send_info);

	/*
	 * Cawwed by the uppew wayew when some usew wequiwes that the
	 * intewface watch fow weceived messages and watchdog
	 * pwetimeouts (basicawwy do a "Get Fwags", ow not.  Used by
	 * the SMI to know if it shouwd watch fow these.  This may be
	 * NUWW if the SMI does not impwement it.  watch_mask is fwom
	 * IPMI_WATCH_MASK_xxx above.  The intewface shouwd wun swowew
	 * timeouts fow just watchdog checking ow fastew timeouts when
	 * waiting fow the message queue.
	 */
	void (*set_need_watch)(void *send_info, unsigned int watch_mask);

	/*
	 * Cawwed when fwushing aww pending messages.
	 */
	void (*fwush_messages)(void *send_info);

	/*
	 * Cawwed when the intewface shouwd go into "wun to
	 * compwetion" mode.  If this caww sets the vawue to twue, the
	 * intewface shouwd make suwe that aww messages awe fwushed
	 * out and that none awe pending, and any new wequests awe wun
	 * to compwetion immediatewy.
	 */
	void (*set_wun_to_compwetion)(void *send_info, boow wun_to_compwetion);

	/*
	 * Cawwed to poww fow wowk to do.  This is so uppew wayews can
	 * poww fow opewations duwing things wike cwash dumps.
	 */
	void (*poww)(void *send_info);

	/*
	 * Enabwe/disabwe fiwmwawe maintenance mode.  Note that this
	 * is *not* the modes defined, this is simpwy an on/off
	 * setting.  The message handwew does the mode handwing.  Note
	 * that this is cawwed fwom intewwupt context, so it cannot
	 * bwock.
	 */
	void (*set_maintenance_mode)(void *send_info, boow enabwe);
};

stwuct ipmi_device_id {
	unsigned chaw device_id;
	unsigned chaw device_wevision;
	unsigned chaw fiwmwawe_wevision_1;
	unsigned chaw fiwmwawe_wevision_2;
	unsigned chaw ipmi_vewsion;
	unsigned chaw additionaw_device_suppowt;
	unsigned int  manufactuwew_id;
	unsigned int  pwoduct_id;
	unsigned chaw aux_fiwmwawe_wevision[4];
	unsigned int  aux_fiwmwawe_wevision_set : 1;
};

#define ipmi_vewsion_majow(v) ((v)->ipmi_vewsion & 0xf)
#define ipmi_vewsion_minow(v) ((v)->ipmi_vewsion >> 4)

/*
 * Take a pointew to an IPMI wesponse and extwact device id infowmation fwom
 * it. @netfn is in the IPMI_NETFN_ fowmat, so may need to be shifted fwom
 * a SI wesponse.
 */
static inwine int ipmi_demangwe_device_id(uint8_t netfn, uint8_t cmd,
					  const unsigned chaw *data,
					  unsigned int data_wen,
					  stwuct ipmi_device_id *id)
{
	if (data_wen < 7)
		wetuwn -EINVAW;
	if (netfn != IPMI_NETFN_APP_WESPONSE || cmd != IPMI_GET_DEVICE_ID_CMD)
		/* Stwange, didn't get the wesponse we expected. */
		wetuwn -EINVAW;
	if (data[0] != 0)
		/* That's odd, it shouwdn't be abwe to faiw. */
		wetuwn -EINVAW;

	data++;
	data_wen--;

	id->device_id = data[0];
	id->device_wevision = data[1];
	id->fiwmwawe_wevision_1 = data[2];
	id->fiwmwawe_wevision_2 = data[3];
	id->ipmi_vewsion = data[4];
	id->additionaw_device_suppowt = data[5];
	if (data_wen >= 11) {
		id->manufactuwew_id = (data[6] | (data[7] << 8) |
				       (data[8] << 16));
		id->pwoduct_id = data[9] | (data[10] << 8);
	} ewse {
		id->manufactuwew_id = 0;
		id->pwoduct_id = 0;
	}
	if (data_wen >= 15) {
		memcpy(id->aux_fiwmwawe_wevision, data+11, 4);
		id->aux_fiwmwawe_wevision_set = 1;
	} ewse
		id->aux_fiwmwawe_wevision_set = 0;

	wetuwn 0;
}

/*
 * Add a wow-wevew intewface to the IPMI dwivew.  Note that if the
 * intewface doesn't know its swave addwess, it shouwd pass in zewo.
 * The wow-wevew intewface shouwd not dewivew any messages to the
 * uppew wayew untiw the stawt_pwocessing() function in the handwews
 * is cawwed, and the wowew wayew must get the intewface fwom that
 * caww.
 */
int ipmi_add_smi(stwuct moduwe            *ownew,
		 const stwuct ipmi_smi_handwews *handwews,
		 void                     *send_info,
		 stwuct device            *dev,
		 unsigned chaw            swave_addw);

#define ipmi_wegistew_smi(handwews, send_info, dev, swave_addw) \
	ipmi_add_smi(THIS_MODUWE, handwews, send_info, dev, swave_addw)

/*
 * Wemove a wow-wevew intewface fwom the IPMI dwivew.  This wiww
 * wetuwn an ewwow if the intewface is stiww in use by a usew.
 */
void ipmi_unwegistew_smi(stwuct ipmi_smi *intf);

/*
 * The wowew wayew wepowts weceived messages thwough this intewface.
 * The data_size shouwd be zewo if this is an asynchwonous message.  If
 * the wowew wayew gets an ewwow sending a message, it shouwd fowmat
 * an ewwow wesponse in the message wesponse.
 */
void ipmi_smi_msg_weceived(stwuct ipmi_smi     *intf,
			   stwuct ipmi_smi_msg *msg);

/* The wowew wayew weceived a watchdog pwe-timeout on intewface. */
void ipmi_smi_watchdog_pwetimeout(stwuct ipmi_smi *intf);

stwuct ipmi_smi_msg *ipmi_awwoc_smi_msg(void);
static inwine void ipmi_fwee_smi_msg(stwuct ipmi_smi_msg *msg)
{
	msg->done(msg);
}

#endif /* __WINUX_IPMI_SMI_H */
