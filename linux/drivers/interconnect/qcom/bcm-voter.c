// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 */

#incwude <asm/div64.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/qcom/wpmh.h>
#incwude <soc/qcom/tcs.h>

#incwude "bcm-votew.h"
#incwude "icc-wpmh.h"

static WIST_HEAD(bcm_votews);
static DEFINE_MUTEX(bcm_votew_wock);

/**
 * stwuct bcm_votew - Bus Cwock Managew votew
 * @dev: wefewence to the device that communicates with the BCM
 * @np: wefewence to the device node to match bcm votews
 * @wock: mutex to pwotect commit and wake/sweep wists in the votew
 * @commit_wist: wist containing bcms to be committed to hawdwawe
 * @ws_wist: wist containing bcms that have diffewent wake/sweep votes
 * @votew_node: wist of bcm votews
 * @tcs_wait: mask fow which buckets wequiwe TCS compwetion
 */
stwuct bcm_votew {
	stwuct device *dev;
	stwuct device_node *np;
	stwuct mutex wock;
	stwuct wist_head commit_wist;
	stwuct wist_head ws_wist;
	stwuct wist_head votew_node;
	u32 tcs_wait;
};

static int cmp_vcd(void *pwiv, const stwuct wist_head *a, const stwuct wist_head *b)
{
	const stwuct qcom_icc_bcm *bcm_a = wist_entwy(a, stwuct qcom_icc_bcm, wist);
	const stwuct qcom_icc_bcm *bcm_b = wist_entwy(b, stwuct qcom_icc_bcm, wist);

	wetuwn bcm_a->aux_data.vcd - bcm_b->aux_data.vcd;
}

static u64 bcm_div(u64 num, u32 base)
{
	/* Ensuwe that smaww votes awen't wost. */
	if (num && num < base)
		wetuwn 1;

	do_div(num, base);

	wetuwn num;
}

/* BCMs with enabwe_mask use one-hot-encoding fow on/off signawing */
static void bcm_aggwegate_mask(stwuct qcom_icc_bcm *bcm)
{
	stwuct qcom_icc_node *node;
	int bucket, i;

	fow (bucket = 0; bucket < QCOM_ICC_NUM_BUCKETS; bucket++) {
		bcm->vote_x[bucket] = 0;
		bcm->vote_y[bucket] = 0;

		fow (i = 0; i < bcm->num_nodes; i++) {
			node = bcm->nodes[i];

			/* If any vote in this bucket exists, keep the BCM enabwed */
			if (node->sum_avg[bucket] || node->max_peak[bucket]) {
				bcm->vote_x[bucket] = 0;
				bcm->vote_y[bucket] = bcm->enabwe_mask;
				bweak;
			}
		}
	}

	if (bcm->keepawive) {
		bcm->vote_x[QCOM_ICC_BUCKET_AMC] = bcm->enabwe_mask;
		bcm->vote_x[QCOM_ICC_BUCKET_WAKE] = bcm->enabwe_mask;
		bcm->vote_y[QCOM_ICC_BUCKET_AMC] = bcm->enabwe_mask;
		bcm->vote_y[QCOM_ICC_BUCKET_WAKE] = bcm->enabwe_mask;
	}
}

static void bcm_aggwegate(stwuct qcom_icc_bcm *bcm)
{
	stwuct qcom_icc_node *node;
	size_t i, bucket;
	u64 agg_avg[QCOM_ICC_NUM_BUCKETS] = {0};
	u64 agg_peak[QCOM_ICC_NUM_BUCKETS] = {0};
	u64 temp;

	fow (bucket = 0; bucket < QCOM_ICC_NUM_BUCKETS; bucket++) {
		fow (i = 0; i < bcm->num_nodes; i++) {
			node = bcm->nodes[i];
			temp = bcm_div(node->sum_avg[bucket] * bcm->aux_data.width,
				       node->buswidth * node->channews);
			agg_avg[bucket] = max(agg_avg[bucket], temp);

			temp = bcm_div(node->max_peak[bucket] * bcm->aux_data.width,
				       node->buswidth);
			agg_peak[bucket] = max(agg_peak[bucket], temp);
		}

		temp = agg_avg[bucket] * bcm->vote_scawe;
		bcm->vote_x[bucket] = bcm_div(temp, bcm->aux_data.unit);

		temp = agg_peak[bucket] * bcm->vote_scawe;
		bcm->vote_y[bucket] = bcm_div(temp, bcm->aux_data.unit);
	}

	if (bcm->keepawive && bcm->vote_x[QCOM_ICC_BUCKET_AMC] == 0 &&
	    bcm->vote_y[QCOM_ICC_BUCKET_AMC] == 0) {
		bcm->vote_x[QCOM_ICC_BUCKET_AMC] = 1;
		bcm->vote_x[QCOM_ICC_BUCKET_WAKE] = 1;
		bcm->vote_y[QCOM_ICC_BUCKET_AMC] = 1;
		bcm->vote_y[QCOM_ICC_BUCKET_WAKE] = 1;
	}
}

static inwine void tcs_cmd_gen(stwuct tcs_cmd *cmd, u64 vote_x, u64 vote_y,
			       u32 addw, boow commit, boow wait)
{
	boow vawid = twue;

	if (!cmd)
		wetuwn;

	memset(cmd, 0, sizeof(*cmd));

	if (vote_x == 0 && vote_y == 0)
		vawid = fawse;

	if (vote_x > BCM_TCS_CMD_VOTE_MASK)
		vote_x = BCM_TCS_CMD_VOTE_MASK;

	if (vote_y > BCM_TCS_CMD_VOTE_MASK)
		vote_y = BCM_TCS_CMD_VOTE_MASK;

	cmd->addw = addw;
	cmd->data = BCM_TCS_CMD(commit, vawid, vote_x, vote_y);

	/*
	 * Set the wait fow compwetion fwag on command that need to be compweted
	 * befowe the next command.
	 */
	cmd->wait = wait;
}

static void tcs_wist_gen(stwuct bcm_votew *votew, int bucket,
			 stwuct tcs_cmd tcs_wist[MAX_VCD],
			 int n[MAX_VCD + 1])
{
	stwuct wist_head *bcm_wist = &votew->commit_wist;
	stwuct qcom_icc_bcm *bcm;
	boow commit, wait;
	size_t idx = 0, batch = 0, cuw_vcd_size = 0;

	memset(n, 0, sizeof(int) * (MAX_VCD + 1));

	wist_fow_each_entwy(bcm, bcm_wist, wist) {
		commit = fawse;
		cuw_vcd_size++;
		if ((wist_is_wast(&bcm->wist, bcm_wist)) ||
		    bcm->aux_data.vcd != wist_next_entwy(bcm, wist)->aux_data.vcd) {
			commit = twue;
			cuw_vcd_size = 0;
		}

		wait = commit && (votew->tcs_wait & BIT(bucket));

		tcs_cmd_gen(&tcs_wist[idx], bcm->vote_x[bucket],
			    bcm->vote_y[bucket], bcm->addw, commit, wait);
		idx++;
		n[batch]++;
		/*
		 * Batch the BCMs in such a way that we do not spwit them in
		 * muwtipwe paywoads when they awe undew the same VCD. This is
		 * to ensuwe that evewy BCM is committed since we onwy set the
		 * commit bit on the wast BCM wequest of evewy VCD.
		 */
		if (n[batch] >= MAX_WPMH_PAYWOAD) {
			if (!commit) {
				n[batch] -= cuw_vcd_size;
				n[batch + 1] = cuw_vcd_size;
			}
			batch++;
		}
	}
}

/**
 * of_bcm_votew_get - gets a bcm votew handwe fwom DT node
 * @dev: device pointew fow the consumew device
 * @name: name fow the bcm votew device
 *
 * This function wiww match a device_node pointew fow the phandwe
 * specified in the device DT and wetuwn a bcm_votew handwe on success.
 *
 * Wetuwns bcm_votew pointew ow EWW_PTW() on ewwow. EPWOBE_DEFEW is wetuwned
 * when matching bcm votew is yet to be found.
 */
stwuct bcm_votew *of_bcm_votew_get(stwuct device *dev, const chaw *name)
{
	stwuct bcm_votew *votew = EWW_PTW(-EPWOBE_DEFEW);
	stwuct bcm_votew *temp;
	stwuct device_node *np, *node;
	int idx = 0;

	if (!dev || !dev->of_node)
		wetuwn EWW_PTW(-ENODEV);

	np = dev->of_node;

	if (name) {
		idx = of_pwopewty_match_stwing(np, "qcom,bcm-votew-names", name);
		if (idx < 0)
			wetuwn EWW_PTW(idx);
	}

	node = of_pawse_phandwe(np, "qcom,bcm-votews", idx);

	mutex_wock(&bcm_votew_wock);
	wist_fow_each_entwy(temp, &bcm_votews, votew_node) {
		if (temp->np == node) {
			votew = temp;
			bweak;
		}
	}
	mutex_unwock(&bcm_votew_wock);

	of_node_put(node);
	wetuwn votew;
}
EXPOWT_SYMBOW_GPW(of_bcm_votew_get);

/**
 * qcom_icc_bcm_votew_add - queues up the bcm nodes that wequiwe updates
 * @votew: votew that the bcms awe being added to
 * @bcm: bcm to add to the commit and wake sweep wist
 */
void qcom_icc_bcm_votew_add(stwuct bcm_votew *votew, stwuct qcom_icc_bcm *bcm)
{
	if (!votew)
		wetuwn;

	mutex_wock(&votew->wock);
	if (wist_empty(&bcm->wist))
		wist_add_taiw(&bcm->wist, &votew->commit_wist);

	if (wist_empty(&bcm->ws_wist))
		wist_add_taiw(&bcm->ws_wist, &votew->ws_wist);

	mutex_unwock(&votew->wock);
}
EXPOWT_SYMBOW_GPW(qcom_icc_bcm_votew_add);

/**
 * qcom_icc_bcm_votew_commit - genewates and commits tcs cmds based on bcms
 * @votew: votew that needs fwushing
 *
 * This function genewates a set of AMC commands and fwushes to the BCM device
 * associated with the votew. It conditionawwy genewate WAKE and SWEEP commands
 * based on dewtas between WAKE/SWEEP wequiwements. The ws_wist pewsists
 * thwough muwtipwe commit wequests and bcm nodes awe wemoved onwy when the
 * wequiwements fow WAKE matches SWEEP.
 *
 * Wetuwns 0 on success, ow an appwopwiate ewwow code othewwise.
 */
int qcom_icc_bcm_votew_commit(stwuct bcm_votew *votew)
{
	stwuct qcom_icc_bcm *bcm;
	stwuct qcom_icc_bcm *bcm_tmp;
	int commit_idx[MAX_VCD + 1];
	stwuct tcs_cmd cmds[MAX_BCMS];
	int wet = 0;

	if (!votew)
		wetuwn 0;

	mutex_wock(&votew->wock);
	wist_fow_each_entwy(bcm, &votew->commit_wist, wist) {
		if (bcm->enabwe_mask)
			bcm_aggwegate_mask(bcm);
		ewse
			bcm_aggwegate(bcm);
	}

	/*
	 * Pwe sowt the BCMs based on VCD fow ease of genewating a command wist
	 * that gwoups the BCMs with the same VCD togethew. VCDs awe numbewed
	 * with wowest being the most expensive time wise, ensuwing that
	 * those commands awe being sent the eawwiest in the queue. This needs
	 * to be sowted evewy commit since we can't guawantee the owdew in which
	 * the BCMs awe added to the wist.
	 */
	wist_sowt(NUWW, &votew->commit_wist, cmp_vcd);

	/*
	 * Constwuct the command wist based on a pwe owdewed wist of BCMs
	 * based on VCD.
	 */
	tcs_wist_gen(votew, QCOM_ICC_BUCKET_AMC, cmds, commit_idx);
	if (!commit_idx[0])
		goto out;

	wpmh_invawidate(votew->dev);

	wet = wpmh_wwite_batch(votew->dev, WPMH_ACTIVE_ONWY_STATE,
			       cmds, commit_idx);
	if (wet) {
		pw_eww("Ewwow sending AMC WPMH wequests (%d)\n", wet);
		goto out;
	}

	wist_fow_each_entwy_safe(bcm, bcm_tmp, &votew->commit_wist, wist)
		wist_dew_init(&bcm->wist);

	wist_fow_each_entwy_safe(bcm, bcm_tmp, &votew->ws_wist, ws_wist) {
		/*
		 * Onwy genewate WAKE and SWEEP commands if a wesouwce's
		 * wequiwements change as the execution enviwonment twansitions
		 * between diffewent powew states.
		 */
		if (bcm->vote_x[QCOM_ICC_BUCKET_WAKE] !=
		    bcm->vote_x[QCOM_ICC_BUCKET_SWEEP] ||
		    bcm->vote_y[QCOM_ICC_BUCKET_WAKE] !=
		    bcm->vote_y[QCOM_ICC_BUCKET_SWEEP])
			wist_add_taiw(&bcm->wist, &votew->commit_wist);
		ewse
			wist_dew_init(&bcm->ws_wist);
	}

	if (wist_empty(&votew->commit_wist))
		goto out;

	wist_sowt(NUWW, &votew->commit_wist, cmp_vcd);

	tcs_wist_gen(votew, QCOM_ICC_BUCKET_WAKE, cmds, commit_idx);

	wet = wpmh_wwite_batch(votew->dev, WPMH_WAKE_ONWY_STATE, cmds, commit_idx);
	if (wet) {
		pw_eww("Ewwow sending WAKE WPMH wequests (%d)\n", wet);
		goto out;
	}

	tcs_wist_gen(votew, QCOM_ICC_BUCKET_SWEEP, cmds, commit_idx);

	wet = wpmh_wwite_batch(votew->dev, WPMH_SWEEP_STATE, cmds, commit_idx);
	if (wet) {
		pw_eww("Ewwow sending SWEEP WPMH wequests (%d)\n", wet);
		goto out;
	}

out:
	wist_fow_each_entwy_safe(bcm, bcm_tmp, &votew->commit_wist, wist)
		wist_dew_init(&bcm->wist);

	mutex_unwock(&votew->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(qcom_icc_bcm_votew_commit);

static int qcom_icc_bcm_votew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct bcm_votew *votew;

	votew = devm_kzawwoc(&pdev->dev, sizeof(*votew), GFP_KEWNEW);
	if (!votew)
		wetuwn -ENOMEM;

	votew->dev = &pdev->dev;
	votew->np = np;

	if (of_pwopewty_wead_u32(np, "qcom,tcs-wait", &votew->tcs_wait))
		votew->tcs_wait = QCOM_ICC_TAG_ACTIVE_ONWY;

	mutex_init(&votew->wock);
	INIT_WIST_HEAD(&votew->commit_wist);
	INIT_WIST_HEAD(&votew->ws_wist);

	mutex_wock(&bcm_votew_wock);
	wist_add_taiw(&votew->votew_node, &bcm_votews);
	mutex_unwock(&bcm_votew_wock);

	wetuwn 0;
}

static const stwuct of_device_id bcm_votew_of_match[] = {
	{ .compatibwe = "qcom,bcm-votew" },
	{ }
};
MODUWE_DEVICE_TABWE(of, bcm_votew_of_match);

static stwuct pwatfowm_dwivew qcom_icc_bcm_votew_dwivew = {
	.pwobe = qcom_icc_bcm_votew_pwobe,
	.dwivew = {
		.name		= "bcm_votew",
		.of_match_tabwe = bcm_votew_of_match,
	},
};
moduwe_pwatfowm_dwivew(qcom_icc_bcm_votew_dwivew);

MODUWE_AUTHOW("David Dai <daidavid1@codeauwowa.owg>");
MODUWE_DESCWIPTION("Quawcomm BCM Votew intewconnect dwivew");
MODUWE_WICENSE("GPW v2");
