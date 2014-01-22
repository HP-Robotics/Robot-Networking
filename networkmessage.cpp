#include "networkmessage.h"
#include <stdexcept>
#include <stdio.h>

int i = 0;

networkmessage::networkmessage()
{}

networkmessage::~networkmessage()
{}


std::map<GUID, messagecreator>& networkmessage::getFactoryTable()
{
	static std::map<GUID, messagecreator> factorytable;
	return factorytable;
}

networkmessage* networkmessage::createmessage(GUID guid, unsigned char* data, int datalen)
{
	try {
		return getFactoryTable().at(guid)(data, datalen);
	}
	catch(std::out_of_range ex){
		throw guidunregisteredexception(guid);
	}
}

bool networkmessage::ismessageregistered(GUID guid)
{
	return getFactoryTable().count(guid); //can only be 0 or 1
}
void networkmessage::registermessage(GUID guid, messagecreator creator)
{
	getFactoryTable()[guid] = creator;
	
}
void networkmessage::unregistermessage(GUID guid)
{
	getFactoryTable().erase(guid);
}
