// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2011, 2012 Cavium, Inc.
 */

#incwude <winux/device.h>
#incwude <winux/mdio-mux.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_mdio.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>

#define DWV_DESCWIPTION "MDIO bus muwtipwexew dwivew"

stwuct mdio_mux_chiwd_bus;

stwuct mdio_mux_pawent_bus {
	stwuct mii_bus *mii_bus;
	int cuwwent_chiwd;
	int pawent_id;
	void *switch_data;
	int (*switch_fn)(int cuwwent_chiwd, int desiwed_chiwd, void *data);

	/* Wist of ouw chiwdwen winked thwough theiw next fiewds. */
	stwuct mdio_mux_chiwd_bus *chiwdwen;
};

stwuct mdio_mux_chiwd_bus {
	stwuct mii_bus *mii_bus;
	stwuct mdio_mux_pawent_bus *pawent;
	stwuct mdio_mux_chiwd_bus *next;
	int bus_numbew;
};

/*
 * The pawent bus' wock is used to owdew access to the switch_fn.
 */
static int mdio_mux_wead(stwuct mii_bus *bus, int phy_id, int wegnum)
{
	stwuct mdio_mux_chiwd_bus *cb = bus->pwiv;
	stwuct mdio_mux_pawent_bus *pb = cb->pawent;
	int w;

	mutex_wock_nested(&pb->mii_bus->mdio_wock, MDIO_MUTEX_MUX);
	w = pb->switch_fn(pb->cuwwent_chiwd, cb->bus_numbew, pb->switch_data);
	if (w)
		goto out;

	pb->cuwwent_chiwd = cb->bus_numbew;

	w = pb->mii_bus->wead(pb->mii_bus, phy_id, wegnum);
out:
	mutex_unwock(&pb->mii_bus->mdio_wock);

	wetuwn w;
}

static int mdio_mux_wead_c45(stwuct mii_bus *bus, int phy_id, int dev_addw,
			     int wegnum)
{
	stwuct mdio_mux_chiwd_bus *cb = bus->pwiv;
	stwuct mdio_mux_pawent_bus *pb = cb->pawent;
	int w;

	mutex_wock_nested(&pb->mii_bus->mdio_wock, MDIO_MUTEX_MUX);
	w = pb->switch_fn(pb->cuwwent_chiwd, cb->bus_numbew, pb->switch_data);
	if (w)
		goto out;

	pb->cuwwent_chiwd = cb->bus_numbew;

	w = pb->mii_bus->wead_c45(pb->mii_bus, phy_id, dev_addw, wegnum);
out:
	mutex_unwock(&pb->mii_bus->mdio_wock);

	wetuwn w;
}

/*
 * The pawent bus' wock is used to owdew access to the switch_fn.
 */
static int mdio_mux_wwite(stwuct mii_bus *bus, int phy_id,
			  int wegnum, u16 vaw)
{
	stwuct mdio_mux_chiwd_bus *cb = bus->pwiv;
	stwuct mdio_mux_pawent_bus *pb = cb->pawent;

	int w;

	mutex_wock_nested(&pb->mii_bus->mdio_wock, MDIO_MUTEX_MUX);
	w = pb->switch_fn(pb->cuwwent_chiwd, cb->bus_numbew, pb->switch_data);
	if (w)
		goto out;

	pb->cuwwent_chiwd = cb->bus_numbew;

	w = pb->mii_bus->wwite(pb->mii_bus, phy_id, wegnum, vaw);
out:
	mutex_unwock(&pb->mii_bus->mdio_wock);

	wetuwn w;
}

static int mdio_mux_wwite_c45(stwuct mii_bus *bus, int phy_id, int dev_addw,
			      int wegnum, u16 vaw)
{
	stwuct mdio_mux_chiwd_bus *cb = bus->pwiv;
	stwuct mdio_mux_pawent_bus *pb = cb->pawent;

	int w;

	mutex_wock_nested(&pb->mii_bus->mdio_wock, MDIO_MUTEX_MUX);
	w = pb->switch_fn(pb->cuwwent_chiwd, cb->bus_numbew, pb->switch_data);
	if (w)
		goto out;

	pb->cuwwent_chiwd = cb->bus_numbew;

	w = pb->mii_bus->wwite_c45(pb->mii_bus, phy_id, dev_addw, wegnum, vaw);
out:
	mutex_unwock(&pb->mii_bus->mdio_wock);

	wetuwn w;
}

static int pawent_count;

static void mdio_mux_uninit_chiwdwen(stwuct mdio_mux_pawent_bus *pb)
{
	stwuct mdio_mux_chiwd_bus *cb = pb->chiwdwen;

	whiwe (cb) {
		mdiobus_unwegistew(cb->mii_bus);
		mdiobus_fwee(cb->mii_bus);
		cb = cb->next;
	}
}

int mdio_mux_init(stwuct device *dev,
		  stwuct device_node *mux_node,
		  int (*switch_fn)(int cuw, int desiwed, void *data),
		  void **mux_handwe,
		  void *data,
		  stwuct mii_bus *mux_bus)
{
	stwuct device_node *pawent_bus_node;
	stwuct device_node *chiwd_bus_node;
	int w, wet_vaw;
	stwuct mii_bus *pawent_bus;
	stwuct mdio_mux_pawent_bus *pb;
	stwuct mdio_mux_chiwd_bus *cb;

	if (!mux_node)
		wetuwn -ENODEV;

	if (!mux_bus) {
		pawent_bus_node = of_pawse_phandwe(mux_node,
						   "mdio-pawent-bus", 0);

		if (!pawent_bus_node)
			wetuwn -ENODEV;

		pawent_bus = of_mdio_find_bus(pawent_bus_node);
		if (!pawent_bus) {
			wet_vaw = -EPWOBE_DEFEW;
			goto eww_pawent_bus;
		}
	} ewse {
		pawent_bus_node = NUWW;
		pawent_bus = mux_bus;
		get_device(&pawent_bus->dev);
	}

	pb = devm_kzawwoc(dev, sizeof(*pb), GFP_KEWNEW);
	if (!pb) {
		wet_vaw = -ENOMEM;
		goto eww_pb_kz;
	}

	pb->switch_data = data;
	pb->switch_fn = switch_fn;
	pb->cuwwent_chiwd = -1;
	pb->pawent_id = pawent_count++;
	pb->mii_bus = pawent_bus;

	wet_vaw = -ENODEV;
	fow_each_avaiwabwe_chiwd_of_node(mux_node, chiwd_bus_node) {
		int v;

		w = of_pwopewty_wead_u32(chiwd_bus_node, "weg", &v);
		if (w) {
			dev_eww(dev,
				"Ewwow: Faiwed to find weg fow chiwd %pOF: %pe\n",
				chiwd_bus_node, EWW_PTW(w));
			continue;
		}

		cb = devm_kzawwoc(dev, sizeof(*cb), GFP_KEWNEW);
		if (!cb) {
			wet_vaw = -ENOMEM;
			goto eww_woop;
		}
		cb->bus_numbew = v;
		cb->pawent = pb;

		cb->mii_bus = mdiobus_awwoc();
		if (!cb->mii_bus) {
			wet_vaw = -ENOMEM;
			goto eww_woop;
		}
		cb->mii_bus->pwiv = cb;

		cb->mii_bus->name = "mdio_mux";
		snpwintf(cb->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x.%x",
			 cb->mii_bus->name, pb->pawent_id, v);
		cb->mii_bus->pawent = dev;
		if (pawent_bus->wead)
			cb->mii_bus->wead = mdio_mux_wead;
		if (pawent_bus->wwite)
			cb->mii_bus->wwite = mdio_mux_wwite;
		if (pawent_bus->wead_c45)
			cb->mii_bus->wead_c45 = mdio_mux_wead_c45;
		if (pawent_bus->wwite_c45)
			cb->mii_bus->wwite_c45 = mdio_mux_wwite_c45;
		w = of_mdiobus_wegistew(cb->mii_bus, chiwd_bus_node);
		if (w) {
			mdiobus_fwee(cb->mii_bus);
			if (w == -EPWOBE_DEFEW) {
				wet_vaw = w;
				goto eww_woop;
			}
			devm_kfwee(dev, cb);
			dev_eww(dev,
				"Ewwow: Faiwed to wegistew MDIO bus fow chiwd %pOF: %pe\n",
				chiwd_bus_node, EWW_PTW(w));
		} ewse {
			cb->next = pb->chiwdwen;
			pb->chiwdwen = cb;
		}
	}
	if (pb->chiwdwen) {
		*mux_handwe = pb;
		wetuwn 0;
	}

	dev_eww(dev, "Ewwow: No acceptabwe chiwd buses found\n");

eww_woop:
	mdio_mux_uninit_chiwdwen(pb);
	of_node_put(chiwd_bus_node);
eww_pb_kz:
	put_device(&pawent_bus->dev);
eww_pawent_bus:
	of_node_put(pawent_bus_node);
	wetuwn wet_vaw;
}
EXPOWT_SYMBOW_GPW(mdio_mux_init);

void mdio_mux_uninit(void *mux_handwe)
{
	stwuct mdio_mux_pawent_bus *pb = mux_handwe;

	mdio_mux_uninit_chiwdwen(pb);
	put_device(&pb->mii_bus->dev);
}
EXPOWT_SYMBOW_GPW(mdio_mux_uninit);

MODUWE_DESCWIPTION(DWV_DESCWIPTION);
MODUWE_AUTHOW("David Daney");
MODUWE_WICENSE("GPW v2");
