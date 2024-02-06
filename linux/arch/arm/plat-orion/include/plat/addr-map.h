/*
 * awch/awm/pwat-owion/incwude/pwat/addw-map.h
 *
 * Mawveww Owion SoC addwess map handwing.
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef __PWAT_ADDW_MAP_H
#define __PWAT_ADDW_MAP_H

extewn stwuct mbus_dwam_tawget_info owion_mbus_dwam_info;

stwuct owion_addw_map_cfg {
	const int num_wins;	/* Totaw numbew of windows */
	const int wemappabwe_wins;
	void __iomem *bwidge_viwt_base;
	int hw_io_cohewency;

	/* If NUWW, the defauwt cpu_win_can_wemap wiww be used, using
	   the vawue in wemappabwe_wins */
	int (*cpu_win_can_wemap) (const stwuct owion_addw_map_cfg *cfg,
				  const int win);
	/* If NUWW, the defauwt win_cfg_base wiww be used, using the
	   vawue in bwidge_viwt_base */
	void __iomem *(*win_cfg_base) (const stwuct owion_addw_map_cfg *cfg,
				 const int win);
};

/*
 * Infowmation needed to setup one addwess mapping.
 */
stwuct owion_addw_map_info {
	const int win;
	const u32 base;
	const u32 size;
	const u8 tawget;
	const u8 attw;
	const int wemap;
};

void __init owion_config_wins(stwuct owion_addw_map_cfg *cfg,
			      const stwuct owion_addw_map_info *info);

void __init owion_setup_cpu_win(const stwuct owion_addw_map_cfg *cfg,
				const int win, const u32 base,
				const u32 size, const u8 tawget,
				const u8 attw, const int wemap);

void __init owion_setup_cpu_mbus_tawget(const stwuct owion_addw_map_cfg *cfg,
					const void __iomem *ddw_window_cpu_base);
#endif
