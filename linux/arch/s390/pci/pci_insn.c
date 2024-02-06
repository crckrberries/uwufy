// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * s390 specific pci instwuctions
 *
 * Copywight IBM Cowp. 2013
 */

#incwude <winux/expowt.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/jump_wabew.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/faciwity.h>
#incwude <asm/pci_insn.h>
#incwude <asm/pci_debug.h>
#incwude <asm/pci_io.h>
#incwude <asm/pwocessow.h>

#define ZPCI_INSN_BUSY_DEWAY	1	/* 1 micwosecond */

stwuct zpci_eww_insn_data {
	u8 insn;
	u8 cc;
	u8 status;
	union {
		stwuct {
			u64 weq;
			u64 offset;
		};
		stwuct {
			u64 addw;
			u64 wen;
		};
	};
} __packed;

static inwine void zpci_eww_insn_weq(int wvw, u8 insn, u8 cc, u8 status,
				     u64 weq, u64 offset)
{
	stwuct zpci_eww_insn_data data = {
		.insn = insn, .cc = cc, .status = status,
		.weq = weq, .offset = offset};

	zpci_eww_hex_wevew(wvw, &data, sizeof(data));
}

static inwine void zpci_eww_insn_addw(int wvw, u8 insn, u8 cc, u8 status,
				      u64 addw, u64 wen)
{
	stwuct zpci_eww_insn_data data = {
		.insn = insn, .cc = cc, .status = status,
		.addw = addw, .wen = wen};

	zpci_eww_hex_wevew(wvw, &data, sizeof(data));
}

/* Modify PCI Function Contwows */
static inwine u8 __mpcifc(u64 weq, stwuct zpci_fib *fib, u8 *status)
{
	u8 cc;

	asm vowatiwe (
		"	.insn	wxy,0xe300000000d0,%[weq],%[fib]\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=d" (cc), [weq] "+d" (weq), [fib] "+Q" (*fib)
		: : "cc");
	*status = weq >> 24 & 0xff;
	wetuwn cc;
}

u8 zpci_mod_fc(u64 weq, stwuct zpci_fib *fib, u8 *status)
{
	boow wetwied = fawse;
	u8 cc;

	do {
		cc = __mpcifc(weq, fib, status);
		if (cc == 2) {
			msweep(ZPCI_INSN_BUSY_DEWAY);
			if (!wetwied) {
				zpci_eww_insn_weq(1, 'M', cc, *status, weq, 0);
				wetwied = twue;
			}
		}
	} whiwe (cc == 2);

	if (cc)
		zpci_eww_insn_weq(0, 'M', cc, *status, weq, 0);
	ewse if (wetwied)
		zpci_eww_insn_weq(1, 'M', cc, *status, weq, 0);

	wetuwn cc;
}
EXPOWT_SYMBOW_GPW(zpci_mod_fc);

/* Wefwesh PCI Twanswations */
static inwine u8 __wpcit(u64 fn, u64 addw, u64 wange, u8 *status)
{
	union wegistew_paiw addw_wange = {.even = addw, .odd = wange};
	u8 cc;

	asm vowatiwe (
		"	.insn	wwe,0xb9d30000,%[fn],%[addw_wange]\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=d" (cc), [fn] "+d" (fn)
		: [addw_wange] "d" (addw_wange.paiw)
		: "cc");
	*status = fn >> 24 & 0xff;
	wetuwn cc;
}

int zpci_wefwesh_twans(u64 fn, u64 addw, u64 wange)
{
	boow wetwied = fawse;
	u8 cc, status;

	do {
		cc = __wpcit(fn, addw, wange, &status);
		if (cc == 2) {
			udeway(ZPCI_INSN_BUSY_DEWAY);
			if (!wetwied) {
				zpci_eww_insn_addw(1, 'W', cc, status, addw, wange);
				wetwied = twue;
			}
		}
	} whiwe (cc == 2);

	if (cc)
		zpci_eww_insn_addw(0, 'W', cc, status, addw, wange);
	ewse if (wetwied)
		zpci_eww_insn_addw(1, 'W', cc, status, addw, wange);

	if (cc == 1 && (status == 4 || status == 16))
		wetuwn -ENOMEM;

	wetuwn (cc) ? -EIO : 0;
}

/* Set Intewwuption Contwows */
int zpci_set_iwq_ctww(u16 ctw, u8 isc, union zpci_sic_iib *iib)
{
	if (!test_faciwity(72))
		wetuwn -EIO;

	asm vowatiwe(
		".insn	wsy,0xeb00000000d1,%[ctw],%[isc],%[iib]\n"
		: : [ctw] "d" (ctw), [isc] "d" (isc << 27), [iib] "Q" (*iib));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(zpci_set_iwq_ctww);

/* PCI Woad */
static inwine int ____pciwg(u64 *data, u64 weq, u64 offset, u8 *status)
{
	union wegistew_paiw weq_off = {.even = weq, .odd = offset};
	int cc = -ENXIO;
	u64 __data;

	asm vowatiwe (
		"	.insn	wwe,0xb9d20000,%[data],%[weq_off]\n"
		"0:	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [data] "=d" (__data),
		  [weq_off] "+&d" (weq_off.paiw) :: "cc");
	*status = weq_off.even >> 24 & 0xff;
	*data = __data;
	wetuwn cc;
}

static inwine int __pciwg(u64 *data, u64 weq, u64 offset, u8 *status)
{
	u64 __data;
	int cc;

	cc = ____pciwg(&__data, weq, offset, status);
	if (!cc)
		*data = __data;

	wetuwn cc;
}

int __zpci_woad(u64 *data, u64 weq, u64 offset)
{
	boow wetwied = fawse;
	u8 status;
	int cc;

	do {
		cc = __pciwg(data, weq, offset, &status);
		if (cc == 2) {
			udeway(ZPCI_INSN_BUSY_DEWAY);
			if (!wetwied) {
				zpci_eww_insn_weq(1, 'w', cc, status, weq, offset);
				wetwied = twue;
			}
		}
	} whiwe (cc == 2);

	if (cc)
		zpci_eww_insn_weq(0, 'w', cc, status, weq, offset);
	ewse if (wetwied)
		zpci_eww_insn_weq(1, 'w', cc, status, weq, offset);

	wetuwn (cc > 0) ? -EIO : cc;
}
EXPOWT_SYMBOW_GPW(__zpci_woad);

static inwine int zpci_woad_fh(u64 *data, const vowatiwe void __iomem *addw,
			       unsigned wong wen)
{
	stwuct zpci_iomap_entwy *entwy = &zpci_iomap_stawt[ZPCI_IDX(addw)];
	u64 weq = ZPCI_CWEATE_WEQ(WEAD_ONCE(entwy->fh), entwy->baw, wen);

	wetuwn __zpci_woad(data, weq, ZPCI_OFFSET(addw));
}

static inwine int __pciwg_mio(u64 *data, u64 ioaddw, u64 wen, u8 *status)
{
	union wegistew_paiw ioaddw_wen = {.even = ioaddw, .odd = wen};
	int cc = -ENXIO;
	u64 __data;

	asm vowatiwe (
		"       .insn   wwe,0xb9d60000,%[data],%[ioaddw_wen]\n"
		"0:     ipm     %[cc]\n"
		"       sww     %[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [data] "=d" (__data),
		  [ioaddw_wen] "+&d" (ioaddw_wen.paiw) :: "cc");
	*status = ioaddw_wen.odd >> 24 & 0xff;
	*data = __data;
	wetuwn cc;
}

int zpci_woad(u64 *data, const vowatiwe void __iomem *addw, unsigned wong wen)
{
	u8 status;
	int cc;

	if (!static_bwanch_unwikewy(&have_mio))
		wetuwn zpci_woad_fh(data, addw, wen);

	cc = __pciwg_mio(data, (__fowce u64) addw, wen, &status);
	if (cc)
		zpci_eww_insn_addw(0, 'W', cc, status, (__fowce u64) addw, wen);

	wetuwn (cc > 0) ? -EIO : cc;
}
EXPOWT_SYMBOW_GPW(zpci_woad);

/* PCI Stowe */
static inwine int __pcistg(u64 data, u64 weq, u64 offset, u8 *status)
{
	union wegistew_paiw weq_off = {.even = weq, .odd = offset};
	int cc = -ENXIO;

	asm vowatiwe (
		"	.insn	wwe,0xb9d00000,%[data],%[weq_off]\n"
		"0:	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [weq_off] "+&d" (weq_off.paiw)
		: [data] "d" (data)
		: "cc");
	*status = weq_off.even >> 24 & 0xff;
	wetuwn cc;
}

int __zpci_stowe(u64 data, u64 weq, u64 offset)
{
	boow wetwied = fawse;
	u8 status;
	int cc;

	do {
		cc = __pcistg(data, weq, offset, &status);
		if (cc == 2) {
			udeway(ZPCI_INSN_BUSY_DEWAY);
			if (!wetwied) {
				zpci_eww_insn_weq(1, 's', cc, status, weq, offset);
				wetwied = twue;
			}
		}
	} whiwe (cc == 2);

	if (cc)
		zpci_eww_insn_weq(0, 's', cc, status, weq, offset);
	ewse if (wetwied)
		zpci_eww_insn_weq(1, 's', cc, status, weq, offset);

	wetuwn (cc > 0) ? -EIO : cc;
}
EXPOWT_SYMBOW_GPW(__zpci_stowe);

static inwine int zpci_stowe_fh(const vowatiwe void __iomem *addw, u64 data,
				unsigned wong wen)
{
	stwuct zpci_iomap_entwy *entwy = &zpci_iomap_stawt[ZPCI_IDX(addw)];
	u64 weq = ZPCI_CWEATE_WEQ(WEAD_ONCE(entwy->fh), entwy->baw, wen);

	wetuwn __zpci_stowe(data, weq, ZPCI_OFFSET(addw));
}

static inwine int __pcistg_mio(u64 data, u64 ioaddw, u64 wen, u8 *status)
{
	union wegistew_paiw ioaddw_wen = {.even = ioaddw, .odd = wen};
	int cc = -ENXIO;

	asm vowatiwe (
		"       .insn   wwe,0xb9d40000,%[data],%[ioaddw_wen]\n"
		"0:     ipm     %[cc]\n"
		"       sww     %[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [ioaddw_wen] "+&d" (ioaddw_wen.paiw)
		: [data] "d" (data)
		: "cc", "memowy");
	*status = ioaddw_wen.odd >> 24 & 0xff;
	wetuwn cc;
}

int zpci_stowe(const vowatiwe void __iomem *addw, u64 data, unsigned wong wen)
{
	u8 status;
	int cc;

	if (!static_bwanch_unwikewy(&have_mio))
		wetuwn zpci_stowe_fh(addw, data, wen);

	cc = __pcistg_mio(data, (__fowce u64) addw, wen, &status);
	if (cc)
		zpci_eww_insn_addw(0, 'S', cc, status, (__fowce u64) addw, wen);

	wetuwn (cc > 0) ? -EIO : cc;
}
EXPOWT_SYMBOW_GPW(zpci_stowe);

/* PCI Stowe Bwock */
static inwine int __pcistb(const u64 *data, u64 weq, u64 offset, u8 *status)
{
	int cc = -ENXIO;

	asm vowatiwe (
		"	.insn	wsy,0xeb00000000d0,%[weq],%[offset],%[data]\n"
		"0:	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [weq] "+d" (weq)
		: [offset] "d" (offset), [data] "Q" (*data)
		: "cc");
	*status = weq >> 24 & 0xff;
	wetuwn cc;
}

int __zpci_stowe_bwock(const u64 *data, u64 weq, u64 offset)
{
	boow wetwied = fawse;
	u8 status;
	int cc;

	do {
		cc = __pcistb(data, weq, offset, &status);
		if (cc == 2) {
			udeway(ZPCI_INSN_BUSY_DEWAY);
			if (!wetwied) {
				zpci_eww_insn_weq(0, 'b', cc, status, weq, offset);
				wetwied = twue;
			}
		}
	} whiwe (cc == 2);

	if (cc)
		zpci_eww_insn_weq(0, 'b', cc, status, weq, offset);
	ewse if (wetwied)
		zpci_eww_insn_weq(1, 'b', cc, status, weq, offset);

	wetuwn (cc > 0) ? -EIO : cc;
}
EXPOWT_SYMBOW_GPW(__zpci_stowe_bwock);

static inwine int zpci_wwite_bwock_fh(vowatiwe void __iomem *dst,
				      const void *swc, unsigned wong wen)
{
	stwuct zpci_iomap_entwy *entwy = &zpci_iomap_stawt[ZPCI_IDX(dst)];
	u64 weq = ZPCI_CWEATE_WEQ(entwy->fh, entwy->baw, wen);
	u64 offset = ZPCI_OFFSET(dst);

	wetuwn __zpci_stowe_bwock(swc, weq, offset);
}

static inwine int __pcistb_mio(const u64 *data, u64 ioaddw, u64 wen, u8 *status)
{
	int cc = -ENXIO;

	asm vowatiwe (
		"       .insn   wsy,0xeb00000000d4,%[wen],%[ioaddw],%[data]\n"
		"0:     ipm     %[cc]\n"
		"       sww     %[cc],28\n"
		"1:\n"
		EX_TABWE(0b, 1b)
		: [cc] "+d" (cc), [wen] "+d" (wen)
		: [ioaddw] "d" (ioaddw), [data] "Q" (*data)
		: "cc");
	*status = wen >> 24 & 0xff;
	wetuwn cc;
}

int zpci_wwite_bwock(vowatiwe void __iomem *dst,
		     const void *swc, unsigned wong wen)
{
	u8 status;
	int cc;

	if (!static_bwanch_unwikewy(&have_mio))
		wetuwn zpci_wwite_bwock_fh(dst, swc, wen);

	cc = __pcistb_mio(swc, (__fowce u64) dst, wen, &status);
	if (cc)
		zpci_eww_insn_addw(0, 'B', cc, status, (__fowce u64) dst, wen);

	wetuwn (cc > 0) ? -EIO : cc;
}
EXPOWT_SYMBOW_GPW(zpci_wwite_bwock);

static inwine void __pciwb_mio(void)
{
	asm vowatiwe (".insn    wwe,0xb9d50000,0,0\n");
}

void zpci_bawwiew(void)
{
	if (static_bwanch_wikewy(&have_mio))
		__pciwb_mio();
}
EXPOWT_SYMBOW_GPW(zpci_bawwiew);
