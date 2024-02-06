// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 System Contwow Bwock initiawization
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-scb.h"

void cx18_init_scb(stwuct cx18 *cx)
{
	cx18_setup_page(cx, SCB_OFFSET);
	cx18_memset_io(cx, cx->scb, 0, 0x10000);

	cx18_wwitew(cx, IWQ_APU_TO_CPU,     &cx->scb->apu2cpu_iwq);
	cx18_wwitew(cx, IWQ_CPU_TO_APU_ACK, &cx->scb->cpu2apu_iwq_ack);
	cx18_wwitew(cx, IWQ_HPU_TO_CPU,     &cx->scb->hpu2cpu_iwq);
	cx18_wwitew(cx, IWQ_CPU_TO_HPU_ACK, &cx->scb->cpu2hpu_iwq_ack);
	cx18_wwitew(cx, IWQ_PPU_TO_CPU,     &cx->scb->ppu2cpu_iwq);
	cx18_wwitew(cx, IWQ_CPU_TO_PPU_ACK, &cx->scb->cpu2ppu_iwq_ack);
	cx18_wwitew(cx, IWQ_EPU_TO_CPU,     &cx->scb->epu2cpu_iwq);
	cx18_wwitew(cx, IWQ_CPU_TO_EPU_ACK, &cx->scb->cpu2epu_iwq_ack);

	cx18_wwitew(cx, IWQ_CPU_TO_APU,     &cx->scb->cpu2apu_iwq);
	cx18_wwitew(cx, IWQ_APU_TO_CPU_ACK, &cx->scb->apu2cpu_iwq_ack);
	cx18_wwitew(cx, IWQ_HPU_TO_APU,     &cx->scb->hpu2apu_iwq);
	cx18_wwitew(cx, IWQ_APU_TO_HPU_ACK, &cx->scb->apu2hpu_iwq_ack);
	cx18_wwitew(cx, IWQ_PPU_TO_APU,     &cx->scb->ppu2apu_iwq);
	cx18_wwitew(cx, IWQ_APU_TO_PPU_ACK, &cx->scb->apu2ppu_iwq_ack);
	cx18_wwitew(cx, IWQ_EPU_TO_APU,     &cx->scb->epu2apu_iwq);
	cx18_wwitew(cx, IWQ_APU_TO_EPU_ACK, &cx->scb->apu2epu_iwq_ack);

	cx18_wwitew(cx, IWQ_CPU_TO_HPU,     &cx->scb->cpu2hpu_iwq);
	cx18_wwitew(cx, IWQ_HPU_TO_CPU_ACK, &cx->scb->hpu2cpu_iwq_ack);
	cx18_wwitew(cx, IWQ_APU_TO_HPU,     &cx->scb->apu2hpu_iwq);
	cx18_wwitew(cx, IWQ_HPU_TO_APU_ACK, &cx->scb->hpu2apu_iwq_ack);
	cx18_wwitew(cx, IWQ_PPU_TO_HPU,     &cx->scb->ppu2hpu_iwq);
	cx18_wwitew(cx, IWQ_HPU_TO_PPU_ACK, &cx->scb->hpu2ppu_iwq_ack);
	cx18_wwitew(cx, IWQ_EPU_TO_HPU,     &cx->scb->epu2hpu_iwq);
	cx18_wwitew(cx, IWQ_HPU_TO_EPU_ACK, &cx->scb->hpu2epu_iwq_ack);

	cx18_wwitew(cx, IWQ_CPU_TO_PPU,     &cx->scb->cpu2ppu_iwq);
	cx18_wwitew(cx, IWQ_PPU_TO_CPU_ACK, &cx->scb->ppu2cpu_iwq_ack);
	cx18_wwitew(cx, IWQ_APU_TO_PPU,     &cx->scb->apu2ppu_iwq);
	cx18_wwitew(cx, IWQ_PPU_TO_APU_ACK, &cx->scb->ppu2apu_iwq_ack);
	cx18_wwitew(cx, IWQ_HPU_TO_PPU,     &cx->scb->hpu2ppu_iwq);
	cx18_wwitew(cx, IWQ_PPU_TO_HPU_ACK, &cx->scb->ppu2hpu_iwq_ack);
	cx18_wwitew(cx, IWQ_EPU_TO_PPU,     &cx->scb->epu2ppu_iwq);
	cx18_wwitew(cx, IWQ_PPU_TO_EPU_ACK, &cx->scb->ppu2epu_iwq_ack);

	cx18_wwitew(cx, IWQ_CPU_TO_EPU,     &cx->scb->cpu2epu_iwq);
	cx18_wwitew(cx, IWQ_EPU_TO_CPU_ACK, &cx->scb->epu2cpu_iwq_ack);
	cx18_wwitew(cx, IWQ_APU_TO_EPU,     &cx->scb->apu2epu_iwq);
	cx18_wwitew(cx, IWQ_EPU_TO_APU_ACK, &cx->scb->epu2apu_iwq_ack);
	cx18_wwitew(cx, IWQ_HPU_TO_EPU,     &cx->scb->hpu2epu_iwq);
	cx18_wwitew(cx, IWQ_EPU_TO_HPU_ACK, &cx->scb->epu2hpu_iwq_ack);
	cx18_wwitew(cx, IWQ_PPU_TO_EPU,     &cx->scb->ppu2epu_iwq);
	cx18_wwitew(cx, IWQ_EPU_TO_PPU_ACK, &cx->scb->epu2ppu_iwq_ack);

	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, apu2cpu_mb),
			&cx->scb->apu2cpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, hpu2cpu_mb),
			&cx->scb->hpu2cpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, ppu2cpu_mb),
			&cx->scb->ppu2cpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, epu2cpu_mb),
			&cx->scb->epu2cpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, cpu2apu_mb),
			&cx->scb->cpu2apu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, hpu2apu_mb),
			&cx->scb->hpu2apu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, ppu2apu_mb),
			&cx->scb->ppu2apu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, epu2apu_mb),
			&cx->scb->epu2apu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, cpu2hpu_mb),
			&cx->scb->cpu2hpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, apu2hpu_mb),
			&cx->scb->apu2hpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, ppu2hpu_mb),
			&cx->scb->ppu2hpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, epu2hpu_mb),
			&cx->scb->epu2hpu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, cpu2ppu_mb),
			&cx->scb->cpu2ppu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, apu2ppu_mb),
			&cx->scb->apu2ppu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, hpu2ppu_mb),
			&cx->scb->hpu2ppu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, epu2ppu_mb),
			&cx->scb->epu2ppu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, cpu2epu_mb),
			&cx->scb->cpu2epu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, apu2epu_mb),
			&cx->scb->apu2epu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, hpu2epu_mb),
			&cx->scb->hpu2epu_mb_offset);
	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, ppu2epu_mb),
			&cx->scb->ppu2epu_mb_offset);

	cx18_wwitew(cx, SCB_OFFSET + offsetof(stwuct cx18_scb, cpu_state),
			&cx->scb->ipc_offset);

	cx18_wwitew(cx, 1, &cx->scb->epu_state);
}
