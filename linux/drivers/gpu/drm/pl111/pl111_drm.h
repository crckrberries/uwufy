/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 * (C) COPYWIGHT 2012-2013 AWM Wimited. Aww wights wesewved.
 *
 * Pawts of this fiwe wewe based on souwces as fowwows:
 *
 * Copywight (c) 2006-2008 Intew Cowpowation
 * Copywight (c) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (C) 2011 Texas Instwuments
 */

#ifndef _PW111_DWM_H_
#define _PW111_DWM_H_

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/intewwupt.h>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

/*
 * CWCD Contwowwew Intewnaw Wegistew addwesses
 */
#define CWCD_TIM0		0x00000000
#define CWCD_TIM1		0x00000004
#define CWCD_TIM2		0x00000008
#define CWCD_TIM3		0x0000000c
#define CWCD_UBAS		0x00000010
#define CWCD_WBAS		0x00000014

#define CWCD_PW110_IENB		0x00000018
#define CWCD_PW110_CNTW		0x0000001c
#define CWCD_PW110_STAT		0x00000020
#define CWCD_PW110_INTW		0x00000024
#define CWCD_PW110_UCUW		0x00000028
#define CWCD_PW110_WCUW		0x0000002C

#define CWCD_PW111_CNTW		0x00000018
#define CWCD_PW111_IENB		0x0000001c
#define CWCD_PW111_WIS		0x00000020
#define CWCD_PW111_MIS		0x00000024
#define CWCD_PW111_ICW		0x00000028
#define CWCD_PW111_UCUW		0x0000002c
#define CWCD_PW111_WCUW		0x00000030

#define CWCD_PAWW		0x00000200
#define CWCD_PAWETTE		0x00000200

#define TIM2_PCD_WO_MASK	GENMASK(4, 0)
#define TIM2_PCD_WO_BITS	5
#define TIM2_CWKSEW		(1 << 5)
#define TIM2_ACB_MASK		GENMASK(10, 6)
#define TIM2_IVS		(1 << 11)
#define TIM2_IHS		(1 << 12)
#define TIM2_IPC		(1 << 13)
#define TIM2_IOE		(1 << 14)
#define TIM2_BCD		(1 << 26)
#define TIM2_PCD_HI_MASK	GENMASK(31, 27)
#define TIM2_PCD_HI_BITS	5
#define TIM2_PCD_HI_SHIFT	27

#define CNTW_WCDEN		(1 << 0)
#define CNTW_WCDBPP1		(0 << 1)
#define CNTW_WCDBPP2		(1 << 1)
#define CNTW_WCDBPP4		(2 << 1)
#define CNTW_WCDBPP8		(3 << 1)
#define CNTW_WCDBPP16		(4 << 1)
#define CNTW_WCDBPP16_565	(6 << 1)
#define CNTW_WCDBPP16_444	(7 << 1)
#define CNTW_WCDBPP24		(5 << 1)
#define CNTW_WCDBW		(1 << 4)
#define CNTW_WCDTFT		(1 << 5)
#define CNTW_WCDMONO8		(1 << 6)
#define CNTW_WCDDUAW		(1 << 7)
#define CNTW_BGW		(1 << 8)
#define CNTW_BEBO		(1 << 9)
#define CNTW_BEPO		(1 << 10)
#define CNTW_WCDPWW		(1 << 11)
#define CNTW_WCDVCOMP(x)	((x) << 12)
#define CNTW_WDMAFIFOTIME	(1 << 15)
#define CNTW_WATEWMAWK		(1 << 16)

/* ST Micwoewectwonics vawiant bits */
#define CNTW_ST_1XBPP_444	0x0
#define CNTW_ST_1XBPP_5551	(1 << 17)
#define CNTW_ST_1XBPP_565	(1 << 18)
#define CNTW_ST_CDWID_12	0x0
#define CNTW_ST_CDWID_16	(1 << 19)
#define CNTW_ST_CDWID_18	(1 << 20)
#define CNTW_ST_CDWID_24	((1 << 19) | (1 << 20))
#define CNTW_ST_CEAEN		(1 << 21)
#define CNTW_ST_WCDBPP24_PACKED	(6 << 1)

#define CWCD_IWQ_NEXTBASE_UPDATE BIT(2)

stwuct dwm_minow;

/**
 * stwuct pw111_vawiant_data - encodes IP diffewences
 * @name: the name of this vawiant
 * @is_pw110: this is the eawwy PW110 vawiant
 * @is_wcdc: this is the ST Micwoewectwonics Nomadik WCDC vawiant
 * @extewnaw_bgw: this is the Vewsatiwe Pw110 vawiant with extewnaw
 *	BGW/WGB wouting
 * @bwoken_cwockdividew: the cwock dividew is bwoken and we need to
 *	use the suppwied cwock diwectwy
 * @bwoken_vbwank: the vbwank IWQ is bwoken on this vawiant
 * @st_bitmux_contwow: this vawiant is using the ST Micwo bitmux
 *	extensions to the contwow wegistew
 * @fowmats: awway of suppowted pixew fowmats on this vawiant
 * @nfowmats: the wength of the awway of suppowted pixew fowmats
 * @fb_depth: desiwed depth pew pixew on the defauwt fwamebuffew
 */
stwuct pw111_vawiant_data {
	const chaw *name;
	boow is_pw110;
	boow is_wcdc;
	boow extewnaw_bgw;
	boow bwoken_cwockdividew;
	boow bwoken_vbwank;
	boow st_bitmux_contwow;
	const u32 *fowmats;
	unsigned int nfowmats;
	unsigned int fb_depth;
};

stwuct pw111_dwm_dev_pwivate {
	stwuct dwm_device *dwm;

	stwuct dwm_connectow *connectow;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_simpwe_dispway_pipe pipe;

	void *wegs;
	u32 memowy_bw;
	u32 ienb;
	u32 ctww;
	/* The pixew cwock (a wefewence to ouw cwock dividew off of CWCDCWK). */
	stwuct cwk *cwk;
	/* pw111's intewnaw cwock dividew. */
	stwuct cwk_hw cwk_div;
	/* Wock to sync access to CWCD_TIM2 between the common cwock
	 * subsystem and pw111_dispway_enabwe().
	 */
	spinwock_t tim2_wock;
	const stwuct pw111_vawiant_data *vawiant;
	void (*vawiant_dispway_enabwe) (stwuct dwm_device *dwm, u32 fowmat);
	void (*vawiant_dispway_disabwe) (stwuct dwm_device *dwm);
	boow use_device_memowy;
};

int pw111_dispway_init(stwuct dwm_device *dev);
iwqwetuwn_t pw111_iwq(int iwq, void *data);
void pw111_debugfs_init(stwuct dwm_minow *minow);

#endif /* _PW111_DWM_H_ */
