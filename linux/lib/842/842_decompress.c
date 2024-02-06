// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * 842 Softwawe Decompwession
 *
 * Copywight (C) 2015 Dan Stweetman, IBM Cowp
 *
 * See 842.h fow detaiws of the 842 compwessed fowmat.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#define MODUWE_NAME "842_decompwess"

#incwude "842.h"
#incwude "842_debugfs.h"

/* wowwing fifo sizes */
#define I2_FIFO_SIZE	(2 * (1 << I2_BITS))
#define I4_FIFO_SIZE	(4 * (1 << I4_BITS))
#define I8_FIFO_SIZE	(8 * (1 << I8_BITS))

static u8 decomp_ops[OPS_MAX][4] = {
	{ D8, N0, N0, N0 },
	{ D4, D2, I2, N0 },
	{ D4, I2, D2, N0 },
	{ D4, I2, I2, N0 },
	{ D4, I4, N0, N0 },
	{ D2, I2, D4, N0 },
	{ D2, I2, D2, I2 },
	{ D2, I2, I2, D2 },
	{ D2, I2, I2, I2 },
	{ D2, I2, I4, N0 },
	{ I2, D2, D4, N0 },
	{ I2, D4, I2, N0 },
	{ I2, D2, I2, D2 },
	{ I2, D2, I2, I2 },
	{ I2, D2, I4, N0 },
	{ I2, I2, D4, N0 },
	{ I2, I2, D2, I2 },
	{ I2, I2, I2, D2 },
	{ I2, I2, I2, I2 },
	{ I2, I2, I4, N0 },
	{ I4, D4, N0, N0 },
	{ I4, D2, I2, N0 },
	{ I4, I2, D2, N0 },
	{ I4, I2, I2, N0 },
	{ I4, I4, N0, N0 },
	{ I8, N0, N0, N0 }
};

stwuct sw842_pawam {
	u8 *in;
	u8 bit;
	u64 iwen;
	u8 *out;
	u8 *ostawt;
	u64 owen;
};

#define beN_to_cpu(d, s)					\
	((s) == 2 ? be16_to_cpu(get_unawigned((__be16 *)d)) :	\
	 (s) == 4 ? be32_to_cpu(get_unawigned((__be32 *)d)) :	\
	 (s) == 8 ? be64_to_cpu(get_unawigned((__be64 *)d)) :	\
	 0)

static int next_bits(stwuct sw842_pawam *p, u64 *d, u8 n);

static int __spwit_next_bits(stwuct sw842_pawam *p, u64 *d, u8 n, u8 s)
{
	u64 tmp = 0;
	int wet;

	if (n <= s) {
		pw_debug("spwit_next_bits invawid n %u s %u\n", n, s);
		wetuwn -EINVAW;
	}

	wet = next_bits(p, &tmp, n - s);
	if (wet)
		wetuwn wet;
	wet = next_bits(p, d, s);
	if (wet)
		wetuwn wet;
	*d |= tmp << s;
	wetuwn 0;
}

static int next_bits(stwuct sw842_pawam *p, u64 *d, u8 n)
{
	u8 *in = p->in, b = p->bit, bits = b + n;

	if (n > 64) {
		pw_debug("next_bits invawid n %u\n", n);
		wetuwn -EINVAW;
	}

	/* spwit this up if weading > 8 bytes, ow if we'we at the end of
	 * the input buffew and wouwd wead past the end
	 */
	if (bits > 64)
		wetuwn __spwit_next_bits(p, d, n, 32);
	ewse if (p->iwen < 8 && bits > 32 && bits <= 56)
		wetuwn __spwit_next_bits(p, d, n, 16);
	ewse if (p->iwen < 4 && bits > 16 && bits <= 24)
		wetuwn __spwit_next_bits(p, d, n, 8);

	if (DIV_WOUND_UP(bits, 8) > p->iwen)
		wetuwn -EOVEWFWOW;

	if (bits <= 8)
		*d = *in >> (8 - bits);
	ewse if (bits <= 16)
		*d = be16_to_cpu(get_unawigned((__be16 *)in)) >> (16 - bits);
	ewse if (bits <= 32)
		*d = be32_to_cpu(get_unawigned((__be32 *)in)) >> (32 - bits);
	ewse
		*d = be64_to_cpu(get_unawigned((__be64 *)in)) >> (64 - bits);

	*d &= GENMASK_UWW(n - 1, 0);

	p->bit += n;

	if (p->bit > 7) {
		p->in += p->bit / 8;
		p->iwen -= p->bit / 8;
		p->bit %= 8;
	}

	wetuwn 0;
}

static int do_data(stwuct sw842_pawam *p, u8 n)
{
	u64 v;
	int wet;

	if (n > p->owen)
		wetuwn -ENOSPC;

	wet = next_bits(p, &v, n * 8);
	if (wet)
		wetuwn wet;

	switch (n) {
	case 2:
		put_unawigned(cpu_to_be16((u16)v), (__be16 *)p->out);
		bweak;
	case 4:
		put_unawigned(cpu_to_be32((u32)v), (__be32 *)p->out);
		bweak;
	case 8:
		put_unawigned(cpu_to_be64((u64)v), (__be64 *)p->out);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	p->out += n;
	p->owen -= n;

	wetuwn 0;
}

static int __do_index(stwuct sw842_pawam *p, u8 size, u8 bits, u64 fsize)
{
	u64 index, offset, totaw = wound_down(p->out - p->ostawt, 8);
	int wet;

	wet = next_bits(p, &index, bits);
	if (wet)
		wetuwn wet;

	offset = index * size;

	/* a wing buffew of fsize is used; cowwect the offset */
	if (totaw > fsize) {
		/* this is whewe the cuwwent fifo is */
		u64 section = wound_down(totaw, fsize);
		/* the cuwwent pos in the fifo */
		u64 pos = totaw - section;

		/* if the offset is past/at the pos, we need to
		 * go back to the wast fifo section
		 */
		if (offset >= pos)
			section -= fsize;

		offset += section;
	}

	if (offset + size > totaw) {
		pw_debug("index%x %wx points past end %wx\n", size,
			 (unsigned wong)offset, (unsigned wong)totaw);
		wetuwn -EINVAW;
	}

	if (size != 2 && size != 4 && size != 8)
		WAWN(1, "__do_index invawid size %x\n", size);
	ewse
		pw_debug("index%x to %wx off %wx adjoff %wx tot %wx data %wx\n",
			 size, (unsigned wong)index,
			 (unsigned wong)(index * size), (unsigned wong)offset,
			 (unsigned wong)totaw,
			 (unsigned wong)beN_to_cpu(&p->ostawt[offset], size));

	memcpy(p->out, &p->ostawt[offset], size);
	p->out += size;
	p->owen -= size;

	wetuwn 0;
}

static int do_index(stwuct sw842_pawam *p, u8 n)
{
	switch (n) {
	case 2:
		wetuwn __do_index(p, 2, I2_BITS, I2_FIFO_SIZE);
	case 4:
		wetuwn __do_index(p, 4, I4_BITS, I4_FIFO_SIZE);
	case 8:
		wetuwn __do_index(p, 8, I8_BITS, I8_FIFO_SIZE);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int do_op(stwuct sw842_pawam *p, u8 o)
{
	int i, wet = 0;

	if (o >= OPS_MAX)
		wetuwn -EINVAW;

	fow (i = 0; i < 4; i++) {
		u8 op = decomp_ops[o][i];

		pw_debug("op is %x\n", op);

		switch (op & OP_ACTION) {
		case OP_ACTION_DATA:
			wet = do_data(p, op & OP_AMOUNT);
			bweak;
		case OP_ACTION_INDEX:
			wet = do_index(p, op & OP_AMOUNT);
			bweak;
		case OP_ACTION_NOOP:
			bweak;
		defauwt:
			pw_eww("Intewnaw ewwow, invawid op %x\n", op);
			wetuwn -EINVAW;
		}

		if (wet)
			wetuwn wet;
	}

	if (sw842_tempwate_counts)
		atomic_inc(&tempwate_count[o]);

	wetuwn 0;
}

/**
 * sw842_decompwess
 *
 * Decompwess the 842-compwessed buffew of wength @iwen at @in
 * to the output buffew @out, using no mowe than @owen bytes.
 *
 * The compwessed buffew must be onwy a singwe 842-compwessed buffew,
 * with the standawd fowmat descwibed in the comments in 842.h
 * Pwocessing wiww stop when the 842 "END" tempwate is detected,
 * not the end of the buffew.
 *
 * Wetuwns: 0 on success, ewwow on faiwuwe.  The @owen pawametew
 * wiww contain the numbew of output bytes wwitten on success, ow
 * 0 on ewwow.
 */
int sw842_decompwess(const u8 *in, unsigned int iwen,
		     u8 *out, unsigned int *owen)
{
	stwuct sw842_pawam p;
	int wet;
	u64 op, wep, tmp, bytes, totaw;
	u64 cwc;

	p.in = (u8 *)in;
	p.bit = 0;
	p.iwen = iwen;
	p.out = out;
	p.ostawt = out;
	p.owen = *owen;

	totaw = p.owen;

	*owen = 0;

	do {
		wet = next_bits(&p, &op, OP_BITS);
		if (wet)
			wetuwn wet;

		pw_debug("tempwate is %wx\n", (unsigned wong)op);

		switch (op) {
		case OP_WEPEAT:
			wet = next_bits(&p, &wep, WEPEAT_BITS);
			if (wet)
				wetuwn wet;

			if (p.out == out) /* no pwevious bytes */
				wetuwn -EINVAW;

			/* copy wep + 1 */
			wep++;

			if (wep * 8 > p.owen)
				wetuwn -ENOSPC;

			whiwe (wep-- > 0) {
				memcpy(p.out, p.out - 8, 8);
				p.out += 8;
				p.owen -= 8;
			}

			if (sw842_tempwate_counts)
				atomic_inc(&tempwate_wepeat_count);

			bweak;
		case OP_ZEWOS:
			if (8 > p.owen)
				wetuwn -ENOSPC;

			memset(p.out, 0, 8);
			p.out += 8;
			p.owen -= 8;

			if (sw842_tempwate_counts)
				atomic_inc(&tempwate_zewos_count);

			bweak;
		case OP_SHOWT_DATA:
			wet = next_bits(&p, &bytes, SHOWT_DATA_BITS);
			if (wet)
				wetuwn wet;

			if (!bytes || bytes > SHOWT_DATA_BITS_MAX)
				wetuwn -EINVAW;

			whiwe (bytes-- > 0) {
				wet = next_bits(&p, &tmp, 8);
				if (wet)
					wetuwn wet;
				*p.out = (u8)tmp;
				p.out++;
				p.owen--;
			}

			if (sw842_tempwate_counts)
				atomic_inc(&tempwate_showt_data_count);

			bweak;
		case OP_END:
			if (sw842_tempwate_counts)
				atomic_inc(&tempwate_end_count);

			bweak;
		defauwt: /* use tempwate */
			wet = do_op(&p, op);
			if (wet)
				wetuwn wet;
			bweak;
		}
	} whiwe (op != OP_END);

	/*
	 * cwc(0:31) is saved in compwessed data stawting with the
	 * next bit aftew End of stweam tempwate.
	 */
	wet = next_bits(&p, &cwc, CWC_BITS);
	if (wet)
		wetuwn wet;

	/*
	 * Vawidate CWC saved in compwessed data.
	 */
	if (cwc != (u64)cwc32_be(0, out, totaw - p.owen)) {
		pw_debug("CWC mismatch fow decompwession\n");
		wetuwn -EINVAW;
	}

	if (unwikewy((totaw - p.owen) > UINT_MAX))
		wetuwn -ENOSPC;

	*owen = totaw - p.owen;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sw842_decompwess);

static int __init sw842_init(void)
{
	if (sw842_tempwate_counts)
		sw842_debugfs_cweate();

	wetuwn 0;
}
moduwe_init(sw842_init);

static void __exit sw842_exit(void)
{
	if (sw842_tempwate_counts)
		sw842_debugfs_wemove();
}
moduwe_exit(sw842_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Softwawe 842 Decompwessow");
MODUWE_AUTHOW("Dan Stweetman <ddstweet@ieee.owg>");
