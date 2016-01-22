#include "SP_use_count.h"



SP_use_count::SP_use_count()
{
	use_count = 0;
}

SP_use_count::SP_use_count(int i) {
	use_count = i;
}

SP_use_count::SP_use_count(SP_use_count& spuc) {
	*this = spuc;
}

SP_use_count::~SP_use_count()
{
}

SP_use_count& SP_use_count::operator=(SP_use_count& spuc) {
	*this = spuc;
	return *this;
}

void SP_use_count::decUseCount()
{
	if(this != nullptr)
		--use_count;
}

void SP_use_count::addUseCount()
{
	if (this != nullptr)
		++use_count;
}

int SP_use_count::getUseCount()
{
	return use_count;
}

SP_use_count& SP_use_count::getThis() {
	return *this;
}

void SP_use_count::setUseCount(int i)
{
	use_count = i;
}
