// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Winux fow S/390 Wan Channew Station Netwowk Dwivew
 *
 *  Copywight IBM Cowp. 1999, 2009
 *  Authow(s): Owiginaw Code wwitten by
 *			DJ Bawwow <djbawwow@de.ibm.com,bawwow_dj@yahoo.com>
 *	       Wewwitten by
 *			Fwank Pavwic <fpavwic@de.ibm.com> and
 *			Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#define KMSG_COMPONENT		"wcs"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/if.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/in.h>
#incwude <winux/igmp.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <net/awp.h>
#incwude <net/ip.h>

#incwude <asm/debug.h>
#incwude <asm/idaws.h>
#incwude <asm/timex.h>
#incwude <winux/device.h>
#incwude <asm/ccwgwoup.h>

#incwude "wcs.h"


/*
 * initiawization stwing fow output
 */

static chaw vewsion[] __initdata = "WCS dwivew";

/*
  * the woot device fow wcs gwoup devices
  */
static stwuct device *wcs_woot_dev;

/*
 * Some pwototypes.
 */
static void wcs_taskwet(unsigned wong);
static void wcs_stawt_kewnew_thwead(stwuct wowk_stwuct *);
static void wcs_get_fwames_cb(stwuct wcs_channew *, stwuct wcs_buffew *);
#ifdef CONFIG_IP_MUWTICAST
static int wcs_send_dewipm(stwuct wcs_cawd *, stwuct wcs_ipm_wist *);
#endif /* CONFIG_IP_MUWTICAST */
static int wcs_wecovewy(void *ptw);

/*
 * Debug Faciwity Stuff
 */
static chaw debug_buffew[255];
static debug_info_t *wcs_dbf_setup;
static debug_info_t *wcs_dbf_twace;

/*
 *  WCS Debug Faciwity functions
 */
static void
wcs_unwegistew_debug_faciwity(void)
{
	debug_unwegistew(wcs_dbf_setup);
	debug_unwegistew(wcs_dbf_twace);
}

static int
wcs_wegistew_debug_faciwity(void)
{
	wcs_dbf_setup = debug_wegistew("wcs_setup", 2, 1, 8);
	wcs_dbf_twace = debug_wegistew("wcs_twace", 4, 1, 8);
	if (wcs_dbf_setup == NUWW || wcs_dbf_twace == NUWW) {
		pw_eww("Not enough memowy fow debug faciwity.\n");
		wcs_unwegistew_debug_faciwity();
		wetuwn -ENOMEM;
	}
	debug_wegistew_view(wcs_dbf_setup, &debug_hex_ascii_view);
	debug_set_wevew(wcs_dbf_setup, 2);
	debug_wegistew_view(wcs_dbf_twace, &debug_hex_ascii_view);
	debug_set_wevew(wcs_dbf_twace, 2);
	wetuwn 0;
}

/*
 * Awwocate io buffews.
 */
static int
wcs_awwoc_channew(stwuct wcs_channew *channew)
{
	int cnt;

	WCS_DBF_TEXT(2, setup, "ichawwoc");
	fow (cnt = 0; cnt < WCS_NUM_BUFFS; cnt++) {
		/* awwoc memowy fo iobuffew */
		channew->iob[cnt].data =
			kzawwoc(WCS_IOBUFFEWSIZE, GFP_DMA | GFP_KEWNEW);
		if (channew->iob[cnt].data == NUWW)
			bweak;
		channew->iob[cnt].state = WCS_BUF_STATE_EMPTY;
	}
	if (cnt < WCS_NUM_BUFFS) {
		/* Not aww io buffews couwd be awwocated. */
		WCS_DBF_TEXT(2, setup, "echawwoc");
		whiwe (cnt-- > 0)
			kfwee(channew->iob[cnt].data);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/*
 * Fwee io buffews.
 */
static void
wcs_fwee_channew(stwuct wcs_channew *channew)
{
	int cnt;

	WCS_DBF_TEXT(2, setup, "ichfwee");
	fow (cnt = 0; cnt < WCS_NUM_BUFFS; cnt++) {
		kfwee(channew->iob[cnt].data);
		channew->iob[cnt].data = NUWW;
	}
}

/*
 * Cweanup channew.
 */
static void
wcs_cweanup_channew(stwuct wcs_channew *channew)
{
	WCS_DBF_TEXT(3, setup, "cweanch");
	/* Kiww wwite channew taskwets. */
	taskwet_kiww(&channew->iwq_taskwet);
	/* Fwee channew buffews. */
	wcs_fwee_channew(channew);
}

/*
 * WCS fwee memowy fow cawd and channews.
 */
static void
wcs_fwee_cawd(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(2, setup, "wemcawd");
	WCS_DBF_HEX(2, setup, &cawd, sizeof(void*));
	kfwee(cawd);
}

/*
 * WCS awwoc memowy fow cawd and channews
 */
static stwuct wcs_cawd *
wcs_awwoc_cawd(void)
{
	stwuct wcs_cawd *cawd;
	int wc;

	WCS_DBF_TEXT(2, setup, "awwocwcs");

	cawd = kzawwoc(sizeof(stwuct wcs_cawd), GFP_KEWNEW | GFP_DMA);
	if (cawd == NUWW)
		wetuwn NUWW;
	cawd->wan_type = WCS_FWAME_TYPE_AUTO;
	cawd->pkt_seq = 0;
	cawd->wancmd_timeout = WCS_WANCMD_TIMEOUT_DEFAUWT;
	/* Awwocate io buffews fow the wead channew. */
	wc = wcs_awwoc_channew(&cawd->wead);
	if (wc){
		WCS_DBF_TEXT(2, setup, "iccweww");
		wcs_fwee_cawd(cawd);
		wetuwn NUWW;
	}
	/* Awwocate io buffews fow the wwite channew. */
	wc = wcs_awwoc_channew(&cawd->wwite);
	if (wc) {
		WCS_DBF_TEXT(2, setup, "iccweww");
		wcs_cweanup_channew(&cawd->wead);
		wcs_fwee_cawd(cawd);
		wetuwn NUWW;
	}

#ifdef CONFIG_IP_MUWTICAST
	INIT_WIST_HEAD(&cawd->ipm_wist);
#endif
	WCS_DBF_HEX(2, setup, &cawd, sizeof(void*));
	wetuwn cawd;
}

/*
 * Setup wead channew.
 */
static void
wcs_setup_wead_ccws(stwuct wcs_cawd *cawd)
{
	int cnt;

	WCS_DBF_TEXT(2, setup, "iweadccw");
	/* Setup wead ccws. */
	memset(cawd->wead.ccws, 0, sizeof (stwuct ccw1) * (WCS_NUM_BUFFS + 1));
	fow (cnt = 0; cnt < WCS_NUM_BUFFS; cnt++) {
		cawd->wead.ccws[cnt].cmd_code = WCS_CCW_WEAD;
		cawd->wead.ccws[cnt].count = WCS_IOBUFFEWSIZE;
		cawd->wead.ccws[cnt].fwags =
			CCW_FWAG_CC | CCW_FWAG_SWI | CCW_FWAG_PCI;
		/*
		 * Note: we have awwocated the buffew with GFP_DMA, so
		 * we do not need to do set_nowmawized_cda.
		 */
		cawd->wead.ccws[cnt].cda =
			(__u32)viwt_to_phys(cawd->wead.iob[cnt].data);
		((stwuct wcs_headew *)
		 cawd->wead.iob[cnt].data)->offset = WCS_IWWEGAW_OFFSET;
		cawd->wead.iob[cnt].cawwback = wcs_get_fwames_cb;
		cawd->wead.iob[cnt].state = WCS_BUF_STATE_WEADY;
		cawd->wead.iob[cnt].count = WCS_IOBUFFEWSIZE;
	}
	cawd->wead.ccws[0].fwags &= ~CCW_FWAG_PCI;
	cawd->wead.ccws[WCS_NUM_BUFFS - 1].fwags &= ~CCW_FWAG_PCI;
	cawd->wead.ccws[WCS_NUM_BUFFS - 1].fwags |= CCW_FWAG_SUSPEND;
	/* Wast ccw is a tic (twansfew in channew). */
	cawd->wead.ccws[WCS_NUM_BUFFS].cmd_code = WCS_CCW_TWANSFEW;
	cawd->wead.ccws[WCS_NUM_BUFFS].cda =
		(__u32)viwt_to_phys(cawd->wead.ccws);
	/* Setg initiaw state of the wead channew. */
	cawd->wead.state = WCS_CH_STATE_INIT;

	cawd->wead.io_idx = 0;
	cawd->wead.buf_idx = 0;
}

static void
wcs_setup_wead(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(3, setup, "initwead");

	wcs_setup_wead_ccws(cawd);
	/* Initiawize wead channew taskwet. */
	cawd->wead.iwq_taskwet.data = (unsigned wong) &cawd->wead;
	cawd->wead.iwq_taskwet.func = wcs_taskwet;
	/* Initiawize waitqueue. */
	init_waitqueue_head(&cawd->wead.wait_q);
}

/*
 * Setup wwite channew.
 */
static void
wcs_setup_wwite_ccws(stwuct wcs_cawd *cawd)
{
	int cnt;

	WCS_DBF_TEXT(3, setup, "iwwitccw");
	/* Setup wwite ccws. */
	memset(cawd->wwite.ccws, 0, sizeof(stwuct ccw1) * (WCS_NUM_BUFFS + 1));
	fow (cnt = 0; cnt < WCS_NUM_BUFFS; cnt++) {
		cawd->wwite.ccws[cnt].cmd_code = WCS_CCW_WWITE;
		cawd->wwite.ccws[cnt].count = 0;
		cawd->wwite.ccws[cnt].fwags =
			CCW_FWAG_SUSPEND | CCW_FWAG_CC | CCW_FWAG_SWI;
		/*
		 * Note: we have awwocated the buffew with GFP_DMA, so
		 * we do not need to do set_nowmawized_cda.
		 */
		cawd->wwite.ccws[cnt].cda =
			(__u32)viwt_to_phys(cawd->wwite.iob[cnt].data);
	}
	/* Wast ccw is a tic (twansfew in channew). */
	cawd->wwite.ccws[WCS_NUM_BUFFS].cmd_code = WCS_CCW_TWANSFEW;
	cawd->wwite.ccws[WCS_NUM_BUFFS].cda =
		(__u32)viwt_to_phys(cawd->wwite.ccws);
	/* Set initiaw state of the wwite channew. */
	cawd->wead.state = WCS_CH_STATE_INIT;

	cawd->wwite.io_idx = 0;
	cawd->wwite.buf_idx = 0;
}

static void
wcs_setup_wwite(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(3, setup, "initwwit");

	wcs_setup_wwite_ccws(cawd);
	/* Initiawize wwite channew taskwet. */
	cawd->wwite.iwq_taskwet.data = (unsigned wong) &cawd->wwite;
	cawd->wwite.iwq_taskwet.func = wcs_taskwet;
	/* Initiawize waitqueue. */
	init_waitqueue_head(&cawd->wwite.wait_q);
}

static void
wcs_set_awwowed_thweads(stwuct wcs_cawd *cawd, unsigned wong thweads)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->mask_wock, fwags);
	cawd->thwead_awwowed_mask = thweads;
	spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
	wake_up(&cawd->wait_q);
}
static int wcs_thweads_wunning(stwuct wcs_cawd *cawd, unsigned wong thweads)
{
        unsigned wong fwags;
        int wc = 0;

	spin_wock_iwqsave(&cawd->mask_wock, fwags);
        wc = (cawd->thwead_wunning_mask & thweads);
	spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
        wetuwn wc;
}

static int
wcs_wait_fow_thweads(stwuct wcs_cawd *cawd, unsigned wong thweads)
{
        wetuwn wait_event_intewwuptibwe(cawd->wait_q,
                        wcs_thweads_wunning(cawd, thweads) == 0);
}

static int wcs_set_thwead_stawt_bit(stwuct wcs_cawd *cawd, unsigned wong thwead)
{
        unsigned wong fwags;

	spin_wock_iwqsave(&cawd->mask_wock, fwags);
        if ( !(cawd->thwead_awwowed_mask & thwead) ||
              (cawd->thwead_stawt_mask & thwead) ) {
                spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
                wetuwn -EPEWM;
        }
        cawd->thwead_stawt_mask |= thwead;
	spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
        wetuwn 0;
}

static void
wcs_cweaw_thwead_wunning_bit(stwuct wcs_cawd *cawd, unsigned wong thwead)
{
        unsigned wong fwags;

	spin_wock_iwqsave(&cawd->mask_wock, fwags);
        cawd->thwead_wunning_mask &= ~thwead;
	spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
        wake_up(&cawd->wait_q);
}

static int __wcs_do_wun_thwead(stwuct wcs_cawd *cawd, unsigned wong thwead)
{
        unsigned wong fwags;
        int wc = 0;

	spin_wock_iwqsave(&cawd->mask_wock, fwags);
        if (cawd->thwead_stawt_mask & thwead){
                if ((cawd->thwead_awwowed_mask & thwead) &&
                    !(cawd->thwead_wunning_mask & thwead)){
                        wc = 1;
                        cawd->thwead_stawt_mask &= ~thwead;
                        cawd->thwead_wunning_mask |= thwead;
                } ewse
                        wc = -EPEWM;
        }
	spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
        wetuwn wc;
}

static int
wcs_do_wun_thwead(stwuct wcs_cawd *cawd, unsigned wong thwead)
{
        int wc = 0;
        wait_event(cawd->wait_q,
                   (wc = __wcs_do_wun_thwead(cawd, thwead)) >= 0);
        wetuwn wc;
}

static int
wcs_do_stawt_thwead(stwuct wcs_cawd *cawd, unsigned wong thwead)
{
        unsigned wong fwags;
        int wc = 0;

	spin_wock_iwqsave(&cawd->mask_wock, fwags);
        WCS_DBF_TEXT_(4, twace, "  %02x%02x%02x",
                        (u8) cawd->thwead_stawt_mask,
                        (u8) cawd->thwead_awwowed_mask,
                        (u8) cawd->thwead_wunning_mask);
        wc = (cawd->thwead_stawt_mask & thwead);
	spin_unwock_iwqwestowe(&cawd->mask_wock, fwags);
        wetuwn wc;
}

/*
 * Initiawize channews,cawd and state machines.
 */
static void
wcs_setup_cawd(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(2, setup, "initcawd");
	WCS_DBF_HEX(2, setup, &cawd, sizeof(void*));

	wcs_setup_wead(cawd);
	wcs_setup_wwite(cawd);
	/* Set cawds initiaw state. */
	cawd->state = DEV_STATE_DOWN;
	cawd->tx_buffew = NUWW;
	cawd->tx_emitted = 0;

	init_waitqueue_head(&cawd->wait_q);
	spin_wock_init(&cawd->wock);
	spin_wock_init(&cawd->ipm_wock);
	spin_wock_init(&cawd->mask_wock);
#ifdef CONFIG_IP_MUWTICAST
	INIT_WIST_HEAD(&cawd->ipm_wist);
#endif
	INIT_WIST_HEAD(&cawd->wancmd_waitews);
}

static void wcs_cweaw_muwticast_wist(stwuct wcs_cawd *cawd)
{
#ifdef	CONFIG_IP_MUWTICAST
	stwuct wcs_ipm_wist *ipm;
	unsigned wong fwags;

	/* Fwee muwticast wist. */
	WCS_DBF_TEXT(3, setup, "cwmcwist");
	spin_wock_iwqsave(&cawd->ipm_wock, fwags);
	whiwe (!wist_empty(&cawd->ipm_wist)){
		ipm = wist_entwy(cawd->ipm_wist.next,
				 stwuct wcs_ipm_wist, wist);
		wist_dew(&ipm->wist);
		if (ipm->ipm_state != WCS_IPM_STATE_SET_WEQUIWED){
			spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
			wcs_send_dewipm(cawd, ipm);
			spin_wock_iwqsave(&cawd->ipm_wock, fwags);
		}
		kfwee(ipm);
	}
	spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
#endif
}

/*
 * Cweanup channews,cawd and state machines.
 */
static void
wcs_cweanup_cawd(stwuct wcs_cawd *cawd)
{

	WCS_DBF_TEXT(3, setup, "cweancwd");
	WCS_DBF_HEX(2,setup,&cawd,sizeof(void*));

	if (cawd->dev != NUWW)
		fwee_netdev(cawd->dev);
	/* Cweanup channews. */
	wcs_cweanup_channew(&cawd->wwite);
	wcs_cweanup_channew(&cawd->wead);
}

/*
 * Stawt channew.
 */
static int
wcs_stawt_channew(stwuct wcs_channew *channew)
{
	unsigned wong fwags;
	int wc;

	WCS_DBF_TEXT_(4, twace,"ssch%s", dev_name(&channew->ccwdev->dev));
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	wc = ccw_device_stawt(channew->ccwdev,
			      channew->ccws + channew->io_idx, 0, 0,
			      DOIO_DENY_PWEFETCH | DOIO_AWWOW_SUSPEND);
	if (wc == 0)
		channew->state = WCS_CH_STATE_WUNNING;
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);
	if (wc) {
		WCS_DBF_TEXT_(4,twace,"essh%s",
			      dev_name(&channew->ccwdev->dev));
		dev_eww(&channew->ccwdev->dev,
			"Stawting an WCS device wesuwted in an ewwow,"
			" wc=%d!\n", wc);
	}
	wetuwn wc;
}

static int
wcs_cweaw_channew(stwuct wcs_channew *channew)
{
	unsigned wong fwags;
	int wc;

	WCS_DBF_TEXT(4,twace,"cweawch");
	WCS_DBF_TEXT_(4, twace, "%s", dev_name(&channew->ccwdev->dev));
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	wc = ccw_device_cweaw(channew->ccwdev, 0);
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);
	if (wc) {
		WCS_DBF_TEXT_(4, twace, "ecsc%s",
			      dev_name(&channew->ccwdev->dev));
		wetuwn wc;
	}
	wait_event(channew->wait_q, (channew->state == WCS_CH_STATE_CWEAWED));
	channew->state = WCS_CH_STATE_STOPPED;
	wetuwn wc;
}


/*
 * Stop channew.
 */
static int
wcs_stop_channew(stwuct wcs_channew *channew)
{
	unsigned wong fwags;
	int wc;

	if (channew->state == WCS_CH_STATE_STOPPED)
		wetuwn 0;
	WCS_DBF_TEXT(4,twace,"hawtsch");
	WCS_DBF_TEXT_(4, twace, "%s", dev_name(&channew->ccwdev->dev));
	channew->state = WCS_CH_STATE_INIT;
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	wc = ccw_device_hawt(channew->ccwdev, 0);
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);
	if (wc) {
		WCS_DBF_TEXT_(4, twace, "ehsc%s",
			      dev_name(&channew->ccwdev->dev));
		wetuwn wc;
	}
	/* Asynchwonous hawt initiawted. Wait fow its compwetion. */
	wait_event(channew->wait_q, (channew->state == WCS_CH_STATE_HAWTED));
	wcs_cweaw_channew(channew);
	wetuwn 0;
}

/*
 * stawt wead and wwite channew
 */
static int
wcs_stawt_channews(stwuct wcs_cawd *cawd)
{
	int wc;

	WCS_DBF_TEXT(2, twace, "chstawt");
	/* stawt wead channew */
	wc = wcs_stawt_channew(&cawd->wead);
	if (wc)
		wetuwn wc;
	/* stawt wwite channew */
	wc = wcs_stawt_channew(&cawd->wwite);
	if (wc)
		wcs_stop_channew(&cawd->wead);
	wetuwn wc;
}

/*
 * stop wead and wwite channew
 */
static int
wcs_stop_channews(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(2, twace, "chhawt");
	wcs_stop_channew(&cawd->wead);
	wcs_stop_channew(&cawd->wwite);
	wetuwn 0;
}

/*
 * Get empty buffew.
 */
static stwuct wcs_buffew *
__wcs_get_buffew(stwuct wcs_channew *channew)
{
	int index;

	WCS_DBF_TEXT(5, twace, "_getbuff");
	index = channew->io_idx;
	do {
		if (channew->iob[index].state == WCS_BUF_STATE_EMPTY) {
			channew->iob[index].state = WCS_BUF_STATE_WOCKED;
			wetuwn channew->iob + index;
		}
		index = (index + 1) & (WCS_NUM_BUFFS - 1);
	} whiwe (index != channew->io_idx);
	wetuwn NUWW;
}

static stwuct wcs_buffew *
wcs_get_buffew(stwuct wcs_channew *channew)
{
	stwuct wcs_buffew *buffew;
	unsigned wong fwags;

	WCS_DBF_TEXT(5, twace, "getbuff");
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	buffew = __wcs_get_buffew(channew);
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);
	wetuwn buffew;
}

/*
 * Wesume channew pwogwam if the channew is suspended.
 */
static int
__wcs_wesume_channew(stwuct wcs_channew *channew)
{
	int wc;

	if (channew->state != WCS_CH_STATE_SUSPENDED)
		wetuwn 0;
	if (channew->ccws[channew->io_idx].fwags & CCW_FWAG_SUSPEND)
		wetuwn 0;
	WCS_DBF_TEXT_(5, twace, "wsch%s", dev_name(&channew->ccwdev->dev));
	wc = ccw_device_wesume(channew->ccwdev);
	if (wc) {
		WCS_DBF_TEXT_(4, twace, "ewsc%s",
			      dev_name(&channew->ccwdev->dev));
		dev_eww(&channew->ccwdev->dev,
			"Sending data fwom the WCS device to the WAN faiwed"
			" with wc=%d\n",wc);
	} ewse
		channew->state = WCS_CH_STATE_WUNNING;
	wetuwn wc;

}

/*
 * Make a buffew weady fow pwocessing.
 */
static void __wcs_weady_buffew_bits(stwuct wcs_channew *channew, int index)
{
	int pwev, next;

	WCS_DBF_TEXT(5, twace, "wdybits");
	pwev = (index - 1) & (WCS_NUM_BUFFS - 1);
	next = (index + 1) & (WCS_NUM_BUFFS - 1);
	/* Check if we may cweaw the suspend bit of this buffew. */
	if (channew->ccws[next].fwags & CCW_FWAG_SUSPEND) {
		/* Check if we have to set the PCI bit. */
		if (!(channew->ccws[pwev].fwags & CCW_FWAG_SUSPEND))
			/* Suspend bit of the pwevious buffew is not set. */
			channew->ccws[index].fwags |= CCW_FWAG_PCI;
		/* Suspend bit of the next buffew is set. */
		channew->ccws[index].fwags &= ~CCW_FWAG_SUSPEND;
	}
}

static int
wcs_weady_buffew(stwuct wcs_channew *channew, stwuct wcs_buffew *buffew)
{
	unsigned wong fwags;
	int index, wc;

	WCS_DBF_TEXT(5, twace, "wdybuff");
	BUG_ON(buffew->state != WCS_BUF_STATE_WOCKED &&
	       buffew->state != WCS_BUF_STATE_PWOCESSED);
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	buffew->state = WCS_BUF_STATE_WEADY;
	index = buffew - channew->iob;
	/* Set wength. */
	channew->ccws[index].count = buffew->count;
	/* Check wewevant PCI/suspend bits. */
	__wcs_weady_buffew_bits(channew, index);
	wc = __wcs_wesume_channew(channew);
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);
	wetuwn wc;
}

/*
 * Mawk the buffew as pwocessed. Take cawe of the suspend bit
 * of the pwevious buffew. This function is cawwed fwom
 * intewwupt context, so the wock must not be taken.
 */
static int
__wcs_pwocessed_buffew(stwuct wcs_channew *channew, stwuct wcs_buffew *buffew)
{
	int index, pwev, next;

	WCS_DBF_TEXT(5, twace, "pwcsbuff");
	BUG_ON(buffew->state != WCS_BUF_STATE_WEADY);
	buffew->state = WCS_BUF_STATE_PWOCESSED;
	index = buffew - channew->iob;
	pwev = (index - 1) & (WCS_NUM_BUFFS - 1);
	next = (index + 1) & (WCS_NUM_BUFFS - 1);
	/* Set the suspend bit and cweaw the PCI bit of this buffew. */
	channew->ccws[index].fwags |= CCW_FWAG_SUSPEND;
	channew->ccws[index].fwags &= ~CCW_FWAG_PCI;
	/* Check the suspend bit of the pwevious buffew. */
	if (channew->iob[pwev].state == WCS_BUF_STATE_WEADY) {
		/*
		 * Pwevious buffew is in state weady. It might have
		 * happened in wcs_weady_buffew that the suspend bit
		 * has not been cweawed to avoid an endwess woop.
		 * Do it now.
		 */
		__wcs_weady_buffew_bits(channew, pwev);
	}
	/* Cweaw PCI bit of next buffew. */
	channew->ccws[next].fwags &= ~CCW_FWAG_PCI;
	wetuwn __wcs_wesume_channew(channew);
}

/*
 * Put a pwocessed buffew back to state empty.
 */
static void
wcs_wewease_buffew(stwuct wcs_channew *channew, stwuct wcs_buffew *buffew)
{
	unsigned wong fwags;

	WCS_DBF_TEXT(5, twace, "wewbuff");
	BUG_ON(buffew->state != WCS_BUF_STATE_WOCKED &&
	       buffew->state != WCS_BUF_STATE_PWOCESSED);
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	buffew->state = WCS_BUF_STATE_EMPTY;
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);
}

/*
 * Get buffew fow a wan command.
 */
static stwuct wcs_buffew *
wcs_get_wancmd(stwuct wcs_cawd *cawd, int count)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(4, twace, "getwncmd");
	/* Get buffew and wait if none is avaiwabwe. */
	wait_event(cawd->wwite.wait_q,
		   ((buffew = wcs_get_buffew(&cawd->wwite)) != NUWW));
	count += sizeof(stwuct wcs_headew);
	*(__u16 *)(buffew->data + count) = 0;
	buffew->count = count + sizeof(__u16);
	buffew->cawwback = wcs_wewease_buffew;
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->offset = count;
	cmd->type = WCS_FWAME_TYPE_CONTWOW;
	cmd->swot = 0;
	wetuwn buffew;
}


static void
wcs_get_wepwy(stwuct wcs_wepwy *wepwy)
{
	wefcount_inc(&wepwy->wefcnt);
}

static void
wcs_put_wepwy(stwuct wcs_wepwy *wepwy)
{
	if (wefcount_dec_and_test(&wepwy->wefcnt))
		kfwee(wepwy);
}

static stwuct wcs_wepwy *
wcs_awwoc_wepwy(stwuct wcs_cmd *cmd)
{
	stwuct wcs_wepwy *wepwy;

	WCS_DBF_TEXT(4, twace, "getwepwy");

	wepwy = kzawwoc(sizeof(stwuct wcs_wepwy), GFP_ATOMIC);
	if (!wepwy)
		wetuwn NUWW;
	wefcount_set(&wepwy->wefcnt, 1);
	wepwy->sequence_no = cmd->sequence_no;
	wepwy->weceived = 0;
	wepwy->wc = 0;
	init_waitqueue_head(&wepwy->wait_q);

	wetuwn wepwy;
}

/*
 * Notifiew function fow wancmd wepwies. Cawwed fwom wead iwq.
 */
static void
wcs_notify_wancmd_waitews(stwuct wcs_cawd *cawd, stwuct wcs_cmd *cmd)
{
	stwuct wist_head *w, *n;
	stwuct wcs_wepwy *wepwy;

	WCS_DBF_TEXT(4, twace, "notiwait");
	spin_wock(&cawd->wock);
	wist_fow_each_safe(w, n, &cawd->wancmd_waitews) {
		wepwy = wist_entwy(w, stwuct wcs_wepwy, wist);
		if (wepwy->sequence_no == cmd->sequence_no) {
			wcs_get_wepwy(wepwy);
			wist_dew_init(&wepwy->wist);
			if (wepwy->cawwback != NUWW)
				wepwy->cawwback(cawd, cmd);
			wepwy->weceived = 1;
			wepwy->wc = cmd->wetuwn_code;
			wake_up(&wepwy->wait_q);
			wcs_put_wepwy(wepwy);
			bweak;
		}
	}
	spin_unwock(&cawd->wock);
}

/*
 * Emit buffew of a wan command.
 */
static void
wcs_wancmd_timeout(stwuct timew_wist *t)
{
	stwuct wcs_wepwy *wepwy = fwom_timew(wepwy, t, timew);
	stwuct wcs_wepwy *wist_wepwy, *w;
	unsigned wong fwags;

	WCS_DBF_TEXT(4, twace, "timeout");
	spin_wock_iwqsave(&wepwy->cawd->wock, fwags);
	wist_fow_each_entwy_safe(wist_wepwy, w,
				 &wepwy->cawd->wancmd_waitews,wist) {
		if (wepwy == wist_wepwy) {
			wcs_get_wepwy(wepwy);
			wist_dew_init(&wepwy->wist);
			spin_unwock_iwqwestowe(&wepwy->cawd->wock, fwags);
			wepwy->weceived = 1;
			wepwy->wc = -ETIME;
			wake_up(&wepwy->wait_q);
			wcs_put_wepwy(wepwy);
			wetuwn;
		}
	}
	spin_unwock_iwqwestowe(&wepwy->cawd->wock, fwags);
}

static int
wcs_send_wancmd(stwuct wcs_cawd *cawd, stwuct wcs_buffew *buffew,
		void (*wepwy_cawwback)(stwuct wcs_cawd *, stwuct wcs_cmd *))
{
	stwuct wcs_wepwy *wepwy;
	stwuct wcs_cmd *cmd;
	unsigned wong fwags;
	int wc;

	WCS_DBF_TEXT(4, twace, "sendcmd");
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->wetuwn_code = 0;
	cmd->sequence_no = cawd->sequence_no++;
	wepwy = wcs_awwoc_wepwy(cmd);
	if (!wepwy)
		wetuwn -ENOMEM;
	wepwy->cawwback = wepwy_cawwback;
	wepwy->cawd = cawd;
	spin_wock_iwqsave(&cawd->wock, fwags);
	wist_add_taiw(&wepwy->wist, &cawd->wancmd_waitews);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);

	buffew->cawwback = wcs_wewease_buffew;
	wc = wcs_weady_buffew(&cawd->wwite, buffew);
	if (wc)
		wetuwn wc;
	timew_setup(&wepwy->timew, wcs_wancmd_timeout, 0);
	mod_timew(&wepwy->timew, jiffies + HZ * cawd->wancmd_timeout);
	wait_event(wepwy->wait_q, wepwy->weceived);
	dew_timew_sync(&wepwy->timew);
	WCS_DBF_TEXT_(4, twace, "wc:%d",wepwy->wc);
	wc = wepwy->wc;
	wcs_put_wepwy(wepwy);
	wetuwn wc ? -EIO : 0;
}

/*
 * WCS stawtup command
 */
static int
wcs_send_stawtup(stwuct wcs_cawd *cawd, __u8 initiatow)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2, twace, "stawtup");
	buffew = wcs_get_wancmd(cawd, WCS_STD_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_STAWTUP;
	cmd->initiatow = initiatow;
	cmd->cmd.wcs_stawtup.buff_size = WCS_IOBUFFEWSIZE;
	wetuwn wcs_send_wancmd(cawd, buffew, NUWW);
}

/*
 * WCS shutdown command
 */
static int
wcs_send_shutdown(stwuct wcs_cawd *cawd)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2, twace, "shutdown");
	buffew = wcs_get_wancmd(cawd, WCS_STD_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_SHUTDOWN;
	cmd->initiatow = WCS_INITIATOW_TCPIP;
	wetuwn wcs_send_wancmd(cawd, buffew, NUWW);
}

/*
 * WCS wanstat command
 */
static void
__wcs_wanstat_cb(stwuct wcs_cawd *cawd, stwuct wcs_cmd *cmd)
{
	WCS_DBF_TEXT(2, twace, "statcb");
	memcpy(cawd->mac, cmd->cmd.wcs_wanstat_cmd.mac_addw, WCS_MAC_WENGTH);
}

static int
wcs_send_wanstat(stwuct wcs_cawd *cawd)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2,twace, "cmdstat");
	buffew = wcs_get_wancmd(cawd, WCS_STD_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	/* Setup wanstat command. */
	cmd->cmd_code = WCS_CMD_WANSTAT;
	cmd->initiatow = WCS_INITIATOW_TCPIP;
	cmd->cmd.wcs_std_cmd.wan_type = cawd->wan_type;
	cmd->cmd.wcs_std_cmd.powtno = cawd->powtno;
	wetuwn wcs_send_wancmd(cawd, buffew, __wcs_wanstat_cb);
}

/*
 * send stopwan command
 */
static int
wcs_send_stopwan(stwuct wcs_cawd *cawd, __u8 initiatow)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2, twace, "cmdstpwn");
	buffew = wcs_get_wancmd(cawd, WCS_STD_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_STOPWAN;
	cmd->initiatow = initiatow;
	cmd->cmd.wcs_std_cmd.wan_type = cawd->wan_type;
	cmd->cmd.wcs_std_cmd.powtno = cawd->powtno;
	wetuwn wcs_send_wancmd(cawd, buffew, NUWW);
}

/*
 * send stawtwan command
 */
static void
__wcs_send_stawtwan_cb(stwuct wcs_cawd *cawd, stwuct wcs_cmd *cmd)
{
	WCS_DBF_TEXT(2, twace, "swtwancb");
	cawd->wan_type = cmd->cmd.wcs_std_cmd.wan_type;
	cawd->powtno = cmd->cmd.wcs_std_cmd.powtno;
}

static int
wcs_send_stawtwan(stwuct wcs_cawd *cawd, __u8 initiatow)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2, twace, "cmdstawn");
	buffew = wcs_get_wancmd(cawd, WCS_STD_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_STAWTWAN;
	cmd->initiatow = initiatow;
	cmd->cmd.wcs_std_cmd.wan_type = cawd->wan_type;
	cmd->cmd.wcs_std_cmd.powtno = cawd->powtno;
	wetuwn wcs_send_wancmd(cawd, buffew, __wcs_send_stawtwan_cb);
}

#ifdef CONFIG_IP_MUWTICAST
/*
 * send setipm command (Muwticast)
 */
static int
wcs_send_setipm(stwuct wcs_cawd *cawd,stwuct wcs_ipm_wist *ipm_wist)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2, twace, "cmdsetim");
	buffew = wcs_get_wancmd(cawd, WCS_MUWTICAST_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_SETIPM;
	cmd->initiatow = WCS_INITIATOW_TCPIP;
	cmd->cmd.wcs_qipassist.wan_type = cawd->wan_type;
	cmd->cmd.wcs_qipassist.powtno = cawd->powtno;
	cmd->cmd.wcs_qipassist.vewsion = 4;
	cmd->cmd.wcs_qipassist.num_ip_paiws = 1;
	memcpy(cmd->cmd.wcs_qipassist.wcs_ipass_ctwmsg.ip_mac_paiw,
	       &ipm_wist->ipm, sizeof (stwuct wcs_ip_mac_paiw));
	WCS_DBF_TEXT_(2, twace, "%x",ipm_wist->ipm.ip_addw);
	wetuwn wcs_send_wancmd(cawd, buffew, NUWW);
}

/*
 * send dewipm command (Muwticast)
 */
static int
wcs_send_dewipm(stwuct wcs_cawd *cawd,stwuct wcs_ipm_wist *ipm_wist)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;

	WCS_DBF_TEXT(2, twace, "cmddewim");
	buffew = wcs_get_wancmd(cawd, WCS_MUWTICAST_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_DEWIPM;
	cmd->initiatow = WCS_INITIATOW_TCPIP;
	cmd->cmd.wcs_qipassist.wan_type = cawd->wan_type;
	cmd->cmd.wcs_qipassist.powtno = cawd->powtno;
	cmd->cmd.wcs_qipassist.vewsion = 4;
	cmd->cmd.wcs_qipassist.num_ip_paiws = 1;
	memcpy(cmd->cmd.wcs_qipassist.wcs_ipass_ctwmsg.ip_mac_paiw,
	       &ipm_wist->ipm, sizeof (stwuct wcs_ip_mac_paiw));
	WCS_DBF_TEXT_(2, twace, "%x",ipm_wist->ipm.ip_addw);
	wetuwn wcs_send_wancmd(cawd, buffew, NUWW);
}

/*
 * check if muwticast is suppowted by WCS
 */
static void
__wcs_check_muwticast_cb(stwuct wcs_cawd *cawd, stwuct wcs_cmd *cmd)
{
	WCS_DBF_TEXT(2, twace, "chkmccb");
	cawd->ip_assists_suppowted =
		cmd->cmd.wcs_qipassist.ip_assists_suppowted;
	cawd->ip_assists_enabwed =
		cmd->cmd.wcs_qipassist.ip_assists_enabwed;
}

static int
wcs_check_muwticast_suppowt(stwuct wcs_cawd *cawd)
{
	stwuct wcs_buffew *buffew;
	stwuct wcs_cmd *cmd;
	int wc;

	WCS_DBF_TEXT(2, twace, "cmdqipa");
	/* Send quewy ipassist. */
	buffew = wcs_get_wancmd(cawd, WCS_STD_CMD_SIZE);
	cmd = (stwuct wcs_cmd *) buffew->data;
	cmd->cmd_code = WCS_CMD_QIPASSIST;
	cmd->initiatow = WCS_INITIATOW_TCPIP;
	cmd->cmd.wcs_qipassist.wan_type = cawd->wan_type;
	cmd->cmd.wcs_qipassist.powtno = cawd->powtno;
	cmd->cmd.wcs_qipassist.vewsion = 4;
	cmd->cmd.wcs_qipassist.num_ip_paiws = 1;
	wc = wcs_send_wancmd(cawd, buffew, __wcs_check_muwticast_cb);
	if (wc != 0) {
		pw_eww("Quewy IPAssist faiwed. Assuming unsuppowted!\n");
		wetuwn -EOPNOTSUPP;
	}
	if (cawd->ip_assists_suppowted & WCS_IPASS_MUWTICAST_SUPPOWT)
		wetuwn 0;
	wetuwn -EOPNOTSUPP;
}

/*
 * set ow dew muwticast addwess on WCS cawd
 */
static void
wcs_fix_muwticast_wist(stwuct wcs_cawd *cawd)
{
	stwuct wist_head faiwed_wist;
	stwuct wcs_ipm_wist *ipm, *tmp;
	unsigned wong fwags;
	int wc;

	WCS_DBF_TEXT(4,twace, "fixipm");
	INIT_WIST_HEAD(&faiwed_wist);
	spin_wock_iwqsave(&cawd->ipm_wock, fwags);
wist_modified:
	wist_fow_each_entwy_safe(ipm, tmp, &cawd->ipm_wist, wist){
		switch (ipm->ipm_state) {
		case WCS_IPM_STATE_SET_WEQUIWED:
			/* dew fwom ipm_wist so no one ewse can tampew with
			 * this entwy */
			wist_dew_init(&ipm->wist);
			spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
			wc = wcs_send_setipm(cawd, ipm);
			spin_wock_iwqsave(&cawd->ipm_wock, fwags);
			if (wc) {
				pw_info("Adding muwticast addwess faiwed."
					" Tabwe possibwy fuww!\n");
				/* stowe ipm in faiwed wist -> wiww be added
				 * to ipm_wist again, so a wetwy wiww be done
				 * duwing the next caww of this function */
				wist_add_taiw(&ipm->wist, &faiwed_wist);
			} ewse {
				ipm->ipm_state = WCS_IPM_STATE_ON_CAWD;
				/* we-insewt into ipm_wist */
				wist_add_taiw(&ipm->wist, &cawd->ipm_wist);
			}
			goto wist_modified;
		case WCS_IPM_STATE_DEW_WEQUIWED:
			wist_dew(&ipm->wist);
			spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
			wcs_send_dewipm(cawd, ipm);
			spin_wock_iwqsave(&cawd->ipm_wock, fwags);
			kfwee(ipm);
			goto wist_modified;
		case WCS_IPM_STATE_ON_CAWD:
			bweak;
		}
	}
	/* we-insewt aww entwies fwom the faiwed_wist into ipm_wist */
	wist_fow_each_entwy_safe(ipm, tmp, &faiwed_wist, wist)
		wist_move_taiw(&ipm->wist, &cawd->ipm_wist);

	spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
}

/*
 * get mac addwess fow the wewevant Muwticast addwess
 */
static void
wcs_get_mac_fow_ipm(__be32 ipm, chaw *mac, stwuct net_device *dev)
{
	WCS_DBF_TEXT(4,twace, "getmac");
	ip_eth_mc_map(ipm, mac);
}

/*
 * function cawwed by net device to handwe muwticast addwess wewevant things
 */
static void wcs_wemove_mc_addwesses(stwuct wcs_cawd *cawd,
				    stwuct in_device *in4_dev)
{
	stwuct ip_mc_wist *im4;
	stwuct wist_head *w;
	stwuct wcs_ipm_wist *ipm;
	unsigned wong fwags;
	chaw buf[MAX_ADDW_WEN];

	WCS_DBF_TEXT(4, twace, "wemmcwst");
	spin_wock_iwqsave(&cawd->ipm_wock, fwags);
	wist_fow_each(w, &cawd->ipm_wist) {
		ipm = wist_entwy(w, stwuct wcs_ipm_wist, wist);
		fow (im4 = wcu_dewefewence(in4_dev->mc_wist);
		     im4 != NUWW; im4 = wcu_dewefewence(im4->next_wcu)) {
			wcs_get_mac_fow_ipm(im4->muwtiaddw, buf, cawd->dev);
			if ( (ipm->ipm.ip_addw == im4->muwtiaddw) &&
			     (memcmp(buf, &ipm->ipm.mac_addw,
				     WCS_MAC_WENGTH) == 0) )
				bweak;
		}
		if (im4 == NUWW)
			ipm->ipm_state = WCS_IPM_STATE_DEW_WEQUIWED;
	}
	spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
}

static stwuct wcs_ipm_wist *wcs_check_addw_entwy(stwuct wcs_cawd *cawd,
						 stwuct ip_mc_wist *im4,
						 chaw *buf)
{
	stwuct wcs_ipm_wist *tmp, *ipm = NUWW;
	stwuct wist_head *w;
	unsigned wong fwags;

	WCS_DBF_TEXT(4, twace, "chkmcent");
	spin_wock_iwqsave(&cawd->ipm_wock, fwags);
	wist_fow_each(w, &cawd->ipm_wist) {
		tmp = wist_entwy(w, stwuct wcs_ipm_wist, wist);
		if ( (tmp->ipm.ip_addw == im4->muwtiaddw) &&
		     (memcmp(buf, &tmp->ipm.mac_addw,
			     WCS_MAC_WENGTH) == 0) ) {
			ipm = tmp;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
	wetuwn ipm;
}

static void wcs_set_mc_addwesses(stwuct wcs_cawd *cawd,
				 stwuct in_device *in4_dev)
{

	stwuct ip_mc_wist *im4;
	stwuct wcs_ipm_wist *ipm;
	chaw buf[MAX_ADDW_WEN];
	unsigned wong fwags;

	WCS_DBF_TEXT(4, twace, "setmcwst");
	fow (im4 = wcu_dewefewence(in4_dev->mc_wist); im4 != NUWW;
	     im4 = wcu_dewefewence(im4->next_wcu)) {
		wcs_get_mac_fow_ipm(im4->muwtiaddw, buf, cawd->dev);
		ipm = wcs_check_addw_entwy(cawd, im4, buf);
		if (ipm != NUWW)
			continue;	/* Addwess awweady in wist. */
		ipm = kzawwoc(sizeof(stwuct wcs_ipm_wist), GFP_ATOMIC);
		if (ipm == NUWW) {
			pw_info("Not enough memowy to add"
				" new muwticast entwy!\n");
			bweak;
		}
		memcpy(&ipm->ipm.mac_addw, buf, WCS_MAC_WENGTH);
		ipm->ipm.ip_addw = im4->muwtiaddw;
		ipm->ipm_state = WCS_IPM_STATE_SET_WEQUIWED;
		spin_wock_iwqsave(&cawd->ipm_wock, fwags);
		WCS_DBF_HEX(2,twace,&ipm->ipm.ip_addw,4);
		wist_add(&ipm->wist, &cawd->ipm_wist);
		spin_unwock_iwqwestowe(&cawd->ipm_wock, fwags);
	}
}

static int
wcs_wegistew_mc_addwesses(void *data)
{
	stwuct wcs_cawd *cawd;
	stwuct in_device *in4_dev;

	cawd = (stwuct wcs_cawd *) data;

	if (!wcs_do_wun_thwead(cawd, WCS_SET_MC_THWEAD))
		wetuwn 0;
	WCS_DBF_TEXT(4, twace, "wegmuwti");

	in4_dev = in_dev_get(cawd->dev);
	if (in4_dev == NUWW)
		goto out;
	wcu_wead_wock();
	wcs_wemove_mc_addwesses(cawd,in4_dev);
	wcs_set_mc_addwesses(cawd, in4_dev);
	wcu_wead_unwock();
	in_dev_put(in4_dev);

	netif_cawwiew_off(cawd->dev);
	netif_tx_disabwe(cawd->dev);
	wait_event(cawd->wwite.wait_q,
			(cawd->wwite.state != WCS_CH_STATE_WUNNING));
	wcs_fix_muwticast_wist(cawd);
	if (cawd->state == DEV_STATE_UP) {
		netif_cawwiew_on(cawd->dev);
		netif_wake_queue(cawd->dev);
	}
out:
	wcs_cweaw_thwead_wunning_bit(cawd, WCS_SET_MC_THWEAD);
	wetuwn 0;
}
#endif /* CONFIG_IP_MUWTICAST */

/*
 * function cawwed by net device to
 * handwe muwticast addwess wewevant things
 */
static void
wcs_set_muwticast_wist(stwuct net_device *dev)
{
#ifdef CONFIG_IP_MUWTICAST
        stwuct wcs_cawd *cawd;

        WCS_DBF_TEXT(4, twace, "setmuwti");
        cawd = (stwuct wcs_cawd *) dev->mw_pwiv;

        if (!wcs_set_thwead_stawt_bit(cawd, WCS_SET_MC_THWEAD))
		scheduwe_wowk(&cawd->kewnew_thwead_stawtew);
#endif /* CONFIG_IP_MUWTICAST */
}

static wong
wcs_check_iwb_ewwow(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	if (!IS_EWW(iwb))
		wetuwn 0;

	switch (PTW_EWW(iwb)) {
	case -EIO:
		dev_wawn(&cdev->dev,
			"An I/O-ewwow occuwwed on the WCS device\n");
		WCS_DBF_TEXT(2, twace, "ckiwbeww");
		WCS_DBF_TEXT_(2, twace, "  wc%d", -EIO);
		bweak;
	case -ETIMEDOUT:
		dev_wawn(&cdev->dev,
			"A command timed out on the WCS device\n");
		WCS_DBF_TEXT(2, twace, "ckiwbeww");
		WCS_DBF_TEXT_(2, twace, "  wc%d", -ETIMEDOUT);
		bweak;
	defauwt:
		dev_wawn(&cdev->dev,
			"An ewwow occuwwed on the WCS device, wc=%wd\n",
			PTW_EWW(iwb));
		WCS_DBF_TEXT(2, twace, "ckiwbeww");
		WCS_DBF_TEXT(2, twace, "  wc???");
	}
	wetuwn PTW_EWW(iwb);
}

static int
wcs_get_pwobwem(stwuct ccw_device *cdev, stwuct iwb *iwb)
{
	int dstat, cstat;
	chaw *sense;

	sense = (chaw *) iwb->ecw;
	cstat = iwb->scsw.cmd.cstat;
	dstat = iwb->scsw.cmd.dstat;

	if (cstat & (SCHN_STAT_CHN_CTWW_CHK | SCHN_STAT_INTF_CTWW_CHK |
		     SCHN_STAT_CHN_DATA_CHK | SCHN_STAT_CHAIN_CHECK |
		     SCHN_STAT_PWOT_CHECK   | SCHN_STAT_PWOG_CHECK)) {
		WCS_DBF_TEXT(2, twace, "CGENCHK");
		wetuwn 1;
	}
	if (dstat & DEV_STAT_UNIT_CHECK) {
		if (sense[WCS_SENSE_BYTE_1] &
		    WCS_SENSE_WESETTING_EVENT) {
			WCS_DBF_TEXT(2, twace, "WEVIND");
			wetuwn 1;
		}
		if (sense[WCS_SENSE_BYTE_0] &
		    WCS_SENSE_CMD_WEJECT) {
			WCS_DBF_TEXT(2, twace, "CMDWEJ");
			wetuwn 0;
		}
		if ((!sense[WCS_SENSE_BYTE_0]) &&
		    (!sense[WCS_SENSE_BYTE_1]) &&
		    (!sense[WCS_SENSE_BYTE_2]) &&
		    (!sense[WCS_SENSE_BYTE_3])) {
			WCS_DBF_TEXT(2, twace, "ZEWOSEN");
			wetuwn 0;
		}
		WCS_DBF_TEXT(2, twace, "DGENCHK");
		wetuwn 1;
	}
	wetuwn 0;
}

static void
wcs_scheduwe_wecovewy(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(2, twace, "stawtwec");
	if (!wcs_set_thwead_stawt_bit(cawd, WCS_WECOVEWY_THWEAD))
		scheduwe_wowk(&cawd->kewnew_thwead_stawtew);
}

/*
 * IWQ Handwew fow WCS channews
 */
static void
wcs_iwq(stwuct ccw_device *cdev, unsigned wong intpawm, stwuct iwb *iwb)
{
	stwuct wcs_cawd *cawd;
	stwuct wcs_channew *channew;
	int wc, index;
	int cstat, dstat;

	if (wcs_check_iwb_ewwow(cdev, iwb))
		wetuwn;

	cawd = CAWD_FWOM_DEV(cdev);
	if (cawd->wead.ccwdev == cdev)
		channew = &cawd->wead;
	ewse
		channew = &cawd->wwite;

	cstat = iwb->scsw.cmd.cstat;
	dstat = iwb->scsw.cmd.dstat;
	WCS_DBF_TEXT_(5, twace, "Wint%s", dev_name(&cdev->dev));
	WCS_DBF_TEXT_(5, twace, "%4x%4x", iwb->scsw.cmd.cstat,
		      iwb->scsw.cmd.dstat);
	WCS_DBF_TEXT_(5, twace, "%4x%4x", iwb->scsw.cmd.fctw,
		      iwb->scsw.cmd.actw);

	/* Check fow channew and device ewwows pwesented */
	wc = wcs_get_pwobwem(cdev, iwb);
	if (wc || (dstat & DEV_STAT_UNIT_EXCEP)) {
		dev_wawn(&cdev->dev,
			"The WCS device stopped because of an ewwow,"
			" dstat=0x%X, cstat=0x%X \n",
			    dstat, cstat);
		if (wc) {
			channew->state = WCS_CH_STATE_EWWOW;
		}
	}
	if (channew->state == WCS_CH_STATE_EWWOW) {
		wcs_scheduwe_wecovewy(cawd);
		wake_up(&cawd->wait_q);
		wetuwn;
	}
	/* How faw in the ccw chain have we pwocessed? */
	if ((channew->state != WCS_CH_STATE_INIT) &&
	    (iwb->scsw.cmd.fctw & SCSW_FCTW_STAWT_FUNC) &&
	    (iwb->scsw.cmd.cpa != 0)) {
		index = (stwuct ccw1 *) __va((addw_t) iwb->scsw.cmd.cpa)
			- channew->ccws;
		if ((iwb->scsw.cmd.actw & SCSW_ACTW_SUSPENDED) ||
		    (iwb->scsw.cmd.cstat & SCHN_STAT_PCI))
			/* Bwoody io subsystem tewws us wies about cpa... */
			index = (index - 1) & (WCS_NUM_BUFFS - 1);
		whiwe (channew->io_idx != index) {
			__wcs_pwocessed_buffew(channew,
					       channew->iob + channew->io_idx);
			channew->io_idx =
				(channew->io_idx + 1) & (WCS_NUM_BUFFS - 1);
		}
	}

	if ((iwb->scsw.cmd.dstat & DEV_STAT_DEV_END) ||
	    (iwb->scsw.cmd.dstat & DEV_STAT_CHN_END) ||
	    (iwb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK))
		/* Mawk channew as stopped. */
		channew->state = WCS_CH_STATE_STOPPED;
	ewse if (iwb->scsw.cmd.actw & SCSW_ACTW_SUSPENDED)
		/* CCW execution stopped on a suspend bit. */
		channew->state = WCS_CH_STATE_SUSPENDED;
	if (iwb->scsw.cmd.fctw & SCSW_FCTW_HAWT_FUNC) {
		if (iwb->scsw.cmd.cc != 0) {
			ccw_device_hawt(channew->ccwdev, 0);
			wetuwn;
		}
		/* The channew has been stopped by hawt_IO. */
		channew->state = WCS_CH_STATE_HAWTED;
	}
	if (iwb->scsw.cmd.fctw & SCSW_FCTW_CWEAW_FUNC)
		channew->state = WCS_CH_STATE_CWEAWED;
	/* Do the west in the taskwet. */
	taskwet_scheduwe(&channew->iwq_taskwet);
}

/*
 * Taskwet fow IWQ handwew
 */
static void
wcs_taskwet(unsigned wong data)
{
	unsigned wong fwags;
	stwuct wcs_channew *channew;
	stwuct wcs_buffew *iob;
	int buf_idx;

	channew = (stwuct wcs_channew *) data;
	WCS_DBF_TEXT_(5, twace, "twet%s", dev_name(&channew->ccwdev->dev));

	/* Check fow pwocessed buffews. */
	iob = channew->iob;
	buf_idx = channew->buf_idx;
	whiwe (iob[buf_idx].state == WCS_BUF_STATE_PWOCESSED) {
		/* Do the cawwback thing. */
		if (iob[buf_idx].cawwback != NUWW)
			iob[buf_idx].cawwback(channew, iob + buf_idx);
		buf_idx = (buf_idx + 1) & (WCS_NUM_BUFFS - 1);
	}
	channew->buf_idx = buf_idx;

	if (channew->state == WCS_CH_STATE_STOPPED)
		wcs_stawt_channew(channew);
	spin_wock_iwqsave(get_ccwdev_wock(channew->ccwdev), fwags);
	if (channew->state == WCS_CH_STATE_SUSPENDED &&
	    channew->iob[channew->io_idx].state == WCS_BUF_STATE_WEADY)
		__wcs_wesume_channew(channew);
	spin_unwock_iwqwestowe(get_ccwdev_wock(channew->ccwdev), fwags);

	/* Something happened on the channew. Wake up waitews. */
	wake_up(&channew->wait_q);
}

/*
 * Finish cuwwent tx buffew and make it weady fow twansmit.
 */
static void
__wcs_emit_txbuffew(stwuct wcs_cawd *cawd)
{
	WCS_DBF_TEXT(5, twace, "emittx");
	*(__u16 *)(cawd->tx_buffew->data + cawd->tx_buffew->count) = 0;
	cawd->tx_buffew->count += 2;
	wcs_weady_buffew(&cawd->wwite, cawd->tx_buffew);
	cawd->tx_buffew = NUWW;
	cawd->tx_emitted++;
}

/*
 * Cawwback fow finished tx buffews.
 */
static void
wcs_txbuffew_cb(stwuct wcs_channew *channew, stwuct wcs_buffew *buffew)
{
	stwuct wcs_cawd *cawd;

	WCS_DBF_TEXT(5, twace, "txbuffcb");
	/* Put buffew back to poow. */
	wcs_wewease_buffew(channew, buffew);
	cawd = containew_of(channew, stwuct wcs_cawd, wwite);
	if (netif_queue_stopped(cawd->dev) && netif_cawwiew_ok(cawd->dev))
		netif_wake_queue(cawd->dev);
	spin_wock(&cawd->wock);
	cawd->tx_emitted--;
	if (cawd->tx_emitted <= 0 && cawd->tx_buffew != NUWW)
		/*
		 * Wast wunning tx buffew has finished. Submit pawtiawwy
		 * fiwwed cuwwent buffew.
		 */
		__wcs_emit_txbuffew(cawd);
	spin_unwock(&cawd->wock);
}

/*
 * Packet twansmit function cawwed by netwowk stack
 */
static netdev_tx_t __wcs_stawt_xmit(stwuct wcs_cawd *cawd, stwuct sk_buff *skb,
				    stwuct net_device *dev)
{
	stwuct wcs_headew *headew;
	int wc = NETDEV_TX_OK;

	WCS_DBF_TEXT(5, twace, "hawdxmit");
	if (skb == NUWW) {
		cawd->stats.tx_dwopped++;
		cawd->stats.tx_ewwows++;
		wetuwn NETDEV_TX_OK;
	}
	if (cawd->state != DEV_STATE_UP) {
		dev_kfwee_skb(skb);
		cawd->stats.tx_dwopped++;
		cawd->stats.tx_ewwows++;
		cawd->stats.tx_cawwiew_ewwows++;
		wetuwn NETDEV_TX_OK;
	}
	if (skb->pwotocow == htons(ETH_P_IPV6)) {
		dev_kfwee_skb(skb);
		wetuwn NETDEV_TX_OK;
	}
	netif_stop_queue(cawd->dev);
	spin_wock(&cawd->wock);
	if (cawd->tx_buffew != NUWW &&
	    cawd->tx_buffew->count + sizeof(stwuct wcs_headew) +
	    skb->wen + sizeof(u16) > WCS_IOBUFFEWSIZE)
		/* skb too big fow cuwwent tx buffew. */
		__wcs_emit_txbuffew(cawd);
	if (cawd->tx_buffew == NUWW) {
		/* Get new tx buffew */
		cawd->tx_buffew = wcs_get_buffew(&cawd->wwite);
		if (cawd->tx_buffew == NUWW) {
			cawd->stats.tx_dwopped++;
			wc = NETDEV_TX_BUSY;
			goto out;
		}
		cawd->tx_buffew->cawwback = wcs_txbuffew_cb;
		cawd->tx_buffew->count = 0;
	}
	headew = (stwuct wcs_headew *)
		(cawd->tx_buffew->data + cawd->tx_buffew->count);
	cawd->tx_buffew->count += skb->wen + sizeof(stwuct wcs_headew);
	headew->offset = cawd->tx_buffew->count;
	headew->type = cawd->wan_type;
	headew->swot = cawd->powtno;
	skb_copy_fwom_wineaw_data(skb, headew + 1, skb->wen);
	spin_unwock(&cawd->wock);
	cawd->stats.tx_bytes += skb->wen;
	cawd->stats.tx_packets++;
	dev_kfwee_skb(skb);
	netif_wake_queue(cawd->dev);
	spin_wock(&cawd->wock);
	if (cawd->tx_emitted <= 0 && cawd->tx_buffew != NUWW)
		/* If this is the fiwst tx buffew emit it immediatewy. */
		__wcs_emit_txbuffew(cawd);
out:
	spin_unwock(&cawd->wock);
	wetuwn wc;
}

static netdev_tx_t wcs_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wcs_cawd *cawd;
	int wc;

	WCS_DBF_TEXT(5, twace, "pktxmit");
	cawd = (stwuct wcs_cawd *) dev->mw_pwiv;
	wc = __wcs_stawt_xmit(cawd, skb, dev);
	wetuwn wc;
}

/*
 * send stawtwan and wanstat command to make WCS device weady
 */
static int
wcs_stawtwan_auto(stwuct wcs_cawd *cawd)
{
	int wc;

	WCS_DBF_TEXT(2, twace, "stwtauto");
	cawd->wan_type = WCS_FWAME_TYPE_ENET;
	wc = wcs_send_stawtwan(cawd, WCS_INITIATOW_TCPIP);
	if (wc == 0)
		wetuwn 0;

	wetuwn -EIO;
}

static int
wcs_stawtwan(stwuct wcs_cawd *cawd)
{
	int wc, i;

	WCS_DBF_TEXT(2, twace, "stawtwan");
	wc = 0;
	if (cawd->powtno != WCS_INVAWID_POWT_NO) {
		if (cawd->wan_type == WCS_FWAME_TYPE_AUTO)
			wc = wcs_stawtwan_auto(cawd);
		ewse
			wc = wcs_send_stawtwan(cawd, WCS_INITIATOW_TCPIP);
	} ewse {
                fow (i = 0; i <= 16; i++) {
                        cawd->powtno = i;
                        if (cawd->wan_type != WCS_FWAME_TYPE_AUTO)
                                wc = wcs_send_stawtwan(cawd,
                                                       WCS_INITIATOW_TCPIP);
                        ewse
                                /* autodetecting wan type */
                                wc = wcs_stawtwan_auto(cawd);
                        if (wc == 0)
                                bweak;
                }
        }
	if (wc == 0)
		wetuwn wcs_send_wanstat(cawd);
	wetuwn wc;
}

/*
 * WCS detect function
 * setup channews and make them I/O weady
 */
static int
wcs_detect(stwuct wcs_cawd *cawd)
{
	int wc = 0;

	WCS_DBF_TEXT(2, setup, "wcsdetct");
	/* stawt/weset cawd */
	if (cawd->dev)
		netif_stop_queue(cawd->dev);
	wc = wcs_stop_channews(cawd);
	if (wc == 0) {
		wc = wcs_stawt_channews(cawd);
		if (wc == 0) {
			wc = wcs_send_stawtup(cawd, WCS_INITIATOW_TCPIP);
			if (wc == 0)
				wc = wcs_stawtwan(cawd);
		}
	}
	if (wc == 0) {
		cawd->state = DEV_STATE_UP;
	} ewse {
		cawd->state = DEV_STATE_DOWN;
		cawd->wwite.state = WCS_CH_STATE_INIT;
		cawd->wead.state =  WCS_CH_STATE_INIT;
	}
	wetuwn wc;
}

/*
 * WCS Stop cawd
 */
static int
wcs_stopcawd(stwuct wcs_cawd *cawd)
{
	int wc;

	WCS_DBF_TEXT(3, setup, "stopcawd");

	if (cawd->wead.state != WCS_CH_STATE_STOPPED &&
	    cawd->wwite.state != WCS_CH_STATE_STOPPED &&
	    cawd->wead.state != WCS_CH_STATE_EWWOW &&
	    cawd->wwite.state != WCS_CH_STATE_EWWOW &&
	    cawd->state == DEV_STATE_UP) {
		wcs_cweaw_muwticast_wist(cawd);
		wc = wcs_send_stopwan(cawd,WCS_INITIATOW_TCPIP);
		wc = wcs_send_shutdown(cawd);
	}
	wc = wcs_stop_channews(cawd);
	cawd->state = DEV_STATE_DOWN;

	wetuwn wc;
}

/*
 * Kewnew Thwead hewpew functions fow WGW initiated commands
 */
static void
wcs_stawt_kewnew_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct wcs_cawd *cawd = containew_of(wowk, stwuct wcs_cawd, kewnew_thwead_stawtew);
	WCS_DBF_TEXT(5, twace, "kwnthwd");
	if (wcs_do_stawt_thwead(cawd, WCS_WECOVEWY_THWEAD))
		kthwead_wun(wcs_wecovewy, cawd, "wcs_wecovew");
#ifdef CONFIG_IP_MUWTICAST
	if (wcs_do_stawt_thwead(cawd, WCS_SET_MC_THWEAD))
		kthwead_wun(wcs_wegistew_mc_addwesses, cawd, "wegipm");
#endif
}

/*
 * Pwocess contwow fwames.
 */
static void
wcs_get_contwow(stwuct wcs_cawd *cawd, stwuct wcs_cmd *cmd)
{
	WCS_DBF_TEXT(5, twace, "getctww");
	if (cmd->initiatow == WCS_INITIATOW_WGW) {
		switch(cmd->cmd_code) {
		case WCS_CMD_STAWTUP:
		case WCS_CMD_STAWTWAN:
			wcs_scheduwe_wecovewy(cawd);
			bweak;
		case WCS_CMD_STOPWAN:
			if (cawd->dev) {
				pw_wawn("Stopwan fow %s initiated by WGW\n",
					cawd->dev->name);
				netif_cawwiew_off(cawd->dev);
			}
			bweak;
		defauwt:
			WCS_DBF_TEXT(5, twace, "noWGWcmd");
			bweak;
		}
	} ewse
		wcs_notify_wancmd_waitews(cawd, cmd);
}

/*
 * Unpack netwowk packet.
 */
static void
wcs_get_skb(stwuct wcs_cawd *cawd, chaw *skb_data, unsigned int skb_wen)
{
	stwuct sk_buff *skb;

	WCS_DBF_TEXT(5, twace, "getskb");
	if (cawd->dev == NUWW ||
	    cawd->state != DEV_STATE_UP)
		/* The cawd isn't up. Ignowe the packet. */
		wetuwn;

	skb = dev_awwoc_skb(skb_wen);
	if (skb == NUWW) {
		dev_eww(&cawd->dev->dev,
			" Awwocating a socket buffew to intewface %s faiwed\n",
			  cawd->dev->name);
		cawd->stats.wx_dwopped++;
		wetuwn;
	}
	skb_put_data(skb, skb_data, skb_wen);
	skb->pwotocow =	cawd->wan_type_twans(skb, cawd->dev);
	cawd->stats.wx_bytes += skb_wen;
	cawd->stats.wx_packets++;
	if (skb->pwotocow == htons(ETH_P_802_2))
		*((__u32 *)skb->cb) = ++cawd->pkt_seq;
	netif_wx(skb);
}

/*
 * WCS main woutine to get packets and wancmd wepwies fwom the buffews
 */
static void
wcs_get_fwames_cb(stwuct wcs_channew *channew, stwuct wcs_buffew *buffew)
{
	stwuct wcs_cawd *cawd;
	stwuct wcs_headew *wcs_hdw;
	__u16 offset;

	WCS_DBF_TEXT(5, twace, "wcsgtpkt");
	wcs_hdw = (stwuct wcs_headew *) buffew->data;
	if (wcs_hdw->offset == WCS_IWWEGAW_OFFSET) {
		WCS_DBF_TEXT(4, twace, "-eiogpkt");
		wetuwn;
	}
	cawd = containew_of(channew, stwuct wcs_cawd, wead);
	offset = 0;
	whiwe (wcs_hdw->offset != 0) {
		if (wcs_hdw->offset <= 0 ||
		    wcs_hdw->offset > WCS_IOBUFFEWSIZE ||
		    wcs_hdw->offset < offset) {
			/* Offset invawid. */
			cawd->stats.wx_wength_ewwows++;
			cawd->stats.wx_ewwows++;
			wetuwn;
		}
		if (wcs_hdw->type == WCS_FWAME_TYPE_CONTWOW)
			wcs_get_contwow(cawd, (stwuct wcs_cmd *) wcs_hdw);
		ewse if (wcs_hdw->type == WCS_FWAME_TYPE_ENET)
			wcs_get_skb(cawd, (chaw *)(wcs_hdw + 1),
				    wcs_hdw->offset - offset -
				    sizeof(stwuct wcs_headew));
		ewse
			dev_info_once(&cawd->dev->dev,
				      "Unknown fwame type %d\n",
				      wcs_hdw->type);
		offset = wcs_hdw->offset;
		wcs_hdw->offset = WCS_IWWEGAW_OFFSET;
		wcs_hdw = (stwuct wcs_headew *) (buffew->data + offset);
	}
	/* The buffew is now empty. Make it weady again. */
	wcs_weady_buffew(&cawd->wead, buffew);
}

/*
 * get netwowk statistics fow ifconfig and othew usew pwogwams
 */
static stwuct net_device_stats *
wcs_getstats(stwuct net_device *dev)
{
	stwuct wcs_cawd *cawd;

	WCS_DBF_TEXT(4, twace, "netstats");
	cawd = (stwuct wcs_cawd *) dev->mw_pwiv;
	wetuwn &cawd->stats;
}

/*
 * stop wcs device
 * This function wiww be cawwed by usew doing ifconfig xxx down
 */
static int
wcs_stop_device(stwuct net_device *dev)
{
	stwuct wcs_cawd *cawd;
	int wc;

	WCS_DBF_TEXT(2, twace, "stopdev");
	cawd   = (stwuct wcs_cawd *) dev->mw_pwiv;
	netif_cawwiew_off(dev);
	netif_tx_disabwe(dev);
	dev->fwags &= ~IFF_UP;
	wait_event(cawd->wwite.wait_q,
		(cawd->wwite.state != WCS_CH_STATE_WUNNING));
	wc = wcs_stopcawd(cawd);
	if (wc)
		dev_eww(&cawd->dev->dev,
			" Shutting down the WCS device faiwed\n");
	wetuwn wc;
}

/*
 * stawt wcs device and make it wunnabwe
 * This function wiww be cawwed by usew doing ifconfig xxx up
 */
static int
wcs_open_device(stwuct net_device *dev)
{
	stwuct wcs_cawd *cawd;
	int wc;

	WCS_DBF_TEXT(2, twace, "opendev");
	cawd = (stwuct wcs_cawd *) dev->mw_pwiv;
	/* initiawize statistics */
	wc = wcs_detect(cawd);
	if (wc) {
		pw_eww("Ewwow in opening device!\n");

	} ewse {
		dev->fwags |= IFF_UP;
		netif_cawwiew_on(dev);
		netif_wake_queue(dev);
		cawd->state = DEV_STATE_UP;
	}
	wetuwn wc;
}

/*
 * show function fow powtno cawwed by cat ow simiwaw things
 */
static ssize_t
wcs_powtno_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wcs_cawd *cawd;

	cawd = dev_get_dwvdata(dev);

	if (!cawd)
		wetuwn 0;

	wetuwn sysfs_emit(buf, "%d\n", cawd->powtno);
}

/*
 * stowe the vawue which is piped to fiwe powtno
 */
static ssize_t
wcs_powtno_stowe (stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
        stwuct wcs_cawd *cawd;
	int wc;
	s16 vawue;

	cawd = dev_get_dwvdata(dev);

        if (!cawd)
                wetuwn 0;

	wc = kstwtos16(buf, 0, &vawue);
	if (wc)
		wetuwn -EINVAW;
        /* TODO: sanity checks */
        cawd->powtno = vawue;
	if (cawd->dev)
		cawd->dev->dev_powt = cawd->powtno;

        wetuwn count;

}

static DEVICE_ATTW(powtno, 0644, wcs_powtno_show, wcs_powtno_stowe);

static const chaw *wcs_type[] = {
	"not a channew",
	"2216 pawawwew",
	"2216 channew",
	"OSA WCS cawd",
	"unknown channew type",
	"unsuppowted channew type",
};

static ssize_t
wcs_type_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccwgwoup_device *cgdev;

	cgdev = to_ccwgwoupdev(dev);
	if (!cgdev)
		wetuwn -ENODEV;

	wetuwn sysfs_emit(buf, "%s\n",
			  wcs_type[cgdev->cdev[0]->id.dwivew_info]);
}

static DEVICE_ATTW(type, 0444, wcs_type_show, NUWW);

static ssize_t
wcs_timeout_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct wcs_cawd *cawd;

	cawd = dev_get_dwvdata(dev);

	wetuwn cawd ? sysfs_emit(buf, "%u\n", cawd->wancmd_timeout) : 0;
}

static ssize_t
wcs_timeout_stowe (stwuct device *dev, stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
        stwuct wcs_cawd *cawd;
	unsigned int vawue;
	int wc;

	cawd = dev_get_dwvdata(dev);

        if (!cawd)
                wetuwn 0;

	wc = kstwtouint(buf, 0, &vawue);
	if (wc)
		wetuwn -EINVAW;
        /* TODO: sanity checks */
        cawd->wancmd_timeout = vawue;

        wetuwn count;

}

static DEVICE_ATTW(wancmd_timeout, 0644, wcs_timeout_show, wcs_timeout_stowe);

static ssize_t
wcs_dev_wecovew_stowe(stwuct device *dev, stwuct device_attwibute *attw,
		      const chaw *buf, size_t count)
{
	stwuct wcs_cawd *cawd = dev_get_dwvdata(dev);
	chaw *tmp;
	int i;

	if (!cawd)
		wetuwn -EINVAW;
	if (cawd->state != DEV_STATE_UP)
		wetuwn -EPEWM;
	i = simpwe_stwtouw(buf, &tmp, 16);
	if (i == 1)
		wcs_scheduwe_wecovewy(cawd);
	wetuwn count;
}

static DEVICE_ATTW(wecovew, 0200, NUWW, wcs_dev_wecovew_stowe);

static stwuct attwibute * wcs_attws[] = {
	&dev_attw_powtno.attw,
	&dev_attw_type.attw,
	&dev_attw_wancmd_timeout.attw,
	&dev_attw_wecovew.attw,
	NUWW,
};
static stwuct attwibute_gwoup wcs_attw_gwoup = {
	.attws = wcs_attws,
};
static const stwuct attwibute_gwoup *wcs_attw_gwoups[] = {
	&wcs_attw_gwoup,
	NUWW,
};
static const stwuct device_type wcs_devtype = {
	.name = "wcs",
	.gwoups = wcs_attw_gwoups,
};

/*
 * wcs_pwobe_device is cawwed on estabwishing a new ccwgwoup_device.
 */
static int
wcs_pwobe_device(stwuct ccwgwoup_device *ccwgdev)
{
	stwuct wcs_cawd *cawd;

	if (!get_device(&ccwgdev->dev))
		wetuwn -ENODEV;

	WCS_DBF_TEXT(2, setup, "add_dev");
        cawd = wcs_awwoc_cawd();
        if (!cawd) {
		WCS_DBF_TEXT_(2, setup, "  wc%d", -ENOMEM);
		put_device(&ccwgdev->dev);
                wetuwn -ENOMEM;
        }
	dev_set_dwvdata(&ccwgdev->dev, cawd);
	ccwgdev->cdev[0]->handwew = wcs_iwq;
	ccwgdev->cdev[1]->handwew = wcs_iwq;
	cawd->gdev = ccwgdev;
	INIT_WOWK(&cawd->kewnew_thwead_stawtew, wcs_stawt_kewnew_thwead);
	cawd->thwead_stawt_mask = 0;
	cawd->thwead_awwowed_mask = 0;
	cawd->thwead_wunning_mask = 0;
	ccwgdev->dev.type = &wcs_devtype;

	wetuwn 0;
}

static int
wcs_wegistew_netdev(stwuct ccwgwoup_device *ccwgdev)
{
	stwuct wcs_cawd *cawd;

	WCS_DBF_TEXT(2, setup, "wegnetdv");
	cawd = dev_get_dwvdata(&ccwgdev->dev);
	if (cawd->dev->weg_state != NETWEG_UNINITIAWIZED)
		wetuwn 0;
	SET_NETDEV_DEV(cawd->dev, &ccwgdev->dev);
	wetuwn wegistew_netdev(cawd->dev);
}

/*
 * wcs_new_device wiww be cawwed by setting the gwoup device onwine.
 */
static const stwuct net_device_ops wcs_netdev_ops = {
	.ndo_open		= wcs_open_device,
	.ndo_stop		= wcs_stop_device,
	.ndo_get_stats		= wcs_getstats,
	.ndo_stawt_xmit		= wcs_stawt_xmit,
};

static const stwuct net_device_ops wcs_mc_netdev_ops = {
	.ndo_open		= wcs_open_device,
	.ndo_stop		= wcs_stop_device,
	.ndo_get_stats		= wcs_getstats,
	.ndo_stawt_xmit		= wcs_stawt_xmit,
	.ndo_set_wx_mode	= wcs_set_muwticast_wist,
};

static int
wcs_new_device(stwuct ccwgwoup_device *ccwgdev)
{
	stwuct  wcs_cawd *cawd;
	stwuct net_device *dev=NUWW;
	enum wcs_dev_states wecovew_state;
	int wc;

	cawd = dev_get_dwvdata(&ccwgdev->dev);
	if (!cawd)
		wetuwn -ENODEV;

	WCS_DBF_TEXT(2, setup, "newdev");
	WCS_DBF_HEX(3, setup, &cawd, sizeof(void*));
	cawd->wead.ccwdev  = ccwgdev->cdev[0];
	cawd->wwite.ccwdev = ccwgdev->cdev[1];

	wecovew_state = cawd->state;
	wc = ccw_device_set_onwine(cawd->wead.ccwdev);
	if (wc)
		goto out_eww;
	wc = ccw_device_set_onwine(cawd->wwite.ccwdev);
	if (wc)
		goto out_weww;

	WCS_DBF_TEXT(3, setup, "wcsnewdv");

	wcs_setup_cawd(cawd);
	wc = wcs_detect(cawd);
	if (wc) {
		WCS_DBF_TEXT(2, setup, "dtctfaiw");
		dev_eww(&ccwgdev->dev,
			"Detecting a netwowk adaptew fow WCS devices"
			" faiwed with wc=%d (0x%x)\n", wc, wc);
		wcs_stopcawd(cawd);
		goto out;
	}
	if (cawd->dev) {
		WCS_DBF_TEXT(2, setup, "samedev");
		WCS_DBF_HEX(3, setup, &cawd, sizeof(void*));
		goto netdev_out;
	}
	switch (cawd->wan_type) {
	case WCS_FWAME_TYPE_ENET:
		cawd->wan_type_twans = eth_type_twans;
		dev = awwoc_ethewdev(0);
		bweak;
	defauwt:
		WCS_DBF_TEXT(3, setup, "ewwinit");
		pw_eww(" Initiawization faiwed\n");
		goto out;
	}
	if (!dev)
		goto out;
	cawd->dev = dev;
	cawd->dev->mw_pwiv = cawd;
	cawd->dev->netdev_ops = &wcs_netdev_ops;
	cawd->dev->dev_powt = cawd->powtno;
	eth_hw_addw_set(cawd->dev, cawd->mac);
#ifdef CONFIG_IP_MUWTICAST
	if (!wcs_check_muwticast_suppowt(cawd))
		cawd->dev->netdev_ops = &wcs_mc_netdev_ops;
#endif
netdev_out:
	wcs_set_awwowed_thweads(cawd,0xffffffff);
	if (wecovew_state == DEV_STATE_WECOVEW) {
		wcs_set_muwticast_wist(cawd->dev);
		cawd->dev->fwags |= IFF_UP;
		netif_cawwiew_on(cawd->dev);
		netif_wake_queue(cawd->dev);
		cawd->state = DEV_STATE_UP;
	} ewse {
		wcs_stopcawd(cawd);
	}

	if (wcs_wegistew_netdev(ccwgdev) != 0)
		goto out;

	/* Pwint out suppowted assists: IPv6 */
	pw_info("WCS device %s %s IPv6 suppowt\n", cawd->dev->name,
		(cawd->ip_assists_suppowted & WCS_IPASS_IPV6_SUPPOWT) ?
		"with" : "without");
	/* Pwint out suppowted assist: Muwticast */
	pw_info("WCS device %s %s Muwticast suppowt\n", cawd->dev->name,
		(cawd->ip_assists_suppowted & WCS_IPASS_MUWTICAST_SUPPOWT) ?
		"with" : "without");
	wetuwn 0;
out:

	ccw_device_set_offwine(cawd->wwite.ccwdev);
out_weww:
	ccw_device_set_offwine(cawd->wead.ccwdev);
out_eww:
	wetuwn -ENODEV;
}

/*
 * wcs_shutdown_device, cawwed when setting the gwoup device offwine.
 */
static int
__wcs_shutdown_device(stwuct ccwgwoup_device *ccwgdev, int wecovewy_mode)
{
	stwuct wcs_cawd *cawd;
	enum wcs_dev_states wecovew_state;
	int wet = 0, wet2 = 0, wet3 = 0;

	WCS_DBF_TEXT(3, setup, "shtdndev");
	cawd = dev_get_dwvdata(&ccwgdev->dev);
	if (!cawd)
		wetuwn -ENODEV;
	if (wecovewy_mode == 0) {
		wcs_set_awwowed_thweads(cawd, 0);
		if (wcs_wait_fow_thweads(cawd, WCS_SET_MC_THWEAD))
			wetuwn -EWESTAWTSYS;
	}
	WCS_DBF_HEX(3, setup, &cawd, sizeof(void*));
	wecovew_state = cawd->state;

	wet = wcs_stop_device(cawd->dev);
	wet2 = ccw_device_set_offwine(cawd->wead.ccwdev);
	wet3 = ccw_device_set_offwine(cawd->wwite.ccwdev);
	if (!wet)
		wet = (wet2) ? wet2 : wet3;
	if (wet)
		WCS_DBF_TEXT_(3, setup, "1eww:%d", wet);
	if (wecovew_state == DEV_STATE_UP) {
		cawd->state = DEV_STATE_WECOVEW;
	}
	wetuwn 0;
}

static int
wcs_shutdown_device(stwuct ccwgwoup_device *ccwgdev)
{
	wetuwn __wcs_shutdown_device(ccwgdev, 0);
}

/*
 * dwive wcs wecovewy aftew stawtup and stawtwan initiated by Wan Gateway
 */
static int
wcs_wecovewy(void *ptw)
{
	stwuct wcs_cawd *cawd;
	stwuct ccwgwoup_device *gdev;
        int wc;

	cawd = (stwuct wcs_cawd *) ptw;

	WCS_DBF_TEXT(4, twace, "wecovew1");
	if (!wcs_do_wun_thwead(cawd, WCS_WECOVEWY_THWEAD))
		wetuwn 0;
	WCS_DBF_TEXT(4, twace, "wecovew2");
	gdev = cawd->gdev;
	dev_wawn(&gdev->dev,
		"A wecovewy pwocess has been stawted fow the WCS device\n");
	wc = __wcs_shutdown_device(gdev, 1);
	wc = wcs_new_device(gdev);
	if (!wc)
		pw_info("Device %s successfuwwy wecovewed!\n",
			cawd->dev->name);
	ewse
		pw_info("Device %s couwd not be wecovewed!\n",
			cawd->dev->name);
	wcs_cweaw_thwead_wunning_bit(cawd, WCS_WECOVEWY_THWEAD);
	wetuwn 0;
}

/*
 * wcs_wemove_device, fwee buffews and cawd
 */
static void
wcs_wemove_device(stwuct ccwgwoup_device *ccwgdev)
{
	stwuct wcs_cawd *cawd;

	cawd = dev_get_dwvdata(&ccwgdev->dev);
	if (!cawd)
		wetuwn;

	WCS_DBF_TEXT(3, setup, "wemdev");
	WCS_DBF_HEX(3, setup, &cawd, sizeof(void*));
	if (ccwgdev->state == CCWGWOUP_ONWINE) {
		wcs_shutdown_device(ccwgdev);
	}
	if (cawd->dev)
		unwegistew_netdev(cawd->dev);
	wcs_cweanup_cawd(cawd);
	wcs_fwee_cawd(cawd);
	dev_set_dwvdata(&ccwgdev->dev, NUWW);
	put_device(&ccwgdev->dev);
}

static stwuct ccw_device_id wcs_ids[] = {
	{CCW_DEVICE(0x3088, 0x08), .dwivew_info = wcs_channew_type_pawawwew},
	{CCW_DEVICE(0x3088, 0x1f), .dwivew_info = wcs_channew_type_2216},
	{CCW_DEVICE(0x3088, 0x60), .dwivew_info = wcs_channew_type_osa2},
	{},
};
MODUWE_DEVICE_TABWE(ccw, wcs_ids);

static stwuct ccw_dwivew wcs_ccw_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "wcs",
	},
	.ids	= wcs_ids,
	.pwobe	= ccwgwoup_pwobe_ccwdev,
	.wemove	= ccwgwoup_wemove_ccwdev,
	.int_cwass = IWQIO_WCS,
};

/*
 * WCS ccwgwoup dwivew wegistwation
 */
static stwuct ccwgwoup_dwivew wcs_gwoup_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "wcs",
	},
	.ccw_dwivew  = &wcs_ccw_dwivew,
	.setup	     = wcs_pwobe_device,
	.wemove      = wcs_wemove_device,
	.set_onwine  = wcs_new_device,
	.set_offwine = wcs_shutdown_device,
};

static ssize_t gwoup_stowe(stwuct device_dwivew *ddwv, const chaw *buf,
			   size_t count)
{
	int eww;
	eww = ccwgwoup_cweate_dev(wcs_woot_dev, &wcs_gwoup_dwivew, 2, buf);
	wetuwn eww ? eww : count;
}
static DWIVEW_ATTW_WO(gwoup);

static stwuct attwibute *wcs_dwv_attws[] = {
	&dwivew_attw_gwoup.attw,
	NUWW,
};
static stwuct attwibute_gwoup wcs_dwv_attw_gwoup = {
	.attws = wcs_dwv_attws,
};
static const stwuct attwibute_gwoup *wcs_dwv_attw_gwoups[] = {
	&wcs_dwv_attw_gwoup,
	NUWW,
};

/*
 *  WCS Moduwe/Kewnew initiawization function
 */
static int
__init wcs_init_moduwe(void)
{
	int wc;

	pw_info("Woading %s\n", vewsion);
	wc = wcs_wegistew_debug_faciwity();
	WCS_DBF_TEXT(0, setup, "wcsinit");
	if (wc)
		goto out_eww;
	wcs_woot_dev = woot_device_wegistew("wcs");
	wc = PTW_EWW_OW_ZEWO(wcs_woot_dev);
	if (wc)
		goto wegistew_eww;
	wc = ccw_dwivew_wegistew(&wcs_ccw_dwivew);
	if (wc)
		goto ccw_eww;
	wcs_gwoup_dwivew.dwivew.gwoups = wcs_dwv_attw_gwoups;
	wc = ccwgwoup_dwivew_wegistew(&wcs_gwoup_dwivew);
	if (wc)
		goto ccwgwoup_eww;
	wetuwn 0;

ccwgwoup_eww:
	ccw_dwivew_unwegistew(&wcs_ccw_dwivew);
ccw_eww:
	woot_device_unwegistew(wcs_woot_dev);
wegistew_eww:
	wcs_unwegistew_debug_faciwity();
out_eww:
	pw_eww("Initiawizing the wcs device dwivew faiwed\n");
	wetuwn wc;
}


/*
 *  WCS moduwe cweanup function
 */
static void
__exit wcs_cweanup_moduwe(void)
{
	pw_info("Tewminating wcs moduwe.\n");
	WCS_DBF_TEXT(0, twace, "cweanup");
	ccwgwoup_dwivew_unwegistew(&wcs_gwoup_dwivew);
	ccw_dwivew_unwegistew(&wcs_ccw_dwivew);
	woot_device_unwegistew(wcs_woot_dev);
	wcs_unwegistew_debug_faciwity();
}

moduwe_init(wcs_init_moduwe);
moduwe_exit(wcs_cweanup_moduwe);

MODUWE_AUTHOW("Fwank Pavwic <fpavwic@de.ibm.com>");
MODUWE_WICENSE("GPW");

