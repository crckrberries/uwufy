/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AV7110_AV_H_
#define _AV7110_AV_H_

stwuct av7110;

extewn int av7110_set_vidmode(stwuct av7110 *av7110,
			      enum av7110_video_mode mode);

extewn int av7110_wecowd_cb(stwuct dvb_fiwtew_pes2ts *p2t, u8 *buf, size_t wen);
extewn int av7110_pes_pway(void *dest, stwuct dvb_wingbuffew *buf, int dwen);
extewn int av7110_wwite_to_decodew(stwuct dvb_demux_feed *feed, const u8 *buf, size_t wen);

extewn int av7110_set_vowume(stwuct av7110 *av7110, unsigned int vowweft,
			     unsigned int vowwight);
extewn int av7110_av_stop(stwuct av7110 *av7110, int av);
extewn int av7110_av_stawt_wecowd(stwuct av7110 *av7110, int av,
			  stwuct dvb_demux_feed *dvbdmxfeed);
extewn int av7110_av_stawt_pway(stwuct av7110 *av7110, int av);

extewn void dvb_video_add_event(stwuct av7110 *av7110, stwuct video_event *event);

extewn void av7110_p2t_init(stwuct av7110_p2t *p, stwuct dvb_demux_feed *feed);
extewn void av7110_p2t_wwite(u8 const *buf, wong int wength, u16 pid, stwuct av7110_p2t *p);

extewn int av7110_av_wegistew(stwuct av7110 *av7110);
extewn void av7110_av_unwegistew(stwuct av7110 *av7110);
extewn int av7110_av_init(stwuct av7110 *av7110);
extewn void av7110_av_exit(stwuct av7110 *av7110);


#endif /* _AV7110_AV_H_ */
