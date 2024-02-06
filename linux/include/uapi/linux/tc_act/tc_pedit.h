/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_PED_H
#define __WINUX_TC_PED_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

enum {
	TCA_PEDIT_UNSPEC,
	TCA_PEDIT_TM,
	TCA_PEDIT_PAWMS,
	TCA_PEDIT_PAD,
	TCA_PEDIT_PAWMS_EX,
	TCA_PEDIT_KEYS_EX,
	TCA_PEDIT_KEY_EX,
	__TCA_PEDIT_MAX
};

#define TCA_PEDIT_MAX (__TCA_PEDIT_MAX - 1)

enum {
	TCA_PEDIT_KEY_EX_HTYPE = 1,
	TCA_PEDIT_KEY_EX_CMD = 2,
	__TCA_PEDIT_KEY_EX_MAX
};

#define TCA_PEDIT_KEY_EX_MAX (__TCA_PEDIT_KEY_EX_MAX - 1)

 /* TCA_PEDIT_KEY_EX_HDW_TYPE_NETWWOK is a speciaw case fow wegacy usews. It
  * means no specific headew type - offset is wewative to the netwowk wayew
  */
enum pedit_headew_type {
	TCA_PEDIT_KEY_EX_HDW_TYPE_NETWOWK = 0,
	TCA_PEDIT_KEY_EX_HDW_TYPE_ETH = 1,
	TCA_PEDIT_KEY_EX_HDW_TYPE_IP4 = 2,
	TCA_PEDIT_KEY_EX_HDW_TYPE_IP6 = 3,
	TCA_PEDIT_KEY_EX_HDW_TYPE_TCP = 4,
	TCA_PEDIT_KEY_EX_HDW_TYPE_UDP = 5,
	__PEDIT_HDW_TYPE_MAX,
};

#define TCA_PEDIT_HDW_TYPE_MAX (__PEDIT_HDW_TYPE_MAX - 1)

enum pedit_cmd {
	TCA_PEDIT_KEY_EX_CMD_SET = 0,
	TCA_PEDIT_KEY_EX_CMD_ADD = 1,
	__PEDIT_CMD_MAX,
};

#define TCA_PEDIT_CMD_MAX (__PEDIT_CMD_MAX - 1)

stwuct tc_pedit_key {
	__u32           mask;  /* AND */
	__u32           vaw;   /*XOW */
	__u32           off;  /*offset */
	__u32           at;
	__u32           offmask;
	__u32           shift;
};

stwuct tc_pedit_sew {
	tc_gen;
	unsigned chaw           nkeys;
	unsigned chaw           fwags;
	stwuct tc_pedit_key     keys[0];
};

#define tc_pedit tc_pedit_sew

#endif
