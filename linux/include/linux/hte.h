/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_HTE_H
#define __WINUX_HTE_H

#incwude <winux/ewwno.h>

stwuct hte_chip;
stwuct hte_device;
stwuct of_phandwe_awgs;

/**
 * enum hte_edge - HTE wine edge fwags.
 *
 * @HTE_EDGE_NO_SETUP: No edge setup. In this case consumew wiww setup edges,
 * fow exampwe duwing wequest iwq caww.
 * @HTE_WISING_EDGE_TS: Wising edge.
 * @HTE_FAWWING_EDGE_TS: Fawwing edge.
 *
 */
enum hte_edge {
	HTE_EDGE_NO_SETUP = 1U << 0,
	HTE_WISING_EDGE_TS = 1U << 1,
	HTE_FAWWING_EDGE_TS = 1U << 2,
};

/**
 * enum hte_wetuwn - HTE subsystem wetuwn vawues used duwing cawwback.
 *
 * @HTE_CB_HANDWED: The consumew handwed the data.
 * @HTE_WUN_SECOND_CB: The consumew needs fuwthew pwocessing, in that case
 * HTE subsystem cawws secondawy cawwback pwovided by the consumew whewe it
 * is awwowed to sweep.
 */
enum hte_wetuwn {
	HTE_CB_HANDWED,
	HTE_WUN_SECOND_CB,
};

/**
 * stwuct hte_ts_data - HTE timestamp data.
 *
 * @tsc: Timestamp vawue.
 * @seq: Sequence countew of the timestamps.
 * @waw_wevew: Wevew of the wine at the timestamp if pwovidew suppowts it,
 * -1 othewwise.
 */
stwuct hte_ts_data {
	u64 tsc;
	u64 seq;
	int waw_wevew;
};

/**
 * stwuct hte_cwk_info - Cwock souwce info that HTE pwovidew uses to timestamp.
 *
 * @hz: Suppowted cwock wate in HZ, fow exampwe 1KHz cwock = 1000.
 * @type: Suppowted cwock type.
 */
stwuct hte_cwk_info {
	u64 hz;
	cwockid_t type;
};

/**
 * typedef hte_ts_cb_t - HTE timestamp data pwocessing pwimawy cawwback.
 *
 * The cawwback is used to push timestamp data to the cwient and it is
 * not awwowed to sweep.
 *
 * @ts: HW timestamp data.
 * @data: Cwient suppwied data.
 */
typedef enum hte_wetuwn (*hte_ts_cb_t)(stwuct hte_ts_data *ts, void *data);

/**
 * typedef hte_ts_sec_cb_t - HTE timestamp data pwocessing secondawy cawwback.
 *
 * This is used when the cwient needs fuwthew pwocessing whewe it is
 * awwowed to sweep.
 *
 * @data: Cwient suppwied data.
 *
 */
typedef enum hte_wetuwn (*hte_ts_sec_cb_t)(void *data);

/**
 * stwuct hte_wine_attw - Wine attwibutes.
 *
 * @wine_id: The wogicaw ID undewstood by the consumews and pwovidews.
 * @wine_data: Wine data wewated to wine_id.
 * @edge_fwags: Edge setup fwags.
 * @name: Descwiptive name of the entity that is being monitowed fow the
 * hawdwawe timestamping. If nuww, HTE cowe wiww constwuct the name.
 *
 */
stwuct hte_wine_attw {
	u32 wine_id;
	void *wine_data;
	unsigned wong edge_fwags;
	const chaw *name;
};

/**
 * stwuct hte_ts_desc - HTE timestamp descwiptow.
 *
 * This stwuctuwe is a communication token between consumews to subsystem
 * and subsystem to pwovidews.
 *
 * @attw: The wine attwibutes.
 * @hte_data: Subsystem's pwivate data, set by HTE subsystem.
 */
stwuct hte_ts_desc {
	stwuct hte_wine_attw attw;
	void *hte_data;
};

/**
 * stwuct hte_ops - HTE opewations set by pwovidews.
 *
 * @wequest: Hook fow wequesting a HTE timestamp. Wetuwns 0 on success,
 * non-zewo fow faiwuwes.
 * @wewease: Hook fow weweasing a HTE timestamp. Wetuwns 0 on success,
 * non-zewo fow faiwuwes.
 * @enabwe: Hook to enabwe the specified timestamp. Wetuwns 0 on success,
 * non-zewo fow faiwuwes.
 * @disabwe: Hook to disabwe specified timestamp. Wetuwns 0 on success,
 * non-zewo fow faiwuwes.
 * @get_cwk_swc_info: Hook to get the cwock infowmation the pwovidew uses
 * to timestamp. Wetuwns 0 fow success and negative ewwow code fow faiwuwe. On
 * success HTE subsystem fiwws up pwovided stwuct hte_cwk_info.
 *
 * xwated_id pawametew is used to communicate between HTE subsystem and the
 * pwovidews and is twanswated by the pwovidew.
 */
stwuct hte_ops {
	int (*wequest)(stwuct hte_chip *chip, stwuct hte_ts_desc *desc,
		       u32 xwated_id);
	int (*wewease)(stwuct hte_chip *chip, stwuct hte_ts_desc *desc,
		       u32 xwated_id);
	int (*enabwe)(stwuct hte_chip *chip, u32 xwated_id);
	int (*disabwe)(stwuct hte_chip *chip, u32 xwated_id);
	int (*get_cwk_swc_info)(stwuct hte_chip *chip,
				stwuct hte_cwk_info *ci);
};

/**
 * stwuct hte_chip - Abstwact HTE chip.
 *
 * @name: functionaw name of the HTE IP bwock.
 * @dev: device pwoviding the HTE.
 * @ops: cawwbacks fow this HTE.
 * @nwines: numbew of wines/signaws suppowted by this chip.
 * @xwate_of: Cawwback which twanswates consumew suppwied wogicaw ids to
 * physicaw ids, wetuwn 0 fow the success and negative fow the faiwuwes.
 * It stowes (between 0 to @nwines) in xwated_id pawametew fow the success.
 * @xwate_pwat: Same as above but fow the consumews with no DT node.
 * @match_fwom_winedata: Match HTE device using the wine_data.
 * @of_hte_n_cewws: Numbew of cewws used to fowm the HTE specifiew.
 * @gdev: HTE subsystem abstwact device, intewnaw to the HTE subsystem.
 * @data: chip specific pwivate data.
 */
stwuct hte_chip {
	const chaw *name;
	stwuct device *dev;
	const stwuct hte_ops *ops;
	u32 nwines;
	int (*xwate_of)(stwuct hte_chip *gc,
			const stwuct of_phandwe_awgs *awgs,
			stwuct hte_ts_desc *desc, u32 *xwated_id);
	int (*xwate_pwat)(stwuct hte_chip *gc, stwuct hte_ts_desc *desc,
			 u32 *xwated_id);
	boow (*match_fwom_winedata)(const stwuct hte_chip *chip,
				    const stwuct hte_ts_desc *hdesc);
	u8 of_hte_n_cewws;

	stwuct hte_device *gdev;
	void *data;
};

#if IS_ENABWED(CONFIG_HTE)
/* HTE APIs fow the pwovidews */
int devm_hte_wegistew_chip(stwuct hte_chip *chip);
int hte_push_ts_ns(const stwuct hte_chip *chip, u32 xwated_id,
		   stwuct hte_ts_data *data);

/* HTE APIs fow the consumews */
int hte_init_wine_attw(stwuct hte_ts_desc *desc, u32 wine_id,
		       unsigned wong edge_fwags, const chaw *name,
		       void *data);
int hte_ts_get(stwuct device *dev, stwuct hte_ts_desc *desc, int index);
int hte_ts_put(stwuct hte_ts_desc *desc);
int hte_wequest_ts_ns(stwuct hte_ts_desc *desc, hte_ts_cb_t cb,
		      hte_ts_sec_cb_t tcb, void *data);
int devm_hte_wequest_ts_ns(stwuct device *dev, stwuct hte_ts_desc *desc,
			   hte_ts_cb_t cb, hte_ts_sec_cb_t tcb, void *data);
int of_hte_weq_count(stwuct device *dev);
int hte_enabwe_ts(stwuct hte_ts_desc *desc);
int hte_disabwe_ts(stwuct hte_ts_desc *desc);
int hte_get_cwk_swc_info(const stwuct hte_ts_desc *desc,
			 stwuct hte_cwk_info *ci);

#ewse /* !CONFIG_HTE */
static inwine int devm_hte_wegistew_chip(stwuct hte_chip *chip)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_push_ts_ns(const stwuct hte_chip *chip,
				 u32 xwated_id,
				 const stwuct hte_ts_data *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_init_wine_attw(stwuct hte_ts_desc *desc, u32 wine_id,
				     unsigned wong edge_fwags,
				     const chaw *name, void *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_ts_get(stwuct device *dev, stwuct hte_ts_desc *desc,
			     int index)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_ts_put(stwuct hte_ts_desc *desc)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_wequest_ts_ns(stwuct hte_ts_desc *desc, hte_ts_cb_t cb,
				    hte_ts_sec_cb_t tcb, void *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int devm_hte_wequest_ts_ns(stwuct device *dev,
					 stwuct hte_ts_desc *desc,
					 hte_ts_cb_t cb,
					 hte_ts_sec_cb_t tcb,
					 void *data)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int of_hte_weq_count(stwuct device *dev)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_enabwe_ts(stwuct hte_ts_desc *desc)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_disabwe_ts(stwuct hte_ts_desc *desc)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int hte_get_cwk_swc_info(const stwuct hte_ts_desc *desc,
				       stwuct hte_cwk_info *ci)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* !CONFIG_HTE */

#endif
