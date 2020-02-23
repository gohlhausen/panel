/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sun 16 Feb 13:35:44 GMT 2020 */

#include "dft/codelet-dft.h"

#if defined(ARCH_PREFERS_FMA) || defined(ISA_EXTENSION_PREFERS_FMA)

/* Generated by: ../../../genfft/gen_twiddle.native -fma -compact -variables 4 -pipeline-latency 4 -n 2 -name t1_2 -include dft/scalar/t.h */

/*
 * This function contains 6 FP additions, 4 FP multiplications,
 * (or, 4 additions, 2 multiplications, 2 fused multiply/add),
 * 11 stack variables, 0 constants, and 8 memory accesses
 */
#include "dft/scalar/t.h"

static void t1_2(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     {
	  INT m;
	  for (m = mb, W = W + (mb * 2); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 2, MAKE_VOLATILE_STRIDE(4, rs)) {
	       E T1, Ta, T3, T6, T4, T8, T2, T7, T9, T5;
	       T1 = ri[0];
	       Ta = ii[0];
	       T3 = ri[WS(rs, 1)];
	       T6 = ii[WS(rs, 1)];
	       T2 = W[0];
	       T4 = T2 * T3;
	       T8 = T2 * T6;
	       T5 = W[1];
	       T7 = FMA(T5, T6, T4);
	       T9 = FNMS(T5, T3, T8);
	       ri[WS(rs, 1)] = T1 - T7;
	       ii[WS(rs, 1)] = Ta - T9;
	       ri[0] = T1 + T7;
	       ii[0] = T9 + Ta;
	  }
     }
}

static const tw_instr twinstr[] = {
     { TW_FULL, 0, 2 },
     { TW_NEXT, 1, 0 }
};

static const ct_desc desc = { 2, "t1_2", twinstr, &GENUS, { 4, 2, 2, 0 }, 0, 0, 0 };

void X(codelet_t1_2) (planner *p) {
     X(kdft_dit_register) (p, t1_2, &desc);
}
#else

/* Generated by: ../../../genfft/gen_twiddle.native -compact -variables 4 -pipeline-latency 4 -n 2 -name t1_2 -include dft/scalar/t.h */

/*
 * This function contains 6 FP additions, 4 FP multiplications,
 * (or, 4 additions, 2 multiplications, 2 fused multiply/add),
 * 9 stack variables, 0 constants, and 8 memory accesses
 */
#include "dft/scalar/t.h"

static void t1_2(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     {
	  INT m;
	  for (m = mb, W = W + (mb * 2); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 2, MAKE_VOLATILE_STRIDE(4, rs)) {
	       E T1, T8, T6, T7;
	       T1 = ri[0];
	       T8 = ii[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = ri[WS(rs, 1)];
		    T5 = ii[WS(rs, 1)];
		    T2 = W[0];
		    T4 = W[1];
		    T6 = FMA(T2, T3, T4 * T5);
		    T7 = FNMS(T4, T3, T2 * T5);
	       }
	       ri[WS(rs, 1)] = T1 - T6;
	       ii[WS(rs, 1)] = T8 - T7;
	       ri[0] = T1 + T6;
	       ii[0] = T7 + T8;
	  }
     }
}

static const tw_instr twinstr[] = {
     { TW_FULL, 0, 2 },
     { TW_NEXT, 1, 0 }
};

static const ct_desc desc = { 2, "t1_2", twinstr, &GENUS, { 4, 2, 2, 0 }, 0, 0, 0 };

void X(codelet_t1_2) (planner *p) {
     X(kdft_dit_register) (p, t1_2, &desc);
}
#endif