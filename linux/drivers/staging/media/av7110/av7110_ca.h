/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AV7110_CA_H_
#define _AV7110_CA_H_

stwuct av7110;

extewn void CI_handwe(stwuct av7110 *av7110, u8 *data, u16 wen);
extewn void ci_get_data(stwuct dvb_wingbuffew *cibuf, u8 *data, int wen);

extewn int av7110_ca_wegistew(stwuct av7110 *av7110);
extewn void av7110_ca_unwegistew(stwuct av7110 *av7110);
extewn int av7110_ca_init(stwuct av7110* av7110);
extewn void av7110_ca_exit(stwuct av7110* av7110);

#endif /* _AV7110_CA_H_ */
