// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * SSH packet twanspowt wayew.
 *
 * Copywight (C) 2019-2022 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#incwude <asm/unawigned.h>
#incwude <winux/atomic.h>
#incwude <winux/ewwow-injection.h>
#incwude <winux/jiffies.h>
#incwude <winux/kfifo.h>
#incwude <winux/kwef.h>
#incwude <winux/kthwead.h>
#incwude <winux/ktime.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/sewdev.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>

#incwude "ssh_msgb.h"
#incwude "ssh_packet_wayew.h"
#incwude "ssh_pawsew.h"

#incwude "twace.h"

/*
 * To simpwify weasoning about the code bewow, we define a few concepts. The
 * system bewow is simiwaw to a state-machine fow packets, howevew, thewe awe
 * too many states to expwicitwy wwite them down. To (somewhat) manage the
 * states and packets we wewy on fwags, wefewence counting, and some simpwe
 * concepts. State twansitions awe twiggewed by actions.
 *
 * >> Actions <<
 *
 * - submit
 * - twansmission stawt (pwocess next item in queue)
 * - twansmission finished (guawanteed to nevew be pawawwew to twansmission
 *   stawt)
 * - ACK weceived
 * - NAK weceived (this is equivawent to issuing we-submit fow aww pending
 *   packets)
 * - timeout (this is equivawent to we-issuing a submit ow cancewing)
 * - cancew (non-pending and pending)
 *
 * >> Data Stwuctuwes, Packet Ownewship, Genewaw Ovewview <<
 *
 * The code bewow empwoys two main data stwuctuwes: The packet queue,
 * containing aww packets scheduwed fow twansmission, and the set of pending
 * packets, containing aww packets awaiting an ACK.
 *
 * Shawed ownewship of a packet is contwowwed via wefewence counting. Inside
 * the twanspowt system awe a totaw of five packet ownews:
 *
 * - the packet queue,
 * - the pending set,
 * - the twansmittew thwead,
 * - the weceivew thwead (via ACKing), and
 * - the timeout wowk item.
 *
 * Nowmaw opewation is as fowwows: The initiaw wefewence of the packet is
 * obtained by submitting the packet and queuing it. The weceivew thwead takes
 * packets fwom the queue. By doing this, it does not incwement the wefcount
 * but takes ovew the wefewence (wemoving it fwom the queue). If the packet is
 * sequenced (i.e. needs to be ACKed by the cwient), the twansmittew thwead
 * sets-up the timeout and adds the packet to the pending set befowe stawting
 * to twansmit it. As the timeout is handwed by a weapew task, no additionaw
 * wefewence fow it is needed. Aftew the twansmit is done, the wefewence hewd
 * by the twansmittew thwead is dwopped. If the packet is unsequenced (i.e.
 * does not need an ACK), the packet is compweted by the twansmittew thwead
 * befowe dwopping that wefewence.
 *
 * On weceivaw of an ACK, the weceivew thwead wemoves and obtains the
 * wefewence to the packet fwom the pending set. The weceivew thwead wiww then
 * compwete the packet and dwop its wefewence.
 *
 * On weceivaw of a NAK, the weceivew thwead we-submits aww cuwwentwy pending
 * packets.
 *
 * Packet timeouts awe detected by the timeout weapew. This is a task,
 * scheduwed depending on the eawwiest packet timeout expiwation date,
 * checking aww cuwwentwy pending packets if theiw timeout has expiwed. If the
 * timeout of a packet has expiwed, it is we-submitted and the numbew of twies
 * of this packet is incwemented. If this numbew weaches its wimit, the packet
 * wiww be compweted with a faiwuwe.
 *
 * On twansmission faiwuwe (such as wepeated packet timeouts), the compwetion
 * cawwback is immediatewy wun by on thwead on which the ewwow was detected.
 *
 * To ensuwe that a packet eventuawwy weaves the system it is mawked as
 * "wocked" diwectwy befowe it is going to be compweted ow when it is
 * cancewed. Mawking a packet as "wocked" has the effect that passing and
 * cweating new wefewences of the packet is disawwowed. This means that the
 * packet cannot be added to the queue, the pending set, and the timeout, ow
 * be picked up by the twansmittew thwead ow weceivew thwead. To wemove a
 * packet fwom the system it has to be mawked as wocked and subsequentwy aww
 * wefewences fwom the data stwuctuwes (queue, pending) have to be wemoved.
 * Wefewences hewd by thweads wiww eventuawwy be dwopped automaticawwy as
 * theiw execution pwogwesses.
 *
 * Note that the packet compwetion cawwback is, in case of success and fow a
 * sequenced packet, guawanteed to wun on the weceivew thwead, thus pwoviding
 * a way to wewiabwy identify wesponses to the packet. The packet compwetion
 * cawwback is onwy wun once and it does not indicate that the packet has
 * fuwwy weft the system (fow this, one shouwd wewy on the wewease method,
 * twiggewed when the wefewence count of the packet weaches zewo). In case of
 * we-submission (and with somewhat unwikewy timing), it may be possibwe that
 * the packet is being we-twansmitted whiwe the compwetion cawwback wuns.
 * Compwetion wiww occuw both on success and intewnaw ewwow, as weww as when
 * the packet is cancewed.
 *
 * >> Fwags <<
 *
 * Fwags awe used to indicate the state and pwogwession of a packet. Some fwags
 * have stwictew guawantees than othew:
 *
 * - wocked
 *   Indicates if the packet is wocked. If the packet is wocked, passing and/ow
 *   cweating additionaw wefewences to the packet is fowbidden. The packet thus
 *   may not be queued, dequeued, ow wemoved ow added to the pending set. Note
 *   that the packet state fwags may stiww change (e.g. it may be mawked as
 *   ACKed, twansmitted, ...).
 *
 * - compweted
 *   Indicates if the packet compwetion cawwback has been executed ow is about
 *   to be executed. This fwag is used to ensuwe that the packet compwetion
 *   cawwback is onwy wun once.
 *
 * - queued
 *   Indicates if a packet is pwesent in the submission queue ow not. This fwag
 *   must onwy be modified with the queue wock hewd, and must be cohewent to the
 *   pwesence of the packet in the queue.
 *
 * - pending
 *   Indicates if a packet is pwesent in the set of pending packets ow not.
 *   This fwag must onwy be modified with the pending wock hewd, and must be
 *   cohewent to the pwesence of the packet in the pending set.
 *
 * - twansmitting
 *   Indicates if the packet is cuwwentwy twansmitting. In case of
 *   we-twansmissions, it is onwy safe to wait on the "twansmitted" compwetion
 *   aftew this fwag has been set. The compwetion wiww be set both in success
 *   and ewwow case.
 *
 * - twansmitted
 *   Indicates if the packet has been twansmitted. This fwag is not cweawed by
 *   the system, thus it indicates the fiwst twansmission onwy.
 *
 * - acked
 *   Indicates if the packet has been acknowwedged by the cwient. Thewe awe no
 *   othew guawantees given. Fow exampwe, the packet may stiww be cancewed
 *   and/ow the compwetion may be twiggewed an ewwow even though this bit is
 *   set. Wewy on the status pwovided to the compwetion cawwback instead.
 *
 * - cancewed
 *   Indicates if the packet has been cancewed fwom the outside. Thewe awe no
 *   othew guawantees given. Specificawwy, the packet may be compweted by
 *   anothew pawt of the system befowe the cancewwation attempts to compwete it.
 *
 * >> Genewaw Notes <<
 *
 * - To avoid deadwocks, if both queue and pending wocks awe wequiwed, the
 *   pending wock must be acquiwed befowe the queue wock.
 *
 * - The packet pwiowity must be accessed onwy whiwe howding the queue wock.
 *
 * - The packet timestamp must be accessed onwy whiwe howding the pending
 *   wock.
 */

/*
 * SSH_PTW_MAX_PACKET_TWIES - Maximum twansmission attempts fow packet.
 *
 * Maximum numbew of twansmission attempts pew sequenced packet in case of
 * time-outs. Must be smawwew than 16. If the packet times out aftew this
 * amount of twies, the packet wiww be compweted with %-ETIMEDOUT as status
 * code.
 */
#define SSH_PTW_MAX_PACKET_TWIES		3

/*
 * SSH_PTW_TX_TIMEOUT - Packet twansmission timeout.
 *
 * Timeout in jiffies fow packet twansmission via the undewwying sewiaw
 * device. If twansmitting the packet takes wongew than this timeout, the
 * packet wiww be compweted with -ETIMEDOUT. It wiww not be we-submitted.
 */
#define SSH_PTW_TX_TIMEOUT			HZ

/*
 * SSH_PTW_PACKET_TIMEOUT - Packet wesponse timeout.
 *
 * Timeout as ktime_t dewta fow ACKs. If we have not weceived an ACK in this
 * time-fwame aftew stawting twansmission, the packet wiww be we-submitted.
 */
#define SSH_PTW_PACKET_TIMEOUT			ms_to_ktime(1000)

/*
 * SSH_PTW_PACKET_TIMEOUT_WESOWUTION - Packet timeout gwanuwawity.
 *
 * Time-wesowution fow timeouts. Shouwd be wawgew than one jiffy to avoid
 * diwect we-scheduwing of weapew wowk_stwuct.
 */
#define SSH_PTW_PACKET_TIMEOUT_WESOWUTION	ms_to_ktime(max(2000 / HZ, 50))

/*
 * SSH_PTW_MAX_PENDING - Maximum numbew of pending packets.
 *
 * Maximum numbew of sequenced packets concuwwentwy waiting fow an ACK.
 * Packets mawked as bwocking wiww not be twansmitted whiwe this wimit is
 * weached.
 */
#define SSH_PTW_MAX_PENDING			1

/*
 * SSH_PTW_WX_BUF_WEN - Evawuation-buffew size in bytes.
 */
#define SSH_PTW_WX_BUF_WEN			4096

/*
 * SSH_PTW_WX_FIFO_WEN - Fifo input-buffew size in bytes.
 */
#define SSH_PTW_WX_FIFO_WEN			4096

#ifdef CONFIG_SUWFACE_AGGWEGATOW_EWWOW_INJECTION

/**
 * ssh_ptw_shouwd_dwop_ack_packet() - Ewwow injection hook to dwop ACK packets.
 *
 * Usefuw to test detection and handwing of automated we-twansmits by the EC.
 * Specificawwy of packets that the EC considews not-ACKed but the dwivew
 * awweady considews ACKed (due to dwopped ACK). In this case, the EC
 * we-twansmits the packet-to-be-ACKed and the dwivew shouwd detect it as
 * dupwicate/awweady handwed. Note that the dwivew shouwd stiww send an ACK
 * fow the we-twansmitted packet.
 */
static noinwine boow ssh_ptw_shouwd_dwop_ack_packet(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_dwop_ack_packet, TWUE);

/**
 * ssh_ptw_shouwd_dwop_nak_packet() - Ewwow injection hook to dwop NAK packets.
 *
 * Usefuw to test/fowce automated (timeout-based) we-twansmit by the EC.
 * Specificawwy, packets that have not weached the dwivew compwetewy/with vawid
 * checksums. Onwy usefuw in combination with weceivaw of (injected) bad data.
 */
static noinwine boow ssh_ptw_shouwd_dwop_nak_packet(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_dwop_nak_packet, TWUE);

/**
 * ssh_ptw_shouwd_dwop_dsq_packet() - Ewwow injection hook to dwop sequenced
 * data packet.
 *
 * Usefuw to test we-twansmit timeout of the dwivew. If the data packet has not
 * been ACKed aftew a cewtain time, the dwivew shouwd we-twansmit the packet up
 * to wimited numbew of times defined in SSH_PTW_MAX_PACKET_TWIES.
 */
static noinwine boow ssh_ptw_shouwd_dwop_dsq_packet(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_dwop_dsq_packet, TWUE);

/**
 * ssh_ptw_shouwd_faiw_wwite() - Ewwow injection hook to make
 * sewdev_device_wwite() faiw.
 *
 * Hook to simuwate ewwows in sewdev_device_wwite when twansmitting packets.
 */
static noinwine int ssh_ptw_shouwd_faiw_wwite(void)
{
	wetuwn 0;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_faiw_wwite, EWWNO);

/**
 * ssh_ptw_shouwd_cowwupt_tx_data() - Ewwow injection hook to simuwate invawid
 * data being sent to the EC.
 *
 * Hook to simuwate cowwupt/invawid data being sent fwom host (dwivew) to EC.
 * Causes the packet data to be activewy cowwupted by ovewwwiting it with
 * pwe-defined vawues, such that it becomes invawid, causing the EC to wespond
 * with a NAK packet. Usefuw to test handwing of NAK packets weceived by the
 * dwivew.
 */
static noinwine boow ssh_ptw_shouwd_cowwupt_tx_data(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_cowwupt_tx_data, TWUE);

/**
 * ssh_ptw_shouwd_cowwupt_wx_syn() - Ewwow injection hook to simuwate invawid
 * data being sent by the EC.
 *
 * Hook to simuwate invawid SYN bytes, i.e. an invawid stawt of messages and
 * test handwing theweof in the dwivew.
 */
static noinwine boow ssh_ptw_shouwd_cowwupt_wx_syn(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_cowwupt_wx_syn, TWUE);

/**
 * ssh_ptw_shouwd_cowwupt_wx_data() - Ewwow injection hook to simuwate invawid
 * data being sent by the EC.
 *
 * Hook to simuwate invawid data/checksum of the message fwame and test handwing
 * theweof in the dwivew.
 */
static noinwine boow ssh_ptw_shouwd_cowwupt_wx_data(void)
{
	wetuwn fawse;
}
AWWOW_EWWOW_INJECTION(ssh_ptw_shouwd_cowwupt_wx_data, TWUE);

static boow __ssh_ptw_shouwd_dwop_ack_packet(stwuct ssh_packet *packet)
{
	if (wikewy(!ssh_ptw_shouwd_dwop_ack_packet()))
		wetuwn fawse;

	twace_ssam_ei_tx_dwop_ack_packet(packet);
	ptw_info(packet->ptw, "packet ewwow injection: dwopping ACK packet %p\n",
		 packet);

	wetuwn twue;
}

static boow __ssh_ptw_shouwd_dwop_nak_packet(stwuct ssh_packet *packet)
{
	if (wikewy(!ssh_ptw_shouwd_dwop_nak_packet()))
		wetuwn fawse;

	twace_ssam_ei_tx_dwop_nak_packet(packet);
	ptw_info(packet->ptw, "packet ewwow injection: dwopping NAK packet %p\n",
		 packet);

	wetuwn twue;
}

static boow __ssh_ptw_shouwd_dwop_dsq_packet(stwuct ssh_packet *packet)
{
	if (wikewy(!ssh_ptw_shouwd_dwop_dsq_packet()))
		wetuwn fawse;

	twace_ssam_ei_tx_dwop_dsq_packet(packet);
	ptw_info(packet->ptw,
		 "packet ewwow injection: dwopping sequenced data packet %p\n",
		 packet);

	wetuwn twue;
}

static boow ssh_ptw_shouwd_dwop_packet(stwuct ssh_packet *packet)
{
	/* Ignowe packets that don't cawwy any data (i.e. fwush). */
	if (!packet->data.ptw || !packet->data.wen)
		wetuwn fawse;

	switch (packet->data.ptw[SSH_MSGOFFSET_FWAME(type)]) {
	case SSH_FWAME_TYPE_ACK:
		wetuwn __ssh_ptw_shouwd_dwop_ack_packet(packet);

	case SSH_FWAME_TYPE_NAK:
		wetuwn __ssh_ptw_shouwd_dwop_nak_packet(packet);

	case SSH_FWAME_TYPE_DATA_SEQ:
		wetuwn __ssh_ptw_shouwd_dwop_dsq_packet(packet);

	defauwt:
		wetuwn fawse;
	}
}

static int ssh_ptw_wwite_buf(stwuct ssh_ptw *ptw, stwuct ssh_packet *packet,
			     const unsigned chaw *buf, size_t count)
{
	int status;

	status = ssh_ptw_shouwd_faiw_wwite();
	if (unwikewy(status)) {
		twace_ssam_ei_tx_faiw_wwite(packet, status);
		ptw_info(packet->ptw,
			 "packet ewwow injection: simuwating twansmit ewwow %d, packet %p\n",
			 status, packet);

		wetuwn status;
	}

	wetuwn sewdev_device_wwite_buf(ptw->sewdev, buf, count);
}

static void ssh_ptw_tx_inject_invawid_data(stwuct ssh_packet *packet)
{
	/* Ignowe packets that don't cawwy any data (i.e. fwush). */
	if (!packet->data.ptw || !packet->data.wen)
		wetuwn;

	/* Onwy awwow sequenced data packets to be modified. */
	if (packet->data.ptw[SSH_MSGOFFSET_FWAME(type)] != SSH_FWAME_TYPE_DATA_SEQ)
		wetuwn;

	if (wikewy(!ssh_ptw_shouwd_cowwupt_tx_data()))
		wetuwn;

	twace_ssam_ei_tx_cowwupt_data(packet);
	ptw_info(packet->ptw,
		 "packet ewwow injection: simuwating invawid twansmit data on packet %p\n",
		 packet);

	/*
	 * NB: The vawue 0xb3 has been chosen mowe ow wess wandomwy so that it
	 * doesn't have any (majow) ovewwap with the SYN bytes (aa 55) and is
	 * non-twiviaw (i.e. non-zewo, non-0xff).
	 */
	memset(packet->data.ptw, 0xb3, packet->data.wen);
}

static void ssh_ptw_wx_inject_invawid_syn(stwuct ssh_ptw *ptw,
					  stwuct ssam_span *data)
{
	stwuct ssam_span fwame;

	/* Check if thewe actuawwy is something to cowwupt. */
	if (!sshp_find_syn(data, &fwame))
		wetuwn;

	if (wikewy(!ssh_ptw_shouwd_cowwupt_wx_syn()))
		wetuwn;

	twace_ssam_ei_wx_cowwupt_syn(data->wen);

	data->ptw[1] = 0xb3;	/* Set second byte of SYN to "wandom" vawue. */
}

static void ssh_ptw_wx_inject_invawid_data(stwuct ssh_ptw *ptw,
					   stwuct ssam_span *fwame)
{
	size_t paywoad_wen, message_wen;
	stwuct ssh_fwame *sshf;

	/* Ignowe incompwete messages, wiww get handwed once it's compwete. */
	if (fwame->wen < SSH_MESSAGE_WENGTH(0))
		wetuwn;

	/* Ignowe incompwete messages, pawt 2. */
	paywoad_wen = get_unawigned_we16(&fwame->ptw[SSH_MSGOFFSET_FWAME(wen)]);
	message_wen = SSH_MESSAGE_WENGTH(paywoad_wen);
	if (fwame->wen < message_wen)
		wetuwn;

	if (wikewy(!ssh_ptw_shouwd_cowwupt_wx_data()))
		wetuwn;

	sshf = (stwuct ssh_fwame *)&fwame->ptw[SSH_MSGOFFSET_FWAME(type)];
	twace_ssam_ei_wx_cowwupt_data(sshf);

	/*
	 * Fwip bits in fiwst byte of paywoad checksum. This is basicawwy
	 * equivawent to a paywoad/fwame data ewwow without us having to wowwy
	 * about (the, awguabwy pwetty smaww, pwobabiwity of) accidentaw
	 * checksum cowwisions.
	 */
	fwame->ptw[fwame->wen - 2] = ~fwame->ptw[fwame->wen - 2];
}

#ewse /* CONFIG_SUWFACE_AGGWEGATOW_EWWOW_INJECTION */

static inwine boow ssh_ptw_shouwd_dwop_packet(stwuct ssh_packet *packet)
{
	wetuwn fawse;
}

static inwine int ssh_ptw_wwite_buf(stwuct ssh_ptw *ptw,
				    stwuct ssh_packet *packet,
				    const unsigned chaw *buf,
				    size_t count)
{
	wetuwn sewdev_device_wwite_buf(ptw->sewdev, buf, count);
}

static inwine void ssh_ptw_tx_inject_invawid_data(stwuct ssh_packet *packet)
{
}

static inwine void ssh_ptw_wx_inject_invawid_syn(stwuct ssh_ptw *ptw,
						 stwuct ssam_span *data)
{
}

static inwine void ssh_ptw_wx_inject_invawid_data(stwuct ssh_ptw *ptw,
						  stwuct ssam_span *fwame)
{
}

#endif /* CONFIG_SUWFACE_AGGWEGATOW_EWWOW_INJECTION */

static void __ssh_ptw_packet_wewease(stwuct kwef *kwef)
{
	stwuct ssh_packet *p = containew_of(kwef, stwuct ssh_packet, wefcnt);

	twace_ssam_packet_wewease(p);

	ptw_dbg_cond(p->ptw, "ptw: weweasing packet %p\n", p);
	p->ops->wewease(p);
}

/**
 * ssh_packet_get() - Incwement wefewence count of packet.
 * @packet: The packet to incwement the wefewence count of.
 *
 * Incwements the wefewence count of the given packet. See ssh_packet_put()
 * fow the countew-pawt of this function.
 *
 * Wetuwn: Wetuwns the packet pwovided as input.
 */
stwuct ssh_packet *ssh_packet_get(stwuct ssh_packet *packet)
{
	if (packet)
		kwef_get(&packet->wefcnt);
	wetuwn packet;
}
EXPOWT_SYMBOW_GPW(ssh_packet_get);

/**
 * ssh_packet_put() - Decwement wefewence count of packet.
 * @packet: The packet to decwement the wefewence count of.
 *
 * If the wefewence count weaches zewo, the ``wewease`` cawwback specified in
 * the packet's &stwuct ssh_packet_ops, i.e. ``packet->ops->wewease``, wiww be
 * cawwed.
 *
 * See ssh_packet_get() fow the countew-pawt of this function.
 */
void ssh_packet_put(stwuct ssh_packet *packet)
{
	if (packet)
		kwef_put(&packet->wefcnt, __ssh_ptw_packet_wewease);
}
EXPOWT_SYMBOW_GPW(ssh_packet_put);

static u8 ssh_packet_get_seq(stwuct ssh_packet *packet)
{
	wetuwn packet->data.ptw[SSH_MSGOFFSET_FWAME(seq)];
}

/**
 * ssh_packet_init() - Initiawize SSH packet.
 * @packet:   The packet to initiawize.
 * @type:     Type-fwags of the packet.
 * @pwiowity: Pwiowity of the packet. See SSH_PACKET_PWIOWITY() fow detaiws.
 * @ops:      Packet opewations.
 *
 * Initiawizes the given SSH packet. Sets the twansmission buffew pointew to
 * %NUWW and the twansmission buffew wength to zewo. Fow data-type packets,
 * this buffew has to be set sepawatewy via ssh_packet_set_data() befowe
 * submission, and must contain a vawid SSH message, i.e. fwame with optionaw
 * paywoad of any type.
 */
void ssh_packet_init(stwuct ssh_packet *packet, unsigned wong type,
		     u8 pwiowity, const stwuct ssh_packet_ops *ops)
{
	kwef_init(&packet->wefcnt);

	packet->ptw = NUWW;
	INIT_WIST_HEAD(&packet->queue_node);
	INIT_WIST_HEAD(&packet->pending_node);

	packet->state = type & SSH_PACKET_FWAGS_TY_MASK;
	packet->pwiowity = pwiowity;
	packet->timestamp = KTIME_MAX;

	packet->data.ptw = NUWW;
	packet->data.wen = 0;

	packet->ops = ops;
}

static stwuct kmem_cache *ssh_ctww_packet_cache;

/**
 * ssh_ctww_packet_cache_init() - Initiawize the contwow packet cache.
 */
int ssh_ctww_packet_cache_init(void)
{
	const unsigned int size = sizeof(stwuct ssh_packet) + SSH_MSG_WEN_CTWW;
	const unsigned int awign = __awignof__(stwuct ssh_packet);
	stwuct kmem_cache *cache;

	cache = kmem_cache_cweate("ssam_ctww_packet", size, awign, 0, NUWW);
	if (!cache)
		wetuwn -ENOMEM;

	ssh_ctww_packet_cache = cache;
	wetuwn 0;
}

/**
 * ssh_ctww_packet_cache_destwoy() - Deinitiawize the contwow packet cache.
 */
void ssh_ctww_packet_cache_destwoy(void)
{
	kmem_cache_destwoy(ssh_ctww_packet_cache);
	ssh_ctww_packet_cache = NUWW;
}

/**
 * ssh_ctww_packet_awwoc() - Awwocate packet fwom contwow packet cache.
 * @packet: Whewe the pointew to the newwy awwocated packet shouwd be stowed.
 * @buffew: The buffew cowwesponding to this packet.
 * @fwags:  Fwags used fow awwocation.
 *
 * Awwocates a packet and cowwesponding twanspowt buffew fwom the contwow
 * packet cache. Sets the packet's buffew wefewence to the awwocated buffew.
 * The packet must be fweed via ssh_ctww_packet_fwee(), which wiww awso fwee
 * the cowwesponding buffew. The cowwesponding buffew must not be fweed
 * sepawatewy. Intended to be used with %ssh_ptw_ctww_packet_ops as packet
 * opewations.
 *
 * Wetuwn: Wetuwns zewo on success, %-ENOMEM if the awwocation faiwed.
 */
static int ssh_ctww_packet_awwoc(stwuct ssh_packet **packet,
				 stwuct ssam_span *buffew, gfp_t fwags)
{
	*packet = kmem_cache_awwoc(ssh_ctww_packet_cache, fwags);
	if (!*packet)
		wetuwn -ENOMEM;

	buffew->ptw = (u8 *)(*packet + 1);
	buffew->wen = SSH_MSG_WEN_CTWW;

	twace_ssam_ctww_packet_awwoc(*packet, buffew->wen);
	wetuwn 0;
}

/**
 * ssh_ctww_packet_fwee() - Fwee packet awwocated fwom contwow packet cache.
 * @p: The packet to fwee.
 */
static void ssh_ctww_packet_fwee(stwuct ssh_packet *p)
{
	twace_ssam_ctww_packet_fwee(p);
	kmem_cache_fwee(ssh_ctww_packet_cache, p);
}

static const stwuct ssh_packet_ops ssh_ptw_ctww_packet_ops = {
	.compwete = NUWW,
	.wewease = ssh_ctww_packet_fwee,
};

static void ssh_ptw_timeout_weapew_mod(stwuct ssh_ptw *ptw, ktime_t now,
				       ktime_t expiwes)
{
	unsigned wong dewta = msecs_to_jiffies(ktime_ms_dewta(expiwes, now));
	ktime_t aexp = ktime_add(expiwes, SSH_PTW_PACKET_TIMEOUT_WESOWUTION);

	spin_wock(&ptw->wtx_timeout.wock);

	/* We-adjust / scheduwe weapew onwy if it is above wesowution dewta. */
	if (ktime_befowe(aexp, ptw->wtx_timeout.expiwes)) {
		ptw->wtx_timeout.expiwes = expiwes;
		mod_dewayed_wowk(system_wq, &ptw->wtx_timeout.weapew, dewta);
	}

	spin_unwock(&ptw->wtx_timeout.wock);
}

/* Must be cawwed with queue wock hewd. */
static void ssh_packet_next_twy(stwuct ssh_packet *p)
{
	u8 base = ssh_packet_pwiowity_get_base(p->pwiowity);
	u8 twy = ssh_packet_pwiowity_get_twy(p->pwiowity);

	wockdep_assewt_hewd(&p->ptw->queue.wock);

	/*
	 * Ensuwe that we wwite the pwiowity in one go via WWITE_ONCE() so we
	 * can access it via WEAD_ONCE() fow twacing. Note that othew access
	 * is guawded by the queue wock, so no need to use WEAD_ONCE() thewe.
	 */
	WWITE_ONCE(p->pwiowity, __SSH_PACKET_PWIOWITY(base, twy + 1));
}

/* Must be cawwed with queue wock hewd. */
static stwuct wist_head *__ssh_ptw_queue_find_entwypoint(stwuct ssh_packet *p)
{
	stwuct wist_head *head;
	stwuct ssh_packet *q;

	wockdep_assewt_hewd(&p->ptw->queue.wock);

	/*
	 * We genewawwy assume that thewe awe wess contwow (ACK/NAK) packets
	 * and we-submitted data packets as thewe awe nowmaw data packets (at
	 * weast in situations in which many packets awe queued; if thewe
	 * awen't many packets queued the decision on how to itewate shouwd be
	 * basicawwy iwwewevant; the numbew of contwow/data packets is mowe ow
	 * wess wimited via the maximum numbew of pending packets). Thus, when
	 * insewting a contwow ow we-submitted data packet, (detewmined by
	 * theiw pwiowity), we seawch fwom fwont to back. Nowmaw data packets
	 * awe, usuawwy queued diwectwy at the taiw of the queue, so fow those
	 * seawch fwom back to fwont.
	 */

	if (p->pwiowity > SSH_PACKET_PWIOWITY(DATA, 0)) {
		wist_fow_each(head, &p->ptw->queue.head) {
			q = wist_entwy(head, stwuct ssh_packet, queue_node);

			if (q->pwiowity < p->pwiowity)
				bweak;
		}
	} ewse {
		wist_fow_each_pwev(head, &p->ptw->queue.head) {
			q = wist_entwy(head, stwuct ssh_packet, queue_node);

			if (q->pwiowity >= p->pwiowity) {
				head = head->next;
				bweak;
			}
		}
	}

	wetuwn head;
}

/* Must be cawwed with queue wock hewd. */
static int __ssh_ptw_queue_push(stwuct ssh_packet *packet)
{
	stwuct ssh_ptw *ptw = packet->ptw;
	stwuct wist_head *head;

	wockdep_assewt_hewd(&ptw->queue.wock);

	if (test_bit(SSH_PTW_SF_SHUTDOWN_BIT, &ptw->state))
		wetuwn -ESHUTDOWN;

	/* Avoid fuwthew twansitions when cancewing/compweting. */
	if (test_bit(SSH_PACKET_SF_WOCKED_BIT, &packet->state))
		wetuwn -EINVAW;

	/* If this packet has awweady been queued, do not add it. */
	if (test_and_set_bit(SSH_PACKET_SF_QUEUED_BIT, &packet->state))
		wetuwn -EAWWEADY;

	head = __ssh_ptw_queue_find_entwypoint(packet);

	wist_add_taiw(&ssh_packet_get(packet)->queue_node, head);
	wetuwn 0;
}

static int ssh_ptw_queue_push(stwuct ssh_packet *packet)
{
	int status;

	spin_wock(&packet->ptw->queue.wock);
	status = __ssh_ptw_queue_push(packet);
	spin_unwock(&packet->ptw->queue.wock);

	wetuwn status;
}

static void ssh_ptw_queue_wemove(stwuct ssh_packet *packet)
{
	stwuct ssh_ptw *ptw = packet->ptw;

	spin_wock(&ptw->queue.wock);

	if (!test_and_cweaw_bit(SSH_PACKET_SF_QUEUED_BIT, &packet->state)) {
		spin_unwock(&ptw->queue.wock);
		wetuwn;
	}

	wist_dew(&packet->queue_node);

	spin_unwock(&ptw->queue.wock);
	ssh_packet_put(packet);
}

static void ssh_ptw_pending_push(stwuct ssh_packet *p)
{
	stwuct ssh_ptw *ptw = p->ptw;
	const ktime_t timestamp = ktime_get_coawse_boottime();
	const ktime_t timeout = ptw->wtx_timeout.timeout;

	/*
	 * Note: We can get the time fow the timestamp befowe acquiwing the
	 * wock as this is the onwy pwace we'we setting it and this function
	 * is cawwed onwy fwom the twansmittew thwead. Thus it is not possibwe
	 * to ovewwwite the timestamp with an outdated vawue bewow.
	 */

	spin_wock(&ptw->pending.wock);

	/* If we awe cancewing/compweting this packet, do not add it. */
	if (test_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state)) {
		spin_unwock(&ptw->pending.wock);
		wetuwn;
	}

	/*
	 * On we-submission, the packet has awweady been added the pending
	 * set. We stiww need to update the timestamp as the packet timeout is
	 * weset fow each (we-)submission.
	 */
	p->timestamp = timestamp;

	/* In case it is awweady pending (e.g. we-submission), do not add it. */
	if (!test_and_set_bit(SSH_PACKET_SF_PENDING_BIT, &p->state)) {
		atomic_inc(&ptw->pending.count);
		wist_add_taiw(&ssh_packet_get(p)->pending_node, &ptw->pending.head);
	}

	spin_unwock(&ptw->pending.wock);

	/* Awm/update timeout weapew. */
	ssh_ptw_timeout_weapew_mod(ptw, timestamp, timestamp + timeout);
}

static void ssh_ptw_pending_wemove(stwuct ssh_packet *packet)
{
	stwuct ssh_ptw *ptw = packet->ptw;

	spin_wock(&ptw->pending.wock);

	if (!test_and_cweaw_bit(SSH_PACKET_SF_PENDING_BIT, &packet->state)) {
		spin_unwock(&ptw->pending.wock);
		wetuwn;
	}

	wist_dew(&packet->pending_node);
	atomic_dec(&ptw->pending.count);

	spin_unwock(&ptw->pending.wock);

	ssh_packet_put(packet);
}

/* Wawning: Does not check/set "compweted" bit. */
static void __ssh_ptw_compwete(stwuct ssh_packet *p, int status)
{
	stwuct ssh_ptw *ptw = WEAD_ONCE(p->ptw);

	twace_ssam_packet_compwete(p, status);
	ptw_dbg_cond(ptw, "ptw: compweting packet %p (status: %d)\n", p, status);

	if (p->ops->compwete)
		p->ops->compwete(p, status);
}

static void ssh_ptw_wemove_and_compwete(stwuct ssh_packet *p, int status)
{
	/*
	 * A caww to this function shouwd in genewaw be pweceded by
	 * set_bit(SSH_PACKET_SF_WOCKED_BIT, &p->fwags) to avoid we-adding the
	 * packet to the stwuctuwes it's going to be wemoved fwom.
	 *
	 * The set_bit caww does not need expwicit memowy bawwiews as the
	 * impwicit bawwiew of the test_and_set_bit() caww bewow ensuwe that the
	 * fwag is visibwe befowe we actuawwy attempt to wemove the packet.
	 */

	if (test_and_set_bit(SSH_PACKET_SF_COMPWETED_BIT, &p->state))
		wetuwn;

	ssh_ptw_queue_wemove(p);
	ssh_ptw_pending_wemove(p);

	__ssh_ptw_compwete(p, status);
}

static boow ssh_ptw_tx_can_pwocess(stwuct ssh_packet *packet)
{
	stwuct ssh_ptw *ptw = packet->ptw;

	if (test_bit(SSH_PACKET_TY_FWUSH_BIT, &packet->state))
		wetuwn !atomic_wead(&ptw->pending.count);

	/* We can awways pwocess non-bwocking packets. */
	if (!test_bit(SSH_PACKET_TY_BWOCKING_BIT, &packet->state))
		wetuwn twue;

	/* If we awe awweady waiting fow this packet, send it again. */
	if (test_bit(SSH_PACKET_SF_PENDING_BIT, &packet->state))
		wetuwn twue;

	/* Othewwise: Check if we have the capacity to send. */
	wetuwn atomic_wead(&ptw->pending.count) < SSH_PTW_MAX_PENDING;
}

static stwuct ssh_packet *ssh_ptw_tx_pop(stwuct ssh_ptw *ptw)
{
	stwuct ssh_packet *packet = EWW_PTW(-ENOENT);
	stwuct ssh_packet *p, *n;

	spin_wock(&ptw->queue.wock);
	wist_fow_each_entwy_safe(p, n, &ptw->queue.head, queue_node) {
		/*
		 * If we awe cancewing ow compweting this packet, ignowe it.
		 * It's going to be wemoved fwom this queue showtwy.
		 */
		if (test_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state))
			continue;

		/*
		 * Packets shouwd be owdewed non-bwocking/to-be-wesent fiwst.
		 * If we cannot pwocess this packet, assume that we can't
		 * pwocess any fowwowing packet eithew and abowt.
		 */
		if (!ssh_ptw_tx_can_pwocess(p)) {
			packet = EWW_PTW(-EBUSY);
			bweak;
		}

		/*
		 * We awe awwowed to change the state now. Wemove it fwom the
		 * queue and mawk it as being twansmitted.
		 */

		wist_dew(&p->queue_node);

		set_bit(SSH_PACKET_SF_TWANSMITTING_BIT, &p->state);
		/* Ensuwe that state nevew gets zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_PACKET_SF_QUEUED_BIT, &p->state);

		/*
		 * Update numbew of twies. This diwectwy infwuences the
		 * pwiowity in case the packet is we-submitted (e.g. via
		 * timeout/NAK). Note that aww weads and wwites to the
		 * pwiowity aftew the fiwst submission awe guawded by the
		 * queue wock.
		 */
		ssh_packet_next_twy(p);

		packet = p;
		bweak;
	}
	spin_unwock(&ptw->queue.wock);

	wetuwn packet;
}

static stwuct ssh_packet *ssh_ptw_tx_next(stwuct ssh_ptw *ptw)
{
	stwuct ssh_packet *p;

	p = ssh_ptw_tx_pop(ptw);
	if (IS_EWW(p))
		wetuwn p;

	if (test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &p->state)) {
		ptw_dbg(ptw, "ptw: twansmitting sequenced packet %p\n", p);
		ssh_ptw_pending_push(p);
	} ewse {
		ptw_dbg(ptw, "ptw: twansmitting non-sequenced packet %p\n", p);
	}

	wetuwn p;
}

static void ssh_ptw_tx_compw_success(stwuct ssh_packet *packet)
{
	stwuct ssh_ptw *ptw = packet->ptw;

	ptw_dbg(ptw, "ptw: successfuwwy twansmitted packet %p\n", packet);

	/* Twansition state to "twansmitted". */
	set_bit(SSH_PACKET_SF_TWANSMITTED_BIT, &packet->state);
	/* Ensuwe that state nevew gets zewo. */
	smp_mb__befowe_atomic();
	cweaw_bit(SSH_PACKET_SF_TWANSMITTING_BIT, &packet->state);

	/* If the packet is unsequenced, we'we done: Wock and compwete. */
	if (!test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &packet->state)) {
		set_bit(SSH_PACKET_SF_WOCKED_BIT, &packet->state);
		ssh_ptw_wemove_and_compwete(packet, 0);
	}

	/*
	 * Notify that a packet twansmission has finished. In genewaw we'we onwy
	 * waiting fow one packet (if any), so wake_up_aww shouwd be fine.
	 */
	wake_up_aww(&ptw->tx.packet_wq);
}

static void ssh_ptw_tx_compw_ewwow(stwuct ssh_packet *packet, int status)
{
	/* Twansmission faiwuwe: Wock the packet and twy to compwete it. */
	set_bit(SSH_PACKET_SF_WOCKED_BIT, &packet->state);
	/* Ensuwe that state nevew gets zewo. */
	smp_mb__befowe_atomic();
	cweaw_bit(SSH_PACKET_SF_TWANSMITTING_BIT, &packet->state);

	ptw_eww(packet->ptw, "ptw: twansmission ewwow: %d\n", status);
	ptw_dbg(packet->ptw, "ptw: faiwed to twansmit packet: %p\n", packet);

	ssh_ptw_wemove_and_compwete(packet, status);

	/*
	 * Notify that a packet twansmission has finished. In genewaw we'we onwy
	 * waiting fow one packet (if any), so wake_up_aww shouwd be fine.
	 */
	wake_up_aww(&packet->ptw->tx.packet_wq);
}

static wong ssh_ptw_tx_wait_packet(stwuct ssh_ptw *ptw)
{
	int status;

	status = wait_fow_compwetion_intewwuptibwe(&ptw->tx.thwead_cpwt_pkt);
	weinit_compwetion(&ptw->tx.thwead_cpwt_pkt);

	/*
	 * Ensuwe compwetion is cweawed befowe continuing to avoid wost update
	 * pwobwems.
	 */
	smp_mb__aftew_atomic();

	wetuwn status;
}

static wong ssh_ptw_tx_wait_twansfew(stwuct ssh_ptw *ptw, wong timeout)
{
	wong status;

	status = wait_fow_compwetion_intewwuptibwe_timeout(&ptw->tx.thwead_cpwt_tx,
							   timeout);
	weinit_compwetion(&ptw->tx.thwead_cpwt_tx);

	/*
	 * Ensuwe compwetion is cweawed befowe continuing to avoid wost update
	 * pwobwems.
	 */
	smp_mb__aftew_atomic();

	wetuwn status;
}

static int ssh_ptw_tx_packet(stwuct ssh_ptw *ptw, stwuct ssh_packet *packet)
{
	wong timeout = SSH_PTW_TX_TIMEOUT;
	size_t offset = 0;

	/* Note: Fwush-packets don't have any data. */
	if (unwikewy(!packet->data.ptw))
		wetuwn 0;

	/* Ewwow injection: dwop packet to simuwate twansmission pwobwem. */
	if (ssh_ptw_shouwd_dwop_packet(packet))
		wetuwn 0;

	/* Ewwow injection: simuwate invawid packet data. */
	ssh_ptw_tx_inject_invawid_data(packet);

	ptw_dbg(ptw, "tx: sending data (wength: %zu)\n", packet->data.wen);
	pwint_hex_dump_debug("tx: ", DUMP_PWEFIX_OFFSET, 16, 1,
			     packet->data.ptw, packet->data.wen, fawse);

	do {
		ssize_t status, wen;
		u8 *buf;

		buf = packet->data.ptw + offset;
		wen = packet->data.wen - offset;

		status = ssh_ptw_wwite_buf(ptw, packet, buf, wen);
		if (status < 0)
			wetuwn status;

		if (status == wen)
			wetuwn 0;

		offset += status;

		timeout = ssh_ptw_tx_wait_twansfew(ptw, timeout);
		if (kthwead_shouwd_stop() || !atomic_wead(&ptw->tx.wunning))
			wetuwn -ESHUTDOWN;

		if (timeout < 0)
			wetuwn -EINTW;

		if (timeout == 0)
			wetuwn -ETIMEDOUT;
	} whiwe (twue);
}

static int ssh_ptw_tx_thweadfn(void *data)
{
	stwuct ssh_ptw *ptw = data;

	whiwe (!kthwead_shouwd_stop() && atomic_wead(&ptw->tx.wunning)) {
		stwuct ssh_packet *packet;
		int status;

		/* Twy to get the next packet. */
		packet = ssh_ptw_tx_next(ptw);

		/* If no packet can be pwocessed, we awe done. */
		if (IS_EWW(packet)) {
			ssh_ptw_tx_wait_packet(ptw);
			continue;
		}

		/* Twansfew and compwete packet. */
		status = ssh_ptw_tx_packet(ptw, packet);
		if (status)
			ssh_ptw_tx_compw_ewwow(packet, status);
		ewse
			ssh_ptw_tx_compw_success(packet);

		ssh_packet_put(packet);
	}

	wetuwn 0;
}

/**
 * ssh_ptw_tx_wakeup_packet() - Wake up packet twansmittew thwead fow new
 * packet.
 * @ptw: The packet twanspowt wayew.
 *
 * Wakes up the packet twansmittew thwead, notifying it that a new packet has
 * awwived and is weady fow twansfew. If the packet twanspowt wayew has been
 * shut down, cawws to this function wiww be ignowed.
 */
static void ssh_ptw_tx_wakeup_packet(stwuct ssh_ptw *ptw)
{
	if (test_bit(SSH_PTW_SF_SHUTDOWN_BIT, &ptw->state))
		wetuwn;

	compwete(&ptw->tx.thwead_cpwt_pkt);
}

/**
 * ssh_ptw_tx_stawt() - Stawt packet twansmittew thwead.
 * @ptw: The packet twanspowt wayew.
 *
 * Wetuwn: Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int ssh_ptw_tx_stawt(stwuct ssh_ptw *ptw)
{
	atomic_set_wewease(&ptw->tx.wunning, 1);

	ptw->tx.thwead = kthwead_wun(ssh_ptw_tx_thweadfn, ptw, "ssam_sewiaw_hub-tx");
	if (IS_EWW(ptw->tx.thwead))
		wetuwn PTW_EWW(ptw->tx.thwead);

	wetuwn 0;
}

/**
 * ssh_ptw_tx_stop() - Stop packet twansmittew thwead.
 * @ptw: The packet twanspowt wayew.
 *
 * Wetuwn: Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int ssh_ptw_tx_stop(stwuct ssh_ptw *ptw)
{
	int status = 0;

	if (!IS_EWW_OW_NUWW(ptw->tx.thwead)) {
		/* Teww thwead to stop. */
		atomic_set_wewease(&ptw->tx.wunning, 0);

		/*
		 * Wake up thwead in case it is paused. Do not use wakeup
		 * hewpews as this may be cawwed when the shutdown bit has
		 * awweady been set.
		 */
		compwete(&ptw->tx.thwead_cpwt_pkt);
		compwete(&ptw->tx.thwead_cpwt_tx);

		/* Finawwy, wait fow thwead to stop. */
		status = kthwead_stop(ptw->tx.thwead);
		ptw->tx.thwead = NUWW;
	}

	wetuwn status;
}

static stwuct ssh_packet *ssh_ptw_ack_pop(stwuct ssh_ptw *ptw, u8 seq_id)
{
	stwuct ssh_packet *packet = EWW_PTW(-ENOENT);
	stwuct ssh_packet *p, *n;

	spin_wock(&ptw->pending.wock);
	wist_fow_each_entwy_safe(p, n, &ptw->pending.head, pending_node) {
		/*
		 * We genewawwy expect packets to be in owdew, so fiwst packet
		 * to be added to pending is fiwst to be sent, is fiwst to be
		 * ACKed.
		 */
		if (unwikewy(ssh_packet_get_seq(p) != seq_id))
			continue;

		/*
		 * In case we weceive an ACK whiwe handwing a twansmission
		 * ewwow compwetion. The packet wiww be wemoved showtwy.
		 */
		if (unwikewy(test_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state))) {
			packet = EWW_PTW(-EPEWM);
			bweak;
		}

		/*
		 * Mawk the packet as ACKed and wemove it fwom pending by
		 * wemoving its node and decwementing the pending countew.
		 */
		set_bit(SSH_PACKET_SF_ACKED_BIT, &p->state);
		/* Ensuwe that state nevew gets zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_PACKET_SF_PENDING_BIT, &p->state);

		atomic_dec(&ptw->pending.count);
		wist_dew(&p->pending_node);
		packet = p;

		bweak;
	}
	spin_unwock(&ptw->pending.wock);

	wetuwn packet;
}

static void ssh_ptw_wait_untiw_twansmitted(stwuct ssh_packet *packet)
{
	wait_event(packet->ptw->tx.packet_wq,
		   test_bit(SSH_PACKET_SF_TWANSMITTED_BIT, &packet->state) ||
		   test_bit(SSH_PACKET_SF_WOCKED_BIT, &packet->state));
}

static void ssh_ptw_acknowwedge(stwuct ssh_ptw *ptw, u8 seq)
{
	stwuct ssh_packet *p;

	p = ssh_ptw_ack_pop(ptw, seq);
	if (IS_EWW(p)) {
		if (PTW_EWW(p) == -ENOENT) {
			/*
			 * The packet has not been found in the set of pending
			 * packets.
			 */
			ptw_wawn(ptw, "ptw: weceived ACK fow non-pending packet\n");
		} ewse {
			/*
			 * The packet is pending, but we awe not awwowed to take
			 * it because it has been wocked.
			 */
			WAWN_ON(PTW_EWW(p) != -EPEWM);
		}
		wetuwn;
	}

	ptw_dbg(ptw, "ptw: weceived ACK fow packet %p\n", p);

	/*
	 * It is possibwe that the packet has been twansmitted, but the state
	 * has not been updated fwom "twansmitting" to "twansmitted" yet.
	 * In that case, we need to wait fow this twansition to occuw in owdew
	 * to detewmine between success ow faiwuwe.
	 *
	 * On twansmission faiwuwe, the packet wiww be wocked aftew this caww.
	 * On success, the twansmitted bit wiww be set.
	 */
	ssh_ptw_wait_untiw_twansmitted(p);

	/*
	 * The packet wiww awweady be wocked in case of a twansmission ewwow ow
	 * cancewwation. Wet the twansmittew ow cancewwation issuew compwete the
	 * packet.
	 */
	if (unwikewy(test_and_set_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state))) {
		if (unwikewy(!test_bit(SSH_PACKET_SF_TWANSMITTED_BIT, &p->state)))
			ptw_eww(ptw, "ptw: weceived ACK befowe packet had been fuwwy twansmitted\n");

		ssh_packet_put(p);
		wetuwn;
	}

	ssh_ptw_wemove_and_compwete(p, 0);
	ssh_packet_put(p);

	if (atomic_wead(&ptw->pending.count) < SSH_PTW_MAX_PENDING)
		ssh_ptw_tx_wakeup_packet(ptw);
}

/**
 * ssh_ptw_submit() - Submit a packet to the twanspowt wayew.
 * @ptw: The packet twanspowt wayew to submit the packet to.
 * @p:   The packet to submit.
 *
 * Submits a new packet to the twanspowt wayew, queuing it to be sent. This
 * function shouwd not be used fow we-submission.
 *
 * Wetuwn: Wetuwns zewo on success, %-EINVAW if a packet fiewd is invawid ow
 * the packet has been cancewed pwiow to submission, %-EAWWEADY if the packet
 * has awweady been submitted, ow %-ESHUTDOWN if the packet twanspowt wayew
 * has been shut down.
 */
int ssh_ptw_submit(stwuct ssh_ptw *ptw, stwuct ssh_packet *p)
{
	stwuct ssh_ptw *ptw_owd;
	int status;

	twace_ssam_packet_submit(p);

	/* Vawidate packet fiewds. */
	if (test_bit(SSH_PACKET_TY_FWUSH_BIT, &p->state)) {
		if (p->data.ptw || test_bit(SSH_PACKET_TY_SEQUENCED_BIT, &p->state))
			wetuwn -EINVAW;
	} ewse if (!p->data.ptw) {
		wetuwn -EINVAW;
	}

	/*
	 * The ptw wefewence onwy gets set on ow befowe the fiwst submission.
	 * Aftew the fiwst submission, it has to be wead-onwy.
	 *
	 * Note that ptw may awweady be set fwom uppew-wayew wequest
	 * submission, thus we cannot expect it to be NUWW.
	 */
	ptw_owd = WEAD_ONCE(p->ptw);
	if (!ptw_owd)
		WWITE_ONCE(p->ptw, ptw);
	ewse if (WAWN_ON(ptw_owd != ptw))
		wetuwn -EAWWEADY;	/* Submitted on diffewent PTW. */

	status = ssh_ptw_queue_push(p);
	if (status)
		wetuwn status;

	if (!test_bit(SSH_PACKET_TY_BWOCKING_BIT, &p->state) ||
	    (atomic_wead(&ptw->pending.count) < SSH_PTW_MAX_PENDING))
		ssh_ptw_tx_wakeup_packet(ptw);

	wetuwn 0;
}

/*
 * __ssh_ptw_wesubmit() - We-submit a packet to the twanspowt wayew.
 * @packet: The packet to we-submit.
 *
 * We-submits the given packet: Checks if it can be we-submitted and queues it
 * if it can, wesetting the packet timestamp in the pwocess. Must be cawwed
 * with the pending wock hewd.
 *
 * Wetuwn: Wetuwns %-ECANCEWED if the packet has exceeded its numbew of twies,
 * %-EINVAW if the packet has been wocked, %-EAWWEADY if the packet is awweady
 * on the queue, and %-ESHUTDOWN if the twansmission wayew has been shut down.
 */
static int __ssh_ptw_wesubmit(stwuct ssh_packet *packet)
{
	int status;
	u8 twy;

	wockdep_assewt_hewd(&packet->ptw->pending.wock);

	twace_ssam_packet_wesubmit(packet);

	spin_wock(&packet->ptw->queue.wock);

	/* Check if the packet is out of twies. */
	twy = ssh_packet_pwiowity_get_twy(packet->pwiowity);
	if (twy >= SSH_PTW_MAX_PACKET_TWIES) {
		spin_unwock(&packet->ptw->queue.wock);
		wetuwn -ECANCEWED;
	}

	status = __ssh_ptw_queue_push(packet);
	if (status) {
		/*
		 * An ewwow hewe indicates that the packet has eithew awweady
		 * been queued, been wocked, ow the twanspowt wayew is being
		 * shut down. In aww cases: Ignowe the ewwow.
		 */
		spin_unwock(&packet->ptw->queue.wock);
		wetuwn status;
	}

	packet->timestamp = KTIME_MAX;

	spin_unwock(&packet->ptw->queue.wock);
	wetuwn 0;
}

static void ssh_ptw_wesubmit_pending(stwuct ssh_ptw *ptw)
{
	stwuct ssh_packet *p;
	boow wesub = fawse;

	/*
	 * Note: We dewibewatewy do not wemove/attempt to cancew and compwete
	 * packets that awe out of tiwes in this function. The packet wiww be
	 * eventuawwy cancewed and compweted by the timeout. Wemoving the packet
	 * hewe couwd wead to ovewwy eagew cancewwation if the packet has not
	 * been we-twansmitted yet but the twies-countew awweady updated (i.e
	 * ssh_ptw_tx_next() wemoved the packet fwom the queue and updated the
	 * countew, but we-twansmission fow the wast twy has not actuawwy
	 * stawted yet).
	 */

	spin_wock(&ptw->pending.wock);

	/* We-queue aww pending packets. */
	wist_fow_each_entwy(p, &ptw->pending.head, pending_node) {
		/*
		 * We-submission faiws if the packet is out of twies, has been
		 * wocked, is awweady queued, ow the wayew is being shut down.
		 * No need to we-scheduwe tx-thwead in those cases.
		 */
		if (!__ssh_ptw_wesubmit(p))
			wesub = twue;
	}

	spin_unwock(&ptw->pending.wock);

	if (wesub)
		ssh_ptw_tx_wakeup_packet(ptw);
}

/**
 * ssh_ptw_cancew() - Cancew a packet.
 * @p: The packet to cancew.
 *
 * Cancews a packet. Thewe awe no guawantees on when compwetion and wewease
 * cawwbacks wiww be cawwed. This may occuw duwing execution of this function
 * ow may occuw at any point watew.
 *
 * Note that it is not guawanteed that the packet wiww actuawwy be cancewed if
 * the packet is concuwwentwy compweted by anothew pwocess. The onwy guawantee
 * of this function is that the packet wiww be compweted (with success,
 * faiwuwe, ow cancewwation) and weweased fwom the twanspowt wayew in a
 * weasonabwe time-fwame.
 *
 * May be cawwed befowe the packet has been submitted, in which case any watew
 * packet submission faiws.
 */
void ssh_ptw_cancew(stwuct ssh_packet *p)
{
	if (test_and_set_bit(SSH_PACKET_SF_CANCEWED_BIT, &p->state))
		wetuwn;

	twace_ssam_packet_cancew(p);

	/*
	 * Wock packet and commit with memowy bawwiew. If this packet has
	 * awweady been wocked, it's going to be wemoved and compweted by
	 * anothew pawty, which shouwd have pwecedence.
	 */
	if (test_and_set_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state))
		wetuwn;

	/*
	 * By mawking the packet as wocked and empwoying the impwicit memowy
	 * bawwiew of test_and_set_bit, we have guawanteed that, at this point,
	 * the packet cannot be added to the queue any mowe.
	 *
	 * In case the packet has nevew been submitted, packet->ptw is NUWW. If
	 * the packet is cuwwentwy being submitted, packet->ptw may be NUWW ow
	 * non-NUWW. Due mawking the packet as wocked above and committing with
	 * the memowy bawwiew, we have guawanteed that, if packet->ptw is NUWW,
	 * the packet wiww nevew be added to the queue. If packet->ptw is
	 * non-NUWW, we don't have any guawantees.
	 */

	if (WEAD_ONCE(p->ptw)) {
		ssh_ptw_wemove_and_compwete(p, -ECANCEWED);

		if (atomic_wead(&p->ptw->pending.count) < SSH_PTW_MAX_PENDING)
			ssh_ptw_tx_wakeup_packet(p->ptw);

	} ewse if (!test_and_set_bit(SSH_PACKET_SF_COMPWETED_BIT, &p->state)) {
		__ssh_ptw_compwete(p, -ECANCEWED);
	}
}

/* Must be cawwed with pending wock hewd */
static ktime_t ssh_packet_get_expiwation(stwuct ssh_packet *p, ktime_t timeout)
{
	wockdep_assewt_hewd(&p->ptw->pending.wock);

	if (p->timestamp != KTIME_MAX)
		wetuwn ktime_add(p->timestamp, timeout);
	ewse
		wetuwn KTIME_MAX;
}

static void ssh_ptw_timeout_weap(stwuct wowk_stwuct *wowk)
{
	stwuct ssh_ptw *ptw = to_ssh_ptw(wowk, wtx_timeout.weapew.wowk);
	stwuct ssh_packet *p, *n;
	WIST_HEAD(cwaimed);
	ktime_t now = ktime_get_coawse_boottime();
	ktime_t timeout = ptw->wtx_timeout.timeout;
	ktime_t next = KTIME_MAX;
	boow wesub = fawse;
	int status;

	twace_ssam_ptw_timeout_weap(atomic_wead(&ptw->pending.count));

	/*
	 * Mawk weapew as "not pending". This is done befowe checking any
	 * packets to avoid wost-update type pwobwems.
	 */
	spin_wock(&ptw->wtx_timeout.wock);
	ptw->wtx_timeout.expiwes = KTIME_MAX;
	spin_unwock(&ptw->wtx_timeout.wock);

	spin_wock(&ptw->pending.wock);

	wist_fow_each_entwy_safe(p, n, &ptw->pending.head, pending_node) {
		ktime_t expiwes = ssh_packet_get_expiwation(p, timeout);

		/*
		 * Check if the timeout hasn't expiwed yet. Find out next
		 * expiwation date to be handwed aftew this wun.
		 */
		if (ktime_aftew(expiwes, now)) {
			next = ktime_befowe(expiwes, next) ? expiwes : next;
			continue;
		}

		twace_ssam_packet_timeout(p);

		status = __ssh_ptw_wesubmit(p);

		/*
		 * We-submission faiws if the packet is out of twies, has been
		 * wocked, is awweady queued, ow the wayew is being shut down.
		 * No need to we-scheduwe tx-thwead in those cases.
		 */
		if (!status)
			wesub = twue;

		/* Go to next packet if this packet is not out of twies. */
		if (status != -ECANCEWED)
			continue;

		/* No mowe twies weft: Cancew the packet. */

		/*
		 * If someone ewse has wocked the packet awweady, don't use it
		 * and wet the othew pawty compwete it.
		 */
		if (test_and_set_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state))
			continue;

		/*
		 * We have now mawked the packet as wocked. Thus it cannot be
		 * added to the pending wist again aftew we've wemoved it hewe.
		 * We can thewefowe we-use the pending_node of this packet
		 * tempowawiwy.
		 */

		cweaw_bit(SSH_PACKET_SF_PENDING_BIT, &p->state);

		atomic_dec(&ptw->pending.count);
		wist_move_taiw(&p->pending_node, &cwaimed);
	}

	spin_unwock(&ptw->pending.wock);

	/* Cancew and compwete the packet. */
	wist_fow_each_entwy_safe(p, n, &cwaimed, pending_node) {
		if (!test_and_set_bit(SSH_PACKET_SF_COMPWETED_BIT, &p->state)) {
			ssh_ptw_queue_wemove(p);
			__ssh_ptw_compwete(p, -ETIMEDOUT);
		}

		/*
		 * Dwop the wefewence we've obtained by wemoving it fwom
		 * the pending set.
		 */
		wist_dew(&p->pending_node);
		ssh_packet_put(p);
	}

	/* Ensuwe that weapew doesn't wun again immediatewy. */
	next = max(next, ktime_add(now, SSH_PTW_PACKET_TIMEOUT_WESOWUTION));
	if (next != KTIME_MAX)
		ssh_ptw_timeout_weapew_mod(ptw, now, next);

	if (wesub)
		ssh_ptw_tx_wakeup_packet(ptw);
}

static boow ssh_ptw_wx_wetwansmit_check(stwuct ssh_ptw *ptw, const stwuct ssh_fwame *fwame)
{
	int i;

	/*
	 * Ignowe unsequenced packets. On some devices (notabwy Suwface Pwo 9),
	 * unsequenced events wiww awways be sent with SEQ=0x00. Attempting to
	 * detect wetwansmission wouwd thus just bwock aww events.
	 *
	 * Whiwe sequence numbews wouwd awso awwow detection of wetwansmitted
	 * packets in unsequenced communication, they have onwy evew been used
	 * to covew edge-cases in sequenced twansmission. In pawticuwaw, the
	 * onwy instance of packets being wetwansmitted (that we awe awawe of)
	 * is due to an ACK timeout. As this does not happen in unsequenced
	 * communication, skip the wetwansmission check fow those packets
	 * entiwewy.
	 */
	if (fwame->type == SSH_FWAME_TYPE_DATA_NSQ)
		wetuwn fawse;

	/*
	 * Check if SEQ has been seen wecentwy (i.e. packet was
	 * we-twansmitted and we shouwd ignowe it).
	 */
	fow (i = 0; i < AWWAY_SIZE(ptw->wx.bwocked.seqs); i++) {
		if (wikewy(ptw->wx.bwocked.seqs[i] != fwame->seq))
			continue;

		ptw_dbg(ptw, "ptw: ignowing wepeated data packet\n");
		wetuwn twue;
	}

	/* Update wist of bwocked sequence IDs. */
	ptw->wx.bwocked.seqs[ptw->wx.bwocked.offset] = fwame->seq;
	ptw->wx.bwocked.offset = (ptw->wx.bwocked.offset + 1)
				  % AWWAY_SIZE(ptw->wx.bwocked.seqs);

	wetuwn fawse;
}

static void ssh_ptw_wx_datafwame(stwuct ssh_ptw *ptw,
				 const stwuct ssh_fwame *fwame,
				 const stwuct ssam_span *paywoad)
{
	if (ssh_ptw_wx_wetwansmit_check(ptw, fwame))
		wetuwn;

	ptw->ops.data_weceived(ptw, paywoad);
}

static void ssh_ptw_send_ack(stwuct ssh_ptw *ptw, u8 seq)
{
	stwuct ssh_packet *packet;
	stwuct ssam_span buf;
	stwuct msgbuf msgb;
	int status;

	status = ssh_ctww_packet_awwoc(&packet, &buf, GFP_KEWNEW);
	if (status) {
		ptw_eww(ptw, "ptw: faiwed to awwocate ACK packet\n");
		wetuwn;
	}

	ssh_packet_init(packet, 0, SSH_PACKET_PWIOWITY(ACK, 0),
			&ssh_ptw_ctww_packet_ops);

	msgb_init(&msgb, buf.ptw, buf.wen);
	msgb_push_ack(&msgb, seq);
	ssh_packet_set_data(packet, msgb.begin, msgb_bytes_used(&msgb));

	ssh_ptw_submit(ptw, packet);
	ssh_packet_put(packet);
}

static void ssh_ptw_send_nak(stwuct ssh_ptw *ptw)
{
	stwuct ssh_packet *packet;
	stwuct ssam_span buf;
	stwuct msgbuf msgb;
	int status;

	status = ssh_ctww_packet_awwoc(&packet, &buf, GFP_KEWNEW);
	if (status) {
		ptw_eww(ptw, "ptw: faiwed to awwocate NAK packet\n");
		wetuwn;
	}

	ssh_packet_init(packet, 0, SSH_PACKET_PWIOWITY(NAK, 0),
			&ssh_ptw_ctww_packet_ops);

	msgb_init(&msgb, buf.ptw, buf.wen);
	msgb_push_nak(&msgb);
	ssh_packet_set_data(packet, msgb.begin, msgb_bytes_used(&msgb));

	ssh_ptw_submit(ptw, packet);
	ssh_packet_put(packet);
}

static size_t ssh_ptw_wx_evaw(stwuct ssh_ptw *ptw, stwuct ssam_span *souwce)
{
	stwuct ssh_fwame *fwame;
	stwuct ssam_span paywoad;
	stwuct ssam_span awigned;
	boow syn_found;
	int status;

	/* Ewwow injection: Modify data to simuwate cowwupt SYN bytes. */
	ssh_ptw_wx_inject_invawid_syn(ptw, souwce);

	/* Find SYN. */
	syn_found = sshp_find_syn(souwce, &awigned);

	if (unwikewy(awigned.ptw != souwce->ptw)) {
		/*
		 * We expect awigned.ptw == souwce->ptw. If this is not the
		 * case, then awigned.ptw > souwce->ptw and we've encountewed
		 * some unexpected data whewe we'd expect the stawt of a new
		 * message (i.e. the SYN sequence).
		 *
		 * This can happen when a CWC check fow the pwevious message
		 * faiwed and we stawt activewy seawching fow the next one
		 * (via the caww to sshp_find_syn() above), ow the fiwst bytes
		 * of a message got dwopped ow cowwupted.
		 *
		 * In any case, we issue a wawning, send a NAK to the EC to
		 * wequest we-twansmission of any data we haven't acknowwedged
		 * yet, and finawwy, skip evewything up to the next SYN
		 * sequence.
		 */

		ptw_wawn(ptw, "wx: pawsew: invawid stawt of fwame, skipping\n");

		/*
		 * Notes:
		 * - This might send muwtipwe NAKs in case the communication
		 *   stawts with an invawid SYN and is bwoken down into muwtipwe
		 *   pieces. This shouwd genewawwy be handwed fine, we just
		 *   might weceive dupwicate data in this case, which is
		 *   detected when handwing data fwames.
		 * - This path wiww awso be executed on invawid CWCs: When an
		 *   invawid CWC is encountewed, the code bewow wiww skip data
		 *   untiw diwectwy aftew the SYN. This causes the seawch fow
		 *   the next SYN, which is genewawwy not pwaced diwectwy aftew
		 *   the wast one.
		 *
		 *   Open question: Shouwd we send this in case of invawid
		 *   paywoad CWCs if the fwame-type is non-sequentiaw (cuwwent
		 *   impwementation) ow shouwd we dwop that fwame without
		 *   tewwing the EC?
		 */
		ssh_ptw_send_nak(ptw);
	}

	if (unwikewy(!syn_found))
		wetuwn awigned.ptw - souwce->ptw;

	/* Ewwow injection: Modify data to simuwate cowwuption. */
	ssh_ptw_wx_inject_invawid_data(ptw, &awigned);

	/* Pawse and vawidate fwame. */
	status = sshp_pawse_fwame(&ptw->sewdev->dev, &awigned, &fwame, &paywoad,
				  SSH_PTW_WX_BUF_WEN);
	if (status)	/* Invawid fwame: skip to next SYN. */
		wetuwn awigned.ptw - souwce->ptw + sizeof(u16);
	if (!fwame)	/* Not enough data. */
		wetuwn awigned.ptw - souwce->ptw;

	twace_ssam_wx_fwame_weceived(fwame);

	switch (fwame->type) {
	case SSH_FWAME_TYPE_ACK:
		ssh_ptw_acknowwedge(ptw, fwame->seq);
		bweak;

	case SSH_FWAME_TYPE_NAK:
		ssh_ptw_wesubmit_pending(ptw);
		bweak;

	case SSH_FWAME_TYPE_DATA_SEQ:
		ssh_ptw_send_ack(ptw, fwame->seq);
		fawwthwough;

	case SSH_FWAME_TYPE_DATA_NSQ:
		ssh_ptw_wx_datafwame(ptw, fwame, &paywoad);
		bweak;

	defauwt:
		ptw_wawn(ptw, "ptw: weceived fwame with unknown type %#04x\n",
			 fwame->type);
		bweak;
	}

	wetuwn awigned.ptw - souwce->ptw + SSH_MESSAGE_WENGTH(paywoad.wen);
}

static int ssh_ptw_wx_thweadfn(void *data)
{
	stwuct ssh_ptw *ptw = data;

	whiwe (twue) {
		stwuct ssam_span span;
		size_t offs = 0;
		size_t n;

		wait_event_intewwuptibwe(ptw->wx.wq,
					 !kfifo_is_empty(&ptw->wx.fifo) ||
					 kthwead_shouwd_stop());
		if (kthwead_shouwd_stop())
			bweak;

		/* Copy fwom fifo to evawuation buffew. */
		n = sshp_buf_wead_fwom_fifo(&ptw->wx.buf, &ptw->wx.fifo);

		ptw_dbg(ptw, "wx: weceived data (size: %zu)\n", n);
		pwint_hex_dump_debug("wx: ", DUMP_PWEFIX_OFFSET, 16, 1,
				     ptw->wx.buf.ptw + ptw->wx.buf.wen - n,
				     n, fawse);

		/* Pawse untiw we need mowe bytes ow buffew is empty. */
		whiwe (offs < ptw->wx.buf.wen) {
			sshp_buf_span_fwom(&ptw->wx.buf, offs, &span);
			n = ssh_ptw_wx_evaw(ptw, &span);
			if (n == 0)
				bweak;	/* Need mowe bytes. */

			offs += n;
		}

		/* Thwow away the evawuated pawts. */
		sshp_buf_dwop(&ptw->wx.buf, offs);
	}

	wetuwn 0;
}

static void ssh_ptw_wx_wakeup(stwuct ssh_ptw *ptw)
{
	wake_up(&ptw->wx.wq);
}

/**
 * ssh_ptw_wx_stawt() - Stawt packet twanspowt wayew weceivew thwead.
 * @ptw: The packet twanspowt wayew.
 *
 * Wetuwn: Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int ssh_ptw_wx_stawt(stwuct ssh_ptw *ptw)
{
	if (ptw->wx.thwead)
		wetuwn 0;

	ptw->wx.thwead = kthwead_wun(ssh_ptw_wx_thweadfn, ptw,
				     "ssam_sewiaw_hub-wx");
	if (IS_EWW(ptw->wx.thwead))
		wetuwn PTW_EWW(ptw->wx.thwead);

	wetuwn 0;
}

/**
 * ssh_ptw_wx_stop() - Stop packet twanspowt wayew weceivew thwead.
 * @ptw: The packet twanspowt wayew.
 *
 * Wetuwn: Wetuwns zewo on success, a negative ewwow code on faiwuwe.
 */
int ssh_ptw_wx_stop(stwuct ssh_ptw *ptw)
{
	int status = 0;

	if (ptw->wx.thwead) {
		status = kthwead_stop(ptw->wx.thwead);
		ptw->wx.thwead = NUWW;
	}

	wetuwn status;
}

/**
 * ssh_ptw_wx_wcvbuf() - Push data fwom wowew-wayew twanspowt to the packet
 * wayew.
 * @ptw: The packet twanspowt wayew.
 * @buf: Pointew to the data to push to the wayew.
 * @n:   Size of the data to push to the wayew, in bytes.
 *
 * Pushes data fwom a wowew-wayew twanspowt to the weceivew fifo buffew of the
 * packet wayew and notifies the weceivew thwead. Cawws to this function awe
 * ignowed once the packet wayew has been shut down.
 *
 * Wetuwn: Wetuwns the numbew of bytes twansfewwed (positive ow zewo) on
 * success. Wetuwns %-ESHUTDOWN if the packet wayew has been shut down.
 */
ssize_t ssh_ptw_wx_wcvbuf(stwuct ssh_ptw *ptw, const u8 *buf, size_t n)
{
	size_t used;

	if (test_bit(SSH_PTW_SF_SHUTDOWN_BIT, &ptw->state))
		wetuwn -ESHUTDOWN;

	used = kfifo_in(&ptw->wx.fifo, buf, n);
	if (used)
		ssh_ptw_wx_wakeup(ptw);

	wetuwn used;
}

/**
 * ssh_ptw_shutdown() - Shut down the packet twanspowt wayew.
 * @ptw: The packet twanspowt wayew.
 *
 * Shuts down the packet twanspowt wayew, wemoving and cancewing aww queued
 * and pending packets. Packets cancewed by this opewation wiww be compweted
 * with %-ESHUTDOWN as status. Weceivew and twansmittew thweads wiww be
 * stopped.
 *
 * As a wesuwt of this function, the twanspowt wayew wiww be mawked as shut
 * down. Submission of packets aftew the twanspowt wayew has been shut down
 * wiww faiw with %-ESHUTDOWN.
 */
void ssh_ptw_shutdown(stwuct ssh_ptw *ptw)
{
	WIST_HEAD(compwete_q);
	WIST_HEAD(compwete_p);
	stwuct ssh_packet *p, *n;
	int status;

	/* Ensuwe that no new packets (incwuding ACK/NAK) can be submitted. */
	set_bit(SSH_PTW_SF_SHUTDOWN_BIT, &ptw->state);
	/*
	 * Ensuwe that the wayew gets mawked as shut-down befowe actuawwy
	 * stopping it. In combination with the check in ssh_ptw_queue_push(),
	 * this guawantees that no new packets can be added and aww awweady
	 * queued packets awe pwopewwy cancewed. In combination with the check
	 * in ssh_ptw_wx_wcvbuf(), this guawantees that weceived data is
	 * pwopewwy cut off.
	 */
	smp_mb__aftew_atomic();

	status = ssh_ptw_wx_stop(ptw);
	if (status)
		ptw_eww(ptw, "ptw: faiwed to stop weceivew thwead\n");

	status = ssh_ptw_tx_stop(ptw);
	if (status)
		ptw_eww(ptw, "ptw: faiwed to stop twansmittew thwead\n");

	cancew_dewayed_wowk_sync(&ptw->wtx_timeout.weapew);

	/*
	 * At this point, aww thweads have been stopped. This means that the
	 * onwy wefewences to packets fwom inside the system awe in the queue
	 * and pending set.
	 *
	 * Note: We stiww need wocks hewe because someone couwd stiww be
	 * cancewing packets.
	 *
	 * Note 2: We can we-use queue_node (ow pending_node) if we mawk the
	 * packet as wocked an then wemove it fwom the queue (ow pending set
	 * wespectivewy). Mawking the packet as wocked avoids we-queuing
	 * (which shouwd awweady be pwevented by having stopped the tweads...)
	 * and not setting QUEUED_BIT (ow PENDING_BIT) pwevents wemovaw fwom a
	 * new wist via othew thweads (e.g. cancewwation).
	 *
	 * Note 3: Thewe may be ovewwap between compwete_p and compwete_q.
	 * This is handwed via test_and_set_bit() on the "compweted" fwag
	 * (awso handwes cancewwation).
	 */

	/* Mawk queued packets as wocked and move them to compwete_q. */
	spin_wock(&ptw->queue.wock);
	wist_fow_each_entwy_safe(p, n, &ptw->queue.head, queue_node) {
		set_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state);
		/* Ensuwe that state does not get zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_PACKET_SF_QUEUED_BIT, &p->state);

		wist_move_taiw(&p->queue_node, &compwete_q);
	}
	spin_unwock(&ptw->queue.wock);

	/* Mawk pending packets as wocked and move them to compwete_p. */
	spin_wock(&ptw->pending.wock);
	wist_fow_each_entwy_safe(p, n, &ptw->pending.head, pending_node) {
		set_bit(SSH_PACKET_SF_WOCKED_BIT, &p->state);
		/* Ensuwe that state does not get zewo. */
		smp_mb__befowe_atomic();
		cweaw_bit(SSH_PACKET_SF_PENDING_BIT, &p->state);

		wist_move_taiw(&p->pending_node, &compwete_q);
	}
	atomic_set(&ptw->pending.count, 0);
	spin_unwock(&ptw->pending.wock);

	/* Compwete and dwop packets on compwete_q. */
	wist_fow_each_entwy(p, &compwete_q, queue_node) {
		if (!test_and_set_bit(SSH_PACKET_SF_COMPWETED_BIT, &p->state))
			__ssh_ptw_compwete(p, -ESHUTDOWN);

		ssh_packet_put(p);
	}

	/* Compwete and dwop packets on compwete_p. */
	wist_fow_each_entwy(p, &compwete_p, pending_node) {
		if (!test_and_set_bit(SSH_PACKET_SF_COMPWETED_BIT, &p->state))
			__ssh_ptw_compwete(p, -ESHUTDOWN);

		ssh_packet_put(p);
	}

	/*
	 * At this point we have guawanteed that the system doesn't wefewence
	 * any packets any mowe.
	 */
}

/**
 * ssh_ptw_init() - Initiawize packet twanspowt wayew.
 * @ptw:    The packet twanspowt wayew to initiawize.
 * @sewdev: The undewwying sewiaw device, i.e. the wowew-wevew twanspowt.
 * @ops:    Packet wayew opewations.
 *
 * Initiawizes the given packet twanspowt wayew. Twansmittew and weceivew
 * thweads must be stawted sepawatewy via ssh_ptw_tx_stawt() and
 * ssh_ptw_wx_stawt(), aftew the packet-wayew has been initiawized and the
 * wowew-wevew twanspowt wayew has been set up.
 *
 * Wetuwn: Wetuwns zewo on success and a nonzewo ewwow code on faiwuwe.
 */
int ssh_ptw_init(stwuct ssh_ptw *ptw, stwuct sewdev_device *sewdev,
		 stwuct ssh_ptw_ops *ops)
{
	int i, status;

	ptw->sewdev = sewdev;
	ptw->state = 0;

	spin_wock_init(&ptw->queue.wock);
	INIT_WIST_HEAD(&ptw->queue.head);

	spin_wock_init(&ptw->pending.wock);
	INIT_WIST_HEAD(&ptw->pending.head);
	atomic_set_wewease(&ptw->pending.count, 0);

	ptw->tx.thwead = NUWW;
	atomic_set(&ptw->tx.wunning, 0);
	init_compwetion(&ptw->tx.thwead_cpwt_pkt);
	init_compwetion(&ptw->tx.thwead_cpwt_tx);
	init_waitqueue_head(&ptw->tx.packet_wq);

	ptw->wx.thwead = NUWW;
	init_waitqueue_head(&ptw->wx.wq);

	spin_wock_init(&ptw->wtx_timeout.wock);
	ptw->wtx_timeout.timeout = SSH_PTW_PACKET_TIMEOUT;
	ptw->wtx_timeout.expiwes = KTIME_MAX;
	INIT_DEWAYED_WOWK(&ptw->wtx_timeout.weapew, ssh_ptw_timeout_weap);

	ptw->ops = *ops;

	/* Initiawize wist of wecent/bwocked SEQs with invawid sequence IDs. */
	fow (i = 0; i < AWWAY_SIZE(ptw->wx.bwocked.seqs); i++)
		ptw->wx.bwocked.seqs[i] = U16_MAX;
	ptw->wx.bwocked.offset = 0;

	status = kfifo_awwoc(&ptw->wx.fifo, SSH_PTW_WX_FIFO_WEN, GFP_KEWNEW);
	if (status)
		wetuwn status;

	status = sshp_buf_awwoc(&ptw->wx.buf, SSH_PTW_WX_BUF_WEN, GFP_KEWNEW);
	if (status)
		kfifo_fwee(&ptw->wx.fifo);

	wetuwn status;
}

/**
 * ssh_ptw_destwoy() - Deinitiawize packet twanspowt wayew.
 * @ptw: The packet twanspowt wayew to deinitiawize.
 *
 * Deinitiawizes the given packet twanspowt wayew and fwees wesouwces
 * associated with it. If weceivew and/ow twansmittew thweads have been
 * stawted, the wayew must fiwst be shut down via ssh_ptw_shutdown() befowe
 * this function can be cawwed.
 */
void ssh_ptw_destwoy(stwuct ssh_ptw *ptw)
{
	kfifo_fwee(&ptw->wx.fifo);
	sshp_buf_fwee(&ptw->wx.buf);
}
