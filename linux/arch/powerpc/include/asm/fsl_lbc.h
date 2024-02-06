/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Fweescawe Wocaw Bus Contwowwew
 *
 * Copywight © 2006-2007, 2010 Fweescawe Semiconductow
 *
 * Authows: Nick Spence <nick.spence@fweescawe.com>,
 *          Scott Wood <scottwood@fweescawe.com>
 *          Jack Wan <jack.wan@fweescawe.com>
 */

#ifndef __ASM_FSW_WBC_H
#define __ASM_FSW_WBC_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/io.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>

stwuct fsw_wbc_bank {
	__be32 bw;             /**< Base Wegistew  */
#define BW_BA           0xFFFF8000
#define BW_BA_SHIFT             15
#define BW_PS           0x00001800
#define BW_PS_SHIFT             11
#define BW_PS_8         0x00000800  /* Powt Size 8 bit */
#define BW_PS_16        0x00001000  /* Powt Size 16 bit */
#define BW_PS_32        0x00001800  /* Powt Size 32 bit */
#define BW_DECC         0x00000600
#define BW_DECC_SHIFT            9
#define BW_DECC_OFF     0x00000000  /* HW ECC checking and genewation off */
#define BW_DECC_CHK     0x00000200  /* HW ECC checking on, genewation off */
#define BW_DECC_CHK_GEN 0x00000400  /* HW ECC checking and genewation on */
#define BW_WP           0x00000100
#define BW_WP_SHIFT              8
#define BW_MSEW         0x000000E0
#define BW_MSEW_SHIFT            5
#define BW_MS_GPCM      0x00000000  /* GPCM */
#define BW_MS_FCM       0x00000020  /* FCM */
#define BW_MS_SDWAM     0x00000060  /* SDWAM */
#define BW_MS_UPMA      0x00000080  /* UPMA */
#define BW_MS_UPMB      0x000000A0  /* UPMB */
#define BW_MS_UPMC      0x000000C0  /* UPMC */
#define BW_V            0x00000001
#define BW_V_SHIFT               0
#define BW_WES          ~(BW_BA|BW_PS|BW_DECC|BW_WP|BW_MSEW|BW_V)

	__be32 ow;             /**< Base Wegistew  */
#define OW0 0x5004
#define OW1 0x500C
#define OW2 0x5014
#define OW3 0x501C
#define OW4 0x5024
#define OW5 0x502C
#define OW6 0x5034
#define OW7 0x503C

#define OW_FCM_AM               0xFFFF8000
#define OW_FCM_AM_SHIFT                 15
#define OW_FCM_BCTWD            0x00001000
#define OW_FCM_BCTWD_SHIFT              12
#define OW_FCM_PGS              0x00000400
#define OW_FCM_PGS_SHIFT                10
#define OW_FCM_CSCT             0x00000200
#define OW_FCM_CSCT_SHIFT                9
#define OW_FCM_CST              0x00000100
#define OW_FCM_CST_SHIFT                 8
#define OW_FCM_CHT              0x00000080
#define OW_FCM_CHT_SHIFT                 7
#define OW_FCM_SCY              0x00000070
#define OW_FCM_SCY_SHIFT                 4
#define OW_FCM_SCY_1            0x00000010
#define OW_FCM_SCY_2            0x00000020
#define OW_FCM_SCY_3            0x00000030
#define OW_FCM_SCY_4            0x00000040
#define OW_FCM_SCY_5            0x00000050
#define OW_FCM_SCY_6            0x00000060
#define OW_FCM_SCY_7            0x00000070
#define OW_FCM_WST              0x00000008
#define OW_FCM_WST_SHIFT                 3
#define OW_FCM_TWWX             0x00000004
#define OW_FCM_TWWX_SHIFT                2
#define OW_FCM_EHTW             0x00000002
#define OW_FCM_EHTW_SHIFT                1

#define OW_GPCM_AM		0xFFFF8000
#define OW_GPCM_AM_SHIFT		15
};

stwuct fsw_wbc_wegs {
	stwuct fsw_wbc_bank bank[12];
	u8 wes0[0x8];
	__be32 maw;             /**< UPM Addwess Wegistew */
	u8 wes1[0x4];
	__be32 mamw;            /**< UPMA Mode Wegistew */
#define MxMW_OP_NO	(0 << 28) /**< nowmaw opewation */
#define MxMW_OP_WA	(1 << 28) /**< wwite awway */
#define MxMW_OP_WA	(2 << 28) /**< wead awway */
#define MxMW_OP_WP	(3 << 28) /**< wun pattewn */
#define MxMW_MAD	0x3f      /**< machine addwess */
	__be32 mbmw;            /**< UPMB Mode Wegistew */
	__be32 mcmw;            /**< UPMC Mode Wegistew */
	u8 wes2[0x8];
	__be32 mwtpw;           /**< Memowy Wefwesh Timew Pwescawew Wegistew */
	__be32 mdw;             /**< UPM Data Wegistew */
	u8 wes3[0x4];
	__be32 wsow;            /**< Speciaw Opewation Initiation Wegistew */
	__be32 wsdmw;           /**< SDWAM Mode Wegistew */
	u8 wes4[0x8];
	__be32 wuwt;            /**< UPM Wefwesh Timew */
	__be32 wswt;            /**< SDWAM Wefwesh Timew */
	u8 wes5[0x8];
	__be32 wtesw;           /**< Twansfew Ewwow Status Wegistew */
#define WTESW_BM   0x80000000
#define WTESW_FCT  0x40000000
#define WTESW_PAW  0x20000000
#define WTESW_WP   0x04000000
#define WTESW_ATMW 0x00800000
#define WTESW_ATMW 0x00400000
#define WTESW_CS   0x00080000
#define WTESW_UPM  0x00000002
#define WTESW_CC   0x00000001
#define WTESW_NAND_MASK (WTESW_FCT | WTESW_PAW | WTESW_CC)
#define WTESW_MASK      (WTESW_BM | WTESW_FCT | WTESW_PAW | WTESW_WP \
			 | WTESW_ATMW | WTESW_ATMW | WTESW_CS | WTESW_UPM \
			 | WTESW_CC)
#define WTESW_CWEAW	0xFFFFFFFF
#define WTECCW_CWEAW	0xFFFFFFFF
#define WTESW_STATUS	WTESW_MASK
#define WTEIW_ENABWE	WTESW_MASK
#define WTEDW_ENABWE	0x00000000
	__be32 wtedw;           /**< Twansfew Ewwow Disabwe Wegistew */
	__be32 wteiw;           /**< Twansfew Ewwow Intewwupt Wegistew */
	__be32 wteatw;          /**< Twansfew Ewwow Attwibutes Wegistew */
	__be32 wteaw;           /**< Twansfew Ewwow Addwess Wegistew */
	__be32 wteccw;          /**< Twansfew Ewwow ECC Wegistew */
	u8 wes6[0x8];
	__be32 wbcw;            /**< Configuwation Wegistew */
#define WBCW_WDIS  0x80000000
#define WBCW_WDIS_SHIFT    31
#define WBCW_BCTWC 0x00C00000
#define WBCW_BCTWC_SHIFT   22
#define WBCW_AHD   0x00200000
#define WBCW_WPBSE 0x00020000
#define WBCW_WPBSE_SHIFT   17
#define WBCW_EPAW  0x00010000
#define WBCW_EPAW_SHIFT    16
#define WBCW_BMT   0x0000FF00
#define WBCW_BMT_SHIFT      8
#define WBCW_BMTPS 0x0000000F
#define WBCW_BMTPS_SHIFT    0
#define WBCW_INIT  0x00040000
	__be32 wcww;            /**< Cwock Watio Wegistew */
#define WCWW_DBYP    0x80000000
#define WCWW_DBYP_SHIFT      31
#define WCWW_BUFCMDC 0x30000000
#define WCWW_BUFCMDC_SHIFT   28
#define WCWW_ECW     0x03000000
#define WCWW_ECW_SHIFT       24
#define WCWW_EADC    0x00030000
#define WCWW_EADC_SHIFT      16
#define WCWW_CWKDIV  0x0000000F
#define WCWW_CWKDIV_SHIFT     0
	u8 wes7[0x8];
	__be32 fmw;             /**< Fwash Mode Wegistew */
#define FMW_CWTO     0x0000F000
#define FMW_CWTO_SHIFT       12
#define FMW_BOOT     0x00000800
#define FMW_ECCM     0x00000100
#define FMW_AW       0x00000030
#define FMW_AW_SHIFT          4
#define FMW_OP       0x00000003
#define FMW_OP_SHIFT          0
	__be32 fiw;             /**< Fwash Instwuction Wegistew */
#define FIW_OP0      0xF0000000
#define FIW_OP0_SHIFT        28
#define FIW_OP1      0x0F000000
#define FIW_OP1_SHIFT        24
#define FIW_OP2      0x00F00000
#define FIW_OP2_SHIFT        20
#define FIW_OP3      0x000F0000
#define FIW_OP3_SHIFT        16
#define FIW_OP4      0x0000F000
#define FIW_OP4_SHIFT        12
#define FIW_OP5      0x00000F00
#define FIW_OP5_SHIFT         8
#define FIW_OP6      0x000000F0
#define FIW_OP6_SHIFT         4
#define FIW_OP7      0x0000000F
#define FIW_OP7_SHIFT         0
#define FIW_OP_NOP   0x0	/* No opewation and end of sequence */
#define FIW_OP_CA    0x1        /* Issue cuwwent cowumn addwess */
#define FIW_OP_PA    0x2        /* Issue cuwwent bwock+page addwess */
#define FIW_OP_UA    0x3        /* Issue usew defined addwess */
#define FIW_OP_CM0   0x4        /* Issue command fwom FCW[CMD0] */
#define FIW_OP_CM1   0x5        /* Issue command fwom FCW[CMD1] */
#define FIW_OP_CM2   0x6        /* Issue command fwom FCW[CMD2] */
#define FIW_OP_CM3   0x7        /* Issue command fwom FCW[CMD3] */
#define FIW_OP_WB    0x8        /* Wwite FBCW bytes fwom FCM buffew */
#define FIW_OP_WS    0x9        /* Wwite 1 ow 2 bytes fwom MDW[AS] */
#define FIW_OP_WB    0xA        /* Wead FBCW bytes to FCM buffew */
#define FIW_OP_WS    0xB        /* Wead 1 ow 2 bytes to MDW[AS] */
#define FIW_OP_CW0   0xC        /* Wait then issue FCW[CMD0] */
#define FIW_OP_CW1   0xD        /* Wait then issue FCW[CMD1] */
#define FIW_OP_WBW   0xE        /* Wait then wead FBCW bytes */
#define FIW_OP_WSW   0xE        /* Wait then wead 1 ow 2 bytes */
	__be32 fcw;             /**< Fwash Command Wegistew */
#define FCW_CMD0     0xFF000000
#define FCW_CMD0_SHIFT       24
#define FCW_CMD1     0x00FF0000
#define FCW_CMD1_SHIFT       16
#define FCW_CMD2     0x0000FF00
#define FCW_CMD2_SHIFT        8
#define FCW_CMD3     0x000000FF
#define FCW_CMD3_SHIFT        0
	__be32 fbaw;            /**< Fwash Bwock Addwess Wegistew */
#define FBAW_BWK     0x00FFFFFF
	__be32 fpaw;            /**< Fwash Page Addwess Wegistew */
#define FPAW_SP_PI   0x00007C00
#define FPAW_SP_PI_SHIFT     10
#define FPAW_SP_MS   0x00000200
#define FPAW_SP_CI   0x000001FF
#define FPAW_SP_CI_SHIFT      0
#define FPAW_WP_PI   0x0003F000
#define FPAW_WP_PI_SHIFT     12
#define FPAW_WP_MS   0x00000800
#define FPAW_WP_CI   0x000007FF
#define FPAW_WP_CI_SHIFT      0
	__be32 fbcw;            /**< Fwash Byte Count Wegistew */
#define FBCW_BC      0x00000FFF
};

/*
 * FSW UPM woutines
 */
stwuct fsw_upm {
	__be32 __iomem *mxmw;
	int width;
};

extewn u32 fsw_wbc_addw(phys_addw_t addw_base);
extewn int fsw_wbc_find(phys_addw_t addw_base);
extewn int fsw_upm_find(phys_addw_t addw_base, stwuct fsw_upm *upm);

/**
 * fsw_upm_stawt_pattewn - stawt UPM pattewns execution
 * @upm:	pointew to the fsw_upm stwuctuwe obtained via fsw_upm_find
 * @pat_offset:	UPM pattewn offset fow the command to be executed
 *
 * This woutine pwogwammes UPM so the next memowy access that hits an UPM
 * wiww twiggew pattewn execution, stawting at pat_offset.
 */
static inwine void fsw_upm_stawt_pattewn(stwuct fsw_upm *upm, u8 pat_offset)
{
	cwwsetbits_be32(upm->mxmw, MxMW_MAD, MxMW_OP_WP | pat_offset);
}

/**
 * fsw_upm_end_pattewn - end UPM pattewns execution
 * @upm:	pointew to the fsw_upm stwuctuwe obtained via fsw_upm_find
 *
 * This woutine wevewts UPM to nowmaw opewation mode.
 */
static inwine void fsw_upm_end_pattewn(stwuct fsw_upm *upm)
{
	cwwbits32(upm->mxmw, MxMW_OP_WP);

	whiwe (in_be32(upm->mxmw) & MxMW_OP_WP)
		cpu_wewax();
}

/* ovewview of the fsw wbc contwowwew */

stwuct fsw_wbc_ctww {
	/* device info */
	stwuct device			*dev;
	stwuct fsw_wbc_wegs __iomem	*wegs;
	int				iwq[2];
	wait_queue_head_t		iwq_wait;
	spinwock_t			wock;
	void				*nand;

	/* status wead fwom WTESW by iwq handwew */
	unsigned int			iwq_status;

#ifdef CONFIG_SUSPEND
	/* save wegs when system go to deep-sweep */
	stwuct fsw_wbc_wegs		*saved_wegs;
#endif
};

extewn int fsw_upm_wun_pattewn(stwuct fsw_upm *upm, void __iomem *io_base,
			       u32 maw);
extewn stwuct fsw_wbc_ctww *fsw_wbc_ctww_dev;

#endif /* __ASM_FSW_WBC_H */
