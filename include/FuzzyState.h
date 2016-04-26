/*
 * FuzzyState.h
 *
 *  Created on: 2016年4月19日
 *      Author: epeius
 */

#ifndef FUZZYSTATE_H_
#define FUZZYSTATE_H_

#ifdef __cplusplus
extern "C"{
#endif

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

// Register related
void register_rw(int reg_id, void *buf, int is_write); // utility function
void Fuzzy_read_register(int reg_id, void *buf);
void Fuzzy_write_register(int reg_id, void *buf);

// Test
void Fuzzy_void();

// Memory related

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
namespace fuzzyqemu {
    struct WallTimer;
}
using fuzzyqemu::WallTimer;
#else
struct WallTimer;

#endif



/* segment registers */
#define es_reg 100
#define cs_reg 101
#define ss_reg 102
#define ds_reg 103
#define fs_reg 104
#define gs_reg 105

/* address-modifier dependent registers */
#define eAX_reg 108
#define eCX_reg 109
#define eDX_reg 110
#define eBX_reg 111
#define eSP_reg 112
#define eBP_reg 113
#define eSI_reg 114
#define eDI_reg 115

/* 8-bit registers */
#define al_reg 116
#define cl_reg 117
#define dl_reg 118
#define bl_reg 119
#define ah_reg 120
#define ch_reg 121
#define dh_reg 122
#define bh_reg 123

/* 16-bit registers */
#define ax_reg 124
#define cx_reg 125
#define dx_reg 126
#define bx_reg 127
#define sp_reg 128
#define bp_reg 129
#define si_reg 130
#define di_reg 131

/* 32-bit registers */
#define eax_reg 132
#define ecx_reg 133
#define edx_reg 134
#define ebx_reg 135
#define esp_reg 136
#define ebp_reg 137
#define esi_reg 138
#define edi_reg 139

#define eip_reg 140
#define cr3_reg 141

#endif /* FUZZYSTATE_H_ */
