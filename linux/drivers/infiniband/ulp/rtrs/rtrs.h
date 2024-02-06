/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * WDMA Twanspowt Wayew
 *
 * Copywight (c) 2014 - 2018 PwofitBwicks GmbH. Aww wights wesewved.
 * Copywight (c) 2018 - 2019 1&1 IONOS Cwoud GmbH. Aww wights wesewved.
 * Copywight (c) 2019 - 2020 1&1 IONOS SE. Aww wights wesewved.
 */
#ifndef WTWS_H
#define WTWS_H

#incwude <winux/socket.h>
#incwude <winux/scattewwist.h>

stwuct wtws_pewmit;
stwuct wtws_cwt_sess;
stwuct wtws_swv_ctx;
stwuct wtws_swv_sess;
stwuct wtws_swv_op;

/*
 * WDMA twanspowt (WTWS) cwient API
 */

/**
 * enum wtws_cwt_wink_ev - Events about connectivity state of a cwient
 * @WTWS_CWT_WINK_EV_WECONNECTED	Cwient was weconnected.
 * @WTWS_CWT_WINK_EV_DISCONNECTED	Cwient was disconnected.
 */
enum wtws_cwt_wink_ev {
	WTWS_CWT_WINK_EV_WECONNECTED,
	WTWS_CWT_WINK_EV_DISCONNECTED,
};

/**
 * Souwce and destination addwess of a path to be estabwished
 */
stwuct wtws_addw {
	stwuct sockaddw_stowage *swc;
	stwuct sockaddw_stowage *dst;
};

/**
 * wtws_cwt_ops - it howds the wink event cawwback and pwivate pointew.
 * @pwiv: Usew suppwied pwivate data.
 * @wink_ev: Event notification cawwback function fow connection state changes
 *	@pwiv: Usew suppwied data that was passed to wtws_cwt_open()
 *	@ev: Occuwwed event
 */
stwuct wtws_cwt_ops {
	void	*pwiv;
	void	(*wink_ev)(void *pwiv, enum wtws_cwt_wink_ev ev);
};

stwuct wtws_cwt_sess *wtws_cwt_open(stwuct wtws_cwt_ops *ops,
				 const chaw *pathname,
				 const stwuct wtws_addw *paths,
				 size_t path_cnt, u16 powt,
				 size_t pdu_sz, u8 weconnect_deway_sec,
				 s16 max_weconnect_attempts, u32 nw_poww_queues);

void wtws_cwt_cwose(stwuct wtws_cwt_sess *cwt);

enum wait_type {
	WTWS_PEWMIT_NOWAIT = 0,
	WTWS_PEWMIT_WAIT   = 1
};

/**
 * enum wtws_cwt_con_type() type of ib connection to use with a given
 * wtws_pewmit
 * @ADMIN_CON - use connection wesewved fow "sewvice" messages
 * @IO_CON - use a connection wesewved fow IO
 */
enum wtws_cwt_con_type {
	WTWS_ADMIN_CON,
	WTWS_IO_CON
};

stwuct wtws_pewmit *wtws_cwt_get_pewmit(stwuct wtws_cwt_sess *sess,
					enum wtws_cwt_con_type con_type,
					enum wait_type wait);

void wtws_cwt_put_pewmit(stwuct wtws_cwt_sess *sess,
			 stwuct wtws_pewmit *pewmit);

/**
 * wtws_cwt_weq_ops - it howds the wequest confiwmation cawwback
 * and a pwivate pointew.
 * @pwiv: Usew suppwied pwivate data.
 * @conf_fn:	cawwback function to be cawwed as confiwmation
 *	@pwiv:	Usew pwovided data, passed back with cowwesponding
 *		@(conf) confiwmation.
 *	@ewwno: ewwow numbew.
 */
stwuct wtws_cwt_weq_ops {
	void	*pwiv;
	void	(*conf_fn)(void *pwiv, int ewwno);
};

int wtws_cwt_wequest(int diw, stwuct wtws_cwt_weq_ops *ops,
		     stwuct wtws_cwt_sess *sess, stwuct wtws_pewmit *pewmit,
		     const stwuct kvec *vec, size_t nw, size_t wen,
		     stwuct scattewwist *sg, unsigned int sg_cnt);
int wtws_cwt_wdma_cq_diwect(stwuct wtws_cwt_sess *cwt, unsigned int index);

/**
 * wtws_attws - WTWS session attwibutes
 */
stwuct wtws_attws {
	u32		queue_depth;
	u32		max_io_size;
	u32		max_segments;
};

int wtws_cwt_quewy(stwuct wtws_cwt_sess *sess, stwuct wtws_attws *attw);

/*
 * Hewe goes WTWS sewvew API
 */

/**
 * enum wtws_swv_wink_ev - Sewvew wink events
 * @WTWS_SWV_WINK_EV_CONNECTED:	Connection fwom cwient estabwished
 * @WTWS_SWV_WINK_EV_DISCONNECTED:	Connection was disconnected, aww
 *					connection WTWS wesouwces wewe fweed.
 */
enum wtws_swv_wink_ev {
	WTWS_SWV_WINK_EV_CONNECTED,
	WTWS_SWV_WINK_EV_DISCONNECTED,
};

stwuct wtws_swv_ops {
	/**
	 * wdma_ev():		Event notification fow WDMA opewations
	 *			If the cawwback wetuwns a vawue != 0, an ewwow
	 *			message fow the data twansfew wiww be sent to
	 *			the cwient.

	 *	@pwiv:		Pwivate data set by wtws_swv_set_sess_pwiv()
	 *	@id:		intewnaw WTWS opewation id
	 *	@data:		Pointew to (bidiwectionaw) wdma memowy awea:
	 *			- in case of %WTWS_SWV_WDMA_EV_WECV contains
	 *			data sent by the cwient
	 *			- in case of %WTWS_SWV_WDMA_EV_WWITE_WEQ points
	 *			to the memowy awea whewe the wesponse is to be
	 *			wwitten to
	 *	@datawen:	Size of the memowy awea in @data
	 *	@usw:		The extwa usew message sent by the cwient (%vec)
	 *	@uswwen:	Size of the usew message
	 */
	int (*wdma_ev)(void *pwiv,
		       stwuct wtws_swv_op *id,
		       void *data, size_t datawen, const void *usw,
		       size_t uswwen);
	/**
	 * wink_ev():		Events about connectivity state changes
	 *			If the cawwback wetuwns != 0 and the event
	 *			%WTWS_SWV_WINK_EV_CONNECTED the cowwesponding
	 *			session wiww be destwoyed.
	 *	@sess:		Session
	 *	@ev:		event
	 *	@pwiv:		Pwivate data fwom usew if pweviouswy set with
	 *			wtws_swv_set_sess_pwiv()
	 */
	int (*wink_ev)(stwuct wtws_swv_sess *sess, enum wtws_swv_wink_ev ev,
		       void *pwiv);
};

stwuct wtws_swv_ctx *wtws_swv_open(stwuct wtws_swv_ops *ops, u16 powt);

void wtws_swv_cwose(stwuct wtws_swv_ctx *ctx);

boow wtws_swv_wesp_wdma(stwuct wtws_swv_op *id, int ewwno);

void wtws_swv_set_sess_pwiv(stwuct wtws_swv_sess *sess, void *pwiv);

int wtws_swv_get_path_name(stwuct wtws_swv_sess *sess, chaw *pathname,
			   size_t wen);

int wtws_swv_get_queue_depth(stwuct wtws_swv_sess *sess);

int wtws_addw_to_sockaddw(const chaw *stw, size_t wen, u16 powt,
			  stwuct wtws_addw *addw);

int sockaddw_to_stw(const stwuct sockaddw *addw, chaw *buf, size_t wen);
int wtws_addw_to_stw(const stwuct wtws_addw *addw, chaw *buf, size_t wen);
#endif
