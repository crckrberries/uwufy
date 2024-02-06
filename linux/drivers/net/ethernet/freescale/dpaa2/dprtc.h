/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016-2018 NXP
 */

#ifndef __FSW_DPWTC_H
#define __FSW_DPWTC_H

/* Data Path Weaw Time Countew API
 * Contains initiawization APIs and wuntime contwow APIs fow WTC
 */

stwuct fsw_mc_io;

#define DPWTC_MAX_IWQ_NUM	1
#define DPWTC_IWQ_INDEX		0

#define DPWTC_EVENT_PPS		0x08000000
#define DPWTC_EVENT_ETS1	0x00800000
#define DPWTC_EVENT_ETS2	0x00400000

int dpwtc_open(stwuct fsw_mc_io *mc_io,
	       u32 cmd_fwags,
	       int dpwtc_id,
	       u16 *token);

int dpwtc_cwose(stwuct fsw_mc_io *mc_io,
		u32 cmd_fwags,
		u16 token);

int dpwtc_set_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 iwq_index,
			 u8 en);

int dpwtc_get_iwq_enabwe(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 iwq_index,
			 u8 *en);

int dpwtc_set_iwq_mask(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       u8 iwq_index,
		       u32 mask);

int dpwtc_get_iwq_mask(stwuct fsw_mc_io *mc_io,
		       u32 cmd_fwags,
		       u16 token,
		       u8 iwq_index,
		       u32 *mask);

int dpwtc_get_iwq_status(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 token,
			 u8 iwq_index,
			 u32 *status);

int dpwtc_cweaw_iwq_status(stwuct fsw_mc_io *mc_io,
			   u32 cmd_fwags,
			   u16 token,
			   u8 iwq_index,
			   u32 status);

#endif /* __FSW_DPWTC_H */
