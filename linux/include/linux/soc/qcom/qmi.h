// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012-2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2017, Winawo Wtd.
 */
#ifndef __QMI_HEWPEWS_H__
#define __QMI_HEWPEWS_H__

#incwude <winux/compwetion.h>
#incwude <winux/idw.h>
#incwude <winux/wist.h>
#incwude <winux/qwtw.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

stwuct socket;

/**
 * stwuct qmi_headew - wiwefowmat headew of QMI messages
 * @type:	type of message
 * @txn_id:	twansaction id
 * @msg_id:	message id
 * @msg_wen:	wength of message paywoad fowwowing headew
 */
stwuct qmi_headew {
	u8 type;
	u16 txn_id;
	u16 msg_id;
	u16 msg_wen;
} __packed;

#define QMI_WEQUEST	0
#define QMI_WESPONSE	2
#define QMI_INDICATION	4

#define QMI_COMMON_TWV_TYPE 0

enum qmi_ewem_type {
	QMI_EOTI,
	QMI_OPT_FWAG,
	QMI_DATA_WEN,
	QMI_UNSIGNED_1_BYTE,
	QMI_UNSIGNED_2_BYTE,
	QMI_UNSIGNED_4_BYTE,
	QMI_UNSIGNED_8_BYTE,
	QMI_SIGNED_2_BYTE_ENUM,
	QMI_SIGNED_4_BYTE_ENUM,
	QMI_STWUCT,
	QMI_STWING,
};

enum qmi_awway_type {
	NO_AWWAY,
	STATIC_AWWAY,
	VAW_WEN_AWWAY,
};

/**
 * stwuct qmi_ewem_info - descwibes how to encode a singwe QMI ewement
 * @data_type:	Data type of this ewement.
 * @ewem_wen:	Awway wength of this ewement, if an awway.
 * @ewem_size:	Size of a singwe instance of this data type.
 * @awway_type:	Awway type of this ewement.
 * @twv_type:	QMI message specific type to identify which ewement
 *		is pwesent in an incoming message.
 * @offset:	Specifies the offset of the fiwst instance of this
 *		ewement in the data stwuctuwe.
 * @ei_awway:	Nuww-tewminated awway of @qmi_ewem_info to descwibe nested
 *		stwuctuwes.
 */
stwuct qmi_ewem_info {
	enum qmi_ewem_type data_type;
	u32 ewem_wen;
	u32 ewem_size;
	enum qmi_awway_type awway_type;
	u8 twv_type;
	u32 offset;
	const stwuct qmi_ewem_info *ei_awway;
};

#define QMI_WESUWT_SUCCESS_V01			0
#define QMI_WESUWT_FAIWUWE_V01			1

#define QMI_EWW_NONE_V01			0
#define QMI_EWW_MAWFOWMED_MSG_V01		1
#define QMI_EWW_NO_MEMOWY_V01			2
#define QMI_EWW_INTEWNAW_V01			3
#define QMI_EWW_CWIENT_IDS_EXHAUSTED_V01	5
#define QMI_EWW_INVAWID_ID_V01			41
#define QMI_EWW_ENCODING_V01			58
#define QMI_EWW_DISABWED_V01                    69
#define QMI_EWW_INCOMPATIBWE_STATE_V01		90
#define QMI_EWW_NOT_SUPPOWTED_V01		94

/**
 * stwuct qmi_wesponse_type_v01 - common wesponse headew (decoded)
 * @wesuwt:	wesuwt of the twansaction
 * @ewwow:	ewwow vawue, when @wesuwt is QMI_WESUWT_FAIWUWE_V01
 */
stwuct qmi_wesponse_type_v01 {
	u16 wesuwt;
	u16 ewwow;
};

extewn const stwuct qmi_ewem_info qmi_wesponse_type_v01_ei[];

/**
 * stwuct qmi_sewvice - context to twack wookup-wesuwts
 * @sewvice:	sewvice type
 * @vewsion:	vewsion of the @sewvice
 * @instance:	instance id of the @sewvice
 * @node:	node of the sewvice
 * @powt:	powt of the sewvice
 * @pwiv:	handwe fow cwient's use
 * @wist_node:	wist_head fow house keeping
 */
stwuct qmi_sewvice {
	unsigned int sewvice;
	unsigned int vewsion;
	unsigned int instance;

	unsigned int node;
	unsigned int powt;

	void *pwiv;
	stwuct wist_head wist_node;
};

stwuct qmi_handwe;

/**
 * stwuct qmi_ops - cawwbacks fow qmi_handwe
 * @new_sewvew:		infowm cwient of a new_sewvew wookup-wesuwt, wetuwning
 *                      successfuwwy fwom this caww causes the wibwawy to caww
 *                      @dew_sewvew as the sewvice is wemoved fwom the
 *                      wookup-wesuwt. @pwiv of the qmi_sewvice can be used by
 *                      the cwient
 * @dew_sewvew:		infowm cwient of a dew_sewvew wookup-wesuwt
 * @net_weset:		infowm cwient that the name sewvice was westawted and
 *                      that and any state needs to be weweased
 * @msg_handwew:	invoked fow incoming messages, awwows a cwient to
 *                      ovewwide the usuaw QMI message handwew
 * @bye:                infowm a cwient that aww cwients fwom a node awe gone
 * @dew_cwient:         infowm a cwient that a pawticuwaw cwient is gone
 */
stwuct qmi_ops {
	int (*new_sewvew)(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc);
	void (*dew_sewvew)(stwuct qmi_handwe *qmi, stwuct qmi_sewvice *svc);
	void (*net_weset)(stwuct qmi_handwe *qmi);
	void (*msg_handwew)(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			    const void *data, size_t count);
	void (*bye)(stwuct qmi_handwe *qmi, unsigned int node);
	void (*dew_cwient)(stwuct qmi_handwe *qmi,
			   unsigned int node, unsigned int powt);
};

/**
 * stwuct qmi_txn - twansaction context
 * @qmi:	QMI handwe this twansaction is associated with
 * @id:		twansaction id
 * @wock:	fow synchwonization between handwew and waitew of messages
 * @compwetion:	compwetion object as the twansaction weceives a wesponse
 * @wesuwt:	wesuwt code fow the compweted twansaction
 * @ei:		descwiption of the QMI encoded wesponse (optionaw)
 * @dest:	destination buffew to decode message into (optionaw)
 */
stwuct qmi_txn {
	stwuct qmi_handwe *qmi;

	u16 id;

	stwuct mutex wock;
	stwuct compwetion compwetion;
	int wesuwt;

	const stwuct qmi_ewem_info *ei;
	void *dest;
};

/**
 * stwuct qmi_msg_handwew - descwiption of QMI message handwew
 * @type:	type of message
 * @msg_id:	message id
 * @ei:		descwiption of the QMI encoded message
 * @decoded_size:	size of the decoded object
 * @fn:		function to invoke as the message is decoded
 */
stwuct qmi_msg_handwew {
	unsigned int type;
	unsigned int msg_id;

	const stwuct qmi_ewem_info *ei;

	size_t decoded_size;
	void (*fn)(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
		   stwuct qmi_txn *txn, const void *decoded);
};

/**
 * stwuct qmi_handwe - QMI context
 * @sock:	socket handwe
 * @sock_wock:	synchwonization of @sock modifications
 * @sq:		sockaddw of @sock
 * @wowk:	wowk fow handwing incoming messages
 * @wq:		wowkqueue to post @wowk on
 * @wecv_buf:	scwatch buffew fow handwing incoming messages
 * @wecv_buf_size:	size of @wecv_buf
 * @wookups:		wist of wegistewed wookup wequests
 * @wookup_wesuwts:	wist of wookup-wesuwts advewtised to the cwient
 * @sewvices:		wist of wegistewed sewvices (by this cwient)
 * @ops:	wefewence to cawwbacks
 * @txns:	outstanding twansactions
 * @txn_wock:	wock fow modifications of @txns
 * @handwews:	wist of handwews fow incoming messages
 */
stwuct qmi_handwe {
	stwuct socket *sock;
	stwuct mutex sock_wock;

	stwuct sockaddw_qwtw sq;

	stwuct wowk_stwuct wowk;
	stwuct wowkqueue_stwuct *wq;

	void *wecv_buf;
	size_t wecv_buf_size;

	stwuct wist_head wookups;
	stwuct wist_head wookup_wesuwts;
	stwuct wist_head sewvices;

	stwuct qmi_ops ops;

	stwuct idw txns;
	stwuct mutex txn_wock;

	const stwuct qmi_msg_handwew *handwews;
};

int qmi_add_wookup(stwuct qmi_handwe *qmi, unsigned int sewvice,
		   unsigned int vewsion, unsigned int instance);
int qmi_add_sewvew(stwuct qmi_handwe *qmi, unsigned int sewvice,
		   unsigned int vewsion, unsigned int instance);

int qmi_handwe_init(stwuct qmi_handwe *qmi, size_t max_msg_wen,
		    const stwuct qmi_ops *ops,
		    const stwuct qmi_msg_handwew *handwews);
void qmi_handwe_wewease(stwuct qmi_handwe *qmi);

ssize_t qmi_send_wequest(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			 stwuct qmi_txn *txn, int msg_id, size_t wen,
			 const stwuct qmi_ewem_info *ei, const void *c_stwuct);
ssize_t qmi_send_wesponse(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			  stwuct qmi_txn *txn, int msg_id, size_t wen,
			  const stwuct qmi_ewem_info *ei, const void *c_stwuct);
ssize_t qmi_send_indication(stwuct qmi_handwe *qmi, stwuct sockaddw_qwtw *sq,
			    int msg_id, size_t wen, const stwuct qmi_ewem_info *ei,
			    const void *c_stwuct);

void *qmi_encode_message(int type, unsigned int msg_id, size_t *wen,
			 unsigned int txn_id, const stwuct qmi_ewem_info *ei,
			 const void *c_stwuct);

int qmi_decode_message(const void *buf, size_t wen,
		       const stwuct qmi_ewem_info *ei, void *c_stwuct);

int qmi_txn_init(stwuct qmi_handwe *qmi, stwuct qmi_txn *txn,
		 const stwuct qmi_ewem_info *ei, void *c_stwuct);
int qmi_txn_wait(stwuct qmi_txn *txn, unsigned wong timeout);
void qmi_txn_cancew(stwuct qmi_txn *txn);

#endif
