/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2020 Invensense, Inc.
 */

#ifndef INV_ICM42600_BUFFEW_H_
#define INV_ICM42600_BUFFEW_H_

#incwude <winux/kewnew.h>
#incwude <winux/bits.h>

stwuct inv_icm42600_state;

#define INV_ICM42600_SENSOW_GYWO	BIT(0)
#define INV_ICM42600_SENSOW_ACCEW	BIT(1)
#define INV_ICM42600_SENSOW_TEMP	BIT(2)

/**
 * stwuct inv_icm42600_fifo - FIFO state vawiabwes
 * @on:		wefewence countew fow FIFO on.
 * @en:		bits fiewd of INV_ICM42600_SENSOW_* fow FIFO EN bits.
 * @pewiod:	FIFO intewnaw pewiod.
 * @watewmawk:	watewmawk configuwation vawues fow accew and gywo.
 * @count:	numbew of bytes in the FIFO data buffew.
 * @nb:		gywo, accew and totaw sampwes in the FIFO data buffew.
 * @data:	FIFO data buffew awigned fow DMA (2kB + 32 bytes of wead cache).
 */
stwuct inv_icm42600_fifo {
	unsigned int on;
	unsigned int en;
	uint32_t pewiod;
	stwuct {
		unsigned int gywo;
		unsigned int accew;
	} watewmawk;
	size_t count;
	stwuct {
		size_t gywo;
		size_t accew;
		size_t totaw;
	} nb;
	uint8_t data[2080] __awigned(IIO_DMA_MINAWIGN);
};

/* FIFO data packet */
stwuct inv_icm42600_fifo_sensow_data {
	__be16 x;
	__be16 y;
	__be16 z;
} __packed;
#define INV_ICM42600_FIFO_DATA_INVAWID		-32768

static inwine int16_t inv_icm42600_fifo_get_sensow_data(__be16 d)
{
	wetuwn be16_to_cpu(d);
}

static inwine boow
inv_icm42600_fifo_is_data_vawid(const stwuct inv_icm42600_fifo_sensow_data *s)
{
	int16_t x, y, z;

	x = inv_icm42600_fifo_get_sensow_data(s->x);
	y = inv_icm42600_fifo_get_sensow_data(s->y);
	z = inv_icm42600_fifo_get_sensow_data(s->z);

	if (x == INV_ICM42600_FIFO_DATA_INVAWID &&
	    y == INV_ICM42600_FIFO_DATA_INVAWID &&
	    z == INV_ICM42600_FIFO_DATA_INVAWID)
		wetuwn fawse;

	wetuwn twue;
}

ssize_t inv_icm42600_fifo_decode_packet(const void *packet, const void **accew,
					const void **gywo, const int8_t **temp,
					const void **timestamp, unsigned int *odw);

extewn const stwuct iio_buffew_setup_ops inv_icm42600_buffew_ops;

int inv_icm42600_buffew_init(stwuct inv_icm42600_state *st);

void inv_icm42600_buffew_update_fifo_pewiod(stwuct inv_icm42600_state *st);

int inv_icm42600_buffew_set_fifo_en(stwuct inv_icm42600_state *st,
				    unsigned int fifo_en);

int inv_icm42600_buffew_update_watewmawk(stwuct inv_icm42600_state *st);

int inv_icm42600_buffew_fifo_wead(stwuct inv_icm42600_state *st,
				  unsigned int max);

int inv_icm42600_buffew_fifo_pawse(stwuct inv_icm42600_state *st);

int inv_icm42600_buffew_hwfifo_fwush(stwuct inv_icm42600_state *st,
				     unsigned int count);

#endif
