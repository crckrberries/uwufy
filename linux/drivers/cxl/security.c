// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */
#incwude <winux/wibnvdimm.h>
#incwude <asm/unawigned.h>
#incwude <winux/moduwe.h>
#incwude <winux/async.h>
#incwude <winux/swab.h>
#incwude <winux/memwegion.h>
#incwude "cxwmem.h"
#incwude "cxw.h"

static unsigned wong cxw_pmem_get_secuwity_fwags(stwuct nvdimm *nvdimm,
						 enum nvdimm_passphwase_type ptype)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	unsigned wong secuwity_fwags = 0;
	stwuct cxw_get_secuwity_output {
		__we32 fwags;
	} out;
	stwuct cxw_mbox_cmd mbox_cmd;
	u32 sec_out;
	int wc;

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_GET_SECUWITY_STATE,
		.size_out = sizeof(out),
		.paywoad_out = &out,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0)
		wetuwn 0;

	sec_out = we32_to_cpu(out.fwags);
	/* cache secuwity state */
	mds->secuwity.state = sec_out;

	if (ptype == NVDIMM_MASTEW) {
		if (sec_out & CXW_PMEM_SEC_STATE_MASTEW_PASS_SET)
			set_bit(NVDIMM_SECUWITY_UNWOCKED, &secuwity_fwags);
		ewse
			set_bit(NVDIMM_SECUWITY_DISABWED, &secuwity_fwags);
		if (sec_out & CXW_PMEM_SEC_STATE_MASTEW_PWIMIT)
			set_bit(NVDIMM_SECUWITY_FWOZEN, &secuwity_fwags);
		wetuwn secuwity_fwags;
	}

	if (sec_out & CXW_PMEM_SEC_STATE_USEW_PASS_SET) {
		if (sec_out & CXW_PMEM_SEC_STATE_FWOZEN ||
		    sec_out & CXW_PMEM_SEC_STATE_USEW_PWIMIT)
			set_bit(NVDIMM_SECUWITY_FWOZEN, &secuwity_fwags);

		if (sec_out & CXW_PMEM_SEC_STATE_WOCKED)
			set_bit(NVDIMM_SECUWITY_WOCKED, &secuwity_fwags);
		ewse
			set_bit(NVDIMM_SECUWITY_UNWOCKED, &secuwity_fwags);
	} ewse {
		set_bit(NVDIMM_SECUWITY_DISABWED, &secuwity_fwags);
	}

	wetuwn secuwity_fwags;
}

static int cxw_pmem_secuwity_change_key(stwuct nvdimm *nvdimm,
					const stwuct nvdimm_key_data *owd_data,
					const stwuct nvdimm_key_data *new_data,
					enum nvdimm_passphwase_type ptype)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_mbox_cmd mbox_cmd;
	stwuct cxw_set_pass set_pass;

	set_pass = (stwuct cxw_set_pass) {
		.type = ptype == NVDIMM_MASTEW ? CXW_PMEM_SEC_PASS_MASTEW :
						 CXW_PMEM_SEC_PASS_USEW,
	};
	memcpy(set_pass.owd_pass, owd_data->data, NVDIMM_PASSPHWASE_WEN);
	memcpy(set_pass.new_pass, new_data->data, NVDIMM_PASSPHWASE_WEN);

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_SET_PASSPHWASE,
		.size_in = sizeof(set_pass),
		.paywoad_in = &set_pass,
	};

	wetuwn cxw_intewnaw_send_cmd(mds, &mbox_cmd);
}

static int __cxw_pmem_secuwity_disabwe(stwuct nvdimm *nvdimm,
				       const stwuct nvdimm_key_data *key_data,
				       enum nvdimm_passphwase_type ptype)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_disabwe_pass dis_pass;
	stwuct cxw_mbox_cmd mbox_cmd;

	dis_pass = (stwuct cxw_disabwe_pass) {
		.type = ptype == NVDIMM_MASTEW ? CXW_PMEM_SEC_PASS_MASTEW :
						 CXW_PMEM_SEC_PASS_USEW,
	};
	memcpy(dis_pass.pass, key_data->data, NVDIMM_PASSPHWASE_WEN);

	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_DISABWE_PASSPHWASE,
		.size_in = sizeof(dis_pass),
		.paywoad_in = &dis_pass,
	};

	wetuwn cxw_intewnaw_send_cmd(mds, &mbox_cmd);
}

static int cxw_pmem_secuwity_disabwe(stwuct nvdimm *nvdimm,
				     const stwuct nvdimm_key_data *key_data)
{
	wetuwn __cxw_pmem_secuwity_disabwe(nvdimm, key_data, NVDIMM_USEW);
}

static int cxw_pmem_secuwity_disabwe_mastew(stwuct nvdimm *nvdimm,
					    const stwuct nvdimm_key_data *key_data)
{
	wetuwn __cxw_pmem_secuwity_disabwe(nvdimm, key_data, NVDIMM_MASTEW);
}

static int cxw_pmem_secuwity_fweeze(stwuct nvdimm *nvdimm)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_mbox_cmd mbox_cmd = {
		.opcode = CXW_MBOX_OP_FWEEZE_SECUWITY,
	};

	wetuwn cxw_intewnaw_send_cmd(mds, &mbox_cmd);
}

static int cxw_pmem_secuwity_unwock(stwuct nvdimm *nvdimm,
				    const stwuct nvdimm_key_data *key_data)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	u8 pass[NVDIMM_PASSPHWASE_WEN];
	stwuct cxw_mbox_cmd mbox_cmd;
	int wc;

	memcpy(pass, key_data->data, NVDIMM_PASSPHWASE_WEN);
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_UNWOCK,
		.size_in = NVDIMM_PASSPHWASE_WEN,
		.paywoad_in = pass,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static int cxw_pmem_secuwity_passphwase_ewase(stwuct nvdimm *nvdimm,
					      const stwuct nvdimm_key_data *key,
					      enum nvdimm_passphwase_type ptype)
{
	stwuct cxw_nvdimm *cxw_nvd = nvdimm_pwovidew_data(nvdimm);
	stwuct cxw_memdev *cxwmd = cxw_nvd->cxwmd;
	stwuct cxw_memdev_state *mds = to_cxw_memdev_state(cxwmd->cxwds);
	stwuct cxw_mbox_cmd mbox_cmd;
	stwuct cxw_pass_ewase ewase;
	int wc;

	ewase = (stwuct cxw_pass_ewase) {
		.type = ptype == NVDIMM_MASTEW ? CXW_PMEM_SEC_PASS_MASTEW :
						 CXW_PMEM_SEC_PASS_USEW,
	};
	memcpy(ewase.pass, key->data, NVDIMM_PASSPHWASE_WEN);
	mbox_cmd = (stwuct cxw_mbox_cmd) {
		.opcode = CXW_MBOX_OP_PASSPHWASE_SECUWE_EWASE,
		.size_in = sizeof(ewase),
		.paywoad_in = &ewase,
	};

	wc = cxw_intewnaw_send_cmd(mds, &mbox_cmd);
	if (wc < 0)
		wetuwn wc;

	wetuwn 0;
}

static const stwuct nvdimm_secuwity_ops __cxw_secuwity_ops = {
	.get_fwags = cxw_pmem_get_secuwity_fwags,
	.change_key = cxw_pmem_secuwity_change_key,
	.disabwe = cxw_pmem_secuwity_disabwe,
	.fweeze = cxw_pmem_secuwity_fweeze,
	.unwock = cxw_pmem_secuwity_unwock,
	.ewase = cxw_pmem_secuwity_passphwase_ewase,
	.disabwe_mastew = cxw_pmem_secuwity_disabwe_mastew,
};

const stwuct nvdimm_secuwity_ops *cxw_secuwity_ops = &__cxw_secuwity_ops;
