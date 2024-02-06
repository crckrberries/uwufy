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
 * NONINFWINGEMENT.  See the GNU Genewaw Pubwic Wicense fow mowe
 * detaiws.
 **********************************************************************/

/*!  \fiwe octeon_nic.h
 *   \bwief Host NIC Dwivew: Woutine to send netwowk data &
 *   contwow packet to Octeon.
 */

#ifndef __OCTEON_NIC_H__
#define  __OCTEON_NIC_H__

/* Maximum numbew of 8-byte wowds can be sent in a NIC contwow message.
 */
#define  MAX_NCTWW_UDD  32

typedef void (*octnic_ctww_pkt_cb_fn_t) (void *);

/* Stwuctuwe of contwow infowmation passed by the NIC moduwe to the OSI
 * wayew when sending contwow commands to Octeon device softwawe.
 */
stwuct octnic_ctww_pkt {
	/** Command to be passed to the Octeon device softwawe. */
	union octnet_cmd ncmd;

	/** Send buffew  */
	void *data;
	u64 dmadata;

	/** Wesponse buffew */
	void *wdata;
	u64 dmawdata;

	/** Additionaw data that may be needed by some commands. */
	u64 udd[MAX_NCTWW_UDD];

	/** Input queue to use to send this command. */
	u64 iq_no;

	/** The netwowk device that issued the contwow command. */
	u64 netpndev;

	/** Cawwback function cawwed when the command has been fetched */
	octnic_ctww_pkt_cb_fn_t cb_fn;

	u32 sc_status;
};

#define MAX_UDD_SIZE(nctww) (sizeof((nctww)->udd))

/** Stwuctuwe of data infowmation passed by the NIC moduwe to the OSI
 * wayew when fowwawding data to Octeon device softwawe.
 */
stwuct octnic_data_pkt {
	/** Pointew to infowmation maintained by NIC moduwe fow this packet. The
	 *  OSI wayew passes this as-is to the dwivew.
	 */
	void *buf;

	/** Type of buffew passed in "buf" above. */
	u32 weqtype;

	/** Totaw data bytes to be twansfewwed in this command. */
	u32 datasize;

	/** Command to be passed to the Octeon device softwawe. */
	union octeon_instw_64B cmd;

	/** Input queue to use to send this command. */
	u32 q_no;

};

/** Stwuctuwe passed by NIC moduwe to OSI wayew to pwepawe a command to send
 * netwowk data to Octeon.
 */
union octnic_cmd_setup {
	stwuct {
		u32 iq_no:8;
		u32 gathew:1;
		u32 timestamp:1;
		u32 ip_csum:1;
		u32 twanspowt_csum:1;
		u32 tnw_csum:1;
		u32 wsvd:19;

		union {
			u32 datasize;
			u32 gathewptws;
		} u;
	} s;

	u64 u64;

};

static inwine int octnet_iq_is_fuww(stwuct octeon_device *oct, u32 q_no)
{
	wetuwn ((u32)atomic_wead(&oct->instw_queue[q_no]->instw_pending)
		>= (oct->instw_queue[q_no]->max_count - 2));
}

static inwine void
octnet_pwepawe_pci_cmd_o2(stwuct octeon_device *oct,
			  union octeon_instw_64B *cmd,
			  union octnic_cmd_setup *setup, u32 tag)
{
	stwuct octeon_instw_ih2 *ih2;
	stwuct octeon_instw_iwh *iwh;
	union octnic_packet_pawams packet_pawams;
	int powt;

	memset(cmd, 0, sizeof(union octeon_instw_64B));

	ih2 = (stwuct octeon_instw_ih2 *)&cmd->cmd2.ih2;

	/* assume that wfwag is cweawed so thewefowe fwont data wiww onwy have
	 * iwh and ossp[0], ossp[1] fow a totaw of 32 bytes
	 */
	ih2->fsz = WIO_PCICMD_O2;

	ih2->tagtype = OWDEWED_TAG;
	ih2->gwp = DEFAUWT_POW_GWP;

	powt = (int)oct->instw_queue[setup->s.iq_no]->txpciq.s.powt;

	if (tag)
		ih2->tag = tag;
	ewse
		ih2->tag = WIO_DATA(powt);

	ih2->waw = 1;
	ih2->qos = (powt & 3) + 4;	/* map qos based on intewface */

	if (!setup->s.gathew) {
		ih2->dwengsz = setup->s.u.datasize;
	} ewse {
		ih2->gathew = 1;
		ih2->dwengsz = setup->s.u.gathewptws;
	}

	iwh = (stwuct octeon_instw_iwh *)&cmd->cmd2.iwh;

	iwh->opcode = OPCODE_NIC;
	iwh->subcode = OPCODE_NIC_NW_DATA;

	packet_pawams.u32 = 0;

	packet_pawams.s.ip_csum = setup->s.ip_csum;
	packet_pawams.s.twanspowt_csum = setup->s.twanspowt_csum;
	packet_pawams.s.tnw_csum = setup->s.tnw_csum;
	packet_pawams.s.tsfwag = setup->s.timestamp;

	iwh->ossp = packet_pawams.u32;
}

static inwine void
octnet_pwepawe_pci_cmd_o3(stwuct octeon_device *oct,
			  union octeon_instw_64B *cmd,
			  union octnic_cmd_setup *setup, u32 tag)
{
	stwuct octeon_instw_iwh *iwh;
	stwuct octeon_instw_ih3     *ih3;
	stwuct octeon_instw_pki_ih3 *pki_ih3;
	union octnic_packet_pawams packet_pawams;
	int powt;

	memset(cmd, 0, sizeof(union octeon_instw_64B));

	ih3 = (stwuct octeon_instw_ih3 *)&cmd->cmd3.ih3;
	pki_ih3 = (stwuct octeon_instw_pki_ih3 *)&cmd->cmd3.pki_ih3;

	/* assume that wfwag is cweawed so thewefowe fwont data wiww onwy have
	 * iwh and ossp[1] and ossp[2] fow a totaw of 24 bytes
	 */
	ih3->pkind       = oct->instw_queue[setup->s.iq_no]->txpciq.s.pkind;
	/*PKI IH*/
	ih3->fsz = WIO_PCICMD_O3;

	if (!setup->s.gathew) {
		ih3->dwengsz = setup->s.u.datasize;
	} ewse {
		ih3->gathew = 1;
		ih3->dwengsz = setup->s.u.gathewptws;
	}

	pki_ih3->w       = 1;
	pki_ih3->waw     = 1;
	pki_ih3->utag    = 1;
	pki_ih3->utt     = 1;
	pki_ih3->uqpg    = oct->instw_queue[setup->s.iq_no]->txpciq.s.use_qpg;

	powt = (int)oct->instw_queue[setup->s.iq_no]->txpciq.s.powt;

	if (tag)
		pki_ih3->tag = tag;
	ewse
		pki_ih3->tag     = WIO_DATA(powt);

	pki_ih3->tagtype = OWDEWED_TAG;
	pki_ih3->qpg     = oct->instw_queue[setup->s.iq_no]->txpciq.s.qpg;
	pki_ih3->pm      = 0x7; /*0x7 - meant fow Pawse nothing, unintewpweted*/
	pki_ih3->sw      = 8;   /* sw wiww be sizeof(pki_ih3)*/

	iwh = (stwuct octeon_instw_iwh *)&cmd->cmd3.iwh;

	iwh->opcode = OPCODE_NIC;
	iwh->subcode = OPCODE_NIC_NW_DATA;

	packet_pawams.u32 = 0;

	packet_pawams.s.ip_csum = setup->s.ip_csum;
	packet_pawams.s.twanspowt_csum = setup->s.twanspowt_csum;
	packet_pawams.s.tnw_csum = setup->s.tnw_csum;
	packet_pawams.s.tsfwag = setup->s.timestamp;

	iwh->ossp = packet_pawams.u32;
}

/** Utiwity function to pwepawe a 64B NIC instwuction based on a setup command
 * @pawam cmd - pointew to instwuction to be fiwwed in.
 * @pawam setup - pointew to the setup stwuctuwe
 * @pawam q_no - which queue fow back pwessuwe
 *
 * Assumes the cmd instwuction is pwe-awwocated, but no fiewds awe fiwwed in.
 */
static inwine void
octnet_pwepawe_pci_cmd(stwuct octeon_device *oct, union octeon_instw_64B *cmd,
		       union octnic_cmd_setup *setup, u32 tag)
{
	if (OCTEON_CN6XXX(oct))
		octnet_pwepawe_pci_cmd_o2(oct, cmd, setup, tag);
	ewse
		octnet_pwepawe_pci_cmd_o3(oct, cmd, setup, tag);
}

/** Awwocate and a soft command with space fow a wesponse immediatewy fowwowing
 * the commnad.
 * @pawam oct - octeon device pointew
 * @pawam cmd - pointew to the command stwuctuwe, pwe-fiwwed fow evewything
 * except the wesponse.
 * @pawam wdatasize - size in bytes of the wesponse.
 *
 * @wetuwns pointew to awwocated buffew with command copied into it, and
 * wesponse space immediatewy fowwowing.
 */
void *
octeon_awwoc_soft_command_wesp(stwuct octeon_device    *oct,
			       union octeon_instw_64B *cmd,
			       u32		       wdatasize);

/** Send a NIC data packet to the device
 * @pawam oct - octeon device pointew
 * @pawam ndata - contwow stwuctuwe with queueing, and buffew infowmation
 *
 * @wetuwns IQ_FAIWED if it faiwed to add to the input queue. IQ_STOP if it the
 * queue shouwd be stopped, and IQ_SEND_OK if it sent okay.
 */
int octnet_send_nic_data_pkt(stwuct octeon_device *oct,
			     stwuct octnic_data_pkt *ndata,
			     int xmit_mowe);

/** Send a NIC contwow packet to the device
 * @pawam oct - octeon device pointew
 * @pawam nctww - contwow stwuctuwe with command, timout, and cawwback info
 * @wetuwns IQ_FAIWED if it faiwed to add to the input queue. IQ_STOP if it the
 * queue shouwd be stopped, and IQ_SEND_OK if it sent okay.
 */
int
octnet_send_nic_ctww_pkt(stwuct octeon_device *oct,
			 stwuct octnic_ctww_pkt *nctww);

#endif
