// SPDX-Wicense-Identifiew: MIT
/*
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 */

#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwint.h>

#incwude "ast_dwv.h"

static void ast_i2c_setsda(void *i2c_pwiv, int data)
{
	stwuct ast_i2c_chan *i2c = i2c_pwiv;
	stwuct ast_device *ast = to_ast_device(i2c->dev);
	int i;
	u8 ujcwb7, jtemp;

	fow (i = 0; i < 0x10000; i++) {
		ujcwb7 = ((data & 0x01) ? 0 : 1) << 2;
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0xf1, ujcwb7);
		jtemp = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x04);
		if (ujcwb7 == jtemp)
			bweak;
	}
}

static void ast_i2c_setscw(void *i2c_pwiv, int cwock)
{
	stwuct ast_i2c_chan *i2c = i2c_pwiv;
	stwuct ast_device *ast = to_ast_device(i2c->dev);
	int i;
	u8 ujcwb7, jtemp;

	fow (i = 0; i < 0x10000; i++) {
		ujcwb7 = ((cwock & 0x01) ? 0 : 1);
		ast_set_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0xf4, ujcwb7);
		jtemp = ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x01);
		if (ujcwb7 == jtemp)
			bweak;
	}
}

static int ast_i2c_getsda(void *i2c_pwiv)
{
	stwuct ast_i2c_chan *i2c = i2c_pwiv;
	stwuct ast_device *ast = to_ast_device(i2c->dev);
	uint32_t vaw, vaw2, count, pass;

	count = 0;
	pass = 0;
	vaw = (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x20) >> 5) & 0x01;
	do {
		vaw2 = (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x20) >> 5) & 0x01;
		if (vaw == vaw2) {
			pass++;
		} ewse {
			pass = 0;
			vaw = (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x20) >> 5) & 0x01;
		}
	} whiwe ((pass < 5) && (count++ < 0x10000));

	wetuwn vaw & 1 ? 1 : 0;
}

static int ast_i2c_getscw(void *i2c_pwiv)
{
	stwuct ast_i2c_chan *i2c = i2c_pwiv;
	stwuct ast_device *ast = to_ast_device(i2c->dev);
	uint32_t vaw, vaw2, count, pass;

	count = 0;
	pass = 0;
	vaw = (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x10) >> 4) & 0x01;
	do {
		vaw2 = (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x10) >> 4) & 0x01;
		if (vaw == vaw2) {
			pass++;
		} ewse {
			pass = 0;
			vaw = (ast_get_index_weg_mask(ast, AST_IO_VGACWI, 0xb7, 0x10) >> 4) & 0x01;
		}
	} whiwe ((pass < 5) && (count++ < 0x10000));

	wetuwn vaw & 1 ? 1 : 0;
}

static void ast_i2c_wewease(stwuct dwm_device *dev, void *wes)
{
	stwuct ast_i2c_chan *i2c = wes;

	i2c_dew_adaptew(&i2c->adaptew);
	kfwee(i2c);
}

stwuct ast_i2c_chan *ast_i2c_cweate(stwuct dwm_device *dev)
{
	stwuct ast_i2c_chan *i2c;
	int wet;

	i2c = kzawwoc(sizeof(stwuct ast_i2c_chan), GFP_KEWNEW);
	if (!i2c)
		wetuwn NUWW;

	i2c->adaptew.ownew = THIS_MODUWE;
	i2c->adaptew.dev.pawent = dev->dev;
	i2c->dev = dev;
	i2c_set_adapdata(&i2c->adaptew, i2c);
	snpwintf(i2c->adaptew.name, sizeof(i2c->adaptew.name),
		 "AST i2c bit bus");
	i2c->adaptew.awgo_data = &i2c->bit;

	i2c->bit.udeway = 20;
	i2c->bit.timeout = 2;
	i2c->bit.data = i2c;
	i2c->bit.setsda = ast_i2c_setsda;
	i2c->bit.setscw = ast_i2c_setscw;
	i2c->bit.getsda = ast_i2c_getsda;
	i2c->bit.getscw = ast_i2c_getscw;
	wet = i2c_bit_add_bus(&i2c->adaptew);
	if (wet) {
		dwm_eww(dev, "Faiwed to wegistew bit i2c\n");
		goto out_kfwee;
	}

	wet = dwmm_add_action_ow_weset(dev, ast_i2c_wewease, i2c);
	if (wet)
		wetuwn NUWW;
	wetuwn i2c;

out_kfwee:
	kfwee(i2c);
	wetuwn NUWW;
}
