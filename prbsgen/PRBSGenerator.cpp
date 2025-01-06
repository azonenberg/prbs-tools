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

#include "PRBSGenerator.h"

bool PRBSGenerator::GenerateNextBit()
{
	uint32_t next;
	switch(m_poly)
	{
		case Polynomial::PRBS7:
			next = ( (m_state >> 6) ^ (m_state >> 5) ) & 1;
			break;

		case Polynomial::PRBS9:
			next = ( (m_state >> 8) ^ (m_state >> 4) ) & 1;
			break;

		case Polynomial::PRBS11:
			next = ( (m_state >> 10) ^ (m_state >> 8) ) & 1;
			break;

		case Polynomial::PRBS15:
			next = ( (m_state >> 14) ^ (m_state >> 13) ) & 1;
			break;

		case Polynomial::PRBS23:
			next = ( (m_state >> 22) ^ (m_state >> 17) ) & 1;
			break;

		case Polynomial::PRBS31:
		default:
			next = ( (m_state >> 30) ^ (m_state >> 27) ) & 1;
			break;
	}
	m_state = (m_state << 1) | next;
	return (bool)next;
}

size_t PRBSGenerator::GetPeriod()
{
	switch(m_poly)
	{
		case Polynomial::PRBS7:
			return (1LL << 7) - 1;

		case Polynomial::PRBS9:
			return (1LL << 9) - 1;

		case Polynomial::PRBS11:
			return (1LL << 11) - 1;

		case Polynomial::PRBS15:
			return (1LL << 15) - 1;

		case Polynomial::PRBS23:
			return (1LL << 23) - 1;

		case Polynomial::PRBS31:
		default:
			return (1LL << 31) - 1;
	}
}
