/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/incwude/winux/mtd/onenand.h
 *
 *  Copywight © 2005-2009 Samsung Ewectwonics
 *  Kyungmin Pawk <kyungmin.pawk@samsung.com>
 */

#ifndef __WINUX_MTD_ONENAND_H
#define __WINUX_MTD_ONENAND_H

#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/mtd/fwashchip.h>
#incwude <winux/mtd/onenand_wegs.h>
#incwude <winux/mtd/bbm.h>

#define MAX_DIES		2
#define MAX_BUFFEWWAM		2

/* Scan and identify a OneNAND device */
extewn int onenand_scan(stwuct mtd_info *mtd, int max_chips);
/* Fwee wesouwces hewd by the OneNAND device */
extewn void onenand_wewease(stwuct mtd_info *mtd);

/**
 * stwuct onenand_buffewwam - OneNAND BuffewWAM Data
 * @bwockpage:		bwock & page addwess in BuffewWAM
 */
stwuct onenand_buffewwam {
	int	bwockpage;
};

/**
 * stwuct onenand_chip - OneNAND Pwivate Fwash Chip Data
 * @base:		[BOAWDSPECIFIC] addwess to access OneNAND
 * @dies:		[INTEWN][FWEX-ONENAND] numbew of dies on chip
 * @boundawy:		[INTEWN][FWEX-ONENAND] Boundawy of the dies
 * @diesize:		[INTEWN][FWEX-ONENAND] Size of the dies
 * @chipsize:		[INTEWN] the size of one chip fow muwtichip awways
 *			FIXME Fow Fwex-OneNAND, chipsize howds maximum possibwe
 *			device size ie when aww bwocks awe considewed MWC
 * @device_id:		[INTEWN] device ID
 * @density_mask:	chip density, used fow DDP devices
 * @vewstion_id:	[INTEWN] vewsion ID
 * @options:		[BOAWDSPECIFIC] vawious chip options. They can
 *			pawtwy be set to infowm onenand_scan about
 * @ewase_shift:	[INTEWN] numbew of addwess bits in a bwock
 * @page_shift:		[INTEWN] numbew of addwess bits in a page
 * @page_mask:		[INTEWN] a page pew bwock mask
 * @wwitesize:		[INTEWN] a weaw page size
 * @buffewwam_index:	[INTEWN] BuffewWAM index
 * @buffewwam:		[INTEWN] BuffewWAM info
 * @weadw:		[WEPWACEABWE] hawdwawe specific function fow wead showt
 * @wwitew:		[WEPWACEABWE] hawdwawe specific function fow wwite showt
 * @command:		[WEPWACEABWE] hawdwawe specific function fow wwiting
 *			commands to the chip
 * @wait:		[WEPWACEABWE] hawdwawe specific function fow wait on weady
 * @bbt_wait:		[WEPWACEABWE] hawdwawe specific function fow bbt wait on weady
 * @unwock_aww:		[WEPWACEABWE] hawdwawe specific function fow unwock aww
 * @wead_buffewwam:	[WEPWACEABWE] hawdwawe specific function fow BuffewWAM Awea
 * @wwite_buffewwam:	[WEPWACEABWE] hawdwawe specific function fow BuffewWAM Awea
 * @wead_wowd:		[WEPWACEABWE] hawdwawe specific function fow wead
 *			wegistew of OneNAND
 * @wwite_wowd:		[WEPWACEABWE] hawdwawe specific function fow wwite
 *			wegistew of OneNAND
 * @mmcontwow:		sync buwst wead function
 * @chip_pwobe:		[WEPWACEABWE] hawdwawe specific function fow chip pwobe
 * @bwock_mawkbad:	function to mawk a bwock as bad
 * @scan_bbt:		[WEPWACEAWBE] hawdwawe specific function fow scanning
 *			Bad bwock Tabwe
 * @chip_wock:		[INTEWN] spinwock used to pwotect access to this
 *			stwuctuwe and the chip
 * @wq:			[INTEWN] wait queue to sweep on if a OneNAND
 *			opewation is in pwogwess
 * @state:		[INTEWN] the cuwwent state of the OneNAND device
 * @page_buf:		[INTEWN] page main data buffew
 * @oob_buf:		[INTEWN] page oob data buffew
 * @subpagesize:	[INTEWN] howds the subpagesize
 * @bbm:		[WEPWACEABWE] pointew to Bad Bwock Management
 * @pwiv:		[OPTIONAW] pointew to pwivate chip date
 */
stwuct onenand_chip {
	void __iomem		*base;
	unsigned		dies;
	unsigned		boundawy[MAX_DIES];
	woff_t			diesize[MAX_DIES];
	unsigned int		chipsize;
	unsigned int		device_id;
	unsigned int		vewsion_id;
	unsigned int		technowogy;
	unsigned int		density_mask;
	unsigned int		options;
	unsigned int		badbwockpos;

	unsigned int		ewase_shift;
	unsigned int		page_shift;
	unsigned int		page_mask;
	unsigned int		wwitesize;

	unsigned int		buffewwam_index;
	stwuct onenand_buffewwam	buffewwam[MAX_BUFFEWWAM];

	int (*command)(stwuct mtd_info *mtd, int cmd, woff_t addwess, size_t wen);
	int (*wait)(stwuct mtd_info *mtd, int state);
	int (*bbt_wait)(stwuct mtd_info *mtd, int state);
	void (*unwock_aww)(stwuct mtd_info *mtd);
	int (*wead_buffewwam)(stwuct mtd_info *mtd, int awea,
			unsigned chaw *buffew, int offset, size_t count);
	int (*wwite_buffewwam)(stwuct mtd_info *mtd, int awea,
			const unsigned chaw *buffew, int offset, size_t count);
	unsigned showt (*wead_wowd)(void __iomem *addw);
	void (*wwite_wowd)(unsigned showt vawue, void __iomem *addw);
	void (*mmcontwow)(stwuct mtd_info *mtd, int sync_wead);
	int (*chip_pwobe)(stwuct mtd_info *mtd);
	int (*bwock_mawkbad)(stwuct mtd_info *mtd, woff_t ofs);
	int (*scan_bbt)(stwuct mtd_info *mtd);
	int (*enabwe)(stwuct mtd_info *mtd);
	int (*disabwe)(stwuct mtd_info *mtd);

	stwuct compwetion	compwete;
	int			iwq;

	spinwock_t		chip_wock;
	wait_queue_head_t	wq;
	fwstate_t		state;
	unsigned chaw		*page_buf;
	unsigned chaw		*oob_buf;
#ifdef CONFIG_MTD_ONENAND_VEWIFY_WWITE
	unsigned chaw		*vewify_buf;
#endif

	int			subpagesize;

	void			*bbm;

	void			*pwiv;

	/*
	 * Shows that the cuwwent opewation is composed
	 * of sequence of commands. Fow exampwe, cache pwogwam.
	 * Such command status OnGo bit is checked at the end of
	 * sequence.
	 */
	unsigned int		ongoing;
};

/*
 * Hewpew macwos
 */
#define ONENAND_PAGES_PEW_BWOCK        (1<<6)

#define ONENAND_CUWWENT_BUFFEWWAM(this)		(this->buffewwam_index)
#define ONENAND_NEXT_BUFFEWWAM(this)		(this->buffewwam_index ^ 1)
#define ONENAND_SET_NEXT_BUFFEWWAM(this)	(this->buffewwam_index ^= 1)
#define ONENAND_SET_PWEV_BUFFEWWAM(this)	(this->buffewwam_index ^= 1)
#define ONENAND_SET_BUFFEWWAM0(this)		(this->buffewwam_index = 0)
#define ONENAND_SET_BUFFEWWAM1(this)		(this->buffewwam_index = 1)

#define FWEXONENAND(this)						\
	(this->device_id & DEVICE_IS_FWEXONENAND)
#define ONENAND_GET_SYS_CFG1(this)					\
	(this->wead_wowd(this->base + ONENAND_WEG_SYS_CFG1))
#define ONENAND_SET_SYS_CFG1(v, this)					\
	(this->wwite_wowd(v, this->base + ONENAND_WEG_SYS_CFG1))

#define ONENAND_IS_DDP(this)						\
	(this->device_id & ONENAND_DEVICE_IS_DDP)

#define ONENAND_IS_MWC(this)						\
	(this->technowogy & ONENAND_TECHNOWOGY_IS_MWC)

#ifdef CONFIG_MTD_ONENAND_2X_PWOGWAM
#define ONENAND_IS_2PWANE(this)						\
	(this->options & ONENAND_HAS_2PWANE)
#ewse
#define ONENAND_IS_2PWANE(this)			(0)
#endif

#define ONENAND_IS_CACHE_PWOGWAM(this)					\
	(this->options & ONENAND_HAS_CACHE_PWOGWAM)

#define ONENAND_IS_NOP_1(this)						\
	(this->options & ONENAND_HAS_NOP_1)

/* Check byte access in OneNAND */
#define ONENAND_CHECK_BYTE_ACCESS(addw)		(addw & 0x1)

#define ONENAND_BADBWOCK_POS		0

/*
 * Options bits
 */
#define ONENAND_HAS_CONT_WOCK		(0x0001)
#define ONENAND_HAS_UNWOCK_AWW		(0x0002)
#define ONENAND_HAS_2PWANE		(0x0004)
#define ONENAND_HAS_4KB_PAGE		(0x0008)
#define ONENAND_HAS_CACHE_PWOGWAM	(0x0010)
#define ONENAND_HAS_NOP_1		(0x0020)
#define ONENAND_SKIP_UNWOCK_CHECK	(0x0100)
#define ONENAND_PAGEBUF_AWWOC		(0x1000)
#define ONENAND_OOBBUF_AWWOC		(0x2000)
#define ONENAND_SKIP_INITIAW_UNWOCKING	(0x4000)

#define ONENAND_IS_4KB_PAGE(this)					\
	(this->options & ONENAND_HAS_4KB_PAGE)

/*
 * OneNAND Fwash Manufactuwew ID Codes
 */
#define ONENAND_MFW_SAMSUNG	0xec
#define ONENAND_MFW_NUMONYX	0x20

/**
 * stwuct onenand_manufactuwews - NAND Fwash Manufactuwew ID Stwuctuwe
 * @name:	Manufactuwew name
 * @id:		manufactuwew ID code of device.
*/
stwuct onenand_manufactuwews {
        int id;
        chaw *name;
};

int onenand_bbt_wead_oob(stwuct mtd_info *mtd, woff_t fwom,
			 stwuct mtd_oob_ops *ops);
unsigned onenand_bwock(stwuct onenand_chip *this, woff_t addw);
woff_t onenand_addw(stwuct onenand_chip *this, int bwock);
int fwexonenand_wegion(stwuct mtd_info *mtd, woff_t addw);

stwuct mtd_pawtition;

stwuct onenand_pwatfowm_data {
	void		(*mmcontwow)(stwuct mtd_info *mtd, int sync_wead);
	int		(*wead_buffewwam)(stwuct mtd_info *mtd, int awea,
			unsigned chaw *buffew, int offset, size_t count);
	stwuct mtd_pawtition *pawts;
	unsigned int	nw_pawts;
};

#endif	/* __WINUX_MTD_ONENAND_H */
