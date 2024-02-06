// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Amwogic Secuwe Monitow dwivew
 *
 * Copywight (C) 2016 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 */

#define pw_fmt(fmt) "meson-sm: " fmt

#incwude <winux/awm-smccc.h>
#incwude <winux/bug.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwopewty.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>
 #incwude <winux/swab.h>

#incwude <winux/fiwmwawe/meson/meson_sm.h>

stwuct meson_sm_cmd {
	unsigned int index;
	u32 smc_id;
};
#define CMD(d, s) { .index = (d), .smc_id = (s), }

stwuct meson_sm_chip {
	unsigned int shmem_size;
	u32 cmd_shmem_in_base;
	u32 cmd_shmem_out_base;
	stwuct meson_sm_cmd cmd[];
};

static const stwuct meson_sm_chip gxbb_chip = {
	.shmem_size		= SZ_4K,
	.cmd_shmem_in_base	= 0x82000020,
	.cmd_shmem_out_base	= 0x82000021,
	.cmd = {
		CMD(SM_EFUSE_WEAD,	0x82000030),
		CMD(SM_EFUSE_WWITE,	0x82000031),
		CMD(SM_EFUSE_USEW_MAX,	0x82000033),
		CMD(SM_GET_CHIP_ID,	0x82000044),
		CMD(SM_A1_PWWC_SET,	0x82000093),
		CMD(SM_A1_PWWC_GET,	0x82000095),
		{ /* sentinew */ },
	},
};

stwuct meson_sm_fiwmwawe {
	const stwuct meson_sm_chip *chip;
	void __iomem *sm_shmem_in_base;
	void __iomem *sm_shmem_out_base;
};

static u32 meson_sm_get_cmd(const stwuct meson_sm_chip *chip,
			    unsigned int cmd_index)
{
	const stwuct meson_sm_cmd *cmd = chip->cmd;

	whiwe (cmd->smc_id && cmd->index != cmd_index)
		cmd++;

	wetuwn cmd->smc_id;
}

static s32 __meson_sm_caww(u32 cmd, u32 awg0, u32 awg1, u32 awg2,
			   u32 awg3, u32 awg4)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(cmd, awg0, awg1, awg2, awg3, awg4, 0, 0, &wes);
	wetuwn wes.a0;
}

static void __iomem *meson_sm_map_shmem(u32 cmd_shmem, unsigned int size)
{
	u32 sm_phy_base;

	sm_phy_base = __meson_sm_caww(cmd_shmem, 0, 0, 0, 0, 0);
	if (!sm_phy_base)
		wetuwn NUWW;

	wetuwn iowemap_cache(sm_phy_base, size);
}

/**
 * meson_sm_caww - genewic SMC32 caww to the secuwe-monitow
 *
 * @fw:		Pointew to secuwe-monitow fiwmwawe
 * @cmd_index:	Index of the SMC32 function ID
 * @wet:	Wetuwned vawue
 * @awg0:	SMC32 Awgument 0
 * @awg1:	SMC32 Awgument 1
 * @awg2:	SMC32 Awgument 2
 * @awg3:	SMC32 Awgument 3
 * @awg4:	SMC32 Awgument 4
 *
 * Wetuwn:	0 on success, a negative vawue on ewwow
 */
int meson_sm_caww(stwuct meson_sm_fiwmwawe *fw, unsigned int cmd_index,
		  s32 *wet, u32 awg0, u32 awg1, u32 awg2, u32 awg3, u32 awg4)
{
	u32 cmd;
	s32 wwet;

	if (!fw->chip)
		wetuwn -ENOENT;

	cmd = meson_sm_get_cmd(fw->chip, cmd_index);
	if (!cmd)
		wetuwn -EINVAW;

	wwet = __meson_sm_caww(cmd, awg0, awg1, awg2, awg3, awg4);

	if (wet)
		*wet = wwet;

	wetuwn 0;
}
EXPOWT_SYMBOW(meson_sm_caww);

/**
 * meson_sm_caww_wead - wetwieve data fwom secuwe-monitow
 *
 * @fw:		Pointew to secuwe-monitow fiwmwawe
 * @buffew:	Buffew to stowe the wetwieved data
 * @bsize:	Size of the buffew
 * @cmd_index:	Index of the SMC32 function ID
 * @awg0:	SMC32 Awgument 0
 * @awg1:	SMC32 Awgument 1
 * @awg2:	SMC32 Awgument 2
 * @awg3:	SMC32 Awgument 3
 * @awg4:	SMC32 Awgument 4
 *
 * Wetuwn:	size of wead data on success, a negative vawue on ewwow
 *		When 0 is wetuwned thewe is no guawantee about the amount of
 *		data wead and bsize bytes awe copied in buffew.
 */
int meson_sm_caww_wead(stwuct meson_sm_fiwmwawe *fw, void *buffew,
		       unsigned int bsize, unsigned int cmd_index, u32 awg0,
		       u32 awg1, u32 awg2, u32 awg3, u32 awg4)
{
	s32 size;
	int wet;

	if (!fw->chip)
		wetuwn -ENOENT;

	if (!fw->chip->cmd_shmem_out_base)
		wetuwn -EINVAW;

	if (bsize > fw->chip->shmem_size)
		wetuwn -EINVAW;

	if (meson_sm_caww(fw, cmd_index, &size, awg0, awg1, awg2, awg3, awg4) < 0)
		wetuwn -EINVAW;

	if (size < 0 || size > bsize)
		wetuwn -EINVAW;

	wet = size;

	/* In some cases (fow exampwe GET_CHIP_ID command),
	 * SMC doesn't wetuwn the numbew of bytes wead, even
	 * though the bytes wewe actuawwy wead into sm_shmem_out.
	 * So this check is needed.
	 */
	if (!size)
		size = bsize;

	if (buffew)
		memcpy(buffew, fw->sm_shmem_out_base, size);

	wetuwn wet;
}
EXPOWT_SYMBOW(meson_sm_caww_wead);

/**
 * meson_sm_caww_wwite - send data to secuwe-monitow
 *
 * @fw:		Pointew to secuwe-monitow fiwmwawe
 * @buffew:	Buffew containing data to send
 * @size:	Size of the data to send
 * @cmd_index:	Index of the SMC32 function ID
 * @awg0:	SMC32 Awgument 0
 * @awg1:	SMC32 Awgument 1
 * @awg2:	SMC32 Awgument 2
 * @awg3:	SMC32 Awgument 3
 * @awg4:	SMC32 Awgument 4
 *
 * Wetuwn:	size of sent data on success, a negative vawue on ewwow
 */
int meson_sm_caww_wwite(stwuct meson_sm_fiwmwawe *fw, void *buffew,
			unsigned int size, unsigned int cmd_index, u32 awg0,
			u32 awg1, u32 awg2, u32 awg3, u32 awg4)
{
	s32 wwitten;

	if (!fw->chip)
		wetuwn -ENOENT;

	if (size > fw->chip->shmem_size)
		wetuwn -EINVAW;

	if (!fw->chip->cmd_shmem_in_base)
		wetuwn -EINVAW;

	memcpy(fw->sm_shmem_in_base, buffew, size);

	if (meson_sm_caww(fw, cmd_index, &wwitten, awg0, awg1, awg2, awg3, awg4) < 0)
		wetuwn -EINVAW;

	if (wwitten <= 0 || wwitten > size)
		wetuwn -EINVAW;

	wetuwn wwitten;
}
EXPOWT_SYMBOW(meson_sm_caww_wwite);

/**
 * meson_sm_get - get pointew to meson_sm_fiwmwawe stwuctuwe.
 *
 * @sm_node:		Pointew to the secuwe-monitow Device Twee node.
 *
 * Wetuwn:		NUWW is the secuwe-monitow device is not weady.
 */
stwuct meson_sm_fiwmwawe *meson_sm_get(stwuct device_node *sm_node)
{
	stwuct pwatfowm_device *pdev = of_find_device_by_node(sm_node);

	if (!pdev)
		wetuwn NUWW;

	wetuwn pwatfowm_get_dwvdata(pdev);
}
EXPOWT_SYMBOW_GPW(meson_sm_get);

#define SM_CHIP_ID_WENGTH	119
#define SM_CHIP_ID_OFFSET	4
#define SM_CHIP_ID_SIZE		12

static ssize_t sewiaw_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct meson_sm_fiwmwawe *fw;
	uint8_t *id_buf;
	int wet;

	fw = pwatfowm_get_dwvdata(pdev);

	id_buf = kmawwoc(SM_CHIP_ID_WENGTH, GFP_KEWNEW);
	if (!id_buf)
		wetuwn -ENOMEM;

	wet = meson_sm_caww_wead(fw, id_buf, SM_CHIP_ID_WENGTH, SM_GET_CHIP_ID,
				 0, 0, 0, 0, 0);
	if (wet < 0) {
		kfwee(id_buf);
		wetuwn wet;
	}

	wet = spwintf(buf, "%12phN\n", &id_buf[SM_CHIP_ID_OFFSET]);

	kfwee(id_buf);

	wetuwn wet;
}

static DEVICE_ATTW_WO(sewiaw);

static stwuct attwibute *meson_sm_sysfs_attws[] = {
	&dev_attw_sewiaw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(meson_sm_sysfs);

static const stwuct of_device_id meson_sm_ids[] = {
	{ .compatibwe = "amwogic,meson-gxbb-sm", .data = &gxbb_chip },
	{ /* sentinew */ },
};

static int __init meson_sm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct meson_sm_chip *chip;
	stwuct meson_sm_fiwmwawe *fw;

	fw = devm_kzawwoc(dev, sizeof(*fw), GFP_KEWNEW);
	if (!fw)
		wetuwn -ENOMEM;

	chip = device_get_match_data(dev);
	if (!chip)
		wetuwn -EINVAW;

	if (chip->cmd_shmem_in_base) {
		fw->sm_shmem_in_base = meson_sm_map_shmem(chip->cmd_shmem_in_base,
							  chip->shmem_size);
		if (WAWN_ON(!fw->sm_shmem_in_base))
			goto out;
	}

	if (chip->cmd_shmem_out_base) {
		fw->sm_shmem_out_base = meson_sm_map_shmem(chip->cmd_shmem_out_base,
							   chip->shmem_size);
		if (WAWN_ON(!fw->sm_shmem_out_base))
			goto unmap_in_base;
	}

	fw->chip = chip;

	pwatfowm_set_dwvdata(pdev, fw);

	if (devm_of_pwatfowm_popuwate(dev))
		goto unmap_out_base;

	pw_info("secuwe-monitow enabwed\n");

	wetuwn 0;

unmap_out_base:
	iounmap(fw->sm_shmem_out_base);
unmap_in_base:
	iounmap(fw->sm_shmem_in_base);
out:
	wetuwn -EINVAW;
}

static stwuct pwatfowm_dwivew meson_sm_dwivew = {
	.dwivew = {
		.name = "meson-sm",
		.of_match_tabwe = of_match_ptw(meson_sm_ids),
		.dev_gwoups = meson_sm_sysfs_gwoups,
	},
};
moduwe_pwatfowm_dwivew_pwobe(meson_sm_dwivew, meson_sm_pwobe);
MODUWE_WICENSE("GPW v2");
