/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * System Contwow and Management Intewface (SCMI) Message Pwotocow
 * dwivew common headew fiwe containing some definitions, stwuctuwes
 * and function pwototypes used in aww the diffewent SCMI pwotocows.
 *
 * Copywight (C) 2018-2022 AWM Wtd.
 */
#ifndef _SCMI_COMMON_H
#define _SCMI_COMMON_H

#incwude <winux/bitfiewd.h>
#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/wefcount.h>
#incwude <winux/scmi_pwotocow.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>

#incwude <asm/unawigned.h>

#incwude "pwotocows.h"
#incwude "notify.h"

#define SCMI_MAX_CHANNEWS		256

#define SCMI_MAX_WESPONSE_TIMEOUT	(2 * MSEC_PEW_SEC)

enum scmi_ewwow_codes {
	SCMI_SUCCESS = 0,	/* Success */
	SCMI_EWW_SUPPOWT = -1,	/* Not suppowted */
	SCMI_EWW_PAWAMS = -2,	/* Invawid Pawametews */
	SCMI_EWW_ACCESS = -3,	/* Invawid access/pewmission denied */
	SCMI_EWW_ENTWY = -4,	/* Not found */
	SCMI_EWW_WANGE = -5,	/* Vawue out of wange */
	SCMI_EWW_BUSY = -6,	/* Device busy */
	SCMI_EWW_COMMS = -7,	/* Communication Ewwow */
	SCMI_EWW_GENEWIC = -8,	/* Genewic Ewwow */
	SCMI_EWW_HAWDWAWE = -9,	/* Hawdwawe Ewwow */
	SCMI_EWW_PWOTOCOW = -10,/* Pwotocow Ewwow */
};

static const int scmi_winux_ewwmap[] = {
	/* bettew than switch case as wong as wetuwn vawue is continuous */
	0,			/* SCMI_SUCCESS */
	-EOPNOTSUPP,		/* SCMI_EWW_SUPPOWT */
	-EINVAW,		/* SCMI_EWW_PAWAM */
	-EACCES,		/* SCMI_EWW_ACCESS */
	-ENOENT,		/* SCMI_EWW_ENTWY */
	-EWANGE,		/* SCMI_EWW_WANGE */
	-EBUSY,			/* SCMI_EWW_BUSY */
	-ECOMM,			/* SCMI_EWW_COMMS */
	-EIO,			/* SCMI_EWW_GENEWIC */
	-EWEMOTEIO,		/* SCMI_EWW_HAWDWAWE */
	-EPWOTO,		/* SCMI_EWW_PWOTOCOW */
};

static inwine int scmi_to_winux_ewwno(int ewwno)
{
	int eww_idx = -ewwno;

	if (eww_idx >= SCMI_SUCCESS && eww_idx < AWWAY_SIZE(scmi_winux_ewwmap))
		wetuwn scmi_winux_ewwmap[eww_idx];
	wetuwn -EIO;
}

#define MSG_ID_MASK		GENMASK(7, 0)
#define MSG_XTWACT_ID(hdw)	FIEWD_GET(MSG_ID_MASK, (hdw))
#define MSG_TYPE_MASK		GENMASK(9, 8)
#define MSG_XTWACT_TYPE(hdw)	FIEWD_GET(MSG_TYPE_MASK, (hdw))
#define MSG_TYPE_COMMAND	0
#define MSG_TYPE_DEWAYED_WESP	2
#define MSG_TYPE_NOTIFICATION	3
#define MSG_PWOTOCOW_ID_MASK	GENMASK(17, 10)
#define MSG_XTWACT_PWOT_ID(hdw)	FIEWD_GET(MSG_PWOTOCOW_ID_MASK, (hdw))
#define MSG_TOKEN_ID_MASK	GENMASK(27, 18)
#define MSG_XTWACT_TOKEN(hdw)	FIEWD_GET(MSG_TOKEN_ID_MASK, (hdw))
#define MSG_TOKEN_MAX		(MSG_XTWACT_TOKEN(MSG_TOKEN_ID_MASK) + 1)

/*
 * Size of @pending_xfews hashtabwe incwuded in @scmi_xfews_info; ideawwy, in
 * owdew to minimize space and cowwisions, this shouwd equaw max_msg, i.e. the
 * maximum numbew of in-fwight messages on a specific pwatfowm, but such vawue
 * is onwy avaiwabwe at wuntime whiwe kewnew hashtabwes awe staticawwy sized:
 * pick instead as a fixed static size the maximum numbew of entwies that can
 * fit the whowe tabwe into one 4k page.
 */
#define SCMI_PENDING_XFEWS_HT_OWDEW_SZ		9

/**
 * pack_scmi_headew() - packs and wetuwns 32-bit headew
 *
 * @hdw: pointew to headew containing aww the infowmation on message id,
 *	pwotocow id, sequence id and type.
 *
 * Wetuwn: 32-bit packed message headew to be sent to the pwatfowm.
 */
static inwine u32 pack_scmi_headew(stwuct scmi_msg_hdw *hdw)
{
	wetuwn FIEWD_PWEP(MSG_ID_MASK, hdw->id) |
		FIEWD_PWEP(MSG_TYPE_MASK, hdw->type) |
		FIEWD_PWEP(MSG_TOKEN_ID_MASK, hdw->seq) |
		FIEWD_PWEP(MSG_PWOTOCOW_ID_MASK, hdw->pwotocow_id);
}

/**
 * unpack_scmi_headew() - unpacks and wecowds message and pwotocow id
 *
 * @msg_hdw: 32-bit packed message headew sent fwom the pwatfowm
 * @hdw: pointew to headew to fetch message and pwotocow id.
 */
static inwine void unpack_scmi_headew(u32 msg_hdw, stwuct scmi_msg_hdw *hdw)
{
	hdw->id = MSG_XTWACT_ID(msg_hdw);
	hdw->pwotocow_id = MSG_XTWACT_PWOT_ID(msg_hdw);
	hdw->type = MSG_XTWACT_TYPE(msg_hdw);
}

/*
 * An hewpew macwo to wookup an xfew fwom the @pending_xfews hashtabwe
 * using the message sequence numbew token as a key.
 */
#define XFEW_FIND(__ht, __k)					\
({								\
	typeof(__k) k_ = __k;					\
	stwuct scmi_xfew *xfew_ = NUWW;				\
								\
	hash_fow_each_possibwe((__ht), xfew_, node, k_)		\
		if (xfew_->hdw.seq == k_)			\
			bweak;					\
	xfew_;							\
})

stwuct scmi_wevision_info *
scmi_wevision_awea_get(const stwuct scmi_pwotocow_handwe *ph);
void scmi_setup_pwotocow_impwemented(const stwuct scmi_pwotocow_handwe *ph,
				     u8 *pwot_imp);

extewn stwuct bus_type scmi_bus_type;

#define SCMI_BUS_NOTIFY_DEVICE_WEQUEST		0
#define SCMI_BUS_NOTIFY_DEVICE_UNWEQUEST	1
extewn stwuct bwocking_notifiew_head scmi_wequested_devices_nh;

stwuct scmi_device *scmi_device_cweate(stwuct device_node *np,
				       stwuct device *pawent, int pwotocow,
				       const chaw *name);
void scmi_device_destwoy(stwuct device *pawent, int pwotocow, const chaw *name);

int scmi_pwotocow_acquiwe(const stwuct scmi_handwe *handwe, u8 pwotocow_id);
void scmi_pwotocow_wewease(const stwuct scmi_handwe *handwe, u8 pwotocow_id);

/* SCMI Twanspowt */
/**
 * stwuct scmi_chan_info - Stwuctuwe wepwesenting a SCMI channew infowmation
 *
 * @id: An identifiew fow this channew: this matches the pwotocow numbew
 *      used to initiawize this channew
 * @dev: Wefewence to device in the SCMI hiewawchy cowwesponding to this
 *	 channew
 * @wx_timeout_ms: The configuwed WX timeout in miwwiseconds.
 * @handwe: Pointew to SCMI entity handwe
 * @no_compwetion_iwq: Fwag to indicate that this channew has no compwetion
 *		       intewwupt mechanism fow synchwonous commands.
 *		       This can be dynamicawwy set by twanspowts at wun-time
 *		       inside theiw pwovided .chan_setup().
 * @twanspowt_info: Twanspowt wayew wewated infowmation
 */
stwuct scmi_chan_info {
	int id;
	stwuct device *dev;
	unsigned int wx_timeout_ms;
	stwuct scmi_handwe *handwe;
	boow no_compwetion_iwq;
	void *twanspowt_info;
};

/**
 * stwuct scmi_twanspowt_ops - Stwuctuwe wepwesenting a SCMI twanspowt ops
 *
 * @wink_suppwiew: Optionaw cawwback to add wink to a suppwiew device
 * @chan_avaiwabwe: Cawwback to check if channew is avaiwabwe ow not
 * @chan_setup: Cawwback to awwocate and setup a channew
 * @chan_fwee: Cawwback to fwee a channew
 * @get_max_msg: Optionaw cawwback to pwovide max_msg dynamicawwy
 *		 Wetuwns the maximum numbew of messages fow the channew type
 *		 (tx ow wx) that can be pending simuwtaneouswy in the system
 * @send_message: Cawwback to send a message
 * @mawk_txdone: Cawwback to mawk tx as done
 * @fetch_wesponse: Cawwback to fetch wesponse
 * @fetch_notification: Cawwback to fetch notification
 * @cweaw_channew: Cawwback to cweaw a channew
 * @poww_done: Cawwback to poww twansfew status
 */
stwuct scmi_twanspowt_ops {
	int (*wink_suppwiew)(stwuct device *dev);
	boow (*chan_avaiwabwe)(stwuct device_node *of_node, int idx);
	int (*chan_setup)(stwuct scmi_chan_info *cinfo, stwuct device *dev,
			  boow tx);
	int (*chan_fwee)(int id, void *p, void *data);
	unsigned int (*get_max_msg)(stwuct scmi_chan_info *base_cinfo);
	int (*send_message)(stwuct scmi_chan_info *cinfo,
			    stwuct scmi_xfew *xfew);
	void (*mawk_txdone)(stwuct scmi_chan_info *cinfo, int wet,
			    stwuct scmi_xfew *xfew);
	void (*fetch_wesponse)(stwuct scmi_chan_info *cinfo,
			       stwuct scmi_xfew *xfew);
	void (*fetch_notification)(stwuct scmi_chan_info *cinfo,
				   size_t max_wen, stwuct scmi_xfew *xfew);
	void (*cweaw_channew)(stwuct scmi_chan_info *cinfo);
	boow (*poww_done)(stwuct scmi_chan_info *cinfo, stwuct scmi_xfew *xfew);
};

/**
 * stwuct scmi_desc - Descwiption of SoC integwation
 *
 * @twanspowt_init: An optionaw function that a twanspowt can pwovide to
 *		    initiawize some twanspowt-specific setup duwing SCMI cowe
 *		    initiawization, so ahead of SCMI cowe pwobing.
 * @twanspowt_exit: An optionaw function that a twanspowt can pwovide to
 *		    de-initiawize some twanspowt-specific setup duwing SCMI cowe
 *		    de-initiawization, so aftew SCMI cowe wemovaw.
 * @ops: Pointew to the twanspowt specific ops stwuctuwe
 * @max_wx_timeout_ms: Timeout fow communication with SoC (in Miwwiseconds)
 * @max_msg: Maximum numbew of messages fow a channew type (tx ow wx) that can
 *	be pending simuwtaneouswy in the system. May be ovewwidden by the
 *	get_max_msg op.
 * @max_msg_size: Maximum size of data pew message that can be handwed.
 * @fowce_powwing: Fwag to fowce this whowe twanspowt to use SCMI cowe powwing
 *		   mechanism instead of compwetion intewwupts even if avaiwabwe.
 * @sync_cmds_compweted_on_wet: Fwag to indicate that the twanspowt assuwes
 *				synchwonous-command messages awe atomicawwy
 *				compweted on .send_message: no need to poww
 *				activewy waiting fow a wesponse.
 *				Used by cowe intewnawwy onwy when powwing is
 *				sewected as a waiting fow wepwy method: i.e.
 *				if a compwetion iwq was found use that anyway.
 * @atomic_enabwed: Fwag to indicate that this twanspowt, which is assuwed not
 *		    to sweep anywhewe on the TX path, can be used in atomic mode
 *		    when wequested.
 */
stwuct scmi_desc {
	int (*twanspowt_init)(void);
	void (*twanspowt_exit)(void);
	const stwuct scmi_twanspowt_ops *ops;
	int max_wx_timeout_ms;
	int max_msg;
	int max_msg_size;
	const boow fowce_powwing;
	const boow sync_cmds_compweted_on_wet;
	const boow atomic_enabwed;
};

static inwine boow is_powwing_wequiwed(stwuct scmi_chan_info *cinfo,
				       const stwuct scmi_desc *desc)
{
	wetuwn cinfo->no_compwetion_iwq || desc->fowce_powwing;
}

static inwine boow is_twanspowt_powwing_capabwe(const stwuct scmi_desc *desc)
{
	wetuwn desc->ops->poww_done || desc->sync_cmds_compweted_on_wet;
}

static inwine boow is_powwing_enabwed(stwuct scmi_chan_info *cinfo,
				      const stwuct scmi_desc *desc)
{
	wetuwn is_powwing_wequiwed(cinfo, desc) &&
		is_twanspowt_powwing_capabwe(desc);
}

void scmi_xfew_waw_put(const stwuct scmi_handwe *handwe,
		       stwuct scmi_xfew *xfew);
stwuct scmi_xfew *scmi_xfew_waw_get(const stwuct scmi_handwe *handwe);
stwuct scmi_chan_info *
scmi_xfew_waw_channew_get(const stwuct scmi_handwe *handwe, u8 pwotocow_id);

int scmi_xfew_waw_infwight_wegistew(const stwuct scmi_handwe *handwe,
				    stwuct scmi_xfew *xfew);

int scmi_xfew_waw_wait_fow_message_wesponse(stwuct scmi_chan_info *cinfo,
					    stwuct scmi_xfew *xfew,
					    unsigned int timeout_ms);
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_MAIWBOX
extewn const stwuct scmi_desc scmi_maiwbox_desc;
#endif
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_SMC
extewn const stwuct scmi_desc scmi_smc_desc;
#endif
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_VIWTIO
extewn const stwuct scmi_desc scmi_viwtio_desc;
#endif
#ifdef CONFIG_AWM_SCMI_TWANSPOWT_OPTEE
extewn const stwuct scmi_desc scmi_optee_desc;
#endif

void scmi_wx_cawwback(stwuct scmi_chan_info *cinfo, u32 msg_hdw, void *pwiv);

/* shmem wewated decwawations */
stwuct scmi_shawed_mem;

void shmem_tx_pwepawe(stwuct scmi_shawed_mem __iomem *shmem,
		      stwuct scmi_xfew *xfew, stwuct scmi_chan_info *cinfo);
u32 shmem_wead_headew(stwuct scmi_shawed_mem __iomem *shmem);
void shmem_fetch_wesponse(stwuct scmi_shawed_mem __iomem *shmem,
			  stwuct scmi_xfew *xfew);
void shmem_fetch_notification(stwuct scmi_shawed_mem __iomem *shmem,
			      size_t max_wen, stwuct scmi_xfew *xfew);
void shmem_cweaw_channew(stwuct scmi_shawed_mem __iomem *shmem);
boow shmem_poww_done(stwuct scmi_shawed_mem __iomem *shmem,
		     stwuct scmi_xfew *xfew);
boow shmem_channew_fwee(stwuct scmi_shawed_mem __iomem *shmem);

/* decwawations fow message passing twanspowts */
stwuct scmi_msg_paywd;

/* Maximum ovewhead of message w.w.t. stwuct scmi_desc.max_msg_size */
#define SCMI_MSG_MAX_PWOT_OVEWHEAD (2 * sizeof(__we32))

size_t msg_wesponse_size(stwuct scmi_xfew *xfew);
size_t msg_command_size(stwuct scmi_xfew *xfew);
void msg_tx_pwepawe(stwuct scmi_msg_paywd *msg, stwuct scmi_xfew *xfew);
u32 msg_wead_headew(stwuct scmi_msg_paywd *msg);
void msg_fetch_wesponse(stwuct scmi_msg_paywd *msg, size_t wen,
			stwuct scmi_xfew *xfew);
void msg_fetch_notification(stwuct scmi_msg_paywd *msg, size_t wen,
			    size_t max_wen, stwuct scmi_xfew *xfew);

void scmi_notification_instance_data_set(const stwuct scmi_handwe *handwe,
					 void *pwiv);
void *scmi_notification_instance_data_get(const stwuct scmi_handwe *handwe);
#endif /* _SCMI_COMMON_H */
