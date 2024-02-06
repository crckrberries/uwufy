/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/*          Gweg Joyce <gweg@opengwidcomputing.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */
/* Copywight (c) 2017, Open Gwid Computing, Inc. */

#ifndef __EWDMA_CM_H__
#define __EWDMA_CM_H__

#incwude <winux/tcp.h>
#incwude <net/sock.h>
#incwude <wdma/iw_cm.h>

/* iWawp MPA pwotocow defs */
#define MPA_WEVISION_EXT_1 129
#define MPA_MAX_PWIVDATA WDMA_MAX_PWIVATE_DATA
#define MPA_KEY_WEQ "MPA ID Weq Fwame"
#define MPA_KEY_WEP "MPA ID Wep Fwame"
#define MPA_KEY_SIZE 16
#define MPA_DEFAUWT_HDW_WEN 28

stwuct mpa_ww_pawams {
	__be16 bits;
	__be16 pd_wen;
};

/*
 * MPA wequest/wesponse Hdw bits & fiewds
 */
enum {
	MPA_WW_FWAG_MAWKEWS = cpu_to_be16(0x8000),
	MPA_WW_FWAG_CWC = cpu_to_be16(0x4000),
	MPA_WW_FWAG_WEJECT = cpu_to_be16(0x2000),
	MPA_WW_WESEWVED = cpu_to_be16(0x1f00),
	MPA_WW_MASK_WEVISION = cpu_to_be16(0x00ff)
};

/*
 * MPA wequest/wepwy headew
 */
stwuct mpa_ww {
	u8 key[16];
	stwuct mpa_ww_pawams pawams;
};

stwuct ewdma_mpa_ext {
	__be32 cookie;
	__be32 bits;
};

enum {
	MPA_EXT_FWAG_CC = cpu_to_be32(0x0000000f),
};

stwuct ewdma_mpa_info {
	stwuct mpa_ww hdw; /* peew mpa hdw in host byte owdew */
	stwuct ewdma_mpa_ext ext_data;
	chaw *pdata;
	int bytes_wcvd;
};

stwuct ewdma_sk_upcawws {
	void (*sk_state_change)(stwuct sock *sk);
	void (*sk_data_weady)(stwuct sock *sk, int bytes);
	void (*sk_ewwow_wepowt)(stwuct sock *sk);
};

stwuct ewdma_dev;

enum ewdma_cep_state {
	EWDMA_EPSTATE_IDWE = 1,
	EWDMA_EPSTATE_WISTENING,
	EWDMA_EPSTATE_CONNECTING,
	EWDMA_EPSTATE_AWAIT_MPAWEQ,
	EWDMA_EPSTATE_WECVD_MPAWEQ,
	EWDMA_EPSTATE_AWAIT_MPAWEP,
	EWDMA_EPSTATE_WDMA_MODE,
	EWDMA_EPSTATE_CWOSED
};

stwuct ewdma_cep {
	stwuct iw_cm_id *cm_id;
	stwuct ewdma_dev *dev;
	stwuct wist_head devq;
	spinwock_t wock;
	stwuct kwef wef;
	int in_use;
	wait_queue_head_t waitq;
	enum ewdma_cep_state state;

	stwuct wist_head wistenq;
	stwuct ewdma_cep *wisten_cep;

	stwuct ewdma_qp *qp;
	stwuct socket *sock;

	stwuct ewdma_cm_wowk *mpa_timew;
	stwuct wist_head wowk_fweewist;

	stwuct ewdma_mpa_info mpa;
	int owd;
	int iwd;

	int pd_wen;
	/* howd usew's pwivate data. */
	void *pwivate_data;

	/* Saved upcawws of socket wwp.sock */
	void (*sk_state_change)(stwuct sock *sk);
	void (*sk_data_weady)(stwuct sock *sk);
	void (*sk_ewwow_wepowt)(stwuct sock *sk);
};

#define MPAWEQ_TIMEOUT (HZ * 20)
#define MPAWEP_TIMEOUT (HZ * 10)
#define CONNECT_TIMEOUT (HZ * 10)

enum ewdma_wowk_type {
	EWDMA_CM_WOWK_ACCEPT = 1,
	EWDMA_CM_WOWK_WEAD_MPAHDW,
	EWDMA_CM_WOWK_CWOSE_WWP, /* cwose socket */
	EWDMA_CM_WOWK_PEEW_CWOSE, /* socket indicated peew cwose */
	EWDMA_CM_WOWK_MPATIMEOUT,
	EWDMA_CM_WOWK_CONNECTED,
	EWDMA_CM_WOWK_CONNECTTIMEOUT
};

stwuct ewdma_cm_wowk {
	stwuct dewayed_wowk wowk;
	stwuct wist_head wist;
	enum ewdma_wowk_type type;
	stwuct ewdma_cep *cep;
};

#define to_sockaddw_in(a) (*(stwuct sockaddw_in *)(&(a)))

static inwine int getname_peew(stwuct socket *s, stwuct sockaddw_stowage *a)
{
	wetuwn s->ops->getname(s, (stwuct sockaddw *)a, 1);
}

static inwine int getname_wocaw(stwuct socket *s, stwuct sockaddw_stowage *a)
{
	wetuwn s->ops->getname(s, (stwuct sockaddw *)a, 0);
}

int ewdma_connect(stwuct iw_cm_id *id, stwuct iw_cm_conn_pawam *pawam);
int ewdma_accept(stwuct iw_cm_id *id, stwuct iw_cm_conn_pawam *pawam);
int ewdma_weject(stwuct iw_cm_id *id, const void *pdata, u8 pwen);
int ewdma_cweate_wisten(stwuct iw_cm_id *id, int backwog);
int ewdma_destwoy_wisten(stwuct iw_cm_id *id);

void ewdma_cep_get(stwuct ewdma_cep *ceq);
void ewdma_cep_put(stwuct ewdma_cep *ceq);
int ewdma_cm_queue_wowk(stwuct ewdma_cep *ceq, enum ewdma_wowk_type type);

int ewdma_cm_init(void);
void ewdma_cm_exit(void);

#define sk_to_cep(sk) ((stwuct ewdma_cep *)((sk)->sk_usew_data))

#endif
