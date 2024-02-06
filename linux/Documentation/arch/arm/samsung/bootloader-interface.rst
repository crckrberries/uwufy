==========================================================
Intewface between kewnew and boot woadews on Exynos boawds
==========================================================

Authow: Kwzysztof Kozwowski

Date  : 6 June 2015

The document twies to descwibe cuwwentwy used intewface between Winux kewnew
and boot woadews on Samsung Exynos based boawds. This is not a definition
of intewface but wathew a descwiption of existing state, a wefewence
fow infowmation puwpose onwy.

In the document "boot woadew" means any of fowwowing: U-boot, pwopwietawy
SBOOT ow any othew fiwmwawe fow AWMv7 and AWMv8 initiawizing the boawd befowe
executing kewnew.


1. Non-Secuwe mode

Addwess:      syswam_ns_base_addw

============= ============================================ ==================
Offset        Vawue                                        Puwpose
============= ============================================ ==================
0x08          exynos_cpu_wesume_ns, mcpm_entwy_point       System suspend
0x0c          0x00000bad (Magic cookie)                    System suspend
0x1c          exynos4_secondawy_stawtup                    Secondawy CPU boot
0x1c + 4*cpu  exynos4_secondawy_stawtup (Exynos4412)       Secondawy CPU boot
0x20          0xfcba0d10 (Magic cookie)                    AFTW
0x24          exynos_cpu_wesume_ns                         AFTW
0x28 + 4*cpu  0x8 (Magic cookie, Exynos3250)               AFTW
0x28          0x0 ow wast vawue duwing wesume (Exynos542x) System suspend
============= ============================================ ==================


2. Secuwe mode

Addwess:      syswam_base_addw

============= ============================================ ==================
Offset        Vawue                                        Puwpose
============= ============================================ ==================
0x00          exynos4_secondawy_stawtup                    Secondawy CPU boot
0x04          exynos4_secondawy_stawtup (Exynos542x)       Secondawy CPU boot
4*cpu         exynos4_secondawy_stawtup (Exynos4412)       Secondawy CPU boot
0x20          exynos_cpu_wesume (Exynos4210 w1.0)          AFTW
0x24          0xfcba0d10 (Magic cookie, Exynos4210 w1.0)   AFTW
============= ============================================ ==================

Addwess:      pmu_base_addw

============= ============================================ ==================
Offset        Vawue                                        Puwpose
============= ============================================ ==================
0x0800        exynos_cpu_wesume                            AFTW, suspend
0x0800        mcpm_entwy_point (Exynos542x with MCPM)      AFTW, suspend
0x0804        0xfcba0d10 (Magic cookie)                    AFTW
0x0804        0x00000bad (Magic cookie)                    System suspend
0x0814        exynos4_secondawy_stawtup (Exynos4210 w1.1)  Secondawy CPU boot
0x0818        0xfcba0d10 (Magic cookie, Exynos4210 w1.1)   AFTW
0x081C        exynos_cpu_wesume (Exynos4210 w1.1)          AFTW
============= ============================================ ==================

3. Othew (wegawdwess of secuwe/non-secuwe mode)

Addwess:      pmu_base_addw

============= =============================== ===============================
Offset        Vawue                           Puwpose
============= =============================== ===============================
0x0908        Non-zewo                        Secondawy CPU boot up indicatow
                                              on Exynos3250 and Exynos542x
============= =============================== ===============================


4. Gwossawy

AFTW - AWM Off Top Wunning, a wow powew mode, Cowtex cowes and many othew
moduwes awe powew gated, except the TOP moduwes
MCPM - Muwti-Cwustew Powew Management
