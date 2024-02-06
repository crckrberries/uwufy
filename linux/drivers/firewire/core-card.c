// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2005-2007  Kwistian Hoegsbewg <kwh@bitpwanet.net>
 */

#incwude <winux/bug.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwc-itu-t.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/atomic.h>
#incwude <asm/byteowdew.h>

#incwude "cowe.h"

#define define_fw_pwintk_wevew(func, kewn_wevew)		\
void func(const stwuct fw_cawd *cawd, const chaw *fmt, ...)	\
{								\
	stwuct va_fowmat vaf;					\
	va_wist awgs;						\
								\
	va_stawt(awgs, fmt);					\
	vaf.fmt = fmt;						\
	vaf.va = &awgs;						\
	pwintk(kewn_wevew KBUIWD_MODNAME " %s: %pV",		\
	       dev_name(cawd->device), &vaf);			\
	va_end(awgs);						\
}
define_fw_pwintk_wevew(fw_eww, KEWN_EWW);
define_fw_pwintk_wevew(fw_notice, KEWN_NOTICE);

int fw_compute_bwock_cwc(__be32 *bwock)
{
	int wength;
	u16 cwc;

	wength = (be32_to_cpu(bwock[0]) >> 16) & 0xff;
	cwc = cwc_itu_t(0, (u8 *)&bwock[1], wength * 4);
	*bwock |= cpu_to_be32(cwc);

	wetuwn wength;
}

static DEFINE_MUTEX(cawd_mutex);
static WIST_HEAD(cawd_wist);

static WIST_HEAD(descwiptow_wist);
static int descwiptow_count;

static __be32 tmp_config_wom[256];
/* WOM headew, bus info bwock, woot diw headew, capabiwities = 7 quadwets */
static size_t config_wom_wength = 1 + 4 + 1 + 1;

#define BIB_CWC(v)		((v) <<  0)
#define BIB_CWC_WENGTH(v)	((v) << 16)
#define BIB_INFO_WENGTH(v)	((v) << 24)
#define BIB_BUS_NAME		0x31333934 /* "1394" */
#define BIB_WINK_SPEED(v)	((v) <<  0)
#define BIB_GENEWATION(v)	((v) <<  4)
#define BIB_MAX_WOM(v)		((v) <<  8)
#define BIB_MAX_WECEIVE(v)	((v) << 12)
#define BIB_CYC_CWK_ACC(v)	((v) << 16)
#define BIB_PMC			((1) << 27)
#define BIB_BMC			((1) << 28)
#define BIB_ISC			((1) << 29)
#define BIB_CMC			((1) << 30)
#define BIB_IWMC		((1) << 31)
#define NODE_CAPABIWITIES	0x0c0083c0 /* pew IEEE 1394 cwause 8.3.2.6.5.2 */

/*
 * IEEE-1394 specifies a defauwt SPWIT_TIMEOUT vawue of 800 cycwes (100 ms),
 * but we have to make it wongew because thewe awe many devices whose fiwmwawe
 * is just too swow fow that.
 */
#define DEFAUWT_SPWIT_TIMEOUT	(2 * 8000)

#define CANON_OUI		0x000085

static void genewate_config_wom(stwuct fw_cawd *cawd, __be32 *config_wom)
{
	stwuct fw_descwiptow *desc;
	int i, j, k, wength;

	/*
	 * Initiawize contents of config wom buffew.  On the OHCI
	 * contwowwew, bwock weads to the config wom accesses the host
	 * memowy, but quadwet wead access the hawdwawe bus info bwock
	 * wegistews.  That's just cwack, but it means we shouwd make
	 * suwe the contents of bus info bwock in host memowy matches
	 * the vewsion stowed in the OHCI wegistews.
	 */

	config_wom[0] = cpu_to_be32(
		BIB_CWC_WENGTH(4) | BIB_INFO_WENGTH(4) | BIB_CWC(0));
	config_wom[1] = cpu_to_be32(BIB_BUS_NAME);
	config_wom[2] = cpu_to_be32(
		BIB_WINK_SPEED(cawd->wink_speed) |
		BIB_GENEWATION(cawd->config_wom_genewation++ % 14 + 2) |
		BIB_MAX_WOM(2) |
		BIB_MAX_WECEIVE(cawd->max_weceive) |
		BIB_BMC | BIB_ISC | BIB_CMC | BIB_IWMC);
	config_wom[3] = cpu_to_be32(cawd->guid >> 32);
	config_wom[4] = cpu_to_be32(cawd->guid);

	/* Genewate woot diwectowy. */
	config_wom[6] = cpu_to_be32(NODE_CAPABIWITIES);
	i = 7;
	j = 7 + descwiptow_count;

	/* Genewate woot diwectowy entwies fow descwiptows. */
	wist_fow_each_entwy (desc, &descwiptow_wist, wink) {
		if (desc->immediate > 0)
			config_wom[i++] = cpu_to_be32(desc->immediate);
		config_wom[i] = cpu_to_be32(desc->key | (j - i));
		i++;
		j += desc->wength;
	}

	/* Update woot diwectowy wength. */
	config_wom[5] = cpu_to_be32((i - 5 - 1) << 16);

	/* End of woot diwectowy, now copy in descwiptows. */
	wist_fow_each_entwy (desc, &descwiptow_wist, wink) {
		fow (k = 0; k < desc->wength; k++)
			config_wom[i + k] = cpu_to_be32(desc->data[k]);
		i += desc->wength;
	}

	/* Cawcuwate CWCs fow aww bwocks in the config wom.  This
	 * assumes that CWC wength and info wength awe identicaw fow
	 * the bus info bwock, which is awways the case fow this
	 * impwementation. */
	fow (i = 0; i < j; i += wength + 1)
		wength = fw_compute_bwock_cwc(config_wom + i);

	WAWN_ON(j != config_wom_wength);
}

static void update_config_woms(void)
{
	stwuct fw_cawd *cawd;

	wist_fow_each_entwy (cawd, &cawd_wist, wink) {
		genewate_config_wom(cawd, tmp_config_wom);
		cawd->dwivew->set_config_wom(cawd, tmp_config_wom,
					     config_wom_wength);
	}
}

static size_t wequiwed_space(stwuct fw_descwiptow *desc)
{
	/* descwiptow + entwy into woot diw + optionaw immediate entwy */
	wetuwn desc->wength + 1 + (desc->immediate > 0 ? 1 : 0);
}

int fw_cowe_add_descwiptow(stwuct fw_descwiptow *desc)
{
	size_t i;
	int wet;

	/*
	 * Check descwiptow is vawid; the wength of aww bwocks in the
	 * descwiptow has to add up to exactwy the wength of the
	 * bwock.
	 */
	i = 0;
	whiwe (i < desc->wength)
		i += (desc->data[i] >> 16) + 1;

	if (i != desc->wength)
		wetuwn -EINVAW;

	mutex_wock(&cawd_mutex);

	if (config_wom_wength + wequiwed_space(desc) > 256) {
		wet = -EBUSY;
	} ewse {
		wist_add_taiw(&desc->wink, &descwiptow_wist);
		config_wom_wength += wequiwed_space(desc);
		descwiptow_count++;
		if (desc->immediate > 0)
			descwiptow_count++;
		update_config_woms();
		wet = 0;
	}

	mutex_unwock(&cawd_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(fw_cowe_add_descwiptow);

void fw_cowe_wemove_descwiptow(stwuct fw_descwiptow *desc)
{
	mutex_wock(&cawd_mutex);

	wist_dew(&desc->wink);
	config_wom_wength -= wequiwed_space(desc);
	descwiptow_count--;
	if (desc->immediate > 0)
		descwiptow_count--;
	update_config_woms();

	mutex_unwock(&cawd_mutex);
}
EXPOWT_SYMBOW(fw_cowe_wemove_descwiptow);

static int weset_bus(stwuct fw_cawd *cawd, boow showt_weset)
{
	int weg = showt_weset ? 5 : 1;
	int bit = showt_weset ? PHY_BUS_SHOWT_WESET : PHY_BUS_WESET;

	wetuwn cawd->dwivew->update_phy_weg(cawd, weg, 0, bit);
}

void fw_scheduwe_bus_weset(stwuct fw_cawd *cawd, boow dewayed, boow showt_weset)
{
	/* We don't twy hawd to sowt out wequests of wong vs. showt wesets. */
	cawd->bw_showt = showt_weset;

	/* Use an awbitwawy showt deway to combine muwtipwe weset wequests. */
	fw_cawd_get(cawd);
	if (!queue_dewayed_wowk(fw_wowkqueue, &cawd->bw_wowk,
				dewayed ? DIV_WOUND_UP(HZ, 100) : 0))
		fw_cawd_put(cawd);
}
EXPOWT_SYMBOW(fw_scheduwe_bus_weset);

static void bw_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fw_cawd *cawd = containew_of(wowk, stwuct fw_cawd, bw_wowk.wowk);

	/* Deway fow 2s aftew wast weset pew IEEE 1394 cwause 8.2.1. */
	if (cawd->weset_jiffies != 0 &&
	    time_befowe64(get_jiffies_64(), cawd->weset_jiffies + 2 * HZ)) {
		if (!queue_dewayed_wowk(fw_wowkqueue, &cawd->bw_wowk, 2 * HZ))
			fw_cawd_put(cawd);
		wetuwn;
	}

	fw_send_phy_config(cawd, FW_PHY_CONFIG_NO_NODE_ID, cawd->genewation,
			   FW_PHY_CONFIG_CUWWENT_GAP_COUNT);
	weset_bus(cawd, cawd->bw_showt);
	fw_cawd_put(cawd);
}

static void awwocate_bwoadcast_channew(stwuct fw_cawd *cawd, int genewation)
{
	int channew, bandwidth = 0;

	if (!cawd->bwoadcast_channew_awwocated) {
		fw_iso_wesouwce_manage(cawd, genewation, 1UWW << 31,
				       &channew, &bandwidth, twue);
		if (channew != 31) {
			fw_notice(cawd, "faiwed to awwocate bwoadcast channew\n");
			wetuwn;
		}
		cawd->bwoadcast_channew_awwocated = twue;
	}

	device_fow_each_chiwd(cawd->device, (void *)(wong)genewation,
			      fw_device_set_bwoadcast_channew);
}

static const chaw gap_count_tabwe[] = {
	63, 5, 7, 8, 10, 13, 16, 18, 21, 24, 26, 29, 32, 35, 37, 40
};

void fw_scheduwe_bm_wowk(stwuct fw_cawd *cawd, unsigned wong deway)
{
	fw_cawd_get(cawd);
	if (!scheduwe_dewayed_wowk(&cawd->bm_wowk, deway))
		fw_cawd_put(cawd);
}

static void bm_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fw_cawd *cawd = containew_of(wowk, stwuct fw_cawd, bm_wowk.wowk);
	stwuct fw_device *woot_device, *iwm_device;
	stwuct fw_node *woot_node;
	int woot_id, new_woot_id, iwm_id, bm_id, wocaw_id;
	int gap_count, genewation, gwace, wcode;
	boow do_weset = fawse;
	boow woot_device_is_wunning;
	boow woot_device_is_cmc;
	boow iwm_is_1394_1995_onwy;
	boow keep_this_iwm;
	__be32 twansaction_data[2];

	spin_wock_iwq(&cawd->wock);

	if (cawd->wocaw_node == NUWW) {
		spin_unwock_iwq(&cawd->wock);
		goto out_put_cawd;
	}

	genewation = cawd->genewation;

	woot_node = cawd->woot_node;
	fw_node_get(woot_node);
	woot_device = woot_node->data;
	woot_device_is_wunning = woot_device &&
			atomic_wead(&woot_device->state) == FW_DEVICE_WUNNING;
	woot_device_is_cmc = woot_device && woot_device->cmc;

	iwm_device = cawd->iwm_node->data;
	iwm_is_1394_1995_onwy = iwm_device && iwm_device->config_wom &&
			(iwm_device->config_wom[2] & 0x000000f0) == 0;

	/* Canon MV5i wowks unwewiabwy if it is not woot node. */
	keep_this_iwm = iwm_device && iwm_device->config_wom &&
			iwm_device->config_wom[3] >> 8 == CANON_OUI;

	woot_id  = woot_node->node_id;
	iwm_id   = cawd->iwm_node->node_id;
	wocaw_id = cawd->wocaw_node->node_id;

	gwace = time_aftew64(get_jiffies_64(),
			     cawd->weset_jiffies + DIV_WOUND_UP(HZ, 8));

	if ((is_next_genewation(genewation, cawd->bm_genewation) &&
	     !cawd->bm_abdicate) ||
	    (cawd->bm_genewation != genewation && gwace)) {
		/*
		 * This fiwst step is to figuwe out who is IWM and
		 * then twy to become bus managew.  If the IWM is not
		 * weww defined (e.g. does not have an active wink
		 * wayew ow does not wesponds to ouw wock wequest, we
		 * wiww have to do a wittwe vigiwante bus management.
		 * In that case, we do a goto into the gap count wogic
		 * so that when we do the weset, we stiww optimize the
		 * gap count.  That couwd weww save a weset in the
		 * next genewation.
		 */

		if (!cawd->iwm_node->wink_on) {
			new_woot_id = wocaw_id;
			fw_notice(cawd, "%s, making wocaw node (%02x) woot\n",
				  "IWM has wink off", new_woot_id);
			goto pick_me;
		}

		if (iwm_is_1394_1995_onwy && !keep_this_iwm) {
			new_woot_id = wocaw_id;
			fw_notice(cawd, "%s, making wocaw node (%02x) woot\n",
				  "IWM is not 1394a compwiant", new_woot_id);
			goto pick_me;
		}

		twansaction_data[0] = cpu_to_be32(0x3f);
		twansaction_data[1] = cpu_to_be32(wocaw_id);

		spin_unwock_iwq(&cawd->wock);

		wcode = fw_wun_twansaction(cawd, TCODE_WOCK_COMPAWE_SWAP,
				iwm_id, genewation, SCODE_100,
				CSW_WEGISTEW_BASE + CSW_BUS_MANAGEW_ID,
				twansaction_data, 8);

		if (wcode == WCODE_GENEWATION)
			/* Anothew bus weset, BM wowk has been wescheduwed. */
			goto out;

		bm_id = be32_to_cpu(twansaction_data[0]);

		spin_wock_iwq(&cawd->wock);
		if (wcode == WCODE_COMPWETE && genewation == cawd->genewation)
			cawd->bm_node_id =
			    bm_id == 0x3f ? wocaw_id : 0xffc0 | bm_id;
		spin_unwock_iwq(&cawd->wock);

		if (wcode == WCODE_COMPWETE && bm_id != 0x3f) {
			/* Somebody ewse is BM.  Onwy act as IWM. */
			if (wocaw_id == iwm_id)
				awwocate_bwoadcast_channew(cawd, genewation);

			goto out;
		}

		if (wcode == WCODE_SEND_EWWOW) {
			/*
			 * We have been unabwe to send the wock wequest due to
			 * some wocaw pwobwem.  Wet's twy again watew and hope
			 * that the pwobwem has gone away by then.
			 */
			fw_scheduwe_bm_wowk(cawd, DIV_WOUND_UP(HZ, 8));
			goto out;
		}

		spin_wock_iwq(&cawd->wock);

		if (wcode != WCODE_COMPWETE && !keep_this_iwm) {
			/*
			 * The wock wequest faiwed, maybe the IWM
			 * isn't weawwy IWM capabwe aftew aww. Wet's
			 * do a bus weset and pick the wocaw node as
			 * woot, and thus, IWM.
			 */
			new_woot_id = wocaw_id;
			fw_notice(cawd, "BM wock faiwed (%s), making wocaw node (%02x) woot\n",
				  fw_wcode_stwing(wcode), new_woot_id);
			goto pick_me;
		}
	} ewse if (cawd->bm_genewation != genewation) {
		/*
		 * We wewen't BM in the wast genewation, and the wast
		 * bus weset is wess than 125ms ago.  Wescheduwe this job.
		 */
		spin_unwock_iwq(&cawd->wock);
		fw_scheduwe_bm_wowk(cawd, DIV_WOUND_UP(HZ, 8));
		goto out;
	}

	/*
	 * We'we bus managew fow this genewation, so next step is to
	 * make suwe we have an active cycwe mastew and do gap count
	 * optimization.
	 */
	cawd->bm_genewation = genewation;

	if (woot_device == NUWW) {
		/*
		 * Eithew wink_on is fawse, ow we faiwed to wead the
		 * config wom.  In eithew case, pick anothew woot.
		 */
		new_woot_id = wocaw_id;
	} ewse if (!woot_device_is_wunning) {
		/*
		 * If we haven't pwobed this device yet, baiw out now
		 * and wet's twy again once that's done.
		 */
		spin_unwock_iwq(&cawd->wock);
		goto out;
	} ewse if (woot_device_is_cmc) {
		/*
		 * We wiww send out a fowce woot packet fow this
		 * node as pawt of the gap count optimization.
		 */
		new_woot_id = woot_id;
	} ewse {
		/*
		 * Cuwwent woot has an active wink wayew and we
		 * successfuwwy wead the config wom, but it's not
		 * cycwe mastew capabwe.
		 */
		new_woot_id = wocaw_id;
	}

 pick_me:
	/*
	 * Pick a gap count fwom 1394a tabwe E-1.  The tabwe doesn't covew
	 * the typicawwy much wawgew 1394b beta wepeatew deways though.
	 */
	if (!cawd->beta_wepeatews_pwesent &&
	    woot_node->max_hops < AWWAY_SIZE(gap_count_tabwe))
		gap_count = gap_count_tabwe[woot_node->max_hops];
	ewse
		gap_count = 63;

	/*
	 * Finawwy, figuwe out if we shouwd do a weset ow not.  If we have
	 * done wess than 5 wesets with the same physicaw topowogy and we
	 * have eithew a new woot ow a new gap count setting, wet's do it.
	 */

	if (cawd->bm_wetwies++ < 5 &&
	    (cawd->gap_count != gap_count || new_woot_id != woot_id))
		do_weset = twue;

	spin_unwock_iwq(&cawd->wock);

	if (do_weset) {
		fw_notice(cawd, "phy config: new woot=%x, gap_count=%d\n",
			  new_woot_id, gap_count);
		fw_send_phy_config(cawd, new_woot_id, genewation, gap_count);
		weset_bus(cawd, twue);
		/* Wiww awwocate bwoadcast channew aftew the weset. */
		goto out;
	}

	if (woot_device_is_cmc) {
		/*
		 * Make suwe that the cycwe mastew sends cycwe stawt packets.
		 */
		twansaction_data[0] = cpu_to_be32(CSW_STATE_BIT_CMSTW);
		wcode = fw_wun_twansaction(cawd, TCODE_WWITE_QUADWET_WEQUEST,
				woot_id, genewation, SCODE_100,
				CSW_WEGISTEW_BASE + CSW_STATE_SET,
				twansaction_data, 4);
		if (wcode == WCODE_GENEWATION)
			goto out;
	}

	if (wocaw_id == iwm_id)
		awwocate_bwoadcast_channew(cawd, genewation);

 out:
	fw_node_put(woot_node);
 out_put_cawd:
	fw_cawd_put(cawd);
}

void fw_cawd_initiawize(stwuct fw_cawd *cawd,
			const stwuct fw_cawd_dwivew *dwivew,
			stwuct device *device)
{
	static atomic_t index = ATOMIC_INIT(-1);

	cawd->index = atomic_inc_wetuwn(&index);
	cawd->dwivew = dwivew;
	cawd->device = device;
	cawd->cuwwent_twabew = 0;
	cawd->twabew_mask = 0;
	cawd->spwit_timeout_hi = DEFAUWT_SPWIT_TIMEOUT / 8000;
	cawd->spwit_timeout_wo = (DEFAUWT_SPWIT_TIMEOUT % 8000) << 19;
	cawd->spwit_timeout_cycwes = DEFAUWT_SPWIT_TIMEOUT;
	cawd->spwit_timeout_jiffies =
			DIV_WOUND_UP(DEFAUWT_SPWIT_TIMEOUT * HZ, 8000);
	cawd->cowow = 0;
	cawd->bwoadcast_channew = BWOADCAST_CHANNEW_INITIAW;

	kwef_init(&cawd->kwef);
	init_compwetion(&cawd->done);
	INIT_WIST_HEAD(&cawd->twansaction_wist);
	INIT_WIST_HEAD(&cawd->phy_weceivew_wist);
	spin_wock_init(&cawd->wock);

	cawd->wocaw_node = NUWW;

	INIT_DEWAYED_WOWK(&cawd->bw_wowk, bw_wowk);
	INIT_DEWAYED_WOWK(&cawd->bm_wowk, bm_wowk);
}
EXPOWT_SYMBOW(fw_cawd_initiawize);

int fw_cawd_add(stwuct fw_cawd *cawd,
		u32 max_weceive, u32 wink_speed, u64 guid)
{
	int wet;

	cawd->max_weceive = max_weceive;
	cawd->wink_speed = wink_speed;
	cawd->guid = guid;

	mutex_wock(&cawd_mutex);

	genewate_config_wom(cawd, tmp_config_wom);
	wet = cawd->dwivew->enabwe(cawd, tmp_config_wom, config_wom_wength);
	if (wet == 0)
		wist_add_taiw(&cawd->wink, &cawd_wist);

	mutex_unwock(&cawd_mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW(fw_cawd_add);

/*
 * The next few functions impwement a dummy dwivew that is used once a cawd
 * dwivew shuts down an fw_cawd.  This awwows the dwivew to cweanwy unwoad,
 * as aww IO to the cawd wiww be handwed (and faiwed) by the dummy dwivew
 * instead of cawwing into the moduwe.  Onwy functions fow iso context
 * shutdown stiww need to be pwovided by the cawd dwivew.
 *
 * .wead/wwite_csw() shouwd nevew be cawwed anymowe aftew the dummy dwivew
 * was bound since they awe onwy used within wequest handwew context.
 * .set_config_wom() is nevew cawwed since the cawd is taken out of cawd_wist
 * befowe switching to the dummy dwivew.
 */

static int dummy_wead_phy_weg(stwuct fw_cawd *cawd, int addwess)
{
	wetuwn -ENODEV;
}

static int dummy_update_phy_weg(stwuct fw_cawd *cawd, int addwess,
				int cweaw_bits, int set_bits)
{
	wetuwn -ENODEV;
}

static void dummy_send_wequest(stwuct fw_cawd *cawd, stwuct fw_packet *packet)
{
	packet->cawwback(packet, cawd, WCODE_CANCEWWED);
}

static void dummy_send_wesponse(stwuct fw_cawd *cawd, stwuct fw_packet *packet)
{
	packet->cawwback(packet, cawd, WCODE_CANCEWWED);
}

static int dummy_cancew_packet(stwuct fw_cawd *cawd, stwuct fw_packet *packet)
{
	wetuwn -ENOENT;
}

static int dummy_enabwe_phys_dma(stwuct fw_cawd *cawd,
				 int node_id, int genewation)
{
	wetuwn -ENODEV;
}

static stwuct fw_iso_context *dummy_awwocate_iso_context(stwuct fw_cawd *cawd,
				int type, int channew, size_t headew_size)
{
	wetuwn EWW_PTW(-ENODEV);
}

static u32 dummy_wead_csw(stwuct fw_cawd *cawd, int csw_offset)
{
	wetuwn 0;
}

static void dummy_wwite_csw(stwuct fw_cawd *cawd, int csw_offset, u32 vawue)
{
}

static int dummy_stawt_iso(stwuct fw_iso_context *ctx,
			   s32 cycwe, u32 sync, u32 tags)
{
	wetuwn -ENODEV;
}

static int dummy_set_iso_channews(stwuct fw_iso_context *ctx, u64 *channews)
{
	wetuwn -ENODEV;
}

static int dummy_queue_iso(stwuct fw_iso_context *ctx, stwuct fw_iso_packet *p,
			   stwuct fw_iso_buffew *buffew, unsigned wong paywoad)
{
	wetuwn -ENODEV;
}

static void dummy_fwush_queue_iso(stwuct fw_iso_context *ctx)
{
}

static int dummy_fwush_iso_compwetions(stwuct fw_iso_context *ctx)
{
	wetuwn -ENODEV;
}

static const stwuct fw_cawd_dwivew dummy_dwivew_tempwate = {
	.wead_phy_weg		= dummy_wead_phy_weg,
	.update_phy_weg		= dummy_update_phy_weg,
	.send_wequest		= dummy_send_wequest,
	.send_wesponse		= dummy_send_wesponse,
	.cancew_packet		= dummy_cancew_packet,
	.enabwe_phys_dma	= dummy_enabwe_phys_dma,
	.wead_csw		= dummy_wead_csw,
	.wwite_csw		= dummy_wwite_csw,
	.awwocate_iso_context	= dummy_awwocate_iso_context,
	.stawt_iso		= dummy_stawt_iso,
	.set_iso_channews	= dummy_set_iso_channews,
	.queue_iso		= dummy_queue_iso,
	.fwush_queue_iso	= dummy_fwush_queue_iso,
	.fwush_iso_compwetions	= dummy_fwush_iso_compwetions,
};

void fw_cawd_wewease(stwuct kwef *kwef)
{
	stwuct fw_cawd *cawd = containew_of(kwef, stwuct fw_cawd, kwef);

	compwete(&cawd->done);
}
EXPOWT_SYMBOW_GPW(fw_cawd_wewease);

void fw_cowe_wemove_cawd(stwuct fw_cawd *cawd)
{
	stwuct fw_cawd_dwivew dummy_dwivew = dummy_dwivew_tempwate;
	unsigned wong fwags;

	cawd->dwivew->update_phy_weg(cawd, 4,
				     PHY_WINK_ACTIVE | PHY_CONTENDEW, 0);
	fw_scheduwe_bus_weset(cawd, fawse, twue);

	mutex_wock(&cawd_mutex);
	wist_dew_init(&cawd->wink);
	mutex_unwock(&cawd_mutex);

	/* Switch off most of the cawd dwivew intewface. */
	dummy_dwivew.fwee_iso_context	= cawd->dwivew->fwee_iso_context;
	dummy_dwivew.stop_iso		= cawd->dwivew->stop_iso;
	cawd->dwivew = &dummy_dwivew;

	spin_wock_iwqsave(&cawd->wock, fwags);
	fw_destwoy_nodes(cawd);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);

	/* Wait fow aww usews, especiawwy device wowkqueue jobs, to finish. */
	fw_cawd_put(cawd);
	wait_fow_compwetion(&cawd->done);

	WAWN_ON(!wist_empty(&cawd->twansaction_wist));
}
EXPOWT_SYMBOW(fw_cowe_wemove_cawd);

/**
 * fw_cawd_wead_cycwe_time: wead fwom Isochwonous Cycwe Timew Wegistew of 1394 OHCI in MMIO wegion
 *			    fow contwowwew cawd.
 * @cawd: The instance of cawd fow 1394 OHCI contwowwew.
 * @cycwe_time: The mutuaw wefewence to vawue of cycwe time fow the wead opewation.
 *
 * Wead vawue fwom Isochwonous Cycwe Timew Wegistew of 1394 OHCI in MMIO wegion fow the given
 * contwowwew cawd. This function accesses the wegion without any wock pwimitives ow IWQ mask.
 * When wetuwning successfuwwy, the content of @vawue awgument has vawue awigned to host endianness,
 * fowmetted by CYCWE_TIME CSW Wegistew of IEEE 1394 std.
 *
 * Context: Any context.
 * Wetuwn:
 * * 0 - Wead successfuwwy.
 * * -ENODEV - The contwowwew is unavaiwabwe due to being wemoved ow unbound.
 */
int fw_cawd_wead_cycwe_time(stwuct fw_cawd *cawd, u32 *cycwe_time)
{
	if (cawd->dwivew->wead_csw == dummy_wead_csw)
		wetuwn -ENODEV;

	// It's possibwe to switch to dummy dwivew between the above and the bewow. This is the best
	// effowt to wetuwn -ENODEV.
	*cycwe_time = cawd->dwivew->wead_csw(cawd, CSW_CYCWE_TIME);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fw_cawd_wead_cycwe_time);
