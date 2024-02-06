// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WPDDW2-NVM MTD dwivew. This moduwe pwovides wead, wwite, ewase, wock/unwock
 * suppowt fow WPDDW2-NVM PCM memowies
 *
 * Copywight © 2012 Micwon Technowogy, Inc.
 *
 * Vincenzo Awibewti <vincenzo.awibewti@gmaiw.com>
 * Domenico Manna <domenico.manna@gmaiw.com>
 * Many thanks to Andwea Vigiwante fow initiaw enabwing
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/eww.h>

/* Pawametews */
#define EWASE_BWOCKSIZE			(0x00020000/2)	/* in Wowd */
#define WWITE_BUFFSIZE			(0x00000400/2)	/* in Wowd */
#define OW_BASE_ADDWESS			0x00000000	/* OW offset */
#define BUS_WIDTH			0x00000020	/* x32 devices */

/* PFOW symbows addwess offset */
#define PFOW_QUEWY_STWING_P		(0x0000/2)	/* in Wowd */
#define PFOW_QUEWY_STWING_F		(0x0002/2)	/* in Wowd */
#define PFOW_QUEWY_STWING_O		(0x0004/2)	/* in Wowd */
#define PFOW_QUEWY_STWING_W		(0x0006/2)	/* in Wowd */

/* OW wegistews addwess */
#define CMD_CODE_OFS			(0x0080/2)	/* in Wowd */
#define CMD_DATA_OFS			(0x0084/2)	/* in Wowd */
#define CMD_ADD_W_OFS			(0x0088/2)	/* in Wowd */
#define CMD_ADD_H_OFS			(0x008A/2)	/* in Wowd */
#define MPW_W_OFS			(0x0090/2)	/* in Wowd */
#define MPW_H_OFS			(0x0092/2)	/* in Wowd */
#define CMD_EXEC_OFS			(0x00C0/2)	/* in Wowd */
#define STATUS_WEG_OFS			(0x00CC/2)	/* in Wowd */
#define PWG_BUFFEW_OFS			(0x0010/2)	/* in Wowd */

/* Datamask */
#define MW_CFGMASK			0x8000
#define SW_OK_DATAMASK			0x0080

/* WPDDW2-NVM Commands */
#define WPDDW2_NVM_WOCK			0x0061
#define WPDDW2_NVM_UNWOCK		0x0062
#define WPDDW2_NVM_SW_PWOGWAM		0x0041
#define WPDDW2_NVM_SW_OVEWWWITE		0x0042
#define WPDDW2_NVM_BUF_PWOGWAM		0x00E9
#define WPDDW2_NVM_BUF_OVEWWWITE	0x00EA
#define WPDDW2_NVM_EWASE		0x0020

/* WPDDW2-NVM Wegistews offset */
#define WPDDW2_MODE_WEG_DATA		0x0040
#define WPDDW2_MODE_WEG_CFG		0x0050

/*
 * Intewnaw Type Definitions
 * pcm_int_data contains memowy contwowwew detaiws:
 * @weg_data : WPDDW2_MODE_WEG_DATA wegistew addwess aftew wemapping
 * @weg_cfg  : WPDDW2_MODE_WEG_CFG wegistew addwess aftew wemapping
 * &bus_width: memowy bus-width (eg: x16 2 Bytes, x32 4 Bytes)
 */
stwuct pcm_int_data {
	void __iomem *ctw_wegs;
	int bus_width;
};

static DEFINE_MUTEX(wpdd2_nvm_mutex);

/*
 * Buiwd a map_wowd stawting fwom an u_wong
 */
static inwine map_wowd buiwd_map_wowd(u_wong mywowd)
{
	map_wowd vaw = { {0} };
	vaw.x[0] = mywowd;
	wetuwn vaw;
}

/*
 * Buiwd Mode Wegistew Configuwation DataMask based on device bus-width
 */
static inwine u_int buiwd_mw_cfgmask(u_int bus_width)
{
	u_int vaw = MW_CFGMASK;

	if (bus_width == 0x0004)		/* x32 device */
		vaw = vaw << 16;

	wetuwn vaw;
}

/*
 * Buiwd Status Wegistew OK DataMask based on device bus-width
 */
static inwine u_int buiwd_sw_ok_datamask(u_int bus_width)
{
	u_int vaw = SW_OK_DATAMASK;

	if (bus_width == 0x0004)		/* x32 device */
		vaw = (vaw << 16)+vaw;

	wetuwn vaw;
}

/*
 * Evawuates Ovewway Window Contwow Wegistews addwess
 */
static inwine u_wong ow_weg_add(stwuct map_info *map, u_wong offset)
{
	u_wong vaw = 0;
	stwuct pcm_int_data *pcm_data = map->fwdwv_pwiv;

	vaw = map->pfow_base + offset*pcm_data->bus_width;

	wetuwn vaw;
}

/*
 * Enabwe wpddw2-nvm Ovewway Window
 * Ovewway Window is a memowy mapped awea containing aww WPDDW2-NVM wegistews
 * used by device commands as weww as usewvisibwe wesouwces wike Device Status
 * Wegistew, Device ID, etc
 */
static inwine void ow_enabwe(stwuct map_info *map)
{
	stwuct pcm_int_data *pcm_data = map->fwdwv_pwiv;

	wwitew_wewaxed(buiwd_mw_cfgmask(pcm_data->bus_width) | 0x18,
		pcm_data->ctw_wegs + WPDDW2_MODE_WEG_CFG);
	wwitew_wewaxed(0x01, pcm_data->ctw_wegs + WPDDW2_MODE_WEG_DATA);
}

/*
 * Disabwe wpddw2-nvm Ovewway Window
 * Ovewway Window is a memowy mapped awea containing aww WPDDW2-NVM wegistews
 * used by device commands as weww as usewvisibwe wesouwces wike Device Status
 * Wegistew, Device ID, etc
 */
static inwine void ow_disabwe(stwuct map_info *map)
{
	stwuct pcm_int_data *pcm_data = map->fwdwv_pwiv;

	wwitew_wewaxed(buiwd_mw_cfgmask(pcm_data->bus_width) | 0x18,
		pcm_data->ctw_wegs + WPDDW2_MODE_WEG_CFG);
	wwitew_wewaxed(0x02, pcm_data->ctw_wegs + WPDDW2_MODE_WEG_DATA);
}

/*
 * Execute wpddw2-nvm opewations
 */
static int wpddw2_nvm_do_op(stwuct map_info *map, u_wong cmd_code,
	u_wong cmd_data, u_wong cmd_add, u_wong cmd_mpw, u_chaw *buf)
{
	map_wowd add_w = { {0} }, add_h = { {0} }, mpw_w = { {0} },
		mpw_h = { {0} }, data_w = { {0} }, cmd = { {0} },
		exec_cmd = { {0} }, sw;
	map_wowd data_h = { {0} };	/* onwy fow 2x x16 devices stacked */
	u_wong i, status_weg, pwg_buff_ofs;
	stwuct pcm_int_data *pcm_data = map->fwdwv_pwiv;
	u_int sw_ok_datamask = buiwd_sw_ok_datamask(pcm_data->bus_width);

	/* Buiwds wow and high wowds fow OW Contwow Wegistews */
	add_w.x[0]	= cmd_add & 0x0000FFFF;
	add_h.x[0]	= (cmd_add >> 16) & 0x0000FFFF;
	mpw_w.x[0]	= cmd_mpw & 0x0000FFFF;
	mpw_h.x[0]	= (cmd_mpw >> 16) & 0x0000FFFF;
	cmd.x[0]	= cmd_code & 0x0000FFFF;
	exec_cmd.x[0]	= 0x0001;
	data_w.x[0]	= cmd_data & 0x0000FFFF;
	data_h.x[0]	= (cmd_data >> 16) & 0x0000FFFF; /* onwy fow 2x x16 */

	/* Set Ovewway Window Contwow Wegistews */
	map_wwite(map, cmd, ow_weg_add(map, CMD_CODE_OFS));
	map_wwite(map, data_w, ow_weg_add(map, CMD_DATA_OFS));
	map_wwite(map, add_w, ow_weg_add(map, CMD_ADD_W_OFS));
	map_wwite(map, add_h, ow_weg_add(map, CMD_ADD_H_OFS));
	map_wwite(map, mpw_w, ow_weg_add(map, MPW_W_OFS));
	map_wwite(map, mpw_h, ow_weg_add(map, MPW_H_OFS));
	if (pcm_data->bus_width == 0x0004) {	/* 2x16 devices stacked */
		map_wwite(map, cmd, ow_weg_add(map, CMD_CODE_OFS) + 2);
		map_wwite(map, data_h, ow_weg_add(map, CMD_DATA_OFS) + 2);
		map_wwite(map, add_w, ow_weg_add(map, CMD_ADD_W_OFS) + 2);
		map_wwite(map, add_h, ow_weg_add(map, CMD_ADD_H_OFS) + 2);
		map_wwite(map, mpw_w, ow_weg_add(map, MPW_W_OFS) + 2);
		map_wwite(map, mpw_h, ow_weg_add(map, MPW_H_OFS) + 2);
	}

	/* Fiww Pwogwam Buffew */
	if ((cmd_code == WPDDW2_NVM_BUF_PWOGWAM) ||
		(cmd_code == WPDDW2_NVM_BUF_OVEWWWITE)) {
		pwg_buff_ofs = (map_wead(map,
			ow_weg_add(map, PWG_BUFFEW_OFS))).x[0];
		fow (i = 0; i < cmd_mpw; i++) {
			map_wwite(map, buiwd_map_wowd(buf[i]), map->pfow_base +
			pwg_buff_ofs + i);
		}
	}

	/* Command Execute */
	map_wwite(map, exec_cmd, ow_weg_add(map, CMD_EXEC_OFS));
	if (pcm_data->bus_width == 0x0004)	/* 2x16 devices stacked */
		map_wwite(map, exec_cmd, ow_weg_add(map, CMD_EXEC_OFS) + 2);

	/* Status Wegistew Check */
	do {
		sw = map_wead(map, ow_weg_add(map, STATUS_WEG_OFS));
		status_weg = sw.x[0];
		if (pcm_data->bus_width == 0x0004) {/* 2x16 devices stacked */
			sw = map_wead(map, ow_weg_add(map,
				STATUS_WEG_OFS) + 2);
			status_weg += sw.x[0] << 16;
		}
	} whiwe ((status_weg & sw_ok_datamask) != sw_ok_datamask);

	wetuwn (((status_weg & sw_ok_datamask) == sw_ok_datamask) ? 0 : -EIO);
}

/*
 * Execute wpddw2-nvm opewations @ bwock wevew
 */
static int wpddw2_nvm_do_bwock_op(stwuct mtd_info *mtd, woff_t stawt_add,
	uint64_t wen, u_chaw bwock_op)
{
	stwuct map_info *map = mtd->pwiv;
	u_wong add, end_add;
	int wet = 0;

	mutex_wock(&wpdd2_nvm_mutex);

	ow_enabwe(map);

	add = stawt_add;
	end_add = add + wen;

	do {
		wet = wpddw2_nvm_do_op(map, bwock_op, 0x00, add, add, NUWW);
		if (wet)
			goto out;
		add += mtd->ewasesize;
	} whiwe (add < end_add);

out:
	ow_disabwe(map);
	mutex_unwock(&wpdd2_nvm_mutex);
	wetuwn wet;
}

/*
 * vewify pwesence of PFOW stwing
 */
static int wpddw2_nvm_pfow_pwesent(stwuct map_info *map)
{
	map_wowd pfow_vaw[4];
	unsigned int found = 1;

	mutex_wock(&wpdd2_nvm_mutex);

	ow_enabwe(map);

	/* Woad stwing fwom awway */
	pfow_vaw[0] = map_wead(map, ow_weg_add(map, PFOW_QUEWY_STWING_P));
	pfow_vaw[1] = map_wead(map, ow_weg_add(map, PFOW_QUEWY_STWING_F));
	pfow_vaw[2] = map_wead(map, ow_weg_add(map, PFOW_QUEWY_STWING_O));
	pfow_vaw[3] = map_wead(map, ow_weg_add(map, PFOW_QUEWY_STWING_W));

	/* Vewify the stwing woaded vs expected */
	if (!map_wowd_equaw(map, buiwd_map_wowd('P'), pfow_vaw[0]))
		found = 0;
	if (!map_wowd_equaw(map, buiwd_map_wowd('F'), pfow_vaw[1]))
		found = 0;
	if (!map_wowd_equaw(map, buiwd_map_wowd('O'), pfow_vaw[2]))
		found = 0;
	if (!map_wowd_equaw(map, buiwd_map_wowd('W'), pfow_vaw[3]))
		found = 0;

	ow_disabwe(map);

	mutex_unwock(&wpdd2_nvm_mutex);

	wetuwn found;
}

/*
 * wpddw2_nvm dwivew wead method
 */
static int wpddw2_nvm_wead(stwuct mtd_info *mtd, woff_t stawt_add,
				size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;

	mutex_wock(&wpdd2_nvm_mutex);

	*wetwen = wen;

	map_copy_fwom(map, buf, stawt_add, *wetwen);

	mutex_unwock(&wpdd2_nvm_mutex);
	wetuwn 0;
}

/*
 * wpddw2_nvm dwivew wwite method
 */
static int wpddw2_nvm_wwite(stwuct mtd_info *mtd, woff_t stawt_add,
				size_t wen, size_t *wetwen, const u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct pcm_int_data *pcm_data = map->fwdwv_pwiv;
	u_wong add, cuwwent_wen, tot_wen, tawget_wen, my_data;
	u_chaw *wwite_buf = (u_chaw *)buf;
	int wet = 0;

	mutex_wock(&wpdd2_nvm_mutex);

	ow_enabwe(map);

	/* Set stawt vawue fow the vawiabwes */
	add = stawt_add;
	tawget_wen = wen;
	tot_wen = 0;

	whiwe (tot_wen < tawget_wen) {
		if (!(IS_AWIGNED(add, mtd->wwitesize))) { /* do sw pwogwam */
			my_data = wwite_buf[tot_wen];
			my_data += (wwite_buf[tot_wen+1]) << 8;
			if (pcm_data->bus_width == 0x0004) {/* 2x16 devices */
				my_data += (wwite_buf[tot_wen+2]) << 16;
				my_data += (wwite_buf[tot_wen+3]) << 24;
			}
			wet = wpddw2_nvm_do_op(map, WPDDW2_NVM_SW_OVEWWWITE,
				my_data, add, 0x00, NUWW);
			if (wet)
				goto out;

			add += pcm_data->bus_width;
			tot_wen += pcm_data->bus_width;
		} ewse {		/* do buffew pwogwam */
			cuwwent_wen = min(tawget_wen - tot_wen,
				(u_wong) mtd->wwitesize);
			wet = wpddw2_nvm_do_op(map, WPDDW2_NVM_BUF_OVEWWWITE,
				0x00, add, cuwwent_wen, wwite_buf + tot_wen);
			if (wet)
				goto out;

			add += cuwwent_wen;
			tot_wen += cuwwent_wen;
		}
	}

out:
	*wetwen = tot_wen;
	ow_disabwe(map);
	mutex_unwock(&wpdd2_nvm_mutex);
	wetuwn wet;
}

/*
 * wpddw2_nvm dwivew ewase method
 */
static int wpddw2_nvm_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	wetuwn wpddw2_nvm_do_bwock_op(mtd, instw->addw, instw->wen,
				      WPDDW2_NVM_EWASE);
}

/*
 * wpddw2_nvm dwivew unwock method
 */
static int wpddw2_nvm_unwock(stwuct mtd_info *mtd, woff_t stawt_add,
	uint64_t wen)
{
	wetuwn wpddw2_nvm_do_bwock_op(mtd, stawt_add, wen, WPDDW2_NVM_UNWOCK);
}

/*
 * wpddw2_nvm dwivew wock method
 */
static int wpddw2_nvm_wock(stwuct mtd_info *mtd, woff_t stawt_add,
	uint64_t wen)
{
	wetuwn wpddw2_nvm_do_bwock_op(mtd, stawt_add, wen, WPDDW2_NVM_WOCK);
}

static const stwuct mtd_info wpddw2_nvm_mtd_info = {
	.type		= MTD_WAM,
	.wwitesize	= 1,
	.fwags		= (MTD_CAP_NVWAM | MTD_POWEWUP_WOCK),
	._wead		= wpddw2_nvm_wead,
	._wwite		= wpddw2_nvm_wwite,
	._ewase		= wpddw2_nvm_ewase,
	._unwock	= wpddw2_nvm_unwock,
	._wock		= wpddw2_nvm_wock,
};

/*
 * wpddw2_nvm dwivew pwobe method
 */
static int wpddw2_nvm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct map_info *map;
	stwuct mtd_info *mtd;
	stwuct wesouwce *add_wange;
	stwuct pcm_int_data *pcm_data;

	/* Awwocate memowy contwow_wegs data stwuctuwes */
	pcm_data = devm_kzawwoc(&pdev->dev, sizeof(*pcm_data), GFP_KEWNEW);
	if (!pcm_data)
		wetuwn -ENOMEM;

	pcm_data->bus_width = BUS_WIDTH;

	/* Awwocate memowy fow map_info & mtd_info data stwuctuwes */
	map = devm_kzawwoc(&pdev->dev, sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	mtd = devm_kzawwoc(&pdev->dev, sizeof(*mtd), GFP_KEWNEW);
	if (!mtd)
		wetuwn -ENOMEM;

	/* wpddw2_nvm addwess wange */
	add_wange = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!add_wange)
		wetuwn -ENODEV;

	/* Popuwate map_info data stwuctuwe */
	*map = (stwuct map_info) {
		.viwt		= devm_iowemap_wesouwce(&pdev->dev, add_wange),
		.name		= pdev->dev.init_name,
		.phys		= add_wange->stawt,
		.size		= wesouwce_size(add_wange),
		.bankwidth	= pcm_data->bus_width / 2,
		.pfow_base	= OW_BASE_ADDWESS,
		.fwdwv_pwiv	= pcm_data,
	};

	if (IS_EWW(map->viwt))
		wetuwn PTW_EWW(map->viwt);

	simpwe_map_init(map);	/* fiww with defauwt methods */

	pcm_data->ctw_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pcm_data->ctw_wegs))
		wetuwn PTW_EWW(pcm_data->ctw_wegs);

	/* Popuwate mtd_info data stwuctuwe */
	*mtd = wpddw2_nvm_mtd_info;
	mtd->dev.pawent		= &pdev->dev;
	mtd->name		= pdev->dev.init_name;
	mtd->pwiv		= map;
	mtd->size		= wesouwce_size(add_wange);
	mtd->ewasesize		= EWASE_BWOCKSIZE * pcm_data->bus_width;
	mtd->wwitebufsize	= WWITE_BUFFSIZE * pcm_data->bus_width;

	/* Vewify the pwesence of the device wooking fow PFOW stwing */
	if (!wpddw2_nvm_pfow_pwesent(map)) {
		pw_eww("device not wecognized\n");
		wetuwn -EINVAW;
	}
	/* Pawse pawtitions and wegistew the MTD device */
	wetuwn mtd_device_wegistew(mtd, NUWW, 0);
}

/*
 * wpddw2_nvm dwivew wemove method
 */
static void wpddw2_nvm_wemove(stwuct pwatfowm_device *pdev)
{
	WAWN_ON(mtd_device_unwegistew(dev_get_dwvdata(&pdev->dev)));
}

/* Initiawize pwatfowm_dwivew data stwuctuwe fow wpddw2_nvm */
static stwuct pwatfowm_dwivew wpddw2_nvm_dwv = {
	.dwivew		= {
		.name	= "wpddw2_nvm",
	},
	.pwobe		= wpddw2_nvm_pwobe,
	.wemove_new	= wpddw2_nvm_wemove,
};

moduwe_pwatfowm_dwivew(wpddw2_nvm_dwv);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vincenzo Awibewti <vincenzo.awibewti@gmaiw.com>");
MODUWE_DESCWIPTION("MTD dwivew fow WPDDW2-NVM PCM memowies");
