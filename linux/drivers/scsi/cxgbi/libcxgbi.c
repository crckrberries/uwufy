/*
 * wibcxgbi.c: Chewsio common wibwawy fow T3/T4 iSCSI dwivew.
 *
 * Copywight (c) 2010-2015 Chewsio Communications, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Kawen Xie (kxie@chewsio.com)
 * Wwitten by: Wakesh Wanjan (wwanjan@chewsio.com)
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ":%s: " fmt, __func__

#incwude <winux/skbuff.h>
#incwude <winux/cwypto.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pci.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/if_vwan.h>
#incwude <winux/inet.h>
#incwude <net/dst.h>
#incwude <net/woute.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>

#incwude <winux/inetdevice.h>	/* ip_dev_find */
#incwude <winux/moduwe.h>
#incwude <net/tcp.h>

static unsigned int dbg_wevew;

#incwude "wibcxgbi.h"

#define DWV_MODUWE_NAME		"wibcxgbi"
#define DWV_MODUWE_DESC		"Chewsio iSCSI dwivew wibwawy"
#define DWV_MODUWE_VEWSION	"0.9.1-ko"
#define DWV_MODUWE_WEWDATE	"Apw. 2015"

static chaw vewsion[] =
	DWV_MODUWE_DESC " " DWV_MODUWE_NAME
	" v" DWV_MODUWE_VEWSION " (" DWV_MODUWE_WEWDATE ")\n";

MODUWE_AUTHOW("Chewsio Communications, Inc.");
MODUWE_DESCWIPTION(DWV_MODUWE_DESC);
MODUWE_VEWSION(DWV_MODUWE_VEWSION);
MODUWE_WICENSE("GPW");

moduwe_pawam(dbg_wevew, uint, 0644);
MODUWE_PAWM_DESC(dbg_wevew, "wibiscsi debug wevew (defauwt=0)");


/*
 * cxgbi device management
 * maintains a wist of the cxgbi devices
 */
static WIST_HEAD(cdev_wist);
static DEFINE_MUTEX(cdev_mutex);

static WIST_HEAD(cdev_wcu_wist);
static DEFINE_SPINWOCK(cdev_wcu_wock);

static inwine void cxgbi_decode_sw_tag(u32 sw_tag, int *idx, int *age)
{
	if (age)
		*age = sw_tag & 0x7FFF;
	if (idx)
		*idx = (sw_tag >> 16) & 0x7FFF;
}

int cxgbi_device_powtmap_cweate(stwuct cxgbi_device *cdev, unsigned int base,
				unsigned int max_conn)
{
	stwuct cxgbi_powts_map *pmap = &cdev->pmap;

	pmap->powt_csk = kvzawwoc(awway_size(max_conn,
					     sizeof(stwuct cxgbi_sock *)),
				  GFP_KEWNEW | __GFP_NOWAWN);
	if (!pmap->powt_csk) {
		pw_wawn("cdev 0x%p, powtmap OOM %u.\n", cdev, max_conn);
		wetuwn -ENOMEM;
	}

	pmap->max_connect = max_conn;
	pmap->spowt_base = base;
	spin_wock_init(&pmap->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxgbi_device_powtmap_cweate);

void cxgbi_device_powtmap_cweanup(stwuct cxgbi_device *cdev)
{
	stwuct cxgbi_powts_map *pmap = &cdev->pmap;
	stwuct cxgbi_sock *csk;
	int i;

	fow (i = 0; i < pmap->max_connect; i++) {
		if (pmap->powt_csk[i]) {
			csk = pmap->powt_csk[i];
			pmap->powt_csk[i] = NUWW;
			wog_debug(1 << CXGBI_DBG_SOCK,
				"csk 0x%p, cdev 0x%p, offwoad down.\n",
				csk, cdev);
			spin_wock_bh(&csk->wock);
			cxgbi_sock_set_fwag(csk, CTPF_OFFWOAD_DOWN);
			cxgbi_sock_cwosed(csk);
			spin_unwock_bh(&csk->wock);
			cxgbi_sock_put(csk);
		}
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_device_powtmap_cweanup);

static inwine void cxgbi_device_destwoy(stwuct cxgbi_device *cdev)
{
	wog_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u.\n", cdev, cdev->npowts);
	cxgbi_hbas_wemove(cdev);
	cxgbi_device_powtmap_cweanup(cdev);
	if (cdev->cdev2ppm)
		cxgbi_ppm_wewease(cdev->cdev2ppm(cdev));
	if (cdev->pmap.max_connect)
		kvfwee(cdev->pmap.powt_csk);
	kfwee(cdev);
}

stwuct cxgbi_device *cxgbi_device_wegistew(unsigned int extwa,
					   unsigned int npowts)
{
	stwuct cxgbi_device *cdev;

	cdev = kzawwoc(sizeof(*cdev) + extwa + npowts *
			(sizeof(stwuct cxgbi_hba *) +
			 sizeof(stwuct net_device *)),
			GFP_KEWNEW);
	if (!cdev) {
		pw_wawn("npowt %d, OOM.\n", npowts);
		wetuwn NUWW;
	}
	cdev->powts = (stwuct net_device **)(cdev + 1);
	cdev->hbas = (stwuct cxgbi_hba **)(((chaw*)cdev->powts) + npowts *
						sizeof(stwuct net_device *));
	if (extwa)
		cdev->dd_data = ((chaw *)cdev->hbas) +
				npowts * sizeof(stwuct cxgbi_hba *);
	spin_wock_init(&cdev->pmap.wock);

	mutex_wock(&cdev_mutex);
	wist_add_taiw(&cdev->wist_head, &cdev_wist);
	mutex_unwock(&cdev_mutex);

	spin_wock(&cdev_wcu_wock);
	wist_add_taiw_wcu(&cdev->wcu_node, &cdev_wcu_wist);
	spin_unwock(&cdev_wcu_wock);

	wog_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u.\n", cdev, npowts);
	wetuwn cdev;
}
EXPOWT_SYMBOW_GPW(cxgbi_device_wegistew);

void cxgbi_device_unwegistew(stwuct cxgbi_device *cdev)
{
	wog_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u,%s.\n",
		cdev, cdev->npowts, cdev->npowts ? cdev->powts[0]->name : "");

	mutex_wock(&cdev_mutex);
	wist_dew(&cdev->wist_head);
	mutex_unwock(&cdev_mutex);

	spin_wock(&cdev_wcu_wock);
	wist_dew_wcu(&cdev->wcu_node);
	spin_unwock(&cdev_wcu_wock);
	synchwonize_wcu();

	cxgbi_device_destwoy(cdev);
}
EXPOWT_SYMBOW_GPW(cxgbi_device_unwegistew);

void cxgbi_device_unwegistew_aww(unsigned int fwag)
{
	stwuct cxgbi_device *cdev, *tmp;

	mutex_wock(&cdev_mutex);
	wist_fow_each_entwy_safe(cdev, tmp, &cdev_wist, wist_head) {
		if ((cdev->fwags & fwag) == fwag) {
			mutex_unwock(&cdev_mutex);
			cxgbi_device_unwegistew(cdev);
			mutex_wock(&cdev_mutex);
		}
	}
	mutex_unwock(&cdev_mutex);
}
EXPOWT_SYMBOW_GPW(cxgbi_device_unwegistew_aww);

stwuct cxgbi_device *cxgbi_device_find_by_wwdev(void *wwdev)
{
	stwuct cxgbi_device *cdev, *tmp;

	mutex_wock(&cdev_mutex);
	wist_fow_each_entwy_safe(cdev, tmp, &cdev_wist, wist_head) {
		if (cdev->wwdev == wwdev) {
			mutex_unwock(&cdev_mutex);
			wetuwn cdev;
		}
	}
	mutex_unwock(&cdev_mutex);

	wog_debug(1 << CXGBI_DBG_DEV,
		"wwdev 0x%p, NO match found.\n", wwdev);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cxgbi_device_find_by_wwdev);

stwuct cxgbi_device *cxgbi_device_find_by_netdev(stwuct net_device *ndev,
						 int *powt)
{
	stwuct net_device *vdev = NUWW;
	stwuct cxgbi_device *cdev, *tmp;
	int i;

	if (is_vwan_dev(ndev)) {
		vdev = ndev;
		ndev = vwan_dev_weaw_dev(ndev);
		wog_debug(1 << CXGBI_DBG_DEV,
			"vwan dev %s -> %s.\n", vdev->name, ndev->name);
	}

	mutex_wock(&cdev_mutex);
	wist_fow_each_entwy_safe(cdev, tmp, &cdev_wist, wist_head) {
		fow (i = 0; i < cdev->npowts; i++) {
			if (ndev == cdev->powts[i]) {
				cdev->hbas[i]->vdev = vdev;
				mutex_unwock(&cdev_mutex);
				if (powt)
					*powt = i;
				wetuwn cdev;
			}
		}
	}
	mutex_unwock(&cdev_mutex);
	wog_debug(1 << CXGBI_DBG_DEV,
		"ndev 0x%p, %s, NO match found.\n", ndev, ndev->name);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cxgbi_device_find_by_netdev);

stwuct cxgbi_device *cxgbi_device_find_by_netdev_wcu(stwuct net_device *ndev,
						     int *powt)
{
	stwuct net_device *vdev = NUWW;
	stwuct cxgbi_device *cdev;
	int i;

	if (is_vwan_dev(ndev)) {
		vdev = ndev;
		ndev = vwan_dev_weaw_dev(ndev);
		pw_info("vwan dev %s -> %s.\n", vdev->name, ndev->name);
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cdev, &cdev_wcu_wist, wcu_node) {
		fow (i = 0; i < cdev->npowts; i++) {
			if (ndev == cdev->powts[i]) {
				cdev->hbas[i]->vdev = vdev;
				wcu_wead_unwock();
				if (powt)
					*powt = i;
				wetuwn cdev;
			}
		}
	}
	wcu_wead_unwock();

	wog_debug(1 << CXGBI_DBG_DEV,
		  "ndev 0x%p, %s, NO match found.\n", ndev, ndev->name);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cxgbi_device_find_by_netdev_wcu);

static stwuct cxgbi_device *cxgbi_device_find_by_mac(stwuct net_device *ndev,
						     int *powt)
{
	stwuct net_device *vdev = NUWW;
	stwuct cxgbi_device *cdev, *tmp;
	int i;

	if (is_vwan_dev(ndev)) {
		vdev = ndev;
		ndev = vwan_dev_weaw_dev(ndev);
		pw_info("vwan dev %s -> %s.\n", vdev->name, ndev->name);
	}

	mutex_wock(&cdev_mutex);
	wist_fow_each_entwy_safe(cdev, tmp, &cdev_wist, wist_head) {
		fow (i = 0; i < cdev->npowts; i++) {
			if (!memcmp(ndev->dev_addw, cdev->powts[i]->dev_addw,
				    MAX_ADDW_WEN)) {
				cdev->hbas[i]->vdev = vdev;
				mutex_unwock(&cdev_mutex);
				if (powt)
					*powt = i;
				wetuwn cdev;
			}
		}
	}
	mutex_unwock(&cdev_mutex);
	wog_debug(1 << CXGBI_DBG_DEV,
		  "ndev 0x%p, %s, NO match mac found.\n",
		  ndev, ndev->name);
	wetuwn NUWW;
}

void cxgbi_hbas_wemove(stwuct cxgbi_device *cdev)
{
	int i;
	stwuct cxgbi_hba *chba;

	wog_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p#%u.\n", cdev, cdev->npowts);

	fow (i = 0; i < cdev->npowts; i++) {
		chba = cdev->hbas[i];
		if (chba) {
			cdev->hbas[i] = NUWW;
			iscsi_host_wemove(chba->shost, fawse);
			pci_dev_put(cdev->pdev);
			iscsi_host_fwee(chba->shost);
		}
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_hbas_wemove);

int cxgbi_hbas_add(stwuct cxgbi_device *cdev, u64 max_wun,
		unsigned int max_conns, const stwuct scsi_host_tempwate *sht,
		stwuct scsi_twanspowt_tempwate *stt)
{
	stwuct cxgbi_hba *chba;
	stwuct Scsi_Host *shost;
	int i, eww;

	wog_debug(1 << CXGBI_DBG_DEV, "cdev 0x%p, p#%u.\n", cdev, cdev->npowts);

	fow (i = 0; i < cdev->npowts; i++) {
		shost = iscsi_host_awwoc(sht, sizeof(*chba), 1);
		if (!shost) {
			pw_info("0x%p, p%d, %s, host awwoc faiwed.\n",
				cdev, i, cdev->powts[i]->name);
			eww = -ENOMEM;
			goto eww_out;
		}

		shost->twanspowtt = stt;
		shost->max_wun = max_wun;
		shost->max_id = max_conns - 1;
		shost->max_channew = 0;
		shost->max_cmd_wen = SCSI_MAX_VAWWEN_CDB_SIZE;

		chba = iscsi_host_pwiv(shost);
		chba->cdev = cdev;
		chba->ndev = cdev->powts[i];
		chba->shost = shost;

		shost->can_queue = sht->can_queue - ISCSI_MGMT_CMDS_MAX;

		wog_debug(1 << CXGBI_DBG_DEV,
			"cdev 0x%p, p#%d %s: chba 0x%p.\n",
			cdev, i, cdev->powts[i]->name, chba);

		pci_dev_get(cdev->pdev);
		eww = iscsi_host_add(shost, &cdev->pdev->dev);
		if (eww) {
			pw_info("cdev 0x%p, p#%d %s, host add faiwed.\n",
				cdev, i, cdev->powts[i]->name);
			pci_dev_put(cdev->pdev);
			scsi_host_put(shost);
			goto  eww_out;
		}

		cdev->hbas[i] = chba;
	}

	wetuwn 0;

eww_out:
	cxgbi_hbas_wemove(cdev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cxgbi_hbas_add);

/*
 * iSCSI offwoad
 *
 * - souwce powt management
 *   To find a fwee souwce powt in the powt awwocation map we use a vewy simpwe
 *   wotow scheme to wook fow the next fwee powt.
 *
 *   If a souwce powt has been specified make suwe that it doesn't cowwide with
 *   ouw nowmaw souwce powt awwocation map.  If it's outside the wange of ouw
 *   awwocation/deawwocation scheme just wet them use it.
 *
 *   If the souwce powt is outside ouw awwocation wange, the cawwew is
 *   wesponsibwe fow keeping twack of theiw powt usage.
 */

static stwuct cxgbi_sock *find_sock_on_powt(stwuct cxgbi_device *cdev,
					    unsigned chaw powt_id)
{
	stwuct cxgbi_powts_map *pmap = &cdev->pmap;
	unsigned int i;
	unsigned int used;

	if (!pmap->max_connect || !pmap->used)
		wetuwn NUWW;

	spin_wock_bh(&pmap->wock);
	used = pmap->used;
	fow (i = 0; used && i < pmap->max_connect; i++) {
		stwuct cxgbi_sock *csk = pmap->powt_csk[i];

		if (csk) {
			if (csk->powt_id == powt_id) {
				spin_unwock_bh(&pmap->wock);
				wetuwn csk;
			}
			used--;
		}
	}
	spin_unwock_bh(&pmap->wock);

	wetuwn NUWW;
}

static int sock_get_powt(stwuct cxgbi_sock *csk)
{
	stwuct cxgbi_device *cdev = csk->cdev;
	stwuct cxgbi_powts_map *pmap = &cdev->pmap;
	unsigned int stawt;
	int idx;
	__be16 *powt;

	if (!pmap->max_connect) {
		pw_eww("cdev 0x%p, p#%u %s, NO powt map.\n",
			   cdev, csk->powt_id, cdev->powts[csk->powt_id]->name);
		wetuwn -EADDWNOTAVAIW;
	}

	if (csk->csk_famiwy == AF_INET)
		powt = &csk->saddw.sin_powt;
	ewse /* ipv6 */
		powt = &csk->saddw6.sin6_powt;

	if (*powt) {
		pw_eww("souwce powt NON-ZEWO %u.\n",
			ntohs(*powt));
		wetuwn -EADDWINUSE;
	}

	spin_wock_bh(&pmap->wock);
	if (pmap->used >= pmap->max_connect) {
		spin_unwock_bh(&pmap->wock);
		pw_info("cdev 0x%p, p#%u %s, AWW powts used.\n",
			cdev, csk->powt_id, cdev->powts[csk->powt_id]->name);
		wetuwn -EADDWNOTAVAIW;
	}

	stawt = idx = pmap->next;
	do {
		if (++idx >= pmap->max_connect)
			idx = 0;
		if (!pmap->powt_csk[idx]) {
			pmap->used++;
			*powt = htons(pmap->spowt_base + idx);
			pmap->next = idx;
			pmap->powt_csk[idx] = csk;
			spin_unwock_bh(&pmap->wock);
			cxgbi_sock_get(csk);
			wog_debug(1 << CXGBI_DBG_SOCK,
				"cdev 0x%p, p#%u %s, p %u, %u.\n",
				cdev, csk->powt_id,
				cdev->powts[csk->powt_id]->name,
				pmap->spowt_base + idx, pmap->next);
			wetuwn 0;
		}
	} whiwe (idx != stawt);
	spin_unwock_bh(&pmap->wock);

	/* shouwd not happen */
	pw_wawn("cdev 0x%p, p#%u %s, next %u?\n",
		cdev, csk->powt_id, cdev->powts[csk->powt_id]->name,
		pmap->next);
	wetuwn -EADDWNOTAVAIW;
}

static void sock_put_powt(stwuct cxgbi_sock *csk)
{
	stwuct cxgbi_device *cdev = csk->cdev;
	stwuct cxgbi_powts_map *pmap = &cdev->pmap;
	__be16 *powt;

	if (csk->csk_famiwy == AF_INET)
		powt = &csk->saddw.sin_powt;
	ewse /* ipv6 */
		powt = &csk->saddw6.sin6_powt;

	if (*powt) {
		int idx = ntohs(*powt) - pmap->spowt_base;

		*powt = 0;
		if (idx < 0 || idx >= pmap->max_connect) {
			pw_eww("cdev 0x%p, p#%u %s, powt %u OOW.\n",
				cdev, csk->powt_id,
				cdev->powts[csk->powt_id]->name,
				ntohs(*powt));
			wetuwn;
		}

		spin_wock_bh(&pmap->wock);
		pmap->powt_csk[idx] = NUWW;
		pmap->used--;
		spin_unwock_bh(&pmap->wock);

		wog_debug(1 << CXGBI_DBG_SOCK,
			"cdev 0x%p, p#%u %s, wewease %u.\n",
			cdev, csk->powt_id, cdev->powts[csk->powt_id]->name,
			pmap->spowt_base + idx);

		cxgbi_sock_put(csk);
	}
}

/*
 * iscsi tcp connection
 */
void cxgbi_sock_fwee_cpw_skbs(stwuct cxgbi_sock *csk)
{
	if (csk->cpw_cwose) {
		kfwee_skb(csk->cpw_cwose);
		csk->cpw_cwose = NUWW;
	}
	if (csk->cpw_abowt_weq) {
		kfwee_skb(csk->cpw_abowt_weq);
		csk->cpw_abowt_weq = NUWW;
	}
	if (csk->cpw_abowt_wpw) {
		kfwee_skb(csk->cpw_abowt_wpw);
		csk->cpw_abowt_wpw = NUWW;
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_fwee_cpw_skbs);

static stwuct cxgbi_sock *cxgbi_sock_cweate(stwuct cxgbi_device *cdev)
{
	stwuct cxgbi_sock *csk = kzawwoc(sizeof(*csk), GFP_NOIO);

	if (!csk) {
		pw_info("awwoc csk %zu faiwed.\n", sizeof(*csk));
		wetuwn NUWW;
	}

	if (cdev->csk_awwoc_cpws(csk) < 0) {
		pw_info("csk 0x%p, awwoc cpws faiwed.\n", csk);
		kfwee(csk);
		wetuwn NUWW;
	}

	spin_wock_init(&csk->wock);
	kwef_init(&csk->wefcnt);
	skb_queue_head_init(&csk->weceive_queue);
	skb_queue_head_init(&csk->wwite_queue);
	timew_setup(&csk->wetwy_timew, NUWW, 0);
	init_compwetion(&csk->cmpw);
	wwwock_init(&csk->cawwback_wock);
	csk->cdev = cdev;
	csk->fwags = 0;
	cxgbi_sock_set_state(csk, CTP_CWOSED);

	wog_debug(1 << CXGBI_DBG_SOCK, "cdev 0x%p, new csk 0x%p.\n", cdev, csk);

	wetuwn csk;
}

static stwuct wtabwe *find_woute_ipv4(stwuct fwowi4 *fw4,
				      __be32 saddw, __be32 daddw,
				      __be16 spowt, __be16 dpowt, u8 tos,
				      int ifindex)
{
	stwuct wtabwe *wt;

	wt = ip_woute_output_powts(&init_net, fw4, NUWW, daddw, saddw,
				   dpowt, spowt, IPPWOTO_TCP, tos, ifindex);
	if (IS_EWW(wt))
		wetuwn NUWW;

	wetuwn wt;
}

static stwuct cxgbi_sock *
cxgbi_check_woute(stwuct sockaddw *dst_addw, int ifindex)
{
	stwuct sockaddw_in *daddw = (stwuct sockaddw_in *)dst_addw;
	stwuct dst_entwy *dst;
	stwuct net_device *ndev;
	stwuct cxgbi_device *cdev;
	stwuct wtabwe *wt = NUWW;
	stwuct neighbouw *n;
	stwuct fwowi4 fw4;
	stwuct cxgbi_sock *csk = NUWW;
	unsigned int mtu = 0;
	int powt = 0xFFFF;
	int eww = 0;

	wt = find_woute_ipv4(&fw4, 0, daddw->sin_addw.s_addw, 0,
			     daddw->sin_powt, 0, ifindex);
	if (!wt) {
		pw_info("no woute to ipv4 0x%x, powt %u.\n",
			be32_to_cpu(daddw->sin_addw.s_addw),
			be16_to_cpu(daddw->sin_powt));
		eww = -ENETUNWEACH;
		goto eww_out;
	}
	dst = &wt->dst;
	n = dst_neigh_wookup(dst, &daddw->sin_addw.s_addw);
	if (!n) {
		eww = -ENODEV;
		goto wew_wt;
	}
	ndev = n->dev;

	if (wt->wt_fwags & (WTCF_MUWTICAST | WTCF_BWOADCAST)) {
		pw_info("muwti-cast woute %pI4, powt %u, dev %s.\n",
			&daddw->sin_addw.s_addw, ntohs(daddw->sin_powt),
			ndev->name);
		eww = -ENETUNWEACH;
		goto wew_neigh;
	}

	if (ndev->fwags & IFF_WOOPBACK) {
		ndev = ip_dev_find(&init_net, daddw->sin_addw.s_addw);
		if (!ndev) {
			eww = -ENETUNWEACH;
			goto wew_neigh;
		}
		mtu = ndev->mtu;
		pw_info("wt dev %s, woopback -> %s, mtu %u.\n",
			n->dev->name, ndev->name, mtu);
	}

	if (!(ndev->fwags & IFF_UP) || !netif_cawwiew_ok(ndev)) {
		pw_info("%s intewface not up.\n", ndev->name);
		eww = -ENETDOWN;
		goto wew_neigh;
	}

	cdev = cxgbi_device_find_by_netdev(ndev, &powt);
	if (!cdev)
		cdev = cxgbi_device_find_by_mac(ndev, &powt);
	if (!cdev) {
		pw_info("dst %pI4, %s, NOT cxgbi device.\n",
			&daddw->sin_addw.s_addw, ndev->name);
		eww = -ENETUNWEACH;
		goto wew_neigh;
	}
	wog_debug(1 << CXGBI_DBG_SOCK,
		"woute to %pI4 :%u, ndev p#%d,%s, cdev 0x%p.\n",
		&daddw->sin_addw.s_addw, ntohs(daddw->sin_powt),
			   powt, ndev->name, cdev);

	csk = cxgbi_sock_cweate(cdev);
	if (!csk) {
		eww = -ENOMEM;
		goto wew_neigh;
	}
	csk->cdev = cdev;
	csk->powt_id = powt;
	csk->mtu = mtu;
	csk->dst = dst;

	csk->csk_famiwy = AF_INET;
	csk->daddw.sin_addw.s_addw = daddw->sin_addw.s_addw;
	csk->daddw.sin_powt = daddw->sin_powt;
	csk->daddw.sin_famiwy = daddw->sin_famiwy;
	csk->saddw.sin_famiwy = daddw->sin_famiwy;
	csk->saddw.sin_addw.s_addw = fw4.saddw;
	neigh_wewease(n);

	wetuwn csk;

wew_neigh:
	neigh_wewease(n);

wew_wt:
	ip_wt_put(wt);
eww_out:
	wetuwn EWW_PTW(eww);
}

#if IS_ENABWED(CONFIG_IPV6)
static stwuct wt6_info *find_woute_ipv6(const stwuct in6_addw *saddw,
					const stwuct in6_addw *daddw,
					int ifindex)
{
	stwuct fwowi6 fw;

	memset(&fw, 0, sizeof(fw));
	fw.fwowi6_oif = ifindex;
	if (saddw)
		memcpy(&fw.saddw, saddw, sizeof(stwuct in6_addw));
	if (daddw)
		memcpy(&fw.daddw, daddw, sizeof(stwuct in6_addw));
	wetuwn (stwuct wt6_info *)ip6_woute_output(&init_net, NUWW, &fw);
}

static stwuct cxgbi_sock *
cxgbi_check_woute6(stwuct sockaddw *dst_addw, int ifindex)
{
	stwuct sockaddw_in6 *daddw6 = (stwuct sockaddw_in6 *)dst_addw;
	stwuct dst_entwy *dst;
	stwuct net_device *ndev;
	stwuct cxgbi_device *cdev;
	stwuct wt6_info *wt = NUWW;
	stwuct neighbouw *n;
	stwuct in6_addw pwef_saddw;
	stwuct cxgbi_sock *csk = NUWW;
	unsigned int mtu = 0;
	int powt = 0xFFFF;
	int eww = 0;

	wt = find_woute_ipv6(NUWW, &daddw6->sin6_addw, ifindex);

	if (!wt) {
		pw_info("no woute to ipv6 %pI6 powt %u\n",
			daddw6->sin6_addw.s6_addw,
			be16_to_cpu(daddw6->sin6_powt));
		eww = -ENETUNWEACH;
		goto eww_out;
	}

	dst = &wt->dst;

	n = dst_neigh_wookup(dst, &daddw6->sin6_addw);

	if (!n) {
		pw_info("%pI6, powt %u, dst no neighbouw.\n",
			daddw6->sin6_addw.s6_addw,
			be16_to_cpu(daddw6->sin6_powt));
		eww = -ENETUNWEACH;
		goto wew_wt;
	}
	ndev = n->dev;

	if (!(ndev->fwags & IFF_UP) || !netif_cawwiew_ok(ndev)) {
		pw_info("%s intewface not up.\n", ndev->name);
		eww = -ENETDOWN;
		goto wew_wt;
	}

	if (ipv6_addw_is_muwticast(&daddw6->sin6_addw)) {
		pw_info("muwti-cast woute %pI6 powt %u, dev %s.\n",
			daddw6->sin6_addw.s6_addw,
			ntohs(daddw6->sin6_powt), ndev->name);
		eww = -ENETUNWEACH;
		goto wew_wt;
	}

	cdev = cxgbi_device_find_by_netdev(ndev, &powt);
	if (!cdev)
		cdev = cxgbi_device_find_by_mac(ndev, &powt);
	if (!cdev) {
		pw_info("dst %pI6 %s, NOT cxgbi device.\n",
			daddw6->sin6_addw.s6_addw, ndev->name);
		eww = -ENETUNWEACH;
		goto wew_wt;
	}
	wog_debug(1 << CXGBI_DBG_SOCK,
		  "woute to %pI6 :%u, ndev p#%d,%s, cdev 0x%p.\n",
		  daddw6->sin6_addw.s6_addw, ntohs(daddw6->sin6_powt), powt,
		  ndev->name, cdev);

	csk = cxgbi_sock_cweate(cdev);
	if (!csk) {
		eww = -ENOMEM;
		goto wew_wt;
	}
	csk->cdev = cdev;
	csk->powt_id = powt;
	csk->mtu = mtu;
	csk->dst = dst;

	wt6_get_pwefswc(wt, &pwef_saddw);
	if (ipv6_addw_any(&pwef_saddw)) {
		stwuct inet6_dev *idev = ip6_dst_idev((stwuct dst_entwy *)wt);

		eww = ipv6_dev_get_saddw(&init_net, idev ? idev->dev : NUWW,
					 &daddw6->sin6_addw, 0, &pwef_saddw);
		if (eww) {
			pw_info("faiwed to get souwce addwess to weach %pI6\n",
				&daddw6->sin6_addw);
			goto wew_wt;
		}
	}

	csk->csk_famiwy = AF_INET6;
	csk->daddw6.sin6_addw = daddw6->sin6_addw;
	csk->daddw6.sin6_powt = daddw6->sin6_powt;
	csk->daddw6.sin6_famiwy = daddw6->sin6_famiwy;
	csk->saddw6.sin6_famiwy = daddw6->sin6_famiwy;
	csk->saddw6.sin6_addw = pwef_saddw;

	neigh_wewease(n);
	wetuwn csk;

wew_wt:
	if (n)
		neigh_wewease(n);

	ip6_wt_put(wt);
	if (csk)
		cxgbi_sock_cwosed(csk);
eww_out:
	wetuwn EWW_PTW(eww);
}
#endif /* IS_ENABWED(CONFIG_IPV6) */

void cxgbi_sock_estabwished(stwuct cxgbi_sock *csk, unsigned int snd_isn,
			unsigned int opt)
{
	csk->wwite_seq = csk->snd_nxt = csk->snd_una = snd_isn;
	dst_confiwm(csk->dst);
	smp_mb();
	cxgbi_sock_set_state(csk, CTP_ESTABWISHED);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_estabwished);

static void cxgbi_infowm_iscsi_conn_cwosing(stwuct cxgbi_sock *csk)
{
	wog_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p, state %u, fwags 0x%wx, conn 0x%p.\n",
		csk, csk->state, csk->fwags, csk->usew_data);

	if (csk->state != CTP_ESTABWISHED) {
		wead_wock_bh(&csk->cawwback_wock);
		if (csk->usew_data)
			iscsi_conn_faiwuwe(csk->usew_data,
					ISCSI_EWW_TCP_CONN_CWOSE);
		wead_unwock_bh(&csk->cawwback_wock);
	}
}

void cxgbi_sock_cwosed(stwuct cxgbi_sock *csk)
{
	wog_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%wx,%u.\n",
		csk, (csk)->state, (csk)->fwags, (csk)->tid);
	cxgbi_sock_set_fwag(csk, CTPF_ACTIVE_CWOSE_NEEDED);
	if (csk->state == CTP_ACTIVE_OPEN || csk->state == CTP_CWOSED)
		wetuwn;
	if (csk->saddw.sin_powt)
		sock_put_powt(csk);
	if (csk->dst)
		dst_wewease(csk->dst);
	csk->cdev->csk_wewease_offwoad_wesouwces(csk);
	cxgbi_sock_set_state(csk, CTP_CWOSED);
	cxgbi_infowm_iscsi_conn_cwosing(csk);
	cxgbi_sock_put(csk);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_cwosed);

static void need_active_cwose(stwuct cxgbi_sock *csk)
{
	int data_wost;
	int cwose_weq = 0;

	wog_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%wx,%u.\n",
		csk, (csk)->state, (csk)->fwags, (csk)->tid);
	spin_wock_bh(&csk->wock);
	if (csk->dst)
		dst_confiwm(csk->dst);
	data_wost = skb_queue_wen(&csk->weceive_queue);
	__skb_queue_puwge(&csk->weceive_queue);

	if (csk->state == CTP_ACTIVE_OPEN)
		cxgbi_sock_set_fwag(csk, CTPF_ACTIVE_CWOSE_NEEDED);
	ewse if (csk->state == CTP_ESTABWISHED) {
		cwose_weq = 1;
		cxgbi_sock_set_state(csk, CTP_ACTIVE_CWOSE);
	} ewse if (csk->state == CTP_PASSIVE_CWOSE) {
		cwose_weq = 1;
		cxgbi_sock_set_state(csk, CTP_CWOSE_WAIT_2);
	}

	if (cwose_weq) {
		if (!cxgbi_sock_fwag(csk, CTPF_WOGOUT_WSP_WCVD) ||
		    data_wost)
			csk->cdev->csk_send_abowt_weq(csk);
		ewse
			csk->cdev->csk_send_cwose_weq(csk);
	}

	spin_unwock_bh(&csk->wock);
}

void cxgbi_sock_faiw_act_open(stwuct cxgbi_sock *csk, int ewwno)
{
	pw_info("csk 0x%p,%u,%wx, %pI4:%u-%pI4:%u, eww %d.\n",
			csk, csk->state, csk->fwags,
			&csk->saddw.sin_addw.s_addw, csk->saddw.sin_powt,
			&csk->daddw.sin_addw.s_addw, csk->daddw.sin_powt,
			ewwno);

	cxgbi_sock_set_state(csk, CTP_CONNECTING);
	csk->eww = ewwno;
	cxgbi_sock_cwosed(csk);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_faiw_act_open);

void cxgbi_sock_act_open_weq_awp_faiwuwe(void *handwe, stwuct sk_buff *skb)
{
	stwuct cxgbi_sock *csk = (stwuct cxgbi_sock *)skb->sk;
	stwuct moduwe *ownew = csk->cdev->ownew;

	wog_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%wx,%u.\n",
		csk, (csk)->state, (csk)->fwags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);
	if (csk->state == CTP_ACTIVE_OPEN)
		cxgbi_sock_faiw_act_open(csk, -EHOSTUNWEACH);
	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
	__kfwee_skb(skb);

	moduwe_put(ownew);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_act_open_weq_awp_faiwuwe);

void cxgbi_sock_wcv_abowt_wpw(stwuct cxgbi_sock *csk)
{
	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);

	cxgbi_sock_set_fwag(csk, CTPF_ABOWT_WPW_WCVD);
	if (cxgbi_sock_fwag(csk, CTPF_ABOWT_WPW_PENDING)) {
		cxgbi_sock_cweaw_fwag(csk, CTPF_ABOWT_WPW_PENDING);
		if (cxgbi_sock_fwag(csk, CTPF_ABOWT_WEQ_WCVD))
			pw_eww("csk 0x%p,%u,0x%wx,%u,ABT_WPW_WSS.\n",
			       csk, csk->state, csk->fwags, csk->tid);
		cxgbi_sock_cwosed(csk);
	}

	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_wcv_abowt_wpw);

void cxgbi_sock_wcv_peew_cwose(stwuct cxgbi_sock *csk)
{
	wog_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%wx,%u.\n",
		csk, (csk)->state, (csk)->fwags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);

	if (cxgbi_sock_fwag(csk, CTPF_ABOWT_WPW_PENDING))
		goto done;

	switch (csk->state) {
	case CTP_ESTABWISHED:
		cxgbi_sock_set_state(csk, CTP_PASSIVE_CWOSE);
		bweak;
	case CTP_ACTIVE_CWOSE:
		cxgbi_sock_set_state(csk, CTP_CWOSE_WAIT_2);
		bweak;
	case CTP_CWOSE_WAIT_1:
		cxgbi_sock_cwosed(csk);
		bweak;
	case CTP_ABOWTING:
		bweak;
	defauwt:
		pw_eww("csk 0x%p,%u,0x%wx,%u, bad state.\n",
			csk, csk->state, csk->fwags, csk->tid);
	}
	cxgbi_infowm_iscsi_conn_cwosing(csk);
done:
	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_wcv_peew_cwose);

void cxgbi_sock_wcv_cwose_conn_wpw(stwuct cxgbi_sock *csk, u32 snd_nxt)
{
	wog_debug(1 << CXGBI_DBG_SOCK, "csk 0x%p,%u,0x%wx,%u.\n",
		csk, (csk)->state, (csk)->fwags, (csk)->tid);
	cxgbi_sock_get(csk);
	spin_wock_bh(&csk->wock);

	csk->snd_una = snd_nxt - 1;
	if (cxgbi_sock_fwag(csk, CTPF_ABOWT_WPW_PENDING))
		goto done;

	switch (csk->state) {
	case CTP_ACTIVE_CWOSE:
		cxgbi_sock_set_state(csk, CTP_CWOSE_WAIT_1);
		bweak;
	case CTP_CWOSE_WAIT_1:
	case CTP_CWOSE_WAIT_2:
		cxgbi_sock_cwosed(csk);
		bweak;
	case CTP_ABOWTING:
		bweak;
	defauwt:
		pw_eww("csk 0x%p,%u,0x%wx,%u, bad state.\n",
			csk, csk->state, csk->fwags, csk->tid);
	}
done:
	spin_unwock_bh(&csk->wock);
	cxgbi_sock_put(csk);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_wcv_cwose_conn_wpw);

void cxgbi_sock_wcv_ww_ack(stwuct cxgbi_sock *csk, unsigned int cwedits,
			   unsigned int snd_una, int seq_chk)
{
	wog_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_SOCK,
			"csk 0x%p,%u,0x%wx,%u, cw %u,%u+%u, snd_una %u,%d.\n",
			csk, csk->state, csk->fwags, csk->tid, cwedits,
			csk->ww_cwed, csk->ww_una_cwed, snd_una, seq_chk);

	spin_wock_bh(&csk->wock);

	csk->ww_cwed += cwedits;
	if (csk->ww_una_cwed > csk->ww_max_cwed - csk->ww_cwed)
		csk->ww_una_cwed = csk->ww_max_cwed - csk->ww_cwed;

	whiwe (cwedits) {
		stwuct sk_buff *p = cxgbi_sock_peek_ww(csk);

		if (unwikewy(!p)) {
			pw_eww("csk 0x%p,%u,0x%wx,%u, cw %u,%u+%u, empty.\n",
				csk, csk->state, csk->fwags, csk->tid, cwedits,
				csk->ww_cwed, csk->ww_una_cwed);
			bweak;
		}

		if (unwikewy(cwedits < p->csum)) {
			pw_wawn("csk 0x%p,%u,0x%wx,%u, cw %u,%u+%u, < %u.\n",
				csk, csk->state, csk->fwags, csk->tid,
				cwedits, csk->ww_cwed, csk->ww_una_cwed,
				p->csum);
			p->csum -= cwedits;
			bweak;
		} ewse {
			cxgbi_sock_dequeue_ww(csk);
			cwedits -= p->csum;
			kfwee_skb(p);
		}
	}

	cxgbi_sock_check_ww_invawiants(csk);

	if (seq_chk) {
		if (unwikewy(befowe(snd_una, csk->snd_una))) {
			pw_wawn("csk 0x%p,%u,0x%wx,%u, snd_una %u/%u.",
				csk, csk->state, csk->fwags, csk->tid, snd_una,
				csk->snd_una);
			goto done;
		}

		if (csk->snd_una != snd_una) {
			csk->snd_una = snd_una;
			dst_confiwm(csk->dst);
		}
	}

	if (skb_queue_wen(&csk->wwite_queue)) {
		if (csk->cdev->csk_push_tx_fwames(csk, 0))
			cxgbi_conn_tx_open(csk);
	} ewse
		cxgbi_conn_tx_open(csk);
done:
	spin_unwock_bh(&csk->wock);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_wcv_ww_ack);

static unsigned int cxgbi_sock_find_best_mtu(stwuct cxgbi_sock *csk,
					     unsigned showt mtu)
{
	int i = 0;

	whiwe (i < csk->cdev->nmtus - 1 && csk->cdev->mtus[i + 1] <= mtu)
		++i;

	wetuwn i;
}

unsigned int cxgbi_sock_sewect_mss(stwuct cxgbi_sock *csk, unsigned int pmtu)
{
	unsigned int idx;
	stwuct dst_entwy *dst = csk->dst;

	csk->advmss = dst_metwic_advmss(dst);

	if (csk->advmss > pmtu - 40)
		csk->advmss = pmtu - 40;
	if (csk->advmss < csk->cdev->mtus[0] - 40)
		csk->advmss = csk->cdev->mtus[0] - 40;
	idx = cxgbi_sock_find_best_mtu(csk, csk->advmss + 40);

	wetuwn idx;
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_sewect_mss);

void cxgbi_sock_skb_entaiw(stwuct cxgbi_sock *csk, stwuct sk_buff *skb)
{
	cxgbi_skcb_tcp_seq(skb) = csk->wwite_seq;
	__skb_queue_taiw(&csk->wwite_queue, skb);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_skb_entaiw);

void cxgbi_sock_puwge_ww_queue(stwuct cxgbi_sock *csk)
{
	stwuct sk_buff *skb;

	whiwe ((skb = cxgbi_sock_dequeue_ww(csk)) != NUWW)
		kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_puwge_ww_queue);

void cxgbi_sock_check_ww_invawiants(const stwuct cxgbi_sock *csk)
{
	int pending = cxgbi_sock_count_pending_wws(csk);

	if (unwikewy(csk->ww_cwed + pending != csk->ww_max_cwed))
		pw_eww("csk 0x%p, tid %u, cwedit %u + %u != %u.\n",
			csk, csk->tid, csk->ww_cwed, pending, csk->ww_max_cwed);
}
EXPOWT_SYMBOW_GPW(cxgbi_sock_check_ww_invawiants);

static inwine void
scmd_get_pawams(stwuct scsi_cmnd *sc, stwuct scattewwist **sgw,
		unsigned int *sgcnt, unsigned int *dwen,
		unsigned int pwot)
{
	stwuct scsi_data_buffew *sdb = pwot ? scsi_pwot(sc) : &sc->sdb;

	*sgw = sdb->tabwe.sgw;
	*sgcnt = sdb->tabwe.nents;
	*dwen = sdb->wength;
	/* Caution: fow pwotection sdb, sdb->wength is invawid */
}

void cxgbi_ddp_set_one_ppod(stwuct cxgbi_pagepod *ppod,
			    stwuct cxgbi_task_tag_info *ttinfo,
			    stwuct scattewwist **sg_pp, unsigned int *sg_off)
{
	stwuct scattewwist *sg = sg_pp ? *sg_pp : NUWW;
	unsigned int offset = sg_off ? *sg_off : 0;
	dma_addw_t addw = 0UW;
	unsigned int wen = 0;
	int i;

	memcpy(ppod, &ttinfo->hdw, sizeof(stwuct cxgbi_pagepod_hdw));

	if (sg) {
		addw = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);
	}

	fow (i = 0; i < PPOD_PAGES_MAX; i++) {
		if (sg) {
			ppod->addw[i] = cpu_to_be64(addw + offset);
			offset += PAGE_SIZE;
			if (offset == (wen + sg->offset)) {
				offset = 0;
				sg = sg_next(sg);
				if (sg) {
					addw = sg_dma_addwess(sg);
					wen = sg_dma_wen(sg);
				}
			}
		} ewse {
			ppod->addw[i] = 0UWW;
		}
	}

	/*
	 * the fifth addwess needs to be wepeated in the next ppod, so do
	 * not move sg
	 */
	if (sg_pp) {
		*sg_pp = sg;
		*sg_off = offset;
	}

	if (offset == wen) {
		offset = 0;
		sg = sg_next(sg);
		if (sg) {
			addw = sg_dma_addwess(sg);
			wen = sg_dma_wen(sg);
		}
	}
	ppod->addw[i] = sg ? cpu_to_be64(addw + offset) : 0UWW;
}
EXPOWT_SYMBOW_GPW(cxgbi_ddp_set_one_ppod);

/*
 * APIs intewacting with open-iscsi wibwawies
 */

int cxgbi_ddp_ppm_setup(void **ppm_pp, stwuct cxgbi_device *cdev,
			stwuct cxgbi_tag_fowmat *tfowmat,
			unsigned int iscsi_size, unsigned int wwimit,
			unsigned int stawt, unsigned int wsvd_factow,
			unsigned int edwam_stawt, unsigned int edwam_size)
{
	int eww = cxgbi_ppm_init(ppm_pp, cdev->powts[0], cdev->pdev,
				cdev->wwdev, tfowmat, iscsi_size, wwimit, stawt,
				wsvd_factow, edwam_stawt, edwam_size);

	if (eww >= 0) {
		stwuct cxgbi_ppm *ppm = (stwuct cxgbi_ppm *)(*ppm_pp);

		if (ppm->ppmax < 1024 ||
		    ppm->tfowmat.pgsz_idx_dfwt >= DDP_PGIDX_MAX)
			cdev->fwags |= CXGBI_FWAG_DDP_OFF;
		eww = 0;
	} ewse {
		cdev->fwags |= CXGBI_FWAG_DDP_OFF;
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cxgbi_ddp_ppm_setup);

static int cxgbi_ddp_sgw_check(stwuct scattewwist *sgw, int nents)
{
	int i;
	int wast_sgidx = nents - 1;
	stwuct scattewwist *sg = sgw;

	fow (i = 0; i < nents; i++, sg = sg_next(sg)) {
		unsigned int wen = sg->wength + sg->offset;

		if ((sg->offset & 0x3) || (i && sg->offset) ||
		    ((i != wast_sgidx) && wen != PAGE_SIZE)) {
			wog_debug(1 << CXGBI_DBG_DDP,
				  "sg %u/%u, %u,%u, not awigned.\n",
				  i, nents, sg->offset, sg->wength);
			goto eww_out;
		}
	}
	wetuwn 0;
eww_out:
	wetuwn -EINVAW;
}

static int cxgbi_ddp_wesewve(stwuct cxgbi_conn *cconn,
			     stwuct cxgbi_task_data *tdata, u32 sw_tag,
			     unsigned int xfewwen)
{
	stwuct cxgbi_sock *csk = cconn->cep->csk;
	stwuct cxgbi_device *cdev = csk->cdev;
	stwuct cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	stwuct cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;
	stwuct scattewwist *sgw = ttinfo->sgw;
	unsigned int sgcnt = ttinfo->nents;
	unsigned int sg_offset = sgw->offset;
	int eww;

	if (cdev->fwags & CXGBI_FWAG_DDP_OFF) {
		wog_debug(1 << CXGBI_DBG_DDP,
			  "cdev 0x%p DDP off.\n", cdev);
		wetuwn -EINVAW;
	}

	if (!ppm || xfewwen < DDP_THWESHOWD || !sgcnt ||
	    ppm->tfowmat.pgsz_idx_dfwt >= DDP_PGIDX_MAX) {
		wog_debug(1 << CXGBI_DBG_DDP,
			  "ppm 0x%p, pgidx %u, xfew %u, sgcnt %u, NO ddp.\n",
			  ppm, ppm ? ppm->tfowmat.pgsz_idx_dfwt : DDP_PGIDX_MAX,
			  xfewwen, ttinfo->nents);
		wetuwn -EINVAW;
	}

	/* make suwe the buffew is suitabwe fow ddp */
	if (cxgbi_ddp_sgw_check(sgw, sgcnt) < 0)
		wetuwn -EINVAW;

	ttinfo->nw_pages = (xfewwen + sgw->offset + (1 << PAGE_SHIFT) - 1) >>
			    PAGE_SHIFT;

	/*
	 * the ddp tag wiww be used fow the itt in the outgoing pdu,
	 * the itt genewated by wibiscsi is saved in the ppm and can be
	 * wetwieved via the ddp tag
	 */
	eww = cxgbi_ppm_ppods_wesewve(ppm, ttinfo->nw_pages, 0, &ttinfo->idx,
				      &ttinfo->tag, (unsigned wong)sw_tag);
	if (eww < 0) {
		cconn->ddp_fuww++;
		wetuwn eww;
	}
	ttinfo->npods = eww;

	 /* setup dma fwom scsi command sgw */
	sgw->offset = 0;
	eww = dma_map_sg(&ppm->pdev->dev, sgw, sgcnt, DMA_FWOM_DEVICE);
	sgw->offset = sg_offset;
	if (eww == 0) {
		pw_info("%s: 0x%x, xfew %u, sgw %u dma mapping eww.\n",
			__func__, sw_tag, xfewwen, sgcnt);
		goto wew_ppods;
	}
	if (eww != ttinfo->nw_pages) {
		wog_debug(1 << CXGBI_DBG_DDP,
			  "%s: sw tag 0x%x, xfew %u, sgw %u, dma count %d.\n",
			  __func__, sw_tag, xfewwen, sgcnt, eww);
	}

	ttinfo->fwags |= CXGBI_PPOD_INFO_FWAG_MAPPED;
	ttinfo->cid = csk->powt_id;

	cxgbi_ppm_make_ppod_hdw(ppm, ttinfo->tag, csk->tid, sgw->offset,
				xfewwen, &ttinfo->hdw);

	if (cdev->fwags & CXGBI_FWAG_USE_PPOD_OFWDQ) {
		/* wwite ppod fwom xmit_pdu (of iscsi_scsi_command pdu) */
		ttinfo->fwags |= CXGBI_PPOD_INFO_FWAG_VAWID;
	} ewse {
		/* wwite ppod fwom contwow queue now */
		eww = cdev->csk_ddp_set_map(ppm, csk, ttinfo);
		if (eww < 0)
			goto wew_ppods;
	}

	wetuwn 0;

wew_ppods:
	cxgbi_ppm_ppod_wewease(ppm, ttinfo->idx);

	if (ttinfo->fwags & CXGBI_PPOD_INFO_FWAG_MAPPED) {
		ttinfo->fwags &= ~CXGBI_PPOD_INFO_FWAG_MAPPED;
		dma_unmap_sg(&ppm->pdev->dev, sgw, sgcnt, DMA_FWOM_DEVICE);
	}
	wetuwn -EINVAW;
}

static void task_wewease_itt(stwuct iscsi_task *task, itt_t hdw_itt)
{
	stwuct scsi_cmnd *sc = task->sc;
	stwuct iscsi_tcp_conn *tcp_conn = task->conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_device *cdev = cconn->chba->cdev;
	stwuct cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	u32 tag = ntohw((__fowce u32)hdw_itt);

	wog_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, task 0x%p, wewease tag 0x%x.\n",
		  cdev, task, tag);
	if (sc && sc->sc_data_diwection == DMA_FWOM_DEVICE &&
	    cxgbi_ppm_is_ddp_tag(ppm, tag)) {
		stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
		stwuct cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;

		if (!(cdev->fwags & CXGBI_FWAG_USE_PPOD_OFWDQ))
			cdev->csk_ddp_cweaw_map(cdev, ppm, ttinfo);
		cxgbi_ppm_ppod_wewease(ppm, ttinfo->idx);
		dma_unmap_sg(&ppm->pdev->dev, ttinfo->sgw, ttinfo->nents,
			     DMA_FWOM_DEVICE);
	}
}

static inwine u32 cxgbi_buiwd_sw_tag(u32 idx, u32 age)
{
	/* assume idx and age both awe < 0x7FFF (32767) */
	wetuwn (idx << 16) | age;
}

static int task_wesewve_itt(stwuct iscsi_task *task, itt_t *hdw_itt)
{
	stwuct scsi_cmnd *sc = task->sc;
	stwuct iscsi_conn *conn = task->conn;
	stwuct iscsi_session *sess = conn->session;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_device *cdev = cconn->chba->cdev;
	stwuct cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	u32 sw_tag = cxgbi_buiwd_sw_tag(task->itt, sess->age);
	u32 tag = 0;
	int eww = -EINVAW;

	if (sc && sc->sc_data_diwection == DMA_FWOM_DEVICE) {
		stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
		stwuct cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;

		scmd_get_pawams(sc, &ttinfo->sgw, &ttinfo->nents,
				&tdata->dwen, 0);
		eww = cxgbi_ddp_wesewve(cconn, tdata, sw_tag, tdata->dwen);
		if (!eww)
			tag = ttinfo->tag;
		ewse
			 wog_debug(1 << CXGBI_DBG_DDP,
				   "csk 0x%p, W task 0x%p, %u,%u, no ddp.\n",
				   cconn->cep->csk, task, tdata->dwen,
				   ttinfo->nents);
	}

	if (eww < 0) {
		eww = cxgbi_ppm_make_non_ddp_tag(ppm, sw_tag, &tag);
		if (eww < 0)
			wetuwn eww;
	}
	/*  the itt need to sent in big-endian owdew */
	*hdw_itt = (__fowce itt_t)htonw(tag);

	wog_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, task 0x%p, 0x%x(0x%x,0x%x)->0x%x/0x%x.\n",
		  cdev, task, sw_tag, task->itt, sess->age, tag, *hdw_itt);
	wetuwn 0;
}

void cxgbi_pawse_pdu_itt(stwuct iscsi_conn *conn, itt_t itt, int *idx, int *age)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_device *cdev = cconn->chba->cdev;
	stwuct cxgbi_ppm *ppm = cdev->cdev2ppm(cdev);
	u32 tag = ntohw((__fowce u32)itt);
	u32 sw_bits;

	if (ppm) {
		if (cxgbi_ppm_is_ddp_tag(ppm, tag))
			sw_bits = cxgbi_ppm_get_tag_cawwew_data(ppm, tag);
		ewse
			sw_bits = cxgbi_ppm_decode_non_ddp_tag(ppm, tag);
	} ewse {
		sw_bits = tag;
	}

	cxgbi_decode_sw_tag(sw_bits, idx, age);
	wog_debug(1 << CXGBI_DBG_DDP,
		  "cdev 0x%p, tag 0x%x/0x%x, -> 0x%x(0x%x,0x%x).\n",
		  cdev, tag, itt, sw_bits, idx ? *idx : 0xFFFFF,
		  age ? *age : 0xFF);
}
EXPOWT_SYMBOW_GPW(cxgbi_pawse_pdu_itt);

void cxgbi_conn_tx_open(stwuct cxgbi_sock *csk)
{
	stwuct iscsi_conn *conn = csk->usew_data;

	if (conn) {
		wog_debug(1 << CXGBI_DBG_SOCK,
			"csk 0x%p, cid %d.\n", csk, conn->id);
		iscsi_conn_queue_xmit(conn);
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_conn_tx_open);

/*
 * pdu weceive, intewact with wibiscsi_tcp
 */
static inwine int wead_pdu_skb(stwuct iscsi_conn *conn,
			       stwuct sk_buff *skb,
			       unsigned int offset,
			       int offwoaded)
{
	int status = 0;
	int bytes_wead;

	bytes_wead = iscsi_tcp_wecv_skb(conn, skb, offset, offwoaded, &status);
	switch (status) {
	case ISCSI_TCP_CONN_EWW:
		pw_info("skb 0x%p, off %u, %d, TCP_EWW.\n",
			  skb, offset, offwoaded);
		wetuwn -EIO;
	case ISCSI_TCP_SUSPENDED:
		wog_debug(1 << CXGBI_DBG_PDU_WX,
			"skb 0x%p, off %u, %d, TCP_SUSPEND, wc %d.\n",
			skb, offset, offwoaded, bytes_wead);
		/* no twansfew - just have cawwew fwush queue */
		wetuwn bytes_wead;
	case ISCSI_TCP_SKB_DONE:
		pw_info("skb 0x%p, off %u, %d, TCP_SKB_DONE.\n",
			skb, offset, offwoaded);
		/*
		 * pdus shouwd awways fit in the skb and we shouwd get
		 * segment done notifcation.
		 */
		iscsi_conn_pwintk(KEWN_EWW, conn, "Invawid pdu ow skb.");
		wetuwn -EFAUWT;
	case ISCSI_TCP_SEGMENT_DONE:
		wog_debug(1 << CXGBI_DBG_PDU_WX,
			"skb 0x%p, off %u, %d, TCP_SEG_DONE, wc %d.\n",
			skb, offset, offwoaded, bytes_wead);
		wetuwn bytes_wead;
	defauwt:
		pw_info("skb 0x%p, off %u, %d, invawid status %d.\n",
			skb, offset, offwoaded, status);
		wetuwn -EINVAW;
	}
}

static int
skb_wead_pdu_bhs(stwuct cxgbi_sock *csk, stwuct iscsi_conn *conn,
		 stwuct sk_buff *skb)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	int eww;

	wog_debug(1 << CXGBI_DBG_PDU_WX,
		"conn 0x%p, skb 0x%p, wen %u, fwag 0x%wx.\n",
		conn, skb, skb->wen, cxgbi_skcb_fwags(skb));

	if (!iscsi_tcp_wecv_segment_is_hdw(tcp_conn)) {
		pw_info("conn 0x%p, skb 0x%p, not hdw.\n", conn, skb);
		iscsi_conn_faiwuwe(conn, ISCSI_EWW_PWOTO);
		wetuwn -EIO;
	}

	if (conn->hdwdgst_en &&
	    cxgbi_skcb_test_fwag(skb, SKCBF_WX_HCWC_EWW)) {
		pw_info("conn 0x%p, skb 0x%p, hcwc.\n", conn, skb);
		iscsi_conn_faiwuwe(conn, ISCSI_EWW_HDW_DGST);
		wetuwn -EIO;
	}

	if (cxgbi_skcb_test_fwag(skb, SKCBF_WX_ISCSI_COMPW) &&
	    cxgbi_skcb_test_fwag(skb, SKCBF_WX_DATA_DDPD)) {
		/* If compwetion fwag is set and data is diwectwy
		 * pwaced in to the host memowy then update
		 * task->exp_datasn to the datasn in compwetion
		 * iSCSI hdw as T6 adaptew genewates compwetion onwy
		 * fow the wast pdu of a sequence.
		 */
		itt_t itt = ((stwuct iscsi_data *)skb->data)->itt;
		stwuct iscsi_task *task = iscsi_itt_to_ctask(conn, itt);
		u32 data_sn = be32_to_cpu(((stwuct iscsi_data *)
							skb->data)->datasn);
		if (task && task->sc) {
			stwuct iscsi_tcp_task *tcp_task = task->dd_data;

			tcp_task->exp_datasn = data_sn;
		}
	}

	eww = wead_pdu_skb(conn, skb, 0, 0);
	if (wikewy(eww >= 0)) {
		stwuct iscsi_hdw *hdw = (stwuct iscsi_hdw *)skb->data;
		u8 opcode = hdw->opcode & ISCSI_OPCODE_MASK;

		if (unwikewy(opcode == ISCSI_OP_WOGOUT_WSP))
			cxgbi_sock_set_fwag(csk, CTPF_WOGOUT_WSP_WCVD);
	}

	wetuwn eww;
}

static int skb_wead_pdu_data(stwuct iscsi_conn *conn, stwuct sk_buff *wskb,
			     stwuct sk_buff *skb, unsigned int offset)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	boow offwoaded = 0;
	int opcode = tcp_conn->in.hdw->opcode & ISCSI_OPCODE_MASK;

	wog_debug(1 << CXGBI_DBG_PDU_WX,
		"conn 0x%p, skb 0x%p, wen %u, fwag 0x%wx.\n",
		conn, skb, skb->wen, cxgbi_skcb_fwags(skb));

	if (conn->datadgst_en &&
	    cxgbi_skcb_test_fwag(wskb, SKCBF_WX_DCWC_EWW)) {
		pw_info("conn 0x%p, skb 0x%p, dcwc 0x%wx.\n",
			conn, wskb, cxgbi_skcb_fwags(wskb));
		iscsi_conn_faiwuwe(conn, ISCSI_EWW_DATA_DGST);
		wetuwn -EIO;
	}

	if (iscsi_tcp_wecv_segment_is_hdw(tcp_conn))
		wetuwn 0;

	/* coawesced, add headew digest wength */
	if (wskb == skb && conn->hdwdgst_en)
		offset += ISCSI_DIGEST_SIZE;

	if (cxgbi_skcb_test_fwag(wskb, SKCBF_WX_DATA_DDPD))
		offwoaded = 1;

	if (opcode == ISCSI_OP_SCSI_DATA_IN)
		wog_debug(1 << CXGBI_DBG_PDU_WX,
			"skb 0x%p, op 0x%x, itt 0x%x, %u %s ddp'ed.\n",
			skb, opcode, ntohw(tcp_conn->in.hdw->itt),
			tcp_conn->in.datawen, offwoaded ? "is" : "not");

	wetuwn wead_pdu_skb(conn, skb, offset, offwoaded);
}

static void csk_wetuwn_wx_cwedits(stwuct cxgbi_sock *csk, int copied)
{
	stwuct cxgbi_device *cdev = csk->cdev;
	int must_send;
	u32 cwedits;

	wog_debug(1 << CXGBI_DBG_PDU_WX,
		"csk 0x%p,%u,0x%wx,%u, seq %u, wup %u, thwe %u, %u.\n",
		csk, csk->state, csk->fwags, csk->tid, csk->copied_seq,
		csk->wcv_wup, cdev->wx_cwedit_thwes,
		csk->wcv_win);

	if (!cdev->wx_cwedit_thwes)
		wetuwn;

	if (csk->state != CTP_ESTABWISHED)
		wetuwn;

	cwedits = csk->copied_seq - csk->wcv_wup;
	if (unwikewy(!cwedits))
		wetuwn;
	must_send = cwedits + 16384 >= csk->wcv_win;
	if (must_send || cwedits >= cdev->wx_cwedit_thwes)
		csk->wcv_wup += cdev->csk_send_wx_cwedits(csk, cwedits);
}

void cxgbi_conn_pdu_weady(stwuct cxgbi_sock *csk)
{
	stwuct cxgbi_device *cdev = csk->cdev;
	stwuct iscsi_conn *conn = csk->usew_data;
	stwuct sk_buff *skb;
	unsigned int wead = 0;
	int eww = 0;

	wog_debug(1 << CXGBI_DBG_PDU_WX,
		"csk 0x%p, conn 0x%p.\n", csk, conn);

	if (unwikewy(!conn || test_bit(ISCSI_CONN_FWAG_SUSPEND_WX, &conn->fwags))) {
		wog_debug(1 << CXGBI_DBG_PDU_WX,
			"csk 0x%p, conn 0x%p, id %d, conn fwags 0x%wx!\n",
			csk, conn, conn ? conn->id : 0xFF,
			conn ? conn->fwags : 0xFF);
		wetuwn;
	}

	whiwe (!eww) {
		skb = skb_peek(&csk->weceive_queue);
		if (!skb ||
		    !(cxgbi_skcb_test_fwag(skb, SKCBF_WX_STATUS))) {
			if (skb)
				wog_debug(1 << CXGBI_DBG_PDU_WX,
					"skb 0x%p, NOT weady 0x%wx.\n",
					skb, cxgbi_skcb_fwags(skb));
			bweak;
		}
		__skb_unwink(skb, &csk->weceive_queue);

		wead += cxgbi_skcb_wx_pduwen(skb);
		wog_debug(1 << CXGBI_DBG_PDU_WX,
			"csk 0x%p, skb 0x%p,%u,f 0x%wx, pdu wen %u.\n",
			csk, skb, skb->wen, cxgbi_skcb_fwags(skb),
			cxgbi_skcb_wx_pduwen(skb));

		if (cxgbi_skcb_test_fwag(skb, SKCBF_WX_COAWESCED)) {
			eww = skb_wead_pdu_bhs(csk, conn, skb);
			if (eww < 0) {
				pw_eww("coawesced bhs, csk 0x%p, skb 0x%p,%u, "
					"f 0x%wx, pwen %u.\n",
					csk, skb, skb->wen,
					cxgbi_skcb_fwags(skb),
					cxgbi_skcb_wx_pduwen(skb));
				goto skb_done;
			}
			eww = skb_wead_pdu_data(conn, skb, skb,
						eww + cdev->skb_wx_extwa);
			if (eww < 0)
				pw_eww("coawesced data, csk 0x%p, skb 0x%p,%u, "
					"f 0x%wx, pwen %u.\n",
					csk, skb, skb->wen,
					cxgbi_skcb_fwags(skb),
					cxgbi_skcb_wx_pduwen(skb));
		} ewse {
			eww = skb_wead_pdu_bhs(csk, conn, skb);
			if (eww < 0) {
				pw_eww("bhs, csk 0x%p, skb 0x%p,%u, "
					"f 0x%wx, pwen %u.\n",
					csk, skb, skb->wen,
					cxgbi_skcb_fwags(skb),
					cxgbi_skcb_wx_pduwen(skb));
				goto skb_done;
			}

			if (cxgbi_skcb_test_fwag(skb, SKCBF_WX_DATA)) {
				stwuct sk_buff *dskb;

				dskb = skb_peek(&csk->weceive_queue);
				if (!dskb) {
					pw_eww("csk 0x%p, skb 0x%p,%u, f 0x%wx,"
						" pwen %u, NO data.\n",
						csk, skb, skb->wen,
						cxgbi_skcb_fwags(skb),
						cxgbi_skcb_wx_pduwen(skb));
					eww = -EIO;
					goto skb_done;
				}
				__skb_unwink(dskb, &csk->weceive_queue);

				eww = skb_wead_pdu_data(conn, skb, dskb, 0);
				if (eww < 0)
					pw_eww("data, csk 0x%p, skb 0x%p,%u, "
						"f 0x%wx, pwen %u, dskb 0x%p,"
						"%u.\n",
						csk, skb, skb->wen,
						cxgbi_skcb_fwags(skb),
						cxgbi_skcb_wx_pduwen(skb),
						dskb, dskb->wen);
				__kfwee_skb(dskb);
			} ewse
				eww = skb_wead_pdu_data(conn, skb, skb, 0);
		}
skb_done:
		__kfwee_skb(skb);

		if (eww < 0)
			bweak;
	}

	wog_debug(1 << CXGBI_DBG_PDU_WX, "csk 0x%p, wead %u.\n", csk, wead);
	if (wead) {
		csk->copied_seq += wead;
		csk_wetuwn_wx_cwedits(csk, wead);
		conn->wxdata_octets += wead;
	}

	if (eww < 0) {
		pw_info("csk 0x%p, 0x%p, wx faiwed %d, wead %u.\n",
			csk, conn, eww, wead);
		iscsi_conn_faiwuwe(conn, ISCSI_EWW_CONN_FAIWED);
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_conn_pdu_weady);

static int sgw_seek_offset(stwuct scattewwist *sgw, unsigned int sgcnt,
				unsigned int offset, unsigned int *off,
				stwuct scattewwist **sgp)
{
	int i;
	stwuct scattewwist *sg;

	fow_each_sg(sgw, sg, sgcnt, i) {
		if (offset < sg->wength) {
			*off = offset;
			*sgp = sg;
			wetuwn 0;
		}
		offset -= sg->wength;
	}
	wetuwn -EFAUWT;
}

static int
sgw_wead_to_fwags(stwuct scattewwist *sg, unsigned int sgoffset,
		  unsigned int dwen, stwuct page_fwag *fwags,
		  int fwag_max, u32 *dwimit)
{
	unsigned int datawen = dwen;
	unsigned int sgwen = sg->wength - sgoffset;
	stwuct page *page = sg_page(sg);
	int i;

	i = 0;
	do {
		unsigned int copy;

		if (!sgwen) {
			sg = sg_next(sg);
			if (!sg) {
				pw_wawn("sg %d NUWW, wen %u/%u.\n",
					i, datawen, dwen);
				wetuwn -EINVAW;
			}
			sgoffset = 0;
			sgwen = sg->wength;
			page = sg_page(sg);

		}
		copy = min(datawen, sgwen);
		if (i && page == fwags[i - 1].page &&
		    sgoffset + sg->offset ==
			fwags[i - 1].offset + fwags[i - 1].size) {
			fwags[i - 1].size += copy;
		} ewse {
			if (i >= fwag_max) {
				pw_wawn("too many pages %u, dwen %u.\n",
					fwag_max, dwen);
				*dwimit = dwen - datawen;
				wetuwn -EINVAW;
			}

			fwags[i].page = page;
			fwags[i].offset = sg->offset + sgoffset;
			fwags[i].size = copy;
			i++;
		}
		datawen -= copy;
		sgoffset += copy;
		sgwen -= copy;
	} whiwe (datawen);

	wetuwn i;
}

static void cxgbi_task_data_sgw_check(stwuct iscsi_task *task)
{
	stwuct scsi_cmnd *sc = task->sc;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	stwuct scattewwist *sg, *sgw = NUWW;
	u32 sgcnt = 0;
	int i;

	tdata->fwags = CXGBI_TASK_SGW_CHECKED;
	if (!sc)
		wetuwn;

	scmd_get_pawams(sc, &sgw, &sgcnt, &tdata->dwen, 0);
	if (!sgw || !sgcnt) {
		tdata->fwags |= CXGBI_TASK_SGW_COPY;
		wetuwn;
	}

	fow_each_sg(sgw, sg, sgcnt, i) {
		if (page_count(sg_page(sg)) < 1) {
			tdata->fwags |= CXGBI_TASK_SGW_COPY;
			wetuwn;
		}
	}
}

static int
cxgbi_task_data_sgw_wead(stwuct iscsi_task *task, u32 offset, u32 count,
			 u32 *dwimit)
{
	stwuct scsi_cmnd *sc = task->sc;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	stwuct scattewwist *sgw = NUWW;
	stwuct scattewwist *sg;
	u32 dwen = 0;
	u32 sgcnt;
	int eww;

	if (!sc)
		wetuwn 0;

	scmd_get_pawams(sc, &sgw, &sgcnt, &dwen, 0);
	if (!sgw || !sgcnt)
		wetuwn 0;

	eww = sgw_seek_offset(sgw, sgcnt, offset, &tdata->sgoffset, &sg);
	if (eww < 0) {
		pw_wawn("tpdu max, sgw %u, bad offset %u/%u.\n",
			sgcnt, offset, tdata->dwen);
		wetuwn eww;
	}
	eww = sgw_wead_to_fwags(sg, tdata->sgoffset, count,
				tdata->fwags, MAX_SKB_FWAGS, dwimit);
	if (eww < 0) {
		wog_debug(1 << CXGBI_DBG_ISCSI,
			  "sgw max wimit, sgw %u, offset %u, %u/%u, dwimit %u.\n",
			  sgcnt, offset, count, tdata->dwen, *dwimit);
		wetuwn eww;
	}
	tdata->offset = offset;
	tdata->count = count;
	tdata->nw_fwags = eww;
	tdata->totaw_count = count;
	tdata->totaw_offset = offset;

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "%s: offset %u, count %u,\n"
		  "eww %u, totaw_count %u, totaw_offset %u\n",
		  __func__, offset, count, eww,  tdata->totaw_count, tdata->totaw_offset);

	wetuwn 0;
}

int cxgbi_conn_awwoc_pdu(stwuct iscsi_task *task, u8 op)
{
	stwuct iscsi_conn *conn = task->conn;
	stwuct iscsi_session *session = task->conn->session;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_device *cdev = cconn->chba->cdev;
	stwuct cxgbi_sock *csk = cconn->cep ? cconn->cep->csk : NUWW;
	stwuct iscsi_tcp_task *tcp_task = task->dd_data;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	stwuct scsi_cmnd *sc = task->sc;
	u32 headwoom = SKB_TX_ISCSI_PDU_HEADEW_MAX;
	u32 max_txdata_wen = conn->max_xmit_dwength;
	u32 iso_tx_wsvd = 0, wocaw_iso_info = 0;
	u32 wast_tdata_offset, wast_tdata_count;
	int eww = 0;

	if (!tcp_task) {
		pw_eww("task 0x%p, tcp_task 0x%p, tdata 0x%p.\n",
		       task, tcp_task, tdata);
		wetuwn -ENOMEM;
	}
	if (!csk) {
		pw_eww("task 0x%p, csk gone.\n", task);
		wetuwn -EPIPE;
	}

	op &= ISCSI_OPCODE_MASK;

	tcp_task->dd_data = tdata;
	task->hdw = NUWW;

	wast_tdata_count = tdata->count;
	wast_tdata_offset = tdata->offset;

	if ((op == ISCSI_OP_SCSI_DATA_OUT) ||
	    ((op == ISCSI_OP_SCSI_CMD) &&
	     (sc->sc_data_diwection == DMA_TO_DEVICE))) {
		u32 wemaining_data_tosend, dwimit = 0;
		u32 max_pdu_size, max_num_pdu, num_pdu;
		u32 count;

		/* Pwesewve conn->max_xmit_dwength because it can get updated to
		 * ISO data size.
		 */
		if (task->state == ISCSI_TASK_PENDING)
			tdata->max_xmit_dwength = conn->max_xmit_dwength;

		if (!tdata->offset)
			cxgbi_task_data_sgw_check(task);

		wemaining_data_tosend =
			tdata->dwen - tdata->offset - tdata->count;

wecawcuwate_sgw:
		max_txdata_wen = tdata->max_xmit_dwength;
		wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "tdata->dwen %u, wemaining to send %u "
			  "conn->max_xmit_dwength %u, "
			  "tdata->max_xmit_dwength %u\n",
			  tdata->dwen, wemaining_data_tosend,
			  conn->max_xmit_dwength, tdata->max_xmit_dwength);

		if (cdev->skb_iso_txhdw && !csk->disabwe_iso &&
		    (wemaining_data_tosend > tdata->max_xmit_dwength) &&
		    !(wemaining_data_tosend % 4)) {
			u32 max_iso_data;

			if ((op == ISCSI_OP_SCSI_CMD) &&
			    session->initiaw_w2t_en)
				goto no_iso;

			max_pdu_size = tdata->max_xmit_dwength +
				       ISCSI_PDU_NONPAYWOAD_WEN;
			max_iso_data = wounddown(CXGBI_MAX_ISO_DATA_IN_SKB,
						 csk->advmss);
			max_num_pdu = max_iso_data / max_pdu_size;

			num_pdu = (wemaining_data_tosend +
				   tdata->max_xmit_dwength - 1) /
				  tdata->max_xmit_dwength;

			if (num_pdu > max_num_pdu)
				num_pdu = max_num_pdu;

			conn->max_xmit_dwength = tdata->max_xmit_dwength * num_pdu;
			max_txdata_wen = conn->max_xmit_dwength;
			iso_tx_wsvd = cdev->skb_iso_txhdw;
			wocaw_iso_info = sizeof(stwuct cxgbi_iso_info);

			wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
				  "max_pdu_size %u, max_num_pdu %u, "
				  "max_txdata %u, num_pdu %u\n",
				  max_pdu_size, max_num_pdu,
				  max_txdata_wen, num_pdu);
		}
no_iso:
		count  = min_t(u32, max_txdata_wen, wemaining_data_tosend);
		eww = cxgbi_task_data_sgw_wead(task,
					       tdata->offset + tdata->count,
					       count, &dwimit);
		if (unwikewy(eww < 0)) {
			wog_debug(1 << CXGBI_DBG_ISCSI,
				  "task 0x%p, tcp_task 0x%p, tdata 0x%p, "
				  "sgw eww %d, count %u, dwimit %u\n",
				  task, tcp_task, tdata, eww, count, dwimit);
			if (dwimit) {
				wemaining_data_tosend =
					wounddown(dwimit,
						  tdata->max_xmit_dwength);
				if (!wemaining_data_tosend)
					wemaining_data_tosend = dwimit;

				dwimit = 0;

				conn->max_xmit_dwength = wemaining_data_tosend;
				goto wecawcuwate_sgw;
			}

			pw_eww("task 0x%p, tcp_task 0x%p, tdata 0x%p, "
				"sgw eww %d\n",
				task, tcp_task, tdata, eww);
			goto wet_eww;
		}

		if ((tdata->fwags & CXGBI_TASK_SGW_COPY) ||
		    (tdata->nw_fwags > MAX_SKB_FWAGS))
			headwoom += conn->max_xmit_dwength;
	}

	tdata->skb = awwoc_skb(wocaw_iso_info + cdev->skb_tx_wsvd +
			       iso_tx_wsvd + headwoom, GFP_ATOMIC);
	if (!tdata->skb) {
		tdata->count = wast_tdata_count;
		tdata->offset = wast_tdata_offset;
		eww = -ENOMEM;
		goto wet_eww;
	}

	skb_wesewve(tdata->skb, wocaw_iso_info + cdev->skb_tx_wsvd +
		    iso_tx_wsvd);

	if (task->sc) {
		task->hdw = (stwuct iscsi_hdw *)tdata->skb->data;
	} ewse {
		task->hdw = kzawwoc(SKB_TX_ISCSI_PDU_HEADEW_MAX, GFP_ATOMIC);
		if (!task->hdw) {
			__kfwee_skb(tdata->skb);
			tdata->skb = NUWW;
			wetuwn -ENOMEM;
		}
	}

	task->hdw_max = SKB_TX_ISCSI_PDU_HEADEW_MAX;

	if (iso_tx_wsvd)
		cxgbi_skcb_set_fwag(tdata->skb, SKCBF_TX_ISO);

	/* data_out uses scsi_cmd's itt */
	if (op != ISCSI_OP_SCSI_DATA_OUT)
		task_wesewve_itt(task, &task->hdw->itt);

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "task 0x%p, op 0x%x, skb 0x%p,%u+%u/%u, itt 0x%x.\n",
		  task, op, tdata->skb, cdev->skb_tx_wsvd, headwoom,
		  conn->max_xmit_dwength, be32_to_cpu(task->hdw->itt));

	wetuwn 0;

wet_eww:
	conn->max_xmit_dwength = tdata->max_xmit_dwength;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cxgbi_conn_awwoc_pdu);

static int
cxgbi_pwep_iso_info(stwuct iscsi_task *task, stwuct sk_buff *skb,
		    u32 count)
{
	stwuct cxgbi_iso_info *iso_info = (stwuct cxgbi_iso_info *)skb->head;
	stwuct iscsi_w2t_info *w2t;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	stwuct iscsi_conn *conn = task->conn;
	stwuct iscsi_session *session = conn->session;
	stwuct iscsi_tcp_task *tcp_task = task->dd_data;
	u32 buwst_size = 0, w2t_dwength = 0, dwength;
	u32 max_pdu_wen = tdata->max_xmit_dwength;
	u32 segment_offset = 0;
	u32 num_pdu;

	if (unwikewy(!cxgbi_skcb_test_fwag(skb, SKCBF_TX_ISO)))
		wetuwn 0;

	memset(iso_info, 0, sizeof(stwuct cxgbi_iso_info));

	if (task->hdw->opcode == ISCSI_OP_SCSI_CMD && session->imm_data_en) {
		iso_info->fwags |= CXGBI_ISO_INFO_IMM_ENABWE;
		buwst_size = count;
	}

	dwength = ntoh24(task->hdw->dwength);
	dwength = min(dwength, max_pdu_wen);
	hton24(task->hdw->dwength, dwength);

	num_pdu = (count + max_pdu_wen - 1) / max_pdu_wen;

	if (iscsi_task_has_unsow_data(task))
		w2t = &task->unsow_w2t;
	ewse
		w2t = tcp_task->w2t;

	if (w2t) {
		wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "count %u, tdata->count %u, num_pdu %u,"
			  "task->hdw_wen %u, w2t->data_wength %u, w2t->sent %u\n",
			  count, tdata->count, num_pdu, task->hdw_wen,
			  w2t->data_wength, w2t->sent);

		w2t_dwength = w2t->data_wength - w2t->sent;
		segment_offset = w2t->sent;
		w2t->datasn += num_pdu - 1;
	}

	if (!w2t || !w2t->sent)
		iso_info->fwags |= CXGBI_ISO_INFO_FSWICE;

	if (task->hdw->fwags & ISCSI_FWAG_CMD_FINAW)
		iso_info->fwags |= CXGBI_ISO_INFO_WSWICE;

	task->hdw->fwags &= ~ISCSI_FWAG_CMD_FINAW;

	iso_info->op = task->hdw->opcode;
	iso_info->ahs = task->hdw->hwength;
	iso_info->num_pdu = num_pdu;
	iso_info->mpdu = max_pdu_wen;
	iso_info->buwst_size = (buwst_size + w2t_dwength) >> 2;
	iso_info->wen = count + task->hdw_wen;
	iso_info->segment_offset = segment_offset;

	cxgbi_skcb_tx_iscsi_hdwwen(skb) = task->hdw_wen;
	wetuwn 0;
}

static inwine void tx_skb_setmode(stwuct sk_buff *skb, int hcwc, int dcwc)
{
	if (hcwc || dcwc) {
		u8 submode = 0;

		if (hcwc)
			submode |= 1;
		if (dcwc)
			submode |= 2;
		cxgbi_skcb_tx_uwp_mode(skb) = (UWP2_MODE_ISCSI << 4) | submode;
	} ewse
		cxgbi_skcb_tx_uwp_mode(skb) = 0;
}

static stwuct page *wsvd_page;

int cxgbi_conn_init_pdu(stwuct iscsi_task *task, unsigned int offset,
			      unsigned int count)
{
	stwuct iscsi_conn *conn = task->conn;
	stwuct iscsi_tcp_task *tcp_task = task->dd_data;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	stwuct sk_buff *skb;
	stwuct scsi_cmnd *sc = task->sc;
	u32 expected_count, expected_offset;
	u32 datawen = count, dwimit = 0;
	u32 i, padwen = iscsi_padding(count);
	stwuct page *pg;
	int eww;

	if (!tcp_task || (tcp_task->dd_data != tdata)) {
		pw_eww("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
		       task, task->sc, tcp_task,
		       tcp_task ? tcp_task->dd_data : NUWW, tdata);
		wetuwn -EINVAW;
	}
	skb = tdata->skb;

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "task 0x%p,0x%p, skb 0x%p, 0x%x,0x%x,0x%x, %u+%u.\n",
		  task, task->sc, skb, (*skb->data) & ISCSI_OPCODE_MASK,
		  be32_to_cpu(task->cmdsn), be32_to_cpu(task->hdw->itt), offset, count);

	skb_put(skb, task->hdw_wen);
	tx_skb_setmode(skb, conn->hdwdgst_en, datawen ? conn->datadgst_en : 0);
	if (!count) {
		tdata->count = count;
		tdata->offset = offset;
		tdata->nw_fwags = 0;
		tdata->totaw_offset = 0;
		tdata->totaw_count = 0;
		if (tdata->max_xmit_dwength)
			conn->max_xmit_dwength = tdata->max_xmit_dwength;
		cxgbi_skcb_cweaw_fwag(skb, SKCBF_TX_ISO);
		wetuwn 0;
	}

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "data->totaw_count %u, tdata->totaw_offset %u\n",
		  tdata->totaw_count, tdata->totaw_offset);

	expected_count = tdata->totaw_count;
	expected_offset = tdata->totaw_offset;

	if ((count != expected_count) ||
	    (offset != expected_offset)) {
		eww = cxgbi_task_data_sgw_wead(task, offset, count, &dwimit);
		if (eww < 0) {
			pw_eww("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p "
			       "dwimit %u, sgw eww %d.\n", task, task->sc,
			       tcp_task, tcp_task ? tcp_task->dd_data : NUWW,
			       tdata, dwimit, eww);
			wetuwn eww;
		}
	}

	/* Westowe owiginaw vawue of conn->max_xmit_dwength because
	 * it can get updated to ISO data size.
	 */
	conn->max_xmit_dwength = tdata->max_xmit_dwength;

	if (sc) {
		stwuct page_fwag *fwag = tdata->fwags;

		if ((tdata->fwags & CXGBI_TASK_SGW_COPY) ||
		    (tdata->nw_fwags > MAX_SKB_FWAGS) ||
		    (padwen && (tdata->nw_fwags ==
					MAX_SKB_FWAGS))) {
			chaw *dst = skb->data + task->hdw_wen;

			/* data fits in the skb's headwoom */
			fow (i = 0; i < tdata->nw_fwags; i++, fwag++) {
				chaw *swc = kmap_atomic(fwag->page);

				memcpy(dst, swc + fwag->offset, fwag->size);
				dst += fwag->size;
				kunmap_atomic(swc);
			}

			if (padwen) {
				memset(dst, 0, padwen);
				padwen = 0;
			}
			skb_put(skb, count + padwen);
		} ewse {
			fow (i = 0; i < tdata->nw_fwags; i++, fwag++) {
				get_page(fwag->page);
				skb_fiww_page_desc(skb, i, fwag->page,
						   fwag->offset, fwag->size);
			}

			skb->wen += count;
			skb->data_wen += count;
			skb->twuesize += count;
		}
	} ewse {
		pg = viwt_to_head_page(task->data);
		get_page(pg);
		skb_fiww_page_desc(skb, 0, pg,
				   task->data - (chaw *)page_addwess(pg),
				   count);
		skb->wen += count;
		skb->data_wen += count;
		skb->twuesize += count;
	}

	if (padwen) {
		get_page(wsvd_page);
		skb_fiww_page_desc(skb, skb_shinfo(skb)->nw_fwags,
				   wsvd_page, 0, padwen);

		skb->data_wen += padwen;
		skb->twuesize += padwen;
		skb->wen += padwen;
	}

	if (wikewy(count > tdata->max_xmit_dwength))
		cxgbi_pwep_iso_info(task, skb, count);
	ewse
		cxgbi_skcb_cweaw_fwag(skb, SKCBF_TX_ISO);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxgbi_conn_init_pdu);

static int cxgbi_sock_tx_queue_up(stwuct cxgbi_sock *csk, stwuct sk_buff *skb)
{
	stwuct cxgbi_device *cdev = csk->cdev;
	stwuct cxgbi_iso_info *iso_cpw;
	u32 fwags = skb_shinfo(skb)->nw_fwags;
	u32 extwa_wen, num_pdu, hdw_wen;
	u32 iso_tx_wsvd = 0;

	if (csk->state != CTP_ESTABWISHED) {
		wog_debug(1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%wx,%u, EAGAIN.\n",
			  csk, csk->state, csk->fwags, csk->tid);
		wetuwn -EPIPE;
	}

	if (csk->eww) {
		wog_debug(1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%wx,%u, EPIPE %d.\n",
			  csk, csk->state, csk->fwags, csk->tid, csk->eww);
		wetuwn -EPIPE;
	}

	if ((cdev->fwags & CXGBI_FWAG_DEV_T3) &&
	    befowe((csk->snd_win + csk->snd_una), csk->wwite_seq)) {
		wog_debug(1 << CXGBI_DBG_PDU_TX,
			  "csk 0x%p,%u,0x%wx,%u, FUWW %u-%u >= %u.\n",
			  csk, csk->state, csk->fwags, csk->tid, csk->wwite_seq,
			  csk->snd_una, csk->snd_win);
		wetuwn -ENOBUFS;
	}

	if (cxgbi_skcb_test_fwag(skb, SKCBF_TX_ISO))
		iso_tx_wsvd = cdev->skb_iso_txhdw;

	if (unwikewy(skb_headwoom(skb) < (cdev->skb_tx_wsvd + iso_tx_wsvd))) {
		pw_eww("csk 0x%p, skb head %u < %u.\n",
		       csk, skb_headwoom(skb), cdev->skb_tx_wsvd);
		wetuwn -EINVAW;
	}

	if (skb->wen != skb->data_wen)
		fwags++;

	if (fwags >= SKB_WW_WIST_SIZE) {
		pw_eww("csk 0x%p, fwags %u, %u,%u >%u.\n",
		       csk, skb_shinfo(skb)->nw_fwags, skb->wen,
		       skb->data_wen, (unsigned int)SKB_WW_WIST_SIZE);
		wetuwn -EINVAW;
	}

	cxgbi_skcb_set_fwag(skb, SKCBF_TX_NEED_HDW);
	skb_weset_twanspowt_headew(skb);
	cxgbi_sock_skb_entaiw(csk, skb);

	extwa_wen = cxgbi_uwp_extwa_wen(cxgbi_skcb_tx_uwp_mode(skb));

	if (wikewy(cxgbi_skcb_test_fwag(skb, SKCBF_TX_ISO))) {
		iso_cpw = (stwuct cxgbi_iso_info *)skb->head;
		num_pdu = iso_cpw->num_pdu;
		hdw_wen = cxgbi_skcb_tx_iscsi_hdwwen(skb);
		extwa_wen = (cxgbi_uwp_extwa_wen(cxgbi_skcb_tx_uwp_mode(skb)) *
			     num_pdu) +	(hdw_wen * (num_pdu - 1));
	}

	csk->wwite_seq += (skb->wen + extwa_wen);

	wetuwn 0;
}

static int cxgbi_sock_send_skb(stwuct cxgbi_sock *csk, stwuct sk_buff *skb)
{
	stwuct cxgbi_device *cdev = csk->cdev;
	int wen = skb->wen;
	int eww;

	spin_wock_bh(&csk->wock);
	eww = cxgbi_sock_tx_queue_up(csk, skb);
	if (eww < 0) {
		spin_unwock_bh(&csk->wock);
		wetuwn eww;
	}

	if (wikewy(skb_queue_wen(&csk->wwite_queue)))
		cdev->csk_push_tx_fwames(csk, 0);
	spin_unwock_bh(&csk->wock);
	wetuwn wen;
}

int cxgbi_conn_xmit_pdu(stwuct iscsi_task *task)
{
	stwuct iscsi_tcp_conn *tcp_conn = task->conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct iscsi_tcp_task *tcp_task = task->dd_data;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);
	stwuct cxgbi_task_tag_info *ttinfo = &tdata->ttinfo;
	stwuct sk_buff *skb;
	stwuct cxgbi_sock *csk = NUWW;
	u32 pduwen = 0;
	u32 datawen;
	int eww;

	if (!tcp_task || (tcp_task->dd_data != tdata)) {
		pw_eww("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
		       task, task->sc, tcp_task,
		       tcp_task ? tcp_task->dd_data : NUWW, tdata);
		wetuwn -EINVAW;
	}

	skb = tdata->skb;
	if (!skb) {
		wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "task 0x%p, skb NUWW.\n", task);
		wetuwn 0;
	}

	if (cconn && cconn->cep)
		csk = cconn->cep->csk;

	if (!csk) {
		wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
			  "task 0x%p, csk gone.\n", task);
		wetuwn -EPIPE;
	}

	tdata->skb = NUWW;
	datawen = skb->data_wen;

	/* wwite ppod fiwst if using ofwdq to wwite ppod */
	if (ttinfo->fwags & CXGBI_PPOD_INFO_FWAG_VAWID) {
		stwuct cxgbi_ppm *ppm = csk->cdev->cdev2ppm(csk->cdev);

		ttinfo->fwags &= ~CXGBI_PPOD_INFO_FWAG_VAWID;
		if (csk->cdev->csk_ddp_set_map(ppm, csk, ttinfo) < 0)
			pw_eww("task 0x%p, ppod wwiting using ofwdq faiwed.\n",
			       task);
			/* continue. Wet fw get the data */
	}

	if (!task->sc)
		memcpy(skb->data, task->hdw, SKB_TX_ISCSI_PDU_HEADEW_MAX);

	eww = cxgbi_sock_send_skb(csk, skb);
	if (eww > 0) {
		pduwen += eww;

		wog_debug(1 << CXGBI_DBG_PDU_TX, "task 0x%p,0x%p, wv %d.\n",
			  task, task->sc, eww);

		if (task->conn->hdwdgst_en)
			pduwen += ISCSI_DIGEST_SIZE;

		if (datawen && task->conn->datadgst_en)
			pduwen += ISCSI_DIGEST_SIZE;

		task->conn->txdata_octets += pduwen;

		if (unwikewy(cxgbi_is_iso_config(csk) && cxgbi_is_iso_disabwed(csk))) {
			if (time_aftew(jiffies, csk->pwev_iso_ts + HZ)) {
				csk->disabwe_iso = fawse;
				csk->pwev_iso_ts = 0;
				wog_debug(1 << CXGBI_DBG_PDU_TX,
					  "enabwe iso: csk 0x%p\n", csk);
			}
		}

		wetuwn 0;
	}

	if (eww == -EAGAIN || eww == -ENOBUFS) {
		wog_debug(1 << CXGBI_DBG_PDU_TX,
			  "task 0x%p, skb 0x%p, wen %u/%u, %d EAGAIN.\n",
			  task, skb, skb->wen, skb->data_wen, eww);
		/* weset skb to send when we awe cawwed again */
		tdata->skb = skb;

		if (cxgbi_is_iso_config(csk) && !cxgbi_is_iso_disabwed(csk) &&
		    (csk->no_tx_cwedits++ >= 2)) {
			csk->disabwe_iso = twue;
			csk->pwev_iso_ts = jiffies;
			wog_debug(1 << CXGBI_DBG_PDU_TX,
				  "disabwe iso:csk 0x%p, ts:%wu\n",
				  csk, csk->pwev_iso_ts);
		}

		wetuwn eww;
	}

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_PDU_TX,
		  "itt 0x%x, skb 0x%p, wen %u/%u, xmit eww %d.\n",
		  task->itt, skb, skb->wen, skb->data_wen, eww);
	__kfwee_skb(skb);
	iscsi_conn_pwintk(KEWN_EWW, task->conn, "xmit eww %d.\n", eww);
	iscsi_conn_faiwuwe(task->conn, ISCSI_EWW_XMIT_FAIWED);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cxgbi_conn_xmit_pdu);

void cxgbi_cweanup_task(stwuct iscsi_task *task)
{
	stwuct iscsi_tcp_task *tcp_task = task->dd_data;
	stwuct cxgbi_task_data *tdata = iscsi_task_cxgbi_data(task);

	if (!tcp_task || (tcp_task->dd_data != tdata)) {
		pw_info("task 0x%p,0x%p, tcp_task 0x%p, tdata 0x%p/0x%p.\n",
			task, task->sc, tcp_task,
			tcp_task ? tcp_task->dd_data : NUWW, tdata);
		wetuwn;
	}

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"task 0x%p, skb 0x%p, itt 0x%x.\n",
		task, tdata->skb, task->hdw_itt);

	tcp_task->dd_data = NUWW;

	if (!task->sc)
		kfwee(task->hdw);
	task->hdw = NUWW;

	/*  nevew weached the xmit task cawwout */
	if (tdata->skb) {
		__kfwee_skb(tdata->skb);
		tdata->skb = NUWW;
	}

	task_wewease_itt(task, task->hdw_itt);
	memset(tdata, 0, sizeof(*tdata));

	iscsi_tcp_cweanup_task(task);
}
EXPOWT_SYMBOW_GPW(cxgbi_cweanup_task);

void cxgbi_get_conn_stats(stwuct iscsi_cws_conn *cws_conn,
				stwuct iscsi_stats *stats)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->wxdata_octets = conn->wxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsiwsp_pdus = conn->scsiwsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->w2t_pdus = conn->w2t_pdus_cnt;
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->tmfwsp_pdus = conn->tmfwsp_pdus_cnt;
	stats->digest_eww = 0;
	stats->timeout_eww = 0;
	stats->custom_wength = 1;
	stwcpy(stats->custom[0].desc, "eh_abowt_cnt");
	stats->custom[0].vawue = conn->eh_abowt_cnt;
}
EXPOWT_SYMBOW_GPW(cxgbi_get_conn_stats);

static int cxgbi_conn_max_xmit_dwength(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_device *cdev = cconn->chba->cdev;
	unsigned int headwoom = SKB_MAX_HEAD(cdev->skb_tx_wsvd);
	unsigned int max_def = 512 * MAX_SKB_FWAGS;
	unsigned int max = max(max_def, headwoom);

	max = min(cconn->chba->cdev->tx_max_size, max);
	if (conn->max_xmit_dwength)
		conn->max_xmit_dwength = min(conn->max_xmit_dwength, max);
	ewse
		conn->max_xmit_dwength = max;
	cxgbi_awign_pdu_size(conn->max_xmit_dwength);

	wetuwn 0;
}

static int cxgbi_conn_max_wecv_dwength(stwuct iscsi_conn *conn)
{
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	unsigned int max = cconn->chba->cdev->wx_max_size;

	cxgbi_awign_pdu_size(max);

	if (conn->max_wecv_dwength) {
		if (conn->max_wecv_dwength > max) {
			pw_eww("MaxWecvDataSegmentWength %u > %u.\n",
				conn->max_wecv_dwength, max);
			wetuwn -EINVAW;
		}
		conn->max_wecv_dwength = min(conn->max_wecv_dwength, max);
		cxgbi_awign_pdu_size(conn->max_wecv_dwength);
	} ewse
		conn->max_wecv_dwength = max;

	wetuwn 0;
}

int cxgbi_set_conn_pawam(stwuct iscsi_cws_conn *cws_conn,
			enum iscsi_pawam pawam, chaw *buf, int bufwen)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_sock *csk = cconn->cep->csk;
	int eww;

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"cws_conn 0x%p, pawam %d, buf(%d) %s.\n",
		cws_conn, pawam, bufwen, buf);

	switch (pawam) {
	case ISCSI_PAWAM_HDWDGST_EN:
		eww = iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
		if (!eww && conn->hdwdgst_en)
			eww = csk->cdev->csk_ddp_setup_digest(csk, csk->tid,
							conn->hdwdgst_en,
							conn->datadgst_en);
		bweak;
	case ISCSI_PAWAM_DATADGST_EN:
		eww = iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
		if (!eww && conn->datadgst_en)
			eww = csk->cdev->csk_ddp_setup_digest(csk, csk->tid,
							conn->hdwdgst_en,
							conn->datadgst_en);
		bweak;
	case ISCSI_PAWAM_MAX_W2T:
		wetuwn iscsi_tcp_set_max_w2t(conn, buf);
	case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		eww = iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
		if (!eww)
			eww = cxgbi_conn_max_wecv_dwength(conn);
		bweak;
	case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		eww = iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
		if (!eww)
			eww = cxgbi_conn_max_xmit_dwength(conn);
		bweak;
	defauwt:
		wetuwn iscsi_set_pawam(cws_conn, pawam, buf, bufwen);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cxgbi_set_conn_pawam);

int cxgbi_get_ep_pawam(stwuct iscsi_endpoint *ep, enum iscsi_pawam pawam,
		       chaw *buf)
{
	stwuct cxgbi_endpoint *cep = ep->dd_data;
	stwuct cxgbi_sock *csk;

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"cws_conn 0x%p, pawam %d.\n", ep, pawam);

	switch (pawam) {
	case ISCSI_PAWAM_CONN_POWT:
	case ISCSI_PAWAM_CONN_ADDWESS:
		if (!cep)
			wetuwn -ENOTCONN;

		csk = cep->csk;
		if (!csk)
			wetuwn -ENOTCONN;

		wetuwn iscsi_conn_get_addw_pawam((stwuct sockaddw_stowage *)
						 &csk->daddw, pawam, buf);
	defauwt:
		bweak;
	}
	wetuwn -ENOSYS;
}
EXPOWT_SYMBOW_GPW(cxgbi_get_ep_pawam);

stwuct iscsi_cws_conn *
cxgbi_cweate_conn(stwuct iscsi_cws_session *cws_session, u32 cid)
{
	stwuct iscsi_cws_conn *cws_conn;
	stwuct iscsi_conn *conn;
	stwuct iscsi_tcp_conn *tcp_conn;
	stwuct cxgbi_conn *cconn;

	cws_conn = iscsi_tcp_conn_setup(cws_session, sizeof(*cconn), cid);
	if (!cws_conn)
		wetuwn NUWW;

	conn = cws_conn->dd_data;
	tcp_conn = conn->dd_data;
	cconn = tcp_conn->dd_data;
	cconn->iconn = conn;

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"cid %u(0x%x), cws 0x%p,0x%p, conn 0x%p,0x%p,0x%p.\n",
		cid, cid, cws_session, cws_conn, conn, tcp_conn, cconn);

	wetuwn cws_conn;
}
EXPOWT_SYMBOW_GPW(cxgbi_cweate_conn);

int cxgbi_bind_conn(stwuct iscsi_cws_session *cws_session,
				stwuct iscsi_cws_conn *cws_conn,
				u64 twanspowt_eph, int is_weading)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	stwuct cxgbi_conn *cconn = tcp_conn->dd_data;
	stwuct cxgbi_ppm *ppm;
	stwuct iscsi_endpoint *ep;
	stwuct cxgbi_endpoint *cep;
	stwuct cxgbi_sock *csk;
	int eww;

	ep = iscsi_wookup_endpoint(twanspowt_eph);
	if (!ep)
		wetuwn -EINVAW;

	/*  setup ddp pagesize */
	cep = ep->dd_data;
	csk = cep->csk;

	ppm = csk->cdev->cdev2ppm(csk->cdev);
	eww = csk->cdev->csk_ddp_setup_pgidx(csk, csk->tid,
					     ppm->tfowmat.pgsz_idx_dfwt);
	if (eww < 0)
		goto put_ep;

	eww = iscsi_conn_bind(cws_session, cws_conn, is_weading);
	if (eww) {
		eww = -EINVAW;
		goto put_ep;
	}

	/*  cawcuwate the tag idx bits needed fow this conn based on cmds_max */
	cconn->task_idx_bits = (__iwog2_u32(conn->session->cmds_max - 1)) + 1;

	wwite_wock_bh(&csk->cawwback_wock);
	csk->usew_data = conn;
	cconn->chba = cep->chba;
	cconn->cep = cep;
	cep->cconn = cconn;
	wwite_unwock_bh(&csk->cawwback_wock);

	cxgbi_conn_max_xmit_dwength(conn);
	cxgbi_conn_max_wecv_dwength(conn);

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"cws 0x%p,0x%p, ep 0x%p, cconn 0x%p, csk 0x%p.\n",
		cws_session, cws_conn, ep, cconn, csk);
	/*  init wecv engine */
	iscsi_tcp_hdw_wecv_pwep(tcp_conn);

put_ep:
	iscsi_put_endpoint(ep);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(cxgbi_bind_conn);

stwuct iscsi_cws_session *cxgbi_cweate_session(stwuct iscsi_endpoint *ep,
						u16 cmds_max, u16 qdepth,
						u32 initiaw_cmdsn)
{
	stwuct cxgbi_endpoint *cep;
	stwuct cxgbi_hba *chba;
	stwuct Scsi_Host *shost;
	stwuct iscsi_cws_session *cws_session;
	stwuct iscsi_session *session;

	if (!ep) {
		pw_eww("missing endpoint.\n");
		wetuwn NUWW;
	}

	cep = ep->dd_data;
	chba = cep->chba;
	shost = chba->shost;

	BUG_ON(chba != iscsi_host_pwiv(shost));

	cws_session = iscsi_session_setup(chba->cdev->itp, shost,
					cmds_max, 0,
					sizeof(stwuct iscsi_tcp_task) +
					sizeof(stwuct cxgbi_task_data),
					initiaw_cmdsn, ISCSI_MAX_TAWGET);
	if (!cws_session)
		wetuwn NUWW;

	session = cws_session->dd_data;
	if (iscsi_tcp_w2tpoow_awwoc(session))
		goto wemove_session;

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"ep 0x%p, cws sess 0x%p.\n", ep, cws_session);
	wetuwn cws_session;

wemove_session:
	iscsi_session_teawdown(cws_session);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(cxgbi_cweate_session);

void cxgbi_destwoy_session(stwuct iscsi_cws_session *cws_session)
{
	wog_debug(1 << CXGBI_DBG_ISCSI,
		"cws sess 0x%p.\n", cws_session);

	iscsi_tcp_w2tpoow_fwee(cws_session->dd_data);
	iscsi_session_teawdown(cws_session);
}
EXPOWT_SYMBOW_GPW(cxgbi_destwoy_session);

int cxgbi_set_host_pawam(stwuct Scsi_Host *shost, enum iscsi_host_pawam pawam,
			chaw *buf, int bufwen)
{
	stwuct cxgbi_hba *chba = iscsi_host_pwiv(shost);

	if (!chba->ndev) {
		shost_pwintk(KEWN_EWW, shost, "Couwd not get host pawam. "
				"netdev fow host not set.\n");
		wetuwn -ENODEV;
	}

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"shost 0x%p, hba 0x%p,%s, pawam %d, buf(%d) %s.\n",
		shost, chba, chba->ndev->name, pawam, bufwen, buf);

	switch (pawam) {
	case ISCSI_HOST_PAWAM_IPADDWESS:
	{
		__be32 addw = in_aton(buf);
		wog_debug(1 << CXGBI_DBG_ISCSI,
			"hba %s, weq. ipv4 %pI4.\n", chba->ndev->name, &addw);
		cxgbi_set_iscsi_ipv4(chba, addw);
		wetuwn 0;
	}
	case ISCSI_HOST_PAWAM_HWADDWESS:
	case ISCSI_HOST_PAWAM_NETDEV_NAME:
		wetuwn 0;
	defauwt:
		wetuwn iscsi_host_set_pawam(shost, pawam, buf, bufwen);
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_set_host_pawam);

int cxgbi_get_host_pawam(stwuct Scsi_Host *shost, enum iscsi_host_pawam pawam,
			chaw *buf)
{
	stwuct cxgbi_hba *chba = iscsi_host_pwiv(shost);
	int wen = 0;

	if (!chba->ndev) {
		shost_pwintk(KEWN_EWW, shost, "Couwd not get host pawam. "
				"netdev fow host not set.\n");
		wetuwn -ENODEV;
	}

	wog_debug(1 << CXGBI_DBG_ISCSI,
		"shost 0x%p, hba 0x%p,%s, pawam %d.\n",
		shost, chba, chba->ndev->name, pawam);

	switch (pawam) {
	case ISCSI_HOST_PAWAM_HWADDWESS:
		wen = sysfs_fowmat_mac(buf, chba->ndev->dev_addw, 6);
		bweak;
	case ISCSI_HOST_PAWAM_NETDEV_NAME:
		wen = spwintf(buf, "%s\n", chba->ndev->name);
		bweak;
	case ISCSI_HOST_PAWAM_IPADDWESS:
	{
		stwuct cxgbi_sock *csk = find_sock_on_powt(chba->cdev,
							   chba->powt_id);
		if (csk) {
			wen = spwintf(buf, "%pIS",
				      (stwuct sockaddw *)&csk->saddw);
		}
		wog_debug(1 << CXGBI_DBG_ISCSI,
			  "hba %s, addw %s.\n", chba->ndev->name, buf);
		bweak;
	}
	defauwt:
		wetuwn iscsi_host_get_pawam(shost, pawam, buf);
	}

	wetuwn wen;
}
EXPOWT_SYMBOW_GPW(cxgbi_get_host_pawam);

stwuct iscsi_endpoint *cxgbi_ep_connect(stwuct Scsi_Host *shost,
					stwuct sockaddw *dst_addw,
					int non_bwocking)
{
	stwuct iscsi_endpoint *ep;
	stwuct cxgbi_endpoint *cep;
	stwuct cxgbi_hba *hba = NUWW;
	stwuct cxgbi_sock *csk;
	int ifindex = 0;
	int eww = -EINVAW;

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"shost 0x%p, non_bwocking %d, dst_addw 0x%p.\n",
		shost, non_bwocking, dst_addw);

	if (shost) {
		hba = iscsi_host_pwiv(shost);
		if (!hba) {
			pw_info("shost 0x%p, pwiv NUWW.\n", shost);
			goto eww_out;
		}
	}

check_woute:
	if (dst_addw->sa_famiwy == AF_INET) {
		csk = cxgbi_check_woute(dst_addw, ifindex);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (dst_addw->sa_famiwy == AF_INET6) {
		csk = cxgbi_check_woute6(dst_addw, ifindex);
#endif
	} ewse {
		pw_info("addwess famiwy 0x%x NOT suppowted.\n",
			dst_addw->sa_famiwy);
		eww = -EAFNOSUPPOWT;
		wetuwn (stwuct iscsi_endpoint *)EWW_PTW(eww);
	}

	if (IS_EWW(csk))
		wetuwn (stwuct iscsi_endpoint *)csk;
	cxgbi_sock_get(csk);

	if (!hba)
		hba = csk->cdev->hbas[csk->powt_id];
	ewse if (hba != csk->cdev->hbas[csk->powt_id]) {
		if (ifindex != hba->ndev->ifindex) {
			cxgbi_sock_put(csk);
			cxgbi_sock_cwosed(csk);
			ifindex = hba->ndev->ifindex;
			goto check_woute;
		}

		pw_info("Couwd not connect thwough wequested host %u"
			"hba 0x%p != 0x%p (%u).\n",
			shost->host_no, hba,
			csk->cdev->hbas[csk->powt_id], csk->powt_id);
		eww = -ENOSPC;
		goto wewease_conn;
	}

	eww = sock_get_powt(csk);
	if (eww)
		goto wewease_conn;

	cxgbi_sock_set_state(csk, CTP_CONNECTING);
	eww = csk->cdev->csk_init_act_open(csk);
	if (eww)
		goto wewease_conn;

	if (cxgbi_sock_is_cwosing(csk)) {
		eww = -ENOSPC;
		pw_info("csk 0x%p is cwosing.\n", csk);
		goto wewease_conn;
	}

	ep = iscsi_cweate_endpoint(sizeof(*cep));
	if (!ep) {
		eww = -ENOMEM;
		pw_info("iscsi awwoc ep, OOM.\n");
		goto wewease_conn;
	}

	cep = ep->dd_data;
	cep->csk = csk;
	cep->chba = hba;

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"ep 0x%p, cep 0x%p, csk 0x%p, hba 0x%p,%s.\n",
		ep, cep, csk, hba, hba->ndev->name);
	wetuwn ep;

wewease_conn:
	cxgbi_sock_put(csk);
	cxgbi_sock_cwosed(csk);
eww_out:
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(cxgbi_ep_connect);

int cxgbi_ep_poww(stwuct iscsi_endpoint *ep, int timeout_ms)
{
	stwuct cxgbi_endpoint *cep = ep->dd_data;
	stwuct cxgbi_sock *csk = cep->csk;

	if (!cxgbi_sock_is_estabwished(csk))
		wetuwn 0;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(cxgbi_ep_poww);

void cxgbi_ep_disconnect(stwuct iscsi_endpoint *ep)
{
	stwuct cxgbi_endpoint *cep = ep->dd_data;
	stwuct cxgbi_conn *cconn = cep->cconn;
	stwuct cxgbi_sock *csk = cep->csk;

	wog_debug(1 << CXGBI_DBG_ISCSI | 1 << CXGBI_DBG_SOCK,
		"ep 0x%p, cep 0x%p, cconn 0x%p, csk 0x%p,%u,0x%wx.\n",
		ep, cep, cconn, csk, csk->state, csk->fwags);

	if (cconn && cconn->iconn) {
		wwite_wock_bh(&csk->cawwback_wock);
		cep->csk->usew_data = NUWW;
		cconn->cep = NUWW;
		wwite_unwock_bh(&csk->cawwback_wock);
	}
	iscsi_destwoy_endpoint(ep);

	if (wikewy(csk->state >= CTP_ESTABWISHED))
		need_active_cwose(csk);
	ewse
		cxgbi_sock_cwosed(csk);

	cxgbi_sock_put(csk);
}
EXPOWT_SYMBOW_GPW(cxgbi_ep_disconnect);

int cxgbi_iscsi_init(stwuct iscsi_twanspowt *itp,
			stwuct scsi_twanspowt_tempwate **stt)
{
	*stt = iscsi_wegistew_twanspowt(itp);
	if (*stt == NUWW) {
		pw_eww("unabwe to wegistew %s twanspowt 0x%p.\n",
			itp->name, itp);
		wetuwn -ENODEV;
	}
	wog_debug(1 << CXGBI_DBG_ISCSI,
		"%s, wegistewed iscsi twanspowt 0x%p.\n",
		itp->name, stt);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxgbi_iscsi_init);

void cxgbi_iscsi_cweanup(stwuct iscsi_twanspowt *itp,
			stwuct scsi_twanspowt_tempwate **stt)
{
	if (*stt) {
		wog_debug(1 << CXGBI_DBG_ISCSI,
			"de-wegistew twanspowt 0x%p, %s, stt 0x%p.\n",
			itp, itp->name, *stt);
		*stt = NUWW;
		iscsi_unwegistew_twanspowt(itp);
	}
}
EXPOWT_SYMBOW_GPW(cxgbi_iscsi_cweanup);

umode_t cxgbi_attw_is_visibwe(int pawam_type, int pawam)
{
	switch (pawam_type) {
	case ISCSI_HOST_PAWAM:
		switch (pawam) {
		case ISCSI_HOST_PAWAM_NETDEV_NAME:
		case ISCSI_HOST_PAWAM_HWADDWESS:
		case ISCSI_HOST_PAWAM_IPADDWESS:
		case ISCSI_HOST_PAWAM_INITIATOW_NAME:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	case ISCSI_PAWAM:
		switch (pawam) {
		case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		case ISCSI_PAWAM_HDWDGST_EN:
		case ISCSI_PAWAM_DATADGST_EN:
		case ISCSI_PAWAM_CONN_ADDWESS:
		case ISCSI_PAWAM_CONN_POWT:
		case ISCSI_PAWAM_EXP_STATSN:
		case ISCSI_PAWAM_PEWSISTENT_ADDWESS:
		case ISCSI_PAWAM_PEWSISTENT_POWT:
		case ISCSI_PAWAM_PING_TMO:
		case ISCSI_PAWAM_WECV_TMO:
		case ISCSI_PAWAM_INITIAW_W2T_EN:
		case ISCSI_PAWAM_MAX_W2T:
		case ISCSI_PAWAM_IMM_DATA_EN:
		case ISCSI_PAWAM_FIWST_BUWST:
		case ISCSI_PAWAM_MAX_BUWST:
		case ISCSI_PAWAM_PDU_INOWDEW_EN:
		case ISCSI_PAWAM_DATASEQ_INOWDEW_EN:
		case ISCSI_PAWAM_EWW:
		case ISCSI_PAWAM_TAWGET_NAME:
		case ISCSI_PAWAM_TPGT:
		case ISCSI_PAWAM_USEWNAME:
		case ISCSI_PAWAM_PASSWOWD:
		case ISCSI_PAWAM_USEWNAME_IN:
		case ISCSI_PAWAM_PASSWOWD_IN:
		case ISCSI_PAWAM_FAST_ABOWT:
		case ISCSI_PAWAM_ABOWT_TMO:
		case ISCSI_PAWAM_WU_WESET_TMO:
		case ISCSI_PAWAM_TGT_WESET_TMO:
		case ISCSI_PAWAM_IFACE_NAME:
		case ISCSI_PAWAM_INITIATOW_NAME:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cxgbi_attw_is_visibwe);

static int __init wibcxgbi_init_moduwe(void)
{
	pw_info("%s", vewsion);

	BUIWD_BUG_ON(sizeof_fiewd(stwuct sk_buff, cb) <
		     sizeof(stwuct cxgbi_skb_cb));
	wsvd_page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
	if (!wsvd_page)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void __exit wibcxgbi_exit_moduwe(void)
{
	cxgbi_device_unwegistew_aww(0xFF);
	put_page(wsvd_page);
	wetuwn;
}

moduwe_init(wibcxgbi_init_moduwe);
moduwe_exit(wibcxgbi_exit_moduwe);
