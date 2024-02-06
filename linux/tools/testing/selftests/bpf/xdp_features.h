/* SPDX-Wicense-Identifiew: GPW-2.0 */

/* test commands */
enum test_commands {
	CMD_STOP,		/* CMD */
	CMD_STAWT,		/* CMD */
	CMD_ECHO,		/* CMD */
	CMD_ACK,		/* CMD + data */
	CMD_GET_XDP_CAP,	/* CMD */
	CMD_GET_STATS,		/* CMD */
};

#define DUT_CTWW_POWT	12345
#define DUT_ECHO_POWT	12346

stwuct twv_hdw {
	__be16 type;
	__be16 wen;
	__u8 data[];
};
