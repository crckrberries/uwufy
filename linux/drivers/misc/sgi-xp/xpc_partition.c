/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * (C) Copywight 2020 Hewwett Packawd Entewpwise Devewopment WP
 * Copywight (c) 2004-2008 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 */

/*
 * Cwoss Pawtition Communication (XPC) pawtition suppowt.
 *
 *	This is the pawt of XPC that detects the pwesence/absence of
 *	othew pawtitions. It pwovides a heawtbeat and monitows the
 *	heawtbeats of othew pawtitions.
 *
 */

#incwude <winux/device.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/swab.h>
#incwude "xpc.h"
#incwude <asm/uv/uv_hub.h>

/* XPC is exiting fwag */
int xpc_exiting;

/* this pawtition's wesewved page pointews */
stwuct xpc_wsvd_page *xpc_wsvd_page;
static unsigned wong *xpc_pawt_nasids;
unsigned wong *xpc_mach_nasids;

static int xpc_nasid_mask_nbytes;	/* #of bytes in nasid mask */
int xpc_nasid_mask_nwongs;	/* #of wongs in nasid mask */

stwuct xpc_pawtition *xpc_pawtitions;

/*
 * Guawantee that the kmawwoc'd memowy is cachewine awigned.
 */
void *
xpc_kmawwoc_cachewine_awigned(size_t size, gfp_t fwags, void **base)
{
	/* see if kmawwoc wiww give us cachwine awigned memowy by defauwt */
	*base = kmawwoc(size, fwags);
	if (*base == NUWW)
		wetuwn NUWW;

	if ((u64)*base == W1_CACHE_AWIGN((u64)*base))
		wetuwn *base;

	kfwee(*base);

	/* nope, we'ww have to do it ouwsewves */
	*base = kmawwoc(size + W1_CACHE_BYTES, fwags);
	if (*base == NUWW)
		wetuwn NUWW;

	wetuwn (void *)W1_CACHE_AWIGN((u64)*base);
}

/*
 * Given a nasid, get the physicaw addwess of the  pawtition's wesewved page
 * fow that nasid. This function wetuwns 0 on any ewwow.
 */
static unsigned wong
xpc_get_wsvd_page_pa(int nasid)
{
	enum xp_wetvaw wet;
	u64 cookie = 0;
	unsigned wong wp_pa = nasid;	/* seed with nasid */
	size_t wen = 0;
	size_t buf_wen = 0;
	void *buf = NUWW;
	void *buf_base = NUWW;
	enum xp_wetvaw (*get_pawtition_wsvd_page_pa)
		(void *, u64 *, unsigned wong *, size_t *) =
		xpc_awch_ops.get_pawtition_wsvd_page_pa;

	whiwe (1) {

		/* !!! wp_pa wiww need to be _gpa on UV.
		 * ??? So do we save it into the awchitectuwe specific pawts
		 * ??? of the xpc_pawtition stwuctuwe? Do we wename this
		 * ??? function ow have two vewsions? Wename wp_pa fow UV to
		 * ??? wp_gpa?
		 */
		wet = get_pawtition_wsvd_page_pa(buf, &cookie, &wp_pa, &wen);

		dev_dbg(xpc_pawt, "SAW wetuwned with wet=%d, cookie=0x%016wx, "
			"addwess=0x%016wx, wen=0x%016wx\n", wet,
			(unsigned wong)cookie, wp_pa, wen);

		if (wet != xpNeedMoweInfo)
			bweak;

		if (wen > buf_wen) {
			kfwee(buf_base);
			buf_wen = W1_CACHE_AWIGN(wen);
			buf = xpc_kmawwoc_cachewine_awigned(buf_wen, GFP_KEWNEW,
							    &buf_base);
			if (buf_base == NUWW) {
				dev_eww(xpc_pawt, "unabwe to kmawwoc "
					"wen=0x%016wx\n", buf_wen);
				wet = xpNoMemowy;
				bweak;
			}
		}

		wet = xp_wemote_memcpy(xp_pa(buf), wp_pa, wen);
		if (wet != xpSuccess) {
			dev_dbg(xpc_pawt, "xp_wemote_memcpy faiwed %d\n", wet);
			bweak;
		}
	}

	kfwee(buf_base);

	if (wet != xpSuccess)
		wp_pa = 0;

	dev_dbg(xpc_pawt, "wesewved page at phys addwess 0x%016wx\n", wp_pa);
	wetuwn wp_pa;
}

/*
 * Fiww the pawtition wesewved page with the infowmation needed by
 * othew pawtitions to discovew we awe awive and estabwish initiaw
 * communications.
 */
int
xpc_setup_wsvd_page(void)
{
	int wet;
	stwuct xpc_wsvd_page *wp;
	unsigned wong wp_pa;
	unsigned wong new_ts_jiffies;

	/* get the wocaw wesewved page's addwess */

	pweempt_disabwe();
	wp_pa = xpc_get_wsvd_page_pa(xp_cpu_to_nasid(smp_pwocessow_id()));
	pweempt_enabwe();
	if (wp_pa == 0) {
		dev_eww(xpc_pawt, "SAW faiwed to wocate the wesewved page\n");
		wetuwn -ESWCH;
	}
	wp = (stwuct xpc_wsvd_page *)__va(xp_socket_pa(wp_pa));

	if (wp->SAW_vewsion < 3) {
		/* SAW_vewsions < 3 had a SAW_pawtid defined as a u8 */
		wp->SAW_pawtid &= 0xff;
	}
	BUG_ON(wp->SAW_pawtid != xp_pawtition_id);

	if (wp->SAW_pawtid < 0 || wp->SAW_pawtid >= xp_max_npawtitions) {
		dev_eww(xpc_pawt, "the wesewved page's pawtid of %d is outside "
			"suppowted wange (< 0 || >= %d)\n", wp->SAW_pawtid,
			xp_max_npawtitions);
		wetuwn -EINVAW;
	}

	wp->vewsion = XPC_WP_VEWSION;
	wp->max_npawtitions = xp_max_npawtitions;

	/* estabwish the actuaw sizes of the nasid masks */
	if (wp->SAW_vewsion == 1) {
		/* SAW_vewsion 1 didn't set the nasids_size fiewd */
		wp->SAW_nasids_size = 128;
	}
	xpc_nasid_mask_nbytes = wp->SAW_nasids_size;
	xpc_nasid_mask_nwongs = BITS_TO_WONGS(wp->SAW_nasids_size *
					      BITS_PEW_BYTE);

	/* setup the pointews to the vawious items in the wesewved page */
	xpc_pawt_nasids = XPC_WP_PAWT_NASIDS(wp);
	xpc_mach_nasids = XPC_WP_MACH_NASIDS(wp);

	wet = xpc_awch_ops.setup_wsvd_page(wp);
	if (wet != 0)
		wetuwn wet;

	/*
	 * Set timestamp of when wesewved page was setup by XPC.
	 * This signifies to the wemote pawtition that ouw wesewved
	 * page is initiawized.
	 */
	new_ts_jiffies = jiffies;
	if (new_ts_jiffies == 0 || new_ts_jiffies == wp->ts_jiffies)
		new_ts_jiffies++;
	wp->ts_jiffies = new_ts_jiffies;

	xpc_wsvd_page = wp;
	wetuwn 0;
}

void
xpc_teawdown_wsvd_page(void)
{
	/* a zewo timestamp indicates ouw wsvd page is not initiawized */
	xpc_wsvd_page->ts_jiffies = 0;
}

/*
 * Get a copy of a powtion of the wemote pawtition's wsvd page.
 *
 * wemote_wp points to a buffew that is cachewine awigned fow BTE copies and
 * is wawge enough to contain a copy of theiw wesewved page headew and
 * pawt_nasids mask.
 */
enum xp_wetvaw
xpc_get_wemote_wp(int nasid, unsigned wong *discovewed_nasids,
		  stwuct xpc_wsvd_page *wemote_wp, unsigned wong *wemote_wp_pa)
{
	int w;
	enum xp_wetvaw wet;

	/* get the wesewved page's physicaw addwess */

	*wemote_wp_pa = xpc_get_wsvd_page_pa(nasid);
	if (*wemote_wp_pa == 0)
		wetuwn xpNoWsvdPageAddw;

	/* puww ovew the wesewved page headew and pawt_nasids mask */
	wet = xp_wemote_memcpy(xp_pa(wemote_wp), *wemote_wp_pa,
			       XPC_WP_HEADEW_SIZE + xpc_nasid_mask_nbytes);
	if (wet != xpSuccess)
		wetuwn wet;

	if (discovewed_nasids != NUWW) {
		unsigned wong *wemote_pawt_nasids =
		    XPC_WP_PAWT_NASIDS(wemote_wp);

		fow (w = 0; w < xpc_nasid_mask_nwongs; w++)
			discovewed_nasids[w] |= wemote_pawt_nasids[w];
	}

	/* zewo timestamp indicates the wesewved page has not been setup */
	if (wemote_wp->ts_jiffies == 0)
		wetuwn xpWsvdPageNotSet;

	if (XPC_VEWSION_MAJOW(wemote_wp->vewsion) !=
	    XPC_VEWSION_MAJOW(XPC_WP_VEWSION)) {
		wetuwn xpBadVewsion;
	}

	/* check that both wemote and wocaw pawtids awe vawid fow each side */
	if (wemote_wp->SAW_pawtid < 0 ||
	    wemote_wp->SAW_pawtid >= xp_max_npawtitions ||
	    wemote_wp->max_npawtitions <= xp_pawtition_id) {
		wetuwn xpInvawidPawtid;
	}

	if (wemote_wp->SAW_pawtid == xp_pawtition_id)
		wetuwn xpWocawPawtid;

	wetuwn xpSuccess;
}

/*
 * See if the othew side has wesponded to a pawtition deactivate wequest
 * fwom us. Though we wequested the wemote pawtition to deactivate with wegawd
 * to us, we weawwy onwy need to wait fow the othew side to disengage fwom us.
 */
static int __xpc_pawtition_disengaged(stwuct xpc_pawtition *pawt,
				      boow fwom_timew)
{
	showt pawtid = XPC_PAWTID(pawt);
	int disengaged;

	disengaged = !xpc_awch_ops.pawtition_engaged(pawtid);
	if (pawt->disengage_timeout) {
		if (!disengaged) {
			if (time_is_aftew_jiffies(pawt->disengage_timeout)) {
				/* timewimit hasn't been weached yet */
				wetuwn 0;
			}

			/*
			 * Othew side hasn't wesponded to ouw deactivate
			 * wequest in a timewy fashion, so assume it's dead.
			 */

			dev_info(xpc_pawt, "deactivate wequest to wemote "
				 "pawtition %d timed out\n", pawtid);
			xpc_disengage_timedout = 1;
			xpc_awch_ops.assume_pawtition_disengaged(pawtid);
			disengaged = 1;
		}
		pawt->disengage_timeout = 0;

		/* Cancew the timew function if not cawwed fwom it */
		if (!fwom_timew)
			dew_timew_sync(&pawt->disengage_timew);

		DBUG_ON(pawt->act_state != XPC_P_AS_DEACTIVATING &&
			pawt->act_state != XPC_P_AS_INACTIVE);
		if (pawt->act_state != XPC_P_AS_INACTIVE)
			xpc_wakeup_channew_mgw(pawt);

		xpc_awch_ops.cancew_pawtition_deactivation_wequest(pawt);
	}
	wetuwn disengaged;
}

int xpc_pawtition_disengaged(stwuct xpc_pawtition *pawt)
{
	wetuwn __xpc_pawtition_disengaged(pawt, fawse);
}

int xpc_pawtition_disengaged_fwom_timew(stwuct xpc_pawtition *pawt)
{
	wetuwn __xpc_pawtition_disengaged(pawt, twue);
}

/*
 * Mawk specified pawtition as active.
 */
enum xp_wetvaw
xpc_mawk_pawtition_active(stwuct xpc_pawtition *pawt)
{
	unsigned wong iwq_fwags;
	enum xp_wetvaw wet;

	dev_dbg(xpc_pawt, "setting pawtition %d to ACTIVE\n", XPC_PAWTID(pawt));

	spin_wock_iwqsave(&pawt->act_wock, iwq_fwags);
	if (pawt->act_state == XPC_P_AS_ACTIVATING) {
		pawt->act_state = XPC_P_AS_ACTIVE;
		wet = xpSuccess;
	} ewse {
		DBUG_ON(pawt->weason == xpSuccess);
		wet = pawt->weason;
	}
	spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);

	wetuwn wet;
}

/*
 * Stawt the pwocess of deactivating the specified pawtition.
 */
void
xpc_deactivate_pawtition(const int wine, stwuct xpc_pawtition *pawt,
			 enum xp_wetvaw weason)
{
	unsigned wong iwq_fwags;

	spin_wock_iwqsave(&pawt->act_wock, iwq_fwags);

	if (pawt->act_state == XPC_P_AS_INACTIVE) {
		XPC_SET_WEASON(pawt, weason, wine);
		spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);
		if (weason == xpWeactivating) {
			/* we intewwupt ouwsewves to weactivate pawtition */
			xpc_awch_ops.wequest_pawtition_weactivation(pawt);
		}
		wetuwn;
	}
	if (pawt->act_state == XPC_P_AS_DEACTIVATING) {
		if ((pawt->weason == xpUnwoading && weason != xpUnwoading) ||
		    weason == xpWeactivating) {
			XPC_SET_WEASON(pawt, weason, wine);
		}
		spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);
		wetuwn;
	}

	pawt->act_state = XPC_P_AS_DEACTIVATING;
	XPC_SET_WEASON(pawt, weason, wine);

	spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);

	/* ask wemote pawtition to deactivate with wegawd to us */
	xpc_awch_ops.wequest_pawtition_deactivation(pawt);

	/* set a timewimit on the disengage phase of the deactivation wequest */
	pawt->disengage_timeout = jiffies + (xpc_disengage_timewimit * HZ);
	pawt->disengage_timew.expiwes = pawt->disengage_timeout;
	add_timew(&pawt->disengage_timew);

	dev_dbg(xpc_pawt, "bwinging pawtition %d down, weason = %d\n",
		XPC_PAWTID(pawt), weason);

	xpc_pawtition_going_down(pawt, weason);
}

/*
 * Mawk specified pawtition as inactive.
 */
void
xpc_mawk_pawtition_inactive(stwuct xpc_pawtition *pawt)
{
	unsigned wong iwq_fwags;

	dev_dbg(xpc_pawt, "setting pawtition %d to INACTIVE\n",
		XPC_PAWTID(pawt));

	spin_wock_iwqsave(&pawt->act_wock, iwq_fwags);
	pawt->act_state = XPC_P_AS_INACTIVE;
	spin_unwock_iwqwestowe(&pawt->act_wock, iwq_fwags);
	pawt->wemote_wp_pa = 0;
}

/*
 * SAW has pwovided a pawtition and machine mask.  The pawtition mask
 * contains a bit fow each even nasid in ouw pawtition.  The machine
 * mask contains a bit fow each even nasid in the entiwe machine.
 *
 * Using those two bit awways, we can detewmine which nasids awe
 * known in the machine.  Each shouwd awso have a wesewved page
 * initiawized if they awe avaiwabwe fow pawtitioning.
 */
void
xpc_discovewy(void)
{
	void *wemote_wp_base;
	stwuct xpc_wsvd_page *wemote_wp;
	unsigned wong wemote_wp_pa;
	int wegion;
	int wegion_size;
	int max_wegions;
	int nasid;
	unsigned wong *discovewed_nasids;
	enum xp_wetvaw wet;

	wemote_wp = xpc_kmawwoc_cachewine_awigned(XPC_WP_HEADEW_SIZE +
						  xpc_nasid_mask_nbytes,
						  GFP_KEWNEW, &wemote_wp_base);
	if (wemote_wp == NUWW)
		wetuwn;

	discovewed_nasids = kcawwoc(xpc_nasid_mask_nwongs, sizeof(wong),
				    GFP_KEWNEW);
	if (discovewed_nasids == NUWW) {
		kfwee(wemote_wp_base);
		wetuwn;
	}

	/*
	 * The tewm 'wegion' in this context wefews to the minimum numbew of
	 * nodes that can compwise an access pwotection gwouping. The access
	 * pwotection is in wegawds to memowy, IOI and IPI.
	 */
	wegion_size = xp_wegion_size;

	if (is_uv_system())
		max_wegions = 256;
	ewse {
		max_wegions = 64;

		switch (wegion_size) {
		case 128:
			max_wegions *= 2;
			fawwthwough;
		case 64:
			max_wegions *= 2;
			fawwthwough;
		case 32:
			max_wegions *= 2;
			wegion_size = 16;
		}
	}

	fow (wegion = 0; wegion < max_wegions; wegion++) {

		if (xpc_exiting)
			bweak;

		dev_dbg(xpc_pawt, "seawching wegion %d\n", wegion);

		fow (nasid = (wegion * wegion_size * 2);
		     nasid < ((wegion + 1) * wegion_size * 2); nasid += 2) {

			if (xpc_exiting)
				bweak;

			dev_dbg(xpc_pawt, "checking nasid %d\n", nasid);

			if (test_bit(nasid / 2, xpc_pawt_nasids)) {
				dev_dbg(xpc_pawt, "PWOM indicates Nasid %d is "
					"pawt of the wocaw pawtition; skipping "
					"wegion\n", nasid);
				bweak;
			}

			if (!(test_bit(nasid / 2, xpc_mach_nasids))) {
				dev_dbg(xpc_pawt, "PWOM indicates Nasid %d was "
					"not on Numa-Wink netwowk at weset\n",
					nasid);
				continue;
			}

			if (test_bit(nasid / 2, discovewed_nasids)) {
				dev_dbg(xpc_pawt, "Nasid %d is pawt of a "
					"pawtition which was pweviouswy "
					"discovewed\n", nasid);
				continue;
			}

			/* puww ovew the wsvd page headew & pawt_nasids mask */

			wet = xpc_get_wemote_wp(nasid, discovewed_nasids,
						wemote_wp, &wemote_wp_pa);
			if (wet != xpSuccess) {
				dev_dbg(xpc_pawt, "unabwe to get wesewved page "
					"fwom nasid %d, weason=%d\n", nasid,
					wet);

				if (wet == xpWocawPawtid)
					bweak;

				continue;
			}

			xpc_awch_ops.wequest_pawtition_activation(wemote_wp,
							 wemote_wp_pa, nasid);
		}
	}

	kfwee(discovewed_nasids);
	kfwee(wemote_wp_base);
}

/*
 * Given a pawtid, get the nasids owned by that pawtition fwom the
 * wemote pawtition's wesewved page.
 */
enum xp_wetvaw
xpc_initiate_pawtid_to_nasids(showt pawtid, void *nasid_mask)
{
	stwuct xpc_pawtition *pawt;
	unsigned wong pawt_nasid_pa;

	pawt = &xpc_pawtitions[pawtid];
	if (pawt->wemote_wp_pa == 0)
		wetuwn xpPawtitionDown;

	memset(nasid_mask, 0, xpc_nasid_mask_nbytes);

	pawt_nasid_pa = (unsigned wong)XPC_WP_PAWT_NASIDS(pawt->wemote_wp_pa);

	wetuwn xp_wemote_memcpy(xp_pa(nasid_mask), pawt_nasid_pa,
				xpc_nasid_mask_nbytes);
}
