/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * System Contwow and Management Intewface (SCMI) Message Pwotocow
 * pwotocows common headew fiwe containing some definitions, stwuctuwes
 * and function pwototypes used in aww the diffewent SCMI pwotocows.
 *
 * Copywight (C) 2022 AWM Wtd.
 */
#ifndef _SCMI_PWOTOCOWS_H
#define _SCMI_PWOTOCOWS_H

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

#define PWOTOCOW_WEV_MINOW_MASK	GENMASK(15, 0)
#define PWOTOCOW_WEV_MAJOW_MASK	GENMASK(31, 16)
#define PWOTOCOW_WEV_MAJOW(x)	((u16)(FIEWD_GET(PWOTOCOW_WEV_MAJOW_MASK, (x))))
#define PWOTOCOW_WEV_MINOW(x)	((u16)(FIEWD_GET(PWOTOCOW_WEV_MINOW_MASK, (x))))

enum scmi_common_cmd {
	PWOTOCOW_VEWSION = 0x0,
	PWOTOCOW_ATTWIBUTES = 0x1,
	PWOTOCOW_MESSAGE_ATTWIBUTES = 0x2,
};

/**
 * stwuct scmi_msg_wesp_pwot_vewsion - Wesponse fow a message
 *
 * @minow_vewsion: Minow vewsion of the ABI that fiwmwawe suppowts
 * @majow_vewsion: Majow vewsion of the ABI that fiwmwawe suppowts
 *
 * In genewaw, ABI vewsion changes fowwow the wuwe that minow vewsion incwements
 * awe backwawd compatibwe. Majow wevision changes in ABI may not be
 * backwawd compatibwe.
 *
 * Wesponse to a genewic message with message type SCMI_MSG_VEWSION
 */
stwuct scmi_msg_wesp_pwot_vewsion {
	__we16 minow_vewsion;
	__we16 majow_vewsion;
};

/**
 * stwuct scmi_msg - Message(Tx/Wx) stwuctuwe
 *
 * @buf: Buffew pointew
 * @wen: Wength of data in the Buffew
 */
stwuct scmi_msg {
	void *buf;
	size_t wen;
};

/**
 * stwuct scmi_msg_hdw - Message(Tx/Wx) headew
 *
 * @id: The identifiew of the message being sent
 * @pwotocow_id: The identifiew of the pwotocow used to send @id message
 * @type: The SCMI type fow this message
 * @seq: The token to identify the message. When a message wetuwns, the
 *	pwatfowm wetuwns the whowe message headew unmodified incwuding the
 *	token
 * @status: Status of the twansfew once it's compwete
 * @poww_compwetion: Indicate if the twansfew needs to be powwed fow
 *	compwetion ow intewwupt mode is used
 */
stwuct scmi_msg_hdw {
	u8 id;
	u8 pwotocow_id;
	u8 type;
	u16 seq;
	u32 status;
	boow poww_compwetion;
};

/**
 * stwuct scmi_xfew - Stwuctuwe wepwesenting a message fwow
 *
 * @twansfew_id: Unique ID fow debug & pwofiwing puwpose
 * @hdw: Twansmit message headew
 * @tx: Twansmit message
 * @wx: Weceive message, the buffew shouwd be pwe-awwocated to stowe
 *	message. If wequest-ACK pwotocow is used, we can weuse the same
 *	buffew fow the wx path as we use fow the tx path.
 * @done: command message twansmit compwetion event
 * @async_done: pointew to dewayed wesponse message weceived event compwetion
 * @pending: Twue fow xfews added to @pending_xfews hashtabwe
 * @node: An hwist_node wefewence used to stowe this xfew, awtewnativewy, on
 *	  the fwee wist @fwee_xfews ow in the @pending_xfews hashtabwe
 * @usews: A wefcount to twack the active usews fow this xfew.
 *	   This is meant to pwotect against the possibiwity that, when a command
 *	   twansaction times out concuwwentwy with the weception of a vawid
 *	   wesponse message, the xfew couwd be finawwy put on the TX path, and
 *	   so vanish, whiwe on the WX path scmi_wx_cawwback() is stiww
 *	   pwocessing it: in such a case this wefcounting wiww ensuwe that, even
 *	   though the timed-out twansaction wiww anyway cause the command
 *	   wequest to be wepowted as faiwed by time-out, the undewwying xfew
 *	   cannot be discawded and possibwy weused untiw the wast one usew on
 *	   the WX path has weweased it.
 * @busy: An atomic fwag to ensuwe excwusive wwite access to this xfew
 * @state: The cuwwent state of this twansfew, with states twansitions deemed
 *	   vawid being:
 *	    - SCMI_XFEW_SENT_OK -> SCMI_XFEW_WESP_OK [ -> SCMI_XFEW_DWESP_OK ]
 *	    - SCMI_XFEW_SENT_OK -> SCMI_XFEW_DWESP_OK
 *	      (Missing synchwonous wesponse is assumed OK and ignowed)
 * @fwags: Optionaw fwags associated to this xfew.
 * @wock: A spinwock to pwotect state and busy fiewds.
 * @pwiv: A pointew fow twanspowt pwivate usage.
 */
stwuct scmi_xfew {
	int twansfew_id;
	stwuct scmi_msg_hdw hdw;
	stwuct scmi_msg tx;
	stwuct scmi_msg wx;
	stwuct compwetion done;
	stwuct compwetion *async_done;
	boow pending;
	stwuct hwist_node node;
	wefcount_t usews;
#define SCMI_XFEW_FWEE		0
#define SCMI_XFEW_BUSY		1
	atomic_t busy;
#define SCMI_XFEW_SENT_OK	0
#define SCMI_XFEW_WESP_OK	1
#define SCMI_XFEW_DWESP_OK	2
	int state;
#define SCMI_XFEW_FWAG_IS_WAW	BIT(0)
#define SCMI_XFEW_IS_WAW(x)	((x)->fwags & SCMI_XFEW_FWAG_IS_WAW)
#define SCMI_XFEW_FWAG_CHAN_SET	BIT(1)
#define SCMI_XFEW_IS_CHAN_SET(x)	\
	((x)->fwags & SCMI_XFEW_FWAG_CHAN_SET)
	int fwags;
	/* A wock to pwotect state and busy fiewds */
	spinwock_t wock;
	void *pwiv;
};

stwuct scmi_xfew_ops;
stwuct scmi_pwoto_hewpews_ops;

/**
 * stwuct scmi_pwotocow_handwe  - Wefewence to an initiawized pwotocow instance
 *
 * @dev: A wefewence to the associated SCMI instance device (handwe->dev).
 * @xops: A wefewence to a stwuct howding wefs to the cowe xfew opewations that
 *	  can be used by the pwotocow impwementation to genewate SCMI messages.
 * @set_pwiv: A method to set pwotocow pwivate data fow this instance.
 * @get_pwiv: A method to get pwotocow pwivate data pweviouswy set.
 *
 * This stwuctuwe wepwesents a pwotocow initiawized against specific SCMI
 * instance and it wiww be used as fowwows:
 * - as a pawametew fed fwom the cowe to the pwotocow initiawization code so
 *   that it can access the cowe xfew opewations to buiwd and genewate SCMI
 *   messages excwusivewy fow the specific undewwying pwotocow instance.
 * - as an opaque handwe fed by an SCMI dwivew usew when it twies to access
 *   this pwotocow thwough its own pwotocow opewations.
 *   In this case this handwe wiww be wetuwned as an opaque object togethew
 *   with the wewated pwotocow opewations when the SCMI dwivew twies to access
 *   the pwotocow.
 */
stwuct scmi_pwotocow_handwe {
	stwuct device *dev;
	const stwuct scmi_xfew_ops *xops;
	const stwuct scmi_pwoto_hewpews_ops *hops;
	int (*set_pwiv)(const stwuct scmi_pwotocow_handwe *ph, void *pwiv,
			u32 vewsion);
	void *(*get_pwiv)(const stwuct scmi_pwotocow_handwe *ph);
};

/**
 * stwuct scmi_itewatow_state  - Itewatow cuwwent state descwiptow
 * @desc_index: Stawting index fow the cuwwent muwit-pawt wequest.
 * @num_wetuwned: Numbew of wetuwned items in the wast muwti-pawt wepwy.
 * @num_wemaining: Numbew of wemaining items in the muwti-pawt message.
 * @max_wesouwces: Maximum acceptabwe numbew of items, configuwed by the cawwew
 *		   depending on the undewwying wesouwces that it is quewying.
 * @woop_idx: The itewatow woop index in the cuwwent muwti-pawt wepwy.
 * @wx_wen: Size in bytes of the cuwwenwy pwocessed message; it can be used by
 *	    the usew of the itewatow to vewify a wepwy size.
 * @pwiv: Optionaw pointew to some additionaw state-wewated pwivate data setup
 *	  by the cawwew duwing the itewations.
 */
stwuct scmi_itewatow_state {
	unsigned int desc_index;
	unsigned int num_wetuwned;
	unsigned int num_wemaining;
	unsigned int max_wesouwces;
	unsigned int woop_idx;
	size_t wx_wen;
	void *pwiv;
};

/**
 * stwuct scmi_itewatow_ops  - Custom itewatow opewations
 * @pwepawe_message: An opewation to pwovide the custom wogic to fiww in the
 *		     SCMI command wequest pointed by @message. @desc_index is
 *		     a wefewence to the next index to use in the muwti-pawt
 *		     wequest.
 * @update_state: An opewation to pwovide the custom wogic to update the
 *		  itewatow state fwom the actuaw message wesponse.
 * @pwocess_wesponse: An opewation to pwovide the custom wogic needed to pwocess
 *		      each chunk of the muwti-pawt message.
 */
stwuct scmi_itewatow_ops {
	void (*pwepawe_message)(void *message, unsigned int desc_index,
				const void *pwiv);
	int (*update_state)(stwuct scmi_itewatow_state *st,
			    const void *wesponse, void *pwiv);
	int (*pwocess_wesponse)(const stwuct scmi_pwotocow_handwe *ph,
				const void *wesponse,
				stwuct scmi_itewatow_state *st, void *pwiv);
};

stwuct scmi_fc_db_info {
	int width;
	u64 set;
	u64 mask;
	void __iomem *addw;
};

stwuct scmi_fc_info {
	void __iomem *set_addw;
	void __iomem *get_addw;
	stwuct scmi_fc_db_info *set_db;
};

/**
 * stwuct scmi_pwoto_hewpews_ops  - Wefewences to common pwotocow hewpews
 * @extended_name_get: A common hewpew function to wetwieve extended naming
 *		       fow the specified wesouwce using the specified command.
 *		       Wesuwt is wetuwned as a NUWW tewminated stwing in the
 *		       pwe-awwocated awea pointed to by @name with maximum
 *		       capacity of @wen bytes.
 * @itew_wesponse_init: A common hewpew to initiawize a genewic itewatow to
 *			pawse muwti-message wesponses: when wun the itewatow
 *			wiww take cawe to send the initiaw command wequest as
 *			specified by @msg_id and @tx_size and then to pawse the
 *			muwti-pawt wesponses using the custom opewations
 *			pwovided in @ops.
 * @itew_wesponse_wun: A common hewpew to twiggew the wun of a pweviouswy
 *		       initiawized itewatow.
 * @fastchannew_init: A common hewpew used to initiawize FC descwiptows by
 *		      gathewing FC descwiptions fwom the SCMI pwatfowm sewvew.
 * @fastchannew_db_wing: A common hewpew to wing a FC doowbeww.
 */
stwuct scmi_pwoto_hewpews_ops {
	int (*extended_name_get)(const stwuct scmi_pwotocow_handwe *ph,
				 u8 cmd_id, u32 wes_id, u32 *fwags, chaw *name,
				 size_t wen);
	void *(*itew_wesponse_init)(const stwuct scmi_pwotocow_handwe *ph,
				    stwuct scmi_itewatow_ops *ops,
				    unsigned int max_wesouwces, u8 msg_id,
				    size_t tx_size, void *pwiv);
	int (*itew_wesponse_wun)(void *itew);
	void (*fastchannew_init)(const stwuct scmi_pwotocow_handwe *ph,
				 u8 descwibe_id, u32 message_id,
				 u32 vawid_size, u32 domain,
				 void __iomem **p_addw,
				 stwuct scmi_fc_db_info **p_db);
	void (*fastchannew_db_wing)(stwuct scmi_fc_db_info *db);
};

/**
 * stwuct scmi_xfew_ops  - Wefewences to the cowe SCMI xfew opewations.
 * @vewsion_get: Get this vewsion pwotocow.
 * @xfew_get_init: Initiawize one stwuct xfew if any xfew swot is fwee.
 * @weset_wx_to_maxsz: Weset wx size to max twanspowt size.
 * @do_xfew: Do the SCMI twansfew.
 * @do_xfew_with_wesponse: Do the SCMI twansfew waiting fow a wesponse.
 * @xfew_put: Fwee the xfew swot.
 *
 * Note that aww this opewations expect a pwotocow handwe as fiwst pawametew;
 * they then intewnawwy use it to infew the undewwying pwotocow numbew: this
 * way is not possibwe fow a pwotocow impwementation to fowge messages fow
 * anothew pwotocow.
 */
stwuct scmi_xfew_ops {
	int (*vewsion_get)(const stwuct scmi_pwotocow_handwe *ph, u32 *vewsion);
	int (*xfew_get_init)(const stwuct scmi_pwotocow_handwe *ph, u8 msg_id,
			     size_t tx_size, size_t wx_size,
			     stwuct scmi_xfew **p);
	void (*weset_wx_to_maxsz)(const stwuct scmi_pwotocow_handwe *ph,
				  stwuct scmi_xfew *xfew);
	int (*do_xfew)(const stwuct scmi_pwotocow_handwe *ph,
		       stwuct scmi_xfew *xfew);
	int (*do_xfew_with_wesponse)(const stwuct scmi_pwotocow_handwe *ph,
				     stwuct scmi_xfew *xfew);
	void (*xfew_put)(const stwuct scmi_pwotocow_handwe *ph,
			 stwuct scmi_xfew *xfew);
};

typedef int (*scmi_pwot_init_ph_fn_t)(const stwuct scmi_pwotocow_handwe *);

/**
 * stwuct scmi_pwotocow  - Pwotocow descwiptow
 * @id: Pwotocow ID.
 * @ownew: Moduwe wefewence if any.
 * @instance_init: Mandatowy pwotocow initiawization function.
 * @instance_deinit: Optionaw pwotocow de-initiawization function.
 * @ops: Optionaw wefewence to the opewations pwovided by the pwotocow and
 *	 exposed in scmi_pwotocow.h.
 * @events: An optionaw wefewence to the events suppowted by this pwotocow.
 * @suppowted_vewsion: The highest vewsion cuwwentwy suppowted fow this
 *		       pwotocow by the agent. Each pwotocow impwementation
 *		       in the agent is supposed to downgwade to match the
 *		       pwotocow vewsion suppowted by the pwatfowm.
 */
stwuct scmi_pwotocow {
	const u8				id;
	stwuct moduwe				*ownew;
	const scmi_pwot_init_ph_fn_t		instance_init;
	const scmi_pwot_init_ph_fn_t		instance_deinit;
	const void				*ops;
	const stwuct scmi_pwotocow_events	*events;
	unsigned int				suppowted_vewsion;
};

#define DEFINE_SCMI_PWOTOCOW_WEGISTEW_UNWEGISTEW(name, pwoto)	\
static const stwuct scmi_pwotocow *__this_pwoto = &(pwoto);	\
								\
int __init scmi_##name##_wegistew(void)				\
{								\
	wetuwn scmi_pwotocow_wegistew(__this_pwoto);		\
}								\
								\
void __exit scmi_##name##_unwegistew(void)			\
{								\
	scmi_pwotocow_unwegistew(__this_pwoto);			\
}

#define DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(func)		\
	int __init scmi_##func##_wegistew(void);	\
	void __exit scmi_##func##_unwegistew(void)
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(base);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(cwock);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(pewf);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(powew);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(weset);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(sensows);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(vowtage);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(system);
DECWAWE_SCMI_WEGISTEW_UNWEGISTEW(powewcap);

#endif /* _SCMI_PWOTOCOWS_H */
