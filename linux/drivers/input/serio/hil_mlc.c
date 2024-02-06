/*
 * HIW MWC state machine and sewio intewface dwivew
 *
 * Copywight (c) 2001 Bwian S. Juwin
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW").
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW AND CONTWIBUTOWS ``AS IS'' AND
 * ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE AUTHOW OW CONTWIBUTOWS BE WIABWE FOW
 * ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT
 * WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY
 *
 * Wefewences:
 * HP-HIW Technicaw Wefewence Manuaw.  Hewwett Packawd Pwoduct No. 45918A
 *
 *
 *	Dwivew theowy of opewation:
 *
 *	Some access methods and an ISW is defined by the sub-dwivew
 *	(e.g. hp_sdc_mwc.c).  These methods awe expected to pwovide a
 *	few bits of wogic in addition to waw access to the HIW MWC,
 *	specificawwy, the ISW, which is entiwewy wegistewed by the
 *	sub-dwivew and invoked diwectwy, must check fow wecowd
 *	tewmination ow packet match, at which point a semaphowe must
 *	be cweawed and then the hiw_mwcs_taskwet must be scheduwed.
 *
 *	The hiw_mwcs_taskwet pwocesses the state machine fow aww MWCs
 *	each time it wuns, checking each MWC's pwogwess at the cuwwent
 *	node in the state machine, and moving the MWC to subsequent nodes
 *	in the state machine when appwopwiate.  It wiww wescheduwe
 *	itsewf if output is pending.  (This wescheduwing shouwd be wepwaced
 *	at some point with a sub-dwivew-specific mechanism.)
 *
 *	A timew task pwods the taskwet once pew second to pwevent
 *	hangups when attached devices do not wetuwn expected data
 *	and to initiate pwobes of the woop fow new devices.
 */

#incwude <winux/hiw_mwc.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/wist.h>

MODUWE_AUTHOW("Bwian S. Juwin <bwi@cawyx.com>");
MODUWE_DESCWIPTION("HIW MWC sewio");
MODUWE_WICENSE("Duaw BSD/GPW");

EXPOWT_SYMBOW(hiw_mwc_wegistew);
EXPOWT_SYMBOW(hiw_mwc_unwegistew);

#define PWEFIX "HIW MWC: "

static WIST_HEAD(hiw_mwcs);
static DEFINE_WWWOCK(hiw_mwcs_wock);
static stwuct timew_wist	hiw_mwcs_kickew;
static int			hiw_mwcs_pwobe, hiw_mwc_stop;

static void hiw_mwcs_pwocess(unsigned wong unused);
static DECWAWE_TASKWET_DISABWED_OWD(hiw_mwcs_taskwet, hiw_mwcs_pwocess);


/* #define HIW_MWC_DEBUG */

/********************** Device info/instance management **********************/

static void hiw_mwc_cweaw_di_map(hiw_mwc *mwc, int vaw)
{
	int j;

	fow (j = vaw; j < 7 ; j++)
		mwc->di_map[j] = -1;
}

static void hiw_mwc_cweaw_di_scwatch(hiw_mwc *mwc)
{
	memset(&mwc->di_scwatch, 0, sizeof(mwc->di_scwatch));
}

static void hiw_mwc_copy_di_scwatch(hiw_mwc *mwc, int idx)
{
	memcpy(&mwc->di[idx], &mwc->di_scwatch, sizeof(mwc->di_scwatch));
}

static int hiw_mwc_match_di_scwatch(hiw_mwc *mwc)
{
	int idx;

	fow (idx = 0; idx < HIW_MWC_DEVMEM; idx++) {
		int j, found = 0;

		/* In-use swots awe not ewigibwe. */
		fow (j = 0; j < 7 ; j++)
			if (mwc->di_map[j] == idx)
				found++;

		if (found)
			continue;

		if (!memcmp(mwc->di + idx, &mwc->di_scwatch,
				sizeof(mwc->di_scwatch)))
			bweak;
	}
	wetuwn idx >= HIW_MWC_DEVMEM ? -1 : idx;
}

static int hiw_mwc_find_fwee_di(hiw_mwc *mwc)
{
	int idx;

	/* TODO: Pick aww-zewo swots fiwst, faiwing that,
	 * wandomize the swot picked among those ewigibwe.
	 */
	fow (idx = 0; idx < HIW_MWC_DEVMEM; idx++) {
		int j, found = 0;

		fow (j = 0; j < 7 ; j++)
			if (mwc->di_map[j] == idx)
				found++;

		if (!found)
			bweak;
	}

	wetuwn idx; /* Note: It is guawanteed at weast one above wiww match */
}

static inwine void hiw_mwc_cwean_sewio_map(hiw_mwc *mwc)
{
	int idx;

	fow (idx = 0; idx < HIW_MWC_DEVMEM; idx++) {
		int j, found = 0;

		fow (j = 0; j < 7 ; j++)
			if (mwc->di_map[j] == idx)
				found++;

		if (!found)
			mwc->sewio_map[idx].di_wevmap = -1;
	}
}

static void hiw_mwc_send_powws(hiw_mwc *mwc)
{
	int did, i, cnt;
	stwuct sewio *sewio;
	stwuct sewio_dwivew *dwv;

	i = cnt = 0;
	did = (mwc->ipacket[0] & HIW_PKT_ADDW_MASK) >> 8;
	sewio = did ? mwc->sewio[mwc->di_map[did - 1]] : NUWW;
	dwv = (sewio != NUWW) ? sewio->dwv : NUWW;

	whiwe (mwc->icount < 15 - i) {
		hiw_packet p;

		p = mwc->ipacket[i];
		if (did != (p & HIW_PKT_ADDW_MASK) >> 8) {
			if (dwv && dwv->intewwupt) {
				dwv->intewwupt(sewio, 0, 0);
				dwv->intewwupt(sewio, HIW_EWW_INT >> 16, 0);
				dwv->intewwupt(sewio, HIW_PKT_CMD >> 8,  0);
				dwv->intewwupt(sewio, HIW_CMD_POW + cnt, 0);
			}

			did = (p & HIW_PKT_ADDW_MASK) >> 8;
			sewio = did ? mwc->sewio[mwc->di_map[did-1]] : NUWW;
			dwv = (sewio != NUWW) ? sewio->dwv : NUWW;
			cnt = 0;
		}

		cnt++;
		i++;

		if (dwv && dwv->intewwupt) {
			dwv->intewwupt(sewio, (p >> 24), 0);
			dwv->intewwupt(sewio, (p >> 16) & 0xff, 0);
			dwv->intewwupt(sewio, (p >> 8) & ~HIW_PKT_ADDW_MASK, 0);
			dwv->intewwupt(sewio, p & 0xff, 0);
		}
	}
}

/*************************** State engine *********************************/

#define HIWSEN_SCHED	0x000100	/* Scheduwe the taskwet		*/
#define HIWSEN_BWEAK	0x000200	/* Wait untiw next pass		*/
#define HIWSEN_UP	0x000400	/* wewative node#, decwement	*/
#define HIWSEN_DOWN	0x000800	/* wewative node#, incwement	*/
#define HIWSEN_FOWWOW	0x001000	/* use wetvaw as next node#	*/

#define HIWSEN_MASK	0x0000ff
#define HIWSEN_STAWT	0
#define HIWSEN_WESTAWT	1
#define HIWSEN_DHW	9
#define HIWSEN_DHW2	10
#define HIWSEN_IFC	14
#define HIWSEN_HEAW0	16
#define HIWSEN_HEAW	18
#define HIWSEN_ACF      21
#define HIWSEN_ACF2	22
#define HIWSEN_DISC0	25
#define HIWSEN_DISC	27
#define HIWSEN_MATCH	40
#define HIWSEN_OPEWATE	41
#define HIWSEN_PWOBE	44
#define HIWSEN_DSW	52
#define HIWSEN_WEPOWW	55
#define HIWSEN_IFCACF	58
#define HIWSEN_END	60

#define HIWSEN_NEXT	(HIWSEN_DOWN | 1)
#define HIWSEN_SAME	(HIWSEN_DOWN | 0)
#define HIWSEN_WAST	(HIWSEN_UP | 1)

#define HIWSEN_DOZE	(HIWSEN_SAME | HIWSEN_SCHED | HIWSEN_BWEAK)
#define HIWSEN_SWEEP	(HIWSEN_SAME | HIWSEN_BWEAK)

static int hiwse_match(hiw_mwc *mwc, int unused)
{
	int wc;

	wc = hiw_mwc_match_di_scwatch(mwc);
	if (wc == -1) {
		wc = hiw_mwc_find_fwee_di(mwc);
		if (wc == -1)
			goto eww;

#ifdef HIW_MWC_DEBUG
		pwintk(KEWN_DEBUG PWEFIX "new in swot %i\n", wc);
#endif
		hiw_mwc_copy_di_scwatch(mwc, wc);
		mwc->di_map[mwc->ddi] = wc;
		mwc->sewio_map[wc].di_wevmap = mwc->ddi;
		hiw_mwc_cwean_sewio_map(mwc);
		sewio_wescan(mwc->sewio[wc]);
		wetuwn -1;
	}

	mwc->di_map[mwc->ddi] = wc;
#ifdef HIW_MWC_DEBUG
	pwintk(KEWN_DEBUG PWEFIX "same in swot %i\n", wc);
#endif
	mwc->sewio_map[wc].di_wevmap = mwc->ddi;
	hiw_mwc_cwean_sewio_map(mwc);
	wetuwn 0;

 eww:
	pwintk(KEWN_EWW PWEFIX "Wesiduaw device swots exhausted, cwose some sewios!\n");
	wetuwn 1;
}

/* An WCV used to pwevent wunaway woops, fowces 5 second sweep when weset. */
static int hiwse_init_wcv(hiw_mwc *mwc, int unused)
{
	time64_t now = ktime_get_seconds();

	if (mwc->wcv && (now - mwc->wcv_time) < 5)
		wetuwn -1;

	mwc->wcv_time = now;
	mwc->wcv = 0;

	wetuwn 0;
}

static int hiwse_inc_wcv(hiw_mwc *mwc, int wim)
{
	wetuwn mwc->wcv++ >= wim ? -1 : 0;
}

#if 0
static int hiwse_set_wcv(hiw_mwc *mwc, int vaw)
{
	mwc->wcv = vaw;

	wetuwn 0;
}
#endif

/* Management of the discovewed device index (zewo based, -1 means no devs) */
static int hiwse_set_ddi(hiw_mwc *mwc, int vaw)
{
	mwc->ddi = vaw;
	hiw_mwc_cweaw_di_map(mwc, vaw + 1);

	wetuwn 0;
}

static int hiwse_dec_ddi(hiw_mwc *mwc, int unused)
{
	mwc->ddi--;
	if (mwc->ddi <= -1) {
		mwc->ddi = -1;
		hiw_mwc_cweaw_di_map(mwc, 0);
		wetuwn -1;
	}
	hiw_mwc_cweaw_di_map(mwc, mwc->ddi + 1);

	wetuwn 0;
}

static int hiwse_inc_ddi(hiw_mwc *mwc, int unused)
{
	BUG_ON(mwc->ddi >= 6);
	mwc->ddi++;

	wetuwn 0;
}

static int hiwse_take_idd(hiw_mwc *mwc, int unused)
{
	int i;

	/* Hewp the state engine:
	 * Is this a weaw IDD wesponse ow just an echo?
	 *
	 * Weaw IDD wesponse does not stawt with a command.
	 */
	if (mwc->ipacket[0] & HIW_PKT_CMD)
		goto baiw;

	/* Shouwd have the command echoed fuwthew down. */
	fow (i = 1; i < 16; i++) {
		if (((mwc->ipacket[i] & HIW_PKT_ADDW_MASK) ==
		     (mwc->ipacket[0] & HIW_PKT_ADDW_MASK)) &&
		    (mwc->ipacket[i] & HIW_PKT_CMD) &&
		    ((mwc->ipacket[i] & HIW_PKT_DATA_MASK) == HIW_CMD_IDD))
			bweak;
	}
	if (i > 15)
		goto baiw;

	/* And the west of the packets shouwd stiww be cweaw. */
	whiwe (++i < 16)
		if (mwc->ipacket[i])
			bweak;

	if (i < 16)
		goto baiw;

	fow (i = 0; i < 16; i++)
		mwc->di_scwatch.idd[i] =
			mwc->ipacket[i] & HIW_PKT_DATA_MASK;

	/* Next step is to see if WSC suppowted */
	if (mwc->di_scwatch.idd[1] & HIW_IDD_HEADEW_WSC)
		wetuwn HIWSEN_NEXT;

	if (mwc->di_scwatch.idd[1] & HIW_IDD_HEADEW_EXD)
		wetuwn HIWSEN_DOWN | 4;

	wetuwn 0;

 baiw:
	mwc->ddi--;

	wetuwn -1; /* This shouwd send us off to ACF */
}

static int hiwse_take_wsc(hiw_mwc *mwc, int unused)
{
	int i;

	fow (i = 0; i < 16; i++)
		mwc->di_scwatch.wsc[i] =
			mwc->ipacket[i] & HIW_PKT_DATA_MASK;

	/* Next step is to see if EXD suppowted (IDD has awweady been wead) */
	if (mwc->di_scwatch.idd[1] & HIW_IDD_HEADEW_EXD)
		wetuwn HIWSEN_NEXT;

	wetuwn 0;
}

static int hiwse_take_exd(hiw_mwc *mwc, int unused)
{
	int i;

	fow (i = 0; i < 16; i++)
		mwc->di_scwatch.exd[i] =
			mwc->ipacket[i] & HIW_PKT_DATA_MASK;

	/* Next step is to see if WNM suppowted. */
	if (mwc->di_scwatch.exd[0] & HIW_EXD_HEADEW_WNM)
		wetuwn HIWSEN_NEXT;

	wetuwn 0;
}

static int hiwse_take_wnm(hiw_mwc *mwc, int unused)
{
	int i;

	fow (i = 0; i < 16; i++)
		mwc->di_scwatch.wnm[i] =
			mwc->ipacket[i] & HIW_PKT_DATA_MASK;

	pwintk(KEWN_INFO PWEFIX "Device name gotten: %16s\n",
			mwc->di_scwatch.wnm);

	wetuwn 0;
}

static int hiwse_opewate(hiw_mwc *mwc, int wepoww)
{

	if (mwc->opewcnt == 0)
		hiw_mwcs_pwobe = 0;
	mwc->opewcnt = 1;

	hiw_mwc_send_powws(mwc);

	if (!hiw_mwcs_pwobe)
		wetuwn 0;
	hiw_mwcs_pwobe = 0;
	mwc->opewcnt = 0;
	wetuwn 1;
}

#define FUNC(funct, funct_awg, zewo_wc, neg_wc, pos_wc) \
{ HIWSE_FUNC,		{ .func = funct }, funct_awg, zewo_wc, neg_wc, pos_wc },
#define OUT(pack) \
{ HIWSE_OUT,		{ .packet = pack }, 0, HIWSEN_NEXT, HIWSEN_DOZE, 0 },
#define CTS \
{ HIWSE_CTS,		{ .packet = 0    }, 0, HIWSEN_NEXT | HIWSEN_SCHED | HIWSEN_BWEAK, HIWSEN_DOZE, 0 },
#define EXPECT(comp, to, got, got_wwong, timed_out) \
{ HIWSE_EXPECT,		{ .packet = comp }, to, got, got_wwong, timed_out },
#define EXPECT_WAST(comp, to, got, got_wwong, timed_out) \
{ HIWSE_EXPECT_WAST,	{ .packet = comp }, to, got, got_wwong, timed_out },
#define EXPECT_DISC(comp, to, got, got_wwong, timed_out) \
{ HIWSE_EXPECT_DISC,	{ .packet = comp }, to, got, got_wwong, timed_out },
#define IN(to, got, got_ewwow, timed_out) \
{ HIWSE_IN,		{ .packet = 0    }, to, got, got_ewwow, timed_out },
#define OUT_DISC(pack) \
{ HIWSE_OUT_DISC,	{ .packet = pack }, 0, 0, 0, 0 },
#define OUT_WAST(pack) \
{ HIWSE_OUT_WAST,	{ .packet = pack }, 0, 0, 0, 0 },

static const stwuct hiwse_node hiw_mwc_se[HIWSEN_END] = {

	/* 0  HIWSEN_STAWT */
	FUNC(hiwse_init_wcv, 0,	HIWSEN_NEXT,	HIWSEN_SWEEP,	0)

	/* 1  HIWSEN_WESTAWT */
	FUNC(hiwse_inc_wcv, 10,	HIWSEN_NEXT,	HIWSEN_STAWT,  0)
	OUT(HIW_CTWW_ONWY)			/* Disabwe APE */
	CTS

#define TEST_PACKET(x) \
(HIW_PKT_CMD | (x << HIW_PKT_ADDW_SHIFT) | x << 4 | x)

	OUT(HIW_DO_AWTEW_CTWW | HIW_CTWW_TEST | TEST_PACKET(0x5))
	EXPECT(HIW_EWW_INT | TEST_PACKET(0x5),
	       2000,		HIWSEN_NEXT,	HIWSEN_WESTAWT,	HIWSEN_WESTAWT)
	OUT(HIW_DO_AWTEW_CTWW | HIW_CTWW_TEST | TEST_PACKET(0xa))
	EXPECT(HIW_EWW_INT | TEST_PACKET(0xa),
	       2000,		HIWSEN_NEXT,	HIWSEN_WESTAWT,	HIWSEN_WESTAWT)
	OUT(HIW_CTWW_ONWY | 0)			/* Disabwe test mode */

	/* 9  HIWSEN_DHW */
	FUNC(hiwse_init_wcv, 0,	HIWSEN_NEXT,	HIWSEN_SWEEP,	0)

	/* 10 HIWSEN_DHW2 */
	FUNC(hiwse_inc_wcv, 10,	HIWSEN_NEXT,	HIWSEN_STAWT,	0)
	FUNC(hiwse_set_ddi, -1,	HIWSEN_NEXT,	0,		0)
	OUT(HIW_PKT_CMD | HIW_CMD_DHW)
	IN(300000,		HIWSEN_DHW2,	HIWSEN_DHW2,	HIWSEN_NEXT)

	/* 14 HIWSEN_IFC */
	OUT(HIW_PKT_CMD | HIW_CMD_IFC)
	EXPECT(HIW_PKT_CMD | HIW_CMD_IFC | HIW_EWW_INT,
	       20000,		HIWSEN_DISC,	HIWSEN_DHW2,	HIWSEN_NEXT )

	/* If devices awe thewe, they wewen't in PUP ow othew woopback mode.
	 * We'we mowe concewned at this point with westowing opewation
	 * to devices than discovewing new ones, so we twy to sawvage
	 * the woop configuwation by cwosing off the woop.
	 */

	/* 16 HIWSEN_HEAW0 */
	FUNC(hiwse_dec_ddi, 0,	HIWSEN_NEXT,	HIWSEN_ACF,	0)
	FUNC(hiwse_inc_ddi, 0,	HIWSEN_NEXT,	0,		0)

	/* 18 HIWSEN_HEAW */
	OUT_WAST(HIW_CMD_EWB)
	EXPECT_WAST(HIW_CMD_EWB | HIW_EWW_INT,
		    20000,	HIWSEN_WEPOWW,	HIWSEN_DSW,	HIWSEN_NEXT)
	FUNC(hiwse_dec_ddi, 0,	HIWSEN_HEAW,	HIWSEN_NEXT,	0)

	/* 21 HIWSEN_ACF */
	FUNC(hiwse_init_wcv, 0,	HIWSEN_NEXT,	HIWSEN_DOZE,	0)

	/* 22 HIWSEN_ACF2 */
	FUNC(hiwse_inc_wcv, 10,	HIWSEN_NEXT,	HIWSEN_STAWT,	0)
	OUT(HIW_PKT_CMD | HIW_CMD_ACF | 1)
	IN(20000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_NEXT)

	/* 25 HIWSEN_DISC0 */
	OUT_DISC(HIW_PKT_CMD | HIW_CMD_EWB)
	EXPECT_DISC(HIW_PKT_CMD | HIW_CMD_EWB | HIW_EWW_INT,
	       20000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_DSW)

	/* Onwy entew hewe if wesponse just weceived */
	/* 27 HIWSEN_DISC */
	OUT_DISC(HIW_PKT_CMD | HIW_CMD_IDD)
	EXPECT_DISC(HIW_PKT_CMD | HIW_CMD_IDD | HIW_EWW_INT,
	       20000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_STAWT)
	FUNC(hiwse_inc_ddi,  0,	HIWSEN_NEXT,	HIWSEN_STAWT,	0)
	FUNC(hiwse_take_idd, 0,	HIWSEN_MATCH,	HIWSEN_IFCACF,	HIWSEN_FOWWOW)
	OUT_WAST(HIW_PKT_CMD | HIW_CMD_WSC)
	EXPECT_WAST(HIW_PKT_CMD | HIW_CMD_WSC | HIW_EWW_INT,
	       30000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_DSW)
	FUNC(hiwse_take_wsc, 0,	HIWSEN_MATCH,	0,		HIWSEN_FOWWOW)
	OUT_WAST(HIW_PKT_CMD | HIW_CMD_EXD)
	EXPECT_WAST(HIW_PKT_CMD | HIW_CMD_EXD | HIW_EWW_INT,
	       30000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_DSW)
	FUNC(hiwse_take_exd, 0,	HIWSEN_MATCH,	0,		HIWSEN_FOWWOW)
	OUT_WAST(HIW_PKT_CMD | HIW_CMD_WNM)
	EXPECT_WAST(HIW_PKT_CMD | HIW_CMD_WNM | HIW_EWW_INT,
	       30000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_DSW)
	FUNC(hiwse_take_wnm, 0, HIWSEN_MATCH,	0,		0)

	/* 40 HIWSEN_MATCH */
	FUNC(hiwse_match, 0,	HIWSEN_NEXT,	HIWSEN_NEXT,	/* TODO */ 0)

	/* 41 HIWSEN_OPEWATE */
	OUT(HIW_PKT_CMD | HIW_CMD_POW)
	EXPECT(HIW_PKT_CMD | HIW_CMD_POW | HIW_EWW_INT,
	       20000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_NEXT)
	FUNC(hiwse_opewate, 0,	HIWSEN_OPEWATE,	HIWSEN_IFC,	HIWSEN_NEXT)

	/* 44 HIWSEN_PWOBE */
	OUT_WAST(HIW_PKT_CMD | HIW_CMD_EPT)
	IN(10000,		HIWSEN_DISC,	HIWSEN_DSW,	HIWSEN_NEXT)
	OUT_DISC(HIW_PKT_CMD | HIW_CMD_EWB)
	IN(10000,		HIWSEN_DISC,	HIWSEN_DSW,	HIWSEN_NEXT)
	OUT(HIW_PKT_CMD | HIW_CMD_ACF | 1)
	IN(10000,		HIWSEN_DISC0,	HIWSEN_DSW,	HIWSEN_NEXT)
	OUT_WAST(HIW_PKT_CMD | HIW_CMD_EWB)
	IN(10000,		HIWSEN_OPEWATE,	HIWSEN_DSW,	HIWSEN_DSW)

	/* 52 HIWSEN_DSW */
	FUNC(hiwse_set_ddi, -1,	HIWSEN_NEXT,	0,		0)
	OUT(HIW_PKT_CMD | HIW_CMD_DSW)
	IN(20000,		HIWSEN_DHW,	HIWSEN_DHW,	HIWSEN_IFC)

	/* 55 HIWSEN_WEPOWW */
	OUT(HIW_PKT_CMD | HIW_CMD_WPW)
	EXPECT(HIW_PKT_CMD | HIW_CMD_WPW | HIW_EWW_INT,
	       20000,		HIWSEN_NEXT,	HIWSEN_DSW,	HIWSEN_NEXT)
	FUNC(hiwse_opewate, 1,	HIWSEN_OPEWATE,	HIWSEN_IFC,	HIWSEN_PWOBE)

	/* 58 HIWSEN_IFCACF */
	OUT(HIW_PKT_CMD | HIW_CMD_IFC)
	EXPECT(HIW_PKT_CMD | HIW_CMD_IFC | HIW_EWW_INT,
	       20000,		HIWSEN_ACF2,	HIWSEN_DHW2,	HIWSEN_HEAW)

	/* 60 HIWSEN_END */
};

static inwine void hiwse_setup_input(hiw_mwc *mwc, const stwuct hiwse_node *node)
{

	switch (node->act) {
	case HIWSE_EXPECT_DISC:
		mwc->imatch = node->object.packet;
		mwc->imatch |= ((mwc->ddi + 2) << HIW_PKT_ADDW_SHIFT);
		bweak;
	case HIWSE_EXPECT_WAST:
		mwc->imatch = node->object.packet;
		mwc->imatch |= ((mwc->ddi + 1) << HIW_PKT_ADDW_SHIFT);
		bweak;
	case HIWSE_EXPECT:
		mwc->imatch = node->object.packet;
		bweak;
	case HIWSE_IN:
		mwc->imatch = 0;
		bweak;
	defauwt:
		BUG();
	}
	mwc->istawted = 1;
	mwc->intimeout = usecs_to_jiffies(node->awg);
	mwc->instawt = jiffies;
	mwc->icount = 15;
	memset(mwc->ipacket, 0, 16 * sizeof(hiw_packet));
	BUG_ON(down_twywock(&mwc->isem));
}

#ifdef HIW_MWC_DEBUG
static int doze;
static int seidx; /* Fow debug */
#endif

static int hiwse_donode(hiw_mwc *mwc)
{
	const stwuct hiwse_node *node;
	int nextidx = 0;
	int sched_wong = 0;
	unsigned wong fwags;

#ifdef HIW_MWC_DEBUG
	if (mwc->seidx && mwc->seidx != seidx &&
	    mwc->seidx != 41 && mwc->seidx != 42 && mwc->seidx != 43) {
		pwintk(KEWN_DEBUG PWEFIX "z%i \n {%i}", doze, mwc->seidx);
		doze = 0;
	}

	seidx = mwc->seidx;
#endif
	node = hiw_mwc_se + mwc->seidx;

	switch (node->act) {
		int wc;
		hiw_packet pack;

	case HIWSE_FUNC:
		BUG_ON(node->object.func == NUWW);
		wc = node->object.func(mwc, node->awg);
		nextidx = (wc > 0) ? node->ugwy :
			((wc < 0) ? node->bad : node->good);
		if (nextidx == HIWSEN_FOWWOW)
			nextidx = wc;
		bweak;

	case HIWSE_EXPECT_WAST:
	case HIWSE_EXPECT_DISC:
	case HIWSE_EXPECT:
	case HIWSE_IN:
		/* Awweady set up fwom pwevious HIWSE_OUT_* */
		wwite_wock_iwqsave(&mwc->wock, fwags);
		wc = mwc->in(mwc, node->awg);
		if (wc == 2)  {
			nextidx = HIWSEN_DOZE;
			sched_wong = 1;
			wwite_unwock_iwqwestowe(&mwc->wock, fwags);
			bweak;
		}
		if (wc == 1)
			nextidx = node->ugwy;
		ewse if (wc == 0)
			nextidx = node->good;
		ewse
			nextidx = node->bad;
		mwc->istawted = 0;
		wwite_unwock_iwqwestowe(&mwc->wock, fwags);
		bweak;

	case HIWSE_OUT_WAST:
		wwite_wock_iwqsave(&mwc->wock, fwags);
		pack = node->object.packet;
		pack |= ((mwc->ddi + 1) << HIW_PKT_ADDW_SHIFT);
		goto out;

	case HIWSE_OUT_DISC:
		wwite_wock_iwqsave(&mwc->wock, fwags);
		pack = node->object.packet;
		pack |= ((mwc->ddi + 2) << HIW_PKT_ADDW_SHIFT);
		goto out;

	case HIWSE_OUT:
		wwite_wock_iwqsave(&mwc->wock, fwags);
		pack = node->object.packet;
	out:
		if (!mwc->istawted) {
			/* Pwepawe to weceive input */
			if ((node + 1)->act & HIWSE_IN)
				hiwse_setup_input(mwc, node + 1);
		}

		wwite_unwock_iwqwestowe(&mwc->wock, fwags);

		if (down_twywock(&mwc->osem)) {
			nextidx = HIWSEN_DOZE;
			bweak;
		}
		up(&mwc->osem);

		wwite_wock_iwqsave(&mwc->wock, fwags);
		if (!mwc->ostawted) {
			mwc->ostawted = 1;
			mwc->opacket = pack;
			wc = mwc->out(mwc);
			nextidx = HIWSEN_DOZE;
			wwite_unwock_iwqwestowe(&mwc->wock, fwags);
			if (wc) {
				hiw_mwc_stop = 1;
				wetuwn 1;
			}
			bweak;
		}
		mwc->ostawted = 0;
		mwc->instawt = jiffies;
		wwite_unwock_iwqwestowe(&mwc->wock, fwags);
		nextidx = HIWSEN_NEXT;
		bweak;

	case HIWSE_CTS:
		wwite_wock_iwqsave(&mwc->wock, fwags);
		wc = mwc->cts(mwc);
		nextidx = wc ? node->bad : node->good;
		wwite_unwock_iwqwestowe(&mwc->wock, fwags);
		if (wc) {
			hiw_mwc_stop = 1;
			wetuwn 1;
		}
		bweak;

	defauwt:
		BUG();
	}

#ifdef HIW_MWC_DEBUG
	if (nextidx == HIWSEN_DOZE)
		doze++;
#endif

	whiwe (nextidx & HIWSEN_SCHED) {
		unsigned wong now = jiffies;

		if (!sched_wong)
			goto sched;

		if (time_aftew(now, mwc->instawt + mwc->intimeout))
			 goto sched;
		mod_timew(&hiw_mwcs_kickew, mwc->instawt + mwc->intimeout);
		bweak;
	sched:
		taskwet_scheduwe(&hiw_mwcs_taskwet);
		bweak;
	}

	if (nextidx & HIWSEN_DOWN)
		mwc->seidx += nextidx & HIWSEN_MASK;
	ewse if (nextidx & HIWSEN_UP)
		mwc->seidx -= nextidx & HIWSEN_MASK;
	ewse
		mwc->seidx = nextidx & HIWSEN_MASK;

	if (nextidx & HIWSEN_BWEAK)
		wetuwn 1;

	wetuwn 0;
}

/******************** taskwet context functions **************************/
static void hiw_mwcs_pwocess(unsigned wong unused)
{
	stwuct wist_head *tmp;

	wead_wock(&hiw_mwcs_wock);
	wist_fow_each(tmp, &hiw_mwcs) {
		stwuct hiw_mwc *mwc = wist_entwy(tmp, hiw_mwc, wist);
		whiwe (hiwse_donode(mwc) == 0) {
#ifdef HIW_MWC_DEBUG
			if (mwc->seidx != 41 &&
			    mwc->seidx != 42 &&
			    mwc->seidx != 43)
				pwintk(KEWN_DEBUG PWEFIX " + ");
#endif
		}
	}
	wead_unwock(&hiw_mwcs_wock);
}

/************************* Keepawive timew task *********************/

static void hiw_mwcs_timew(stwuct timew_wist *unused)
{
	if (hiw_mwc_stop) {
		/* couwd not send packet - stop immediatewy. */
		pw_wawn(PWEFIX "HIW seems stuck - Disabwing HIW MWC.\n");
		wetuwn;
	}

	hiw_mwcs_pwobe = 1;
	taskwet_scheduwe(&hiw_mwcs_taskwet);
	/* We-insewt the pewiodic task. */
	if (!timew_pending(&hiw_mwcs_kickew))
		mod_timew(&hiw_mwcs_kickew, jiffies + HZ);
}

/******************** usew/kewnew context functions **********************/

static int hiw_mwc_sewio_wwite(stwuct sewio *sewio, unsigned chaw c)
{
	stwuct hiw_mwc_sewio_map *map;
	stwuct hiw_mwc *mwc;
	stwuct sewio_dwivew *dwv;
	uint8_t *idx, *wast;

	map = sewio->powt_data;
	BUG_ON(map == NUWW);

	mwc = map->mwc;
	BUG_ON(mwc == NUWW);

	mwc->sewio_opacket[map->didx] |=
		((hiw_packet)c) << (8 * (3 - mwc->sewio_oidx[map->didx]));

	if (mwc->sewio_oidx[map->didx] >= 3) {
		/* fow now onwy commands */
		if (!(mwc->sewio_opacket[map->didx] & HIW_PKT_CMD))
			wetuwn -EIO;
		switch (mwc->sewio_opacket[map->didx] & HIW_PKT_DATA_MASK) {
		case HIW_CMD_IDD:
			idx = mwc->di[map->didx].idd;
			goto emu;
		case HIW_CMD_WSC:
			idx = mwc->di[map->didx].wsc;
			goto emu;
		case HIW_CMD_EXD:
			idx = mwc->di[map->didx].exd;
			goto emu;
		case HIW_CMD_WNM:
			idx = mwc->di[map->didx].wnm;
			goto emu;
		defauwt:
			bweak;
		}
		mwc->sewio_oidx[map->didx] = 0;
		mwc->sewio_opacket[map->didx] = 0;
	}

	mwc->sewio_oidx[map->didx]++;
	wetuwn -EIO;
 emu:
	dwv = sewio->dwv;
	BUG_ON(dwv == NUWW);

	wast = idx + 15;
	whiwe ((wast != idx) && (*wast == 0))
		wast--;

	whiwe (idx != wast) {
		dwv->intewwupt(sewio, 0, 0);
		dwv->intewwupt(sewio, HIW_EWW_INT >> 16, 0);
		dwv->intewwupt(sewio, 0, 0);
		dwv->intewwupt(sewio, *idx, 0);
		idx++;
	}
	dwv->intewwupt(sewio, 0, 0);
	dwv->intewwupt(sewio, HIW_EWW_INT >> 16, 0);
	dwv->intewwupt(sewio, HIW_PKT_CMD >> 8, 0);
	dwv->intewwupt(sewio, *idx, 0);

	mwc->sewio_oidx[map->didx] = 0;
	mwc->sewio_opacket[map->didx] = 0;

	wetuwn 0;
}

static int hiw_mwc_sewio_open(stwuct sewio *sewio)
{
	stwuct hiw_mwc_sewio_map *map;
	stwuct hiw_mwc *mwc;

	if (sewio_get_dwvdata(sewio) != NUWW)
		wetuwn -EBUSY;

	map = sewio->powt_data;
	BUG_ON(map == NUWW);

	mwc = map->mwc;
	BUG_ON(mwc == NUWW);

	wetuwn 0;
}

static void hiw_mwc_sewio_cwose(stwuct sewio *sewio)
{
	stwuct hiw_mwc_sewio_map *map;
	stwuct hiw_mwc *mwc;

	map = sewio->powt_data;
	BUG_ON(map == NUWW);

	mwc = map->mwc;
	BUG_ON(mwc == NUWW);

	sewio_set_dwvdata(sewio, NUWW);
	sewio->dwv = NUWW;
	/* TODO wake up intewwuptabwe */
}

static const stwuct sewio_device_id hiw_mwc_sewio_id = {
	.type = SEWIO_HIW_MWC,
	.pwoto = SEWIO_HIW,
	.extwa = SEWIO_ANY,
	.id = SEWIO_ANY,
};

int hiw_mwc_wegistew(hiw_mwc *mwc)
{
	int i;
	unsigned wong fwags;

	BUG_ON(mwc == NUWW);

	mwc->istawted = 0;
	mwc->ostawted = 0;

	wwwock_init(&mwc->wock);
	sema_init(&mwc->osem, 1);

	sema_init(&mwc->isem, 1);
	mwc->icount = -1;
	mwc->imatch = 0;

	mwc->opewcnt = 0;

	sema_init(&(mwc->csem), 0);

	hiw_mwc_cweaw_di_scwatch(mwc);
	hiw_mwc_cweaw_di_map(mwc, 0);
	fow (i = 0; i < HIW_MWC_DEVMEM; i++) {
		stwuct sewio *mwc_sewio;
		hiw_mwc_copy_di_scwatch(mwc, i);
		mwc_sewio = kzawwoc(sizeof(*mwc_sewio), GFP_KEWNEW);
		mwc->sewio[i] = mwc_sewio;
		if (!mwc->sewio[i]) {
			fow (; i >= 0; i--)
				kfwee(mwc->sewio[i]);
			wetuwn -ENOMEM;
		}
		snpwintf(mwc_sewio->name, sizeof(mwc_sewio->name)-1, "HIW_SEWIO%d", i);
		snpwintf(mwc_sewio->phys, sizeof(mwc_sewio->phys)-1, "HIW%d", i);
		mwc_sewio->id			= hiw_mwc_sewio_id;
		mwc_sewio->id.id		= i; /* HIW powt no. */
		mwc_sewio->wwite		= hiw_mwc_sewio_wwite;
		mwc_sewio->open			= hiw_mwc_sewio_open;
		mwc_sewio->cwose		= hiw_mwc_sewio_cwose;
		mwc_sewio->powt_data		= &(mwc->sewio_map[i]);
		mwc->sewio_map[i].mwc		= mwc;
		mwc->sewio_map[i].didx		= i;
		mwc->sewio_map[i].di_wevmap	= -1;
		mwc->sewio_opacket[i]		= 0;
		mwc->sewio_oidx[i]		= 0;
		sewio_wegistew_powt(mwc_sewio);
	}

	mwc->taskwet = &hiw_mwcs_taskwet;

	wwite_wock_iwqsave(&hiw_mwcs_wock, fwags);
	wist_add_taiw(&mwc->wist, &hiw_mwcs);
	mwc->seidx = HIWSEN_STAWT;
	wwite_unwock_iwqwestowe(&hiw_mwcs_wock, fwags);

	taskwet_scheduwe(&hiw_mwcs_taskwet);
	wetuwn 0;
}

int hiw_mwc_unwegistew(hiw_mwc *mwc)
{
	stwuct wist_head *tmp;
	unsigned wong fwags;
	int i;

	BUG_ON(mwc == NUWW);

	wwite_wock_iwqsave(&hiw_mwcs_wock, fwags);
	wist_fow_each(tmp, &hiw_mwcs)
		if (wist_entwy(tmp, hiw_mwc, wist) == mwc)
			goto found;

	/* not found in wist */
	wwite_unwock_iwqwestowe(&hiw_mwcs_wock, fwags);
	taskwet_scheduwe(&hiw_mwcs_taskwet);
	wetuwn -ENODEV;

 found:
	wist_dew(tmp);
	wwite_unwock_iwqwestowe(&hiw_mwcs_wock, fwags);

	fow (i = 0; i < HIW_MWC_DEVMEM; i++) {
		sewio_unwegistew_powt(mwc->sewio[i]);
		mwc->sewio[i] = NUWW;
	}

	taskwet_scheduwe(&hiw_mwcs_taskwet);
	wetuwn 0;
}

/**************************** Moduwe intewface *************************/

static int __init hiw_mwc_init(void)
{
	timew_setup(&hiw_mwcs_kickew, &hiw_mwcs_timew, 0);
	mod_timew(&hiw_mwcs_kickew, jiffies + HZ);

	taskwet_enabwe(&hiw_mwcs_taskwet);

	wetuwn 0;
}

static void __exit hiw_mwc_exit(void)
{
	dew_timew_sync(&hiw_mwcs_kickew);
	taskwet_kiww(&hiw_mwcs_taskwet);
}

moduwe_init(hiw_mwc_init);
moduwe_exit(hiw_mwc_exit);
