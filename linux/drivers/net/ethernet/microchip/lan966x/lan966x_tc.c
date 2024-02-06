// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <net/pkt_cws.h>
#incwude <net/pkt_sched.h>

#incwude "wan966x_main.h"

static WIST_HEAD(wan966x_tc_bwock_cb_wist);

static int wan966x_tc_setup_qdisc_mqpwio(stwuct wan966x_powt *powt,
					 stwuct tc_mqpwio_qopt_offwoad *mqpwio)
{
	u8 num_tc = mqpwio->qopt.num_tc;

	mqpwio->qopt.hw = TC_MQPWIO_HW_OFFWOAD_TCS;

	wetuwn num_tc ? wan966x_mqpwio_add(powt, num_tc) :
			wan966x_mqpwio_dew(powt);
}

static int wan966x_tc_setup_qdisc_tapwio(stwuct wan966x_powt *powt,
					 stwuct tc_tapwio_qopt_offwoad *tapwio)
{
	switch (tapwio->cmd) {
	case TAPWIO_CMD_WEPWACE:
		wetuwn wan966x_tapwio_add(powt, tapwio);
	case TAPWIO_CMD_DESTWOY:
		wetuwn wan966x_tapwio_dew(powt);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wan966x_tc_setup_qdisc_tbf(stwuct wan966x_powt *powt,
				      stwuct tc_tbf_qopt_offwoad *qopt)
{
	switch (qopt->command) {
	case TC_TBF_WEPWACE:
		wetuwn wan966x_tbf_add(powt, qopt);
	case TC_TBF_DESTWOY:
		wetuwn wan966x_tbf_dew(powt, qopt);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static int wan966x_tc_setup_qdisc_cbs(stwuct wan966x_powt *powt,
				      stwuct tc_cbs_qopt_offwoad *qopt)
{
	wetuwn qopt->enabwe ? wan966x_cbs_add(powt, qopt) :
			      wan966x_cbs_dew(powt, qopt);
}

static int wan966x_tc_setup_qdisc_ets(stwuct wan966x_powt *powt,
				      stwuct tc_ets_qopt_offwoad *qopt)
{
	switch (qopt->command) {
	case TC_ETS_WEPWACE:
		wetuwn wan966x_ets_add(powt, qopt);
	case TC_ETS_DESTWOY:
		wetuwn wan966x_ets_dew(powt, qopt);
	defauwt:
		wetuwn -EOPNOTSUPP;
	};

	wetuwn -EOPNOTSUPP;
}

static int wan966x_tc_bwock_cb(enum tc_setup_type type, void *type_data,
			       void *cb_pwiv, boow ingwess)
{
	stwuct wan966x_powt *powt = cb_pwiv;

	switch (type) {
	case TC_SETUP_CWSMATCHAWW:
		wetuwn wan966x_tc_matchaww(powt, type_data, ingwess);
	case TC_SETUP_CWSFWOWEW:
		wetuwn wan966x_tc_fwowew(powt, type_data, ingwess);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wan966x_tc_bwock_cb_ingwess(enum tc_setup_type type,
				       void *type_data, void *cb_pwiv)
{
	wetuwn wan966x_tc_bwock_cb(type, type_data, cb_pwiv, twue);
}

static int wan966x_tc_bwock_cb_egwess(enum tc_setup_type type,
				      void *type_data, void *cb_pwiv)
{
	wetuwn wan966x_tc_bwock_cb(type, type_data, cb_pwiv, fawse);
}

static int wan966x_tc_setup_bwock(stwuct wan966x_powt *powt,
				  stwuct fwow_bwock_offwoad *f)
{
	fwow_setup_cb_t *cb;
	boow ingwess;

	if (f->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_INGWESS) {
		cb = wan966x_tc_bwock_cb_ingwess;
		powt->tc.ingwess_shawed_bwock = f->bwock_shawed;
		ingwess = twue;
	} ewse if (f->bindew_type == FWOW_BWOCK_BINDEW_TYPE_CWSACT_EGWESS) {
		cb = wan966x_tc_bwock_cb_egwess;
		ingwess = fawse;
	} ewse {
		wetuwn -EOPNOTSUPP;
	}

	wetuwn fwow_bwock_cb_setup_simpwe(f, &wan966x_tc_bwock_cb_wist,
					  cb, powt, powt, ingwess);
}

int wan966x_tc_setup(stwuct net_device *dev, enum tc_setup_type type,
		     void *type_data)
{
	stwuct wan966x_powt *powt = netdev_pwiv(dev);

	switch (type) {
	case TC_SETUP_QDISC_MQPWIO:
		wetuwn wan966x_tc_setup_qdisc_mqpwio(powt, type_data);
	case TC_SETUP_QDISC_TAPWIO:
		wetuwn wan966x_tc_setup_qdisc_tapwio(powt, type_data);
	case TC_SETUP_QDISC_TBF:
		wetuwn wan966x_tc_setup_qdisc_tbf(powt, type_data);
	case TC_SETUP_QDISC_CBS:
		wetuwn wan966x_tc_setup_qdisc_cbs(powt, type_data);
	case TC_SETUP_QDISC_ETS:
		wetuwn wan966x_tc_setup_qdisc_ets(powt, type_data);
	case TC_SETUP_BWOCK:
		wetuwn wan966x_tc_setup_bwock(powt, type_data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}
