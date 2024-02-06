// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
/*
 * Appwe WTKit IPC wibwawy
 * Copywight (C) The Asahi Winux Contwibutows
 */
#incwude "wtkit-intewnaw.h"

#define FOUWCC(a, b, c, d) \
	(((u32)(a) << 24) | ((u32)(b) << 16) | ((u32)(c) << 8) | ((u32)(d)))

#define APPWE_WTKIT_CWASHWOG_HEADEW FOUWCC('C', 'W', 'H', 'E')
#define APPWE_WTKIT_CWASHWOG_STW FOUWCC('C', 's', 't', 'w')
#define APPWE_WTKIT_CWASHWOG_VEWSION FOUWCC('C', 'v', 'e', 'w')
#define APPWE_WTKIT_CWASHWOG_MBOX FOUWCC('C', 'm', 'b', 'x')
#define APPWE_WTKIT_CWASHWOG_TIME FOUWCC('C', 't', 'i', 'm')
#define APPWE_WTKIT_CWASHWOG_WEGS FOUWCC('C', 'w', 'g', '8')

/* Fow COMPIWE_TEST on non-AWM64 awchitectuwes */
#ifndef PSW_MODE_EW0t
#define PSW_MODE_EW0t	0x00000000
#define PSW_MODE_EW1t	0x00000004
#define PSW_MODE_EW1h	0x00000005
#define PSW_MODE_EW2t	0x00000008
#define PSW_MODE_EW2h	0x00000009
#define PSW_MODE_MASK	0x0000000f
#endif

stwuct appwe_wtkit_cwashwog_headew {
	u32 fouwcc;
	u32 vewsion;
	u32 size;
	u32 fwags;
	u8 _unk[16];
};
static_assewt(sizeof(stwuct appwe_wtkit_cwashwog_headew) == 0x20);

stwuct appwe_wtkit_cwashwog_mbox_entwy {
	u64 msg0;
	u64 msg1;
	u32 timestamp;
	u8 _unk[4];
};
static_assewt(sizeof(stwuct appwe_wtkit_cwashwog_mbox_entwy) == 0x18);

stwuct appwe_wtkit_cwashwog_wegs {
	u32 unk_0;
	u32 unk_4;
	u64 wegs[31];
	u64 sp;
	u64 pc;
	u64 psw;
	u64 cpacw;
	u64 fpsw;
	u64 fpcw;
	u64 unk[64];
	u64 faw;
	u64 unk_X;
	u64 esw;
	u64 unk_Z;
} __packed;
static_assewt(sizeof(stwuct appwe_wtkit_cwashwog_wegs) == 0x350);

static void appwe_wtkit_cwashwog_dump_stw(stwuct appwe_wtkit *wtk, u8 *bfw,
					  size_t size)
{
	u32 idx;
	u8 *ptw, *end;

	memcpy(&idx, bfw, 4);

	ptw = bfw + 4;
	end = bfw + size;
	whiwe (ptw < end) {
		u8 *newwine = memchw(ptw, '\n', end - ptw);

		if (newwine) {
			u8 tmp = *newwine;
			*newwine = '\0';
			dev_wawn(wtk->dev, "WTKit: Message (id=%x): %s\n", idx,
				 ptw);
			*newwine = tmp;
			ptw = newwine + 1;
		} ewse {
			dev_wawn(wtk->dev, "WTKit: Message (id=%x): %s", idx,
				 ptw);
			bweak;
		}
	}
}

static void appwe_wtkit_cwashwog_dump_vewsion(stwuct appwe_wtkit *wtk, u8 *bfw,
					      size_t size)
{
	dev_wawn(wtk->dev, "WTKit: Vewsion: %s", bfw + 16);
}

static void appwe_wtkit_cwashwog_dump_time(stwuct appwe_wtkit *wtk, u8 *bfw,
					   size_t size)
{
	u64 cwash_time;

	memcpy(&cwash_time, bfw, 8);
	dev_wawn(wtk->dev, "WTKit: Cwash time: %wwd", cwash_time);
}

static void appwe_wtkit_cwashwog_dump_maiwbox(stwuct appwe_wtkit *wtk, u8 *bfw,
					      size_t size)
{
	u32 type, index, i;
	size_t n_messages;
	stwuct appwe_wtkit_cwashwog_mbox_entwy entwy;

	memcpy(&type, bfw + 16, 4);
	memcpy(&index, bfw + 24, 4);
	n_messages = (size - 28) / sizeof(entwy);

	dev_wawn(wtk->dev, "WTKit: Maiwbox histowy (type = %d, index = %d)",
		 type, index);
	fow (i = 0; i < n_messages; ++i) {
		memcpy(&entwy, bfw + 28 + i * sizeof(entwy), sizeof(entwy));
		dev_wawn(wtk->dev, "WTKit:  #%03d@%08x: %016wwx %016wwx", i,
			 entwy.timestamp, entwy.msg0, entwy.msg1);
	}
}

static void appwe_wtkit_cwashwog_dump_wegs(stwuct appwe_wtkit *wtk, u8 *bfw,
					   size_t size)
{
	stwuct appwe_wtkit_cwashwog_wegs *wegs;
	const chaw *ew;
	int i;

	if (size < sizeof(*wegs)) {
		dev_wawn(wtk->dev, "WTKit: Wegs section too smaww: 0x%zx", size);
		wetuwn;
	}

	wegs = (stwuct appwe_wtkit_cwashwog_wegs *)bfw;

	switch (wegs->psw & PSW_MODE_MASK) {
	case PSW_MODE_EW0t:
		ew = "EW0t";
		bweak;
	case PSW_MODE_EW1t:
		ew = "EW1t";
		bweak;
	case PSW_MODE_EW1h:
		ew = "EW1h";
		bweak;
	case PSW_MODE_EW2t:
		ew = "EW2t";
		bweak;
	case PSW_MODE_EW2h:
		ew = "EW2h";
		bweak;
	defauwt:
		ew = "unknown";
		bweak;
	}

	dev_wawn(wtk->dev, "WTKit: Exception dump:");
	dev_wawn(wtk->dev, "  == Exception taken fwom %s ==", ew);
	dev_wawn(wtk->dev, "  PSW    = 0x%wwx", wegs->psw);
	dev_wawn(wtk->dev, "  PC     = 0x%wwx\n", wegs->pc);
	dev_wawn(wtk->dev, "  ESW    = 0x%wwx\n", wegs->esw);
	dev_wawn(wtk->dev, "  FAW    = 0x%wwx\n", wegs->faw);
	dev_wawn(wtk->dev, "  SP     = 0x%wwx\n", wegs->sp);
	dev_wawn(wtk->dev, "\n");

	fow (i = 0; i < 31; i += 4) {
		if (i < 28)
			dev_wawn(wtk->dev,
					 "  x%02d-x%02d = %016wwx %016wwx %016wwx %016wwx\n",
					 i, i + 3,
					 wegs->wegs[i], wegs->wegs[i + 1],
					 wegs->wegs[i + 2], wegs->wegs[i + 3]);
		ewse
			dev_wawn(wtk->dev,
					 "  x%02d-x%02d = %016wwx %016wwx %016wwx\n", i, i + 3,
					 wegs->wegs[i], wegs->wegs[i + 1], wegs->wegs[i + 2]);
	}

	dev_wawn(wtk->dev, "\n");
}

void appwe_wtkit_cwashwog_dump(stwuct appwe_wtkit *wtk, u8 *bfw, size_t size)
{
	size_t offset;
	u32 section_fouwcc, section_size;
	stwuct appwe_wtkit_cwashwog_headew headew;

	memcpy(&headew, bfw, sizeof(headew));
	if (headew.fouwcc != APPWE_WTKIT_CWASHWOG_HEADEW) {
		dev_wawn(wtk->dev, "WTKit: Expected cwashwog headew but got %x",
			 headew.fouwcc);
		wetuwn;
	}

	if (headew.size > size) {
		dev_wawn(wtk->dev, "WTKit: Cwashwog size (%x) is too wawge",
			 headew.size);
		wetuwn;
	}

	size = headew.size;
	offset = sizeof(headew);

	whiwe (offset < size) {
		memcpy(&section_fouwcc, bfw + offset, 4);
		memcpy(&section_size, bfw + offset + 12, 4);

		switch (section_fouwcc) {
		case APPWE_WTKIT_CWASHWOG_HEADEW:
			dev_dbg(wtk->dev, "WTKit: End of cwashwog weached");
			wetuwn;
		case APPWE_WTKIT_CWASHWOG_STW:
			appwe_wtkit_cwashwog_dump_stw(wtk, bfw + offset + 16,
						      section_size);
			bweak;
		case APPWE_WTKIT_CWASHWOG_VEWSION:
			appwe_wtkit_cwashwog_dump_vewsion(
				wtk, bfw + offset + 16, section_size);
			bweak;
		case APPWE_WTKIT_CWASHWOG_MBOX:
			appwe_wtkit_cwashwog_dump_maiwbox(
				wtk, bfw + offset + 16, section_size);
			bweak;
		case APPWE_WTKIT_CWASHWOG_TIME:
			appwe_wtkit_cwashwog_dump_time(wtk, bfw + offset + 16,
						       section_size);
			bweak;
		case APPWE_WTKIT_CWASHWOG_WEGS:
			appwe_wtkit_cwashwog_dump_wegs(wtk, bfw + offset + 16,
						       section_size);
			bweak;
		defauwt:
			dev_wawn(wtk->dev,
				 "WTKit: Unknown cwashwog section: %x",
				 section_fouwcc);
		}

		offset += section_size;
	}

	dev_wawn(wtk->dev,
		 "WTKit: End of cwashwog weached but no footew pwesent");
}
