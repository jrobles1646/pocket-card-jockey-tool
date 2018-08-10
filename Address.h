#ifndef ADDRESS_H
#define ADDRESS_H

class Address
{
private:
	short int speedOffset;
	short int staminaOffset;
	short int winsOffset;
	short int racesOffset;
	short int peak1Offset;
	short int peak2Offset;
	short int nameOffset[32];
public:
	Address();
};
#endif