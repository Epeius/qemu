/*
 * FuzzyState.c
 *
 *  Created on: 2016年4月19日
 *      Author: epeius
 */
#include "FuzzyState.h"
#include <assert.h>

#include "qemu/osdep.h"
#include "cpu.h"
#include "trace.h"
#include "disas/disas.h"
#include "tcg.h"
#include "qemu/atomic.h"
#include "sysemu/qtest.h"
#include "qemu/timer.h"
#include "exec/address-spaces.h"
#include "qemu/rcu.h"
#include "exec/tb-hash.h"
#include "exec/log.h"
#if defined(TARGET_I386) && !defined(CONFIG_USER_ONLY)
#include "hw/i386/apic.h"
#endif
#include "sysemu/replay.h"


void register_rw(int reg_id, void *buf, int is_write)
{
    assert(current_cpu != NULL);
    CPUArchState *env = current_cpu->env_ptr;
    uint32_t offset, size;

    switch (reg_id) {
        case eax_reg:
            offset = R_EAX * 4, size = 4;
            break;
        case ecx_reg:
            offset = R_ECX * 4, size = 4;
            break;
        case edx_reg:
            offset = R_EDX * 4, size = 4;
            break;
        case ebx_reg:
            offset = R_EBX * 4, size = 4;
            break;
        case esp_reg:
            offset = R_ESP * 4, size = 4;
            break;
        case ebp_reg:
            offset = R_EBP * 4, size = 4;
            break;
        case esi_reg:
            offset = R_ESI * 4, size = 4;
            break;
        case edi_reg:
            offset = R_EDI * 4, size = 4;
            break;

        case al_reg:
            offset = R_EAX * 4, size = 1;
            break;
        case cl_reg:
            offset = R_ECX * 4, size = 1;
            break;
        case dl_reg:
            offset = R_EDX * 4, size = 1;
            break;
        case bl_reg:
            offset = R_EBX * 4, size = 1;
            break;
        case ah_reg:
            offset = R_EAX * 4 + 1, size = 1;
            break;
        case ch_reg:
            offset = R_ECX * 4 + 1, size = 1;
            break;
        case dh_reg:
            offset = R_EDX * 4 + 1, size = 1;
            break;
        case bh_reg:
            offset = R_EBX * 4 + 1, size = 1;
            break;

        case ax_reg:
            offset = R_EAX * 4, size = 2;
            break;
        case cx_reg:
            offset = R_ECX * 4, size = 2;
            break;
        case dx_reg:
            offset = R_EDX * 4, size = 2;
            break;
        case bx_reg:
            offset = R_EBX * 4, size = 2;
            break;
        case sp_reg:
            offset = R_ESP * 4, size = 2;
            break;
        case bp_reg:
            offset = R_EBP * 4, size = 2;
            break;
        case si_reg:
            offset = R_ESI * 4, size = 2;
            break;
        case di_reg:
            offset = R_EDI * 4, size = 2;
            break;

        case eip_reg:
            assert(!is_write && "Currently we do not support write to the program pointer!");
            *(uint32_t *) buf = env->eip;
            return;
        case cr3_reg:
            if (is_write)
                assert(0);
            else
                *(uint32_t *) buf = env->cr[3];
            return;

        default:
            assert(0);
    }

    //XXX:Here, we assume little endian in the host machine!!!
    if (is_write)
        memcpy((unsigned char *) env->regs + offset, buf, size);
    else
        memcpy(buf, (unsigned char *) env->regs + offset, size);
}

void Fuzzy_read_register(int reg_id, void *buf)
{
    register_rw(reg_id, buf, 0);
}

void Fuzzy_write_register(int reg_id, void *buf)
{
    register_rw(reg_id, buf, 1);
}

void Fuzzy_void()
{
    return;
}

