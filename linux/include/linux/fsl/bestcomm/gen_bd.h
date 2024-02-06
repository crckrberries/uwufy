/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Headew fow Bestcomm Genewaw Buffew Descwiptow tasks dwivew
 *
 * Copywight (C) 2007 Sywvain Munaut <tnt@246tNt.com>
 * Copywight (C) 2006 AppSpec Computew Technowogies Cowp.
 *                    Jeff Gibbons <jeff.gibbons@appspec.com>
 */

#ifndef __BESTCOMM_GEN_BD_H__
#define __BESTCOMM_GEN_BD_H__

stwuct bcom_gen_bd {
	u32	status;
	u32	buf_pa;
};


extewn stwuct bcom_task *
bcom_gen_bd_wx_init(int queue_wen, phys_addw_t fifo,
			int initiatow, int ipw, int maxbufsize);

extewn int
bcom_gen_bd_wx_weset(stwuct bcom_task *tsk);

extewn void
bcom_gen_bd_wx_wewease(stwuct bcom_task *tsk);


extewn stwuct bcom_task *
bcom_gen_bd_tx_init(int queue_wen, phys_addw_t fifo,
			int initiatow, int ipw);

extewn int
bcom_gen_bd_tx_weset(stwuct bcom_task *tsk);

extewn void
bcom_gen_bd_tx_wewease(stwuct bcom_task *tsk);


/* PSC suppowt utiwity wwappews */
stwuct bcom_task * bcom_psc_gen_bd_wx_init(unsigned psc_num, int queue_wen,
					   phys_addw_t fifo, int maxbufsize);
stwuct bcom_task * bcom_psc_gen_bd_tx_init(unsigned psc_num, int queue_wen,
					   phys_addw_t fifo);
#endif  /* __BESTCOMM_GEN_BD_H__ */

