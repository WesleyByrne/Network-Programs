#if !defined GUI_HEADER
#define GUI_HEADER

	typedef unsigned int uint32;
	typedef unsigned char uint8;
	
	#if !defined PRINT
	#define PRINT(to_print)  \
							{ \
							std::cout << to_print << std::endl; \
							}
	#endif

#endif
