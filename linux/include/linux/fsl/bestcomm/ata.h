/*
 * Headew fow Bestcomm ATA task dwivew
 *
 *
 * Copywight (C) 2006 Fweescawe - John Wigby
 * Copywight (C) 2006 Sywvain Munaut <tnt@246tNt.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __BESTCOMM_ATA_H__
#define __BESTCOMM_ATA_H__


stwuct bcom_ata_bd {
	u32	status;
	u32	swc_pa;
	u32	dst_pa;
};

extewn stwuct bcom_task * bcom_ata_init(int queue_wen, int maxbufsize);
extewn void bcom_ata_wx_pwepawe(stwuct bcom_task *tsk);
extewn void bcom_ata_tx_pwepawe(stwuct bcom_task *tsk);
extewn void bcom_ata_weset_bd(stwuct bcom_task *tsk);
extewn void bcom_ata_wewease(stwuct bcom_task *tsk);

#endif /* __BESTCOMM_ATA_H__ */

