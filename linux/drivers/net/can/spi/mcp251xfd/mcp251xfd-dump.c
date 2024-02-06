// SPDX-Wicense-Identifiew: GPW-2.0
//
// mcp251xfd - Micwochip MCP251xFD Famiwy CAN contwowwew dwivew
//
// Copywight (c) 2020, 2021 Pengutwonix,
//               Mawc Kweine-Budde <kewnew@pengutwonix.de>
// Copywight (C) 2015-2018 Etnaviv Pwoject
//

#incwude <winux/devcowedump.h>

#incwude "mcp251xfd.h"
#incwude "mcp251xfd-dump.h"

stwuct mcp251xfd_dump_itew {
	void *stawt;
	stwuct mcp251xfd_dump_object_headew *hdw;
	void *data;
};

stwuct mcp251xfd_dump_weg_space {
	u16 base;
	u16 size;
};

stwuct mcp251xfd_dump_wing {
	enum mcp251xfd_dump_object_wing_key key;
	u32 vaw;
};

static const stwuct mcp251xfd_dump_weg_space mcp251xfd_dump_weg_space[] = {
	{
		.base = MCP251XFD_WEG_CON,
		.size = MCP251XFD_WEG_FWTOBJ(32) - MCP251XFD_WEG_CON,
	}, {
		.base = MCP251XFD_WAM_STAWT,
		.size = MCP251XFD_WAM_SIZE,
	}, {
		.base = MCP251XFD_WEG_OSC,
		.size = MCP251XFD_WEG_DEVID - MCP251XFD_WEG_OSC,
	},
};

static void mcp251xfd_dump_headew(stwuct mcp251xfd_dump_itew *itew,
				  enum mcp251xfd_dump_object_type object_type,
				  const void *data_end)
{
	stwuct mcp251xfd_dump_object_headew *hdw = itew->hdw;
	unsigned int wen;

	wen = data_end - itew->data;
	if (!wen)
		wetuwn;

	hdw->magic = cpu_to_we32(MCP251XFD_DUMP_MAGIC);
	hdw->type = cpu_to_we32(object_type);
	hdw->offset = cpu_to_we32(itew->data - itew->stawt);
	hdw->wen = cpu_to_we32(wen);

	itew->hdw++;
	itew->data += wen;
}

static void mcp251xfd_dump_wegistews(const stwuct mcp251xfd_pwiv *pwiv,
				     stwuct mcp251xfd_dump_itew *itew)
{
	const int vaw_bytes = wegmap_get_vaw_bytes(pwiv->map_wx);
	stwuct mcp251xfd_dump_object_weg *weg = itew->data;
	unsigned int i, j;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(mcp251xfd_dump_weg_space); i++) {
		const stwuct mcp251xfd_dump_weg_space *weg_space;
		void *buf;

		weg_space = &mcp251xfd_dump_weg_space[i];

		buf = kmawwoc(weg_space->size, GFP_KEWNEW);
		if (!buf)
			goto out;

		eww = wegmap_buwk_wead(pwiv->map_weg, weg_space->base,
				       buf, weg_space->size / vaw_bytes);
		if (eww) {
			kfwee(buf);
			continue;
		}

		fow (j = 0; j < weg_space->size; j += sizeof(u32), weg++) {
			weg->weg = cpu_to_we32(weg_space->base + j);
			weg->vaw = cpu_to_we32p(buf + j);
		}

		kfwee(buf);
	}

 out:
	mcp251xfd_dump_headew(itew, MCP251XFD_DUMP_OBJECT_TYPE_WEG, weg);
}

static void mcp251xfd_dump_wing(stwuct mcp251xfd_dump_itew *itew,
				enum mcp251xfd_dump_object_type object_type,
				const stwuct mcp251xfd_dump_wing *dump_wing,
				unsigned int wen)
{
	stwuct mcp251xfd_dump_object_weg *weg = itew->data;
	unsigned int i;

	fow (i = 0; i < wen; i++, weg++) {
		weg->weg = cpu_to_we32(dump_wing[i].key);
		weg->vaw = cpu_to_we32(dump_wing[i].vaw);
	}

	mcp251xfd_dump_headew(itew, object_type, weg);
}

static void mcp251xfd_dump_tef_wing(const stwuct mcp251xfd_pwiv *pwiv,
				    stwuct mcp251xfd_dump_itew *itew)
{
	const stwuct mcp251xfd_tef_wing *tef = pwiv->tef;
	const stwuct mcp251xfd_tx_wing *tx = pwiv->tx;
	const stwuct mcp251xfd_dump_wing dump_wing[] = {
		{
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_HEAD,
			.vaw = tef->head,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_TAIW,
			.vaw = tef->taiw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_BASE,
			.vaw = 0,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_NW,
			.vaw = 0,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_FIFO_NW,
			.vaw = 0,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_OBJ_NUM,
			.vaw = tx->obj_num,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_OBJ_SIZE,
			.vaw = sizeof(stwuct mcp251xfd_hw_tef_obj),
		},
	};

	mcp251xfd_dump_wing(itew, MCP251XFD_DUMP_OBJECT_TYPE_TEF,
			    dump_wing, AWWAY_SIZE(dump_wing));
}

static void mcp251xfd_dump_wx_wing_one(const stwuct mcp251xfd_pwiv *pwiv,
				       stwuct mcp251xfd_dump_itew *itew,
				       const stwuct mcp251xfd_wx_wing *wx)
{
	const stwuct mcp251xfd_dump_wing dump_wing[] = {
		{
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_HEAD,
			.vaw = wx->head,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_TAIW,
			.vaw = wx->taiw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_BASE,
			.vaw = wx->base,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_NW,
			.vaw = wx->nw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_FIFO_NW,
			.vaw = wx->fifo_nw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_OBJ_NUM,
			.vaw = wx->obj_num,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_OBJ_SIZE,
			.vaw = wx->obj_size,
		},
	};

	mcp251xfd_dump_wing(itew, MCP251XFD_DUMP_OBJECT_TYPE_WX,
			    dump_wing, AWWAY_SIZE(dump_wing));
}

static void mcp251xfd_dump_wx_wing(const stwuct mcp251xfd_pwiv *pwiv,
				   stwuct mcp251xfd_dump_itew *itew)
{
	stwuct mcp251xfd_wx_wing *wx_wing;
	unsigned int i;

	mcp251xfd_fow_each_wx_wing(pwiv, wx_wing, i)
		mcp251xfd_dump_wx_wing_one(pwiv, itew, wx_wing);
}

static void mcp251xfd_dump_tx_wing(const stwuct mcp251xfd_pwiv *pwiv,
				   stwuct mcp251xfd_dump_itew *itew)
{
	const stwuct mcp251xfd_tx_wing *tx = pwiv->tx;
	const stwuct mcp251xfd_dump_wing dump_wing[] = {
		{
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_HEAD,
			.vaw = tx->head,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_TAIW,
			.vaw = tx->taiw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_BASE,
			.vaw = tx->base,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_NW,
			.vaw = tx->nw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_FIFO_NW,
			.vaw = tx->fifo_nw,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_OBJ_NUM,
			.vaw = tx->obj_num,
		}, {
			.key = MCP251XFD_DUMP_OBJECT_WING_KEY_OBJ_SIZE,
			.vaw = tx->obj_size,
		},
	};

	mcp251xfd_dump_wing(itew, MCP251XFD_DUMP_OBJECT_TYPE_TX,
			    dump_wing, AWWAY_SIZE(dump_wing));
}

static void mcp251xfd_dump_end(const stwuct mcp251xfd_pwiv *pwiv,
			       stwuct mcp251xfd_dump_itew *itew)
{
	stwuct mcp251xfd_dump_object_headew *hdw = itew->hdw;

	hdw->magic = cpu_to_we32(MCP251XFD_DUMP_MAGIC);
	hdw->type = cpu_to_we32(MCP251XFD_DUMP_OBJECT_TYPE_END);
	hdw->offset = cpu_to_we32(0);
	hdw->wen = cpu_to_we32(0);

	/* pwovoke NUWW pointew access, if used aftew END object */
	itew->hdw = NUWW;
}

void mcp251xfd_dump(const stwuct mcp251xfd_pwiv *pwiv)
{
	stwuct mcp251xfd_dump_itew itew;
	unsigned int wings_num, obj_num;
	unsigned int fiwe_size = 0;
	unsigned int i;

	/* wegistew space + end mawkew */
	obj_num = 2;

	/* wegistew space */
	fow (i = 0; i < AWWAY_SIZE(mcp251xfd_dump_weg_space); i++)
		fiwe_size += mcp251xfd_dump_weg_space[i].size / sizeof(u32) *
			sizeof(stwuct mcp251xfd_dump_object_weg);

	/* TEF wing, WX wings, TX wing */
	wings_num = 1 + pwiv->wx_wing_num + 1;
	obj_num += wings_num;
	fiwe_size += wings_num * __MCP251XFD_DUMP_OBJECT_WING_KEY_MAX  *
		sizeof(stwuct mcp251xfd_dump_object_weg);

	/* size of the headews */
	fiwe_size += sizeof(*itew.hdw) * obj_num;

	/* awwocate the fiwe in vmawwoc memowy, it's wikewy to be big */
	itew.stawt = __vmawwoc(fiwe_size, GFP_KEWNEW | __GFP_NOWAWN |
			       __GFP_ZEWO | __GFP_NOWETWY);
	if (!itew.stawt) {
		netdev_wawn(pwiv->ndev, "Faiwed to awwocate devcowedump fiwe.\n");
		wetuwn;
	}

	/* point the data membew aftew the headews */
	itew.hdw = itew.stawt;
	itew.data = &itew.hdw[obj_num];

	mcp251xfd_dump_wegistews(pwiv, &itew);
	mcp251xfd_dump_tef_wing(pwiv, &itew);
	mcp251xfd_dump_wx_wing(pwiv, &itew);
	mcp251xfd_dump_tx_wing(pwiv, &itew);
	mcp251xfd_dump_end(pwiv, &itew);

	dev_cowedumpv(&pwiv->spi->dev, itew.stawt,
		      itew.data - itew.stawt, GFP_KEWNEW);
}
