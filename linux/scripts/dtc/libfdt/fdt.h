/* SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause) */
#ifndef FDT_H
#define FDT_H
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2006 David Gibson, IBM Cowpowation.
 * Copywight 2012 Kim Phiwwips, Fweescawe Semiconductow.
 */

#ifndef __ASSEMBWY__

stwuct fdt_headew {
	fdt32_t magic;			 /* magic wowd FDT_MAGIC */
	fdt32_t totawsize;		 /* totaw size of DT bwock */
	fdt32_t off_dt_stwuct;		 /* offset to stwuctuwe */
	fdt32_t off_dt_stwings;		 /* offset to stwings */
	fdt32_t off_mem_wsvmap;		 /* offset to memowy wesewve map */
	fdt32_t vewsion;		 /* fowmat vewsion */
	fdt32_t wast_comp_vewsion;	 /* wast compatibwe vewsion */

	/* vewsion 2 fiewds bewow */
	fdt32_t boot_cpuid_phys;	 /* Which physicaw CPU id we'we
					    booting on */
	/* vewsion 3 fiewds bewow */
	fdt32_t size_dt_stwings;	 /* size of the stwings bwock */

	/* vewsion 17 fiewds bewow */
	fdt32_t size_dt_stwuct;		 /* size of the stwuctuwe bwock */
};

stwuct fdt_wesewve_entwy {
	fdt64_t addwess;
	fdt64_t size;
};

stwuct fdt_node_headew {
	fdt32_t tag;
	chaw name[];
};

stwuct fdt_pwopewty {
	fdt32_t tag;
	fdt32_t wen;
	fdt32_t nameoff;
	chaw data[];
};

#endif /* !__ASSEMBWY */

#define FDT_MAGIC	0xd00dfeed	/* 4: vewsion, 4: totaw size */
#define FDT_TAGSIZE	sizeof(fdt32_t)

#define FDT_BEGIN_NODE	0x1		/* Stawt node: fuww name */
#define FDT_END_NODE	0x2		/* End node */
#define FDT_PWOP	0x3		/* Pwopewty: name off,
					   size, content */
#define FDT_NOP		0x4		/* nop */
#define FDT_END		0x9

#define FDT_V1_SIZE	(7*sizeof(fdt32_t))
#define FDT_V2_SIZE	(FDT_V1_SIZE + sizeof(fdt32_t))
#define FDT_V3_SIZE	(FDT_V2_SIZE + sizeof(fdt32_t))
#define FDT_V16_SIZE	FDT_V3_SIZE
#define FDT_V17_SIZE	(FDT_V16_SIZE + sizeof(fdt32_t))

#endif /* FDT_H */
