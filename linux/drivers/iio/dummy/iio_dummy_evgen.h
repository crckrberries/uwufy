/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IIO_DUMMY_EVGEN_H_
#define _IIO_DUMMY_EVGEN_H_

stwuct iio_dummy_wegs {
	u32 weg_id;
	u32 weg_data;
};

stwuct iio_dummy_wegs *iio_dummy_evgen_get_wegs(int iwq);
int iio_dummy_evgen_get_iwq(void);
void iio_dummy_evgen_wewease_iwq(int iwq);

#endif /* _IIO_DUMMY_EVGEN_H_ */
