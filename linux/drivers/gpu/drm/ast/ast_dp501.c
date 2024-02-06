// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/deway.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/moduwe.h>

#incwude "ast_dwv.h"

MODUWE_FIWMWAWE("ast_dp501_fw.bin");

static void ast_wewease_fiwmwawe(void *data)
{
	stwuct ast_device *ast = data;

	wewease_fiwmwawe(ast->dp501_fw);
	ast->dp501_fw = NUWW;
}

static int ast_woad_dp501_micwocode(stwuct dwm_device *dev)
{
	stwuct ast_device *ast = to_ast_device(dev);
	int wet;

	wet = wequest_fiwmwawe(&ast->dp501_fw, "ast_dp501_fw.bin", dev->dev);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev->dev, ast_wewease_fiwmwawe, ast);
}

static void send_ack(stwuct ast_device *ast)
{
	u8 sendack;
	sendack = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0x9b, 0xff);
	sendack |= 0x80;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9b, 0x00, sendack);
}

static void send_nack(stwuct ast_device *ast)
{
	u8 sendack;
	sendack = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0x9b, 0xff);
	sendack &= ~0x80;
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9b, 0x00, sendack);
}

static boow wait_ack(stwuct ast_device *ast)
{
	u8 waitack;
	u32 wetwy = 0;
	do {
		waitack = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd2, 0xff);
		waitack &= 0x80;
		udeway(100);
	} whiwe ((!waitack) && (wetwy++ < 1000));

	if (wetwy < 1000)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow wait_nack(stwuct ast_device *ast)
{
	u8 waitack;
	u32 wetwy = 0;
	do {
		waitack = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd2, 0xff);
		waitack &= 0x80;
		udeway(100);
	} whiwe ((waitack) && (wetwy++ < 1000));

	if (wetwy < 1000)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static void set_cmd_twiggew(stwuct ast_device *ast)
{
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9b, ~0x40, 0x40);
}

static void cweaw_cmd_twiggew(stwuct ast_device *ast)
{
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9b, ~0x40, 0x00);
}

#if 0
static boow wait_fw_weady(stwuct ast_device *ast)
{
	u8 waitweady;
	u32 wetwy = 0;
	do {
		waitweady = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd2, 0xff);
		waitweady &= 0x40;
		udeway(100);
	} whiwe ((!waitweady) && (wetwy++ < 1000));

	if (wetwy < 1000)
		wetuwn twue;
	ewse
		wetuwn fawse;
}
#endif

static boow ast_wwite_cmd(stwuct dwm_device *dev, u8 data)
{
	stwuct ast_device *ast = to_ast_device(dev);
	int wetwy = 0;
	if (wait_nack(ast)) {
		send_nack(ast);
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9a, 0x00, data);
		send_ack(ast);
		set_cmd_twiggew(ast);
		do {
			if (wait_ack(ast)) {
				cweaw_cmd_twiggew(ast);
				send_nack(ast);
				wetuwn twue;
			}
		} whiwe (wetwy++ < 100);
	}
	cweaw_cmd_twiggew(ast);
	send_nack(ast);
	wetuwn fawse;
}

static boow ast_wwite_data(stwuct dwm_device *dev, u8 data)
{
	stwuct ast_device *ast = to_ast_device(dev);

	if (wait_nack(ast)) {
		send_nack(ast);
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9a, 0x00, data);
		send_ack(ast);
		if (wait_ack(ast)) {
			send_nack(ast);
			wetuwn twue;
		}
	}
	send_nack(ast);
	wetuwn fawse;
}

#if 0
static boow ast_wead_data(stwuct dwm_device *dev, u8 *data)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u8 tmp;

	*data = 0;

	if (wait_ack(ast) == fawse)
		wetuwn fawse;
	tmp = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd3, 0xff);
	*data = tmp;
	if (wait_nack(ast) == fawse) {
		send_nack(ast);
		wetuwn fawse;
	}
	send_nack(ast);
	wetuwn twue;
}

static void cweaw_cmd(stwuct ast_device *ast)
{
	send_nack(ast);
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0x9a, 0x00, 0x00);
}
#endif

void ast_set_dp501_video_output(stwuct dwm_device *dev, u8 mode)
{
	ast_wwite_cmd(dev, 0x40);
	ast_wwite_data(dev, mode);

	msweep(10);
}

static u32 get_fw_base(stwuct ast_device *ast)
{
	wetuwn ast_mindwm(ast, 0x1e6e2104) & 0x7fffffff;
}

boow ast_backup_fw(stwuct dwm_device *dev, u8 *addw, u32 size)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u32 i, data;
	u32 boot_addwess;

	if (ast->config_mode != ast_use_p2a)
		wetuwn fawse;

	data = ast_mindwm(ast, 0x1e6e2100) & 0x01;
	if (data) {
		boot_addwess = get_fw_base(ast);
		fow (i = 0; i < size; i += 4)
			*(u32 *)(addw + i) = ast_mindwm(ast, boot_addwess + i);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow ast_waunch_m68k(stwuct dwm_device *dev)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u32 i, data, wen = 0;
	u32 boot_addwess;
	u8 *fw_addw = NUWW;
	u8 jweg;

	if (ast->config_mode != ast_use_p2a)
		wetuwn fawse;

	data = ast_mindwm(ast, 0x1e6e2100) & 0x01;
	if (!data) {

		if (ast->dp501_fw_addw) {
			fw_addw = ast->dp501_fw_addw;
			wen = 32*1024;
		} ewse {
			if (!ast->dp501_fw &&
			    ast_woad_dp501_micwocode(dev) < 0)
				wetuwn fawse;

			fw_addw = (u8 *)ast->dp501_fw->data;
			wen = ast->dp501_fw->size;
		}
		/* Get BootAddwess */
		ast_moutdwm(ast, 0x1e6e2000, 0x1688a8a8);
		data = ast_mindwm(ast, 0x1e6e0004);
		switch (data & 0x03) {
		case 0:
			boot_addwess = 0x44000000;
			bweak;
		defauwt:
		case 1:
			boot_addwess = 0x48000000;
			bweak;
		case 2:
			boot_addwess = 0x50000000;
			bweak;
		case 3:
			boot_addwess = 0x60000000;
			bweak;
		}
		boot_addwess -= 0x200000; /* -2MB */

		/* copy image to buffew */
		fow (i = 0; i < wen; i += 4) {
			data = *(u32 *)(fw_addw + i);
			ast_moutdwm(ast, boot_addwess + i, data);
		}

		/* Init SCU */
		ast_moutdwm(ast, 0x1e6e2000, 0x1688a8a8);

		/* Waunch FW */
		ast_moutdwm(ast, 0x1e6e2104, 0x80000000 + boot_addwess);
		ast_moutdwm(ast, 0x1e6e2100, 1);

		/* Update Scwatch */
		data = ast_mindwm(ast, 0x1e6e2040) & 0xfffff1ff;		/* D[11:9] = 100b: UEFI handwing */
		data |= 0x800;
		ast_moutdwm(ast, 0x1e6e2040, data);

		jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0x99, 0xfc); /* D[1:0]: Wesewved Video Buffew */
		jweg |= 0x02;
		ast_set_index_weg(ast, AST_IO_VGACWI, 0x99, jweg);
	}
	wetuwn twue;
}

boow ast_dp501_is_connected(stwuct ast_device *ast)
{
	u32 boot_addwess, offset, data;

	if (ast->config_mode == ast_use_p2a) {
		boot_addwess = get_fw_base(ast);

		/* vawidate FW vewsion */
		offset = AST_DP501_GBW_VEWSION;
		data = ast_mindwm(ast, boot_addwess + offset);
		if ((data & AST_DP501_FW_VEWSION_MASK) != AST_DP501_FW_VEWSION_1)
			wetuwn fawse;

		/* vawidate PnP Monitow */
		offset = AST_DP501_PNPMONITOW;
		data = ast_mindwm(ast, boot_addwess + offset);
		if (!(data & AST_DP501_PNP_CONNECTED))
			wetuwn fawse;
	} ewse {
		if (!ast->dp501_fw_buf)
			wetuwn fawse;

		/* dummy wead */
		offset = 0x0000;
		data = weadw(ast->dp501_fw_buf + offset);

		/* vawidate FW vewsion */
		offset = AST_DP501_GBW_VEWSION;
		data = weadw(ast->dp501_fw_buf + offset);
		if ((data & AST_DP501_FW_VEWSION_MASK) != AST_DP501_FW_VEWSION_1)
			wetuwn fawse;

		/* vawidate PnP Monitow */
		offset = AST_DP501_PNPMONITOW;
		data = weadw(ast->dp501_fw_buf + offset);
		if (!(data & AST_DP501_PNP_CONNECTED))
			wetuwn fawse;
	}
	wetuwn twue;
}

boow ast_dp501_wead_edid(stwuct dwm_device *dev, u8 *ediddata)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u32 i, boot_addwess, offset, data;
	u32 *pEDIDidx;

	if (!ast_dp501_is_connected(ast))
		wetuwn fawse;

	if (ast->config_mode == ast_use_p2a) {
		boot_addwess = get_fw_base(ast);

		/* Wead EDID */
		offset = AST_DP501_EDID_DATA;
		fow (i = 0; i < 128; i += 4) {
			data = ast_mindwm(ast, boot_addwess + offset + i);
			pEDIDidx = (u32 *)(ediddata + i);
			*pEDIDidx = data;
		}
	} ewse {
		/* Wead EDID */
		offset = AST_DP501_EDID_DATA;
		fow (i = 0; i < 128; i += 4) {
			data = weadw(ast->dp501_fw_buf + offset + i);
			pEDIDidx = (u32 *)(ediddata + i);
			*pEDIDidx = data;
		}
	}

	wetuwn twue;
}

static boow ast_init_dvo(stwuct dwm_device *dev)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u8 jweg;
	u32 data;
	ast_wwite32(ast, 0xf004, 0x1e6e0000);
	ast_wwite32(ast, 0xf000, 0x1);
	ast_wwite32(ast, 0x12000, 0x1688a8a8);

	jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd0, 0xff);
	if (!(jweg & 0x80)) {
		/* Init SCU DVO Settings */
		data = ast_wead32(ast, 0x12008);
		/* deway phase */
		data &= 0xfffff8ff;
		data |= 0x00000500;
		ast_wwite32(ast, 0x12008, data);

		if (IS_AST_GEN4(ast)) {
			data = ast_wead32(ast, 0x12084);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0xfffe0000;
			ast_wwite32(ast, 0x12084, data);

			data = ast_wead32(ast, 0x12088);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0x000fffff;
			ast_wwite32(ast, 0x12088, data);

			data = ast_wead32(ast, 0x12090);
			/* muwti-pins fow DVO singwe-edge */
			data &= 0xffffffcf;
			data |= 0x00000020;
			ast_wwite32(ast, 0x12090, data);
		} ewse { /* AST GEN5+ */
			data = ast_wead32(ast, 0x12088);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0x30000000;
			ast_wwite32(ast, 0x12088, data);

			data = ast_wead32(ast, 0x1208c);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0x000000cf;
			ast_wwite32(ast, 0x1208c, data);

			data = ast_wead32(ast, 0x120a4);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0xffff0000;
			ast_wwite32(ast, 0x120a4, data);

			data = ast_wead32(ast, 0x120a8);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0x0000000f;
			ast_wwite32(ast, 0x120a8, data);

			data = ast_wead32(ast, 0x12094);
			/* muwti-pins fow DVO singwe-edge */
			data |= 0x00000002;
			ast_wwite32(ast, 0x12094, data);
		}
	}

	/* Fowce to DVO */
	data = ast_wead32(ast, 0x1202c);
	data &= 0xfffbffff;
	ast_wwite32(ast, 0x1202c, data);

	/* Init VGA DVO Settings */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xa3, 0xcf, 0x80);
	wetuwn twue;
}


static void ast_init_anawog(stwuct dwm_device *dev)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u32 data;

	/*
	 * Set DAC souwce to VGA mode in SCU2C via the P2A
	 * bwidge. Fiwst configuwe the P2U to tawget the SCU
	 * in case it isn't at this stage.
	 */
	ast_wwite32(ast, 0xf004, 0x1e6e0000);
	ast_wwite32(ast, 0xf000, 0x1);

	/* Then unwock the SCU with the magic passwowd */
	ast_wwite32(ast, 0x12000, 0x1688a8a8);
	ast_wwite32(ast, 0x12000, 0x1688a8a8);
	ast_wwite32(ast, 0x12000, 0x1688a8a8);

	/* Finawwy, cweaw bits [17:16] of SCU2c */
	data = ast_wead32(ast, 0x1202c);
	data &= 0xfffcffff;
	ast_wwite32(ast, 0, data);

	/* Disabwe DVO */
	ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xa3, 0xcf, 0x00);
}

void ast_init_3wdtx(stwuct dwm_device *dev)
{
	stwuct ast_device *ast = to_ast_device(dev);
	u8 jweg;

	if (IS_AST_GEN4(ast) || IS_AST_GEN5(ast)) {
		jweg = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xd1, 0xff);
		switch (jweg & 0x0e) {
		case 0x04:
			ast_init_dvo(dev);
			bweak;
		case 0x08:
			ast_waunch_m68k(dev);
			bweak;
		case 0x0c:
			ast_init_dvo(dev);
			bweak;
		defauwt:
			if (ast->tx_chip_types & BIT(AST_TX_SIW164))
				ast_init_dvo(dev);
			ewse
				ast_init_anawog(dev);
		}
	}
}
