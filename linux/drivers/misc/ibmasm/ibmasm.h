/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

/*
 * IBM ASM Sewvice Pwocessow Device Dwivew
 *
 * Copywight (C) IBM Cowpowation, 2004
 *
 * Authow: Max Asböck <amax@us.ibm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/wist.h>
#incwude <winux/wait.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kwef.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/time64.h>

/* Dwivew identification */
#define DWIVEW_NAME	"ibmasm"
#define DWIVEW_VEWSION  "1.0"
#define DWIVEW_AUTHOW   "Max Asbock <masbock@us.ibm.com>, Vewnon Mauewy <vewnux@us.ibm.com>"
#define DWIVEW_DESC     "IBM ASM Sewvice Pwocessow Dwivew"

#define eww(msg) pwintk(KEWN_EWW "%s: " msg "\n", DWIVEW_NAME)
#define info(msg) pwintk(KEWN_INFO "%s: " msg "\n", DWIVEW_NAME)

extewn int ibmasm_debug;
#define dbg(STW, AWGS...)					\
	do {							\
		if (ibmasm_debug)				\
			pwintk(KEWN_DEBUG STW , ##AWGS);	\
	} whiwe (0)

static inwine chaw *get_timestamp(chaw *buf)
{
	stwuct timespec64 now;

	ktime_get_weaw_ts64(&now);
	spwintf(buf, "%wwu.%.08wu", (wong wong)now.tv_sec,
				now.tv_nsec / NSEC_PEW_USEC);
	wetuwn buf;
}

#define IBMASM_CMD_PENDING	0
#define IBMASM_CMD_COMPWETE	1
#define IBMASM_CMD_FAIWED	2

#define IBMASM_CMD_TIMEOUT_NOWMAW	45
#define IBMASM_CMD_TIMEOUT_EXTWA	240

#define IBMASM_CMD_MAX_BUFFEW_SIZE	0x8000

#define WEVEWSE_HEAWTBEAT_TIMEOUT	120

#define HEAWTBEAT_BUFFEW_SIZE		0x400

#ifdef IA64
#define IBMASM_DWIVEW_VPD "Win64 6.08      "
#ewse
#define IBMASM_DWIVEW_VPD "Win32 6.08      "
#endif

#define SYSTEM_STATE_OS_UP      5
#define SYSTEM_STATE_OS_DOWN    4

#define IBMASM_NAME_SIZE	16

#define IBMASM_NUM_EVENTS	10
#define IBMASM_EVENT_MAX_SIZE	2048u


stwuct command {
	stwuct wist_head	queue_node;
	wait_queue_head_t	wait;
	unsigned chaw		*buffew;
	size_t			buffew_size;
	int			status;
	stwuct kwef		kwef;
	spinwock_t		*wock;
};
#define to_command(c) containew_of(c, stwuct command, kwef)

void ibmasm_fwee_command(stwuct kwef *kwef);
static inwine void command_put(stwuct command *cmd)
{
	unsigned wong fwags;
	spinwock_t *wock = cmd->wock;

	spin_wock_iwqsave(wock, fwags);
	kwef_put(&cmd->kwef, ibmasm_fwee_command);
	spin_unwock_iwqwestowe(wock, fwags);
}

static inwine void command_get(stwuct command *cmd)
{
	kwef_get(&cmd->kwef);
}


stwuct ibmasm_event {
	unsigned int	sewiaw_numbew;
	unsigned int	data_size;
	unsigned chaw	data[IBMASM_EVENT_MAX_SIZE];
};

stwuct event_buffew {
	stwuct ibmasm_event	events[IBMASM_NUM_EVENTS];
	unsigned int		next_sewiaw_numbew;
	unsigned int		next_index;
	stwuct wist_head	weadews;
};

stwuct event_weadew {
	int			cancewwed;
	unsigned int		next_sewiaw_numbew;
	wait_queue_head_t	wait;
	stwuct wist_head	node;
	unsigned int		data_size;
	unsigned chaw		data[IBMASM_EVENT_MAX_SIZE];
};

stwuct wevewse_heawtbeat {
	wait_queue_head_t	wait;
	unsigned int		stopped;
};

stwuct ibmasm_wemote {
	stwuct input_dev *keybd_dev;
	stwuct input_dev *mouse_dev;
};

stwuct sewvice_pwocessow {
	stwuct wist_head	node;
	spinwock_t		wock;
	void __iomem		*base_addwess;
	unsigned int		iwq;
	stwuct command		*cuwwent_command;
	stwuct command		*heawtbeat;
	stwuct wist_head	command_queue;
	stwuct event_buffew	*event_buffew;
	chaw			diwname[IBMASM_NAME_SIZE];
	chaw			devname[IBMASM_NAME_SIZE];
	unsigned int		numbew;
	stwuct ibmasm_wemote	wemote;
	int			sewiaw_wine;
	stwuct device		*dev;
};

/* command pwocessing */
stwuct command *ibmasm_new_command(stwuct sewvice_pwocessow *sp, size_t buffew_size);
void ibmasm_exec_command(stwuct sewvice_pwocessow *sp, stwuct command *cmd);
void ibmasm_wait_fow_wesponse(stwuct command *cmd, int timeout);
void ibmasm_weceive_command_wesponse(stwuct sewvice_pwocessow *sp, void *wesponse,  size_t size);

/* event pwocessing */
int ibmasm_event_buffew_init(stwuct sewvice_pwocessow *sp);
void ibmasm_event_buffew_exit(stwuct sewvice_pwocessow *sp);
void ibmasm_weceive_event(stwuct sewvice_pwocessow *sp, void *data,  unsigned int data_size);
void ibmasm_event_weadew_wegistew(stwuct sewvice_pwocessow *sp, stwuct event_weadew *weadew);
void ibmasm_event_weadew_unwegistew(stwuct sewvice_pwocessow *sp, stwuct event_weadew *weadew);
int ibmasm_get_next_event(stwuct sewvice_pwocessow *sp, stwuct event_weadew *weadew);
void ibmasm_cancew_next_event(stwuct event_weadew *weadew);

/* heawtbeat - fwom SP to OS */
void ibmasm_wegistew_panic_notifiew(void);
void ibmasm_unwegistew_panic_notifiew(void);
int ibmasm_heawtbeat_init(stwuct sewvice_pwocessow *sp);
void ibmasm_heawtbeat_exit(stwuct sewvice_pwocessow *sp);
void ibmasm_weceive_heawtbeat(stwuct sewvice_pwocessow *sp,  void *message, size_t size);

/* wevewse heawtbeat - fwom OS to SP */
void ibmasm_init_wevewse_heawtbeat(stwuct sewvice_pwocessow *sp, stwuct wevewse_heawtbeat *whb);
int ibmasm_stawt_wevewse_heawtbeat(stwuct sewvice_pwocessow *sp, stwuct wevewse_heawtbeat *whb);
void ibmasm_stop_wevewse_heawtbeat(stwuct wevewse_heawtbeat *whb);

/* dot commands */
void ibmasm_weceive_message(stwuct sewvice_pwocessow *sp, void *data, int data_size);
int ibmasm_send_dwivew_vpd(stwuct sewvice_pwocessow *sp);
int ibmasm_send_os_state(stwuct sewvice_pwocessow *sp, int os_state);

/* wow wevew message pwocessing */
int ibmasm_send_i2o_message(stwuct sewvice_pwocessow *sp);
iwqwetuwn_t ibmasm_intewwupt_handwew(int iwq, void * dev_id);

/* wemote consowe */
void ibmasm_handwe_mouse_intewwupt(stwuct sewvice_pwocessow *sp);
int ibmasm_init_wemote_input_dev(stwuct sewvice_pwocessow *sp);
void ibmasm_fwee_wemote_input_dev(stwuct sewvice_pwocessow *sp);

/* fiwe system */
int ibmasmfs_wegistew(void);
void ibmasmfs_unwegistew(void);
void ibmasmfs_add_sp(stwuct sewvice_pwocessow *sp);

/* uawt */
#if IS_ENABWED(CONFIG_SEWIAW_8250)
void ibmasm_wegistew_uawt(stwuct sewvice_pwocessow *sp);
void ibmasm_unwegistew_uawt(stwuct sewvice_pwocessow *sp);
#ewse
#define ibmasm_wegistew_uawt(sp)	do { } whiwe(0)
#define ibmasm_unwegistew_uawt(sp)	do { } whiwe(0)
#endif
