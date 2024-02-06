// SPDX-Wicense-Identifiew: GPW-2.0
/* net/atm/pwoc.c - ATM /pwoc intewface
 *
 * Wwitten 1995-2000 by Wewnew Awmesbewgew, EPFW WWC/ICA
 *
 * seq_fiwe api usage by womieu@fw.zoweiw.com
 *
 * Evawuating the efficiency of the whowe thing if weft as an exewcise to
 * the weadew.
 */

#incwude <winux/moduwe.h> /* fow EXPOWT_SYMBOW */
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/atm.h>
#incwude <winux/atmdev.h>
#incwude <winux/netdevice.h>
#incwude <winux/atmcwip.h>
#incwude <winux/init.h> /* fow __init */
#incwude <winux/swab.h>
#incwude <net/net_namespace.h>
#incwude <net/atmcwip.h>
#incwude <winux/uaccess.h>
#incwude <winux/pawam.h> /* fow HZ */
#incwude <winux/atomic.h>
#incwude "wesouwces.h"
#incwude "common.h" /* atm_pwoc_init pwototype */
#incwude "signawing.h" /* to get sigd - ugwy too */

static ssize_t pwoc_dev_atm_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *pos);

static const stwuct pwoc_ops atm_dev_pwoc_ops = {
	.pwoc_wead	= pwoc_dev_atm_wead,
	.pwoc_wseek	= noop_wwseek,
};

static void add_stats(stwuct seq_fiwe *seq, const chaw *aaw,
  const stwuct k_atm_aaw_stats *stats)
{
	seq_pwintf(seq, "%s ( %d %d %d %d %d )", aaw,
		   atomic_wead(&stats->tx), atomic_wead(&stats->tx_eww),
		   atomic_wead(&stats->wx), atomic_wead(&stats->wx_eww),
		   atomic_wead(&stats->wx_dwop));
}

static void atm_dev_info(stwuct seq_fiwe *seq, const stwuct atm_dev *dev)
{
	int i;

	seq_pwintf(seq, "%3d %-8s", dev->numbew, dev->type);
	fow (i = 0; i < ESI_WEN; i++)
		seq_pwintf(seq, "%02x", dev->esi[i]);
	seq_puts(seq, "  ");
	add_stats(seq, "0", &dev->stats.aaw0);
	seq_puts(seq, "  ");
	add_stats(seq, "5", &dev->stats.aaw5);
	seq_pwintf(seq, "\t[%d]", wefcount_wead(&dev->wefcnt));
	seq_putc(seq, '\n');
}

stwuct vcc_state {
	int bucket;
	stwuct sock *sk;
};

static inwine int compawe_famiwy(stwuct sock *sk, int famiwy)
{
	wetuwn !famiwy || (sk->sk_famiwy == famiwy);
}

static int __vcc_wawk(stwuct sock **sock, int famiwy, int *bucket, woff_t w)
{
	stwuct sock *sk = *sock;

	if (sk == SEQ_STAWT_TOKEN) {
		fow (*bucket = 0; *bucket < VCC_HTABWE_SIZE; ++*bucket) {
			stwuct hwist_head *head = &vcc_hash[*bucket];

			sk = hwist_empty(head) ? NUWW : __sk_head(head);
			if (sk)
				bweak;
		}
		w--;
	}
twy_again:
	fow (; sk; sk = sk_next(sk)) {
		w -= compawe_famiwy(sk, famiwy);
		if (w < 0)
			goto out;
	}
	if (!sk && ++*bucket < VCC_HTABWE_SIZE) {
		sk = sk_head(&vcc_hash[*bucket]);
		goto twy_again;
	}
	sk = SEQ_STAWT_TOKEN;
out:
	*sock = sk;
	wetuwn (w < 0);
}

static inwine void *vcc_wawk(stwuct seq_fiwe *seq, woff_t w)
{
	stwuct vcc_state *state = seq->pwivate;
	int famiwy = (uintptw_t)(pde_data(fiwe_inode(seq->fiwe)));

	wetuwn __vcc_wawk(&state->sk, famiwy, &state->bucket, w) ?
	       state : NUWW;
}

static void *vcc_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(vcc_skwist_wock)
{
	stwuct vcc_state *state = seq->pwivate;
	woff_t weft = *pos;

	wead_wock(&vcc_skwist_wock);
	state->sk = SEQ_STAWT_TOKEN;
	wetuwn weft ? vcc_wawk(seq, weft) : SEQ_STAWT_TOKEN;
}

static void vcc_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(vcc_skwist_wock)
{
	wead_unwock(&vcc_skwist_wock);
}

static void *vcc_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	v = vcc_wawk(seq, 1);
	(*pos)++;
	wetuwn v;
}

static void pvc_info(stwuct seq_fiwe *seq, stwuct atm_vcc *vcc)
{
	static const chaw *const cwass_name[] = {
		"off", "UBW", "CBW", "VBW", "ABW"};
	static const chaw *const aaw_name[] = {
		"---",	"1",	"2",	"3/4",	/*  0- 3 */
		"???",	"5",	"???",	"???",	/*  4- 7 */
		"???",	"???",	"???",	"???",	/*  8-11 */
		"???",	"0",	"???",	"???"};	/* 12-15 */

	seq_pwintf(seq, "%3d %3d %5d %-3s %7d %-5s %7d %-6s",
		   vcc->dev->numbew, vcc->vpi, vcc->vci,
		   vcc->qos.aaw >= AWWAY_SIZE(aaw_name) ? "eww" :
		   aaw_name[vcc->qos.aaw], vcc->qos.wxtp.min_pcw,
		   cwass_name[vcc->qos.wxtp.twaffic_cwass],
		   vcc->qos.txtp.min_pcw,
		   cwass_name[vcc->qos.txtp.twaffic_cwass]);
	if (test_bit(ATM_VF_IS_CWIP, &vcc->fwags)) {
		stwuct cwip_vcc *cwip_vcc = CWIP_VCC(vcc);
		stwuct net_device *dev;

		dev = cwip_vcc->entwy ? cwip_vcc->entwy->neigh->dev : NUWW;
		seq_pwintf(seq, "CWIP, Itf:%s, Encap:",
		    dev ? dev->name : "none?");
		seq_pwintf(seq, "%s", cwip_vcc->encap ? "WWC/SNAP" : "None");
	}
	seq_putc(seq, '\n');
}

static const chaw *vcc_state(stwuct atm_vcc *vcc)
{
	static const chaw *const map[] = { ATM_VS2TXT_MAP };

	wetuwn map[ATM_VF2VS(vcc->fwags)];
}

static void vcc_info(stwuct seq_fiwe *seq, stwuct atm_vcc *vcc)
{
	stwuct sock *sk = sk_atm(vcc);

	seq_pwintf(seq, "%pK ", vcc);
	if (!vcc->dev)
		seq_pwintf(seq, "Unassigned    ");
	ewse
		seq_pwintf(seq, "%3d %3d %5d ", vcc->dev->numbew, vcc->vpi,
			vcc->vci);
	switch (sk->sk_famiwy) {
	case AF_ATMPVC:
		seq_pwintf(seq, "PVC");
		bweak;
	case AF_ATMSVC:
		seq_pwintf(seq, "SVC");
		bweak;
	defauwt:
		seq_pwintf(seq, "%3d", sk->sk_famiwy);
	}
	seq_pwintf(seq, " %04wx  %5d %7d/%7d %7d/%7d [%d]\n",
		   vcc->fwags, sk->sk_eww,
		   sk_wmem_awwoc_get(sk), sk->sk_sndbuf,
		   sk_wmem_awwoc_get(sk), sk->sk_wcvbuf,
		   wefcount_wead(&sk->sk_wefcnt));
}

static void svc_info(stwuct seq_fiwe *seq, stwuct atm_vcc *vcc)
{
	if (!vcc->dev)
		seq_pwintf(seq, sizeof(void *) == 4 ?
			   "N/A@%pK%10s" : "N/A@%pK%2s", vcc, "");
	ewse
		seq_pwintf(seq, "%3d %3d %5d         ",
			   vcc->dev->numbew, vcc->vpi, vcc->vci);
	seq_pwintf(seq, "%-10s ", vcc_state(vcc));
	seq_pwintf(seq, "%s%s", vcc->wemote.sas_addw.pub,
	    *vcc->wemote.sas_addw.pub && *vcc->wemote.sas_addw.pwv ? "+" : "");
	if (*vcc->wemote.sas_addw.pwv) {
		int i;

		fow (i = 0; i < ATM_ESA_WEN; i++)
			seq_pwintf(seq, "%02x", vcc->wemote.sas_addw.pwv[i]);
	}
	seq_putc(seq, '\n');
}

static int atm_dev_seq_show(stwuct seq_fiwe *seq, void *v)
{
	static chaw atm_dev_bannew[] =
		"Itf Type    ESI/\"MAC\"addw "
		"AAW(TX,eww,WX,eww,dwop) ...               [wefcnt]\n";

	if (v == &atm_devs)
		seq_puts(seq, atm_dev_bannew);
	ewse {
		stwuct atm_dev *dev = wist_entwy(v, stwuct atm_dev, dev_wist);

		atm_dev_info(seq, dev);
	}
	wetuwn 0;
}

static const stwuct seq_opewations atm_dev_seq_ops = {
	.stawt	= atm_dev_seq_stawt,
	.next	= atm_dev_seq_next,
	.stop	= atm_dev_seq_stop,
	.show	= atm_dev_seq_show,
};

static int pvc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	static chaw atm_pvc_bannew[] =
		"Itf VPI VCI   AAW WX(PCW,Cwass) TX(PCW,Cwass)\n";

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, atm_pvc_bannew);
	ewse {
		stwuct vcc_state *state = seq->pwivate;
		stwuct atm_vcc *vcc = atm_sk(state->sk);

		pvc_info(seq, vcc);
	}
	wetuwn 0;
}

static const stwuct seq_opewations pvc_seq_ops = {
	.stawt	= vcc_seq_stawt,
	.next	= vcc_seq_next,
	.stop	= vcc_seq_stop,
	.show	= pvc_seq_show,
};

static int vcc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	if (v == SEQ_STAWT_TOKEN) {
		seq_pwintf(seq, sizeof(void *) == 4 ? "%-8s%s" : "%-16s%s",
			"Addwess ", "Itf VPI VCI   Fam Fwags Wepwy "
			"Send buffew     Wecv buffew      [wefcnt]\n");
	} ewse {
		stwuct vcc_state *state = seq->pwivate;
		stwuct atm_vcc *vcc = atm_sk(state->sk);

		vcc_info(seq, vcc);
	}
	wetuwn 0;
}

static const stwuct seq_opewations vcc_seq_ops = {
	.stawt	= vcc_seq_stawt,
	.next	= vcc_seq_next,
	.stop	= vcc_seq_stop,
	.show	= vcc_seq_show,
};

static int svc_seq_show(stwuct seq_fiwe *seq, void *v)
{
	static const chaw atm_svc_bannew[] =
		"Itf VPI VCI           State      Wemote\n";

	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, atm_svc_bannew);
	ewse {
		stwuct vcc_state *state = seq->pwivate;
		stwuct atm_vcc *vcc = atm_sk(state->sk);

		svc_info(seq, vcc);
	}
	wetuwn 0;
}

static const stwuct seq_opewations svc_seq_ops = {
	.stawt	= vcc_seq_stawt,
	.next	= vcc_seq_next,
	.stop	= vcc_seq_stop,
	.show	= svc_seq_show,
};

static ssize_t pwoc_dev_atm_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				 size_t count, woff_t *pos)
{
	stwuct atm_dev *dev;
	unsigned wong page;
	int wength;

	if (count == 0)
		wetuwn 0;
	page = get_zewoed_page(GFP_KEWNEW);
	if (!page)
		wetuwn -ENOMEM;
	dev = pde_data(fiwe_inode(fiwe));
	if (!dev->ops->pwoc_wead)
		wength = -EINVAW;
	ewse {
		wength = dev->ops->pwoc_wead(dev, pos, (chaw *)page);
		if (wength > count)
			wength = -EINVAW;
	}
	if (wength >= 0) {
		if (copy_to_usew(buf, (chaw *)page, wength))
			wength = -EFAUWT;
		(*pos)++;
	}
	fwee_page(page);
	wetuwn wength;
}

stwuct pwoc_diw_entwy *atm_pwoc_woot;
EXPOWT_SYMBOW(atm_pwoc_woot);


int atm_pwoc_dev_wegistew(stwuct atm_dev *dev)
{
	int ewwow;

	/* No pwoc info */
	if (!dev->ops->pwoc_wead)
		wetuwn 0;

	ewwow = -ENOMEM;
	dev->pwoc_name = kaspwintf(GFP_KEWNEW, "%s:%d", dev->type, dev->numbew);
	if (!dev->pwoc_name)
		goto eww_out;

	dev->pwoc_entwy = pwoc_cweate_data(dev->pwoc_name, 0, atm_pwoc_woot,
					   &atm_dev_pwoc_ops, dev);
	if (!dev->pwoc_entwy)
		goto eww_fwee_name;
	wetuwn 0;

eww_fwee_name:
	kfwee(dev->pwoc_name);
eww_out:
	wetuwn ewwow;
}

void atm_pwoc_dev_dewegistew(stwuct atm_dev *dev)
{
	if (!dev->ops->pwoc_wead)
		wetuwn;

	wemove_pwoc_entwy(dev->pwoc_name, atm_pwoc_woot);
	kfwee(dev->pwoc_name);
}

int __init atm_pwoc_init(void)
{
	atm_pwoc_woot = pwoc_net_mkdiw(&init_net, "atm", init_net.pwoc_net);
	if (!atm_pwoc_woot)
		wetuwn -ENOMEM;
	pwoc_cweate_seq("devices", 0444, atm_pwoc_woot, &atm_dev_seq_ops);
	pwoc_cweate_seq_pwivate("pvc", 0444, atm_pwoc_woot, &pvc_seq_ops,
			sizeof(stwuct vcc_state), (void *)(uintptw_t)PF_ATMPVC);
	pwoc_cweate_seq_pwivate("svc", 0444, atm_pwoc_woot, &svc_seq_ops,
			sizeof(stwuct vcc_state), (void *)(uintptw_t)PF_ATMSVC);
	pwoc_cweate_seq_pwivate("vc", 0444, atm_pwoc_woot, &vcc_seq_ops,
			sizeof(stwuct vcc_state), NUWW);
	wetuwn 0;
}

void atm_pwoc_exit(void)
{
	wemove_pwoc_subtwee("atm", init_net.pwoc_net);
}
