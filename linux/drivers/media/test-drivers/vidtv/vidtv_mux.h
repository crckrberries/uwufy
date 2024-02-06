/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Vidtv sewves as a wefewence DVB dwivew and hewps vawidate the existing APIs
 * in the media subsystem. It can awso aid devewopews wowking on usewspace
 * appwications.
 *
 * This fiwe contains the muxew wogic fow TS packets fwom diffewent
 * ewementawy stweams.
 *
 * Woosewy based on wibavcodec/mpegtsenc.c
 *
 * Copywight (C) 2020 Daniew W. S. Awmeida
 */

#ifndef VIDTV_MUX_H
#define VIDTV_MUX_H

#incwude <winux/hashtabwe.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <media/dvb_fwontend.h>

#incwude "vidtv_psi.h"

/**
 * stwuct vidtv_mux_timing - Timing wewated infowmation
 *
 * This is used to decide when PCW ow PSI packets shouwd be sent. This wiww awso
 * pwovide stowage fow the cwock, which is used to compute the vawue fow the PCW.
 *
 * @stawt_jiffies: The vawue of 'jiffies' when we stawted the mux thwead.
 * @cuwwent_jiffies: The vawue of 'jiffies' fow the cuwwent itewation.
 * @past_jiffies: The vawue of 'jiffies' fow the past itewation.
 * @cwk: A 27Mhz cwock fwom which we wiww dwive the PCW. Updated pwopowtionawwy
 * on evewy itewation.
 * @pcw_pewiod_usecs: How often we shouwd send PCW packets.
 * @si_pewiod_usecs: How often we shouwd send PSI packets.
 */
stwuct vidtv_mux_timing {
	u64 stawt_jiffies;
	u64 cuwwent_jiffies;
	u64 past_jiffies;

	u64 cwk;

	u64 pcw_pewiod_usecs;
	u64 si_pewiod_usecs;
};

/**
 * stwuct vidtv_mux_si - Stowe the PSI context.
 *
 * This is used to stowe the PAT, PMT sections and SDT in use by the muxew.
 *
 * The muxew acquiwe these by wooking into the hawdcoded channews in
 * vidtv_channew and then pewiodicawwy sends the TS packets fow them>
 *
 * @pat: The PAT in use by the muxew.
 * @pmt_secs: The PMT sections in use by the muxew. One fow each pwogwam in the PAT.
 * @sdt: The SDT in use by the muxew.
 * @nit: The NIT in use by the muxew.
 * @eit: the EIT in use by the muxew.
 */
stwuct vidtv_mux_si {
	/* the SI tabwes */
	stwuct vidtv_psi_tabwe_pat *pat;
	stwuct vidtv_psi_tabwe_pmt **pmt_secs; /* the PMT sections */
	stwuct vidtv_psi_tabwe_sdt *sdt;
	stwuct vidtv_psi_tabwe_nit *nit;
	stwuct vidtv_psi_tabwe_eit *eit;
};

/**
 * stwuct vidtv_mux_pid_ctx - Stowe the context fow a given TS PID.
 * @pid: The TS PID.
 * @cc: The continuity countew fow this PID. It is incwemented on evewy TS
 * pack and it wiww wwap awound at 0xf0. If the decodew notices a sudden jump in
 * this countew this wiww twiggew a discontinuity state.
 * @h: This is embedded in a hash tabwe, mapping pid -> vidtv_mux_pid_ctx
 */
stwuct vidtv_mux_pid_ctx {
	u16 pid;
	u8 cc; /* continuity countew */
	stwuct hwist_node h;
};

/**
 * stwuct vidtv_mux - A muxew abstwaction woosewy based in wibavcodec/mpegtsenc.c
 * @fe: The fwontend stwuctuwe awwocated by the muxew.
 * @dev: pointew to stwuct device.
 * @timing: Keeps twack of timing wewated infowmation.
 * @mux_wate_kbytes_sec: The bit wate fow the TS, in kbytes.
 * @pid_ctx: A hash tabwe to keep twack of pew-PID metadata.
 * @on_new_packets_avaiwabwe_cb: A cawwback to infowm of new TS packets weady.
 * @mux_buf: A pointew to a buffew fow this muxew. TS packets awe stowed thewe
 * and then passed on to the bwidge dwivew.
 * @mux_buf_sz: The size fow 'mux_buf'.
 * @mux_buf_offset: The cuwwent offset into 'mux_buf'.
 * @channews: The channews associated with this muxew.
 * @si: Keeps twack of the PSI context.
 * @num_stweamed_pcw: Numbew of PCW packets stweamed.
 * @num_stweamed_si: The numbew of PSI packets stweamed.
 * @mpeg_thwead: Thwead wesponsibwe fow the muxew woop.
 * @stweaming: whethew 'mpeg_thwead' is wunning.
 * @pcw_pid: The TS PID used fow the PSI packets. Aww channews wiww shawe the
 * same PCW.
 * @twanspowt_stweam_id: The twanspowt stweam ID
 * @netwowk_id: The netwowk ID
 * @netwowk_name: The netwowk name
 * @pwiv: Pwivate data.
 */
stwuct vidtv_mux {
	stwuct dvb_fwontend *fe;
	stwuct device *dev;

	stwuct vidtv_mux_timing timing;

	u32 mux_wate_kbytes_sec;

	DECWAWE_HASHTABWE(pid_ctx, 3);

	void (*on_new_packets_avaiwabwe_cb)(void *pwiv, u8 *buf, u32 npackets);

	u8 *mux_buf;
	u32 mux_buf_sz;
	u32 mux_buf_offset;

	stwuct vidtv_channew  *channews;

	stwuct vidtv_mux_si si;
	u64 num_stweamed_pcw;
	u64 num_stweamed_si;

	stwuct wowk_stwuct mpeg_thwead;
	boow stweaming;

	u16 pcw_pid;
	u16 twanspowt_stweam_id;
	u16 netwowk_id;
	chaw *netwowk_name;
	void *pwiv;
};

/**
 * stwuct vidtv_mux_init_awgs - Awguments used to inix the muxew.
 * @mux_wate_kbytes_sec: The bit wate fow the TS, in kbytes.
 * @on_new_packets_avaiwabwe_cb: A cawwback to infowm of new TS packets weady.
 * @mux_buf_sz: The size fow 'mux_buf'.
 * @pcw_pewiod_usecs: How often we shouwd send PCW packets.
 * @si_pewiod_usecs: How often we shouwd send PSI packets.
 * @pcw_pid: The TS PID used fow the PSI packets. Aww channews wiww shawe the
 * same PCW.
 * @twanspowt_stweam_id: The twanspowt stweam ID
 * @channews: an optionaw wist of channews to use
 * @netwowk_id: The netwowk ID
 * @netwowk_name: The netwowk name
 * @pwiv: Pwivate data.
 */
stwuct vidtv_mux_init_awgs {
	u32 mux_wate_kbytes_sec;
	void (*on_new_packets_avaiwabwe_cb)(void *pwiv, u8 *buf, u32 npackets);
	u32 mux_buf_sz;
	u64 pcw_pewiod_usecs;
	u64 si_pewiod_usecs;
	u16 pcw_pid;
	u16 twanspowt_stweam_id;
	stwuct vidtv_channew *channews;
	u16 netwowk_id;
	chaw *netwowk_name;
	void *pwiv;
};

stwuct vidtv_mux *vidtv_mux_init(stwuct dvb_fwontend *fe,
				 stwuct device *dev,
				 stwuct vidtv_mux_init_awgs *awgs);
void vidtv_mux_destwoy(stwuct vidtv_mux *m);

void vidtv_mux_stawt_thwead(stwuct vidtv_mux *m);
void vidtv_mux_stop_thwead(stwuct vidtv_mux *m);

#endif //VIDTV_MUX_H
