#if !defined ENDEAVOR_STATE
#define ENDEAVOR_STATE

#include "EndeavorHeader.h"
#include "String_.h"

class EndeavorAI;
class EndeavorState
{
   private:
		CSC1310::String* state_key;

   public:
      EndeavorState(CSC1310::String* key);
      virtual ~EndeavorState();
	  
	  CSC1310::String* getKey();

      virtual void mouseClicked(uint32 x, uint32 y) = 0;
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id) = 0;
	  
	  static int computeHashFunctionState(EndeavorState* state);
      static int computeHashFunctionKey(CSC1310::String* key);
	  
	  static int compareStates(EndeavorState* state_1, EndeavorState* state_2);
	  static int compareStatesByKeyAndState(CSC1310::String* key, EndeavorState* state);
	  
};

#endif