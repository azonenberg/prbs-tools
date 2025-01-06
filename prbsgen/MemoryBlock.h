/***********************************************************************************************************************
*                                                                                                                      *
* prbs-tools                                                                                                           *
*                                                                                                                      *
* Copyright (c) 2025 Andrew D. Zonenberg                                                                               *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

#ifndef MemoryBlock_h
#define MemoryBlock_h

#include <vector>

#include "PRBSGenerator.h"

/**
	@brief A chunk of memory
 */
template <class T>
class MemoryBlock
{
public:

	/**
		@brief Allocate the buffer and fill with zeroes
	 */
	MemoryBlock(size_t len)
	{
		m_data.resize(len);
		for(size_t i=0; i<len; i++)
			m_data[i] = 0;
	}

	/**
		@brief Fill with a PRBS in a bit-plane fashion
	 */
	void FillBitPlane(size_t nplanes, PRBSGenerator& gen)
	{
		size_t nwords = m_data.size();
		size_t nbits = nplanes * nwords;
		size_t period = gen.GetPeriod();

		//Warn if requested dataset is larger than sequence length
		if(nbits > period)
		{
			printf("WARNING: dataset requires %d bits of output, but selected polynomial repeats after %d bits\n",
				nbits, period);
		}

		for(size_t plane = 0; plane < nplanes; plane ++)
		{
			T bitval = (1LL << plane);

			for(size_t nword = 0; nword < nwords; nword ++)
			{
				if(gen.GenerateNextBit())
					m_data[nword] |= bitval;
			}
		}
	}

	///@brief The actual memory data
	std::vector<T> m_data;
};

#endif
