#pragma once

typedef double real;

const real realZero = 0.0;
const real realOne = 1.0;
const real realEmpty = 0x1.fffffffffffffp+1023;
const real NaN = -realEmpty;
const real realPlusInf = realEmpty - 1;
const real realMinusInf = -realPlusInf;

inline bool IsEmpty( real x ){	return x == realEmpty;	}