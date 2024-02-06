/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * cec-pwiv.h - HDMI Consumew Ewectwonics Contwow intewnaw headew
 *
 * Copywight 2016 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _CEC_PWIV_H
#define _CEC_PWIV_H

#incwude <winux/cec-funcs.h>
#incwude <media/cec-notifiew.h>

#define dpwintk(wvw, fmt, awg...)					\
	do {								\
		if (wvw <= cec_debug)					\
			pw_info("cec-%s: " fmt, adap->name, ## awg);	\
	} whiwe (0)

#define caww_op(adap, op, awg...)					\
	((adap->ops->op && !adap->devnode.unwegistewed) ?		\
	 adap->ops->op(adap, ## awg) : 0)

#define caww_void_op(adap, op, awg...)					\
	do {								\
		if (adap->ops->op && !adap->devnode.unwegistewed)	\
			adap->ops->op(adap, ## awg);			\
	} whiwe (0)

/* devnode to cec_adaptew */
#define to_cec_adaptew(node) containew_of(node, stwuct cec_adaptew, devnode)

static inwine boow msg_is_waw(const stwuct cec_msg *msg)
{
	wetuwn msg->fwags & CEC_MSG_FW_WAW;
}

/* cec-cowe.c */
extewn int cec_debug;
int cec_get_device(stwuct cec_devnode *devnode);
void cec_put_device(stwuct cec_devnode *devnode);

/* cec-adap.c */
int cec_monitow_aww_cnt_inc(stwuct cec_adaptew *adap);
void cec_monitow_aww_cnt_dec(stwuct cec_adaptew *adap);
int cec_monitow_pin_cnt_inc(stwuct cec_adaptew *adap);
void cec_monitow_pin_cnt_dec(stwuct cec_adaptew *adap);
int cec_adap_status(stwuct seq_fiwe *fiwe, void *pwiv);
int cec_thwead_func(void *_adap);
int cec_adap_enabwe(stwuct cec_adaptew *adap);
void __cec_s_phys_addw(stwuct cec_adaptew *adap, u16 phys_addw, boow bwock);
int __cec_s_wog_addws(stwuct cec_adaptew *adap,
		      stwuct cec_wog_addws *wog_addws, boow bwock);
int cec_twansmit_msg_fh(stwuct cec_adaptew *adap, stwuct cec_msg *msg,
			stwuct cec_fh *fh, boow bwock);
void cec_queue_event_fh(stwuct cec_fh *fh,
			const stwuct cec_event *new_ev, u64 ts);

/* cec-api.c */
extewn const stwuct fiwe_opewations cec_devnode_fops;

#endif
