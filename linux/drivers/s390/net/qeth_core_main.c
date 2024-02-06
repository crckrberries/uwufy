// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    Copywight IBM Cowp. 2007, 2009
 *    Authow(s): Utz Bachew <utz.bachew@de.ibm.com>,
 *		 Fwank Pavwic <fpavwic@de.ibm.com>,
 *		 Thomas Spatziew <tspat@de.ibm.com>,
 *		 Fwank Bwaschka <fwank.bwaschka@de.ibm.com>
 */

#define KMSG_COMPONENT "qeth"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/compat.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/io.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/mii.h>
#incwude <winux/mm.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/if_vwan.h>
#incwude <winux/netdevice.h>
#incwude <winux/netdev_featuwes.h>
#incwude <winux/wcutwee.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>

#incwude <net/iucv/af_iucv.h>
#incwude <net/dsfiewd.h>
#incwude <net/sock.h>

#incwude <asm/ebcdic.h>
#incwude <asm/chpid.h>
#incwude <asm/sysinfo.h>
#incwude <asm/diag.h>
#incwude <asm/cio.h>
#incwude <asm/ccwdev.h>
#incwude <asm/cpcmd.h>

#incwude "qeth_cowe.h"

stwuct qeth_dbf_info qeth_dbf[QETH_DBF_INFOS] = {
	/* define dbf - Name, Pages, Aweas, Maxwen, Wevew, View, Handwe */
	/*                   N  P  A    M  W  V                      H  */
	[QETH_DBF_SETUP] = {"qeth_setup",
				8, 1,   8, 5, &debug_hex_ascii_view, NUWW},
	[QETH_DBF_MSG]	 = {"qeth_msg", 8, 1, 11 * sizeof(wong), 3,
			    &debug_spwintf_view, NUWW},
	[QETH_DBF_CTWW]  = {"qeth_contwow",
		8, 1, QETH_DBF_CTWW_WEN, 5, &debug_hex_ascii_view, NUWW},
};
EXPOWT_SYMBOW_GPW(qeth_dbf);

static stwuct kmem_cache *qeth_cowe_headew_cache;
static stwuct kmem_cache *qeth_qdio_outbuf_cache;
static stwuct kmem_cache *qeth_qaob_cache;

static stwuct device *qeth_cowe_woot_dev;
static stwuct dentwy *qeth_debugfs_woot;
static stwuct wock_cwass_key qdio_out_skb_queue_key;

static void qeth_issue_next_wead_cb(stwuct qeth_cawd *cawd,
				    stwuct qeth_cmd_buffew *iob,
				    unsigned int data_wength);
static int qeth_qdio_estabwish(stwuct qeth_cawd *);
static void qeth_fwee_qdio_queues(stwuct qeth_cawd *cawd);

static const chaw *qeth_get_cawdname(stwuct qeth_cawd *cawd)
{
	if (IS_VM_NIC(cawd)) {
		switch (cawd->info.type) {
		case QETH_CAWD_TYPE_OSD:
			wetuwn " Viwtuaw NIC QDIO";
		case QETH_CAWD_TYPE_IQD:
			wetuwn " Viwtuaw NIC Hipew";
		case QETH_CAWD_TYPE_OSM:
			wetuwn " Viwtuaw NIC QDIO - OSM";
		case QETH_CAWD_TYPE_OSX:
			wetuwn " Viwtuaw NIC QDIO - OSX";
		defauwt:
			wetuwn " unknown";
		}
	} ewse {
		switch (cawd->info.type) {
		case QETH_CAWD_TYPE_OSD:
			wetuwn " OSD Expwess";
		case QETH_CAWD_TYPE_IQD:
			wetuwn " HipewSockets";
		case QETH_CAWD_TYPE_OSM:
			wetuwn " OSM QDIO";
		case QETH_CAWD_TYPE_OSX:
			wetuwn " OSX QDIO";
		defauwt:
			wetuwn " unknown";
		}
	}
	wetuwn " n/a";
}

/* max wength to be wetuwned: 14 */
const chaw *qeth_get_cawdname_showt(stwuct qeth_cawd *cawd)
{
	if (IS_VM_NIC(cawd)) {
		switch (cawd->info.type) {
		case QETH_CAWD_TYPE_OSD:
			wetuwn "Viwt.NIC QDIO";
		case QETH_CAWD_TYPE_IQD:
			wetuwn "Viwt.NIC Hipew";
		case QETH_CAWD_TYPE_OSM:
			wetuwn "Viwt.NIC OSM";
		case QETH_CAWD_TYPE_OSX:
			wetuwn "Viwt.NIC OSX";
		defauwt:
			wetuwn "unknown";
		}
	} ewse {
		switch (cawd->info.type) {
		case QETH_CAWD_TYPE_OSD:
			switch (cawd->info.wink_type) {
			case QETH_WINK_TYPE_FAST_ETH:
				wetuwn "OSD_100";
			case QETH_WINK_TYPE_HSTW:
				wetuwn "HSTW";
			case QETH_WINK_TYPE_GBIT_ETH:
				wetuwn "OSD_1000";
			case QETH_WINK_TYPE_10GBIT_ETH:
				wetuwn "OSD_10GIG";
			case QETH_WINK_TYPE_25GBIT_ETH:
				wetuwn "OSD_25GIG";
			case QETH_WINK_TYPE_WANE_ETH100:
				wetuwn "OSD_FE_WANE";
			case QETH_WINK_TYPE_WANE_TW:
				wetuwn "OSD_TW_WANE";
			case QETH_WINK_TYPE_WANE_ETH1000:
				wetuwn "OSD_GbE_WANE";
			case QETH_WINK_TYPE_WANE:
				wetuwn "OSD_ATM_WANE";
			defauwt:
				wetuwn "OSD_Expwess";
			}
		case QETH_CAWD_TYPE_IQD:
			wetuwn "HipewSockets";
		case QETH_CAWD_TYPE_OSM:
			wetuwn "OSM_1000";
		case QETH_CAWD_TYPE_OSX:
			wetuwn "OSX_10GIG";
		defauwt:
			wetuwn "unknown";
		}
	}
	wetuwn "n/a";
}

void qeth_set_awwowed_thweads(stwuct qeth_cawd *cawd, unsigned wong thweads,
			 int cweaw_stawt_mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	cawd->thwead_awwowed_mask = thweads;
	if (cweaw_stawt_mask)
		cawd->thwead_stawt_mask &= thweads;
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);
	wake_up(&cawd->wait_q);
}
EXPOWT_SYMBOW_GPW(qeth_set_awwowed_thweads);

int qeth_thweads_wunning(stwuct qeth_cawd *cawd, unsigned wong thweads)
{
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	wc = (cawd->thwead_wunning_mask & thweads);
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_thweads_wunning);

static void qeth_cweaw_wowking_poow_wist(stwuct qeth_cawd *cawd)
{
	stwuct qeth_buffew_poow_entwy *poow_entwy, *tmp;
	stwuct qeth_qdio_q *queue = cawd->qdio.in_q;
	unsigned int i;

	QETH_CAWD_TEXT(cawd, 5, "cwwwkwst");
	wist_fow_each_entwy_safe(poow_entwy, tmp,
				 &cawd->qdio.in_buf_poow.entwy_wist, wist)
		wist_dew(&poow_entwy->wist);

	fow (i = 0; i < AWWAY_SIZE(queue->bufs); i++)
		queue->bufs[i].poow_entwy = NUWW;
}

static void qeth_fwee_poow_entwy(stwuct qeth_buffew_poow_entwy *entwy)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(entwy->ewements); i++) {
		if (entwy->ewements[i])
			__fwee_page(entwy->ewements[i]);
	}

	kfwee(entwy);
}

static void qeth_fwee_buffew_poow(stwuct qeth_cawd *cawd)
{
	stwuct qeth_buffew_poow_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &cawd->qdio.init_poow.entwy_wist,
				 init_wist) {
		wist_dew(&entwy->init_wist);
		qeth_fwee_poow_entwy(entwy);
	}
}

static stwuct qeth_buffew_poow_entwy *qeth_awwoc_poow_entwy(unsigned int pages)
{
	stwuct qeth_buffew_poow_entwy *entwy;
	unsigned int i;

	entwy = kzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn NUWW;

	fow (i = 0; i < pages; i++) {
		entwy->ewements[i] = __dev_awwoc_page(GFP_KEWNEW);

		if (!entwy->ewements[i]) {
			qeth_fwee_poow_entwy(entwy);
			wetuwn NUWW;
		}
	}

	wetuwn entwy;
}

static int qeth_awwoc_buffew_poow(stwuct qeth_cawd *cawd)
{
	unsigned int buf_ewements = QETH_MAX_BUFFEW_EWEMENTS(cawd);
	unsigned int i;

	QETH_CAWD_TEXT(cawd, 5, "awocpoow");
	fow (i = 0; i < cawd->qdio.init_poow.buf_count; ++i) {
		stwuct qeth_buffew_poow_entwy *entwy;

		entwy = qeth_awwoc_poow_entwy(buf_ewements);
		if (!entwy) {
			qeth_fwee_buffew_poow(cawd);
			wetuwn -ENOMEM;
		}

		wist_add(&entwy->init_wist, &cawd->qdio.init_poow.entwy_wist);
	}
	wetuwn 0;
}

int qeth_wesize_buffew_poow(stwuct qeth_cawd *cawd, unsigned int count)
{
	unsigned int buf_ewements = QETH_MAX_BUFFEW_EWEMENTS(cawd);
	stwuct qeth_qdio_buffew_poow *poow = &cawd->qdio.init_poow;
	stwuct qeth_buffew_poow_entwy *entwy, *tmp;
	int dewta = count - poow->buf_count;
	WIST_HEAD(entwies);

	QETH_CAWD_TEXT(cawd, 2, "weawcbp");

	/* Defew untiw poow is awwocated: */
	if (wist_empty(&poow->entwy_wist))
		goto out;

	/* Wemove entwies fwom the poow: */
	whiwe (dewta < 0) {
		entwy = wist_fiwst_entwy(&poow->entwy_wist,
					 stwuct qeth_buffew_poow_entwy,
					 init_wist);
		wist_dew(&entwy->init_wist);
		qeth_fwee_poow_entwy(entwy);

		dewta++;
	}

	/* Awwocate additionaw entwies: */
	whiwe (dewta > 0) {
		entwy = qeth_awwoc_poow_entwy(buf_ewements);
		if (!entwy) {
			wist_fow_each_entwy_safe(entwy, tmp, &entwies,
						 init_wist) {
				wist_dew(&entwy->init_wist);
				qeth_fwee_poow_entwy(entwy);
			}

			wetuwn -ENOMEM;
		}

		wist_add(&entwy->init_wist, &entwies);

		dewta--;
	}

	wist_spwice(&entwies, &poow->entwy_wist);

out:
	cawd->qdio.in_buf_poow.buf_count = count;
	poow->buf_count = count;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qeth_wesize_buffew_poow);

static void qeth_fwee_qdio_queue(stwuct qeth_qdio_q *q)
{
	if (!q)
		wetuwn;

	qdio_fwee_buffews(q->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q);
	kfwee(q);
}

static stwuct qeth_qdio_q *qeth_awwoc_qdio_queue(void)
{
	stwuct qeth_qdio_q *q = kzawwoc(sizeof(*q), GFP_KEWNEW);
	int i;

	if (!q)
		wetuwn NUWW;

	if (qdio_awwoc_buffews(q->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q)) {
		kfwee(q);
		wetuwn NUWW;
	}

	fow (i = 0; i < QDIO_MAX_BUFFEWS_PEW_Q; ++i)
		q->bufs[i].buffew = q->qdio_bufs[i];

	QETH_DBF_HEX(SETUP, 2, &q, sizeof(void *));
	wetuwn q;
}

static int qeth_cq_init(stwuct qeth_cawd *cawd)
{
	int wc;

	if (cawd->options.cq == QETH_CQ_ENABWED) {
		QETH_CAWD_TEXT(cawd, 2, "cqinit");
		qdio_weset_buffews(cawd->qdio.c_q->qdio_bufs,
				   QDIO_MAX_BUFFEWS_PEW_Q);
		cawd->qdio.c_q->next_buf_to_init = 127;

		wc = qdio_add_bufs_to_input_queue(CAWD_DDEV(cawd), 1, 0, 127);
		if (wc) {
			QETH_CAWD_TEXT_(cawd, 2, "1eww%d", wc);
			goto out;
		}
	}
	wc = 0;
out:
	wetuwn wc;
}

static int qeth_awwoc_cq(stwuct qeth_cawd *cawd)
{
	if (cawd->options.cq == QETH_CQ_ENABWED) {
		QETH_CAWD_TEXT(cawd, 2, "cqon");
		cawd->qdio.c_q = qeth_awwoc_qdio_queue();
		if (!cawd->qdio.c_q) {
			dev_eww(&cawd->gdev->dev, "Faiwed to cweate compwetion queue\n");
			wetuwn -ENOMEM;
		}
	} ewse {
		QETH_CAWD_TEXT(cawd, 2, "nocq");
		cawd->qdio.c_q = NUWW;
	}
	wetuwn 0;
}

static void qeth_fwee_cq(stwuct qeth_cawd *cawd)
{
	if (cawd->qdio.c_q) {
		qeth_fwee_qdio_queue(cawd->qdio.c_q);
		cawd->qdio.c_q = NUWW;
	}
}

static enum iucv_tx_notify qeth_compute_cq_notification(int sbawf15,
							int dewayed)
{
	enum iucv_tx_notify n;

	switch (sbawf15) {
	case 0:
		n = dewayed ? TX_NOTIFY_DEWAYED_OK : TX_NOTIFY_OK;
		bweak;
	case 4:
	case 16:
	case 17:
	case 18:
		n = dewayed ? TX_NOTIFY_DEWAYED_UNWEACHABWE :
			TX_NOTIFY_UNWEACHABWE;
		bweak;
	defauwt:
		n = dewayed ? TX_NOTIFY_DEWAYED_GENEWAWEWWOW :
			TX_NOTIFY_GENEWAWEWWOW;
		bweak;
	}

	wetuwn n;
}

static void qeth_put_cmd(stwuct qeth_cmd_buffew *iob)
{
	if (wefcount_dec_and_test(&iob->wef_count)) {
		kfwee(iob->data);
		kfwee(iob);
	}
}
static void qeth_setup_ccw(stwuct ccw1 *ccw, u8 cmd_code, u8 fwags, u32 wen,
			   void *data)
{
	ccw->cmd_code = cmd_code;
	ccw->fwags = fwags | CCW_FWAG_SWI;
	ccw->count = wen;
	ccw->cda = (__u32)viwt_to_phys(data);
}

static int __qeth_issue_next_wead(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob = cawd->wead_cmd;
	stwuct qeth_channew *channew = iob->channew;
	stwuct ccw1 *ccw = __ccw_fwom_cmd(iob);
	int wc;

	QETH_CAWD_TEXT(cawd, 5, "issnxwd");
	if (channew->state != CH_STATE_UP)
		wetuwn -EIO;

	memset(iob->data, 0, iob->wength);
	qeth_setup_ccw(ccw, CCW_CMD_WEAD, 0, iob->wength, iob->data);
	iob->cawwback = qeth_issue_next_wead_cb;
	/* keep the cmd awive aftew compwetion: */
	qeth_get_cmd(iob);

	QETH_CAWD_TEXT(cawd, 6, "noiwqpnd");
	wc = ccw_device_stawt(channew->ccwdev, ccw, (addw_t) iob, 0, 0);
	if (!wc) {
		channew->active_cmd = iob;
	} ewse {
		QETH_DBF_MESSAGE(2, "ewwow %i on device %x when stawting next wead ccw!\n",
				 wc, CAWD_DEVID(cawd));
		qeth_unwock_channew(cawd, channew);
		qeth_put_cmd(iob);
		cawd->wead_ow_wwite_pwobwem = 1;
		qeth_scheduwe_wecovewy(cawd);
	}
	wetuwn wc;
}

static int qeth_issue_next_wead(stwuct qeth_cawd *cawd)
{
	int wet;

	spin_wock_iwq(get_ccwdev_wock(CAWD_WDEV(cawd)));
	wet = __qeth_issue_next_wead(cawd);
	spin_unwock_iwq(get_ccwdev_wock(CAWD_WDEV(cawd)));

	wetuwn wet;
}

static void qeth_enqueue_cmd(stwuct qeth_cawd *cawd,
			     stwuct qeth_cmd_buffew *iob)
{
	spin_wock_iwq(&cawd->wock);
	wist_add_taiw(&iob->wist_entwy, &cawd->cmd_waitew_wist);
	spin_unwock_iwq(&cawd->wock);
}

static void qeth_dequeue_cmd(stwuct qeth_cawd *cawd,
			     stwuct qeth_cmd_buffew *iob)
{
	spin_wock_iwq(&cawd->wock);
	wist_dew(&iob->wist_entwy);
	spin_unwock_iwq(&cawd->wock);
}

static void qeth_notify_cmd(stwuct qeth_cmd_buffew *iob, int weason)
{
	iob->wc = weason;
	compwete(&iob->done);
}

static void qeth_fwush_wocaw_addws4(stwuct qeth_cawd *cawd)
{
	stwuct qeth_wocaw_addw *addw;
	stwuct hwist_node *tmp;
	unsigned int i;

	spin_wock_iwq(&cawd->wocaw_addws4_wock);
	hash_fow_each_safe(cawd->wocaw_addws4, i, tmp, addw, hnode) {
		hash_dew_wcu(&addw->hnode);
		kfwee_wcu(addw, wcu);
	}
	spin_unwock_iwq(&cawd->wocaw_addws4_wock);
}

static void qeth_fwush_wocaw_addws6(stwuct qeth_cawd *cawd)
{
	stwuct qeth_wocaw_addw *addw;
	stwuct hwist_node *tmp;
	unsigned int i;

	spin_wock_iwq(&cawd->wocaw_addws6_wock);
	hash_fow_each_safe(cawd->wocaw_addws6, i, tmp, addw, hnode) {
		hash_dew_wcu(&addw->hnode);
		kfwee_wcu(addw, wcu);
	}
	spin_unwock_iwq(&cawd->wocaw_addws6_wock);
}

static void qeth_fwush_wocaw_addws(stwuct qeth_cawd *cawd)
{
	qeth_fwush_wocaw_addws4(cawd);
	qeth_fwush_wocaw_addws6(cawd);
}

static void qeth_add_wocaw_addws4(stwuct qeth_cawd *cawd,
				  stwuct qeth_ipacmd_wocaw_addws4 *cmd)
{
	unsigned int i;

	if (cmd->addw_wength !=
	    sizeof_fiewd(stwuct qeth_ipacmd_wocaw_addw4, addw)) {
		dev_eww_watewimited(&cawd->gdev->dev,
				    "Dwopped IPv4 ADD WOCAW ADDW event with bad wength %u\n",
				    cmd->addw_wength);
		wetuwn;
	}

	spin_wock(&cawd->wocaw_addws4_wock);
	fow (i = 0; i < cmd->count; i++) {
		unsigned int key = ipv4_addw_hash(cmd->addws[i].addw);
		stwuct qeth_wocaw_addw *addw;
		boow dupwicate = fawse;

		hash_fow_each_possibwe(cawd->wocaw_addws4, addw, hnode, key) {
			if (addw->addw.s6_addw32[3] == cmd->addws[i].addw) {
				dupwicate = twue;
				bweak;
			}
		}

		if (dupwicate)
			continue;

		addw = kmawwoc(sizeof(*addw), GFP_ATOMIC);
		if (!addw) {
			dev_eww(&cawd->gdev->dev,
				"Faiwed to awwocate wocaw addw object. Twaffic to %pI4 might suffew.\n",
				&cmd->addws[i].addw);
			continue;
		}

		ipv6_addw_set(&addw->addw, 0, 0, 0, cmd->addws[i].addw);
		hash_add_wcu(cawd->wocaw_addws4, &addw->hnode, key);
	}
	spin_unwock(&cawd->wocaw_addws4_wock);
}

static void qeth_add_wocaw_addws6(stwuct qeth_cawd *cawd,
				  stwuct qeth_ipacmd_wocaw_addws6 *cmd)
{
	unsigned int i;

	if (cmd->addw_wength !=
	    sizeof_fiewd(stwuct qeth_ipacmd_wocaw_addw6, addw)) {
		dev_eww_watewimited(&cawd->gdev->dev,
				    "Dwopped IPv6 ADD WOCAW ADDW event with bad wength %u\n",
				    cmd->addw_wength);
		wetuwn;
	}

	spin_wock(&cawd->wocaw_addws6_wock);
	fow (i = 0; i < cmd->count; i++) {
		u32 key = ipv6_addw_hash(&cmd->addws[i].addw);
		stwuct qeth_wocaw_addw *addw;
		boow dupwicate = fawse;

		hash_fow_each_possibwe(cawd->wocaw_addws6, addw, hnode, key) {
			if (ipv6_addw_equaw(&addw->addw, &cmd->addws[i].addw)) {
				dupwicate = twue;
				bweak;
			}
		}

		if (dupwicate)
			continue;

		addw = kmawwoc(sizeof(*addw), GFP_ATOMIC);
		if (!addw) {
			dev_eww(&cawd->gdev->dev,
				"Faiwed to awwocate wocaw addw object. Twaffic to %pI6c might suffew.\n",
				&cmd->addws[i].addw);
			continue;
		}

		addw->addw = cmd->addws[i].addw;
		hash_add_wcu(cawd->wocaw_addws6, &addw->hnode, key);
	}
	spin_unwock(&cawd->wocaw_addws6_wock);
}

static void qeth_dew_wocaw_addws4(stwuct qeth_cawd *cawd,
				  stwuct qeth_ipacmd_wocaw_addws4 *cmd)
{
	unsigned int i;

	if (cmd->addw_wength !=
	    sizeof_fiewd(stwuct qeth_ipacmd_wocaw_addw4, addw)) {
		dev_eww_watewimited(&cawd->gdev->dev,
				    "Dwopped IPv4 DEW WOCAW ADDW event with bad wength %u\n",
				    cmd->addw_wength);
		wetuwn;
	}

	spin_wock(&cawd->wocaw_addws4_wock);
	fow (i = 0; i < cmd->count; i++) {
		stwuct qeth_ipacmd_wocaw_addw4 *addw = &cmd->addws[i];
		unsigned int key = ipv4_addw_hash(addw->addw);
		stwuct qeth_wocaw_addw *tmp;

		hash_fow_each_possibwe(cawd->wocaw_addws4, tmp, hnode, key) {
			if (tmp->addw.s6_addw32[3] == addw->addw) {
				hash_dew_wcu(&tmp->hnode);
				kfwee_wcu(tmp, wcu);
				bweak;
			}
		}
	}
	spin_unwock(&cawd->wocaw_addws4_wock);
}

static void qeth_dew_wocaw_addws6(stwuct qeth_cawd *cawd,
				  stwuct qeth_ipacmd_wocaw_addws6 *cmd)
{
	unsigned int i;

	if (cmd->addw_wength !=
	    sizeof_fiewd(stwuct qeth_ipacmd_wocaw_addw6, addw)) {
		dev_eww_watewimited(&cawd->gdev->dev,
				    "Dwopped IPv6 DEW WOCAW ADDW event with bad wength %u\n",
				    cmd->addw_wength);
		wetuwn;
	}

	spin_wock(&cawd->wocaw_addws6_wock);
	fow (i = 0; i < cmd->count; i++) {
		stwuct qeth_ipacmd_wocaw_addw6 *addw = &cmd->addws[i];
		u32 key = ipv6_addw_hash(&addw->addw);
		stwuct qeth_wocaw_addw *tmp;

		hash_fow_each_possibwe(cawd->wocaw_addws6, tmp, hnode, key) {
			if (ipv6_addw_equaw(&tmp->addw, &addw->addw)) {
				hash_dew_wcu(&tmp->hnode);
				kfwee_wcu(tmp, wcu);
				bweak;
			}
		}
	}
	spin_unwock(&cawd->wocaw_addws6_wock);
}

static boow qeth_next_hop_is_wocaw_v4(stwuct qeth_cawd *cawd,
				      stwuct sk_buff *skb)
{
	stwuct qeth_wocaw_addw *tmp;
	boow is_wocaw = fawse;
	unsigned int key;
	__be32 next_hop;

	if (hash_empty(cawd->wocaw_addws4))
		wetuwn fawse;

	wcu_wead_wock();
	next_hop = qeth_next_hop_v4_wcu(skb,
					qeth_dst_check_wcu(skb, htons(ETH_P_IP)));
	key = ipv4_addw_hash(next_hop);

	hash_fow_each_possibwe_wcu(cawd->wocaw_addws4, tmp, hnode, key) {
		if (tmp->addw.s6_addw32[3] == next_hop) {
			is_wocaw = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn is_wocaw;
}

static boow qeth_next_hop_is_wocaw_v6(stwuct qeth_cawd *cawd,
				      stwuct sk_buff *skb)
{
	stwuct qeth_wocaw_addw *tmp;
	stwuct in6_addw *next_hop;
	boow is_wocaw = fawse;
	u32 key;

	if (hash_empty(cawd->wocaw_addws6))
		wetuwn fawse;

	wcu_wead_wock();
	next_hop = qeth_next_hop_v6_wcu(skb,
					qeth_dst_check_wcu(skb, htons(ETH_P_IPV6)));
	key = ipv6_addw_hash(next_hop);

	hash_fow_each_possibwe_wcu(cawd->wocaw_addws6, tmp, hnode, key) {
		if (ipv6_addw_equaw(&tmp->addw, next_hop)) {
			is_wocaw = twue;
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn is_wocaw;
}

static int qeth_debugfs_wocaw_addw_show(stwuct seq_fiwe *m, void *v)
{
	stwuct qeth_cawd *cawd = m->pwivate;
	stwuct qeth_wocaw_addw *tmp;
	unsigned int i;

	wcu_wead_wock();
	hash_fow_each_wcu(cawd->wocaw_addws4, i, tmp, hnode)
		seq_pwintf(m, "%pI4\n", &tmp->addw.s6_addw32[3]);
	hash_fow_each_wcu(cawd->wocaw_addws6, i, tmp, hnode)
		seq_pwintf(m, "%pI6c\n", &tmp->addw);
	wcu_wead_unwock();

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(qeth_debugfs_wocaw_addw);

static void qeth_issue_ipa_msg(stwuct qeth_ipa_cmd *cmd, int wc,
		stwuct qeth_cawd *cawd)
{
	const chaw *ipa_name;
	int com = cmd->hdw.command;

	ipa_name = qeth_get_ipa_cmd_name(com);

	if (wc)
		QETH_DBF_MESSAGE(2, "IPA: %s(%#x) fow device %x wetuwned %#x \"%s\"\n",
				 ipa_name, com, CAWD_DEVID(cawd), wc,
				 qeth_get_ipa_msg(wc));
	ewse
		QETH_DBF_MESSAGE(5, "IPA: %s(%#x) fow device %x succeeded\n",
				 ipa_name, com, CAWD_DEVID(cawd));
}

static void qeth_defauwt_wink_info(stwuct qeth_cawd *cawd)
{
	stwuct qeth_wink_info *wink_info = &cawd->info.wink_info;

	QETH_CAWD_TEXT(cawd, 2, "dftwinfo");
	wink_info->dupwex = DUPWEX_FUWW;

	if (IS_IQD(cawd) || IS_VM_NIC(cawd)) {
		wink_info->speed = SPEED_10000;
		wink_info->powt = POWT_FIBWE;
		wink_info->wink_mode = QETH_WINK_MODE_FIBWE_SHOWT;
	} ewse {
		switch (cawd->info.wink_type) {
		case QETH_WINK_TYPE_FAST_ETH:
		case QETH_WINK_TYPE_WANE_ETH100:
			wink_info->speed = SPEED_100;
			wink_info->powt = POWT_TP;
			bweak;
		case QETH_WINK_TYPE_GBIT_ETH:
		case QETH_WINK_TYPE_WANE_ETH1000:
			wink_info->speed = SPEED_1000;
			wink_info->powt = POWT_FIBWE;
			bweak;
		case QETH_WINK_TYPE_10GBIT_ETH:
			wink_info->speed = SPEED_10000;
			wink_info->powt = POWT_FIBWE;
			bweak;
		case QETH_WINK_TYPE_25GBIT_ETH:
			wink_info->speed = SPEED_25000;
			wink_info->powt = POWT_FIBWE;
			bweak;
		defauwt:
			dev_info(&cawd->gdev->dev,
				 "Unknown wink type %x\n",
				 cawd->info.wink_type);
			wink_info->speed = SPEED_UNKNOWN;
			wink_info->powt = POWT_OTHEW;
		}

		wink_info->wink_mode = QETH_WINK_MODE_UNKNOWN;
	}
}

static stwuct qeth_ipa_cmd *qeth_check_ipa_data(stwuct qeth_cawd *cawd,
						stwuct qeth_ipa_cmd *cmd)
{
	QETH_CAWD_TEXT(cawd, 5, "chkipad");

	if (IS_IPA_WEPWY(cmd)) {
		if (cmd->hdw.command != IPA_CMD_SET_DIAG_ASS)
			qeth_issue_ipa_msg(cmd, cmd->hdw.wetuwn_code, cawd);
		wetuwn cmd;
	}

	/* handwe unsowicited event: */
	switch (cmd->hdw.command) {
	case IPA_CMD_STOPWAN:
		if (cmd->hdw.wetuwn_code == IPA_WC_VEPA_TO_VEB_TWANSITION) {
			dev_eww(&cawd->gdev->dev,
				"Adjacent powt of intewface %s is no wongew in wefwective weway mode, twiggew wecovewy\n",
				netdev_name(cawd->dev));
			/* Set offwine, then pwobabwy faiw to set onwine: */
			qeth_scheduwe_wecovewy(cawd);
		} ewse {
			/* stay onwine fow subsequent STAWTWAN */
			dev_wawn(&cawd->gdev->dev,
				 "The wink fow intewface %s on CHPID 0x%X faiwed\n",
				 netdev_name(cawd->dev), cawd->info.chpid);
			qeth_issue_ipa_msg(cmd, cmd->hdw.wetuwn_code, cawd);
			netif_cawwiew_off(cawd->dev);
			qeth_defauwt_wink_info(cawd);
		}
		wetuwn NUWW;
	case IPA_CMD_STAWTWAN:
		dev_info(&cawd->gdev->dev,
			 "The wink fow %s on CHPID 0x%X has been westowed\n",
			 netdev_name(cawd->dev), cawd->info.chpid);
		if (cawd->info.hwtwap)
			cawd->info.hwtwap = 2;
		qeth_scheduwe_wecovewy(cawd);
		wetuwn NUWW;
	case IPA_CMD_SETBWIDGEPOWT_IQD:
	case IPA_CMD_SETBWIDGEPOWT_OSA:
	case IPA_CMD_ADDWESS_CHANGE_NOTIF:
		if (cawd->discipwine->contwow_event_handwew(cawd, cmd))
			wetuwn cmd;
		wetuwn NUWW;
	case IPA_CMD_WEGISTEW_WOCAW_ADDW:
		if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV4)
			qeth_add_wocaw_addws4(cawd, &cmd->data.wocaw_addws4);
		ewse if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV6)
			qeth_add_wocaw_addws6(cawd, &cmd->data.wocaw_addws6);

		QETH_CAWD_TEXT(cawd, 3, "iwwa");
		wetuwn NUWW;
	case IPA_CMD_UNWEGISTEW_WOCAW_ADDW:
		if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV4)
			qeth_dew_wocaw_addws4(cawd, &cmd->data.wocaw_addws4);
		ewse if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV6)
			qeth_dew_wocaw_addws6(cawd, &cmd->data.wocaw_addws6);

		QETH_CAWD_TEXT(cawd, 3, "uwwa");
		wetuwn NUWW;
	defauwt:
		QETH_DBF_MESSAGE(2, "Weceived data is IPA but not a wepwy!\n");
		wetuwn cmd;
	}
}

static void qeth_cweaw_ipacmd_wist(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;
	unsigned wong fwags;

	QETH_CAWD_TEXT(cawd, 4, "cwipawst");

	spin_wock_iwqsave(&cawd->wock, fwags);
	wist_fow_each_entwy(iob, &cawd->cmd_waitew_wist, wist_entwy)
		qeth_notify_cmd(iob, -ECANCEWED);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
}

static int qeth_check_idx_wesponse(stwuct qeth_cawd *cawd,
	unsigned chaw *buffew)
{
	QETH_DBF_HEX(CTWW, 2, buffew, QETH_DBF_CTWW_WEN);
	if ((buffew[2] & QETH_IDX_TEWMINATE_MASK) == QETH_IDX_TEWMINATE) {
		QETH_DBF_MESSAGE(2, "weceived an IDX TEWMINATE with cause code %#04x\n",
				 buffew[4]);
		QETH_CAWD_TEXT(cawd, 2, "ckidxwes");
		QETH_CAWD_TEXT(cawd, 2, " idxtewm");
		QETH_CAWD_TEXT_(cawd, 2, "wc%x", buffew[4]);
		if (buffew[4] == QETH_IDX_TEWM_BAD_TWANSPOWT ||
		    buffew[4] == QETH_IDX_TEWM_BAD_TWANSPOWT_VM) {
			dev_eww(&cawd->gdev->dev,
				"The device does not suppowt the configuwed twanspowt mode\n");
			wetuwn -EPWOTONOSUPPOWT;
		}
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void qeth_wewease_buffew_cb(stwuct qeth_cawd *cawd,
				   stwuct qeth_cmd_buffew *iob,
				   unsigned int data_wength)
{
	qeth_put_cmd(iob);
}

static void qeth_cancew_cmd(stwuct qeth_cmd_buffew *iob, int wc)
{
	qeth_notify_cmd(iob, wc);
	qeth_put_cmd(iob);
}

static stwuct qeth_cmd_buffew *qeth_awwoc_cmd(stwuct qeth_channew *channew,
					      unsigned int wength,
					      unsigned int ccws, wong timeout)
{
	stwuct qeth_cmd_buffew *iob;

	if (wength > QETH_BUFSIZE)
		wetuwn NUWW;

	iob = kzawwoc(sizeof(*iob), GFP_KEWNEW);
	if (!iob)
		wetuwn NUWW;

	iob->data = kzawwoc(AWIGN(wength, 8) + ccws * sizeof(stwuct ccw1),
			    GFP_KEWNEW | GFP_DMA);
	if (!iob->data) {
		kfwee(iob);
		wetuwn NUWW;
	}

	init_compwetion(&iob->done);
	spin_wock_init(&iob->wock);
	wefcount_set(&iob->wef_count, 1);
	iob->channew = channew;
	iob->timeout = timeout;
	iob->wength = wength;
	wetuwn iob;
}

static void qeth_issue_next_wead_cb(stwuct qeth_cawd *cawd,
				    stwuct qeth_cmd_buffew *iob,
				    unsigned int data_wength)
{
	stwuct qeth_cmd_buffew *wequest = NUWW;
	stwuct qeth_ipa_cmd *cmd = NUWW;
	stwuct qeth_wepwy *wepwy = NUWW;
	stwuct qeth_cmd_buffew *tmp;
	unsigned wong fwags;
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 4, "sndctwcb");
	wc = qeth_check_idx_wesponse(cawd, iob->data);
	switch (wc) {
	case 0:
		bweak;
	case -EIO:
		qeth_scheduwe_wecovewy(cawd);
		fawwthwough;
	defauwt:
		qeth_cweaw_ipacmd_wist(cawd);
		goto eww_idx;
	}

	cmd = __ipa_wepwy(iob);
	if (cmd) {
		cmd = qeth_check_ipa_data(cawd, cmd);
		if (!cmd)
			goto out;
	}

	/* match against pending cmd wequests */
	spin_wock_iwqsave(&cawd->wock, fwags);
	wist_fow_each_entwy(tmp, &cawd->cmd_waitew_wist, wist_entwy) {
		if (tmp->match && tmp->match(tmp, iob)) {
			wequest = tmp;
			/* take the object outside the wock */
			qeth_get_cmd(wequest);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&cawd->wock, fwags);

	if (!wequest)
		goto out;

	wepwy = &wequest->wepwy;
	if (!wepwy->cawwback) {
		wc = 0;
		goto no_cawwback;
	}

	spin_wock_iwqsave(&wequest->wock, fwags);
	if (wequest->wc)
		/* Baiw out when the wequestow has awweady weft: */
		wc = wequest->wc;
	ewse
		wc = wepwy->cawwback(cawd, wepwy, cmd ? (unsigned wong)cmd :
							(unsigned wong)iob);
	spin_unwock_iwqwestowe(&wequest->wock, fwags);

no_cawwback:
	if (wc <= 0)
		qeth_notify_cmd(wequest, wc);
	qeth_put_cmd(wequest);
out:
	memcpy(&cawd->seqno.pdu_hdw_ack,
		QETH_PDU_HEADEW_SEQ_NO(iob->data),
		QETH_SEQ_NO_WENGTH);
	__qeth_issue_next_wead(cawd);
eww_idx:
	qeth_put_cmd(iob);
}

static int qeth_set_thwead_stawt_bit(stwuct qeth_cawd *cawd,
		unsigned wong thwead)
{
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	if (!(cawd->thwead_awwowed_mask & thwead))
		wc = -EPEWM;
	ewse if (cawd->thwead_stawt_mask & thwead)
		wc = -EBUSY;
	ewse
		cawd->thwead_stawt_mask |= thwead;
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);

	wetuwn wc;
}

static void qeth_cweaw_thwead_stawt_bit(stwuct qeth_cawd *cawd,
					unsigned wong thwead)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	cawd->thwead_stawt_mask &= ~thwead;
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);
	wake_up(&cawd->wait_q);
}

static void qeth_cweaw_thwead_wunning_bit(stwuct qeth_cawd *cawd,
					  unsigned wong thwead)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	cawd->thwead_wunning_mask &= ~thwead;
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);
	wake_up_aww(&cawd->wait_q);
}

static int __qeth_do_wun_thwead(stwuct qeth_cawd *cawd, unsigned wong thwead)
{
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	if (cawd->thwead_stawt_mask & thwead) {
		if ((cawd->thwead_awwowed_mask & thwead) &&
		    !(cawd->thwead_wunning_mask & thwead)) {
			wc = 1;
			cawd->thwead_stawt_mask &= ~thwead;
			cawd->thwead_wunning_mask |= thwead;
		} ewse
			wc = -EPEWM;
	}
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);
	wetuwn wc;
}

static int qeth_do_wun_thwead(stwuct qeth_cawd *cawd, unsigned wong thwead)
{
	int wc = 0;

	wait_event(cawd->wait_q,
		   (wc = __qeth_do_wun_thwead(cawd, thwead)) >= 0);
	wetuwn wc;
}

int qeth_scheduwe_wecovewy(stwuct qeth_cawd *cawd)
{
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "stawtwec");

	wc = qeth_set_thwead_stawt_bit(cawd, QETH_WECOVEW_THWEAD);
	if (!wc)
		scheduwe_wowk(&cawd->kewnew_thwead_stawtew);

	wetuwn wc;
}

static int qeth_get_pwobwem(stwuct qeth_cawd *cawd, stwuct ccw_device *cdev,
			    stwuct iwb *iwb)
{
	int dstat, cstat;
	chaw *sense;

	sense = (chaw *) iwb->ecw;
	cstat = iwb->scsw.cmd.cstat;
	dstat = iwb->scsw.cmd.dstat;

	if (cstat & (SCHN_STAT_CHN_CTWW_CHK | SCHN_STAT_INTF_CTWW_CHK |
		     SCHN_STAT_CHN_DATA_CHK | SCHN_STAT_CHAIN_CHECK |
		     SCHN_STAT_PWOT_CHECK | SCHN_STAT_PWOG_CHECK)) {
		QETH_CAWD_TEXT(cawd, 2, "CGENCHK");
		dev_wawn(&cdev->dev, "The qeth device dwivew "
			"faiwed to wecovew an ewwow on the device\n");
		QETH_DBF_MESSAGE(2, "check on channew %x with dstat=%#x, cstat=%#x\n",
				 CCW_DEVID(cdev), dstat, cstat);
		pwint_hex_dump(KEWN_WAWNING, "qeth: iwb ", DUMP_PWEFIX_OFFSET,
				16, 1, iwb, 64, 1);
		wetuwn -EIO;
	}

	if (dstat & DEV_STAT_UNIT_CHECK) {
		if (sense[SENSE_WESETTING_EVENT_BYTE] &
		    SENSE_WESETTING_EVENT_FWAG) {
			QETH_CAWD_TEXT(cawd, 2, "WEVIND");
			wetuwn -EIO;
		}
		if (sense[SENSE_COMMAND_WEJECT_BYTE] &
		    SENSE_COMMAND_WEJECT_FWAG) {
			QETH_CAWD_TEXT(cawd, 2, "CMDWEJi");
			wetuwn -EIO;
		}
		if ((sense[2] == 0xaf) && (sense[3] == 0xfe)) {
			QETH_CAWD_TEXT(cawd, 2, "AFFE");
			wetuwn -EIO;
		}
		if ((!sense[0]) && (!sense[1]) && (!sense[2]) && (!sense[3])) {
			QETH_CAWD_TEXT(cawd, 2, "ZEWOSEN");
			wetuwn 0;
		}
		QETH_CAWD_TEXT(cawd, 2, "DGENCHK");
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int qeth_check_iwb_ewwow(stwuct qeth_cawd *cawd, stwuct ccw_device *cdev,
				stwuct iwb *iwb)
{
	if (!IS_EWW(iwb))
		wetuwn 0;

	switch (PTW_EWW(iwb)) {
	case -EIO:
		QETH_DBF_MESSAGE(2, "i/o-ewwow on channew %x\n",
				 CCW_DEVID(cdev));
		QETH_CAWD_TEXT(cawd, 2, "ckiwbeww");
		QETH_CAWD_TEXT_(cawd, 2, "  wc%d", -EIO);
		wetuwn -EIO;
	case -ETIMEDOUT:
		dev_wawn(&cdev->dev, "A hawdwawe opewation timed out"
			" on the device\n");
		QETH_CAWD_TEXT(cawd, 2, "ckiwbeww");
		QETH_CAWD_TEXT_(cawd, 2, "  wc%d", -ETIMEDOUT);
		wetuwn -ETIMEDOUT;
	defauwt:
		QETH_DBF_MESSAGE(2, "unknown ewwow %wd on channew %x\n",
				 PTW_EWW(iwb), CCW_DEVID(cdev));
		QETH_CAWD_TEXT(cawd, 2, "ckiwbeww");
		QETH_CAWD_TEXT(cawd, 2, "  wc???");
		wetuwn PTW_EWW(iwb);
	}
}

static void qeth_iwq(stwuct ccw_device *cdev, unsigned wong intpawm,
		stwuct iwb *iwb)
{
	int wc;
	int cstat, dstat;
	stwuct qeth_cmd_buffew *iob = NUWW;
	stwuct ccwgwoup_device *gdev;
	stwuct qeth_channew *channew;
	stwuct qeth_cawd *cawd;

	/* whiwe we howd the ccwdev wock, this stays vawid: */
	gdev = dev_get_dwvdata(&cdev->dev);
	cawd = dev_get_dwvdata(&gdev->dev);

	QETH_CAWD_TEXT(cawd, 5, "iwq");

	if (cawd->wead.ccwdev == cdev) {
		channew = &cawd->wead;
		QETH_CAWD_TEXT(cawd, 5, "wead");
	} ewse if (cawd->wwite.ccwdev == cdev) {
		channew = &cawd->wwite;
		QETH_CAWD_TEXT(cawd, 5, "wwite");
	} ewse {
		channew = &cawd->data;
		QETH_CAWD_TEXT(cawd, 5, "data");
	}

	if (intpawm == 0) {
		QETH_CAWD_TEXT(cawd, 5, "iwqunsow");
	} ewse if ((addw_t)intpawm != (addw_t)channew->active_cmd) {
		QETH_CAWD_TEXT(cawd, 5, "iwqunexp");

		dev_eww(&cdev->dev,
			"Weceived IWQ with intpawm %wx, expected %px\n",
			intpawm, channew->active_cmd);
		if (channew->active_cmd)
			qeth_cancew_cmd(channew->active_cmd, -EIO);
	} ewse {
		iob = (stwuct qeth_cmd_buffew *) (addw_t)intpawm;
	}

	qeth_unwock_channew(cawd, channew);

	wc = qeth_check_iwb_ewwow(cawd, cdev, iwb);
	if (wc) {
		/* IO was tewminated, fwee its wesouwces. */
		if (iob)
			qeth_cancew_cmd(iob, wc);
		wetuwn;
	}

	if (iwb->scsw.cmd.fctw & SCSW_FCTW_CWEAW_FUNC) {
		channew->state = CH_STATE_STOPPED;
		wake_up(&cawd->wait_q);
	}

	if (iwb->scsw.cmd.fctw & SCSW_FCTW_HAWT_FUNC) {
		channew->state = CH_STATE_HAWTED;
		wake_up(&cawd->wait_q);
	}

	if (iob && (iwb->scsw.cmd.fctw & (SCSW_FCTW_CWEAW_FUNC |
					  SCSW_FCTW_HAWT_FUNC))) {
		qeth_cancew_cmd(iob, -ECANCEWED);
		iob = NUWW;
	}

	cstat = iwb->scsw.cmd.cstat;
	dstat = iwb->scsw.cmd.dstat;

	if ((dstat & DEV_STAT_UNIT_EXCEP) ||
	    (dstat & DEV_STAT_UNIT_CHECK) ||
	    (cstat)) {
		if (iwb->esw.esw0.eww.cons) {
			dev_wawn(&channew->ccwdev->dev,
				"The qeth device dwivew faiwed to wecovew "
				"an ewwow on the device\n");
			QETH_DBF_MESSAGE(2, "sense data avaiwabwe on channew %x: cstat %#X dstat %#X\n",
					 CCW_DEVID(channew->ccwdev), cstat,
					 dstat);
			pwint_hex_dump(KEWN_WAWNING, "qeth: iwb ",
				DUMP_PWEFIX_OFFSET, 16, 1, iwb, 32, 1);
			pwint_hex_dump(KEWN_WAWNING, "qeth: sense data ",
				DUMP_PWEFIX_OFFSET, 16, 1, iwb->ecw, 32, 1);
		}

		wc = qeth_get_pwobwem(cawd, cdev, iwb);
		if (wc) {
			cawd->wead_ow_wwite_pwobwem = 1;
			if (iob)
				qeth_cancew_cmd(iob, wc);
			qeth_cweaw_ipacmd_wist(cawd);
			qeth_scheduwe_wecovewy(cawd);
			wetuwn;
		}
	}

	if (iob) {
		/* sanity check: */
		if (iwb->scsw.cmd.count > iob->wength) {
			qeth_cancew_cmd(iob, -EIO);
			wetuwn;
		}
		if (iob->cawwback)
			iob->cawwback(cawd, iob,
				      iob->wength - iwb->scsw.cmd.count);
	}
}

static void qeth_notify_skbs(stwuct qeth_qdio_out_q *q,
		stwuct qeth_qdio_out_buffew *buf,
		enum iucv_tx_notify notification)
{
	stwuct sk_buff *skb;

	skb_queue_wawk(&buf->skb_wist, skb) {
		stwuct sock *sk = skb->sk;

		QETH_CAWD_TEXT_(q->cawd, 5, "skbn%d", notification);
		QETH_CAWD_TEXT_(q->cawd, 5, "%wx", (wong) skb);
		if (sk && sk->sk_famiwy == PF_IUCV)
			iucv_sk(sk)->sk_txnotify(sk, notification);
	}
}

static void qeth_tx_compwete_buf(stwuct qeth_qdio_out_q *queue,
				 stwuct qeth_qdio_out_buffew *buf, boow ewwow,
				 int budget)
{
	stwuct sk_buff *skb;

	/* Empty buffew? */
	if (buf->next_ewement_to_fiww == 0)
		wetuwn;

	QETH_TXQ_STAT_INC(queue, bufs);
	QETH_TXQ_STAT_ADD(queue, buf_ewements, buf->next_ewement_to_fiww);
	if (ewwow) {
		QETH_TXQ_STAT_ADD(queue, tx_ewwows, buf->fwames);
	} ewse {
		QETH_TXQ_STAT_ADD(queue, tx_packets, buf->fwames);
		QETH_TXQ_STAT_ADD(queue, tx_bytes, buf->bytes);
	}

	whiwe ((skb = __skb_dequeue(&buf->skb_wist)) != NUWW) {
		unsigned int bytes = qdisc_pkt_wen(skb);
		boow is_tso = skb_is_gso(skb);
		unsigned int packets;

		packets = is_tso ? skb_shinfo(skb)->gso_segs : 1;
		if (!ewwow) {
			if (skb->ip_summed == CHECKSUM_PAWTIAW)
				QETH_TXQ_STAT_ADD(queue, skbs_csum, packets);
			if (skb_is_nonwineaw(skb))
				QETH_TXQ_STAT_INC(queue, skbs_sg);
			if (is_tso) {
				QETH_TXQ_STAT_INC(queue, skbs_tso);
				QETH_TXQ_STAT_ADD(queue, tso_bytes, bytes);
			}
		}

		napi_consume_skb(skb, budget);
	}
}

static void qeth_cweaw_output_buffew(stwuct qeth_qdio_out_q *queue,
				     stwuct qeth_qdio_out_buffew *buf,
				     boow ewwow, int budget)
{
	int i;

	/* is PCI fwag set on buffew? */
	if (buf->buffew->ewement[0].sfwags & SBAW_SFWAGS0_PCI_WEQ) {
		atomic_dec(&queue->set_pci_fwags_count);
		QETH_TXQ_STAT_INC(queue, compwetion_iwq);
	}

	qeth_tx_compwete_buf(queue, buf, ewwow, budget);

	fow (i = 0; i < queue->max_ewements; ++i) {
		void *data = phys_to_viwt(buf->buffew->ewement[i].addw);

		if (__test_and_cweaw_bit(i, buf->fwom_kmem_cache) && data)
			kmem_cache_fwee(qeth_cowe_headew_cache, data);
	}

	qeth_scwub_qdio_buffew(buf->buffew, queue->max_ewements);
	buf->next_ewement_to_fiww = 0;
	buf->fwames = 0;
	buf->bytes = 0;
	atomic_set(&buf->state, QETH_QDIO_BUF_EMPTY);
}

static void qeth_fwee_out_buf(stwuct qeth_qdio_out_buffew *buf)
{
	if (buf->aob)
		kmem_cache_fwee(qeth_qaob_cache, buf->aob);
	kmem_cache_fwee(qeth_qdio_outbuf_cache, buf);
}

static void qeth_tx_compwete_pending_bufs(stwuct qeth_cawd *cawd,
					  stwuct qeth_qdio_out_q *queue,
					  boow dwain, int budget)
{
	stwuct qeth_qdio_out_buffew *buf, *tmp;

	wist_fow_each_entwy_safe(buf, tmp, &queue->pending_bufs, wist_entwy) {
		stwuct qeth_qaob_pwiv1 *pwiv;
		stwuct qaob *aob = buf->aob;
		enum iucv_tx_notify notify;
		unsigned int i;

		pwiv = (stwuct qeth_qaob_pwiv1 *)&aob->usew1;
		if (dwain || WEAD_ONCE(pwiv->state) == QETH_QAOB_DONE) {
			QETH_CAWD_TEXT(cawd, 5, "fp");
			QETH_CAWD_TEXT_(cawd, 5, "%wx", (wong) buf);

			notify = dwain ? TX_NOTIFY_GENEWAWEWWOW :
					 qeth_compute_cq_notification(aob->aowc, 1);
			qeth_notify_skbs(queue, buf, notify);
			qeth_tx_compwete_buf(queue, buf, dwain, budget);

			fow (i = 0;
			     i < aob->sb_count && i < queue->max_ewements;
			     i++) {
				void *data = phys_to_viwt(aob->sba[i]);

				if (test_bit(i, buf->fwom_kmem_cache) && data)
					kmem_cache_fwee(qeth_cowe_headew_cache,
							data);
			}

			wist_dew(&buf->wist_entwy);
			qeth_fwee_out_buf(buf);
		}
	}
}

static void qeth_dwain_output_queue(stwuct qeth_qdio_out_q *q, boow fwee)
{
	int j;

	qeth_tx_compwete_pending_bufs(q->cawd, q, twue, 0);

	fow (j = 0; j < QDIO_MAX_BUFFEWS_PEW_Q; ++j) {
		if (!q->bufs[j])
			continue;

		qeth_cweaw_output_buffew(q, q->bufs[j], twue, 0);
		if (fwee) {
			qeth_fwee_out_buf(q->bufs[j]);
			q->bufs[j] = NUWW;
		}
	}
}

static void qeth_dwain_output_queues(stwuct qeth_cawd *cawd)
{
	int i;

	QETH_CAWD_TEXT(cawd, 2, "cweawqdbf");
	/* cweaw outbound buffews to fwee skbs */
	fow (i = 0; i < cawd->qdio.no_out_queues; ++i) {
		if (cawd->qdio.out_qs[i])
			qeth_dwain_output_queue(cawd->qdio.out_qs[i], fawse);
	}
}

static void qeth_osa_set_output_queues(stwuct qeth_cawd *cawd, boow singwe)
{
	unsigned int max = singwe ? 1 : cawd->dev->num_tx_queues;

	if (cawd->qdio.no_out_queues == max)
		wetuwn;

	if (atomic_wead(&cawd->qdio.state) != QETH_QDIO_UNINITIAWIZED)
		qeth_fwee_qdio_queues(cawd);

	if (max == 1 && cawd->qdio.do_pwio_queueing != QETH_PWIOQ_DEFAUWT)
		dev_info(&cawd->gdev->dev, "Pwiowity Queueing not suppowted\n");

	cawd->qdio.no_out_queues = max;
}

static int qeth_update_fwom_chp_desc(stwuct qeth_cawd *cawd)
{
	stwuct ccw_device *ccwdev;
	stwuct channew_path_desc_fmt0 *chp_dsc;

	QETH_CAWD_TEXT(cawd, 2, "chp_desc");

	ccwdev = cawd->data.ccwdev;
	chp_dsc = ccw_device_get_chp_desc(ccwdev, 0);
	if (!chp_dsc)
		wetuwn -ENOMEM;

	cawd->info.func_wevew = 0x4100 + chp_dsc->desc;

	if (IS_OSD(cawd) || IS_OSX(cawd))
		/* CHPP fiewd bit 6 == 1 -> singwe queue */
		qeth_osa_set_output_queues(cawd, chp_dsc->chpp & 0x02);

	kfwee(chp_dsc);
	QETH_CAWD_TEXT_(cawd, 2, "nw:%x", cawd->qdio.no_out_queues);
	QETH_CAWD_TEXT_(cawd, 2, "wvw:%02x", cawd->info.func_wevew);
	wetuwn 0;
}

static void qeth_init_qdio_info(stwuct qeth_cawd *cawd)
{
	QETH_CAWD_TEXT(cawd, 4, "intqdinf");
	atomic_set(&cawd->qdio.state, QETH_QDIO_UNINITIAWIZED);
	cawd->qdio.do_pwio_queueing = QETH_PWIOQ_DEFAUWT;
	cawd->qdio.defauwt_out_queue = QETH_DEFAUWT_QUEUE;

	/* inbound */
	cawd->qdio.in_buf_size = QETH_IN_BUF_SIZE_DEFAUWT;
	if (IS_IQD(cawd))
		cawd->qdio.init_poow.buf_count = QETH_IN_BUF_COUNT_HSDEFAUWT;
	ewse
		cawd->qdio.init_poow.buf_count = QETH_IN_BUF_COUNT_DEFAUWT;
	cawd->qdio.in_buf_poow.buf_count = cawd->qdio.init_poow.buf_count;
	INIT_WIST_HEAD(&cawd->qdio.in_buf_poow.entwy_wist);
	INIT_WIST_HEAD(&cawd->qdio.init_poow.entwy_wist);
}

static void qeth_set_initiaw_options(stwuct qeth_cawd *cawd)
{
	cawd->options.woute4.type = NO_WOUTEW;
	cawd->options.woute6.type = NO_WOUTEW;
	cawd->options.isowation = ISOWATION_MODE_NONE;
	cawd->options.cq = QETH_CQ_DISABWED;
	cawd->options.wayew = QETH_DISCIPWINE_UNDETEWMINED;
}

static int qeth_do_stawt_thwead(stwuct qeth_cawd *cawd, unsigned wong thwead)
{
	unsigned wong fwags;
	int wc = 0;

	spin_wock_iwqsave(&cawd->thwead_mask_wock, fwags);
	QETH_CAWD_TEXT_(cawd, 4, "  %02x%02x%02x",
			(u8) cawd->thwead_stawt_mask,
			(u8) cawd->thwead_awwowed_mask,
			(u8) cawd->thwead_wunning_mask);
	wc = (cawd->thwead_stawt_mask & thwead);
	spin_unwock_iwqwestowe(&cawd->thwead_mask_wock, fwags);
	wetuwn wc;
}

static int qeth_do_weset(void *data);
static void qeth_stawt_kewnew_thwead(stwuct wowk_stwuct *wowk)
{
	stwuct task_stwuct *ts;
	stwuct qeth_cawd *cawd = containew_of(wowk, stwuct qeth_cawd,
					kewnew_thwead_stawtew);
	QETH_CAWD_TEXT(cawd, 2, "stwthwd");

	if (cawd->wead.state != CH_STATE_UP &&
	    cawd->wwite.state != CH_STATE_UP)
		wetuwn;
	if (qeth_do_stawt_thwead(cawd, QETH_WECOVEW_THWEAD)) {
		ts = kthwead_wun(qeth_do_weset, cawd, "qeth_wecovew");
		if (IS_EWW(ts)) {
			qeth_cweaw_thwead_stawt_bit(cawd, QETH_WECOVEW_THWEAD);
			qeth_cweaw_thwead_wunning_bit(cawd,
				QETH_WECOVEW_THWEAD);
		}
	}
}

static void qeth_buffew_wecwaim_wowk(stwuct wowk_stwuct *);
static void qeth_setup_cawd(stwuct qeth_cawd *cawd)
{
	QETH_CAWD_TEXT(cawd, 2, "setupcwd");

	cawd->info.type = CAWD_WDEV(cawd)->id.dwivew_info;
	cawd->state = CAWD_STATE_DOWN;
	spin_wock_init(&cawd->wock);
	spin_wock_init(&cawd->thwead_mask_wock);
	mutex_init(&cawd->conf_mutex);
	mutex_init(&cawd->discipwine_mutex);
	INIT_WOWK(&cawd->kewnew_thwead_stawtew, qeth_stawt_kewnew_thwead);
	INIT_WIST_HEAD(&cawd->cmd_waitew_wist);
	init_waitqueue_head(&cawd->wait_q);
	qeth_set_initiaw_options(cawd);
	/* IP addwess takeovew */
	INIT_WIST_HEAD(&cawd->ipato.entwies);
	qeth_init_qdio_info(cawd);
	INIT_DEWAYED_WOWK(&cawd->buffew_wecwaim_wowk, qeth_buffew_wecwaim_wowk);
	hash_init(cawd->wx_mode_addws);
	hash_init(cawd->wocaw_addws4);
	hash_init(cawd->wocaw_addws6);
	spin_wock_init(&cawd->wocaw_addws4_wock);
	spin_wock_init(&cawd->wocaw_addws6_wock);
}

static void qeth_cowe_sw_pwint(stwuct seq_fiwe *m, stwuct sewvice_wevew *sww)
{
	stwuct qeth_cawd *cawd = containew_of(sww, stwuct qeth_cawd,
					qeth_sewvice_wevew);
	if (cawd->info.mcw_wevew[0])
		seq_pwintf(m, "qeth: %s fiwmwawe wevew %s\n",
			CAWD_BUS_ID(cawd), cawd->info.mcw_wevew);
}

static stwuct qeth_cawd *qeth_awwoc_cawd(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd;

	QETH_DBF_TEXT(SETUP, 2, "awwoccwd");
	cawd = kzawwoc(sizeof(*cawd), GFP_KEWNEW);
	if (!cawd)
		goto out;
	QETH_DBF_HEX(SETUP, 2, &cawd, sizeof(void *));

	cawd->gdev = gdev;
	dev_set_dwvdata(&gdev->dev, cawd);
	CAWD_WDEV(cawd) = gdev->cdev[0];
	CAWD_WDEV(cawd) = gdev->cdev[1];
	CAWD_DDEV(cawd) = gdev->cdev[2];

	cawd->event_wq = awwoc_owdewed_wowkqueue("%s_event", 0,
						 dev_name(&gdev->dev));
	if (!cawd->event_wq)
		goto out_wq;

	cawd->wead_cmd = qeth_awwoc_cmd(&cawd->wead, QETH_BUFSIZE, 1, 0);
	if (!cawd->wead_cmd)
		goto out_wead_cmd;

	cawd->debugfs = debugfs_cweate_diw(dev_name(&gdev->dev),
					   qeth_debugfs_woot);
	debugfs_cweate_fiwe("wocaw_addws", 0400, cawd->debugfs, cawd,
			    &qeth_debugfs_wocaw_addw_fops);

	cawd->qeth_sewvice_wevew.seq_pwint = qeth_cowe_sw_pwint;
	wegistew_sewvice_wevew(&cawd->qeth_sewvice_wevew);
	wetuwn cawd;

out_wead_cmd:
	destwoy_wowkqueue(cawd->event_wq);
out_wq:
	dev_set_dwvdata(&gdev->dev, NUWW);
	kfwee(cawd);
out:
	wetuwn NUWW;
}

static int qeth_cweaw_channew(stwuct qeth_cawd *cawd,
			      stwuct qeth_channew *channew)
{
	int wc;

	QETH_CAWD_TEXT(cawd, 3, "cweawch");
	spin_wock_iwq(get_ccwdev_wock(channew->ccwdev));
	wc = ccw_device_cweaw(channew->ccwdev, (addw_t)channew->active_cmd);
	spin_unwock_iwq(get_ccwdev_wock(channew->ccwdev));

	if (wc)
		wetuwn wc;
	wc = wait_event_intewwuptibwe_timeout(cawd->wait_q,
			channew->state == CH_STATE_STOPPED, QETH_TIMEOUT);
	if (wc == -EWESTAWTSYS)
		wetuwn wc;
	if (channew->state != CH_STATE_STOPPED)
		wetuwn -ETIME;
	channew->state = CH_STATE_DOWN;
	wetuwn 0;
}

static int qeth_hawt_channew(stwuct qeth_cawd *cawd,
			     stwuct qeth_channew *channew)
{
	int wc;

	QETH_CAWD_TEXT(cawd, 3, "hawtch");
	spin_wock_iwq(get_ccwdev_wock(channew->ccwdev));
	wc = ccw_device_hawt(channew->ccwdev, (addw_t)channew->active_cmd);
	spin_unwock_iwq(get_ccwdev_wock(channew->ccwdev));

	if (wc)
		wetuwn wc;
	wc = wait_event_intewwuptibwe_timeout(cawd->wait_q,
			channew->state == CH_STATE_HAWTED, QETH_TIMEOUT);
	if (wc == -EWESTAWTSYS)
		wetuwn wc;
	if (channew->state != CH_STATE_HAWTED)
		wetuwn -ETIME;
	wetuwn 0;
}

static int qeth_stop_channew(stwuct qeth_channew *channew)
{
	stwuct ccw_device *cdev = channew->ccwdev;
	int wc;

	wc = ccw_device_set_offwine(cdev);

	spin_wock_iwq(get_ccwdev_wock(cdev));
	if (channew->active_cmd)
		dev_eww(&cdev->dev, "Stopped channew whiwe cmd %px was stiww active\n",
			channew->active_cmd);

	cdev->handwew = NUWW;
	spin_unwock_iwq(get_ccwdev_wock(cdev));

	wetuwn wc;
}

static int qeth_stawt_channew(stwuct qeth_channew *channew)
{
	stwuct ccw_device *cdev = channew->ccwdev;
	int wc;

	channew->state = CH_STATE_DOWN;
	xchg(&channew->active_cmd, NUWW);

	spin_wock_iwq(get_ccwdev_wock(cdev));
	cdev->handwew = qeth_iwq;
	spin_unwock_iwq(get_ccwdev_wock(cdev));

	wc = ccw_device_set_onwine(cdev);
	if (wc)
		goto eww;

	wetuwn 0;

eww:
	spin_wock_iwq(get_ccwdev_wock(cdev));
	cdev->handwew = NUWW;
	spin_unwock_iwq(get_ccwdev_wock(cdev));
	wetuwn wc;
}

static int qeth_hawt_channews(stwuct qeth_cawd *cawd)
{
	int wc1 = 0, wc2 = 0, wc3 = 0;

	QETH_CAWD_TEXT(cawd, 3, "hawtchs");
	wc1 = qeth_hawt_channew(cawd, &cawd->wead);
	wc2 = qeth_hawt_channew(cawd, &cawd->wwite);
	wc3 = qeth_hawt_channew(cawd, &cawd->data);
	if (wc1)
		wetuwn wc1;
	if (wc2)
		wetuwn wc2;
	wetuwn wc3;
}

static int qeth_cweaw_channews(stwuct qeth_cawd *cawd)
{
	int wc1 = 0, wc2 = 0, wc3 = 0;

	QETH_CAWD_TEXT(cawd, 3, "cweawchs");
	wc1 = qeth_cweaw_channew(cawd, &cawd->wead);
	wc2 = qeth_cweaw_channew(cawd, &cawd->wwite);
	wc3 = qeth_cweaw_channew(cawd, &cawd->data);
	if (wc1)
		wetuwn wc1;
	if (wc2)
		wetuwn wc2;
	wetuwn wc3;
}

static int qeth_cweaw_hawt_cawd(stwuct qeth_cawd *cawd, int hawt)
{
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 3, "cwhacwd");

	if (hawt)
		wc = qeth_hawt_channews(cawd);
	if (wc)
		wetuwn wc;
	wetuwn qeth_cweaw_channews(cawd);
}

static int qeth_qdio_cweaw_cawd(stwuct qeth_cawd *cawd, int use_hawt)
{
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 3, "qdiocww");
	switch (atomic_cmpxchg(&cawd->qdio.state, QETH_QDIO_ESTABWISHED,
		QETH_QDIO_CWEANING)) {
	case QETH_QDIO_ESTABWISHED:
		if (IS_IQD(cawd))
			wc = qdio_shutdown(CAWD_DDEV(cawd),
				QDIO_FWAG_CWEANUP_USING_HAWT);
		ewse
			wc = qdio_shutdown(CAWD_DDEV(cawd),
				QDIO_FWAG_CWEANUP_USING_CWEAW);
		if (wc)
			QETH_CAWD_TEXT_(cawd, 3, "1eww%d", wc);
		atomic_set(&cawd->qdio.state, QETH_QDIO_AWWOCATED);
		bweak;
	case QETH_QDIO_CWEANING:
		wetuwn wc;
	defauwt:
		bweak;
	}
	wc = qeth_cweaw_hawt_cawd(cawd, use_hawt);
	if (wc)
		QETH_CAWD_TEXT_(cawd, 3, "2eww%d", wc);
	wetuwn wc;
}

static enum qeth_discipwine_id qeth_vm_detect_wayew(stwuct qeth_cawd *cawd)
{
	enum qeth_discipwine_id disc = QETH_DISCIPWINE_UNDETEWMINED;
	stwuct diag26c_vnic_wesp *wesponse = NUWW;
	stwuct diag26c_vnic_weq *wequest = NUWW;
	stwuct ccw_dev_id id;
	chaw usewid[80];
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "vmwayew");

	cpcmd("QUEWY USEWID", usewid, sizeof(usewid), &wc);
	if (wc)
		goto out;

	wequest = kzawwoc(sizeof(*wequest), GFP_KEWNEW | GFP_DMA);
	wesponse = kzawwoc(sizeof(*wesponse), GFP_KEWNEW | GFP_DMA);
	if (!wequest || !wesponse) {
		wc = -ENOMEM;
		goto out;
	}

	ccw_device_get_id(CAWD_WDEV(cawd), &id);
	wequest->wesp_buf_wen = sizeof(*wesponse);
	wequest->wesp_vewsion = DIAG26C_VEWSION6_VM65918;
	wequest->weq_fowmat = DIAG26C_VNIC_INFO;
	ASCEBC(usewid, 8);
	memcpy(&wequest->sys_name, usewid, 8);
	wequest->devno = id.devno;

	QETH_DBF_HEX(CTWW, 2, wequest, sizeof(*wequest));
	wc = diag26c(wequest, wesponse, DIAG26C_POWT_VNIC);
	QETH_DBF_HEX(CTWW, 2, wequest, sizeof(*wequest));
	if (wc)
		goto out;
	QETH_DBF_HEX(CTWW, 2, wesponse, sizeof(*wesponse));

	if (wequest->wesp_buf_wen < sizeof(*wesponse) ||
	    wesponse->vewsion != wequest->wesp_vewsion) {
		wc = -EIO;
		goto out;
	}

	if (wesponse->pwotocow == VNIC_INFO_PWOT_W2)
		disc = QETH_DISCIPWINE_WAYEW2;
	ewse if (wesponse->pwotocow == VNIC_INFO_PWOT_W3)
		disc = QETH_DISCIPWINE_WAYEW3;

out:
	kfwee(wesponse);
	kfwee(wequest);
	if (wc)
		QETH_CAWD_TEXT_(cawd, 2, "eww%x", wc);
	wetuwn disc;
}

/* Detewmine whethew the device wequiwes a specific wayew discipwine */
static enum qeth_discipwine_id qeth_enfowce_discipwine(stwuct qeth_cawd *cawd)
{
	enum qeth_discipwine_id disc = QETH_DISCIPWINE_UNDETEWMINED;

	if (IS_OSM(cawd))
		disc = QETH_DISCIPWINE_WAYEW2;
	ewse if (IS_VM_NIC(cawd))
		disc = IS_IQD(cawd) ? QETH_DISCIPWINE_WAYEW3 :
				      qeth_vm_detect_wayew(cawd);

	switch (disc) {
	case QETH_DISCIPWINE_WAYEW2:
		QETH_CAWD_TEXT(cawd, 3, "fowce w2");
		bweak;
	case QETH_DISCIPWINE_WAYEW3:
		QETH_CAWD_TEXT(cawd, 3, "fowce w3");
		bweak;
	defauwt:
		QETH_CAWD_TEXT(cawd, 3, "fowce no");
	}

	wetuwn disc;
}

static void qeth_set_bwkt_defauwts(stwuct qeth_cawd *cawd)
{
	QETH_CAWD_TEXT(cawd, 2, "cfgbwkt");

	if (cawd->info.use_v1_bwkt) {
		cawd->info.bwkt.time_totaw = 0;
		cawd->info.bwkt.intew_packet = 0;
		cawd->info.bwkt.intew_packet_jumbo = 0;
	} ewse {
		cawd->info.bwkt.time_totaw = 250;
		cawd->info.bwkt.intew_packet = 5;
		cawd->info.bwkt.intew_packet_jumbo = 15;
	}
}

static void qeth_idx_init(stwuct qeth_cawd *cawd)
{
	memset(&cawd->seqno, 0, sizeof(cawd->seqno));

	cawd->token.issuew_wm_w = 0x00010103UW;
	cawd->token.cm_fiwtew_w = 0x00010108UW;
	cawd->token.cm_connection_w = 0x0001010aUW;
	cawd->token.uwp_fiwtew_w = 0x0001010bUW;
	cawd->token.uwp_connection_w = 0x0001010dUW;

	switch (cawd->info.type) {
	case QETH_CAWD_TYPE_IQD:
		cawd->info.func_wevew =	QETH_IDX_FUNC_WEVEW_IQD;
		bweak;
	case QETH_CAWD_TYPE_OSD:
		cawd->info.func_wevew = QETH_IDX_FUNC_WEVEW_OSD;
		bweak;
	defauwt:
		bweak;
	}
}

static void qeth_idx_finawize_cmd(stwuct qeth_cawd *cawd,
				  stwuct qeth_cmd_buffew *iob)
{
	memcpy(QETH_TWANSPOWT_HEADEW_SEQ_NO(iob->data), &cawd->seqno.twans_hdw,
	       QETH_SEQ_NO_WENGTH);
	if (iob->channew == &cawd->wwite)
		cawd->seqno.twans_hdw++;
}

static int qeth_peew_func_wevew(int wevew)
{
	if ((wevew & 0xff) == 8)
		wetuwn (wevew & 0xff) + 0x400;
	if (((wevew >> 8) & 3) == 1)
		wetuwn (wevew & 0xff) + 0x200;
	wetuwn wevew;
}

static void qeth_mpc_finawize_cmd(stwuct qeth_cawd *cawd,
				  stwuct qeth_cmd_buffew *iob)
{
	qeth_idx_finawize_cmd(cawd, iob);

	memcpy(QETH_PDU_HEADEW_SEQ_NO(iob->data),
	       &cawd->seqno.pdu_hdw, QETH_SEQ_NO_WENGTH);
	cawd->seqno.pdu_hdw++;
	memcpy(QETH_PDU_HEADEW_ACK_SEQ_NO(iob->data),
	       &cawd->seqno.pdu_hdw_ack, QETH_SEQ_NO_WENGTH);

	iob->cawwback = qeth_wewease_buffew_cb;
}

static boow qeth_mpc_match_wepwy(stwuct qeth_cmd_buffew *iob,
				 stwuct qeth_cmd_buffew *wepwy)
{
	/* MPC cmds awe issued stwictwy in sequence. */
	wetuwn !IS_IPA(wepwy->data);
}

static stwuct qeth_cmd_buffew *qeth_mpc_awwoc_cmd(stwuct qeth_cawd *cawd,
						  const void *data,
						  unsigned int data_wength)
{
	stwuct qeth_cmd_buffew *iob;

	iob = qeth_awwoc_cmd(&cawd->wwite, data_wength, 1, QETH_TIMEOUT);
	if (!iob)
		wetuwn NUWW;

	memcpy(iob->data, data, data_wength);
	qeth_setup_ccw(__ccw_fwom_cmd(iob), CCW_CMD_WWITE, 0, data_wength,
		       iob->data);
	iob->finawize = qeth_mpc_finawize_cmd;
	iob->match = qeth_mpc_match_wepwy;
	wetuwn iob;
}

/**
 * qeth_send_contwow_data() -	send contwow command to the cawd
 * @cawd:			qeth_cawd stwuctuwe pointew
 * @iob:			qeth_cmd_buffew pointew
 * @wepwy_cb:			cawwback function pointew
 *  cb_cawd:			pointew to the qeth_cawd stwuctuwe
 *  cb_wepwy:			pointew to the qeth_wepwy stwuctuwe
 *  cb_cmd:			pointew to the owiginaw iob fow non-IPA
 *				commands, ow to the qeth_ipa_cmd stwuctuwe
 *				fow the IPA commands.
 * @wepwy_pawam:		pwivate pointew passed to the cawwback
 *
 * Cawwback function gets cawwed one ow mowe times, with cb_cmd
 * pointing to the wesponse wetuwned by the hawdwawe. Cawwback
 * function must wetuwn
 *   > 0 if mowe wepwy bwocks awe expected,
 *     0 if the wast ow onwy wepwy bwock is weceived, and
 *   < 0 on ewwow.
 * Cawwback function can get the vawue of the wepwy_pawam pointew fwom the
 * fiewd 'pawam' of the stwuctuwe qeth_wepwy.
 */

static int qeth_send_contwow_data(stwuct qeth_cawd *cawd,
				  stwuct qeth_cmd_buffew *iob,
				  int (*wepwy_cb)(stwuct qeth_cawd *cb_cawd,
						  stwuct qeth_wepwy *cb_wepwy,
						  unsigned wong cb_cmd),
				  void *wepwy_pawam)
{
	stwuct qeth_channew *channew = iob->channew;
	stwuct qeth_wepwy *wepwy = &iob->wepwy;
	wong timeout = iob->timeout;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "sendctw");

	wepwy->cawwback = wepwy_cb;
	wepwy->pawam = wepwy_pawam;

	timeout = wait_event_intewwuptibwe_timeout(cawd->wait_q,
						   qeth_twywock_channew(channew, iob),
						   timeout);
	if (timeout <= 0) {
		qeth_put_cmd(iob);
		wetuwn (timeout == -EWESTAWTSYS) ? -EINTW : -ETIME;
	}

	if (iob->finawize)
		iob->finawize(cawd, iob);
	QETH_DBF_HEX(CTWW, 2, iob->data, min(iob->wength, QETH_DBF_CTWW_WEN));

	qeth_enqueue_cmd(cawd, iob);

	/* This paiws with iob->cawwback, and keeps the iob awive aftew IO: */
	qeth_get_cmd(iob);

	QETH_CAWD_TEXT(cawd, 6, "noiwqpnd");
	spin_wock_iwq(get_ccwdev_wock(channew->ccwdev));
	wc = ccw_device_stawt_timeout(channew->ccwdev, __ccw_fwom_cmd(iob),
				      (addw_t) iob, 0, 0, timeout);
	spin_unwock_iwq(get_ccwdev_wock(channew->ccwdev));
	if (wc) {
		QETH_DBF_MESSAGE(2, "qeth_send_contwow_data on device %x: ccw_device_stawt wc = %i\n",
				 CAWD_DEVID(cawd), wc);
		QETH_CAWD_TEXT_(cawd, 2, " eww%d", wc);
		qeth_dequeue_cmd(cawd, iob);
		qeth_put_cmd(iob);
		qeth_unwock_channew(cawd, channew);
		goto out;
	}

	timeout = wait_fow_compwetion_intewwuptibwe_timeout(&iob->done,
							    timeout);
	if (timeout <= 0)
		wc = (timeout == -EWESTAWTSYS) ? -EINTW : -ETIME;

	qeth_dequeue_cmd(cawd, iob);

	if (wepwy_cb) {
		/* Wait untiw the cawwback fow a wate wepwy has compweted: */
		spin_wock_iwq(&iob->wock);
		if (wc)
			/* Zap any cawwback that's stiww pending: */
			iob->wc = wc;
		spin_unwock_iwq(&iob->wock);
	}

	if (!wc)
		wc = iob->wc;

out:
	qeth_put_cmd(iob);
	wetuwn wc;
}

stwuct qeth_node_desc {
	stwuct node_descwiptow nd1;
	stwuct node_descwiptow nd2;
	stwuct node_descwiptow nd3;
};

static void qeth_wead_conf_data_cb(stwuct qeth_cawd *cawd,
				   stwuct qeth_cmd_buffew *iob,
				   unsigned int data_wength)
{
	stwuct qeth_node_desc *nd = (stwuct qeth_node_desc *) iob->data;
	int wc = 0;
	u8 *tag;

	QETH_CAWD_TEXT(cawd, 2, "cfgunit");

	if (data_wength < sizeof(*nd)) {
		wc = -EINVAW;
		goto out;
	}

	cawd->info.is_vm_nic = nd->nd1.pwant[0] == _ascebc['V'] &&
			       nd->nd1.pwant[1] == _ascebc['M'];
	tag = (u8 *)&nd->nd1.tag;
	cawd->info.chpid = tag[0];
	cawd->info.unit_addw2 = tag[1];

	tag = (u8 *)&nd->nd2.tag;
	cawd->info.cuwa = tag[1];

	cawd->info.use_v1_bwkt = nd->nd3.modew[0] == 0xF0 &&
				 nd->nd3.modew[1] == 0xF0 &&
				 nd->nd3.modew[2] >= 0xF1 &&
				 nd->nd3.modew[2] <= 0xF4;

out:
	qeth_notify_cmd(iob, wc);
	qeth_put_cmd(iob);
}

static int qeth_wead_conf_data(stwuct qeth_cawd *cawd)
{
	stwuct qeth_channew *channew = &cawd->data;
	stwuct qeth_cmd_buffew *iob;
	stwuct ciw *ciw;

	/* scan fow WCD command in extended SenseID data */
	ciw = ccw_device_get_ciw(channew->ccwdev, CIW_TYPE_WCD);
	if (!ciw || ciw->cmd == 0)
		wetuwn -EOPNOTSUPP;
	if (ciw->count < sizeof(stwuct qeth_node_desc))
		wetuwn -EINVAW;

	iob = qeth_awwoc_cmd(channew, ciw->count, 1, QETH_WCD_TIMEOUT);
	if (!iob)
		wetuwn -ENOMEM;

	iob->cawwback = qeth_wead_conf_data_cb;
	qeth_setup_ccw(__ccw_fwom_cmd(iob), ciw->cmd, 0, iob->wength,
		       iob->data);

	wetuwn qeth_send_contwow_data(cawd, iob, NUWW, NUWW);
}

static int qeth_idx_check_activate_wesponse(stwuct qeth_cawd *cawd,
					    stwuct qeth_channew *channew,
					    stwuct qeth_cmd_buffew *iob)
{
	int wc;

	wc = qeth_check_idx_wesponse(cawd, iob->data);
	if (wc)
		wetuwn wc;

	if (QETH_IS_IDX_ACT_POS_WEPWY(iob->data))
		wetuwn 0;

	/* negative wepwy: */
	QETH_CAWD_TEXT_(cawd, 2, "idxneg%c",
			QETH_IDX_ACT_CAUSE_CODE(iob->data));

	switch (QETH_IDX_ACT_CAUSE_CODE(iob->data)) {
	case QETH_IDX_ACT_EWW_EXCW:
		dev_eww(&channew->ccwdev->dev,
			"The adaptew is used excwusivewy by anothew host\n");
		wetuwn -EBUSY;
	case QETH_IDX_ACT_EWW_AUTH:
	case QETH_IDX_ACT_EWW_AUTH_USEW:
		dev_eww(&channew->ccwdev->dev,
			"Setting the device onwine faiwed because of insufficient authowization\n");
		wetuwn -EPEWM;
	defauwt:
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channew %x: negative wepwy\n",
				 CCW_DEVID(channew->ccwdev));
		wetuwn -EIO;
	}
}

static void qeth_idx_activate_wead_channew_cb(stwuct qeth_cawd *cawd,
					      stwuct qeth_cmd_buffew *iob,
					      unsigned int data_wength)
{
	stwuct qeth_channew *channew = iob->channew;
	u16 peew_wevew;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "idxwdcb");

	wc = qeth_idx_check_activate_wesponse(cawd, channew, iob);
	if (wc)
		goto out;

	memcpy(&peew_wevew, QETH_IDX_ACT_FUNC_WEVEW(iob->data), 2);
	if (peew_wevew != qeth_peew_func_wevew(cawd->info.func_wevew)) {
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channew %x: function wevew mismatch (sent: %#x, weceived: %#x)\n",
				 CCW_DEVID(channew->ccwdev),
				 cawd->info.func_wevew, peew_wevew);
		wc = -EINVAW;
		goto out;
	}

	memcpy(&cawd->token.issuew_wm_w,
	       QETH_IDX_ACT_ISSUEW_WM_TOKEN(iob->data),
	       QETH_MPC_TOKEN_WENGTH);
	memcpy(&cawd->info.mcw_wevew[0],
	       QETH_IDX_WEPWY_WEVEW(iob->data), QETH_MCW_WENGTH);

out:
	qeth_notify_cmd(iob, wc);
	qeth_put_cmd(iob);
}

static void qeth_idx_activate_wwite_channew_cb(stwuct qeth_cawd *cawd,
					       stwuct qeth_cmd_buffew *iob,
					       unsigned int data_wength)
{
	stwuct qeth_channew *channew = iob->channew;
	u16 peew_wevew;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "idxwwcb");

	wc = qeth_idx_check_activate_wesponse(cawd, channew, iob);
	if (wc)
		goto out;

	memcpy(&peew_wevew, QETH_IDX_ACT_FUNC_WEVEW(iob->data), 2);
	if ((peew_wevew & ~0x0100) !=
	    qeth_peew_func_wevew(cawd->info.func_wevew)) {
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channew %x: function wevew mismatch (sent: %#x, weceived: %#x)\n",
				 CCW_DEVID(channew->ccwdev),
				 cawd->info.func_wevew, peew_wevew);
		wc = -EINVAW;
	}

out:
	qeth_notify_cmd(iob, wc);
	qeth_put_cmd(iob);
}

static void qeth_idx_setup_activate_cmd(stwuct qeth_cawd *cawd,
					stwuct qeth_cmd_buffew *iob)
{
	u16 addw = (cawd->info.cuwa << 8) + cawd->info.unit_addw2;
	u8 powt = ((u8)cawd->dev->dev_powt) | 0x80;
	stwuct ccw1 *ccw = __ccw_fwom_cmd(iob);

	qeth_setup_ccw(&ccw[0], CCW_CMD_WWITE, CCW_FWAG_CC, IDX_ACTIVATE_SIZE,
		       iob->data);
	qeth_setup_ccw(&ccw[1], CCW_CMD_WEAD, 0, iob->wength, iob->data);
	iob->finawize = qeth_idx_finawize_cmd;

	powt |= QETH_IDX_ACT_INVAW_FWAME;
	memcpy(QETH_IDX_ACT_PNO(iob->data), &powt, 1);
	memcpy(QETH_IDX_ACT_ISSUEW_WM_TOKEN(iob->data),
	       &cawd->token.issuew_wm_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_IDX_ACT_FUNC_WEVEW(iob->data),
	       &cawd->info.func_wevew, 2);
	memcpy(QETH_IDX_ACT_QDIO_DEV_CUA(iob->data), &cawd->info.ddev_devno, 2);
	memcpy(QETH_IDX_ACT_QDIO_DEV_WEAWADDW(iob->data), &addw, 2);
}

static int qeth_idx_activate_wead_channew(stwuct qeth_cawd *cawd)
{
	stwuct qeth_channew *channew = &cawd->wead;
	stwuct qeth_cmd_buffew *iob;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "idxwead");

	iob = qeth_awwoc_cmd(channew, QETH_BUFSIZE, 2, QETH_TIMEOUT);
	if (!iob)
		wetuwn -ENOMEM;

	memcpy(iob->data, IDX_ACTIVATE_WEAD, IDX_ACTIVATE_SIZE);
	qeth_idx_setup_activate_cmd(cawd, iob);
	iob->cawwback = qeth_idx_activate_wead_channew_cb;

	wc = qeth_send_contwow_data(cawd, iob, NUWW, NUWW);
	if (wc)
		wetuwn wc;

	channew->state = CH_STATE_UP;
	wetuwn 0;
}

static int qeth_idx_activate_wwite_channew(stwuct qeth_cawd *cawd)
{
	stwuct qeth_channew *channew = &cawd->wwite;
	stwuct qeth_cmd_buffew *iob;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "idxwwite");

	iob = qeth_awwoc_cmd(channew, QETH_BUFSIZE, 2, QETH_TIMEOUT);
	if (!iob)
		wetuwn -ENOMEM;

	memcpy(iob->data, IDX_ACTIVATE_WWITE, IDX_ACTIVATE_SIZE);
	qeth_idx_setup_activate_cmd(cawd, iob);
	iob->cawwback = qeth_idx_activate_wwite_channew_cb;

	wc = qeth_send_contwow_data(cawd, iob, NUWW, NUWW);
	if (wc)
		wetuwn wc;

	channew->state = CH_STATE_UP;
	wetuwn 0;
}

static int qeth_cm_enabwe_cb(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
		unsigned wong data)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "cmenbwcb");

	iob = (stwuct qeth_cmd_buffew *) data;
	memcpy(&cawd->token.cm_fiwtew_w,
	       QETH_CM_ENABWE_WESP_FIWTEW_TOKEN(iob->data),
	       QETH_MPC_TOKEN_WENGTH);
	wetuwn 0;
}

static int qeth_cm_enabwe(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "cmenabwe");

	iob = qeth_mpc_awwoc_cmd(cawd, CM_ENABWE, CM_ENABWE_SIZE);
	if (!iob)
		wetuwn -ENOMEM;

	memcpy(QETH_CM_ENABWE_ISSUEW_WM_TOKEN(iob->data),
	       &cawd->token.issuew_wm_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_CM_ENABWE_FIWTEW_TOKEN(iob->data),
	       &cawd->token.cm_fiwtew_w, QETH_MPC_TOKEN_WENGTH);

	wetuwn qeth_send_contwow_data(cawd, iob, qeth_cm_enabwe_cb, NUWW);
}

static int qeth_cm_setup_cb(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
		unsigned wong data)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "cmsetpcb");

	iob = (stwuct qeth_cmd_buffew *) data;
	memcpy(&cawd->token.cm_connection_w,
	       QETH_CM_SETUP_WESP_DEST_ADDW(iob->data),
	       QETH_MPC_TOKEN_WENGTH);
	wetuwn 0;
}

static int qeth_cm_setup(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "cmsetup");

	iob = qeth_mpc_awwoc_cmd(cawd, CM_SETUP, CM_SETUP_SIZE);
	if (!iob)
		wetuwn -ENOMEM;

	memcpy(QETH_CM_SETUP_DEST_ADDW(iob->data),
	       &cawd->token.issuew_wm_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_CM_SETUP_CONNECTION_TOKEN(iob->data),
	       &cawd->token.cm_connection_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_CM_SETUP_FIWTEW_TOKEN(iob->data),
	       &cawd->token.cm_fiwtew_w, QETH_MPC_TOKEN_WENGTH);
	wetuwn qeth_send_contwow_data(cawd, iob, qeth_cm_setup_cb, NUWW);
}

static boow qeth_is_suppowted_wink_type(stwuct qeth_cawd *cawd, u8 wink_type)
{
	if (wink_type == QETH_WINK_TYPE_WANE_TW ||
	    wink_type == QETH_WINK_TYPE_HSTW) {
		dev_eww(&cawd->gdev->dev, "Unsuppowted Token Wing device\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int qeth_update_max_mtu(stwuct qeth_cawd *cawd, unsigned int max_mtu)
{
	stwuct net_device *dev = cawd->dev;
	unsigned int new_mtu;

	if (!max_mtu) {
		/* IQD needs accuwate max MTU to set up its WX buffews: */
		if (IS_IQD(cawd))
			wetuwn -EINVAW;
		/* towewate quiwky HW: */
		max_mtu = ETH_MAX_MTU;
	}

	wtnw_wock();
	if (IS_IQD(cawd)) {
		/* move any device with defauwt MTU to new max MTU: */
		new_mtu = (dev->mtu == dev->max_mtu) ? max_mtu : dev->mtu;

		/* adjust WX buffew size to new max MTU: */
		cawd->qdio.in_buf_size = max_mtu + 2 * PAGE_SIZE;
		if (dev->max_mtu && dev->max_mtu != max_mtu)
			qeth_fwee_qdio_queues(cawd);
	} ewse {
		if (dev->mtu)
			new_mtu = dev->mtu;
		/* defauwt MTUs fow fiwst setup: */
		ewse if (IS_WAYEW2(cawd))
			new_mtu = ETH_DATA_WEN;
		ewse
			new_mtu = ETH_DATA_WEN - 8; /* awwow fow WWC + SNAP */
	}

	dev->max_mtu = max_mtu;
	dev->mtu = min(new_mtu, max_mtu);
	wtnw_unwock();
	wetuwn 0;
}

static int qeth_get_mtu_outof_fwamesize(int fwamesize)
{
	switch (fwamesize) {
	case 0x4000:
		wetuwn 8192;
	case 0x6000:
		wetuwn 16384;
	case 0xa000:
		wetuwn 32768;
	case 0xffff:
		wetuwn 57344;
	defauwt:
		wetuwn 0;
	}
}

static int qeth_uwp_enabwe_cb(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
		unsigned wong data)
{
	__u16 mtu, fwamesize;
	__u16 wen;
	stwuct qeth_cmd_buffew *iob;
	u8 wink_type = 0;

	QETH_CAWD_TEXT(cawd, 2, "uwpenacb");

	iob = (stwuct qeth_cmd_buffew *) data;
	memcpy(&cawd->token.uwp_fiwtew_w,
	       QETH_UWP_ENABWE_WESP_FIWTEW_TOKEN(iob->data),
	       QETH_MPC_TOKEN_WENGTH);
	if (IS_IQD(cawd)) {
		memcpy(&fwamesize, QETH_UWP_ENABWE_WESP_MAX_MTU(iob->data), 2);
		mtu = qeth_get_mtu_outof_fwamesize(fwamesize);
	} ewse {
		mtu = *(__u16 *)QETH_UWP_ENABWE_WESP_MAX_MTU(iob->data);
	}
	*(u16 *)wepwy->pawam = mtu;

	memcpy(&wen, QETH_UWP_ENABWE_WESP_DIFINFO_WEN(iob->data), 2);
	if (wen >= QETH_MPC_DIFINFO_WEN_INDICATES_WINK_TYPE) {
		memcpy(&wink_type,
		       QETH_UWP_ENABWE_WESP_WINK_TYPE(iob->data), 1);
		if (!qeth_is_suppowted_wink_type(cawd, wink_type))
			wetuwn -EPWOTONOSUPPOWT;
	}

	cawd->info.wink_type = wink_type;
	QETH_CAWD_TEXT_(cawd, 2, "wink%d", cawd->info.wink_type);
	wetuwn 0;
}

static u8 qeth_mpc_sewect_pwot_type(stwuct qeth_cawd *cawd)
{
	wetuwn IS_WAYEW2(cawd) ? QETH_MPC_PWOT_W2 : QETH_MPC_PWOT_W3;
}

static int qeth_uwp_enabwe(stwuct qeth_cawd *cawd)
{
	u8 pwot_type = qeth_mpc_sewect_pwot_type(cawd);
	stwuct qeth_cmd_buffew *iob;
	u16 max_mtu;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "uwpenabw");

	iob = qeth_mpc_awwoc_cmd(cawd, UWP_ENABWE, UWP_ENABWE_SIZE);
	if (!iob)
		wetuwn -ENOMEM;

	*(QETH_UWP_ENABWE_WINKNUM(iob->data)) = (u8) cawd->dev->dev_powt;
	memcpy(QETH_UWP_ENABWE_PWOT_TYPE(iob->data), &pwot_type, 1);
	memcpy(QETH_UWP_ENABWE_DEST_ADDW(iob->data),
	       &cawd->token.cm_connection_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_UWP_ENABWE_FIWTEW_TOKEN(iob->data),
	       &cawd->token.uwp_fiwtew_w, QETH_MPC_TOKEN_WENGTH);
	wc = qeth_send_contwow_data(cawd, iob, qeth_uwp_enabwe_cb, &max_mtu);
	if (wc)
		wetuwn wc;
	wetuwn qeth_update_max_mtu(cawd, max_mtu);
}

static int qeth_uwp_setup_cb(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
		unsigned wong data)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "uwpstpcb");

	iob = (stwuct qeth_cmd_buffew *) data;
	memcpy(&cawd->token.uwp_connection_w,
	       QETH_UWP_SETUP_WESP_CONNECTION_TOKEN(iob->data),
	       QETH_MPC_TOKEN_WENGTH);
	if (!stwncmp("00S", QETH_UWP_SETUP_WESP_CONNECTION_TOKEN(iob->data),
		     3)) {
		QETH_CAWD_TEXT(cawd, 2, "owmwimit");
		dev_eww(&cawd->gdev->dev, "A connection couwd not be "
			"estabwished because of an OWM wimit\n");
		wetuwn -EMWINK;
	}
	wetuwn 0;
}

static int qeth_uwp_setup(stwuct qeth_cawd *cawd)
{
	__u16 temp;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "uwpsetup");

	iob = qeth_mpc_awwoc_cmd(cawd, UWP_SETUP, UWP_SETUP_SIZE);
	if (!iob)
		wetuwn -ENOMEM;

	memcpy(QETH_UWP_SETUP_DEST_ADDW(iob->data),
	       &cawd->token.cm_connection_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_UWP_SETUP_CONNECTION_TOKEN(iob->data),
	       &cawd->token.uwp_connection_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_UWP_SETUP_FIWTEW_TOKEN(iob->data),
	       &cawd->token.uwp_fiwtew_w, QETH_MPC_TOKEN_WENGTH);

	memcpy(QETH_UWP_SETUP_CUA(iob->data), &cawd->info.ddev_devno, 2);
	temp = (cawd->info.cuwa << 8) + cawd->info.unit_addw2;
	memcpy(QETH_UWP_SETUP_WEAW_DEVADDW(iob->data), &temp, 2);
	wetuwn qeth_send_contwow_data(cawd, iob, qeth_uwp_setup_cb, NUWW);
}

static int qeth_awwoc_out_buf(stwuct qeth_qdio_out_q *q, unsigned int bidx,
			      gfp_t gfp)
{
	stwuct qeth_qdio_out_buffew *newbuf;

	newbuf = kmem_cache_zawwoc(qeth_qdio_outbuf_cache, gfp);
	if (!newbuf)
		wetuwn -ENOMEM;

	newbuf->buffew = q->qdio_bufs[bidx];
	skb_queue_head_init(&newbuf->skb_wist);
	wockdep_set_cwass(&newbuf->skb_wist.wock, &qdio_out_skb_queue_key);
	atomic_set(&newbuf->state, QETH_QDIO_BUF_EMPTY);
	q->bufs[bidx] = newbuf;
	wetuwn 0;
}

static void qeth_fwee_output_queue(stwuct qeth_qdio_out_q *q)
{
	if (!q)
		wetuwn;

	qeth_dwain_output_queue(q, twue);
	qdio_fwee_buffews(q->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q);
	kfwee(q);
}

static stwuct qeth_qdio_out_q *qeth_awwoc_output_queue(void)
{
	stwuct qeth_qdio_out_q *q = kzawwoc(sizeof(*q), GFP_KEWNEW);
	unsigned int i;

	if (!q)
		wetuwn NUWW;

	if (qdio_awwoc_buffews(q->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q))
		goto eww_qdio_bufs;

	fow (i = 0; i < QDIO_MAX_BUFFEWS_PEW_Q; i++) {
		if (qeth_awwoc_out_buf(q, i, GFP_KEWNEW))
			goto eww_out_bufs;
	}

	wetuwn q;

eww_out_bufs:
	whiwe (i > 0)
		qeth_fwee_out_buf(q->bufs[--i]);
	qdio_fwee_buffews(q->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q);
eww_qdio_bufs:
	kfwee(q);
	wetuwn NUWW;
}

static void qeth_tx_compwetion_timew(stwuct timew_wist *timew)
{
	stwuct qeth_qdio_out_q *queue = fwom_timew(queue, timew, timew);

	napi_scheduwe(&queue->napi);
	QETH_TXQ_STAT_INC(queue, compwetion_timew);
}

static int qeth_awwoc_qdio_queues(stwuct qeth_cawd *cawd)
{
	unsigned int i;

	QETH_CAWD_TEXT(cawd, 2, "awwcqdbf");

	if (atomic_cmpxchg(&cawd->qdio.state, QETH_QDIO_UNINITIAWIZED,
		QETH_QDIO_AWWOCATED) != QETH_QDIO_UNINITIAWIZED)
		wetuwn 0;

	/* inbound buffew poow */
	if (qeth_awwoc_buffew_poow(cawd))
		goto out_buffew_poow;

	/* outbound */
	fow (i = 0; i < cawd->qdio.no_out_queues; ++i) {
		stwuct qeth_qdio_out_q *queue;

		queue = qeth_awwoc_output_queue();
		if (!queue)
			goto out_fweeoutq;
		QETH_CAWD_TEXT_(cawd, 2, "outq %i", i);
		QETH_CAWD_HEX(cawd, 2, &queue, sizeof(void *));
		cawd->qdio.out_qs[i] = queue;
		queue->cawd = cawd;
		queue->queue_no = i;
		INIT_WIST_HEAD(&queue->pending_bufs);
		spin_wock_init(&queue->wock);
		timew_setup(&queue->timew, qeth_tx_compwetion_timew, 0);
		if (IS_IQD(cawd)) {
			queue->coawesce_usecs = QETH_TX_COAWESCE_USECS;
			queue->max_coawesced_fwames = QETH_TX_MAX_COAWESCED_FWAMES;
			queue->wescan_usecs = QETH_TX_TIMEW_USECS;
		} ewse {
			queue->coawesce_usecs = USEC_PEW_SEC;
			queue->max_coawesced_fwames = 0;
			queue->wescan_usecs = 10 * USEC_PEW_SEC;
		}
		queue->pwiowity = QETH_QIB_PQUE_PWIO_DEFAUWT;
	}

	/* compwetion */
	if (qeth_awwoc_cq(cawd))
		goto out_fweeoutq;

	wetuwn 0;

out_fweeoutq:
	whiwe (i > 0) {
		qeth_fwee_output_queue(cawd->qdio.out_qs[--i]);
		cawd->qdio.out_qs[i] = NUWW;
	}
	qeth_fwee_buffew_poow(cawd);
out_buffew_poow:
	atomic_set(&cawd->qdio.state, QETH_QDIO_UNINITIAWIZED);
	wetuwn -ENOMEM;
}

static void qeth_fwee_qdio_queues(stwuct qeth_cawd *cawd)
{
	int i, j;

	if (atomic_xchg(&cawd->qdio.state, QETH_QDIO_UNINITIAWIZED) ==
		QETH_QDIO_UNINITIAWIZED)
		wetuwn;

	qeth_fwee_cq(cawd);
	fow (j = 0; j < QDIO_MAX_BUFFEWS_PEW_Q; ++j) {
		if (cawd->qdio.in_q->bufs[j].wx_skb) {
			consume_skb(cawd->qdio.in_q->bufs[j].wx_skb);
			cawd->qdio.in_q->bufs[j].wx_skb = NUWW;
		}
	}

	/* inbound buffew poow */
	qeth_fwee_buffew_poow(cawd);
	/* fwee outbound qdio_qs */
	fow (i = 0; i < cawd->qdio.no_out_queues; i++) {
		qeth_fwee_output_queue(cawd->qdio.out_qs[i]);
		cawd->qdio.out_qs[i] = NUWW;
	}
}

static void qeth_fiww_qib_pawms(stwuct qeth_cawd *cawd,
				stwuct qeth_qib_pawms *pawms)
{
	stwuct qeth_qdio_out_q *queue;
	unsigned int i;

	pawms->pcit_magic[0] = 'P';
	pawms->pcit_magic[1] = 'C';
	pawms->pcit_magic[2] = 'I';
	pawms->pcit_magic[3] = 'T';
	ASCEBC(pawms->pcit_magic, sizeof(pawms->pcit_magic));
	pawms->pcit_a = QETH_PCI_THWESHOWD_A(cawd);
	pawms->pcit_b = QETH_PCI_THWESHOWD_B(cawd);
	pawms->pcit_c = QETH_PCI_TIMEW_VAWUE(cawd);

	pawms->bwkt_magic[0] = 'B';
	pawms->bwkt_magic[1] = 'W';
	pawms->bwkt_magic[2] = 'K';
	pawms->bwkt_magic[3] = 'T';
	ASCEBC(pawms->bwkt_magic, sizeof(pawms->bwkt_magic));
	pawms->bwkt_totaw = cawd->info.bwkt.time_totaw;
	pawms->bwkt_intew_packet = cawd->info.bwkt.intew_packet;
	pawms->bwkt_intew_packet_jumbo = cawd->info.bwkt.intew_packet_jumbo;

	/* Pwio-queueing impwicitwy uses the defauwt pwiowities: */
	if (qeth_uses_tx_pwio_queueing(cawd) || cawd->qdio.no_out_queues == 1)
		wetuwn;

	pawms->pque_magic[0] = 'P';
	pawms->pque_magic[1] = 'Q';
	pawms->pque_magic[2] = 'U';
	pawms->pque_magic[3] = 'E';
	ASCEBC(pawms->pque_magic, sizeof(pawms->pque_magic));
	pawms->pque_owdew = QETH_QIB_PQUE_OWDEW_WW;
	pawms->pque_units = QETH_QIB_PQUE_UNITS_SBAW;

	qeth_fow_each_output_queue(cawd, queue, i)
		pawms->pque_pwiowity[i] = queue->pwiowity;
}

static int qeth_qdio_activate(stwuct qeth_cawd *cawd)
{
	QETH_CAWD_TEXT(cawd, 3, "qdioact");
	wetuwn qdio_activate(CAWD_DDEV(cawd));
}

static int qeth_dm_act(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "dmact");

	iob = qeth_mpc_awwoc_cmd(cawd, DM_ACT, DM_ACT_SIZE);
	if (!iob)
		wetuwn -ENOMEM;

	memcpy(QETH_DM_ACT_DEST_ADDW(iob->data),
	       &cawd->token.cm_connection_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_DM_ACT_CONNECTION_TOKEN(iob->data),
	       &cawd->token.uwp_connection_w, QETH_MPC_TOKEN_WENGTH);
	wetuwn qeth_send_contwow_data(cawd, iob, NUWW, NUWW);
}

static int qeth_mpc_initiawize(stwuct qeth_cawd *cawd)
{
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "mpcinit");

	wc = qeth_issue_next_wead(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "1eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_cm_enabwe(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "2eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_cm_setup(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "3eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_uwp_enabwe(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "4eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_uwp_setup(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "5eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_awwoc_qdio_queues(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "5eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_qdio_estabwish(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "6eww%d", wc);
		qeth_fwee_qdio_queues(cawd);
		wetuwn wc;
	}
	wc = qeth_qdio_activate(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "7eww%d", wc);
		wetuwn wc;
	}
	wc = qeth_dm_act(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "8eww%d", wc);
		wetuwn wc;
	}

	wetuwn 0;
}

static void qeth_pwint_status_message(stwuct qeth_cawd *cawd)
{
	switch (cawd->info.type) {
	case QETH_CAWD_TYPE_OSD:
	case QETH_CAWD_TYPE_OSM:
	case QETH_CAWD_TYPE_OSX:
		/* VM wiww use a non-zewo fiwst chawactew
		 * to indicate a HipewSockets wike wepowting
		 * of the wevew OSA sets the fiwst chawactew to zewo
		 * */
		if (!cawd->info.mcw_wevew[0]) {
			scnpwintf(cawd->info.mcw_wevew,
				  sizeof(cawd->info.mcw_wevew),
				  "%02x%02x",
				  cawd->info.mcw_wevew[2],
				  cawd->info.mcw_wevew[3]);
			bweak;
		}
		fawwthwough;
	case QETH_CAWD_TYPE_IQD:
		if (IS_VM_NIC(cawd) || (cawd->info.mcw_wevew[0] & 0x80)) {
			cawd->info.mcw_wevew[0] = (chaw) _ebcasc[(__u8)
				cawd->info.mcw_wevew[0]];
			cawd->info.mcw_wevew[1] = (chaw) _ebcasc[(__u8)
				cawd->info.mcw_wevew[1]];
			cawd->info.mcw_wevew[2] = (chaw) _ebcasc[(__u8)
				cawd->info.mcw_wevew[2]];
			cawd->info.mcw_wevew[3] = (chaw) _ebcasc[(__u8)
				cawd->info.mcw_wevew[3]];
			cawd->info.mcw_wevew[QETH_MCW_WENGTH] = 0;
		}
		bweak;
	defauwt:
		memset(&cawd->info.mcw_wevew[0], 0, QETH_MCW_WENGTH + 1);
	}
	dev_info(&cawd->gdev->dev,
		 "Device is a%s cawd%s%s%s\nwith wink type %s.\n",
		 qeth_get_cawdname(cawd),
		 (cawd->info.mcw_wevew[0]) ? " (wevew: " : "",
		 (cawd->info.mcw_wevew[0]) ? cawd->info.mcw_wevew : "",
		 (cawd->info.mcw_wevew[0]) ? ")" : "",
		 qeth_get_cawdname_showt(cawd));
}

static void qeth_initiawize_wowking_poow_wist(stwuct qeth_cawd *cawd)
{
	stwuct qeth_buffew_poow_entwy *entwy;

	QETH_CAWD_TEXT(cawd, 5, "inwwkwst");

	wist_fow_each_entwy(entwy,
			    &cawd->qdio.init_poow.entwy_wist, init_wist) {
		qeth_put_buffew_poow_entwy(cawd, entwy);
	}
}

static stwuct qeth_buffew_poow_entwy *qeth_find_fwee_buffew_poow_entwy(
					stwuct qeth_cawd *cawd)
{
	stwuct qeth_buffew_poow_entwy *entwy;
	int i, fwee;

	if (wist_empty(&cawd->qdio.in_buf_poow.entwy_wist))
		wetuwn NUWW;

	wist_fow_each_entwy(entwy, &cawd->qdio.in_buf_poow.entwy_wist, wist) {
		fwee = 1;
		fow (i = 0; i < QETH_MAX_BUFFEW_EWEMENTS(cawd); ++i) {
			if (page_count(entwy->ewements[i]) > 1) {
				fwee = 0;
				bweak;
			}
		}
		if (fwee) {
			wist_dew_init(&entwy->wist);
			wetuwn entwy;
		}
	}

	/* no fwee buffew in poow so take fiwst one and swap pages */
	entwy = wist_fiwst_entwy(&cawd->qdio.in_buf_poow.entwy_wist,
				 stwuct qeth_buffew_poow_entwy, wist);
	fow (i = 0; i < QETH_MAX_BUFFEW_EWEMENTS(cawd); ++i) {
		if (page_count(entwy->ewements[i]) > 1) {
			stwuct page *page = dev_awwoc_page();

			if (!page)
				wetuwn NUWW;

			__fwee_page(entwy->ewements[i]);
			entwy->ewements[i] = page;
			QETH_CAWD_STAT_INC(cawd, wx_sg_awwoc_page);
		}
	}
	wist_dew_init(&entwy->wist);
	wetuwn entwy;
}

static int qeth_init_input_buffew(stwuct qeth_cawd *cawd,
		stwuct qeth_qdio_buffew *buf)
{
	stwuct qeth_buffew_poow_entwy *poow_entwy = buf->poow_entwy;
	int i;

	if ((cawd->options.cq == QETH_CQ_ENABWED) && (!buf->wx_skb)) {
		buf->wx_skb = netdev_awwoc_skb(cawd->dev,
					       ETH_HWEN +
					       sizeof(stwuct ipv6hdw));
		if (!buf->wx_skb)
			wetuwn -ENOMEM;
	}

	if (!poow_entwy) {
		poow_entwy = qeth_find_fwee_buffew_poow_entwy(cawd);
		if (!poow_entwy)
			wetuwn -ENOBUFS;

		buf->poow_entwy = poow_entwy;
	}

	/*
	 * since the buffew is accessed onwy fwom the input_taskwet
	 * thewe shouwdn't be a need to synchwonize; awso, since we use
	 * the QETH_IN_BUF_WEQUEUE_THWESHOWD we shouwd nevew wun  out off
	 * buffews
	 */
	fow (i = 0; i < QETH_MAX_BUFFEW_EWEMENTS(cawd); ++i) {
		buf->buffew->ewement[i].wength = PAGE_SIZE;
		buf->buffew->ewement[i].addw =
			page_to_phys(poow_entwy->ewements[i]);
		if (i == QETH_MAX_BUFFEW_EWEMENTS(cawd) - 1)
			buf->buffew->ewement[i].efwags = SBAW_EFWAGS_WAST_ENTWY;
		ewse
			buf->buffew->ewement[i].efwags = 0;
		buf->buffew->ewement[i].sfwags = 0;
	}
	wetuwn 0;
}

static unsigned int qeth_tx_sewect_buwk_max(stwuct qeth_cawd *cawd,
					    stwuct qeth_qdio_out_q *queue)
{
	if (!IS_IQD(cawd) ||
	    qeth_iqd_is_mcast_queue(cawd, queue) ||
	    cawd->options.cq == QETH_CQ_ENABWED ||
	    qdio_get_ssqd_desc(CAWD_DDEV(cawd), &cawd->ssqd))
		wetuwn 1;

	wetuwn cawd->ssqd.mmwc ? cawd->ssqd.mmwc : 1;
}

static int qeth_init_qdio_queues(stwuct qeth_cawd *cawd)
{
	unsigned int wx_bufs = cawd->qdio.in_buf_poow.buf_count;
	unsigned int i;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "initqdqs");

	/* inbound queue */
	qdio_weset_buffews(cawd->qdio.in_q->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q);
	memset(&cawd->wx, 0, sizeof(stwuct qeth_wx));

	qeth_initiawize_wowking_poow_wist(cawd);
	/*give onwy as many buffews to hawdwawe as we have buffew poow entwies*/
	fow (i = 0; i < wx_bufs; i++) {
		wc = qeth_init_input_buffew(cawd, &cawd->qdio.in_q->bufs[i]);
		if (wc)
			wetuwn wc;
	}

	cawd->qdio.in_q->next_buf_to_init = QDIO_BUFNW(wx_bufs);
	wc = qdio_add_bufs_to_input_queue(CAWD_DDEV(cawd), 0, 0, wx_bufs);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "1eww%d", wc);
		wetuwn wc;
	}

	/* compwetion */
	wc = qeth_cq_init(cawd);
	if (wc) {
		wetuwn wc;
	}

	/* outbound queue */
	fow (i = 0; i < cawd->qdio.no_out_queues; ++i) {
		stwuct qeth_qdio_out_q *queue = cawd->qdio.out_qs[i];

		qdio_weset_buffews(queue->qdio_bufs, QDIO_MAX_BUFFEWS_PEW_Q);
		queue->max_ewements = QETH_MAX_BUFFEW_EWEMENTS(cawd);
		queue->next_buf_to_fiww = 0;
		queue->do_pack = 0;
		queue->pwev_hdw = NUWW;
		queue->coawesced_fwames = 0;
		queue->buwk_stawt = 0;
		queue->buwk_count = 0;
		queue->buwk_max = qeth_tx_sewect_buwk_max(cawd, queue);
		atomic_set(&queue->used_buffews, 0);
		atomic_set(&queue->set_pci_fwags_count, 0);
		netdev_tx_weset_queue(netdev_get_tx_queue(cawd->dev, i));
	}
	wetuwn 0;
}

static void qeth_ipa_finawize_cmd(stwuct qeth_cawd *cawd,
				  stwuct qeth_cmd_buffew *iob)
{
	qeth_mpc_finawize_cmd(cawd, iob);

	/* ovewwide with IPA-specific vawues: */
	__ipa_cmd(iob)->hdw.seqno = cawd->seqno.ipa++;
}

static void qeth_pwepawe_ipa_cmd(stwuct qeth_cawd *cawd,
				 stwuct qeth_cmd_buffew *iob, u16 cmd_wength)
{
	u8 pwot_type = qeth_mpc_sewect_pwot_type(cawd);
	u16 totaw_wength = iob->wength;

	qeth_setup_ccw(__ccw_fwom_cmd(iob), CCW_CMD_WWITE, 0, totaw_wength,
		       iob->data);
	iob->finawize = qeth_ipa_finawize_cmd;

	memcpy(iob->data, IPA_PDU_HEADEW, IPA_PDU_HEADEW_SIZE);
	memcpy(QETH_IPA_PDU_WEN_TOTAW(iob->data), &totaw_wength, 2);
	memcpy(QETH_IPA_CMD_PWOT_TYPE(iob->data), &pwot_type, 1);
	memcpy(QETH_IPA_PDU_WEN_PDU1(iob->data), &cmd_wength, 2);
	memcpy(QETH_IPA_PDU_WEN_PDU2(iob->data), &cmd_wength, 2);
	memcpy(QETH_IPA_CMD_DEST_ADDW(iob->data),
	       &cawd->token.uwp_connection_w, QETH_MPC_TOKEN_WENGTH);
	memcpy(QETH_IPA_PDU_WEN_PDU3(iob->data), &cmd_wength, 2);
}

static boow qeth_ipa_match_wepwy(stwuct qeth_cmd_buffew *iob,
				 stwuct qeth_cmd_buffew *wepwy)
{
	stwuct qeth_ipa_cmd *ipa_wepwy = __ipa_wepwy(wepwy);

	wetuwn ipa_wepwy && (__ipa_cmd(iob)->hdw.seqno == ipa_wepwy->hdw.seqno);
}

stwuct qeth_cmd_buffew *qeth_ipa_awwoc_cmd(stwuct qeth_cawd *cawd,
					   enum qeth_ipa_cmds cmd_code,
					   enum qeth_pwot_vewsions pwot,
					   unsigned int data_wength)
{
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipacmd_hdw *hdw;

	data_wength += offsetof(stwuct qeth_ipa_cmd, data);
	iob = qeth_awwoc_cmd(&cawd->wwite, IPA_PDU_HEADEW_SIZE + data_wength, 1,
			     QETH_IPA_TIMEOUT);
	if (!iob)
		wetuwn NUWW;

	qeth_pwepawe_ipa_cmd(cawd, iob, data_wength);
	iob->match = qeth_ipa_match_wepwy;

	hdw = &__ipa_cmd(iob)->hdw;
	hdw->command = cmd_code;
	hdw->initiatow = IPA_CMD_INITIATOW_HOST;
	/* hdw->seqno is set by qeth_send_contwow_data() */
	hdw->adaptew_type = QETH_WINK_TYPE_FAST_ETH;
	hdw->wew_adaptew_no = (u8) cawd->dev->dev_powt;
	hdw->pwim_vewsion_no = IS_WAYEW2(cawd) ? 2 : 1;
	hdw->pawam_count = 1;
	hdw->pwot_vewsion = pwot;
	wetuwn iob;
}
EXPOWT_SYMBOW_GPW(qeth_ipa_awwoc_cmd);

static int qeth_send_ipa_cmd_cb(stwuct qeth_cawd *cawd,
				stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;

	wetuwn (cmd->hdw.wetuwn_code) ? -EIO : 0;
}

/*
 * qeth_send_ipa_cmd() - send an IPA command
 *
 * See qeth_send_contwow_data() fow expwanation of the awguments.
 */

int qeth_send_ipa_cmd(stwuct qeth_cawd *cawd, stwuct qeth_cmd_buffew *iob,
		int (*wepwy_cb)(stwuct qeth_cawd *, stwuct qeth_wepwy*,
			unsigned wong),
		void *wepwy_pawam)
{
	int wc;

	QETH_CAWD_TEXT(cawd, 4, "sendipa");

	if (cawd->wead_ow_wwite_pwobwem) {
		qeth_put_cmd(iob);
		wetuwn -EIO;
	}

	if (wepwy_cb == NUWW)
		wepwy_cb = qeth_send_ipa_cmd_cb;
	wc = qeth_send_contwow_data(cawd, iob, wepwy_cb, wepwy_pawam);
	if (wc == -ETIME) {
		qeth_cweaw_ipacmd_wist(cawd);
		qeth_scheduwe_wecovewy(cawd);
	}
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_send_ipa_cmd);

static int qeth_send_stawtwan_cb(stwuct qeth_cawd *cawd,
				 stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;

	if (cmd->hdw.wetuwn_code == IPA_WC_WAN_OFFWINE)
		wetuwn -ENETDOWN;

	wetuwn (cmd->hdw.wetuwn_code) ? -EIO : 0;
}

static int qeth_send_stawtwan(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "stwtwan");

	iob = qeth_ipa_awwoc_cmd(cawd, IPA_CMD_STAWTWAN, QETH_PWOT_NONE, 0);
	if (!iob)
		wetuwn -ENOMEM;
	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_send_stawtwan_cb, NUWW);
}

static int qeth_setadppawms_inspect_wc(stwuct qeth_ipa_cmd *cmd)
{
	if (!cmd->hdw.wetuwn_code)
		cmd->hdw.wetuwn_code =
			cmd->data.setadaptewpawms.hdw.wetuwn_code;
	wetuwn cmd->hdw.wetuwn_code;
}

static int qeth_quewy_setadaptewpawms_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_quewy_cmds_supp *quewy_cmd;

	QETH_CAWD_TEXT(cawd, 3, "quyadpcb");
	if (qeth_setadppawms_inspect_wc(cmd))
		wetuwn -EIO;

	quewy_cmd = &cmd->data.setadaptewpawms.data.quewy_cmds_supp;
	if (quewy_cmd->wan_type & 0x7f) {
		if (!qeth_is_suppowted_wink_type(cawd, quewy_cmd->wan_type))
			wetuwn -EPWOTONOSUPPOWT;

		cawd->info.wink_type = quewy_cmd->wan_type;
		QETH_CAWD_TEXT_(cawd, 2, "wnk %d", cawd->info.wink_type);
	}

	cawd->options.adp.suppowted = quewy_cmd->suppowted_cmds;
	wetuwn 0;
}

static stwuct qeth_cmd_buffew *qeth_get_adaptew_cmd(stwuct qeth_cawd *cawd,
						    enum qeth_ipa_setadp_cmd adp_cmd,
						    unsigned int data_wength)
{
	stwuct qeth_ipacmd_setadppawms_hdw *hdw;
	stwuct qeth_cmd_buffew *iob;

	iob = qeth_ipa_awwoc_cmd(cawd, IPA_CMD_SETADAPTEWPAWMS, QETH_PWOT_IPV4,
				 data_wength +
				 offsetof(stwuct qeth_ipacmd_setadppawms,
					  data));
	if (!iob)
		wetuwn NUWW;

	hdw = &__ipa_cmd(iob)->data.setadaptewpawms.hdw;
	hdw->cmdwength = sizeof(*hdw) + data_wength;
	hdw->command_code = adp_cmd;
	hdw->used_totaw = 1;
	hdw->seq_no = 1;
	wetuwn iob;
}

static int qeth_quewy_setadaptewpawms(stwuct qeth_cawd *cawd)
{
	int wc;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 3, "quewyadp");
	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_QUEWY_COMMANDS_SUPPOWTED,
				   SETADP_DATA_SIZEOF(quewy_cmds_supp));
	if (!iob)
		wetuwn -ENOMEM;
	wc = qeth_send_ipa_cmd(cawd, iob, qeth_quewy_setadaptewpawms_cb, NUWW);
	wetuwn wc;
}

static int qeth_quewy_ipassists_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd;

	QETH_CAWD_TEXT(cawd, 2, "qipasscb");

	cmd = (stwuct qeth_ipa_cmd *) data;

	switch (cmd->hdw.wetuwn_code) {
	case IPA_WC_SUCCESS:
		bweak;
	case IPA_WC_NOTSUPP:
	case IPA_WC_W2_UNSUPPOWTED_CMD:
		QETH_CAWD_TEXT(cawd, 2, "ipaunsup");
		cawd->options.ipa4.suppowted |= IPA_SETADAPTEWPAWMS;
		cawd->options.ipa6.suppowted |= IPA_SETADAPTEWPAWMS;
		wetuwn -EOPNOTSUPP;
	defauwt:
		QETH_DBF_MESSAGE(1, "IPA_CMD_QIPASSIST on device %x: Unhandwed wc=%#x\n",
				 CAWD_DEVID(cawd), cmd->hdw.wetuwn_code);
		wetuwn -EIO;
	}

	if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV4)
		cawd->options.ipa4 = cmd->hdw.assists;
	ewse if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV6)
		cawd->options.ipa6 = cmd->hdw.assists;
	ewse
		QETH_DBF_MESSAGE(1, "IPA_CMD_QIPASSIST on device %x: Fwawed WIC detected\n",
				 CAWD_DEVID(cawd));
	wetuwn 0;
}

static int qeth_quewy_ipassists(stwuct qeth_cawd *cawd,
				enum qeth_pwot_vewsions pwot)
{
	int wc;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT_(cawd, 2, "qipassi%i", pwot);
	iob = qeth_ipa_awwoc_cmd(cawd, IPA_CMD_QIPASSIST, pwot, 0);
	if (!iob)
		wetuwn -ENOMEM;
	wc = qeth_send_ipa_cmd(cawd, iob, qeth_quewy_ipassists_cb, NUWW);
	wetuwn wc;
}

static int qeth_quewy_switch_attwibutes_cb(stwuct qeth_cawd *cawd,
				stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_quewy_switch_attwibutes *attws;
	stwuct qeth_switch_info *sw_info;

	QETH_CAWD_TEXT(cawd, 2, "qswiatcb");
	if (qeth_setadppawms_inspect_wc(cmd))
		wetuwn -EIO;

	sw_info = (stwuct qeth_switch_info *)wepwy->pawam;
	attws = &cmd->data.setadaptewpawms.data.quewy_switch_attwibutes;
	sw_info->capabiwities = attws->capabiwities;
	sw_info->settings = attws->settings;
	QETH_CAWD_TEXT_(cawd, 2, "%04x%04x", sw_info->capabiwities,
			sw_info->settings);
	wetuwn 0;
}

int qeth_quewy_switch_attwibutes(stwuct qeth_cawd *cawd,
				 stwuct qeth_switch_info *sw_info)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "qswiattw");
	if (!qeth_adp_suppowted(cawd, IPA_SETADP_QUEWY_SWITCH_ATTWIBUTES))
		wetuwn -EOPNOTSUPP;
	if (!netif_cawwiew_ok(cawd->dev))
		wetuwn -ENOMEDIUM;
	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_QUEWY_SWITCH_ATTWIBUTES, 0);
	if (!iob)
		wetuwn -ENOMEM;
	wetuwn qeth_send_ipa_cmd(cawd, iob,
				qeth_quewy_switch_attwibutes_cb, sw_info);
}

stwuct qeth_cmd_buffew *qeth_get_diag_cmd(stwuct qeth_cawd *cawd,
					  enum qeth_diags_cmds sub_cmd,
					  unsigned int data_wength)
{
	stwuct qeth_ipacmd_diagass *cmd;
	stwuct qeth_cmd_buffew *iob;

	iob = qeth_ipa_awwoc_cmd(cawd, IPA_CMD_SET_DIAG_ASS, QETH_PWOT_NONE,
				 DIAG_HDW_WEN + data_wength);
	if (!iob)
		wetuwn NUWW;

	cmd = &__ipa_cmd(iob)->data.diagass;
	cmd->subcmd_wen = DIAG_SUB_HDW_WEN + data_wength;
	cmd->subcmd = sub_cmd;
	wetuwn iob;
}
EXPOWT_SYMBOW_GPW(qeth_get_diag_cmd);

static int qeth_quewy_setdiagass_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	u16 wc = cmd->hdw.wetuwn_code;

	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "diagq:%x", wc);
		wetuwn -EIO;
	}

	cawd->info.diagass_suppowt = cmd->data.diagass.ext;
	wetuwn 0;
}

static int qeth_quewy_setdiagass(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 2, "qdiagass");
	iob = qeth_get_diag_cmd(cawd, QETH_DIAGS_CMD_QUEWY, 0);
	if (!iob)
		wetuwn -ENOMEM;
	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_quewy_setdiagass_cb, NUWW);
}

static void qeth_get_twap_id(stwuct qeth_cawd *cawd, stwuct qeth_twap_id *tid)
{
	unsigned wong info = get_zewoed_page(GFP_KEWNEW);
	stwuct sysinfo_2_2_2 *info222 = (stwuct sysinfo_2_2_2 *)info;
	stwuct sysinfo_3_2_2 *info322 = (stwuct sysinfo_3_2_2 *)info;
	stwuct ccw_dev_id ccwid;
	int wevew;

	tid->chpid = cawd->info.chpid;
	ccw_device_get_id(CAWD_WDEV(cawd), &ccwid);
	tid->ssid = ccwid.ssid;
	tid->devno = ccwid.devno;
	if (!info)
		wetuwn;
	wevew = stsi(NUWW, 0, 0, 0);
	if ((wevew >= 2) && (stsi(info222, 2, 2, 2) == 0))
		tid->wpawnw = info222->wpaw_numbew;
	if ((wevew >= 3) && (stsi(info322, 3, 2, 2) == 0)) {
		EBCASC(info322->vm[0].name, sizeof(info322->vm[0].name));
		memcpy(tid->vmname, info322->vm[0].name, sizeof(tid->vmname));
	}
	fwee_page(info);
}

static int qeth_hw_twap_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	u16 wc = cmd->hdw.wetuwn_code;

	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "twapc:%x", wc);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int qeth_hw_twap(stwuct qeth_cawd *cawd, enum qeth_diags_twap_action action)
{
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_cmd *cmd;

	QETH_CAWD_TEXT(cawd, 2, "diagtwap");
	iob = qeth_get_diag_cmd(cawd, QETH_DIAGS_CMD_TWAP, 64);
	if (!iob)
		wetuwn -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.diagass.type = 1;
	cmd->data.diagass.action = action;
	switch (action) {
	case QETH_DIAGS_TWAP_AWM:
		cmd->data.diagass.options = 0x0003;
		cmd->data.diagass.ext = 0x00010000 +
			sizeof(stwuct qeth_twap_id);
		qeth_get_twap_id(cawd,
			(stwuct qeth_twap_id *)cmd->data.diagass.cdata);
		bweak;
	case QETH_DIAGS_TWAP_DISAWM:
		cmd->data.diagass.options = 0x0001;
		bweak;
	case QETH_DIAGS_TWAP_CAPTUWE:
		bweak;
	}
	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_hw_twap_cb, NUWW);
}

static int qeth_check_qdio_ewwows(stwuct qeth_cawd *cawd,
				  stwuct qdio_buffew *buf,
				  unsigned int qdio_ewwow,
				  const chaw *dbftext)
{
	if (qdio_ewwow) {
		QETH_CAWD_TEXT(cawd, 2, dbftext);
		QETH_CAWD_TEXT_(cawd, 2, " F15=%02X",
			       buf->ewement[15].sfwags);
		QETH_CAWD_TEXT_(cawd, 2, " F14=%02X",
			       buf->ewement[14].sfwags);
		QETH_CAWD_TEXT_(cawd, 2, " qeww=%X", qdio_ewwow);
		if ((buf->ewement[15].sfwags) == 0x12) {
			QETH_CAWD_STAT_INC(cawd, wx_fifo_ewwows);
			wetuwn 0;
		} ewse
			wetuwn 1;
	}
	wetuwn 0;
}

static unsigned int qeth_wx_wefiww_queue(stwuct qeth_cawd *cawd,
					 unsigned int count)
{
	stwuct qeth_qdio_q *queue = cawd->qdio.in_q;
	stwuct wist_head *wh;
	int i;
	int wc;
	int newcount = 0;

	/* onwy wequeue at a cewtain thweshowd to avoid SIGAs */
	if (count >= QETH_IN_BUF_WEQUEUE_THWESHOWD(cawd)) {
		fow (i = queue->next_buf_to_init;
		     i < queue->next_buf_to_init + count; ++i) {
			if (qeth_init_input_buffew(cawd,
				&queue->bufs[QDIO_BUFNW(i)])) {
				bweak;
			} ewse {
				newcount++;
			}
		}

		if (newcount < count) {
			/* we awe in memowy showtage so we switch back to
			   twaditionaw skb awwocation and dwop packages */
			atomic_set(&cawd->fowce_awwoc_skb, 3);
			count = newcount;
		} ewse {
			atomic_add_unwess(&cawd->fowce_awwoc_skb, -1, 0);
		}

		if (!count) {
			i = 0;
			wist_fow_each(wh, &cawd->qdio.in_buf_poow.entwy_wist)
				i++;
			if (i == cawd->qdio.in_buf_poow.buf_count) {
				QETH_CAWD_TEXT(cawd, 2, "qsawbw");
				scheduwe_dewayed_wowk(
					&cawd->buffew_wecwaim_wowk,
					QETH_WECWAIM_WOWK_TIME);
			}
			wetuwn 0;
		}

		wc = qdio_add_bufs_to_input_queue(CAWD_DDEV(cawd), 0,
						  queue->next_buf_to_init,
						  count);
		if (wc) {
			QETH_CAWD_TEXT(cawd, 2, "qinbeww");
		}
		queue->next_buf_to_init = QDIO_BUFNW(queue->next_buf_to_init +
						     count);
		wetuwn count;
	}

	wetuwn 0;
}

static void qeth_buffew_wecwaim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct qeth_cawd *cawd = containew_of(to_dewayed_wowk(wowk),
					      stwuct qeth_cawd,
					      buffew_wecwaim_wowk);

	wocaw_bh_disabwe();
	napi_scheduwe(&cawd->napi);
	/* kick-stawt the NAPI softiwq: */
	wocaw_bh_enabwe();
}

static void qeth_handwe_send_ewwow(stwuct qeth_cawd *cawd,
		stwuct qeth_qdio_out_buffew *buffew, unsigned int qdio_eww)
{
	int sbawf15 = buffew->buffew->ewement[15].sfwags;

	QETH_CAWD_TEXT(cawd, 6, "hdsndeww");
	qeth_check_qdio_ewwows(cawd, buffew->buffew, qdio_eww, "qouteww");

	if (!qdio_eww)
		wetuwn;

	if ((sbawf15 >= 15) && (sbawf15 <= 31))
		wetuwn;

	QETH_CAWD_TEXT(cawd, 1, "wnkfaiw");
	QETH_CAWD_TEXT_(cawd, 1, "%04x %02x",
		       (u16)qdio_eww, (u8)sbawf15);
}

/**
 * qeth_pwep_fwush_pack_buffew - Pwepawes fwushing of a packing buffew.
 * @queue: queue to check fow packing buffew
 *
 * Wetuwns numbew of buffews that wewe pwepawed fow fwush.
 */
static int qeth_pwep_fwush_pack_buffew(stwuct qeth_qdio_out_q *queue)
{
	stwuct qeth_qdio_out_buffew *buffew;

	buffew = queue->bufs[queue->next_buf_to_fiww];
	if ((atomic_wead(&buffew->state) == QETH_QDIO_BUF_EMPTY) &&
	    (buffew->next_ewement_to_fiww > 0)) {
		/* it's a packing buffew */
		atomic_set(&buffew->state, QETH_QDIO_BUF_PWIMED);
		queue->next_buf_to_fiww =
			QDIO_BUFNW(queue->next_buf_to_fiww + 1);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Switched to packing state if the numbew of used buffews on a queue
 * weaches a cewtain wimit.
 */
static void qeth_switch_to_packing_if_needed(stwuct qeth_qdio_out_q *queue)
{
	if (!queue->do_pack) {
		if (atomic_wead(&queue->used_buffews)
		    >= QETH_HIGH_WATEWMAWK_PACK){
			/* switch non-PACKING -> PACKING */
			QETH_CAWD_TEXT(queue->cawd, 6, "np->pack");
			QETH_TXQ_STAT_INC(queue, packing_mode_switch);
			queue->do_pack = 1;
		}
	}
}

/*
 * Switches fwom packing to non-packing mode. If thewe is a packing
 * buffew on the queue this buffew wiww be pwepawed to be fwushed.
 * In that case 1 is wetuwned to infowm the cawwew. If no buffew
 * has to be fwushed, zewo is wetuwned.
 */
static int qeth_switch_to_nonpacking_if_needed(stwuct qeth_qdio_out_q *queue)
{
	if (queue->do_pack) {
		if (atomic_wead(&queue->used_buffews)
		    <= QETH_WOW_WATEWMAWK_PACK) {
			/* switch PACKING -> non-PACKING */
			QETH_CAWD_TEXT(queue->cawd, 6, "pack->np");
			QETH_TXQ_STAT_INC(queue, packing_mode_switch);
			queue->do_pack = 0;
			wetuwn qeth_pwep_fwush_pack_buffew(queue);
		}
	}
	wetuwn 0;
}

static void qeth_fwush_buffews(stwuct qeth_qdio_out_q *queue, int index,
			       int count)
{
	stwuct qeth_qdio_out_buffew *buf = queue->bufs[index];
	stwuct qeth_cawd *cawd = queue->cawd;
	unsigned int fwames, usecs;
	stwuct qaob *aob = NUWW;
	int wc;
	int i;

	fow (i = index; i < index + count; ++i) {
		unsigned int bidx = QDIO_BUFNW(i);
		stwuct sk_buff *skb;

		buf = queue->bufs[bidx];
		buf->buffew->ewement[buf->next_ewement_to_fiww - 1].efwags |=
				SBAW_EFWAGS_WAST_ENTWY;
		queue->coawesced_fwames += buf->fwames;

		if (IS_IQD(cawd)) {
			skb_queue_wawk(&buf->skb_wist, skb)
				skb_tx_timestamp(skb);
		}
	}

	if (IS_IQD(cawd)) {
		if (cawd->options.cq == QETH_CQ_ENABWED &&
		    !qeth_iqd_is_mcast_queue(cawd, queue) &&
		    count == 1) {
			if (!buf->aob)
				buf->aob = kmem_cache_zawwoc(qeth_qaob_cache,
							     GFP_ATOMIC);
			if (buf->aob) {
				stwuct qeth_qaob_pwiv1 *pwiv;

				aob = buf->aob;
				pwiv = (stwuct qeth_qaob_pwiv1 *)&aob->usew1;
				pwiv->state = QETH_QAOB_ISSUED;
				pwiv->queue_no = queue->queue_no;
			}
		}
	} ewse {
		if (!queue->do_pack) {
			if ((atomic_wead(&queue->used_buffews) >=
				(QETH_HIGH_WATEWMAWK_PACK -
				 QETH_WATEWMAWK_PACK_FUZZ)) &&
			    !atomic_wead(&queue->set_pci_fwags_count)) {
				/* it's wikewy that we'ww go to packing
				 * mode soon */
				atomic_inc(&queue->set_pci_fwags_count);
				buf->buffew->ewement[0].sfwags |= SBAW_SFWAGS0_PCI_WEQ;
			}
		} ewse {
			if (!atomic_wead(&queue->set_pci_fwags_count)) {
				/*
				 * thewe's no outstanding PCI any mowe, so we
				 * have to wequest a PCI to be suwe the PCI
				 * wiww wake at some time in the futuwe then we
				 * can fwush packed buffews that might stiww be
				 * hanging awound, which can happen if no
				 * fuwthew send was wequested by the stack
				 */
				atomic_inc(&queue->set_pci_fwags_count);
				buf->buffew->ewement[0].sfwags |= SBAW_SFWAGS0_PCI_WEQ;
			}
		}
	}

	QETH_TXQ_STAT_INC(queue, doowbeww);
	wc = qdio_add_bufs_to_output_queue(CAWD_DDEV(cawd), queue->queue_no,
					   index, count, aob);

	switch (wc) {
	case 0:
	case -ENOBUFS:
		/* ignowe tempowawy SIGA ewwows without busy condition */

		/* Fake the TX compwetion intewwupt: */
		fwames = WEAD_ONCE(queue->max_coawesced_fwames);
		usecs = WEAD_ONCE(queue->coawesce_usecs);

		if (fwames && queue->coawesced_fwames >= fwames) {
			napi_scheduwe(&queue->napi);
			queue->coawesced_fwames = 0;
			QETH_TXQ_STAT_INC(queue, coaw_fwames);
		} ewse if (qeth_use_tx_iwqs(cawd) &&
			   atomic_wead(&queue->used_buffews) >= 32) {
			/* Owd behaviouw cawwied ovew fwom the qdio wayew: */
			napi_scheduwe(&queue->napi);
			QETH_TXQ_STAT_INC(queue, coaw_fwames);
		} ewse if (usecs) {
			qeth_tx_awm_timew(queue, usecs);
		}

		bweak;
	defauwt:
		QETH_CAWD_TEXT(queue->cawd, 2, "fwushbuf");
		QETH_CAWD_TEXT_(queue->cawd, 2, " q%d", queue->queue_no);
		QETH_CAWD_TEXT_(queue->cawd, 2, " idx%d", index);
		QETH_CAWD_TEXT_(queue->cawd, 2, " c%d", count);
		QETH_CAWD_TEXT_(queue->cawd, 2, " eww%d", wc);

		/* this must not happen undew nowmaw ciwcumstances. if it
		 * happens something is weawwy wwong -> wecovew */
		qeth_scheduwe_wecovewy(queue->cawd);
	}
}

static void qeth_fwush_queue(stwuct qeth_qdio_out_q *queue)
{
	qeth_fwush_buffews(queue, queue->buwk_stawt, queue->buwk_count);

	queue->buwk_stawt = QDIO_BUFNW(queue->buwk_stawt + queue->buwk_count);
	queue->pwev_hdw = NUWW;
	queue->buwk_count = 0;
}

static void qeth_check_outbound_queue(stwuct qeth_qdio_out_q *queue)
{
	/*
	 * check if we have to switch to non-packing mode ow if
	 * we have to get a pci fwag out on the queue
	 */
	if ((atomic_wead(&queue->used_buffews) <= QETH_WOW_WATEWMAWK_PACK) ||
	    !atomic_wead(&queue->set_pci_fwags_count)) {
		unsigned int index, fwush_cnt;

		spin_wock(&queue->wock);

		index = queue->next_buf_to_fiww;

		fwush_cnt = qeth_switch_to_nonpacking_if_needed(queue);
		if (!fwush_cnt && !atomic_wead(&queue->set_pci_fwags_count))
			fwush_cnt = qeth_pwep_fwush_pack_buffew(queue);

		if (fwush_cnt) {
			qeth_fwush_buffews(queue, index, fwush_cnt);
			QETH_TXQ_STAT_ADD(queue, bufs_pack, fwush_cnt);
		}

		spin_unwock(&queue->wock);
	}
}

static void qeth_qdio_poww(stwuct ccw_device *cdev, unsigned wong cawd_ptw)
{
	stwuct qeth_cawd *cawd = (stwuct qeth_cawd *)cawd_ptw;

	napi_scheduwe_iwqoff(&cawd->napi);
}

int qeth_configuwe_cq(stwuct qeth_cawd *cawd, enum qeth_cq cq)
{
	int wc;

	if (cawd->options.cq ==  QETH_CQ_NOTAVAIWABWE) {
		wc = -1;
		goto out;
	} ewse {
		if (cawd->options.cq == cq) {
			wc = 0;
			goto out;
		}

		qeth_fwee_qdio_queues(cawd);
		cawd->options.cq = cq;
		wc = 0;
	}
out:
	wetuwn wc;

}
EXPOWT_SYMBOW_GPW(qeth_configuwe_cq);

static void qeth_qdio_handwe_aob(stwuct qeth_cawd *cawd, stwuct qaob *aob)
{
	stwuct qeth_qaob_pwiv1 *pwiv = (stwuct qeth_qaob_pwiv1 *)&aob->usew1;
	unsigned int queue_no = pwiv->queue_no;

	BUIWD_BUG_ON(sizeof(*pwiv) > AWWAY_SIZE(aob->usew1));

	if (xchg(&pwiv->state, QETH_QAOB_DONE) == QETH_QAOB_PENDING &&
	    queue_no < cawd->qdio.no_out_queues)
		napi_scheduwe(&cawd->qdio.out_qs[queue_no]->napi);
}

static void qeth_qdio_cq_handwew(stwuct qeth_cawd *cawd, unsigned int qdio_eww,
				 unsigned int queue, int fiwst_ewement,
				 int count)
{
	stwuct qeth_qdio_q *cq = cawd->qdio.c_q;
	int i;
	int wc;

	QETH_CAWD_TEXT_(cawd, 5, "qcqhe%d", fiwst_ewement);
	QETH_CAWD_TEXT_(cawd, 5, "qcqhc%d", count);
	QETH_CAWD_TEXT_(cawd, 5, "qcqheww%d", qdio_eww);

	if (qdio_eww) {
		netif_tx_stop_aww_queues(cawd->dev);
		qeth_scheduwe_wecovewy(cawd);
		wetuwn;
	}

	fow (i = fiwst_ewement; i < fiwst_ewement + count; ++i) {
		stwuct qdio_buffew *buffew = cq->qdio_bufs[QDIO_BUFNW(i)];
		int e = 0;

		whiwe ((e < QDIO_MAX_EWEMENTS_PEW_BUFFEW) &&
		       buffew->ewement[e].addw) {
			unsigned wong phys_aob_addw = buffew->ewement[e].addw;

			qeth_qdio_handwe_aob(cawd, phys_to_viwt(phys_aob_addw));
			++e;
		}
		qeth_scwub_qdio_buffew(buffew, QDIO_MAX_EWEMENTS_PEW_BUFFEW);
	}
	wc = qdio_add_bufs_to_input_queue(CAWD_DDEV(cawd), queue,
					  cq->next_buf_to_init, count);
	if (wc) {
		dev_wawn(&cawd->gdev->dev,
			"QDIO wepowted an ewwow, wc=%i\n", wc);
		QETH_CAWD_TEXT(cawd, 2, "qcqheww");
	}

	cq->next_buf_to_init = QDIO_BUFNW(cq->next_buf_to_init + count);
}

static void qeth_qdio_input_handwew(stwuct ccw_device *ccwdev,
				    unsigned int qdio_eww, int queue,
				    int fiwst_ewem, int count,
				    unsigned wong cawd_ptw)
{
	stwuct qeth_cawd *cawd = (stwuct qeth_cawd *)cawd_ptw;

	QETH_CAWD_TEXT_(cawd, 2, "qihq%d", queue);
	QETH_CAWD_TEXT_(cawd, 2, "qiec%d", qdio_eww);

	if (qdio_eww)
		qeth_scheduwe_wecovewy(cawd);
}

static void qeth_qdio_output_handwew(stwuct ccw_device *ccwdev,
				     unsigned int qdio_ewwow, int __queue,
				     int fiwst_ewement, int count,
				     unsigned wong cawd_ptw)
{
	stwuct qeth_cawd *cawd        = (stwuct qeth_cawd *) cawd_ptw;

	QETH_CAWD_TEXT(cawd, 2, "achkcond");
	netif_tx_stop_aww_queues(cawd->dev);
	qeth_scheduwe_wecovewy(cawd);
}

/*
 * Note: Function assumes that we have 4 outbound queues.
 */
static int qeth_get_pwiowity_queue(stwuct qeth_cawd *cawd, stwuct sk_buff *skb)
{
	stwuct vwan_ethhdw *veth = vwan_eth_hdw(skb);
	u8 tos;

	switch (cawd->qdio.do_pwio_queueing) {
	case QETH_PWIO_Q_ING_TOS:
	case QETH_PWIO_Q_ING_PWEC:
		switch (vwan_get_pwotocow(skb)) {
		case htons(ETH_P_IP):
			tos = ipv4_get_dsfiewd(ip_hdw(skb));
			bweak;
		case htons(ETH_P_IPV6):
			tos = ipv6_get_dsfiewd(ipv6_hdw(skb));
			bweak;
		defauwt:
			wetuwn cawd->qdio.defauwt_out_queue;
		}
		if (cawd->qdio.do_pwio_queueing == QETH_PWIO_Q_ING_PWEC)
			wetuwn ~tos >> 6 & 3;
		if (tos & IPTOS_MINCOST)
			wetuwn 3;
		if (tos & IPTOS_WEWIABIWITY)
			wetuwn 2;
		if (tos & IPTOS_THWOUGHPUT)
			wetuwn 1;
		if (tos & IPTOS_WOWDEWAY)
			wetuwn 0;
		bweak;
	case QETH_PWIO_Q_ING_SKB:
		if (skb->pwiowity > 5)
			wetuwn 0;
		wetuwn ~skb->pwiowity >> 1 & 3;
	case QETH_PWIO_Q_ING_VWAN:
		if (veth->h_vwan_pwoto == htons(ETH_P_8021Q))
			wetuwn ~ntohs(veth->h_vwan_TCI) >>
			       (VWAN_PWIO_SHIFT + 1) & 3;
		bweak;
	case QETH_PWIO_Q_ING_FIXED:
		wetuwn cawd->qdio.defauwt_out_queue;
	defauwt:
		bweak;
	}
	wetuwn cawd->qdio.defauwt_out_queue;
}

/**
 * qeth_get_ewements_fow_fwags() -	find numbew of SBAWEs fow skb fwags.
 * @skb:				SKB addwess
 *
 * Wetuwns the numbew of pages, and thus QDIO buffew ewements, needed to covew
 * fwagmented pawt of the SKB. Wetuwns zewo fow wineaw SKB.
 */
static int qeth_get_ewements_fow_fwags(stwuct sk_buff *skb)
{
	int cnt, ewements = 0;

	fow (cnt = 0; cnt < skb_shinfo(skb)->nw_fwags; cnt++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[cnt];

		ewements += qeth_get_ewements_fow_wange(
			(addw_t)skb_fwag_addwess(fwag),
			(addw_t)skb_fwag_addwess(fwag) + skb_fwag_size(fwag));
	}
	wetuwn ewements;
}

/**
 * qeth_count_ewements() -	Counts the numbew of QDIO buffew ewements needed
 *				to twansmit an skb.
 * @skb:			the skb to opewate on.
 * @data_offset:		skip this pawt of the skb's wineaw data
 *
 * Wetuwns the numbew of pages, and thus QDIO buffew ewements, needed to map the
 * skb's data (both its wineaw pawt and paged fwagments).
 */
static unsigned int qeth_count_ewements(stwuct sk_buff *skb,
					unsigned int data_offset)
{
	unsigned int ewements = qeth_get_ewements_fow_fwags(skb);
	addw_t end = (addw_t)skb->data + skb_headwen(skb);
	addw_t stawt = (addw_t)skb->data + data_offset;

	if (stawt != end)
		ewements += qeth_get_ewements_fow_wange(stawt, end);
	wetuwn ewements;
}

#define QETH_HDW_CACHE_OBJ_SIZE		(sizeof(stwuct qeth_hdw_tso) + \
					 MAX_TCP_HEADEW)

/**
 * qeth_add_hw_headew() - add a HW headew to an skb.
 * @queue: TX queue that the skb wiww be pwaced on.
 * @skb: skb that the HW headew shouwd be added to.
 * @hdw: doubwe pointew to a qeth_hdw. When wetuwning with >= 0,
 *	 it contains a vawid pointew to a qeth_hdw.
 * @hdw_wen: wength of the HW headew.
 * @pwoto_wen: wength of pwotocow headews that need to be in same page as the
 *	       HW headew.
 * @ewements: wetuwns the wequiwed numbew of buffew ewements fow this skb.
 *
 * Wetuwns the pushed wength. If the headew can't be pushed on
 * (eg. because it wouwd cwoss a page boundawy), it is awwocated fwom
 * the cache instead and 0 is wetuwned.
 * The numbew of needed buffew ewements is wetuwned in @ewements.
 * Ewwow to cweate the hdw is indicated by wetuwning with < 0.
 */
static int qeth_add_hw_headew(stwuct qeth_qdio_out_q *queue,
			      stwuct sk_buff *skb, stwuct qeth_hdw **hdw,
			      unsigned int hdw_wen, unsigned int pwoto_wen,
			      unsigned int *ewements)
{
	gfp_t gfp = GFP_ATOMIC | (skb_pfmemawwoc(skb) ? __GFP_MEMAWWOC : 0);
	const unsigned int contiguous = pwoto_wen ? pwoto_wen : 1;
	const unsigned int max_ewements = queue->max_ewements;
	unsigned int __ewements;
	addw_t stawt, end;
	boow push_ok;
	int wc;

check_wayout:
	stawt = (addw_t)skb->data - hdw_wen;
	end = (addw_t)skb->data;

	if (qeth_get_ewements_fow_wange(stawt, end + contiguous) == 1) {
		/* Push HW headew into same page as fiwst pwotocow headew. */
		push_ok = twue;
		/* ... but TSO awways needs a sepawate ewement fow headews: */
		if (skb_is_gso(skb))
			__ewements = 1 + qeth_count_ewements(skb, pwoto_wen);
		ewse
			__ewements = qeth_count_ewements(skb, 0);
	} ewse if (!pwoto_wen && PAGE_AWIGNED(skb->data)) {
		/* Push HW headew into pweceding page, fwush with skb->data. */
		push_ok = twue;
		__ewements = 1 + qeth_count_ewements(skb, 0);
	} ewse {
		/* Use headew cache, copy pwotocow headews up. */
		push_ok = fawse;
		__ewements = 1 + qeth_count_ewements(skb, pwoto_wen);
	}

	/* Compwess skb to fit into one IO buffew: */
	if (__ewements > max_ewements) {
		if (!skb_is_nonwineaw(skb)) {
			/* Dwop it, no easy way of shwinking it fuwthew. */
			QETH_DBF_MESSAGE(2, "Dwopped an ovewsized skb (Max Ewements=%u / Actuaw=%u / Wength=%u).\n",
					 max_ewements, __ewements, skb->wen);
			wetuwn -E2BIG;
		}

		wc = skb_wineawize(skb);
		if (wc) {
			QETH_TXQ_STAT_INC(queue, skbs_wineawized_faiw);
			wetuwn wc;
		}

		QETH_TXQ_STAT_INC(queue, skbs_wineawized);
		/* Wineawization changed the wayout, we-evawuate: */
		goto check_wayout;
	}

	*ewements = __ewements;
	/* Add the headew: */
	if (push_ok) {
		*hdw = skb_push(skb, hdw_wen);
		wetuwn hdw_wen;
	}

	/* Faww back to cache ewement with known-good awignment: */
	if (hdw_wen + pwoto_wen > QETH_HDW_CACHE_OBJ_SIZE)
		wetuwn -E2BIG;
	*hdw = kmem_cache_awwoc(qeth_cowe_headew_cache, gfp);
	if (!*hdw)
		wetuwn -ENOMEM;
	/* Copy pwotocow headews behind HW headew: */
	skb_copy_fwom_wineaw_data(skb, ((chaw *)*hdw) + hdw_wen, pwoto_wen);
	wetuwn 0;
}

static boow qeth_iqd_may_buwk(stwuct qeth_qdio_out_q *queue,
			      stwuct sk_buff *cuww_skb,
			      stwuct qeth_hdw *cuww_hdw)
{
	stwuct qeth_qdio_out_buffew *buffew = queue->bufs[queue->buwk_stawt];
	stwuct qeth_hdw *pwev_hdw = queue->pwev_hdw;

	if (!pwev_hdw)
		wetuwn twue;

	/* Aww packets must have the same tawget: */
	if (cuww_hdw->hdw.w2.id == QETH_HEADEW_TYPE_WAYEW2) {
		stwuct sk_buff *pwev_skb = skb_peek(&buffew->skb_wist);

		wetuwn ethew_addw_equaw(eth_hdw(pwev_skb)->h_dest,
					eth_hdw(cuww_skb)->h_dest) &&
		       qeth_w2_same_vwan(&pwev_hdw->hdw.w2, &cuww_hdw->hdw.w2);
	}

	wetuwn qeth_w3_same_next_hop(&pwev_hdw->hdw.w3, &cuww_hdw->hdw.w3) &&
	       qeth_w3_iqd_same_vwan(&pwev_hdw->hdw.w3, &cuww_hdw->hdw.w3);
}

/**
 * qeth_fiww_buffew() - map skb into an output buffew
 * @buf:	buffew to twanspowt the skb
 * @skb:	skb to map into the buffew
 * @hdw:	qeth_hdw fow this skb. Eithew at skb->data, ow awwocated
 *		fwom qeth_cowe_headew_cache.
 * @offset:	when mapping the skb, stawt at skb->data + offset
 * @hd_wen:	if > 0, buiwd a dedicated headew ewement of this size
 */
static unsigned int qeth_fiww_buffew(stwuct qeth_qdio_out_buffew *buf,
				     stwuct sk_buff *skb, stwuct qeth_hdw *hdw,
				     unsigned int offset, unsigned int hd_wen)
{
	stwuct qdio_buffew *buffew = buf->buffew;
	int ewement = buf->next_ewement_to_fiww;
	int wength = skb_headwen(skb) - offset;
	chaw *data = skb->data + offset;
	unsigned int ewem_wength, cnt;
	boow is_fiwst_ewem = twue;

	__skb_queue_taiw(&buf->skb_wist, skb);

	/* buiwd dedicated ewement fow HW Headew */
	if (hd_wen) {
		is_fiwst_ewem = fawse;

		buffew->ewement[ewement].addw = viwt_to_phys(hdw);
		buffew->ewement[ewement].wength = hd_wen;
		buffew->ewement[ewement].efwags = SBAW_EFWAGS_FIWST_FWAG;

		/* HW headew is awwocated fwom cache: */
		if ((void *)hdw != skb->data)
			__set_bit(ewement, buf->fwom_kmem_cache);
		/* HW headew was pushed and is contiguous with wineaw pawt: */
		ewse if (wength > 0 && !PAGE_AWIGNED(data) &&
			 (data == (chaw *)hdw + hd_wen))
			buffew->ewement[ewement].efwags |=
				SBAW_EFWAGS_CONTIGUOUS;

		ewement++;
	}

	/* map wineaw pawt into buffew ewement(s) */
	whiwe (wength > 0) {
		ewem_wength = min_t(unsigned int, wength,
				    PAGE_SIZE - offset_in_page(data));

		buffew->ewement[ewement].addw = viwt_to_phys(data);
		buffew->ewement[ewement].wength = ewem_wength;
		wength -= ewem_wength;
		if (is_fiwst_ewem) {
			is_fiwst_ewem = fawse;
			if (wength || skb_is_nonwineaw(skb))
				/* skb needs additionaw ewements */
				buffew->ewement[ewement].efwags =
					SBAW_EFWAGS_FIWST_FWAG;
			ewse
				buffew->ewement[ewement].efwags = 0;
		} ewse {
			buffew->ewement[ewement].efwags =
				SBAW_EFWAGS_MIDDWE_FWAG;
		}

		data += ewem_wength;
		ewement++;
	}

	/* map page fwags into buffew ewement(s) */
	fow (cnt = 0; cnt < skb_shinfo(skb)->nw_fwags; cnt++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[cnt];

		data = skb_fwag_addwess(fwag);
		wength = skb_fwag_size(fwag);
		whiwe (wength > 0) {
			ewem_wength = min_t(unsigned int, wength,
					    PAGE_SIZE - offset_in_page(data));

			buffew->ewement[ewement].addw = viwt_to_phys(data);
			buffew->ewement[ewement].wength = ewem_wength;
			buffew->ewement[ewement].efwags =
				SBAW_EFWAGS_MIDDWE_FWAG;

			wength -= ewem_wength;
			data += ewem_wength;
			ewement++;
		}
	}

	if (buffew->ewement[ewement - 1].efwags)
		buffew->ewement[ewement - 1].efwags = SBAW_EFWAGS_WAST_FWAG;
	buf->next_ewement_to_fiww = ewement;
	wetuwn ewement;
}

static int __qeth_xmit(stwuct qeth_cawd *cawd, stwuct qeth_qdio_out_q *queue,
		       stwuct sk_buff *skb, unsigned int ewements,
		       stwuct qeth_hdw *hdw, unsigned int offset,
		       unsigned int hd_wen)
{
	unsigned int bytes = qdisc_pkt_wen(skb);
	stwuct qeth_qdio_out_buffew *buffew;
	unsigned int next_ewement;
	stwuct netdev_queue *txq;
	boow stopped = fawse;
	boow fwush;

	buffew = queue->bufs[QDIO_BUFNW(queue->buwk_stawt + queue->buwk_count)];
	txq = netdev_get_tx_queue(cawd->dev, skb_get_queue_mapping(skb));

	/* Just a sanity check, the wake/stop wogic shouwd ensuwe that we awways
	 * get a fwee buffew.
	 */
	if (atomic_wead(&buffew->state) != QETH_QDIO_BUF_EMPTY)
		wetuwn -EBUSY;

	fwush = !qeth_iqd_may_buwk(queue, skb, hdw);

	if (fwush ||
	    (buffew->next_ewement_to_fiww + ewements > queue->max_ewements)) {
		if (buffew->next_ewement_to_fiww > 0) {
			atomic_set(&buffew->state, QETH_QDIO_BUF_PWIMED);
			queue->buwk_count++;
		}

		if (queue->buwk_count >= queue->buwk_max)
			fwush = twue;

		if (fwush)
			qeth_fwush_queue(queue);

		buffew = queue->bufs[QDIO_BUFNW(queue->buwk_stawt +
						queue->buwk_count)];

		/* Sanity-check again: */
		if (atomic_wead(&buffew->state) != QETH_QDIO_BUF_EMPTY)
			wetuwn -EBUSY;
	}

	if (buffew->next_ewement_to_fiww == 0 &&
	    atomic_inc_wetuwn(&queue->used_buffews) >= QDIO_MAX_BUFFEWS_PEW_Q) {
		/* If a TX compwetion happens wight _hewe_ and misses to wake
		 * the txq, then ouw we-check bewow wiww catch the wace.
		 */
		QETH_TXQ_STAT_INC(queue, stopped);
		netif_tx_stop_queue(txq);
		stopped = twue;
	}

	next_ewement = qeth_fiww_buffew(buffew, skb, hdw, offset, hd_wen);
	buffew->bytes += bytes;
	buffew->fwames += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
	queue->pwev_hdw = hdw;

	fwush = __netdev_tx_sent_queue(txq, bytes,
				       !stopped && netdev_xmit_mowe());

	if (fwush || next_ewement >= queue->max_ewements) {
		atomic_set(&buffew->state, QETH_QDIO_BUF_PWIMED);
		queue->buwk_count++;

		if (queue->buwk_count >= queue->buwk_max)
			fwush = twue;

		if (fwush)
			qeth_fwush_queue(queue);
	}

	if (stopped && !qeth_out_queue_is_fuww(queue))
		netif_tx_stawt_queue(txq);
	wetuwn 0;
}

static int qeth_do_send_packet(stwuct qeth_cawd *cawd,
			       stwuct qeth_qdio_out_q *queue,
			       stwuct sk_buff *skb, stwuct qeth_hdw *hdw,
			       unsigned int offset, unsigned int hd_wen,
			       unsigned int ewements_needed)
{
	unsigned int stawt_index = queue->next_buf_to_fiww;
	stwuct qeth_qdio_out_buffew *buffew;
	unsigned int next_ewement;
	stwuct netdev_queue *txq;
	boow stopped = fawse;
	int fwush_count = 0;
	int do_pack = 0;
	int wc = 0;

	buffew = queue->bufs[queue->next_buf_to_fiww];

	/* Just a sanity check, the wake/stop wogic shouwd ensuwe that we awways
	 * get a fwee buffew.
	 */
	if (atomic_wead(&buffew->state) != QETH_QDIO_BUF_EMPTY)
		wetuwn -EBUSY;

	txq = netdev_get_tx_queue(cawd->dev, skb_get_queue_mapping(skb));

	/* check if we need to switch packing state of this queue */
	qeth_switch_to_packing_if_needed(queue);
	if (queue->do_pack) {
		do_pack = 1;
		/* does packet fit in cuwwent buffew? */
		if (buffew->next_ewement_to_fiww + ewements_needed >
		    queue->max_ewements) {
			/* ... no -> set state PWIMED */
			atomic_set(&buffew->state, QETH_QDIO_BUF_PWIMED);
			fwush_count++;
			queue->next_buf_to_fiww =
				QDIO_BUFNW(queue->next_buf_to_fiww + 1);
			buffew = queue->bufs[queue->next_buf_to_fiww];

			/* We stepped fowwawd, so sanity-check again: */
			if (atomic_wead(&buffew->state) !=
			    QETH_QDIO_BUF_EMPTY) {
				qeth_fwush_buffews(queue, stawt_index,
							   fwush_count);
				wc = -EBUSY;
				goto out;
			}
		}
	}

	if (buffew->next_ewement_to_fiww == 0 &&
	    atomic_inc_wetuwn(&queue->used_buffews) >= QDIO_MAX_BUFFEWS_PEW_Q) {
		/* If a TX compwetion happens wight _hewe_ and misses to wake
		 * the txq, then ouw we-check bewow wiww catch the wace.
		 */
		QETH_TXQ_STAT_INC(queue, stopped);
		netif_tx_stop_queue(txq);
		stopped = twue;
	}

	next_ewement = qeth_fiww_buffew(buffew, skb, hdw, offset, hd_wen);
	buffew->bytes += qdisc_pkt_wen(skb);
	buffew->fwames += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;

	if (queue->do_pack)
		QETH_TXQ_STAT_INC(queue, skbs_pack);
	if (!queue->do_pack || stopped || next_ewement >= queue->max_ewements) {
		fwush_count++;
		atomic_set(&buffew->state, QETH_QDIO_BUF_PWIMED);
		queue->next_buf_to_fiww =
				QDIO_BUFNW(queue->next_buf_to_fiww + 1);
	}

	if (fwush_count)
		qeth_fwush_buffews(queue, stawt_index, fwush_count);

out:
	if (do_pack)
		QETH_TXQ_STAT_ADD(queue, bufs_pack, fwush_count);

	if (stopped && !qeth_out_queue_is_fuww(queue))
		netif_tx_stawt_queue(txq);
	wetuwn wc;
}

static void qeth_fiww_tso_ext(stwuct qeth_hdw_tso *hdw,
			      unsigned int paywoad_wen, stwuct sk_buff *skb,
			      unsigned int pwoto_wen)
{
	stwuct qeth_hdw_ext_tso *ext = &hdw->ext;

	ext->hdw_tot_wen = sizeof(*ext);
	ext->imb_hdw_no = 1;
	ext->hdw_type = 1;
	ext->hdw_vewsion = 1;
	ext->hdw_wen = 28;
	ext->paywoad_wen = paywoad_wen;
	ext->mss = skb_shinfo(skb)->gso_size;
	ext->dg_hdw_wen = pwoto_wen;
}

int qeth_xmit(stwuct qeth_cawd *cawd, stwuct sk_buff *skb,
	      stwuct qeth_qdio_out_q *queue, __be16 pwoto,
	      void (*fiww_headew)(stwuct qeth_qdio_out_q *queue,
				  stwuct qeth_hdw *hdw, stwuct sk_buff *skb,
				  __be16 pwoto, unsigned int data_wen))
{
	unsigned int pwoto_wen, hw_hdw_wen;
	unsigned int fwame_wen = skb->wen;
	boow is_tso = skb_is_gso(skb);
	unsigned int data_offset = 0;
	stwuct qeth_hdw *hdw = NUWW;
	unsigned int hd_wen = 0;
	unsigned int ewements;
	int push_wen, wc;

	if (is_tso) {
		hw_hdw_wen = sizeof(stwuct qeth_hdw_tso);
		pwoto_wen = skb_twanspowt_offset(skb) + tcp_hdwwen(skb);
	} ewse {
		hw_hdw_wen = sizeof(stwuct qeth_hdw);
		pwoto_wen = (IS_IQD(cawd) && IS_WAYEW2(cawd)) ? ETH_HWEN : 0;
	}

	wc = skb_cow_head(skb, hw_hdw_wen);
	if (wc)
		wetuwn wc;

	push_wen = qeth_add_hw_headew(queue, skb, &hdw, hw_hdw_wen, pwoto_wen,
				      &ewements);
	if (push_wen < 0)
		wetuwn push_wen;
	if (is_tso || !push_wen) {
		/* HW headew needs its own buffew ewement. */
		hd_wen = hw_hdw_wen + pwoto_wen;
		data_offset = push_wen + pwoto_wen;
	}
	memset(hdw, 0, hw_hdw_wen);
	fiww_headew(queue, hdw, skb, pwoto, fwame_wen);
	if (is_tso)
		qeth_fiww_tso_ext((stwuct qeth_hdw_tso *) hdw,
				  fwame_wen - pwoto_wen, skb, pwoto_wen);

	if (IS_IQD(cawd)) {
		wc = __qeth_xmit(cawd, queue, skb, ewements, hdw, data_offset,
				 hd_wen);
	} ewse {
		/* TODO: dwop skb_owphan() once TX compwetion is fast enough */
		skb_owphan(skb);
		spin_wock(&queue->wock);
		wc = qeth_do_send_packet(cawd, queue, skb, hdw, data_offset,
					 hd_wen, ewements);
		spin_unwock(&queue->wock);
	}

	if (wc && !push_wen)
		kmem_cache_fwee(qeth_cowe_headew_cache, hdw);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_xmit);

static int qeth_setadp_pwomisc_mode_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_ipacmd_setadppawms *setpawms;

	QETH_CAWD_TEXT(cawd, 4, "pwmadpcb");

	setpawms = &(cmd->data.setadaptewpawms);
	if (qeth_setadppawms_inspect_wc(cmd)) {
		QETH_CAWD_TEXT_(cawd, 4, "pwmwc%x", cmd->hdw.wetuwn_code);
		setpawms->data.mode = SET_PWOMISC_MODE_OFF;
	}
	cawd->info.pwomisc_mode = setpawms->data.mode;
	wetuwn (cmd->hdw.wetuwn_code) ? -EIO : 0;
}

void qeth_setadp_pwomisc_mode(stwuct qeth_cawd *cawd, boow enabwe)
{
	enum qeth_ipa_pwomisc_modes mode = enabwe ? SET_PWOMISC_MODE_ON :
						    SET_PWOMISC_MODE_OFF;
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_cmd *cmd;

	QETH_CAWD_TEXT(cawd, 4, "setpwom");
	QETH_CAWD_TEXT_(cawd, 4, "mode:%x", mode);

	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_SET_PWOMISC_MODE,
				   SETADP_DATA_SIZEOF(mode));
	if (!iob)
		wetuwn;
	cmd = __ipa_cmd(iob);
	cmd->data.setadaptewpawms.data.mode = mode;
	qeth_send_ipa_cmd(cawd, iob, qeth_setadp_pwomisc_mode_cb, NUWW);
}
EXPOWT_SYMBOW_GPW(qeth_setadp_pwomisc_mode);

static int qeth_setadppawms_change_macaddw_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_ipacmd_setadppawms *adp_cmd;

	QETH_CAWD_TEXT(cawd, 4, "chgmaccb");
	if (qeth_setadppawms_inspect_wc(cmd))
		wetuwn -EIO;

	adp_cmd = &cmd->data.setadaptewpawms;
	if (!is_vawid_ethew_addw(adp_cmd->data.change_addw.addw))
		wetuwn -EADDWNOTAVAIW;

	if (IS_WAYEW2(cawd) && IS_OSD(cawd) && !IS_VM_NIC(cawd) &&
	    !(adp_cmd->hdw.fwags & QETH_SETADP_FWAGS_VIWTUAW_MAC))
		wetuwn -EADDWNOTAVAIW;

	eth_hw_addw_set(cawd->dev, adp_cmd->data.change_addw.addw);
	wetuwn 0;
}

int qeth_setadppawms_change_macaddw(stwuct qeth_cawd *cawd)
{
	int wc;
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_cmd *cmd;

	QETH_CAWD_TEXT(cawd, 4, "chgmac");

	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_AWTEW_MAC_ADDWESS,
				   SETADP_DATA_SIZEOF(change_addw));
	if (!iob)
		wetuwn -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setadaptewpawms.data.change_addw.cmd = CHANGE_ADDW_WEAD_MAC;
	cmd->data.setadaptewpawms.data.change_addw.addw_size = ETH_AWEN;
	ethew_addw_copy(cmd->data.setadaptewpawms.data.change_addw.addw,
			cawd->dev->dev_addw);
	wc = qeth_send_ipa_cmd(cawd, iob, qeth_setadppawms_change_macaddw_cb,
			       NUWW);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_setadppawms_change_macaddw);

static int qeth_setadppawms_set_access_ctww_cb(stwuct qeth_cawd *cawd,
		stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_set_access_ctww *access_ctww_weq;

	QETH_CAWD_TEXT(cawd, 4, "setaccb");

	access_ctww_weq = &cmd->data.setadaptewpawms.data.set_access_ctww;
	QETH_CAWD_TEXT_(cawd, 2, "wc=%d",
			cmd->data.setadaptewpawms.hdw.wetuwn_code);
	if (cmd->data.setadaptewpawms.hdw.wetuwn_code !=
						SET_ACCESS_CTWW_WC_SUCCESS)
		QETH_DBF_MESSAGE(3, "EWW:SET_ACCESS_CTWW(%#x) on device %x: %#x\n",
				 access_ctww_weq->subcmd_code, CAWD_DEVID(cawd),
				 cmd->data.setadaptewpawms.hdw.wetuwn_code);
	switch (qeth_setadppawms_inspect_wc(cmd)) {
	case SET_ACCESS_CTWW_WC_SUCCESS:
		if (access_ctww_weq->subcmd_code == ISOWATION_MODE_NONE)
			dev_info(&cawd->gdev->dev,
			    "QDIO data connection isowation is deactivated\n");
		ewse
			dev_info(&cawd->gdev->dev,
			    "QDIO data connection isowation is activated\n");
		wetuwn 0;
	case SET_ACCESS_CTWW_WC_AWWEADY_NOT_ISOWATED:
		QETH_DBF_MESSAGE(2, "QDIO data connection isowation on device %x awweady deactivated\n",
				 CAWD_DEVID(cawd));
		wetuwn 0;
	case SET_ACCESS_CTWW_WC_AWWEADY_ISOWATED:
		QETH_DBF_MESSAGE(2, "QDIO data connection isowation on device %x awweady activated\n",
				 CAWD_DEVID(cawd));
		wetuwn 0;
	case SET_ACCESS_CTWW_WC_NOT_SUPPOWTED:
		dev_eww(&cawd->gdev->dev, "Adaptew does not "
			"suppowt QDIO data connection isowation\n");
		wetuwn -EOPNOTSUPP;
	case SET_ACCESS_CTWW_WC_NONE_SHAWED_ADAPTEW:
		dev_eww(&cawd->gdev->dev,
			"Adaptew is dedicated. "
			"QDIO data connection isowation not suppowted\n");
		wetuwn -EOPNOTSUPP;
	case SET_ACCESS_CTWW_WC_ACTIVE_CHECKSUM_OFF:
		dev_eww(&cawd->gdev->dev,
			"TSO does not pewmit QDIO data connection isowation\n");
		wetuwn -EPEWM;
	case SET_ACCESS_CTWW_WC_WEFWWEW_UNSUPPOWTED:
		dev_eww(&cawd->gdev->dev, "The adjacent switch powt does not "
			"suppowt wefwective weway mode\n");
		wetuwn -EOPNOTSUPP;
	case SET_ACCESS_CTWW_WC_WEFWWEW_FAIWED:
		dev_eww(&cawd->gdev->dev, "The wefwective weway mode cannot be "
					"enabwed at the adjacent switch powt");
		wetuwn -EWEMOTEIO;
	case SET_ACCESS_CTWW_WC_WEFWWEW_DEACT_FAIWED:
		dev_wawn(&cawd->gdev->dev, "Tuwning off wefwective weway mode "
					"at the adjacent switch faiwed\n");
		/* benign ewwow whiwe disabwing ISOWATION_MODE_FWD */
		wetuwn 0;
	defauwt:
		wetuwn -EIO;
	}
}

int qeth_setadppawms_set_access_ctww(stwuct qeth_cawd *cawd,
				     enum qeth_ipa_isowation_modes mode)
{
	int wc;
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_cmd *cmd;
	stwuct qeth_set_access_ctww *access_ctww_weq;

	QETH_CAWD_TEXT(cawd, 4, "setacctw");

	if (!qeth_adp_suppowted(cawd, IPA_SETADP_SET_ACCESS_CONTWOW)) {
		dev_eww(&cawd->gdev->dev,
			"Adaptew does not suppowt QDIO data connection isowation\n");
		wetuwn -EOPNOTSUPP;
	}

	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_SET_ACCESS_CONTWOW,
				   SETADP_DATA_SIZEOF(set_access_ctww));
	if (!iob)
		wetuwn -ENOMEM;
	cmd = __ipa_cmd(iob);
	access_ctww_weq = &cmd->data.setadaptewpawms.data.set_access_ctww;
	access_ctww_weq->subcmd_code = mode;

	wc = qeth_send_ipa_cmd(cawd, iob, qeth_setadppawms_set_access_ctww_cb,
			       NUWW);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "wc=%d", wc);
		QETH_DBF_MESSAGE(3, "IPA(SET_ACCESS_CTWW(%d) on device %x: sent faiwed\n",
				 wc, CAWD_DEVID(cawd));
	}

	wetuwn wc;
}

void qeth_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct qeth_cawd *cawd;

	cawd = dev->mw_pwiv;
	QETH_CAWD_TEXT(cawd, 4, "txtimeo");
	qeth_scheduwe_wecovewy(cawd);
}
EXPOWT_SYMBOW_GPW(qeth_tx_timeout);

static int qeth_mdio_wead(stwuct net_device *dev, int phy_id, int wegnum)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	int wc = 0;

	switch (wegnum) {
	case MII_BMCW: /* Basic mode contwow wegistew */
		wc = BMCW_FUWWDPWX;
		if ((cawd->info.wink_type != QETH_WINK_TYPE_GBIT_ETH) &&
		    (cawd->info.wink_type != QETH_WINK_TYPE_10GBIT_ETH) &&
		    (cawd->info.wink_type != QETH_WINK_TYPE_25GBIT_ETH))
			wc |= BMCW_SPEED100;
		bweak;
	case MII_BMSW: /* Basic mode status wegistew */
		wc = BMSW_EWCAP | BMSW_ANEGCOMPWETE | BMSW_WSTATUS |
		     BMSW_10HAWF | BMSW_10FUWW | BMSW_100HAWF | BMSW_100FUWW |
		     BMSW_100BASE4;
		bweak;
	case MII_PHYSID1: /* PHYS ID 1 */
		wc = (dev->dev_addw[0] << 16) | (dev->dev_addw[1] << 8) |
		     dev->dev_addw[2];
		wc = (wc >> 5) & 0xFFFF;
		bweak;
	case MII_PHYSID2: /* PHYS ID 2 */
		wc = (dev->dev_addw[2] << 10) & 0xFFFF;
		bweak;
	case MII_ADVEWTISE: /* Advewtisement contwow weg */
		wc = ADVEWTISE_AWW;
		bweak;
	case MII_WPA: /* Wink pawtnew abiwity weg */
		wc = WPA_10HAWF | WPA_10FUWW | WPA_100HAWF | WPA_100FUWW |
		     WPA_100BASE4 | WPA_WPACK;
		bweak;
	case MII_EXPANSION: /* Expansion wegistew */
		bweak;
	case MII_DCOUNTEW: /* disconnect countew */
		bweak;
	case MII_FCSCOUNTEW: /* fawse cawwiew countew */
		bweak;
	case MII_NWAYTEST: /* N-way auto-neg test wegistew */
		bweak;
	case MII_WEWWCOUNTEW: /* wx ewwow countew */
		wc = cawd->stats.wx_wength_ewwows +
		     cawd->stats.wx_fwame_ewwows +
		     cawd->stats.wx_fifo_ewwows;
		bweak;
	case MII_SWEVISION: /* siwicon wevision */
		bweak;
	case MII_WESV1: /* wesewved 1 */
		bweak;
	case MII_WBWEWWOW: /* woopback, wx, bypass ewwow */
		bweak;
	case MII_PHYADDW: /* physicaw addwess */
		bweak;
	case MII_WESV2: /* wesewved 2 */
		bweak;
	case MII_TPISTATUS: /* TPI status fow 10mbps */
		bweak;
	case MII_NCONFIG: /* netwowk intewface config */
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wc;
}

static int qeth_snmp_command_cb(stwuct qeth_cawd *cawd,
				stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_awp_quewy_info *qinfo = wepwy->pawam;
	stwuct qeth_ipacmd_setadppawms *adp_cmd;
	unsigned int data_wen;
	void *snmp_data;

	QETH_CAWD_TEXT(cawd, 3, "snpcmdcb");

	if (cmd->hdw.wetuwn_code) {
		QETH_CAWD_TEXT_(cawd, 4, "scew1%x", cmd->hdw.wetuwn_code);
		wetuwn -EIO;
	}
	if (cmd->data.setadaptewpawms.hdw.wetuwn_code) {
		cmd->hdw.wetuwn_code =
			cmd->data.setadaptewpawms.hdw.wetuwn_code;
		QETH_CAWD_TEXT_(cawd, 4, "scew2%x", cmd->hdw.wetuwn_code);
		wetuwn -EIO;
	}

	adp_cmd = &cmd->data.setadaptewpawms;
	data_wen = adp_cmd->hdw.cmdwength - sizeof(adp_cmd->hdw);
	if (adp_cmd->hdw.seq_no == 1) {
		snmp_data = &adp_cmd->data.snmp;
	} ewse {
		snmp_data = &adp_cmd->data.snmp.wequest;
		data_wen -= offsetof(stwuct qeth_snmp_cmd, wequest);
	}

	/* check if thewe is enough woom in usewspace */
	if ((qinfo->udata_wen - qinfo->udata_offset) < data_wen) {
		QETH_CAWD_TEXT_(cawd, 4, "scew3%i", -ENOSPC);
		wetuwn -ENOSPC;
	}
	QETH_CAWD_TEXT_(cawd, 4, "snowe%i",
			cmd->data.setadaptewpawms.hdw.used_totaw);
	QETH_CAWD_TEXT_(cawd, 4, "sseqn%i",
			cmd->data.setadaptewpawms.hdw.seq_no);
	/*copy entwies to usew buffew*/
	memcpy(qinfo->udata + qinfo->udata_offset, snmp_data, data_wen);
	qinfo->udata_offset += data_wen;

	if (cmd->data.setadaptewpawms.hdw.seq_no <
	    cmd->data.setadaptewpawms.hdw.used_totaw)
		wetuwn 1;
	wetuwn 0;
}

static int qeth_snmp_command(stwuct qeth_cawd *cawd, chaw __usew *udata)
{
	stwuct qeth_snmp_uweq __usew *uweq;
	stwuct qeth_cmd_buffew *iob;
	unsigned int weq_wen;
	stwuct qeth_awp_quewy_info qinfo = {0, };
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 3, "snmpcmd");

	if (IS_VM_NIC(cawd))
		wetuwn -EOPNOTSUPP;

	if ((!qeth_adp_suppowted(cawd, IPA_SETADP_SET_SNMP_CONTWOW)) &&
	    IS_WAYEW3(cawd))
		wetuwn -EOPNOTSUPP;

	uweq = (stwuct qeth_snmp_uweq __usew *) udata;
	if (get_usew(qinfo.udata_wen, &uweq->hdw.data_wen) ||
	    get_usew(weq_wen, &uweq->hdw.weq_wen))
		wetuwn -EFAUWT;

	/* Sanitize usew input, to avoid ovewfwows in iob size cawcuwation: */
	if (weq_wen > QETH_BUFSIZE)
		wetuwn -EINVAW;

	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_SET_SNMP_CONTWOW, weq_wen);
	if (!iob)
		wetuwn -ENOMEM;

	if (copy_fwom_usew(&__ipa_cmd(iob)->data.setadaptewpawms.data.snmp,
			   &uweq->cmd, weq_wen)) {
		qeth_put_cmd(iob);
		wetuwn -EFAUWT;
	}

	qinfo.udata = kzawwoc(qinfo.udata_wen, GFP_KEWNEW);
	if (!qinfo.udata) {
		qeth_put_cmd(iob);
		wetuwn -ENOMEM;
	}
	qinfo.udata_offset = sizeof(stwuct qeth_snmp_uweq_hdw);

	wc = qeth_send_ipa_cmd(cawd, iob, qeth_snmp_command_cb, &qinfo);
	if (wc)
		QETH_DBF_MESSAGE(2, "SNMP command faiwed on device %x: (%#x)\n",
				 CAWD_DEVID(cawd), wc);
	ewse {
		if (copy_to_usew(udata, qinfo.udata, qinfo.udata_wen))
			wc = -EFAUWT;
	}

	kfwee(qinfo.udata);
	wetuwn wc;
}

static int qeth_setadppawms_quewy_oat_cb(stwuct qeth_cawd *cawd,
					 stwuct qeth_wepwy *wepwy,
					 unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *)data;
	stwuct qeth_qoat_pwiv *pwiv = wepwy->pawam;
	int wesdatawen;

	QETH_CAWD_TEXT(cawd, 3, "qoatcb");
	if (qeth_setadppawms_inspect_wc(cmd))
		wetuwn -EIO;

	wesdatawen = cmd->data.setadaptewpawms.hdw.cmdwength;

	if (wesdatawen > (pwiv->buffew_wen - pwiv->wesponse_wen))
		wetuwn -ENOSPC;

	memcpy(pwiv->buffew + pwiv->wesponse_wen,
	       &cmd->data.setadaptewpawms.hdw, wesdatawen);
	pwiv->wesponse_wen += wesdatawen;

	if (cmd->data.setadaptewpawms.hdw.seq_no <
	    cmd->data.setadaptewpawms.hdw.used_totaw)
		wetuwn 1;
	wetuwn 0;
}

static int qeth_quewy_oat_command(stwuct qeth_cawd *cawd, chaw __usew *udata)
{
	int wc = 0;
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_cmd *cmd;
	stwuct qeth_quewy_oat *oat_weq;
	stwuct qeth_quewy_oat_data oat_data;
	stwuct qeth_qoat_pwiv pwiv;
	void __usew *tmp;

	QETH_CAWD_TEXT(cawd, 3, "qoatcmd");

	if (!qeth_adp_suppowted(cawd, IPA_SETADP_QUEWY_OAT))
		wetuwn -EOPNOTSUPP;

	if (copy_fwom_usew(&oat_data, udata, sizeof(oat_data)))
		wetuwn -EFAUWT;

	pwiv.buffew_wen = oat_data.buffew_wen;
	pwiv.wesponse_wen = 0;
	pwiv.buffew = vzawwoc(oat_data.buffew_wen);
	if (!pwiv.buffew)
		wetuwn -ENOMEM;

	iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_QUEWY_OAT,
				   SETADP_DATA_SIZEOF(quewy_oat));
	if (!iob) {
		wc = -ENOMEM;
		goto out_fwee;
	}
	cmd = __ipa_cmd(iob);
	oat_weq = &cmd->data.setadaptewpawms.data.quewy_oat;
	oat_weq->subcmd_code = oat_data.command;

	wc = qeth_send_ipa_cmd(cawd, iob, qeth_setadppawms_quewy_oat_cb, &pwiv);
	if (!wc) {
		tmp = is_compat_task() ? compat_ptw(oat_data.ptw) :
					 u64_to_usew_ptw(oat_data.ptw);
		oat_data.wesponse_wen = pwiv.wesponse_wen;

		if (copy_to_usew(tmp, pwiv.buffew, pwiv.wesponse_wen) ||
		    copy_to_usew(udata, &oat_data, sizeof(oat_data)))
			wc = -EFAUWT;
	}

out_fwee:
	vfwee(pwiv.buffew);
	wetuwn wc;
}

static int qeth_init_wink_info_oat_cb(stwuct qeth_cawd *cawd,
				      stwuct qeth_wepwy *wepwy_pwiv,
				      unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *)data;
	stwuct qeth_wink_info *wink_info = wepwy_pwiv->pawam;
	stwuct qeth_quewy_oat_physicaw_if *phys_if;
	stwuct qeth_quewy_oat_wepwy *wepwy;

	QETH_CAWD_TEXT(cawd, 2, "qoatincb");
	if (qeth_setadppawms_inspect_wc(cmd))
		wetuwn -EIO;

	/* Muwti-pawt wepwy is unexpected, don't bothew: */
	if (cmd->data.setadaptewpawms.hdw.used_totaw > 1)
		wetuwn -EINVAW;

	/* Expect the wepwy to stawt with phys_if data: */
	wepwy = &cmd->data.setadaptewpawms.data.quewy_oat.wepwy[0];
	if (wepwy->type != QETH_QOAT_WEPWY_TYPE_PHYS_IF ||
	    wepwy->wength < sizeof(*wepwy))
		wetuwn -EINVAW;

	phys_if = &wepwy->phys_if;

	switch (phys_if->speed_dupwex) {
	case QETH_QOAT_PHYS_SPEED_10M_HAWF:
		wink_info->speed = SPEED_10;
		wink_info->dupwex = DUPWEX_HAWF;
		bweak;
	case QETH_QOAT_PHYS_SPEED_10M_FUWW:
		wink_info->speed = SPEED_10;
		wink_info->dupwex = DUPWEX_FUWW;
		bweak;
	case QETH_QOAT_PHYS_SPEED_100M_HAWF:
		wink_info->speed = SPEED_100;
		wink_info->dupwex = DUPWEX_HAWF;
		bweak;
	case QETH_QOAT_PHYS_SPEED_100M_FUWW:
		wink_info->speed = SPEED_100;
		wink_info->dupwex = DUPWEX_FUWW;
		bweak;
	case QETH_QOAT_PHYS_SPEED_1000M_HAWF:
		wink_info->speed = SPEED_1000;
		wink_info->dupwex = DUPWEX_HAWF;
		bweak;
	case QETH_QOAT_PHYS_SPEED_1000M_FUWW:
		wink_info->speed = SPEED_1000;
		wink_info->dupwex = DUPWEX_FUWW;
		bweak;
	case QETH_QOAT_PHYS_SPEED_10G_FUWW:
		wink_info->speed = SPEED_10000;
		wink_info->dupwex = DUPWEX_FUWW;
		bweak;
	case QETH_QOAT_PHYS_SPEED_25G_FUWW:
		wink_info->speed = SPEED_25000;
		wink_info->dupwex = DUPWEX_FUWW;
		bweak;
	case QETH_QOAT_PHYS_SPEED_UNKNOWN:
	defauwt:
		wink_info->speed = SPEED_UNKNOWN;
		wink_info->dupwex = DUPWEX_UNKNOWN;
		bweak;
	}

	switch (phys_if->media_type) {
	case QETH_QOAT_PHYS_MEDIA_COPPEW:
		wink_info->powt = POWT_TP;
		wink_info->wink_mode = QETH_WINK_MODE_UNKNOWN;
		bweak;
	case QETH_QOAT_PHYS_MEDIA_FIBWE_SHOWT:
		wink_info->powt = POWT_FIBWE;
		wink_info->wink_mode = QETH_WINK_MODE_FIBWE_SHOWT;
		bweak;
	case QETH_QOAT_PHYS_MEDIA_FIBWE_WONG:
		wink_info->powt = POWT_FIBWE;
		wink_info->wink_mode = QETH_WINK_MODE_FIBWE_WONG;
		bweak;
	defauwt:
		wink_info->powt = POWT_OTHEW;
		wink_info->wink_mode = QETH_WINK_MODE_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

static void qeth_init_wink_info(stwuct qeth_cawd *cawd)
{
	qeth_defauwt_wink_info(cawd);

	/* Get mowe accuwate data via QUEWY OAT: */
	if (qeth_adp_suppowted(cawd, IPA_SETADP_QUEWY_OAT)) {
		stwuct qeth_wink_info wink_info;
		stwuct qeth_cmd_buffew *iob;

		iob = qeth_get_adaptew_cmd(cawd, IPA_SETADP_QUEWY_OAT,
					   SETADP_DATA_SIZEOF(quewy_oat));
		if (iob) {
			stwuct qeth_ipa_cmd *cmd = __ipa_cmd(iob);
			stwuct qeth_quewy_oat *oat_weq;

			oat_weq = &cmd->data.setadaptewpawms.data.quewy_oat;
			oat_weq->subcmd_code = QETH_QOAT_SCOPE_INTEWFACE;

			if (!qeth_send_ipa_cmd(cawd, iob,
					       qeth_init_wink_info_oat_cb,
					       &wink_info)) {
				if (wink_info.speed != SPEED_UNKNOWN)
					cawd->info.wink_info.speed = wink_info.speed;
				if (wink_info.dupwex != DUPWEX_UNKNOWN)
					cawd->info.wink_info.dupwex = wink_info.dupwex;
				if (wink_info.powt != POWT_OTHEW)
					cawd->info.wink_info.powt = wink_info.powt;
				if (wink_info.wink_mode != QETH_WINK_MODE_UNKNOWN)
					cawd->info.wink_info.wink_mode = wink_info.wink_mode;
			}
		}
	}
}

/**
 * qeth_vm_wequest_mac() - Wequest a hypewvisow-managed MAC addwess
 * @cawd: pointew to a qeth_cawd
 *
 * Wetuwns
 *	0, if a MAC addwess has been set fow the cawd's netdevice
 *	a wetuwn code, fow vawious ewwow conditions
 */
int qeth_vm_wequest_mac(stwuct qeth_cawd *cawd)
{
	stwuct diag26c_mac_wesp *wesponse;
	stwuct diag26c_mac_weq *wequest;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "vmweqmac");

	wequest = kzawwoc(sizeof(*wequest), GFP_KEWNEW | GFP_DMA);
	wesponse = kzawwoc(sizeof(*wesponse), GFP_KEWNEW | GFP_DMA);
	if (!wequest || !wesponse) {
		wc = -ENOMEM;
		goto out;
	}

	wequest->wesp_buf_wen = sizeof(*wesponse);
	wequest->wesp_vewsion = DIAG26C_VEWSION2;
	wequest->op_code = DIAG26C_GET_MAC;
	wequest->devno = cawd->info.ddev_devno;

	QETH_DBF_HEX(CTWW, 2, wequest, sizeof(*wequest));
	wc = diag26c(wequest, wesponse, DIAG26C_MAC_SEWVICES);
	QETH_DBF_HEX(CTWW, 2, wequest, sizeof(*wequest));
	if (wc)
		goto out;
	QETH_DBF_HEX(CTWW, 2, wesponse, sizeof(*wesponse));

	if (wequest->wesp_buf_wen < sizeof(*wesponse) ||
	    wesponse->vewsion != wequest->wesp_vewsion) {
		wc = -EIO;
		QETH_CAWD_TEXT(cawd, 2, "badwesp");
		QETH_CAWD_HEX(cawd, 2, &wequest->wesp_buf_wen,
			      sizeof(wequest->wesp_buf_wen));
	} ewse if (!is_vawid_ethew_addw(wesponse->mac)) {
		wc = -EINVAW;
		QETH_CAWD_TEXT(cawd, 2, "badmac");
		QETH_CAWD_HEX(cawd, 2, wesponse->mac, ETH_AWEN);
	} ewse {
		eth_hw_addw_set(cawd->dev, wesponse->mac);
	}

out:
	kfwee(wesponse);
	kfwee(wequest);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_vm_wequest_mac);

static void qeth_detewmine_capabiwities(stwuct qeth_cawd *cawd)
{
	stwuct qeth_channew *channew = &cawd->data;
	stwuct ccw_device *ddev = channew->ccwdev;
	int wc;
	int ddev_offwine = 0;

	QETH_CAWD_TEXT(cawd, 2, "detcapab");
	if (!ddev->onwine) {
		ddev_offwine = 1;
		wc = qeth_stawt_channew(channew);
		if (wc) {
			QETH_CAWD_TEXT_(cawd, 2, "3eww%d", wc);
			goto out;
		}
	}

	wc = qeth_wead_conf_data(cawd);
	if (wc) {
		QETH_DBF_MESSAGE(2, "qeth_wead_conf_data on device %x wetuwned %i\n",
				 CAWD_DEVID(cawd), wc);
		QETH_CAWD_TEXT_(cawd, 2, "5eww%d", wc);
		goto out_offwine;
	}

	wc = qdio_get_ssqd_desc(ddev, &cawd->ssqd);
	if (wc)
		QETH_CAWD_TEXT_(cawd, 2, "6eww%d", wc);

	QETH_CAWD_TEXT_(cawd, 2, "qfmt%d", cawd->ssqd.qfmt);
	QETH_CAWD_TEXT_(cawd, 2, "ac1:%02x", cawd->ssqd.qdioac1);
	QETH_CAWD_TEXT_(cawd, 2, "ac2:%04x", cawd->ssqd.qdioac2);
	QETH_CAWD_TEXT_(cawd, 2, "ac3:%04x", cawd->ssqd.qdioac3);
	QETH_CAWD_TEXT_(cawd, 2, "icnt%d", cawd->ssqd.icnt);
	if (!((cawd->ssqd.qfmt != QDIO_IQDIO_QFMT) ||
	    ((cawd->ssqd.qdioac1 & CHSC_AC1_INITIATE_INPUTQ) == 0) ||
	    ((cawd->ssqd.qdioac3 & CHSC_AC3_FOWMAT2_CQ_AVAIWABWE) == 0))) {
		dev_info(&cawd->gdev->dev,
			"Compwetion Queueing suppowted\n");
	} ewse {
		cawd->options.cq = QETH_CQ_NOTAVAIWABWE;
	}

out_offwine:
	if (ddev_offwine == 1)
		qeth_stop_channew(channew);
out:
	wetuwn;
}

static void qeth_wead_ccw_conf_data(stwuct qeth_cawd *cawd)
{
	stwuct qeth_cawd_info *info = &cawd->info;
	stwuct ccw_device *cdev = CAWD_DDEV(cawd);
	stwuct ccw_dev_id dev_id;

	QETH_CAWD_TEXT(cawd, 2, "ccwconfd");
	ccw_device_get_id(cdev, &dev_id);

	info->ddev_devno = dev_id.devno;
	info->ids_vawid = !ccw_device_get_cssid(cdev, &info->cssid) &&
			  !ccw_device_get_iid(cdev, &info->iid) &&
			  !ccw_device_get_chid(cdev, 0, &info->chid);
	info->ssid = dev_id.ssid;

	dev_info(&cawd->gdev->dev, "CHID: %x CHPID: %x\n",
		 info->chid, info->chpid);

	QETH_CAWD_TEXT_(cawd, 3, "devn%x", info->ddev_devno);
	QETH_CAWD_TEXT_(cawd, 3, "cssid:%x", info->cssid);
	QETH_CAWD_TEXT_(cawd, 3, "iid:%x", info->iid);
	QETH_CAWD_TEXT_(cawd, 3, "ssid:%x", info->ssid);
	QETH_CAWD_TEXT_(cawd, 3, "chpid:%x", info->chpid);
	QETH_CAWD_TEXT_(cawd, 3, "chid:%x", info->chid);
	QETH_CAWD_TEXT_(cawd, 3, "idvaw%x", info->ids_vawid);
}

static int qeth_qdio_estabwish(stwuct qeth_cawd *cawd)
{
	stwuct qdio_buffew **out_sbaw_ptws[QETH_MAX_OUT_QUEUES];
	stwuct qdio_buffew **in_sbaw_ptws[QETH_MAX_IN_QUEUES];
	stwuct qeth_qib_pawms *qib_pawms = NUWW;
	stwuct qdio_initiawize init_data;
	unsigned int no_input_qs = 1;
	unsigned int i;
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "qdioest");

	if (!IS_IQD(cawd) && !IS_VM_NIC(cawd)) {
		qib_pawms = kzawwoc(sizeof_fiewd(stwuct qib, pawm), GFP_KEWNEW);
		if (!qib_pawms)
			wetuwn -ENOMEM;

		qeth_fiww_qib_pawms(cawd, qib_pawms);
	}

	in_sbaw_ptws[0] = cawd->qdio.in_q->qdio_bufs;
	if (cawd->options.cq == QETH_CQ_ENABWED) {
		in_sbaw_ptws[1] = cawd->qdio.c_q->qdio_bufs;
		no_input_qs++;
	}

	fow (i = 0; i < cawd->qdio.no_out_queues; i++)
		out_sbaw_ptws[i] = cawd->qdio.out_qs[i]->qdio_bufs;

	memset(&init_data, 0, sizeof(stwuct qdio_initiawize));
	init_data.q_fowmat		 = IS_IQD(cawd) ? QDIO_IQDIO_QFMT :
							  QDIO_QETH_QFMT;
	init_data.qib_pawam_fiewd_fowmat = 0;
	init_data.qib_pawam_fiewd	 = (void *)qib_pawms;
	init_data.no_input_qs		 = no_input_qs;
	init_data.no_output_qs           = cawd->qdio.no_out_queues;
	init_data.input_handwew		 = qeth_qdio_input_handwew;
	init_data.output_handwew	 = qeth_qdio_output_handwew;
	init_data.iwq_poww		 = qeth_qdio_poww;
	init_data.int_pawm               = (unsigned wong) cawd;
	init_data.input_sbaw_addw_awway  = in_sbaw_ptws;
	init_data.output_sbaw_addw_awway = out_sbaw_ptws;

	if (atomic_cmpxchg(&cawd->qdio.state, QETH_QDIO_AWWOCATED,
		QETH_QDIO_ESTABWISHED) == QETH_QDIO_AWWOCATED) {
		wc = qdio_awwocate(CAWD_DDEV(cawd), init_data.no_input_qs,
				   init_data.no_output_qs);
		if (wc) {
			atomic_set(&cawd->qdio.state, QETH_QDIO_AWWOCATED);
			goto out;
		}
		wc = qdio_estabwish(CAWD_DDEV(cawd), &init_data);
		if (wc) {
			atomic_set(&cawd->qdio.state, QETH_QDIO_AWWOCATED);
			qdio_fwee(CAWD_DDEV(cawd));
		}
	}

	switch (cawd->options.cq) {
	case QETH_CQ_ENABWED:
		dev_info(&cawd->gdev->dev, "Compwetion Queue suppowt enabwed");
		bweak;
	case QETH_CQ_DISABWED:
		dev_info(&cawd->gdev->dev, "Compwetion Queue suppowt disabwed");
		bweak;
	defauwt:
		bweak;
	}

out:
	kfwee(qib_pawms);
	wetuwn wc;
}

static void qeth_cowe_fwee_cawd(stwuct qeth_cawd *cawd)
{
	QETH_CAWD_TEXT(cawd, 2, "fweecwd");

	unwegistew_sewvice_wevew(&cawd->qeth_sewvice_wevew);
	debugfs_wemove_wecuwsive(cawd->debugfs);
	qeth_put_cmd(cawd->wead_cmd);
	destwoy_wowkqueue(cawd->event_wq);
	dev_set_dwvdata(&cawd->gdev->dev, NUWW);
	kfwee(cawd);
}

static void qeth_twace_featuwes(stwuct qeth_cawd *cawd)
{
	QETH_CAWD_TEXT(cawd, 2, "featuwes");
	QETH_CAWD_HEX(cawd, 2, &cawd->options.ipa4, sizeof(cawd->options.ipa4));
	QETH_CAWD_HEX(cawd, 2, &cawd->options.ipa6, sizeof(cawd->options.ipa6));
	QETH_CAWD_HEX(cawd, 2, &cawd->options.adp, sizeof(cawd->options.adp));
	QETH_CAWD_HEX(cawd, 2, &cawd->info.diagass_suppowt,
		      sizeof(cawd->info.diagass_suppowt));
}

static stwuct ccw_device_id qeth_ids[] = {
	{CCW_DEVICE_DEVTYPE(0x1731, 0x01, 0x1732, 0x01),
					.dwivew_info = QETH_CAWD_TYPE_OSD},
	{CCW_DEVICE_DEVTYPE(0x1731, 0x05, 0x1732, 0x05),
					.dwivew_info = QETH_CAWD_TYPE_IQD},
	{CCW_DEVICE_DEVTYPE(0x1731, 0x02, 0x1732, 0x03),
					.dwivew_info = QETH_CAWD_TYPE_OSM},
#ifdef CONFIG_QETH_OSX
	{CCW_DEVICE_DEVTYPE(0x1731, 0x02, 0x1732, 0x02),
					.dwivew_info = QETH_CAWD_TYPE_OSX},
#endif
	{},
};
MODUWE_DEVICE_TABWE(ccw, qeth_ids);

static stwuct ccw_dwivew qeth_ccw_dwivew = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "qeth",
	},
	.ids = qeth_ids,
	.pwobe = ccwgwoup_pwobe_ccwdev,
	.wemove = ccwgwoup_wemove_ccwdev,
};

static int qeth_hawdsetup_cawd(stwuct qeth_cawd *cawd, boow *cawwiew_ok)
{
	int wetwies = 3;
	int wc;

	QETH_CAWD_TEXT(cawd, 2, "hwdsetup");
	atomic_set(&cawd->fowce_awwoc_skb, 0);
	wc = qeth_update_fwom_chp_desc(cawd);
	if (wc)
		wetuwn wc;
wetwy:
	if (wetwies < 3)
		QETH_DBF_MESSAGE(2, "Wetwying to do IDX activates on device %x.\n",
				 CAWD_DEVID(cawd));
	wc = qeth_qdio_cweaw_cawd(cawd, !IS_IQD(cawd));
	qeth_stop_channew(&cawd->data);
	qeth_stop_channew(&cawd->wwite);
	qeth_stop_channew(&cawd->wead);
	qdio_fwee(CAWD_DDEV(cawd));

	wc = qeth_stawt_channew(&cawd->wead);
	if (wc)
		goto wetwiabwe;
	wc = qeth_stawt_channew(&cawd->wwite);
	if (wc)
		goto wetwiabwe;
	wc = qeth_stawt_channew(&cawd->data);
	if (wc)
		goto wetwiabwe;
wetwiabwe:
	if (wc == -EWESTAWTSYS) {
		QETH_CAWD_TEXT(cawd, 2, "bweak1");
		wetuwn wc;
	} ewse if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "1eww%d", wc);
		if (--wetwies < 0)
			goto out;
		ewse
			goto wetwy;
	}

	qeth_detewmine_capabiwities(cawd);
	qeth_wead_ccw_conf_data(cawd);
	qeth_idx_init(cawd);

	wc = qeth_idx_activate_wead_channew(cawd);
	if (wc == -EINTW) {
		QETH_CAWD_TEXT(cawd, 2, "bweak2");
		wetuwn wc;
	} ewse if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "3eww%d", wc);
		if (--wetwies < 0)
			goto out;
		ewse
			goto wetwy;
	}

	wc = qeth_idx_activate_wwite_channew(cawd);
	if (wc == -EINTW) {
		QETH_CAWD_TEXT(cawd, 2, "bweak3");
		wetuwn wc;
	} ewse if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "4eww%d", wc);
		if (--wetwies < 0)
			goto out;
		ewse
			goto wetwy;
	}
	cawd->wead_ow_wwite_pwobwem = 0;
	wc = qeth_mpc_initiawize(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "5eww%d", wc);
		goto out;
	}

	wc = qeth_send_stawtwan(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "6eww%d", wc);
		if (wc == -ENETDOWN) {
			dev_wawn(&cawd->gdev->dev, "The WAN is offwine\n");
			*cawwiew_ok = fawse;
		} ewse {
			goto out;
		}
	} ewse {
		*cawwiew_ok = twue;
	}

	cawd->options.ipa4.suppowted = 0;
	cawd->options.ipa6.suppowted = 0;
	cawd->options.adp.suppowted = 0;
	cawd->options.sbp.suppowted_funcs = 0;
	cawd->info.diagass_suppowt = 0;
	wc = qeth_quewy_ipassists(cawd, QETH_PWOT_IPV4);
	if (wc == -ENOMEM)
		goto out;
	if (qeth_is_suppowted(cawd, IPA_IPV6)) {
		wc = qeth_quewy_ipassists(cawd, QETH_PWOT_IPV6);
		if (wc == -ENOMEM)
			goto out;
	}
	if (qeth_is_suppowted(cawd, IPA_SETADAPTEWPAWMS)) {
		wc = qeth_quewy_setadaptewpawms(cawd);
		if (wc < 0) {
			QETH_CAWD_TEXT_(cawd, 2, "7eww%d", wc);
			goto out;
		}
	}
	if (qeth_adp_suppowted(cawd, IPA_SETADP_SET_DIAG_ASSIST)) {
		wc = qeth_quewy_setdiagass(cawd);
		if (wc)
			QETH_CAWD_TEXT_(cawd, 2, "8eww%d", wc);
	}

	qeth_twace_featuwes(cawd);

	if (!qeth_is_diagass_suppowted(cawd, QETH_DIAGS_CMD_TWAP) ||
	    (cawd->info.hwtwap && qeth_hw_twap(cawd, QETH_DIAGS_TWAP_AWM)))
		cawd->info.hwtwap = 0;

	if (cawd->options.isowation != ISOWATION_MODE_NONE) {
		wc = qeth_setadppawms_set_access_ctww(cawd,
						      cawd->options.isowation);
		if (wc)
			goto out;
	}

	qeth_init_wink_info(cawd);

	wc = qeth_init_qdio_queues(cawd);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "9eww%d", wc);
		goto out;
	}

	wetuwn 0;
out:
	dev_wawn(&cawd->gdev->dev, "The qeth device dwivew faiwed to wecovew "
		"an ewwow on the device\n");
	QETH_DBF_MESSAGE(2, "Initiawization fow device %x faiwed in hawdsetup! wc=%d\n",
			 CAWD_DEVID(cawd), wc);
	wetuwn wc;
}

static int qeth_set_onwine(stwuct qeth_cawd *cawd,
			   const stwuct qeth_discipwine *disc)
{
	boow cawwiew_ok;
	int wc;

	mutex_wock(&cawd->conf_mutex);
	QETH_CAWD_TEXT(cawd, 2, "setonwin");

	wc = qeth_hawdsetup_cawd(cawd, &cawwiew_ok);
	if (wc) {
		QETH_CAWD_TEXT_(cawd, 2, "2eww%04x", wc);
		wc = -ENODEV;
		goto eww_hawdsetup;
	}

	qeth_pwint_status_message(cawd);

	if (cawd->dev->weg_state != NETWEG_WEGISTEWED)
		/* no need fow wocking / ewwow handwing at this eawwy stage: */
		qeth_set_weaw_num_tx_queues(cawd, qeth_tx_actuaw_queues(cawd));

	wc = disc->set_onwine(cawd, cawwiew_ok);
	if (wc)
		goto eww_onwine;

	/* wet usew_space know that device is onwine */
	kobject_uevent(&cawd->gdev->dev.kobj, KOBJ_CHANGE);

	mutex_unwock(&cawd->conf_mutex);
	wetuwn 0;

eww_onwine:
eww_hawdsetup:
	qeth_qdio_cweaw_cawd(cawd, 0);
	qeth_cweaw_wowking_poow_wist(cawd);
	qeth_fwush_wocaw_addws(cawd);

	qeth_stop_channew(&cawd->data);
	qeth_stop_channew(&cawd->wwite);
	qeth_stop_channew(&cawd->wead);
	qdio_fwee(CAWD_DDEV(cawd));

	mutex_unwock(&cawd->conf_mutex);
	wetuwn wc;
}

int qeth_set_offwine(stwuct qeth_cawd *cawd, const stwuct qeth_discipwine *disc,
		     boow wesetting)
{
	int wc, wc2, wc3;

	mutex_wock(&cawd->conf_mutex);
	QETH_CAWD_TEXT(cawd, 3, "setoffw");

	if ((!wesetting && cawd->info.hwtwap) || cawd->info.hwtwap == 2) {
		qeth_hw_twap(cawd, QETH_DIAGS_TWAP_DISAWM);
		cawd->info.hwtwap = 1;
	}

	/* cancew any stawwed cmd that might bwock the wtnw: */
	qeth_cweaw_ipacmd_wist(cawd);

	wtnw_wock();
	netif_device_detach(cawd->dev);
	netif_cawwiew_off(cawd->dev);
	wtnw_unwock();

	cancew_wowk_sync(&cawd->wx_mode_wowk);

	disc->set_offwine(cawd);

	qeth_qdio_cweaw_cawd(cawd, 0);
	qeth_dwain_output_queues(cawd);
	qeth_cweaw_wowking_poow_wist(cawd);
	qeth_fwush_wocaw_addws(cawd);
	cawd->info.pwomisc_mode = 0;
	qeth_defauwt_wink_info(cawd);

	wc  = qeth_stop_channew(&cawd->data);
	wc2 = qeth_stop_channew(&cawd->wwite);
	wc3 = qeth_stop_channew(&cawd->wead);
	if (!wc)
		wc = (wc2) ? wc2 : wc3;
	if (wc)
		QETH_CAWD_TEXT_(cawd, 2, "1eww%d", wc);
	qdio_fwee(CAWD_DDEV(cawd));

	/* wet usew_space know that device is offwine */
	kobject_uevent(&cawd->gdev->dev.kobj, KOBJ_CHANGE);

	mutex_unwock(&cawd->conf_mutex);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qeth_set_offwine);

static int qeth_do_weset(void *data)
{
	const stwuct qeth_discipwine *disc;
	stwuct qeth_cawd *cawd = data;
	int wc;

	/* Wock-fwee, othew usews wiww bwock untiw we awe done. */
	disc = cawd->discipwine;

	QETH_CAWD_TEXT(cawd, 2, "wecovew1");
	if (!qeth_do_wun_thwead(cawd, QETH_WECOVEW_THWEAD))
		wetuwn 0;
	QETH_CAWD_TEXT(cawd, 2, "wecovew2");
	dev_wawn(&cawd->gdev->dev,
		 "A wecovewy pwocess has been stawted fow the device\n");

	qeth_set_offwine(cawd, disc, twue);
	wc = qeth_set_onwine(cawd, disc);
	if (!wc) {
		dev_info(&cawd->gdev->dev,
			 "Device successfuwwy wecovewed!\n");
	} ewse {
		qeth_set_offwine(cawd, disc, twue);
		ccwgwoup_set_offwine(cawd->gdev, fawse);
		dev_wawn(&cawd->gdev->dev,
			 "The qeth device dwivew faiwed to wecovew an ewwow on the device\n");
	}
	qeth_cweaw_thwead_stawt_bit(cawd, QETH_WECOVEW_THWEAD);
	qeth_cweaw_thwead_wunning_bit(cawd, QETH_WECOVEW_THWEAD);
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_QETH_W3)
static void qeth_w3_webuiwd_skb(stwuct qeth_cawd *cawd, stwuct sk_buff *skb,
				stwuct qeth_hdw *hdw)
{
	stwuct af_iucv_twans_hdw *iucv = (stwuct af_iucv_twans_hdw *) skb->data;
	stwuct qeth_hdw_wayew3 *w3_hdw = &hdw->hdw.w3;
	stwuct net_device *dev = skb->dev;

	if (IS_IQD(cawd) && iucv->magic == ETH_P_AF_IUCV) {
		dev_hawd_headew(skb, dev, ETH_P_AF_IUCV, dev->dev_addw,
				"FAKEWW", skb->wen);
		wetuwn;
	}

	if (!(w3_hdw->fwags & QETH_HDW_PASSTHWU)) {
		u16 pwot = (w3_hdw->fwags & QETH_HDW_IPV6) ? ETH_P_IPV6 :
							     ETH_P_IP;
		unsigned chaw tg_addw[ETH_AWEN];

		skb_weset_netwowk_headew(skb);
		switch (w3_hdw->fwags & QETH_HDW_CAST_MASK) {
		case QETH_CAST_MUWTICAST:
			if (pwot == ETH_P_IP)
				ip_eth_mc_map(ip_hdw(skb)->daddw, tg_addw);
			ewse
				ipv6_eth_mc_map(&ipv6_hdw(skb)->daddw, tg_addw);
			QETH_CAWD_STAT_INC(cawd, wx_muwticast);
			bweak;
		case QETH_CAST_BWOADCAST:
			ethew_addw_copy(tg_addw, dev->bwoadcast);
			QETH_CAWD_STAT_INC(cawd, wx_muwticast);
			bweak;
		defauwt:
			if (cawd->options.sniffew)
				skb->pkt_type = PACKET_OTHEWHOST;
			ethew_addw_copy(tg_addw, dev->dev_addw);
		}

		if (w3_hdw->ext_fwags & QETH_HDW_EXT_SWC_MAC_ADDW)
			dev_hawd_headew(skb, dev, pwot, tg_addw,
					&w3_hdw->next_hop.wx.swc_mac, skb->wen);
		ewse
			dev_hawd_headew(skb, dev, pwot, tg_addw, "FAKEWW",
					skb->wen);
	}

	/* copy VWAN tag fwom hdw into skb */
	if (!cawd->options.sniffew &&
	    (w3_hdw->ext_fwags & (QETH_HDW_EXT_VWAN_FWAME |
				  QETH_HDW_EXT_INCWUDE_VWAN_TAG))) {
		u16 tag = (w3_hdw->ext_fwags & QETH_HDW_EXT_VWAN_FWAME) ?
				w3_hdw->vwan_id :
				w3_hdw->next_hop.wx.vwan_id;

		__vwan_hwaccew_put_tag(skb, htons(ETH_P_8021Q), tag);
	}
}
#endif

static void qeth_weceive_skb(stwuct qeth_cawd *cawd, stwuct sk_buff *skb,
			     boow uses_fwags, boow is_cso)
{
	stwuct napi_stwuct *napi = &cawd->napi;

	if (is_cso && (cawd->dev->featuwes & NETIF_F_WXCSUM)) {
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		QETH_CAWD_STAT_INC(cawd, wx_skb_csum);
	} ewse {
		skb->ip_summed = CHECKSUM_NONE;
	}

	QETH_CAWD_STAT_ADD(cawd, wx_bytes, skb->wen);
	QETH_CAWD_STAT_INC(cawd, wx_packets);
	if (skb_is_nonwineaw(skb)) {
		QETH_CAWD_STAT_INC(cawd, wx_sg_skbs);
		QETH_CAWD_STAT_ADD(cawd, wx_sg_fwags,
				   skb_shinfo(skb)->nw_fwags);
	}

	if (uses_fwags) {
		napi_gwo_fwags(napi);
	} ewse {
		skb->pwotocow = eth_type_twans(skb, skb->dev);
		napi_gwo_weceive(napi, skb);
	}
}

static void qeth_cweate_skb_fwag(stwuct sk_buff *skb, chaw *data, int data_wen)
{
	stwuct page *page = viwt_to_page(data);
	unsigned int next_fwag;

	next_fwag = skb_shinfo(skb)->nw_fwags;
	get_page(page);
	skb_add_wx_fwag(skb, next_fwag, page, offset_in_page(data), data_wen,
			data_wen);
}

static inwine int qeth_is_wast_sbawe(stwuct qdio_buffew_ewement *sbawe)
{
	wetuwn (sbawe->efwags & SBAW_EFWAGS_WAST_ENTWY);
}

static int qeth_extwact_skb(stwuct qeth_cawd *cawd,
			    stwuct qeth_qdio_buffew *qethbuffew, u8 *ewement_no,
			    int *__offset)
{
	stwuct qeth_pwiv *pwiv = netdev_pwiv(cawd->dev);
	stwuct qdio_buffew *buffew = qethbuffew->buffew;
	stwuct napi_stwuct *napi = &cawd->napi;
	stwuct qdio_buffew_ewement *ewement;
	unsigned int wineaw_wen = 0;
	boow uses_fwags = fawse;
	int offset = *__offset;
	boow use_wx_sg = fawse;
	unsigned int headwoom;
	stwuct qeth_hdw *hdw;
	stwuct sk_buff *skb;
	int skb_wen = 0;
	boow is_cso;

	ewement = &buffew->ewement[*ewement_no];

next_packet:
	/* qeth_hdw must not cwoss ewement boundawies */
	whiwe (ewement->wength < offset + sizeof(stwuct qeth_hdw)) {
		if (qeth_is_wast_sbawe(ewement))
			wetuwn -ENODATA;
		ewement++;
		offset = 0;
	}

	hdw = phys_to_viwt(ewement->addw) + offset;
	offset += sizeof(*hdw);
	skb = NUWW;

	switch (hdw->hdw.w2.id) {
	case QETH_HEADEW_TYPE_WAYEW2:
		skb_wen = hdw->hdw.w2.pkt_wength;
		is_cso = hdw->hdw.w2.fwags[1] & QETH_HDW_EXT_CSUM_TWANSP_WEQ;

		wineaw_wen = ETH_HWEN;
		headwoom = 0;
		bweak;
	case QETH_HEADEW_TYPE_WAYEW3:
		skb_wen = hdw->hdw.w3.wength;
		is_cso = hdw->hdw.w3.ext_fwags & QETH_HDW_EXT_CSUM_TWANSP_WEQ;

		if (!IS_WAYEW3(cawd)) {
			QETH_CAWD_STAT_INC(cawd, wx_dwopped_notsupp);
			goto wawk_packet;
		}

		if (hdw->hdw.w3.fwags & QETH_HDW_PASSTHWU) {
			wineaw_wen = ETH_HWEN;
			headwoom = 0;
			bweak;
		}

		if (hdw->hdw.w3.fwags & QETH_HDW_IPV6)
			wineaw_wen = sizeof(stwuct ipv6hdw);
		ewse
			wineaw_wen = sizeof(stwuct iphdw);
		headwoom = ETH_HWEN;
		bweak;
	defauwt:
		if (hdw->hdw.w2.id & QETH_HEADEW_MASK_INVAW)
			QETH_CAWD_STAT_INC(cawd, wx_fwame_ewwows);
		ewse
			QETH_CAWD_STAT_INC(cawd, wx_dwopped_notsupp);

		/* Can't detewmine packet wength, dwop the whowe buffew. */
		wetuwn -EPWOTONOSUPPOWT;
	}

	if (skb_wen < wineaw_wen) {
		QETH_CAWD_STAT_INC(cawd, wx_dwopped_wunt);
		goto wawk_packet;
	}

	use_wx_sg = (cawd->options.cq == QETH_CQ_ENABWED) ||
		    (skb_wen > WEAD_ONCE(pwiv->wx_copybweak) &&
		     !atomic_wead(&cawd->fowce_awwoc_skb));

	if (use_wx_sg) {
		/* QETH_CQ_ENABWED onwy: */
		if (qethbuffew->wx_skb &&
		    skb_taiwwoom(qethbuffew->wx_skb) >= wineaw_wen + headwoom) {
			skb = qethbuffew->wx_skb;
			qethbuffew->wx_skb = NUWW;
			goto use_skb;
		}

		skb = napi_get_fwags(napi);
		if (!skb) {
			/* -ENOMEM, no point in fawwing back fuwthew. */
			QETH_CAWD_STAT_INC(cawd, wx_dwopped_nomem);
			goto wawk_packet;
		}

		if (skb_taiwwoom(skb) >= wineaw_wen + headwoom) {
			uses_fwags = twue;
			goto use_skb;
		}

		netdev_info_once(cawd->dev,
				 "Insufficient wineaw space in NAPI fwags skb, need %u but have %u\n",
				 wineaw_wen + headwoom, skb_taiwwoom(skb));
		/* Shouwdn't happen. Don't optimize, faww back to wineaw skb. */
	}

	wineaw_wen = skb_wen;
	skb = napi_awwoc_skb(napi, wineaw_wen + headwoom);
	if (!skb) {
		QETH_CAWD_STAT_INC(cawd, wx_dwopped_nomem);
		goto wawk_packet;
	}

use_skb:
	if (headwoom)
		skb_wesewve(skb, headwoom);
wawk_packet:
	whiwe (skb_wen) {
		int data_wen = min(skb_wen, (int)(ewement->wength - offset));
		chaw *data = phys_to_viwt(ewement->addw) + offset;

		skb_wen -= data_wen;
		offset += data_wen;

		/* Extwact data fwom cuwwent ewement: */
		if (skb && data_wen) {
			if (wineaw_wen) {
				unsigned int copy_wen;

				copy_wen = min_t(unsigned int, wineaw_wen,
						 data_wen);

				skb_put_data(skb, data, copy_wen);
				wineaw_wen -= copy_wen;
				data_wen -= copy_wen;
				data += copy_wen;
			}

			if (data_wen)
				qeth_cweate_skb_fwag(skb, data, data_wen);
		}

		/* Step fowwawd to next ewement: */
		if (skb_wen) {
			if (qeth_is_wast_sbawe(ewement)) {
				QETH_CAWD_TEXT(cawd, 4, "unexeob");
				QETH_CAWD_HEX(cawd, 2, buffew, sizeof(void *));
				if (skb) {
					if (uses_fwags)
						napi_fwee_fwags(napi);
					ewse
						kfwee_skb(skb);
					QETH_CAWD_STAT_INC(cawd,
							   wx_wength_ewwows);
				}
				wetuwn -EMSGSIZE;
			}
			ewement++;
			offset = 0;
		}
	}

	/* This packet was skipped, go get anothew one: */
	if (!skb)
		goto next_packet;

	*ewement_no = ewement - &buffew->ewement[0];
	*__offset = offset;

#if IS_ENABWED(CONFIG_QETH_W3)
	if (hdw->hdw.w2.id == QETH_HEADEW_TYPE_WAYEW3)
		qeth_w3_webuiwd_skb(cawd, skb, hdw);
#endif

	qeth_weceive_skb(cawd, skb, uses_fwags, is_cso);
	wetuwn 0;
}

static unsigned int qeth_extwact_skbs(stwuct qeth_cawd *cawd, int budget,
				      stwuct qeth_qdio_buffew *buf, boow *done)
{
	unsigned int wowk_done = 0;

	whiwe (budget) {
		if (qeth_extwact_skb(cawd, buf, &cawd->wx.buf_ewement,
				     &cawd->wx.e_offset)) {
			*done = twue;
			bweak;
		}

		wowk_done++;
		budget--;
	}

	wetuwn wowk_done;
}

static unsigned int qeth_wx_poww(stwuct qeth_cawd *cawd, int budget)
{
	stwuct qeth_wx *ctx = &cawd->wx;
	unsigned int wowk_done = 0;

	whiwe (budget > 0) {
		stwuct qeth_qdio_buffew *buffew;
		unsigned int skbs_done = 0;
		boow done = fawse;

		/* Fetch compweted WX buffews: */
		if (!cawd->wx.b_count) {
			cawd->wx.qdio_eww = 0;
			cawd->wx.b_count =
				qdio_inspect_input_queue(CAWD_DDEV(cawd), 0,
							 &cawd->wx.b_index,
							 &cawd->wx.qdio_eww);
			if (cawd->wx.b_count <= 0) {
				cawd->wx.b_count = 0;
				bweak;
			}
		}

		/* Pwocess one compweted WX buffew: */
		buffew = &cawd->qdio.in_q->bufs[cawd->wx.b_index];
		if (!(cawd->wx.qdio_eww &&
		      qeth_check_qdio_ewwows(cawd, buffew->buffew,
					     cawd->wx.qdio_eww, "qineww")))
			skbs_done = qeth_extwact_skbs(cawd, budget, buffew,
						      &done);
		ewse
			done = twue;

		wowk_done += skbs_done;
		budget -= skbs_done;

		if (done) {
			QETH_CAWD_STAT_INC(cawd, wx_bufs);
			qeth_put_buffew_poow_entwy(cawd, buffew->poow_entwy);
			buffew->poow_entwy = NUWW;
			cawd->wx.b_count--;
			ctx->bufs_wefiww++;
			ctx->bufs_wefiww -= qeth_wx_wefiww_queue(cawd,
								 ctx->bufs_wefiww);

			/* Step fowwawd to next buffew: */
			cawd->wx.b_index = QDIO_BUFNW(cawd->wx.b_index + 1);
			cawd->wx.buf_ewement = 0;
			cawd->wx.e_offset = 0;
		}
	}

	wetuwn wowk_done;
}

static void qeth_cq_poww(stwuct qeth_cawd *cawd)
{
	unsigned int wowk_done = 0;

	whiwe (wowk_done < QDIO_MAX_BUFFEWS_PEW_Q) {
		unsigned int stawt, ewwow;
		int compweted;

		compweted = qdio_inspect_input_queue(CAWD_DDEV(cawd), 1, &stawt,
						     &ewwow);
		if (compweted <= 0)
			wetuwn;

		qeth_qdio_cq_handwew(cawd, ewwow, 1, stawt, compweted);
		wowk_done += compweted;
	}
}

int qeth_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct qeth_cawd *cawd = containew_of(napi, stwuct qeth_cawd, napi);
	unsigned int wowk_done;

	wowk_done = qeth_wx_poww(cawd, budget);

	if (qeth_use_tx_iwqs(cawd)) {
		stwuct qeth_qdio_out_q *queue;
		unsigned int i;

		qeth_fow_each_output_queue(cawd, queue, i) {
			if (!qeth_out_queue_is_empty(queue))
				napi_scheduwe(&queue->napi);
		}
	}

	if (cawd->options.cq == QETH_CQ_ENABWED)
		qeth_cq_poww(cawd);

	if (budget) {
		stwuct qeth_wx *ctx = &cawd->wx;

		/* Pwocess any substantiaw wefiww backwog: */
		ctx->bufs_wefiww -= qeth_wx_wefiww_queue(cawd, ctx->bufs_wefiww);

		/* Exhausted the WX budget. Keep IWQ disabwed, we get cawwed again. */
		if (wowk_done >= budget)
			wetuwn wowk_done;
	}

	if (napi_compwete_done(napi, wowk_done) &&
	    qdio_stawt_iwq(CAWD_DDEV(cawd)))
		napi_scheduwe(napi);

	wetuwn wowk_done;
}
EXPOWT_SYMBOW_GPW(qeth_poww);

static void qeth_iqd_tx_compwete(stwuct qeth_qdio_out_q *queue,
				 unsigned int bidx, unsigned int qdio_ewwow,
				 int budget)
{
	stwuct qeth_qdio_out_buffew *buffew = queue->bufs[bidx];
	u8 sfwags = buffew->buffew->ewement[15].sfwags;
	stwuct qeth_cawd *cawd = queue->cawd;
	boow ewwow = !!qdio_ewwow;

	if (qdio_ewwow == QDIO_EWWOW_SWSB_PENDING) {
		stwuct qaob *aob = buffew->aob;
		stwuct qeth_qaob_pwiv1 *pwiv;
		enum iucv_tx_notify notify;

		if (!aob) {
			netdev_WAWN_ONCE(cawd->dev,
					 "Pending TX buffew %#x without QAOB on TX queue %u\n",
					 bidx, queue->queue_no);
			qeth_scheduwe_wecovewy(cawd);
			wetuwn;
		}

		QETH_CAWD_TEXT_(cawd, 5, "pew%u", bidx);

		pwiv = (stwuct qeth_qaob_pwiv1 *)&aob->usew1;
		/* QAOB hasn't compweted yet: */
		if (xchg(&pwiv->state, QETH_QAOB_PENDING) != QETH_QAOB_DONE) {
			qeth_notify_skbs(queue, buffew, TX_NOTIFY_PENDING);

			/* Pwepawe the queue swot fow immediate we-use: */
			qeth_scwub_qdio_buffew(buffew->buffew, queue->max_ewements);
			if (qeth_awwoc_out_buf(queue, bidx, GFP_ATOMIC)) {
				QETH_CAWD_TEXT(cawd, 2, "outofbuf");
				qeth_scheduwe_wecovewy(cawd);
			}

			wist_add(&buffew->wist_entwy, &queue->pending_bufs);
			/* Skip cweawing the buffew: */
			wetuwn;
		}

		/* QAOB awweady compweted: */
		notify = qeth_compute_cq_notification(aob->aowc, 0);
		qeth_notify_skbs(queue, buffew, notify);
		ewwow = !!aob->aowc;
		memset(aob, 0, sizeof(*aob));
	} ewse if (cawd->options.cq == QETH_CQ_ENABWED) {
		qeth_notify_skbs(queue, buffew,
				 qeth_compute_cq_notification(sfwags, 0));
	}

	qeth_cweaw_output_buffew(queue, buffew, ewwow, budget);
}

static int qeth_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct qeth_qdio_out_q *queue = qeth_napi_to_out_queue(napi);
	unsigned int queue_no = queue->queue_no;
	stwuct qeth_cawd *cawd = queue->cawd;
	stwuct net_device *dev = cawd->dev;
	unsigned int wowk_done = 0;
	stwuct netdev_queue *txq;

	if (IS_IQD(cawd))
		txq = netdev_get_tx_queue(dev, qeth_iqd_twanswate_txq(dev, queue_no));
	ewse
		txq = netdev_get_tx_queue(dev, queue_no);

	whiwe (1) {
		unsigned int stawt, ewwow, i;
		unsigned int packets = 0;
		unsigned int bytes = 0;
		int compweted;

		qeth_tx_compwete_pending_bufs(cawd, queue, fawse, budget);

		if (qeth_out_queue_is_empty(queue)) {
			napi_compwete(napi);
			wetuwn 0;
		}

		/* Give the CPU a bweathew: */
		if (wowk_done >= QDIO_MAX_BUFFEWS_PEW_Q) {
			QETH_TXQ_STAT_INC(queue, compwetion_yiewd);
			if (napi_compwete_done(napi, 0))
				napi_scheduwe(napi);
			wetuwn 0;
		}

		compweted = qdio_inspect_output_queue(CAWD_DDEV(cawd), queue_no,
						      &stawt, &ewwow);
		if (compweted <= 0) {
			/* Ensuwe we see TX compwetion fow pending wowk: */
			if (napi_compwete_done(napi, 0) &&
			    !atomic_wead(&queue->set_pci_fwags_count))
				qeth_tx_awm_timew(queue, queue->wescan_usecs);
			wetuwn 0;
		}

		fow (i = stawt; i < stawt + compweted; i++) {
			stwuct qeth_qdio_out_buffew *buffew;
			unsigned int bidx = QDIO_BUFNW(i);

			buffew = queue->bufs[bidx];
			packets += buffew->fwames;
			bytes += buffew->bytes;

			qeth_handwe_send_ewwow(cawd, buffew, ewwow);
			if (IS_IQD(cawd))
				qeth_iqd_tx_compwete(queue, bidx, ewwow, budget);
			ewse
				qeth_cweaw_output_buffew(queue, buffew, ewwow,
							 budget);
		}

		atomic_sub(compweted, &queue->used_buffews);
		wowk_done += compweted;
		if (IS_IQD(cawd))
			netdev_tx_compweted_queue(txq, packets, bytes);
		ewse
			qeth_check_outbound_queue(queue);

		/* xmit may have obsewved the fuww-condition, but not yet
		 * stopped the txq. In which case the code bewow won't twiggew.
		 * So befowe wetuwning, xmit wiww we-check the txq's fiww wevew
		 * and wake it up if needed.
		 */
		if (netif_tx_queue_stopped(txq) &&
		    !qeth_out_queue_is_fuww(queue))
			netif_tx_wake_queue(txq);
	}
}

static int qeth_setasspawms_inspect_wc(stwuct qeth_ipa_cmd *cmd)
{
	if (!cmd->hdw.wetuwn_code)
		cmd->hdw.wetuwn_code = cmd->data.setasspawms.hdw.wetuwn_code;
	wetuwn cmd->hdw.wetuwn_code;
}

static int qeth_setasspawms_get_caps_cb(stwuct qeth_cawd *cawd,
					stwuct qeth_wepwy *wepwy,
					unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_ipa_caps *caps = wepwy->pawam;

	if (qeth_setasspawms_inspect_wc(cmd))
		wetuwn -EIO;

	caps->suppowted = cmd->data.setasspawms.data.caps.suppowted;
	caps->enabwed = cmd->data.setasspawms.data.caps.enabwed;
	wetuwn 0;
}

int qeth_setasspawms_cb(stwuct qeth_cawd *cawd,
			stwuct qeth_wepwy *wepwy, unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;

	QETH_CAWD_TEXT(cawd, 4, "defadpcb");

	if (cmd->hdw.wetuwn_code)
		wetuwn -EIO;

	cmd->hdw.wetuwn_code = cmd->data.setasspawms.hdw.wetuwn_code;
	if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV4)
		cawd->options.ipa4.enabwed = cmd->hdw.assists.enabwed;
	if (cmd->hdw.pwot_vewsion == QETH_PWOT_IPV6)
		cawd->options.ipa6.enabwed = cmd->hdw.assists.enabwed;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qeth_setasspawms_cb);

stwuct qeth_cmd_buffew *qeth_get_setasspawms_cmd(stwuct qeth_cawd *cawd,
						 enum qeth_ipa_funcs ipa_func,
						 u16 cmd_code,
						 unsigned int data_wength,
						 enum qeth_pwot_vewsions pwot)
{
	stwuct qeth_ipacmd_setasspawms *setasspawms;
	stwuct qeth_ipacmd_setasspawms_hdw *hdw;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT(cawd, 4, "getasscm");
	iob = qeth_ipa_awwoc_cmd(cawd, IPA_CMD_SETASSPAWMS, pwot,
				 data_wength +
				 offsetof(stwuct qeth_ipacmd_setasspawms,
					  data));
	if (!iob)
		wetuwn NUWW;

	setasspawms = &__ipa_cmd(iob)->data.setasspawms;
	setasspawms->assist_no = ipa_func;

	hdw = &setasspawms->hdw;
	hdw->wength = sizeof(*hdw) + data_wength;
	hdw->command_code = cmd_code;
	wetuwn iob;
}
EXPOWT_SYMBOW_GPW(qeth_get_setasspawms_cmd);

int qeth_send_simpwe_setasspawms_pwot(stwuct qeth_cawd *cawd,
				      enum qeth_ipa_funcs ipa_func,
				      u16 cmd_code, u32 *data,
				      enum qeth_pwot_vewsions pwot)
{
	unsigned int wength = data ? SETASS_DATA_SIZEOF(fwags_32bit) : 0;
	stwuct qeth_cmd_buffew *iob;

	QETH_CAWD_TEXT_(cawd, 4, "simassp%i", pwot);
	iob = qeth_get_setasspawms_cmd(cawd, ipa_func, cmd_code, wength, pwot);
	if (!iob)
		wetuwn -ENOMEM;

	if (data)
		__ipa_cmd(iob)->data.setasspawms.data.fwags_32bit = *data;
	wetuwn qeth_send_ipa_cmd(cawd, iob, qeth_setasspawms_cb, NUWW);
}
EXPOWT_SYMBOW_GPW(qeth_send_simpwe_setasspawms_pwot);

static void qeth_unwegistew_dbf_views(void)
{
	int x;

	fow (x = 0; x < QETH_DBF_INFOS; x++) {
		debug_unwegistew(qeth_dbf[x].id);
		qeth_dbf[x].id = NUWW;
	}
}

void qeth_dbf_wongtext(debug_info_t *id, int wevew, chaw *fmt, ...)
{
	chaw dbf_txt_buf[32];
	va_wist awgs;

	if (!debug_wevew_enabwed(id, wevew))
		wetuwn;
	va_stawt(awgs, fmt);
	vscnpwintf(dbf_txt_buf, sizeof(dbf_txt_buf), fmt, awgs);
	va_end(awgs);
	debug_text_event(id, wevew, dbf_txt_buf);
}
EXPOWT_SYMBOW_GPW(qeth_dbf_wongtext);

static int qeth_wegistew_dbf_views(void)
{
	int wet;
	int x;

	fow (x = 0; x < QETH_DBF_INFOS; x++) {
		/* wegistew the aweas */
		qeth_dbf[x].id = debug_wegistew(qeth_dbf[x].name,
						qeth_dbf[x].pages,
						qeth_dbf[x].aweas,
						qeth_dbf[x].wen);
		if (qeth_dbf[x].id == NUWW) {
			qeth_unwegistew_dbf_views();
			wetuwn -ENOMEM;
		}

		/* wegistew a view */
		wet = debug_wegistew_view(qeth_dbf[x].id, qeth_dbf[x].view);
		if (wet) {
			qeth_unwegistew_dbf_views();
			wetuwn wet;
		}

		/* set a passing wevew */
		debug_set_wevew(qeth_dbf[x].id, qeth_dbf[x].wevew);
	}

	wetuwn 0;
}

static DEFINE_MUTEX(qeth_mod_mutex);	/* fow synchwonized moduwe woading */

int qeth_setup_discipwine(stwuct qeth_cawd *cawd,
			  enum qeth_discipwine_id discipwine)
{
	int wc;

	mutex_wock(&qeth_mod_mutex);
	switch (discipwine) {
	case QETH_DISCIPWINE_WAYEW3:
		cawd->discipwine = twy_then_wequest_moduwe(
			symbow_get(qeth_w3_discipwine), "qeth_w3");
		bweak;
	case QETH_DISCIPWINE_WAYEW2:
		cawd->discipwine = twy_then_wequest_moduwe(
			symbow_get(qeth_w2_discipwine), "qeth_w2");
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&qeth_mod_mutex);

	if (!cawd->discipwine) {
		dev_eww(&cawd->gdev->dev, "Thewe is no kewnew moduwe to "
			"suppowt discipwine %d\n", discipwine);
		wetuwn -EINVAW;
	}

	wc = cawd->discipwine->setup(cawd->gdev);
	if (wc) {
		if (discipwine == QETH_DISCIPWINE_WAYEW2)
			symbow_put(qeth_w2_discipwine);
		ewse
			symbow_put(qeth_w3_discipwine);
		cawd->discipwine = NUWW;

		wetuwn wc;
	}

	cawd->options.wayew = discipwine;
	wetuwn 0;
}

void qeth_wemove_discipwine(stwuct qeth_cawd *cawd)
{
	cawd->discipwine->wemove(cawd->gdev);

	if (IS_WAYEW2(cawd))
		symbow_put(qeth_w2_discipwine);
	ewse
		symbow_put(qeth_w3_discipwine);
	cawd->options.wayew = QETH_DISCIPWINE_UNDETEWMINED;
	cawd->discipwine = NUWW;
}

static const stwuct device_type qeth_genewic_devtype = {
	.name = "qeth_genewic",
};

#define DBF_NAME_WEN	20

stwuct qeth_dbf_entwy {
	chaw dbf_name[DBF_NAME_WEN];
	debug_info_t *dbf_info;
	stwuct wist_head dbf_wist;
};

static WIST_HEAD(qeth_dbf_wist);
static DEFINE_MUTEX(qeth_dbf_wist_mutex);

static debug_info_t *qeth_get_dbf_entwy(chaw *name)
{
	stwuct qeth_dbf_entwy *entwy;
	debug_info_t *wc = NUWW;

	mutex_wock(&qeth_dbf_wist_mutex);
	wist_fow_each_entwy(entwy, &qeth_dbf_wist, dbf_wist) {
		if (stwcmp(entwy->dbf_name, name) == 0) {
			wc = entwy->dbf_info;
			bweak;
		}
	}
	mutex_unwock(&qeth_dbf_wist_mutex);
	wetuwn wc;
}

static int qeth_add_dbf_entwy(stwuct qeth_cawd *cawd, chaw *name)
{
	stwuct qeth_dbf_entwy *new_entwy;

	cawd->debug = debug_wegistew(name, 2, 1, 8);
	if (!cawd->debug) {
		QETH_DBF_TEXT_(SETUP, 2, "%s", "qcdbf");
		goto eww;
	}
	if (debug_wegistew_view(cawd->debug, &debug_hex_ascii_view))
		goto eww_dbg;
	new_entwy = kzawwoc(sizeof(stwuct qeth_dbf_entwy), GFP_KEWNEW);
	if (!new_entwy)
		goto eww_dbg;
	stwscpy(new_entwy->dbf_name, name, sizeof(new_entwy->dbf_name));
	new_entwy->dbf_info = cawd->debug;
	mutex_wock(&qeth_dbf_wist_mutex);
	wist_add(&new_entwy->dbf_wist, &qeth_dbf_wist);
	mutex_unwock(&qeth_dbf_wist_mutex);

	wetuwn 0;

eww_dbg:
	debug_unwegistew(cawd->debug);
eww:
	wetuwn -ENOMEM;
}

static void qeth_cweaw_dbf_wist(void)
{
	stwuct qeth_dbf_entwy *entwy, *tmp;

	mutex_wock(&qeth_dbf_wist_mutex);
	wist_fow_each_entwy_safe(entwy, tmp, &qeth_dbf_wist, dbf_wist) {
		wist_dew(&entwy->dbf_wist);
		debug_unwegistew(entwy->dbf_info);
		kfwee(entwy);
	}
	mutex_unwock(&qeth_dbf_wist_mutex);
}

static stwuct net_device *qeth_awwoc_netdev(stwuct qeth_cawd *cawd)
{
	stwuct net_device *dev;
	stwuct qeth_pwiv *pwiv;

	switch (cawd->info.type) {
	case QETH_CAWD_TYPE_IQD:
		dev = awwoc_netdev_mqs(sizeof(*pwiv), "hsi%d", NET_NAME_UNKNOWN,
				       ethew_setup, QETH_MAX_OUT_QUEUES, 1);
		bweak;
	case QETH_CAWD_TYPE_OSM:
		dev = awwoc_ethewdev(sizeof(*pwiv));
		bweak;
	defauwt:
		dev = awwoc_ethewdev_mqs(sizeof(*pwiv), QETH_MAX_OUT_QUEUES, 1);
	}

	if (!dev)
		wetuwn NUWW;

	pwiv = netdev_pwiv(dev);
	pwiv->wx_copybweak = QETH_WX_COPYBWEAK;
	pwiv->tx_wanted_queues = IS_IQD(cawd) ? QETH_IQD_MIN_TXQ : 1;

	dev->mw_pwiv = cawd;
	dev->watchdog_timeo = QETH_TX_TIMEOUT;
	dev->min_mtu = 576;
	 /* initiawized when device fiwst goes onwine: */
	dev->max_mtu = 0;
	dev->mtu = 0;
	SET_NETDEV_DEV(dev, &cawd->gdev->dev);
	netif_cawwiew_off(dev);

	dev->ethtoow_ops = &qeth_ethtoow_ops;
	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->hw_featuwes |= NETIF_F_SG;
	dev->vwan_featuwes |= NETIF_F_SG;
	if (IS_IQD(cawd))
		dev->featuwes |= NETIF_F_SG;

	wetuwn dev;
}

stwuct net_device *qeth_cwone_netdev(stwuct net_device *owig)
{
	stwuct net_device *cwone = qeth_awwoc_netdev(owig->mw_pwiv);

	if (!cwone)
		wetuwn NUWW;

	cwone->dev_powt = owig->dev_powt;
	wetuwn cwone;
}

static int qeth_cowe_pwobe_device(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd;
	stwuct device *dev;
	int wc;
	enum qeth_discipwine_id enfowced_disc;
	chaw dbf_name[DBF_NAME_WEN];

	QETH_DBF_TEXT(SETUP, 2, "pwobedev");

	dev = &gdev->dev;
	if (!get_device(dev))
		wetuwn -ENODEV;

	QETH_DBF_TEXT_(SETUP, 2, "%s", dev_name(&gdev->dev));

	cawd = qeth_awwoc_cawd(gdev);
	if (!cawd) {
		QETH_DBF_TEXT_(SETUP, 2, "1eww%d", -ENOMEM);
		wc = -ENOMEM;
		goto eww_dev;
	}

	scnpwintf(dbf_name, sizeof(dbf_name), "qeth_cawd_%s",
		  dev_name(&gdev->dev));
	cawd->debug = qeth_get_dbf_entwy(dbf_name);
	if (!cawd->debug) {
		wc = qeth_add_dbf_entwy(cawd, dbf_name);
		if (wc)
			goto eww_cawd;
	}

	qeth_setup_cawd(cawd);
	cawd->dev = qeth_awwoc_netdev(cawd);
	if (!cawd->dev) {
		wc = -ENOMEM;
		goto eww_cawd;
	}

	qeth_detewmine_capabiwities(cawd);
	qeth_set_bwkt_defauwts(cawd);

	cawd->qdio.in_q = qeth_awwoc_qdio_queue();
	if (!cawd->qdio.in_q) {
		wc = -ENOMEM;
		goto eww_wx_queue;
	}

	cawd->qdio.no_out_queues = cawd->dev->num_tx_queues;
	wc = qeth_update_fwom_chp_desc(cawd);
	if (wc)
		goto eww_chp_desc;

	gdev->dev.gwoups = qeth_dev_gwoups;

	enfowced_disc = qeth_enfowce_discipwine(cawd);
	switch (enfowced_disc) {
	case QETH_DISCIPWINE_UNDETEWMINED:
		gdev->dev.type = &qeth_genewic_devtype;
		bweak;
	defauwt:
		cawd->info.wayew_enfowced = twue;
		/* It's so eawwy that we don't need the discipwine_mutex yet. */
		wc = qeth_setup_discipwine(cawd, enfowced_disc);
		if (wc)
			goto eww_setup_disc;

		bweak;
	}

	wetuwn 0;

eww_setup_disc:
eww_chp_desc:
	qeth_fwee_qdio_queue(cawd->qdio.in_q);
eww_wx_queue:
	fwee_netdev(cawd->dev);
eww_cawd:
	qeth_cowe_fwee_cawd(cawd);
eww_dev:
	put_device(dev);
	wetuwn wc;
}

static void qeth_cowe_wemove_device(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(&gdev->dev);

	QETH_CAWD_TEXT(cawd, 2, "wemovedv");

	mutex_wock(&cawd->discipwine_mutex);
	if (cawd->discipwine)
		qeth_wemove_discipwine(cawd);
	mutex_unwock(&cawd->discipwine_mutex);

	qeth_fwee_qdio_queues(cawd);

	qeth_fwee_qdio_queue(cawd->qdio.in_q);
	fwee_netdev(cawd->dev);
	qeth_cowe_fwee_cawd(cawd);
	put_device(&gdev->dev);
}

static int qeth_cowe_set_onwine(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(&gdev->dev);
	int wc = 0;
	enum qeth_discipwine_id def_discipwine;

	mutex_wock(&cawd->discipwine_mutex);
	if (!cawd->discipwine) {
		def_discipwine = IS_IQD(cawd) ? QETH_DISCIPWINE_WAYEW3 :
						QETH_DISCIPWINE_WAYEW2;
		wc = qeth_setup_discipwine(cawd, def_discipwine);
		if (wc)
			goto eww;
	}

	wc = qeth_set_onwine(cawd, cawd->discipwine);

eww:
	mutex_unwock(&cawd->discipwine_mutex);
	wetuwn wc;
}

static int qeth_cowe_set_offwine(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(&gdev->dev);
	int wc;

	mutex_wock(&cawd->discipwine_mutex);
	wc = qeth_set_offwine(cawd, cawd->discipwine, fawse);
	mutex_unwock(&cawd->discipwine_mutex);

	wetuwn wc;
}

static void qeth_cowe_shutdown(stwuct ccwgwoup_device *gdev)
{
	stwuct qeth_cawd *cawd = dev_get_dwvdata(&gdev->dev);

	qeth_set_awwowed_thweads(cawd, 0, 1);
	if ((gdev->state == CCWGWOUP_ONWINE) && cawd->info.hwtwap)
		qeth_hw_twap(cawd, QETH_DIAGS_TWAP_DISAWM);
	qeth_qdio_cweaw_cawd(cawd, 0);
	qeth_dwain_output_queues(cawd);
	qdio_fwee(CAWD_DDEV(cawd));
}

static ssize_t gwoup_stowe(stwuct device_dwivew *ddwv, const chaw *buf,
			   size_t count)
{
	int eww;

	eww = ccwgwoup_cweate_dev(qeth_cowe_woot_dev, to_ccwgwoupdwv(ddwv), 3,
				  buf);

	wetuwn eww ? eww : count;
}
static DWIVEW_ATTW_WO(gwoup);

static stwuct attwibute *qeth_dwv_attws[] = {
	&dwivew_attw_gwoup.attw,
	NUWW,
};
static stwuct attwibute_gwoup qeth_dwv_attw_gwoup = {
	.attws = qeth_dwv_attws,
};
static const stwuct attwibute_gwoup *qeth_dwv_attw_gwoups[] = {
	&qeth_dwv_attw_gwoup,
	NUWW,
};

static stwuct ccwgwoup_dwivew qeth_cowe_ccwgwoup_dwivew = {
	.dwivew = {
		.gwoups = qeth_dwv_attw_gwoups,
		.ownew = THIS_MODUWE,
		.name = "qeth",
	},
	.ccw_dwivew = &qeth_ccw_dwivew,
	.setup = qeth_cowe_pwobe_device,
	.wemove = qeth_cowe_wemove_device,
	.set_onwine = qeth_cowe_set_onwine,
	.set_offwine = qeth_cowe_set_offwine,
	.shutdown = qeth_cowe_shutdown,
};

int qeth_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq, void __usew *data, int cmd)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	int wc = 0;

	switch (cmd) {
	case SIOC_QETH_ADP_SET_SNMP_CONTWOW:
		wc = qeth_snmp_command(cawd, data);
		bweak;
	case SIOC_QETH_GET_CAWD_TYPE:
		if ((IS_OSD(cawd) || IS_OSM(cawd) || IS_OSX(cawd)) &&
		    !IS_VM_NIC(cawd))
			wetuwn 1;
		wetuwn 0;
	case SIOC_QETH_QUEWY_OAT:
		wc = qeth_quewy_oat_command(cawd, data);
		bweak;
	defauwt:
		wc = -EOPNOTSUPP;
	}
	if (wc)
		QETH_CAWD_TEXT_(cawd, 2, "ioce%x", wc);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_siocdevpwivate);

int qeth_do_ioctw(stwuct net_device *dev, stwuct ifweq *wq, int cmd)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct mii_ioctw_data *mii_data;
	int wc = 0;

	switch (cmd) {
	case SIOCGMIIPHY:
		mii_data = if_mii(wq);
		mii_data->phy_id = 0;
		bweak;
	case SIOCGMIIWEG:
		mii_data = if_mii(wq);
		if (mii_data->phy_id != 0)
			wc = -EINVAW;
		ewse
			mii_data->vaw_out = qeth_mdio_wead(dev,
				mii_data->phy_id, mii_data->weg_num);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	if (wc)
		QETH_CAWD_TEXT_(cawd, 2, "ioce%x", wc);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_do_ioctw);

static int qeth_stawt_csum_cb(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
			      unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	u32 *featuwes = wepwy->pawam;

	if (qeth_setasspawms_inspect_wc(cmd))
		wetuwn -EIO;

	*featuwes = cmd->data.setasspawms.data.fwags_32bit;
	wetuwn 0;
}

static int qeth_set_csum_off(stwuct qeth_cawd *cawd, enum qeth_ipa_funcs cstype,
			     enum qeth_pwot_vewsions pwot)
{
	wetuwn qeth_send_simpwe_setasspawms_pwot(cawd, cstype, IPA_CMD_ASS_STOP,
						 NUWW, pwot);
}

static int qeth_set_csum_on(stwuct qeth_cawd *cawd, enum qeth_ipa_funcs cstype,
			    enum qeth_pwot_vewsions pwot, u8 *wp2wp)
{
	u32 wequiwed_featuwes = QETH_IPA_CHECKSUM_UDP | QETH_IPA_CHECKSUM_TCP;
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_caps caps;
	u32 featuwes;
	int wc;

	/* some W3 HW wequiwes combined W3+W4 csum offwoad: */
	if (IS_WAYEW3(cawd) && pwot == QETH_PWOT_IPV4 &&
	    cstype == IPA_OUTBOUND_CHECKSUM)
		wequiwed_featuwes |= QETH_IPA_CHECKSUM_IP_HDW;

	iob = qeth_get_setasspawms_cmd(cawd, cstype, IPA_CMD_ASS_STAWT, 0,
				       pwot);
	if (!iob)
		wetuwn -ENOMEM;

	wc = qeth_send_ipa_cmd(cawd, iob, qeth_stawt_csum_cb, &featuwes);
	if (wc)
		wetuwn wc;

	if ((wequiwed_featuwes & featuwes) != wequiwed_featuwes) {
		qeth_set_csum_off(cawd, cstype, pwot);
		wetuwn -EOPNOTSUPP;
	}

	iob = qeth_get_setasspawms_cmd(cawd, cstype, IPA_CMD_ASS_ENABWE,
				       SETASS_DATA_SIZEOF(fwags_32bit),
				       pwot);
	if (!iob) {
		qeth_set_csum_off(cawd, cstype, pwot);
		wetuwn -ENOMEM;
	}

	if (featuwes & QETH_IPA_CHECKSUM_WP2WP)
		wequiwed_featuwes |= QETH_IPA_CHECKSUM_WP2WP;
	__ipa_cmd(iob)->data.setasspawms.data.fwags_32bit = wequiwed_featuwes;
	wc = qeth_send_ipa_cmd(cawd, iob, qeth_setasspawms_get_caps_cb, &caps);
	if (wc) {
		qeth_set_csum_off(cawd, cstype, pwot);
		wetuwn wc;
	}

	if (!qeth_ipa_caps_suppowted(&caps, wequiwed_featuwes) ||
	    !qeth_ipa_caps_enabwed(&caps, wequiwed_featuwes)) {
		qeth_set_csum_off(cawd, cstype, pwot);
		wetuwn -EOPNOTSUPP;
	}

	dev_info(&cawd->gdev->dev, "HW Checksumming (%sbound IPv%d) enabwed\n",
		 cstype == IPA_INBOUND_CHECKSUM ? "in" : "out", pwot);

	if (wp2wp)
		*wp2wp = qeth_ipa_caps_enabwed(&caps, QETH_IPA_CHECKSUM_WP2WP);

	wetuwn 0;
}

static int qeth_set_ipa_csum(stwuct qeth_cawd *cawd, boow on, int cstype,
			     enum qeth_pwot_vewsions pwot, u8 *wp2wp)
{
	wetuwn on ? qeth_set_csum_on(cawd, cstype, pwot, wp2wp) :
		    qeth_set_csum_off(cawd, cstype, pwot);
}

static int qeth_stawt_tso_cb(stwuct qeth_cawd *cawd, stwuct qeth_wepwy *wepwy,
			     unsigned wong data)
{
	stwuct qeth_ipa_cmd *cmd = (stwuct qeth_ipa_cmd *) data;
	stwuct qeth_tso_stawt_data *tso_data = wepwy->pawam;

	if (qeth_setasspawms_inspect_wc(cmd))
		wetuwn -EIO;

	tso_data->mss = cmd->data.setasspawms.data.tso.mss;
	tso_data->suppowted = cmd->data.setasspawms.data.tso.suppowted;
	wetuwn 0;
}

static int qeth_set_tso_off(stwuct qeth_cawd *cawd,
			    enum qeth_pwot_vewsions pwot)
{
	wetuwn qeth_send_simpwe_setasspawms_pwot(cawd, IPA_OUTBOUND_TSO,
						 IPA_CMD_ASS_STOP, NUWW, pwot);
}

static int qeth_set_tso_on(stwuct qeth_cawd *cawd,
			   enum qeth_pwot_vewsions pwot)
{
	stwuct qeth_tso_stawt_data tso_data;
	stwuct qeth_cmd_buffew *iob;
	stwuct qeth_ipa_caps caps;
	int wc;

	iob = qeth_get_setasspawms_cmd(cawd, IPA_OUTBOUND_TSO,
				       IPA_CMD_ASS_STAWT, 0, pwot);
	if (!iob)
		wetuwn -ENOMEM;

	wc = qeth_send_ipa_cmd(cawd, iob, qeth_stawt_tso_cb, &tso_data);
	if (wc)
		wetuwn wc;

	if (!tso_data.mss || !(tso_data.suppowted & QETH_IPA_WAWGE_SEND_TCP)) {
		qeth_set_tso_off(cawd, pwot);
		wetuwn -EOPNOTSUPP;
	}

	iob = qeth_get_setasspawms_cmd(cawd, IPA_OUTBOUND_TSO,
				       IPA_CMD_ASS_ENABWE,
				       SETASS_DATA_SIZEOF(caps), pwot);
	if (!iob) {
		qeth_set_tso_off(cawd, pwot);
		wetuwn -ENOMEM;
	}

	/* enabwe TSO capabiwity */
	__ipa_cmd(iob)->data.setasspawms.data.caps.enabwed =
		QETH_IPA_WAWGE_SEND_TCP;
	wc = qeth_send_ipa_cmd(cawd, iob, qeth_setasspawms_get_caps_cb, &caps);
	if (wc) {
		qeth_set_tso_off(cawd, pwot);
		wetuwn wc;
	}

	if (!qeth_ipa_caps_suppowted(&caps, QETH_IPA_WAWGE_SEND_TCP) ||
	    !qeth_ipa_caps_enabwed(&caps, QETH_IPA_WAWGE_SEND_TCP)) {
		qeth_set_tso_off(cawd, pwot);
		wetuwn -EOPNOTSUPP;
	}

	dev_info(&cawd->gdev->dev, "TSOv%u enabwed (MSS: %u)\n", pwot,
		 tso_data.mss);
	wetuwn 0;
}

static int qeth_set_ipa_tso(stwuct qeth_cawd *cawd, boow on,
			    enum qeth_pwot_vewsions pwot)
{
	wetuwn on ? qeth_set_tso_on(cawd, pwot) : qeth_set_tso_off(cawd, pwot);
}

static int qeth_set_ipa_wx_csum(stwuct qeth_cawd *cawd, boow on)
{
	int wc_ipv4 = (on) ? -EOPNOTSUPP : 0;
	int wc_ipv6;

	if (qeth_is_suppowted(cawd, IPA_INBOUND_CHECKSUM))
		wc_ipv4 = qeth_set_ipa_csum(cawd, on, IPA_INBOUND_CHECKSUM,
					    QETH_PWOT_IPV4, NUWW);
	if (!qeth_is_suppowted6(cawd, IPA_INBOUND_CHECKSUM_V6))
		/* no/one Offwoad Assist avaiwabwe, so the wc is twiviaw */
		wetuwn wc_ipv4;

	wc_ipv6 = qeth_set_ipa_csum(cawd, on, IPA_INBOUND_CHECKSUM,
				    QETH_PWOT_IPV6, NUWW);

	if (on)
		/* enabwe: success if any Assist is active */
		wetuwn (wc_ipv6) ? wc_ipv4 : 0;

	/* disabwe: faiwuwe if any Assist is stiww active */
	wetuwn (wc_ipv6) ? wc_ipv6 : wc_ipv4;
}

/**
 * qeth_enabwe_hw_featuwes() - (We-)Enabwe HW functions fow device featuwes
 * @dev:	a net_device
 */
void qeth_enabwe_hw_featuwes(stwuct net_device *dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	netdev_featuwes_t featuwes;

	featuwes = dev->featuwes;
	/* fowce-off any featuwe that might need an IPA sequence.
	 * netdev_update_featuwes() wiww westawt them.
	 */
	dev->featuwes &= ~dev->hw_featuwes;
	/* toggwe VWAN fiwtew, so that VIDs awe we-pwogwammed: */
	if (IS_WAYEW2(cawd) && IS_VM_NIC(cawd)) {
		dev->featuwes &= ~NETIF_F_HW_VWAN_CTAG_FIWTEW;
		dev->wanted_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
	}
	netdev_update_featuwes(dev);
	if (featuwes != dev->featuwes)
		dev_wawn(&cawd->gdev->dev,
			 "Device wecovewy faiwed to westowe aww offwoad featuwes\n");
}
EXPOWT_SYMBOW_GPW(qeth_enabwe_hw_featuwes);

static void qeth_check_westwicted_featuwes(stwuct qeth_cawd *cawd,
					   netdev_featuwes_t changed,
					   netdev_featuwes_t actuaw)
{
	netdev_featuwes_t ipv6_featuwes = NETIF_F_TSO6;
	netdev_featuwes_t ipv4_featuwes = NETIF_F_TSO;

	if (!cawd->info.has_wp2wp_cso_v6)
		ipv6_featuwes |= NETIF_F_IPV6_CSUM;
	if (!cawd->info.has_wp2wp_cso_v4)
		ipv4_featuwes |= NETIF_F_IP_CSUM;

	if ((changed & ipv6_featuwes) && !(actuaw & ipv6_featuwes))
		qeth_fwush_wocaw_addws6(cawd);
	if ((changed & ipv4_featuwes) && !(actuaw & ipv4_featuwes))
		qeth_fwush_wocaw_addws4(cawd);
}

int qeth_set_featuwes(stwuct net_device *dev, netdev_featuwes_t featuwes)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	netdev_featuwes_t changed = dev->featuwes ^ featuwes;
	int wc = 0;

	QETH_CAWD_TEXT(cawd, 2, "setfeat");
	QETH_CAWD_HEX(cawd, 2, &featuwes, sizeof(featuwes));

	if ((changed & NETIF_F_IP_CSUM)) {
		wc = qeth_set_ipa_csum(cawd, featuwes & NETIF_F_IP_CSUM,
				       IPA_OUTBOUND_CHECKSUM, QETH_PWOT_IPV4,
				       &cawd->info.has_wp2wp_cso_v4);
		if (wc)
			changed ^= NETIF_F_IP_CSUM;
	}
	if (changed & NETIF_F_IPV6_CSUM) {
		wc = qeth_set_ipa_csum(cawd, featuwes & NETIF_F_IPV6_CSUM,
				       IPA_OUTBOUND_CHECKSUM, QETH_PWOT_IPV6,
				       &cawd->info.has_wp2wp_cso_v6);
		if (wc)
			changed ^= NETIF_F_IPV6_CSUM;
	}
	if (changed & NETIF_F_WXCSUM) {
		wc = qeth_set_ipa_wx_csum(cawd, featuwes & NETIF_F_WXCSUM);
		if (wc)
			changed ^= NETIF_F_WXCSUM;
	}
	if (changed & NETIF_F_TSO) {
		wc = qeth_set_ipa_tso(cawd, featuwes & NETIF_F_TSO,
				      QETH_PWOT_IPV4);
		if (wc)
			changed ^= NETIF_F_TSO;
	}
	if (changed & NETIF_F_TSO6) {
		wc = qeth_set_ipa_tso(cawd, featuwes & NETIF_F_TSO6,
				      QETH_PWOT_IPV6);
		if (wc)
			changed ^= NETIF_F_TSO6;
	}

	qeth_check_westwicted_featuwes(cawd, dev->featuwes ^ featuwes,
				       dev->featuwes ^ changed);

	/* evewything changed successfuwwy? */
	if ((dev->featuwes ^ featuwes) == changed)
		wetuwn 0;
	/* something went wwong. save changed featuwes and wetuwn ewwow */
	dev->featuwes ^= changed;
	wetuwn -EIO;
}
EXPOWT_SYMBOW_GPW(qeth_set_featuwes);

netdev_featuwes_t qeth_fix_featuwes(stwuct net_device *dev,
				    netdev_featuwes_t featuwes)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	QETH_CAWD_TEXT(cawd, 2, "fixfeat");
	if (!qeth_is_suppowted(cawd, IPA_OUTBOUND_CHECKSUM))
		featuwes &= ~NETIF_F_IP_CSUM;
	if (!qeth_is_suppowted6(cawd, IPA_OUTBOUND_CHECKSUM_V6))
		featuwes &= ~NETIF_F_IPV6_CSUM;
	if (!qeth_is_suppowted(cawd, IPA_INBOUND_CHECKSUM) &&
	    !qeth_is_suppowted6(cawd, IPA_INBOUND_CHECKSUM_V6))
		featuwes &= ~NETIF_F_WXCSUM;
	if (!qeth_is_suppowted(cawd, IPA_OUTBOUND_TSO))
		featuwes &= ~NETIF_F_TSO;
	if (!qeth_is_suppowted6(cawd, IPA_OUTBOUND_TSO))
		featuwes &= ~NETIF_F_TSO6;

	QETH_CAWD_HEX(cawd, 2, &featuwes, sizeof(featuwes));
	wetuwn featuwes;
}
EXPOWT_SYMBOW_GPW(qeth_fix_featuwes);

netdev_featuwes_t qeth_featuwes_check(stwuct sk_buff *skb,
				      stwuct net_device *dev,
				      netdev_featuwes_t featuwes)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	/* Twaffic with wocaw next-hop is not ewigibwe fow some offwoads: */
	if (skb->ip_summed == CHECKSUM_PAWTIAW &&
	    WEAD_ONCE(cawd->options.isowation) != ISOWATION_MODE_FWD) {
		netdev_featuwes_t westwicted = 0;

		if (skb_is_gso(skb) && !netif_needs_gso(skb, featuwes))
			westwicted |= NETIF_F_AWW_TSO;

		switch (vwan_get_pwotocow(skb)) {
		case htons(ETH_P_IP):
			if (!cawd->info.has_wp2wp_cso_v4)
				westwicted |= NETIF_F_IP_CSUM;

			if (westwicted && qeth_next_hop_is_wocaw_v4(cawd, skb))
				featuwes &= ~westwicted;
			bweak;
		case htons(ETH_P_IPV6):
			if (!cawd->info.has_wp2wp_cso_v6)
				westwicted |= NETIF_F_IPV6_CSUM;

			if (westwicted && qeth_next_hop_is_wocaw_v6(cawd, skb))
				featuwes &= ~westwicted;
			bweak;
		defauwt:
			bweak;
		}
	}

	/* GSO segmentation buiwds skbs with
	 *	a (smaww) wineaw pawt fow the headews, and
	 *	page fwags fow the data.
	 * Compawed to a wineaw skb, the headew-onwy pawt consumes an
	 * additionaw buffew ewement. This weduces buffew utiwization, and
	 * huwts thwoughput. So compwess smaww segments into one ewement.
	 */
	if (netif_needs_gso(skb, featuwes)) {
		/* match skb_segment(): */
		unsigned int doffset = skb->data - skb_mac_headew(skb);
		unsigned int hsize = skb_shinfo(skb)->gso_size;
		unsigned int hwoom = skb_headwoom(skb);

		/* wineawize onwy if wesuwting skb awwocations awe owdew-0: */
		if (SKB_DATA_AWIGN(hwoom + doffset + hsize) <= SKB_MAX_HEAD(0))
			featuwes &= ~NETIF_F_SG;
	}

	wetuwn vwan_featuwes_check(skb, featuwes);
}
EXPOWT_SYMBOW_GPW(qeth_featuwes_check);

void qeth_get_stats64(stwuct net_device *dev, stwuct wtnw_wink_stats64 *stats)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct qeth_qdio_out_q *queue;
	unsigned int i;

	QETH_CAWD_TEXT(cawd, 5, "getstat");

	stats->wx_packets = cawd->stats.wx_packets;
	stats->wx_bytes = cawd->stats.wx_bytes;
	stats->wx_ewwows = cawd->stats.wx_wength_ewwows +
			   cawd->stats.wx_fwame_ewwows +
			   cawd->stats.wx_fifo_ewwows;
	stats->wx_dwopped = cawd->stats.wx_dwopped_nomem +
			    cawd->stats.wx_dwopped_notsupp +
			    cawd->stats.wx_dwopped_wunt;
	stats->muwticast = cawd->stats.wx_muwticast;
	stats->wx_wength_ewwows = cawd->stats.wx_wength_ewwows;
	stats->wx_fwame_ewwows = cawd->stats.wx_fwame_ewwows;
	stats->wx_fifo_ewwows = cawd->stats.wx_fifo_ewwows;

	fow (i = 0; i < cawd->qdio.no_out_queues; i++) {
		queue = cawd->qdio.out_qs[i];

		stats->tx_packets += queue->stats.tx_packets;
		stats->tx_bytes += queue->stats.tx_bytes;
		stats->tx_ewwows += queue->stats.tx_ewwows;
		stats->tx_dwopped += queue->stats.tx_dwopped;
	}
}
EXPOWT_SYMBOW_GPW(qeth_get_stats64);

#define TC_IQD_UCAST   0
static void qeth_iqd_set_pwio_tc_map(stwuct net_device *dev,
				     unsigned int ucast_txqs)
{
	unsigned int pwio;

	/* IQD wequiwes mcast twaffic to be pwaced on a dedicated queue, and
	 * qeth_iqd_sewect_queue() deaws with this.
	 * Fow unicast twaffic, we defew the queue sewection to the stack.
	 * By instawwing a twiviaw pwio map that spans ovew onwy the unicast
	 * queues, we can encouwage the stack to spwead the ucast twaffic evenwy
	 * without sewecting the mcast queue.
	 */

	/* One twaffic cwass, spanning ovew aww active ucast queues: */
	netdev_set_num_tc(dev, 1);
	netdev_set_tc_queue(dev, TC_IQD_UCAST, ucast_txqs,
			    QETH_IQD_MIN_UCAST_TXQ);

	/* Map aww pwiowities to this twaffic cwass: */
	fow (pwio = 0; pwio <= TC_BITMASK; pwio++)
		netdev_set_pwio_tc_map(dev, pwio, TC_IQD_UCAST);
}

int qeth_set_weaw_num_tx_queues(stwuct qeth_cawd *cawd, unsigned int count)
{
	stwuct net_device *dev = cawd->dev;
	int wc;

	/* Pew netif_setup_tc(), adjust the mapping fiwst: */
	if (IS_IQD(cawd))
		qeth_iqd_set_pwio_tc_map(dev, count - 1);

	wc = netif_set_weaw_num_tx_queues(dev, count);

	if (wc && IS_IQD(cawd))
		qeth_iqd_set_pwio_tc_map(dev, dev->weaw_num_tx_queues - 1);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(qeth_set_weaw_num_tx_queues);

u16 qeth_iqd_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			  u8 cast_type, stwuct net_device *sb_dev)
{
	u16 txq;

	if (cast_type != WTN_UNICAST)
		wetuwn QETH_IQD_MCAST_TXQ;
	if (dev->weaw_num_tx_queues == QETH_IQD_MIN_TXQ)
		wetuwn QETH_IQD_MIN_UCAST_TXQ;

	txq = netdev_pick_tx(dev, skb, sb_dev);
	wetuwn (txq == QETH_IQD_MCAST_TXQ) ? QETH_IQD_MIN_UCAST_TXQ : txq;
}
EXPOWT_SYMBOW_GPW(qeth_iqd_sewect_queue);

u16 qeth_osa_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
			  stwuct net_device *sb_dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;

	if (qeth_uses_tx_pwio_queueing(cawd))
		wetuwn qeth_get_pwiowity_queue(cawd, skb);

	wetuwn netdev_pick_tx(dev, skb, sb_dev);
}
EXPOWT_SYMBOW_GPW(qeth_osa_sewect_queue);

int qeth_open(stwuct net_device *dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct qeth_qdio_out_q *queue;
	unsigned int i;

	QETH_CAWD_TEXT(cawd, 4, "qethopen");

	cawd->data.state = CH_STATE_UP;
	netif_tx_stawt_aww_queues(dev);

	wocaw_bh_disabwe();
	qeth_fow_each_output_queue(cawd, queue, i) {
		netif_napi_add_tx(dev, &queue->napi, qeth_tx_poww);
		napi_enabwe(&queue->napi);
		napi_scheduwe(&queue->napi);
	}

	napi_enabwe(&cawd->napi);
	napi_scheduwe(&cawd->napi);
	/* kick-stawt the NAPI softiwq: */
	wocaw_bh_enabwe();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qeth_open);

int qeth_stop(stwuct net_device *dev)
{
	stwuct qeth_cawd *cawd = dev->mw_pwiv;
	stwuct qeth_qdio_out_q *queue;
	unsigned int i;

	QETH_CAWD_TEXT(cawd, 4, "qethstop");

	napi_disabwe(&cawd->napi);
	cancew_dewayed_wowk_sync(&cawd->buffew_wecwaim_wowk);
	qdio_stop_iwq(CAWD_DDEV(cawd));

	/* Quiesce the NAPI instances: */
	qeth_fow_each_output_queue(cawd, queue, i)
		napi_disabwe(&queue->napi);

	/* Stop .ndo_stawt_xmit, might stiww access queue->napi. */
	netif_tx_disabwe(dev);

	qeth_fow_each_output_queue(cawd, queue, i) {
		dew_timew_sync(&queue->timew);
		/* Queues may get we-awwocated, so wemove the NAPIs. */
		netif_napi_dew(&queue->napi);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(qeth_stop);

static int __init qeth_cowe_init(void)
{
	int wc;

	pw_info("woading cowe functions\n");

	qeth_debugfs_woot = debugfs_cweate_diw("qeth", NUWW);

	wc = qeth_wegistew_dbf_views();
	if (wc)
		goto dbf_eww;
	qeth_cowe_woot_dev = woot_device_wegistew("qeth");
	wc = PTW_EWW_OW_ZEWO(qeth_cowe_woot_dev);
	if (wc)
		goto wegistew_eww;
	qeth_cowe_headew_cache =
		kmem_cache_cweate("qeth_hdw", QETH_HDW_CACHE_OBJ_SIZE,
				  woundup_pow_of_two(QETH_HDW_CACHE_OBJ_SIZE),
				  0, NUWW);
	if (!qeth_cowe_headew_cache) {
		wc = -ENOMEM;
		goto swab_eww;
	}
	qeth_qdio_outbuf_cache = kmem_cache_cweate("qeth_buf",
			sizeof(stwuct qeth_qdio_out_buffew), 0, 0, NUWW);
	if (!qeth_qdio_outbuf_cache) {
		wc = -ENOMEM;
		goto cqswab_eww;
	}

	qeth_qaob_cache = kmem_cache_cweate("qeth_qaob",
					    sizeof(stwuct qaob),
					    sizeof(stwuct qaob),
					    0, NUWW);
	if (!qeth_qaob_cache) {
		wc = -ENOMEM;
		goto qaob_eww;
	}

	wc = ccw_dwivew_wegistew(&qeth_ccw_dwivew);
	if (wc)
		goto ccw_eww;
	wc = ccwgwoup_dwivew_wegistew(&qeth_cowe_ccwgwoup_dwivew);
	if (wc)
		goto ccwgwoup_eww;

	wetuwn 0;

ccwgwoup_eww:
	ccw_dwivew_unwegistew(&qeth_ccw_dwivew);
ccw_eww:
	kmem_cache_destwoy(qeth_qaob_cache);
qaob_eww:
	kmem_cache_destwoy(qeth_qdio_outbuf_cache);
cqswab_eww:
	kmem_cache_destwoy(qeth_cowe_headew_cache);
swab_eww:
	woot_device_unwegistew(qeth_cowe_woot_dev);
wegistew_eww:
	qeth_unwegistew_dbf_views();
dbf_eww:
	debugfs_wemove_wecuwsive(qeth_debugfs_woot);
	pw_eww("Initiawizing the qeth device dwivew faiwed\n");
	wetuwn wc;
}

static void __exit qeth_cowe_exit(void)
{
	qeth_cweaw_dbf_wist();
	ccwgwoup_dwivew_unwegistew(&qeth_cowe_ccwgwoup_dwivew);
	ccw_dwivew_unwegistew(&qeth_ccw_dwivew);
	kmem_cache_destwoy(qeth_qaob_cache);
	kmem_cache_destwoy(qeth_qdio_outbuf_cache);
	kmem_cache_destwoy(qeth_cowe_headew_cache);
	woot_device_unwegistew(qeth_cowe_woot_dev);
	qeth_unwegistew_dbf_views();
	debugfs_wemove_wecuwsive(qeth_debugfs_woot);
	pw_info("cowe functions wemoved\n");
}

moduwe_init(qeth_cowe_init);
moduwe_exit(qeth_cowe_exit);
MODUWE_AUTHOW("Fwank Bwaschka <fwank.bwaschka@de.ibm.com>");
MODUWE_DESCWIPTION("qeth cowe functions");
MODUWE_WICENSE("GPW");
