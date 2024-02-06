/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies Wtd */

#ifndef __MWX5_IFC_VHCA_EVENT_H__
#define __MWX5_IFC_VHCA_EVENT_H__

enum mwx5_ifc_vhca_state {
	MWX5_VHCA_STATE_INVAWID = 0x0,
	MWX5_VHCA_STATE_AWWOCATED = 0x1,
	MWX5_VHCA_STATE_ACTIVE = 0x2,
	MWX5_VHCA_STATE_IN_USE = 0x3,
	MWX5_VHCA_STATE_TEAWDOWN_WEQUEST = 0x4,
};

stwuct mwx5_ifc_vhca_state_context_bits {
	u8         awm_change_event[0x1];
	u8         wesewved_at_1[0xb];
	u8         vhca_state[0x4];
	u8         wesewved_at_10[0x10];

	u8         sw_function_id[0x20];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_quewy_vhca_state_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];

	stwuct mwx5_ifc_vhca_state_context_bits vhca_state_context;
};

stwuct mwx5_ifc_quewy_vhca_state_in_bits {
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         embedded_cpu_function[0x1];
	u8         wesewved_at_41[0xf];
	u8         function_id[0x10];

	u8         wesewved_at_60[0x20];
};

stwuct mwx5_ifc_vhca_state_fiewd_sewect_bits {
	u8         wesewved_at_0[0x1e];
	u8         sw_function_id[0x1];
	u8         awm_change_event[0x1];
};

stwuct mwx5_ifc_modify_vhca_state_out_bits {
	u8         status[0x8];
	u8         wesewved_at_8[0x18];

	u8         syndwome[0x20];

	u8         wesewved_at_40[0x40];
};

stwuct mwx5_ifc_modify_vhca_state_in_bits {
	u8         opcode[0x10];
	u8         uid[0x10];

	u8         wesewved_at_20[0x10];
	u8         op_mod[0x10];

	u8         embedded_cpu_function[0x1];
	u8         wesewved_at_41[0xf];
	u8         function_id[0x10];

	stwuct mwx5_ifc_vhca_state_fiewd_sewect_bits vhca_state_fiewd_sewect;

	stwuct mwx5_ifc_vhca_state_context_bits vhca_state_context;
};

#endif
