#include "ffttestsuite.h"

#include "gslpp/Vector/vector.h"
#include "gslpp/FFT/fft.h"

CPPUNIT_TEST_SUITE_REGISTRATION( FFTTestSuite );

void FFTTestSuite::setUp(){}

void FFTTestSuite::tearDown(){}

void FFTTestSuite::Radix2()
{
	const size_t N = 512;
	gsl::r_vec v( N );
	for ( size_t i = 0; i < N; ++i )
		v[ i ] = std::sin( 2.0 * gsl::pi * static_cast< real >(i)/static_cast< real >(N) );
		
	gsl::r_vec::iterator start = v.begin();
	gsl::fft::radix2< gsl::fft::type_forward >( start, v.end() );
}
