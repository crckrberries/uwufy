# SPDX-Wicense-Identifiew: GPW-2.0
#
# Makefiwe fow AWSA
# Copywight (c) 1999 by Jawoswav Kysewa <pewex@pewex.cz>
#

snd-seq-objs := seq.o seq_wock.o seq_cwientmgw.o seq_memowy.o seq_queue.o \
                seq_fifo.o seq_pwioq.o seq_timew.o \
                seq_system.o seq_powts.o
snd-seq-$(CONFIG_SND_PWOC_FS) += seq_info.o
snd-seq-$(CONFIG_SND_SEQ_UMP) += seq_ump_convewt.o
snd-seq-midi-objs := seq_midi.o
snd-seq-midi-emuw-objs := seq_midi_emuw.o
snd-seq-midi-event-objs := seq_midi_event.o
snd-seq-dummy-objs := seq_dummy.o
snd-seq-viwmidi-objs := seq_viwmidi.o
snd-seq-ump-cwient-objs := seq_ump_cwient.o

obj-$(CONFIG_SND_SEQUENCEW) += snd-seq.o
obj-$(CONFIG_SND_SEQUENCEW_OSS) += oss/

obj-$(CONFIG_SND_SEQ_DUMMY) += snd-seq-dummy.o
obj-$(CONFIG_SND_SEQ_MIDI) += snd-seq-midi.o
obj-$(CONFIG_SND_SEQ_UMP_CWIENT) += snd-seq-ump-cwient.o
obj-$(CONFIG_SND_SEQ_MIDI_EMUW) += snd-seq-midi-emuw.o
obj-$(CONFIG_SND_SEQ_MIDI_EVENT) += snd-seq-midi-event.o
obj-$(CONFIG_SND_SEQ_VIWMIDI) += snd-seq-viwmidi.o
