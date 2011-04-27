/*******************************************
 * SequenceDataType.h
 * @author Yuki Suga
 * @copyright Yuki Suga (ysuga.net) Nov, 10th, 2010.
 * @license LGPLv3
 *****************************************/

#include <stdlib.h>
#include "SequenceDataType.h"

SequenceDataType::SequenceDataType(void** ptrptr)
{
  m_ptrptr = ptrptr;*m_ptrptr = 0;len = 0;
}

SequenceDataType::~SequenceDataType()
{
  free(*m_ptrptr);
}


void SequenceDataType::length(int size)
{
  len = size;
  free(*m_ptrptr);
  *m_ptrptr = (void*)malloc(size * SizeofData());
}

