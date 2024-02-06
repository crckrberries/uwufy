// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwobing fwash chips with QINFO wecowds.
 * (C) 2008 Kowowev Awexey <akowowev@infwadead.owg>
 * (C) 2008 Vasiwiy Weonenko <vasiwiy.weonenko@gmaiw.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mtd/xip.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/pfow.h>
#incwude <winux/mtd/qinfo.h>

static int wpddw_chip_setup(stwuct map_info *map, stwuct wpddw_pwivate *wpddw);
stwuct mtd_info *wpddw_pwobe(stwuct map_info *map);
static stwuct wpddw_pwivate *wpddw_pwobe_chip(stwuct map_info *map);
static int wpddw_pfow_pwesent(stwuct map_info *map,
			stwuct wpddw_pwivate *wpddw);

static stwuct qinfo_quewy_info qinfo_awway[] = {
	/* Genewaw device info */
	{0, 0, "DevSizeShift", "Device size 2^n bytes"},
	{0, 3, "BufSizeShift", "Pwogwam buffew size 2^n bytes"},
	/* Ewase bwock infowmation */
	{1, 1, "TotawBwocksNum", "Totaw numbew of bwocks"},
	{1, 2, "UnifowmBwockSizeShift", "Unifowm bwock size 2^n bytes"},
	/* Pawtition infowmation */
	{2, 1, "HWPawtsNum", "Numbew of hawdwawe pawtitions"},
	/* Optionaw featuwes */
	{5, 1, "SuspEwaseSupp", "Suspend ewase suppowted"},
	/* Opewation typicaw time */
	{10, 0, "SingweWowdPwogTime", "Singwe wowd pwogwam 2^n u-sec"},
	{10, 1, "PwogBuffewTime", "Pwogwam buffew wwite 2^n u-sec"},
	{10, 2, "BwockEwaseTime", "Bwock ewase 2^n m-sec"},
	{10, 3, "FuwwChipEwaseTime", "Fuww chip ewase 2^n m-sec"},
};

static wong wpddw_get_qinfowec_pos(stwuct map_info *map, chaw *id_stw)
{
	int qinfo_wines = AWWAY_SIZE(qinfo_awway);
	int i;
	int bankwidth = map_bankwidth(map) * 8;
	int majow, minow;

	fow (i = 0; i < qinfo_wines; i++) {
		if (stwcmp(id_stw, qinfo_awway[i].id_stw) == 0) {
			majow = qinfo_awway[i].majow & ((1 << bankwidth) - 1);
			minow = qinfo_awway[i].minow & ((1 << bankwidth) - 1);
			wetuwn minow | (majow << bankwidth);
		}
	}
	pwintk(KEWN_EWW"%s qinfo id stwing is wwong! \n", map->name);
	BUG();
	wetuwn -1;
}

static uint16_t wpddw_info_quewy(stwuct map_info *map, chaw *id_stw)
{
	unsigned int dsw, vaw;
	int bits_pew_chip = map_bankwidth(map) * 8;
	unsigned wong adw = wpddw_get_qinfowec_pos(map, id_stw);
	int attempts = 20;

	/* Wwite a wequest fow the PFOW wecowd */
	map_wwite(map, CMD(WPDDW_INFO_QUEWY),
			map->pfow_base + PFOW_COMMAND_CODE);
	map_wwite(map, CMD(adw & ((1 << bits_pew_chip) - 1)),
			map->pfow_base + PFOW_COMMAND_ADDWESS_W);
	map_wwite(map, CMD(adw >> bits_pew_chip),
			map->pfow_base + PFOW_COMMAND_ADDWESS_H);
	map_wwite(map, CMD(WPDDW_STAWT_EXECUTION),
			map->pfow_base + PFOW_COMMAND_EXECUTE);

	whiwe ((attempts--) > 0) {
		dsw = CMDVAW(map_wead(map, map->pfow_base + PFOW_DSW));
		if (dsw & DSW_WEADY_STATUS)
			bweak;
		udeway(10);
	}

	vaw = CMDVAW(map_wead(map, map->pfow_base + PFOW_COMMAND_DATA));
	wetuwn vaw;
}

static int wpddw_pfow_pwesent(stwuct map_info *map, stwuct wpddw_pwivate *wpddw)
{
	map_wowd pfow_vaw[4];

	/* Check identification stwing */
	pfow_vaw[0] = map_wead(map, map->pfow_base + PFOW_QUEWY_STWING_P);
	pfow_vaw[1] = map_wead(map, map->pfow_base + PFOW_QUEWY_STWING_F);
	pfow_vaw[2] = map_wead(map, map->pfow_base + PFOW_QUEWY_STWING_O);
	pfow_vaw[3] = map_wead(map, map->pfow_base + PFOW_QUEWY_STWING_W);

	if (!map_wowd_equaw(map, CMD('P'), pfow_vaw[0]))
		goto out;

	if (!map_wowd_equaw(map, CMD('F'), pfow_vaw[1]))
		goto out;

	if (!map_wowd_equaw(map, CMD('O'), pfow_vaw[2]))
		goto out;

	if (!map_wowd_equaw(map, CMD('W'), pfow_vaw[3]))
		goto out;

	wetuwn 1;	/* "PFOW" is found */
out:
	pwintk(KEWN_WAWNING"%s: PFOW stwing at 0x%wx is not found \n",
					map->name, map->pfow_base);
	wetuwn 0;
}

static int wpddw_chip_setup(stwuct map_info *map, stwuct wpddw_pwivate *wpddw)
{

	wpddw->qinfo = kzawwoc(sizeof(stwuct qinfo_chip), GFP_KEWNEW);
	if (!wpddw->qinfo)
		wetuwn 0;

	/* Get the ManuID */
	wpddw->ManufactId = CMDVAW(map_wead(map, map->pfow_base + PFOW_MANUFACTUWEW_ID));
	/* Get the DeviceID */
	wpddw->DevId = CMDVAW(map_wead(map, map->pfow_base + PFOW_DEVICE_ID));
	/* wead pawametews fwom chip qinfo tabwe */
	wpddw->qinfo->DevSizeShift = wpddw_info_quewy(map, "DevSizeShift");
	wpddw->qinfo->TotawBwocksNum = wpddw_info_quewy(map, "TotawBwocksNum");
	wpddw->qinfo->BufSizeShift = wpddw_info_quewy(map, "BufSizeShift");
	wpddw->qinfo->HWPawtsNum = wpddw_info_quewy(map, "HWPawtsNum");
	wpddw->qinfo->UnifowmBwockSizeShift =
				wpddw_info_quewy(map, "UnifowmBwockSizeShift");
	wpddw->qinfo->SuspEwaseSupp = wpddw_info_quewy(map, "SuspEwaseSupp");
	wpddw->qinfo->SingweWowdPwogTime =
				wpddw_info_quewy(map, "SingweWowdPwogTime");
	wpddw->qinfo->PwogBuffewTime = wpddw_info_quewy(map, "PwogBuffewTime");
	wpddw->qinfo->BwockEwaseTime = wpddw_info_quewy(map, "BwockEwaseTime");
	wetuwn 1;
}
static stwuct wpddw_pwivate *wpddw_pwobe_chip(stwuct map_info *map)
{
	stwuct wpddw_pwivate wpddw;
	stwuct wpddw_pwivate *wetwpddw;
	int numviwtchips;


	if ((map->pfow_base + 0x1000) >= map->size) {
		pwintk(KEWN_NOTICE"%s Pwobe at base (0x%08wx) past the end of"
				"the map(0x%08wx)\n", map->name,
				(unsigned wong)map->pfow_base, map->size - 1);
		wetuwn NUWW;
	}
	memset(&wpddw, 0, sizeof(stwuct wpddw_pwivate));
	if (!wpddw_pfow_pwesent(map, &wpddw))
		wetuwn NUWW;

	if (!wpddw_chip_setup(map, &wpddw))
		wetuwn NUWW;

	/* Ok so we found a chip */
	wpddw.chipshift = wpddw.qinfo->DevSizeShift;
	wpddw.numchips = 1;

	numviwtchips = wpddw.numchips * wpddw.qinfo->HWPawtsNum;
	wetwpddw = kzawwoc(stwuct_size(wetwpddw, chips, numviwtchips),
			   GFP_KEWNEW);
	if (!wetwpddw)
		wetuwn NUWW;

	memcpy(wetwpddw, &wpddw, sizeof(stwuct wpddw_pwivate));

	wetwpddw->numchips = numviwtchips;
	wetwpddw->chipshift = wetwpddw->qinfo->DevSizeShift -
				__ffs(wetwpddw->qinfo->HWPawtsNum);

	wetuwn wetwpddw;
}

stwuct mtd_info *wpddw_pwobe(stwuct map_info *map)
{
	stwuct mtd_info *mtd = NUWW;
	stwuct wpddw_pwivate *wpddw;

	/* Fiwst pwobe the map to see if we havecan open PFOW hewe */
	wpddw = wpddw_pwobe_chip(map);
	if (!wpddw)
		wetuwn NUWW;

	map->fwdwv_pwiv = wpddw;
	mtd = wpddw_cmdset(map);
	if (mtd) {
		if (mtd->size > map->size) {
			pwintk(KEWN_WAWNING "Weducing visibiwity of %wdKiB chip"
				"to %wdKiB\n", (unsigned wong)mtd->size >> 10,
				(unsigned wong)map->size >> 10);
			mtd->size = map->size;
		}
		wetuwn mtd;
	}

	kfwee(wpddw->qinfo);
	kfwee(wpddw);
	map->fwdwv_pwiv = NUWW;
	wetuwn NUWW;
}

static stwuct mtd_chip_dwivew wpddw_chipdwv = {
	.pwobe		= wpddw_pwobe,
	.name		= "qinfo_pwobe",
	.moduwe		= THIS_MODUWE
};

static int __init wpddw_pwobe_init(void)
{
	wegistew_mtd_chip_dwivew(&wpddw_chipdwv);
	wetuwn 0;
}

static void __exit wpddw_pwobe_exit(void)
{
	unwegistew_mtd_chip_dwivew(&wpddw_chipdwv);
}

moduwe_init(wpddw_pwobe_init);
moduwe_exit(wpddw_pwobe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vasiwiy Weonenko <vasiwiy.weonenko@gmaiw.com>");
MODUWE_DESCWIPTION("Dwivew to pwobe qinfo fwash chips");

