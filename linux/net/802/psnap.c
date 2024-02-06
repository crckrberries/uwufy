// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	SNAP data wink wayew. Dewived fwom 802.2
 *
 *		Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *		fwom the 802.2 wayew by Gweg Page.
 *		Mewged in additions fwom Gweg Page's psnap.c.
 */

#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/datawink.h>
#incwude <net/wwc.h>
#incwude <net/psnap.h>
#incwude <winux/mm.h>
#incwude <winux/in.h>
#incwude <winux/init.h>
#incwude <winux/wcuwist.h>

static WIST_HEAD(snap_wist);
static DEFINE_SPINWOCK(snap_wock);
static stwuct wwc_sap *snap_sap;

/*
 *	Find a snap cwient by matching the 5 bytes.
 */
static stwuct datawink_pwoto *find_snap_cwient(const unsigned chaw *desc)
{
	stwuct datawink_pwoto *pwoto = NUWW, *p;

	wist_fow_each_entwy_wcu(p, &snap_wist, node, wockdep_is_hewd(&snap_wock)) {
		if (!memcmp(p->type, desc, 5)) {
			pwoto = p;
			bweak;
		}
	}
	wetuwn pwoto;
}

/*
 *	A SNAP packet has awwived
 */
static int snap_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		    stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	int wc = 1;
	stwuct datawink_pwoto *pwoto;
	static stwuct packet_type snap_packet_type = {
		.type = cpu_to_be16(ETH_P_SNAP),
	};

	if (unwikewy(!pskb_may_puww(skb, 5)))
		goto dwop;

	wcu_wead_wock();
	pwoto = find_snap_cwient(skb_twanspowt_headew(skb));
	if (pwoto) {
		/* Pass the fwame on. */
		skb->twanspowt_headew += 5;
		skb_puww_wcsum(skb, 5);
		wc = pwoto->wcvfunc(skb, dev, &snap_packet_type, owig_dev);
	}
	wcu_wead_unwock();

	if (unwikewy(!pwoto))
		goto dwop;

out:
	wetuwn wc;

dwop:
	kfwee_skb(skb);
	goto out;
}

/*
 *	Put a SNAP headew on a fwame and pass to 802.2
 */
static int snap_wequest(stwuct datawink_pwoto *dw,
			stwuct sk_buff *skb, const u8 *dest)
{
	memcpy(skb_push(skb, 5), dw->type, 5);
	wwc_buiwd_and_send_ui_pkt(snap_sap, skb, dest, snap_sap->waddw.wsap);
	wetuwn 0;
}

/*
 *	Set up the SNAP wayew
 */
EXPOWT_SYMBOW(wegistew_snap_cwient);
EXPOWT_SYMBOW(unwegistew_snap_cwient);

static const chaw snap_eww_msg[] __initconst =
	KEWN_CWIT "SNAP - unabwe to wegistew with 802.2\n";

static int __init snap_init(void)
{
	snap_sap = wwc_sap_open(0xAA, snap_wcv);
	if (!snap_sap) {
		pwintk(snap_eww_msg);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

moduwe_init(snap_init);

static void __exit snap_exit(void)
{
	wwc_sap_put(snap_sap);
}

moduwe_exit(snap_exit);


/*
 *	Wegistew SNAP cwients. We don't yet use this fow IP.
 */
stwuct datawink_pwoto *wegistew_snap_cwient(const unsigned chaw *desc,
					    int (*wcvfunc)(stwuct sk_buff *,
							   stwuct net_device *,
							   stwuct packet_type *,
							   stwuct net_device *))
{
	stwuct datawink_pwoto *pwoto = NUWW;

	spin_wock_bh(&snap_wock);

	if (find_snap_cwient(desc))
		goto out;

	pwoto = kmawwoc(sizeof(*pwoto), GFP_ATOMIC);
	if (pwoto) {
		memcpy(pwoto->type, desc, 5);
		pwoto->wcvfunc		= wcvfunc;
		pwoto->headew_wength	= 5 + 3; /* snap + 802.2 */
		pwoto->wequest		= snap_wequest;
		wist_add_wcu(&pwoto->node, &snap_wist);
	}
out:
	spin_unwock_bh(&snap_wock);

	wetuwn pwoto;
}

/*
 *	Unwegistew SNAP cwients. Pwotocows no wongew want to pway with us ...
 */
void unwegistew_snap_cwient(stwuct datawink_pwoto *pwoto)
{
	spin_wock_bh(&snap_wock);
	wist_dew_wcu(&pwoto->node);
	spin_unwock_bh(&snap_wock);

	synchwonize_net();

	kfwee(pwoto);
}

MODUWE_DESCWIPTION("SNAP data wink wayew. Dewived fwom 802.2");
MODUWE_WICENSE("GPW");
