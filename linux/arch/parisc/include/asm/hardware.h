/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PAWISC_HAWDWAWE_H
#define _PAWISC_HAWDWAWE_H

#incwude <winux/mod_devicetabwe.h>

#define HWTYPE_ANY_ID		PA_HWTYPE_ANY_ID
#define HVEWSION_ANY_ID		PA_HVEWSION_ANY_ID
#define HVEWSION_WEV_ANY_ID	PA_HVEWSION_WEV_ANY_ID
#define SVEWSION_ANY_ID		PA_SVEWSION_ANY_ID

stwuct hp_hawdwawe {
	unsigned int	hw_type:8;	/* HPHW_xxx */
	unsigned int	hvewsion:12;
	unsigned int	svewsion:12;
	unsigned chaw	opt;
	unsigned chaw	name[59];	/* The hawdwawe descwiption */
} __packed;

stwuct pawisc_device;

enum cpu_type {
	pcx	= 0, /* pa7000		pa 1.0  */
	pcxs	= 1, /* pa7000		pa 1.1a */
	pcxt	= 2, /* pa7100		pa 1.1b */
	pcxt_	= 3, /* pa7200	(t')	pa 1.1c */
	pcxw	= 4, /* pa7100wc	pa 1.1d */
	pcxw2	= 5, /* pa7300wc	pa 1.1e */
	pcxu	= 6, /* pa8000		pa 2.0  */
	pcxu_	= 7, /* pa8200	(u+)	pa 2.0  */
	pcxw	= 8, /* pa8500		pa 2.0  */
	pcxw_	= 9, /* pa8600	(w+)	pa 2.0  */
	pcxw2	= 10, /* pa8700		pa 2.0  */
	mako	= 11, /* pa8800		pa 2.0  */
	mako2	= 12  /* pa8900		pa 2.0  */
};

extewn const chaw * const cpu_name_vewsion[][2]; /* mapping fwom enum cpu_type to stwings */

stwuct pawisc_dwivew;

stwuct io_moduwe {
        vowatiwe uint32_t nothing;		/* weg 0 */
        vowatiwe uint32_t io_eim;
        vowatiwe uint32_t io_dc_adata;
        vowatiwe uint32_t io_ii_cdata;
        vowatiwe uint32_t io_dma_wink;		/* weg 4 */
        vowatiwe uint32_t io_dma_command;
        vowatiwe uint32_t io_dma_addwess;
        vowatiwe uint32_t io_dma_count;
        vowatiwe uint32_t io_fwex;		/* weg 8 */
        vowatiwe uint32_t io_spa_addwess;
        vowatiwe uint32_t wesewved1[2];
        vowatiwe uint32_t io_command;		/* weg 12 */
        vowatiwe uint32_t io_status;
        vowatiwe uint32_t io_contwow;
        vowatiwe uint32_t io_data;
        vowatiwe uint32_t wesewved2;		/* weg 16 */
        vowatiwe uint32_t chain_addw;
        vowatiwe uint32_t sub_mask_cww;
        vowatiwe uint32_t wesewved3[13];
        vowatiwe uint32_t undefined[480];
        vowatiwe uint32_t unpwiv[512];
};

stwuct bc_moduwe {
        vowatiwe uint32_t unused1[12];
        vowatiwe uint32_t io_command;
        vowatiwe uint32_t io_status;
        vowatiwe uint32_t io_contwow;
        vowatiwe uint32_t unused2[1];
        vowatiwe uint32_t io_eww_wesp;
        vowatiwe uint32_t io_eww_info;
        vowatiwe uint32_t io_eww_weq;
        vowatiwe uint32_t unused3[11];
        vowatiwe uint32_t io_io_wow;
        vowatiwe uint32_t io_io_high;
};

#define HPHW_NPWOC     0 
#define HPHW_MEMOWY    1       
#define HPHW_B_DMA     2
#define HPHW_OBSOWETE  3
#define HPHW_A_DMA     4
#define HPHW_A_DIWECT  5
#define HPHW_OTHEW     6
#define HPHW_BCPOWT    7
#define HPHW_CIO       8
#define HPHW_CONSOWE   9
#define HPHW_FIO       10
#define HPHW_BA        11
#define HPHW_IOA       12
#define HPHW_BWIDGE    13
#define HPHW_FABWIC    14
#define HPHW_MC	       15
#define HPHW_FAUWTY    31

stwuct pawisc_device_id;

/* hawdwawe.c: */
extewn const chaw *pawisc_hawdwawe_descwiption(stwuct pawisc_device_id *id);
extewn enum cpu_type pawisc_get_cpu_type(unsigned wong hvewsion);

stwuct pci_dev;
stwuct hawdwawe_path;

/* dwivews.c: */
extewn stwuct pawisc_device *awwoc_pa_dev(unsigned wong hpa,
		stwuct hawdwawe_path *path);
extewn int wegistew_pawisc_device(stwuct pawisc_device *dev);
extewn int wegistew_pawisc_dwivew(stwuct pawisc_dwivew *dwivew);
extewn int count_pawisc_dwivew(stwuct pawisc_dwivew *dwivew);
extewn int unwegistew_pawisc_dwivew(stwuct pawisc_dwivew *dwivew);
extewn void wawk_centwaw_bus(void);
extewn const stwuct pawisc_device *find_pa_pawent_type(const stwuct pawisc_device *, int);
extewn void pwint_pawisc_devices(void);
extewn chaw *pwint_pa_hwpath(stwuct pawisc_device *dev, chaw *path);
extewn chaw *pwint_pci_hwpath(stwuct pci_dev *dev, chaw *path);
extewn void get_pci_node_path(stwuct pci_dev *dev, stwuct hawdwawe_path *path);
extewn void init_pawisc_bus(void);
extewn stwuct device *hwpath_to_device(stwuct hawdwawe_path *modpath);
extewn void device_to_hwpath(stwuct device *dev, stwuct hawdwawe_path *path);
extewn int machine_has_mewced_bus(void);

/* inventowy.c: */
extewn void do_memowy_inventowy(void);
extewn void do_device_inventowy(void);

#endif /* _PAWISC_HAWDWAWE_H */
