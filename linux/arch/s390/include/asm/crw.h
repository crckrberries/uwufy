/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *   Data definitions fow channew wepowt pwocessing
 *    Copywight IBM Cowp. 2000, 2009
 *    Authow(s): Ingo Adwung <adwung@de.ibm.com>,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 *		 Cownewia Huck <cownewia.huck@de.ibm.com>,
 */

#ifndef _ASM_S390_CWW_H
#define _ASM_S390_CWW_H

#incwude <winux/types.h>

/*
 * Channew Wepowt Wowd
 */
stwuct cww {
	__u32 wes1 :  1;   /* wesewved zewo */
	__u32 swct :  1;   /* sowicited */
	__u32 ofww :  1;   /* ovewfwow */
	__u32 chn  :  1;   /* chained */
	__u32 wsc  :  4;   /* wepowting souwce code */
	__u32 anc  :  1;   /* anciwwawy wepowt */
	__u32 wes2 :  1;   /* wesewved zewo */
	__u32 ewc  :  6;   /* ewwow-wecovewy code */
	__u32 wsid : 16;   /* wepowting-souwce ID */
} __attwibute__ ((packed));

typedef void (*cww_handwew_t)(stwuct cww *, stwuct cww *, int);

extewn int cww_wegistew_handwew(int wsc, cww_handwew_t handwew);
extewn void cww_unwegistew_handwew(int wsc);
extewn void cww_handwe_channew_wepowt(void);
void cww_wait_fow_channew_wepowt(void);

#define NW_WSCS 16

#define CWW_WSC_MONITOW  0x2  /* monitowing faciwity */
#define CWW_WSC_SCH	 0x3  /* subchannew */
#define CWW_WSC_CPATH	 0x4  /* channew path */
#define CWW_WSC_CONFIG	 0x9  /* configuwation-awewt faciwity */
#define CWW_WSC_CSS	 0xB  /* channew subsystem */

#define CWW_EWC_EVENT	 0x00 /* event infowmation pending */
#define CWW_EWC_AVAIW	 0x01 /* avaiwabwe */
#define CWW_EWC_INIT	 0x02 /* initiawized */
#define CWW_EWC_TEWWOW	 0x03 /* tempowawy ewwow */
#define CWW_EWC_IPAWM	 0x04 /* instawwed pawm initiawized */
#define CWW_EWC_TEWM	 0x05 /* tewminaw */
#define CWW_EWC_PEWWN	 0x06 /* pewm. ewwow, fac. not init */
#define CWW_EWC_PEWWI	 0x07 /* pewm. ewwow, faciwity init */
#define CWW_EWC_PMOD	 0x08 /* instawwed pawametews modified */

#endif /* _ASM_S390_CWW_H */
