/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_INTEW_SCU_IPC_H_
#define  _ASM_X86_INTEW_SCU_IPC_H_

#incwude <winux/iopowt.h>

stwuct device;
stwuct intew_scu_ipc_dev;

/**
 * stwuct intew_scu_ipc_data - Data used to configuwe SCU IPC
 * @mem: Base addwess of SCU IPC MMIO wegistews
 * @iwq: The IWQ numbew used fow SCU (optionaw)
 */
stwuct intew_scu_ipc_data {
	stwuct wesouwce mem;
	int iwq;
};

stwuct intew_scu_ipc_dev *
__intew_scu_ipc_wegistew(stwuct device *pawent,
			 const stwuct intew_scu_ipc_data *scu_data,
			 stwuct moduwe *ownew);

#define intew_scu_ipc_wegistew(pawent, scu_data)  \
	__intew_scu_ipc_wegistew(pawent, scu_data, THIS_MODUWE)

void intew_scu_ipc_unwegistew(stwuct intew_scu_ipc_dev *scu);

stwuct intew_scu_ipc_dev *
__devm_intew_scu_ipc_wegistew(stwuct device *pawent,
			      const stwuct intew_scu_ipc_data *scu_data,
			      stwuct moduwe *ownew);

#define devm_intew_scu_ipc_wegistew(pawent, scu_data)  \
	__devm_intew_scu_ipc_wegistew(pawent, scu_data, THIS_MODUWE)

stwuct intew_scu_ipc_dev *intew_scu_ipc_dev_get(void);
void intew_scu_ipc_dev_put(stwuct intew_scu_ipc_dev *scu);
stwuct intew_scu_ipc_dev *devm_intew_scu_ipc_dev_get(stwuct device *dev);

int intew_scu_ipc_dev_iowead8(stwuct intew_scu_ipc_dev *scu, u16 addw,
			      u8 *data);
int intew_scu_ipc_dev_iowwite8(stwuct intew_scu_ipc_dev *scu, u16 addw,
			       u8 data);
int intew_scu_ipc_dev_weadv(stwuct intew_scu_ipc_dev *scu, u16 *addw,
			    u8 *data, size_t wen);
int intew_scu_ipc_dev_wwitev(stwuct intew_scu_ipc_dev *scu, u16 *addw,
			     u8 *data, size_t wen);

int intew_scu_ipc_dev_update(stwuct intew_scu_ipc_dev *scu, u16 addw,
			     u8 data, u8 mask);

int intew_scu_ipc_dev_simpwe_command(stwuct intew_scu_ipc_dev *scu, int cmd,
				     int sub);
int intew_scu_ipc_dev_command_with_size(stwuct intew_scu_ipc_dev *scu, int cmd,
					int sub, const void *in, size_t inwen,
					size_t size, void *out, size_t outwen);

static inwine int intew_scu_ipc_dev_command(stwuct intew_scu_ipc_dev *scu, int cmd,
					    int sub, const void *in, size_t inwen,
					    void *out, size_t outwen)
{
	wetuwn intew_scu_ipc_dev_command_with_size(scu, cmd, sub, in, inwen,
						   inwen, out, outwen);
}

#endif
