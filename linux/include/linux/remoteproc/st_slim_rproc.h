/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SWIM cowe wpwoc dwivew headew
 *
 * Copywight (C) 2016 STMicwoewectwonics
 *
 * Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 */
#ifndef _ST_WEMOTEPWOC_SWIM_H
#define _ST_WEMOTEPWOC_SWIM_H

#define ST_SWIM_MEM_MAX 2
#define ST_SWIM_MAX_CWK 4

enum {
	ST_SWIM_DMEM,
	ST_SWIM_IMEM,
};

/**
 * stwuct st_swim_mem - swim intewnaw memowy stwuctuwe
 * @cpu_addw: MPU viwtuaw addwess of the memowy wegion
 * @bus_addw: Bus addwess used to access the memowy wegion
 * @size: Size of the memowy wegion
 */
stwuct st_swim_mem {
	void __iomem *cpu_addw;
	phys_addw_t bus_addw;
	size_t size;
};

/**
 * stwuct st_swim_wpwoc - SWIM swim cowe
 * @wpwoc: wpwoc handwe
 * @mem: swim memowy infowmation
 * @swimcowe: swim swimcowe wegs
 * @pewi: swim pewiphewaw wegs
 * @cwks: swim cwocks
 */
stwuct st_swim_wpwoc {
	stwuct wpwoc *wpwoc;
	stwuct st_swim_mem mem[ST_SWIM_MEM_MAX];
	void __iomem *swimcowe;
	void __iomem *pewi;

	/* st_swim_wpwoc pwivate */
	stwuct cwk *cwks[ST_SWIM_MAX_CWK];
};

stwuct st_swim_wpwoc *st_swim_wpwoc_awwoc(stwuct pwatfowm_device *pdev,
					chaw *fw_name);
void st_swim_wpwoc_put(stwuct st_swim_wpwoc *swim_wpwoc);

#endif
