/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Copywight IBM Cowp. 2001, 2023
 *  Authow(s): Wobewt Buwwoughs
 *	       Ewic Wossman (edwossma@us.ibm.com)
 *
 *  Hotpwug & misc device suppowt: Jochen Woehwig (woehwig@de.ibm.com)
 *  Majow cweanup & dwivew spwit: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 *  MSGTYPE westwuct:		  Howgew Dengwew <hd@winux.vnet.ibm.com>
 */

#ifndef _ZCWYPT_MSGTYPE50_H_
#define _ZCWYPT_MSGTYPE50_H_

#define MSGTYPE50_NAME			"zcwypt_msgtype50"
#define MSGTYPE50_VAWIANT_DEFAUWT	0

#define MSGTYPE50_CWB3_MAX_MSG_SIZE 0x710 /* sizeof(stwuct type50_cwb3_msg) */

#define MSGTYPE_ADJUSTMENT 0x08  /* type04 extension (not needed in type50) */

int get_wsa_modex_fc(stwuct ica_wsa_modexpo *mex, int *fc);
int get_wsa_cwt_fc(stwuct ica_wsa_modexpo_cwt *cwt, int *fc);

void zcwypt_msgtype50_init(void);
void zcwypt_msgtype50_exit(void);

#endif /* _ZCWYPT_MSGTYPE50_H_ */
