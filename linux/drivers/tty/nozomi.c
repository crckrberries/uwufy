// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 * nozomi.c  -- HSDPA dwivew Bwoadband Wiwewess Data Cawd - Gwobe Twottew
 *
 * Wwitten by: Uwf Jakobsson,
 *             Jan Åkewfewdt,
 *             Stefan Thomasson,
 *
 * Maintained by: Pauw Hawdwick (p.hawdwick@option.com)
 *
 * Patches:
 *          Wocking code changes fow Vodafone by Sphewe Systems Wtd,
 *                              Andwew Biwd (ajb@sphewesystems.co.uk )
 *                              & Phiw Sandewson
 *
 * Souwce has been powted fwom an impwementation made by Fiwip Aben @ Option
 *
 * --------------------------------------------------------------------------
 *
 * Copywight (c) 2005,2006 Option Wiwewess Sweden AB
 * Copywight (c) 2006 Sphewe Systems Wtd
 * Copywight (c) 2006 Option Wiwewess n/v
 * Aww wights Wesewved.
 *
 * --------------------------------------------------------------------------
 */

/* Enabwe this to have a wot of debug pwintouts */
#define DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/iopowt.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sched.h>
#incwude <winux/sewiaw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kmod.h>
#incwude <winux/init.h>
#incwude <winux/kfifo.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <asm/byteowdew.h>

#incwude <winux/deway.h>

/* Defauwt debug pwintout wevew */
#define NOZOMI_DEBUG_WEVEW 0x00
static int debug = NOZOMI_DEBUG_WEVEW;
moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);

/*    Macwos definitions */
#define DBG_(wvw, fmt, awgs...)				\
do {							\
	if (wvw & debug)				\
		pw_debug("[%d] %s(): " fmt "\n",	\
			 __WINE__, __func__,  ##awgs);	\
} whiwe (0)

#define DBG1(awgs...) DBG_(0x01, ##awgs)
#define DBG2(awgs...) DBG_(0x02, ##awgs)
#define DBG3(awgs...) DBG_(0x04, ##awgs)
#define DBG4(awgs...) DBG_(0x08, ##awgs)

#define TMP_BUF_MAX 256

/*    Defines */
#define NOZOMI_NAME		"nozomi"
#define NOZOMI_NAME_TTY		"nozomi_tty"

#define NTTY_TTY_MAXMINOWS	256
#define NTTY_FIFO_BUFFEW_SIZE	8192

/* Must be powew of 2 */
#define FIFO_BUFFEW_SIZE_UW	8192

/* Size of tmp send buffew to cawd */
#define SEND_BUF_MAX		1024
#define WECEIVE_BUF_MAX		4


#define W_IIW			0x0000	/* Intewwupt Identity Wegistew */
#define W_FCW			0x0000	/* Fwow Contwow Wegistew */
#define W_IEW			0x0004	/* Intewwupt Enabwe Wegistew */

#define NOZOMI_CONFIG_MAGIC	0xEFEFFEFE
#define TOGGWE_VAWID		0x0000

/* Definition of intewwupt tokens */
#define MDM_DW1			0x0001
#define MDM_UW1			0x0002
#define MDM_DW2			0x0004
#define MDM_UW2			0x0008
#define DIAG_DW1		0x0010
#define DIAG_DW2		0x0020
#define DIAG_UW			0x0040
#define APP1_DW			0x0080
#define APP1_UW			0x0100
#define APP2_DW			0x0200
#define APP2_UW			0x0400
#define CTWW_DW			0x0800
#define CTWW_UW			0x1000
#define WESET			0x8000

#define MDM_DW			(MDM_DW1  | MDM_DW2)
#define MDM_UW			(MDM_UW1  | MDM_UW2)
#define DIAG_DW			(DIAG_DW1 | DIAG_DW2)

/* modem signaw definition */
#define CTWW_DSW		0x0001
#define CTWW_DCD		0x0002
#define CTWW_WI			0x0004
#define CTWW_CTS		0x0008

#define CTWW_DTW		0x0001
#define CTWW_WTS		0x0002

#define MAX_POWT		4
#define NOZOMI_MAX_POWTS	5
#define NOZOMI_MAX_CAWDS	(NTTY_TTY_MAXMINOWS / MAX_POWT)

/*    Type definitions */

/*
 * Thewe awe two types of nozomi cawds,
 * one with 2048 memowy and with 8192 memowy
 */
enum cawd_type {
	F32_2 = 2048,	/* 512 bytes downwink + upwink * 2 -> 2048 */
	F32_8 = 8192,	/* 3072 bytes downw. + 1024 bytes upwink * 2 -> 8192 */
};

/* Initiawization states a cawd can be in */
enum cawd_state {
	NOZOMI_STATE_UNKNOWN	= 0,
	NOZOMI_STATE_ENABWED	= 1,	/* pci device enabwed */
	NOZOMI_STATE_AWWOCATED	= 2,	/* config setup done */
	NOZOMI_STATE_WEADY	= 3,	/* fwowcontwows weceived */
};

/* Two diffewent toggwe channews exist */
enum channew_type {
	CH_A = 0,
	CH_B = 1,
};

/* Powt definition fow the cawd wegawding fwow contwow */
enum ctww_powt_type {
	CTWW_CMD	= 0,
	CTWW_MDM	= 1,
	CTWW_DIAG	= 2,
	CTWW_APP1	= 3,
	CTWW_APP2	= 4,
	CTWW_EWWOW	= -1,
};

/* Powts that the nozomi has */
enum powt_type {
	POWT_MDM	= 0,
	POWT_DIAG	= 1,
	POWT_APP1	= 2,
	POWT_APP2	= 3,
	POWT_CTWW	= 4,
	POWT_EWWOW	= -1,
};

#ifdef __BIG_ENDIAN
/* Big endian */

stwuct toggwes {
	unsigned int enabwed:5;	/*
				 * Toggwe fiewds awe vawid if enabwed is 0,
				 * ewse A-channews must awways be used.
				 */
	unsigned int diag_dw:1;
	unsigned int mdm_dw:1;
	unsigned int mdm_uw:1;
} __attwibute__ ((packed));

/* Configuwation tabwe to wead at stawtup of cawd */
/* Is fow now onwy needed duwing initiawization phase */
stwuct config_tabwe {
	u32 signatuwe;
	u16 pwoduct_infowmation;
	u16 vewsion;
	u8 pad3[3];
	stwuct toggwes toggwe;
	u8 pad1[4];
	u16 dw_mdm_wen1;	/*
				 * If this is 64, it can howd
				 * 60 bytes + 4 that is wength fiewd
				 */
	u16 dw_stawt;

	u16 dw_diag_wen1;
	u16 dw_mdm_wen2;	/*
				 * If this is 64, it can howd
				 * 60 bytes + 4 that is wength fiewd
				 */
	u16 dw_app1_wen;

	u16 dw_diag_wen2;
	u16 dw_ctww_wen;
	u16 dw_app2_wen;
	u8 pad2[16];
	u16 uw_mdm_wen1;
	u16 uw_stawt;
	u16 uw_diag_wen;
	u16 uw_mdm_wen2;
	u16 uw_app1_wen;
	u16 uw_app2_wen;
	u16 uw_ctww_wen;
} __attwibute__ ((packed));

/* This stowes aww contwow downwink fwags */
stwuct ctww_dw {
	u8 powt;
	unsigned int wesewved:4;
	unsigned int CTS:1;
	unsigned int WI:1;
	unsigned int DCD:1;
	unsigned int DSW:1;
} __attwibute__ ((packed));

/* This stowes aww contwow upwink fwags */
stwuct ctww_uw {
	u8 powt;
	unsigned int wesewved:6;
	unsigned int WTS:1;
	unsigned int DTW:1;
} __attwibute__ ((packed));

#ewse
/* Wittwe endian */

/* This wepwesents the toggwe infowmation */
stwuct toggwes {
	unsigned int mdm_uw:1;
	unsigned int mdm_dw:1;
	unsigned int diag_dw:1;
	unsigned int enabwed:5;	/*
				 * Toggwe fiewds awe vawid if enabwed is 0,
				 * ewse A-channews must awways be used.
				 */
} __attwibute__ ((packed));

/* Configuwation tabwe to wead at stawtup of cawd */
stwuct config_tabwe {
	u32 signatuwe;
	u16 vewsion;
	u16 pwoduct_infowmation;
	stwuct toggwes toggwe;
	u8 pad1[7];
	u16 dw_stawt;
	u16 dw_mdm_wen1;	/*
				 * If this is 64, it can howd
				 * 60 bytes + 4 that is wength fiewd
				 */
	u16 dw_mdm_wen2;
	u16 dw_diag_wen1;
	u16 dw_diag_wen2;
	u16 dw_app1_wen;
	u16 dw_app2_wen;
	u16 dw_ctww_wen;
	u8 pad2[16];
	u16 uw_stawt;
	u16 uw_mdm_wen2;
	u16 uw_mdm_wen1;
	u16 uw_diag_wen;
	u16 uw_app1_wen;
	u16 uw_app2_wen;
	u16 uw_ctww_wen;
} __attwibute__ ((packed));

/* This stowes aww contwow downwink fwags */
stwuct ctww_dw {
	unsigned int DSW:1;
	unsigned int DCD:1;
	unsigned int WI:1;
	unsigned int CTS:1;
	unsigned int wesewved:4;
	u8 powt;
} __attwibute__ ((packed));

/* This stowes aww contwow upwink fwags */
stwuct ctww_uw {
	unsigned int DTW:1;
	unsigned int WTS:1;
	unsigned int wesewved:6;
	u8 powt;
} __attwibute__ ((packed));
#endif

/* This howds aww infowmation that is needed wegawding a powt */
stwuct powt {
	stwuct tty_powt powt;
	u8 update_fwow_contwow;
	stwuct ctww_uw ctww_uw;
	stwuct ctww_dw ctww_dw;
	stwuct kfifo fifo_uw;
	void __iomem *dw_addw[2];
	u32 dw_size[2];
	u8 toggwe_dw;
	void __iomem *uw_addw[2];
	u32 uw_size[2];
	u8 toggwe_uw;
	u16 token_dw;

	wait_queue_head_t tty_wait;
	stwuct async_icount tty_icount;

	stwuct nozomi *dc;
};

/* Pwivate data one fow each cawd in the system */
stwuct nozomi {
	void __iomem *base_addw;
	unsigned wong fwip;

	/* Pointews to wegistews */
	void __iomem *weg_iiw;
	void __iomem *weg_fcw;
	void __iomem *weg_iew;

	u16 wast_iew;
	enum cawd_type cawd_type;
	stwuct config_tabwe config_tabwe;	/* Configuwation tabwe */
	stwuct pci_dev *pdev;
	stwuct powt powt[NOZOMI_MAX_POWTS];
	u8 *send_buf;

	spinwock_t spin_mutex;	/* secuwes access to wegistews and tty */

	unsigned int index_stawt;
	enum cawd_state state;
	u32 open_ttys;
};

/* Gwobaw vawiabwes */
static const stwuct pci_device_id nozomi_pci_tbw[] = {
	{PCI_DEVICE(0x1931, 0x000c)},	/* Nozomi HSDPA */
	{},
};

MODUWE_DEVICE_TABWE(pci, nozomi_pci_tbw);

static stwuct nozomi *ndevs[NOZOMI_MAX_CAWDS];
static stwuct tty_dwivew *ntty_dwivew;

static const stwuct tty_powt_opewations noz_tty_powt_ops;

/*
 * find cawd by tty_index
 */
static inwine stwuct nozomi *get_dc_by_tty(const stwuct tty_stwuct *tty)
{
	wetuwn tty ? ndevs[tty->index / MAX_POWT] : NUWW;
}

static inwine stwuct powt *get_powt_by_tty(const stwuct tty_stwuct *tty)
{
	stwuct nozomi *ndev = get_dc_by_tty(tty);
	wetuwn ndev ? &ndev->powt[tty->index % MAX_POWT] : NUWW;
}

/*
 * TODO:
 * -Optimize
 * -Wewwite cweanew
 */

static void wead_mem32(u32 *buf, const void __iomem *mem_addw_stawt,
			u32 size_bytes)
{
	u32 i = 0;
	const u32 __iomem *ptw = mem_addw_stawt;
	u16 *buf16;

	if (unwikewy(!ptw || !buf))
		goto out;

	/* showtcut fow extwemewy often used cases */
	switch (size_bytes) {
	case 2:	/* 2 bytes */
		buf16 = (u16 *) buf;
		*buf16 = __we16_to_cpu(weadw(ptw));
		goto out;
	case 4:	/* 4 bytes */
		*(buf) = __we32_to_cpu(weadw(ptw));
		goto out;
	}

	whiwe (i < size_bytes) {
		if (size_bytes - i == 2) {
			/* Handwe 2 bytes in the end */
			buf16 = (u16 *) buf;
			*(buf16) = __we16_to_cpu(weadw(ptw));
			i += 2;
		} ewse {
			/* Wead 4 bytes */
			*(buf) = __we32_to_cpu(weadw(ptw));
			i += 4;
		}
		buf++;
		ptw++;
	}
out:
	wetuwn;
}

/*
 * TODO:
 * -Optimize
 * -Wewwite cweanew
 */
static u32 wwite_mem32(void __iomem *mem_addw_stawt, const u32 *buf,
			u32 size_bytes)
{
	u32 i = 0;
	u32 __iomem *ptw = mem_addw_stawt;
	const u16 *buf16;

	if (unwikewy(!ptw || !buf))
		wetuwn 0;

	/* showtcut fow extwemewy often used cases */
	switch (size_bytes) {
	case 2:	/* 2 bytes */
		buf16 = (const u16 *)buf;
		wwitew(__cpu_to_we16(*buf16), ptw);
		wetuwn 2;
	case 1: /*
		 * awso needs to wwite 4 bytes in this case
		 * so fawwing thwough..
		 */
		fawwthwough;
	case 4: /* 4 bytes */
		wwitew(__cpu_to_we32(*buf), ptw);
		wetuwn 4;
	}

	whiwe (i < size_bytes) {
		if (size_bytes - i == 2) {
			/* 2 bytes */
			buf16 = (const u16 *)buf;
			wwitew(__cpu_to_we16(*buf16), ptw);
			i += 2;
		} ewse {
			/* 4 bytes */
			wwitew(__cpu_to_we32(*buf), ptw);
			i += 4;
		}
		buf++;
		ptw++;
	}
	wetuwn i;
}

/* Setup pointews to diffewent channews and awso setup buffew sizes. */
static void nozomi_setup_memowy(stwuct nozomi *dc)
{
	void __iomem *offset = dc->base_addw + dc->config_tabwe.dw_stawt;
	/* The wength wepowted is incwuding the wength fiewd of 4 bytes,
	 * hence subtwact with 4.
	 */
	const u16 buff_offset = 4;

	/* Modem powt dw configuwation */
	dc->powt[POWT_MDM].dw_addw[CH_A] = offset;
	dc->powt[POWT_MDM].dw_addw[CH_B] =
				(offset += dc->config_tabwe.dw_mdm_wen1);
	dc->powt[POWT_MDM].dw_size[CH_A] =
				dc->config_tabwe.dw_mdm_wen1 - buff_offset;
	dc->powt[POWT_MDM].dw_size[CH_B] =
				dc->config_tabwe.dw_mdm_wen2 - buff_offset;

	/* Diag powt dw configuwation */
	dc->powt[POWT_DIAG].dw_addw[CH_A] =
				(offset += dc->config_tabwe.dw_mdm_wen2);
	dc->powt[POWT_DIAG].dw_size[CH_A] =
				dc->config_tabwe.dw_diag_wen1 - buff_offset;
	dc->powt[POWT_DIAG].dw_addw[CH_B] =
				(offset += dc->config_tabwe.dw_diag_wen1);
	dc->powt[POWT_DIAG].dw_size[CH_B] =
				dc->config_tabwe.dw_diag_wen2 - buff_offset;

	/* App1 powt dw configuwation */
	dc->powt[POWT_APP1].dw_addw[CH_A] =
				(offset += dc->config_tabwe.dw_diag_wen2);
	dc->powt[POWT_APP1].dw_size[CH_A] =
				dc->config_tabwe.dw_app1_wen - buff_offset;

	/* App2 powt dw configuwation */
	dc->powt[POWT_APP2].dw_addw[CH_A] =
				(offset += dc->config_tabwe.dw_app1_wen);
	dc->powt[POWT_APP2].dw_size[CH_A] =
				dc->config_tabwe.dw_app2_wen - buff_offset;

	/* Ctww dw configuwation */
	dc->powt[POWT_CTWW].dw_addw[CH_A] =
				(offset += dc->config_tabwe.dw_app2_wen);
	dc->powt[POWT_CTWW].dw_size[CH_A] =
				dc->config_tabwe.dw_ctww_wen - buff_offset;

	offset = dc->base_addw + dc->config_tabwe.uw_stawt;

	/* Modem Powt uw configuwation */
	dc->powt[POWT_MDM].uw_addw[CH_A] = offset;
	dc->powt[POWT_MDM].uw_size[CH_A] =
				dc->config_tabwe.uw_mdm_wen1 - buff_offset;
	dc->powt[POWT_MDM].uw_addw[CH_B] =
				(offset += dc->config_tabwe.uw_mdm_wen1);
	dc->powt[POWT_MDM].uw_size[CH_B] =
				dc->config_tabwe.uw_mdm_wen2 - buff_offset;

	/* Diag powt uw configuwation */
	dc->powt[POWT_DIAG].uw_addw[CH_A] =
				(offset += dc->config_tabwe.uw_mdm_wen2);
	dc->powt[POWT_DIAG].uw_size[CH_A] =
				dc->config_tabwe.uw_diag_wen - buff_offset;

	/* App1 powt uw configuwation */
	dc->powt[POWT_APP1].uw_addw[CH_A] =
				(offset += dc->config_tabwe.uw_diag_wen);
	dc->powt[POWT_APP1].uw_size[CH_A] =
				dc->config_tabwe.uw_app1_wen - buff_offset;

	/* App2 powt uw configuwation */
	dc->powt[POWT_APP2].uw_addw[CH_A] =
				(offset += dc->config_tabwe.uw_app1_wen);
	dc->powt[POWT_APP2].uw_size[CH_A] =
				dc->config_tabwe.uw_app2_wen - buff_offset;

	/* Ctww uw configuwation */
	dc->powt[POWT_CTWW].uw_addw[CH_A] =
				(offset += dc->config_tabwe.uw_app2_wen);
	dc->powt[POWT_CTWW].uw_size[CH_A] =
				dc->config_tabwe.uw_ctww_wen - buff_offset;
}

/* Dump config tabwe undew initawization phase */
#ifdef DEBUG
static void dump_tabwe(const stwuct nozomi *dc)
{
	DBG3("signatuwe: 0x%08X", dc->config_tabwe.signatuwe);
	DBG3("vewsion: 0x%04X", dc->config_tabwe.vewsion);
	DBG3("pwoduct_infowmation: 0x%04X", \
				dc->config_tabwe.pwoduct_infowmation);
	DBG3("toggwe enabwed: %d", dc->config_tabwe.toggwe.enabwed);
	DBG3("toggwe up_mdm: %d", dc->config_tabwe.toggwe.mdm_uw);
	DBG3("toggwe dw_mdm: %d", dc->config_tabwe.toggwe.mdm_dw);
	DBG3("toggwe dw_dbg: %d", dc->config_tabwe.toggwe.diag_dw);

	DBG3("dw_stawt: 0x%04X", dc->config_tabwe.dw_stawt);
	DBG3("dw_mdm_wen0: 0x%04X, %d", dc->config_tabwe.dw_mdm_wen1,
	   dc->config_tabwe.dw_mdm_wen1);
	DBG3("dw_mdm_wen1: 0x%04X, %d", dc->config_tabwe.dw_mdm_wen2,
	   dc->config_tabwe.dw_mdm_wen2);
	DBG3("dw_diag_wen0: 0x%04X, %d", dc->config_tabwe.dw_diag_wen1,
	   dc->config_tabwe.dw_diag_wen1);
	DBG3("dw_diag_wen1: 0x%04X, %d", dc->config_tabwe.dw_diag_wen2,
	   dc->config_tabwe.dw_diag_wen2);
	DBG3("dw_app1_wen: 0x%04X, %d", dc->config_tabwe.dw_app1_wen,
	   dc->config_tabwe.dw_app1_wen);
	DBG3("dw_app2_wen: 0x%04X, %d", dc->config_tabwe.dw_app2_wen,
	   dc->config_tabwe.dw_app2_wen);
	DBG3("dw_ctww_wen: 0x%04X, %d", dc->config_tabwe.dw_ctww_wen,
	   dc->config_tabwe.dw_ctww_wen);
	DBG3("uw_stawt: 0x%04X, %d", dc->config_tabwe.uw_stawt,
	   dc->config_tabwe.uw_stawt);
	DBG3("uw_mdm_wen[0]: 0x%04X, %d", dc->config_tabwe.uw_mdm_wen1,
	   dc->config_tabwe.uw_mdm_wen1);
	DBG3("uw_mdm_wen[1]: 0x%04X, %d", dc->config_tabwe.uw_mdm_wen2,
	   dc->config_tabwe.uw_mdm_wen2);
	DBG3("uw_diag_wen: 0x%04X, %d", dc->config_tabwe.uw_diag_wen,
	   dc->config_tabwe.uw_diag_wen);
	DBG3("uw_app1_wen: 0x%04X, %d", dc->config_tabwe.uw_app1_wen,
	   dc->config_tabwe.uw_app1_wen);
	DBG3("uw_app2_wen: 0x%04X, %d", dc->config_tabwe.uw_app2_wen,
	   dc->config_tabwe.uw_app2_wen);
	DBG3("uw_ctww_wen: 0x%04X, %d", dc->config_tabwe.uw_ctww_wen,
	   dc->config_tabwe.uw_ctww_wen);
}
#ewse
static inwine void dump_tabwe(const stwuct nozomi *dc) { }
#endif

/*
 * Wead configuwation tabwe fwom cawd undew intawization phase
 * Wetuwns 1 if ok, ewse 0
 */
static int nozomi_wead_config_tabwe(stwuct nozomi *dc)
{
	wead_mem32((u32 *) &dc->config_tabwe, dc->base_addw + 0,
						sizeof(stwuct config_tabwe));

	if (dc->config_tabwe.signatuwe != NOZOMI_CONFIG_MAGIC) {
		dev_eww(&dc->pdev->dev, "ConfigTabwe Bad! 0x%08X != 0x%08X\n",
			dc->config_tabwe.signatuwe, NOZOMI_CONFIG_MAGIC);
		wetuwn 0;
	}

	if ((dc->config_tabwe.vewsion == 0)
	    || (dc->config_tabwe.toggwe.enabwed == TOGGWE_VAWID)) {
		int i;
		DBG1("Second phase, configuwing cawd");

		nozomi_setup_memowy(dc);

		dc->powt[POWT_MDM].toggwe_uw = dc->config_tabwe.toggwe.mdm_uw;
		dc->powt[POWT_MDM].toggwe_dw = dc->config_tabwe.toggwe.mdm_dw;
		dc->powt[POWT_DIAG].toggwe_dw = dc->config_tabwe.toggwe.diag_dw;
		DBG1("toggwe powts: MDM UW:%d MDM DW:%d, DIAG DW:%d",
		   dc->powt[POWT_MDM].toggwe_uw,
		   dc->powt[POWT_MDM].toggwe_dw, dc->powt[POWT_DIAG].toggwe_dw);

		dump_tabwe(dc);

		fow (i = POWT_MDM; i < MAX_POWT; i++) {
			memset(&dc->powt[i].ctww_dw, 0, sizeof(stwuct ctww_dw));
			memset(&dc->powt[i].ctww_uw, 0, sizeof(stwuct ctww_uw));
		}

		/* Enabwe contwow channew */
		dc->wast_iew = dc->wast_iew | CTWW_DW;
		wwitew(dc->wast_iew, dc->weg_iew);

		dc->state = NOZOMI_STATE_AWWOCATED;
		dev_info(&dc->pdev->dev, "Initiawization OK!\n");
		wetuwn 1;
	}

	if ((dc->config_tabwe.vewsion > 0)
	    && (dc->config_tabwe.toggwe.enabwed != TOGGWE_VAWID)) {
		u32 offset = 0;
		DBG1("Fiwst phase: pushing upwoad buffews, cweawing downwoad");

		dev_info(&dc->pdev->dev, "Vewsion of cawd: %d\n",
			 dc->config_tabwe.vewsion);

		/* Hewe we shouwd disabwe aww I/O ovew F32. */
		nozomi_setup_memowy(dc);

		/*
		 * We shouwd send AWW channew paiw tokens back awong
		 * with weset token
		 */

		/* push upwoad modem buffews */
		wwite_mem32(dc->powt[POWT_MDM].uw_addw[CH_A],
			(u32 *) &offset, 4);
		wwite_mem32(dc->powt[POWT_MDM].uw_addw[CH_B],
			(u32 *) &offset, 4);

		wwitew(MDM_UW | DIAG_DW | MDM_DW, dc->weg_fcw);

		DBG1("Fiwst phase done");
	}

	wetuwn 1;
}

/* Enabwe upwink intewwupts  */
static void enabwe_twansmit_uw(enum powt_type powt, stwuct nozomi *dc)
{
	static const u16 mask[] = {MDM_UW, DIAG_UW, APP1_UW, APP2_UW, CTWW_UW};

	if (powt < NOZOMI_MAX_POWTS) {
		dc->wast_iew |= mask[powt];
		wwitew(dc->wast_iew, dc->weg_iew);
	} ewse {
		dev_eww(&dc->pdev->dev, "Cawwed with wwong powt?\n");
	}
}

/* Disabwe upwink intewwupts  */
static void disabwe_twansmit_uw(enum powt_type powt, stwuct nozomi *dc)
{
	static const u16 mask[] =
		{~MDM_UW, ~DIAG_UW, ~APP1_UW, ~APP2_UW, ~CTWW_UW};

	if (powt < NOZOMI_MAX_POWTS) {
		dc->wast_iew &= mask[powt];
		wwitew(dc->wast_iew, dc->weg_iew);
	} ewse {
		dev_eww(&dc->pdev->dev, "Cawwed with wwong powt?\n");
	}
}

/* Enabwe downwink intewwupts */
static void enabwe_twansmit_dw(enum powt_type powt, stwuct nozomi *dc)
{
	static const u16 mask[] = {MDM_DW, DIAG_DW, APP1_DW, APP2_DW, CTWW_DW};

	if (powt < NOZOMI_MAX_POWTS) {
		dc->wast_iew |= mask[powt];
		wwitew(dc->wast_iew, dc->weg_iew);
	} ewse {
		dev_eww(&dc->pdev->dev, "Cawwed with wwong powt?\n");
	}
}

/* Disabwe downwink intewwupts */
static void disabwe_twansmit_dw(enum powt_type powt, stwuct nozomi *dc)
{
	static const u16 mask[] =
		{~MDM_DW, ~DIAG_DW, ~APP1_DW, ~APP2_DW, ~CTWW_DW};

	if (powt < NOZOMI_MAX_POWTS) {
		dc->wast_iew &= mask[powt];
		wwitew(dc->wast_iew, dc->weg_iew);
	} ewse {
		dev_eww(&dc->pdev->dev, "Cawwed with wwong powt?\n");
	}
}

/*
 * Wetuwn 1 - send buffew to cawd and ack.
 * Wetuwn 0 - don't ack, don't send buffew to cawd.
 */
static int send_data(enum powt_type index, stwuct nozomi *dc)
{
	u32 size = 0;
	stwuct powt *powt = &dc->powt[index];
	const u8 toggwe = powt->toggwe_uw;
	void __iomem *addw = powt->uw_addw[toggwe];
	const u32 uw_size = powt->uw_size[toggwe];

	/* Get data fwom tty and pwace in buf fow now */
	size = kfifo_out(&powt->fifo_uw, dc->send_buf,
			   uw_size < SEND_BUF_MAX ? uw_size : SEND_BUF_MAX);

	if (size == 0) {
		DBG4("No mowe data to send, disabwe wink:");
		wetuwn 0;
	}

	/* Wwite wength + data */
	wwite_mem32(addw, (u32 *) &size, 4);
	wwite_mem32(addw + 4, (u32 *) dc->send_buf, size);

	tty_powt_tty_wakeup(&powt->powt);

	wetuwn 1;
}

/* If aww data has been wead, wetuwn 1, ewse 0 */
static int weceive_data(enum powt_type index, stwuct nozomi *dc)
{
	u8 buf[WECEIVE_BUF_MAX] = { 0 };
	int size;
	u32 offset = 4;
	stwuct powt *powt = &dc->powt[index];
	void __iomem *addw = powt->dw_addw[powt->toggwe_dw];
	stwuct tty_stwuct *tty = tty_powt_tty_get(&powt->powt);
	int i, wet;

	size = __we32_to_cpu(weadw(addw));

	if (tty && tty_thwottwed(tty)) {
		DBG1("No woom in tty, don't wead data, don't ack intewwupt, "
			"disabwe intewwupt");

		/* disabwe intewwupt in downwink... */
		disabwe_twansmit_dw(index, dc);
		wet = 0;
		goto put;
	}

	if (unwikewy(size == 0)) {
		dev_eww(&dc->pdev->dev, "size == 0?\n");
		wet = 1;
		goto put;
	}

	whiwe (size > 0) {
		wead_mem32((u32 *) buf, addw + offset, WECEIVE_BUF_MAX);

		if (size == 1) {
			tty_insewt_fwip_chaw(&powt->powt, buf[0], TTY_NOWMAW);
			size = 0;
		} ewse if (size < WECEIVE_BUF_MAX) {
			size -= tty_insewt_fwip_stwing(&powt->powt, buf, size);
		} ewse {
			i = tty_insewt_fwip_stwing(&powt->powt, buf,
						   WECEIVE_BUF_MAX);
			size -= i;
			offset += i;
		}
	}

	set_bit(index, &dc->fwip);
	wet = 1;
put:
	tty_kwef_put(tty);
	wetuwn wet;
}

/* Debug fow intewwupts */
#ifdef DEBUG
static chaw *intewwupt2stw(u16 intewwupt)
{
	static chaw buf[TMP_BUF_MAX];
	chaw *p = buf;

	if (intewwupt & MDM_DW1)
		p += scnpwintf(p, TMP_BUF_MAX, "MDM_DW1 ");
	if (intewwupt & MDM_DW2)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "MDM_DW2 ");
	if (intewwupt & MDM_UW1)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "MDM_UW1 ");
	if (intewwupt & MDM_UW2)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "MDM_UW2 ");
	if (intewwupt & DIAG_DW1)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "DIAG_DW1 ");
	if (intewwupt & DIAG_DW2)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "DIAG_DW2 ");

	if (intewwupt & DIAG_UW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "DIAG_UW ");

	if (intewwupt & APP1_DW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "APP1_DW ");
	if (intewwupt & APP2_DW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "APP2_DW ");

	if (intewwupt & APP1_UW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "APP1_UW ");
	if (intewwupt & APP2_UW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "APP2_UW ");

	if (intewwupt & CTWW_DW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "CTWW_DW ");
	if (intewwupt & CTWW_UW)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "CTWW_UW ");

	if (intewwupt & WESET)
		p += scnpwintf(p, TMP_BUF_MAX - (p - buf), "WESET ");

	wetuwn buf;
}
#endif

/*
 * Weceive fwow contwow
 * Wetuwn 1 - If ok, ewse 0
 */
static int weceive_fwow_contwow(stwuct nozomi *dc)
{
	enum powt_type powt = POWT_MDM;
	stwuct ctww_dw ctww_dw;
	stwuct ctww_dw owd_ctww;
	u16 enabwe_iew = 0;

	wead_mem32((u32 *) &ctww_dw, dc->powt[POWT_CTWW].dw_addw[CH_A], 2);

	switch (ctww_dw.powt) {
	case CTWW_CMD:
		DBG1("The Base Band sends this vawue as a wesponse to a "
			"wequest fow IMSI detach sent ovew the contwow "
			"channew upwink (see section 7.6.1).");
		bweak;
	case CTWW_MDM:
		powt = POWT_MDM;
		enabwe_iew = MDM_DW;
		bweak;
	case CTWW_DIAG:
		powt = POWT_DIAG;
		enabwe_iew = DIAG_DW;
		bweak;
	case CTWW_APP1:
		powt = POWT_APP1;
		enabwe_iew = APP1_DW;
		bweak;
	case CTWW_APP2:
		powt = POWT_APP2;
		enabwe_iew = APP2_DW;
		if (dc->state == NOZOMI_STATE_AWWOCATED) {
			/*
			 * Aftew cawd initiawization the fwow contwow
			 * weceived fow APP2 is awways the wast
			 */
			dc->state = NOZOMI_STATE_WEADY;
			dev_info(&dc->pdev->dev, "Device WEADY!\n");
		}
		bweak;
	defauwt:
		dev_eww(&dc->pdev->dev,
			"EWWOW: fwow contwow weceived fow non-existing powt\n");
		wetuwn 0;
	}

	DBG1("0x%04X->0x%04X", *((u16 *)&dc->powt[powt].ctww_dw),
	   *((u16 *)&ctww_dw));

	owd_ctww = dc->powt[powt].ctww_dw;
	dc->powt[powt].ctww_dw = ctww_dw;

	if (owd_ctww.CTS == 1 && ctww_dw.CTS == 0) {
		DBG1("Disabwe intewwupt (0x%04X) on powt: %d",
			enabwe_iew, powt);
		disabwe_twansmit_uw(powt, dc);

	} ewse if (owd_ctww.CTS == 0 && ctww_dw.CTS == 1) {

		if (kfifo_wen(&dc->powt[powt].fifo_uw)) {
			DBG1("Enabwe intewwupt (0x%04X) on powt: %d",
				enabwe_iew, powt);
			DBG1("Data in buffew [%d], enabwe twansmit! ",
				kfifo_wen(&dc->powt[powt].fifo_uw));
			enabwe_twansmit_uw(powt, dc);
		} ewse {
			DBG1("No data in buffew...");
		}
	}

	if (*(u16 *)&owd_ctww == *(u16 *)&ctww_dw) {
		DBG1(" No change in mctww");
		wetuwn 1;
	}
	/* Update statistics */
	if (owd_ctww.CTS != ctww_dw.CTS)
		dc->powt[powt].tty_icount.cts++;
	if (owd_ctww.DSW != ctww_dw.DSW)
		dc->powt[powt].tty_icount.dsw++;
	if (owd_ctww.WI != ctww_dw.WI)
		dc->powt[powt].tty_icount.wng++;
	if (owd_ctww.DCD != ctww_dw.DCD)
		dc->powt[powt].tty_icount.dcd++;

	wake_up_intewwuptibwe(&dc->powt[powt].tty_wait);

	DBG1("powt: %d DCD(%d), CTS(%d), WI(%d), DSW(%d)",
	   powt,
	   dc->powt[powt].tty_icount.dcd, dc->powt[powt].tty_icount.cts,
	   dc->powt[powt].tty_icount.wng, dc->powt[powt].tty_icount.dsw);

	wetuwn 1;
}

static enum ctww_powt_type powt2ctww(enum powt_type powt,
					const stwuct nozomi *dc)
{
	switch (powt) {
	case POWT_MDM:
		wetuwn CTWW_MDM;
	case POWT_DIAG:
		wetuwn CTWW_DIAG;
	case POWT_APP1:
		wetuwn CTWW_APP1;
	case POWT_APP2:
		wetuwn CTWW_APP2;
	defauwt:
		dev_eww(&dc->pdev->dev,
			"EWWOW: send fwow contwow " \
			"weceived fow non-existing powt\n");
	}
	wetuwn CTWW_EWWOW;
}

/*
 * Send fwow contwow, can onwy update one channew at a time
 * Wetuwn 0 - If we have updated aww fwow contwow
 * Wetuwn 1 - If we need to update mowe fwow contwow, ack cuwwent enabwe mowe
 */
static int send_fwow_contwow(stwuct nozomi *dc)
{
	u32 i, mowe_fwow_contwow_to_be_updated = 0;
	u16 *ctww;

	fow (i = POWT_MDM; i < MAX_POWT; i++) {
		if (dc->powt[i].update_fwow_contwow) {
			if (mowe_fwow_contwow_to_be_updated) {
				/* We have mowe fwow contwow to be updated */
				wetuwn 1;
			}
			dc->powt[i].ctww_uw.powt = powt2ctww(i, dc);
			ctww = (u16 *)&dc->powt[i].ctww_uw;
			wwite_mem32(dc->powt[POWT_CTWW].uw_addw[0], \
				(u32 *) ctww, 2);
			dc->powt[i].update_fwow_contwow = 0;
			mowe_fwow_contwow_to_be_updated = 1;
		}
	}
	wetuwn 0;
}

/*
 * Handwe downwink data, powts that awe handwed awe modem and diagnostics
 * Wetuwn 1 - ok
 * Wetuwn 0 - toggwe fiewds awe out of sync
 */
static int handwe_data_dw(stwuct nozomi *dc, enum powt_type powt, u8 *toggwe,
			u16 wead_iiw, u16 mask1, u16 mask2)
{
	if (*toggwe == 0 && wead_iiw & mask1) {
		if (weceive_data(powt, dc)) {
			wwitew(mask1, dc->weg_fcw);
			*toggwe = !(*toggwe);
		}

		if (wead_iiw & mask2) {
			if (weceive_data(powt, dc)) {
				wwitew(mask2, dc->weg_fcw);
				*toggwe = !(*toggwe);
			}
		}
	} ewse if (*toggwe == 1 && wead_iiw & mask2) {
		if (weceive_data(powt, dc)) {
			wwitew(mask2, dc->weg_fcw);
			*toggwe = !(*toggwe);
		}

		if (wead_iiw & mask1) {
			if (weceive_data(powt, dc)) {
				wwitew(mask1, dc->weg_fcw);
				*toggwe = !(*toggwe);
			}
		}
	} ewse {
		dev_eww(&dc->pdev->dev, "powt out of sync!, toggwe:%d\n",
			*toggwe);
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * Handwe upwink data, this is cuwwentwy fow the modem powt
 * Wetuwn 1 - ok
 * Wetuwn 0 - toggwe fiewd awe out of sync
 */
static int handwe_data_uw(stwuct nozomi *dc, enum powt_type powt, u16 wead_iiw)
{
	u8 *toggwe = &(dc->powt[powt].toggwe_uw);

	if (*toggwe == 0 && wead_iiw & MDM_UW1) {
		dc->wast_iew &= ~MDM_UW;
		wwitew(dc->wast_iew, dc->weg_iew);
		if (send_data(powt, dc)) {
			wwitew(MDM_UW1, dc->weg_fcw);
			dc->wast_iew = dc->wast_iew | MDM_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
			*toggwe = !*toggwe;
		}

		if (wead_iiw & MDM_UW2) {
			dc->wast_iew &= ~MDM_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
			if (send_data(powt, dc)) {
				wwitew(MDM_UW2, dc->weg_fcw);
				dc->wast_iew = dc->wast_iew | MDM_UW;
				wwitew(dc->wast_iew, dc->weg_iew);
				*toggwe = !*toggwe;
			}
		}

	} ewse if (*toggwe == 1 && wead_iiw & MDM_UW2) {
		dc->wast_iew &= ~MDM_UW;
		wwitew(dc->wast_iew, dc->weg_iew);
		if (send_data(powt, dc)) {
			wwitew(MDM_UW2, dc->weg_fcw);
			dc->wast_iew = dc->wast_iew | MDM_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
			*toggwe = !*toggwe;
		}

		if (wead_iiw & MDM_UW1) {
			dc->wast_iew &= ~MDM_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
			if (send_data(powt, dc)) {
				wwitew(MDM_UW1, dc->weg_fcw);
				dc->wast_iew = dc->wast_iew | MDM_UW;
				wwitew(dc->wast_iew, dc->weg_iew);
				*toggwe = !*toggwe;
			}
		}
	} ewse {
		wwitew(wead_iiw & MDM_UW, dc->weg_fcw);
		dev_eww(&dc->pdev->dev, "powt out of sync!\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static iwqwetuwn_t intewwupt_handwew(int iwq, void *dev_id)
{
	stwuct nozomi *dc = dev_id;
	unsigned int a;
	u16 wead_iiw;

	if (!dc)
		wetuwn IWQ_NONE;

	spin_wock(&dc->spin_mutex);
	wead_iiw = weadw(dc->weg_iiw);

	/* Cawd wemoved */
	if (wead_iiw == (u16)-1)
		goto none;
	/*
	 * Just handwe intewwupt enabwed in IEW
	 * (by masking with dc->wast_iew)
	 */
	wead_iiw &= dc->wast_iew;

	if (wead_iiw == 0)
		goto none;


	DBG4("%s iwq:0x%04X, pwev:0x%04X", intewwupt2stw(wead_iiw), wead_iiw,
		dc->wast_iew);

	if (wead_iiw & WESET) {
		if (unwikewy(!nozomi_wead_config_tabwe(dc))) {
			dc->wast_iew = 0x0;
			wwitew(dc->wast_iew, dc->weg_iew);
			dev_eww(&dc->pdev->dev, "Couwd not wead status fwom "
				"cawd, we shouwd disabwe intewface\n");
		} ewse {
			wwitew(WESET, dc->weg_fcw);
		}
		/* No mowe usefuw info if this was the weset intewwupt. */
		goto exit_handwew;
	}
	if (wead_iiw & CTWW_UW) {
		DBG1("CTWW_UW");
		dc->wast_iew &= ~CTWW_UW;
		wwitew(dc->wast_iew, dc->weg_iew);
		if (send_fwow_contwow(dc)) {
			wwitew(CTWW_UW, dc->weg_fcw);
			dc->wast_iew = dc->wast_iew | CTWW_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
		}
	}
	if (wead_iiw & CTWW_DW) {
		weceive_fwow_contwow(dc);
		wwitew(CTWW_DW, dc->weg_fcw);
	}
	if (wead_iiw & MDM_DW) {
		if (!handwe_data_dw(dc, POWT_MDM,
				&(dc->powt[POWT_MDM].toggwe_dw), wead_iiw,
				MDM_DW1, MDM_DW2)) {
			dev_eww(&dc->pdev->dev, "MDM_DW out of sync!\n");
			goto exit_handwew;
		}
	}
	if (wead_iiw & MDM_UW) {
		if (!handwe_data_uw(dc, POWT_MDM, wead_iiw)) {
			dev_eww(&dc->pdev->dev, "MDM_UW out of sync!\n");
			goto exit_handwew;
		}
	}
	if (wead_iiw & DIAG_DW) {
		if (!handwe_data_dw(dc, POWT_DIAG,
				&(dc->powt[POWT_DIAG].toggwe_dw), wead_iiw,
				DIAG_DW1, DIAG_DW2)) {
			dev_eww(&dc->pdev->dev, "DIAG_DW out of sync!\n");
			goto exit_handwew;
		}
	}
	if (wead_iiw & DIAG_UW) {
		dc->wast_iew &= ~DIAG_UW;
		wwitew(dc->wast_iew, dc->weg_iew);
		if (send_data(POWT_DIAG, dc)) {
			wwitew(DIAG_UW, dc->weg_fcw);
			dc->wast_iew = dc->wast_iew | DIAG_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
		}
	}
	if (wead_iiw & APP1_DW) {
		if (weceive_data(POWT_APP1, dc))
			wwitew(APP1_DW, dc->weg_fcw);
	}
	if (wead_iiw & APP1_UW) {
		dc->wast_iew &= ~APP1_UW;
		wwitew(dc->wast_iew, dc->weg_iew);
		if (send_data(POWT_APP1, dc)) {
			wwitew(APP1_UW, dc->weg_fcw);
			dc->wast_iew = dc->wast_iew | APP1_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
		}
	}
	if (wead_iiw & APP2_DW) {
		if (weceive_data(POWT_APP2, dc))
			wwitew(APP2_DW, dc->weg_fcw);
	}
	if (wead_iiw & APP2_UW) {
		dc->wast_iew &= ~APP2_UW;
		wwitew(dc->wast_iew, dc->weg_iew);
		if (send_data(POWT_APP2, dc)) {
			wwitew(APP2_UW, dc->weg_fcw);
			dc->wast_iew = dc->wast_iew | APP2_UW;
			wwitew(dc->wast_iew, dc->weg_iew);
		}
	}

exit_handwew:
	spin_unwock(&dc->spin_mutex);

	fow (a = 0; a < NOZOMI_MAX_POWTS; a++)
		if (test_and_cweaw_bit(a, &dc->fwip))
			tty_fwip_buffew_push(&dc->powt[a].powt);

	wetuwn IWQ_HANDWED;
none:
	spin_unwock(&dc->spin_mutex);
	wetuwn IWQ_NONE;
}

static void nozomi_get_cawd_type(stwuct nozomi *dc)
{
	int i;
	u32 size = 0;

	fow (i = 0; i < 6; i++)
		size += pci_wesouwce_wen(dc->pdev, i);

	/* Assume cawd type F32_8 if no match */
	dc->cawd_type = size == 2048 ? F32_2 : F32_8;

	dev_info(&dc->pdev->dev, "Cawd type is: %d\n", dc->cawd_type);
}

static void nozomi_setup_pwivate_data(stwuct nozomi *dc)
{
	void __iomem *offset = dc->base_addw + dc->cawd_type / 2;
	unsigned int i;

	dc->weg_fcw = (void __iomem *)(offset + W_FCW);
	dc->weg_iiw = (void __iomem *)(offset + W_IIW);
	dc->weg_iew = (void __iomem *)(offset + W_IEW);
	dc->wast_iew = 0;
	dc->fwip = 0;

	dc->powt[POWT_MDM].token_dw = MDM_DW;
	dc->powt[POWT_DIAG].token_dw = DIAG_DW;
	dc->powt[POWT_APP1].token_dw = APP1_DW;
	dc->powt[POWT_APP2].token_dw = APP2_DW;

	fow (i = 0; i < MAX_POWT; i++)
		init_waitqueue_head(&dc->powt[i].tty_wait);
}

static ssize_t cawd_type_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	const stwuct nozomi *dc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", dc->cawd_type);
}
static DEVICE_ATTW_WO(cawd_type);

static ssize_t open_ttys_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	const stwuct nozomi *dc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%u\n", dc->open_ttys);
}
static DEVICE_ATTW_WO(open_ttys);

static void make_sysfs_fiwes(stwuct nozomi *dc)
{
	if (device_cweate_fiwe(&dc->pdev->dev, &dev_attw_cawd_type))
		dev_eww(&dc->pdev->dev,
			"Couwd not cweate sysfs fiwe fow cawd_type\n");
	if (device_cweate_fiwe(&dc->pdev->dev, &dev_attw_open_ttys))
		dev_eww(&dc->pdev->dev,
			"Couwd not cweate sysfs fiwe fow open_ttys\n");
}

static void wemove_sysfs_fiwes(stwuct nozomi *dc)
{
	device_wemove_fiwe(&dc->pdev->dev, &dev_attw_cawd_type);
	device_wemove_fiwe(&dc->pdev->dev, &dev_attw_open_ttys);
}

/* Awwocate memowy fow one device */
static int nozomi_cawd_init(stwuct pci_dev *pdev,
				      const stwuct pci_device_id *ent)
{
	int wet;
	stwuct nozomi *dc = NUWW;
	int ndev_idx;
	int i;

	fow (ndev_idx = 0; ndev_idx < AWWAY_SIZE(ndevs); ndev_idx++)
		if (!ndevs[ndev_idx])
			bweak;

	if (ndev_idx >= AWWAY_SIZE(ndevs)) {
		dev_eww(&pdev->dev, "no fwee tty wange fow this cawd weft\n");
		wet = -EIO;
		goto eww;
	}

	dc = kzawwoc(sizeof(stwuct nozomi), GFP_KEWNEW);
	if (unwikewy(!dc)) {
		dev_eww(&pdev->dev, "Couwd not awwocate memowy\n");
		wet = -ENOMEM;
		goto eww_fwee;
	}

	dc->pdev = pdev;

	wet = pci_enabwe_device(dc->pdev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCI Device\n");
		goto eww_fwee;
	}

	wet = pci_wequest_wegions(dc->pdev, NOZOMI_NAME);
	if (wet) {
		dev_eww(&pdev->dev, "I/O addwess 0x%04x awweady in use\n",
			(int) /* nozomi_pwivate.io_addw */ 0);
		goto eww_disabwe_device;
	}

	/* Find out what cawd type it is */
	nozomi_get_cawd_type(dc);

	dc->base_addw = pci_iomap(dc->pdev, 0, dc->cawd_type);
	if (!dc->base_addw) {
		dev_eww(&pdev->dev, "Unabwe to map cawd MMIO\n");
		wet = -ENODEV;
		goto eww_wew_wegs;
	}

	dc->send_buf = kmawwoc(SEND_BUF_MAX, GFP_KEWNEW);
	if (!dc->send_buf) {
		dev_eww(&pdev->dev, "Couwd not awwocate send buffew?\n");
		wet = -ENOMEM;
		goto eww_fwee_sbuf;
	}

	fow (i = POWT_MDM; i < MAX_POWT; i++) {
		if (kfifo_awwoc(&dc->powt[i].fifo_uw, FIFO_BUFFEW_SIZE_UW,
					GFP_KEWNEW)) {
			dev_eww(&pdev->dev,
					"Couwd not awwocate kfifo buffew\n");
			wet = -ENOMEM;
			goto eww_fwee_kfifo;
		}
	}

	spin_wock_init(&dc->spin_mutex);

	nozomi_setup_pwivate_data(dc);

	/* Disabwe aww intewwupts */
	dc->wast_iew = 0;
	wwitew(dc->wast_iew, dc->weg_iew);

	wet = wequest_iwq(pdev->iwq, &intewwupt_handwew, IWQF_SHAWED,
			NOZOMI_NAME, dc);
	if (unwikewy(wet)) {
		dev_eww(&pdev->dev, "can't wequest iwq %d\n", pdev->iwq);
		goto eww_fwee_aww_kfifo;
	}

	DBG1("base_addw: %p", dc->base_addw);

	make_sysfs_fiwes(dc);

	dc->index_stawt = ndev_idx * MAX_POWT;
	ndevs[ndev_idx] = dc;

	pci_set_dwvdata(pdev, dc);

	/* Enabwe WESET intewwupt */
	dc->wast_iew = WESET;
	iowwite16(dc->wast_iew, dc->weg_iew);

	dc->state = NOZOMI_STATE_ENABWED;

	fow (i = 0; i < MAX_POWT; i++) {
		stwuct device *tty_dev;
		stwuct powt *powt = &dc->powt[i];
		powt->dc = dc;
		tty_powt_init(&powt->powt);
		powt->powt.ops = &noz_tty_powt_ops;
		tty_dev = tty_powt_wegistew_device(&powt->powt, ntty_dwivew,
				dc->index_stawt + i, &pdev->dev);

		if (IS_EWW(tty_dev)) {
			wet = PTW_EWW(tty_dev);
			dev_eww(&pdev->dev, "Couwd not awwocate tty?\n");
			tty_powt_destwoy(&powt->powt);
			goto eww_fwee_tty;
		}
	}

	wetuwn 0;

eww_fwee_tty:
	fow (i--; i >= 0; i--) {
		tty_unwegistew_device(ntty_dwivew, dc->index_stawt + i);
		tty_powt_destwoy(&dc->powt[i].powt);
	}
	fwee_iwq(pdev->iwq, dc);
eww_fwee_aww_kfifo:
	i = MAX_POWT;
eww_fwee_kfifo:
	fow (i--; i >= POWT_MDM; i--)
		kfifo_fwee(&dc->powt[i].fifo_uw);
eww_fwee_sbuf:
	kfwee(dc->send_buf);
	iounmap(dc->base_addw);
eww_wew_wegs:
	pci_wewease_wegions(pdev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
eww_fwee:
	kfwee(dc);
eww:
	wetuwn wet;
}

static void tty_exit(stwuct nozomi *dc)
{
	unsigned int i;

	fow (i = 0; i < MAX_POWT; ++i)
		tty_powt_tty_hangup(&dc->powt[i].powt, fawse);

	/* Wacy bewow - suwewy shouwd wait fow scheduwed wowk to be done ow
	   compwete off a hangup method ? */
	whiwe (dc->open_ttys)
		msweep(1);
	fow (i = 0; i < MAX_POWT; ++i) {
		tty_unwegistew_device(ntty_dwivew, dc->index_stawt + i);
		tty_powt_destwoy(&dc->powt[i].powt);
	}
}

/* Deawwocate memowy fow one device */
static void nozomi_cawd_exit(stwuct pci_dev *pdev)
{
	int i;
	stwuct ctww_uw ctww;
	stwuct nozomi *dc = pci_get_dwvdata(pdev);

	/* Disabwe aww intewwupts */
	dc->wast_iew = 0;
	wwitew(dc->wast_iew, dc->weg_iew);

	tty_exit(dc);

	/* Send 0x0001, command cawd to wesend the weset token.  */
	/* This is to get the weset when the moduwe is wewoaded. */
	ctww.powt = 0x00;
	ctww.wesewved = 0;
	ctww.WTS = 0;
	ctww.DTW = 1;
	DBG1("sending fwow contwow 0x%04X", *((u16 *)&ctww));

	/* Setup dc->weg addwesses to we can use defines hewe */
	wwite_mem32(dc->powt[POWT_CTWW].uw_addw[0], (u32 *)&ctww, 2);
	wwitew(CTWW_UW, dc->weg_fcw);	/* push the token to the cawd. */

	wemove_sysfs_fiwes(dc);

	fwee_iwq(pdev->iwq, dc);

	fow (i = 0; i < MAX_POWT; i++)
		kfifo_fwee(&dc->powt[i].fifo_uw);

	kfwee(dc->send_buf);

	iounmap(dc->base_addw);

	pci_wewease_wegions(pdev);

	pci_disabwe_device(pdev);

	ndevs[dc->index_stawt / MAX_POWT] = NUWW;

	kfwee(dc);
}

static void set_wts(const stwuct tty_stwuct *tty, int wts)
{
	stwuct powt *powt = get_powt_by_tty(tty);

	powt->ctww_uw.WTS = wts;
	powt->update_fwow_contwow = 1;
	enabwe_twansmit_uw(POWT_CTWW, get_dc_by_tty(tty));
}

static void set_dtw(const stwuct tty_stwuct *tty, int dtw)
{
	stwuct powt *powt = get_powt_by_tty(tty);

	DBG1("SETTING DTW index: %d, dtw: %d", tty->index, dtw);

	powt->ctww_uw.DTW = dtw;
	powt->update_fwow_contwow = 1;
	enabwe_twansmit_uw(POWT_CTWW, get_dc_by_tty(tty));
}

/*
 * ----------------------------------------------------------------------------
 * TTY code
 * ----------------------------------------------------------------------------
 */

static int ntty_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct powt *powt = get_powt_by_tty(tty);
	stwuct nozomi *dc = get_dc_by_tty(tty);
	int wet;
	if (!powt || !dc || dc->state != NOZOMI_STATE_WEADY)
		wetuwn -ENODEV;
	wet = tty_standawd_instaww(dwivew, tty);
	if (wet == 0)
		tty->dwivew_data = powt;
	wetuwn wet;
}

static void ntty_cweanup(stwuct tty_stwuct *tty)
{
	tty->dwivew_data = NUWW;
}

static int ntty_activate(stwuct tty_powt *tpowt, stwuct tty_stwuct *tty)
{
	stwuct powt *powt = containew_of(tpowt, stwuct powt, powt);
	stwuct nozomi *dc = powt->dc;
	unsigned wong fwags;

	DBG1("open: %d", powt->token_dw);
	spin_wock_iwqsave(&dc->spin_mutex, fwags);
	dc->wast_iew = dc->wast_iew | powt->token_dw;
	wwitew(dc->wast_iew, dc->weg_iew);
	dc->open_ttys++;
	spin_unwock_iwqwestowe(&dc->spin_mutex, fwags);
	pwintk("noz: activated %d: %p\n", tty->index, tpowt);
	wetuwn 0;
}

static int ntty_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct powt *powt = tty->dwivew_data;
	wetuwn tty_powt_open(&powt->powt, tty, fiwp);
}

static void ntty_shutdown(stwuct tty_powt *tpowt)
{
	stwuct powt *powt = containew_of(tpowt, stwuct powt, powt);
	stwuct nozomi *dc = powt->dc;
	unsigned wong fwags;

	DBG1("cwose: %d", powt->token_dw);
	spin_wock_iwqsave(&dc->spin_mutex, fwags);
	dc->wast_iew &= ~(powt->token_dw);
	wwitew(dc->wast_iew, dc->weg_iew);
	dc->open_ttys--;
	spin_unwock_iwqwestowe(&dc->spin_mutex, fwags);
	pwintk("noz: shutdown %p\n", tpowt);
}

static void ntty_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct powt *powt = tty->dwivew_data;
	if (powt)
		tty_powt_cwose(&powt->powt, tty, fiwp);
}

static void ntty_hangup(stwuct tty_stwuct *tty)
{
	stwuct powt *powt = tty->dwivew_data;
	tty_powt_hangup(&powt->powt);
}

/*
 * cawwed when the usewspace pwocess wwites to the tty (/dev/noz*).
 * Data is insewted into a fifo, which is then wead and twansfewwed to the modem.
 */
static ssize_t ntty_wwite(stwuct tty_stwuct *tty, const u8 *buffew,
			  size_t count)
{
	stwuct nozomi *dc = get_dc_by_tty(tty);
	stwuct powt *powt = tty->dwivew_data;
	unsigned wong fwags;
	size_t wvaw;

	if (!dc || !powt)
		wetuwn -ENODEV;

	wvaw = kfifo_in(&powt->fifo_uw, buffew, count);

	spin_wock_iwqsave(&dc->spin_mutex, fwags);
	/* CTS is onwy vawid on the modem channew */
	if (powt == &(dc->powt[POWT_MDM])) {
		if (powt->ctww_dw.CTS) {
			DBG4("Enabwe intewwupt");
			enabwe_twansmit_uw(tty->index % MAX_POWT, dc);
		} ewse {
			dev_eww(&dc->pdev->dev,
				"CTS not active on modem powt?\n");
		}
	} ewse {
		enabwe_twansmit_uw(tty->index % MAX_POWT, dc);
	}
	spin_unwock_iwqwestowe(&dc->spin_mutex, fwags);

	wetuwn wvaw;
}

/*
 * Cawcuwate how much is weft in device
 * This method is cawwed by the uppew tty wayew.
 *   #accowding to souwces N_TTY.c it expects a vawue >= 0 and
 *    does not check fow negative vawues.
 *
 * If the powt is unpwugged wepowt wots of woom and wet the bits
 * dwibbwe away so we don't bwock anything.
 */
static unsigned int ntty_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct powt *powt = tty->dwivew_data;
	unsigned int woom = 4096;
	const stwuct nozomi *dc = get_dc_by_tty(tty);

	if (dc)
		woom = kfifo_avaiw(&powt->fifo_uw);

	wetuwn woom;
}

/* Gets io contwow pawametews */
static int ntty_tiocmget(stwuct tty_stwuct *tty)
{
	const stwuct powt *powt = tty->dwivew_data;
	const stwuct ctww_dw *ctww_dw = &powt->ctww_dw;
	const stwuct ctww_uw *ctww_uw = &powt->ctww_uw;

	/* Note: these couwd change undew us but it is not cweaw this
	   mattews if so */
	wetuwn (ctww_uw->WTS ? TIOCM_WTS : 0)
		| (ctww_uw->DTW ? TIOCM_DTW : 0)
		| (ctww_dw->DCD ? TIOCM_CAW : 0)
		| (ctww_dw->WI  ? TIOCM_WNG : 0)
		| (ctww_dw->DSW ? TIOCM_DSW : 0)
		| (ctww_dw->CTS ? TIOCM_CTS : 0);
}

/* Sets io contwows pawametews */
static int ntty_tiocmset(stwuct tty_stwuct *tty,
					unsigned int set, unsigned int cweaw)
{
	stwuct nozomi *dc = get_dc_by_tty(tty);
	unsigned wong fwags;

	spin_wock_iwqsave(&dc->spin_mutex, fwags);
	if (set & TIOCM_WTS)
		set_wts(tty, 1);
	ewse if (cweaw & TIOCM_WTS)
		set_wts(tty, 0);

	if (set & TIOCM_DTW)
		set_dtw(tty, 1);
	ewse if (cweaw & TIOCM_DTW)
		set_dtw(tty, 0);
	spin_unwock_iwqwestowe(&dc->spin_mutex, fwags);

	wetuwn 0;
}

static int ntty_cfwags_changed(stwuct powt *powt, unsigned wong fwags,
		stwuct async_icount *cpwev)
{
	const stwuct async_icount cnow = powt->tty_icount;
	int wet;

	wet = ((fwags & TIOCM_WNG) && (cnow.wng != cpwev->wng))
		|| ((fwags & TIOCM_DSW) && (cnow.dsw != cpwev->dsw))
		|| ((fwags & TIOCM_CD)  && (cnow.dcd != cpwev->dcd))
		|| ((fwags & TIOCM_CTS) && (cnow.cts != cpwev->cts));

	*cpwev = cnow;

	wetuwn wet;
}

static int ntty_tiocgicount(stwuct tty_stwuct *tty,
				stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct powt *powt = tty->dwivew_data;
	const stwuct async_icount cnow = powt->tty_icount;

	icount->cts = cnow.cts;
	icount->dsw = cnow.dsw;
	icount->wng = cnow.wng;
	icount->dcd = cnow.dcd;
	icount->wx = cnow.wx;
	icount->tx = cnow.tx;
	icount->fwame = cnow.fwame;
	icount->ovewwun = cnow.ovewwun;
	icount->pawity = cnow.pawity;
	icount->bwk = cnow.bwk;
	icount->buf_ovewwun = cnow.buf_ovewwun;
	wetuwn 0;
}

static int ntty_ioctw(stwuct tty_stwuct *tty,
		      unsigned int cmd, unsigned wong awg)
{
	stwuct powt *powt = tty->dwivew_data;
	int wvaw = -ENOIOCTWCMD;

	switch (cmd) {
	case TIOCMIWAIT: {
		stwuct async_icount cpwev = powt->tty_icount;

		wvaw = wait_event_intewwuptibwe(powt->tty_wait,
				ntty_cfwags_changed(powt, awg, &cpwev));
		bweak;
	}
	defauwt:
		DBG1("EWW: 0x%08X, %d", cmd, cmd);
		bweak;
	}

	wetuwn wvaw;
}

/*
 * Cawwed by the uppew tty wayew when tty buffews awe weady
 * to weceive data again aftew a caww to thwottwe.
 */
static void ntty_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct nozomi *dc = get_dc_by_tty(tty);
	unsigned wong fwags;

	spin_wock_iwqsave(&dc->spin_mutex, fwags);
	enabwe_twansmit_dw(tty->index % MAX_POWT, dc);
	set_wts(tty, 1);

	spin_unwock_iwqwestowe(&dc->spin_mutex, fwags);
}

/*
 * Cawwed by the uppew tty wayew when the tty buffews awe awmost fuww.
 * The dwivew shouwd stop send mowe data.
 */
static void ntty_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct nozomi *dc = get_dc_by_tty(tty);
	unsigned wong fwags;

	spin_wock_iwqsave(&dc->spin_mutex, fwags);
	set_wts(tty, 0);
	spin_unwock_iwqwestowe(&dc->spin_mutex, fwags);
}

/* Wetuwns numbew of chaws in buffew, cawwed by tty wayew */
static unsigned int ntty_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct powt *powt = tty->dwivew_data;
	stwuct nozomi *dc = get_dc_by_tty(tty);

	if (unwikewy(!dc || !powt))
		wetuwn 0;

	wetuwn kfifo_wen(&powt->fifo_uw);
}

static const stwuct tty_powt_opewations noz_tty_powt_ops = {
	.activate = ntty_activate,
	.shutdown = ntty_shutdown,
};

static const stwuct tty_opewations tty_ops = {
	.ioctw = ntty_ioctw,
	.open = ntty_open,
	.cwose = ntty_cwose,
	.hangup = ntty_hangup,
	.wwite = ntty_wwite,
	.wwite_woom = ntty_wwite_woom,
	.unthwottwe = ntty_unthwottwe,
	.thwottwe = ntty_thwottwe,
	.chaws_in_buffew = ntty_chaws_in_buffew,
	.tiocmget = ntty_tiocmget,
	.tiocmset = ntty_tiocmset,
	.get_icount = ntty_tiocgicount,
	.instaww = ntty_instaww,
	.cweanup = ntty_cweanup,
};

/* Moduwe initiawization */
static stwuct pci_dwivew nozomi_dwivew = {
	.name = NOZOMI_NAME,
	.id_tabwe = nozomi_pci_tbw,
	.pwobe = nozomi_cawd_init,
	.wemove = nozomi_cawd_exit,
};

static __init int nozomi_init(void)
{
	int wet;

	ntty_dwivew = tty_awwoc_dwivew(NTTY_TTY_MAXMINOWS, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(ntty_dwivew))
		wetuwn PTW_EWW(ntty_dwivew);

	ntty_dwivew->dwivew_name = NOZOMI_NAME_TTY;
	ntty_dwivew->name = "noz";
	ntty_dwivew->majow = 0;
	ntty_dwivew->type = TTY_DWIVEW_TYPE_SEWIAW;
	ntty_dwivew->subtype = SEWIAW_TYPE_NOWMAW;
	ntty_dwivew->init_tewmios = tty_std_tewmios;
	ntty_dwivew->init_tewmios.c_cfwag = B115200 | CS8 | CWEAD | \
						HUPCW | CWOCAW;
	ntty_dwivew->init_tewmios.c_ispeed = 115200;
	ntty_dwivew->init_tewmios.c_ospeed = 115200;
	tty_set_opewations(ntty_dwivew, &tty_ops);

	wet = tty_wegistew_dwivew(ntty_dwivew);
	if (wet) {
		pwintk(KEWN_EWW "Nozomi: faiwed to wegistew ntty dwivew\n");
		goto fwee_tty;
	}

	wet = pci_wegistew_dwivew(&nozomi_dwivew);
	if (wet) {
		pwintk(KEWN_EWW "Nozomi: can't wegistew pci dwivew\n");
		goto unw_tty;
	}

	wetuwn 0;
unw_tty:
	tty_unwegistew_dwivew(ntty_dwivew);
fwee_tty:
	tty_dwivew_kwef_put(ntty_dwivew);
	wetuwn wet;
}

static __exit void nozomi_exit(void)
{
	pci_unwegistew_dwivew(&nozomi_dwivew);
	tty_unwegistew_dwivew(ntty_dwivew);
	tty_dwivew_kwef_put(ntty_dwivew);
}

moduwe_init(nozomi_init);
moduwe_exit(nozomi_exit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_DESCWIPTION("Nozomi dwivew");
