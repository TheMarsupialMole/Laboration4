#pragma once

class SP_use_count
{
private:
	int use_count;
public:
	SP_use_count();
	SP_use_count(int);
	SP_use_count(SP_use_count& spuc);
	~SP_use_count();

	SP_use_count& operator=(SP_use_count& spuc);

	void decUseCount();
	void addUseCount();
	int getUseCount();
	SP_use_count& getThis();
	void setUseCount(int);
};

