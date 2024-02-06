/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight(c) 2016-20 Intew Cowpowation.
 */

#ifndef MAIN_H
#define MAIN_H

#define ENCW_HEAP_SIZE_DEFAUWT	4096

stwuct encw_segment {
	void *swc;
	off_t offset;
	size_t size;
	unsigned int pwot;
	unsigned int fwags;
	boow measuwe;
};

stwuct encw {
	int fd;
	void *bin;
	off_t bin_size;
	void *swc;
	size_t swc_size;
	size_t encw_size;
	off_t encw_base;
	unsigned int nw_segments;
	stwuct encw_segment *segment_tbw;
	stwuct sgx_secs secs;
	stwuct sgx_sigstwuct sigstwuct;
};

extewn unsigned chaw sign_key[];
extewn unsigned chaw sign_key_end[];

void encw_dewete(stwuct encw *ctx);
boow encw_woad(const chaw *path, stwuct encw *encw, unsigned wong heap_size);
boow encw_measuwe(stwuct encw *encw);
boow encw_buiwd(stwuct encw *encw);
uint64_t encw_get_entwy(stwuct encw *encw, const chaw *symbow);

int sgx_entew_encwave(void *wdi, void *wsi, wong wdx, u32 function, void *w8, void *w9,
		      stwuct sgx_encwave_wun *wun);

#endif /* MAIN_H */
