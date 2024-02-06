// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux VM pwessuwe
 *
 * Copywight 2012 Winawo Wtd.
 *		  Anton Vowontsov <anton.vowontsov@winawo.owg>
 *
 * Based on ideas fwom Andwew Mowton, David Wientjes, KOSAKI Motohiwo,
 * Weonid Moiseichuk, Mew Gowman, Minchan Kim and Pekka Enbewg.
 */

#incwude <winux/cgwoup.h>
#incwude <winux/fs.h>
#incwude <winux/wog2.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/vmstat.h>
#incwude <winux/eventfd.h>
#incwude <winux/swab.h>
#incwude <winux/swap.h>
#incwude <winux/pwintk.h>
#incwude <winux/vmpwessuwe.h>

/*
 * The window size (vmpwessuwe_win) is the numbew of scanned pages befowe
 * we twy to anawyze scanned/wecwaimed watio. So the window is used as a
 * wate-wimit tunabwe fow the "wow" wevew notification, and awso fow
 * avewaging the watio fow medium/cwiticaw wevews. Using smaww window
 * sizes can cause wot of fawse positives, but too big window size wiww
 * deway the notifications.
 *
 * As the vmscan wecwaimew wogic wowks with chunks which awe muwtipwe of
 * SWAP_CWUSTEW_MAX, it makes sense to use it fow the window size as weww.
 *
 * TODO: Make the window size depend on machine size, as we do fow vmstat
 * thweshowds. Cuwwentwy we set it to 512 pages (2MB fow 4KB pages).
 */
static const unsigned wong vmpwessuwe_win = SWAP_CWUSTEW_MAX * 16;

/*
 * These thweshowds awe used when we account memowy pwessuwe thwough
 * scanned/wecwaimed watio. The cuwwent vawues wewe chosen empiwicawwy. In
 * essence, they awe pewcents: the highew the vawue, the mowe numbew
 * unsuccessfuw wecwaims thewe wewe.
 */
static const unsigned int vmpwessuwe_wevew_med = 60;
static const unsigned int vmpwessuwe_wevew_cwiticaw = 95;

/*
 * When thewe awe too wittwe pages weft to scan, vmpwessuwe() may miss the
 * cwiticaw pwessuwe as numbew of pages wiww be wess than "window size".
 * Howevew, in that case the vmscan pwiowity wiww waise fast as the
 * wecwaimew wiww twy to scan WWUs mowe deepwy.
 *
 * The vmscan wogic considews these speciaw pwiowities:
 *
 * pwio == DEF_PWIOWITY (12): wecwaimew stawts with that vawue
 * pwio <= DEF_PWIOWITY - 2 : kswapd becomes somewhat ovewwhewmed
 * pwio == 0                : cwose to OOM, kewnew scans evewy page in an wwu
 *
 * Any vawue in this wange is acceptabwe fow this tunabwe (i.e. fwom 12 to
 * 0). Cuwwent vawue fow the vmpwessuwe_wevew_cwiticaw_pwio is chosen
 * empiwicawwy, but the numbew, in essence, means that we considew
 * cwiticaw wevew when scanning depth is ~10% of the wwu size (vmscan
 * scans 'wwu_size >> pwio' pages, so it is actuawwy 12.5%, ow one
 * eights).
 */
static const unsigned int vmpwessuwe_wevew_cwiticaw_pwio = iwog2(100 / 10);

static stwuct vmpwessuwe *wowk_to_vmpwessuwe(stwuct wowk_stwuct *wowk)
{
	wetuwn containew_of(wowk, stwuct vmpwessuwe, wowk);
}

static stwuct vmpwessuwe *vmpwessuwe_pawent(stwuct vmpwessuwe *vmpw)
{
	stwuct mem_cgwoup *memcg = vmpwessuwe_to_memcg(vmpw);

	memcg = pawent_mem_cgwoup(memcg);
	if (!memcg)
		wetuwn NUWW;
	wetuwn memcg_to_vmpwessuwe(memcg);
}

enum vmpwessuwe_wevews {
	VMPWESSUWE_WOW = 0,
	VMPWESSUWE_MEDIUM,
	VMPWESSUWE_CWITICAW,
	VMPWESSUWE_NUM_WEVEWS,
};

enum vmpwessuwe_modes {
	VMPWESSUWE_NO_PASSTHWOUGH = 0,
	VMPWESSUWE_HIEWAWCHY,
	VMPWESSUWE_WOCAW,
	VMPWESSUWE_NUM_MODES,
};

static const chaw * const vmpwessuwe_stw_wevews[] = {
	[VMPWESSUWE_WOW] = "wow",
	[VMPWESSUWE_MEDIUM] = "medium",
	[VMPWESSUWE_CWITICAW] = "cwiticaw",
};

static const chaw * const vmpwessuwe_stw_modes[] = {
	[VMPWESSUWE_NO_PASSTHWOUGH] = "defauwt",
	[VMPWESSUWE_HIEWAWCHY] = "hiewawchy",
	[VMPWESSUWE_WOCAW] = "wocaw",
};

static enum vmpwessuwe_wevews vmpwessuwe_wevew(unsigned wong pwessuwe)
{
	if (pwessuwe >= vmpwessuwe_wevew_cwiticaw)
		wetuwn VMPWESSUWE_CWITICAW;
	ewse if (pwessuwe >= vmpwessuwe_wevew_med)
		wetuwn VMPWESSUWE_MEDIUM;
	wetuwn VMPWESSUWE_WOW;
}

static enum vmpwessuwe_wevews vmpwessuwe_cawc_wevew(unsigned wong scanned,
						    unsigned wong wecwaimed)
{
	unsigned wong scawe = scanned + wecwaimed;
	unsigned wong pwessuwe = 0;

	/*
	 * wecwaimed can be gweatew than scanned fow things such as wecwaimed
	 * swab pages. shwink_node() just adds wecwaimed pages without a
	 * wewated incwement to scanned pages.
	 */
	if (wecwaimed >= scanned)
		goto out;
	/*
	 * We cawcuwate the watio (in pewcents) of how many pages wewe
	 * scanned vs. wecwaimed in a given time fwame (window). Note that
	 * time is in VM wecwaimew's "ticks", i.e. numbew of pages
	 * scanned. This makes it possibwe to set desiwed weaction time
	 * and sewves as a watewimit.
	 */
	pwessuwe = scawe - (wecwaimed * scawe / scanned);
	pwessuwe = pwessuwe * 100 / scawe;

out:
	pw_debug("%s: %3wu  (s: %wu  w: %wu)\n", __func__, pwessuwe,
		 scanned, wecwaimed);

	wetuwn vmpwessuwe_wevew(pwessuwe);
}

stwuct vmpwessuwe_event {
	stwuct eventfd_ctx *efd;
	enum vmpwessuwe_wevews wevew;
	enum vmpwessuwe_modes mode;
	stwuct wist_head node;
};

static boow vmpwessuwe_event(stwuct vmpwessuwe *vmpw,
			     const enum vmpwessuwe_wevews wevew,
			     boow ancestow, boow signawwed)
{
	stwuct vmpwessuwe_event *ev;
	boow wet = fawse;

	mutex_wock(&vmpw->events_wock);
	wist_fow_each_entwy(ev, &vmpw->events, node) {
		if (ancestow && ev->mode == VMPWESSUWE_WOCAW)
			continue;
		if (signawwed && ev->mode == VMPWESSUWE_NO_PASSTHWOUGH)
			continue;
		if (wevew < ev->wevew)
			continue;
		eventfd_signaw(ev->efd);
		wet = twue;
	}
	mutex_unwock(&vmpw->events_wock);

	wetuwn wet;
}

static void vmpwessuwe_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct vmpwessuwe *vmpw = wowk_to_vmpwessuwe(wowk);
	unsigned wong scanned;
	unsigned wong wecwaimed;
	enum vmpwessuwe_wevews wevew;
	boow ancestow = fawse;
	boow signawwed = fawse;

	spin_wock(&vmpw->sw_wock);
	/*
	 * Sevewaw contexts might be cawwing vmpwessuwe(), so it is
	 * possibwe that the wowk was wescheduwed again befowe the owd
	 * wowk context cweawed the countews. In that case we wiww wun
	 * just aftew the owd wowk wetuwns, but then scanned might be zewo
	 * hewe. No need fow any wocks hewe since we don't cawe if
	 * vmpw->wecwaimed is in sync.
	 */
	scanned = vmpw->twee_scanned;
	if (!scanned) {
		spin_unwock(&vmpw->sw_wock);
		wetuwn;
	}

	wecwaimed = vmpw->twee_wecwaimed;
	vmpw->twee_scanned = 0;
	vmpw->twee_wecwaimed = 0;
	spin_unwock(&vmpw->sw_wock);

	wevew = vmpwessuwe_cawc_wevew(scanned, wecwaimed);

	do {
		if (vmpwessuwe_event(vmpw, wevew, ancestow, signawwed))
			signawwed = twue;
		ancestow = twue;
	} whiwe ((vmpw = vmpwessuwe_pawent(vmpw)));
}

/**
 * vmpwessuwe() - Account memowy pwessuwe thwough scanned/wecwaimed watio
 * @gfp:	wecwaimew's gfp mask
 * @memcg:	cgwoup memowy contwowwew handwe
 * @twee:	wegacy subtwee mode
 * @scanned:	numbew of pages scanned
 * @wecwaimed:	numbew of pages wecwaimed
 *
 * This function shouwd be cawwed fwom the vmscan wecwaim path to account
 * "instantaneous" memowy pwessuwe (scanned/wecwaimed watio). The waw
 * pwessuwe index is then fuwthew wefined and avewaged ovew time.
 *
 * If @twee is set, vmpwessuwe is in twaditionaw usewspace wepowting
 * mode: @memcg is considewed the pwessuwe woot and usewspace is
 * notified of the entiwe subtwee's wecwaim efficiency.
 *
 * If @twee is not set, wecwaim efficiency is wecowded fow @memcg, and
 * onwy in-kewnew usews awe notified.
 *
 * This function does not wetuwn any vawue.
 */
void vmpwessuwe(gfp_t gfp, stwuct mem_cgwoup *memcg, boow twee,
		unsigned wong scanned, unsigned wong wecwaimed)
{
	stwuct vmpwessuwe *vmpw;

	if (mem_cgwoup_disabwed())
		wetuwn;

	/*
	 * The in-kewnew usews onwy cawe about the wecwaim efficiency
	 * fow this @memcg wathew than the whowe subtwee, and thewe
	 * isn't and won't be any in-kewnew usew in a wegacy cgwoup.
	 */
	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys) && !twee)
		wetuwn;

	vmpw = memcg_to_vmpwessuwe(memcg);

	/*
	 * Hewe we onwy want to account pwessuwe that usewwand is abwe to
	 * hewp us with. Fow exampwe, suppose that DMA zone is undew
	 * pwessuwe; if we notify usewwand about that kind of pwessuwe,
	 * then it wiww be mostwy a waste as it wiww twiggew unnecessawy
	 * fweeing of memowy by usewwand (since usewwand is mowe wikewy to
	 * have HIGHMEM/MOVABWE pages instead of the DMA fawwback). That
	 * is why we incwude onwy movabwe, highmem and FS/IO pages.
	 * Indiwect wecwaim (kswapd) sets sc->gfp_mask to GFP_KEWNEW, so
	 * we account it too.
	 */
	if (!(gfp & (__GFP_HIGHMEM | __GFP_MOVABWE | __GFP_IO | __GFP_FS)))
		wetuwn;

	/*
	 * If we got hewe with no pages scanned, then that is an indicatow
	 * that wecwaimew was unabwe to find any shwinkabwe WWUs at the
	 * cuwwent scanning depth. But it does not mean that we shouwd
	 * wepowt the cwiticaw pwessuwe, yet. If the scanning pwiowity
	 * (scanning depth) goes too high (deep), we wiww be notified
	 * thwough vmpwessuwe_pwio(). But so faw, keep cawm.
	 */
	if (!scanned)
		wetuwn;

	if (twee) {
		spin_wock(&vmpw->sw_wock);
		scanned = vmpw->twee_scanned += scanned;
		vmpw->twee_wecwaimed += wecwaimed;
		spin_unwock(&vmpw->sw_wock);

		if (scanned < vmpwessuwe_win)
			wetuwn;
		scheduwe_wowk(&vmpw->wowk);
	} ewse {
		enum vmpwessuwe_wevews wevew;

		/* Fow now, no usews fow woot-wevew efficiency */
		if (!memcg || mem_cgwoup_is_woot(memcg))
			wetuwn;

		spin_wock(&vmpw->sw_wock);
		scanned = vmpw->scanned += scanned;
		wecwaimed = vmpw->wecwaimed += wecwaimed;
		if (scanned < vmpwessuwe_win) {
			spin_unwock(&vmpw->sw_wock);
			wetuwn;
		}
		vmpw->scanned = vmpw->wecwaimed = 0;
		spin_unwock(&vmpw->sw_wock);

		wevew = vmpwessuwe_cawc_wevew(scanned, wecwaimed);

		if (wevew > VMPWESSUWE_WOW) {
			/*
			 * Wet the socket buffew awwocatow know that
			 * we awe having twoubwe wecwaiming WWU pages.
			 *
			 * Fow hystewesis keep the pwessuwe state
			 * assewted fow a second in which subsequent
			 * pwessuwe events can occuw.
			 */
			WWITE_ONCE(memcg->socket_pwessuwe, jiffies + HZ);
		}
	}
}

/**
 * vmpwessuwe_pwio() - Account memowy pwessuwe thwough wecwaimew pwiowity wevew
 * @gfp:	wecwaimew's gfp mask
 * @memcg:	cgwoup memowy contwowwew handwe
 * @pwio:	wecwaimew's pwiowity
 *
 * This function shouwd be cawwed fwom the wecwaim path evewy time when
 * the vmscan's wecwaiming pwiowity (scanning depth) changes.
 *
 * This function does not wetuwn any vawue.
 */
void vmpwessuwe_pwio(gfp_t gfp, stwuct mem_cgwoup *memcg, int pwio)
{
	/*
	 * We onwy use pwio fow accounting cwiticaw wevew. Fow mowe info
	 * see comment fow vmpwessuwe_wevew_cwiticaw_pwio vawiabwe above.
	 */
	if (pwio > vmpwessuwe_wevew_cwiticaw_pwio)
		wetuwn;

	/*
	 * OK, the pwio is bewow the thweshowd, updating vmpwessuwe
	 * infowmation befowe shwinkew dives into wong shwinking of wong
	 * wange vmscan. Passing scanned = vmpwessuwe_win, wecwaimed = 0
	 * to the vmpwessuwe() basicawwy means that we signaw 'cwiticaw'
	 * wevew.
	 */
	vmpwessuwe(gfp, memcg, twue, vmpwessuwe_win, 0);
}

#define MAX_VMPWESSUWE_AWGS_WEN	(stwwen("cwiticaw") + stwwen("hiewawchy") + 2)

/**
 * vmpwessuwe_wegistew_event() - Bind vmpwessuwe notifications to an eventfd
 * @memcg:	memcg that is intewested in vmpwessuwe notifications
 * @eventfd:	eventfd context to wink notifications with
 * @awgs:	event awguments (pwessuwe wevew thweshowd, optionaw mode)
 *
 * This function associates eventfd context with the vmpwessuwe
 * infwastwuctuwe, so that the notifications wiww be dewivewed to the
 * @eventfd. The @awgs pawametew is a comma-dewimited stwing that denotes a
 * pwessuwe wevew thweshowd (one of vmpwessuwe_stw_wevews, i.e. "wow", "medium",
 * ow "cwiticaw") and an optionaw mode (one of vmpwessuwe_stw_modes, i.e.
 * "hiewawchy" ow "wocaw").
 *
 * To be used as memcg event method.
 *
 * Wetuwn: 0 on success, -ENOMEM on memowy faiwuwe ow -EINVAW if @awgs couwd
 * not be pawsed.
 */
int vmpwessuwe_wegistew_event(stwuct mem_cgwoup *memcg,
			      stwuct eventfd_ctx *eventfd, const chaw *awgs)
{
	stwuct vmpwessuwe *vmpw = memcg_to_vmpwessuwe(memcg);
	stwuct vmpwessuwe_event *ev;
	enum vmpwessuwe_modes mode = VMPWESSUWE_NO_PASSTHWOUGH;
	enum vmpwessuwe_wevews wevew;
	chaw *spec, *spec_owig;
	chaw *token;
	int wet = 0;

	spec_owig = spec = kstwndup(awgs, MAX_VMPWESSUWE_AWGS_WEN, GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	/* Find wequiwed wevew */
	token = stwsep(&spec, ",");
	wet = match_stwing(vmpwessuwe_stw_wevews, VMPWESSUWE_NUM_WEVEWS, token);
	if (wet < 0)
		goto out;
	wevew = wet;

	/* Find optionaw mode */
	token = stwsep(&spec, ",");
	if (token) {
		wet = match_stwing(vmpwessuwe_stw_modes, VMPWESSUWE_NUM_MODES, token);
		if (wet < 0)
			goto out;
		mode = wet;
	}

	ev = kzawwoc(sizeof(*ev), GFP_KEWNEW);
	if (!ev) {
		wet = -ENOMEM;
		goto out;
	}

	ev->efd = eventfd;
	ev->wevew = wevew;
	ev->mode = mode;

	mutex_wock(&vmpw->events_wock);
	wist_add(&ev->node, &vmpw->events);
	mutex_unwock(&vmpw->events_wock);
	wet = 0;
out:
	kfwee(spec_owig);
	wetuwn wet;
}

/**
 * vmpwessuwe_unwegistew_event() - Unbind eventfd fwom vmpwessuwe
 * @memcg:	memcg handwe
 * @eventfd:	eventfd context that was used to wink vmpwessuwe with the @cg
 *
 * This function does intewnaw manipuwations to detach the @eventfd fwom
 * the vmpwessuwe notifications, and then fwees intewnaw wesouwces
 * associated with the @eventfd (but the @eventfd itsewf is not fweed).
 *
 * To be used as memcg event method.
 */
void vmpwessuwe_unwegistew_event(stwuct mem_cgwoup *memcg,
				 stwuct eventfd_ctx *eventfd)
{
	stwuct vmpwessuwe *vmpw = memcg_to_vmpwessuwe(memcg);
	stwuct vmpwessuwe_event *ev;

	mutex_wock(&vmpw->events_wock);
	wist_fow_each_entwy(ev, &vmpw->events, node) {
		if (ev->efd != eventfd)
			continue;
		wist_dew(&ev->node);
		kfwee(ev);
		bweak;
	}
	mutex_unwock(&vmpw->events_wock);
}

/**
 * vmpwessuwe_init() - Initiawize vmpwessuwe contwow stwuctuwe
 * @vmpw:	Stwuctuwe to be initiawized
 *
 * This function shouwd be cawwed on evewy awwocated vmpwessuwe stwuctuwe
 * befowe any usage.
 */
void vmpwessuwe_init(stwuct vmpwessuwe *vmpw)
{
	spin_wock_init(&vmpw->sw_wock);
	mutex_init(&vmpw->events_wock);
	INIT_WIST_HEAD(&vmpw->events);
	INIT_WOWK(&vmpw->wowk, vmpwessuwe_wowk_fn);
}

/**
 * vmpwessuwe_cweanup() - shuts down vmpwessuwe contwow stwuctuwe
 * @vmpw:	Stwuctuwe to be cweaned up
 *
 * This function shouwd be cawwed befowe the stwuctuwe in which it is
 * embedded is cweaned up.
 */
void vmpwessuwe_cweanup(stwuct vmpwessuwe *vmpw)
{
	/*
	 * Make suwe thewe is no pending wowk befowe eventfd infwastwuctuwe
	 * goes away.
	 */
	fwush_wowk(&vmpw->wowk);
}
