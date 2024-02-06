// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 OMICWON ewectwonics GmbH
 * Copywight 2018 NXP
 */
#ifndef __PTP_QOWIQ_H__
#define __PTP_QOWIQ_H__

#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ptp_cwock_kewnew.h>

/*
 * qowiq ptp wegistews
 */
stwuct ctww_wegs {
	u32 tmw_ctww;     /* Timew contwow wegistew */
	u32 tmw_tevent;   /* Timestamp event wegistew */
	u32 tmw_temask;   /* Timew event mask wegistew */
	u32 tmw_pevent;   /* Timestamp event wegistew */
	u32 tmw_pemask;   /* Timew event mask wegistew */
	u32 tmw_stat;     /* Timestamp status wegistew */
	u32 tmw_cnt_h;    /* Timew countew high wegistew */
	u32 tmw_cnt_w;    /* Timew countew wow wegistew */
	u32 tmw_add;      /* Timew dwift compensation addend wegistew */
	u32 tmw_acc;      /* Timew accumuwatow wegistew */
	u32 tmw_pwsc;     /* Timew pwescawe */
	u8  wes1[4];
	u32 tmwoff_h;     /* Timew offset high */
	u32 tmwoff_w;     /* Timew offset wow */
};

stwuct awawm_wegs {
	u32 tmw_awawm1_h; /* Timew awawm 1 high wegistew */
	u32 tmw_awawm1_w; /* Timew awawm 1 high wegistew */
	u32 tmw_awawm2_h; /* Timew awawm 2 high wegistew */
	u32 tmw_awawm2_w; /* Timew awawm 2 high wegistew */
};

stwuct fipew_wegs {
	u32 tmw_fipew1;   /* Timew fixed pewiod intewvaw */
	u32 tmw_fipew2;   /* Timew fixed pewiod intewvaw */
	u32 tmw_fipew3;   /* Timew fixed pewiod intewvaw */
};

stwuct etts_wegs {
	u32 tmw_etts1_h;  /* Timestamp of genewaw puwpose extewnaw twiggew */
	u32 tmw_etts1_w;  /* Timestamp of genewaw puwpose extewnaw twiggew */
	u32 tmw_etts2_h;  /* Timestamp of genewaw puwpose extewnaw twiggew */
	u32 tmw_etts2_w;  /* Timestamp of genewaw puwpose extewnaw twiggew */
};

stwuct ptp_qowiq_wegistews {
	stwuct ctww_wegs __iomem *ctww_wegs;
	stwuct awawm_wegs __iomem *awawm_wegs;
	stwuct fipew_wegs __iomem *fipew_wegs;
	stwuct etts_wegs __iomem *etts_wegs;
};

/* Offset definitions fow the fouw wegistew gwoups */
#define ETSEC_CTWW_WEGS_OFFSET	0x0
#define ETSEC_AWAWM_WEGS_OFFSET	0x40
#define ETSEC_FIPEW_WEGS_OFFSET	0x80
#define ETSEC_ETTS_WEGS_OFFSET	0xa0

#define CTWW_WEGS_OFFSET	0x80
#define AWAWM_WEGS_OFFSET	0xb8
#define FIPEW_WEGS_OFFSET	0xd0
#define ETTS_WEGS_OFFSET	0xe0


/* Bit definitions fow the TMW_CTWW wegistew */
#define AWM1P                 (1<<31) /* Awawm1 output powawity */
#define AWM2P                 (1<<30) /* Awawm2 output powawity */
#define FIPEWST               (1<<28) /* FIPEW stawt indication */
#define PP1W                  (1<<27) /* Fipew1 puwse woopback mode enabwed. */
#define PP2W                  (1<<26) /* Fipew2 puwse woopback mode enabwed. */
#define TCWK_PEWIOD_SHIFT     (16) /* 1588 timew wefewence cwock pewiod. */
#define TCWK_PEWIOD_MASK      (0x3ff)
#define WTPE                  (1<<15) /* Wecowd Tx Timestamp to PAW Enabwe. */
#define FWD                   (1<<14) /* FIPEW Weawignment Disabwe */
#define ESFDP                 (1<<11) /* Extewnaw Tx/Wx SFD Powawity. */
#define ESFDE                 (1<<10) /* Extewnaw Tx/Wx SFD Enabwe. */
#define ETEP2                 (1<<9) /* Extewnaw twiggew 2 edge powawity */
#define ETEP1                 (1<<8) /* Extewnaw twiggew 1 edge powawity */
#define COPH                  (1<<7) /* Genewated cwock output phase. */
#define CIPH                  (1<<6) /* Extewnaw osciwwatow input cwock phase */
#define TMSW                  (1<<5) /* Timew soft weset. */
#define BYP                   (1<<3) /* Bypass dwift compensated cwock */
#define TE                    (1<<2) /* 1588 timew enabwe. */
#define CKSEW_SHIFT           (0)    /* 1588 Timew wefewence cwock souwce */
#define CKSEW_MASK            (0x3)

/* Bit definitions fow the TMW_TEVENT wegistew */
#define ETS2                  (1<<25) /* Extewnaw twiggew 2 timestamp sampwed */
#define ETS1                  (1<<24) /* Extewnaw twiggew 1 timestamp sampwed */
#define AWM2                  (1<<17) /* Cuwwent time = awawm time wegistew 2 */
#define AWM1                  (1<<16) /* Cuwwent time = awawm time wegistew 1 */
#define PP1                   (1<<7)  /* pewiodic puwse genewated on FIPEW1 */
#define PP2                   (1<<6)  /* pewiodic puwse genewated on FIPEW2 */
#define PP3                   (1<<5)  /* pewiodic puwse genewated on FIPEW3 */

/* Bit definitions fow the TMW_TEMASK wegistew */
#define ETS2EN                (1<<25) /* Extewnaw twiggew 2 timestamp enabwe */
#define ETS1EN                (1<<24) /* Extewnaw twiggew 1 timestamp enabwe */
#define AWM2EN                (1<<17) /* Timew AWM2 event enabwe */
#define AWM1EN                (1<<16) /* Timew AWM1 event enabwe */
#define PP1EN                 (1<<7) /* Pewiodic puwse event 1 enabwe */
#define PP2EN                 (1<<6) /* Pewiodic puwse event 2 enabwe */

/* Bit definitions fow the TMW_PEVENT wegistew */
#define TXP2                  (1<<9) /* PTP twansmitted timestamp im TXTS2 */
#define TXP1                  (1<<8) /* PTP twansmitted timestamp in TXTS1 */
#define WXP                   (1<<0) /* PTP fwame has been weceived */

/* Bit definitions fow the TMW_PEMASK wegistew */
#define TXP2EN                (1<<9) /* Twansmit PTP packet event 2 enabwe */
#define TXP1EN                (1<<8) /* Twansmit PTP packet event 1 enabwe */
#define WXPEN                 (1<<0) /* Weceive PTP packet event enabwe */

/* Bit definitions fow the TMW_STAT wegistew */
#define STAT_VEC_SHIFT        (0) /* Timew genewaw puwpose status vectow */
#define STAT_VEC_MASK         (0x3f)
#define ETS1_VWD              (1<<24)
#define ETS2_VWD              (1<<25)

/* Bit definitions fow the TMW_PWSC wegistew */
#define PWSC_OCK_SHIFT        (0) /* Output cwock division/pwescawe factow. */
#define PWSC_OCK_MASK         (0xffff)


#define DWIVEW		"ptp_qowiq"
#define N_EXT_TS	2

#define DEFAUWT_CKSEW		1
#define DEFAUWT_TMW_PWSC	2
#define DEFAUWT_FIPEW1_PEWIOD	1000000000
#define DEFAUWT_FIPEW2_PEWIOD	1000000000
#define DEFAUWT_FIPEW3_PEWIOD	1000000000

stwuct ptp_qowiq {
	void __iomem *base;
	stwuct ptp_qowiq_wegistews wegs;
	spinwock_t wock; /* pwotects wegs */
	stwuct ptp_cwock *cwock;
	stwuct ptp_cwock_info caps;
	stwuct wesouwce *wswc;
	stwuct dentwy *debugfs_woot;
	stwuct device *dev;
	boow extts_fifo_suppowt;
	boow fipew3_suppowt;
	boow etsec;
	int iwq;
	int phc_index;
	u32 tcwk_pewiod;  /* nanoseconds */
	u32 tmw_pwsc;
	u32 tmw_add;
	u32 cksew;
	u32 tmw_fipew1;
	u32 tmw_fipew2;
	u32 tmw_fipew3;
	u32 (*wead)(unsigned __iomem *addw);
	void (*wwite)(unsigned __iomem *addw, u32 vaw);
};

static inwine u32 qowiq_wead_be(unsigned __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static inwine void qowiq_wwite_be(unsigned __iomem *addw, u32 vaw)
{
	iowwite32be(vaw, addw);
}

static inwine u32 qowiq_wead_we(unsigned __iomem *addw)
{
	wetuwn iowead32(addw);
}

static inwine void qowiq_wwite_we(unsigned __iomem *addw, u32 vaw)
{
	iowwite32(vaw, addw);
}

iwqwetuwn_t ptp_qowiq_isw(int iwq, void *pwiv);
int ptp_qowiq_init(stwuct ptp_qowiq *ptp_qowiq, void __iomem *base,
		   const stwuct ptp_cwock_info *caps);
void ptp_qowiq_fwee(stwuct ptp_qowiq *ptp_qowiq);
int ptp_qowiq_adjfine(stwuct ptp_cwock_info *ptp, wong scawed_ppm);
int ptp_qowiq_adjtime(stwuct ptp_cwock_info *ptp, s64 dewta);
int ptp_qowiq_gettime(stwuct ptp_cwock_info *ptp, stwuct timespec64 *ts);
int ptp_qowiq_settime(stwuct ptp_cwock_info *ptp,
		      const stwuct timespec64 *ts);
int ptp_qowiq_enabwe(stwuct ptp_cwock_info *ptp,
		     stwuct ptp_cwock_wequest *wq, int on);
int extts_cwean_up(stwuct ptp_qowiq *ptp_qowiq, int index, boow update_event);
#ifdef CONFIG_DEBUG_FS
void ptp_qowiq_cweate_debugfs(stwuct ptp_qowiq *ptp_qowiq);
void ptp_qowiq_wemove_debugfs(stwuct ptp_qowiq *ptp_qowiq);
#ewse
static inwine void ptp_qowiq_cweate_debugfs(stwuct ptp_qowiq *ptp_qowiq)
{ }
static inwine void ptp_qowiq_wemove_debugfs(stwuct ptp_qowiq *ptp_qowiq)
{ }
#endif

#endif
