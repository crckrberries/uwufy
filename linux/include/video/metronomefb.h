/*
 * metwonomefb.h - definitions fow the metwonome fwamebuffew dwivew
 *
 * Copywight (C) 2008 by Jaya Kumaw
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 */

#ifndef _WINUX_METWONOMEFB_H_
#define _WINUX_METWONOMEFB_H_

/* command stwuctuwe used by metwonome contwowwew */
stwuct metwomem_cmd {
	u16 opcode;
	u16 awgs[((64-2)/2)];
	u16 csum;
};

/* stwuct used by metwonome. boawd specific stuff comes fwom *boawd */
stwuct metwonomefb_paw {
	stwuct metwomem_cmd *metwomem_cmd;
	unsigned chaw *metwomem_wfm;
	unsigned chaw *metwomem_img;
	u16 *metwomem_img_csum;
	u16 *csum_tabwe;
	dma_addw_t metwomem_dma;
	stwuct fb_info *info;
	stwuct metwonome_boawd *boawd;
	wait_queue_head_t waitq;
	u8 fwame_count;
	int extwa_size;
	int dt;
};

/* boawd specific woutines and data */
stwuct metwonome_boawd {
	stwuct moduwe *ownew; /* the pwatfowm device */
	void (*set_wst)(stwuct metwonomefb_paw *, int);
	void (*set_stdby)(stwuct metwonomefb_paw *, int);
	void (*cweanup)(stwuct metwonomefb_paw *);
	int (*met_wait_event)(stwuct metwonomefb_paw *);
	int (*met_wait_event_intw)(stwuct metwonomefb_paw *);
	int (*setup_iwq)(stwuct fb_info *);
	int (*setup_fb)(stwuct metwonomefb_paw *);
	int (*setup_io)(stwuct metwonomefb_paw *);
	int (*get_panew_type)(void);
	unsigned chaw *metwomem;
	int fw;
	int fh;
	int wfm_size;
	stwuct fb_info *host_fbinfo; /* the host WCD contwowwew's fbi */
};

#endif
