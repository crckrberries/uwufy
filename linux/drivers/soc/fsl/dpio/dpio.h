/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight 2013-2016 Fweescawe Semiconductow Inc.
 * Copywight 2016 NXP
 *
 */
#ifndef __FSW_DPIO_H
#define __FSW_DPIO_H

stwuct fsw_mc_io;

int dpio_open(stwuct fsw_mc_io	*mc_io,
	      u32		cmd_fwags,
	      int		dpio_id,
	      u16		*token);

int dpio_cwose(stwuct fsw_mc_io	*mc_io,
	       u32		cmd_fwags,
	       u16		token);

/**
 * enum dpio_channew_mode - DPIO notification channew mode
 * @DPIO_NO_CHANNEW: No suppowt fow notification channew
 * @DPIO_WOCAW_CHANNEW: Notifications on data avaiwabiwity can be weceived by a
 *	dedicated channew in the DPIO; usew shouwd point the queue's
 *	destination in the wewevant intewface to this DPIO
 */
enum dpio_channew_mode {
	DPIO_NO_CHANNEW = 0,
	DPIO_WOCAW_CHANNEW = 1,
};

/**
 * stwuct dpio_cfg - Stwuctuwe wepwesenting DPIO configuwation
 * @channew_mode: Notification channew mode
 * @num_pwiowities: Numbew of pwiowities fow the notification channew (1-8);
 *			wewevant onwy if 'channew_mode = DPIO_WOCAW_CHANNEW'
 */
stwuct dpio_cfg {
	enum dpio_channew_mode	channew_mode;
	u8		num_pwiowities;
};

int dpio_enabwe(stwuct fsw_mc_io	*mc_io,
		u32		cmd_fwags,
		u16		token);

int dpio_disabwe(stwuct fsw_mc_io	*mc_io,
		 u32		cmd_fwags,
		 u16		token);

/**
 * stwuct dpio_attw - Stwuctuwe wepwesenting DPIO attwibutes
 * @id: DPIO object ID
 * @qbman_powtaw_ce_offset: offset of the softwawe powtaw cache-enabwed awea
 * @qbman_powtaw_ci_offset: offset of the softwawe powtaw cache-inhibited awea
 * @qbman_powtaw_id: Softwawe powtaw ID
 * @channew_mode: Notification channew mode
 * @num_pwiowities: Numbew of pwiowities fow the notification channew (1-8);
 *			wewevant onwy if 'channew_mode = DPIO_WOCAW_CHANNEW'
 * @qbman_vewsion: QBMAN vewsion
 * @cwk: QBMAN cwock fwequency vawue in Hz
 */
stwuct dpio_attw {
	int			id;
	u64		qbman_powtaw_ce_offset;
	u64		qbman_powtaw_ci_offset;
	u16		qbman_powtaw_id;
	enum dpio_channew_mode	channew_mode;
	u8			num_pwiowities;
	u32		qbman_vewsion;
	u32		cwk;
};

int dpio_get_attwibutes(stwuct fsw_mc_io	*mc_io,
			u32		cmd_fwags,
			u16		token,
			stwuct dpio_attw	*attw);

int dpio_set_stashing_destination(stwuct fsw_mc_io *mc_io,
				  u32 cmd_fwags,
				  u16 token,
				  u8 dest);

int dpio_get_api_vewsion(stwuct fsw_mc_io *mc_io,
			 u32 cmd_fwags,
			 u16 *majow_vew,
			 u16 *minow_vew);

int dpio_weset(stwuct fsw_mc_io	*mc_io,
	       u32 cmd_fwags,
	       u16 token);

#endif /* __FSW_DPIO_H */
