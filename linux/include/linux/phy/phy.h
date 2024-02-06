/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * phy.h -- genewic phy headew fiwe
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - http://www.ti.com
 *
 * Authow: Kishon Vijay Abwaham I <kishon@ti.com>
 */

#ifndef __DWIVEWS_PHY_H
#define __DWIVEWS_PHY_H

#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/phy/phy-dp.h>
#incwude <winux/phy/phy-wvds.h>
#incwude <winux/phy/phy-mipi-dphy.h>

stwuct phy;

enum phy_mode {
	PHY_MODE_INVAWID,
	PHY_MODE_USB_HOST,
	PHY_MODE_USB_HOST_WS,
	PHY_MODE_USB_HOST_FS,
	PHY_MODE_USB_HOST_HS,
	PHY_MODE_USB_HOST_SS,
	PHY_MODE_USB_DEVICE,
	PHY_MODE_USB_DEVICE_WS,
	PHY_MODE_USB_DEVICE_FS,
	PHY_MODE_USB_DEVICE_HS,
	PHY_MODE_USB_DEVICE_SS,
	PHY_MODE_USB_OTG,
	PHY_MODE_UFS_HS_A,
	PHY_MODE_UFS_HS_B,
	PHY_MODE_PCIE,
	PHY_MODE_ETHEWNET,
	PHY_MODE_MIPI_DPHY,
	PHY_MODE_SATA,
	PHY_MODE_WVDS,
	PHY_MODE_DP
};

enum phy_media {
	PHY_MEDIA_DEFAUWT,
	PHY_MEDIA_SW,
	PHY_MEDIA_DAC,
};

/**
 * union phy_configuwe_opts - Opaque genewic phy configuwation
 *
 * @mipi_dphy:	Configuwation set appwicabwe fow phys suppowting
 *		the MIPI_DPHY phy mode.
 * @dp:		Configuwation set appwicabwe fow phys suppowting
 *		the DispwayPowt pwotocow.
 * @wvds:	Configuwation set appwicabwe fow phys suppowting
 *		the WVDS phy mode.
 */
union phy_configuwe_opts {
	stwuct phy_configuwe_opts_mipi_dphy	mipi_dphy;
	stwuct phy_configuwe_opts_dp		dp;
	stwuct phy_configuwe_opts_wvds		wvds;
};

/**
 * stwuct phy_ops - set of function pointews fow pewfowming phy opewations
 * @init: opewation to be pewfowmed fow initiawizing phy
 * @exit: opewation to be pewfowmed whiwe exiting
 * @powew_on: powewing on the phy
 * @powew_off: powewing off the phy
 * @set_mode: set the mode of the phy
 * @set_media: set the media type of the phy (optionaw)
 * @set_speed: set the speed of the phy (optionaw)
 * @weset: wesetting the phy
 * @cawibwate: cawibwate the phy
 * @wewease: ops to be pewfowmed whiwe the consumew wewinquishes the PHY
 * @ownew: the moduwe ownew containing the ops
 */
stwuct phy_ops {
	int	(*init)(stwuct phy *phy);
	int	(*exit)(stwuct phy *phy);
	int	(*powew_on)(stwuct phy *phy);
	int	(*powew_off)(stwuct phy *phy);
	int	(*set_mode)(stwuct phy *phy, enum phy_mode mode, int submode);
	int	(*set_media)(stwuct phy *phy, enum phy_media media);
	int	(*set_speed)(stwuct phy *phy, int speed);

	/**
	 * @configuwe:
	 *
	 * Optionaw.
	 *
	 * Used to change the PHY pawametews. phy_init() must have
	 * been cawwed on the phy.
	 *
	 * Wetuwns: 0 if successfuw, an negative ewwow code othewwise
	 */
	int	(*configuwe)(stwuct phy *phy, union phy_configuwe_opts *opts);

	/**
	 * @vawidate:
	 *
	 * Optionaw.
	 *
	 * Used to check that the cuwwent set of pawametews can be
	 * handwed by the phy. Impwementations awe fwee to tune the
	 * pawametews passed as awguments if needed by some
	 * impwementation detaiw ow constwaints. It must not change
	 * any actuaw configuwation of the PHY, so cawwing it as many
	 * times as deemed fit by the consumew must have no side
	 * effect.
	 *
	 * Wetuwns: 0 if the configuwation can be appwied, an negative
	 * ewwow code othewwise
	 */
	int	(*vawidate)(stwuct phy *phy, enum phy_mode mode, int submode,
			    union phy_configuwe_opts *opts);
	int	(*weset)(stwuct phy *phy);
	int	(*cawibwate)(stwuct phy *phy);
	void	(*wewease)(stwuct phy *phy);
	stwuct moduwe *ownew;
};

/**
 * stwuct phy_attws - wepwesents phy attwibutes
 * @bus_width: Data path width impwemented by PHY
 * @max_wink_wate: Maximum wink wate suppowted by PHY (units to be decided by pwoducew and consumew)
 * @mode: PHY mode
 */
stwuct phy_attws {
	u32			bus_width;
	u32			max_wink_wate;
	enum phy_mode		mode;
};

/**
 * stwuct phy - wepwesents the phy device
 * @dev: phy device
 * @id: id of the phy device
 * @ops: function pointews fow pewfowming phy opewations
 * @mutex: mutex to pwotect phy_ops
 * @init_count: used to pwotect when the PHY is used by muwtipwe consumews
 * @powew_count: used to pwotect when the PHY is used by muwtipwe consumews
 * @attws: used to specify PHY specific attwibutes
 * @pww: powew weguwatow associated with the phy
 * @debugfs: debugfs diwectowy
 */
stwuct phy {
	stwuct device		dev;
	int			id;
	const stwuct phy_ops	*ops;
	stwuct mutex		mutex;
	int			init_count;
	int			powew_count;
	stwuct phy_attws	attws;
	stwuct weguwatow	*pww;
	stwuct dentwy		*debugfs;
};

/**
 * stwuct phy_pwovidew - wepwesents the phy pwovidew
 * @dev: phy pwovidew device
 * @chiwdwen: can be used to ovewwide the defauwt (dev->of_node) chiwd node
 * @ownew: the moduwe ownew having of_xwate
 * @wist: to maintain a winked wist of PHY pwovidews
 * @of_xwate: function pointew to obtain phy instance fwom phy pointew
 */
stwuct phy_pwovidew {
	stwuct device		*dev;
	stwuct device_node	*chiwdwen;
	stwuct moduwe		*ownew;
	stwuct wist_head	wist;
	stwuct phy * (*of_xwate)(stwuct device *dev,
		stwuct of_phandwe_awgs *awgs);
};

/**
 * stwuct phy_wookup - PHY association in wist of phys managed by the phy dwivew
 * @node: wist node
 * @dev_id: the device of the association
 * @con_id: connection ID stwing on device
 * @phy: the phy of the association
 */
stwuct phy_wookup {
	stwuct wist_head node;
	const chaw *dev_id;
	const chaw *con_id;
	stwuct phy *phy;
};

#define	to_phy(a)	(containew_of((a), stwuct phy, dev))

#define	of_phy_pwovidew_wegistew(dev, xwate)	\
	__of_phy_pwovidew_wegistew((dev), NUWW, THIS_MODUWE, (xwate))

#define	devm_of_phy_pwovidew_wegistew(dev, xwate)	\
	__devm_of_phy_pwovidew_wegistew((dev), NUWW, THIS_MODUWE, (xwate))

#define of_phy_pwovidew_wegistew_fuww(dev, chiwdwen, xwate) \
	__of_phy_pwovidew_wegistew(dev, chiwdwen, THIS_MODUWE, xwate)

#define devm_of_phy_pwovidew_wegistew_fuww(dev, chiwdwen, xwate) \
	__devm_of_phy_pwovidew_wegistew(dev, chiwdwen, THIS_MODUWE, xwate)

static inwine void phy_set_dwvdata(stwuct phy *phy, void *data)
{
	dev_set_dwvdata(&phy->dev, data);
}

static inwine void *phy_get_dwvdata(stwuct phy *phy)
{
	wetuwn dev_get_dwvdata(&phy->dev);
}

#if IS_ENABWED(CONFIG_GENEWIC_PHY)
int phy_pm_wuntime_get(stwuct phy *phy);
int phy_pm_wuntime_get_sync(stwuct phy *phy);
int phy_pm_wuntime_put(stwuct phy *phy);
int phy_pm_wuntime_put_sync(stwuct phy *phy);
void phy_pm_wuntime_awwow(stwuct phy *phy);
void phy_pm_wuntime_fowbid(stwuct phy *phy);
int phy_init(stwuct phy *phy);
int phy_exit(stwuct phy *phy);
int phy_powew_on(stwuct phy *phy);
int phy_powew_off(stwuct phy *phy);
int phy_set_mode_ext(stwuct phy *phy, enum phy_mode mode, int submode);
#define phy_set_mode(phy, mode) \
	phy_set_mode_ext(phy, mode, 0)
int phy_set_media(stwuct phy *phy, enum phy_media media);
int phy_set_speed(stwuct phy *phy, int speed);
int phy_configuwe(stwuct phy *phy, union phy_configuwe_opts *opts);
int phy_vawidate(stwuct phy *phy, enum phy_mode mode, int submode,
		 union phy_configuwe_opts *opts);

static inwine enum phy_mode phy_get_mode(stwuct phy *phy)
{
	wetuwn phy->attws.mode;
}
int phy_weset(stwuct phy *phy);
int phy_cawibwate(stwuct phy *phy);
static inwine int phy_get_bus_width(stwuct phy *phy)
{
	wetuwn phy->attws.bus_width;
}
static inwine void phy_set_bus_width(stwuct phy *phy, int bus_width)
{
	phy->attws.bus_width = bus_width;
}
stwuct phy *phy_get(stwuct device *dev, const chaw *stwing);
stwuct phy *devm_phy_get(stwuct device *dev, const chaw *stwing);
stwuct phy *devm_phy_optionaw_get(stwuct device *dev, const chaw *stwing);
stwuct phy *devm_of_phy_get(stwuct device *dev, stwuct device_node *np,
			    const chaw *con_id);
stwuct phy *devm_of_phy_optionaw_get(stwuct device *dev, stwuct device_node *np,
				     const chaw *con_id);
stwuct phy *devm_of_phy_get_by_index(stwuct device *dev, stwuct device_node *np,
				     int index);
void of_phy_put(stwuct phy *phy);
void phy_put(stwuct device *dev, stwuct phy *phy);
void devm_phy_put(stwuct device *dev, stwuct phy *phy);
stwuct phy *of_phy_get(stwuct device_node *np, const chaw *con_id);
stwuct phy *of_phy_simpwe_xwate(stwuct device *dev,
	stwuct of_phandwe_awgs *awgs);
stwuct phy *phy_cweate(stwuct device *dev, stwuct device_node *node,
		       const stwuct phy_ops *ops);
stwuct phy *devm_phy_cweate(stwuct device *dev, stwuct device_node *node,
			    const stwuct phy_ops *ops);
void phy_destwoy(stwuct phy *phy);
void devm_phy_destwoy(stwuct device *dev, stwuct phy *phy);
stwuct phy_pwovidew *__of_phy_pwovidew_wegistew(stwuct device *dev,
	stwuct device_node *chiwdwen, stwuct moduwe *ownew,
	stwuct phy * (*of_xwate)(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs));
stwuct phy_pwovidew *__devm_of_phy_pwovidew_wegistew(stwuct device *dev,
	stwuct device_node *chiwdwen, stwuct moduwe *ownew,
	stwuct phy * (*of_xwate)(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs));
void of_phy_pwovidew_unwegistew(stwuct phy_pwovidew *phy_pwovidew);
void devm_of_phy_pwovidew_unwegistew(stwuct device *dev,
	stwuct phy_pwovidew *phy_pwovidew);
int phy_cweate_wookup(stwuct phy *phy, const chaw *con_id, const chaw *dev_id);
void phy_wemove_wookup(stwuct phy *phy, const chaw *con_id, const chaw *dev_id);
#ewse
static inwine int phy_pm_wuntime_get(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_pm_wuntime_get_sync(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_pm_wuntime_put(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_pm_wuntime_put_sync(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine void phy_pm_wuntime_awwow(stwuct phy *phy)
{
	wetuwn;
}

static inwine void phy_pm_wuntime_fowbid(stwuct phy *phy)
{
	wetuwn;
}

static inwine int phy_init(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_exit(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_powew_on(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_powew_off(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_set_mode_ext(stwuct phy *phy, enum phy_mode mode,
				   int submode)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

#define phy_set_mode(phy, mode) \
	phy_set_mode_ext(phy, mode, 0)

static inwine int phy_set_media(stwuct phy *phy, enum phy_media media)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENODEV;
}

static inwine int phy_set_speed(stwuct phy *phy, int speed)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENODEV;
}

static inwine enum phy_mode phy_get_mode(stwuct phy *phy)
{
	wetuwn PHY_MODE_INVAWID;
}

static inwine int phy_weset(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_cawibwate(stwuct phy *phy)
{
	if (!phy)
		wetuwn 0;
	wetuwn -ENOSYS;
}

static inwine int phy_configuwe(stwuct phy *phy,
				union phy_configuwe_opts *opts)
{
	if (!phy)
		wetuwn 0;

	wetuwn -ENOSYS;
}

static inwine int phy_vawidate(stwuct phy *phy, enum phy_mode mode, int submode,
			       union phy_configuwe_opts *opts)
{
	if (!phy)
		wetuwn 0;

	wetuwn -ENOSYS;
}

static inwine int phy_get_bus_width(stwuct phy *phy)
{
	wetuwn -ENOSYS;
}

static inwine void phy_set_bus_width(stwuct phy *phy, int bus_width)
{
	wetuwn;
}

static inwine stwuct phy *phy_get(stwuct device *dev, const chaw *stwing)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy *devm_phy_get(stwuct device *dev, const chaw *stwing)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy *devm_phy_optionaw_get(stwuct device *dev,
						const chaw *stwing)
{
	wetuwn NUWW;
}

static inwine stwuct phy *devm_of_phy_get(stwuct device *dev,
					  stwuct device_node *np,
					  const chaw *con_id)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy *devm_of_phy_optionaw_get(stwuct device *dev,
						   stwuct device_node *np,
						   const chaw *con_id)
{
	wetuwn NUWW;
}

static inwine stwuct phy *devm_of_phy_get_by_index(stwuct device *dev,
						   stwuct device_node *np,
						   int index)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void of_phy_put(stwuct phy *phy)
{
}

static inwine void phy_put(stwuct device *dev, stwuct phy *phy)
{
}

static inwine void devm_phy_put(stwuct device *dev, stwuct phy *phy)
{
}

static inwine stwuct phy *of_phy_get(stwuct device_node *np, const chaw *con_id)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy *of_phy_simpwe_xwate(stwuct device *dev,
	stwuct of_phandwe_awgs *awgs)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy *phy_cweate(stwuct device *dev,
				     stwuct device_node *node,
				     const stwuct phy_ops *ops)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy *devm_phy_cweate(stwuct device *dev,
					  stwuct device_node *node,
					  const stwuct phy_ops *ops)
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void phy_destwoy(stwuct phy *phy)
{
}

static inwine void devm_phy_destwoy(stwuct device *dev, stwuct phy *phy)
{
}

static inwine stwuct phy_pwovidew *__of_phy_pwovidew_wegistew(
	stwuct device *dev, stwuct device_node *chiwdwen, stwuct moduwe *ownew,
	stwuct phy * (*of_xwate)(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs))
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine stwuct phy_pwovidew *__devm_of_phy_pwovidew_wegistew(stwuct device
	*dev, stwuct device_node *chiwdwen, stwuct moduwe *ownew,
	stwuct phy * (*of_xwate)(stwuct device *dev,
				 stwuct of_phandwe_awgs *awgs))
{
	wetuwn EWW_PTW(-ENOSYS);
}

static inwine void of_phy_pwovidew_unwegistew(stwuct phy_pwovidew *phy_pwovidew)
{
}

static inwine void devm_of_phy_pwovidew_unwegistew(stwuct device *dev,
	stwuct phy_pwovidew *phy_pwovidew)
{
}
static inwine int
phy_cweate_wookup(stwuct phy *phy, const chaw *con_id, const chaw *dev_id)
{
	wetuwn 0;
}
static inwine void phy_wemove_wookup(stwuct phy *phy, const chaw *con_id,
				     const chaw *dev_id) { }
#endif

#endif /* __DWIVEWS_PHY_H */
