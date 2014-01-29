#include "networkbuffer_out.h"

#include <cstring>
#include <cstdlib>

networkbuffer_out::networkbuffer_out(const unsigned char* raw, int length)
	:_buffer(0), _size(length), _offset(0)
{
	_buffer = malloc(length * sizeof(char));
	memcpy(_buffer, raw, length);
}


int networkbuffer_out::getSize() const
{
	return _size;
}

networkbuffer_out& networkbuffer_out::operator>>(bool& v)
{
	return operator>>((unsigned char&)v);
}
networkbuffer_out& networkbuffer_out::operator>>(char& v )
{
	return operator>>((unsigned char&)v);
}
networkbuffer_out& networkbuffer_out::operator>>(short& v)
{
	return operator>>((unsigned short&)v);
}
networkbuffer_out& networkbuffer_out::operator>>(int& v)
{
	return operator>>((unsigned int&)v);
}
networkbuffer_out& networkbuffer_out::operator>>(unsigned char& v)
{
	v = v[_offset++];
}
networkbuffer_out& networkbuffer_out::operator>>(unsigned short& v)
{
	unsigned char big, small;
	big = v[_offset++];
	small = v[_offset++];
	unsigned short network = (((short)big) << 8) | small;
	
	v = ntohs(network);
}
networkbuffer_out& networkbuffer_out::operator>>(unsigned int& v)
{
	//sorry about these variable names :D
	unsigned char bigest, big, small, smallest;
	bigest = v[_offset++];
	big = v[_offset++];
	small = v[_offset++];
	smallest = v[_offset++];
	unsigned int network = (((int)bigest) << 24) | ((int)big) << 16) | ((int)big) << 8) | small;
	
	v = ntohs(network);
}
networkbuffer_out& networkbuffer_out::operator>>(string& v)
{
	
}
int copyfrom(char* buffer, int bytestocopy)
{
	//TODO:
	//memcpy(buffer, (_buffer + _offset), bytestocopy) 
}
