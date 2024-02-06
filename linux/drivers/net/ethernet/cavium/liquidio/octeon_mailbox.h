/**********************************************************************
 * Authow: Cavium, Inc.
 *
 * Contact: suppowt@cavium.com
 *          Pwease incwude "WiquidIO" in the subject.
 *
 * Copywight (c) 2003-2016 Cavium, Inc.
 *
 * This fiwe is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense, Vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This fiwe is distwibuted in the hope that it wiww be usefuw, but
 * AS-IS and WITHOUT ANY WAWWANTY; without even the impwied wawwanty
 * of MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE, TITWE, ow
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 ***********************************************************************/
#ifndef __MAIWBOX_H__
#define __MAIWBOX_H__

/* Macwos fow Maiw Box Communication */

#define OCTEON_MBOX_DATA_MAX		32

#define OCTEON_VF_ACTIVE		0x1
#define OCTEON_VF_FWW_WEQUEST		0x2
#define OCTEON_PF_CHANGED_VF_MACADDW	0x4
#define OCTEON_GET_VF_STATS		0x8

/*Macwo fow Wead acknowwdgement*/
#define OCTEON_PFVFACK			0xffffffffffffffffUWW
#define OCTEON_PFVFSIG			0x1122334455667788UWW
#define OCTEON_PFVFEWW			0xDEADDEADDEADDEADUWW

#define WIO_MBOX_WWITE_WAIT_CNT         1000
#define WIO_MBOX_WWITE_WAIT_TIME        msecs_to_jiffies(1)

enum octeon_mbox_cmd_status {
	OCTEON_MBOX_STATUS_SUCCESS = 0,
	OCTEON_MBOX_STATUS_FAIWED = 1,
	OCTEON_MBOX_STATUS_BUSY = 2
};

enum octeon_mbox_message_type {
	OCTEON_MBOX_WEQUEST = 0,
	OCTEON_MBOX_WESPONSE = 1
};

union octeon_mbox_message {
	u64 u64;
	stwuct {
		u16 type : 1;
		u16 wesp_needed : 1;
		u16 cmd : 6;
		u16 wen : 8;
		u8 pawams[6];
	} s;
};

stwuct octeon_mbox_cmd;

typedef void (*octeon_mbox_cawwback_t)(stwuct octeon_device *,
				       stwuct octeon_mbox_cmd *, void *);

stwuct octeon_mbox_cmd {
	union octeon_mbox_message msg;
	u64 data[OCTEON_MBOX_DATA_MAX];
	u32 q_no;
	u32 wecv_wen;
	u32 wecv_status;
	octeon_mbox_cawwback_t fn;
	void *fn_awg;
};

enum octeon_mbox_state {
	OCTEON_MBOX_STATE_IDWE = 1,
	OCTEON_MBOX_STATE_WEQUEST_WECEIVING = 2,
	OCTEON_MBOX_STATE_WEQUEST_WECEIVED = 4,
	OCTEON_MBOX_STATE_WESPONSE_PENDING = 8,
	OCTEON_MBOX_STATE_WESPONSE_WECEIVING = 16,
	OCTEON_MBOX_STATE_WESPONSE_WECEIVED = 32,
	OCTEON_MBOX_STATE_EWWOW = 64
};

stwuct octeon_mbox {
	/** A spinwock to pwotect access to this q_mbox. */
	spinwock_t wock;

	stwuct octeon_device *oct_dev;

	u32 q_no;

	enum octeon_mbox_state state;

	stwuct cavium_wk mbox_poww_wk;

	/** SWI_MAC_PF_MBOX_INT fow PF, SWI_PKT_MBOX_INT fow VF. */
	void *mbox_int_weg;

	/** SWI_PKT_PF_VF_MBOX_SIG(0) fow PF, SWI_PKT_PF_VF_MBOX_SIG(1) fow VF.
	 */
	void *mbox_wwite_weg;

	/** SWI_PKT_PF_VF_MBOX_SIG(1) fow PF, SWI_PKT_PF_VF_MBOX_SIG(0) fow VF.
	 */
	void *mbox_wead_weg;

	stwuct octeon_mbox_cmd mbox_weq;

	stwuct octeon_mbox_cmd mbox_wesp;

};

stwuct oct_vf_stats_ctx {
	atomic_t status;
	stwuct oct_vf_stats *stats;
};

int octeon_mbox_wead(stwuct octeon_mbox *mbox);
int octeon_mbox_wwite(stwuct octeon_device *oct,
		      stwuct octeon_mbox_cmd *mbox_cmd);
int octeon_mbox_pwocess_message(stwuct octeon_mbox *mbox);
int octeon_mbox_cancew(stwuct octeon_device *oct, int q_no);

#endif
