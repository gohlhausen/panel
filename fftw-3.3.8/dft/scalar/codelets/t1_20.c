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
/* Generated on Sun 16 Feb 13:39:26 GMT 2020 */

#include "dft/codelet-dft.h"

#if defined(ARCH_PREFERS_FMA) || defined(ISA_EXTENSION_PREFERS_FMA)

/* Generated by: ../../../genfft/gen_twiddle.native -fma -compact -variables 4 -pipeline-latency 4 -n 20 -name t1_20 -include dft/scalar/t.h */

/*
 * This function contains 246 FP additions, 148 FP multiplications,
 * (or, 136 additions, 38 multiplications, 110 fused multiply/add),
 * 61 stack variables, 4 constants, and 80 memory accesses
 */
#include "dft/scalar/t.h"

static void t1_20(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 38); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 38, MAKE_VOLATILE_STRIDE(40, rs)) {
	       E T8, T4N, T2i, T4r, Tl, T4O, T2n, T4n, TN, T2b, T40, T4b, T2v, T3v, T3i;
	       E T3F, T27, T2f, T3W, T4f, T2R, T3z, T3a, T3J, T1G, T2e, T3T, T4e, T2K, T3y;
	       E T33, T3I, T1e, T2c, T43, T4c, T2C, T3w, T3p, T3G;
	       {
		    E T1, T4q, T3, T6, T4, T4o, T2, T7, T4p, T5;
		    T1 = ri[0];
		    T4q = ii[0];
		    T3 = ri[WS(rs, 10)];
		    T6 = ii[WS(rs, 10)];
		    T2 = W[18];
		    T4 = T2 * T3;
		    T4o = T2 * T6;
		    T5 = W[19];
		    T7 = FMA(T5, T6, T4);
		    T4p = FNMS(T5, T3, T4o);
		    T8 = T1 + T7;
		    T4N = T4q - T4p;
		    T2i = T1 - T7;
		    T4r = T4p + T4q;
	       }
	       {
		    E Ta, Td, Tb, T2j, Tg, Tj, Th, T2l, T9, Tf;
		    Ta = ri[WS(rs, 5)];
		    Td = ii[WS(rs, 5)];
		    T9 = W[8];
		    Tb = T9 * Ta;
		    T2j = T9 * Td;
		    Tg = ri[WS(rs, 15)];
		    Tj = ii[WS(rs, 15)];
		    Tf = W[28];
		    Th = Tf * Tg;
		    T2l = Tf * Tj;
		    {
			 E Te, T2k, Tk, T2m, Tc, Ti;
			 Tc = W[9];
			 Te = FMA(Tc, Td, Tb);
			 T2k = FNMS(Tc, Ta, T2j);
			 Ti = W[29];
			 Tk = FMA(Ti, Tj, Th);
			 T2m = FNMS(Ti, Tg, T2l);
			 Tl = Te + Tk;
			 T4O = Te - Tk;
			 T2n = T2k - T2m;
			 T4n = T2k + T2m;
		    }
	       }
	       {
		    E Ts, T3d, TL, T2t, Ty, T3f, TF, T2r;
		    {
			 E To, Tr, Tp, T3c, Tn, Tq;
			 To = ri[WS(rs, 4)];
			 Tr = ii[WS(rs, 4)];
			 Tn = W[6];
			 Tp = Tn * To;
			 T3c = Tn * Tr;
			 Tq = W[7];
			 Ts = FMA(Tq, Tr, Tp);
			 T3d = FNMS(Tq, To, T3c);
		    }
		    {
			 E TH, TK, TI, T2s, TG, TJ;
			 TH = ri[WS(rs, 19)];
			 TK = ii[WS(rs, 19)];
			 TG = W[36];
			 TI = TG * TH;
			 T2s = TG * TK;
			 TJ = W[37];
			 TL = FMA(TJ, TK, TI);
			 T2t = FNMS(TJ, TH, T2s);
		    }
		    {
			 E Tu, Tx, Tv, T3e, Tt, Tw;
			 Tu = ri[WS(rs, 14)];
			 Tx = ii[WS(rs, 14)];
			 Tt = W[26];
			 Tv = Tt * Tu;
			 T3e = Tt * Tx;
			 Tw = W[27];
			 Ty = FMA(Tw, Tx, Tv);
			 T3f = FNMS(Tw, Tu, T3e);
		    }
		    {
			 E TB, TE, TC, T2q, TA, TD;
			 TB = ri[WS(rs, 9)];
			 TE = ii[WS(rs, 9)];
			 TA = W[16];
			 TC = TA * TB;
			 T2q = TA * TE;
			 TD = W[17];
			 TF = FMA(TD, TE, TC);
			 T2r = FNMS(TD, TB, T2q);
		    }
		    {
			 E Tz, TM, T3Y, T3Z;
			 Tz = Ts + Ty;
			 TM = TF + TL;
			 TN = Tz - TM;
			 T2b = Tz + TM;
			 T3Y = T3d + T3f;
			 T3Z = T2r + T2t;
			 T40 = T3Y - T3Z;
			 T4b = T3Y + T3Z;
		    }
		    {
			 E T2p, T2u, T3g, T3h;
			 T2p = Ts - Ty;
			 T2u = T2r - T2t;
			 T2v = T2p - T2u;
			 T3v = T2p + T2u;
			 T3g = T3d - T3f;
			 T3h = TF - TL;
			 T3i = T3g + T3h;
			 T3F = T3g - T3h;
		    }
	       }
	       {
		    E T1M, T35, T25, T2P, T1S, T37, T1Z, T2N;
		    {
			 E T1I, T1L, T1J, T34, T1H, T1K;
			 T1I = ri[WS(rs, 12)];
			 T1L = ii[WS(rs, 12)];
			 T1H = W[22];
			 T1J = T1H * T1I;
			 T34 = T1H * T1L;
			 T1K = W[23];
			 T1M = FMA(T1K, T1L, T1J);
			 T35 = FNMS(T1K, T1I, T34);
		    }
		    {
			 E T21, T24, T22, T2O, T20, T23;
			 T21 = ri[WS(rs, 7)];
			 T24 = ii[WS(rs, 7)];
			 T20 = W[12];
			 T22 = T20 * T21;
			 T2O = T20 * T24;
			 T23 = W[13];
			 T25 = FMA(T23, T24, T22);
			 T2P = FNMS(T23, T21, T2O);
		    }
		    {
			 E T1O, T1R, T1P, T36, T1N, T1Q;
			 T1O = ri[WS(rs, 2)];
			 T1R = ii[WS(rs, 2)];
			 T1N = W[2];
			 T1P = T1N * T1O;
			 T36 = T1N * T1R;
			 T1Q = W[3];
			 T1S = FMA(T1Q, T1R, T1P);
			 T37 = FNMS(T1Q, T1O, T36);
		    }
		    {
			 E T1V, T1Y, T1W, T2M, T1U, T1X;
			 T1V = ri[WS(rs, 17)];
			 T1Y = ii[WS(rs, 17)];
			 T1U = W[32];
			 T1W = T1U * T1V;
			 T2M = T1U * T1Y;
			 T1X = W[33];
			 T1Z = FMA(T1X, T1Y, T1W);
			 T2N = FNMS(T1X, T1V, T2M);
		    }
		    {
			 E T1T, T26, T3U, T3V;
			 T1T = T1M + T1S;
			 T26 = T1Z + T25;
			 T27 = T1T - T26;
			 T2f = T1T + T26;
			 T3U = T35 + T37;
			 T3V = T2N + T2P;
			 T3W = T3U - T3V;
			 T4f = T3U + T3V;
		    }
		    {
			 E T2L, T2Q, T38, T39;
			 T2L = T1M - T1S;
			 T2Q = T2N - T2P;
			 T2R = T2L - T2Q;
			 T3z = T2L + T2Q;
			 T38 = T35 - T37;
			 T39 = T1Z - T25;
			 T3a = T38 + T39;
			 T3J = T38 - T39;
		    }
	       }
	       {
		    E T1l, T2Y, T1E, T2I, T1r, T30, T1y, T2G;
		    {
			 E T1h, T1k, T1i, T2X, T1g, T1j;
			 T1h = ri[WS(rs, 8)];
			 T1k = ii[WS(rs, 8)];
			 T1g = W[14];
			 T1i = T1g * T1h;
			 T2X = T1g * T1k;
			 T1j = W[15];
			 T1l = FMA(T1j, T1k, T1i);
			 T2Y = FNMS(T1j, T1h, T2X);
		    }
		    {
			 E T1A, T1D, T1B, T2H, T1z, T1C;
			 T1A = ri[WS(rs, 3)];
			 T1D = ii[WS(rs, 3)];
			 T1z = W[4];
			 T1B = T1z * T1A;
			 T2H = T1z * T1D;
			 T1C = W[5];
			 T1E = FMA(T1C, T1D, T1B);
			 T2I = FNMS(T1C, T1A, T2H);
		    }
		    {
			 E T1n, T1q, T1o, T2Z, T1m, T1p;
			 T1n = ri[WS(rs, 18)];
			 T1q = ii[WS(rs, 18)];
			 T1m = W[34];
			 T1o = T1m * T1n;
			 T2Z = T1m * T1q;
			 T1p = W[35];
			 T1r = FMA(T1p, T1q, T1o);
			 T30 = FNMS(T1p, T1n, T2Z);
		    }
		    {
			 E T1u, T1x, T1v, T2F, T1t, T1w;
			 T1u = ri[WS(rs, 13)];
			 T1x = ii[WS(rs, 13)];
			 T1t = W[24];
			 T1v = T1t * T1u;
			 T2F = T1t * T1x;
			 T1w = W[25];
			 T1y = FMA(T1w, T1x, T1v);
			 T2G = FNMS(T1w, T1u, T2F);
		    }
		    {
			 E T1s, T1F, T3R, T3S;
			 T1s = T1l + T1r;
			 T1F = T1y + T1E;
			 T1G = T1s - T1F;
			 T2e = T1s + T1F;
			 T3R = T2Y + T30;
			 T3S = T2G + T2I;
			 T3T = T3R - T3S;
			 T4e = T3R + T3S;
		    }
		    {
			 E T2E, T2J, T31, T32;
			 T2E = T1l - T1r;
			 T2J = T2G - T2I;
			 T2K = T2E - T2J;
			 T3y = T2E + T2J;
			 T31 = T2Y - T30;
			 T32 = T1y - T1E;
			 T33 = T31 + T32;
			 T3I = T31 - T32;
		    }
	       }
	       {
		    E TT, T3k, T1c, T2A, TZ, T3m, T16, T2y;
		    {
			 E TP, TS, TQ, T3j, TO, TR;
			 TP = ri[WS(rs, 16)];
			 TS = ii[WS(rs, 16)];
			 TO = W[30];
			 TQ = TO * TP;
			 T3j = TO * TS;
			 TR = W[31];
			 TT = FMA(TR, TS, TQ);
			 T3k = FNMS(TR, TP, T3j);
		    }
		    {
			 E T18, T1b, T19, T2z, T17, T1a;
			 T18 = ri[WS(rs, 11)];
			 T1b = ii[WS(rs, 11)];
			 T17 = W[20];
			 T19 = T17 * T18;
			 T2z = T17 * T1b;
			 T1a = W[21];
			 T1c = FMA(T1a, T1b, T19);
			 T2A = FNMS(T1a, T18, T2z);
		    }
		    {
			 E TV, TY, TW, T3l, TU, TX;
			 TV = ri[WS(rs, 6)];
			 TY = ii[WS(rs, 6)];
			 TU = W[10];
			 TW = TU * TV;
			 T3l = TU * TY;
			 TX = W[11];
			 TZ = FMA(TX, TY, TW);
			 T3m = FNMS(TX, TV, T3l);
		    }
		    {
			 E T12, T15, T13, T2x, T11, T14;
			 T12 = ri[WS(rs, 1)];
			 T15 = ii[WS(rs, 1)];
			 T11 = W[0];
			 T13 = T11 * T12;
			 T2x = T11 * T15;
			 T14 = W[1];
			 T16 = FMA(T14, T15, T13);
			 T2y = FNMS(T14, T12, T2x);
		    }
		    {
			 E T10, T1d, T41, T42;
			 T10 = TT + TZ;
			 T1d = T16 + T1c;
			 T1e = T10 - T1d;
			 T2c = T10 + T1d;
			 T41 = T3k + T3m;
			 T42 = T2y + T2A;
			 T43 = T41 - T42;
			 T4c = T41 + T42;
		    }
		    {
			 E T2w, T2B, T3n, T3o;
			 T2w = TT - TZ;
			 T2B = T2y - T2A;
			 T2C = T2w - T2B;
			 T3w = T2w + T2B;
			 T3n = T3k - T3m;
			 T3o = T16 - T1c;
			 T3p = T3n + T3o;
			 T3G = T3n - T3o;
		    }
	       }
	       {
		    E T45, T47, Tm, T29, T3O, T3P, T46, T3Q;
		    {
			 E T3X, T44, T1f, T28;
			 T3X = T3T - T3W;
			 T44 = T40 - T43;
			 T45 = FNMS(KP618033988, T44, T3X);
			 T47 = FMA(KP618033988, T3X, T44);
			 Tm = T8 - Tl;
			 T1f = TN + T1e;
			 T28 = T1G + T27;
			 T29 = T1f + T28;
			 T3O = FNMS(KP250000000, T29, Tm);
			 T3P = T1f - T28;
		    }
		    ri[WS(rs, 10)] = Tm + T29;
		    T46 = FMA(KP559016994, T3P, T3O);
		    ri[WS(rs, 14)] = FNMS(KP951056516, T47, T46);
		    ri[WS(rs, 6)] = FMA(KP951056516, T47, T46);
		    T3Q = FNMS(KP559016994, T3P, T3O);
		    ri[WS(rs, 2)] = FNMS(KP951056516, T45, T3Q);
		    ri[WS(rs, 18)] = FMA(KP951056516, T45, T3Q);
	       }
	       {
		    E T4K, T4M, T4B, T4E, T4F, T4G, T4L, T4H;
		    {
			 E T4I, T4J, T4C, T4D;
			 T4I = T1G - T27;
			 T4J = TN - T1e;
			 T4K = FNMS(KP618033988, T4J, T4I);
			 T4M = FMA(KP618033988, T4I, T4J);
			 T4B = T4r - T4n;
			 T4C = T40 + T43;
			 T4D = T3T + T3W;
			 T4E = T4C + T4D;
			 T4F = FNMS(KP250000000, T4E, T4B);
			 T4G = T4C - T4D;
		    }
		    ii[WS(rs, 10)] = T4E + T4B;
		    T4L = FMA(KP559016994, T4G, T4F);
		    ii[WS(rs, 6)] = FNMS(KP951056516, T4M, T4L);
		    ii[WS(rs, 14)] = FMA(KP951056516, T4M, T4L);
		    T4H = FNMS(KP559016994, T4G, T4F);
		    ii[WS(rs, 2)] = FMA(KP951056516, T4K, T4H);
		    ii[WS(rs, 18)] = FNMS(KP951056516, T4K, T4H);
	       }
	       {
		    E T4h, T4j, T2a, T2h, T48, T49, T4i, T4a;
		    {
			 E T4d, T4g, T2d, T2g;
			 T4d = T4b - T4c;
			 T4g = T4e - T4f;
			 T4h = FMA(KP618033988, T4g, T4d);
			 T4j = FNMS(KP618033988, T4d, T4g);
			 T2a = T8 + Tl;
			 T2d = T2b + T2c;
			 T2g = T2e + T2f;
			 T2h = T2d + T2g;
			 T48 = FNMS(KP250000000, T2h, T2a);
			 T49 = T2d - T2g;
		    }
		    ri[0] = T2a + T2h;
		    T4i = FNMS(KP559016994, T49, T48);
		    ri[WS(rs, 12)] = FNMS(KP951056516, T4j, T4i);
		    ri[WS(rs, 8)] = FMA(KP951056516, T4j, T4i);
		    T4a = FMA(KP559016994, T49, T48);
		    ri[WS(rs, 4)] = FNMS(KP951056516, T4h, T4a);
		    ri[WS(rs, 16)] = FMA(KP951056516, T4h, T4a);
	       }
	       {
		    E T4y, T4A, T4s, T4m, T4t, T4u, T4z, T4v;
		    {
			 E T4w, T4x, T4k, T4l;
			 T4w = T2b - T2c;
			 T4x = T2e - T2f;
			 T4y = FMA(KP618033988, T4x, T4w);
			 T4A = FNMS(KP618033988, T4w, T4x);
			 T4s = T4n + T4r;
			 T4k = T4b + T4c;
			 T4l = T4e + T4f;
			 T4m = T4k + T4l;
			 T4t = FNMS(KP250000000, T4m, T4s);
			 T4u = T4k - T4l;
		    }
		    ii[0] = T4m + T4s;
		    T4z = FNMS(KP559016994, T4u, T4t);
		    ii[WS(rs, 8)] = FNMS(KP951056516, T4A, T4z);
		    ii[WS(rs, 12)] = FMA(KP951056516, T4A, T4z);
		    T4v = FMA(KP559016994, T4u, T4t);
		    ii[WS(rs, 4)] = FMA(KP951056516, T4y, T4v);
		    ii[WS(rs, 16)] = FNMS(KP951056516, T4y, T4v);
	       }
	       {
		    E T3r, T3t, T2o, T2T, T2U, T2V, T3s, T2W;
		    {
			 E T3b, T3q, T2D, T2S;
			 T3b = T33 - T3a;
			 T3q = T3i - T3p;
			 T3r = FNMS(KP618033988, T3q, T3b);
			 T3t = FMA(KP618033988, T3b, T3q);
			 T2o = T2i - T2n;
			 T2D = T2v + T2C;
			 T2S = T2K + T2R;
			 T2T = T2D + T2S;
			 T2U = FNMS(KP250000000, T2T, T2o);
			 T2V = T2D - T2S;
		    }
		    ri[WS(rs, 15)] = T2o + T2T;
		    T3s = FMA(KP559016994, T2V, T2U);
		    ri[WS(rs, 11)] = FMA(KP951056516, T3t, T3s);
		    ri[WS(rs, 19)] = FNMS(KP951056516, T3t, T3s);
		    T2W = FNMS(KP559016994, T2V, T2U);
		    ri[WS(rs, 3)] = FMA(KP951056516, T3r, T2W);
		    ri[WS(rs, 7)] = FNMS(KP951056516, T3r, T2W);
	       }
	       {
		    E T5a, T5c, T51, T54, T55, T56, T5b, T57;
		    {
			 E T58, T59, T52, T53;
			 T58 = T2K - T2R;
			 T59 = T2v - T2C;
			 T5a = FNMS(KP618033988, T59, T58);
			 T5c = FMA(KP618033988, T58, T59);
			 T51 = T4O + T4N;
			 T52 = T3i + T3p;
			 T53 = T33 + T3a;
			 T54 = T52 + T53;
			 T55 = FNMS(KP250000000, T54, T51);
			 T56 = T52 - T53;
		    }
		    ii[WS(rs, 15)] = T54 + T51;
		    T5b = FMA(KP559016994, T56, T55);
		    ii[WS(rs, 11)] = FNMS(KP951056516, T5c, T5b);
		    ii[WS(rs, 19)] = FMA(KP951056516, T5c, T5b);
		    T57 = FNMS(KP559016994, T56, T55);
		    ii[WS(rs, 3)] = FNMS(KP951056516, T5a, T57);
		    ii[WS(rs, 7)] = FMA(KP951056516, T5a, T57);
	       }
	       {
		    E T3L, T3N, T3u, T3B, T3C, T3D, T3M, T3E;
		    {
			 E T3H, T3K, T3x, T3A;
			 T3H = T3F - T3G;
			 T3K = T3I - T3J;
			 T3L = FMA(KP618033988, T3K, T3H);
			 T3N = FNMS(KP618033988, T3H, T3K);
			 T3u = T2i + T2n;
			 T3x = T3v + T3w;
			 T3A = T3y + T3z;
			 T3B = T3x + T3A;
			 T3C = FNMS(KP250000000, T3B, T3u);
			 T3D = T3x - T3A;
		    }
		    ri[WS(rs, 5)] = T3u + T3B;
		    T3M = FNMS(KP559016994, T3D, T3C);
		    ri[WS(rs, 13)] = FMA(KP951056516, T3N, T3M);
		    ri[WS(rs, 17)] = FNMS(KP951056516, T3N, T3M);
		    T3E = FMA(KP559016994, T3D, T3C);
		    ri[WS(rs, 1)] = FMA(KP951056516, T3L, T3E);
		    ri[WS(rs, 9)] = FNMS(KP951056516, T3L, T3E);
	       }
	       {
		    E T4Y, T50, T4P, T4S, T4T, T4U, T4Z, T4V;
		    {
			 E T4W, T4X, T4Q, T4R;
			 T4W = T3v - T3w;
			 T4X = T3y - T3z;
			 T4Y = FMA(KP618033988, T4X, T4W);
			 T50 = FNMS(KP618033988, T4W, T4X);
			 T4P = T4N - T4O;
			 T4Q = T3F + T3G;
			 T4R = T3I + T3J;
			 T4S = T4Q + T4R;
			 T4T = FNMS(KP250000000, T4S, T4P);
			 T4U = T4Q - T4R;
		    }
		    ii[WS(rs, 5)] = T4S + T4P;
		    T4Z = FNMS(KP559016994, T4U, T4T);
		    ii[WS(rs, 13)] = FNMS(KP951056516, T50, T4Z);
		    ii[WS(rs, 17)] = FMA(KP951056516, T50, T4Z);
		    T4V = FMA(KP559016994, T4U, T4T);
		    ii[WS(rs, 1)] = FNMS(KP951056516, T4Y, T4V);
		    ii[WS(rs, 9)] = FMA(KP951056516, T4Y, T4V);
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     { TW_FULL, 0, 20 },
     { TW_NEXT, 1, 0 }
};

static const ct_desc desc = { 20, "t1_20", twinstr, &GENUS, { 136, 38, 110, 0 }, 0, 0, 0 };

void X(codelet_t1_20) (planner *p) {
     X(kdft_dit_register) (p, t1_20, &desc);
}
#else

/* Generated by: ../../../genfft/gen_twiddle.native -compact -variables 4 -pipeline-latency 4 -n 20 -name t1_20 -include dft/scalar/t.h */

/*
 * This function contains 246 FP additions, 124 FP multiplications,
 * (or, 184 additions, 62 multiplications, 62 fused multiply/add),
 * 85 stack variables, 4 constants, and 80 memory accesses
 */
#include "dft/scalar/t.h"

static void t1_20(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     {
	  INT m;
	  for (m = mb, W = W + (mb * 38); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 38, MAKE_VOLATILE_STRIDE(40, rs)) {
	       E Tj, T1R, T4g, T4p, T2q, T37, T3Q, T42, T1r, T1O, T1P, T3i, T3l, T44, T3D;
	       E T3E, T3K, T1V, T1W, T1X, T23, T28, T4r, T2W, T2X, T4c, T33, T34, T35, T2G;
	       E T2L, T2M, TG, T13, T14, T3p, T3s, T43, T3A, T3B, T3J, T1S, T1T, T1U, T2e;
	       E T2j, T4q, T2T, T2U, T4b, T30, T31, T32, T2v, T2A, T2B;
	       {
		    E T1, T3O, T6, T3N, Tc, T2n, Th, T2o;
		    T1 = ri[0];
		    T3O = ii[0];
		    {
			 E T3, T5, T2, T4;
			 T3 = ri[WS(rs, 10)];
			 T5 = ii[WS(rs, 10)];
			 T2 = W[18];
			 T4 = W[19];
			 T6 = FMA(T2, T3, T4 * T5);
			 T3N = FNMS(T4, T3, T2 * T5);
		    }
		    {
			 E T9, Tb, T8, Ta;
			 T9 = ri[WS(rs, 5)];
			 Tb = ii[WS(rs, 5)];
			 T8 = W[8];
			 Ta = W[9];
			 Tc = FMA(T8, T9, Ta * Tb);
			 T2n = FNMS(Ta, T9, T8 * Tb);
		    }
		    {
			 E Te, Tg, Td, Tf;
			 Te = ri[WS(rs, 15)];
			 Tg = ii[WS(rs, 15)];
			 Td = W[28];
			 Tf = W[29];
			 Th = FMA(Td, Te, Tf * Tg);
			 T2o = FNMS(Tf, Te, Td * Tg);
		    }
		    {
			 E T7, Ti, T4e, T4f;
			 T7 = T1 + T6;
			 Ti = Tc + Th;
			 Tj = T7 - Ti;
			 T1R = T7 + Ti;
			 T4e = T3O - T3N;
			 T4f = Tc - Th;
			 T4g = T4e - T4f;
			 T4p = T4f + T4e;
		    }
		    {
			 E T2m, T2p, T3M, T3P;
			 T2m = T1 - T6;
			 T2p = T2n - T2o;
			 T2q = T2m - T2p;
			 T37 = T2m + T2p;
			 T3M = T2n + T2o;
			 T3P = T3N + T3O;
			 T3Q = T3M + T3P;
			 T42 = T3P - T3M;
		    }
	       }
	       {
		    E T1f, T3g, T21, T2C, T1N, T3k, T27, T2K, T1q, T3h, T22, T2F, T1C, T3j, T26;
		    E T2H;
		    {
			 E T19, T1Z, T1e, T20;
			 {
			      E T16, T18, T15, T17;
			      T16 = ri[WS(rs, 8)];
			      T18 = ii[WS(rs, 8)];
			      T15 = W[14];
			      T17 = W[15];
			      T19 = FMA(T15, T16, T17 * T18);
			      T1Z = FNMS(T17, T16, T15 * T18);
			 }
			 {
			      E T1b, T1d, T1a, T1c;
			      T1b = ri[WS(rs, 18)];
			      T1d = ii[WS(rs, 18)];
			      T1a = W[34];
			      T1c = W[35];
			      T1e = FMA(T1a, T1b, T1c * T1d);
			      T20 = FNMS(T1c, T1b, T1a * T1d);
			 }
			 T1f = T19 + T1e;
			 T3g = T1Z + T20;
			 T21 = T1Z - T20;
			 T2C = T19 - T1e;
		    }
		    {
			 E T1H, T2I, T1M, T2J;
			 {
			      E T1E, T1G, T1D, T1F;
			      T1E = ri[WS(rs, 17)];
			      T1G = ii[WS(rs, 17)];
			      T1D = W[32];
			      T1F = W[33];
			      T1H = FMA(T1D, T1E, T1F * T1G);
			      T2I = FNMS(T1F, T1E, T1D * T1G);
			 }
			 {
			      E T1J, T1L, T1I, T1K;
			      T1J = ri[WS(rs, 7)];
			      T1L = ii[WS(rs, 7)];
			      T1I = W[12];
			      T1K = W[13];
			      T1M = FMA(T1I, T1J, T1K * T1L);
			      T2J = FNMS(T1K, T1J, T1I * T1L);
			 }
			 T1N = T1H + T1M;
			 T3k = T2I + T2J;
			 T27 = T1H - T1M;
			 T2K = T2I - T2J;
		    }
		    {
			 E T1k, T2D, T1p, T2E;
			 {
			      E T1h, T1j, T1g, T1i;
			      T1h = ri[WS(rs, 13)];
			      T1j = ii[WS(rs, 13)];
			      T1g = W[24];
			      T1i = W[25];
			      T1k = FMA(T1g, T1h, T1i * T1j);
			      T2D = FNMS(T1i, T1h, T1g * T1j);
			 }
			 {
			      E T1m, T1o, T1l, T1n;
			      T1m = ri[WS(rs, 3)];
			      T1o = ii[WS(rs, 3)];
			      T1l = W[4];
			      T1n = W[5];
			      T1p = FMA(T1l, T1m, T1n * T1o);
			      T2E = FNMS(T1n, T1m, T1l * T1o);
			 }
			 T1q = T1k + T1p;
			 T3h = T2D + T2E;
			 T22 = T1k - T1p;
			 T2F = T2D - T2E;
		    }
		    {
			 E T1w, T24, T1B, T25;
			 {
			      E T1t, T1v, T1s, T1u;
			      T1t = ri[WS(rs, 12)];
			      T1v = ii[WS(rs, 12)];
			      T1s = W[22];
			      T1u = W[23];
			      T1w = FMA(T1s, T1t, T1u * T1v);
			      T24 = FNMS(T1u, T1t, T1s * T1v);
			 }
			 {
			      E T1y, T1A, T1x, T1z;
			      T1y = ri[WS(rs, 2)];
			      T1A = ii[WS(rs, 2)];
			      T1x = W[2];
			      T1z = W[3];
			      T1B = FMA(T1x, T1y, T1z * T1A);
			      T25 = FNMS(T1z, T1y, T1x * T1A);
			 }
			 T1C = T1w + T1B;
			 T3j = T24 + T25;
			 T26 = T24 - T25;
			 T2H = T1w - T1B;
		    }
		    T1r = T1f - T1q;
		    T1O = T1C - T1N;
		    T1P = T1r + T1O;
		    T3i = T3g - T3h;
		    T3l = T3j - T3k;
		    T44 = T3i + T3l;
		    T3D = T3g + T3h;
		    T3E = T3j + T3k;
		    T3K = T3D + T3E;
		    T1V = T1f + T1q;
		    T1W = T1C + T1N;
		    T1X = T1V + T1W;
		    T23 = T21 + T22;
		    T28 = T26 + T27;
		    T4r = T23 + T28;
		    T2W = T21 - T22;
		    T2X = T26 - T27;
		    T4c = T2W + T2X;
		    T33 = T2C + T2F;
		    T34 = T2H + T2K;
		    T35 = T33 + T34;
		    T2G = T2C - T2F;
		    T2L = T2H - T2K;
		    T2M = T2G + T2L;
	       }
	       {
		    E Tu, T3n, T2c, T2r, T12, T3r, T2i, T2z, TF, T3o, T2d, T2u, TR, T3q, T2h;
		    E T2w;
		    {
			 E To, T2a, Tt, T2b;
			 {
			      E Tl, Tn, Tk, Tm;
			      Tl = ri[WS(rs, 4)];
			      Tn = ii[WS(rs, 4)];
			      Tk = W[6];
			      Tm = W[7];
			      To = FMA(Tk, Tl, Tm * Tn);
			      T2a = FNMS(Tm, Tl, Tk * Tn);
			 }
			 {
			      E Tq, Ts, Tp, Tr;
			      Tq = ri[WS(rs, 14)];
			      Ts = ii[WS(rs, 14)];
			      Tp = W[26];
			      Tr = W[27];
			      Tt = FMA(Tp, Tq, Tr * Ts);
			      T2b = FNMS(Tr, Tq, Tp * Ts);
			 }
			 Tu = To + Tt;
			 T3n = T2a + T2b;
			 T2c = T2a - T2b;
			 T2r = To - Tt;
		    }
		    {
			 E TW, T2x, T11, T2y;
			 {
			      E TT, TV, TS, TU;
			      TT = ri[WS(rs, 1)];
			      TV = ii[WS(rs, 1)];
			      TS = W[0];
			      TU = W[1];
			      TW = FMA(TS, TT, TU * TV);
			      T2x = FNMS(TU, TT, TS * TV);
			 }
			 {
			      E TY, T10, TX, TZ;
			      TY = ri[WS(rs, 11)];
			      T10 = ii[WS(rs, 11)];
			      TX = W[20];
			      TZ = W[21];
			      T11 = FMA(TX, TY, TZ * T10);
			      T2y = FNMS(TZ, TY, TX * T10);
			 }
			 T12 = TW + T11;
			 T3r = T2x + T2y;
			 T2i = TW - T11;
			 T2z = T2x - T2y;
		    }
		    {
			 E Tz, T2s, TE, T2t;
			 {
			      E Tw, Ty, Tv, Tx;
			      Tw = ri[WS(rs, 9)];
			      Ty = ii[WS(rs, 9)];
			      Tv = W[16];
			      Tx = W[17];
			      Tz = FMA(Tv, Tw, Tx * Ty);
			      T2s = FNMS(Tx, Tw, Tv * Ty);
			 }
			 {
			      E TB, TD, TA, TC;
			      TB = ri[WS(rs, 19)];
			      TD = ii[WS(rs, 19)];
			      TA = W[36];
			      TC = W[37];
			      TE = FMA(TA, TB, TC * TD);
			      T2t = FNMS(TC, TB, TA * TD);
			 }
			 TF = Tz + TE;
			 T3o = T2s + T2t;
			 T2d = Tz - TE;
			 T2u = T2s - T2t;
		    }
		    {
			 E TL, T2f, TQ, T2g;
			 {
			      E TI, TK, TH, TJ;
			      TI = ri[WS(rs, 16)];
			      TK = ii[WS(rs, 16)];
			      TH = W[30];
			      TJ = W[31];
			      TL = FMA(TH, TI, TJ * TK);
			      T2f = FNMS(TJ, TI, TH * TK);
			 }
			 {
			      E TN, TP, TM, TO;
			      TN = ri[WS(rs, 6)];
			      TP = ii[WS(rs, 6)];
			      TM = W[10];
			      TO = W[11];
			      TQ = FMA(TM, TN, TO * TP);
			      T2g = FNMS(TO, TN, TM * TP);
			 }
			 TR = TL + TQ;
			 T3q = T2f + T2g;
			 T2h = T2f - T2g;
			 T2w = TL - TQ;
		    }
		    TG = Tu - TF;
		    T13 = TR - T12;
		    T14 = TG + T13;
		    T3p = T3n - T3o;
		    T3s = T3q - T3r;
		    T43 = T3p + T3s;
		    T3A = T3n + T3o;
		    T3B = T3q + T3r;
		    T3J = T3A + T3B;
		    T1S = Tu + TF;
		    T1T = TR + T12;
		    T1U = T1S + T1T;
		    T2e = T2c + T2d;
		    T2j = T2h + T2i;
		    T4q = T2e + T2j;
		    T2T = T2c - T2d;
		    T2U = T2h - T2i;
		    T4b = T2T + T2U;
		    T30 = T2r + T2u;
		    T31 = T2w + T2z;
		    T32 = T30 + T31;
		    T2v = T2r - T2u;
		    T2A = T2w - T2z;
		    T2B = T2v + T2A;
	       }
	       {
		    E T3e, T1Q, T3d, T3u, T3w, T3m, T3t, T3v, T3f;
		    T3e = KP559016994 * (T14 - T1P);
		    T1Q = T14 + T1P;
		    T3d = FNMS(KP250000000, T1Q, Tj);
		    T3m = T3i - T3l;
		    T3t = T3p - T3s;
		    T3u = FNMS(KP587785252, T3t, KP951056516 * T3m);
		    T3w = FMA(KP951056516, T3t, KP587785252 * T3m);
		    ri[WS(rs, 10)] = Tj + T1Q;
		    T3v = T3e + T3d;
		    ri[WS(rs, 14)] = T3v - T3w;
		    ri[WS(rs, 6)] = T3v + T3w;
		    T3f = T3d - T3e;
		    ri[WS(rs, 2)] = T3f - T3u;
		    ri[WS(rs, 18)] = T3f + T3u;
	       }
	       {
		    E T47, T45, T46, T41, T4a, T3Z, T40, T49, T48;
		    T47 = KP559016994 * (T43 - T44);
		    T45 = T43 + T44;
		    T46 = FNMS(KP250000000, T45, T42);
		    T3Z = T1r - T1O;
		    T40 = TG - T13;
		    T41 = FNMS(KP587785252, T40, KP951056516 * T3Z);
		    T4a = FMA(KP951056516, T40, KP587785252 * T3Z);
		    ii[WS(rs, 10)] = T45 + T42;
		    T49 = T47 + T46;
		    ii[WS(rs, 6)] = T49 - T4a;
		    ii[WS(rs, 14)] = T4a + T49;
		    T48 = T46 - T47;
		    ii[WS(rs, 2)] = T41 + T48;
		    ii[WS(rs, 18)] = T48 - T41;
	       }
	       {
		    E T3x, T1Y, T3y, T3G, T3I, T3C, T3F, T3H, T3z;
		    T3x = KP559016994 * (T1U - T1X);
		    T1Y = T1U + T1X;
		    T3y = FNMS(KP250000000, T1Y, T1R);
		    T3C = T3A - T3B;
		    T3F = T3D - T3E;
		    T3G = FMA(KP951056516, T3C, KP587785252 * T3F);
		    T3I = FNMS(KP587785252, T3C, KP951056516 * T3F);
		    ri[0] = T1R + T1Y;
		    T3H = T3y - T3x;
		    ri[WS(rs, 12)] = T3H - T3I;
		    ri[WS(rs, 8)] = T3H + T3I;
		    T3z = T3x + T3y;
		    ri[WS(rs, 4)] = T3z - T3G;
		    ri[WS(rs, 16)] = T3z + T3G;
	       }
	       {
		    E T3U, T3L, T3V, T3T, T3Y, T3R, T3S, T3X, T3W;
		    T3U = KP559016994 * (T3J - T3K);
		    T3L = T3J + T3K;
		    T3V = FNMS(KP250000000, T3L, T3Q);
		    T3R = T1S - T1T;
		    T3S = T1V - T1W;
		    T3T = FMA(KP951056516, T3R, KP587785252 * T3S);
		    T3Y = FNMS(KP587785252, T3R, KP951056516 * T3S);
		    ii[0] = T3L + T3Q;
		    T3X = T3V - T3U;
		    ii[WS(rs, 8)] = T3X - T3Y;
		    ii[WS(rs, 12)] = T3Y + T3X;
		    T3W = T3U + T3V;
		    ii[WS(rs, 4)] = T3T + T3W;
		    ii[WS(rs, 16)] = T3W - T3T;
	       }
	       {
		    E T2P, T2N, T2O, T2l, T2R, T29, T2k, T2S, T2Q;
		    T2P = KP559016994 * (T2B - T2M);
		    T2N = T2B + T2M;
		    T2O = FNMS(KP250000000, T2N, T2q);
		    T29 = T23 - T28;
		    T2k = T2e - T2j;
		    T2l = FNMS(KP587785252, T2k, KP951056516 * T29);
		    T2R = FMA(KP951056516, T2k, KP587785252 * T29);
		    ri[WS(rs, 15)] = T2q + T2N;
		    T2S = T2P + T2O;
		    ri[WS(rs, 11)] = T2R + T2S;
		    ri[WS(rs, 19)] = T2S - T2R;
		    T2Q = T2O - T2P;
		    ri[WS(rs, 3)] = T2l + T2Q;
		    ri[WS(rs, 7)] = T2Q - T2l;
	       }
	       {
		    E T4u, T4s, T4t, T4y, T4A, T4w, T4x, T4z, T4v;
		    T4u = KP559016994 * (T4q - T4r);
		    T4s = T4q + T4r;
		    T4t = FNMS(KP250000000, T4s, T4p);
		    T4w = T2G - T2L;
		    T4x = T2v - T2A;
		    T4y = FNMS(KP587785252, T4x, KP951056516 * T4w);
		    T4A = FMA(KP951056516, T4x, KP587785252 * T4w);
		    ii[WS(rs, 15)] = T4s + T4p;
		    T4z = T4u + T4t;
		    ii[WS(rs, 11)] = T4z - T4A;
		    ii[WS(rs, 19)] = T4A + T4z;
		    T4v = T4t - T4u;
		    ii[WS(rs, 3)] = T4v - T4y;
		    ii[WS(rs, 7)] = T4y + T4v;
	       }
	       {
		    E T36, T38, T39, T2Z, T3b, T2V, T2Y, T3c, T3a;
		    T36 = KP559016994 * (T32 - T35);
		    T38 = T32 + T35;
		    T39 = FNMS(KP250000000, T38, T37);
		    T2V = T2T - T2U;
		    T2Y = T2W - T2X;
		    T2Z = FMA(KP951056516, T2V, KP587785252 * T2Y);
		    T3b = FNMS(KP587785252, T2V, KP951056516 * T2Y);
		    ri[WS(rs, 5)] = T37 + T38;
		    T3c = T39 - T36;
		    ri[WS(rs, 13)] = T3b + T3c;
		    ri[WS(rs, 17)] = T3c - T3b;
		    T3a = T36 + T39;
		    ri[WS(rs, 1)] = T2Z + T3a;
		    ri[WS(rs, 9)] = T3a - T2Z;
	       }
	       {
		    E T4d, T4h, T4i, T4m, T4o, T4k, T4l, T4n, T4j;
		    T4d = KP559016994 * (T4b - T4c);
		    T4h = T4b + T4c;
		    T4i = FNMS(KP250000000, T4h, T4g);
		    T4k = T30 - T31;
		    T4l = T33 - T34;
		    T4m = FMA(KP951056516, T4k, KP587785252 * T4l);
		    T4o = FNMS(KP587785252, T4k, KP951056516 * T4l);
		    ii[WS(rs, 5)] = T4h + T4g;
		    T4n = T4i - T4d;
		    ii[WS(rs, 13)] = T4n - T4o;
		    ii[WS(rs, 17)] = T4o + T4n;
		    T4j = T4d + T4i;
		    ii[WS(rs, 1)] = T4j - T4m;
		    ii[WS(rs, 9)] = T4m + T4j;
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     { TW_FULL, 0, 20 },
     { TW_NEXT, 1, 0 }
};

static const ct_desc desc = { 20, "t1_20", twinstr, &GENUS, { 184, 62, 62, 0 }, 0, 0, 0 };

void X(codelet_t1_20) (planner *p) {
     X(kdft_dit_register) (p, t1_20, &desc);
}
#endif
