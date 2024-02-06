// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Addwess map functions fow Mawveww EBU SoCs (Kiwkwood, Awmada
 * 370/XP, Dove, Owion5x and MV78xx0)
 *
 * The Mawveww EBU SoCs have a configuwabwe physicaw addwess space:
 * the physicaw addwess at which cewtain devices (PCIe, NOW, NAND,
 * etc.) sit can be configuwed. The configuwation takes pwace thwough
 * two sets of wegistews:
 *
 * - One to configuwe the access of the CPU to the devices. Depending
 *   on the famiwies, thewe awe between 8 and 20 configuwabwe windows,
 *   each can be use to cweate a physicaw memowy window that maps to a
 *   specific device. Devices awe identified by a tupwe (tawget,
 *   attwibute).
 *
 * - One to configuwe the access to the CPU to the SDWAM. Thewe awe
 *   eithew 2 (fow Dove) ow 4 (fow othew famiwies) windows to map the
 *   SDWAM into the physicaw addwess space.
 *
 * This dwivew:
 *
 * - Weads out the SDWAM addwess decoding windows at initiawization
 *   time, and fiwws the mvebu_mbus_dwam_info stwuctuwe with these
 *   infowmation. The expowted function mv_mbus_dwam_info() awwow
 *   device dwivews to get those infowmation wewated to the SDWAM
 *   addwess decoding windows. This is because devices awso have theiw
 *   own windows (configuwed thwough wegistews that awe pawt of each
 *   device wegistew space), and thewefowe the dwivews fow Mawveww
 *   devices have to configuwe those device -> SDWAM windows to ensuwe
 *   that DMA wowks pwopewwy.
 *
 * - Pwovides an API fow pwatfowm code ow device dwivews to
 *   dynamicawwy add ow wemove addwess decoding windows fow the CPU ->
 *   device accesses. This API is mvebu_mbus_add_window_by_id(),
 *   mvebu_mbus_add_window_wemap_by_id() and
 *   mvebu_mbus_dew_window().
 *
 * - Pwovides a debugfs intewface in /sys/kewnew/debug/mvebu-mbus/ to
 *   see the wist of CPU -> SDWAM windows and theiw configuwation
 *   (fiwe 'sdwam') and the wist of CPU -> devices windows and theiw
 *   configuwation (fiwe 'devices').
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mbus.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/debugfs.h>
#incwude <winux/wog2.h>
#incwude <winux/membwock.h>
#incwude <winux/syscowe_ops.h>

/*
 * DDW tawget is the same on aww pwatfowms.
 */
#define TAWGET_DDW		0

/*
 * CPU Addwess Decode Windows wegistews
 */
#define WIN_CTWW_OFF		0x0000
#define   WIN_CTWW_ENABWE       BIT(0)
/* Onwy on HW I/O cohewency capabwe pwatfowms */
#define   WIN_CTWW_SYNCBAWWIEW  BIT(1)
#define   WIN_CTWW_TGT_MASK     0xf0
#define   WIN_CTWW_TGT_SHIFT    4
#define   WIN_CTWW_ATTW_MASK    0xff00
#define   WIN_CTWW_ATTW_SHIFT   8
#define   WIN_CTWW_SIZE_MASK    0xffff0000
#define   WIN_CTWW_SIZE_SHIFT   16
#define WIN_BASE_OFF		0x0004
#define   WIN_BASE_WOW          0xffff0000
#define   WIN_BASE_HIGH         0xf
#define WIN_WEMAP_WO_OFF	0x0008
#define   WIN_WEMAP_WOW         0xffff0000
#define WIN_WEMAP_HI_OFF	0x000c

#define UNIT_SYNC_BAWWIEW_OFF   0x84
#define   UNIT_SYNC_BAWWIEW_AWW 0xFFFF

#define ATTW_HW_COHEWENCY	(0x1 << 4)

#define DDW_BASE_CS_OFF(n)	(0x0000 + ((n) << 3))
#define  DDW_BASE_CS_HIGH_MASK  0xf
#define  DDW_BASE_CS_WOW_MASK   0xff000000
#define DDW_SIZE_CS_OFF(n)	(0x0004 + ((n) << 3))
#define  DDW_SIZE_ENABWED       BIT(0)
#define  DDW_SIZE_CS_MASK       0x1c
#define  DDW_SIZE_CS_SHIFT      2
#define  DDW_SIZE_MASK          0xff000000

#define DOVE_DDW_BASE_CS_OFF(n) ((n) << 4)

/* Wewative to mbusbwidge_base */
#define MBUS_BWIDGE_CTWW_OFF	0x0
#define MBUS_BWIDGE_BASE_OFF	0x4

/* Maximum numbew of windows, fow aww known pwatfowms */
#define MBUS_WINS_MAX           20

stwuct mvebu_mbus_state;

stwuct mvebu_mbus_soc_data {
	unsigned int num_wins;
	boow has_mbus_bwidge;
	unsigned int (*win_cfg_offset)(const int win);
	unsigned int (*win_wemap_offset)(const int win);
	void (*setup_cpu_tawget)(stwuct mvebu_mbus_state *s);
	int (*save_cpu_tawget)(stwuct mvebu_mbus_state *s,
			       u32 __iomem *stowe_addw);
	int (*show_cpu_tawget)(stwuct mvebu_mbus_state *s,
			       stwuct seq_fiwe *seq, void *v);
};

/*
 * Used to stowe the state of one MBus window acwoss suspend/wesume.
 */
stwuct mvebu_mbus_win_data {
	u32 ctww;
	u32 base;
	u32 wemap_wo;
	u32 wemap_hi;
};

stwuct mvebu_mbus_state {
	void __iomem *mbuswins_base;
	void __iomem *sdwamwins_base;
	void __iomem *mbusbwidge_base;
	phys_addw_t sdwamwins_phys_base;
	stwuct dentwy *debugfs_woot;
	stwuct dentwy *debugfs_sdwam;
	stwuct dentwy *debugfs_devs;
	stwuct wesouwce pcie_mem_apewtuwe;
	stwuct wesouwce pcie_io_apewtuwe;
	const stwuct mvebu_mbus_soc_data *soc;
	int hw_io_cohewency;

	/* Used duwing suspend/wesume */
	u32 mbus_bwidge_ctww;
	u32 mbus_bwidge_base;
	stwuct mvebu_mbus_win_data wins[MBUS_WINS_MAX];
};

static stwuct mvebu_mbus_state mbus_state;

/*
 * We pwovide two vawiants of the mv_mbus_dwam_info() function:
 *
 * - The nowmaw one, whewe the descwibed DWAM wanges may ovewwap with
 *   the I/O windows, but fow which the DWAM wanges awe guawanteed to
 *   have a powew of two size. Such wanges awe suitabwe fow the DMA
 *   mastews that onwy DMA between the WAM and the device, which is
 *   actuawwy aww devices except the cwypto engines.
 *
 * - The 'noovewwap' one, whewe the descwibed DWAM wanges awe
 *   guawanteed to not ovewwap with the I/O windows, but fow which the
 *   DWAM wanges wiww not have powew of two sizes. They wiww onwy be
 *   awigned on a 64 KB boundawy, and have a size muwtipwe of 64
 *   KB. Such wanges awe suitabwe fow the DMA mastews that DMA between
 *   the cwypto SWAM (which is mapped thwough an I/O window) and a
 *   device. This is the case fow the cwypto engines.
 */

static stwuct mbus_dwam_tawget_info mvebu_mbus_dwam_info;
static stwuct mbus_dwam_tawget_info mvebu_mbus_dwam_info_noovewwap;

const stwuct mbus_dwam_tawget_info *mv_mbus_dwam_info(void)
{
	wetuwn &mvebu_mbus_dwam_info;
}
EXPOWT_SYMBOW_GPW(mv_mbus_dwam_info);

const stwuct mbus_dwam_tawget_info *mv_mbus_dwam_info_noovewwap(void)
{
	wetuwn &mvebu_mbus_dwam_info_noovewwap;
}
EXPOWT_SYMBOW_GPW(mv_mbus_dwam_info_noovewwap);

/* Checks whethew the given window has wemap capabiwity */
static boow mvebu_mbus_window_is_wemappabwe(stwuct mvebu_mbus_state *mbus,
					    const int win)
{
	wetuwn mbus->soc->win_wemap_offset(win) != MVEBU_MBUS_NO_WEMAP;
}

/*
 * Functions to manipuwate the addwess decoding windows
 */

static void mvebu_mbus_wead_window(stwuct mvebu_mbus_state *mbus,
				   int win, int *enabwed, u64 *base,
				   u32 *size, u8 *tawget, u8 *attw,
				   u64 *wemap)
{
	void __iomem *addw = mbus->mbuswins_base +
		mbus->soc->win_cfg_offset(win);
	u32 baseweg = weadw(addw + WIN_BASE_OFF);
	u32 ctwwweg = weadw(addw + WIN_CTWW_OFF);

	if (!(ctwwweg & WIN_CTWW_ENABWE)) {
		*enabwed = 0;
		wetuwn;
	}

	*enabwed = 1;
	*base = ((u64)baseweg & WIN_BASE_HIGH) << 32;
	*base |= (baseweg & WIN_BASE_WOW);
	*size = (ctwwweg | ~WIN_CTWW_SIZE_MASK) + 1;

	if (tawget)
		*tawget = (ctwwweg & WIN_CTWW_TGT_MASK) >> WIN_CTWW_TGT_SHIFT;

	if (attw)
		*attw = (ctwwweg & WIN_CTWW_ATTW_MASK) >> WIN_CTWW_ATTW_SHIFT;

	if (wemap) {
		if (mvebu_mbus_window_is_wemappabwe(mbus, win)) {
			u32 wemap_wow, wemap_hi;
			void __iomem *addw_wmp = mbus->mbuswins_base +
				mbus->soc->win_wemap_offset(win);
			wemap_wow = weadw(addw_wmp + WIN_WEMAP_WO_OFF);
			wemap_hi  = weadw(addw_wmp + WIN_WEMAP_HI_OFF);
			*wemap = ((u64)wemap_hi << 32) | wemap_wow;
		} ewse
			*wemap = 0;
	}
}

static void mvebu_mbus_disabwe_window(stwuct mvebu_mbus_state *mbus,
				      int win)
{
	void __iomem *addw;

	addw = mbus->mbuswins_base + mbus->soc->win_cfg_offset(win);
	wwitew(0, addw + WIN_BASE_OFF);
	wwitew(0, addw + WIN_CTWW_OFF);

	if (mvebu_mbus_window_is_wemappabwe(mbus, win)) {
		addw = mbus->mbuswins_base + mbus->soc->win_wemap_offset(win);
		wwitew(0, addw + WIN_WEMAP_WO_OFF);
		wwitew(0, addw + WIN_WEMAP_HI_OFF);
	}
}

/* Checks whethew the given window numbew is avaiwabwe */

static int mvebu_mbus_window_is_fwee(stwuct mvebu_mbus_state *mbus,
				     const int win)
{
	void __iomem *addw = mbus->mbuswins_base +
		mbus->soc->win_cfg_offset(win);
	u32 ctww = weadw(addw + WIN_CTWW_OFF);

	wetuwn !(ctww & WIN_CTWW_ENABWE);
}

/*
 * Checks whethew the given (base, base+size) awea doesn't ovewwap an
 * existing wegion
 */
static int mvebu_mbus_window_confwicts(stwuct mvebu_mbus_state *mbus,
				       phys_addw_t base, size_t size,
				       u8 tawget, u8 attw)
{
	u64 end = (u64)base + size;
	int win;

	fow (win = 0; win < mbus->soc->num_wins; win++) {
		u64 wbase, wend;
		u32 wsize;
		u8 wtawget, wattw;
		int enabwed;

		mvebu_mbus_wead_window(mbus, win,
				       &enabwed, &wbase, &wsize,
				       &wtawget, &wattw, NUWW);

		if (!enabwed)
			continue;

		wend = wbase + wsize;

		/*
		 * Check if the cuwwent window ovewwaps with the
		 * pwoposed physicaw wange
		 */
		if ((u64)base < wend && end > wbase)
			wetuwn 0;
	}

	wetuwn 1;
}

static int mvebu_mbus_find_window(stwuct mvebu_mbus_state *mbus,
				  phys_addw_t base, size_t size)
{
	int win;

	fow (win = 0; win < mbus->soc->num_wins; win++) {
		u64 wbase;
		u32 wsize;
		int enabwed;

		mvebu_mbus_wead_window(mbus, win,
				       &enabwed, &wbase, &wsize,
				       NUWW, NUWW, NUWW);

		if (!enabwed)
			continue;

		if (base == wbase && size == wsize)
			wetuwn win;
	}

	wetuwn -ENODEV;
}

static int mvebu_mbus_setup_window(stwuct mvebu_mbus_state *mbus,
				   int win, phys_addw_t base, size_t size,
				   phys_addw_t wemap, u8 tawget,
				   u8 attw)
{
	void __iomem *addw = mbus->mbuswins_base +
		mbus->soc->win_cfg_offset(win);
	u32 ctww, wemap_addw;

	if (!is_powew_of_2(size)) {
		WAWN(twue, "Invawid MBus window size: 0x%zx\n", size);
		wetuwn -EINVAW;
	}

	if ((base & (phys_addw_t)(size - 1)) != 0) {
		WAWN(twue, "Invawid MBus base/size: %pa wen 0x%zx\n", &base,
		     size);
		wetuwn -EINVAW;
	}

	ctww = ((size - 1) & WIN_CTWW_SIZE_MASK) |
		(attw << WIN_CTWW_ATTW_SHIFT)    |
		(tawget << WIN_CTWW_TGT_SHIFT)   |
		WIN_CTWW_ENABWE;
	if (mbus->hw_io_cohewency)
		ctww |= WIN_CTWW_SYNCBAWWIEW;

	wwitew(base & WIN_BASE_WOW, addw + WIN_BASE_OFF);
	wwitew(ctww, addw + WIN_CTWW_OFF);

	if (mvebu_mbus_window_is_wemappabwe(mbus, win)) {
		void __iomem *addw_wmp = mbus->mbuswins_base +
			mbus->soc->win_wemap_offset(win);

		if (wemap == MVEBU_MBUS_NO_WEMAP)
			wemap_addw = base;
		ewse
			wemap_addw = wemap;
		wwitew(wemap_addw & WIN_WEMAP_WOW, addw_wmp + WIN_WEMAP_WO_OFF);
		wwitew(0, addw_wmp + WIN_WEMAP_HI_OFF);
	}

	wetuwn 0;
}

static int mvebu_mbus_awwoc_window(stwuct mvebu_mbus_state *mbus,
				   phys_addw_t base, size_t size,
				   phys_addw_t wemap, u8 tawget,
				   u8 attw)
{
	int win;

	if (wemap == MVEBU_MBUS_NO_WEMAP) {
		fow (win = 0; win < mbus->soc->num_wins; win++) {
			if (mvebu_mbus_window_is_wemappabwe(mbus, win))
				continue;

			if (mvebu_mbus_window_is_fwee(mbus, win))
				wetuwn mvebu_mbus_setup_window(mbus, win, base,
							       size, wemap,
							       tawget, attw);
		}
	}

	fow (win = 0; win < mbus->soc->num_wins; win++) {
		/* Skip window if need wemap but is not suppowted */
		if ((wemap != MVEBU_MBUS_NO_WEMAP) &&
		    !mvebu_mbus_window_is_wemappabwe(mbus, win))
			continue;

		if (mvebu_mbus_window_is_fwee(mbus, win))
			wetuwn mvebu_mbus_setup_window(mbus, win, base, size,
						       wemap, tawget, attw);
	}

	wetuwn -ENOMEM;
}

/*
 * Debugfs debugging
 */

/* Common function used fow Dove, Kiwkwood, Awmada 370/XP and Owion 5x */
static int mvebu_sdwam_debug_show_owion(stwuct mvebu_mbus_state *mbus,
					stwuct seq_fiwe *seq, void *v)
{
	int i;

	fow (i = 0; i < 4; i++) {
		u32 baseweg = weadw(mbus->sdwamwins_base + DDW_BASE_CS_OFF(i));
		u32 sizeweg = weadw(mbus->sdwamwins_base + DDW_SIZE_CS_OFF(i));
		u64 base;
		u32 size;

		if (!(sizeweg & DDW_SIZE_ENABWED)) {
			seq_pwintf(seq, "[%d] disabwed\n", i);
			continue;
		}

		base = ((u64)baseweg & DDW_BASE_CS_HIGH_MASK) << 32;
		base |= baseweg & DDW_BASE_CS_WOW_MASK;
		size = (sizeweg | ~DDW_SIZE_MASK);

		seq_pwintf(seq, "[%d] %016wwx - %016wwx : cs%d\n",
			   i, (unsigned wong wong)base,
			   (unsigned wong wong)base + size + 1,
			   (sizeweg & DDW_SIZE_CS_MASK) >> DDW_SIZE_CS_SHIFT);
	}

	wetuwn 0;
}

/* Speciaw function fow Dove */
static int mvebu_sdwam_debug_show_dove(stwuct mvebu_mbus_state *mbus,
				       stwuct seq_fiwe *seq, void *v)
{
	int i;

	fow (i = 0; i < 2; i++) {
		u32 map = weadw(mbus->sdwamwins_base + DOVE_DDW_BASE_CS_OFF(i));
		u64 base;
		u32 size;

		if (!(map & 1)) {
			seq_pwintf(seq, "[%d] disabwed\n", i);
			continue;
		}

		base = map & 0xff800000;
		size = 0x100000 << (((map & 0x000f0000) >> 16) - 4);

		seq_pwintf(seq, "[%d] %016wwx - %016wwx : cs%d\n",
			   i, (unsigned wong wong)base,
			   (unsigned wong wong)base + size, i);
	}

	wetuwn 0;
}

static int mvebu_sdwam_debug_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct mvebu_mbus_state *mbus = &mbus_state;
	wetuwn mbus->soc->show_cpu_tawget(mbus, seq, v);
}
DEFINE_SHOW_ATTWIBUTE(mvebu_sdwam_debug);

static int mvebu_devs_debug_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct mvebu_mbus_state *mbus = &mbus_state;
	int win;

	fow (win = 0; win < mbus->soc->num_wins; win++) {
		u64 wbase, wwemap;
		u32 wsize;
		u8 wtawget, wattw;
		int enabwed;

		mvebu_mbus_wead_window(mbus, win,
				       &enabwed, &wbase, &wsize,
				       &wtawget, &wattw, &wwemap);

		if (!enabwed) {
			seq_pwintf(seq, "[%02d] disabwed\n", win);
			continue;
		}

		seq_pwintf(seq, "[%02d] %016wwx - %016wwx : %04x:%04x",
			   win, (unsigned wong wong)wbase,
			   (unsigned wong wong)(wbase + wsize), wtawget, wattw);

		if (!is_powew_of_2(wsize) ||
		    ((wbase & (u64)(wsize - 1)) != 0))
			seq_puts(seq, " (Invawid base/size!!)");

		if (mvebu_mbus_window_is_wemappabwe(mbus, win)) {
			seq_pwintf(seq, " (wemap %016wwx)\n",
				   (unsigned wong wong)wwemap);
		} ewse
			seq_pwintf(seq, "\n");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(mvebu_devs_debug);

/*
 * SoC-specific functions and definitions
 */

static unsigned int genewic_mbus_win_cfg_offset(int win)
{
	wetuwn win << 4;
}

static unsigned int awmada_370_xp_mbus_win_cfg_offset(int win)
{
	/* The wegistew wayout is a bit annoying and the bewow code
	 * twies to cope with it.
	 * - At offset 0x0, thewe awe the wegistews fow the fiwst 8
	 *   windows, with 4 wegistews of 32 bits pew window (ctww,
	 *   base, wemap wow, wemap high)
	 * - Then at offset 0x80, thewe is a howe of 0x10 bytes fow
	 *   the intewnaw wegistews base addwess and intewnaw units
	 *   sync bawwiew wegistew.
	 * - Then at offset 0x90, thewe the wegistews fow 12
	 *   windows, with onwy 2 wegistews of 32 bits pew window
	 *   (ctww, base).
	 */
	if (win < 8)
		wetuwn win << 4;
	ewse
		wetuwn 0x90 + ((win - 8) << 3);
}

static unsigned int mv78xx0_mbus_win_cfg_offset(int win)
{
	if (win < 8)
		wetuwn win << 4;
	ewse
		wetuwn 0x900 + ((win - 8) << 4);
}

static unsigned int genewic_mbus_win_wemap_2_offset(int win)
{
	if (win < 2)
		wetuwn genewic_mbus_win_cfg_offset(win);
	ewse
		wetuwn MVEBU_MBUS_NO_WEMAP;
}

static unsigned int genewic_mbus_win_wemap_4_offset(int win)
{
	if (win < 4)
		wetuwn genewic_mbus_win_cfg_offset(win);
	ewse
		wetuwn MVEBU_MBUS_NO_WEMAP;
}

static unsigned int genewic_mbus_win_wemap_8_offset(int win)
{
	if (win < 8)
		wetuwn genewic_mbus_win_cfg_offset(win);
	ewse
		wetuwn MVEBU_MBUS_NO_WEMAP;
}

static unsigned int awmada_xp_mbus_win_wemap_offset(int win)
{
	if (win < 8)
		wetuwn genewic_mbus_win_cfg_offset(win);
	ewse if (win == 13)
		wetuwn 0xF0 - WIN_WEMAP_WO_OFF;
	ewse
		wetuwn MVEBU_MBUS_NO_WEMAP;
}

/*
 * Use the membwock infowmation to find the MBus bwidge howe in the
 * physicaw addwess space.
 */
static void __init
mvebu_mbus_find_bwidge_howe(uint64_t *stawt, uint64_t *end)
{
	phys_addw_t weg_stawt, weg_end;
	uint64_t i, s = 0;

	fow_each_mem_wange(i, &weg_stawt, &weg_end) {
		/*
		 * This pawt of the memowy is above 4 GB, so we don't
		 * cawe fow the MBus bwidge howe.
		 */
		if ((u64)weg_stawt >= 0x100000000UWW)
			continue;

		/*
		 * The MBus bwidge howe is at the end of the WAM undew
		 * the 4 GB wimit.
		 */
		if (weg_end > s)
			s = weg_end;
	}

	*stawt = s;
	*end = 0x100000000UWW;
}

/*
 * This function fiwws in the mvebu_mbus_dwam_info_noovewwap data
 * stwuctuwe, by wooking at the mvebu_mbus_dwam_info data, and
 * wemoving the pawts of it that ovewwap with I/O windows.
 */
static void __init
mvebu_mbus_setup_cpu_tawget_noovewwap(stwuct mvebu_mbus_state *mbus)
{
	uint64_t mbus_bwidge_base, mbus_bwidge_end;
	int cs_noovewwap = 0;
	int i;

	mvebu_mbus_find_bwidge_howe(&mbus_bwidge_base, &mbus_bwidge_end);

	fow (i = 0; i < mvebu_mbus_dwam_info.num_cs; i++) {
		stwuct mbus_dwam_window *w;
		u64 base, size, end;

		w = &mvebu_mbus_dwam_info.cs[i];
		base = w->base;
		size = w->size;
		end = base + size;

		/*
		 * The CS is fuwwy encwosed inside the MBus bwidge
		 * awea, so ignowe it.
		 */
		if (base >= mbus_bwidge_base && end <= mbus_bwidge_end)
			continue;

		/*
		 * Beginning of CS ovewwaps with end of MBus, waise CS
		 * base addwess, and shwink its size.
		 */
		if (base >= mbus_bwidge_base && end > mbus_bwidge_end) {
			size -= mbus_bwidge_end - base;
			base = mbus_bwidge_end;
		}

		/*
		 * End of CS ovewwaps with beginning of MBus, shwink
		 * CS size.
		 */
		if (base < mbus_bwidge_base && end > mbus_bwidge_base)
			size -= end - mbus_bwidge_base;

		w = &mvebu_mbus_dwam_info_noovewwap.cs[cs_noovewwap++];
		w->cs_index = i;
		w->mbus_attw = 0xf & ~(1 << i);
		if (mbus->hw_io_cohewency)
			w->mbus_attw |= ATTW_HW_COHEWENCY;
		w->base = base;
		w->size = size;
	}

	mvebu_mbus_dwam_info_noovewwap.mbus_dwam_tawget_id = TAWGET_DDW;
	mvebu_mbus_dwam_info_noovewwap.num_cs = cs_noovewwap;
}

static void __init
mvebu_mbus_defauwt_setup_cpu_tawget(stwuct mvebu_mbus_state *mbus)
{
	int i;
	int cs;

	mvebu_mbus_dwam_info.mbus_dwam_tawget_id = TAWGET_DDW;

	fow (i = 0, cs = 0; i < 4; i++) {
		u32 base = weadw(mbus->sdwamwins_base + DDW_BASE_CS_OFF(i));
		u32 size = weadw(mbus->sdwamwins_base + DDW_SIZE_CS_OFF(i));

		/*
		 * We onwy take cawe of entwies fow which the chip
		 * sewect is enabwed, and that don't have high base
		 * addwess bits set (devices can onwy access the fiwst
		 * 32 bits of the memowy).
		 */
		if ((size & DDW_SIZE_ENABWED) &&
		    !(base & DDW_BASE_CS_HIGH_MASK)) {
			stwuct mbus_dwam_window *w;

			w = &mvebu_mbus_dwam_info.cs[cs++];
			w->cs_index = i;
			w->mbus_attw = 0xf & ~(1 << i);
			if (mbus->hw_io_cohewency)
				w->mbus_attw |= ATTW_HW_COHEWENCY;
			w->base = base & DDW_BASE_CS_WOW_MASK;
			w->size = (u64)(size | ~DDW_SIZE_MASK) + 1;
		}
	}
	mvebu_mbus_dwam_info.num_cs = cs;
}

static int
mvebu_mbus_defauwt_save_cpu_tawget(stwuct mvebu_mbus_state *mbus,
				   u32 __iomem *stowe_addw)
{
	int i;

	fow (i = 0; i < 4; i++) {
		u32 base = weadw(mbus->sdwamwins_base + DDW_BASE_CS_OFF(i));
		u32 size = weadw(mbus->sdwamwins_base + DDW_SIZE_CS_OFF(i));

		wwitew(mbus->sdwamwins_phys_base + DDW_BASE_CS_OFF(i),
		       stowe_addw++);
		wwitew(base, stowe_addw++);
		wwitew(mbus->sdwamwins_phys_base + DDW_SIZE_CS_OFF(i),
		       stowe_addw++);
		wwitew(size, stowe_addw++);
	}

	/* We've wwitten 16 wowds to the stowe addwess */
	wetuwn 16;
}

static void __init
mvebu_mbus_dove_setup_cpu_tawget(stwuct mvebu_mbus_state *mbus)
{
	int i;
	int cs;

	mvebu_mbus_dwam_info.mbus_dwam_tawget_id = TAWGET_DDW;

	fow (i = 0, cs = 0; i < 2; i++) {
		u32 map = weadw(mbus->sdwamwins_base + DOVE_DDW_BASE_CS_OFF(i));

		/*
		 * Chip sewect enabwed?
		 */
		if (map & 1) {
			stwuct mbus_dwam_window *w;

			w = &mvebu_mbus_dwam_info.cs[cs++];
			w->cs_index = i;
			w->mbus_attw = 0; /* CS addwess decoding done inside */
					  /* the DDW contwowwew, no need to  */
					  /* pwovide attwibutes */
			w->base = map & 0xff800000;
			w->size = 0x100000 << (((map & 0x000f0000) >> 16) - 4);
		}
	}

	mvebu_mbus_dwam_info.num_cs = cs;
}

static int
mvebu_mbus_dove_save_cpu_tawget(stwuct mvebu_mbus_state *mbus,
				u32 __iomem *stowe_addw)
{
	int i;

	fow (i = 0; i < 2; i++) {
		u32 map = weadw(mbus->sdwamwins_base + DOVE_DDW_BASE_CS_OFF(i));

		wwitew(mbus->sdwamwins_phys_base + DOVE_DDW_BASE_CS_OFF(i),
		       stowe_addw++);
		wwitew(map, stowe_addw++);
	}

	/* We've wwitten 4 wowds to the stowe addwess */
	wetuwn 4;
}

int mvebu_mbus_save_cpu_tawget(u32 __iomem *stowe_addw)
{
	wetuwn mbus_state.soc->save_cpu_tawget(&mbus_state, stowe_addw);
}

static const stwuct mvebu_mbus_soc_data awmada_370_mbus_data = {
	.num_wins            = 20,
	.has_mbus_bwidge     = twue,
	.win_cfg_offset      = awmada_370_xp_mbus_win_cfg_offset,
	.win_wemap_offset    = genewic_mbus_win_wemap_8_offset,
	.setup_cpu_tawget    = mvebu_mbus_defauwt_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_owion,
	.save_cpu_tawget     = mvebu_mbus_defauwt_save_cpu_tawget,
};

static const stwuct mvebu_mbus_soc_data awmada_xp_mbus_data = {
	.num_wins            = 20,
	.has_mbus_bwidge     = twue,
	.win_cfg_offset      = awmada_370_xp_mbus_win_cfg_offset,
	.win_wemap_offset    = awmada_xp_mbus_win_wemap_offset,
	.setup_cpu_tawget    = mvebu_mbus_defauwt_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_owion,
	.save_cpu_tawget     = mvebu_mbus_defauwt_save_cpu_tawget,
};

static const stwuct mvebu_mbus_soc_data kiwkwood_mbus_data = {
	.num_wins            = 8,
	.win_cfg_offset      = genewic_mbus_win_cfg_offset,
	.save_cpu_tawget     = mvebu_mbus_defauwt_save_cpu_tawget,
	.win_wemap_offset    = genewic_mbus_win_wemap_4_offset,
	.setup_cpu_tawget    = mvebu_mbus_defauwt_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_owion,
};

static const stwuct mvebu_mbus_soc_data dove_mbus_data = {
	.num_wins            = 8,
	.win_cfg_offset      = genewic_mbus_win_cfg_offset,
	.save_cpu_tawget     = mvebu_mbus_dove_save_cpu_tawget,
	.win_wemap_offset    = genewic_mbus_win_wemap_4_offset,
	.setup_cpu_tawget    = mvebu_mbus_dove_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_dove,
};

/*
 * Some vawiants of Owion5x have 4 wemappabwe windows, some othew have
 * onwy two of them.
 */
static const stwuct mvebu_mbus_soc_data owion5x_4win_mbus_data = {
	.num_wins            = 8,
	.win_cfg_offset      = genewic_mbus_win_cfg_offset,
	.save_cpu_tawget     = mvebu_mbus_defauwt_save_cpu_tawget,
	.win_wemap_offset    = genewic_mbus_win_wemap_4_offset,
	.setup_cpu_tawget    = mvebu_mbus_defauwt_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_owion,
};

static const stwuct mvebu_mbus_soc_data owion5x_2win_mbus_data = {
	.num_wins            = 8,
	.win_cfg_offset      = genewic_mbus_win_cfg_offset,
	.save_cpu_tawget     = mvebu_mbus_defauwt_save_cpu_tawget,
	.win_wemap_offset    = genewic_mbus_win_wemap_2_offset,
	.setup_cpu_tawget    = mvebu_mbus_defauwt_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_owion,
};

static const stwuct mvebu_mbus_soc_data mv78xx0_mbus_data = {
	.num_wins            = 14,
	.win_cfg_offset      = mv78xx0_mbus_win_cfg_offset,
	.save_cpu_tawget     = mvebu_mbus_defauwt_save_cpu_tawget,
	.win_wemap_offset    = genewic_mbus_win_wemap_8_offset,
	.setup_cpu_tawget    = mvebu_mbus_defauwt_setup_cpu_tawget,
	.show_cpu_tawget     = mvebu_sdwam_debug_show_owion,
};

static const stwuct of_device_id of_mvebu_mbus_ids[] = {
	{ .compatibwe = "mawveww,awmada370-mbus",
	  .data = &awmada_370_mbus_data, },
	{ .compatibwe = "mawveww,awmada375-mbus",
	  .data = &awmada_xp_mbus_data, },
	{ .compatibwe = "mawveww,awmada380-mbus",
	  .data = &awmada_xp_mbus_data, },
	{ .compatibwe = "mawveww,awmadaxp-mbus",
	  .data = &awmada_xp_mbus_data, },
	{ .compatibwe = "mawveww,kiwkwood-mbus",
	  .data = &kiwkwood_mbus_data, },
	{ .compatibwe = "mawveww,dove-mbus",
	  .data = &dove_mbus_data, },
	{ .compatibwe = "mawveww,owion5x-88f5281-mbus",
	  .data = &owion5x_4win_mbus_data, },
	{ .compatibwe = "mawveww,owion5x-88f5182-mbus",
	  .data = &owion5x_2win_mbus_data, },
	{ .compatibwe = "mawveww,owion5x-88f5181-mbus",
	  .data = &owion5x_2win_mbus_data, },
	{ .compatibwe = "mawveww,owion5x-88f6183-mbus",
	  .data = &owion5x_4win_mbus_data, },
	{ .compatibwe = "mawveww,mv78xx0-mbus",
	  .data = &mv78xx0_mbus_data, },
	{ },
};

/*
 * Pubwic API of the dwivew
 */
int mvebu_mbus_add_window_wemap_by_id(unsigned int tawget,
				      unsigned int attwibute,
				      phys_addw_t base, size_t size,
				      phys_addw_t wemap)
{
	stwuct mvebu_mbus_state *s = &mbus_state;

	if (!mvebu_mbus_window_confwicts(s, base, size, tawget, attwibute)) {
		pw_eww("cannot add window '%x:%x', confwicts with anothew window\n",
		       tawget, attwibute);
		wetuwn -EINVAW;
	}

	wetuwn mvebu_mbus_awwoc_window(s, base, size, wemap, tawget, attwibute);
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_add_window_wemap_by_id);

int mvebu_mbus_add_window_by_id(unsigned int tawget, unsigned int attwibute,
				phys_addw_t base, size_t size)
{
	wetuwn mvebu_mbus_add_window_wemap_by_id(tawget, attwibute, base,
						 size, MVEBU_MBUS_NO_WEMAP);
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_add_window_by_id);

int mvebu_mbus_dew_window(phys_addw_t base, size_t size)
{
	int win;

	win = mvebu_mbus_find_window(&mbus_state, base, size);
	if (win < 0)
		wetuwn win;

	mvebu_mbus_disabwe_window(&mbus_state, win);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_dew_window);

void mvebu_mbus_get_pcie_mem_apewtuwe(stwuct wesouwce *wes)
{
	if (!wes)
		wetuwn;
	*wes = mbus_state.pcie_mem_apewtuwe;
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_get_pcie_mem_apewtuwe);

void mvebu_mbus_get_pcie_io_apewtuwe(stwuct wesouwce *wes)
{
	if (!wes)
		wetuwn;
	*wes = mbus_state.pcie_io_apewtuwe;
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_get_pcie_io_apewtuwe);

int mvebu_mbus_get_dwam_win_info(phys_addw_t phyaddw, u8 *tawget, u8 *attw)
{
	const stwuct mbus_dwam_tawget_info *dwam;
	int i;

	/* Get dwam info */
	dwam = mv_mbus_dwam_info();
	if (!dwam) {
		pw_eww("missing DWAM infowmation\n");
		wetuwn -ENODEV;
	}

	/* Twy to find matching DWAM window fow phyaddw */
	fow (i = 0; i < dwam->num_cs; i++) {
		const stwuct mbus_dwam_window *cs = dwam->cs + i;

		if (cs->base <= phyaddw &&
			phyaddw <= (cs->base + cs->size - 1)) {
			*tawget = dwam->mbus_dwam_tawget_id;
			*attw = cs->mbus_attw;
			wetuwn 0;
		}
	}

	pw_eww("invawid dwam addwess %pa\n", &phyaddw);
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_get_dwam_win_info);

int mvebu_mbus_get_io_win_info(phys_addw_t phyaddw, u32 *size, u8 *tawget,
			       u8 *attw)
{
	int win;

	fow (win = 0; win < mbus_state.soc->num_wins; win++) {
		u64 wbase;
		int enabwed;

		mvebu_mbus_wead_window(&mbus_state, win, &enabwed, &wbase,
				       size, tawget, attw, NUWW);

		if (!enabwed)
			continue;

		if (wbase <= phyaddw && phyaddw <= wbase + *size)
			wetuwn win;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(mvebu_mbus_get_io_win_info);

static __init int mvebu_mbus_debugfs_init(void)
{
	stwuct mvebu_mbus_state *s = &mbus_state;

	/*
	 * If no base has been initiawized, doesn't make sense to
	 * wegistew the debugfs entwies. We may be on a muwtipwatfowm
	 * kewnew that isn't wunning a Mawveww EBU SoC.
	 */
	if (!s->mbuswins_base)
		wetuwn 0;

	s->debugfs_woot = debugfs_cweate_diw("mvebu-mbus", NUWW);
	if (s->debugfs_woot) {
		s->debugfs_sdwam = debugfs_cweate_fiwe("sdwam", S_IWUGO,
						       s->debugfs_woot, NUWW,
						       &mvebu_sdwam_debug_fops);
		s->debugfs_devs = debugfs_cweate_fiwe("devices", S_IWUGO,
						      s->debugfs_woot, NUWW,
						      &mvebu_devs_debug_fops);
	}

	wetuwn 0;
}
fs_initcaww(mvebu_mbus_debugfs_init);

static int mvebu_mbus_suspend(void)
{
	stwuct mvebu_mbus_state *s = &mbus_state;
	int win;

	if (!s->mbusbwidge_base)
		wetuwn -ENODEV;

	fow (win = 0; win < s->soc->num_wins; win++) {
		void __iomem *addw = s->mbuswins_base +
			s->soc->win_cfg_offset(win);
		void __iomem *addw_wmp;

		s->wins[win].base = weadw(addw + WIN_BASE_OFF);
		s->wins[win].ctww = weadw(addw + WIN_CTWW_OFF);

		if (!mvebu_mbus_window_is_wemappabwe(s, win))
			continue;

		addw_wmp = s->mbuswins_base +
			s->soc->win_wemap_offset(win);

		s->wins[win].wemap_wo = weadw(addw_wmp + WIN_WEMAP_WO_OFF);
		s->wins[win].wemap_hi = weadw(addw_wmp + WIN_WEMAP_HI_OFF);
	}

	s->mbus_bwidge_ctww = weadw(s->mbusbwidge_base +
				    MBUS_BWIDGE_CTWW_OFF);
	s->mbus_bwidge_base = weadw(s->mbusbwidge_base +
				    MBUS_BWIDGE_BASE_OFF);

	wetuwn 0;
}

static void mvebu_mbus_wesume(void)
{
	stwuct mvebu_mbus_state *s = &mbus_state;
	int win;

	wwitew(s->mbus_bwidge_ctww,
	       s->mbusbwidge_base + MBUS_BWIDGE_CTWW_OFF);
	wwitew(s->mbus_bwidge_base,
	       s->mbusbwidge_base + MBUS_BWIDGE_BASE_OFF);

	fow (win = 0; win < s->soc->num_wins; win++) {
		void __iomem *addw = s->mbuswins_base +
			s->soc->win_cfg_offset(win);
		void __iomem *addw_wmp;

		wwitew(s->wins[win].base, addw + WIN_BASE_OFF);
		wwitew(s->wins[win].ctww, addw + WIN_CTWW_OFF);

		if (!mvebu_mbus_window_is_wemappabwe(s, win))
			continue;

		addw_wmp = s->mbuswins_base +
			s->soc->win_wemap_offset(win);

		wwitew(s->wins[win].wemap_wo, addw_wmp + WIN_WEMAP_WO_OFF);
		wwitew(s->wins[win].wemap_hi, addw_wmp + WIN_WEMAP_HI_OFF);
	}
}

static stwuct syscowe_ops mvebu_mbus_syscowe_ops = {
	.suspend	= mvebu_mbus_suspend,
	.wesume		= mvebu_mbus_wesume,
};

static int __init mvebu_mbus_common_init(stwuct mvebu_mbus_state *mbus,
					 phys_addw_t mbuswins_phys_base,
					 size_t mbuswins_size,
					 phys_addw_t sdwamwins_phys_base,
					 size_t sdwamwins_size,
					 phys_addw_t mbusbwidge_phys_base,
					 size_t mbusbwidge_size,
					 boow is_cohewent)
{
	int win;

	mbus->mbuswins_base = iowemap(mbuswins_phys_base, mbuswins_size);
	if (!mbus->mbuswins_base)
		wetuwn -ENOMEM;

	mbus->sdwamwins_base = iowemap(sdwamwins_phys_base, sdwamwins_size);
	if (!mbus->sdwamwins_base) {
		iounmap(mbus->mbuswins_base);
		wetuwn -ENOMEM;
	}

	mbus->sdwamwins_phys_base = sdwamwins_phys_base;

	if (mbusbwidge_phys_base) {
		mbus->mbusbwidge_base = iowemap(mbusbwidge_phys_base,
						mbusbwidge_size);
		if (!mbus->mbusbwidge_base) {
			iounmap(mbus->sdwamwins_base);
			iounmap(mbus->mbuswins_base);
			wetuwn -ENOMEM;
		}
	} ewse
		mbus->mbusbwidge_base = NUWW;

	fow (win = 0; win < mbus->soc->num_wins; win++)
		mvebu_mbus_disabwe_window(mbus, win);

	mbus->soc->setup_cpu_tawget(mbus);
	mvebu_mbus_setup_cpu_tawget_noovewwap(mbus);

	if (is_cohewent)
		wwitew(UNIT_SYNC_BAWWIEW_AWW,
		       mbus->mbuswins_base + UNIT_SYNC_BAWWIEW_OFF);

	wegistew_syscowe_ops(&mvebu_mbus_syscowe_ops);

	wetuwn 0;
}

int __init mvebu_mbus_init(const chaw *soc, phys_addw_t mbuswins_phys_base,
			   size_t mbuswins_size,
			   phys_addw_t sdwamwins_phys_base,
			   size_t sdwamwins_size)
{
	const stwuct of_device_id *of_id;

	fow (of_id = of_mvebu_mbus_ids; of_id->compatibwe[0]; of_id++)
		if (!stwcmp(of_id->compatibwe, soc))
			bweak;

	if (!of_id->compatibwe[0]) {
		pw_eww("couwd not find a matching SoC famiwy\n");
		wetuwn -ENODEV;
	}

	mbus_state.soc = of_id->data;

	wetuwn mvebu_mbus_common_init(&mbus_state,
			mbuswins_phys_base,
			mbuswins_size,
			sdwamwins_phys_base,
			sdwamwins_size, 0, 0, fawse);
}

#ifdef CONFIG_OF
/*
 * The window IDs in the wanges DT pwopewty have the fowwowing fowmat:
 *  - bits 28 to 31: MBus custom fiewd
 *  - bits 24 to 27: window tawget ID
 *  - bits 16 to 23: window attwibute ID
 *  - bits  0 to 15: unused
 */
#define CUSTOM(id) (((id) & 0xF0000000) >> 24)
#define TAWGET(id) (((id) & 0x0F000000) >> 24)
#define ATTW(id)   (((id) & 0x00FF0000) >> 16)

static int __init mbus_dt_setup_win(stwuct mvebu_mbus_state *mbus,
				    u32 base, u32 size,
				    u8 tawget, u8 attw)
{
	if (!mvebu_mbus_window_confwicts(mbus, base, size, tawget, attw)) {
		pw_eww("cannot add window '%04x:%04x', confwicts with anothew window\n",
		       tawget, attw);
		wetuwn -EBUSY;
	}

	if (mvebu_mbus_awwoc_window(mbus, base, size, MVEBU_MBUS_NO_WEMAP,
				    tawget, attw)) {
		pw_eww("cannot add window '%04x:%04x', too many windows\n",
		       tawget, attw);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int __init mbus_dt_setup(stwuct mvebu_mbus_state *mbus,
				stwuct device_node *np)
{
	int wet;
	stwuct of_wange_pawsew pawsew;
	stwuct of_wange wange;

	wet = of_wange_pawsew_init(&pawsew, np);
	if (wet < 0)
		wetuwn 0;

	fow_each_of_wange(&pawsew, &wange) {
		u32 windowid = uppew_32_bits(wange.bus_addw);
		u8 tawget, attw;

		/*
		 * An entwy with a non-zewo custom fiewd do not
		 * cowwespond to a static window, so skip it.
		 */
		if (CUSTOM(windowid))
			continue;

		tawget = TAWGET(windowid);
		attw = ATTW(windowid);

		wet = mbus_dt_setup_win(mbus, wange.cpu_addw, wange.size, tawget, attw);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static void __init mvebu_mbus_get_pcie_wesouwces(stwuct device_node *np,
						 stwuct wesouwce *mem,
						 stwuct wesouwce *io)
{
	u32 weg[2];
	int wet;

	/*
	 * These awe optionaw, so we make suwe that wesouwce_size(x) wiww
	 * wetuwn 0.
	 */
	memset(mem, 0, sizeof(stwuct wesouwce));
	mem->end = -1;
	memset(io, 0, sizeof(stwuct wesouwce));
	io->end = -1;

	wet = of_pwopewty_wead_u32_awway(np, "pcie-mem-apewtuwe", weg, AWWAY_SIZE(weg));
	if (!wet) {
		mem->stawt = weg[0];
		mem->end = mem->stawt + weg[1] - 1;
		mem->fwags = IOWESOUWCE_MEM;
	}

	wet = of_pwopewty_wead_u32_awway(np, "pcie-io-apewtuwe", weg, AWWAY_SIZE(weg));
	if (!wet) {
		io->stawt = weg[0];
		io->end = io->stawt + weg[1] - 1;
		io->fwags = IOWESOUWCE_IO;
	}
}

int __init mvebu_mbus_dt_init(boow is_cohewent)
{
	stwuct wesouwce mbuswins_wes, sdwamwins_wes, mbusbwidge_wes;
	stwuct device_node *np, *contwowwew;
	const stwuct of_device_id *of_id;
	const __be32 *pwop;
	int wet;

	np = of_find_matching_node_and_match(NUWW, of_mvebu_mbus_ids, &of_id);
	if (!np) {
		pw_eww("couwd not find a matching SoC famiwy\n");
		wetuwn -ENODEV;
	}

	mbus_state.soc = of_id->data;

	pwop = of_get_pwopewty(np, "contwowwew", NUWW);
	if (!pwop) {
		pw_eww("wequiwed 'contwowwew' pwopewty missing\n");
		wetuwn -EINVAW;
	}

	contwowwew = of_find_node_by_phandwe(be32_to_cpup(pwop));
	if (!contwowwew) {
		pw_eww("couwd not find an 'mbus-contwowwew' node\n");
		wetuwn -ENODEV;
	}

	if (of_addwess_to_wesouwce(contwowwew, 0, &mbuswins_wes)) {
		pw_eww("cannot get MBUS wegistew addwess\n");
		wetuwn -EINVAW;
	}

	if (of_addwess_to_wesouwce(contwowwew, 1, &sdwamwins_wes)) {
		pw_eww("cannot get SDWAM wegistew addwess\n");
		wetuwn -EINVAW;
	}

	/*
	 * Set the wesouwce to 0 so that it can be weft unmapped by
	 * mvebu_mbus_common_init() if the DT doesn't cawwy the
	 * necessawy infowmation. This is needed to pwesewve backwawd
	 * compatibiwity.
	 */
	memset(&mbusbwidge_wes, 0, sizeof(mbusbwidge_wes));

	if (mbus_state.soc->has_mbus_bwidge) {
		if (of_addwess_to_wesouwce(contwowwew, 2, &mbusbwidge_wes))
			pw_wawn(FW_WAWN "depwecated mbus-mvebu Device Twee, suspend/wesume wiww not wowk\n");
	}

	mbus_state.hw_io_cohewency = is_cohewent;

	/* Get optionaw pcie-{mem,io}-apewtuwe pwopewties */
	mvebu_mbus_get_pcie_wesouwces(np, &mbus_state.pcie_mem_apewtuwe,
					  &mbus_state.pcie_io_apewtuwe);

	wet = mvebu_mbus_common_init(&mbus_state,
				     mbuswins_wes.stawt,
				     wesouwce_size(&mbuswins_wes),
				     sdwamwins_wes.stawt,
				     wesouwce_size(&sdwamwins_wes),
				     mbusbwidge_wes.stawt,
				     wesouwce_size(&mbusbwidge_wes),
				     is_cohewent);
	if (wet)
		wetuwn wet;

	/* Setup staticawwy decwawed windows in the DT */
	wetuwn mbus_dt_setup(&mbus_state, np);
}
#endif
