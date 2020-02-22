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
/* Generated on Sun 16 Feb 13:35:52 GMT 2020 */

#include "dft/codelet-dft.h"

#if defined(ARCH_PREFERS_FMA) || defined(ISA_EXTENSION_PREFERS_FMA)

/* Generated by: ../../../genfft/gen_twiddle.native -fma -compact -variables 4 -pipeline-latency 4 -n 10 -name t1_10 -include dft/scalar/t.h */

/*
 * This function contains 102 FP additions, 72 FP multiplications,
 * (or, 48 additions, 18 multiplications, 54 fused multiply/add),
 * 47 stack variables, 4 constants, and 40 memory accesses
 */
#include "dft/scalar/t.h"

static void t1_10(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 18); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 18, MAKE_VOLATILE_STRIDE(20, rs)) {
	       E T8, T23, T12, T1U, TM, TZ, T10, T1F, T1G, T1P, T16, T17, T18, T1s, T1x;
	       E T25, Tl, Ty, Tz, T1I, T1J, T1O, T13, T14, T15, T1h, T1m, T24;
	       {
		    E T1, T1T, T3, T6, T4, T1R, T2, T7, T1S, T5;
		    T1 = ri[0];
		    T1T = ii[0];
		    T3 = ri[WS(rs, 5)];
		    T6 = ii[WS(rs, 5)];
		    T2 = W[8];
		    T4 = T2 * T3;
		    T1R = T2 * T6;
		    T5 = W[9];
		    T7 = FMA(T5, T6, T4);
		    T1S = FNMS(T5, T3, T1R);
		    T8 = T1 - T7;
		    T23 = T1T - T1S;
		    T12 = T1 + T7;
		    T1U = T1S + T1T;
	       }
	       {
		    E TF, T1p, TY, T1w, TL, T1r, TS, T1u;
		    {
			 E TB, TE, TC, T1o, TA, TD;
			 TB = ri[WS(rs, 4)];
			 TE = ii[WS(rs, 4)];
			 TA = W[6];
			 TC = TA * TB;
			 T1o = TA * TE;
			 TD = W[7];
			 TF = FMA(TD, TE, TC);
			 T1p = FNMS(TD, TB, T1o);
		    }
		    {
			 E TU, TX, TV, T1v, TT, TW;
			 TU = ri[WS(rs, 1)];
			 TX = ii[WS(rs, 1)];
			 TT = W[0];
			 TV = TT * TU;
			 T1v = TT * TX;
			 TW = W[1];
			 TY = FMA(TW, TX, TV);
			 T1w = FNMS(TW, TU, T1v);
		    }
		    {
			 E TH, TK, TI, T1q, TG, TJ;
			 TH = ri[WS(rs, 9)];
			 TK = ii[WS(rs, 9)];
			 TG = W[16];
			 TI = TG * TH;
			 T1q = TG * TK;
			 TJ = W[17];
			 TL = FMA(TJ, TK, TI);
			 T1r = FNMS(TJ, TH, T1q);
		    }
		    {
			 E TO, TR, TP, T1t, TN, TQ;
			 TO = ri[WS(rs, 6)];
			 TR = ii[WS(rs, 6)];
			 TN = W[10];
			 TP = TN * TO;
			 T1t = TN * TR;
			 TQ = W[11];
			 TS = FMA(TQ, TR, TP);
			 T1u = FNMS(TQ, TO, T1t);
		    }
		    TM = TF - TL;
		    TZ = TS - TY;
		    T10 = TM + TZ;
		    T1F = T1p + T1r;
		    T1G = T1u + T1w;
		    T1P = T1F + T1G;
		    T16 = TF + TL;
		    T17 = TS + TY;
		    T18 = T16 + T17;
		    T1s = T1p - T1r;
		    T1x = T1u - T1w;
		    T25 = T1s + T1x;
	       }
	       {
		    E Te, T1e, Tx, T1l, Tk, T1g, Tr, T1j;
		    {
			 E Ta, Td, Tb, T1d, T9, Tc;
			 Ta = ri[WS(rs, 2)];
			 Td = ii[WS(rs, 2)];
			 T9 = W[2];
			 Tb = T9 * Ta;
			 T1d = T9 * Td;
			 Tc = W[3];
			 Te = FMA(Tc, Td, Tb);
			 T1e = FNMS(Tc, Ta, T1d);
		    }
		    {
			 E Tt, Tw, Tu, T1k, Ts, Tv;
			 Tt = ri[WS(rs, 3)];
			 Tw = ii[WS(rs, 3)];
			 Ts = W[4];
			 Tu = Ts * Tt;
			 T1k = Ts * Tw;
			 Tv = W[5];
			 Tx = FMA(Tv, Tw, Tu);
			 T1l = FNMS(Tv, Tt, T1k);
		    }
		    {
			 E Tg, Tj, Th, T1f, Tf, Ti;
			 Tg = ri[WS(rs, 7)];
			 Tj = ii[WS(rs, 7)];
			 Tf = W[12];
			 Th = Tf * Tg;
			 T1f = Tf * Tj;
			 Ti = W[13];
			 Tk = FMA(Ti, Tj, Th);
			 T1g = FNMS(Ti, Tg, T1f);
		    }
		    {
			 E Tn, Tq, To, T1i, Tm, Tp;
			 Tn = ri[WS(rs, 8)];
			 Tq = ii[WS(rs, 8)];
			 Tm = W[14];
			 To = Tm * Tn;
			 T1i = Tm * Tq;
			 Tp = W[15];
			 Tr = FMA(Tp, Tq, To);
			 T1j = FNMS(Tp, Tn, T1i);
		    }
		    Tl = Te - Tk;
		    Ty = Tr - Tx;
		    Tz = Tl + Ty;
		    T1I = T1e + T1g;
		    T1J = T1j + T1l;
		    T1O = T1I + T1J;
		    T13 = Te + Tk;
		    T14 = Tr + Tx;
		    T15 = T13 + T14;
		    T1h = T1e - T1g;
		    T1m = T1j - T1l;
		    T24 = T1h + T1m;
	       }
	       {
		    E T1b, T11, T1a, T1z, T1B, T1n, T1y, T1A, T1c;
		    T1b = Tz - T10;
		    T11 = Tz + T10;
		    T1a = FNMS(KP250000000, T11, T8);
		    T1n = T1h - T1m;
		    T1y = T1s - T1x;
		    T1z = FMA(KP618033988, T1y, T1n);
		    T1B = FNMS(KP618033988, T1n, T1y);
		    ri[WS(rs, 5)] = T8 + T11;
		    T1A = FNMS(KP559016994, T1b, T1a);
		    ri[WS(rs, 7)] = FNMS(KP951056516, T1B, T1A);
		    ri[WS(rs, 3)] = FMA(KP951056516, T1B, T1A);
		    T1c = FMA(KP559016994, T1b, T1a);
		    ri[WS(rs, 9)] = FNMS(KP951056516, T1z, T1c);
		    ri[WS(rs, 1)] = FMA(KP951056516, T1z, T1c);
	       }
	       {
		    E T28, T26, T27, T2c, T2e, T2a, T2b, T2d, T29;
		    T28 = T24 - T25;
		    T26 = T24 + T25;
		    T27 = FNMS(KP250000000, T26, T23);
		    T2a = Tl - Ty;
		    T2b = TM - TZ;
		    T2c = FMA(KP618033988, T2b, T2a);
		    T2e = FNMS(KP618033988, T2a, T2b);
		    ii[WS(rs, 5)] = T26 + T23;
		    T2d = FNMS(KP559016994, T28, T27);
		    ii[WS(rs, 3)] = FNMS(KP951056516, T2e, T2d);
		    ii[WS(rs, 7)] = FMA(KP951056516, T2e, T2d);
		    T29 = FMA(KP559016994, T28, T27);
		    ii[WS(rs, 1)] = FNMS(KP951056516, T2c, T29);
		    ii[WS(rs, 9)] = FMA(KP951056516, T2c, T29);
	       }
	       {
		    E T1D, T19, T1C, T1L, T1N, T1H, T1K, T1M, T1E;
		    T1D = T15 - T18;
		    T19 = T15 + T18;
		    T1C = FNMS(KP250000000, T19, T12);
		    T1H = T1F - T1G;
		    T1K = T1I - T1J;
		    T1L = FNMS(KP618033988, T1K, T1H);
		    T1N = FMA(KP618033988, T1H, T1K);
		    ri[0] = T12 + T19;
		    T1M = FMA(KP559016994, T1D, T1C);
		    ri[WS(rs, 4)] = FNMS(KP951056516, T1N, T1M);
		    ri[WS(rs, 6)] = FMA(KP951056516, T1N, T1M);
		    T1E = FNMS(KP559016994, T1D, T1C);
		    ri[WS(rs, 2)] = FNMS(KP951056516, T1L, T1E);
		    ri[WS(rs, 8)] = FMA(KP951056516, T1L, T1E);
	       }
	       {
		    E T1W, T1Q, T1V, T20, T22, T1Y, T1Z, T21, T1X;
		    T1W = T1O - T1P;
		    T1Q = T1O + T1P;
		    T1V = FNMS(KP250000000, T1Q, T1U);
		    T1Y = T16 - T17;
		    T1Z = T13 - T14;
		    T20 = FNMS(KP618033988, T1Z, T1Y);
		    T22 = FMA(KP618033988, T1Y, T1Z);
		    ii[0] = T1Q + T1U;
		    T21 = FMA(KP559016994, T1W, T1V);
		    ii[WS(rs, 4)] = FMA(KP951056516, T22, T21);
		    ii[WS(rs, 6)] = FNMS(KP951056516, T22, T21);
		    T1X = FNMS(KP559016994, T1W, T1V);
		    ii[WS(rs, 2)] = FMA(KP951056516, T20, T1X);
		    ii[WS(rs, 8)] = FNMS(KP951056516, T20, T1X);
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     { TW_FULL, 0, 10 },
     { TW_NEXT, 1, 0 }
};

static const ct_desc desc = { 10, "t1_10", twinstr, &GENUS, { 48, 18, 54, 0 }, 0, 0, 0 };

void X(codelet_t1_10) (planner *p) {
     X(kdft_dit_register) (p, t1_10, &desc);
}
#else

/* Generated by: ../../../genfft/gen_twiddle.native -compact -variables 4 -pipeline-latency 4 -n 10 -name t1_10 -include dft/scalar/t.h */

/*
 * This function contains 102 FP additions, 60 FP multiplications,
 * (or, 72 additions, 30 multiplications, 30 fused multiply/add),
 * 45 stack variables, 4 constants, and 40 memory accesses
 */
#include "dft/scalar/t.h"

static void t1_10(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 18); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 18, MAKE_VOLATILE_STRIDE(20, rs)) {
	       E T7, T1O, TT, T1C, TF, TQ, TR, T1o, T1p, T1y, TX, TY, TZ, T1d, T1g;
	       E T1M, Ti, Tt, Tu, T1r, T1s, T1x, TU, TV, TW, T16, T19, T1L;
	       {
		    E T1, T1B, T6, T1A;
		    T1 = ri[0];
		    T1B = ii[0];
		    {
			 E T3, T5, T2, T4;
			 T3 = ri[WS(rs, 5)];
			 T5 = ii[WS(rs, 5)];
			 T2 = W[8];
			 T4 = W[9];
			 T6 = FMA(T2, T3, T4 * T5);
			 T1A = FNMS(T4, T3, T2 * T5);
		    }
		    T7 = T1 - T6;
		    T1O = T1B - T1A;
		    TT = T1 + T6;
		    T1C = T1A + T1B;
	       }
	       {
		    E Tz, T1b, TP, T1f, TE, T1c, TK, T1e;
		    {
			 E Tw, Ty, Tv, Tx;
			 Tw = ri[WS(rs, 4)];
			 Ty = ii[WS(rs, 4)];
			 Tv = W[6];
			 Tx = W[7];
			 Tz = FMA(Tv, Tw, Tx * Ty);
			 T1b = FNMS(Tx, Tw, Tv * Ty);
		    }
		    {
			 E TM, TO, TL, TN;
			 TM = ri[WS(rs, 1)];
			 TO = ii[WS(rs, 1)];
			 TL = W[0];
			 TN = W[1];
			 TP = FMA(TL, TM, TN * TO);
			 T1f = FNMS(TN, TM, TL * TO);
		    }
		    {
			 E TB, TD, TA, TC;
			 TB = ri[WS(rs, 9)];
			 TD = ii[WS(rs, 9)];
			 TA = W[16];
			 TC = W[17];
			 TE = FMA(TA, TB, TC * TD);
			 T1c = FNMS(TC, TB, TA * TD);
		    }
		    {
			 E TH, TJ, TG, TI;
			 TH = ri[WS(rs, 6)];
			 TJ = ii[WS(rs, 6)];
			 TG = W[10];
			 TI = W[11];
			 TK = FMA(TG, TH, TI * TJ);
			 T1e = FNMS(TI, TH, TG * TJ);
		    }
		    TF = Tz - TE;
		    TQ = TK - TP;
		    TR = TF + TQ;
		    T1o = T1b + T1c;
		    T1p = T1e + T1f;
		    T1y = T1o + T1p;
		    TX = Tz + TE;
		    TY = TK + TP;
		    TZ = TX + TY;
		    T1d = T1b - T1c;
		    T1g = T1e - T1f;
		    T1M = T1d + T1g;
	       }
	       {
		    E Tc, T14, Ts, T18, Th, T15, Tn, T17;
		    {
			 E T9, Tb, T8, Ta;
			 T9 = ri[WS(rs, 2)];
			 Tb = ii[WS(rs, 2)];
			 T8 = W[2];
			 Ta = W[3];
			 Tc = FMA(T8, T9, Ta * Tb);
			 T14 = FNMS(Ta, T9, T8 * Tb);
		    }
		    {
			 E Tp, Tr, To, Tq;
			 Tp = ri[WS(rs, 3)];
			 Tr = ii[WS(rs, 3)];
			 To = W[4];
			 Tq = W[5];
			 Ts = FMA(To, Tp, Tq * Tr);
			 T18 = FNMS(Tq, Tp, To * Tr);
		    }
		    {
			 E Te, Tg, Td, Tf;
			 Te = ri[WS(rs, 7)];
			 Tg = ii[WS(rs, 7)];
			 Td = W[12];
			 Tf = W[13];
			 Th = FMA(Td, Te, Tf * Tg);
			 T15 = FNMS(Tf, Te, Td * Tg);
		    }
		    {
			 E Tk, Tm, Tj, Tl;
			 Tk = ri[WS(rs, 8)];
			 Tm = ii[WS(rs, 8)];
			 Tj = W[14];
			 Tl = W[15];
			 Tn = FMA(Tj, Tk, Tl * Tm);
			 T17 = FNMS(Tl, Tk, Tj * Tm);
		    }
		    Ti = Tc - Th;
		    Tt = Tn - Ts;
		    Tu = Ti + Tt;
		    T1r = T14 + T15;
		    T1s = T17 + T18;
		    T1x = T1r + T1s;
		    TU = Tc + Th;
		    TV = Tn + Ts;
		    TW = TU + TV;
		    T16 = T14 - T15;
		    T19 = T17 - T18;
		    T1L = T16 + T19;
	       }
	       {
		    E T11, TS, T12, T1i, T1k, T1a, T1h, T1j, T13;
		    T11 = KP559016994 * (Tu - TR);
		    TS = Tu + TR;
		    T12 = FNMS(KP250000000, TS, T7);
		    T1a = T16 - T19;
		    T1h = T1d - T1g;
		    T1i = FMA(KP951056516, T1a, KP587785252 * T1h);
		    T1k = FNMS(KP587785252, T1a, KP951056516 * T1h);
		    ri[WS(rs, 5)] = T7 + TS;
		    T1j = T12 - T11;
		    ri[WS(rs, 7)] = T1j - T1k;
		    ri[WS(rs, 3)] = T1j + T1k;
		    T13 = T11 + T12;
		    ri[WS(rs, 9)] = T13 - T1i;
		    ri[WS(rs, 1)] = T13 + T1i;
	       }
	       {
		    E T1N, T1P, T1Q, T1U, T1W, T1S, T1T, T1V, T1R;
		    T1N = KP559016994 * (T1L - T1M);
		    T1P = T1L + T1M;
		    T1Q = FNMS(KP250000000, T1P, T1O);
		    T1S = Ti - Tt;
		    T1T = TF - TQ;
		    T1U = FMA(KP951056516, T1S, KP587785252 * T1T);
		    T1W = FNMS(KP587785252, T1S, KP951056516 * T1T);
		    ii[WS(rs, 5)] = T1P + T1O;
		    T1V = T1Q - T1N;
		    ii[WS(rs, 3)] = T1V - T1W;
		    ii[WS(rs, 7)] = T1W + T1V;
		    T1R = T1N + T1Q;
		    ii[WS(rs, 1)] = T1R - T1U;
		    ii[WS(rs, 9)] = T1U + T1R;
	       }
	       {
		    E T1m, T10, T1l, T1u, T1w, T1q, T1t, T1v, T1n;
		    T1m = KP559016994 * (TW - TZ);
		    T10 = TW + TZ;
		    T1l = FNMS(KP250000000, T10, TT);
		    T1q = T1o - T1p;
		    T1t = T1r - T1s;
		    T1u = FNMS(KP587785252, T1t, KP951056516 * T1q);
		    T1w = FMA(KP951056516, T1t, KP587785252 * T1q);
		    ri[0] = TT + T10;
		    T1v = T1m + T1l;
		    ri[WS(rs, 4)] = T1v - T1w;
		    ri[WS(rs, 6)] = T1v + T1w;
		    T1n = T1l - T1m;
		    ri[WS(rs, 2)] = T1n - T1u;
		    ri[WS(rs, 8)] = T1n + T1u;
	       }
	       {
		    E T1H, T1z, T1G, T1F, T1J, T1D, T1E, T1K, T1I;
		    T1H = KP559016994 * (T1x - T1y);
		    T1z = T1x + T1y;
		    T1G = FNMS(KP250000000, T1z, T1C);
		    T1D = TX - TY;
		    T1E = TU - TV;
		    T1F = FNMS(KP587785252, T1E, KP951056516 * T1D);
		    T1J = FMA(KP951056516, T1E, KP587785252 * T1D);
		    ii[0] = T1z + T1C;
		    T1K = T1H + T1G;
		    ii[WS(rs, 4)] = T1J + T1K;
		    ii[WS(rs, 6)] = T1K - T1J;
		    T1I = T1G - T1H;
		    ii[WS(rs, 2)] = T1F + T1I;
		    ii[WS(rs, 8)] = T1I - T1F;
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     { TW_FULL, 0, 10 },
     { TW_NEXT, 1, 0 }
};

static const ct_desc desc = { 10, "t1_10", twinstr, &GENUS, { 72, 30, 30, 0 }, 0, 0, 0 };

void X(codelet_t1_10) (planner *p) {
     X(kdft_dit_register) (p, t1_10, &desc);
}
#endif
