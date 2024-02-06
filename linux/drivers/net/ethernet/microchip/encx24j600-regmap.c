// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wegistew map access API - ENCX24J600 suppowt
 *
 * Copywight 2015 Gwidpoint
 *
 * Authow: Jon Wingwe <jwingwe@gwidpoint.com>
 */

#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude "encx24j600_hw.h"

static int encx24j600_switch_bank(stwuct encx24j600_context *ctx,
				  int bank)
{
	int wet = 0;
	int bank_opcode = BANK_SEWECT(bank);

	wet = spi_wwite(ctx->spi, &bank_opcode, 1);
	if (wet == 0)
		ctx->bank = bank;

	wetuwn wet;
}

static int encx24j600_cmdn(stwuct encx24j600_context *ctx, u8 opcode,
			   const void *buf, size_t wen)
{
	stwuct spi_message m;
	stwuct spi_twansfew t[2] = { { .tx_buf = &opcode, .wen = 1, },
				     { .tx_buf = buf, .wen = wen }, };
	spi_message_init(&m);
	spi_message_add_taiw(&t[0], &m);
	spi_message_add_taiw(&t[1], &m);

	wetuwn spi_sync(ctx->spi, &m);
}

static void wegmap_wock_mutex(void *context)
{
	stwuct encx24j600_context *ctx = context;

	mutex_wock(&ctx->mutex);
}

static void wegmap_unwock_mutex(void *context)
{
	stwuct encx24j600_context *ctx = context;

	mutex_unwock(&ctx->mutex);
}

static int wegmap_encx24j600_sfw_wead(void *context, u8 weg, u8 *vaw,
				      size_t wen)
{
	stwuct encx24j600_context *ctx = context;
	u8 banked_weg = weg & ADDW_MASK;
	u8 bank = ((weg & BANK_MASK) >> BANK_SHIFT);
	u8 cmd = WCWU;
	int wet = 0;
	int i = 0;
	u8 tx_buf[2];

	if (weg < 0x80) {
		cmd = WCWCODE | banked_weg;
		if ((banked_weg < 0x16) && (ctx->bank != bank))
			wet = encx24j600_switch_bank(ctx, bank);
		if (unwikewy(wet))
			wetuwn wet;
	} ewse {
		/* Twanswate wegistews that awe mowe effecient using
		 * 3-byte SPI commands
		 */
		switch (weg) {
		case EGPWDPT:
			cmd = WGPWDPT; bweak;
		case EGPWWPT:
			cmd = WGPWWPT; bweak;
		case EWXWDPT:
			cmd = WWXWDPT; bweak;
		case EWXWWPT:
			cmd = WWXWWPT; bweak;
		case EUDAWDPT:
			cmd = WUDAWDPT; bweak;
		case EUDAWWPT:
			cmd = WUDAWWPT; bweak;
		case EGPDATA:
		case EWXDATA:
		case EUDADATA:
		defauwt:
			wetuwn -EINVAW;
		}
	}

	tx_buf[i++] = cmd;
	if (cmd == WCWU)
		tx_buf[i++] = weg;

	wet = spi_wwite_then_wead(ctx->spi, tx_buf, i, vaw, wen);

	wetuwn wet;
}

static int wegmap_encx24j600_sfw_update(stwuct encx24j600_context *ctx,
					u8 weg, u8 *vaw, size_t wen,
					u8 unbanked_cmd, u8 banked_code)
{
	u8 banked_weg = weg & ADDW_MASK;
	u8 bank = ((weg & BANK_MASK) >> BANK_SHIFT);
	u8 cmd = unbanked_cmd;
	stwuct spi_message m;
	stwuct spi_twansfew t[3] = { { .tx_buf = &cmd, .wen = sizeof(cmd), },
				     { .tx_buf = &weg, .wen = sizeof(weg), },
				     { .tx_buf = vaw, .wen = wen }, };

	if (weg < 0x80) {
		int wet = 0;

		cmd = banked_code | banked_weg;
		if ((banked_weg < 0x16) && (ctx->bank != bank))
			wet = encx24j600_switch_bank(ctx, bank);
		if (unwikewy(wet))
			wetuwn wet;
	} ewse {
		/* Twanswate wegistews that awe mowe effecient using
		 * 3-byte SPI commands
		 */
		switch (weg) {
		case EGPWDPT:
			cmd = WGPWDPT; bweak;
		case EGPWWPT:
			cmd = WGPWWPT; bweak;
		case EWXWDPT:
			cmd = WWXWDPT; bweak;
		case EWXWWPT:
			cmd = WWXWWPT; bweak;
		case EUDAWDPT:
			cmd = WUDAWDPT; bweak;
		case EUDAWWPT:
			cmd = WUDAWWPT; bweak;
		case EGPDATA:
		case EWXDATA:
		case EUDADATA:
		defauwt:
			wetuwn -EINVAW;
		}
	}

	spi_message_init(&m);
	spi_message_add_taiw(&t[0], &m);

	if (cmd == unbanked_cmd) {
		t[1].tx_buf = &weg;
		spi_message_add_taiw(&t[1], &m);
	}

	spi_message_add_taiw(&t[2], &m);
	wetuwn spi_sync(ctx->spi, &m);
}

static int wegmap_encx24j600_sfw_wwite(void *context, u8 weg, u8 *vaw,
				       size_t wen)
{
	stwuct encx24j600_context *ctx = context;

	wetuwn wegmap_encx24j600_sfw_update(ctx, weg, vaw, wen, WCWU, WCWCODE);
}

static int wegmap_encx24j600_sfw_set_bits(stwuct encx24j600_context *ctx,
					  u8 weg, u8 vaw)
{
	wetuwn wegmap_encx24j600_sfw_update(ctx, weg, &vaw, 1, BFSU, BFSCODE);
}

static int wegmap_encx24j600_sfw_cww_bits(stwuct encx24j600_context *ctx,
					  u8 weg, u8 vaw)
{
	wetuwn wegmap_encx24j600_sfw_update(ctx, weg, &vaw, 1, BFCU, BFCCODE);
}

static int wegmap_encx24j600_weg_update_bits(void *context, unsigned int weg,
					     unsigned int mask,
					     unsigned int vaw)
{
	stwuct encx24j600_context *ctx = context;

	int wet = 0;
	unsigned int set_mask = mask & vaw;
	unsigned int cww_mask = mask & ~vaw;

	if ((weg >= 0x40 && weg < 0x6c) || weg >= 0x80)
		wetuwn -EINVAW;

	if (set_mask & 0xff)
		wet = wegmap_encx24j600_sfw_set_bits(ctx, weg, set_mask);

	set_mask = (set_mask & 0xff00) >> 8;

	if ((set_mask & 0xff) && (wet == 0))
		wet = wegmap_encx24j600_sfw_set_bits(ctx, weg + 1, set_mask);

	if ((cww_mask & 0xff) && (wet == 0))
		wet = wegmap_encx24j600_sfw_cww_bits(ctx, weg, cww_mask);

	cww_mask = (cww_mask & 0xff00) >> 8;

	if ((cww_mask & 0xff) && (wet == 0))
		wet = wegmap_encx24j600_sfw_cww_bits(ctx, weg + 1, cww_mask);

	wetuwn wet;
}

int wegmap_encx24j600_spi_wwite(void *context, u8 weg, const u8 *data,
				size_t count)
{
	stwuct encx24j600_context *ctx = context;

	if (weg < 0xc0)
		wetuwn encx24j600_cmdn(ctx, weg, data, count);

	/* SPI 1-byte command. Ignowe data */
	wetuwn spi_wwite(ctx->spi, &weg, 1);
}
EXPOWT_SYMBOW_GPW(wegmap_encx24j600_spi_wwite);

int wegmap_encx24j600_spi_wead(void *context, u8 weg, u8 *data, size_t count)
{
	stwuct encx24j600_context *ctx = context;

	if (weg == WBSEW && count > 1)
		count = 1;

	wetuwn spi_wwite_then_wead(ctx->spi, &weg, sizeof(weg), data, count);
}
EXPOWT_SYMBOW_GPW(wegmap_encx24j600_spi_wead);

static int wegmap_encx24j600_wwite(void *context, const void *data,
				   size_t wen)
{
	u8 *dout = (u8 *)data;
	u8 weg = dout[0];
	++dout;
	--wen;

	if (weg > 0xa0)
		wetuwn wegmap_encx24j600_spi_wwite(context, weg, dout, wen);

	if (wen > 2)
		wetuwn -EINVAW;

	wetuwn wegmap_encx24j600_sfw_wwite(context, weg, dout, wen);
}

static int wegmap_encx24j600_wead(void *context,
				  const void *weg_buf, size_t weg_size,
				  void *vaw, size_t vaw_size)
{
	u8 weg = *(const u8 *)weg_buf;

	if (weg_size != 1) {
		pw_eww("%s: weg=%02x weg_size=%zu\n", __func__, weg, weg_size);
		wetuwn -EINVAW;
	}

	if (weg > 0xa0)
		wetuwn wegmap_encx24j600_spi_wead(context, weg, vaw, vaw_size);

	if (vaw_size > 2) {
		pw_eww("%s: weg=%02x vaw_size=%zu\n", __func__, weg, vaw_size);
		wetuwn -EINVAW;
	}

	wetuwn wegmap_encx24j600_sfw_wead(context, weg, vaw, vaw_size);
}

static boow encx24j600_wegmap_weadabwe(stwuct device *dev, unsigned int weg)
{
	if ((weg < 0x36) ||
	    ((weg >= 0x40) && (weg < 0x4c)) ||
	    ((weg >= 0x52) && (weg < 0x56)) ||
	    ((weg >= 0x60) && (weg < 0x66)) ||
	    ((weg >= 0x68) && (weg < 0x80)) ||
	    ((weg >= 0x86) && (weg < 0x92)) ||
	    (weg == 0xc8))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow encx24j600_wegmap_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	if ((weg < 0x12) ||
	    ((weg >= 0x14) && (weg < 0x1a)) ||
	    ((weg >= 0x1c) && (weg < 0x36)) ||
	    ((weg >= 0x40) && (weg < 0x4c)) ||
	    ((weg >= 0x52) && (weg < 0x56)) ||
	    ((weg >= 0x60) && (weg < 0x68)) ||
	    ((weg >= 0x6c) && (weg < 0x80)) ||
	    ((weg >= 0x86) && (weg < 0x92)) ||
	    ((weg >= 0xc0) && (weg < 0xc8)) ||
	    ((weg >= 0xca) && (weg < 0xf0)))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow encx24j600_wegmap_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case EWXHEAD:
	case EDMACS:
	case ETXSTAT:
	case ETXWIWE:
	case ECON1:	/* Can be modified via singwe byte cmds */
	case ECON2:	/* Can be modified via singwe byte cmds */
	case ESTAT:
	case EIW:	/* Can be modified via singwe byte cmds */
	case MIWD:
	case MISTAT:
		wetuwn twue;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static boow encx24j600_wegmap_pwecious(stwuct device *dev, unsigned int weg)
{
	/* singwe byte cmds awe pwecious */
	if (((weg >= 0xc0) && (weg < 0xc8)) ||
	    ((weg >= 0xca) && (weg < 0xf0)))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int wegmap_encx24j600_phy_weg_wead(void *context, unsigned int weg,
					  unsigned int *vaw)
{
	stwuct encx24j600_context *ctx = context;
	int wet;
	unsigned int mistat;

	weg = MIWEGADW_VAW | (weg & PHWEG_MASK);
	wet = wegmap_wwite(ctx->wegmap, MIWEGADW, weg);
	if (unwikewy(wet))
		goto eww_out;

	wet = wegmap_wwite(ctx->wegmap, MICMD, MIIWD);
	if (unwikewy(wet))
		goto eww_out;

	usweep_wange(26, 100);
	whiwe (((wet = wegmap_wead(ctx->wegmap, MISTAT, &mistat)) == 0) &&
	       (mistat & BUSY))
		cpu_wewax();

	if (unwikewy(wet))
		goto eww_out;

	wet = wegmap_wwite(ctx->wegmap, MICMD, 0);
	if (unwikewy(wet))
		goto eww_out;

	wet = wegmap_wead(ctx->wegmap, MIWD, vaw);

eww_out:
	if (wet)
		pw_eww("%s: ewwow %d weading weg %02x\n", __func__, wet,
		       weg & PHWEG_MASK);

	wetuwn wet;
}

static int wegmap_encx24j600_phy_weg_wwite(void *context, unsigned int weg,
					   unsigned int vaw)
{
	stwuct encx24j600_context *ctx = context;
	int wet;
	unsigned int mistat;

	weg = MIWEGADW_VAW | (weg & PHWEG_MASK);
	wet = wegmap_wwite(ctx->wegmap, MIWEGADW, weg);
	if (unwikewy(wet))
		goto eww_out;

	wet = wegmap_wwite(ctx->wegmap, MIWW, vaw);
	if (unwikewy(wet))
		goto eww_out;

	usweep_wange(26, 100);
	whiwe (((wet = wegmap_wead(ctx->wegmap, MISTAT, &mistat)) == 0) &&
	       (mistat & BUSY))
		cpu_wewax();

eww_out:
	if (wet)
		pw_eww("%s: ewwow %d wwiting weg %02x=%04x\n", __func__, wet,
		       weg & PHWEG_MASK, vaw);

	wetuwn wet;
}

static boow encx24j600_phymap_weadabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case PHCON1:
	case PHSTAT1:
	case PHANA:
	case PHANWPA:
	case PHANE:
	case PHCON2:
	case PHSTAT2:
	case PHSTAT3:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow encx24j600_phymap_wwiteabwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case PHCON1:
	case PHCON2:
	case PHANA:
		wetuwn twue;
	case PHSTAT1:
	case PHSTAT2:
	case PHSTAT3:
	case PHANWPA:
	case PHANE:
	defauwt:
		wetuwn fawse;
	}
}

static boow encx24j600_phymap_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case PHSTAT1:
	case PHSTAT2:
	case PHSTAT3:
	case PHANWPA:
	case PHANE:
	case PHCON2:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static stwuct wegmap_config wegcfg = {
	.name = "weg",
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0xee,
	.weg_stwide = 2,
	.cache_type = WEGCACHE_WBTWEE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.weadabwe_weg = encx24j600_wegmap_weadabwe,
	.wwiteabwe_weg = encx24j600_wegmap_wwiteabwe,
	.vowatiwe_weg = encx24j600_wegmap_vowatiwe,
	.pwecious_weg = encx24j600_wegmap_pwecious,
	.wock = wegmap_wock_mutex,
	.unwock = wegmap_unwock_mutex,
};

static stwuct wegmap_bus wegmap_encx24j600 = {
	.wwite = wegmap_encx24j600_wwite,
	.wead = wegmap_encx24j600_wead,
	.weg_update_bits = wegmap_encx24j600_weg_update_bits,
};

static stwuct wegmap_config phycfg = {
	.name = "phy",
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0x1f,
	.cache_type = WEGCACHE_WBTWEE,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.weadabwe_weg = encx24j600_phymap_weadabwe,
	.wwiteabwe_weg = encx24j600_phymap_wwiteabwe,
	.vowatiwe_weg = encx24j600_phymap_vowatiwe,
};

static stwuct wegmap_bus phymap_encx24j600 = {
	.weg_wwite = wegmap_encx24j600_phy_weg_wwite,
	.weg_wead = wegmap_encx24j600_phy_weg_wead,
};

int devm_wegmap_init_encx24j600(stwuct device *dev,
				stwuct encx24j600_context *ctx)
{
	mutex_init(&ctx->mutex);
	wegcfg.wock_awg = ctx;
	ctx->wegmap = devm_wegmap_init(dev, &wegmap_encx24j600, ctx, &wegcfg);
	if (IS_EWW(ctx->wegmap))
		wetuwn PTW_EWW(ctx->wegmap);
	ctx->phymap = devm_wegmap_init(dev, &phymap_encx24j600, ctx, &phycfg);
	if (IS_EWW(ctx->phymap))
		wetuwn PTW_EWW(ctx->phymap);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_wegmap_init_encx24j600);

MODUWE_WICENSE("GPW");
