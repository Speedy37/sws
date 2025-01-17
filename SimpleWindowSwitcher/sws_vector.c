#include "sws_vector.h"

sws_error_t sws_vector_PushBack(sws_vector* _this, void* pElement)
{
	sws_error_t rv = SWS_ERROR_SUCCESS;

	if (!rv)
	{
		if (_this->cbCapacity == 0 || _this->cbElementSize == 0)
		{
			rv = sws_error_Report(sws_error_GetFromInternalError(SWS_ERROR_NO_MEMORY), NULL);
		}
	}
	if (!rv)
	{
		if (_this->cbSize >= _this->cbCapacity)
		{
			void* prev = _this->pList;
			_this->pList = realloc(_this->pList, (uintptr_t)_this->cbElementSize * (uintptr_t)((uintptr_t)_this->cbCapacity + SWS_VECTOR_CAPACITY));
			if (!_this->pList)
			{
				free(prev);
				_this->cbElementSize = 0;
				_this->cbCapacity = 0;
				_this->cbSize = 0;
				rv = sws_error_Report(sws_error_GetFromInternalError(SWS_ERROR_NO_MEMORY), NULL);
			}
			else
			{
				_this->cbCapacity = _this->cbCapacity + SWS_VECTOR_CAPACITY;
			}
		}
	}
	if (!rv)
	{
		memcpy((uintptr_t)_this->pList + (uintptr_t)_this->cbSize * (uintptr_t)_this->cbElementSize, pElement, _this->cbElementSize);
		_this->cbSize++;
	}

	return rv;
}

void sws_vector_Clear(sws_vector* _this)
{
	if (_this)
	{
		free(_this->pList);
		memset(_this, 0, sizeof(sws_vector));
	}
}

sws_error_t sws_vector_Initialize(sws_vector* _this, unsigned int cbElementSize)
{
	sws_error_t rv = SWS_ERROR_SUCCESS;

	if (!rv)
	{
		if (!_this)
		{
			rv = sws_error_Report(sws_error_GetFromInternalError(SWS_ERROR_NO_MEMORY), NULL);
		}
	}
	if (!rv)
	{
		_this->pList = calloc(SWS_VECTOR_CAPACITY, cbElementSize);
		if (!_this->pList)
		{
			rv = sws_error_Report(sws_error_GetFromInternalError(SWS_ERROR_NO_MEMORY), NULL);
		}
		_this->cbElementSize = cbElementSize;
		_this->cbCapacity = SWS_VECTOR_CAPACITY;
		_this->cbSize = 0;
	}

	return rv;
}