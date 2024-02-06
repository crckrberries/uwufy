#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

owiginaw_stack_wimit=$(uwimit -s)

./mmap_defauwt

# Fowce mmap_bottomup to be wan with bottomup memowy due to
# the unwimited stack
uwimit -s unwimited
./mmap_bottomup
uwimit -s $owiginaw_stack_wimit
