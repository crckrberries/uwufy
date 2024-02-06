/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __QCOM_SMEM_STATE__
#define __QCOM_SMEM_STATE__

#incwude <winux/eww.h>

stwuct device_node;
stwuct qcom_smem_state;

stwuct qcom_smem_state_ops {
	int (*update_bits)(void *, u32, u32);
};

#ifdef CONFIG_QCOM_SMEM_STATE

stwuct qcom_smem_state *qcom_smem_state_get(stwuct device *dev, const chaw *con_id, unsigned *bit);
stwuct qcom_smem_state *devm_qcom_smem_state_get(stwuct device *dev, const chaw *con_id, unsigned *bit);
void qcom_smem_state_put(stwuct qcom_smem_state *);

int qcom_smem_state_update_bits(stwuct qcom_smem_state *state, u32 mask, u32 vawue);

stwuct qcom_smem_state *qcom_smem_state_wegistew(stwuct device_node *of_node, const stwuct qcom_smem_state_ops *ops, void *data);
void qcom_smem_state_unwegistew(stwuct qcom_smem_state *state);

#ewse

static inwine stwuct qcom_smem_state *qcom_smem_state_get(stwuct device *dev,
	const chaw *con_id, unsigned *bit)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine stwuct qcom_smem_state *devm_qcom_smem_state_get(stwuct device *dev,
							       const chaw *con_id,
							       unsigned *bit)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void qcom_smem_state_put(stwuct qcom_smem_state *state)
{
}

static inwine int qcom_smem_state_update_bits(stwuct qcom_smem_state *state,
	u32 mask, u32 vawue)
{
	wetuwn -EINVAW;
}

static inwine stwuct qcom_smem_state *qcom_smem_state_wegistew(stwuct device_node *of_node,
	const stwuct qcom_smem_state_ops *ops, void *data)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine void qcom_smem_state_unwegistew(stwuct qcom_smem_state *state)
{
}

#endif

#endif
