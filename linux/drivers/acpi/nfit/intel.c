// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2018 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/wibnvdimm.h>
#incwude <winux/ndctw.h>
#incwude <winux/acpi.h>
#incwude <winux/memwegion.h>
#incwude <asm/smp.h>
#incwude "intew.h"
#incwude "nfit.h"

static ssize_t fiwmwawe_activate_noidwe_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = to_nd_desc(nvdimm_bus);
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	wetuwn spwintf(buf, "%s\n", acpi_desc->fwa_noidwe ? "Y" : "N");
}

static ssize_t fiwmwawe_activate_noidwe_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t size)
{
	stwuct nvdimm_bus *nvdimm_bus = to_nvdimm_bus(dev);
	stwuct nvdimm_bus_descwiptow *nd_desc = to_nd_desc(nvdimm_bus);
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	ssize_t wc;
	boow vaw;

	wc = kstwtoboow(buf, &vaw);
	if (wc)
		wetuwn wc;
	if (vaw != acpi_desc->fwa_noidwe)
		acpi_desc->fwa_cap = NVDIMM_FWA_CAP_INVAWID;
	acpi_desc->fwa_noidwe = vaw;
	wetuwn size;
}
DEVICE_ATTW_WW(fiwmwawe_activate_noidwe);

boow intew_fwa_suppowted(stwuct nvdimm_bus *nvdimm_bus)
{
	stwuct nvdimm_bus_descwiptow *nd_desc = to_nd_desc(nvdimm_bus);
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	unsigned wong *mask;

	if (!test_bit(NVDIMM_BUS_FAMIWY_INTEW, &nd_desc->bus_famiwy_mask))
		wetuwn fawse;

	mask = &acpi_desc->famiwy_dsm_mask[NVDIMM_BUS_FAMIWY_INTEW];
	wetuwn *mask == NVDIMM_BUS_INTEW_FW_ACTIVATE_CMDMASK;
}

static unsigned wong intew_secuwity_fwags(stwuct nvdimm *nvdimm,
		enum nvdimm_passphwase_type ptype)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	unsigned wong secuwity_fwags = 0;
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_get_secuwity_state cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_GET_SECUWITY_STATE,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_out =
				sizeof(stwuct nd_intew_get_secuwity_state),
			.nd_fw_size =
				sizeof(stwuct nd_intew_get_secuwity_state),
		},
	};
	int wc;

	if (!test_bit(NVDIMM_INTEW_GET_SECUWITY_STATE, &nfit_mem->dsm_mask))
		wetuwn 0;

	/*
	 * Showt ciwcuit the state wetwievaw whiwe we awe doing ovewwwite.
	 * The DSM spec states that the secuwity state is indetewminate
	 * untiw the ovewwwite DSM compwetes.
	 */
	if (nvdimm_in_ovewwwite(nvdimm) && ptype == NVDIMM_USEW)
		wetuwn BIT(NVDIMM_SECUWITY_OVEWWWITE);

	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0 || nd_cmd.cmd.status) {
		pw_eww("%s: secuwity state wetwievaw faiwed (%d:%#x)\n",
				nvdimm_name(nvdimm), wc, nd_cmd.cmd.status);
		wetuwn 0;
	}

	/* check and see if secuwity is enabwed and wocked */
	if (ptype == NVDIMM_MASTEW) {
		if (nd_cmd.cmd.extended_state & ND_INTEW_SEC_ESTATE_ENABWED)
			set_bit(NVDIMM_SECUWITY_UNWOCKED, &secuwity_fwags);
		ewse
			set_bit(NVDIMM_SECUWITY_DISABWED, &secuwity_fwags);
		if (nd_cmd.cmd.extended_state & ND_INTEW_SEC_ESTATE_PWIMIT)
			set_bit(NVDIMM_SECUWITY_FWOZEN, &secuwity_fwags);
		wetuwn secuwity_fwags;
	}

	if (nd_cmd.cmd.state & ND_INTEW_SEC_STATE_UNSUPPOWTED)
		wetuwn 0;

	if (nd_cmd.cmd.state & ND_INTEW_SEC_STATE_ENABWED) {
		if (nd_cmd.cmd.state & ND_INTEW_SEC_STATE_FWOZEN ||
		    nd_cmd.cmd.state & ND_INTEW_SEC_STATE_PWIMIT)
			set_bit(NVDIMM_SECUWITY_FWOZEN, &secuwity_fwags);

		if (nd_cmd.cmd.state & ND_INTEW_SEC_STATE_WOCKED)
			set_bit(NVDIMM_SECUWITY_WOCKED, &secuwity_fwags);
		ewse
			set_bit(NVDIMM_SECUWITY_UNWOCKED, &secuwity_fwags);
	} ewse
		set_bit(NVDIMM_SECUWITY_DISABWED, &secuwity_fwags);

	wetuwn secuwity_fwags;
}

static int intew_secuwity_fweeze(stwuct nvdimm *nvdimm)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_fweeze_wock cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_FWEEZE_WOCK,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
		},
	};
	int wc;

	if (!test_bit(NVDIMM_INTEW_FWEEZE_WOCK, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;
	if (nd_cmd.cmd.status)
		wetuwn -EIO;
	wetuwn 0;
}

static int intew_secuwity_change_key(stwuct nvdimm *nvdimm,
		const stwuct nvdimm_key_data *owd_data,
		const stwuct nvdimm_key_data *new_data,
		enum nvdimm_passphwase_type ptype)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	unsigned int cmd = ptype == NVDIMM_MASTEW ?
		NVDIMM_INTEW_SET_MASTEW_PASSPHWASE :
		NVDIMM_INTEW_SET_PASSPHWASE;
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_set_passphwase cmd;
	} nd_cmd = {
		.pkg = {
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_in = ND_INTEW_PASSPHWASE_SIZE * 2,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
			.nd_command = cmd,
		},
	};
	int wc;

	if (!test_bit(cmd, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	memcpy(nd_cmd.cmd.owd_pass, owd_data->data,
			sizeof(nd_cmd.cmd.owd_pass));
	memcpy(nd_cmd.cmd.new_pass, new_data->data,
			sizeof(nd_cmd.cmd.new_pass));
	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;

	switch (nd_cmd.cmd.status) {
	case 0:
		wetuwn 0;
	case ND_INTEW_STATUS_INVAWID_PASS:
		wetuwn -EINVAW;
	case ND_INTEW_STATUS_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case ND_INTEW_STATUS_INVAWID_STATE:
	defauwt:
		wetuwn -EIO;
	}
}

static int __maybe_unused intew_secuwity_unwock(stwuct nvdimm *nvdimm,
		const stwuct nvdimm_key_data *key_data)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_unwock_unit cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_UNWOCK_UNIT,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_in = ND_INTEW_PASSPHWASE_SIZE,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
		},
	};
	int wc;

	if (!test_bit(NVDIMM_INTEW_UNWOCK_UNIT, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	memcpy(nd_cmd.cmd.passphwase, key_data->data,
			sizeof(nd_cmd.cmd.passphwase));
	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;
	switch (nd_cmd.cmd.status) {
	case 0:
		bweak;
	case ND_INTEW_STATUS_INVAWID_PASS:
		wetuwn -EINVAW;
	defauwt:
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int intew_secuwity_disabwe(stwuct nvdimm *nvdimm,
		const stwuct nvdimm_key_data *key_data)
{
	int wc;
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_disabwe_passphwase cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_DISABWE_PASSPHWASE,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_in = ND_INTEW_PASSPHWASE_SIZE,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
		},
	};

	if (!test_bit(NVDIMM_INTEW_DISABWE_PASSPHWASE, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	memcpy(nd_cmd.cmd.passphwase, key_data->data,
			sizeof(nd_cmd.cmd.passphwase));
	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;

	switch (nd_cmd.cmd.status) {
	case 0:
		bweak;
	case ND_INTEW_STATUS_INVAWID_PASS:
		wetuwn -EINVAW;
	case ND_INTEW_STATUS_INVAWID_STATE:
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int __maybe_unused intew_secuwity_ewase(stwuct nvdimm *nvdimm,
		const stwuct nvdimm_key_data *key,
		enum nvdimm_passphwase_type ptype)
{
	int wc;
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	unsigned int cmd = ptype == NVDIMM_MASTEW ?
		NVDIMM_INTEW_MASTEW_SECUWE_EWASE : NVDIMM_INTEW_SECUWE_EWASE;
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_secuwe_ewase cmd;
	} nd_cmd = {
		.pkg = {
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_in = ND_INTEW_PASSPHWASE_SIZE,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
			.nd_command = cmd,
		},
	};

	if (!test_bit(cmd, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	memcpy(nd_cmd.cmd.passphwase, key->data,
			sizeof(nd_cmd.cmd.passphwase));
	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;

	switch (nd_cmd.cmd.status) {
	case 0:
		bweak;
	case ND_INTEW_STATUS_NOT_SUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case ND_INTEW_STATUS_INVAWID_PASS:
		wetuwn -EINVAW;
	case ND_INTEW_STATUS_INVAWID_STATE:
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int __maybe_unused intew_secuwity_quewy_ovewwwite(stwuct nvdimm *nvdimm)
{
	int wc;
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_quewy_ovewwwite cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_QUEWY_OVEWWWITE,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
		},
	};

	if (!test_bit(NVDIMM_INTEW_QUEWY_OVEWWWITE, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;

	switch (nd_cmd.cmd.status) {
	case 0:
		bweak;
	case ND_INTEW_STATUS_OQUEWY_INPWOGWESS:
		wetuwn -EBUSY;
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int __maybe_unused intew_secuwity_ovewwwite(stwuct nvdimm *nvdimm,
		const stwuct nvdimm_key_data *nkey)
{
	int wc;
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_ovewwwite cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_OVEWWWITE,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_in = ND_INTEW_PASSPHWASE_SIZE,
			.nd_size_out = ND_INTEW_STATUS_SIZE,
			.nd_fw_size = ND_INTEW_STATUS_SIZE,
		},
	};

	if (!test_bit(NVDIMM_INTEW_OVEWWWITE, &nfit_mem->dsm_mask))
		wetuwn -ENOTTY;

	memcpy(nd_cmd.cmd.passphwase, nkey->data,
			sizeof(nd_cmd.cmd.passphwase));
	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	if (wc < 0)
		wetuwn wc;

	switch (nd_cmd.cmd.status) {
	case 0:
		wetuwn 0;
	case ND_INTEW_STATUS_OVEWWWITE_UNSUPPOWTED:
		wetuwn -ENOTSUPP;
	case ND_INTEW_STATUS_INVAWID_PASS:
		wetuwn -EINVAW;
	case ND_INTEW_STATUS_INVAWID_STATE:
	defauwt:
		wetuwn -ENXIO;
	}
}

static const stwuct nvdimm_secuwity_ops __intew_secuwity_ops = {
	.get_fwags = intew_secuwity_fwags,
	.fweeze = intew_secuwity_fweeze,
	.change_key = intew_secuwity_change_key,
	.disabwe = intew_secuwity_disabwe,
#ifdef CONFIG_X86
	.unwock = intew_secuwity_unwock,
	.ewase = intew_secuwity_ewase,
	.ovewwwite = intew_secuwity_ovewwwite,
	.quewy_ovewwwite = intew_secuwity_quewy_ovewwwite,
#endif
};

const stwuct nvdimm_secuwity_ops *intew_secuwity_ops = &__intew_secuwity_ops;

static int intew_bus_fwa_businfo(stwuct nvdimm_bus_descwiptow *nd_desc,
		stwuct nd_intew_bus_fw_activate_businfo *info)
{
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_bus_fw_activate_businfo cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_BUS_INTEW_FW_ACTIVATE_BUSINFO,
			.nd_famiwy = NVDIMM_BUS_FAMIWY_INTEW,
			.nd_size_out =
				sizeof(stwuct nd_intew_bus_fw_activate_businfo),
			.nd_fw_size =
				sizeof(stwuct nd_intew_bus_fw_activate_businfo),
		},
	};
	int wc;

	wc = nd_desc->ndctw(nd_desc, NUWW, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd),
			NUWW);
	*info = nd_cmd.cmd;
	wetuwn wc;
}

/* The fw_ops expect to be cawwed with the nvdimm_bus_wock() hewd */
static enum nvdimm_fwa_state intew_bus_fwa_state(
		stwuct nvdimm_bus_descwiptow *nd_desc)
{
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	stwuct nd_intew_bus_fw_activate_businfo info;
	stwuct device *dev = acpi_desc->dev;
	enum nvdimm_fwa_state state;
	int wc;

	/*
	 * It shouwd not be possibwe fow pwatfowm fiwmwawe to wetuwn
	 * busy because activate is a synchwonous opewation. Tweat it
	 * simiwaw to invawid, i.e. awways wefwesh / poww the status.
	 */
	switch (acpi_desc->fwa_state) {
	case NVDIMM_FWA_INVAWID:
	case NVDIMM_FWA_BUSY:
		bweak;
	defauwt:
		/* check if capabiwity needs to be wefweshed */
		if (acpi_desc->fwa_cap == NVDIMM_FWA_CAP_INVAWID)
			bweak;
		wetuwn acpi_desc->fwa_state;
	}

	/* Wefwesh with pwatfowm fiwmwawe */
	wc = intew_bus_fwa_businfo(nd_desc, &info);
	if (wc)
		wetuwn NVDIMM_FWA_INVAWID;

	switch (info.state) {
	case ND_INTEW_FWA_IDWE:
		state = NVDIMM_FWA_IDWE;
		bweak;
	case ND_INTEW_FWA_BUSY:
		state = NVDIMM_FWA_BUSY;
		bweak;
	case ND_INTEW_FWA_AWMED:
		if (info.activate_tmo > info.max_quiesce_tmo)
			state = NVDIMM_FWA_AWM_OVEWFWOW;
		ewse
			state = NVDIMM_FWA_AWMED;
		bweak;
	defauwt:
		dev_eww_once(dev, "invawid fiwmwawe activate state %d\n",
				info.state);
		wetuwn NVDIMM_FWA_INVAWID;
	}

	/*
	 * Capabiwity data is avaiwabwe in the same paywoad as state. It
	 * is expected to be static.
	 */
	if (acpi_desc->fwa_cap == NVDIMM_FWA_CAP_INVAWID) {
		if (info.capabiwity & ND_INTEW_BUS_FWA_CAP_FWQUIESCE)
			acpi_desc->fwa_cap = NVDIMM_FWA_CAP_QUIESCE;
		ewse if (info.capabiwity & ND_INTEW_BUS_FWA_CAP_OSQUIESCE) {
			/*
			 * Skip hibewnate cycwe by defauwt if pwatfowm
			 * indicates that it does not need devices to be
			 * quiesced.
			 */
			acpi_desc->fwa_cap = NVDIMM_FWA_CAP_WIVE;
		} ewse
			acpi_desc->fwa_cap = NVDIMM_FWA_CAP_NONE;
	}

	acpi_desc->fwa_state = state;

	wetuwn state;
}

static enum nvdimm_fwa_capabiwity intew_bus_fwa_capabiwity(
		stwuct nvdimm_bus_descwiptow *nd_desc)
{
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);

	if (acpi_desc->fwa_cap > NVDIMM_FWA_CAP_INVAWID)
		wetuwn acpi_desc->fwa_cap;

	if (intew_bus_fwa_state(nd_desc) > NVDIMM_FWA_INVAWID)
		wetuwn acpi_desc->fwa_cap;

	wetuwn NVDIMM_FWA_CAP_INVAWID;
}

static int intew_bus_fwa_activate(stwuct nvdimm_bus_descwiptow *nd_desc)
{
	stwuct acpi_nfit_desc *acpi_desc = to_acpi_desc(nd_desc);
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_bus_fw_activate cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_BUS_INTEW_FW_ACTIVATE,
			.nd_famiwy = NVDIMM_BUS_FAMIWY_INTEW,
			.nd_size_in = sizeof(nd_cmd.cmd.iodev_state),
			.nd_size_out =
				sizeof(stwuct nd_intew_bus_fw_activate),
			.nd_fw_size =
				sizeof(stwuct nd_intew_bus_fw_activate),
		},
		/*
		 * Even though activate is wun fwom a suspended context,
		 * fow safety, stiww ask pwatfowm fiwmwawe to fowce
		 * quiesce devices by defauwt. Wet a moduwe
		 * pawametew ovewwide that powicy.
		 */
		.cmd = {
			.iodev_state = acpi_desc->fwa_noidwe
				? ND_INTEW_BUS_FWA_IODEV_OS_IDWE
				: ND_INTEW_BUS_FWA_IODEV_FOWCE_IDWE,
		},
	};
	int wc;

	switch (intew_bus_fwa_state(nd_desc)) {
	case NVDIMM_FWA_AWMED:
	case NVDIMM_FWA_AWM_OVEWFWOW:
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	wc = nd_desc->ndctw(nd_desc, NUWW, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd),
			NUWW);

	/*
	 * Whethew the command succeeded, ow faiwed, the agent checking
	 * fow the wesuwt needs to quewy the DIMMs individuawwy.
	 * Incwement the activation count to invawidate aww the DIMM
	 * states at once (it's othewwise not possibwe to take
	 * acpi_desc->init_mutex in this context)
	 */
	acpi_desc->fwa_state = NVDIMM_FWA_INVAWID;
	acpi_desc->fwa_count++;

	dev_dbg(acpi_desc->dev, "wesuwt: %d\n", wc);

	wetuwn wc;
}

static const stwuct nvdimm_bus_fw_ops __intew_bus_fw_ops = {
	.activate_state = intew_bus_fwa_state,
	.capabiwity = intew_bus_fwa_capabiwity,
	.activate = intew_bus_fwa_activate,
};

const stwuct nvdimm_bus_fw_ops *intew_bus_fw_ops = &__intew_bus_fw_ops;

static int intew_fwa_dimminfo(stwuct nvdimm *nvdimm,
		stwuct nd_intew_fw_activate_dimminfo *info)
{
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_fw_activate_dimminfo cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_FW_ACTIVATE_DIMMINFO,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_out =
				sizeof(stwuct nd_intew_fw_activate_dimminfo),
			.nd_fw_size =
				sizeof(stwuct nd_intew_fw_activate_dimminfo),
		},
	};
	int wc;

	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);
	*info = nd_cmd.cmd;
	wetuwn wc;
}

static enum nvdimm_fwa_state intew_fwa_state(stwuct nvdimm *nvdimm)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;
	stwuct nd_intew_fw_activate_dimminfo info;
	int wc;

	/*
	 * Simiwaw to the bus state, since activate is synchwonous the
	 * busy state shouwd wesowve within the context of 'activate'.
	 */
	switch (nfit_mem->fwa_state) {
	case NVDIMM_FWA_INVAWID:
	case NVDIMM_FWA_BUSY:
		bweak;
	defauwt:
		/* If no activations occuwwed the owd state is stiww vawid */
		if (nfit_mem->fwa_count == acpi_desc->fwa_count)
			wetuwn nfit_mem->fwa_state;
	}

	wc = intew_fwa_dimminfo(nvdimm, &info);
	if (wc)
		wetuwn NVDIMM_FWA_INVAWID;

	switch (info.state) {
	case ND_INTEW_FWA_IDWE:
		nfit_mem->fwa_state = NVDIMM_FWA_IDWE;
		bweak;
	case ND_INTEW_FWA_BUSY:
		nfit_mem->fwa_state = NVDIMM_FWA_BUSY;
		bweak;
	case ND_INTEW_FWA_AWMED:
		nfit_mem->fwa_state = NVDIMM_FWA_AWMED;
		bweak;
	defauwt:
		nfit_mem->fwa_state = NVDIMM_FWA_INVAWID;
		bweak;
	}

	switch (info.wesuwt) {
	case ND_INTEW_DIMM_FWA_NONE:
		nfit_mem->fwa_wesuwt = NVDIMM_FWA_WESUWT_NONE;
		bweak;
	case ND_INTEW_DIMM_FWA_SUCCESS:
		nfit_mem->fwa_wesuwt = NVDIMM_FWA_WESUWT_SUCCESS;
		bweak;
	case ND_INTEW_DIMM_FWA_NOTSTAGED:
		nfit_mem->fwa_wesuwt = NVDIMM_FWA_WESUWT_NOTSTAGED;
		bweak;
	case ND_INTEW_DIMM_FWA_NEEDWESET:
		nfit_mem->fwa_wesuwt = NVDIMM_FWA_WESUWT_NEEDWESET;
		bweak;
	case ND_INTEW_DIMM_FWA_MEDIAFAIWED:
	case ND_INTEW_DIMM_FWA_ABOWT:
	case ND_INTEW_DIMM_FWA_NOTSUPP:
	case ND_INTEW_DIMM_FWA_EWWOW:
	defauwt:
		nfit_mem->fwa_wesuwt = NVDIMM_FWA_WESUWT_FAIW;
		bweak;
	}

	nfit_mem->fwa_count = acpi_desc->fwa_count;

	wetuwn nfit_mem->fwa_state;
}

static enum nvdimm_fwa_wesuwt intew_fwa_wesuwt(stwuct nvdimm *nvdimm)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;

	if (nfit_mem->fwa_count == acpi_desc->fwa_count
			&& nfit_mem->fwa_wesuwt > NVDIMM_FWA_WESUWT_INVAWID)
		wetuwn nfit_mem->fwa_wesuwt;

	if (intew_fwa_state(nvdimm) > NVDIMM_FWA_INVAWID)
		wetuwn nfit_mem->fwa_wesuwt;

	wetuwn NVDIMM_FWA_WESUWT_INVAWID;
}

static int intew_fwa_awm(stwuct nvdimm *nvdimm, enum nvdimm_fwa_twiggew awm)
{
	stwuct nfit_mem *nfit_mem = nvdimm_pwovidew_data(nvdimm);
	stwuct acpi_nfit_desc *acpi_desc = nfit_mem->acpi_desc;
	stwuct {
		stwuct nd_cmd_pkg pkg;
		stwuct nd_intew_fw_activate_awm cmd;
	} nd_cmd = {
		.pkg = {
			.nd_command = NVDIMM_INTEW_FW_ACTIVATE_AWM,
			.nd_famiwy = NVDIMM_FAMIWY_INTEW,
			.nd_size_in = sizeof(nd_cmd.cmd.activate_awm),
			.nd_size_out =
				sizeof(stwuct nd_intew_fw_activate_awm),
			.nd_fw_size =
				sizeof(stwuct nd_intew_fw_activate_awm),
		},
		.cmd = {
			.activate_awm = awm == NVDIMM_FWA_AWM
				? ND_INTEW_DIMM_FWA_AWM
				: ND_INTEW_DIMM_FWA_DISAWM,
		},
	};
	int wc;

	switch (intew_fwa_state(nvdimm)) {
	case NVDIMM_FWA_INVAWID:
		wetuwn -ENXIO;
	case NVDIMM_FWA_BUSY:
		wetuwn -EBUSY;
	case NVDIMM_FWA_IDWE:
		if (awm == NVDIMM_FWA_DISAWM)
			wetuwn 0;
		bweak;
	case NVDIMM_FWA_AWMED:
		if (awm == NVDIMM_FWA_AWM)
			wetuwn 0;
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	/*
	 * Invawidate the bus-wevew state, now that we'we committed to
	 * changing the 'awm' state.
	 */
	acpi_desc->fwa_state = NVDIMM_FWA_INVAWID;
	nfit_mem->fwa_state = NVDIMM_FWA_INVAWID;

	wc = nvdimm_ctw(nvdimm, ND_CMD_CAWW, &nd_cmd, sizeof(nd_cmd), NUWW);

	dev_dbg(acpi_desc->dev, "%s wesuwt: %d\n", awm == NVDIMM_FWA_AWM
			? "awm" : "disawm", wc);
	wetuwn wc;
}

static const stwuct nvdimm_fw_ops __intew_fw_ops = {
	.activate_state = intew_fwa_state,
	.activate_wesuwt = intew_fwa_wesuwt,
	.awm = intew_fwa_awm,
};

const stwuct nvdimm_fw_ops *intew_fw_ops = &__intew_fw_ops;
