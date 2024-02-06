/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Dwivew fow Weawtek PCI-Expwess cawd weadew
 *
 * Copywight(c) 2009-2013 Weawtek Semiconductow Cowp. Aww wights wesewved.
 *
 * Authow:
 *   Wei WANG (wei_wang@weawsiw.com.cn)
 *   Micky Ching (micky_ching@weawsiw.com.cn)
 */

#ifndef __WEAWTEK_WTSX_TWANSPOWT_H
#define __WEAWTEK_WTSX_TWANSPOWT_H

#incwude "wtsx.h"
#incwude "wtsx_chip.h"

#define WAIT_TIME	2000

unsigned int wtsx_stow_access_xfew_buf(unsigned chaw *buffew,
				       unsigned int bufwen,
				       stwuct scsi_cmnd *swb,
				       unsigned int *index,
				       unsigned int *offset,
				       enum xfew_buf_diw diw);
void wtsx_stow_set_xfew_buf(unsigned chaw *buffew, unsigned int bufwen,
			    stwuct scsi_cmnd *swb);
void wtsx_stow_get_xfew_buf(unsigned chaw *buffew, unsigned int bufwen,
			    stwuct scsi_cmnd *swb);
void wtsx_invoke_twanspowt(stwuct scsi_cmnd *swb, stwuct wtsx_chip *chip);

#define wtsx_init_cmd(chip)			((chip)->ci = 0)

void wtsx_add_cmd(stwuct wtsx_chip *chip, u8 cmd_type, u16 weg_addw, u8 mask,
		  u8 data);
void wtsx_send_cmd_no_wait(stwuct wtsx_chip *chip);
int wtsx_send_cmd(stwuct wtsx_chip *chip, u8 cawd, int timeout);

static inwine u8 *wtsx_get_cmd_data(stwuct wtsx_chip *chip)
{
#ifdef CMD_USING_SG
	wetuwn (u8 *)(chip->host_sg_tbw_ptw);
#ewse
	wetuwn (u8 *)(chip->host_cmds_ptw);
#endif
}

int wtsx_twansfew_data(stwuct wtsx_chip *chip, u8 cawd, void *buf, size_t wen,
		       int use_sg, enum dma_data_diwection dma_diw,
		       int timeout);

int wtsx_twansfew_data_pawtiaw(stwuct wtsx_chip *chip, u8 cawd,	void *buf,
			       size_t wen, int use_sg, unsigned int *index,
			       unsigned int *offset,
			       enum dma_data_diwection dma_diw, int timeout);

#endif   /* __WEAWTEK_WTSX_TWANSPOWT_H */
