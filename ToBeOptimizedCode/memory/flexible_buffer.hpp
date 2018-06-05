#pragma once

#include <cstring>

struct FlexibleBuffer
{
	FlexibleBuffer() : buffer(NULL), buffer_size(0) {}
	~FlexibleBuffer()
	{
		this->ChangeBufferSize(0);
	}

	char *GetBuffer() { return buffer; }
	int GetBufferSize() { return buffer_size; }

	bool SetBuffer(char *buff, int length)
	{
		if (0 >= length)
		return false;

		this->ChangeBufferSize(length);
		memcpy(buffer, buff, length);

		return true;
	}

	bool ChangeBufferSize(int size)
	{
		if (buffer_size == size)
			return true;

		int min_buffer_size = (size < buffer_size) ? size : buffer_size;

		buffer_size = size;
			
		char *old_buffer = buffer;

		if (size > 0)
		{
			buffer = new char[size];
			memset(buffer, 0, buffer_size);

			if (NULL != old_buffer)
				memcpy(buffer, old_buffer, min_buffer_size);
		}

		if (NULL != old_buffer) delete[] old_buffer;
		return true;
  }

	bool ZeroAllBytes()
	{
		if (NULL == buffer || buffer_size <= 0)
			return false;

		memset(buffer, 0, buffer_size);
		return true;
	}

	char *buffer;
	int buffer_size;
};

