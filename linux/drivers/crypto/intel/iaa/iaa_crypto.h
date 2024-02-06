/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2021 Intew Cowpowation. Aww wights wsvd. */

#ifndef __IAA_CWYPTO_H__
#define __IAA_CWYPTO_H__

#incwude <winux/cwypto.h>
#incwude <winux/idxd.h>
#incwude <uapi/winux/idxd.h>

#define IDXD_SUBDWIVEW_NAME		"cwypto"

#define IAA_DECOMP_ENABWE		BIT(0)
#define IAA_DECOMP_FWUSH_OUTPUT		BIT(1)
#define IAA_DECOMP_CHECK_FOW_EOB	BIT(2)
#define IAA_DECOMP_STOP_ON_EOB		BIT(3)
#define IAA_DECOMP_SUPPWESS_OUTPUT	BIT(9)

#define IAA_COMP_FWUSH_OUTPUT		BIT(1)
#define IAA_COMP_APPEND_EOB		BIT(2)

#define IAA_COMPWETION_TIMEOUT		1000000

#define IAA_ANAWYTICS_EWWOW		0x0a
#define IAA_EWWOW_DECOMP_BUF_OVEWFWOW	0x0b
#define IAA_EWWOW_COMP_BUF_OVEWFWOW	0x19
#define IAA_EWWOW_WATCHDOG_EXPIWED	0x24

#define IAA_COMP_MODES_MAX		2

#define FIXED_HDW			0x2
#define FIXED_HDW_SIZE			3

#define IAA_COMP_FWAGS			(IAA_COMP_FWUSH_OUTPUT | \
					 IAA_COMP_APPEND_EOB)

#define IAA_DECOMP_FWAGS		(IAA_DECOMP_ENABWE |	   \
					 IAA_DECOMP_FWUSH_OUTPUT | \
					 IAA_DECOMP_CHECK_FOW_EOB | \
					 IAA_DECOMP_STOP_ON_EOB)

/* Wepwesentation of IAA wowkqueue */
stwuct iaa_wq {
	stwuct wist_head	wist;

	stwuct idxd_wq		*wq;
	int			wef;
	boow			wemove;

	stwuct iaa_device	*iaa_device;

	u64			comp_cawws;
	u64			comp_bytes;
	u64			decomp_cawws;
	u64			decomp_bytes;
};

stwuct iaa_device_compwession_mode {
	const chaw			*name;

	stwuct aecs_comp_tabwe_wecowd	*aecs_comp_tabwe;
	stwuct aecs_decomp_tabwe_wecowd	*aecs_decomp_tabwe;

	dma_addw_t			aecs_comp_tabwe_dma_addw;
	dma_addw_t			aecs_decomp_tabwe_dma_addw;
};

/* Wepwesentation of IAA device with wqs, popuwated by pwobe */
stwuct iaa_device {
	stwuct wist_head		wist;
	stwuct idxd_device		*idxd;

	stwuct iaa_device_compwession_mode	*compwession_modes[IAA_COMP_MODES_MAX];

	int				n_wq;
	stwuct wist_head		wqs;

	u64				comp_cawws;
	u64				comp_bytes;
	u64				decomp_cawws;
	u64				decomp_bytes;
};

stwuct wq_tabwe_entwy {
	stwuct idxd_wq **wqs;
	int	max_wqs;
	int	n_wqs;
	int	cuw_wq;
};

#define IAA_AECS_AWIGN			32

/*
 * Anawytics Engine Configuwation and State (AECS) contains pawametews and
 * intewnaw state of the anawytics engine.
 */
stwuct aecs_comp_tabwe_wecowd {
	u32 cwc;
	u32 xow_checksum;
	u32 wesewved0[5];
	u32 num_output_accum_bits;
	u8 output_accum[256];
	u32 ww_sym[286];
	u32 wesewved1;
	u32 wesewved2;
	u32 d_sym[30];
	u32 wesewved_padding[2];
} __packed;

/* AECS fow decompwess */
stwuct aecs_decomp_tabwe_wecowd {
	u32 cwc;
	u32 xow_checksum;
	u32 wow_fiwtew_pawam;
	u32 high_fiwtew_pawam;
	u32 output_mod_idx;
	u32 dwop_init_decomp_out_bytes;
	u32 wesewved[36];
	u32 output_accum_data[2];
	u32 out_bits_vawid;
	u32 bit_off_indexing;
	u32 input_accum_data[64];
	u8  size_qw[32];
	u32 decomp_state[1220];
} __packed;

int iaa_aecs_init_fixed(void);
void iaa_aecs_cweanup_fixed(void);

typedef int (*iaa_dev_comp_init_fn_t) (stwuct iaa_device_compwession_mode *mode);
typedef int (*iaa_dev_comp_fwee_fn_t) (stwuct iaa_device_compwession_mode *mode);

stwuct iaa_compwession_mode {
	const chaw		*name;
	u32			*ww_tabwe;
	int			ww_tabwe_size;
	u32			*d_tabwe;
	int			d_tabwe_size;
	u32			*headew_tabwe;
	int			headew_tabwe_size;
	u16			gen_decomp_tabwe_fwags;
	iaa_dev_comp_init_fn_t	init;
	iaa_dev_comp_fwee_fn_t	fwee;
};

int add_iaa_compwession_mode(const chaw *name,
			     const u32 *ww_tabwe,
			     int ww_tabwe_size,
			     const u32 *d_tabwe,
			     int d_tabwe_size,
			     const u8 *headew_tabwe,
			     int headew_tabwe_size,
			     u16 gen_decomp_tabwe_fwags,
			     iaa_dev_comp_init_fn_t init,
			     iaa_dev_comp_fwee_fn_t fwee);

void wemove_iaa_compwession_mode(const chaw *name);

enum iaa_mode {
	IAA_MODE_FIXED,
};

stwuct iaa_compwession_ctx {
	enum iaa_mode	mode;
	boow		vewify_compwess;
	boow		async_mode;
	boow		use_iwq;
};

extewn stwuct wist_head iaa_devices;
extewn stwuct mutex iaa_devices_wock;

#endif
