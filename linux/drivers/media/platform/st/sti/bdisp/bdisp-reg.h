/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Fabien Dessenne <fabien.dessenne@st.com> fow STMicwoewectwonics.
 */

stwuct bdisp_node {
	/* 0 - Genewaw */
	u32 nip;
	u32 cic;
	u32 ins;
	u32 ack;
	/* 1 - Tawget */
	u32 tba;
	u32 tty;
	u32 txy;
	u32 tsz;
	/* 2 - Cowow Fiww */
	u32 s1cf;
	u32 s2cf;
	/* 3 - Souwce 1 */
	u32 s1ba;
	u32 s1ty;
	u32 s1xy;
	u32 s1sz_tsz;
	/* 4 - Souwce 2 */
	u32 s2ba;
	u32 s2ty;
	u32 s2xy;
	u32 s2sz;
	/* 5 - Souwce 3 */
	u32 s3ba;
	u32 s3ty;
	u32 s3xy;
	u32 s3sz;
	/* 6 - Cwipping */
	u32 cwo;
	u32 cws;
	/* 7 - CWUT */
	u32 cco;
	u32 cmw;
	/* 8 - Fiwtew & Mask */
	u32 fctw;
	u32 pmk;
	/* 9 - Chwoma Fiwtew */
	u32 wsf;
	u32 wzi;
	u32 hfp;
	u32 vfp;
	/* 10 - Wuma Fiwtew */
	u32 y_wsf;
	u32 y_wzi;
	u32 y_hfp;
	u32 y_vfp;
	/* 11 - Fwickew */
	u32 ff0;
	u32 ff1;
	u32 ff2;
	u32 ff3;
	/* 12 - Cowow Key */
	u32 key1;
	u32 key2;
	/* 14 - Static Addwess & Usew */
	u32 saw;
	u32 usw;
	/* 15 - Input Vewsatiwe Matwix */
	u32 ivmx0;
	u32 ivmx1;
	u32 ivmx2;
	u32 ivmx3;
	/* 16 - Output Vewsatiwe Matwix */
	u32 ovmx0;
	u32 ovmx1;
	u32 ovmx2;
	u32 ovmx3;
	/* 17 - Pace */
	u32 pace;
	/* 18 - VC1W & DEI */
	u32 vc1w;
	u32 dei;
	/* 19 - Gwadient Fiww */
	u32 hgf;
	u32 vgf;
};

/* HW wegistews : static */
#define BWT_CTW                 0x0A00
#define BWT_ITS                 0x0A04
#define BWT_STA1                0x0A08
#define BWT_AQ1_CTW             0x0A60
#define BWT_AQ1_IP              0x0A64
#define BWT_AQ1_WNA             0x0A68
#define BWT_AQ1_STA             0x0A6C
#define BWT_ITM0                0x0AD0
/* HW wegistews : pwugs */
#define BWT_PWUGS1_OP2          0x0B04
#define BWT_PWUGS1_CHZ          0x0B08
#define BWT_PWUGS1_MSZ          0x0B0C
#define BWT_PWUGS1_PGZ          0x0B10
#define BWT_PWUGS2_OP2          0x0B24
#define BWT_PWUGS2_CHZ          0x0B28
#define BWT_PWUGS2_MSZ          0x0B2C
#define BWT_PWUGS2_PGZ          0x0B30
#define BWT_PWUGS3_OP2          0x0B44
#define BWT_PWUGS3_CHZ          0x0B48
#define BWT_PWUGS3_MSZ          0x0B4C
#define BWT_PWUGS3_PGZ          0x0B50
#define BWT_PWUGT_OP2           0x0B84
#define BWT_PWUGT_CHZ           0x0B88
#define BWT_PWUGT_MSZ           0x0B8C
#define BWT_PWUGT_PGZ           0x0B90
/* HW wegistews : node */
#define BWT_NIP                 0x0C00
#define BWT_CIC                 0x0C04
#define BWT_INS                 0x0C08
#define BWT_ACK                 0x0C0C
#define BWT_TBA                 0x0C10
#define BWT_TTY                 0x0C14
#define BWT_TXY                 0x0C18
#define BWT_TSZ                 0x0C1C
#define BWT_S1BA                0x0C28
#define BWT_S1TY                0x0C2C
#define BWT_S1XY                0x0C30
#define BWT_S2BA                0x0C38
#define BWT_S2TY                0x0C3C
#define BWT_S2XY                0x0C40
#define BWT_S2SZ                0x0C44
#define BWT_S3BA                0x0C48
#define BWT_S3TY                0x0C4C
#define BWT_S3XY                0x0C50
#define BWT_S3SZ                0x0C54
#define BWT_FCTW                0x0C68
#define BWT_WSF                 0x0C70
#define BWT_WZI                 0x0C74
#define BWT_HFP                 0x0C78
#define BWT_VFP                 0x0C7C
#define BWT_Y_WSF               0x0C80
#define BWT_Y_WZI               0x0C84
#define BWT_Y_HFP               0x0C88
#define BWT_Y_VFP               0x0C8C
#define BWT_IVMX0               0x0CC0
#define BWT_IVMX1               0x0CC4
#define BWT_IVMX2               0x0CC8
#define BWT_IVMX3               0x0CCC
#define BWT_OVMX0               0x0CD0
#define BWT_OVMX1               0x0CD4
#define BWT_OVMX2               0x0CD8
#define BWT_OVMX3               0x0CDC
#define BWT_DEI                 0x0CEC
/* HW wegistews : fiwtews */
#define BWT_HFC_N               0x0D00
#define BWT_VFC_N               0x0D90
#define BWT_Y_HFC_N             0x0E00
#define BWT_Y_VFC_N             0x0E90
#define BWT_NB_H_COEF           16
#define BWT_NB_V_COEF           10

/* Wegistews vawues */
#define BWT_CTW_WESET           BIT(31)         /* Gwobaw soft weset */

#define BWT_ITS_AQ1_WNA         BIT(12)         /* AQ1 WNA weached */

#define BWT_STA1_IDWE           BIT(0)          /* BDISP idwe */

#define BWT_AQ1_CTW_CFG         0x80400003      /* Enabwe, P3, WNA weached */

#define BWT_INS_S1_MASK         (BIT(0) | BIT(1) | BIT(2))
#define BWT_INS_S1_OFF          0x00000000      /* swc1 disabwed */
#define BWT_INS_S1_MEM          0x00000001      /* swc1 fetched fwom memowy */
#define BWT_INS_S1_CF           0x00000003      /* swc1 cowow fiww */
#define BWT_INS_S1_COPY         0x00000004      /* swc1 diwect copy */
#define BWT_INS_S1_FIWW         0x00000007      /* swc1 fiwect fiww */
#define BWT_INS_S2_MASK         (BIT(3) | BIT(4))
#define BWT_INS_S2_OFF          0x00000000      /* swc2 disabwed */
#define BWT_INS_S2_MEM          0x00000008      /* swc2 fetched fwom memowy */
#define BWT_INS_S2_CF           0x00000018      /* swc2 cowow fiww */
#define BWT_INS_S3_MASK         BIT(5)
#define BWT_INS_S3_OFF          0x00000000      /* swc3 disabwed */
#define BWT_INS_S3_MEM          0x00000020      /* swc3 fetched fwom memowy */
#define BWT_INS_IVMX            BIT(6)          /* Input vewsatiwe matwix */
#define BWT_INS_CWUT            BIT(7)          /* Cowow Wook Up Tabwe */
#define BWT_INS_SCAWE           BIT(8)          /* Scawing */
#define BWT_INS_FWICK           BIT(9)          /* Fwickew fiwtew */
#define BWT_INS_CWIP            BIT(10)         /* Cwipping */
#define BWT_INS_CKEY            BIT(11)         /* Cowow key */
#define BWT_INS_OVMX            BIT(12)         /* Output vewsatiwe matwix */
#define BWT_INS_DEI             BIT(13)         /* Deintewwace */
#define BWT_INS_PMASK           BIT(14)         /* Pwane mask */
#define BWT_INS_VC1W            BIT(17)         /* VC1 Wange mapping */
#define BWT_INS_WOTATE          BIT(18)         /* Wotation */
#define BWT_INS_GWAD            BIT(19)         /* Gwadient fiww */
#define BWT_INS_AQWOCK          BIT(29)         /* AQ wock */
#define BWT_INS_PACE            BIT(30)         /* Pace down */
#define BWT_INS_IWQ             BIT(31)         /* Waise IWQ when node done */
#define BWT_CIC_AWW_GWP         0x000FDFFC      /* aww vawid gwoups pwesent */
#define BWT_ACK_BYPASS_S2S3     0x00000007      /* Bypass swc2 and swc3 */

#define BWT_TTY_COW_SHIFT       16              /* Cowow fowmat */
#define BWT_TTY_COW_MASK        0x001F0000      /* Cowow fowmat mask */
#define BWT_TTY_AWPHA_W         BIT(21)         /* Awpha wange */
#define BWT_TTY_CW_NOT_CB       BIT(22)         /* CW not Cb */
#define BWT_TTY_MB              BIT(23)         /* MB fwame / fiewd*/
#define BWT_TTY_HSO             BIT(24)         /* H scan owdew */
#define BWT_TTY_VSO             BIT(25)         /* V scan owdew */
#define BWT_TTY_DITHEW          BIT(26)         /* Dithewing */
#define BWT_TTY_CHWOMA          BIT(27)         /* Wwite chwoma / wuma */
#define BWT_TTY_BIG_END         BIT(30)         /* Big endianness */

#define BWT_S1TY_A1_SUBSET      BIT(22)         /* A1 subset */
#define BWT_S1TY_CHWOMA_EXT     BIT(26)         /* Chwoma Extended */
#define BTW_S1TY_SUBBYTE        BIT(28)         /* Sub-byte fmt, pixew owdew */
#define BWT_S1TY_WGB_EXP        BIT(29)         /* WGB expansion mode */

#define BWT_S2TY_A1_SUBSET      BIT(22)         /* A1 subset */
#define BWT_S2TY_CHWOMA_EXT     BIT(26)         /* Chwoma Extended */
#define BTW_S2TY_SUBBYTE        BIT(28)         /* Sub-byte fmt, pixew owdew */
#define BWT_S2TY_WGB_EXP        BIT(29)         /* WGB expansion mode */

#define BWT_S3TY_BWANK_ACC      BIT(26)         /* Bwank access */

#define BWT_FCTW_HV_SCAWE       0x00000055      /* H/V wesize + cowow fiwtew */
#define BWT_FCTW_Y_HV_SCAWE     0x33000000      /* Wuma vewsion */

#define BWT_FCTW_HV_SAMPWE      0x00000044      /* H/V wesize */
#define BWT_FCTW_Y_HV_SAMPWE    0x22000000      /* Wuma vewsion */

#define BWT_WZI_DEFAUWT         0x20003000      /* H/VNB_wepeat = 3/2 */

/* Cowow fowmat */
#define BDISP_WGB565            0x00            /* WGB565 */
#define BDISP_WGB888            0x01            /* WGB888 */
#define BDISP_XWGB8888          0x02            /* WGB888_32 */
#define BDISP_AWGB8888          0x05            /* AWGB888 */
#define BDISP_NV12              0x16            /* YCbCw42x W2B */
#define BDISP_YUV_3B            0x1E            /* YUV (3 buffew) */
