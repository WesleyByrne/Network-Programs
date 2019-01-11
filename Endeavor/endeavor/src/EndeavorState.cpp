#include "EndeavorState.h"

EndeavorState::EndeavorState(CSC1310::String* key)
{
	state_key = key;
}

EndeavorState::~EndeavorState()
{
	delete state_key;
}

CSC1310::String* EndeavorState::getKey()
{
	return state_key;
}

int EndeavorState::computeHashFunctionState(EndeavorState* state)
{
	return computeHashFunctionKey(state->getKey());
}

int EndeavorState::computeHashFunctionKey(CSC1310::String* key)
{
	return key->computeHashFunctionByASCIISum();
}

int EndeavorState::compareStates(EndeavorState* state_1, EndeavorState* state_2)
{
	CSC1310::String* key_1 = state_1->getKey();
	CSC1310::String* key_2 = state_2->getKey();
	return key_1->compare(key_2);
}

int EndeavorState::compareStatesByKeyAndState(CSC1310::String* key_1, EndeavorState* state)
{
	CSC1310::String* key_2 = state->getKey();
	return key_1->compare(key_2);
}
