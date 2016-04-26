/*
 * BaseInstruction.c
 *
 *  Created on: 2016年4月19日
 *      Author: epeius
 */
#include "qemu/osdep.h"

#include "qemu/host-utils.h"
#include "cpu.h"
#include "disas/disas.h"
#include "tcg-op.h"
#include "BaseInstruction.h"
#include "FuzzyState.h"
#include <assert.h>
#include <stdio.h>
#include "OpCode.h"
#include "WallTimerWrapper.h"

void fuzzy_tcg_emit_custom_instruction(uint64_t arg)
{
    TCGv_i64 t0 = tcg_temp_new_i64();
    tcg_gen_movi_i64(t0, arg);

    gen_helper_onCustomInstruction(t0);
    tcg_temp_free_i64(t0);
    return;
}

void handleBuiltInOps(uint64_t opcode)
{
    switch ((opcode >> OPSHIFT) & 0xFF) {
        case 0: { /* fuzzy_version */
            fuzzy_version();
            break;
        }
        case 1: { /* Test time */
            CurTIme();
            break;
        }
            break;
        default:
            break;
    }

}

void HELPER(onCustomInstruction)(uint64_t opcode)
{
    uint8_t opc = (opcode >> OPSHIFT) & 0xFF;
    if (opc <= 0x70) {
        handleBuiltInOps(opcode);
    }
}

void fuzzy_version(void)
{
    uint32_t cur_EAX;
    //Fuzzy_void();
    Fuzzy_read_register(eax_reg, &cur_EAX);
    printf("This is just a test function, cur_EAX is 0x%08x\n", cur_EAX);
    cur_EAX = 1;
    Fuzzy_write_register(eax_reg, &cur_EAX);
}

// Test Functions
void CurTIme(void)
{
    struct WallTimerWrapper * wtw = WallTimer_GetInstance();
    printf("Cur time_second is %d, time_usecond is %d.\n", \
            WallTimer_GetSeconds(wtw), \
            WallTimer_GetUSeconds(wtw));
    return;
}
