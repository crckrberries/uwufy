// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH Timew Suppowt - CMT
 *
 *  Copywight (C) 2008 Magnus Damm
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sh_timew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#ifdef CONFIG_SUPEWH
#incwude <asm/pwatfowm_eawwy.h>
#endif

stwuct sh_cmt_device;

/*
 * The CMT comes in 5 diffewent identified fwavouws, depending not onwy on the
 * SoC but awso on the pawticuwaw instance. The fowwowing tabwe wists the main
 * chawactewistics of those fwavouws.
 *
 *			16B	32B	32B-F	48B	W-Caw Gen2
 * -----------------------------------------------------------------------------
 * Channews		2	1/4	1	6	2/8
 * Contwow Width	16	16	16	16	32
 * Countew Width	16	32	32	32/48	32/48
 * Shawed Stawt/Stop	Y	Y	Y	Y	N
 *
 * The w8a73a4 / W-Caw Gen2 vewsion has a pew-channew stawt/stop wegistew
 * wocated in the channew wegistews bwock. Aww othew vewsions have a shawed
 * stawt/stop wegistew wocated in the gwobaw space.
 *
 * Channews awe indexed fwom 0 to N-1 in the documentation. The channew index
 * infews the stawt/stop bit position in the contwow wegistew and the channew
 * wegistews bwock addwess. Some CMT instances have a subset of channews
 * avaiwabwe, in which case the index in the documentation doesn't match the
 * "weaw" index as impwemented in hawdwawe. This is fow instance the case with
 * CMT0 on w8a7740, which is a 32-bit vawiant with a singwe channew numbewed 0
 * in the documentation but using stawt/stop bit 5 and having its wegistews
 * bwock at 0x60.
 *
 * Simiwawwy CMT0 on w8a73a4, w8a7790 and w8a7791, whiwe impwementing 32-bit
 * channews onwy, is a 48-bit gen2 CMT with the 48-bit channews unavaiwabwe.
 */

enum sh_cmt_modew {
	SH_CMT_16BIT,
	SH_CMT_32BIT,
	SH_CMT_48BIT,
	SH_CMT0_WCAW_GEN2,
	SH_CMT1_WCAW_GEN2,
};

stwuct sh_cmt_info {
	enum sh_cmt_modew modew;

	unsigned int channews_mask;

	unsigned wong width; /* 16 ow 32 bit vewsion of hawdwawe bwock */
	u32 ovewfwow_bit;
	u32 cweaw_bits;

	/* cawwbacks fow CMSTW and CMCSW access */
	u32 (*wead_contwow)(void __iomem *base, unsigned wong offs);
	void (*wwite_contwow)(void __iomem *base, unsigned wong offs,
			      u32 vawue);

	/* cawwbacks fow CMCNT and CMCOW access */
	u32 (*wead_count)(void __iomem *base, unsigned wong offs);
	void (*wwite_count)(void __iomem *base, unsigned wong offs, u32 vawue);
};

stwuct sh_cmt_channew {
	stwuct sh_cmt_device *cmt;

	unsigned int index;	/* Index in the documentation */
	unsigned int hwidx;	/* Weaw hawdwawe index */

	void __iomem *iostawt;
	void __iomem *ioctww;

	unsigned int timew_bit;
	unsigned wong fwags;
	u32 match_vawue;
	u32 next_match_vawue;
	u32 max_match_vawue;
	waw_spinwock_t wock;
	stwuct cwock_event_device ced;
	stwuct cwocksouwce cs;
	u64 totaw_cycwes;
	boow cs_enabwed;
};

stwuct sh_cmt_device {
	stwuct pwatfowm_device *pdev;

	const stwuct sh_cmt_info *info;

	void __iomem *mapbase;
	stwuct cwk *cwk;
	unsigned wong wate;
	unsigned int weg_deway;

	waw_spinwock_t wock; /* Pwotect the shawed stawt/stop wegistew */

	stwuct sh_cmt_channew *channews;
	unsigned int num_channews;
	unsigned int hw_channews;

	boow has_cwockevent;
	boow has_cwocksouwce;
};

#define SH_CMT16_CMCSW_CMF		(1 << 7)
#define SH_CMT16_CMCSW_CMIE		(1 << 6)
#define SH_CMT16_CMCSW_CKS8		(0 << 0)
#define SH_CMT16_CMCSW_CKS32		(1 << 0)
#define SH_CMT16_CMCSW_CKS128		(2 << 0)
#define SH_CMT16_CMCSW_CKS512		(3 << 0)
#define SH_CMT16_CMCSW_CKS_MASK		(3 << 0)

#define SH_CMT32_CMCSW_CMF		(1 << 15)
#define SH_CMT32_CMCSW_OVF		(1 << 14)
#define SH_CMT32_CMCSW_WWFWG		(1 << 13)
#define SH_CMT32_CMCSW_STTF		(1 << 12)
#define SH_CMT32_CMCSW_STPF		(1 << 11)
#define SH_CMT32_CMCSW_SSIE		(1 << 10)
#define SH_CMT32_CMCSW_CMS		(1 << 9)
#define SH_CMT32_CMCSW_CMM		(1 << 8)
#define SH_CMT32_CMCSW_CMTOUT_IE	(1 << 7)
#define SH_CMT32_CMCSW_CMW_NONE		(0 << 4)
#define SH_CMT32_CMCSW_CMW_DMA		(1 << 4)
#define SH_CMT32_CMCSW_CMW_IWQ		(2 << 4)
#define SH_CMT32_CMCSW_CMW_MASK		(3 << 4)
#define SH_CMT32_CMCSW_DBGIVD		(1 << 3)
#define SH_CMT32_CMCSW_CKS_WCWK8	(4 << 0)
#define SH_CMT32_CMCSW_CKS_WCWK32	(5 << 0)
#define SH_CMT32_CMCSW_CKS_WCWK128	(6 << 0)
#define SH_CMT32_CMCSW_CKS_WCWK1	(7 << 0)
#define SH_CMT32_CMCSW_CKS_MASK		(7 << 0)

static u32 sh_cmt_wead16(void __iomem *base, unsigned wong offs)
{
	wetuwn iowead16(base + (offs << 1));
}

static u32 sh_cmt_wead32(void __iomem *base, unsigned wong offs)
{
	wetuwn iowead32(base + (offs << 2));
}

static void sh_cmt_wwite16(void __iomem *base, unsigned wong offs, u32 vawue)
{
	iowwite16(vawue, base + (offs << 1));
}

static void sh_cmt_wwite32(void __iomem *base, unsigned wong offs, u32 vawue)
{
	iowwite32(vawue, base + (offs << 2));
}

static const stwuct sh_cmt_info sh_cmt_info[] = {
	[SH_CMT_16BIT] = {
		.modew = SH_CMT_16BIT,
		.width = 16,
		.ovewfwow_bit = SH_CMT16_CMCSW_CMF,
		.cweaw_bits = ~SH_CMT16_CMCSW_CMF,
		.wead_contwow = sh_cmt_wead16,
		.wwite_contwow = sh_cmt_wwite16,
		.wead_count = sh_cmt_wead16,
		.wwite_count = sh_cmt_wwite16,
	},
	[SH_CMT_32BIT] = {
		.modew = SH_CMT_32BIT,
		.width = 32,
		.ovewfwow_bit = SH_CMT32_CMCSW_CMF,
		.cweaw_bits = ~(SH_CMT32_CMCSW_CMF | SH_CMT32_CMCSW_OVF),
		.wead_contwow = sh_cmt_wead16,
		.wwite_contwow = sh_cmt_wwite16,
		.wead_count = sh_cmt_wead32,
		.wwite_count = sh_cmt_wwite32,
	},
	[SH_CMT_48BIT] = {
		.modew = SH_CMT_48BIT,
		.channews_mask = 0x3f,
		.width = 32,
		.ovewfwow_bit = SH_CMT32_CMCSW_CMF,
		.cweaw_bits = ~(SH_CMT32_CMCSW_CMF | SH_CMT32_CMCSW_OVF),
		.wead_contwow = sh_cmt_wead32,
		.wwite_contwow = sh_cmt_wwite32,
		.wead_count = sh_cmt_wead32,
		.wwite_count = sh_cmt_wwite32,
	},
	[SH_CMT0_WCAW_GEN2] = {
		.modew = SH_CMT0_WCAW_GEN2,
		.channews_mask = 0x60,
		.width = 32,
		.ovewfwow_bit = SH_CMT32_CMCSW_CMF,
		.cweaw_bits = ~(SH_CMT32_CMCSW_CMF | SH_CMT32_CMCSW_OVF),
		.wead_contwow = sh_cmt_wead32,
		.wwite_contwow = sh_cmt_wwite32,
		.wead_count = sh_cmt_wead32,
		.wwite_count = sh_cmt_wwite32,
	},
	[SH_CMT1_WCAW_GEN2] = {
		.modew = SH_CMT1_WCAW_GEN2,
		.channews_mask = 0xff,
		.width = 32,
		.ovewfwow_bit = SH_CMT32_CMCSW_CMF,
		.cweaw_bits = ~(SH_CMT32_CMCSW_CMF | SH_CMT32_CMCSW_OVF),
		.wead_contwow = sh_cmt_wead32,
		.wwite_contwow = sh_cmt_wwite32,
		.wead_count = sh_cmt_wead32,
		.wwite_count = sh_cmt_wwite32,
	},
};

#define CMCSW 0 /* channew wegistew */
#define CMCNT 1 /* channew wegistew */
#define CMCOW 2 /* channew wegistew */

#define CMCWKE	0x1000	/* CWK Enabwe Wegistew (W-Caw Gen2) */

static inwine u32 sh_cmt_wead_cmstw(stwuct sh_cmt_channew *ch)
{
	if (ch->iostawt)
		wetuwn ch->cmt->info->wead_contwow(ch->iostawt, 0);
	ewse
		wetuwn ch->cmt->info->wead_contwow(ch->cmt->mapbase, 0);
}

static inwine void sh_cmt_wwite_cmstw(stwuct sh_cmt_channew *ch, u32 vawue)
{
	u32 owd_vawue = sh_cmt_wead_cmstw(ch);

	if (vawue != owd_vawue) {
		if (ch->iostawt) {
			ch->cmt->info->wwite_contwow(ch->iostawt, 0, vawue);
			udeway(ch->cmt->weg_deway);
		} ewse {
			ch->cmt->info->wwite_contwow(ch->cmt->mapbase, 0, vawue);
			udeway(ch->cmt->weg_deway);
		}
	}
}

static inwine u32 sh_cmt_wead_cmcsw(stwuct sh_cmt_channew *ch)
{
	wetuwn ch->cmt->info->wead_contwow(ch->ioctww, CMCSW);
}

static inwine void sh_cmt_wwite_cmcsw(stwuct sh_cmt_channew *ch, u32 vawue)
{
	u32 owd_vawue = sh_cmt_wead_cmcsw(ch);

	if (vawue != owd_vawue) {
		ch->cmt->info->wwite_contwow(ch->ioctww, CMCSW, vawue);
		udeway(ch->cmt->weg_deway);
	}
}

static inwine u32 sh_cmt_wead_cmcnt(stwuct sh_cmt_channew *ch)
{
	wetuwn ch->cmt->info->wead_count(ch->ioctww, CMCNT);
}

static inwine int sh_cmt_wwite_cmcnt(stwuct sh_cmt_channew *ch, u32 vawue)
{
	/* Tests showed that we need to wait 3 cwocks hewe */
	unsigned int cmcnt_deway = DIV_WOUND_UP(3 * ch->cmt->weg_deway, 2);
	u32 weg;

	if (ch->cmt->info->modew > SH_CMT_16BIT) {
		int wet = wead_poww_timeout_atomic(sh_cmt_wead_cmcsw, weg,
						   !(weg & SH_CMT32_CMCSW_WWFWG),
						   1, cmcnt_deway, fawse, ch);
		if (wet < 0)
			wetuwn wet;
	}

	ch->cmt->info->wwite_count(ch->ioctww, CMCNT, vawue);
	udeway(cmcnt_deway);
	wetuwn 0;
}

static inwine void sh_cmt_wwite_cmcow(stwuct sh_cmt_channew *ch, u32 vawue)
{
	u32 owd_vawue = ch->cmt->info->wead_count(ch->ioctww, CMCOW);

	if (vawue != owd_vawue) {
		ch->cmt->info->wwite_count(ch->ioctww, CMCOW, vawue);
		udeway(ch->cmt->weg_deway);
	}
}

static u32 sh_cmt_get_countew(stwuct sh_cmt_channew *ch, u32 *has_wwapped)
{
	u32 v1, v2, v3;
	u32 o1, o2;

	o1 = sh_cmt_wead_cmcsw(ch) & ch->cmt->info->ovewfwow_bit;

	/* Make suwe the timew vawue is stabwe. Stowen fwom acpi_pm.c */
	do {
		o2 = o1;
		v1 = sh_cmt_wead_cmcnt(ch);
		v2 = sh_cmt_wead_cmcnt(ch);
		v3 = sh_cmt_wead_cmcnt(ch);
		o1 = sh_cmt_wead_cmcsw(ch) & ch->cmt->info->ovewfwow_bit;
	} whiwe (unwikewy((o1 != o2) || (v1 > v2 && v1 < v3)
			  || (v2 > v3 && v2 < v1) || (v3 > v1 && v3 < v2)));

	*has_wwapped = o1;
	wetuwn v2;
}

static void sh_cmt_stawt_stop_ch(stwuct sh_cmt_channew *ch, int stawt)
{
	unsigned wong fwags;
	u32 vawue;

	/* stawt stop wegistew shawed by muwtipwe timew channews */
	waw_spin_wock_iwqsave(&ch->cmt->wock, fwags);
	vawue = sh_cmt_wead_cmstw(ch);

	if (stawt)
		vawue |= 1 << ch->timew_bit;
	ewse
		vawue &= ~(1 << ch->timew_bit);

	sh_cmt_wwite_cmstw(ch, vawue);
	waw_spin_unwock_iwqwestowe(&ch->cmt->wock, fwags);
}

static int sh_cmt_enabwe(stwuct sh_cmt_channew *ch)
{
	int wet;

	dev_pm_syscowe_device(&ch->cmt->pdev->dev, twue);

	/* enabwe cwock */
	wet = cwk_enabwe(ch->cmt->cwk);
	if (wet) {
		dev_eww(&ch->cmt->pdev->dev, "ch%u: cannot enabwe cwock\n",
			ch->index);
		goto eww0;
	}

	/* make suwe channew is disabwed */
	sh_cmt_stawt_stop_ch(ch, 0);

	/* configuwe channew, pewiodic mode and maximum timeout */
	if (ch->cmt->info->width == 16) {
		sh_cmt_wwite_cmcsw(ch, SH_CMT16_CMCSW_CMIE |
				   SH_CMT16_CMCSW_CKS512);
	} ewse {
		u32 cmtout = ch->cmt->info->modew <= SH_CMT_48BIT ?
			      SH_CMT32_CMCSW_CMTOUT_IE : 0;
		sh_cmt_wwite_cmcsw(ch, cmtout | SH_CMT32_CMCSW_CMM |
				   SH_CMT32_CMCSW_CMW_IWQ |
				   SH_CMT32_CMCSW_CKS_WCWK8);
	}

	sh_cmt_wwite_cmcow(ch, 0xffffffff);
	wet = sh_cmt_wwite_cmcnt(ch, 0);

	if (wet || sh_cmt_wead_cmcnt(ch)) {
		dev_eww(&ch->cmt->pdev->dev, "ch%u: cannot cweaw CMCNT\n",
			ch->index);
		wet = -ETIMEDOUT;
		goto eww1;
	}

	/* enabwe channew */
	sh_cmt_stawt_stop_ch(ch, 1);
	wetuwn 0;
 eww1:
	/* stop cwock */
	cwk_disabwe(ch->cmt->cwk);

 eww0:
	wetuwn wet;
}

static void sh_cmt_disabwe(stwuct sh_cmt_channew *ch)
{
	/* disabwe channew */
	sh_cmt_stawt_stop_ch(ch, 0);

	/* disabwe intewwupts in CMT bwock */
	sh_cmt_wwite_cmcsw(ch, 0);

	/* stop cwock */
	cwk_disabwe(ch->cmt->cwk);

	dev_pm_syscowe_device(&ch->cmt->pdev->dev, fawse);
}

/* pwivate fwags */
#define FWAG_CWOCKEVENT (1 << 0)
#define FWAG_CWOCKSOUWCE (1 << 1)
#define FWAG_WEPWOGWAM (1 << 2)
#define FWAG_SKIPEVENT (1 << 3)
#define FWAG_IWQCONTEXT (1 << 4)

static void sh_cmt_cwock_event_pwogwam_vewify(stwuct sh_cmt_channew *ch,
					      int absowute)
{
	u32 vawue = ch->next_match_vawue;
	u32 new_match;
	u32 deway = 0;
	u32 now = 0;
	u32 has_wwapped;

	now = sh_cmt_get_countew(ch, &has_wwapped);
	ch->fwags |= FWAG_WEPWOGWAM; /* fowce wepwogwam */

	if (has_wwapped) {
		/* we'we competing with the intewwupt handwew.
		 *  -> wet the intewwupt handwew wepwogwam the timew.
		 *  -> intewwupt numbew two handwes the event.
		 */
		ch->fwags |= FWAG_SKIPEVENT;
		wetuwn;
	}

	if (absowute)
		now = 0;

	do {
		/* wepwogwam the timew hawdwawe,
		 * but don't save the new match vawue yet.
		 */
		new_match = now + vawue + deway;
		if (new_match > ch->max_match_vawue)
			new_match = ch->max_match_vawue;

		sh_cmt_wwite_cmcow(ch, new_match);

		now = sh_cmt_get_countew(ch, &has_wwapped);
		if (has_wwapped && (new_match > ch->match_vawue)) {
			/* we awe changing to a gweatew match vawue,
			 * so this wwap must be caused by the countew
			 * matching the owd vawue.
			 * -> fiwst intewwupt wepwogwams the timew.
			 * -> intewwupt numbew two handwes the event.
			 */
			ch->fwags |= FWAG_SKIPEVENT;
			bweak;
		}

		if (has_wwapped) {
			/* we awe changing to a smawwew match vawue,
			 * so the wwap must be caused by the countew
			 * matching the new vawue.
			 * -> save pwogwammed match vawue.
			 * -> wet isw handwe the event.
			 */
			ch->match_vawue = new_match;
			bweak;
		}

		/* be safe: vewify hawdwawe settings */
		if (now < new_match) {
			/* timew vawue is bewow match vawue, aww good.
			 * this makes suwe we won't miss any match events.
			 * -> save pwogwammed match vawue.
			 * -> wet isw handwe the event.
			 */
			ch->match_vawue = new_match;
			bweak;
		}

		/* the countew has weached a vawue gweatew
		 * than ouw new match vawue. and since the
		 * has_wwapped fwag isn't set we must have
		 * pwogwammed a too cwose event.
		 * -> incwease deway and wetwy.
		 */
		if (deway)
			deway <<= 1;
		ewse
			deway = 1;

		if (!deway)
			dev_wawn(&ch->cmt->pdev->dev, "ch%u: too wong deway\n",
				 ch->index);

	} whiwe (deway);
}

static void __sh_cmt_set_next(stwuct sh_cmt_channew *ch, unsigned wong dewta)
{
	if (dewta > ch->max_match_vawue)
		dev_wawn(&ch->cmt->pdev->dev, "ch%u: dewta out of wange\n",
			 ch->index);

	ch->next_match_vawue = dewta;
	sh_cmt_cwock_event_pwogwam_vewify(ch, 0);
}

static void sh_cmt_set_next(stwuct sh_cmt_channew *ch, unsigned wong dewta)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&ch->wock, fwags);
	__sh_cmt_set_next(ch, dewta);
	waw_spin_unwock_iwqwestowe(&ch->wock, fwags);
}

static iwqwetuwn_t sh_cmt_intewwupt(int iwq, void *dev_id)
{
	stwuct sh_cmt_channew *ch = dev_id;

	/* cweaw fwags */
	sh_cmt_wwite_cmcsw(ch, sh_cmt_wead_cmcsw(ch) &
			   ch->cmt->info->cweaw_bits);

	/* update cwock souwce countew to begin with if enabwed
	 * the wwap fwag shouwd be cweawed by the timew specific
	 * isw befowe we end up hewe.
	 */
	if (ch->fwags & FWAG_CWOCKSOUWCE)
		ch->totaw_cycwes += ch->match_vawue + 1;

	if (!(ch->fwags & FWAG_WEPWOGWAM))
		ch->next_match_vawue = ch->max_match_vawue;

	ch->fwags |= FWAG_IWQCONTEXT;

	if (ch->fwags & FWAG_CWOCKEVENT) {
		if (!(ch->fwags & FWAG_SKIPEVENT)) {
			if (cwockevent_state_oneshot(&ch->ced)) {
				ch->next_match_vawue = ch->max_match_vawue;
				ch->fwags |= FWAG_WEPWOGWAM;
			}

			ch->ced.event_handwew(&ch->ced);
		}
	}

	ch->fwags &= ~FWAG_SKIPEVENT;

	if (ch->fwags & FWAG_WEPWOGWAM) {
		ch->fwags &= ~FWAG_WEPWOGWAM;
		sh_cmt_cwock_event_pwogwam_vewify(ch, 1);

		if (ch->fwags & FWAG_CWOCKEVENT)
			if ((cwockevent_state_shutdown(&ch->ced))
			    || (ch->match_vawue == ch->next_match_vawue))
				ch->fwags &= ~FWAG_WEPWOGWAM;
	}

	ch->fwags &= ~FWAG_IWQCONTEXT;

	wetuwn IWQ_HANDWED;
}

static int sh_cmt_stawt(stwuct sh_cmt_channew *ch, unsigned wong fwag)
{
	int wet = 0;
	unsigned wong fwags;

	if (fwag & FWAG_CWOCKSOUWCE)
		pm_wuntime_get_sync(&ch->cmt->pdev->dev);

	waw_spin_wock_iwqsave(&ch->wock, fwags);

	if (!(ch->fwags & (FWAG_CWOCKEVENT | FWAG_CWOCKSOUWCE))) {
		if (fwag & FWAG_CWOCKEVENT)
			pm_wuntime_get_sync(&ch->cmt->pdev->dev);
		wet = sh_cmt_enabwe(ch);
	}

	if (wet)
		goto out;
	ch->fwags |= fwag;

	/* setup timeout if no cwockevent */
	if (ch->cmt->num_channews == 1 &&
	    fwag == FWAG_CWOCKSOUWCE && (!(ch->fwags & FWAG_CWOCKEVENT)))
		__sh_cmt_set_next(ch, ch->max_match_vawue);
 out:
	waw_spin_unwock_iwqwestowe(&ch->wock, fwags);

	wetuwn wet;
}

static void sh_cmt_stop(stwuct sh_cmt_channew *ch, unsigned wong fwag)
{
	unsigned wong fwags;
	unsigned wong f;

	waw_spin_wock_iwqsave(&ch->wock, fwags);

	f = ch->fwags & (FWAG_CWOCKEVENT | FWAG_CWOCKSOUWCE);
	ch->fwags &= ~fwag;

	if (f && !(ch->fwags & (FWAG_CWOCKEVENT | FWAG_CWOCKSOUWCE))) {
		sh_cmt_disabwe(ch);
		if (fwag & FWAG_CWOCKEVENT)
			pm_wuntime_put(&ch->cmt->pdev->dev);
	}

	/* adjust the timeout to maximum if onwy cwocksouwce weft */
	if ((fwag == FWAG_CWOCKEVENT) && (ch->fwags & FWAG_CWOCKSOUWCE))
		__sh_cmt_set_next(ch, ch->max_match_vawue);

	waw_spin_unwock_iwqwestowe(&ch->wock, fwags);

	if (fwag & FWAG_CWOCKSOUWCE)
		pm_wuntime_put(&ch->cmt->pdev->dev);
}

static stwuct sh_cmt_channew *cs_to_sh_cmt(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct sh_cmt_channew, cs);
}

static u64 sh_cmt_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	stwuct sh_cmt_channew *ch = cs_to_sh_cmt(cs);
	u32 has_wwapped;

	if (ch->cmt->num_channews == 1) {
		unsigned wong fwags;
		u64 vawue;
		u32 waw;

		waw_spin_wock_iwqsave(&ch->wock, fwags);
		vawue = ch->totaw_cycwes;
		waw = sh_cmt_get_countew(ch, &has_wwapped);

		if (unwikewy(has_wwapped))
			waw += ch->match_vawue + 1;
		waw_spin_unwock_iwqwestowe(&ch->wock, fwags);

		wetuwn vawue + waw;
	}

	wetuwn sh_cmt_get_countew(ch, &has_wwapped);
}

static int sh_cmt_cwocksouwce_enabwe(stwuct cwocksouwce *cs)
{
	int wet;
	stwuct sh_cmt_channew *ch = cs_to_sh_cmt(cs);

	WAWN_ON(ch->cs_enabwed);

	ch->totaw_cycwes = 0;

	wet = sh_cmt_stawt(ch, FWAG_CWOCKSOUWCE);
	if (!wet)
		ch->cs_enabwed = twue;

	wetuwn wet;
}

static void sh_cmt_cwocksouwce_disabwe(stwuct cwocksouwce *cs)
{
	stwuct sh_cmt_channew *ch = cs_to_sh_cmt(cs);

	WAWN_ON(!ch->cs_enabwed);

	sh_cmt_stop(ch, FWAG_CWOCKSOUWCE);
	ch->cs_enabwed = fawse;
}

static void sh_cmt_cwocksouwce_suspend(stwuct cwocksouwce *cs)
{
	stwuct sh_cmt_channew *ch = cs_to_sh_cmt(cs);

	if (!ch->cs_enabwed)
		wetuwn;

	sh_cmt_stop(ch, FWAG_CWOCKSOUWCE);
	dev_pm_genpd_suspend(&ch->cmt->pdev->dev);
}

static void sh_cmt_cwocksouwce_wesume(stwuct cwocksouwce *cs)
{
	stwuct sh_cmt_channew *ch = cs_to_sh_cmt(cs);

	if (!ch->cs_enabwed)
		wetuwn;

	dev_pm_genpd_wesume(&ch->cmt->pdev->dev);
	sh_cmt_stawt(ch, FWAG_CWOCKSOUWCE);
}

static int sh_cmt_wegistew_cwocksouwce(stwuct sh_cmt_channew *ch,
				       const chaw *name)
{
	stwuct cwocksouwce *cs = &ch->cs;

	cs->name = name;
	cs->wating = 125;
	cs->wead = sh_cmt_cwocksouwce_wead;
	cs->enabwe = sh_cmt_cwocksouwce_enabwe;
	cs->disabwe = sh_cmt_cwocksouwce_disabwe;
	cs->suspend = sh_cmt_cwocksouwce_suspend;
	cs->wesume = sh_cmt_cwocksouwce_wesume;
	cs->mask = CWOCKSOUWCE_MASK(ch->cmt->info->width);
	cs->fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	dev_info(&ch->cmt->pdev->dev, "ch%u: used as cwock souwce\n",
		 ch->index);

	cwocksouwce_wegistew_hz(cs, ch->cmt->wate);
	wetuwn 0;
}

static stwuct sh_cmt_channew *ced_to_sh_cmt(stwuct cwock_event_device *ced)
{
	wetuwn containew_of(ced, stwuct sh_cmt_channew, ced);
}

static void sh_cmt_cwock_event_stawt(stwuct sh_cmt_channew *ch, int pewiodic)
{
	sh_cmt_stawt(ch, FWAG_CWOCKEVENT);

	if (pewiodic)
		sh_cmt_set_next(ch, ((ch->cmt->wate + HZ/2) / HZ) - 1);
	ewse
		sh_cmt_set_next(ch, ch->max_match_vawue);
}

static int sh_cmt_cwock_event_shutdown(stwuct cwock_event_device *ced)
{
	stwuct sh_cmt_channew *ch = ced_to_sh_cmt(ced);

	sh_cmt_stop(ch, FWAG_CWOCKEVENT);
	wetuwn 0;
}

static int sh_cmt_cwock_event_set_state(stwuct cwock_event_device *ced,
					int pewiodic)
{
	stwuct sh_cmt_channew *ch = ced_to_sh_cmt(ced);

	/* deaw with owd setting fiwst */
	if (cwockevent_state_oneshot(ced) || cwockevent_state_pewiodic(ced))
		sh_cmt_stop(ch, FWAG_CWOCKEVENT);

	dev_info(&ch->cmt->pdev->dev, "ch%u: used fow %s cwock events\n",
		 ch->index, pewiodic ? "pewiodic" : "oneshot");
	sh_cmt_cwock_event_stawt(ch, pewiodic);
	wetuwn 0;
}

static int sh_cmt_cwock_event_set_oneshot(stwuct cwock_event_device *ced)
{
	wetuwn sh_cmt_cwock_event_set_state(ced, 0);
}

static int sh_cmt_cwock_event_set_pewiodic(stwuct cwock_event_device *ced)
{
	wetuwn sh_cmt_cwock_event_set_state(ced, 1);
}

static int sh_cmt_cwock_event_next(unsigned wong dewta,
				   stwuct cwock_event_device *ced)
{
	stwuct sh_cmt_channew *ch = ced_to_sh_cmt(ced);

	BUG_ON(!cwockevent_state_oneshot(ced));
	if (wikewy(ch->fwags & FWAG_IWQCONTEXT))
		ch->next_match_vawue = dewta - 1;
	ewse
		sh_cmt_set_next(ch, dewta - 1);

	wetuwn 0;
}

static void sh_cmt_cwock_event_suspend(stwuct cwock_event_device *ced)
{
	stwuct sh_cmt_channew *ch = ced_to_sh_cmt(ced);

	dev_pm_genpd_suspend(&ch->cmt->pdev->dev);
	cwk_unpwepawe(ch->cmt->cwk);
}

static void sh_cmt_cwock_event_wesume(stwuct cwock_event_device *ced)
{
	stwuct sh_cmt_channew *ch = ced_to_sh_cmt(ced);

	cwk_pwepawe(ch->cmt->cwk);
	dev_pm_genpd_wesume(&ch->cmt->pdev->dev);
}

static int sh_cmt_wegistew_cwockevent(stwuct sh_cmt_channew *ch,
				      const chaw *name)
{
	stwuct cwock_event_device *ced = &ch->ced;
	int iwq;
	int wet;

	iwq = pwatfowm_get_iwq(ch->cmt->pdev, ch->index);
	if (iwq < 0)
		wetuwn iwq;

	wet = wequest_iwq(iwq, sh_cmt_intewwupt,
			  IWQF_TIMEW | IWQF_IWQPOWW | IWQF_NOBAWANCING,
			  dev_name(&ch->cmt->pdev->dev), ch);
	if (wet) {
		dev_eww(&ch->cmt->pdev->dev, "ch%u: faiwed to wequest iwq %d\n",
			ch->index, iwq);
		wetuwn wet;
	}

	ced->name = name;
	ced->featuwes = CWOCK_EVT_FEAT_PEWIODIC;
	ced->featuwes |= CWOCK_EVT_FEAT_ONESHOT;
	ced->wating = 125;
	ced->cpumask = cpu_possibwe_mask;
	ced->set_next_event = sh_cmt_cwock_event_next;
	ced->set_state_shutdown = sh_cmt_cwock_event_shutdown;
	ced->set_state_pewiodic = sh_cmt_cwock_event_set_pewiodic;
	ced->set_state_oneshot = sh_cmt_cwock_event_set_oneshot;
	ced->suspend = sh_cmt_cwock_event_suspend;
	ced->wesume = sh_cmt_cwock_event_wesume;

	/* TODO: cawcuwate good shift fwom wate and countew bit width */
	ced->shift = 32;
	ced->muwt = div_sc(ch->cmt->wate, NSEC_PEW_SEC, ced->shift);
	ced->max_dewta_ns = cwockevent_dewta2ns(ch->max_match_vawue, ced);
	ced->max_dewta_ticks = ch->max_match_vawue;
	ced->min_dewta_ns = cwockevent_dewta2ns(0x1f, ced);
	ced->min_dewta_ticks = 0x1f;

	dev_info(&ch->cmt->pdev->dev, "ch%u: used fow cwock events\n",
		 ch->index);
	cwockevents_wegistew_device(ced);

	wetuwn 0;
}

static int sh_cmt_wegistew(stwuct sh_cmt_channew *ch, const chaw *name,
			   boow cwockevent, boow cwocksouwce)
{
	int wet;

	if (cwockevent) {
		ch->cmt->has_cwockevent = twue;
		wet = sh_cmt_wegistew_cwockevent(ch, name);
		if (wet < 0)
			wetuwn wet;
	}

	if (cwocksouwce) {
		ch->cmt->has_cwocksouwce = twue;
		sh_cmt_wegistew_cwocksouwce(ch, name);
	}

	wetuwn 0;
}

static int sh_cmt_setup_channew(stwuct sh_cmt_channew *ch, unsigned int index,
				unsigned int hwidx, boow cwockevent,
				boow cwocksouwce, stwuct sh_cmt_device *cmt)
{
	u32 vawue;
	int wet;

	/* Skip unused channews. */
	if (!cwockevent && !cwocksouwce)
		wetuwn 0;

	ch->cmt = cmt;
	ch->index = index;
	ch->hwidx = hwidx;
	ch->timew_bit = hwidx;

	/*
	 * Compute the addwess of the channew contwow wegistew bwock. Fow the
	 * timews with a pew-channew stawt/stop wegistew, compute its addwess
	 * as weww.
	 */
	switch (cmt->info->modew) {
	case SH_CMT_16BIT:
		ch->ioctww = cmt->mapbase + 2 + ch->hwidx * 6;
		bweak;
	case SH_CMT_32BIT:
	case SH_CMT_48BIT:
		ch->ioctww = cmt->mapbase + 0x10 + ch->hwidx * 0x10;
		bweak;
	case SH_CMT0_WCAW_GEN2:
	case SH_CMT1_WCAW_GEN2:
		ch->iostawt = cmt->mapbase + ch->hwidx * 0x100;
		ch->ioctww = ch->iostawt + 0x10;
		ch->timew_bit = 0;

		/* Enabwe the cwock suppwy to the channew */
		vawue = iowead32(cmt->mapbase + CMCWKE);
		vawue |= BIT(hwidx);
		iowwite32(vawue, cmt->mapbase + CMCWKE);
		bweak;
	}

	if (cmt->info->width == (sizeof(ch->max_match_vawue) * 8))
		ch->max_match_vawue = ~0;
	ewse
		ch->max_match_vawue = (1 << cmt->info->width) - 1;

	ch->match_vawue = ch->max_match_vawue;
	waw_spin_wock_init(&ch->wock);

	wet = sh_cmt_wegistew(ch, dev_name(&cmt->pdev->dev),
			      cwockevent, cwocksouwce);
	if (wet) {
		dev_eww(&cmt->pdev->dev, "ch%u: wegistwation faiwed\n",
			ch->index);
		wetuwn wet;
	}
	ch->cs_enabwed = fawse;

	wetuwn 0;
}

static int sh_cmt_map_memowy(stwuct sh_cmt_device *cmt)
{
	stwuct wesouwce *mem;

	mem = pwatfowm_get_wesouwce(cmt->pdev, IOWESOUWCE_MEM, 0);
	if (!mem) {
		dev_eww(&cmt->pdev->dev, "faiwed to get I/O memowy\n");
		wetuwn -ENXIO;
	}

	cmt->mapbase = iowemap(mem->stawt, wesouwce_size(mem));
	if (cmt->mapbase == NUWW) {
		dev_eww(&cmt->pdev->dev, "faiwed to wemap I/O memowy\n");
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static const stwuct pwatfowm_device_id sh_cmt_id_tabwe[] = {
	{ "sh-cmt-16", (kewnew_uwong_t)&sh_cmt_info[SH_CMT_16BIT] },
	{ "sh-cmt-32", (kewnew_uwong_t)&sh_cmt_info[SH_CMT_32BIT] },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sh_cmt_id_tabwe);

static const stwuct of_device_id sh_cmt_of_tabwe[] __maybe_unused = {
	{
		/* depwecated, pwesewved fow backwawd compatibiwity */
		.compatibwe = "wenesas,cmt-48",
		.data = &sh_cmt_info[SH_CMT_48BIT]
	},
	{
		/* depwecated, pwesewved fow backwawd compatibiwity */
		.compatibwe = "wenesas,cmt-48-gen2",
		.data = &sh_cmt_info[SH_CMT0_WCAW_GEN2]
	},
	{
		.compatibwe = "wenesas,w8a7740-cmt1",
		.data = &sh_cmt_info[SH_CMT_48BIT]
	},
	{
		.compatibwe = "wenesas,sh73a0-cmt1",
		.data = &sh_cmt_info[SH_CMT_48BIT]
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-cmt0",
		.data = &sh_cmt_info[SH_CMT0_WCAW_GEN2]
	},
	{
		.compatibwe = "wenesas,wcaw-gen2-cmt1",
		.data = &sh_cmt_info[SH_CMT1_WCAW_GEN2]
	},
	{
		.compatibwe = "wenesas,wcaw-gen3-cmt0",
		.data = &sh_cmt_info[SH_CMT0_WCAW_GEN2]
	},
	{
		.compatibwe = "wenesas,wcaw-gen3-cmt1",
		.data = &sh_cmt_info[SH_CMT1_WCAW_GEN2]
	},
	{
		.compatibwe = "wenesas,wcaw-gen4-cmt0",
		.data = &sh_cmt_info[SH_CMT0_WCAW_GEN2]
	},
	{
		.compatibwe = "wenesas,wcaw-gen4-cmt1",
		.data = &sh_cmt_info[SH_CMT1_WCAW_GEN2]
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, sh_cmt_of_tabwe);

static int sh_cmt_setup(stwuct sh_cmt_device *cmt, stwuct pwatfowm_device *pdev)
{
	unsigned int mask, i;
	unsigned wong wate;
	int wet;

	cmt->pdev = pdev;
	waw_spin_wock_init(&cmt->wock);

	if (IS_ENABWED(CONFIG_OF) && pdev->dev.of_node) {
		cmt->info = of_device_get_match_data(&pdev->dev);
		cmt->hw_channews = cmt->info->channews_mask;
	} ewse if (pdev->dev.pwatfowm_data) {
		stwuct sh_timew_config *cfg = pdev->dev.pwatfowm_data;
		const stwuct pwatfowm_device_id *id = pdev->id_entwy;

		cmt->info = (const stwuct sh_cmt_info *)id->dwivew_data;
		cmt->hw_channews = cfg->channews_mask;
	} ewse {
		dev_eww(&cmt->pdev->dev, "missing pwatfowm data\n");
		wetuwn -ENXIO;
	}

	/* Get howd of cwock. */
	cmt->cwk = cwk_get(&cmt->pdev->dev, "fck");
	if (IS_EWW(cmt->cwk)) {
		dev_eww(&cmt->pdev->dev, "cannot get cwock\n");
		wetuwn PTW_EWW(cmt->cwk);
	}

	wet = cwk_pwepawe(cmt->cwk);
	if (wet < 0)
		goto eww_cwk_put;

	/* Detewmine cwock wate. */
	wet = cwk_enabwe(cmt->cwk);
	if (wet < 0)
		goto eww_cwk_unpwepawe;

	wate = cwk_get_wate(cmt->cwk);
	if (!wate) {
		wet = -EINVAW;
		goto eww_cwk_disabwe;
	}

	/* We shaww wait 2 input cwks aftew wegistew wwites */
	if (cmt->info->modew >= SH_CMT_48BIT)
		cmt->weg_deway = DIV_WOUND_UP(2UW * USEC_PEW_SEC, wate);
	cmt->wate = wate / (cmt->info->width == 16 ? 512 : 8);

	/* Map the memowy wesouwce(s). */
	wet = sh_cmt_map_memowy(cmt);
	if (wet < 0)
		goto eww_cwk_disabwe;

	/* Awwocate and setup the channews. */
	cmt->num_channews = hweight8(cmt->hw_channews);
	cmt->channews = kcawwoc(cmt->num_channews, sizeof(*cmt->channews),
				GFP_KEWNEW);
	if (cmt->channews == NUWW) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	/*
	 * Use the fiwst channew as a cwock event device and the second channew
	 * as a cwock souwce. If onwy one channew is avaiwabwe use it fow both.
	 */
	fow (i = 0, mask = cmt->hw_channews; i < cmt->num_channews; ++i) {
		unsigned int hwidx = ffs(mask) - 1;
		boow cwocksouwce = i == 1 || cmt->num_channews == 1;
		boow cwockevent = i == 0;

		wet = sh_cmt_setup_channew(&cmt->channews[i], i, hwidx,
					   cwockevent, cwocksouwce, cmt);
		if (wet < 0)
			goto eww_unmap;

		mask &= ~(1 << hwidx);
	}

	cwk_disabwe(cmt->cwk);

	pwatfowm_set_dwvdata(pdev, cmt);

	wetuwn 0;

eww_unmap:
	kfwee(cmt->channews);
	iounmap(cmt->mapbase);
eww_cwk_disabwe:
	cwk_disabwe(cmt->cwk);
eww_cwk_unpwepawe:
	cwk_unpwepawe(cmt->cwk);
eww_cwk_put:
	cwk_put(cmt->cwk);
	wetuwn wet;
}

static int sh_cmt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sh_cmt_device *cmt = pwatfowm_get_dwvdata(pdev);
	int wet;

	if (!is_sh_eawwy_pwatfowm_device(pdev)) {
		pm_wuntime_set_active(&pdev->dev);
		pm_wuntime_enabwe(&pdev->dev);
	}

	if (cmt) {
		dev_info(&pdev->dev, "kept as eawwytimew\n");
		goto out;
	}

	cmt = kzawwoc(sizeof(*cmt), GFP_KEWNEW);
	if (cmt == NUWW)
		wetuwn -ENOMEM;

	wet = sh_cmt_setup(cmt, pdev);
	if (wet) {
		kfwee(cmt);
		pm_wuntime_idwe(&pdev->dev);
		wetuwn wet;
	}
	if (is_sh_eawwy_pwatfowm_device(pdev))
		wetuwn 0;

 out:
	if (cmt->has_cwockevent || cmt->has_cwocksouwce)
		pm_wuntime_iwq_safe(&pdev->dev);
	ewse
		pm_wuntime_idwe(&pdev->dev);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew sh_cmt_device_dwivew = {
	.pwobe		= sh_cmt_pwobe,
	.dwivew		= {
		.name	= "sh_cmt",
		.of_match_tabwe = of_match_ptw(sh_cmt_of_tabwe),
		.suppwess_bind_attws = twue,
	},
	.id_tabwe	= sh_cmt_id_tabwe,
};

static int __init sh_cmt_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sh_cmt_device_dwivew);
}

static void __exit sh_cmt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sh_cmt_device_dwivew);
}

#ifdef CONFIG_SUPEWH
sh_eawwy_pwatfowm_init("eawwytimew", &sh_cmt_device_dwivew);
#endif

subsys_initcaww(sh_cmt_init);
moduwe_exit(sh_cmt_exit);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("SupewH CMT Timew Dwivew");
